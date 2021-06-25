<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Implementation of mac80211 API.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 */
#अगर_अघोषित WFX_STA_H
#घोषणा WFX_STA_H

#समावेश <net/mac80211.h>

काष्ठा wfx_dev;
काष्ठा wfx_vअगर;

काष्ठा wfx_sta_priv अणु
	पूर्णांक link_id;
	पूर्णांक vअगर_id;
पूर्ण;

// mac80211 पूर्णांकerface
पूर्णांक wfx_start(काष्ठा ieee80211_hw *hw);
व्योम wfx_stop(काष्ठा ieee80211_hw *hw);
पूर्णांक wfx_config(काष्ठा ieee80211_hw *hw, u32 changed);
पूर्णांक wfx_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 value);
व्योम wfx_set_शेष_unicast_key(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर, पूर्णांक idx);
व्योम wfx_configure_filter(काष्ठा ieee80211_hw *hw, अचिन्हित पूर्णांक changed_flags,
			  अचिन्हित पूर्णांक *total_flags, u64 unused);

पूर्णांक wfx_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर);
व्योम wfx_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक wfx_start_ap(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर);
व्योम wfx_stop_ap(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक wfx_join_ibss(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर);
व्योम wfx_leave_ibss(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक wfx_conf_tx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		u16 queue, स्थिर काष्ठा ieee80211_tx_queue_params *params);
व्योम wfx_bss_info_changed(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			  काष्ठा ieee80211_bss_conf *info, u32 changed);
पूर्णांक wfx_sta_add(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		काष्ठा ieee80211_sta *sta);
पूर्णांक wfx_sta_हटाओ(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_sta *sta);
व्योम wfx_sta_notअगरy(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		    क्रमागत sta_notअगरy_cmd cmd, काष्ठा ieee80211_sta *sta);
पूर्णांक wfx_set_tim(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_sta *sta, bool set);
पूर्णांक wfx_ampdu_action(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		     काष्ठा ieee80211_ampdu_params *params);
पूर्णांक wfx_add_chanctx(काष्ठा ieee80211_hw *hw,
		    काष्ठा ieee80211_chanctx_conf *conf);
व्योम wfx_हटाओ_chanctx(काष्ठा ieee80211_hw *hw,
			काष्ठा ieee80211_chanctx_conf *conf);
व्योम wfx_change_chanctx(काष्ठा ieee80211_hw *hw,
			काष्ठा ieee80211_chanctx_conf *conf, u32 changed);
पूर्णांक wfx_assign_vअगर_chanctx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_chanctx_conf *conf);
व्योम wfx_unassign_vअगर_chanctx(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_chanctx_conf *conf);

// WSM Callbacks
व्योम wfx_cooling_समयout_work(काष्ठा work_काष्ठा *work);
व्योम wfx_suspend_hot_dev(काष्ठा wfx_dev *wdev, क्रमागत sta_notअगरy_cmd cmd);
व्योम wfx_suspend_resume_mc(काष्ठा wfx_vअगर *wvअगर, क्रमागत sta_notअगरy_cmd cmd);
व्योम wfx_event_report_rssi(काष्ठा wfx_vअगर *wvअगर, u8 raw_rcpi_rssi);
पूर्णांक wfx_update_pm(काष्ठा wfx_vअगर *wvअगर);

// Other Helpers
व्योम wfx_reset(काष्ठा wfx_vअगर *wvअगर);
u32 wfx_rate_mask_to_hw(काष्ठा wfx_dev *wdev, u32 rates);

#पूर्ण_अगर /* WFX_STA_H */
