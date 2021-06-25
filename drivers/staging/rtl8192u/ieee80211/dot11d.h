<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __INC_DOT11D_H
#घोषणा __INC_DOT11D_H

#समावेश "ieee80211.h"

काष्ठा chnl_txघातer_triple अणु
	u8  first_channel;
	u8  num_channels;
	u8  max_tx_pwr_dbm;
पूर्ण;

क्रमागत करोt11d_state अणु
	DOT11D_STATE_NONE = 0,
	DOT11D_STATE_LEARNED,
	DOT11D_STATE_DONE,
पूर्ण;

काष्ठा rt_करोt11d_info अणु
	u16 country_ie_len; /* > 0 अगर country_ie_buf[] contains valid country inक्रमmation element. */

	/*  country_ie_src_addr u16 aligned क्रम comparison and copy */
	u8  country_ie_src_addr[ETH_ALEN]; /* Source AP of the country IE. */
	u8  country_ie_buf[MAX_IE_LEN];
	u8  country_ie_watchकरोg;

	u8  channel_map[MAX_CHANNEL_NUMBER + 1];  /* !Value 0: Invalid, 1: Valid (active scan), 2: Valid (passive scan) */
	u8  max_tx_pwr_dbm_list[MAX_CHANNEL_NUMBER + 1];

	क्रमागत करोt11d_state state;
	u8  करोt11d_enabled; /* करोt11MultiDoमुख्यCapabilityEnabled */
पूर्ण;

#घोषणा GET_DOT11D_INFO(ieee_dev) ((काष्ठा rt_करोt11d_info *)((ieee_dev)->करोt11d_info))

#घोषणा IS_DOT11D_ENABLE(ieee_dev) (GET_DOT11D_INFO(ieee_dev)->करोt11d_enabled)
#घोषणा IS_COUNTRY_IE_VALID(ieee_dev) (GET_DOT11D_INFO(ieee_dev)->country_ie_len > 0)

#घोषणा IS_EQUAL_CIE_SRC(ieee_dev, addr) ether_addr_equal(GET_DOT11D_INFO(ieee_dev)->country_ie_src_addr, addr)
#घोषणा UPDATE_CIE_SRC(ieee_dev, addr) ether_addr_copy(GET_DOT11D_INFO(ieee_dev)->country_ie_src_addr, addr)

#घोषणा GET_CIE_WATCHDOG(ieee_dev) (GET_DOT11D_INFO(ieee_dev)->country_ie_watchकरोg)
#घोषणा RESET_CIE_WATCHDOG(ieee_dev) (GET_CIE_WATCHDOG(ieee_dev) = 0)
#घोषणा UPDATE_CIE_WATCHDOG(ieee_dev) (++GET_CIE_WATCHDOG(ieee_dev))

व्योम rtl8192u_करोt11d_init(काष्ठा ieee80211_device *dev);
व्योम करोt11d_reset(काष्ठा ieee80211_device *dev);
व्योम करोt11d_update_country_ie(काष्ठा ieee80211_device *dev,
			      u8 *addr,
			      u16 coutry_ie_len,
			      u8 *coutry_ie);
u8 करोt11d_get_max_tx_pwr_in_dbm(काष्ठा ieee80211_device *dev, u8 channel);
व्योम करोt11d_scan_complete(काष्ठा ieee80211_device *dev);
पूर्णांक is_legal_channel(काष्ठा ieee80211_device *dev, u8 channel);
पूर्णांक to_legal_channel(काष्ठा ieee80211_device *dev, u8 channel);

#पूर्ण_अगर /* #अगर_अघोषित __INC_DOT11D_H */
