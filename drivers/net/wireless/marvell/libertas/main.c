<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file contains the major functions in WLAN
 * driver. It includes init, निकास, खोलो, बंद and मुख्य
 * thपढ़ो etc..
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/slab.h>
#समावेश <net/cfg80211.h>

#समावेश "host.h"
#समावेश "decl.h"
#समावेश "dev.h"
#समावेश "cfg.h"
#समावेश "debugfs.h"
#समावेश "cmd.h"
#समावेश "mesh.h"

#घोषणा DRIVER_RELEASE_VERSION "323.p0"
स्थिर अक्षर lbs_driver_version[] = "COMM-USB8388-" DRIVER_RELEASE_VERSION
#अगर_घोषित  DEBUG
    "-dbg"
#पूर्ण_अगर
    "";


/* Module parameters */
अचिन्हित पूर्णांक lbs_debug;
EXPORT_SYMBOL_GPL(lbs_debug);
module_param_named(libertas_debug, lbs_debug, पूर्णांक, 0644);

अचिन्हित पूर्णांक lbs_disablemesh;
EXPORT_SYMBOL_GPL(lbs_disablemesh);
module_param_named(libertas_disablemesh, lbs_disablemesh, पूर्णांक, 0644);


/*
 * This global काष्ठाure is used to send the confirm_sleep command as
 * fast as possible करोwn to the firmware.
 */
काष्ठा cmd_confirm_sleep confirm_sleep;


/*
 * the table to keep region code
 */
u16 lbs_region_code_to_index[MRVDRV_MAX_REGION_CODE] =
    अणु 0x10, 0x20, 0x30, 0x31, 0x32, 0x40 पूर्ण;

/*
 * FW rate table.  FW refers to rates by their index in this table, not by the
 * rate value itself.  Values of 0x00 are
 * reserved positions.
 */
अटल u8 fw_data_rates[MAX_RATES] =
    अणु 0x02, 0x04, 0x0B, 0x16, 0x00, 0x0C, 0x12,
      0x18, 0x24, 0x30, 0x48, 0x60, 0x6C, 0x00
पूर्ण;

/**
 *  lbs_fw_index_to_data_rate - use index to get the data rate
 *
 *  @idx:	The index of data rate
 *  वापसs:	data rate or 0
 */
u32 lbs_fw_index_to_data_rate(u8 idx)
अणु
	अगर (idx >= माप(fw_data_rates))
		idx = 0;
	वापस fw_data_rates[idx];
पूर्ण

/**
 *  lbs_data_rate_to_fw_index - use rate to get the index
 *
 *  @rate:	data rate
 *  वापसs:	index or 0
 */
u8 lbs_data_rate_to_fw_index(u32 rate)
अणु
	u8 i;

	अगर (!rate)
		वापस 0;

	क्रम (i = 0; i < माप(fw_data_rates); i++) अणु
		अगर (rate == fw_data_rates[i])
			वापस i;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक lbs_set_अगरace_type(काष्ठा lbs_निजी *priv, क्रमागत nl80211_अगरtype type)
अणु
	पूर्णांक ret = 0;

	चयन (type) अणु
	हाल NL80211_IFTYPE_MONITOR:
		ret = lbs_set_monitor_mode(priv, 1);
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		अगर (priv->wdev->अगरtype == NL80211_IFTYPE_MONITOR)
			ret = lbs_set_monitor_mode(priv, 0);
		अगर (!ret)
			ret = lbs_set_snmp_mib(priv, SNMP_MIB_OID_BSS_TYPE, 1);
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		अगर (priv->wdev->अगरtype == NL80211_IFTYPE_MONITOR)
			ret = lbs_set_monitor_mode(priv, 0);
		अगर (!ret)
			ret = lbs_set_snmp_mib(priv, SNMP_MIB_OID_BSS_TYPE, 2);
		अवरोध;
	शेष:
		ret = -ENOTSUPP;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक lbs_start_अगरace(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा cmd_ds_802_11_mac_address cmd;
	पूर्णांक ret;

	अगर (priv->घातer_restore) अणु
		ret = priv->घातer_restore(priv);
		अगर (ret)
			वापस ret;
	पूर्ण

	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);
	स_नकल(cmd.macadd, priv->current_addr, ETH_ALEN);

	ret = lbs_cmd_with_response(priv, CMD_802_11_MAC_ADDRESS, &cmd);
	अगर (ret) अणु
		lbs_deb_net("set MAC address failed\n");
		जाओ err;
	पूर्ण

	ret = lbs_set_अगरace_type(priv, priv->wdev->अगरtype);
	अगर (ret) अणु
		lbs_deb_net("set iface type failed\n");
		जाओ err;
	पूर्ण

	ret = lbs_set_11d_करोमुख्य_info(priv);
	अगर (ret) अणु
		lbs_deb_net("set 11d domain info failed\n");
		जाओ err;
	पूर्ण

	lbs_update_channel(priv);

	priv->अगरace_running = true;
	वापस 0;

err:
	अगर (priv->घातer_save)
		priv->घातer_save(priv);
	वापस ret;
पूर्ण

/**
 *  lbs_dev_खोलो - खोलो the ethX पूर्णांकerface
 *
 *  @dev:	A poपूर्णांकer to &net_device काष्ठाure
 *  वापसs:	0 or -EBUSY अगर monitor mode active
 */
अटल पूर्णांक lbs_dev_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा lbs_निजी *priv = dev->ml_priv;
	पूर्णांक ret = 0;

	अगर (!priv->अगरace_running) अणु
		ret = lbs_start_अगरace(priv);
		अगर (ret)
			जाओ out;
	पूर्ण

	spin_lock_irq(&priv->driver_lock);

	netअगर_carrier_off(dev);

	अगर (!priv->tx_pending_len)
		netअगर_wake_queue(dev);

	spin_unlock_irq(&priv->driver_lock);

out:
	वापस ret;
पूर्ण

अटल bool lbs_command_queue_empty(काष्ठा lbs_निजी *priv)
अणु
	अचिन्हित दीर्घ flags;
	bool ret;
	spin_lock_irqsave(&priv->driver_lock, flags);
	ret = priv->cur_cmd == शून्य && list_empty(&priv->cmdpendingq);
	spin_unlock_irqrestore(&priv->driver_lock, flags);
	वापस ret;
पूर्ण

पूर्णांक lbs_stop_अगरace(काष्ठा lbs_निजी *priv)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&priv->driver_lock, flags);
	priv->अगरace_running = false;
	kमुक्त_skb(priv->currenttxskb);
	priv->currenttxskb = शून्य;
	priv->tx_pending_len = 0;
	spin_unlock_irqrestore(&priv->driver_lock, flags);

	cancel_work_sync(&priv->mcast_work);
	del_समयr_sync(&priv->tx_lockup_समयr);

	/* Disable command processing, and रुको क्रम all commands to complete */
	lbs_deb_मुख्य("waiting for commands to complete\n");
	रुको_event(priv->रुकोq, lbs_command_queue_empty(priv));
	lbs_deb_मुख्य("all commands completed\n");

	अगर (priv->घातer_save)
		ret = priv->घातer_save(priv);

	वापस ret;
पूर्ण

/**
 *  lbs_eth_stop - बंद the ethX पूर्णांकerface
 *
 *  @dev:	A poपूर्णांकer to &net_device काष्ठाure
 *  वापसs:	0
 */
अटल पूर्णांक lbs_eth_stop(काष्ठा net_device *dev)
अणु
	काष्ठा lbs_निजी *priv = dev->ml_priv;

	अगर (priv->connect_status == LBS_CONNECTED)
		lbs_disconnect(priv, WLAN_REASON_DEAUTH_LEAVING);

	spin_lock_irq(&priv->driver_lock);
	netअगर_stop_queue(dev);
	spin_unlock_irq(&priv->driver_lock);

	lbs_update_mcast(priv);
	cancel_delayed_work_sync(&priv->scan_work);
	अगर (priv->scan_req)
		lbs_scan_करोne(priv);

	netअगर_carrier_off(priv->dev);

	अगर (!lbs_अगरace_active(priv))
		lbs_stop_अगरace(priv);

	वापस 0;
पूर्ण

व्योम lbs_host_to_card_करोne(काष्ठा lbs_निजी *priv)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->driver_lock, flags);
	del_समयr(&priv->tx_lockup_समयr);

	priv->dnld_sent = DNLD_RES_RECEIVED;

	/* Wake मुख्य thपढ़ो अगर commands are pending */
	अगर (!priv->cur_cmd || priv->tx_pending_len > 0) अणु
		अगर (!priv->wakeup_dev_required)
			wake_up(&priv->रुकोq);
	पूर्ण

	spin_unlock_irqrestore(&priv->driver_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(lbs_host_to_card_करोne);

पूर्णांक lbs_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	पूर्णांक ret = 0;
	काष्ठा lbs_निजी *priv = dev->ml_priv;
	काष्ठा sockaddr *phwaddr = addr;

	/*
	 * Can only set MAC address when all पूर्णांकerfaces are करोwn, to be written
	 * to the hardware when one of them is brought up.
	 */
	अगर (lbs_अगरace_active(priv))
		वापस -EBUSY;

	/* In हाल it was called from the mesh device */
	dev = priv->dev;

	स_नकल(priv->current_addr, phwaddr->sa_data, ETH_ALEN);
	स_नकल(dev->dev_addr, phwaddr->sa_data, ETH_ALEN);
	अगर (priv->mesh_dev)
		स_नकल(priv->mesh_dev->dev_addr, phwaddr->sa_data, ETH_ALEN);

	वापस ret;
पूर्ण


अटल अंतरभूत पूर्णांक mac_in_list(अचिन्हित अक्षर *list, पूर्णांक list_len,
			      अचिन्हित अक्षर *mac)
अणु
	जबतक (list_len) अणु
		अगर (!स_भेद(list, mac, ETH_ALEN))
			वापस 1;
		list += ETH_ALEN;
		list_len--;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक lbs_add_mcast_addrs(काष्ठा cmd_ds_mac_multicast_adr *cmd,
			       काष्ठा net_device *dev, पूर्णांक nr_addrs)
अणु
	पूर्णांक i = nr_addrs;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक cnt;

	अगर ((dev->flags & (IFF_UP|IFF_MULTICAST)) != (IFF_UP|IFF_MULTICAST))
		वापस nr_addrs;

	netअगर_addr_lock_bh(dev);
	cnt = netdev_mc_count(dev);
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		अगर (mac_in_list(cmd->maclist, nr_addrs, ha->addr)) अणु
			lbs_deb_net("mcast address %s:%pM skipped\n", dev->name,
				    ha->addr);
			cnt--;
			जारी;
		पूर्ण

		अगर (i == MRVDRV_MAX_MULTICAST_LIST_SIZE)
			अवरोध;
		स_नकल(&cmd->maclist[6*i], ha->addr, ETH_ALEN);
		lbs_deb_net("mcast address %s:%pM added to filter\n", dev->name,
			    ha->addr);
		i++;
		cnt--;
	पूर्ण
	netअगर_addr_unlock_bh(dev);
	अगर (cnt)
		वापस -EOVERFLOW;

	वापस i;
पूर्ण

व्योम lbs_update_mcast(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा cmd_ds_mac_multicast_adr mcast_cmd;
	पूर्णांक dev_flags = 0;
	पूर्णांक nr_addrs;
	पूर्णांक old_mac_control = priv->mac_control;

	अगर (netअगर_running(priv->dev))
		dev_flags |= priv->dev->flags;
	अगर (priv->mesh_dev && netअगर_running(priv->mesh_dev))
		dev_flags |= priv->mesh_dev->flags;

	अगर (dev_flags & IFF_PROMISC) अणु
		priv->mac_control |= CMD_ACT_MAC_PROMISCUOUS_ENABLE;
		priv->mac_control &= ~(CMD_ACT_MAC_ALL_MULTICAST_ENABLE |
				       CMD_ACT_MAC_MULTICAST_ENABLE);
		जाओ out_set_mac_control;
	पूर्ण अन्यथा अगर (dev_flags & IFF_ALLMULTI) अणु
	करो_allmulti:
		priv->mac_control |= CMD_ACT_MAC_ALL_MULTICAST_ENABLE;
		priv->mac_control &= ~(CMD_ACT_MAC_PROMISCUOUS_ENABLE |
				       CMD_ACT_MAC_MULTICAST_ENABLE);
		जाओ out_set_mac_control;
	पूर्ण

	/* Once क्रम priv->dev, again क्रम priv->mesh_dev अगर it exists */
	nr_addrs = lbs_add_mcast_addrs(&mcast_cmd, priv->dev, 0);
	अगर (nr_addrs >= 0 && priv->mesh_dev)
		nr_addrs = lbs_add_mcast_addrs(&mcast_cmd, priv->mesh_dev, nr_addrs);
	अगर (nr_addrs < 0)
		जाओ करो_allmulti;

	अगर (nr_addrs) अणु
		पूर्णांक size = दुरत्व(काष्ठा cmd_ds_mac_multicast_adr,
				    maclist[6*nr_addrs]);

		mcast_cmd.action = cpu_to_le16(CMD_ACT_SET);
		mcast_cmd.hdr.size = cpu_to_le16(size);
		mcast_cmd.nr_of_adrs = cpu_to_le16(nr_addrs);

		lbs_cmd_async(priv, CMD_MAC_MULTICAST_ADR, &mcast_cmd.hdr, size);

		priv->mac_control |= CMD_ACT_MAC_MULTICAST_ENABLE;
	पूर्ण अन्यथा
		priv->mac_control &= ~CMD_ACT_MAC_MULTICAST_ENABLE;

	priv->mac_control &= ~(CMD_ACT_MAC_PROMISCUOUS_ENABLE |
			       CMD_ACT_MAC_ALL_MULTICAST_ENABLE);
 out_set_mac_control:
	अगर (priv->mac_control != old_mac_control)
		lbs_set_mac_control(priv);
पूर्ण

अटल व्योम lbs_set_mcast_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lbs_निजी *priv = container_of(work, काष्ठा lbs_निजी, mcast_work);
	lbs_update_mcast(priv);
पूर्ण

व्योम lbs_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा lbs_निजी *priv = dev->ml_priv;

	schedule_work(&priv->mcast_work);
पूर्ण

/**
 *  lbs_thपढ़ो - handles the major jobs in the LBS driver.
 *  It handles all events generated by firmware, RX data received
 *  from firmware and TX data sent from kernel.
 *
 *  @data:	A poपूर्णांकer to &lbs_thपढ़ो काष्ठाure
 *  वापसs:	0
 */
अटल पूर्णांक lbs_thपढ़ो(व्योम *data)
अणु
	काष्ठा net_device *dev = data;
	काष्ठा lbs_निजी *priv = dev->ml_priv;
	रुको_queue_entry_t रुको;

	init_रुकोqueue_entry(&रुको, current);

	क्रम (;;) अणु
		पूर्णांक shouldsleep;
		u8 resp_idx;

		lbs_deb_thपढ़ो("1: currenttxskb %p, dnld_sent %d\n",
				priv->currenttxskb, priv->dnld_sent);

		add_रुको_queue(&priv->रुकोq, &रुको);
		set_current_state(TASK_INTERRUPTIBLE);
		spin_lock_irq(&priv->driver_lock);

		अगर (kthपढ़ो_should_stop())
			shouldsleep = 0;	/* Bye */
		अन्यथा अगर (priv->surpriseहटाओd)
			shouldsleep = 1;	/* We need to रुको until we're _told_ to die */
		अन्यथा अगर (priv->psstate == PS_STATE_SLEEP)
			shouldsleep = 1;	/* Sleep mode. Nothing we can करो till it wakes */
		अन्यथा अगर (priv->cmd_समयd_out)
			shouldsleep = 0;	/* Command समयd out. Recover */
		अन्यथा अगर (!priv->fw_पढ़ोy)
			shouldsleep = 1;	/* Firmware not पढ़ोy. We're रुकोing क्रम it */
		अन्यथा अगर (priv->dnld_sent)
			shouldsleep = 1;	/* Something is en route to the device alपढ़ोy */
		अन्यथा अगर (priv->tx_pending_len > 0)
			shouldsleep = 0;	/* We've a packet to send */
		अन्यथा अगर (priv->resp_len[priv->resp_idx])
			shouldsleep = 0;	/* We have a command response */
		अन्यथा अगर (priv->cur_cmd)
			shouldsleep = 1;	/* Can't send a command; one alपढ़ोy running */
		अन्यथा अगर (!list_empty(&priv->cmdpendingq) &&
					!(priv->wakeup_dev_required))
			shouldsleep = 0;	/* We have a command to send */
		अन्यथा अगर (kfअगरo_len(&priv->event_fअगरo))
			shouldsleep = 0;	/* We have an event to process */
		अन्यथा
			shouldsleep = 1;	/* No command */

		अगर (shouldsleep) अणु
			lbs_deb_thपढ़ो("sleeping, connect_status %d, "
				"psmode %d, psstate %d\n",
				priv->connect_status,
				priv->psmode, priv->psstate);
			spin_unlock_irq(&priv->driver_lock);
			schedule();
		पूर्ण अन्यथा
			spin_unlock_irq(&priv->driver_lock);

		lbs_deb_thपढ़ो("2: currenttxskb %p, dnld_send %d\n",
			       priv->currenttxskb, priv->dnld_sent);

		set_current_state(TASK_RUNNING);
		हटाओ_रुको_queue(&priv->रुकोq, &रुको);

		lbs_deb_thपढ़ो("3: currenttxskb %p, dnld_sent %d\n",
			       priv->currenttxskb, priv->dnld_sent);

		अगर (kthपढ़ो_should_stop()) अणु
			lbs_deb_thपढ़ो("break from main thread\n");
			अवरोध;
		पूर्ण

		अगर (priv->surpriseहटाओd) अणु
			lbs_deb_thपढ़ो("adapter removed; waiting to die...\n");
			जारी;
		पूर्ण

		lbs_deb_thपढ़ो("4: currenttxskb %p, dnld_sent %d\n",
		       priv->currenttxskb, priv->dnld_sent);

		/* Process any pending command response */
		spin_lock_irq(&priv->driver_lock);
		resp_idx = priv->resp_idx;
		अगर (priv->resp_len[resp_idx]) अणु
			spin_unlock_irq(&priv->driver_lock);
			lbs_process_command_response(priv,
				priv->resp_buf[resp_idx],
				priv->resp_len[resp_idx]);
			spin_lock_irq(&priv->driver_lock);
			priv->resp_len[resp_idx] = 0;
		पूर्ण
		spin_unlock_irq(&priv->driver_lock);

		/* Process hardware events, e.g. card हटाओd, link lost */
		spin_lock_irq(&priv->driver_lock);
		जबतक (kfअगरo_len(&priv->event_fअगरo)) अणु
			u32 event;

			अगर (kfअगरo_out(&priv->event_fअगरo,
				(अचिन्हित अक्षर *) &event, माप(event)) !=
				माप(event))
					अवरोध;
			spin_unlock_irq(&priv->driver_lock);
			lbs_process_event(priv, event);
			spin_lock_irq(&priv->driver_lock);
		पूर्ण
		spin_unlock_irq(&priv->driver_lock);

		अगर (priv->wakeup_dev_required) अणु
			lbs_deb_thपढ़ो("Waking up device...\n");
			/* Wake up device */
			अगर (priv->निकास_deep_sleep(priv))
				lbs_deb_thपढ़ो("Wakeup device failed\n");
			जारी;
		पूर्ण

		/* command समयout stuff */
		अगर (priv->cmd_समयd_out && priv->cur_cmd) अणु
			काष्ठा cmd_ctrl_node *cmdnode = priv->cur_cmd;

			netdev_info(dev, "Timeout submitting command 0x%04x\n",
				    le16_to_cpu(cmdnode->cmdbuf->command));
			lbs_complete_command(priv, cmdnode, -ETIMEDOUT);

			/* Reset card, but only when it isn't in the process
			 * of being shutकरोwn anyway. */
			अगर (!dev->dismantle && priv->reset_card)
				priv->reset_card(priv);
		पूर्ण
		priv->cmd_समयd_out = 0;

		अगर (!priv->fw_पढ़ोy)
			जारी;

		/* Check अगर we need to confirm Sleep Request received previously */
		अगर (priv->psstate == PS_STATE_PRE_SLEEP &&
		    !priv->dnld_sent && !priv->cur_cmd) अणु
			अगर (priv->connect_status == LBS_CONNECTED) अणु
				lbs_deb_thपढ़ो("pre-sleep, currenttxskb %p, "
					"dnld_sent %d, cur_cmd %p\n",
					priv->currenttxskb, priv->dnld_sent,
					priv->cur_cmd);

				lbs_ps_confirm_sleep(priv);
			पूर्ण अन्यथा अणु
				/* workaround क्रम firmware sending
				 * deauth/linkloss event immediately
				 * after sleep request; हटाओ this
				 * after firmware fixes it
				 */
				priv->psstate = PS_STATE_AWAKE;
				netdev_alert(dev,
					     "ignore PS_SleepConfirm in non-connected state\n");
			पूर्ण
		पूर्ण

		/* The PS state is changed during processing of Sleep Request
		 * event above
		 */
		अगर ((priv->psstate == PS_STATE_SLEEP) ||
		    (priv->psstate == PS_STATE_PRE_SLEEP))
			जारी;

		अगर (priv->is_deep_sleep)
			जारी;

		/* Execute the next command */
		अगर (!priv->dnld_sent && !priv->cur_cmd)
			lbs_execute_next_command(priv);

		spin_lock_irq(&priv->driver_lock);
		अगर (!priv->dnld_sent && priv->tx_pending_len > 0) अणु
			पूर्णांक ret = priv->hw_host_to_card(priv, MVMS_DAT,
							priv->tx_pending_buf,
							priv->tx_pending_len);
			अगर (ret) अणु
				lbs_deb_tx("host_to_card failed %d\n", ret);
				priv->dnld_sent = DNLD_RES_RECEIVED;
			पूर्ण अन्यथा अणु
				mod_समयr(&priv->tx_lockup_समयr,
					  jअगरfies + (HZ * 5));
			पूर्ण
			priv->tx_pending_len = 0;
			अगर (!priv->currenttxskb) अणु
				/* We can wake the queues immediately अगर we aren't
				   रुकोing क्रम TX feedback */
				अगर (priv->connect_status == LBS_CONNECTED)
					netअगर_wake_queue(priv->dev);
				अगर (priv->mesh_dev &&
				    netअगर_running(priv->mesh_dev))
					netअगर_wake_queue(priv->mesh_dev);
			पूर्ण
		पूर्ण
		spin_unlock_irq(&priv->driver_lock);
	पूर्ण

	del_समयr(&priv->command_समयr);
	del_समयr(&priv->tx_lockup_समयr);
	del_समयr(&priv->स्वतः_deepsleep_समयr);

	वापस 0;
पूर्ण

/**
 * lbs_setup_firmware - माला_लो the HW spec from the firmware and sets
 *        some basic parameters
 *
 *  @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 *  वापसs:	0 or -1
 */
अटल पूर्णांक lbs_setup_firmware(काष्ठा lbs_निजी *priv)
अणु
	पूर्णांक ret = -1;
	s16 curlevel = 0, minlevel = 0, maxlevel = 0;

	/* Read MAC address from firmware */
	eth_broadcast_addr(priv->current_addr);
	ret = lbs_update_hw_spec(priv);
	अगर (ret)
		जाओ करोne;

	/* Read घातer levels अगर available */
	ret = lbs_get_tx_घातer(priv, &curlevel, &minlevel, &maxlevel);
	अगर (ret == 0) अणु
		priv->txघातer_cur = curlevel;
		priv->txघातer_min = minlevel;
		priv->txघातer_max = maxlevel;
	पूर्ण

	/* Send cmd to FW to enable 11D function */
	ret = lbs_set_snmp_mib(priv, SNMP_MIB_OID_11D_ENABLE, 1);
	अगर (ret)
		जाओ करोne;

	ret = lbs_set_mac_control_sync(priv);
करोne:
	वापस ret;
पूर्ण

पूर्णांक lbs_suspend(काष्ठा lbs_निजी *priv)
अणु
	पूर्णांक ret;

	अगर (priv->is_deep_sleep) अणु
		ret = lbs_set_deep_sleep(priv, 0);
		अगर (ret) अणु
			netdev_err(priv->dev,
				   "deep sleep cancellation failed: %d\n", ret);
			वापस ret;
		पूर्ण
		priv->deep_sleep_required = 1;
	पूर्ण

	ret = lbs_set_host_sleep(priv, 1);

	netअगर_device_detach(priv->dev);
	अगर (priv->mesh_dev)
		netअगर_device_detach(priv->mesh_dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lbs_suspend);

पूर्णांक lbs_resume(काष्ठा lbs_निजी *priv)
अणु
	पूर्णांक ret;

	ret = lbs_set_host_sleep(priv, 0);

	netअगर_device_attach(priv->dev);
	अगर (priv->mesh_dev)
		netअगर_device_attach(priv->mesh_dev);

	अगर (priv->deep_sleep_required) अणु
		priv->deep_sleep_required = 0;
		ret = lbs_set_deep_sleep(priv, 1);
		अगर (ret)
			netdev_err(priv->dev,
				   "deep sleep activation failed: %d\n", ret);
	पूर्ण

	अगर (priv->setup_fw_on_resume)
		ret = lbs_setup_firmware(priv);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lbs_resume);

/**
 * lbs_cmd_समयout_handler - handles the समयout of command sending.
 * It will re-send the same command again.
 *
 * @t: Context from which to retrieve a &काष्ठा lbs_निजी poपूर्णांकer
 */
अटल व्योम lbs_cmd_समयout_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा lbs_निजी *priv = from_समयr(priv, t, command_समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->driver_lock, flags);

	अगर (!priv->cur_cmd)
		जाओ out;

	netdev_info(priv->dev, "command 0x%04x timed out\n",
		    le16_to_cpu(priv->cur_cmd->cmdbuf->command));

	priv->cmd_समयd_out = 1;

	/*
	 * If the device didn't even acknowledge the command, reset the state
	 * so that we करोn't block all future commands due to this one समयout.
	 */
	अगर (priv->dnld_sent == DNLD_CMD_SENT)
		priv->dnld_sent = DNLD_RES_RECEIVED;

	wake_up(&priv->रुकोq);
out:
	spin_unlock_irqrestore(&priv->driver_lock, flags);
पूर्ण

/**
 * lbs_tx_lockup_handler - handles the समयout of the passing of TX frames
 * to the hardware. This is known to frequently happen with SD8686 when
 * waking up after a Wake-on-WLAN-triggered resume.
 *
 * @t: Context from which to retrieve a &काष्ठा lbs_निजी poपूर्णांकer
 */
अटल व्योम lbs_tx_lockup_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा lbs_निजी *priv = from_समयr(priv, t, tx_lockup_समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->driver_lock, flags);

	netdev_info(priv->dev, "TX lockup detected\n");
	अगर (priv->reset_card)
		priv->reset_card(priv);

	priv->dnld_sent = DNLD_RES_RECEIVED;
	wake_up_पूर्णांकerruptible(&priv->रुकोq);

	spin_unlock_irqrestore(&priv->driver_lock, flags);
पूर्ण

/**
 * स्वतः_deepsleep_समयr_fn - put the device back to deep sleep mode when
 * समयr expires and no activity (command, event, data etc.) is detected.
 * @t: Context from which to retrieve a &काष्ठा lbs_निजी poपूर्णांकer
 * वापसs:	N/A
 */
अटल व्योम स्वतः_deepsleep_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा lbs_निजी *priv = from_समयr(priv, t, स्वतः_deepsleep_समयr);

	अगर (priv->is_activity_detected) अणु
		priv->is_activity_detected = 0;
	पूर्ण अन्यथा अणु
		अगर (priv->is_स्वतः_deep_sleep_enabled &&
		    (!priv->wakeup_dev_required) &&
		    (priv->connect_status != LBS_CONNECTED)) अणु
			काष्ठा cmd_header cmd;

			lbs_deb_मुख्य("Entering auto deep sleep mode...\n");
			स_रखो(&cmd, 0, माप(cmd));
			cmd.size = cpu_to_le16(माप(cmd));
			lbs_cmd_async(priv, CMD_802_11_DEEP_SLEEP, &cmd,
					माप(cmd));
		पूर्ण
	पूर्ण
	mod_समयr(&priv->स्वतः_deepsleep_समयr , jअगरfies +
				(priv->स्वतः_deep_sleep_समयout * HZ)/1000);
पूर्ण

पूर्णांक lbs_enter_स्वतः_deep_sleep(काष्ठा lbs_निजी *priv)
अणु
	priv->is_स्वतः_deep_sleep_enabled = 1;
	अगर (priv->is_deep_sleep)
		priv->wakeup_dev_required = 1;
	mod_समयr(&priv->स्वतः_deepsleep_समयr ,
			jअगरfies + (priv->स्वतः_deep_sleep_समयout * HZ)/1000);

	वापस 0;
पूर्ण

पूर्णांक lbs_निकास_स्वतः_deep_sleep(काष्ठा lbs_निजी *priv)
अणु
	priv->is_स्वतः_deep_sleep_enabled = 0;
	priv->स्वतः_deep_sleep_समयout = 0;
	del_समयr(&priv->स्वतः_deepsleep_समयr);

	वापस 0;
पूर्ण

अटल पूर्णांक lbs_init_adapter(काष्ठा lbs_निजी *priv)
अणु
	पूर्णांक ret;

	eth_broadcast_addr(priv->current_addr);

	priv->connect_status = LBS_DISCONNECTED;
	priv->channel = DEFAULT_AD_HOC_CHANNEL;
	priv->mac_control = CMD_ACT_MAC_RX_ON | CMD_ACT_MAC_TX_ON;
	priv->radio_on = 1;
	priv->psmode = LBS802_11POWERMODECAM;
	priv->psstate = PS_STATE_FULL_POWER;
	priv->is_deep_sleep = 0;
	priv->is_स्वतः_deep_sleep_enabled = 0;
	priv->deep_sleep_required = 0;
	priv->wakeup_dev_required = 0;
	init_रुकोqueue_head(&priv->ds_awake_q);
	init_रुकोqueue_head(&priv->scan_q);
	priv->authtype_स्वतः = 1;
	priv->is_host_sleep_configured = 0;
	priv->is_host_sleep_activated = 0;
	init_रुकोqueue_head(&priv->host_sleep_q);
	init_रुकोqueue_head(&priv->fw_रुकोq);
	mutex_init(&priv->lock);

	समयr_setup(&priv->command_समयr, lbs_cmd_समयout_handler, 0);
	समयr_setup(&priv->tx_lockup_समयr, lbs_tx_lockup_handler, 0);
	समयr_setup(&priv->स्वतः_deepsleep_समयr, स्वतः_deepsleep_समयr_fn, 0);

	INIT_LIST_HEAD(&priv->cmdमुक्तq);
	INIT_LIST_HEAD(&priv->cmdpendingq);

	spin_lock_init(&priv->driver_lock);

	/* Allocate the command buffers */
	अगर (lbs_allocate_cmd_buffer(priv)) अणु
		pr_err("Out of memory allocating command buffers\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	priv->resp_idx = 0;
	priv->resp_len[0] = priv->resp_len[1] = 0;

	/* Create the event FIFO */
	ret = kfअगरo_alloc(&priv->event_fअगरo, माप(u32) * 16, GFP_KERNEL);
	अगर (ret) अणु
		pr_err("Out of memory allocating event FIFO buffer\n");
		जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल व्योम lbs_मुक्त_adapter(काष्ठा lbs_निजी *priv)
अणु
	lbs_मुक्त_cmd_buffer(priv);
	kfअगरo_मुक्त(&priv->event_fअगरo);
	del_समयr(&priv->command_समयr);
	del_समयr(&priv->tx_lockup_समयr);
	del_समयr(&priv->स्वतः_deepsleep_समयr);
पूर्ण

अटल स्थिर काष्ठा net_device_ops lbs_netdev_ops = अणु
	.nकरो_खोलो 		= lbs_dev_खोलो,
	.nकरो_stop		= lbs_eth_stop,
	.nकरो_start_xmit		= lbs_hard_start_xmit,
	.nकरो_set_mac_address	= lbs_set_mac_address,
	.nकरो_set_rx_mode	= lbs_set_multicast_list,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

/**
 * lbs_add_card - adds the card. It will probe the
 * card, allocate the lbs_priv and initialize the device.
 *
 * @card:	A poपूर्णांकer to card
 * @dmdev:	A poपूर्णांकer to &काष्ठा device
 * वापसs:	A poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 */
काष्ठा lbs_निजी *lbs_add_card(व्योम *card, काष्ठा device *dmdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा wireless_dev *wdev;
	काष्ठा lbs_निजी *priv = शून्य;
	पूर्णांक err;

	/* Allocate an Ethernet device and रेजिस्टर it */
	wdev = lbs_cfg_alloc(dmdev);
	अगर (IS_ERR(wdev)) अणु
		err = PTR_ERR(wdev);
		pr_err("cfg80211 init failed\n");
		जाओ err_cfg;
	पूर्ण

	wdev->अगरtype = NL80211_IFTYPE_STATION;
	priv = wdev_priv(wdev);
	priv->wdev = wdev;

	err = lbs_init_adapter(priv);
	अगर (err) अणु
		pr_err("failed to initialize adapter structure\n");
		जाओ err_wdev;
	पूर्ण

	dev = alloc_netdev(0, "wlan%d", NET_NAME_UNKNOWN, ether_setup);
	अगर (!dev) अणु
		err = -ENOMEM;
		dev_err(dmdev, "no memory for network device instance\n");
		जाओ err_adapter;
	पूर्ण

	dev->ieee80211_ptr = wdev;
	dev->ml_priv = priv;
	SET_NETDEV_DEV(dev, dmdev);
	wdev->netdev = dev;
	priv->dev = dev;

 	dev->netdev_ops = &lbs_netdev_ops;
	dev->watchकरोg_समयo = 5 * HZ;
	dev->ethtool_ops = &lbs_ethtool_ops;
	dev->flags |= IFF_BROADCAST | IFF_MULTICAST;

	priv->card = card;

	म_नकल(dev->name, "wlan%d");

	lbs_deb_thपढ़ो("Starting main thread...\n");
	init_रुकोqueue_head(&priv->रुकोq);
	priv->मुख्य_thपढ़ो = kthपढ़ो_run(lbs_thपढ़ो, dev, "lbs_main");
	अगर (IS_ERR(priv->मुख्य_thपढ़ो)) अणु
		err = PTR_ERR(priv->मुख्य_thपढ़ो);
		lbs_deb_thपढ़ो("Error creating main thread.\n");
		जाओ err_ndev;
	पूर्ण

	priv->work_thपढ़ो = create_singlethपढ़ो_workqueue("lbs_worker");
	INIT_WORK(&priv->mcast_work, lbs_set_mcast_worker);

	priv->wol_criteria = EHS_REMOVE_WAKEUP;
	priv->wol_gpio = 0xff;
	priv->wol_gap = 20;
	priv->ehs_हटाओ_supported = true;

	वापस priv;

 err_ndev:
	मुक्त_netdev(dev);

 err_adapter:
	lbs_मुक्त_adapter(priv);

 err_wdev:
	lbs_cfg_मुक्त(priv);

 err_cfg:
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(lbs_add_card);


व्योम lbs_हटाओ_card(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा net_device *dev = priv->dev;

	lbs_हटाओ_mesh(priv);

	अगर (priv->wiphy_रेजिस्टरed)
		lbs_scan_deinit(priv);

	lbs_रुको_क्रम_firmware_load(priv);

	/* worker thपढ़ो deकाष्ठाion blocks on the in-flight command which
	 * should have been cleared alपढ़ोy in lbs_stop_card().
	 */
	lbs_deb_मुख्य("destroying worker thread\n");
	destroy_workqueue(priv->work_thपढ़ो);
	lbs_deb_मुख्य("done destroying worker thread\n");

	अगर (priv->psmode == LBS802_11POWERMODEMAX_PSP) अणु
		priv->psmode = LBS802_11POWERMODECAM;
		/* no need to wakeup अगर alपढ़ोy woken up,
		 * on suspend, this निकास ps command is not processed
		 * the driver hangs
		 */
		अगर (priv->psstate != PS_STATE_FULL_POWER)
			lbs_set_ps_mode(priv, PS_MODE_ACTION_EXIT_PS, true);
	पूर्ण

	अगर (priv->is_deep_sleep) अणु
		priv->is_deep_sleep = 0;
		wake_up_पूर्णांकerruptible(&priv->ds_awake_q);
	पूर्ण

	priv->is_host_sleep_configured = 0;
	priv->is_host_sleep_activated = 0;
	wake_up_पूर्णांकerruptible(&priv->host_sleep_q);

	/* Stop the thपढ़ो servicing the पूर्णांकerrupts */
	priv->surpriseहटाओd = 1;
	kthपढ़ो_stop(priv->मुख्य_thपढ़ो);

	lbs_मुक्त_adapter(priv);
	lbs_cfg_मुक्त(priv);
	मुक्त_netdev(dev);
पूर्ण
EXPORT_SYMBOL_GPL(lbs_हटाओ_card);


पूर्णांक lbs_rtap_supported(काष्ठा lbs_निजी *priv)
अणु
	अगर (MRVL_FW_MAJOR_REV(priv->fwrelease) == MRVL_FW_V5)
		वापस 1;

	/* newer firmware use a capability mask */
	वापस ((MRVL_FW_MAJOR_REV(priv->fwrelease) >= MRVL_FW_V10) &&
		(priv->fwcapinfo & MESH_CAPINFO_ENABLE_MASK));
पूर्ण


पूर्णांक lbs_start_card(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा net_device *dev = priv->dev;
	पूर्णांक ret;

	/* poke the firmware */
	ret = lbs_setup_firmware(priv);
	अगर (ret)
		जाओ करोne;

	अगर (!lbs_disablemesh)
		lbs_init_mesh(priv);
	अन्यथा
		pr_info("%s: mesh disabled\n", dev->name);

	ret = lbs_cfg_रेजिस्टर(priv);
	अगर (ret) अणु
		pr_err("cannot register device\n");
		जाओ करोne;
	पूर्ण

	अगर (lbs_mesh_activated(priv))
		lbs_start_mesh(priv);

	lbs_debugfs_init_one(priv, dev);

	netdev_info(dev, "Marvell WLAN 802.11 adapter\n");

	ret = 0;

करोne:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lbs_start_card);


व्योम lbs_stop_card(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा net_device *dev;

	अगर (!priv)
		वापस;
	dev = priv->dev;

	/* If the netdev isn't रेजिस्टरed, it means that lbs_start_card() was
	 * never called so we have nothing to करो here. */
	अगर (dev->reg_state != NETREG_REGISTERED)
		वापस;

	netअगर_stop_queue(dev);
	netअगर_carrier_off(dev);

	lbs_debugfs_हटाओ_one(priv);
	lbs_deinit_mesh(priv);
	unरेजिस्टर_netdev(dev);
पूर्ण
EXPORT_SYMBOL_GPL(lbs_stop_card);


व्योम lbs_queue_event(काष्ठा lbs_निजी *priv, u32 event)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->driver_lock, flags);

	अगर (priv->psstate == PS_STATE_SLEEP)
		priv->psstate = PS_STATE_AWAKE;

	kfअगरo_in(&priv->event_fअगरo, (अचिन्हित अक्षर *) &event, माप(u32));

	wake_up(&priv->रुकोq);

	spin_unlock_irqrestore(&priv->driver_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(lbs_queue_event);

व्योम lbs_notअगरy_command_response(काष्ठा lbs_निजी *priv, u8 resp_idx)
अणु
	अगर (priv->psstate == PS_STATE_SLEEP)
		priv->psstate = PS_STATE_AWAKE;

	/* Swap buffers by flipping the response index */
	BUG_ON(resp_idx > 1);
	priv->resp_idx = resp_idx;

	wake_up(&priv->रुकोq);
पूर्ण
EXPORT_SYMBOL_GPL(lbs_notअगरy_command_response);

अटल पूर्णांक __init lbs_init_module(व्योम)
अणु
	स_रखो(&confirm_sleep, 0, माप(confirm_sleep));
	confirm_sleep.hdr.command = cpu_to_le16(CMD_802_11_PS_MODE);
	confirm_sleep.hdr.size = cpu_to_le16(माप(confirm_sleep));
	confirm_sleep.action = cpu_to_le16(PS_MODE_ACTION_SLEEP_CONFIRMED);
	lbs_debugfs_init();

	वापस 0;
पूर्ण

अटल व्योम __निकास lbs_निकास_module(व्योम)
अणु
	lbs_debugfs_हटाओ();
पूर्ण

module_init(lbs_init_module);
module_निकास(lbs_निकास_module);

MODULE_DESCRIPTION("Libertas WLAN Driver Library");
MODULE_AUTHOR("Marvell International Ltd.");
MODULE_LICENSE("GPL");
