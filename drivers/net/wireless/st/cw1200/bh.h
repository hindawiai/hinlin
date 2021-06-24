<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Device handling thपढ़ो पूर्णांकerface क्रम mac80211 ST-Ericsson CW1200 drivers
 *
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 */

#अगर_अघोषित CW1200_BH_H
#घोषणा CW1200_BH_H

/* बाह्य */ काष्ठा cw1200_common;

पूर्णांक cw1200_रेजिस्टर_bh(काष्ठा cw1200_common *priv);
व्योम cw1200_unरेजिस्टर_bh(काष्ठा cw1200_common *priv);
व्योम cw1200_irq_handler(काष्ठा cw1200_common *priv);
व्योम cw1200_bh_wakeup(काष्ठा cw1200_common *priv);
पूर्णांक cw1200_bh_suspend(काष्ठा cw1200_common *priv);
पूर्णांक cw1200_bh_resume(काष्ठा cw1200_common *priv);
/* Must be called from BH thपढ़ो. */
व्योम cw1200_enable_घातersave(काष्ठा cw1200_common *priv,
			     bool enable);
पूर्णांक wsm_release_tx_buffer(काष्ठा cw1200_common *priv, पूर्णांक count);

#पूर्ण_अगर /* CW1200_BH_H */
