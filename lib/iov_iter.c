<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <crypto/hash.h>
#समावेश <linux/export.h>
#समावेश <linux/bvec.h>
#समावेश <linux/fault-inject-usercopy.h>
#समावेश <linux/uपन.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/splice.h>
#समावेश <linux/compat.h>
#समावेश <net/checksum.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/instrumented.h>

#घोषणा PIPE_PARANOIA /* क्रम now */

#घोषणा iterate_iovec(i, n, __v, __p, skip, STEP) अणु	\
	माप_प्रकार left;					\
	माप_प्रकार wanted = n;				\
	__p = i->iov;					\
	__v.iov_len = min(n, __p->iov_len - skip);	\
	अगर (likely(__v.iov_len)) अणु			\
		__v.iov_base = __p->iov_base + skip;	\
		left = (STEP);				\
		__v.iov_len -= left;			\
		skip += __v.iov_len;			\
		n -= __v.iov_len;			\
	पूर्ण अन्यथा अणु					\
		left = 0;				\
	पूर्ण						\
	जबतक (unlikely(!left && n)) अणु			\
		__p++;					\
		__v.iov_len = min(n, __p->iov_len);	\
		अगर (unlikely(!__v.iov_len))		\
			जारी;			\
		__v.iov_base = __p->iov_base;		\
		left = (STEP);				\
		__v.iov_len -= left;			\
		skip = __v.iov_len;			\
		n -= __v.iov_len;			\
	पूर्ण						\
	n = wanted - n;					\
पूर्ण

#घोषणा iterate_kvec(i, n, __v, __p, skip, STEP) अणु	\
	माप_प्रकार wanted = n;				\
	__p = i->kvec;					\
	__v.iov_len = min(n, __p->iov_len - skip);	\
	अगर (likely(__v.iov_len)) अणु			\
		__v.iov_base = __p->iov_base + skip;	\
		(व्योम)(STEP);				\
		skip += __v.iov_len;			\
		n -= __v.iov_len;			\
	पूर्ण						\
	जबतक (unlikely(n)) अणु				\
		__p++;					\
		__v.iov_len = min(n, __p->iov_len);	\
		अगर (unlikely(!__v.iov_len))		\
			जारी;			\
		__v.iov_base = __p->iov_base;		\
		(व्योम)(STEP);				\
		skip = __v.iov_len;			\
		n -= __v.iov_len;			\
	पूर्ण						\
	n = wanted;					\
पूर्ण

#घोषणा iterate_bvec(i, n, __v, __bi, skip, STEP) अणु	\
	काष्ठा bvec_iter __start;			\
	__start.bi_size = n;				\
	__start.bi_bvec_करोne = skip;			\
	__start.bi_idx = 0;				\
	क्रम_each_bvec(__v, i->bvec, __bi, __start) अणु	\
		(व्योम)(STEP);				\
	पूर्ण						\
पूर्ण

#घोषणा iterate_xarray(i, n, __v, skip, STEP) अणु		\
	काष्ठा page *head = शून्य;				\
	माप_प्रकार wanted = n, seg, offset;				\
	loff_t start = i->xarray_start + skip;			\
	pgoff_t index = start >> PAGE_SHIFT;			\
	पूर्णांक j;							\
								\
	XA_STATE(xas, i->xarray, index);			\
								\
	rcu_पढ़ो_lock();						\
	xas_क्रम_each(&xas, head, अच_दीर्घ_उच्च) अणु				\
		अगर (xas_retry(&xas, head))				\
			जारी;					\
		अगर (WARN_ON(xa_is_value(head)))				\
			अवरोध;						\
		अगर (WARN_ON(PageHuge(head)))				\
			अवरोध;						\
		क्रम (j = (head->index < index) ? index - head->index : 0; \
		     j < thp_nr_pages(head); j++) अणु			\
			__v.bv_page = head + j;				\
			offset = (i->xarray_start + skip) & ~PAGE_MASK;	\
			seg = PAGE_SIZE - offset;			\
			__v.bv_offset = offset;				\
			__v.bv_len = min(n, seg);			\
			(व्योम)(STEP);					\
			n -= __v.bv_len;				\
			skip += __v.bv_len;				\
			अगर (n == 0)					\
				अवरोध;					\
		पूर्ण							\
		अगर (n == 0)						\
			अवरोध;						\
	पूर्ण							\
	rcu_पढ़ो_unlock();					\
	n = wanted - n;						\
पूर्ण

#घोषणा iterate_all_kinds(i, n, v, I, B, K, X) अणु		\
	अगर (likely(n)) अणु					\
		माप_प्रकार skip = i->iov_offset;			\
		अगर (unlikely(i->type & ITER_BVEC)) अणु		\
			काष्ठा bio_vec v;			\
			काष्ठा bvec_iter __bi;			\
			iterate_bvec(i, n, v, __bi, skip, (B))	\
		पूर्ण अन्यथा अगर (unlikely(i->type & ITER_KVEC)) अणु	\
			स्थिर काष्ठा kvec *kvec;		\
			काष्ठा kvec v;				\
			iterate_kvec(i, n, v, kvec, skip, (K))	\
		पूर्ण अन्यथा अगर (unlikely(i->type & ITER_DISCARD)) अणु	\
		पूर्ण अन्यथा अगर (unlikely(i->type & ITER_XARRAY)) अणु	\
			काष्ठा bio_vec v;			\
			iterate_xarray(i, n, v, skip, (X));	\
		पूर्ण अन्यथा अणु					\
			स्थिर काष्ठा iovec *iov;		\
			काष्ठा iovec v;				\
			iterate_iovec(i, n, v, iov, skip, (I))	\
		पूर्ण						\
	पूर्ण							\
पूर्ण

#घोषणा iterate_and_advance(i, n, v, I, B, K, X) अणु		\
	अगर (unlikely(i->count < n))				\
		n = i->count;					\
	अगर (i->count) अणु						\
		माप_प्रकार skip = i->iov_offset;			\
		अगर (unlikely(i->type & ITER_BVEC)) अणु		\
			स्थिर काष्ठा bio_vec *bvec = i->bvec;	\
			काष्ठा bio_vec v;			\
			काष्ठा bvec_iter __bi;			\
			iterate_bvec(i, n, v, __bi, skip, (B))	\
			i->bvec = __bvec_iter_bvec(i->bvec, __bi);	\
			i->nr_segs -= i->bvec - bvec;		\
			skip = __bi.bi_bvec_करोne;		\
		पूर्ण अन्यथा अगर (unlikely(i->type & ITER_KVEC)) अणु	\
			स्थिर काष्ठा kvec *kvec;		\
			काष्ठा kvec v;				\
			iterate_kvec(i, n, v, kvec, skip, (K))	\
			अगर (skip == kvec->iov_len) अणु		\
				kvec++;				\
				skip = 0;			\
			पूर्ण					\
			i->nr_segs -= kvec - i->kvec;		\
			i->kvec = kvec;				\
		पूर्ण अन्यथा अगर (unlikely(i->type & ITER_DISCARD)) अणु	\
			skip += n;				\
		पूर्ण अन्यथा अगर (unlikely(i->type & ITER_XARRAY)) अणु	\
			काष्ठा bio_vec v;			\
			iterate_xarray(i, n, v, skip, (X))	\
		पूर्ण अन्यथा अणु					\
			स्थिर काष्ठा iovec *iov;		\
			काष्ठा iovec v;				\
			iterate_iovec(i, n, v, iov, skip, (I))	\
			अगर (skip == iov->iov_len) अणु		\
				iov++;				\
				skip = 0;			\
			पूर्ण					\
			i->nr_segs -= iov - i->iov;		\
			i->iov = iov;				\
		पूर्ण						\
		i->count -= n;					\
		i->iov_offset = skip;				\
	पूर्ण							\
पूर्ण

अटल पूर्णांक copyout(व्योम __user *to, स्थिर व्योम *from, माप_प्रकार n)
अणु
	अगर (should_fail_usercopy())
		वापस n;
	अगर (access_ok(to, n)) अणु
		instrument_copy_to_user(to, from, n);
		n = raw_copy_to_user(to, from, n);
	पूर्ण
	वापस n;
पूर्ण

अटल पूर्णांक copyin(व्योम *to, स्थिर व्योम __user *from, माप_प्रकार n)
अणु
	अगर (should_fail_usercopy())
		वापस n;
	अगर (access_ok(from, n)) अणु
		instrument_copy_from_user(to, from, n);
		n = raw_copy_from_user(to, from, n);
	पूर्ण
	वापस n;
पूर्ण

अटल माप_प्रकार copy_page_to_iter_iovec(काष्ठा page *page, माप_प्रकार offset, माप_प्रकार bytes,
			 काष्ठा iov_iter *i)
अणु
	माप_प्रकार skip, copy, left, wanted;
	स्थिर काष्ठा iovec *iov;
	अक्षर __user *buf;
	व्योम *kaddr, *from;

	अगर (unlikely(bytes > i->count))
		bytes = i->count;

	अगर (unlikely(!bytes))
		वापस 0;

	might_fault();
	wanted = bytes;
	iov = i->iov;
	skip = i->iov_offset;
	buf = iov->iov_base + skip;
	copy = min(bytes, iov->iov_len - skip);

	अगर (IS_ENABLED(CONFIG_HIGHMEM) && !fault_in_pages_ग_लिखोable(buf, copy)) अणु
		kaddr = kmap_atomic(page);
		from = kaddr + offset;

		/* first chunk, usually the only one */
		left = copyout(buf, from, copy);
		copy -= left;
		skip += copy;
		from += copy;
		bytes -= copy;

		जबतक (unlikely(!left && bytes)) अणु
			iov++;
			buf = iov->iov_base;
			copy = min(bytes, iov->iov_len);
			left = copyout(buf, from, copy);
			copy -= left;
			skip = copy;
			from += copy;
			bytes -= copy;
		पूर्ण
		अगर (likely(!bytes)) अणु
			kunmap_atomic(kaddr);
			जाओ करोne;
		पूर्ण
		offset = from - kaddr;
		buf += copy;
		kunmap_atomic(kaddr);
		copy = min(bytes, iov->iov_len - skip);
	पूर्ण
	/* Too bad - revert to non-atomic kmap */

	kaddr = kmap(page);
	from = kaddr + offset;
	left = copyout(buf, from, copy);
	copy -= left;
	skip += copy;
	from += copy;
	bytes -= copy;
	जबतक (unlikely(!left && bytes)) अणु
		iov++;
		buf = iov->iov_base;
		copy = min(bytes, iov->iov_len);
		left = copyout(buf, from, copy);
		copy -= left;
		skip = copy;
		from += copy;
		bytes -= copy;
	पूर्ण
	kunmap(page);

करोne:
	अगर (skip == iov->iov_len) अणु
		iov++;
		skip = 0;
	पूर्ण
	i->count -= wanted - bytes;
	i->nr_segs -= iov - i->iov;
	i->iov = iov;
	i->iov_offset = skip;
	वापस wanted - bytes;
पूर्ण

अटल माप_प्रकार copy_page_from_iter_iovec(काष्ठा page *page, माप_प्रकार offset, माप_प्रकार bytes,
			 काष्ठा iov_iter *i)
अणु
	माप_प्रकार skip, copy, left, wanted;
	स्थिर काष्ठा iovec *iov;
	अक्षर __user *buf;
	व्योम *kaddr, *to;

	अगर (unlikely(bytes > i->count))
		bytes = i->count;

	अगर (unlikely(!bytes))
		वापस 0;

	might_fault();
	wanted = bytes;
	iov = i->iov;
	skip = i->iov_offset;
	buf = iov->iov_base + skip;
	copy = min(bytes, iov->iov_len - skip);

	अगर (IS_ENABLED(CONFIG_HIGHMEM) && !fault_in_pages_पढ़ोable(buf, copy)) अणु
		kaddr = kmap_atomic(page);
		to = kaddr + offset;

		/* first chunk, usually the only one */
		left = copyin(to, buf, copy);
		copy -= left;
		skip += copy;
		to += copy;
		bytes -= copy;

		जबतक (unlikely(!left && bytes)) अणु
			iov++;
			buf = iov->iov_base;
			copy = min(bytes, iov->iov_len);
			left = copyin(to, buf, copy);
			copy -= left;
			skip = copy;
			to += copy;
			bytes -= copy;
		पूर्ण
		अगर (likely(!bytes)) अणु
			kunmap_atomic(kaddr);
			जाओ करोne;
		पूर्ण
		offset = to - kaddr;
		buf += copy;
		kunmap_atomic(kaddr);
		copy = min(bytes, iov->iov_len - skip);
	पूर्ण
	/* Too bad - revert to non-atomic kmap */

	kaddr = kmap(page);
	to = kaddr + offset;
	left = copyin(to, buf, copy);
	copy -= left;
	skip += copy;
	to += copy;
	bytes -= copy;
	जबतक (unlikely(!left && bytes)) अणु
		iov++;
		buf = iov->iov_base;
		copy = min(bytes, iov->iov_len);
		left = copyin(to, buf, copy);
		copy -= left;
		skip = copy;
		to += copy;
		bytes -= copy;
	पूर्ण
	kunmap(page);

करोne:
	अगर (skip == iov->iov_len) अणु
		iov++;
		skip = 0;
	पूर्ण
	i->count -= wanted - bytes;
	i->nr_segs -= iov - i->iov;
	i->iov = iov;
	i->iov_offset = skip;
	वापस wanted - bytes;
पूर्ण

#अगर_घोषित PIPE_PARANOIA
अटल bool sanity(स्थिर काष्ठा iov_iter *i)
अणु
	काष्ठा pipe_inode_info *pipe = i->pipe;
	अचिन्हित पूर्णांक p_head = pipe->head;
	अचिन्हित पूर्णांक p_tail = pipe->tail;
	अचिन्हित पूर्णांक p_mask = pipe->ring_size - 1;
	अचिन्हित पूर्णांक p_occupancy = pipe_occupancy(p_head, p_tail);
	अचिन्हित पूर्णांक i_head = i->head;
	अचिन्हित पूर्णांक idx;

	अगर (i->iov_offset) अणु
		काष्ठा pipe_buffer *p;
		अगर (unlikely(p_occupancy == 0))
			जाओ Bad;	// pipe must be non-empty
		अगर (unlikely(i_head != p_head - 1))
			जाओ Bad;	// must be at the last buffer...

		p = &pipe->bufs[i_head & p_mask];
		अगर (unlikely(p->offset + p->len != i->iov_offset))
			जाओ Bad;	// ... at the end of segment
	पूर्ण अन्यथा अणु
		अगर (i_head != p_head)
			जाओ Bad;	// must be right after the last buffer
	पूर्ण
	वापस true;
Bad:
	prपूर्णांकk(KERN_ERR "idx = %d, offset = %zd\n", i_head, i->iov_offset);
	prपूर्णांकk(KERN_ERR "head = %d, tail = %d, buffers = %d\n",
			p_head, p_tail, pipe->ring_size);
	क्रम (idx = 0; idx < pipe->ring_size; idx++)
		prपूर्णांकk(KERN_ERR "[%p %p %d %d]\n",
			pipe->bufs[idx].ops,
			pipe->bufs[idx].page,
			pipe->bufs[idx].offset,
			pipe->bufs[idx].len);
	WARN_ON(1);
	वापस false;
पूर्ण
#अन्यथा
#घोषणा sanity(i) true
#पूर्ण_अगर

अटल माप_प्रकार copy_page_to_iter_pipe(काष्ठा page *page, माप_प्रकार offset, माप_प्रकार bytes,
			 काष्ठा iov_iter *i)
अणु
	काष्ठा pipe_inode_info *pipe = i->pipe;
	काष्ठा pipe_buffer *buf;
	अचिन्हित पूर्णांक p_tail = pipe->tail;
	अचिन्हित पूर्णांक p_mask = pipe->ring_size - 1;
	अचिन्हित पूर्णांक i_head = i->head;
	माप_प्रकार off;

	अगर (unlikely(bytes > i->count))
		bytes = i->count;

	अगर (unlikely(!bytes))
		वापस 0;

	अगर (!sanity(i))
		वापस 0;

	off = i->iov_offset;
	buf = &pipe->bufs[i_head & p_mask];
	अगर (off) अणु
		अगर (offset == off && buf->page == page) अणु
			/* merge with the last one */
			buf->len += bytes;
			i->iov_offset += bytes;
			जाओ out;
		पूर्ण
		i_head++;
		buf = &pipe->bufs[i_head & p_mask];
	पूर्ण
	अगर (pipe_full(i_head, p_tail, pipe->max_usage))
		वापस 0;

	buf->ops = &page_cache_pipe_buf_ops;
	get_page(page);
	buf->page = page;
	buf->offset = offset;
	buf->len = bytes;

	pipe->head = i_head + 1;
	i->iov_offset = offset + bytes;
	i->head = i_head;
out:
	i->count -= bytes;
	वापस bytes;
पूर्ण

/*
 * Fault in one or more iovecs of the given iov_iter, to a maximum length of
 * bytes.  For each iovec, fault in each page that स्थिरitutes the iovec.
 *
 * Return 0 on success, or non-zero अगर the memory could not be accessed (i.e.
 * because it is an invalid address).
 */
पूर्णांक iov_iter_fault_in_पढ़ोable(काष्ठा iov_iter *i, माप_प्रकार bytes)
अणु
	माप_प्रकार skip = i->iov_offset;
	स्थिर काष्ठा iovec *iov;
	पूर्णांक err;
	काष्ठा iovec v;

	अगर (!(i->type & (ITER_BVEC|ITER_KVEC))) अणु
		iterate_iovec(i, bytes, v, iov, skip, (अणु
			err = fault_in_pages_पढ़ोable(v.iov_base, v.iov_len);
			अगर (unlikely(err))
			वापस err;
		0;पूर्ण))
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(iov_iter_fault_in_पढ़ोable);

व्योम iov_iter_init(काष्ठा iov_iter *i, अचिन्हित पूर्णांक direction,
			स्थिर काष्ठा iovec *iov, अचिन्हित दीर्घ nr_segs,
			माप_प्रकार count)
अणु
	WARN_ON(direction & ~(READ | WRITE));
	direction &= READ | WRITE;

	/* It will get better.  Eventually... */
	अगर (uaccess_kernel()) अणु
		i->type = ITER_KVEC | direction;
		i->kvec = (काष्ठा kvec *)iov;
	पूर्ण अन्यथा अणु
		i->type = ITER_IOVEC | direction;
		i->iov = iov;
	पूर्ण
	i->nr_segs = nr_segs;
	i->iov_offset = 0;
	i->count = count;
पूर्ण
EXPORT_SYMBOL(iov_iter_init);

अटल अंतरभूत bool allocated(काष्ठा pipe_buffer *buf)
अणु
	वापस buf->ops == &शेष_pipe_buf_ops;
पूर्ण

अटल अंतरभूत व्योम data_start(स्थिर काष्ठा iov_iter *i,
			      अचिन्हित पूर्णांक *iter_headp, माप_प्रकार *offp)
अणु
	अचिन्हित पूर्णांक p_mask = i->pipe->ring_size - 1;
	अचिन्हित पूर्णांक iter_head = i->head;
	माप_प्रकार off = i->iov_offset;

	अगर (off && (!allocated(&i->pipe->bufs[iter_head & p_mask]) ||
		    off == PAGE_SIZE)) अणु
		iter_head++;
		off = 0;
	पूर्ण
	*iter_headp = iter_head;
	*offp = off;
पूर्ण

अटल माप_प्रकार push_pipe(काष्ठा iov_iter *i, माप_प्रकार size,
			पूर्णांक *iter_headp, माप_प्रकार *offp)
अणु
	काष्ठा pipe_inode_info *pipe = i->pipe;
	अचिन्हित पूर्णांक p_tail = pipe->tail;
	अचिन्हित पूर्णांक p_mask = pipe->ring_size - 1;
	अचिन्हित पूर्णांक iter_head;
	माप_प्रकार off;
	sमाप_प्रकार left;

	अगर (unlikely(size > i->count))
		size = i->count;
	अगर (unlikely(!size))
		वापस 0;

	left = size;
	data_start(i, &iter_head, &off);
	*iter_headp = iter_head;
	*offp = off;
	अगर (off) अणु
		left -= PAGE_SIZE - off;
		अगर (left <= 0) अणु
			pipe->bufs[iter_head & p_mask].len += size;
			वापस size;
		पूर्ण
		pipe->bufs[iter_head & p_mask].len = PAGE_SIZE;
		iter_head++;
	पूर्ण
	जबतक (!pipe_full(iter_head, p_tail, pipe->max_usage)) अणु
		काष्ठा pipe_buffer *buf = &pipe->bufs[iter_head & p_mask];
		काष्ठा page *page = alloc_page(GFP_USER);
		अगर (!page)
			अवरोध;

		buf->ops = &शेष_pipe_buf_ops;
		buf->page = page;
		buf->offset = 0;
		buf->len = min_t(sमाप_प्रकार, left, PAGE_SIZE);
		left -= buf->len;
		iter_head++;
		pipe->head = iter_head;

		अगर (left == 0)
			वापस size;
	पूर्ण
	वापस size - left;
पूर्ण

अटल माप_प्रकार copy_pipe_to_iter(स्थिर व्योम *addr, माप_प्रकार bytes,
				काष्ठा iov_iter *i)
अणु
	काष्ठा pipe_inode_info *pipe = i->pipe;
	अचिन्हित पूर्णांक p_mask = pipe->ring_size - 1;
	अचिन्हित पूर्णांक i_head;
	माप_प्रकार n, off;

	अगर (!sanity(i))
		वापस 0;

	bytes = n = push_pipe(i, bytes, &i_head, &off);
	अगर (unlikely(!n))
		वापस 0;
	करो अणु
		माप_प्रकार chunk = min_t(माप_प्रकार, n, PAGE_SIZE - off);
		स_नकल_to_page(pipe->bufs[i_head & p_mask].page, off, addr, chunk);
		i->head = i_head;
		i->iov_offset = off + chunk;
		n -= chunk;
		addr += chunk;
		off = 0;
		i_head++;
	पूर्ण जबतक (n);
	i->count -= bytes;
	वापस bytes;
पूर्ण

अटल __wsum csum_and_स_नकल(व्योम *to, स्थिर व्योम *from, माप_प्रकार len,
			      __wsum sum, माप_प्रकार off)
अणु
	__wsum next = csum_partial_copy_nocheck(from, to, len);
	वापस csum_block_add(sum, next, off);
पूर्ण

अटल माप_प्रकार csum_and_copy_to_pipe_iter(स्थिर व्योम *addr, माप_प्रकार bytes,
					 काष्ठा csum_state *csstate,
					 काष्ठा iov_iter *i)
अणु
	काष्ठा pipe_inode_info *pipe = i->pipe;
	अचिन्हित पूर्णांक p_mask = pipe->ring_size - 1;
	__wsum sum = csstate->csum;
	माप_प्रकार off = csstate->off;
	अचिन्हित पूर्णांक i_head;
	माप_प्रकार n, r;

	अगर (!sanity(i))
		वापस 0;

	bytes = n = push_pipe(i, bytes, &i_head, &r);
	अगर (unlikely(!n))
		वापस 0;
	करो अणु
		माप_प्रकार chunk = min_t(माप_प्रकार, n, PAGE_SIZE - r);
		अक्षर *p = kmap_atomic(pipe->bufs[i_head & p_mask].page);
		sum = csum_and_स_नकल(p + r, addr, chunk, sum, off);
		kunmap_atomic(p);
		i->head = i_head;
		i->iov_offset = r + chunk;
		n -= chunk;
		off += chunk;
		addr += chunk;
		r = 0;
		i_head++;
	पूर्ण जबतक (n);
	i->count -= bytes;
	csstate->csum = sum;
	csstate->off = off;
	वापस bytes;
पूर्ण

माप_प्रकार _copy_to_iter(स्थिर व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	स्थिर अक्षर *from = addr;
	अगर (unlikely(iov_iter_is_pipe(i)))
		वापस copy_pipe_to_iter(addr, bytes, i);
	अगर (iter_is_iovec(i))
		might_fault();
	iterate_and_advance(i, bytes, v,
		copyout(v.iov_base, (from += v.iov_len) - v.iov_len, v.iov_len),
		स_नकल_to_page(v.bv_page, v.bv_offset,
			       (from += v.bv_len) - v.bv_len, v.bv_len),
		स_नकल(v.iov_base, (from += v.iov_len) - v.iov_len, v.iov_len),
		स_नकल_to_page(v.bv_page, v.bv_offset,
			       (from += v.bv_len) - v.bv_len, v.bv_len)
	)

	वापस bytes;
पूर्ण
EXPORT_SYMBOL(_copy_to_iter);

#अगर_घोषित CONFIG_ARCH_HAS_COPY_MC
अटल पूर्णांक copyout_mc(व्योम __user *to, स्थिर व्योम *from, माप_प्रकार n)
अणु
	अगर (access_ok(to, n)) अणु
		instrument_copy_to_user(to, from, n);
		n = copy_mc_to_user((__क्रमce व्योम *) to, from, n);
	पूर्ण
	वापस n;
पूर्ण

अटल अचिन्हित दीर्घ copy_mc_to_page(काष्ठा page *page, माप_प्रकार offset,
		स्थिर अक्षर *from, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ ret;
	अक्षर *to;

	to = kmap_atomic(page);
	ret = copy_mc_to_kernel(to + offset, from, len);
	kunmap_atomic(to);

	वापस ret;
पूर्ण

अटल माप_प्रकार copy_mc_pipe_to_iter(स्थिर व्योम *addr, माप_प्रकार bytes,
				काष्ठा iov_iter *i)
अणु
	काष्ठा pipe_inode_info *pipe = i->pipe;
	अचिन्हित पूर्णांक p_mask = pipe->ring_size - 1;
	अचिन्हित पूर्णांक i_head;
	माप_प्रकार n, off, xfer = 0;

	अगर (!sanity(i))
		वापस 0;

	bytes = n = push_pipe(i, bytes, &i_head, &off);
	अगर (unlikely(!n))
		वापस 0;
	करो अणु
		माप_प्रकार chunk = min_t(माप_प्रकार, n, PAGE_SIZE - off);
		अचिन्हित दीर्घ rem;

		rem = copy_mc_to_page(pipe->bufs[i_head & p_mask].page,
					    off, addr, chunk);
		i->head = i_head;
		i->iov_offset = off + chunk - rem;
		xfer += chunk - rem;
		अगर (rem)
			अवरोध;
		n -= chunk;
		addr += chunk;
		off = 0;
		i_head++;
	पूर्ण जबतक (n);
	i->count -= xfer;
	वापस xfer;
पूर्ण

/**
 * _copy_mc_to_iter - copy to iter with source memory error exception handling
 * @addr: source kernel address
 * @bytes: total transfer length
 * @iter: destination iterator
 *
 * The pmem driver deploys this क्रम the dax operation
 * (dax_copy_to_iter()) क्रम dax पढ़ोs (bypass page-cache and the
 * block-layer). Upon #MC पढ़ो(2) पातs and वापसs EIO or the bytes
 * successfully copied.
 *
 * The मुख्य dअगरferences between this and typical _copy_to_iter().
 *
 * * Typical tail/residue handling after a fault retries the copy
 *   byte-by-byte until the fault happens again. Re-triggering machine
 *   checks is potentially fatal so the implementation uses source
 *   alignment and poison alignment assumptions to aव्योम re-triggering
 *   hardware exceptions.
 *
 * * ITER_KVEC, ITER_PIPE, and ITER_BVEC can वापस लघु copies.
 *   Compare to copy_to_iter() where only ITER_IOVEC attempts might वापस
 *   a लघु copy.
 */
माप_प्रकार _copy_mc_to_iter(स्थिर व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	स्थिर अक्षर *from = addr;
	अचिन्हित दीर्घ rem, curr_addr, s_addr = (अचिन्हित दीर्घ) addr;

	अगर (unlikely(iov_iter_is_pipe(i)))
		वापस copy_mc_pipe_to_iter(addr, bytes, i);
	अगर (iter_is_iovec(i))
		might_fault();
	iterate_and_advance(i, bytes, v,
		copyout_mc(v.iov_base, (from += v.iov_len) - v.iov_len,
			   v.iov_len),
		(अणु
		rem = copy_mc_to_page(v.bv_page, v.bv_offset,
				      (from += v.bv_len) - v.bv_len, v.bv_len);
		अगर (rem) अणु
			curr_addr = (अचिन्हित दीर्घ) from;
			bytes = curr_addr - s_addr - rem;
			वापस bytes;
		पूर्ण
		पूर्ण),
		(अणु
		rem = copy_mc_to_kernel(v.iov_base, (from += v.iov_len)
					- v.iov_len, v.iov_len);
		अगर (rem) अणु
			curr_addr = (अचिन्हित दीर्घ) from;
			bytes = curr_addr - s_addr - rem;
			वापस bytes;
		पूर्ण
		पूर्ण),
		(अणु
		rem = copy_mc_to_page(v.bv_page, v.bv_offset,
				      (from += v.bv_len) - v.bv_len, v.bv_len);
		अगर (rem) अणु
			curr_addr = (अचिन्हित दीर्घ) from;
			bytes = curr_addr - s_addr - rem;
			rcu_पढ़ो_unlock();
			i->iov_offset += bytes;
			i->count -= bytes;
			वापस bytes;
		पूर्ण
		पूर्ण)
	)

	वापस bytes;
पूर्ण
EXPORT_SYMBOL_GPL(_copy_mc_to_iter);
#पूर्ण_अगर /* CONFIG_ARCH_HAS_COPY_MC */

माप_प्रकार _copy_from_iter(व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	अक्षर *to = addr;
	अगर (unlikely(iov_iter_is_pipe(i))) अणु
		WARN_ON(1);
		वापस 0;
	पूर्ण
	अगर (iter_is_iovec(i))
		might_fault();
	iterate_and_advance(i, bytes, v,
		copyin((to += v.iov_len) - v.iov_len, v.iov_base, v.iov_len),
		स_नकल_from_page((to += v.bv_len) - v.bv_len, v.bv_page,
				 v.bv_offset, v.bv_len),
		स_नकल((to += v.iov_len) - v.iov_len, v.iov_base, v.iov_len),
		स_नकल_from_page((to += v.bv_len) - v.bv_len, v.bv_page,
				 v.bv_offset, v.bv_len)
	)

	वापस bytes;
पूर्ण
EXPORT_SYMBOL(_copy_from_iter);

bool _copy_from_iter_full(व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	अक्षर *to = addr;
	अगर (unlikely(iov_iter_is_pipe(i))) अणु
		WARN_ON(1);
		वापस false;
	पूर्ण
	अगर (unlikely(i->count < bytes))
		वापस false;

	अगर (iter_is_iovec(i))
		might_fault();
	iterate_all_kinds(i, bytes, v, (अणु
		अगर (copyin((to += v.iov_len) - v.iov_len,
				      v.iov_base, v.iov_len))
			वापस false;
		0;पूर्ण),
		स_नकल_from_page((to += v.bv_len) - v.bv_len, v.bv_page,
				 v.bv_offset, v.bv_len),
		स_नकल((to += v.iov_len) - v.iov_len, v.iov_base, v.iov_len),
		स_नकल_from_page((to += v.bv_len) - v.bv_len, v.bv_page,
				 v.bv_offset, v.bv_len)
	)

	iov_iter_advance(i, bytes);
	वापस true;
पूर्ण
EXPORT_SYMBOL(_copy_from_iter_full);

माप_प्रकार _copy_from_iter_nocache(व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	अक्षर *to = addr;
	अगर (unlikely(iov_iter_is_pipe(i))) अणु
		WARN_ON(1);
		वापस 0;
	पूर्ण
	iterate_and_advance(i, bytes, v,
		__copy_from_user_inatomic_nocache((to += v.iov_len) - v.iov_len,
					 v.iov_base, v.iov_len),
		स_नकल_from_page((to += v.bv_len) - v.bv_len, v.bv_page,
				 v.bv_offset, v.bv_len),
		स_नकल((to += v.iov_len) - v.iov_len, v.iov_base, v.iov_len),
		स_नकल_from_page((to += v.bv_len) - v.bv_len, v.bv_page,
				 v.bv_offset, v.bv_len)
	)

	वापस bytes;
पूर्ण
EXPORT_SYMBOL(_copy_from_iter_nocache);

#अगर_घोषित CONFIG_ARCH_HAS_UACCESS_FLUSHCACHE
/**
 * _copy_from_iter_flushcache - ग_लिखो destination through cpu cache
 * @addr: destination kernel address
 * @bytes: total transfer length
 * @iter: source iterator
 *
 * The pmem driver arranges क्रम fileप्रणाली-dax to use this facility via
 * dax_copy_from_iter() क्रम ensuring that ग_लिखोs to persistent memory
 * are flushed through the CPU cache. It is dअगरferentiated from
 * _copy_from_iter_nocache() in that guarantees all data is flushed क्रम
 * all iterator types. The _copy_from_iter_nocache() only attempts to
 * bypass the cache क्रम the ITER_IOVEC हाल, and on some archs may use
 * inकाष्ठाions that stअक्रम dirty-data in the cache.
 */
माप_प्रकार _copy_from_iter_flushcache(व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	अक्षर *to = addr;
	अगर (unlikely(iov_iter_is_pipe(i))) अणु
		WARN_ON(1);
		वापस 0;
	पूर्ण
	iterate_and_advance(i, bytes, v,
		__copy_from_user_flushcache((to += v.iov_len) - v.iov_len,
					 v.iov_base, v.iov_len),
		स_नकल_page_flushcache((to += v.bv_len) - v.bv_len, v.bv_page,
				 v.bv_offset, v.bv_len),
		स_नकल_flushcache((to += v.iov_len) - v.iov_len, v.iov_base,
			v.iov_len),
		स_नकल_page_flushcache((to += v.bv_len) - v.bv_len, v.bv_page,
				 v.bv_offset, v.bv_len)
	)

	वापस bytes;
पूर्ण
EXPORT_SYMBOL_GPL(_copy_from_iter_flushcache);
#पूर्ण_अगर

bool _copy_from_iter_full_nocache(व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	अक्षर *to = addr;
	अगर (unlikely(iov_iter_is_pipe(i))) अणु
		WARN_ON(1);
		वापस false;
	पूर्ण
	अगर (unlikely(i->count < bytes))
		वापस false;
	iterate_all_kinds(i, bytes, v, (अणु
		अगर (__copy_from_user_inatomic_nocache((to += v.iov_len) - v.iov_len,
					     v.iov_base, v.iov_len))
			वापस false;
		0;पूर्ण),
		स_नकल_from_page((to += v.bv_len) - v.bv_len, v.bv_page,
				 v.bv_offset, v.bv_len),
		स_नकल((to += v.iov_len) - v.iov_len, v.iov_base, v.iov_len),
		स_नकल_from_page((to += v.bv_len) - v.bv_len, v.bv_page,
				 v.bv_offset, v.bv_len)
	)

	iov_iter_advance(i, bytes);
	वापस true;
पूर्ण
EXPORT_SYMBOL(_copy_from_iter_full_nocache);

अटल अंतरभूत bool page_copy_sane(काष्ठा page *page, माप_प्रकार offset, माप_प्रकार n)
अणु
	काष्ठा page *head;
	माप_प्रकार v = n + offset;

	/*
	 * The general हाल needs to access the page order in order
	 * to compute the page size.
	 * However, we mostly deal with order-0 pages and thus can
	 * aव्योम a possible cache line miss क्रम requests that fit all
	 * page orders.
	 */
	अगर (n <= v && v <= PAGE_SIZE)
		वापस true;

	head = compound_head(page);
	v += (page - head) << PAGE_SHIFT;

	अगर (likely(n <= v && v <= (page_size(head))))
		वापस true;
	WARN_ON(1);
	वापस false;
पूर्ण

माप_प्रकार copy_page_to_iter(काष्ठा page *page, माप_प्रकार offset, माप_प्रकार bytes,
			 काष्ठा iov_iter *i)
अणु
	अगर (unlikely(!page_copy_sane(page, offset, bytes)))
		वापस 0;
	अगर (i->type & (ITER_BVEC | ITER_KVEC | ITER_XARRAY)) अणु
		व्योम *kaddr = kmap_atomic(page);
		माप_प्रकार wanted = copy_to_iter(kaddr + offset, bytes, i);
		kunmap_atomic(kaddr);
		वापस wanted;
	पूर्ण अन्यथा अगर (unlikely(iov_iter_is_discard(i)))
		वापस bytes;
	अन्यथा अगर (likely(!iov_iter_is_pipe(i)))
		वापस copy_page_to_iter_iovec(page, offset, bytes, i);
	अन्यथा
		वापस copy_page_to_iter_pipe(page, offset, bytes, i);
पूर्ण
EXPORT_SYMBOL(copy_page_to_iter);

माप_प्रकार copy_page_from_iter(काष्ठा page *page, माप_प्रकार offset, माप_प्रकार bytes,
			 काष्ठा iov_iter *i)
अणु
	अगर (unlikely(!page_copy_sane(page, offset, bytes)))
		वापस 0;
	अगर (unlikely(iov_iter_is_pipe(i) || iov_iter_is_discard(i))) अणु
		WARN_ON(1);
		वापस 0;
	पूर्ण
	अगर (i->type & (ITER_BVEC | ITER_KVEC | ITER_XARRAY)) अणु
		व्योम *kaddr = kmap_atomic(page);
		माप_प्रकार wanted = _copy_from_iter(kaddr + offset, bytes, i);
		kunmap_atomic(kaddr);
		वापस wanted;
	पूर्ण अन्यथा
		वापस copy_page_from_iter_iovec(page, offset, bytes, i);
पूर्ण
EXPORT_SYMBOL(copy_page_from_iter);

अटल माप_प्रकार pipe_zero(माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	काष्ठा pipe_inode_info *pipe = i->pipe;
	अचिन्हित पूर्णांक p_mask = pipe->ring_size - 1;
	अचिन्हित पूर्णांक i_head;
	माप_प्रकार n, off;

	अगर (!sanity(i))
		वापस 0;

	bytes = n = push_pipe(i, bytes, &i_head, &off);
	अगर (unlikely(!n))
		वापस 0;

	करो अणु
		माप_प्रकार chunk = min_t(माप_प्रकार, n, PAGE_SIZE - off);
		memzero_page(pipe->bufs[i_head & p_mask].page, off, chunk);
		i->head = i_head;
		i->iov_offset = off + chunk;
		n -= chunk;
		off = 0;
		i_head++;
	पूर्ण जबतक (n);
	i->count -= bytes;
	वापस bytes;
पूर्ण

माप_प्रकार iov_iter_zero(माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	अगर (unlikely(iov_iter_is_pipe(i)))
		वापस pipe_zero(bytes, i);
	iterate_and_advance(i, bytes, v,
		clear_user(v.iov_base, v.iov_len),
		memzero_page(v.bv_page, v.bv_offset, v.bv_len),
		स_रखो(v.iov_base, 0, v.iov_len),
		memzero_page(v.bv_page, v.bv_offset, v.bv_len)
	)

	वापस bytes;
पूर्ण
EXPORT_SYMBOL(iov_iter_zero);

माप_प्रकार iov_iter_copy_from_user_atomic(काष्ठा page *page,
		काष्ठा iov_iter *i, अचिन्हित दीर्घ offset, माप_प्रकार bytes)
अणु
	अक्षर *kaddr = kmap_atomic(page), *p = kaddr + offset;
	अगर (unlikely(!page_copy_sane(page, offset, bytes))) अणु
		kunmap_atomic(kaddr);
		वापस 0;
	पूर्ण
	अगर (unlikely(iov_iter_is_pipe(i) || iov_iter_is_discard(i))) अणु
		kunmap_atomic(kaddr);
		WARN_ON(1);
		वापस 0;
	पूर्ण
	iterate_all_kinds(i, bytes, v,
		copyin((p += v.iov_len) - v.iov_len, v.iov_base, v.iov_len),
		स_नकल_from_page((p += v.bv_len) - v.bv_len, v.bv_page,
				 v.bv_offset, v.bv_len),
		स_नकल((p += v.iov_len) - v.iov_len, v.iov_base, v.iov_len),
		स_नकल_from_page((p += v.bv_len) - v.bv_len, v.bv_page,
				 v.bv_offset, v.bv_len)
	)
	kunmap_atomic(kaddr);
	वापस bytes;
पूर्ण
EXPORT_SYMBOL(iov_iter_copy_from_user_atomic);

अटल अंतरभूत व्योम pipe_truncate(काष्ठा iov_iter *i)
अणु
	काष्ठा pipe_inode_info *pipe = i->pipe;
	अचिन्हित पूर्णांक p_tail = pipe->tail;
	अचिन्हित पूर्णांक p_head = pipe->head;
	अचिन्हित पूर्णांक p_mask = pipe->ring_size - 1;

	अगर (!pipe_empty(p_head, p_tail)) अणु
		काष्ठा pipe_buffer *buf;
		अचिन्हित पूर्णांक i_head = i->head;
		माप_प्रकार off = i->iov_offset;

		अगर (off) अणु
			buf = &pipe->bufs[i_head & p_mask];
			buf->len = off - buf->offset;
			i_head++;
		पूर्ण
		जबतक (p_head != i_head) अणु
			p_head--;
			pipe_buf_release(pipe, &pipe->bufs[p_head & p_mask]);
		पूर्ण

		pipe->head = p_head;
	पूर्ण
पूर्ण

अटल व्योम pipe_advance(काष्ठा iov_iter *i, माप_प्रकार size)
अणु
	काष्ठा pipe_inode_info *pipe = i->pipe;
	अगर (unlikely(i->count < size))
		size = i->count;
	अगर (size) अणु
		काष्ठा pipe_buffer *buf;
		अचिन्हित पूर्णांक p_mask = pipe->ring_size - 1;
		अचिन्हित पूर्णांक i_head = i->head;
		माप_प्रकार off = i->iov_offset, left = size;

		अगर (off) /* make it relative to the beginning of buffer */
			left += off - pipe->bufs[i_head & p_mask].offset;
		जबतक (1) अणु
			buf = &pipe->bufs[i_head & p_mask];
			अगर (left <= buf->len)
				अवरोध;
			left -= buf->len;
			i_head++;
		पूर्ण
		i->head = i_head;
		i->iov_offset = buf->offset + left;
	पूर्ण
	i->count -= size;
	/* ... and discard everything past that poपूर्णांक */
	pipe_truncate(i);
पूर्ण

अटल व्योम iov_iter_bvec_advance(काष्ठा iov_iter *i, माप_प्रकार size)
अणु
	काष्ठा bvec_iter bi;

	bi.bi_size = i->count;
	bi.bi_bvec_करोne = i->iov_offset;
	bi.bi_idx = 0;
	bvec_iter_advance(i->bvec, &bi, size);

	i->bvec += bi.bi_idx;
	i->nr_segs -= bi.bi_idx;
	i->count = bi.bi_size;
	i->iov_offset = bi.bi_bvec_करोne;
पूर्ण

व्योम iov_iter_advance(काष्ठा iov_iter *i, माप_प्रकार size)
अणु
	अगर (unlikely(iov_iter_is_pipe(i))) अणु
		pipe_advance(i, size);
		वापस;
	पूर्ण
	अगर (unlikely(iov_iter_is_discard(i))) अणु
		i->count -= size;
		वापस;
	पूर्ण
	अगर (unlikely(iov_iter_is_xarray(i))) अणु
		size = min(size, i->count);
		i->iov_offset += size;
		i->count -= size;
		वापस;
	पूर्ण
	अगर (iov_iter_is_bvec(i)) अणु
		iov_iter_bvec_advance(i, size);
		वापस;
	पूर्ण
	iterate_and_advance(i, size, v, 0, 0, 0, 0)
पूर्ण
EXPORT_SYMBOL(iov_iter_advance);

व्योम iov_iter_revert(काष्ठा iov_iter *i, माप_प्रकार unroll)
अणु
	अगर (!unroll)
		वापस;
	अगर (WARN_ON(unroll > MAX_RW_COUNT))
		वापस;
	i->count += unroll;
	अगर (unlikely(iov_iter_is_pipe(i))) अणु
		काष्ठा pipe_inode_info *pipe = i->pipe;
		अचिन्हित पूर्णांक p_mask = pipe->ring_size - 1;
		अचिन्हित पूर्णांक i_head = i->head;
		माप_प्रकार off = i->iov_offset;
		जबतक (1) अणु
			काष्ठा pipe_buffer *b = &pipe->bufs[i_head & p_mask];
			माप_प्रकार n = off - b->offset;
			अगर (unroll < n) अणु
				off -= unroll;
				अवरोध;
			पूर्ण
			unroll -= n;
			अगर (!unroll && i_head == i->start_head) अणु
				off = 0;
				अवरोध;
			पूर्ण
			i_head--;
			b = &pipe->bufs[i_head & p_mask];
			off = b->offset + b->len;
		पूर्ण
		i->iov_offset = off;
		i->head = i_head;
		pipe_truncate(i);
		वापस;
	पूर्ण
	अगर (unlikely(iov_iter_is_discard(i)))
		वापस;
	अगर (unroll <= i->iov_offset) अणु
		i->iov_offset -= unroll;
		वापस;
	पूर्ण
	unroll -= i->iov_offset;
	अगर (iov_iter_is_xarray(i)) अणु
		BUG(); /* We should never go beyond the start of the specअगरied
			* range since we might then be straying पूर्णांकo pages that
			* aren't pinned.
			*/
	पूर्ण अन्यथा अगर (iov_iter_is_bvec(i)) अणु
		स्थिर काष्ठा bio_vec *bvec = i->bvec;
		जबतक (1) अणु
			माप_प्रकार n = (--bvec)->bv_len;
			i->nr_segs++;
			अगर (unroll <= n) अणु
				i->bvec = bvec;
				i->iov_offset = n - unroll;
				वापस;
			पूर्ण
			unroll -= n;
		पूर्ण
	पूर्ण अन्यथा अणु /* same logics क्रम iovec and kvec */
		स्थिर काष्ठा iovec *iov = i->iov;
		जबतक (1) अणु
			माप_प्रकार n = (--iov)->iov_len;
			i->nr_segs++;
			अगर (unroll <= n) अणु
				i->iov = iov;
				i->iov_offset = n - unroll;
				वापस;
			पूर्ण
			unroll -= n;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(iov_iter_revert);

/*
 * Return the count of just the current iov_iter segment.
 */
माप_प्रकार iov_iter_single_seg_count(स्थिर काष्ठा iov_iter *i)
अणु
	अगर (unlikely(iov_iter_is_pipe(i)))
		वापस i->count;	// it is a silly place, anyway
	अगर (i->nr_segs == 1)
		वापस i->count;
	अगर (unlikely(iov_iter_is_discard(i) || iov_iter_is_xarray(i)))
		वापस i->count;
	अगर (iov_iter_is_bvec(i))
		वापस min(i->count, i->bvec->bv_len - i->iov_offset);
	अन्यथा
		वापस min(i->count, i->iov->iov_len - i->iov_offset);
पूर्ण
EXPORT_SYMBOL(iov_iter_single_seg_count);

व्योम iov_iter_kvec(काष्ठा iov_iter *i, अचिन्हित पूर्णांक direction,
			स्थिर काष्ठा kvec *kvec, अचिन्हित दीर्घ nr_segs,
			माप_प्रकार count)
अणु
	WARN_ON(direction & ~(READ | WRITE));
	i->type = ITER_KVEC | (direction & (READ | WRITE));
	i->kvec = kvec;
	i->nr_segs = nr_segs;
	i->iov_offset = 0;
	i->count = count;
पूर्ण
EXPORT_SYMBOL(iov_iter_kvec);

व्योम iov_iter_bvec(काष्ठा iov_iter *i, अचिन्हित पूर्णांक direction,
			स्थिर काष्ठा bio_vec *bvec, अचिन्हित दीर्घ nr_segs,
			माप_प्रकार count)
अणु
	WARN_ON(direction & ~(READ | WRITE));
	i->type = ITER_BVEC | (direction & (READ | WRITE));
	i->bvec = bvec;
	i->nr_segs = nr_segs;
	i->iov_offset = 0;
	i->count = count;
पूर्ण
EXPORT_SYMBOL(iov_iter_bvec);

व्योम iov_iter_pipe(काष्ठा iov_iter *i, अचिन्हित पूर्णांक direction,
			काष्ठा pipe_inode_info *pipe,
			माप_प्रकार count)
अणु
	BUG_ON(direction != READ);
	WARN_ON(pipe_full(pipe->head, pipe->tail, pipe->ring_size));
	i->type = ITER_PIPE | READ;
	i->pipe = pipe;
	i->head = pipe->head;
	i->iov_offset = 0;
	i->count = count;
	i->start_head = i->head;
पूर्ण
EXPORT_SYMBOL(iov_iter_pipe);

/**
 * iov_iter_xarray - Initialise an I/O iterator to use the pages in an xarray
 * @i: The iterator to initialise.
 * @direction: The direction of the transfer.
 * @xarray: The xarray to access.
 * @start: The start file position.
 * @count: The size of the I/O buffer in bytes.
 *
 * Set up an I/O iterator to either draw data out of the pages attached to an
 * inode or to inject data पूर्णांकo those pages.  The pages *must* be prevented
 * from evaporation, either by taking a ref on them or locking them by the
 * caller.
 */
व्योम iov_iter_xarray(काष्ठा iov_iter *i, अचिन्हित पूर्णांक direction,
		     काष्ठा xarray *xarray, loff_t start, माप_प्रकार count)
अणु
	BUG_ON(direction & ~1);
	i->type = ITER_XARRAY | (direction & (READ | WRITE));
	i->xarray = xarray;
	i->xarray_start = start;
	i->count = count;
	i->iov_offset = 0;
पूर्ण
EXPORT_SYMBOL(iov_iter_xarray);

/**
 * iov_iter_discard - Initialise an I/O iterator that discards data
 * @i: The iterator to initialise.
 * @direction: The direction of the transfer.
 * @count: The size of the I/O buffer in bytes.
 *
 * Set up an I/O iterator that just discards everything that's written to it.
 * It's only available as a READ iterator.
 */
व्योम iov_iter_discard(काष्ठा iov_iter *i, अचिन्हित पूर्णांक direction, माप_प्रकार count)
अणु
	BUG_ON(direction != READ);
	i->type = ITER_DISCARD | READ;
	i->count = count;
	i->iov_offset = 0;
पूर्ण
EXPORT_SYMBOL(iov_iter_discard);

अचिन्हित दीर्घ iov_iter_alignment(स्थिर काष्ठा iov_iter *i)
अणु
	अचिन्हित दीर्घ res = 0;
	माप_प्रकार size = i->count;

	अगर (unlikely(iov_iter_is_pipe(i))) अणु
		अचिन्हित पूर्णांक p_mask = i->pipe->ring_size - 1;

		अगर (size && i->iov_offset && allocated(&i->pipe->bufs[i->head & p_mask]))
			वापस size | i->iov_offset;
		वापस size;
	पूर्ण
	अगर (unlikely(iov_iter_is_xarray(i)))
		वापस (i->xarray_start + i->iov_offset) | i->count;
	iterate_all_kinds(i, size, v,
		(res |= (अचिन्हित दीर्घ)v.iov_base | v.iov_len, 0),
		res |= v.bv_offset | v.bv_len,
		res |= (अचिन्हित दीर्घ)v.iov_base | v.iov_len,
		res |= v.bv_offset | v.bv_len
	)
	वापस res;
पूर्ण
EXPORT_SYMBOL(iov_iter_alignment);

अचिन्हित दीर्घ iov_iter_gap_alignment(स्थिर काष्ठा iov_iter *i)
अणु
	अचिन्हित दीर्घ res = 0;
	माप_प्रकार size = i->count;

	अगर (unlikely(iov_iter_is_pipe(i) || iov_iter_is_discard(i))) अणु
		WARN_ON(1);
		वापस ~0U;
	पूर्ण

	iterate_all_kinds(i, size, v,
		(res |= (!res ? 0 : (अचिन्हित दीर्घ)v.iov_base) |
			(size != v.iov_len ? size : 0), 0),
		(res |= (!res ? 0 : (अचिन्हित दीर्घ)v.bv_offset) |
			(size != v.bv_len ? size : 0)),
		(res |= (!res ? 0 : (अचिन्हित दीर्घ)v.iov_base) |
			(size != v.iov_len ? size : 0)),
		(res |= (!res ? 0 : (अचिन्हित दीर्घ)v.bv_offset) |
			(size != v.bv_len ? size : 0))
		);
	वापस res;
पूर्ण
EXPORT_SYMBOL(iov_iter_gap_alignment);

अटल अंतरभूत sमाप_प्रकार __pipe_get_pages(काष्ठा iov_iter *i,
				माप_प्रकार maxsize,
				काष्ठा page **pages,
				पूर्णांक iter_head,
				माप_प्रकार *start)
अणु
	काष्ठा pipe_inode_info *pipe = i->pipe;
	अचिन्हित पूर्णांक p_mask = pipe->ring_size - 1;
	sमाप_प्रकार n = push_pipe(i, maxsize, &iter_head, start);
	अगर (!n)
		वापस -EFAULT;

	maxsize = n;
	n += *start;
	जबतक (n > 0) अणु
		get_page(*pages++ = pipe->bufs[iter_head & p_mask].page);
		iter_head++;
		n -= PAGE_SIZE;
	पूर्ण

	वापस maxsize;
पूर्ण

अटल sमाप_प्रकार pipe_get_pages(काष्ठा iov_iter *i,
		   काष्ठा page **pages, माप_प्रकार maxsize, अचिन्हित maxpages,
		   माप_प्रकार *start)
अणु
	अचिन्हित पूर्णांक iter_head, npages;
	माप_प्रकार capacity;

	अगर (!maxsize)
		वापस 0;

	अगर (!sanity(i))
		वापस -EFAULT;

	data_start(i, &iter_head, start);
	/* Amount of मुक्त space: some of this one + all after this one */
	npages = pipe_space_क्रम_user(iter_head, i->pipe->tail, i->pipe);
	capacity = min(npages, maxpages) * PAGE_SIZE - *start;

	वापस __pipe_get_pages(i, min(maxsize, capacity), pages, iter_head, start);
पूर्ण

अटल sमाप_प्रकार iter_xarray_populate_pages(काष्ठा page **pages, काष्ठा xarray *xa,
					  pgoff_t index, अचिन्हित पूर्णांक nr_pages)
अणु
	XA_STATE(xas, xa, index);
	काष्ठा page *page;
	अचिन्हित पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	क्रम (page = xas_load(&xas); page; page = xas_next(&xas)) अणु
		अगर (xas_retry(&xas, page))
			जारी;

		/* Has the page moved or been split? */
		अगर (unlikely(page != xas_reload(&xas))) अणु
			xas_reset(&xas);
			जारी;
		पूर्ण

		pages[ret] = find_subpage(page, xas.xa_index);
		get_page(pages[ret]);
		अगर (++ret == nr_pages)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iter_xarray_get_pages(काष्ठा iov_iter *i,
				     काष्ठा page **pages, माप_प्रकार maxsize,
				     अचिन्हित maxpages, माप_प्रकार *_start_offset)
अणु
	अचिन्हित nr, offset;
	pgoff_t index, count;
	माप_प्रकार size = maxsize, actual;
	loff_t pos;

	अगर (!size || !maxpages)
		वापस 0;

	pos = i->xarray_start + i->iov_offset;
	index = pos >> PAGE_SHIFT;
	offset = pos & ~PAGE_MASK;
	*_start_offset = offset;

	count = 1;
	अगर (size > PAGE_SIZE - offset) अणु
		size -= PAGE_SIZE - offset;
		count += size >> PAGE_SHIFT;
		size &= ~PAGE_MASK;
		अगर (size)
			count++;
	पूर्ण

	अगर (count > maxpages)
		count = maxpages;

	nr = iter_xarray_populate_pages(pages, i->xarray, index, count);
	अगर (nr == 0)
		वापस 0;

	actual = PAGE_SIZE * nr;
	actual -= offset;
	अगर (nr == count && size > 0) अणु
		अचिन्हित last_offset = (nr > 1) ? 0 : offset;
		actual -= PAGE_SIZE - (last_offset + size);
	पूर्ण
	वापस actual;
पूर्ण

sमाप_प्रकार iov_iter_get_pages(काष्ठा iov_iter *i,
		   काष्ठा page **pages, माप_प्रकार maxsize, अचिन्हित maxpages,
		   माप_प्रकार *start)
अणु
	अगर (maxsize > i->count)
		maxsize = i->count;

	अगर (unlikely(iov_iter_is_pipe(i)))
		वापस pipe_get_pages(i, pages, maxsize, maxpages, start);
	अगर (unlikely(iov_iter_is_xarray(i)))
		वापस iter_xarray_get_pages(i, pages, maxsize, maxpages, start);
	अगर (unlikely(iov_iter_is_discard(i)))
		वापस -EFAULT;

	iterate_all_kinds(i, maxsize, v, (अणु
		अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)v.iov_base;
		माप_प्रकार len = v.iov_len + (*start = addr & (PAGE_SIZE - 1));
		पूर्णांक n;
		पूर्णांक res;

		अगर (len > maxpages * PAGE_SIZE)
			len = maxpages * PAGE_SIZE;
		addr &= ~(PAGE_SIZE - 1);
		n = DIV_ROUND_UP(len, PAGE_SIZE);
		res = get_user_pages_fast(addr, n,
				iov_iter_rw(i) != WRITE ?  FOLL_WRITE : 0,
				pages);
		अगर (unlikely(res < 0))
			वापस res;
		वापस (res == n ? len : res * PAGE_SIZE) - *start;
	0;पूर्ण),(अणु
		/* can't be more than PAGE_SIZE */
		*start = v.bv_offset;
		get_page(*pages = v.bv_page);
		वापस v.bv_len;
	पूर्ण),(अणु
		वापस -EFAULT;
	पूर्ण),
	0
	)
	वापस 0;
पूर्ण
EXPORT_SYMBOL(iov_iter_get_pages);

अटल काष्ठा page **get_pages_array(माप_प्रकार n)
अणु
	वापस kvदो_स्मृति_array(n, माप(काष्ठा page *), GFP_KERNEL);
पूर्ण

अटल sमाप_प्रकार pipe_get_pages_alloc(काष्ठा iov_iter *i,
		   काष्ठा page ***pages, माप_प्रकार maxsize,
		   माप_प्रकार *start)
अणु
	काष्ठा page **p;
	अचिन्हित पूर्णांक iter_head, npages;
	sमाप_प्रकार n;

	अगर (!maxsize)
		वापस 0;

	अगर (!sanity(i))
		वापस -EFAULT;

	data_start(i, &iter_head, start);
	/* Amount of मुक्त space: some of this one + all after this one */
	npages = pipe_space_क्रम_user(iter_head, i->pipe->tail, i->pipe);
	n = npages * PAGE_SIZE - *start;
	अगर (maxsize > n)
		maxsize = n;
	अन्यथा
		npages = DIV_ROUND_UP(maxsize + *start, PAGE_SIZE);
	p = get_pages_array(npages);
	अगर (!p)
		वापस -ENOMEM;
	n = __pipe_get_pages(i, maxsize, p, iter_head, start);
	अगर (n > 0)
		*pages = p;
	अन्यथा
		kvमुक्त(p);
	वापस n;
पूर्ण

अटल sमाप_प्रकार iter_xarray_get_pages_alloc(काष्ठा iov_iter *i,
					   काष्ठा page ***pages, माप_प्रकार maxsize,
					   माप_प्रकार *_start_offset)
अणु
	काष्ठा page **p;
	अचिन्हित nr, offset;
	pgoff_t index, count;
	माप_प्रकार size = maxsize, actual;
	loff_t pos;

	अगर (!size)
		वापस 0;

	pos = i->xarray_start + i->iov_offset;
	index = pos >> PAGE_SHIFT;
	offset = pos & ~PAGE_MASK;
	*_start_offset = offset;

	count = 1;
	अगर (size > PAGE_SIZE - offset) अणु
		size -= PAGE_SIZE - offset;
		count += size >> PAGE_SHIFT;
		size &= ~PAGE_MASK;
		अगर (size)
			count++;
	पूर्ण

	p = get_pages_array(count);
	अगर (!p)
		वापस -ENOMEM;
	*pages = p;

	nr = iter_xarray_populate_pages(p, i->xarray, index, count);
	अगर (nr == 0)
		वापस 0;

	actual = PAGE_SIZE * nr;
	actual -= offset;
	अगर (nr == count && size > 0) अणु
		अचिन्हित last_offset = (nr > 1) ? 0 : offset;
		actual -= PAGE_SIZE - (last_offset + size);
	पूर्ण
	वापस actual;
पूर्ण

sमाप_प्रकार iov_iter_get_pages_alloc(काष्ठा iov_iter *i,
		   काष्ठा page ***pages, माप_प्रकार maxsize,
		   माप_प्रकार *start)
अणु
	काष्ठा page **p;

	अगर (maxsize > i->count)
		maxsize = i->count;

	अगर (unlikely(iov_iter_is_pipe(i)))
		वापस pipe_get_pages_alloc(i, pages, maxsize, start);
	अगर (unlikely(iov_iter_is_xarray(i)))
		वापस iter_xarray_get_pages_alloc(i, pages, maxsize, start);
	अगर (unlikely(iov_iter_is_discard(i)))
		वापस -EFAULT;

	iterate_all_kinds(i, maxsize, v, (अणु
		अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)v.iov_base;
		माप_प्रकार len = v.iov_len + (*start = addr & (PAGE_SIZE - 1));
		पूर्णांक n;
		पूर्णांक res;

		addr &= ~(PAGE_SIZE - 1);
		n = DIV_ROUND_UP(len, PAGE_SIZE);
		p = get_pages_array(n);
		अगर (!p)
			वापस -ENOMEM;
		res = get_user_pages_fast(addr, n,
				iov_iter_rw(i) != WRITE ?  FOLL_WRITE : 0, p);
		अगर (unlikely(res < 0)) अणु
			kvमुक्त(p);
			वापस res;
		पूर्ण
		*pages = p;
		वापस (res == n ? len : res * PAGE_SIZE) - *start;
	0;पूर्ण),(अणु
		/* can't be more than PAGE_SIZE */
		*start = v.bv_offset;
		*pages = p = get_pages_array(1);
		अगर (!p)
			वापस -ENOMEM;
		get_page(*p = v.bv_page);
		वापस v.bv_len;
	पूर्ण),(अणु
		वापस -EFAULT;
	पूर्ण), 0
	)
	वापस 0;
पूर्ण
EXPORT_SYMBOL(iov_iter_get_pages_alloc);

माप_प्रकार csum_and_copy_from_iter(व्योम *addr, माप_प्रकार bytes, __wsum *csum,
			       काष्ठा iov_iter *i)
अणु
	अक्षर *to = addr;
	__wsum sum, next;
	माप_प्रकार off = 0;
	sum = *csum;
	अगर (unlikely(iov_iter_is_pipe(i) || iov_iter_is_discard(i))) अणु
		WARN_ON(1);
		वापस 0;
	पूर्ण
	iterate_and_advance(i, bytes, v, (अणु
		next = csum_and_copy_from_user(v.iov_base,
					       (to += v.iov_len) - v.iov_len,
					       v.iov_len);
		अगर (next) अणु
			sum = csum_block_add(sum, next, off);
			off += v.iov_len;
		पूर्ण
		next ? 0 : v.iov_len;
	पूर्ण), (अणु
		अक्षर *p = kmap_atomic(v.bv_page);
		sum = csum_and_स_नकल((to += v.bv_len) - v.bv_len,
				      p + v.bv_offset, v.bv_len,
				      sum, off);
		kunmap_atomic(p);
		off += v.bv_len;
	पूर्ण),(अणु
		sum = csum_and_स_नकल((to += v.iov_len) - v.iov_len,
				      v.iov_base, v.iov_len,
				      sum, off);
		off += v.iov_len;
	पूर्ण), (अणु
		अक्षर *p = kmap_atomic(v.bv_page);
		sum = csum_and_स_नकल((to += v.bv_len) - v.bv_len,
				      p + v.bv_offset, v.bv_len,
				      sum, off);
		kunmap_atomic(p);
		off += v.bv_len;
	पूर्ण)
	)
	*csum = sum;
	वापस bytes;
पूर्ण
EXPORT_SYMBOL(csum_and_copy_from_iter);

bool csum_and_copy_from_iter_full(व्योम *addr, माप_प्रकार bytes, __wsum *csum,
			       काष्ठा iov_iter *i)
अणु
	अक्षर *to = addr;
	__wsum sum, next;
	माप_प्रकार off = 0;
	sum = *csum;
	अगर (unlikely(iov_iter_is_pipe(i) || iov_iter_is_discard(i))) अणु
		WARN_ON(1);
		वापस false;
	पूर्ण
	अगर (unlikely(i->count < bytes))
		वापस false;
	iterate_all_kinds(i, bytes, v, (अणु
		next = csum_and_copy_from_user(v.iov_base,
					       (to += v.iov_len) - v.iov_len,
					       v.iov_len);
		अगर (!next)
			वापस false;
		sum = csum_block_add(sum, next, off);
		off += v.iov_len;
		0;
	पूर्ण), (अणु
		अक्षर *p = kmap_atomic(v.bv_page);
		sum = csum_and_स_नकल((to += v.bv_len) - v.bv_len,
				      p + v.bv_offset, v.bv_len,
				      sum, off);
		kunmap_atomic(p);
		off += v.bv_len;
	पूर्ण),(अणु
		sum = csum_and_स_नकल((to += v.iov_len) - v.iov_len,
				      v.iov_base, v.iov_len,
				      sum, off);
		off += v.iov_len;
	पूर्ण), (अणु
		अक्षर *p = kmap_atomic(v.bv_page);
		sum = csum_and_स_नकल((to += v.bv_len) - v.bv_len,
				      p + v.bv_offset, v.bv_len,
				      sum, off);
		kunmap_atomic(p);
		off += v.bv_len;
	पूर्ण)
	)
	*csum = sum;
	iov_iter_advance(i, bytes);
	वापस true;
पूर्ण
EXPORT_SYMBOL(csum_and_copy_from_iter_full);

माप_प्रकार csum_and_copy_to_iter(स्थिर व्योम *addr, माप_प्रकार bytes, व्योम *_csstate,
			     काष्ठा iov_iter *i)
अणु
	काष्ठा csum_state *csstate = _csstate;
	स्थिर अक्षर *from = addr;
	__wsum sum, next;
	माप_प्रकार off;

	अगर (unlikely(iov_iter_is_pipe(i)))
		वापस csum_and_copy_to_pipe_iter(addr, bytes, _csstate, i);

	sum = csstate->csum;
	off = csstate->off;
	अगर (unlikely(iov_iter_is_discard(i))) अणु
		WARN_ON(1);	/* क्रम now */
		वापस 0;
	पूर्ण
	iterate_and_advance(i, bytes, v, (अणु
		next = csum_and_copy_to_user((from += v.iov_len) - v.iov_len,
					     v.iov_base,
					     v.iov_len);
		अगर (next) अणु
			sum = csum_block_add(sum, next, off);
			off += v.iov_len;
		पूर्ण
		next ? 0 : v.iov_len;
	पूर्ण), (अणु
		अक्षर *p = kmap_atomic(v.bv_page);
		sum = csum_and_स_नकल(p + v.bv_offset,
				      (from += v.bv_len) - v.bv_len,
				      v.bv_len, sum, off);
		kunmap_atomic(p);
		off += v.bv_len;
	पूर्ण),(अणु
		sum = csum_and_स_नकल(v.iov_base,
				     (from += v.iov_len) - v.iov_len,
				     v.iov_len, sum, off);
		off += v.iov_len;
	पूर्ण), (अणु
		अक्षर *p = kmap_atomic(v.bv_page);
		sum = csum_and_स_नकल(p + v.bv_offset,
				      (from += v.bv_len) - v.bv_len,
				      v.bv_len, sum, off);
		kunmap_atomic(p);
		off += v.bv_len;
	पूर्ण)
	)
	csstate->csum = sum;
	csstate->off = off;
	वापस bytes;
पूर्ण
EXPORT_SYMBOL(csum_and_copy_to_iter);

माप_प्रकार hash_and_copy_to_iter(स्थिर व्योम *addr, माप_प्रकार bytes, व्योम *hashp,
		काष्ठा iov_iter *i)
अणु
#अगर_घोषित CONFIG_CRYPTO_HASH
	काष्ठा ahash_request *hash = hashp;
	काष्ठा scatterlist sg;
	माप_प्रकार copied;

	copied = copy_to_iter(addr, bytes, i);
	sg_init_one(&sg, addr, copied);
	ahash_request_set_crypt(hash, &sg, शून्य, copied);
	crypto_ahash_update(hash);
	वापस copied;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(hash_and_copy_to_iter);

पूर्णांक iov_iter_npages(स्थिर काष्ठा iov_iter *i, पूर्णांक maxpages)
अणु
	माप_प्रकार size = i->count;
	पूर्णांक npages = 0;

	अगर (!size)
		वापस 0;
	अगर (unlikely(iov_iter_is_discard(i)))
		वापस 0;

	अगर (unlikely(iov_iter_is_pipe(i))) अणु
		काष्ठा pipe_inode_info *pipe = i->pipe;
		अचिन्हित पूर्णांक iter_head;
		माप_प्रकार off;

		अगर (!sanity(i))
			वापस 0;

		data_start(i, &iter_head, &off);
		/* some of this one + all after this one */
		npages = pipe_space_क्रम_user(iter_head, pipe->tail, pipe);
		अगर (npages >= maxpages)
			वापस maxpages;
	पूर्ण अन्यथा अगर (unlikely(iov_iter_is_xarray(i))) अणु
		अचिन्हित offset;

		offset = (i->xarray_start + i->iov_offset) & ~PAGE_MASK;

		npages = 1;
		अगर (size > PAGE_SIZE - offset) अणु
			size -= PAGE_SIZE - offset;
			npages += size >> PAGE_SHIFT;
			size &= ~PAGE_MASK;
			अगर (size)
				npages++;
		पूर्ण
		अगर (npages >= maxpages)
			वापस maxpages;
	पूर्ण अन्यथा iterate_all_kinds(i, size, v, (अणु
		अचिन्हित दीर्घ p = (अचिन्हित दीर्घ)v.iov_base;
		npages += DIV_ROUND_UP(p + v.iov_len, PAGE_SIZE)
			- p / PAGE_SIZE;
		अगर (npages >= maxpages)
			वापस maxpages;
	0;पूर्ण),(अणु
		npages++;
		अगर (npages >= maxpages)
			वापस maxpages;
	पूर्ण),(अणु
		अचिन्हित दीर्घ p = (अचिन्हित दीर्घ)v.iov_base;
		npages += DIV_ROUND_UP(p + v.iov_len, PAGE_SIZE)
			- p / PAGE_SIZE;
		अगर (npages >= maxpages)
			वापस maxpages;
	पूर्ण),
	0
	)
	वापस npages;
पूर्ण
EXPORT_SYMBOL(iov_iter_npages);

स्थिर व्योम *dup_iter(काष्ठा iov_iter *new, काष्ठा iov_iter *old, gfp_t flags)
अणु
	*new = *old;
	अगर (unlikely(iov_iter_is_pipe(new))) अणु
		WARN_ON(1);
		वापस शून्य;
	पूर्ण
	अगर (unlikely(iov_iter_is_discard(new) || iov_iter_is_xarray(new)))
		वापस शून्य;
	अगर (iov_iter_is_bvec(new))
		वापस new->bvec = kmemdup(new->bvec,
				    new->nr_segs * माप(काष्ठा bio_vec),
				    flags);
	अन्यथा
		/* iovec and kvec have identical layout */
		वापस new->iov = kmemdup(new->iov,
				   new->nr_segs * माप(काष्ठा iovec),
				   flags);
पूर्ण
EXPORT_SYMBOL(dup_iter);

अटल पूर्णांक copy_compat_iovec_from_user(काष्ठा iovec *iov,
		स्थिर काष्ठा iovec __user *uvec, अचिन्हित दीर्घ nr_segs)
अणु
	स्थिर काष्ठा compat_iovec __user *uiov =
		(स्थिर काष्ठा compat_iovec __user *)uvec;
	पूर्णांक ret = -EFAULT, i;

	अगर (!user_access_begin(uiov, nr_segs * माप(*uiov)))
		वापस -EFAULT;

	क्रम (i = 0; i < nr_segs; i++) अणु
		compat_uptr_t buf;
		compat_sमाप_प्रकार len;

		unsafe_get_user(len, &uiov[i].iov_len, uaccess_end);
		unsafe_get_user(buf, &uiov[i].iov_base, uaccess_end);

		/* check क्रम compat_माप_प्रकार not fitting in compat_sमाप_प्रकार .. */
		अगर (len < 0) अणु
			ret = -EINVAL;
			जाओ uaccess_end;
		पूर्ण
		iov[i].iov_base = compat_ptr(buf);
		iov[i].iov_len = len;
	पूर्ण

	ret = 0;
uaccess_end:
	user_access_end();
	वापस ret;
पूर्ण

अटल पूर्णांक copy_iovec_from_user(काष्ठा iovec *iov,
		स्थिर काष्ठा iovec __user *uvec, अचिन्हित दीर्घ nr_segs)
अणु
	अचिन्हित दीर्घ seg;

	अगर (copy_from_user(iov, uvec, nr_segs * माप(*uvec)))
		वापस -EFAULT;
	क्रम (seg = 0; seg < nr_segs; seg++) अणु
		अगर ((sमाप_प्रकार)iov[seg].iov_len < 0)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा iovec *iovec_from_user(स्थिर काष्ठा iovec __user *uvec,
		अचिन्हित दीर्घ nr_segs, अचिन्हित दीर्घ fast_segs,
		काष्ठा iovec *fast_iov, bool compat)
अणु
	काष्ठा iovec *iov = fast_iov;
	पूर्णांक ret;

	/*
	 * SuS says "The पढ़ोv() function *may* fail अगर the iovcnt argument was
	 * less than or equal to 0, or greater than अणुIOV_MAXपूर्ण.  Linux has
	 * traditionally वापसed zero क्रम zero segments, so...
	 */
	अगर (nr_segs == 0)
		वापस iov;
	अगर (nr_segs > UIO_MAXIOV)
		वापस ERR_PTR(-EINVAL);
	अगर (nr_segs > fast_segs) अणु
		iov = kदो_स्मृति_array(nr_segs, माप(काष्ठा iovec), GFP_KERNEL);
		अगर (!iov)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण

	अगर (compat)
		ret = copy_compat_iovec_from_user(iov, uvec, nr_segs);
	अन्यथा
		ret = copy_iovec_from_user(iov, uvec, nr_segs);
	अगर (ret) अणु
		अगर (iov != fast_iov)
			kमुक्त(iov);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस iov;
पूर्ण

sमाप_प्रकार __import_iovec(पूर्णांक type, स्थिर काष्ठा iovec __user *uvec,
		 अचिन्हित nr_segs, अचिन्हित fast_segs, काष्ठा iovec **iovp,
		 काष्ठा iov_iter *i, bool compat)
अणु
	sमाप_प्रकार total_len = 0;
	अचिन्हित दीर्घ seg;
	काष्ठा iovec *iov;

	iov = iovec_from_user(uvec, nr_segs, fast_segs, *iovp, compat);
	अगर (IS_ERR(iov)) अणु
		*iovp = शून्य;
		वापस PTR_ERR(iov);
	पूर्ण

	/*
	 * According to the Single Unix Specअगरication we should वापस EINVAL अगर
	 * an element length is < 0 when cast to sमाप_प्रकार or अगर the total length
	 * would overflow the sमाप_प्रकार वापस value of the प्रणाली call.
	 *
	 * Linux caps all पढ़ो/ग_लिखो calls to MAX_RW_COUNT, and aव्योमs the
	 * overflow हाल.
	 */
	क्रम (seg = 0; seg < nr_segs; seg++) अणु
		sमाप_प्रकार len = (sमाप_प्रकार)iov[seg].iov_len;

		अगर (!access_ok(iov[seg].iov_base, len)) अणु
			अगर (iov != *iovp)
				kमुक्त(iov);
			*iovp = शून्य;
			वापस -EFAULT;
		पूर्ण

		अगर (len > MAX_RW_COUNT - total_len) अणु
			len = MAX_RW_COUNT - total_len;
			iov[seg].iov_len = len;
		पूर्ण
		total_len += len;
	पूर्ण

	iov_iter_init(i, type, iov, nr_segs, total_len);
	अगर (iov == *iovp)
		*iovp = शून्य;
	अन्यथा
		*iovp = iov;
	वापस total_len;
पूर्ण

/**
 * import_iovec() - Copy an array of &काष्ठा iovec from userspace
 *     पूर्णांकo the kernel, check that it is valid, and initialize a new
 *     &काष्ठा iov_iter iterator to access it.
 *
 * @type: One of %READ or %WRITE.
 * @uvec: Poपूर्णांकer to the userspace array.
 * @nr_segs: Number of elements in userspace array.
 * @fast_segs: Number of elements in @iov.
 * @iovp: (input and output parameter) Poपूर्णांकer to poपूर्णांकer to (usually small
 *     on-stack) kernel array.
 * @i: Poपूर्णांकer to iterator that will be initialized on success.
 *
 * If the array poपूर्णांकed to by *@iov is large enough to hold all @nr_segs,
 * then this function places %शून्य in *@iov on वापस. Otherwise, a new
 * array will be allocated and the result placed in *@iov. This means that
 * the caller may call kमुक्त() on *@iov regardless of whether the small
 * on-stack array was used or not (and regardless of whether this function
 * वापसs an error or not).
 *
 * Return: Negative error code on error, bytes imported on success
 */
sमाप_प्रकार import_iovec(पूर्णांक type, स्थिर काष्ठा iovec __user *uvec,
		 अचिन्हित nr_segs, अचिन्हित fast_segs,
		 काष्ठा iovec **iovp, काष्ठा iov_iter *i)
अणु
	वापस __import_iovec(type, uvec, nr_segs, fast_segs, iovp, i,
			      in_compat_syscall());
पूर्ण
EXPORT_SYMBOL(import_iovec);

पूर्णांक import_single_range(पूर्णांक rw, व्योम __user *buf, माप_प्रकार len,
		 काष्ठा iovec *iov, काष्ठा iov_iter *i)
अणु
	अगर (len > MAX_RW_COUNT)
		len = MAX_RW_COUNT;
	अगर (unlikely(!access_ok(buf, len)))
		वापस -EFAULT;

	iov->iov_base = buf;
	iov->iov_len = len;
	iov_iter_init(i, rw, iov, 1, len);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(import_single_range);

पूर्णांक iov_iter_क्रम_each_range(काष्ठा iov_iter *i, माप_प्रकार bytes,
			    पूर्णांक (*f)(काष्ठा kvec *vec, व्योम *context),
			    व्योम *context)
अणु
	काष्ठा kvec w;
	पूर्णांक err = -EINVAL;
	अगर (!bytes)
		वापस 0;

	iterate_all_kinds(i, bytes, v, -EINVAL, (अणु
		w.iov_base = kmap(v.bv_page) + v.bv_offset;
		w.iov_len = v.bv_len;
		err = f(&w, context);
		kunmap(v.bv_page);
		err;पूर्ण), (अणु
		w = v;
		err = f(&w, context);पूर्ण), (अणु
		w.iov_base = kmap(v.bv_page) + v.bv_offset;
		w.iov_len = v.bv_len;
		err = f(&w, context);
		kunmap(v.bv_page);
		err;पूर्ण)
	)
	वापस err;
पूर्ण
EXPORT_SYMBOL(iov_iter_क्रम_each_range);
