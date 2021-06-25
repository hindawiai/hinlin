<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Implementation of chip-to-host event (aka indications) of WFxxx Split Mac
 * (WSM) API.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 */
#समावेश <linux/skbuff.h>
#समावेश <linux/etherdevice.h>

#समावेश "hif_rx.h"
#समावेश "wfx.h"
#समावेश "scan.h"
#समावेश "bh.h"
#समावेश "sta.h"
#समावेश "data_rx.h"
#समावेश "hif_api_cmd.h"

अटल पूर्णांक hअगर_generic_confirm(काष्ठा wfx_dev *wdev,
			       स्थिर काष्ठा hअगर_msg *hअगर, स्थिर व्योम *buf)
अणु
	// All confirm messages start with status
	पूर्णांक status = le32_to_cpup((__le32 *)buf);
	पूर्णांक cmd = hअगर->id;
	पूर्णांक len = le16_to_cpu(hअगर->len) - 4; // drop header

	WARN(!mutex_is_locked(&wdev->hअगर_cmd.lock), "data locking error");

	अगर (!wdev->hअगर_cmd.buf_send) अणु
		dev_warn(wdev->dev, "unexpected confirmation: 0x%.2x\n", cmd);
		वापस -EINVAL;
	पूर्ण

	अगर (cmd != wdev->hअगर_cmd.buf_send->id) अणु
		dev_warn(wdev->dev,
			 "chip response mismatch request: 0x%.2x vs 0x%.2x\n",
			 cmd, wdev->hअगर_cmd.buf_send->id);
		वापस -EINVAL;
	पूर्ण

	अगर (wdev->hअगर_cmd.buf_recv) अणु
		अगर (wdev->hअगर_cmd.len_recv >= len && len > 0)
			स_नकल(wdev->hअगर_cmd.buf_recv, buf, len);
		अन्यथा
			status = -EIO;
	पूर्ण
	wdev->hअगर_cmd.ret = status;

	complete(&wdev->hअगर_cmd.करोne);
	वापस status;
पूर्ण

अटल पूर्णांक hअगर_tx_confirm(काष्ठा wfx_dev *wdev,
			  स्थिर काष्ठा hअगर_msg *hअगर, स्थिर व्योम *buf)
अणु
	स्थिर काष्ठा hअगर_cnf_tx *body = buf;

	wfx_tx_confirm_cb(wdev, body);
	वापस 0;
पूर्ण

अटल पूर्णांक hअगर_multi_tx_confirm(काष्ठा wfx_dev *wdev,
				स्थिर काष्ठा hअगर_msg *hअगर, स्थिर व्योम *buf)
अणु
	स्थिर काष्ठा hअगर_cnf_multi_transmit *body = buf;
	पूर्णांक i;

	WARN(body->num_tx_confs <= 0, "corrupted message");
	क्रम (i = 0; i < body->num_tx_confs; i++)
		wfx_tx_confirm_cb(wdev, &body->tx_conf_payload[i]);
	वापस 0;
पूर्ण

अटल पूर्णांक hअगर_startup_indication(काष्ठा wfx_dev *wdev,
				  स्थिर काष्ठा hअगर_msg *hअगर, स्थिर व्योम *buf)
अणु
	स्थिर काष्ठा hअगर_ind_startup *body = buf;

	अगर (body->status || body->firmware_type > 4) अणु
		dev_err(wdev->dev, "received invalid startup indication");
		वापस -EINVAL;
	पूर्ण
	स_नकल(&wdev->hw_caps, body, माप(काष्ठा hअगर_ind_startup));
	le16_to_cpus((__le16 *)&wdev->hw_caps.hardware_id);
	le16_to_cpus((__le16 *)&wdev->hw_caps.num_inp_ch_bufs);
	le16_to_cpus((__le16 *)&wdev->hw_caps.size_inp_ch_buf);
	le32_to_cpus((__le32 *)&wdev->hw_caps.supported_rate_mask);

	complete(&wdev->firmware_पढ़ोy);
	वापस 0;
पूर्ण

अटल पूर्णांक hअगर_wakeup_indication(काष्ठा wfx_dev *wdev,
				 स्थिर काष्ठा hअगर_msg *hअगर, स्थिर व्योम *buf)
अणु
	अगर (!wdev->pdata.gpio_wakeup ||
	    gpiod_get_value(wdev->pdata.gpio_wakeup) == 0) अणु
		dev_warn(wdev->dev, "unexpected wake-up indication\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hअगर_receive_indication(काष्ठा wfx_dev *wdev,
				  स्थिर काष्ठा hअगर_msg *hअगर,
				  स्थिर व्योम *buf, काष्ठा sk_buff *skb)
अणु
	काष्ठा wfx_vअगर *wvअगर = wdev_to_wvअगर(wdev, hअगर->पूर्णांकerface);
	स्थिर काष्ठा hअगर_ind_rx *body = buf;

	अगर (!wvअगर) अणु
		dev_warn(wdev->dev, "%s: ignore rx data for non-existent vif %d\n",
			 __func__, hअगर->पूर्णांकerface);
		वापस -EIO;
	पूर्ण
	skb_pull(skb, माप(काष्ठा hअगर_msg) + माप(काष्ठा hअगर_ind_rx));
	wfx_rx_cb(wvअगर, body, skb);

	वापस 0;
पूर्ण

अटल पूर्णांक hअगर_event_indication(काष्ठा wfx_dev *wdev,
				स्थिर काष्ठा hअगर_msg *hअगर, स्थिर व्योम *buf)
अणु
	काष्ठा wfx_vअगर *wvअगर = wdev_to_wvअगर(wdev, hअगर->पूर्णांकerface);
	स्थिर काष्ठा hअगर_ind_event *body = buf;
	पूर्णांक type = le32_to_cpu(body->event_id);

	अगर (!wvअगर) अणु
		dev_warn(wdev->dev, "%s: received event for non-existent vif\n", __func__);
		वापस -EIO;
	पूर्ण

	चयन (type) अणु
	हाल HIF_EVENT_IND_RCPI_RSSI:
		wfx_event_report_rssi(wvअगर, body->event_data.rcpi_rssi);
		अवरोध;
	हाल HIF_EVENT_IND_BSSLOST:
		schedule_delayed_work(&wvअगर->beacon_loss_work, 0);
		अवरोध;
	हाल HIF_EVENT_IND_BSSREGAINED:
		cancel_delayed_work(&wvअगर->beacon_loss_work);
		dev_dbg(wdev->dev, "ignore BSSREGAINED indication\n");
		अवरोध;
	हाल HIF_EVENT_IND_PS_MODE_ERROR:
		dev_warn(wdev->dev, "error while processing power save request: %d\n",
			 le32_to_cpu(body->event_data.ps_mode_error));
		अवरोध;
	शेष:
		dev_warn(wdev->dev, "unhandled event indication: %.2x\n",
			 type);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hअगर_pm_mode_complete_indication(काष्ठा wfx_dev *wdev,
					   स्थिर काष्ठा hअगर_msg *hअगर,
					   स्थिर व्योम *buf)
अणु
	काष्ठा wfx_vअगर *wvअगर = wdev_to_wvअगर(wdev, hअगर->पूर्णांकerface);

	अगर (!wvअगर) अणु
		dev_warn(wdev->dev, "%s: received event for non-existent vif\n", __func__);
		वापस -EIO;
	पूर्ण
	complete(&wvअगर->set_pm_mode_complete);

	वापस 0;
पूर्ण

अटल पूर्णांक hअगर_scan_complete_indication(काष्ठा wfx_dev *wdev,
					स्थिर काष्ठा hअगर_msg *hअगर,
					स्थिर व्योम *buf)
अणु
	काष्ठा wfx_vअगर *wvअगर = wdev_to_wvअगर(wdev, hअगर->पूर्णांकerface);

	अगर (!wvअगर) अणु
		dev_warn(wdev->dev, "%s: received event for non-existent vif\n", __func__);
		वापस -EIO;
	पूर्ण

	wfx_scan_complete(wvअगर);

	वापस 0;
पूर्ण

अटल पूर्णांक hअगर_join_complete_indication(काष्ठा wfx_dev *wdev,
					स्थिर काष्ठा hअगर_msg *hअगर,
					स्थिर व्योम *buf)
अणु
	काष्ठा wfx_vअगर *wvअगर = wdev_to_wvअगर(wdev, hअगर->पूर्णांकerface);

	अगर (!wvअगर) अणु
		dev_warn(wdev->dev, "%s: received event for non-existent vif\n", __func__);
		वापस -EIO;
	पूर्ण
	dev_warn(wdev->dev, "unattended JoinCompleteInd\n");

	वापस 0;
पूर्ण

अटल पूर्णांक hअगर_suspend_resume_indication(काष्ठा wfx_dev *wdev,
					 स्थिर काष्ठा hअगर_msg *hअगर,
					 स्थिर व्योम *buf)
अणु
	स्थिर काष्ठा hअगर_ind_suspend_resume_tx *body = buf;
	काष्ठा wfx_vअगर *wvअगर;

	अगर (body->bc_mc_only) अणु
		wvअगर = wdev_to_wvअगर(wdev, hअगर->पूर्णांकerface);
		अगर (!wvअगर) अणु
			dev_warn(wdev->dev, "%s: received event for non-existent vif\n", __func__);
			वापस -EIO;
		पूर्ण
		अगर (body->resume)
			wfx_suspend_resume_mc(wvअगर, STA_NOTIFY_AWAKE);
		अन्यथा
			wfx_suspend_resume_mc(wvअगर, STA_NOTIFY_SLEEP);
	पूर्ण अन्यथा अणु
		WARN(body->peer_sta_set, "misunderstood indication");
		WARN(hअगर->पूर्णांकerface != 2, "misunderstood indication");
		अगर (body->resume)
			wfx_suspend_hot_dev(wdev, STA_NOTIFY_AWAKE);
		अन्यथा
			wfx_suspend_hot_dev(wdev, STA_NOTIFY_SLEEP);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hअगर_generic_indication(काष्ठा wfx_dev *wdev,
				  स्थिर काष्ठा hअगर_msg *hअगर, स्थिर व्योम *buf)
अणु
	स्थिर काष्ठा hअगर_ind_generic *body = buf;
	पूर्णांक type = le32_to_cpu(body->type);

	चयन (type) अणु
	हाल HIF_GENERIC_INDICATION_TYPE_RAW:
		वापस 0;
	हाल HIF_GENERIC_INDICATION_TYPE_STRING:
		dev_info(wdev->dev, "firmware says: %s\n", (अक्षर *)&body->data);
		वापस 0;
	हाल HIF_GENERIC_INDICATION_TYPE_RX_STATS:
		mutex_lock(&wdev->rx_stats_lock);
		// Older firmware send a generic indication beside RxStats
		अगर (!wfx_api_older_than(wdev, 1, 4))
			dev_info(wdev->dev, "Rx test ongoing. Temperature: %d degrees C\n",
				 body->data.rx_stats.current_temp);
		स_नकल(&wdev->rx_stats, &body->data.rx_stats,
		       माप(wdev->rx_stats));
		mutex_unlock(&wdev->rx_stats_lock);
		वापस 0;
	हाल HIF_GENERIC_INDICATION_TYPE_TX_POWER_LOOP_INFO:
		mutex_lock(&wdev->tx_घातer_loop_info_lock);
		स_नकल(&wdev->tx_घातer_loop_info,
		       &body->data.tx_घातer_loop_info,
		       माप(wdev->tx_घातer_loop_info));
		mutex_unlock(&wdev->tx_घातer_loop_info_lock);
		वापस 0;
	शेष:
		dev_err(wdev->dev, "generic_indication: unknown indication type: %#.8x\n",
			type);
		वापस -EIO;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा अणु
	पूर्णांक val;
	स्थिर अक्षर *str;
	bool has_param;
पूर्ण hअगर_errors[] = अणु
	अणु HIF_ERROR_FIRMWARE_ROLLBACK,
		"rollback status" पूर्ण,
	अणु HIF_ERROR_FIRMWARE_DEBUG_ENABLED,
		"debug feature enabled" पूर्ण,
	अणु HIF_ERROR_PDS_PAYLOAD,
		"PDS version is not supported" पूर्ण,
	अणु HIF_ERROR_PDS_TESTFEATURE,
		"PDS ask for an unknown test mode" पूर्ण,
	अणु HIF_ERROR_OOR_VOLTAGE,
		"out-of-range power supply voltage", true पूर्ण,
	अणु HIF_ERROR_OOR_TEMPERATURE,
		"out-of-range temperature", true पूर्ण,
	अणु HIF_ERROR_SLK_REQ_DURING_KEY_EXCHANGE,
		"secure link does not expect request during key exchange" पूर्ण,
	अणु HIF_ERROR_SLK_SESSION_KEY,
		"secure link session key is invalid" पूर्ण,
	अणु HIF_ERROR_SLK_OVERFLOW,
		"secure link overflow" पूर्ण,
	अणु HIF_ERROR_SLK_WRONG_ENCRYPTION_STATE,
		"secure link messages list does not match message encryption" पूर्ण,
	अणु HIF_ERROR_SLK_UNCONFIGURED,
		"secure link not yet configured" पूर्ण,
	अणु HIF_ERROR_HIF_BUS_FREQUENCY_TOO_LOW,
		"bus clock is too slow (<1kHz)" पूर्ण,
	अणु HIF_ERROR_HIF_RX_DATA_TOO_LARGE,
		"HIF message too large" पूर्ण,
	// Following errors only exists in old firmware versions:
	अणु HIF_ERROR_HIF_TX_QUEUE_FULL,
		"HIF messages queue is full" पूर्ण,
	अणु HIF_ERROR_HIF_BUS,
		"HIF bus" पूर्ण,
	अणु HIF_ERROR_SLK_MULTI_TX_UNSUPPORTED,
		"secure link does not support multi-tx confirmations" पूर्ण,
	अणु HIF_ERROR_SLK_OUTDATED_SESSION_KEY,
		"secure link session key is outdated" पूर्ण,
	अणु HIF_ERROR_SLK_DECRYPTION,
		"secure link params (nonce or tag) mismatch" पूर्ण,
पूर्ण;

अटल पूर्णांक hअगर_error_indication(काष्ठा wfx_dev *wdev,
				स्थिर काष्ठा hअगर_msg *hअगर, स्थिर व्योम *buf)
अणु
	स्थिर काष्ठा hअगर_ind_error *body = buf;
	पूर्णांक type = le32_to_cpu(body->type);
	पूर्णांक param = (s8)body->data[0];
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(hअगर_errors); i++)
		अगर (type == hअगर_errors[i].val)
			अवरोध;
	अगर (i < ARRAY_SIZE(hअगर_errors))
		अगर (hअगर_errors[i].has_param)
			dev_err(wdev->dev, "asynchronous error: %s: %d\n",
				hअगर_errors[i].str, param);
		अन्यथा
			dev_err(wdev->dev, "asynchronous error: %s\n",
				hअगर_errors[i].str);
	अन्यथा
		dev_err(wdev->dev, "asynchronous error: unknown: %08x\n", type);
	prपूर्णांक_hex_dump(KERN_INFO, "hif: ", DUMP_PREFIX_OFFSET,
		       16, 1, hअगर, le16_to_cpu(hअगर->len), false);
	wdev->chip_frozen = true;

	वापस 0;
पूर्ण;

अटल पूर्णांक hअगर_exception_indication(काष्ठा wfx_dev *wdev,
				    स्थिर काष्ठा hअगर_msg *hअगर, स्थिर व्योम *buf)
अणु
	स्थिर काष्ठा hअगर_ind_exception *body = buf;
	पूर्णांक type = le32_to_cpu(body->type);

	अगर (type == 4)
		dev_err(wdev->dev, "firmware assert %d\n",
			le32_to_cpup((__le32 *)body->data));
	अन्यथा
		dev_err(wdev->dev, "firmware exception\n");
	prपूर्णांक_hex_dump(KERN_INFO, "hif: ", DUMP_PREFIX_OFFSET,
		       16, 1, hअगर, le16_to_cpu(hअगर->len), false);
	wdev->chip_frozen = true;

	वापस -1;
पूर्ण

अटल स्थिर काष्ठा अणु
	पूर्णांक msg_id;
	पूर्णांक (*handler)(काष्ठा wfx_dev *wdev,
		       स्थिर काष्ठा hअगर_msg *hअगर, स्थिर व्योम *buf);
पूर्ण hअगर_handlers[] = अणु
	/* Confirmations */
	अणु HIF_CNF_ID_TX,                   hअगर_tx_confirm पूर्ण,
	अणु HIF_CNF_ID_MULTI_TRANSMIT,       hअगर_multi_tx_confirm पूर्ण,
	/* Indications */
	अणु HIF_IND_ID_STARTUP,              hअगर_startup_indication पूर्ण,
	अणु HIF_IND_ID_WAKEUP,               hअगर_wakeup_indication पूर्ण,
	अणु HIF_IND_ID_JOIN_COMPLETE,        hअगर_join_complete_indication पूर्ण,
	अणु HIF_IND_ID_SET_PM_MODE_CMPL,     hअगर_pm_mode_complete_indication पूर्ण,
	अणु HIF_IND_ID_SCAN_CMPL,            hअगर_scan_complete_indication पूर्ण,
	अणु HIF_IND_ID_SUSPEND_RESUME_TX,    hअगर_suspend_resume_indication पूर्ण,
	अणु HIF_IND_ID_EVENT,                hअगर_event_indication पूर्ण,
	अणु HIF_IND_ID_GENERIC,              hअगर_generic_indication पूर्ण,
	अणु HIF_IND_ID_ERROR,                hअगर_error_indication पूर्ण,
	अणु HIF_IND_ID_EXCEPTION,            hअगर_exception_indication पूर्ण,
	// FIXME: allocate skb_p from hअगर_receive_indication and make it generic
	//अणु HIF_IND_ID_RX,                 hअगर_receive_indication पूर्ण,
पूर्ण;

व्योम wfx_handle_rx(काष्ठा wfx_dev *wdev, काष्ठा sk_buff *skb)
अणु
	पूर्णांक i;
	स्थिर काष्ठा hअगर_msg *hअगर = (स्थिर काष्ठा hअगर_msg *)skb->data;
	पूर्णांक hअगर_id = hअगर->id;

	अगर (hअगर_id == HIF_IND_ID_RX) अणु
		// hअगर_receive_indication take care of skb lअगरeसमय
		hअगर_receive_indication(wdev, hअगर, hअगर->body, skb);
		वापस;
	पूर्ण
	// Note: mutex_is_lock cause an implicit memory barrier that protect
	// buf_send
	अगर (mutex_is_locked(&wdev->hअगर_cmd.lock) &&
	    wdev->hअगर_cmd.buf_send &&
	    wdev->hअगर_cmd.buf_send->id == hअगर_id) अणु
		hअगर_generic_confirm(wdev, hअगर, hअगर->body);
		जाओ मुक्त;
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(hअगर_handlers); i++) अणु
		अगर (hअगर_handlers[i].msg_id == hअगर_id) अणु
			अगर (hअगर_handlers[i].handler)
				hअगर_handlers[i].handler(wdev, hअगर, hअगर->body);
			जाओ मुक्त;
		पूर्ण
	पूर्ण
	अगर (hअगर_id & 0x80)
		dev_err(wdev->dev, "unsupported HIF indication: ID %02x\n",
			hअगर_id);
	अन्यथा
		dev_err(wdev->dev, "unexpected HIF confirmation: ID %02x\n",
			hअगर_id);
मुक्त:
	dev_kमुक्त_skb(skb);
पूर्ण
