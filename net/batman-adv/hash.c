<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Simon Wunderlich, Marek Lindner
 */

#समावेश "hash.h"
#समावेश "main.h"

#समावेश <linux/gfp.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/slab.h>

/* clears the hash */
अटल व्योम batadv_hash_init(काष्ठा batadv_hashtable *hash)
अणु
	u32 i;

	क्रम (i = 0; i < hash->size; i++) अणु
		INIT_HLIST_HEAD(&hash->table[i]);
		spin_lock_init(&hash->list_locks[i]);
	पूर्ण

	atomic_set(&hash->generation, 0);
पूर्ण

/**
 * batadv_hash_destroy() - Free only the hashtable and the hash itself
 * @hash: hash object to destroy
 */
व्योम batadv_hash_destroy(काष्ठा batadv_hashtable *hash)
अणु
	kमुक्त(hash->list_locks);
	kमुक्त(hash->table);
	kमुक्त(hash);
पूर्ण

/**
 * batadv_hash_new() - Allocates and clears the hashtable
 * @size: number of hash buckets to allocate
 *
 * Return: newly allocated hashtable, शून्य on errors
 */
काष्ठा batadv_hashtable *batadv_hash_new(u32 size)
अणु
	काष्ठा batadv_hashtable *hash;

	hash = kदो_स्मृति(माप(*hash), GFP_ATOMIC);
	अगर (!hash)
		वापस शून्य;

	hash->table = kदो_स्मृति_array(size, माप(*hash->table), GFP_ATOMIC);
	अगर (!hash->table)
		जाओ मुक्त_hash;

	hash->list_locks = kदो_स्मृति_array(size, माप(*hash->list_locks),
					 GFP_ATOMIC);
	अगर (!hash->list_locks)
		जाओ मुक्त_table;

	hash->size = size;
	batadv_hash_init(hash);
	वापस hash;

मुक्त_table:
	kमुक्त(hash->table);
मुक्त_hash:
	kमुक्त(hash);
	वापस शून्य;
पूर्ण

/**
 * batadv_hash_set_lock_class() - Set specअगरic lockdep class क्रम hash spinlocks
 * @hash: hash object to modअगरy
 * @key: lockdep class key address
 */
व्योम batadv_hash_set_lock_class(काष्ठा batadv_hashtable *hash,
				काष्ठा lock_class_key *key)
अणु
	u32 i;

	क्रम (i = 0; i < hash->size; i++)
		lockdep_set_class(&hash->list_locks[i], key);
पूर्ण
