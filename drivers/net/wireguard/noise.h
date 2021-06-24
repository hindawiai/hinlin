<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */
#अगर_अघोषित _WG_NOISE_H
#घोषणा _WG_NOISE_H

#समावेश "messages.h"
#समावेश "peerlookup.h"

#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/atomic.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kref.h>

काष्ठा noise_replay_counter अणु
	u64 counter;
	spinlock_t lock;
	अचिन्हित दीर्घ backtrack[COUNTER_BITS_TOTAL / BITS_PER_LONG];
पूर्ण;

काष्ठा noise_symmetric_key अणु
	u8 key[NOISE_SYMMETRIC_KEY_LEN];
	u64 birthdate;
	bool is_valid;
पूर्ण;

काष्ठा noise_keypair अणु
	काष्ठा index_hashtable_entry entry;
	काष्ठा noise_symmetric_key sending;
	atomic64_t sending_counter;
	काष्ठा noise_symmetric_key receiving;
	काष्ठा noise_replay_counter receiving_counter;
	__le32 remote_index;
	bool i_am_the_initiator;
	काष्ठा kref refcount;
	काष्ठा rcu_head rcu;
	u64 पूर्णांकernal_id;
पूर्ण;

काष्ठा noise_keypairs अणु
	काष्ठा noise_keypair __rcu *current_keypair;
	काष्ठा noise_keypair __rcu *previous_keypair;
	काष्ठा noise_keypair __rcu *next_keypair;
	spinlock_t keypair_update_lock;
पूर्ण;

काष्ठा noise_अटल_identity अणु
	u8 अटल_खुला[NOISE_PUBLIC_KEY_LEN];
	u8 अटल_निजी[NOISE_PUBLIC_KEY_LEN];
	काष्ठा rw_semaphore lock;
	bool has_identity;
पूर्ण;

क्रमागत noise_handshake_state अणु
	HANDSHAKE_ZEROED,
	HANDSHAKE_CREATED_INITIATION,
	HANDSHAKE_CONSUMED_INITIATION,
	HANDSHAKE_CREATED_RESPONSE,
	HANDSHAKE_CONSUMED_RESPONSE
पूर्ण;

काष्ठा noise_handshake अणु
	काष्ठा index_hashtable_entry entry;

	क्रमागत noise_handshake_state state;
	u64 last_initiation_consumption;

	काष्ठा noise_अटल_identity *अटल_identity;

	u8 ephemeral_निजी[NOISE_PUBLIC_KEY_LEN];
	u8 remote_अटल[NOISE_PUBLIC_KEY_LEN];
	u8 remote_ephemeral[NOISE_PUBLIC_KEY_LEN];
	u8 precomputed_अटल_अटल[NOISE_PUBLIC_KEY_LEN];

	u8 preshared_key[NOISE_SYMMETRIC_KEY_LEN];

	u8 hash[NOISE_HASH_LEN];
	u8 chaining_key[NOISE_HASH_LEN];

	u8 latest_बारtamp[NOISE_TIMESTAMP_LEN];
	__le32 remote_index;

	/* Protects all members except the immutable (after noise_handshake_
	 * init): remote_अटल, precomputed_अटल_अटल, अटल_identity.
	 */
	काष्ठा rw_semaphore lock;
पूर्ण;

काष्ठा wg_device;

व्योम wg_noise_init(व्योम);
व्योम wg_noise_handshake_init(काष्ठा noise_handshake *handshake,
			     काष्ठा noise_अटल_identity *अटल_identity,
			     स्थिर u8 peer_खुला_key[NOISE_PUBLIC_KEY_LEN],
			     स्थिर u8 peer_preshared_key[NOISE_SYMMETRIC_KEY_LEN],
			     काष्ठा wg_peer *peer);
व्योम wg_noise_handshake_clear(काष्ठा noise_handshake *handshake);
अटल अंतरभूत व्योम wg_noise_reset_last_sent_handshake(atomic64_t *handshake_ns)
अणु
	atomic64_set(handshake_ns, kसमय_get_coarse_bootसमय_ns() -
				       (u64)(REKEY_TIMEOUT + 1) * NSEC_PER_SEC);
पूर्ण

व्योम wg_noise_keypair_put(काष्ठा noise_keypair *keypair, bool unreference_now);
काष्ठा noise_keypair *wg_noise_keypair_get(काष्ठा noise_keypair *keypair);
व्योम wg_noise_keypairs_clear(काष्ठा noise_keypairs *keypairs);
bool wg_noise_received_with_keypair(काष्ठा noise_keypairs *keypairs,
				    काष्ठा noise_keypair *received_keypair);
व्योम wg_noise_expire_current_peer_keypairs(काष्ठा wg_peer *peer);

व्योम wg_noise_set_अटल_identity_निजी_key(
	काष्ठा noise_अटल_identity *अटल_identity,
	स्थिर u8 निजी_key[NOISE_PUBLIC_KEY_LEN]);
व्योम wg_noise_precompute_अटल_अटल(काष्ठा wg_peer *peer);

bool
wg_noise_handshake_create_initiation(काष्ठा message_handshake_initiation *dst,
				     काष्ठा noise_handshake *handshake);
काष्ठा wg_peer *
wg_noise_handshake_consume_initiation(काष्ठा message_handshake_initiation *src,
				      काष्ठा wg_device *wg);

bool wg_noise_handshake_create_response(काष्ठा message_handshake_response *dst,
					काष्ठा noise_handshake *handshake);
काष्ठा wg_peer *
wg_noise_handshake_consume_response(काष्ठा message_handshake_response *src,
				    काष्ठा wg_device *wg);

bool wg_noise_handshake_begin_session(काष्ठा noise_handshake *handshake,
				      काष्ठा noise_keypairs *keypairs);

#पूर्ण_अगर /* _WG_NOISE_H */
