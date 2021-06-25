<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * 1-Wire implementation क्रम the ds2780 chip
 *
 * Author: Renata Sayakhova <renata@oktetद_असल.ru>
 *
 * Based on w1-ds2760 driver
 */

#अगर_अघोषित _W1_DS2781_H
#घोषणा _W1_DS2781_H

/* Function commands */
#घोषणा W1_DS2781_READ_DATA		0x69
#घोषणा W1_DS2781_WRITE_DATA		0x6C
#घोषणा W1_DS2781_COPY_DATA		0x48
#घोषणा W1_DS2781_RECALL_DATA		0xB8
#घोषणा W1_DS2781_LOCK			0x6A

/* Register map */
/* Register 0x00 Reserved */
#घोषणा DS2781_STATUS			0x01
#घोषणा DS2781_RAAC_MSB			0x02
#घोषणा DS2781_RAAC_LSB			0x03
#घोषणा DS2781_RSAC_MSB			0x04
#घोषणा DS2781_RSAC_LSB			0x05
#घोषणा DS2781_RARC			0x06
#घोषणा DS2781_RSRC			0x07
#घोषणा DS2781_IAVG_MSB			0x08
#घोषणा DS2781_IAVG_LSB			0x09
#घोषणा DS2781_TEMP_MSB			0x0A
#घोषणा DS2781_TEMP_LSB			0x0B
#घोषणा DS2781_VOLT_MSB			0x0C
#घोषणा DS2781_VOLT_LSB			0x0D
#घोषणा DS2781_CURRENT_MSB		0x0E
#घोषणा DS2781_CURRENT_LSB		0x0F
#घोषणा DS2781_ACR_MSB			0x10
#घोषणा DS2781_ACR_LSB			0x11
#घोषणा DS2781_ACRL_MSB			0x12
#घोषणा DS2781_ACRL_LSB			0x13
#घोषणा DS2781_AS			0x14
#घोषणा DS2781_SFR			0x15
#घोषणा DS2781_FULL_MSB			0x16
#घोषणा DS2781_FULL_LSB			0x17
#घोषणा DS2781_AE_MSB			0x18
#घोषणा DS2781_AE_LSB			0x19
#घोषणा DS2781_SE_MSB			0x1A
#घोषणा DS2781_SE_LSB			0x1B
/* Register 0x1C - 0x1E Reserved */
#घोषणा DS2781_EEPROM		0x1F
#घोषणा DS2781_EEPROM_BLOCK0_START	0x20
/* Register 0x20 - 0x2F User EEPROM */
#घोषणा DS2781_EEPROM_BLOCK0_END	0x2F
/* Register 0x30 - 0x5F Reserved */
#घोषणा DS2781_EEPROM_BLOCK1_START	0x60
#घोषणा DS2781_CONTROL			0x60
#घोषणा DS2781_AB			0x61
#घोषणा DS2781_AC_MSB			0x62
#घोषणा DS2781_AC_LSB			0x63
#घोषणा DS2781_VCHG			0x64
#घोषणा DS2781_IMIN			0x65
#घोषणा DS2781_VAE			0x66
#घोषणा DS2781_IAE			0x67
#घोषणा DS2781_AE_40			0x68
#घोषणा DS2781_RSNSP			0x69
#घोषणा DS2781_FULL_40_MSB		0x6A
#घोषणा DS2781_FULL_40_LSB		0x6B
#घोषणा DS2781_FULL_4_SLOPE		0x6C
#घोषणा DS2781_FULL_3_SLOPE		0x6D
#घोषणा DS2781_FULL_2_SLOPE		0x6E
#घोषणा DS2781_FULL_1_SLOPE		0x6F
#घोषणा DS2781_AE_4_SLOPE		0x70
#घोषणा DS2781_AE_3_SLOPE		0x71
#घोषणा DS2781_AE_2_SLOPE		0x72
#घोषणा DS2781_AE_1_SLOPE		0x73
#घोषणा DS2781_SE_4_SLOPE		0x74
#घोषणा DS2781_SE_3_SLOPE		0x75
#घोषणा DS2781_SE_2_SLOPE		0x76
#घोषणा DS2781_SE_1_SLOPE		0x77
#घोषणा DS2781_RSGAIN_MSB		0x78
#घोषणा DS2781_RSGAIN_LSB		0x79
#घोषणा DS2781_RSTC			0x7A
#घोषणा DS2781_COB			0x7B
#घोषणा DS2781_TBP34			0x7C
#घोषणा DS2781_TBP23			0x7D
#घोषणा DS2781_TBP12			0x7E
#घोषणा DS2781_EEPROM_BLOCK1_END	0x7F
/* Register 0x7D - 0xFF Reserved */

#घोषणा DS2781_FSGAIN_MSB		0xB0
#घोषणा DS2781_FSGAIN_LSB		0xB1

/* Number of valid रेजिस्टर addresses */
#घोषणा DS2781_DATA_SIZE		0xB2

/* Status रेजिस्टर bits */
#घोषणा DS2781_STATUS_CHGTF		(1 << 7)
#घोषणा DS2781_STATUS_AEF		(1 << 6)
#घोषणा DS2781_STATUS_SEF		(1 << 5)
#घोषणा DS2781_STATUS_LEARNF		(1 << 4)
/* Bit 3 Reserved */
#घोषणा DS2781_STATUS_UVF		(1 << 2)
#घोषणा DS2781_STATUS_PORF		(1 << 1)
/* Bit 0 Reserved */

/* Control रेजिस्टर bits */
/* Bit 7 Reserved */
#घोषणा DS2781_CONTROL_NBEN		(1 << 7)
#घोषणा DS2781_CONTROL_UVEN		(1 << 6)
#घोषणा DS2781_CONTROL_PMOD		(1 << 5)
#घोषणा DS2781_CONTROL_RNAOP		(1 << 4)
#घोषणा DS1781_CONTROL_UVTH		(1 << 3)
/* Bit 0 - 2 Reserved */

/* Special feature रेजिस्टर bits */
/* Bit 1 - 7 Reserved */
#घोषणा DS2781_SFR_PIOSC		(1 << 0)

/* EEPROM रेजिस्टर bits */
#घोषणा DS2781_EEPROM_EEC		(1 << 7)
#घोषणा DS2781_EEPROM_LOCK		(1 << 6)
/* Bit 2 - 6 Reserved */
#घोषणा DS2781_EEPROM_BL1		(1 << 1)
#घोषणा DS2781_EEPROM_BL0		(1 << 0)

बाह्य पूर्णांक w1_ds2781_io(काष्ठा device *dev, अक्षर *buf, पूर्णांक addr, माप_प्रकार count,
			पूर्णांक io);
बाह्य पूर्णांक w1_ds2781_eeprom_cmd(काष्ठा device *dev, पूर्णांक addr, पूर्णांक cmd);

#पूर्ण_अगर /* !_W1_DS2781_H */
