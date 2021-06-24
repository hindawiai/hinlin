<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2019 Facebook
 * Copyright 2020 Google LLC.
 */

#अगर_अघोषित _BPF_LOCAL_STORAGE_H
#घोषणा _BPF_LOCAL_STORAGE_H

#समावेश <linux/bpf.h>
#समावेश <linux/rculist.h>
#समावेश <linux/list.h>
#समावेश <linux/hash.h>
#समावेश <linux/types.h>
#समावेश <uapi/linux/btf.h>

#घोषणा BPF_LOCAL_STORAGE_CACHE_SIZE	16

काष्ठा bpf_local_storage_map_bucket अणु
	काष्ठा hlist_head list;
	raw_spinlock_t lock;
पूर्ण;

/* Thp map is not the primary owner of a bpf_local_storage_elem.
 * Instead, the container object (eg. sk->sk_bpf_storage) is.
 *
 * The map (bpf_local_storage_map) is क्रम two purposes
 * 1. Define the size of the "local storage".  It is
 *    the map's value_size.
 *
 * 2. Maपूर्णांकain a list to keep track of all elems such
 *    that they can be cleaned up during the map deकाष्ठाion.
 *
 * When a bpf local storage is being looked up क्रम a
 * particular object,  the "bpf_map" poपूर्णांकer is actually used
 * as the "key" to search in the list of elem in
 * the respective bpf_local_storage owned by the object.
 *
 * e.g. sk->sk_bpf_storage is the mini-map with the "bpf_map" poपूर्णांकer
 * as the searching key.
 */
काष्ठा bpf_local_storage_map अणु
	काष्ठा bpf_map map;
	/* Lookup elem करोes not require accessing the map.
	 *
	 * Updating/Deleting requires a bucket lock to
	 * link/unlink the elem from the map.  Having
	 * multiple buckets to improve contention.
	 */
	काष्ठा bpf_local_storage_map_bucket *buckets;
	u32 bucket_log;
	u16 elem_size;
	u16 cache_idx;
पूर्ण;

काष्ठा bpf_local_storage_data अणु
	/* smap is used as the searching key when looking up
	 * from the object's bpf_local_storage.
	 *
	 * Put it in the same cacheline as the data to minimize
	 * the number of cachelines access during the cache hit हाल.
	 */
	काष्ठा bpf_local_storage_map __rcu *smap;
	u8 data[] __aligned(8);
पूर्ण;

/* Linked to bpf_local_storage and bpf_local_storage_map */
काष्ठा bpf_local_storage_elem अणु
	काष्ठा hlist_node map_node;	/* Linked to bpf_local_storage_map */
	काष्ठा hlist_node snode;	/* Linked to bpf_local_storage */
	काष्ठा bpf_local_storage __rcu *local_storage;
	काष्ठा rcu_head rcu;
	/* 8 bytes hole */
	/* The data is stored in aother cacheline to minimize
	 * the number of cachelines access during a cache hit.
	 */
	काष्ठा bpf_local_storage_data sdata ____cacheline_aligned;
पूर्ण;

काष्ठा bpf_local_storage अणु
	काष्ठा bpf_local_storage_data __rcu *cache[BPF_LOCAL_STORAGE_CACHE_SIZE];
	काष्ठा hlist_head list; /* List of bpf_local_storage_elem */
	व्योम *owner;		/* The object that owns the above "list" of
				 * bpf_local_storage_elem.
				 */
	काष्ठा rcu_head rcu;
	raw_spinlock_t lock;	/* Protect adding/removing from the "list" */
पूर्ण;

/* U16_MAX is much more than enough क्रम sk local storage
 * considering a tcp_sock is ~2k.
 */
#घोषणा BPF_LOCAL_STORAGE_MAX_VALUE_SIZE				       \
	min_t(u32,                                                             \
	      (KMALLOC_MAX_SIZE - MAX_BPF_STACK -                              \
	       माप(काष्ठा bpf_local_storage_elem)),                         \
	      (U16_MAX - माप(काष्ठा bpf_local_storage_elem)))

#घोषणा SELEM(_SDATA)                                                          \
	container_of((_SDATA), काष्ठा bpf_local_storage_elem, sdata)
#घोषणा SDATA(_SELEM) (&(_SELEM)->sdata)

#घोषणा BPF_LOCAL_STORAGE_CACHE_SIZE	16

काष्ठा bpf_local_storage_cache अणु
	spinlock_t idx_lock;
	u64 idx_usage_counts[BPF_LOCAL_STORAGE_CACHE_SIZE];
पूर्ण;

#घोषणा DEFINE_BPF_STORAGE_CACHE(name)				\
अटल काष्ठा bpf_local_storage_cache name = अणु			\
	.idx_lock = __SPIN_LOCK_UNLOCKED(name.idx_lock),	\
पूर्ण

u16 bpf_local_storage_cache_idx_get(काष्ठा bpf_local_storage_cache *cache);
व्योम bpf_local_storage_cache_idx_मुक्त(काष्ठा bpf_local_storage_cache *cache,
				      u16 idx);

/* Helper functions क्रम bpf_local_storage */
पूर्णांक bpf_local_storage_map_alloc_check(जोड़ bpf_attr *attr);

काष्ठा bpf_local_storage_map *bpf_local_storage_map_alloc(जोड़ bpf_attr *attr);

काष्ठा bpf_local_storage_data *
bpf_local_storage_lookup(काष्ठा bpf_local_storage *local_storage,
			 काष्ठा bpf_local_storage_map *smap,
			 bool cacheit_lockit);

व्योम bpf_local_storage_map_मुक्त(काष्ठा bpf_local_storage_map *smap,
				पूर्णांक __percpu *busy_counter);

पूर्णांक bpf_local_storage_map_check_btf(स्थिर काष्ठा bpf_map *map,
				    स्थिर काष्ठा btf *btf,
				    स्थिर काष्ठा btf_type *key_type,
				    स्थिर काष्ठा btf_type *value_type);

व्योम bpf_selem_link_storage_nolock(काष्ठा bpf_local_storage *local_storage,
				   काष्ठा bpf_local_storage_elem *selem);

bool bpf_selem_unlink_storage_nolock(काष्ठा bpf_local_storage *local_storage,
				     काष्ठा bpf_local_storage_elem *selem,
				     bool unअक्षरge_omem);

व्योम bpf_selem_unlink(काष्ठा bpf_local_storage_elem *selem);

व्योम bpf_selem_link_map(काष्ठा bpf_local_storage_map *smap,
			काष्ठा bpf_local_storage_elem *selem);

व्योम bpf_selem_unlink_map(काष्ठा bpf_local_storage_elem *selem);

काष्ठा bpf_local_storage_elem *
bpf_selem_alloc(काष्ठा bpf_local_storage_map *smap, व्योम *owner, व्योम *value,
		bool अक्षरge_mem);

पूर्णांक
bpf_local_storage_alloc(व्योम *owner,
			काष्ठा bpf_local_storage_map *smap,
			काष्ठा bpf_local_storage_elem *first_selem);

काष्ठा bpf_local_storage_data *
bpf_local_storage_update(व्योम *owner, काष्ठा bpf_local_storage_map *smap,
			 व्योम *value, u64 map_flags);

#पूर्ण_अगर /* _BPF_LOCAL_STORAGE_H */
