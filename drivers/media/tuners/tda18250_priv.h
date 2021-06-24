<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NXP TDA18250BHN silicon tuner driver
 *
 * Copyright (C) 2017 Olli Salonen <olli.salonen@iki.fi>
 */

#अगर_अघोषित TDA18250_PRIV_H
#घोषणा TDA18250_PRIV_H

#समावेश "tda18250.h"

#घोषणा R00_ID1		0x00	/* ID byte 1 */
#घोषणा R01_ID2		0x01	/* ID byte 2 */
#घोषणा R02_ID3		0x02	/* ID byte 3 */
#घोषणा R03_THERMO1	0x03	/* Thermo byte 1 */
#घोषणा R04_THERMO2	0x04	/* Thermo byte 2 */
#घोषणा R05_POWER1	0x05	/* Power byte 1 */
#घोषणा R06_POWER2	0x06	/* Power byte 2 */
#घोषणा R07_GPIO	0x07	/* GPIO */
#घोषणा R08_IRQ1	0x08	/* IRQ */
#घोषणा R09_IRQ2	0x09	/* IRQ */
#घोषणा R0A_IRQ3	0x0a	/* IRQ */
#घोषणा R0B_IRQ4	0x0b	/* IRQ */
#घोषणा R0C_AGC11	0x0c	/* AGC1 byte 1 */
#घोषणा R0D_AGC12	0x0d	/* AGC1 byte 2 */
#घोषणा R0E_AGC13	0x0e	/* AGC1 byte 3 */
#घोषणा R0F_AGC14	0x0f	/* AGC1 byte 4 */
#घोषणा R10_LT1		0x10	/* LT byte 1 */
#घोषणा R11_LT2		0x11	/* LT byte 2 */
#घोषणा R12_AGC21	0x12	/* AGC2 byte 1 */
#घोषणा R13_AGC22	0x13	/* AGC2 byte 2 */
#घोषणा R14_AGC23	0x14	/* AGC2 byte 3 */
#घोषणा R15_AGC24	0x15	/* AGC2 byte 4 */
#घोषणा R16_AGC25	0x16	/* AGC2 byte 5 */
#घोषणा R17_AGC31	0x17	/* AGC3 byte 1 */
#घोषणा R18_AGC32	0x18	/* AGC3 byte 2 */
#घोषणा R19_AGC33	0x19	/* AGC3 byte 3 */
#घोषणा R1A_AGCK	0x1a
#घोषणा R1B_GAIN1	0x1b
#घोषणा R1C_GAIN2	0x1c
#घोषणा R1D_GAIN3	0x1d
#घोषणा R1E_WI_FI	0x1e	/* Wireless Filter */
#घोषणा R1F_RF_BPF	0x1f	/* RF Band Pass Filter */
#घोषणा R20_IR_MIX	0x20	/* IR Mixer */
#घोषणा R21_IF_AGC	0x21
#घोषणा R22_IF1		0x22	/* IF byte 1 */
#घोषणा R23_IF2		0x23	/* IF byte 2 */
#घोषणा R24_IF3		0x24	/* IF byte 3 */
#घोषणा R25_REF		0x25	/* reference byte */
#घोषणा R26_IF		0x26	/* IF frequency */
#घोषणा R27_RF1		0x27	/* RF frequency byte 1 */
#घोषणा R28_RF2		0x28	/* RF frequency byte 2 */
#घोषणा R29_RF3		0x29	/* RF frequency byte 3 */
#घोषणा R2A_MSM1	0x2a
#घोषणा R2B_MSM2	0x2b
#घोषणा R2C_PS1		0x2c	/* घातer saving mode byte 1 */
#घोषणा R2D_PS2		0x2d	/* घातer saving mode byte 2 */
#घोषणा R2E_PS3		0x2e	/* घातer saving mode byte 3 */
#घोषणा R2F_RSSI1	0x2f
#घोषणा R30_RSSI2	0x30
#घोषणा R31_IRQ_CTRL	0x31
#घोषणा R32_DUMMY	0x32
#घोषणा R33_TEST	0x33
#घोषणा R34_MD1		0x34
#घोषणा R35_SD1		0x35
#घोषणा R36_SD2		0x36
#घोषणा R37_SD3		0x37
#घोषणा R38_SD4		0x38
#घोषणा R39_SD5		0x39
#घोषणा R3A_SD_TEST	0x3a
#घोषणा R3B_REGU	0x3b
#घोषणा R3C_RCCAL1	0x3c
#घोषणा R3D_RCCAL2	0x3d
#घोषणा R3E_IRCAL1	0x3e
#घोषणा R3F_IRCAL2	0x3f
#घोषणा R40_IRCAL3	0x40
#घोषणा R41_IRCAL4	0x41
#घोषणा R42_IRCAL5	0x42
#घोषणा R43_PD1		0x43	/* घातer करोwn byte 1 */
#घोषणा R44_PD2		0x44	/* घातer करोwn byte 2 */
#घोषणा R45_PD		0x45	/* घातer करोwn */
#घोषणा R46_CPUMP	0x46	/* अक्षरge pump */
#घोषणा R47_LNAPOL	0x47	/* LNA polar casc */
#घोषणा R48_SMOOTH1	0x48	/* smooth test byte 1 */
#घोषणा R49_SMOOTH2	0x49	/* smooth test byte 2 */
#घोषणा R4A_SMOOTH3	0x4a	/* smooth test byte 3 */
#घोषणा R4B_XTALOSC1	0x4b
#घोषणा R4C_XTALOSC2	0x4c
#घोषणा R4D_XTALFLX1	0x4d
#घोषणा R4E_XTALFLX2	0x4e
#घोषणा R4F_XTALFLX3	0x4f
#घोषणा R50_XTALFLX4	0x50
#घोषणा R51_XTALFLX5	0x51
#घोषणा R52_IRLOOP0	0x52
#घोषणा R53_IRLOOP1	0x53
#घोषणा R54_IRLOOP2	0x54
#घोषणा R55_IRLOOP3	0x55
#घोषणा R56_IRLOOP4	0x56
#घोषणा R57_PLL_LOG	0x57
#घोषणा R58_AGC2_UP1	0x58
#घोषणा R59_AGC2_UP2	0x59
#घोषणा R5A_H3H5	0x5a
#घोषणा R5B_AGC_AUTO	0x5b
#घोषणा R5C_AGC_DEBUG	0x5c

#घोषणा TDA18250_NUM_REGS 93

#घोषणा TDA18250_POWER_STANDBY 0
#घोषणा TDA18250_POWER_NORMAL 1

#घोषणा TDA18250_IRQ_CAL     0x81
#घोषणा TDA18250_IRQ_HW_INIT 0x82
#घोषणा TDA18250_IRQ_TUNE    0x88

काष्ठा tda18250_dev अणु
	काष्ठा mutex i2c_mutex;
	काष्ठा dvb_frontend *fe;
	काष्ठा i2c_adapter *i2c;
	काष्ठा regmap *regmap;
	u8 xtal_freq;
	/* IF in kHz */
	u16 अगर_dvbt_6;
	u16 अगर_dvbt_7;
	u16 अगर_dvbt_8;
	u16 अगर_dvbc_6;
	u16 अगर_dvbc_8;
	u16 अगर_atsc;
	u16 अगर_frequency;
	bool slave;
	bool loopthrough;
	bool warm;
	u8 regs[TDA18250_NUM_REGS];
पूर्ण;

#पूर्ण_अगर
