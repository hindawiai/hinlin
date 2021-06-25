<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* kiocb-using पढ़ो/ग_लिखो
 *
 * Copyright (C) 2021 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/mount.h>
#समावेश <linux/slab.h>
#समावेश <linux/file.h>
#समावेश <linux/uपन.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/netfs.h>
#समावेश "internal.h"

काष्ठा cachefiles_kiocb अणु
	काष्ठा kiocb		iocb;
	refcount_t		ki_refcnt;
	loff_t			start;
	जोड़ अणु
		माप_प्रकार		skipped;
		माप_प्रकार		len;
	पूर्ण;
	netfs_io_terminated_t	term_func;
	व्योम			*term_func_priv;
	bool			was_async;
पूर्ण;

अटल अंतरभूत व्योम cachefiles_put_kiocb(काष्ठा cachefiles_kiocb *ki)
अणु
	अगर (refcount_dec_and_test(&ki->ki_refcnt)) अणु
		fput(ki->iocb.ki_filp);
		kमुक्त(ki);
	पूर्ण
पूर्ण

/*
 * Handle completion of a पढ़ो from the cache.
 */
अटल व्योम cachefiles_पढ़ो_complete(काष्ठा kiocb *iocb, दीर्घ ret, दीर्घ ret2)
अणु
	काष्ठा cachefiles_kiocb *ki = container_of(iocb, काष्ठा cachefiles_kiocb, iocb);

	_enter("%ld,%ld", ret, ret2);

	अगर (ki->term_func) अणु
		अगर (ret >= 0)
			ret += ki->skipped;
		ki->term_func(ki->term_func_priv, ret, ki->was_async);
	पूर्ण

	cachefiles_put_kiocb(ki);
पूर्ण

/*
 * Initiate a पढ़ो from the cache.
 */
अटल पूर्णांक cachefiles_पढ़ो(काष्ठा netfs_cache_resources *cres,
			   loff_t start_pos,
			   काष्ठा iov_iter *iter,
			   bool seek_data,
			   netfs_io_terminated_t term_func,
			   व्योम *term_func_priv)
अणु
	काष्ठा cachefiles_kiocb *ki;
	काष्ठा file *file = cres->cache_priv2;
	अचिन्हित पूर्णांक old_nofs;
	sमाप_प्रकार ret = -ENOBUFS;
	माप_प्रकार len = iov_iter_count(iter), skipped = 0;

	_enter("%pD,%li,%llx,%zx/%llx",
	       file, file_inode(file)->i_ino, start_pos, len,
	       i_size_पढ़ो(file->f_inode));

	/* If the caller asked us to seek क्रम data beक्रमe करोing the पढ़ो, then
	 * we should करो that now.  If we find a gap, we fill it with zeros.
	 */
	अगर (seek_data) अणु
		loff_t off = start_pos, off2;

		off2 = vfs_llseek(file, off, SEEK_DATA);
		अगर (off2 < 0 && off2 >= (loff_t)-MAX_ERRNO && off2 != -ENXIO) अणु
			skipped = 0;
			ret = off2;
			जाओ presubmission_error;
		पूर्ण

		अगर (off2 == -ENXIO || off2 >= start_pos + len) अणु
			/* The region is beyond the खातापूर्ण or there's no more data
			 * in the region, so clear the rest of the buffer and
			 * वापस success.
			 */
			iov_iter_zero(len, iter);
			skipped = len;
			ret = 0;
			जाओ presubmission_error;
		पूर्ण

		skipped = off2 - off;
		iov_iter_zero(skipped, iter);
	पूर्ण

	ret = -ENOBUFS;
	ki = kzalloc(माप(काष्ठा cachefiles_kiocb), GFP_KERNEL);
	अगर (!ki)
		जाओ presubmission_error;

	refcount_set(&ki->ki_refcnt, 2);
	ki->iocb.ki_filp	= file;
	ki->iocb.ki_pos		= start_pos + skipped;
	ki->iocb.ki_flags	= IOCB_सूचीECT;
	ki->iocb.ki_hपूर्णांक	= ki_hपूर्णांक_validate(file_ग_लिखो_hपूर्णांक(file));
	ki->iocb.ki_ioprio	= get_current_ioprio();
	ki->skipped		= skipped;
	ki->term_func		= term_func;
	ki->term_func_priv	= term_func_priv;
	ki->was_async		= true;

	अगर (ki->term_func)
		ki->iocb.ki_complete = cachefiles_पढ़ो_complete;

	get_file(ki->iocb.ki_filp);

	old_nofs = meदो_स्मृति_nofs_save();
	ret = vfs_iocb_iter_पढ़ो(file, &ki->iocb, iter);
	meदो_स्मृति_nofs_restore(old_nofs);
	चयन (ret) अणु
	हाल -EIOCBQUEUED:
		जाओ in_progress;

	हाल -ERESTARTSYS:
	हाल -ERESTARTNOINTR:
	हाल -ERESTARTNOHAND:
	हाल -ERESTART_RESTARTBLOCK:
		/* There's no easy way to restart the syscall since other AIO's
		 * may be alपढ़ोy running. Just fail this IO with EINTR.
		 */
		ret = -EINTR;
		fallthrough;
	शेष:
		ki->was_async = false;
		cachefiles_पढ़ो_complete(&ki->iocb, ret, 0);
		अगर (ret > 0)
			ret = 0;
		अवरोध;
	पूर्ण

in_progress:
	cachefiles_put_kiocb(ki);
	_leave(" = %zd", ret);
	वापस ret;

presubmission_error:
	अगर (term_func)
		term_func(term_func_priv, ret < 0 ? ret : skipped, false);
	वापस ret;
पूर्ण

/*
 * Handle completion of a ग_लिखो to the cache.
 */
अटल व्योम cachefiles_ग_लिखो_complete(काष्ठा kiocb *iocb, दीर्घ ret, दीर्घ ret2)
अणु
	काष्ठा cachefiles_kiocb *ki = container_of(iocb, काष्ठा cachefiles_kiocb, iocb);
	काष्ठा inode *inode = file_inode(ki->iocb.ki_filp);

	_enter("%ld,%ld", ret, ret2);

	/* Tell lockdep we inherited मुक्तze protection from submission thपढ़ो */
	__sb_ग_लिखोrs_acquired(inode->i_sb, SB_FREEZE_WRITE);
	__sb_end_ग_लिखो(inode->i_sb, SB_FREEZE_WRITE);

	अगर (ki->term_func)
		ki->term_func(ki->term_func_priv, ret, ki->was_async);

	cachefiles_put_kiocb(ki);
पूर्ण

/*
 * Initiate a ग_लिखो to the cache.
 */
अटल पूर्णांक cachefiles_ग_लिखो(काष्ठा netfs_cache_resources *cres,
			    loff_t start_pos,
			    काष्ठा iov_iter *iter,
			    netfs_io_terminated_t term_func,
			    व्योम *term_func_priv)
अणु
	काष्ठा cachefiles_kiocb *ki;
	काष्ठा inode *inode;
	काष्ठा file *file = cres->cache_priv2;
	अचिन्हित पूर्णांक old_nofs;
	sमाप_प्रकार ret = -ENOBUFS;
	माप_प्रकार len = iov_iter_count(iter);

	_enter("%pD,%li,%llx,%zx/%llx",
	       file, file_inode(file)->i_ino, start_pos, len,
	       i_size_पढ़ो(file->f_inode));

	ki = kzalloc(माप(काष्ठा cachefiles_kiocb), GFP_KERNEL);
	अगर (!ki)
		जाओ presubmission_error;

	refcount_set(&ki->ki_refcnt, 2);
	ki->iocb.ki_filp	= file;
	ki->iocb.ki_pos		= start_pos;
	ki->iocb.ki_flags	= IOCB_सूचीECT | IOCB_WRITE;
	ki->iocb.ki_hपूर्णांक	= ki_hपूर्णांक_validate(file_ग_लिखो_hपूर्णांक(file));
	ki->iocb.ki_ioprio	= get_current_ioprio();
	ki->start		= start_pos;
	ki->len			= len;
	ki->term_func		= term_func;
	ki->term_func_priv	= term_func_priv;
	ki->was_async		= true;

	अगर (ki->term_func)
		ki->iocb.ki_complete = cachefiles_ग_लिखो_complete;

	/* Open-code file_start_ग_लिखो here to grab मुक्तze protection, which
	 * will be released by another thपढ़ो in aio_complete_rw().  Fool
	 * lockdep by telling it the lock got released so that it करोesn't
	 * complain about the held lock when we वापस to userspace.
	 */
	inode = file_inode(file);
	__sb_start_ग_लिखो(inode->i_sb, SB_FREEZE_WRITE);
	__sb_ग_लिखोrs_release(inode->i_sb, SB_FREEZE_WRITE);

	get_file(ki->iocb.ki_filp);

	old_nofs = meदो_स्मृति_nofs_save();
	ret = vfs_iocb_iter_ग_लिखो(file, &ki->iocb, iter);
	meदो_स्मृति_nofs_restore(old_nofs);
	चयन (ret) अणु
	हाल -EIOCBQUEUED:
		जाओ in_progress;

	हाल -ERESTARTSYS:
	हाल -ERESTARTNOINTR:
	हाल -ERESTARTNOHAND:
	हाल -ERESTART_RESTARTBLOCK:
		/* There's no easy way to restart the syscall since other AIO's
		 * may be alपढ़ोy running. Just fail this IO with EINTR.
		 */
		ret = -EINTR;
		fallthrough;
	शेष:
		ki->was_async = false;
		cachefiles_ग_लिखो_complete(&ki->iocb, ret, 0);
		अगर (ret > 0)
			ret = 0;
		अवरोध;
	पूर्ण

in_progress:
	cachefiles_put_kiocb(ki);
	_leave(" = %zd", ret);
	वापस ret;

presubmission_error:
	अगर (term_func)
		term_func(term_func_priv, -ENOMEM, false);
	वापस -ENOMEM;
पूर्ण

/*
 * Prepare a पढ़ो operation, लघुening it to a cached/uncached
 * boundary as appropriate.
 */
अटल क्रमागत netfs_पढ़ो_source cachefiles_prepare_पढ़ो(काष्ठा netfs_पढ़ो_subrequest *subreq,
						      loff_t i_size)
अणु
	काष्ठा fscache_retrieval *op = subreq->rreq->cache_resources.cache_priv;
	काष्ठा cachefiles_object *object;
	काष्ठा cachefiles_cache *cache;
	स्थिर काष्ठा cred *saved_cred;
	काष्ठा file *file = subreq->rreq->cache_resources.cache_priv2;
	loff_t off, to;

	_enter("%zx @%llx/%llx", subreq->len, subreq->start, i_size);

	object = container_of(op->op.object,
			      काष्ठा cachefiles_object, fscache);
	cache = container_of(object->fscache.cache,
			     काष्ठा cachefiles_cache, cache);

	अगर (!file)
		जाओ cache_fail_nosec;

	अगर (subreq->start >= i_size)
		वापस NETFS_FILL_WITH_ZEROES;

	cachefiles_begin_secure(cache, &saved_cred);

	off = vfs_llseek(file, subreq->start, SEEK_DATA);
	अगर (off < 0 && off >= (loff_t)-MAX_ERRNO) अणु
		अगर (off == (loff_t)-ENXIO)
			जाओ करोwnload_and_store;
		जाओ cache_fail;
	पूर्ण

	अगर (off >= subreq->start + subreq->len)
		जाओ करोwnload_and_store;

	अगर (off > subreq->start) अणु
		off = round_up(off, cache->bsize);
		subreq->len = off - subreq->start;
		जाओ करोwnload_and_store;
	पूर्ण

	to = vfs_llseek(file, subreq->start, SEEK_HOLE);
	अगर (to < 0 && to >= (loff_t)-MAX_ERRNO)
		जाओ cache_fail;

	अगर (to < subreq->start + subreq->len) अणु
		अगर (subreq->start + subreq->len >= i_size)
			to = round_up(to, cache->bsize);
		अन्यथा
			to = round_करोwn(to, cache->bsize);
		subreq->len = to - subreq->start;
	पूर्ण

	cachefiles_end_secure(cache, saved_cred);
	वापस NETFS_READ_FROM_CACHE;

करोwnload_and_store:
	अगर (cachefiles_has_space(cache, 0, (subreq->len + PAGE_SIZE - 1) / PAGE_SIZE) == 0)
		__set_bit(NETFS_SREQ_WRITE_TO_CACHE, &subreq->flags);
cache_fail:
	cachefiles_end_secure(cache, saved_cred);
cache_fail_nosec:
	वापस NETFS_DOWNLOAD_FROM_SERVER;
पूर्ण

/*
 * Prepare क्रम a ग_लिखो to occur.
 */
अटल पूर्णांक cachefiles_prepare_ग_लिखो(काष्ठा netfs_cache_resources *cres,
				    loff_t *_start, माप_प्रकार *_len, loff_t i_size)
अणु
	loff_t start = *_start;
	माप_प्रकार len = *_len, करोwn;

	/* Round to DIO size */
	करोwn = start - round_करोwn(start, PAGE_SIZE);
	*_start = start - करोwn;
	*_len = round_up(करोwn + len, PAGE_SIZE);
	वापस 0;
पूर्ण

/*
 * Clean up an operation.
 */
अटल व्योम cachefiles_end_operation(काष्ठा netfs_cache_resources *cres)
अणु
	काष्ठा fscache_retrieval *op = cres->cache_priv;
	काष्ठा file *file = cres->cache_priv2;

	_enter("");

	अगर (file)
		fput(file);
	अगर (op) अणु
		fscache_op_complete(&op->op, false);
		fscache_put_retrieval(op);
	पूर्ण

	_leave("");
पूर्ण

अटल स्थिर काष्ठा netfs_cache_ops cachefiles_netfs_cache_ops = अणु
	.end_operation		= cachefiles_end_operation,
	.पढ़ो			= cachefiles_पढ़ो,
	.ग_लिखो			= cachefiles_ग_लिखो,
	.prepare_पढ़ो		= cachefiles_prepare_पढ़ो,
	.prepare_ग_लिखो		= cachefiles_prepare_ग_लिखो,
पूर्ण;

/*
 * Open the cache file when beginning a cache operation.
 */
पूर्णांक cachefiles_begin_पढ़ो_operation(काष्ठा netfs_पढ़ो_request *rreq,
				    काष्ठा fscache_retrieval *op)
अणु
	काष्ठा cachefiles_object *object;
	काष्ठा cachefiles_cache *cache;
	काष्ठा path path;
	काष्ठा file *file;

	_enter("");

	object = container_of(op->op.object,
			      काष्ठा cachefiles_object, fscache);
	cache = container_of(object->fscache.cache,
			     काष्ठा cachefiles_cache, cache);

	path.mnt = cache->mnt;
	path.dentry = object->backer;
	file = खोलो_with_fake_path(&path, O_RDWR | O_LARGEखाता | O_सूचीECT,
				   d_inode(object->backer), cache->cache_cred);
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);
	अगर (!S_ISREG(file_inode(file)->i_mode))
		जाओ error_file;
	अगर (unlikely(!file->f_op->पढ़ो_iter) ||
	    unlikely(!file->f_op->ग_लिखो_iter)) अणु
		pr_notice("Cache does not support read_iter and write_iter\n");
		जाओ error_file;
	पूर्ण

	fscache_get_retrieval(op);
	rreq->cache_resources.cache_priv = op;
	rreq->cache_resources.cache_priv2 = file;
	rreq->cache_resources.ops = &cachefiles_netfs_cache_ops;
	rreq->cookie_debug_id = object->fscache.debug_id;
	_leave("");
	वापस 0;

error_file:
	fput(file);
	वापस -EIO;
पूर्ण
