<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित	__RTW_RF_H_
#घोषणा __RTW_RF_H_

#समावेश <rtw_cmd.h>

#घोषणा OFDM_PHY		1
#घोषणा MIXED_PHY		2
#घोषणा CCK_PHY		3

#घोषणा NumRates	(13)

/*  slot समय क्रम 11g */
#घोषणा SHORT_SLOT_TIME			9
#घोषणा NON_SHORT_SLOT_TIME		20

/*  We now define the following channels as the max channels in each
 * channel plan.
 */
/*  2G, total 14 chnls */
/*  अणु1,2,3,4,5,6,7,8,9,10,11,12,13,14पूर्ण */
#घोषणा	MAX_CHANNEL_NUM_2G		14
#घोषणा	MAX_CHANNEL_NUM			14	/* 2.4 GHz only */

/* Country codes */
#घोषणा USA				0x555320
#घोषणा EUROPE				0x1 /* temp, should be provided later */
#घोषणा JAPAN				0x2 /* temp, should be provided later */

काष्ठा	regulatory_class अणु
	u32	starting_freq;				/* MHz, */
	u8	channel_set[MAX_CHANNEL_NUM];
	u8	channel_cck_घातer[MAX_CHANNEL_NUM];	/* dbm */
	u8	channel_ofdm_घातer[MAX_CHANNEL_NUM];	/* dbm */
	u8	txघातer_limit;				/* dbm */
	u8	channel_spacing;			/* MHz */
	u8	modem;
पूर्ण;

क्रमागत capability अणु
	cESS		= 0x0001,
	cIBSS		= 0x0002,
	cPollable	= 0x0004,
	cPollReq	= 0x0008,
	cPrivacy	= 0x0010,
	cShortPreamble	= 0x0020,
	cPBCC		= 0x0040,
	cChannelAgility	= 0x0080,
	cSpectrumMgnt	= 0x0100,
	cQos		= 0x0200,	/* For HCCA, use with CF-Pollable
					 * and CF-PollReq
					 */
	cShortSlotTime	= 0x0400,
	cAPSD		= 0x0800,
	cRM		= 0x1000,	/*  RRM (Radio Request Measurement) */
	cDSSS_OFDM	= 0x2000,
	cDelayedBA	= 0x4000,
	cImmediateBA	= 0x8000,
पूर्ण;

क्रमागत	_REG_PREAMBLE_MODE अणु
	PREAMBLE_LONG	= 1,
	PREAMBLE_AUTO	= 2,
	PREAMBLE_SHORT	= 3,
पूर्ण;

क्रमागत rf90_radio_path अणु
	RF90_PATH_A = 0,		/* Radio Path A */
	RF90_PATH_B = 1,		/* Radio Path B */
	RF90_PATH_C = 2,		/* Radio Path C */
	RF90_PATH_D = 3			/* Radio Path D */
पूर्ण;

/*  Bandwidth Offset */
#घोषणा HAL_PRIME_CHNL_OFFSET_DONT_CARE	0
#घोषणा HAL_PRIME_CHNL_OFFSET_LOWER	1
#घोषणा HAL_PRIME_CHNL_OFFSET_UPPER	2

/*  Represent Channel Width in HT Capabilities */
/*  */
क्रमागत ht_channel_width अणु
	HT_CHANNEL_WIDTH_20 = 0,
	HT_CHANNEL_WIDTH_40 = 1,
	HT_CHANNEL_WIDTH_80 = 2,
	HT_CHANNEL_WIDTH_160 = 3,
	HT_CHANNEL_WIDTH_10 = 4,
पूर्ण;

/*  */
/*  Represent Extension Channel Offset in HT Capabilities */
/*  This is available only in 40Mhz mode. */
/*  */
क्रमागत ht_extchnl_offset अणु
	HT_EXTCHNL_OFFSET_NO_EXT = 0,
	HT_EXTCHNL_OFFSET_UPPER = 1,
	HT_EXTCHNL_OFFSET_NO_DEF = 2,
	HT_EXTCHNL_OFFSET_LOWER = 3,
पूर्ण;

/* 2007/11/15 MH Define dअगरferent RF type. */
क्रमागत rt_rf_type_def अणु
	RF_1T2R = 0,
	RF_2T4R = 1,
	RF_2T2R = 2,
	RF_1T1R = 3,
	RF_2T2R_GREEN = 4,
	RF_819X_MAX_TYPE = 5,
पूर्ण;

u32 rtw_ch2freq(u32 ch);

#पूर्ण_अगर /* _RTL8711_RF_H_ */
