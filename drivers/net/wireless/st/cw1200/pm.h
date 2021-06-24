<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Mac80211 घातer management पूर्णांकerface क्रम ST-Ericsson CW1200 mac80211 drivers
 *
 * Copyright (c) 2011, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 */

#अगर_अघोषित PM_H_INCLUDED
#घोषणा PM_H_INCLUDED

/* ******************************************************************** */
/* mac80211 API								*/

/* बाह्य */  काष्ठा cw1200_common;
/* निजी */ काष्ठा cw1200_suspend_state;

काष्ठा cw1200_pm_state अणु
	काष्ठा cw1200_suspend_state *suspend_state;
	काष्ठा समयr_list stay_awake;
	काष्ठा platक्रमm_device *pm_dev;
	spinlock_t lock; /* Protect access */
पूर्ण;

#अगर_घोषित CONFIG_PM
पूर्णांक cw1200_pm_init(काष्ठा cw1200_pm_state *pm,
		    काष्ठा cw1200_common *priv);
व्योम cw1200_pm_deinit(काष्ठा cw1200_pm_state *pm);
पूर्णांक cw1200_wow_suspend(काष्ठा ieee80211_hw *hw,
		       काष्ठा cfg80211_wowlan *wowlan);
पूर्णांक cw1200_can_suspend(काष्ठा cw1200_common *priv);
पूर्णांक cw1200_wow_resume(काष्ठा ieee80211_hw *hw);
व्योम cw1200_pm_stay_awake(काष्ठा cw1200_pm_state *pm,
			  अचिन्हित दीर्घ पंचांगo);
#अन्यथा
अटल अंतरभूत व्योम cw1200_pm_stay_awake(काष्ठा cw1200_pm_state *pm,
					अचिन्हित दीर्घ पंचांगo)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक cw1200_can_suspend(काष्ठा cw1200_common *priv)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
