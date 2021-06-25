<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1251
 *
 * Copyright (C) 2008-2009 Nokia Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/firmware.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/crc32.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>

#समावेश "wl1251.h"
#समावेश "wl12xx_80211.h"
#समावेश "reg.h"
#समावेश "io.h"
#समावेश "cmd.h"
#समावेश "event.h"
#समावेश "tx.h"
#समावेश "rx.h"
#समावेश "ps.h"
#समावेश "init.h"
#समावेश "debugfs.h"
#समावेश "boot.h"

व्योम wl1251_enable_पूर्णांकerrupts(काष्ठा wl1251 *wl)
अणु
	wl->अगर_ops->enable_irq(wl);
पूर्ण

व्योम wl1251_disable_पूर्णांकerrupts(काष्ठा wl1251 *wl)
अणु
	wl->अगर_ops->disable_irq(wl);
पूर्ण

अटल पूर्णांक wl1251_घातer_off(काष्ठा wl1251 *wl)
अणु
	वापस wl->अगर_ops->घातer(wl, false);
पूर्ण

अटल पूर्णांक wl1251_घातer_on(काष्ठा wl1251 *wl)
अणु
	वापस wl->अगर_ops->घातer(wl, true);
पूर्ण

अटल पूर्णांक wl1251_fetch_firmware(काष्ठा wl1251 *wl)
अणु
	स्थिर काष्ठा firmware *fw;
	काष्ठा device *dev = wiphy_dev(wl->hw->wiphy);
	पूर्णांक ret;

	ret = request_firmware(&fw, WL1251_FW_NAME, dev);

	अगर (ret < 0) अणु
		wl1251_error("could not get firmware: %d", ret);
		वापस ret;
	पूर्ण

	अगर (fw->size % 4) अणु
		wl1251_error("firmware size is not multiple of 32 bits: %zu",
			     fw->size);
		ret = -EILSEQ;
		जाओ out;
	पूर्ण

	wl->fw_len = fw->size;
	wl->fw = vदो_स्मृति(wl->fw_len);

	अगर (!wl->fw) अणु
		wl1251_error("could not allocate memory for the firmware");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	स_नकल(wl->fw, fw->data, wl->fw_len);

	ret = 0;

out:
	release_firmware(fw);

	वापस ret;
पूर्ण

अटल पूर्णांक wl1251_fetch_nvs(काष्ठा wl1251 *wl)
अणु
	स्थिर काष्ठा firmware *fw;
	काष्ठा device *dev = wiphy_dev(wl->hw->wiphy);
	पूर्णांक ret;

	ret = request_firmware(&fw, WL1251_NVS_NAME, dev);

	अगर (ret < 0) अणु
		wl1251_error("could not get nvs file: %d", ret);
		वापस ret;
	पूर्ण

	अगर (fw->size % 4) अणु
		wl1251_error("nvs size is not multiple of 32 bits: %zu",
			     fw->size);
		ret = -EILSEQ;
		जाओ out;
	पूर्ण

	wl->nvs = kmemdup(fw->data, fw->size, GFP_KERNEL);

	अगर (!wl->nvs) अणु
		wl1251_error("could not allocate memory for the nvs file");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	wl->nvs_len = fw->size;

	ret = 0;

out:
	release_firmware(fw);

	वापस ret;
पूर्ण

अटल व्योम wl1251_fw_wakeup(काष्ठा wl1251 *wl)
अणु
	u32 elp_reg;

	elp_reg = ELPCTRL_WAKE_UP;
	wl1251_ग_लिखो_elp(wl, HW_ACCESS_ELP_CTRL_REG_ADDR, elp_reg);
	elp_reg = wl1251_पढ़ो_elp(wl, HW_ACCESS_ELP_CTRL_REG_ADDR);

	अगर (!(elp_reg & ELPCTRL_WLAN_READY))
		wl1251_warning("WLAN not ready");
पूर्ण

अटल पूर्णांक wl1251_chip_wakeup(काष्ठा wl1251 *wl)
अणु
	पूर्णांक ret;

	ret = wl1251_घातer_on(wl);
	अगर (ret < 0)
		वापस ret;

	msleep(WL1251_POWER_ON_SLEEP);
	wl->अगर_ops->reset(wl);

	/* We करोn't need a real memory partition here, because we only want
	 * to use the रेजिस्टरs at this poपूर्णांक. */
	wl1251_set_partition(wl,
			     0x00000000,
			     0x00000000,
			     REGISTERS_BASE,
			     REGISTERS_DOWN_SIZE);

	/* ELP module wake up */
	wl1251_fw_wakeup(wl);

	/* whal_FwCtrl_BootSm() */

	/* 0. पढ़ो chip id from CHIP_ID */
	wl->chip_id = wl1251_reg_पढ़ो32(wl, CHIP_ID_B);

	/* 1. check अगर chip id is valid */

	चयन (wl->chip_id) अणु
	हाल CHIP_ID_1251_PG12:
		wl1251_debug(DEBUG_BOOT, "chip id 0x%x (1251 PG12)",
			     wl->chip_id);
		अवरोध;
	हाल CHIP_ID_1251_PG11:
		wl1251_debug(DEBUG_BOOT, "chip id 0x%x (1251 PG11)",
			     wl->chip_id);
		अवरोध;
	हाल CHIP_ID_1251_PG10:
	शेष:
		wl1251_error("unsupported chip id: 0x%x", wl->chip_id);
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (wl->fw == शून्य) अणु
		ret = wl1251_fetch_firmware(wl);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण

#घोषणा WL1251_IRQ_LOOP_COUNT 10
अटल व्योम wl1251_irq_work(काष्ठा work_काष्ठा *work)
अणु
	u32 पूर्णांकr, ctr = WL1251_IRQ_LOOP_COUNT;
	काष्ठा wl1251 *wl =
		container_of(work, काष्ठा wl1251, irq_work);
	पूर्णांक ret;

	mutex_lock(&wl->mutex);

	wl1251_debug(DEBUG_IRQ, "IRQ work");

	अगर (wl->state == WL1251_STATE_OFF)
		जाओ out;

	ret = wl1251_ps_elp_wakeup(wl);
	अगर (ret < 0)
		जाओ out;

	wl1251_reg_ग_लिखो32(wl, ACX_REG_INTERRUPT_MASK, WL1251_ACX_INTR_ALL);

	पूर्णांकr = wl1251_reg_पढ़ो32(wl, ACX_REG_INTERRUPT_CLEAR);
	wl1251_debug(DEBUG_IRQ, "intr: 0x%x", पूर्णांकr);

	करो अणु
		अगर (wl->data_path) अणु
			wl->rx_counter = wl1251_mem_पढ़ो32(
				wl, wl->data_path->rx_control_addr);

			/* We handle a frmware bug here */
			चयन ((wl->rx_counter - wl->rx_handled) & 0xf) अणु
			हाल 0:
				wl1251_debug(DEBUG_IRQ,
					     "RX: FW and host in sync");
				पूर्णांकr &= ~WL1251_ACX_INTR_RX0_DATA;
				पूर्णांकr &= ~WL1251_ACX_INTR_RX1_DATA;
				अवरोध;
			हाल 1:
				wl1251_debug(DEBUG_IRQ, "RX: FW +1");
				पूर्णांकr |= WL1251_ACX_INTR_RX0_DATA;
				पूर्णांकr &= ~WL1251_ACX_INTR_RX1_DATA;
				अवरोध;
			हाल 2:
				wl1251_debug(DEBUG_IRQ, "RX: FW +2");
				पूर्णांकr |= WL1251_ACX_INTR_RX0_DATA;
				पूर्णांकr |= WL1251_ACX_INTR_RX1_DATA;
				अवरोध;
			शेष:
				wl1251_warning(
					"RX: FW and host out of sync: %d",
					wl->rx_counter - wl->rx_handled);
				अवरोध;
			पूर्ण

			wl->rx_handled = wl->rx_counter;

			wl1251_debug(DEBUG_IRQ, "RX counter: %d",
				     wl->rx_counter);
		पूर्ण

		पूर्णांकr &= wl->पूर्णांकr_mask;

		अगर (पूर्णांकr == 0) अणु
			wl1251_debug(DEBUG_IRQ, "INTR is 0");
			जाओ out_sleep;
		पूर्ण

		अगर (पूर्णांकr & WL1251_ACX_INTR_RX0_DATA) अणु
			wl1251_debug(DEBUG_IRQ, "WL1251_ACX_INTR_RX0_DATA");
			wl1251_rx(wl);
		पूर्ण

		अगर (पूर्णांकr & WL1251_ACX_INTR_RX1_DATA) अणु
			wl1251_debug(DEBUG_IRQ, "WL1251_ACX_INTR_RX1_DATA");
			wl1251_rx(wl);
		पूर्ण

		अगर (पूर्णांकr & WL1251_ACX_INTR_TX_RESULT) अणु
			wl1251_debug(DEBUG_IRQ, "WL1251_ACX_INTR_TX_RESULT");
			wl1251_tx_complete(wl);
		पूर्ण

		अगर (पूर्णांकr & WL1251_ACX_INTR_EVENT_A) अणु
			wl1251_debug(DEBUG_IRQ, "WL1251_ACX_INTR_EVENT_A");
			wl1251_event_handle(wl, 0);
		पूर्ण

		अगर (पूर्णांकr & WL1251_ACX_INTR_EVENT_B) अणु
			wl1251_debug(DEBUG_IRQ, "WL1251_ACX_INTR_EVENT_B");
			wl1251_event_handle(wl, 1);
		पूर्ण

		अगर (पूर्णांकr & WL1251_ACX_INTR_INIT_COMPLETE)
			wl1251_debug(DEBUG_IRQ,
				     "WL1251_ACX_INTR_INIT_COMPLETE");

		अगर (--ctr == 0)
			अवरोध;

		पूर्णांकr = wl1251_reg_पढ़ो32(wl, ACX_REG_INTERRUPT_CLEAR);
	पूर्ण जबतक (पूर्णांकr);

out_sleep:
	wl1251_reg_ग_लिखो32(wl, ACX_REG_INTERRUPT_MASK, ~(wl->पूर्णांकr_mask));
	wl1251_ps_elp_sleep(wl);

out:
	mutex_unlock(&wl->mutex);
पूर्ण

अटल पूर्णांक wl1251_join(काष्ठा wl1251 *wl, u8 bss_type, u8 channel,
		       u16 beacon_पूर्णांकerval, u8 dtim_period)
अणु
	पूर्णांक ret;

	ret = wl1251_acx_frame_rates(wl, DEFAULT_HW_GEN_TX_RATE,
				     DEFAULT_HW_GEN_MODULATION_TYPE,
				     wl->tx_mgmt_frm_rate,
				     wl->tx_mgmt_frm_mod);
	अगर (ret < 0)
		जाओ out;

	/*
	 * Join command applies filters, and अगर we are not associated,
	 * BSSID filter must be disabled क्रम association to work.
	 */
	अगर (is_zero_ether_addr(wl->bssid))
		wl->rx_config &= ~CFG_BSSID_FILTER_EN;

	ret = wl1251_cmd_join(wl, bss_type, channel, beacon_पूर्णांकerval,
			      dtim_period);
	अगर (ret < 0)
		जाओ out;

	ret = wl1251_event_रुको(wl, JOIN_EVENT_COMPLETE_ID, 100);
	अगर (ret < 0)
		wl1251_warning("join timeout");

out:
	वापस ret;
पूर्ण

अटल व्योम wl1251_op_tx(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_tx_control *control,
			 काष्ठा sk_buff *skb)
अणु
	काष्ठा wl1251 *wl = hw->priv;
	अचिन्हित दीर्घ flags;

	skb_queue_tail(&wl->tx_queue, skb);

	/*
	 * The chip specअगरic setup must run beक्रमe the first TX packet -
	 * beक्रमe that, the tx_work will not be initialized!
	 */

	ieee80211_queue_work(wl->hw, &wl->tx_work);

	/*
	 * The workqueue is slow to process the tx_queue and we need stop
	 * the queue here, otherwise the queue will get too दीर्घ.
	 */
	अगर (skb_queue_len(&wl->tx_queue) >= WL1251_TX_QUEUE_HIGH_WATERMARK) अणु
		wl1251_debug(DEBUG_TX, "op_tx: tx_queue full, stop queues");

		spin_lock_irqsave(&wl->wl_lock, flags);
		ieee80211_stop_queues(wl->hw);
		wl->tx_queue_stopped = true;
		spin_unlock_irqrestore(&wl->wl_lock, flags);
	पूर्ण
पूर्ण

अटल पूर्णांक wl1251_op_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा wl1251 *wl = hw->priv;
	काष्ठा wiphy *wiphy = hw->wiphy;
	पूर्णांक ret = 0;

	wl1251_debug(DEBUG_MAC80211, "mac80211 start");

	mutex_lock(&wl->mutex);

	अगर (wl->state != WL1251_STATE_OFF) अणु
		wl1251_error("cannot start because not in off state: %d",
			     wl->state);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = wl1251_chip_wakeup(wl);
	अगर (ret < 0)
		जाओ out;

	ret = wl1251_boot(wl);
	अगर (ret < 0)
		जाओ out;

	ret = wl1251_hw_init(wl);
	अगर (ret < 0)
		जाओ out;

	ret = wl1251_acx_station_id(wl);
	अगर (ret < 0)
		जाओ out;

	wl->state = WL1251_STATE_ON;

	wl1251_info("firmware booted (%s)", wl->fw_ver);

	/* update hw/fw version info in wiphy काष्ठा */
	wiphy->hw_version = wl->chip_id;
	म_नकलन(wiphy->fw_version, wl->fw_ver, माप(wiphy->fw_version));

out:
	अगर (ret < 0)
		wl1251_घातer_off(wl);

	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

अटल व्योम wl1251_op_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा wl1251 *wl = hw->priv;

	wl1251_info("down");

	wl1251_debug(DEBUG_MAC80211, "mac80211 stop");

	mutex_lock(&wl->mutex);

	WARN_ON(wl->state != WL1251_STATE_ON);

	अगर (wl->scanning) अणु
		काष्ठा cfg80211_scan_info info = अणु
			.पातed = true,
		पूर्ण;

		ieee80211_scan_completed(wl->hw, &info);
		wl->scanning = false;
	पूर्ण

	wl->state = WL1251_STATE_OFF;

	wl1251_disable_पूर्णांकerrupts(wl);

	mutex_unlock(&wl->mutex);

	cancel_work_sync(&wl->irq_work);
	cancel_work_sync(&wl->tx_work);
	cancel_delayed_work_sync(&wl->elp_work);

	mutex_lock(&wl->mutex);

	/* let's notअगरy MAC80211 about the reमुख्यing pending TX frames */
	wl1251_tx_flush(wl);
	wl1251_घातer_off(wl);

	eth_zero_addr(wl->bssid);
	wl->listen_पूर्णांक = 1;
	wl->bss_type = MAX_BSS_TYPE;

	wl->data_in_count = 0;
	wl->rx_counter = 0;
	wl->rx_handled = 0;
	wl->rx_current_buffer = 0;
	wl->rx_last_id = 0;
	wl->next_tx_complete = 0;
	wl->elp = false;
	wl->station_mode = STATION_ACTIVE_MODE;
	wl->psm_entry_retry = 0;
	wl->tx_queue_stopped = false;
	wl->घातer_level = WL1251_DEFAULT_POWER_LEVEL;
	wl->rssi_thold = 0;
	wl->channel = WL1251_DEFAULT_CHANNEL;
	wl->monitor_present = false;
	wl->joined = false;

	wl1251_debugfs_reset(wl);

	mutex_unlock(&wl->mutex);
पूर्ण

अटल पूर्णांक wl1251_op_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wl1251 *wl = hw->priv;
	पूर्णांक ret = 0;

	vअगर->driver_flags |= IEEE80211_VIF_BEACON_FILTER |
			     IEEE80211_VIF_SUPPORTS_UAPSD |
			     IEEE80211_VIF_SUPPORTS_CQM_RSSI;

	wl1251_debug(DEBUG_MAC80211, "mac80211 add interface type %d mac %pM",
		     vअगर->type, vअगर->addr);

	mutex_lock(&wl->mutex);
	अगर (wl->vअगर) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	wl->vअगर = vअगर;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		wl->bss_type = BSS_TYPE_STA_BSS;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		wl->bss_type = BSS_TYPE_IBSS;
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (!ether_addr_equal_unaligned(wl->mac_addr, vअगर->addr)) अणु
		स_नकल(wl->mac_addr, vअगर->addr, ETH_ALEN);
		SET_IEEE80211_PERM_ADDR(wl->hw, wl->mac_addr);
		ret = wl1251_acx_station_id(wl);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

out:
	mutex_unlock(&wl->mutex);
	वापस ret;
पूर्ण

अटल व्योम wl1251_op_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
					 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wl1251 *wl = hw->priv;

	mutex_lock(&wl->mutex);
	wl1251_debug(DEBUG_MAC80211, "mac80211 remove interface");
	wl->vअगर = शून्य;
	eth_zero_addr(wl->bssid);
	mutex_unlock(&wl->mutex);
पूर्ण

अटल पूर्णांक wl1251_build_null_data(काष्ठा wl1251 *wl)
अणु
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक size;
	व्योम *ptr;
	पूर्णांक ret = -ENOMEM;

	अगर (wl->bss_type == BSS_TYPE_IBSS) अणु
		size = माप(काष्ठा wl12xx_null_data_ढाँचा);
		ptr = शून्य;
	पूर्ण अन्यथा अणु
		skb = ieee80211_nullfunc_get(wl->hw, wl->vअगर, false);
		अगर (!skb)
			जाओ out;
		size = skb->len;
		ptr = skb->data;
	पूर्ण

	ret = wl1251_cmd_ढाँचा_set(wl, CMD_शून्य_DATA, ptr, size);

out:
	dev_kमुक्त_skb(skb);
	अगर (ret)
		wl1251_warning("cmd build null data failed: %d", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक wl1251_build_qos_null_data(काष्ठा wl1251 *wl)
अणु
	काष्ठा ieee80211_qos_hdr ढाँचा;

	स_रखो(&ढाँचा, 0, माप(ढाँचा));

	स_नकल(ढाँचा.addr1, wl->bssid, ETH_ALEN);
	स_नकल(ढाँचा.addr2, wl->mac_addr, ETH_ALEN);
	स_नकल(ढाँचा.addr3, wl->bssid, ETH_ALEN);

	ढाँचा.frame_control = cpu_to_le16(IEEE80211_FTYPE_DATA |
					     IEEE80211_STYPE_QOS_शून्यFUNC |
					     IEEE80211_FCTL_TODS);

	/* FIXME: not sure what priority to use here */
	ढाँचा.qos_ctrl = cpu_to_le16(0);

	वापस wl1251_cmd_ढाँचा_set(wl, CMD_QOS_शून्य_DATA, &ढाँचा,
				       माप(ढाँचा));
पूर्ण

अटल bool wl1251_can_करो_pm(काष्ठा ieee80211_conf *conf, काष्ठा wl1251 *wl)
अणु
	वापस (conf->flags & IEEE80211_CONF_PS) && !wl->monitor_present;
पूर्ण

अटल पूर्णांक wl1251_op_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा wl1251 *wl = hw->priv;
	काष्ठा ieee80211_conf *conf = &hw->conf;
	पूर्णांक channel, ret = 0;

	channel = ieee80211_frequency_to_channel(
			conf->chandef.chan->center_freq);

	wl1251_debug(DEBUG_MAC80211,
		     "mac80211 config ch %d monitor %s psm %s power %d",
		     channel,
		     conf->flags & IEEE80211_CONF_MONITOR ? "on" : "off",
		     conf->flags & IEEE80211_CONF_PS ? "on" : "off",
		     conf->घातer_level);

	mutex_lock(&wl->mutex);

	ret = wl1251_ps_elp_wakeup(wl);
	अगर (ret < 0)
		जाओ out;

	अगर (changed & IEEE80211_CONF_CHANGE_MONITOR) अणु
		u32 mode;

		अगर (conf->flags & IEEE80211_CONF_MONITOR) अणु
			wl->monitor_present = true;
			mode = DF_SNIFF_MODE_ENABLE | DF_ENCRYPTION_DISABLE;
		पूर्ण अन्यथा अणु
			wl->monitor_present = false;
			mode = 0;
		पूर्ण

		ret = wl1251_acx_feature_cfg(wl, mode);
		अगर (ret < 0)
			जाओ out_sleep;
	पूर्ण

	अगर (channel != wl->channel) अणु
		wl->channel = channel;

		/*
		 * Use ENABLE_RX command क्रम channel चयनing when no
		 * पूर्णांकerface is present (monitor mode only).
		 * This leaves the tx path disabled in firmware, whereas
		 * the usual JOIN command seems to transmit some frames
		 * at firmware level.
		 */
		अगर (wl->vअगर == शून्य) अणु
			wl->joined = false;
			ret = wl1251_cmd_data_path_rx(wl, wl->channel, 1);
		पूर्ण अन्यथा अणु
			ret = wl1251_join(wl, wl->bss_type, wl->channel,
					  wl->beacon_पूर्णांक, wl->dtim_period);
		पूर्ण
		अगर (ret < 0)
			जाओ out_sleep;
	पूर्ण

	अगर (wl1251_can_करो_pm(conf, wl) && !wl->psm_requested) अणु
		wl1251_debug(DEBUG_PSM, "psm enabled");

		wl->psm_requested = true;

		wl->dtim_period = conf->ps_dtim_period;

		ret = wl1251_acx_wr_tbtt_and_dtim(wl, wl->beacon_पूर्णांक,
						  wl->dtim_period);

		/*
		 * mac80211 enables PSM only अगर we're alपढ़ोy associated.
		 */
		ret = wl1251_ps_set_mode(wl, STATION_POWER_SAVE_MODE);
		अगर (ret < 0)
			जाओ out_sleep;
	पूर्ण अन्यथा अगर (!wl1251_can_करो_pm(conf, wl) && wl->psm_requested) अणु
		wl1251_debug(DEBUG_PSM, "psm disabled");

		wl->psm_requested = false;

		अगर (wl->station_mode != STATION_ACTIVE_MODE) अणु
			ret = wl1251_ps_set_mode(wl, STATION_ACTIVE_MODE);
			अगर (ret < 0)
				जाओ out_sleep;
		पूर्ण
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_IDLE && !wl->scanning) अणु
		अगर (conf->flags & IEEE80211_CONF_IDLE) अणु
			ret = wl1251_ps_set_mode(wl, STATION_IDLE);
			अगर (ret < 0)
				जाओ out_sleep;
		पूर्ण अन्यथा अणु
			ret = wl1251_ps_set_mode(wl, STATION_ACTIVE_MODE);
			अगर (ret < 0)
				जाओ out_sleep;
			ret = wl1251_join(wl, wl->bss_type, wl->channel,
					  wl->beacon_पूर्णांक, wl->dtim_period);
			अगर (ret < 0)
				जाओ out_sleep;
		पूर्ण
	पूर्ण

	अगर (conf->घातer_level != wl->घातer_level) अणु
		ret = wl1251_acx_tx_घातer(wl, conf->घातer_level);
		अगर (ret < 0)
			जाओ out_sleep;

		wl->घातer_level = conf->घातer_level;
	पूर्ण

out_sleep:
	wl1251_ps_elp_sleep(wl);

out:
	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

काष्ठा wl1251_filter_params अणु
	bool enabled;
	पूर्णांक mc_list_length;
	u8 mc_list[ACX_MC_ADDRESS_GROUP_MAX][ETH_ALEN];
पूर्ण;

अटल u64 wl1251_op_prepare_multicast(काष्ठा ieee80211_hw *hw,
				       काष्ठा netdev_hw_addr_list *mc_list)
अणु
	काष्ठा wl1251_filter_params *fp;
	काष्ठा netdev_hw_addr *ha;
	काष्ठा wl1251 *wl = hw->priv;

	अगर (unlikely(wl->state == WL1251_STATE_OFF))
		वापस 0;

	fp = kzalloc(माप(*fp), GFP_ATOMIC);
	अगर (!fp) अणु
		wl1251_error("Out of memory setting filters.");
		वापस 0;
	पूर्ण

	/* update multicast filtering parameters */
	fp->mc_list_length = 0;
	अगर (netdev_hw_addr_list_count(mc_list) > ACX_MC_ADDRESS_GROUP_MAX) अणु
		fp->enabled = false;
	पूर्ण अन्यथा अणु
		fp->enabled = true;
		netdev_hw_addr_list_क्रम_each(ha, mc_list) अणु
			स_नकल(fp->mc_list[fp->mc_list_length],
					ha->addr, ETH_ALEN);
			fp->mc_list_length++;
		पूर्ण
	पूर्ण

	वापस (u64)(अचिन्हित दीर्घ)fp;
पूर्ण

#घोषणा WL1251_SUPPORTED_FILTERS (FIF_ALLMULTI | \
				  FIF_FCSFAIL | \
				  FIF_BCN_PRBRESP_PROMISC | \
				  FIF_CONTROL | \
				  FIF_OTHER_BSS | \
				  FIF_PROBE_REQ)

अटल व्योम wl1251_op_configure_filter(काष्ठा ieee80211_hw *hw,
				       अचिन्हित पूर्णांक changed,
				       अचिन्हित पूर्णांक *total, u64 multicast)
अणु
	काष्ठा wl1251_filter_params *fp = (व्योम *)(अचिन्हित दीर्घ)multicast;
	काष्ठा wl1251 *wl = hw->priv;
	पूर्णांक ret;

	wl1251_debug(DEBUG_MAC80211, "mac80211 configure filter");

	*total &= WL1251_SUPPORTED_FILTERS;
	changed &= WL1251_SUPPORTED_FILTERS;

	अगर (changed == 0) अणु
		/* no filters which we support changed */
		kमुक्त(fp);
		वापस;
	पूर्ण

	mutex_lock(&wl->mutex);

	wl->rx_config = WL1251_DEFAULT_RX_CONFIG;
	wl->rx_filter = WL1251_DEFAULT_RX_FILTER;

	अगर (*total & FIF_ALLMULTI)
		/*
		 * CFG_MC_FILTER_EN in rx_config needs to be 0 to receive
		 * all multicast frames
		 */
		wl->rx_config &= ~CFG_MC_FILTER_EN;
	अगर (*total & FIF_FCSFAIL)
		wl->rx_filter |= CFG_RX_FCS_ERROR;
	अगर (*total & FIF_BCN_PRBRESP_PROMISC) अणु
		wl->rx_config &= ~CFG_BSSID_FILTER_EN;
		wl->rx_config &= ~CFG_SSID_FILTER_EN;
	पूर्ण
	अगर (*total & FIF_CONTROL)
		wl->rx_filter |= CFG_RX_CTL_EN;
	अगर (*total & FIF_OTHER_BSS || is_zero_ether_addr(wl->bssid))
		wl->rx_config &= ~CFG_BSSID_FILTER_EN;
	अगर (*total & FIF_PROBE_REQ)
		wl->rx_filter |= CFG_RX_PREQ_EN;

	अगर (wl->state == WL1251_STATE_OFF)
		जाओ out;

	ret = wl1251_ps_elp_wakeup(wl);
	अगर (ret < 0)
		जाओ out;

	अगर (*total & FIF_ALLMULTI)
		ret = wl1251_acx_group_address_tbl(wl, false, शून्य, 0);
	अन्यथा अगर (fp)
		ret = wl1251_acx_group_address_tbl(wl, fp->enabled,
						   fp->mc_list,
						   fp->mc_list_length);
	अगर (ret < 0)
		जाओ out;

	/* send filters to firmware */
	wl1251_acx_rx_config(wl, wl->rx_config, wl->rx_filter);

	wl1251_ps_elp_sleep(wl);

out:
	mutex_unlock(&wl->mutex);
	kमुक्त(fp);
पूर्ण

/* HW encryption */
अटल पूर्णांक wl1251_set_key_type(काष्ठा wl1251 *wl,
			       काष्ठा wl1251_cmd_set_keys *key,
			       क्रमागत set_key_cmd cmd,
			       काष्ठा ieee80211_key_conf *mac80211_key,
			       स्थिर u8 *addr)
अणु
	चयन (mac80211_key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		अगर (is_broadcast_ether_addr(addr))
			key->key_type = KEY_WEP_DEFAULT;
		अन्यथा
			key->key_type = KEY_WEP_ADDR;

		mac80211_key->hw_key_idx = mac80211_key->keyidx;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		अगर (is_broadcast_ether_addr(addr))
			key->key_type = KEY_TKIP_MIC_GROUP;
		अन्यथा
			key->key_type = KEY_TKIP_MIC_PAIRWISE;

		mac80211_key->hw_key_idx = mac80211_key->keyidx;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		अगर (is_broadcast_ether_addr(addr))
			key->key_type = KEY_AES_GROUP;
		अन्यथा
			key->key_type = KEY_AES_PAIRWISE;
		mac80211_key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
		अवरोध;
	शेष:
		wl1251_error("Unknown key cipher 0x%x", mac80211_key->cipher);
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wl1251_op_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_sta *sta,
			     काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा wl1251 *wl = hw->priv;
	काष्ठा wl1251_cmd_set_keys *wl_cmd;
	स्थिर u8 *addr;
	पूर्णांक ret;

	अटल स्थिर u8 bcast_addr[ETH_ALEN] =
		अणु 0xff, 0xff, 0xff, 0xff, 0xff, 0xff पूर्ण;

	wl1251_debug(DEBUG_MAC80211, "mac80211 set key");

	wl_cmd = kzalloc(माप(*wl_cmd), GFP_KERNEL);
	अगर (!wl_cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	addr = sta ? sta->addr : bcast_addr;

	wl1251_debug(DEBUG_CRYPT, "CMD: 0x%x", cmd);
	wl1251_dump(DEBUG_CRYPT, "ADDR: ", addr, ETH_ALEN);
	wl1251_debug(DEBUG_CRYPT, "Key: algo:0x%x, id:%d, len:%d flags 0x%x",
		     key->cipher, key->keyidx, key->keylen, key->flags);
	wl1251_dump(DEBUG_CRYPT, "KEY: ", key->key, key->keylen);

	अगर (is_zero_ether_addr(addr)) अणु
		/* We करोnt support TX only encryption */
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	mutex_lock(&wl->mutex);

	चयन (cmd) अणु
	हाल SET_KEY:
		अगर (wl->monitor_present) अणु
			ret = -EOPNOTSUPP;
			जाओ out_unlock;
		पूर्ण
		wl_cmd->key_action = KEY_ADD_OR_REPLACE;
		अवरोध;
	हाल DISABLE_KEY:
		wl_cmd->key_action = KEY_REMOVE;
		अवरोध;
	शेष:
		wl1251_error("Unsupported key cmd 0x%x", cmd);
		अवरोध;
	पूर्ण

	ret = wl1251_ps_elp_wakeup(wl);
	अगर (ret < 0)
		जाओ out_unlock;

	ret = wl1251_set_key_type(wl, wl_cmd, cmd, key, addr);
	अगर (ret < 0) अणु
		wl1251_error("Set KEY type failed");
		जाओ out_sleep;
	पूर्ण

	अगर (wl_cmd->key_type != KEY_WEP_DEFAULT)
		स_नकल(wl_cmd->addr, addr, ETH_ALEN);

	अगर ((wl_cmd->key_type == KEY_TKIP_MIC_GROUP) ||
	    (wl_cmd->key_type == KEY_TKIP_MIC_PAIRWISE)) अणु
		/*
		 * We get the key in the following क्रमm:
		 * TKIP (16 bytes) - TX MIC (8 bytes) - RX MIC (8 bytes)
		 * but the target is expecting:
		 * TKIP - RX MIC - TX MIC
		 */
		स_नकल(wl_cmd->key, key->key, 16);
		स_नकल(wl_cmd->key + 16, key->key + 24, 8);
		स_नकल(wl_cmd->key + 24, key->key + 16, 8);

	पूर्ण अन्यथा अणु
		स_नकल(wl_cmd->key, key->key, key->keylen);
	पूर्ण
	wl_cmd->key_size = key->keylen;

	wl_cmd->id = key->keyidx;
	wl_cmd->ssid_profile = 0;

	wl1251_dump(DEBUG_CRYPT, "TARGET KEY: ", wl_cmd, माप(*wl_cmd));

	ret = wl1251_cmd_send(wl, CMD_SET_KEYS, wl_cmd, माप(*wl_cmd));
	अगर (ret < 0) अणु
		wl1251_warning("could not set keys");
		जाओ out_sleep;
	पूर्ण

out_sleep:
	wl1251_ps_elp_sleep(wl);

out_unlock:
	mutex_unlock(&wl->mutex);

out:
	kमुक्त(wl_cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक wl1251_op_hw_scan(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_scan_request *hw_req)
अणु
	काष्ठा cfg80211_scan_request *req = &hw_req->req;
	काष्ठा wl1251 *wl = hw->priv;
	काष्ठा sk_buff *skb;
	माप_प्रकार ssid_len = 0;
	u8 *ssid = शून्य;
	पूर्णांक ret;

	wl1251_debug(DEBUG_MAC80211, "mac80211 hw scan");

	अगर (req->n_ssids) अणु
		ssid = req->ssids[0].ssid;
		ssid_len = req->ssids[0].ssid_len;
	पूर्ण

	mutex_lock(&wl->mutex);

	अगर (wl->scanning) अणु
		wl1251_debug(DEBUG_SCAN, "scan already in progress");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = wl1251_ps_elp_wakeup(wl);
	अगर (ret < 0)
		जाओ out;

	अगर (hw->conf.flags & IEEE80211_CONF_IDLE) अणु
		ret = wl1251_ps_set_mode(wl, STATION_ACTIVE_MODE);
		अगर (ret < 0)
			जाओ out_sleep;
		ret = wl1251_join(wl, wl->bss_type, wl->channel,
				  wl->beacon_पूर्णांक, wl->dtim_period);
		अगर (ret < 0)
			जाओ out_sleep;
	पूर्ण

	skb = ieee80211_probereq_get(wl->hw, wl->vअगर->addr, ssid, ssid_len,
				     req->ie_len);
	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ out_idle;
	पूर्ण
	अगर (req->ie_len)
		skb_put_data(skb, req->ie, req->ie_len);

	ret = wl1251_cmd_ढाँचा_set(wl, CMD_PROBE_REQ, skb->data,
				      skb->len);
	dev_kमुक्त_skb(skb);
	अगर (ret < 0)
		जाओ out_idle;

	ret = wl1251_cmd_trigger_scan_to(wl, 0);
	अगर (ret < 0)
		जाओ out_idle;

	wl->scanning = true;

	ret = wl1251_cmd_scan(wl, ssid, ssid_len, req->channels,
			      req->n_channels, WL1251_SCAN_NUM_PROBES);
	अगर (ret < 0) अणु
		wl1251_debug(DEBUG_SCAN, "scan failed %d", ret);
		wl->scanning = false;
		जाओ out_idle;
	पूर्ण
	जाओ out_sleep;

out_idle:
	अगर (hw->conf.flags & IEEE80211_CONF_IDLE)
		ret = wl1251_ps_set_mode(wl, STATION_IDLE);
out_sleep:
	wl1251_ps_elp_sleep(wl);

out:
	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक wl1251_op_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 value)
अणु
	काष्ठा wl1251 *wl = hw->priv;
	पूर्णांक ret;

	mutex_lock(&wl->mutex);

	ret = wl1251_ps_elp_wakeup(wl);
	अगर (ret < 0)
		जाओ out;

	ret = wl1251_acx_rts_threshold(wl, (u16) value);
	अगर (ret < 0)
		wl1251_warning("wl1251_op_set_rts_threshold failed: %d", ret);

	wl1251_ps_elp_sleep(wl);

out:
	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

अटल व्योम wl1251_op_bss_info_changed(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_bss_conf *bss_conf,
				       u32 changed)
अणु
	काष्ठा wl1251 *wl = hw->priv;
	काष्ठा sk_buff *beacon, *skb;
	bool enable;
	पूर्णांक ret;

	wl1251_debug(DEBUG_MAC80211, "mac80211 bss info changed");

	mutex_lock(&wl->mutex);

	ret = wl1251_ps_elp_wakeup(wl);
	अगर (ret < 0)
		जाओ out;

	अगर (changed & BSS_CHANGED_CQM) अणु
		ret = wl1251_acx_low_rssi(wl, bss_conf->cqm_rssi_thold,
					  WL1251_DEFAULT_LOW_RSSI_WEIGHT,
					  WL1251_DEFAULT_LOW_RSSI_DEPTH,
					  WL1251_ACX_LOW_RSSI_TYPE_EDGE);
		अगर (ret < 0)
			जाओ out;
		wl->rssi_thold = bss_conf->cqm_rssi_thold;
	पूर्ण

	अगर ((changed & BSS_CHANGED_BSSID) &&
	    स_भेद(wl->bssid, bss_conf->bssid, ETH_ALEN)) अणु
		स_नकल(wl->bssid, bss_conf->bssid, ETH_ALEN);

		अगर (!is_zero_ether_addr(wl->bssid)) अणु
			ret = wl1251_build_null_data(wl);
			अगर (ret < 0)
				जाओ out_sleep;

			ret = wl1251_build_qos_null_data(wl);
			अगर (ret < 0)
				जाओ out_sleep;

			ret = wl1251_join(wl, wl->bss_type, wl->channel,
					  wl->beacon_पूर्णांक, wl->dtim_period);
			अगर (ret < 0)
				जाओ out_sleep;
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_ASSOC) अणु
		अगर (bss_conf->assoc) अणु
			wl->beacon_पूर्णांक = bss_conf->beacon_पूर्णांक;

			skb = ieee80211_pspoll_get(wl->hw, wl->vअगर);
			अगर (!skb)
				जाओ out_sleep;

			ret = wl1251_cmd_ढाँचा_set(wl, CMD_PS_POLL,
						      skb->data,
						      skb->len);
			dev_kमुक्त_skb(skb);
			अगर (ret < 0)
				जाओ out_sleep;

			ret = wl1251_acx_aid(wl, bss_conf->aid);
			अगर (ret < 0)
				जाओ out_sleep;
		पूर्ण अन्यथा अणु
			/* use शेषs when not associated */
			wl->beacon_पूर्णांक = WL1251_DEFAULT_BEACON_INT;
			wl->dtim_period = WL1251_DEFAULT_DTIM_PERIOD;
		पूर्ण
	पूर्ण
	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		अगर (bss_conf->use_लघु_slot)
			ret = wl1251_acx_slot(wl, SLOT_TIME_SHORT);
		अन्यथा
			ret = wl1251_acx_slot(wl, SLOT_TIME_LONG);
		अगर (ret < 0) अणु
			wl1251_warning("Set slot time failed %d", ret);
			जाओ out_sleep;
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_PREAMBLE) अणु
		अगर (bss_conf->use_लघु_preamble)
			wl1251_acx_set_preamble(wl, ACX_PREAMBLE_SHORT);
		अन्यथा
			wl1251_acx_set_preamble(wl, ACX_PREAMBLE_LONG);
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_CTS_PROT) अणु
		अगर (bss_conf->use_cts_prot)
			ret = wl1251_acx_cts_protect(wl, CTSPROTECT_ENABLE);
		अन्यथा
			ret = wl1251_acx_cts_protect(wl, CTSPROTECT_DISABLE);
		अगर (ret < 0) अणु
			wl1251_warning("Set ctsprotect failed %d", ret);
			जाओ out_sleep;
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_ARP_FILTER) अणु
		__be32 addr = bss_conf->arp_addr_list[0];
		WARN_ON(wl->bss_type != BSS_TYPE_STA_BSS);

		enable = bss_conf->arp_addr_cnt == 1 && bss_conf->assoc;
		ret = wl1251_acx_arp_ip_filter(wl, enable, addr);
		अगर (ret < 0)
			जाओ out_sleep;
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON) अणु
		beacon = ieee80211_beacon_get(hw, vअगर);
		अगर (!beacon)
			जाओ out_sleep;

		ret = wl1251_cmd_ढाँचा_set(wl, CMD_BEACON, beacon->data,
					      beacon->len);

		अगर (ret < 0) अणु
			dev_kमुक्त_skb(beacon);
			जाओ out_sleep;
		पूर्ण

		ret = wl1251_cmd_ढाँचा_set(wl, CMD_PROBE_RESP, beacon->data,
					      beacon->len);

		dev_kमुक्त_skb(beacon);

		अगर (ret < 0)
			जाओ out_sleep;

		ret = wl1251_join(wl, wl->bss_type, wl->channel,
				  wl->beacon_पूर्णांक, wl->dtim_period);

		अगर (ret < 0)
			जाओ out_sleep;
	पूर्ण

out_sleep:
	wl1251_ps_elp_sleep(wl);

out:
	mutex_unlock(&wl->mutex);
पूर्ण


/* can't be स्थिर, mac80211 ग_लिखोs to this */
अटल काष्ठा ieee80211_rate wl1251_rates[] = अणु
	अणु .bitrate = 10,
	  .hw_value = 0x1,
	  .hw_value_लघु = 0x1, पूर्ण,
	अणु .bitrate = 20,
	  .hw_value = 0x2,
	  .hw_value_लघु = 0x2,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 55,
	  .hw_value = 0x4,
	  .hw_value_लघु = 0x4,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 110,
	  .hw_value = 0x20,
	  .hw_value_लघु = 0x20,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 60,
	  .hw_value = 0x8,
	  .hw_value_लघु = 0x8, पूर्ण,
	अणु .bitrate = 90,
	  .hw_value = 0x10,
	  .hw_value_लघु = 0x10, पूर्ण,
	अणु .bitrate = 120,
	  .hw_value = 0x40,
	  .hw_value_लघु = 0x40, पूर्ण,
	अणु .bitrate = 180,
	  .hw_value = 0x80,
	  .hw_value_लघु = 0x80, पूर्ण,
	अणु .bitrate = 240,
	  .hw_value = 0x200,
	  .hw_value_लघु = 0x200, पूर्ण,
	अणु .bitrate = 360,
	 .hw_value = 0x400,
	 .hw_value_लघु = 0x400, पूर्ण,
	अणु .bitrate = 480,
	  .hw_value = 0x800,
	  .hw_value_लघु = 0x800, पूर्ण,
	अणु .bitrate = 540,
	  .hw_value = 0x1000,
	  .hw_value_लघु = 0x1000, पूर्ण,
पूर्ण;

/* can't be स्थिर, mac80211 ग_लिखोs to this */
अटल काष्ठा ieee80211_channel wl1251_channels[] = अणु
	अणु .hw_value = 1, .center_freq = 2412पूर्ण,
	अणु .hw_value = 2, .center_freq = 2417पूर्ण,
	अणु .hw_value = 3, .center_freq = 2422पूर्ण,
	अणु .hw_value = 4, .center_freq = 2427पूर्ण,
	अणु .hw_value = 5, .center_freq = 2432पूर्ण,
	अणु .hw_value = 6, .center_freq = 2437पूर्ण,
	अणु .hw_value = 7, .center_freq = 2442पूर्ण,
	अणु .hw_value = 8, .center_freq = 2447पूर्ण,
	अणु .hw_value = 9, .center_freq = 2452पूर्ण,
	अणु .hw_value = 10, .center_freq = 2457पूर्ण,
	अणु .hw_value = 11, .center_freq = 2462पूर्ण,
	अणु .hw_value = 12, .center_freq = 2467पूर्ण,
	अणु .hw_value = 13, .center_freq = 2472पूर्ण,
पूर्ण;

अटल पूर्णांक wl1251_op_conf_tx(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर, u16 queue,
			     स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	क्रमागत wl1251_acx_ps_scheme ps_scheme;
	काष्ठा wl1251 *wl = hw->priv;
	पूर्णांक ret;

	mutex_lock(&wl->mutex);

	wl1251_debug(DEBUG_MAC80211, "mac80211 conf tx %d", queue);

	ret = wl1251_ps_elp_wakeup(wl);
	अगर (ret < 0)
		जाओ out;

	/* mac80211 uses units of 32 usec */
	ret = wl1251_acx_ac_cfg(wl, wl1251_tx_get_queue(queue),
				params->cw_min, params->cw_max,
				params->aअगरs, params->txop * 32);
	अगर (ret < 0)
		जाओ out_sleep;

	अगर (params->uapsd)
		ps_scheme = WL1251_ACX_PS_SCHEME_UPSD_TRIGGER;
	अन्यथा
		ps_scheme = WL1251_ACX_PS_SCHEME_LEGACY;

	ret = wl1251_acx_tid_cfg(wl, wl1251_tx_get_queue(queue),
				 CHANNEL_TYPE_EDCF,
				 wl1251_tx_get_queue(queue), ps_scheme,
				 WL1251_ACX_ACK_POLICY_LEGACY);
	अगर (ret < 0)
		जाओ out_sleep;

out_sleep:
	wl1251_ps_elp_sleep(wl);

out:
	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक wl1251_op_get_survey(काष्ठा ieee80211_hw *hw, पूर्णांक idx,
				काष्ठा survey_info *survey)
अणु
	काष्ठा wl1251 *wl = hw->priv;
	काष्ठा ieee80211_conf *conf = &hw->conf;
 
	अगर (idx != 0)
		वापस -ENOENT;
 
	survey->channel = conf->chandef.chan;
	survey->filled = SURVEY_INFO_NOISE_DBM;
	survey->noise = wl->noise;
 
	वापस 0;
पूर्ण

/* can't be स्थिर, mac80211 ग_लिखोs to this */
अटल काष्ठा ieee80211_supported_band wl1251_band_2ghz = अणु
	.channels = wl1251_channels,
	.n_channels = ARRAY_SIZE(wl1251_channels),
	.bitrates = wl1251_rates,
	.n_bitrates = ARRAY_SIZE(wl1251_rates),
पूर्ण;

अटल स्थिर काष्ठा ieee80211_ops wl1251_ops = अणु
	.start = wl1251_op_start,
	.stop = wl1251_op_stop,
	.add_पूर्णांकerface = wl1251_op_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface = wl1251_op_हटाओ_पूर्णांकerface,
	.config = wl1251_op_config,
	.prepare_multicast = wl1251_op_prepare_multicast,
	.configure_filter = wl1251_op_configure_filter,
	.tx = wl1251_op_tx,
	.set_key = wl1251_op_set_key,
	.hw_scan = wl1251_op_hw_scan,
	.bss_info_changed = wl1251_op_bss_info_changed,
	.set_rts_threshold = wl1251_op_set_rts_threshold,
	.conf_tx = wl1251_op_conf_tx,
	.get_survey = wl1251_op_get_survey,
पूर्ण;

अटल पूर्णांक wl1251_पढ़ो_eeprom_byte(काष्ठा wl1251 *wl, off_t offset, u8 *data)
अणु
	अचिन्हित दीर्घ समयout;

	wl1251_reg_ग_लिखो32(wl, EE_ADDR, offset);
	wl1251_reg_ग_लिखो32(wl, EE_CTL, EE_CTL_READ);

	/* EE_CTL_READ clears when data is पढ़ोy */
	समयout = jअगरfies + msecs_to_jअगरfies(100);
	जबतक (1) अणु
		अगर (!(wl1251_reg_पढ़ो32(wl, EE_CTL) & EE_CTL_READ))
			अवरोध;

		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIMEDOUT;

		msleep(1);
	पूर्ण

	*data = wl1251_reg_पढ़ो32(wl, EE_DATA);
	वापस 0;
पूर्ण

अटल पूर्णांक wl1251_पढ़ो_eeprom(काष्ठा wl1251 *wl, off_t offset,
			      u8 *data, माप_प्रकार len)
अणु
	माप_प्रकार i;
	पूर्णांक ret;

	wl1251_reg_ग_लिखो32(wl, EE_START, 0);

	क्रम (i = 0; i < len; i++) अणु
		ret = wl1251_पढ़ो_eeprom_byte(wl, offset + i, &data[i]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wl1251_पढ़ो_eeprom_mac(काष्ठा wl1251 *wl)
अणु
	u8 mac[ETH_ALEN];
	पूर्णांक i, ret;

	wl1251_set_partition(wl, 0, 0, REGISTERS_BASE, REGISTERS_DOWN_SIZE);

	ret = wl1251_पढ़ो_eeprom(wl, 0x1c, mac, माप(mac));
	अगर (ret < 0) अणु
		wl1251_warning("failed to read MAC address from EEPROM");
		वापस ret;
	पूर्ण

	/* MAC is stored in reverse order */
	क्रम (i = 0; i < ETH_ALEN; i++)
		wl->mac_addr[i] = mac[ETH_ALEN - i - 1];

	वापस 0;
पूर्ण

#घोषणा NVS_OFF_MAC_LEN 0x19
#घोषणा NVS_OFF_MAC_ADDR_LO 0x1a
#घोषणा NVS_OFF_MAC_ADDR_HI 0x1b
#घोषणा NVS_OFF_MAC_DATA 0x1c

अटल पूर्णांक wl1251_check_nvs_mac(काष्ठा wl1251 *wl)
अणु
	अगर (wl->nvs_len < 0x24)
		वापस -ENODATA;

	/* length is 2 and data address is 0x546c (ANDed with 0xfffe) */
	अगर (wl->nvs[NVS_OFF_MAC_LEN] != 2 ||
	    wl->nvs[NVS_OFF_MAC_ADDR_LO] != 0x6d ||
	    wl->nvs[NVS_OFF_MAC_ADDR_HI] != 0x54)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक wl1251_पढ़ो_nvs_mac(काष्ठा wl1251 *wl)
अणु
	u8 mac[ETH_ALEN];
	पूर्णांक i, ret;

	ret = wl1251_check_nvs_mac(wl);
	अगर (ret)
		वापस ret;

	/* MAC is stored in reverse order */
	क्रम (i = 0; i < ETH_ALEN; i++)
		mac[i] = wl->nvs[NVS_OFF_MAC_DATA + ETH_ALEN - i - 1];

	/* 00:00:20:07:03:09 is in example file wl1251-nvs.bin, so invalid */
	अगर (ether_addr_equal_unaligned(mac, "\x00\x00\x20\x07\x03\x09"))
		वापस -EINVAL;

	स_नकल(wl->mac_addr, mac, ETH_ALEN);
	वापस 0;
पूर्ण

अटल पूर्णांक wl1251_ग_लिखो_nvs_mac(काष्ठा wl1251 *wl)
अणु
	पूर्णांक i, ret;

	ret = wl1251_check_nvs_mac(wl);
	अगर (ret)
		वापस ret;

	/* MAC is stored in reverse order */
	क्रम (i = 0; i < ETH_ALEN; i++)
		wl->nvs[NVS_OFF_MAC_DATA + i] = wl->mac_addr[ETH_ALEN - i - 1];

	वापस 0;
पूर्ण

अटल पूर्णांक wl1251_रेजिस्टर_hw(काष्ठा wl1251 *wl)
अणु
	पूर्णांक ret;

	अगर (wl->mac80211_रेजिस्टरed)
		वापस 0;

	SET_IEEE80211_PERM_ADDR(wl->hw, wl->mac_addr);

	ret = ieee80211_रेजिस्टर_hw(wl->hw);
	अगर (ret < 0) अणु
		wl1251_error("unable to register mac80211 hw: %d", ret);
		वापस ret;
	पूर्ण

	wl->mac80211_रेजिस्टरed = true;

	wl1251_notice("loaded");

	वापस 0;
पूर्ण

पूर्णांक wl1251_init_ieee80211(काष्ठा wl1251 *wl)
अणु
	पूर्णांक ret;

	/* The tx descriptor buffer and the TKIP space */
	wl->hw->extra_tx_headroom = माप(काष्ठा tx_द्विगुन_buffer_desc)
		+ WL1251_TKIP_IV_SPACE;

	/* unit us */
	/* FIXME: find a proper value */

	ieee80211_hw_set(wl->hw, SIGNAL_DBM);
	ieee80211_hw_set(wl->hw, SUPPORTS_PS);

	wl->hw->wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
					 BIT(NL80211_IFTYPE_ADHOC);
	wl->hw->wiphy->max_scan_ssids = 1;
	wl->hw->wiphy->bands[NL80211_BAND_2GHZ] = &wl1251_band_2ghz;

	wl->hw->queues = 4;

	अगर (wl->nvs == शून्य && !wl->use_eeprom) अणु
		ret = wl1251_fetch_nvs(wl);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	अगर (wl->use_eeprom)
		ret = wl1251_पढ़ो_eeprom_mac(wl);
	अन्यथा
		ret = wl1251_पढ़ो_nvs_mac(wl);

	अगर (ret == 0 && !is_valid_ether_addr(wl->mac_addr))
		ret = -EINVAL;

	अगर (ret < 0) अणु
		/*
		 * In हाल our MAC address is not correctly set,
		 * we use a अक्रमom but Nokia MAC.
		 */
		अटल स्थिर u8 nokia_oui[3] = अणु0x00, 0x1f, 0xdfपूर्ण;
		स_नकल(wl->mac_addr, nokia_oui, 3);
		get_अक्रमom_bytes(wl->mac_addr + 3, 3);
		अगर (!wl->use_eeprom)
			wl1251_ग_लिखो_nvs_mac(wl);
		wl1251_warning("MAC address in eeprom or nvs data is not valid");
		wl1251_warning("Setting random MAC address: %pM", wl->mac_addr);
	पूर्ण

	ret = wl1251_रेजिस्टर_hw(wl);
	अगर (ret)
		जाओ out;

	wl1251_debugfs_init(wl);
	wl1251_notice("initialized");

	ret = 0;

out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wl1251_init_ieee80211);

काष्ठा ieee80211_hw *wl1251_alloc_hw(व्योम)
अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा wl1251 *wl;
	पूर्णांक i;

	hw = ieee80211_alloc_hw(माप(*wl), &wl1251_ops);
	अगर (!hw) अणु
		wl1251_error("could not alloc ieee80211_hw");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	wl = hw->priv;
	स_रखो(wl, 0, माप(*wl));

	wl->hw = hw;

	wl->data_in_count = 0;

	skb_queue_head_init(&wl->tx_queue);

	INIT_DELAYED_WORK(&wl->elp_work, wl1251_elp_work);
	wl->channel = WL1251_DEFAULT_CHANNEL;
	wl->monitor_present = false;
	wl->joined = false;
	wl->scanning = false;
	wl->bss_type = MAX_BSS_TYPE;
	wl->शेष_key = 0;
	wl->listen_पूर्णांक = 1;
	wl->rx_counter = 0;
	wl->rx_handled = 0;
	wl->rx_current_buffer = 0;
	wl->rx_last_id = 0;
	wl->rx_config = WL1251_DEFAULT_RX_CONFIG;
	wl->rx_filter = WL1251_DEFAULT_RX_FILTER;
	wl->elp = false;
	wl->station_mode = STATION_ACTIVE_MODE;
	wl->psm_requested = false;
	wl->psm_entry_retry = 0;
	wl->tx_queue_stopped = false;
	wl->घातer_level = WL1251_DEFAULT_POWER_LEVEL;
	wl->rssi_thold = 0;
	wl->beacon_पूर्णांक = WL1251_DEFAULT_BEACON_INT;
	wl->dtim_period = WL1251_DEFAULT_DTIM_PERIOD;
	wl->vअगर = शून्य;

	क्रम (i = 0; i < FW_TX_CMPLT_BLOCK_SIZE; i++)
		wl->tx_frames[i] = शून्य;

	wl->next_tx_complete = 0;

	INIT_WORK(&wl->irq_work, wl1251_irq_work);
	INIT_WORK(&wl->tx_work, wl1251_tx_work);

	wl->state = WL1251_STATE_OFF;
	mutex_init(&wl->mutex);
	spin_lock_init(&wl->wl_lock);

	wl->tx_mgmt_frm_rate = DEFAULT_HW_GEN_TX_RATE;
	wl->tx_mgmt_frm_mod = DEFAULT_HW_GEN_MODULATION_TYPE;

	wl->rx_descriptor = kदो_स्मृति(माप(*wl->rx_descriptor), GFP_KERNEL);
	अगर (!wl->rx_descriptor) अणु
		wl1251_error("could not allocate memory for rx descriptor");
		ieee80211_मुक्त_hw(hw);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस hw;
पूर्ण
EXPORT_SYMBOL_GPL(wl1251_alloc_hw);

पूर्णांक wl1251_मुक्त_hw(काष्ठा wl1251 *wl)
अणु
	ieee80211_unरेजिस्टर_hw(wl->hw);

	wl1251_debugfs_निकास(wl);

	kमुक्त(wl->target_mem_map);
	kमुक्त(wl->data_path);
	vमुक्त(wl->fw);
	wl->fw = शून्य;
	kमुक्त(wl->nvs);
	wl->nvs = शून्य;

	kमुक्त(wl->rx_descriptor);
	wl->rx_descriptor = शून्य;

	ieee80211_मुक्त_hw(wl->hw);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wl1251_मुक्त_hw);

MODULE_DESCRIPTION("TI wl1251 Wireless LAN Driver Core");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kalle Valo <kvalo@adurom.com>");
MODULE_FIRMWARE(WL1251_FW_NAME);
MODULE_FIRMWARE(WL1251_NVS_NAME);
