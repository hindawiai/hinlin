<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl12xx
 *
 * Copyright (C) 2012 Texas Instruments. All rights reserved.
 */

#अगर_अघोषित __WL12XX_SCAN_H__
#घोषणा __WL12XX_SCAN_H__

#समावेश "../wlcore/wlcore.h"
#समावेश "../wlcore/cmd.h"
#समावेश "../wlcore/scan.h"

#घोषणा WL12XX_MAX_CHANNELS_5GHZ 23

काष्ठा basic_scan_params अणु
	/* Scan option flags (WL1271_SCAN_OPT_*) */
	__le16 scan_options;
	u8 role_id;
	/* Number of scan channels in the list (maximum 30) */
	u8 n_ch;
	/* This field indicates the number of probe requests to send
	   per channel क्रम an active scan */
	u8 n_probe_reqs;
	u8 tid_trigger;
	u8 ssid_len;
	u8 use_ssid_list;

	/* Rate bit field क्रम sending the probes */
	__le32 tx_rate;

	u8 ssid[IEEE80211_MAX_SSID_LEN];
	/* Band to scan */
	u8 band;

	u8 scan_tag;
	u8 padding2[2];
पूर्ण __packed;

काष्ठा basic_scan_channel_params अणु
	/* Duration in TU to रुको क्रम frames on a channel क्रम active scan */
	__le32 min_duration;
	__le32 max_duration;
	__le32 bssid_lsb;
	__le16 bssid_msb;
	u8 early_termination;
	u8 tx_घातer_att;
	u8 channel;
	/* FW पूर्णांकernal use only! */
	u8 dfs_candidate;
	u8 activity_detected;
	u8 pad;
पूर्ण __packed;

काष्ठा wl1271_cmd_scan अणु
	काष्ठा wl1271_cmd_header header;

	काष्ठा basic_scan_params params;
	काष्ठा basic_scan_channel_params channels[WL1271_SCAN_MAX_CHANNELS];

	/* src mac address */
	u8 addr[ETH_ALEN];
	u8 padding[2];
पूर्ण __packed;

काष्ठा wl1271_cmd_sched_scan_config अणु
	काष्ठा wl1271_cmd_header header;

	__le32 पूर्णांकervals[SCAN_MAX_CYCLE_INTERVALS];

	s8 rssi_threshold; /* क्रम filtering (in dBm) */
	s8 snr_threshold;  /* क्रम filtering (in dB) */

	u8 cycles;       /* maximum number of scan cycles */
	u8 report_after; /* report when this number of results are received */
	u8 terminate;    /* stop scanning after reporting */

	u8 tag;
	u8 bss_type; /* क्रम filtering */
	u8 filter_type;

	u8 ssid_len;     /* For SCAN_SSID_FILTER_SPECIFIC */
	u8 ssid[IEEE80211_MAX_SSID_LEN];

	u8 n_probe_reqs; /* Number of probes requests per channel */

	u8 passive[SCAN_MAX_BANDS];
	u8 active[SCAN_MAX_BANDS];

	u8 dfs;

	u8 n_pactive_ch; /* number of pactive (passive until fw detects energy)
			    channels in BG band */
	u8 role_id;
	u8 padding[1];
	काष्ठा conn_scan_ch_params channels_2[MAX_CHANNELS_2GHZ];
	काष्ठा conn_scan_ch_params channels_5[WL12XX_MAX_CHANNELS_5GHZ];
	काष्ठा conn_scan_ch_params channels_4[MAX_CHANNELS_4GHZ];
पूर्ण __packed;

काष्ठा wl1271_cmd_sched_scan_start अणु
	काष्ठा wl1271_cmd_header header;

	u8 tag;
	u8 role_id;
	u8 padding[2];
पूर्ण __packed;

काष्ठा wl1271_cmd_sched_scan_stop अणु
	काष्ठा wl1271_cmd_header header;

	u8 tag;
	u8 role_id;
	u8 padding[2];
पूर्ण __packed;

पूर्णांक wl12xx_scan_start(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
		      काष्ठा cfg80211_scan_request *req);
पूर्णांक wl12xx_scan_stop(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
व्योम wl12xx_scan_completed(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
पूर्णांक wl12xx_sched_scan_start(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर  *wlvअगर,
			    काष्ठा cfg80211_sched_scan_request *req,
			    काष्ठा ieee80211_scan_ies *ies);
व्योम wl12xx_scan_sched_scan_stop(काष्ठा wl1271 *wl,  काष्ठा wl12xx_vअगर *wlvअगर);
#पूर्ण_अगर
