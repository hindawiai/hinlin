<शैली गुरु>
/*
 * Copyright (C) 2009-2011 Red Hat, Inc.
 *
 * Author: Mikulas Patocka <mpatocka@redhat.com>
 *
 * This file is released under the GPL.
 */

#समावेश <linux/dm-bufपन.स>

#समावेश <linux/device-mapper.h>
#समावेश <linux/dm-पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/shrinker.h>
#समावेश <linux/module.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/stacktrace.h>

#घोषणा DM_MSG_PREFIX "bufio"

/*
 * Memory management policy:
 *	Limit the number of buffers to DM_BUFIO_MEMORY_PERCENT of मुख्य memory
 *	or DM_BUFIO_VMALLOC_PERCENT of vदो_स्मृति memory (whichever is lower).
 *	Always allocate at least DM_BUFIO_MIN_BUFFERS buffers.
 *	Start background ग_लिखोback when there are DM_BUFIO_WRITEBACK_PERCENT
 *	dirty buffers.
 */
#घोषणा DM_BUFIO_MIN_BUFFERS		8

#घोषणा DM_BUFIO_MEMORY_PERCENT		2
#घोषणा DM_BUFIO_VMALLOC_PERCENT	25
#घोषणा DM_BUFIO_WRITEBACK_RATIO	3
#घोषणा DM_BUFIO_LOW_WATERMARK_RATIO	16

/*
 * Check buffer ages in this पूर्णांकerval (seconds)
 */
#घोषणा DM_BUFIO_WORK_TIMER_SECS	30

/*
 * Free buffers when they are older than this (seconds)
 */
#घोषणा DM_BUFIO_DEFAULT_AGE_SECS	300

/*
 * The nr of bytes of cached data to keep around.
 */
#घोषणा DM_BUFIO_DEFAULT_RETAIN_BYTES   (256 * 1024)

/*
 * Align buffer ग_लिखोs to this boundary.
 * Tests show that SSDs have the highest IOPS when using 4k ग_लिखोs.
 */
#घोषणा DM_BUFIO_WRITE_ALIGN		4096

/*
 * dm_buffer->list_mode
 */
#घोषणा LIST_CLEAN	0
#घोषणा LIST_सूचीTY	1
#घोषणा LIST_SIZE	2

/*
 * Linking of buffers:
 *	All buffers are linked to buffer_tree with their node field.
 *
 *	Clean buffers that are not being written (B_WRITING not set)
 *	are linked to lru[LIST_CLEAN] with their lru_list field.
 *
 *	Dirty and clean buffers that are being written are linked to
 *	lru[LIST_सूचीTY] with their lru_list field. When the ग_लिखो
 *	finishes, the buffer cannot be relinked immediately (because we
 *	are in an पूर्णांकerrupt context and relinking requires process
 *	context), so some clean-not-writing buffers can be held on
 *	dirty_lru too.  They are later added to lru in the process
 *	context.
 */
काष्ठा dm_bufio_client अणु
	काष्ठा mutex lock;

	काष्ठा list_head lru[LIST_SIZE];
	अचिन्हित दीर्घ n_buffers[LIST_SIZE];

	काष्ठा block_device *bdev;
	अचिन्हित block_size;
	s8 sectors_per_block_bits;
	व्योम (*alloc_callback)(काष्ठा dm_buffer *);
	व्योम (*ग_लिखो_callback)(काष्ठा dm_buffer *);

	काष्ठा kmem_cache *slab_buffer;
	काष्ठा kmem_cache *slab_cache;
	काष्ठा dm_io_client *dm_io;

	काष्ठा list_head reserved_buffers;
	अचिन्हित need_reserved_buffers;

	अचिन्हित minimum_buffers;

	काष्ठा rb_root buffer_tree;
	रुको_queue_head_t मुक्त_buffer_रुको;

	sector_t start;

	पूर्णांक async_ग_लिखो_error;

	काष्ठा list_head client_list;

	काष्ठा shrinker shrinker;
	काष्ठा work_काष्ठा shrink_work;
	atomic_दीर्घ_t need_shrink;
पूर्ण;

/*
 * Buffer state bits.
 */
#घोषणा B_READING	0
#घोषणा B_WRITING	1
#घोषणा B_सूचीTY		2

/*
 * Describes how the block was allocated:
 * kmem_cache_alloc(), __get_मुक्त_pages() or vदो_स्मृति().
 * See the comment at alloc_buffer_data.
 */
क्रमागत data_mode अणु
	DATA_MODE_SLAB = 0,
	DATA_MODE_GET_FREE_PAGES = 1,
	DATA_MODE_VMALLOC = 2,
	DATA_MODE_LIMIT = 3
पूर्ण;

काष्ठा dm_buffer अणु
	काष्ठा rb_node node;
	काष्ठा list_head lru_list;
	काष्ठा list_head global_list;
	sector_t block;
	व्योम *data;
	अचिन्हित अक्षर data_mode;		/* DATA_MODE_* */
	अचिन्हित अक्षर list_mode;		/* LIST_* */
	blk_status_t पढ़ो_error;
	blk_status_t ग_लिखो_error;
	अचिन्हित accessed;
	अचिन्हित hold_count;
	अचिन्हित दीर्घ state;
	अचिन्हित दीर्घ last_accessed;
	अचिन्हित dirty_start;
	अचिन्हित dirty_end;
	अचिन्हित ग_लिखो_start;
	अचिन्हित ग_लिखो_end;
	काष्ठा dm_bufio_client *c;
	काष्ठा list_head ग_लिखो_list;
	व्योम (*end_io)(काष्ठा dm_buffer *, blk_status_t);
#अगर_घोषित CONFIG_DM_DEBUG_BLOCK_STACK_TRACING
#घोषणा MAX_STACK 10
	अचिन्हित पूर्णांक stack_len;
	अचिन्हित दीर्घ stack_entries[MAX_STACK];
#पूर्ण_अगर
पूर्ण;

/*----------------------------------------------------------------*/

#घोषणा dm_bufio_in_request()	(!!current->bio_list)

अटल व्योम dm_bufio_lock(काष्ठा dm_bufio_client *c)
अणु
	mutex_lock_nested(&c->lock, dm_bufio_in_request());
पूर्ण

अटल पूर्णांक dm_bufio_trylock(काष्ठा dm_bufio_client *c)
अणु
	वापस mutex_trylock(&c->lock);
पूर्ण

अटल व्योम dm_bufio_unlock(काष्ठा dm_bufio_client *c)
अणु
	mutex_unlock(&c->lock);
पूर्ण

/*----------------------------------------------------------------*/

/*
 * Default cache size: available memory भागided by the ratio.
 */
अटल अचिन्हित दीर्घ dm_bufio_शेष_cache_size;

/*
 * Total cache size set by the user.
 */
अटल अचिन्हित दीर्घ dm_bufio_cache_size;

/*
 * A copy of dm_bufio_cache_size because dm_bufio_cache_size can change
 * at any समय.  If it disagrees, the user has changed cache size.
 */
अटल अचिन्हित दीर्घ dm_bufio_cache_size_latch;

अटल DEFINE_SPINLOCK(global_spinlock);

अटल LIST_HEAD(global_queue);

अटल अचिन्हित दीर्घ global_num = 0;

/*
 * Buffers are मुक्तd after this समयout
 */
अटल अचिन्हित dm_bufio_max_age = DM_BUFIO_DEFAULT_AGE_SECS;
अटल अचिन्हित दीर्घ dm_bufio_retain_bytes = DM_BUFIO_DEFAULT_RETAIN_BYTES;

अटल अचिन्हित दीर्घ dm_bufio_peak_allocated;
अटल अचिन्हित दीर्घ dm_bufio_allocated_kmem_cache;
अटल अचिन्हित दीर्घ dm_bufio_allocated_get_मुक्त_pages;
अटल अचिन्हित दीर्घ dm_bufio_allocated_vदो_स्मृति;
अटल अचिन्हित दीर्घ dm_bufio_current_allocated;

/*----------------------------------------------------------------*/

/*
 * The current number of clients.
 */
अटल पूर्णांक dm_bufio_client_count;

/*
 * The list of all clients.
 */
अटल LIST_HEAD(dm_bufio_all_clients);

/*
 * This mutex protects dm_bufio_cache_size_latch and dm_bufio_client_count
 */
अटल DEFINE_MUTEX(dm_bufio_clients_lock);

अटल काष्ठा workqueue_काष्ठा *dm_bufio_wq;
अटल काष्ठा delayed_work dm_bufio_cleanup_old_work;
अटल काष्ठा work_काष्ठा dm_bufio_replacement_work;


#अगर_घोषित CONFIG_DM_DEBUG_BLOCK_STACK_TRACING
अटल व्योम buffer_record_stack(काष्ठा dm_buffer *b)
अणु
	b->stack_len = stack_trace_save(b->stack_entries, MAX_STACK, 2);
पूर्ण
#पूर्ण_अगर

/*----------------------------------------------------------------
 * A red/black tree acts as an index क्रम all the buffers.
 *--------------------------------------------------------------*/
अटल काष्ठा dm_buffer *__find(काष्ठा dm_bufio_client *c, sector_t block)
अणु
	काष्ठा rb_node *n = c->buffer_tree.rb_node;
	काष्ठा dm_buffer *b;

	जबतक (n) अणु
		b = container_of(n, काष्ठा dm_buffer, node);

		अगर (b->block == block)
			वापस b;

		n = block < b->block ? n->rb_left : n->rb_right;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा dm_buffer *__find_next(काष्ठा dm_bufio_client *c, sector_t block)
अणु
	काष्ठा rb_node *n = c->buffer_tree.rb_node;
	काष्ठा dm_buffer *b;
	काष्ठा dm_buffer *best = शून्य;

	जबतक (n) अणु
		b = container_of(n, काष्ठा dm_buffer, node);

		अगर (b->block == block)
			वापस b;

		अगर (block <= b->block) अणु
			n = n->rb_left;
			best = b;
		पूर्ण अन्यथा अणु
			n = n->rb_right;
		पूर्ण
	पूर्ण

	वापस best;
पूर्ण

अटल व्योम __insert(काष्ठा dm_bufio_client *c, काष्ठा dm_buffer *b)
अणु
	काष्ठा rb_node **new = &c->buffer_tree.rb_node, *parent = शून्य;
	काष्ठा dm_buffer *found;

	जबतक (*new) अणु
		found = container_of(*new, काष्ठा dm_buffer, node);

		अगर (found->block == b->block) अणु
			BUG_ON(found != b);
			वापस;
		पूर्ण

		parent = *new;
		new = b->block < found->block ?
			&found->node.rb_left : &found->node.rb_right;
	पूर्ण

	rb_link_node(&b->node, parent, new);
	rb_insert_color(&b->node, &c->buffer_tree);
पूर्ण

अटल व्योम __हटाओ(काष्ठा dm_bufio_client *c, काष्ठा dm_buffer *b)
अणु
	rb_erase(&b->node, &c->buffer_tree);
पूर्ण

/*----------------------------------------------------------------*/

अटल व्योम adjust_total_allocated(काष्ठा dm_buffer *b, bool unlink)
अणु
	अचिन्हित अक्षर data_mode;
	दीर्घ dअगरf;

	अटल अचिन्हित दीर्घ * स्थिर class_ptr[DATA_MODE_LIMIT] = अणु
		&dm_bufio_allocated_kmem_cache,
		&dm_bufio_allocated_get_मुक्त_pages,
		&dm_bufio_allocated_vदो_स्मृति,
	पूर्ण;

	data_mode = b->data_mode;
	dअगरf = (दीर्घ)b->c->block_size;
	अगर (unlink)
		dअगरf = -dअगरf;

	spin_lock(&global_spinlock);

	*class_ptr[data_mode] += dअगरf;

	dm_bufio_current_allocated += dअगरf;

	अगर (dm_bufio_current_allocated > dm_bufio_peak_allocated)
		dm_bufio_peak_allocated = dm_bufio_current_allocated;

	b->accessed = 1;

	अगर (!unlink) अणु
		list_add(&b->global_list, &global_queue);
		global_num++;
		अगर (dm_bufio_current_allocated > dm_bufio_cache_size)
			queue_work(dm_bufio_wq, &dm_bufio_replacement_work);
	पूर्ण अन्यथा अणु
		list_del(&b->global_list);
		global_num--;
	पूर्ण

	spin_unlock(&global_spinlock);
पूर्ण

/*
 * Change the number of clients and recalculate per-client limit.
 */
अटल व्योम __cache_size_refresh(व्योम)
अणु
	BUG_ON(!mutex_is_locked(&dm_bufio_clients_lock));
	BUG_ON(dm_bufio_client_count < 0);

	dm_bufio_cache_size_latch = READ_ONCE(dm_bufio_cache_size);

	/*
	 * Use शेष अगर set to 0 and report the actual cache size used.
	 */
	अगर (!dm_bufio_cache_size_latch) अणु
		(व्योम)cmpxchg(&dm_bufio_cache_size, 0,
			      dm_bufio_शेष_cache_size);
		dm_bufio_cache_size_latch = dm_bufio_शेष_cache_size;
	पूर्ण
पूर्ण

/*
 * Allocating buffer data.
 *
 * Small buffers are allocated with kmem_cache, to use space optimally.
 *
 * For large buffers, we choose between get_मुक्त_pages and vदो_स्मृति.
 * Each has advantages and disadvantages.
 *
 * __get_मुक्त_pages can अक्रमomly fail अगर the memory is fragmented.
 * __vदो_स्मृति won't अक्रमomly fail, but vदो_स्मृति space is limited (it may be
 * as low as 128M) so using it क्रम caching is not appropriate.
 *
 * If the allocation may fail we use __get_मुक्त_pages. Memory fragmentation
 * won't have a fatal effect here, but it just causes flushes of some other
 * buffers and more I/O will be perक्रमmed. Don't use __get_मुक्त_pages अगर it
 * always fails (i.e. order >= MAX_ORDER).
 *
 * If the allocation shouldn't fail we use __vदो_स्मृति. This is only क्रम the
 * initial reserve allocation, so there's no risk of wasting all vदो_स्मृति
 * space.
 */
अटल व्योम *alloc_buffer_data(काष्ठा dm_bufio_client *c, gfp_t gfp_mask,
			       अचिन्हित अक्षर *data_mode)
अणु
	अगर (unlikely(c->slab_cache != शून्य)) अणु
		*data_mode = DATA_MODE_SLAB;
		वापस kmem_cache_alloc(c->slab_cache, gfp_mask);
	पूर्ण

	अगर (c->block_size <= KMALLOC_MAX_SIZE &&
	    gfp_mask & __GFP_NORETRY) अणु
		*data_mode = DATA_MODE_GET_FREE_PAGES;
		वापस (व्योम *)__get_मुक्त_pages(gfp_mask,
						c->sectors_per_block_bits - (PAGE_SHIFT - SECTOR_SHIFT));
	पूर्ण

	*data_mode = DATA_MODE_VMALLOC;

	/*
	 * __vदो_स्मृति allocates the data pages and auxiliary काष्ठाures with
	 * gfp_flags that were specअगरied, but pagetables are always allocated
	 * with GFP_KERNEL, no matter what was specअगरied as gfp_mask.
	 *
	 * Consequently, we must set per-process flag PF_MEMALLOC_NOIO so that
	 * all allocations करोne by this process (including pagetables) are करोne
	 * as अगर GFP_NOIO was specअगरied.
	 */
	अगर (gfp_mask & __GFP_NORETRY) अणु
		अचिन्हित noio_flag = meदो_स्मृति_noio_save();
		व्योम *ptr = __vदो_स्मृति(c->block_size, gfp_mask);

		meदो_स्मृति_noio_restore(noio_flag);
		वापस ptr;
	पूर्ण

	वापस __vदो_स्मृति(c->block_size, gfp_mask);
पूर्ण

/*
 * Free buffer's data.
 */
अटल व्योम मुक्त_buffer_data(काष्ठा dm_bufio_client *c,
			     व्योम *data, अचिन्हित अक्षर data_mode)
अणु
	चयन (data_mode) अणु
	हाल DATA_MODE_SLAB:
		kmem_cache_मुक्त(c->slab_cache, data);
		अवरोध;

	हाल DATA_MODE_GET_FREE_PAGES:
		मुक्त_pages((अचिन्हित दीर्घ)data,
			   c->sectors_per_block_bits - (PAGE_SHIFT - SECTOR_SHIFT));
		अवरोध;

	हाल DATA_MODE_VMALLOC:
		vमुक्त(data);
		अवरोध;

	शेष:
		DMCRIT("dm_bufio_free_buffer_data: bad data mode: %d",
		       data_mode);
		BUG();
	पूर्ण
पूर्ण

/*
 * Allocate buffer and its data.
 */
अटल काष्ठा dm_buffer *alloc_buffer(काष्ठा dm_bufio_client *c, gfp_t gfp_mask)
अणु
	काष्ठा dm_buffer *b = kmem_cache_alloc(c->slab_buffer, gfp_mask);

	अगर (!b)
		वापस शून्य;

	b->c = c;

	b->data = alloc_buffer_data(c, gfp_mask, &b->data_mode);
	अगर (!b->data) अणु
		kmem_cache_मुक्त(c->slab_buffer, b);
		वापस शून्य;
	पूर्ण

#अगर_घोषित CONFIG_DM_DEBUG_BLOCK_STACK_TRACING
	b->stack_len = 0;
#पूर्ण_अगर
	वापस b;
पूर्ण

/*
 * Free buffer and its data.
 */
अटल व्योम मुक्त_buffer(काष्ठा dm_buffer *b)
अणु
	काष्ठा dm_bufio_client *c = b->c;

	मुक्त_buffer_data(c, b->data, b->data_mode);
	kmem_cache_मुक्त(c->slab_buffer, b);
पूर्ण

/*
 * Link buffer to the buffer tree and clean or dirty queue.
 */
अटल व्योम __link_buffer(काष्ठा dm_buffer *b, sector_t block, पूर्णांक dirty)
अणु
	काष्ठा dm_bufio_client *c = b->c;

	c->n_buffers[dirty]++;
	b->block = block;
	b->list_mode = dirty;
	list_add(&b->lru_list, &c->lru[dirty]);
	__insert(b->c, b);
	b->last_accessed = jअगरfies;

	adjust_total_allocated(b, false);
पूर्ण

/*
 * Unlink buffer from the buffer tree and dirty or clean queue.
 */
अटल व्योम __unlink_buffer(काष्ठा dm_buffer *b)
अणु
	काष्ठा dm_bufio_client *c = b->c;

	BUG_ON(!c->n_buffers[b->list_mode]);

	c->n_buffers[b->list_mode]--;
	__हटाओ(b->c, b);
	list_del(&b->lru_list);

	adjust_total_allocated(b, true);
पूर्ण

/*
 * Place the buffer to the head of dirty or clean LRU queue.
 */
अटल व्योम __relink_lru(काष्ठा dm_buffer *b, पूर्णांक dirty)
अणु
	काष्ठा dm_bufio_client *c = b->c;

	b->accessed = 1;

	BUG_ON(!c->n_buffers[b->list_mode]);

	c->n_buffers[b->list_mode]--;
	c->n_buffers[dirty]++;
	b->list_mode = dirty;
	list_move(&b->lru_list, &c->lru[dirty]);
	b->last_accessed = jअगरfies;
पूर्ण

/*----------------------------------------------------------------
 * Submit I/O on the buffer.
 *
 * Bio पूर्णांकerface is faster but it has some problems:
 *	the vector list is limited (increasing this limit increases
 *	memory-consumption per buffer, so it is not viable);
 *
 *	the memory must be direct-mapped, not vदो_स्मृतिed;
 *
 * If the buffer is small enough (up to DM_BUFIO_INLINE_VECS pages) and
 * it is not vदो_स्मृतिed, try using the bio पूर्णांकerface.
 *
 * If the buffer is big, अगर it is vदो_स्मृतिed or अगर the underlying device
 * rejects the bio because it is too large, use dm-io layer to करो the I/O.
 * The dm-io layer splits the I/O पूर्णांकo multiple requests, aव्योमing the above
 * लघुcomings.
 *--------------------------------------------------------------*/

/*
 * dm-io completion routine. It just calls b->bio.bi_end_io, pretending
 * that the request was handled directly with bio पूर्णांकerface.
 */
अटल व्योम dmio_complete(अचिन्हित दीर्घ error, व्योम *context)
अणु
	काष्ठा dm_buffer *b = context;

	b->end_io(b, unlikely(error != 0) ? BLK_STS_IOERR : 0);
पूर्ण

अटल व्योम use_dmio(काष्ठा dm_buffer *b, पूर्णांक rw, sector_t sector,
		     अचिन्हित n_sectors, अचिन्हित offset)
अणु
	पूर्णांक r;
	काष्ठा dm_io_request io_req = अणु
		.bi_op = rw,
		.bi_op_flags = 0,
		.notअगरy.fn = dmio_complete,
		.notअगरy.context = b,
		.client = b->c->dm_io,
	पूर्ण;
	काष्ठा dm_io_region region = अणु
		.bdev = b->c->bdev,
		.sector = sector,
		.count = n_sectors,
	पूर्ण;

	अगर (b->data_mode != DATA_MODE_VMALLOC) अणु
		io_req.mem.type = DM_IO_KMEM;
		io_req.mem.ptr.addr = (अक्षर *)b->data + offset;
	पूर्ण अन्यथा अणु
		io_req.mem.type = DM_IO_VMA;
		io_req.mem.ptr.vma = (अक्षर *)b->data + offset;
	पूर्ण

	r = dm_io(&io_req, 1, &region, शून्य);
	अगर (unlikely(r))
		b->end_io(b, त्रुटि_सं_to_blk_status(r));
पूर्ण

अटल व्योम bio_complete(काष्ठा bio *bio)
अणु
	काष्ठा dm_buffer *b = bio->bi_निजी;
	blk_status_t status = bio->bi_status;
	bio_put(bio);
	b->end_io(b, status);
पूर्ण

अटल व्योम use_bio(काष्ठा dm_buffer *b, पूर्णांक rw, sector_t sector,
		    अचिन्हित n_sectors, अचिन्हित offset)
अणु
	काष्ठा bio *bio;
	अक्षर *ptr;
	अचिन्हित vec_size, len;

	vec_size = b->c->block_size >> PAGE_SHIFT;
	अगर (unlikely(b->c->sectors_per_block_bits < PAGE_SHIFT - SECTOR_SHIFT))
		vec_size += 2;

	bio = bio_kदो_स्मृति(GFP_NOWAIT | __GFP_NORETRY | __GFP_NOWARN, vec_size);
	अगर (!bio) अणु
dmio:
		use_dmio(b, rw, sector, n_sectors, offset);
		वापस;
	पूर्ण

	bio->bi_iter.bi_sector = sector;
	bio_set_dev(bio, b->c->bdev);
	bio_set_op_attrs(bio, rw, 0);
	bio->bi_end_io = bio_complete;
	bio->bi_निजी = b;

	ptr = (अक्षर *)b->data + offset;
	len = n_sectors << SECTOR_SHIFT;

	करो अणु
		अचिन्हित this_step = min((अचिन्हित)(PAGE_SIZE - offset_in_page(ptr)), len);
		अगर (!bio_add_page(bio, virt_to_page(ptr), this_step,
				  offset_in_page(ptr))) अणु
			bio_put(bio);
			जाओ dmio;
		पूर्ण

		len -= this_step;
		ptr += this_step;
	पूर्ण जबतक (len > 0);

	submit_bio(bio);
पूर्ण

अटल अंतरभूत sector_t block_to_sector(काष्ठा dm_bufio_client *c, sector_t block)
अणु
	sector_t sector;

	अगर (likely(c->sectors_per_block_bits >= 0))
		sector = block << c->sectors_per_block_bits;
	अन्यथा
		sector = block * (c->block_size >> SECTOR_SHIFT);
	sector += c->start;

	वापस sector;
पूर्ण

अटल व्योम submit_io(काष्ठा dm_buffer *b, पूर्णांक rw, व्योम (*end_io)(काष्ठा dm_buffer *, blk_status_t))
अणु
	अचिन्हित n_sectors;
	sector_t sector;
	अचिन्हित offset, end;

	b->end_io = end_io;

	sector = block_to_sector(b->c, b->block);

	अगर (rw != REQ_OP_WRITE) अणु
		n_sectors = b->c->block_size >> SECTOR_SHIFT;
		offset = 0;
	पूर्ण अन्यथा अणु
		अगर (b->c->ग_लिखो_callback)
			b->c->ग_लिखो_callback(b);
		offset = b->ग_लिखो_start;
		end = b->ग_लिखो_end;
		offset &= -DM_BUFIO_WRITE_ALIGN;
		end += DM_BUFIO_WRITE_ALIGN - 1;
		end &= -DM_BUFIO_WRITE_ALIGN;
		अगर (unlikely(end > b->c->block_size))
			end = b->c->block_size;

		sector += offset >> SECTOR_SHIFT;
		n_sectors = (end - offset) >> SECTOR_SHIFT;
	पूर्ण

	अगर (b->data_mode != DATA_MODE_VMALLOC)
		use_bio(b, rw, sector, n_sectors, offset);
	अन्यथा
		use_dmio(b, rw, sector, n_sectors, offset);
पूर्ण

/*----------------------------------------------------------------
 * Writing dirty buffers
 *--------------------------------------------------------------*/

/*
 * The endio routine क्रम ग_लिखो.
 *
 * Set the error, clear B_WRITING bit and wake anyone who was रुकोing on
 * it.
 */
अटल व्योम ग_लिखो_endio(काष्ठा dm_buffer *b, blk_status_t status)
अणु
	b->ग_लिखो_error = status;
	अगर (unlikely(status)) अणु
		काष्ठा dm_bufio_client *c = b->c;

		(व्योम)cmpxchg(&c->async_ग_लिखो_error, 0,
				blk_status_to_त्रुटि_सं(status));
	पूर्ण

	BUG_ON(!test_bit(B_WRITING, &b->state));

	smp_mb__beक्रमe_atomic();
	clear_bit(B_WRITING, &b->state);
	smp_mb__after_atomic();

	wake_up_bit(&b->state, B_WRITING);
पूर्ण

/*
 * Initiate a ग_लिखो on a dirty buffer, but करोn't रुको क्रम it.
 *
 * - If the buffer is not dirty, निकास.
 * - If there some previous ग_लिखो going on, रुको क्रम it to finish (we can't
 *   have two ग_लिखोs on the same buffer simultaneously).
 * - Submit our ग_लिखो and करोn't रुको on it. We set B_WRITING indicating
 *   that there is a ग_लिखो in progress.
 */
अटल व्योम __ग_लिखो_dirty_buffer(काष्ठा dm_buffer *b,
				 काष्ठा list_head *ग_लिखो_list)
अणु
	अगर (!test_bit(B_सूचीTY, &b->state))
		वापस;

	clear_bit(B_सूचीTY, &b->state);
	रुको_on_bit_lock_io(&b->state, B_WRITING, TASK_UNINTERRUPTIBLE);

	b->ग_लिखो_start = b->dirty_start;
	b->ग_लिखो_end = b->dirty_end;

	अगर (!ग_लिखो_list)
		submit_io(b, REQ_OP_WRITE, ग_लिखो_endio);
	अन्यथा
		list_add_tail(&b->ग_लिखो_list, ग_लिखो_list);
पूर्ण

अटल व्योम __flush_ग_लिखो_list(काष्ठा list_head *ग_लिखो_list)
अणु
	काष्ठा blk_plug plug;
	blk_start_plug(&plug);
	जबतक (!list_empty(ग_लिखो_list)) अणु
		काष्ठा dm_buffer *b =
			list_entry(ग_लिखो_list->next, काष्ठा dm_buffer, ग_लिखो_list);
		list_del(&b->ग_लिखो_list);
		submit_io(b, REQ_OP_WRITE, ग_लिखो_endio);
		cond_resched();
	पूर्ण
	blk_finish_plug(&plug);
पूर्ण

/*
 * Wait until any activity on the buffer finishes.  Possibly ग_लिखो the
 * buffer अगर it is dirty.  When this function finishes, there is no I/O
 * running on the buffer and the buffer is not dirty.
 */
अटल व्योम __make_buffer_clean(काष्ठा dm_buffer *b)
अणु
	BUG_ON(b->hold_count);

	अगर (!b->state)	/* fast हाल */
		वापस;

	रुको_on_bit_io(&b->state, B_READING, TASK_UNINTERRUPTIBLE);
	__ग_लिखो_dirty_buffer(b, शून्य);
	रुको_on_bit_io(&b->state, B_WRITING, TASK_UNINTERRUPTIBLE);
पूर्ण

/*
 * Find some buffer that is not held by anybody, clean it, unlink it and
 * वापस it.
 */
अटल काष्ठा dm_buffer *__get_unclaimed_buffer(काष्ठा dm_bufio_client *c)
अणु
	काष्ठा dm_buffer *b;

	list_क्रम_each_entry_reverse(b, &c->lru[LIST_CLEAN], lru_list) अणु
		BUG_ON(test_bit(B_WRITING, &b->state));
		BUG_ON(test_bit(B_सूचीTY, &b->state));

		अगर (!b->hold_count) अणु
			__make_buffer_clean(b);
			__unlink_buffer(b);
			वापस b;
		पूर्ण
		cond_resched();
	पूर्ण

	list_क्रम_each_entry_reverse(b, &c->lru[LIST_सूचीTY], lru_list) अणु
		BUG_ON(test_bit(B_READING, &b->state));

		अगर (!b->hold_count) अणु
			__make_buffer_clean(b);
			__unlink_buffer(b);
			वापस b;
		पूर्ण
		cond_resched();
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Wait until some other thपढ़ोs मुक्त some buffer or release hold count on
 * some buffer.
 *
 * This function is entered with c->lock held, drops it and regains it
 * beक्रमe निकासing.
 */
अटल व्योम __रुको_क्रम_मुक्त_buffer(काष्ठा dm_bufio_client *c)
अणु
	DECLARE_WAITQUEUE(रुको, current);

	add_रुको_queue(&c->मुक्त_buffer_रुको, &रुको);
	set_current_state(TASK_UNINTERRUPTIBLE);
	dm_bufio_unlock(c);

	io_schedule();

	हटाओ_रुको_queue(&c->मुक्त_buffer_रुको, &रुको);

	dm_bufio_lock(c);
पूर्ण

क्रमागत new_flag अणु
	NF_FRESH = 0,
	NF_READ = 1,
	NF_GET = 2,
	NF_PREFETCH = 3
पूर्ण;

/*
 * Allocate a new buffer. If the allocation is not possible, रुको until
 * some other thपढ़ो मुक्तs a buffer.
 *
 * May drop the lock and regain it.
 */
अटल काष्ठा dm_buffer *__alloc_buffer_रुको_no_callback(काष्ठा dm_bufio_client *c, क्रमागत new_flag nf)
अणु
	काष्ठा dm_buffer *b;
	bool tried_noio_alloc = false;

	/*
	 * dm-bufio is resistant to allocation failures (it just keeps
	 * one buffer reserved in हालs all the allocations fail).
	 * So set flags to not try too hard:
	 *	GFP_NOWAIT: करोn't wait; if we need to sleep we'll release our
	 *		    mutex and रुको ourselves.
	 *	__GFP_NORETRY: करोn't retry and rather वापस failure
	 *	__GFP_NOMEMALLOC: करोn't use emergency reserves
	 *	__GFP_NOWARN: करोn't prपूर्णांक a warning in हाल of failure
	 *
	 * For debugging, अगर we set the cache size to 1, no new buffers will
	 * be allocated.
	 */
	जबतक (1) अणु
		अगर (dm_bufio_cache_size_latch != 1) अणु
			b = alloc_buffer(c, GFP_NOWAIT | __GFP_NORETRY | __GFP_NOMEMALLOC | __GFP_NOWARN);
			अगर (b)
				वापस b;
		पूर्ण

		अगर (nf == NF_PREFETCH)
			वापस शून्य;

		अगर (dm_bufio_cache_size_latch != 1 && !tried_noio_alloc) अणु
			dm_bufio_unlock(c);
			b = alloc_buffer(c, GFP_NOIO | __GFP_NORETRY | __GFP_NOMEMALLOC | __GFP_NOWARN);
			dm_bufio_lock(c);
			अगर (b)
				वापस b;
			tried_noio_alloc = true;
		पूर्ण

		अगर (!list_empty(&c->reserved_buffers)) अणु
			b = list_entry(c->reserved_buffers.next,
				       काष्ठा dm_buffer, lru_list);
			list_del(&b->lru_list);
			c->need_reserved_buffers++;

			वापस b;
		पूर्ण

		b = __get_unclaimed_buffer(c);
		अगर (b)
			वापस b;

		__रुको_क्रम_मुक्त_buffer(c);
	पूर्ण
पूर्ण

अटल काष्ठा dm_buffer *__alloc_buffer_रुको(काष्ठा dm_bufio_client *c, क्रमागत new_flag nf)
अणु
	काष्ठा dm_buffer *b = __alloc_buffer_रुको_no_callback(c, nf);

	अगर (!b)
		वापस शून्य;

	अगर (c->alloc_callback)
		c->alloc_callback(b);

	वापस b;
पूर्ण

/*
 * Free a buffer and wake other thपढ़ोs रुकोing क्रम मुक्त buffers.
 */
अटल व्योम __मुक्त_buffer_wake(काष्ठा dm_buffer *b)
अणु
	काष्ठा dm_bufio_client *c = b->c;

	अगर (!c->need_reserved_buffers)
		मुक्त_buffer(b);
	अन्यथा अणु
		list_add(&b->lru_list, &c->reserved_buffers);
		c->need_reserved_buffers--;
	पूर्ण

	wake_up(&c->मुक्त_buffer_रुको);
पूर्ण

अटल व्योम __ग_लिखो_dirty_buffers_async(काष्ठा dm_bufio_client *c, पूर्णांक no_रुको,
					काष्ठा list_head *ग_लिखो_list)
अणु
	काष्ठा dm_buffer *b, *पंचांगp;

	list_क्रम_each_entry_safe_reverse(b, पंचांगp, &c->lru[LIST_सूचीTY], lru_list) अणु
		BUG_ON(test_bit(B_READING, &b->state));

		अगर (!test_bit(B_सूचीTY, &b->state) &&
		    !test_bit(B_WRITING, &b->state)) अणु
			__relink_lru(b, LIST_CLEAN);
			जारी;
		पूर्ण

		अगर (no_रुको && test_bit(B_WRITING, &b->state))
			वापस;

		__ग_लिखो_dirty_buffer(b, ग_लिखो_list);
		cond_resched();
	पूर्ण
पूर्ण

/*
 * Check अगर we're over watermark.
 * If we are over threshold_buffers, start मुक्तing buffers.
 * If we're over "limit_buffers", block until we get under the limit.
 */
अटल व्योम __check_watermark(काष्ठा dm_bufio_client *c,
			      काष्ठा list_head *ग_लिखो_list)
अणु
	अगर (c->n_buffers[LIST_सूचीTY] > c->n_buffers[LIST_CLEAN] * DM_BUFIO_WRITEBACK_RATIO)
		__ग_लिखो_dirty_buffers_async(c, 1, ग_लिखो_list);
पूर्ण

/*----------------------------------------------------------------
 * Getting a buffer
 *--------------------------------------------------------------*/

अटल काष्ठा dm_buffer *__bufio_new(काष्ठा dm_bufio_client *c, sector_t block,
				     क्रमागत new_flag nf, पूर्णांक *need_submit,
				     काष्ठा list_head *ग_लिखो_list)
अणु
	काष्ठा dm_buffer *b, *new_b = शून्य;

	*need_submit = 0;

	b = __find(c, block);
	अगर (b)
		जाओ found_buffer;

	अगर (nf == NF_GET)
		वापस शून्य;

	new_b = __alloc_buffer_रुको(c, nf);
	अगर (!new_b)
		वापस शून्य;

	/*
	 * We've had a period where the mutex was unlocked, so need to
	 * recheck the buffer tree.
	 */
	b = __find(c, block);
	अगर (b) अणु
		__मुक्त_buffer_wake(new_b);
		जाओ found_buffer;
	पूर्ण

	__check_watermark(c, ग_लिखो_list);

	b = new_b;
	b->hold_count = 1;
	b->पढ़ो_error = 0;
	b->ग_लिखो_error = 0;
	__link_buffer(b, block, LIST_CLEAN);

	अगर (nf == NF_FRESH) अणु
		b->state = 0;
		वापस b;
	पूर्ण

	b->state = 1 << B_READING;
	*need_submit = 1;

	वापस b;

found_buffer:
	अगर (nf == NF_PREFETCH)
		वापस शून्य;
	/*
	 * Note: it is essential that we करोn't रुको क्रम the buffer to be
	 * पढ़ो अगर dm_bufio_get function is used. Both dm_bufio_get and
	 * dm_bufio_prefetch can be used in the driver request routine.
	 * If the user called both dm_bufio_prefetch and dm_bufio_get on
	 * the same buffer, it would deadlock अगर we रुकोed.
	 */
	अगर (nf == NF_GET && unlikely(test_bit(B_READING, &b->state)))
		वापस शून्य;

	b->hold_count++;
	__relink_lru(b, test_bit(B_सूचीTY, &b->state) ||
		     test_bit(B_WRITING, &b->state));
	वापस b;
पूर्ण

/*
 * The endio routine क्रम पढ़ोing: set the error, clear the bit and wake up
 * anyone रुकोing on the buffer.
 */
अटल व्योम पढ़ो_endio(काष्ठा dm_buffer *b, blk_status_t status)
अणु
	b->पढ़ो_error = status;

	BUG_ON(!test_bit(B_READING, &b->state));

	smp_mb__beक्रमe_atomic();
	clear_bit(B_READING, &b->state);
	smp_mb__after_atomic();

	wake_up_bit(&b->state, B_READING);
पूर्ण

/*
 * A common routine क्रम dm_bufio_new and dm_bufio_पढ़ो.  Operation of these
 * functions is similar except that dm_bufio_new करोesn't पढ़ो the
 * buffer from the disk (assuming that the caller overग_लिखोs all the data
 * and uses dm_bufio_mark_buffer_dirty to ग_लिखो new data back).
 */
अटल व्योम *new_पढ़ो(काष्ठा dm_bufio_client *c, sector_t block,
		      क्रमागत new_flag nf, काष्ठा dm_buffer **bp)
अणु
	पूर्णांक need_submit;
	काष्ठा dm_buffer *b;

	LIST_HEAD(ग_लिखो_list);

	dm_bufio_lock(c);
	b = __bufio_new(c, block, nf, &need_submit, &ग_लिखो_list);
#अगर_घोषित CONFIG_DM_DEBUG_BLOCK_STACK_TRACING
	अगर (b && b->hold_count == 1)
		buffer_record_stack(b);
#पूर्ण_अगर
	dm_bufio_unlock(c);

	__flush_ग_लिखो_list(&ग_लिखो_list);

	अगर (!b)
		वापस शून्य;

	अगर (need_submit)
		submit_io(b, REQ_OP_READ, पढ़ो_endio);

	रुको_on_bit_io(&b->state, B_READING, TASK_UNINTERRUPTIBLE);

	अगर (b->पढ़ो_error) अणु
		पूर्णांक error = blk_status_to_त्रुटि_सं(b->पढ़ो_error);

		dm_bufio_release(b);

		वापस ERR_PTR(error);
	पूर्ण

	*bp = b;

	वापस b->data;
पूर्ण

व्योम *dm_bufio_get(काष्ठा dm_bufio_client *c, sector_t block,
		   काष्ठा dm_buffer **bp)
अणु
	वापस new_पढ़ो(c, block, NF_GET, bp);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_get);

व्योम *dm_bufio_पढ़ो(काष्ठा dm_bufio_client *c, sector_t block,
		    काष्ठा dm_buffer **bp)
अणु
	BUG_ON(dm_bufio_in_request());

	वापस new_पढ़ो(c, block, NF_READ, bp);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_पढ़ो);

व्योम *dm_bufio_new(काष्ठा dm_bufio_client *c, sector_t block,
		   काष्ठा dm_buffer **bp)
अणु
	BUG_ON(dm_bufio_in_request());

	वापस new_पढ़ो(c, block, NF_FRESH, bp);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_new);

व्योम dm_bufio_prefetch(काष्ठा dm_bufio_client *c,
		       sector_t block, अचिन्हित n_blocks)
अणु
	काष्ठा blk_plug plug;

	LIST_HEAD(ग_लिखो_list);

	BUG_ON(dm_bufio_in_request());

	blk_start_plug(&plug);
	dm_bufio_lock(c);

	क्रम (; n_blocks--; block++) अणु
		पूर्णांक need_submit;
		काष्ठा dm_buffer *b;
		b = __bufio_new(c, block, NF_PREFETCH, &need_submit,
				&ग_लिखो_list);
		अगर (unlikely(!list_empty(&ग_लिखो_list))) अणु
			dm_bufio_unlock(c);
			blk_finish_plug(&plug);
			__flush_ग_लिखो_list(&ग_लिखो_list);
			blk_start_plug(&plug);
			dm_bufio_lock(c);
		पूर्ण
		अगर (unlikely(b != शून्य)) अणु
			dm_bufio_unlock(c);

			अगर (need_submit)
				submit_io(b, REQ_OP_READ, पढ़ो_endio);
			dm_bufio_release(b);

			cond_resched();

			अगर (!n_blocks)
				जाओ flush_plug;
			dm_bufio_lock(c);
		पूर्ण
	पूर्ण

	dm_bufio_unlock(c);

flush_plug:
	blk_finish_plug(&plug);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_prefetch);

व्योम dm_bufio_release(काष्ठा dm_buffer *b)
अणु
	काष्ठा dm_bufio_client *c = b->c;

	dm_bufio_lock(c);

	BUG_ON(!b->hold_count);

	b->hold_count--;
	अगर (!b->hold_count) अणु
		wake_up(&c->मुक्त_buffer_रुको);

		/*
		 * If there were errors on the buffer, and the buffer is not
		 * to be written, मुक्त the buffer. There is no poपूर्णांक in caching
		 * invalid buffer.
		 */
		अगर ((b->पढ़ो_error || b->ग_लिखो_error) &&
		    !test_bit(B_READING, &b->state) &&
		    !test_bit(B_WRITING, &b->state) &&
		    !test_bit(B_सूचीTY, &b->state)) अणु
			__unlink_buffer(b);
			__मुक्त_buffer_wake(b);
		पूर्ण
	पूर्ण

	dm_bufio_unlock(c);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_release);

व्योम dm_bufio_mark_partial_buffer_dirty(काष्ठा dm_buffer *b,
					अचिन्हित start, अचिन्हित end)
अणु
	काष्ठा dm_bufio_client *c = b->c;

	BUG_ON(start >= end);
	BUG_ON(end > b->c->block_size);

	dm_bufio_lock(c);

	BUG_ON(test_bit(B_READING, &b->state));

	अगर (!test_and_set_bit(B_सूचीTY, &b->state)) अणु
		b->dirty_start = start;
		b->dirty_end = end;
		__relink_lru(b, LIST_सूचीTY);
	पूर्ण अन्यथा अणु
		अगर (start < b->dirty_start)
			b->dirty_start = start;
		अगर (end > b->dirty_end)
			b->dirty_end = end;
	पूर्ण

	dm_bufio_unlock(c);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_mark_partial_buffer_dirty);

व्योम dm_bufio_mark_buffer_dirty(काष्ठा dm_buffer *b)
अणु
	dm_bufio_mark_partial_buffer_dirty(b, 0, b->c->block_size);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_mark_buffer_dirty);

व्योम dm_bufio_ग_लिखो_dirty_buffers_async(काष्ठा dm_bufio_client *c)
अणु
	LIST_HEAD(ग_लिखो_list);

	BUG_ON(dm_bufio_in_request());

	dm_bufio_lock(c);
	__ग_लिखो_dirty_buffers_async(c, 0, &ग_लिखो_list);
	dm_bufio_unlock(c);
	__flush_ग_लिखो_list(&ग_लिखो_list);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_ग_लिखो_dirty_buffers_async);

/*
 * For perक्रमmance, it is essential that the buffers are written asynchronously
 * and simultaneously (so that the block layer can merge the ग_लिखोs) and then
 * रुकोed upon.
 *
 * Finally, we flush hardware disk cache.
 */
पूर्णांक dm_bufio_ग_लिखो_dirty_buffers(काष्ठा dm_bufio_client *c)
अणु
	पूर्णांक a, f;
	अचिन्हित दीर्घ buffers_processed = 0;
	काष्ठा dm_buffer *b, *पंचांगp;

	LIST_HEAD(ग_लिखो_list);

	dm_bufio_lock(c);
	__ग_लिखो_dirty_buffers_async(c, 0, &ग_लिखो_list);
	dm_bufio_unlock(c);
	__flush_ग_लिखो_list(&ग_लिखो_list);
	dm_bufio_lock(c);

again:
	list_क्रम_each_entry_safe_reverse(b, पंचांगp, &c->lru[LIST_सूचीTY], lru_list) अणु
		पूर्णांक dropped_lock = 0;

		अगर (buffers_processed < c->n_buffers[LIST_सूचीTY])
			buffers_processed++;

		BUG_ON(test_bit(B_READING, &b->state));

		अगर (test_bit(B_WRITING, &b->state)) अणु
			अगर (buffers_processed < c->n_buffers[LIST_सूचीTY]) अणु
				dropped_lock = 1;
				b->hold_count++;
				dm_bufio_unlock(c);
				रुको_on_bit_io(&b->state, B_WRITING,
					       TASK_UNINTERRUPTIBLE);
				dm_bufio_lock(c);
				b->hold_count--;
			पूर्ण अन्यथा
				रुको_on_bit_io(&b->state, B_WRITING,
					       TASK_UNINTERRUPTIBLE);
		पूर्ण

		अगर (!test_bit(B_सूचीTY, &b->state) &&
		    !test_bit(B_WRITING, &b->state))
			__relink_lru(b, LIST_CLEAN);

		cond_resched();

		/*
		 * If we dropped the lock, the list is no दीर्घer consistent,
		 * so we must restart the search.
		 *
		 * In the most common हाल, the buffer just processed is
		 * relinked to the clean list, so we won't loop scanning the
		 * same buffer again and again.
		 *
		 * This may livelock अगर there is another thपढ़ो simultaneously
		 * dirtying buffers, so we count the number of buffers walked
		 * and अगर it exceeds the total number of buffers, it means that
		 * someone is करोing some ग_लिखोs simultaneously with us.  In
		 * this हाल, stop, dropping the lock.
		 */
		अगर (dropped_lock)
			जाओ again;
	पूर्ण
	wake_up(&c->मुक्त_buffer_रुको);
	dm_bufio_unlock(c);

	a = xchg(&c->async_ग_लिखो_error, 0);
	f = dm_bufio_issue_flush(c);
	अगर (a)
		वापस a;

	वापस f;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_ग_लिखो_dirty_buffers);

/*
 * Use dm-io to send an empty barrier to flush the device.
 */
पूर्णांक dm_bufio_issue_flush(काष्ठा dm_bufio_client *c)
अणु
	काष्ठा dm_io_request io_req = अणु
		.bi_op = REQ_OP_WRITE,
		.bi_op_flags = REQ_PREFLUSH | REQ_SYNC,
		.mem.type = DM_IO_KMEM,
		.mem.ptr.addr = शून्य,
		.client = c->dm_io,
	पूर्ण;
	काष्ठा dm_io_region io_reg = अणु
		.bdev = c->bdev,
		.sector = 0,
		.count = 0,
	पूर्ण;

	BUG_ON(dm_bufio_in_request());

	वापस dm_io(&io_req, 1, &io_reg, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_issue_flush);

/*
 * Use dm-io to send a discard request to flush the device.
 */
पूर्णांक dm_bufio_issue_discard(काष्ठा dm_bufio_client *c, sector_t block, sector_t count)
अणु
	काष्ठा dm_io_request io_req = अणु
		.bi_op = REQ_OP_DISCARD,
		.bi_op_flags = REQ_SYNC,
		.mem.type = DM_IO_KMEM,
		.mem.ptr.addr = शून्य,
		.client = c->dm_io,
	पूर्ण;
	काष्ठा dm_io_region io_reg = अणु
		.bdev = c->bdev,
		.sector = block_to_sector(c, block),
		.count = block_to_sector(c, count),
	पूर्ण;

	BUG_ON(dm_bufio_in_request());

	वापस dm_io(&io_req, 1, &io_reg, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_issue_discard);

/*
 * We first delete any other buffer that may be at that new location.
 *
 * Then, we ग_लिखो the buffer to the original location अगर it was dirty.
 *
 * Then, अगर we are the only one who is holding the buffer, relink the buffer
 * in the buffer tree क्रम the new location.
 *
 * If there was someone अन्यथा holding the buffer, we ग_लिखो it to the new
 * location but not relink it, because that other user needs to have the buffer
 * at the same place.
 */
व्योम dm_bufio_release_move(काष्ठा dm_buffer *b, sector_t new_block)
अणु
	काष्ठा dm_bufio_client *c = b->c;
	काष्ठा dm_buffer *new;

	BUG_ON(dm_bufio_in_request());

	dm_bufio_lock(c);

retry:
	new = __find(c, new_block);
	अगर (new) अणु
		अगर (new->hold_count) अणु
			__रुको_क्रम_मुक्त_buffer(c);
			जाओ retry;
		पूर्ण

		/*
		 * FIXME: Is there any poपूर्णांक रुकोing क्रम a ग_लिखो that's going
		 * to be overwritten in a bit?
		 */
		__make_buffer_clean(new);
		__unlink_buffer(new);
		__मुक्त_buffer_wake(new);
	पूर्ण

	BUG_ON(!b->hold_count);
	BUG_ON(test_bit(B_READING, &b->state));

	__ग_लिखो_dirty_buffer(b, शून्य);
	अगर (b->hold_count == 1) अणु
		रुको_on_bit_io(&b->state, B_WRITING,
			       TASK_UNINTERRUPTIBLE);
		set_bit(B_सूचीTY, &b->state);
		b->dirty_start = 0;
		b->dirty_end = c->block_size;
		__unlink_buffer(b);
		__link_buffer(b, new_block, LIST_सूचीTY);
	पूर्ण अन्यथा अणु
		sector_t old_block;
		रुको_on_bit_lock_io(&b->state, B_WRITING,
				    TASK_UNINTERRUPTIBLE);
		/*
		 * Relink buffer to "new_block" so that ग_लिखो_callback
		 * sees "new_block" as a block number.
		 * After the ग_लिखो, link the buffer back to old_block.
		 * All this must be करोne in bufio lock, so that block number
		 * change isn't visible to other thपढ़ोs.
		 */
		old_block = b->block;
		__unlink_buffer(b);
		__link_buffer(b, new_block, b->list_mode);
		submit_io(b, REQ_OP_WRITE, ग_लिखो_endio);
		रुको_on_bit_io(&b->state, B_WRITING,
			       TASK_UNINTERRUPTIBLE);
		__unlink_buffer(b);
		__link_buffer(b, old_block, b->list_mode);
	पूर्ण

	dm_bufio_unlock(c);
	dm_bufio_release(b);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_release_move);

अटल व्योम क्रमget_buffer_locked(काष्ठा dm_buffer *b)
अणु
	अगर (likely(!b->hold_count) && likely(!b->state)) अणु
		__unlink_buffer(b);
		__मुक्त_buffer_wake(b);
	पूर्ण
पूर्ण

/*
 * Free the given buffer.
 *
 * This is just a hपूर्णांक, अगर the buffer is in use or dirty, this function
 * करोes nothing.
 */
व्योम dm_bufio_क्रमget(काष्ठा dm_bufio_client *c, sector_t block)
अणु
	काष्ठा dm_buffer *b;

	dm_bufio_lock(c);

	b = __find(c, block);
	अगर (b)
		क्रमget_buffer_locked(b);

	dm_bufio_unlock(c);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_क्रमget);

व्योम dm_bufio_क्रमget_buffers(काष्ठा dm_bufio_client *c, sector_t block, sector_t n_blocks)
अणु
	काष्ठा dm_buffer *b;
	sector_t end_block = block + n_blocks;

	जबतक (block < end_block) अणु
		dm_bufio_lock(c);

		b = __find_next(c, block);
		अगर (b) अणु
			block = b->block + 1;
			क्रमget_buffer_locked(b);
		पूर्ण

		dm_bufio_unlock(c);

		अगर (!b)
			अवरोध;
	पूर्ण

पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_क्रमget_buffers);

व्योम dm_bufio_set_minimum_buffers(काष्ठा dm_bufio_client *c, अचिन्हित n)
अणु
	c->minimum_buffers = n;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_set_minimum_buffers);

अचिन्हित dm_bufio_get_block_size(काष्ठा dm_bufio_client *c)
अणु
	वापस c->block_size;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_get_block_size);

sector_t dm_bufio_get_device_size(काष्ठा dm_bufio_client *c)
अणु
	sector_t s = i_size_पढ़ो(c->bdev->bd_inode) >> SECTOR_SHIFT;
	अगर (s >= c->start)
		s -= c->start;
	अन्यथा
		s = 0;
	अगर (likely(c->sectors_per_block_bits >= 0))
		s >>= c->sectors_per_block_bits;
	अन्यथा
		sector_भाग(s, c->block_size >> SECTOR_SHIFT);
	वापस s;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_get_device_size);

काष्ठा dm_io_client *dm_bufio_get_dm_io_client(काष्ठा dm_bufio_client *c)
अणु
	वापस c->dm_io;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_get_dm_io_client);

sector_t dm_bufio_get_block_number(काष्ठा dm_buffer *b)
अणु
	वापस b->block;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_get_block_number);

व्योम *dm_bufio_get_block_data(काष्ठा dm_buffer *b)
अणु
	वापस b->data;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_get_block_data);

व्योम *dm_bufio_get_aux_data(काष्ठा dm_buffer *b)
अणु
	वापस b + 1;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_get_aux_data);

काष्ठा dm_bufio_client *dm_bufio_get_client(काष्ठा dm_buffer *b)
अणु
	वापस b->c;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_get_client);

अटल व्योम drop_buffers(काष्ठा dm_bufio_client *c)
अणु
	काष्ठा dm_buffer *b;
	पूर्णांक i;
	bool warned = false;

	BUG_ON(dm_bufio_in_request());

	/*
	 * An optimization so that the buffers are not written one-by-one.
	 */
	dm_bufio_ग_लिखो_dirty_buffers_async(c);

	dm_bufio_lock(c);

	जबतक ((b = __get_unclaimed_buffer(c)))
		__मुक्त_buffer_wake(b);

	क्रम (i = 0; i < LIST_SIZE; i++)
		list_क्रम_each_entry(b, &c->lru[i], lru_list) अणु
			WARN_ON(!warned);
			warned = true;
			DMERR("leaked buffer %llx, hold count %u, list %d",
			      (अचिन्हित दीर्घ दीर्घ)b->block, b->hold_count, i);
#अगर_घोषित CONFIG_DM_DEBUG_BLOCK_STACK_TRACING
			stack_trace_prपूर्णांक(b->stack_entries, b->stack_len, 1);
			/* mark unclaimed to aव्योम BUG_ON below */
			b->hold_count = 0;
#पूर्ण_अगर
		पूर्ण

#अगर_घोषित CONFIG_DM_DEBUG_BLOCK_STACK_TRACING
	जबतक ((b = __get_unclaimed_buffer(c)))
		__मुक्त_buffer_wake(b);
#पूर्ण_अगर

	क्रम (i = 0; i < LIST_SIZE; i++)
		BUG_ON(!list_empty(&c->lru[i]));

	dm_bufio_unlock(c);
पूर्ण

/*
 * We may not be able to evict this buffer अगर IO pending or the client
 * is still using it.  Caller is expected to know buffer is too old.
 *
 * And अगर GFP_NOFS is used, we must not करो any I/O because we hold
 * dm_bufio_clients_lock and we would risk deadlock अगर the I/O माला_लो
 * rerouted to dअगरferent bufio client.
 */
अटल bool __try_evict_buffer(काष्ठा dm_buffer *b, gfp_t gfp)
अणु
	अगर (!(gfp & __GFP_FS)) अणु
		अगर (test_bit(B_READING, &b->state) ||
		    test_bit(B_WRITING, &b->state) ||
		    test_bit(B_सूचीTY, &b->state))
			वापस false;
	पूर्ण

	अगर (b->hold_count)
		वापस false;

	__make_buffer_clean(b);
	__unlink_buffer(b);
	__मुक्त_buffer_wake(b);

	वापस true;
पूर्ण

अटल अचिन्हित दीर्घ get_retain_buffers(काष्ठा dm_bufio_client *c)
अणु
	अचिन्हित दीर्घ retain_bytes = READ_ONCE(dm_bufio_retain_bytes);
	अगर (likely(c->sectors_per_block_bits >= 0))
		retain_bytes >>= c->sectors_per_block_bits + SECTOR_SHIFT;
	अन्यथा
		retain_bytes /= c->block_size;
	वापस retain_bytes;
पूर्ण

अटल व्योम __scan(काष्ठा dm_bufio_client *c)
अणु
	पूर्णांक l;
	काष्ठा dm_buffer *b, *पंचांगp;
	अचिन्हित दीर्घ मुक्तd = 0;
	अचिन्हित दीर्घ count = c->n_buffers[LIST_CLEAN] +
			      c->n_buffers[LIST_सूचीTY];
	अचिन्हित दीर्घ retain_target = get_retain_buffers(c);

	क्रम (l = 0; l < LIST_SIZE; l++) अणु
		list_क्रम_each_entry_safe_reverse(b, पंचांगp, &c->lru[l], lru_list) अणु
			अगर (count - मुक्तd <= retain_target)
				atomic_दीर्घ_set(&c->need_shrink, 0);
			अगर (!atomic_दीर्घ_पढ़ो(&c->need_shrink))
				वापस;
			अगर (__try_evict_buffer(b, GFP_KERNEL)) अणु
				atomic_दीर्घ_dec(&c->need_shrink);
				मुक्तd++;
			पूर्ण
			cond_resched();
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम shrink_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा dm_bufio_client *c = container_of(w, काष्ठा dm_bufio_client, shrink_work);

	dm_bufio_lock(c);
	__scan(c);
	dm_bufio_unlock(c);
पूर्ण

अटल अचिन्हित दीर्घ dm_bufio_shrink_scan(काष्ठा shrinker *shrink, काष्ठा shrink_control *sc)
अणु
	काष्ठा dm_bufio_client *c;

	c = container_of(shrink, काष्ठा dm_bufio_client, shrinker);
	atomic_दीर्घ_add(sc->nr_to_scan, &c->need_shrink);
	queue_work(dm_bufio_wq, &c->shrink_work);

	वापस sc->nr_to_scan;
पूर्ण

अटल अचिन्हित दीर्घ dm_bufio_shrink_count(काष्ठा shrinker *shrink, काष्ठा shrink_control *sc)
अणु
	काष्ठा dm_bufio_client *c = container_of(shrink, काष्ठा dm_bufio_client, shrinker);
	अचिन्हित दीर्घ count = READ_ONCE(c->n_buffers[LIST_CLEAN]) +
			      READ_ONCE(c->n_buffers[LIST_सूचीTY]);
	अचिन्हित दीर्घ retain_target = get_retain_buffers(c);
	अचिन्हित दीर्घ queued_क्रम_cleanup = atomic_दीर्घ_पढ़ो(&c->need_shrink);

	अगर (unlikely(count < retain_target))
		count = 0;
	अन्यथा
		count -= retain_target;

	अगर (unlikely(count < queued_क्रम_cleanup))
		count = 0;
	अन्यथा
		count -= queued_क्रम_cleanup;

	वापस count;
पूर्ण

/*
 * Create the buffering पूर्णांकerface
 */
काष्ठा dm_bufio_client *dm_bufio_client_create(काष्ठा block_device *bdev, अचिन्हित block_size,
					       अचिन्हित reserved_buffers, अचिन्हित aux_size,
					       व्योम (*alloc_callback)(काष्ठा dm_buffer *),
					       व्योम (*ग_लिखो_callback)(काष्ठा dm_buffer *))
अणु
	पूर्णांक r;
	काष्ठा dm_bufio_client *c;
	अचिन्हित i;
	अक्षर slab_name[27];

	अगर (!block_size || block_size & ((1 << SECTOR_SHIFT) - 1)) अणु
		DMERR("%s: block size not specified or is not multiple of 512b", __func__);
		r = -EINVAL;
		जाओ bad_client;
	पूर्ण

	c = kzalloc(माप(*c), GFP_KERNEL);
	अगर (!c) अणु
		r = -ENOMEM;
		जाओ bad_client;
	पूर्ण
	c->buffer_tree = RB_ROOT;

	c->bdev = bdev;
	c->block_size = block_size;
	अगर (is_घातer_of_2(block_size))
		c->sectors_per_block_bits = __ffs(block_size) - SECTOR_SHIFT;
	अन्यथा
		c->sectors_per_block_bits = -1;

	c->alloc_callback = alloc_callback;
	c->ग_लिखो_callback = ग_लिखो_callback;

	क्रम (i = 0; i < LIST_SIZE; i++) अणु
		INIT_LIST_HEAD(&c->lru[i]);
		c->n_buffers[i] = 0;
	पूर्ण

	mutex_init(&c->lock);
	INIT_LIST_HEAD(&c->reserved_buffers);
	c->need_reserved_buffers = reserved_buffers;

	dm_bufio_set_minimum_buffers(c, DM_BUFIO_MIN_BUFFERS);

	init_रुकोqueue_head(&c->मुक्त_buffer_रुको);
	c->async_ग_लिखो_error = 0;

	c->dm_io = dm_io_client_create();
	अगर (IS_ERR(c->dm_io)) अणु
		r = PTR_ERR(c->dm_io);
		जाओ bad_dm_io;
	पूर्ण

	अगर (block_size <= KMALLOC_MAX_SIZE &&
	    (block_size < PAGE_SIZE || !is_घातer_of_2(block_size))) अणु
		अचिन्हित align = min(1U << __ffs(block_size), (अचिन्हित)PAGE_SIZE);
		snम_लिखो(slab_name, माप slab_name, "dm_bufio_cache-%u", block_size);
		c->slab_cache = kmem_cache_create(slab_name, block_size, align,
						  SLAB_RECLAIM_ACCOUNT, शून्य);
		अगर (!c->slab_cache) अणु
			r = -ENOMEM;
			जाओ bad;
		पूर्ण
	पूर्ण
	अगर (aux_size)
		snम_लिखो(slab_name, माप slab_name, "dm_bufio_buffer-%u", aux_size);
	अन्यथा
		snम_लिखो(slab_name, माप slab_name, "dm_bufio_buffer");
	c->slab_buffer = kmem_cache_create(slab_name, माप(काष्ठा dm_buffer) + aux_size,
					   0, SLAB_RECLAIM_ACCOUNT, शून्य);
	अगर (!c->slab_buffer) अणु
		r = -ENOMEM;
		जाओ bad;
	पूर्ण

	जबतक (c->need_reserved_buffers) अणु
		काष्ठा dm_buffer *b = alloc_buffer(c, GFP_KERNEL);

		अगर (!b) अणु
			r = -ENOMEM;
			जाओ bad;
		पूर्ण
		__मुक्त_buffer_wake(b);
	पूर्ण

	INIT_WORK(&c->shrink_work, shrink_work);
	atomic_दीर्घ_set(&c->need_shrink, 0);

	c->shrinker.count_objects = dm_bufio_shrink_count;
	c->shrinker.scan_objects = dm_bufio_shrink_scan;
	c->shrinker.seeks = 1;
	c->shrinker.batch = 0;
	r = रेजिस्टर_shrinker(&c->shrinker);
	अगर (r)
		जाओ bad;

	mutex_lock(&dm_bufio_clients_lock);
	dm_bufio_client_count++;
	list_add(&c->client_list, &dm_bufio_all_clients);
	__cache_size_refresh();
	mutex_unlock(&dm_bufio_clients_lock);

	वापस c;

bad:
	जबतक (!list_empty(&c->reserved_buffers)) अणु
		काष्ठा dm_buffer *b = list_entry(c->reserved_buffers.next,
						 काष्ठा dm_buffer, lru_list);
		list_del(&b->lru_list);
		मुक्त_buffer(b);
	पूर्ण
	kmem_cache_destroy(c->slab_cache);
	kmem_cache_destroy(c->slab_buffer);
	dm_io_client_destroy(c->dm_io);
bad_dm_io:
	mutex_destroy(&c->lock);
	kमुक्त(c);
bad_client:
	वापस ERR_PTR(r);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_client_create);

/*
 * Free the buffering पूर्णांकerface.
 * It is required that there are no references on any buffers.
 */
व्योम dm_bufio_client_destroy(काष्ठा dm_bufio_client *c)
अणु
	अचिन्हित i;

	drop_buffers(c);

	unरेजिस्टर_shrinker(&c->shrinker);
	flush_work(&c->shrink_work);

	mutex_lock(&dm_bufio_clients_lock);

	list_del(&c->client_list);
	dm_bufio_client_count--;
	__cache_size_refresh();

	mutex_unlock(&dm_bufio_clients_lock);

	BUG_ON(!RB_EMPTY_ROOT(&c->buffer_tree));
	BUG_ON(c->need_reserved_buffers);

	जबतक (!list_empty(&c->reserved_buffers)) अणु
		काष्ठा dm_buffer *b = list_entry(c->reserved_buffers.next,
						 काष्ठा dm_buffer, lru_list);
		list_del(&b->lru_list);
		मुक्त_buffer(b);
	पूर्ण

	क्रम (i = 0; i < LIST_SIZE; i++)
		अगर (c->n_buffers[i])
			DMERR("leaked buffer count %d: %ld", i, c->n_buffers[i]);

	क्रम (i = 0; i < LIST_SIZE; i++)
		BUG_ON(c->n_buffers[i]);

	kmem_cache_destroy(c->slab_cache);
	kmem_cache_destroy(c->slab_buffer);
	dm_io_client_destroy(c->dm_io);
	mutex_destroy(&c->lock);
	kमुक्त(c);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_client_destroy);

व्योम dm_bufio_set_sector_offset(काष्ठा dm_bufio_client *c, sector_t start)
अणु
	c->start = start;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bufio_set_sector_offset);

अटल अचिन्हित get_max_age_hz(व्योम)
अणु
	अचिन्हित max_age = READ_ONCE(dm_bufio_max_age);

	अगर (max_age > अच_पूर्णांक_उच्च / HZ)
		max_age = अच_पूर्णांक_उच्च / HZ;

	वापस max_age * HZ;
पूर्ण

अटल bool older_than(काष्ठा dm_buffer *b, अचिन्हित दीर्घ age_hz)
अणु
	वापस समय_after_eq(jअगरfies, b->last_accessed + age_hz);
पूर्ण

अटल व्योम __evict_old_buffers(काष्ठा dm_bufio_client *c, अचिन्हित दीर्घ age_hz)
अणु
	काष्ठा dm_buffer *b, *पंचांगp;
	अचिन्हित दीर्घ retain_target = get_retain_buffers(c);
	अचिन्हित दीर्घ count;
	LIST_HEAD(ग_लिखो_list);

	dm_bufio_lock(c);

	__check_watermark(c, &ग_लिखो_list);
	अगर (unlikely(!list_empty(&ग_लिखो_list))) अणु
		dm_bufio_unlock(c);
		__flush_ग_लिखो_list(&ग_लिखो_list);
		dm_bufio_lock(c);
	पूर्ण

	count = c->n_buffers[LIST_CLEAN] + c->n_buffers[LIST_सूचीTY];
	list_क्रम_each_entry_safe_reverse(b, पंचांगp, &c->lru[LIST_CLEAN], lru_list) अणु
		अगर (count <= retain_target)
			अवरोध;

		अगर (!older_than(b, age_hz))
			अवरोध;

		अगर (__try_evict_buffer(b, 0))
			count--;

		cond_resched();
	पूर्ण

	dm_bufio_unlock(c);
पूर्ण

अटल व्योम करो_global_cleanup(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा dm_bufio_client *locked_client = शून्य;
	काष्ठा dm_bufio_client *current_client;
	काष्ठा dm_buffer *b;
	अचिन्हित spinlock_hold_count;
	अचिन्हित दीर्घ threshold = dm_bufio_cache_size -
		dm_bufio_cache_size / DM_BUFIO_LOW_WATERMARK_RATIO;
	अचिन्हित दीर्घ loops = global_num * 2;

	mutex_lock(&dm_bufio_clients_lock);

	जबतक (1) अणु
		cond_resched();

		spin_lock(&global_spinlock);
		अगर (unlikely(dm_bufio_current_allocated <= threshold))
			अवरोध;

		spinlock_hold_count = 0;
get_next:
		अगर (!loops--)
			अवरोध;
		अगर (unlikely(list_empty(&global_queue)))
			अवरोध;
		b = list_entry(global_queue.prev, काष्ठा dm_buffer, global_list);

		अगर (b->accessed) अणु
			b->accessed = 0;
			list_move(&b->global_list, &global_queue);
			अगर (likely(++spinlock_hold_count < 16))
				जाओ get_next;
			spin_unlock(&global_spinlock);
			जारी;
		पूर्ण

		current_client = b->c;
		अगर (unlikely(current_client != locked_client)) अणु
			अगर (locked_client)
				dm_bufio_unlock(locked_client);

			अगर (!dm_bufio_trylock(current_client)) अणु
				spin_unlock(&global_spinlock);
				dm_bufio_lock(current_client);
				locked_client = current_client;
				जारी;
			पूर्ण

			locked_client = current_client;
		पूर्ण

		spin_unlock(&global_spinlock);

		अगर (unlikely(!__try_evict_buffer(b, GFP_KERNEL))) अणु
			spin_lock(&global_spinlock);
			list_move(&b->global_list, &global_queue);
			spin_unlock(&global_spinlock);
		पूर्ण
	पूर्ण

	spin_unlock(&global_spinlock);

	अगर (locked_client)
		dm_bufio_unlock(locked_client);

	mutex_unlock(&dm_bufio_clients_lock);
पूर्ण

अटल व्योम cleanup_old_buffers(व्योम)
अणु
	अचिन्हित दीर्घ max_age_hz = get_max_age_hz();
	काष्ठा dm_bufio_client *c;

	mutex_lock(&dm_bufio_clients_lock);

	__cache_size_refresh();

	list_क्रम_each_entry(c, &dm_bufio_all_clients, client_list)
		__evict_old_buffers(c, max_age_hz);

	mutex_unlock(&dm_bufio_clients_lock);
पूर्ण

अटल व्योम work_fn(काष्ठा work_काष्ठा *w)
अणु
	cleanup_old_buffers();

	queue_delayed_work(dm_bufio_wq, &dm_bufio_cleanup_old_work,
			   DM_BUFIO_WORK_TIMER_SECS * HZ);
पूर्ण

/*----------------------------------------------------------------
 * Module setup
 *--------------------------------------------------------------*/

/*
 * This is called only once क्रम the whole dm_bufio module.
 * It initializes memory limit.
 */
अटल पूर्णांक __init dm_bufio_init(व्योम)
अणु
	__u64 mem;

	dm_bufio_allocated_kmem_cache = 0;
	dm_bufio_allocated_get_मुक्त_pages = 0;
	dm_bufio_allocated_vदो_स्मृति = 0;
	dm_bufio_current_allocated = 0;

	mem = (__u64)mult_frac(totalram_pages() - totalhigh_pages(),
			       DM_BUFIO_MEMORY_PERCENT, 100) << PAGE_SHIFT;

	अगर (mem > अच_दीर्घ_उच्च)
		mem = अच_दीर्घ_उच्च;

#अगर_घोषित CONFIG_MMU
	अगर (mem > mult_frac(VMALLOC_TOTAL, DM_BUFIO_VMALLOC_PERCENT, 100))
		mem = mult_frac(VMALLOC_TOTAL, DM_BUFIO_VMALLOC_PERCENT, 100);
#पूर्ण_अगर

	dm_bufio_शेष_cache_size = mem;

	mutex_lock(&dm_bufio_clients_lock);
	__cache_size_refresh();
	mutex_unlock(&dm_bufio_clients_lock);

	dm_bufio_wq = alloc_workqueue("dm_bufio_cache", WQ_MEM_RECLAIM, 0);
	अगर (!dm_bufio_wq)
		वापस -ENOMEM;

	INIT_DELAYED_WORK(&dm_bufio_cleanup_old_work, work_fn);
	INIT_WORK(&dm_bufio_replacement_work, करो_global_cleanup);
	queue_delayed_work(dm_bufio_wq, &dm_bufio_cleanup_old_work,
			   DM_BUFIO_WORK_TIMER_SECS * HZ);

	वापस 0;
पूर्ण

/*
 * This is called once when unloading the dm_bufio module.
 */
अटल व्योम __निकास dm_bufio_निकास(व्योम)
अणु
	पूर्णांक bug = 0;

	cancel_delayed_work_sync(&dm_bufio_cleanup_old_work);
	flush_workqueue(dm_bufio_wq);
	destroy_workqueue(dm_bufio_wq);

	अगर (dm_bufio_client_count) अणु
		DMCRIT("%s: dm_bufio_client_count leaked: %d",
			__func__, dm_bufio_client_count);
		bug = 1;
	पूर्ण

	अगर (dm_bufio_current_allocated) अणु
		DMCRIT("%s: dm_bufio_current_allocated leaked: %lu",
			__func__, dm_bufio_current_allocated);
		bug = 1;
	पूर्ण

	अगर (dm_bufio_allocated_get_मुक्त_pages) अणु
		DMCRIT("%s: dm_bufio_allocated_get_free_pages leaked: %lu",
		       __func__, dm_bufio_allocated_get_मुक्त_pages);
		bug = 1;
	पूर्ण

	अगर (dm_bufio_allocated_vदो_स्मृति) अणु
		DMCRIT("%s: dm_bufio_vmalloc leaked: %lu",
		       __func__, dm_bufio_allocated_vदो_स्मृति);
		bug = 1;
	पूर्ण

	BUG_ON(bug);
पूर्ण

module_init(dm_bufio_init)
module_निकास(dm_bufio_निकास)

module_param_named(max_cache_size_bytes, dm_bufio_cache_size, uदीर्घ, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(max_cache_size_bytes, "Size of metadata cache");

module_param_named(max_age_seconds, dm_bufio_max_age, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(max_age_seconds, "Max age of a buffer in seconds");

module_param_named(retain_bytes, dm_bufio_retain_bytes, uदीर्घ, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(retain_bytes, "Try to keep at least this many bytes cached in memory");

module_param_named(peak_allocated_bytes, dm_bufio_peak_allocated, uदीर्घ, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(peak_allocated_bytes, "Tracks the maximum allocated memory");

module_param_named(allocated_kmem_cache_bytes, dm_bufio_allocated_kmem_cache, uदीर्घ, S_IRUGO);
MODULE_PARM_DESC(allocated_kmem_cache_bytes, "Memory allocated with kmem_cache_alloc");

module_param_named(allocated_get_मुक्त_pages_bytes, dm_bufio_allocated_get_मुक्त_pages, uदीर्घ, S_IRUGO);
MODULE_PARM_DESC(allocated_get_मुक्त_pages_bytes, "Memory allocated with get_free_pages");

module_param_named(allocated_vदो_स्मृति_bytes, dm_bufio_allocated_vदो_स्मृति, uदीर्घ, S_IRUGO);
MODULE_PARM_DESC(allocated_vदो_स्मृति_bytes, "Memory allocated with vmalloc");

module_param_named(current_allocated_bytes, dm_bufio_current_allocated, uदीर्घ, S_IRUGO);
MODULE_PARM_DESC(current_allocated_bytes, "Memory currently used by the cache");

MODULE_AUTHOR("Mikulas Patocka <dm-devel@redhat.com>");
MODULE_DESCRIPTION(DM_NAME " buffered I/O library");
MODULE_LICENSE("GPL");
