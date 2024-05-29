#include "Flash.h"
/****************************************** Register Struct: *********************************************************/
typedef struct
{
    uint32_t ACR;
    uint32_t KEYR;
    uint32_t OPTKEYR;
    uint32_t SR;
    uint32_t CR;
    uint32_t OPTCR;
    uint32_t OPTCR1;   
}FLASH_t;

#define FLASH ((volatile FLASH_t*)0x40023C00)
/****************************************** APIs: ********************************************************************/
void FLASH_unlock(void)
{
    FLASH->KEYR = 0x45670123;
    FLASH->KEYR = 0xCDEF89AB;
}

/**
 * @brief Function to lock the flash after write operations
 * 
 * This function is used to lock the flash memory after write operations have been performed on it.
 * Once the flash memory is locked, no further write operations can be performed until it is unlocked again.
 * 
 * @note This function should be called after all write operations on the flash memory have been completed.
 */
void FLASH_lock(void)
{
    FLASH->CR |= (1 << 31);
}

/**
 * @brief Function to erase a specific flash sector
 * 
 * This function is used to erase a specific sector of the flash memory.
 * The sector to be erased is specified by the sector number.
 * 
 * @param sector The sector number to be erased
 * @return ErrorStatus_t Returns SUCCESS if the sector is successfully erased, otherwise returns ERROR
 */
ErrorStatus_t FLASH_eraseSector(uint8_t sector)
{
    ErrorStatus_t status = Ok;
    if (sector > FLASH_Sector_7)
    {
        status = NotOk;
    }
    
    else
    {
        FLASH->CR &= ~(0x1F << 3);
        FLASH->CR |= (sector << 3);
        FLASH->CR |= (1 << 1);
        
        while (FLASH->SR & (1 << 16))
        {
            // Wait for the BSY bit to be cleared
        }
        
        if (FLASH->SR & (1 << 0))
        {
            return ERROR;
        }
    }
    
    
    return SUCCESS;
}

/**
 * @brief Function to erase all flash sectors
 * 
 * This function is used to erase all sectors of the flash memory.
 * 
 * @return ErrorStatus_t Returns SUCCESS if all sectors are successfully erased, otherwise returns ERROR
 */
ErrorStatus_t FLASH_eraseAllSectors(void)
{
    FLASH->CR |= (1 << 2);
    
    while (FLASH->SR & (1 << 16))
    {
        // Wait for the BSY bit to be cleared
    }
    
    if (FLASH->SR & (1 << 0))
    {
        return ERROR;
    }
    
    return SUCCESS;
}


/**
 * @brief Function to program a word into flash memory
 * 
 * This function is used to program a 32-bit word into the flash memory at the specified address.
 * The data to be programmed is specified by the 'data' parameter.
 * 
 * @param address The address in flash memory where the data will be programmed
 * @param data The 32-bit word to be programmed into flash memory
 * @return ErrorStatus_t Returns SUCCESS if the word is successfully programmed, otherwise returns ERROR
 */
ErrorStatus_t FLASH_programWord(uint32_t address, uint32_t data)
{
    FLASH->CR |= (1 << 0);
    
    *(volatile uint32_t*)address = data;
    
    while (FLASH->SR & (1 << 16))
    {
        // Wait for the BSY bit to be cleared
    }
    
    if (FLASH->SR & (1 << 0))
    {
        return ERROR;
    }
    
    return SUCCESS;
}

/**
 * @brief Function to read a word from flash memory
 * 
 * This function is used to read a 32-bit word from the flash memory at the specified address.
 * The address from where the word will be read is specified by the 'address' parameter.
 * 
 * @param address The address in flash memory from where the word will be read
 * @return uint32_t The 32-bit word read from flash memory
 */
uint32_t FLASH_readWord(uint32_t address)
{
    return *(volatile uint32_t*)address;
}

/**
 * @brief Function to read a byte from flash memory
 * 
 * This function is used to read a byte from the flash memory at the specified address.
 * The address from where the byte will be read is specified by the 'address' parameter.
 * 
 * @param address The address in flash memory from where the byte will be read
 * @return uint8_t The byte read from flash memory
 */
uint8_t FLASH_readByte(uint32_t address)
{
    return *(volatile uint8_t*)address;
}
