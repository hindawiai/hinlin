<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_MBCACHE_H
#घोषणा _LINUX_MBCACHE_H

#समावेश <linux/hash.h>
#समावेश <linux/list_bl.h>
#समावेश <linux/list.h>
#समावेश <linux/atomic.h>
#समावेश <linux/fs.h>

काष्ठा mb_cache;

काष्ठा mb_cache_entry अणु
	/* List of entries in cache - रक्षित by cache->c_list_lock */
	काष्ठा list_head	e_list;
	/* Hash table list - रक्षित by hash chain bitlock */
	काष्ठा hlist_bl_node	e_hash_list;
	atomic_t		e_refcnt;
	/* Key in hash - stable during lअगरeसमय of the entry */
	u32			e_key;
	u32			e_referenced:1;
	u32			e_reusable:1;
	/* User provided value - stable during lअगरeसमय of the entry */
	u64			e_value;
पूर्ण;

काष्ठा mb_cache *mb_cache_create(पूर्णांक bucket_bits);
व्योम mb_cache_destroy(काष्ठा mb_cache *cache);

पूर्णांक mb_cache_entry_create(काष्ठा mb_cache *cache, gfp_t mask, u32 key,
			  u64 value, bool reusable);
व्योम __mb_cache_entry_मुक्त(काष्ठा mb_cache_entry *entry);
अटल अंतरभूत पूर्णांक mb_cache_entry_put(काष्ठा mb_cache *cache,
				     काष्ठा mb_cache_entry *entry)
अणु
	अगर (!atomic_dec_and_test(&entry->e_refcnt))
		वापस 0;
	__mb_cache_entry_मुक्त(entry);
	वापस 1;
पूर्ण

व्योम mb_cache_entry_delete(काष्ठा mb_cache *cache, u32 key, u64 value);
काष्ठा mb_cache_entry *mb_cache_entry_get(काष्ठा mb_cache *cache, u32 key,
					  u64 value);
काष्ठा mb_cache_entry *mb_cache_entry_find_first(काष्ठा mb_cache *cache,
						 u32 key);
काष्ठा mb_cache_entry *mb_cache_entry_find_next(काष्ठा mb_cache *cache,
						काष्ठा mb_cache_entry *entry);
व्योम mb_cache_entry_touch(काष्ठा mb_cache *cache,
			  काष्ठा mb_cache_entry *entry);

#पूर्ण_अगर	/* _LINUX_MBCACHE_H */
