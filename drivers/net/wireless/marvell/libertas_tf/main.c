<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2008, cozybit Inc.
 *  Copyright (C) 2003-2006, Marvell International Ltd.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/hardirq.h>
#समावेश <linux/slab.h>

#समावेश <linux/etherdevice.h>
#समावेश <linux/module.h>
#समावेश "libertas_tf.h"

/* thinfirm version: 5.132.X.pX */
#घोषणा LBTF_FW_VER_MIN		0x05840300
#घोषणा LBTF_FW_VER_MAX		0x0584ffff

/* Module parameters */
अचिन्हित पूर्णांक lbtf_debug;
EXPORT_SYMBOL_GPL(lbtf_debug);
module_param_named(libertas_tf_debug, lbtf_debug, पूर्णांक, 0644);

काष्ठा workqueue_काष्ठा *lbtf_wq;

अटल स्थिर काष्ठा ieee80211_channel lbtf_channels[] = अणु
	अणु .center_freq = 2412, .hw_value = 1 पूर्ण,
	अणु .center_freq = 2417, .hw_value = 2 पूर्ण,
	अणु .center_freq = 2422, .hw_value = 3 पूर्ण,
	अणु .center_freq = 2427, .hw_value = 4 पूर्ण,
	अणु .center_freq = 2432, .hw_value = 5 पूर्ण,
	अणु .center_freq = 2437, .hw_value = 6 पूर्ण,
	अणु .center_freq = 2442, .hw_value = 7 पूर्ण,
	अणु .center_freq = 2447, .hw_value = 8 पूर्ण,
	अणु .center_freq = 2452, .hw_value = 9 पूर्ण,
	अणु .center_freq = 2457, .hw_value = 10 पूर्ण,
	अणु .center_freq = 2462, .hw_value = 11 पूर्ण,
	अणु .center_freq = 2467, .hw_value = 12 पूर्ण,
	अणु .center_freq = 2472, .hw_value = 13 पूर्ण,
	अणु .center_freq = 2484, .hw_value = 14 पूर्ण,
पूर्ण;

/* This table contains the hardware specअगरic values क्रम the modulation rates. */
अटल स्थिर काष्ठा ieee80211_rate lbtf_rates[] = अणु
	अणु .bitrate = 10,
	  .hw_value = 0, पूर्ण,
	अणु .bitrate = 20,
	  .hw_value = 1,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 55,
	  .hw_value = 2,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 110,
	  .hw_value = 3,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 60,
	  .hw_value = 5,
	  .flags = 0 पूर्ण,
	अणु .bitrate = 90,
	  .hw_value = 6,
	  .flags = 0 पूर्ण,
	अणु .bitrate = 120,
	  .hw_value = 7,
	  .flags = 0 पूर्ण,
	अणु .bitrate = 180,
	  .hw_value = 8,
	  .flags = 0 पूर्ण,
	अणु .bitrate = 240,
	  .hw_value = 9,
	  .flags = 0 पूर्ण,
	अणु .bitrate = 360,
	  .hw_value = 10,
	  .flags = 0 पूर्ण,
	अणु .bitrate = 480,
	  .hw_value = 11,
	  .flags = 0 पूर्ण,
	अणु .bitrate = 540,
	  .hw_value = 12,
	  .flags = 0 पूर्ण,
पूर्ण;

अटल व्योम lbtf_cmd_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lbtf_निजी *priv = container_of(work, काष्ठा lbtf_निजी,
					 cmd_work);

	lbtf_deb_enter(LBTF_DEB_CMD);

	spin_lock_irq(&priv->driver_lock);
	/* command response? */
	अगर (priv->cmd_response_rxed) अणु
		priv->cmd_response_rxed = 0;
		spin_unlock_irq(&priv->driver_lock);
		lbtf_process_rx_command(priv);
		spin_lock_irq(&priv->driver_lock);
	पूर्ण

	अगर (priv->cmd_समयd_out && priv->cur_cmd) अणु
		काष्ठा cmd_ctrl_node *cmdnode = priv->cur_cmd;

		अगर (++priv->nr_retries > 10) अणु
			lbtf_complete_command(priv, cmdnode,
					      -ETIMEDOUT);
			priv->nr_retries = 0;
		पूर्ण अन्यथा अणु
			priv->cur_cmd = शून्य;

			/* Stick it back at the _top_ of the pending
			 * queue क्रम immediate resubmission */
			list_add(&cmdnode->list, &priv->cmdpendingq);
		पूर्ण
	पूर्ण
	priv->cmd_समयd_out = 0;
	spin_unlock_irq(&priv->driver_lock);

	/* Execute the next command */
	अगर (!priv->cur_cmd)
		lbtf_execute_next_command(priv);

	lbtf_deb_leave(LBTF_DEB_CMD);
पूर्ण

/*
 *  This function handles the समयout of command sending.
 *  It will re-send the same command again.
 */
अटल व्योम command_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा lbtf_निजी *priv = from_समयr(priv, t, command_समयr);
	अचिन्हित दीर्घ flags;
	lbtf_deb_enter(LBTF_DEB_CMD);

	spin_lock_irqsave(&priv->driver_lock, flags);

	अगर (!priv->cur_cmd) अणु
		prपूर्णांकk(KERN_DEBUG "libertastf: command timer expired; "
				  "no pending command\n");
		जाओ out;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "libertas: command %x timed out\n",
		le16_to_cpu(priv->cur_cmd->cmdbuf->command));

	priv->cmd_समयd_out = 1;
	queue_work(lbtf_wq, &priv->cmd_work);
out:
	spin_unlock_irqrestore(&priv->driver_lock, flags);
	lbtf_deb_leave(LBTF_DEB_CMD);
पूर्ण

अटल पूर्णांक lbtf_init_adapter(काष्ठा lbtf_निजी *priv)
अणु
	lbtf_deb_enter(LBTF_DEB_MAIN);
	eth_broadcast_addr(priv->current_addr);
	mutex_init(&priv->lock);

	priv->vअगर = शून्य;
	समयr_setup(&priv->command_समयr, command_समयr_fn, 0);

	INIT_LIST_HEAD(&priv->cmdमुक्तq);
	INIT_LIST_HEAD(&priv->cmdpendingq);

	spin_lock_init(&priv->driver_lock);

	/* Allocate the command buffers */
	अगर (lbtf_allocate_cmd_buffer(priv))
		वापस -1;

	lbtf_deb_leave(LBTF_DEB_MAIN);
	वापस 0;
पूर्ण

अटल व्योम lbtf_मुक्त_adapter(काष्ठा lbtf_निजी *priv)
अणु
	lbtf_deb_enter(LBTF_DEB_MAIN);
	lbtf_मुक्त_cmd_buffer(priv);
	del_समयr(&priv->command_समयr);
	lbtf_deb_leave(LBTF_DEB_MAIN);
पूर्ण

अटल व्योम lbtf_op_tx(काष्ठा ieee80211_hw *hw,
		       काष्ठा ieee80211_tx_control *control,
		       काष्ठा sk_buff *skb)
अणु
	काष्ठा lbtf_निजी *priv = hw->priv;

	priv->skb_to_tx = skb;
	queue_work(lbtf_wq, &priv->tx_work);
	/*
	 * queue will be restarted when we receive transmission feedback अगर
	 * there are no buffered multicast frames to send
	 */
	ieee80211_stop_queues(priv->hw);
पूर्ण

अटल व्योम lbtf_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lbtf_निजी *priv = container_of(work, काष्ठा lbtf_निजी,
					 tx_work);
	अचिन्हित पूर्णांक len;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा txpd *txpd;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक err;

	lbtf_deb_enter(LBTF_DEB_MACOPS | LBTF_DEB_TX);

	अगर ((priv->vअगर->type == NL80211_IFTYPE_AP) &&
	    (!skb_queue_empty(&priv->bc_ps_buf)))
		skb = skb_dequeue(&priv->bc_ps_buf);
	अन्यथा अगर (priv->skb_to_tx) अणु
		skb = priv->skb_to_tx;
		priv->skb_to_tx = शून्य;
	पूर्ण अन्यथा अणु
		lbtf_deb_leave(LBTF_DEB_MACOPS | LBTF_DEB_TX);
		वापस;
	पूर्ण

	len = skb->len;
	info  = IEEE80211_SKB_CB(skb);
	txpd = skb_push(skb, माप(काष्ठा txpd));

	अगर (priv->surpriseहटाओd) अणु
		dev_kमुक्त_skb_any(skb);
		lbtf_deb_leave(LBTF_DEB_MACOPS | LBTF_DEB_TX);
		वापस;
	पूर्ण

	स_रखो(txpd, 0, माप(काष्ठा txpd));
	/* Activate per-packet rate selection */
	txpd->tx_control |= cpu_to_le32(MRVL_PER_PACKET_RATE |
			     ieee80211_get_tx_rate(priv->hw, info)->hw_value);

	/* copy destination address from 802.11 header */
	स_नकल(txpd->tx_dest_addr_high, skb->data + माप(काष्ठा txpd) + 4,
		ETH_ALEN);
	txpd->tx_packet_length = cpu_to_le16(len);
	txpd->tx_packet_location = cpu_to_le32(माप(काष्ठा txpd));
	lbtf_deb_hex(LBTF_DEB_TX, "TX Data", skb->data, min_t(अचिन्हित पूर्णांक, skb->len, 100));
	BUG_ON(priv->tx_skb);
	spin_lock_irq(&priv->driver_lock);
	priv->tx_skb = skb;
	err = priv->ops->hw_host_to_card(priv, MVMS_DAT, skb->data, skb->len);
	spin_unlock_irq(&priv->driver_lock);
	अगर (err) अणु
		dev_kमुक्त_skb_any(skb);
		priv->tx_skb = शून्य;
		pr_err("TX error: %d", err);
	पूर्ण
	lbtf_deb_leave(LBTF_DEB_MACOPS | LBTF_DEB_TX);
पूर्ण

अटल पूर्णांक lbtf_op_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा lbtf_निजी *priv = hw->priv;

	lbtf_deb_enter(LBTF_DEB_MACOPS);

	priv->capability = WLAN_CAPABILITY_SHORT_PREAMBLE;
	priv->radioon = RADIO_ON;
	priv->mac_control = CMD_ACT_MAC_RX_ON | CMD_ACT_MAC_TX_ON;
	lbtf_set_mac_control(priv);
	lbtf_set_radio_control(priv);

	lbtf_deb_leave(LBTF_DEB_MACOPS);
	वापस 0;
पूर्ण

अटल व्योम lbtf_op_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा lbtf_निजी *priv = hw->priv;
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *skb;

	काष्ठा cmd_ctrl_node *cmdnode;

	lbtf_deb_enter(LBTF_DEB_MACOPS);

	/* Flush pending command nodes */
	spin_lock_irqsave(&priv->driver_lock, flags);
	list_क्रम_each_entry(cmdnode, &priv->cmdpendingq, list) अणु
		cmdnode->result = -ENOENT;
		cmdnode->cmdरुकोqwoken = 1;
		wake_up_पूर्णांकerruptible(&cmdnode->cmdरुको_q);
	पूर्ण

	spin_unlock_irqrestore(&priv->driver_lock, flags);
	cancel_work_sync(&priv->cmd_work);
	cancel_work_sync(&priv->tx_work);
	जबतक ((skb = skb_dequeue(&priv->bc_ps_buf)))
		dev_kमुक्त_skb_any(skb);
	priv->radioon = RADIO_OFF;
	lbtf_set_radio_control(priv);

	lbtf_deb_leave(LBTF_DEB_MACOPS);
पूर्ण

अटल पूर्णांक lbtf_op_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
			काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा lbtf_निजी *priv = hw->priv;
	lbtf_deb_enter(LBTF_DEB_MACOPS);
	अगर (priv->vअगर != शून्य)
		वापस -EOPNOTSUPP;

	priv->vअगर = vअगर;
	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_AP:
		lbtf_set_mode(priv, LBTF_AP_MODE);
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		lbtf_set_mode(priv, LBTF_STA_MODE);
		अवरोध;
	शेष:
		priv->vअगर = शून्य;
		वापस -EOPNOTSUPP;
	पूर्ण
	lbtf_set_mac_address(priv, (u8 *) vअगर->addr);
	lbtf_deb_leave(LBTF_DEB_MACOPS);
	वापस 0;
पूर्ण

अटल व्योम lbtf_op_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
			काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा lbtf_निजी *priv = hw->priv;
	lbtf_deb_enter(LBTF_DEB_MACOPS);

	अगर (priv->vअगर->type == NL80211_IFTYPE_AP ||
	    priv->vअगर->type == NL80211_IFTYPE_MESH_POINT)
		lbtf_beacon_ctrl(priv, 0, 0);
	lbtf_set_mode(priv, LBTF_PASSIVE_MODE);
	lbtf_set_bssid(priv, 0, शून्य);
	priv->vअगर = शून्य;
	lbtf_deb_leave(LBTF_DEB_MACOPS);
पूर्ण

अटल पूर्णांक lbtf_op_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा lbtf_निजी *priv = hw->priv;
	काष्ठा ieee80211_conf *conf = &hw->conf;
	lbtf_deb_enter(LBTF_DEB_MACOPS);

	अगर (conf->chandef.chan->center_freq != priv->cur_freq) अणु
		priv->cur_freq = conf->chandef.chan->center_freq;
		lbtf_set_channel(priv, conf->chandef.chan->hw_value);
	पूर्ण
	lbtf_deb_leave(LBTF_DEB_MACOPS);
	वापस 0;
पूर्ण

अटल u64 lbtf_op_prepare_multicast(काष्ठा ieee80211_hw *hw,
				     काष्ठा netdev_hw_addr_list *mc_list)
अणु
	काष्ठा lbtf_निजी *priv = hw->priv;
	पूर्णांक i;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक mc_count = netdev_hw_addr_list_count(mc_list);

	अगर (!mc_count || mc_count > MRVDRV_MAX_MULTICAST_LIST_SIZE)
		वापस mc_count;

	priv->nr_of_multicasपंचांगacaddr = mc_count;
	i = 0;
	netdev_hw_addr_list_क्रम_each(ha, mc_list)
		स_नकल(&priv->multicastlist[i++], ha->addr, ETH_ALEN);

	वापस mc_count;
पूर्ण

#घोषणा SUPPORTED_FIF_FLAGS  FIF_ALLMULTI
अटल व्योम lbtf_op_configure_filter(काष्ठा ieee80211_hw *hw,
			अचिन्हित पूर्णांक changed_flags,
			अचिन्हित पूर्णांक *new_flags,
			u64 multicast)
अणु
	काष्ठा lbtf_निजी *priv = hw->priv;
	पूर्णांक old_mac_control = priv->mac_control;

	lbtf_deb_enter(LBTF_DEB_MACOPS);

	changed_flags &= SUPPORTED_FIF_FLAGS;
	*new_flags &= SUPPORTED_FIF_FLAGS;

	अगर (!changed_flags) अणु
		lbtf_deb_leave(LBTF_DEB_MACOPS);
		वापस;
	पूर्ण

	priv->mac_control &= ~CMD_ACT_MAC_PROMISCUOUS_ENABLE;
	अगर (*new_flags & (FIF_ALLMULTI) ||
	    multicast > MRVDRV_MAX_MULTICAST_LIST_SIZE) अणु
		priv->mac_control |= CMD_ACT_MAC_ALL_MULTICAST_ENABLE;
		priv->mac_control &= ~CMD_ACT_MAC_MULTICAST_ENABLE;
	पूर्ण अन्यथा अगर (multicast) अणु
		priv->mac_control |= CMD_ACT_MAC_MULTICAST_ENABLE;
		priv->mac_control &= ~CMD_ACT_MAC_ALL_MULTICAST_ENABLE;
		lbtf_cmd_set_mac_multicast_addr(priv);
	पूर्ण अन्यथा अणु
		priv->mac_control &= ~(CMD_ACT_MAC_MULTICAST_ENABLE |
				       CMD_ACT_MAC_ALL_MULTICAST_ENABLE);
		अगर (priv->nr_of_multicasपंचांगacaddr) अणु
			priv->nr_of_multicasपंचांगacaddr = 0;
			lbtf_cmd_set_mac_multicast_addr(priv);
		पूर्ण
	पूर्ण


	अगर (priv->mac_control != old_mac_control)
		lbtf_set_mac_control(priv);

	lbtf_deb_leave(LBTF_DEB_MACOPS);
पूर्ण

अटल व्योम lbtf_op_bss_info_changed(काष्ठा ieee80211_hw *hw,
			काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_bss_conf *bss_conf,
			u32 changes)
अणु
	काष्ठा lbtf_निजी *priv = hw->priv;
	काष्ठा sk_buff *beacon;
	lbtf_deb_enter(LBTF_DEB_MACOPS);

	अगर (changes & (BSS_CHANGED_BEACON | BSS_CHANGED_BEACON_INT)) अणु
		चयन (priv->vअगर->type) अणु
		हाल NL80211_IFTYPE_AP:
		हाल NL80211_IFTYPE_MESH_POINT:
			beacon = ieee80211_beacon_get(hw, vअगर);
			अगर (beacon) अणु
				lbtf_beacon_set(priv, beacon);
				kमुक्त_skb(beacon);
				lbtf_beacon_ctrl(priv, 1,
						 bss_conf->beacon_पूर्णांक);
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (changes & BSS_CHANGED_BSSID) अणु
		bool activate = !is_zero_ether_addr(bss_conf->bssid);
		lbtf_set_bssid(priv, activate, bss_conf->bssid);
	पूर्ण

	अगर (changes & BSS_CHANGED_ERP_PREAMBLE) अणु
		अगर (bss_conf->use_लघु_preamble)
			priv->preamble = CMD_TYPE_SHORT_PREAMBLE;
		अन्यथा
			priv->preamble = CMD_TYPE_LONG_PREAMBLE;
		lbtf_set_radio_control(priv);
	पूर्ण

	lbtf_deb_leave(LBTF_DEB_MACOPS);
पूर्ण

अटल पूर्णांक lbtf_op_get_survey(काष्ठा ieee80211_hw *hw, पूर्णांक idx,
				काष्ठा survey_info *survey)
अणु
	काष्ठा lbtf_निजी *priv = hw->priv;
	काष्ठा ieee80211_conf *conf = &hw->conf;

	अगर (idx != 0)
		वापस -ENOENT;

	survey->channel = conf->chandef.chan;
	survey->filled = SURVEY_INFO_NOISE_DBM;
	survey->noise = priv->noise;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops lbtf_ops = अणु
	.tx			= lbtf_op_tx,
	.start			= lbtf_op_start,
	.stop			= lbtf_op_stop,
	.add_पूर्णांकerface		= lbtf_op_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= lbtf_op_हटाओ_पूर्णांकerface,
	.config			= lbtf_op_config,
	.prepare_multicast	= lbtf_op_prepare_multicast,
	.configure_filter	= lbtf_op_configure_filter,
	.bss_info_changed	= lbtf_op_bss_info_changed,
	.get_survey		= lbtf_op_get_survey,
पूर्ण;

पूर्णांक lbtf_rx(काष्ठा lbtf_निजी *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_rx_status stats;
	काष्ठा rxpd *prxpd;
	पूर्णांक need_padding;
	काष्ठा ieee80211_hdr *hdr;

	lbtf_deb_enter(LBTF_DEB_RX);

	अगर (priv->radioon != RADIO_ON) अणु
		lbtf_deb_rx("rx before we turned on the radio");
		जाओ करोne;
	पूर्ण

	prxpd = (काष्ठा rxpd *) skb->data;

	स_रखो(&stats, 0, माप(stats));
	अगर (!(prxpd->status & cpu_to_le16(MRVDRV_RXPD_STATUS_OK)))
		stats.flag |= RX_FLAG_FAILED_FCS_CRC;
	stats.freq = priv->cur_freq;
	stats.band = NL80211_BAND_2GHZ;
	stats.संकेत = prxpd->snr - prxpd->nf;
	priv->noise = prxpd->nf;
	/* Marvell rate index has a hole at value 4 */
	अगर (prxpd->rx_rate > 4)
		--prxpd->rx_rate;
	stats.rate_idx = prxpd->rx_rate;
	skb_pull(skb, माप(काष्ठा rxpd));

	hdr = (काष्ठा ieee80211_hdr *)skb->data;

	need_padding = ieee80211_is_data_qos(hdr->frame_control);
	need_padding ^= ieee80211_has_a4(hdr->frame_control);
	need_padding ^= ieee80211_is_data_qos(hdr->frame_control) &&
			(*ieee80211_get_qos_ctl(hdr) &
			 IEEE80211_QOS_CTL_A_MSDU_PRESENT);

	अगर (need_padding) अणु
		स_हटाओ(skb->data + 2, skb->data, skb->len);
		skb_reserve(skb, 2);
	पूर्ण

	स_नकल(IEEE80211_SKB_RXCB(skb), &stats, माप(stats));

	lbtf_deb_rx("rx data: skb->len-sizeof(RxPd) = %d-%zd = %zd\n",
	       skb->len, माप(काष्ठा rxpd), skb->len - माप(काष्ठा rxpd));
	lbtf_deb_hex(LBTF_DEB_RX, "RX Data", skb->data,
	             min_t(अचिन्हित पूर्णांक, skb->len, 100));

	ieee80211_rx_irqsafe(priv->hw, skb);

करोne:
	lbtf_deb_leave(LBTF_DEB_RX);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(lbtf_rx);

/*
 * lbtf_add_card: Add and initialize the card.
 *
 *  Returns: poपूर्णांकer to काष्ठा lbtf_priv.
 */
काष्ठा lbtf_निजी *lbtf_add_card(व्योम *card, काष्ठा device *dmdev,
				   स्थिर काष्ठा lbtf_ops *ops)
अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा lbtf_निजी *priv = शून्य;

	lbtf_deb_enter(LBTF_DEB_MAIN);

	hw = ieee80211_alloc_hw(माप(काष्ठा lbtf_निजी), &lbtf_ops);
	अगर (!hw)
		जाओ करोne;

	priv = hw->priv;
	अगर (lbtf_init_adapter(priv))
		जाओ err_init_adapter;

	priv->hw = hw;
	priv->card = card;
	priv->ops = ops;
	priv->tx_skb = शून्य;
	priv->radioon = RADIO_OFF;

	hw->queues = 1;
	ieee80211_hw_set(hw, HOST_BROADCAST_PS_BUFFERING);
	ieee80211_hw_set(hw, SIGNAL_DBM);
	hw->extra_tx_headroom = माप(काष्ठा txpd);
	स_नकल(priv->channels, lbtf_channels, माप(lbtf_channels));
	स_नकल(priv->rates, lbtf_rates, माप(lbtf_rates));
	priv->band.n_bitrates = ARRAY_SIZE(lbtf_rates);
	priv->band.bitrates = priv->rates;
	priv->band.n_channels = ARRAY_SIZE(lbtf_channels);
	priv->band.channels = priv->channels;
	hw->wiphy->bands[NL80211_BAND_2GHZ] = &priv->band;
	hw->wiphy->पूर्णांकerface_modes =
		BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_ADHOC);
	skb_queue_head_init(&priv->bc_ps_buf);

	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	SET_IEEE80211_DEV(hw, dmdev);

	INIT_WORK(&priv->cmd_work, lbtf_cmd_work);
	INIT_WORK(&priv->tx_work, lbtf_tx_work);

	अगर (priv->ops->hw_prog_firmware(priv)) अणु
		lbtf_deb_usbd(dmdev, "Error programming the firmware\n");
		priv->ops->hw_reset_device(priv);
		जाओ err_init_adapter;
	पूर्ण

	eth_broadcast_addr(priv->current_addr);
	अगर (lbtf_update_hw_spec(priv))
		जाओ err_init_adapter;

	अगर (priv->fwrelease < LBTF_FW_VER_MIN ||
	    priv->fwrelease > LBTF_FW_VER_MAX) अणु
		जाओ err_init_adapter;
	पूर्ण

	/* The firmware seems to start with the radio enabled. Turn it
	 * off beक्रमe an actual mac80211 start callback is invoked.
	 */
	lbtf_set_radio_control(priv);

	अगर (ieee80211_रेजिस्टर_hw(hw))
		जाओ err_init_adapter;

	dev_info(dmdev, "libertastf: Marvell WLAN 802.11 thinfirm adapter\n");
	जाओ करोne;

err_init_adapter:
	lbtf_मुक्त_adapter(priv);
	ieee80211_मुक्त_hw(hw);
	priv = शून्य;

करोne:
	lbtf_deb_leave_args(LBTF_DEB_MAIN, "priv %p", priv);
	वापस priv;
पूर्ण
EXPORT_SYMBOL_GPL(lbtf_add_card);


पूर्णांक lbtf_हटाओ_card(काष्ठा lbtf_निजी *priv)
अणु
	काष्ठा ieee80211_hw *hw = priv->hw;

	lbtf_deb_enter(LBTF_DEB_MAIN);

	priv->surpriseहटाओd = 1;
	del_समयr(&priv->command_समयr);
	lbtf_मुक्त_adapter(priv);
	priv->hw = शून्य;
	ieee80211_unरेजिस्टर_hw(hw);
	ieee80211_मुक्त_hw(hw);

	lbtf_deb_leave(LBTF_DEB_MAIN);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(lbtf_हटाओ_card);

व्योम lbtf_send_tx_feedback(काष्ठा lbtf_निजी *priv, u8 retrycnt, u8 fail)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(priv->tx_skb);

	ieee80211_tx_info_clear_status(info);
	/*
	 * Commented out, otherwise we never go beyond 1Mbit/s using mac80211
	 * शेष pid rc algorithm.
	 *
	 * info->status.retry_count = MRVL_DEFAULT_RETRIES - retrycnt;
	 */
	अगर (!(info->flags & IEEE80211_TX_CTL_NO_ACK) && !fail)
		info->flags |= IEEE80211_TX_STAT_ACK;
	skb_pull(priv->tx_skb, माप(काष्ठा txpd));
	ieee80211_tx_status_irqsafe(priv->hw, priv->tx_skb);
	priv->tx_skb = शून्य;
	अगर (!priv->skb_to_tx && skb_queue_empty(&priv->bc_ps_buf))
		ieee80211_wake_queues(priv->hw);
	अन्यथा
		queue_work(lbtf_wq, &priv->tx_work);
पूर्ण
EXPORT_SYMBOL_GPL(lbtf_send_tx_feedback);

व्योम lbtf_bcn_sent(काष्ठा lbtf_निजी *priv)
अणु
	काष्ठा sk_buff *skb = शून्य;

	अगर (priv->vअगर->type != NL80211_IFTYPE_AP)
		वापस;

	अगर (skb_queue_empty(&priv->bc_ps_buf)) अणु
		bool tx_buff_bc = false;

		जबतक ((skb = ieee80211_get_buffered_bc(priv->hw, priv->vअगर))) अणु
			skb_queue_tail(&priv->bc_ps_buf, skb);
			tx_buff_bc = true;
		पूर्ण
		अगर (tx_buff_bc) अणु
			ieee80211_stop_queues(priv->hw);
			queue_work(lbtf_wq, &priv->tx_work);
		पूर्ण
	पूर्ण

	skb = ieee80211_beacon_get(priv->hw, priv->vअगर);

	अगर (skb) अणु
		lbtf_beacon_set(priv, skb);
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(lbtf_bcn_sent);

अटल पूर्णांक __init lbtf_init_module(व्योम)
अणु
	lbtf_deb_enter(LBTF_DEB_MAIN);
	lbtf_wq = alloc_workqueue("libertastf", WQ_MEM_RECLAIM, 0);
	अगर (lbtf_wq == शून्य) अणु
		prपूर्णांकk(KERN_ERR "libertastf: couldn't create workqueue\n");
		वापस -ENOMEM;
	पूर्ण
	lbtf_deb_leave(LBTF_DEB_MAIN);
	वापस 0;
पूर्ण

अटल व्योम __निकास lbtf_निकास_module(व्योम)
अणु
	lbtf_deb_enter(LBTF_DEB_MAIN);
	destroy_workqueue(lbtf_wq);
	lbtf_deb_leave(LBTF_DEB_MAIN);
पूर्ण

module_init(lbtf_init_module);
module_निकास(lbtf_निकास_module);

MODULE_DESCRIPTION("Libertas WLAN Thinfirm Driver Library");
MODULE_AUTHOR("Cozybit Inc.");
MODULE_LICENSE("GPL");
