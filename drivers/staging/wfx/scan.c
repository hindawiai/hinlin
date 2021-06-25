<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Scan related functions.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 */
#समावेश <net/mac80211.h>

#समावेश "scan.h"
#समावेश "wfx.h"
#समावेश "sta.h"
#समावेश "hif_tx_mib.h"

अटल व्योम __ieee80211_scan_completed_compat(काष्ठा ieee80211_hw *hw,
					      bool पातed)
अणु
	काष्ठा cfg80211_scan_info info = अणु
		.पातed = पातed,
	पूर्ण;

	ieee80211_scan_completed(hw, &info);
पूर्ण

अटल पूर्णांक update_probe_पंचांगpl(काष्ठा wfx_vअगर *wvअगर,
			     काष्ठा cfg80211_scan_request *req)
अणु
	काष्ठा sk_buff *skb;

	skb = ieee80211_probereq_get(wvअगर->wdev->hw, wvअगर->vअगर->addr,
				     शून्य, 0, req->ie_len);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_data(skb, req->ie, req->ie_len);
	hअगर_set_ढाँचा_frame(wvअगर, skb, HIF_TMPLT_PRBREQ, 0);
	dev_kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक send_scan_req(काष्ठा wfx_vअगर *wvअगर,
			 काष्ठा cfg80211_scan_request *req, पूर्णांक start_idx)
अणु
	पूर्णांक i, ret, समयout;
	काष्ठा ieee80211_channel *ch_start, *ch_cur;

	क्रम (i = start_idx; i < req->n_channels; i++) अणु
		ch_start = req->channels[start_idx];
		ch_cur = req->channels[i];
		WARN(ch_cur->band != NL80211_BAND_2GHZ, "band not supported");
		अगर (ch_cur->max_घातer != ch_start->max_घातer)
			अवरोध;
		अगर ((ch_cur->flags ^ ch_start->flags) & IEEE80211_CHAN_NO_IR)
			अवरोध;
	पूर्ण
	wfx_tx_lock_flush(wvअगर->wdev);
	wvअगर->scan_पात = false;
	reinit_completion(&wvअगर->scan_complete);
	ret = hअगर_scan(wvअगर, req, start_idx, i - start_idx, &समयout);
	अगर (ret) अणु
		wfx_tx_unlock(wvअगर->wdev);
		वापस -EIO;
	पूर्ण
	ret = रुको_क्रम_completion_समयout(&wvअगर->scan_complete, समयout);
	अगर (req->channels[start_idx]->max_घातer != wvअगर->vअगर->bss_conf.txघातer)
		hअगर_set_output_घातer(wvअगर, wvअगर->vअगर->bss_conf.txघातer);
	wfx_tx_unlock(wvअगर->wdev);
	अगर (!ret) अणु
		dev_notice(wvअगर->wdev->dev, "scan timeout\n");
		hअगर_stop_scan(wvअगर);
		वापस -ETIMEDOUT;
	पूर्ण
	अगर (wvअगर->scan_पात) अणु
		dev_notice(wvअगर->wdev->dev, "scan abort\n");
		वापस -ECONNABORTED;
	पूर्ण
	वापस i - start_idx;
पूर्ण

/*
 * It is not really necessary to run scan request asynchronously. However,
 * there is a bug in "iw scan" when ieee80211_scan_completed() is called beक्रमe
 * wfx_hw_scan() वापस
 */
व्योम wfx_hw_scan_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wfx_vअगर *wvअगर = container_of(work, काष्ठा wfx_vअगर, scan_work);
	काष्ठा ieee80211_scan_request *hw_req = wvअगर->scan_req;
	पूर्णांक chan_cur, ret;

	mutex_lock(&wvअगर->wdev->conf_mutex);
	mutex_lock(&wvअगर->scan_lock);
	अगर (wvअगर->join_in_progress) अणु
		dev_info(wvअगर->wdev->dev, "%s: abort in-progress REQ_JOIN",
			 __func__);
		wfx_reset(wvअगर);
	पूर्ण
	update_probe_पंचांगpl(wvअगर, &hw_req->req);
	chan_cur = 0;
	करो अणु
		ret = send_scan_req(wvअगर, &hw_req->req, chan_cur);
		अगर (ret > 0)
			chan_cur += ret;
	पूर्ण जबतक (ret > 0 && chan_cur < hw_req->req.n_channels);
	mutex_unlock(&wvअगर->scan_lock);
	mutex_unlock(&wvअगर->wdev->conf_mutex);
	__ieee80211_scan_completed_compat(wvअगर->wdev->hw, ret < 0);
पूर्ण

पूर्णांक wfx_hw_scan(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		काष्ठा ieee80211_scan_request *hw_req)
अणु
	काष्ठा wfx_vअगर *wvअगर = (काष्ठा wfx_vअगर *)vअगर->drv_priv;

	WARN_ON(hw_req->req.n_channels > HIF_API_MAX_NB_CHANNELS);
	wvअगर->scan_req = hw_req;
	schedule_work(&wvअगर->scan_work);
	वापस 0;
पूर्ण

व्योम wfx_cancel_hw_scan(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wfx_vअगर *wvअगर = (काष्ठा wfx_vअगर *)vअगर->drv_priv;

	wvअगर->scan_पात = true;
	hअगर_stop_scan(wvअगर);
पूर्ण

व्योम wfx_scan_complete(काष्ठा wfx_vअगर *wvअगर)
अणु
	complete(&wvअगर->scan_complete);
पूर्ण
