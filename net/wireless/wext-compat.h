<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __WEXT_COMPAT
#घोषणा __WEXT_COMPAT

#समावेश <net/iw_handler.h>
#समावेश <linux/wireless.h>

#अगर_घोषित CONFIG_CFG80211_WEXT_EXPORT
#घोषणा EXPORT_WEXT_HANDLER(h) EXPORT_SYMBOL_GPL(h)
#अन्यथा
#घोषणा EXPORT_WEXT_HANDLER(h)
#पूर्ण_अगर /* CONFIG_CFG80211_WEXT_EXPORT */

पूर्णांक cfg80211_ibss_wext_siwfreq(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       काष्ठा iw_freq *freq, अक्षर *extra);
पूर्णांक cfg80211_ibss_wext_giwfreq(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       काष्ठा iw_freq *freq, अक्षर *extra);
पूर्णांक cfg80211_ibss_wext_siwap(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     काष्ठा sockaddr *ap_addr, अक्षर *extra);
पूर्णांक cfg80211_ibss_wext_giwap(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     काष्ठा sockaddr *ap_addr, अक्षर *extra);
पूर्णांक cfg80211_ibss_wext_siwessid(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				काष्ठा iw_poपूर्णांक *data, अक्षर *ssid);
पूर्णांक cfg80211_ibss_wext_giwessid(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				काष्ठा iw_poपूर्णांक *data, अक्षर *ssid);

पूर्णांक cfg80211_mgd_wext_siwfreq(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      काष्ठा iw_freq *freq, अक्षर *extra);
पूर्णांक cfg80211_mgd_wext_giwfreq(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      काष्ठा iw_freq *freq, अक्षर *extra);
पूर्णांक cfg80211_mgd_wext_siwap(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    काष्ठा sockaddr *ap_addr, अक्षर *extra);
पूर्णांक cfg80211_mgd_wext_giwap(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    काष्ठा sockaddr *ap_addr, अक्षर *extra);
पूर्णांक cfg80211_mgd_wext_siwessid(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       काष्ठा iw_poपूर्णांक *data, अक्षर *ssid);
पूर्णांक cfg80211_mgd_wext_giwessid(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       काष्ठा iw_poपूर्णांक *data, अक्षर *ssid);

पूर्णांक cfg80211_wext_siwmlme(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_poपूर्णांक *data, अक्षर *extra);
पूर्णांक cfg80211_wext_siwgenie(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   काष्ठा iw_poपूर्णांक *data, अक्षर *extra);


पूर्णांक cfg80211_wext_freq(काष्ठा iw_freq *freq);


बाह्य स्थिर काष्ठा iw_handler_def cfg80211_wext_handler;
#पूर्ण_अगर /* __WEXT_COMPAT */
