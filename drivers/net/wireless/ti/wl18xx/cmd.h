<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl18xx
 *
 * Copyright (C) 2011 Texas Instruments. All rights reserved.
 */

#अगर_अघोषित __WL18XX_CMD_H__
#घोषणा __WL18XX_CMD_H__

#समावेश "../wlcore/wlcore.h"
#समावेश "../wlcore/acx.h"

काष्ठा wl18xx_cmd_channel_चयन अणु
	काष्ठा wl1271_cmd_header header;

	u8 role_id;

	/* The new serving channel */
	u8 channel;
	/* Relative समय of the serving channel चयन in TBTT units */
	u8 चयन_समय;
	/* Stop the role TX, should expect it after radar detection */
	u8 stop_tx;

	__le32 local_supported_rates;

	u8 channel_type;
	u8 band;

	u8 padding[2];
पूर्ण __packed;

काष्ठा wl18xx_cmd_smart_config_start अणु
	काष्ठा wl1271_cmd_header header;

	__le32 group_id_biपंचांगask;
पूर्ण __packed;

काष्ठा wl18xx_cmd_smart_config_set_group_key अणु
	काष्ठा wl1271_cmd_header header;

	__le32 group_id;

	u8 key[16];
पूर्ण __packed;

काष्ठा wl18xx_cmd_dfs_radar_debug अणु
	काष्ठा wl1271_cmd_header header;

	u8 channel;
	u8 padding[3];
पूर्ण __packed;

काष्ठा wl18xx_cmd_dfs_master_restart अणु
	काष्ठा wl1271_cmd_header header;

	u8 role_id;
	u8 padding[3];
पूर्ण __packed;

/* cac_start and cac_stop share the same params */
काष्ठा wlcore_cmd_cac_start अणु
	काष्ठा wl1271_cmd_header header;

	u8 role_id;
	u8 channel;
	u8 band;
	u8 bandwidth;
पूर्ण __packed;

पूर्णांक wl18xx_cmd_channel_चयन(काष्ठा wl1271 *wl,
			      काष्ठा wl12xx_vअगर *wlvअगर,
			      काष्ठा ieee80211_channel_चयन *ch_चयन);
पूर्णांक wl18xx_cmd_smart_config_start(काष्ठा wl1271 *wl, u32 group_biपंचांगap);
पूर्णांक wl18xx_cmd_smart_config_stop(काष्ठा wl1271 *wl);
पूर्णांक wl18xx_cmd_smart_config_set_group_key(काष्ठा wl1271 *wl, u16 group_id,
					  u8 key_len, u8 *key);
पूर्णांक wl18xx_cmd_set_cac(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर, bool start);
पूर्णांक wl18xx_cmd_radar_detection_debug(काष्ठा wl1271 *wl, u8 channel);
पूर्णांक wl18xx_cmd_dfs_master_restart(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
#पूर्ण_अगर
