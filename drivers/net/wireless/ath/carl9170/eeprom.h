<शैली गुरु>
/*
 * Shared Atheros AR9170 Header
 *
 * EEPROM layout
 *
 * Copyright 2008, Johannes Berg <johannes@sipsolutions.net>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; see the file COPYING.  If not, see
 * http://www.gnu.org/licenses/.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *    Copyright (c) 2007-2008 Atheros Communications, Inc.
 *
 *    Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#अगर_अघोषित __CARL9170_SHARED_EEPROM_H
#घोषणा __CARL9170_SHARED_EEPROM_H

#घोषणा AR9170_EEPROM_START		0x1600

#घोषणा AR5416_MAX_CHAINS		2
#घोषणा AR5416_MODAL_SPURS		5

काष्ठा ar9170_eeprom_modal अणु
	__le32	antCtrlChain[AR5416_MAX_CHAINS];
	__le32	antCtrlCommon;
	s8	antennaGainCh[AR5416_MAX_CHAINS];
	u8	चयनSettling;
	u8	txRxAttenCh[AR5416_MAX_CHAINS];
	u8	rxTxMarginCh[AR5416_MAX_CHAINS];
	s8	adcDesiredSize;
	s8	pgaDesiredSize;
	u8	xlnaGainCh[AR5416_MAX_CHAINS];
	u8	txEndToXpaOff;
	u8	txEndToRxOn;
	u8	txFrameToXpaOn;
	u8	thresh62;
	s8	noiseFloorThreshCh[AR5416_MAX_CHAINS];
	u8	xpdGain;
	u8	xpd;
	s8	iqCalICh[AR5416_MAX_CHAINS];
	s8	iqCalQCh[AR5416_MAX_CHAINS];
	u8	pdGainOverlap;
	u8	ob;
	u8	db;
	u8	xpaBiasLvl;
	u8	pwrDecreaseFor2Chain;
	u8	pwrDecreaseFor3Chain;
	u8	txFrameToDataStart;
	u8	txFrameToPaOn;
	u8	ht40PowerIncForPdadc;
	u8	bswAtten[AR5416_MAX_CHAINS];
	u8	bswMargin[AR5416_MAX_CHAINS];
	u8	swSettleHt40;
	u8	reserved[22];
	काष्ठा spur_channel अणु
		__le16 spurChan;
		u8	spurRangeLow;
		u8	spurRangeHigh;
	पूर्ण __packed spur_channels[AR5416_MODAL_SPURS];
पूर्ण __packed;

#घोषणा AR5416_NUM_PD_GAINS		4
#घोषणा AR5416_PD_GAIN_ICEPTS		5

काष्ठा ar9170_calibration_data_per_freq अणु
	u8	pwr_pdg[AR5416_NUM_PD_GAINS][AR5416_PD_GAIN_ICEPTS];
	u8	vpd_pdg[AR5416_NUM_PD_GAINS][AR5416_PD_GAIN_ICEPTS];
पूर्ण __packed;

#घोषणा AR5416_NUM_5G_CAL_PIERS		8
#घोषणा AR5416_NUM_2G_CAL_PIERS		4

#घोषणा AR5416_NUM_5G_TARGET_PWRS	8
#घोषणा AR5416_NUM_2G_CCK_TARGET_PWRS	3
#घोषणा AR5416_NUM_2G_OFDM_TARGET_PWRS	4
#घोषणा AR5416_MAX_NUM_TGT_PWRS		8

काष्ठा ar9170_calibration_target_घातer_legacy अणु
	u8	freq;
	u8	घातer[4];
पूर्ण __packed;

काष्ठा ar9170_calibration_target_घातer_ht अणु
	u8	freq;
	u8	घातer[8];
पूर्ण __packed;

#घोषणा AR5416_NUM_CTLS			24

काष्ठा ar9170_calctl_edges अणु
	u8	channel;
#घोषणा AR9170_CALCTL_EDGE_FLAGS	0xC0
	u8	घातer_flags;
पूर्ण __packed;

#घोषणा AR5416_NUM_BAND_EDGES		8

काष्ठा ar9170_calctl_data अणु
	काष्ठा ar9170_calctl_edges
		control_edges[AR5416_MAX_CHAINS][AR5416_NUM_BAND_EDGES];
पूर्ण __packed;

काष्ठा ar9170_eeprom अणु
	__le16	length;
	__le16	checksum;
	__le16	version;
	u8	operating_flags;
#घोषणा AR9170_OPFLAG_5GHZ		1
#घोषणा AR9170_OPFLAG_2GHZ		2
	u8	misc;
	__le16	reg_करोमुख्य[2];
	u8	mac_address[6];
	u8	rx_mask;
	u8	tx_mask;
	__le16	rf_silent;
	__le16	bluetooth_options;
	__le16	device_capabilities;
	__le32	build_number;
	u8	deviceType;
	u8	reserved[33];

	u8	customer_data[64];

	काष्ठा ar9170_eeprom_modal
		modal_header[2];

	u8	cal_freq_pier_5G[AR5416_NUM_5G_CAL_PIERS];
	u8	cal_freq_pier_2G[AR5416_NUM_2G_CAL_PIERS];

	काष्ठा ar9170_calibration_data_per_freq
		cal_pier_data_5G[AR5416_MAX_CHAINS][AR5416_NUM_5G_CAL_PIERS],
		cal_pier_data_2G[AR5416_MAX_CHAINS][AR5416_NUM_2G_CAL_PIERS];

	/* घातer calibration data */
	काष्ठा ar9170_calibration_target_घातer_legacy
		cal_tgt_pwr_5G[AR5416_NUM_5G_TARGET_PWRS];
	काष्ठा ar9170_calibration_target_घातer_ht
		cal_tgt_pwr_5G_ht20[AR5416_NUM_5G_TARGET_PWRS],
		cal_tgt_pwr_5G_ht40[AR5416_NUM_5G_TARGET_PWRS];

	काष्ठा ar9170_calibration_target_घातer_legacy
		cal_tgt_pwr_2G_cck[AR5416_NUM_2G_CCK_TARGET_PWRS],
		cal_tgt_pwr_2G_ofdm[AR5416_NUM_2G_OFDM_TARGET_PWRS];
	काष्ठा ar9170_calibration_target_घातer_ht
		cal_tgt_pwr_2G_ht20[AR5416_NUM_2G_OFDM_TARGET_PWRS],
		cal_tgt_pwr_2G_ht40[AR5416_NUM_2G_OFDM_TARGET_PWRS];

	/* conक्रमmance testing limits */
	u8	ctl_index[AR5416_NUM_CTLS];
	काष्ठा ar9170_calctl_data
		ctl_data[AR5416_NUM_CTLS];

	u8	pad;
	__le16	subप्रणाली_id;
पूर्ण __packed;

#घोषणा AR9170_LED_MODE_POWER_ON		0x0001
#घोषणा AR9170_LED_MODE_RESERVED		0x0002
#घोषणा AR9170_LED_MODE_DISABLE_STATE		0x0004
#घोषणा AR9170_LED_MODE_OFF_IN_PSM		0x0008

/* AR9170_LED_MODE BIT is set */
#घोषणा AR9170_LED_MODE_FREQUENCY_S		4
#घोषणा AR9170_LED_MODE_FREQUENCY		0x0030
#घोषणा AR9170_LED_MODE_FREQUENCY_1HZ		0x0000
#घोषणा AR9170_LED_MODE_FREQUENCY_0_5HZ		0x0010
#घोषणा AR9170_LED_MODE_FREQUENCY_0_25HZ	0x0020
#घोषणा AR9170_LED_MODE_FREQUENCY_0_125HZ	0x0030

/* AR9170_LED_MODE BIT is not set */
#घोषणा AR9170_LED_MODE_CONN_STATE_S		4
#घोषणा AR9170_LED_MODE_CONN_STATE		0x0030
#घोषणा AR9170_LED_MODE_CONN_STATE_FORCE_OFF	0x0000
#घोषणा AR9170_LED_MODE_CONN_STATE_FORCE_ON	0x0010
/* Idle off / Active on */
#घोषणा AR9170_LED_MODE_CONN_STATE_IOFF_AON	0x0020
/* Idle on / Active off */
#घोषणा AR9170_LED_MODE_CONN_STATE_ION_AOFF	0x0010

#घोषणा AR9170_LED_MODE_MODE			0x0040
#घोषणा AR9170_LED_MODE_RESERVED2		0x0080

#घोषणा AR9170_LED_MODE_TON_SCAN_S		8
#घोषणा AR9170_LED_MODE_TON_SCAN		0x0f00

#घोषणा AR9170_LED_MODE_TOFF_SCAN_S		12
#घोषणा AR9170_LED_MODE_TOFF_SCAN		0xf000

काष्ठा ar9170_led_mode अणु
	__le16 led;
पूर्ण;

#पूर्ण_अगर /* __CARL9170_SHARED_EEPROM_H */
