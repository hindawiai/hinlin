<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित	__RTL871X_RF_H_
#घोषणा __RTL871X_RF_H_

#समावेश "rtl871x_cmd.h"
#समावेश "rtl871x_mp_phy_regdef.h"

#घोषणा OFDM_PHY		1
#घोषणा MIXED_PHY		2
#घोषणा CCK_PHY		3
#घोषणा NumRates	(13)
#घोषणा RTL8711_RF_MAX_SENS 6
#घोषणा RTL8711_RF_DEF_SENS 4
#घोषणा NUM_CHANNELS	15

काष्ठा	regulatory_class अणु
	u32	starting_freq;		/*MHz, */
	u8	channel_set[NUM_CHANNELS];
	u8	channel_cck_घातer[NUM_CHANNELS]; /*dbm*/
	u8	channel_ofdm_घातer[NUM_CHANNELS];/*dbm*/
	u8	txघातer_limit;		/*dbm*/
	u8	channel_spacing;	/*MHz*/
	u8	modem;
पूर्ण;

क्रमागत	_REG_PREAMBLE_MODE अणु
	PREAMBLE_LONG	= 1,
	PREAMBLE_AUTO	= 2,
	PREAMBLE_SHORT	= 3,
पूर्ण;

क्रमागत अणु
	RTL8712_RFC_1T = 0x10,
	RTL8712_RFC_2T = 0x20,
	RTL8712_RFC_1R = 0x01,
	RTL8712_RFC_2R = 0x02,
	RTL8712_RFC_1T1R = 0x11,
	RTL8712_RFC_1T2R = 0x12,
	RTL8712_RFC_TURBO = 0x92,
	RTL8712_RFC_2T2R = 0x22
पूर्ण;

#पूर्ण_अगर /*__RTL871X_RF_H_*/
