<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dax: direct host memory access
 * Copyright (C) 2020 Red Hat, Inc.
 */

#समावेश "fuse_i.h"

#समावेश <linux/delay.h>
#समावेश <linux/dax.h>
#समावेश <linux/uपन.स>
#समावेश <linux/pfn_t.h>
#समावेश <linux/iomap.h>
#समावेश <linux/पूर्णांकerval_tree.h>

/*
 * Default memory range size.  A घातer of 2 so it agrees with common FUSE_INIT
 * map_alignment values 4KB and 64KB.
 */
#घोषणा FUSE_DAX_SHIFT	21
#घोषणा FUSE_DAX_SZ	(1 << FUSE_DAX_SHIFT)
#घोषणा FUSE_DAX_PAGES	(FUSE_DAX_SZ / PAGE_SIZE)

/* Number of ranges reclaimer will try to मुक्त in one invocation */
#घोषणा FUSE_DAX_RECLAIM_CHUNK		(10)

/*
 * Dax memory reclaim threshold in percetage of total ranges. When मुक्त
 * number of मुक्त ranges drops below this threshold, reclaim can trigger
 * Default is 20%
 */
#घोषणा FUSE_DAX_RECLAIM_THRESHOLD	(20)

/** Translation inक्रमmation क्रम file offsets to DAX winकरोw offsets */
काष्ठा fuse_dax_mapping अणु
	/* Poपूर्णांकer to inode where this memory range is mapped */
	काष्ठा inode *inode;

	/* Will connect in fcd->मुक्त_ranges to keep track of मुक्त memory */
	काष्ठा list_head list;

	/* For पूर्णांकerval tree in file/inode */
	काष्ठा पूर्णांकerval_tree_node itn;

	/* Will connect in fc->busy_ranges to keep track busy memory */
	काष्ठा list_head busy_list;

	/** Position in DAX winकरोw */
	u64 winकरोw_offset;

	/** Length of mapping, in bytes */
	loff_t length;

	/* Is this mapping पढ़ो-only or पढ़ो-ग_लिखो */
	bool writable;

	/* reference count when the mapping is used by dax iomap. */
	refcount_t refcnt;
पूर्ण;

/* Per-inode dax map */
काष्ठा fuse_inode_dax अणु
	/* Semaphore to protect modअगरications to the dmap tree */
	काष्ठा rw_semaphore sem;

	/* Sorted rb tree of काष्ठा fuse_dax_mapping elements */
	काष्ठा rb_root_cached tree;
	अचिन्हित दीर्घ nr;
पूर्ण;

काष्ठा fuse_conn_dax अणु
	/* DAX device */
	काष्ठा dax_device *dev;

	/* Lock protecting accessess to  members of this काष्ठाure */
	spinlock_t lock;

	/* List of memory ranges which are busy */
	अचिन्हित दीर्घ nr_busy_ranges;
	काष्ठा list_head busy_ranges;

	/* Worker to मुक्त up memory ranges */
	काष्ठा delayed_work मुक्त_work;

	/* Wait queue क्रम a dax range to become मुक्त */
	रुको_queue_head_t range_रुकोq;

	/* DAX Winकरोw Free Ranges */
	दीर्घ nr_मुक्त_ranges;
	काष्ठा list_head मुक्त_ranges;

	अचिन्हित दीर्घ nr_ranges;
पूर्ण;

अटल अंतरभूत काष्ठा fuse_dax_mapping *
node_to_dmap(काष्ठा पूर्णांकerval_tree_node *node)
अणु
	अगर (!node)
		वापस शून्य;

	वापस container_of(node, काष्ठा fuse_dax_mapping, itn);
पूर्ण

अटल काष्ठा fuse_dax_mapping *
alloc_dax_mapping_reclaim(काष्ठा fuse_conn_dax *fcd, काष्ठा inode *inode);

अटल व्योम
__kick_dmap_मुक्त_worker(काष्ठा fuse_conn_dax *fcd, अचिन्हित दीर्घ delay_ms)
अणु
	अचिन्हित दीर्घ मुक्त_threshold;

	/* If number of मुक्त ranges are below threshold, start reclaim */
	मुक्त_threshold = max_t(अचिन्हित दीर्घ, fcd->nr_ranges * FUSE_DAX_RECLAIM_THRESHOLD / 100,
			     1);
	अगर (fcd->nr_मुक्त_ranges < मुक्त_threshold)
		queue_delayed_work(प्रणाली_दीर्घ_wq, &fcd->मुक्त_work,
				   msecs_to_jअगरfies(delay_ms));
पूर्ण

अटल व्योम kick_dmap_मुक्त_worker(काष्ठा fuse_conn_dax *fcd,
				  अचिन्हित दीर्घ delay_ms)
अणु
	spin_lock(&fcd->lock);
	__kick_dmap_मुक्त_worker(fcd, delay_ms);
	spin_unlock(&fcd->lock);
पूर्ण

अटल काष्ठा fuse_dax_mapping *alloc_dax_mapping(काष्ठा fuse_conn_dax *fcd)
अणु
	काष्ठा fuse_dax_mapping *dmap;

	spin_lock(&fcd->lock);
	dmap = list_first_entry_or_null(&fcd->मुक्त_ranges,
					काष्ठा fuse_dax_mapping, list);
	अगर (dmap) अणु
		list_del_init(&dmap->list);
		WARN_ON(fcd->nr_मुक्त_ranges <= 0);
		fcd->nr_मुक्त_ranges--;
	पूर्ण
	spin_unlock(&fcd->lock);

	kick_dmap_मुक्त_worker(fcd, 0);
	वापस dmap;
पूर्ण

/* This assumes fcd->lock is held */
अटल व्योम __dmap_हटाओ_busy_list(काष्ठा fuse_conn_dax *fcd,
				    काष्ठा fuse_dax_mapping *dmap)
अणु
	list_del_init(&dmap->busy_list);
	WARN_ON(fcd->nr_busy_ranges == 0);
	fcd->nr_busy_ranges--;
पूर्ण

अटल व्योम dmap_हटाओ_busy_list(काष्ठा fuse_conn_dax *fcd,
				  काष्ठा fuse_dax_mapping *dmap)
अणु
	spin_lock(&fcd->lock);
	__dmap_हटाओ_busy_list(fcd, dmap);
	spin_unlock(&fcd->lock);
पूर्ण

/* This assumes fcd->lock is held */
अटल व्योम __dmap_add_to_मुक्त_pool(काष्ठा fuse_conn_dax *fcd,
				काष्ठा fuse_dax_mapping *dmap)
अणु
	list_add_tail(&dmap->list, &fcd->मुक्त_ranges);
	fcd->nr_मुक्त_ranges++;
	wake_up(&fcd->range_रुकोq);
पूर्ण

अटल व्योम dmap_add_to_मुक्त_pool(काष्ठा fuse_conn_dax *fcd,
				काष्ठा fuse_dax_mapping *dmap)
अणु
	/* Return fuse_dax_mapping to मुक्त list */
	spin_lock(&fcd->lock);
	__dmap_add_to_मुक्त_pool(fcd, dmap);
	spin_unlock(&fcd->lock);
पूर्ण

अटल पूर्णांक fuse_setup_one_mapping(काष्ठा inode *inode, अचिन्हित दीर्घ start_idx,
				  काष्ठा fuse_dax_mapping *dmap, bool writable,
				  bool upgrade)
अणु
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	काष्ठा fuse_conn_dax *fcd = fm->fc->dax;
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	काष्ठा fuse_setupmapping_in inarg;
	loff_t offset = start_idx << FUSE_DAX_SHIFT;
	FUSE_ARGS(args);
	sमाप_प्रकार err;

	WARN_ON(fcd->nr_मुक्त_ranges < 0);

	/* Ask fuse daemon to setup mapping */
	स_रखो(&inarg, 0, माप(inarg));
	inarg.foffset = offset;
	inarg.fh = -1;
	inarg.moffset = dmap->winकरोw_offset;
	inarg.len = FUSE_DAX_SZ;
	inarg.flags |= FUSE_SETUPMAPPING_FLAG_READ;
	अगर (writable)
		inarg.flags |= FUSE_SETUPMAPPING_FLAG_WRITE;
	args.opcode = FUSE_SETUPMAPPING;
	args.nodeid = fi->nodeid;
	args.in_numargs = 1;
	args.in_args[0].size = माप(inarg);
	args.in_args[0].value = &inarg;
	err = fuse_simple_request(fm, &args);
	अगर (err < 0)
		वापस err;
	dmap->writable = writable;
	अगर (!upgrade) अणु
		/*
		 * We करोn't take a refernce on inode. inode is valid right now
		 * and when inode is going away, cleanup logic should first
		 * cleanup dmap entries.
		 */
		dmap->inode = inode;
		dmap->itn.start = dmap->itn.last = start_idx;
		/* Protected by fi->dax->sem */
		पूर्णांकerval_tree_insert(&dmap->itn, &fi->dax->tree);
		fi->dax->nr++;
		spin_lock(&fcd->lock);
		list_add_tail(&dmap->busy_list, &fcd->busy_ranges);
		fcd->nr_busy_ranges++;
		spin_unlock(&fcd->lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fuse_send_हटाओmapping(काष्ठा inode *inode,
				   काष्ठा fuse_हटाओmapping_in *inargp,
				   काष्ठा fuse_हटाओmapping_one *हटाओ_one)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	FUSE_ARGS(args);

	args.opcode = FUSE_REMOVEMAPPING;
	args.nodeid = fi->nodeid;
	args.in_numargs = 2;
	args.in_args[0].size = माप(*inargp);
	args.in_args[0].value = inargp;
	args.in_args[1].size = inargp->count * माप(*हटाओ_one);
	args.in_args[1].value = हटाओ_one;
	वापस fuse_simple_request(fm, &args);
पूर्ण

अटल पूर्णांक dmap_हटाओmapping_list(काष्ठा inode *inode, अचिन्हित पूर्णांक num,
				   काष्ठा list_head *to_हटाओ)
अणु
	काष्ठा fuse_हटाओmapping_one *हटाओ_one, *ptr;
	काष्ठा fuse_हटाओmapping_in inarg;
	काष्ठा fuse_dax_mapping *dmap;
	पूर्णांक ret, i = 0, nr_alloc;

	nr_alloc = min_t(अचिन्हित पूर्णांक, num, FUSE_REMOVEMAPPING_MAX_ENTRY);
	हटाओ_one = kदो_स्मृति_array(nr_alloc, माप(*हटाओ_one), GFP_NOFS);
	अगर (!हटाओ_one)
		वापस -ENOMEM;

	ptr = हटाओ_one;
	list_क्रम_each_entry(dmap, to_हटाओ, list) अणु
		ptr->moffset = dmap->winकरोw_offset;
		ptr->len = dmap->length;
		ptr++;
		i++;
		num--;
		अगर (i >= nr_alloc || num == 0) अणु
			स_रखो(&inarg, 0, माप(inarg));
			inarg.count = i;
			ret = fuse_send_हटाओmapping(inode, &inarg,
						      हटाओ_one);
			अगर (ret)
				जाओ out;
			ptr = हटाओ_one;
			i = 0;
		पूर्ण
	पूर्ण
out:
	kमुक्त(हटाओ_one);
	वापस ret;
पूर्ण

/*
 * Cleanup dmap entry and add back to मुक्त list. This should be called with
 * fcd->lock held.
 */
अटल व्योम dmap_reinit_add_to_मुक्त_pool(काष्ठा fuse_conn_dax *fcd,
					    काष्ठा fuse_dax_mapping *dmap)
अणु
	pr_debug("fuse: freeing memory range start_idx=0x%lx end_idx=0x%lx window_offset=0x%llx length=0x%llx\n",
		 dmap->itn.start, dmap->itn.last, dmap->winकरोw_offset,
		 dmap->length);
	__dmap_हटाओ_busy_list(fcd, dmap);
	dmap->inode = शून्य;
	dmap->itn.start = dmap->itn.last = 0;
	__dmap_add_to_मुक्त_pool(fcd, dmap);
पूर्ण

/*
 * Free inode dmap entries whose range falls inside [start, end].
 * Does not take any locks. At this poपूर्णांक of समय it should only be
 * called from evict_inode() path where we know all dmap entries can be
 * reclaimed.
 */
अटल व्योम inode_reclaim_dmap_range(काष्ठा fuse_conn_dax *fcd,
				     काष्ठा inode *inode,
				     loff_t start, loff_t end)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	काष्ठा fuse_dax_mapping *dmap, *n;
	पूर्णांक err, num = 0;
	LIST_HEAD(to_हटाओ);
	अचिन्हित दीर्घ start_idx = start >> FUSE_DAX_SHIFT;
	अचिन्हित दीर्घ end_idx = end >> FUSE_DAX_SHIFT;
	काष्ठा पूर्णांकerval_tree_node *node;

	जबतक (1) अणु
		node = पूर्णांकerval_tree_iter_first(&fi->dax->tree, start_idx,
						end_idx);
		अगर (!node)
			अवरोध;
		dmap = node_to_dmap(node);
		/* inode is going away. There should not be any users of dmap */
		WARN_ON(refcount_पढ़ो(&dmap->refcnt) > 1);
		पूर्णांकerval_tree_हटाओ(&dmap->itn, &fi->dax->tree);
		num++;
		list_add(&dmap->list, &to_हटाओ);
	पूर्ण

	/* Nothing to हटाओ */
	अगर (list_empty(&to_हटाओ))
		वापस;

	WARN_ON(fi->dax->nr < num);
	fi->dax->nr -= num;
	err = dmap_हटाओmapping_list(inode, num, &to_हटाओ);
	अगर (err && err != -ENOTCONN) अणु
		pr_warn("Failed to removemappings. start=0x%llx end=0x%llx\n",
			start, end);
	पूर्ण
	spin_lock(&fcd->lock);
	list_क्रम_each_entry_safe(dmap, n, &to_हटाओ, list) अणु
		list_del_init(&dmap->list);
		dmap_reinit_add_to_मुक्त_pool(fcd, dmap);
	पूर्ण
	spin_unlock(&fcd->lock);
पूर्ण

अटल पूर्णांक dmap_हटाओmapping_one(काष्ठा inode *inode,
				  काष्ठा fuse_dax_mapping *dmap)
अणु
	काष्ठा fuse_हटाओmapping_one क्रमget_one;
	काष्ठा fuse_हटाओmapping_in inarg;

	स_रखो(&inarg, 0, माप(inarg));
	inarg.count = 1;
	स_रखो(&क्रमget_one, 0, माप(क्रमget_one));
	क्रमget_one.moffset = dmap->winकरोw_offset;
	क्रमget_one.len = dmap->length;

	वापस fuse_send_हटाओmapping(inode, &inarg, &क्रमget_one);
पूर्ण

/*
 * It is called from evict_inode() and by that समय inode is going away. So
 * this function करोes not take any locks like fi->dax->sem क्रम traversing
 * that fuse inode पूर्णांकerval tree. If that lock is taken then lock validator
 * complains of deadlock situation w.r.t fs_reclaim lock.
 */
व्योम fuse_dax_inode_cleanup(काष्ठा inode *inode)
अणु
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);

	/*
	 * fuse_evict_inode() has alपढ़ोy called truncate_inode_pages_final()
	 * beक्रमe we arrive here. So we should not have to worry about any
	 * pages/exception entries still associated with inode.
	 */
	inode_reclaim_dmap_range(fc->dax, inode, 0, -1);
	WARN_ON(fi->dax->nr);
पूर्ण

अटल व्योम fuse_fill_iomap_hole(काष्ठा iomap *iomap, loff_t length)
अणु
	iomap->addr = IOMAP_शून्य_ADDR;
	iomap->length = length;
	iomap->type = IOMAP_HOLE;
पूर्ण

अटल व्योम fuse_fill_iomap(काष्ठा inode *inode, loff_t pos, loff_t length,
			    काष्ठा iomap *iomap, काष्ठा fuse_dax_mapping *dmap,
			    अचिन्हित पूर्णांक flags)
अणु
	loff_t offset, len;
	loff_t i_size = i_size_पढ़ो(inode);

	offset = pos - (dmap->itn.start << FUSE_DAX_SHIFT);
	len = min(length, dmap->length - offset);

	/* If length is beyond end of file, truncate further */
	अगर (pos + len > i_size)
		len = i_size - pos;

	अगर (len > 0) अणु
		iomap->addr = dmap->winकरोw_offset + offset;
		iomap->length = len;
		अगर (flags & IOMAP_FAULT)
			iomap->length = ALIGN(len, PAGE_SIZE);
		iomap->type = IOMAP_MAPPED;
		/*
		 * increace refcnt so that reclaim code knows this dmap is in
		 * use. This assumes fi->dax->sem mutex is held either
		 * shared/exclusive.
		 */
		refcount_inc(&dmap->refcnt);

		/* iomap->निजी should be शून्य */
		WARN_ON_ONCE(iomap->निजी);
		iomap->निजी = dmap;
	पूर्ण अन्यथा अणु
		/* Mapping beyond end of file is hole */
		fuse_fill_iomap_hole(iomap, length);
	पूर्ण
पूर्ण

अटल पूर्णांक fuse_setup_new_dax_mapping(काष्ठा inode *inode, loff_t pos,
				      loff_t length, अचिन्हित पूर्णांक flags,
				      काष्ठा iomap *iomap)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	काष्ठा fuse_conn_dax *fcd = fc->dax;
	काष्ठा fuse_dax_mapping *dmap, *alloc_dmap = शून्य;
	पूर्णांक ret;
	bool writable = flags & IOMAP_WRITE;
	अचिन्हित दीर्घ start_idx = pos >> FUSE_DAX_SHIFT;
	काष्ठा पूर्णांकerval_tree_node *node;

	/*
	 * Can't करो अंतरभूत reclaim in fault path. We call
	 * dax_layout_busy_page() beक्रमe we मुक्त a range. And
	 * fuse_रुको_dax_page() drops fi->i_mmap_sem lock and requires it.
	 * In fault path we enter with fi->i_mmap_sem held and can't drop
	 * it. Also in fault path we hold fi->i_mmap_sem shared and not
	 * exclusive, so that creates further issues with fuse_रुको_dax_page().
	 * Hence वापस -EAGAIN and fuse_dax_fault() will रुको क्रम a memory
	 * range to become मुक्त and retry.
	 */
	अगर (flags & IOMAP_FAULT) अणु
		alloc_dmap = alloc_dax_mapping(fcd);
		अगर (!alloc_dmap)
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		alloc_dmap = alloc_dax_mapping_reclaim(fcd, inode);
		अगर (IS_ERR(alloc_dmap))
			वापस PTR_ERR(alloc_dmap);
	पूर्ण

	/* If we are here, we should have memory allocated */
	अगर (WARN_ON(!alloc_dmap))
		वापस -EIO;

	/*
	 * Take ग_लिखो lock so that only one caller can try to setup mapping
	 * and other रुकोs.
	 */
	करोwn_ग_लिखो(&fi->dax->sem);
	/*
	 * We dropped lock. Check again अगर somebody अन्यथा setup
	 * mapping alपढ़ोy.
	 */
	node = पूर्णांकerval_tree_iter_first(&fi->dax->tree, start_idx, start_idx);
	अगर (node) अणु
		dmap = node_to_dmap(node);
		fuse_fill_iomap(inode, pos, length, iomap, dmap, flags);
		dmap_add_to_मुक्त_pool(fcd, alloc_dmap);
		up_ग_लिखो(&fi->dax->sem);
		वापस 0;
	पूर्ण

	/* Setup one mapping */
	ret = fuse_setup_one_mapping(inode, pos >> FUSE_DAX_SHIFT, alloc_dmap,
				     writable, false);
	अगर (ret < 0) अणु
		dmap_add_to_मुक्त_pool(fcd, alloc_dmap);
		up_ग_लिखो(&fi->dax->sem);
		वापस ret;
	पूर्ण
	fuse_fill_iomap(inode, pos, length, iomap, alloc_dmap, flags);
	up_ग_लिखो(&fi->dax->sem);
	वापस 0;
पूर्ण

अटल पूर्णांक fuse_upgrade_dax_mapping(काष्ठा inode *inode, loff_t pos,
				    loff_t length, अचिन्हित पूर्णांक flags,
				    काष्ठा iomap *iomap)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	काष्ठा fuse_dax_mapping *dmap;
	पूर्णांक ret;
	अचिन्हित दीर्घ idx = pos >> FUSE_DAX_SHIFT;
	काष्ठा पूर्णांकerval_tree_node *node;

	/*
	 * Take exclusive lock so that only one caller can try to setup
	 * mapping and others रुको.
	 */
	करोwn_ग_लिखो(&fi->dax->sem);
	node = पूर्णांकerval_tree_iter_first(&fi->dax->tree, idx, idx);

	/* We are holding either inode lock or i_mmap_sem, and that should
	 * ensure that dmap can't be truncated. We are holding a reference
	 * on dmap and that should make sure it can't be reclaimed. So dmap
	 * should still be there in tree despite the fact we dropped and
	 * re-acquired the fi->dax->sem lock.
	 */
	ret = -EIO;
	अगर (WARN_ON(!node))
		जाओ out_err;

	dmap = node_to_dmap(node);

	/* We took an extra reference on dmap to make sure its not reclaimd.
	 * Now we hold fi->dax->sem lock and that reference is not needed
	 * anymore. Drop it.
	 */
	अगर (refcount_dec_and_test(&dmap->refcnt)) अणु
		/* refcount should not hit 0. This object only goes
		 * away when fuse connection goes away
		 */
		WARN_ON_ONCE(1);
	पूर्ण

	/* Maybe another thपढ़ो alपढ़ोy upgraded mapping जबतक we were not
	 * holding lock.
	 */
	अगर (dmap->writable) अणु
		ret = 0;
		जाओ out_fill_iomap;
	पूर्ण

	ret = fuse_setup_one_mapping(inode, pos >> FUSE_DAX_SHIFT, dmap, true,
				     true);
	अगर (ret < 0)
		जाओ out_err;
out_fill_iomap:
	fuse_fill_iomap(inode, pos, length, iomap, dmap, flags);
out_err:
	up_ग_लिखो(&fi->dax->sem);
	वापस ret;
पूर्ण

/* This is just क्रम DAX and the mapping is ephemeral, करो not use it क्रम other
 * purposes since there is no block device with a permanent mapping.
 */
अटल पूर्णांक fuse_iomap_begin(काष्ठा inode *inode, loff_t pos, loff_t length,
			    अचिन्हित पूर्णांक flags, काष्ठा iomap *iomap,
			    काष्ठा iomap *srcmap)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	काष्ठा fuse_dax_mapping *dmap;
	bool writable = flags & IOMAP_WRITE;
	अचिन्हित दीर्घ start_idx = pos >> FUSE_DAX_SHIFT;
	काष्ठा पूर्णांकerval_tree_node *node;

	/* We करोn't support FIEMAP */
	अगर (WARN_ON(flags & IOMAP_REPORT))
		वापस -EIO;

	iomap->offset = pos;
	iomap->flags = 0;
	iomap->bdev = शून्य;
	iomap->dax_dev = fc->dax->dev;

	/*
	 * Both पढ़ो/ग_लिखो and mmap path can race here. So we need something
	 * to make sure अगर we are setting up mapping, then other path रुकोs
	 *
	 * For now, use a semaphore क्रम this. It probably needs to be
	 * optimized later.
	 */
	करोwn_पढ़ो(&fi->dax->sem);
	node = पूर्णांकerval_tree_iter_first(&fi->dax->tree, start_idx, start_idx);
	अगर (node) अणु
		dmap = node_to_dmap(node);
		अगर (writable && !dmap->writable) अणु
			/* Upgrade पढ़ो-only mapping to पढ़ो-ग_लिखो. This will
			 * require exclusive fi->dax->sem lock as we करोn't want
			 * two thपढ़ोs to be trying to this simultaneously
			 * क्रम same dmap. So drop shared lock and acquire
			 * exclusive lock.
			 *
			 * Beक्रमe dropping fi->dax->sem lock, take reference
			 * on dmap so that its not मुक्तd by range reclaim.
			 */
			refcount_inc(&dmap->refcnt);
			up_पढ़ो(&fi->dax->sem);
			pr_debug("%s: Upgrading mapping at offset 0x%llx length 0x%llx\n",
				 __func__, pos, length);
			वापस fuse_upgrade_dax_mapping(inode, pos, length,
							flags, iomap);
		पूर्ण अन्यथा अणु
			fuse_fill_iomap(inode, pos, length, iomap, dmap, flags);
			up_पढ़ो(&fi->dax->sem);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		up_पढ़ो(&fi->dax->sem);
		pr_debug("%s: no mapping at offset 0x%llx length 0x%llx\n",
				__func__, pos, length);
		अगर (pos >= i_size_पढ़ो(inode))
			जाओ iomap_hole;

		वापस fuse_setup_new_dax_mapping(inode, pos, length, flags,
						  iomap);
	पूर्ण

	/*
	 * If पढ़ो beyond end of file happnes, fs code seems to वापस
	 * it as hole
	 */
iomap_hole:
	fuse_fill_iomap_hole(iomap, length);
	pr_debug("%s returning hole mapping. pos=0x%llx length_asked=0x%llx length_returned=0x%llx\n",
		 __func__, pos, length, iomap->length);
	वापस 0;
पूर्ण

अटल पूर्णांक fuse_iomap_end(काष्ठा inode *inode, loff_t pos, loff_t length,
			  sमाप_प्रकार written, अचिन्हित पूर्णांक flags,
			  काष्ठा iomap *iomap)
अणु
	काष्ठा fuse_dax_mapping *dmap = iomap->निजी;

	अगर (dmap) अणु
		अगर (refcount_dec_and_test(&dmap->refcnt)) अणु
			/* refcount should not hit 0. This object only goes
			 * away when fuse connection goes away
			 */
			WARN_ON_ONCE(1);
		पूर्ण
	पूर्ण

	/* DAX ग_लिखोs beyond end-of-file aren't handled using iomap, so the
	 * file size is unchanged and there is nothing to करो here.
	 */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iomap_ops fuse_iomap_ops = अणु
	.iomap_begin = fuse_iomap_begin,
	.iomap_end = fuse_iomap_end,
पूर्ण;

अटल व्योम fuse_रुको_dax_page(काष्ठा inode *inode)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);

	up_ग_लिखो(&fi->i_mmap_sem);
	schedule();
	करोwn_ग_लिखो(&fi->i_mmap_sem);
पूर्ण

/* Should be called with fi->i_mmap_sem lock held exclusively */
अटल पूर्णांक __fuse_dax_अवरोध_layouts(काष्ठा inode *inode, bool *retry,
				    loff_t start, loff_t end)
अणु
	काष्ठा page *page;

	page = dax_layout_busy_page_range(inode->i_mapping, start, end);
	अगर (!page)
		वापस 0;

	*retry = true;
	वापस ___रुको_var_event(&page->_refcount,
			atomic_पढ़ो(&page->_refcount) == 1, TASK_INTERRUPTIBLE,
			0, 0, fuse_रुको_dax_page(inode));
पूर्ण

/* dmap_end == 0 leads to unmapping of whole file */
पूर्णांक fuse_dax_अवरोध_layouts(काष्ठा inode *inode, u64 dmap_start,
				  u64 dmap_end)
अणु
	bool	retry;
	पूर्णांक	ret;

	करो अणु
		retry = false;
		ret = __fuse_dax_अवरोध_layouts(inode, &retry, dmap_start,
					       dmap_end);
	पूर्ण जबतक (ret == 0 && retry);

	वापस ret;
पूर्ण

sमाप_प्रकार fuse_dax_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	sमाप_प्रकार ret;

	अगर (iocb->ki_flags & IOCB_NOWAIT) अणु
		अगर (!inode_trylock_shared(inode))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		inode_lock_shared(inode);
	पूर्ण

	ret = dax_iomap_rw(iocb, to, &fuse_iomap_ops);
	inode_unlock_shared(inode);

	/* TODO file_accessed(iocb->f_filp) */
	वापस ret;
पूर्ण

अटल bool file_extending_ग_लिखो(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);

	वापस (iov_iter_rw(from) == WRITE &&
		((iocb->ki_pos) >= i_size_पढ़ो(inode) ||
		  (iocb->ki_pos + iov_iter_count(from) > i_size_पढ़ो(inode))));
पूर्ण

अटल sमाप_प्रकार fuse_dax_direct_ग_लिखो(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	काष्ठा fuse_io_priv io = FUSE_IO_PRIV_SYNC(iocb);
	sमाप_प्रकार ret;

	ret = fuse_direct_io(&io, from, &iocb->ki_pos, FUSE_DIO_WRITE);
	अगर (ret < 0)
		वापस ret;

	fuse_invalidate_attr(inode);
	fuse_ग_लिखो_update_size(inode, iocb->ki_pos);
	वापस ret;
पूर्ण

sमाप_प्रकार fuse_dax_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	sमाप_प्रकार ret;

	अगर (iocb->ki_flags & IOCB_NOWAIT) अणु
		अगर (!inode_trylock(inode))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		inode_lock(inode);
	पूर्ण

	ret = generic_ग_लिखो_checks(iocb, from);
	अगर (ret <= 0)
		जाओ out;

	ret = file_हटाओ_privs(iocb->ki_filp);
	अगर (ret)
		जाओ out;
	/* TODO file_update_समय() but we करोn't want metadata I/O */

	/* Do not use dax क्रम file extending ग_लिखोs as ग_लिखो and on
	 * disk i_size increase are not atomic otherwise.
	 */
	अगर (file_extending_ग_लिखो(iocb, from))
		ret = fuse_dax_direct_ग_लिखो(iocb, from);
	अन्यथा
		ret = dax_iomap_rw(iocb, from, &fuse_iomap_ops);

out:
	inode_unlock(inode);

	अगर (ret > 0)
		ret = generic_ग_लिखो_sync(iocb, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक fuse_dax_ग_लिखोpages(काष्ठा address_space *mapping,
			       काष्ठा ग_लिखोback_control *wbc)
अणु

	काष्ठा inode *inode = mapping->host;
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);

	वापस dax_ग_लिखोback_mapping_range(mapping, fc->dax->dev, wbc);
पूर्ण

अटल vm_fault_t __fuse_dax_fault(काष्ठा vm_fault *vmf,
				   क्रमागत page_entry_size pe_size, bool ग_लिखो)
अणु
	vm_fault_t ret;
	काष्ठा inode *inode = file_inode(vmf->vma->vm_file);
	काष्ठा super_block *sb = inode->i_sb;
	pfn_t pfn;
	पूर्णांक error = 0;
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	काष्ठा fuse_conn_dax *fcd = fc->dax;
	bool retry = false;

	अगर (ग_लिखो)
		sb_start_pagefault(sb);
retry:
	अगर (retry && !(fcd->nr_मुक्त_ranges > 0))
		रुको_event(fcd->range_रुकोq, (fcd->nr_मुक्त_ranges > 0));

	/*
	 * We need to serialize against not only truncate but also against
	 * fuse dax memory range reclaim. While a range is being reclaimed,
	 * we करो not want any पढ़ो/ग_लिखो/mmap to make progress and try
	 * to populate page cache or access memory we are trying to मुक्त.
	 */
	करोwn_पढ़ो(&get_fuse_inode(inode)->i_mmap_sem);
	ret = dax_iomap_fault(vmf, pe_size, &pfn, &error, &fuse_iomap_ops);
	अगर ((ret & VM_FAULT_ERROR) && error == -EAGAIN) अणु
		error = 0;
		retry = true;
		up_पढ़ो(&get_fuse_inode(inode)->i_mmap_sem);
		जाओ retry;
	पूर्ण

	अगर (ret & VM_FAULT_NEEDDSYNC)
		ret = dax_finish_sync_fault(vmf, pe_size, pfn);
	up_पढ़ो(&get_fuse_inode(inode)->i_mmap_sem);

	अगर (ग_लिखो)
		sb_end_pagefault(sb);

	वापस ret;
पूर्ण

अटल vm_fault_t fuse_dax_fault(काष्ठा vm_fault *vmf)
अणु
	वापस __fuse_dax_fault(vmf, PE_SIZE_PTE,
				vmf->flags & FAULT_FLAG_WRITE);
पूर्ण

अटल vm_fault_t fuse_dax_huge_fault(काष्ठा vm_fault *vmf,
			       क्रमागत page_entry_size pe_size)
अणु
	वापस __fuse_dax_fault(vmf, pe_size, vmf->flags & FAULT_FLAG_WRITE);
पूर्ण

अटल vm_fault_t fuse_dax_page_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	वापस __fuse_dax_fault(vmf, PE_SIZE_PTE, true);
पूर्ण

अटल vm_fault_t fuse_dax_pfn_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	वापस __fuse_dax_fault(vmf, PE_SIZE_PTE, true);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा fuse_dax_vm_ops = अणु
	.fault		= fuse_dax_fault,
	.huge_fault	= fuse_dax_huge_fault,
	.page_mkग_लिखो	= fuse_dax_page_mkग_लिखो,
	.pfn_mkग_लिखो	= fuse_dax_pfn_mkग_लिखो,
पूर्ण;

पूर्णांक fuse_dax_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	file_accessed(file);
	vma->vm_ops = &fuse_dax_vm_ops;
	vma->vm_flags |= VM_MIXEDMAP | VM_HUGEPAGE;
	वापस 0;
पूर्ण

अटल पूर्णांक dmap_ग_लिखोback_invalidate(काष्ठा inode *inode,
				     काष्ठा fuse_dax_mapping *dmap)
अणु
	पूर्णांक ret;
	loff_t start_pos = dmap->itn.start << FUSE_DAX_SHIFT;
	loff_t end_pos = (start_pos + FUSE_DAX_SZ - 1);

	ret = filemap_fdataग_लिखो_range(inode->i_mapping, start_pos, end_pos);
	अगर (ret) अणु
		pr_debug("fuse: filemap_fdatawrite_range() failed. err=%d start_pos=0x%llx, end_pos=0x%llx\n",
			 ret, start_pos, end_pos);
		वापस ret;
	पूर्ण

	ret = invalidate_inode_pages2_range(inode->i_mapping,
					    start_pos >> PAGE_SHIFT,
					    end_pos >> PAGE_SHIFT);
	अगर (ret)
		pr_debug("fuse: invalidate_inode_pages2_range() failed err=%d\n",
			 ret);

	वापस ret;
पूर्ण

अटल पूर्णांक reclaim_one_dmap_locked(काष्ठा inode *inode,
				   काष्ठा fuse_dax_mapping *dmap)
अणु
	पूर्णांक ret;
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);

	/*
	 * igrab() was करोne to make sure inode won't go under us, and this
	 * further aव्योमs the race with evict().
	 */
	ret = dmap_ग_लिखोback_invalidate(inode, dmap);
	अगर (ret)
		वापस ret;

	/* Remove dax mapping from inode पूर्णांकerval tree now */
	पूर्णांकerval_tree_हटाओ(&dmap->itn, &fi->dax->tree);
	fi->dax->nr--;

	/* It is possible that umount/shutकरोwn has समाप्तed the fuse connection
	 * and worker thपढ़ो is trying to reclaim memory in parallel.  Don't
	 * warn in that हाल.
	 */
	ret = dmap_हटाओmapping_one(inode, dmap);
	अगर (ret && ret != -ENOTCONN) अणु
		pr_warn("Failed to remove mapping. offset=0x%llx len=0x%llx ret=%d\n",
			dmap->winकरोw_offset, dmap->length, ret);
	पूर्ण
	वापस 0;
पूर्ण

/* Find first mapped dmap क्रम an inode and वापस file offset. Caller needs
 * to hold fi->dax->sem lock either shared or exclusive.
 */
अटल काष्ठा fuse_dax_mapping *inode_lookup_first_dmap(काष्ठा inode *inode)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	काष्ठा fuse_dax_mapping *dmap;
	काष्ठा पूर्णांकerval_tree_node *node;

	क्रम (node = पूर्णांकerval_tree_iter_first(&fi->dax->tree, 0, -1); node;
	     node = पूर्णांकerval_tree_iter_next(node, 0, -1)) अणु
		dmap = node_to_dmap(node);
		/* still in use. */
		अगर (refcount_पढ़ो(&dmap->refcnt) > 1)
			जारी;

		वापस dmap;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Find first mapping in the tree and मुक्त it and वापस it. Do not add
 * it back to मुक्त pool.
 */
अटल काष्ठा fuse_dax_mapping *
inode_अंतरभूत_reclaim_one_dmap(काष्ठा fuse_conn_dax *fcd, काष्ठा inode *inode,
			      bool *retry)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	काष्ठा fuse_dax_mapping *dmap;
	u64 dmap_start, dmap_end;
	अचिन्हित दीर्घ start_idx;
	पूर्णांक ret;
	काष्ठा पूर्णांकerval_tree_node *node;

	करोwn_ग_लिखो(&fi->i_mmap_sem);

	/* Lookup a dmap and corresponding file offset to reclaim. */
	करोwn_पढ़ो(&fi->dax->sem);
	dmap = inode_lookup_first_dmap(inode);
	अगर (dmap) अणु
		start_idx = dmap->itn.start;
		dmap_start = start_idx << FUSE_DAX_SHIFT;
		dmap_end = dmap_start + FUSE_DAX_SZ - 1;
	पूर्ण
	up_पढ़ो(&fi->dax->sem);

	अगर (!dmap)
		जाओ out_mmap_sem;
	/*
	 * Make sure there are no references to inode pages using
	 * get_user_pages()
	 */
	ret = fuse_dax_अवरोध_layouts(inode, dmap_start, dmap_end);
	अगर (ret) अणु
		pr_debug("fuse: fuse_dax_break_layouts() failed. err=%d\n",
			 ret);
		dmap = ERR_PTR(ret);
		जाओ out_mmap_sem;
	पूर्ण

	करोwn_ग_लिखो(&fi->dax->sem);
	node = पूर्णांकerval_tree_iter_first(&fi->dax->tree, start_idx, start_idx);
	/* Range alपढ़ोy got reclaimed by somebody अन्यथा */
	अगर (!node) अणु
		अगर (retry)
			*retry = true;
		जाओ out_ग_लिखो_dmap_sem;
	पूर्ण

	dmap = node_to_dmap(node);
	/* still in use. */
	अगर (refcount_पढ़ो(&dmap->refcnt) > 1) अणु
		dmap = शून्य;
		अगर (retry)
			*retry = true;
		जाओ out_ग_लिखो_dmap_sem;
	पूर्ण

	ret = reclaim_one_dmap_locked(inode, dmap);
	अगर (ret < 0) अणु
		dmap = ERR_PTR(ret);
		जाओ out_ग_लिखो_dmap_sem;
	पूर्ण

	/* Clean up dmap. Do not add back to मुक्त list */
	dmap_हटाओ_busy_list(fcd, dmap);
	dmap->inode = शून्य;
	dmap->itn.start = dmap->itn.last = 0;

	pr_debug("fuse: %s: inline reclaimed memory range. inode=%p, window_offset=0x%llx, length=0x%llx\n",
		 __func__, inode, dmap->winकरोw_offset, dmap->length);

out_ग_लिखो_dmap_sem:
	up_ग_लिखो(&fi->dax->sem);
out_mmap_sem:
	up_ग_लिखो(&fi->i_mmap_sem);
	वापस dmap;
पूर्ण

अटल काष्ठा fuse_dax_mapping *
alloc_dax_mapping_reclaim(काष्ठा fuse_conn_dax *fcd, काष्ठा inode *inode)
अणु
	काष्ठा fuse_dax_mapping *dmap;
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);

	जबतक (1) अणु
		bool retry = false;

		dmap = alloc_dax_mapping(fcd);
		अगर (dmap)
			वापस dmap;

		dmap = inode_अंतरभूत_reclaim_one_dmap(fcd, inode, &retry);
		/*
		 * Either we got a mapping or it is an error, वापस in both
		 * the हालs.
		 */
		अगर (dmap)
			वापस dmap;

		/* If we could not reclaim a mapping because it
		 * had a reference or some other temporary failure,
		 * Try again. We want to give up अंतरभूत reclaim only
		 * अगर there is no range asचिन्हित to this node. Otherwise
		 * अगर a deadlock is possible अगर we sleep with fi->i_mmap_sem
		 * held and worker to मुक्त memory can't make progress due
		 * to unavailability of fi->i_mmap_sem lock. So sleep
		 * only अगर fi->dax->nr=0
		 */
		अगर (retry)
			जारी;
		/*
		 * There are no mappings which can be reclaimed. Wait क्रम one.
		 * We are not holding fi->dax->sem. So it is possible
		 * that range माला_लो added now. But as we are not holding
		 * fi->i_mmap_sem, worker should still be able to मुक्त up
		 * a range and wake us up.
		 */
		अगर (!fi->dax->nr && !(fcd->nr_मुक्त_ranges > 0)) अणु
			अगर (रुको_event_समाप्तable_exclusive(fcd->range_रुकोq,
					(fcd->nr_मुक्त_ranges > 0))) अणु
				वापस ERR_PTR(-EINTR);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक lookup_and_reclaim_dmap_locked(काष्ठा fuse_conn_dax *fcd,
					  काष्ठा inode *inode,
					  अचिन्हित दीर्घ start_idx)
अणु
	पूर्णांक ret;
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	काष्ठा fuse_dax_mapping *dmap;
	काष्ठा पूर्णांकerval_tree_node *node;

	/* Find fuse dax mapping at file offset inode. */
	node = पूर्णांकerval_tree_iter_first(&fi->dax->tree, start_idx, start_idx);

	/* Range alपढ़ोy got cleaned up by somebody अन्यथा */
	अगर (!node)
		वापस 0;
	dmap = node_to_dmap(node);

	/* still in use. */
	अगर (refcount_पढ़ो(&dmap->refcnt) > 1)
		वापस 0;

	ret = reclaim_one_dmap_locked(inode, dmap);
	अगर (ret < 0)
		वापस ret;

	/* Cleanup dmap entry and add back to मुक्त list */
	spin_lock(&fcd->lock);
	dmap_reinit_add_to_मुक्त_pool(fcd, dmap);
	spin_unlock(&fcd->lock);
	वापस ret;
पूर्ण

/*
 * Free a range of memory.
 * Locking:
 * 1. Take fi->i_mmap_sem to block dax faults.
 * 2. Take fi->dax->sem to protect पूर्णांकerval tree and also to make sure
 *    पढ़ो/ग_लिखो can not reuse a dmap which we might be मुक्तing.
 */
अटल पूर्णांक lookup_and_reclaim_dmap(काष्ठा fuse_conn_dax *fcd,
				   काष्ठा inode *inode,
				   अचिन्हित दीर्घ start_idx,
				   अचिन्हित दीर्घ end_idx)
अणु
	पूर्णांक ret;
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	loff_t dmap_start = start_idx << FUSE_DAX_SHIFT;
	loff_t dmap_end = (dmap_start + FUSE_DAX_SZ) - 1;

	करोwn_ग_लिखो(&fi->i_mmap_sem);
	ret = fuse_dax_अवरोध_layouts(inode, dmap_start, dmap_end);
	अगर (ret) अणु
		pr_debug("virtio_fs: fuse_dax_break_layouts() failed. err=%d\n",
			 ret);
		जाओ out_mmap_sem;
	पूर्ण

	करोwn_ग_लिखो(&fi->dax->sem);
	ret = lookup_and_reclaim_dmap_locked(fcd, inode, start_idx);
	up_ग_लिखो(&fi->dax->sem);
out_mmap_sem:
	up_ग_लिखो(&fi->i_mmap_sem);
	वापस ret;
पूर्ण

अटल पूर्णांक try_to_मुक्त_dmap_chunks(काष्ठा fuse_conn_dax *fcd,
				   अचिन्हित दीर्घ nr_to_मुक्त)
अणु
	काष्ठा fuse_dax_mapping *dmap, *pos, *temp;
	पूर्णांक ret, nr_मुक्तd = 0;
	अचिन्हित दीर्घ start_idx = 0, end_idx = 0;
	काष्ठा inode *inode = शून्य;

	/* Pick first busy range and मुक्त it क्रम now*/
	जबतक (1) अणु
		अगर (nr_मुक्तd >= nr_to_मुक्त)
			अवरोध;

		dmap = शून्य;
		spin_lock(&fcd->lock);

		अगर (!fcd->nr_busy_ranges) अणु
			spin_unlock(&fcd->lock);
			वापस 0;
		पूर्ण

		list_क्रम_each_entry_safe(pos, temp, &fcd->busy_ranges,
						busy_list) अणु
			/* skip this range अगर it's in use. */
			अगर (refcount_पढ़ो(&pos->refcnt) > 1)
				जारी;

			inode = igrab(pos->inode);
			/*
			 * This inode is going away. That will मुक्त
			 * up all the ranges anyway, जारी to
			 * next range.
			 */
			अगर (!inode)
				जारी;
			/*
			 * Take this element off list and add it tail. If
			 * this element can't be मुक्तd, it will help with
			 * selecting new element in next iteration of loop.
			 */
			dmap = pos;
			list_move_tail(&dmap->busy_list, &fcd->busy_ranges);
			start_idx = end_idx = dmap->itn.start;
			अवरोध;
		पूर्ण
		spin_unlock(&fcd->lock);
		अगर (!dmap)
			वापस 0;

		ret = lookup_and_reclaim_dmap(fcd, inode, start_idx, end_idx);
		iput(inode);
		अगर (ret)
			वापस ret;
		nr_मुक्तd++;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम fuse_dax_मुक्त_mem_worker(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	काष्ठा fuse_conn_dax *fcd = container_of(work, काष्ठा fuse_conn_dax,
						 मुक्त_work.work);
	ret = try_to_मुक्त_dmap_chunks(fcd, FUSE_DAX_RECLAIM_CHUNK);
	अगर (ret) अणु
		pr_debug("fuse: try_to_free_dmap_chunks() failed with err=%d\n",
			 ret);
	पूर्ण

	/* If number of मुक्त ranges are still below threhold, requeue */
	kick_dmap_मुक्त_worker(fcd, 1);
पूर्ण

अटल व्योम fuse_मुक्त_dax_mem_ranges(काष्ठा list_head *mem_list)
अणु
	काष्ठा fuse_dax_mapping *range, *temp;

	/* Free All allocated elements */
	list_क्रम_each_entry_safe(range, temp, mem_list, list) अणु
		list_del(&range->list);
		अगर (!list_empty(&range->busy_list))
			list_del(&range->busy_list);
		kमुक्त(range);
	पूर्ण
पूर्ण

व्योम fuse_dax_conn_मुक्त(काष्ठा fuse_conn *fc)
अणु
	अगर (fc->dax) अणु
		fuse_मुक्त_dax_mem_ranges(&fc->dax->मुक्त_ranges);
		kमुक्त(fc->dax);
	पूर्ण
पूर्ण

अटल पूर्णांक fuse_dax_mem_range_init(काष्ठा fuse_conn_dax *fcd)
अणु
	दीर्घ nr_pages, nr_ranges;
	व्योम *kaddr;
	pfn_t pfn;
	काष्ठा fuse_dax_mapping *range;
	पूर्णांक ret, id;
	माप_प्रकार dax_size = -1;
	अचिन्हित दीर्घ i;

	init_रुकोqueue_head(&fcd->range_रुकोq);
	INIT_LIST_HEAD(&fcd->मुक्त_ranges);
	INIT_LIST_HEAD(&fcd->busy_ranges);
	INIT_DELAYED_WORK(&fcd->मुक्त_work, fuse_dax_मुक्त_mem_worker);

	id = dax_पढ़ो_lock();
	nr_pages = dax_direct_access(fcd->dev, 0, PHYS_PFN(dax_size), &kaddr,
				     &pfn);
	dax_पढ़ो_unlock(id);
	अगर (nr_pages < 0) अणु
		pr_debug("dax_direct_access() returned %ld\n", nr_pages);
		वापस nr_pages;
	पूर्ण

	nr_ranges = nr_pages/FUSE_DAX_PAGES;
	pr_debug("%s: dax mapped %ld pages. nr_ranges=%ld\n",
		__func__, nr_pages, nr_ranges);

	क्रम (i = 0; i < nr_ranges; i++) अणु
		range = kzalloc(माप(काष्ठा fuse_dax_mapping), GFP_KERNEL);
		ret = -ENOMEM;
		अगर (!range)
			जाओ out_err;

		/* TODO: This offset only works अगर virtio-fs driver is not
		 * having some memory hidden at the beginning. This needs
		 * better handling
		 */
		range->winकरोw_offset = i * FUSE_DAX_SZ;
		range->length = FUSE_DAX_SZ;
		INIT_LIST_HEAD(&range->busy_list);
		refcount_set(&range->refcnt, 1);
		list_add_tail(&range->list, &fcd->मुक्त_ranges);
	पूर्ण

	fcd->nr_मुक्त_ranges = nr_ranges;
	fcd->nr_ranges = nr_ranges;
	वापस 0;
out_err:
	/* Free All allocated elements */
	fuse_मुक्त_dax_mem_ranges(&fcd->मुक्त_ranges);
	वापस ret;
पूर्ण

पूर्णांक fuse_dax_conn_alloc(काष्ठा fuse_conn *fc, काष्ठा dax_device *dax_dev)
अणु
	काष्ठा fuse_conn_dax *fcd;
	पूर्णांक err;

	अगर (!dax_dev)
		वापस 0;

	fcd = kzalloc(माप(*fcd), GFP_KERNEL);
	अगर (!fcd)
		वापस -ENOMEM;

	spin_lock_init(&fcd->lock);
	fcd->dev = dax_dev;
	err = fuse_dax_mem_range_init(fcd);
	अगर (err) अणु
		kमुक्त(fcd);
		वापस err;
	पूर्ण

	fc->dax = fcd;
	वापस 0;
पूर्ण

bool fuse_dax_inode_alloc(काष्ठा super_block *sb, काष्ठा fuse_inode *fi)
अणु
	काष्ठा fuse_conn *fc = get_fuse_conn_super(sb);

	fi->dax = शून्य;
	अगर (fc->dax) अणु
		fi->dax = kzalloc(माप(*fi->dax), GFP_KERNEL_ACCOUNT);
		अगर (!fi->dax)
			वापस false;

		init_rwsem(&fi->dax->sem);
		fi->dax->tree = RB_ROOT_CACHED;
	पूर्ण

	वापस true;
पूर्ण

अटल स्थिर काष्ठा address_space_operations fuse_dax_file_aops  = अणु
	.ग_लिखोpages	= fuse_dax_ग_लिखोpages,
	.direct_IO	= noop_direct_IO,
	.set_page_dirty	= noop_set_page_dirty,
	.invalidatepage	= noop_invalidatepage,
पूर्ण;

व्योम fuse_dax_inode_init(काष्ठा inode *inode)
अणु
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);

	अगर (!fc->dax)
		वापस;

	inode->i_flags |= S_DAX;
	inode->i_data.a_ops = &fuse_dax_file_aops;
पूर्ण

bool fuse_dax_check_alignment(काष्ठा fuse_conn *fc, अचिन्हित पूर्णांक map_alignment)
अणु
	अगर (fc->dax && (map_alignment > FUSE_DAX_SHIFT)) अणु
		pr_warn("FUSE: map_alignment %u incompatible with dax mem range size %u\n",
			map_alignment, FUSE_DAX_SZ);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

व्योम fuse_dax_cancel_work(काष्ठा fuse_conn *fc)
अणु
	काष्ठा fuse_conn_dax *fcd = fc->dax;

	अगर (fcd)
		cancel_delayed_work_sync(&fcd->मुक्त_work);

पूर्ण
EXPORT_SYMBOL_GPL(fuse_dax_cancel_work);
