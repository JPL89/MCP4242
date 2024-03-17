// @File		MCP4242.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		17/03/24
//
//
// Copyright (C) 2024 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//

#ifndef MCP4242_H
#define MCP4242_H

#define MCP4242_SCK PORTCbits.RC0
#define MCP4242_DIN PORTCbits.RC1
#define MCP4242_SDO PORTCbits.RC2
#define MCP4242_CS PORTCbits.RC3

#define MCP4242_SCK_TRIS TRISCbits.RC0
#define MCP4242_DIN_TRIS TRISCbits.RC1
#define MCP4242_SDO_TRIS TRISCbits.RC2
#define MCP4242_CS_TRIS TRISCbits.RC3

// MEMORY MAP
#define MCP4242_VOLATILE_WIPER_0 0x00
#define MCP4242_VOLATILE_WIPER_1 0x10
#define MCP4242_NON_VOLATILE_WIPER_0 0x20
#define MCP4242_NON_VOLATILE_WIPER_1 0x30
#define MCP4242_VOLATILE_TCON_REGISTER 0x40
#define MCP4242_STATUS_REGISTER 0x50

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
unsigned char  SPI_transfer(unsigned int data)
{     
    unsigned char byte = 0x00;
    
    for(unsigned int mask = 0x80; mask; mask >>= 1)
    {
        if(data & mask) MCP4242_DIN = 1; else MCP4242_DIN = 0;
            
         __asm__ __volatile__("nop");
         MCP4242_SCK = 1;
         __asm__ __volatile__("nop");
         MCP4242_SCK = 0;
         __asm__ __volatile__("nop");  
         
         byte <<= 1;
         if(MCP4242_SDO) byte |= 0x01;
    }
    
    return ((unsigned char) byte);
}

unsigned char MCP4242_Read(unsigned char cmd)
{
    unsigned char byte = 0x00;
    
    MCP4242_CS = 0;
    SPI_transfer(0x0C);
    byte = SPI_transfer(0xFF);
    MCP4242_CS = 1;
    
    return ((unsigned char) byte);
}

void MCP4242_Write(unsigned char cmd, unsigned char value)
{
    // SPI MODE: 0,0
    // DATA IS CLOCKED IN ON THE SDIN THE RISING EDGE OF SCK AND
    // CLOCKED OUT ON SDO PIN ON THE FAALING EDGE OF SCK
    MCP4242_DIN = 0;
    MCP4242_SCK = 0;
    
    MCP4242_CS = 0;
    SPI_transfer(cmd);
    SPI_transfer(value);
    MCP4242_CS = 1;
}

void MCP4242_Increment(void)
{
    MCP4242_CS = 0;
    SPI_transfer(0x40);
    MCP4242_CS = 1;    
}

void MCP4242_Decrement(void)
{
    MCP4242_CS = 0;
    SPI_transfer(0x80);
    MCP4242_CS = 1;
}

void MCP4242_Init(void)
{
    MCP4242_SCK_TRIS = 0;
    MCP4242_DIN_TRIS = 0;
    MCP4242_SDO_TRIS = 1;
    MCP4242_CS_TRIS = 0;
    
    MCP4242_CS = 1;
}

#endif 
