<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Utility routines
 *
 * Copyright (C) 2015 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/udp.h>
#समावेश "ar-internal.h"

/*
 * Fill out a peer address from a socket buffer containing a packet.
 */
पूर्णांक rxrpc_extract_addr_from_skb(काष्ठा sockaddr_rxrpc *srx, काष्ठा sk_buff *skb)
अणु
	स_रखो(srx, 0, माप(*srx));

	चयन (ntohs(skb->protocol)) अणु
	हाल ETH_P_IP:
		srx->transport_type = SOCK_DGRAM;
		srx->transport_len = माप(srx->transport.sin);
		srx->transport.sin.sin_family = AF_INET;
		srx->transport.sin.sin_port = udp_hdr(skb)->source;
		srx->transport.sin.sin_addr.s_addr = ip_hdr(skb)->saddr;
		वापस 0;

#अगर_घोषित CONFIG_AF_RXRPC_IPV6
	हाल ETH_P_IPV6:
		srx->transport_type = SOCK_DGRAM;
		srx->transport_len = माप(srx->transport.sin6);
		srx->transport.sin6.sin6_family = AF_INET6;
		srx->transport.sin6.sin6_port = udp_hdr(skb)->source;
		srx->transport.sin6.sin6_addr = ipv6_hdr(skb)->saddr;
		वापस 0;
#पूर्ण_अगर

	शेष:
		pr_warn_ratelimited("AF_RXRPC: Unknown eth protocol %u\n",
				    ntohs(skb->protocol));
		वापस -EAFNOSUPPORT;
	पूर्ण
पूर्ण
