<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Implementation of host-to-chip commands (aka request/confirmation) of WFxxx
 * Split Mac (WSM) API.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 */
#समावेश <linux/etherdevice.h>

#समावेश "hif_tx.h"
#समावेश "wfx.h"
#समावेश "bh.h"
#समावेश "hwio.h"
#समावेश "debug.h"
#समावेश "sta.h"

व्योम wfx_init_hअगर_cmd(काष्ठा wfx_hअगर_cmd *hअगर_cmd)
अणु
	init_completion(&hअगर_cmd->पढ़ोy);
	init_completion(&hअगर_cmd->करोne);
	mutex_init(&hअगर_cmd->lock);
पूर्ण

अटल व्योम wfx_fill_header(काष्ठा hअगर_msg *hअगर, पूर्णांक अगर_id,
			    अचिन्हित पूर्णांक cmd, माप_प्रकार size)
अणु
	अगर (अगर_id == -1)
		अगर_id = 2;

	WARN(cmd > 0x3f, "invalid WSM command %#.2x", cmd);
	WARN(size > 0xFFF, "requested buffer is too large: %zu bytes", size);
	WARN(अगर_id > 0x3, "invalid interface ID %d", अगर_id);

	hअगर->len = cpu_to_le16(size + 4);
	hअगर->id = cmd;
	hअगर->पूर्णांकerface = अगर_id;
पूर्ण

अटल व्योम *wfx_alloc_hअगर(माप_प्रकार body_len, काष्ठा hअगर_msg **hअगर)
अणु
	*hअगर = kzalloc(माप(काष्ठा hअगर_msg) + body_len, GFP_KERNEL);
	अगर (*hअगर)
		वापस (*hअगर)->body;
	अन्यथा
		वापस शून्य;
पूर्ण

पूर्णांक wfx_cmd_send(काष्ठा wfx_dev *wdev, काष्ठा hअगर_msg *request,
		 व्योम *reply, माप_प्रकार reply_len, bool no_reply)
अणु
	स्थिर अक्षर *mib_name = "";
	स्थिर अक्षर *mib_sep = "";
	पूर्णांक cmd = request->id;
	पूर्णांक vअगर = request->पूर्णांकerface;
	पूर्णांक ret;

	// Do not रुको क्रम any reply अगर chip is frozen
	अगर (wdev->chip_frozen)
		वापस -ETIMEDOUT;

	mutex_lock(&wdev->hअगर_cmd.lock);
	WARN(wdev->hअगर_cmd.buf_send, "data locking error");

	// Note: call to complete() below has an implicit memory barrier that
	// hopefully protect buf_send
	wdev->hअगर_cmd.buf_send = request;
	wdev->hअगर_cmd.buf_recv = reply;
	wdev->hअगर_cmd.len_recv = reply_len;
	complete(&wdev->hअगर_cmd.पढ़ोy);

	wfx_bh_request_tx(wdev);

	अगर (no_reply) अणु
		// Chip won't reply. Give enough समय to the wq to send the
		// buffer.
		msleep(100);
		wdev->hअगर_cmd.buf_send = शून्य;
		mutex_unlock(&wdev->hअगर_cmd.lock);
		वापस 0;
	पूर्ण

	अगर (wdev->poll_irq)
		wfx_bh_poll_irq(wdev);

	ret = रुको_क्रम_completion_समयout(&wdev->hअगर_cmd.करोne, 1 * HZ);
	अगर (!ret) अणु
		dev_err(wdev->dev, "chip is abnormally long to answer\n");
		reinit_completion(&wdev->hअगर_cmd.पढ़ोy);
		ret = रुको_क्रम_completion_समयout(&wdev->hअगर_cmd.करोne, 3 * HZ);
	पूर्ण
	अगर (!ret) अणु
		dev_err(wdev->dev, "chip did not answer\n");
		wfx_pending_dump_old_frames(wdev, 3000);
		wdev->chip_frozen = true;
		reinit_completion(&wdev->hअगर_cmd.करोne);
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		ret = wdev->hअगर_cmd.ret;
	पूर्ण

	wdev->hअगर_cmd.buf_send = शून्य;
	mutex_unlock(&wdev->hअगर_cmd.lock);

	अगर (ret &&
	    (cmd == HIF_REQ_ID_READ_MIB || cmd == HIF_REQ_ID_WRITE_MIB)) अणु
		mib_name = get_mib_name(((u16 *)request)[2]);
		mib_sep = "/";
	पूर्ण
	अगर (ret < 0)
		dev_err(wdev->dev,
			"WSM request %s%s%s (%#.2x) on vif %d returned error %d\n",
			get_hअगर_name(cmd), mib_sep, mib_name, cmd, vअगर, ret);
	अगर (ret > 0)
		dev_warn(wdev->dev,
			 "WSM request %s%s%s (%#.2x) on vif %d returned status %d\n",
			 get_hअगर_name(cmd), mib_sep, mib_name, cmd, vअगर, ret);

	वापस ret;
पूर्ण

// This function is special. After HIF_REQ_ID_SHUT_DOWN, chip won't reply to any
// request anymore. Obviously, only call this function during device unरेजिस्टर.
पूर्णांक hअगर_shutकरोwn(काष्ठा wfx_dev *wdev)
अणु
	पूर्णांक ret;
	काष्ठा hअगर_msg *hअगर;

	wfx_alloc_hअगर(0, &hअगर);
	अगर (!hअगर)
		वापस -ENOMEM;
	wfx_fill_header(hअगर, -1, HIF_REQ_ID_SHUT_DOWN, 0);
	ret = wfx_cmd_send(wdev, hअगर, शून्य, 0, true);
	अगर (wdev->pdata.gpio_wakeup)
		gpiod_set_value(wdev->pdata.gpio_wakeup, 0);
	अन्यथा
		control_reg_ग_लिखो(wdev, 0);
	kमुक्त(hअगर);
	वापस ret;
पूर्ण

पूर्णांक hअगर_configuration(काष्ठा wfx_dev *wdev, स्थिर u8 *conf, माप_प्रकार len)
अणु
	पूर्णांक ret;
	माप_प्रकार buf_len = माप(काष्ठा hअगर_req_configuration) + len;
	काष्ठा hअगर_msg *hअगर;
	काष्ठा hअगर_req_configuration *body = wfx_alloc_hअगर(buf_len, &hअगर);

	अगर (!hअगर)
		वापस -ENOMEM;
	body->length = cpu_to_le16(len);
	स_नकल(body->pds_data, conf, len);
	wfx_fill_header(hअगर, -1, HIF_REQ_ID_CONFIGURATION, buf_len);
	ret = wfx_cmd_send(wdev, hअगर, शून्य, 0, false);
	kमुक्त(hअगर);
	वापस ret;
पूर्ण

पूर्णांक hअगर_reset(काष्ठा wfx_vअगर *wvअगर, bool reset_stat)
अणु
	पूर्णांक ret;
	काष्ठा hअगर_msg *hअगर;
	काष्ठा hअगर_req_reset *body = wfx_alloc_hअगर(माप(*body), &hअगर);

	अगर (!hअगर)
		वापस -ENOMEM;
	body->reset_stat = reset_stat;
	wfx_fill_header(hअगर, wvअगर->id, HIF_REQ_ID_RESET, माप(*body));
	ret = wfx_cmd_send(wvअगर->wdev, hअगर, शून्य, 0, false);
	kमुक्त(hअगर);
	वापस ret;
पूर्ण

पूर्णांक hअगर_पढ़ो_mib(काष्ठा wfx_dev *wdev, पूर्णांक vअगर_id, u16 mib_id,
		 व्योम *val, माप_प्रकार val_len)
अणु
	पूर्णांक ret;
	काष्ठा hअगर_msg *hअगर;
	पूर्णांक buf_len = माप(काष्ठा hअगर_cnf_पढ़ो_mib) + val_len;
	काष्ठा hअगर_req_पढ़ो_mib *body = wfx_alloc_hअगर(माप(*body), &hअगर);
	काष्ठा hअगर_cnf_पढ़ो_mib *reply = kदो_स्मृति(buf_len, GFP_KERNEL);

	अगर (!body || !reply) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	body->mib_id = cpu_to_le16(mib_id);
	wfx_fill_header(hअगर, vअगर_id, HIF_REQ_ID_READ_MIB, माप(*body));
	ret = wfx_cmd_send(wdev, hअगर, reply, buf_len, false);

	अगर (!ret && mib_id != le16_to_cpu(reply->mib_id)) अणु
		dev_warn(wdev->dev, "%s: confirmation mismatch request\n",
			 __func__);
		ret = -EIO;
	पूर्ण
	अगर (ret == -ENOMEM)
		dev_err(wdev->dev, "buffer is too small to receive %s (%zu < %d)\n",
			get_mib_name(mib_id), val_len,
			le16_to_cpu(reply->length));
	अगर (!ret)
		स_नकल(val, &reply->mib_data, le16_to_cpu(reply->length));
	अन्यथा
		स_रखो(val, 0xFF, val_len);
out:
	kमुक्त(hअगर);
	kमुक्त(reply);
	वापस ret;
पूर्ण

पूर्णांक hअगर_ग_लिखो_mib(काष्ठा wfx_dev *wdev, पूर्णांक vअगर_id, u16 mib_id,
		  व्योम *val, माप_प्रकार val_len)
अणु
	पूर्णांक ret;
	काष्ठा hअगर_msg *hअगर;
	पूर्णांक buf_len = माप(काष्ठा hअगर_req_ग_लिखो_mib) + val_len;
	काष्ठा hअगर_req_ग_लिखो_mib *body = wfx_alloc_hअगर(buf_len, &hअगर);

	अगर (!hअगर)
		वापस -ENOMEM;
	body->mib_id = cpu_to_le16(mib_id);
	body->length = cpu_to_le16(val_len);
	स_नकल(&body->mib_data, val, val_len);
	wfx_fill_header(hअगर, vअगर_id, HIF_REQ_ID_WRITE_MIB, buf_len);
	ret = wfx_cmd_send(wdev, hअगर, शून्य, 0, false);
	kमुक्त(hअगर);
	वापस ret;
पूर्ण

पूर्णांक hअगर_scan(काष्ठा wfx_vअगर *wvअगर, काष्ठा cfg80211_scan_request *req,
	     पूर्णांक chan_start_idx, पूर्णांक chan_num, पूर्णांक *समयout)
अणु
	पूर्णांक ret, i;
	काष्ठा hअगर_msg *hअगर;
	माप_प्रकार buf_len =
		माप(काष्ठा hअगर_req_start_scan_alt) + chan_num * माप(u8);
	काष्ठा hअगर_req_start_scan_alt *body = wfx_alloc_hअगर(buf_len, &hअगर);
	पूर्णांक पंचांगo_chan_fg, पंचांगo_chan_bg, पंचांगo;

	WARN(chan_num > HIF_API_MAX_NB_CHANNELS, "invalid params");
	WARN(req->n_ssids > HIF_API_MAX_NB_SSIDS, "invalid params");

	अगर (!hअगर)
		वापस -ENOMEM;
	क्रम (i = 0; i < req->n_ssids; i++) अणु
		स_नकल(body->ssid_def[i].ssid, req->ssids[i].ssid,
		       IEEE80211_MAX_SSID_LEN);
		body->ssid_def[i].ssid_length =
			cpu_to_le32(req->ssids[i].ssid_len);
	पूर्ण
	body->num_of_ssids = HIF_API_MAX_NB_SSIDS;
	body->मुख्यtain_current_bss = 1;
	body->disallow_ps = 1;
	body->tx_घातer_level =
		cpu_to_le32(req->channels[chan_start_idx]->max_घातer);
	body->num_of_channels = chan_num;
	क्रम (i = 0; i < chan_num; i++)
		body->channel_list[i] =
			req->channels[i + chan_start_idx]->hw_value;
	अगर (req->no_cck)
		body->max_transmit_rate = API_RATE_INDEX_G_6MBPS;
	अन्यथा
		body->max_transmit_rate = API_RATE_INDEX_B_1MBPS;
	अगर (req->channels[chan_start_idx]->flags & IEEE80211_CHAN_NO_IR) अणु
		body->min_channel_समय = cpu_to_le32(50);
		body->max_channel_समय = cpu_to_le32(150);
	पूर्ण अन्यथा अणु
		body->min_channel_समय = cpu_to_le32(10);
		body->max_channel_समय = cpu_to_le32(50);
		body->num_of_probe_requests = 2;
		body->probe_delay = 100;
	पूर्ण
	पंचांगo_chan_bg = le32_to_cpu(body->max_channel_समय) * USEC_PER_TU;
	पंचांगo_chan_fg = 512 * USEC_PER_TU + body->probe_delay;
	पंचांगo_chan_fg *= body->num_of_probe_requests;
	पंचांगo = chan_num * max(पंचांगo_chan_bg, पंचांगo_chan_fg) + 512 * USEC_PER_TU;
	अगर (समयout)
		*समयout = usecs_to_jअगरfies(पंचांगo);

	wfx_fill_header(hअगर, wvअगर->id, HIF_REQ_ID_START_SCAN, buf_len);
	ret = wfx_cmd_send(wvअगर->wdev, hअगर, शून्य, 0, false);
	kमुक्त(hअगर);
	वापस ret;
पूर्ण

पूर्णांक hअगर_stop_scan(काष्ठा wfx_vअगर *wvअगर)
अणु
	पूर्णांक ret;
	काष्ठा hअगर_msg *hअगर;
	// body associated to HIF_REQ_ID_STOP_SCAN is empty
	wfx_alloc_hअगर(0, &hअगर);

	अगर (!hअगर)
		वापस -ENOMEM;
	wfx_fill_header(hअगर, wvअगर->id, HIF_REQ_ID_STOP_SCAN, 0);
	ret = wfx_cmd_send(wvअगर->wdev, hअगर, शून्य, 0, false);
	kमुक्त(hअगर);
	वापस ret;
पूर्ण

पूर्णांक hअगर_join(काष्ठा wfx_vअगर *wvअगर, स्थिर काष्ठा ieee80211_bss_conf *conf,
	     काष्ठा ieee80211_channel *channel, स्थिर u8 *ssid, पूर्णांक ssidlen)
अणु
	पूर्णांक ret;
	काष्ठा hअगर_msg *hअगर;
	काष्ठा hअगर_req_join *body = wfx_alloc_hअगर(माप(*body), &hअगर);

	WARN_ON(!conf->beacon_पूर्णांक);
	WARN_ON(!conf->basic_rates);
	WARN_ON(माप(body->ssid) < ssidlen);
	WARN(!conf->ibss_joined && !ssidlen, "joining an unknown BSS");
	अगर (WARN_ON(!channel))
		वापस -EINVAL;
	अगर (!hअगर)
		वापस -ENOMEM;
	body->infraकाष्ठाure_bss_mode = !conf->ibss_joined;
	body->लघु_preamble = conf->use_लघु_preamble;
	अगर (channel->flags & IEEE80211_CHAN_NO_IR)
		body->probe_क्रम_join = 0;
	अन्यथा
		body->probe_क्रम_join = 1;
	body->channel_number = channel->hw_value;
	body->beacon_पूर्णांकerval = cpu_to_le32(conf->beacon_पूर्णांक);
	body->basic_rate_set =
		cpu_to_le32(wfx_rate_mask_to_hw(wvअगर->wdev, conf->basic_rates));
	स_नकल(body->bssid, conf->bssid, माप(body->bssid));
	अगर (ssid) अणु
		body->ssid_length = cpu_to_le32(ssidlen);
		स_नकल(body->ssid, ssid, ssidlen);
	पूर्ण
	wfx_fill_header(hअगर, wvअगर->id, HIF_REQ_ID_JOIN, माप(*body));
	ret = wfx_cmd_send(wvअगर->wdev, hअगर, शून्य, 0, false);
	kमुक्त(hअगर);
	वापस ret;
पूर्ण

पूर्णांक hअगर_set_bss_params(काष्ठा wfx_vअगर *wvअगर, पूर्णांक aid, पूर्णांक beacon_lost_count)
अणु
	पूर्णांक ret;
	काष्ठा hअगर_msg *hअगर;
	काष्ठा hअगर_req_set_bss_params *body =
		wfx_alloc_hअगर(माप(*body), &hअगर);

	अगर (!hअगर)
		वापस -ENOMEM;
	body->aid = cpu_to_le16(aid);
	body->beacon_lost_count = beacon_lost_count;
	wfx_fill_header(hअगर, wvअगर->id, HIF_REQ_ID_SET_BSS_PARAMS,
			माप(*body));
	ret = wfx_cmd_send(wvअगर->wdev, hअगर, शून्य, 0, false);
	kमुक्त(hअगर);
	वापस ret;
पूर्ण

पूर्णांक hअगर_add_key(काष्ठा wfx_dev *wdev, स्थिर काष्ठा hअगर_req_add_key *arg)
अणु
	पूर्णांक ret;
	काष्ठा hअगर_msg *hअगर;
	// FIXME: only send necessary bits
	काष्ठा hअगर_req_add_key *body = wfx_alloc_hअगर(माप(*body), &hअगर);

	अगर (!hअगर)
		वापस -ENOMEM;
	// FIXME: swap bytes as necessary in body
	स_नकल(body, arg, माप(*body));
	अगर (wfx_api_older_than(wdev, 1, 5))
		// Legacy firmwares expect that add_key to be sent on right
		// पूर्णांकerface.
		wfx_fill_header(hअगर, arg->पूर्णांक_id, HIF_REQ_ID_ADD_KEY,
				माप(*body));
	अन्यथा
		wfx_fill_header(hअगर, -1, HIF_REQ_ID_ADD_KEY, माप(*body));
	ret = wfx_cmd_send(wdev, hअगर, शून्य, 0, false);
	kमुक्त(hअगर);
	वापस ret;
पूर्ण

पूर्णांक hअगर_हटाओ_key(काष्ठा wfx_dev *wdev, पूर्णांक idx)
अणु
	पूर्णांक ret;
	काष्ठा hअगर_msg *hअगर;
	काष्ठा hअगर_req_हटाओ_key *body = wfx_alloc_hअगर(माप(*body), &hअगर);

	अगर (!hअगर)
		वापस -ENOMEM;
	body->entry_index = idx;
	wfx_fill_header(hअगर, -1, HIF_REQ_ID_REMOVE_KEY, माप(*body));
	ret = wfx_cmd_send(wdev, hअगर, शून्य, 0, false);
	kमुक्त(hअगर);
	वापस ret;
पूर्ण

पूर्णांक hअगर_set_edca_queue_params(काष्ठा wfx_vअगर *wvअगर, u16 queue,
			      स्थिर काष्ठा ieee80211_tx_queue_params *arg)
अणु
	पूर्णांक ret;
	काष्ठा hअगर_msg *hअगर;
	काष्ठा hअगर_req_edca_queue_params *body = wfx_alloc_hअगर(माप(*body),
							       &hअगर);

	अगर (!body)
		वापस -ENOMEM;

	WARN_ON(arg->aअगरs > 255);
	अगर (!hअगर)
		वापस -ENOMEM;
	body->aअगरsn = arg->aअगरs;
	body->cw_min = cpu_to_le16(arg->cw_min);
	body->cw_max = cpu_to_le16(arg->cw_max);
	body->tx_op_limit = cpu_to_le16(arg->txop * USEC_PER_TXOP);
	body->queue_id = 3 - queue;
	// API 2.0 has changed queue IDs values
	अगर (wfx_api_older_than(wvअगर->wdev, 2, 0) && queue == IEEE80211_AC_BE)
		body->queue_id = HIF_QUEUE_ID_BACKGROUND;
	अगर (wfx_api_older_than(wvअगर->wdev, 2, 0) && queue == IEEE80211_AC_BK)
		body->queue_id = HIF_QUEUE_ID_BESTEFFORT;
	wfx_fill_header(hअगर, wvअगर->id, HIF_REQ_ID_EDCA_QUEUE_PARAMS,
			माप(*body));
	ret = wfx_cmd_send(wvअगर->wdev, hअगर, शून्य, 0, false);
	kमुक्त(hअगर);
	वापस ret;
पूर्ण

पूर्णांक hअगर_set_pm(काष्ठा wfx_vअगर *wvअगर, bool ps, पूर्णांक dynamic_ps_समयout)
अणु
	पूर्णांक ret;
	काष्ठा hअगर_msg *hअगर;
	काष्ठा hअगर_req_set_pm_mode *body = wfx_alloc_hअगर(माप(*body), &hअगर);

	अगर (!body)
		वापस -ENOMEM;

	अगर (!hअगर)
		वापस -ENOMEM;
	अगर (ps) अणु
		body->enter_psm = 1;
		// Firmware करोes not support more than 128ms
		body->fast_psm_idle_period = min(dynamic_ps_समयout * 2, 255);
		अगर (body->fast_psm_idle_period)
			body->fast_psm = 1;
	पूर्ण
	wfx_fill_header(hअगर, wvअगर->id, HIF_REQ_ID_SET_PM_MODE, माप(*body));
	ret = wfx_cmd_send(wvअगर->wdev, hअगर, शून्य, 0, false);
	kमुक्त(hअगर);
	वापस ret;
पूर्ण

पूर्णांक hअगर_start(काष्ठा wfx_vअगर *wvअगर, स्थिर काष्ठा ieee80211_bss_conf *conf,
	      स्थिर काष्ठा ieee80211_channel *channel)
अणु
	पूर्णांक ret;
	काष्ठा hअगर_msg *hअगर;
	काष्ठा hअगर_req_start *body = wfx_alloc_hअगर(माप(*body), &hअगर);

	WARN_ON(!conf->beacon_पूर्णांक);
	अगर (!hअगर)
		वापस -ENOMEM;
	body->dtim_period = conf->dtim_period;
	body->लघु_preamble = conf->use_लघु_preamble;
	body->channel_number = channel->hw_value;
	body->beacon_पूर्णांकerval = cpu_to_le32(conf->beacon_पूर्णांक);
	body->basic_rate_set =
		cpu_to_le32(wfx_rate_mask_to_hw(wvअगर->wdev, conf->basic_rates));
	body->ssid_length = conf->ssid_len;
	स_नकल(body->ssid, conf->ssid, conf->ssid_len);
	wfx_fill_header(hअगर, wvअगर->id, HIF_REQ_ID_START, माप(*body));
	ret = wfx_cmd_send(wvअगर->wdev, hअगर, शून्य, 0, false);
	kमुक्त(hअगर);
	वापस ret;
पूर्ण

पूर्णांक hअगर_beacon_transmit(काष्ठा wfx_vअगर *wvअगर, bool enable)
अणु
	पूर्णांक ret;
	काष्ठा hअगर_msg *hअगर;
	काष्ठा hअगर_req_beacon_transmit *body = wfx_alloc_hअगर(माप(*body),
							     &hअगर);

	अगर (!hअगर)
		वापस -ENOMEM;
	body->enable_beaconing = enable ? 1 : 0;
	wfx_fill_header(hअगर, wvअगर->id, HIF_REQ_ID_BEACON_TRANSMIT,
			माप(*body));
	ret = wfx_cmd_send(wvअगर->wdev, hअगर, शून्य, 0, false);
	kमुक्त(hअगर);
	वापस ret;
पूर्ण

पूर्णांक hअगर_map_link(काष्ठा wfx_vअगर *wvअगर, bool unmap, u8 *mac_addr, पूर्णांक sta_id, bool mfp)
अणु
	पूर्णांक ret;
	काष्ठा hअगर_msg *hअगर;
	काष्ठा hअगर_req_map_link *body = wfx_alloc_hअगर(माप(*body), &hअगर);

	अगर (!hअगर)
		वापस -ENOMEM;
	अगर (mac_addr)
		ether_addr_copy(body->mac_addr, mac_addr);
	body->mfpc = mfp ? 1 : 0;
	body->unmap = unmap ? 1 : 0;
	body->peer_sta_id = sta_id;
	wfx_fill_header(hअगर, wvअगर->id, HIF_REQ_ID_MAP_LINK, माप(*body));
	ret = wfx_cmd_send(wvअगर->wdev, hअगर, शून्य, 0, false);
	kमुक्त(hअगर);
	वापस ret;
पूर्ण

पूर्णांक hअगर_update_ie_beacon(काष्ठा wfx_vअगर *wvअगर, स्थिर u8 *ies, माप_प्रकार ies_len)
अणु
	पूर्णांक ret;
	काष्ठा hअगर_msg *hअगर;
	पूर्णांक buf_len = माप(काष्ठा hअगर_req_update_ie) + ies_len;
	काष्ठा hअगर_req_update_ie *body = wfx_alloc_hअगर(buf_len, &hअगर);

	अगर (!hअगर)
		वापस -ENOMEM;
	body->beacon = 1;
	body->num_ies = cpu_to_le16(1);
	स_नकल(body->ie, ies, ies_len);
	wfx_fill_header(hअगर, wvअगर->id, HIF_REQ_ID_UPDATE_IE, buf_len);
	ret = wfx_cmd_send(wvअगर->wdev, hअगर, शून्य, 0, false);
	kमुक्त(hअगर);
	वापस ret;
पूर्ण
