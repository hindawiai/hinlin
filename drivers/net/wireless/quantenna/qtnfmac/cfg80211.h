<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (c) 2015-2016 Quantenna Communications. All rights reserved. */

#अगर_अघोषित _QTN_FMAC_CFG80211_H_
#घोषणा _QTN_FMAC_CFG80211_H_

#समावेश <net/cfg80211.h>

#समावेश "core.h"

पूर्णांक qtnf_wiphy_रेजिस्टर(काष्ठा qtnf_hw_info *hw_info, काष्ठा qtnf_wmac *mac);
पूर्णांक qtnf_del_भव_पूर्णांकf(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev);
व्योम qtnf_cfg80211_vअगर_reset(काष्ठा qtnf_vअगर *vअगर);
व्योम qtnf_band_init_rates(काष्ठा ieee80211_supported_band *band);
व्योम qtnf_band_setup_htvht_caps(काष्ठा qtnf_mac_info *macinfo,
				काष्ठा ieee80211_supported_band *band);

#पूर्ण_अगर /* _QTN_FMAC_CFG80211_H_ */
