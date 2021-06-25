<शैली गुरु>
/*
 * Copyright (c) 2007, 2020 Oracle and/or its affiliates.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
#समावेश <linux/pagemap.h>
#समावेश <linux/slab.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/dma-mapping.h> /* क्रम DMA_*_DEVICE */

#समावेश "rds.h"

/*
 * XXX
 *  - build with sparse
 *  - should we detect duplicate keys on a socket?  hmm.
 *  - an rdma is an mlock, apply rlimit?
 */

/*
 * get the number of pages by looking at the page indices that the start and
 * end addresses fall in.
 *
 * Returns 0 अगर the vec is invalid.  It is invalid अगर the number of bytes
 * causes the address to wrap or overflows an अचिन्हित पूर्णांक.  This comes
 * from being stored in the 'length' member of 'struct scatterlist'.
 */
अटल अचिन्हित पूर्णांक rds_pages_in_vec(काष्ठा rds_iovec *vec)
अणु
	अगर ((vec->addr + vec->bytes <= vec->addr) ||
	    (vec->bytes > (u64)अच_पूर्णांक_उच्च))
		वापस 0;

	वापस ((vec->addr + vec->bytes + PAGE_SIZE - 1) >> PAGE_SHIFT) -
		(vec->addr >> PAGE_SHIFT);
पूर्ण

अटल काष्ठा rds_mr *rds_mr_tree_walk(काष्ठा rb_root *root, u64 key,
				       काष्ठा rds_mr *insert)
अणु
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा rds_mr *mr;

	जबतक (*p) अणु
		parent = *p;
		mr = rb_entry(parent, काष्ठा rds_mr, r_rb_node);

		अगर (key < mr->r_key)
			p = &(*p)->rb_left;
		अन्यथा अगर (key > mr->r_key)
			p = &(*p)->rb_right;
		अन्यथा
			वापस mr;
	पूर्ण

	अगर (insert) अणु
		rb_link_node(&insert->r_rb_node, parent, p);
		rb_insert_color(&insert->r_rb_node, root);
		kref_get(&insert->r_kref);
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Destroy the transport-specअगरic part of a MR.
 */
अटल व्योम rds_destroy_mr(काष्ठा rds_mr *mr)
अणु
	काष्ठा rds_sock *rs = mr->r_sock;
	व्योम *trans_निजी = शून्य;
	अचिन्हित दीर्घ flags;

	rdsdebug("RDS: destroy mr key is %x refcnt %u\n",
		 mr->r_key, kref_पढ़ो(&mr->r_kref));

	spin_lock_irqsave(&rs->rs_rdma_lock, flags);
	अगर (!RB_EMPTY_NODE(&mr->r_rb_node))
		rb_erase(&mr->r_rb_node, &rs->rs_rdma_keys);
	trans_निजी = mr->r_trans_निजी;
	mr->r_trans_निजी = शून्य;
	spin_unlock_irqrestore(&rs->rs_rdma_lock, flags);

	अगर (trans_निजी)
		mr->r_trans->मुक्त_mr(trans_निजी, mr->r_invalidate);
पूर्ण

व्योम __rds_put_mr_final(काष्ठा kref *kref)
अणु
	काष्ठा rds_mr *mr = container_of(kref, काष्ठा rds_mr, r_kref);

	rds_destroy_mr(mr);
	kमुक्त(mr);
पूर्ण

/*
 * By the समय this is called we can't have any more ioctls called on
 * the socket so we करोn't need to worry about racing with others.
 */
व्योम rds_rdma_drop_keys(काष्ठा rds_sock *rs)
अणु
	काष्ठा rds_mr *mr;
	काष्ठा rb_node *node;
	अचिन्हित दीर्घ flags;

	/* Release any MRs associated with this socket */
	spin_lock_irqsave(&rs->rs_rdma_lock, flags);
	जबतक ((node = rb_first(&rs->rs_rdma_keys))) अणु
		mr = rb_entry(node, काष्ठा rds_mr, r_rb_node);
		अगर (mr->r_trans == rs->rs_transport)
			mr->r_invalidate = 0;
		rb_erase(&mr->r_rb_node, &rs->rs_rdma_keys);
		RB_CLEAR_NODE(&mr->r_rb_node);
		spin_unlock_irqrestore(&rs->rs_rdma_lock, flags);
		kref_put(&mr->r_kref, __rds_put_mr_final);
		spin_lock_irqsave(&rs->rs_rdma_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&rs->rs_rdma_lock, flags);

	अगर (rs->rs_transport && rs->rs_transport->flush_mrs)
		rs->rs_transport->flush_mrs();
पूर्ण

/*
 * Helper function to pin user pages.
 */
अटल पूर्णांक rds_pin_pages(अचिन्हित दीर्घ user_addr, अचिन्हित पूर्णांक nr_pages,
			काष्ठा page **pages, पूर्णांक ग_लिखो)
अणु
	अचिन्हित पूर्णांक gup_flags = FOLL_LONGTERM;
	पूर्णांक ret;

	अगर (ग_लिखो)
		gup_flags |= FOLL_WRITE;

	ret = pin_user_pages_fast(user_addr, nr_pages, gup_flags, pages);
	अगर (ret >= 0 && ret < nr_pages) अणु
		unpin_user_pages(pages, ret);
		ret = -EFAULT;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __rds_rdma_map(काष्ठा rds_sock *rs, काष्ठा rds_get_mr_args *args,
			  u64 *cookie_ret, काष्ठा rds_mr **mr_ret,
			  काष्ठा rds_conn_path *cp)
अणु
	काष्ठा rds_mr *mr = शून्य, *found;
	काष्ठा scatterlist *sg = शून्य;
	अचिन्हित पूर्णांक nr_pages;
	काष्ठा page **pages = शून्य;
	व्योम *trans_निजी;
	अचिन्हित दीर्घ flags;
	rds_rdma_cookie_t cookie;
	अचिन्हित पूर्णांक nents = 0;
	पूर्णांक need_odp = 0;
	दीर्घ i;
	पूर्णांक ret;

	अगर (ipv6_addr_any(&rs->rs_bound_addr) || !rs->rs_transport) अणु
		ret = -ENOTCONN; /* XXX not a great त्रुटि_सं */
		जाओ out;
	पूर्ण

	अगर (!rs->rs_transport->get_mr) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	/* If the combination of the addr and size requested क्रम this memory
	 * region causes an पूर्णांकeger overflow, वापस error.
	 */
	अगर (((args->vec.addr + args->vec.bytes) < args->vec.addr) ||
	    PAGE_ALIGN(args->vec.addr + args->vec.bytes) <
		    (args->vec.addr + args->vec.bytes)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!can_करो_mlock()) अणु
		ret = -EPERM;
		जाओ out;
	पूर्ण

	nr_pages = rds_pages_in_vec(&args->vec);
	अगर (nr_pages == 0) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Restrict the size of mr irrespective of underlying transport
	 * To account क्रम unaligned mr regions, subtract one from nr_pages
	 */
	अगर ((nr_pages - 1) > (RDS_MAX_MSG_SIZE >> PAGE_SHIFT)) अणु
		ret = -EMSGSIZE;
		जाओ out;
	पूर्ण

	rdsdebug("RDS: get_mr addr %llx len %llu nr_pages %u\n",
		args->vec.addr, args->vec.bytes, nr_pages);

	/* XXX clamp nr_pages to limit the size of this alloc? */
	pages = kसुस्मृति(nr_pages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!pages) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	mr = kzalloc(माप(काष्ठा rds_mr), GFP_KERNEL);
	अगर (!mr) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	kref_init(&mr->r_kref);
	RB_CLEAR_NODE(&mr->r_rb_node);
	mr->r_trans = rs->rs_transport;
	mr->r_sock = rs;

	अगर (args->flags & RDS_RDMA_USE_ONCE)
		mr->r_use_once = 1;
	अगर (args->flags & RDS_RDMA_INVALIDATE)
		mr->r_invalidate = 1;
	अगर (args->flags & RDS_RDMA_READWRITE)
		mr->r_ग_लिखो = 1;

	/*
	 * Pin the pages that make up the user buffer and transfer the page
	 * poपूर्णांकers to the mr's sg array.  We check to see if we've mapped
	 * the whole region after transferring the partial page references
	 * to the sg array so that we can have one page ref cleanup path.
	 *
	 * For now we have no flag that tells us whether the mapping is
	 * r/o or r/w. We need to assume r/w, or we'll करो a lot of RDMA to
	 * the zero page.
	 */
	ret = rds_pin_pages(args->vec.addr, nr_pages, pages, 1);
	अगर (ret == -EOPNOTSUPP) अणु
		need_odp = 1;
	पूर्ण अन्यथा अगर (ret <= 0) अणु
		जाओ out;
	पूर्ण अन्यथा अणु
		nents = ret;
		sg = kदो_स्मृति_array(nents, माप(*sg), GFP_KERNEL);
		अगर (!sg) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		WARN_ON(!nents);
		sg_init_table(sg, nents);

		/* Stick all pages पूर्णांकo the scatterlist */
		क्रम (i = 0 ; i < nents; i++)
			sg_set_page(&sg[i], pages[i], PAGE_SIZE, 0);

		rdsdebug("RDS: trans_private nents is %u\n", nents);
	पूर्ण
	/* Obtain a transport specअगरic MR. If this succeeds, the
	 * s/g list is now owned by the MR.
	 * Note that dma_map() implies that pending ग_लिखोs are
	 * flushed to RAM, so no dma_sync is needed here. */
	trans_निजी = rs->rs_transport->get_mr(
		sg, nents, rs, &mr->r_key, cp ? cp->cp_conn : शून्य,
		args->vec.addr, args->vec.bytes,
		need_odp ? ODP_ZEROBASED : ODP_NOT_NEEDED);

	अगर (IS_ERR(trans_निजी)) अणु
		/* In ODP हाल, we करोn't GUP pages, so don't need
		 * to release anything.
		 */
		अगर (!need_odp) अणु
			unpin_user_pages(pages, nr_pages);
			kमुक्त(sg);
		पूर्ण
		ret = PTR_ERR(trans_निजी);
		जाओ out;
	पूर्ण

	mr->r_trans_निजी = trans_निजी;

	rdsdebug("RDS: get_mr put_user key is %x cookie_addr %p\n",
	       mr->r_key, (व्योम *)(अचिन्हित दीर्घ) args->cookie_addr);

	/* The user may pass us an unaligned address, but we can only
	 * map page aligned regions. So we keep the offset, and build
	 * a 64bit cookie containing <R_Key, offset> and pass that
	 * around. */
	अगर (need_odp)
		cookie = rds_rdma_make_cookie(mr->r_key, 0);
	अन्यथा
		cookie = rds_rdma_make_cookie(mr->r_key,
					      args->vec.addr & ~PAGE_MASK);
	अगर (cookie_ret)
		*cookie_ret = cookie;

	अगर (args->cookie_addr &&
	    put_user(cookie, (u64 __user *)(अचिन्हित दीर्घ)args->cookie_addr)) अणु
		अगर (!need_odp) अणु
			unpin_user_pages(pages, nr_pages);
			kमुक्त(sg);
		पूर्ण
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	/* Inserting the new MR पूर्णांकo the rbtree bumps its
	 * reference count. */
	spin_lock_irqsave(&rs->rs_rdma_lock, flags);
	found = rds_mr_tree_walk(&rs->rs_rdma_keys, mr->r_key, mr);
	spin_unlock_irqrestore(&rs->rs_rdma_lock, flags);

	BUG_ON(found && found != mr);

	rdsdebug("RDS: get_mr key is %x\n", mr->r_key);
	अगर (mr_ret) अणु
		kref_get(&mr->r_kref);
		*mr_ret = mr;
	पूर्ण

	ret = 0;
out:
	kमुक्त(pages);
	अगर (mr)
		kref_put(&mr->r_kref, __rds_put_mr_final);
	वापस ret;
पूर्ण

पूर्णांक rds_get_mr(काष्ठा rds_sock *rs, sockptr_t optval, पूर्णांक optlen)
अणु
	काष्ठा rds_get_mr_args args;

	अगर (optlen != माप(काष्ठा rds_get_mr_args))
		वापस -EINVAL;

	अगर (copy_from_sockptr(&args, optval, माप(काष्ठा rds_get_mr_args)))
		वापस -EFAULT;

	वापस __rds_rdma_map(rs, &args, शून्य, शून्य, शून्य);
पूर्ण

पूर्णांक rds_get_mr_क्रम_dest(काष्ठा rds_sock *rs, sockptr_t optval, पूर्णांक optlen)
अणु
	काष्ठा rds_get_mr_क्रम_dest_args args;
	काष्ठा rds_get_mr_args new_args;

	अगर (optlen != माप(काष्ठा rds_get_mr_क्रम_dest_args))
		वापस -EINVAL;

	अगर (copy_from_sockptr(&args, optval,
			   माप(काष्ठा rds_get_mr_क्रम_dest_args)))
		वापस -EFAULT;

	/*
	 * Initially, just behave like get_mr().
	 * TODO: Implement get_mr as wrapper around this
	 *	 and deprecate it.
	 */
	new_args.vec = args.vec;
	new_args.cookie_addr = args.cookie_addr;
	new_args.flags = args.flags;

	वापस __rds_rdma_map(rs, &new_args, शून्य, शून्य, शून्य);
पूर्ण

/*
 * Free the MR indicated by the given R_Key
 */
पूर्णांक rds_मुक्त_mr(काष्ठा rds_sock *rs, sockptr_t optval, पूर्णांक optlen)
अणु
	काष्ठा rds_मुक्त_mr_args args;
	काष्ठा rds_mr *mr;
	अचिन्हित दीर्घ flags;

	अगर (optlen != माप(काष्ठा rds_मुक्त_mr_args))
		वापस -EINVAL;

	अगर (copy_from_sockptr(&args, optval, माप(काष्ठा rds_मुक्त_mr_args)))
		वापस -EFAULT;

	/* Special हाल - a null cookie means flush all unused MRs */
	अगर (args.cookie == 0) अणु
		अगर (!rs->rs_transport || !rs->rs_transport->flush_mrs)
			वापस -EINVAL;
		rs->rs_transport->flush_mrs();
		वापस 0;
	पूर्ण

	/* Look up the MR given its R_key and हटाओ it from the rbtree
	 * so nobody अन्यथा finds it.
	 * This should also prevent races with rds_rdma_unuse.
	 */
	spin_lock_irqsave(&rs->rs_rdma_lock, flags);
	mr = rds_mr_tree_walk(&rs->rs_rdma_keys, rds_rdma_cookie_key(args.cookie), शून्य);
	अगर (mr) अणु
		rb_erase(&mr->r_rb_node, &rs->rs_rdma_keys);
		RB_CLEAR_NODE(&mr->r_rb_node);
		अगर (args.flags & RDS_RDMA_INVALIDATE)
			mr->r_invalidate = 1;
	पूर्ण
	spin_unlock_irqrestore(&rs->rs_rdma_lock, flags);

	अगर (!mr)
		वापस -EINVAL;

	kref_put(&mr->r_kref, __rds_put_mr_final);
	वापस 0;
पूर्ण

/*
 * This is called when we receive an extension header that
 * tells us this MR was used. It allows us to implement
 * use_once semantics
 */
व्योम rds_rdma_unuse(काष्ठा rds_sock *rs, u32 r_key, पूर्णांक क्रमce)
अणु
	काष्ठा rds_mr *mr;
	अचिन्हित दीर्घ flags;
	पूर्णांक zot_me = 0;

	spin_lock_irqsave(&rs->rs_rdma_lock, flags);
	mr = rds_mr_tree_walk(&rs->rs_rdma_keys, r_key, शून्य);
	अगर (!mr) अणु
		pr_debug("rds: trying to unuse MR with unknown r_key %u!\n",
			 r_key);
		spin_unlock_irqrestore(&rs->rs_rdma_lock, flags);
		वापस;
	पूर्ण

	/* Get a reference so that the MR won't go away beक्रमe calling
	 * sync_mr() below.
	 */
	kref_get(&mr->r_kref);

	/* If it is going to be मुक्तd, हटाओ it from the tree now so
	 * that no other thपढ़ो can find it and मुक्त it.
	 */
	अगर (mr->r_use_once || क्रमce) अणु
		rb_erase(&mr->r_rb_node, &rs->rs_rdma_keys);
		RB_CLEAR_NODE(&mr->r_rb_node);
		zot_me = 1;
	पूर्ण
	spin_unlock_irqrestore(&rs->rs_rdma_lock, flags);

	/* May have to issue a dma_sync on this memory region.
	 * Note we could aव्योम this अगर the operation was a RDMA READ,
	 * but at this poपूर्णांक we can't tell. */
	अगर (mr->r_trans->sync_mr)
		mr->r_trans->sync_mr(mr->r_trans_निजी, DMA_FROM_DEVICE);

	/* Release the reference held above. */
	kref_put(&mr->r_kref, __rds_put_mr_final);

	/* If the MR was marked as invalidate, this will
	 * trigger an async flush. */
	अगर (zot_me)
		kref_put(&mr->r_kref, __rds_put_mr_final);
पूर्ण

व्योम rds_rdma_मुक्त_op(काष्ठा rm_rdma_op *ro)
अणु
	अचिन्हित पूर्णांक i;

	अगर (ro->op_odp_mr) अणु
		kref_put(&ro->op_odp_mr->r_kref, __rds_put_mr_final);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ro->op_nents; i++) अणु
			काष्ठा page *page = sg_page(&ro->op_sg[i]);

			/* Mark page dirty अगर it was possibly modअगरied, which
			 * is the हाल क्रम a RDMA_READ which copies from remote
			 * to local memory
			 */
			unpin_user_pages_dirty_lock(&page, 1, !ro->op_ग_लिखो);
		पूर्ण
	पूर्ण

	kमुक्त(ro->op_notअगरier);
	ro->op_notअगरier = शून्य;
	ro->op_active = 0;
	ro->op_odp_mr = शून्य;
पूर्ण

व्योम rds_atomic_मुक्त_op(काष्ठा rm_atomic_op *ao)
अणु
	काष्ठा page *page = sg_page(ao->op_sg);

	/* Mark page dirty अगर it was possibly modअगरied, which
	 * is the हाल क्रम a RDMA_READ which copies from remote
	 * to local memory */
	unpin_user_pages_dirty_lock(&page, 1, true);

	kमुक्त(ao->op_notअगरier);
	ao->op_notअगरier = शून्य;
	ao->op_active = 0;
पूर्ण


/*
 * Count the number of pages needed to describe an incoming iovec array.
 */
अटल पूर्णांक rds_rdma_pages(काष्ठा rds_iovec iov[], पूर्णांक nr_iovecs)
अणु
	पूर्णांक tot_pages = 0;
	अचिन्हित पूर्णांक nr_pages;
	अचिन्हित पूर्णांक i;

	/* figure out the number of pages in the vector */
	क्रम (i = 0; i < nr_iovecs; i++) अणु
		nr_pages = rds_pages_in_vec(&iov[i]);
		अगर (nr_pages == 0)
			वापस -EINVAL;

		tot_pages += nr_pages;

		/*
		 * nr_pages क्रम one entry is limited to (अच_पूर्णांक_उच्च>>PAGE_SHIFT)+1,
		 * so tot_pages cannot overflow without first going negative.
		 */
		अगर (tot_pages < 0)
			वापस -EINVAL;
	पूर्ण

	वापस tot_pages;
पूर्ण

पूर्णांक rds_rdma_extra_size(काष्ठा rds_rdma_args *args,
			काष्ठा rds_iov_vector *iov)
अणु
	काष्ठा rds_iovec *vec;
	काष्ठा rds_iovec __user *local_vec;
	पूर्णांक tot_pages = 0;
	अचिन्हित पूर्णांक nr_pages;
	अचिन्हित पूर्णांक i;

	local_vec = (काष्ठा rds_iovec __user *)(अचिन्हित दीर्घ) args->local_vec_addr;

	अगर (args->nr_local == 0)
		वापस -EINVAL;

	अगर (args->nr_local > UIO_MAXIOV)
		वापस -EMSGSIZE;

	iov->iov = kसुस्मृति(args->nr_local,
			   माप(काष्ठा rds_iovec),
			   GFP_KERNEL);
	अगर (!iov->iov)
		वापस -ENOMEM;

	vec = &iov->iov[0];

	अगर (copy_from_user(vec, local_vec, args->nr_local *
			   माप(काष्ठा rds_iovec)))
		वापस -EFAULT;
	iov->len = args->nr_local;

	/* figure out the number of pages in the vector */
	क्रम (i = 0; i < args->nr_local; i++, vec++) अणु

		nr_pages = rds_pages_in_vec(vec);
		अगर (nr_pages == 0)
			वापस -EINVAL;

		tot_pages += nr_pages;

		/*
		 * nr_pages क्रम one entry is limited to (अच_पूर्णांक_उच्च>>PAGE_SHIFT)+1,
		 * so tot_pages cannot overflow without first going negative.
		 */
		अगर (tot_pages < 0)
			वापस -EINVAL;
	पूर्ण

	वापस tot_pages * माप(काष्ठा scatterlist);
पूर्ण

/*
 * The application asks क्रम a RDMA transfer.
 * Extract all arguments and set up the rdma_op
 */
पूर्णांक rds_cmsg_rdma_args(काष्ठा rds_sock *rs, काष्ठा rds_message *rm,
		       काष्ठा cmsghdr *cmsg,
		       काष्ठा rds_iov_vector *vec)
अणु
	काष्ठा rds_rdma_args *args;
	काष्ठा rm_rdma_op *op = &rm->rdma;
	पूर्णांक nr_pages;
	अचिन्हित पूर्णांक nr_bytes;
	काष्ठा page **pages = शून्य;
	काष्ठा rds_iovec *iovs;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक ret = 0;
	bool odp_supported = true;

	अगर (cmsg->cmsg_len < CMSG_LEN(माप(काष्ठा rds_rdma_args))
	    || rm->rdma.op_active)
		वापस -EINVAL;

	args = CMSG_DATA(cmsg);

	अगर (ipv6_addr_any(&rs->rs_bound_addr)) अणु
		ret = -ENOTCONN; /* XXX not a great त्रुटि_सं */
		जाओ out_ret;
	पूर्ण

	अगर (args->nr_local > UIO_MAXIOV) अणु
		ret = -EMSGSIZE;
		जाओ out_ret;
	पूर्ण

	अगर (vec->len != args->nr_local) अणु
		ret = -EINVAL;
		जाओ out_ret;
	पूर्ण
	/* odp-mr is not supported क्रम multiple requests within one message */
	अगर (args->nr_local != 1)
		odp_supported = false;

	iovs = vec->iov;

	nr_pages = rds_rdma_pages(iovs, args->nr_local);
	अगर (nr_pages < 0) अणु
		ret = -EINVAL;
		जाओ out_ret;
	पूर्ण

	pages = kसुस्मृति(nr_pages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!pages) अणु
		ret = -ENOMEM;
		जाओ out_ret;
	पूर्ण

	op->op_ग_लिखो = !!(args->flags & RDS_RDMA_READWRITE);
	op->op_fence = !!(args->flags & RDS_RDMA_FENCE);
	op->op_notअगरy = !!(args->flags & RDS_RDMA_NOTIFY_ME);
	op->op_silent = !!(args->flags & RDS_RDMA_SILENT);
	op->op_active = 1;
	op->op_recverr = rs->rs_recverr;
	op->op_odp_mr = शून्य;

	WARN_ON(!nr_pages);
	op->op_sg = rds_message_alloc_sgs(rm, nr_pages);
	अगर (IS_ERR(op->op_sg)) अणु
		ret = PTR_ERR(op->op_sg);
		जाओ out_pages;
	पूर्ण

	अगर (op->op_notअगरy || op->op_recverr) अणु
		/* We allocate an uninitialized notअगरier here, because
		 * we करोn't want to करो that in the completion handler. We
		 * would have to use GFP_ATOMIC there, and करोn't want to deal
		 * with failed allocations.
		 */
		op->op_notअगरier = kदो_स्मृति(माप(काष्ठा rds_notअगरier), GFP_KERNEL);
		अगर (!op->op_notअगरier) अणु
			ret = -ENOMEM;
			जाओ out_pages;
		पूर्ण
		op->op_notअगरier->n_user_token = args->user_token;
		op->op_notअगरier->n_status = RDS_RDMA_SUCCESS;
	पूर्ण

	/* The cookie contains the R_Key of the remote memory region, and
	 * optionally an offset पूर्णांकo it. This is how we implement RDMA पूर्णांकo
	 * unaligned memory.
	 * When setting up the RDMA, we need to add that offset to the
	 * destination address (which is really an offset पूर्णांकo the MR)
	 * FIXME: We may want to move this पूर्णांकo ib_rdma.c
	 */
	op->op_rkey = rds_rdma_cookie_key(args->cookie);
	op->op_remote_addr = args->remote_vec.addr + rds_rdma_cookie_offset(args->cookie);

	nr_bytes = 0;

	rdsdebug("RDS: rdma prepare nr_local %llu rva %llx rkey %x\n",
	       (अचिन्हित दीर्घ दीर्घ)args->nr_local,
	       (अचिन्हित दीर्घ दीर्घ)args->remote_vec.addr,
	       op->op_rkey);

	क्रम (i = 0; i < args->nr_local; i++) अणु
		काष्ठा rds_iovec *iov = &iovs[i];
		/* करोn't need to check, rds_rdma_pages() verअगरied nr will be +nonzero */
		अचिन्हित पूर्णांक nr = rds_pages_in_vec(iov);

		rs->rs_user_addr = iov->addr;
		rs->rs_user_bytes = iov->bytes;

		/* If it's a WRITE operation, we want to pin the pages क्रम पढ़ोing.
		 * If it's a READ operation, we need to pin the pages क्रम writing.
		 */
		ret = rds_pin_pages(iov->addr, nr, pages, !op->op_ग_लिखो);
		अगर ((!odp_supported && ret <= 0) ||
		    (odp_supported && ret <= 0 && ret != -EOPNOTSUPP))
			जाओ out_pages;

		अगर (ret == -EOPNOTSUPP) अणु
			काष्ठा rds_mr *local_odp_mr;

			अगर (!rs->rs_transport->get_mr) अणु
				ret = -EOPNOTSUPP;
				जाओ out_pages;
			पूर्ण
			local_odp_mr =
				kzalloc(माप(*local_odp_mr), GFP_KERNEL);
			अगर (!local_odp_mr) अणु
				ret = -ENOMEM;
				जाओ out_pages;
			पूर्ण
			RB_CLEAR_NODE(&local_odp_mr->r_rb_node);
			kref_init(&local_odp_mr->r_kref);
			local_odp_mr->r_trans = rs->rs_transport;
			local_odp_mr->r_sock = rs;
			local_odp_mr->r_trans_निजी =
				rs->rs_transport->get_mr(
					शून्य, 0, rs, &local_odp_mr->r_key, शून्य,
					iov->addr, iov->bytes, ODP_VIRTUAL);
			अगर (IS_ERR(local_odp_mr->r_trans_निजी)) अणु
				ret = IS_ERR(local_odp_mr->r_trans_निजी);
				rdsdebug("get_mr ret %d %p\"", ret,
					 local_odp_mr->r_trans_निजी);
				kमुक्त(local_odp_mr);
				ret = -EOPNOTSUPP;
				जाओ out_pages;
			पूर्ण
			rdsdebug("Need odp; local_odp_mr %p trans_private %p\n",
				 local_odp_mr, local_odp_mr->r_trans_निजी);
			op->op_odp_mr = local_odp_mr;
			op->op_odp_addr = iov->addr;
		पूर्ण

		rdsdebug("RDS: nr_bytes %u nr %u iov->bytes %llu iov->addr %llx\n",
			 nr_bytes, nr, iov->bytes, iov->addr);

		nr_bytes += iov->bytes;

		क्रम (j = 0; j < nr; j++) अणु
			अचिन्हित पूर्णांक offset = iov->addr & ~PAGE_MASK;
			काष्ठा scatterlist *sg;

			sg = &op->op_sg[op->op_nents + j];
			sg_set_page(sg, pages[j],
					min_t(अचिन्हित पूर्णांक, iov->bytes, PAGE_SIZE - offset),
					offset);

			sg_dma_len(sg) = sg->length;
			rdsdebug("RDS: sg->offset %x sg->len %x iov->addr %llx iov->bytes %llu\n",
			       sg->offset, sg->length, iov->addr, iov->bytes);

			iov->addr += sg->length;
			iov->bytes -= sg->length;
		पूर्ण

		op->op_nents += nr;
	पूर्ण

	अगर (nr_bytes > args->remote_vec.bytes) अणु
		rdsdebug("RDS nr_bytes %u remote_bytes %u do not match\n",
				nr_bytes,
				(अचिन्हित पूर्णांक) args->remote_vec.bytes);
		ret = -EINVAL;
		जाओ out_pages;
	पूर्ण
	op->op_bytes = nr_bytes;
	ret = 0;

out_pages:
	kमुक्त(pages);
out_ret:
	अगर (ret)
		rds_rdma_मुक्त_op(op);
	अन्यथा
		rds_stats_inc(s_send_rdma);

	वापस ret;
पूर्ण

/*
 * The application wants us to pass an RDMA destination (aka MR)
 * to the remote
 */
पूर्णांक rds_cmsg_rdma_dest(काष्ठा rds_sock *rs, काष्ठा rds_message *rm,
			  काष्ठा cmsghdr *cmsg)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rds_mr *mr;
	u32 r_key;
	पूर्णांक err = 0;

	अगर (cmsg->cmsg_len < CMSG_LEN(माप(rds_rdma_cookie_t)) ||
	    rm->m_rdma_cookie != 0)
		वापस -EINVAL;

	स_नकल(&rm->m_rdma_cookie, CMSG_DATA(cmsg), माप(rm->m_rdma_cookie));

	/* We are reusing a previously mapped MR here. Most likely, the
	 * application has written to the buffer, so we need to explicitly
	 * flush those ग_लिखोs to RAM. Otherwise the HCA may not see them
	 * when करोing a DMA from that buffer.
	 */
	r_key = rds_rdma_cookie_key(rm->m_rdma_cookie);

	spin_lock_irqsave(&rs->rs_rdma_lock, flags);
	mr = rds_mr_tree_walk(&rs->rs_rdma_keys, r_key, शून्य);
	अगर (!mr)
		err = -EINVAL;	/* invalid r_key */
	अन्यथा
		kref_get(&mr->r_kref);
	spin_unlock_irqrestore(&rs->rs_rdma_lock, flags);

	अगर (mr) अणु
		mr->r_trans->sync_mr(mr->r_trans_निजी,
				     DMA_TO_DEVICE);
		rm->rdma.op_rdma_mr = mr;
	पूर्ण
	वापस err;
पूर्ण

/*
 * The application passes us an address range it wants to enable RDMA
 * to/from. We map the area, and save the <R_Key,offset> pair
 * in rm->m_rdma_cookie. This causes it to be sent aदीर्घ to the peer
 * in an extension header.
 */
पूर्णांक rds_cmsg_rdma_map(काष्ठा rds_sock *rs, काष्ठा rds_message *rm,
			  काष्ठा cmsghdr *cmsg)
अणु
	अगर (cmsg->cmsg_len < CMSG_LEN(माप(काष्ठा rds_get_mr_args)) ||
	    rm->m_rdma_cookie != 0)
		वापस -EINVAL;

	वापस __rds_rdma_map(rs, CMSG_DATA(cmsg), &rm->m_rdma_cookie,
			      &rm->rdma.op_rdma_mr, rm->m_conn_path);
पूर्ण

/*
 * Fill in rds_message क्रम an atomic request.
 */
पूर्णांक rds_cmsg_atomic(काष्ठा rds_sock *rs, काष्ठा rds_message *rm,
		    काष्ठा cmsghdr *cmsg)
अणु
	काष्ठा page *page = शून्य;
	काष्ठा rds_atomic_args *args;
	पूर्णांक ret = 0;

	अगर (cmsg->cmsg_len < CMSG_LEN(माप(काष्ठा rds_atomic_args))
	 || rm->atomic.op_active)
		वापस -EINVAL;

	args = CMSG_DATA(cmsg);

	/* Nonmasked & masked cmsg ops converted to masked hw ops */
	चयन (cmsg->cmsg_type) अणु
	हाल RDS_CMSG_ATOMIC_FADD:
		rm->atomic.op_type = RDS_ATOMIC_TYPE_FADD;
		rm->atomic.op_m_fadd.add = args->fadd.add;
		rm->atomic.op_m_fadd.nocarry_mask = 0;
		अवरोध;
	हाल RDS_CMSG_MASKED_ATOMIC_FADD:
		rm->atomic.op_type = RDS_ATOMIC_TYPE_FADD;
		rm->atomic.op_m_fadd.add = args->m_fadd.add;
		rm->atomic.op_m_fadd.nocarry_mask = args->m_fadd.nocarry_mask;
		अवरोध;
	हाल RDS_CMSG_ATOMIC_CSWP:
		rm->atomic.op_type = RDS_ATOMIC_TYPE_CSWP;
		rm->atomic.op_m_cswp.compare = args->cswp.compare;
		rm->atomic.op_m_cswp.swap = args->cswp.swap;
		rm->atomic.op_m_cswp.compare_mask = ~0;
		rm->atomic.op_m_cswp.swap_mask = ~0;
		अवरोध;
	हाल RDS_CMSG_MASKED_ATOMIC_CSWP:
		rm->atomic.op_type = RDS_ATOMIC_TYPE_CSWP;
		rm->atomic.op_m_cswp.compare = args->m_cswp.compare;
		rm->atomic.op_m_cswp.swap = args->m_cswp.swap;
		rm->atomic.op_m_cswp.compare_mask = args->m_cswp.compare_mask;
		rm->atomic.op_m_cswp.swap_mask = args->m_cswp.swap_mask;
		अवरोध;
	शेष:
		BUG(); /* should never happen */
	पूर्ण

	rm->atomic.op_notअगरy = !!(args->flags & RDS_RDMA_NOTIFY_ME);
	rm->atomic.op_silent = !!(args->flags & RDS_RDMA_SILENT);
	rm->atomic.op_active = 1;
	rm->atomic.op_recverr = rs->rs_recverr;
	rm->atomic.op_sg = rds_message_alloc_sgs(rm, 1);
	अगर (IS_ERR(rm->atomic.op_sg)) अणु
		ret = PTR_ERR(rm->atomic.op_sg);
		जाओ err;
	पूर्ण

	/* verअगरy 8 byte-aligned */
	अगर (args->local_addr & 0x7) अणु
		ret = -EFAULT;
		जाओ err;
	पूर्ण

	ret = rds_pin_pages(args->local_addr, 1, &page, 1);
	अगर (ret != 1)
		जाओ err;
	ret = 0;

	sg_set_page(rm->atomic.op_sg, page, 8, offset_in_page(args->local_addr));

	अगर (rm->atomic.op_notअगरy || rm->atomic.op_recverr) अणु
		/* We allocate an uninitialized notअगरier here, because
		 * we करोn't want to करो that in the completion handler. We
		 * would have to use GFP_ATOMIC there, and करोn't want to deal
		 * with failed allocations.
		 */
		rm->atomic.op_notअगरier = kदो_स्मृति(माप(*rm->atomic.op_notअगरier), GFP_KERNEL);
		अगर (!rm->atomic.op_notअगरier) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		rm->atomic.op_notअगरier->n_user_token = args->user_token;
		rm->atomic.op_notअगरier->n_status = RDS_RDMA_SUCCESS;
	पूर्ण

	rm->atomic.op_rkey = rds_rdma_cookie_key(args->cookie);
	rm->atomic.op_remote_addr = args->remote_addr + rds_rdma_cookie_offset(args->cookie);

	वापस ret;
err:
	अगर (page)
		unpin_user_page(page);
	rm->atomic.op_active = 0;
	kमुक्त(rm->atomic.op_notअगरier);

	वापस ret;
पूर्ण
