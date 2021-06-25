<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम Silicon Lअसल SI2165 DVB-C/-T Demodulator
 *
 * Copyright (C) 2013-2017 Matthias Schwarzott <zzam@gentoo.org>
 */

#अगर_अघोषित _DVB_SI2165_PRIV
#घोषणा _DVB_SI2165_PRIV

#घोषणा SI2165_FIRMWARE_REV_D "dvb-demod-si2165.fw"

काष्ठा si2165_config अणु
	/* i2c addr
	 * possible values: 0x64,0x65,0x66,0x67
	 */
	u8 i2c_addr;

	/* बाह्यal घड़ी or XTAL */
	u8 chip_mode;

	/* frequency of बाह्यal घड़ी or xtal in Hz
	 * possible values: 4000000, 16000000, 20000000, 240000000, 27000000
	 */
	u32 ref_freq_hz;

	/* invert the spectrum */
	bool inversion;
पूर्ण;

#घोषणा STATISTICS_PERIOD_PKT_COUNT	30000u
#घोषणा STATISTICS_PERIOD_BIT_COUNT	(STATISTICS_PERIOD_PKT_COUNT * 204 * 8)

#घोषणा REG_CHIP_MODE			0x0000
#घोषणा REG_CHIP_REVCODE		0x0023
#घोषणा REV_CHIP_TYPE			0x0118
#घोषणा REG_CHIP_INIT			0x0050
#घोषणा REG_INIT_DONE			0x0054
#घोषणा REG_START_INIT			0x0096
#घोषणा REG_PLL_DIVL			0x00a0
#घोषणा REG_RST_ALL			0x00c0
#घोषणा REG_LOCK_TIMEOUT		0x00c4
#घोषणा REG_AUTO_RESET			0x00cb
#घोषणा REG_OVERSAMP			0x00e4
#घोषणा REG_IF_FREQ_SHIFT		0x00e8
#घोषणा REG_DVB_STANDARD		0x00ec
#घोषणा REG_DSP_CLOCK			0x0104
#घोषणा REG_ADC_RI8			0x0123
#घोषणा REG_ADC_RI1			0x012a
#घोषणा REG_ADC_RI2			0x012b
#घोषणा REG_ADC_RI3			0x012c
#घोषणा REG_ADC_RI4			0x012d
#घोषणा REG_ADC_RI5			0x012e
#घोषणा REG_ADC_RI6			0x012f
#घोषणा REG_AGC_CRESTF_DBX8		0x0150
#घोषणा REG_AGC_UNFREEZE_THR		0x015b
#घोषणा REG_AGC2_MIN			0x016e
#घोषणा REG_AGC2_KACQ			0x016c
#घोषणा REG_AGC2_KLOC			0x016d
#घोषणा REG_AGC2_OUTPUT			0x0170
#घोषणा REG_AGC2_CLKDIV			0x0171
#घोषणा REG_AGC_IF_TRI			0x018b
#घोषणा REG_AGC_IF_SLR			0x0190
#घोषणा REG_AAF_CRESTF_DBX8		0x01a0
#घोषणा REG_ACI_CRESTF_DBX8		0x01c8
#घोषणा REG_SWEEP_STEP			0x0232
#घोषणा REG_KP_LOCK			0x023a
#घोषणा REG_UNKNOWN_24C			0x024c
#घोषणा REG_CENTRAL_TAP			0x0261
#घोषणा REG_C_N				0x026c
#घोषणा REG_EQ_AUTO_CONTROL		0x0278
#घोषणा REG_UNKNOWN_27C			0x027c
#घोषणा REG_START_SYNCHRO		0x02e0
#घोषणा REG_REQ_CONSTELLATION		0x02f4
#घोषणा REG_T_BANDWIDTH			0x0308
#घोषणा REG_FREQ_SYNC_RANGE		0x030c
#घोषणा REG_IMPULSIVE_NOISE_REM		0x031c
#घोषणा REG_WDOG_AND_BOOT		0x0341
#घोषणा REG_PATCH_VERSION		0x0344
#घोषणा REG_ADDR_JUMP			0x0348
#घोषणा REG_UNKNOWN_350			0x0350
#घोषणा REG_EN_RST_ERROR		0x035c
#घोषणा REG_DCOM_CONTROL_BYTE		0x0364
#घोषणा REG_DCOM_ADDR			0x0368
#घोषणा REG_DCOM_DATA			0x036c
#घोषणा REG_RST_CRC			0x0379
#घोषणा REG_GP_REG0_LSB			0x0384
#घोषणा REG_GP_REG0_MSB			0x0387
#घोषणा REG_CRC				0x037a
#घोषणा REG_CHECK_SIGNAL		0x03a8
#घोषणा REG_CBER_RST			0x0424
#घोषणा REG_CBER_BIT			0x0428
#घोषणा REG_CBER_ERR			0x0430
#घोषणा REG_CBER_AVAIL			0x0434
#घोषणा REG_PS_LOCK			0x0440
#घोषणा REG_UNCOR_CNT			0x0468
#घोषणा REG_BER_RST			0x046c
#घोषणा REG_BER_PKT			0x0470
#घोषणा REG_BER_BIT			0x0478
#घोषणा REG_BER_AVAIL			0x047c
#घोषणा REG_FEC_LOCK			0x04e0
#घोषणा REG_TS_DATA_MODE		0x04e4
#घोषणा REG_TS_CLK_MODE			0x04e5
#घोषणा REG_TS_TRI			0x04ef
#घोषणा REG_TS_SLR			0x04f4
#घोषणा REG_RSSI_ENABLE			0x0641
#घोषणा REG_RSSI_PAD_CTRL		0x0646
#घोषणा REG_TS_PARALLEL_MODE		0x08f8

#पूर्ण_अगर /* _DVB_SI2165_PRIV */
