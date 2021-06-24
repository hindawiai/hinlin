<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * 1-Wire implementation क्रम the ds2780 chip
 *
 * Copyright (C) 2010 Indesign, LLC
 *
 * Author: Clअगरton Barnes <cabarnes@indesign-llc.com>
 *
 * Based on w1-ds2760 driver
 */

#अगर_अघोषित _W1_DS2780_H
#घोषणा _W1_DS2780_H

/* Function commands */
#घोषणा W1_DS2780_READ_DATA		0x69
#घोषणा W1_DS2780_WRITE_DATA		0x6C
#घोषणा W1_DS2780_COPY_DATA		0x48
#घोषणा W1_DS2780_RECALL_DATA		0xB8
#घोषणा W1_DS2780_LOCK			0x6A

/* Register map */
/* Register 0x00 Reserved */
#घोषणा DS2780_STATUS_REG		0x01
#घोषणा DS2780_RAAC_MSB_REG		0x02
#घोषणा DS2780_RAAC_LSB_REG		0x03
#घोषणा DS2780_RSAC_MSB_REG		0x04
#घोषणा DS2780_RSAC_LSB_REG		0x05
#घोषणा DS2780_RARC_REG			0x06
#घोषणा DS2780_RSRC_REG			0x07
#घोषणा DS2780_IAVG_MSB_REG		0x08
#घोषणा DS2780_IAVG_LSB_REG		0x09
#घोषणा DS2780_TEMP_MSB_REG		0x0A
#घोषणा DS2780_TEMP_LSB_REG		0x0B
#घोषणा DS2780_VOLT_MSB_REG		0x0C
#घोषणा DS2780_VOLT_LSB_REG		0x0D
#घोषणा DS2780_CURRENT_MSB_REG		0x0E
#घोषणा DS2780_CURRENT_LSB_REG		0x0F
#घोषणा DS2780_ACR_MSB_REG		0x10
#घोषणा DS2780_ACR_LSB_REG		0x11
#घोषणा DS2780_ACRL_MSB_REG		0x12
#घोषणा DS2780_ACRL_LSB_REG		0x13
#घोषणा DS2780_AS_REG			0x14
#घोषणा DS2780_SFR_REG			0x15
#घोषणा DS2780_FULL_MSB_REG		0x16
#घोषणा DS2780_FULL_LSB_REG		0x17
#घोषणा DS2780_AE_MSB_REG		0x18
#घोषणा DS2780_AE_LSB_REG		0x19
#घोषणा DS2780_SE_MSB_REG		0x1A
#घोषणा DS2780_SE_LSB_REG		0x1B
/* Register 0x1C - 0x1E Reserved */
#घोषणा DS2780_EEPROM_REG		0x1F
#घोषणा DS2780_EEPROM_BLOCK0_START	0x20
/* Register 0x20 - 0x2F User EEPROM */
#घोषणा DS2780_EEPROM_BLOCK0_END	0x2F
/* Register 0x30 - 0x5F Reserved */
#घोषणा DS2780_EEPROM_BLOCK1_START	0x60
#घोषणा DS2780_CONTROL_REG		0x60
#घोषणा DS2780_AB_REG			0x61
#घोषणा DS2780_AC_MSB_REG		0x62
#घोषणा DS2780_AC_LSB_REG		0x63
#घोषणा DS2780_VCHG_REG			0x64
#घोषणा DS2780_IMIN_REG			0x65
#घोषणा DS2780_VAE_REG			0x66
#घोषणा DS2780_IAE_REG			0x67
#घोषणा DS2780_AE_40_REG		0x68
#घोषणा DS2780_RSNSP_REG		0x69
#घोषणा DS2780_FULL_40_MSB_REG		0x6A
#घोषणा DS2780_FULL_40_LSB_REG		0x6B
#घोषणा DS2780_FULL_3040_SLOPE_REG	0x6C
#घोषणा DS2780_FULL_2030_SLOPE_REG	0x6D
#घोषणा DS2780_FULL_1020_SLOPE_REG	0x6E
#घोषणा DS2780_FULL_0010_SLOPE_REG	0x6F
#घोषणा DS2780_AE_3040_SLOPE_REG	0x70
#घोषणा DS2780_AE_2030_SLOPE_REG	0x71
#घोषणा DS2780_AE_1020_SLOPE_REG	0x72
#घोषणा DS2780_AE_0010_SLOPE_REG	0x73
#घोषणा DS2780_SE_3040_SLOPE_REG	0x74
#घोषणा DS2780_SE_2030_SLOPE_REG	0x75
#घोषणा DS2780_SE_1020_SLOPE_REG	0x76
#घोषणा DS2780_SE_0010_SLOPE_REG	0x77
#घोषणा DS2780_RSGAIN_MSB_REG		0x78
#घोषणा DS2780_RSGAIN_LSB_REG		0x79
#घोषणा DS2780_RSTC_REG			0x7A
#घोषणा DS2780_FRSGAIN_MSB_REG		0x7B
#घोषणा DS2780_FRSGAIN_LSB_REG		0x7C
#घोषणा DS2780_EEPROM_BLOCK1_END	0x7C
/* Register 0x7D - 0xFF Reserved */

/* Number of valid रेजिस्टर addresses */
#घोषणा DS2780_DATA_SIZE		0x80

/* Status रेजिस्टर bits */
#घोषणा DS2780_STATUS_REG_CHGTF		(1 << 7)
#घोषणा DS2780_STATUS_REG_AEF		(1 << 6)
#घोषणा DS2780_STATUS_REG_SEF		(1 << 5)
#घोषणा DS2780_STATUS_REG_LEARNF	(1 << 4)
/* Bit 3 Reserved */
#घोषणा DS2780_STATUS_REG_UVF		(1 << 2)
#घोषणा DS2780_STATUS_REG_PORF		(1 << 1)
/* Bit 0 Reserved */

/* Control रेजिस्टर bits */
/* Bit 7 Reserved */
#घोषणा DS2780_CONTROL_REG_UVEN		(1 << 6)
#घोषणा DS2780_CONTROL_REG_PMOD		(1 << 5)
#घोषणा DS2780_CONTROL_REG_RNAOP	(1 << 4)
/* Bit 0 - 3 Reserved */

/* Special feature रेजिस्टर bits */
/* Bit 1 - 7 Reserved */
#घोषणा DS2780_SFR_REG_PIOSC		(1 << 0)

/* EEPROM रेजिस्टर bits */
#घोषणा DS2780_EEPROM_REG_EEC		(1 << 7)
#घोषणा DS2780_EEPROM_REG_LOCK		(1 << 6)
/* Bit 2 - 6 Reserved */
#घोषणा DS2780_EEPROM_REG_BL1		(1 << 1)
#घोषणा DS2780_EEPROM_REG_BL0		(1 << 0)

बाह्य पूर्णांक w1_ds2780_io(काष्ठा device *dev, अक्षर *buf, पूर्णांक addr, माप_प्रकार count,
			पूर्णांक io);
बाह्य पूर्णांक w1_ds2780_eeprom_cmd(काष्ठा device *dev, पूर्णांक addr, पूर्णांक cmd);

#पूर्ण_अगर /* !_W1_DS2780_H */
