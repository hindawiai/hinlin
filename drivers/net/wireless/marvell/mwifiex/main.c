<शैली गुरु>
/*
 * NXP Wireless LAN device driver: major functions
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#समावेश <linux/suspend.h>

#समावेश "main.h"
#समावेश "wmm.h"
#समावेश "cfg80211.h"
#समावेश "11n.h"

#घोषणा VERSION	"1.0"
#घोषणा MFG_FIRMWARE	"mwifiex_mfg.bin"

अटल अचिन्हित पूर्णांक debug_mask = MWIFIEX_DEFAULT_DEBUG_MASK;
module_param(debug_mask, uपूर्णांक, 0);
MODULE_PARM_DESC(debug_mask, "bitmap for debug flags");

स्थिर अक्षर driver_version[] = "mwifiex " VERSION " (%s) ";
अटल अक्षर *cal_data_cfg;
module_param(cal_data_cfg, अक्षरp, 0);

अटल अचिन्हित लघु driver_mode;
module_param(driver_mode, uलघु, 0);
MODULE_PARM_DESC(driver_mode,
		 "station=0x1(default), ap-sta=0x3, station-p2p=0x5, ap-sta-p2p=0x7");

bool mfg_mode;
module_param(mfg_mode, bool, 0);
MODULE_PARM_DESC(mfg_mode, "manufacturing mode enable:1, disable:0");

bool aggr_ctrl;
module_param(aggr_ctrl, bool, 0000);
MODULE_PARM_DESC(aggr_ctrl, "usb tx aggregation enable:1, disable:0");

स्थिर u16 mwअगरiex_1d_to_wmm_queue[8] = अणु 1, 0, 0, 1, 2, 2, 3, 3 पूर्ण;

/*
 * This function रेजिस्टरs the device and perक्रमms all the necessary
 * initializations.
 *
 * The following initialization operations are perक्रमmed -
 *      - Allocate adapter काष्ठाure
 *      - Save पूर्णांकerface specअगरic operations table in adapter
 *      - Call पूर्णांकerface specअगरic initialization routine
 *      - Allocate निजी काष्ठाures
 *      - Set शेष adapter काष्ठाure parameters
 *      - Initialize locks
 *
 * In हाल of any errors during inittialization, this function also ensures
 * proper cleanup beक्रमe निकासing.
 */
अटल पूर्णांक mwअगरiex_रेजिस्टर(व्योम *card, काष्ठा device *dev,
			    काष्ठा mwअगरiex_अगर_ops *अगर_ops, व्योम **padapter)
अणु
	काष्ठा mwअगरiex_adapter *adapter;
	पूर्णांक i;

	adapter = kzalloc(माप(काष्ठा mwअगरiex_adapter), GFP_KERNEL);
	अगर (!adapter)
		वापस -ENOMEM;

	*padapter = adapter;
	adapter->dev = dev;
	adapter->card = card;

	/* Save पूर्णांकerface specअगरic operations in adapter */
	स_हटाओ(&adapter->अगर_ops, अगर_ops, माप(काष्ठा mwअगरiex_अगर_ops));
	adapter->debug_mask = debug_mask;

	/* card specअगरic initialization has been deferred until now .. */
	अगर (adapter->अगर_ops.init_अगर)
		अगर (adapter->अगर_ops.init_अगर(adapter))
			जाओ error;

	adapter->priv_num = 0;

	क्रम (i = 0; i < MWIFIEX_MAX_BSS_NUM; i++) अणु
		/* Allocate memory क्रम निजी काष्ठाure */
		adapter->priv[i] =
			kzalloc(माप(काष्ठा mwअगरiex_निजी), GFP_KERNEL);
		अगर (!adapter->priv[i])
			जाओ error;

		adapter->priv[i]->adapter = adapter;
		adapter->priv_num++;
	पूर्ण
	mwअगरiex_init_lock_list(adapter);

	समयr_setup(&adapter->cmd_समयr, mwअगरiex_cmd_समयout_func, 0);

	वापस 0;

error:
	mwअगरiex_dbg(adapter, ERROR,
		    "info: leave mwifiex_register with error\n");

	क्रम (i = 0; i < adapter->priv_num; i++)
		kमुक्त(adapter->priv[i]);

	kमुक्त(adapter);

	वापस -1;
पूर्ण

/*
 * This function unरेजिस्टरs the device and perक्रमms all the necessary
 * cleanups.
 *
 * The following cleanup operations are perक्रमmed -
 *      - Free the समयrs
 *      - Free beacon buffers
 *      - Free निजी काष्ठाures
 *      - Free adapter काष्ठाure
 */
अटल पूर्णांक mwअगरiex_unरेजिस्टर(काष्ठा mwअगरiex_adapter *adapter)
अणु
	s32 i;

	अगर (adapter->अगर_ops.cleanup_अगर)
		adapter->अगर_ops.cleanup_अगर(adapter);

	del_समयr_sync(&adapter->cmd_समयr);

	/* Free निजी काष्ठाures */
	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		अगर (adapter->priv[i]) अणु
			mwअगरiex_मुक्त_curr_bcn(adapter->priv[i]);
			kमुक्त(adapter->priv[i]);
		पूर्ण
	पूर्ण

	अगर (adapter->nd_info) अणु
		क्रम (i = 0 ; i < adapter->nd_info->n_matches ; i++)
			kमुक्त(adapter->nd_info->matches[i]);
		kमुक्त(adapter->nd_info);
		adapter->nd_info = शून्य;
	पूर्ण

	kमुक्त(adapter->regd);

	kमुक्त(adapter);
	वापस 0;
पूर्ण

व्योम mwअगरiex_queue_मुख्य_work(काष्ठा mwअगरiex_adapter *adapter)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adapter->मुख्य_proc_lock, flags);
	अगर (adapter->mwअगरiex_processing) अणु
		adapter->more_task_flag = true;
		spin_unlock_irqrestore(&adapter->मुख्य_proc_lock, flags);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&adapter->मुख्य_proc_lock, flags);
		queue_work(adapter->workqueue, &adapter->मुख्य_work);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_queue_मुख्य_work);

अटल व्योम mwअगरiex_queue_rx_work(काष्ठा mwअगरiex_adapter *adapter)
अणु
	spin_lock_bh(&adapter->rx_proc_lock);
	अगर (adapter->rx_processing) अणु
		spin_unlock_bh(&adapter->rx_proc_lock);
	पूर्ण अन्यथा अणु
		spin_unlock_bh(&adapter->rx_proc_lock);
		queue_work(adapter->rx_workqueue, &adapter->rx_work);
	पूर्ण
पूर्ण

अटल पूर्णांक mwअगरiex_process_rx(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा mwअगरiex_rxinfo *rx_info;

	spin_lock_bh(&adapter->rx_proc_lock);
	अगर (adapter->rx_processing || adapter->rx_locked) अणु
		spin_unlock_bh(&adapter->rx_proc_lock);
		जाओ निकास_rx_proc;
	पूर्ण अन्यथा अणु
		adapter->rx_processing = true;
		spin_unlock_bh(&adapter->rx_proc_lock);
	पूर्ण

	/* Check क्रम Rx data */
	जबतक ((skb = skb_dequeue(&adapter->rx_data_q))) अणु
		atomic_dec(&adapter->rx_pending);
		अगर ((adapter->delay_मुख्य_work ||
		     adapter->अगरace_type == MWIFIEX_USB) &&
		    (atomic_पढ़ो(&adapter->rx_pending) < LOW_RX_PENDING)) अणु
			अगर (adapter->अगर_ops.submit_rem_rx_urbs)
				adapter->अगर_ops.submit_rem_rx_urbs(adapter);
			adapter->delay_मुख्य_work = false;
			mwअगरiex_queue_मुख्य_work(adapter);
		पूर्ण
		rx_info = MWIFIEX_SKB_RXCB(skb);
		अगर (rx_info->buf_type == MWIFIEX_TYPE_AGGR_DATA) अणु
			अगर (adapter->अगर_ops.deaggr_pkt)
				adapter->अगर_ops.deaggr_pkt(adapter, skb);
			dev_kमुक्त_skb_any(skb);
		पूर्ण अन्यथा अणु
			mwअगरiex_handle_rx_packet(adapter, skb);
		पूर्ण
	पूर्ण
	spin_lock_bh(&adapter->rx_proc_lock);
	adapter->rx_processing = false;
	spin_unlock_bh(&adapter->rx_proc_lock);

निकास_rx_proc:
	वापस 0;
पूर्ण

/*
 * The मुख्य process.
 *
 * This function is the मुख्य procedure of the driver and handles various driver
 * operations. It runs in a loop and provides the core functionalities.
 *
 * The मुख्य responsibilities of this function are -
 *      - Ensure concurrency control
 *      - Handle pending पूर्णांकerrupts and call पूर्णांकerrupt handlers
 *      - Wake up the card अगर required
 *      - Handle command responses and call response handlers
 *      - Handle events and call event handlers
 *      - Execute pending commands
 *      - Transmit pending data packets
 */
पूर्णांक mwअगरiex_मुख्य_process(काष्ठा mwअगरiex_adapter *adapter)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adapter->मुख्य_proc_lock, flags);

	/* Check अगर alपढ़ोy processing */
	अगर (adapter->mwअगरiex_processing || adapter->मुख्य_locked) अणु
		adapter->more_task_flag = true;
		spin_unlock_irqrestore(&adapter->मुख्य_proc_lock, flags);
		वापस 0;
	पूर्ण अन्यथा अणु
		adapter->mwअगरiex_processing = true;
		spin_unlock_irqrestore(&adapter->मुख्य_proc_lock, flags);
	पूर्ण
process_start:
	करो अणु
		अगर (adapter->hw_status == MWIFIEX_HW_STATUS_NOT_READY)
			अवरोध;

		/* For non-USB पूर्णांकerfaces, If we process पूर्णांकerrupts first, it
		 * would increase RX pending even further. Aव्योम this by
		 * checking अगर rx_pending has crossed high threshold and
		 * schedule rx work queue and then process पूर्णांकerrupts.
		 * For USB पूर्णांकerface, there are no पूर्णांकerrupts. We alपढ़ोy have
		 * HIGH_RX_PENDING check in usb.c
		 */
		अगर (atomic_पढ़ो(&adapter->rx_pending) >= HIGH_RX_PENDING &&
		    adapter->अगरace_type != MWIFIEX_USB) अणु
			adapter->delay_मुख्य_work = true;
			mwअगरiex_queue_rx_work(adapter);
			अवरोध;
		पूर्ण

		/* Handle pending पूर्णांकerrupt अगर any */
		अगर (adapter->पूर्णांक_status) अणु
			अगर (adapter->hs_activated)
				mwअगरiex_process_hs_config(adapter);
			अगर (adapter->अगर_ops.process_पूर्णांक_status)
				adapter->अगर_ops.process_पूर्णांक_status(adapter);
		पूर्ण

		अगर (adapter->rx_work_enabled && adapter->data_received)
			mwअगरiex_queue_rx_work(adapter);

		/* Need to wake up the card ? */
		अगर ((adapter->ps_state == PS_STATE_SLEEP) &&
		    (adapter->pm_wakeup_card_req &&
		     !adapter->pm_wakeup_fw_try) &&
		    (is_command_pending(adapter) ||
		     !skb_queue_empty(&adapter->tx_data_q) ||
		     !mwअगरiex_bypass_txlist_empty(adapter) ||
		     !mwअगरiex_wmm_lists_empty(adapter))) अणु
			adapter->pm_wakeup_fw_try = true;
			mod_समयr(&adapter->wakeup_समयr, jअगरfies + (HZ*3));
			adapter->अगर_ops.wakeup(adapter);
			जारी;
		पूर्ण

		अगर (IS_CARD_RX_RCVD(adapter)) अणु
			adapter->data_received = false;
			adapter->pm_wakeup_fw_try = false;
			del_समयr(&adapter->wakeup_समयr);
			अगर (adapter->ps_state == PS_STATE_SLEEP)
				adapter->ps_state = PS_STATE_AWAKE;
		पूर्ण अन्यथा अणु
			/* We have tried to wakeup the card alपढ़ोy */
			अगर (adapter->pm_wakeup_fw_try)
				अवरोध;
			अगर (adapter->ps_state == PS_STATE_PRE_SLEEP)
				mwअगरiex_check_ps_cond(adapter);

			अगर (adapter->ps_state != PS_STATE_AWAKE)
				अवरोध;
			अगर (adapter->tx_lock_flag) अणु
				अगर (adapter->अगरace_type == MWIFIEX_USB) अणु
					अगर (!adapter->usb_mc_setup)
						अवरोध;
				पूर्ण अन्यथा
					अवरोध;
			पूर्ण

			अगर ((!adapter->scan_chan_gap_enabled &&
			     adapter->scan_processing) || adapter->data_sent ||
			     mwअगरiex_is_tdls_chan_चयनing
			     (mwअगरiex_get_priv(adapter,
					       MWIFIEX_BSS_ROLE_STA)) ||
			    (mwअगरiex_wmm_lists_empty(adapter) &&
			     mwअगरiex_bypass_txlist_empty(adapter) &&
			     skb_queue_empty(&adapter->tx_data_q))) अणु
				अगर (adapter->cmd_sent || adapter->curr_cmd ||
					!mwअगरiex_is_send_cmd_allowed
						(mwअगरiex_get_priv(adapter,
						MWIFIEX_BSS_ROLE_STA)) ||
				    (!is_command_pending(adapter)))
					अवरोध;
			पूर्ण
		पूर्ण

		/* Check क्रम event */
		अगर (adapter->event_received) अणु
			adapter->event_received = false;
			mwअगरiex_process_event(adapter);
		पूर्ण

		/* Check क्रम Cmd Resp */
		अगर (adapter->cmd_resp_received) अणु
			adapter->cmd_resp_received = false;
			mwअगरiex_process_cmdresp(adapter);

			/* call mwअगरiex back when init_fw is करोne */
			अगर (adapter->hw_status == MWIFIEX_HW_STATUS_INIT_DONE) अणु
				adapter->hw_status = MWIFIEX_HW_STATUS_READY;
				mwअगरiex_init_fw_complete(adapter);
			पूर्ण
		पूर्ण

		/* Check अगर we need to confirm Sleep Request
		   received previously */
		अगर (adapter->ps_state == PS_STATE_PRE_SLEEP)
			mwअगरiex_check_ps_cond(adapter);

		/* * The ps_state may have been changed during processing of
		 * Sleep Request event.
		 */
		अगर ((adapter->ps_state == PS_STATE_SLEEP) ||
		    (adapter->ps_state == PS_STATE_PRE_SLEEP) ||
		    (adapter->ps_state == PS_STATE_SLEEP_CFM)) अणु
			जारी;
		पूर्ण

		अगर (adapter->tx_lock_flag) अणु
			अगर (adapter->अगरace_type == MWIFIEX_USB) अणु
				अगर (!adapter->usb_mc_setup)
					जारी;
			पूर्ण अन्यथा
				जारी;
		पूर्ण

		अगर (!adapter->cmd_sent && !adapter->curr_cmd &&
		    mwअगरiex_is_send_cmd_allowed
		    (mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_STA))) अणु
			अगर (mwअगरiex_exec_next_cmd(adapter) == -1) अणु
				ret = -1;
				अवरोध;
			पूर्ण
		पूर्ण

		/** If USB Multi channel setup ongoing,
		 *  रुको क्रम पढ़ोy to tx data.
		 */
		अगर (adapter->अगरace_type == MWIFIEX_USB &&
		    adapter->usb_mc_setup)
			जारी;

		अगर ((adapter->scan_chan_gap_enabled ||
		     !adapter->scan_processing) &&
		    !adapter->data_sent &&
		    !skb_queue_empty(&adapter->tx_data_q)) अणु
			mwअगरiex_process_tx_queue(adapter);
			अगर (adapter->hs_activated) अणु
				clear_bit(MWIFIEX_IS_HS_CONFIGURED,
					  &adapter->work_flags);
				mwअगरiex_hs_activated_event
					(mwअगरiex_get_priv
					(adapter, MWIFIEX_BSS_ROLE_ANY),
					false);
			पूर्ण
		पूर्ण

		अगर ((adapter->scan_chan_gap_enabled ||
		     !adapter->scan_processing) &&
		    !adapter->data_sent &&
		    !mwअगरiex_bypass_txlist_empty(adapter) &&
		    !mwअगरiex_is_tdls_chan_चयनing
			(mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_STA))) अणु
			mwअगरiex_process_bypass_tx(adapter);
			अगर (adapter->hs_activated) अणु
				clear_bit(MWIFIEX_IS_HS_CONFIGURED,
					  &adapter->work_flags);
				mwअगरiex_hs_activated_event
					(mwअगरiex_get_priv
					 (adapter, MWIFIEX_BSS_ROLE_ANY),
					 false);
			पूर्ण
		पूर्ण

		अगर ((adapter->scan_chan_gap_enabled ||
		     !adapter->scan_processing) &&
		    !adapter->data_sent && !mwअगरiex_wmm_lists_empty(adapter) &&
		    !mwअगरiex_is_tdls_chan_चयनing
			(mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_STA))) अणु
			mwअगरiex_wmm_process_tx(adapter);
			अगर (adapter->hs_activated) अणु
				clear_bit(MWIFIEX_IS_HS_CONFIGURED,
					  &adapter->work_flags);
				mwअगरiex_hs_activated_event
					(mwअगरiex_get_priv
					 (adapter, MWIFIEX_BSS_ROLE_ANY),
					 false);
			पूर्ण
		पूर्ण

		अगर (adapter->delay_null_pkt && !adapter->cmd_sent &&
		    !adapter->curr_cmd && !is_command_pending(adapter) &&
		    (mwअगरiex_wmm_lists_empty(adapter) &&
		     mwअगरiex_bypass_txlist_empty(adapter) &&
		     skb_queue_empty(&adapter->tx_data_q))) अणु
			अगर (!mwअगरiex_send_null_packet
			    (mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_STA),
			     MWIFIEX_TxPD_POWER_MGMT_शून्य_PACKET |
			     MWIFIEX_TxPD_POWER_MGMT_LAST_PACKET)) अणु
				adapter->delay_null_pkt = false;
				adapter->ps_state = PS_STATE_SLEEP;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण जबतक (true);

	spin_lock_irqsave(&adapter->मुख्य_proc_lock, flags);
	अगर (adapter->more_task_flag) अणु
		adapter->more_task_flag = false;
		spin_unlock_irqrestore(&adapter->मुख्य_proc_lock, flags);
		जाओ process_start;
	पूर्ण
	adapter->mwअगरiex_processing = false;
	spin_unlock_irqrestore(&adapter->मुख्य_proc_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_मुख्य_process);

/*
 * This function मुक्तs the adapter काष्ठाure.
 *
 * Additionally, this बंदs the netlink socket, मुक्तs the समयrs
 * and निजी काष्ठाures.
 */
अटल व्योम mwअगरiex_मुक्त_adapter(काष्ठा mwअगरiex_adapter *adapter)
अणु
	अगर (!adapter) अणु
		pr_err("%s: adapter is NULL\n", __func__);
		वापस;
	पूर्ण

	mwअगरiex_unरेजिस्टर(adapter);
	pr_debug("info: %s: free adapter\n", __func__);
पूर्ण

/*
 * This function cancels all works in the queue and destroys
 * the मुख्य workqueue.
 */
अटल व्योम mwअगरiex_terminate_workqueue(काष्ठा mwअगरiex_adapter *adapter)
अणु
	अगर (adapter->workqueue) अणु
		flush_workqueue(adapter->workqueue);
		destroy_workqueue(adapter->workqueue);
		adapter->workqueue = शून्य;
	पूर्ण

	अगर (adapter->rx_workqueue) अणु
		flush_workqueue(adapter->rx_workqueue);
		destroy_workqueue(adapter->rx_workqueue);
		adapter->rx_workqueue = शून्य;
	पूर्ण
पूर्ण

/*
 * This function माला_लो firmware and initializes it.
 *
 * The मुख्य initialization steps followed are -
 *      - Download the correct firmware to card
 *      - Issue the init commands to firmware
 */
अटल पूर्णांक _mwअगरiex_fw_dpc(स्थिर काष्ठा firmware *firmware, व्योम *context)
अणु
	पूर्णांक ret;
	अक्षर fmt[64];
	काष्ठा mwअगरiex_adapter *adapter = context;
	काष्ठा mwअगरiex_fw_image fw;
	bool init_failed = false;
	काष्ठा wireless_dev *wdev;
	काष्ठा completion *fw_करोne = adapter->fw_करोne;

	अगर (!firmware) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "Failed to get firmware %s\n", adapter->fw_name);
		जाओ err_dnld_fw;
	पूर्ण

	स_रखो(&fw, 0, माप(काष्ठा mwअगरiex_fw_image));
	adapter->firmware = firmware;
	fw.fw_buf = (u8 *) adapter->firmware->data;
	fw.fw_len = adapter->firmware->size;

	अगर (adapter->अगर_ops.dnld_fw) अणु
		ret = adapter->अगर_ops.dnld_fw(adapter, &fw);
	पूर्ण अन्यथा अणु
		ret = mwअगरiex_dnld_fw(adapter, &fw);
	पूर्ण

	अगर (ret == -1)
		जाओ err_dnld_fw;

	mwअगरiex_dbg(adapter, MSG, "WLAN FW is active\n");

	अगर (cal_data_cfg) अणु
		अगर ((request_firmware(&adapter->cal_data, cal_data_cfg,
				      adapter->dev)) < 0)
			mwअगरiex_dbg(adapter, ERROR,
				    "Cal data request_firmware() failed\n");
	पूर्ण

	/* enable host पूर्णांकerrupt after fw dnld is successful */
	अगर (adapter->अगर_ops.enable_पूर्णांक) अणु
		अगर (adapter->अगर_ops.enable_पूर्णांक(adapter))
			जाओ err_dnld_fw;
	पूर्ण

	adapter->init_रुको_q_woken = false;
	ret = mwअगरiex_init_fw(adapter);
	अगर (ret == -1) अणु
		जाओ err_init_fw;
	पूर्ण अन्यथा अगर (!ret) अणु
		adapter->hw_status = MWIFIEX_HW_STATUS_READY;
		जाओ करोne;
	पूर्ण
	/* Wait क्रम mwअगरiex_init to complete */
	अगर (!adapter->mfg_mode) अणु
		रुको_event_पूर्णांकerruptible(adapter->init_रुको_q,
					 adapter->init_रुको_q_woken);
		अगर (adapter->hw_status != MWIFIEX_HW_STATUS_READY)
			जाओ err_init_fw;
	पूर्ण

	अगर (!adapter->wiphy) अणु
		अगर (mwअगरiex_रेजिस्टर_cfg80211(adapter)) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "cannot register with cfg80211\n");
			जाओ err_init_fw;
		पूर्ण
	पूर्ण

	अगर (mwअगरiex_init_channel_scan_gap(adapter)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "could not init channel stats table\n");
		जाओ err_init_chan_scan;
	पूर्ण

	अगर (driver_mode) अणु
		driver_mode &= MWIFIEX_DRIVER_MODE_BITMASK;
		driver_mode |= MWIFIEX_DRIVER_MODE_STA;
	पूर्ण

	rtnl_lock();
	wiphy_lock(adapter->wiphy);
	/* Create station पूर्णांकerface by शेष */
	wdev = mwअगरiex_add_भव_पूर्णांकf(adapter->wiphy, "mlan%d", NET_NAME_ENUM,
					NL80211_IFTYPE_STATION, शून्य);
	अगर (IS_ERR(wdev)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "cannot create default STA interface\n");
		wiphy_unlock(adapter->wiphy);
		rtnl_unlock();
		जाओ err_add_पूर्णांकf;
	पूर्ण

	अगर (driver_mode & MWIFIEX_DRIVER_MODE_UAP) अणु
		wdev = mwअगरiex_add_भव_पूर्णांकf(adapter->wiphy, "uap%d", NET_NAME_ENUM,
						NL80211_IFTYPE_AP, शून्य);
		अगर (IS_ERR(wdev)) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "cannot create AP interface\n");
			wiphy_unlock(adapter->wiphy);
			rtnl_unlock();
			जाओ err_add_पूर्णांकf;
		पूर्ण
	पूर्ण

	अगर (driver_mode & MWIFIEX_DRIVER_MODE_P2P) अणु
		wdev = mwअगरiex_add_भव_पूर्णांकf(adapter->wiphy, "p2p%d", NET_NAME_ENUM,
						NL80211_IFTYPE_P2P_CLIENT, शून्य);
		अगर (IS_ERR(wdev)) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "cannot create p2p client interface\n");
			wiphy_unlock(adapter->wiphy);
			rtnl_unlock();
			जाओ err_add_पूर्णांकf;
		पूर्ण
	पूर्ण
	wiphy_unlock(adapter->wiphy);
	rtnl_unlock();

	mwअगरiex_drv_get_driver_version(adapter, fmt, माप(fmt) - 1);
	mwअगरiex_dbg(adapter, MSG, "driver_version = %s\n", fmt);
	adapter->is_up = true;
	जाओ करोne;

err_add_पूर्णांकf:
	vमुक्त(adapter->chan_stats);
err_init_chan_scan:
	wiphy_unरेजिस्टर(adapter->wiphy);
	wiphy_मुक्त(adapter->wiphy);
err_init_fw:
	अगर (adapter->अगर_ops.disable_पूर्णांक)
		adapter->अगर_ops.disable_पूर्णांक(adapter);
err_dnld_fw:
	mwअगरiex_dbg(adapter, ERROR,
		    "info: %s: unregister device\n", __func__);
	अगर (adapter->अगर_ops.unरेजिस्टर_dev)
		adapter->अगर_ops.unरेजिस्टर_dev(adapter);

	set_bit(MWIFIEX_SURPRISE_REMOVED, &adapter->work_flags);
	mwअगरiex_terminate_workqueue(adapter);

	अगर (adapter->hw_status == MWIFIEX_HW_STATUS_READY) अणु
		pr_debug("info: %s: shutdown mwifiex\n", __func__);
		mwअगरiex_shutकरोwn_drv(adapter);
		mwअगरiex_मुक्त_cmd_buffers(adapter);
	पूर्ण

	init_failed = true;
करोne:
	अगर (adapter->cal_data) अणु
		release_firmware(adapter->cal_data);
		adapter->cal_data = शून्य;
	पूर्ण
	अगर (adapter->firmware) अणु
		release_firmware(adapter->firmware);
		adapter->firmware = शून्य;
	पूर्ण
	अगर (init_failed) अणु
		अगर (adapter->irq_wakeup >= 0)
			device_init_wakeup(adapter->dev, false);
		mwअगरiex_मुक्त_adapter(adapter);
	पूर्ण
	/* Tell all current and future रुकोers we're finished */
	complete_all(fw_करोne);

	वापस init_failed ? -EIO : 0;
पूर्ण

अटल व्योम mwअगरiex_fw_dpc(स्थिर काष्ठा firmware *firmware, व्योम *context)
अणु
	_mwअगरiex_fw_dpc(firmware, context);
पूर्ण

/*
 * This function माला_लो the firmware and (अगर called asynchronously) kicks off the
 * HW init when करोne.
 */
अटल पूर्णांक mwअगरiex_init_hw_fw(काष्ठा mwअगरiex_adapter *adapter,
			      bool req_fw_noरुको)
अणु
	पूर्णांक ret;

	/* Override शेष firmware with manufacturing one अगर
	 * manufacturing mode is enabled
	 */
	अगर (mfg_mode) अणु
		अगर (strlcpy(adapter->fw_name, MFG_FIRMWARE,
			    माप(adapter->fw_name)) >=
			    माप(adapter->fw_name)) अणु
			pr_err("%s: fw_name too long!\n", __func__);
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (req_fw_noरुको) अणु
		ret = request_firmware_noरुको(THIS_MODULE, 1, adapter->fw_name,
					      adapter->dev, GFP_KERNEL, adapter,
					      mwअगरiex_fw_dpc);
	पूर्ण अन्यथा अणु
		ret = request_firmware(&adapter->firmware,
				       adapter->fw_name,
				       adapter->dev);
	पूर्ण

	अगर (ret < 0)
		mwअगरiex_dbg(adapter, ERROR, "request_firmware%s error %d\n",
			    req_fw_noरुको ? "_nowait" : "", ret);
	वापस ret;
पूर्ण

/*
 * CFG802.11 network device handler क्रम खोलो.
 *
 * Starts the data queue.
 */
अटल पूर्णांक
mwअगरiex_खोलो(काष्ठा net_device *dev)
अणु
	netअगर_carrier_off(dev);

	वापस 0;
पूर्ण

/*
 * CFG802.11 network device handler क्रम बंद.
 */
अटल पूर्णांक
mwअगरiex_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);

	अगर (priv->scan_request) अणु
		काष्ठा cfg80211_scan_info info = अणु
			.पातed = true,
		पूर्ण;

		mwअगरiex_dbg(priv->adapter, INFO,
			    "aborting scan on ndo_stop\n");
		cfg80211_scan_करोne(priv->scan_request, &info);
		priv->scan_request = शून्य;
		priv->scan_पातing = true;
	पूर्ण

	अगर (priv->sched_scanning) अणु
		mwअगरiex_dbg(priv->adapter, INFO,
			    "aborting bgscan on ndo_stop\n");
		mwअगरiex_stop_bg_scan(priv);
		cfg80211_sched_scan_stopped(priv->wdev.wiphy, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool
mwअगरiex_bypass_tx_queue(काष्ठा mwअगरiex_निजी *priv,
			काष्ठा sk_buff *skb)
अणु
	काष्ठा ethhdr *eth_hdr = (काष्ठा ethhdr *)skb->data;

	अगर (ntohs(eth_hdr->h_proto) == ETH_P_PAE ||
	    mwअगरiex_is_skb_mgmt_frame(skb) ||
	    (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA &&
	     ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info) &&
	     (ntohs(eth_hdr->h_proto) == ETH_P_TDLS))) अणु
		mwअगरiex_dbg(priv->adapter, DATA,
			    "bypass txqueue; eth type %#x, mgmt %d\n",
			     ntohs(eth_hdr->h_proto),
			     mwअगरiex_is_skb_mgmt_frame(skb));
		वापस true;
	पूर्ण

	वापस false;
पूर्ण
/*
 * Add buffer पूर्णांकo wmm tx queue and queue work to transmit it.
 */
पूर्णांक mwअगरiex_queue_tx_pkt(काष्ठा mwअगरiex_निजी *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा netdev_queue *txq;
	पूर्णांक index = mwअगरiex_1d_to_wmm_queue[skb->priority];

	अगर (atomic_inc_वापस(&priv->wmm_tx_pending[index]) >= MAX_TX_PENDING) अणु
		txq = netdev_get_tx_queue(priv->netdev, index);
		अगर (!netअगर_tx_queue_stopped(txq)) अणु
			netअगर_tx_stop_queue(txq);
			mwअगरiex_dbg(priv->adapter, DATA,
				    "stop queue: %d\n", index);
		पूर्ण
	पूर्ण

	अगर (mwअगरiex_bypass_tx_queue(priv, skb)) अणु
		atomic_inc(&priv->adapter->tx_pending);
		atomic_inc(&priv->adapter->bypass_tx_pending);
		mwअगरiex_wmm_add_buf_bypass_txqueue(priv, skb);
	 पूर्ण अन्यथा अणु
		atomic_inc(&priv->adapter->tx_pending);
		mwअगरiex_wmm_add_buf_txqueue(priv, skb);
	 पूर्ण

	mwअगरiex_queue_मुख्य_work(priv->adapter);

	वापस 0;
पूर्ण

काष्ठा sk_buff *
mwअगरiex_clone_skb_क्रम_tx_status(काष्ठा mwअगरiex_निजी *priv,
				काष्ठा sk_buff *skb, u8 flag, u64 *cookie)
अणु
	काष्ठा sk_buff *orig_skb = skb;
	काष्ठा mwअगरiex_txinfo *tx_info, *orig_tx_info;

	skb = skb_clone(skb, GFP_ATOMIC);
	अगर (skb) अणु
		पूर्णांक id;

		spin_lock_bh(&priv->ack_status_lock);
		id = idr_alloc(&priv->ack_status_frames, orig_skb,
			       1, 0x10, GFP_ATOMIC);
		spin_unlock_bh(&priv->ack_status_lock);

		अगर (id >= 0) अणु
			tx_info = MWIFIEX_SKB_TXCB(skb);
			tx_info->ack_frame_id = id;
			tx_info->flags |= flag;
			orig_tx_info = MWIFIEX_SKB_TXCB(orig_skb);
			orig_tx_info->ack_frame_id = id;
			orig_tx_info->flags |= flag;

			अगर (flag == MWIFIEX_BUF_FLAG_ACTION_TX_STATUS && cookie)
				orig_tx_info->cookie = *cookie;

		पूर्ण अन्यथा अगर (skb_shared(skb)) अणु
			kमुक्त_skb(orig_skb);
		पूर्ण अन्यथा अणु
			kमुक्त_skb(skb);
			skb = orig_skb;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* couldn't clone -- lose tx status ... */
		skb = orig_skb;
	पूर्ण

	वापस skb;
पूर्ण

/*
 * CFG802.11 network device handler क्रम data transmission.
 */
अटल netdev_tx_t
mwअगरiex_hard_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);
	काष्ठा sk_buff *new_skb;
	काष्ठा mwअगरiex_txinfo *tx_info;
	bool multicast;

	mwअगरiex_dbg(priv->adapter, DATA,
		    "data: %lu BSS(%d-%d): Data <= kernel\n",
		    jअगरfies, priv->bss_type, priv->bss_num);

	अगर (test_bit(MWIFIEX_SURPRISE_REMOVED, &priv->adapter->work_flags)) अणु
		kमुक्त_skb(skb);
		priv->stats.tx_dropped++;
		वापस 0;
	पूर्ण
	अगर (!skb->len || (skb->len > ETH_FRAME_LEN)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "Tx: bad skb len %d\n", skb->len);
		kमुक्त_skb(skb);
		priv->stats.tx_dropped++;
		वापस 0;
	पूर्ण
	अगर (skb_headroom(skb) < MWIFIEX_MIN_DATA_HEADER_LEN) अणु
		mwअगरiex_dbg(priv->adapter, DATA,
			    "data: Tx: insufficient skb headroom %d\n",
			    skb_headroom(skb));
		/* Insufficient skb headroom - allocate a new skb */
		new_skb =
			skb_पुनः_स्मृति_headroom(skb, MWIFIEX_MIN_DATA_HEADER_LEN);
		अगर (unlikely(!new_skb)) अणु
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "Tx: cannot alloca new_skb\n");
			kमुक्त_skb(skb);
			priv->stats.tx_dropped++;
			वापस 0;
		पूर्ण
		kमुक्त_skb(skb);
		skb = new_skb;
		mwअगरiex_dbg(priv->adapter, INFO,
			    "info: new skb headroomd %d\n",
			    skb_headroom(skb));
	पूर्ण

	tx_info = MWIFIEX_SKB_TXCB(skb);
	स_रखो(tx_info, 0, माप(*tx_info));
	tx_info->bss_num = priv->bss_num;
	tx_info->bss_type = priv->bss_type;
	tx_info->pkt_len = skb->len;

	multicast = is_multicast_ether_addr(skb->data);

	अगर (unlikely(!multicast && skb->sk &&
		     skb_shinfo(skb)->tx_flags & SKBTX_WIFI_STATUS &&
		     priv->adapter->fw_api_ver == MWIFIEX_FW_V15))
		skb = mwअगरiex_clone_skb_क्रम_tx_status(priv,
						      skb,
					MWIFIEX_BUF_FLAG_EAPOL_TX_STATUS, शून्य);

	/* Record the current समय the packet was queued; used to
	 * determine the amount of समय the packet was queued in
	 * the driver beक्रमe it was sent to the firmware.
	 * The delay is then sent aदीर्घ with the packet to the
	 * firmware क्रम aggregate delay calculation क्रम stats and
	 * MSDU lअगरeसमय expiry.
	 */
	__net_बारtamp(skb);

	अगर (ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info) &&
	    priv->bss_type == MWIFIEX_BSS_TYPE_STA &&
	    !ether_addr_equal_unaligned(priv->cfg_bssid, skb->data)) अणु
		अगर (priv->adapter->स्वतः_tdls && priv->check_tdls_tx)
			mwअगरiex_tdls_check_tx(priv, skb);
	पूर्ण

	mwअगरiex_queue_tx_pkt(priv, skb);

	वापस 0;
पूर्ण

पूर्णांक mwअगरiex_set_mac_address(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा net_device *dev, bool बाह्यal,
			    u8 *new_mac)
अणु
	पूर्णांक ret;
	u64 mac_addr, old_mac_addr;

	old_mac_addr = ether_addr_to_u64(priv->curr_addr);

	अगर (बाह्यal) अणु
		mac_addr = ether_addr_to_u64(new_mac);
	पूर्ण अन्यथा अणु
		/* Internal mac address change */
		अगर (priv->bss_type == MWIFIEX_BSS_TYPE_ANY)
			वापस -EOPNOTSUPP;

		mac_addr = old_mac_addr;

		अगर (priv->bss_type == MWIFIEX_BSS_TYPE_P2P) अणु
			mac_addr |= BIT_ULL(MWIFIEX_MAC_LOCAL_ADMIN_BIT);
			mac_addr += priv->bss_num;
		पूर्ण अन्यथा अगर (priv->adapter->priv[0] != priv) अणु
			/* Set mac address based on bss_type/bss_num */
			mac_addr ^= BIT_ULL(priv->bss_type + 8);
			mac_addr += priv->bss_num;
		पूर्ण
	पूर्ण

	u64_to_ether_addr(mac_addr, priv->curr_addr);

	/* Send request to firmware */
	ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_MAC_ADDRESS,
			       HostCmd_ACT_GEN_SET, 0, शून्य, true);

	अगर (ret) अणु
		u64_to_ether_addr(old_mac_addr, priv->curr_addr);
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "set mac address failed: ret=%d\n", ret);
		वापस ret;
	पूर्ण

	ether_addr_copy(dev->dev_addr, priv->curr_addr);
	वापस 0;
पूर्ण

/* CFG802.11 network device handler क्रम setting MAC address.
 */
अटल पूर्णांक
mwअगरiex_nकरो_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);
	काष्ठा sockaddr *hw_addr = addr;

	वापस mwअगरiex_set_mac_address(priv, dev, true, hw_addr->sa_data);
पूर्ण

/*
 * CFG802.11 network device handler क्रम setting multicast list.
 */
अटल व्योम mwअगरiex_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);
	काष्ठा mwअगरiex_multicast_list mcast_list;

	अगर (dev->flags & IFF_PROMISC) अणु
		mcast_list.mode = MWIFIEX_PROMISC_MODE;
	पूर्ण अन्यथा अगर (dev->flags & IFF_ALLMULTI ||
		   netdev_mc_count(dev) > MWIFIEX_MAX_MULTICAST_LIST_SIZE) अणु
		mcast_list.mode = MWIFIEX_ALL_MULTI_MODE;
	पूर्ण अन्यथा अणु
		mcast_list.mode = MWIFIEX_MULTICAST_MODE;
		mcast_list.num_multicast_addr =
			mwअगरiex_copy_mcast_addr(&mcast_list, dev);
	पूर्ण
	mwअगरiex_request_set_multicast_list(priv, &mcast_list);
पूर्ण

/*
 * CFG802.11 network device handler क्रम transmission समयout.
 */
अटल व्योम
mwअगरiex_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);

	priv->num_tx_समयout++;
	priv->tx_समयout_cnt++;
	mwअगरiex_dbg(priv->adapter, ERROR,
		    "%lu : Tx timeout(#%d), bss_type-num = %d-%d\n",
		    jअगरfies, priv->tx_समयout_cnt, priv->bss_type,
		    priv->bss_num);
	mwअगरiex_set_trans_start(dev);

	अगर (priv->tx_समयout_cnt > TX_TIMEOUT_THRESHOLD &&
	    priv->adapter->अगर_ops.card_reset) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "tx_timeout_cnt exceeds threshold.\t"
			    "Triggering card reset!\n");
		priv->adapter->अगर_ops.card_reset(priv->adapter);
	पूर्ण
पूर्ण

व्योम mwअगरiex_multi_chan_resync(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा usb_card_rec *card = adapter->card;
	काष्ठा mwअगरiex_निजी *priv;
	u16 tx_buf_size;
	पूर्णांक i, ret;

	card->mc_resync_flag = true;
	क्रम (i = 0; i < MWIFIEX_TX_DATA_PORT; i++) अणु
		अगर (atomic_पढ़ो(&card->port[i].tx_data_urb_pending)) अणु
			mwअगरiex_dbg(adapter, WARN, "pending data urb in sys\n");
			वापस;
		पूर्ण
	पूर्ण

	card->mc_resync_flag = false;
	tx_buf_size = 0xffff;
	priv = mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);
	ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_RECONFIGURE_TX_BUFF,
			       HostCmd_ACT_GEN_SET, 0, &tx_buf_size, false);
	अगर (ret)
		mwअगरiex_dbg(adapter, ERROR,
			    "send reconfig tx buf size cmd err\n");
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_multi_chan_resync);

व्योम mwअगरiex_upload_device_dump(काष्ठा mwअगरiex_adapter *adapter)
अणु
	/* Dump all the memory data पूर्णांकo single file, a userspace script will
	 * be used to split all the memory data to multiple files
	 */
	mwअगरiex_dbg(adapter, MSG,
		    "== mwifiex dump information to /sys/class/devcoredump start\n");
	dev_coredumpv(adapter->dev, adapter->devdump_data, adapter->devdump_len,
		      GFP_KERNEL);
	mwअगरiex_dbg(adapter, MSG,
		    "== mwifiex dump information to /sys/class/devcoredump end\n");

	/* Device dump data will be मुक्तd in device coredump release function
	 * after 5 min. Here reset adapter->devdump_data and ->devdump_len
	 * to aव्योम it been accidentally reused.
	 */
	adapter->devdump_data = शून्य;
	adapter->devdump_len = 0;
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_upload_device_dump);

व्योम mwअगरiex_drv_info_dump(काष्ठा mwअगरiex_adapter *adapter)
अणु
	अक्षर *p;
	अक्षर drv_version[64];
	काष्ठा usb_card_rec *cardp;
	काष्ठा sdio_mmc_card *sdio_card;
	काष्ठा mwअगरiex_निजी *priv;
	पूर्णांक i, idx;
	काष्ठा netdev_queue *txq;
	काष्ठा mwअगरiex_debug_info *debug_info;

	mwअगरiex_dbg(adapter, MSG, "===mwifiex driverinfo dump start===\n");

	p = adapter->devdump_data;
	म_नकल(p, "========Start dump driverinfo========\n");
	p += म_माप("========Start dump driverinfo========\n");
	p += प्र_लिखो(p, "driver_name = " "\"mwifiex\"\n");

	mwअगरiex_drv_get_driver_version(adapter, drv_version,
				       माप(drv_version) - 1);
	p += प्र_लिखो(p, "driver_version = %s\n", drv_version);

	अगर (adapter->अगरace_type == MWIFIEX_USB) अणु
		cardp = (काष्ठा usb_card_rec *)adapter->card;
		p += प्र_लिखो(p, "tx_cmd_urb_pending = %d\n",
			     atomic_पढ़ो(&cardp->tx_cmd_urb_pending));
		p += प्र_लिखो(p, "tx_data_urb_pending_port_0 = %d\n",
			     atomic_पढ़ो(&cardp->port[0].tx_data_urb_pending));
		p += प्र_लिखो(p, "tx_data_urb_pending_port_1 = %d\n",
			     atomic_पढ़ो(&cardp->port[1].tx_data_urb_pending));
		p += प्र_लिखो(p, "rx_cmd_urb_pending = %d\n",
			     atomic_पढ़ो(&cardp->rx_cmd_urb_pending));
		p += प्र_लिखो(p, "rx_data_urb_pending = %d\n",
			     atomic_पढ़ो(&cardp->rx_data_urb_pending));
	पूर्ण

	p += प्र_लिखो(p, "tx_pending = %d\n",
		     atomic_पढ़ो(&adapter->tx_pending));
	p += प्र_लिखो(p, "rx_pending = %d\n",
		     atomic_पढ़ो(&adapter->rx_pending));

	अगर (adapter->अगरace_type == MWIFIEX_SDIO) अणु
		sdio_card = (काष्ठा sdio_mmc_card *)adapter->card;
		p += प्र_लिखो(p, "\nmp_rd_bitmap=0x%x curr_rd_port=0x%x\n",
			     sdio_card->mp_rd_biपंचांगap, sdio_card->curr_rd_port);
		p += प्र_लिखो(p, "mp_wr_bitmap=0x%x curr_wr_port=0x%x\n",
			     sdio_card->mp_wr_biपंचांगap, sdio_card->curr_wr_port);
	पूर्ण

	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		अगर (!adapter->priv[i] || !adapter->priv[i]->netdev)
			जारी;
		priv = adapter->priv[i];
		p += प्र_लिखो(p, "\n[interface  : \"%s\"]\n",
			     priv->netdev->name);
		p += प्र_लिखो(p, "wmm_tx_pending[0] = %d\n",
			     atomic_पढ़ो(&priv->wmm_tx_pending[0]));
		p += प्र_लिखो(p, "wmm_tx_pending[1] = %d\n",
			     atomic_पढ़ो(&priv->wmm_tx_pending[1]));
		p += प्र_लिखो(p, "wmm_tx_pending[2] = %d\n",
			     atomic_पढ़ो(&priv->wmm_tx_pending[2]));
		p += प्र_लिखो(p, "wmm_tx_pending[3] = %d\n",
			     atomic_पढ़ो(&priv->wmm_tx_pending[3]));
		p += प्र_लिखो(p, "media_state=\"%s\"\n", !priv->media_connected ?
			     "Disconnected" : "Connected");
		p += प्र_लिखो(p, "carrier %s\n", (netअगर_carrier_ok(priv->netdev)
			     ? "on" : "off"));
		क्रम (idx = 0; idx < priv->netdev->num_tx_queues; idx++) अणु
			txq = netdev_get_tx_queue(priv->netdev, idx);
			p += प्र_लिखो(p, "tx queue %d:%s  ", idx,
				     netअगर_tx_queue_stopped(txq) ?
				     "stopped" : "started");
		पूर्ण
		p += प्र_लिखो(p, "\n%s: num_tx_timeout = %d\n",
			     priv->netdev->name, priv->num_tx_समयout);
	पूर्ण

	अगर (adapter->अगरace_type == MWIFIEX_SDIO ||
	    adapter->अगरace_type == MWIFIEX_PCIE) अणु
		p += प्र_लिखो(p, "\n=== %s register dump===\n",
			     adapter->अगरace_type == MWIFIEX_SDIO ?
							"SDIO" : "PCIE");
		अगर (adapter->अगर_ops.reg_dump)
			p += adapter->अगर_ops.reg_dump(adapter, p);
	पूर्ण
	p += प्र_लिखो(p, "\n=== more debug information\n");
	debug_info = kzalloc(माप(*debug_info), GFP_KERNEL);
	अगर (debug_info) अणु
		क्रम (i = 0; i < adapter->priv_num; i++) अणु
			अगर (!adapter->priv[i] || !adapter->priv[i]->netdev)
				जारी;
			priv = adapter->priv[i];
			mwअगरiex_get_debug_info(priv, debug_info);
			p += mwअगरiex_debug_info_to_buffer(priv, p, debug_info);
			अवरोध;
		पूर्ण
		kमुक्त(debug_info);
	पूर्ण

	म_नकल(p, "\n========End dump========\n");
	p += म_माप("\n========End dump========\n");
	mwअगरiex_dbg(adapter, MSG, "===mwifiex driverinfo dump end===\n");
	adapter->devdump_len = p - (अक्षर *)adapter->devdump_data;
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_drv_info_dump);

व्योम mwअगरiex_prepare_fw_dump_info(काष्ठा mwअगरiex_adapter *adapter)
अणु
	u8 idx;
	अक्षर *fw_dump_ptr;
	u32 dump_len = 0;

	क्रम (idx = 0; idx < adapter->num_mem_types; idx++) अणु
		काष्ठा memory_type_mapping *entry =
				&adapter->mem_type_mapping_tbl[idx];

		अगर (entry->mem_ptr) अणु
			dump_len += (म_माप("========Start dump ") +
					म_माप(entry->mem_name) +
					म_माप("========\n") +
					(entry->mem_size + 1) +
					म_माप("\n========End dump========\n"));
		पूर्ण
	पूर्ण

	अगर (dump_len + 1 + adapter->devdump_len > MWIFIEX_FW_DUMP_SIZE) अणु
		/* Realloc in हाल buffer overflow */
		fw_dump_ptr = vzalloc(dump_len + 1 + adapter->devdump_len);
		mwअगरiex_dbg(adapter, MSG, "Realloc device dump data.\n");
		अगर (!fw_dump_ptr) अणु
			vमुक्त(adapter->devdump_data);
			mwअगरiex_dbg(adapter, ERROR,
				    "vzalloc devdump data failure!\n");
			वापस;
		पूर्ण

		स_हटाओ(fw_dump_ptr, adapter->devdump_data,
			adapter->devdump_len);
		vमुक्त(adapter->devdump_data);
		adapter->devdump_data = fw_dump_ptr;
	पूर्ण

	fw_dump_ptr = (अक्षर *)adapter->devdump_data + adapter->devdump_len;

	क्रम (idx = 0; idx < adapter->num_mem_types; idx++) अणु
		काष्ठा memory_type_mapping *entry =
					&adapter->mem_type_mapping_tbl[idx];

		अगर (entry->mem_ptr) अणु
			म_नकल(fw_dump_ptr, "========Start dump ");
			fw_dump_ptr += म_माप("========Start dump ");

			म_नकल(fw_dump_ptr, entry->mem_name);
			fw_dump_ptr += म_माप(entry->mem_name);

			म_नकल(fw_dump_ptr, "========\n");
			fw_dump_ptr += म_माप("========\n");

			स_नकल(fw_dump_ptr, entry->mem_ptr, entry->mem_size);
			fw_dump_ptr += entry->mem_size;

			म_नकल(fw_dump_ptr, "\n========End dump========\n");
			fw_dump_ptr += म_माप("\n========End dump========\n");
		पूर्ण
	पूर्ण

	adapter->devdump_len = fw_dump_ptr - (अक्षर *)adapter->devdump_data;

	क्रम (idx = 0; idx < adapter->num_mem_types; idx++) अणु
		काष्ठा memory_type_mapping *entry =
			&adapter->mem_type_mapping_tbl[idx];

		vमुक्त(entry->mem_ptr);
		entry->mem_ptr = शून्य;
		entry->mem_size = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_prepare_fw_dump_info);

/*
 * CFG802.11 network device handler क्रम statistics retrieval.
 */
अटल काष्ठा net_device_stats *mwअगरiex_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);

	वापस &priv->stats;
पूर्ण

अटल u16
mwअगरiex_netdev_select_wmm_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
				काष्ठा net_device *sb_dev)
अणु
	skb->priority = cfg80211_classअगरy8021d(skb, शून्य);
	वापस mwअगरiex_1d_to_wmm_queue[skb->priority];
पूर्ण

/* Network device handlers */
अटल स्थिर काष्ठा net_device_ops mwअगरiex_netdev_ops = अणु
	.nकरो_खोलो = mwअगरiex_खोलो,
	.nकरो_stop = mwअगरiex_बंद,
	.nकरो_start_xmit = mwअगरiex_hard_start_xmit,
	.nकरो_set_mac_address = mwअगरiex_nकरो_set_mac_address,
	.nकरो_validate_addr = eth_validate_addr,
	.nकरो_tx_समयout = mwअगरiex_tx_समयout,
	.nकरो_get_stats = mwअगरiex_get_stats,
	.nकरो_set_rx_mode = mwअगरiex_set_multicast_list,
	.nकरो_select_queue = mwअगरiex_netdev_select_wmm_queue,
पूर्ण;

/*
 * This function initializes the निजी काष्ठाure parameters.
 *
 * The following रुको queues are initialized -
 *      - IOCTL रुको queue
 *      - Command रुको queue
 *      - Statistics रुको queue
 *
 * ...and the following शेष parameters are set -
 *      - Current key index     : Set to 0
 *      - Rate index            : Set to स्वतः
 *      - Media connected       : Set to disconnected
 *      - Adhoc link sensed     : Set to false
 *      - Nick name             : Set to null
 *      - Number of Tx समयout  : Set to 0
 *      - Device address        : Set to current address
 *      - Rx histogram statistc : Set to 0
 *
 * In addition, the CFG80211 work queue is also created.
 */
व्योम mwअगरiex_init_priv_params(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा net_device *dev)
अणु
	dev->netdev_ops = &mwअगरiex_netdev_ops;
	dev->needs_मुक्त_netdev = true;
	/* Initialize निजी काष्ठाure */
	priv->current_key_index = 0;
	priv->media_connected = false;
	स_रखो(priv->mgmt_ie, 0,
	       माप(काष्ठा mwअगरiex_ie) * MAX_MGMT_IE_INDEX);
	priv->beacon_idx = MWIFIEX_AUTO_IDX_MASK;
	priv->proberesp_idx = MWIFIEX_AUTO_IDX_MASK;
	priv->assocresp_idx = MWIFIEX_AUTO_IDX_MASK;
	priv->gen_idx = MWIFIEX_AUTO_IDX_MASK;
	priv->num_tx_समयout = 0;
	अगर (is_valid_ether_addr(dev->dev_addr))
		ether_addr_copy(priv->curr_addr, dev->dev_addr);
	अन्यथा
		ether_addr_copy(priv->curr_addr, priv->adapter->perm_addr);

	अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA ||
	    GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_UAP) अणु
		priv->hist_data = kदो_स्मृति(माप(*priv->hist_data), GFP_KERNEL);
		अगर (priv->hist_data)
			mwअगरiex_hist_data_reset(priv);
	पूर्ण
पूर्ण

/*
 * This function check अगर command is pending.
 */
पूर्णांक is_command_pending(काष्ठा mwअगरiex_adapter *adapter)
अणु
	पूर्णांक is_cmd_pend_q_empty;

	spin_lock_bh(&adapter->cmd_pending_q_lock);
	is_cmd_pend_q_empty = list_empty(&adapter->cmd_pending_q);
	spin_unlock_bh(&adapter->cmd_pending_q_lock);

	वापस !is_cmd_pend_q_empty;
पूर्ण

/*
 * This is the RX work queue function.
 *
 * It handles the RX operations.
 */
अटल व्योम mwअगरiex_rx_work_queue(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mwअगरiex_adapter *adapter =
		container_of(work, काष्ठा mwअगरiex_adapter, rx_work);

	अगर (test_bit(MWIFIEX_SURPRISE_REMOVED, &adapter->work_flags))
		वापस;
	mwअगरiex_process_rx(adapter);
पूर्ण

/*
 * This is the मुख्य work queue function.
 *
 * It handles the मुख्य process, which in turn handles the complete
 * driver operations.
 */
अटल व्योम mwअगरiex_मुख्य_work_queue(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mwअगरiex_adapter *adapter =
		container_of(work, काष्ठा mwअगरiex_adapter, मुख्य_work);

	अगर (test_bit(MWIFIEX_SURPRISE_REMOVED, &adapter->work_flags))
		वापस;
	mwअगरiex_मुख्य_process(adapter);
पूर्ण

/* Common tearकरोwn code used क्रम both device removal and reset */
अटल व्योम mwअगरiex_uninit_sw(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा mwअगरiex_निजी *priv;
	पूर्णांक i;

	/* We can no दीर्घer handle पूर्णांकerrupts once we start करोing the tearकरोwn
	 * below.
	 */
	अगर (adapter->अगर_ops.disable_पूर्णांक)
		adapter->अगर_ops.disable_पूर्णांक(adapter);

	set_bit(MWIFIEX_SURPRISE_REMOVED, &adapter->work_flags);
	mwअगरiex_terminate_workqueue(adapter);
	adapter->पूर्णांक_status = 0;

	/* Stop data */
	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		priv = adapter->priv[i];
		अगर (priv && priv->netdev) अणु
			mwअगरiex_stop_net_dev_queue(priv->netdev, adapter);
			अगर (netअगर_carrier_ok(priv->netdev))
				netअगर_carrier_off(priv->netdev);
			netअगर_device_detach(priv->netdev);
		पूर्ण
	पूर्ण

	mwअगरiex_dbg(adapter, CMD, "cmd: calling mwifiex_shutdown_drv...\n");
	mwअगरiex_shutकरोwn_drv(adapter);
	mwअगरiex_dbg(adapter, CMD, "cmd: mwifiex_shutdown_drv done\n");

	अगर (atomic_पढ़ो(&adapter->rx_pending) ||
	    atomic_पढ़ो(&adapter->tx_pending) ||
	    atomic_पढ़ो(&adapter->cmd_pending)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "rx_pending=%d, tx_pending=%d,\t"
			    "cmd_pending=%d\n",
			    atomic_पढ़ो(&adapter->rx_pending),
			    atomic_पढ़ो(&adapter->tx_pending),
			    atomic_पढ़ो(&adapter->cmd_pending));
	पूर्ण

	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		priv = adapter->priv[i];
		अगर (!priv)
			जारी;
		rtnl_lock();
		wiphy_lock(adapter->wiphy);
		अगर (priv->netdev &&
		    priv->wdev.अगरtype != NL80211_IFTYPE_UNSPECIFIED)
			mwअगरiex_del_भव_पूर्णांकf(adapter->wiphy, &priv->wdev);
		wiphy_unlock(adapter->wiphy);
		rtnl_unlock();
	पूर्ण

	wiphy_unरेजिस्टर(adapter->wiphy);
	wiphy_मुक्त(adapter->wiphy);
	adapter->wiphy = शून्य;

	vमुक्त(adapter->chan_stats);
	mwअगरiex_मुक्त_cmd_buffers(adapter);
पूर्ण

/*
 * This function can be used क्रम shutting करोwn the adapter SW.
 */
पूर्णांक mwअगरiex_shutकरोwn_sw(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा mwअगरiex_निजी *priv;

	अगर (!adapter)
		वापस 0;

	रुको_क्रम_completion(adapter->fw_करोne);
	/* Caller should ensure we aren't suspending जबतक this happens */
	reinit_completion(adapter->fw_करोne);

	priv = mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);
	mwअगरiex_deauthenticate(priv, शून्य);

	mwअगरiex_init_shutकरोwn_fw(priv, MWIFIEX_FUNC_SHUTDOWN);

	mwअगरiex_uninit_sw(adapter);
	adapter->is_up = false;

	अगर (adapter->अगर_ops.करोwn_dev)
		adapter->अगर_ops.करोwn_dev(adapter);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_shutकरोwn_sw);

/* This function can be used क्रम reinitting the adapter SW. Required
 * code is extracted from mwअगरiex_add_card()
 */
पूर्णांक
mwअगरiex_reinit_sw(काष्ठा mwअगरiex_adapter *adapter)
अणु
	पूर्णांक ret;

	mwअगरiex_init_lock_list(adapter);
	अगर (adapter->अगर_ops.up_dev)
		adapter->अगर_ops.up_dev(adapter);

	adapter->hw_status = MWIFIEX_HW_STATUS_INITIALIZING;
	clear_bit(MWIFIEX_SURPRISE_REMOVED, &adapter->work_flags);
	init_रुकोqueue_head(&adapter->init_रुको_q);
	clear_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags);
	adapter->hs_activated = false;
	clear_bit(MWIFIEX_IS_CMD_TIMEDOUT, &adapter->work_flags);
	init_रुकोqueue_head(&adapter->hs_activate_रुको_q);
	init_रुकोqueue_head(&adapter->cmd_रुको_q.रुको);
	adapter->cmd_रुको_q.status = 0;
	adapter->scan_रुको_q_woken = false;

	अगर ((num_possible_cpus() > 1) || adapter->अगरace_type == MWIFIEX_USB)
		adapter->rx_work_enabled = true;

	adapter->workqueue =
		alloc_workqueue("MWIFIEX_WORK_QUEUE",
				WQ_HIGHPRI | WQ_MEM_RECLAIM | WQ_UNBOUND, 1);
	अगर (!adapter->workqueue)
		जाओ err_kदो_स्मृति;

	INIT_WORK(&adapter->मुख्य_work, mwअगरiex_मुख्य_work_queue);

	अगर (adapter->rx_work_enabled) अणु
		adapter->rx_workqueue = alloc_workqueue("MWIFIEX_RX_WORK_QUEUE",
							WQ_HIGHPRI |
							WQ_MEM_RECLAIM |
							WQ_UNBOUND, 1);
		अगर (!adapter->rx_workqueue)
			जाओ err_kदो_स्मृति;
		INIT_WORK(&adapter->rx_work, mwअगरiex_rx_work_queue);
	पूर्ण

	/* Register the device. Fill up the निजी data काष्ठाure with
	 * relevant inक्रमmation from the card. Some code extracted from
	 * mwअगरiex_रेजिस्टर_dev()
	 */
	mwअगरiex_dbg(adapter, INFO, "%s, mwifiex_init_hw_fw()...\n", __func__);

	अगर (mwअगरiex_init_hw_fw(adapter, false)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: firmware init failed\n", __func__);
		जाओ err_init_fw;
	पूर्ण

	/* _mwअगरiex_fw_dpc() करोes its own cleanup */
	ret = _mwअगरiex_fw_dpc(adapter->firmware, adapter);
	अगर (ret) अणु
		pr_err("Failed to bring up adapter: %d\n", ret);
		वापस ret;
	पूर्ण
	mwअगरiex_dbg(adapter, INFO, "%s, successful\n", __func__);

	वापस 0;

err_init_fw:
	mwअगरiex_dbg(adapter, ERROR, "info: %s: unregister device\n", __func__);
	अगर (adapter->अगर_ops.unरेजिस्टर_dev)
		adapter->अगर_ops.unरेजिस्टर_dev(adapter);

err_kदो_स्मृति:
	set_bit(MWIFIEX_SURPRISE_REMOVED, &adapter->work_flags);
	mwअगरiex_terminate_workqueue(adapter);
	अगर (adapter->hw_status == MWIFIEX_HW_STATUS_READY) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "info: %s: shutdown mwifiex\n", __func__);
		mwअगरiex_shutकरोwn_drv(adapter);
		mwअगरiex_मुक्त_cmd_buffers(adapter);
	पूर्ण

	complete_all(adapter->fw_करोne);
	mwअगरiex_dbg(adapter, INFO, "%s, error\n", __func__);

	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_reinit_sw);

अटल irqवापस_t mwअगरiex_irq_wakeup_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv;

	dev_dbg(adapter->dev, "%s: wake by wifi", __func__);
	adapter->wake_by_wअगरi = true;
	disable_irq_nosync(irq);

	/* Notअगरy PM core we are wakeup source */
	pm_wakeup_event(adapter->dev, 0);
	pm_प्रणाली_wakeup();

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mwअगरiex_probe_of(काष्ठा mwअगरiex_adapter *adapter)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = adapter->dev;

	अगर (!dev->of_node)
		जाओ err_निकास;

	adapter->dt_node = dev->of_node;
	adapter->irq_wakeup = irq_of_parse_and_map(adapter->dt_node, 0);
	अगर (!adapter->irq_wakeup) अणु
		dev_dbg(dev, "fail to parse irq_wakeup from device tree\n");
		जाओ err_निकास;
	पूर्ण

	ret = devm_request_irq(dev, adapter->irq_wakeup,
			       mwअगरiex_irq_wakeup_handler, IRQF_TRIGGER_LOW,
			       "wifi_wake", adapter);
	अगर (ret) अणु
		dev_err(dev, "Failed to request irq_wakeup %d (%d)\n",
			adapter->irq_wakeup, ret);
		जाओ err_निकास;
	पूर्ण

	disable_irq(adapter->irq_wakeup);
	अगर (device_init_wakeup(dev, true)) अणु
		dev_err(dev, "fail to init wakeup for mwifiex\n");
		जाओ err_निकास;
	पूर्ण
	वापस;

err_निकास:
	adapter->irq_wakeup = -1;
पूर्ण

/*
 * This function adds the card.
 *
 * This function follows the following major steps to set up the device -
 *      - Initialize software. This includes probing the card, रेजिस्टरing
 *        the पूर्णांकerface operations table, and allocating/initializing the
 *        adapter काष्ठाure
 *      - Set up the netlink socket
 *      - Create and start the मुख्य work queue
 *      - Register the device
 *      - Initialize firmware and hardware
 *      - Add logical पूर्णांकerfaces
 */
पूर्णांक
mwअगरiex_add_card(व्योम *card, काष्ठा completion *fw_करोne,
		 काष्ठा mwअगरiex_अगर_ops *अगर_ops, u8 अगरace_type,
		 काष्ठा device *dev)
अणु
	काष्ठा mwअगरiex_adapter *adapter;

	अगर (mwअगरiex_रेजिस्टर(card, dev, अगर_ops, (व्योम **)&adapter)) अणु
		pr_err("%s: software init failed\n", __func__);
		जाओ err_init_sw;
	पूर्ण

	mwअगरiex_probe_of(adapter);

	adapter->अगरace_type = अगरace_type;
	adapter->fw_करोne = fw_करोne;

	adapter->hw_status = MWIFIEX_HW_STATUS_INITIALIZING;
	clear_bit(MWIFIEX_SURPRISE_REMOVED, &adapter->work_flags);
	init_रुकोqueue_head(&adapter->init_रुको_q);
	clear_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags);
	adapter->hs_activated = false;
	init_रुकोqueue_head(&adapter->hs_activate_रुको_q);
	init_रुकोqueue_head(&adapter->cmd_रुको_q.रुको);
	adapter->cmd_रुको_q.status = 0;
	adapter->scan_रुको_q_woken = false;

	अगर ((num_possible_cpus() > 1) || adapter->अगरace_type == MWIFIEX_USB)
		adapter->rx_work_enabled = true;

	adapter->workqueue =
		alloc_workqueue("MWIFIEX_WORK_QUEUE",
				WQ_HIGHPRI | WQ_MEM_RECLAIM | WQ_UNBOUND, 1);
	अगर (!adapter->workqueue)
		जाओ err_kदो_स्मृति;

	INIT_WORK(&adapter->मुख्य_work, mwअगरiex_मुख्य_work_queue);

	अगर (adapter->rx_work_enabled) अणु
		adapter->rx_workqueue = alloc_workqueue("MWIFIEX_RX_WORK_QUEUE",
							WQ_HIGHPRI |
							WQ_MEM_RECLAIM |
							WQ_UNBOUND, 1);
		अगर (!adapter->rx_workqueue)
			जाओ err_kदो_स्मृति;

		INIT_WORK(&adapter->rx_work, mwअगरiex_rx_work_queue);
	पूर्ण

	/* Register the device. Fill up the निजी data काष्ठाure with relevant
	   inक्रमmation from the card. */
	अगर (adapter->अगर_ops.रेजिस्टर_dev(adapter)) अणु
		pr_err("%s: failed to register mwifiex device\n", __func__);
		जाओ err_रेजिस्टरdev;
	पूर्ण

	अगर (mwअगरiex_init_hw_fw(adapter, true)) अणु
		pr_err("%s: firmware init failed\n", __func__);
		जाओ err_init_fw;
	पूर्ण

	वापस 0;

err_init_fw:
	pr_debug("info: %s: unregister device\n", __func__);
	अगर (adapter->अगर_ops.unरेजिस्टर_dev)
		adapter->अगर_ops.unरेजिस्टर_dev(adapter);
err_रेजिस्टरdev:
	set_bit(MWIFIEX_SURPRISE_REMOVED, &adapter->work_flags);
	mwअगरiex_terminate_workqueue(adapter);
	अगर (adapter->hw_status == MWIFIEX_HW_STATUS_READY) अणु
		pr_debug("info: %s: shutdown mwifiex\n", __func__);
		mwअगरiex_shutकरोwn_drv(adapter);
		mwअगरiex_मुक्त_cmd_buffers(adapter);
	पूर्ण
err_kदो_स्मृति:
	अगर (adapter->irq_wakeup >= 0)
		device_init_wakeup(adapter->dev, false);
	mwअगरiex_मुक्त_adapter(adapter);

err_init_sw:

	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_add_card);

/*
 * This function हटाओs the card.
 *
 * This function follows the following major steps to हटाओ the device -
 *      - Stop data traffic
 *      - Shutकरोwn firmware
 *      - Remove the logical पूर्णांकerfaces
 *      - Terminate the work queue
 *      - Unरेजिस्टर the device
 *      - Free the adapter काष्ठाure
 */
पूर्णांक mwअगरiex_हटाओ_card(काष्ठा mwअगरiex_adapter *adapter)
अणु
	अगर (!adapter)
		वापस 0;

	अगर (adapter->is_up)
		mwअगरiex_uninit_sw(adapter);

	अगर (adapter->irq_wakeup >= 0)
		device_init_wakeup(adapter->dev, false);

	/* Unरेजिस्टर device */
	mwअगरiex_dbg(adapter, INFO,
		    "info: unregister device\n");
	अगर (adapter->अगर_ops.unरेजिस्टर_dev)
		adapter->अगर_ops.unरेजिस्टर_dev(adapter);
	/* Free adapter काष्ठाure */
	mwअगरiex_dbg(adapter, INFO,
		    "info: free adapter\n");
	mwअगरiex_मुक्त_adapter(adapter);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_हटाओ_card);

व्योम _mwअगरiex_dbg(स्थिर काष्ठा mwअगरiex_adapter *adapter, पूर्णांक mask,
		  स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (!(adapter->debug_mask & mask))
		वापस;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (adapter->dev)
		dev_info(adapter->dev, "%pV", &vaf);
	अन्यथा
		pr_info("%pV", &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL_GPL(_mwअगरiex_dbg);

/*
 * This function initializes the module.
 *
 * The debug FS is also initialized अगर configured.
 */
अटल पूर्णांक
mwअगरiex_init_module(व्योम)
अणु
#अगर_घोषित CONFIG_DEBUG_FS
	mwअगरiex_debugfs_init();
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * This function cleans up the module.
 *
 * The debug FS is हटाओd अगर available.
 */
अटल व्योम
mwअगरiex_cleanup_module(व्योम)
अणु
#अगर_घोषित CONFIG_DEBUG_FS
	mwअगरiex_debugfs_हटाओ();
#पूर्ण_अगर
पूर्ण

module_init(mwअगरiex_init_module);
module_निकास(mwअगरiex_cleanup_module);

MODULE_AUTHOR("Marvell International Ltd.");
MODULE_DESCRIPTION("Marvell WiFi-Ex Driver version " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL v2");
