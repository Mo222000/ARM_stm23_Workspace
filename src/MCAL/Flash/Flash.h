#ifndef FLASH
#define FLASH
/************************************************Includes: ************************************************/
#include <stdint.h>
#include <ErrorStatus.h>

/************************************************Defines: *************************************************/
/*sectors in STM32 Memory */
#define FLASH_Sector_0      0x00000000
#define FLASH_Sector_1      0x00000001
#define FLASH_Sector_2      0x00000002
#define FLASH_Sector_3      0x00000003
#define FLASH_Sector_4      0x00000004
#define FLASH_Sector_5      0x00000005
#define FLASH_Sector_6      0x00000006
#define FLASH_Sector_7      0x00000007

/************************************************APIs: *************************************************/
/**
 * @brief Function to unlock the flash for write operations
 * 
 * This function is used to unlock the flash memory so that write operations can be performed on it.
 * Before performing any write operations on the flash memory, this function should be called to unlock it.
 * 
 * @note This function should be called before any write operations on the flash memory.
 */
void FLASH_unlock(void);

/**
 * @brief Function to lock the flash after write operations
 * 
 * This function is used to lock the flash memory after write operations have been performed on it.
 * Once the flash memory is locked, no further write operations can be performed until it is unlocked again.
 * 
 * @note This function should be called after all write operations on the flash memory have been completed.
 */
void FLASH_lock(void);

/**
 * @brief Function to erase a specific flash sector
 * 
 * This function is used to erase a specific sector of the flash memory.
 * The sector to be erased is specified by the sector number.
 * 
 * @param sector The sector number to be erased
 * @return ErrorStatus_t Returns SUCCESS if the sector is successfully erased, otherwise returns ERROR
 */
ErrorStatus_t FLASH_eraseSector(uint8_t sector);

/**
 * @brief Function to erase all flash sectors
 * 
 * This function is used to erase all sectors of the flash memory.
 * 
 * @return ErrorStatus_t Returns SUCCESS if all sectors are successfully erased, otherwise returns ERROR
 */
ErrorStatus_t FLASH_eraseAllSectors(void);


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
ErrorStatus_t FLASH_programWord(uint32_t address, uint32_t data);

/**
 * @brief Function to read a word from flash memory
 * 
 * This function is used to read a 32-bit word from the flash memory at the specified address.
 * The address from where the word will be read is specified by the 'address' parameter.
 * 
 * @param address The address in flash memory from where the word will be read
 * @return uint32_t The 32-bit word read from flash memory
 */
uint32_t FLASH_readWord(uint32_t address);

/**
 * @brief Function to read a byte from flash memory
 * 
 * This function is used to read a byte from the flash memory at the specified address.
 * The address from where the byte will be read is specified by the 'address' parameter.
 * 
 * @param address The address in flash memory from where the byte will be read
 * @return uint8_t The byte read from flash memory
 */
uint8_t FLASH_readByte(uint32_t address);

#endif