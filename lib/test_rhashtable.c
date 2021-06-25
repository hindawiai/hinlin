<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Resizable, Scalable, Concurrent Hash Table
 *
 * Copyright (c) 2014-2015 Thomas Graf <tgraf@suug.ch>
 * Copyright (c) 2008-2014 Patrick McHardy <kaber@trash.net>
 */

/**************************************************************************
 * Self Test
 **************************************************************************/

#समावेश <linux/init.h>
#समावेश <linux/jhash.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/रुको.h>

#घोषणा MAX_ENTRIES	1000000
#घोषणा TEST_INSERT_FAIL पूर्णांक_उच्च

अटल पूर्णांक parm_entries = 50000;
module_param(parm_entries, पूर्णांक, 0);
MODULE_PARM_DESC(parm_entries, "Number of entries to add (default: 50000)");

अटल पूर्णांक runs = 4;
module_param(runs, पूर्णांक, 0);
MODULE_PARM_DESC(runs, "Number of test runs per variant (default: 4)");

अटल पूर्णांक max_size = 0;
module_param(max_size, पूर्णांक, 0);
MODULE_PARM_DESC(max_size, "Maximum table size (default: calculated)");

अटल bool shrinking = false;
module_param(shrinking, bool, 0);
MODULE_PARM_DESC(shrinking, "Enable automatic shrinking (default: off)");

अटल पूर्णांक size = 8;
module_param(size, पूर्णांक, 0);
MODULE_PARM_DESC(size, "Initial size hint of table (default: 8)");

अटल पूर्णांक tcount = 10;
module_param(tcount, पूर्णांक, 0);
MODULE_PARM_DESC(tcount, "Number of threads to spawn (default: 10)");

अटल bool enomem_retry = false;
module_param(enomem_retry, bool, 0);
MODULE_PARM_DESC(enomem_retry, "Retry insert even if -ENOMEM was returned (default: off)");

काष्ठा test_obj_val अणु
	पूर्णांक	id;
	पूर्णांक	tid;
पूर्ण;

काष्ठा test_obj अणु
	काष्ठा test_obj_val	value;
	काष्ठा rhash_head	node;
पूर्ण;

काष्ठा test_obj_rhl अणु
	काष्ठा test_obj_val	value;
	काष्ठा rhlist_head	list_node;
पूर्ण;

काष्ठा thपढ़ो_data अणु
	अचिन्हित पूर्णांक entries;
	पूर्णांक id;
	काष्ठा task_काष्ठा *task;
	काष्ठा test_obj *objs;
पूर्ण;

अटल u32 my_hashfn(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा test_obj_rhl *obj = data;

	वापस (obj->value.id % 10);
पूर्ण

अटल पूर्णांक my_cmpfn(काष्ठा rhashtable_compare_arg *arg, स्थिर व्योम *obj)
अणु
	स्थिर काष्ठा test_obj_rhl *test_obj = obj;
	स्थिर काष्ठा test_obj_val *val = arg->key;

	वापस test_obj->value.id - val->id;
पूर्ण

अटल काष्ठा rhashtable_params test_rht_params = अणु
	.head_offset = दुरत्व(काष्ठा test_obj, node),
	.key_offset = दुरत्व(काष्ठा test_obj, value),
	.key_len = माप(काष्ठा test_obj_val),
	.hashfn = jhash,
पूर्ण;

अटल काष्ठा rhashtable_params test_rht_params_dup = अणु
	.head_offset = दुरत्व(काष्ठा test_obj_rhl, list_node),
	.key_offset = दुरत्व(काष्ठा test_obj_rhl, value),
	.key_len = माप(काष्ठा test_obj_val),
	.hashfn = jhash,
	.obj_hashfn = my_hashfn,
	.obj_cmpfn = my_cmpfn,
	.nelem_hपूर्णांक = 128,
	.स्वतःmatic_shrinking = false,
पूर्ण;

अटल atomic_t startup_count;
अटल DECLARE_WAIT_QUEUE_HEAD(startup_रुको);

अटल पूर्णांक insert_retry(काष्ठा rhashtable *ht, काष्ठा test_obj *obj,
                        स्थिर काष्ठा rhashtable_params params)
अणु
	पूर्णांक err, retries = -1, enomem_retries = 0;

	करो अणु
		retries++;
		cond_resched();
		err = rhashtable_insert_fast(ht, &obj->node, params);
		अगर (err == -ENOMEM && enomem_retry) अणु
			enomem_retries++;
			err = -EBUSY;
		पूर्ण
	पूर्ण जबतक (err == -EBUSY);

	अगर (enomem_retries)
		pr_info(" %u insertions retried after -ENOMEM\n",
			enomem_retries);

	वापस err ? : retries;
पूर्ण

अटल पूर्णांक __init test_rht_lookup(काष्ठा rhashtable *ht, काष्ठा test_obj *array,
				  अचिन्हित पूर्णांक entries)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < entries; i++) अणु
		काष्ठा test_obj *obj;
		bool expected = !(i % 2);
		काष्ठा test_obj_val key = अणु
			.id = i,
		पूर्ण;

		अगर (array[i / 2].value.id == TEST_INSERT_FAIL)
			expected = false;

		obj = rhashtable_lookup_fast(ht, &key, test_rht_params);

		अगर (expected && !obj) अणु
			pr_warn("Test failed: Could not find key %u\n", key.id);
			वापस -ENOENT;
		पूर्ण अन्यथा अगर (!expected && obj) अणु
			pr_warn("Test failed: Unexpected entry found for key %u\n",
				key.id);
			वापस -EEXIST;
		पूर्ण अन्यथा अगर (expected && obj) अणु
			अगर (obj->value.id != i) अणु
				pr_warn("Test failed: Lookup value mismatch %u!=%u\n",
					obj->value.id, i);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		cond_resched_rcu();
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम test_bucket_stats(काष्ठा rhashtable *ht, अचिन्हित पूर्णांक entries)
अणु
	अचिन्हित पूर्णांक total = 0, chain_len = 0;
	काष्ठा rhashtable_iter hti;
	काष्ठा rhash_head *pos;

	rhashtable_walk_enter(ht, &hti);
	rhashtable_walk_start(&hti);

	जबतक ((pos = rhashtable_walk_next(&hti))) अणु
		अगर (PTR_ERR(pos) == -EAGAIN) अणु
			pr_info("Info: encountered resize\n");
			chain_len++;
			जारी;
		पूर्ण अन्यथा अगर (IS_ERR(pos)) अणु
			pr_warn("Test failed: rhashtable_walk_next() error: %ld\n",
				PTR_ERR(pos));
			अवरोध;
		पूर्ण

		total++;
	पूर्ण

	rhashtable_walk_stop(&hti);
	rhashtable_walk_निकास(&hti);

	pr_info("  Traversal complete: counted=%u, nelems=%u, entries=%d, table-jumps=%u\n",
		total, atomic_पढ़ो(&ht->nelems), entries, chain_len);

	अगर (total != atomic_पढ़ो(&ht->nelems) || total != entries)
		pr_warn("Test failed: Total count mismatch ^^^");
पूर्ण

अटल s64 __init test_rhashtable(काष्ठा rhashtable *ht, काष्ठा test_obj *array,
				  अचिन्हित पूर्णांक entries)
अणु
	काष्ठा test_obj *obj;
	पूर्णांक err;
	अचिन्हित पूर्णांक i, insert_retries = 0;
	s64 start, end;

	/*
	 * Insertion Test:
	 * Insert entries पूर्णांकo table with all keys even numbers
	 */
	pr_info("  Adding %d keys\n", entries);
	start = kसमय_get_ns();
	क्रम (i = 0; i < entries; i++) अणु
		काष्ठा test_obj *obj = &array[i];

		obj->value.id = i * 2;
		err = insert_retry(ht, obj, test_rht_params);
		अगर (err > 0)
			insert_retries += err;
		अन्यथा अगर (err)
			वापस err;
	पूर्ण

	अगर (insert_retries)
		pr_info("  %u insertions retried due to memory pressure\n",
			insert_retries);

	test_bucket_stats(ht, entries);
	rcu_पढ़ो_lock();
	test_rht_lookup(ht, array, entries);
	rcu_पढ़ो_unlock();

	test_bucket_stats(ht, entries);

	pr_info("  Deleting %d keys\n", entries);
	क्रम (i = 0; i < entries; i++) अणु
		काष्ठा test_obj_val key = अणु
			.id = i * 2,
		पूर्ण;

		अगर (array[i].value.id != TEST_INSERT_FAIL) अणु
			obj = rhashtable_lookup_fast(ht, &key, test_rht_params);
			BUG_ON(!obj);

			rhashtable_हटाओ_fast(ht, &obj->node, test_rht_params);
		पूर्ण

		cond_resched();
	पूर्ण

	end = kसमय_get_ns();
	pr_info("  Duration of test: %lld ns\n", end - start);

	वापस end - start;
पूर्ण

अटल काष्ठा rhashtable ht;
अटल काष्ठा rhltable rhlt;

अटल पूर्णांक __init test_rhltable(अचिन्हित पूर्णांक entries)
अणु
	काष्ठा test_obj_rhl *rhl_test_objects;
	अचिन्हित दीर्घ *obj_in_table;
	अचिन्हित पूर्णांक i, j, k;
	पूर्णांक ret, err;

	अगर (entries == 0)
		entries = 1;

	rhl_test_objects = vzalloc(array_size(entries,
					      माप(*rhl_test_objects)));
	अगर (!rhl_test_objects)
		वापस -ENOMEM;

	ret = -ENOMEM;
	obj_in_table = vzalloc(array_size(माप(अचिन्हित दीर्घ),
					  BITS_TO_LONGS(entries)));
	अगर (!obj_in_table)
		जाओ out_मुक्त;

	err = rhltable_init(&rhlt, &test_rht_params);
	अगर (WARN_ON(err))
		जाओ out_मुक्त;

	k = pअक्रमom_u32();
	ret = 0;
	क्रम (i = 0; i < entries; i++) अणु
		rhl_test_objects[i].value.id = k;
		err = rhltable_insert(&rhlt, &rhl_test_objects[i].list_node,
				      test_rht_params);
		अगर (WARN(err, "error %d on element %d\n", err, i))
			अवरोध;
		अगर (err == 0)
			set_bit(i, obj_in_table);
	पूर्ण

	अगर (err)
		ret = err;

	pr_info("test %d add/delete pairs into rhlist\n", entries);
	क्रम (i = 0; i < entries; i++) अणु
		काष्ठा rhlist_head *h, *pos;
		काष्ठा test_obj_rhl *obj;
		काष्ठा test_obj_val key = अणु
			.id = k,
		पूर्ण;
		bool found;

		rcu_पढ़ो_lock();
		h = rhltable_lookup(&rhlt, &key, test_rht_params);
		अगर (WARN(!h, "key not found during iteration %d of %d", i, entries)) अणु
			rcu_पढ़ो_unlock();
			अवरोध;
		पूर्ण

		अगर (i) अणु
			j = i - 1;
			rhl_क्रम_each_entry_rcu(obj, pos, h, list_node) अणु
				अगर (WARN(pos == &rhl_test_objects[j].list_node, "old element found, should be gone"))
					अवरोध;
			पूर्ण
		पूर्ण

		cond_resched_rcu();

		found = false;

		rhl_क्रम_each_entry_rcu(obj, pos, h, list_node) अणु
			अगर (pos == &rhl_test_objects[i].list_node) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण

		rcu_पढ़ो_unlock();

		अगर (WARN(!found, "element %d not found", i))
			अवरोध;

		err = rhltable_हटाओ(&rhlt, &rhl_test_objects[i].list_node, test_rht_params);
		WARN(err, "rhltable_remove: err %d for iteration %d\n", err, i);
		अगर (err == 0)
			clear_bit(i, obj_in_table);
	पूर्ण

	अगर (ret == 0 && err)
		ret = err;

	क्रम (i = 0; i < entries; i++) अणु
		WARN(test_bit(i, obj_in_table), "elem %d allegedly still present", i);

		err = rhltable_insert(&rhlt, &rhl_test_objects[i].list_node,
				      test_rht_params);
		अगर (WARN(err, "error %d on element %d\n", err, i))
			अवरोध;
		अगर (err == 0)
			set_bit(i, obj_in_table);
	पूर्ण

	pr_info("test %d random rhlist add/delete operations\n", entries);
	क्रम (j = 0; j < entries; j++) अणु
		u32 i = pअक्रमom_u32_max(entries);
		u32 pअक्रम = pअक्रमom_u32();

		cond_resched();

		अगर (pअक्रम == 0)
			pअक्रम = pअक्रमom_u32();

		अगर (pअक्रम & 1) अणु
			pअक्रम >>= 1;
			जारी;
		पूर्ण

		err = rhltable_हटाओ(&rhlt, &rhl_test_objects[i].list_node, test_rht_params);
		अगर (test_bit(i, obj_in_table)) अणु
			clear_bit(i, obj_in_table);
			अगर (WARN(err, "cannot remove element at slot %d", i))
				जारी;
		पूर्ण अन्यथा अणु
			अगर (WARN(err != -ENOENT, "removed non-existent element %d, error %d not %d",
			     i, err, -ENOENT))
				जारी;
		पूर्ण

		अगर (pअक्रम & 1) अणु
			pअक्रम >>= 1;
			जारी;
		पूर्ण

		err = rhltable_insert(&rhlt, &rhl_test_objects[i].list_node, test_rht_params);
		अगर (err == 0) अणु
			अगर (WARN(test_and_set_bit(i, obj_in_table), "succeeded to insert same object %d", i))
				जारी;
		पूर्ण अन्यथा अणु
			अगर (WARN(!test_bit(i, obj_in_table), "failed to insert object %d", i))
				जारी;
		पूर्ण

		अगर (pअक्रम & 1) अणु
			pअक्रम >>= 1;
			जारी;
		पूर्ण

		i = pअक्रमom_u32_max(entries);
		अगर (test_bit(i, obj_in_table)) अणु
			err = rhltable_हटाओ(&rhlt, &rhl_test_objects[i].list_node, test_rht_params);
			WARN(err, "cannot remove element at slot %d", i);
			अगर (err == 0)
				clear_bit(i, obj_in_table);
		पूर्ण अन्यथा अणु
			err = rhltable_insert(&rhlt, &rhl_test_objects[i].list_node, test_rht_params);
			WARN(err, "failed to insert object %d", i);
			अगर (err == 0)
				set_bit(i, obj_in_table);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < entries; i++) अणु
		cond_resched();
		err = rhltable_हटाओ(&rhlt, &rhl_test_objects[i].list_node, test_rht_params);
		अगर (test_bit(i, obj_in_table)) अणु
			अगर (WARN(err, "cannot remove element at slot %d", i))
				जारी;
		पूर्ण अन्यथा अणु
			अगर (WARN(err != -ENOENT, "removed non-existent element, error %d not %d",
				 err, -ENOENT))
				जारी;
		पूर्ण
	पूर्ण

	rhltable_destroy(&rhlt);
out_मुक्त:
	vमुक्त(rhl_test_objects);
	vमुक्त(obj_in_table);
	वापस ret;
पूर्ण

अटल पूर्णांक __init test_rhashtable_max(काष्ठा test_obj *array,
				      अचिन्हित पूर्णांक entries)
अणु
	अचिन्हित पूर्णांक i, insert_retries = 0;
	पूर्णांक err;

	test_rht_params.max_size = roundup_घात_of_two(entries / 8);
	err = rhashtable_init(&ht, &test_rht_params);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < ht.max_elems; i++) अणु
		काष्ठा test_obj *obj = &array[i];

		obj->value.id = i * 2;
		err = insert_retry(&ht, obj, test_rht_params);
		अगर (err > 0)
			insert_retries += err;
		अन्यथा अगर (err)
			वापस err;
	पूर्ण

	err = insert_retry(&ht, &array[ht.max_elems], test_rht_params);
	अगर (err == -E2BIG) अणु
		err = 0;
	पूर्ण अन्यथा अणु
		pr_info("insert element %u should have failed with %d, got %d\n",
				ht.max_elems, -E2BIG, err);
		अगर (err == 0)
			err = -1;
	पूर्ण

	rhashtable_destroy(&ht);

	वापस err;
पूर्ण

अटल अचिन्हित पूर्णांक __init prपूर्णांक_ht(काष्ठा rhltable *rhlt)
अणु
	काष्ठा rhashtable *ht;
	स्थिर काष्ठा bucket_table *tbl;
	अक्षर buff[512] = "";
	पूर्णांक offset = 0;
	अचिन्हित पूर्णांक i, cnt = 0;

	ht = &rhlt->ht;
	/* Take the mutex to aव्योम RCU warning */
	mutex_lock(&ht->mutex);
	tbl = rht_dereference(ht->tbl, ht);
	क्रम (i = 0; i < tbl->size; i++) अणु
		काष्ठा rhash_head *pos, *next;
		काष्ठा test_obj_rhl *p;

		pos = rht_ptr_exclusive(tbl->buckets + i);
		next = !rht_is_a_nulls(pos) ? rht_dereference(pos->next, ht) : शून्य;

		अगर (!rht_is_a_nulls(pos)) अणु
			offset += प्र_लिखो(buff + offset, "\nbucket[%d] -> ", i);
		पूर्ण

		जबतक (!rht_is_a_nulls(pos)) अणु
			काष्ठा rhlist_head *list = container_of(pos, काष्ठा rhlist_head, rhead);
			offset += प्र_लिखो(buff + offset, "[[");
			करो अणु
				pos = &list->rhead;
				list = rht_dereference(list->next, ht);
				p = rht_obj(ht, pos);

				offset += प्र_लिखो(buff + offset, " val %d (tid=%d)%s", p->value.id, p->value.tid,
					list? ", " : " ");
				cnt++;
			पूर्ण जबतक (list);

			pos = next,
			next = !rht_is_a_nulls(pos) ?
				rht_dereference(pos->next, ht) : शून्य;

			offset += प्र_लिखो(buff + offset, "]]%s", !rht_is_a_nulls(pos) ? " -> " : "");
		पूर्ण
	पूर्ण
	prपूर्णांकk(KERN_ERR "\n---- ht: ----%s\n-------------\n", buff);
	mutex_unlock(&ht->mutex);

	वापस cnt;
पूर्ण

अटल पूर्णांक __init test_insert_dup(काष्ठा test_obj_rhl *rhl_test_objects,
				  पूर्णांक cnt, bool slow)
अणु
	काष्ठा rhltable *rhlt;
	अचिन्हित पूर्णांक i, ret;
	स्थिर अक्षर *key;
	पूर्णांक err = 0;

	rhlt = kदो_स्मृति(माप(*rhlt), GFP_KERNEL);
	अगर (WARN_ON(!rhlt))
		वापस -EINVAL;

	err = rhltable_init(rhlt, &test_rht_params_dup);
	अगर (WARN_ON(err)) अणु
		kमुक्त(rhlt);
		वापस err;
	पूर्ण

	क्रम (i = 0; i < cnt; i++) अणु
		rhl_test_objects[i].value.tid = i;
		key = rht_obj(&rhlt->ht, &rhl_test_objects[i].list_node.rhead);
		key += test_rht_params_dup.key_offset;

		अगर (slow) अणु
			err = PTR_ERR(rhashtable_insert_slow(&rhlt->ht, key,
							     &rhl_test_objects[i].list_node.rhead));
			अगर (err == -EAGAIN)
				err = 0;
		पूर्ण अन्यथा
			err = rhltable_insert(rhlt,
					      &rhl_test_objects[i].list_node,
					      test_rht_params_dup);
		अगर (WARN(err, "error %d on element %d/%d (%s)\n", err, i, cnt, slow? "slow" : "fast"))
			जाओ skip_prपूर्णांक;
	पूर्ण

	ret = prपूर्णांक_ht(rhlt);
	WARN(ret != cnt, "missing rhltable elements (%d != %d, %s)\n", ret, cnt, slow? "slow" : "fast");

skip_prपूर्णांक:
	rhltable_destroy(rhlt);
	kमुक्त(rhlt);

	वापस 0;
पूर्ण

अटल पूर्णांक __init test_insert_duplicates_run(व्योम)
अणु
	काष्ठा test_obj_rhl rhl_test_objects[3] = अणुपूर्ण;

	pr_info("test inserting duplicates\n");

	/* two dअगरferent values that map to same bucket */
	rhl_test_objects[0].value.id = 1;
	rhl_test_objects[1].value.id = 21;

	/* and another duplicate with same as [0] value
	 * which will be second on the bucket list */
	rhl_test_objects[2].value.id = rhl_test_objects[0].value.id;

	test_insert_dup(rhl_test_objects, 2, false);
	test_insert_dup(rhl_test_objects, 3, false);
	test_insert_dup(rhl_test_objects, 2, true);
	test_insert_dup(rhl_test_objects, 3, true);

	वापस 0;
पूर्ण

अटल पूर्णांक thपढ़ो_lookup_test(काष्ठा thपढ़ो_data *tdata)
अणु
	अचिन्हित पूर्णांक entries = tdata->entries;
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < entries; i++) अणु
		काष्ठा test_obj *obj;
		काष्ठा test_obj_val key = अणु
			.id = i,
			.tid = tdata->id,
		पूर्ण;

		obj = rhashtable_lookup_fast(&ht, &key, test_rht_params);
		अगर (obj && (tdata->objs[i].value.id == TEST_INSERT_FAIL)) अणु
			pr_err("  found unexpected object %d-%d\n", key.tid, key.id);
			err++;
		पूर्ण अन्यथा अगर (!obj && (tdata->objs[i].value.id != TEST_INSERT_FAIL)) अणु
			pr_err("  object %d-%d not found!\n", key.tid, key.id);
			err++;
		पूर्ण अन्यथा अगर (obj && स_भेद(&obj->value, &key, माप(key))) अणु
			pr_err("  wrong object returned (got %d-%d, expected %d-%d)\n",
			       obj->value.tid, obj->value.id, key.tid, key.id);
			err++;
		पूर्ण

		cond_resched();
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक thपढ़ोfunc(व्योम *data)
अणु
	पूर्णांक i, step, err = 0, insert_retries = 0;
	काष्ठा thपढ़ो_data *tdata = data;

	अगर (atomic_dec_and_test(&startup_count))
		wake_up(&startup_रुको);
	अगर (रुको_event_पूर्णांकerruptible(startup_रुको, atomic_पढ़ो(&startup_count) == -1)) अणु
		pr_err("  thread[%d]: interrupted\n", tdata->id);
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < tdata->entries; i++) अणु
		tdata->objs[i].value.id = i;
		tdata->objs[i].value.tid = tdata->id;
		err = insert_retry(&ht, &tdata->objs[i], test_rht_params);
		अगर (err > 0) अणु
			insert_retries += err;
		पूर्ण अन्यथा अगर (err) अणु
			pr_err("  thread[%d]: rhashtable_insert_fast failed\n",
			       tdata->id);
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (insert_retries)
		pr_info("  thread[%d]: %u insertions retried due to memory pressure\n",
			tdata->id, insert_retries);

	err = thपढ़ो_lookup_test(tdata);
	अगर (err) अणु
		pr_err("  thread[%d]: rhashtable_lookup_test failed\n",
		       tdata->id);
		जाओ out;
	पूर्ण

	क्रम (step = 10; step > 0; step--) अणु
		क्रम (i = 0; i < tdata->entries; i += step) अणु
			अगर (tdata->objs[i].value.id == TEST_INSERT_FAIL)
				जारी;
			err = rhashtable_हटाओ_fast(&ht, &tdata->objs[i].node,
			                             test_rht_params);
			अगर (err) अणु
				pr_err("  thread[%d]: rhashtable_remove_fast failed\n",
				       tdata->id);
				जाओ out;
			पूर्ण
			tdata->objs[i].value.id = TEST_INSERT_FAIL;

			cond_resched();
		पूर्ण
		err = thपढ़ो_lookup_test(tdata);
		अगर (err) अणु
			pr_err("  thread[%d]: rhashtable_lookup_test (2) failed\n",
			       tdata->id);
			जाओ out;
		पूर्ण
	पूर्ण
out:
	जबतक (!kthपढ़ो_should_stop()) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		schedule();
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक __init test_rht_init(व्योम)
अणु
	अचिन्हित पूर्णांक entries;
	पूर्णांक i, err, started_thपढ़ोs = 0, failed_thपढ़ोs = 0;
	u64 total_समय = 0;
	काष्ठा thपढ़ो_data *tdata;
	काष्ठा test_obj *objs;

	अगर (parm_entries < 0)
		parm_entries = 1;

	entries = min(parm_entries, MAX_ENTRIES);

	test_rht_params.स्वतःmatic_shrinking = shrinking;
	test_rht_params.max_size = max_size ? : roundup_घात_of_two(entries);
	test_rht_params.nelem_hपूर्णांक = size;

	objs = vzalloc(array_size(माप(काष्ठा test_obj),
				  test_rht_params.max_size + 1));
	अगर (!objs)
		वापस -ENOMEM;

	pr_info("Running rhashtable test nelem=%d, max_size=%d, shrinking=%d\n",
		size, max_size, shrinking);

	क्रम (i = 0; i < runs; i++) अणु
		s64 समय;

		pr_info("Test %02d:\n", i);
		स_रखो(objs, 0, test_rht_params.max_size * माप(काष्ठा test_obj));

		err = rhashtable_init(&ht, &test_rht_params);
		अगर (err < 0) अणु
			pr_warn("Test failed: Unable to initialize hashtable: %d\n",
				err);
			जारी;
		पूर्ण

		समय = test_rhashtable(&ht, objs, entries);
		rhashtable_destroy(&ht);
		अगर (समय < 0) अणु
			vमुक्त(objs);
			pr_warn("Test failed: return code %lld\n", समय);
			वापस -EINVAL;
		पूर्ण

		total_समय += समय;
	पूर्ण

	pr_info("test if its possible to exceed max_size %d: %s\n",
			test_rht_params.max_size, test_rhashtable_max(objs, entries) == 0 ?
			"no, ok" : "YES, failed");
	vमुक्त(objs);

	करो_भाग(total_समय, runs);
	pr_info("Average test time: %llu\n", total_समय);

	test_insert_duplicates_run();

	अगर (!tcount)
		वापस 0;

	pr_info("Testing concurrent rhashtable access from %d threads\n",
	        tcount);
	atomic_set(&startup_count, tcount);
	tdata = vzalloc(array_size(tcount, माप(काष्ठा thपढ़ो_data)));
	अगर (!tdata)
		वापस -ENOMEM;
	objs  = vzalloc(array3_size(माप(काष्ठा test_obj), tcount, entries));
	अगर (!objs) अणु
		vमुक्त(tdata);
		वापस -ENOMEM;
	पूर्ण

	test_rht_params.max_size = max_size ? :
	                           roundup_घात_of_two(tcount * entries);
	err = rhashtable_init(&ht, &test_rht_params);
	अगर (err < 0) अणु
		pr_warn("Test failed: Unable to initialize hashtable: %d\n",
			err);
		vमुक्त(tdata);
		vमुक्त(objs);
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < tcount; i++) अणु
		tdata[i].id = i;
		tdata[i].entries = entries;
		tdata[i].objs = objs + i * entries;
		tdata[i].task = kthपढ़ो_run(thपढ़ोfunc, &tdata[i],
		                            "rhashtable_thrad[%d]", i);
		अगर (IS_ERR(tdata[i].task)) अणु
			pr_err(" kthread_run failed for thread %d\n", i);
			atomic_dec(&startup_count);
		पूर्ण अन्यथा अणु
			started_thपढ़ोs++;
		पूर्ण
	पूर्ण
	अगर (रुको_event_पूर्णांकerruptible(startup_रुको, atomic_पढ़ो(&startup_count) == 0))
		pr_err("  wait_event interruptible failed\n");
	/* count is 0 now, set it to -1 and wake up all thपढ़ोs together */
	atomic_dec(&startup_count);
	wake_up_all(&startup_रुको);
	क्रम (i = 0; i < tcount; i++) अणु
		अगर (IS_ERR(tdata[i].task))
			जारी;
		अगर ((err = kthपढ़ो_stop(tdata[i].task))) अणु
			pr_warn("Test failed: thread %d returned: %d\n",
			        i, err);
			failed_thपढ़ोs++;
		पूर्ण
	पूर्ण
	rhashtable_destroy(&ht);
	vमुक्त(tdata);
	vमुक्त(objs);

	/*
	 * rhltable_हटाओ is very expensive, शेष values can cause test
	 * to run क्रम 2 minutes or more,  use a smaller number instead.
	 */
	err = test_rhltable(entries / 16);
	pr_info("Started %d threads, %d failed, rhltable test returns %d\n",
	        started_thपढ़ोs, failed_thपढ़ोs, err);
	वापस 0;
पूर्ण

अटल व्योम __निकास test_rht_निकास(व्योम)
अणु
पूर्ण

module_init(test_rht_init);
module_निकास(test_rht_निकास);

MODULE_LICENSE("GPL v2");
