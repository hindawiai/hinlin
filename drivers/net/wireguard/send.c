<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#समावेश "queueing.h"
#समावेश "timers.h"
#समावेश "device.h"
#समावेश "peer.h"
#समावेश "socket.h"
#समावेश "messages.h"
#समावेश "cookie.h"

#समावेश <linux/uपन.स>
#समावेश <linux/inetdevice.h>
#समावेश <linux/socket.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/udp.h>
#समावेश <net/sock.h>

अटल व्योम wg_packet_send_handshake_initiation(काष्ठा wg_peer *peer)
अणु
	काष्ठा message_handshake_initiation packet;

	अगर (!wg_birthdate_has_expired(atomic64_पढ़ो(&peer->last_sent_handshake),
				      REKEY_TIMEOUT))
		वापस; /* This function is rate limited. */

	atomic64_set(&peer->last_sent_handshake, kसमय_get_coarse_bootसमय_ns());
	net_dbg_ratelimited("%s: Sending handshake initiation to peer %llu (%pISpfsc)\n",
			    peer->device->dev->name, peer->पूर्णांकernal_id,
			    &peer->endpoपूर्णांक.addr);

	अगर (wg_noise_handshake_create_initiation(&packet, &peer->handshake)) अणु
		wg_cookie_add_mac_to_packet(&packet, माप(packet), peer);
		wg_समयrs_any_authenticated_packet_traversal(peer);
		wg_समयrs_any_authenticated_packet_sent(peer);
		atomic64_set(&peer->last_sent_handshake,
			     kसमय_get_coarse_bootसमय_ns());
		wg_socket_send_buffer_to_peer(peer, &packet, माप(packet),
					      HANDSHAKE_DSCP);
		wg_समयrs_handshake_initiated(peer);
	पूर्ण
पूर्ण

व्योम wg_packet_handshake_send_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wg_peer *peer = container_of(work, काष्ठा wg_peer,
					    transmit_handshake_work);

	wg_packet_send_handshake_initiation(peer);
	wg_peer_put(peer);
पूर्ण

व्योम wg_packet_send_queued_handshake_initiation(काष्ठा wg_peer *peer,
						bool is_retry)
अणु
	अगर (!is_retry)
		peer->समयr_handshake_attempts = 0;

	rcu_पढ़ो_lock_bh();
	/* We check last_sent_handshake here in addition to the actual function
	 * we're queueing up, so that we don't queue things अगर not strictly
	 * necessary:
	 */
	अगर (!wg_birthdate_has_expired(atomic64_पढ़ो(&peer->last_sent_handshake),
				      REKEY_TIMEOUT) ||
			unlikely(READ_ONCE(peer->is_dead)))
		जाओ out;

	wg_peer_get(peer);
	/* Queues up calling packet_send_queued_handshakes(peer), where we करो a
	 * peer_put(peer) after:
	 */
	अगर (!queue_work(peer->device->handshake_send_wq,
			&peer->transmit_handshake_work))
		/* If the work was alपढ़ोy queued, we want to drop the
		 * extra reference:
		 */
		wg_peer_put(peer);
out:
	rcu_पढ़ो_unlock_bh();
पूर्ण

व्योम wg_packet_send_handshake_response(काष्ठा wg_peer *peer)
अणु
	काष्ठा message_handshake_response packet;

	atomic64_set(&peer->last_sent_handshake, kसमय_get_coarse_bootसमय_ns());
	net_dbg_ratelimited("%s: Sending handshake response to peer %llu (%pISpfsc)\n",
			    peer->device->dev->name, peer->पूर्णांकernal_id,
			    &peer->endpoपूर्णांक.addr);

	अगर (wg_noise_handshake_create_response(&packet, &peer->handshake)) अणु
		wg_cookie_add_mac_to_packet(&packet, माप(packet), peer);
		अगर (wg_noise_handshake_begin_session(&peer->handshake,
						     &peer->keypairs)) अणु
			wg_समयrs_session_derived(peer);
			wg_समयrs_any_authenticated_packet_traversal(peer);
			wg_समयrs_any_authenticated_packet_sent(peer);
			atomic64_set(&peer->last_sent_handshake,
				     kसमय_get_coarse_bootसमय_ns());
			wg_socket_send_buffer_to_peer(peer, &packet,
						      माप(packet),
						      HANDSHAKE_DSCP);
		पूर्ण
	पूर्ण
पूर्ण

व्योम wg_packet_send_handshake_cookie(काष्ठा wg_device *wg,
				     काष्ठा sk_buff *initiating_skb,
				     __le32 sender_index)
अणु
	काष्ठा message_handshake_cookie packet;

	net_dbg_skb_ratelimited("%s: Sending cookie response for denied handshake message for %pISpfsc\n",
				wg->dev->name, initiating_skb);
	wg_cookie_message_create(&packet, initiating_skb, sender_index,
				 &wg->cookie_checker);
	wg_socket_send_buffer_as_reply_to_skb(wg, initiating_skb, &packet,
					      माप(packet));
पूर्ण

अटल व्योम keep_key_fresh(काष्ठा wg_peer *peer)
अणु
	काष्ठा noise_keypair *keypair;
	bool send;

	rcu_पढ़ो_lock_bh();
	keypair = rcu_dereference_bh(peer->keypairs.current_keypair);
	send = keypair && READ_ONCE(keypair->sending.is_valid) &&
	       (atomic64_पढ़ो(&keypair->sending_counter) > REKEY_AFTER_MESSAGES ||
		(keypair->i_am_the_initiator &&
		 wg_birthdate_has_expired(keypair->sending.birthdate, REKEY_AFTER_TIME)));
	rcu_पढ़ो_unlock_bh();

	अगर (unlikely(send))
		wg_packet_send_queued_handshake_initiation(peer, false);
पूर्ण

अटल अचिन्हित पूर्णांक calculate_skb_padding(काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक padded_size, last_unit = skb->len;

	अगर (unlikely(!PACKET_CB(skb)->mtu))
		वापस ALIGN(last_unit, MESSAGE_PADDING_MULTIPLE) - last_unit;

	/* We करो this modulo business with the MTU, just in हाल the networking
	 * layer gives us a packet that's bigger than the MTU. In that हाल, we
	 * wouldn't want the final subtraction to overflow in the हाल of the
	 * padded_size being clamped. Fortunately, that's very rarely the हाल,
	 * so we optimize क्रम that not happening.
	 */
	अगर (unlikely(last_unit > PACKET_CB(skb)->mtu))
		last_unit %= PACKET_CB(skb)->mtu;

	padded_size = min(PACKET_CB(skb)->mtu,
			  ALIGN(last_unit, MESSAGE_PADDING_MULTIPLE));
	वापस padded_size - last_unit;
पूर्ण

अटल bool encrypt_packet(काष्ठा sk_buff *skb, काष्ठा noise_keypair *keypair)
अणु
	अचिन्हित पूर्णांक padding_len, plaपूर्णांकext_len, trailer_len;
	काष्ठा scatterlist sg[MAX_SKB_FRAGS + 8];
	काष्ठा message_data *header;
	काष्ठा sk_buff *trailer;
	पूर्णांक num_frags;

	/* Force hash calculation beक्रमe encryption so that flow analysis is
	 * consistent over the inner packet.
	 */
	skb_get_hash(skb);

	/* Calculate lengths. */
	padding_len = calculate_skb_padding(skb);
	trailer_len = padding_len + noise_encrypted_len(0);
	plaपूर्णांकext_len = skb->len + padding_len;

	/* Expand data section to have room क्रम padding and auth tag. */
	num_frags = skb_cow_data(skb, trailer_len, &trailer);
	अगर (unlikely(num_frags < 0 || num_frags > ARRAY_SIZE(sg)))
		वापस false;

	/* Set the padding to zeros, and make sure it and the auth tag are part
	 * of the skb.
	 */
	स_रखो(skb_tail_poपूर्णांकer(trailer), 0, padding_len);

	/* Expand head section to have room क्रम our header and the network
	 * stack's headers.
	 */
	अगर (unlikely(skb_cow_head(skb, DATA_PACKET_HEAD_ROOM) < 0))
		वापस false;

	/* Finalize checksum calculation क्रम the inner packet, अगर required. */
	अगर (unlikely(skb->ip_summed == CHECKSUM_PARTIAL &&
		     skb_checksum_help(skb)))
		वापस false;

	/* Only after checksumming can we safely add on the padding at the end
	 * and the header.
	 */
	skb_set_inner_network_header(skb, 0);
	header = (काष्ठा message_data *)skb_push(skb, माप(*header));
	header->header.type = cpu_to_le32(MESSAGE_DATA);
	header->key_idx = keypair->remote_index;
	header->counter = cpu_to_le64(PACKET_CB(skb)->nonce);
	pskb_put(skb, trailer, trailer_len);

	/* Now we can encrypt the scattergather segments */
	sg_init_table(sg, num_frags);
	अगर (skb_to_sgvec(skb, sg, माप(काष्ठा message_data),
			 noise_encrypted_len(plaपूर्णांकext_len)) <= 0)
		वापस false;
	वापस chacha20poly1305_encrypt_sg_inplace(sg, plaपूर्णांकext_len, शून्य, 0,
						   PACKET_CB(skb)->nonce,
						   keypair->sending.key);
पूर्ण

व्योम wg_packet_send_keepalive(काष्ठा wg_peer *peer)
अणु
	काष्ठा sk_buff *skb;

	अगर (skb_queue_empty(&peer->staged_packet_queue)) अणु
		skb = alloc_skb(DATA_PACKET_HEAD_ROOM + MESSAGE_MINIMUM_LENGTH,
				GFP_ATOMIC);
		अगर (unlikely(!skb))
			वापस;
		skb_reserve(skb, DATA_PACKET_HEAD_ROOM);
		skb->dev = peer->device->dev;
		PACKET_CB(skb)->mtu = skb->dev->mtu;
		skb_queue_tail(&peer->staged_packet_queue, skb);
		net_dbg_ratelimited("%s: Sending keepalive packet to peer %llu (%pISpfsc)\n",
				    peer->device->dev->name, peer->पूर्णांकernal_id,
				    &peer->endpoपूर्णांक.addr);
	पूर्ण

	wg_packet_send_staged_packets(peer);
पूर्ण

अटल व्योम wg_packet_create_data_करोne(काष्ठा wg_peer *peer, काष्ठा sk_buff *first)
अणु
	काष्ठा sk_buff *skb, *next;
	bool is_keepalive, data_sent = false;

	wg_समयrs_any_authenticated_packet_traversal(peer);
	wg_समयrs_any_authenticated_packet_sent(peer);
	skb_list_walk_safe(first, skb, next) अणु
		is_keepalive = skb->len == message_data_len(0);
		अगर (likely(!wg_socket_send_skb_to_peer(peer, skb,
				PACKET_CB(skb)->ds) && !is_keepalive))
			data_sent = true;
	पूर्ण

	अगर (likely(data_sent))
		wg_समयrs_data_sent(peer);

	keep_key_fresh(peer);
पूर्ण

व्योम wg_packet_tx_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wg_peer *peer = container_of(work, काष्ठा wg_peer, transmit_packet_work);
	काष्ठा noise_keypair *keypair;
	क्रमागत packet_state state;
	काष्ठा sk_buff *first;

	जबतक ((first = wg_prev_queue_peek(&peer->tx_queue)) != शून्य &&
	       (state = atomic_पढ़ो_acquire(&PACKET_CB(first)->state)) !=
		       PACKET_STATE_UNCRYPTED) अणु
		wg_prev_queue_drop_peeked(&peer->tx_queue);
		keypair = PACKET_CB(first)->keypair;

		अगर (likely(state == PACKET_STATE_CRYPTED))
			wg_packet_create_data_करोne(peer, first);
		अन्यथा
			kमुक्त_skb_list(first);

		wg_noise_keypair_put(keypair, false);
		wg_peer_put(peer);
		अगर (need_resched())
			cond_resched();
	पूर्ण
पूर्ण

व्योम wg_packet_encrypt_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा crypt_queue *queue = container_of(work, काष्ठा multicore_worker,
						 work)->ptr;
	काष्ठा sk_buff *first, *skb, *next;

	जबतक ((first = ptr_ring_consume_bh(&queue->ring)) != शून्य) अणु
		क्रमागत packet_state state = PACKET_STATE_CRYPTED;

		skb_list_walk_safe(first, skb, next) अणु
			अगर (likely(encrypt_packet(skb,
					PACKET_CB(first)->keypair))) अणु
				wg_reset_packet(skb, true);
			पूर्ण अन्यथा अणु
				state = PACKET_STATE_DEAD;
				अवरोध;
			पूर्ण
		पूर्ण
		wg_queue_enqueue_per_peer_tx(first, state);
		अगर (need_resched())
			cond_resched();
	पूर्ण
पूर्ण

अटल व्योम wg_packet_create_data(काष्ठा wg_peer *peer, काष्ठा sk_buff *first)
अणु
	काष्ठा wg_device *wg = peer->device;
	पूर्णांक ret = -EINVAL;

	rcu_पढ़ो_lock_bh();
	अगर (unlikely(READ_ONCE(peer->is_dead)))
		जाओ err;

	ret = wg_queue_enqueue_per_device_and_peer(&wg->encrypt_queue, &peer->tx_queue, first,
						   wg->packet_crypt_wq, &wg->encrypt_queue.last_cpu);
	अगर (unlikely(ret == -EPIPE))
		wg_queue_enqueue_per_peer_tx(first, PACKET_STATE_DEAD);
err:
	rcu_पढ़ो_unlock_bh();
	अगर (likely(!ret || ret == -EPIPE))
		वापस;
	wg_noise_keypair_put(PACKET_CB(first)->keypair, false);
	wg_peer_put(peer);
	kमुक्त_skb_list(first);
पूर्ण

व्योम wg_packet_purge_staged_packets(काष्ठा wg_peer *peer)
अणु
	spin_lock_bh(&peer->staged_packet_queue.lock);
	peer->device->dev->stats.tx_dropped += peer->staged_packet_queue.qlen;
	__skb_queue_purge(&peer->staged_packet_queue);
	spin_unlock_bh(&peer->staged_packet_queue.lock);
पूर्ण

व्योम wg_packet_send_staged_packets(काष्ठा wg_peer *peer)
अणु
	काष्ठा noise_keypair *keypair;
	काष्ठा sk_buff_head packets;
	काष्ठा sk_buff *skb;

	/* Steal the current queue पूर्णांकo our local one. */
	__skb_queue_head_init(&packets);
	spin_lock_bh(&peer->staged_packet_queue.lock);
	skb_queue_splice_init(&peer->staged_packet_queue, &packets);
	spin_unlock_bh(&peer->staged_packet_queue.lock);
	अगर (unlikely(skb_queue_empty(&packets)))
		वापस;

	/* First we make sure we have a valid reference to a valid key. */
	rcu_पढ़ो_lock_bh();
	keypair = wg_noise_keypair_get(
		rcu_dereference_bh(peer->keypairs.current_keypair));
	rcu_पढ़ो_unlock_bh();
	अगर (unlikely(!keypair))
		जाओ out_nokey;
	अगर (unlikely(!READ_ONCE(keypair->sending.is_valid)))
		जाओ out_nokey;
	अगर (unlikely(wg_birthdate_has_expired(keypair->sending.birthdate,
					      REJECT_AFTER_TIME)))
		जाओ out_invalid;

	/* After we know we have a somewhat valid key, we now try to assign
	 * nonces to all of the packets in the queue. If we can't assign nonces
	 * क्रम all of them, we just consider it a failure and रुको क्रम the next
	 * handshake.
	 */
	skb_queue_walk(&packets, skb) अणु
		/* 0 क्रम no outer TOS: no leak. TODO: at some later poपूर्णांक, we
		 * might consider using flowi->tos as outer instead.
		 */
		PACKET_CB(skb)->ds = ip_tunnel_ecn_encap(0, ip_hdr(skb), skb);
		PACKET_CB(skb)->nonce =
				atomic64_inc_वापस(&keypair->sending_counter) - 1;
		अगर (unlikely(PACKET_CB(skb)->nonce >= REJECT_AFTER_MESSAGES))
			जाओ out_invalid;
	पूर्ण

	packets.prev->next = शून्य;
	wg_peer_get(keypair->entry.peer);
	PACKET_CB(packets.next)->keypair = keypair;
	wg_packet_create_data(peer, packets.next);
	वापस;

out_invalid:
	WRITE_ONCE(keypair->sending.is_valid, false);
out_nokey:
	wg_noise_keypair_put(keypair, false);

	/* We orphan the packets अगर we're रुकोing on a handshake, so that they
	 * करोn't block a socket's pool.
	 */
	skb_queue_walk(&packets, skb)
		skb_orphan(skb);
	/* Then we put them back on the top of the queue. We're not too
	 * concerned about accidentally getting things a little out of order अगर
	 * packets are being added really fast, because this queue is क्रम beक्रमe
	 * packets can even be sent and it's small anyway.
	 */
	spin_lock_bh(&peer->staged_packet_queue.lock);
	skb_queue_splice(&packets, &peer->staged_packet_queue);
	spin_unlock_bh(&peer->staged_packet_queue.lock);

	/* If we're exiting because there's something wrong with the key, it
	 * means we should initiate a new handshake.
	 */
	wg_packet_send_queued_handshake_initiation(peer, false);
पूर्ण
