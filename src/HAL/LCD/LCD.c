/**********************************************************************************************************/
/*******************************************************Includes: *****************************************/
/**********************************************************************************************************/
#include <HAL/LCD/LCD.h>
#include <MCAL/RCC/RCC.h>
#include <HAL/LED/LED.h>
/**********************************************************************************************************/
/*******************************************************Defines: ******************************************/
/**********************************************************************************************************/
typedef struct 
{
    uint8_t ReqType;
    uint8_t ReqState;
    uint8_t cursor_x;
    uint8_t cursor_y;
    uint8_t* string;
    uint8_t strSize;
    uint64_t Number;
    uint32_t DigitsNumber;
}LCD_UserRequest_t;

#define CONCAT_HELPER(pin7, pin6, pin5, pin4, pin3, pin2, pin1, pin0) (0b##pin7##pin6##pin5##pin4##pin3##pin2##pin1##pin0)
#define CONCAT(a, b, c, d, e, f, g, h) CONCAT_HELPER(a, b, c, d, e, f, g, h)
#define LCD_EIGHTBITMODE_FUNCTIONSET		CONCAT(0,0,1,1,NUMBER_OF_LINES,CHARACTER_FONT,0,0)
#define LCD_EIGHTBITMODE_DISPLAYCONTROL		CONCAT(0,0,0,0,1,DISPLAY_STATE,CURSOR_STATE,CURSOR_BLINKING_STATE)
#define LCD_EIGHTBITMODE_CLEAR				0x01
#define LCD_EIGHTBITMODE_ENTERMODE			0x03           /* 0000 0110 */
#define LCD_HOME							0x02        /*return cursor to first position on first line*/
#define CURSOR_SET                          0x80          /*set cursor position*/
/**********************************************************************************************************/
/*******************************************************Enums: ********************************************/
/**********************************************************************************************************/
enum 
{
    LCD_enumState_Off,
    LCD_enumState_Init,
    LCD_enumState_Operational
};

enum
{
    LCD_enumState_Idle,
    LCD_enumState_Busy
};

enum 
{
    LCD_enumRequest_Write ,
    LCD_enumRequest_WriteNumber ,
    LCD_enumRequest_clear,
    LCD_enumRequest_SetCursor,
    LCD_enumRequest_NoRequest
};


enum 
{
    LCD_WriteNumberState_CalculateDigits,
    LCD_WriteNumberState_Print,
    LCD_WriteNumberState_Finished
};
/**********************************************************************************************************/
/*******************************************************Variables: ****************************************/
/**********************************************************************************************************/
extern LCD_PinConfig LCD_Config[LCD_MODE];
static uint8_t LCD_Global_State = LCD_enumState_Init;
static LCD_UserRequest_t User_Req;

/**********************************************************************************************************/
/******************************************************static functions prototype: ************************/
/**********************************************************************************************************/
static void LCD_InitProcess(void);
static void LCD_WriteStringProcess(void);
static void LCD_ClearProcess(void);
static void LCD_WriteCommandProcess(uint8_t Command);
static void LCD_WriteDataProcess(uint8_t data);
static void LCD_WriteNumberProcess(void);
/**********************************************************************************************************/
/*******************************************************APIs: *********************************************/
/**********************************************************************************************************/
static void LCD_WriteCommandProcess(uint8_t Command)
{
    /* set RS and RW pins by 0 to write command*/
    GPIO_SetPinValue(LCD_Config[RS].port, LCD_Config[RS].pin, GPIO_STATE_LOW);
    GPIO_SetPinValue(LCD_Config[RW].port, LCD_Config[RW].pin, GPIO_STATE_LOW);
    GPIO_SetPinValue(LCD_Config[E].port, LCD_Config[E].pin, GPIO_STATE_LOW);
    /*send the command*/
    for (uint8_t itr = 0; itr < 8; itr++)
    {
        if(((Command >> itr) & 1) == 1)
        {
            GPIO_SetPinValue(LCD_Config[itr].port, LCD_Config[itr].pin, GPIO_STATE_HIGH);
        }
        else
        {
            GPIO_SetPinValue(LCD_Config[itr].port, LCD_Config[itr].pin, GPIO_STATE_LOW);
        }
    }
    /* high on enable pin */
    GPIO_SetPinValue(LCD_Config[E].port, LCD_Config[E].pin, GPIO_STATE_HIGH);
    /* @note make sure you triggering enable after call this function*/
}

static void LCD_WriteDataProcess(uint8_t data)
{
    /* set RW pins by 0 and RS pin by 1 to write data*/
    GPIO_SetPinValue(LCD_Config[RS].port, LCD_Config[RS].pin, GPIO_STATE_HIGH);
    GPIO_SetPinValue(LCD_Config[RW].port, LCD_Config[RW].pin, GPIO_STATE_LOW);
    GPIO_SetPinValue(LCD_Config[E].port, LCD_Config[E].pin, GPIO_STATE_LOW);
    /*send the data*/
    for (uint8_t itr = 0; itr < 8; itr++)
    {
        if(((data >> itr) & 1) == 1)
        {
            GPIO_SetPinValue(LCD_Config[itr].port, LCD_Config[itr].pin, GPIO_STATE_HIGH);
        }
        else
        {
            GPIO_SetPinValue(LCD_Config[itr].port, LCD_Config[itr].pin, GPIO_STATE_LOW);
        }
    }
    /* high on enable pin */
    GPIO_SetPinValue(LCD_Config[E].port, LCD_Config[E].pin, GPIO_STATE_HIGH);
    /* @note make sure you triggering enable after call this function*/
}

ErrorStatus_t LCD_initAsynch(void) 
{
    ErrorStatus_t Loc_Return = Ok; // Variable to store the return status
    GPIO_PIN_t LCD_struct; // Structure to hold GPIO pin configuration

    // Enable GPIO ports A, B, and C clocks
    Loc_Return = RCC_Control_AHB1Peripherals(RCC_PERI_AHB1ENR_GPIOA, Status_Enable);
    Loc_Return = RCC_Control_AHB1Peripherals(RCC_PERI_AHB1ENR_GPIOB, Status_Enable);
    Loc_Return = RCC_Control_AHB1Peripherals(RCC_PERI_AHB1ENR_GPIOC, Status_Enable);
    
    #if LCD_MODE == LCD_8_BIT_MODE // Configuration for 8-bit mode
        // Iterate over each pin required for 8-bit mode
        for(uint8_t itr = 0 ; itr < LCD_MODE ; itr++) {
            // Configure GPIO struct with LCD pin details
            LCD_struct.port  = LCD_Config[itr].port;
            LCD_struct.pin   = LCD_Config[itr].pin;
            LCD_struct.speed = GPIO_SPEED_HIGH;
            LCD_struct.mode  = GPIO_MODE_OUT_PP;

            // Initialize GPIO pin
            Loc_Return = GPIO_Init(&LCD_struct);
            GPIO_SetPinValue(LCD_Config[itr].port, LCD_Config[itr].pin, GPIO_STATE_LOW);
        }

    #elif LCD_MODE == LCD_4_BIT_MODE // Configuration for 4-bit mode
        // Iterate over each pin required for 4-bit mode
        for(uint8_t itr= 4; itr< 11; itr++) {
            // Configure GPIO struct with LCD pin details
            LCD_struct.port  = LCD_Config[itr].port;
            LCD_struct.pin   = LCD_Config[itr].pin;
            LCD_struct.speed = GPIO_SPEED_HIGH;
            LCD_struct.mode  = GPIO_MODE_OUT_PP;

            // Initialize GPIO pin
            Loc_Return = GPIO_Init(&LCD_struct);
            GPIO_SetPinValue(LCD_Config[itr].port, LCD_Config[itr].pin, GPIO_STATE_LOW);
        }
    #endif 

    LCD_Global_State = LCD_enumState_Init;
    return Loc_Return; // Return the status of initialization
}

ErrorStatus_t LCD_WriteStringAsynch(uint8_t* string)
{
    ErrorStatus_t Loc_Return = Ok;
    if(string == NULL)
    {
        Loc_Return = NullPointerError;
    }
    else
    {
        Loc_Return = Ok;
        User_Req.ReqState = LCD_enumState_Busy;
        User_Req.ReqType = LCD_enumRequest_Write;
        User_Req.string = string;
    }
    return Loc_Return;
}


static void LCD_InitProcess(void)
{
    static uint32_t Init_counter = 0;
    if(Init_counter == 30)
    {
        LCD_WriteCommandProcess(LCD_HOME);
    }
    else if (Init_counter == 31)
    {
        /* trigger enable pin */
        GPIO_SetPinValue(LCD_Config[E].port, LCD_Config[E].pin, GPIO_STATE_LOW);
    }
    /* function set */
    else if (Init_counter == 32)
    {
        LCD_WriteCommandProcess(LCD_EIGHTBITMODE_FUNCTIONSET);
    }
    else if (Init_counter == 33)
    {
        /* trigger enable pin */
        GPIO_SetPinValue(LCD_Config[E].port, LCD_Config[E].pin, GPIO_STATE_LOW);
    }
    /* Display Control */
    else if (Init_counter == 34)
    {
        LCD_WriteCommandProcess(LCD_EIGHTBITMODE_DISPLAYCONTROL);
    }
    else if(Init_counter == 35)
    {
        /* trigger enable pin */
        GPIO_SetPinValue(LCD_Config[E].port, LCD_Config[E].pin, GPIO_STATE_LOW);
    }
    /* clear display */
    else if (Init_counter == 36)
    {
        LCD_WriteCommandProcess(LCD_EIGHTBITMODE_CLEAR);
    }
    else if (Init_counter == 37)
    {
        /* trigger enable pin */
        GPIO_SetPinValue(LCD_Config[E].port, LCD_Config[E].pin, GPIO_STATE_LOW);
    }
    else if (Init_counter == 39)
    {
        LCD_WriteCommandProcess(LCD_EIGHTBITMODE_ENTERMODE);
    }
    else if(Init_counter == 40)
    {
        /* trigger enable pin */
        GPIO_SetPinValue(LCD_Config[E].port, LCD_Config[E].pin, GPIO_STATE_LOW);
        LCD_Global_State = LCD_enumState_Operational;
    }
    else
    {
        /* do nothing */
    }

    Init_counter ++;
}

static void LCD_WriteStringProcess(void)
{
    static uint32_t TimeCounter = 0;
    if(User_Req.string[TimeCounter] != '\0')
    {
        //if(!EnablepinTriggerd)
        //{
        //    /* trigger enable pin */
        //    GPIO_SetPinValue(LCD_Config[E].port, LCD_Config[E].pin, GPIO_STATE_LOW);
        //    EnablepinTriggerd = 1;
        //}
        //else
        //{
        //    LCD_WriteDataProcess(User_Req.string[TimeCounter-2]);
        //    WriteStringCounter++;
        //    EnablepinTriggerd = 0;
        //}

        LCD_WriteDataProcess(User_Req.string[TimeCounter]);
        GPIO_SetPinValue(LCD_Config[E].port, LCD_Config[E].pin, GPIO_STATE_LOW);                
    }
    else 
    {
        User_Req.string = NULL;
        User_Req.ReqState = LCD_enumState_Idle;
        User_Req.ReqType = LCD_enumRequest_NoRequest;
    }
    TimeCounter++;
}


static void LCD_ClearProcess(void)
{
    static uint8_t Counter = 0;
    if(Counter == 0)
    {
        LCD_WriteCommandProcess(LCD_EIGHTBITMODE_CLEAR);
        
    }
    else if(Counter ==2)
    {
        /* trigger enable pin */
        GPIO_SetPinValue(LCD_Config[E].port, LCD_Config[E].pin, GPIO_STATE_LOW);
    }
    else if( Counter == 4 )
    {
        User_Req.ReqType = LCD_enumRequest_NoRequest;
        User_Req.ReqState = LCD_enumState_Idle;
    }
    Counter++;
}

void LCD_ClearAsynch(void)
{
    User_Req.ReqType = LCD_enumRequest_clear;
    User_Req.ReqState = LCD_enumState_Busy;
}



ErrorStatus_t LCD_WriteNumberAsynch(uint64_t Number)
{
    if(LCD_Global_State == LCD_enumState_Operational && User_Req.ReqState == LCD_enumState_Idle)
    {
        User_Req.Number = Number;
        User_Req.ReqType = LCD_enumRequest_WriteNumber;
        User_Req.ReqState = LCD_enumState_Busy;
        if(Number == 0)
        {
            User_Req.DigitsNumber = 1;
        }
        while (Number != 0)
        {
            Number= Number/10;
            User_Req.DigitsNumber = User_Req.DigitsNumber + 1;
        }
        
    }
    return Ok;
}

void LCD_WriteNumberProcess(void)
{
    static uint32_t Counter = 0;
    uint8_t DigitsBuffer[15] = {0};
    static uint8_t WriteNumberState = 0;

    switch (WriteNumberState)
    {
        case LCD_WriteNumberState_CalculateDigits:
            while (User_Req.Number > 0)
            {
                uint8_t digit = User_Req.Number % 10;
                DigitsBuffer[Counter] = digit + '0';
                User_Req.Number /= 10;
                Counter++;
            }
            WriteNumberState = LCD_WriteNumberState_Print;
        break;
        
        case LCD_WriteNumberState_Print:
            for (uint8_t itr = Counter-1 ; itr >= 0; itr--)
            {
                LCD_WriteDataProcess(DigitsBuffer[itr]);
                Counter--;
                break;
            }
            GPIO_SetPinValue(LCD_Config[E].port, LCD_Config[E].pin, GPIO_STATE_LOW);
            if (Counter == 0)
            {
                WriteNumberState = LCD_WriteNumberState_Finished;
            } 
        break;

        case LCD_WriteNumberState_Finished:
            User_Req.DigitsNumber =0;
            User_Req.Number =0;
            User_Req.ReqState = LCD_enumState_Idle;
            User_Req.ReqType= LCD_enumRequest_NoRequest;
        break;

        default:
        
        break;
    }
}

void LCD_Runnable(void)
{
    switch (LCD_Global_State)
    {
        
        case LCD_enumState_Off:
            
        break;

        case LCD_enumState_Init:
            LCD_InitProcess();
        break;
        
        case LCD_enumState_Operational:
            if(User_Req.ReqState == LCD_enumState_Busy)
            {
                switch(User_Req.ReqType)
                {
                    case LCD_enumRequest_Write:
                        LCD_WriteStringProcess();
                    break;
                    
                    case LCD_enumRequest_clear:
                        LCD_ClearProcess();
                    break;
                    
                    case LCD_enumRequest_SetCursor:
                        //LCD_SetCursorProcess();
                    break;

                    case LCD_enumRequest_WriteNumber:
                        LCD_WriteNumberProcess();
                    break;

                    default:
                    
                    break;
                }
            }
            else
            {
                /* do nothing */
            }
        break;

        default:
        break;
    }
}




