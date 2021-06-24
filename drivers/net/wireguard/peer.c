<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#समावेश "peer.h"
#समावेश "device.h"
#समावेश "queueing.h"
#समावेश "timers.h"
#समावेश "peerlookup.h"
#समावेश "noise.h"

#समावेश <linux/kref.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/list.h>

अटल काष्ठा kmem_cache *peer_cache;
अटल atomic64_t peer_counter = ATOMIC64_INIT(0);

काष्ठा wg_peer *wg_peer_create(काष्ठा wg_device *wg,
			       स्थिर u8 खुला_key[NOISE_PUBLIC_KEY_LEN],
			       स्थिर u8 preshared_key[NOISE_SYMMETRIC_KEY_LEN])
अणु
	काष्ठा wg_peer *peer;
	पूर्णांक ret = -ENOMEM;

	lockdep_निश्चित_held(&wg->device_update_lock);

	अगर (wg->num_peers >= MAX_PEERS_PER_DEVICE)
		वापस ERR_PTR(ret);

	peer = kmem_cache_zalloc(peer_cache, GFP_KERNEL);
	अगर (unlikely(!peer))
		वापस ERR_PTR(ret);
	अगर (unlikely(dst_cache_init(&peer->endpoपूर्णांक_cache, GFP_KERNEL)))
		जाओ err;

	peer->device = wg;
	wg_noise_handshake_init(&peer->handshake, &wg->अटल_identity,
				खुला_key, preshared_key, peer);
	peer->पूर्णांकernal_id = atomic64_inc_वापस(&peer_counter);
	peer->serial_work_cpu = nr_cpumask_bits;
	wg_cookie_init(&peer->latest_cookie);
	wg_समयrs_init(peer);
	wg_cookie_checker_precompute_peer_keys(peer);
	spin_lock_init(&peer->keypairs.keypair_update_lock);
	INIT_WORK(&peer->transmit_handshake_work, wg_packet_handshake_send_worker);
	INIT_WORK(&peer->transmit_packet_work, wg_packet_tx_worker);
	wg_prev_queue_init(&peer->tx_queue);
	wg_prev_queue_init(&peer->rx_queue);
	rwlock_init(&peer->endpoपूर्णांक_lock);
	kref_init(&peer->refcount);
	skb_queue_head_init(&peer->staged_packet_queue);
	wg_noise_reset_last_sent_handshake(&peer->last_sent_handshake);
	set_bit(NAPI_STATE_NO_BUSY_POLL, &peer->napi.state);
	netअगर_napi_add(wg->dev, &peer->napi, wg_packet_rx_poll,
		       NAPI_POLL_WEIGHT);
	napi_enable(&peer->napi);
	list_add_tail(&peer->peer_list, &wg->peer_list);
	INIT_LIST_HEAD(&peer->allowedips_list);
	wg_pubkey_hashtable_add(wg->peer_hashtable, peer);
	++wg->num_peers;
	pr_debug("%s: Peer %llu created\n", wg->dev->name, peer->पूर्णांकernal_id);
	वापस peer;

err:
	kmem_cache_मुक्त(peer_cache, peer);
	वापस ERR_PTR(ret);
पूर्ण

काष्ठा wg_peer *wg_peer_get_maybe_zero(काष्ठा wg_peer *peer)
अणु
	RCU_LOCKDEP_WARN(!rcu_पढ़ो_lock_bh_held(),
			 "Taking peer reference without holding the RCU read lock");
	अगर (unlikely(!peer || !kref_get_unless_zero(&peer->refcount)))
		वापस शून्य;
	वापस peer;
पूर्ण

अटल व्योम peer_make_dead(काष्ठा wg_peer *peer)
अणु
	/* Remove from configuration-समय lookup काष्ठाures. */
	list_del_init(&peer->peer_list);
	wg_allowedips_हटाओ_by_peer(&peer->device->peer_allowedips, peer,
				     &peer->device->device_update_lock);
	wg_pubkey_hashtable_हटाओ(peer->device->peer_hashtable, peer);

	/* Mark as dead, so that we करोn't allow jumping contexts after. */
	WRITE_ONCE(peer->is_dead, true);

	/* The caller must now synchronize_net() क्रम this to take effect. */
पूर्ण

अटल व्योम peer_हटाओ_after_dead(काष्ठा wg_peer *peer)
अणु
	WARN_ON(!peer->is_dead);

	/* No more keypairs can be created क्रम this peer, since is_dead protects
	 * add_new_keypair, so we can now destroy existing ones.
	 */
	wg_noise_keypairs_clear(&peer->keypairs);

	/* Destroy all ongoing समयrs that were in-flight at the beginning of
	 * this function.
	 */
	wg_समयrs_stop(peer);

	/* The transition between packet encryption/decryption queues isn't
	 * guarded by is_dead, but each reference's lअगरe is strictly bounded by
	 * two generations: once क्रम parallel crypto and once क्रम serial
	 * ingestion, so we can simply flush twice, and be sure that we no
	 * दीर्घer have references inside these queues.
	 */

	/* a) For encrypt/decrypt. */
	flush_workqueue(peer->device->packet_crypt_wq);
	/* b.1) For send (but not receive, since that's napi). */
	flush_workqueue(peer->device->packet_crypt_wq);
	/* b.2.1) For receive (but not send, since that's wq). */
	napi_disable(&peer->napi);
	/* b.2.1) It's now safe to हटाओ the napi काष्ठा, which must be करोne
	 * here from process context.
	 */
	netअगर_napi_del(&peer->napi);

	/* Ensure any workकाष्ठाs we own (like transmit_handshake_work or
	 * clear_peer_work) no दीर्घer are in use.
	 */
	flush_workqueue(peer->device->handshake_send_wq);

	/* After the above flushes, a peer might still be active in a few
	 * dअगरferent contexts: 1) from xmit(), beक्रमe hitting is_dead and
	 * वापसing, 2) from wg_packet_consume_data(), beक्रमe hitting is_dead
	 * and वापसing, 3) from wg_receive_handshake_packet() after a poपूर्णांक
	 * where it has processed an incoming handshake packet, but where
	 * all calls to pass it off to समयrs fails because of is_dead. We won't
	 * have new references in (1) eventually, because we're हटाओd from
	 * allowedips; we won't have new references in (2) eventually, because
	 * wg_index_hashtable_lookup will always वापस शून्य, since we हटाओd
	 * all existing keypairs and no more can be created; we won't have new
	 * references in (3) eventually, because we're हटाओd from the pubkey
	 * hash table, which allows क्रम a maximum of one handshake response,
	 * via the still-uncleared index hashtable entry, but not more than one,
	 * and in wg_cookie_message_consume, the lookup eventually माला_लो a peer
	 * with a refcount of zero, so no new reference is taken.
	 */

	--peer->device->num_peers;
	wg_peer_put(peer);
पूर्ण

/* We have a separate "remove" function make sure that all active places where
 * a peer is currently operating will eventually come to an end and not pass
 * their reference onto another context.
 */
व्योम wg_peer_हटाओ(काष्ठा wg_peer *peer)
अणु
	अगर (unlikely(!peer))
		वापस;
	lockdep_निश्चित_held(&peer->device->device_update_lock);

	peer_make_dead(peer);
	synchronize_net();
	peer_हटाओ_after_dead(peer);
पूर्ण

व्योम wg_peer_हटाओ_all(काष्ठा wg_device *wg)
अणु
	काष्ठा wg_peer *peer, *temp;
	LIST_HEAD(dead_peers);

	lockdep_निश्चित_held(&wg->device_update_lock);

	/* Aव्योम having to traverse inभागidually क्रम each one. */
	wg_allowedips_मुक्त(&wg->peer_allowedips, &wg->device_update_lock);

	list_क्रम_each_entry_safe(peer, temp, &wg->peer_list, peer_list) अणु
		peer_make_dead(peer);
		list_add_tail(&peer->peer_list, &dead_peers);
	पूर्ण
	synchronize_net();
	list_क्रम_each_entry_safe(peer, temp, &dead_peers, peer_list)
		peer_हटाओ_after_dead(peer);
पूर्ण

अटल व्योम rcu_release(काष्ठा rcu_head *rcu)
अणु
	काष्ठा wg_peer *peer = container_of(rcu, काष्ठा wg_peer, rcu);

	dst_cache_destroy(&peer->endpoपूर्णांक_cache);
	WARN_ON(wg_prev_queue_peek(&peer->tx_queue) || wg_prev_queue_peek(&peer->rx_queue));

	/* The final zeroing takes care of clearing any reमुख्यing handshake key
	 * material and other potentially sensitive inक्रमmation.
	 */
	memzero_explicit(peer, माप(*peer));
	kmem_cache_मुक्त(peer_cache, peer);
पूर्ण

अटल व्योम kref_release(काष्ठा kref *refcount)
अणु
	काष्ठा wg_peer *peer = container_of(refcount, काष्ठा wg_peer, refcount);

	pr_debug("%s: Peer %llu (%pISpfsc) destroyed\n",
		 peer->device->dev->name, peer->पूर्णांकernal_id,
		 &peer->endpoपूर्णांक.addr);

	/* Remove ourself from dynamic runसमय lookup काष्ठाures, now that the
	 * last reference is gone.
	 */
	wg_index_hashtable_हटाओ(peer->device->index_hashtable,
				  &peer->handshake.entry);

	/* Remove any lingering packets that didn't have a chance to be
	 * transmitted.
	 */
	wg_packet_purge_staged_packets(peer);

	/* Free the memory used. */
	call_rcu(&peer->rcu, rcu_release);
पूर्ण

व्योम wg_peer_put(काष्ठा wg_peer *peer)
अणु
	अगर (unlikely(!peer))
		वापस;
	kref_put(&peer->refcount, kref_release);
पूर्ण

पूर्णांक __init wg_peer_init(व्योम)
अणु
	peer_cache = KMEM_CACHE(wg_peer, 0);
	वापस peer_cache ? 0 : -ENOMEM;
पूर्ण

व्योम wg_peer_uninit(व्योम)
अणु
	kmem_cache_destroy(peer_cache);
पूर्ण
