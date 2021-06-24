<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001-2003 International Business Machines, Corp.
 * Copyright (c) 2001 Intel Corp.
 * Copyright (c) 2001 Nokia, Inc.
 * Copyright (c) 2001 La Monte H.P. Yarroll
 *
 * This file is part of the SCTP kernel implementation
 *
 * These functions handle all input from the IP layer पूर्णांकo SCTP.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Karl Knutson <karl@athena.chicago.il.us>
 *    Xingang Guo <xingang.guo@पूर्णांकel.com>
 *    Jon Grimm <jgrimm@us.ibm.com>
 *    Hui Huang <hui.huang@nokia.com>
 *    Daisy Chang <daisyc@us.ibm.com>
 *    Sridhar Samudrala <sri@us.ibm.com>
 *    Ardelle Fan <ardelle.fan@पूर्णांकel.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/list.h> /* For काष्ठा list_head */
#समावेश <linux/socket.h>
#समावेश <linux/ip.h>
#समावेश <linux/समय.स> /* For काष्ठा समयval */
#समावेश <linux/slab.h>
#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/snmp.h>
#समावेश <net/sock.h>
#समावेश <net/xfrm.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/sm.h>
#समावेश <net/sctp/checksum.h>
#समावेश <net/net_namespace.h>
#समावेश <linux/rhashtable.h>
#समावेश <net/sock_reuseport.h>

/* Forward declarations क्रम पूर्णांकernal helpers. */
अटल पूर्णांक sctp_rcv_ootb(काष्ठा sk_buff *);
अटल काष्ठा sctp_association *__sctp_rcv_lookup(काष्ठा net *net,
				      काष्ठा sk_buff *skb,
				      स्थिर जोड़ sctp_addr *paddr,
				      स्थिर जोड़ sctp_addr *laddr,
				      काष्ठा sctp_transport **transportp);
अटल काष्ठा sctp_endpoपूर्णांक *__sctp_rcv_lookup_endpoपूर्णांक(
					काष्ठा net *net, काष्ठा sk_buff *skb,
					स्थिर जोड़ sctp_addr *laddr,
					स्थिर जोड़ sctp_addr *daddr);
अटल काष्ठा sctp_association *__sctp_lookup_association(
					काष्ठा net *net,
					स्थिर जोड़ sctp_addr *local,
					स्थिर जोड़ sctp_addr *peer,
					काष्ठा sctp_transport **pt);

अटल पूर्णांक sctp_add_backlog(काष्ठा sock *sk, काष्ठा sk_buff *skb);


/* Calculate the SCTP checksum of an SCTP packet.  */
अटल अंतरभूत पूर्णांक sctp_rcv_checksum(काष्ठा net *net, काष्ठा sk_buff *skb)
अणु
	काष्ठा sctphdr *sh = sctp_hdr(skb);
	__le32 cmp = sh->checksum;
	__le32 val = sctp_compute_cksum(skb, 0);

	अगर (val != cmp) अणु
		/* CRC failure, dump it. */
		__SCTP_INC_STATS(net, SCTP_MIB_CHECKSUMERRORS);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This is the routine which IP calls when receiving an SCTP packet.
 */
पूर्णांक sctp_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk;
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_endpoपूर्णांक *ep = शून्य;
	काष्ठा sctp_ep_common *rcvr;
	काष्ठा sctp_transport *transport = शून्य;
	काष्ठा sctp_chunk *chunk;
	जोड़ sctp_addr src;
	जोड़ sctp_addr dest;
	पूर्णांक family;
	काष्ठा sctp_af *af;
	काष्ठा net *net = dev_net(skb->dev);
	bool is_gso = skb_is_gso(skb) && skb_is_gso_sctp(skb);

	अगर (skb->pkt_type != PACKET_HOST)
		जाओ discard_it;

	__SCTP_INC_STATS(net, SCTP_MIB_INSCTPPACKS);

	/* If packet is too small to contain a single chunk, let's not
	 * waste समय on it anymore.
	 */
	अगर (skb->len < माप(काष्ठा sctphdr) + माप(काष्ठा sctp_chunkhdr) +
		       skb_transport_offset(skb))
		जाओ discard_it;

	/* If the packet is fragmented and we need to करो crc checking,
	 * it's better to just linearize it otherwise crc computing
	 * takes दीर्घer.
	 */
	अगर ((!is_gso && skb_linearize(skb)) ||
	    !pskb_may_pull(skb, माप(काष्ठा sctphdr)))
		जाओ discard_it;

	/* Pull up the IP header. */
	__skb_pull(skb, skb_transport_offset(skb));

	skb->csum_valid = 0; /* Previous value not applicable */
	अगर (skb_csum_unnecessary(skb))
		__skb_decr_checksum_unnecessary(skb);
	अन्यथा अगर (!sctp_checksum_disable &&
		 !is_gso &&
		 sctp_rcv_checksum(net, skb) < 0)
		जाओ discard_it;
	skb->csum_valid = 1;

	__skb_pull(skb, माप(काष्ठा sctphdr));

	family = ipver2af(ip_hdr(skb)->version);
	af = sctp_get_af_specअगरic(family);
	अगर (unlikely(!af))
		जाओ discard_it;
	SCTP_INPUT_CB(skb)->af = af;

	/* Initialize local addresses क्रम lookups. */
	af->from_skb(&src, skb, 1);
	af->from_skb(&dest, skb, 0);

	/* If the packet is to or from a non-unicast address,
	 * silently discard the packet.
	 *
	 * This is not clearly defined in the RFC except in section
	 * 8.4 - OOTB handling.  However, based on the book "Stream Control
	 * Transmission Protocol" 2.1, "It is important to note that the
	 * IP address of an SCTP transport address must be a routable
	 * unicast address.  In other words, IP multicast addresses and
	 * IP broadcast addresses cannot be used in an SCTP transport
	 * address."
	 */
	अगर (!af->addr_valid(&src, शून्य, skb) ||
	    !af->addr_valid(&dest, शून्य, skb))
		जाओ discard_it;

	asoc = __sctp_rcv_lookup(net, skb, &src, &dest, &transport);

	अगर (!asoc)
		ep = __sctp_rcv_lookup_endpoपूर्णांक(net, skb, &dest, &src);

	/* Retrieve the common input handling subकाष्ठाure. */
	rcvr = asoc ? &asoc->base : &ep->base;
	sk = rcvr->sk;

	/*
	 * If a frame arrives on an पूर्णांकerface and the receiving socket is
	 * bound to another पूर्णांकerface, via SO_BINDTODEVICE, treat it as OOTB
	 */
	अगर (sk->sk_bound_dev_अगर && (sk->sk_bound_dev_अगर != af->skb_iअगर(skb))) अणु
		अगर (transport) अणु
			sctp_transport_put(transport);
			asoc = शून्य;
			transport = शून्य;
		पूर्ण अन्यथा अणु
			sctp_endpoपूर्णांक_put(ep);
			ep = शून्य;
		पूर्ण
		sk = net->sctp.ctl_sock;
		ep = sctp_sk(sk)->ep;
		sctp_endpoपूर्णांक_hold(ep);
		rcvr = &ep->base;
	पूर्ण

	/*
	 * RFC 2960, 8.4 - Handle "Out of the blue" Packets.
	 * An SCTP packet is called an "out of the blue" (OOTB)
	 * packet अगर it is correctly क्रमmed, i.e., passed the
	 * receiver's checksum check, but the receiver is not
	 * able to identअगरy the association to which this
	 * packet beदीर्घs.
	 */
	अगर (!asoc) अणु
		अगर (sctp_rcv_ootb(skb)) अणु
			__SCTP_INC_STATS(net, SCTP_MIB_OUTOFBLUES);
			जाओ discard_release;
		पूर्ण
	पूर्ण

	अगर (!xfrm_policy_check(sk, XFRM_POLICY_IN, skb, family))
		जाओ discard_release;
	nf_reset_ct(skb);

	अगर (sk_filter(sk, skb))
		जाओ discard_release;

	/* Create an SCTP packet काष्ठाure. */
	chunk = sctp_chunkअगरy(skb, asoc, sk, GFP_ATOMIC);
	अगर (!chunk)
		जाओ discard_release;
	SCTP_INPUT_CB(skb)->chunk = chunk;

	/* Remember what endpoपूर्णांक is to handle this packet. */
	chunk->rcvr = rcvr;

	/* Remember the SCTP header. */
	chunk->sctp_hdr = sctp_hdr(skb);

	/* Set the source and destination addresses of the incoming chunk.  */
	sctp_init_addrs(chunk, &src, &dest);

	/* Remember where we came from.  */
	chunk->transport = transport;

	/* Acquire access to the sock lock. Note: We are safe from other
	 * bottom halves on this lock, but a user may be in the lock too,
	 * so check अगर it is busy.
	 */
	bh_lock_sock(sk);

	अगर (sk != rcvr->sk) अणु
		/* Our cached sk is dअगरferent from the rcvr->sk.  This is
		 * because migrate()/accept() may have moved the association
		 * to a new socket and released all the sockets.  So now we
		 * are holding a lock on the old socket जबतक the user may
		 * be करोing something with the new socket.  Switch our veiw
		 * of the current sk.
		 */
		bh_unlock_sock(sk);
		sk = rcvr->sk;
		bh_lock_sock(sk);
	पूर्ण

	अगर (sock_owned_by_user(sk) || !sctp_newsk_पढ़ोy(sk)) अणु
		अगर (sctp_add_backlog(sk, skb)) अणु
			bh_unlock_sock(sk);
			sctp_chunk_मुक्त(chunk);
			skb = शून्य; /* sctp_chunk_मुक्त alपढ़ोy मुक्तd the skb */
			जाओ discard_release;
		पूर्ण
		__SCTP_INC_STATS(net, SCTP_MIB_IN_PKT_BACKLOG);
	पूर्ण अन्यथा अणु
		__SCTP_INC_STATS(net, SCTP_MIB_IN_PKT_SOFTIRQ);
		sctp_inq_push(&chunk->rcvr->inqueue, chunk);
	पूर्ण

	bh_unlock_sock(sk);

	/* Release the asoc/ep ref we took in the lookup calls. */
	अगर (transport)
		sctp_transport_put(transport);
	अन्यथा
		sctp_endpoपूर्णांक_put(ep);

	वापस 0;

discard_it:
	__SCTP_INC_STATS(net, SCTP_MIB_IN_PKT_DISCARDS);
	kमुक्त_skb(skb);
	वापस 0;

discard_release:
	/* Release the asoc/ep ref we took in the lookup calls. */
	अगर (transport)
		sctp_transport_put(transport);
	अन्यथा
		sctp_endpoपूर्णांक_put(ep);

	जाओ discard_it;
पूर्ण

/* Process the backlog queue of the socket.  Every skb on
 * the backlog holds a ref on an association or endpoपूर्णांक.
 * We hold this ref throughout the state machine to make
 * sure that the काष्ठाure we need is still around.
 */
पूर्णांक sctp_backlog_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा sctp_chunk *chunk = SCTP_INPUT_CB(skb)->chunk;
	काष्ठा sctp_inq *inqueue = &chunk->rcvr->inqueue;
	काष्ठा sctp_transport *t = chunk->transport;
	काष्ठा sctp_ep_common *rcvr = शून्य;
	पूर्णांक backloged = 0;

	rcvr = chunk->rcvr;

	/* If the rcvr is dead then the association or endpoपूर्णांक
	 * has been deleted and we can safely drop the chunk
	 * and refs that we are holding.
	 */
	अगर (rcvr->dead) अणु
		sctp_chunk_मुक्त(chunk);
		जाओ करोne;
	पूर्ण

	अगर (unlikely(rcvr->sk != sk)) अणु
		/* In this हाल, the association moved from one socket to
		 * another.  We are currently sitting on the backlog of the
		 * old socket, so we need to move.
		 * However, since we are here in the process context we
		 * need to take make sure that the user करोesn't own
		 * the new socket when we process the packet.
		 * If the new socket is user-owned, queue the chunk to the
		 * backlog of the new socket without dropping any refs.
		 * Otherwise, we can safely push the chunk on the inqueue.
		 */

		sk = rcvr->sk;
		local_bh_disable();
		bh_lock_sock(sk);

		अगर (sock_owned_by_user(sk) || !sctp_newsk_पढ़ोy(sk)) अणु
			अगर (sk_add_backlog(sk, skb, READ_ONCE(sk->sk_rcvbuf)))
				sctp_chunk_मुक्त(chunk);
			अन्यथा
				backloged = 1;
		पूर्ण अन्यथा
			sctp_inq_push(inqueue, chunk);

		bh_unlock_sock(sk);
		local_bh_enable();

		/* If the chunk was backloged again, करोn't drop refs */
		अगर (backloged)
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर (!sctp_newsk_पढ़ोy(sk)) अणु
			अगर (!sk_add_backlog(sk, skb, READ_ONCE(sk->sk_rcvbuf)))
				वापस 0;
			sctp_chunk_मुक्त(chunk);
		पूर्ण अन्यथा अणु
			sctp_inq_push(inqueue, chunk);
		पूर्ण
	पूर्ण

करोne:
	/* Release the refs we took in sctp_add_backlog */
	अगर (SCTP_EP_TYPE_ASSOCIATION == rcvr->type)
		sctp_transport_put(t);
	अन्यथा अगर (SCTP_EP_TYPE_SOCKET == rcvr->type)
		sctp_endpoपूर्णांक_put(sctp_ep(rcvr));
	अन्यथा
		BUG();

	वापस 0;
पूर्ण

अटल पूर्णांक sctp_add_backlog(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा sctp_chunk *chunk = SCTP_INPUT_CB(skb)->chunk;
	काष्ठा sctp_transport *t = chunk->transport;
	काष्ठा sctp_ep_common *rcvr = chunk->rcvr;
	पूर्णांक ret;

	ret = sk_add_backlog(sk, skb, READ_ONCE(sk->sk_rcvbuf));
	अगर (!ret) अणु
		/* Hold the assoc/ep जबतक hanging on the backlog queue.
		 * This way, we know काष्ठाures we need will not disappear
		 * from us
		 */
		अगर (SCTP_EP_TYPE_ASSOCIATION == rcvr->type)
			sctp_transport_hold(t);
		अन्यथा अगर (SCTP_EP_TYPE_SOCKET == rcvr->type)
			sctp_endpoपूर्णांक_hold(sctp_ep(rcvr));
		अन्यथा
			BUG();
	पूर्ण
	वापस ret;

पूर्ण

/* Handle icmp frag needed error. */
व्योम sctp_icmp_frag_needed(काष्ठा sock *sk, काष्ठा sctp_association *asoc,
			   काष्ठा sctp_transport *t, __u32 pmtu)
अणु
	अगर (!t || (t->pathmtu <= pmtu))
		वापस;

	अगर (sock_owned_by_user(sk)) अणु
		atomic_set(&t->mtu_info, pmtu);
		asoc->pmtu_pending = 1;
		t->pmtu_pending = 1;
		वापस;
	पूर्ण

	अगर (!(t->param_flags & SPP_PMTUD_ENABLE))
		/* We can't allow retransmitting in such हाल, as the
		 * retransmission would be sized just as beक्रमe, and thus we
		 * would get another icmp, and retransmit again.
		 */
		वापस;

	/* Update transports view of the MTU. Return अगर no update was needed.
	 * If an update wasn't needed/possible, it also doesn't make sense to
	 * try to retransmit now.
	 */
	अगर (!sctp_transport_update_pmtu(t, pmtu))
		वापस;

	/* Update association pmtu. */
	sctp_assoc_sync_pmtu(asoc);

	/* Retransmit with the new pmtu setting. */
	sctp_retransmit(&asoc->outqueue, t, SCTP_RTXR_PMTUD);
पूर्ण

व्योम sctp_icmp_redirect(काष्ठा sock *sk, काष्ठा sctp_transport *t,
			काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst;

	अगर (sock_owned_by_user(sk) || !t)
		वापस;
	dst = sctp_transport_dst_check(t);
	अगर (dst)
		dst->ops->redirect(dst, sk, skb);
पूर्ण

/*
 * SCTP Implementer's Guide, 2.37 ICMP handling procedures
 *
 * ICMP8) If the ICMP code is a "Unrecognized next header type encountered"
 *        or a "Protocol Unreachable" treat this message as an पात
 *        with the T bit set.
 *
 * This function sends an event to the state machine, which will पात the
 * association.
 *
 */
व्योम sctp_icmp_proto_unreachable(काष्ठा sock *sk,
			   काष्ठा sctp_association *asoc,
			   काष्ठा sctp_transport *t)
अणु
	अगर (sock_owned_by_user(sk)) अणु
		अगर (समयr_pending(&t->proto_unreach_समयr))
			वापस;
		अन्यथा अणु
			अगर (!mod_समयr(&t->proto_unreach_समयr,
						jअगरfies + (HZ/20)))
				sctp_transport_hold(t);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा net *net = sock_net(sk);

		pr_debug("%s: unrecognized next header type "
			 "encountered!\n", __func__);

		अगर (del_समयr(&t->proto_unreach_समयr))
			sctp_transport_put(t);

		sctp_करो_sm(net, SCTP_EVENT_T_OTHER,
			   SCTP_ST_OTHER(SCTP_EVENT_ICMP_PROTO_UNREACH),
			   asoc->state, asoc->ep, asoc, t,
			   GFP_ATOMIC);
	पूर्ण
पूर्ण

/* Common lookup code क्रम icmp/icmpv6 error handler. */
काष्ठा sock *sctp_err_lookup(काष्ठा net *net, पूर्णांक family, काष्ठा sk_buff *skb,
			     काष्ठा sctphdr *sctphdr,
			     काष्ठा sctp_association **app,
			     काष्ठा sctp_transport **tpp)
अणु
	काष्ठा sctp_init_chunk *chunkhdr, _chunkhdr;
	जोड़ sctp_addr saddr;
	जोड़ sctp_addr daddr;
	काष्ठा sctp_af *af;
	काष्ठा sock *sk = शून्य;
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_transport *transport = शून्य;
	__u32 vtag = ntohl(sctphdr->vtag);

	*app = शून्य; *tpp = शून्य;

	af = sctp_get_af_specअगरic(family);
	अगर (unlikely(!af)) अणु
		वापस शून्य;
	पूर्ण

	/* Initialize local addresses क्रम lookups. */
	af->from_skb(&saddr, skb, 1);
	af->from_skb(&daddr, skb, 0);

	/* Look क्रम an association that matches the incoming ICMP error
	 * packet.
	 */
	asoc = __sctp_lookup_association(net, &saddr, &daddr, &transport);
	अगर (!asoc)
		वापस शून्य;

	sk = asoc->base.sk;

	/* RFC 4960, Appendix C. ICMP Handling
	 *
	 * ICMP6) An implementation MUST validate that the Verअगरication Tag
	 * contained in the ICMP message matches the Verअगरication Tag of
	 * the peer.  If the Verअगरication Tag is not 0 and करोes NOT
	 * match, discard the ICMP message.  If it is 0 and the ICMP
	 * message contains enough bytes to verअगरy that the chunk type is
	 * an INIT chunk and that the Initiate Tag matches the tag of the
	 * peer, जारी with ICMP7.  If the ICMP message is too लघु
	 * or the chunk type or the Initiate Tag करोes not match, silently
	 * discard the packet.
	 */
	अगर (vtag == 0) अणु
		/* chunk header + first 4 octects of init header */
		chunkhdr = skb_header_poपूर्णांकer(skb, skb_transport_offset(skb) +
					      माप(काष्ठा sctphdr),
					      माप(काष्ठा sctp_chunkhdr) +
					      माप(__be32), &_chunkhdr);
		अगर (!chunkhdr ||
		    chunkhdr->chunk_hdr.type != SCTP_CID_INIT ||
		    ntohl(chunkhdr->init_hdr.init_tag) != asoc->c.my_vtag)
			जाओ out;

	पूर्ण अन्यथा अगर (vtag != asoc->c.peer_vtag) अणु
		जाओ out;
	पूर्ण

	bh_lock_sock(sk);

	/* If too many ICMPs get dropped on busy
	 * servers this needs to be solved dअगरferently.
	 */
	अगर (sock_owned_by_user(sk))
		__NET_INC_STATS(net, LINUX_MIB_LOCKDROPPEDICMPS);

	*app = asoc;
	*tpp = transport;
	वापस sk;

out:
	sctp_transport_put(transport);
	वापस शून्य;
पूर्ण

/* Common cleanup code क्रम icmp/icmpv6 error handler. */
व्योम sctp_err_finish(काष्ठा sock *sk, काष्ठा sctp_transport *t)
	__releases(&((__sk)->sk_lock.slock))
अणु
	bh_unlock_sock(sk);
	sctp_transport_put(t);
पूर्ण

/*
 * This routine is called by the ICMP module when it माला_लो some
 * sort of error condition.  If err < 0 then the socket should
 * be बंदd and the error वापसed to the user.  If err > 0
 * it's just the icmp type << 8 | icmp code.  After adjusपंचांगent
 * header poपूर्णांकs to the first 8 bytes of the sctp header.  We need
 * to find the appropriate port.
 *
 * The locking strategy used here is very "optimistic". When
 * someone अन्यथा accesses the socket the ICMP is just dropped
 * and क्रम some paths there is no check at all.
 * A more general error queue to queue errors क्रम later handling
 * is probably better.
 *
 */
पूर्णांक sctp_v4_err(काष्ठा sk_buff *skb, __u32 info)
अणु
	स्थिर काष्ठा iphdr *iph = (स्थिर काष्ठा iphdr *)skb->data;
	स्थिर पूर्णांक ihlen = iph->ihl * 4;
	स्थिर पूर्णांक type = icmp_hdr(skb)->type;
	स्थिर पूर्णांक code = icmp_hdr(skb)->code;
	काष्ठा sock *sk;
	काष्ठा sctp_association *asoc = शून्य;
	काष्ठा sctp_transport *transport;
	काष्ठा inet_sock *inet;
	__u16 saveip, savesctp;
	पूर्णांक err;
	काष्ठा net *net = dev_net(skb->dev);

	/* Fix up skb to look at the embedded net header. */
	saveip = skb->network_header;
	savesctp = skb->transport_header;
	skb_reset_network_header(skb);
	skb_set_transport_header(skb, ihlen);
	sk = sctp_err_lookup(net, AF_INET, skb, sctp_hdr(skb), &asoc, &transport);
	/* Put back, the original values. */
	skb->network_header = saveip;
	skb->transport_header = savesctp;
	अगर (!sk) अणु
		__ICMP_INC_STATS(net, ICMP_MIB_INERRORS);
		वापस -ENOENT;
	पूर्ण
	/* Warning:  The sock lock is held.  Remember to call
	 * sctp_err_finish!
	 */

	चयन (type) अणु
	हाल ICMP_PARAMETERPROB:
		err = EPROTO;
		अवरोध;
	हाल ICMP_DEST_UNREACH:
		अगर (code > NR_ICMP_UNREACH)
			जाओ out_unlock;

		/* PMTU discovery (RFC1191) */
		अगर (ICMP_FRAG_NEEDED == code) अणु
			sctp_icmp_frag_needed(sk, asoc, transport,
					      SCTP_TRUNC4(info));
			जाओ out_unlock;
		पूर्ण अन्यथा अणु
			अगर (ICMP_PROT_UNREACH == code) अणु
				sctp_icmp_proto_unreachable(sk, asoc,
							    transport);
				जाओ out_unlock;
			पूर्ण
		पूर्ण
		err = icmp_err_convert[code].त्रुटि_सं;
		अवरोध;
	हाल ICMP_TIME_EXCEEDED:
		/* Ignore any समय exceeded errors due to fragment reassembly
		 * समयouts.
		 */
		अगर (ICMP_EXC_FRAGTIME == code)
			जाओ out_unlock;

		err = EHOSTUNREACH;
		अवरोध;
	हाल ICMP_REसूचीECT:
		sctp_icmp_redirect(sk, transport, skb);
		/* Fall through to out_unlock. */
	शेष:
		जाओ out_unlock;
	पूर्ण

	inet = inet_sk(sk);
	अगर (!sock_owned_by_user(sk) && inet->recverr) अणु
		sk->sk_err = err;
		sk->sk_error_report(sk);
	पूर्ण अन्यथा अणु  /* Only an error on समयout */
		sk->sk_err_soft = err;
	पूर्ण

out_unlock:
	sctp_err_finish(sk, transport);
	वापस 0;
पूर्ण

/*
 * RFC 2960, 8.4 - Handle "Out of the blue" Packets.
 *
 * This function scans all the chunks in the OOTB packet to determine अगर
 * the packet should be discarded right away.  If a response might be needed
 * क्रम this packet, or, अगर further processing is possible, the packet will
 * be queued to a proper inqueue क्रम the next phase of handling.
 *
 * Output:
 * Return 0 - If further processing is needed.
 * Return 1 - If the packet can be discarded right away.
 */
अटल पूर्णांक sctp_rcv_ootb(काष्ठा sk_buff *skb)
अणु
	काष्ठा sctp_chunkhdr *ch, _ch;
	पूर्णांक ch_end, offset = 0;

	/* Scan through all the chunks in the packet.  */
	करो अणु
		/* Make sure we have at least the header there */
		अगर (offset + माप(_ch) > skb->len)
			अवरोध;

		ch = skb_header_poपूर्णांकer(skb, offset, माप(*ch), &_ch);

		/* Break out अगर chunk length is less then minimal. */
		अगर (ntohs(ch->length) < माप(_ch))
			अवरोध;

		ch_end = offset + SCTP_PAD4(ntohs(ch->length));
		अगर (ch_end > skb->len)
			अवरोध;

		/* RFC 8.4, 2) If the OOTB packet contains an ABORT chunk, the
		 * receiver MUST silently discard the OOTB packet and take no
		 * further action.
		 */
		अगर (SCTP_CID_ABORT == ch->type)
			जाओ discard;

		/* RFC 8.4, 6) If the packet contains a SHUTDOWN COMPLETE
		 * chunk, the receiver should silently discard the packet
		 * and take no further action.
		 */
		अगर (SCTP_CID_SHUTDOWN_COMPLETE == ch->type)
			जाओ discard;

		/* RFC 4460, 2.11.2
		 * This will discard packets with INIT chunk bundled as
		 * subsequent chunks in the packet.  When INIT is first,
		 * the normal INIT processing will discard the chunk.
		 */
		अगर (SCTP_CID_INIT == ch->type && (व्योम *)ch != skb->data)
			जाओ discard;

		offset = ch_end;
	पूर्ण जबतक (ch_end < skb->len);

	वापस 0;

discard:
	वापस 1;
पूर्ण

/* Insert endpoपूर्णांक पूर्णांकo the hash table.  */
अटल पूर्णांक __sctp_hash_endpoपूर्णांक(काष्ठा sctp_endpoपूर्णांक *ep)
अणु
	काष्ठा sock *sk = ep->base.sk;
	काष्ठा net *net = sock_net(sk);
	काष्ठा sctp_hashbucket *head;
	काष्ठा sctp_ep_common *epb;

	epb = &ep->base;
	epb->hashent = sctp_ep_hashfn(net, epb->bind_addr.port);
	head = &sctp_ep_hashtable[epb->hashent];

	अगर (sk->sk_reuseport) अणु
		bool any = sctp_is_ep_boundall(sk);
		काष्ठा sctp_ep_common *epb2;
		काष्ठा list_head *list;
		पूर्णांक cnt = 0, err = 1;

		list_क्रम_each(list, &ep->base.bind_addr.address_list)
			cnt++;

		sctp_क्रम_each_hentry(epb2, &head->chain) अणु
			काष्ठा sock *sk2 = epb2->sk;

			अगर (!net_eq(sock_net(sk2), net) || sk2 == sk ||
			    !uid_eq(sock_i_uid(sk2), sock_i_uid(sk)) ||
			    !sk2->sk_reuseport)
				जारी;

			err = sctp_bind_addrs_check(sctp_sk(sk2),
						    sctp_sk(sk), cnt);
			अगर (!err) अणु
				err = reuseport_add_sock(sk, sk2, any);
				अगर (err)
					वापस err;
				अवरोध;
			पूर्ण अन्यथा अगर (err < 0) अणु
				वापस err;
			पूर्ण
		पूर्ण

		अगर (err) अणु
			err = reuseport_alloc(sk, any);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	ग_लिखो_lock(&head->lock);
	hlist_add_head(&epb->node, &head->chain);
	ग_लिखो_unlock(&head->lock);
	वापस 0;
पूर्ण

/* Add an endpoपूर्णांक to the hash. Local BH-safe. */
पूर्णांक sctp_hash_endpoपूर्णांक(काष्ठा sctp_endpoपूर्णांक *ep)
अणु
	पूर्णांक err;

	local_bh_disable();
	err = __sctp_hash_endpoपूर्णांक(ep);
	local_bh_enable();

	वापस err;
पूर्ण

/* Remove endpoपूर्णांक from the hash table.  */
अटल व्योम __sctp_unhash_endpoपूर्णांक(काष्ठा sctp_endpoपूर्णांक *ep)
अणु
	काष्ठा sock *sk = ep->base.sk;
	काष्ठा sctp_hashbucket *head;
	काष्ठा sctp_ep_common *epb;

	epb = &ep->base;

	epb->hashent = sctp_ep_hashfn(sock_net(sk), epb->bind_addr.port);

	head = &sctp_ep_hashtable[epb->hashent];

	अगर (rcu_access_poपूर्णांकer(sk->sk_reuseport_cb))
		reuseport_detach_sock(sk);

	ग_लिखो_lock(&head->lock);
	hlist_del_init(&epb->node);
	ग_लिखो_unlock(&head->lock);
पूर्ण

/* Remove endpoपूर्णांक from the hash.  Local BH-safe. */
व्योम sctp_unhash_endpoपूर्णांक(काष्ठा sctp_endpoपूर्णांक *ep)
अणु
	local_bh_disable();
	__sctp_unhash_endpoपूर्णांक(ep);
	local_bh_enable();
पूर्ण

अटल अंतरभूत __u32 sctp_hashfn(स्थिर काष्ठा net *net, __be16 lport,
				स्थिर जोड़ sctp_addr *paddr, __u32 seed)
अणु
	__u32 addr;

	अगर (paddr->sa.sa_family == AF_INET6)
		addr = jhash(&paddr->v6.sin6_addr, 16, seed);
	अन्यथा
		addr = (__क्रमce __u32)paddr->v4.sin_addr.s_addr;

	वापस  jhash_3words(addr, ((__क्रमce __u32)paddr->v4.sin_port) << 16 |
			     (__क्रमce __u32)lport, net_hash_mix(net), seed);
पूर्ण

/* Look up an endpoपूर्णांक. */
अटल काष्ठा sctp_endpoपूर्णांक *__sctp_rcv_lookup_endpoपूर्णांक(
					काष्ठा net *net, काष्ठा sk_buff *skb,
					स्थिर जोड़ sctp_addr *laddr,
					स्थिर जोड़ sctp_addr *paddr)
अणु
	काष्ठा sctp_hashbucket *head;
	काष्ठा sctp_ep_common *epb;
	काष्ठा sctp_endpoपूर्णांक *ep;
	काष्ठा sock *sk;
	__be16 lport;
	पूर्णांक hash;

	lport = laddr->v4.sin_port;
	hash = sctp_ep_hashfn(net, ntohs(lport));
	head = &sctp_ep_hashtable[hash];
	पढ़ो_lock(&head->lock);
	sctp_क्रम_each_hentry(epb, &head->chain) अणु
		ep = sctp_ep(epb);
		अगर (sctp_endpoपूर्णांक_is_match(ep, net, laddr))
			जाओ hit;
	पूर्ण

	ep = sctp_sk(net->sctp.ctl_sock)->ep;

hit:
	sk = ep->base.sk;
	अगर (sk->sk_reuseport) अणु
		__u32 phash = sctp_hashfn(net, lport, paddr, 0);

		sk = reuseport_select_sock(sk, phash, skb,
					   माप(काष्ठा sctphdr));
		अगर (sk)
			ep = sctp_sk(sk)->ep;
	पूर्ण
	sctp_endpoपूर्णांक_hold(ep);
	पढ़ो_unlock(&head->lock);
	वापस ep;
पूर्ण

/* rhashtable क्रम transport */
काष्ठा sctp_hash_cmp_arg अणु
	स्थिर जोड़ sctp_addr	*paddr;
	स्थिर काष्ठा net	*net;
	__be16			lport;
पूर्ण;

अटल अंतरभूत पूर्णांक sctp_hash_cmp(काष्ठा rhashtable_compare_arg *arg,
				स्थिर व्योम *ptr)
अणु
	काष्ठा sctp_transport *t = (काष्ठा sctp_transport *)ptr;
	स्थिर काष्ठा sctp_hash_cmp_arg *x = arg->key;
	पूर्णांक err = 1;

	अगर (!sctp_cmp_addr_exact(&t->ipaddr, x->paddr))
		वापस err;
	अगर (!sctp_transport_hold(t))
		वापस err;

	अगर (!net_eq(t->asoc->base.net, x->net))
		जाओ out;
	अगर (x->lport != htons(t->asoc->base.bind_addr.port))
		जाओ out;

	err = 0;
out:
	sctp_transport_put(t);
	वापस err;
पूर्ण

अटल अंतरभूत __u32 sctp_hash_obj(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा sctp_transport *t = data;

	वापस sctp_hashfn(t->asoc->base.net,
			   htons(t->asoc->base.bind_addr.port),
			   &t->ipaddr, seed);
पूर्ण

अटल अंतरभूत __u32 sctp_hash_key(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा sctp_hash_cmp_arg *x = data;

	वापस sctp_hashfn(x->net, x->lport, x->paddr, seed);
पूर्ण

अटल स्थिर काष्ठा rhashtable_params sctp_hash_params = अणु
	.head_offset		= दुरत्व(काष्ठा sctp_transport, node),
	.hashfn			= sctp_hash_key,
	.obj_hashfn		= sctp_hash_obj,
	.obj_cmpfn		= sctp_hash_cmp,
	.स्वतःmatic_shrinking	= true,
पूर्ण;

पूर्णांक sctp_transport_hashtable_init(व्योम)
अणु
	वापस rhltable_init(&sctp_transport_hashtable, &sctp_hash_params);
पूर्ण

व्योम sctp_transport_hashtable_destroy(व्योम)
अणु
	rhltable_destroy(&sctp_transport_hashtable);
पूर्ण

पूर्णांक sctp_hash_transport(काष्ठा sctp_transport *t)
अणु
	काष्ठा sctp_transport *transport;
	काष्ठा rhlist_head *पंचांगp, *list;
	काष्ठा sctp_hash_cmp_arg arg;
	पूर्णांक err;

	अगर (t->asoc->temp)
		वापस 0;

	arg.net   = t->asoc->base.net;
	arg.paddr = &t->ipaddr;
	arg.lport = htons(t->asoc->base.bind_addr.port);

	rcu_पढ़ो_lock();
	list = rhltable_lookup(&sctp_transport_hashtable, &arg,
			       sctp_hash_params);

	rhl_क्रम_each_entry_rcu(transport, पंचांगp, list, node)
		अगर (transport->asoc->ep == t->asoc->ep) अणु
			rcu_पढ़ो_unlock();
			वापस -EEXIST;
		पूर्ण
	rcu_पढ़ो_unlock();

	err = rhltable_insert_key(&sctp_transport_hashtable, &arg,
				  &t->node, sctp_hash_params);
	अगर (err)
		pr_err_once("insert transport fail, errno %d\n", err);

	वापस err;
पूर्ण

व्योम sctp_unhash_transport(काष्ठा sctp_transport *t)
अणु
	अगर (t->asoc->temp)
		वापस;

	rhltable_हटाओ(&sctp_transport_hashtable, &t->node,
			sctp_hash_params);
पूर्ण

/* वापस a transport with holding it */
काष्ठा sctp_transport *sctp_addrs_lookup_transport(
				काष्ठा net *net,
				स्थिर जोड़ sctp_addr *laddr,
				स्थिर जोड़ sctp_addr *paddr)
अणु
	काष्ठा rhlist_head *पंचांगp, *list;
	काष्ठा sctp_transport *t;
	काष्ठा sctp_hash_cmp_arg arg = अणु
		.paddr = paddr,
		.net   = net,
		.lport = laddr->v4.sin_port,
	पूर्ण;

	list = rhltable_lookup(&sctp_transport_hashtable, &arg,
			       sctp_hash_params);

	rhl_क्रम_each_entry_rcu(t, पंचांगp, list, node) अणु
		अगर (!sctp_transport_hold(t))
			जारी;

		अगर (sctp_bind_addr_match(&t->asoc->base.bind_addr,
					 laddr, sctp_sk(t->asoc->base.sk)))
			वापस t;
		sctp_transport_put(t);
	पूर्ण

	वापस शून्य;
पूर्ण

/* वापस a transport without holding it, as it's only used under sock lock */
काष्ठा sctp_transport *sctp_epaddr_lookup_transport(
				स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
				स्थिर जोड़ sctp_addr *paddr)
अणु
	काष्ठा rhlist_head *पंचांगp, *list;
	काष्ठा sctp_transport *t;
	काष्ठा sctp_hash_cmp_arg arg = अणु
		.paddr = paddr,
		.net   = ep->base.net,
		.lport = htons(ep->base.bind_addr.port),
	पूर्ण;

	list = rhltable_lookup(&sctp_transport_hashtable, &arg,
			       sctp_hash_params);

	rhl_क्रम_each_entry_rcu(t, पंचांगp, list, node)
		अगर (ep == t->asoc->ep)
			वापस t;

	वापस शून्य;
पूर्ण

/* Look up an association. */
अटल काष्ठा sctp_association *__sctp_lookup_association(
					काष्ठा net *net,
					स्थिर जोड़ sctp_addr *local,
					स्थिर जोड़ sctp_addr *peer,
					काष्ठा sctp_transport **pt)
अणु
	काष्ठा sctp_transport *t;
	काष्ठा sctp_association *asoc = शून्य;

	t = sctp_addrs_lookup_transport(net, local, peer);
	अगर (!t)
		जाओ out;

	asoc = t->asoc;
	*pt = t;

out:
	वापस asoc;
पूर्ण

/* Look up an association. रक्षित by RCU पढ़ो lock */
अटल
काष्ठा sctp_association *sctp_lookup_association(काष्ठा net *net,
						 स्थिर जोड़ sctp_addr *laddr,
						 स्थिर जोड़ sctp_addr *paddr,
						 काष्ठा sctp_transport **transportp)
अणु
	काष्ठा sctp_association *asoc;

	rcu_पढ़ो_lock();
	asoc = __sctp_lookup_association(net, laddr, paddr, transportp);
	rcu_पढ़ो_unlock();

	वापस asoc;
पूर्ण

/* Is there an association matching the given local and peer addresses? */
bool sctp_has_association(काष्ठा net *net,
			  स्थिर जोड़ sctp_addr *laddr,
			  स्थिर जोड़ sctp_addr *paddr)
अणु
	काष्ठा sctp_transport *transport;

	अगर (sctp_lookup_association(net, laddr, paddr, &transport)) अणु
		sctp_transport_put(transport);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * SCTP Implementors Guide, 2.18 Handling of address
 * parameters within the INIT or INIT-ACK.
 *
 * D) When searching क्रम a matching TCB upon reception of an INIT
 *    or INIT-ACK chunk the receiver SHOULD use not only the
 *    source address of the packet (containing the INIT or
 *    INIT-ACK) but the receiver SHOULD also use all valid
 *    address parameters contained within the chunk.
 *
 * 2.18.3 Solution description
 *
 * This new text clearly specअगरies to an implementor the need
 * to look within the INIT or INIT-ACK. Any implementation that
 * करोes not करो this, may not be able to establish associations
 * in certain circumstances.
 *
 */
अटल काष्ठा sctp_association *__sctp_rcv_init_lookup(काष्ठा net *net,
	काष्ठा sk_buff *skb,
	स्थिर जोड़ sctp_addr *laddr, काष्ठा sctp_transport **transportp)
अणु
	काष्ठा sctp_association *asoc;
	जोड़ sctp_addr addr;
	जोड़ sctp_addr *paddr = &addr;
	काष्ठा sctphdr *sh = sctp_hdr(skb);
	जोड़ sctp_params params;
	काष्ठा sctp_init_chunk *init;
	काष्ठा sctp_af *af;

	/*
	 * This code will NOT touch anything inside the chunk--it is
	 * strictly READ-ONLY.
	 *
	 * RFC 2960 3  SCTP packet Format
	 *
	 * Multiple chunks can be bundled पूर्णांकo one SCTP packet up to
	 * the MTU size, except क्रम the INIT, INIT ACK, and SHUTDOWN
	 * COMPLETE chunks.  These chunks MUST NOT be bundled with any
	 * other chunk in a packet.  See Section 6.10 क्रम more details
	 * on chunk bundling.
	 */

	/* Find the start of the TLVs and the end of the chunk.  This is
	 * the region we search क्रम address parameters.
	 */
	init = (काष्ठा sctp_init_chunk *)skb->data;

	/* Walk the parameters looking क्रम embedded addresses. */
	sctp_walk_params(params, init, init_hdr.params) अणु

		/* Note: Ignoring hostname addresses. */
		af = sctp_get_af_specअगरic(param_type2af(params.p->type));
		अगर (!af)
			जारी;

		af->from_addr_param(paddr, params.addr, sh->source, 0);

		asoc = __sctp_lookup_association(net, laddr, paddr, transportp);
		अगर (asoc)
			वापस asoc;
	पूर्ण

	वापस शून्य;
पूर्ण

/* ADD-IP, Section 5.2
 * When an endpoपूर्णांक receives an ASCONF Chunk from the remote peer
 * special procedures may be needed to identअगरy the association the
 * ASCONF Chunk is associated with. To properly find the association
 * the following procedures SHOULD be followed:
 *
 * D2) If the association is not found, use the address found in the
 * Address Parameter TLV combined with the port number found in the
 * SCTP common header. If found proceed to rule D4.
 *
 * D2-ext) If more than one ASCONF Chunks are packed together, use the
 * address found in the ASCONF Address Parameter TLV of each of the
 * subsequent ASCONF Chunks. If found, proceed to rule D4.
 */
अटल काष्ठा sctp_association *__sctp_rcv_asconf_lookup(
					काष्ठा net *net,
					काष्ठा sctp_chunkhdr *ch,
					स्थिर जोड़ sctp_addr *laddr,
					__be16 peer_port,
					काष्ठा sctp_transport **transportp)
अणु
	काष्ठा sctp_addip_chunk *asconf = (काष्ठा sctp_addip_chunk *)ch;
	काष्ठा sctp_af *af;
	जोड़ sctp_addr_param *param;
	जोड़ sctp_addr paddr;

	/* Skip over the ADDIP header and find the Address parameter */
	param = (जोड़ sctp_addr_param *)(asconf + 1);

	af = sctp_get_af_specअगरic(param_type2af(param->p.type));
	अगर (unlikely(!af))
		वापस शून्य;

	af->from_addr_param(&paddr, param, peer_port, 0);

	वापस __sctp_lookup_association(net, laddr, &paddr, transportp);
पूर्ण


/* SCTP-AUTH, Section 6.3:
*    If the receiver करोes not find a STCB क्रम a packet containing an AUTH
*    chunk as the first chunk and not a COOKIE-ECHO chunk as the second
*    chunk, it MUST use the chunks after the AUTH chunk to look up an existing
*    association.
*
* This means that any chunks that can help us identअगरy the association need
* to be looked at to find this association.
*/
अटल काष्ठा sctp_association *__sctp_rcv_walk_lookup(काष्ठा net *net,
				      काष्ठा sk_buff *skb,
				      स्थिर जोड़ sctp_addr *laddr,
				      काष्ठा sctp_transport **transportp)
अणु
	काष्ठा sctp_association *asoc = शून्य;
	काष्ठा sctp_chunkhdr *ch;
	पूर्णांक have_auth = 0;
	अचिन्हित पूर्णांक chunk_num = 1;
	__u8 *ch_end;

	/* Walk through the chunks looking क्रम AUTH or ASCONF chunks
	 * to help us find the association.
	 */
	ch = (काष्ठा sctp_chunkhdr *)skb->data;
	करो अणु
		/* Break out अगर chunk length is less then minimal. */
		अगर (ntohs(ch->length) < माप(*ch))
			अवरोध;

		ch_end = ((__u8 *)ch) + SCTP_PAD4(ntohs(ch->length));
		अगर (ch_end > skb_tail_poपूर्णांकer(skb))
			अवरोध;

		चयन (ch->type) अणु
		हाल SCTP_CID_AUTH:
			have_auth = chunk_num;
			अवरोध;

		हाल SCTP_CID_COOKIE_ECHO:
			/* If a packet arrives containing an AUTH chunk as
			 * a first chunk, a COOKIE-ECHO chunk as the second
			 * chunk, and possibly more chunks after them, and
			 * the receiver करोes not have an STCB क्रम that
			 * packet, then authentication is based on
			 * the contents of the COOKIE- ECHO chunk.
			 */
			अगर (have_auth == 1 && chunk_num == 2)
				वापस शून्य;
			अवरोध;

		हाल SCTP_CID_ASCONF:
			अगर (have_auth || net->sctp.addip_noauth)
				asoc = __sctp_rcv_asconf_lookup(
						net, ch, laddr,
						sctp_hdr(skb)->source,
						transportp);
		शेष:
			अवरोध;
		पूर्ण

		अगर (asoc)
			अवरोध;

		ch = (काष्ठा sctp_chunkhdr *)ch_end;
		chunk_num++;
	पूर्ण जबतक (ch_end < skb_tail_poपूर्णांकer(skb));

	वापस asoc;
पूर्ण

/*
 * There are circumstances when we need to look inside the SCTP packet
 * क्रम inक्रमmation to help us find the association.   Examples
 * include looking inside of INIT/INIT-ACK chunks or after the AUTH
 * chunks.
 */
अटल काष्ठा sctp_association *__sctp_rcv_lookup_harder(काष्ठा net *net,
				      काष्ठा sk_buff *skb,
				      स्थिर जोड़ sctp_addr *laddr,
				      काष्ठा sctp_transport **transportp)
अणु
	काष्ठा sctp_chunkhdr *ch;

	/* We करो not allow GSO frames here as we need to linearize and
	 * then cannot guarantee frame boundaries. This shouldn't be an
	 * issue as packets hitting this are mostly INIT or INIT-ACK and
	 * those cannot be on GSO-style anyway.
	 */
	अगर (skb_is_gso(skb) && skb_is_gso_sctp(skb))
		वापस शून्य;

	ch = (काष्ठा sctp_chunkhdr *)skb->data;

	/* The code below will attempt to walk the chunk and extract
	 * parameter inक्रमmation.  Beक्रमe we करो that, we need to verअगरy
	 * that the chunk length करोesn't cause overflow.  Otherwise, we'll
	 * walk off the end.
	 */
	अगर (SCTP_PAD4(ntohs(ch->length)) > skb->len)
		वापस शून्य;

	/* If this is INIT/INIT-ACK look inside the chunk too. */
	अगर (ch->type == SCTP_CID_INIT || ch->type == SCTP_CID_INIT_ACK)
		वापस __sctp_rcv_init_lookup(net, skb, laddr, transportp);

	वापस __sctp_rcv_walk_lookup(net, skb, laddr, transportp);
पूर्ण

/* Lookup an association क्रम an inbound skb. */
अटल काष्ठा sctp_association *__sctp_rcv_lookup(काष्ठा net *net,
				      काष्ठा sk_buff *skb,
				      स्थिर जोड़ sctp_addr *paddr,
				      स्थिर जोड़ sctp_addr *laddr,
				      काष्ठा sctp_transport **transportp)
अणु
	काष्ठा sctp_association *asoc;

	asoc = __sctp_lookup_association(net, laddr, paddr, transportp);
	अगर (asoc)
		जाओ out;

	/* Further lookup क्रम INIT/INIT-ACK packets.
	 * SCTP Implementors Guide, 2.18 Handling of address
	 * parameters within the INIT or INIT-ACK.
	 */
	asoc = __sctp_rcv_lookup_harder(net, skb, laddr, transportp);
	अगर (asoc)
		जाओ out;

	अगर (paddr->sa.sa_family == AF_INET)
		pr_debug("sctp: asoc not found for src:%pI4:%d dst:%pI4:%d\n",
			 &laddr->v4.sin_addr, ntohs(laddr->v4.sin_port),
			 &paddr->v4.sin_addr, ntohs(paddr->v4.sin_port));
	अन्यथा
		pr_debug("sctp: asoc not found for src:%pI6:%d dst:%pI6:%d\n",
			 &laddr->v6.sin6_addr, ntohs(laddr->v6.sin6_port),
			 &paddr->v6.sin6_addr, ntohs(paddr->v6.sin6_port));

out:
	वापस asoc;
पूर्ण
