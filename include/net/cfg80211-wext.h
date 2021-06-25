<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __NET_CFG80211_WEXT_H
#घोषणा __NET_CFG80211_WEXT_H
/*
 * 802.11 device and configuration पूर्णांकerface -- wext handlers
 *
 * Copyright 2006-2010	Johannes Berg <johannes@sipsolutions.net>
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/wireless.h>
#समावेश <net/iw_handler.h>

/*
 * Temporary wext handlers & helper functions
 *
 * These are used only by drivers that aren't yet fully
 * converted to cfg80211.
 */
पूर्णांक cfg80211_wext_giwname(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  अक्षर *name, अक्षर *extra);
पूर्णांक cfg80211_wext_siwmode(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			  u32 *mode, अक्षर *extra);
पूर्णांक cfg80211_wext_giwmode(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			  u32 *mode, अक्षर *extra);
पूर्णांक cfg80211_wext_siwscan(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra);
पूर्णांक cfg80211_wext_giwscan(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_poपूर्णांक *data, अक्षर *extra);
पूर्णांक cfg80211_wext_giwrange(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   काष्ठा iw_poपूर्णांक *data, अक्षर *extra);
पूर्णांक cfg80211_wext_siwrts(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 काष्ठा iw_param *rts, अक्षर *extra);
पूर्णांक cfg80211_wext_giwrts(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 काष्ठा iw_param *rts, अक्षर *extra);
पूर्णांक cfg80211_wext_siwfrag(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_param *frag, अक्षर *extra);
पूर्णांक cfg80211_wext_giwfrag(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_param *frag, अक्षर *extra);
पूर्णांक cfg80211_wext_giwretry(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   काष्ठा iw_param *retry, अक्षर *extra);

#पूर्ण_अगर /* __NET_CFG80211_WEXT_H */
