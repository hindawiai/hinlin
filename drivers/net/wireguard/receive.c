<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#समावेश "queueing.h"
#समावेश "device.h"
#समावेश "peer.h"
#समावेश "timers.h"
#समावेश "messages.h"
#समावेश "cookie.h"
#समावेश "socket.h"

#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/udp.h>
#समावेश <net/ip_tunnels.h>

/* Must be called with bh disabled. */
अटल व्योम update_rx_stats(काष्ठा wg_peer *peer, माप_प्रकार len)
अणु
	काष्ठा pcpu_sw_netstats *tstats =
		get_cpu_ptr(peer->device->dev->tstats);

	u64_stats_update_begin(&tstats->syncp);
	++tstats->rx_packets;
	tstats->rx_bytes += len;
	peer->rx_bytes += len;
	u64_stats_update_end(&tstats->syncp);
	put_cpu_ptr(tstats);
पूर्ण

#घोषणा SKB_TYPE_LE32(skb) (((काष्ठा message_header *)(skb)->data)->type)

अटल माप_प्रकार validate_header_len(काष्ठा sk_buff *skb)
अणु
	अगर (unlikely(skb->len < माप(काष्ठा message_header)))
		वापस 0;
	अगर (SKB_TYPE_LE32(skb) == cpu_to_le32(MESSAGE_DATA) &&
	    skb->len >= MESSAGE_MINIMUM_LENGTH)
		वापस माप(काष्ठा message_data);
	अगर (SKB_TYPE_LE32(skb) == cpu_to_le32(MESSAGE_HANDSHAKE_INITIATION) &&
	    skb->len == माप(काष्ठा message_handshake_initiation))
		वापस माप(काष्ठा message_handshake_initiation);
	अगर (SKB_TYPE_LE32(skb) == cpu_to_le32(MESSAGE_HANDSHAKE_RESPONSE) &&
	    skb->len == माप(काष्ठा message_handshake_response))
		वापस माप(काष्ठा message_handshake_response);
	अगर (SKB_TYPE_LE32(skb) == cpu_to_le32(MESSAGE_HANDSHAKE_COOKIE) &&
	    skb->len == माप(काष्ठा message_handshake_cookie))
		वापस माप(काष्ठा message_handshake_cookie);
	वापस 0;
पूर्ण

अटल पूर्णांक prepare_skb_header(काष्ठा sk_buff *skb, काष्ठा wg_device *wg)
अणु
	माप_प्रकार data_offset, data_len, header_len;
	काष्ठा udphdr *udp;

	अगर (unlikely(!wg_check_packet_protocol(skb) ||
		     skb_transport_header(skb) < skb->head ||
		     (skb_transport_header(skb) + माप(काष्ठा udphdr)) >
			     skb_tail_poपूर्णांकer(skb)))
		वापस -EINVAL; /* Bogus IP header */
	udp = udp_hdr(skb);
	data_offset = (u8 *)udp - skb->data;
	अगर (unlikely(data_offset > U16_MAX ||
		     data_offset + माप(काष्ठा udphdr) > skb->len))
		/* Packet has offset at impossible location or isn't big enough
		 * to have UDP fields.
		 */
		वापस -EINVAL;
	data_len = ntohs(udp->len);
	अगर (unlikely(data_len < माप(काष्ठा udphdr) ||
		     data_len > skb->len - data_offset))
		/* UDP packet is reporting too small of a size or lying about
		 * its size.
		 */
		वापस -EINVAL;
	data_len -= माप(काष्ठा udphdr);
	data_offset = (u8 *)udp + माप(काष्ठा udphdr) - skb->data;
	अगर (unlikely(!pskb_may_pull(skb,
				data_offset + माप(काष्ठा message_header)) ||
		     pskb_trim(skb, data_len + data_offset) < 0))
		वापस -EINVAL;
	skb_pull(skb, data_offset);
	अगर (unlikely(skb->len != data_len))
		/* Final len करोes not agree with calculated len */
		वापस -EINVAL;
	header_len = validate_header_len(skb);
	अगर (unlikely(!header_len))
		वापस -EINVAL;
	__skb_push(skb, data_offset);
	अगर (unlikely(!pskb_may_pull(skb, data_offset + header_len)))
		वापस -EINVAL;
	__skb_pull(skb, data_offset);
	वापस 0;
पूर्ण

अटल व्योम wg_receive_handshake_packet(काष्ठा wg_device *wg,
					काष्ठा sk_buff *skb)
अणु
	क्रमागत cookie_mac_state mac_state;
	काष्ठा wg_peer *peer = शून्य;
	/* This is global, so that our load calculation applies to the whole
	 * प्रणाली. We करोn't care about races with it at all.
	 */
	अटल u64 last_under_load;
	bool packet_needs_cookie;
	bool under_load;

	अगर (SKB_TYPE_LE32(skb) == cpu_to_le32(MESSAGE_HANDSHAKE_COOKIE)) अणु
		net_dbg_skb_ratelimited("%s: Receiving cookie response from %pISpfsc\n",
					wg->dev->name, skb);
		wg_cookie_message_consume(
			(काष्ठा message_handshake_cookie *)skb->data, wg);
		वापस;
	पूर्ण

	under_load = skb_queue_len(&wg->incoming_handshakes) >=
		     MAX_QUEUED_INCOMING_HANDSHAKES / 8;
	अगर (under_load) अणु
		last_under_load = kसमय_get_coarse_bootसमय_ns();
	पूर्ण अन्यथा अगर (last_under_load) अणु
		under_load = !wg_birthdate_has_expired(last_under_load, 1);
		अगर (!under_load)
			last_under_load = 0;
	पूर्ण
	mac_state = wg_cookie_validate_packet(&wg->cookie_checker, skb,
					      under_load);
	अगर ((under_load && mac_state == VALID_MAC_WITH_COOKIE) ||
	    (!under_load && mac_state == VALID_MAC_BUT_NO_COOKIE)) अणु
		packet_needs_cookie = false;
	पूर्ण अन्यथा अगर (under_load && mac_state == VALID_MAC_BUT_NO_COOKIE) अणु
		packet_needs_cookie = true;
	पूर्ण अन्यथा अणु
		net_dbg_skb_ratelimited("%s: Invalid MAC of handshake, dropping packet from %pISpfsc\n",
					wg->dev->name, skb);
		वापस;
	पूर्ण

	चयन (SKB_TYPE_LE32(skb)) अणु
	हाल cpu_to_le32(MESSAGE_HANDSHAKE_INITIATION): अणु
		काष्ठा message_handshake_initiation *message =
			(काष्ठा message_handshake_initiation *)skb->data;

		अगर (packet_needs_cookie) अणु
			wg_packet_send_handshake_cookie(wg, skb,
							message->sender_index);
			वापस;
		पूर्ण
		peer = wg_noise_handshake_consume_initiation(message, wg);
		अगर (unlikely(!peer)) अणु
			net_dbg_skb_ratelimited("%s: Invalid handshake initiation from %pISpfsc\n",
						wg->dev->name, skb);
			वापस;
		पूर्ण
		wg_socket_set_peer_endpoपूर्णांक_from_skb(peer, skb);
		net_dbg_ratelimited("%s: Receiving handshake initiation from peer %llu (%pISpfsc)\n",
				    wg->dev->name, peer->पूर्णांकernal_id,
				    &peer->endpoपूर्णांक.addr);
		wg_packet_send_handshake_response(peer);
		अवरोध;
	पूर्ण
	हाल cpu_to_le32(MESSAGE_HANDSHAKE_RESPONSE): अणु
		काष्ठा message_handshake_response *message =
			(काष्ठा message_handshake_response *)skb->data;

		अगर (packet_needs_cookie) अणु
			wg_packet_send_handshake_cookie(wg, skb,
							message->sender_index);
			वापस;
		पूर्ण
		peer = wg_noise_handshake_consume_response(message, wg);
		अगर (unlikely(!peer)) अणु
			net_dbg_skb_ratelimited("%s: Invalid handshake response from %pISpfsc\n",
						wg->dev->name, skb);
			वापस;
		पूर्ण
		wg_socket_set_peer_endpoपूर्णांक_from_skb(peer, skb);
		net_dbg_ratelimited("%s: Receiving handshake response from peer %llu (%pISpfsc)\n",
				    wg->dev->name, peer->पूर्णांकernal_id,
				    &peer->endpoपूर्णांक.addr);
		अगर (wg_noise_handshake_begin_session(&peer->handshake,
						     &peer->keypairs)) अणु
			wg_समयrs_session_derived(peer);
			wg_समयrs_handshake_complete(peer);
			/* Calling this function will either send any existing
			 * packets in the queue and not send a keepalive, which
			 * is the best हाल, Or, अगर there's nothing in the
			 * queue, it will send a keepalive, in order to give
			 * immediate confirmation of the session.
			 */
			wg_packet_send_keepalive(peer);
		पूर्ण
		अवरोध;
	पूर्ण
	पूर्ण

	अगर (unlikely(!peer)) अणु
		WARN(1, "Somehow a wrong type of packet wound up in the handshake queue!\n");
		वापस;
	पूर्ण

	local_bh_disable();
	update_rx_stats(peer, skb->len);
	local_bh_enable();

	wg_समयrs_any_authenticated_packet_received(peer);
	wg_समयrs_any_authenticated_packet_traversal(peer);
	wg_peer_put(peer);
पूर्ण

व्योम wg_packet_handshake_receive_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wg_device *wg = container_of(work, काष्ठा multicore_worker,
					    work)->ptr;
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(&wg->incoming_handshakes)) != शून्य) अणु
		wg_receive_handshake_packet(wg, skb);
		dev_kमुक्त_skb(skb);
		cond_resched();
	पूर्ण
पूर्ण

अटल व्योम keep_key_fresh(काष्ठा wg_peer *peer)
अणु
	काष्ठा noise_keypair *keypair;
	bool send;

	अगर (peer->sent_lasपंचांगinute_handshake)
		वापस;

	rcu_पढ़ो_lock_bh();
	keypair = rcu_dereference_bh(peer->keypairs.current_keypair);
	send = keypair && READ_ONCE(keypair->sending.is_valid) &&
	       keypair->i_am_the_initiator &&
	       wg_birthdate_has_expired(keypair->sending.birthdate,
			REJECT_AFTER_TIME - KEEPALIVE_TIMEOUT - REKEY_TIMEOUT);
	rcu_पढ़ो_unlock_bh();

	अगर (unlikely(send)) अणु
		peer->sent_lasपंचांगinute_handshake = true;
		wg_packet_send_queued_handshake_initiation(peer, false);
	पूर्ण
पूर्ण

अटल bool decrypt_packet(काष्ठा sk_buff *skb, काष्ठा noise_keypair *keypair)
अणु
	काष्ठा scatterlist sg[MAX_SKB_FRAGS + 8];
	काष्ठा sk_buff *trailer;
	अचिन्हित पूर्णांक offset;
	पूर्णांक num_frags;

	अगर (unlikely(!keypair))
		वापस false;

	अगर (unlikely(!READ_ONCE(keypair->receiving.is_valid) ||
		  wg_birthdate_has_expired(keypair->receiving.birthdate, REJECT_AFTER_TIME) ||
		  keypair->receiving_counter.counter >= REJECT_AFTER_MESSAGES)) अणु
		WRITE_ONCE(keypair->receiving.is_valid, false);
		वापस false;
	पूर्ण

	PACKET_CB(skb)->nonce =
		le64_to_cpu(((काष्ठा message_data *)skb->data)->counter);

	/* We ensure that the network header is part of the packet beक्रमe we
	 * call skb_cow_data, so that there's no chance that data is हटाओd
	 * from the skb, so that later we can extract the original endpoपूर्णांक.
	 */
	offset = skb->data - skb_network_header(skb);
	skb_push(skb, offset);
	num_frags = skb_cow_data(skb, 0, &trailer);
	offset += माप(काष्ठा message_data);
	skb_pull(skb, offset);
	अगर (unlikely(num_frags < 0 || num_frags > ARRAY_SIZE(sg)))
		वापस false;

	sg_init_table(sg, num_frags);
	अगर (skb_to_sgvec(skb, sg, 0, skb->len) <= 0)
		वापस false;

	अगर (!chacha20poly1305_decrypt_sg_inplace(sg, skb->len, शून्य, 0,
					         PACKET_CB(skb)->nonce,
						 keypair->receiving.key))
		वापस false;

	/* Another ugly situation of pushing and pulling the header so as to
	 * keep endpoपूर्णांक inक्रमmation पूर्णांकact.
	 */
	skb_push(skb, offset);
	अगर (pskb_trim(skb, skb->len - noise_encrypted_len(0)))
		वापस false;
	skb_pull(skb, offset);

	वापस true;
पूर्ण

/* This is RFC6479, a replay detection biपंचांगap algorithm that aव्योमs bitshअगरts */
अटल bool counter_validate(काष्ठा noise_replay_counter *counter, u64 their_counter)
अणु
	अचिन्हित दीर्घ index, index_current, top, i;
	bool ret = false;

	spin_lock_bh(&counter->lock);

	अगर (unlikely(counter->counter >= REJECT_AFTER_MESSAGES + 1 ||
		     their_counter >= REJECT_AFTER_MESSAGES))
		जाओ out;

	++their_counter;

	अगर (unlikely((COUNTER_WINDOW_SIZE + their_counter) <
		     counter->counter))
		जाओ out;

	index = their_counter >> ilog2(BITS_PER_LONG);

	अगर (likely(their_counter > counter->counter)) अणु
		index_current = counter->counter >> ilog2(BITS_PER_LONG);
		top = min_t(अचिन्हित दीर्घ, index - index_current,
			    COUNTER_BITS_TOTAL / BITS_PER_LONG);
		क्रम (i = 1; i <= top; ++i)
			counter->backtrack[(i + index_current) &
				((COUNTER_BITS_TOTAL / BITS_PER_LONG) - 1)] = 0;
		counter->counter = their_counter;
	पूर्ण

	index &= (COUNTER_BITS_TOTAL / BITS_PER_LONG) - 1;
	ret = !test_and_set_bit(their_counter & (BITS_PER_LONG - 1),
				&counter->backtrack[index]);

out:
	spin_unlock_bh(&counter->lock);
	वापस ret;
पूर्ण

#समावेश "selftest/counter.c"

अटल व्योम wg_packet_consume_data_करोne(काष्ठा wg_peer *peer,
					काष्ठा sk_buff *skb,
					काष्ठा endpoपूर्णांक *endpoपूर्णांक)
अणु
	काष्ठा net_device *dev = peer->device->dev;
	अचिन्हित पूर्णांक len, len_beक्रमe_trim;
	काष्ठा wg_peer *routed_peer;

	wg_socket_set_peer_endpoपूर्णांक(peer, endpoपूर्णांक);

	अगर (unlikely(wg_noise_received_with_keypair(&peer->keypairs,
						    PACKET_CB(skb)->keypair))) अणु
		wg_समयrs_handshake_complete(peer);
		wg_packet_send_staged_packets(peer);
	पूर्ण

	keep_key_fresh(peer);

	wg_समयrs_any_authenticated_packet_received(peer);
	wg_समयrs_any_authenticated_packet_traversal(peer);

	/* A packet with length 0 is a keepalive packet */
	अगर (unlikely(!skb->len)) अणु
		update_rx_stats(peer, message_data_len(0));
		net_dbg_ratelimited("%s: Receiving keepalive packet from peer %llu (%pISpfsc)\n",
				    dev->name, peer->पूर्णांकernal_id,
				    &peer->endpoपूर्णांक.addr);
		जाओ packet_processed;
	पूर्ण

	wg_समयrs_data_received(peer);

	अगर (unlikely(skb_network_header(skb) < skb->head))
		जाओ dishonest_packet_size;
	अगर (unlikely(!(pskb_network_may_pull(skb, माप(काष्ठा iphdr)) &&
		       (ip_hdr(skb)->version == 4 ||
			(ip_hdr(skb)->version == 6 &&
			 pskb_network_may_pull(skb, माप(काष्ठा ipv6hdr)))))))
		जाओ dishonest_packet_type;

	skb->dev = dev;
	/* We've alपढ़ोy verअगरied the Poly1305 auth tag, which means this packet
	 * was not modअगरied in transit. We can thereक्रमe tell the networking
	 * stack that all checksums of every layer of encapsulation have alपढ़ोy
	 * been checked "by the hardware" and thereक्रमe is unnecessary to check
	 * again in software.
	 */
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb->csum_level = ~0; /* All levels */
	skb->protocol = ip_tunnel_parse_protocol(skb);
	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		len = ntohs(ip_hdr(skb)->tot_len);
		अगर (unlikely(len < माप(काष्ठा iphdr)))
			जाओ dishonest_packet_size;
		INET_ECN_decapsulate(skb, PACKET_CB(skb)->ds, ip_hdr(skb)->tos);
	पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
		len = ntohs(ipv6_hdr(skb)->payload_len) +
		      माप(काष्ठा ipv6hdr);
		INET_ECN_decapsulate(skb, PACKET_CB(skb)->ds, ipv6_get_dsfield(ipv6_hdr(skb)));
	पूर्ण अन्यथा अणु
		जाओ dishonest_packet_type;
	पूर्ण

	अगर (unlikely(len > skb->len))
		जाओ dishonest_packet_size;
	len_beक्रमe_trim = skb->len;
	अगर (unlikely(pskb_trim(skb, len)))
		जाओ packet_processed;

	routed_peer = wg_allowedips_lookup_src(&peer->device->peer_allowedips,
					       skb);
	wg_peer_put(routed_peer); /* We करोn't need the extra reference. */

	अगर (unlikely(routed_peer != peer))
		जाओ dishonest_packet_peer;

	napi_gro_receive(&peer->napi, skb);
	update_rx_stats(peer, message_data_len(len_beक्रमe_trim));
	वापस;

dishonest_packet_peer:
	net_dbg_skb_ratelimited("%s: Packet has unallowed src IP (%pISc) from peer %llu (%pISpfsc)\n",
				dev->name, skb, peer->पूर्णांकernal_id,
				&peer->endpoपूर्णांक.addr);
	++dev->stats.rx_errors;
	++dev->stats.rx_frame_errors;
	जाओ packet_processed;
dishonest_packet_type:
	net_dbg_ratelimited("%s: Packet is neither ipv4 nor ipv6 from peer %llu (%pISpfsc)\n",
			    dev->name, peer->पूर्णांकernal_id, &peer->endpoपूर्णांक.addr);
	++dev->stats.rx_errors;
	++dev->stats.rx_frame_errors;
	जाओ packet_processed;
dishonest_packet_size:
	net_dbg_ratelimited("%s: Packet has incorrect size from peer %llu (%pISpfsc)\n",
			    dev->name, peer->पूर्णांकernal_id, &peer->endpoपूर्णांक.addr);
	++dev->stats.rx_errors;
	++dev->stats.rx_length_errors;
	जाओ packet_processed;
packet_processed:
	dev_kमुक्त_skb(skb);
पूर्ण

पूर्णांक wg_packet_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा wg_peer *peer = container_of(napi, काष्ठा wg_peer, napi);
	काष्ठा noise_keypair *keypair;
	काष्ठा endpoपूर्णांक endpoपूर्णांक;
	क्रमागत packet_state state;
	काष्ठा sk_buff *skb;
	पूर्णांक work_करोne = 0;
	bool मुक्त;

	अगर (unlikely(budget <= 0))
		वापस 0;

	जबतक ((skb = wg_prev_queue_peek(&peer->rx_queue)) != शून्य &&
	       (state = atomic_पढ़ो_acquire(&PACKET_CB(skb)->state)) !=
		       PACKET_STATE_UNCRYPTED) अणु
		wg_prev_queue_drop_peeked(&peer->rx_queue);
		keypair = PACKET_CB(skb)->keypair;
		मुक्त = true;

		अगर (unlikely(state != PACKET_STATE_CRYPTED))
			जाओ next;

		अगर (unlikely(!counter_validate(&keypair->receiving_counter,
					       PACKET_CB(skb)->nonce))) अणु
			net_dbg_ratelimited("%s: Packet has invalid nonce %llu (max %llu)\n",
					    peer->device->dev->name,
					    PACKET_CB(skb)->nonce,
					    keypair->receiving_counter.counter);
			जाओ next;
		पूर्ण

		अगर (unlikely(wg_socket_endpoपूर्णांक_from_skb(&endpoपूर्णांक, skb)))
			जाओ next;

		wg_reset_packet(skb, false);
		wg_packet_consume_data_करोne(peer, skb, &endpoपूर्णांक);
		मुक्त = false;

next:
		wg_noise_keypair_put(keypair, false);
		wg_peer_put(peer);
		अगर (unlikely(मुक्त))
			dev_kमुक्त_skb(skb);

		अगर (++work_करोne >= budget)
			अवरोध;
	पूर्ण

	अगर (work_करोne < budget)
		napi_complete_करोne(napi, work_करोne);

	वापस work_करोne;
पूर्ण

व्योम wg_packet_decrypt_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा crypt_queue *queue = container_of(work, काष्ठा multicore_worker,
						 work)->ptr;
	काष्ठा sk_buff *skb;

	जबतक ((skb = ptr_ring_consume_bh(&queue->ring)) != शून्य) अणु
		क्रमागत packet_state state =
			likely(decrypt_packet(skb, PACKET_CB(skb)->keypair)) ?
				PACKET_STATE_CRYPTED : PACKET_STATE_DEAD;
		wg_queue_enqueue_per_peer_rx(skb, state);
		अगर (need_resched())
			cond_resched();
	पूर्ण
पूर्ण

अटल व्योम wg_packet_consume_data(काष्ठा wg_device *wg, काष्ठा sk_buff *skb)
अणु
	__le32 idx = ((काष्ठा message_data *)skb->data)->key_idx;
	काष्ठा wg_peer *peer = शून्य;
	पूर्णांक ret;

	rcu_पढ़ो_lock_bh();
	PACKET_CB(skb)->keypair =
		(काष्ठा noise_keypair *)wg_index_hashtable_lookup(
			wg->index_hashtable, INDEX_HASHTABLE_KEYPAIR, idx,
			&peer);
	अगर (unlikely(!wg_noise_keypair_get(PACKET_CB(skb)->keypair)))
		जाओ err_keypair;

	अगर (unlikely(READ_ONCE(peer->is_dead)))
		जाओ err;

	ret = wg_queue_enqueue_per_device_and_peer(&wg->decrypt_queue, &peer->rx_queue, skb,
						   wg->packet_crypt_wq, &wg->decrypt_queue.last_cpu);
	अगर (unlikely(ret == -EPIPE))
		wg_queue_enqueue_per_peer_rx(skb, PACKET_STATE_DEAD);
	अगर (likely(!ret || ret == -EPIPE)) अणु
		rcu_पढ़ो_unlock_bh();
		वापस;
	पूर्ण
err:
	wg_noise_keypair_put(PACKET_CB(skb)->keypair, false);
err_keypair:
	rcu_पढ़ो_unlock_bh();
	wg_peer_put(peer);
	dev_kमुक्त_skb(skb);
पूर्ण

व्योम wg_packet_receive(काष्ठा wg_device *wg, काष्ठा sk_buff *skb)
अणु
	अगर (unlikely(prepare_skb_header(skb, wg) < 0))
		जाओ err;
	चयन (SKB_TYPE_LE32(skb)) अणु
	हाल cpu_to_le32(MESSAGE_HANDSHAKE_INITIATION):
	हाल cpu_to_le32(MESSAGE_HANDSHAKE_RESPONSE):
	हाल cpu_to_le32(MESSAGE_HANDSHAKE_COOKIE): अणु
		पूर्णांक cpu;

		अगर (skb_queue_len(&wg->incoming_handshakes) >
			    MAX_QUEUED_INCOMING_HANDSHAKES ||
		    unlikely(!rng_is_initialized())) अणु
			net_dbg_skb_ratelimited("%s: Dropping handshake packet from %pISpfsc\n",
						wg->dev->name, skb);
			जाओ err;
		पूर्ण
		skb_queue_tail(&wg->incoming_handshakes, skb);
		/* Queues up a call to packet_process_queued_handshake_
		 * packets(skb):
		 */
		cpu = wg_cpumask_next_online(&wg->incoming_handshake_cpu);
		queue_work_on(cpu, wg->handshake_receive_wq,
			&per_cpu_ptr(wg->incoming_handshakes_worker, cpu)->work);
		अवरोध;
	पूर्ण
	हाल cpu_to_le32(MESSAGE_DATA):
		PACKET_CB(skb)->ds = ip_tunnel_get_dsfield(ip_hdr(skb), skb);
		wg_packet_consume_data(wg, skb);
		अवरोध;
	शेष:
		WARN(1, "Non-exhaustive parsing of packet header lead to unknown packet type!\n");
		जाओ err;
	पूर्ण
	वापस;

err:
	dev_kमुक्त_skb(skb);
पूर्ण
