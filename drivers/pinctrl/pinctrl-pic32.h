<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * PIC32 pinctrl driver
 *
 * Joshua Henderson, <joshua.henderson@microchip.com>
 * Copyright (C) 2015 Microchip Technology Inc.  All rights reserved.
 */
#अगर_अघोषित PINCTRL_PINCTRL_PIC32_H
#घोषणा PINCTRL_PINCTRL_PIC32_H

/* PORT Registers */
#घोषणा ANSEL_REG	0x00
#घोषणा TRIS_REG	0x10
#घोषणा PORT_REG	0x20
#घोषणा LAT_REG		0x30
#घोषणा ODCU_REG	0x40
#घोषणा CNPU_REG	0x50
#घोषणा CNPD_REG	0x60
#घोषणा CNCON_REG	0x70
#घोषणा CNEN_REG	0x80
#घोषणा CNSTAT_REG	0x90
#घोषणा CNNE_REG	0xA0
#घोषणा CNF_REG		0xB0

/* Input PPS Registers */
#घोषणा INT1R 0x04
#घोषणा INT2R 0x08
#घोषणा INT3R 0x0C
#घोषणा INT4R 0x10
#घोषणा T2CKR 0x18
#घोषणा T3CKR 0x1C
#घोषणा T4CKR 0x20
#घोषणा T5CKR 0x24
#घोषणा T6CKR 0x28
#घोषणा T7CKR 0x2C
#घोषणा T8CKR 0x30
#घोषणा T9CKR 0x34
#घोषणा IC1R 0x38
#घोषणा IC2R 0x3C
#घोषणा IC3R 0x40
#घोषणा IC4R 0x44
#घोषणा IC5R 0x48
#घोषणा IC6R 0x4C
#घोषणा IC7R 0x50
#घोषणा IC8R 0x54
#घोषणा IC9R 0x58
#घोषणा OCFAR 0x60
#घोषणा U1RXR 0x68
#घोषणा U1CTSR 0x6C
#घोषणा U2RXR 0x70
#घोषणा U2CTSR 0x74
#घोषणा U3RXR 0x78
#घोषणा U3CTSR 0x7C
#घोषणा U4RXR 0x80
#घोषणा U4CTSR 0x84
#घोषणा U5RXR 0x88
#घोषणा U5CTSR 0x8C
#घोषणा U6RXR 0x90
#घोषणा U6CTSR 0x94
#घोषणा SDI1R 0x9C
#घोषणा SS1INR 0xA0
#घोषणा SDI2R 0xA8
#घोषणा SS2INR 0xAC
#घोषणा SDI3R 0xB4
#घोषणा SS3INR 0xB8
#घोषणा SDI4R 0xC0
#घोषणा SS4INR 0xC4
#घोषणा SDI5R 0xCC
#घोषणा SS5INR 0xD0
#घोषणा SDI6R 0xD8
#घोषणा SS6INR 0xDC
#घोषणा C1RXR 0xE0
#घोषणा C2RXR 0xE4
#घोषणा REFCLKI1R 0xE8
#घोषणा REFCLKI3R 0xF0
#घोषणा REFCLKI4R 0xF4

/* Output PPS Registers */
#घोषणा RPA14R 0x138
#घोषणा RPA15R 0x13C
#घोषणा RPB0R 0x140
#घोषणा RPB1R 0x144
#घोषणा RPB2R 0x148
#घोषणा RPB3R 0x14C
#घोषणा RPB5R 0x154
#घोषणा RPB6R 0x158
#घोषणा RPB7R 0x15C
#घोषणा RPB8R 0x160
#घोषणा RPB9R 0x164
#घोषणा RPB10R 0x168
#घोषणा RPB14R 0x178
#घोषणा RPB15R 0x17C
#घोषणा RPC1R 0x184
#घोषणा RPC2R 0x188
#घोषणा RPC3R 0x18C
#घोषणा RPC4R 0x190
#घोषणा RPC13R 0x1B4
#घोषणा RPC14R 0x1B8
#घोषणा RPD0R 0x1C0
#घोषणा RPD1R 0x1C4
#घोषणा RPD2R 0x1C8
#घोषणा RPD3R 0x1CC
#घोषणा RPD4R 0x1D0
#घोषणा RPD5R 0x1D4
#घोषणा RPD6R 0x1D8
#घोषणा RPD7R 0x1DC
#घोषणा RPD9R 0x1E4
#घोषणा RPD10R 0x1E8
#घोषणा RPD11R 0x1EC
#घोषणा RPD12R 0x1F0
#घोषणा RPD14R 0x1F8
#घोषणा RPD15R 0x1FC
#घोषणा RPE3R 0x20C
#घोषणा RPE5R 0x214
#घोषणा RPE8R 0x220
#घोषणा RPE9R 0x224
#घोषणा RPF0R 0x240
#घोषणा RPF1R 0x244
#घोषणा RPF2R 0x248
#घोषणा RPF3R 0x24C
#घोषणा RPF4R 0x250
#घोषणा RPF5R 0x254
#घोषणा RPF8R 0x260
#घोषणा RPF12R 0x270
#घोषणा RPF13R 0x274
#घोषणा RPG0R 0x280
#घोषणा RPG1R 0x284
#घोषणा RPG6R 0x298
#घोषणा RPG7R 0x29C
#घोषणा RPG8R 0x2A0
#घोषणा RPG9R 0x2A4

#पूर्ण_अगर  /* PINCTRL_PINCTRL_PIC32_H */
