<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MAC80211_DEBUG_H
#घोषणा __MAC80211_DEBUG_H
#समावेश <net/cfg80211.h>

#अगर_घोषित CONFIG_MAC80211_OCB_DEBUG
#घोषणा MAC80211_OCB_DEBUG 1
#अन्यथा
#घोषणा MAC80211_OCB_DEBUG 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_MAC80211_IBSS_DEBUG
#घोषणा MAC80211_IBSS_DEBUG 1
#अन्यथा
#घोषणा MAC80211_IBSS_DEBUG 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_MAC80211_PS_DEBUG
#घोषणा MAC80211_PS_DEBUG 1
#अन्यथा
#घोषणा MAC80211_PS_DEBUG 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_MAC80211_HT_DEBUG
#घोषणा MAC80211_HT_DEBUG 1
#अन्यथा
#घोषणा MAC80211_HT_DEBUG 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_MAC80211_MPL_DEBUG
#घोषणा MAC80211_MPL_DEBUG 1
#अन्यथा
#घोषणा MAC80211_MPL_DEBUG 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_MAC80211_MPATH_DEBUG
#घोषणा MAC80211_MPATH_DEBUG 1
#अन्यथा
#घोषणा MAC80211_MPATH_DEBUG 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_MAC80211_MHWMP_DEBUG
#घोषणा MAC80211_MHWMP_DEBUG 1
#अन्यथा
#घोषणा MAC80211_MHWMP_DEBUG 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_MAC80211_MESH_SYNC_DEBUG
#घोषणा MAC80211_MESH_SYNC_DEBUG 1
#अन्यथा
#घोषणा MAC80211_MESH_SYNC_DEBUG 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_MAC80211_MESH_CSA_DEBUG
#घोषणा MAC80211_MESH_CSA_DEBUG 1
#अन्यथा
#घोषणा MAC80211_MESH_CSA_DEBUG 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_MAC80211_MESH_PS_DEBUG
#घोषणा MAC80211_MESH_PS_DEBUG 1
#अन्यथा
#घोषणा MAC80211_MESH_PS_DEBUG 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_MAC80211_TDLS_DEBUG
#घोषणा MAC80211_TDLS_DEBUG 1
#अन्यथा
#घोषणा MAC80211_TDLS_DEBUG 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_MAC80211_STA_DEBUG
#घोषणा MAC80211_STA_DEBUG 1
#अन्यथा
#घोषणा MAC80211_STA_DEBUG 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_MAC80211_MLME_DEBUG
#घोषणा MAC80211_MLME_DEBUG 1
#अन्यथा
#घोषणा MAC80211_MLME_DEBUG 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_MAC80211_MESSAGE_TRACING
व्योम __sdata_info(स्थिर अक्षर *fmt, ...) __म_लिखो(1, 2);
व्योम __sdata_dbg(bool prपूर्णांक, स्थिर अक्षर *fmt, ...) __म_लिखो(2, 3);
व्योम __sdata_err(स्थिर अक्षर *fmt, ...) __म_लिखो(1, 2);
व्योम __wiphy_dbg(काष्ठा wiphy *wiphy, bool prपूर्णांक, स्थिर अक्षर *fmt, ...)
	__म_लिखो(3, 4);

#घोषणा _sdata_info(sdata, fmt, ...)					\
	__sdata_info("%s: " fmt, (sdata)->name, ##__VA_ARGS__)
#घोषणा _sdata_dbg(prपूर्णांक, sdata, fmt, ...)				\
	__sdata_dbg(prपूर्णांक, "%s: " fmt, (sdata)->name, ##__VA_ARGS__)
#घोषणा _sdata_err(sdata, fmt, ...)					\
	__sdata_err("%s: " fmt, (sdata)->name, ##__VA_ARGS__)
#घोषणा _wiphy_dbg(prपूर्णांक, wiphy, fmt, ...)				\
	__wiphy_dbg(wiphy, prपूर्णांक, fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा _sdata_info(sdata, fmt, ...)					\
करो अणु									\
	pr_info("%s: " fmt,						\
		(sdata)->name, ##__VA_ARGS__);				\
पूर्ण जबतक (0)

#घोषणा _sdata_dbg(prपूर्णांक, sdata, fmt, ...)				\
करो अणु									\
	अगर (prपूर्णांक)							\
		pr_debug("%s: " fmt,					\
			 (sdata)->name, ##__VA_ARGS__);			\
पूर्ण जबतक (0)

#घोषणा _sdata_err(sdata, fmt, ...)					\
करो अणु									\
	pr_err("%s: " fmt,						\
	       (sdata)->name, ##__VA_ARGS__);				\
पूर्ण जबतक (0)

#घोषणा _wiphy_dbg(prपूर्णांक, wiphy, fmt, ...)				\
करो अणु									\
	अगर (prपूर्णांक)							\
		wiphy_dbg((wiphy), fmt, ##__VA_ARGS__);			\
पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा sdata_info(sdata, fmt, ...)					\
	_sdata_info(sdata, fmt, ##__VA_ARGS__)
#घोषणा sdata_err(sdata, fmt, ...)					\
	_sdata_err(sdata, fmt, ##__VA_ARGS__)
#घोषणा sdata_dbg(sdata, fmt, ...)					\
	_sdata_dbg(1, sdata, fmt, ##__VA_ARGS__)

#घोषणा ht_dbg(sdata, fmt, ...)						\
	_sdata_dbg(MAC80211_HT_DEBUG,					\
		   sdata, fmt, ##__VA_ARGS__)

#घोषणा ht_dbg_ratelimited(sdata, fmt, ...)				\
	_sdata_dbg(MAC80211_HT_DEBUG && net_ratelimit(),		\
		   sdata, fmt, ##__VA_ARGS__)

#घोषणा ocb_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_OCB_DEBUG,					\
		   sdata, fmt, ##__VA_ARGS__)

#घोषणा ibss_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_IBSS_DEBUG,					\
		   sdata, fmt, ##__VA_ARGS__)

#घोषणा ps_dbg(sdata, fmt, ...)						\
	_sdata_dbg(MAC80211_PS_DEBUG,					\
		   sdata, fmt, ##__VA_ARGS__)

#घोषणा ps_dbg_hw(hw, fmt, ...)						\
	_wiphy_dbg(MAC80211_PS_DEBUG,					\
		   (hw)->wiphy, fmt, ##__VA_ARGS__)

#घोषणा ps_dbg_ratelimited(sdata, fmt, ...)				\
	_sdata_dbg(MAC80211_PS_DEBUG && net_ratelimit(),		\
		   sdata, fmt, ##__VA_ARGS__)

#घोषणा mpl_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_MPL_DEBUG,					\
		   sdata, fmt, ##__VA_ARGS__)

#घोषणा mpath_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_MPATH_DEBUG,				\
		   sdata, fmt, ##__VA_ARGS__)

#घोषणा mhwmp_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_MHWMP_DEBUG,				\
		   sdata, fmt, ##__VA_ARGS__)

#घोषणा msync_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_MESH_SYNC_DEBUG,				\
		   sdata, fmt, ##__VA_ARGS__)

#घोषणा mcsa_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_MESH_CSA_DEBUG,				\
		   sdata, fmt, ##__VA_ARGS__)

#घोषणा mps_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_MESH_PS_DEBUG,				\
		   sdata, fmt, ##__VA_ARGS__)

#घोषणा tdls_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_TDLS_DEBUG,					\
		   sdata, fmt, ##__VA_ARGS__)

#घोषणा sta_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_STA_DEBUG,					\
		   sdata, fmt, ##__VA_ARGS__)

#घोषणा mlme_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_MLME_DEBUG,					\
		   sdata, fmt, ##__VA_ARGS__)

#घोषणा mlme_dbg_ratelimited(sdata, fmt, ...)				\
	_sdata_dbg(MAC80211_MLME_DEBUG && net_ratelimit(),		\
		   sdata, fmt, ##__VA_ARGS__)

#पूर्ण_अगर /* __MAC80211_DEBUG_H */
