<शैली गुरु>
/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */
#समावेश "dm-transaction-manager.h"
#समावेश "dm-space-map.h"
#समावेश "dm-space-map-disk.h"
#समावेश "dm-space-map-metadata.h"
#समावेश "dm-persistent-data-internal.h"

#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/hash.h>
#समावेश <linux/slab.h>
#समावेश <linux/device-mapper.h>

#घोषणा DM_MSG_PREFIX "transaction manager"

/*----------------------------------------------------------------*/

#घोषणा PREFETCH_SIZE 128
#घोषणा PREFETCH_BITS 7
#घोषणा PREFETCH_SENTINEL ((dm_block_t) -1ULL)

काष्ठा prefetch_set अणु
	काष्ठा mutex lock;
	dm_block_t blocks[PREFETCH_SIZE];
पूर्ण;

अटल अचिन्हित prefetch_hash(dm_block_t b)
अणु
	वापस hash_64(b, PREFETCH_BITS);
पूर्ण

अटल व्योम prefetch_wipe(काष्ठा prefetch_set *p)
अणु
	अचिन्हित i;
	क्रम (i = 0; i < PREFETCH_SIZE; i++)
		p->blocks[i] = PREFETCH_SENTINEL;
पूर्ण

अटल व्योम prefetch_init(काष्ठा prefetch_set *p)
अणु
	mutex_init(&p->lock);
	prefetch_wipe(p);
पूर्ण

अटल व्योम prefetch_add(काष्ठा prefetch_set *p, dm_block_t b)
अणु
	अचिन्हित h = prefetch_hash(b);

	mutex_lock(&p->lock);
	अगर (p->blocks[h] == PREFETCH_SENTINEL)
		p->blocks[h] = b;

	mutex_unlock(&p->lock);
पूर्ण

अटल व्योम prefetch_issue(काष्ठा prefetch_set *p, काष्ठा dm_block_manager *bm)
अणु
	अचिन्हित i;

	mutex_lock(&p->lock);

	क्रम (i = 0; i < PREFETCH_SIZE; i++)
		अगर (p->blocks[i] != PREFETCH_SENTINEL) अणु
			dm_bm_prefetch(bm, p->blocks[i]);
			p->blocks[i] = PREFETCH_SENTINEL;
		पूर्ण

	mutex_unlock(&p->lock);
पूर्ण

/*----------------------------------------------------------------*/

काष्ठा shaकरोw_info अणु
	काष्ठा hlist_node hlist;
	dm_block_t where;
पूर्ण;

/*
 * It would be nice अगर we scaled with the size of transaction.
 */
#घोषणा DM_HASH_SIZE 256
#घोषणा DM_HASH_MASK (DM_HASH_SIZE - 1)

काष्ठा dm_transaction_manager अणु
	पूर्णांक is_clone;
	काष्ठा dm_transaction_manager *real;

	काष्ठा dm_block_manager *bm;
	काष्ठा dm_space_map *sm;

	spinlock_t lock;
	काष्ठा hlist_head buckets[DM_HASH_SIZE];

	काष्ठा prefetch_set prefetches;
पूर्ण;

/*----------------------------------------------------------------*/

अटल पूर्णांक is_shaकरोw(काष्ठा dm_transaction_manager *पंचांग, dm_block_t b)
अणु
	पूर्णांक r = 0;
	अचिन्हित bucket = dm_hash_block(b, DM_HASH_MASK);
	काष्ठा shaकरोw_info *si;

	spin_lock(&पंचांग->lock);
	hlist_क्रम_each_entry(si, पंचांग->buckets + bucket, hlist)
		अगर (si->where == b) अणु
			r = 1;
			अवरोध;
		पूर्ण
	spin_unlock(&पंचांग->lock);

	वापस r;
पूर्ण

/*
 * This can silently fail अगर there's no memory.  We're ok with this since
 * creating redundant shaकरोws causes no harm.
 */
अटल व्योम insert_shaकरोw(काष्ठा dm_transaction_manager *पंचांग, dm_block_t b)
अणु
	अचिन्हित bucket;
	काष्ठा shaकरोw_info *si;

	si = kदो_स्मृति(माप(*si), GFP_NOIO);
	अगर (si) अणु
		si->where = b;
		bucket = dm_hash_block(b, DM_HASH_MASK);
		spin_lock(&पंचांग->lock);
		hlist_add_head(&si->hlist, पंचांग->buckets + bucket);
		spin_unlock(&पंचांग->lock);
	पूर्ण
पूर्ण

अटल व्योम wipe_shaकरोw_table(काष्ठा dm_transaction_manager *पंचांग)
अणु
	काष्ठा shaकरोw_info *si;
	काष्ठा hlist_node *पंचांगp;
	काष्ठा hlist_head *bucket;
	पूर्णांक i;

	spin_lock(&पंचांग->lock);
	क्रम (i = 0; i < DM_HASH_SIZE; i++) अणु
		bucket = पंचांग->buckets + i;
		hlist_क्रम_each_entry_safe(si, पंचांगp, bucket, hlist)
			kमुक्त(si);

		INIT_HLIST_HEAD(bucket);
	पूर्ण

	spin_unlock(&पंचांग->lock);
पूर्ण

/*----------------------------------------------------------------*/

अटल काष्ठा dm_transaction_manager *dm_पंचांग_create(काष्ठा dm_block_manager *bm,
						   काष्ठा dm_space_map *sm)
अणु
	पूर्णांक i;
	काष्ठा dm_transaction_manager *पंचांग;

	पंचांग = kदो_स्मृति(माप(*पंचांग), GFP_KERNEL);
	अगर (!पंचांग)
		वापस ERR_PTR(-ENOMEM);

	पंचांग->is_clone = 0;
	पंचांग->real = शून्य;
	पंचांग->bm = bm;
	पंचांग->sm = sm;

	spin_lock_init(&पंचांग->lock);
	क्रम (i = 0; i < DM_HASH_SIZE; i++)
		INIT_HLIST_HEAD(पंचांग->buckets + i);

	prefetch_init(&पंचांग->prefetches);

	वापस पंचांग;
पूर्ण

काष्ठा dm_transaction_manager *dm_पंचांग_create_non_blocking_clone(काष्ठा dm_transaction_manager *real)
अणु
	काष्ठा dm_transaction_manager *पंचांग;

	पंचांग = kदो_स्मृति(माप(*पंचांग), GFP_KERNEL);
	अगर (पंचांग) अणु
		पंचांग->is_clone = 1;
		पंचांग->real = real;
	पूर्ण

	वापस पंचांग;
पूर्ण
EXPORT_SYMBOL_GPL(dm_पंचांग_create_non_blocking_clone);

व्योम dm_पंचांग_destroy(काष्ठा dm_transaction_manager *पंचांग)
अणु
	अगर (!पंचांग->is_clone)
		wipe_shaकरोw_table(पंचांग);

	kमुक्त(पंचांग);
पूर्ण
EXPORT_SYMBOL_GPL(dm_पंचांग_destroy);

पूर्णांक dm_पंचांग_pre_commit(काष्ठा dm_transaction_manager *पंचांग)
अणु
	पूर्णांक r;

	अगर (पंचांग->is_clone)
		वापस -EWOULDBLOCK;

	r = dm_sm_commit(पंचांग->sm);
	अगर (r < 0)
		वापस r;

	वापस dm_bm_flush(पंचांग->bm);
पूर्ण
EXPORT_SYMBOL_GPL(dm_पंचांग_pre_commit);

पूर्णांक dm_पंचांग_commit(काष्ठा dm_transaction_manager *पंचांग, काष्ठा dm_block *root)
अणु
	अगर (पंचांग->is_clone)
		वापस -EWOULDBLOCK;

	wipe_shaकरोw_table(पंचांग);
	dm_bm_unlock(root);

	वापस dm_bm_flush(पंचांग->bm);
पूर्ण
EXPORT_SYMBOL_GPL(dm_पंचांग_commit);

पूर्णांक dm_पंचांग_new_block(काष्ठा dm_transaction_manager *पंचांग,
		    काष्ठा dm_block_validator *v,
		    काष्ठा dm_block **result)
अणु
	पूर्णांक r;
	dm_block_t new_block;

	अगर (पंचांग->is_clone)
		वापस -EWOULDBLOCK;

	r = dm_sm_new_block(पंचांग->sm, &new_block);
	अगर (r < 0)
		वापस r;

	r = dm_bm_ग_लिखो_lock_zero(पंचांग->bm, new_block, v, result);
	अगर (r < 0) अणु
		dm_sm_dec_block(पंचांग->sm, new_block);
		वापस r;
	पूर्ण

	/*
	 * New blocks count as shaकरोws in that they करोn't need to be
	 * shaकरोwed again.
	 */
	insert_shaकरोw(पंचांग, new_block);

	वापस 0;
पूर्ण

अटल पूर्णांक __shaकरोw_block(काष्ठा dm_transaction_manager *पंचांग, dm_block_t orig,
			  काष्ठा dm_block_validator *v,
			  काष्ठा dm_block **result)
अणु
	पूर्णांक r;
	dm_block_t new;
	काष्ठा dm_block *orig_block;

	r = dm_sm_new_block(पंचांग->sm, &new);
	अगर (r < 0)
		वापस r;

	r = dm_sm_dec_block(पंचांग->sm, orig);
	अगर (r < 0)
		वापस r;

	r = dm_bm_पढ़ो_lock(पंचांग->bm, orig, v, &orig_block);
	अगर (r < 0)
		वापस r;

	/*
	 * It would be tempting to use dm_bm_unlock_move here, but some
	 * code, such as the space maps, keeps using the old data काष्ठाures
	 * secure in the knowledge they won't be changed until the next
	 * transaction.  Using unlock_move would क्रमce a synchronous पढ़ो
	 * since the old block would no दीर्घer be in the cache.
	 */
	r = dm_bm_ग_लिखो_lock_zero(पंचांग->bm, new, v, result);
	अगर (r) अणु
		dm_bm_unlock(orig_block);
		वापस r;
	पूर्ण

	स_नकल(dm_block_data(*result), dm_block_data(orig_block),
	       dm_bm_block_size(पंचांग->bm));

	dm_bm_unlock(orig_block);
	वापस r;
पूर्ण

पूर्णांक dm_पंचांग_shaकरोw_block(काष्ठा dm_transaction_manager *पंचांग, dm_block_t orig,
		       काष्ठा dm_block_validator *v, काष्ठा dm_block **result,
		       पूर्णांक *inc_children)
अणु
	पूर्णांक r;

	अगर (पंचांग->is_clone)
		वापस -EWOULDBLOCK;

	r = dm_sm_count_is_more_than_one(पंचांग->sm, orig, inc_children);
	अगर (r < 0)
		वापस r;

	अगर (is_shaकरोw(पंचांग, orig) && !*inc_children)
		वापस dm_bm_ग_लिखो_lock(पंचांग->bm, orig, v, result);

	r = __shaकरोw_block(पंचांग, orig, v, result);
	अगर (r < 0)
		वापस r;
	insert_shaकरोw(पंचांग, dm_block_location(*result));

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_पंचांग_shaकरोw_block);

पूर्णांक dm_पंचांग_पढ़ो_lock(काष्ठा dm_transaction_manager *पंचांग, dm_block_t b,
		    काष्ठा dm_block_validator *v,
		    काष्ठा dm_block **blk)
अणु
	अगर (पंचांग->is_clone) अणु
		पूर्णांक r = dm_bm_पढ़ो_try_lock(पंचांग->real->bm, b, v, blk);

		अगर (r == -EWOULDBLOCK)
			prefetch_add(&पंचांग->real->prefetches, b);

		वापस r;
	पूर्ण

	वापस dm_bm_पढ़ो_lock(पंचांग->bm, b, v, blk);
पूर्ण
EXPORT_SYMBOL_GPL(dm_पंचांग_पढ़ो_lock);

व्योम dm_पंचांग_unlock(काष्ठा dm_transaction_manager *पंचांग, काष्ठा dm_block *b)
अणु
	dm_bm_unlock(b);
पूर्ण
EXPORT_SYMBOL_GPL(dm_पंचांग_unlock);

व्योम dm_पंचांग_inc(काष्ठा dm_transaction_manager *पंचांग, dm_block_t b)
अणु
	/*
	 * The non-blocking clone करोesn't support this.
	 */
	BUG_ON(पंचांग->is_clone);

	dm_sm_inc_block(पंचांग->sm, b);
पूर्ण
EXPORT_SYMBOL_GPL(dm_पंचांग_inc);

व्योम dm_पंचांग_dec(काष्ठा dm_transaction_manager *पंचांग, dm_block_t b)
अणु
	/*
	 * The non-blocking clone करोesn't support this.
	 */
	BUG_ON(पंचांग->is_clone);

	dm_sm_dec_block(पंचांग->sm, b);
पूर्ण
EXPORT_SYMBOL_GPL(dm_पंचांग_dec);

पूर्णांक dm_पंचांग_ref(काष्ठा dm_transaction_manager *पंचांग, dm_block_t b,
	      uपूर्णांक32_t *result)
अणु
	अगर (पंचांग->is_clone)
		वापस -EWOULDBLOCK;

	वापस dm_sm_get_count(पंचांग->sm, b, result);
पूर्ण

काष्ठा dm_block_manager *dm_पंचांग_get_bm(काष्ठा dm_transaction_manager *पंचांग)
अणु
	वापस पंचांग->bm;
पूर्ण

व्योम dm_पंचांग_issue_prefetches(काष्ठा dm_transaction_manager *पंचांग)
अणु
	prefetch_issue(&पंचांग->prefetches, पंचांग->bm);
पूर्ण
EXPORT_SYMBOL_GPL(dm_पंचांग_issue_prefetches);

/*----------------------------------------------------------------*/

अटल पूर्णांक dm_पंचांग_create_पूर्णांकernal(काष्ठा dm_block_manager *bm,
				 dm_block_t sb_location,
				 काष्ठा dm_transaction_manager **पंचांग,
				 काष्ठा dm_space_map **sm,
				 पूर्णांक create,
				 व्योम *sm_root, माप_प्रकार sm_len)
अणु
	पूर्णांक r;

	*sm = dm_sm_metadata_init();
	अगर (IS_ERR(*sm))
		वापस PTR_ERR(*sm);

	*पंचांग = dm_पंचांग_create(bm, *sm);
	अगर (IS_ERR(*पंचांग)) अणु
		dm_sm_destroy(*sm);
		वापस PTR_ERR(*पंचांग);
	पूर्ण

	अगर (create) अणु
		r = dm_sm_metadata_create(*sm, *पंचांग, dm_bm_nr_blocks(bm),
					  sb_location);
		अगर (r) अणु
			DMERR("couldn't create metadata space map");
			जाओ bad;
		पूर्ण

	पूर्ण अन्यथा अणु
		r = dm_sm_metadata_खोलो(*sm, *पंचांग, sm_root, sm_len);
		अगर (r) अणु
			DMERR("couldn't open metadata space map");
			जाओ bad;
		पूर्ण
	पूर्ण

	वापस 0;

bad:
	dm_पंचांग_destroy(*पंचांग);
	dm_sm_destroy(*sm);
	वापस r;
पूर्ण

पूर्णांक dm_पंचांग_create_with_sm(काष्ठा dm_block_manager *bm, dm_block_t sb_location,
			 काष्ठा dm_transaction_manager **पंचांग,
			 काष्ठा dm_space_map **sm)
अणु
	वापस dm_पंचांग_create_पूर्णांकernal(bm, sb_location, पंचांग, sm, 1, शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(dm_पंचांग_create_with_sm);

पूर्णांक dm_पंचांग_खोलो_with_sm(काष्ठा dm_block_manager *bm, dm_block_t sb_location,
		       व्योम *sm_root, माप_प्रकार root_len,
		       काष्ठा dm_transaction_manager **पंचांग,
		       काष्ठा dm_space_map **sm)
अणु
	वापस dm_पंचांग_create_पूर्णांकernal(bm, sb_location, पंचांग, sm, 0, sm_root, root_len);
पूर्ण
EXPORT_SYMBOL_GPL(dm_पंचांग_खोलो_with_sm);

/*----------------------------------------------------------------*/
