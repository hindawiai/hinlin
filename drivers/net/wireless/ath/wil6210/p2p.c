<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#समावेश "wil6210.h"
#समावेश "wmi.h"

#घोषणा P2P_WILDCARD_SSID "DIRECT-"
#घोषणा P2P_DMG_SOCIAL_CHANNEL 2
#घोषणा P2P_SEARCH_DURATION_MS 500
#घोषणा P2P_DEFAULT_BI 100

अटल पूर्णांक wil_p2p_start_listen(काष्ठा wil6210_vअगर *vअगर)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wil_p2p_info *p2p = &vअगर->p2p;
	u8 channel = p2p->listen_chan.hw_value;
	पूर्णांक rc;

	lockdep_निश्चित_held(&wil->mutex);

	rc = wmi_p2p_cfg(vअगर, channel, P2P_DEFAULT_BI);
	अगर (rc) अणु
		wil_err(wil, "wmi_p2p_cfg failed\n");
		जाओ out;
	पूर्ण

	rc = wmi_set_ssid(vअगर, म_माप(P2P_WILDCARD_SSID), P2P_WILDCARD_SSID);
	अगर (rc) अणु
		wil_err(wil, "wmi_set_ssid failed\n");
		जाओ out_stop;
	पूर्ण

	rc = wmi_start_listen(vअगर);
	अगर (rc) अणु
		wil_err(wil, "wmi_start_listen failed\n");
		जाओ out_stop;
	पूर्ण

	INIT_WORK(&p2p->discovery_expired_work, wil_p2p_listen_expired);
	mod_समयr(&p2p->discovery_समयr,
		  jअगरfies + msecs_to_jअगरfies(p2p->listen_duration));
out_stop:
	अगर (rc)
		wmi_stop_discovery(vअगर);

out:
	वापस rc;
पूर्ण

bool wil_p2p_is_social_scan(काष्ठा cfg80211_scan_request *request)
अणु
	वापस (request->n_channels == 1) &&
	       (request->channels[0]->hw_value == P2P_DMG_SOCIAL_CHANNEL);
पूर्ण

पूर्णांक wil_p2p_search(काष्ठा wil6210_vअगर *vअगर,
		   काष्ठा cfg80211_scan_request *request)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक rc;
	काष्ठा wil_p2p_info *p2p = &vअगर->p2p;

	wil_dbg_misc(wil, "p2p_search: channel %d\n", P2P_DMG_SOCIAL_CHANNEL);

	lockdep_निश्चित_held(&wil->mutex);

	अगर (p2p->discovery_started) अणु
		wil_err(wil, "search failed. discovery already ongoing\n");
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	rc = wmi_p2p_cfg(vअगर, P2P_DMG_SOCIAL_CHANNEL, P2P_DEFAULT_BI);
	अगर (rc) अणु
		wil_err(wil, "wmi_p2p_cfg failed\n");
		जाओ out;
	पूर्ण

	rc = wmi_set_ssid(vअगर, म_माप(P2P_WILDCARD_SSID), P2P_WILDCARD_SSID);
	अगर (rc) अणु
		wil_err(wil, "wmi_set_ssid failed\n");
		जाओ out_stop;
	पूर्ण

	/* Set application IE to probe request and probe response */
	rc = wmi_set_ie(vअगर, WMI_FRAME_PROBE_REQ,
			request->ie_len, request->ie);
	अगर (rc) अणु
		wil_err(wil, "wmi_set_ie(WMI_FRAME_PROBE_REQ) failed\n");
		जाओ out_stop;
	पूर्ण

	/* supplicant करोesn't provide Probe Response IEs. As a workaround -
	 * re-use Probe Request IEs
	 */
	rc = wmi_set_ie(vअगर, WMI_FRAME_PROBE_RESP,
			request->ie_len, request->ie);
	अगर (rc) अणु
		wil_err(wil, "wmi_set_ie(WMI_FRAME_PROBE_RESP) failed\n");
		जाओ out_stop;
	पूर्ण

	rc = wmi_start_search(vअगर);
	अगर (rc) अणु
		wil_err(wil, "wmi_start_search failed\n");
		जाओ out_stop;
	पूर्ण

	p2p->discovery_started = 1;
	INIT_WORK(&p2p->discovery_expired_work, wil_p2p_search_expired);
	mod_समयr(&p2p->discovery_समयr,
		  jअगरfies + msecs_to_jअगरfies(P2P_SEARCH_DURATION_MS));

out_stop:
	अगर (rc)
		wmi_stop_discovery(vअगर);

out:
	वापस rc;
पूर्ण

पूर्णांक wil_p2p_listen(काष्ठा wil6210_priv *wil, काष्ठा wireless_dev *wdev,
		   अचिन्हित पूर्णांक duration, काष्ठा ieee80211_channel *chan,
		   u64 *cookie)
अणु
	काष्ठा wil6210_vअगर *vअगर = wdev_to_vअगर(wil, wdev);
	काष्ठा wil_p2p_info *p2p = &vअगर->p2p;
	पूर्णांक rc;

	अगर (!chan)
		वापस -EINVAL;

	wil_dbg_misc(wil, "p2p_listen: duration %d\n", duration);

	mutex_lock(&wil->mutex);

	अगर (p2p->discovery_started) अणु
		wil_err(wil, "discovery already ongoing\n");
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	स_नकल(&p2p->listen_chan, chan, माप(*chan));
	*cookie = ++p2p->cookie;
	p2p->listen_duration = duration;

	mutex_lock(&wil->vअगर_mutex);
	अगर (vअगर->scan_request) अणु
		wil_dbg_misc(wil, "Delaying p2p listen until scan done\n");
		p2p->pending_listen_wdev = wdev;
		p2p->discovery_started = 1;
		rc = 0;
		mutex_unlock(&wil->vअगर_mutex);
		जाओ out;
	पूर्ण
	mutex_unlock(&wil->vअगर_mutex);

	rc = wil_p2p_start_listen(vअगर);
	अगर (rc)
		जाओ out;

	p2p->discovery_started = 1;
	अगर (vअगर->mid == 0)
		wil->radio_wdev = wdev;

	cfg80211_पढ़ोy_on_channel(wdev, *cookie, chan, duration,
				  GFP_KERNEL);

out:
	mutex_unlock(&wil->mutex);
	वापस rc;
पूर्ण

u8 wil_p2p_stop_discovery(काष्ठा wil6210_vअगर *vअगर)
अणु
	काष्ठा wil_p2p_info *p2p = &vअगर->p2p;
	u8 started = p2p->discovery_started;

	अगर (p2p->discovery_started) अणु
		अगर (p2p->pending_listen_wdev) अणु
			/* discovery not really started, only pending */
			p2p->pending_listen_wdev = शून्य;
		पूर्ण अन्यथा अणु
			del_समयr_sync(&p2p->discovery_समयr);
			wmi_stop_discovery(vअगर);
		पूर्ण
		p2p->discovery_started = 0;
	पूर्ण

	वापस started;
पूर्ण

पूर्णांक wil_p2p_cancel_listen(काष्ठा wil6210_vअगर *vअगर, u64 cookie)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wil_p2p_info *p2p = &vअगर->p2p;
	u8 started;

	mutex_lock(&wil->mutex);

	अगर (cookie != p2p->cookie) अणु
		wil_info(wil, "Cookie mismatch: 0x%016llx vs. 0x%016llx\n",
			 p2p->cookie, cookie);
		mutex_unlock(&wil->mutex);
		वापस -ENOENT;
	पूर्ण

	started = wil_p2p_stop_discovery(vअगर);

	mutex_unlock(&wil->mutex);

	अगर (!started) अणु
		wil_err(wil, "listen not started\n");
		वापस -ENOENT;
	पूर्ण

	mutex_lock(&wil->vअगर_mutex);
	cfg80211_reमुख्य_on_channel_expired(vअगर_to_radio_wdev(wil, vअगर),
					   p2p->cookie,
					   &p2p->listen_chan,
					   GFP_KERNEL);
	अगर (vअगर->mid == 0)
		wil->radio_wdev = wil->मुख्य_ndev->ieee80211_ptr;
	mutex_unlock(&wil->vअगर_mutex);
	वापस 0;
पूर्ण

व्योम wil_p2p_listen_expired(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wil_p2p_info *p2p = container_of(work,
			काष्ठा wil_p2p_info, discovery_expired_work);
	काष्ठा wil6210_vअगर *vअगर = container_of(p2p,
			काष्ठा wil6210_vअगर, p2p);
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	u8 started;

	wil_dbg_misc(wil, "p2p_listen_expired\n");

	mutex_lock(&wil->mutex);
	started = wil_p2p_stop_discovery(vअगर);
	mutex_unlock(&wil->mutex);

	अगर (!started)
		वापस;

	mutex_lock(&wil->vअगर_mutex);
	cfg80211_reमुख्य_on_channel_expired(vअगर_to_radio_wdev(wil, vअगर),
					   p2p->cookie,
					   &p2p->listen_chan,
					   GFP_KERNEL);
	अगर (vअगर->mid == 0)
		wil->radio_wdev = wil->मुख्य_ndev->ieee80211_ptr;
	mutex_unlock(&wil->vअगर_mutex);
पूर्ण

व्योम wil_p2p_search_expired(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wil_p2p_info *p2p = container_of(work,
			काष्ठा wil_p2p_info, discovery_expired_work);
	काष्ठा wil6210_vअगर *vअगर = container_of(p2p,
			काष्ठा wil6210_vअगर, p2p);
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	u8 started;

	wil_dbg_misc(wil, "p2p_search_expired\n");

	mutex_lock(&wil->mutex);
	started = wil_p2p_stop_discovery(vअगर);
	mutex_unlock(&wil->mutex);

	अगर (started) अणु
		काष्ठा cfg80211_scan_info info = अणु
			.पातed = false,
		पूर्ण;

		mutex_lock(&wil->vअगर_mutex);
		अगर (vअगर->scan_request) अणु
			cfg80211_scan_करोne(vअगर->scan_request, &info);
			vअगर->scan_request = शून्य;
			अगर (vअगर->mid == 0)
				wil->radio_wdev =
					wil->मुख्य_ndev->ieee80211_ptr;
		पूर्ण
		mutex_unlock(&wil->vअगर_mutex);
	पूर्ण
पूर्ण

व्योम wil_p2p_delayed_listen_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wil_p2p_info *p2p = container_of(work,
			काष्ठा wil_p2p_info, delayed_listen_work);
	काष्ठा wil6210_vअगर *vअगर = container_of(p2p,
			काष्ठा wil6210_vअगर, p2p);
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक rc;

	mutex_lock(&wil->mutex);

	wil_dbg_misc(wil, "Checking delayed p2p listen\n");
	अगर (!p2p->discovery_started || !p2p->pending_listen_wdev)
		जाओ out;

	mutex_lock(&wil->vअगर_mutex);
	अगर (vअगर->scan_request) अणु
		/* another scan started, रुको again... */
		mutex_unlock(&wil->vअगर_mutex);
		जाओ out;
	पूर्ण
	mutex_unlock(&wil->vअगर_mutex);

	rc = wil_p2p_start_listen(vअगर);

	mutex_lock(&wil->vअगर_mutex);
	अगर (rc) अणु
		cfg80211_reमुख्य_on_channel_expired(p2p->pending_listen_wdev,
						   p2p->cookie,
						   &p2p->listen_chan,
						   GFP_KERNEL);
		अगर (vअगर->mid == 0)
			wil->radio_wdev = wil->मुख्य_ndev->ieee80211_ptr;
	पूर्ण अन्यथा अणु
		cfg80211_पढ़ोy_on_channel(p2p->pending_listen_wdev, p2p->cookie,
					  &p2p->listen_chan,
					  p2p->listen_duration, GFP_KERNEL);
		अगर (vअगर->mid == 0)
			wil->radio_wdev = p2p->pending_listen_wdev;
	पूर्ण
	p2p->pending_listen_wdev = शून्य;
	mutex_unlock(&wil->vअगर_mutex);

out:
	mutex_unlock(&wil->mutex);
पूर्ण

व्योम wil_p2p_stop_radio_operations(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	काष्ठा wil_p2p_info *p2p = &vअगर->p2p;
	काष्ठा cfg80211_scan_info info = अणु
		.पातed = true,
	पूर्ण;

	lockdep_निश्चित_held(&wil->mutex);
	lockdep_निश्चित_held(&wil->vअगर_mutex);

	अगर (wil->radio_wdev != wil->p2p_wdev)
		जाओ out;

	अगर (!p2p->discovery_started) अणु
		/* Regular scan on the p2p device */
		अगर (vअगर->scan_request &&
		    vअगर->scan_request->wdev == wil->p2p_wdev)
			wil_पात_scan(vअगर, true);
		जाओ out;
	पूर्ण

	/* Search or listen on p2p device */
	mutex_unlock(&wil->vअगर_mutex);
	wil_p2p_stop_discovery(vअगर);
	mutex_lock(&wil->vअगर_mutex);

	अगर (vअगर->scan_request) अणु
		/* search */
		cfg80211_scan_करोne(vअगर->scan_request, &info);
		vअगर->scan_request = शून्य;
	पूर्ण अन्यथा अणु
		/* listen */
		cfg80211_reमुख्य_on_channel_expired(wil->radio_wdev,
						   p2p->cookie,
						   &p2p->listen_chan,
						   GFP_KERNEL);
	पूर्ण

out:
	wil->radio_wdev = wil->मुख्य_ndev->ieee80211_ptr;
पूर्ण
