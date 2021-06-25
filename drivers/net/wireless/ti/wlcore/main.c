<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wlcore
 *
 * Copyright (C) 2008-2010 Nokia Corporation
 * Copyright (C) 2011-2013 Texas Instruments Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_wakeirq.h>

#समावेश "wlcore.h"
#समावेश "debug.h"
#समावेश "wl12xx_80211.h"
#समावेश "io.h"
#समावेश "tx.h"
#समावेश "ps.h"
#समावेश "init.h"
#समावेश "debugfs.h"
#समावेश "testmode.h"
#समावेश "vendor_cmd.h"
#समावेश "scan.h"
#समावेश "hw_ops.h"
#समावेश "sysfs.h"

#घोषणा WL1271_BOOT_RETRIES 3
#घोषणा WL1271_WAKEUP_TIMEOUT 500

अटल अक्षर *fwlog_param;
अटल पूर्णांक fwlog_mem_blocks = -1;
अटल पूर्णांक bug_on_recovery = -1;
अटल पूर्णांक no_recovery     = -1;

अटल व्योम __wl1271_op_हटाओ_पूर्णांकerface(काष्ठा wl1271 *wl,
					 काष्ठा ieee80211_vअगर *vअगर,
					 bool reset_tx_queues);
अटल व्योम wlcore_op_stop_locked(काष्ठा wl1271 *wl);
अटल व्योम wl1271_मुक्त_ap_keys(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);

अटल पूर्णांक wl12xx_set_authorized(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	पूर्णांक ret;

	अगर (WARN_ON(wlvअगर->bss_type != BSS_TYPE_STA_BSS))
		वापस -EINVAL;

	अगर (!test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvअगर->flags))
		वापस 0;

	अगर (test_and_set_bit(WLVIF_FLAG_STA_STATE_SENT, &wlvअगर->flags))
		वापस 0;

	ret = wl12xx_cmd_set_peer_state(wl, wlvअगर, wlvअगर->sta.hlid);
	अगर (ret < 0)
		वापस ret;

	wl1271_info("Association completed.");
	वापस 0;
पूर्ण

अटल व्योम wl1271_reg_notअगरy(काष्ठा wiphy *wiphy,
			      काष्ठा regulatory_request *request)
अणु
	काष्ठा ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	काष्ठा wl1271 *wl = hw->priv;

	/* copy the current dfs region */
	अगर (request)
		wl->dfs_region = request->dfs_region;

	wlcore_regकरोमुख्य_config(wl);
पूर्ण

अटल पूर्णांक wl1271_set_rx_streaming(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				   bool enable)
अणु
	पूर्णांक ret = 0;

	/* we should hold wl->mutex */
	ret = wl1271_acx_ps_rx_streaming(wl, wlvअगर, enable);
	अगर (ret < 0)
		जाओ out;

	अगर (enable)
		set_bit(WLVIF_FLAG_RX_STREAMING_STARTED, &wlvअगर->flags);
	अन्यथा
		clear_bit(WLVIF_FLAG_RX_STREAMING_STARTED, &wlvअगर->flags);
out:
	वापस ret;
पूर्ण

/*
 * this function is being called when the rx_streaming पूर्णांकerval
 * has beed changed or rx_streaming should be disabled
 */
पूर्णांक wl1271_recalc_rx_streaming(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	पूर्णांक ret = 0;
	पूर्णांक period = wl->conf.rx_streaming.पूर्णांकerval;

	/* करोn't reconfigure अगर rx_streaming is disabled */
	अगर (!test_bit(WLVIF_FLAG_RX_STREAMING_STARTED, &wlvअगर->flags))
		जाओ out;

	/* reconfigure/disable according to new streaming_period */
	अगर (period &&
	    test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvअगर->flags) &&
	    (wl->conf.rx_streaming.always ||
	     test_bit(WL1271_FLAG_SOFT_GEMINI, &wl->flags)))
		ret = wl1271_set_rx_streaming(wl, wlvअगर, true);
	अन्यथा अणु
		ret = wl1271_set_rx_streaming(wl, wlvअगर, false);
		/* करोn't cancel_work_sync since we might deadlock */
		del_समयr_sync(&wlvअगर->rx_streaming_समयr);
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल व्योम wl1271_rx_streaming_enable_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	काष्ठा wl12xx_vअगर *wlvअगर = container_of(work, काष्ठा wl12xx_vअगर,
						rx_streaming_enable_work);
	काष्ठा wl1271 *wl = wlvअगर->wl;

	mutex_lock(&wl->mutex);

	अगर (test_bit(WLVIF_FLAG_RX_STREAMING_STARTED, &wlvअगर->flags) ||
	    !test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvअगर->flags) ||
	    (!wl->conf.rx_streaming.always &&
	     !test_bit(WL1271_FLAG_SOFT_GEMINI, &wl->flags)))
		जाओ out;

	अगर (!wl->conf.rx_streaming.पूर्णांकerval)
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	ret = wl1271_set_rx_streaming(wl, wlvअगर, true);
	अगर (ret < 0)
		जाओ out_sleep;

	/* stop it after some समय of inactivity */
	mod_समयr(&wlvअगर->rx_streaming_समयr,
		  jअगरfies + msecs_to_jअगरfies(wl->conf.rx_streaming.duration));

out_sleep:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
पूर्ण

अटल व्योम wl1271_rx_streaming_disable_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	काष्ठा wl12xx_vअगर *wlvअगर = container_of(work, काष्ठा wl12xx_vअगर,
						rx_streaming_disable_work);
	काष्ठा wl1271 *wl = wlvअगर->wl;

	mutex_lock(&wl->mutex);

	अगर (!test_bit(WLVIF_FLAG_RX_STREAMING_STARTED, &wlvअगर->flags))
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	ret = wl1271_set_rx_streaming(wl, wlvअगर, false);
	अगर (ret)
		जाओ out_sleep;

out_sleep:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
पूर्ण

अटल व्योम wl1271_rx_streaming_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = from_समयr(wlvअगर, t, rx_streaming_समयr);
	काष्ठा wl1271 *wl = wlvअगर->wl;
	ieee80211_queue_work(wl->hw, &wlvअगर->rx_streaming_disable_work);
पूर्ण

/* wl->mutex must be taken */
व्योम wl12xx_rearm_tx_watchकरोg_locked(काष्ठा wl1271 *wl)
अणु
	/* अगर the watchकरोg is not armed, करोn't करो anything */
	अगर (wl->tx_allocated_blocks == 0)
		वापस;

	cancel_delayed_work(&wl->tx_watchकरोg_work);
	ieee80211_queue_delayed_work(wl->hw, &wl->tx_watchकरोg_work,
		msecs_to_jअगरfies(wl->conf.tx.tx_watchकरोg_समयout));
पूर्ण

अटल व्योम wlcore_rc_update_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	काष्ठा wl12xx_vअगर *wlvअगर = container_of(work, काष्ठा wl12xx_vअगर,
						rc_update_work);
	काष्ठा wl1271 *wl = wlvअगर->wl;
	काष्ठा ieee80211_vअगर *vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	अगर (ieee80211_vअगर_is_mesh(vअगर)) अणु
		ret = wl1271_acx_set_ht_capabilities(wl, &wlvअगर->rc_ht_cap,
						     true, wlvअगर->sta.hlid);
		अगर (ret < 0)
			जाओ out_sleep;
	पूर्ण अन्यथा अणु
		wlcore_hw_sta_rc_update(wl, wlvअगर);
	पूर्ण

out_sleep:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
पूर्ण

अटल व्योम wl12xx_tx_watchकरोg_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork;
	काष्ठा wl1271 *wl;

	dwork = to_delayed_work(work);
	wl = container_of(dwork, काष्ठा wl1271, tx_watchकरोg_work);

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	/* Tx went out in the meanसमय - everything is ok */
	अगर (unlikely(wl->tx_allocated_blocks == 0))
		जाओ out;

	/*
	 * अगर a ROC is in progress, we might not have any Tx क्रम a दीर्घ
	 * समय (e.g. pending Tx on the non-ROC channels)
	 */
	अगर (find_first_bit(wl->roc_map, WL12XX_MAX_ROLES) < WL12XX_MAX_ROLES) अणु
		wl1271_debug(DEBUG_TX, "No Tx (in FW) for %d ms due to ROC",
			     wl->conf.tx.tx_watchकरोg_समयout);
		wl12xx_rearm_tx_watchकरोg_locked(wl);
		जाओ out;
	पूर्ण

	/*
	 * अगर a scan is in progress, we might not have any Tx क्रम a दीर्घ
	 * समय
	 */
	अगर (wl->scan.state != WL1271_SCAN_STATE_IDLE) अणु
		wl1271_debug(DEBUG_TX, "No Tx (in FW) for %d ms due to scan",
			     wl->conf.tx.tx_watchकरोg_समयout);
		wl12xx_rearm_tx_watchकरोg_locked(wl);
		जाओ out;
	पूर्ण

	/*
	* AP might cache a frame क्रम a दीर्घ समय क्रम a sleeping station,
	* so rearm the समयr अगर there's an AP पूर्णांकerface with stations. If
	* Tx is genuinely stuck we will most hopefully discover it when all
	* stations are हटाओd due to inactivity.
	*/
	अगर (wl->active_sta_count) अणु
		wl1271_debug(DEBUG_TX, "No Tx (in FW) for %d ms. AP has "
			     " %d stations",
			      wl->conf.tx.tx_watchकरोg_समयout,
			      wl->active_sta_count);
		wl12xx_rearm_tx_watchकरोg_locked(wl);
		जाओ out;
	पूर्ण

	wl1271_error("Tx stuck (in FW) for %d ms. Starting recovery",
		     wl->conf.tx.tx_watchकरोg_समयout);
	wl12xx_queue_recovery_work(wl);

out:
	mutex_unlock(&wl->mutex);
पूर्ण

अटल व्योम wlcore_adjust_conf(काष्ठा wl1271 *wl)
अणु

	अगर (fwlog_param) अणु
		अगर (!म_भेद(fwlog_param, "continuous")) अणु
			wl->conf.fwlog.mode = WL12XX_FWLOG_CONTINUOUS;
			wl->conf.fwlog.output = WL12XX_FWLOG_OUTPUT_HOST;
		पूर्ण अन्यथा अगर (!म_भेद(fwlog_param, "dbgpins")) अणु
			wl->conf.fwlog.mode = WL12XX_FWLOG_CONTINUOUS;
			wl->conf.fwlog.output = WL12XX_FWLOG_OUTPUT_DBG_PINS;
		पूर्ण अन्यथा अगर (!म_भेद(fwlog_param, "disable")) अणु
			wl->conf.fwlog.mem_blocks = 0;
			wl->conf.fwlog.output = WL12XX_FWLOG_OUTPUT_NONE;
		पूर्ण अन्यथा अणु
			wl1271_error("Unknown fwlog parameter %s", fwlog_param);
		पूर्ण
	पूर्ण

	अगर (bug_on_recovery != -1)
		wl->conf.recovery.bug_on_recovery = (u8) bug_on_recovery;

	अगर (no_recovery != -1)
		wl->conf.recovery.no_recovery = (u8) no_recovery;
पूर्ण

अटल व्योम wl12xx_irq_ps_regulate_link(काष्ठा wl1271 *wl,
					काष्ठा wl12xx_vअगर *wlvअगर,
					u8 hlid, u8 tx_pkts)
अणु
	bool fw_ps;

	fw_ps = test_bit(hlid, &wl->ap_fw_ps_map);

	/*
	 * Wake up from high level PS अगर the STA is asleep with too little
	 * packets in FW or अगर the STA is awake.
	 */
	अगर (!fw_ps || tx_pkts < WL1271_PS_STA_MAX_PACKETS)
		wl12xx_ps_link_end(wl, wlvअगर, hlid);

	/*
	 * Start high-level PS अगर the STA is asleep with enough blocks in FW.
	 * Make an exception अगर this is the only connected link. In this
	 * हाल FW-memory congestion is less of a problem.
	 * Note that a single connected STA means 2*ap_count + 1 active links,
	 * since we must account क्रम the global and broadcast AP links
	 * क्रम each AP. The "fw_ps" check assures us the other link is a STA
	 * connected to the AP. Otherwise the FW would not set the PSM bit.
	 */
	अन्यथा अगर (wl->active_link_count > (wl->ap_count*2 + 1) && fw_ps &&
		 tx_pkts >= WL1271_PS_STA_MAX_PACKETS)
		wl12xx_ps_link_start(wl, wlvअगर, hlid, true);
पूर्ण

अटल व्योम wl12xx_irq_update_links_status(काष्ठा wl1271 *wl,
					   काष्ठा wl12xx_vअगर *wlvअगर,
					   काष्ठा wl_fw_status *status)
अणु
	अचिन्हित दीर्घ cur_fw_ps_map;
	u8 hlid;

	cur_fw_ps_map = status->link_ps_biपंचांगap;
	अगर (wl->ap_fw_ps_map != cur_fw_ps_map) अणु
		wl1271_debug(DEBUG_PSM,
			     "link ps prev 0x%lx cur 0x%lx changed 0x%lx",
			     wl->ap_fw_ps_map, cur_fw_ps_map,
			     wl->ap_fw_ps_map ^ cur_fw_ps_map);

		wl->ap_fw_ps_map = cur_fw_ps_map;
	पूर्ण

	क्रम_each_set_bit(hlid, wlvअगर->ap.sta_hlid_map, wl->num_links)
		wl12xx_irq_ps_regulate_link(wl, wlvअगर, hlid,
					    wl->links[hlid].allocated_pkts);
पूर्ण

अटल पूर्णांक wlcore_fw_status(काष्ठा wl1271 *wl, काष्ठा wl_fw_status *status)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर;
	u32 old_tx_blk_count = wl->tx_blocks_available;
	पूर्णांक avail, मुक्तd_blocks;
	पूर्णांक i;
	पूर्णांक ret;
	काष्ठा wl1271_link *lnk;

	ret = wlcore_raw_पढ़ो_data(wl, REG_RAW_FW_STATUS_ADDR,
				   wl->raw_fw_status,
				   wl->fw_status_len, false);
	अगर (ret < 0)
		वापस ret;

	wlcore_hw_convert_fw_status(wl, wl->raw_fw_status, wl->fw_status);

	wl1271_debug(DEBUG_IRQ, "intr: 0x%x (fw_rx_counter = %d, "
		     "drv_rx_counter = %d, tx_results_counter = %d)",
		     status->पूर्णांकr,
		     status->fw_rx_counter,
		     status->drv_rx_counter,
		     status->tx_results_counter);

	क्रम (i = 0; i < NUM_TX_QUEUES; i++) अणु
		/* prevent wrap-around in मुक्तd-packets counter */
		wl->tx_allocated_pkts[i] -=
				(status->counters.tx_released_pkts[i] -
				wl->tx_pkts_मुक्तd[i]) & 0xff;

		wl->tx_pkts_मुक्तd[i] = status->counters.tx_released_pkts[i];
	पूर्ण


	क्रम_each_set_bit(i, wl->links_map, wl->num_links) अणु
		u8 dअगरf;
		lnk = &wl->links[i];

		/* prevent wrap-around in मुक्तd-packets counter */
		dअगरf = (status->counters.tx_lnk_मुक्त_pkts[i] -
		       lnk->prev_मुक्तd_pkts) & 0xff;

		अगर (dअगरf == 0)
			जारी;

		lnk->allocated_pkts -= dअगरf;
		lnk->prev_मुक्तd_pkts = status->counters.tx_lnk_मुक्त_pkts[i];

		/* accumulate the prev_मुक्तd_pkts counter */
		lnk->total_मुक्तd_pkts += dअगरf;
	पूर्ण

	/* prevent wrap-around in total blocks counter */
	अगर (likely(wl->tx_blocks_मुक्तd <= status->total_released_blks))
		मुक्तd_blocks = status->total_released_blks -
			       wl->tx_blocks_मुक्तd;
	अन्यथा
		मुक्तd_blocks = 0x100000000LL - wl->tx_blocks_मुक्तd +
			       status->total_released_blks;

	wl->tx_blocks_मुक्तd = status->total_released_blks;

	wl->tx_allocated_blocks -= मुक्तd_blocks;

	/*
	 * If the FW मुक्तd some blocks:
	 * If we still have allocated blocks - re-arm the समयr, Tx is
	 * not stuck. Otherwise, cancel the समयr (no Tx currently).
	 */
	अगर (मुक्तd_blocks) अणु
		अगर (wl->tx_allocated_blocks)
			wl12xx_rearm_tx_watchकरोg_locked(wl);
		अन्यथा
			cancel_delayed_work(&wl->tx_watchकरोg_work);
	पूर्ण

	avail = status->tx_total - wl->tx_allocated_blocks;

	/*
	 * The FW might change the total number of TX memblocks beक्रमe
	 * we get a notअगरication about blocks being released. Thus, the
	 * available blocks calculation might yield a temporary result
	 * which is lower than the actual available blocks. Keeping in
	 * mind that only blocks that were allocated can be moved from
	 * TX to RX, tx_blocks_available should never decrease here.
	 */
	wl->tx_blocks_available = max((पूर्णांक)wl->tx_blocks_available,
				      avail);

	/* अगर more blocks are available now, tx work can be scheduled */
	अगर (wl->tx_blocks_available > old_tx_blk_count)
		clear_bit(WL1271_FLAG_FW_TX_BUSY, &wl->flags);

	/* क्रम AP update num of allocated TX blocks per link and ps status */
	wl12xx_क्रम_each_wlvअगर_ap(wl, wlvअगर) अणु
		wl12xx_irq_update_links_status(wl, wlvअगर, status);
	पूर्ण

	/* update the host-chipset समय offset */
	wl->समय_offset = (kसमय_get_bootसमय_ns() >> 10) -
		(s64)(status->fw_स_स्थानीय);

	wl->fw_fast_lnk_map = status->link_fast_biपंचांगap;

	वापस 0;
पूर्ण

अटल व्योम wl1271_flush_deferred_work(काष्ठा wl1271 *wl)
अणु
	काष्ठा sk_buff *skb;

	/* Pass all received frames to the network stack */
	जबतक ((skb = skb_dequeue(&wl->deferred_rx_queue)))
		ieee80211_rx_ni(wl->hw, skb);

	/* Return sent skbs to the network stack */
	जबतक ((skb = skb_dequeue(&wl->deferred_tx_queue)))
		ieee80211_tx_status_ni(wl->hw, skb);
पूर्ण

अटल व्योम wl1271_netstack_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wl1271 *wl =
		container_of(work, काष्ठा wl1271, netstack_work);

	करो अणु
		wl1271_flush_deferred_work(wl);
	पूर्ण जबतक (skb_queue_len(&wl->deferred_rx_queue));
पूर्ण

#घोषणा WL1271_IRQ_MAX_LOOPS 256

अटल पूर्णांक wlcore_irq_locked(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret = 0;
	u32 पूर्णांकr;
	पूर्णांक loopcount = WL1271_IRQ_MAX_LOOPS;
	bool run_tx_queue = true;
	bool करोne = false;
	अचिन्हित पूर्णांक defer_count;
	अचिन्हित दीर्घ flags;

	/*
	 * In हाल edge triggered पूर्णांकerrupt must be used, we cannot iterate
	 * more than once without पूर्णांकroducing race conditions with the hardirq.
	 */
	अगर (wl->irq_flags & (IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING))
		loopcount = 1;

	wl1271_debug(DEBUG_IRQ, "IRQ work");

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	जबतक (!करोne && loopcount--) अणु
		smp_mb__after_atomic();

		ret = wlcore_fw_status(wl, wl->fw_status);
		अगर (ret < 0)
			जाओ err_ret;

		wlcore_hw_tx_immediate_compl(wl);

		पूर्णांकr = wl->fw_status->पूर्णांकr;
		पूर्णांकr &= WLCORE_ALL_INTR_MASK;
		अगर (!पूर्णांकr) अणु
			करोne = true;
			जारी;
		पूर्ण

		अगर (unlikely(पूर्णांकr & WL1271_ACX_INTR_WATCHDOG)) अणु
			wl1271_error("HW watchdog interrupt received! starting recovery.");
			wl->watchकरोg_recovery = true;
			ret = -EIO;

			/* restarting the chip. ignore any other पूर्णांकerrupt. */
			जाओ err_ret;
		पूर्ण

		अगर (unlikely(पूर्णांकr & WL1271_ACX_SW_INTR_WATCHDOG)) अणु
			wl1271_error("SW watchdog interrupt received! "
				     "starting recovery.");
			wl->watchकरोg_recovery = true;
			ret = -EIO;

			/* restarting the chip. ignore any other पूर्णांकerrupt. */
			जाओ err_ret;
		पूर्ण

		अगर (likely(पूर्णांकr & WL1271_ACX_INTR_DATA)) अणु
			wl1271_debug(DEBUG_IRQ, "WL1271_ACX_INTR_DATA");

			ret = wlcore_rx(wl, wl->fw_status);
			अगर (ret < 0)
				जाओ err_ret;

			/* Check अगर any tx blocks were मुक्तd */
			अगर (!test_bit(WL1271_FLAG_FW_TX_BUSY, &wl->flags)) अणु
				अगर (spin_trylock_irqsave(&wl->wl_lock, flags)) अणु
					अगर (!wl1271_tx_total_queue_count(wl))
						run_tx_queue = false;
					spin_unlock_irqrestore(&wl->wl_lock, flags);
				पूर्ण

				/*
				 * In order to aव्योम starvation of the TX path,
				 * call the work function directly.
				 */
				अगर (run_tx_queue) अणु
					ret = wlcore_tx_work_locked(wl);
					अगर (ret < 0)
						जाओ err_ret;
				पूर्ण
			पूर्ण

			/* check क्रम tx results */
			ret = wlcore_hw_tx_delayed_compl(wl);
			अगर (ret < 0)
				जाओ err_ret;

			/* Make sure the deferred queues करोn't get too दीर्घ */
			defer_count = skb_queue_len(&wl->deferred_tx_queue) +
				      skb_queue_len(&wl->deferred_rx_queue);
			अगर (defer_count > WL1271_DEFERRED_QUEUE_LIMIT)
				wl1271_flush_deferred_work(wl);
		पूर्ण

		अगर (पूर्णांकr & WL1271_ACX_INTR_EVENT_A) अणु
			wl1271_debug(DEBUG_IRQ, "WL1271_ACX_INTR_EVENT_A");
			ret = wl1271_event_handle(wl, 0);
			अगर (ret < 0)
				जाओ err_ret;
		पूर्ण

		अगर (पूर्णांकr & WL1271_ACX_INTR_EVENT_B) अणु
			wl1271_debug(DEBUG_IRQ, "WL1271_ACX_INTR_EVENT_B");
			ret = wl1271_event_handle(wl, 1);
			अगर (ret < 0)
				जाओ err_ret;
		पूर्ण

		अगर (पूर्णांकr & WL1271_ACX_INTR_INIT_COMPLETE)
			wl1271_debug(DEBUG_IRQ,
				     "WL1271_ACX_INTR_INIT_COMPLETE");

		अगर (पूर्णांकr & WL1271_ACX_INTR_HW_AVAILABLE)
			wl1271_debug(DEBUG_IRQ, "WL1271_ACX_INTR_HW_AVAILABLE");
	पूर्ण

err_ret:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

out:
	वापस ret;
पूर्ण

अटल irqवापस_t wlcore_irq(पूर्णांक irq, व्योम *cookie)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	काष्ठा wl1271 *wl = cookie;
	bool queue_tx_work = true;

	set_bit(WL1271_FLAG_IRQ_RUNNING, &wl->flags);

	/* complete the ELP completion */
	अगर (test_bit(WL1271_FLAG_IN_ELP, &wl->flags)) अणु
		spin_lock_irqsave(&wl->wl_lock, flags);
		अगर (wl->elp_compl)
			complete(wl->elp_compl);
		spin_unlock_irqrestore(&wl->wl_lock, flags);
	पूर्ण

	अगर (test_bit(WL1271_FLAG_SUSPENDED, &wl->flags)) अणु
		/* करोn't enqueue a work right now. mark it as pending */
		set_bit(WL1271_FLAG_PENDING_WORK, &wl->flags);
		wl1271_debug(DEBUG_IRQ, "should not enqueue work");
		spin_lock_irqsave(&wl->wl_lock, flags);
		disable_irq_nosync(wl->irq);
		pm_wakeup_event(wl->dev, 0);
		spin_unlock_irqrestore(&wl->wl_lock, flags);
		जाओ out_handled;
	पूर्ण

	/* TX might be handled here, aव्योम redundant work */
	set_bit(WL1271_FLAG_TX_PENDING, &wl->flags);
	cancel_work_sync(&wl->tx_work);

	mutex_lock(&wl->mutex);

	ret = wlcore_irq_locked(wl);
	अगर (ret)
		wl12xx_queue_recovery_work(wl);

	/* In हाल TX was not handled in wlcore_irq_locked(), queue TX work */
	clear_bit(WL1271_FLAG_TX_PENDING, &wl->flags);
	अगर (!test_bit(WL1271_FLAG_FW_TX_BUSY, &wl->flags)) अणु
		अगर (spin_trylock_irqsave(&wl->wl_lock, flags)) अणु
			अगर (!wl1271_tx_total_queue_count(wl))
				queue_tx_work = false;
			spin_unlock_irqrestore(&wl->wl_lock, flags);
		पूर्ण
		अगर (queue_tx_work)
			ieee80211_queue_work(wl->hw, &wl->tx_work);
	पूर्ण

	mutex_unlock(&wl->mutex);

out_handled:
	clear_bit(WL1271_FLAG_IRQ_RUNNING, &wl->flags);

	वापस IRQ_HANDLED;
पूर्ण

काष्ठा vअगर_counter_data अणु
	u8 counter;

	काष्ठा ieee80211_vअगर *cur_vअगर;
	bool cur_vअगर_running;
पूर्ण;

अटल व्योम wl12xx_vअगर_count_iter(व्योम *data, u8 *mac,
				  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा vअगर_counter_data *counter = data;

	counter->counter++;
	अगर (counter->cur_vअगर == vअगर)
		counter->cur_vअगर_running = true;
पूर्ण

/* caller must not hold wl->mutex, as it might deadlock */
अटल व्योम wl12xx_get_vअगर_count(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *cur_vअगर,
			       काष्ठा vअगर_counter_data *data)
अणु
	स_रखो(data, 0, माप(*data));
	data->cur_vअगर = cur_vअगर;

	ieee80211_iterate_active_पूर्णांकerfaces(hw, IEEE80211_IFACE_ITER_RESUME_ALL,
					    wl12xx_vअगर_count_iter, data);
पूर्ण

अटल पूर्णांक wl12xx_fetch_firmware(काष्ठा wl1271 *wl, bool plt)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *fw_name;
	क्रमागत wl12xx_fw_type fw_type;
	पूर्णांक ret;

	अगर (plt) अणु
		fw_type = WL12XX_FW_TYPE_PLT;
		fw_name = wl->plt_fw_name;
	पूर्ण अन्यथा अणु
		/*
		 * we can't call wl12xx_get_vअगर_count() here because
		 * wl->mutex is taken, so use the cached last_vअगर_count value
		 */
		अगर (wl->last_vअगर_count > 1 && wl->mr_fw_name) अणु
			fw_type = WL12XX_FW_TYPE_MULTI;
			fw_name = wl->mr_fw_name;
		पूर्ण अन्यथा अणु
			fw_type = WL12XX_FW_TYPE_NORMAL;
			fw_name = wl->sr_fw_name;
		पूर्ण
	पूर्ण

	अगर (wl->fw_type == fw_type)
		वापस 0;

	wl1271_debug(DEBUG_BOOT, "booting firmware %s", fw_name);

	ret = request_firmware(&fw, fw_name, wl->dev);

	अगर (ret < 0) अणु
		wl1271_error("could not get firmware %s: %d", fw_name, ret);
		वापस ret;
	पूर्ण

	अगर (fw->size % 4) अणु
		wl1271_error("firmware size is not multiple of 32 bits: %zu",
			     fw->size);
		ret = -EILSEQ;
		जाओ out;
	पूर्ण

	vमुक्त(wl->fw);
	wl->fw_type = WL12XX_FW_TYPE_NONE;
	wl->fw_len = fw->size;
	wl->fw = vदो_स्मृति(wl->fw_len);

	अगर (!wl->fw) अणु
		wl1271_error("could not allocate memory for the firmware");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	स_नकल(wl->fw, fw->data, wl->fw_len);
	ret = 0;
	wl->fw_type = fw_type;
out:
	release_firmware(fw);

	वापस ret;
पूर्ण

व्योम wl12xx_queue_recovery_work(काष्ठा wl1271 *wl)
अणु
	/* Aव्योम a recursive recovery */
	अगर (wl->state == WLCORE_STATE_ON) अणु
		WARN_ON(!test_bit(WL1271_FLAG_INTENDED_FW_RECOVERY,
				  &wl->flags));

		wl->state = WLCORE_STATE_RESTARTING;
		set_bit(WL1271_FLAG_RECOVERY_IN_PROGRESS, &wl->flags);
		ieee80211_queue_work(wl->hw, &wl->recovery_work);
	पूर्ण
पूर्ण

माप_प्रकार wl12xx_copy_fwlog(काष्ठा wl1271 *wl, u8 *memblock, माप_प्रकार maxlen)
अणु
	माप_प्रकार len;

	/* Make sure we have enough room */
	len = min_t(माप_प्रकार, maxlen, PAGE_SIZE - wl->fwlog_size);

	/* Fill the FW log file, consumed by the sysfs fwlog entry */
	स_नकल(wl->fwlog + wl->fwlog_size, memblock, len);
	wl->fwlog_size += len;

	वापस len;
पूर्ण

अटल व्योम wl12xx_पढ़ो_fwlog_panic(काष्ठा wl1271 *wl)
अणु
	u32 end_of_log = 0;
	पूर्णांक error;

	अगर (wl->quirks & WLCORE_QUIRK_FWLOG_NOT_IMPLEMENTED)
		वापस;

	wl1271_info("Reading FW panic log");

	/*
	 * Make sure the chip is awake and the logger isn't active.
	 * Do not send a stop fwlog command अगर the fw is hanged or अगर
	 * dbgpins are used (due to some fw bug).
	 */
	error = pm_runसमय_get_sync(wl->dev);
	अगर (error < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		वापस;
	पूर्ण
	अगर (!wl->watchकरोg_recovery &&
	    wl->conf.fwlog.output != WL12XX_FWLOG_OUTPUT_DBG_PINS)
		wl12xx_cmd_stop_fwlog(wl);

	/* Traverse the memory blocks linked list */
	करो अणु
		end_of_log = wlcore_event_fw_logger(wl);
		अगर (end_of_log == 0) अणु
			msleep(100);
			end_of_log = wlcore_event_fw_logger(wl);
		पूर्ण
	पूर्ण जबतक (end_of_log != 0);
पूर्ण

अटल व्योम wlcore_save_मुक्तd_pkts(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				   u8 hlid, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा wl1271_station *wl_sta;
	u32 sqn_recovery_padding = WL1271_TX_SQN_POST_RECOVERY_PADDING;

	wl_sta = (व्योम *)sta->drv_priv;
	wl_sta->total_मुक्तd_pkts = wl->links[hlid].total_मुक्तd_pkts;

	/*
	 * increment the initial seq number on recovery to account क्रम
	 * transmitted packets that we haven't yet got in the FW status
	 */
	अगर (wlvअगर->encryption_type == KEY_GEM)
		sqn_recovery_padding = WL1271_TX_SQN_POST_RECOVERY_PADDING_GEM;

	अगर (test_bit(WL1271_FLAG_RECOVERY_IN_PROGRESS, &wl->flags))
		wl_sta->total_मुक्तd_pkts += sqn_recovery_padding;
पूर्ण

अटल व्योम wlcore_save_मुक्तd_pkts_addr(काष्ठा wl1271 *wl,
					काष्ठा wl12xx_vअगर *wlvअगर,
					u8 hlid, स्थिर u8 *addr)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा ieee80211_vअगर *vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);

	अगर (WARN_ON(hlid == WL12XX_INVALID_LINK_ID ||
		    is_zero_ether_addr(addr)))
		वापस;

	rcu_पढ़ो_lock();
	sta = ieee80211_find_sta(vअगर, addr);
	अगर (sta)
		wlcore_save_मुक्तd_pkts(wl, wlvअगर, hlid, sta);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम wlcore_prपूर्णांक_recovery(काष्ठा wl1271 *wl)
अणु
	u32 pc = 0;
	u32 hपूर्णांक_sts = 0;
	पूर्णांक ret;

	wl1271_info("Hardware recovery in progress. FW ver: %s",
		    wl->chip.fw_ver_str);

	/* change partitions momentarily so we can पढ़ो the FW pc */
	ret = wlcore_set_partition(wl, &wl->ptable[PART_BOOT]);
	अगर (ret < 0)
		वापस;

	ret = wlcore_पढ़ो_reg(wl, REG_PC_ON_RECOVERY, &pc);
	अगर (ret < 0)
		वापस;

	ret = wlcore_पढ़ो_reg(wl, REG_INTERRUPT_NO_CLEAR, &hपूर्णांक_sts);
	अगर (ret < 0)
		वापस;

	wl1271_info("pc: 0x%x, hint_sts: 0x%08x count: %d",
				pc, hपूर्णांक_sts, ++wl->recovery_count);

	wlcore_set_partition(wl, &wl->ptable[PART_WORK]);
पूर्ण


अटल व्योम wl1271_recovery_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wl1271 *wl =
		container_of(work, काष्ठा wl1271, recovery_work);
	काष्ठा wl12xx_vअगर *wlvअगर;
	काष्ठा ieee80211_vअगर *vअगर;
	पूर्णांक error;

	mutex_lock(&wl->mutex);

	अगर (wl->state == WLCORE_STATE_OFF || wl->plt)
		जाओ out_unlock;

	error = pm_runसमय_get_sync(wl->dev);
	अगर (error < 0) अणु
		wl1271_warning("Enable for recovery failed");
		pm_runसमय_put_noidle(wl->dev);
	पूर्ण
	wlcore_disable_पूर्णांकerrupts_nosync(wl);

	अगर (!test_bit(WL1271_FLAG_INTENDED_FW_RECOVERY, &wl->flags)) अणु
		अगर (wl->conf.fwlog.output == WL12XX_FWLOG_OUTPUT_HOST)
			wl12xx_पढ़ो_fwlog_panic(wl);
		wlcore_prपूर्णांक_recovery(wl);
	पूर्ण

	BUG_ON(wl->conf.recovery.bug_on_recovery &&
	       !test_bit(WL1271_FLAG_INTENDED_FW_RECOVERY, &wl->flags));

	clear_bit(WL1271_FLAG_INTENDED_FW_RECOVERY, &wl->flags);

	अगर (wl->conf.recovery.no_recovery) अणु
		wl1271_info("No recovery (chosen on module load). Fw will remain stuck.");
		जाओ out_unlock;
	पूर्ण

	/* Prevent spurious TX during FW restart */
	wlcore_stop_queues(wl, WLCORE_QUEUE_STOP_REASON_FW_RESTART);

	/* reboot the chipset */
	जबतक (!list_empty(&wl->wlvअगर_list)) अणु
		wlvअगर = list_first_entry(&wl->wlvअगर_list,
				       काष्ठा wl12xx_vअगर, list);
		vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);

		अगर (wlvअगर->bss_type == BSS_TYPE_STA_BSS &&
		    test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvअगर->flags)) अणु
			wlcore_save_मुक्तd_pkts_addr(wl, wlvअगर, wlvअगर->sta.hlid,
						    vअगर->bss_conf.bssid);
		पूर्ण

		__wl1271_op_हटाओ_पूर्णांकerface(wl, vअगर, false);
	पूर्ण

	wlcore_op_stop_locked(wl);
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

	ieee80211_restart_hw(wl->hw);

	/*
	 * Its safe to enable TX now - the queues are stopped after a request
	 * to restart the HW.
	 */
	wlcore_wake_queues(wl, WLCORE_QUEUE_STOP_REASON_FW_RESTART);

out_unlock:
	wl->watchकरोg_recovery = false;
	clear_bit(WL1271_FLAG_RECOVERY_IN_PROGRESS, &wl->flags);
	mutex_unlock(&wl->mutex);
पूर्ण

अटल पूर्णांक wlcore_fw_wakeup(काष्ठा wl1271 *wl)
अणु
	वापस wlcore_raw_ग_लिखो32(wl, HW_ACCESS_ELP_CTRL_REG, ELPCTRL_WAKE_UP);
पूर्ण

अटल पूर्णांक wl1271_setup(काष्ठा wl1271 *wl)
अणु
	wl->raw_fw_status = kzalloc(wl->fw_status_len, GFP_KERNEL);
	अगर (!wl->raw_fw_status)
		जाओ err;

	wl->fw_status = kzalloc(माप(*wl->fw_status), GFP_KERNEL);
	अगर (!wl->fw_status)
		जाओ err;

	wl->tx_res_अगर = kzalloc(माप(*wl->tx_res_अगर), GFP_KERNEL);
	अगर (!wl->tx_res_अगर)
		जाओ err;

	वापस 0;
err:
	kमुक्त(wl->fw_status);
	kमुक्त(wl->raw_fw_status);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक wl12xx_set_घातer_on(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	msleep(WL1271_PRE_POWER_ON_SLEEP);
	ret = wl1271_घातer_on(wl);
	अगर (ret < 0)
		जाओ out;
	msleep(WL1271_POWER_ON_SLEEP);
	wl1271_io_reset(wl);
	wl1271_io_init(wl);

	ret = wlcore_set_partition(wl, &wl->ptable[PART_BOOT]);
	अगर (ret < 0)
		जाओ fail;

	/* ELP module wake up */
	ret = wlcore_fw_wakeup(wl);
	अगर (ret < 0)
		जाओ fail;

out:
	वापस ret;

fail:
	wl1271_घातer_off(wl);
	वापस ret;
पूर्ण

अटल पूर्णांक wl12xx_chip_wakeup(काष्ठा wl1271 *wl, bool plt)
अणु
	पूर्णांक ret = 0;

	ret = wl12xx_set_घातer_on(wl);
	अगर (ret < 0)
		जाओ out;

	/*
	 * For wl127x based devices we could use the शेष block
	 * size (512 bytes), but due to a bug in the sdio driver, we
	 * need to set it explicitly after the chip is घातered on.  To
	 * simplअगरy the code and since the perक्रमmance impact is
	 * negligible, we use the same block size क्रम all dअगरferent
	 * chip types.
	 *
	 * Check अगर the bus supports blocksize alignment and, अगर it
	 * करोesn't, make sure we don't have the quirk.
	 */
	अगर (!wl1271_set_block_size(wl))
		wl->quirks &= ~WLCORE_QUIRK_TX_BLOCKSIZE_ALIGN;

	/* TODO: make sure the lower driver has set things up correctly */

	ret = wl1271_setup(wl);
	अगर (ret < 0)
		जाओ out;

	ret = wl12xx_fetch_firmware(wl, plt);
	अगर (ret < 0) अणु
		kमुक्त(wl->fw_status);
		kमुक्त(wl->raw_fw_status);
		kमुक्त(wl->tx_res_अगर);
	पूर्ण

out:
	वापस ret;
पूर्ण

पूर्णांक wl1271_plt_start(काष्ठा wl1271 *wl, स्थिर क्रमागत plt_mode plt_mode)
अणु
	पूर्णांक retries = WL1271_BOOT_RETRIES;
	काष्ठा wiphy *wiphy = wl->hw->wiphy;

	अटल स्थिर अक्षर* स्थिर PLT_MODE[] = अणु
		"PLT_OFF",
		"PLT_ON",
		"PLT_FEM_DETECT",
		"PLT_CHIP_AWAKE"
	पूर्ण;

	पूर्णांक ret;

	mutex_lock(&wl->mutex);

	wl1271_notice("power up");

	अगर (wl->state != WLCORE_STATE_OFF) अणु
		wl1271_error("cannot go into PLT state because not "
			     "in off state: %d", wl->state);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/* Indicate to lower levels that we are now in PLT mode */
	wl->plt = true;
	wl->plt_mode = plt_mode;

	जबतक (retries) अणु
		retries--;
		ret = wl12xx_chip_wakeup(wl, true);
		अगर (ret < 0)
			जाओ घातer_off;

		अगर (plt_mode != PLT_CHIP_AWAKE) अणु
			ret = wl->ops->plt_init(wl);
			अगर (ret < 0)
				जाओ घातer_off;
		पूर्ण

		wl->state = WLCORE_STATE_ON;
		wl1271_notice("firmware booted in PLT mode %s (%s)",
			      PLT_MODE[plt_mode],
			      wl->chip.fw_ver_str);

		/* update hw/fw version info in wiphy काष्ठा */
		wiphy->hw_version = wl->chip.id;
		म_नकलन(wiphy->fw_version, wl->chip.fw_ver_str,
			माप(wiphy->fw_version));

		जाओ out;

घातer_off:
		wl1271_घातer_off(wl);
	पूर्ण

	wl->plt = false;
	wl->plt_mode = PLT_OFF;

	wl1271_error("firmware boot in PLT mode failed despite %d retries",
		     WL1271_BOOT_RETRIES);
out:
	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

पूर्णांक wl1271_plt_stop(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret = 0;

	wl1271_notice("power down");

	/*
	 * Interrupts must be disabled beक्रमe setting the state to OFF.
	 * Otherwise, the पूर्णांकerrupt handler might be called and निकास without
	 * पढ़ोing the पूर्णांकerrupt status.
	 */
	wlcore_disable_पूर्णांकerrupts(wl);
	mutex_lock(&wl->mutex);
	अगर (!wl->plt) अणु
		mutex_unlock(&wl->mutex);

		/*
		 * This will not necessarily enable पूर्णांकerrupts as पूर्णांकerrupts
		 * may have been disabled when op_stop was called. It will,
		 * however, balance the above call to disable_पूर्णांकerrupts().
		 */
		wlcore_enable_पूर्णांकerrupts(wl);

		wl1271_error("cannot power down because not in PLT "
			     "state: %d", wl->state);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	mutex_unlock(&wl->mutex);

	wl1271_flush_deferred_work(wl);
	cancel_work_sync(&wl->netstack_work);
	cancel_work_sync(&wl->recovery_work);
	cancel_delayed_work_sync(&wl->tx_watchकरोg_work);

	mutex_lock(&wl->mutex);
	wl1271_घातer_off(wl);
	wl->flags = 0;
	wl->sleep_auth = WL1271_PSM_ILLEGAL;
	wl->state = WLCORE_STATE_OFF;
	wl->plt = false;
	wl->plt_mode = PLT_OFF;
	wl->rx_counter = 0;
	mutex_unlock(&wl->mutex);

out:
	वापस ret;
पूर्ण

अटल व्योम wl1271_op_tx(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_tx_control *control,
			 काष्ठा sk_buff *skb)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_vअगर *vअगर = info->control.vअगर;
	काष्ठा wl12xx_vअगर *wlvअगर = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक q, mapping;
	u8 hlid;

	अगर (!vअगर) अणु
		wl1271_debug(DEBUG_TX, "DROP skb with no vif");
		ieee80211_मुक्त_txskb(hw, skb);
		वापस;
	पूर्ण

	wlvअगर = wl12xx_vअगर_to_data(vअगर);
	mapping = skb_get_queue_mapping(skb);
	q = wl1271_tx_get_queue(mapping);

	hlid = wl12xx_tx_get_hlid(wl, wlvअगर, skb, control->sta);

	spin_lock_irqsave(&wl->wl_lock, flags);

	/*
	 * drop the packet अगर the link is invalid or the queue is stopped
	 * क्रम any reason but watermark. Watermark is a "soft"-stop so we
	 * allow these packets through.
	 */
	अगर (hlid == WL12XX_INVALID_LINK_ID ||
	    (!test_bit(hlid, wlvअगर->links_map)) ||
	     (wlcore_is_queue_stopped_locked(wl, wlvअगर, q) &&
	      !wlcore_is_queue_stopped_by_reason_locked(wl, wlvअगर, q,
			WLCORE_QUEUE_STOP_REASON_WATERMARK))) अणु
		wl1271_debug(DEBUG_TX, "DROP skb hlid %d q %d", hlid, q);
		ieee80211_मुक्त_txskb(hw, skb);
		जाओ out;
	पूर्ण

	wl1271_debug(DEBUG_TX, "queue skb hlid %d q %d len %d",
		     hlid, q, skb->len);
	skb_queue_tail(&wl->links[hlid].tx_queue[q], skb);

	wl->tx_queue_count[q]++;
	wlvअगर->tx_queue_count[q]++;

	/*
	 * The workqueue is slow to process the tx_queue and we need stop
	 * the queue here, otherwise the queue will get too दीर्घ.
	 */
	अगर (wlvअगर->tx_queue_count[q] >= WL1271_TX_QUEUE_HIGH_WATERMARK &&
	    !wlcore_is_queue_stopped_by_reason_locked(wl, wlvअगर, q,
					WLCORE_QUEUE_STOP_REASON_WATERMARK)) अणु
		wl1271_debug(DEBUG_TX, "op_tx: stopping queues for q %d", q);
		wlcore_stop_queue_locked(wl, wlvअगर, q,
					 WLCORE_QUEUE_STOP_REASON_WATERMARK);
	पूर्ण

	/*
	 * The chip specअगरic setup must run beक्रमe the first TX packet -
	 * beक्रमe that, the tx_work will not be initialized!
	 */

	अगर (!test_bit(WL1271_FLAG_FW_TX_BUSY, &wl->flags) &&
	    !test_bit(WL1271_FLAG_TX_PENDING, &wl->flags))
		ieee80211_queue_work(wl->hw, &wl->tx_work);

out:
	spin_unlock_irqrestore(&wl->wl_lock, flags);
पूर्ण

पूर्णांक wl1271_tx_dummy_packet(काष्ठा wl1271 *wl)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक q;

	/* no need to queue a new dummy packet अगर one is alपढ़ोy pending */
	अगर (test_bit(WL1271_FLAG_DUMMY_PACKET_PENDING, &wl->flags))
		वापस 0;

	q = wl1271_tx_get_queue(skb_get_queue_mapping(wl->dummy_packet));

	spin_lock_irqsave(&wl->wl_lock, flags);
	set_bit(WL1271_FLAG_DUMMY_PACKET_PENDING, &wl->flags);
	wl->tx_queue_count[q]++;
	spin_unlock_irqrestore(&wl->wl_lock, flags);

	/* The FW is low on RX memory blocks, so send the dummy packet asap */
	अगर (!test_bit(WL1271_FLAG_FW_TX_BUSY, &wl->flags))
		वापस wlcore_tx_work_locked(wl);

	/*
	 * If the FW TX is busy, TX work will be scheduled by the thपढ़ोed
	 * पूर्णांकerrupt handler function
	 */
	वापस 0;
पूर्ण

/*
 * The size of the dummy packet should be at least 1400 bytes. However, in
 * order to minimize the number of bus transactions, aligning it to 512 bytes
 * boundaries could be beneficial, perक्रमmance wise
 */
#घोषणा TOTAL_TX_DUMMY_PACKET_SIZE (ALIGN(1400, 512))

अटल काष्ठा sk_buff *wl12xx_alloc_dummy_packet(काष्ठा wl1271 *wl)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_hdr_3addr *hdr;
	अचिन्हित पूर्णांक dummy_packet_size;

	dummy_packet_size = TOTAL_TX_DUMMY_PACKET_SIZE -
			    माप(काष्ठा wl1271_tx_hw_descr) - माप(*hdr);

	skb = dev_alloc_skb(TOTAL_TX_DUMMY_PACKET_SIZE);
	अगर (!skb) अणु
		wl1271_warning("Failed to allocate a dummy packet skb");
		वापस शून्य;
	पूर्ण

	skb_reserve(skb, माप(काष्ठा wl1271_tx_hw_descr));

	hdr = skb_put_zero(skb, माप(*hdr));
	hdr->frame_control = cpu_to_le16(IEEE80211_FTYPE_DATA |
					 IEEE80211_STYPE_शून्यFUNC |
					 IEEE80211_FCTL_TODS);

	skb_put_zero(skb, dummy_packet_size);

	/* Dummy packets require the TID to be management */
	skb->priority = WL1271_TID_MGMT;

	/* Initialize all fields that might be used */
	skb_set_queue_mapping(skb, 0);
	स_रखो(IEEE80211_SKB_CB(skb), 0, माप(काष्ठा ieee80211_tx_info));

	वापस skb;
पूर्ण


अटल पूर्णांक
wl1271_validate_wowlan_pattern(काष्ठा cfg80211_pkt_pattern *p)
अणु
	पूर्णांक num_fields = 0, in_field = 0, fields_size = 0;
	पूर्णांक i, pattern_len = 0;

	अगर (!p->mask) अणु
		wl1271_warning("No mask in WoWLAN pattern");
		वापस -EINVAL;
	पूर्ण

	/*
	 * The pattern is broken up पूर्णांकo segments of bytes at dअगरferent offsets
	 * that need to be checked by the FW filter. Each segment is called
	 * a field in the FW API. We verअगरy that the total number of fields
	 * required क्रम this pattern won't exceed FW limits (8)
	 * as well as the total fields buffer won't exceed the FW limit.
	 * Note that अगर there's a pattern which crosses Ethernet/IP header
	 * boundary a new field is required.
	 */
	क्रम (i = 0; i < p->pattern_len; i++) अणु
		अगर (test_bit(i, (अचिन्हित दीर्घ *)p->mask)) अणु
			अगर (!in_field) अणु
				in_field = 1;
				pattern_len = 1;
			पूर्ण अन्यथा अणु
				अगर (i == WL1271_RX_FILTER_ETH_HEADER_SIZE) अणु
					num_fields++;
					fields_size += pattern_len +
						RX_FILTER_FIELD_OVERHEAD;
					pattern_len = 1;
				पूर्ण अन्यथा
					pattern_len++;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (in_field) अणु
				in_field = 0;
				fields_size += pattern_len +
					RX_FILTER_FIELD_OVERHEAD;
				num_fields++;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (in_field) अणु
		fields_size += pattern_len + RX_FILTER_FIELD_OVERHEAD;
		num_fields++;
	पूर्ण

	अगर (num_fields > WL1271_RX_FILTER_MAX_FIELDS) अणु
		wl1271_warning("RX Filter too complex. Too many segments");
		वापस -EINVAL;
	पूर्ण

	अगर (fields_size > WL1271_RX_FILTER_MAX_FIELDS_SIZE) अणु
		wl1271_warning("RX filter pattern is too big");
		वापस -E2BIG;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा wl12xx_rx_filter *wl1271_rx_filter_alloc(व्योम)
अणु
	वापस kzalloc(माप(काष्ठा wl12xx_rx_filter), GFP_KERNEL);
पूर्ण

व्योम wl1271_rx_filter_मुक्त(काष्ठा wl12xx_rx_filter *filter)
अणु
	पूर्णांक i;

	अगर (filter == शून्य)
		वापस;

	क्रम (i = 0; i < filter->num_fields; i++)
		kमुक्त(filter->fields[i].pattern);

	kमुक्त(filter);
पूर्ण

पूर्णांक wl1271_rx_filter_alloc_field(काष्ठा wl12xx_rx_filter *filter,
				 u16 offset, u8 flags,
				 स्थिर u8 *pattern, u8 len)
अणु
	काष्ठा wl12xx_rx_filter_field *field;

	अगर (filter->num_fields == WL1271_RX_FILTER_MAX_FIELDS) अणु
		wl1271_warning("Max fields per RX filter. can't alloc another");
		वापस -EINVAL;
	पूर्ण

	field = &filter->fields[filter->num_fields];

	field->pattern = kmemdup(pattern, len, GFP_KERNEL);
	अगर (!field->pattern) अणु
		wl1271_warning("Failed to allocate RX filter pattern");
		वापस -ENOMEM;
	पूर्ण

	filter->num_fields++;

	field->offset = cpu_to_le16(offset);
	field->flags = flags;
	field->len = len;

	वापस 0;
पूर्ण

पूर्णांक wl1271_rx_filter_get_fields_size(काष्ठा wl12xx_rx_filter *filter)
अणु
	पूर्णांक i, fields_size = 0;

	क्रम (i = 0; i < filter->num_fields; i++)
		fields_size += filter->fields[i].len +
			माप(काष्ठा wl12xx_rx_filter_field) -
			माप(u8 *);

	वापस fields_size;
पूर्ण

व्योम wl1271_rx_filter_flatten_fields(काष्ठा wl12xx_rx_filter *filter,
				    u8 *buf)
अणु
	पूर्णांक i;
	काष्ठा wl12xx_rx_filter_field *field;

	क्रम (i = 0; i < filter->num_fields; i++) अणु
		field = (काष्ठा wl12xx_rx_filter_field *)buf;

		field->offset = filter->fields[i].offset;
		field->flags = filter->fields[i].flags;
		field->len = filter->fields[i].len;

		स_नकल(&field->pattern, filter->fields[i].pattern, field->len);
		buf += माप(काष्ठा wl12xx_rx_filter_field) -
			माप(u8 *) + field->len;
	पूर्ण
पूर्ण

/*
 * Allocates an RX filter वापसed through f
 * which needs to be मुक्तd using rx_filter_मुक्त()
 */
अटल पूर्णांक
wl1271_convert_wowlan_pattern_to_rx_filter(काष्ठा cfg80211_pkt_pattern *p,
					   काष्ठा wl12xx_rx_filter **f)
अणु
	पूर्णांक i, j, ret = 0;
	काष्ठा wl12xx_rx_filter *filter;
	u16 offset;
	u8 flags, len;

	filter = wl1271_rx_filter_alloc();
	अगर (!filter) अणु
		wl1271_warning("Failed to alloc rx filter");
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	i = 0;
	जबतक (i < p->pattern_len) अणु
		अगर (!test_bit(i, (अचिन्हित दीर्घ *)p->mask)) अणु
			i++;
			जारी;
		पूर्ण

		क्रम (j = i; j < p->pattern_len; j++) अणु
			अगर (!test_bit(j, (अचिन्हित दीर्घ *)p->mask))
				अवरोध;

			अगर (i < WL1271_RX_FILTER_ETH_HEADER_SIZE &&
			    j >= WL1271_RX_FILTER_ETH_HEADER_SIZE)
				अवरोध;
		पूर्ण

		अगर (i < WL1271_RX_FILTER_ETH_HEADER_SIZE) अणु
			offset = i;
			flags = WL1271_RX_FILTER_FLAG_ETHERNET_HEADER;
		पूर्ण अन्यथा अणु
			offset = i - WL1271_RX_FILTER_ETH_HEADER_SIZE;
			flags = WL1271_RX_FILTER_FLAG_IP_HEADER;
		पूर्ण

		len = j - i;

		ret = wl1271_rx_filter_alloc_field(filter,
						   offset,
						   flags,
						   &p->pattern[i], len);
		अगर (ret)
			जाओ err;

		i = j;
	पूर्ण

	filter->action = FILTER_SIGNAL;

	*f = filter;
	वापस 0;

err:
	wl1271_rx_filter_मुक्त(filter);
	*f = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक wl1271_configure_wowlan(काष्ठा wl1271 *wl,
				   काष्ठा cfg80211_wowlan *wow)
अणु
	पूर्णांक i, ret;

	अगर (!wow || wow->any || !wow->n_patterns) अणु
		ret = wl1271_acx_शेष_rx_filter_enable(wl, 0,
							  FILTER_SIGNAL);
		अगर (ret)
			जाओ out;

		ret = wl1271_rx_filter_clear_all(wl);
		अगर (ret)
			जाओ out;

		वापस 0;
	पूर्ण

	अगर (WARN_ON(wow->n_patterns > WL1271_MAX_RX_FILTERS))
		वापस -EINVAL;

	/* Validate all incoming patterns beक्रमe clearing current FW state */
	क्रम (i = 0; i < wow->n_patterns; i++) अणु
		ret = wl1271_validate_wowlan_pattern(&wow->patterns[i]);
		अगर (ret) अणु
			wl1271_warning("Bad wowlan pattern %d", i);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = wl1271_acx_शेष_rx_filter_enable(wl, 0, FILTER_SIGNAL);
	अगर (ret)
		जाओ out;

	ret = wl1271_rx_filter_clear_all(wl);
	अगर (ret)
		जाओ out;

	/* Translate WoWLAN patterns पूर्णांकo filters */
	क्रम (i = 0; i < wow->n_patterns; i++) अणु
		काष्ठा cfg80211_pkt_pattern *p;
		काष्ठा wl12xx_rx_filter *filter = शून्य;

		p = &wow->patterns[i];

		ret = wl1271_convert_wowlan_pattern_to_rx_filter(p, &filter);
		अगर (ret) अणु
			wl1271_warning("Failed to create an RX filter from "
				       "wowlan pattern %d", i);
			जाओ out;
		पूर्ण

		ret = wl1271_rx_filter_enable(wl, i, 1, filter);

		wl1271_rx_filter_मुक्त(filter);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = wl1271_acx_शेष_rx_filter_enable(wl, 1, FILTER_DROP);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl1271_configure_suspend_sta(काष्ठा wl1271 *wl,
					काष्ठा wl12xx_vअगर *wlvअगर,
					काष्ठा cfg80211_wowlan *wow)
अणु
	पूर्णांक ret = 0;

	अगर (!test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvअगर->flags))
		जाओ out;

	ret = wl1271_configure_wowlan(wl, wow);
	अगर (ret < 0)
		जाओ out;

	अगर ((wl->conf.conn.suspend_wake_up_event ==
	     wl->conf.conn.wake_up_event) &&
	    (wl->conf.conn.suspend_listen_पूर्णांकerval ==
	     wl->conf.conn.listen_पूर्णांकerval))
		जाओ out;

	ret = wl1271_acx_wake_up_conditions(wl, wlvअगर,
				    wl->conf.conn.suspend_wake_up_event,
				    wl->conf.conn.suspend_listen_पूर्णांकerval);

	अगर (ret < 0)
		wl1271_error("suspend: set wake up conditions failed: %d", ret);
out:
	वापस ret;

पूर्ण

अटल पूर्णांक wl1271_configure_suspend_ap(काष्ठा wl1271 *wl,
					काष्ठा wl12xx_vअगर *wlvअगर,
					काष्ठा cfg80211_wowlan *wow)
अणु
	पूर्णांक ret = 0;

	अगर (!test_bit(WLVIF_FLAG_AP_STARTED, &wlvअगर->flags))
		जाओ out;

	ret = wl1271_acx_beacon_filter_opt(wl, wlvअगर, true);
	अगर (ret < 0)
		जाओ out;

	ret = wl1271_configure_wowlan(wl, wow);
	अगर (ret < 0)
		जाओ out;

out:
	वापस ret;

पूर्ण

अटल पूर्णांक wl1271_configure_suspend(काष्ठा wl1271 *wl,
				    काष्ठा wl12xx_vअगर *wlvअगर,
				    काष्ठा cfg80211_wowlan *wow)
अणु
	अगर (wlvअगर->bss_type == BSS_TYPE_STA_BSS)
		वापस wl1271_configure_suspend_sta(wl, wlvअगर, wow);
	अगर (wlvअगर->bss_type == BSS_TYPE_AP_BSS)
		वापस wl1271_configure_suspend_ap(wl, wlvअगर, wow);
	वापस 0;
पूर्ण

अटल व्योम wl1271_configure_resume(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	पूर्णांक ret = 0;
	bool is_ap = wlvअगर->bss_type == BSS_TYPE_AP_BSS;
	bool is_sta = wlvअगर->bss_type == BSS_TYPE_STA_BSS;

	अगर ((!is_ap) && (!is_sta))
		वापस;

	अगर ((is_sta && !test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvअगर->flags)) ||
	    (is_ap && !test_bit(WLVIF_FLAG_AP_STARTED, &wlvअगर->flags)))
		वापस;

	wl1271_configure_wowlan(wl, शून्य);

	अगर (is_sta) अणु
		अगर ((wl->conf.conn.suspend_wake_up_event ==
		     wl->conf.conn.wake_up_event) &&
		    (wl->conf.conn.suspend_listen_पूर्णांकerval ==
		     wl->conf.conn.listen_पूर्णांकerval))
			वापस;

		ret = wl1271_acx_wake_up_conditions(wl, wlvअगर,
				    wl->conf.conn.wake_up_event,
				    wl->conf.conn.listen_पूर्णांकerval);

		अगर (ret < 0)
			wl1271_error("resume: wake up conditions failed: %d",
				     ret);

	पूर्ण अन्यथा अगर (is_ap) अणु
		ret = wl1271_acx_beacon_filter_opt(wl, wlvअगर, false);
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused wl1271_op_suspend(काष्ठा ieee80211_hw *hw,
					    काष्ठा cfg80211_wowlan *wow)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	wl1271_debug(DEBUG_MAC80211, "mac80211 suspend wow=%d", !!wow);
	WARN_ON(!wow);

	/* we want to perक्रमm the recovery beक्रमe suspending */
	अगर (test_bit(WL1271_FLAG_RECOVERY_IN_PROGRESS, &wl->flags)) अणु
		wl1271_warning("postponing suspend to perform recovery");
		वापस -EBUSY;
	पूर्ण

	wl1271_tx_flush(wl);

	mutex_lock(&wl->mutex);

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		mutex_unlock(&wl->mutex);
		वापस ret;
	पूर्ण

	wl->wow_enabled = true;
	wl12xx_क्रम_each_wlvअगर(wl, wlvअगर) अणु
		अगर (wlcore_is_p2p_mgmt(wlvअगर))
			जारी;

		ret = wl1271_configure_suspend(wl, wlvअगर, wow);
		अगर (ret < 0) अणु
			जाओ out_sleep;
		पूर्ण
	पूर्ण

	/* disable fast link flow control notअगरications from FW */
	ret = wlcore_hw_पूर्णांकerrupt_notअगरy(wl, false);
	अगर (ret < 0)
		जाओ out_sleep;

	/* अगर filtering is enabled, configure the FW to drop all RX BA frames */
	ret = wlcore_hw_rx_ba_filter(wl,
				     !!wl->conf.conn.suspend_rx_ba_activity);
	अगर (ret < 0)
		जाओ out_sleep;

out_sleep:
	pm_runसमय_put_noidle(wl->dev);
	mutex_unlock(&wl->mutex);

	अगर (ret < 0) अणु
		wl1271_warning("couldn't prepare device to suspend");
		वापस ret;
	पूर्ण

	/* flush any reमुख्यing work */
	wl1271_debug(DEBUG_MAC80211, "flushing remaining works");

	flush_work(&wl->tx_work);

	/*
	 * Cancel the watchकरोg even अगर above tx_flush failed. We will detect
	 * it on resume anyway.
	 */
	cancel_delayed_work(&wl->tx_watchकरोg_work);

	/*
	 * set suspended flag to aव्योम triggering a new thपढ़ोed_irq
	 * work.
	 */
	spin_lock_irqsave(&wl->wl_lock, flags);
	set_bit(WL1271_FLAG_SUSPENDED, &wl->flags);
	spin_unlock_irqrestore(&wl->wl_lock, flags);

	वापस pm_runसमय_क्रमce_suspend(wl->dev);
पूर्ण

अटल पूर्णांक __maybe_unused wl1271_op_resume(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर;
	अचिन्हित दीर्घ flags;
	bool run_irq_work = false, pending_recovery;
	पूर्णांक ret;

	wl1271_debug(DEBUG_MAC80211, "mac80211 resume wow=%d",
		     wl->wow_enabled);
	WARN_ON(!wl->wow_enabled);

	ret = pm_runसमय_क्रमce_resume(wl->dev);
	अगर (ret < 0) अणु
		wl1271_error("ELP wakeup failure!");
		जाओ out_sleep;
	पूर्ण

	/*
	 * re-enable irq_work enqueuing, and call irq_work directly अगर
	 * there is a pending work.
	 */
	spin_lock_irqsave(&wl->wl_lock, flags);
	clear_bit(WL1271_FLAG_SUSPENDED, &wl->flags);
	अगर (test_and_clear_bit(WL1271_FLAG_PENDING_WORK, &wl->flags))
		run_irq_work = true;
	spin_unlock_irqrestore(&wl->wl_lock, flags);

	mutex_lock(&wl->mutex);

	/* test the recovery flag beक्रमe calling any SDIO functions */
	pending_recovery = test_bit(WL1271_FLAG_RECOVERY_IN_PROGRESS,
				    &wl->flags);

	अगर (run_irq_work) अणु
		wl1271_debug(DEBUG_MAC80211,
			     "run postponed irq_work directly");

		/* करोn't talk to the HW अगर recovery is pending */
		अगर (!pending_recovery) अणु
			ret = wlcore_irq_locked(wl);
			अगर (ret)
				wl12xx_queue_recovery_work(wl);
		पूर्ण

		wlcore_enable_पूर्णांकerrupts(wl);
	पूर्ण

	अगर (pending_recovery) अणु
		wl1271_warning("queuing forgotten recovery on resume");
		ieee80211_queue_work(wl->hw, &wl->recovery_work);
		जाओ out_sleep;
	पूर्ण

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	wl12xx_क्रम_each_wlvअगर(wl, wlvअगर) अणु
		अगर (wlcore_is_p2p_mgmt(wlvअगर))
			जारी;

		wl1271_configure_resume(wl, wlvअगर);
	पूर्ण

	ret = wlcore_hw_पूर्णांकerrupt_notअगरy(wl, true);
	अगर (ret < 0)
		जाओ out_sleep;

	/* अगर filtering is enabled, configure the FW to drop all RX BA frames */
	ret = wlcore_hw_rx_ba_filter(wl, false);
	अगर (ret < 0)
		जाओ out_sleep;

out_sleep:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

out:
	wl->wow_enabled = false;

	/*
	 * Set a flag to re-init the watchकरोg on the first Tx after resume.
	 * That way we aव्योम possible conditions where Tx-complete पूर्णांकerrupts
	 * fail to arrive and we perक्रमm a spurious recovery.
	 */
	set_bit(WL1271_FLAG_REINIT_TX_WDOG, &wl->flags);
	mutex_unlock(&wl->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक wl1271_op_start(काष्ठा ieee80211_hw *hw)
अणु
	wl1271_debug(DEBUG_MAC80211, "mac80211 start");

	/*
	 * We have to delay the booting of the hardware because
	 * we need to know the local MAC address beक्रमe करोwnloading and
	 * initializing the firmware. The MAC address cannot be changed
	 * after boot, and without the proper MAC address, the firmware
	 * will not function properly.
	 *
	 * The MAC address is first known when the corresponding पूर्णांकerface
	 * is added. That is where we will initialize the hardware.
	 */

	वापस 0;
पूर्ण

अटल व्योम wlcore_op_stop_locked(काष्ठा wl1271 *wl)
अणु
	पूर्णांक i;

	अगर (wl->state == WLCORE_STATE_OFF) अणु
		अगर (test_and_clear_bit(WL1271_FLAG_RECOVERY_IN_PROGRESS,
					&wl->flags))
			wlcore_enable_पूर्णांकerrupts(wl);

		वापस;
	पूर्ण

	/*
	 * this must be beक्रमe the cancel_work calls below, so that the work
	 * functions करोn't perक्रमm further work.
	 */
	wl->state = WLCORE_STATE_OFF;

	/*
	 * Use the nosync variant to disable पूर्णांकerrupts, so the mutex could be
	 * held जबतक करोing so without deadlocking.
	 */
	wlcore_disable_पूर्णांकerrupts_nosync(wl);

	mutex_unlock(&wl->mutex);

	wlcore_synchronize_पूर्णांकerrupts(wl);
	अगर (!test_bit(WL1271_FLAG_RECOVERY_IN_PROGRESS, &wl->flags))
		cancel_work_sync(&wl->recovery_work);
	wl1271_flush_deferred_work(wl);
	cancel_delayed_work_sync(&wl->scan_complete_work);
	cancel_work_sync(&wl->netstack_work);
	cancel_work_sync(&wl->tx_work);
	cancel_delayed_work_sync(&wl->tx_watchकरोg_work);

	/* let's notअगरy MAC80211 about the reमुख्यing pending TX frames */
	mutex_lock(&wl->mutex);
	wl12xx_tx_reset(wl);

	wl1271_घातer_off(wl);
	/*
	 * In हाल a recovery was scheduled, पूर्णांकerrupts were disabled to aव्योम
	 * an पूर्णांकerrupt storm. Now that the घातer is करोwn, it is safe to
	 * re-enable पूर्णांकerrupts to balance the disable depth
	 */
	अगर (test_and_clear_bit(WL1271_FLAG_RECOVERY_IN_PROGRESS, &wl->flags))
		wlcore_enable_पूर्णांकerrupts(wl);

	wl->band = NL80211_BAND_2GHZ;

	wl->rx_counter = 0;
	wl->घातer_level = WL1271_DEFAULT_POWER_LEVEL;
	wl->channel_type = NL80211_CHAN_NO_HT;
	wl->tx_blocks_available = 0;
	wl->tx_allocated_blocks = 0;
	wl->tx_results_count = 0;
	wl->tx_packets_count = 0;
	wl->समय_offset = 0;
	wl->ap_fw_ps_map = 0;
	wl->ap_ps_map = 0;
	wl->sleep_auth = WL1271_PSM_ILLEGAL;
	स_रखो(wl->roles_map, 0, माप(wl->roles_map));
	स_रखो(wl->links_map, 0, माप(wl->links_map));
	स_रखो(wl->roc_map, 0, माप(wl->roc_map));
	स_रखो(wl->session_ids, 0, माप(wl->session_ids));
	स_रखो(wl->rx_filter_enabled, 0, माप(wl->rx_filter_enabled));
	wl->active_sta_count = 0;
	wl->active_link_count = 0;

	/* The प्रणाली link is always allocated */
	wl->links[WL12XX_SYSTEM_HLID].allocated_pkts = 0;
	wl->links[WL12XX_SYSTEM_HLID].prev_मुक्तd_pkts = 0;
	__set_bit(WL12XX_SYSTEM_HLID, wl->links_map);

	/*
	 * this is perक्रमmed after the cancel_work calls and the associated
	 * mutex_lock, so that wl1271_op_add_पूर्णांकerface करोes not accidentally
	 * get executed beक्रमe all these vars have been reset.
	 */
	wl->flags = 0;

	wl->tx_blocks_मुक्तd = 0;

	क्रम (i = 0; i < NUM_TX_QUEUES; i++) अणु
		wl->tx_pkts_मुक्तd[i] = 0;
		wl->tx_allocated_pkts[i] = 0;
	पूर्ण

	wl1271_debugfs_reset(wl);

	kमुक्त(wl->raw_fw_status);
	wl->raw_fw_status = शून्य;
	kमुक्त(wl->fw_status);
	wl->fw_status = शून्य;
	kमुक्त(wl->tx_res_अगर);
	wl->tx_res_अगर = शून्य;
	kमुक्त(wl->target_mem_map);
	wl->target_mem_map = शून्य;

	/*
	 * FW channels must be re-calibrated after recovery,
	 * save current Reg-Doमुख्य channel configuration and clear it.
	 */
	स_नकल(wl->reg_ch_conf_pending, wl->reg_ch_conf_last,
	       माप(wl->reg_ch_conf_pending));
	स_रखो(wl->reg_ch_conf_last, 0, माप(wl->reg_ch_conf_last));
पूर्ण

अटल व्योम wlcore_op_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा wl1271 *wl = hw->priv;

	wl1271_debug(DEBUG_MAC80211, "mac80211 stop");

	mutex_lock(&wl->mutex);

	wlcore_op_stop_locked(wl);

	mutex_unlock(&wl->mutex);
पूर्ण

अटल व्योम wlcore_channel_चयन_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork;
	काष्ठा wl1271 *wl;
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा wl12xx_vअगर *wlvअगर;
	पूर्णांक ret;

	dwork = to_delayed_work(work);
	wlvअगर = container_of(dwork, काष्ठा wl12xx_vअगर, channel_चयन_work);
	wl = wlvअगर->wl;

	wl1271_info("channel switch failed (role_id: %d).", wlvअगर->role_id);

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	/* check the channel चयन is still ongoing */
	अगर (!test_and_clear_bit(WLVIF_FLAG_CS_PROGRESS, &wlvअगर->flags))
		जाओ out;

	vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);
	ieee80211_chचयन_करोne(vअगर, false);

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	wl12xx_cmd_stop_channel_चयन(wl, wlvअगर);

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
पूर्ण

अटल व्योम wlcore_connection_loss_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork;
	काष्ठा wl1271 *wl;
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा wl12xx_vअगर *wlvअगर;

	dwork = to_delayed_work(work);
	wlvअगर = container_of(dwork, काष्ठा wl12xx_vअगर, connection_loss_work);
	wl = wlvअगर->wl;

	wl1271_info("Connection loss work (role_id: %d).", wlvअगर->role_id);

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	/* Call mac80211 connection loss */
	अगर (!test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvअगर->flags))
		जाओ out;

	vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);
	ieee80211_connection_loss(vअगर);
out:
	mutex_unlock(&wl->mutex);
पूर्ण

अटल व्योम wlcore_pending_auth_complete_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork;
	काष्ठा wl1271 *wl;
	काष्ठा wl12xx_vअगर *wlvअगर;
	अचिन्हित दीर्घ समय_spare;
	पूर्णांक ret;

	dwork = to_delayed_work(work);
	wlvअगर = container_of(dwork, काष्ठा wl12xx_vअगर,
			     pending_auth_complete_work);
	wl = wlvअगर->wl;

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	/*
	 * Make sure a second really passed since the last auth reply. Maybe
	 * a second auth reply arrived जबतक we were stuck on the mutex.
	 * Check क्रम a little less than the समयout to protect from scheduler
	 * irregularities.
	 */
	समय_spare = jअगरfies +
			msecs_to_jअगरfies(WLCORE_PEND_AUTH_ROC_TIMEOUT - 50);
	अगर (!समय_after(समय_spare, wlvअगर->pending_auth_reply_समय))
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	/* cancel the ROC अगर active */
	wlcore_update_inconn_sta(wl, wlvअगर, शून्य, false);

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
पूर्ण

अटल पूर्णांक wl12xx_allocate_rate_policy(काष्ठा wl1271 *wl, u8 *idx)
अणु
	u8 policy = find_first_zero_bit(wl->rate_policies_map,
					WL12XX_MAX_RATE_POLICIES);
	अगर (policy >= WL12XX_MAX_RATE_POLICIES)
		वापस -EBUSY;

	__set_bit(policy, wl->rate_policies_map);
	*idx = policy;
	वापस 0;
पूर्ण

अटल व्योम wl12xx_मुक्त_rate_policy(काष्ठा wl1271 *wl, u8 *idx)
अणु
	अगर (WARN_ON(*idx >= WL12XX_MAX_RATE_POLICIES))
		वापस;

	__clear_bit(*idx, wl->rate_policies_map);
	*idx = WL12XX_MAX_RATE_POLICIES;
पूर्ण

अटल पूर्णांक wlcore_allocate_klv_ढाँचा(काष्ठा wl1271 *wl, u8 *idx)
अणु
	u8 policy = find_first_zero_bit(wl->klv_ढाँचाs_map,
					WLCORE_MAX_KLV_TEMPLATES);
	अगर (policy >= WLCORE_MAX_KLV_TEMPLATES)
		वापस -EBUSY;

	__set_bit(policy, wl->klv_ढाँचाs_map);
	*idx = policy;
	वापस 0;
पूर्ण

अटल व्योम wlcore_मुक्त_klv_ढाँचा(काष्ठा wl1271 *wl, u8 *idx)
अणु
	अगर (WARN_ON(*idx >= WLCORE_MAX_KLV_TEMPLATES))
		वापस;

	__clear_bit(*idx, wl->klv_ढाँचाs_map);
	*idx = WLCORE_MAX_KLV_TEMPLATES;
पूर्ण

अटल u8 wl12xx_get_role_type(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा ieee80211_vअगर *vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);

	चयन (wlvअगर->bss_type) अणु
	हाल BSS_TYPE_AP_BSS:
		अगर (wlvअगर->p2p)
			वापस WL1271_ROLE_P2P_GO;
		अन्यथा अगर (ieee80211_vअगर_is_mesh(vअगर))
			वापस WL1271_ROLE_MESH_POINT;
		अन्यथा
			वापस WL1271_ROLE_AP;

	हाल BSS_TYPE_STA_BSS:
		अगर (wlvअगर->p2p)
			वापस WL1271_ROLE_P2P_CL;
		अन्यथा
			वापस WL1271_ROLE_STA;

	हाल BSS_TYPE_IBSS:
		वापस WL1271_ROLE_IBSS;

	शेष:
		wl1271_error("invalid bss_type: %d", wlvअगर->bss_type);
	पूर्ण
	वापस WL12XX_INVALID_ROLE_TYPE;
पूर्ण

अटल पूर्णांक wl12xx_init_vअगर_data(काष्ठा wl1271 *wl, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	पूर्णांक i;

	/* clear everything but the persistent data */
	स_रखो(wlvअगर, 0, दुरत्व(काष्ठा wl12xx_vअगर, persistent));

	चयन (ieee80211_vअगर_type_p2p(vअगर)) अणु
	हाल NL80211_IFTYPE_P2P_CLIENT:
		wlvअगर->p2p = 1;
		fallthrough;
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_P2P_DEVICE:
		wlvअगर->bss_type = BSS_TYPE_STA_BSS;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		wlvअगर->bss_type = BSS_TYPE_IBSS;
		अवरोध;
	हाल NL80211_IFTYPE_P2P_GO:
		wlvअगर->p2p = 1;
		fallthrough;
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_MESH_POINT:
		wlvअगर->bss_type = BSS_TYPE_AP_BSS;
		अवरोध;
	शेष:
		wlvअगर->bss_type = MAX_BSS_TYPE;
		वापस -EOPNOTSUPP;
	पूर्ण

	wlvअगर->role_id = WL12XX_INVALID_ROLE_ID;
	wlvअगर->dev_role_id = WL12XX_INVALID_ROLE_ID;
	wlvअगर->dev_hlid = WL12XX_INVALID_LINK_ID;

	अगर (wlvअगर->bss_type == BSS_TYPE_STA_BSS ||
	    wlvअगर->bss_type == BSS_TYPE_IBSS) अणु
		/* init sta/ibss data */
		wlvअगर->sta.hlid = WL12XX_INVALID_LINK_ID;
		wl12xx_allocate_rate_policy(wl, &wlvअगर->sta.basic_rate_idx);
		wl12xx_allocate_rate_policy(wl, &wlvअगर->sta.ap_rate_idx);
		wl12xx_allocate_rate_policy(wl, &wlvअगर->sta.p2p_rate_idx);
		wlcore_allocate_klv_ढाँचा(wl, &wlvअगर->sta.klv_ढाँचा_id);
		wlvअगर->basic_rate_set = CONF_TX_RATE_MASK_BASIC;
		wlvअगर->basic_rate = CONF_TX_RATE_MASK_BASIC;
		wlvअगर->rate_set = CONF_TX_RATE_MASK_BASIC;
	पूर्ण अन्यथा अणु
		/* init ap data */
		wlvअगर->ap.bcast_hlid = WL12XX_INVALID_LINK_ID;
		wlvअगर->ap.global_hlid = WL12XX_INVALID_LINK_ID;
		wl12xx_allocate_rate_policy(wl, &wlvअगर->ap.mgmt_rate_idx);
		wl12xx_allocate_rate_policy(wl, &wlvअगर->ap.bcast_rate_idx);
		क्रम (i = 0; i < CONF_TX_MAX_AC_COUNT; i++)
			wl12xx_allocate_rate_policy(wl,
						&wlvअगर->ap.ucast_rate_idx[i]);
		wlvअगर->basic_rate_set = CONF_TX_ENABLED_RATES;
		/*
		 * TODO: check अगर basic_rate shouldn't be
		 * wl1271_tx_min_rate_get(wl, wlvअगर->basic_rate_set);
		 * instead (the same thing क्रम STA above).
		*/
		wlvअगर->basic_rate = CONF_TX_ENABLED_RATES;
		/* TODO: this seems to be used only क्रम STA, check it */
		wlvअगर->rate_set = CONF_TX_ENABLED_RATES;
	पूर्ण

	wlvअगर->bitrate_masks[NL80211_BAND_2GHZ] = wl->conf.tx.basic_rate;
	wlvअगर->bitrate_masks[NL80211_BAND_5GHZ] = wl->conf.tx.basic_rate_5;
	wlvअगर->beacon_पूर्णांक = WL1271_DEFAULT_BEACON_INT;

	/*
	 * mac80211 configures some values globally, जबतक we treat them
	 * per-पूर्णांकerface. thus, on init, we have to copy them from wl
	 */
	wlvअगर->band = wl->band;
	wlvअगर->channel = wl->channel;
	wlvअगर->घातer_level = wl->घातer_level;
	wlvअगर->channel_type = wl->channel_type;

	INIT_WORK(&wlvअगर->rx_streaming_enable_work,
		  wl1271_rx_streaming_enable_work);
	INIT_WORK(&wlvअगर->rx_streaming_disable_work,
		  wl1271_rx_streaming_disable_work);
	INIT_WORK(&wlvअगर->rc_update_work, wlcore_rc_update_work);
	INIT_DELAYED_WORK(&wlvअगर->channel_चयन_work,
			  wlcore_channel_चयन_work);
	INIT_DELAYED_WORK(&wlvअगर->connection_loss_work,
			  wlcore_connection_loss_work);
	INIT_DELAYED_WORK(&wlvअगर->pending_auth_complete_work,
			  wlcore_pending_auth_complete_work);
	INIT_LIST_HEAD(&wlvअगर->list);

	समयr_setup(&wlvअगर->rx_streaming_समयr, wl1271_rx_streaming_समयr, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक wl12xx_init_fw(काष्ठा wl1271 *wl)
अणु
	पूर्णांक retries = WL1271_BOOT_RETRIES;
	bool booted = false;
	काष्ठा wiphy *wiphy = wl->hw->wiphy;
	पूर्णांक ret;

	जबतक (retries) अणु
		retries--;
		ret = wl12xx_chip_wakeup(wl, false);
		अगर (ret < 0)
			जाओ घातer_off;

		ret = wl->ops->boot(wl);
		अगर (ret < 0)
			जाओ घातer_off;

		ret = wl1271_hw_init(wl);
		अगर (ret < 0)
			जाओ irq_disable;

		booted = true;
		अवरोध;

irq_disable:
		mutex_unlock(&wl->mutex);
		/* Unlocking the mutex in the middle of handling is
		   inherently unsafe. In this हाल we deem it safe to करो,
		   because we need to let any possibly pending IRQ out of
		   the प्रणाली (and जबतक we are WLCORE_STATE_OFF the IRQ
		   work function will not करो anything.) Also, any other
		   possible concurrent operations will fail due to the
		   current state, hence the wl1271 काष्ठा should be safe. */
		wlcore_disable_पूर्णांकerrupts(wl);
		wl1271_flush_deferred_work(wl);
		cancel_work_sync(&wl->netstack_work);
		mutex_lock(&wl->mutex);
घातer_off:
		wl1271_घातer_off(wl);
	पूर्ण

	अगर (!booted) अणु
		wl1271_error("firmware boot failed despite %d retries",
			     WL1271_BOOT_RETRIES);
		जाओ out;
	पूर्ण

	wl1271_info("firmware booted (%s)", wl->chip.fw_ver_str);

	/* update hw/fw version info in wiphy काष्ठा */
	wiphy->hw_version = wl->chip.id;
	म_नकलन(wiphy->fw_version, wl->chip.fw_ver_str,
		माप(wiphy->fw_version));

	/*
	 * Now we know अगर 11a is supported (info from the NVS), so disable
	 * 11a channels अगर not supported
	 */
	अगर (!wl->enable_11a)
		wiphy->bands[NL80211_BAND_5GHZ]->n_channels = 0;

	wl1271_debug(DEBUG_MAC80211, "11a is %ssupported",
		     wl->enable_11a ? "" : "not ");

	wl->state = WLCORE_STATE_ON;
out:
	वापस ret;
पूर्ण

अटल bool wl12xx_dev_role_started(काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	वापस wlvअगर->dev_hlid != WL12XX_INVALID_LINK_ID;
पूर्ण

/*
 * Check whether a fw चयन (i.e. moving from one loaded
 * fw to another) is needed. This function is also responsible
 * क्रम updating wl->last_vअगर_count, so it must be called beक्रमe
 * loading a non-plt fw (so the correct fw (single-role/multi-role)
 * will be used).
 */
अटल bool wl12xx_need_fw_change(काष्ठा wl1271 *wl,
				  काष्ठा vअगर_counter_data vअगर_counter_data,
				  bool add)
अणु
	क्रमागत wl12xx_fw_type current_fw = wl->fw_type;
	u8 vअगर_count = vअगर_counter_data.counter;

	अगर (test_bit(WL1271_FLAG_VIF_CHANGE_IN_PROGRESS, &wl->flags))
		वापस false;

	/* increase the vअगर count अगर this is a new vअगर */
	अगर (add && !vअगर_counter_data.cur_vअगर_running)
		vअगर_count++;

	wl->last_vअगर_count = vअगर_count;

	/* no need क्रम fw change अगर the device is OFF */
	अगर (wl->state == WLCORE_STATE_OFF)
		वापस false;

	/* no need क्रम fw change अगर a single fw is used */
	अगर (!wl->mr_fw_name)
		वापस false;

	अगर (vअगर_count > 1 && current_fw == WL12XX_FW_TYPE_NORMAL)
		वापस true;
	अगर (vअगर_count <= 1 && current_fw == WL12XX_FW_TYPE_MULTI)
		वापस true;

	वापस false;
पूर्ण

/*
 * Enter "forced psm". Make sure the sta is in psm against the ap,
 * to make the fw चयन a bit more disconnection-persistent.
 */
अटल व्योम wl12xx_क्रमce_active_psm(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर;

	wl12xx_क्रम_each_wlvअगर_sta(wl, wlvअगर) अणु
		wl1271_ps_set_mode(wl, wlvअगर, STATION_POWER_SAVE_MODE);
	पूर्ण
पूर्ण

काष्ठा wlcore_hw_queue_iter_data अणु
	अचिन्हित दीर्घ hw_queue_map[BITS_TO_LONGS(WLCORE_NUM_MAC_ADDRESSES)];
	/* current vअगर */
	काष्ठा ieee80211_vअगर *vअगर;
	/* is the current vअगर among those iterated */
	bool cur_running;
पूर्ण;

अटल व्योम wlcore_hw_queue_iter(व्योम *data, u8 *mac,
				 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wlcore_hw_queue_iter_data *iter_data = data;

	अगर (vअगर->type == NL80211_IFTYPE_P2P_DEVICE ||
	    WARN_ON_ONCE(vअगर->hw_queue[0] == IEEE80211_INVAL_HW_QUEUE))
		वापस;

	अगर (iter_data->cur_running || vअगर == iter_data->vअगर) अणु
		iter_data->cur_running = true;
		वापस;
	पूर्ण

	__set_bit(vअगर->hw_queue[0] / NUM_TX_QUEUES, iter_data->hw_queue_map);
पूर्ण

अटल पूर्णांक wlcore_allocate_hw_queue_base(काष्ठा wl1271 *wl,
					 काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा ieee80211_vअगर *vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);
	काष्ठा wlcore_hw_queue_iter_data iter_data = अणुपूर्ण;
	पूर्णांक i, q_base;

	अगर (vअगर->type == NL80211_IFTYPE_P2P_DEVICE) अणु
		vअगर->cab_queue = IEEE80211_INVAL_HW_QUEUE;
		वापस 0;
	पूर्ण

	iter_data.vअगर = vअगर;

	/* mark all bits taken by active पूर्णांकerfaces */
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(wl->hw,
					IEEE80211_IFACE_ITER_RESUME_ALL,
					wlcore_hw_queue_iter, &iter_data);

	/* the current vअगर is alपढ़ोy running in mac80211 (resume/recovery) */
	अगर (iter_data.cur_running) अणु
		wlvअगर->hw_queue_base = vअगर->hw_queue[0];
		wl1271_debug(DEBUG_MAC80211,
			     "using pre-allocated hw queue base %d",
			     wlvअगर->hw_queue_base);

		/* पूर्णांकerface type might have changed type */
		जाओ adjust_cab_queue;
	पूर्ण

	q_base = find_first_zero_bit(iter_data.hw_queue_map,
				     WLCORE_NUM_MAC_ADDRESSES);
	अगर (q_base >= WLCORE_NUM_MAC_ADDRESSES)
		वापस -EBUSY;

	wlvअगर->hw_queue_base = q_base * NUM_TX_QUEUES;
	wl1271_debug(DEBUG_MAC80211, "allocating hw queue base: %d",
		     wlvअगर->hw_queue_base);

	क्रम (i = 0; i < NUM_TX_QUEUES; i++) अणु
		wl->queue_stop_reasons[wlvअगर->hw_queue_base + i] = 0;
		/* रेजिस्टर hw queues in mac80211 */
		vअगर->hw_queue[i] = wlvअगर->hw_queue_base + i;
	पूर्ण

adjust_cab_queue:
	/* the last places are reserved क्रम cab queues per पूर्णांकerface */
	अगर (wlvअगर->bss_type == BSS_TYPE_AP_BSS)
		vअगर->cab_queue = NUM_TX_QUEUES * WLCORE_NUM_MAC_ADDRESSES +
				 wlvअगर->hw_queue_base / NUM_TX_QUEUES;
	अन्यथा
		vअगर->cab_queue = IEEE80211_INVAL_HW_QUEUE;

	वापस 0;
पूर्ण

अटल पूर्णांक wl1271_op_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	काष्ठा vअगर_counter_data vअगर_count;
	पूर्णांक ret = 0;
	u8 role_type;

	अगर (wl->plt) अणु
		wl1271_error("Adding Interface not allowed while in PLT mode");
		वापस -EBUSY;
	पूर्ण

	vअगर->driver_flags |= IEEE80211_VIF_BEACON_FILTER |
			     IEEE80211_VIF_SUPPORTS_UAPSD |
			     IEEE80211_VIF_SUPPORTS_CQM_RSSI;

	wl1271_debug(DEBUG_MAC80211, "mac80211 add interface type %d mac %pM",
		     ieee80211_vअगर_type_p2p(vअगर), vअगर->addr);

	wl12xx_get_vअगर_count(hw, vअगर, &vअगर_count);

	mutex_lock(&wl->mutex);

	/*
	 * in some very corner हाल HW recovery scenarios its possible to
	 * get here beक्रमe __wl1271_op_हटाओ_पूर्णांकerface is complete, so
	 * opt out अगर that is the हाल.
	 */
	अगर (test_bit(WL1271_FLAG_RECOVERY_IN_PROGRESS, &wl->flags) ||
	    test_bit(WLVIF_FLAG_INITIALIZED, &wlvअगर->flags)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण


	ret = wl12xx_init_vअगर_data(wl, vअगर);
	अगर (ret < 0)
		जाओ out;

	wlvअगर->wl = wl;
	role_type = wl12xx_get_role_type(wl, wlvअगर);
	अगर (role_type == WL12XX_INVALID_ROLE_TYPE) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = wlcore_allocate_hw_queue_base(wl, wlvअगर);
	अगर (ret < 0)
		जाओ out;

	/*
	 * TODO: after the nvs issue will be solved, move this block
	 * to start(), and make sure here the driver is ON.
	 */
	अगर (wl->state == WLCORE_STATE_OFF) अणु
		/*
		 * we still need this in order to configure the fw
		 * जबतक uploading the nvs
		 */
		स_नकल(wl->addresses[0].addr, vअगर->addr, ETH_ALEN);

		ret = wl12xx_init_fw(wl);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	/*
	 * Call runसमय PM only after possible wl12xx_init_fw() above
	 * is करोne. Otherwise we करो not have पूर्णांकerrupts enabled.
	 */
	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out_unlock;
	पूर्ण

	अगर (wl12xx_need_fw_change(wl, vअगर_count, true)) अणु
		wl12xx_क्रमce_active_psm(wl);
		set_bit(WL1271_FLAG_INTENDED_FW_RECOVERY, &wl->flags);
		mutex_unlock(&wl->mutex);
		wl1271_recovery_work(&wl->recovery_work);
		वापस 0;
	पूर्ण

	अगर (!wlcore_is_p2p_mgmt(wlvअगर)) अणु
		ret = wl12xx_cmd_role_enable(wl, vअगर->addr,
					     role_type, &wlvअगर->role_id);
		अगर (ret < 0)
			जाओ out;

		ret = wl1271_init_vअगर_specअगरic(wl, vअगर);
		अगर (ret < 0)
			जाओ out;

	पूर्ण अन्यथा अणु
		ret = wl12xx_cmd_role_enable(wl, vअगर->addr, WL1271_ROLE_DEVICE,
					     &wlvअगर->dev_role_id);
		अगर (ret < 0)
			जाओ out;

		/* needed मुख्यly क्रम configuring rate policies */
		ret = wl1271_sta_hw_init(wl, wlvअगर);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	list_add(&wlvअगर->list, &wl->wlvअगर_list);
	set_bit(WLVIF_FLAG_INITIALIZED, &wlvअगर->flags);

	अगर (wlvअगर->bss_type == BSS_TYPE_AP_BSS)
		wl->ap_count++;
	अन्यथा
		wl->sta_count++;
out:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out_unlock:
	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

अटल व्योम __wl1271_op_हटाओ_पूर्णांकerface(काष्ठा wl1271 *wl,
					 काष्ठा ieee80211_vअगर *vअगर,
					 bool reset_tx_queues)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	पूर्णांक i, ret;
	bool is_ap = (wlvअगर->bss_type == BSS_TYPE_AP_BSS);

	wl1271_debug(DEBUG_MAC80211, "mac80211 remove interface");

	अगर (!test_and_clear_bit(WLVIF_FLAG_INITIALIZED, &wlvअगर->flags))
		वापस;

	/* because of hardware recovery, we may get here twice */
	अगर (wl->state == WLCORE_STATE_OFF)
		वापस;

	wl1271_info("down");

	अगर (wl->scan.state != WL1271_SCAN_STATE_IDLE &&
	    wl->scan_wlvअगर == wlvअगर) अणु
		काष्ठा cfg80211_scan_info info = अणु
			.पातed = true,
		पूर्ण;

		/*
		 * Rearm the tx watchकरोg just beक्रमe idling scan. This
		 * prevents just-finished scans from triggering the watchकरोg
		 */
		wl12xx_rearm_tx_watchकरोg_locked(wl);

		wl->scan.state = WL1271_SCAN_STATE_IDLE;
		स_रखो(wl->scan.scanned_ch, 0, माप(wl->scan.scanned_ch));
		wl->scan_wlvअगर = शून्य;
		wl->scan.req = शून्य;
		ieee80211_scan_completed(wl->hw, &info);
	पूर्ण

	अगर (wl->sched_vअगर == wlvअगर)
		wl->sched_vअगर = शून्य;

	अगर (wl->roc_vअगर == vअगर) अणु
		wl->roc_vअगर = शून्य;
		ieee80211_reमुख्य_on_channel_expired(wl->hw);
	पूर्ण

	अगर (!test_bit(WL1271_FLAG_RECOVERY_IN_PROGRESS, &wl->flags)) अणु
		/* disable active roles */
		ret = pm_runसमय_get_sync(wl->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(wl->dev);
			जाओ deinit;
		पूर्ण

		अगर (wlvअगर->bss_type == BSS_TYPE_STA_BSS ||
		    wlvअगर->bss_type == BSS_TYPE_IBSS) अणु
			अगर (wl12xx_dev_role_started(wlvअगर))
				wl12xx_stop_dev(wl, wlvअगर);
		पूर्ण

		अगर (!wlcore_is_p2p_mgmt(wlvअगर)) अणु
			ret = wl12xx_cmd_role_disable(wl, &wlvअगर->role_id);
			अगर (ret < 0) अणु
				pm_runसमय_put_noidle(wl->dev);
				जाओ deinit;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = wl12xx_cmd_role_disable(wl, &wlvअगर->dev_role_id);
			अगर (ret < 0) अणु
				pm_runसमय_put_noidle(wl->dev);
				जाओ deinit;
			पूर्ण
		पूर्ण

		pm_runसमय_mark_last_busy(wl->dev);
		pm_runसमय_put_स्वतःsuspend(wl->dev);
	पूर्ण
deinit:
	wl12xx_tx_reset_wlvअगर(wl, wlvअगर);

	/* clear all hlids (except प्रणाली_hlid) */
	wlvअगर->dev_hlid = WL12XX_INVALID_LINK_ID;

	अगर (wlvअगर->bss_type == BSS_TYPE_STA_BSS ||
	    wlvअगर->bss_type == BSS_TYPE_IBSS) अणु
		wlvअगर->sta.hlid = WL12XX_INVALID_LINK_ID;
		wl12xx_मुक्त_rate_policy(wl, &wlvअगर->sta.basic_rate_idx);
		wl12xx_मुक्त_rate_policy(wl, &wlvअगर->sta.ap_rate_idx);
		wl12xx_मुक्त_rate_policy(wl, &wlvअगर->sta.p2p_rate_idx);
		wlcore_मुक्त_klv_ढाँचा(wl, &wlvअगर->sta.klv_ढाँचा_id);
	पूर्ण अन्यथा अणु
		wlvअगर->ap.bcast_hlid = WL12XX_INVALID_LINK_ID;
		wlvअगर->ap.global_hlid = WL12XX_INVALID_LINK_ID;
		wl12xx_मुक्त_rate_policy(wl, &wlvअगर->ap.mgmt_rate_idx);
		wl12xx_मुक्त_rate_policy(wl, &wlvअगर->ap.bcast_rate_idx);
		क्रम (i = 0; i < CONF_TX_MAX_AC_COUNT; i++)
			wl12xx_मुक्त_rate_policy(wl,
						&wlvअगर->ap.ucast_rate_idx[i]);
		wl1271_मुक्त_ap_keys(wl, wlvअगर);
	पूर्ण

	dev_kमुक्त_skb(wlvअगर->probereq);
	wlvअगर->probereq = शून्य;
	अगर (wl->last_wlvअगर == wlvअगर)
		wl->last_wlvअगर = शून्य;
	list_del(&wlvअगर->list);
	स_रखो(wlvअगर->ap.sta_hlid_map, 0, माप(wlvअगर->ap.sta_hlid_map));
	wlvअगर->role_id = WL12XX_INVALID_ROLE_ID;
	wlvअगर->dev_role_id = WL12XX_INVALID_ROLE_ID;

	अगर (is_ap)
		wl->ap_count--;
	अन्यथा
		wl->sta_count--;

	/*
	 * Last AP, have more stations. Configure sleep auth according to STA.
	 * Don't करो thin on unपूर्णांकended recovery.
	 */
	अगर (test_bit(WL1271_FLAG_RECOVERY_IN_PROGRESS, &wl->flags) &&
	    !test_bit(WL1271_FLAG_INTENDED_FW_RECOVERY, &wl->flags))
		जाओ unlock;

	अगर (wl->ap_count == 0 && is_ap) अणु
		/* mask ap events */
		wl->event_mask &= ~wl->ap_event_mask;
		wl1271_event_unmask(wl);
	पूर्ण

	अगर (wl->ap_count == 0 && is_ap && wl->sta_count) अणु
		u8 sta_auth = wl->conf.conn.sta_sleep_auth;
		/* Configure क्रम घातer according to debugfs */
		अगर (sta_auth != WL1271_PSM_ILLEGAL)
			wl1271_acx_sleep_auth(wl, sta_auth);
		/* Configure क्रम ELP घातer saving */
		अन्यथा
			wl1271_acx_sleep_auth(wl, WL1271_PSM_ELP);
	पूर्ण

unlock:
	mutex_unlock(&wl->mutex);

	del_समयr_sync(&wlvअगर->rx_streaming_समयr);
	cancel_work_sync(&wlvअगर->rx_streaming_enable_work);
	cancel_work_sync(&wlvअगर->rx_streaming_disable_work);
	cancel_work_sync(&wlvअगर->rc_update_work);
	cancel_delayed_work_sync(&wlvअगर->connection_loss_work);
	cancel_delayed_work_sync(&wlvअगर->channel_चयन_work);
	cancel_delayed_work_sync(&wlvअगर->pending_auth_complete_work);

	mutex_lock(&wl->mutex);
पूर्ण

अटल व्योम wl1271_op_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	काष्ठा wl12xx_vअगर *iter;
	काष्ठा vअगर_counter_data vअगर_count;

	wl12xx_get_vअगर_count(hw, vअगर, &vअगर_count);
	mutex_lock(&wl->mutex);

	अगर (wl->state == WLCORE_STATE_OFF ||
	    !test_bit(WLVIF_FLAG_INITIALIZED, &wlvअगर->flags))
		जाओ out;

	/*
	 * wl->vअगर can be null here अगर someone shuts करोwn the पूर्णांकerface
	 * just when hardware recovery has been started.
	 */
	wl12xx_क्रम_each_wlvअगर(wl, iter) अणु
		अगर (iter != wlvअगर)
			जारी;

		__wl1271_op_हटाओ_पूर्णांकerface(wl, vअगर, true);
		अवरोध;
	पूर्ण
	WARN_ON(iter != wlvअगर);
	अगर (wl12xx_need_fw_change(wl, vअगर_count, false)) अणु
		wl12xx_क्रमce_active_psm(wl);
		set_bit(WL1271_FLAG_INTENDED_FW_RECOVERY, &wl->flags);
		wl12xx_queue_recovery_work(wl);
	पूर्ण
out:
	mutex_unlock(&wl->mutex);
पूर्ण

अटल पूर्णांक wl12xx_op_change_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर *vअगर,
				      क्रमागत nl80211_अगरtype new_type, bool p2p)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	पूर्णांक ret;

	set_bit(WL1271_FLAG_VIF_CHANGE_IN_PROGRESS, &wl->flags);
	wl1271_op_हटाओ_पूर्णांकerface(hw, vअगर);

	vअगर->type = new_type;
	vअगर->p2p = p2p;
	ret = wl1271_op_add_पूर्णांकerface(hw, vअगर);

	clear_bit(WL1271_FLAG_VIF_CHANGE_IN_PROGRESS, &wl->flags);
	वापस ret;
पूर्ण

अटल पूर्णांक wlcore_join(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	पूर्णांक ret;
	bool is_ibss = (wlvअगर->bss_type == BSS_TYPE_IBSS);

	/*
	 * One of the side effects of the JOIN command is that is clears
	 * WPA/WPA2 keys from the chipset. Perक्रमming a JOIN जबतक associated
	 * to a WPA/WPA2 access poपूर्णांक will thereक्रमe समाप्त the data-path.
	 * Currently the only valid scenario क्रम JOIN during association
	 * is on roaming, in which हाल we will also be given new keys.
	 * Keep the below message क्रम now, unless it starts bothering
	 * users who really like to roam a lot :)
	 */
	अगर (test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvअगर->flags))
		wl1271_info("JOIN while associated.");

	/* clear encryption type */
	wlvअगर->encryption_type = KEY_NONE;

	अगर (is_ibss)
		ret = wl12xx_cmd_role_start_ibss(wl, wlvअगर);
	अन्यथा
		ret = wl12xx_cmd_role_start_sta(wl, wlvअगर);

	वापस ret;
पूर्ण

अटल पूर्णांक wl1271_ssid_set(काष्ठा wl12xx_vअगर *wlvअगर, काष्ठा sk_buff *skb,
			    पूर्णांक offset)
अणु
	u8 ssid_len;
	स्थिर u8 *ptr = cfg80211_find_ie(WLAN_EID_SSID, skb->data + offset,
					 skb->len - offset);

	अगर (!ptr) अणु
		wl1271_error("No SSID in IEs!");
		वापस -ENOENT;
	पूर्ण

	ssid_len = ptr[1];
	अगर (ssid_len > IEEE80211_MAX_SSID_LEN) अणु
		wl1271_error("SSID is too long!");
		वापस -EINVAL;
	पूर्ण

	wlvअगर->ssid_len = ssid_len;
	स_नकल(wlvअगर->ssid, ptr+2, ssid_len);
	वापस 0;
पूर्ण

अटल पूर्णांक wlcore_set_ssid(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा ieee80211_vअगर *vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);
	काष्ठा sk_buff *skb;
	पूर्णांक ieoffset;

	/* we currently only support setting the ssid from the ap probe req */
	अगर (wlvअगर->bss_type != BSS_TYPE_STA_BSS)
		वापस -EINVAL;

	skb = ieee80211_ap_probereq_get(wl->hw, vअगर);
	अगर (!skb)
		वापस -EINVAL;

	ieoffset = दुरत्व(काष्ठा ieee80211_mgmt,
			    u.probe_req.variable);
	wl1271_ssid_set(wlvअगर, skb, ieoffset);
	dev_kमुक्त_skb(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक wlcore_set_assoc(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			    काष्ठा ieee80211_bss_conf *bss_conf,
			    u32 sta_rate_set)
अणु
	पूर्णांक ieoffset;
	पूर्णांक ret;

	wlvअगर->aid = bss_conf->aid;
	wlvअगर->channel_type = cfg80211_get_chandef_type(&bss_conf->chandef);
	wlvअगर->beacon_पूर्णांक = bss_conf->beacon_पूर्णांक;
	wlvअगर->wmm_enabled = bss_conf->qos;

	set_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvअगर->flags);

	/*
	 * with wl1271, we करोn't need to update the
	 * beacon_पूर्णांक and dtim_period, because the firmware
	 * updates it by itself when the first beacon is
	 * received after a join.
	 */
	ret = wl1271_cmd_build_ps_poll(wl, wlvअगर, wlvअगर->aid);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Get a ढाँचा क्रम hardware connection मुख्यtenance
	 */
	dev_kमुक्त_skb(wlvअगर->probereq);
	wlvअगर->probereq = wl1271_cmd_build_ap_probe_req(wl,
							wlvअगर,
							शून्य);
	ieoffset = दुरत्व(काष्ठा ieee80211_mgmt,
			    u.probe_req.variable);
	wl1271_ssid_set(wlvअगर, wlvअगर->probereq, ieoffset);

	/* enable the connection monitoring feature */
	ret = wl1271_acx_conn_monit_params(wl, wlvअगर, true);
	अगर (ret < 0)
		वापस ret;

	/*
	 * The join command disable the keep-alive mode, shut करोwn its process,
	 * and also clear the ढाँचा config, so we need to reset it all after
	 * the join. The acx_aid starts the keep-alive process, and the order
	 * of the commands below is relevant.
	 */
	ret = wl1271_acx_keep_alive_mode(wl, wlvअगर, true);
	अगर (ret < 0)
		वापस ret;

	ret = wl1271_acx_aid(wl, wlvअगर, wlvअगर->aid);
	अगर (ret < 0)
		वापस ret;

	ret = wl12xx_cmd_build_klv_null_data(wl, wlvअगर);
	अगर (ret < 0)
		वापस ret;

	ret = wl1271_acx_keep_alive_config(wl, wlvअगर,
					   wlvअगर->sta.klv_ढाँचा_id,
					   ACX_KEEP_ALIVE_TPL_VALID);
	अगर (ret < 0)
		वापस ret;

	/*
	 * The शेष fw psm configuration is AUTO, जबतक mac80211 शेष
	 * setting is off (ACTIVE), so sync the fw with the correct value.
	 */
	ret = wl1271_ps_set_mode(wl, wlvअगर, STATION_ACTIVE_MODE);
	अगर (ret < 0)
		वापस ret;

	अगर (sta_rate_set) अणु
		wlvअगर->rate_set =
			wl1271_tx_enabled_rates_get(wl,
						    sta_rate_set,
						    wlvअगर->band);
		ret = wl1271_acx_sta_rate_policies(wl, wlvअगर);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक wlcore_unset_assoc(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	पूर्णांक ret;
	bool sta = wlvअगर->bss_type == BSS_TYPE_STA_BSS;

	/* make sure we are connected (sta) joined */
	अगर (sta &&
	    !test_and_clear_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvअगर->flags))
		वापस false;

	/* make sure we are joined (ibss) */
	अगर (!sta &&
	    test_and_clear_bit(WLVIF_FLAG_IBSS_JOINED, &wlvअगर->flags))
		वापस false;

	अगर (sta) अणु
		/* use शेषs when not associated */
		wlvअगर->aid = 0;

		/* मुक्त probe-request ढाँचा */
		dev_kमुक्त_skb(wlvअगर->probereq);
		wlvअगर->probereq = शून्य;

		/* disable connection monitor features */
		ret = wl1271_acx_conn_monit_params(wl, wlvअगर, false);
		अगर (ret < 0)
			वापस ret;

		/* Disable the keep-alive feature */
		ret = wl1271_acx_keep_alive_mode(wl, wlvअगर, false);
		अगर (ret < 0)
			वापस ret;

		/* disable beacon filtering */
		ret = wl1271_acx_beacon_filter_opt(wl, wlvअगर, false);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (test_and_clear_bit(WLVIF_FLAG_CS_PROGRESS, &wlvअगर->flags)) अणु
		काष्ठा ieee80211_vअगर *vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);

		wl12xx_cmd_stop_channel_चयन(wl, wlvअगर);
		ieee80211_chचयन_करोne(vअगर, false);
		cancel_delayed_work(&wlvअगर->channel_चयन_work);
	पूर्ण

	/* invalidate keep-alive ढाँचा */
	wl1271_acx_keep_alive_config(wl, wlvअगर,
				     wlvअगर->sta.klv_ढाँचा_id,
				     ACX_KEEP_ALIVE_TPL_INVALID);

	वापस 0;
पूर्ण

अटल व्योम wl1271_set_band_rate(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	wlvअगर->basic_rate_set = wlvअगर->bitrate_masks[wlvअगर->band];
	wlvअगर->rate_set = wlvअगर->basic_rate_set;
पूर्ण

अटल व्योम wl1271_sta_handle_idle(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				   bool idle)
अणु
	bool cur_idle = !test_bit(WLVIF_FLAG_ACTIVE, &wlvअगर->flags);

	अगर (idle == cur_idle)
		वापस;

	अगर (idle) अणु
		clear_bit(WLVIF_FLAG_ACTIVE, &wlvअगर->flags);
	पूर्ण अन्यथा अणु
		/* The current firmware only supports sched_scan in idle */
		अगर (wl->sched_vअगर == wlvअगर)
			wl->ops->sched_scan_stop(wl, wlvअगर);

		set_bit(WLVIF_FLAG_ACTIVE, &wlvअगर->flags);
	पूर्ण
पूर्ण

अटल पूर्णांक wl12xx_config_vअगर(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			     काष्ठा ieee80211_conf *conf, u32 changed)
अणु
	पूर्णांक ret;

	अगर (wlcore_is_p2p_mgmt(wlvअगर))
		वापस 0;

	अगर (conf->घातer_level != wlvअगर->घातer_level) अणु
		ret = wl1271_acx_tx_घातer(wl, wlvअगर, conf->घातer_level);
		अगर (ret < 0)
			वापस ret;

		wlvअगर->घातer_level = conf->घातer_level;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wl1271_op_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर;
	काष्ठा ieee80211_conf *conf = &hw->conf;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_MAC80211, "mac80211 config psm %s power %d %s"
		     " changed 0x%x",
		     conf->flags & IEEE80211_CONF_PS ? "on" : "off",
		     conf->घातer_level,
		     conf->flags & IEEE80211_CONF_IDLE ? "idle" : "in use",
			 changed);

	mutex_lock(&wl->mutex);

	अगर (changed & IEEE80211_CONF_CHANGE_POWER)
		wl->घातer_level = conf->घातer_level;

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	/* configure each पूर्णांकerface */
	wl12xx_क्रम_each_wlvअगर(wl, wlvअगर) अणु
		ret = wl12xx_config_vअगर(wl, wlvअगर, conf, changed);
		अगर (ret < 0)
			जाओ out_sleep;
	पूर्ण

out_sleep:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

out:
	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

काष्ठा wl1271_filter_params अणु
	bool enabled;
	पूर्णांक mc_list_length;
	u8 mc_list[ACX_MC_ADDRESS_GROUP_MAX][ETH_ALEN];
पूर्ण;

अटल u64 wl1271_op_prepare_multicast(काष्ठा ieee80211_hw *hw,
				       काष्ठा netdev_hw_addr_list *mc_list)
अणु
	काष्ठा wl1271_filter_params *fp;
	काष्ठा netdev_hw_addr *ha;

	fp = kzalloc(माप(*fp), GFP_ATOMIC);
	अगर (!fp) अणु
		wl1271_error("Out of memory setting filters.");
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

#घोषणा WL1271_SUPPORTED_FILTERS (FIF_ALLMULTI | \
				  FIF_FCSFAIL | \
				  FIF_BCN_PRBRESP_PROMISC | \
				  FIF_CONTROL | \
				  FIF_OTHER_BSS)

अटल व्योम wl1271_op_configure_filter(काष्ठा ieee80211_hw *hw,
				       अचिन्हित पूर्णांक changed,
				       अचिन्हित पूर्णांक *total, u64 multicast)
अणु
	काष्ठा wl1271_filter_params *fp = (व्योम *)(अचिन्हित दीर्घ)multicast;
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर;

	पूर्णांक ret;

	wl1271_debug(DEBUG_MAC80211, "mac80211 configure filter changed %x"
		     " total %x", changed, *total);

	mutex_lock(&wl->mutex);

	*total &= WL1271_SUPPORTED_FILTERS;
	changed &= WL1271_SUPPORTED_FILTERS;

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	wl12xx_क्रम_each_wlvअगर(wl, wlvअगर) अणु
		अगर (wlcore_is_p2p_mgmt(wlvअगर))
			जारी;

		अगर (wlvअगर->bss_type != BSS_TYPE_AP_BSS) अणु
			अगर (*total & FIF_ALLMULTI)
				ret = wl1271_acx_group_address_tbl(wl, wlvअगर,
								   false,
								   शून्य, 0);
			अन्यथा अगर (fp)
				ret = wl1271_acx_group_address_tbl(wl, wlvअगर,
							fp->enabled,
							fp->mc_list,
							fp->mc_list_length);
			अगर (ret < 0)
				जाओ out_sleep;
		पूर्ण

		/*
		 * If पूर्णांकerface in AP mode and created with allmulticast then disable
		 * the firmware filters so that all multicast packets are passed
		 * This is mandatory क्रम MDNS based discovery protocols 
		 */
 		अगर (wlvअगर->bss_type == BSS_TYPE_AP_BSS) अणु
 			अगर (*total & FIF_ALLMULTI) अणु
				ret = wl1271_acx_group_address_tbl(wl, wlvअगर,
							false,
							शून्य, 0);
				अगर (ret < 0)
					जाओ out_sleep;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * the fw करोesn't provide an api to configure the filters. instead,
	 * the filters configuration is based on the active roles / ROC
	 * state.
	 */

out_sleep:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

out:
	mutex_unlock(&wl->mutex);
	kमुक्त(fp);
पूर्ण

अटल पूर्णांक wl1271_record_ap_key(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				u8 id, u8 key_type, u8 key_size,
				स्थिर u8 *key, u8 hlid, u32 tx_seq_32,
				u16 tx_seq_16, bool is_pairwise)
अणु
	काष्ठा wl1271_ap_key *ap_key;
	पूर्णांक i;

	wl1271_debug(DEBUG_CRYPT, "record ap key id %d", (पूर्णांक)id);

	अगर (key_size > MAX_KEY_SIZE)
		वापस -EINVAL;

	/*
	 * Find next मुक्त entry in ap_keys. Also check we are not replacing
	 * an existing key.
	 */
	क्रम (i = 0; i < MAX_NUM_KEYS; i++) अणु
		अगर (wlvअगर->ap.recorded_keys[i] == शून्य)
			अवरोध;

		अगर (wlvअगर->ap.recorded_keys[i]->id == id) अणु
			wl1271_warning("trying to record key replacement");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (i == MAX_NUM_KEYS)
		वापस -EBUSY;

	ap_key = kzalloc(माप(*ap_key), GFP_KERNEL);
	अगर (!ap_key)
		वापस -ENOMEM;

	ap_key->id = id;
	ap_key->key_type = key_type;
	ap_key->key_size = key_size;
	स_नकल(ap_key->key, key, key_size);
	ap_key->hlid = hlid;
	ap_key->tx_seq_32 = tx_seq_32;
	ap_key->tx_seq_16 = tx_seq_16;
	ap_key->is_pairwise = is_pairwise;

	wlvअगर->ap.recorded_keys[i] = ap_key;
	वापस 0;
पूर्ण

अटल व्योम wl1271_मुक्त_ap_keys(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_NUM_KEYS; i++) अणु
		kमुक्त(wlvअगर->ap.recorded_keys[i]);
		wlvअगर->ap.recorded_keys[i] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक wl1271_ap_init_hwenc(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा wl1271_ap_key *key;
	bool wep_key_added = false;

	क्रम (i = 0; i < MAX_NUM_KEYS; i++) अणु
		u8 hlid;
		अगर (wlvअगर->ap.recorded_keys[i] == शून्य)
			अवरोध;

		key = wlvअगर->ap.recorded_keys[i];
		hlid = key->hlid;
		अगर (hlid == WL12XX_INVALID_LINK_ID)
			hlid = wlvअगर->ap.bcast_hlid;

		ret = wl1271_cmd_set_ap_key(wl, wlvअगर, KEY_ADD_OR_REPLACE,
					    key->id, key->key_type,
					    key->key_size, key->key,
					    hlid, key->tx_seq_32,
					    key->tx_seq_16, key->is_pairwise);
		अगर (ret < 0)
			जाओ out;

		अगर (key->key_type == KEY_WEP)
			wep_key_added = true;
	पूर्ण

	अगर (wep_key_added) अणु
		ret = wl12xx_cmd_set_शेष_wep_key(wl, wlvअगर->शेष_key,
						     wlvअगर->ap.bcast_hlid);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

out:
	wl1271_मुक्त_ap_keys(wl, wlvअगर);
	वापस ret;
पूर्ण

अटल पूर्णांक wl1271_set_key(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
		       u16 action, u8 id, u8 key_type,
		       u8 key_size, स्थिर u8 *key, u32 tx_seq_32,
		       u16 tx_seq_16, काष्ठा ieee80211_sta *sta,
		       bool is_pairwise)
अणु
	पूर्णांक ret;
	bool is_ap = (wlvअगर->bss_type == BSS_TYPE_AP_BSS);

	अगर (is_ap) अणु
		काष्ठा wl1271_station *wl_sta;
		u8 hlid;

		अगर (sta) अणु
			wl_sta = (काष्ठा wl1271_station *)sta->drv_priv;
			hlid = wl_sta->hlid;
		पूर्ण अन्यथा अणु
			hlid = wlvअगर->ap.bcast_hlid;
		पूर्ण

		अगर (!test_bit(WLVIF_FLAG_AP_STARTED, &wlvअगर->flags)) अणु
			/*
			 * We करो not support removing keys after AP shutकरोwn.
			 * Pretend we करो to make mac80211 happy.
			 */
			अगर (action != KEY_ADD_OR_REPLACE)
				वापस 0;

			ret = wl1271_record_ap_key(wl, wlvअगर, id,
					     key_type, key_size,
					     key, hlid, tx_seq_32,
					     tx_seq_16, is_pairwise);
		पूर्ण अन्यथा अणु
			ret = wl1271_cmd_set_ap_key(wl, wlvअगर, action,
					     id, key_type, key_size,
					     key, hlid, tx_seq_32,
					     tx_seq_16, is_pairwise);
		पूर्ण

		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		स्थिर u8 *addr;
		अटल स्थिर u8 bcast_addr[ETH_ALEN] = अणु
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff
		पूर्ण;

		addr = sta ? sta->addr : bcast_addr;

		अगर (is_zero_ether_addr(addr)) अणु
			/* We करोnt support TX only encryption */
			वापस -EOPNOTSUPP;
		पूर्ण

		/* The wl1271 करोes not allow to हटाओ unicast keys - they
		   will be cleared स्वतःmatically on next CMD_JOIN. Ignore the
		   request silently, as we करोnt want the mac80211 to emit
		   an error message. */
		अगर (action == KEY_REMOVE && !is_broadcast_ether_addr(addr))
			वापस 0;

		/* करोn't हटाओ key अगर hlid was alपढ़ोy deleted */
		अगर (action == KEY_REMOVE &&
		    wlvअगर->sta.hlid == WL12XX_INVALID_LINK_ID)
			वापस 0;

		ret = wl1271_cmd_set_sta_key(wl, wlvअगर, action,
					     id, key_type, key_size,
					     key, addr, tx_seq_32,
					     tx_seq_16);
		अगर (ret < 0)
			वापस ret;

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wlcore_op_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_sta *sta,
			     काष्ठा ieee80211_key_conf *key_conf)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	पूर्णांक ret;
	bool might_change_spare =
		key_conf->cipher == WL1271_CIPHER_SUITE_GEM ||
		key_conf->cipher == WLAN_CIPHER_SUITE_TKIP;

	अगर (might_change_spare) अणु
		/*
		 * stop the queues and flush to ensure the next packets are
		 * in sync with FW spare block accounting
		 */
		wlcore_stop_queues(wl, WLCORE_QUEUE_STOP_REASON_SPARE_BLK);
		wl1271_tx_flush(wl);
	पूर्ण

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON)) अणु
		ret = -EAGAIN;
		जाओ out_wake_queues;
	पूर्ण

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out_wake_queues;
	पूर्ण

	ret = wlcore_hw_set_key(wl, cmd, vअगर, sta, key_conf);

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

out_wake_queues:
	अगर (might_change_spare)
		wlcore_wake_queues(wl, WLCORE_QUEUE_STOP_REASON_SPARE_BLK);

	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

पूर्णांक wlcore_set_key(काष्ठा wl1271 *wl, क्रमागत set_key_cmd cmd,
		   काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_sta *sta,
		   काष्ठा ieee80211_key_conf *key_conf)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	पूर्णांक ret;
	u32 tx_seq_32 = 0;
	u16 tx_seq_16 = 0;
	u8 key_type;
	u8 hlid;
	bool is_pairwise;

	wl1271_debug(DEBUG_MAC80211, "mac80211 set key");

	wl1271_debug(DEBUG_CRYPT, "CMD: 0x%x sta: %p", cmd, sta);
	wl1271_debug(DEBUG_CRYPT, "Key: algo:0x%x, id:%d, len:%d flags 0x%x",
		     key_conf->cipher, key_conf->keyidx,
		     key_conf->keylen, key_conf->flags);
	wl1271_dump(DEBUG_CRYPT, "KEY: ", key_conf->key, key_conf->keylen);

	अगर (wlvअगर->bss_type == BSS_TYPE_AP_BSS)
		अगर (sta) अणु
			काष्ठा wl1271_station *wl_sta = (व्योम *)sta->drv_priv;
			hlid = wl_sta->hlid;
		पूर्ण अन्यथा अणु
			hlid = wlvअगर->ap.bcast_hlid;
		पूर्ण
	अन्यथा
		hlid = wlvअगर->sta.hlid;

	अगर (hlid != WL12XX_INVALID_LINK_ID) अणु
		u64 tx_seq = wl->links[hlid].total_मुक्तd_pkts;
		tx_seq_32 = WL1271_TX_SECURITY_HI32(tx_seq);
		tx_seq_16 = WL1271_TX_SECURITY_LO16(tx_seq);
	पूर्ण

	चयन (key_conf->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		key_type = KEY_WEP;

		key_conf->hw_key_idx = key_conf->keyidx;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		key_type = KEY_TKIP;
		key_conf->hw_key_idx = key_conf->keyidx;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		key_type = KEY_AES;
		key_conf->flags |= IEEE80211_KEY_FLAG_PUT_IV_SPACE;
		अवरोध;
	हाल WL1271_CIPHER_SUITE_GEM:
		key_type = KEY_GEM;
		अवरोध;
	शेष:
		wl1271_error("Unknown key algo 0x%x", key_conf->cipher);

		वापस -EOPNOTSUPP;
	पूर्ण

	is_pairwise = key_conf->flags & IEEE80211_KEY_FLAG_PAIRWISE;

	चयन (cmd) अणु
	हाल SET_KEY:
		ret = wl1271_set_key(wl, wlvअगर, KEY_ADD_OR_REPLACE,
				 key_conf->keyidx, key_type,
				 key_conf->keylen, key_conf->key,
				 tx_seq_32, tx_seq_16, sta, is_pairwise);
		अगर (ret < 0) अणु
			wl1271_error("Could not add or replace key");
			वापस ret;
		पूर्ण

		/*
		 * reconfiguring arp response अगर the unicast (or common)
		 * encryption key type was changed
		 */
		अगर (wlvअगर->bss_type == BSS_TYPE_STA_BSS &&
		    (sta || key_type == KEY_WEP) &&
		    wlvअगर->encryption_type != key_type) अणु
			wlvअगर->encryption_type = key_type;
			ret = wl1271_cmd_build_arp_rsp(wl, wlvअगर);
			अगर (ret < 0) अणु
				wl1271_warning("build arp rsp failed: %d", ret);
				वापस ret;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल DISABLE_KEY:
		ret = wl1271_set_key(wl, wlvअगर, KEY_REMOVE,
				     key_conf->keyidx, key_type,
				     key_conf->keylen, key_conf->key,
				     0, 0, sta, is_pairwise);
		अगर (ret < 0) अणु
			wl1271_error("Could not remove key");
			वापस ret;
		पूर्ण
		अवरोध;

	शेष:
		wl1271_error("Unsupported key cmd 0x%x", cmd);
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_set_key);

अटल व्योम wl1271_op_set_शेष_key_idx(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_vअगर *vअगर,
					  पूर्णांक key_idx)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	पूर्णांक ret;

	wl1271_debug(DEBUG_MAC80211, "mac80211 set default key idx %d",
		     key_idx);

	/* we करोn't handle unsetting of शेष key */
	अगर (key_idx == -1)
		वापस;

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON)) अणु
		ret = -EAGAIN;
		जाओ out_unlock;
	पूर्ण

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out_unlock;
	पूर्ण

	wlvअगर->शेष_key = key_idx;

	/* the शेष WEP key needs to be configured at least once */
	अगर (wlvअगर->encryption_type == KEY_WEP) अणु
		ret = wl12xx_cmd_set_शेष_wep_key(wl,
				key_idx,
				wlvअगर->sta.hlid);
		अगर (ret < 0)
			जाओ out_sleep;
	पूर्ण

out_sleep:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

out_unlock:
	mutex_unlock(&wl->mutex);
पूर्ण

व्योम wlcore_regकरोमुख्य_config(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	अगर (!(wl->quirks & WLCORE_QUIRK_REGDOMAIN_CONF))
		वापस;

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(wl->dev);
		जाओ out;
	पूर्ण

	ret = wlcore_cmd_regकरोमुख्य_config_locked(wl);
	अगर (ret < 0) अणु
		wl12xx_queue_recovery_work(wl);
		जाओ out;
	पूर्ण

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
पूर्ण

अटल पूर्णांक wl1271_op_hw_scan(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_scan_request *hw_req)
अणु
	काष्ठा cfg80211_scan_request *req = &hw_req->req;
	काष्ठा wl1271 *wl = hw->priv;
	पूर्णांक ret;
	u8 *ssid = शून्य;
	माप_प्रकार len = 0;

	wl1271_debug(DEBUG_MAC80211, "mac80211 hw scan");

	अगर (req->n_ssids) अणु
		ssid = req->ssids[0].ssid;
		len = req->ssids[0].ssid_len;
	पूर्ण

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON)) अणु
		/*
		 * We cannot वापस -EBUSY here because cfg80211 will expect
		 * a call to ieee80211_scan_completed अगर we करो - in this हाल
		 * there won't be any call.
		 */
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	/* fail अगर there is any role in ROC */
	अगर (find_first_bit(wl->roc_map, WL12XX_MAX_ROLES) < WL12XX_MAX_ROLES) अणु
		/* करोn't allow scanning right now */
		ret = -EBUSY;
		जाओ out_sleep;
	पूर्ण

	ret = wlcore_scan(hw->priv, vअगर, ssid, len, req);
out_sleep:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

अटल व्योम wl1271_op_cancel_hw_scan(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	काष्ठा cfg80211_scan_info info = अणु
		.पातed = true,
	पूर्ण;
	पूर्णांक ret;

	wl1271_debug(DEBUG_MAC80211, "mac80211 cancel hw scan");

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	अगर (wl->scan.state == WL1271_SCAN_STATE_IDLE)
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	अगर (wl->scan.state != WL1271_SCAN_STATE_DONE) अणु
		ret = wl->ops->scan_stop(wl, wlvअगर);
		अगर (ret < 0)
			जाओ out_sleep;
	पूर्ण

	/*
	 * Rearm the tx watchकरोg just beक्रमe idling scan. This
	 * prevents just-finished scans from triggering the watchकरोg
	 */
	wl12xx_rearm_tx_watchकरोg_locked(wl);

	wl->scan.state = WL1271_SCAN_STATE_IDLE;
	स_रखो(wl->scan.scanned_ch, 0, माप(wl->scan.scanned_ch));
	wl->scan_wlvअगर = शून्य;
	wl->scan.req = शून्य;
	ieee80211_scan_completed(wl->hw, &info);

out_sleep:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);

	cancel_delayed_work_sync(&wl->scan_complete_work);
पूर्ण

अटल पूर्णांक wl1271_op_sched_scan_start(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा cfg80211_sched_scan_request *req,
				      काष्ठा ieee80211_scan_ies *ies)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	पूर्णांक ret;

	wl1271_debug(DEBUG_MAC80211, "wl1271_op_sched_scan_start");

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON)) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	ret = wl->ops->sched_scan_start(wl, wlvअगर, req, ies);
	अगर (ret < 0)
		जाओ out_sleep;

	wl->sched_vअगर = wlvअगर;

out_sleep:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक wl1271_op_sched_scan_stop(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	पूर्णांक ret;

	wl1271_debug(DEBUG_MAC80211, "wl1271_op_sched_scan_stop");

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	wl->ops->sched_scan_stop(wl, wlvअगर);

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक wl1271_op_set_frag_threshold(काष्ठा ieee80211_hw *hw, u32 value)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	पूर्णांक ret = 0;

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON)) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	ret = wl1271_acx_frag_threshold(wl, value);
	अगर (ret < 0)
		wl1271_warning("wl1271_op_set_frag_threshold failed: %d", ret);

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

out:
	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक wl1271_op_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 value)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर;
	पूर्णांक ret = 0;

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON)) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	wl12xx_क्रम_each_wlvअगर(wl, wlvअगर) अणु
		ret = wl1271_acx_rts_threshold(wl, wlvअगर, value);
		अगर (ret < 0)
			wl1271_warning("set rts threshold failed: %d", ret);
	पूर्ण
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

out:
	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

अटल व्योम wl12xx_हटाओ_ie(काष्ठा sk_buff *skb, u8 eid, पूर्णांक ieoffset)
अणु
	पूर्णांक len;
	स्थिर u8 *next, *end = skb->data + skb->len;
	u8 *ie = (u8 *)cfg80211_find_ie(eid, skb->data + ieoffset,
					skb->len - ieoffset);
	अगर (!ie)
		वापस;
	len = ie[1] + 2;
	next = ie + len;
	स_हटाओ(ie, next, end - next);
	skb_trim(skb, skb->len - len);
पूर्ण

अटल व्योम wl12xx_हटाओ_venकरोr_ie(काष्ठा sk_buff *skb,
					    अचिन्हित पूर्णांक oui, u8 oui_type,
					    पूर्णांक ieoffset)
अणु
	पूर्णांक len;
	स्थिर u8 *next, *end = skb->data + skb->len;
	u8 *ie = (u8 *)cfg80211_find_venकरोr_ie(oui, oui_type,
					       skb->data + ieoffset,
					       skb->len - ieoffset);
	अगर (!ie)
		वापस;
	len = ie[1] + 2;
	next = ie + len;
	स_हटाओ(ie, next, end - next);
	skb_trim(skb, skb->len - len);
पूर्ण

अटल पूर्णांक wl1271_ap_set_probe_resp_पंचांगpl(काष्ठा wl1271 *wl, u32 rates,
					 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ieee80211_proberesp_get(wl->hw, vअगर);
	अगर (!skb)
		वापस -EOPNOTSUPP;

	ret = wl1271_cmd_ढाँचा_set(wl, wlvअगर->role_id,
				      CMD_TEMPL_AP_PROBE_RESPONSE,
				      skb->data,
				      skb->len, 0,
				      rates);
	dev_kमुक्त_skb(skb);

	अगर (ret < 0)
		जाओ out;

	wl1271_debug(DEBUG_AP, "probe response updated");
	set_bit(WLVIF_FLAG_AP_PROBE_RESP_SET, &wlvअगर->flags);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl1271_ap_set_probe_resp_पंचांगpl_legacy(काष्ठा wl1271 *wl,
					     काष्ठा ieee80211_vअगर *vअगर,
					     u8 *probe_rsp_data,
					     माप_प्रकार probe_rsp_len,
					     u32 rates)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	काष्ठा ieee80211_bss_conf *bss_conf = &vअगर->bss_conf;
	u8 probe_rsp_templ[WL1271_CMD_TEMPL_MAX_SIZE];
	पूर्णांक ssid_ie_offset, ie_offset, templ_len;
	स्थिर u8 *ptr;

	/* no need to change probe response अगर the SSID is set correctly */
	अगर (wlvअगर->ssid_len > 0)
		वापस wl1271_cmd_ढाँचा_set(wl, wlvअगर->role_id,
					       CMD_TEMPL_AP_PROBE_RESPONSE,
					       probe_rsp_data,
					       probe_rsp_len, 0,
					       rates);

	अगर (probe_rsp_len + bss_conf->ssid_len > WL1271_CMD_TEMPL_MAX_SIZE) अणु
		wl1271_error("probe_rsp template too big");
		वापस -EINVAL;
	पूर्ण

	/* start searching from IE offset */
	ie_offset = दुरत्व(काष्ठा ieee80211_mgmt, u.probe_resp.variable);

	ptr = cfg80211_find_ie(WLAN_EID_SSID, probe_rsp_data + ie_offset,
			       probe_rsp_len - ie_offset);
	अगर (!ptr) अणु
		wl1271_error("No SSID in beacon!");
		वापस -EINVAL;
	पूर्ण

	ssid_ie_offset = ptr - probe_rsp_data;
	ptr += (ptr[1] + 2);

	स_नकल(probe_rsp_templ, probe_rsp_data, ssid_ie_offset);

	/* insert SSID from bss_conf */
	probe_rsp_templ[ssid_ie_offset] = WLAN_EID_SSID;
	probe_rsp_templ[ssid_ie_offset + 1] = bss_conf->ssid_len;
	स_नकल(probe_rsp_templ + ssid_ie_offset + 2,
	       bss_conf->ssid, bss_conf->ssid_len);
	templ_len = ssid_ie_offset + 2 + bss_conf->ssid_len;

	स_नकल(probe_rsp_templ + ssid_ie_offset + 2 + bss_conf->ssid_len,
	       ptr, probe_rsp_len - (ptr - probe_rsp_data));
	templ_len += probe_rsp_len - (ptr - probe_rsp_data);

	वापस wl1271_cmd_ढाँचा_set(wl, wlvअगर->role_id,
				       CMD_TEMPL_AP_PROBE_RESPONSE,
				       probe_rsp_templ,
				       templ_len, 0,
				       rates);
पूर्ण

अटल पूर्णांक wl1271_bss_erp_info_changed(काष्ठा wl1271 *wl,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_bss_conf *bss_conf,
				       u32 changed)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	पूर्णांक ret = 0;

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		अगर (bss_conf->use_लघु_slot)
			ret = wl1271_acx_slot(wl, wlvअगर, SLOT_TIME_SHORT);
		अन्यथा
			ret = wl1271_acx_slot(wl, wlvअगर, SLOT_TIME_LONG);
		अगर (ret < 0) अणु
			wl1271_warning("Set slot time failed %d", ret);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_PREAMBLE) अणु
		अगर (bss_conf->use_लघु_preamble)
			wl1271_acx_set_preamble(wl, wlvअगर, ACX_PREAMBLE_SHORT);
		अन्यथा
			wl1271_acx_set_preamble(wl, wlvअगर, ACX_PREAMBLE_LONG);
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_CTS_PROT) अणु
		अगर (bss_conf->use_cts_prot)
			ret = wl1271_acx_cts_protect(wl, wlvअगर,
						     CTSPROTECT_ENABLE);
		अन्यथा
			ret = wl1271_acx_cts_protect(wl, wlvअगर,
						     CTSPROTECT_DISABLE);
		अगर (ret < 0) अणु
			wl1271_warning("Set ctsprotect failed %d", ret);
			जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wlcore_set_beacon_ढाँचा(काष्ठा wl1271 *wl,
				      काष्ठा ieee80211_vअगर *vअगर,
				      bool is_ap)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	काष्ठा ieee80211_hdr *hdr;
	u32 min_rate;
	पूर्णांक ret;
	पूर्णांक ieoffset = दुरत्व(काष्ठा ieee80211_mgmt, u.beacon.variable);
	काष्ठा sk_buff *beacon = ieee80211_beacon_get(wl->hw, vअगर);
	u16 पंचांगpl_id;

	अगर (!beacon) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	wl1271_debug(DEBUG_MASTER, "beacon updated");

	ret = wl1271_ssid_set(wlvअगर, beacon, ieoffset);
	अगर (ret < 0) अणु
		dev_kमुक्त_skb(beacon);
		जाओ out;
	पूर्ण
	min_rate = wl1271_tx_min_rate_get(wl, wlvअगर->basic_rate_set);
	पंचांगpl_id = is_ap ? CMD_TEMPL_AP_BEACON :
		CMD_TEMPL_BEACON;
	ret = wl1271_cmd_ढाँचा_set(wl, wlvअगर->role_id, पंचांगpl_id,
				      beacon->data,
				      beacon->len, 0,
				      min_rate);
	अगर (ret < 0) अणु
		dev_kमुक्त_skb(beacon);
		जाओ out;
	पूर्ण

	wlvअगर->wmm_enabled =
		cfg80211_find_venकरोr_ie(WLAN_OUI_MICROSOFT,
					WLAN_OUI_TYPE_MICROSOFT_WMM,
					beacon->data + ieoffset,
					beacon->len - ieoffset);

	/*
	 * In हाल we alपढ़ोy have a probe-resp beacon set explicitly
	 * by usermode, करोn't use the beacon data.
	 */
	अगर (test_bit(WLVIF_FLAG_AP_PROBE_RESP_SET, &wlvअगर->flags))
		जाओ end_bcn;

	/* हटाओ TIM ie from probe response */
	wl12xx_हटाओ_ie(beacon, WLAN_EID_TIM, ieoffset);

	/*
	 * हटाओ p2p ie from probe response.
	 * the fw reponds to probe requests that करोn't include
	 * the p2p ie. probe requests with p2p ie will be passed,
	 * and will be responded by the supplicant (the spec
	 * क्रमbids including the p2p ie when responding to probe
	 * requests that didn't include it).
	 */
	wl12xx_हटाओ_venकरोr_ie(beacon, WLAN_OUI_WFA,
				WLAN_OUI_TYPE_WFA_P2P, ieoffset);

	hdr = (काष्ठा ieee80211_hdr *) beacon->data;
	hdr->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					 IEEE80211_STYPE_PROBE_RESP);
	अगर (is_ap)
		ret = wl1271_ap_set_probe_resp_पंचांगpl_legacy(wl, vअगर,
							   beacon->data,
							   beacon->len,
							   min_rate);
	अन्यथा
		ret = wl1271_cmd_ढाँचा_set(wl, wlvअगर->role_id,
					      CMD_TEMPL_PROBE_RESPONSE,
					      beacon->data,
					      beacon->len, 0,
					      min_rate);
end_bcn:
	dev_kमुक्त_skb(beacon);
	अगर (ret < 0)
		जाओ out;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl1271_bss_beacon_info_changed(काष्ठा wl1271 *wl,
					  काष्ठा ieee80211_vअगर *vअगर,
					  काष्ठा ieee80211_bss_conf *bss_conf,
					  u32 changed)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	bool is_ap = (wlvअगर->bss_type == BSS_TYPE_AP_BSS);
	पूर्णांक ret = 0;

	अगर (changed & BSS_CHANGED_BEACON_INT) अणु
		wl1271_debug(DEBUG_MASTER, "beacon interval updated: %d",
			bss_conf->beacon_पूर्णांक);

		wlvअगर->beacon_पूर्णांक = bss_conf->beacon_पूर्णांक;
	पूर्ण

	अगर ((changed & BSS_CHANGED_AP_PROBE_RESP) && is_ap) अणु
		u32 rate = wl1271_tx_min_rate_get(wl, wlvअगर->basic_rate_set);

		wl1271_ap_set_probe_resp_पंचांगpl(wl, rate, vअगर);
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON) अणु
		ret = wlcore_set_beacon_ढाँचा(wl, vअगर, is_ap);
		अगर (ret < 0)
			जाओ out;

		अगर (test_and_clear_bit(WLVIF_FLAG_BEACON_DISABLED,
				       &wlvअगर->flags)) अणु
			ret = wlcore_hw_dfs_master_restart(wl, wlvअगर);
			अगर (ret < 0)
				जाओ out;
		पूर्ण
	पूर्ण
out:
	अगर (ret != 0)
		wl1271_error("beacon info change failed: %d", ret);
	वापस ret;
पूर्ण

/* AP mode changes */
अटल व्योम wl1271_bss_info_changed_ap(काष्ठा wl1271 *wl,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_bss_conf *bss_conf,
				       u32 changed)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	पूर्णांक ret = 0;

	अगर (changed & BSS_CHANGED_BASIC_RATES) अणु
		u32 rates = bss_conf->basic_rates;

		wlvअगर->basic_rate_set = wl1271_tx_enabled_rates_get(wl, rates,
								 wlvअगर->band);
		wlvअगर->basic_rate = wl1271_tx_min_rate_get(wl,
							wlvअगर->basic_rate_set);

		ret = wl1271_init_ap_rates(wl, wlvअगर);
		अगर (ret < 0) अणु
			wl1271_error("AP rate policy change failed %d", ret);
			जाओ out;
		पूर्ण

		ret = wl1271_ap_init_ढाँचाs(wl, vअगर);
		अगर (ret < 0)
			जाओ out;

		/* No need to set probe resp ढाँचा क्रम mesh */
		अगर (!ieee80211_vअगर_is_mesh(vअगर)) अणु
			ret = wl1271_ap_set_probe_resp_पंचांगpl(wl,
							    wlvअगर->basic_rate,
							    vअगर);
			अगर (ret < 0)
				जाओ out;
		पूर्ण

		ret = wlcore_set_beacon_ढाँचा(wl, vअगर, true);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	ret = wl1271_bss_beacon_info_changed(wl, vअगर, bss_conf, changed);
	अगर (ret < 0)
		जाओ out;

	अगर (changed & BSS_CHANGED_BEACON_ENABLED) अणु
		अगर (bss_conf->enable_beacon) अणु
			अगर (!test_bit(WLVIF_FLAG_AP_STARTED, &wlvअगर->flags)) अणु
				ret = wl12xx_cmd_role_start_ap(wl, wlvअगर);
				अगर (ret < 0)
					जाओ out;

				ret = wl1271_ap_init_hwenc(wl, wlvअगर);
				अगर (ret < 0)
					जाओ out;

				set_bit(WLVIF_FLAG_AP_STARTED, &wlvअगर->flags);
				wl1271_debug(DEBUG_AP, "started AP");
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (test_bit(WLVIF_FLAG_AP_STARTED, &wlvअगर->flags)) अणु
				/*
				 * AP might be in ROC in हाल we have just
				 * sent auth reply. handle it.
				 */
				अगर (test_bit(wlvअगर->role_id, wl->roc_map))
					wl12xx_croc(wl, wlvअगर->role_id);

				ret = wl12xx_cmd_role_stop_ap(wl, wlvअगर);
				अगर (ret < 0)
					जाओ out;

				clear_bit(WLVIF_FLAG_AP_STARTED, &wlvअगर->flags);
				clear_bit(WLVIF_FLAG_AP_PROBE_RESP_SET,
					  &wlvअगर->flags);
				wl1271_debug(DEBUG_AP, "stopped AP");
			पूर्ण
		पूर्ण
	पूर्ण

	ret = wl1271_bss_erp_info_changed(wl, vअगर, bss_conf, changed);
	अगर (ret < 0)
		जाओ out;

	/* Handle HT inक्रमmation change */
	अगर ((changed & BSS_CHANGED_HT) &&
	    (bss_conf->chandef.width != NL80211_CHAN_WIDTH_20_NOHT)) अणु
		ret = wl1271_acx_set_ht_inक्रमmation(wl, wlvअगर,
					bss_conf->ht_operation_mode);
		अगर (ret < 0) अणु
			wl1271_warning("Set ht information failed %d", ret);
			जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस;
पूर्ण

अटल पूर्णांक wlcore_set_bssid(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			    काष्ठा ieee80211_bss_conf *bss_conf,
			    u32 sta_rate_set)
अणु
	u32 rates;
	पूर्णांक ret;

	wl1271_debug(DEBUG_MAC80211,
	     "changed_bssid: %pM, aid: %d, bcn_int: %d, brates: 0x%x sta_rate_set: 0x%x",
	     bss_conf->bssid, bss_conf->aid,
	     bss_conf->beacon_पूर्णांक,
	     bss_conf->basic_rates, sta_rate_set);

	wlvअगर->beacon_पूर्णांक = bss_conf->beacon_पूर्णांक;
	rates = bss_conf->basic_rates;
	wlvअगर->basic_rate_set =
		wl1271_tx_enabled_rates_get(wl, rates,
					    wlvअगर->band);
	wlvअगर->basic_rate =
		wl1271_tx_min_rate_get(wl,
				       wlvअगर->basic_rate_set);

	अगर (sta_rate_set)
		wlvअगर->rate_set =
			wl1271_tx_enabled_rates_get(wl,
						sta_rate_set,
						wlvअगर->band);

	/* we only support sched_scan जबतक not connected */
	अगर (wl->sched_vअगर == wlvअगर)
		wl->ops->sched_scan_stop(wl, wlvअगर);

	ret = wl1271_acx_sta_rate_policies(wl, wlvअगर);
	अगर (ret < 0)
		वापस ret;

	ret = wl12xx_cmd_build_null_data(wl, wlvअगर);
	अगर (ret < 0)
		वापस ret;

	ret = wl1271_build_qos_null_data(wl, wl12xx_wlvअगर_to_vअगर(wlvअगर));
	अगर (ret < 0)
		वापस ret;

	wlcore_set_ssid(wl, wlvअगर);

	set_bit(WLVIF_FLAG_IN_USE, &wlvअगर->flags);

	वापस 0;
पूर्ण

अटल पूर्णांक wlcore_clear_bssid(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	पूर्णांक ret;

	/* revert back to minimum rates क्रम the current band */
	wl1271_set_band_rate(wl, wlvअगर);
	wlvअगर->basic_rate = wl1271_tx_min_rate_get(wl, wlvअगर->basic_rate_set);

	ret = wl1271_acx_sta_rate_policies(wl, wlvअगर);
	अगर (ret < 0)
		वापस ret;

	अगर (wlvअगर->bss_type == BSS_TYPE_STA_BSS &&
	    test_bit(WLVIF_FLAG_IN_USE, &wlvअगर->flags)) अणु
		ret = wl12xx_cmd_role_stop_sta(wl, wlvअगर);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	clear_bit(WLVIF_FLAG_IN_USE, &wlvअगर->flags);
	वापस 0;
पूर्ण
/* STA/IBSS mode changes */
अटल व्योम wl1271_bss_info_changed_sta(काष्ठा wl1271 *wl,
					काष्ठा ieee80211_vअगर *vअगर,
					काष्ठा ieee80211_bss_conf *bss_conf,
					u32 changed)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	bool करो_join = false;
	bool is_ibss = (wlvअगर->bss_type == BSS_TYPE_IBSS);
	bool ibss_joined = false;
	u32 sta_rate_set = 0;
	पूर्णांक ret;
	काष्ठा ieee80211_sta *sta;
	bool sta_exists = false;
	काष्ठा ieee80211_sta_ht_cap sta_ht_cap;

	अगर (is_ibss) अणु
		ret = wl1271_bss_beacon_info_changed(wl, vअगर, bss_conf,
						     changed);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	अगर (changed & BSS_CHANGED_IBSS) अणु
		अगर (bss_conf->ibss_joined) अणु
			set_bit(WLVIF_FLAG_IBSS_JOINED, &wlvअगर->flags);
			ibss_joined = true;
		पूर्ण अन्यथा अणु
			wlcore_unset_assoc(wl, wlvअगर);
			wl12xx_cmd_role_stop_sta(wl, wlvअगर);
		पूर्ण
	पूर्ण

	अगर ((changed & BSS_CHANGED_BEACON_INT) && ibss_joined)
		करो_join = true;

	/* Need to update the SSID (क्रम filtering etc) */
	अगर ((changed & BSS_CHANGED_BEACON) && ibss_joined)
		करो_join = true;

	अगर ((changed & BSS_CHANGED_BEACON_ENABLED) && ibss_joined) अणु
		wl1271_debug(DEBUG_ADHOC, "ad-hoc beaconing: %s",
			     bss_conf->enable_beacon ? "enabled" : "disabled");

		करो_join = true;
	पूर्ण

	अगर (changed & BSS_CHANGED_IDLE && !is_ibss)
		wl1271_sta_handle_idle(wl, wlvअगर, bss_conf->idle);

	अगर (changed & BSS_CHANGED_CQM) अणु
		bool enable = false;
		अगर (bss_conf->cqm_rssi_thold)
			enable = true;
		ret = wl1271_acx_rssi_snr_trigger(wl, wlvअगर, enable,
						  bss_conf->cqm_rssi_thold,
						  bss_conf->cqm_rssi_hyst);
		अगर (ret < 0)
			जाओ out;
		wlvअगर->rssi_thold = bss_conf->cqm_rssi_thold;
	पूर्ण

	अगर (changed & (BSS_CHANGED_BSSID | BSS_CHANGED_HT |
		       BSS_CHANGED_ASSOC)) अणु
		rcu_पढ़ो_lock();
		sta = ieee80211_find_sta(vअगर, bss_conf->bssid);
		अगर (sta) अणु
			u8 *rx_mask = sta->ht_cap.mcs.rx_mask;

			/* save the supp_rates of the ap */
			sta_rate_set = sta->supp_rates[wlvअगर->band];
			अगर (sta->ht_cap.ht_supported)
				sta_rate_set |=
					(rx_mask[0] << HW_HT_RATES_OFFSET) |
					(rx_mask[1] << HW_MIMO_RATES_OFFSET);
			sta_ht_cap = sta->ht_cap;
			sta_exists = true;
		पूर्ण

		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (changed & BSS_CHANGED_BSSID) अणु
		अगर (!is_zero_ether_addr(bss_conf->bssid)) अणु
			ret = wlcore_set_bssid(wl, wlvअगर, bss_conf,
					       sta_rate_set);
			अगर (ret < 0)
				जाओ out;

			/* Need to update the BSSID (क्रम filtering etc) */
			करो_join = true;
		पूर्ण अन्यथा अणु
			ret = wlcore_clear_bssid(wl, wlvअगर);
			अगर (ret < 0)
				जाओ out;
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_IBSS) अणु
		wl1271_debug(DEBUG_ADHOC, "ibss_joined: %d",
			     bss_conf->ibss_joined);

		अगर (bss_conf->ibss_joined) अणु
			u32 rates = bss_conf->basic_rates;
			wlvअगर->basic_rate_set =
				wl1271_tx_enabled_rates_get(wl, rates,
							    wlvअगर->band);
			wlvअगर->basic_rate =
				wl1271_tx_min_rate_get(wl,
						       wlvअगर->basic_rate_set);

			/* by शेष, use 11b + OFDM rates */
			wlvअगर->rate_set = CONF_TX_IBSS_DEFAULT_RATES;
			ret = wl1271_acx_sta_rate_policies(wl, wlvअगर);
			अगर (ret < 0)
				जाओ out;
		पूर्ण
	पूर्ण

	अगर ((changed & BSS_CHANGED_BEACON_INFO) && bss_conf->dtim_period) अणु
		/* enable beacon filtering */
		ret = wl1271_acx_beacon_filter_opt(wl, wlvअगर, true);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	ret = wl1271_bss_erp_info_changed(wl, vअगर, bss_conf, changed);
	अगर (ret < 0)
		जाओ out;

	अगर (करो_join) अणु
		ret = wlcore_join(wl, wlvअगर);
		अगर (ret < 0) अणु
			wl1271_warning("cmd join failed %d", ret);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_ASSOC) अणु
		अगर (bss_conf->assoc) अणु
			ret = wlcore_set_assoc(wl, wlvअगर, bss_conf,
					       sta_rate_set);
			अगर (ret < 0)
				जाओ out;

			अगर (test_bit(WLVIF_FLAG_STA_AUTHORIZED, &wlvअगर->flags))
				wl12xx_set_authorized(wl, wlvअगर);
		पूर्ण अन्यथा अणु
			wlcore_unset_assoc(wl, wlvअगर);
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_PS) अणु
		अगर ((bss_conf->ps) &&
		    test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvअगर->flags) &&
		    !test_bit(WLVIF_FLAG_IN_PS, &wlvअगर->flags)) अणु
			पूर्णांक ps_mode;
			अक्षर *ps_mode_str;

			अगर (wl->conf.conn.क्रमced_ps) अणु
				ps_mode = STATION_POWER_SAVE_MODE;
				ps_mode_str = "forced";
			पूर्ण अन्यथा अणु
				ps_mode = STATION_AUTO_PS_MODE;
				ps_mode_str = "auto";
			पूर्ण

			wl1271_debug(DEBUG_PSM, "%s ps enabled", ps_mode_str);

			ret = wl1271_ps_set_mode(wl, wlvअगर, ps_mode);
			अगर (ret < 0)
				wl1271_warning("enter %s ps failed %d",
					       ps_mode_str, ret);
		पूर्ण अन्यथा अगर (!bss_conf->ps &&
			   test_bit(WLVIF_FLAG_IN_PS, &wlvअगर->flags)) अणु
			wl1271_debug(DEBUG_PSM, "auto ps disabled");

			ret = wl1271_ps_set_mode(wl, wlvअगर,
						 STATION_ACTIVE_MODE);
			अगर (ret < 0)
				wl1271_warning("exit auto ps failed %d", ret);
		पूर्ण
	पूर्ण

	/* Handle new association with HT. Do this after join. */
	अगर (sta_exists) अणु
		bool enabled =
			bss_conf->chandef.width != NL80211_CHAN_WIDTH_20_NOHT;

		ret = wlcore_hw_set_peer_cap(wl,
					     &sta_ht_cap,
					     enabled,
					     wlvअगर->rate_set,
					     wlvअगर->sta.hlid);
		अगर (ret < 0) अणु
			wl1271_warning("Set ht cap failed %d", ret);
			जाओ out;

		पूर्ण

		अगर (enabled) अणु
			ret = wl1271_acx_set_ht_inक्रमmation(wl, wlvअगर,
						bss_conf->ht_operation_mode);
			अगर (ret < 0) अणु
				wl1271_warning("Set ht information failed %d",
					       ret);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Handle arp filtering. Done after join. */
	अगर ((changed & BSS_CHANGED_ARP_FILTER) ||
	    (!is_ibss && (changed & BSS_CHANGED_QOS))) अणु
		__be32 addr = bss_conf->arp_addr_list[0];
		wlvअगर->sta.qos = bss_conf->qos;
		WARN_ON(wlvअगर->bss_type != BSS_TYPE_STA_BSS);

		अगर (bss_conf->arp_addr_cnt == 1 && bss_conf->assoc) अणु
			wlvअगर->ip_addr = addr;
			/*
			 * The ढाँचा should have been configured only upon
			 * association. however, it seems that the correct ip
			 * isn't being set (when sending), so we have to
			 * reconfigure the ढाँचा upon every ip change.
			 */
			ret = wl1271_cmd_build_arp_rsp(wl, wlvअगर);
			अगर (ret < 0) अणु
				wl1271_warning("build arp rsp failed: %d", ret);
				जाओ out;
			पूर्ण

			ret = wl1271_acx_arp_ip_filter(wl, wlvअगर,
				(ACX_ARP_FILTER_ARP_FILTERING |
				 ACX_ARP_FILTER_AUTO_ARP),
				addr);
		पूर्ण अन्यथा अणु
			wlvअगर->ip_addr = 0;
			ret = wl1271_acx_arp_ip_filter(wl, wlvअगर, 0, addr);
		पूर्ण

		अगर (ret < 0)
			जाओ out;
	पूर्ण

out:
	वापस;
पूर्ण

अटल व्योम wl1271_op_bss_info_changed(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_bss_conf *bss_conf,
				       u32 changed)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	bool is_ap = (wlvअगर->bss_type == BSS_TYPE_AP_BSS);
	पूर्णांक ret;

	wl1271_debug(DEBUG_MAC80211, "mac80211 bss info role %d changed 0x%x",
		     wlvअगर->role_id, (पूर्णांक)changed);

	/*
	 * make sure to cancel pending disconnections अगर our association
	 * state changed
	 */
	अगर (!is_ap && (changed & BSS_CHANGED_ASSOC))
		cancel_delayed_work_sync(&wlvअगर->connection_loss_work);

	अगर (is_ap && (changed & BSS_CHANGED_BEACON_ENABLED) &&
	    !bss_conf->enable_beacon)
		wl1271_tx_flush(wl);

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	अगर (unlikely(!test_bit(WLVIF_FLAG_INITIALIZED, &wlvअगर->flags)))
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	अगर ((changed & BSS_CHANGED_TXPOWER) &&
	    bss_conf->txघातer != wlvअगर->घातer_level) अणु

		ret = wl1271_acx_tx_घातer(wl, wlvअगर, bss_conf->txघातer);
		अगर (ret < 0)
			जाओ out;

		wlvअगर->घातer_level = bss_conf->txघातer;
	पूर्ण

	अगर (is_ap)
		wl1271_bss_info_changed_ap(wl, vअगर, bss_conf, changed);
	अन्यथा
		wl1271_bss_info_changed_sta(wl, vअगर, bss_conf, changed);

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

out:
	mutex_unlock(&wl->mutex);
पूर्ण

अटल पूर्णांक wlcore_op_add_chanctx(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	wl1271_debug(DEBUG_MAC80211, "mac80211 add chanctx %d (type %d)",
		     ieee80211_frequency_to_channel(ctx->def.chan->center_freq),
		     cfg80211_get_chandef_type(&ctx->def));
	वापस 0;
पूर्ण

अटल व्योम wlcore_op_हटाओ_chanctx(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	wl1271_debug(DEBUG_MAC80211, "mac80211 remove chanctx %d (type %d)",
		     ieee80211_frequency_to_channel(ctx->def.chan->center_freq),
		     cfg80211_get_chandef_type(&ctx->def));
पूर्ण

अटल व्योम wlcore_op_change_chanctx(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_chanctx_conf *ctx,
				     u32 changed)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर;
	पूर्णांक ret;
	पूर्णांक channel = ieee80211_frequency_to_channel(
		ctx->def.chan->center_freq);

	wl1271_debug(DEBUG_MAC80211,
		     "mac80211 change chanctx %d (type %d) changed 0x%x",
		     channel, cfg80211_get_chandef_type(&ctx->def), changed);

	mutex_lock(&wl->mutex);

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	wl12xx_क्रम_each_wlvअगर(wl, wlvअगर) अणु
		काष्ठा ieee80211_vअगर *vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);

		rcu_पढ़ो_lock();
		अगर (rcu_access_poपूर्णांकer(vअगर->chanctx_conf) != ctx) अणु
			rcu_पढ़ो_unlock();
			जारी;
		पूर्ण
		rcu_पढ़ो_unlock();

		/* start radar अगर needed */
		अगर (changed & IEEE80211_CHANCTX_CHANGE_RADAR &&
		    wlvअगर->bss_type == BSS_TYPE_AP_BSS &&
		    ctx->radar_enabled && !wlvअगर->radar_enabled &&
		    ctx->def.chan->dfs_state == NL80211_DFS_USABLE) अणु
			wl1271_debug(DEBUG_MAC80211, "Start radar detection");
			wlcore_hw_set_cac(wl, wlvअगर, true);
			wlvअगर->radar_enabled = true;
		पूर्ण
	पूर्ण

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
पूर्ण

अटल पूर्णांक wlcore_op_assign_vअगर_chanctx(काष्ठा ieee80211_hw *hw,
					काष्ठा ieee80211_vअगर *vअगर,
					काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	पूर्णांक channel = ieee80211_frequency_to_channel(
		ctx->def.chan->center_freq);
	पूर्णांक ret = -EINVAL;

	wl1271_debug(DEBUG_MAC80211,
		     "mac80211 assign chanctx (role %d) %d (type %d) (radar %d dfs_state %d)",
		     wlvअगर->role_id, channel,
		     cfg80211_get_chandef_type(&ctx->def),
		     ctx->radar_enabled, ctx->def.chan->dfs_state);

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	अगर (unlikely(!test_bit(WLVIF_FLAG_INITIALIZED, &wlvअगर->flags)))
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	wlvअगर->band = ctx->def.chan->band;
	wlvअगर->channel = channel;
	wlvअगर->channel_type = cfg80211_get_chandef_type(&ctx->def);

	/* update शेष rates according to the band */
	wl1271_set_band_rate(wl, wlvअगर);

	अगर (ctx->radar_enabled &&
	    ctx->def.chan->dfs_state == NL80211_DFS_USABLE) अणु
		wl1271_debug(DEBUG_MAC80211, "Start radar detection");
		wlcore_hw_set_cac(wl, wlvअगर, true);
		wlvअगर->radar_enabled = true;
	पूर्ण

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);

	वापस 0;
पूर्ण

अटल व्योम wlcore_op_unassign_vअगर_chanctx(काष्ठा ieee80211_hw *hw,
					   काष्ठा ieee80211_vअगर *vअगर,
					   काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	पूर्णांक ret;

	wl1271_debug(DEBUG_MAC80211,
		     "mac80211 unassign chanctx (role %d) %d (type %d)",
		     wlvअगर->role_id,
		     ieee80211_frequency_to_channel(ctx->def.chan->center_freq),
		     cfg80211_get_chandef_type(&ctx->def));

	wl1271_tx_flush(wl);

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	अगर (unlikely(!test_bit(WLVIF_FLAG_INITIALIZED, &wlvअगर->flags)))
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	अगर (wlvअगर->radar_enabled) अणु
		wl1271_debug(DEBUG_MAC80211, "Stop radar detection");
		wlcore_hw_set_cac(wl, wlvअगर, false);
		wlvअगर->radar_enabled = false;
	पूर्ण

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
पूर्ण

अटल पूर्णांक __wlcore_चयन_vअगर_chan(काष्ठा wl1271 *wl,
				    काष्ठा wl12xx_vअगर *wlvअगर,
				    काष्ठा ieee80211_chanctx_conf *new_ctx)
अणु
	पूर्णांक channel = ieee80211_frequency_to_channel(
		new_ctx->def.chan->center_freq);

	wl1271_debug(DEBUG_MAC80211,
		     "switch vif (role %d) %d -> %d chan_type: %d",
		     wlvअगर->role_id, wlvअगर->channel, channel,
		     cfg80211_get_chandef_type(&new_ctx->def));

	अगर (WARN_ON_ONCE(wlvअगर->bss_type != BSS_TYPE_AP_BSS))
		वापस 0;

	WARN_ON(!test_bit(WLVIF_FLAG_BEACON_DISABLED, &wlvअगर->flags));

	अगर (wlvअगर->radar_enabled) अणु
		wl1271_debug(DEBUG_MAC80211, "Stop radar detection");
		wlcore_hw_set_cac(wl, wlvअगर, false);
		wlvअगर->radar_enabled = false;
	पूर्ण

	wlvअगर->band = new_ctx->def.chan->band;
	wlvअगर->channel = channel;
	wlvअगर->channel_type = cfg80211_get_chandef_type(&new_ctx->def);

	/* start radar अगर needed */
	अगर (new_ctx->radar_enabled) अणु
		wl1271_debug(DEBUG_MAC80211, "Start radar detection");
		wlcore_hw_set_cac(wl, wlvअगर, true);
		wlvअगर->radar_enabled = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
wlcore_op_चयन_vअगर_chanctx(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर_chanctx_चयन *vअगरs,
			     पूर्णांक n_vअगरs,
			     क्रमागत ieee80211_chanctx_चयन_mode mode)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	पूर्णांक i, ret;

	wl1271_debug(DEBUG_MAC80211,
		     "mac80211 switch chanctx n_vifs %d mode %d",
		     n_vअगरs, mode);

	mutex_lock(&wl->mutex);

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < n_vअगरs; i++) अणु
		काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगरs[i].vअगर);

		ret = __wlcore_चयन_vअगर_chan(wl, wlvअगर, vअगरs[i].new_ctx);
		अगर (ret)
			जाओ out_sleep;
	पूर्ण
out_sleep:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक wl1271_op_conf_tx(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर, u16 queue,
			     स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	u8 ps_scheme;
	पूर्णांक ret = 0;

	अगर (wlcore_is_p2p_mgmt(wlvअगर))
		वापस 0;

	mutex_lock(&wl->mutex);

	wl1271_debug(DEBUG_MAC80211, "mac80211 conf tx %d", queue);

	अगर (params->uapsd)
		ps_scheme = CONF_PS_SCHEME_UPSD_TRIGGER;
	अन्यथा
		ps_scheme = CONF_PS_SCHEME_LEGACY;

	अगर (!test_bit(WLVIF_FLAG_INITIALIZED, &wlvअगर->flags))
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	/*
	 * the txop is confed in units of 32us by the mac80211,
	 * we need us
	 */
	ret = wl1271_acx_ac_cfg(wl, wlvअगर, wl1271_tx_get_queue(queue),
				params->cw_min, params->cw_max,
				params->aअगरs, params->txop << 5);
	अगर (ret < 0)
		जाओ out_sleep;

	ret = wl1271_acx_tid_cfg(wl, wlvअगर, wl1271_tx_get_queue(queue),
				 CONF_CHANNEL_TYPE_EDCF,
				 wl1271_tx_get_queue(queue),
				 ps_scheme, CONF_ACK_POLICY_LEGACY,
				 0, 0);

out_sleep:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

out:
	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

अटल u64 wl1271_op_get_tsf(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर)
अणु

	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	u64 maस_समय = ULदीर्घ_उच्च;
	पूर्णांक ret;

	wl1271_debug(DEBUG_MAC80211, "mac80211 get tsf");

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	ret = wl12xx_acx_tsf_info(wl, wlvअगर, &maस_समय);
	अगर (ret < 0)
		जाओ out_sleep;

out_sleep:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

out:
	mutex_unlock(&wl->mutex);
	वापस maस_समय;
पूर्ण

अटल पूर्णांक wl1271_op_get_survey(काष्ठा ieee80211_hw *hw, पूर्णांक idx,
				काष्ठा survey_info *survey)
अणु
	काष्ठा ieee80211_conf *conf = &hw->conf;

	अगर (idx != 0)
		वापस -ENOENT;

	survey->channel = conf->chandef.chan;
	survey->filled = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक wl1271_allocate_sta(काष्ठा wl1271 *wl,
			     काष्ठा wl12xx_vअगर *wlvअगर,
			     काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा wl1271_station *wl_sta;
	पूर्णांक ret;


	अगर (wl->active_sta_count >= wl->max_ap_stations) अणु
		wl1271_warning("could not allocate HLID - too much stations");
		वापस -EBUSY;
	पूर्ण

	wl_sta = (काष्ठा wl1271_station *)sta->drv_priv;
	ret = wl12xx_allocate_link(wl, wlvअगर, &wl_sta->hlid);
	अगर (ret < 0) अणु
		wl1271_warning("could not allocate HLID - too many links");
		वापस -EBUSY;
	पूर्ण

	/* use the previous security seq, अगर this is a recovery/resume */
	wl->links[wl_sta->hlid].total_मुक्तd_pkts = wl_sta->total_मुक्तd_pkts;

	set_bit(wl_sta->hlid, wlvअगर->ap.sta_hlid_map);
	स_नकल(wl->links[wl_sta->hlid].addr, sta->addr, ETH_ALEN);
	wl->active_sta_count++;
	वापस 0;
पूर्ण

व्योम wl1271_मुक्त_sta(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर, u8 hlid)
अणु
	अगर (!test_bit(hlid, wlvअगर->ap.sta_hlid_map))
		वापस;

	clear_bit(hlid, wlvअगर->ap.sta_hlid_map);
	__clear_bit(hlid, &wl->ap_ps_map);
	__clear_bit(hlid, &wl->ap_fw_ps_map);

	/*
	 * save the last used PN in the निजी part of iee80211_sta,
	 * in हाल of recovery/suspend
	 */
	wlcore_save_मुक्तd_pkts_addr(wl, wlvअगर, hlid, wl->links[hlid].addr);

	wl12xx_मुक्त_link(wl, wlvअगर, &hlid);
	wl->active_sta_count--;

	/*
	 * rearm the tx watchकरोg when the last STA is मुक्तd - give the FW a
	 * chance to वापस STA-buffered packets beक्रमe complaining.
	 */
	अगर (wl->active_sta_count == 0)
		wl12xx_rearm_tx_watchकरोg_locked(wl);
पूर्ण

अटल पूर्णांक wl12xx_sta_add(काष्ठा wl1271 *wl,
			  काष्ठा wl12xx_vअगर *wlvअगर,
			  काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा wl1271_station *wl_sta;
	पूर्णांक ret = 0;
	u8 hlid;

	wl1271_debug(DEBUG_MAC80211, "mac80211 add sta %d", (पूर्णांक)sta->aid);

	ret = wl1271_allocate_sta(wl, wlvअगर, sta);
	अगर (ret < 0)
		वापस ret;

	wl_sta = (काष्ठा wl1271_station *)sta->drv_priv;
	hlid = wl_sta->hlid;

	ret = wl12xx_cmd_add_peer(wl, wlvअगर, sta, hlid);
	अगर (ret < 0)
		wl1271_मुक्त_sta(wl, wlvअगर, hlid);

	वापस ret;
पूर्ण

अटल पूर्णांक wl12xx_sta_हटाओ(काष्ठा wl1271 *wl,
			     काष्ठा wl12xx_vअगर *wlvअगर,
			     काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा wl1271_station *wl_sta;
	पूर्णांक ret = 0, id;

	wl1271_debug(DEBUG_MAC80211, "mac80211 remove sta %d", (पूर्णांक)sta->aid);

	wl_sta = (काष्ठा wl1271_station *)sta->drv_priv;
	id = wl_sta->hlid;
	अगर (WARN_ON(!test_bit(id, wlvअगर->ap.sta_hlid_map)))
		वापस -EINVAL;

	ret = wl12xx_cmd_हटाओ_peer(wl, wlvअगर, wl_sta->hlid);
	अगर (ret < 0)
		वापस ret;

	wl1271_मुक्त_sta(wl, wlvअगर, wl_sta->hlid);
	वापस ret;
पूर्ण

अटल व्योम wlcore_roc_अगर_possible(काष्ठा wl1271 *wl,
				   काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	अगर (find_first_bit(wl->roc_map,
			   WL12XX_MAX_ROLES) < WL12XX_MAX_ROLES)
		वापस;

	अगर (WARN_ON(wlvअगर->role_id == WL12XX_INVALID_ROLE_ID))
		वापस;

	wl12xx_roc(wl, wlvअगर, wlvअगर->role_id, wlvअगर->band, wlvअगर->channel);
पूर्ण

/*
 * when wl_sta is शून्य, we treat this call as अगर coming from a
 * pending auth reply.
 * wl->mutex must be taken and the FW must be awake when the call
 * takes place.
 */
व्योम wlcore_update_inconn_sta(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			      काष्ठा wl1271_station *wl_sta, bool in_conn)
अणु
	अगर (in_conn) अणु
		अगर (WARN_ON(wl_sta && wl_sta->in_connection))
			वापस;

		अगर (!wlvअगर->ap_pending_auth_reply &&
		    !wlvअगर->inconn_count)
			wlcore_roc_अगर_possible(wl, wlvअगर);

		अगर (wl_sta) अणु
			wl_sta->in_connection = true;
			wlvअगर->inconn_count++;
		पूर्ण अन्यथा अणु
			wlvअगर->ap_pending_auth_reply = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (wl_sta && !wl_sta->in_connection)
			वापस;

		अगर (WARN_ON(!wl_sta && !wlvअगर->ap_pending_auth_reply))
			वापस;

		अगर (WARN_ON(wl_sta && !wlvअगर->inconn_count))
			वापस;

		अगर (wl_sta) अणु
			wl_sta->in_connection = false;
			wlvअगर->inconn_count--;
		पूर्ण अन्यथा अणु
			wlvअगर->ap_pending_auth_reply = false;
		पूर्ण

		अगर (!wlvअगर->inconn_count && !wlvअगर->ap_pending_auth_reply &&
		    test_bit(wlvअगर->role_id, wl->roc_map))
			wl12xx_croc(wl, wlvअगर->role_id);
	पूर्ण
पूर्ण

अटल पूर्णांक wl12xx_update_sta_state(काष्ठा wl1271 *wl,
				   काष्ठा wl12xx_vअगर *wlvअगर,
				   काष्ठा ieee80211_sta *sta,
				   क्रमागत ieee80211_sta_state old_state,
				   क्रमागत ieee80211_sta_state new_state)
अणु
	काष्ठा wl1271_station *wl_sta;
	bool is_ap = wlvअगर->bss_type == BSS_TYPE_AP_BSS;
	bool is_sta = wlvअगर->bss_type == BSS_TYPE_STA_BSS;
	पूर्णांक ret;

	wl_sta = (काष्ठा wl1271_station *)sta->drv_priv;

	/* Add station (AP mode) */
	अगर (is_ap &&
	    old_state == IEEE80211_STA_NOTEXIST &&
	    new_state == IEEE80211_STA_NONE) अणु
		ret = wl12xx_sta_add(wl, wlvअगर, sta);
		अगर (ret)
			वापस ret;

		wlcore_update_inconn_sta(wl, wlvअगर, wl_sta, true);
	पूर्ण

	/* Remove station (AP mode) */
	अगर (is_ap &&
	    old_state == IEEE80211_STA_NONE &&
	    new_state == IEEE80211_STA_NOTEXIST) अणु
		/* must not fail */
		wl12xx_sta_हटाओ(wl, wlvअगर, sta);

		wlcore_update_inconn_sta(wl, wlvअगर, wl_sta, false);
	पूर्ण

	/* Authorize station (AP mode) */
	अगर (is_ap &&
	    new_state == IEEE80211_STA_AUTHORIZED) अणु
		ret = wl12xx_cmd_set_peer_state(wl, wlvअगर, wl_sta->hlid);
		अगर (ret < 0)
			वापस ret;

		/* reconfigure rates */
		ret = wl12xx_cmd_add_peer(wl, wlvअगर, sta, wl_sta->hlid);
		अगर (ret < 0)
			वापस ret;

		ret = wl1271_acx_set_ht_capabilities(wl, &sta->ht_cap, true,
						     wl_sta->hlid);
		अगर (ret)
			वापस ret;

		wlcore_update_inconn_sta(wl, wlvअगर, wl_sta, false);
	पूर्ण

	/* Authorize station */
	अगर (is_sta &&
	    new_state == IEEE80211_STA_AUTHORIZED) अणु
		set_bit(WLVIF_FLAG_STA_AUTHORIZED, &wlvअगर->flags);
		ret = wl12xx_set_authorized(wl, wlvअगर);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (is_sta &&
	    old_state == IEEE80211_STA_AUTHORIZED &&
	    new_state == IEEE80211_STA_ASSOC) अणु
		clear_bit(WLVIF_FLAG_STA_AUTHORIZED, &wlvअगर->flags);
		clear_bit(WLVIF_FLAG_STA_STATE_SENT, &wlvअगर->flags);
	पूर्ण

	/* save seq number on disassoc (suspend) */
	अगर (is_sta &&
	    old_state == IEEE80211_STA_ASSOC &&
	    new_state == IEEE80211_STA_AUTH) अणु
		wlcore_save_मुक्तd_pkts(wl, wlvअगर, wlvअगर->sta.hlid, sta);
		wlvअगर->total_मुक्तd_pkts = 0;
	पूर्ण

	/* restore seq number on assoc (resume) */
	अगर (is_sta &&
	    old_state == IEEE80211_STA_AUTH &&
	    new_state == IEEE80211_STA_ASSOC) अणु
		wlvअगर->total_मुक्तd_pkts = wl_sta->total_मुक्तd_pkts;
	पूर्ण

	/* clear ROCs on failure or authorization */
	अगर (is_sta &&
	    (new_state == IEEE80211_STA_AUTHORIZED ||
	     new_state == IEEE80211_STA_NOTEXIST)) अणु
		अगर (test_bit(wlvअगर->role_id, wl->roc_map))
			wl12xx_croc(wl, wlvअगर->role_id);
	पूर्ण

	अगर (is_sta &&
	    old_state == IEEE80211_STA_NOTEXIST &&
	    new_state == IEEE80211_STA_NONE) अणु
		अगर (find_first_bit(wl->roc_map,
				   WL12XX_MAX_ROLES) >= WL12XX_MAX_ROLES) अणु
			WARN_ON(wlvअगर->role_id == WL12XX_INVALID_ROLE_ID);
			wl12xx_roc(wl, wlvअगर, wlvअगर->role_id,
				   wlvअगर->band, wlvअगर->channel);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wl12xx_op_sta_state(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा ieee80211_sta *sta,
			       क्रमागत ieee80211_sta_state old_state,
			       क्रमागत ieee80211_sta_state new_state)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	पूर्णांक ret;

	wl1271_debug(DEBUG_MAC80211, "mac80211 sta %d state=%d->%d",
		     sta->aid, old_state, new_state);

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	ret = wl12xx_update_sta_state(wl, wlvअगर, sta, old_state, new_state);

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
	अगर (new_state < old_state)
		वापस 0;
	वापस ret;
पूर्ण

अटल पूर्णांक wl1271_op_ampdu_action(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर,
				  काष्ठा ieee80211_ampdu_params *params)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	पूर्णांक ret;
	u8 hlid, *ba_biपंचांगap;
	काष्ठा ieee80211_sta *sta = params->sta;
	क्रमागत ieee80211_ampdu_mlme_action action = params->action;
	u16 tid = params->tid;
	u16 *ssn = &params->ssn;

	wl1271_debug(DEBUG_MAC80211, "mac80211 ampdu action %d tid %d", action,
		     tid);

	/* sanity check - the fields in FW are only 8bits wide */
	अगर (WARN_ON(tid > 0xFF))
		वापस -ENOTSUPP;

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON)) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	अगर (wlvअगर->bss_type == BSS_TYPE_STA_BSS) अणु
		hlid = wlvअगर->sta.hlid;
	पूर्ण अन्यथा अगर (wlvअगर->bss_type == BSS_TYPE_AP_BSS) अणु
		काष्ठा wl1271_station *wl_sta;

		wl_sta = (काष्ठा wl1271_station *)sta->drv_priv;
		hlid = wl_sta->hlid;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ba_biपंचांगap = &wl->links[hlid].ba_biपंचांगap;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	wl1271_debug(DEBUG_MAC80211, "mac80211 ampdu: Rx tid %d action %d",
		     tid, action);

	चयन (action) अणु
	हाल IEEE80211_AMPDU_RX_START:
		अगर (!wlvअगर->ba_support || !wlvअगर->ba_allowed) अणु
			ret = -ENOTSUPP;
			अवरोध;
		पूर्ण

		अगर (wl->ba_rx_session_count >= wl->ba_rx_session_count_max) अणु
			ret = -EBUSY;
			wl1271_debug(DEBUG_RX, "exceeded max RX BA sessions");
			अवरोध;
		पूर्ण

		अगर (*ba_biपंचांगap & BIT(tid)) अणु
			ret = -EINVAL;
			wl1271_error("cannot enable RX BA session on active "
				     "tid: %d", tid);
			अवरोध;
		पूर्ण

		ret = wl12xx_acx_set_ba_receiver_session(wl, tid, *ssn, true,
				hlid,
				params->buf_size);

		अगर (!ret) अणु
			*ba_biपंचांगap |= BIT(tid);
			wl->ba_rx_session_count++;
		पूर्ण
		अवरोध;

	हाल IEEE80211_AMPDU_RX_STOP:
		अगर (!(*ba_biपंचांगap & BIT(tid))) अणु
			/*
			 * this happens on reconfig - so only output a debug
			 * message क्रम now, and करोn't fail the function.
			 */
			wl1271_debug(DEBUG_MAC80211,
				     "no active RX BA session on tid: %d",
				     tid);
			ret = 0;
			अवरोध;
		पूर्ण

		ret = wl12xx_acx_set_ba_receiver_session(wl, tid, 0, false,
							 hlid, 0);
		अगर (!ret) अणु
			*ba_biपंचांगap &= ~BIT(tid);
			wl->ba_rx_session_count--;
		पूर्ण
		अवरोध;

	/*
	 * The BA initiator session management in FW independently.
	 * Falling अवरोध here on purpose क्रम all TX APDU commands.
	 */
	हाल IEEE80211_AMPDU_TX_START:
	हाल IEEE80211_AMPDU_TX_STOP_CONT:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		ret = -EINVAL;
		अवरोध;

	शेष:
		wl1271_error("Incorrect ampdu action id=%x\n", action);
		ret = -EINVAL;
	पूर्ण

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

out:
	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक wl12xx_set_bitrate_mask(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर,
				   स्थिर काष्ठा cfg80211_bitrate_mask *mask)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	काष्ठा wl1271 *wl = hw->priv;
	पूर्णांक i, ret = 0;

	wl1271_debug(DEBUG_MAC80211, "mac80211 set_bitrate_mask 0x%x 0x%x",
		mask->control[NL80211_BAND_2GHZ].legacy,
		mask->control[NL80211_BAND_5GHZ].legacy);

	mutex_lock(&wl->mutex);

	क्रम (i = 0; i < WLCORE_NUM_BANDS; i++)
		wlvअगर->bitrate_masks[i] =
			wl1271_tx_enabled_rates_get(wl,
						    mask->control[i].legacy,
						    i);

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	अगर (wlvअगर->bss_type == BSS_TYPE_STA_BSS &&
	    !test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvअगर->flags)) अणु

		ret = pm_runसमय_get_sync(wl->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(wl->dev);
			जाओ out;
		पूर्ण

		wl1271_set_band_rate(wl, wlvअगर);
		wlvअगर->basic_rate =
			wl1271_tx_min_rate_get(wl, wlvअगर->basic_rate_set);
		ret = wl1271_acx_sta_rate_policies(wl, wlvअगर);

		pm_runसमय_mark_last_busy(wl->dev);
		pm_runसमय_put_स्वतःsuspend(wl->dev);
	पूर्ण
out:
	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

अटल व्योम wl12xx_op_channel_चयन(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर,
				     काष्ठा ieee80211_channel_चयन *ch_चयन)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	पूर्णांक ret;

	wl1271_debug(DEBUG_MAC80211, "mac80211 channel switch");

	wl1271_tx_flush(wl);

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state == WLCORE_STATE_OFF)) अणु
		अगर (test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvअगर->flags))
			ieee80211_chचयन_करोne(vअगर, false);
		जाओ out;
	पूर्ण अन्यथा अगर (unlikely(wl->state != WLCORE_STATE_ON)) अणु
		जाओ out;
	पूर्ण

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	/* TODO: change mac80211 to pass vअगर as param */

	अगर (test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvअगर->flags)) अणु
		अचिन्हित दीर्घ delay_usec;

		ret = wl->ops->channel_चयन(wl, wlvअगर, ch_चयन);
		अगर (ret)
			जाओ out_sleep;

		set_bit(WLVIF_FLAG_CS_PROGRESS, &wlvअगर->flags);

		/* indicate failure 5 seconds after channel चयन समय */
		delay_usec = ieee80211_tu_to_usec(wlvअगर->beacon_पूर्णांक) *
			ch_चयन->count;
		ieee80211_queue_delayed_work(hw, &wlvअगर->channel_चयन_work,
					     usecs_to_jअगरfies(delay_usec) +
					     msecs_to_jअगरfies(5000));
	पूर्ण

out_sleep:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

out:
	mutex_unlock(&wl->mutex);
पूर्ण

अटल स्थिर व्योम *wlcore_get_beacon_ie(काष्ठा wl1271 *wl,
					काष्ठा wl12xx_vअगर *wlvअगर,
					u8 eid)
अणु
	पूर्णांक ieoffset = दुरत्व(काष्ठा ieee80211_mgmt, u.beacon.variable);
	काष्ठा sk_buff *beacon =
		ieee80211_beacon_get(wl->hw, wl12xx_wlvअगर_to_vअगर(wlvअगर));

	अगर (!beacon)
		वापस शून्य;

	वापस cfg80211_find_ie(eid,
				beacon->data + ieoffset,
				beacon->len - ieoffset);
पूर्ण

अटल पूर्णांक wlcore_get_csa_count(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				u8 *csa_count)
अणु
	स्थिर u8 *ie;
	स्थिर काष्ठा ieee80211_channel_sw_ie *ie_csa;

	ie = wlcore_get_beacon_ie(wl, wlvअगर, WLAN_EID_CHANNEL_SWITCH);
	अगर (!ie)
		वापस -EINVAL;

	ie_csa = (काष्ठा ieee80211_channel_sw_ie *)&ie[2];
	*csa_count = ie_csa->count;

	वापस 0;
पूर्ण

अटल व्योम wlcore_op_channel_चयन_beacon(काष्ठा ieee80211_hw *hw,
					    काष्ठा ieee80211_vअगर *vअगर,
					    काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	काष्ठा ieee80211_channel_चयन ch_चयन = अणु
		.block_tx = true,
		.chandef = *chandef,
	पूर्ण;
	पूर्णांक ret;

	wl1271_debug(DEBUG_MAC80211,
		     "mac80211 channel switch beacon (role %d)",
		     wlvअगर->role_id);

	ret = wlcore_get_csa_count(wl, wlvअगर, &ch_चयन.count);
	अगर (ret < 0) अणु
		wl1271_error("error getting beacon (for CSA counter)");
		वापस;
	पूर्ण

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	ret = wl->ops->channel_चयन(wl, wlvअगर, &ch_चयन);
	अगर (ret)
		जाओ out_sleep;

	set_bit(WLVIF_FLAG_CS_PROGRESS, &wlvअगर->flags);

out_sleep:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
पूर्ण

अटल व्योम wlcore_op_flush(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			    u32 queues, bool drop)
अणु
	काष्ठा wl1271 *wl = hw->priv;

	wl1271_tx_flush(wl);
पूर्ण

अटल पूर्णांक wlcore_op_reमुख्य_on_channel(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_channel *chan,
				       पूर्णांक duration,
				       क्रमागत ieee80211_roc_type type)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	काष्ठा wl1271 *wl = hw->priv;
	पूर्णांक channel, active_roc, ret = 0;

	channel = ieee80211_frequency_to_channel(chan->center_freq);

	wl1271_debug(DEBUG_MAC80211, "mac80211 roc %d (%d)",
		     channel, wlvअगर->role_id);

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	/* वापस EBUSY अगर we can't ROC right now */
	active_roc = find_first_bit(wl->roc_map, WL12XX_MAX_ROLES);
	अगर (wl->roc_vअगर || active_roc < WL12XX_MAX_ROLES) अणु
		wl1271_warning("active roc on role %d", active_roc);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	ret = wl12xx_start_dev(wl, wlvअगर, chan->band, channel);
	अगर (ret < 0)
		जाओ out_sleep;

	wl->roc_vअगर = vअगर;
	ieee80211_queue_delayed_work(hw, &wl->roc_complete_work,
				     msecs_to_jअगरfies(duration));
out_sleep:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक __wlcore_roc_completed(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर;
	पूर्णांक ret;

	/* alपढ़ोy completed */
	अगर (unlikely(!wl->roc_vअगर))
		वापस 0;

	wlvअगर = wl12xx_vअगर_to_data(wl->roc_vअगर);

	अगर (!test_bit(WLVIF_FLAG_INITIALIZED, &wlvअगर->flags))
		वापस -EBUSY;

	ret = wl12xx_stop_dev(wl, wlvअगर);
	अगर (ret < 0)
		वापस ret;

	wl->roc_vअगर = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक wlcore_roc_completed(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	wl1271_debug(DEBUG_MAC80211, "roc complete");

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	ret = __wlcore_roc_completed(wl);

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

अटल व्योम wlcore_roc_complete_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork;
	काष्ठा wl1271 *wl;
	पूर्णांक ret;

	dwork = to_delayed_work(work);
	wl = container_of(dwork, काष्ठा wl1271, roc_complete_work);

	ret = wlcore_roc_completed(wl);
	अगर (!ret)
		ieee80211_reमुख्य_on_channel_expired(wl->hw);
पूर्ण

अटल पूर्णांक wlcore_op_cancel_reमुख्य_on_channel(काष्ठा ieee80211_hw *hw,
					      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wl1271 *wl = hw->priv;

	wl1271_debug(DEBUG_MAC80211, "mac80211 croc");

	/* TODO: per-vअगर */
	wl1271_tx_flush(wl);

	/*
	 * we can't just flush_work here, because it might deadlock
	 * (as we might get called from the same workqueue)
	 */
	cancel_delayed_work_sync(&wl->roc_complete_work);
	wlcore_roc_completed(wl);

	वापस 0;
पूर्ण

अटल व्योम wlcore_op_sta_rc_update(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_sta *sta,
				    u32 changed)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);

	wl1271_debug(DEBUG_MAC80211, "mac80211 sta_rc_update");

	अगर (!(changed & IEEE80211_RC_BW_CHANGED))
		वापस;

	/* this callback is atomic, so schedule a new work */
	wlvअगर->rc_update_bw = sta->bandwidth;
	स_नकल(&wlvअगर->rc_ht_cap, &sta->ht_cap, माप(sta->ht_cap));
	ieee80211_queue_work(hw, &wlvअगर->rc_update_work);
पूर्ण

अटल व्योम wlcore_op_sta_statistics(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर,
				     काष्ठा ieee80211_sta *sta,
				     काष्ठा station_info *sinfo)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	s8 rssi_dbm;
	पूर्णांक ret;

	wl1271_debug(DEBUG_MAC80211, "mac80211 get_rssi");

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out_sleep;
	पूर्ण

	ret = wlcore_acx_average_rssi(wl, wlvअगर, &rssi_dbm);
	अगर (ret < 0)
		जाओ out_sleep;

	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL);
	sinfo->संकेत = rssi_dbm;

out_sleep:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

out:
	mutex_unlock(&wl->mutex);
पूर्ण

अटल u32 wlcore_op_get_expected_throughput(काष्ठा ieee80211_hw *hw,
					     काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा wl1271_station *wl_sta = (काष्ठा wl1271_station *)sta->drv_priv;
	काष्ठा wl1271 *wl = hw->priv;
	u8 hlid = wl_sta->hlid;

	/* वापस in units of Kbps */
	वापस (wl->links[hlid].fw_rate_mbps * 1000);
पूर्ण

अटल bool wl1271_tx_frames_pending(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	bool ret = false;

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	/* packets are considered pending अगर in the TX queue or the FW */
	ret = (wl1271_tx_total_queue_count(wl) > 0) || (wl->tx_frames_cnt > 0);
out:
	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

/* can't be स्थिर, mac80211 ग_लिखोs to this */
अटल काष्ठा ieee80211_rate wl1271_rates[] = अणु
	अणु .bitrate = 10,
	  .hw_value = CONF_HW_BIT_RATE_1MBPS,
	  .hw_value_लघु = CONF_HW_BIT_RATE_1MBPS, पूर्ण,
	अणु .bitrate = 20,
	  .hw_value = CONF_HW_BIT_RATE_2MBPS,
	  .hw_value_लघु = CONF_HW_BIT_RATE_2MBPS,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 55,
	  .hw_value = CONF_HW_BIT_RATE_5_5MBPS,
	  .hw_value_लघु = CONF_HW_BIT_RATE_5_5MBPS,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 110,
	  .hw_value = CONF_HW_BIT_RATE_11MBPS,
	  .hw_value_लघु = CONF_HW_BIT_RATE_11MBPS,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 60,
	  .hw_value = CONF_HW_BIT_RATE_6MBPS,
	  .hw_value_लघु = CONF_HW_BIT_RATE_6MBPS, पूर्ण,
	अणु .bitrate = 90,
	  .hw_value = CONF_HW_BIT_RATE_9MBPS,
	  .hw_value_लघु = CONF_HW_BIT_RATE_9MBPS, पूर्ण,
	अणु .bitrate = 120,
	  .hw_value = CONF_HW_BIT_RATE_12MBPS,
	  .hw_value_लघु = CONF_HW_BIT_RATE_12MBPS, पूर्ण,
	अणु .bitrate = 180,
	  .hw_value = CONF_HW_BIT_RATE_18MBPS,
	  .hw_value_लघु = CONF_HW_BIT_RATE_18MBPS, पूर्ण,
	अणु .bitrate = 240,
	  .hw_value = CONF_HW_BIT_RATE_24MBPS,
	  .hw_value_लघु = CONF_HW_BIT_RATE_24MBPS, पूर्ण,
	अणु .bitrate = 360,
	 .hw_value = CONF_HW_BIT_RATE_36MBPS,
	 .hw_value_लघु = CONF_HW_BIT_RATE_36MBPS, पूर्ण,
	अणु .bitrate = 480,
	  .hw_value = CONF_HW_BIT_RATE_48MBPS,
	  .hw_value_लघु = CONF_HW_BIT_RATE_48MBPS, पूर्ण,
	अणु .bitrate = 540,
	  .hw_value = CONF_HW_BIT_RATE_54MBPS,
	  .hw_value_लघु = CONF_HW_BIT_RATE_54MBPS, पूर्ण,
पूर्ण;

/* can't be स्थिर, mac80211 ग_लिखोs to this */
अटल काष्ठा ieee80211_channel wl1271_channels[] = अणु
	अणु .hw_value = 1, .center_freq = 2412, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 2, .center_freq = 2417, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 3, .center_freq = 2422, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 4, .center_freq = 2427, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 5, .center_freq = 2432, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 6, .center_freq = 2437, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 7, .center_freq = 2442, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 8, .center_freq = 2447, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 9, .center_freq = 2452, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 10, .center_freq = 2457, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 11, .center_freq = 2462, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 12, .center_freq = 2467, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 13, .center_freq = 2472, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 14, .center_freq = 2484, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
पूर्ण;

/* can't be स्थिर, mac80211 ग_लिखोs to this */
अटल काष्ठा ieee80211_supported_band wl1271_band_2ghz = अणु
	.channels = wl1271_channels,
	.n_channels = ARRAY_SIZE(wl1271_channels),
	.bitrates = wl1271_rates,
	.n_bitrates = ARRAY_SIZE(wl1271_rates),
पूर्ण;

/* 5 GHz data rates क्रम WL1273 */
अटल काष्ठा ieee80211_rate wl1271_rates_5ghz[] = अणु
	अणु .bitrate = 60,
	  .hw_value = CONF_HW_BIT_RATE_6MBPS,
	  .hw_value_लघु = CONF_HW_BIT_RATE_6MBPS, पूर्ण,
	अणु .bitrate = 90,
	  .hw_value = CONF_HW_BIT_RATE_9MBPS,
	  .hw_value_लघु = CONF_HW_BIT_RATE_9MBPS, पूर्ण,
	अणु .bitrate = 120,
	  .hw_value = CONF_HW_BIT_RATE_12MBPS,
	  .hw_value_लघु = CONF_HW_BIT_RATE_12MBPS, पूर्ण,
	अणु .bitrate = 180,
	  .hw_value = CONF_HW_BIT_RATE_18MBPS,
	  .hw_value_लघु = CONF_HW_BIT_RATE_18MBPS, पूर्ण,
	अणु .bitrate = 240,
	  .hw_value = CONF_HW_BIT_RATE_24MBPS,
	  .hw_value_लघु = CONF_HW_BIT_RATE_24MBPS, पूर्ण,
	अणु .bitrate = 360,
	 .hw_value = CONF_HW_BIT_RATE_36MBPS,
	 .hw_value_लघु = CONF_HW_BIT_RATE_36MBPS, पूर्ण,
	अणु .bitrate = 480,
	  .hw_value = CONF_HW_BIT_RATE_48MBPS,
	  .hw_value_लघु = CONF_HW_BIT_RATE_48MBPS, पूर्ण,
	अणु .bitrate = 540,
	  .hw_value = CONF_HW_BIT_RATE_54MBPS,
	  .hw_value_लघु = CONF_HW_BIT_RATE_54MBPS, पूर्ण,
पूर्ण;

/* 5 GHz band channels क्रम WL1273 */
अटल काष्ठा ieee80211_channel wl1271_channels_5ghz[] = अणु
	अणु .hw_value = 8, .center_freq = 5040, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 12, .center_freq = 5060, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 16, .center_freq = 5080, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 34, .center_freq = 5170, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 36, .center_freq = 5180, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 38, .center_freq = 5190, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 40, .center_freq = 5200, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 42, .center_freq = 5210, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 44, .center_freq = 5220, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 46, .center_freq = 5230, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 48, .center_freq = 5240, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 52, .center_freq = 5260, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 56, .center_freq = 5280, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 60, .center_freq = 5300, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 64, .center_freq = 5320, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 100, .center_freq = 5500, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 104, .center_freq = 5520, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 108, .center_freq = 5540, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 112, .center_freq = 5560, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 116, .center_freq = 5580, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 120, .center_freq = 5600, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 124, .center_freq = 5620, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 128, .center_freq = 5640, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 132, .center_freq = 5660, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 136, .center_freq = 5680, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 140, .center_freq = 5700, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 149, .center_freq = 5745, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 153, .center_freq = 5765, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 157, .center_freq = 5785, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 161, .center_freq = 5805, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
	अणु .hw_value = 165, .center_freq = 5825, .max_घातer = WLCORE_MAX_TXPWR पूर्ण,
पूर्ण;

अटल काष्ठा ieee80211_supported_band wl1271_band_5ghz = अणु
	.channels = wl1271_channels_5ghz,
	.n_channels = ARRAY_SIZE(wl1271_channels_5ghz),
	.bitrates = wl1271_rates_5ghz,
	.n_bitrates = ARRAY_SIZE(wl1271_rates_5ghz),
पूर्ण;

अटल स्थिर काष्ठा ieee80211_ops wl1271_ops = अणु
	.start = wl1271_op_start,
	.stop = wlcore_op_stop,
	.add_पूर्णांकerface = wl1271_op_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface = wl1271_op_हटाओ_पूर्णांकerface,
	.change_पूर्णांकerface = wl12xx_op_change_पूर्णांकerface,
#अगर_घोषित CONFIG_PM
	.suspend = wl1271_op_suspend,
	.resume = wl1271_op_resume,
#पूर्ण_अगर
	.config = wl1271_op_config,
	.prepare_multicast = wl1271_op_prepare_multicast,
	.configure_filter = wl1271_op_configure_filter,
	.tx = wl1271_op_tx,
	.set_key = wlcore_op_set_key,
	.hw_scan = wl1271_op_hw_scan,
	.cancel_hw_scan = wl1271_op_cancel_hw_scan,
	.sched_scan_start = wl1271_op_sched_scan_start,
	.sched_scan_stop = wl1271_op_sched_scan_stop,
	.bss_info_changed = wl1271_op_bss_info_changed,
	.set_frag_threshold = wl1271_op_set_frag_threshold,
	.set_rts_threshold = wl1271_op_set_rts_threshold,
	.conf_tx = wl1271_op_conf_tx,
	.get_tsf = wl1271_op_get_tsf,
	.get_survey = wl1271_op_get_survey,
	.sta_state = wl12xx_op_sta_state,
	.ampdu_action = wl1271_op_ampdu_action,
	.tx_frames_pending = wl1271_tx_frames_pending,
	.set_bitrate_mask = wl12xx_set_bitrate_mask,
	.set_शेष_unicast_key = wl1271_op_set_शेष_key_idx,
	.channel_चयन = wl12xx_op_channel_चयन,
	.channel_चयन_beacon = wlcore_op_channel_चयन_beacon,
	.flush = wlcore_op_flush,
	.reमुख्य_on_channel = wlcore_op_reमुख्य_on_channel,
	.cancel_reमुख्य_on_channel = wlcore_op_cancel_reमुख्य_on_channel,
	.add_chanctx = wlcore_op_add_chanctx,
	.हटाओ_chanctx = wlcore_op_हटाओ_chanctx,
	.change_chanctx = wlcore_op_change_chanctx,
	.assign_vअगर_chanctx = wlcore_op_assign_vअगर_chanctx,
	.unassign_vअगर_chanctx = wlcore_op_unassign_vअगर_chanctx,
	.चयन_vअगर_chanctx = wlcore_op_चयन_vअगर_chanctx,
	.sta_rc_update = wlcore_op_sta_rc_update,
	.sta_statistics = wlcore_op_sta_statistics,
	.get_expected_throughput = wlcore_op_get_expected_throughput,
	CFG80211_TESTMODE_CMD(wl1271_पंचांग_cmd)
पूर्ण;


u8 wlcore_rate_to_idx(काष्ठा wl1271 *wl, u8 rate, क्रमागत nl80211_band band)
अणु
	u8 idx;

	BUG_ON(band >= 2);

	अगर (unlikely(rate >= wl->hw_tx_rate_tbl_size)) अणु
		wl1271_error("Illegal RX rate from HW: %d", rate);
		वापस 0;
	पूर्ण

	idx = wl->band_rate_to_idx[band][rate];
	अगर (unlikely(idx == CONF_HW_RXTX_RATE_UNSUPPORTED)) अणु
		wl1271_error("Unsupported RX rate from HW: %d", rate);
		वापस 0;
	पूर्ण

	वापस idx;
पूर्ण

अटल व्योम wl12xx_derive_mac_addresses(काष्ठा wl1271 *wl, u32 oui, u32 nic)
अणु
	पूर्णांक i;

	wl1271_debug(DEBUG_PROBE, "base address: oui %06x nic %06x",
		     oui, nic);

	अगर (nic + WLCORE_NUM_MAC_ADDRESSES - wl->num_mac_addr > 0xffffff)
		wl1271_warning("NIC part of the MAC address wraps around!");

	क्रम (i = 0; i < wl->num_mac_addr; i++) अणु
		wl->addresses[i].addr[0] = (u8)(oui >> 16);
		wl->addresses[i].addr[1] = (u8)(oui >> 8);
		wl->addresses[i].addr[2] = (u8) oui;
		wl->addresses[i].addr[3] = (u8)(nic >> 16);
		wl->addresses[i].addr[4] = (u8)(nic >> 8);
		wl->addresses[i].addr[5] = (u8) nic;
		nic++;
	पूर्ण

	/* we may be one address लघु at the most */
	WARN_ON(wl->num_mac_addr + 1 < WLCORE_NUM_MAC_ADDRESSES);

	/*
	 * turn on the LAA bit in the first address and use it as
	 * the last address.
	 */
	अगर (wl->num_mac_addr < WLCORE_NUM_MAC_ADDRESSES) अणु
		पूर्णांक idx = WLCORE_NUM_MAC_ADDRESSES - 1;
		स_नकल(&wl->addresses[idx], &wl->addresses[0],
		       माप(wl->addresses[0]));
		/* LAA bit */
		wl->addresses[idx].addr[0] |= BIT(1);
	पूर्ण

	wl->hw->wiphy->n_addresses = WLCORE_NUM_MAC_ADDRESSES;
	wl->hw->wiphy->addresses = wl->addresses;
पूर्ण

अटल पूर्णांक wl12xx_get_hw_info(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	ret = wlcore_पढ़ो_reg(wl, REG_CHIP_ID_B, &wl->chip.id);
	अगर (ret < 0)
		जाओ out;

	wl->fuse_oui_addr = 0;
	wl->fuse_nic_addr = 0;

	ret = wl->ops->get_pg_ver(wl, &wl->hw_pg_ver);
	अगर (ret < 0)
		जाओ out;

	अगर (wl->ops->get_mac)
		ret = wl->ops->get_mac(wl);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl1271_रेजिस्टर_hw(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;
	u32 oui_addr = 0, nic_addr = 0;
	काष्ठा platक्रमm_device *pdev = wl->pdev;
	काष्ठा wlcore_platdev_data *pdev_data = dev_get_platdata(&pdev->dev);

	अगर (wl->mac80211_रेजिस्टरed)
		वापस 0;

	अगर (wl->nvs_len >= 12) अणु
		/* NOTE: The wl->nvs->nvs element must be first, in
		 * order to simplअगरy the casting, we assume it is at
		 * the beginning of the wl->nvs काष्ठाure.
		 */
		u8 *nvs_ptr = (u8 *)wl->nvs;

		oui_addr =
			(nvs_ptr[11] << 16) + (nvs_ptr[10] << 8) + nvs_ptr[6];
		nic_addr =
			(nvs_ptr[5] << 16) + (nvs_ptr[4] << 8) + nvs_ptr[3];
	पूर्ण

	/* अगर the MAC address is zeroed in the NVS derive from fuse */
	अगर (oui_addr == 0 && nic_addr == 0) अणु
		oui_addr = wl->fuse_oui_addr;
		/* fuse has the BD_ADDR, the WLAN addresses are the next two */
		nic_addr = wl->fuse_nic_addr + 1;
	पूर्ण

	अगर (oui_addr == 0xdeadbe && nic_addr == 0xef0000) अणु
		wl1271_warning("Detected unconfigured mac address in nvs, derive from fuse instead.");
		अगर (!म_भेद(pdev_data->family->name, "wl18xx")) अणु
			wl1271_warning("This default nvs file can be removed from the file system");
		पूर्ण अन्यथा अणु
			wl1271_warning("Your device performance is not optimized.");
			wl1271_warning("Please use the calibrator tool to configure your device.");
		पूर्ण

		अगर (wl->fuse_oui_addr == 0 && wl->fuse_nic_addr == 0) अणु
			wl1271_warning("Fuse mac address is zero. using random mac");
			/* Use TI oui and a अक्रमom nic */
			oui_addr = WLCORE_TI_OUI_ADDRESS;
			nic_addr = get_अक्रमom_पूर्णांक();
		पूर्ण अन्यथा अणु
			oui_addr = wl->fuse_oui_addr;
			/* fuse has the BD_ADDR, the WLAN addresses are the next two */
			nic_addr = wl->fuse_nic_addr + 1;
		पूर्ण
	पूर्ण

	wl12xx_derive_mac_addresses(wl, oui_addr, nic_addr);

	ret = ieee80211_रेजिस्टर_hw(wl->hw);
	अगर (ret < 0) अणु
		wl1271_error("unable to register mac80211 hw: %d", ret);
		जाओ out;
	पूर्ण

	wl->mac80211_रेजिस्टरed = true;

	wl1271_debugfs_init(wl);

	wl1271_notice("loaded");

out:
	वापस ret;
पूर्ण

अटल व्योम wl1271_unरेजिस्टर_hw(काष्ठा wl1271 *wl)
अणु
	अगर (wl->plt)
		wl1271_plt_stop(wl);

	ieee80211_unरेजिस्टर_hw(wl->hw);
	wl->mac80211_रेजिस्टरed = false;

पूर्ण

अटल पूर्णांक wl1271_init_ieee80211(काष्ठा wl1271 *wl)
अणु
	पूर्णांक i;
	अटल स्थिर u32 cipher_suites[] = अणु
		WLAN_CIPHER_SUITE_WEP40,
		WLAN_CIPHER_SUITE_WEP104,
		WLAN_CIPHER_SUITE_TKIP,
		WLAN_CIPHER_SUITE_CCMP,
		WL1271_CIPHER_SUITE_GEM,
	पूर्ण;

	/* The tx descriptor buffer */
	wl->hw->extra_tx_headroom = माप(काष्ठा wl1271_tx_hw_descr);

	अगर (wl->quirks & WLCORE_QUIRK_TKIP_HEADER_SPACE)
		wl->hw->extra_tx_headroom += WL1271_EXTRA_SPACE_TKIP;

	/* unit us */
	/* FIXME: find a proper value */
	wl->hw->max_listen_पूर्णांकerval = wl->conf.conn.max_listen_पूर्णांकerval;

	ieee80211_hw_set(wl->hw, SUPPORT_FAST_XMIT);
	ieee80211_hw_set(wl->hw, CHANCTX_STA_CSA);
	ieee80211_hw_set(wl->hw, SUPPORTS_PER_STA_GTK);
	ieee80211_hw_set(wl->hw, QUEUE_CONTROL);
	ieee80211_hw_set(wl->hw, TX_AMPDU_SETUP_IN_HW);
	ieee80211_hw_set(wl->hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(wl->hw, AP_LINK_PS);
	ieee80211_hw_set(wl->hw, SPECTRUM_MGMT);
	ieee80211_hw_set(wl->hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(wl->hw, CONNECTION_MONITOR);
	ieee80211_hw_set(wl->hw, HAS_RATE_CONTROL);
	ieee80211_hw_set(wl->hw, SUPPORTS_DYNAMIC_PS);
	ieee80211_hw_set(wl->hw, SIGNAL_DBM);
	ieee80211_hw_set(wl->hw, SUPPORTS_PS);
	ieee80211_hw_set(wl->hw, SUPPORTS_TX_FRAG);

	wl->hw->wiphy->cipher_suites = cipher_suites;
	wl->hw->wiphy->n_cipher_suites = ARRAY_SIZE(cipher_suites);

	wl->hw->wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
					 BIT(NL80211_IFTYPE_AP) |
					 BIT(NL80211_IFTYPE_P2P_DEVICE) |
					 BIT(NL80211_IFTYPE_P2P_CLIENT) |
#अगर_घोषित CONFIG_MAC80211_MESH
					 BIT(NL80211_IFTYPE_MESH_POINT) |
#पूर्ण_अगर
					 BIT(NL80211_IFTYPE_P2P_GO);

	wl->hw->wiphy->max_scan_ssids = 1;
	wl->hw->wiphy->max_sched_scan_ssids = 16;
	wl->hw->wiphy->max_match_sets = 16;
	/*
	 * Maximum length of elements in scanning probe request ढाँचाs
	 * should be the maximum length possible क्रम a ढाँचा, without
	 * the IEEE80211 header of the ढाँचा
	 */
	wl->hw->wiphy->max_scan_ie_len = WL1271_CMD_TEMPL_MAX_SIZE -
			माप(काष्ठा ieee80211_header);

	wl->hw->wiphy->max_sched_scan_reqs = 1;
	wl->hw->wiphy->max_sched_scan_ie_len = WL1271_CMD_TEMPL_MAX_SIZE -
		माप(काष्ठा ieee80211_header);

	wl->hw->wiphy->max_reमुख्य_on_channel_duration = 30000;

	wl->hw->wiphy->flags |= WIPHY_FLAG_AP_UAPSD |
				WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL |
				WIPHY_FLAG_HAS_CHANNEL_SWITCH |
				WIPHY_FLAG_IBSS_RSN;

	wl->hw->wiphy->features |= NL80211_FEATURE_AP_SCAN;

	/* make sure all our channels fit in the scanned_ch biपंचांगask */
	BUILD_BUG_ON(ARRAY_SIZE(wl1271_channels) +
		     ARRAY_SIZE(wl1271_channels_5ghz) >
		     WL1271_MAX_CHANNELS);
	/*
	* clear channel flags from the previous usage
	* and restore max_घातer & max_antenna_gain values.
	*/
	क्रम (i = 0; i < ARRAY_SIZE(wl1271_channels); i++) अणु
		wl1271_band_2ghz.channels[i].flags = 0;
		wl1271_band_2ghz.channels[i].max_घातer = WLCORE_MAX_TXPWR;
		wl1271_band_2ghz.channels[i].max_antenna_gain = 0;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(wl1271_channels_5ghz); i++) अणु
		wl1271_band_5ghz.channels[i].flags = 0;
		wl1271_band_5ghz.channels[i].max_घातer = WLCORE_MAX_TXPWR;
		wl1271_band_5ghz.channels[i].max_antenna_gain = 0;
	पूर्ण

	/*
	 * We keep local copies of the band काष्ठाs because we need to
	 * modअगरy them on a per-device basis.
	 */
	स_नकल(&wl->bands[NL80211_BAND_2GHZ], &wl1271_band_2ghz,
	       माप(wl1271_band_2ghz));
	स_नकल(&wl->bands[NL80211_BAND_2GHZ].ht_cap,
	       &wl->ht_cap[NL80211_BAND_2GHZ],
	       माप(*wl->ht_cap));
	स_नकल(&wl->bands[NL80211_BAND_5GHZ], &wl1271_band_5ghz,
	       माप(wl1271_band_5ghz));
	स_नकल(&wl->bands[NL80211_BAND_5GHZ].ht_cap,
	       &wl->ht_cap[NL80211_BAND_5GHZ],
	       माप(*wl->ht_cap));

	wl->hw->wiphy->bands[NL80211_BAND_2GHZ] =
		&wl->bands[NL80211_BAND_2GHZ];
	wl->hw->wiphy->bands[NL80211_BAND_5GHZ] =
		&wl->bands[NL80211_BAND_5GHZ];

	/*
	 * allow 4 queues per mac address we support +
	 * 1 cab queue per mac + one global offchannel Tx queue
	 */
	wl->hw->queues = (NUM_TX_QUEUES + 1) * WLCORE_NUM_MAC_ADDRESSES + 1;

	/* the last queue is the offchannel queue */
	wl->hw->offchannel_tx_hw_queue = wl->hw->queues - 1;
	wl->hw->max_rates = 1;

	wl->hw->wiphy->reg_notअगरier = wl1271_reg_notअगरy;

	/* the FW answers probe-requests in AP-mode */
	wl->hw->wiphy->flags |= WIPHY_FLAG_AP_PROBE_RESP_OFFLOAD;
	wl->hw->wiphy->probe_resp_offload =
		NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS |
		NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS2 |
		NL80211_PROBE_RESP_OFFLOAD_SUPPORT_P2P;

	/* allowed पूर्णांकerface combinations */
	wl->hw->wiphy->अगरace_combinations = wl->अगरace_combinations;
	wl->hw->wiphy->n_अगरace_combinations = wl->n_अगरace_combinations;

	/* रेजिस्टर venकरोr commands */
	wlcore_set_venकरोr_commands(wl->hw->wiphy);

	SET_IEEE80211_DEV(wl->hw, wl->dev);

	wl->hw->sta_data_size = माप(काष्ठा wl1271_station);
	wl->hw->vअगर_data_size = माप(काष्ठा wl12xx_vअगर);

	wl->hw->max_rx_aggregation_subframes = wl->conf.ht.rx_ba_win_size;

	वापस 0;
पूर्ण

काष्ठा ieee80211_hw *wlcore_alloc_hw(माप_प्रकार priv_size, u32 aggr_buf_size,
				     u32 mbox_size)
अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा wl1271 *wl;
	पूर्णांक i, j, ret;
	अचिन्हित पूर्णांक order;

	hw = ieee80211_alloc_hw(माप(*wl), &wl1271_ops);
	अगर (!hw) अणु
		wl1271_error("could not alloc ieee80211_hw");
		ret = -ENOMEM;
		जाओ err_hw_alloc;
	पूर्ण

	wl = hw->priv;
	स_रखो(wl, 0, माप(*wl));

	wl->priv = kzalloc(priv_size, GFP_KERNEL);
	अगर (!wl->priv) अणु
		wl1271_error("could not alloc wl priv");
		ret = -ENOMEM;
		जाओ err_priv_alloc;
	पूर्ण

	INIT_LIST_HEAD(&wl->wlvअगर_list);

	wl->hw = hw;

	/*
	 * wl->num_links is not configured yet, so just use WLCORE_MAX_LINKS.
	 * we करोn't allocate any additional resource here, so that's fine.
	 */
	क्रम (i = 0; i < NUM_TX_QUEUES; i++)
		क्रम (j = 0; j < WLCORE_MAX_LINKS; j++)
			skb_queue_head_init(&wl->links[j].tx_queue[i]);

	skb_queue_head_init(&wl->deferred_rx_queue);
	skb_queue_head_init(&wl->deferred_tx_queue);

	INIT_WORK(&wl->netstack_work, wl1271_netstack_work);
	INIT_WORK(&wl->tx_work, wl1271_tx_work);
	INIT_WORK(&wl->recovery_work, wl1271_recovery_work);
	INIT_DELAYED_WORK(&wl->scan_complete_work, wl1271_scan_complete_work);
	INIT_DELAYED_WORK(&wl->roc_complete_work, wlcore_roc_complete_work);
	INIT_DELAYED_WORK(&wl->tx_watchकरोg_work, wl12xx_tx_watchकरोg_work);

	wl->मुक्तzable_wq = create_मुक्तzable_workqueue("wl12xx_wq");
	अगर (!wl->मुक्तzable_wq) अणु
		ret = -ENOMEM;
		जाओ err_hw;
	पूर्ण

	wl->channel = 0;
	wl->rx_counter = 0;
	wl->घातer_level = WL1271_DEFAULT_POWER_LEVEL;
	wl->band = NL80211_BAND_2GHZ;
	wl->channel_type = NL80211_CHAN_NO_HT;
	wl->flags = 0;
	wl->sg_enabled = true;
	wl->sleep_auth = WL1271_PSM_ILLEGAL;
	wl->recovery_count = 0;
	wl->hw_pg_ver = -1;
	wl->ap_ps_map = 0;
	wl->ap_fw_ps_map = 0;
	wl->quirks = 0;
	wl->प्रणाली_hlid = WL12XX_SYSTEM_HLID;
	wl->active_sta_count = 0;
	wl->active_link_count = 0;
	wl->fwlog_size = 0;

	/* The प्रणाली link is always allocated */
	__set_bit(WL12XX_SYSTEM_HLID, wl->links_map);

	स_रखो(wl->tx_frames_map, 0, माप(wl->tx_frames_map));
	क्रम (i = 0; i < wl->num_tx_desc; i++)
		wl->tx_frames[i] = शून्य;

	spin_lock_init(&wl->wl_lock);

	wl->state = WLCORE_STATE_OFF;
	wl->fw_type = WL12XX_FW_TYPE_NONE;
	mutex_init(&wl->mutex);
	mutex_init(&wl->flush_mutex);
	init_completion(&wl->nvs_loading_complete);

	order = get_order(aggr_buf_size);
	wl->aggr_buf = (u8 *)__get_मुक्त_pages(GFP_KERNEL, order);
	अगर (!wl->aggr_buf) अणु
		ret = -ENOMEM;
		जाओ err_wq;
	पूर्ण
	wl->aggr_buf_size = aggr_buf_size;

	wl->dummy_packet = wl12xx_alloc_dummy_packet(wl);
	अगर (!wl->dummy_packet) अणु
		ret = -ENOMEM;
		जाओ err_aggr;
	पूर्ण

	/* Allocate one page क्रम the FW log */
	wl->fwlog = (u8 *)get_zeroed_page(GFP_KERNEL);
	अगर (!wl->fwlog) अणु
		ret = -ENOMEM;
		जाओ err_dummy_packet;
	पूर्ण

	wl->mbox_size = mbox_size;
	wl->mbox = kदो_स्मृति(wl->mbox_size, GFP_KERNEL | GFP_DMA);
	अगर (!wl->mbox) अणु
		ret = -ENOMEM;
		जाओ err_fwlog;
	पूर्ण

	wl->buffer_32 = kदो_स्मृति(माप(*wl->buffer_32), GFP_KERNEL);
	अगर (!wl->buffer_32) अणु
		ret = -ENOMEM;
		जाओ err_mbox;
	पूर्ण

	वापस hw;

err_mbox:
	kमुक्त(wl->mbox);

err_fwlog:
	मुक्त_page((अचिन्हित दीर्घ)wl->fwlog);

err_dummy_packet:
	dev_kमुक्त_skb(wl->dummy_packet);

err_aggr:
	मुक्त_pages((अचिन्हित दीर्घ)wl->aggr_buf, order);

err_wq:
	destroy_workqueue(wl->मुक्तzable_wq);

err_hw:
	wl1271_debugfs_निकास(wl);
	kमुक्त(wl->priv);

err_priv_alloc:
	ieee80211_मुक्त_hw(hw);

err_hw_alloc:

	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_alloc_hw);

पूर्णांक wlcore_मुक्त_hw(काष्ठा wl1271 *wl)
अणु
	/* Unblock any fwlog पढ़ोers */
	mutex_lock(&wl->mutex);
	wl->fwlog_size = -1;
	mutex_unlock(&wl->mutex);

	wlcore_sysfs_मुक्त(wl);

	kमुक्त(wl->buffer_32);
	kमुक्त(wl->mbox);
	मुक्त_page((अचिन्हित दीर्घ)wl->fwlog);
	dev_kमुक्त_skb(wl->dummy_packet);
	मुक्त_pages((अचिन्हित दीर्घ)wl->aggr_buf, get_order(wl->aggr_buf_size));

	wl1271_debugfs_निकास(wl);

	vमुक्त(wl->fw);
	wl->fw = शून्य;
	wl->fw_type = WL12XX_FW_TYPE_NONE;
	kमुक्त(wl->nvs);
	wl->nvs = शून्य;

	kमुक्त(wl->raw_fw_status);
	kमुक्त(wl->fw_status);
	kमुक्त(wl->tx_res_अगर);
	destroy_workqueue(wl->मुक्तzable_wq);

	kमुक्त(wl->priv);
	ieee80211_मुक्त_hw(wl->hw);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_मुक्त_hw);

#अगर_घोषित CONFIG_PM
अटल स्थिर काष्ठा wiphy_wowlan_support wlcore_wowlan_support = अणु
	.flags = WIPHY_WOWLAN_ANY,
	.n_patterns = WL1271_MAX_RX_FILTERS,
	.pattern_min_len = 1,
	.pattern_max_len = WL1271_RX_FILTER_MAX_PATTERN_SIZE,
पूर्ण;
#पूर्ण_अगर

अटल irqवापस_t wlcore_hardirq(पूर्णांक irq, व्योम *cookie)
अणु
	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल व्योम wlcore_nvs_cb(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	काष्ठा wl1271 *wl = context;
	काष्ठा platक्रमm_device *pdev = wl->pdev;
	काष्ठा wlcore_platdev_data *pdev_data = dev_get_platdata(&pdev->dev);
	काष्ठा resource *res;

	पूर्णांक ret;
	irq_handler_t hardirq_fn = शून्य;

	अगर (fw) अणु
		wl->nvs = kmemdup(fw->data, fw->size, GFP_KERNEL);
		अगर (!wl->nvs) अणु
			wl1271_error("Could not allocate nvs data");
			जाओ out;
		पूर्ण
		wl->nvs_len = fw->size;
	पूर्ण अन्यथा अगर (pdev_data->family->nvs_name) अणु
		wl1271_debug(DEBUG_BOOT, "Could not get nvs file %s",
			     pdev_data->family->nvs_name);
		wl->nvs = शून्य;
		wl->nvs_len = 0;
	पूर्ण अन्यथा अणु
		wl->nvs = शून्य;
		wl->nvs_len = 0;
	पूर्ण

	ret = wl->ops->setup(wl);
	अगर (ret < 0)
		जाओ out_मुक्त_nvs;

	BUG_ON(wl->num_tx_desc > WLCORE_MAX_TX_DESCRIPTORS);

	/* adjust some runसमय configuration parameters */
	wlcore_adjust_conf(wl);

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		wl1271_error("Could not get IRQ resource");
		जाओ out_मुक्त_nvs;
	पूर्ण

	wl->irq = res->start;
	wl->irq_flags = res->flags & IRQF_TRIGGER_MASK;
	wl->अगर_ops = pdev_data->अगर_ops;

	अगर (wl->irq_flags & (IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING))
		hardirq_fn = wlcore_hardirq;
	अन्यथा
		wl->irq_flags |= IRQF_ONESHOT;

	ret = wl12xx_set_घातer_on(wl);
	अगर (ret < 0)
		जाओ out_मुक्त_nvs;

	ret = wl12xx_get_hw_info(wl);
	अगर (ret < 0) अणु
		wl1271_error("couldn't get hw info");
		wl1271_घातer_off(wl);
		जाओ out_मुक्त_nvs;
	पूर्ण

	ret = request_thपढ़ोed_irq(wl->irq, hardirq_fn, wlcore_irq,
				   wl->irq_flags, pdev->name, wl);
	अगर (ret < 0) अणु
		wl1271_error("interrupt configuration failed");
		wl1271_घातer_off(wl);
		जाओ out_मुक्त_nvs;
	पूर्ण

#अगर_घोषित CONFIG_PM
	device_init_wakeup(wl->dev, true);

	ret = enable_irq_wake(wl->irq);
	अगर (!ret) अणु
		wl->irq_wake_enabled = true;
		अगर (pdev_data->pwr_in_suspend)
			wl->hw->wiphy->wowlan = &wlcore_wowlan_support;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 1);
	अगर (res) अणु
		wl->wakeirq = res->start;
		wl->wakeirq_flags = res->flags & IRQF_TRIGGER_MASK;
		ret = dev_pm_set_dedicated_wake_irq(wl->dev, wl->wakeirq);
		अगर (ret)
			wl->wakeirq = -ENODEV;
	पूर्ण अन्यथा अणु
		wl->wakeirq = -ENODEV;
	पूर्ण
#पूर्ण_अगर
	disable_irq(wl->irq);
	wl1271_घातer_off(wl);

	ret = wl->ops->identअगरy_chip(wl);
	अगर (ret < 0)
		जाओ out_irq;

	ret = wl1271_init_ieee80211(wl);
	अगर (ret)
		जाओ out_irq;

	ret = wl1271_रेजिस्टर_hw(wl);
	अगर (ret)
		जाओ out_irq;

	ret = wlcore_sysfs_init(wl);
	अगर (ret)
		जाओ out_unreg;

	wl->initialized = true;
	जाओ out;

out_unreg:
	wl1271_unरेजिस्टर_hw(wl);

out_irq:
	अगर (wl->wakeirq >= 0)
		dev_pm_clear_wake_irq(wl->dev);
	device_init_wakeup(wl->dev, false);
	मुक्त_irq(wl->irq, wl);

out_मुक्त_nvs:
	kमुक्त(wl->nvs);

out:
	release_firmware(fw);
	complete_all(&wl->nvs_loading_complete);
पूर्ण

अटल पूर्णांक __maybe_unused wlcore_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा wl1271 *wl = dev_get_drvdata(dev);
	काष्ठा wl12xx_vअगर *wlvअगर;
	पूर्णांक error;

	/* We करो not enter elp sleep in PLT mode */
	अगर (wl->plt)
		वापस 0;

	/* Nothing to करो अगर no ELP mode requested */
	अगर (wl->sleep_auth != WL1271_PSM_ELP)
		वापस 0;

	wl12xx_क्रम_each_wlvअगर(wl, wlvअगर) अणु
		अगर (!test_bit(WLVIF_FLAG_IN_PS, &wlvअगर->flags) &&
		    test_bit(WLVIF_FLAG_IN_USE, &wlvअगर->flags))
			वापस -EBUSY;
	पूर्ण

	wl1271_debug(DEBUG_PSM, "chip to elp");
	error = wlcore_raw_ग_लिखो32(wl, HW_ACCESS_ELP_CTRL_REG, ELPCTRL_SLEEP);
	अगर (error < 0) अणु
		wl12xx_queue_recovery_work(wl);

		वापस error;
	पूर्ण

	set_bit(WL1271_FLAG_IN_ELP, &wl->flags);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused wlcore_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा wl1271 *wl = dev_get_drvdata(dev);
	DECLARE_COMPLETION_ONSTACK(compl);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	अचिन्हित दीर्घ start_समय = jअगरfies;
	bool recovery = false;

	/* Nothing to करो अगर no ELP mode requested */
	अगर (!test_bit(WL1271_FLAG_IN_ELP, &wl->flags))
		वापस 0;

	wl1271_debug(DEBUG_PSM, "waking up chip from elp");

	spin_lock_irqsave(&wl->wl_lock, flags);
	wl->elp_compl = &compl;
	spin_unlock_irqrestore(&wl->wl_lock, flags);

	ret = wlcore_raw_ग_लिखो32(wl, HW_ACCESS_ELP_CTRL_REG, ELPCTRL_WAKE_UP);
	अगर (ret < 0) अणु
		recovery = true;
	पूर्ण अन्यथा अगर (!test_bit(WL1271_FLAG_IRQ_RUNNING, &wl->flags)) अणु
		ret = रुको_क्रम_completion_समयout(&compl,
			msecs_to_jअगरfies(WL1271_WAKEUP_TIMEOUT));
		अगर (ret == 0) अणु
			wl1271_warning("ELP wakeup timeout!");
			recovery = true;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&wl->wl_lock, flags);
	wl->elp_compl = शून्य;
	spin_unlock_irqrestore(&wl->wl_lock, flags);
	clear_bit(WL1271_FLAG_IN_ELP, &wl->flags);

	अगर (recovery) अणु
		set_bit(WL1271_FLAG_INTENDED_FW_RECOVERY, &wl->flags);
		wl12xx_queue_recovery_work(wl);
	पूर्ण अन्यथा अणु
		wl1271_debug(DEBUG_PSM, "wakeup time: %u ms",
			     jअगरfies_to_msecs(jअगरfies - start_समय));
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops wlcore_pm_ops = अणु
	SET_RUNTIME_PM_OPS(wlcore_runसमय_suspend,
			   wlcore_runसमय_resume,
			   शून्य)
पूर्ण;

पूर्णांक wlcore_probe(काष्ठा wl1271 *wl, काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wlcore_platdev_data *pdev_data = dev_get_platdata(&pdev->dev);
	स्थिर अक्षर *nvs_name;
	पूर्णांक ret = 0;

	अगर (!wl->ops || !wl->ptable || !pdev_data)
		वापस -EINVAL;

	wl->dev = &pdev->dev;
	wl->pdev = pdev;
	platक्रमm_set_drvdata(pdev, wl);

	अगर (pdev_data->family && pdev_data->family->nvs_name) अणु
		nvs_name = pdev_data->family->nvs_name;
		ret = request_firmware_noरुको(THIS_MODULE, FW_ACTION_HOTPLUG,
					      nvs_name, &pdev->dev, GFP_KERNEL,
					      wl, wlcore_nvs_cb);
		अगर (ret < 0) अणु
			wl1271_error("request_firmware_nowait failed for %s: %d",
				     nvs_name, ret);
			complete_all(&wl->nvs_loading_complete);
		पूर्ण
	पूर्ण अन्यथा अणु
		wlcore_nvs_cb(शून्य, wl);
	पूर्ण

	wl->dev->driver->pm = &wlcore_pm_ops;
	pm_runसमय_set_स्वतःsuspend_delay(wl->dev, 50);
	pm_runसमय_use_स्वतःsuspend(wl->dev);
	pm_runसमय_enable(wl->dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_probe);

पूर्णांक wlcore_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wlcore_platdev_data *pdev_data = dev_get_platdata(&pdev->dev);
	काष्ठा wl1271 *wl = platक्रमm_get_drvdata(pdev);
	पूर्णांक error;

	error = pm_runसमय_get_sync(wl->dev);
	अगर (error < 0)
		dev_warn(wl->dev, "PM runtime failed: %i\n", error);

	wl->dev->driver->pm = शून्य;

	अगर (pdev_data->family && pdev_data->family->nvs_name)
		रुको_क्रम_completion(&wl->nvs_loading_complete);
	अगर (!wl->initialized)
		वापस 0;

	अगर (wl->wakeirq >= 0) अणु
		dev_pm_clear_wake_irq(wl->dev);
		wl->wakeirq = -ENODEV;
	पूर्ण

	device_init_wakeup(wl->dev, false);

	अगर (wl->irq_wake_enabled)
		disable_irq_wake(wl->irq);

	wl1271_unरेजिस्टर_hw(wl);

	pm_runसमय_put_sync(wl->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(wl->dev);
	pm_runसमय_disable(wl->dev);

	मुक्त_irq(wl->irq, wl);
	wlcore_मुक्त_hw(wl);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_हटाओ);

u32 wl12xx_debug_level = DEBUG_NONE;
EXPORT_SYMBOL_GPL(wl12xx_debug_level);
module_param_named(debug_level, wl12xx_debug_level, uपूर्णांक, 0600);
MODULE_PARM_DESC(debug_level, "wl12xx debugging level");

module_param_named(fwlog, fwlog_param, अक्षरp, 0);
MODULE_PARM_DESC(fwlog,
		 "FW logger options: continuous, dbgpins or disable");

module_param(fwlog_mem_blocks, पूर्णांक, 0600);
MODULE_PARM_DESC(fwlog_mem_blocks, "fwlog mem_blocks");

module_param(bug_on_recovery, पूर्णांक, 0600);
MODULE_PARM_DESC(bug_on_recovery, "BUG() on fw recovery");

module_param(no_recovery, पूर्णांक, 0600);
MODULE_PARM_DESC(no_recovery, "Prevent HW recovery. FW will remain stuck.");

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Luciano Coelho <coelho@ti.com>");
MODULE_AUTHOR("Juuso Oikarinen <juuso.oikarinen@nokia.com>");
