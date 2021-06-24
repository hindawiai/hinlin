<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012 Linutronix GmbH
 * Copyright (c) 2014 sigma star gmbh
 * Author: Riअक्षरd Weinberger <riअक्षरd@nod.at>
 */

/**
 * update_fasपंचांगap_work_fn - calls ubi_update_fasपंचांगap from a work queue
 * @wrk: the work description object
 */
अटल व्योम update_fasपंचांगap_work_fn(काष्ठा work_काष्ठा *wrk)
अणु
	काष्ठा ubi_device *ubi = container_of(wrk, काष्ठा ubi_device, fm_work);

	ubi_update_fasपंचांगap(ubi);
	spin_lock(&ubi->wl_lock);
	ubi->fm_work_scheduled = 0;
	spin_unlock(&ubi->wl_lock);
पूर्ण

/**
 * find_anchor_wl_entry - find wear-leveling entry to used as anchor PEB.
 * @root: the RB-tree where to look क्रम
 */
अटल काष्ठा ubi_wl_entry *find_anchor_wl_entry(काष्ठा rb_root *root)
अणु
	काष्ठा rb_node *p;
	काष्ठा ubi_wl_entry *e, *victim = शून्य;
	पूर्णांक max_ec = UBI_MAX_ERASECOUNTER;

	ubi_rb_क्रम_each_entry(p, e, root, u.rb) अणु
		अगर (e->pnum < UBI_FM_MAX_START && e->ec < max_ec) अणु
			victim = e;
			max_ec = e->ec;
		पूर्ण
	पूर्ण

	वापस victim;
पूर्ण

अटल अंतरभूत व्योम वापस_unused_peb(काष्ठा ubi_device *ubi,
				     काष्ठा ubi_wl_entry *e)
अणु
	wl_tree_add(e, &ubi->मुक्त);
	ubi->मुक्त_count++;
पूर्ण

/**
 * वापस_unused_pool_pebs - वापसs unused PEB to the मुक्त tree.
 * @ubi: UBI device description object
 * @pool: fasपंचांगap pool description object
 */
अटल व्योम वापस_unused_pool_pebs(काष्ठा ubi_device *ubi,
				    काष्ठा ubi_fm_pool *pool)
अणु
	पूर्णांक i;
	काष्ठा ubi_wl_entry *e;

	क्रम (i = pool->used; i < pool->size; i++) अणु
		e = ubi->lookuptbl[pool->pebs[i]];
		वापस_unused_peb(ubi, e);
	पूर्ण
पूर्ण

/**
 * ubi_wl_get_fm_peb - find a physical erase block with a given maximal number.
 * @ubi: UBI device description object
 * @anchor: This PEB will be used as anchor PEB by fasपंचांगap
 *
 * The function वापसs a physical erase block with a given maximal number
 * and हटाओs it from the wl subप्रणाली.
 * Must be called with wl_lock held!
 */
काष्ठा ubi_wl_entry *ubi_wl_get_fm_peb(काष्ठा ubi_device *ubi, पूर्णांक anchor)
अणु
	काष्ठा ubi_wl_entry *e = शून्य;

	अगर (!ubi->मुक्त.rb_node || (ubi->मुक्त_count - ubi->beb_rsvd_pebs < 1))
		जाओ out;

	अगर (anchor)
		e = find_anchor_wl_entry(&ubi->मुक्त);
	अन्यथा
		e = find_mean_wl_entry(ubi, &ubi->मुक्त);

	अगर (!e)
		जाओ out;

	self_check_in_wl_tree(ubi, e, &ubi->मुक्त);

	/* हटाओ it from the मुक्त list,
	 * the wl subप्रणाली करोes no दीर्घer know this erase block */
	rb_erase(&e->u.rb, &ubi->मुक्त);
	ubi->मुक्त_count--;
out:
	वापस e;
पूर्ण

/**
 * ubi_refill_pools - refills all fasपंचांगap PEB pools.
 * @ubi: UBI device description object
 */
व्योम ubi_refill_pools(काष्ठा ubi_device *ubi)
अणु
	काष्ठा ubi_fm_pool *wl_pool = &ubi->fm_wl_pool;
	काष्ठा ubi_fm_pool *pool = &ubi->fm_pool;
	काष्ठा ubi_wl_entry *e;
	पूर्णांक enough;

	spin_lock(&ubi->wl_lock);

	वापस_unused_pool_pebs(ubi, wl_pool);
	वापस_unused_pool_pebs(ubi, pool);

	wl_pool->size = 0;
	pool->size = 0;

	अगर (ubi->fm_anchor) अणु
		wl_tree_add(ubi->fm_anchor, &ubi->मुक्त);
		ubi->मुक्त_count++;
	पूर्ण
	अगर (ubi->fm_next_anchor) अणु
		wl_tree_add(ubi->fm_next_anchor, &ubi->मुक्त);
		ubi->मुक्त_count++;
	पूर्ण

	/* All available PEBs are in ubi->मुक्त, now is the समय to get
	 * the best anchor PEBs.
	 */
	ubi->fm_anchor = ubi_wl_get_fm_peb(ubi, 1);
	ubi->fm_next_anchor = ubi_wl_get_fm_peb(ubi, 1);

	क्रम (;;) अणु
		enough = 0;
		अगर (pool->size < pool->max_size) अणु
			अगर (!ubi->मुक्त.rb_node)
				अवरोध;

			e = wl_get_wle(ubi);
			अगर (!e)
				अवरोध;

			pool->pebs[pool->size] = e->pnum;
			pool->size++;
		पूर्ण अन्यथा
			enough++;

		अगर (wl_pool->size < wl_pool->max_size) अणु
			अगर (!ubi->मुक्त.rb_node ||
			   (ubi->मुक्त_count - ubi->beb_rsvd_pebs < 5))
				अवरोध;

			e = find_wl_entry(ubi, &ubi->मुक्त, WL_FREE_MAX_DIFF);
			self_check_in_wl_tree(ubi, e, &ubi->मुक्त);
			rb_erase(&e->u.rb, &ubi->मुक्त);
			ubi->मुक्त_count--;

			wl_pool->pebs[wl_pool->size] = e->pnum;
			wl_pool->size++;
		पूर्ण अन्यथा
			enough++;

		अगर (enough == 2)
			अवरोध;
	पूर्ण

	wl_pool->used = 0;
	pool->used = 0;

	spin_unlock(&ubi->wl_lock);
पूर्ण

/**
 * produce_मुक्त_peb - produce a मुक्त physical eraseblock.
 * @ubi: UBI device description object
 *
 * This function tries to make a मुक्त PEB by means of synchronous execution of
 * pending works. This may be needed अगर, क्रम example the background thपढ़ो is
 * disabled. Returns zero in हाल of success and a negative error code in हाल
 * of failure.
 */
अटल पूर्णांक produce_मुक्त_peb(काष्ठा ubi_device *ubi)
अणु
	पूर्णांक err;

	जबतक (!ubi->मुक्त.rb_node && ubi->works_count) अणु
		dbg_wl("do one work synchronously");
		err = करो_work(ubi);

		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ubi_wl_get_peb - get a physical eraseblock.
 * @ubi: UBI device description object
 *
 * This function वापसs a physical eraseblock in हाल of success and a
 * negative error code in हाल of failure.
 * Returns with ubi->fm_eba_sem held in पढ़ो mode!
 */
पूर्णांक ubi_wl_get_peb(काष्ठा ubi_device *ubi)
अणु
	पूर्णांक ret, attempts = 0;
	काष्ठा ubi_fm_pool *pool = &ubi->fm_pool;
	काष्ठा ubi_fm_pool *wl_pool = &ubi->fm_wl_pool;

again:
	करोwn_पढ़ो(&ubi->fm_eba_sem);
	spin_lock(&ubi->wl_lock);

	/* We check here also क्रम the WL pool because at this poपूर्णांक we can
	 * refill the WL pool synchronous. */
	अगर (pool->used == pool->size || wl_pool->used == wl_pool->size) अणु
		spin_unlock(&ubi->wl_lock);
		up_पढ़ो(&ubi->fm_eba_sem);
		ret = ubi_update_fasपंचांगap(ubi);
		अगर (ret) अणु
			ubi_msg(ubi, "Unable to write a new fastmap: %i", ret);
			करोwn_पढ़ो(&ubi->fm_eba_sem);
			वापस -ENOSPC;
		पूर्ण
		करोwn_पढ़ो(&ubi->fm_eba_sem);
		spin_lock(&ubi->wl_lock);
	पूर्ण

	अगर (pool->used == pool->size) अणु
		spin_unlock(&ubi->wl_lock);
		attempts++;
		अगर (attempts == 10) अणु
			ubi_err(ubi, "Unable to get a free PEB from user WL pool");
			ret = -ENOSPC;
			जाओ out;
		पूर्ण
		up_पढ़ो(&ubi->fm_eba_sem);
		ret = produce_मुक्त_peb(ubi);
		अगर (ret < 0) अणु
			करोwn_पढ़ो(&ubi->fm_eba_sem);
			जाओ out;
		पूर्ण
		जाओ again;
	पूर्ण

	ubi_निश्चित(pool->used < pool->size);
	ret = pool->pebs[pool->used++];
	prot_queue_add(ubi, ubi->lookuptbl[ret]);
	spin_unlock(&ubi->wl_lock);
out:
	वापस ret;
पूर्ण

/* get_peb_क्रम_wl - वापसs a PEB to be used पूर्णांकernally by the WL sub-प्रणाली.
 *
 * @ubi: UBI device description object
 */
अटल काष्ठा ubi_wl_entry *get_peb_क्रम_wl(काष्ठा ubi_device *ubi)
अणु
	काष्ठा ubi_fm_pool *pool = &ubi->fm_wl_pool;
	पूर्णांक pnum;

	ubi_निश्चित(rwsem_is_locked(&ubi->fm_eba_sem));

	अगर (pool->used == pool->size) अणु
		/* We cannot update the fasपंचांगap here because this
		 * function is called in atomic context.
		 * Let's fail here and refill/update it as soon as possible. */
		अगर (!ubi->fm_work_scheduled) अणु
			ubi->fm_work_scheduled = 1;
			schedule_work(&ubi->fm_work);
		पूर्ण
		वापस शून्य;
	पूर्ण

	pnum = pool->pebs[pool->used++];
	वापस ubi->lookuptbl[pnum];
पूर्ण

/**
 * ubi_ensure_anchor_pebs - schedule wear-leveling to produce an anchor PEB.
 * @ubi: UBI device description object
 */
पूर्णांक ubi_ensure_anchor_pebs(काष्ठा ubi_device *ubi)
अणु
	काष्ठा ubi_work *wrk;

	spin_lock(&ubi->wl_lock);

	/* Do we have a next anchor? */
	अगर (!ubi->fm_next_anchor) अणु
		ubi->fm_next_anchor = ubi_wl_get_fm_peb(ubi, 1);
		अगर (!ubi->fm_next_anchor)
			/* Tell wear leveling to produce a new anchor PEB */
			ubi->fm_करो_produce_anchor = 1;
	पूर्ण

	/* Do wear leveling to get a new anchor PEB or check the
	 * existing next anchor candidate.
	 */
	अगर (ubi->wl_scheduled) अणु
		spin_unlock(&ubi->wl_lock);
		वापस 0;
	पूर्ण
	ubi->wl_scheduled = 1;
	spin_unlock(&ubi->wl_lock);

	wrk = kदो_स्मृति(माप(काष्ठा ubi_work), GFP_NOFS);
	अगर (!wrk) अणु
		spin_lock(&ubi->wl_lock);
		ubi->wl_scheduled = 0;
		spin_unlock(&ubi->wl_lock);
		वापस -ENOMEM;
	पूर्ण

	wrk->func = &wear_leveling_worker;
	__schedule_ubi_work(ubi, wrk);
	वापस 0;
पूर्ण

/**
 * ubi_wl_put_fm_peb - वापसs a PEB used in a fasपंचांगap to the wear-leveling
 * sub-प्रणाली.
 * see: ubi_wl_put_peb()
 *
 * @ubi: UBI device description object
 * @fm_e: physical eraseblock to वापस
 * @lnum: the last used logical eraseblock number क्रम the PEB
 * @torture: अगर this physical eraseblock has to be tortured
 */
पूर्णांक ubi_wl_put_fm_peb(काष्ठा ubi_device *ubi, काष्ठा ubi_wl_entry *fm_e,
		      पूर्णांक lnum, पूर्णांक torture)
अणु
	काष्ठा ubi_wl_entry *e;
	पूर्णांक vol_id, pnum = fm_e->pnum;

	dbg_wl("PEB %d", pnum);

	ubi_निश्चित(pnum >= 0);
	ubi_निश्चित(pnum < ubi->peb_count);

	spin_lock(&ubi->wl_lock);
	e = ubi->lookuptbl[pnum];

	/* This can happen अगर we recovered from a fasपंचांगap the very
	 * first समय and writing now a new one. In this हाल the wl प्रणाली
	 * has never seen any PEB used by the original fasपंचांगap.
	 */
	अगर (!e) अणु
		e = fm_e;
		ubi_निश्चित(e->ec >= 0);
		ubi->lookuptbl[pnum] = e;
	पूर्ण

	spin_unlock(&ubi->wl_lock);

	vol_id = lnum ? UBI_FM_DATA_VOLUME_ID : UBI_FM_SB_VOLUME_ID;
	वापस schedule_erase(ubi, e, vol_id, lnum, torture, true);
पूर्ण

/**
 * ubi_is_erase_work - checks whether a work is erase work.
 * @wrk: The work object to be checked
 */
पूर्णांक ubi_is_erase_work(काष्ठा ubi_work *wrk)
अणु
	वापस wrk->func == erase_worker;
पूर्ण

अटल व्योम ubi_fasपंचांगap_बंद(काष्ठा ubi_device *ubi)
अणु
	पूर्णांक i;

	वापस_unused_pool_pebs(ubi, &ubi->fm_pool);
	वापस_unused_pool_pebs(ubi, &ubi->fm_wl_pool);

	अगर (ubi->fm_anchor) अणु
		वापस_unused_peb(ubi, ubi->fm_anchor);
		ubi->fm_anchor = शून्य;
	पूर्ण

	अगर (ubi->fm_next_anchor) अणु
		वापस_unused_peb(ubi, ubi->fm_next_anchor);
		ubi->fm_next_anchor = शून्य;
	पूर्ण

	अगर (ubi->fm) अणु
		क्रम (i = 0; i < ubi->fm->used_blocks; i++)
			kमुक्त(ubi->fm->e[i]);
	पूर्ण
	kमुक्त(ubi->fm);
पूर्ण

/**
 * may_reserve_क्रम_fm - tests whether a PEB shall be reserved क्रम fasपंचांगap.
 * See find_mean_wl_entry()
 *
 * @ubi: UBI device description object
 * @e: physical eraseblock to वापस
 * @root: RB tree to test against.
 */
अटल काष्ठा ubi_wl_entry *may_reserve_क्रम_fm(काष्ठा ubi_device *ubi,
					   काष्ठा ubi_wl_entry *e,
					   काष्ठा rb_root *root) अणु
	अगर (e && !ubi->fm_disabled && !ubi->fm &&
	    e->pnum < UBI_FM_MAX_START)
		e = rb_entry(rb_next(root->rb_node),
			     काष्ठा ubi_wl_entry, u.rb);

	वापस e;
पूर्ण
