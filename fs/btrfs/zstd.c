<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016-present, Facebook, Inc.
 * All rights reserved.
 *
 */

#समावेश <linux/bपन.स>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/refcount.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/zstd.h>
#समावेश "misc.h"
#समावेश "compression.h"
#समावेश "ctree.h"

#घोषणा ZSTD_BTRFS_MAX_WINDOWLOG 17
#घोषणा ZSTD_BTRFS_MAX_INPUT (1 << ZSTD_BTRFS_MAX_WINDOWLOG)
#घोषणा ZSTD_BTRFS_DEFAULT_LEVEL 3
#घोषणा ZSTD_BTRFS_MAX_LEVEL 15
/* 307s to aव्योम pathologically clashing with transaction commit */
#घोषणा ZSTD_BTRFS_RECLAIM_JIFFIES (307 * HZ)

अटल ZSTD_parameters zstd_get_btrfs_parameters(अचिन्हित पूर्णांक level,
						 माप_प्रकार src_len)
अणु
	ZSTD_parameters params = ZSTD_getParams(level, src_len, 0);

	अगर (params.cParams.winकरोwLog > ZSTD_BTRFS_MAX_WINDOWLOG)
		params.cParams.winकरोwLog = ZSTD_BTRFS_MAX_WINDOWLOG;
	WARN_ON(src_len > ZSTD_BTRFS_MAX_INPUT);
	वापस params;
पूर्ण

काष्ठा workspace अणु
	व्योम *mem;
	माप_प्रकार size;
	अक्षर *buf;
	अचिन्हित पूर्णांक level;
	अचिन्हित पूर्णांक req_level;
	अचिन्हित दीर्घ last_used; /* jअगरfies */
	काष्ठा list_head list;
	काष्ठा list_head lru_list;
	ZSTD_inBuffer in_buf;
	ZSTD_outBuffer out_buf;
पूर्ण;

/*
 * Zstd Workspace Management
 *
 * Zstd workspaces have dअगरferent memory requirements depending on the level.
 * The zstd workspaces are managed by having inभागidual lists क्रम each level
 * and a global lru.  Forward progress is मुख्यtained by protecting a max level
 * workspace.
 *
 * Getting a workspace is करोne by using the biपंचांगap to identअगरy the levels that
 * have available workspaces and scans up.  This lets us recycle higher level
 * workspaces because of the monotonic memory guarantee.  A workspace's
 * last_used is only updated अगर it is being used by the corresponding memory
 * level.  Putting a workspace involves adding it back to the appropriate places
 * and adding it back to the lru अगर necessary.
 *
 * A समयr is used to reclaim workspaces अगर they have not been used क्रम
 * ZSTD_BTRFS_RECLAIM_JIFFIES.  This helps keep only active workspaces around.
 * The upper bound is provided by the workqueue limit which is 2 (percpu limit).
 */

काष्ठा zstd_workspace_manager अणु
	स्थिर काष्ठा btrfs_compress_op *ops;
	spinlock_t lock;
	काष्ठा list_head lru_list;
	काष्ठा list_head idle_ws[ZSTD_BTRFS_MAX_LEVEL];
	अचिन्हित दीर्घ active_map;
	रुको_queue_head_t रुको;
	काष्ठा समयr_list समयr;
पूर्ण;

अटल काष्ठा zstd_workspace_manager wsm;

अटल माप_प्रकार zstd_ws_mem_sizes[ZSTD_BTRFS_MAX_LEVEL];

अटल अंतरभूत काष्ठा workspace *list_to_workspace(काष्ठा list_head *list)
अणु
	वापस container_of(list, काष्ठा workspace, list);
पूर्ण

व्योम zstd_मुक्त_workspace(काष्ठा list_head *ws);
काष्ठा list_head *zstd_alloc_workspace(अचिन्हित पूर्णांक level);
/*
 * zstd_reclaim_समयr_fn - reclaim समयr
 * @t: समयr
 *
 * This scans the lru_list and attempts to reclaim any workspace that hasn't
 * been used क्रम ZSTD_BTRFS_RECLAIM_JIFFIES.
 */
अटल व्योम zstd_reclaim_समयr_fn(काष्ठा समयr_list *समयr)
अणु
	अचिन्हित दीर्घ reclaim_threshold = jअगरfies - ZSTD_BTRFS_RECLAIM_JIFFIES;
	काष्ठा list_head *pos, *next;

	spin_lock_bh(&wsm.lock);

	अगर (list_empty(&wsm.lru_list)) अणु
		spin_unlock_bh(&wsm.lock);
		वापस;
	पूर्ण

	list_क्रम_each_prev_safe(pos, next, &wsm.lru_list) अणु
		काष्ठा workspace *victim = container_of(pos, काष्ठा workspace,
							lru_list);
		अचिन्हित पूर्णांक level;

		अगर (समय_after(victim->last_used, reclaim_threshold))
			अवरोध;

		/* workspace is in use */
		अगर (victim->req_level)
			जारी;

		level = victim->level;
		list_del(&victim->lru_list);
		list_del(&victim->list);
		zstd_मुक्त_workspace(&victim->list);

		अगर (list_empty(&wsm.idle_ws[level - 1]))
			clear_bit(level - 1, &wsm.active_map);

	पूर्ण

	अगर (!list_empty(&wsm.lru_list))
		mod_समयr(&wsm.समयr, jअगरfies + ZSTD_BTRFS_RECLAIM_JIFFIES);

	spin_unlock_bh(&wsm.lock);
पूर्ण

/*
 * zstd_calc_ws_mem_sizes - calculate monotonic memory bounds
 *
 * It is possible based on the level configurations that a higher level
 * workspace uses less memory than a lower level workspace.  In order to reuse
 * workspaces, this must be made a monotonic relationship.  This precomputes
 * the required memory क्रम each level and enक्रमces the monotonicity between
 * level and memory required.
 */
अटल व्योम zstd_calc_ws_mem_sizes(व्योम)
अणु
	माप_प्रकार max_size = 0;
	अचिन्हित पूर्णांक level;

	क्रम (level = 1; level <= ZSTD_BTRFS_MAX_LEVEL; level++) अणु
		ZSTD_parameters params =
			zstd_get_btrfs_parameters(level, ZSTD_BTRFS_MAX_INPUT);
		माप_प्रकार level_size =
			max_t(माप_प्रकार,
			      ZSTD_CStreamWorkspaceBound(params.cParams),
			      ZSTD_DStreamWorkspaceBound(ZSTD_BTRFS_MAX_INPUT));

		max_size = max_t(माप_प्रकार, max_size, level_size);
		zstd_ws_mem_sizes[level - 1] = max_size;
	पूर्ण
पूर्ण

व्योम zstd_init_workspace_manager(व्योम)
अणु
	काष्ठा list_head *ws;
	पूर्णांक i;

	zstd_calc_ws_mem_sizes();

	wsm.ops = &btrfs_zstd_compress;
	spin_lock_init(&wsm.lock);
	init_रुकोqueue_head(&wsm.रुको);
	समयr_setup(&wsm.समयr, zstd_reclaim_समयr_fn, 0);

	INIT_LIST_HEAD(&wsm.lru_list);
	क्रम (i = 0; i < ZSTD_BTRFS_MAX_LEVEL; i++)
		INIT_LIST_HEAD(&wsm.idle_ws[i]);

	ws = zstd_alloc_workspace(ZSTD_BTRFS_MAX_LEVEL);
	अगर (IS_ERR(ws)) अणु
		pr_warn(
		"BTRFS: cannot preallocate zstd compression workspace\n");
	पूर्ण अन्यथा अणु
		set_bit(ZSTD_BTRFS_MAX_LEVEL - 1, &wsm.active_map);
		list_add(ws, &wsm.idle_ws[ZSTD_BTRFS_MAX_LEVEL - 1]);
	पूर्ण
पूर्ण

व्योम zstd_cleanup_workspace_manager(व्योम)
अणु
	काष्ठा workspace *workspace;
	पूर्णांक i;

	spin_lock_bh(&wsm.lock);
	क्रम (i = 0; i < ZSTD_BTRFS_MAX_LEVEL; i++) अणु
		जबतक (!list_empty(&wsm.idle_ws[i])) अणु
			workspace = container_of(wsm.idle_ws[i].next,
						 काष्ठा workspace, list);
			list_del(&workspace->list);
			list_del(&workspace->lru_list);
			zstd_मुक्त_workspace(&workspace->list);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&wsm.lock);

	del_समयr_sync(&wsm.समयr);
पूर्ण

/*
 * zstd_find_workspace - find workspace
 * @level: compression level
 *
 * This iterates over the set bits in the active_map beginning at the requested
 * compression level.  This lets us utilize alपढ़ोy allocated workspaces beक्रमe
 * allocating a new one.  If the workspace is of a larger size, it is used, but
 * the place in the lru_list and last_used बार are not updated.  This is to
 * offer the opportunity to reclaim the workspace in favor of allocating an
 * appropriately sized one in the future.
 */
अटल काष्ठा list_head *zstd_find_workspace(अचिन्हित पूर्णांक level)
अणु
	काष्ठा list_head *ws;
	काष्ठा workspace *workspace;
	पूर्णांक i = level - 1;

	spin_lock_bh(&wsm.lock);
	क्रम_each_set_bit_from(i, &wsm.active_map, ZSTD_BTRFS_MAX_LEVEL) अणु
		अगर (!list_empty(&wsm.idle_ws[i])) अणु
			ws = wsm.idle_ws[i].next;
			workspace = list_to_workspace(ws);
			list_del_init(ws);
			/* keep its place अगर it's a lower level using this */
			workspace->req_level = level;
			अगर (level == workspace->level)
				list_del(&workspace->lru_list);
			अगर (list_empty(&wsm.idle_ws[i]))
				clear_bit(i, &wsm.active_map);
			spin_unlock_bh(&wsm.lock);
			वापस ws;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&wsm.lock);

	वापस शून्य;
पूर्ण

/*
 * zstd_get_workspace - zstd's get_workspace
 * @level: compression level
 *
 * If @level is 0, then any compression level can be used.  Thereक्रमe, we begin
 * scanning from 1.  We first scan through possible workspaces and then after
 * attempt to allocate a new workspace.  If we fail to allocate one due to
 * memory pressure, go to sleep रुकोing क्रम the max level workspace to मुक्त up.
 */
काष्ठा list_head *zstd_get_workspace(अचिन्हित पूर्णांक level)
अणु
	काष्ठा list_head *ws;
	अचिन्हित पूर्णांक nofs_flag;

	/* level == 0 means we can use any workspace */
	अगर (!level)
		level = 1;

again:
	ws = zstd_find_workspace(level);
	अगर (ws)
		वापस ws;

	nofs_flag = meदो_स्मृति_nofs_save();
	ws = zstd_alloc_workspace(level);
	meदो_स्मृति_nofs_restore(nofs_flag);

	अगर (IS_ERR(ws)) अणु
		DEFINE_WAIT(रुको);

		prepare_to_रुको(&wsm.रुको, &रुको, TASK_UNINTERRUPTIBLE);
		schedule();
		finish_रुको(&wsm.रुको, &रुको);

		जाओ again;
	पूर्ण

	वापस ws;
पूर्ण

/*
 * zstd_put_workspace - zstd put_workspace
 * @ws: list_head क्रम the workspace
 *
 * When putting back a workspace, we only need to update the LRU अगर we are of
 * the requested compression level.  Here is where we जारी to protect the
 * max level workspace or update last_used accordingly.  If the reclaim समयr
 * isn't set, it is also set here.  Only the max level workspace tries and wakes
 * up रुकोing workspaces.
 */
व्योम zstd_put_workspace(काष्ठा list_head *ws)
अणु
	काष्ठा workspace *workspace = list_to_workspace(ws);

	spin_lock_bh(&wsm.lock);

	/* A node is only taken off the lru अगर we are the corresponding level */
	अगर (workspace->req_level == workspace->level) अणु
		/* Hide a max level workspace from reclaim */
		अगर (list_empty(&wsm.idle_ws[ZSTD_BTRFS_MAX_LEVEL - 1])) अणु
			INIT_LIST_HEAD(&workspace->lru_list);
		पूर्ण अन्यथा अणु
			workspace->last_used = jअगरfies;
			list_add(&workspace->lru_list, &wsm.lru_list);
			अगर (!समयr_pending(&wsm.समयr))
				mod_समयr(&wsm.समयr,
					  jअगरfies + ZSTD_BTRFS_RECLAIM_JIFFIES);
		पूर्ण
	पूर्ण

	set_bit(workspace->level - 1, &wsm.active_map);
	list_add(&workspace->list, &wsm.idle_ws[workspace->level - 1]);
	workspace->req_level = 0;

	spin_unlock_bh(&wsm.lock);

	अगर (workspace->level == ZSTD_BTRFS_MAX_LEVEL)
		cond_wake_up(&wsm.रुको);
पूर्ण

व्योम zstd_मुक्त_workspace(काष्ठा list_head *ws)
अणु
	काष्ठा workspace *workspace = list_entry(ws, काष्ठा workspace, list);

	kvमुक्त(workspace->mem);
	kमुक्त(workspace->buf);
	kमुक्त(workspace);
पूर्ण

काष्ठा list_head *zstd_alloc_workspace(अचिन्हित पूर्णांक level)
अणु
	काष्ठा workspace *workspace;

	workspace = kzalloc(माप(*workspace), GFP_KERNEL);
	अगर (!workspace)
		वापस ERR_PTR(-ENOMEM);

	workspace->size = zstd_ws_mem_sizes[level - 1];
	workspace->level = level;
	workspace->req_level = level;
	workspace->last_used = jअगरfies;
	workspace->mem = kvदो_स्मृति(workspace->size, GFP_KERNEL);
	workspace->buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!workspace->mem || !workspace->buf)
		जाओ fail;

	INIT_LIST_HEAD(&workspace->list);
	INIT_LIST_HEAD(&workspace->lru_list);

	वापस &workspace->list;
fail:
	zstd_मुक्त_workspace(&workspace->list);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

पूर्णांक zstd_compress_pages(काष्ठा list_head *ws, काष्ठा address_space *mapping,
		u64 start, काष्ठा page **pages, अचिन्हित दीर्घ *out_pages,
		अचिन्हित दीर्घ *total_in, अचिन्हित दीर्घ *total_out)
अणु
	काष्ठा workspace *workspace = list_entry(ws, काष्ठा workspace, list);
	ZSTD_CStream *stream;
	पूर्णांक ret = 0;
	पूर्णांक nr_pages = 0;
	काष्ठा page *in_page = शून्य;  /* The current page to पढ़ो */
	काष्ठा page *out_page = शून्य; /* The current page to ग_लिखो to */
	अचिन्हित दीर्घ tot_in = 0;
	अचिन्हित दीर्घ tot_out = 0;
	अचिन्हित दीर्घ len = *total_out;
	स्थिर अचिन्हित दीर्घ nr_dest_pages = *out_pages;
	अचिन्हित दीर्घ max_out = nr_dest_pages * PAGE_SIZE;
	ZSTD_parameters params = zstd_get_btrfs_parameters(workspace->req_level,
							   len);

	*out_pages = 0;
	*total_out = 0;
	*total_in = 0;

	/* Initialize the stream */
	stream = ZSTD_initCStream(params, len, workspace->mem,
			workspace->size);
	अगर (!stream) अणु
		pr_warn("BTRFS: ZSTD_initCStream failed\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	/* map in the first page of input data */
	in_page = find_get_page(mapping, start >> PAGE_SHIFT);
	workspace->in_buf.src = kmap(in_page);
	workspace->in_buf.pos = 0;
	workspace->in_buf.size = min_t(माप_प्रकार, len, PAGE_SIZE);


	/* Allocate and map in the output buffer */
	out_page = alloc_page(GFP_NOFS | __GFP_HIGHMEM);
	अगर (out_page == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	pages[nr_pages++] = out_page;
	workspace->out_buf.dst = kmap(out_page);
	workspace->out_buf.pos = 0;
	workspace->out_buf.size = min_t(माप_प्रकार, max_out, PAGE_SIZE);

	जबतक (1) अणु
		माप_प्रकार ret2;

		ret2 = ZSTD_compressStream(stream, &workspace->out_buf,
				&workspace->in_buf);
		अगर (ZSTD_isError(ret2)) अणु
			pr_debug("BTRFS: ZSTD_compressStream returned %d\n",
					ZSTD_getErrorCode(ret2));
			ret = -EIO;
			जाओ out;
		पूर्ण

		/* Check to see अगर we are making it bigger */
		अगर (tot_in + workspace->in_buf.pos > 8192 &&
				tot_in + workspace->in_buf.pos <
				tot_out + workspace->out_buf.pos) अणु
			ret = -E2BIG;
			जाओ out;
		पूर्ण

		/* We've reached the end of our output range */
		अगर (workspace->out_buf.pos >= max_out) अणु
			tot_out += workspace->out_buf.pos;
			ret = -E2BIG;
			जाओ out;
		पूर्ण

		/* Check अगर we need more output space */
		अगर (workspace->out_buf.pos == workspace->out_buf.size) अणु
			tot_out += PAGE_SIZE;
			max_out -= PAGE_SIZE;
			kunmap(out_page);
			अगर (nr_pages == nr_dest_pages) अणु
				out_page = शून्य;
				ret = -E2BIG;
				जाओ out;
			पूर्ण
			out_page = alloc_page(GFP_NOFS | __GFP_HIGHMEM);
			अगर (out_page == शून्य) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			pages[nr_pages++] = out_page;
			workspace->out_buf.dst = kmap(out_page);
			workspace->out_buf.pos = 0;
			workspace->out_buf.size = min_t(माप_प्रकार, max_out,
							PAGE_SIZE);
		पूर्ण

		/* We've reached the end of the input */
		अगर (workspace->in_buf.pos >= len) अणु
			tot_in += workspace->in_buf.pos;
			अवरोध;
		पूर्ण

		/* Check अगर we need more input */
		अगर (workspace->in_buf.pos == workspace->in_buf.size) अणु
			tot_in += PAGE_SIZE;
			kunmap(in_page);
			put_page(in_page);

			start += PAGE_SIZE;
			len -= PAGE_SIZE;
			in_page = find_get_page(mapping, start >> PAGE_SHIFT);
			workspace->in_buf.src = kmap(in_page);
			workspace->in_buf.pos = 0;
			workspace->in_buf.size = min_t(माप_प्रकार, len, PAGE_SIZE);
		पूर्ण
	पूर्ण
	जबतक (1) अणु
		माप_प्रकार ret2;

		ret2 = ZSTD_endStream(stream, &workspace->out_buf);
		अगर (ZSTD_isError(ret2)) अणु
			pr_debug("BTRFS: ZSTD_endStream returned %d\n",
					ZSTD_getErrorCode(ret2));
			ret = -EIO;
			जाओ out;
		पूर्ण
		अगर (ret2 == 0) अणु
			tot_out += workspace->out_buf.pos;
			अवरोध;
		पूर्ण
		अगर (workspace->out_buf.pos >= max_out) अणु
			tot_out += workspace->out_buf.pos;
			ret = -E2BIG;
			जाओ out;
		पूर्ण

		tot_out += PAGE_SIZE;
		max_out -= PAGE_SIZE;
		kunmap(out_page);
		अगर (nr_pages == nr_dest_pages) अणु
			out_page = शून्य;
			ret = -E2BIG;
			जाओ out;
		पूर्ण
		out_page = alloc_page(GFP_NOFS | __GFP_HIGHMEM);
		अगर (out_page == शून्य) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		pages[nr_pages++] = out_page;
		workspace->out_buf.dst = kmap(out_page);
		workspace->out_buf.pos = 0;
		workspace->out_buf.size = min_t(माप_प्रकार, max_out, PAGE_SIZE);
	पूर्ण

	अगर (tot_out >= tot_in) अणु
		ret = -E2BIG;
		जाओ out;
	पूर्ण

	ret = 0;
	*total_in = tot_in;
	*total_out = tot_out;
out:
	*out_pages = nr_pages;
	/* Cleanup */
	अगर (in_page) अणु
		kunmap(in_page);
		put_page(in_page);
	पूर्ण
	अगर (out_page)
		kunmap(out_page);
	वापस ret;
पूर्ण

पूर्णांक zstd_decompress_bio(काष्ठा list_head *ws, काष्ठा compressed_bio *cb)
अणु
	काष्ठा workspace *workspace = list_entry(ws, काष्ठा workspace, list);
	काष्ठा page **pages_in = cb->compressed_pages;
	u64 disk_start = cb->start;
	काष्ठा bio *orig_bio = cb->orig_bio;
	माप_प्रकार srclen = cb->compressed_len;
	ZSTD_DStream *stream;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ page_in_index = 0;
	अचिन्हित दीर्घ total_pages_in = DIV_ROUND_UP(srclen, PAGE_SIZE);
	अचिन्हित दीर्घ buf_start;
	अचिन्हित दीर्घ total_out = 0;

	stream = ZSTD_initDStream(
			ZSTD_BTRFS_MAX_INPUT, workspace->mem, workspace->size);
	अगर (!stream) अणु
		pr_debug("BTRFS: ZSTD_initDStream failed\n");
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	workspace->in_buf.src = kmap(pages_in[page_in_index]);
	workspace->in_buf.pos = 0;
	workspace->in_buf.size = min_t(माप_प्रकार, srclen, PAGE_SIZE);

	workspace->out_buf.dst = workspace->buf;
	workspace->out_buf.pos = 0;
	workspace->out_buf.size = PAGE_SIZE;

	जबतक (1) अणु
		माप_प्रकार ret2;

		ret2 = ZSTD_decompressStream(stream, &workspace->out_buf,
				&workspace->in_buf);
		अगर (ZSTD_isError(ret2)) अणु
			pr_debug("BTRFS: ZSTD_decompressStream returned %d\n",
					ZSTD_getErrorCode(ret2));
			ret = -EIO;
			जाओ करोne;
		पूर्ण
		buf_start = total_out;
		total_out += workspace->out_buf.pos;
		workspace->out_buf.pos = 0;

		ret = btrfs_decompress_buf2page(workspace->out_buf.dst,
				buf_start, total_out, disk_start, orig_bio);
		अगर (ret == 0)
			अवरोध;

		अगर (workspace->in_buf.pos >= srclen)
			अवरोध;

		/* Check अगर we've hit the end of a frame */
		अगर (ret2 == 0)
			अवरोध;

		अगर (workspace->in_buf.pos == workspace->in_buf.size) अणु
			kunmap(pages_in[page_in_index++]);
			अगर (page_in_index >= total_pages_in) अणु
				workspace->in_buf.src = शून्य;
				ret = -EIO;
				जाओ करोne;
			पूर्ण
			srclen -= PAGE_SIZE;
			workspace->in_buf.src = kmap(pages_in[page_in_index]);
			workspace->in_buf.pos = 0;
			workspace->in_buf.size = min_t(माप_प्रकार, srclen, PAGE_SIZE);
		पूर्ण
	पूर्ण
	ret = 0;
	zero_fill_bio(orig_bio);
करोne:
	अगर (workspace->in_buf.src)
		kunmap(pages_in[page_in_index]);
	वापस ret;
पूर्ण

पूर्णांक zstd_decompress(काष्ठा list_head *ws, अचिन्हित अक्षर *data_in,
		काष्ठा page *dest_page, अचिन्हित दीर्घ start_byte, माप_प्रकार srclen,
		माप_प्रकार destlen)
अणु
	काष्ठा workspace *workspace = list_entry(ws, काष्ठा workspace, list);
	ZSTD_DStream *stream;
	पूर्णांक ret = 0;
	माप_प्रकार ret2;
	अचिन्हित दीर्घ total_out = 0;
	अचिन्हित दीर्घ pg_offset = 0;

	stream = ZSTD_initDStream(
			ZSTD_BTRFS_MAX_INPUT, workspace->mem, workspace->size);
	अगर (!stream) अणु
		pr_warn("BTRFS: ZSTD_initDStream failed\n");
		ret = -EIO;
		जाओ finish;
	पूर्ण

	destlen = min_t(माप_प्रकार, destlen, PAGE_SIZE);

	workspace->in_buf.src = data_in;
	workspace->in_buf.pos = 0;
	workspace->in_buf.size = srclen;

	workspace->out_buf.dst = workspace->buf;
	workspace->out_buf.pos = 0;
	workspace->out_buf.size = PAGE_SIZE;

	ret2 = 1;
	जबतक (pg_offset < destlen
	       && workspace->in_buf.pos < workspace->in_buf.size) अणु
		अचिन्हित दीर्घ buf_start;
		अचिन्हित दीर्घ buf_offset;
		अचिन्हित दीर्घ bytes;

		/* Check अगर the frame is over and we still need more input */
		अगर (ret2 == 0) अणु
			pr_debug("BTRFS: ZSTD_decompressStream ended early\n");
			ret = -EIO;
			जाओ finish;
		पूर्ण
		ret2 = ZSTD_decompressStream(stream, &workspace->out_buf,
				&workspace->in_buf);
		अगर (ZSTD_isError(ret2)) अणु
			pr_debug("BTRFS: ZSTD_decompressStream returned %d\n",
					ZSTD_getErrorCode(ret2));
			ret = -EIO;
			जाओ finish;
		पूर्ण

		buf_start = total_out;
		total_out += workspace->out_buf.pos;
		workspace->out_buf.pos = 0;

		अगर (total_out <= start_byte)
			जारी;

		अगर (total_out > start_byte && buf_start < start_byte)
			buf_offset = start_byte - buf_start;
		अन्यथा
			buf_offset = 0;

		bytes = min_t(अचिन्हित दीर्घ, destlen - pg_offset,
				workspace->out_buf.size - buf_offset);

		स_नकल_to_page(dest_page, pg_offset,
			       workspace->out_buf.dst + buf_offset, bytes);

		pg_offset += bytes;
	पूर्ण
	ret = 0;
finish:
	अगर (pg_offset < destlen) अणु
		memzero_page(dest_page, pg_offset, destlen - pg_offset);
	पूर्ण
	वापस ret;
पूर्ण

स्थिर काष्ठा btrfs_compress_op btrfs_zstd_compress = अणु
	/* ZSTD uses own workspace manager */
	.workspace_manager = शून्य,
	.max_level	= ZSTD_BTRFS_MAX_LEVEL,
	.शेष_level	= ZSTD_BTRFS_DEFAULT_LEVEL,
पूर्ण;
