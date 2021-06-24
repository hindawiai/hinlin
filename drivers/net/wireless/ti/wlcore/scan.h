<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl1271
 *
 * Copyright (C) 2009-2010 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#अगर_अघोषित __SCAN_H__
#घोषणा __SCAN_H__

#समावेश "wlcore.h"

पूर्णांक wlcore_scan(काष्ठा wl1271 *wl, काष्ठा ieee80211_vअगर *vअगर,
		स्थिर u8 *ssid, माप_प्रकार ssid_len,
		काष्ठा cfg80211_scan_request *req);
पूर्णांक wl1271_scan_build_probe_req(काष्ठा wl1271 *wl,
				स्थिर u8 *ssid, माप_प्रकार ssid_len,
				स्थिर u8 *ie, माप_प्रकार ie_len, u8 band);
व्योम wl1271_scan_sपंचांग(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
व्योम wl1271_scan_complete_work(काष्ठा work_काष्ठा *work);
पूर्णांक wl1271_scan_sched_scan_config(काष्ठा wl1271 *wl,
				     काष्ठा wl12xx_vअगर *wlvअगर,
				     काष्ठा cfg80211_sched_scan_request *req,
				     काष्ठा ieee80211_scan_ies *ies);
पूर्णांक wl1271_scan_sched_scan_start(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
व्योम wlcore_scan_sched_scan_results(काष्ठा wl1271 *wl);

#घोषणा WL1271_SCAN_MAX_CHANNELS       24
#घोषणा WL1271_SCAN_DEFAULT_TAG        1
#घोषणा WL1271_SCAN_CURRENT_TX_PWR     0
#घोषणा WL1271_SCAN_OPT_ACTIVE         0
#घोषणा WL1271_SCAN_OPT_PASSIVE	       1
#घोषणा WL1271_SCAN_OPT_SPLIT_SCAN     2
#घोषणा WL1271_SCAN_OPT_PRIORITY_HIGH  4
/* scan even अगर we fail to enter psm */
#घोषणा WL1271_SCAN_OPT_FORCE          8
#घोषणा WL1271_SCAN_BAND_2_4_GHZ 0
#घोषणा WL1271_SCAN_BAND_5_GHZ 1

#घोषणा WL1271_SCAN_TIMEOUT    30000 /* msec */

क्रमागत अणु
	WL1271_SCAN_STATE_IDLE,
	WL1271_SCAN_STATE_2GHZ_ACTIVE,
	WL1271_SCAN_STATE_2GHZ_PASSIVE,
	WL1271_SCAN_STATE_5GHZ_ACTIVE,
	WL1271_SCAN_STATE_5GHZ_PASSIVE,
	WL1271_SCAN_STATE_DONE
पूर्ण;

काष्ठा wl1271_cmd_trigger_scan_to अणु
	काष्ठा wl1271_cmd_header header;

	__le32 समयout;
पूर्ण __packed;

#घोषणा MAX_CHANNELS_2GHZ	14
#घोषणा MAX_CHANNELS_4GHZ	4

/*
 * This max value here is used only क्रम the काष्ठा definition of
 * wlcore_scan_channels. This काष्ठा is used by both 12xx
 * and 18xx (which have dअगरferent max 5ghz channels value).
 * In order to make sure this is large enough, just use the
 * max possible 5ghz channels.
 */
#घोषणा MAX_CHANNELS_5GHZ	42

#घोषणा SCAN_MAX_CYCLE_INTERVALS 16

/* The FW पूर्णांकervals can take up to 16 entries.
 * The 1st entry isn't used (scan is immediate). The last
 * entry should be used क्रम the दीर्घ_पूर्णांकerval
 */
#घोषणा SCAN_MAX_SHORT_INTERVALS (SCAN_MAX_CYCLE_INTERVALS - 2)
#घोषणा SCAN_MAX_BANDS 3

क्रमागत अणु
	SCAN_SSID_FILTER_ANY      = 0,
	SCAN_SSID_FILTER_SPECIFIC = 1,
	SCAN_SSID_FILTER_LIST     = 2,
	SCAN_SSID_FILTER_DISABLED = 3
पूर्ण;

क्रमागत अणु
	SCAN_BSS_TYPE_INDEPENDENT,
	SCAN_BSS_TYPE_INFRASTRUCTURE,
	SCAN_BSS_TYPE_ANY,
पूर्ण;

#घोषणा SCAN_CHANNEL_FLAGS_DFS		BIT(0) /* channel is passive until an
						  activity is detected on it */
#घोषणा SCAN_CHANNEL_FLAGS_DFS_ENABLED	BIT(1)

काष्ठा conn_scan_ch_params अणु
	__le16 min_duration;
	__le16 max_duration;
	__le16 passive_duration;

	u8  channel;
	u8  tx_घातer_att;

	/* bit 0: DFS channel; bit 1: DFS enabled */
	u8  flags;

	u8  padding[3];
पूर्ण __packed;

#घोषणा SCHED_SCAN_MAX_SSIDS 16

क्रमागत अणु
	SCAN_SSID_TYPE_PUBLIC = 0,
	SCAN_SSID_TYPE_HIDDEN = 1,
पूर्ण;

काष्ठा wl1271_ssid अणु
	u8 type;
	u8 len;
	u8 ssid[IEEE80211_MAX_SSID_LEN];
	/* u8 padding[2]; */
पूर्ण __packed;

काष्ठा wl1271_cmd_sched_scan_ssid_list अणु
	काष्ठा wl1271_cmd_header header;

	u8 n_ssids;
	काष्ठा wl1271_ssid ssids[SCHED_SCAN_MAX_SSIDS];
	u8 role_id;
	u8 padding[2];
पूर्ण __packed;

काष्ठा wlcore_scan_channels अणु
	u8 passive[SCAN_MAX_BANDS]; /* number of passive scan channels */
	u8 active[SCAN_MAX_BANDS];  /* number of active scan channels */
	u8 dfs;		   /* number of dfs channels in 5ghz */
	u8 passive_active; /* number of passive beक्रमe active channels 2.4ghz */

	काष्ठा conn_scan_ch_params channels_2[MAX_CHANNELS_2GHZ];
	काष्ठा conn_scan_ch_params channels_5[MAX_CHANNELS_5GHZ];
	काष्ठा conn_scan_ch_params channels_4[MAX_CHANNELS_4GHZ];
पूर्ण;

क्रमागत अणु
	SCAN_TYPE_SEARCH	= 0,
	SCAN_TYPE_PERIODIC	= 1,
	SCAN_TYPE_TRACKING	= 2,
पूर्ण;

bool
wlcore_set_scan_chan_params(काष्ठा wl1271 *wl,
			    काष्ठा wlcore_scan_channels *cfg,
			    काष्ठा ieee80211_channel *channels[],
			    u32 n_channels,
			    u32 n_ssids,
			    पूर्णांक scan_type);

पूर्णांक
wlcore_scan_sched_scan_ssid_list(काष्ठा wl1271 *wl,
				 काष्ठा wl12xx_vअगर *wlvअगर,
				 काष्ठा cfg80211_sched_scan_request *req);

#पूर्ण_अगर /* __WL1271_SCAN_H__ */
