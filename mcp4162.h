// @File		MCP4162.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		16/03/24
//
//
// Copyright (C) 2024 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//

#ifndef MCP4162_H
#define MCP4162_H

#define MCP4162_SCK PORTCbits.RC0
#define MCP4162_DIN PORTCbits.RC1
#define MCP4162_CS PORTCbits.RC3

#define MCP4162_SCK_TRIS TRISCbits.RC0
#define MCP4162_DIN_TRIS TRISCbits.RC1
#define MCP4162_CS_TRIS TRISCbits.RC3

// MEMORY MAP
#define MCP4162_VOLATILE_WIPER_0 0x00
#define MCP4162_NON_VOLATILE_WIPER_0 0x20
#define MCP4162_NON_VOLATILE_WIPER_1 0x30
#define MCP4162_VOLATILE_TCON_REGISTER 0x40
#define MCP4162_STATUS_REGISTER 0x50

// B15: ADDR
// B14: ADDR
// B13: ADDR
// B12: ADDR
// B11:  C1
// B10:  C0
// B9:  DATA BIT9
// B8:  DATA BIT8
// B7:  DATA BIT7
// B6:  DATA BIT6
// B5:  DATA BIT5
// B4:  DATA BIT4
// B3:  DATA BIT3
// B2:  DATA BIT2
// B1:  DATA BIT1
// B0:  DATA BIT0
void SPI_transfer(unsigned int data)
{     
    for(unsigned int mask = 0x80; mask; mask >>= 1)
    {
        if(data & mask) MCP4162_DIN = 1; else MCP4162_DIN = 0;
            
         __asm__ __volatile__("nop");
         MCP4162_SCK = 1;
         __asm__ __volatile__("nop");
         MCP4162_SCK = 0;
         __asm__ __volatile__("nop");    
    }
}

void MCP4162_Write(unsigned char cmd, unsigned char value)
{
    // SPI MODE: 0,0
    // DATA IS CLOCKED IN ON THE SDIN THE RISING EDGE OF SCK AND
    // CLOCKED OUT ON SDO PIN ON THE FALLING EDGE OF SCK
    MCP4162_DIN = 0;
    MCP4162_SCK = 0;
    
    MCP4162_CS = 0;
    SPI_transfer(cmd);
    SPI_transfer(value);
    MCP4162_CS = 1;
}

void MCP4162_Increment(void)
{
    MCP4162_CS = 0;
    SPI_transfer(0x40);
    MCP4162_CS = 1;    
}

void MCP4162_Decrement(void)
{
    MCP4162_CS = 0;
    SPI_transfer(0x80);
    MCP4162_CS = 1;
}

void MCP4162_Init(void)
{
    MCP4162_SCK_TRIS = 0;
    MCP4162_DIN_TRIS = 0;
    MCP4162_CS_TRIS = 0;
    
    MCP4162_CS = 1;
}

#endif 
