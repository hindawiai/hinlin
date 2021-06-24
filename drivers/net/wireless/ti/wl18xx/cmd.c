<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl18xx
 *
 * Copyright (C) 2011 Texas Instruments Inc.
 */

#समावेश "../wlcore/cmd.h"
#समावेश "../wlcore/debug.h"
#समावेश "../wlcore/hw_ops.h"

#समावेश "cmd.h"

पूर्णांक wl18xx_cmd_channel_चयन(काष्ठा wl1271 *wl,
			      काष्ठा wl12xx_vअगर *wlvअगर,
			      काष्ठा ieee80211_channel_चयन *ch_चयन)
अणु
	काष्ठा wl18xx_cmd_channel_चयन *cmd;
	u32 supported_rates;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "cmd channel switch (count=%d)",
		     ch_चयन->count);

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	cmd->role_id = wlvअगर->role_id;
	cmd->channel = ch_चयन->chandef.chan->hw_value;
	cmd->चयन_समय = ch_चयन->count;
	cmd->stop_tx = ch_चयन->block_tx;

	चयन (ch_चयन->chandef.chan->band) अणु
	हाल NL80211_BAND_2GHZ:
		cmd->band = WLCORE_BAND_2_4GHZ;
		अवरोध;
	हाल NL80211_BAND_5GHZ:
		cmd->band = WLCORE_BAND_5GHZ;
		अवरोध;
	शेष:
		wl1271_error("invalid channel switch band: %d",
			     ch_चयन->chandef.chan->band);
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	supported_rates = CONF_TX_ENABLED_RATES | CONF_TX_MCS_RATES;
	अगर (wlvअगर->bss_type == BSS_TYPE_STA_BSS)
		supported_rates |= wlcore_hw_sta_get_ap_rate_mask(wl, wlvअगर);
	अन्यथा
		supported_rates |=
			wlcore_hw_ap_get_mimo_wide_rate_mask(wl, wlvअगर);
	अगर (wlvअगर->p2p)
		supported_rates &= ~CONF_TX_CCK_RATES;
	cmd->local_supported_rates = cpu_to_le32(supported_rates);
	cmd->channel_type = wlvअगर->channel_type;

	ret = wl1271_cmd_send(wl, CMD_CHANNEL_SWITCH, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to send channel switch command");
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(cmd);
out:
	वापस ret;
पूर्ण

पूर्णांक wl18xx_cmd_smart_config_start(काष्ठा wl1271 *wl, u32 group_biपंचांगap)
अणु
	काष्ठा wl18xx_cmd_smart_config_start *cmd;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd smart config start group_bitmap=0x%x",
		     group_biपंचांगap);

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	cmd->group_id_biपंचांगask = cpu_to_le32(group_biपंचांगap);

	ret = wl1271_cmd_send(wl, CMD_SMART_CONFIG_START, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to send smart config start command");
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(cmd);
out:
	वापस ret;
पूर्ण

पूर्णांक wl18xx_cmd_smart_config_stop(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl1271_cmd_header *cmd;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd smart config stop");

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = wl1271_cmd_send(wl, CMD_SMART_CONFIG_STOP, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to send smart config stop command");
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(cmd);
out:
	वापस ret;
पूर्ण

पूर्णांक wl18xx_cmd_smart_config_set_group_key(काष्ठा wl1271 *wl, u16 group_id,
					  u8 key_len, u8 *key)
अणु
	काष्ठा wl18xx_cmd_smart_config_set_group_key *cmd;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd smart config set group key id=0x%x",
		     group_id);

	अगर (key_len != माप(cmd->key)) अणु
		wl1271_error("invalid group key size: %d", key_len);
		वापस -E2BIG;
	पूर्ण

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	cmd->group_id = cpu_to_le32(group_id);
	स_नकल(cmd->key, key, key_len);

	ret = wl1271_cmd_send(wl, CMD_SMART_CONFIG_SET_GROUP_KEY, cmd,
			      माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to send smart config set group key cmd");
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(cmd);
out:
	वापस ret;
पूर्ण

पूर्णांक wl18xx_cmd_set_cac(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर, bool start)
अणु
	काष्ठा wlcore_cmd_cac_start *cmd;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd cac (channel %d) %s",
		     wlvअगर->channel, start ? "start" : "stop");

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->role_id = wlvअगर->role_id;
	cmd->channel = wlvअगर->channel;
	अगर (wlvअगर->band == NL80211_BAND_5GHZ)
		cmd->band = WLCORE_BAND_5GHZ;
	cmd->bandwidth = wlcore_get_native_channel_type(wlvअगर->channel_type);

	ret = wl1271_cmd_send(wl,
			      start ? CMD_CAC_START : CMD_CAC_STOP,
			      cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to send cac command");
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(cmd);
	वापस ret;
पूर्ण

पूर्णांक wl18xx_cmd_radar_detection_debug(काष्ठा wl1271 *wl, u8 channel)
अणु
	काष्ठा wl18xx_cmd_dfs_radar_debug *cmd;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd radar detection debug (chan %d)",
		     channel);

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->channel = channel;

	ret = wl1271_cmd_send(wl, CMD_DFS_RADAR_DETECTION_DEBUG,
			      cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to send radar detection debug command");
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(cmd);
	वापस ret;
पूर्ण

पूर्णांक wl18xx_cmd_dfs_master_restart(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा wl18xx_cmd_dfs_master_restart *cmd;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd dfs master restart (role %d)",
		     wlvअगर->role_id);

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->role_id = wlvअगर->role_id;

	ret = wl1271_cmd_send(wl, CMD_DFS_MASTER_RESTART,
			      cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to send dfs master restart command");
		जाओ out_मुक्त;
	पूर्ण
out_मुक्त:
	kमुक्त(cmd);
	वापस ret;
पूर्ण
