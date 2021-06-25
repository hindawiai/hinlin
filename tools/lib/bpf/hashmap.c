<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)

/*
 * Generic non-thपढ़ो safe hash map implementation.
 *
 * Copyright (c) 2019 Facebook
 */
#समावेश <मानक_निवेशt.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश "hashmap.h"

/* make sure libbpf करोesn't use kernel-only पूर्णांकeger प्रकारs */
#आशय GCC poison u8 u16 u32 u64 s8 s16 s32 s64

/* prevent accidental re-addition of पुनः_स्मृतिarray() */
#आशय GCC poison पुनः_स्मृतिarray

/* start with 4 buckets */
#घोषणा HASHMAP_MIN_CAP_BITS 2

अटल व्योम hashmap_add_entry(काष्ठा hashmap_entry **pprev,
			      काष्ठा hashmap_entry *entry)
अणु
	entry->next = *pprev;
	*pprev = entry;
पूर्ण

अटल व्योम hashmap_del_entry(काष्ठा hashmap_entry **pprev,
			      काष्ठा hashmap_entry *entry)
अणु
	*pprev = entry->next;
	entry->next = शून्य;
पूर्ण

व्योम hashmap__init(काष्ठा hashmap *map, hashmap_hash_fn hash_fn,
		   hashmap_equal_fn equal_fn, व्योम *ctx)
अणु
	map->hash_fn = hash_fn;
	map->equal_fn = equal_fn;
	map->ctx = ctx;

	map->buckets = शून्य;
	map->cap = 0;
	map->cap_bits = 0;
	map->sz = 0;
पूर्ण

काष्ठा hashmap *hashmap__new(hashmap_hash_fn hash_fn,
			     hashmap_equal_fn equal_fn,
			     व्योम *ctx)
अणु
	काष्ठा hashmap *map = दो_स्मृति(माप(काष्ठा hashmap));

	अगर (!map)
		वापस ERR_PTR(-ENOMEM);
	hashmap__init(map, hash_fn, equal_fn, ctx);
	वापस map;
पूर्ण

व्योम hashmap__clear(काष्ठा hashmap *map)
अणु
	काष्ठा hashmap_entry *cur, *पंचांगp;
	माप_प्रकार bkt;

	hashmap__क्रम_each_entry_safe(map, cur, पंचांगp, bkt) अणु
		मुक्त(cur);
	पूर्ण
	मुक्त(map->buckets);
	map->buckets = शून्य;
	map->cap = map->cap_bits = map->sz = 0;
पूर्ण

व्योम hashmap__मुक्त(काष्ठा hashmap *map)
अणु
	अगर (!map)
		वापस;

	hashmap__clear(map);
	मुक्त(map);
पूर्ण

माप_प्रकार hashmap__size(स्थिर काष्ठा hashmap *map)
अणु
	वापस map->sz;
पूर्ण

माप_प्रकार hashmap__capacity(स्थिर काष्ठा hashmap *map)
अणु
	वापस map->cap;
पूर्ण

अटल bool hashmap_needs_to_grow(काष्ठा hashmap *map)
अणु
	/* grow अगर empty or more than 75% filled */
	वापस (map->cap == 0) || ((map->sz + 1) * 4 / 3 > map->cap);
पूर्ण

अटल पूर्णांक hashmap_grow(काष्ठा hashmap *map)
अणु
	काष्ठा hashmap_entry **new_buckets;
	काष्ठा hashmap_entry *cur, *पंचांगp;
	माप_प्रकार new_cap_bits, new_cap;
	माप_प्रकार h, bkt;

	new_cap_bits = map->cap_bits + 1;
	अगर (new_cap_bits < HASHMAP_MIN_CAP_BITS)
		new_cap_bits = HASHMAP_MIN_CAP_BITS;

	new_cap = 1UL << new_cap_bits;
	new_buckets = सुस्मृति(new_cap, माप(new_buckets[0]));
	अगर (!new_buckets)
		वापस -ENOMEM;

	hashmap__क्रम_each_entry_safe(map, cur, पंचांगp, bkt) अणु
		h = hash_bits(map->hash_fn(cur->key, map->ctx), new_cap_bits);
		hashmap_add_entry(&new_buckets[h], cur);
	पूर्ण

	map->cap = new_cap;
	map->cap_bits = new_cap_bits;
	मुक्त(map->buckets);
	map->buckets = new_buckets;

	वापस 0;
पूर्ण

अटल bool hashmap_find_entry(स्थिर काष्ठा hashmap *map,
			       स्थिर व्योम *key, माप_प्रकार hash,
			       काष्ठा hashmap_entry ***pprev,
			       काष्ठा hashmap_entry **entry)
अणु
	काष्ठा hashmap_entry *cur, **prev_ptr;

	अगर (!map->buckets)
		वापस false;

	क्रम (prev_ptr = &map->buckets[hash], cur = *prev_ptr;
	     cur;
	     prev_ptr = &cur->next, cur = cur->next) अणु
		अगर (map->equal_fn(cur->key, key, map->ctx)) अणु
			अगर (pprev)
				*pprev = prev_ptr;
			*entry = cur;
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक hashmap__insert(काष्ठा hashmap *map, स्थिर व्योम *key, व्योम *value,
		    क्रमागत hashmap_insert_strategy strategy,
		    स्थिर व्योम **old_key, व्योम **old_value)
अणु
	काष्ठा hashmap_entry *entry;
	माप_प्रकार h;
	पूर्णांक err;

	अगर (old_key)
		*old_key = शून्य;
	अगर (old_value)
		*old_value = शून्य;

	h = hash_bits(map->hash_fn(key, map->ctx), map->cap_bits);
	अगर (strategy != HASHMAP_APPEND &&
	    hashmap_find_entry(map, key, h, शून्य, &entry)) अणु
		अगर (old_key)
			*old_key = entry->key;
		अगर (old_value)
			*old_value = entry->value;

		अगर (strategy == HASHMAP_SET || strategy == HASHMAP_UPDATE) अणु
			entry->key = key;
			entry->value = value;
			वापस 0;
		पूर्ण अन्यथा अगर (strategy == HASHMAP_ADD) अणु
			वापस -EEXIST;
		पूर्ण
	पूर्ण

	अगर (strategy == HASHMAP_UPDATE)
		वापस -ENOENT;

	अगर (hashmap_needs_to_grow(map)) अणु
		err = hashmap_grow(map);
		अगर (err)
			वापस err;
		h = hash_bits(map->hash_fn(key, map->ctx), map->cap_bits);
	पूर्ण

	entry = दो_स्मृति(माप(काष्ठा hashmap_entry));
	अगर (!entry)
		वापस -ENOMEM;

	entry->key = key;
	entry->value = value;
	hashmap_add_entry(&map->buckets[h], entry);
	map->sz++;

	वापस 0;
पूर्ण

bool hashmap__find(स्थिर काष्ठा hashmap *map, स्थिर व्योम *key, व्योम **value)
अणु
	काष्ठा hashmap_entry *entry;
	माप_प्रकार h;

	h = hash_bits(map->hash_fn(key, map->ctx), map->cap_bits);
	अगर (!hashmap_find_entry(map, key, h, शून्य, &entry))
		वापस false;

	अगर (value)
		*value = entry->value;
	वापस true;
पूर्ण

bool hashmap__delete(काष्ठा hashmap *map, स्थिर व्योम *key,
		     स्थिर व्योम **old_key, व्योम **old_value)
अणु
	काष्ठा hashmap_entry **pprev, *entry;
	माप_प्रकार h;

	h = hash_bits(map->hash_fn(key, map->ctx), map->cap_bits);
	अगर (!hashmap_find_entry(map, key, h, &pprev, &entry))
		वापस false;

	अगर (old_key)
		*old_key = entry->key;
	अगर (old_value)
		*old_value = entry->value;

	hashmap_del_entry(pprev, entry);
	मुक्त(entry);
	map->sz--;

	वापस true;
पूर्ण

