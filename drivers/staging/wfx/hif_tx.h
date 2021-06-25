<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Implementation of host-to-chip commands (aka request/confirmation) of WFxxx
 * Split Mac (WSM) API.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 * Copyright (C) 2010, ST-Ericsson SA
 */
#अगर_अघोषित WFX_HIF_TX_H
#घोषणा WFX_HIF_TX_H

काष्ठा ieee80211_channel;
काष्ठा ieee80211_bss_conf;
काष्ठा ieee80211_tx_queue_params;
काष्ठा cfg80211_scan_request;
काष्ठा hअगर_req_add_key;
काष्ठा wfx_dev;
काष्ठा wfx_vअगर;

काष्ठा wfx_hअगर_cmd अणु
	काष्ठा mutex      lock;
	काष्ठा completion पढ़ोy;
	काष्ठा completion करोne;
	काष्ठा hअगर_msg    *buf_send;
	व्योम              *buf_recv;
	माप_प्रकार            len_recv;
	पूर्णांक               ret;
पूर्ण;

व्योम wfx_init_hअगर_cmd(काष्ठा wfx_hअगर_cmd *wfx_hअगर_cmd);
पूर्णांक wfx_cmd_send(काष्ठा wfx_dev *wdev, काष्ठा hअगर_msg *request,
		 व्योम *reply, माप_प्रकार reply_len, bool async);

पूर्णांक hअगर_shutकरोwn(काष्ठा wfx_dev *wdev);
पूर्णांक hअगर_configuration(काष्ठा wfx_dev *wdev, स्थिर u8 *conf, माप_प्रकार len);
पूर्णांक hअगर_reset(काष्ठा wfx_vअगर *wvअगर, bool reset_stat);
पूर्णांक hअगर_पढ़ो_mib(काष्ठा wfx_dev *wdev, पूर्णांक vअगर_id, u16 mib_id,
		 व्योम *buf, माप_प्रकार buf_size);
पूर्णांक hअगर_ग_लिखो_mib(काष्ठा wfx_dev *wdev, पूर्णांक vअगर_id, u16 mib_id,
		  व्योम *buf, माप_प्रकार buf_size);
पूर्णांक hअगर_scan(काष्ठा wfx_vअगर *wvअगर, काष्ठा cfg80211_scan_request *req80211,
	     पूर्णांक chan_start, पूर्णांक chan_num, पूर्णांक *समयout);
पूर्णांक hअगर_stop_scan(काष्ठा wfx_vअगर *wvअगर);
पूर्णांक hअगर_join(काष्ठा wfx_vअगर *wvअगर, स्थिर काष्ठा ieee80211_bss_conf *conf,
	     काष्ठा ieee80211_channel *channel, स्थिर u8 *ssid, पूर्णांक ssidlen);
पूर्णांक hअगर_set_pm(काष्ठा wfx_vअगर *wvअगर, bool ps, पूर्णांक dynamic_ps_समयout);
पूर्णांक hअगर_set_bss_params(काष्ठा wfx_vअगर *wvअगर, पूर्णांक aid, पूर्णांक beacon_lost_count);
पूर्णांक hअगर_add_key(काष्ठा wfx_dev *wdev, स्थिर काष्ठा hअगर_req_add_key *arg);
पूर्णांक hअगर_हटाओ_key(काष्ठा wfx_dev *wdev, पूर्णांक idx);
पूर्णांक hअगर_set_edca_queue_params(काष्ठा wfx_vअगर *wvअगर, u16 queue,
			      स्थिर काष्ठा ieee80211_tx_queue_params *arg);
पूर्णांक hअगर_start(काष्ठा wfx_vअगर *wvअगर, स्थिर काष्ठा ieee80211_bss_conf *conf,
	      स्थिर काष्ठा ieee80211_channel *channel);
पूर्णांक hअगर_beacon_transmit(काष्ठा wfx_vअगर *wvअगर, bool enable);
पूर्णांक hअगर_map_link(काष्ठा wfx_vअगर *wvअगर,
		 bool unmap, u8 *mac_addr, पूर्णांक sta_id, bool mfp);
पूर्णांक hअगर_update_ie_beacon(काष्ठा wfx_vअगर *wvअगर, स्थिर u8 *ies, माप_प्रकार ies_len);

#पूर्ण_अगर
