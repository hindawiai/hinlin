<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// mcp251xfd - Microchip MCP251xFD Family CAN controller driver
//
// Copyright (c) 2021 Pengutronix,
//               Marc Kleine-Budde <kernel@pengutronix.de>
//

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/workqueue.h>

#समावेश "mcp251xfd.h"

अटल u64 mcp251xfd_बारtamp_पढ़ो(स्थिर काष्ठा cyclecounter *cc)
अणु
	काष्ठा mcp251xfd_priv *priv;
	u32 बारtamp = 0;
	पूर्णांक err;

	priv = container_of(cc, काष्ठा mcp251xfd_priv, cc);
	err = mcp251xfd_get_बारtamp(priv, &बारtamp);
	अगर (err)
		netdev_err(priv->ndev,
			   "Error %d while reading timestamp. HW timestamps may be inaccurate.",
			   err);

	वापस बारtamp;
पूर्ण

अटल व्योम mcp251xfd_बारtamp_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delayed_work = to_delayed_work(work);
	काष्ठा mcp251xfd_priv *priv;

	priv = container_of(delayed_work, काष्ठा mcp251xfd_priv, बारtamp);
	समयcounter_पढ़ो(&priv->tc);

	schedule_delayed_work(&priv->बारtamp,
			      MCP251XFD_TIMESTAMP_WORK_DELAY_SEC * HZ);
पूर्ण

व्योम mcp251xfd_skb_set_बारtamp(काष्ठा mcp251xfd_priv *priv,
				 काष्ठा sk_buff *skb, u32 बारtamp)
अणु
	काष्ठा skb_shared_hwtstamps *hwtstamps = skb_hwtstamps(skb);
	u64 ns;

	ns = समयcounter_cyc2समय(&priv->tc, बारtamp);
	hwtstamps->hwtstamp = ns_to_kसमय(ns);
पूर्ण

व्योम mcp251xfd_बारtamp_init(काष्ठा mcp251xfd_priv *priv)
अणु
	काष्ठा cyclecounter *cc = &priv->cc;

	cc->पढ़ो = mcp251xfd_बारtamp_पढ़ो;
	cc->mask = CYCLECOUNTER_MASK(32);
	cc->shअगरt = 1;
	cc->mult = घड़ीsource_hz2mult(priv->can.घड़ी.freq, cc->shअगरt);

	समयcounter_init(&priv->tc, &priv->cc, kसमय_get_real_ns());

	INIT_DELAYED_WORK(&priv->बारtamp, mcp251xfd_बारtamp_work);
	schedule_delayed_work(&priv->बारtamp,
			      MCP251XFD_TIMESTAMP_WORK_DELAY_SEC * HZ);
पूर्ण

व्योम mcp251xfd_बारtamp_stop(काष्ठा mcp251xfd_priv *priv)
अणु
	cancel_delayed_work_sync(&priv->बारtamp);
पूर्ण
