<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the NXP SAA7164 PCIe bridge
 *
 *  Copyright (c) 2010-2015 Steven Toth <stoth@kernelद_असल.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>

#समावेश "saa7164.h"

/* The Bridge API needs to understand रेजिस्टर widths (in bytes) क्रम the
 * attached I2C devices, so we can simplअगरy the भव i2c mechansms
 * and keep the -i2c.c implementation clean.
 */
#घोषणा REGLEN_0bit	0
#घोषणा REGLEN_8bit	1
#घोषणा REGLEN_16bit	2

काष्ठा saa7164_board saa7164_boards[] = अणु
	[SAA7164_BOARD_UNKNOWN] = अणु
		/* Bridge will not load any firmware, without knowing
		 * the rev this would be fatal. */
		.name		= "Unknown",
	पूर्ण,
	[SAA7164_BOARD_UNKNOWN_REV2] = अणु
		/* Bridge will load the v2 f/w and dump descriptors */
		/* Required during new board bringup */
		.name		= "Generic Rev2",
		.chiprev	= SAA7164_CHIP_REV2,
	पूर्ण,
	[SAA7164_BOARD_UNKNOWN_REV3] = अणु
		/* Bridge will load the v2 f/w and dump descriptors */
		/* Required during new board bringup */
		.name		= "Generic Rev3",
		.chiprev	= SAA7164_CHIP_REV3,
	पूर्ण,
	[SAA7164_BOARD_HAUPPAUGE_HVR2200] = अणु
		.name		= "Hauppauge WinTV-HVR2200",
		.porta		= SAA7164_MPEG_DVB,
		.portb		= SAA7164_MPEG_DVB,
		.portc		= SAA7164_MPEG_ENCODER,
		.portd		= SAA7164_MPEG_ENCODER,
		.porte		= SAA7164_MPEG_VBI,
		.portf		= SAA7164_MPEG_VBI,
		.chiprev	= SAA7164_CHIP_REV3,
		.unit		= अणुअणु
			.id		= 0x1d,
			.type		= SAA7164_UNIT_EEPROM,
			.name		= "4K EEPROM",
			.i2c_bus_nr	= SAA7164_I2C_BUS_0,
			.i2c_bus_addr	= 0xa0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "TDA18271-1",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x1b,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "TDA18271-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x1e,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "TDA10048-1",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0x10 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x1f,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "TDA10048-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0x12 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7164_BOARD_HAUPPAUGE_HVR2200_2] = अणु
		.name		= "Hauppauge WinTV-HVR2200",
		.porta		= SAA7164_MPEG_DVB,
		.portb		= SAA7164_MPEG_DVB,
		.portc		= SAA7164_MPEG_ENCODER,
		.portd		= SAA7164_MPEG_ENCODER,
		.porte		= SAA7164_MPEG_VBI,
		.portf		= SAA7164_MPEG_VBI,
		.chiprev	= SAA7164_CHIP_REV2,
		.unit		= अणुअणु
			.id		= 0x06,
			.type		= SAA7164_UNIT_EEPROM,
			.name		= "4K EEPROM",
			.i2c_bus_nr	= SAA7164_I2C_BUS_0,
			.i2c_bus_addr	= 0xa0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "TDA18271-1",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x05,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "TDA10048-1",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0x10 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x1e,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "TDA18271-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x1f,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "TDA10048-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0x12 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7164_BOARD_HAUPPAUGE_HVR2200_3] = अणु
		.name		= "Hauppauge WinTV-HVR2200",
		.porta		= SAA7164_MPEG_DVB,
		.portb		= SAA7164_MPEG_DVB,
		.portc		= SAA7164_MPEG_ENCODER,
		.portd		= SAA7164_MPEG_ENCODER,
		.porte		= SAA7164_MPEG_VBI,
		.portf		= SAA7164_MPEG_VBI,
		.chiprev	= SAA7164_CHIP_REV2,
		.unit		= अणुअणु
			.id		= 0x1d,
			.type		= SAA7164_UNIT_EEPROM,
			.name		= "4K EEPROM",
			.i2c_bus_nr	= SAA7164_I2C_BUS_0,
			.i2c_bus_addr	= 0xa0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "TDA18271-1",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x05,
			.type		= SAA7164_UNIT_ANALOG_DEMODULATOR,
			.name		= "TDA8290-1",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0x84 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x1b,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "TDA18271-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x1c,
			.type		= SAA7164_UNIT_ANALOG_DEMODULATOR,
			.name		= "TDA8290-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0x84 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x1e,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "TDA10048-1",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0x10 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x1f,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "TDA10048-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0x12 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7164_BOARD_HAUPPAUGE_HVR2200_4] = अणु
		.name		= "Hauppauge WinTV-HVR2200",
		.porta		= SAA7164_MPEG_DVB,
		.portb		= SAA7164_MPEG_DVB,
		.portc		= SAA7164_MPEG_ENCODER,
		.portd		= SAA7164_MPEG_ENCODER,
		.porte		= SAA7164_MPEG_VBI,
		.portf		= SAA7164_MPEG_VBI,
		.chiprev	= SAA7164_CHIP_REV3,
		.unit		= अणुअणु
			.id		= 0x1d,
			.type		= SAA7164_UNIT_EEPROM,
			.name		= "4K EEPROM",
			.i2c_bus_nr	= SAA7164_I2C_BUS_0,
			.i2c_bus_addr	= 0xa0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "TDA18271-1",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x05,
			.type		= SAA7164_UNIT_ANALOG_DEMODULATOR,
			.name		= "TDA8290-1",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0x84 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x1b,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "TDA18271-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x1c,
			.type		= SAA7164_UNIT_ANALOG_DEMODULATOR,
			.name		= "TDA8290-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0x84 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x1e,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "TDA10048-1",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0x10 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x1f,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "TDA10048-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0x12 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7164_BOARD_HAUPPAUGE_HVR2250] = अणु
		.name		= "Hauppauge WinTV-HVR2250",
		.porta		= SAA7164_MPEG_DVB,
		.portb		= SAA7164_MPEG_DVB,
		.portc		= SAA7164_MPEG_ENCODER,
		.portd		= SAA7164_MPEG_ENCODER,
		.porte		= SAA7164_MPEG_VBI,
		.portf		= SAA7164_MPEG_VBI,
		.chiprev	= SAA7164_CHIP_REV3,
		.unit		= अणुअणु
			.id		= 0x22,
			.type		= SAA7164_UNIT_EEPROM,
			.name		= "4K EEPROM",
			.i2c_bus_nr	= SAA7164_I2C_BUS_0,
			.i2c_bus_addr	= 0xa0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "TDA18271-1",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x07,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "CX24228/S5H1411-1 (TOP)",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0x32 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x08,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "CX24228/S5H1411-1 (QAM)",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0x34 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x1e,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "TDA18271-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x20,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "CX24228/S5H1411-2 (TOP)",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0x32 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x23,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "CX24228/S5H1411-2 (QAM)",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0x34 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7164_BOARD_HAUPPAUGE_HVR2250_2] = अणु
		.name		= "Hauppauge WinTV-HVR2250",
		.porta		= SAA7164_MPEG_DVB,
		.portb		= SAA7164_MPEG_DVB,
		.portc		= SAA7164_MPEG_ENCODER,
		.portd		= SAA7164_MPEG_ENCODER,
		.porte		= SAA7164_MPEG_VBI,
		.portf		= SAA7164_MPEG_VBI,
		.chiprev	= SAA7164_CHIP_REV3,
		.unit		= अणुअणु
			.id		= 0x28,
			.type		= SAA7164_UNIT_EEPROM,
			.name		= "4K EEPROM",
			.i2c_bus_nr	= SAA7164_I2C_BUS_0,
			.i2c_bus_addr	= 0xa0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "TDA18271-1",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x07,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "CX24228/S5H1411-1 (TOP)",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0x32 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x08,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "CX24228/S5H1411-1 (QAM)",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0x34 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x24,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "TDA18271-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x26,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "CX24228/S5H1411-2 (TOP)",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0x32 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x29,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "CX24228/S5H1411-2 (QAM)",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0x34 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7164_BOARD_HAUPPAUGE_HVR2250_3] = अणु
		.name		= "Hauppauge WinTV-HVR2250",
		.porta		= SAA7164_MPEG_DVB,
		.portb		= SAA7164_MPEG_DVB,
		.portc		= SAA7164_MPEG_ENCODER,
		.portd		= SAA7164_MPEG_ENCODER,
		.porte		= SAA7164_MPEG_VBI,
		.portf		= SAA7164_MPEG_VBI,
		.chiprev	= SAA7164_CHIP_REV3,
		.unit		= अणुअणु
			.id		= 0x26,
			.type		= SAA7164_UNIT_EEPROM,
			.name		= "4K EEPROM",
			.i2c_bus_nr	= SAA7164_I2C_BUS_0,
			.i2c_bus_addr	= 0xa0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "TDA18271-1",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x07,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "CX24228/S5H1411-1 (TOP)",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0x32 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x08,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "CX24228/S5H1411-1 (QAM)",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0x34 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x22,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "TDA18271-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x24,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "CX24228/S5H1411-2 (TOP)",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0x32 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x27,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "CX24228/S5H1411-2 (QAM)",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0x34 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7164_BOARD_HAUPPAUGE_HVR2200_5] = अणु
		.name		= "Hauppauge WinTV-HVR2200",
		.porta		= SAA7164_MPEG_DVB,
		.portb		= SAA7164_MPEG_DVB,
		.chiprev	= SAA7164_CHIP_REV3,
		.unit		= अणुअणु
			.id		= 0x23,
			.type		= SAA7164_UNIT_EEPROM,
			.name		= "4K EEPROM",
			.i2c_bus_nr	= SAA7164_I2C_BUS_0,
			.i2c_bus_addr	= 0xa0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "TDA18271-1",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x05,
			.type		= SAA7164_UNIT_ANALOG_DEMODULATOR,
			.name		= "TDA8290-1",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0x84 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x21,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "TDA18271-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x22,
			.type		= SAA7164_UNIT_ANALOG_DEMODULATOR,
			.name		= "TDA8290-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0x84 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x24,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "TDA10048-1",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0x10 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x25,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "TDA10048-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0x12 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7164_BOARD_HAUPPAUGE_HVR2255proto] = अणु
		.name		= "Hauppauge WinTV-HVR2255(proto)",
		.porta		= SAA7164_MPEG_DVB,
		.portb		= SAA7164_MPEG_DVB,
		.portc		= SAA7164_MPEG_ENCODER,
		.portd		= SAA7164_MPEG_ENCODER,
		.porte		= SAA7164_MPEG_VBI,
		.portf		= SAA7164_MPEG_VBI,
		.chiprev	= SAA7164_CHIP_REV3,
		.unit		= अणुअणु
			.id		= 0x27,
			.type		= SAA7164_UNIT_EEPROM,
			.name		= "4K EEPROM",
			.i2c_bus_nr	= SAA7164_I2C_BUS_0,
			.i2c_bus_addr	= 0xa0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "SI2157-1",
			.i2c_bus_nr	= SAA7164_I2C_BUS_0,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_0bit,
		पूर्ण, अणु
			.id		= 0x06,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "LGDT3306",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0xb2 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x24,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "SI2157-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_0bit,
		पूर्ण, अणु
			.id		= 0x26,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "LGDT3306-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0x1c >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7164_BOARD_HAUPPAUGE_HVR2255] = अणु
		.name		= "Hauppauge WinTV-HVR2255",
		.porta		= SAA7164_MPEG_DVB,
		.portb		= SAA7164_MPEG_DVB,
		.portc		= SAA7164_MPEG_ENCODER,
		.portd		= SAA7164_MPEG_ENCODER,
		.porte		= SAA7164_MPEG_VBI,
		.portf		= SAA7164_MPEG_VBI,
		.chiprev	= SAA7164_CHIP_REV3,
		.unit		= अणुअणु
			.id		= 0x28,
			.type		= SAA7164_UNIT_EEPROM,
			.name		= "4K EEPROM",
			.i2c_bus_nr	= SAA7164_I2C_BUS_0,
			.i2c_bus_addr	= 0xa0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "SI2157-1",
			.i2c_bus_nr	= SAA7164_I2C_BUS_0,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_0bit,
		पूर्ण, अणु
			.id		= 0x06,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "LGDT3306-1",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0xb2 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x25,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "SI2157-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_0bit,
		पूर्ण, अणु
			.id		= 0x27,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "LGDT3306-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0x1c >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7164_BOARD_HAUPPAUGE_HVR2205] = अणु
		.name		= "Hauppauge WinTV-HVR2205",
		.porta		= SAA7164_MPEG_DVB,
		.portb		= SAA7164_MPEG_DVB,
		.portc		= SAA7164_MPEG_ENCODER,
		.portd		= SAA7164_MPEG_ENCODER,
		.porte		= SAA7164_MPEG_VBI,
		.portf		= SAA7164_MPEG_VBI,
		.chiprev	= SAA7164_CHIP_REV3,
		.unit		= अणुअणु
			.id		= 0x28,
			.type		= SAA7164_UNIT_EEPROM,
			.name		= "4K EEPROM",
			.i2c_bus_nr	= SAA7164_I2C_BUS_0,
			.i2c_bus_addr	= 0xa0 >> 1,
			.i2c_reg_len	= REGLEN_8bit,
		पूर्ण, अणु
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "SI2157-1",
			.i2c_bus_nr	= SAA7164_I2C_BUS_0,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_0bit,
		पूर्ण, अणु
			.id		= 0x06,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "SI2168-1",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0xc8 >> 1,
			.i2c_reg_len	= REGLEN_0bit,
		पूर्ण, अणु
			.id		= 0x25,
			.type		= SAA7164_UNIT_TUNER,
			.name		= "SI2157-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_1,
			.i2c_bus_addr	= 0xc0 >> 1,
			.i2c_reg_len	= REGLEN_0bit,
		पूर्ण, अणु
			.id		= 0x27,
			.type		= SAA7164_UNIT_DIGITAL_DEMODULATOR,
			.name		= "SI2168-2",
			.i2c_bus_nr	= SAA7164_I2C_BUS_2,
			.i2c_bus_addr	= 0xcc >> 1,
			.i2c_reg_len	= REGLEN_0bit,
		पूर्ण पूर्ण,
	पूर्ण,
पूर्ण;
स्थिर अचिन्हित पूर्णांक saa7164_bcount = ARRAY_SIZE(saa7164_boards);

/* ------------------------------------------------------------------ */
/* PCI subप्रणाली IDs                                                  */

काष्ठा saa7164_subid saa7164_subids[] = अणु
	अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x8880,
		.card      = SAA7164_BOARD_HAUPPAUGE_HVR2250,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x8810,
		.card      = SAA7164_BOARD_HAUPPAUGE_HVR2250,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x8980,
		.card      = SAA7164_BOARD_HAUPPAUGE_HVR2200,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x8900,
		.card      = SAA7164_BOARD_HAUPPAUGE_HVR2200_2,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x8901,
		.card      = SAA7164_BOARD_HAUPPAUGE_HVR2200_3,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x88A1,
		.card      = SAA7164_BOARD_HAUPPAUGE_HVR2250_3,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x8891,
		.card      = SAA7164_BOARD_HAUPPAUGE_HVR2250_2,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x8851,
		.card      = SAA7164_BOARD_HAUPPAUGE_HVR2250_2,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x8940,
		.card      = SAA7164_BOARD_HAUPPAUGE_HVR2200_4,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x8953,
		.card      = SAA7164_BOARD_HAUPPAUGE_HVR2200_5,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0xf111,
		.card      = SAA7164_BOARD_HAUPPAUGE_HVR2255,
		/* Prototype card left here क्रम करोcumentation purposes.
		.card      = SAA7164_BOARD_HAUPPAUGE_HVR2255proto,
		*/
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0xf123,
		.card      = SAA7164_BOARD_HAUPPAUGE_HVR2205,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0xf120,
		.card      = SAA7164_BOARD_HAUPPAUGE_HVR2205,
	पूर्ण,
पूर्ण;
स्थिर अचिन्हित पूर्णांक saa7164_idcount = ARRAY_SIZE(saa7164_subids);

व्योम saa7164_card_list(काष्ठा saa7164_dev *dev)
अणु
	पूर्णांक i;

	अगर (0 == dev->pci->subप्रणाली_venकरोr &&
	    0 == dev->pci->subप्रणाली_device) अणु
		prपूर्णांकk(KERN_ERR
			"%s: Board has no valid PCIe Subsystem ID and can't\n"
			"%s: be autodetected. Pass card=<n> insmod option to\n"
			"%s: workaround that. Send complaints to the vendor\n"
			"%s: of the TV card. Best regards,\n"
			"%s:         -- tux\n",
			dev->name, dev->name, dev->name, dev->name, dev->name);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR
			"%s: Your board isn't known (yet) to the driver.\n"
			"%s: Try to pick one of the existing card configs via\n"
			"%s: card=<n> insmod option.  Updating to the latest\n"
			"%s: version might help as well.\n",
			dev->name, dev->name, dev->name, dev->name);
	पूर्ण

	prपूर्णांकk(KERN_ERR "%s: Here are valid choices for the card=<n> insmod option:\n",
	       dev->name);

	क्रम (i = 0; i < saa7164_bcount; i++)
		prपूर्णांकk(KERN_ERR "%s:    card=%d -> %s\n",
		       dev->name, i, saa7164_boards[i].name);
पूर्ण

/* TODO: clean this define up पूर्णांकo the -cards.c काष्ठाs */
#घोषणा PCIEBRIDGE_UNITID 2

व्योम saa7164_gpio_setup(काष्ठा saa7164_dev *dev)
अणु
	चयन (dev->board) अणु
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2200:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2200_2:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2200_3:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2200_4:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2200_5:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2250:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2250_2:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2250_3:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2255proto:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2255:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2205:
		/*
		HVR2200 / HVR2250
		GPIO 2: s5h1411 / tda10048-1 demod reset
		GPIO 3: s5h1411 / tda10048-2 demod reset
		GPIO 7: IRBlaster Zilog reset
		 */

		/* HVR2255
		 * GPIO 2: lgdg3306-1 demod reset
		 * GPIO 3: lgdt3306-2 demod reset
		 */

		/* HVR2205
		 * GPIO 2: si2168-1 demod reset
		 * GPIO 3: si2168-2 demod reset
		 */

		/* Reset parts by going in and out of reset */
		saa7164_api_clear_gpiobit(dev, PCIEBRIDGE_UNITID, 2);
		saa7164_api_clear_gpiobit(dev, PCIEBRIDGE_UNITID, 3);

		msleep(20);

		saa7164_api_set_gpiobit(dev, PCIEBRIDGE_UNITID, 2);
		saa7164_api_set_gpiobit(dev, PCIEBRIDGE_UNITID, 3);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम hauppauge_eeprom(काष्ठा saa7164_dev *dev, u8 *eeprom_data)
अणु
	काष्ठा tveeprom tv;

	tveeprom_hauppauge_analog(&tv, eeprom_data);

	/* Make sure we support the board model */
	चयन (tv.model) अणु
	हाल 88001:
		/* Development board - Limit circulation */
		/* WinTV-HVR2250 (PCIe, Retail, full-height bracket)
		 * ATSC/QAM (TDA18271/S5H1411) and basic analog, no IR, FM */
	हाल 88021:
		/* WinTV-HVR2250 (PCIe, Retail, full-height bracket)
		 * ATSC/QAM (TDA18271/S5H1411) and basic analog, MCE CIR, FM */
		अवरोध;
	हाल 88041:
		/* WinTV-HVR2250 (PCIe, Retail, full-height bracket)
		 * ATSC/QAM (TDA18271/S5H1411) and basic analog, no IR, FM */
		अवरोध;
	हाल 88061:
		/* WinTV-HVR2250 (PCIe, Retail, full-height bracket)
		 * ATSC/QAM (TDA18271/S5H1411) and basic analog, FM */
		अवरोध;
	हाल 89519:
	हाल 89609:
		/* WinTV-HVR2200 (PCIe, Retail, full-height)
		 * DVB-T (TDA18271/TDA10048) and basic analog, no IR */
		अवरोध;
	हाल 89619:
		/* WinTV-HVR2200 (PCIe, Retail, half-height)
		 * DVB-T (TDA18271/TDA10048) and basic analog, no IR */
		अवरोध;
	हाल 151009:
		/* First production board rev B2I6 */
		/* WinTV-HVR2205 (PCIe, Retail, full-height bracket)
		 * DVB-T/T2/C (SI2157/SI2168) and basic analog, FM */
		अवरोध;
	हाल 151609:
		/* First production board rev B2I6 */
		/* WinTV-HVR2205 (PCIe, Retail, half-height bracket)
		 * DVB-T/T2/C (SI2157/SI2168) and basic analog, FM */
		अवरोध;
	हाल 151061:
		/* First production board rev B1I6 */
		/* WinTV-HVR2255 (PCIe, Retail, full-height bracket)
		 * ATSC/QAM (SI2157/LGDT3306) and basic analog, FM */
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "%s: Warning: Unknown Hauppauge model #%d\n",
			dev->name, tv.model);
		अवरोध;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s: Hauppauge eeprom: model=%d\n", dev->name,
		tv.model);
पूर्ण

व्योम saa7164_card_setup(काष्ठा saa7164_dev *dev)
अणु
	अटल u8 eeprom[256];

	अगर (dev->i2c_bus[0].i2c_rc == 0) अणु
		अगर (saa7164_api_पढ़ो_eeprom(dev, &eeprom[0],
			माप(eeprom)) < 0)
			वापस;
	पूर्ण

	चयन (dev->board) अणु
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2200:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2200_2:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2200_3:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2200_4:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2200_5:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2250:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2250_2:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2250_3:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2255proto:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2255:
	हाल SAA7164_BOARD_HAUPPAUGE_HVR2205:
		hauppauge_eeprom(dev, &eeprom[0]);
		अवरोध;
	पूर्ण
पूर्ण

/* With most other drivers, the kernel expects to communicate with subdrivers
 * through i2c. This bridge करोes not allow that, it करोes not expose any direct
 * access to I2C. Instead we have to communicate through the device f/w क्रम
 * रेजिस्टर access to 'processing units'. Each unit has a unique
 * id, regardless of how the physical implementation occurs across
 * the three physical i2c buses. The being said अगर we want leverge of
 * the existing kernel drivers क्रम tuners and demods we have to 'speak i2c',
 * to this bridge implements 3 भव i2c buses. This is a helper function
 * क्रम those.
 *
 * Description: Translate the kernels notion of an i2c address and bus पूर्णांकo
 * the appropriate unitid.
 */
पूर्णांक saa7164_i2caddr_to_unitid(काष्ठा saa7164_i2c *bus, पूर्णांक addr)
अणु
	/* For a given bus and i2c device address, वापस the saa7164 unique
	 * unitid. < 0 on error */

	काष्ठा saa7164_dev *dev = bus->dev;
	काष्ठा saa7164_unit *unit;
	पूर्णांक i;

	क्रम (i = 0; i < SAA7164_MAX_UNITS; i++) अणु
		unit = &saa7164_boards[dev->board].unit[i];

		अगर (unit->type == SAA7164_UNIT_UNDEFINED)
			जारी;
		अगर ((bus->nr == unit->i2c_bus_nr) &&
			(addr == unit->i2c_bus_addr))
			वापस unit->id;
	पूर्ण

	वापस -1;
पूर्ण

/* The 7164 API needs to know the i2c रेजिस्टर length in advance.
 * this is a helper function. Based on a specअगरic chip addr and bus वापस the
 * reg length.
 */
पूर्णांक saa7164_i2caddr_to_reglen(काष्ठा saa7164_i2c *bus, पूर्णांक addr)
अणु
	/* For a given bus and i2c device address, वापस the
	 * saa7164 registry address width. < 0 on error
	 */

	काष्ठा saa7164_dev *dev = bus->dev;
	काष्ठा saa7164_unit *unit;
	पूर्णांक i;

	क्रम (i = 0; i < SAA7164_MAX_UNITS; i++) अणु
		unit = &saa7164_boards[dev->board].unit[i];

		अगर (unit->type == SAA7164_UNIT_UNDEFINED)
			जारी;

		अगर ((bus->nr == unit->i2c_bus_nr) &&
			(addr == unit->i2c_bus_addr))
			वापस unit->i2c_reg_len;
	पूर्ण

	वापस -1;
पूर्ण
/* TODO: implement a 'findeeprom' functio like the above and fix any other
 * eeprom related toकरो's in -api.c.
 */

/* Translate a unitid पूर्णांकo a x पढ़ोable device name, क्रम display purposes.  */
अक्षर *saa7164_unitid_name(काष्ठा saa7164_dev *dev, u8 unitid)
अणु
	अक्षर *undefed = "UNDEFINED";
	अक्षर *bridge = "BRIDGE";
	काष्ठा saa7164_unit *unit;
	पूर्णांक i;

	अगर (unitid == 0)
		वापस bridge;

	क्रम (i = 0; i < SAA7164_MAX_UNITS; i++) अणु
		unit = &saa7164_boards[dev->board].unit[i];

		अगर (unit->type == SAA7164_UNIT_UNDEFINED)
			जारी;

		अगर (unitid == unit->id)
				वापस unit->name;
	पूर्ण

	वापस undefed;
पूर्ण

