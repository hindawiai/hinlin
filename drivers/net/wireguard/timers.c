<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#समावेश "timers.h"
#समावेश "device.h"
#समावेश "peer.h"
#समावेश "queueing.h"
#समावेश "socket.h"

/*
 * - Timer क्रम retransmitting the handshake अगर we करोn't hear back after
 * `REKEY_TIMEOUT + jitter` ms.
 *
 * - Timer क्रम sending empty packet अगर we have received a packet but after have
 * not sent one क्रम `KEEPALIVE_TIMEOUT` ms.
 *
 * - Timer क्रम initiating new handshake अगर we have sent a packet but after have
 * not received one (even empty) क्रम `(KEEPALIVE_TIMEOUT + REKEY_TIMEOUT) +
 * jitter` ms.
 *
 * - Timer क्रम zeroing out all ephemeral keys after `(REJECT_AFTER_TIME * 3)` ms
 * अगर no new keys have been received.
 *
 * - Timer क्रम, अगर enabled, sending an empty authenticated packet every user-
 * specअगरied seconds.
 */

अटल अंतरभूत व्योम mod_peer_समयr(काष्ठा wg_peer *peer,
				  काष्ठा समयr_list *समयr,
				  अचिन्हित दीर्घ expires)
अणु
	rcu_पढ़ो_lock_bh();
	अगर (likely(netअगर_running(peer->device->dev) &&
		   !READ_ONCE(peer->is_dead)))
		mod_समयr(समयr, expires);
	rcu_पढ़ो_unlock_bh();
पूर्ण

अटल व्योम wg_expired_retransmit_handshake(काष्ठा समयr_list *समयr)
अणु
	काष्ठा wg_peer *peer = from_समयr(peer, समयr,
					  समयr_retransmit_handshake);

	अगर (peer->समयr_handshake_attempts > MAX_TIMER_HANDSHAKES) अणु
		pr_debug("%s: Handshake for peer %llu (%pISpfsc) did not complete after %d attempts, giving up\n",
			 peer->device->dev->name, peer->पूर्णांकernal_id,
			 &peer->endpoपूर्णांक.addr, MAX_TIMER_HANDSHAKES + 2);

		del_समयr(&peer->समयr_send_keepalive);
		/* We drop all packets without a keypair and करोn't try again,
		 * अगर we try unsuccessfully क्रम too दीर्घ to make a handshake.
		 */
		wg_packet_purge_staged_packets(peer);

		/* We set a समयr क्रम destroying any residue that might be left
		 * of a partial exchange.
		 */
		अगर (!समयr_pending(&peer->समयr_zero_key_material))
			mod_peer_समयr(peer, &peer->समयr_zero_key_material,
				       jअगरfies + REJECT_AFTER_TIME * 3 * HZ);
	पूर्ण अन्यथा अणु
		++peer->समयr_handshake_attempts;
		pr_debug("%s: Handshake for peer %llu (%pISpfsc) did not complete after %d seconds, retrying (try %d)\n",
			 peer->device->dev->name, peer->पूर्णांकernal_id,
			 &peer->endpoपूर्णांक.addr, REKEY_TIMEOUT,
			 peer->समयr_handshake_attempts + 1);

		/* We clear the endpoपूर्णांक address src address, in हाल this is
		 * the cause of trouble.
		 */
		wg_socket_clear_peer_endpoपूर्णांक_src(peer);

		wg_packet_send_queued_handshake_initiation(peer, true);
	पूर्ण
पूर्ण

अटल व्योम wg_expired_send_keepalive(काष्ठा समयr_list *समयr)
अणु
	काष्ठा wg_peer *peer = from_समयr(peer, समयr, समयr_send_keepalive);

	wg_packet_send_keepalive(peer);
	अगर (peer->समयr_need_another_keepalive) अणु
		peer->समयr_need_another_keepalive = false;
		mod_peer_समयr(peer, &peer->समयr_send_keepalive,
			       jअगरfies + KEEPALIVE_TIMEOUT * HZ);
	पूर्ण
पूर्ण

अटल व्योम wg_expired_new_handshake(काष्ठा समयr_list *समयr)
अणु
	काष्ठा wg_peer *peer = from_समयr(peer, समयr, समयr_new_handshake);

	pr_debug("%s: Retrying handshake with peer %llu (%pISpfsc) because we stopped hearing back after %d seconds\n",
		 peer->device->dev->name, peer->पूर्णांकernal_id,
		 &peer->endpoपूर्णांक.addr, KEEPALIVE_TIMEOUT + REKEY_TIMEOUT);
	/* We clear the endpoपूर्णांक address src address, in हाल this is the cause
	 * of trouble.
	 */
	wg_socket_clear_peer_endpoपूर्णांक_src(peer);
	wg_packet_send_queued_handshake_initiation(peer, false);
पूर्ण

अटल व्योम wg_expired_zero_key_material(काष्ठा समयr_list *समयr)
अणु
	काष्ठा wg_peer *peer = from_समयr(peer, समयr, समयr_zero_key_material);

	rcu_पढ़ो_lock_bh();
	अगर (!READ_ONCE(peer->is_dead)) अणु
		wg_peer_get(peer);
		अगर (!queue_work(peer->device->handshake_send_wq,
				&peer->clear_peer_work))
			/* If the work was alपढ़ोy on the queue, we want to drop
			 * the extra reference.
			 */
			wg_peer_put(peer);
	पूर्ण
	rcu_पढ़ो_unlock_bh();
पूर्ण

अटल व्योम wg_queued_expired_zero_key_material(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wg_peer *peer = container_of(work, काष्ठा wg_peer,
					    clear_peer_work);

	pr_debug("%s: Zeroing out all keys for peer %llu (%pISpfsc), since we haven't received a new one in %d seconds\n",
		 peer->device->dev->name, peer->पूर्णांकernal_id,
		 &peer->endpoपूर्णांक.addr, REJECT_AFTER_TIME * 3);
	wg_noise_handshake_clear(&peer->handshake);
	wg_noise_keypairs_clear(&peer->keypairs);
	wg_peer_put(peer);
पूर्ण

अटल व्योम wg_expired_send_persistent_keepalive(काष्ठा समयr_list *समयr)
अणु
	काष्ठा wg_peer *peer = from_समयr(peer, समयr,
					  समयr_persistent_keepalive);

	अगर (likely(peer->persistent_keepalive_पूर्णांकerval))
		wg_packet_send_keepalive(peer);
पूर्ण

/* Should be called after an authenticated data packet is sent. */
व्योम wg_समयrs_data_sent(काष्ठा wg_peer *peer)
अणु
	अगर (!समयr_pending(&peer->समयr_new_handshake))
		mod_peer_समयr(peer, &peer->समयr_new_handshake,
			jअगरfies + (KEEPALIVE_TIMEOUT + REKEY_TIMEOUT) * HZ +
			pअक्रमom_u32_max(REKEY_TIMEOUT_JITTER_MAX_JIFFIES));
पूर्ण

/* Should be called after an authenticated data packet is received. */
व्योम wg_समयrs_data_received(काष्ठा wg_peer *peer)
अणु
	अगर (likely(netअगर_running(peer->device->dev))) अणु
		अगर (!समयr_pending(&peer->समयr_send_keepalive))
			mod_peer_समयr(peer, &peer->समयr_send_keepalive,
				       jअगरfies + KEEPALIVE_TIMEOUT * HZ);
		अन्यथा
			peer->समयr_need_another_keepalive = true;
	पूर्ण
पूर्ण

/* Should be called after any type of authenticated packet is sent, whether
 * keepalive, data, or handshake.
 */
व्योम wg_समयrs_any_authenticated_packet_sent(काष्ठा wg_peer *peer)
अणु
	del_समयr(&peer->समयr_send_keepalive);
पूर्ण

/* Should be called after any type of authenticated packet is received, whether
 * keepalive, data, or handshake.
 */
व्योम wg_समयrs_any_authenticated_packet_received(काष्ठा wg_peer *peer)
अणु
	del_समयr(&peer->समयr_new_handshake);
पूर्ण

/* Should be called after a handshake initiation message is sent. */
व्योम wg_समयrs_handshake_initiated(काष्ठा wg_peer *peer)
अणु
	mod_peer_समयr(peer, &peer->समयr_retransmit_handshake,
		       jअगरfies + REKEY_TIMEOUT * HZ +
		       pअक्रमom_u32_max(REKEY_TIMEOUT_JITTER_MAX_JIFFIES));
पूर्ण

/* Should be called after a handshake response message is received and processed
 * or when getting key confirmation via the first data message.
 */
व्योम wg_समयrs_handshake_complete(काष्ठा wg_peer *peer)
अणु
	del_समयr(&peer->समयr_retransmit_handshake);
	peer->समयr_handshake_attempts = 0;
	peer->sent_lasपंचांगinute_handshake = false;
	kसमय_get_real_ts64(&peer->wallसमय_last_handshake);
पूर्ण

/* Should be called after an ephemeral key is created, which is beक्रमe sending a
 * handshake response or after receiving a handshake response.
 */
व्योम wg_समयrs_session_derived(काष्ठा wg_peer *peer)
अणु
	mod_peer_समयr(peer, &peer->समयr_zero_key_material,
		       jअगरfies + REJECT_AFTER_TIME * 3 * HZ);
पूर्ण

/* Should be called beक्रमe a packet with authentication, whether
 * keepalive, data, or handshakem is sent, or after one is received.
 */
व्योम wg_समयrs_any_authenticated_packet_traversal(काष्ठा wg_peer *peer)
अणु
	अगर (peer->persistent_keepalive_पूर्णांकerval)
		mod_peer_समयr(peer, &peer->समयr_persistent_keepalive,
			jअगरfies + peer->persistent_keepalive_पूर्णांकerval * HZ);
पूर्ण

व्योम wg_समयrs_init(काष्ठा wg_peer *peer)
अणु
	समयr_setup(&peer->समयr_retransmit_handshake,
		    wg_expired_retransmit_handshake, 0);
	समयr_setup(&peer->समयr_send_keepalive, wg_expired_send_keepalive, 0);
	समयr_setup(&peer->समयr_new_handshake, wg_expired_new_handshake, 0);
	समयr_setup(&peer->समयr_zero_key_material,
		    wg_expired_zero_key_material, 0);
	समयr_setup(&peer->समयr_persistent_keepalive,
		    wg_expired_send_persistent_keepalive, 0);
	INIT_WORK(&peer->clear_peer_work, wg_queued_expired_zero_key_material);
	peer->समयr_handshake_attempts = 0;
	peer->sent_lasपंचांगinute_handshake = false;
	peer->समयr_need_another_keepalive = false;
पूर्ण

व्योम wg_समयrs_stop(काष्ठा wg_peer *peer)
अणु
	del_समयr_sync(&peer->समयr_retransmit_handshake);
	del_समयr_sync(&peer->समयr_send_keepalive);
	del_समयr_sync(&peer->समयr_new_handshake);
	del_समयr_sync(&peer->समयr_zero_key_material);
	del_समयr_sync(&peer->समयr_persistent_keepalive);
	flush_work(&peer->clear_peer_work);
पूर्ण
