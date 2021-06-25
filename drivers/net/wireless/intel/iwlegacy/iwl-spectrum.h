<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************
 *
 * Copyright(c) 2003 - 2011 Intel Corporation. All rights reserved.
 *
 * Portions of this file are derived from the ieee80211 subप्रणाली header files.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#अगर_अघोषित __il_spectrum_h__
#घोषणा __il_spectrum_h__
क्रमागत अणु				/* ieee80211_basic_report.map */
	IEEE80211_BASIC_MAP_BSS = (1 << 0),
	IEEE80211_BASIC_MAP_OFDM = (1 << 1),
	IEEE80211_BASIC_MAP_UNIDENTIFIED = (1 << 2),
	IEEE80211_BASIC_MAP_RADAR = (1 << 3),
	IEEE80211_BASIC_MAP_UNMEASURED = (1 << 4),
	/* Bits 5-7 are reserved */

पूर्ण;
काष्ठा ieee80211_basic_report अणु
	u8 channel;
	__le64 start_समय;
	__le16 duration;
	u8 map;
पूर्ण __packed;

क्रमागत अणु				/* ieee80211_measurement_request.mode */
	/* Bit 0 is reserved */
	IEEE80211_MEASUREMENT_ENABLE = (1 << 1),
	IEEE80211_MEASUREMENT_REQUEST = (1 << 2),
	IEEE80211_MEASUREMENT_REPORT = (1 << 3),
	/* Bits 4-7 are reserved */
पूर्ण;

क्रमागत अणु
	IEEE80211_REPORT_BASIC = 0,	/* required */
	IEEE80211_REPORT_CCA = 1,	/* optional */
	IEEE80211_REPORT_RPI = 2,	/* optional */
	/* 3-255 reserved */
पूर्ण;

काष्ठा ieee80211_measurement_params अणु
	u8 channel;
	__le64 start_समय;
	__le16 duration;
पूर्ण __packed;

काष्ठा ieee80211_info_element अणु
	u8 id;
	u8 len;
	u8 data[];
पूर्ण __packed;

काष्ठा ieee80211_measurement_request अणु
	काष्ठा ieee80211_info_element ie;
	u8 token;
	u8 mode;
	u8 type;
	काष्ठा ieee80211_measurement_params params[];
पूर्ण __packed;

काष्ठा ieee80211_measurement_report अणु
	काष्ठा ieee80211_info_element ie;
	u8 token;
	u8 mode;
	u8 type;
	जोड़ अणु
		काष्ठा ieee80211_basic_report basic[0];
	पूर्ण u;
पूर्ण __packed;

#पूर्ण_अगर
