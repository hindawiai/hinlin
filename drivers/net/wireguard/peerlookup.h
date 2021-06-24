<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#अगर_अघोषित _WG_PEERLOOKUP_H
#घोषणा _WG_PEERLOOKUP_H

#समावेश "messages.h"

#समावेश <linux/hashtable.h>
#समावेश <linux/mutex.h>
#समावेश <linux/siphash.h>

काष्ठा wg_peer;

काष्ठा pubkey_hashtable अणु
	/* TODO: move to rhashtable */
	DECLARE_HASHTABLE(hashtable, 11);
	siphash_key_t key;
	काष्ठा mutex lock;
पूर्ण;

काष्ठा pubkey_hashtable *wg_pubkey_hashtable_alloc(व्योम);
व्योम wg_pubkey_hashtable_add(काष्ठा pubkey_hashtable *table,
			     काष्ठा wg_peer *peer);
व्योम wg_pubkey_hashtable_हटाओ(काष्ठा pubkey_hashtable *table,
				काष्ठा wg_peer *peer);
काष्ठा wg_peer *
wg_pubkey_hashtable_lookup(काष्ठा pubkey_hashtable *table,
			   स्थिर u8 pubkey[NOISE_PUBLIC_KEY_LEN]);

काष्ठा index_hashtable अणु
	/* TODO: move to rhashtable */
	DECLARE_HASHTABLE(hashtable, 13);
	spinlock_t lock;
पूर्ण;

क्रमागत index_hashtable_type अणु
	INDEX_HASHTABLE_HANDSHAKE = 1U << 0,
	INDEX_HASHTABLE_KEYPAIR = 1U << 1
पूर्ण;

काष्ठा index_hashtable_entry अणु
	काष्ठा wg_peer *peer;
	काष्ठा hlist_node index_hash;
	क्रमागत index_hashtable_type type;
	__le32 index;
पूर्ण;

काष्ठा index_hashtable *wg_index_hashtable_alloc(व्योम);
__le32 wg_index_hashtable_insert(काष्ठा index_hashtable *table,
				 काष्ठा index_hashtable_entry *entry);
bool wg_index_hashtable_replace(काष्ठा index_hashtable *table,
				काष्ठा index_hashtable_entry *old,
				काष्ठा index_hashtable_entry *new);
व्योम wg_index_hashtable_हटाओ(काष्ठा index_hashtable *table,
			       काष्ठा index_hashtable_entry *entry);
काष्ठा index_hashtable_entry *
wg_index_hashtable_lookup(काष्ठा index_hashtable *table,
			  स्थिर क्रमागत index_hashtable_type type_mask,
			  स्थिर __le32 index, काष्ठा wg_peer **peer);

#पूर्ण_अगर /* _WG_PEERLOOKUP_H */
