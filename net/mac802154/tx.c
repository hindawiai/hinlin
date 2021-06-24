<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2007-2012 Siemens AG
 *
 * Written by:
 * Dmitry Eremin-Solenikov <dbaryshkov@gmail.com>
 * Sergey Lapin <slapin@ossfans.org>
 * Maxim Gorbachyov <maxim.gorbachev@siemens.com>
 * Alexander Smirnov <alex.bluesman.smirnov@gmail.com>
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/crc-ccitt.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <net/rtnetlink.h>
#समावेश <net/ieee802154_netdev.h>
#समावेश <net/mac802154.h>
#समावेश <net/cfg802154.h>

#समावेश "ieee802154_i.h"
#समावेश "driver-ops.h"

व्योम ieee802154_xmit_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee802154_local *local =
		container_of(work, काष्ठा ieee802154_local, tx_work);
	काष्ठा sk_buff *skb = local->tx_skb;
	काष्ठा net_device *dev = skb->dev;
	पूर्णांक res;

	res = drv_xmit_sync(local, skb);
	अगर (res)
		जाओ err_tx;

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	ieee802154_xmit_complete(&local->hw, skb, false);

	वापस;

err_tx:
	/* Restart the netअगर queue on each sub_अगर_data object. */
	ieee802154_wake_queue(&local->hw);
	kमुक्त_skb(skb);
	netdev_dbg(dev, "transmission failed\n");
पूर्ण

अटल netdev_tx_t
ieee802154_tx(काष्ठा ieee802154_local *local, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = skb->dev;
	पूर्णांक ret;

	अगर (!(local->hw.flags & IEEE802154_HW_TX_OMIT_CKSUM)) अणु
		काष्ठा sk_buff *nskb;
		u16 crc;

		अगर (unlikely(skb_tailroom(skb) < IEEE802154_FCS_LEN)) अणु
			nskb = skb_copy_expand(skb, 0, IEEE802154_FCS_LEN,
					       GFP_ATOMIC);
			अगर (likely(nskb)) अणु
				consume_skb(skb);
				skb = nskb;
			पूर्ण अन्यथा अणु
				जाओ err_tx;
			पूर्ण
		पूर्ण

		crc = crc_ccitt(0, skb->data, skb->len);
		put_unaligned_le16(crc, skb_put(skb, 2));
	पूर्ण

	/* Stop the netअगर queue on each sub_अगर_data object. */
	ieee802154_stop_queue(&local->hw);

	/* async is priority, otherwise sync is fallback */
	अगर (local->ops->xmit_async) अणु
		अचिन्हित पूर्णांक len = skb->len;

		ret = drv_xmit_async(local, skb);
		अगर (ret) अणु
			ieee802154_wake_queue(&local->hw);
			जाओ err_tx;
		पूर्ण

		dev->stats.tx_packets++;
		dev->stats.tx_bytes += len;
	पूर्ण अन्यथा अणु
		local->tx_skb = skb;
		queue_work(local->workqueue, &local->tx_work);
	पूर्ण

	वापस NETDEV_TX_OK;

err_tx:
	kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

netdev_tx_t
ieee802154_monitor_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);

	skb->skb_iअगर = dev->अगरindex;

	वापस ieee802154_tx(sdata->local, skb);
पूर्ण

netdev_tx_t
ieee802154_subअगर_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	पूर्णांक rc;

	/* TODO we should move it to wpan_dev_hard_header and dev_hard_header
	 * functions. The reason is wireshark will show a mac header which is
	 * with security fields but the payload is not encrypted.
	 */
	rc = mac802154_llsec_encrypt(&sdata->sec, skb);
	अगर (rc) अणु
		netdev_warn(dev, "encryption failed: %i\n", rc);
		kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	skb->skb_iअगर = dev->अगरindex;

	वापस ieee802154_tx(sdata->local, skb);
पूर्ण
