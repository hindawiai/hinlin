<शैली गुरु>
/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-space-map-common.h"
#समावेश "dm-space-map-disk.h"
#समावेश "dm-space-map.h"
#समावेश "dm-transaction-manager.h"

#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/device-mapper.h>

#घोषणा DM_MSG_PREFIX "space map disk"

/*----------------------------------------------------------------*/

/*
 * Space map पूर्णांकerface.
 */
काष्ठा sm_disk अणु
	काष्ठा dm_space_map sm;

	काष्ठा ll_disk ll;
	काष्ठा ll_disk old_ll;

	dm_block_t begin;
	dm_block_t nr_allocated_this_transaction;
पूर्ण;

अटल व्योम sm_disk_destroy(काष्ठा dm_space_map *sm)
अणु
	काष्ठा sm_disk *smd = container_of(sm, काष्ठा sm_disk, sm);

	kमुक्त(smd);
पूर्ण

अटल पूर्णांक sm_disk_extend(काष्ठा dm_space_map *sm, dm_block_t extra_blocks)
अणु
	काष्ठा sm_disk *smd = container_of(sm, काष्ठा sm_disk, sm);

	वापस sm_ll_extend(&smd->ll, extra_blocks);
पूर्ण

अटल पूर्णांक sm_disk_get_nr_blocks(काष्ठा dm_space_map *sm, dm_block_t *count)
अणु
	काष्ठा sm_disk *smd = container_of(sm, काष्ठा sm_disk, sm);
	*count = smd->old_ll.nr_blocks;

	वापस 0;
पूर्ण

अटल पूर्णांक sm_disk_get_nr_मुक्त(काष्ठा dm_space_map *sm, dm_block_t *count)
अणु
	काष्ठा sm_disk *smd = container_of(sm, काष्ठा sm_disk, sm);
	*count = (smd->old_ll.nr_blocks - smd->old_ll.nr_allocated) - smd->nr_allocated_this_transaction;

	वापस 0;
पूर्ण

अटल पूर्णांक sm_disk_get_count(काष्ठा dm_space_map *sm, dm_block_t b,
			     uपूर्णांक32_t *result)
अणु
	काष्ठा sm_disk *smd = container_of(sm, काष्ठा sm_disk, sm);
	वापस sm_ll_lookup(&smd->ll, b, result);
पूर्ण

अटल पूर्णांक sm_disk_count_is_more_than_one(काष्ठा dm_space_map *sm, dm_block_t b,
					  पूर्णांक *result)
अणु
	पूर्णांक r;
	uपूर्णांक32_t count;

	r = sm_disk_get_count(sm, b, &count);
	अगर (r)
		वापस r;

	*result = count > 1;

	वापस 0;
पूर्ण

अटल पूर्णांक sm_disk_set_count(काष्ठा dm_space_map *sm, dm_block_t b,
			     uपूर्णांक32_t count)
अणु
	पूर्णांक r;
	uपूर्णांक32_t old_count;
	क्रमागत allocation_event ev;
	काष्ठा sm_disk *smd = container_of(sm, काष्ठा sm_disk, sm);

	r = sm_ll_insert(&smd->ll, b, count, &ev);
	अगर (!r) अणु
		चयन (ev) अणु
		हाल SM_NONE:
			अवरोध;

		हाल SM_ALLOC:
			/*
			 * This _must_ be मुक्त in the prior transaction
			 * otherwise we've lost atomicity.
			 */
			smd->nr_allocated_this_transaction++;
			अवरोध;

		हाल SM_FREE:
			/*
			 * It's only free if it's also मुक्त in the last
			 * transaction.
			 */
			r = sm_ll_lookup(&smd->old_ll, b, &old_count);
			अगर (r)
				वापस r;

			अगर (!old_count)
				smd->nr_allocated_this_transaction--;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक sm_disk_inc_block(काष्ठा dm_space_map *sm, dm_block_t b)
अणु
	पूर्णांक r;
	क्रमागत allocation_event ev;
	काष्ठा sm_disk *smd = container_of(sm, काष्ठा sm_disk, sm);

	r = sm_ll_inc(&smd->ll, b, &ev);
	अगर (!r && (ev == SM_ALLOC))
		/*
		 * This _must_ be मुक्त in the prior transaction
		 * otherwise we've lost atomicity.
		 */
		smd->nr_allocated_this_transaction++;

	वापस r;
पूर्ण

अटल पूर्णांक sm_disk_dec_block(काष्ठा dm_space_map *sm, dm_block_t b)
अणु
	पूर्णांक r;
	uपूर्णांक32_t old_count;
	क्रमागत allocation_event ev;
	काष्ठा sm_disk *smd = container_of(sm, काष्ठा sm_disk, sm);

	r = sm_ll_dec(&smd->ll, b, &ev);
	अगर (!r && (ev == SM_FREE)) अणु
		/*
		 * It's only free if it's also मुक्त in the last
		 * transaction.
		 */
		r = sm_ll_lookup(&smd->old_ll, b, &old_count);
		अगर (!r && !old_count)
			smd->nr_allocated_this_transaction--;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक sm_disk_new_block(काष्ठा dm_space_map *sm, dm_block_t *b)
अणु
	पूर्णांक r;
	क्रमागत allocation_event ev;
	काष्ठा sm_disk *smd = container_of(sm, काष्ठा sm_disk, sm);

	/*
	 * Any block we allocate has to be मुक्त in both the old and current ll.
	 */
	r = sm_ll_find_common_मुक्त_block(&smd->old_ll, &smd->ll, smd->begin, smd->ll.nr_blocks, b);
	अगर (r)
		वापस r;

	smd->begin = *b + 1;
	r = sm_ll_inc(&smd->ll, *b, &ev);
	अगर (!r) अणु
		BUG_ON(ev != SM_ALLOC);
		smd->nr_allocated_this_transaction++;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक sm_disk_commit(काष्ठा dm_space_map *sm)
अणु
	पूर्णांक r;
	काष्ठा sm_disk *smd = container_of(sm, काष्ठा sm_disk, sm);

	r = sm_ll_commit(&smd->ll);
	अगर (r)
		वापस r;

	स_नकल(&smd->old_ll, &smd->ll, माप(smd->old_ll));
	smd->begin = 0;
	smd->nr_allocated_this_transaction = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक sm_disk_root_size(काष्ठा dm_space_map *sm, माप_प्रकार *result)
अणु
	*result = माप(काष्ठा disk_sm_root);

	वापस 0;
पूर्ण

अटल पूर्णांक sm_disk_copy_root(काष्ठा dm_space_map *sm, व्योम *where_le, माप_प्रकार max)
अणु
	काष्ठा sm_disk *smd = container_of(sm, काष्ठा sm_disk, sm);
	काष्ठा disk_sm_root root_le;

	root_le.nr_blocks = cpu_to_le64(smd->ll.nr_blocks);
	root_le.nr_allocated = cpu_to_le64(smd->ll.nr_allocated);
	root_le.biपंचांगap_root = cpu_to_le64(smd->ll.biपंचांगap_root);
	root_le.ref_count_root = cpu_to_le64(smd->ll.ref_count_root);

	अगर (max < माप(root_le))
		वापस -ENOSPC;

	स_नकल(where_le, &root_le, माप(root_le));

	वापस 0;
पूर्ण

/*----------------------------------------------------------------*/

अटल काष्ठा dm_space_map ops = अणु
	.destroy = sm_disk_destroy,
	.extend = sm_disk_extend,
	.get_nr_blocks = sm_disk_get_nr_blocks,
	.get_nr_मुक्त = sm_disk_get_nr_मुक्त,
	.get_count = sm_disk_get_count,
	.count_is_more_than_one = sm_disk_count_is_more_than_one,
	.set_count = sm_disk_set_count,
	.inc_block = sm_disk_inc_block,
	.dec_block = sm_disk_dec_block,
	.new_block = sm_disk_new_block,
	.commit = sm_disk_commit,
	.root_size = sm_disk_root_size,
	.copy_root = sm_disk_copy_root,
	.रेजिस्टर_threshold_callback = शून्य
पूर्ण;

काष्ठा dm_space_map *dm_sm_disk_create(काष्ठा dm_transaction_manager *पंचांग,
				       dm_block_t nr_blocks)
अणु
	पूर्णांक r;
	काष्ठा sm_disk *smd;

	smd = kदो_स्मृति(माप(*smd), GFP_KERNEL);
	अगर (!smd)
		वापस ERR_PTR(-ENOMEM);

	smd->begin = 0;
	smd->nr_allocated_this_transaction = 0;
	स_नकल(&smd->sm, &ops, माप(smd->sm));

	r = sm_ll_new_disk(&smd->ll, पंचांग);
	अगर (r)
		जाओ bad;

	r = sm_ll_extend(&smd->ll, nr_blocks);
	अगर (r)
		जाओ bad;

	r = sm_disk_commit(&smd->sm);
	अगर (r)
		जाओ bad;

	वापस &smd->sm;

bad:
	kमुक्त(smd);
	वापस ERR_PTR(r);
पूर्ण
EXPORT_SYMBOL_GPL(dm_sm_disk_create);

काष्ठा dm_space_map *dm_sm_disk_खोलो(काष्ठा dm_transaction_manager *पंचांग,
				     व्योम *root_le, माप_प्रकार len)
अणु
	पूर्णांक r;
	काष्ठा sm_disk *smd;

	smd = kदो_स्मृति(माप(*smd), GFP_KERNEL);
	अगर (!smd)
		वापस ERR_PTR(-ENOMEM);

	smd->begin = 0;
	smd->nr_allocated_this_transaction = 0;
	स_नकल(&smd->sm, &ops, माप(smd->sm));

	r = sm_ll_खोलो_disk(&smd->ll, पंचांग, root_le, len);
	अगर (r)
		जाओ bad;

	r = sm_disk_commit(&smd->sm);
	अगर (r)
		जाओ bad;

	वापस &smd->sm;

bad:
	kमुक्त(smd);
	वापस ERR_PTR(r);
पूर्ण
EXPORT_SYMBOL_GPL(dm_sm_disk_खोलो);

/*----------------------------------------------------------------*/
