<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1271
 *
 * Copyright (C) 2009-2010 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/spi/spi.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ieee80211.h>
#समावेश <linux/slab.h>

#समावेश "wlcore.h"
#समावेश "debug.h"
#समावेश "io.h"
#समावेश "acx.h"
#समावेश "wl12xx_80211.h"
#समावेश "cmd.h"
#समावेश "event.h"
#समावेश "tx.h"
#समावेश "hw_ops.h"

#घोषणा WL1271_CMD_FAST_POLL_COUNT       50
#घोषणा WL1271_WAIT_EVENT_FAST_POLL_COUNT 20

/*
 * send command to firmware
 *
 * @wl: wl काष्ठा
 * @id: command id
 * @buf: buffer containing the command, must work with dma
 * @len: length of the buffer
 * वापस the cmd status code on success.
 */
अटल पूर्णांक __wlcore_cmd_send(काष्ठा wl1271 *wl, u16 id, व्योम *buf,
			     माप_प्रकार len, माप_प्रकार res_len)
अणु
	काष्ठा wl1271_cmd_header *cmd;
	अचिन्हित दीर्घ समयout;
	u32 पूर्णांकr;
	पूर्णांक ret;
	u16 status;
	u16 poll_count = 0;

	अगर (unlikely(wl->state == WLCORE_STATE_RESTARTING &&
		     id != CMD_STOP_FWLOGGER))
		वापस -EIO;

	अगर (WARN_ON_ONCE(len < माप(*cmd)))
		वापस -EIO;

	cmd = buf;
	cmd->id = cpu_to_le16(id);
	cmd->status = 0;

	WARN_ON(len % 4 != 0);
	WARN_ON(test_bit(WL1271_FLAG_IN_ELP, &wl->flags));

	ret = wlcore_ग_लिखो(wl, wl->cmd_box_addr, buf, len, false);
	अगर (ret < 0)
		वापस ret;

	/*
	 * TODO: we just need this because one bit is in a dअगरferent
	 * place.  Is there any better way?
	 */
	ret = wl->ops->trigger_cmd(wl, wl->cmd_box_addr, buf, len);
	अगर (ret < 0)
		वापस ret;

	समयout = jअगरfies + msecs_to_jअगरfies(WL1271_COMMAND_TIMEOUT);

	ret = wlcore_पढ़ो_reg(wl, REG_INTERRUPT_NO_CLEAR, &पूर्णांकr);
	अगर (ret < 0)
		वापस ret;

	जबतक (!(पूर्णांकr & WL1271_ACX_INTR_CMD_COMPLETE)) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			wl1271_error("command complete timeout");
			वापस -ETIMEDOUT;
		पूर्ण

		poll_count++;
		अगर (poll_count < WL1271_CMD_FAST_POLL_COUNT)
			udelay(10);
		अन्यथा
			msleep(1);

		ret = wlcore_पढ़ो_reg(wl, REG_INTERRUPT_NO_CLEAR, &पूर्णांकr);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* पढ़ो back the status code of the command */
	अगर (res_len == 0)
		res_len = माप(काष्ठा wl1271_cmd_header);

	ret = wlcore_पढ़ो(wl, wl->cmd_box_addr, cmd, res_len, false);
	अगर (ret < 0)
		वापस ret;

	status = le16_to_cpu(cmd->status);

	ret = wlcore_ग_लिखो_reg(wl, REG_INTERRUPT_ACK,
			       WL1271_ACX_INTR_CMD_COMPLETE);
	अगर (ret < 0)
		वापस ret;

	वापस status;
पूर्ण

/*
 * send command to fw and वापस cmd status on success
 * valid_rets contains a biपंचांगap of allowed error codes
 */
अटल पूर्णांक wlcore_cmd_send_failsafe(काष्ठा wl1271 *wl, u16 id, व्योम *buf,
				    माप_प्रकार len, माप_प्रकार res_len,
				    अचिन्हित दीर्घ valid_rets)
अणु
	पूर्णांक ret = __wlcore_cmd_send(wl, id, buf, len, res_len);

	अगर (ret < 0)
		जाओ fail;

	/* success is always a valid status */
	valid_rets |= BIT(CMD_STATUS_SUCCESS);

	अगर (ret >= MAX_COMMAND_STATUS ||
	    !test_bit(ret, &valid_rets)) अणु
		wl1271_error("command execute failure %d", ret);
		ret = -EIO;
		जाओ fail;
	पूर्ण
	वापस ret;
fail:
	wl12xx_queue_recovery_work(wl);
	वापस ret;
पूर्ण

/*
 * wrapper क्रम wlcore_cmd_send that accept only CMD_STATUS_SUCCESS
 * वापस 0 on success.
 */
पूर्णांक wl1271_cmd_send(काष्ठा wl1271 *wl, u16 id, व्योम *buf, माप_प्रकार len,
		    माप_प्रकार res_len)
अणु
	पूर्णांक ret = wlcore_cmd_send_failsafe(wl, id, buf, len, res_len, 0);

	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wl1271_cmd_send);

/*
 * Poll the mailbox event field until any of the bits in the mask is set or a
 * समयout occurs (WL1271_EVENT_TIMEOUT in msecs)
 */
पूर्णांक wlcore_cmd_रुको_क्रम_event_or_समयout(काष्ठा wl1271 *wl,
					 u32 mask, bool *समयout)
अणु
	u32 *events_vector;
	u32 event;
	अचिन्हित दीर्घ समयout_समय;
	u16 poll_count = 0;
	पूर्णांक ret = 0;

	*समयout = false;

	events_vector = kदो_स्मृति(माप(*events_vector), GFP_KERNEL | GFP_DMA);
	अगर (!events_vector)
		वापस -ENOMEM;

	समयout_समय = jअगरfies + msecs_to_jअगरfies(WL1271_EVENT_TIMEOUT);

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ मुक्त_vector;
	पूर्ण

	करो अणु
		अगर (समय_after(jअगरfies, समयout_समय)) अणु
			wl1271_debug(DEBUG_CMD, "timeout waiting for event %d",
				     (पूर्णांक)mask);
			*समयout = true;
			जाओ out;
		पूर्ण

		poll_count++;
		अगर (poll_count < WL1271_WAIT_EVENT_FAST_POLL_COUNT)
			usleep_range(50, 51);
		अन्यथा
			usleep_range(1000, 5000);

		/* पढ़ो from both event fields */
		ret = wlcore_पढ़ो(wl, wl->mbox_ptr[0], events_vector,
				  माप(*events_vector), false);
		अगर (ret < 0)
			जाओ out;

		event = *events_vector & mask;

		ret = wlcore_पढ़ो(wl, wl->mbox_ptr[1], events_vector,
				  माप(*events_vector), false);
		अगर (ret < 0)
			जाओ out;

		event |= *events_vector & mask;
	पूर्ण जबतक (!event);

out:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
मुक्त_vector:
	kमुक्त(events_vector);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_cmd_रुको_क्रम_event_or_समयout);

पूर्णांक wl12xx_cmd_role_enable(काष्ठा wl1271 *wl, u8 *addr, u8 role_type,
			   u8 *role_id)
अणु
	काष्ठा wl12xx_cmd_role_enable *cmd;
	पूर्णांक ret;

	wl1271_debug(DEBUG_CMD, "cmd role enable");

	अगर (WARN_ON(*role_id != WL12XX_INVALID_ROLE_ID))
		वापस -EBUSY;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* get role id */
	cmd->role_id = find_first_zero_bit(wl->roles_map, WL12XX_MAX_ROLES);
	अगर (cmd->role_id >= WL12XX_MAX_ROLES) अणु
		ret = -EBUSY;
		जाओ out_मुक्त;
	पूर्ण

	स_नकल(cmd->mac_address, addr, ETH_ALEN);
	cmd->role_type = role_type;

	ret = wl1271_cmd_send(wl, CMD_ROLE_ENABLE, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to initiate cmd role enable");
		जाओ out_मुक्त;
	पूर्ण

	__set_bit(cmd->role_id, wl->roles_map);
	*role_id = cmd->role_id;

out_मुक्त:
	kमुक्त(cmd);

out:
	वापस ret;
पूर्ण

पूर्णांक wl12xx_cmd_role_disable(काष्ठा wl1271 *wl, u8 *role_id)
अणु
	काष्ठा wl12xx_cmd_role_disable *cmd;
	पूर्णांक ret;

	wl1271_debug(DEBUG_CMD, "cmd role disable");

	अगर (WARN_ON(*role_id == WL12XX_INVALID_ROLE_ID))
		वापस -ENOENT;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	cmd->role_id = *role_id;

	ret = wl1271_cmd_send(wl, CMD_ROLE_DISABLE, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to initiate cmd role disable");
		जाओ out_मुक्त;
	पूर्ण

	__clear_bit(*role_id, wl->roles_map);
	*role_id = WL12XX_INVALID_ROLE_ID;

out_मुक्त:
	kमुक्त(cmd);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wlcore_get_new_session_id(काष्ठा wl1271 *wl, u8 hlid)
अणु
	अगर (wl->session_ids[hlid] >= SESSION_COUNTER_MAX)
		wl->session_ids[hlid] = 0;

	wl->session_ids[hlid]++;

	वापस wl->session_ids[hlid];
पूर्ण

पूर्णांक wl12xx_allocate_link(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर, u8 *hlid)
अणु
	अचिन्हित दीर्घ flags;
	u8 link = find_first_zero_bit(wl->links_map, wl->num_links);
	अगर (link >= wl->num_links)
		वापस -EBUSY;

	wl->session_ids[link] = wlcore_get_new_session_id(wl, link);

	/* these bits are used by op_tx */
	spin_lock_irqsave(&wl->wl_lock, flags);
	__set_bit(link, wl->links_map);
	__set_bit(link, wlvअगर->links_map);
	spin_unlock_irqrestore(&wl->wl_lock, flags);

	/*
	 * take the last "freed packets" value from the current FW status.
	 * on recovery, we might not have fw_status yet, and
	 * tx_lnk_मुक्त_pkts will be शून्य. check क्रम it.
	 */
	अगर (wl->fw_status->counters.tx_lnk_मुक्त_pkts)
		wl->links[link].prev_मुक्तd_pkts =
			wl->fw_status->counters.tx_lnk_मुक्त_pkts[link];
	wl->links[link].wlvअगर = wlvअगर;

	/*
	 * Take saved value क्रम total मुक्तd packets from wlvअगर, in हाल this is
	 * recovery/resume
	 */
	अगर (wlvअगर->bss_type != BSS_TYPE_AP_BSS)
		wl->links[link].total_मुक्तd_pkts = wlvअगर->total_मुक्तd_pkts;

	*hlid = link;

	wl->active_link_count++;
	वापस 0;
पूर्ण

व्योम wl12xx_मुक्त_link(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर, u8 *hlid)
अणु
	अचिन्हित दीर्घ flags;

	अगर (*hlid == WL12XX_INVALID_LINK_ID)
		वापस;

	/* these bits are used by op_tx */
	spin_lock_irqsave(&wl->wl_lock, flags);
	__clear_bit(*hlid, wl->links_map);
	__clear_bit(*hlid, wlvअगर->links_map);
	spin_unlock_irqrestore(&wl->wl_lock, flags);

	wl->links[*hlid].allocated_pkts = 0;
	wl->links[*hlid].prev_मुक्तd_pkts = 0;
	wl->links[*hlid].ba_biपंचांगap = 0;
	eth_zero_addr(wl->links[*hlid].addr);

	/*
	 * At this poपूर्णांक op_tx() will not add more packets to the queues. We
	 * can purge them.
	 */
	wl1271_tx_reset_link_queues(wl, *hlid);
	wl->links[*hlid].wlvअगर = शून्य;

	अगर (wlvअगर->bss_type == BSS_TYPE_AP_BSS &&
	    *hlid == wlvअगर->ap.bcast_hlid) अणु
		u32 sqn_padding = WL1271_TX_SQN_POST_RECOVERY_PADDING;
		/*
		 * save the total मुक्तd packets in the wlvअगर, in हाल this is
		 * recovery or suspend
		 */
		wlvअगर->total_मुक्तd_pkts = wl->links[*hlid].total_मुक्तd_pkts;

		/*
		 * increment the initial seq number on recovery to account क्रम
		 * transmitted packets that we haven't yet got in the FW status
		 */
		अगर (wlvअगर->encryption_type == KEY_GEM)
			sqn_padding = WL1271_TX_SQN_POST_RECOVERY_PADDING_GEM;

		अगर (test_bit(WL1271_FLAG_RECOVERY_IN_PROGRESS, &wl->flags))
			wlvअगर->total_मुक्तd_pkts += sqn_padding;
	पूर्ण

	wl->links[*hlid].total_मुक्तd_pkts = 0;

	*hlid = WL12XX_INVALID_LINK_ID;
	wl->active_link_count--;
	WARN_ON_ONCE(wl->active_link_count < 0);
पूर्ण

u8 wlcore_get_native_channel_type(u8 nl_channel_type)
अणु
	चयन (nl_channel_type) अणु
	हाल NL80211_CHAN_NO_HT:
		वापस WLCORE_CHAN_NO_HT;
	हाल NL80211_CHAN_HT20:
		वापस WLCORE_CHAN_HT20;
	हाल NL80211_CHAN_HT40MINUS:
		वापस WLCORE_CHAN_HT40MINUS;
	हाल NL80211_CHAN_HT40PLUS:
		वापस WLCORE_CHAN_HT40PLUS;
	शेष:
		WARN_ON(1);
		वापस WLCORE_CHAN_NO_HT;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_get_native_channel_type);

अटल पूर्णांक wl12xx_cmd_role_start_dev(काष्ठा wl1271 *wl,
				     काष्ठा wl12xx_vअगर *wlvअगर,
				     क्रमागत nl80211_band band,
				     पूर्णांक channel)
अणु
	काष्ठा wl12xx_cmd_role_start *cmd;
	पूर्णांक ret;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	wl1271_debug(DEBUG_CMD, "cmd role start dev %d", wlvअगर->dev_role_id);

	cmd->role_id = wlvअगर->dev_role_id;
	अगर (band == NL80211_BAND_5GHZ)
		cmd->band = WLCORE_BAND_5GHZ;
	cmd->channel = channel;

	अगर (wlvअगर->dev_hlid == WL12XX_INVALID_LINK_ID) अणु
		ret = wl12xx_allocate_link(wl, wlvअगर, &wlvअगर->dev_hlid);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण
	cmd->device.hlid = wlvअगर->dev_hlid;
	cmd->device.session = wl->session_ids[wlvअगर->dev_hlid];

	wl1271_debug(DEBUG_CMD, "role start: roleid=%d, hlid=%d, session=%d",
		     cmd->role_id, cmd->device.hlid, cmd->device.session);

	ret = wl1271_cmd_send(wl, CMD_ROLE_START, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to initiate cmd role enable");
		जाओ err_hlid;
	पूर्ण

	जाओ out_मुक्त;

err_hlid:
	/* clear links on error */
	wl12xx_मुक्त_link(wl, wlvअगर, &wlvअगर->dev_hlid);

out_मुक्त:
	kमुक्त(cmd);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl12xx_cmd_role_stop_dev(काष्ठा wl1271 *wl,
				    काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा wl12xx_cmd_role_stop *cmd;
	पूर्णांक ret;

	अगर (WARN_ON(wlvअगर->dev_hlid == WL12XX_INVALID_LINK_ID))
		वापस -EINVAL;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	wl1271_debug(DEBUG_CMD, "cmd role stop dev");

	cmd->role_id = wlvअगर->dev_role_id;
	cmd->disc_type = DISCONNECT_IMMEDIATE;
	cmd->reason = cpu_to_le16(WLAN_REASON_UNSPECIFIED);

	ret = wl1271_cmd_send(wl, CMD_ROLE_STOP, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to initiate cmd role stop");
		जाओ out_मुक्त;
	पूर्ण

	wl12xx_मुक्त_link(wl, wlvअगर, &wlvअगर->dev_hlid);

out_मुक्त:
	kमुक्त(cmd);

out:
	वापस ret;
पूर्ण

पूर्णांक wl12xx_cmd_role_start_sta(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा ieee80211_vअगर *vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);
	काष्ठा wl12xx_cmd_role_start *cmd;
	u32 supported_rates;
	पूर्णांक ret;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	wl1271_debug(DEBUG_CMD, "cmd role start sta %d", wlvअगर->role_id);

	cmd->role_id = wlvअगर->role_id;
	अगर (wlvअगर->band == NL80211_BAND_5GHZ)
		cmd->band = WLCORE_BAND_5GHZ;
	cmd->channel = wlvअगर->channel;
	cmd->sta.basic_rate_set = cpu_to_le32(wlvअगर->basic_rate_set);
	cmd->sta.beacon_पूर्णांकerval = cpu_to_le16(wlvअगर->beacon_पूर्णांक);
	cmd->sta.ssid_type = WL12XX_SSID_TYPE_ANY;
	cmd->sta.ssid_len = wlvअगर->ssid_len;
	स_नकल(cmd->sta.ssid, wlvअगर->ssid, wlvअगर->ssid_len);
	स_नकल(cmd->sta.bssid, vअगर->bss_conf.bssid, ETH_ALEN);

	supported_rates = CONF_TX_ENABLED_RATES | CONF_TX_MCS_RATES |
			  wlcore_hw_sta_get_ap_rate_mask(wl, wlvअगर);
	अगर (wlvअगर->p2p)
		supported_rates &= ~CONF_TX_CCK_RATES;

	cmd->sta.local_rates = cpu_to_le32(supported_rates);

	cmd->channel_type = wlcore_get_native_channel_type(wlvअगर->channel_type);

	अगर (wlvअगर->sta.hlid == WL12XX_INVALID_LINK_ID) अणु
		ret = wl12xx_allocate_link(wl, wlvअगर, &wlvअगर->sta.hlid);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण
	cmd->sta.hlid = wlvअगर->sta.hlid;
	cmd->sta.session = wl->session_ids[wlvअगर->sta.hlid];
	/*
	 * We करोn't have the correct remote rates in this stage.  The
	 * rates will be reconfigured later, after association, अगर the
	 * firmware supports ACX_PEER_CAP.  Otherwise, there's nothing
	 * we can करो, so use all supported_rates here.
	 */
	cmd->sta.remote_rates = cpu_to_le32(supported_rates);

	wl1271_debug(DEBUG_CMD, "role start: roleid=%d, hlid=%d, session=%d "
		     "basic_rate_set: 0x%x, remote_rates: 0x%x",
		     wlvअगर->role_id, cmd->sta.hlid, cmd->sta.session,
		     wlvअगर->basic_rate_set, wlvअगर->rate_set);

	ret = wl1271_cmd_send(wl, CMD_ROLE_START, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to initiate cmd role start sta");
		जाओ err_hlid;
	पूर्ण

	wlvअगर->sta.role_chan_type = wlvअगर->channel_type;
	जाओ out_मुक्त;

err_hlid:
	/* clear links on error. */
	wl12xx_मुक्त_link(wl, wlvअगर, &wlvअगर->sta.hlid);

out_मुक्त:
	kमुक्त(cmd);

out:
	वापस ret;
पूर्ण

/* use this function to stop ibss as well */
पूर्णांक wl12xx_cmd_role_stop_sta(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा wl12xx_cmd_role_stop *cmd;
	पूर्णांक ret;

	अगर (WARN_ON(wlvअगर->sta.hlid == WL12XX_INVALID_LINK_ID))
		वापस -EINVAL;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	wl1271_debug(DEBUG_CMD, "cmd role stop sta %d", wlvअगर->role_id);

	cmd->role_id = wlvअगर->role_id;
	cmd->disc_type = DISCONNECT_IMMEDIATE;
	cmd->reason = cpu_to_le16(WLAN_REASON_UNSPECIFIED);

	ret = wl1271_cmd_send(wl, CMD_ROLE_STOP, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to initiate cmd role stop sta");
		जाओ out_मुक्त;
	पूर्ण

	wl12xx_मुक्त_link(wl, wlvअगर, &wlvअगर->sta.hlid);

out_मुक्त:
	kमुक्त(cmd);

out:
	वापस ret;
पूर्ण

पूर्णांक wl12xx_cmd_role_start_ap(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा wl12xx_cmd_role_start *cmd;
	काष्ठा ieee80211_vअगर *vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);
	काष्ठा ieee80211_bss_conf *bss_conf = &vअगर->bss_conf;
	u32 supported_rates;
	पूर्णांक ret;

	wl1271_debug(DEBUG_CMD, "cmd role start ap %d", wlvअगर->role_id);

	/* If MESH --> ssid_len is always 0 */
	अगर (!ieee80211_vअगर_is_mesh(vअगर)) अणु
		/* trying to use hidden SSID with an old hostapd version */
		अगर (wlvअगर->ssid_len == 0 && !bss_conf->hidden_ssid) अणु
			wl1271_error("got a null SSID from beacon/bss");
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = wl12xx_allocate_link(wl, wlvअगर, &wlvअगर->ap.global_hlid);
	अगर (ret < 0)
		जाओ out_मुक्त;

	ret = wl12xx_allocate_link(wl, wlvअगर, &wlvअगर->ap.bcast_hlid);
	अगर (ret < 0)
		जाओ out_मुक्त_global;

	/* use the previous security seq, अगर this is a recovery/resume */
	wl->links[wlvअगर->ap.bcast_hlid].total_मुक्तd_pkts =
						wlvअगर->total_मुक्तd_pkts;

	cmd->role_id = wlvअगर->role_id;
	cmd->ap.aging_period = cpu_to_le16(wl->conf.tx.ap_aging_period);
	cmd->ap.bss_index = WL1271_AP_BSS_INDEX;
	cmd->ap.global_hlid = wlvअगर->ap.global_hlid;
	cmd->ap.broadcast_hlid = wlvअगर->ap.bcast_hlid;
	cmd->ap.global_session_id = wl->session_ids[wlvअगर->ap.global_hlid];
	cmd->ap.bcast_session_id = wl->session_ids[wlvअगर->ap.bcast_hlid];
	cmd->ap.basic_rate_set = cpu_to_le32(wlvअगर->basic_rate_set);
	cmd->ap.beacon_पूर्णांकerval = cpu_to_le16(wlvअगर->beacon_पूर्णांक);
	cmd->ap.dtim_पूर्णांकerval = bss_conf->dtim_period;
	cmd->ap.beacon_expiry = WL1271_AP_DEF_BEACON_EXP;
	/* FIXME: Change when adding DFS */
	cmd->ap.reset_tsf = 1;  /* By शेष reset AP TSF */
	cmd->ap.wmm = wlvअगर->wmm_enabled;
	cmd->channel = wlvअगर->channel;
	cmd->channel_type = wlcore_get_native_channel_type(wlvअगर->channel_type);

	अगर (!bss_conf->hidden_ssid) अणु
		/* take the SSID from the beacon क्रम backward compatibility */
		cmd->ap.ssid_type = WL12XX_SSID_TYPE_PUBLIC;
		cmd->ap.ssid_len = wlvअगर->ssid_len;
		स_नकल(cmd->ap.ssid, wlvअगर->ssid, wlvअगर->ssid_len);
	पूर्ण अन्यथा अणु
		cmd->ap.ssid_type = WL12XX_SSID_TYPE_HIDDEN;
		cmd->ap.ssid_len = bss_conf->ssid_len;
		स_नकल(cmd->ap.ssid, bss_conf->ssid, bss_conf->ssid_len);
	पूर्ण

	supported_rates = CONF_TX_ENABLED_RATES | CONF_TX_MCS_RATES |
		wlcore_hw_ap_get_mimo_wide_rate_mask(wl, wlvअगर);
	अगर (wlvअगर->p2p)
		supported_rates &= ~CONF_TX_CCK_RATES;

	wl1271_debug(DEBUG_CMD, "cmd role start ap with supported_rates 0x%08x",
		     supported_rates);

	cmd->ap.local_rates = cpu_to_le32(supported_rates);

	चयन (wlvअगर->band) अणु
	हाल NL80211_BAND_2GHZ:
		cmd->band = WLCORE_BAND_2_4GHZ;
		अवरोध;
	हाल NL80211_BAND_5GHZ:
		cmd->band = WLCORE_BAND_5GHZ;
		अवरोध;
	शेष:
		wl1271_warning("ap start - unknown band: %d", (पूर्णांक)wlvअगर->band);
		cmd->band = WLCORE_BAND_2_4GHZ;
		अवरोध;
	पूर्ण

	ret = wl1271_cmd_send(wl, CMD_ROLE_START, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to initiate cmd role start ap");
		जाओ out_मुक्त_bcast;
	पूर्ण

	जाओ out_मुक्त;

out_मुक्त_bcast:
	wl12xx_मुक्त_link(wl, wlvअगर, &wlvअगर->ap.bcast_hlid);

out_मुक्त_global:
	wl12xx_मुक्त_link(wl, wlvअगर, &wlvअगर->ap.global_hlid);

out_मुक्त:
	kमुक्त(cmd);

out:
	वापस ret;
पूर्ण

पूर्णांक wl12xx_cmd_role_stop_ap(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा wl12xx_cmd_role_stop *cmd;
	पूर्णांक ret;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	wl1271_debug(DEBUG_CMD, "cmd role stop ap %d", wlvअगर->role_id);

	cmd->role_id = wlvअगर->role_id;

	ret = wl1271_cmd_send(wl, CMD_ROLE_STOP, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to initiate cmd role stop ap");
		जाओ out_मुक्त;
	पूर्ण

	wl12xx_मुक्त_link(wl, wlvअगर, &wlvअगर->ap.bcast_hlid);
	wl12xx_मुक्त_link(wl, wlvअगर, &wlvअगर->ap.global_hlid);

out_मुक्त:
	kमुक्त(cmd);

out:
	वापस ret;
पूर्ण

पूर्णांक wl12xx_cmd_role_start_ibss(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा ieee80211_vअगर *vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);
	काष्ठा wl12xx_cmd_role_start *cmd;
	काष्ठा ieee80211_bss_conf *bss_conf = &vअगर->bss_conf;
	पूर्णांक ret;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	wl1271_debug(DEBUG_CMD, "cmd role start ibss %d", wlvअगर->role_id);

	cmd->role_id = wlvअगर->role_id;
	अगर (wlvअगर->band == NL80211_BAND_5GHZ)
		cmd->band = WLCORE_BAND_5GHZ;
	cmd->channel = wlvअगर->channel;
	cmd->ibss.basic_rate_set = cpu_to_le32(wlvअगर->basic_rate_set);
	cmd->ibss.beacon_पूर्णांकerval = cpu_to_le16(wlvअगर->beacon_पूर्णांक);
	cmd->ibss.dtim_पूर्णांकerval = bss_conf->dtim_period;
	cmd->ibss.ssid_type = WL12XX_SSID_TYPE_ANY;
	cmd->ibss.ssid_len = wlvअगर->ssid_len;
	स_नकल(cmd->ibss.ssid, wlvअगर->ssid, wlvअगर->ssid_len);
	स_नकल(cmd->ibss.bssid, vअगर->bss_conf.bssid, ETH_ALEN);
	cmd->sta.local_rates = cpu_to_le32(wlvअगर->rate_set);

	अगर (wlvअगर->sta.hlid == WL12XX_INVALID_LINK_ID) अणु
		ret = wl12xx_allocate_link(wl, wlvअगर, &wlvअगर->sta.hlid);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण
	cmd->ibss.hlid = wlvअगर->sta.hlid;
	cmd->ibss.remote_rates = cpu_to_le32(wlvअगर->rate_set);

	wl1271_debug(DEBUG_CMD, "role start: roleid=%d, hlid=%d, session=%d "
		     "basic_rate_set: 0x%x, remote_rates: 0x%x",
		     wlvअगर->role_id, cmd->sta.hlid, cmd->sta.session,
		     wlvअगर->basic_rate_set, wlvअगर->rate_set);

	wl1271_debug(DEBUG_CMD, "vif->bss_conf.bssid = %pM",
		     vअगर->bss_conf.bssid);

	ret = wl1271_cmd_send(wl, CMD_ROLE_START, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to initiate cmd role enable");
		जाओ err_hlid;
	पूर्ण

	जाओ out_मुक्त;

err_hlid:
	/* clear links on error. */
	wl12xx_मुक्त_link(wl, wlvअगर, &wlvअगर->sta.hlid);

out_मुक्त:
	kमुक्त(cmd);

out:
	वापस ret;
पूर्ण


/**
 * send test command to firmware
 *
 * @wl: wl काष्ठा
 * @buf: buffer containing the command, with all headers, must work with dma
 * @buf_len: length of the buffer
 * @answer: is answer needed
 */
पूर्णांक wl1271_cmd_test(काष्ठा wl1271 *wl, व्योम *buf, माप_प्रकार buf_len, u8 answer)
अणु
	पूर्णांक ret;
	माप_प्रकार res_len = 0;

	wl1271_debug(DEBUG_CMD, "cmd test");

	अगर (answer)
		res_len = buf_len;

	ret = wl1271_cmd_send(wl, CMD_TEST, buf, buf_len, res_len);

	अगर (ret < 0) अणु
		wl1271_warning("TEST command failed");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wl1271_cmd_test);

/**
 * पढ़ो acx from firmware
 *
 * @wl: wl काष्ठा
 * @id: acx id
 * @buf: buffer क्रम the response, including all headers, must work with dma
 * @cmd_len: length of command
 * @res_len: length of payload
 */
पूर्णांक wl1271_cmd_पूर्णांकerrogate(काष्ठा wl1271 *wl, u16 id, व्योम *buf,
			   माप_प्रकार cmd_len, माप_प्रकार res_len)
अणु
	काष्ठा acx_header *acx = buf;
	पूर्णांक ret;

	wl1271_debug(DEBUG_CMD, "cmd interrogate");

	acx->id = cpu_to_le16(id);

	/* response payload length, करोes not include any headers */
	acx->len = cpu_to_le16(res_len - माप(*acx));

	ret = wl1271_cmd_send(wl, CMD_INTERROGATE, acx, cmd_len, res_len);
	अगर (ret < 0)
		wl1271_error("INTERROGATE command failed");

	वापस ret;
पूर्ण

/**
 * ग_लिखो acx value to firmware
 *
 * @wl: wl काष्ठा
 * @id: acx id
 * @buf: buffer containing acx, including all headers, must work with dma
 * @len: length of buf
 * @valid_rets: biपंचांगap of valid cmd status codes (i.e. वापस values).
 * वापस the cmd status on success.
 */
पूर्णांक wlcore_cmd_configure_failsafe(काष्ठा wl1271 *wl, u16 id, व्योम *buf,
				  माप_प्रकार len, अचिन्हित दीर्घ valid_rets)
अणु
	काष्ठा acx_header *acx = buf;
	पूर्णांक ret;

	wl1271_debug(DEBUG_CMD, "cmd configure (%d)", id);

	अगर (WARN_ON_ONCE(len < माप(*acx)))
		वापस -EIO;

	acx->id = cpu_to_le16(id);

	/* payload length, करोes not include any headers */
	acx->len = cpu_to_le16(len - माप(*acx));

	ret = wlcore_cmd_send_failsafe(wl, CMD_CONFIGURE, acx, len, 0,
				       valid_rets);
	अगर (ret < 0) अणु
		wl1271_warning("CONFIGURE command NOK");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * wrapper क्रम wlcore_cmd_configure that accepts only success status.
 * वापस 0 on success
 */
पूर्णांक wl1271_cmd_configure(काष्ठा wl1271 *wl, u16 id, व्योम *buf, माप_प्रकार len)
अणु
	पूर्णांक ret = wlcore_cmd_configure_failsafe(wl, id, buf, len, 0);

	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wl1271_cmd_configure);

पूर्णांक wl1271_cmd_data_path(काष्ठा wl1271 *wl, bool enable)
अणु
	काष्ठा cmd_enabledisable_path *cmd;
	पूर्णांक ret;
	u16 cmd_rx, cmd_tx;

	wl1271_debug(DEBUG_CMD, "cmd data path");

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* the channel here is only used क्रम calibration, so hardcoded to 1 */
	cmd->channel = 1;

	अगर (enable) अणु
		cmd_rx = CMD_ENABLE_RX;
		cmd_tx = CMD_ENABLE_TX;
	पूर्ण अन्यथा अणु
		cmd_rx = CMD_DISABLE_RX;
		cmd_tx = CMD_DISABLE_TX;
	पूर्ण

	ret = wl1271_cmd_send(wl, cmd_rx, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("rx %s cmd for channel %d failed",
			     enable ? "start" : "stop", cmd->channel);
		जाओ out;
	पूर्ण

	wl1271_debug(DEBUG_BOOT, "rx %s cmd channel %d",
		     enable ? "start" : "stop", cmd->channel);

	ret = wl1271_cmd_send(wl, cmd_tx, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("tx %s cmd for channel %d failed",
			     enable ? "start" : "stop", cmd->channel);
		जाओ out;
	पूर्ण

	wl1271_debug(DEBUG_BOOT, "tx %s cmd channel %d",
		     enable ? "start" : "stop", cmd->channel);

out:
	kमुक्त(cmd);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wl1271_cmd_data_path);

पूर्णांक wl1271_cmd_ps_mode(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
		       u8 ps_mode, u16 स्वतः_ps_समयout)
अणु
	काष्ठा wl1271_cmd_ps_params *ps_params = शून्य;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd set ps mode");

	ps_params = kzalloc(माप(*ps_params), GFP_KERNEL);
	अगर (!ps_params) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ps_params->role_id = wlvअगर->role_id;
	ps_params->ps_mode = ps_mode;
	ps_params->स्वतः_ps_समयout = स्वतः_ps_समयout;

	ret = wl1271_cmd_send(wl, CMD_SET_PS_MODE, ps_params,
			      माप(*ps_params), 0);
	अगर (ret < 0) अणु
		wl1271_error("cmd set_ps_mode failed");
		जाओ out;
	पूर्ण

out:
	kमुक्त(ps_params);
	वापस ret;
पूर्ण

पूर्णांक wl1271_cmd_ढाँचा_set(काष्ठा wl1271 *wl, u8 role_id,
			    u16 ढाँचा_id, व्योम *buf, माप_प्रकार buf_len,
			    पूर्णांक index, u32 rates)
अणु
	काष्ठा wl1271_cmd_ढाँचा_set *cmd;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd template_set %d (role %d)",
		     ढाँचा_id, role_id);

	WARN_ON(buf_len > WL1271_CMD_TEMPL_MAX_SIZE);
	buf_len = min_t(माप_प्रकार, buf_len, WL1271_CMD_TEMPL_MAX_SIZE);

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* during initialization wlvअगर is शून्य */
	cmd->role_id = role_id;
	cmd->len = cpu_to_le16(buf_len);
	cmd->ढाँचा_type = ढाँचा_id;
	cmd->enabled_rates = cpu_to_le32(rates);
	cmd->लघु_retry_limit = wl->conf.tx.पंचांगpl_लघु_retry_limit;
	cmd->दीर्घ_retry_limit = wl->conf.tx.पंचांगpl_दीर्घ_retry_limit;
	cmd->index = index;

	अगर (buf)
		स_नकल(cmd->ढाँचा_data, buf, buf_len);

	ret = wl1271_cmd_send(wl, CMD_SET_TEMPLATE, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_warning("cmd set_template failed: %d", ret);
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(cmd);

out:
	वापस ret;
पूर्ण

पूर्णांक wl12xx_cmd_build_null_data(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक size;
	व्योम *ptr;
	पूर्णांक ret = -ENOMEM;


	अगर (wlvअगर->bss_type == BSS_TYPE_IBSS) अणु
		size = माप(काष्ठा wl12xx_null_data_ढाँचा);
		ptr = शून्य;
	पूर्ण अन्यथा अणु
		skb = ieee80211_nullfunc_get(wl->hw,
					     wl12xx_wlvअगर_to_vअगर(wlvअगर),
					     false);
		अगर (!skb)
			जाओ out;
		size = skb->len;
		ptr = skb->data;
	पूर्ण

	ret = wl1271_cmd_ढाँचा_set(wl, wlvअगर->role_id,
				      CMD_TEMPL_शून्य_DATA, ptr, size, 0,
				      wlvअगर->basic_rate);

out:
	dev_kमुक्त_skb(skb);
	अगर (ret)
		wl1271_warning("cmd build null data failed %d", ret);

	वापस ret;

पूर्ण

पूर्णांक wl12xx_cmd_build_klv_null_data(काष्ठा wl1271 *wl,
				   काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा ieee80211_vअगर *vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक ret = -ENOMEM;

	skb = ieee80211_nullfunc_get(wl->hw, vअगर, false);
	अगर (!skb)
		जाओ out;

	ret = wl1271_cmd_ढाँचा_set(wl, wlvअगर->role_id, CMD_TEMPL_KLV,
				      skb->data, skb->len,
				      wlvअगर->sta.klv_ढाँचा_id,
				      wlvअगर->basic_rate);

out:
	dev_kमुक्त_skb(skb);
	अगर (ret)
		wl1271_warning("cmd build klv null data failed %d", ret);

	वापस ret;

पूर्ण

पूर्णांक wl1271_cmd_build_ps_poll(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			     u16 aid)
अणु
	काष्ठा ieee80211_vअगर *vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);
	काष्ठा sk_buff *skb;
	पूर्णांक ret = 0;

	skb = ieee80211_pspoll_get(wl->hw, vअगर);
	अगर (!skb)
		जाओ out;

	ret = wl1271_cmd_ढाँचा_set(wl, wlvअगर->role_id,
				      CMD_TEMPL_PS_POLL, skb->data,
				      skb->len, 0, wlvअगर->basic_rate_set);

out:
	dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

पूर्णांक wl12xx_cmd_build_probe_req(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			       u8 role_id, u8 band,
			       स्थिर u8 *ssid, माप_प्रकार ssid_len,
			       स्थिर u8 *ie0, माप_प्रकार ie0_len, स्थिर u8 *ie1,
			       माप_प्रकार ie1_len, bool sched_scan)
अणु
	काष्ठा ieee80211_vअगर *vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);
	काष्ठा sk_buff *skb;
	पूर्णांक ret;
	u32 rate;
	u16 ढाँचा_id_2_4 = wl->scan_templ_id_2_4;
	u16 ढाँचा_id_5 = wl->scan_templ_id_5;

	wl1271_debug(DEBUG_SCAN, "build probe request band %d", band);

	skb = ieee80211_probereq_get(wl->hw, vअगर->addr, ssid, ssid_len,
				     ie0_len + ie1_len);
	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	अगर (ie0_len)
		skb_put_data(skb, ie0, ie0_len);
	अगर (ie1_len)
		skb_put_data(skb, ie1, ie1_len);

	अगर (sched_scan &&
	    (wl->quirks & WLCORE_QUIRK_DUAL_PROBE_TMPL)) अणु
		ढाँचा_id_2_4 = wl->sched_scan_templ_id_2_4;
		ढाँचा_id_5 = wl->sched_scan_templ_id_5;
	पूर्ण

	rate = wl1271_tx_min_rate_get(wl, wlvअगर->bitrate_masks[band]);
	अगर (band == NL80211_BAND_2GHZ)
		ret = wl1271_cmd_ढाँचा_set(wl, role_id,
					      ढाँचा_id_2_4,
					      skb->data, skb->len, 0, rate);
	अन्यथा
		ret = wl1271_cmd_ढाँचा_set(wl, role_id,
					      ढाँचा_id_5,
					      skb->data, skb->len, 0, rate);

out:
	dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wl12xx_cmd_build_probe_req);

काष्ठा sk_buff *wl1271_cmd_build_ap_probe_req(काष्ठा wl1271 *wl,
					      काष्ठा wl12xx_vअगर *wlvअगर,
					      काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_vअगर *vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);
	पूर्णांक ret;
	u32 rate;

	अगर (!skb)
		skb = ieee80211_ap_probereq_get(wl->hw, vअगर);
	अगर (!skb)
		जाओ out;

	wl1271_debug(DEBUG_SCAN, "set ap probe request template");

	rate = wl1271_tx_min_rate_get(wl, wlvअगर->bitrate_masks[wlvअगर->band]);
	अगर (wlvअगर->band == NL80211_BAND_2GHZ)
		ret = wl1271_cmd_ढाँचा_set(wl, wlvअगर->role_id,
					      CMD_TEMPL_CFG_PROBE_REQ_2_4,
					      skb->data, skb->len, 0, rate);
	अन्यथा
		ret = wl1271_cmd_ढाँचा_set(wl, wlvअगर->role_id,
					      CMD_TEMPL_CFG_PROBE_REQ_5,
					      skb->data, skb->len, 0, rate);

	अगर (ret < 0)
		wl1271_error("Unable to set ap probe request template.");

out:
	वापस skb;
पूर्ण

पूर्णांक wl1271_cmd_build_arp_rsp(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	पूर्णांक ret, extra = 0;
	u16 fc;
	काष्ठा ieee80211_vअगर *vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);
	काष्ठा sk_buff *skb;
	काष्ठा wl12xx_arp_rsp_ढाँचा *पंचांगpl;
	काष्ठा ieee80211_hdr_3addr *hdr;
	काष्ठा arphdr *arp_hdr;

	skb = dev_alloc_skb(माप(*hdr) + माप(__le16) + माप(*पंचांगpl) +
			    WL1271_EXTRA_SPACE_MAX);
	अगर (!skb) अणु
		wl1271_error("failed to allocate buffer for arp rsp template");
		वापस -ENOMEM;
	पूर्ण

	skb_reserve(skb, माप(*hdr) + WL1271_EXTRA_SPACE_MAX);

	पंचांगpl = skb_put_zero(skb, माप(*पंचांगpl));

	/* llc layer */
	स_नकल(पंचांगpl->llc_hdr, rfc1042_header, माप(rfc1042_header));
	पंचांगpl->llc_type = cpu_to_be16(ETH_P_ARP);

	/* arp header */
	arp_hdr = &पंचांगpl->arp_hdr;
	arp_hdr->ar_hrd = cpu_to_be16(ARPHRD_ETHER);
	arp_hdr->ar_pro = cpu_to_be16(ETH_P_IP);
	arp_hdr->ar_hln = ETH_ALEN;
	arp_hdr->ar_pln = 4;
	arp_hdr->ar_op = cpu_to_be16(ARPOP_REPLY);

	/* arp payload */
	स_नकल(पंचांगpl->sender_hw, vअगर->addr, ETH_ALEN);
	पंचांगpl->sender_ip = wlvअगर->ip_addr;

	/* encryption space */
	चयन (wlvअगर->encryption_type) अणु
	हाल KEY_TKIP:
		अगर (wl->quirks & WLCORE_QUIRK_TKIP_HEADER_SPACE)
			extra = WL1271_EXTRA_SPACE_TKIP;
		अवरोध;
	हाल KEY_AES:
		extra = WL1271_EXTRA_SPACE_AES;
		अवरोध;
	हाल KEY_NONE:
	हाल KEY_WEP:
	हाल KEY_GEM:
		extra = 0;
		अवरोध;
	शेष:
		wl1271_warning("Unknown encryption type: %d",
			       wlvअगर->encryption_type);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (extra) अणु
		u8 *space = skb_push(skb, extra);
		स_रखो(space, 0, extra);
	पूर्ण

	/* QoS header - BE */
	अगर (wlvअगर->sta.qos)
		स_रखो(skb_push(skb, माप(__le16)), 0, माप(__le16));

	/* mac80211 header */
	hdr = skb_push(skb, माप(*hdr));
	स_रखो(hdr, 0, माप(*hdr));
	fc = IEEE80211_FTYPE_DATA | IEEE80211_FCTL_TODS;
	अगर (wlvअगर->sta.qos)
		fc |= IEEE80211_STYPE_QOS_DATA;
	अन्यथा
		fc |= IEEE80211_STYPE_DATA;
	अगर (wlvअगर->encryption_type != KEY_NONE)
		fc |= IEEE80211_FCTL_PROTECTED;

	hdr->frame_control = cpu_to_le16(fc);
	स_नकल(hdr->addr1, vअगर->bss_conf.bssid, ETH_ALEN);
	स_नकल(hdr->addr2, vअगर->addr, ETH_ALEN);
	eth_broadcast_addr(hdr->addr3);

	ret = wl1271_cmd_ढाँचा_set(wl, wlvअगर->role_id, CMD_TEMPL_ARP_RSP,
				      skb->data, skb->len, 0,
				      wlvअगर->basic_rate);
out:
	dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

पूर्णांक wl1271_build_qos_null_data(काष्ठा wl1271 *wl, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	काष्ठा ieee80211_qos_hdr ढाँचा;

	स_रखो(&ढाँचा, 0, माप(ढाँचा));

	स_नकल(ढाँचा.addr1, vअगर->bss_conf.bssid, ETH_ALEN);
	स_नकल(ढाँचा.addr2, vअगर->addr, ETH_ALEN);
	स_नकल(ढाँचा.addr3, vअगर->bss_conf.bssid, ETH_ALEN);

	ढाँचा.frame_control = cpu_to_le16(IEEE80211_FTYPE_DATA |
					     IEEE80211_STYPE_QOS_शून्यFUNC |
					     IEEE80211_FCTL_TODS);

	/* FIXME: not sure what priority to use here */
	ढाँचा.qos_ctrl = cpu_to_le16(0);

	वापस wl1271_cmd_ढाँचा_set(wl, wlvअगर->role_id,
				       CMD_TEMPL_QOS_शून्य_DATA, &ढाँचा,
				       माप(ढाँचा), 0,
				       wlvअगर->basic_rate);
पूर्ण

पूर्णांक wl12xx_cmd_set_शेष_wep_key(काष्ठा wl1271 *wl, u8 id, u8 hlid)
अणु
	काष्ठा wl1271_cmd_set_keys *cmd;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd set_default_wep_key %d", id);

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	cmd->hlid = hlid;
	cmd->key_id = id;
	cmd->lid_key_type = WEP_DEFAULT_LID_TYPE;
	cmd->key_action = cpu_to_le16(KEY_SET_ID);
	cmd->key_type = KEY_WEP;

	ret = wl1271_cmd_send(wl, CMD_SET_KEYS, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_warning("cmd set_default_wep_key failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(cmd);

	वापस ret;
पूर्ण

पूर्णांक wl1271_cmd_set_sta_key(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
		       u16 action, u8 id, u8 key_type,
		       u8 key_size, स्थिर u8 *key, स्थिर u8 *addr,
		       u32 tx_seq_32, u16 tx_seq_16)
अणु
	काष्ठा wl1271_cmd_set_keys *cmd;
	पूर्णांक ret = 0;

	/* hlid might have alपढ़ोy been deleted */
	अगर (wlvअगर->sta.hlid == WL12XX_INVALID_LINK_ID)
		वापस 0;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	cmd->hlid = wlvअगर->sta.hlid;

	अगर (key_type == KEY_WEP)
		cmd->lid_key_type = WEP_DEFAULT_LID_TYPE;
	अन्यथा अगर (is_broadcast_ether_addr(addr))
		cmd->lid_key_type = BROADCAST_LID_TYPE;
	अन्यथा
		cmd->lid_key_type = UNICAST_LID_TYPE;

	cmd->key_action = cpu_to_le16(action);
	cmd->key_size = key_size;
	cmd->key_type = key_type;

	cmd->ac_seq_num16[0] = cpu_to_le16(tx_seq_16);
	cmd->ac_seq_num32[0] = cpu_to_le32(tx_seq_32);

	cmd->key_id = id;

	अगर (key_type == KEY_TKIP) अणु
		/*
		 * We get the key in the following क्रमm:
		 * TKIP (16 bytes) - TX MIC (8 bytes) - RX MIC (8 bytes)
		 * but the target is expecting:
		 * TKIP - RX MIC - TX MIC
		 */
		स_नकल(cmd->key, key, 16);
		स_नकल(cmd->key + 16, key + 24, 8);
		स_नकल(cmd->key + 24, key + 16, 8);

	पूर्ण अन्यथा अणु
		स_नकल(cmd->key, key, key_size);
	पूर्ण

	wl1271_dump(DEBUG_CRYPT, "TARGET KEY: ", cmd, माप(*cmd));

	ret = wl1271_cmd_send(wl, CMD_SET_KEYS, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_warning("could not set keys");
		जाओ out;
	पूर्ण

out:
	kमुक्त(cmd);

	वापस ret;
पूर्ण

/*
 * TODO: merge with sta/ibss पूर्णांकo 1 set_key function.
 * note there are slight dअगरfs
 */
पूर्णांक wl1271_cmd_set_ap_key(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			  u16 action, u8 id, u8 key_type,
			  u8 key_size, स्थिर u8 *key, u8 hlid, u32 tx_seq_32,
			  u16 tx_seq_16, bool is_pairwise)
अणु
	काष्ठा wl1271_cmd_set_keys *cmd;
	पूर्णांक ret = 0;
	u8 lid_type;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	अगर (hlid == wlvअगर->ap.bcast_hlid) अणु
		अगर (key_type == KEY_WEP)
			lid_type = WEP_DEFAULT_LID_TYPE;
		अन्यथा
			lid_type = BROADCAST_LID_TYPE;
	पूर्ण अन्यथा अगर (is_pairwise) अणु
		lid_type = UNICAST_LID_TYPE;
	पूर्ण अन्यथा अणु
		lid_type = BROADCAST_LID_TYPE;
	पूर्ण

	wl1271_debug(DEBUG_CRYPT, "ap key action: %d id: %d lid: %d type: %d"
		     " hlid: %d", (पूर्णांक)action, (पूर्णांक)id, (पूर्णांक)lid_type,
		     (पूर्णांक)key_type, (पूर्णांक)hlid);

	cmd->lid_key_type = lid_type;
	cmd->hlid = hlid;
	cmd->key_action = cpu_to_le16(action);
	cmd->key_size = key_size;
	cmd->key_type = key_type;
	cmd->key_id = id;
	cmd->ac_seq_num16[0] = cpu_to_le16(tx_seq_16);
	cmd->ac_seq_num32[0] = cpu_to_le32(tx_seq_32);

	अगर (key_type == KEY_TKIP) अणु
		/*
		 * We get the key in the following क्रमm:
		 * TKIP (16 bytes) - TX MIC (8 bytes) - RX MIC (8 bytes)
		 * but the target is expecting:
		 * TKIP - RX MIC - TX MIC
		 */
		स_नकल(cmd->key, key, 16);
		स_नकल(cmd->key + 16, key + 24, 8);
		स_नकल(cmd->key + 24, key + 16, 8);
	पूर्ण अन्यथा अणु
		स_नकल(cmd->key, key, key_size);
	पूर्ण

	wl1271_dump(DEBUG_CRYPT, "TARGET AP KEY: ", cmd, माप(*cmd));

	ret = wl1271_cmd_send(wl, CMD_SET_KEYS, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_warning("could not set ap keys");
		जाओ out;
	पूर्ण

out:
	kमुक्त(cmd);
	वापस ret;
पूर्ण

पूर्णांक wl12xx_cmd_set_peer_state(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			      u8 hlid)
अणु
	काष्ठा wl12xx_cmd_set_peer_state *cmd;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd set peer state (hlid=%d)", hlid);

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	cmd->hlid = hlid;
	cmd->state = WL1271_CMD_STA_STATE_CONNECTED;

	/* wmm param is valid only क्रम station role */
	अगर (wlvअगर->bss_type == BSS_TYPE_STA_BSS)
		cmd->wmm = wlvअगर->wmm_enabled;

	ret = wl1271_cmd_send(wl, CMD_SET_PEER_STATE, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to send set peer state command");
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(cmd);

out:
	वापस ret;
पूर्ण

पूर्णांक wl12xx_cmd_add_peer(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			काष्ठा ieee80211_sta *sta, u8 hlid)
अणु
	काष्ठा wl12xx_cmd_add_peer *cmd;
	पूर्णांक i, ret;
	u32 sta_rates;

	wl1271_debug(DEBUG_CMD, "cmd add peer %d", (पूर्णांक)hlid);

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	स_नकल(cmd->addr, sta->addr, ETH_ALEN);
	cmd->bss_index = WL1271_AP_BSS_INDEX;
	cmd->aid = sta->aid;
	cmd->hlid = hlid;
	cmd->sp_len = sta->max_sp;
	cmd->wmm = sta->wme ? 1 : 0;
	cmd->session_id = wl->session_ids[hlid];
	cmd->role_id = wlvअगर->role_id;

	क्रम (i = 0; i < NUM_ACCESS_CATEGORIES_COPY; i++)
		अगर (sta->wme && (sta->uapsd_queues & BIT(i)))
			cmd->psd_type[NUM_ACCESS_CATEGORIES_COPY-1-i] =
					WL1271_PSD_UPSD_TRIGGER;
		अन्यथा
			cmd->psd_type[NUM_ACCESS_CATEGORIES_COPY-1-i] =
					WL1271_PSD_LEGACY;


	sta_rates = sta->supp_rates[wlvअगर->band];
	अगर (sta->ht_cap.ht_supported)
		sta_rates |=
			(sta->ht_cap.mcs.rx_mask[0] << HW_HT_RATES_OFFSET) |
			(sta->ht_cap.mcs.rx_mask[1] << HW_MIMO_RATES_OFFSET);

	cmd->supported_rates =
		cpu_to_le32(wl1271_tx_enabled_rates_get(wl, sta_rates,
							wlvअगर->band));

	अगर (!cmd->supported_rates) अणु
		wl1271_debug(DEBUG_CMD,
			     "peer has no supported rates yet, configuring basic rates: 0x%x",
			     wlvअगर->basic_rate_set);
		cmd->supported_rates = cpu_to_le32(wlvअगर->basic_rate_set);
	पूर्ण

	wl1271_debug(DEBUG_CMD, "new peer rates=0x%x queues=0x%x",
		     cmd->supported_rates, sta->uapsd_queues);

	ret = wl1271_cmd_send(wl, CMD_ADD_PEER, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to initiate cmd add peer");
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(cmd);

out:
	वापस ret;
पूर्ण

पूर्णांक wl12xx_cmd_हटाओ_peer(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			   u8 hlid)
अणु
	काष्ठा wl12xx_cmd_हटाओ_peer *cmd;
	पूर्णांक ret;
	bool समयout = false;

	wl1271_debug(DEBUG_CMD, "cmd remove peer %d", (पूर्णांक)hlid);

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	cmd->hlid = hlid;
	/* We never send a deauth, mac80211 is in अक्षरge of this */
	cmd->reason_opcode = 0;
	cmd->send_deauth_flag = 0;
	cmd->role_id = wlvअगर->role_id;

	ret = wl1271_cmd_send(wl, CMD_REMOVE_PEER, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to initiate cmd remove peer");
		जाओ out_मुक्त;
	पूर्ण

	ret = wl->ops->रुको_क्रम_event(wl,
				      WLCORE_EVENT_PEER_REMOVE_COMPLETE,
				      &समयout);

	/*
	 * We are ok with a समयout here. The event is someबार not sent
	 * due to a firmware bug. In हाल of another error (like SDIO समयout)
	 * queue a recovery.
	 */
	अगर (ret)
		wl12xx_queue_recovery_work(wl);

out_मुक्त:
	kमुक्त(cmd);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wlcore_get_reg_conf_ch_idx(क्रमागत nl80211_band band, u16 ch)
अणु
	/*
	 * map the given band/channel to the respective predefined
	 * bit expected by the fw
	 */
	चयन (band) अणु
	हाल NL80211_BAND_2GHZ:
		/* channels 1..14 are mapped to 0..13 */
		अगर (ch >= 1 && ch <= 14)
			वापस ch - 1;
		अवरोध;
	हाल NL80211_BAND_5GHZ:
		चयन (ch) अणु
		हाल 8 ... 16:
			/* channels 8,12,16 are mapped to 18,19,20 */
			वापस 18 + (ch-8)/4;
		हाल 34 ... 48:
			/* channels 34,36..48 are mapped to 21..28 */
			वापस 21 + (ch-34)/2;
		हाल 52 ... 64:
			/* channels 52,56..64 are mapped to 29..32 */
			वापस 29 + (ch-52)/4;
		हाल 100 ... 140:
			/* channels 100,104..140 are mapped to 33..43 */
			वापस 33 + (ch-100)/4;
		हाल 149 ... 165:
			/* channels 149,153..165 are mapped to 44..48 */
			वापस 44 + (ch-149)/4;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	wl1271_error("%s: unknown band/channel: %d/%d", __func__, band, ch);
	वापस -1;
पूर्ण

व्योम wlcore_set_pending_regकरोमुख्य_ch(काष्ठा wl1271 *wl, u16 channel,
				     क्रमागत nl80211_band band)
अणु
	पूर्णांक ch_bit_idx = 0;

	अगर (!(wl->quirks & WLCORE_QUIRK_REGDOMAIN_CONF))
		वापस;

	ch_bit_idx = wlcore_get_reg_conf_ch_idx(band, channel);

	अगर (ch_bit_idx >= 0 && ch_bit_idx <= WL1271_MAX_CHANNELS)
		__set_bit_le(ch_bit_idx, (दीर्घ *)wl->reg_ch_conf_pending);
पूर्ण

पूर्णांक wlcore_cmd_regकरोमुख्य_config_locked(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl12xx_cmd_regकरोमुख्य_dfs_config *cmd = शून्य;
	पूर्णांक ret = 0, i, b, ch_bit_idx;
	__le32 पंचांगp_ch_biपंचांगap[2] __aligned(माप(अचिन्हित दीर्घ));
	काष्ठा wiphy *wiphy = wl->hw->wiphy;
	काष्ठा ieee80211_supported_band *band;
	bool समयout = false;

	अगर (!(wl->quirks & WLCORE_QUIRK_REGDOMAIN_CONF))
		वापस 0;

	wl1271_debug(DEBUG_CMD, "cmd reg domain config");

	स_नकल(पंचांगp_ch_biपंचांगap, wl->reg_ch_conf_pending, माप(पंचांगp_ch_biपंचांगap));

	क्रम (b = NL80211_BAND_2GHZ; b <= NL80211_BAND_5GHZ; b++) अणु
		band = wiphy->bands[b];
		क्रम (i = 0; i < band->n_channels; i++) अणु
			काष्ठा ieee80211_channel *channel = &band->channels[i];
			u16 ch = channel->hw_value;
			u32 flags = channel->flags;

			अगर (flags & (IEEE80211_CHAN_DISABLED |
				     IEEE80211_CHAN_NO_IR))
				जारी;

			अगर ((flags & IEEE80211_CHAN_RADAR) &&
			    channel->dfs_state != NL80211_DFS_AVAILABLE)
				जारी;

			ch_bit_idx = wlcore_get_reg_conf_ch_idx(b, ch);
			अगर (ch_bit_idx < 0)
				जारी;

			__set_bit_le(ch_bit_idx, (दीर्घ *)पंचांगp_ch_biपंचांगap);
		पूर्ण
	पूर्ण

	अगर (!स_भेद(पंचांगp_ch_biपंचांगap, wl->reg_ch_conf_last, माप(पंचांगp_ch_biपंचांगap)))
		जाओ out;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	cmd->ch_bit_map1 = पंचांगp_ch_biपंचांगap[0];
	cmd->ch_bit_map2 = पंचांगp_ch_biपंचांगap[1];
	cmd->dfs_region = wl->dfs_region;

	wl1271_debug(DEBUG_CMD,
		     "cmd reg domain bitmap1: 0x%08x, bitmap2: 0x%08x",
		     cmd->ch_bit_map1, cmd->ch_bit_map2);

	ret = wl1271_cmd_send(wl, CMD_DFS_CHANNEL_CONFIG, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to send reg domain dfs config");
		जाओ out;
	पूर्ण

	ret = wl->ops->रुको_क्रम_event(wl,
				      WLCORE_EVENT_DFS_CONFIG_COMPLETE,
				      &समयout);
	अगर (ret < 0 || समयout) अणु
		wl1271_error("reg domain conf %serror",
			     समयout ? "completion " : "");
		ret = समयout ? -ETIMEDOUT : ret;
		जाओ out;
	पूर्ण

	स_नकल(wl->reg_ch_conf_last, पंचांगp_ch_biपंचांगap, माप(पंचांगp_ch_biपंचांगap));
	स_रखो(wl->reg_ch_conf_pending, 0, माप(wl->reg_ch_conf_pending));

out:
	kमुक्त(cmd);
	वापस ret;
पूर्ण

पूर्णांक wl12xx_cmd_config_fwlog(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl12xx_cmd_config_fwlog *cmd;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd config firmware logger");

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	cmd->logger_mode = wl->conf.fwlog.mode;
	cmd->log_severity = wl->conf.fwlog.severity;
	cmd->बारtamp = wl->conf.fwlog.बारtamp;
	cmd->output = wl->conf.fwlog.output;
	cmd->threshold = wl->conf.fwlog.threshold;

	ret = wl1271_cmd_send(wl, CMD_CONFIG_FWLOGGER, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to send config firmware logger command");
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(cmd);

out:
	वापस ret;
पूर्ण

पूर्णांक wl12xx_cmd_start_fwlog(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl12xx_cmd_start_fwlog *cmd;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd start firmware logger");

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = wl1271_cmd_send(wl, CMD_START_FWLOGGER, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to send start firmware logger command");
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(cmd);

out:
	वापस ret;
पूर्ण

पूर्णांक wl12xx_cmd_stop_fwlog(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl12xx_cmd_stop_fwlog *cmd;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd stop firmware logger");

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = wl1271_cmd_send(wl, CMD_STOP_FWLOGGER, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to send stop firmware logger command");
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(cmd);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl12xx_cmd_roc(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			  u8 role_id, क्रमागत nl80211_band band, u8 channel)
अणु
	काष्ठा wl12xx_cmd_roc *cmd;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd roc %d (%d)", channel, role_id);

	अगर (WARN_ON(role_id == WL12XX_INVALID_ROLE_ID))
		वापस -EINVAL;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	cmd->role_id = role_id;
	cmd->channel = channel;
	चयन (band) अणु
	हाल NL80211_BAND_2GHZ:
		cmd->band = WLCORE_BAND_2_4GHZ;
		अवरोध;
	हाल NL80211_BAND_5GHZ:
		cmd->band = WLCORE_BAND_5GHZ;
		अवरोध;
	शेष:
		wl1271_error("roc - unknown band: %d", (पूर्णांक)wlvअगर->band);
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण


	ret = wl1271_cmd_send(wl, CMD_REMAIN_ON_CHANNEL, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to send ROC command");
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(cmd);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl12xx_cmd_croc(काष्ठा wl1271 *wl, u8 role_id)
अणु
	काष्ठा wl12xx_cmd_croc *cmd;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd croc (%d)", role_id);

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	cmd->role_id = role_id;

	ret = wl1271_cmd_send(wl, CMD_CANCEL_REMAIN_ON_CHANNEL, cmd,
			      माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to send ROC command");
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(cmd);

out:
	वापस ret;
पूर्ण

पूर्णांक wl12xx_roc(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर, u8 role_id,
	       क्रमागत nl80211_band band, u8 channel)
अणु
	पूर्णांक ret = 0;

	अगर (WARN_ON(test_bit(role_id, wl->roc_map)))
		वापस 0;

	ret = wl12xx_cmd_roc(wl, wlvअगर, role_id, band, channel);
	अगर (ret < 0)
		जाओ out;

	__set_bit(role_id, wl->roc_map);
out:
	वापस ret;
पूर्ण

पूर्णांक wl12xx_croc(काष्ठा wl1271 *wl, u8 role_id)
अणु
	पूर्णांक ret = 0;

	अगर (WARN_ON(!test_bit(role_id, wl->roc_map)))
		वापस 0;

	ret = wl12xx_cmd_croc(wl, role_id);
	अगर (ret < 0)
		जाओ out;

	__clear_bit(role_id, wl->roc_map);

	/*
	 * Rearm the tx watchकरोg when removing the last ROC. This prevents
	 * recoveries due to just finished ROCs - when Tx hasn't yet had
	 * a chance to get out.
	 */
	अगर (find_first_bit(wl->roc_map, WL12XX_MAX_ROLES) >= WL12XX_MAX_ROLES)
		wl12xx_rearm_tx_watchकरोg_locked(wl);
out:
	वापस ret;
पूर्ण

पूर्णांक wl12xx_cmd_stop_channel_चयन(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा wl12xx_cmd_stop_channel_चयन *cmd;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "cmd stop channel switch");

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	cmd->role_id = wlvअगर->role_id;

	ret = wl1271_cmd_send(wl, CMD_STOP_CHANNEL_SWICTH, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to stop channel switch command");
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(cmd);

out:
	वापस ret;
पूर्ण

/* start dev role and roc on its channel */
पूर्णांक wl12xx_start_dev(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
		     क्रमागत nl80211_band band, पूर्णांक channel)
अणु
	पूर्णांक ret;

	अगर (WARN_ON(!(wlvअगर->bss_type == BSS_TYPE_STA_BSS ||
		      wlvअगर->bss_type == BSS_TYPE_IBSS)))
		वापस -EINVAL;

	/* the dev role is alपढ़ोy started क्रम p2p mgmt पूर्णांकerfaces */
	अगर (!wlcore_is_p2p_mgmt(wlvअगर)) अणु
		ret = wl12xx_cmd_role_enable(wl,
					     wl12xx_wlvअगर_to_vअगर(wlvअगर)->addr,
					     WL1271_ROLE_DEVICE,
					     &wlvअगर->dev_role_id);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	ret = wl12xx_cmd_role_start_dev(wl, wlvअगर, band, channel);
	अगर (ret < 0)
		जाओ out_disable;

	ret = wl12xx_roc(wl, wlvअगर, wlvअगर->dev_role_id, band, channel);
	अगर (ret < 0)
		जाओ out_stop;

	वापस 0;

out_stop:
	wl12xx_cmd_role_stop_dev(wl, wlvअगर);
out_disable:
	अगर (!wlcore_is_p2p_mgmt(wlvअगर))
		wl12xx_cmd_role_disable(wl, &wlvअगर->dev_role_id);
out:
	वापस ret;
पूर्ण

/* croc dev hlid, and stop the role */
पूर्णांक wl12xx_stop_dev(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	पूर्णांक ret;

	अगर (WARN_ON(!(wlvअगर->bss_type == BSS_TYPE_STA_BSS ||
		      wlvअगर->bss_type == BSS_TYPE_IBSS)))
		वापस -EINVAL;

	/* flush all pending packets */
	ret = wlcore_tx_work_locked(wl);
	अगर (ret < 0)
		जाओ out;

	अगर (test_bit(wlvअगर->dev_role_id, wl->roc_map)) अणु
		ret = wl12xx_croc(wl, wlvअगर->dev_role_id);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	ret = wl12xx_cmd_role_stop_dev(wl, wlvअगर);
	अगर (ret < 0)
		जाओ out;

	अगर (!wlcore_is_p2p_mgmt(wlvअगर)) अणु
		ret = wl12xx_cmd_role_disable(wl, &wlvअगर->dev_role_id);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण

पूर्णांक wlcore_cmd_generic_cfg(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			   u8 feature, u8 enable, u8 value)
अणु
	काष्ठा wlcore_cmd_generic_cfg *cmd;
	पूर्णांक ret;

	wl1271_debug(DEBUG_CMD,
		     "cmd generic cfg (role %d feature %d enable %d value %d)",
		     wlvअगर->role_id, feature, enable, value);

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->role_id = wlvअगर->role_id;
	cmd->feature = feature;
	cmd->enable = enable;
	cmd->value = value;

	ret = wl1271_cmd_send(wl, CMD_GENERIC_CFG, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to send generic cfg command");
		जाओ out_मुक्त;
	पूर्ण
out_मुक्त:
	kमुक्त(cmd);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_cmd_generic_cfg);
