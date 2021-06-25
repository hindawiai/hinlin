<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Scan पूर्णांकerface क्रम ST-Ericsson CW1200 mac80211 drivers
 *
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 */

#अगर_अघोषित SCAN_H_INCLUDED
#घोषणा SCAN_H_INCLUDED

#समावेश <linux/semaphore.h>
#समावेश "wsm.h"

/* बाह्यal */ काष्ठा sk_buff;
/* बाह्यal */ काष्ठा cfg80211_scan_request;
/* बाह्यal */ काष्ठा ieee80211_channel;
/* बाह्यal */ काष्ठा ieee80211_hw;
/* बाह्यal */ काष्ठा work_काष्ठा;

काष्ठा cw1200_scan अणु
	काष्ठा semaphore lock;
	काष्ठा work_काष्ठा work;
	काष्ठा delayed_work समयout;
	काष्ठा cfg80211_scan_request *req;
	काष्ठा ieee80211_channel **begin;
	काष्ठा ieee80211_channel **curr;
	काष्ठा ieee80211_channel **end;
	काष्ठा wsm_ssid ssids[WSM_SCAN_MAX_NUM_OF_SSIDS];
	पूर्णांक output_घातer;
	पूर्णांक n_ssids;
	पूर्णांक status;
	atomic_t in_progress;
	/* Direct probe requests workaround */
	काष्ठा delayed_work probe_work;
	पूर्णांक direct_probe;
पूर्ण;

पूर्णांक cw1200_hw_scan(काष्ठा ieee80211_hw *hw,
		   काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_scan_request *hw_req);
व्योम cw1200_scan_work(काष्ठा work_काष्ठा *work);
व्योम cw1200_scan_समयout(काष्ठा work_काष्ठा *work);
व्योम cw1200_clear_recent_scan_work(काष्ठा work_काष्ठा *work);
व्योम cw1200_scan_complete_cb(काष्ठा cw1200_common *priv,
			     काष्ठा wsm_scan_complete *arg);
व्योम cw1200_scan_failed_cb(काष्ठा cw1200_common *priv);

/* ******************************************************************** */
/* Raw probe requests TX workaround					*/
व्योम cw1200_probe_work(काष्ठा work_काष्ठा *work);

#पूर्ण_अगर
