<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AF_RXRPC local endpoपूर्णांक management
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#समावेश <generated/utsrelease.h>
#समावेश "ar-internal.h"

अटल स्थिर अक्षर rxrpc_version_string[65] = "linux-" UTS_RELEASE " AF_RXRPC";

/*
 * Reply to a version request
 */
अटल व्योम rxrpc_send_version_request(काष्ठा rxrpc_local *local,
				       काष्ठा rxrpc_host_header *hdr,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा rxrpc_wire_header whdr;
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	काष्ठा sockaddr_rxrpc srx;
	काष्ठा msghdr msg;
	काष्ठा kvec iov[2];
	माप_प्रकार len;
	पूर्णांक ret;

	_enter("");

	अगर (rxrpc_extract_addr_from_skb(&srx, skb) < 0)
		वापस;

	msg.msg_name	= &srx.transport;
	msg.msg_namelen	= srx.transport_len;
	msg.msg_control	= शून्य;
	msg.msg_controllen = 0;
	msg.msg_flags	= 0;

	whdr.epoch	= htonl(sp->hdr.epoch);
	whdr.cid	= htonl(sp->hdr.cid);
	whdr.callNumber	= htonl(sp->hdr.callNumber);
	whdr.seq	= 0;
	whdr.serial	= 0;
	whdr.type	= RXRPC_PACKET_TYPE_VERSION;
	whdr.flags	= RXRPC_LAST_PACKET | (~hdr->flags & RXRPC_CLIENT_INITIATED);
	whdr.userStatus	= 0;
	whdr.securityIndex = 0;
	whdr._rsvd	= 0;
	whdr.serviceId	= htons(sp->hdr.serviceId);

	iov[0].iov_base	= &whdr;
	iov[0].iov_len	= माप(whdr);
	iov[1].iov_base	= (अक्षर *)rxrpc_version_string;
	iov[1].iov_len	= माप(rxrpc_version_string);

	len = iov[0].iov_len + iov[1].iov_len;

	_proto("Tx VERSION (reply)");

	ret = kernel_sendmsg(local->socket, &msg, iov, 2, len);
	अगर (ret < 0)
		trace_rxrpc_tx_fail(local->debug_id, 0, ret,
				    rxrpc_tx_poपूर्णांक_version_reply);
	अन्यथा
		trace_rxrpc_tx_packet(local->debug_id, &whdr,
				      rxrpc_tx_poपूर्णांक_version_reply);

	_leave("");
पूर्ण

/*
 * Process event packets targetted at a local endpoपूर्णांक.
 */
व्योम rxrpc_process_local_events(काष्ठा rxrpc_local *local)
अणु
	काष्ठा sk_buff *skb;
	अक्षर v;

	_enter("");

	skb = skb_dequeue(&local->event_queue);
	अगर (skb) अणु
		काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);

		rxrpc_see_skb(skb, rxrpc_skb_seen);
		_debug("{%d},{%u}", local->debug_id, sp->hdr.type);

		चयन (sp->hdr.type) अणु
		हाल RXRPC_PACKET_TYPE_VERSION:
			अगर (skb_copy_bits(skb, माप(काष्ठा rxrpc_wire_header),
					  &v, 1) < 0)
				वापस;
			_proto("Rx VERSION { %02x }", v);
			अगर (v == 0)
				rxrpc_send_version_request(local, &sp->hdr, skb);
			अवरोध;

		शेष:
			/* Just ignore anything we करोn't understand */
			अवरोध;
		पूर्ण

		rxrpc_मुक्त_skb(skb, rxrpc_skb_मुक्तd);
	पूर्ण

	_leave("");
पूर्ण
