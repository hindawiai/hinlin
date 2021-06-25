<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* ar-skbuff.c: socket buffer deकाष्ठाion handling
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#समावेश "ar-internal.h"

#घोषणा is_tx_skb(skb) (rxrpc_skb(skb)->rx_flags & RXRPC_SKB_TX_BUFFER)
#घोषणा select_skb_count(skb) (is_tx_skb(skb) ? &rxrpc_n_tx_skbs : &rxrpc_n_rx_skbs)

/*
 * Note the allocation or reception of a socket buffer.
 */
व्योम rxrpc_new_skb(काष्ठा sk_buff *skb, क्रमागत rxrpc_skb_trace op)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	पूर्णांक n = atomic_inc_वापस(select_skb_count(skb));
	trace_rxrpc_skb(skb, op, refcount_पढ़ो(&skb->users), n,
			rxrpc_skb(skb)->rx_flags, here);
पूर्ण

/*
 * Note the re-emergence of a socket buffer from a queue or buffer.
 */
व्योम rxrpc_see_skb(काष्ठा sk_buff *skb, क्रमागत rxrpc_skb_trace op)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	अगर (skb) अणु
		पूर्णांक n = atomic_पढ़ो(select_skb_count(skb));
		trace_rxrpc_skb(skb, op, refcount_पढ़ो(&skb->users), n,
				rxrpc_skb(skb)->rx_flags, here);
	पूर्ण
पूर्ण

/*
 * Note the addition of a ref on a socket buffer.
 */
व्योम rxrpc_get_skb(काष्ठा sk_buff *skb, क्रमागत rxrpc_skb_trace op)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	पूर्णांक n = atomic_inc_वापस(select_skb_count(skb));
	trace_rxrpc_skb(skb, op, refcount_पढ़ो(&skb->users), n,
			rxrpc_skb(skb)->rx_flags, here);
	skb_get(skb);
पूर्ण

/*
 * Note the dropping of a ref on a socket buffer by the core.
 */
व्योम rxrpc_eaten_skb(काष्ठा sk_buff *skb, क्रमागत rxrpc_skb_trace op)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	पूर्णांक n = atomic_inc_वापस(&rxrpc_n_rx_skbs);
	trace_rxrpc_skb(skb, op, 0, n, 0, here);
पूर्ण

/*
 * Note the deकाष्ठाion of a socket buffer.
 */
व्योम rxrpc_मुक्त_skb(काष्ठा sk_buff *skb, क्रमागत rxrpc_skb_trace op)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	अगर (skb) अणु
		पूर्णांक n;
		CHECK_SLAB_OKAY(&skb->users);
		n = atomic_dec_वापस(select_skb_count(skb));
		trace_rxrpc_skb(skb, op, refcount_पढ़ो(&skb->users), n,
				rxrpc_skb(skb)->rx_flags, here);
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण

/*
 * Clear a queue of socket buffers.
 */
व्योम rxrpc_purge_queue(काष्ठा sk_buff_head *list)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	काष्ठा sk_buff *skb;
	जबतक ((skb = skb_dequeue((list))) != शून्य) अणु
		पूर्णांक n = atomic_dec_वापस(select_skb_count(skb));
		trace_rxrpc_skb(skb, rxrpc_skb_purged,
				refcount_पढ़ो(&skb->users), n,
				rxrpc_skb(skb)->rx_flags, here);
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण
