<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) 2001 Clemson University and The University of Chicago
 *
 * See COPYING in top-level directory.
 */
#समावेश "protocol.h"
#समावेश "orangefs-kernel.h"
#समावेश "orangefs-bufmap.h"

काष्ठा slot_map अणु
	पूर्णांक c;
	रुको_queue_head_t q;
	पूर्णांक count;
	अचिन्हित दीर्घ *map;
पूर्ण;

अटल काष्ठा slot_map rw_map = अणु
	.c = -1,
	.q = __WAIT_QUEUE_HEAD_INITIALIZER(rw_map.q)
पूर्ण;
अटल काष्ठा slot_map सूची_पढ़ो_map = अणु
	.c = -1,
	.q = __WAIT_QUEUE_HEAD_INITIALIZER(सूची_पढ़ो_map.q)
पूर्ण;


अटल व्योम install(काष्ठा slot_map *m, पूर्णांक count, अचिन्हित दीर्घ *map)
अणु
	spin_lock(&m->q.lock);
	m->c = m->count = count;
	m->map = map;
	wake_up_all_locked(&m->q);
	spin_unlock(&m->q.lock);
पूर्ण

अटल व्योम mark_समाप्तed(काष्ठा slot_map *m)
अणु
	spin_lock(&m->q.lock);
	m->c -= m->count + 1;
	spin_unlock(&m->q.lock);
पूर्ण

अटल व्योम run_करोwn(काष्ठा slot_map *m)
अणु
	DEFINE_WAIT(रुको);
	spin_lock(&m->q.lock);
	अगर (m->c != -1) अणु
		क्रम (;;) अणु
			अगर (likely(list_empty(&रुको.entry)))
				__add_रुको_queue_entry_tail(&m->q, &रुको);
			set_current_state(TASK_UNINTERRUPTIBLE);

			अगर (m->c == -1)
				अवरोध;

			spin_unlock(&m->q.lock);
			schedule();
			spin_lock(&m->q.lock);
		पूर्ण
		__हटाओ_रुको_queue(&m->q, &रुको);
		__set_current_state(TASK_RUNNING);
	पूर्ण
	m->map = शून्य;
	spin_unlock(&m->q.lock);
पूर्ण

अटल व्योम put(काष्ठा slot_map *m, पूर्णांक slot)
अणु
	पूर्णांक v;
	spin_lock(&m->q.lock);
	__clear_bit(slot, m->map);
	v = ++m->c;
	अगर (v > 0)
		wake_up_locked(&m->q);
	अगर (unlikely(v == -1))     /* finished dying */
		wake_up_all_locked(&m->q);
	spin_unlock(&m->q.lock);
पूर्ण

अटल पूर्णांक रुको_क्रम_मुक्त(काष्ठा slot_map *m)
अणु
	दीर्घ left = slot_समयout_secs * HZ;
	DEFINE_WAIT(रुको);

	करो अणु
		दीर्घ n = left, t;
		अगर (likely(list_empty(&रुको.entry)))
			__add_रुको_queue_entry_tail_exclusive(&m->q, &रुको);
		set_current_state(TASK_INTERRUPTIBLE);

		अगर (m->c > 0)
			अवरोध;

		अगर (m->c < 0) अणु
			/* we are रुकोing क्रम map to be installed */
			/* it would better be there soon, or we go away */
			अगर (n > ORANGEFS_BUFMAP_WAIT_TIMEOUT_SECS * HZ)
				n = ORANGEFS_BUFMAP_WAIT_TIMEOUT_SECS * HZ;
		पूर्ण
		spin_unlock(&m->q.lock);
		t = schedule_समयout(n);
		spin_lock(&m->q.lock);
		अगर (unlikely(!t) && n != left && m->c < 0)
			left = t;
		अन्यथा
			left = t + (left - n);
		अगर (संकेत_pending(current))
			left = -EINTR;
	पूर्ण जबतक (left > 0);

	अगर (!list_empty(&रुको.entry))
		list_del(&रुको.entry);
	अन्यथा अगर (left <= 0 && रुकोqueue_active(&m->q))
		__wake_up_locked_key(&m->q, TASK_INTERRUPTIBLE, शून्य);
	__set_current_state(TASK_RUNNING);

	अगर (likely(left > 0))
		वापस 0;

	वापस left < 0 ? -EINTR : -ETIMEDOUT;
पूर्ण

अटल पूर्णांक get(काष्ठा slot_map *m)
अणु
	पूर्णांक res = 0;
	spin_lock(&m->q.lock);
	अगर (unlikely(m->c <= 0))
		res = रुको_क्रम_मुक्त(m);
	अगर (likely(!res)) अणु
		m->c--;
		res = find_first_zero_bit(m->map, m->count);
		__set_bit(res, m->map);
	पूर्ण
	spin_unlock(&m->q.lock);
	वापस res;
पूर्ण

/* used to describe mapped buffers */
काष्ठा orangefs_bufmap_desc अणु
	व्योम __user *uaddr;		/* user space address poपूर्णांकer */
	काष्ठा page **page_array;	/* array of mapped pages */
	पूर्णांक array_count;		/* size of above arrays */
	काष्ठा list_head list_link;
पूर्ण;

अटल काष्ठा orangefs_bufmap अणु
	पूर्णांक desc_size;
	पूर्णांक desc_shअगरt;
	पूर्णांक desc_count;
	पूर्णांक total_size;
	पूर्णांक page_count;

	काष्ठा page **page_array;
	काष्ठा orangefs_bufmap_desc *desc_array;

	/* array to track usage of buffer descriptors */
	अचिन्हित दीर्घ *buffer_index_array;

	/* array to track usage of buffer descriptors क्रम सूची_पढ़ो */
#घोषणा N DIV_ROUND_UP(ORANGEFS_READसूची_DEFAULT_DESC_COUNT, BITS_PER_LONG)
	अचिन्हित दीर्घ सूची_पढ़ो_index_array[N];
#अघोषित N
पूर्ण *__orangefs_bufmap;

अटल DEFINE_SPINLOCK(orangefs_bufmap_lock);

अटल व्योम
orangefs_bufmap_unmap(काष्ठा orangefs_bufmap *bufmap)
अणु
	unpin_user_pages(bufmap->page_array, bufmap->page_count);
पूर्ण

अटल व्योम
orangefs_bufmap_मुक्त(काष्ठा orangefs_bufmap *bufmap)
अणु
	kमुक्त(bufmap->page_array);
	kमुक्त(bufmap->desc_array);
	kमुक्त(bufmap->buffer_index_array);
	kमुक्त(bufmap);
पूर्ण

/*
 * XXX: Can the size and shअगरt change जबतक the caller gives up the
 * XXX: lock between calling this and करोing something useful?
 */

पूर्णांक orangefs_bufmap_size_query(व्योम)
अणु
	काष्ठा orangefs_bufmap *bufmap;
	पूर्णांक size = 0;
	spin_lock(&orangefs_bufmap_lock);
	bufmap = __orangefs_bufmap;
	अगर (bufmap)
		size = bufmap->desc_size;
	spin_unlock(&orangefs_bufmap_lock);
	वापस size;
पूर्ण

पूर्णांक orangefs_bufmap_shअगरt_query(व्योम)
अणु
	काष्ठा orangefs_bufmap *bufmap;
	पूर्णांक shअगरt = 0;
	spin_lock(&orangefs_bufmap_lock);
	bufmap = __orangefs_bufmap;
	अगर (bufmap)
		shअगरt = bufmap->desc_shअगरt;
	spin_unlock(&orangefs_bufmap_lock);
	वापस shअगरt;
पूर्ण

अटल DECLARE_WAIT_QUEUE_HEAD(bufmap_रुकोq);
अटल DECLARE_WAIT_QUEUE_HEAD(सूची_पढ़ो_रुकोq);

अटल काष्ठा orangefs_bufmap *
orangefs_bufmap_alloc(काष्ठा ORANGEFS_dev_map_desc *user_desc)
अणु
	काष्ठा orangefs_bufmap *bufmap;

	bufmap = kzalloc(माप(*bufmap), GFP_KERNEL);
	अगर (!bufmap)
		जाओ out;

	bufmap->total_size = user_desc->total_size;
	bufmap->desc_count = user_desc->count;
	bufmap->desc_size = user_desc->size;
	bufmap->desc_shअगरt = ilog2(bufmap->desc_size);

	bufmap->buffer_index_array =
		kzalloc(DIV_ROUND_UP(bufmap->desc_count, BITS_PER_LONG), GFP_KERNEL);
	अगर (!bufmap->buffer_index_array)
		जाओ out_मुक्त_bufmap;

	bufmap->desc_array =
		kसुस्मृति(bufmap->desc_count, माप(काष्ठा orangefs_bufmap_desc),
			GFP_KERNEL);
	अगर (!bufmap->desc_array)
		जाओ out_मुक्त_index_array;

	bufmap->page_count = bufmap->total_size / PAGE_SIZE;

	/* allocate storage to track our page mappings */
	bufmap->page_array =
		kसुस्मृति(bufmap->page_count, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!bufmap->page_array)
		जाओ out_मुक्त_desc_array;

	वापस bufmap;

out_मुक्त_desc_array:
	kमुक्त(bufmap->desc_array);
out_मुक्त_index_array:
	kमुक्त(bufmap->buffer_index_array);
out_मुक्त_bufmap:
	kमुक्त(bufmap);
out:
	वापस शून्य;
पूर्ण

अटल पूर्णांक
orangefs_bufmap_map(काष्ठा orangefs_bufmap *bufmap,
		काष्ठा ORANGEFS_dev_map_desc *user_desc)
अणु
	पूर्णांक pages_per_desc = bufmap->desc_size / PAGE_SIZE;
	पूर्णांक offset = 0, ret, i;

	/* map the pages */
	ret = pin_user_pages_fast((अचिन्हित दीर्घ)user_desc->ptr,
			     bufmap->page_count, FOLL_WRITE, bufmap->page_array);

	अगर (ret < 0)
		वापस ret;

	अगर (ret != bufmap->page_count) अणु
		gossip_err("orangefs error: asked for %d pages, only got %d.\n",
				bufmap->page_count, ret);

		क्रम (i = 0; i < ret; i++) अणु
			SetPageError(bufmap->page_array[i]);
			unpin_user_page(bufmap->page_array[i]);
		पूर्ण
		वापस -ENOMEM;
	पूर्ण

	/*
	 * ideally we want to get kernel space poपूर्णांकers क्रम each page, but
	 * we can't kmap that many pages at once अगर highmem is being used.
	 * so instead, we just kmap/kunmap the page address each समय the
	 * kaddr is needed.
	 */
	क्रम (i = 0; i < bufmap->page_count; i++)
		flush_dcache_page(bufmap->page_array[i]);

	/* build a list of available descriptors */
	क्रम (offset = 0, i = 0; i < bufmap->desc_count; i++) अणु
		bufmap->desc_array[i].page_array = &bufmap->page_array[offset];
		bufmap->desc_array[i].array_count = pages_per_desc;
		bufmap->desc_array[i].uaddr =
		    (user_desc->ptr + (i * pages_per_desc * PAGE_SIZE));
		offset += pages_per_desc;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * orangefs_bufmap_initialize()
 *
 * initializes the mapped buffer पूर्णांकerface
 *
 * वापसs 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक orangefs_bufmap_initialize(काष्ठा ORANGEFS_dev_map_desc *user_desc)
अणु
	काष्ठा orangefs_bufmap *bufmap;
	पूर्णांक ret = -EINVAL;

	gossip_debug(GOSSIP_BUFMAP_DEBUG,
		     "orangefs_bufmap_initialize: called (ptr ("
		     "%p) sz (%d) cnt(%d).\n",
		     user_desc->ptr,
		     user_desc->size,
		     user_desc->count);

	अगर (user_desc->total_size < 0 ||
	    user_desc->size < 0 ||
	    user_desc->count < 0)
		जाओ out;

	/*
	 * sanity check alignment and size of buffer that caller wants to
	 * work with
	 */
	अगर (PAGE_ALIGN((अचिन्हित दीर्घ)user_desc->ptr) !=
	    (अचिन्हित दीर्घ)user_desc->ptr) अणु
		gossip_err("orangefs error: memory alignment (front). %p\n",
			   user_desc->ptr);
		जाओ out;
	पूर्ण

	अगर (PAGE_ALIGN(((अचिन्हित दीर्घ)user_desc->ptr + user_desc->total_size))
	    != (अचिन्हित दीर्घ)(user_desc->ptr + user_desc->total_size)) अणु
		gossip_err("orangefs error: memory alignment (back).(%p + %d)\n",
			   user_desc->ptr,
			   user_desc->total_size);
		जाओ out;
	पूर्ण

	अगर (user_desc->total_size != (user_desc->size * user_desc->count)) अणु
		gossip_err("orangefs error: user provided an oddly sized buffer: (%d, %d, %d)\n",
			   user_desc->total_size,
			   user_desc->size,
			   user_desc->count);
		जाओ out;
	पूर्ण

	अगर ((user_desc->size % PAGE_SIZE) != 0) अणु
		gossip_err("orangefs error: bufmap size not page size divisible (%d).\n",
			   user_desc->size);
		जाओ out;
	पूर्ण

	ret = -ENOMEM;
	bufmap = orangefs_bufmap_alloc(user_desc);
	अगर (!bufmap)
		जाओ out;

	ret = orangefs_bufmap_map(bufmap, user_desc);
	अगर (ret)
		जाओ out_मुक्त_bufmap;


	spin_lock(&orangefs_bufmap_lock);
	अगर (__orangefs_bufmap) अणु
		spin_unlock(&orangefs_bufmap_lock);
		gossip_err("orangefs: error: bufmap already initialized.\n");
		ret = -EINVAL;
		जाओ out_unmap_bufmap;
	पूर्ण
	__orangefs_bufmap = bufmap;
	install(&rw_map,
		bufmap->desc_count,
		bufmap->buffer_index_array);
	install(&सूची_पढ़ो_map,
		ORANGEFS_READसूची_DEFAULT_DESC_COUNT,
		bufmap->सूची_पढ़ो_index_array);
	spin_unlock(&orangefs_bufmap_lock);

	gossip_debug(GOSSIP_BUFMAP_DEBUG,
		     "orangefs_bufmap_initialize: exiting normally\n");
	वापस 0;

out_unmap_bufmap:
	orangefs_bufmap_unmap(bufmap);
out_मुक्त_bufmap:
	orangefs_bufmap_मुक्त(bufmap);
out:
	वापस ret;
पूर्ण

/*
 * orangefs_bufmap_finalize()
 *
 * shuts करोwn the mapped buffer पूर्णांकerface and releases any resources
 * associated with it
 *
 * no वापस value
 */
व्योम orangefs_bufmap_finalize(व्योम)
अणु
	काष्ठा orangefs_bufmap *bufmap = __orangefs_bufmap;
	अगर (!bufmap)
		वापस;
	gossip_debug(GOSSIP_BUFMAP_DEBUG, "orangefs_bufmap_finalize: called\n");
	mark_समाप्तed(&rw_map);
	mark_समाप्तed(&सूची_पढ़ो_map);
	gossip_debug(GOSSIP_BUFMAP_DEBUG,
		     "orangefs_bufmap_finalize: exiting normally\n");
पूर्ण

व्योम orangefs_bufmap_run_करोwn(व्योम)
अणु
	काष्ठा orangefs_bufmap *bufmap = __orangefs_bufmap;
	अगर (!bufmap)
		वापस;
	run_करोwn(&rw_map);
	run_करोwn(&सूची_पढ़ो_map);
	spin_lock(&orangefs_bufmap_lock);
	__orangefs_bufmap = शून्य;
	spin_unlock(&orangefs_bufmap_lock);
	orangefs_bufmap_unmap(bufmap);
	orangefs_bufmap_मुक्त(bufmap);
पूर्ण

/*
 * orangefs_bufmap_get()
 *
 * माला_लो a मुक्त mapped buffer descriptor, will sleep until one becomes
 * available अगर necessary
 *
 * वापसs slot on success, -त्रुटि_सं on failure
 */
पूर्णांक orangefs_bufmap_get(व्योम)
अणु
	वापस get(&rw_map);
पूर्ण

/*
 * orangefs_bufmap_put()
 *
 * वापसs a mapped buffer descriptor to the collection
 *
 * no वापस value
 */
व्योम orangefs_bufmap_put(पूर्णांक buffer_index)
अणु
	put(&rw_map, buffer_index);
पूर्ण

/*
 * orangefs_सूची_पढ़ो_index_get()
 *
 * माला_लो a मुक्त descriptor, will sleep until one becomes
 * available अगर necessary.
 * Although the सूची_पढ़ो buffers are not mapped पूर्णांकo kernel space
 * we could करो that at a later poपूर्णांक of समय. Regardless, these
 * indices are used by the client-core.
 *
 * वापसs slot on success, -त्रुटि_सं on failure
 */
पूर्णांक orangefs_सूची_पढ़ो_index_get(व्योम)
अणु
	वापस get(&सूची_पढ़ो_map);
पूर्ण

व्योम orangefs_सूची_पढ़ो_index_put(पूर्णांक buffer_index)
अणु
	put(&सूची_पढ़ो_map, buffer_index);
पूर्ण

/*
 * we've been handed an iovec, we need to copy it to
 * the shared memory descriptor at "buffer_index".
 */
पूर्णांक orangefs_bufmap_copy_from_iovec(काष्ठा iov_iter *iter,
				पूर्णांक buffer_index,
				माप_प्रकार size)
अणु
	काष्ठा orangefs_bufmap_desc *to;
	पूर्णांक i;

	gossip_debug(GOSSIP_BUFMAP_DEBUG,
		     "%s: buffer_index:%d: size:%zu:\n",
		     __func__, buffer_index, size);

	to = &__orangefs_bufmap->desc_array[buffer_index];
	क्रम (i = 0; size; i++) अणु
		काष्ठा page *page = to->page_array[i];
		माप_प्रकार n = size;
		अगर (n > PAGE_SIZE)
			n = PAGE_SIZE;
		अगर (copy_page_from_iter(page, 0, n, iter) != n)
			वापस -EFAULT;
		size -= n;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * we've been handed an iovec, we need to fill it from
 * the shared memory descriptor at "buffer_index".
 */
पूर्णांक orangefs_bufmap_copy_to_iovec(काष्ठा iov_iter *iter,
				    पूर्णांक buffer_index,
				    माप_प्रकार size)
अणु
	काष्ठा orangefs_bufmap_desc *from;
	पूर्णांक i;

	from = &__orangefs_bufmap->desc_array[buffer_index];
	gossip_debug(GOSSIP_BUFMAP_DEBUG,
		     "%s: buffer_index:%d: size:%zu:\n",
		     __func__, buffer_index, size);


	क्रम (i = 0; size; i++) अणु
		काष्ठा page *page = from->page_array[i];
		माप_प्रकार n = size;
		अगर (n > PAGE_SIZE)
			n = PAGE_SIZE;
		n = copy_page_to_iter(page, 0, n, iter);
		अगर (!n)
			वापस -EFAULT;
		size -= n;
	पूर्ण
	वापस 0;
पूर्ण

व्योम orangefs_bufmap_page_fill(व्योम *page_to,
				पूर्णांक buffer_index,
				पूर्णांक slot_index)
अणु
	काष्ठा orangefs_bufmap_desc *from;
	व्योम *page_from;

	from = &__orangefs_bufmap->desc_array[buffer_index];
	page_from = kmap_atomic(from->page_array[slot_index]);
	स_नकल(page_to, page_from, PAGE_SIZE);
	kunmap_atomic(page_from);
पूर्ण
