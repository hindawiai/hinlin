<शैली गुरु>
/* SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause) */

/*
 * Generic non-thपढ़ो safe hash map implementation.
 *
 * Copyright (c) 2019 Facebook
 */
#अगर_अघोषित __LIBBPF_HASHMAP_H
#घोषणा __LIBBPF_HASHMAP_H

#समावेश <stdbool.h>
#समावेश <मानकघोष.स>
#समावेश <सीमा.स>

अटल अंतरभूत माप_प्रकार hash_bits(माप_प्रकार h, पूर्णांक bits)
अणु
	/* shuffle bits and वापस requested number of upper bits */
	अगर (bits == 0)
		वापस 0;

#अगर (__SIZखातापूर्ण_SIZE_T__ == __SIZखातापूर्ण_LONG_LONG__)
	/* LP64 हाल */
	वापस (h * 11400714819323198485llu) >> (__SIZखातापूर्ण_LONG_LONG__ * 8 - bits);
#या_अगर (__SIZखातापूर्ण_SIZE_T__ <= __SIZखातापूर्ण_LONG__)
	वापस (h * 2654435769lu) >> (__SIZखातापूर्ण_LONG__ * 8 - bits);
#अन्यथा
#	error "Unsupported size_t size"
#पूर्ण_अगर
पूर्ण

/* generic C-string hashing function */
अटल अंतरभूत माप_प्रकार str_hash(स्थिर अक्षर *s)
अणु
	माप_प्रकार h = 0;

	जबतक (*s) अणु
		h = h * 31 + *s;
		s++;
	पूर्ण
	वापस h;
पूर्ण

प्रकार माप_प्रकार (*hashmap_hash_fn)(स्थिर व्योम *key, व्योम *ctx);
प्रकार bool (*hashmap_equal_fn)(स्थिर व्योम *key1, स्थिर व्योम *key2, व्योम *ctx);

काष्ठा hashmap_entry अणु
	स्थिर व्योम *key;
	व्योम *value;
	काष्ठा hashmap_entry *next;
पूर्ण;

काष्ठा hashmap अणु
	hashmap_hash_fn hash_fn;
	hashmap_equal_fn equal_fn;
	व्योम *ctx;

	काष्ठा hashmap_entry **buckets;
	माप_प्रकार cap;
	माप_प्रकार cap_bits;
	माप_प्रकार sz;
पूर्ण;

#घोषणा HASHMAP_INIT(hash_fn, equal_fn, ctx) अणु	\
	.hash_fn = (hash_fn),			\
	.equal_fn = (equal_fn),			\
	.ctx = (ctx),				\
	.buckets = शून्य,			\
	.cap = 0,				\
	.cap_bits = 0,				\
	.sz = 0,				\
पूर्ण

व्योम hashmap__init(काष्ठा hashmap *map, hashmap_hash_fn hash_fn,
		   hashmap_equal_fn equal_fn, व्योम *ctx);
काष्ठा hashmap *hashmap__new(hashmap_hash_fn hash_fn,
			     hashmap_equal_fn equal_fn,
			     व्योम *ctx);
व्योम hashmap__clear(काष्ठा hashmap *map);
व्योम hashmap__मुक्त(काष्ठा hashmap *map);

माप_प्रकार hashmap__size(स्थिर काष्ठा hashmap *map);
माप_प्रकार hashmap__capacity(स्थिर काष्ठा hashmap *map);

/*
 * Hashmap insertion strategy:
 * - HASHMAP_ADD - only add key/value अगर key करोesn't exist yet;
 * - HASHMAP_SET - add key/value pair अगर key करोesn't exist yet; otherwise,
 *   update value;
 * - HASHMAP_UPDATE - update value, अगर key alपढ़ोy exists; otherwise, करो
 *   nothing and वापस -ENOENT;
 * - HASHMAP_APPEND - always add key/value pair, even अगर key alपढ़ोy exists.
 *   This turns hashmap पूर्णांकo a multimap by allowing multiple values to be
 *   associated with the same key. Most useful पढ़ो API क्रम such hashmap is
 *   hashmap__क्रम_each_key_entry() iteration. If hashmap__find() is still
 *   used, it will वापस last inserted key/value entry (first in a bucket
 *   chain).
 */
क्रमागत hashmap_insert_strategy अणु
	HASHMAP_ADD,
	HASHMAP_SET,
	HASHMAP_UPDATE,
	HASHMAP_APPEND,
पूर्ण;

/*
 * hashmap__insert() adds key/value entry w/ various semantics, depending on
 * provided strategy value. If a given key/value pair replaced alपढ़ोy
 * existing key/value pair, both old key and old value will be वापसed
 * through old_key and old_value to allow calling code करो proper memory
 * management.
 */
पूर्णांक hashmap__insert(काष्ठा hashmap *map, स्थिर व्योम *key, व्योम *value,
		    क्रमागत hashmap_insert_strategy strategy,
		    स्थिर व्योम **old_key, व्योम **old_value);

अटल अंतरभूत पूर्णांक hashmap__add(काष्ठा hashmap *map,
			       स्थिर व्योम *key, व्योम *value)
अणु
	वापस hashmap__insert(map, key, value, HASHMAP_ADD, शून्य, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक hashmap__set(काष्ठा hashmap *map,
			       स्थिर व्योम *key, व्योम *value,
			       स्थिर व्योम **old_key, व्योम **old_value)
अणु
	वापस hashmap__insert(map, key, value, HASHMAP_SET,
			       old_key, old_value);
पूर्ण

अटल अंतरभूत पूर्णांक hashmap__update(काष्ठा hashmap *map,
				  स्थिर व्योम *key, व्योम *value,
				  स्थिर व्योम **old_key, व्योम **old_value)
अणु
	वापस hashmap__insert(map, key, value, HASHMAP_UPDATE,
			       old_key, old_value);
पूर्ण

अटल अंतरभूत पूर्णांक hashmap__append(काष्ठा hashmap *map,
				  स्थिर व्योम *key, व्योम *value)
अणु
	वापस hashmap__insert(map, key, value, HASHMAP_APPEND, शून्य, शून्य);
पूर्ण

bool hashmap__delete(काष्ठा hashmap *map, स्थिर व्योम *key,
		     स्थिर व्योम **old_key, व्योम **old_value);

bool hashmap__find(स्थिर काष्ठा hashmap *map, स्थिर व्योम *key, व्योम **value);

/*
 * hashmap__क्रम_each_entry - iterate over all entries in hashmap
 * @map: hashmap to iterate
 * @cur: काष्ठा hashmap_entry * used as a loop cursor
 * @bkt: पूर्णांकeger used as a bucket loop cursor
 */
#घोषणा hashmap__क्रम_each_entry(map, cur, bkt)				    \
	क्रम (bkt = 0; bkt < map->cap; bkt++)				    \
		क्रम (cur = map->buckets[bkt]; cur; cur = cur->next)

/*
 * hashmap__क्रम_each_entry_safe - iterate over all entries in hashmap, safe
 * against removals
 * @map: hashmap to iterate
 * @cur: काष्ठा hashmap_entry * used as a loop cursor
 * @पंचांगp: काष्ठा hashmap_entry * used as a temporary next cursor storage
 * @bkt: पूर्णांकeger used as a bucket loop cursor
 */
#घोषणा hashmap__क्रम_each_entry_safe(map, cur, पंचांगp, bkt)		    \
	क्रम (bkt = 0; bkt < map->cap; bkt++)				    \
		क्रम (cur = map->buckets[bkt];				    \
		     cur && (अणुपंचांगp = cur->next; true; पूर्ण);		    \
		     cur = पंचांगp)

/*
 * hashmap__क्रम_each_key_entry - iterate over entries associated with given key
 * @map: hashmap to iterate
 * @cur: काष्ठा hashmap_entry * used as a loop cursor
 * @key: key to iterate entries क्रम
 */
#घोषणा hashmap__क्रम_each_key_entry(map, cur, _key)			    \
	क्रम (cur = map->buckets						    \
		     ? map->buckets[hash_bits(map->hash_fn((_key), map->ctx), map->cap_bits)] \
		     : शून्य;						    \
	     cur;							    \
	     cur = cur->next)						    \
		अगर (map->equal_fn(cur->key, (_key), map->ctx))

#घोषणा hashmap__क्रम_each_key_entry_safe(map, cur, पंचांगp, _key)		    \
	क्रम (cur = map->buckets						    \
		     ? map->buckets[hash_bits(map->hash_fn((_key), map->ctx), map->cap_bits)] \
		     : शून्य;						    \
	     cur && (अणु पंचांगp = cur->next; true; पूर्ण);			    \
	     cur = पंचांगp)							    \
		अगर (map->equal_fn(cur->key, (_key), map->ctx))

#पूर्ण_अगर /* __LIBBPF_HASHMAP_H */
