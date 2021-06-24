<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)

/*
 * Tests क्रम libbpf's hashmap.
 *
 * Copyright (c) 2019 Facebook
 */
#समावेश "test_progs.h"
#समावेश "bpf/hashmap.h"

अटल पूर्णांक duration = 0;

अटल माप_प्रकार hash_fn(स्थिर व्योम *k, व्योम *ctx)
अणु
	वापस (दीर्घ)k;
पूर्ण

अटल bool equal_fn(स्थिर व्योम *a, स्थिर व्योम *b, व्योम *ctx)
अणु
	वापस (दीर्घ)a == (दीर्घ)b;
पूर्ण

अटल अंतरभूत माप_प्रकार next_घात_2(माप_प्रकार n)
अणु
	माप_प्रकार r = 1;

	जबतक (r < n)
		r <<= 1;
	वापस r;
पूर्ण

अटल अंतरभूत माप_प्रकार exp_cap(माप_प्रकार sz)
अणु
	माप_प्रकार r = next_घात_2(sz);

	अगर (sz * 4 / 3 > r)
		r <<= 1;
	वापस r;
पूर्ण

#घोषणा ELEM_CNT 62

अटल व्योम test_hashmap_generic(व्योम)
अणु
	काष्ठा hashmap_entry *entry, *पंचांगp;
	पूर्णांक err, bkt, found_cnt, i;
	दीर्घ दीर्घ found_msk;
	काष्ठा hashmap *map;

	map = hashmap__new(hash_fn, equal_fn, शून्य);
	अगर (CHECK(IS_ERR(map), "hashmap__new",
		  "failed to create map: %ld\n", PTR_ERR(map)))
		वापस;

	क्रम (i = 0; i < ELEM_CNT; i++) अणु
		स्थिर व्योम *oldk, *k = (स्थिर व्योम *)(दीर्घ)i;
		व्योम *oldv, *v = (व्योम *)(दीर्घ)(1024 + i);

		err = hashmap__update(map, k, v, &oldk, &oldv);
		अगर (CHECK(err != -ENOENT, "hashmap__update",
			  "unexpected result: %d\n", err))
			जाओ cleanup;

		अगर (i % 2) अणु
			err = hashmap__add(map, k, v);
		पूर्ण अन्यथा अणु
			err = hashmap__set(map, k, v, &oldk, &oldv);
			अगर (CHECK(oldk != शून्य || oldv != शून्य, "check_kv",
				  "unexpected k/v: %p=%p\n", oldk, oldv))
				जाओ cleanup;
		पूर्ण

		अगर (CHECK(err, "elem_add", "failed to add k/v %ld = %ld: %d\n",
			       (दीर्घ)k, (दीर्घ)v, err))
			जाओ cleanup;

		अगर (CHECK(!hashmap__find(map, k, &oldv), "elem_find",
			  "failed to find key %ld\n", (दीर्घ)k))
			जाओ cleanup;
		अगर (CHECK(oldv != v, "elem_val",
			  "found value is wrong: %ld\n", (दीर्घ)oldv))
			जाओ cleanup;
	पूर्ण

	अगर (CHECK(hashmap__size(map) != ELEM_CNT, "hashmap__size",
		  "invalid map size: %zu\n", hashmap__size(map)))
		जाओ cleanup;
	अगर (CHECK(hashmap__capacity(map) != exp_cap(hashmap__size(map)),
		  "hashmap_cap",
		  "unexpected map capacity: %zu\n", hashmap__capacity(map)))
		जाओ cleanup;

	found_msk = 0;
	hashmap__क्रम_each_entry(map, entry, bkt) अणु
		दीर्घ k = (दीर्घ)entry->key;
		दीर्घ v = (दीर्घ)entry->value;

		found_msk |= 1ULL << k;
		अगर (CHECK(v - k != 1024, "check_kv",
			  "invalid k/v pair: %ld = %ld\n", k, v))
			जाओ cleanup;
	पूर्ण
	अगर (CHECK(found_msk != (1ULL << ELEM_CNT) - 1, "elem_cnt",
		  "not all keys iterated: %llx\n", found_msk))
		जाओ cleanup;

	क्रम (i = 0; i < ELEM_CNT; i++) अणु
		स्थिर व्योम *oldk, *k = (स्थिर व्योम *)(दीर्घ)i;
		व्योम *oldv, *v = (व्योम *)(दीर्घ)(256 + i);

		err = hashmap__add(map, k, v);
		अगर (CHECK(err != -EEXIST, "hashmap__add",
			  "unexpected add result: %d\n", err))
			जाओ cleanup;

		अगर (i % 2)
			err = hashmap__update(map, k, v, &oldk, &oldv);
		अन्यथा
			err = hashmap__set(map, k, v, &oldk, &oldv);

		अगर (CHECK(err, "elem_upd",
			  "failed to update k/v %ld = %ld: %d\n",
			  (दीर्घ)k, (दीर्घ)v, err))
			जाओ cleanup;
		अगर (CHECK(!hashmap__find(map, k, &oldv), "elem_find",
			  "failed to find key %ld\n", (दीर्घ)k))
			जाओ cleanup;
		अगर (CHECK(oldv != v, "elem_val",
			  "found value is wrong: %ld\n", (दीर्घ)oldv))
			जाओ cleanup;
	पूर्ण

	अगर (CHECK(hashmap__size(map) != ELEM_CNT, "hashmap__size",
		  "invalid updated map size: %zu\n", hashmap__size(map)))
		जाओ cleanup;
	अगर (CHECK(hashmap__capacity(map) != exp_cap(hashmap__size(map)),
		  "hashmap__capacity",
		  "unexpected map capacity: %zu\n", hashmap__capacity(map)))
		जाओ cleanup;

	found_msk = 0;
	hashmap__क्रम_each_entry_safe(map, entry, पंचांगp, bkt) अणु
		दीर्घ k = (दीर्घ)entry->key;
		दीर्घ v = (दीर्घ)entry->value;

		found_msk |= 1ULL << k;
		अगर (CHECK(v - k != 256, "elem_check",
			  "invalid updated k/v pair: %ld = %ld\n", k, v))
			जाओ cleanup;
	पूर्ण
	अगर (CHECK(found_msk != (1ULL << ELEM_CNT) - 1, "elem_cnt",
		  "not all keys iterated after update: %llx\n", found_msk))
		जाओ cleanup;

	found_cnt = 0;
	hashmap__क्रम_each_key_entry(map, entry, (व्योम *)0) अणु
		found_cnt++;
	पूर्ण
	अगर (CHECK(!found_cnt, "found_cnt",
		  "didn't find any entries for key 0\n"))
		जाओ cleanup;

	found_msk = 0;
	found_cnt = 0;
	hashmap__क्रम_each_key_entry_safe(map, entry, पंचांगp, (व्योम *)0) अणु
		स्थिर व्योम *oldk, *k;
		व्योम *oldv, *v;

		k = entry->key;
		v = entry->value;

		found_cnt++;
		found_msk |= 1ULL << (दीर्घ)k;

		अगर (CHECK(!hashmap__delete(map, k, &oldk, &oldv), "elem_del",
			  "failed to delete k/v %ld = %ld\n",
			  (दीर्घ)k, (दीर्घ)v))
			जाओ cleanup;
		अगर (CHECK(oldk != k || oldv != v, "check_old",
			  "invalid deleted k/v: expected %ld = %ld, got %ld = %ld\n",
			  (दीर्घ)k, (दीर्घ)v, (दीर्घ)oldk, (दीर्घ)oldv))
			जाओ cleanup;
		अगर (CHECK(hashmap__delete(map, k, &oldk, &oldv), "elem_del",
			  "unexpectedly deleted k/v %ld = %ld\n",
			  (दीर्घ)oldk, (दीर्घ)oldv))
			जाओ cleanup;
	पूर्ण

	अगर (CHECK(!found_cnt || !found_msk, "found_entries",
		  "didn't delete any key entries\n"))
		जाओ cleanup;
	अगर (CHECK(hashmap__size(map) != ELEM_CNT - found_cnt, "elem_cnt",
		  "invalid updated map size (already deleted: %d): %zu\n",
		  found_cnt, hashmap__size(map)))
		जाओ cleanup;
	अगर (CHECK(hashmap__capacity(map) != exp_cap(hashmap__size(map)),
		  "hashmap__capacity",
		  "unexpected map capacity: %zu\n", hashmap__capacity(map)))
		जाओ cleanup;

	hashmap__क्रम_each_entry_safe(map, entry, पंचांगp, bkt) अणु
		स्थिर व्योम *oldk, *k;
		व्योम *oldv, *v;

		k = entry->key;
		v = entry->value;

		found_cnt++;
		found_msk |= 1ULL << (दीर्घ)k;

		अगर (CHECK(!hashmap__delete(map, k, &oldk, &oldv), "elem_del",
			  "failed to delete k/v %ld = %ld\n",
			  (दीर्घ)k, (दीर्घ)v))
			जाओ cleanup;
		अगर (CHECK(oldk != k || oldv != v, "elem_check",
			  "invalid old k/v: expect %ld = %ld, got %ld = %ld\n",
			  (दीर्घ)k, (दीर्घ)v, (दीर्घ)oldk, (दीर्घ)oldv))
			जाओ cleanup;
		अगर (CHECK(hashmap__delete(map, k, &oldk, &oldv), "elem_del",
			  "unexpectedly deleted k/v %ld = %ld\n",
			  (दीर्घ)k, (दीर्घ)v))
			जाओ cleanup;
	पूर्ण

	अगर (CHECK(found_cnt != ELEM_CNT || found_msk != (1ULL << ELEM_CNT) - 1,
		  "found_cnt",
		  "not all keys were deleted: found_cnt:%d, found_msk:%llx\n",
		  found_cnt, found_msk))
		जाओ cleanup;
	अगर (CHECK(hashmap__size(map) != 0, "hashmap__size",
		  "invalid updated map size (already deleted: %d): %zu\n",
		  found_cnt, hashmap__size(map)))
		जाओ cleanup;

	found_cnt = 0;
	hashmap__क्रम_each_entry(map, entry, bkt) अणु
		CHECK(false, "elem_exists",
		      "unexpected map entries left: %ld = %ld\n",
		      (दीर्घ)entry->key, (दीर्घ)entry->value);
		जाओ cleanup;
	पूर्ण

	hashmap__clear(map);
	hashmap__क्रम_each_entry(map, entry, bkt) अणु
		CHECK(false, "elem_exists",
		      "unexpected map entries left: %ld = %ld\n",
		      (दीर्घ)entry->key, (दीर्घ)entry->value);
		जाओ cleanup;
	पूर्ण

cleanup:
	hashmap__मुक्त(map);
पूर्ण

अटल माप_प्रकार collision_hash_fn(स्थिर व्योम *k, व्योम *ctx)
अणु
	वापस 0;
पूर्ण

अटल व्योम test_hashmap_multimap(व्योम)
अणु
	व्योम *k1 = (व्योम *)0, *k2 = (व्योम *)1;
	काष्ठा hashmap_entry *entry;
	काष्ठा hashmap *map;
	दीर्घ found_msk;
	पूर्णांक err, bkt;

	/* क्रमce collisions */
	map = hashmap__new(collision_hash_fn, equal_fn, शून्य);
	अगर (CHECK(IS_ERR(map), "hashmap__new",
		  "failed to create map: %ld\n", PTR_ERR(map)))
		वापस;

	/* set up multimap:
	 * [0] -> 1, 2, 4;
	 * [1] -> 8, 16, 32;
	 */
	err = hashmap__append(map, k1, (व्योम *)1);
	अगर (CHECK(err, "elem_add", "failed to add k/v: %d\n", err))
		जाओ cleanup;
	err = hashmap__append(map, k1, (व्योम *)2);
	अगर (CHECK(err, "elem_add", "failed to add k/v: %d\n", err))
		जाओ cleanup;
	err = hashmap__append(map, k1, (व्योम *)4);
	अगर (CHECK(err, "elem_add", "failed to add k/v: %d\n", err))
		जाओ cleanup;

	err = hashmap__append(map, k2, (व्योम *)8);
	अगर (CHECK(err, "elem_add", "failed to add k/v: %d\n", err))
		जाओ cleanup;
	err = hashmap__append(map, k2, (व्योम *)16);
	अगर (CHECK(err, "elem_add", "failed to add k/v: %d\n", err))
		जाओ cleanup;
	err = hashmap__append(map, k2, (व्योम *)32);
	अगर (CHECK(err, "elem_add", "failed to add k/v: %d\n", err))
		जाओ cleanup;

	अगर (CHECK(hashmap__size(map) != 6, "hashmap_size",
		  "invalid map size: %zu\n", hashmap__size(map)))
		जाओ cleanup;

	/* verअगरy global iteration still works and sees all values */
	found_msk = 0;
	hashmap__क्रम_each_entry(map, entry, bkt) अणु
		found_msk |= (दीर्घ)entry->value;
	पूर्ण
	अगर (CHECK(found_msk != (1 << 6) - 1, "found_msk",
		  "not all keys iterated: %lx\n", found_msk))
		जाओ cleanup;

	/* iterate values क्रम key 1 */
	found_msk = 0;
	hashmap__क्रम_each_key_entry(map, entry, k1) अणु
		found_msk |= (दीर्घ)entry->value;
	पूर्ण
	अगर (CHECK(found_msk != (1 | 2 | 4), "found_msk",
		  "invalid k1 values: %lx\n", found_msk))
		जाओ cleanup;

	/* iterate values क्रम key 2 */
	found_msk = 0;
	hashmap__क्रम_each_key_entry(map, entry, k2) अणु
		found_msk |= (दीर्घ)entry->value;
	पूर्ण
	अगर (CHECK(found_msk != (8 | 16 | 32), "found_msk",
		  "invalid k2 values: %lx\n", found_msk))
		जाओ cleanup;

cleanup:
	hashmap__मुक्त(map);
पूर्ण

अटल व्योम test_hashmap_empty()
अणु
	काष्ठा hashmap_entry *entry;
	पूर्णांक bkt;
	काष्ठा hashmap *map;
	व्योम *k = (व्योम *)0;

	/* क्रमce collisions */
	map = hashmap__new(hash_fn, equal_fn, शून्य);
	अगर (CHECK(IS_ERR(map), "hashmap__new",
		  "failed to create map: %ld\n", PTR_ERR(map)))
		जाओ cleanup;

	अगर (CHECK(hashmap__size(map) != 0, "hashmap__size",
		  "invalid map size: %zu\n", hashmap__size(map)))
		जाओ cleanup;
	अगर (CHECK(hashmap__capacity(map) != 0, "hashmap__capacity",
		  "invalid map capacity: %zu\n", hashmap__capacity(map)))
		जाओ cleanup;
	अगर (CHECK(hashmap__find(map, k, शून्य), "elem_find",
		  "unexpected find\n"))
		जाओ cleanup;
	अगर (CHECK(hashmap__delete(map, k, शून्य, शून्य), "elem_del",
		  "unexpected delete\n"))
		जाओ cleanup;

	hashmap__क्रम_each_entry(map, entry, bkt) अणु
		CHECK(false, "elem_found", "unexpected iterated entry\n");
		जाओ cleanup;
	पूर्ण
	hashmap__क्रम_each_key_entry(map, entry, k) अणु
		CHECK(false, "key_found", "unexpected key entry\n");
		जाओ cleanup;
	पूर्ण

cleanup:
	hashmap__मुक्त(map);
पूर्ण

व्योम test_hashmap()
अणु
	अगर (test__start_subtest("generic"))
		test_hashmap_generic();
	अगर (test__start_subtest("multimap"))
		test_hashmap_multimap();
	अगर (test__start_subtest("empty"))
		test_hashmap_empty();
पूर्ण
