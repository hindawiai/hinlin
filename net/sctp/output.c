<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 *
 * This file is part of the SCTP kernel implementation
 *
 * These functions handle output processing.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Karl Knutson          <karl@athena.chicago.il.us>
 *    Jon Grimm             <jgrimm@austin.ibm.com>
 *    Sridhar Samudrala     <sri@us.ibm.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/रुको.h>
#समावेश <linux/समय.स>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/net_namespace.h>

#समावेश <linux/socket.h> /* क्रम sa_family_t */
#समावेश <net/sock.h>

#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/sm.h>
#समावेश <net/sctp/checksum.h>

/* Forward declarations क्रम निजी helpers. */
अटल क्रमागत sctp_xmit __sctp_packet_append_chunk(काष्ठा sctp_packet *packet,
						 काष्ठा sctp_chunk *chunk);
अटल क्रमागत sctp_xmit sctp_packet_can_append_data(काष्ठा sctp_packet *packet,
						  काष्ठा sctp_chunk *chunk);
अटल व्योम sctp_packet_append_data(काष्ठा sctp_packet *packet,
				    काष्ठा sctp_chunk *chunk);
अटल क्रमागत sctp_xmit sctp_packet_will_fit(काष्ठा sctp_packet *packet,
					   काष्ठा sctp_chunk *chunk,
					   u16 chunk_len);

अटल व्योम sctp_packet_reset(काष्ठा sctp_packet *packet)
अणु
	/* sctp_packet_transmit() relies on this to reset size to the
	 * current overhead after sending packets.
	 */
	packet->size = packet->overhead;

	packet->has_cookie_echo = 0;
	packet->has_sack = 0;
	packet->has_data = 0;
	packet->has_auth = 0;
	packet->ipfragok = 0;
	packet->auth = शून्य;
पूर्ण

/* Config a packet.
 * This appears to be a followup set of initializations.
 */
व्योम sctp_packet_config(काष्ठा sctp_packet *packet, __u32 vtag,
			पूर्णांक ecn_capable)
अणु
	काष्ठा sctp_transport *tp = packet->transport;
	काष्ठा sctp_association *asoc = tp->asoc;
	काष्ठा sctp_sock *sp = शून्य;
	काष्ठा sock *sk;

	pr_debug("%s: packet:%p vtag:0x%x\n", __func__, packet, vtag);
	packet->vtag = vtag;

	/* करो the following jobs only once क्रम a flush schedule */
	अगर (!sctp_packet_empty(packet))
		वापस;

	/* set packet max_size with pathmtu, then calculate overhead */
	packet->max_size = tp->pathmtu;

	अगर (asoc) अणु
		sk = asoc->base.sk;
		sp = sctp_sk(sk);
	पूर्ण
	packet->overhead = sctp_mtu_payload(sp, 0, 0);
	packet->size = packet->overhead;

	अगर (!asoc)
		वापस;

	/* update dst or transport pathmtu अगर in need */
	अगर (!sctp_transport_dst_check(tp)) अणु
		sctp_transport_route(tp, शून्य, sp);
		अगर (asoc->param_flags & SPP_PMTUD_ENABLE)
			sctp_assoc_sync_pmtu(asoc);
	पूर्ण अन्यथा अगर (!sctp_transport_pmtu_check(tp)) अणु
		अगर (asoc->param_flags & SPP_PMTUD_ENABLE)
			sctp_assoc_sync_pmtu(asoc);
	पूर्ण

	अगर (asoc->pmtu_pending) अणु
		अगर (asoc->param_flags & SPP_PMTUD_ENABLE)
			sctp_assoc_sync_pmtu(asoc);
		asoc->pmtu_pending = 0;
	पूर्ण

	/* If there a is a prepend chunk stick it on the list beक्रमe
	 * any other chunks get appended.
	 */
	अगर (ecn_capable) अणु
		काष्ठा sctp_chunk *chunk = sctp_get_ecne_prepend(asoc);

		अगर (chunk)
			sctp_packet_append_chunk(packet, chunk);
	पूर्ण

	अगर (!tp->dst)
		वापस;

	/* set packet max_size with gso_max_size अगर gso is enabled*/
	rcu_पढ़ो_lock();
	अगर (__sk_dst_get(sk) != tp->dst) अणु
		dst_hold(tp->dst);
		sk_setup_caps(sk, tp->dst);
	पूर्ण
	packet->max_size = sk_can_gso(sk) ? tp->dst->dev->gso_max_size
					  : asoc->pathmtu;
	rcu_पढ़ो_unlock();
पूर्ण

/* Initialize the packet काष्ठाure. */
व्योम sctp_packet_init(काष्ठा sctp_packet *packet,
		      काष्ठा sctp_transport *transport,
		      __u16 sport, __u16 dport)
अणु
	pr_debug("%s: packet:%p transport:%p\n", __func__, packet, transport);

	packet->transport = transport;
	packet->source_port = sport;
	packet->destination_port = dport;
	INIT_LIST_HEAD(&packet->chunk_list);
	/* The overhead will be calculated by sctp_packet_config() */
	packet->overhead = 0;
	sctp_packet_reset(packet);
	packet->vtag = 0;
पूर्ण

/* Free a packet.  */
व्योम sctp_packet_मुक्त(काष्ठा sctp_packet *packet)
अणु
	काष्ठा sctp_chunk *chunk, *पंचांगp;

	pr_debug("%s: packet:%p\n", __func__, packet);

	list_क्रम_each_entry_safe(chunk, पंचांगp, &packet->chunk_list, list) अणु
		list_del_init(&chunk->list);
		sctp_chunk_मुक्त(chunk);
	पूर्ण
पूर्ण

/* This routine tries to append the chunk to the offered packet. If adding
 * the chunk causes the packet to exceed the path MTU and COOKIE_ECHO chunk
 * is not present in the packet, it transmits the input packet.
 * Data can be bundled with a packet containing a COOKIE_ECHO chunk as दीर्घ
 * as it can fit in the packet, but any more data that करोes not fit in this
 * packet can be sent only after receiving the COOKIE_ACK.
 */
क्रमागत sctp_xmit sctp_packet_transmit_chunk(काष्ठा sctp_packet *packet,
					  काष्ठा sctp_chunk *chunk,
					  पूर्णांक one_packet, gfp_t gfp)
अणु
	क्रमागत sctp_xmit retval;

	pr_debug("%s: packet:%p size:%zu chunk:%p size:%d\n", __func__,
		 packet, packet->size, chunk, chunk->skb ? chunk->skb->len : -1);

	चयन ((retval = (sctp_packet_append_chunk(packet, chunk)))) अणु
	हाल SCTP_XMIT_PMTU_FULL:
		अगर (!packet->has_cookie_echo) अणु
			पूर्णांक error = 0;

			error = sctp_packet_transmit(packet, gfp);
			अगर (error < 0)
				chunk->skb->sk->sk_err = -error;

			/* If we have an empty packet, then we can NOT ever
			 * वापस PMTU_FULL.
			 */
			अगर (!one_packet)
				retval = sctp_packet_append_chunk(packet,
								  chunk);
		पूर्ण
		अवरोध;

	हाल SCTP_XMIT_RWND_FULL:
	हाल SCTP_XMIT_OK:
	हाल SCTP_XMIT_DELAY:
		अवरोध;
	पूर्ण

	वापस retval;
पूर्ण

/* Try to bundle an auth chunk पूर्णांकo the packet. */
अटल क्रमागत sctp_xmit sctp_packet_bundle_auth(काष्ठा sctp_packet *pkt,
					      काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_association *asoc = pkt->transport->asoc;
	क्रमागत sctp_xmit retval = SCTP_XMIT_OK;
	काष्ठा sctp_chunk *auth;

	/* अगर we करोn't have an association, we can't करो authentication */
	अगर (!asoc)
		वापस retval;

	/* See अगर this is an auth chunk we are bundling or अगर
	 * auth is alपढ़ोy bundled.
	 */
	अगर (chunk->chunk_hdr->type == SCTP_CID_AUTH || pkt->has_auth)
		वापस retval;

	/* अगर the peer did not request this chunk to be authenticated,
	 * करोn't करो it
	 */
	अगर (!chunk->auth)
		वापस retval;

	auth = sctp_make_auth(asoc, chunk->shkey->key_id);
	अगर (!auth)
		वापस retval;

	auth->shkey = chunk->shkey;
	sctp_auth_shkey_hold(auth->shkey);

	retval = __sctp_packet_append_chunk(pkt, auth);

	अगर (retval != SCTP_XMIT_OK)
		sctp_chunk_मुक्त(auth);

	वापस retval;
पूर्ण

/* Try to bundle a SACK with the packet. */
अटल क्रमागत sctp_xmit sctp_packet_bundle_sack(काष्ठा sctp_packet *pkt,
					      काष्ठा sctp_chunk *chunk)
अणु
	क्रमागत sctp_xmit retval = SCTP_XMIT_OK;

	/* If sending DATA and haven't aleady bundled a SACK, try to
	 * bundle one in to the packet.
	 */
	अगर (sctp_chunk_is_data(chunk) && !pkt->has_sack &&
	    !pkt->has_cookie_echo) अणु
		काष्ठा sctp_association *asoc;
		काष्ठा समयr_list *समयr;
		asoc = pkt->transport->asoc;
		समयr = &asoc->समयrs[SCTP_EVENT_TIMEOUT_SACK];

		/* If the SACK समयr is running, we have a pending SACK */
		अगर (समयr_pending(समयr)) अणु
			काष्ठा sctp_chunk *sack;

			अगर (pkt->transport->sack_generation !=
			    pkt->transport->asoc->peer.sack_generation)
				वापस retval;

			asoc->a_rwnd = asoc->rwnd;
			sack = sctp_make_sack(asoc);
			अगर (sack) अणु
				retval = __sctp_packet_append_chunk(pkt, sack);
				अगर (retval != SCTP_XMIT_OK) अणु
					sctp_chunk_मुक्त(sack);
					जाओ out;
				पूर्ण
				SCTP_INC_STATS(asoc->base.net,
					       SCTP_MIB_OUTCTRLCHUNKS);
				asoc->stats.octrlchunks++;
				asoc->peer.sack_needed = 0;
				अगर (del_समयr(समयr))
					sctp_association_put(asoc);
			पूर्ण
		पूर्ण
	पूर्ण
out:
	वापस retval;
पूर्ण


/* Append a chunk to the offered packet reporting back any inability to करो
 * so.
 */
अटल क्रमागत sctp_xmit __sctp_packet_append_chunk(काष्ठा sctp_packet *packet,
						 काष्ठा sctp_chunk *chunk)
अणु
	__u16 chunk_len = SCTP_PAD4(ntohs(chunk->chunk_hdr->length));
	क्रमागत sctp_xmit retval = SCTP_XMIT_OK;

	/* Check to see अगर this chunk will fit पूर्णांकo the packet */
	retval = sctp_packet_will_fit(packet, chunk, chunk_len);
	अगर (retval != SCTP_XMIT_OK)
		जाओ finish;

	/* We believe that this chunk is OK to add to the packet */
	चयन (chunk->chunk_hdr->type) अणु
	हाल SCTP_CID_DATA:
	हाल SCTP_CID_I_DATA:
		/* Account क्रम the data being in the packet */
		sctp_packet_append_data(packet, chunk);
		/* Disallow SACK bundling after DATA. */
		packet->has_sack = 1;
		/* Disallow AUTH bundling after DATA */
		packet->has_auth = 1;
		/* Let it be knows that packet has DATA in it */
		packet->has_data = 1;
		/* बारtamp the chunk क्रम rtx purposes */
		chunk->sent_at = jअगरfies;
		/* Mainly used क्रम prsctp RTX policy */
		chunk->sent_count++;
		अवरोध;
	हाल SCTP_CID_COOKIE_ECHO:
		packet->has_cookie_echo = 1;
		अवरोध;

	हाल SCTP_CID_SACK:
		packet->has_sack = 1;
		अगर (chunk->asoc)
			chunk->asoc->stats.osacks++;
		अवरोध;

	हाल SCTP_CID_AUTH:
		packet->has_auth = 1;
		packet->auth = chunk;
		अवरोध;
	पूर्ण

	/* It is OK to send this chunk.  */
	list_add_tail(&chunk->list, &packet->chunk_list);
	packet->size += chunk_len;
	chunk->transport = packet->transport;
finish:
	वापस retval;
पूर्ण

/* Append a chunk to the offered packet reporting back any inability to करो
 * so.
 */
क्रमागत sctp_xmit sctp_packet_append_chunk(काष्ठा sctp_packet *packet,
					काष्ठा sctp_chunk *chunk)
अणु
	क्रमागत sctp_xmit retval = SCTP_XMIT_OK;

	pr_debug("%s: packet:%p chunk:%p\n", __func__, packet, chunk);

	/* Data chunks are special.  Beक्रमe seeing what अन्यथा we can
	 * bundle पूर्णांकo this packet, check to see अगर we are allowed to
	 * send this DATA.
	 */
	अगर (sctp_chunk_is_data(chunk)) अणु
		retval = sctp_packet_can_append_data(packet, chunk);
		अगर (retval != SCTP_XMIT_OK)
			जाओ finish;
	पूर्ण

	/* Try to bundle AUTH chunk */
	retval = sctp_packet_bundle_auth(packet, chunk);
	अगर (retval != SCTP_XMIT_OK)
		जाओ finish;

	/* Try to bundle SACK chunk */
	retval = sctp_packet_bundle_sack(packet, chunk);
	अगर (retval != SCTP_XMIT_OK)
		जाओ finish;

	retval = __sctp_packet_append_chunk(packet, chunk);

finish:
	वापस retval;
पूर्ण

अटल व्योम sctp_packet_gso_append(काष्ठा sk_buff *head, काष्ठा sk_buff *skb)
अणु
	अगर (SCTP_OUTPUT_CB(head)->last == head)
		skb_shinfo(head)->frag_list = skb;
	अन्यथा
		SCTP_OUTPUT_CB(head)->last->next = skb;
	SCTP_OUTPUT_CB(head)->last = skb;

	head->truesize += skb->truesize;
	head->data_len += skb->len;
	head->len += skb->len;
	refcount_add(skb->truesize, &head->sk->sk_wmem_alloc);

	__skb_header_release(skb);
पूर्ण

अटल पूर्णांक sctp_packet_pack(काष्ठा sctp_packet *packet,
			    काष्ठा sk_buff *head, पूर्णांक gso, gfp_t gfp)
अणु
	काष्ठा sctp_transport *tp = packet->transport;
	काष्ठा sctp_auth_chunk *auth = शून्य;
	काष्ठा sctp_chunk *chunk, *पंचांगp;
	पूर्णांक pkt_count = 0, pkt_size;
	काष्ठा sock *sk = head->sk;
	काष्ठा sk_buff *nskb;
	पूर्णांक auth_len = 0;

	अगर (gso) अणु
		skb_shinfo(head)->gso_type = sk->sk_gso_type;
		SCTP_OUTPUT_CB(head)->last = head;
	पूर्ण अन्यथा अणु
		nskb = head;
		pkt_size = packet->size;
		जाओ merge;
	पूर्ण

	करो अणु
		/* calculate the pkt_size and alloc nskb */
		pkt_size = packet->overhead;
		list_क्रम_each_entry_safe(chunk, पंचांगp, &packet->chunk_list,
					 list) अणु
			पूर्णांक padded = SCTP_PAD4(chunk->skb->len);

			अगर (chunk == packet->auth)
				auth_len = padded;
			अन्यथा अगर (auth_len + padded + packet->overhead >
				 tp->pathmtu)
				वापस 0;
			अन्यथा अगर (pkt_size + padded > tp->pathmtu)
				अवरोध;
			pkt_size += padded;
		पूर्ण
		nskb = alloc_skb(pkt_size + MAX_HEADER, gfp);
		अगर (!nskb)
			वापस 0;
		skb_reserve(nskb, packet->overhead + MAX_HEADER);

merge:
		/* merge chunks पूर्णांकo nskb and append nskb पूर्णांकo head list */
		pkt_size -= packet->overhead;
		list_क्रम_each_entry_safe(chunk, पंचांगp, &packet->chunk_list, list) अणु
			पूर्णांक padding;

			list_del_init(&chunk->list);
			अगर (sctp_chunk_is_data(chunk)) अणु
				अगर (!sctp_chunk_retransmitted(chunk) &&
				    !tp->rto_pending) अणु
					chunk->rtt_in_progress = 1;
					tp->rto_pending = 1;
				पूर्ण
			पूर्ण

			padding = SCTP_PAD4(chunk->skb->len) - chunk->skb->len;
			अगर (padding)
				skb_put_zero(chunk->skb, padding);

			अगर (chunk == packet->auth)
				auth = (काष्ठा sctp_auth_chunk *)
							skb_tail_poपूर्णांकer(nskb);

			skb_put_data(nskb, chunk->skb->data, chunk->skb->len);

			pr_debug("*** Chunk:%p[%s] %s 0x%x, length:%d, chunk->skb->len:%d, rtt_in_progress:%d\n",
				 chunk,
				 sctp_cname(SCTP_ST_CHUNK(chunk->chunk_hdr->type)),
				 chunk->has_tsn ? "TSN" : "No TSN",
				 chunk->has_tsn ? ntohl(chunk->subh.data_hdr->tsn) : 0,
				 ntohs(chunk->chunk_hdr->length), chunk->skb->len,
				 chunk->rtt_in_progress);

			pkt_size -= SCTP_PAD4(chunk->skb->len);

			अगर (!sctp_chunk_is_data(chunk) && chunk != packet->auth)
				sctp_chunk_मुक्त(chunk);

			अगर (!pkt_size)
				अवरोध;
		पूर्ण

		अगर (auth) अणु
			sctp_auth_calculate_hmac(tp->asoc, nskb, auth,
						 packet->auth->shkey, gfp);
			/* मुक्त auth अगर no more chunks, or add it back */
			अगर (list_empty(&packet->chunk_list))
				sctp_chunk_मुक्त(packet->auth);
			अन्यथा
				list_add(&packet->auth->list,
					 &packet->chunk_list);
		पूर्ण

		अगर (gso)
			sctp_packet_gso_append(head, nskb);

		pkt_count++;
	पूर्ण जबतक (!list_empty(&packet->chunk_list));

	अगर (gso) अणु
		स_रखो(head->cb, 0, max(माप(काष्ठा inet_skb_parm),
					माप(काष्ठा inet6_skb_parm)));
		skb_shinfo(head)->gso_segs = pkt_count;
		skb_shinfo(head)->gso_size = GSO_BY_FRAGS;
		जाओ chksum;
	पूर्ण

	अगर (sctp_checksum_disable)
		वापस 1;

	अगर (!(tp->dst->dev->features & NETIF_F_SCTP_CRC) ||
	    dst_xfrm(tp->dst) || packet->ipfragok || tp->encap_port) अणु
		काष्ठा sctphdr *sh =
			(काष्ठा sctphdr *)skb_transport_header(head);

		sh->checksum = sctp_compute_cksum(head, 0);
	पूर्ण अन्यथा अणु
chksum:
		head->ip_summed = CHECKSUM_PARTIAL;
		head->csum_not_inet = 1;
		head->csum_start = skb_transport_header(head) - head->head;
		head->csum_offset = दुरत्व(काष्ठा sctphdr, checksum);
	पूर्ण

	वापस pkt_count;
पूर्ण

/* All packets are sent to the network through this function from
 * sctp_outq_tail().
 *
 * The वापस value is always 0 क्रम now.
 */
पूर्णांक sctp_packet_transmit(काष्ठा sctp_packet *packet, gfp_t gfp)
अणु
	काष्ठा sctp_transport *tp = packet->transport;
	काष्ठा sctp_association *asoc = tp->asoc;
	काष्ठा sctp_chunk *chunk, *पंचांगp;
	पूर्णांक pkt_count, gso = 0;
	काष्ठा sk_buff *head;
	काष्ठा sctphdr *sh;
	काष्ठा sock *sk;

	pr_debug("%s: packet:%p\n", __func__, packet);
	अगर (list_empty(&packet->chunk_list))
		वापस 0;
	chunk = list_entry(packet->chunk_list.next, काष्ठा sctp_chunk, list);
	sk = chunk->skb->sk;

	/* check gso */
	अगर (packet->size > tp->pathmtu && !packet->ipfragok) अणु
		अगर (!sk_can_gso(sk)) अणु
			pr_err_once("Trying to GSO but underlying device doesn't support it.");
			जाओ out;
		पूर्ण
		gso = 1;
	पूर्ण

	/* alloc head skb */
	head = alloc_skb((gso ? packet->overhead : packet->size) +
			 MAX_HEADER, gfp);
	अगर (!head)
		जाओ out;
	skb_reserve(head, packet->overhead + MAX_HEADER);
	skb_set_owner_w(head, sk);

	/* set sctp header */
	sh = skb_push(head, माप(काष्ठा sctphdr));
	skb_reset_transport_header(head);
	sh->source = htons(packet->source_port);
	sh->dest = htons(packet->destination_port);
	sh->vtag = htonl(packet->vtag);
	sh->checksum = 0;

	/* drop packet अगर no dst */
	अगर (!tp->dst) अणु
		IP_INC_STATS(sock_net(sk), IPSTATS_MIB_OUTNOROUTES);
		kमुक्त_skb(head);
		जाओ out;
	पूर्ण

	/* pack up chunks */
	pkt_count = sctp_packet_pack(packet, head, gso, gfp);
	अगर (!pkt_count) अणु
		kमुक्त_skb(head);
		जाओ out;
	पूर्ण
	pr_debug("***sctp_transmit_packet*** skb->len:%d\n", head->len);

	/* start स्वतःबंद समयr */
	अगर (packet->has_data && sctp_state(asoc, ESTABLISHED) &&
	    asoc->समयouts[SCTP_EVENT_TIMEOUT_AUTOCLOSE]) अणु
		काष्ठा समयr_list *समयr =
			&asoc->समयrs[SCTP_EVENT_TIMEOUT_AUTOCLOSE];
		अचिन्हित दीर्घ समयout =
			asoc->समयouts[SCTP_EVENT_TIMEOUT_AUTOCLOSE];

		अगर (!mod_समयr(समयr, jअगरfies + समयout))
			sctp_association_hold(asoc);
	पूर्ण

	/* sctp xmit */
	tp->af_specअगरic->ecn_capable(sk);
	अगर (asoc) अणु
		asoc->stats.opackets += pkt_count;
		अगर (asoc->peer.last_sent_to != tp)
			asoc->peer.last_sent_to = tp;
	पूर्ण
	head->ignore_df = packet->ipfragok;
	अगर (tp->dst_pending_confirm)
		skb_set_dst_pending_confirm(head, 1);
	/* neighbour should be confirmed on successful transmission or
	 * positive error
	 */
	अगर (tp->af_specअगरic->sctp_xmit(head, tp) >= 0 &&
	    tp->dst_pending_confirm)
		tp->dst_pending_confirm = 0;

out:
	list_क्रम_each_entry_safe(chunk, पंचांगp, &packet->chunk_list, list) अणु
		list_del_init(&chunk->list);
		अगर (!sctp_chunk_is_data(chunk))
			sctp_chunk_मुक्त(chunk);
	पूर्ण
	sctp_packet_reset(packet);
	वापस 0;
पूर्ण

/********************************************************************
 * 2nd Level Abstractions
 ********************************************************************/

/* This निजी function check to see अगर a chunk can be added */
अटल क्रमागत sctp_xmit sctp_packet_can_append_data(काष्ठा sctp_packet *packet,
						  काष्ठा sctp_chunk *chunk)
अणु
	माप_प्रकार datasize, rwnd, inflight, flight_size;
	काष्ठा sctp_transport *transport = packet->transport;
	काष्ठा sctp_association *asoc = transport->asoc;
	काष्ठा sctp_outq *q = &asoc->outqueue;

	/* RFC 2960 6.1  Transmission of DATA Chunks
	 *
	 * A) At any given समय, the data sender MUST NOT transmit new data to
	 * any destination transport address अगर its peer's rwnd indicates
	 * that the peer has no buffer space (i.e. rwnd is 0, see Section
	 * 6.2.1).  However, regardless of the value of rwnd (including अगर it
	 * is 0), the data sender can always have one DATA chunk in flight to
	 * the receiver अगर allowed by cwnd (see rule B below).  This rule
	 * allows the sender to probe क्रम a change in rwnd that the sender
	 * missed due to the SACK having been lost in transit from the data
	 * receiver to the data sender.
	 */

	rwnd = asoc->peer.rwnd;
	inflight = q->outstanding_bytes;
	flight_size = transport->flight_size;

	datasize = sctp_data_size(chunk);

	अगर (datasize > rwnd && inflight > 0)
		/* We have (at least) one data chunk in flight,
		 * so we can't fall back to rule 6.1 B).
		 */
		वापस SCTP_XMIT_RWND_FULL;

	/* RFC 2960 6.1  Transmission of DATA Chunks
	 *
	 * B) At any given समय, the sender MUST NOT transmit new data
	 * to a given transport address अगर it has cwnd or more bytes
	 * of data outstanding to that transport address.
	 */
	/* RFC 7.2.4 & the Implementers Guide 2.8.
	 *
	 * 3) ...
	 *    When a Fast Retransmit is being perक्रमmed the sender SHOULD
	 *    ignore the value of cwnd and SHOULD NOT delay retransmission.
	 */
	अगर (chunk->fast_retransmit != SCTP_NEED_FRTX &&
	    flight_size >= transport->cwnd)
		वापस SCTP_XMIT_RWND_FULL;

	/* Nagle's algorithm to solve small-packet problem:
	 * Inhibit the sending of new chunks when new outgoing data arrives
	 * अगर any previously transmitted data on the connection reमुख्यs
	 * unacknowledged.
	 */

	अगर ((sctp_sk(asoc->base.sk)->nodelay || inflight == 0) &&
	    !asoc->क्रमce_delay)
		/* Nothing unacked */
		वापस SCTP_XMIT_OK;

	अगर (!sctp_packet_empty(packet))
		/* Append to packet */
		वापस SCTP_XMIT_OK;

	अगर (!sctp_state(asoc, ESTABLISHED))
		वापस SCTP_XMIT_OK;

	/* Check whether this chunk and all the rest of pending data will fit
	 * or delay in hopes of bundling a full sized packet.
	 */
	अगर (chunk->skb->len + q->out_qlen > transport->pathmtu -
	    packet->overhead - sctp_datachk_len(&chunk->asoc->stream) - 4)
		/* Enough data queued to fill a packet */
		वापस SCTP_XMIT_OK;

	/* Don't delay large message ग_लिखोs that may have been fragmented */
	अगर (!chunk->msg->can_delay)
		वापस SCTP_XMIT_OK;

	/* Defer until all data acked or packet full */
	वापस SCTP_XMIT_DELAY;
पूर्ण

/* This निजी function करोes management things when adding DATA chunk */
अटल व्योम sctp_packet_append_data(काष्ठा sctp_packet *packet,
				काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_transport *transport = packet->transport;
	माप_प्रकार datasize = sctp_data_size(chunk);
	काष्ठा sctp_association *asoc = transport->asoc;
	u32 rwnd = asoc->peer.rwnd;

	/* Keep track of how many bytes are in flight over this transport. */
	transport->flight_size += datasize;

	/* Keep track of how many bytes are in flight to the receiver. */
	asoc->outqueue.outstanding_bytes += datasize;

	/* Update our view of the receiver's rwnd. */
	अगर (datasize < rwnd)
		rwnd -= datasize;
	अन्यथा
		rwnd = 0;

	asoc->peer.rwnd = rwnd;
	sctp_chunk_assign_tsn(chunk);
	asoc->stream.si->assign_number(chunk);
पूर्ण

अटल क्रमागत sctp_xmit sctp_packet_will_fit(काष्ठा sctp_packet *packet,
					   काष्ठा sctp_chunk *chunk,
					   u16 chunk_len)
अणु
	क्रमागत sctp_xmit retval = SCTP_XMIT_OK;
	माप_प्रकार psize, pmtu, maxsize;

	/* Don't bundle in this packet if this chunk's auth key doesn't
	 * match other chunks alपढ़ोy enqueued on this packet. Also,
	 * करोn't bundle the chunk with auth key अगर other chunks in this
	 * packet करोn't have auth key.
	 */
	अगर ((packet->auth && chunk->shkey != packet->auth->shkey) ||
	    (!packet->auth && chunk->shkey &&
	     chunk->chunk_hdr->type != SCTP_CID_AUTH))
		वापस SCTP_XMIT_PMTU_FULL;

	psize = packet->size;
	अगर (packet->transport->asoc)
		pmtu = packet->transport->asoc->pathmtu;
	अन्यथा
		pmtu = packet->transport->pathmtu;

	/* Decide अगर we need to fragment or resubmit later. */
	अगर (psize + chunk_len > pmtu) अणु
		/* It's OK to fragment at IP level अगर any one of the following
		 * is true:
		 *	1. The packet is empty (meaning this chunk is greater
		 *	   the MTU)
		 *	2. The packet करोesn't have any data in it yet and data
		 *	   requires authentication.
		 */
		अगर (sctp_packet_empty(packet) ||
		    (!packet->has_data && chunk->auth)) अणु
			/* We no दीर्घer करो re-fragmentation.
			 * Just fragment at the IP layer, अगर we
			 * actually hit this condition
			 */
			packet->ipfragok = 1;
			जाओ out;
		पूर्ण

		/* Similarly, अगर this chunk was built beक्रमe a PMTU
		 * reduction, we have to fragment it at IP level now. So
		 * अगर the packet alपढ़ोy contains something, we need to
		 * flush.
		 */
		maxsize = pmtu - packet->overhead;
		अगर (packet->auth)
			maxsize -= SCTP_PAD4(packet->auth->skb->len);
		अगर (chunk_len > maxsize)
			retval = SCTP_XMIT_PMTU_FULL;

		/* It is also okay to fragment अगर the chunk we are
		 * adding is a control chunk, but only अगर current packet
		 * is not a GSO one otherwise it causes fragmentation of
		 * a large frame. So in this हाल we allow the
		 * fragmentation by क्रमcing it to be in a new packet.
		 */
		अगर (!sctp_chunk_is_data(chunk) && packet->has_data)
			retval = SCTP_XMIT_PMTU_FULL;

		अगर (psize + chunk_len > packet->max_size)
			/* Hit GSO/PMTU limit, gotta flush */
			retval = SCTP_XMIT_PMTU_FULL;

		अगर (!packet->transport->burst_limited &&
		    psize + chunk_len > (packet->transport->cwnd >> 1))
			/* Do not allow a single GSO packet to use more
			 * than half of cwnd.
			 */
			retval = SCTP_XMIT_PMTU_FULL;

		अगर (packet->transport->burst_limited &&
		    psize + chunk_len > (packet->transport->burst_limited >> 1))
			/* Do not allow a single GSO packet to use more
			 * than half of original cwnd.
			 */
			retval = SCTP_XMIT_PMTU_FULL;
		/* Otherwise it will fit in the GSO packet */
	पूर्ण

out:
	वापस retval;
पूर्ण
