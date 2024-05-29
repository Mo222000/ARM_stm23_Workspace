/*
 * Flash Module Organization for STM32F401xB/C and STM32F401xD/E
 */

// Main Memory
// Sector 0: 0x0800 0000 - 0x0800 3FFF (16 Kbytes)
// Sector 1: 0x0800 4000 - 0x0800 7FFF (16 Kbytes)
// Sector 2: 0x0800 8000 - 0x0800 BFFF (16 Kbytes)
// Sector 3: 0x0800 C000 - 0x0800 FFFF (16 Kbytes)
// Sector 4: 0x0801 0000 - 0x0801 FFFF (64 Kbytes)
// Sector 5: 0x0802 0000 - 0x0803 FFFF (128 Kbytes)
// Sector 6: 0x0804 0000 - 0x0805 FFFF (128 Kbytes)
// Sector 7: 0x0806 0000 - 0x0807 FFFF (128 Kbytes)

// System Memory
// 0x1FFF 0000 - 0x1FFF 77FF (30 Kbytes)

// OTP Area (One-Time Programmable)
// 0x1FFF 7800 - 0x1FFF 7A0F (528 bytes)

// Option Bytes
// 0x1FFF C000 - 0x1FFF C00F (16 bytes)
