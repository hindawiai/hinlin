<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PTP 1588 घड़ी support - support क्रम बारtamping in PHY devices
 *
 * Copyright (C) 2010 OMICRON electronics GmbH
 */
#समावेश <linux/errqueue.h>
#समावेश <linux/phy.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/export.h>

अटल अचिन्हित पूर्णांक classअगरy(स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (likely(skb->dev && skb->dev->phydev &&
		   skb->dev->phydev->mii_ts))
		वापस ptp_classअगरy_raw(skb);
	अन्यथा
		वापस PTP_CLASS_NONE;
पूर्ण

व्योम skb_clone_tx_बारtamp(काष्ठा sk_buff *skb)
अणु
	काष्ठा mii_बारtamper *mii_ts;
	काष्ठा sk_buff *clone;
	अचिन्हित पूर्णांक type;

	अगर (!skb->sk)
		वापस;

	type = classअगरy(skb);
	अगर (type == PTP_CLASS_NONE)
		वापस;

	mii_ts = skb->dev->phydev->mii_ts;
	अगर (likely(mii_ts->txtstamp)) अणु
		clone = skb_clone_sk(skb);
		अगर (!clone)
			वापस;
		mii_ts->txtstamp(mii_ts, clone, type);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(skb_clone_tx_बारtamp);

bool skb_defer_rx_बारtamp(काष्ठा sk_buff *skb)
अणु
	काष्ठा mii_बारtamper *mii_ts;
	अचिन्हित पूर्णांक type;

	अगर (!skb->dev || !skb->dev->phydev || !skb->dev->phydev->mii_ts)
		वापस false;

	अगर (skb_headroom(skb) < ETH_HLEN)
		वापस false;

	__skb_push(skb, ETH_HLEN);

	type = ptp_classअगरy_raw(skb);

	__skb_pull(skb, ETH_HLEN);

	अगर (type == PTP_CLASS_NONE)
		वापस false;

	mii_ts = skb->dev->phydev->mii_ts;
	अगर (likely(mii_ts->rxtstamp))
		वापस mii_ts->rxtstamp(mii_ts, skb, type);

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(skb_defer_rx_बारtamp);
