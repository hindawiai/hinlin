<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/linux/mfd/wl1273-core.h
 *
 * Some definitions क्रम the wl1273 radio receiver/transmitter chip.
 *
 * Copyright (C) 2010 Nokia Corporation
 * Author: Matti J. Aaltonen <matti.j.aaltonen@nokia.com>
 */

#अगर_अघोषित WL1273_CORE_H
#घोषणा WL1273_CORE_H

#समावेश <linux/i2c.h>
#समावेश <linux/mfd/core.h>

#घोषणा WL1273_FM_DRIVER_NAME	"wl1273-fm"
#घोषणा RX71_FM_I2C_ADDR	0x22

#घोषणा WL1273_STEREO_GET		0
#घोषणा WL1273_RSSI_LVL_GET		1
#घोषणा WL1273_IF_COUNT_GET		2
#घोषणा WL1273_FLAG_GET			3
#घोषणा WL1273_RDS_SYNC_GET		4
#घोषणा WL1273_RDS_DATA_GET		5
#घोषणा WL1273_FREQ_SET			10
#घोषणा WL1273_AF_FREQ_SET		11
#घोषणा WL1273_MOST_MODE_SET		12
#घोषणा WL1273_MOST_BLEND_SET		13
#घोषणा WL1273_DEMPH_MODE_SET		14
#घोषणा WL1273_SEARCH_LVL_SET		15
#घोषणा WL1273_BAND_SET			16
#घोषणा WL1273_MUTE_STATUS_SET		17
#घोषणा WL1273_RDS_PAUSE_LVL_SET	18
#घोषणा WL1273_RDS_PAUSE_DUR_SET	19
#घोषणा WL1273_RDS_MEM_SET		20
#घोषणा WL1273_RDS_BLK_B_SET		21
#घोषणा WL1273_RDS_MSK_B_SET		22
#घोषणा WL1273_RDS_PI_MASK_SET		23
#घोषणा WL1273_RDS_PI_SET		24
#घोषणा WL1273_RDS_SYSTEM_SET		25
#घोषणा WL1273_INT_MASK_SET		26
#घोषणा WL1273_SEARCH_सूची_SET		27
#घोषणा WL1273_VOLUME_SET		28
#घोषणा WL1273_AUDIO_ENABLE		29
#घोषणा WL1273_PCM_MODE_SET		30
#घोषणा WL1273_I2S_MODE_CONFIG_SET	31
#घोषणा WL1273_POWER_SET		32
#घोषणा WL1273_INTX_CONFIG_SET		33
#घोषणा WL1273_PULL_EN_SET		34
#घोषणा WL1273_HILO_SET			35
#घोषणा WL1273_SWITCH2FREF		36
#घोषणा WL1273_FREQ_DRIFT_REPORT	37

#घोषणा WL1273_PCE_GET			40
#घोषणा WL1273_FIRM_VER_GET		41
#घोषणा WL1273_ASIC_VER_GET		42
#घोषणा WL1273_ASIC_ID_GET		43
#घोषणा WL1273_MAN_ID_GET		44
#घोषणा WL1273_TUNER_MODE_SET		45
#घोषणा WL1273_STOP_SEARCH		46
#घोषणा WL1273_RDS_CNTRL_SET		47

#घोषणा WL1273_WRITE_HARDWARE_REG	100
#घोषणा WL1273_CODE_DOWNLOAD		101
#घोषणा WL1273_RESET			102

#घोषणा WL1273_FM_POWER_MODE		254
#घोषणा WL1273_FM_INTERRUPT		255

/* Transmitter API */

#घोषणा WL1273_CHANL_SET			55
#घोषणा WL1273_SCAN_SPACING_SET			56
#घोषणा WL1273_REF_SET				57
#घोषणा WL1273_POWER_ENB_SET			90
#घोषणा WL1273_POWER_ATT_SET			58
#घोषणा WL1273_POWER_LEV_SET			59
#घोषणा WL1273_AUDIO_DEV_SET			60
#घोषणा WL1273_PILOT_DEV_SET			61
#घोषणा WL1273_RDS_DEV_SET			62
#घोषणा WL1273_PUPD_SET				91
#घोषणा WL1273_AUDIO_IO_SET			63
#घोषणा WL1273_PREMPH_SET			64
#घोषणा WL1273_MONO_SET				66
#घोषणा WL1273_MUTE				92
#घोषणा WL1273_MPX_LMT_ENABLE			67
#घोषणा WL1273_PI_SET				93
#घोषणा WL1273_ECC_SET				69
#घोषणा WL1273_PTY				70
#घोषणा WL1273_AF				71
#घोषणा WL1273_DISPLAY_MODE			74
#घोषणा WL1273_RDS_REP_SET			77
#घोषणा WL1273_RDS_CONFIG_DATA_SET		98
#घोषणा WL1273_RDS_DATA_SET			99
#घोषणा WL1273_RDS_DATA_ENB			94
#घोषणा WL1273_TA_SET				78
#घोषणा WL1273_TP_SET				79
#घोषणा WL1273_DI_SET				80
#घोषणा WL1273_MS_SET				81
#घोषणा WL1273_PS_SCROLL_SPEED			82
#घोषणा WL1273_TX_AUDIO_LEVEL_TEST		96
#घोषणा WL1273_TX_AUDIO_LEVEL_TEST_THRESHOLD	73
#घोषणा WL1273_TX_AUDIO_INPUT_LEVEL_RANGE_SET	54
#घोषणा WL1273_RX_ANTENNA_SELECT		87
#घोषणा WL1273_I2C_DEV_ADDR_SET			86
#घोषणा WL1273_REF_ERR_CALIB_PARAM_SET		88
#घोषणा WL1273_REF_ERR_CALIB_PERIODICITY_SET	89
#घोषणा WL1273_SOC_INT_TRIGGER			52
#घोषणा WL1273_SOC_AUDIO_PATH_SET		83
#घोषणा WL1273_SOC_PCMI_OVERRIDE		84
#घोषणा WL1273_SOC_I2S_OVERRIDE			85
#घोषणा WL1273_RSSI_BLOCK_SCAN_FREQ_SET		95
#घोषणा WL1273_RSSI_BLOCK_SCAN_START		97
#घोषणा WL1273_RSSI_BLOCK_SCAN_DATA_GET		5
#घोषणा WL1273_READ_FMANT_TUNE_VALUE		104

#घोषणा WL1273_RDS_OFF		0
#घोषणा WL1273_RDS_ON		1
#घोषणा WL1273_RDS_RESET	2

#घोषणा WL1273_AUDIO_DIGITAL	0
#घोषणा WL1273_AUDIO_ANALOG	1

#घोषणा WL1273_MODE_RX		BIT(0)
#घोषणा WL1273_MODE_TX		BIT(1)
#घोषणा WL1273_MODE_OFF		BIT(2)
#घोषणा WL1273_MODE_SUSPENDED	BIT(3)

#घोषणा WL1273_RADIO_CHILD	BIT(0)
#घोषणा WL1273_CODEC_CHILD	BIT(1)

#घोषणा WL1273_RX_MONO		1
#घोषणा WL1273_RX_STEREO	0
#घोषणा WL1273_TX_MONO		0
#घोषणा WL1273_TX_STEREO	1

#घोषणा WL1273_MAX_VOLUME	0xffff
#घोषणा WL1273_DEFAULT_VOLUME	0x78b8

/* I2S protocol, left channel first, data width 16 bits */
#घोषणा WL1273_PCM_DEF_MODE		0x00

/* Rx */
#घोषणा WL1273_AUDIO_ENABLE_I2S		BIT(0)
#घोषणा WL1273_AUDIO_ENABLE_ANALOG	BIT(1)

/* Tx */
#घोषणा WL1273_AUDIO_IO_SET_ANALOG	0
#घोषणा WL1273_AUDIO_IO_SET_I2S		1

#घोषणा WL1273_PUPD_SET_OFF		0x00
#घोषणा WL1273_PUPD_SET_ON		0x01
#घोषणा WL1273_PUPD_SET_RETENTION	0x10

/* I2S mode */
#घोषणा WL1273_IS2_WIDTH_32	0x0
#घोषणा WL1273_IS2_WIDTH_40	0x1
#घोषणा WL1273_IS2_WIDTH_22_23	0x2
#घोषणा WL1273_IS2_WIDTH_23_22	0x3
#घोषणा WL1273_IS2_WIDTH_48	0x4
#घोषणा WL1273_IS2_WIDTH_50	0x5
#घोषणा WL1273_IS2_WIDTH_60	0x6
#घोषणा WL1273_IS2_WIDTH_64	0x7
#घोषणा WL1273_IS2_WIDTH_80	0x8
#घोषणा WL1273_IS2_WIDTH_96	0x9
#घोषणा WL1273_IS2_WIDTH_128	0xa
#घोषणा WL1273_IS2_WIDTH	0xf

#घोषणा WL1273_IS2_FORMAT_STD	(0x0 << 4)
#घोषणा WL1273_IS2_FORMAT_LEFT	(0x1 << 4)
#घोषणा WL1273_IS2_FORMAT_RIGHT	(0x2 << 4)
#घोषणा WL1273_IS2_FORMAT_USER	(0x3 << 4)

#घोषणा WL1273_IS2_MASTER	(0x0 << 6)
#घोषणा WL1273_IS2_SLAVEW	(0x1 << 6)

#घोषणा WL1273_IS2_TRI_AFTER_SENDING	(0x0 << 7)
#घोषणा WL1273_IS2_TRI_ALWAYS_ACTIVE	(0x1 << 7)

#घोषणा WL1273_IS2_SDOWS_RR	(0x0 << 8)
#घोषणा WL1273_IS2_SDOWS_RF	(0x1 << 8)
#घोषणा WL1273_IS2_SDOWS_FR	(0x2 << 8)
#घोषणा WL1273_IS2_SDOWS_FF	(0x3 << 8)

#घोषणा WL1273_IS2_TRI_OPT	(0x0 << 10)
#घोषणा WL1273_IS2_TRI_ALWAYS	(0x1 << 10)

#घोषणा WL1273_IS2_RATE_48K	(0x0 << 12)
#घोषणा WL1273_IS2_RATE_44_1K	(0x1 << 12)
#घोषणा WL1273_IS2_RATE_32K	(0x2 << 12)
#घोषणा WL1273_IS2_RATE_22_05K	(0x4 << 12)
#घोषणा WL1273_IS2_RATE_16K	(0x5 << 12)
#घोषणा WL1273_IS2_RATE_12K	(0x8 << 12)
#घोषणा WL1273_IS2_RATE_11_025	(0x9 << 12)
#घोषणा WL1273_IS2_RATE_8K	(0xa << 12)
#घोषणा WL1273_IS2_RATE		(0xf << 12)

#घोषणा WL1273_I2S_DEF_MODE	(WL1273_IS2_WIDTH_32 | \
				 WL1273_IS2_FORMAT_STD | \
				 WL1273_IS2_MASTER | \
				 WL1273_IS2_TRI_AFTER_SENDING | \
				 WL1273_IS2_SDOWS_RR | \
				 WL1273_IS2_TRI_OPT | \
				 WL1273_IS2_RATE_48K)

#घोषणा च_अक्षर_न्यून (-128)
#घोषणा च_अक्षर_उच्च 127

#घोषणा WL1273_FR_EVENT			BIT(0)
#घोषणा WL1273_BL_EVENT			BIT(1)
#घोषणा WL1273_RDS_EVENT		BIT(2)
#घोषणा WL1273_BBLK_EVENT		BIT(3)
#घोषणा WL1273_LSYNC_EVENT		BIT(4)
#घोषणा WL1273_LEV_EVENT		BIT(5)
#घोषणा WL1273_IFFR_EVENT		BIT(6)
#घोषणा WL1273_PI_EVENT			BIT(7)
#घोषणा WL1273_PD_EVENT			BIT(8)
#घोषणा WL1273_STIC_EVENT		BIT(9)
#घोषणा WL1273_MAL_EVENT		BIT(10)
#घोषणा WL1273_POW_ENB_EVENT		BIT(11)
#घोषणा WL1273_SCAN_OVER_EVENT		BIT(12)
#घोषणा WL1273_ERROR_EVENT		BIT(13)

#घोषणा TUNER_MODE_STOP_SEARCH		0
#घोषणा TUNER_MODE_PRESET		1
#घोषणा TUNER_MODE_AUTO_SEEK		2
#घोषणा TUNER_MODE_AF			3
#घोषणा TUNER_MODE_AUTO_SEEK_PI		4
#घोषणा TUNER_MODE_AUTO_SEEK_BULK	5

#घोषणा RDS_BLOCK_SIZE	3

काष्ठा wl1273_fm_platक्रमm_data अणु
	पूर्णांक (*request_resources) (काष्ठा i2c_client *client);
	व्योम (*मुक्त_resources) (व्योम);
	व्योम (*enable) (व्योम);
	व्योम (*disable) (व्योम);

	u8 क्रमbidden_modes;
	अचिन्हित पूर्णांक children;
पूर्ण;

#घोषणा WL1273_FM_CORE_CELLS	2

#घोषणा WL1273_BAND_OTHER	0
#घोषणा WL1273_BAND_JAPAN	1

#घोषणा WL1273_BAND_JAPAN_LOW	76000
#घोषणा WL1273_BAND_JAPAN_HIGH	90000
#घोषणा WL1273_BAND_OTHER_LOW	87500
#घोषणा WL1273_BAND_OTHER_HIGH	108000

#घोषणा WL1273_BAND_TX_LOW	76000
#घोषणा WL1273_BAND_TX_HIGH	108000

काष्ठा wl1273_core अणु
	काष्ठा mfd_cell cells[WL1273_FM_CORE_CELLS];
	काष्ठा wl1273_fm_platक्रमm_data *pdata;

	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक i2s_mode;
	अचिन्हित पूर्णांक volume;
	अचिन्हित पूर्णांक audio_mode;
	अचिन्हित पूर्णांक channel_number;
	काष्ठा mutex lock; /* क्रम serializing fm radio operations */

	काष्ठा i2c_client *client;

	पूर्णांक (*पढ़ो)(काष्ठा wl1273_core *core, u8, u16 *);
	पूर्णांक (*ग_लिखो)(काष्ठा wl1273_core *core, u8, u16);
	पूर्णांक (*ग_लिखो_data)(काष्ठा wl1273_core *core, u8 *, u16);
	पूर्णांक (*set_audio)(काष्ठा wl1273_core *core, अचिन्हित पूर्णांक);
	पूर्णांक (*set_volume)(काष्ठा wl1273_core *core, अचिन्हित पूर्णांक);
पूर्ण;

#पूर्ण_अगर	/* अगरndef WL1273_CORE_H */
