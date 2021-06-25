<शैली गुरु>
/*
   BNEP implementation क्रम Linux Bluetooth stack (BlueZ).
   Copyright (C) 2001-2002 Inventel Systemes
   Written 2001-2002 by
	Clथऊment Moreau <clement.moreau@inventel.fr>
	David Libault  <david.libault@inventel.fr>

   Copyright (C) 2002 Maxim Krasnyansky <maxk@qualcomm.com>

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INसूचीECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*/

#समावेश <linux/etherdevice.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <net/bluetooth/l2cap.h>

#समावेश "bnep.h"

#घोषणा BNEP_TX_QUEUE_LEN 20

अटल पूर्णांक bnep_net_खोलो(काष्ठा net_device *dev)
अणु
	netअगर_start_queue(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक bnep_net_बंद(काष्ठा net_device *dev)
अणु
	netअगर_stop_queue(dev);
	वापस 0;
पूर्ण

अटल व्योम bnep_net_set_mc_list(काष्ठा net_device *dev)
अणु
#अगर_घोषित CONFIG_BT_BNEP_MC_FILTER
	काष्ठा bnep_session *s = netdev_priv(dev);
	काष्ठा sock *sk = s->sock->sk;
	काष्ठा bnep_set_filter_req *r;
	काष्ठा sk_buff *skb;
	पूर्णांक size;

	BT_DBG("%s mc_count %d", dev->name, netdev_mc_count(dev));

	size = माप(*r) + (BNEP_MAX_MULTICAST_FILTERS + 1) * ETH_ALEN * 2;
	skb  = alloc_skb(size, GFP_ATOMIC);
	अगर (!skb) अणु
		BT_ERR("%s Multicast list allocation failed", dev->name);
		वापस;
	पूर्ण

	r = (व्योम *) skb->data;
	__skb_put(skb, माप(*r));

	r->type = BNEP_CONTROL;
	r->ctrl = BNEP_FILTER_MULTI_ADDR_SET;

	अगर (dev->flags & (IFF_PROMISC | IFF_ALLMULTI)) अणु
		u8 start[ETH_ALEN] = अणु 0x01 पूर्ण;

		/* Request all addresses */
		__skb_put_data(skb, start, ETH_ALEN);
		__skb_put_data(skb, dev->broadcast, ETH_ALEN);
		r->len = htons(ETH_ALEN * 2);
	पूर्ण अन्यथा अणु
		काष्ठा netdev_hw_addr *ha;
		पूर्णांक i, len = skb->len;

		अगर (dev->flags & IFF_BROADCAST) अणु
			__skb_put_data(skb, dev->broadcast, ETH_ALEN);
			__skb_put_data(skb, dev->broadcast, ETH_ALEN);
		पूर्ण

		/* FIXME: We should group addresses here. */

		i = 0;
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			अगर (i == BNEP_MAX_MULTICAST_FILTERS)
				अवरोध;
			__skb_put_data(skb, ha->addr, ETH_ALEN);
			__skb_put_data(skb, ha->addr, ETH_ALEN);

			i++;
		पूर्ण
		r->len = htons(skb->len - len);
	पूर्ण

	skb_queue_tail(&sk->sk_ग_लिखो_queue, skb);
	wake_up_पूर्णांकerruptible(sk_sleep(sk));
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक bnep_net_set_mac_addr(काष्ठा net_device *dev, व्योम *arg)
अणु
	BT_DBG("%s", dev->name);
	वापस 0;
पूर्ण

अटल व्योम bnep_net_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	BT_DBG("net_timeout");
	netअगर_wake_queue(dev);
पूर्ण

#अगर_घोषित CONFIG_BT_BNEP_MC_FILTER
अटल पूर्णांक bnep_net_mc_filter(काष्ठा sk_buff *skb, काष्ठा bnep_session *s)
अणु
	काष्ठा ethhdr *eh = (व्योम *) skb->data;

	अगर ((eh->h_dest[0] & 1) && !test_bit(bnep_mc_hash(eh->h_dest), (uदीर्घ *) &s->mc_filter))
		वापस 1;
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_BT_BNEP_PROTO_FILTER
/* Determine ether protocol. Based on eth_type_trans. */
अटल u16 bnep_net_eth_proto(काष्ठा sk_buff *skb)
अणु
	काष्ठा ethhdr *eh = (व्योम *) skb->data;
	u16 proto = ntohs(eh->h_proto);

	अगर (proto >= ETH_P_802_3_MIN)
		वापस proto;

	अगर (get_unaligned((__be16 *) skb->data) == htons(0xFFFF))
		वापस ETH_P_802_3;

	वापस ETH_P_802_2;
पूर्ण

अटल पूर्णांक bnep_net_proto_filter(काष्ठा sk_buff *skb, काष्ठा bnep_session *s)
अणु
	u16 proto = bnep_net_eth_proto(skb);
	काष्ठा bnep_proto_filter *f = s->proto_filter;
	पूर्णांक i;

	क्रम (i = 0; i < BNEP_MAX_PROTO_FILTERS && f[i].end; i++) अणु
		अगर (proto >= f[i].start && proto <= f[i].end)
			वापस 0;
	पूर्ण

	BT_DBG("BNEP: filtered skb %p, proto 0x%.4x", skb, proto);
	वापस 1;
पूर्ण
#पूर्ण_अगर

अटल netdev_tx_t bnep_net_xmit(काष्ठा sk_buff *skb,
				 काष्ठा net_device *dev)
अणु
	काष्ठा bnep_session *s = netdev_priv(dev);
	काष्ठा sock *sk = s->sock->sk;

	BT_DBG("skb %p, dev %p", skb, dev);

#अगर_घोषित CONFIG_BT_BNEP_MC_FILTER
	अगर (bnep_net_mc_filter(skb, s)) अणु
		kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_BT_BNEP_PROTO_FILTER
	अगर (bnep_net_proto_filter(skb, s)) अणु
		kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण
#पूर्ण_अगर

	/*
	 * We cannot send L2CAP packets from here as we are potentially in a bh.
	 * So we have to queue them and wake up session thपढ़ो which is sleeping
	 * on the sk_sleep(sk).
	 */
	netअगर_trans_update(dev);
	skb_queue_tail(&sk->sk_ग_लिखो_queue, skb);
	wake_up_पूर्णांकerruptible(sk_sleep(sk));

	अगर (skb_queue_len(&sk->sk_ग_लिखो_queue) >= BNEP_TX_QUEUE_LEN) अणु
		BT_DBG("tx queue is full");

		/* Stop queuing.
		 * Session thपढ़ो will करो netअगर_wake_queue() */
		netअगर_stop_queue(dev);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा net_device_ops bnep_netdev_ops = अणु
	.nकरो_खोलो            = bnep_net_खोलो,
	.nकरो_stop            = bnep_net_बंद,
	.nकरो_start_xmit	     = bnep_net_xmit,
	.nकरो_validate_addr   = eth_validate_addr,
	.nकरो_set_rx_mode     = bnep_net_set_mc_list,
	.nकरो_set_mac_address = bnep_net_set_mac_addr,
	.nकरो_tx_समयout      = bnep_net_समयout,

पूर्ण;

व्योम bnep_net_setup(काष्ठा net_device *dev)
अणु

	eth_broadcast_addr(dev->broadcast);
	dev->addr_len = ETH_ALEN;

	ether_setup(dev);
	dev->min_mtu = 0;
	dev->max_mtu = ETH_MAX_MTU;
	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
	dev->netdev_ops = &bnep_netdev_ops;

	dev->watchकरोg_समयo  = HZ * 2;
पूर्ण
