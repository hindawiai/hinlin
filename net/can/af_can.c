<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/* af_can.c - Protocol family CAN core module
 *            (used by dअगरferent CAN protocol modules)
 *
 * Copyright (c) 2002-2017 Volkswagen Group Electronic Research
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of Volkswagen nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 *
 * Alternatively, provided that this notice is retained in full, this
 * software may be distributed under the terms of the GNU General
 * Public License ("GPL") version 2, in which हाल the provisions of the
 * GPL apply INSTEAD OF those given above.
 *
 * The provided data काष्ठाures and बाह्यal पूर्णांकerfaces from this code
 * are not restricted to be used by modules with a GPL compatible license.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/init.h>
#समावेश <linux/kmod.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/socket.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/can.h>
#समावेश <linux/can/core.h>
#समावेश <linux/can/skb.h>
#समावेश <linux/can/can-ml.h>
#समावेश <linux/ratelimit.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>

#समावेश "af_can.h"

MODULE_DESCRIPTION("Controller Area Network PF_CAN core");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Urs Thuermann <urs.thuermann@volkswagen.de>, "
	      "Oliver Hartkopp <oliver.hartkopp@volkswagen.de>");

MODULE_ALIAS_NETPROTO(PF_CAN);

अटल पूर्णांक stats_समयr __पढ़ो_mostly = 1;
module_param(stats_समयr, पूर्णांक, 0444);
MODULE_PARM_DESC(stats_समयr, "enable timer for statistics (default:on)");

अटल काष्ठा kmem_cache *rcv_cache __पढ़ो_mostly;

/* table of रेजिस्टरed CAN protocols */
अटल स्थिर काष्ठा can_proto __rcu *proto_tab[CAN_NPROTO] __पढ़ो_mostly;
अटल DEFINE_MUTEX(proto_tab_lock);

अटल atomic_t skbcounter = ATOMIC_INIT(0);

/* af_can socket functions */

व्योम can_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	skb_queue_purge(&sk->sk_receive_queue);
	skb_queue_purge(&sk->sk_error_queue);
पूर्ण
EXPORT_SYMBOL(can_sock_deकाष्ठा);

अटल स्थिर काष्ठा can_proto *can_get_proto(पूर्णांक protocol)
अणु
	स्थिर काष्ठा can_proto *cp;

	rcu_पढ़ो_lock();
	cp = rcu_dereference(proto_tab[protocol]);
	अगर (cp && !try_module_get(cp->prot->owner))
		cp = शून्य;
	rcu_पढ़ो_unlock();

	वापस cp;
पूर्ण

अटल अंतरभूत व्योम can_put_proto(स्थिर काष्ठा can_proto *cp)
अणु
	module_put(cp->prot->owner);
पूर्ण

अटल पूर्णांक can_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
		      पूर्णांक kern)
अणु
	काष्ठा sock *sk;
	स्थिर काष्ठा can_proto *cp;
	पूर्णांक err = 0;

	sock->state = SS_UNCONNECTED;

	अगर (protocol < 0 || protocol >= CAN_NPROTO)
		वापस -EINVAL;

	cp = can_get_proto(protocol);

#अगर_घोषित CONFIG_MODULES
	अगर (!cp) अणु
		/* try to load protocol module अगर kernel is modular */

		err = request_module("can-proto-%d", protocol);

		/* In हाल of error we only prपूर्णांक a message but करोn't
		 * वापस the error code immediately.  Below we will
		 * वापस -EPROTONOSUPPORT
		 */
		अगर (err)
			pr_err_ratelimited("can: request_module (can-proto-%d) failed.\n",
					   protocol);

		cp = can_get_proto(protocol);
	पूर्ण
#पूर्ण_अगर

	/* check क्रम available protocol and correct usage */

	अगर (!cp)
		वापस -EPROTONOSUPPORT;

	अगर (cp->type != sock->type) अणु
		err = -EPROTOTYPE;
		जाओ errout;
	पूर्ण

	sock->ops = cp->ops;

	sk = sk_alloc(net, PF_CAN, GFP_KERNEL, cp->prot, kern);
	अगर (!sk) अणु
		err = -ENOMEM;
		जाओ errout;
	पूर्ण

	sock_init_data(sock, sk);
	sk->sk_deकाष्ठा = can_sock_deकाष्ठा;

	अगर (sk->sk_prot->init)
		err = sk->sk_prot->init(sk);

	अगर (err) अणु
		/* release sk on errors */
		sock_orphan(sk);
		sock_put(sk);
	पूर्ण

 errout:
	can_put_proto(cp);
	वापस err;
पूर्ण

/* af_can tx path */

/**
 * can_send - transmit a CAN frame (optional with local loopback)
 * @skb: poपूर्णांकer to socket buffer with CAN frame in data section
 * @loop: loopback क्रम listeners on local CAN sockets (recommended शेष!)
 *
 * Due to the loopback this routine must not be called from hardirq context.
 *
 * Return:
 *  0 on success
 *  -ENETDOWN when the selected पूर्णांकerface is करोwn
 *  -ENOBUFS on full driver queue (see net_xmit_त्रुटि_सं())
 *  -ENOMEM when local loopback failed at calling skb_clone()
 *  -EPERM when trying to send on a non-CAN पूर्णांकerface
 *  -EMSGSIZE CAN frame size is bigger than CAN पूर्णांकerface MTU
 *  -EINVAL when the skb->data करोes not contain a valid CAN frame
 */
पूर्णांक can_send(काष्ठा sk_buff *skb, पूर्णांक loop)
अणु
	काष्ठा sk_buff *newskb = शून्य;
	काष्ठा canfd_frame *cfd = (काष्ठा canfd_frame *)skb->data;
	काष्ठा can_pkg_stats *pkg_stats = dev_net(skb->dev)->can.pkg_stats;
	पूर्णांक err = -EINVAL;

	अगर (skb->len == CAN_MTU) अणु
		skb->protocol = htons(ETH_P_CAN);
		अगर (unlikely(cfd->len > CAN_MAX_DLEN))
			जाओ inval_skb;
	पूर्ण अन्यथा अगर (skb->len == CANFD_MTU) अणु
		skb->protocol = htons(ETH_P_CANFD);
		अगर (unlikely(cfd->len > CANFD_MAX_DLEN))
			जाओ inval_skb;
	पूर्ण अन्यथा अणु
		जाओ inval_skb;
	पूर्ण

	/* Make sure the CAN frame can pass the selected CAN netdevice.
	 * As काष्ठाs can_frame and canfd_frame are similar, we can provide
	 * CAN FD frames to legacy CAN drivers as दीर्घ as the length is <= 8
	 */
	अगर (unlikely(skb->len > skb->dev->mtu && cfd->len > CAN_MAX_DLEN)) अणु
		err = -EMSGSIZE;
		जाओ inval_skb;
	पूर्ण

	अगर (unlikely(skb->dev->type != ARPHRD_CAN)) अणु
		err = -EPERM;
		जाओ inval_skb;
	पूर्ण

	अगर (unlikely(!(skb->dev->flags & IFF_UP))) अणु
		err = -ENETDOWN;
		जाओ inval_skb;
	पूर्ण

	skb->ip_summed = CHECKSUM_UNNECESSARY;

	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);

	अगर (loop) अणु
		/* local loopback of sent CAN frames */

		/* indication क्रम the CAN driver: करो loopback */
		skb->pkt_type = PACKET_LOOPBACK;

		/* The reference to the originating sock may be required
		 * by the receiving socket to check whether the frame is
		 * its own. Example: can_raw sockopt CAN_RAW_RECV_OWN_MSGS
		 * Thereक्रमe we have to ensure that skb->sk reमुख्यs the
		 * reference to the originating sock by restoring skb->sk
		 * after each skb_clone() or skb_orphan() usage.
		 */

		अगर (!(skb->dev->flags & IFF_ECHO)) अणु
			/* If the पूर्णांकerface is not capable to करो loopback
			 * itself, we करो it here.
			 */
			newskb = skb_clone(skb, GFP_ATOMIC);
			अगर (!newskb) अणु
				kमुक्त_skb(skb);
				वापस -ENOMEM;
			पूर्ण

			can_skb_set_owner(newskb, skb->sk);
			newskb->ip_summed = CHECKSUM_UNNECESSARY;
			newskb->pkt_type = PACKET_BROADCAST;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* indication क्रम the CAN driver: no loopback required */
		skb->pkt_type = PACKET_HOST;
	पूर्ण

	/* send to netdevice */
	err = dev_queue_xmit(skb);
	अगर (err > 0)
		err = net_xmit_त्रुटि_सं(err);

	अगर (err) अणु
		kमुक्त_skb(newskb);
		वापस err;
	पूर्ण

	अगर (newskb)
		netअगर_rx_ni(newskb);

	/* update statistics */
	pkg_stats->tx_frames++;
	pkg_stats->tx_frames_delta++;

	वापस 0;

inval_skb:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण
EXPORT_SYMBOL(can_send);

/* af_can rx path */

अटल काष्ठा can_dev_rcv_lists *can_dev_rcv_lists_find(काष्ठा net *net,
							काष्ठा net_device *dev)
अणु
	अगर (dev) अणु
		काष्ठा can_ml_priv *can_ml = can_get_ml_priv(dev);
		वापस &can_ml->dev_rcv_lists;
	पूर्ण अन्यथा अणु
		वापस net->can.rx_alldev_list;
	पूर्ण
पूर्ण

/**
 * effhash - hash function क्रम 29 bit CAN identअगरier reduction
 * @can_id: 29 bit CAN identअगरier
 *
 * Description:
 *  To reduce the linear traversal in one linked list of _single_ EFF CAN
 *  frame subscriptions the 29 bit identअगरier is mapped to 10 bits.
 *  (see CAN_EFF_RCV_HASH_BITS definition)
 *
 * Return:
 *  Hash value from 0x000 - 0x3FF ( enक्रमced by CAN_EFF_RCV_HASH_BITS mask )
 */
अटल अचिन्हित पूर्णांक effhash(canid_t can_id)
अणु
	अचिन्हित पूर्णांक hash;

	hash = can_id;
	hash ^= can_id >> CAN_EFF_RCV_HASH_BITS;
	hash ^= can_id >> (2 * CAN_EFF_RCV_HASH_BITS);

	वापस hash & ((1 << CAN_EFF_RCV_HASH_BITS) - 1);
पूर्ण

/**
 * can_rcv_list_find - determine optimal filterlist inside device filter काष्ठा
 * @can_id: poपूर्णांकer to CAN identअगरier of a given can_filter
 * @mask: poपूर्णांकer to CAN mask of a given can_filter
 * @dev_rcv_lists: poपूर्णांकer to the device filter काष्ठा
 *
 * Description:
 *  Returns the optimal filterlist to reduce the filter handling in the
 *  receive path. This function is called by service functions that need
 *  to रेजिस्टर or unरेजिस्टर a can_filter in the filter lists.
 *
 *  A filter matches in general, when
 *
 *          <received_can_id> & mask == can_id & mask
 *
 *  so every bit set in the mask (even CAN_EFF_FLAG, CAN_RTR_FLAG) describe
 *  relevant bits क्रम the filter.
 *
 *  The filter can be inverted (CAN_INV_FILTER bit set in can_id) or it can
 *  filter क्रम error messages (CAN_ERR_FLAG bit set in mask). For error msg
 *  frames there is a special filterlist and a special rx path filter handling.
 *
 * Return:
 *  Poपूर्णांकer to optimal filterlist क्रम the given can_id/mask pair.
 *  Consistency checked mask.
 *  Reduced can_id to have a preprocessed filter compare value.
 */
अटल काष्ठा hlist_head *can_rcv_list_find(canid_t *can_id, canid_t *mask,
					    काष्ठा can_dev_rcv_lists *dev_rcv_lists)
अणु
	canid_t inv = *can_id & CAN_INV_FILTER; /* save flag beक्रमe masking */

	/* filter क्रम error message frames in extra filterlist */
	अगर (*mask & CAN_ERR_FLAG) अणु
		/* clear CAN_ERR_FLAG in filter entry */
		*mask &= CAN_ERR_MASK;
		वापस &dev_rcv_lists->rx[RX_ERR];
	पूर्ण

	/* with cleared CAN_ERR_FLAG we have a simple mask/value filterpair */

#घोषणा CAN_EFF_RTR_FLAGS (CAN_EFF_FLAG | CAN_RTR_FLAG)

	/* ensure valid values in can_mask क्रम 'SFF only' frame filtering */
	अगर ((*mask & CAN_EFF_FLAG) && !(*can_id & CAN_EFF_FLAG))
		*mask &= (CAN_SFF_MASK | CAN_EFF_RTR_FLAGS);

	/* reduce condition testing at receive समय */
	*can_id &= *mask;

	/* inverse can_id/can_mask filter */
	अगर (inv)
		वापस &dev_rcv_lists->rx[RX_INV];

	/* mask == 0 => no condition testing at receive समय */
	अगर (!(*mask))
		वापस &dev_rcv_lists->rx[RX_ALL];

	/* extra filterlists क्रम the subscription of a single non-RTR can_id */
	अगर (((*mask & CAN_EFF_RTR_FLAGS) == CAN_EFF_RTR_FLAGS) &&
	    !(*can_id & CAN_RTR_FLAG)) अणु
		अगर (*can_id & CAN_EFF_FLAG) अणु
			अगर (*mask == (CAN_EFF_MASK | CAN_EFF_RTR_FLAGS))
				वापस &dev_rcv_lists->rx_eff[effhash(*can_id)];
		पूर्ण अन्यथा अणु
			अगर (*mask == (CAN_SFF_MASK | CAN_EFF_RTR_FLAGS))
				वापस &dev_rcv_lists->rx_sff[*can_id];
		पूर्ण
	पूर्ण

	/* शेष: filter via can_id/can_mask */
	वापस &dev_rcv_lists->rx[RX_FIL];
पूर्ण

/**
 * can_rx_रेजिस्टर - subscribe CAN frames from a specअगरic पूर्णांकerface
 * @net: the applicable net namespace
 * @dev: poपूर्णांकer to netdevice (शून्य => subscribe from 'all' CAN devices list)
 * @can_id: CAN identअगरier (see description)
 * @mask: CAN mask (see description)
 * @func: callback function on filter match
 * @data: वापसed parameter क्रम callback function
 * @ident: string क्रम calling module identअगरication
 * @sk: socket poपूर्णांकer (might be शून्य)
 *
 * Description:
 *  Invokes the callback function with the received sk_buff and the given
 *  parameter 'data' on a matching receive filter. A filter matches, when
 *
 *          <received_can_id> & mask == can_id & mask
 *
 *  The filter can be inverted (CAN_INV_FILTER bit set in can_id) or it can
 *  filter क्रम error message frames (CAN_ERR_FLAG bit set in mask).
 *
 *  The provided poपूर्णांकer to the sk_buff is guaranteed to be valid as दीर्घ as
 *  the callback function is running. The callback function must *not* मुक्त
 *  the given sk_buff जबतक processing it's task. When the given sk_buff is
 *  needed after the end of the callback function it must be cloned inside
 *  the callback function with skb_clone().
 *
 * Return:
 *  0 on success
 *  -ENOMEM on missing cache mem to create subscription entry
 *  -ENODEV unknown device
 */
पूर्णांक can_rx_रेजिस्टर(काष्ठा net *net, काष्ठा net_device *dev, canid_t can_id,
		    canid_t mask, व्योम (*func)(काष्ठा sk_buff *, व्योम *),
		    व्योम *data, अक्षर *ident, काष्ठा sock *sk)
अणु
	काष्ठा receiver *rcv;
	काष्ठा hlist_head *rcv_list;
	काष्ठा can_dev_rcv_lists *dev_rcv_lists;
	काष्ठा can_rcv_lists_stats *rcv_lists_stats = net->can.rcv_lists_stats;
	पूर्णांक err = 0;

	/* insert new receiver  (dev,canid,mask) -> (func,data) */

	अगर (dev && dev->type != ARPHRD_CAN)
		वापस -ENODEV;

	अगर (dev && !net_eq(net, dev_net(dev)))
		वापस -ENODEV;

	rcv = kmem_cache_alloc(rcv_cache, GFP_KERNEL);
	अगर (!rcv)
		वापस -ENOMEM;

	spin_lock_bh(&net->can.rcvlists_lock);

	dev_rcv_lists = can_dev_rcv_lists_find(net, dev);
	rcv_list = can_rcv_list_find(&can_id, &mask, dev_rcv_lists);

	rcv->can_id = can_id;
	rcv->mask = mask;
	rcv->matches = 0;
	rcv->func = func;
	rcv->data = data;
	rcv->ident = ident;
	rcv->sk = sk;

	hlist_add_head_rcu(&rcv->list, rcv_list);
	dev_rcv_lists->entries++;

	rcv_lists_stats->rcv_entries++;
	rcv_lists_stats->rcv_entries_max = max(rcv_lists_stats->rcv_entries_max,
					       rcv_lists_stats->rcv_entries);
	spin_unlock_bh(&net->can.rcvlists_lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL(can_rx_रेजिस्टर);

/* can_rx_delete_receiver - rcu callback क्रम single receiver entry removal */
अटल व्योम can_rx_delete_receiver(काष्ठा rcu_head *rp)
अणु
	काष्ठा receiver *rcv = container_of(rp, काष्ठा receiver, rcu);
	काष्ठा sock *sk = rcv->sk;

	kmem_cache_मुक्त(rcv_cache, rcv);
	अगर (sk)
		sock_put(sk);
पूर्ण

/**
 * can_rx_unरेजिस्टर - unsubscribe CAN frames from a specअगरic पूर्णांकerface
 * @net: the applicable net namespace
 * @dev: poपूर्णांकer to netdevice (शून्य => unsubscribe from 'all' CAN devices list)
 * @can_id: CAN identअगरier
 * @mask: CAN mask
 * @func: callback function on filter match
 * @data: वापसed parameter क्रम callback function
 *
 * Description:
 *  Removes subscription entry depending on given (subscription) values.
 */
व्योम can_rx_unरेजिस्टर(काष्ठा net *net, काष्ठा net_device *dev, canid_t can_id,
		       canid_t mask, व्योम (*func)(काष्ठा sk_buff *, व्योम *),
		       व्योम *data)
अणु
	काष्ठा receiver *rcv = शून्य;
	काष्ठा hlist_head *rcv_list;
	काष्ठा can_rcv_lists_stats *rcv_lists_stats = net->can.rcv_lists_stats;
	काष्ठा can_dev_rcv_lists *dev_rcv_lists;

	अगर (dev && dev->type != ARPHRD_CAN)
		वापस;

	अगर (dev && !net_eq(net, dev_net(dev)))
		वापस;

	spin_lock_bh(&net->can.rcvlists_lock);

	dev_rcv_lists = can_dev_rcv_lists_find(net, dev);
	rcv_list = can_rcv_list_find(&can_id, &mask, dev_rcv_lists);

	/* Search the receiver list क्रम the item to delete.  This should
	 * exist, since no receiver may be unरेजिस्टरed that hasn't
	 * been रेजिस्टरed beक्रमe.
	 */
	hlist_क्रम_each_entry_rcu(rcv, rcv_list, list) अणु
		अगर (rcv->can_id == can_id && rcv->mask == mask &&
		    rcv->func == func && rcv->data == data)
			अवरोध;
	पूर्ण

	/* Check क्रम bugs in CAN protocol implementations using af_can.c:
	 * 'rcv' will be शून्य अगर no matching list item was found क्रम removal.
	 * As this हाल may potentially happen when closing a socket जबतक
	 * the notअगरier क्रम removing the CAN netdev is running we just prपूर्णांक
	 * a warning here.
	 */
	अगर (!rcv) अणु
		pr_warn("can: receive list entry not found for dev %s, id %03X, mask %03X\n",
			DNAME(dev), can_id, mask);
		जाओ out;
	पूर्ण

	hlist_del_rcu(&rcv->list);
	dev_rcv_lists->entries--;

	अगर (rcv_lists_stats->rcv_entries > 0)
		rcv_lists_stats->rcv_entries--;

 out:
	spin_unlock_bh(&net->can.rcvlists_lock);

	/* schedule the receiver item क्रम deletion */
	अगर (rcv) अणु
		अगर (rcv->sk)
			sock_hold(rcv->sk);
		call_rcu(&rcv->rcu, can_rx_delete_receiver);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(can_rx_unरेजिस्टर);

अटल अंतरभूत व्योम deliver(काष्ठा sk_buff *skb, काष्ठा receiver *rcv)
अणु
	rcv->func(skb, rcv->data);
	rcv->matches++;
पूर्ण

अटल पूर्णांक can_rcv_filter(काष्ठा can_dev_rcv_lists *dev_rcv_lists, काष्ठा sk_buff *skb)
अणु
	काष्ठा receiver *rcv;
	पूर्णांक matches = 0;
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;
	canid_t can_id = cf->can_id;

	अगर (dev_rcv_lists->entries == 0)
		वापस 0;

	अगर (can_id & CAN_ERR_FLAG) अणु
		/* check क्रम error message frame entries only */
		hlist_क्रम_each_entry_rcu(rcv, &dev_rcv_lists->rx[RX_ERR], list) अणु
			अगर (can_id & rcv->mask) अणु
				deliver(skb, rcv);
				matches++;
			पूर्ण
		पूर्ण
		वापस matches;
	पूर्ण

	/* check क्रम unfiltered entries */
	hlist_क्रम_each_entry_rcu(rcv, &dev_rcv_lists->rx[RX_ALL], list) अणु
		deliver(skb, rcv);
		matches++;
	पूर्ण

	/* check क्रम can_id/mask entries */
	hlist_क्रम_each_entry_rcu(rcv, &dev_rcv_lists->rx[RX_FIL], list) अणु
		अगर ((can_id & rcv->mask) == rcv->can_id) अणु
			deliver(skb, rcv);
			matches++;
		पूर्ण
	पूर्ण

	/* check क्रम inverted can_id/mask entries */
	hlist_क्रम_each_entry_rcu(rcv, &dev_rcv_lists->rx[RX_INV], list) अणु
		अगर ((can_id & rcv->mask) != rcv->can_id) अणु
			deliver(skb, rcv);
			matches++;
		पूर्ण
	पूर्ण

	/* check filterlists क्रम single non-RTR can_ids */
	अगर (can_id & CAN_RTR_FLAG)
		वापस matches;

	अगर (can_id & CAN_EFF_FLAG) अणु
		hlist_क्रम_each_entry_rcu(rcv, &dev_rcv_lists->rx_eff[effhash(can_id)], list) अणु
			अगर (rcv->can_id == can_id) अणु
				deliver(skb, rcv);
				matches++;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		can_id &= CAN_SFF_MASK;
		hlist_क्रम_each_entry_rcu(rcv, &dev_rcv_lists->rx_sff[can_id], list) अणु
			deliver(skb, rcv);
			matches++;
		पूर्ण
	पूर्ण

	वापस matches;
पूर्ण

अटल व्योम can_receive(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा can_dev_rcv_lists *dev_rcv_lists;
	काष्ठा net *net = dev_net(dev);
	काष्ठा can_pkg_stats *pkg_stats = net->can.pkg_stats;
	पूर्णांक matches;

	/* update statistics */
	pkg_stats->rx_frames++;
	pkg_stats->rx_frames_delta++;

	/* create non-zero unique skb identअगरier together with *skb */
	जबतक (!(can_skb_prv(skb)->skbcnt))
		can_skb_prv(skb)->skbcnt = atomic_inc_वापस(&skbcounter);

	rcu_पढ़ो_lock();

	/* deliver the packet to sockets listening on all devices */
	matches = can_rcv_filter(net->can.rx_alldev_list, skb);

	/* find receive list क्रम this device */
	dev_rcv_lists = can_dev_rcv_lists_find(net, dev);
	matches += can_rcv_filter(dev_rcv_lists, skb);

	rcu_पढ़ो_unlock();

	/* consume the skbuff allocated by the netdevice driver */
	consume_skb(skb);

	अगर (matches > 0) अणु
		pkg_stats->matches++;
		pkg_stats->matches_delta++;
	पूर्ण
पूर्ण

अटल पूर्णांक can_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		   काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	काष्ठा canfd_frame *cfd = (काष्ठा canfd_frame *)skb->data;

	अगर (unlikely(dev->type != ARPHRD_CAN || skb->len != CAN_MTU)) अणु
		pr_warn_once("PF_CAN: dropped non conform CAN skbuff: dev type %d, len %d\n",
			     dev->type, skb->len);
		जाओ मुक्त_skb;
	पूर्ण

	/* This check is made separately since cfd->len would be uninitialized अगर skb->len = 0. */
	अगर (unlikely(cfd->len > CAN_MAX_DLEN)) अणु
		pr_warn_once("PF_CAN: dropped non conform CAN skbuff: dev type %d, len %d, datalen %d\n",
			     dev->type, skb->len, cfd->len);
		जाओ मुक्त_skb;
	पूर्ण

	can_receive(skb, dev);
	वापस NET_RX_SUCCESS;

मुक्त_skb:
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण

अटल पूर्णांक canfd_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		     काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	काष्ठा canfd_frame *cfd = (काष्ठा canfd_frame *)skb->data;

	अगर (unlikely(dev->type != ARPHRD_CAN || skb->len != CANFD_MTU)) अणु
		pr_warn_once("PF_CAN: dropped non conform CAN FD skbuff: dev type %d, len %d\n",
			     dev->type, skb->len);
		जाओ मुक्त_skb;
	पूर्ण

	/* This check is made separately since cfd->len would be uninitialized अगर skb->len = 0. */
	अगर (unlikely(cfd->len > CANFD_MAX_DLEN)) अणु
		pr_warn_once("PF_CAN: dropped non conform CAN FD skbuff: dev type %d, len %d, datalen %d\n",
			     dev->type, skb->len, cfd->len);
		जाओ मुक्त_skb;
	पूर्ण

	can_receive(skb, dev);
	वापस NET_RX_SUCCESS;

मुक्त_skb:
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण

/* af_can protocol functions */

/**
 * can_proto_रेजिस्टर - रेजिस्टर CAN transport protocol
 * @cp: poपूर्णांकer to CAN protocol काष्ठाure
 *
 * Return:
 *  0 on success
 *  -EINVAL invalid (out of range) protocol number
 *  -EBUSY  protocol alपढ़ोy in use
 *  -ENOBUF अगर proto_रेजिस्टर() fails
 */
पूर्णांक can_proto_रेजिस्टर(स्थिर काष्ठा can_proto *cp)
अणु
	पूर्णांक proto = cp->protocol;
	पूर्णांक err = 0;

	अगर (proto < 0 || proto >= CAN_NPROTO) अणु
		pr_err("can: protocol number %d out of range\n", proto);
		वापस -EINVAL;
	पूर्ण

	err = proto_रेजिस्टर(cp->prot, 0);
	अगर (err < 0)
		वापस err;

	mutex_lock(&proto_tab_lock);

	अगर (rcu_access_poपूर्णांकer(proto_tab[proto])) अणु
		pr_err("can: protocol %d already registered\n", proto);
		err = -EBUSY;
	पूर्ण अन्यथा अणु
		RCU_INIT_POINTER(proto_tab[proto], cp);
	पूर्ण

	mutex_unlock(&proto_tab_lock);

	अगर (err < 0)
		proto_unरेजिस्टर(cp->prot);

	वापस err;
पूर्ण
EXPORT_SYMBOL(can_proto_रेजिस्टर);

/**
 * can_proto_unरेजिस्टर - unरेजिस्टर CAN transport protocol
 * @cp: poपूर्णांकer to CAN protocol काष्ठाure
 */
व्योम can_proto_unरेजिस्टर(स्थिर काष्ठा can_proto *cp)
अणु
	पूर्णांक proto = cp->protocol;

	mutex_lock(&proto_tab_lock);
	BUG_ON(rcu_access_poपूर्णांकer(proto_tab[proto]) != cp);
	RCU_INIT_POINTER(proto_tab[proto], शून्य);
	mutex_unlock(&proto_tab_lock);

	synchronize_rcu();

	proto_unरेजिस्टर(cp->prot);
पूर्ण
EXPORT_SYMBOL(can_proto_unरेजिस्टर);

अटल पूर्णांक can_pernet_init(काष्ठा net *net)
अणु
	spin_lock_init(&net->can.rcvlists_lock);
	net->can.rx_alldev_list =
		kzalloc(माप(*net->can.rx_alldev_list), GFP_KERNEL);
	अगर (!net->can.rx_alldev_list)
		जाओ out;
	net->can.pkg_stats = kzalloc(माप(*net->can.pkg_stats), GFP_KERNEL);
	अगर (!net->can.pkg_stats)
		जाओ out_मुक्त_rx_alldev_list;
	net->can.rcv_lists_stats = kzalloc(माप(*net->can.rcv_lists_stats), GFP_KERNEL);
	अगर (!net->can.rcv_lists_stats)
		जाओ out_मुक्त_pkg_stats;

	अगर (IS_ENABLED(CONFIG_PROC_FS)) अणु
		/* the statistics are updated every second (समयr triggered) */
		अगर (stats_समयr) अणु
			समयr_setup(&net->can.statसमयr, can_stat_update,
				    0);
			mod_समयr(&net->can.statसमयr,
				  round_jअगरfies(jअगरfies + HZ));
		पूर्ण
		net->can.pkg_stats->jअगरfies_init = jअगरfies;
		can_init_proc(net);
	पूर्ण

	वापस 0;

 out_मुक्त_pkg_stats:
	kमुक्त(net->can.pkg_stats);
 out_मुक्त_rx_alldev_list:
	kमुक्त(net->can.rx_alldev_list);
 out:
	वापस -ENOMEM;
पूर्ण

अटल व्योम can_pernet_निकास(काष्ठा net *net)
अणु
	अगर (IS_ENABLED(CONFIG_PROC_FS)) अणु
		can_हटाओ_proc(net);
		अगर (stats_समयr)
			del_समयr_sync(&net->can.statसमयr);
	पूर्ण

	kमुक्त(net->can.rx_alldev_list);
	kमुक्त(net->can.pkg_stats);
	kमुक्त(net->can.rcv_lists_stats);
पूर्ण

/* af_can module init/निकास functions */

अटल काष्ठा packet_type can_packet __पढ़ो_mostly = अणु
	.type = cpu_to_be16(ETH_P_CAN),
	.func = can_rcv,
पूर्ण;

अटल काष्ठा packet_type canfd_packet __पढ़ो_mostly = अणु
	.type = cpu_to_be16(ETH_P_CANFD),
	.func = canfd_rcv,
पूर्ण;

अटल स्थिर काष्ठा net_proto_family can_family_ops = अणु
	.family = PF_CAN,
	.create = can_create,
	.owner  = THIS_MODULE,
पूर्ण;

अटल काष्ठा pernet_operations can_pernet_ops __पढ़ो_mostly = अणु
	.init = can_pernet_init,
	.निकास = can_pernet_निकास,
पूर्ण;

अटल __init पूर्णांक can_init(व्योम)
अणु
	पूर्णांक err;

	/* check क्रम correct padding to be able to use the काष्ठाs similarly */
	BUILD_BUG_ON(दुरत्व(काष्ठा can_frame, len) !=
		     दुरत्व(काष्ठा canfd_frame, len) ||
		     दुरत्व(काष्ठा can_frame, data) !=
		     दुरत्व(काष्ठा canfd_frame, data));

	pr_info("can: controller area network core\n");

	rcv_cache = kmem_cache_create("can_receiver", माप(काष्ठा receiver),
				      0, 0, शून्य);
	अगर (!rcv_cache)
		वापस -ENOMEM;

	err = रेजिस्टर_pernet_subsys(&can_pernet_ops);
	अगर (err)
		जाओ out_pernet;

	/* protocol रेजिस्टर */
	err = sock_रेजिस्टर(&can_family_ops);
	अगर (err)
		जाओ out_sock;

	dev_add_pack(&can_packet);
	dev_add_pack(&canfd_packet);

	वापस 0;

out_sock:
	unरेजिस्टर_pernet_subsys(&can_pernet_ops);
out_pernet:
	kmem_cache_destroy(rcv_cache);

	वापस err;
पूर्ण

अटल __निकास व्योम can_निकास(व्योम)
अणु
	/* protocol unरेजिस्टर */
	dev_हटाओ_pack(&canfd_packet);
	dev_हटाओ_pack(&can_packet);
	sock_unरेजिस्टर(PF_CAN);

	unरेजिस्टर_pernet_subsys(&can_pernet_ops);

	rcu_barrier(); /* Wait क्रम completion of call_rcu()'s */

	kmem_cache_destroy(rcv_cache);
पूर्ण

module_init(can_init);
module_निकास(can_निकास);
