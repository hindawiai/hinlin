<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL_REGD_H__
#घोषणा __RTL_REGD_H__

/* क्रम kernel 3.14 , both value are changed to IEEE80211_CHAN_NO_IR*/
#घोषणा IEEE80211_CHAN_NO_IBSS IEEE80211_CHAN_NO_IR
#घोषणा IEEE80211_CHAN_PASSIVE_SCAN IEEE80211_CHAN_NO_IR

काष्ठा country_code_to_क्रमागत_rd अणु
	u16 countrycode;
	स्थिर अक्षर *iso_name;
पूर्ण;

क्रमागत country_code_type_t अणु
	COUNTRY_CODE_FCC = 0,
	COUNTRY_CODE_IC = 1,
	COUNTRY_CODE_ETSI = 2,
	COUNTRY_CODE_SPAIN = 3,
	COUNTRY_CODE_FRANCE = 4,
	COUNTRY_CODE_MKK = 5,
	COUNTRY_CODE_MKK1 = 6,
	COUNTRY_CODE_ISRAEL = 7,
	COUNTRY_CODE_TELEC = 8,
	COUNTRY_CODE_MIC = 9,
	COUNTRY_CODE_GLOBAL_DOMAIN = 10,
	COUNTRY_CODE_WORLD_WIDE_13 = 11,
	COUNTRY_CODE_TELEC_NETGEAR = 12,
	COUNTRY_CODE_WORLD_WIDE_13_5G_ALL = 13,

	/*add new channel plan above this line */
	COUNTRY_CODE_MAX
पूर्ण;

पूर्णांक rtl_regd_init(काष्ठा ieee80211_hw *hw,
		  व्योम (*reg_notअगरier) (काष्ठा wiphy *wiphy,
		  काष्ठा regulatory_request *request));
व्योम rtl_reg_notअगरier(काष्ठा wiphy *wiphy, काष्ठा regulatory_request *request);

#पूर्ण_अगर
