<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NXP TDA18218HN silicon tuner driver
 *
 * Copyright (C) 2010 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित TDA18218_PRIV_H
#घोषणा TDA18218_PRIV_H

#समावेश "tda18218.h"

#घोषणा R00_ID         0x00	/* ID byte */
#घोषणा R01_R1         0x01	/* Read byte 1 */
#घोषणा R02_R2         0x02	/* Read byte 2 */
#घोषणा R03_R3         0x03	/* Read byte 3 */
#घोषणा R04_R4         0x04	/* Read byte 4 */
#घोषणा R05_R5         0x05	/* Read byte 5 */
#घोषणा R06_R6         0x06	/* Read byte 6 */
#घोषणा R07_MD1        0x07	/* Main भागider byte 1 */
#घोषणा R08_PSM1       0x08	/* PSM byte 1 */
#घोषणा R09_MD2        0x09	/* Main भागider byte 2 */
#घोषणा R0A_MD3        0x0a	/* Main भागider byte 1 */
#घोषणा R0B_MD4        0x0b	/* Main भागider byte 4 */
#घोषणा R0C_MD5        0x0c	/* Main भागider byte 5 */
#घोषणा R0D_MD6        0x0d	/* Main भागider byte 6 */
#घोषणा R0E_MD7        0x0e	/* Main भागider byte 7 */
#घोषणा R0F_MD8        0x0f	/* Main भागider byte 8 */
#घोषणा R10_CD1        0x10	/* Call भागider byte 1 */
#घोषणा R11_CD2        0x11	/* Call भागider byte 2 */
#घोषणा R12_CD3        0x12	/* Call भागider byte 3 */
#घोषणा R13_CD4        0x13	/* Call भागider byte 4 */
#घोषणा R14_CD5        0x14	/* Call भागider byte 5 */
#घोषणा R15_CD6        0x15	/* Call भागider byte 6 */
#घोषणा R16_CD7        0x16	/* Call भागider byte 7 */
#घोषणा R17_PD1        0x17	/* Power-करोwn byte 1 */
#घोषणा R18_PD2        0x18	/* Power-करोwn byte 2 */
#घोषणा R19_XTOUT      0x19	/* XTOUT byte */
#घोषणा R1A_IF1        0x1a	/* IF byte 1 */
#घोषणा R1B_IF2        0x1b	/* IF byte 2 */
#घोषणा R1C_AGC2B      0x1c	/* AGC2b byte */
#घोषणा R1D_PSM2       0x1d	/* PSM byte 2 */
#घोषणा R1E_PSM3       0x1e	/* PSM byte 3 */
#घोषणा R1F_PSM4       0x1f	/* PSM byte 4 */
#घोषणा R20_AGC11      0x20	/* AGC1 byte 1 */
#घोषणा R21_AGC12      0x21	/* AGC1 byte 2 */
#घोषणा R22_AGC13      0x22	/* AGC1 byte 3 */
#घोषणा R23_AGC21      0x23	/* AGC2 byte 1 */
#घोषणा R24_AGC22      0x24	/* AGC2 byte 2 */
#घोषणा R25_AAGC       0x25	/* Analog AGC byte */
#घोषणा R26_RC         0x26	/* RC byte */
#घोषणा R27_RSSI       0x27	/* RSSI byte */
#घोषणा R28_IRCAL1     0x28	/* IR CAL byte 1 */
#घोषणा R29_IRCAL2     0x29	/* IR CAL byte 2 */
#घोषणा R2A_IRCAL3     0x2a	/* IR CAL byte 3 */
#घोषणा R2B_IRCAL4     0x2b	/* IR CAL byte 4 */
#घोषणा R2C_RFCAL1     0x2c	/* RF CAL byte 1 */
#घोषणा R2D_RFCAL2     0x2d	/* RF CAL byte 2 */
#घोषणा R2E_RFCAL3     0x2e	/* RF CAL byte 3 */
#घोषणा R2F_RFCAL4     0x2f	/* RF CAL byte 4 */
#घोषणा R30_RFCAL5     0x30	/* RF CAL byte 5 */
#घोषणा R31_RFCAL6     0x31	/* RF CAL byte 6 */
#घोषणा R32_RFCAL7     0x32	/* RF CAL byte 7 */
#घोषणा R33_RFCAL8     0x33	/* RF CAL byte 8 */
#घोषणा R34_RFCAL9     0x34	/* RF CAL byte 9 */
#घोषणा R35_RFCAL10    0x35	/* RF CAL byte 10 */
#घोषणा R36_RFCALRAM1  0x36	/* RF CAL RAM byte 1 */
#घोषणा R37_RFCALRAM2  0x37	/* RF CAL RAM byte 2 */
#घोषणा R38_MARGIN     0x38	/* Margin byte */
#घोषणा R39_FMAX1      0x39	/* Fmax byte 1 */
#घोषणा R3A_FMAX2      0x3a	/* Fmax byte 2 */

#घोषणा TDA18218_NUM_REGS 59

काष्ठा tda18218_priv अणु
	काष्ठा tda18218_config *cfg;
	काष्ठा i2c_adapter *i2c;

	u32 अगर_frequency;

	u8 regs[TDA18218_NUM_REGS];
पूर्ण;

#पूर्ण_अगर
