<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2012 - 2018 Microchip Technology Inc., and its subsidiaries.
 * All rights reserved.
 */

#समावेश <linux/irq.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/firmware.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/inetdevice.h>

#समावेश "cfg80211.h"
#समावेश "wlan_cfg.h"

#घोषणा WILC_MULTICAST_TABLE_SIZE	8

/* latest API version supported */
#घोषणा WILC1000_API_VER		1

#घोषणा WILC1000_FW_PREFIX		"atmel/wilc1000_wifi_firmware-"
#घोषणा __WILC1000_FW(api)		WILC1000_FW_PREFIX #api ".bin"
#घोषणा WILC1000_FW(api)		__WILC1000_FW(api)

अटल irqवापस_t isr_uh_routine(पूर्णांक irq, व्योम *user_data)
अणु
	काष्ठा wilc *wilc = user_data;

	अगर (wilc->बंद) अणु
		pr_err("Can't handle UH interrupt");
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t isr_bh_routine(पूर्णांक irq, व्योम *userdata)
अणु
	काष्ठा wilc *wilc = userdata;

	अगर (wilc->बंद) अणु
		pr_err("Can't handle BH interrupt\n");
		वापस IRQ_HANDLED;
	पूर्ण

	wilc_handle_isr(wilc);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक init_irq(काष्ठा net_device *dev)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc *wl = vअगर->wilc;
	पूर्णांक ret;

	ret = request_thपढ़ोed_irq(wl->dev_irq_num, isr_uh_routine,
				   isr_bh_routine,
				   IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				   "WILC_IRQ", wl);
	अगर (ret) अणु
		netdev_err(dev, "Failed to request IRQ [%d]\n", ret);
		वापस ret;
	पूर्ण
	netdev_dbg(dev, "IRQ request succeeded IRQ-NUM= %d\n", wl->dev_irq_num);

	वापस 0;
पूर्ण

अटल व्योम deinit_irq(काष्ठा net_device *dev)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc *wilc = vअगर->wilc;

	/* Deinitialize IRQ */
	अगर (wilc->dev_irq_num)
		मुक्त_irq(wilc->dev_irq_num, wilc);
पूर्ण

व्योम wilc_mac_indicate(काष्ठा wilc *wilc)
अणु
	s8 status;

	wilc_wlan_cfg_get_val(wilc, WID_STATUS, &status, 1);
	अगर (wilc->mac_status == WILC_MAC_STATUS_INIT) अणु
		wilc->mac_status = status;
		complete(&wilc->sync_event);
	पूर्ण अन्यथा अणु
		wilc->mac_status = status;
	पूर्ण
पूर्ण

अटल काष्ठा net_device *get_अगर_handler(काष्ठा wilc *wilc, u8 *mac_header)
अणु
	काष्ठा net_device *ndev = शून्य;
	काष्ठा wilc_vअगर *vअगर;
	काष्ठा ieee80211_hdr *h = (काष्ठा ieee80211_hdr *)mac_header;

	list_क्रम_each_entry_rcu(vअगर, &wilc->vअगर_list, list) अणु
		अगर (vअगर->mode == WILC_STATION_MODE)
			अगर (ether_addr_equal_unaligned(h->addr2, vअगर->bssid)) अणु
				ndev = vअगर->ndev;
				जाओ out;
			पूर्ण
		अगर (vअगर->mode == WILC_AP_MODE)
			अगर (ether_addr_equal_unaligned(h->addr1, vअगर->bssid)) अणु
				ndev = vअगर->ndev;
				जाओ out;
			पूर्ण
	पूर्ण
out:
	वापस ndev;
पूर्ण

व्योम wilc_wlan_set_bssid(काष्ठा net_device *wilc_netdev, u8 *bssid, u8 mode)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(wilc_netdev);

	अगर (bssid)
		ether_addr_copy(vअगर->bssid, bssid);
	अन्यथा
		eth_zero_addr(vअगर->bssid);

	vअगर->mode = mode;
पूर्ण

पूर्णांक wilc_wlan_get_num_conn_अगरcs(काष्ठा wilc *wilc)
अणु
	पूर्णांक srcu_idx;
	u8 ret_val = 0;
	काष्ठा wilc_vअगर *vअगर;

	srcu_idx = srcu_पढ़ो_lock(&wilc->srcu);
	list_क्रम_each_entry_rcu(vअगर, &wilc->vअगर_list, list) अणु
		अगर (!is_zero_ether_addr(vअगर->bssid))
			ret_val++;
	पूर्ण
	srcu_पढ़ो_unlock(&wilc->srcu, srcu_idx);
	वापस ret_val;
पूर्ण

अटल पूर्णांक wilc_txq_task(व्योम *vp)
अणु
	पूर्णांक ret;
	u32 txq_count;
	काष्ठा wilc *wl = vp;

	complete(&wl->txq_thपढ़ो_started);
	जबतक (1) अणु
		रुको_क्रम_completion(&wl->txq_event);

		अगर (wl->बंद) अणु
			complete(&wl->txq_thपढ़ो_started);

			जबतक (!kthपढ़ो_should_stop())
				schedule();
			अवरोध;
		पूर्ण
		करो अणु
			ret = wilc_wlan_handle_txq(wl, &txq_count);
			अगर (txq_count < FLOW_CONTROL_LOWER_THRESHOLD) अणु
				पूर्णांक srcu_idx;
				काष्ठा wilc_vअगर *अगरc;

				srcu_idx = srcu_पढ़ो_lock(&wl->srcu);
				list_क्रम_each_entry_rcu(अगरc, &wl->vअगर_list,
							list) अणु
					अगर (अगरc->mac_खोलोed && अगरc->ndev)
						netअगर_wake_queue(अगरc->ndev);
				पूर्ण
				srcu_पढ़ो_unlock(&wl->srcu, srcu_idx);
			पूर्ण
		पूर्ण जबतक (ret == WILC_VMM_ENTRY_FULL_RETRY && !wl->बंद);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wilc_wlan_get_firmware(काष्ठा net_device *dev)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc *wilc = vअगर->wilc;
	पूर्णांक chip_id;
	स्थिर काष्ठा firmware *wilc_fw;
	पूर्णांक ret;

	chip_id = wilc_get_chipid(wilc, false);

	netdev_info(dev, "ChipID [%x] loading firmware [%s]\n", chip_id,
		    WILC1000_FW(WILC1000_API_VER));

	ret = request_firmware(&wilc_fw, WILC1000_FW(WILC1000_API_VER),
			       wilc->dev);
	अगर (ret != 0) अणु
		netdev_err(dev, "%s - firmware not available\n",
			   WILC1000_FW(WILC1000_API_VER));
		वापस -EINVAL;
	पूर्ण
	wilc->firmware = wilc_fw;

	वापस 0;
पूर्ण

अटल पूर्णांक wilc_start_firmware(काष्ठा net_device *dev)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc *wilc = vअगर->wilc;
	पूर्णांक ret = 0;

	ret = wilc_wlan_start(wilc);
	अगर (ret)
		वापस ret;

	अगर (!रुको_क्रम_completion_समयout(&wilc->sync_event,
					 msecs_to_jअगरfies(5000)))
		वापस -ETIME;

	वापस 0;
पूर्ण

अटल पूर्णांक wilc1000_firmware_करोwnload(काष्ठा net_device *dev)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc *wilc = vअगर->wilc;
	पूर्णांक ret = 0;

	अगर (!wilc->firmware) अणु
		netdev_err(dev, "Firmware buffer is NULL\n");
		वापस -ENOBUFS;
	पूर्ण

	ret = wilc_wlan_firmware_करोwnload(wilc, wilc->firmware->data,
					  wilc->firmware->size);
	अगर (ret)
		वापस ret;

	release_firmware(wilc->firmware);
	wilc->firmware = शून्य;

	netdev_dbg(dev, "Download Succeeded\n");

	वापस 0;
पूर्ण

अटल पूर्णांक wilc_init_fw_config(काष्ठा net_device *dev, काष्ठा wilc_vअगर *vअगर)
अणु
	काष्ठा wilc_priv *priv = &vअगर->priv;
	काष्ठा host_अगर_drv *hअगर_drv;
	u8 b;
	u16 hw;
	u32 w;

	netdev_dbg(dev, "Start configuring Firmware\n");
	hअगर_drv = (काष्ठा host_अगर_drv *)priv->hअगर_drv;
	netdev_dbg(dev, "Host = %p\n", hअगर_drv);

	w = vअगर->अगरtype;
	cpu_to_le32s(&w);
	अगर (!wilc_wlan_cfg_set(vअगर, 1, WID_SET_OPERATION_MODE, (u8 *)&w, 4,
			       0, 0))
		जाओ fail;

	b = WILC_FW_BSS_TYPE_INFRA;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_BSS_TYPE, &b, 1, 0, 0))
		जाओ fail;

	b = WILC_FW_TX_RATE_AUTO;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_CURRENT_TX_RATE, &b, 1, 0, 0))
		जाओ fail;

	b = WILC_FW_OPER_MODE_G_MIXED_11B_2;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_11G_OPERATING_MODE, &b, 1, 0, 0))
		जाओ fail;

	b = WILC_FW_PREAMBLE_SHORT;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_PREAMBLE, &b, 1, 0, 0))
		जाओ fail;

	b = WILC_FW_11N_PROT_AUTO;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_11N_PROT_MECH, &b, 1, 0, 0))
		जाओ fail;

	b = WILC_FW_ACTIVE_SCAN;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_SCAN_TYPE, &b, 1, 0, 0))
		जाओ fail;

	b = WILC_FW_SITE_SURVEY_OFF;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_SITE_SURVEY, &b, 1, 0, 0))
		जाओ fail;

	hw = 0xffff;
	cpu_to_le16s(&hw);
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_RTS_THRESHOLD, (u8 *)&hw, 2, 0, 0))
		जाओ fail;

	hw = 2346;
	cpu_to_le16s(&hw);
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_FRAG_THRESHOLD, (u8 *)&hw, 2, 0, 0))
		जाओ fail;

	b = 0;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_BCAST_SSID, &b, 1, 0, 0))
		जाओ fail;

	b = 1;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_QOS_ENABLE, &b, 1, 0, 0))
		जाओ fail;

	b = WILC_FW_NO_POWERSAVE;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_POWER_MANAGEMENT, &b, 1, 0, 0))
		जाओ fail;

	b = WILC_FW_SEC_NO;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_11I_MODE, &b, 1, 0, 0))
		जाओ fail;

	b = WILC_FW_AUTH_OPEN_SYSTEM;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_AUTH_TYPE, &b, 1, 0, 0))
		जाओ fail;

	b = 3;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_LISTEN_INTERVAL, &b, 1, 0, 0))
		जाओ fail;

	b = 3;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_DTIM_PERIOD, &b, 1, 0, 0))
		जाओ fail;

	b = WILC_FW_ACK_POLICY_NORMAL;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_ACK_POLICY, &b, 1, 0, 0))
		जाओ fail;

	b = 0;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_USER_CONTROL_ON_TX_POWER, &b, 1,
			       0, 0))
		जाओ fail;

	b = 48;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_TX_POWER_LEVEL_11A, &b, 1, 0, 0))
		जाओ fail;

	b = 28;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_TX_POWER_LEVEL_11B, &b, 1, 0, 0))
		जाओ fail;

	hw = 100;
	cpu_to_le16s(&hw);
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_BEACON_INTERVAL, (u8 *)&hw, 2, 0, 0))
		जाओ fail;

	b = WILC_FW_REKEY_POLICY_DISABLE;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_REKEY_POLICY, &b, 1, 0, 0))
		जाओ fail;

	w = 84600;
	cpu_to_le32s(&w);
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_REKEY_PERIOD, (u8 *)&w, 4, 0, 0))
		जाओ fail;

	w = 500;
	cpu_to_le32s(&w);
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_REKEY_PACKET_COUNT, (u8 *)&w, 4, 0,
			       0))
		जाओ fail;

	b = 1;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_SHORT_SLOT_ALLOWED, &b, 1, 0,
			       0))
		जाओ fail;

	b = WILC_FW_ERP_PROT_SELF_CTS;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_11N_ERP_PROT_TYPE, &b, 1, 0, 0))
		जाओ fail;

	b = 1;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_11N_ENABLE, &b, 1, 0, 0))
		जाओ fail;

	b = WILC_FW_11N_OP_MODE_HT_MIXED;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_11N_OPERATING_MODE, &b, 1, 0, 0))
		जाओ fail;

	b = 1;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_11N_TXOP_PROT_DISABLE, &b, 1, 0, 0))
		जाओ fail;

	b = WILC_FW_OBBS_NONHT_DETECT_PROTECT_REPORT;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_11N_OBSS_NONHT_DETECTION, &b, 1,
			       0, 0))
		जाओ fail;

	b = WILC_FW_HT_PROT_RTS_CTS_NONHT;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_11N_HT_PROT_TYPE, &b, 1, 0, 0))
		जाओ fail;

	b = 0;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_11N_RIFS_PROT_ENABLE, &b, 1, 0,
			       0))
		जाओ fail;

	b = 7;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_11N_CURRENT_TX_MCS, &b, 1, 0, 0))
		जाओ fail;

	b = 1;
	अगर (!wilc_wlan_cfg_set(vअगर, 0, WID_11N_IMMEDIATE_BA_ENABLED, &b, 1,
			       1, 1))
		जाओ fail;

	वापस 0;

fail:
	वापस -EINVAL;
पूर्ण

अटल व्योम wlan_deinitialize_thपढ़ोs(काष्ठा net_device *dev)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc *wl = vअगर->wilc;

	wl->बंद = 1;

	complete(&wl->txq_event);

	अगर (wl->txq_thपढ़ो) अणु
		kthपढ़ो_stop(wl->txq_thपढ़ो);
		wl->txq_thपढ़ो = शून्य;
	पूर्ण
पूर्ण

अटल व्योम wilc_wlan_deinitialize(काष्ठा net_device *dev)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc *wl = vअगर->wilc;

	अगर (!wl) अणु
		netdev_err(dev, "wl is NULL\n");
		वापस;
	पूर्ण

	अगर (wl->initialized) अणु
		netdev_info(dev, "Deinitializing wilc1000...\n");

		अगर (!wl->dev_irq_num &&
		    wl->hअगर_func->disable_पूर्णांकerrupt) अणु
			mutex_lock(&wl->hअगर_cs);
			wl->hअगर_func->disable_पूर्णांकerrupt(wl);
			mutex_unlock(&wl->hअगर_cs);
		पूर्ण
		complete(&wl->txq_event);

		wlan_deinitialize_thपढ़ोs(dev);
		deinit_irq(dev);

		wilc_wlan_stop(wl, vअगर);
		wilc_wlan_cleanup(dev);

		wl->initialized = false;

		netdev_dbg(dev, "wilc1000 deinitialization Done\n");
	पूर्ण अन्यथा अणु
		netdev_dbg(dev, "wilc1000 is not initialized\n");
	पूर्ण
पूर्ण

अटल पूर्णांक wlan_initialize_thपढ़ोs(काष्ठा net_device *dev)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc *wilc = vअगर->wilc;

	wilc->txq_thपढ़ो = kthपढ़ो_run(wilc_txq_task, (व्योम *)wilc,
				       "K_TXQ_TASK");
	अगर (IS_ERR(wilc->txq_thपढ़ो)) अणु
		netdev_err(dev, "couldn't create TXQ thread\n");
		wilc->बंद = 0;
		वापस PTR_ERR(wilc->txq_thपढ़ो);
	पूर्ण
	रुको_क्रम_completion(&wilc->txq_thपढ़ो_started);

	वापस 0;
पूर्ण

अटल पूर्णांक wilc_wlan_initialize(काष्ठा net_device *dev, काष्ठा wilc_vअगर *vअगर)
अणु
	पूर्णांक ret = 0;
	काष्ठा wilc *wl = vअगर->wilc;

	अगर (!wl->initialized) अणु
		wl->mac_status = WILC_MAC_STATUS_INIT;
		wl->बंद = 0;

		ret = wilc_wlan_init(dev);
		अगर (ret)
			वापस ret;

		ret = wlan_initialize_thपढ़ोs(dev);
		अगर (ret)
			जाओ fail_wilc_wlan;

		अगर (wl->dev_irq_num && init_irq(dev)) अणु
			ret = -EIO;
			जाओ fail_thपढ़ोs;
		पूर्ण

		अगर (!wl->dev_irq_num &&
		    wl->hअगर_func->enable_पूर्णांकerrupt &&
		    wl->hअगर_func->enable_पूर्णांकerrupt(wl)) अणु
			ret = -EIO;
			जाओ fail_irq_init;
		पूर्ण

		ret = wilc_wlan_get_firmware(dev);
		अगर (ret)
			जाओ fail_irq_enable;

		ret = wilc1000_firmware_करोwnload(dev);
		अगर (ret)
			जाओ fail_irq_enable;

		ret = wilc_start_firmware(dev);
		अगर (ret)
			जाओ fail_irq_enable;

		अगर (wilc_wlan_cfg_get(vअगर, 1, WID_FIRMWARE_VERSION, 1, 0)) अणु
			पूर्णांक size;
			अक्षर firmware_ver[20];

			size = wilc_wlan_cfg_get_val(wl, WID_FIRMWARE_VERSION,
						     firmware_ver,
						     माप(firmware_ver));
			firmware_ver[size] = '\0';
			netdev_dbg(dev, "Firmware Ver = %s\n", firmware_ver);
		पूर्ण

		ret = wilc_init_fw_config(dev, vअगर);
		अगर (ret) अणु
			netdev_err(dev, "Failed to configure firmware\n");
			जाओ fail_fw_start;
		पूर्ण
		wl->initialized = true;
		वापस 0;

fail_fw_start:
		wilc_wlan_stop(wl, vअगर);

fail_irq_enable:
		अगर (!wl->dev_irq_num &&
		    wl->hअगर_func->disable_पूर्णांकerrupt)
			wl->hअगर_func->disable_पूर्णांकerrupt(wl);
fail_irq_init:
		अगर (wl->dev_irq_num)
			deinit_irq(dev);
fail_thपढ़ोs:
		wlan_deinitialize_thपढ़ोs(dev);
fail_wilc_wlan:
		wilc_wlan_cleanup(dev);
		netdev_err(dev, "WLAN initialization FAILED\n");
	पूर्ण अन्यथा अणु
		netdev_dbg(dev, "wilc1000 already initialized\n");
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक mac_init_fn(काष्ठा net_device *ndev)
अणु
	netअगर_start_queue(ndev);
	netअगर_stop_queue(ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक wilc_mac_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(ndev);
	काष्ठा wilc *wl = vअगर->wilc;
	पूर्णांक ret = 0;
	काष्ठा mgmt_frame_regs mgmt_regs = अणुपूर्ण;

	अगर (!wl || !wl->dev) अणु
		netdev_err(ndev, "device not ready\n");
		वापस -ENODEV;
	पूर्ण

	netdev_dbg(ndev, "MAC OPEN[%p]\n", ndev);

	ret = wilc_init_host_पूर्णांक(ndev);
	अगर (ret)
		वापस ret;

	ret = wilc_wlan_initialize(ndev, vअगर);
	अगर (ret) अणु
		wilc_deinit_host_पूर्णांक(ndev);
		वापस ret;
	पूर्ण

	wilc_set_operation_mode(vअगर, wilc_get_vअगर_idx(vअगर), vअगर->अगरtype,
				vअगर->idx);

	अगर (is_valid_ether_addr(ndev->dev_addr))
		wilc_set_mac_address(vअगर, ndev->dev_addr);
	अन्यथा
		wilc_get_mac_address(vअगर, ndev->dev_addr);
	netdev_dbg(ndev, "Mac address: %pM\n", ndev->dev_addr);

	अगर (!is_valid_ether_addr(ndev->dev_addr)) अणु
		netdev_err(ndev, "Wrong MAC address\n");
		wilc_deinit_host_पूर्णांक(ndev);
		wilc_wlan_deinitialize(ndev);
		वापस -EINVAL;
	पूर्ण

	mgmt_regs.पूर्णांकerface_stypes = vअगर->mgmt_reg_stypes;
	/* so we detect a change */
	vअगर->mgmt_reg_stypes = 0;
	wilc_update_mgmt_frame_registrations(vअगर->ndev->ieee80211_ptr->wiphy,
					     vअगर->ndev->ieee80211_ptr,
					     &mgmt_regs);
	netअगर_wake_queue(ndev);
	wl->खोलो_अगरcs++;
	vअगर->mac_खोलोed = 1;
	वापस 0;
पूर्ण

अटल काष्ठा net_device_stats *mac_stats(काष्ठा net_device *dev)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);

	वापस &vअगर->netstats;
पूर्ण

अटल पूर्णांक wilc_set_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	पूर्णांक result;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc *wilc = vअगर->wilc;
	काष्ठा sockaddr *addr = (काष्ठा sockaddr *)p;
	अचिन्हित अक्षर mac_addr[ETH_ALEN];
	काष्ठा wilc_vअगर *पंचांगp_vअगर;
	पूर्णांक srcu_idx;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	अगर (!vअगर->mac_खोलोed) अणु
		eth_commit_mac_addr_change(dev, p);
		वापस 0;
	पूर्ण

	/* Verअगरy MAC Address is not alपढ़ोy in use: */

	srcu_idx = srcu_पढ़ो_lock(&wilc->srcu);
	list_क्रम_each_entry_rcu(पंचांगp_vअगर, &wilc->vअगर_list, list) अणु
		wilc_get_mac_address(पंचांगp_vअगर, mac_addr);
		अगर (ether_addr_equal(addr->sa_data, mac_addr)) अणु
			अगर (vअगर != पंचांगp_vअगर) अणु
				srcu_पढ़ो_unlock(&wilc->srcu, srcu_idx);
				वापस -EADDRNOTAVAIL;
			पूर्ण
			srcu_पढ़ो_unlock(&wilc->srcu, srcu_idx);
			वापस 0;
		पूर्ण
	पूर्ण
	srcu_पढ़ो_unlock(&wilc->srcu, srcu_idx);

	result = wilc_set_mac_address(vअगर, (u8 *)addr->sa_data);
	अगर (result)
		वापस result;

	eth_commit_mac_addr_change(dev, p);
	वापस result;
पूर्ण

अटल व्योम wilc_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_hw_addr *ha;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	पूर्णांक i;
	u8 *mc_list;
	u8 *cur_mc;

	अगर (dev->flags & IFF_PROMISC)
		वापस;

	अगर (dev->flags & IFF_ALLMULTI ||
	    dev->mc.count > WILC_MULTICAST_TABLE_SIZE) अणु
		wilc_setup_multicast_filter(vअगर, 0, 0, शून्य);
		वापस;
	पूर्ण

	अगर (dev->mc.count == 0) अणु
		wilc_setup_multicast_filter(vअगर, 1, 0, शून्य);
		वापस;
	पूर्ण

	mc_list = kदो_स्मृति_array(dev->mc.count, ETH_ALEN, GFP_ATOMIC);
	अगर (!mc_list)
		वापस;

	cur_mc = mc_list;
	i = 0;
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		स_नकल(cur_mc, ha->addr, ETH_ALEN);
		netdev_dbg(dev, "Entry[%d]: %pM\n", i, cur_mc);
		i++;
		cur_mc += ETH_ALEN;
	पूर्ण

	अगर (wilc_setup_multicast_filter(vअगर, 1, dev->mc.count, mc_list))
		kमुक्त(mc_list);
पूर्ण

अटल व्योम wilc_tx_complete(व्योम *priv, पूर्णांक status)
अणु
	काष्ठा tx_complete_data *pv_data = priv;

	dev_kमुक्त_skb(pv_data->skb);
	kमुक्त(pv_data);
पूर्ण

netdev_tx_t wilc_mac_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(ndev);
	काष्ठा wilc *wilc = vअगर->wilc;
	काष्ठा tx_complete_data *tx_data = शून्य;
	पूर्णांक queue_count;

	अगर (skb->dev != ndev) अणु
		netdev_err(ndev, "Packet not destined to this device\n");
		वापस NETDEV_TX_OK;
	पूर्ण

	tx_data = kदो_स्मृति(माप(*tx_data), GFP_ATOMIC);
	अगर (!tx_data) अणु
		dev_kमुक्त_skb(skb);
		netअगर_wake_queue(ndev);
		वापस NETDEV_TX_OK;
	पूर्ण

	tx_data->buff = skb->data;
	tx_data->size = skb->len;
	tx_data->skb  = skb;

	vअगर->netstats.tx_packets++;
	vअगर->netstats.tx_bytes += tx_data->size;
	queue_count = wilc_wlan_txq_add_net_pkt(ndev, tx_data,
						tx_data->buff, tx_data->size,
						wilc_tx_complete);

	अगर (queue_count > FLOW_CONTROL_UPPER_THRESHOLD) अणु
		पूर्णांक srcu_idx;
		काष्ठा wilc_vअगर *vअगर;

		srcu_idx = srcu_पढ़ो_lock(&wilc->srcu);
		list_क्रम_each_entry_rcu(vअगर, &wilc->vअगर_list, list) अणु
			अगर (vअगर->mac_खोलोed)
				netअगर_stop_queue(vअगर->ndev);
		पूर्ण
		srcu_पढ़ो_unlock(&wilc->srcu, srcu_idx);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक wilc_mac_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(ndev);
	काष्ठा wilc *wl = vअगर->wilc;

	netdev_dbg(ndev, "Mac close\n");

	अगर (wl->खोलो_अगरcs > 0)
		wl->खोलो_अगरcs--;
	अन्यथा
		वापस 0;

	अगर (vअगर->ndev) अणु
		netअगर_stop_queue(vअगर->ndev);

		wilc_deinit_host_पूर्णांक(vअगर->ndev);
	पूर्ण

	अगर (wl->खोलो_अगरcs == 0) अणु
		netdev_dbg(ndev, "Deinitializing wilc1000\n");
		wl->बंद = 1;
		wilc_wlan_deinitialize(ndev);
	पूर्ण

	vअगर->mac_खोलोed = 0;

	वापस 0;
पूर्ण

व्योम wilc_frmw_to_host(काष्ठा wilc *wilc, u8 *buff, u32 size,
		       u32 pkt_offset)
अणु
	अचिन्हित पूर्णांक frame_len = 0;
	पूर्णांक stats;
	अचिन्हित अक्षर *buff_to_send = शून्य;
	काष्ठा sk_buff *skb;
	काष्ठा net_device *wilc_netdev;
	काष्ठा wilc_vअगर *vअगर;

	अगर (!wilc)
		वापस;

	wilc_netdev = get_अगर_handler(wilc, buff);
	अगर (!wilc_netdev)
		वापस;

	buff += pkt_offset;
	vअगर = netdev_priv(wilc_netdev);

	अगर (size > 0) अणु
		frame_len = size;
		buff_to_send = buff;

		skb = dev_alloc_skb(frame_len);
		अगर (!skb)
			वापस;

		skb->dev = wilc_netdev;

		skb_put_data(skb, buff_to_send, frame_len);

		skb->protocol = eth_type_trans(skb, wilc_netdev);
		vअगर->netstats.rx_packets++;
		vअगर->netstats.rx_bytes += frame_len;
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		stats = netअगर_rx(skb);
		netdev_dbg(wilc_netdev, "netif_rx ret value is: %d\n", stats);
	पूर्ण
पूर्ण

व्योम wilc_wfi_mgmt_rx(काष्ठा wilc *wilc, u8 *buff, u32 size)
अणु
	पूर्णांक srcu_idx;
	काष्ठा wilc_vअगर *vअगर;

	srcu_idx = srcu_पढ़ो_lock(&wilc->srcu);
	list_क्रम_each_entry_rcu(vअगर, &wilc->vअगर_list, list) अणु
		u16 type = le16_to_cpup((__le16 *)buff);
		u32 type_bit = BIT(type >> 4);

		अगर (vअगर->priv.p2p_listen_state &&
		    vअगर->mgmt_reg_stypes & type_bit)
			wilc_wfi_p2p_rx(vअगर, buff, size);

		अगर (vअगर->monitor_flag)
			wilc_wfi_monitor_rx(wilc->monitor_dev, buff, size);
	पूर्ण
	srcu_पढ़ो_unlock(&wilc->srcu, srcu_idx);
पूर्ण

अटल स्थिर काष्ठा net_device_ops wilc_netdev_ops = अणु
	.nकरो_init = mac_init_fn,
	.nकरो_खोलो = wilc_mac_खोलो,
	.nकरो_stop = wilc_mac_बंद,
	.nकरो_set_mac_address = wilc_set_mac_addr,
	.nकरो_start_xmit = wilc_mac_xmit,
	.nकरो_get_stats = mac_stats,
	.nकरो_set_rx_mode  = wilc_set_multicast_list,
पूर्ण;

व्योम wilc_netdev_cleanup(काष्ठा wilc *wilc)
अणु
	काष्ठा wilc_vअगर *vअगर;
	पूर्णांक srcu_idx, अगरc_cnt = 0;

	अगर (!wilc)
		वापस;

	अगर (wilc->firmware) अणु
		release_firmware(wilc->firmware);
		wilc->firmware = शून्य;
	पूर्ण

	srcu_idx = srcu_पढ़ो_lock(&wilc->srcu);
	list_क्रम_each_entry_rcu(vअगर, &wilc->vअगर_list, list) अणु
		अगर (vअगर->ndev)
			unरेजिस्टर_netdev(vअगर->ndev);
	पूर्ण
	srcu_पढ़ो_unlock(&wilc->srcu, srcu_idx);

	wilc_wfi_deinit_mon_पूर्णांकerface(wilc, false);
	flush_workqueue(wilc->hअगर_workqueue);
	destroy_workqueue(wilc->hअगर_workqueue);

	जबतक (अगरc_cnt < WILC_NUM_CONCURRENT_IFC) अणु
		mutex_lock(&wilc->vअगर_mutex);
		अगर (wilc->vअगर_num <= 0) अणु
			mutex_unlock(&wilc->vअगर_mutex);
			अवरोध;
		पूर्ण
		vअगर = wilc_get_wl_to_vअगर(wilc);
		अगर (!IS_ERR(vअगर))
			list_del_rcu(&vअगर->list);

		wilc->vअगर_num--;
		mutex_unlock(&wilc->vअगर_mutex);
		synchronize_srcu(&wilc->srcu);
		अगरc_cnt++;
	पूर्ण

	wilc_wlan_cfg_deinit(wilc);
	wlan_deinit_locks(wilc);
	kमुक्त(wilc->bus_data);
	wiphy_unरेजिस्टर(wilc->wiphy);
	wiphy_मुक्त(wilc->wiphy);
पूर्ण
EXPORT_SYMBOL_GPL(wilc_netdev_cleanup);

अटल u8 wilc_get_available_idx(काष्ठा wilc *wl)
अणु
	पूर्णांक idx = 0;
	काष्ठा wilc_vअगर *vअगर;
	पूर्णांक srcu_idx;

	srcu_idx = srcu_पढ़ो_lock(&wl->srcu);
	list_क्रम_each_entry_rcu(vअगर, &wl->vअगर_list, list) अणु
		अगर (vअगर->idx == 0)
			idx = 1;
		अन्यथा
			idx = 0;
	पूर्ण
	srcu_पढ़ो_unlock(&wl->srcu, srcu_idx);
	वापस idx;
पूर्ण

काष्ठा wilc_vअगर *wilc_netdev_अगरc_init(काष्ठा wilc *wl, स्थिर अक्षर *name,
				      पूर्णांक vअगर_type, क्रमागत nl80211_अगरtype type,
				      bool rtnl_locked)
अणु
	काष्ठा net_device *ndev;
	काष्ठा wilc_vअगर *vअगर;
	पूर्णांक ret;

	ndev = alloc_etherdev(माप(*vअगर));
	अगर (!ndev)
		वापस ERR_PTR(-ENOMEM);

	vअगर = netdev_priv(ndev);
	ndev->ieee80211_ptr = &vअगर->priv.wdev;
	म_नकल(ndev->name, name);
	vअगर->wilc = wl;
	vअगर->ndev = ndev;
	ndev->ml_priv = vअगर;

	ndev->netdev_ops = &wilc_netdev_ops;

	SET_NETDEV_DEV(ndev, wiphy_dev(wl->wiphy));

	vअगर->priv.wdev.wiphy = wl->wiphy;
	vअगर->priv.wdev.netdev = ndev;
	vअगर->priv.wdev.अगरtype = type;
	vअगर->priv.dev = ndev;

	अगर (rtnl_locked)
		ret = cfg80211_रेजिस्टर_netdevice(ndev);
	अन्यथा
		ret = रेजिस्टर_netdev(ndev);

	अगर (ret) अणु
		मुक्त_netdev(ndev);
		वापस ERR_PTR(-EFAULT);
	पूर्ण

	ndev->needs_मुक्त_netdev = true;
	vअगर->अगरtype = vअगर_type;
	vअगर->idx = wilc_get_available_idx(wl);
	vअगर->mac_खोलोed = 0;
	mutex_lock(&wl->vअगर_mutex);
	list_add_tail_rcu(&vअगर->list, &wl->vअगर_list);
	wl->vअगर_num += 1;
	mutex_unlock(&wl->vअगर_mutex);
	synchronize_srcu(&wl->srcu);

	वापस vअगर;
पूर्ण

MODULE_LICENSE("GPL");
MODULE_FIRMWARE(WILC1000_FW(WILC1000_API_VER));
