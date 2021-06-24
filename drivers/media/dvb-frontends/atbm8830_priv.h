<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *    Support क्रम AltoBeam GB20600 (a.k.a DMB-TH) demodulator
 *    ATBM8830, ATBM8831
 *
 *    Copyright (C) 2009 David T.L. Wong <davidtlwong@gmail.com>
 */

#अगर_अघोषित __ATBM8830_PRIV_H
#घोषणा __ATBM8830_PRIV_H

काष्ठा atbm_state अणु
	काष्ठा i2c_adapter *i2c;
	/* configuration settings */
	स्थिर काष्ठा atbm8830_config *config;
	काष्ठा dvb_frontend frontend;
पूर्ण;

#घोषणा REG_CHIP_ID	0x0000
#घोषणा REG_TUNER_BASEBAND	0x0001
#घोषणा REG_DEMOD_RUN	0x0004
#घोषणा REG_DSP_RESET	0x0005
#घोषणा REG_RAM_RESET	0x0006
#घोषणा REG_ADC_RESET	0x0007
#घोषणा REG_TSPORT_RESET	0x0008
#घोषणा REG_BLKERR_POL	0x000C
#घोषणा REG_I2C_GATE	0x0103
#घोषणा REG_TS_SAMPLE_EDGE	0x0301
#घोषणा REG_TS_PKT_LEN_204	0x0302
#घोषणा REG_TS_PKT_LEN_AUTO	0x0303
#घोषणा REG_TS_SERIAL	0x0305
#घोषणा REG_TS_CLK_FREERUN	0x0306
#घोषणा REG_TS_VALID_MODE	0x0307
#घोषणा REG_TS_CLK_MODE	0x030B /* 1 क्रम serial, 0 क्रम parallel */

#घोषणा REG_TS_ERRBIT_USE	0x030C
#घोषणा REG_LOCK_STATUS	0x030D
#घोषणा REG_ADC_CONFIG	0x0602
#घोषणा REG_CARRIER_OFFSET	0x0827 /* 0x0827-0x0829 little endian */
#घोषणा REG_DETECTED_PN_MODE	0x082D
#घोषणा REG_READ_LATCH	0x084D
#घोषणा REG_IF_FREQ	0x0A00 /* 0x0A00-0x0A02 little endian */
#घोषणा REG_OSC_CLK	0x0A03 /* 0x0A03-0x0A05 little endian */
#घोषणा REG_BYPASS_CCI	0x0A06
#घोषणा REG_ANALOG_LUMA_DETECTED	0x0A25
#घोषणा REG_ANALOG_AUDIO_DETECTED	0x0A26
#घोषणा REG_ANALOG_CHROMA_DETECTED	0x0A39
#घोषणा REG_FRAME_ERR_CNT	0x0B04
#घोषणा REG_USE_EXT_ADC	0x0C00
#घोषणा REG_SWAP_I_Q	0x0C01
#घोषणा REG_TPS_MANUAL	0x0D01
#घोषणा REG_TPS_CONFIG	0x0D02
#घोषणा REG_BYPASS_DEINTERLEAVER	0x0E00
#घोषणा REG_AGC_TARGET	0x1003 /* 0x1003-0x1005 little endian */
#घोषणा REG_AGC_MIN	0x1020
#घोषणा REG_AGC_MAX	0x1023
#घोषणा REG_AGC_LOCK	0x1027
#घोषणा REG_AGC_PWM_VAL	0x1028 /* 0x1028-0x1029 little endian */
#घोषणा REG_AGC_HOLD_LOOP	0x1031

#पूर्ण_अगर

