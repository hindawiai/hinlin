<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Functions related to mapping data to requests
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/module.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/uपन.स>

#समावेश "blk.h"

काष्ठा bio_map_data अणु
	bool is_our_pages : 1;
	bool is_null_mapped : 1;
	काष्ठा iov_iter iter;
	काष्ठा iovec iov[];
पूर्ण;

अटल काष्ठा bio_map_data *bio_alloc_map_data(काष्ठा iov_iter *data,
					       gfp_t gfp_mask)
अणु
	काष्ठा bio_map_data *bmd;

	अगर (data->nr_segs > UIO_MAXIOV)
		वापस शून्य;

	bmd = kदो_स्मृति(काष्ठा_size(bmd, iov, data->nr_segs), gfp_mask);
	अगर (!bmd)
		वापस शून्य;
	स_नकल(bmd->iov, data->iov, माप(काष्ठा iovec) * data->nr_segs);
	bmd->iter = *data;
	bmd->iter.iov = bmd->iov;
	वापस bmd;
पूर्ण

/**
 * bio_copy_from_iter - copy all pages from iov_iter to bio
 * @bio: The &काष्ठा bio which describes the I/O as destination
 * @iter: iov_iter as source
 *
 * Copy all pages from iov_iter to bio.
 * Returns 0 on success, or error on failure.
 */
अटल पूर्णांक bio_copy_from_iter(काष्ठा bio *bio, काष्ठा iov_iter *iter)
अणु
	काष्ठा bio_vec *bvec;
	काष्ठा bvec_iter_all iter_all;

	bio_क्रम_each_segment_all(bvec, bio, iter_all) अणु
		sमाप_प्रकार ret;

		ret = copy_page_from_iter(bvec->bv_page,
					  bvec->bv_offset,
					  bvec->bv_len,
					  iter);

		अगर (!iov_iter_count(iter))
			अवरोध;

		अगर (ret < bvec->bv_len)
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * bio_copy_to_iter - copy all pages from bio to iov_iter
 * @bio: The &काष्ठा bio which describes the I/O as source
 * @iter: iov_iter as destination
 *
 * Copy all pages from bio to iov_iter.
 * Returns 0 on success, or error on failure.
 */
अटल पूर्णांक bio_copy_to_iter(काष्ठा bio *bio, काष्ठा iov_iter iter)
अणु
	काष्ठा bio_vec *bvec;
	काष्ठा bvec_iter_all iter_all;

	bio_क्रम_each_segment_all(bvec, bio, iter_all) अणु
		sमाप_प्रकार ret;

		ret = copy_page_to_iter(bvec->bv_page,
					bvec->bv_offset,
					bvec->bv_len,
					&iter);

		अगर (!iov_iter_count(&iter))
			अवरोध;

		अगर (ret < bvec->bv_len)
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	bio_uncopy_user	-	finish previously mapped bio
 *	@bio: bio being terminated
 *
 *	Free pages allocated from bio_copy_user_iov() and ग_लिखो back data
 *	to user space in हाल of a पढ़ो.
 */
अटल पूर्णांक bio_uncopy_user(काष्ठा bio *bio)
अणु
	काष्ठा bio_map_data *bmd = bio->bi_निजी;
	पूर्णांक ret = 0;

	अगर (!bmd->is_null_mapped) अणु
		/*
		 * अगर we're in a workqueue, the request is orphaned, so
		 * करोn't copy पूर्णांकo a अक्रमom user address space, just मुक्त
		 * and वापस -EINTR so user space करोesn't expect any data.
		 */
		अगर (!current->mm)
			ret = -EINTR;
		अन्यथा अगर (bio_data_dir(bio) == READ)
			ret = bio_copy_to_iter(bio, bmd->iter);
		अगर (bmd->is_our_pages)
			bio_मुक्त_pages(bio);
	पूर्ण
	kमुक्त(bmd);
	वापस ret;
पूर्ण

अटल पूर्णांक bio_copy_user_iov(काष्ठा request *rq, काष्ठा rq_map_data *map_data,
		काष्ठा iov_iter *iter, gfp_t gfp_mask)
अणु
	काष्ठा bio_map_data *bmd;
	काष्ठा page *page;
	काष्ठा bio *bio;
	पूर्णांक i = 0, ret;
	पूर्णांक nr_pages;
	अचिन्हित पूर्णांक len = iter->count;
	अचिन्हित पूर्णांक offset = map_data ? offset_in_page(map_data->offset) : 0;

	bmd = bio_alloc_map_data(iter, gfp_mask);
	अगर (!bmd)
		वापस -ENOMEM;

	/*
	 * We need to करो a deep copy of the iov_iter including the iovecs.
	 * The caller provided iov might poपूर्णांक to an on-stack or otherwise
	 * लघुlived one.
	 */
	bmd->is_our_pages = !map_data;
	bmd->is_null_mapped = (map_data && map_data->null_mapped);

	nr_pages = bio_max_segs(DIV_ROUND_UP(offset + len, PAGE_SIZE));

	ret = -ENOMEM;
	bio = bio_kदो_स्मृति(gfp_mask, nr_pages);
	अगर (!bio)
		जाओ out_bmd;
	bio->bi_opf |= req_op(rq);

	अगर (map_data) अणु
		nr_pages = 1 << map_data->page_order;
		i = map_data->offset / PAGE_SIZE;
	पूर्ण
	जबतक (len) अणु
		अचिन्हित पूर्णांक bytes = PAGE_SIZE;

		bytes -= offset;

		अगर (bytes > len)
			bytes = len;

		अगर (map_data) अणु
			अगर (i == map_data->nr_entries * nr_pages) अणु
				ret = -ENOMEM;
				जाओ cleanup;
			पूर्ण

			page = map_data->pages[i / nr_pages];
			page += (i % nr_pages);

			i++;
		पूर्ण अन्यथा अणु
			page = alloc_page(GFP_NOIO | gfp_mask);
			अगर (!page) अणु
				ret = -ENOMEM;
				जाओ cleanup;
			पूर्ण
		पूर्ण

		अगर (bio_add_pc_page(rq->q, bio, page, bytes, offset) < bytes) अणु
			अगर (!map_data)
				__मुक्त_page(page);
			अवरोध;
		पूर्ण

		len -= bytes;
		offset = 0;
	पूर्ण

	अगर (map_data)
		map_data->offset += bio->bi_iter.bi_size;

	/*
	 * success
	 */
	अगर ((iov_iter_rw(iter) == WRITE &&
	     (!map_data || !map_data->null_mapped)) ||
	    (map_data && map_data->from_user)) अणु
		ret = bio_copy_from_iter(bio, iter);
		अगर (ret)
			जाओ cleanup;
	पूर्ण अन्यथा अणु
		अगर (bmd->is_our_pages)
			zero_fill_bio(bio);
		iov_iter_advance(iter, bio->bi_iter.bi_size);
	पूर्ण

	bio->bi_निजी = bmd;

	ret = blk_rq_append_bio(rq, bio);
	अगर (ret)
		जाओ cleanup;
	वापस 0;
cleanup:
	अगर (!map_data)
		bio_मुक्त_pages(bio);
	bio_put(bio);
out_bmd:
	kमुक्त(bmd);
	वापस ret;
पूर्ण

अटल पूर्णांक bio_map_user_iov(काष्ठा request *rq, काष्ठा iov_iter *iter,
		gfp_t gfp_mask)
अणु
	अचिन्हित पूर्णांक max_sectors = queue_max_hw_sectors(rq->q);
	काष्ठा bio *bio;
	पूर्णांक ret;
	पूर्णांक j;

	अगर (!iov_iter_count(iter))
		वापस -EINVAL;

	bio = bio_kदो_स्मृति(gfp_mask, iov_iter_npages(iter, BIO_MAX_VECS));
	अगर (!bio)
		वापस -ENOMEM;
	bio->bi_opf |= req_op(rq);

	जबतक (iov_iter_count(iter)) अणु
		काष्ठा page **pages;
		sमाप_प्रकार bytes;
		माप_प्रकार offs, added = 0;
		पूर्णांक npages;

		bytes = iov_iter_get_pages_alloc(iter, &pages, दीर्घ_उच्च, &offs);
		अगर (unlikely(bytes <= 0)) अणु
			ret = bytes ? bytes : -EFAULT;
			जाओ out_unmap;
		पूर्ण

		npages = DIV_ROUND_UP(offs + bytes, PAGE_SIZE);

		अगर (unlikely(offs & queue_dma_alignment(rq->q))) अणु
			ret = -EINVAL;
			j = 0;
		पूर्ण अन्यथा अणु
			क्रम (j = 0; j < npages; j++) अणु
				काष्ठा page *page = pages[j];
				अचिन्हित पूर्णांक n = PAGE_SIZE - offs;
				bool same_page = false;

				अगर (n > bytes)
					n = bytes;

				अगर (!bio_add_hw_page(rq->q, bio, page, n, offs,
						     max_sectors, &same_page)) अणु
					अगर (same_page)
						put_page(page);
					अवरोध;
				पूर्ण

				added += n;
				bytes -= n;
				offs = 0;
			पूर्ण
			iov_iter_advance(iter, added);
		पूर्ण
		/*
		 * release the pages we didn't map पूर्णांकo the bio, अगर any
		 */
		जबतक (j < npages)
			put_page(pages[j++]);
		kvमुक्त(pages);
		/* couldn't stuff something पूर्णांकo bio? */
		अगर (bytes)
			अवरोध;
	पूर्ण

	ret = blk_rq_append_bio(rq, bio);
	अगर (ret)
		जाओ out_unmap;
	वापस 0;

 out_unmap:
	bio_release_pages(bio, false);
	bio_put(bio);
	वापस ret;
पूर्ण

अटल व्योम bio_invalidate_vदो_स्मृति_pages(काष्ठा bio *bio)
अणु
#अगर_घोषित ARCH_HAS_FLUSH_KERNEL_DCACHE_PAGE
	अगर (bio->bi_निजी && !op_is_ग_लिखो(bio_op(bio))) अणु
		अचिन्हित दीर्घ i, len = 0;

		क्रम (i = 0; i < bio->bi_vcnt; i++)
			len += bio->bi_io_vec[i].bv_len;
		invalidate_kernel_vmap_range(bio->bi_निजी, len);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम bio_map_kern_endio(काष्ठा bio *bio)
अणु
	bio_invalidate_vदो_स्मृति_pages(bio);
	bio_put(bio);
पूर्ण

/**
 *	bio_map_kern	-	map kernel address पूर्णांकo bio
 *	@q: the काष्ठा request_queue क्रम the bio
 *	@data: poपूर्णांकer to buffer to map
 *	@len: length in bytes
 *	@gfp_mask: allocation flags क्रम bio allocation
 *
 *	Map the kernel address पूर्णांकo a bio suitable क्रम io to a block
 *	device. Returns an error poपूर्णांकer in हाल of error.
 */
अटल काष्ठा bio *bio_map_kern(काष्ठा request_queue *q, व्योम *data,
		अचिन्हित पूर्णांक len, gfp_t gfp_mask)
अणु
	अचिन्हित दीर्घ kaddr = (अचिन्हित दीर्घ)data;
	अचिन्हित दीर्घ end = (kaddr + len + PAGE_SIZE - 1) >> PAGE_SHIFT;
	अचिन्हित दीर्घ start = kaddr >> PAGE_SHIFT;
	स्थिर पूर्णांक nr_pages = end - start;
	bool is_vदो_स्मृति = is_vदो_स्मृति_addr(data);
	काष्ठा page *page;
	पूर्णांक offset, i;
	काष्ठा bio *bio;

	bio = bio_kदो_स्मृति(gfp_mask, nr_pages);
	अगर (!bio)
		वापस ERR_PTR(-ENOMEM);

	अगर (is_vदो_स्मृति) अणु
		flush_kernel_vmap_range(data, len);
		bio->bi_निजी = data;
	पूर्ण

	offset = offset_in_page(kaddr);
	क्रम (i = 0; i < nr_pages; i++) अणु
		अचिन्हित पूर्णांक bytes = PAGE_SIZE - offset;

		अगर (len <= 0)
			अवरोध;

		अगर (bytes > len)
			bytes = len;

		अगर (!is_vदो_स्मृति)
			page = virt_to_page(data);
		अन्यथा
			page = vदो_स्मृति_to_page(data);
		अगर (bio_add_pc_page(q, bio, page, bytes,
				    offset) < bytes) अणु
			/* we करोn't support partial mappings */
			bio_put(bio);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		data += bytes;
		len -= bytes;
		offset = 0;
	पूर्ण

	bio->bi_end_io = bio_map_kern_endio;
	वापस bio;
पूर्ण

अटल व्योम bio_copy_kern_endio(काष्ठा bio *bio)
अणु
	bio_मुक्त_pages(bio);
	bio_put(bio);
पूर्ण

अटल व्योम bio_copy_kern_endio_पढ़ो(काष्ठा bio *bio)
अणु
	अक्षर *p = bio->bi_निजी;
	काष्ठा bio_vec *bvec;
	काष्ठा bvec_iter_all iter_all;

	bio_क्रम_each_segment_all(bvec, bio, iter_all) अणु
		स_नकल(p, page_address(bvec->bv_page), bvec->bv_len);
		p += bvec->bv_len;
	पूर्ण

	bio_copy_kern_endio(bio);
पूर्ण

/**
 *	bio_copy_kern	-	copy kernel address पूर्णांकo bio
 *	@q: the काष्ठा request_queue क्रम the bio
 *	@data: poपूर्णांकer to buffer to copy
 *	@len: length in bytes
 *	@gfp_mask: allocation flags क्रम bio and page allocation
 *	@पढ़ोing: data direction is READ
 *
 *	copy the kernel address पूर्णांकo a bio suitable क्रम io to a block
 *	device. Returns an error poपूर्णांकer in हाल of error.
 */
अटल काष्ठा bio *bio_copy_kern(काष्ठा request_queue *q, व्योम *data,
		अचिन्हित पूर्णांक len, gfp_t gfp_mask, पूर्णांक पढ़ोing)
अणु
	अचिन्हित दीर्घ kaddr = (अचिन्हित दीर्घ)data;
	अचिन्हित दीर्घ end = (kaddr + len + PAGE_SIZE - 1) >> PAGE_SHIFT;
	अचिन्हित दीर्घ start = kaddr >> PAGE_SHIFT;
	काष्ठा bio *bio;
	व्योम *p = data;
	पूर्णांक nr_pages = 0;

	/*
	 * Overflow, पात
	 */
	अगर (end < start)
		वापस ERR_PTR(-EINVAL);

	nr_pages = end - start;
	bio = bio_kदो_स्मृति(gfp_mask, nr_pages);
	अगर (!bio)
		वापस ERR_PTR(-ENOMEM);

	जबतक (len) अणु
		काष्ठा page *page;
		अचिन्हित पूर्णांक bytes = PAGE_SIZE;

		अगर (bytes > len)
			bytes = len;

		page = alloc_page(GFP_NOIO | gfp_mask);
		अगर (!page)
			जाओ cleanup;

		अगर (!पढ़ोing)
			स_नकल(page_address(page), p, bytes);

		अगर (bio_add_pc_page(q, bio, page, bytes, 0) < bytes)
			अवरोध;

		len -= bytes;
		p += bytes;
	पूर्ण

	अगर (पढ़ोing) अणु
		bio->bi_end_io = bio_copy_kern_endio_पढ़ो;
		bio->bi_निजी = data;
	पूर्ण अन्यथा अणु
		bio->bi_end_io = bio_copy_kern_endio;
	पूर्ण

	वापस bio;

cleanup:
	bio_मुक्त_pages(bio);
	bio_put(bio);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

/*
 * Append a bio to a passthrough request.  Only works अगर the bio can be merged
 * पूर्णांकo the request based on the driver स्थिरraपूर्णांकs.
 */
पूर्णांक blk_rq_append_bio(काष्ठा request *rq, काष्ठा bio *bio)
अणु
	काष्ठा bvec_iter iter;
	काष्ठा bio_vec bv;
	अचिन्हित पूर्णांक nr_segs = 0;

	bio_क्रम_each_bvec(bv, bio, iter)
		nr_segs++;

	अगर (!rq->bio) अणु
		blk_rq_bio_prep(rq, bio, nr_segs);
	पूर्ण अन्यथा अणु
		अगर (!ll_back_merge_fn(rq, bio, nr_segs))
			वापस -EINVAL;
		rq->biotail->bi_next = bio;
		rq->biotail = bio;
		rq->__data_len += (bio)->bi_iter.bi_size;
		bio_crypt_मुक्त_ctx(bio);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(blk_rq_append_bio);

/**
 * blk_rq_map_user_iov - map user data to a request, क्रम passthrough requests
 * @q:		request queue where request should be inserted
 * @rq:		request to map data to
 * @map_data:   poपूर्णांकer to the rq_map_data holding pages (अगर necessary)
 * @iter:	iovec iterator
 * @gfp_mask:	memory allocation flags
 *
 * Description:
 *    Data will be mapped directly क्रम zero copy I/O, अगर possible. Otherwise
 *    a kernel bounce buffer is used.
 *
 *    A matching blk_rq_unmap_user() must be issued at the end of I/O, जबतक
 *    still in process context.
 */
पूर्णांक blk_rq_map_user_iov(काष्ठा request_queue *q, काष्ठा request *rq,
			काष्ठा rq_map_data *map_data,
			स्थिर काष्ठा iov_iter *iter, gfp_t gfp_mask)
अणु
	bool copy = false;
	अचिन्हित दीर्घ align = q->dma_pad_mask | queue_dma_alignment(q);
	काष्ठा bio *bio = शून्य;
	काष्ठा iov_iter i;
	पूर्णांक ret = -EINVAL;

	अगर (!iter_is_iovec(iter))
		जाओ fail;

	अगर (map_data)
		copy = true;
	अन्यथा अगर (blk_queue_may_bounce(q))
		copy = true;
	अन्यथा अगर (iov_iter_alignment(iter) & align)
		copy = true;
	अन्यथा अगर (queue_virt_boundary(q))
		copy = queue_virt_boundary(q) & iov_iter_gap_alignment(iter);

	i = *iter;
	करो अणु
		अगर (copy)
			ret = bio_copy_user_iov(rq, map_data, &i, gfp_mask);
		अन्यथा
			ret = bio_map_user_iov(rq, &i, gfp_mask);
		अगर (ret)
			जाओ unmap_rq;
		अगर (!bio)
			bio = rq->bio;
	पूर्ण जबतक (iov_iter_count(&i));

	वापस 0;

unmap_rq:
	blk_rq_unmap_user(bio);
fail:
	rq->bio = शून्य;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(blk_rq_map_user_iov);

पूर्णांक blk_rq_map_user(काष्ठा request_queue *q, काष्ठा request *rq,
		    काष्ठा rq_map_data *map_data, व्योम __user *ubuf,
		    अचिन्हित दीर्घ len, gfp_t gfp_mask)
अणु
	काष्ठा iovec iov;
	काष्ठा iov_iter i;
	पूर्णांक ret = import_single_range(rq_data_dir(rq), ubuf, len, &iov, &i);

	अगर (unlikely(ret < 0))
		वापस ret;

	वापस blk_rq_map_user_iov(q, rq, map_data, &i, gfp_mask);
पूर्ण
EXPORT_SYMBOL(blk_rq_map_user);

/**
 * blk_rq_unmap_user - unmap a request with user data
 * @bio:	       start of bio list
 *
 * Description:
 *    Unmap a rq previously mapped by blk_rq_map_user(). The caller must
 *    supply the original rq->bio from the blk_rq_map_user() वापस, since
 *    the I/O completion may have changed rq->bio.
 */
पूर्णांक blk_rq_unmap_user(काष्ठा bio *bio)
अणु
	काष्ठा bio *next_bio;
	पूर्णांक ret = 0, ret2;

	जबतक (bio) अणु
		अगर (bio->bi_निजी) अणु
			ret2 = bio_uncopy_user(bio);
			अगर (ret2 && !ret)
				ret = ret2;
		पूर्ण अन्यथा अणु
			bio_release_pages(bio, bio_data_dir(bio) == READ);
		पूर्ण

		next_bio = bio;
		bio = bio->bi_next;
		bio_put(next_bio);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(blk_rq_unmap_user);

/**
 * blk_rq_map_kern - map kernel data to a request, क्रम passthrough requests
 * @q:		request queue where request should be inserted
 * @rq:		request to fill
 * @kbuf:	the kernel buffer
 * @len:	length of user data
 * @gfp_mask:	memory allocation flags
 *
 * Description:
 *    Data will be mapped directly अगर possible. Otherwise a bounce
 *    buffer is used. Can be called multiple बार to append multiple
 *    buffers.
 */
पूर्णांक blk_rq_map_kern(काष्ठा request_queue *q, काष्ठा request *rq, व्योम *kbuf,
		    अचिन्हित पूर्णांक len, gfp_t gfp_mask)
अणु
	पूर्णांक पढ़ोing = rq_data_dir(rq) == READ;
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) kbuf;
	काष्ठा bio *bio;
	पूर्णांक ret;

	अगर (len > (queue_max_hw_sectors(q) << 9))
		वापस -EINVAL;
	अगर (!len || !kbuf)
		वापस -EINVAL;

	अगर (!blk_rq_aligned(q, addr, len) || object_is_on_stack(kbuf) ||
	    blk_queue_may_bounce(q))
		bio = bio_copy_kern(q, kbuf, len, gfp_mask, पढ़ोing);
	अन्यथा
		bio = bio_map_kern(q, kbuf, len, gfp_mask);

	अगर (IS_ERR(bio))
		वापस PTR_ERR(bio);

	bio->bi_opf &= ~REQ_OP_MASK;
	bio->bi_opf |= req_op(rq);

	ret = blk_rq_append_bio(rq, bio);
	अगर (unlikely(ret))
		bio_put(bio);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(blk_rq_map_kern);
