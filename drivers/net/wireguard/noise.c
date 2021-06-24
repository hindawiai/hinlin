<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#समावेश "noise.h"
#समावेश "device.h"
#समावेश "peer.h"
#समावेश "messages.h"
#समावेश "queueing.h"
#समावेश "peerlookup.h"

#समावेश <linux/rcupdate.h>
#समावेश <linux/slab.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/highस्मृति.स>
#समावेश <crypto/algapi.h>

/* This implements Noise_IKpsk2:
 *
 * <- s
 * ******
 * -> e, es, s, ss, अणुtपूर्ण
 * <- e, ee, se, psk, अणुपूर्ण
 */

अटल स्थिर u8 handshake_name[37] = "Noise_IKpsk2_25519_ChaChaPoly_BLAKE2s";
अटल स्थिर u8 identअगरier_name[34] = "WireGuard v1 zx2c4 Jason@zx2c4.com";
अटल u8 handshake_init_hash[NOISE_HASH_LEN] __ro_after_init;
अटल u8 handshake_init_chaining_key[NOISE_HASH_LEN] __ro_after_init;
अटल atomic64_t keypair_counter = ATOMIC64_INIT(0);

व्योम __init wg_noise_init(व्योम)
अणु
	काष्ठा blake2s_state blake;

	blake2s(handshake_init_chaining_key, handshake_name, शून्य,
		NOISE_HASH_LEN, माप(handshake_name), 0);
	blake2s_init(&blake, NOISE_HASH_LEN);
	blake2s_update(&blake, handshake_init_chaining_key, NOISE_HASH_LEN);
	blake2s_update(&blake, identअगरier_name, माप(identअगरier_name));
	blake2s_final(&blake, handshake_init_hash);
पूर्ण

/* Must hold peer->handshake.अटल_identity->lock */
व्योम wg_noise_precompute_अटल_अटल(काष्ठा wg_peer *peer)
अणु
	करोwn_ग_लिखो(&peer->handshake.lock);
	अगर (!peer->handshake.अटल_identity->has_identity ||
	    !curve25519(peer->handshake.precomputed_अटल_अटल,
			peer->handshake.अटल_identity->अटल_निजी,
			peer->handshake.remote_अटल))
		स_रखो(peer->handshake.precomputed_अटल_अटल, 0,
		       NOISE_PUBLIC_KEY_LEN);
	up_ग_लिखो(&peer->handshake.lock);
पूर्ण

व्योम wg_noise_handshake_init(काष्ठा noise_handshake *handshake,
			     काष्ठा noise_अटल_identity *अटल_identity,
			     स्थिर u8 peer_खुला_key[NOISE_PUBLIC_KEY_LEN],
			     स्थिर u8 peer_preshared_key[NOISE_SYMMETRIC_KEY_LEN],
			     काष्ठा wg_peer *peer)
अणु
	स_रखो(handshake, 0, माप(*handshake));
	init_rwsem(&handshake->lock);
	handshake->entry.type = INDEX_HASHTABLE_HANDSHAKE;
	handshake->entry.peer = peer;
	स_नकल(handshake->remote_अटल, peer_खुला_key, NOISE_PUBLIC_KEY_LEN);
	अगर (peer_preshared_key)
		स_नकल(handshake->preshared_key, peer_preshared_key,
		       NOISE_SYMMETRIC_KEY_LEN);
	handshake->अटल_identity = अटल_identity;
	handshake->state = HANDSHAKE_ZEROED;
	wg_noise_precompute_अटल_अटल(peer);
पूर्ण

अटल व्योम handshake_zero(काष्ठा noise_handshake *handshake)
अणु
	स_रखो(&handshake->ephemeral_निजी, 0, NOISE_PUBLIC_KEY_LEN);
	स_रखो(&handshake->remote_ephemeral, 0, NOISE_PUBLIC_KEY_LEN);
	स_रखो(&handshake->hash, 0, NOISE_HASH_LEN);
	स_रखो(&handshake->chaining_key, 0, NOISE_HASH_LEN);
	handshake->remote_index = 0;
	handshake->state = HANDSHAKE_ZEROED;
पूर्ण

व्योम wg_noise_handshake_clear(काष्ठा noise_handshake *handshake)
अणु
	करोwn_ग_लिखो(&handshake->lock);
	wg_index_hashtable_हटाओ(
			handshake->entry.peer->device->index_hashtable,
			&handshake->entry);
	handshake_zero(handshake);
	up_ग_लिखो(&handshake->lock);
पूर्ण

अटल काष्ठा noise_keypair *keypair_create(काष्ठा wg_peer *peer)
अणु
	काष्ठा noise_keypair *keypair = kzalloc(माप(*keypair), GFP_KERNEL);

	अगर (unlikely(!keypair))
		वापस शून्य;
	spin_lock_init(&keypair->receiving_counter.lock);
	keypair->पूर्णांकernal_id = atomic64_inc_वापस(&keypair_counter);
	keypair->entry.type = INDEX_HASHTABLE_KEYPAIR;
	keypair->entry.peer = peer;
	kref_init(&keypair->refcount);
	वापस keypair;
पूर्ण

अटल व्योम keypair_मुक्त_rcu(काष्ठा rcu_head *rcu)
अणु
	kमुक्त_sensitive(container_of(rcu, काष्ठा noise_keypair, rcu));
पूर्ण

अटल व्योम keypair_मुक्त_kref(काष्ठा kref *kref)
अणु
	काष्ठा noise_keypair *keypair =
		container_of(kref, काष्ठा noise_keypair, refcount);

	net_dbg_ratelimited("%s: Keypair %llu destroyed for peer %llu\n",
			    keypair->entry.peer->device->dev->name,
			    keypair->पूर्णांकernal_id,
			    keypair->entry.peer->पूर्णांकernal_id);
	wg_index_hashtable_हटाओ(keypair->entry.peer->device->index_hashtable,
				  &keypair->entry);
	call_rcu(&keypair->rcu, keypair_मुक्त_rcu);
पूर्ण

व्योम wg_noise_keypair_put(काष्ठा noise_keypair *keypair, bool unreference_now)
अणु
	अगर (unlikely(!keypair))
		वापस;
	अगर (unlikely(unreference_now))
		wg_index_hashtable_हटाओ(
			keypair->entry.peer->device->index_hashtable,
			&keypair->entry);
	kref_put(&keypair->refcount, keypair_मुक्त_kref);
पूर्ण

काष्ठा noise_keypair *wg_noise_keypair_get(काष्ठा noise_keypair *keypair)
अणु
	RCU_LOCKDEP_WARN(!rcu_पढ़ो_lock_bh_held(),
		"Taking noise keypair reference without holding the RCU BH read lock");
	अगर (unlikely(!keypair || !kref_get_unless_zero(&keypair->refcount)))
		वापस शून्य;
	वापस keypair;
पूर्ण

व्योम wg_noise_keypairs_clear(काष्ठा noise_keypairs *keypairs)
अणु
	काष्ठा noise_keypair *old;

	spin_lock_bh(&keypairs->keypair_update_lock);

	/* We zero the next_keypair beक्रमe zeroing the others, so that
	 * wg_noise_received_with_keypair वापसs early beक्रमe subsequent ones
	 * are zeroed.
	 */
	old = rcu_dereference_रक्षित(keypairs->next_keypair,
		lockdep_is_held(&keypairs->keypair_update_lock));
	RCU_INIT_POINTER(keypairs->next_keypair, शून्य);
	wg_noise_keypair_put(old, true);

	old = rcu_dereference_रक्षित(keypairs->previous_keypair,
		lockdep_is_held(&keypairs->keypair_update_lock));
	RCU_INIT_POINTER(keypairs->previous_keypair, शून्य);
	wg_noise_keypair_put(old, true);

	old = rcu_dereference_रक्षित(keypairs->current_keypair,
		lockdep_is_held(&keypairs->keypair_update_lock));
	RCU_INIT_POINTER(keypairs->current_keypair, शून्य);
	wg_noise_keypair_put(old, true);

	spin_unlock_bh(&keypairs->keypair_update_lock);
पूर्ण

व्योम wg_noise_expire_current_peer_keypairs(काष्ठा wg_peer *peer)
अणु
	काष्ठा noise_keypair *keypair;

	wg_noise_handshake_clear(&peer->handshake);
	wg_noise_reset_last_sent_handshake(&peer->last_sent_handshake);

	spin_lock_bh(&peer->keypairs.keypair_update_lock);
	keypair = rcu_dereference_रक्षित(peer->keypairs.next_keypair,
			lockdep_is_held(&peer->keypairs.keypair_update_lock));
	अगर (keypair)
		keypair->sending.is_valid = false;
	keypair = rcu_dereference_रक्षित(peer->keypairs.current_keypair,
			lockdep_is_held(&peer->keypairs.keypair_update_lock));
	अगर (keypair)
		keypair->sending.is_valid = false;
	spin_unlock_bh(&peer->keypairs.keypair_update_lock);
पूर्ण

अटल व्योम add_new_keypair(काष्ठा noise_keypairs *keypairs,
			    काष्ठा noise_keypair *new_keypair)
अणु
	काष्ठा noise_keypair *previous_keypair, *next_keypair, *current_keypair;

	spin_lock_bh(&keypairs->keypair_update_lock);
	previous_keypair = rcu_dereference_रक्षित(keypairs->previous_keypair,
		lockdep_is_held(&keypairs->keypair_update_lock));
	next_keypair = rcu_dereference_रक्षित(keypairs->next_keypair,
		lockdep_is_held(&keypairs->keypair_update_lock));
	current_keypair = rcu_dereference_रक्षित(keypairs->current_keypair,
		lockdep_is_held(&keypairs->keypair_update_lock));
	अगर (new_keypair->i_am_the_initiator) अणु
		/* If we're the initiator, it means we've sent a handshake, and
		 * received a confirmation response, which means this new
		 * keypair can now be used.
		 */
		अगर (next_keypair) अणु
			/* If there alपढ़ोy was a next keypair pending, we
			 * demote it to be the previous keypair, and मुक्त the
			 * existing current. Note that this means KCI can result
			 * in this transition. It would perhaps be more sound to
			 * always just get rid of the unused next keypair
			 * instead of putting it in the previous slot, but this
			 * might be a bit less robust. Something to think about
			 * क्रम the future.
			 */
			RCU_INIT_POINTER(keypairs->next_keypair, शून्य);
			rcu_assign_poपूर्णांकer(keypairs->previous_keypair,
					   next_keypair);
			wg_noise_keypair_put(current_keypair, true);
		पूर्ण अन्यथा /* If there wasn't an existing next keypair, we replace
			* the previous with the current one.
			*/
			rcu_assign_poपूर्णांकer(keypairs->previous_keypair,
					   current_keypair);
		/* At this poपूर्णांक we can get rid of the old previous keypair, and
		 * set up the new keypair.
		 */
		wg_noise_keypair_put(previous_keypair, true);
		rcu_assign_poपूर्णांकer(keypairs->current_keypair, new_keypair);
	पूर्ण अन्यथा अणु
		/* If we're the responder, it means we can't use the new keypair
		 * until we receive confirmation via the first data packet, so
		 * we get rid of the existing previous one, the possibly
		 * existing next one, and slide in the new next one.
		 */
		rcu_assign_poपूर्णांकer(keypairs->next_keypair, new_keypair);
		wg_noise_keypair_put(next_keypair, true);
		RCU_INIT_POINTER(keypairs->previous_keypair, शून्य);
		wg_noise_keypair_put(previous_keypair, true);
	पूर्ण
	spin_unlock_bh(&keypairs->keypair_update_lock);
पूर्ण

bool wg_noise_received_with_keypair(काष्ठा noise_keypairs *keypairs,
				    काष्ठा noise_keypair *received_keypair)
अणु
	काष्ठा noise_keypair *old_keypair;
	bool key_is_new;

	/* We first check without taking the spinlock. */
	key_is_new = received_keypair ==
		     rcu_access_poपूर्णांकer(keypairs->next_keypair);
	अगर (likely(!key_is_new))
		वापस false;

	spin_lock_bh(&keypairs->keypair_update_lock);
	/* After locking, we द्विगुन check that things didn't change from
	 * beneath us.
	 */
	अगर (unlikely(received_keypair !=
		    rcu_dereference_रक्षित(keypairs->next_keypair,
			    lockdep_is_held(&keypairs->keypair_update_lock)))) अणु
		spin_unlock_bh(&keypairs->keypair_update_lock);
		वापस false;
	पूर्ण

	/* When we've finally received the confirmation, we slide the next
	 * पूर्णांकo the current, the current पूर्णांकo the previous, and get rid of
	 * the old previous.
	 */
	old_keypair = rcu_dereference_रक्षित(keypairs->previous_keypair,
		lockdep_is_held(&keypairs->keypair_update_lock));
	rcu_assign_poपूर्णांकer(keypairs->previous_keypair,
		rcu_dereference_रक्षित(keypairs->current_keypair,
			lockdep_is_held(&keypairs->keypair_update_lock)));
	wg_noise_keypair_put(old_keypair, true);
	rcu_assign_poपूर्णांकer(keypairs->current_keypair, received_keypair);
	RCU_INIT_POINTER(keypairs->next_keypair, शून्य);

	spin_unlock_bh(&keypairs->keypair_update_lock);
	वापस true;
पूर्ण

/* Must hold अटल_identity->lock */
व्योम wg_noise_set_अटल_identity_निजी_key(
	काष्ठा noise_अटल_identity *अटल_identity,
	स्थिर u8 निजी_key[NOISE_PUBLIC_KEY_LEN])
अणु
	स_नकल(अटल_identity->अटल_निजी, निजी_key,
	       NOISE_PUBLIC_KEY_LEN);
	curve25519_clamp_secret(अटल_identity->अटल_निजी);
	अटल_identity->has_identity = curve25519_generate_खुला(
		अटल_identity->अटल_खुला, निजी_key);
पूर्ण

/* This is Hugo Krawczyk's HKDF:
 *  - https://eprपूर्णांक.iacr.org/2010/264.pdf
 *  - https://tools.ietf.org/hपंचांगl/rfc5869
 */
अटल व्योम kdf(u8 *first_dst, u8 *second_dst, u8 *third_dst, स्थिर u8 *data,
		माप_प्रकार first_len, माप_प्रकार second_len, माप_प्रकार third_len,
		माप_प्रकार data_len, स्थिर u8 chaining_key[NOISE_HASH_LEN])
अणु
	u8 output[BLAKE2S_HASH_SIZE + 1];
	u8 secret[BLAKE2S_HASH_SIZE];

	WARN_ON(IS_ENABLED(DEBUG) &&
		(first_len > BLAKE2S_HASH_SIZE ||
		 second_len > BLAKE2S_HASH_SIZE ||
		 third_len > BLAKE2S_HASH_SIZE ||
		 ((second_len || second_dst || third_len || third_dst) &&
		  (!first_len || !first_dst)) ||
		 ((third_len || third_dst) && (!second_len || !second_dst))));

	/* Extract entropy from data पूर्णांकo secret */
	blake2s256_hmac(secret, data, chaining_key, data_len, NOISE_HASH_LEN);

	अगर (!first_dst || !first_len)
		जाओ out;

	/* Expand first key: key = secret, data = 0x1 */
	output[0] = 1;
	blake2s256_hmac(output, output, secret, 1, BLAKE2S_HASH_SIZE);
	स_नकल(first_dst, output, first_len);

	अगर (!second_dst || !second_len)
		जाओ out;

	/* Expand second key: key = secret, data = first-key || 0x2 */
	output[BLAKE2S_HASH_SIZE] = 2;
	blake2s256_hmac(output, output, secret, BLAKE2S_HASH_SIZE + 1,
			BLAKE2S_HASH_SIZE);
	स_नकल(second_dst, output, second_len);

	अगर (!third_dst || !third_len)
		जाओ out;

	/* Expand third key: key = secret, data = second-key || 0x3 */
	output[BLAKE2S_HASH_SIZE] = 3;
	blake2s256_hmac(output, output, secret, BLAKE2S_HASH_SIZE + 1,
			BLAKE2S_HASH_SIZE);
	स_नकल(third_dst, output, third_len);

out:
	/* Clear sensitive data from stack */
	memzero_explicit(secret, BLAKE2S_HASH_SIZE);
	memzero_explicit(output, BLAKE2S_HASH_SIZE + 1);
पूर्ण

अटल व्योम derive_keys(काष्ठा noise_symmetric_key *first_dst,
			काष्ठा noise_symmetric_key *second_dst,
			स्थिर u8 chaining_key[NOISE_HASH_LEN])
अणु
	u64 birthdate = kसमय_get_coarse_bootसमय_ns();
	kdf(first_dst->key, second_dst->key, शून्य, शून्य,
	    NOISE_SYMMETRIC_KEY_LEN, NOISE_SYMMETRIC_KEY_LEN, 0, 0,
	    chaining_key);
	first_dst->birthdate = second_dst->birthdate = birthdate;
	first_dst->is_valid = second_dst->is_valid = true;
पूर्ण

अटल bool __must_check mix_dh(u8 chaining_key[NOISE_HASH_LEN],
				u8 key[NOISE_SYMMETRIC_KEY_LEN],
				स्थिर u8 निजी[NOISE_PUBLIC_KEY_LEN],
				स्थिर u8 खुला[NOISE_PUBLIC_KEY_LEN])
अणु
	u8 dh_calculation[NOISE_PUBLIC_KEY_LEN];

	अगर (unlikely(!curve25519(dh_calculation, निजी, खुला)))
		वापस false;
	kdf(chaining_key, key, शून्य, dh_calculation, NOISE_HASH_LEN,
	    NOISE_SYMMETRIC_KEY_LEN, 0, NOISE_PUBLIC_KEY_LEN, chaining_key);
	memzero_explicit(dh_calculation, NOISE_PUBLIC_KEY_LEN);
	वापस true;
पूर्ण

अटल bool __must_check mix_precomputed_dh(u8 chaining_key[NOISE_HASH_LEN],
					    u8 key[NOISE_SYMMETRIC_KEY_LEN],
					    स्थिर u8 precomputed[NOISE_PUBLIC_KEY_LEN])
अणु
	अटल u8 zero_poपूर्णांक[NOISE_PUBLIC_KEY_LEN];
	अगर (unlikely(!crypto_memneq(precomputed, zero_poपूर्णांक, NOISE_PUBLIC_KEY_LEN)))
		वापस false;
	kdf(chaining_key, key, शून्य, precomputed, NOISE_HASH_LEN,
	    NOISE_SYMMETRIC_KEY_LEN, 0, NOISE_PUBLIC_KEY_LEN,
	    chaining_key);
	वापस true;
पूर्ण

अटल व्योम mix_hash(u8 hash[NOISE_HASH_LEN], स्थिर u8 *src, माप_प्रकार src_len)
अणु
	काष्ठा blake2s_state blake;

	blake2s_init(&blake, NOISE_HASH_LEN);
	blake2s_update(&blake, hash, NOISE_HASH_LEN);
	blake2s_update(&blake, src, src_len);
	blake2s_final(&blake, hash);
पूर्ण

अटल व्योम mix_psk(u8 chaining_key[NOISE_HASH_LEN], u8 hash[NOISE_HASH_LEN],
		    u8 key[NOISE_SYMMETRIC_KEY_LEN],
		    स्थिर u8 psk[NOISE_SYMMETRIC_KEY_LEN])
अणु
	u8 temp_hash[NOISE_HASH_LEN];

	kdf(chaining_key, temp_hash, key, psk, NOISE_HASH_LEN, NOISE_HASH_LEN,
	    NOISE_SYMMETRIC_KEY_LEN, NOISE_SYMMETRIC_KEY_LEN, chaining_key);
	mix_hash(hash, temp_hash, NOISE_HASH_LEN);
	memzero_explicit(temp_hash, NOISE_HASH_LEN);
पूर्ण

अटल व्योम handshake_init(u8 chaining_key[NOISE_HASH_LEN],
			   u8 hash[NOISE_HASH_LEN],
			   स्थिर u8 remote_अटल[NOISE_PUBLIC_KEY_LEN])
अणु
	स_नकल(hash, handshake_init_hash, NOISE_HASH_LEN);
	स_नकल(chaining_key, handshake_init_chaining_key, NOISE_HASH_LEN);
	mix_hash(hash, remote_अटल, NOISE_PUBLIC_KEY_LEN);
पूर्ण

अटल व्योम message_encrypt(u8 *dst_ciphertext, स्थिर u8 *src_plaपूर्णांकext,
			    माप_प्रकार src_len, u8 key[NOISE_SYMMETRIC_KEY_LEN],
			    u8 hash[NOISE_HASH_LEN])
अणु
	chacha20poly1305_encrypt(dst_ciphertext, src_plaपूर्णांकext, src_len, hash,
				 NOISE_HASH_LEN,
				 0 /* Always zero क्रम Noise_IK */, key);
	mix_hash(hash, dst_ciphertext, noise_encrypted_len(src_len));
पूर्ण

अटल bool message_decrypt(u8 *dst_plaपूर्णांकext, स्थिर u8 *src_ciphertext,
			    माप_प्रकार src_len, u8 key[NOISE_SYMMETRIC_KEY_LEN],
			    u8 hash[NOISE_HASH_LEN])
अणु
	अगर (!chacha20poly1305_decrypt(dst_plaपूर्णांकext, src_ciphertext, src_len,
				      hash, NOISE_HASH_LEN,
				      0 /* Always zero क्रम Noise_IK */, key))
		वापस false;
	mix_hash(hash, src_ciphertext, src_len);
	वापस true;
पूर्ण

अटल व्योम message_ephemeral(u8 ephemeral_dst[NOISE_PUBLIC_KEY_LEN],
			      स्थिर u8 ephemeral_src[NOISE_PUBLIC_KEY_LEN],
			      u8 chaining_key[NOISE_HASH_LEN],
			      u8 hash[NOISE_HASH_LEN])
अणु
	अगर (ephemeral_dst != ephemeral_src)
		स_नकल(ephemeral_dst, ephemeral_src, NOISE_PUBLIC_KEY_LEN);
	mix_hash(hash, ephemeral_src, NOISE_PUBLIC_KEY_LEN);
	kdf(chaining_key, शून्य, शून्य, ephemeral_src, NOISE_HASH_LEN, 0, 0,
	    NOISE_PUBLIC_KEY_LEN, chaining_key);
पूर्ण

अटल व्योम tai64n_now(u8 output[NOISE_TIMESTAMP_LEN])
अणु
	काष्ठा बारpec64 now;

	kसमय_get_real_ts64(&now);

	/* In order to prevent some sort of infoleak from precise समयrs, we
	 * round करोwn the nanoseconds part to the बंदst rounded-करोwn घातer of
	 * two to the maximum initiations per second allowed anyway by the
	 * implementation.
	 */
	now.tv_nsec = ALIGN_DOWN(now.tv_nsec,
		roundकरोwn_घात_of_two(NSEC_PER_SEC / INITIATIONS_PER_SECOND));

	/* https://cr.yp.to/libtai/tai64.hपंचांगl */
	*(__be64 *)output = cpu_to_be64(0x400000000000000aULL + now.tv_sec);
	*(__be32 *)(output + माप(__be64)) = cpu_to_be32(now.tv_nsec);
पूर्ण

bool
wg_noise_handshake_create_initiation(काष्ठा message_handshake_initiation *dst,
				     काष्ठा noise_handshake *handshake)
अणु
	u8 बारtamp[NOISE_TIMESTAMP_LEN];
	u8 key[NOISE_SYMMETRIC_KEY_LEN];
	bool ret = false;

	/* We need to रुको क्रम crng _beक्रमe_ taking any locks, since
	 * curve25519_generate_secret uses get_अक्रमom_bytes_रुको.
	 */
	रुको_क्रम_अक्रमom_bytes();

	करोwn_पढ़ो(&handshake->अटल_identity->lock);
	करोwn_ग_लिखो(&handshake->lock);

	अगर (unlikely(!handshake->अटल_identity->has_identity))
		जाओ out;

	dst->header.type = cpu_to_le32(MESSAGE_HANDSHAKE_INITIATION);

	handshake_init(handshake->chaining_key, handshake->hash,
		       handshake->remote_अटल);

	/* e */
	curve25519_generate_secret(handshake->ephemeral_निजी);
	अगर (!curve25519_generate_खुला(dst->unencrypted_ephemeral,
					handshake->ephemeral_निजी))
		जाओ out;
	message_ephemeral(dst->unencrypted_ephemeral,
			  dst->unencrypted_ephemeral, handshake->chaining_key,
			  handshake->hash);

	/* es */
	अगर (!mix_dh(handshake->chaining_key, key, handshake->ephemeral_निजी,
		    handshake->remote_अटल))
		जाओ out;

	/* s */
	message_encrypt(dst->encrypted_अटल,
			handshake->अटल_identity->अटल_खुला,
			NOISE_PUBLIC_KEY_LEN, key, handshake->hash);

	/* ss */
	अगर (!mix_precomputed_dh(handshake->chaining_key, key,
				handshake->precomputed_अटल_अटल))
		जाओ out;

	/* अणुtपूर्ण */
	tai64n_now(बारtamp);
	message_encrypt(dst->encrypted_बारtamp, बारtamp,
			NOISE_TIMESTAMP_LEN, key, handshake->hash);

	dst->sender_index = wg_index_hashtable_insert(
		handshake->entry.peer->device->index_hashtable,
		&handshake->entry);

	handshake->state = HANDSHAKE_CREATED_INITIATION;
	ret = true;

out:
	up_ग_लिखो(&handshake->lock);
	up_पढ़ो(&handshake->अटल_identity->lock);
	memzero_explicit(key, NOISE_SYMMETRIC_KEY_LEN);
	वापस ret;
पूर्ण

काष्ठा wg_peer *
wg_noise_handshake_consume_initiation(काष्ठा message_handshake_initiation *src,
				      काष्ठा wg_device *wg)
अणु
	काष्ठा wg_peer *peer = शून्य, *ret_peer = शून्य;
	काष्ठा noise_handshake *handshake;
	bool replay_attack, flood_attack;
	u8 key[NOISE_SYMMETRIC_KEY_LEN];
	u8 chaining_key[NOISE_HASH_LEN];
	u8 hash[NOISE_HASH_LEN];
	u8 s[NOISE_PUBLIC_KEY_LEN];
	u8 e[NOISE_PUBLIC_KEY_LEN];
	u8 t[NOISE_TIMESTAMP_LEN];
	u64 initiation_consumption;

	करोwn_पढ़ो(&wg->अटल_identity.lock);
	अगर (unlikely(!wg->अटल_identity.has_identity))
		जाओ out;

	handshake_init(chaining_key, hash, wg->अटल_identity.अटल_खुला);

	/* e */
	message_ephemeral(e, src->unencrypted_ephemeral, chaining_key, hash);

	/* es */
	अगर (!mix_dh(chaining_key, key, wg->अटल_identity.अटल_निजी, e))
		जाओ out;

	/* s */
	अगर (!message_decrypt(s, src->encrypted_अटल,
			     माप(src->encrypted_अटल), key, hash))
		जाओ out;

	/* Lookup which peer we're actually talking to */
	peer = wg_pubkey_hashtable_lookup(wg->peer_hashtable, s);
	अगर (!peer)
		जाओ out;
	handshake = &peer->handshake;

	/* ss */
	अगर (!mix_precomputed_dh(chaining_key, key,
				handshake->precomputed_अटल_अटल))
	    जाओ out;

	/* अणुtपूर्ण */
	अगर (!message_decrypt(t, src->encrypted_बारtamp,
			     माप(src->encrypted_बारtamp), key, hash))
		जाओ out;

	करोwn_पढ़ो(&handshake->lock);
	replay_attack = स_भेद(t, handshake->latest_बारtamp,
			       NOISE_TIMESTAMP_LEN) <= 0;
	flood_attack = (s64)handshake->last_initiation_consumption +
			       NSEC_PER_SEC / INITIATIONS_PER_SECOND >
		       (s64)kसमय_get_coarse_bootसमय_ns();
	up_पढ़ो(&handshake->lock);
	अगर (replay_attack || flood_attack)
		जाओ out;

	/* Success! Copy everything to peer */
	करोwn_ग_लिखो(&handshake->lock);
	स_नकल(handshake->remote_ephemeral, e, NOISE_PUBLIC_KEY_LEN);
	अगर (स_भेद(t, handshake->latest_बारtamp, NOISE_TIMESTAMP_LEN) > 0)
		स_नकल(handshake->latest_बारtamp, t, NOISE_TIMESTAMP_LEN);
	स_नकल(handshake->hash, hash, NOISE_HASH_LEN);
	स_नकल(handshake->chaining_key, chaining_key, NOISE_HASH_LEN);
	handshake->remote_index = src->sender_index;
	initiation_consumption = kसमय_get_coarse_bootसमय_ns();
	अगर ((s64)(handshake->last_initiation_consumption - initiation_consumption) < 0)
		handshake->last_initiation_consumption = initiation_consumption;
	handshake->state = HANDSHAKE_CONSUMED_INITIATION;
	up_ग_लिखो(&handshake->lock);
	ret_peer = peer;

out:
	memzero_explicit(key, NOISE_SYMMETRIC_KEY_LEN);
	memzero_explicit(hash, NOISE_HASH_LEN);
	memzero_explicit(chaining_key, NOISE_HASH_LEN);
	up_पढ़ो(&wg->अटल_identity.lock);
	अगर (!ret_peer)
		wg_peer_put(peer);
	वापस ret_peer;
पूर्ण

bool wg_noise_handshake_create_response(काष्ठा message_handshake_response *dst,
					काष्ठा noise_handshake *handshake)
अणु
	u8 key[NOISE_SYMMETRIC_KEY_LEN];
	bool ret = false;

	/* We need to रुको क्रम crng _beक्रमe_ taking any locks, since
	 * curve25519_generate_secret uses get_अक्रमom_bytes_रुको.
	 */
	रुको_क्रम_अक्रमom_bytes();

	करोwn_पढ़ो(&handshake->अटल_identity->lock);
	करोwn_ग_लिखो(&handshake->lock);

	अगर (handshake->state != HANDSHAKE_CONSUMED_INITIATION)
		जाओ out;

	dst->header.type = cpu_to_le32(MESSAGE_HANDSHAKE_RESPONSE);
	dst->receiver_index = handshake->remote_index;

	/* e */
	curve25519_generate_secret(handshake->ephemeral_निजी);
	अगर (!curve25519_generate_खुला(dst->unencrypted_ephemeral,
					handshake->ephemeral_निजी))
		जाओ out;
	message_ephemeral(dst->unencrypted_ephemeral,
			  dst->unencrypted_ephemeral, handshake->chaining_key,
			  handshake->hash);

	/* ee */
	अगर (!mix_dh(handshake->chaining_key, शून्य, handshake->ephemeral_निजी,
		    handshake->remote_ephemeral))
		जाओ out;

	/* se */
	अगर (!mix_dh(handshake->chaining_key, शून्य, handshake->ephemeral_निजी,
		    handshake->remote_अटल))
		जाओ out;

	/* psk */
	mix_psk(handshake->chaining_key, handshake->hash, key,
		handshake->preshared_key);

	/* अणुपूर्ण */
	message_encrypt(dst->encrypted_nothing, शून्य, 0, key, handshake->hash);

	dst->sender_index = wg_index_hashtable_insert(
		handshake->entry.peer->device->index_hashtable,
		&handshake->entry);

	handshake->state = HANDSHAKE_CREATED_RESPONSE;
	ret = true;

out:
	up_ग_लिखो(&handshake->lock);
	up_पढ़ो(&handshake->अटल_identity->lock);
	memzero_explicit(key, NOISE_SYMMETRIC_KEY_LEN);
	वापस ret;
पूर्ण

काष्ठा wg_peer *
wg_noise_handshake_consume_response(काष्ठा message_handshake_response *src,
				    काष्ठा wg_device *wg)
अणु
	क्रमागत noise_handshake_state state = HANDSHAKE_ZEROED;
	काष्ठा wg_peer *peer = शून्य, *ret_peer = शून्य;
	काष्ठा noise_handshake *handshake;
	u8 key[NOISE_SYMMETRIC_KEY_LEN];
	u8 hash[NOISE_HASH_LEN];
	u8 chaining_key[NOISE_HASH_LEN];
	u8 e[NOISE_PUBLIC_KEY_LEN];
	u8 ephemeral_निजी[NOISE_PUBLIC_KEY_LEN];
	u8 अटल_निजी[NOISE_PUBLIC_KEY_LEN];
	u8 preshared_key[NOISE_SYMMETRIC_KEY_LEN];

	करोwn_पढ़ो(&wg->अटल_identity.lock);

	अगर (unlikely(!wg->अटल_identity.has_identity))
		जाओ out;

	handshake = (काष्ठा noise_handshake *)wg_index_hashtable_lookup(
		wg->index_hashtable, INDEX_HASHTABLE_HANDSHAKE,
		src->receiver_index, &peer);
	अगर (unlikely(!handshake))
		जाओ out;

	करोwn_पढ़ो(&handshake->lock);
	state = handshake->state;
	स_नकल(hash, handshake->hash, NOISE_HASH_LEN);
	स_नकल(chaining_key, handshake->chaining_key, NOISE_HASH_LEN);
	स_नकल(ephemeral_निजी, handshake->ephemeral_निजी,
	       NOISE_PUBLIC_KEY_LEN);
	स_नकल(preshared_key, handshake->preshared_key,
	       NOISE_SYMMETRIC_KEY_LEN);
	up_पढ़ो(&handshake->lock);

	अगर (state != HANDSHAKE_CREATED_INITIATION)
		जाओ fail;

	/* e */
	message_ephemeral(e, src->unencrypted_ephemeral, chaining_key, hash);

	/* ee */
	अगर (!mix_dh(chaining_key, शून्य, ephemeral_निजी, e))
		जाओ fail;

	/* se */
	अगर (!mix_dh(chaining_key, शून्य, wg->अटल_identity.अटल_निजी, e))
		जाओ fail;

	/* psk */
	mix_psk(chaining_key, hash, key, preshared_key);

	/* अणुपूर्ण */
	अगर (!message_decrypt(शून्य, src->encrypted_nothing,
			     माप(src->encrypted_nothing), key, hash))
		जाओ fail;

	/* Success! Copy everything to peer */
	करोwn_ग_लिखो(&handshake->lock);
	/* It's important to check that the state is still the same, जबतक we
	 * have an exclusive lock.
	 */
	अगर (handshake->state != state) अणु
		up_ग_लिखो(&handshake->lock);
		जाओ fail;
	पूर्ण
	स_नकल(handshake->remote_ephemeral, e, NOISE_PUBLIC_KEY_LEN);
	स_नकल(handshake->hash, hash, NOISE_HASH_LEN);
	स_नकल(handshake->chaining_key, chaining_key, NOISE_HASH_LEN);
	handshake->remote_index = src->sender_index;
	handshake->state = HANDSHAKE_CONSUMED_RESPONSE;
	up_ग_लिखो(&handshake->lock);
	ret_peer = peer;
	जाओ out;

fail:
	wg_peer_put(peer);
out:
	memzero_explicit(key, NOISE_SYMMETRIC_KEY_LEN);
	memzero_explicit(hash, NOISE_HASH_LEN);
	memzero_explicit(chaining_key, NOISE_HASH_LEN);
	memzero_explicit(ephemeral_निजी, NOISE_PUBLIC_KEY_LEN);
	memzero_explicit(अटल_निजी, NOISE_PUBLIC_KEY_LEN);
	memzero_explicit(preshared_key, NOISE_SYMMETRIC_KEY_LEN);
	up_पढ़ो(&wg->अटल_identity.lock);
	वापस ret_peer;
पूर्ण

bool wg_noise_handshake_begin_session(काष्ठा noise_handshake *handshake,
				      काष्ठा noise_keypairs *keypairs)
अणु
	काष्ठा noise_keypair *new_keypair;
	bool ret = false;

	करोwn_ग_लिखो(&handshake->lock);
	अगर (handshake->state != HANDSHAKE_CREATED_RESPONSE &&
	    handshake->state != HANDSHAKE_CONSUMED_RESPONSE)
		जाओ out;

	new_keypair = keypair_create(handshake->entry.peer);
	अगर (!new_keypair)
		जाओ out;
	new_keypair->i_am_the_initiator = handshake->state ==
					  HANDSHAKE_CONSUMED_RESPONSE;
	new_keypair->remote_index = handshake->remote_index;

	अगर (new_keypair->i_am_the_initiator)
		derive_keys(&new_keypair->sending, &new_keypair->receiving,
			    handshake->chaining_key);
	अन्यथा
		derive_keys(&new_keypair->receiving, &new_keypair->sending,
			    handshake->chaining_key);

	handshake_zero(handshake);
	rcu_पढ़ो_lock_bh();
	अगर (likely(!READ_ONCE(container_of(handshake, काष्ठा wg_peer,
					   handshake)->is_dead))) अणु
		add_new_keypair(keypairs, new_keypair);
		net_dbg_ratelimited("%s: Keypair %llu created for peer %llu\n",
				    handshake->entry.peer->device->dev->name,
				    new_keypair->पूर्णांकernal_id,
				    handshake->entry.peer->पूर्णांकernal_id);
		ret = wg_index_hashtable_replace(
			handshake->entry.peer->device->index_hashtable,
			&handshake->entry, &new_keypair->entry);
	पूर्ण अन्यथा अणु
		kमुक्त_sensitive(new_keypair);
	पूर्ण
	rcu_पढ़ो_unlock_bh();

out:
	up_ग_लिखो(&handshake->lock);
	वापस ret;
पूर्ण
