<शैली गुरु>
#समावेश <linux/bpf.h>
#समावेश <linux/btf.h>
#समावेश <linux/err.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/slab.h>
#समावेश <linux/filter.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/रुको.h>
#समावेश <linux/poll.h>
#समावेश <uapi/linux/btf.h>

#घोषणा RINGBUF_CREATE_FLAG_MASK (BPF_F_NUMA_NODE)

/* non-mmap()'able part of bpf_ringbuf (everything up to consumer page) */
#घोषणा RINGBUF_PGOFF \
	(दुरत्व(काष्ठा bpf_ringbuf, consumer_pos) >> PAGE_SHIFT)
/* consumer page and producer page */
#घोषणा RINGBUF_POS_PAGES 2

#घोषणा RINGBUF_MAX_RECORD_SZ (अच_पूर्णांक_उच्च/4)

/* Maximum size of ring buffer area is limited by 32-bit page offset within
 * record header, counted in pages. Reserve 8 bits क्रम extensibility, and take
 * पूर्णांकo account few extra pages क्रम consumer/producer pages and
 * non-mmap()'able parts. This gives 64GB limit, which seems plenty क्रम single
 * ring buffer.
 */
#घोषणा RINGBUF_MAX_DATA_SZ \
	(((1ULL << 24) - RINGBUF_POS_PAGES - RINGBUF_PGOFF) * PAGE_SIZE)

काष्ठा bpf_ringbuf अणु
	रुको_queue_head_t रुकोq;
	काष्ठा irq_work work;
	u64 mask;
	काष्ठा page **pages;
	पूर्णांक nr_pages;
	spinlock_t spinlock ____cacheline_aligned_in_smp;
	/* Consumer and producer counters are put पूर्णांकo separate pages to allow
	 * mapping consumer page as r/w, but restrict producer page to r/o.
	 * This protects producer position from being modअगरied by user-space
	 * application and ruining in-kernel position tracking.
	 */
	अचिन्हित दीर्घ consumer_pos __aligned(PAGE_SIZE);
	अचिन्हित दीर्घ producer_pos __aligned(PAGE_SIZE);
	अक्षर data[] __aligned(PAGE_SIZE);
पूर्ण;

काष्ठा bpf_ringbuf_map अणु
	काष्ठा bpf_map map;
	काष्ठा bpf_ringbuf *rb;
पूर्ण;

/* 8-byte ring buffer record header काष्ठाure */
काष्ठा bpf_ringbuf_hdr अणु
	u32 len;
	u32 pg_off;
पूर्ण;

अटल काष्ठा bpf_ringbuf *bpf_ringbuf_area_alloc(माप_प्रकार data_sz, पूर्णांक numa_node)
अणु
	स्थिर gfp_t flags = GFP_KERNEL_ACCOUNT | __GFP_RETRY_MAYFAIL |
			    __GFP_NOWARN | __GFP_ZERO;
	पूर्णांक nr_meta_pages = RINGBUF_PGOFF + RINGBUF_POS_PAGES;
	पूर्णांक nr_data_pages = data_sz >> PAGE_SHIFT;
	पूर्णांक nr_pages = nr_meta_pages + nr_data_pages;
	काष्ठा page **pages, *page;
	काष्ठा bpf_ringbuf *rb;
	माप_प्रकार array_size;
	पूर्णांक i;

	/* Each data page is mapped twice to allow "virtual"
	 * continuous पढ़ो of samples wrapping around the end of ring
	 * buffer area:
	 * ------------------------------------------------------
	 * | meta pages |  real data pages  |  same data pages  |
	 * ------------------------------------------------------
	 * |            | 1 2 3 4 5 6 7 8 9 | 1 2 3 4 5 6 7 8 9 |
	 * ------------------------------------------------------
	 * |            | TA             DA | TA             DA |
	 * ------------------------------------------------------
	 *                               ^^^^^^^
	 *                                  |
	 * Here, no need to worry about special handling of wrapped-around
	 * data due to द्विगुन-mapped data pages. This works both in kernel and
	 * when mmap()'ed in user-space, simplअगरying both kernel and
	 * user-space implementations signअगरicantly.
	 */
	array_size = (nr_meta_pages + 2 * nr_data_pages) * माप(*pages);
	pages = bpf_map_area_alloc(array_size, numa_node);
	अगर (!pages)
		वापस शून्य;

	क्रम (i = 0; i < nr_pages; i++) अणु
		page = alloc_pages_node(numa_node, flags, 0);
		अगर (!page) अणु
			nr_pages = i;
			जाओ err_मुक्त_pages;
		पूर्ण
		pages[i] = page;
		अगर (i >= nr_meta_pages)
			pages[nr_data_pages + i] = page;
	पूर्ण

	rb = vmap(pages, nr_meta_pages + 2 * nr_data_pages,
		  VM_ALLOC | VM_USERMAP, PAGE_KERNEL);
	अगर (rb) अणु
		rb->pages = pages;
		rb->nr_pages = nr_pages;
		वापस rb;
	पूर्ण

err_मुक्त_pages:
	क्रम (i = 0; i < nr_pages; i++)
		__मुक्त_page(pages[i]);
	kvमुक्त(pages);
	वापस शून्य;
पूर्ण

अटल व्योम bpf_ringbuf_notअगरy(काष्ठा irq_work *work)
अणु
	काष्ठा bpf_ringbuf *rb = container_of(work, काष्ठा bpf_ringbuf, work);

	wake_up_all(&rb->रुकोq);
पूर्ण

अटल काष्ठा bpf_ringbuf *bpf_ringbuf_alloc(माप_प्रकार data_sz, पूर्णांक numa_node)
अणु
	काष्ठा bpf_ringbuf *rb;

	rb = bpf_ringbuf_area_alloc(data_sz, numa_node);
	अगर (!rb)
		वापस शून्य;

	spin_lock_init(&rb->spinlock);
	init_रुकोqueue_head(&rb->रुकोq);
	init_irq_work(&rb->work, bpf_ringbuf_notअगरy);

	rb->mask = data_sz - 1;
	rb->consumer_pos = 0;
	rb->producer_pos = 0;

	वापस rb;
पूर्ण

अटल काष्ठा bpf_map *ringbuf_map_alloc(जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_ringbuf_map *rb_map;

	अगर (attr->map_flags & ~RINGBUF_CREATE_FLAG_MASK)
		वापस ERR_PTR(-EINVAL);

	अगर (attr->key_size || attr->value_size ||
	    !is_घातer_of_2(attr->max_entries) ||
	    !PAGE_ALIGNED(attr->max_entries))
		वापस ERR_PTR(-EINVAL);

#अगर_घोषित CONFIG_64BIT
	/* on 32-bit arch, it's impossible to overflow record's hdr->pgoff */
	अगर (attr->max_entries > RINGBUF_MAX_DATA_SZ)
		वापस ERR_PTR(-E2BIG);
#पूर्ण_अगर

	rb_map = kzalloc(माप(*rb_map), GFP_USER | __GFP_ACCOUNT);
	अगर (!rb_map)
		वापस ERR_PTR(-ENOMEM);

	bpf_map_init_from_attr(&rb_map->map, attr);

	rb_map->rb = bpf_ringbuf_alloc(attr->max_entries, rb_map->map.numa_node);
	अगर (!rb_map->rb) अणु
		kमुक्त(rb_map);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस &rb_map->map;
पूर्ण

अटल व्योम bpf_ringbuf_मुक्त(काष्ठा bpf_ringbuf *rb)
अणु
	/* copy pages poपूर्णांकer and nr_pages to local variable, as we are going
	 * to unmap rb itself with vunmap() below
	 */
	काष्ठा page **pages = rb->pages;
	पूर्णांक i, nr_pages = rb->nr_pages;

	vunmap(rb);
	क्रम (i = 0; i < nr_pages; i++)
		__मुक्त_page(pages[i]);
	kvमुक्त(pages);
पूर्ण

अटल व्योम ringbuf_map_मुक्त(काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_ringbuf_map *rb_map;

	rb_map = container_of(map, काष्ठा bpf_ringbuf_map, map);
	bpf_ringbuf_मुक्त(rb_map->rb);
	kमुक्त(rb_map);
पूर्ण

अटल व्योम *ringbuf_map_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	वापस ERR_PTR(-ENOTSUPP);
पूर्ण

अटल पूर्णांक ringbuf_map_update_elem(काष्ठा bpf_map *map, व्योम *key, व्योम *value,
				   u64 flags)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक ringbuf_map_delete_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक ringbuf_map_get_next_key(काष्ठा bpf_map *map, व्योम *key,
				    व्योम *next_key)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक ringbuf_map_mmap(काष्ठा bpf_map *map, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा bpf_ringbuf_map *rb_map;

	rb_map = container_of(map, काष्ठा bpf_ringbuf_map, map);

	अगर (vma->vm_flags & VM_WRITE) अणु
		/* allow writable mapping क्रम the consumer_pos only */
		अगर (vma->vm_pgoff != 0 || vma->vm_end - vma->vm_start != PAGE_SIZE)
			वापस -EPERM;
	पूर्ण अन्यथा अणु
		vma->vm_flags &= ~VM_MAYWRITE;
	पूर्ण
	/* remap_vदो_स्मृति_range() checks size and offset स्थिरraपूर्णांकs */
	वापस remap_vदो_स्मृति_range(vma, rb_map->rb,
				   vma->vm_pgoff + RINGBUF_PGOFF);
पूर्ण

अटल अचिन्हित दीर्घ ringbuf_avail_data_sz(काष्ठा bpf_ringbuf *rb)
अणु
	अचिन्हित दीर्घ cons_pos, prod_pos;

	cons_pos = smp_load_acquire(&rb->consumer_pos);
	prod_pos = smp_load_acquire(&rb->producer_pos);
	वापस prod_pos - cons_pos;
पूर्ण

अटल __poll_t ringbuf_map_poll(काष्ठा bpf_map *map, काष्ठा file *filp,
				 काष्ठा poll_table_काष्ठा *pts)
अणु
	काष्ठा bpf_ringbuf_map *rb_map;

	rb_map = container_of(map, काष्ठा bpf_ringbuf_map, map);
	poll_रुको(filp, &rb_map->rb->रुकोq, pts);

	अगर (ringbuf_avail_data_sz(rb_map->rb))
		वापस EPOLLIN | EPOLLRDNORM;
	वापस 0;
पूर्ण

अटल पूर्णांक ringbuf_map_btf_id;
स्थिर काष्ठा bpf_map_ops ringbuf_map_ops = अणु
	.map_meta_equal = bpf_map_meta_equal,
	.map_alloc = ringbuf_map_alloc,
	.map_मुक्त = ringbuf_map_मुक्त,
	.map_mmap = ringbuf_map_mmap,
	.map_poll = ringbuf_map_poll,
	.map_lookup_elem = ringbuf_map_lookup_elem,
	.map_update_elem = ringbuf_map_update_elem,
	.map_delete_elem = ringbuf_map_delete_elem,
	.map_get_next_key = ringbuf_map_get_next_key,
	.map_btf_name = "bpf_ringbuf_map",
	.map_btf_id = &ringbuf_map_btf_id,
पूर्ण;

/* Given poपूर्णांकer to ring buffer record metadata and काष्ठा bpf_ringbuf itself,
 * calculate offset from record metadata to ring buffer in pages, rounded
 * करोwn. This page offset is stored as part of record metadata and allows to
 * restore काष्ठा bpf_ringbuf * from record poपूर्णांकer. This page offset is
 * stored at offset 4 of record metadata header.
 */
अटल माप_प्रकार bpf_ringbuf_rec_pg_off(काष्ठा bpf_ringbuf *rb,
				     काष्ठा bpf_ringbuf_hdr *hdr)
अणु
	वापस ((व्योम *)hdr - (व्योम *)rb) >> PAGE_SHIFT;
पूर्ण

/* Given poपूर्णांकer to ring buffer record header, restore poपूर्णांकer to काष्ठा
 * bpf_ringbuf itself by using page offset stored at offset 4
 */
अटल काष्ठा bpf_ringbuf *
bpf_ringbuf_restore_from_rec(काष्ठा bpf_ringbuf_hdr *hdr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)(व्योम *)hdr;
	अचिन्हित दीर्घ off = (अचिन्हित दीर्घ)hdr->pg_off << PAGE_SHIFT;

	वापस (व्योम*)((addr & PAGE_MASK) - off);
पूर्ण

अटल व्योम *__bpf_ringbuf_reserve(काष्ठा bpf_ringbuf *rb, u64 size)
अणु
	अचिन्हित दीर्घ cons_pos, prod_pos, new_prod_pos, flags;
	u32 len, pg_off;
	काष्ठा bpf_ringbuf_hdr *hdr;

	अगर (unlikely(size > RINGBUF_MAX_RECORD_SZ))
		वापस शून्य;

	len = round_up(size + BPF_RINGBUF_HDR_SZ, 8);
	अगर (len > rb->mask + 1)
		वापस शून्य;

	cons_pos = smp_load_acquire(&rb->consumer_pos);

	अगर (in_nmi()) अणु
		अगर (!spin_trylock_irqsave(&rb->spinlock, flags))
			वापस शून्य;
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&rb->spinlock, flags);
	पूर्ण

	prod_pos = rb->producer_pos;
	new_prod_pos = prod_pos + len;

	/* check क्रम out of ringbuf space by ensuring producer position
	 * करोesn't advance more than (ringbuf_size - 1) ahead
	 */
	अगर (new_prod_pos - cons_pos > rb->mask) अणु
		spin_unlock_irqrestore(&rb->spinlock, flags);
		वापस शून्य;
	पूर्ण

	hdr = (व्योम *)rb->data + (prod_pos & rb->mask);
	pg_off = bpf_ringbuf_rec_pg_off(rb, hdr);
	hdr->len = size | BPF_RINGBUF_BUSY_BIT;
	hdr->pg_off = pg_off;

	/* pairs with consumer's smp_load_acquire() */
	smp_store_release(&rb->producer_pos, new_prod_pos);

	spin_unlock_irqrestore(&rb->spinlock, flags);

	वापस (व्योम *)hdr + BPF_RINGBUF_HDR_SZ;
पूर्ण

BPF_CALL_3(bpf_ringbuf_reserve, काष्ठा bpf_map *, map, u64, size, u64, flags)
अणु
	काष्ठा bpf_ringbuf_map *rb_map;

	अगर (unlikely(flags))
		वापस 0;

	rb_map = container_of(map, काष्ठा bpf_ringbuf_map, map);
	वापस (अचिन्हित दीर्घ)__bpf_ringbuf_reserve(rb_map->rb, size);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_ringbuf_reserve_proto = अणु
	.func		= bpf_ringbuf_reserve,
	.ret_type	= RET_PTR_TO_ALLOC_MEM_OR_शून्य,
	.arg1_type	= ARG_CONST_MAP_PTR,
	.arg2_type	= ARG_CONST_ALLOC_SIZE_OR_ZERO,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;

अटल व्योम bpf_ringbuf_commit(व्योम *sample, u64 flags, bool discard)
अणु
	अचिन्हित दीर्घ rec_pos, cons_pos;
	काष्ठा bpf_ringbuf_hdr *hdr;
	काष्ठा bpf_ringbuf *rb;
	u32 new_len;

	hdr = sample - BPF_RINGBUF_HDR_SZ;
	rb = bpf_ringbuf_restore_from_rec(hdr);
	new_len = hdr->len ^ BPF_RINGBUF_BUSY_BIT;
	अगर (discard)
		new_len |= BPF_RINGBUF_DISCARD_BIT;

	/* update record header with correct final size prefix */
	xchg(&hdr->len, new_len);

	/* अगर consumer caught up and is रुकोing क्रम our record, notअगरy about
	 * new data availability
	 */
	rec_pos = (व्योम *)hdr - (व्योम *)rb->data;
	cons_pos = smp_load_acquire(&rb->consumer_pos) & rb->mask;

	अगर (flags & BPF_RB_FORCE_WAKEUP)
		irq_work_queue(&rb->work);
	अन्यथा अगर (cons_pos == rec_pos && !(flags & BPF_RB_NO_WAKEUP))
		irq_work_queue(&rb->work);
पूर्ण

BPF_CALL_2(bpf_ringbuf_submit, व्योम *, sample, u64, flags)
अणु
	bpf_ringbuf_commit(sample, flags, false /* discard */);
	वापस 0;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_ringbuf_submit_proto = अणु
	.func		= bpf_ringbuf_submit,
	.ret_type	= RET_VOID,
	.arg1_type	= ARG_PTR_TO_ALLOC_MEM,
	.arg2_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_2(bpf_ringbuf_discard, व्योम *, sample, u64, flags)
अणु
	bpf_ringbuf_commit(sample, flags, true /* discard */);
	वापस 0;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_ringbuf_discard_proto = अणु
	.func		= bpf_ringbuf_discard,
	.ret_type	= RET_VOID,
	.arg1_type	= ARG_PTR_TO_ALLOC_MEM,
	.arg2_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_4(bpf_ringbuf_output, काष्ठा bpf_map *, map, व्योम *, data, u64, size,
	   u64, flags)
अणु
	काष्ठा bpf_ringbuf_map *rb_map;
	व्योम *rec;

	अगर (unlikely(flags & ~(BPF_RB_NO_WAKEUP | BPF_RB_FORCE_WAKEUP)))
		वापस -EINVAL;

	rb_map = container_of(map, काष्ठा bpf_ringbuf_map, map);
	rec = __bpf_ringbuf_reserve(rb_map->rb, size);
	अगर (!rec)
		वापस -EAGAIN;

	स_नकल(rec, data, size);
	bpf_ringbuf_commit(rec, flags, false /* discard */);
	वापस 0;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_ringbuf_output_proto = अणु
	.func		= bpf_ringbuf_output,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_CONST_MAP_PTR,
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE_OR_ZERO,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_2(bpf_ringbuf_query, काष्ठा bpf_map *, map, u64, flags)
अणु
	काष्ठा bpf_ringbuf *rb;

	rb = container_of(map, काष्ठा bpf_ringbuf_map, map)->rb;

	चयन (flags) अणु
	हाल BPF_RB_AVAIL_DATA:
		वापस ringbuf_avail_data_sz(rb);
	हाल BPF_RB_RING_SIZE:
		वापस rb->mask + 1;
	हाल BPF_RB_CONS_POS:
		वापस smp_load_acquire(&rb->consumer_pos);
	हाल BPF_RB_PROD_POS:
		वापस smp_load_acquire(&rb->producer_pos);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_ringbuf_query_proto = अणु
	.func		= bpf_ringbuf_query,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_CONST_MAP_PTR,
	.arg2_type	= ARG_ANYTHING,
पूर्ण;
