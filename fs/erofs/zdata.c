<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Created by Gao Xiang <gaoxiang25@huawei.com>
 */
#समावेश "zdata.h"
#समावेश "compress.h"
#समावेश <linux/prefetch.h>

#समावेश <trace/events/erofs.h>

/*
 * since pclustersize is variable क्रम big pcluster feature, पूर्णांकroduce slab
 * pools implementation क्रम dअगरferent pcluster sizes.
 */
काष्ठा z_erofs_pcluster_slab अणु
	काष्ठा kmem_cache *slab;
	अचिन्हित पूर्णांक maxpages;
	अक्षर name[48];
पूर्ण;

#घोषणा _PCLP(n) अणु .maxpages = n पूर्ण

अटल काष्ठा z_erofs_pcluster_slab pcluster_pool[] __पढ़ो_mostly = अणु
	_PCLP(1), _PCLP(4), _PCLP(16), _PCLP(64), _PCLP(128),
	_PCLP(Z_EROFS_PCLUSTER_MAX_PAGES)
पूर्ण;

अटल व्योम z_erofs_destroy_pcluster_pool(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pcluster_pool); ++i) अणु
		अगर (!pcluster_pool[i].slab)
			जारी;
		kmem_cache_destroy(pcluster_pool[i].slab);
		pcluster_pool[i].slab = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक z_erofs_create_pcluster_pool(व्योम)
अणु
	काष्ठा z_erofs_pcluster_slab *pcs;
	काष्ठा z_erofs_pcluster *a;
	अचिन्हित पूर्णांक size;

	क्रम (pcs = pcluster_pool;
	     pcs < pcluster_pool + ARRAY_SIZE(pcluster_pool); ++pcs) अणु
		size = काष्ठा_size(a, compressed_pages, pcs->maxpages);

		प्र_लिखो(pcs->name, "erofs_pcluster-%u", pcs->maxpages);
		pcs->slab = kmem_cache_create(pcs->name, size, 0,
					      SLAB_RECLAIM_ACCOUNT, शून्य);
		अगर (pcs->slab)
			जारी;

		z_erofs_destroy_pcluster_pool();
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा z_erofs_pcluster *z_erofs_alloc_pcluster(अचिन्हित पूर्णांक nrpages)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pcluster_pool); ++i) अणु
		काष्ठा z_erofs_pcluster_slab *pcs = pcluster_pool + i;
		काष्ठा z_erofs_pcluster *pcl;

		अगर (nrpages > pcs->maxpages)
			जारी;

		pcl = kmem_cache_zalloc(pcs->slab, GFP_NOFS);
		अगर (!pcl)
			वापस ERR_PTR(-ENOMEM);
		pcl->pclusterpages = nrpages;
		वापस pcl;
	पूर्ण
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल व्योम z_erofs_मुक्त_pcluster(काष्ठा z_erofs_pcluster *pcl)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pcluster_pool); ++i) अणु
		काष्ठा z_erofs_pcluster_slab *pcs = pcluster_pool + i;

		अगर (pcl->pclusterpages > pcs->maxpages)
			जारी;

		kmem_cache_मुक्त(pcs->slab, pcl);
		वापस;
	पूर्ण
	DBG_BUGON(1);
पूर्ण

/*
 * a compressed_pages[] placeholder in order to aव्योम
 * being filled with file pages क्रम in-place decompression.
 */
#घोषणा PAGE_UNALLOCATED     ((व्योम *)0x5F0E4B1D)

/* how to allocate cached pages क्रम a pcluster */
क्रमागत z_erofs_cache_alloctype अणु
	DONTALLOC,	/* करोn't allocate any cached pages */
	DELAYEDALLOC,	/* delayed allocation (at the समय of submitting io) */
	/*
	 * try to use cached I/O अगर page allocation succeeds or fallback
	 * to in-place I/O instead to aव्योम any direct reclaim.
	 */
	TRYALLOC,
पूर्ण;

/*
 * tagged poपूर्णांकer with 1-bit tag क्रम all compressed pages
 * tag 0 - the page is just found with an extra page reference
 */
प्रकार tagptr1_t compressed_page_t;

#घोषणा tag_compressed_page_justfound(page) \
	tagptr_fold(compressed_page_t, page, 1)

अटल काष्ठा workqueue_काष्ठा *z_erofs_workqueue __पढ़ो_mostly;

व्योम z_erofs_निकास_zip_subप्रणाली(व्योम)
अणु
	destroy_workqueue(z_erofs_workqueue);
	z_erofs_destroy_pcluster_pool();
पूर्ण

अटल अंतरभूत पूर्णांक z_erofs_init_workqueue(व्योम)
अणु
	स्थिर अचिन्हित पूर्णांक onlinecpus = num_possible_cpus();

	/*
	 * no need to spawn too many thपढ़ोs, limiting thपढ़ोs could minimum
	 * scheduling overhead, perhaps per-CPU thपढ़ोs should be better?
	 */
	z_erofs_workqueue = alloc_workqueue("erofs_unzipd",
					    WQ_UNBOUND | WQ_HIGHPRI,
					    onlinecpus + onlinecpus / 4);
	वापस z_erofs_workqueue ? 0 : -ENOMEM;
पूर्ण

पूर्णांक __init z_erofs_init_zip_subप्रणाली(व्योम)
अणु
	पूर्णांक err = z_erofs_create_pcluster_pool();

	अगर (err)
		वापस err;
	err = z_erofs_init_workqueue();
	अगर (err)
		z_erofs_destroy_pcluster_pool();
	वापस err;
पूर्ण

क्रमागत z_erofs_collecपंचांगode अणु
	COLLECT_SECONDARY,
	COLLECT_PRIMARY,
	/*
	 * The current collection was the tail of an exist chain, in addition
	 * that the previous processed chained collections are all decided to
	 * be hooked up to it.
	 * A new chain will be created क्रम the reमुख्यing collections which are
	 * not processed yet, thereक्रमe dअगरferent from COLLECT_PRIMARY_FOLLOWED,
	 * the next collection cannot reuse the whole page safely in
	 * the following scenario:
	 *  ________________________________________________________________
	 * |      tail (partial) page     |       head (partial) page       |
	 * |   (beदीर्घs to the next cl)   |   (beदीर्घs to the current cl)   |
	 * |_______PRIMARY_FOLLOWED_______|________PRIMARY_HOOKED___________|
	 */
	COLLECT_PRIMARY_HOOKED,
	/*
	 * a weak क्रमm of COLLECT_PRIMARY_FOLLOWED, the dअगरference is that it
	 * could be dispatched पूर्णांकo bypass queue later due to uptodated managed
	 * pages. All related online pages cannot be reused क्रम inplace I/O (or
	 * pagevec) since it can be directly decoded without I/O submission.
	 */
	COLLECT_PRIMARY_FOLLOWED_NOINPLACE,
	/*
	 * The current collection has been linked with the owned chain, and
	 * could also be linked with the reमुख्यing collections, which means
	 * अगर the processing page is the tail page of the collection, thus
	 * the current collection can safely use the whole page (since
	 * the previous collection is under control) क्रम in-place I/O, as
	 * illustrated below:
	 *  ________________________________________________________________
	 * |  tail (partial) page |          head (partial) page           |
	 * |  (of the current cl) |      (of the previous collection)      |
	 * |  PRIMARY_FOLLOWED or |                                        |
	 * |_____PRIMARY_HOOKED___|____________PRIMARY_FOLLOWED____________|
	 *
	 * [  (*) the above page can be used as inplace I/O.               ]
	 */
	COLLECT_PRIMARY_FOLLOWED,
पूर्ण;

काष्ठा z_erofs_collector अणु
	काष्ठा z_erofs_pagevec_ctor vector;

	काष्ठा z_erofs_pcluster *pcl, *tailpcl;
	काष्ठा z_erofs_collection *cl;
	/* a poपूर्णांकer used to pick up inplace I/O pages */
	काष्ठा page **icpage_ptr;
	z_erofs_next_pcluster_t owned_head;

	क्रमागत z_erofs_collecपंचांगode mode;
पूर्ण;

काष्ठा z_erofs_decompress_frontend अणु
	काष्ठा inode *स्थिर inode;

	काष्ठा z_erofs_collector clt;
	काष्ठा erofs_map_blocks map;

	bool पढ़ोahead;
	/* used क्रम applying cache strategy on the fly */
	bool backmost;
	erofs_off_t heaकरोffset;
पूर्ण;

#घोषणा COLLECTOR_INIT() अणु \
	.owned_head = Z_EROFS_PCLUSTER_TAIL, \
	.mode = COLLECT_PRIMARY_FOLLOWED पूर्ण

#घोषणा DECOMPRESS_FRONTEND_INIT(__i) अणु \
	.inode = __i, .clt = COLLECTOR_INIT(), \
	.backmost = true, पूर्ण

अटल काष्ठा page *z_pagemap_global[Z_EROFS_VMAP_GLOBAL_PAGES];
अटल DEFINE_MUTEX(z_pagemap_global_lock);

अटल व्योम preload_compressed_pages(काष्ठा z_erofs_collector *clt,
				     काष्ठा address_space *mc,
				     क्रमागत z_erofs_cache_alloctype type,
				     काष्ठा list_head *pagepool)
अणु
	काष्ठा z_erofs_pcluster *pcl = clt->pcl;
	bool standalone = true;
	gfp_t gfp = (mapping_gfp_mask(mc) & ~__GFP_सूचीECT_RECLAIM) |
			__GFP_NOMEMALLOC | __GFP_NORETRY | __GFP_NOWARN;
	काष्ठा page **pages;
	pgoff_t index;

	अगर (clt->mode < COLLECT_PRIMARY_FOLLOWED)
		वापस;

	pages = pcl->compressed_pages;
	index = pcl->obj.index;
	क्रम (; index < pcl->obj.index + pcl->pclusterpages; ++index, ++pages) अणु
		काष्ठा page *page;
		compressed_page_t t;
		काष्ठा page *newpage = शून्य;

		/* the compressed page was loaded beक्रमe */
		अगर (READ_ONCE(*pages))
			जारी;

		page = find_get_page(mc, index);

		अगर (page) अणु
			t = tag_compressed_page_justfound(page);
		पूर्ण अन्यथा अणु
			/* I/O is needed, no possible to decompress directly */
			standalone = false;
			चयन (type) अणु
			हाल DELAYEDALLOC:
				t = tagptr_init(compressed_page_t,
						PAGE_UNALLOCATED);
				अवरोध;
			हाल TRYALLOC:
				newpage = erofs_allocpage(pagepool, gfp);
				अगर (!newpage)
					जारी;
				set_page_निजी(newpage,
						 Z_EROFS_PREALLOCATED_PAGE);
				t = tag_compressed_page_justfound(newpage);
				अवरोध;
			शेष:        /* DONTALLOC */
				जारी;
			पूर्ण
		पूर्ण

		अगर (!cmpxchg_relaxed(pages, शून्य, tagptr_cast_ptr(t)))
			जारी;

		अगर (page) अणु
			put_page(page);
		पूर्ण अन्यथा अगर (newpage) अणु
			set_page_निजी(newpage, 0);
			list_add(&newpage->lru, pagepool);
		पूर्ण
	पूर्ण

	/*
	 * करोn't करो inplace I/O अगर all compressed pages are available in
	 * managed cache since it can be moved to the bypass queue instead.
	 */
	अगर (standalone)
		clt->mode = COLLECT_PRIMARY_FOLLOWED_NOINPLACE;
पूर्ण

/* called by erofs_shrinker to get rid of all compressed_pages */
पूर्णांक erofs_try_to_मुक्त_all_cached_pages(काष्ठा erofs_sb_info *sbi,
				       काष्ठा erofs_workgroup *grp)
अणु
	काष्ठा z_erofs_pcluster *स्थिर pcl =
		container_of(grp, काष्ठा z_erofs_pcluster, obj);
	काष्ठा address_space *स्थिर mapping = MNGD_MAPPING(sbi);
	पूर्णांक i;

	/*
	 * refcount of workgroup is now मुक्तzed as 1,
	 * thereक्रमe no need to worry about available decompression users.
	 */
	क्रम (i = 0; i < pcl->pclusterpages; ++i) अणु
		काष्ठा page *page = pcl->compressed_pages[i];

		अगर (!page)
			जारी;

		/* block other users from reclaiming or migrating the page */
		अगर (!trylock_page(page))
			वापस -EBUSY;

		अगर (page->mapping != mapping)
			जारी;

		/* barrier is implied in the following 'unlock_page' */
		WRITE_ONCE(pcl->compressed_pages[i], शून्य);
		detach_page_निजी(page);
		unlock_page(page);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक erofs_try_to_मुक्त_cached_page(काष्ठा address_space *mapping,
				  काष्ठा page *page)
अणु
	काष्ठा z_erofs_pcluster *स्थिर pcl = (व्योम *)page_निजी(page);
	पूर्णांक ret = 0;	/* 0 - busy */

	अगर (erofs_workgroup_try_to_मुक्तze(&pcl->obj, 1)) अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < pcl->pclusterpages; ++i) अणु
			अगर (pcl->compressed_pages[i] == page) अणु
				WRITE_ONCE(pcl->compressed_pages[i], शून्य);
				ret = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		erofs_workgroup_unमुक्तze(&pcl->obj, 1);

		अगर (ret)
			detach_page_निजी(page);
	पूर्ण
	वापस ret;
पूर्ण

/* page_type must be Z_EROFS_PAGE_TYPE_EXCLUSIVE */
अटल bool z_erofs_try_inplace_io(काष्ठा z_erofs_collector *clt,
				   काष्ठा page *page)
अणु
	काष्ठा z_erofs_pcluster *स्थिर pcl = clt->pcl;

	जबतक (clt->icpage_ptr > pcl->compressed_pages)
		अगर (!cmpxchg(--clt->icpage_ptr, शून्य, page))
			वापस true;
	वापस false;
पूर्ण

/* callers must be with collection lock held */
अटल पूर्णांक z_erofs_attach_page(काष्ठा z_erofs_collector *clt,
			       काष्ठा page *page,
			       क्रमागत z_erofs_page_type type)
अणु
	पूर्णांक ret;
	bool occupied;

	/* give priority क्रम inplaceio */
	अगर (clt->mode >= COLLECT_PRIMARY &&
	    type == Z_EROFS_PAGE_TYPE_EXCLUSIVE &&
	    z_erofs_try_inplace_io(clt, page))
		वापस 0;

	ret = z_erofs_pagevec_enqueue(&clt->vector,
				      page, type, &occupied);
	clt->cl->vcnt += (अचिन्हित पूर्णांक)ret;

	वापस ret ? 0 : -EAGAIN;
पूर्ण

अटल व्योम z_erofs_try_to_claim_pcluster(काष्ठा z_erofs_collector *clt)
अणु
	काष्ठा z_erofs_pcluster *pcl = clt->pcl;
	z_erofs_next_pcluster_t *owned_head = &clt->owned_head;

	/* type 1, nil pcluster (this pcluster करोesn't beदीर्घ to any chain.) */
	अगर (cmpxchg(&pcl->next, Z_EROFS_PCLUSTER_NIL,
		    *owned_head) == Z_EROFS_PCLUSTER_NIL) अणु
		*owned_head = &pcl->next;
		/* so we can attach this pcluster to our submission chain. */
		clt->mode = COLLECT_PRIMARY_FOLLOWED;
		वापस;
	पूर्ण

	/*
	 * type 2, link to the end of an existing खोलो chain, be careful
	 * that its submission is controlled by the original attached chain.
	 */
	अगर (cmpxchg(&pcl->next, Z_EROFS_PCLUSTER_TAIL,
		    *owned_head) == Z_EROFS_PCLUSTER_TAIL) अणु
		*owned_head = Z_EROFS_PCLUSTER_TAIL;
		clt->mode = COLLECT_PRIMARY_HOOKED;
		clt->tailpcl = शून्य;
		वापस;
	पूर्ण
	/* type 3, it beदीर्घs to a chain, but it isn't the end of the chain */
	clt->mode = COLLECT_PRIMARY;
पूर्ण

अटल पूर्णांक z_erofs_lookup_collection(काष्ठा z_erofs_collector *clt,
				     काष्ठा inode *inode,
				     काष्ठा erofs_map_blocks *map)
अणु
	काष्ठा z_erofs_pcluster *pcl = clt->pcl;
	काष्ठा z_erofs_collection *cl;
	अचिन्हित पूर्णांक length;

	/* to aव्योम unexpected loop क्रमmed by corrupted images */
	अगर (clt->owned_head == &pcl->next || pcl == clt->tailpcl) अणु
		DBG_BUGON(1);
		वापस -EFSCORRUPTED;
	पूर्ण

	cl = z_erofs_primarycollection(pcl);
	अगर (cl->pageofs != (map->m_la & ~PAGE_MASK)) अणु
		DBG_BUGON(1);
		वापस -EFSCORRUPTED;
	पूर्ण

	length = READ_ONCE(pcl->length);
	अगर (length & Z_EROFS_PCLUSTER_FULL_LENGTH) अणु
		अगर ((map->m_llen << Z_EROFS_PCLUSTER_LENGTH_BIT) > length) अणु
			DBG_BUGON(1);
			वापस -EFSCORRUPTED;
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक llen = map->m_llen << Z_EROFS_PCLUSTER_LENGTH_BIT;

		अगर (map->m_flags & EROFS_MAP_FULL_MAPPED)
			llen |= Z_EROFS_PCLUSTER_FULL_LENGTH;

		जबतक (llen > length &&
		       length != cmpxchg_relaxed(&pcl->length, length, llen)) अणु
			cpu_relax();
			length = READ_ONCE(pcl->length);
		पूर्ण
	पूर्ण
	mutex_lock(&cl->lock);
	/* used to check tail merging loop due to corrupted images */
	अगर (clt->owned_head == Z_EROFS_PCLUSTER_TAIL)
		clt->tailpcl = pcl;

	z_erofs_try_to_claim_pcluster(clt);
	clt->cl = cl;
	वापस 0;
पूर्ण

अटल पूर्णांक z_erofs_रेजिस्टर_collection(काष्ठा z_erofs_collector *clt,
				       काष्ठा inode *inode,
				       काष्ठा erofs_map_blocks *map)
अणु
	काष्ठा z_erofs_pcluster *pcl;
	काष्ठा z_erofs_collection *cl;
	काष्ठा erofs_workgroup *grp;
	पूर्णांक err;

	/* no available pcluster, let's allocate one */
	pcl = z_erofs_alloc_pcluster(map->m_plen >> PAGE_SHIFT);
	अगर (IS_ERR(pcl))
		वापस PTR_ERR(pcl);

	atomic_set(&pcl->obj.refcount, 1);
	pcl->obj.index = map->m_pa >> PAGE_SHIFT;

	pcl->length = (map->m_llen << Z_EROFS_PCLUSTER_LENGTH_BIT) |
		(map->m_flags & EROFS_MAP_FULL_MAPPED ?
			Z_EROFS_PCLUSTER_FULL_LENGTH : 0);

	अगर (map->m_flags & EROFS_MAP_ZIPPED)
		pcl->algorithmक्रमmat = Z_EROFS_COMPRESSION_LZ4;
	अन्यथा
		pcl->algorithmक्रमmat = Z_EROFS_COMPRESSION_SHIFTED;

	/* new pclusters should be claimed as type 1, primary and followed */
	pcl->next = clt->owned_head;
	clt->mode = COLLECT_PRIMARY_FOLLOWED;

	cl = z_erofs_primarycollection(pcl);
	cl->pageofs = map->m_la & ~PAGE_MASK;

	/*
	 * lock all primary followed works beक्रमe visible to others
	 * and mutex_trylock *never* fails क्रम a new pcluster.
	 */
	mutex_init(&cl->lock);
	DBG_BUGON(!mutex_trylock(&cl->lock));

	grp = erofs_insert_workgroup(inode->i_sb, &pcl->obj);
	अगर (IS_ERR(grp)) अणु
		err = PTR_ERR(grp);
		जाओ err_out;
	पूर्ण

	अगर (grp != &pcl->obj) अणु
		clt->pcl = container_of(grp, काष्ठा z_erofs_pcluster, obj);
		err = -EEXIST;
		जाओ err_out;
	पूर्ण
	/* used to check tail merging loop due to corrupted images */
	अगर (clt->owned_head == Z_EROFS_PCLUSTER_TAIL)
		clt->tailpcl = pcl;
	clt->owned_head = &pcl->next;
	clt->pcl = pcl;
	clt->cl = cl;
	वापस 0;

err_out:
	mutex_unlock(&cl->lock);
	z_erofs_मुक्त_pcluster(pcl);
	वापस err;
पूर्ण

अटल पूर्णांक z_erofs_collector_begin(काष्ठा z_erofs_collector *clt,
				   काष्ठा inode *inode,
				   काष्ठा erofs_map_blocks *map)
अणु
	काष्ठा erofs_workgroup *grp;
	पूर्णांक ret;

	DBG_BUGON(clt->cl);

	/* must be Z_EROFS_PCLUSTER_TAIL or poपूर्णांकed to previous collection */
	DBG_BUGON(clt->owned_head == Z_EROFS_PCLUSTER_NIL);
	DBG_BUGON(clt->owned_head == Z_EROFS_PCLUSTER_TAIL_CLOSED);

	अगर (!PAGE_ALIGNED(map->m_pa)) अणु
		DBG_BUGON(1);
		वापस -EINVAL;
	पूर्ण

	grp = erofs_find_workgroup(inode->i_sb, map->m_pa >> PAGE_SHIFT);
	अगर (grp) अणु
		clt->pcl = container_of(grp, काष्ठा z_erofs_pcluster, obj);
	पूर्ण अन्यथा अणु
		ret = z_erofs_रेजिस्टर_collection(clt, inode, map);

		अगर (!ret)
			जाओ out;
		अगर (ret != -EEXIST)
			वापस ret;
	पूर्ण

	ret = z_erofs_lookup_collection(clt, inode, map);
	अगर (ret) अणु
		erofs_workgroup_put(&clt->pcl->obj);
		वापस ret;
	पूर्ण

out:
	z_erofs_pagevec_ctor_init(&clt->vector, Z_EROFS_NR_INLINE_PAGEVECS,
				  clt->cl->pagevec, clt->cl->vcnt);

	/* since file-backed online pages are traversed in reverse order */
	clt->icpage_ptr = clt->pcl->compressed_pages + clt->pcl->pclusterpages;
	वापस 0;
पूर्ण

/*
 * keep in mind that no referenced pclusters will be मुक्तd
 * only after a RCU grace period.
 */
अटल व्योम z_erofs_rcu_callback(काष्ठा rcu_head *head)
अणु
	काष्ठा z_erofs_collection *स्थिर cl =
		container_of(head, काष्ठा z_erofs_collection, rcu);

	z_erofs_मुक्त_pcluster(container_of(cl, काष्ठा z_erofs_pcluster,
					   primary_collection));
पूर्ण

व्योम erofs_workgroup_मुक्त_rcu(काष्ठा erofs_workgroup *grp)
अणु
	काष्ठा z_erofs_pcluster *स्थिर pcl =
		container_of(grp, काष्ठा z_erofs_pcluster, obj);
	काष्ठा z_erofs_collection *स्थिर cl = z_erofs_primarycollection(pcl);

	call_rcu(&cl->rcu, z_erofs_rcu_callback);
पूर्ण

अटल व्योम z_erofs_collection_put(काष्ठा z_erofs_collection *cl)
अणु
	काष्ठा z_erofs_pcluster *स्थिर pcl =
		container_of(cl, काष्ठा z_erofs_pcluster, primary_collection);

	erofs_workgroup_put(&pcl->obj);
पूर्ण

अटल bool z_erofs_collector_end(काष्ठा z_erofs_collector *clt)
अणु
	काष्ठा z_erofs_collection *cl = clt->cl;

	अगर (!cl)
		वापस false;

	z_erofs_pagevec_ctor_निकास(&clt->vector, false);
	mutex_unlock(&cl->lock);

	/*
	 * अगर all pending pages are added, करोn't hold its reference
	 * any दीर्घer अगर the pcluster isn't hosted by ourselves.
	 */
	अगर (clt->mode < COLLECT_PRIMARY_FOLLOWED_NOINPLACE)
		z_erofs_collection_put(cl);

	clt->cl = शून्य;
	वापस true;
पूर्ण

अटल bool should_alloc_managed_pages(काष्ठा z_erofs_decompress_frontend *fe,
				       अचिन्हित पूर्णांक cachestrategy,
				       erofs_off_t la)
अणु
	अगर (cachestrategy <= EROFS_ZIP_CACHE_DISABLED)
		वापस false;

	अगर (fe->backmost)
		वापस true;

	वापस cachestrategy >= EROFS_ZIP_CACHE_READAROUND &&
		la < fe->heaकरोffset;
पूर्ण

अटल पूर्णांक z_erofs_करो_पढ़ो_page(काष्ठा z_erofs_decompress_frontend *fe,
				काष्ठा page *page, काष्ठा list_head *pagepool)
अणु
	काष्ठा inode *स्थिर inode = fe->inode;
	काष्ठा erofs_sb_info *स्थिर sbi = EROFS_I_SB(inode);
	काष्ठा erofs_map_blocks *स्थिर map = &fe->map;
	काष्ठा z_erofs_collector *स्थिर clt = &fe->clt;
	स्थिर loff_t offset = page_offset(page);
	bool tight = true;

	क्रमागत z_erofs_cache_alloctype cache_strategy;
	क्रमागत z_erofs_page_type page_type;
	अचिन्हित पूर्णांक cur, end, spiltted, index;
	पूर्णांक err = 0;

	/* रेजिस्टर locked file pages as online pages in pack */
	z_erofs_onlinepage_init(page);

	spiltted = 0;
	end = PAGE_SIZE;
repeat:
	cur = end - 1;

	/* lucky, within the range of the current map_blocks */
	अगर (offset + cur >= map->m_la &&
	    offset + cur < map->m_la + map->m_llen) अणु
		/* didn't get a valid collection previously (very rare) */
		अगर (!clt->cl)
			जाओ restart_now;
		जाओ hitted;
	पूर्ण

	/* go ahead the next map_blocks */
	erofs_dbg("%s: [out-of-range] pos %llu", __func__, offset + cur);

	अगर (z_erofs_collector_end(clt))
		fe->backmost = false;

	map->m_la = offset + cur;
	map->m_llen = 0;
	err = z_erofs_map_blocks_iter(inode, map, 0);
	अगर (err)
		जाओ err_out;

restart_now:
	अगर (!(map->m_flags & EROFS_MAP_MAPPED))
		जाओ hitted;

	err = z_erofs_collector_begin(clt, inode, map);
	अगर (err)
		जाओ err_out;

	/* preload all compressed pages (maybe करोwngrade role अगर necessary) */
	अगर (should_alloc_managed_pages(fe, sbi->ctx.cache_strategy, map->m_la))
		cache_strategy = TRYALLOC;
	अन्यथा
		cache_strategy = DONTALLOC;

	preload_compressed_pages(clt, MNGD_MAPPING(sbi),
				 cache_strategy, pagepool);

hitted:
	/*
	 * Ensure the current partial page beदीर्घs to this submit chain rather
	 * than other concurrent submit chains or the noio(bypass) chain since
	 * those chains are handled asynchronously thus the page cannot be used
	 * क्रम inplace I/O or pagevec (should be processed in strict order.)
	 */
	tight &= (clt->mode >= COLLECT_PRIMARY_HOOKED &&
		  clt->mode != COLLECT_PRIMARY_FOLLOWED_NOINPLACE);

	cur = end - min_t(अचिन्हित पूर्णांक, offset + end - map->m_la, end);
	अगर (!(map->m_flags & EROFS_MAP_MAPPED)) अणु
		zero_user_segment(page, cur, end);
		जाओ next_part;
	पूर्ण

	/* let's derive page type */
	page_type = cur ? Z_EROFS_VLE_PAGE_TYPE_HEAD :
		(!spiltted ? Z_EROFS_PAGE_TYPE_EXCLUSIVE :
			(tight ? Z_EROFS_PAGE_TYPE_EXCLUSIVE :
				Z_EROFS_VLE_PAGE_TYPE_TAIL_SHARED));

	अगर (cur)
		tight &= (clt->mode >= COLLECT_PRIMARY_FOLLOWED);

retry:
	err = z_erofs_attach_page(clt, page, page_type);
	/* should allocate an additional लघु-lived page क्रम pagevec */
	अगर (err == -EAGAIN) अणु
		काष्ठा page *स्थिर newpage =
				alloc_page(GFP_NOFS | __GFP_NOFAIL);

		set_page_निजी(newpage, Z_EROFS_SHORTLIVED_PAGE);
		err = z_erofs_attach_page(clt, newpage,
					  Z_EROFS_PAGE_TYPE_EXCLUSIVE);
		अगर (!err)
			जाओ retry;
	पूर्ण

	अगर (err)
		जाओ err_out;

	index = page->index - (map->m_la >> PAGE_SHIFT);

	z_erofs_onlinepage_fixup(page, index, true);

	/* bump up the number of spiltted parts of a page */
	++spiltted;
	/* also update nr_pages */
	clt->cl->nr_pages = max_t(pgoff_t, clt->cl->nr_pages, index + 1);
next_part:
	/* can be used क्रम verअगरication */
	map->m_llen = offset + cur - map->m_la;

	end = cur;
	अगर (end > 0)
		जाओ repeat;

out:
	z_erofs_onlinepage_endio(page);

	erofs_dbg("%s, finish page: %pK spiltted: %u map->m_llen %llu",
		  __func__, page, spiltted, map->m_llen);
	वापस err;

	/* अगर some error occurred जबतक processing this page */
err_out:
	SetPageError(page);
	जाओ out;
पूर्ण

अटल व्योम z_erofs_decompressqueue_work(काष्ठा work_काष्ठा *work);
अटल व्योम z_erofs_decompress_kickoff(काष्ठा z_erofs_decompressqueue *io,
				       bool sync, पूर्णांक bios)
अणु
	काष्ठा erofs_sb_info *स्थिर sbi = EROFS_SB(io->sb);

	/* wake up the caller thपढ़ो क्रम sync decompression */
	अगर (sync) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&io->u.रुको.lock, flags);
		अगर (!atomic_add_वापस(bios, &io->pending_bios))
			wake_up_locked(&io->u.रुको);
		spin_unlock_irqrestore(&io->u.रुको.lock, flags);
		वापस;
	पूर्ण

	अगर (atomic_add_वापस(bios, &io->pending_bios))
		वापस;
	/* Use workqueue and sync decompression क्रम atomic contexts only */
	अगर (in_atomic() || irqs_disabled()) अणु
		queue_work(z_erofs_workqueue, &io->u.work);
		sbi->ctx.पढ़ोahead_sync_decompress = true;
		वापस;
	पूर्ण
	z_erofs_decompressqueue_work(&io->u.work);
पूर्ण

अटल bool z_erofs_page_is_invalidated(काष्ठा page *page)
अणु
	वापस !page->mapping && !z_erofs_is_लघुlived_page(page);
पूर्ण

अटल व्योम z_erofs_decompressqueue_endio(काष्ठा bio *bio)
अणु
	tagptr1_t t = tagptr_init(tagptr1_t, bio->bi_निजी);
	काष्ठा z_erofs_decompressqueue *q = tagptr_unfold_ptr(t);
	blk_status_t err = bio->bi_status;
	काष्ठा bio_vec *bvec;
	काष्ठा bvec_iter_all iter_all;

	bio_क्रम_each_segment_all(bvec, bio, iter_all) अणु
		काष्ठा page *page = bvec->bv_page;

		DBG_BUGON(PageUptodate(page));
		DBG_BUGON(z_erofs_page_is_invalidated(page));

		अगर (err)
			SetPageError(page);

		अगर (erofs_page_is_managed(EROFS_SB(q->sb), page)) अणु
			अगर (!err)
				SetPageUptodate(page);
			unlock_page(page);
		पूर्ण
	पूर्ण
	z_erofs_decompress_kickoff(q, tagptr_unfold_tags(t), -1);
	bio_put(bio);
पूर्ण

अटल पूर्णांक z_erofs_decompress_pcluster(काष्ठा super_block *sb,
				       काष्ठा z_erofs_pcluster *pcl,
				       काष्ठा list_head *pagepool)
अणु
	काष्ठा erofs_sb_info *स्थिर sbi = EROFS_SB(sb);
	काष्ठा z_erofs_pagevec_ctor ctor;
	अचिन्हित पूर्णांक i, inमाला_दोize, outमाला_दोize, llen, nr_pages;
	काष्ठा page *pages_onstack[Z_EROFS_VMAP_ONSTACK_PAGES];
	काष्ठा page **pages, **compressed_pages, *page;

	क्रमागत z_erofs_page_type page_type;
	bool overlapped, partial;
	काष्ठा z_erofs_collection *cl;
	पूर्णांक err;

	might_sleep();
	cl = z_erofs_primarycollection(pcl);
	DBG_BUGON(!READ_ONCE(cl->nr_pages));

	mutex_lock(&cl->lock);
	nr_pages = cl->nr_pages;

	अगर (nr_pages <= Z_EROFS_VMAP_ONSTACK_PAGES) अणु
		pages = pages_onstack;
	पूर्ण अन्यथा अगर (nr_pages <= Z_EROFS_VMAP_GLOBAL_PAGES &&
		   mutex_trylock(&z_pagemap_global_lock)) अणु
		pages = z_pagemap_global;
	पूर्ण अन्यथा अणु
		gfp_t gfp_flags = GFP_KERNEL;

		अगर (nr_pages > Z_EROFS_VMAP_GLOBAL_PAGES)
			gfp_flags |= __GFP_NOFAIL;

		pages = kvदो_स्मृति_array(nr_pages, माप(काष्ठा page *),
				       gfp_flags);

		/* fallback to global pagemap क्रम the lowmem scenario */
		अगर (!pages) अणु
			mutex_lock(&z_pagemap_global_lock);
			pages = z_pagemap_global;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < nr_pages; ++i)
		pages[i] = शून्य;

	err = 0;
	z_erofs_pagevec_ctor_init(&ctor, Z_EROFS_NR_INLINE_PAGEVECS,
				  cl->pagevec, 0);

	क्रम (i = 0; i < cl->vcnt; ++i) अणु
		अचिन्हित पूर्णांक pagenr;

		page = z_erofs_pagevec_dequeue(&ctor, &page_type);

		/* all pages in pagevec ought to be valid */
		DBG_BUGON(!page);
		DBG_BUGON(z_erofs_page_is_invalidated(page));

		अगर (z_erofs_put_लघुlivedpage(pagepool, page))
			जारी;

		अगर (page_type == Z_EROFS_VLE_PAGE_TYPE_HEAD)
			pagenr = 0;
		अन्यथा
			pagenr = z_erofs_onlinepage_index(page);

		DBG_BUGON(pagenr >= nr_pages);

		/*
		 * currently EROFS करोesn't support multiref(dedup),
		 * so here erroring out one multiref page.
		 */
		अगर (pages[pagenr]) अणु
			DBG_BUGON(1);
			SetPageError(pages[pagenr]);
			z_erofs_onlinepage_endio(pages[pagenr]);
			err = -EFSCORRUPTED;
		पूर्ण
		pages[pagenr] = page;
	पूर्ण
	z_erofs_pagevec_ctor_निकास(&ctor, true);

	overlapped = false;
	compressed_pages = pcl->compressed_pages;

	क्रम (i = 0; i < pcl->pclusterpages; ++i) अणु
		अचिन्हित पूर्णांक pagenr;

		page = compressed_pages[i];

		/* all compressed pages ought to be valid */
		DBG_BUGON(!page);
		DBG_BUGON(z_erofs_page_is_invalidated(page));

		अगर (!z_erofs_is_लघुlived_page(page)) अणु
			अगर (erofs_page_is_managed(sbi, page)) अणु
				अगर (!PageUptodate(page))
					err = -EIO;
				जारी;
			पूर्ण

			/*
			 * only अगर non-head page can be selected
			 * क्रम inplace decompression
			 */
			pagenr = z_erofs_onlinepage_index(page);

			DBG_BUGON(pagenr >= nr_pages);
			अगर (pages[pagenr]) अणु
				DBG_BUGON(1);
				SetPageError(pages[pagenr]);
				z_erofs_onlinepage_endio(pages[pagenr]);
				err = -EFSCORRUPTED;
			पूर्ण
			pages[pagenr] = page;

			overlapped = true;
		पूर्ण

		/* PG_error needs checking क्रम all non-managed pages */
		अगर (PageError(page)) अणु
			DBG_BUGON(PageUptodate(page));
			err = -EIO;
		पूर्ण
	पूर्ण

	अगर (err)
		जाओ out;

	llen = pcl->length >> Z_EROFS_PCLUSTER_LENGTH_BIT;
	अगर (nr_pages << PAGE_SHIFT >= cl->pageofs + llen) अणु
		outमाला_दोize = llen;
		partial = !(pcl->length & Z_EROFS_PCLUSTER_FULL_LENGTH);
	पूर्ण अन्यथा अणु
		outमाला_दोize = (nr_pages << PAGE_SHIFT) - cl->pageofs;
		partial = true;
	पूर्ण

	inमाला_दोize = pcl->pclusterpages * PAGE_SIZE;
	err = z_erofs_decompress(&(काष्ठा z_erofs_decompress_req) अणु
					.sb = sb,
					.in = compressed_pages,
					.out = pages,
					.pageofs_out = cl->pageofs,
					.inमाला_दोize = inमाला_दोize,
					.outमाला_दोize = outमाला_दोize,
					.alg = pcl->algorithmक्रमmat,
					.inplace_io = overlapped,
					.partial_decoding = partial
				 पूर्ण, pagepool);

out:
	/* must handle all compressed pages beक्रमe ending pages */
	क्रम (i = 0; i < pcl->pclusterpages; ++i) अणु
		page = compressed_pages[i];

		अगर (erofs_page_is_managed(sbi, page))
			जारी;

		/* recycle all inभागidual लघु-lived pages */
		(व्योम)z_erofs_put_लघुlivedpage(pagepool, page);

		WRITE_ONCE(compressed_pages[i], शून्य);
	पूर्ण

	क्रम (i = 0; i < nr_pages; ++i) अणु
		page = pages[i];
		अगर (!page)
			जारी;

		DBG_BUGON(z_erofs_page_is_invalidated(page));

		/* recycle all inभागidual लघु-lived pages */
		अगर (z_erofs_put_लघुlivedpage(pagepool, page))
			जारी;

		अगर (err < 0)
			SetPageError(page);

		z_erofs_onlinepage_endio(page);
	पूर्ण

	अगर (pages == z_pagemap_global)
		mutex_unlock(&z_pagemap_global_lock);
	अन्यथा अगर (pages != pages_onstack)
		kvमुक्त(pages);

	cl->nr_pages = 0;
	cl->vcnt = 0;

	/* all cl locks MUST be taken beक्रमe the following line */
	WRITE_ONCE(pcl->next, Z_EROFS_PCLUSTER_NIL);

	/* all cl locks SHOULD be released right now */
	mutex_unlock(&cl->lock);

	z_erofs_collection_put(cl);
	वापस err;
पूर्ण

अटल व्योम z_erofs_decompress_queue(स्थिर काष्ठा z_erofs_decompressqueue *io,
				     काष्ठा list_head *pagepool)
अणु
	z_erofs_next_pcluster_t owned = io->head;

	जबतक (owned != Z_EROFS_PCLUSTER_TAIL_CLOSED) अणु
		काष्ठा z_erofs_pcluster *pcl;

		/* no possible that 'owned' equals Z_EROFS_WORK_TPTR_TAIL */
		DBG_BUGON(owned == Z_EROFS_PCLUSTER_TAIL);

		/* no possible that 'owned' equals शून्य */
		DBG_BUGON(owned == Z_EROFS_PCLUSTER_NIL);

		pcl = container_of(owned, काष्ठा z_erofs_pcluster, next);
		owned = READ_ONCE(pcl->next);

		z_erofs_decompress_pcluster(io->sb, pcl, pagepool);
	पूर्ण
पूर्ण

अटल व्योम z_erofs_decompressqueue_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा z_erofs_decompressqueue *bgq =
		container_of(work, काष्ठा z_erofs_decompressqueue, u.work);
	LIST_HEAD(pagepool);

	DBG_BUGON(bgq->head == Z_EROFS_PCLUSTER_TAIL_CLOSED);
	z_erofs_decompress_queue(bgq, &pagepool);

	put_pages_list(&pagepool);
	kvमुक्त(bgq);
पूर्ण

अटल काष्ठा page *pickup_page_क्रम_submission(काष्ठा z_erofs_pcluster *pcl,
					       अचिन्हित पूर्णांक nr,
					       काष्ठा list_head *pagepool,
					       काष्ठा address_space *mc,
					       gfp_t gfp)
अणु
	स्थिर pgoff_t index = pcl->obj.index;
	bool tocache = false;

	काष्ठा address_space *mapping;
	काष्ठा page *oldpage, *page;

	compressed_page_t t;
	पूर्णांक justfound;

repeat:
	page = READ_ONCE(pcl->compressed_pages[nr]);
	oldpage = page;

	अगर (!page)
		जाओ out_allocpage;

	/*
	 * the cached page has not been allocated and
	 * an placeholder is out there, prepare it now.
	 */
	अगर (page == PAGE_UNALLOCATED) अणु
		tocache = true;
		जाओ out_allocpage;
	पूर्ण

	/* process the target tagged poपूर्णांकer */
	t = tagptr_init(compressed_page_t, page);
	justfound = tagptr_unfold_tags(t);
	page = tagptr_unfold_ptr(t);

	/*
	 * pपुनः_स्मृतिated cached pages, which is used to aव्योम direct reclaim
	 * otherwise, it will go inplace I/O path instead.
	 */
	अगर (page->निजी == Z_EROFS_PREALLOCATED_PAGE) अणु
		WRITE_ONCE(pcl->compressed_pages[nr], page);
		set_page_निजी(page, 0);
		tocache = true;
		जाओ out_tocache;
	पूर्ण
	mapping = READ_ONCE(page->mapping);

	/*
	 * file-backed online pages in plcuster are all locked steady,
	 * thereक्रमe it is impossible क्रम `mapping' to be शून्य.
	 */
	अगर (mapping && mapping != mc)
		/* ought to be unmanaged pages */
		जाओ out;

	/* directly वापस क्रम लघुlived page as well */
	अगर (z_erofs_is_लघुlived_page(page))
		जाओ out;

	lock_page(page);

	/* only true अगर page reclaim goes wrong, should never happen */
	DBG_BUGON(justfound && PagePrivate(page));

	/* the page is still in manage cache */
	अगर (page->mapping == mc) अणु
		WRITE_ONCE(pcl->compressed_pages[nr], page);

		ClearPageError(page);
		अगर (!PagePrivate(page)) अणु
			/*
			 * impossible to be !PagePrivate(page) क्रम
			 * the current restriction as well अगर
			 * the page is alपढ़ोy in compressed_pages[].
			 */
			DBG_BUGON(!justfound);

			justfound = 0;
			set_page_निजी(page, (अचिन्हित दीर्घ)pcl);
			SetPagePrivate(page);
		पूर्ण

		/* no need to submit io अगर it is alपढ़ोy up-to-date */
		अगर (PageUptodate(page)) अणु
			unlock_page(page);
			page = शून्य;
		पूर्ण
		जाओ out;
	पूर्ण

	/*
	 * the managed page has been truncated, it's unsafe to
	 * reuse this one, let's allocate a new cache-managed page.
	 */
	DBG_BUGON(page->mapping);
	DBG_BUGON(!justfound);

	tocache = true;
	unlock_page(page);
	put_page(page);
out_allocpage:
	page = erofs_allocpage(pagepool, gfp | __GFP_NOFAIL);
	अगर (oldpage != cmpxchg(&pcl->compressed_pages[nr], oldpage, page)) अणु
		list_add(&page->lru, pagepool);
		cond_resched();
		जाओ repeat;
	पूर्ण
out_tocache:
	अगर (!tocache || add_to_page_cache_lru(page, mc, index + nr, gfp)) अणु
		/* turn पूर्णांकo temporary page अगर fails (1 ref) */
		set_page_निजी(page, Z_EROFS_SHORTLIVED_PAGE);
		जाओ out;
	पूर्ण
	attach_page_निजी(page, pcl);
	/* drop a refcount added by allocpage (then we have 2 refs here) */
	put_page(page);

out:	/* the only निकास (क्रम tracing and debugging) */
	वापस page;
पूर्ण

अटल काष्ठा z_erofs_decompressqueue *
jobqueue_init(काष्ठा super_block *sb,
	      काष्ठा z_erofs_decompressqueue *fgq, bool *fg)
अणु
	काष्ठा z_erofs_decompressqueue *q;

	अगर (fg && !*fg) अणु
		q = kvzalloc(माप(*q), GFP_KERNEL | __GFP_NOWARN);
		अगर (!q) अणु
			*fg = true;
			जाओ fg_out;
		पूर्ण
		INIT_WORK(&q->u.work, z_erofs_decompressqueue_work);
	पूर्ण अन्यथा अणु
fg_out:
		q = fgq;
		init_रुकोqueue_head(&fgq->u.रुको);
		atomic_set(&fgq->pending_bios, 0);
	पूर्ण
	q->sb = sb;
	q->head = Z_EROFS_PCLUSTER_TAIL_CLOSED;
	वापस q;
पूर्ण

/* define decompression jobqueue types */
क्रमागत अणु
	JQ_BYPASS,
	JQ_SUBMIT,
	NR_JOBQUEUES,
पूर्ण;

अटल व्योम *jobqueueset_init(काष्ठा super_block *sb,
			      काष्ठा z_erofs_decompressqueue *q[],
			      काष्ठा z_erofs_decompressqueue *fgq, bool *fg)
अणु
	/*
	 * अगर managed cache is enabled, bypass jobqueue is needed,
	 * no need to पढ़ो from device क्रम all pclusters in this queue.
	 */
	q[JQ_BYPASS] = jobqueue_init(sb, fgq + JQ_BYPASS, शून्य);
	q[JQ_SUBMIT] = jobqueue_init(sb, fgq + JQ_SUBMIT, fg);

	वापस tagptr_cast_ptr(tagptr_fold(tagptr1_t, q[JQ_SUBMIT], *fg));
पूर्ण

अटल व्योम move_to_bypass_jobqueue(काष्ठा z_erofs_pcluster *pcl,
				    z_erofs_next_pcluster_t qtail[],
				    z_erofs_next_pcluster_t owned_head)
अणु
	z_erofs_next_pcluster_t *स्थिर submit_qtail = qtail[JQ_SUBMIT];
	z_erofs_next_pcluster_t *स्थिर bypass_qtail = qtail[JQ_BYPASS];

	DBG_BUGON(owned_head == Z_EROFS_PCLUSTER_TAIL_CLOSED);
	अगर (owned_head == Z_EROFS_PCLUSTER_TAIL)
		owned_head = Z_EROFS_PCLUSTER_TAIL_CLOSED;

	WRITE_ONCE(pcl->next, Z_EROFS_PCLUSTER_TAIL_CLOSED);

	WRITE_ONCE(*submit_qtail, owned_head);
	WRITE_ONCE(*bypass_qtail, &pcl->next);

	qtail[JQ_BYPASS] = &pcl->next;
पूर्ण

अटल व्योम z_erofs_submit_queue(काष्ठा super_block *sb,
				 काष्ठा z_erofs_decompress_frontend *f,
				 काष्ठा list_head *pagepool,
				 काष्ठा z_erofs_decompressqueue *fgq,
				 bool *क्रमce_fg)
अणु
	काष्ठा erofs_sb_info *स्थिर sbi = EROFS_SB(sb);
	z_erofs_next_pcluster_t qtail[NR_JOBQUEUES];
	काष्ठा z_erofs_decompressqueue *q[NR_JOBQUEUES];
	व्योम *bi_निजी;
	z_erofs_next_pcluster_t owned_head = f->clt.owned_head;
	/* since bio will be शून्य, no need to initialize last_index */
	pgoff_t last_index;
	अचिन्हित पूर्णांक nr_bios = 0;
	काष्ठा bio *bio = शून्य;

	bi_निजी = jobqueueset_init(sb, q, fgq, क्रमce_fg);
	qtail[JQ_BYPASS] = &q[JQ_BYPASS]->head;
	qtail[JQ_SUBMIT] = &q[JQ_SUBMIT]->head;

	/* by शेष, all need io submission */
	q[JQ_SUBMIT]->head = owned_head;

	करो अणु
		काष्ठा z_erofs_pcluster *pcl;
		pgoff_t cur, end;
		अचिन्हित पूर्णांक i = 0;
		bool bypass = true;

		/* no possible 'owned_head' equals the following */
		DBG_BUGON(owned_head == Z_EROFS_PCLUSTER_TAIL_CLOSED);
		DBG_BUGON(owned_head == Z_EROFS_PCLUSTER_NIL);

		pcl = container_of(owned_head, काष्ठा z_erofs_pcluster, next);

		cur = pcl->obj.index;
		end = cur + pcl->pclusterpages;

		/* बंद the मुख्य owned chain at first */
		owned_head = cmpxchg(&pcl->next, Z_EROFS_PCLUSTER_TAIL,
				     Z_EROFS_PCLUSTER_TAIL_CLOSED);

		करो अणु
			काष्ठा page *page;

			page = pickup_page_क्रम_submission(pcl, i++, pagepool,
							  MNGD_MAPPING(sbi),
							  GFP_NOFS);
			अगर (!page)
				जारी;

			अगर (bio && cur != last_index + 1) अणु
submit_bio_retry:
				submit_bio(bio);
				bio = शून्य;
			पूर्ण

			अगर (!bio) अणु
				bio = bio_alloc(GFP_NOIO, BIO_MAX_VECS);

				bio->bi_end_io = z_erofs_decompressqueue_endio;
				bio_set_dev(bio, sb->s_bdev);
				bio->bi_iter.bi_sector = (sector_t)cur <<
					LOG_SECTORS_PER_BLOCK;
				bio->bi_निजी = bi_निजी;
				bio->bi_opf = REQ_OP_READ;
				अगर (f->पढ़ोahead)
					bio->bi_opf |= REQ_RAHEAD;
				++nr_bios;
			पूर्ण

			अगर (bio_add_page(bio, page, PAGE_SIZE, 0) < PAGE_SIZE)
				जाओ submit_bio_retry;

			last_index = cur;
			bypass = false;
		पूर्ण जबतक (++cur < end);

		अगर (!bypass)
			qtail[JQ_SUBMIT] = &pcl->next;
		अन्यथा
			move_to_bypass_jobqueue(pcl, qtail, owned_head);
	पूर्ण जबतक (owned_head != Z_EROFS_PCLUSTER_TAIL);

	अगर (bio)
		submit_bio(bio);

	/*
	 * although background is preferred, no one is pending क्रम submission.
	 * करोn't issue workqueue क्रम decompression but drop it directly instead.
	 */
	अगर (!*क्रमce_fg && !nr_bios) अणु
		kvमुक्त(q[JQ_SUBMIT]);
		वापस;
	पूर्ण
	z_erofs_decompress_kickoff(q[JQ_SUBMIT], *क्रमce_fg, nr_bios);
पूर्ण

अटल व्योम z_erofs_runqueue(काष्ठा super_block *sb,
			     काष्ठा z_erofs_decompress_frontend *f,
			     काष्ठा list_head *pagepool, bool क्रमce_fg)
अणु
	काष्ठा z_erofs_decompressqueue io[NR_JOBQUEUES];

	अगर (f->clt.owned_head == Z_EROFS_PCLUSTER_TAIL)
		वापस;
	z_erofs_submit_queue(sb, f, pagepool, io, &क्रमce_fg);

	/* handle bypass queue (no i/o pclusters) immediately */
	z_erofs_decompress_queue(&io[JQ_BYPASS], pagepool);

	अगर (!क्रमce_fg)
		वापस;

	/* रुको until all bios are completed */
	io_रुको_event(io[JQ_SUBMIT].u.रुको,
		      !atomic_पढ़ो(&io[JQ_SUBMIT].pending_bios));

	/* handle synchronous decompress queue in the caller context */
	z_erofs_decompress_queue(&io[JQ_SUBMIT], pagepool);
पूर्ण

अटल पूर्णांक z_erofs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा inode *स्थिर inode = page->mapping->host;
	काष्ठा z_erofs_decompress_frontend f = DECOMPRESS_FRONTEND_INIT(inode);
	पूर्णांक err;
	LIST_HEAD(pagepool);

	trace_erofs_पढ़ोpage(page, false);

	f.heaकरोffset = (erofs_off_t)page->index << PAGE_SHIFT;

	err = z_erofs_करो_पढ़ो_page(&f, page, &pagepool);
	(व्योम)z_erofs_collector_end(&f.clt);

	/* अगर some compressed cluster पढ़ोy, need submit them anyway */
	z_erofs_runqueue(inode->i_sb, &f, &pagepool, true);

	अगर (err)
		erofs_err(inode->i_sb, "failed to read, err [%d]", err);

	अगर (f.map.mpage)
		put_page(f.map.mpage);

	/* clean up the reमुख्यing मुक्त pages */
	put_pages_list(&pagepool);
	वापस err;
पूर्ण

अटल व्योम z_erofs_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	काष्ठा inode *स्थिर inode = rac->mapping->host;
	काष्ठा erofs_sb_info *स्थिर sbi = EROFS_I_SB(inode);

	अचिन्हित पूर्णांक nr_pages = पढ़ोahead_count(rac);
	bool sync = (sbi->ctx.पढ़ोahead_sync_decompress &&
			nr_pages <= sbi->ctx.max_sync_decompress_pages);
	काष्ठा z_erofs_decompress_frontend f = DECOMPRESS_FRONTEND_INIT(inode);
	काष्ठा page *page, *head = शून्य;
	LIST_HEAD(pagepool);

	trace_erofs_पढ़ोpages(inode, पढ़ोahead_index(rac), nr_pages, false);

	f.पढ़ोahead = true;
	f.heaकरोffset = पढ़ोahead_pos(rac);

	जबतक ((page = पढ़ोahead_page(rac))) अणु
		prefetchw(&page->flags);

		/*
		 * A pure asynchronous पढ़ोahead is indicated अगर
		 * a PG_पढ़ोahead marked page is hitted at first.
		 * Let's also करो asynchronous decompression क्रम this हाल.
		 */
		sync &= !(PageReadahead(page) && !head);

		set_page_निजी(page, (अचिन्हित दीर्घ)head);
		head = page;
	पूर्ण

	जबतक (head) अणु
		काष्ठा page *page = head;
		पूर्णांक err;

		/* traversal in reverse order */
		head = (व्योम *)page_निजी(page);

		err = z_erofs_करो_पढ़ो_page(&f, page, &pagepool);
		अगर (err)
			erofs_err(inode->i_sb,
				  "readahead error at page %lu @ nid %llu",
				  page->index, EROFS_I(inode)->nid);
		put_page(page);
	पूर्ण

	(व्योम)z_erofs_collector_end(&f.clt);

	z_erofs_runqueue(inode->i_sb, &f, &pagepool, sync);

	अगर (f.map.mpage)
		put_page(f.map.mpage);

	/* clean up the reमुख्यing मुक्त pages */
	put_pages_list(&pagepool);
पूर्ण

स्थिर काष्ठा address_space_operations z_erofs_aops = अणु
	.पढ़ोpage = z_erofs_पढ़ोpage,
	.पढ़ोahead = z_erofs_पढ़ोahead,
पूर्ण;

