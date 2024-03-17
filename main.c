// @File		MAIN.C		 		
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
#include "utils.h"
#include "mcp4242.h"

void main(void)
{
    __delay_ms(500);   
    
    Pic18f2520_init();

    MCP4242_Init();
    
    MCP4242_Write(MCP4242_VOLATILE_TCON_REGISTER, 0xFF);
    
    MCP4242_Write(MCP4242_VOLATILE_WIPER_1, 0);
    
    while(1);
    
    return;
}
