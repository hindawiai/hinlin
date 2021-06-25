<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2013 Broadcom Corporation
 */
#अगर_अघोषित WL_BTCOEX_H_
#घोषणा WL_BTCOEX_H_

क्रमागत brcmf_btcoex_mode अणु
	BRCMF_BTCOEX_DISABLED,
	BRCMF_BTCOEX_ENABLED
पूर्ण;

पूर्णांक brcmf_btcoex_attach(काष्ठा brcmf_cfg80211_info *cfg);
व्योम brcmf_btcoex_detach(काष्ठा brcmf_cfg80211_info *cfg);
पूर्णांक brcmf_btcoex_set_mode(काष्ठा brcmf_cfg80211_vअगर *vअगर,
			  क्रमागत brcmf_btcoex_mode mode, u16 duration);

#पूर्ण_अगर /* WL_BTCOEX_H_ */
