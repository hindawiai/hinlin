<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2016 CNEX Lअसल
 * Initial release: Javier Gonzalez <javier@cnexद_असल.com>
 *
 * Based upon the circular ringbuffer.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * pblk-rb.c - pblk's ग_लिखो buffer
 */

#समावेश <linux/circ_buf.h>

#समावेश "pblk.h"

अटल DECLARE_RWSEM(pblk_rb_lock);

अटल व्योम pblk_rb_data_मुक्त(काष्ठा pblk_rb *rb)
अणु
	काष्ठा pblk_rb_pages *p, *t;

	करोwn_ग_लिखो(&pblk_rb_lock);
	list_क्रम_each_entry_safe(p, t, &rb->pages, list) अणु
		मुक्त_pages((अचिन्हित दीर्घ)page_address(p->pages), p->order);
		list_del(&p->list);
		kमुक्त(p);
	पूर्ण
	up_ग_लिखो(&pblk_rb_lock);
पूर्ण

व्योम pblk_rb_मुक्त(काष्ठा pblk_rb *rb)
अणु
	pblk_rb_data_मुक्त(rb);
	vमुक्त(rb->entries);
पूर्ण

/*
 * pblk_rb_calculate_size -- calculate the size of the ग_लिखो buffer
 */
अटल अचिन्हित पूर्णांक pblk_rb_calculate_size(अचिन्हित पूर्णांक nr_entries,
					   अचिन्हित पूर्णांक threshold)
अणु
	अचिन्हित पूर्णांक thr_sz = 1 << (get_count_order(threshold + NVM_MAX_VLBA));
	अचिन्हित पूर्णांक max_sz = max(thr_sz, nr_entries);
	अचिन्हित पूर्णांक max_io;

	/* Alloc a ग_लिखो buffer that can (i) fit at least two split bios
	 * (considering max I/O size NVM_MAX_VLBA, and (ii) guarantee that the
	 * threshold will be respected
	 */
	max_io = (1 << max((पूर्णांक)(get_count_order(max_sz)),
				(पूर्णांक)(get_count_order(NVM_MAX_VLBA << 1))));
	अगर ((threshold + NVM_MAX_VLBA) >= max_io)
		max_io <<= 1;

	वापस max_io;
पूर्ण

/*
 * Initialize ring buffer. The data and metadata buffers must be previously
 * allocated and their size must be a घातer of two
 * (Documentation/core-api/circular-buffers.rst)
 */
पूर्णांक pblk_rb_init(काष्ठा pblk_rb *rb, अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक threshold,
		 अचिन्हित पूर्णांक seg_size)
अणु
	काष्ठा pblk *pblk = container_of(rb, काष्ठा pblk, rwb);
	काष्ठा pblk_rb_entry *entries;
	अचिन्हित पूर्णांक init_entry = 0;
	अचिन्हित पूर्णांक max_order = MAX_ORDER - 1;
	अचिन्हित पूर्णांक घातer_size, घातer_seg_sz;
	अचिन्हित पूर्णांक alloc_order, order, iter;
	अचिन्हित पूर्णांक nr_entries;

	nr_entries = pblk_rb_calculate_size(size, threshold);
	entries = vzalloc(array_size(nr_entries, माप(काष्ठा pblk_rb_entry)));
	अगर (!entries)
		वापस -ENOMEM;

	घातer_size = get_count_order(nr_entries);
	घातer_seg_sz = get_count_order(seg_size);

	करोwn_ग_लिखो(&pblk_rb_lock);
	rb->entries = entries;
	rb->seg_size = (1 << घातer_seg_sz);
	rb->nr_entries = (1 << घातer_size);
	rb->mem = rb->subm = rb->sync = rb->l2p_update = 0;
	rb->back_thres = threshold;
	rb->flush_poपूर्णांक = EMPTY_ENTRY;

	spin_lock_init(&rb->w_lock);
	spin_lock_init(&rb->s_lock);

	INIT_LIST_HEAD(&rb->pages);

	alloc_order = घातer_size;
	अगर (alloc_order >= max_order) अणु
		order = max_order;
		iter = (1 << (alloc_order - max_order));
	पूर्ण अन्यथा अणु
		order = alloc_order;
		iter = 1;
	पूर्ण

	करो अणु
		काष्ठा pblk_rb_entry *entry;
		काष्ठा pblk_rb_pages *page_set;
		व्योम *kaddr;
		अचिन्हित दीर्घ set_size;
		पूर्णांक i;

		page_set = kदो_स्मृति(माप(काष्ठा pblk_rb_pages), GFP_KERNEL);
		अगर (!page_set) अणु
			up_ग_लिखो(&pblk_rb_lock);
			vमुक्त(entries);
			वापस -ENOMEM;
		पूर्ण

		page_set->order = order;
		page_set->pages = alloc_pages(GFP_KERNEL, order);
		अगर (!page_set->pages) अणु
			kमुक्त(page_set);
			pblk_rb_data_मुक्त(rb);
			up_ग_लिखो(&pblk_rb_lock);
			vमुक्त(entries);
			वापस -ENOMEM;
		पूर्ण
		kaddr = page_address(page_set->pages);

		entry = &rb->entries[init_entry];
		entry->data = kaddr;
		entry->cacheline = pblk_cacheline_to_addr(init_entry++);
		entry->w_ctx.flags = PBLK_WRITABLE_ENTRY;

		set_size = (1 << order);
		क्रम (i = 1; i < set_size; i++) अणु
			entry = &rb->entries[init_entry];
			entry->cacheline = pblk_cacheline_to_addr(init_entry++);
			entry->data = kaddr + (i * rb->seg_size);
			entry->w_ctx.flags = PBLK_WRITABLE_ENTRY;
			bio_list_init(&entry->w_ctx.bios);
		पूर्ण

		list_add_tail(&page_set->list, &rb->pages);
		iter--;
	पूर्ण जबतक (iter > 0);
	up_ग_लिखो(&pblk_rb_lock);

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	atomic_set(&rb->inflight_flush_poपूर्णांक, 0);
#पूर्ण_अगर

	/*
	 * Initialize rate-limiter, which controls access to the ग_लिखो buffer
	 * by user and GC I/O
	 */
	pblk_rl_init(&pblk->rl, rb->nr_entries, threshold);

	वापस 0;
पूर्ण

अटल व्योम clean_wctx(काष्ठा pblk_w_ctx *w_ctx)
अणु
	पूर्णांक flags;

	flags = READ_ONCE(w_ctx->flags);
	WARN_ONCE(!(flags & PBLK_SUBMITTED_ENTRY),
			"pblk: overwriting unsubmitted data\n");

	/* Release flags on context. Protect from ग_लिखोs and पढ़ोs */
	smp_store_release(&w_ctx->flags, PBLK_WRITABLE_ENTRY);
	pblk_ppa_set_empty(&w_ctx->ppa);
	w_ctx->lba = ADDR_EMPTY;
पूर्ण

#घोषणा pblk_rb_ring_count(head, tail, size) CIRC_CNT(head, tail, size)
#घोषणा pblk_rb_ring_space(rb, head, tail, size) \
					(CIRC_SPACE(head, tail, size))

/*
 * Buffer space is calculated with respect to the back poपूर्णांकer संकेतing
 * synchronized entries to the media.
 */
अटल अचिन्हित पूर्णांक pblk_rb_space(काष्ठा pblk_rb *rb)
अणु
	अचिन्हित पूर्णांक mem = READ_ONCE(rb->mem);
	अचिन्हित पूर्णांक sync = READ_ONCE(rb->sync);

	वापस pblk_rb_ring_space(rb, mem, sync, rb->nr_entries);
पूर्ण

अचिन्हित पूर्णांक pblk_rb_ptr_wrap(काष्ठा pblk_rb *rb, अचिन्हित पूर्णांक p,
			      अचिन्हित पूर्णांक nr_entries)
अणु
	वापस (p + nr_entries) & (rb->nr_entries - 1);
पूर्ण

/*
 * Buffer count is calculated with respect to the submission entry संकेतing the
 * entries that are available to send to the media
 */
अचिन्हित पूर्णांक pblk_rb_पढ़ो_count(काष्ठा pblk_rb *rb)
अणु
	अचिन्हित पूर्णांक mem = READ_ONCE(rb->mem);
	अचिन्हित पूर्णांक subm = READ_ONCE(rb->subm);

	वापस pblk_rb_ring_count(mem, subm, rb->nr_entries);
पूर्ण

अचिन्हित पूर्णांक pblk_rb_sync_count(काष्ठा pblk_rb *rb)
अणु
	अचिन्हित पूर्णांक mem = READ_ONCE(rb->mem);
	अचिन्हित पूर्णांक sync = READ_ONCE(rb->sync);

	वापस pblk_rb_ring_count(mem, sync, rb->nr_entries);
पूर्ण

अचिन्हित पूर्णांक pblk_rb_पढ़ो_commit(काष्ठा pblk_rb *rb, अचिन्हित पूर्णांक nr_entries)
अणु
	अचिन्हित पूर्णांक subm;

	subm = READ_ONCE(rb->subm);
	/* Commit पढ़ो means updating submission poपूर्णांकer */
	smp_store_release(&rb->subm, pblk_rb_ptr_wrap(rb, subm, nr_entries));

	वापस subm;
पूर्ण

अटल पूर्णांक __pblk_rb_update_l2p(काष्ठा pblk_rb *rb, अचिन्हित पूर्णांक to_update)
अणु
	काष्ठा pblk *pblk = container_of(rb, काष्ठा pblk, rwb);
	काष्ठा pblk_line *line;
	काष्ठा pblk_rb_entry *entry;
	काष्ठा pblk_w_ctx *w_ctx;
	अचिन्हित पूर्णांक user_io = 0, gc_io = 0;
	अचिन्हित पूर्णांक i;
	पूर्णांक flags;

	क्रम (i = 0; i < to_update; i++) अणु
		entry = &rb->entries[rb->l2p_update];
		w_ctx = &entry->w_ctx;

		flags = READ_ONCE(entry->w_ctx.flags);
		अगर (flags & PBLK_IOTYPE_USER)
			user_io++;
		अन्यथा अगर (flags & PBLK_IOTYPE_GC)
			gc_io++;
		अन्यथा
			WARN(1, "pblk: unknown IO type\n");

		pblk_update_map_dev(pblk, w_ctx->lba, w_ctx->ppa,
							entry->cacheline);

		line = pblk_ppa_to_line(pblk, w_ctx->ppa);
		atomic_dec(&line->sec_to_update);
		kref_put(&line->ref, pblk_line_put);
		clean_wctx(w_ctx);
		rb->l2p_update = pblk_rb_ptr_wrap(rb, rb->l2p_update, 1);
	पूर्ण

	pblk_rl_out(&pblk->rl, user_io, gc_io);

	वापस 0;
पूर्ण

/*
 * When we move the l2p_update poपूर्णांकer, we update the l2p table - lookups will
 * poपूर्णांक to the physical address instead of to the cacheline in the ग_लिखो buffer
 * from this moment on.
 */
अटल पूर्णांक pblk_rb_update_l2p(काष्ठा pblk_rb *rb, अचिन्हित पूर्णांक nr_entries,
			      अचिन्हित पूर्णांक mem, अचिन्हित पूर्णांक sync)
अणु
	अचिन्हित पूर्णांक space, count;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&rb->w_lock);

	/* Update l2p only as buffer entries are being overwritten */
	space = pblk_rb_ring_space(rb, mem, rb->l2p_update, rb->nr_entries);
	अगर (space > nr_entries)
		जाओ out;

	count = nr_entries - space;
	/* l2p_update used exclusively under rb->w_lock */
	ret = __pblk_rb_update_l2p(rb, count);

out:
	वापस ret;
पूर्ण

/*
 * Update the l2p entry क्रम all sectors stored on the ग_लिखो buffer. This means
 * that all future lookups to the l2p table will poपूर्णांक to a device address, not
 * to the cacheline in the ग_लिखो buffer.
 */
व्योम pblk_rb_sync_l2p(काष्ठा pblk_rb *rb)
अणु
	अचिन्हित पूर्णांक sync;
	अचिन्हित पूर्णांक to_update;

	spin_lock(&rb->w_lock);

	/* Protect from पढ़ोs and ग_लिखोs */
	sync = smp_load_acquire(&rb->sync);

	to_update = pblk_rb_ring_count(sync, rb->l2p_update, rb->nr_entries);
	__pblk_rb_update_l2p(rb, to_update);

	spin_unlock(&rb->w_lock);
पूर्ण

/*
 * Write @nr_entries to ring buffer from @data buffer अगर there is enough space.
 * Typically, 4KB data chunks coming from a bio will be copied to the ring
 * buffer, thus the ग_लिखो will fail अगर not all incoming data can be copied.
 *
 */
अटल व्योम __pblk_rb_ग_लिखो_entry(काष्ठा pblk_rb *rb, व्योम *data,
				  काष्ठा pblk_w_ctx w_ctx,
				  काष्ठा pblk_rb_entry *entry)
अणु
	स_नकल(entry->data, data, rb->seg_size);

	entry->w_ctx.lba = w_ctx.lba;
	entry->w_ctx.ppa = w_ctx.ppa;
पूर्ण

व्योम pblk_rb_ग_लिखो_entry_user(काष्ठा pblk_rb *rb, व्योम *data,
			      काष्ठा pblk_w_ctx w_ctx, अचिन्हित पूर्णांक ring_pos)
अणु
	काष्ठा pblk *pblk = container_of(rb, काष्ठा pblk, rwb);
	काष्ठा pblk_rb_entry *entry;
	पूर्णांक flags;

	entry = &rb->entries[ring_pos];
	flags = READ_ONCE(entry->w_ctx.flags);
#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	/* Caller must guarantee that the entry is मुक्त */
	BUG_ON(!(flags & PBLK_WRITABLE_ENTRY));
#पूर्ण_अगर

	__pblk_rb_ग_लिखो_entry(rb, data, w_ctx, entry);

	pblk_update_map_cache(pblk, w_ctx.lba, entry->cacheline);
	flags = w_ctx.flags | PBLK_WRITTEN_DATA;

	/* Release flags on ग_लिखो context. Protect from ग_लिखोs */
	smp_store_release(&entry->w_ctx.flags, flags);
पूर्ण

व्योम pblk_rb_ग_लिखो_entry_gc(काष्ठा pblk_rb *rb, व्योम *data,
			    काष्ठा pblk_w_ctx w_ctx, काष्ठा pblk_line *line,
			    u64 paddr, अचिन्हित पूर्णांक ring_pos)
अणु
	काष्ठा pblk *pblk = container_of(rb, काष्ठा pblk, rwb);
	काष्ठा pblk_rb_entry *entry;
	पूर्णांक flags;

	entry = &rb->entries[ring_pos];
	flags = READ_ONCE(entry->w_ctx.flags);
#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	/* Caller must guarantee that the entry is मुक्त */
	BUG_ON(!(flags & PBLK_WRITABLE_ENTRY));
#पूर्ण_अगर

	__pblk_rb_ग_लिखो_entry(rb, data, w_ctx, entry);

	अगर (!pblk_update_map_gc(pblk, w_ctx.lba, entry->cacheline, line, paddr))
		entry->w_ctx.lba = ADDR_EMPTY;

	flags = w_ctx.flags | PBLK_WRITTEN_DATA;

	/* Release flags on ग_लिखो context. Protect from ग_लिखोs */
	smp_store_release(&entry->w_ctx.flags, flags);
पूर्ण

अटल पूर्णांक pblk_rb_flush_poपूर्णांक_set(काष्ठा pblk_rb *rb, काष्ठा bio *bio,
				   अचिन्हित पूर्णांक pos)
अणु
	काष्ठा pblk_rb_entry *entry;
	अचिन्हित पूर्णांक sync, flush_poपूर्णांक;

	pblk_rb_sync_init(rb, शून्य);
	sync = READ_ONCE(rb->sync);

	अगर (pos == sync) अणु
		pblk_rb_sync_end(rb, शून्य);
		वापस 0;
	पूर्ण

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	atomic_inc(&rb->inflight_flush_poपूर्णांक);
#पूर्ण_अगर

	flush_poपूर्णांक = (pos == 0) ? (rb->nr_entries - 1) : (pos - 1);
	entry = &rb->entries[flush_poपूर्णांक];

	/* Protect flush poपूर्णांकs */
	smp_store_release(&rb->flush_poपूर्णांक, flush_poपूर्णांक);

	अगर (bio)
		bio_list_add(&entry->w_ctx.bios, bio);

	pblk_rb_sync_end(rb, शून्य);

	वापस bio ? 1 : 0;
पूर्ण

अटल पूर्णांक __pblk_rb_may_ग_लिखो(काष्ठा pblk_rb *rb, अचिन्हित पूर्णांक nr_entries,
			       अचिन्हित पूर्णांक *pos)
अणु
	अचिन्हित पूर्णांक mem;
	अचिन्हित पूर्णांक sync;
	अचिन्हित पूर्णांक threshold;

	sync = READ_ONCE(rb->sync);
	mem = READ_ONCE(rb->mem);

	threshold = nr_entries + rb->back_thres;

	अगर (pblk_rb_ring_space(rb, mem, sync, rb->nr_entries) < threshold)
		वापस 0;

	अगर (pblk_rb_update_l2p(rb, nr_entries, mem, sync))
		वापस 0;

	*pos = mem;

	वापस 1;
पूर्ण

अटल पूर्णांक pblk_rb_may_ग_लिखो(काष्ठा pblk_rb *rb, अचिन्हित पूर्णांक nr_entries,
			     अचिन्हित पूर्णांक *pos)
अणु
	अगर (!__pblk_rb_may_ग_लिखो(rb, nr_entries, pos))
		वापस 0;

	/* Protect from पढ़ो count */
	smp_store_release(&rb->mem, pblk_rb_ptr_wrap(rb, *pos, nr_entries));
	वापस 1;
पूर्ण

व्योम pblk_rb_flush(काष्ठा pblk_rb *rb)
अणु
	काष्ठा pblk *pblk = container_of(rb, काष्ठा pblk, rwb);
	अचिन्हित पूर्णांक mem = READ_ONCE(rb->mem);

	अगर (pblk_rb_flush_poपूर्णांक_set(rb, शून्य, mem))
		वापस;

	pblk_ग_लिखो_kick(pblk);
पूर्ण

अटल पूर्णांक pblk_rb_may_ग_लिखो_flush(काष्ठा pblk_rb *rb, अचिन्हित पूर्णांक nr_entries,
				   अचिन्हित पूर्णांक *pos, काष्ठा bio *bio,
				   पूर्णांक *io_ret)
अणु
	अचिन्हित पूर्णांक mem;

	अगर (!__pblk_rb_may_ग_लिखो(rb, nr_entries, pos))
		वापस 0;

	mem = pblk_rb_ptr_wrap(rb, *pos, nr_entries);
	*io_ret = NVM_IO_DONE;

	अगर (bio->bi_opf & REQ_PREFLUSH) अणु
		काष्ठा pblk *pblk = container_of(rb, काष्ठा pblk, rwb);

		atomic64_inc(&pblk->nr_flush);
		अगर (pblk_rb_flush_poपूर्णांक_set(&pblk->rwb, bio, mem))
			*io_ret = NVM_IO_OK;
	पूर्ण

	/* Protect from पढ़ो count */
	smp_store_release(&rb->mem, mem);

	वापस 1;
पूर्ण

/*
 * Atomically check that (i) there is space on the ग_लिखो buffer क्रम the
 * incoming I/O, and (ii) the current I/O type has enough budget in the ग_लिखो
 * buffer (rate-limiter).
 */
पूर्णांक pblk_rb_may_ग_लिखो_user(काष्ठा pblk_rb *rb, काष्ठा bio *bio,
			   अचिन्हित पूर्णांक nr_entries, अचिन्हित पूर्णांक *pos)
अणु
	काष्ठा pblk *pblk = container_of(rb, काष्ठा pblk, rwb);
	पूर्णांक io_ret;

	spin_lock(&rb->w_lock);
	io_ret = pblk_rl_user_may_insert(&pblk->rl, nr_entries);
	अगर (io_ret) अणु
		spin_unlock(&rb->w_lock);
		वापस io_ret;
	पूर्ण

	अगर (!pblk_rb_may_ग_लिखो_flush(rb, nr_entries, pos, bio, &io_ret)) अणु
		spin_unlock(&rb->w_lock);
		वापस NVM_IO_REQUEUE;
	पूर्ण

	pblk_rl_user_in(&pblk->rl, nr_entries);
	spin_unlock(&rb->w_lock);

	वापस io_ret;
पूर्ण

/*
 * Look at pblk_rb_may_ग_लिखो_user comment
 */
पूर्णांक pblk_rb_may_ग_लिखो_gc(काष्ठा pblk_rb *rb, अचिन्हित पूर्णांक nr_entries,
			 अचिन्हित पूर्णांक *pos)
अणु
	काष्ठा pblk *pblk = container_of(rb, काष्ठा pblk, rwb);

	spin_lock(&rb->w_lock);
	अगर (!pblk_rl_gc_may_insert(&pblk->rl, nr_entries)) अणु
		spin_unlock(&rb->w_lock);
		वापस 0;
	पूर्ण

	अगर (!pblk_rb_may_ग_लिखो(rb, nr_entries, pos)) अणु
		spin_unlock(&rb->w_lock);
		वापस 0;
	पूर्ण

	pblk_rl_gc_in(&pblk->rl, nr_entries);
	spin_unlock(&rb->w_lock);

	वापस 1;
पूर्ण

/*
 * Read available entries on rb and add them to the given bio. To aव्योम a memory
 * copy, a page reference to the ग_लिखो buffer is used to be added to the bio.
 *
 * This function is used by the ग_लिखो thपढ़ो to क्रमm the ग_लिखो bio that will
 * persist data on the ग_लिखो buffer to the media.
 */
अचिन्हित पूर्णांक pblk_rb_पढ़ो_to_bio(काष्ठा pblk_rb *rb, काष्ठा nvm_rq *rqd,
				 अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक nr_entries,
				 अचिन्हित पूर्णांक count)
अणु
	काष्ठा pblk *pblk = container_of(rb, काष्ठा pblk, rwb);
	काष्ठा request_queue *q = pblk->dev->q;
	काष्ठा pblk_c_ctx *c_ctx = nvm_rq_to_pdu(rqd);
	काष्ठा bio *bio = rqd->bio;
	काष्ठा pblk_rb_entry *entry;
	काष्ठा page *page;
	अचिन्हित पूर्णांक pad = 0, to_पढ़ो = nr_entries;
	अचिन्हित पूर्णांक i;
	पूर्णांक flags;

	अगर (count < nr_entries) अणु
		pad = nr_entries - count;
		to_पढ़ो = count;
	पूर्ण

	/* Add space क्रम packed metadata अगर in use*/
	pad += (pblk->min_ग_लिखो_pgs - pblk->min_ग_लिखो_pgs_data);

	c_ctx->sentry = pos;
	c_ctx->nr_valid = to_पढ़ो;
	c_ctx->nr_padded = pad;

	क्रम (i = 0; i < to_पढ़ो; i++) अणु
		entry = &rb->entries[pos];

		/* A ग_लिखो has been allowed पूर्णांकo the buffer, but data is still
		 * being copied to it. It is ok to busy रुको.
		 */
try:
		flags = READ_ONCE(entry->w_ctx.flags);
		अगर (!(flags & PBLK_WRITTEN_DATA)) अणु
			io_schedule();
			जाओ try;
		पूर्ण

		page = virt_to_page(entry->data);
		अगर (!page) अणु
			pblk_err(pblk, "could not allocate write bio page\n");
			flags &= ~PBLK_WRITTEN_DATA;
			flags |= PBLK_SUBMITTED_ENTRY;
			/* Release flags on context. Protect from ग_लिखोs */
			smp_store_release(&entry->w_ctx.flags, flags);
			वापस NVM_IO_ERR;
		पूर्ण

		अगर (bio_add_pc_page(q, bio, page, rb->seg_size, 0) !=
								rb->seg_size) अणु
			pblk_err(pblk, "could not add page to write bio\n");
			flags &= ~PBLK_WRITTEN_DATA;
			flags |= PBLK_SUBMITTED_ENTRY;
			/* Release flags on context. Protect from ग_लिखोs */
			smp_store_release(&entry->w_ctx.flags, flags);
			वापस NVM_IO_ERR;
		पूर्ण

		flags &= ~PBLK_WRITTEN_DATA;
		flags |= PBLK_SUBMITTED_ENTRY;

		/* Release flags on context. Protect from ग_लिखोs */
		smp_store_release(&entry->w_ctx.flags, flags);

		pos = pblk_rb_ptr_wrap(rb, pos, 1);
	पूर्ण

	अगर (pad) अणु
		अगर (pblk_bio_add_pages(pblk, bio, GFP_KERNEL, pad)) अणु
			pblk_err(pblk, "could not pad page in write bio\n");
			वापस NVM_IO_ERR;
		पूर्ण

		अगर (pad < pblk->min_ग_लिखो_pgs)
			atomic64_inc(&pblk->pad_dist[pad - 1]);
		अन्यथा
			pblk_warn(pblk, "padding more than min. sectors\n");

		atomic64_add(pad, &pblk->pad_wa);
	पूर्ण

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	atomic_दीर्घ_add(pad, &pblk->padded_ग_लिखोs);
#पूर्ण_अगर

	वापस NVM_IO_OK;
पूर्ण

/*
 * Copy to bio only अगर the lba matches the one on the given cache entry.
 * Otherwise, it means that the entry has been overwritten, and the bio should
 * be directed to disk.
 */
पूर्णांक pblk_rb_copy_to_bio(काष्ठा pblk_rb *rb, काष्ठा bio *bio, sector_t lba,
			काष्ठा ppa_addr ppa)
अणु
	काष्ठा pblk *pblk = container_of(rb, काष्ठा pblk, rwb);
	काष्ठा pblk_rb_entry *entry;
	काष्ठा pblk_w_ctx *w_ctx;
	काष्ठा ppa_addr l2p_ppa;
	u64 pos = pblk_addr_to_cacheline(ppa);
	व्योम *data;
	पूर्णांक flags;
	पूर्णांक ret = 1;


#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	/* Caller must ensure that the access will not cause an overflow */
	BUG_ON(pos >= rb->nr_entries);
#पूर्ण_अगर
	entry = &rb->entries[pos];
	w_ctx = &entry->w_ctx;
	flags = READ_ONCE(w_ctx->flags);

	spin_lock(&rb->w_lock);
	spin_lock(&pblk->trans_lock);
	l2p_ppa = pblk_trans_map_get(pblk, lba);
	spin_unlock(&pblk->trans_lock);

	/* Check अगर the entry has been overwritten or is scheduled to be */
	अगर (!pblk_ppa_comp(l2p_ppa, ppa) || w_ctx->lba != lba ||
						flags & PBLK_WRITABLE_ENTRY) अणु
		ret = 0;
		जाओ out;
	पूर्ण
	data = bio_data(bio);
	स_नकल(data, entry->data, rb->seg_size);

out:
	spin_unlock(&rb->w_lock);
	वापस ret;
पूर्ण

काष्ठा pblk_w_ctx *pblk_rb_w_ctx(काष्ठा pblk_rb *rb, अचिन्हित पूर्णांक pos)
अणु
	अचिन्हित पूर्णांक entry = pblk_rb_ptr_wrap(rb, pos, 0);

	वापस &rb->entries[entry].w_ctx;
पूर्ण

अचिन्हित पूर्णांक pblk_rb_sync_init(काष्ठा pblk_rb *rb, अचिन्हित दीर्घ *flags)
	__acquires(&rb->s_lock)
अणु
	अगर (flags)
		spin_lock_irqsave(&rb->s_lock, *flags);
	अन्यथा
		spin_lock_irq(&rb->s_lock);

	वापस rb->sync;
पूर्ण

व्योम pblk_rb_sync_end(काष्ठा pblk_rb *rb, अचिन्हित दीर्घ *flags)
	__releases(&rb->s_lock)
अणु
	lockdep_निश्चित_held(&rb->s_lock);

	अगर (flags)
		spin_unlock_irqrestore(&rb->s_lock, *flags);
	अन्यथा
		spin_unlock_irq(&rb->s_lock);
पूर्ण

अचिन्हित पूर्णांक pblk_rb_sync_advance(काष्ठा pblk_rb *rb, अचिन्हित पूर्णांक nr_entries)
अणु
	अचिन्हित पूर्णांक sync, flush_poपूर्णांक;
	lockdep_निश्चित_held(&rb->s_lock);

	sync = READ_ONCE(rb->sync);
	flush_poपूर्णांक = READ_ONCE(rb->flush_poपूर्णांक);

	अगर (flush_poपूर्णांक != EMPTY_ENTRY) अणु
		अचिन्हित पूर्णांक secs_to_flush;

		secs_to_flush = pblk_rb_ring_count(flush_poपूर्णांक, sync,
					rb->nr_entries);
		अगर (secs_to_flush < nr_entries) अणु
			/* Protect flush poपूर्णांकs */
			smp_store_release(&rb->flush_poपूर्णांक, EMPTY_ENTRY);
		पूर्ण
	पूर्ण

	sync = pblk_rb_ptr_wrap(rb, sync, nr_entries);

	/* Protect from counts */
	smp_store_release(&rb->sync, sync);

	वापस sync;
पूर्ण

/* Calculate how many sectors to submit up to the current flush poपूर्णांक. */
अचिन्हित पूर्णांक pblk_rb_flush_poपूर्णांक_count(काष्ठा pblk_rb *rb)
अणु
	अचिन्हित पूर्णांक subm, sync, flush_poपूर्णांक;
	अचिन्हित पूर्णांक submitted, to_flush;

	/* Protect flush poपूर्णांकs */
	flush_poपूर्णांक = smp_load_acquire(&rb->flush_poपूर्णांक);
	अगर (flush_poपूर्णांक == EMPTY_ENTRY)
		वापस 0;

	/* Protect syncs */
	sync = smp_load_acquire(&rb->sync);

	subm = READ_ONCE(rb->subm);
	submitted = pblk_rb_ring_count(subm, sync, rb->nr_entries);

	/* The sync poपूर्णांक itself counts as a sector to sync */
	to_flush = pblk_rb_ring_count(flush_poपूर्णांक, sync, rb->nr_entries) + 1;

	वापस (submitted < to_flush) ? (to_flush - submitted) : 0;
पूर्ण

पूर्णांक pblk_rb_tear_करोwn_check(काष्ठा pblk_rb *rb)
अणु
	काष्ठा pblk_rb_entry *entry;
	पूर्णांक i;
	पूर्णांक ret = 0;

	spin_lock(&rb->w_lock);
	spin_lock_irq(&rb->s_lock);

	अगर ((rb->mem == rb->subm) && (rb->subm == rb->sync) &&
				(rb->sync == rb->l2p_update) &&
				(rb->flush_poपूर्णांक == EMPTY_ENTRY)) अणु
		जाओ out;
	पूर्ण

	अगर (!rb->entries) अणु
		ret = 1;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < rb->nr_entries; i++) अणु
		entry = &rb->entries[i];

		अगर (!entry->data) अणु
			ret = 1;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	spin_unlock_irq(&rb->s_lock);
	spin_unlock(&rb->w_lock);

	वापस ret;
पूर्ण

अचिन्हित पूर्णांक pblk_rb_wrap_pos(काष्ठा pblk_rb *rb, अचिन्हित पूर्णांक pos)
अणु
	वापस (pos & (rb->nr_entries - 1));
पूर्ण

पूर्णांक pblk_rb_pos_oob(काष्ठा pblk_rb *rb, u64 pos)
अणु
	वापस (pos >= rb->nr_entries);
पूर्ण

sमाप_प्रकार pblk_rb_sysfs(काष्ठा pblk_rb *rb, अक्षर *buf)
अणु
	काष्ठा pblk *pblk = container_of(rb, काष्ठा pblk, rwb);
	काष्ठा pblk_c_ctx *c;
	sमाप_प्रकार offset;
	पूर्णांक queued_entries = 0;

	spin_lock_irq(&rb->s_lock);
	list_क्रम_each_entry(c, &pblk->compl_list, list)
		queued_entries++;
	spin_unlock_irq(&rb->s_lock);

	अगर (rb->flush_poपूर्णांक != EMPTY_ENTRY)
		offset = scnम_लिखो(buf, PAGE_SIZE,
			"%u\t%u\t%u\t%u\t%u\t%u\t%u - %u/%u/%u - %d\n",
			rb->nr_entries,
			rb->mem,
			rb->subm,
			rb->sync,
			rb->l2p_update,
#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
			atomic_पढ़ो(&rb->inflight_flush_poपूर्णांक),
#अन्यथा
			0,
#पूर्ण_अगर
			rb->flush_poपूर्णांक,
			pblk_rb_पढ़ो_count(rb),
			pblk_rb_space(rb),
			pblk_rb_flush_poपूर्णांक_count(rb),
			queued_entries);
	अन्यथा
		offset = scnम_लिखो(buf, PAGE_SIZE,
			"%u\t%u\t%u\t%u\t%u\t%u\tNULL - %u/%u/%u - %d\n",
			rb->nr_entries,
			rb->mem,
			rb->subm,
			rb->sync,
			rb->l2p_update,
#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
			atomic_पढ़ो(&rb->inflight_flush_poपूर्णांक),
#अन्यथा
			0,
#पूर्ण_अगर
			pblk_rb_पढ़ो_count(rb),
			pblk_rb_space(rb),
			pblk_rb_flush_poपूर्णांक_count(rb),
			queued_entries);

	वापस offset;
पूर्ण
