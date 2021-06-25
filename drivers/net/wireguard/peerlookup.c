<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#समावेश "peerlookup.h"
#समावेश "peer.h"
#समावेश "noise.h"

अटल काष्ठा hlist_head *pubkey_bucket(काष्ठा pubkey_hashtable *table,
					स्थिर u8 pubkey[NOISE_PUBLIC_KEY_LEN])
अणु
	/* siphash gives us a secure 64bit number based on a अक्रमom key. Since
	 * the bits are unअगरormly distributed, we can then mask off to get the
	 * bits we need.
	 */
	स्थिर u64 hash = siphash(pubkey, NOISE_PUBLIC_KEY_LEN, &table->key);

	वापस &table->hashtable[hash & (HASH_SIZE(table->hashtable) - 1)];
पूर्ण

काष्ठा pubkey_hashtable *wg_pubkey_hashtable_alloc(व्योम)
अणु
	काष्ठा pubkey_hashtable *table = kvदो_स्मृति(माप(*table), GFP_KERNEL);

	अगर (!table)
		वापस शून्य;

	get_अक्रमom_bytes(&table->key, माप(table->key));
	hash_init(table->hashtable);
	mutex_init(&table->lock);
	वापस table;
पूर्ण

व्योम wg_pubkey_hashtable_add(काष्ठा pubkey_hashtable *table,
			     काष्ठा wg_peer *peer)
अणु
	mutex_lock(&table->lock);
	hlist_add_head_rcu(&peer->pubkey_hash,
			   pubkey_bucket(table, peer->handshake.remote_अटल));
	mutex_unlock(&table->lock);
पूर्ण

व्योम wg_pubkey_hashtable_हटाओ(काष्ठा pubkey_hashtable *table,
				काष्ठा wg_peer *peer)
अणु
	mutex_lock(&table->lock);
	hlist_del_init_rcu(&peer->pubkey_hash);
	mutex_unlock(&table->lock);
पूर्ण

/* Returns a strong reference to a peer */
काष्ठा wg_peer *
wg_pubkey_hashtable_lookup(काष्ठा pubkey_hashtable *table,
			   स्थिर u8 pubkey[NOISE_PUBLIC_KEY_LEN])
अणु
	काष्ठा wg_peer *iter_peer, *peer = शून्य;

	rcu_पढ़ो_lock_bh();
	hlist_क्रम_each_entry_rcu_bh(iter_peer, pubkey_bucket(table, pubkey),
				    pubkey_hash) अणु
		अगर (!स_भेद(pubkey, iter_peer->handshake.remote_अटल,
			    NOISE_PUBLIC_KEY_LEN)) अणु
			peer = iter_peer;
			अवरोध;
		पूर्ण
	पूर्ण
	peer = wg_peer_get_maybe_zero(peer);
	rcu_पढ़ो_unlock_bh();
	वापस peer;
पूर्ण

अटल काष्ठा hlist_head *index_bucket(काष्ठा index_hashtable *table,
				       स्थिर __le32 index)
अणु
	/* Since the indices are अक्रमom and thus all bits are unअगरormly
	 * distributed, we can find its bucket simply by masking.
	 */
	वापस &table->hashtable[(__क्रमce u32)index &
				 (HASH_SIZE(table->hashtable) - 1)];
पूर्ण

काष्ठा index_hashtable *wg_index_hashtable_alloc(व्योम)
अणु
	काष्ठा index_hashtable *table = kvदो_स्मृति(माप(*table), GFP_KERNEL);

	अगर (!table)
		वापस शून्य;

	hash_init(table->hashtable);
	spin_lock_init(&table->lock);
	वापस table;
पूर्ण

/* At the moment, we limit ourselves to 2^20 total peers, which generally might
 * amount to 2^20*3 items in this hashtable. The algorithm below works by
 * picking a अक्रमom number and testing it. We can see that these limits mean we
 * usually succeed pretty quickly:
 *
 * >>> def calculation(tries, size):
 * ...     वापस (size / 2**32)**(tries - 1) *  (1 - (size / 2**32))
 * ...
 * >>> calculation(1, 2**20 * 3)
 * 0.999267578125
 * >>> calculation(2, 2**20 * 3)
 * 0.0007318854331970215
 * >>> calculation(3, 2**20 * 3)
 * 5.360489012673497e-07
 * >>> calculation(4, 2**20 * 3)
 * 3.9261394135792216e-10
 *
 * At the moment, we करोn't do any masking, so this algorithm isn't exactly
 * स्थिरant समय in either the अक्रमom guessing or in the hash list lookup. We
 * could require a minimum of 3 tries, which would successfully mask the
 * guessing. this would not, however, help with the growing hash lengths, which
 * is another thing to consider moving क्रमward.
 */

__le32 wg_index_hashtable_insert(काष्ठा index_hashtable *table,
				 काष्ठा index_hashtable_entry *entry)
अणु
	काष्ठा index_hashtable_entry *existing_entry;

	spin_lock_bh(&table->lock);
	hlist_del_init_rcu(&entry->index_hash);
	spin_unlock_bh(&table->lock);

	rcu_पढ़ो_lock_bh();

search_unused_slot:
	/* First we try to find an unused slot, अक्रमomly, जबतक unlocked. */
	entry->index = (__क्रमce __le32)get_अक्रमom_u32();
	hlist_क्रम_each_entry_rcu_bh(existing_entry,
				    index_bucket(table, entry->index),
				    index_hash) अणु
		अगर (existing_entry->index == entry->index)
			/* If it's alपढ़ोy in use, we जारी searching. */
			जाओ search_unused_slot;
	पूर्ण

	/* Once we've found an unused slot, we lock it, and then द्विगुन-check
	 * that nobody अन्यथा stole it from us.
	 */
	spin_lock_bh(&table->lock);
	hlist_क्रम_each_entry_rcu_bh(existing_entry,
				    index_bucket(table, entry->index),
				    index_hash) अणु
		अगर (existing_entry->index == entry->index) अणु
			spin_unlock_bh(&table->lock);
			/* If it was stolen, we start over. */
			जाओ search_unused_slot;
		पूर्ण
	पूर्ण
	/* Otherwise, we know we have it exclusively (since we're locked),
	 * so we insert.
	 */
	hlist_add_head_rcu(&entry->index_hash,
			   index_bucket(table, entry->index));
	spin_unlock_bh(&table->lock);

	rcu_पढ़ो_unlock_bh();

	वापस entry->index;
पूर्ण

bool wg_index_hashtable_replace(काष्ठा index_hashtable *table,
				काष्ठा index_hashtable_entry *old,
				काष्ठा index_hashtable_entry *new)
अणु
	bool ret;

	spin_lock_bh(&table->lock);
	ret = !hlist_unhashed(&old->index_hash);
	अगर (unlikely(!ret))
		जाओ out;

	new->index = old->index;
	hlist_replace_rcu(&old->index_hash, &new->index_hash);

	/* Calling init here शून्यs out index_hash, and in fact after this
	 * function वापसs, it's theoretically possible क्रम this to get
	 * reinserted अन्यथाwhere. That means the RCU lookup below might either
	 * terminate early or jump between buckets, in which हाल the packet
	 * simply माला_लो dropped, which isn't terrible.
	 */
	INIT_HLIST_NODE(&old->index_hash);
out:
	spin_unlock_bh(&table->lock);
	वापस ret;
पूर्ण

व्योम wg_index_hashtable_हटाओ(काष्ठा index_hashtable *table,
			       काष्ठा index_hashtable_entry *entry)
अणु
	spin_lock_bh(&table->lock);
	hlist_del_init_rcu(&entry->index_hash);
	spin_unlock_bh(&table->lock);
पूर्ण

/* Returns a strong reference to a entry->peer */
काष्ठा index_hashtable_entry *
wg_index_hashtable_lookup(काष्ठा index_hashtable *table,
			  स्थिर क्रमागत index_hashtable_type type_mask,
			  स्थिर __le32 index, काष्ठा wg_peer **peer)
अणु
	काष्ठा index_hashtable_entry *iter_entry, *entry = शून्य;

	rcu_पढ़ो_lock_bh();
	hlist_क्रम_each_entry_rcu_bh(iter_entry, index_bucket(table, index),
				    index_hash) अणु
		अगर (iter_entry->index == index) अणु
			अगर (likely(iter_entry->type & type_mask))
				entry = iter_entry;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (likely(entry)) अणु
		entry->peer = wg_peer_get_maybe_zero(entry->peer);
		अगर (likely(entry->peer))
			*peer = entry->peer;
		अन्यथा
			entry = शून्य;
	पूर्ण
	rcu_पढ़ो_unlock_bh();
	वापस entry;
पूर्ण
