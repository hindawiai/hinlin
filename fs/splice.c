<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * "splice": joining two ropes together by पूर्णांकerweaving their stअक्रमs.
 *
 * This is the "extended pipe" functionality, where a pipe is used as
 * an arbitrary in-memory buffer. Think of a pipe as a small kernel
 * buffer that you can use to transfer data from one end to the other.
 *
 * The traditional unix पढ़ो/ग_लिखो is extended with a "splice()" operation
 * that transfers data buffers to or from a pipe buffer.
 *
 * Named by Larry McVoy, original implementation from Linus, extended by
 * Jens to support splicing to files, network, direct splicing, etc and
 * fixing lots of bugs.
 *
 * Copyright (C) 2005-2006 Jens Axboe <axboe@kernel.dk>
 * Copyright (C) 2005-2006 Linus Torvalds <torvalds@osdl.org>
 * Copyright (C) 2006 Ingo Molnar <mingo@elte.hu>
 *
 */
#समावेश <linux/bvec.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/splice.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <linux/swap.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/export.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/uपन.स>
#समावेश <linux/security.h>
#समावेश <linux/gfp.h>
#समावेश <linux/socket.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "internal.h"

/*
 * Attempt to steal a page from a pipe buffer. This should perhaps go पूर्णांकo
 * a vm helper function, it's alपढ़ोy simplअगरied quite a bit by the
 * addition of हटाओ_mapping(). If success is वापसed, the caller may
 * attempt to reuse this page क्रम another destination.
 */
अटल bool page_cache_pipe_buf_try_steal(काष्ठा pipe_inode_info *pipe,
		काष्ठा pipe_buffer *buf)
अणु
	काष्ठा page *page = buf->page;
	काष्ठा address_space *mapping;

	lock_page(page);

	mapping = page_mapping(page);
	अगर (mapping) अणु
		WARN_ON(!PageUptodate(page));

		/*
		 * At least क्रम ext2 with nobh option, we need to रुको on
		 * ग_लिखोback completing on this page, since we'll हटाओ it
		 * from the pagecache.  Otherwise truncate wont रुको on the
		 * page, allowing the disk blocks to be reused by someone अन्यथा
		 * beक्रमe we actually wrote our data to them. fs corruption
		 * ensues.
		 */
		रुको_on_page_ग_लिखोback(page);

		अगर (page_has_निजी(page) &&
		    !try_to_release_page(page, GFP_KERNEL))
			जाओ out_unlock;

		/*
		 * If we succeeded in removing the mapping, set LRU flag
		 * and वापस good.
		 */
		अगर (हटाओ_mapping(mapping, page)) अणु
			buf->flags |= PIPE_BUF_FLAG_LRU;
			वापस true;
		पूर्ण
	पूर्ण

	/*
	 * Raced with truncate or failed to हटाओ page from current
	 * address space, unlock and वापस failure.
	 */
out_unlock:
	unlock_page(page);
	वापस false;
पूर्ण

अटल व्योम page_cache_pipe_buf_release(काष्ठा pipe_inode_info *pipe,
					काष्ठा pipe_buffer *buf)
अणु
	put_page(buf->page);
	buf->flags &= ~PIPE_BUF_FLAG_LRU;
पूर्ण

/*
 * Check whether the contents of buf is OK to access. Since the content
 * is a page cache page, IO may be in flight.
 */
अटल पूर्णांक page_cache_pipe_buf_confirm(काष्ठा pipe_inode_info *pipe,
				       काष्ठा pipe_buffer *buf)
अणु
	काष्ठा page *page = buf->page;
	पूर्णांक err;

	अगर (!PageUptodate(page)) अणु
		lock_page(page);

		/*
		 * Page got truncated/unhashed. This will cause a 0-byte
		 * splice, अगर this is the first page.
		 */
		अगर (!page->mapping) अणु
			err = -ENODATA;
			जाओ error;
		पूर्ण

		/*
		 * Uh oh, पढ़ो-error from disk.
		 */
		अगर (!PageUptodate(page)) अणु
			err = -EIO;
			जाओ error;
		पूर्ण

		/*
		 * Page is ok afterall, we are करोne.
		 */
		unlock_page(page);
	पूर्ण

	वापस 0;
error:
	unlock_page(page);
	वापस err;
पूर्ण

स्थिर काष्ठा pipe_buf_operations page_cache_pipe_buf_ops = अणु
	.confirm	= page_cache_pipe_buf_confirm,
	.release	= page_cache_pipe_buf_release,
	.try_steal	= page_cache_pipe_buf_try_steal,
	.get		= generic_pipe_buf_get,
पूर्ण;

अटल bool user_page_pipe_buf_try_steal(काष्ठा pipe_inode_info *pipe,
		काष्ठा pipe_buffer *buf)
अणु
	अगर (!(buf->flags & PIPE_BUF_FLAG_GIFT))
		वापस false;

	buf->flags |= PIPE_BUF_FLAG_LRU;
	वापस generic_pipe_buf_try_steal(pipe, buf);
पूर्ण

अटल स्थिर काष्ठा pipe_buf_operations user_page_pipe_buf_ops = अणु
	.release	= page_cache_pipe_buf_release,
	.try_steal	= user_page_pipe_buf_try_steal,
	.get		= generic_pipe_buf_get,
पूर्ण;

अटल व्योम wakeup_pipe_पढ़ोers(काष्ठा pipe_inode_info *pipe)
अणु
	smp_mb();
	अगर (रुकोqueue_active(&pipe->rd_रुको))
		wake_up_पूर्णांकerruptible(&pipe->rd_रुको);
	समाप्त_fasync(&pipe->fasync_पढ़ोers, SIGIO, POLL_IN);
पूर्ण

/**
 * splice_to_pipe - fill passed data पूर्णांकo a pipe
 * @pipe:	pipe to fill
 * @spd:	data to fill
 *
 * Description:
 *    @spd contains a map of pages and len/offset tuples, aदीर्घ with
 *    the काष्ठा pipe_buf_operations associated with these pages. This
 *    function will link that data to the pipe.
 *
 */
sमाप_प्रकार splice_to_pipe(काष्ठा pipe_inode_info *pipe,
		       काष्ठा splice_pipe_desc *spd)
अणु
	अचिन्हित पूर्णांक spd_pages = spd->nr_pages;
	अचिन्हित पूर्णांक tail = pipe->tail;
	अचिन्हित पूर्णांक head = pipe->head;
	अचिन्हित पूर्णांक mask = pipe->ring_size - 1;
	पूर्णांक ret = 0, page_nr = 0;

	अगर (!spd_pages)
		वापस 0;

	अगर (unlikely(!pipe->पढ़ोers)) अणु
		send_sig(SIGPIPE, current, 0);
		ret = -EPIPE;
		जाओ out;
	पूर्ण

	जबतक (!pipe_full(head, tail, pipe->max_usage)) अणु
		काष्ठा pipe_buffer *buf = &pipe->bufs[head & mask];

		buf->page = spd->pages[page_nr];
		buf->offset = spd->partial[page_nr].offset;
		buf->len = spd->partial[page_nr].len;
		buf->निजी = spd->partial[page_nr].निजी;
		buf->ops = spd->ops;
		buf->flags = 0;

		head++;
		pipe->head = head;
		page_nr++;
		ret += buf->len;

		अगर (!--spd->nr_pages)
			अवरोध;
	पूर्ण

	अगर (!ret)
		ret = -EAGAIN;

out:
	जबतक (page_nr < spd_pages)
		spd->spd_release(spd, page_nr++);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(splice_to_pipe);

sमाप_प्रकार add_to_pipe(काष्ठा pipe_inode_info *pipe, काष्ठा pipe_buffer *buf)
अणु
	अचिन्हित पूर्णांक head = pipe->head;
	अचिन्हित पूर्णांक tail = pipe->tail;
	अचिन्हित पूर्णांक mask = pipe->ring_size - 1;
	पूर्णांक ret;

	अगर (unlikely(!pipe->पढ़ोers)) अणु
		send_sig(SIGPIPE, current, 0);
		ret = -EPIPE;
	पूर्ण अन्यथा अगर (pipe_full(head, tail, pipe->max_usage)) अणु
		ret = -EAGAIN;
	पूर्ण अन्यथा अणु
		pipe->bufs[head & mask] = *buf;
		pipe->head = head + 1;
		वापस buf->len;
	पूर्ण
	pipe_buf_release(pipe, buf);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(add_to_pipe);

/*
 * Check अगर we need to grow the arrays holding pages and partial page
 * descriptions.
 */
पूर्णांक splice_grow_spd(स्थिर काष्ठा pipe_inode_info *pipe, काष्ठा splice_pipe_desc *spd)
अणु
	अचिन्हित पूर्णांक max_usage = READ_ONCE(pipe->max_usage);

	spd->nr_pages_max = max_usage;
	अगर (max_usage <= PIPE_DEF_BUFFERS)
		वापस 0;

	spd->pages = kदो_स्मृति_array(max_usage, माप(काष्ठा page *), GFP_KERNEL);
	spd->partial = kदो_स्मृति_array(max_usage, माप(काष्ठा partial_page),
				     GFP_KERNEL);

	अगर (spd->pages && spd->partial)
		वापस 0;

	kमुक्त(spd->pages);
	kमुक्त(spd->partial);
	वापस -ENOMEM;
पूर्ण

व्योम splice_shrink_spd(काष्ठा splice_pipe_desc *spd)
अणु
	अगर (spd->nr_pages_max <= PIPE_DEF_BUFFERS)
		वापस;

	kमुक्त(spd->pages);
	kमुक्त(spd->partial);
पूर्ण

/**
 * generic_file_splice_पढ़ो - splice data from file to a pipe
 * @in:		file to splice from
 * @ppos:	position in @in
 * @pipe:	pipe to splice to
 * @len:	number of bytes to splice
 * @flags:	splice modअगरier flags
 *
 * Description:
 *    Will पढ़ो pages from given file and fill them पूर्णांकo a pipe. Can be
 *    used as दीर्घ as it has more or less sane ->पढ़ो_iter().
 *
 */
sमाप_प्रकार generic_file_splice_पढ़ो(काष्ठा file *in, loff_t *ppos,
				 काष्ठा pipe_inode_info *pipe, माप_प्रकार len,
				 अचिन्हित पूर्णांक flags)
अणु
	काष्ठा iov_iter to;
	काष्ठा kiocb kiocb;
	अचिन्हित पूर्णांक i_head;
	पूर्णांक ret;

	iov_iter_pipe(&to, READ, pipe, len);
	i_head = to.head;
	init_sync_kiocb(&kiocb, in);
	kiocb.ki_pos = *ppos;
	ret = call_पढ़ो_iter(in, &kiocb, &to);
	अगर (ret > 0) अणु
		*ppos = kiocb.ki_pos;
		file_accessed(in);
	पूर्ण अन्यथा अगर (ret < 0) अणु
		to.head = i_head;
		to.iov_offset = 0;
		iov_iter_advance(&to, 0); /* to मुक्त what was emitted */
		/*
		 * callers of ->splice_पढ़ो() expect -EAGAIN on
		 * "can't put anything in there", rather than -EFAULT.
		 */
		अगर (ret == -EFAULT)
			ret = -EAGAIN;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(generic_file_splice_पढ़ो);

स्थिर काष्ठा pipe_buf_operations शेष_pipe_buf_ops = अणु
	.release	= generic_pipe_buf_release,
	.try_steal	= generic_pipe_buf_try_steal,
	.get		= generic_pipe_buf_get,
पूर्ण;

/* Pipe buffer operations क्रम a socket and similar. */
स्थिर काष्ठा pipe_buf_operations nosteal_pipe_buf_ops = अणु
	.release	= generic_pipe_buf_release,
	.get		= generic_pipe_buf_get,
पूर्ण;
EXPORT_SYMBOL(nosteal_pipe_buf_ops);

/*
 * Send 'sd->len' bytes to socket from 'sd->file' at position 'sd->pos'
 * using sendpage(). Return the number of bytes sent.
 */
अटल पूर्णांक pipe_to_sendpage(काष्ठा pipe_inode_info *pipe,
			    काष्ठा pipe_buffer *buf, काष्ठा splice_desc *sd)
अणु
	काष्ठा file *file = sd->u.file;
	loff_t pos = sd->pos;
	पूर्णांक more;

	अगर (!likely(file->f_op->sendpage))
		वापस -EINVAL;

	more = (sd->flags & SPLICE_F_MORE) ? MSG_MORE : 0;

	अगर (sd->len < sd->total_len &&
	    pipe_occupancy(pipe->head, pipe->tail) > 1)
		more |= MSG_SENDPAGE_NOTLAST;

	वापस file->f_op->sendpage(file, buf->page, buf->offset,
				    sd->len, &pos, more);
पूर्ण

अटल व्योम wakeup_pipe_ग_लिखोrs(काष्ठा pipe_inode_info *pipe)
अणु
	smp_mb();
	अगर (रुकोqueue_active(&pipe->wr_रुको))
		wake_up_पूर्णांकerruptible(&pipe->wr_रुको);
	समाप्त_fasync(&pipe->fasync_ग_लिखोrs, SIGIO, POLL_OUT);
पूर्ण

/**
 * splice_from_pipe_feed - feed available data from a pipe to a file
 * @pipe:	pipe to splice from
 * @sd:		inक्रमmation to @actor
 * @actor:	handler that splices the data
 *
 * Description:
 *    This function loops over the pipe and calls @actor to करो the
 *    actual moving of a single काष्ठा pipe_buffer to the desired
 *    destination.  It वापसs when there's no more buffers left in
 *    the pipe or अगर the requested number of bytes (@sd->total_len)
 *    have been copied.  It वापसs a positive number (one) अगर the
 *    pipe needs to be filled with more data, zero अगर the required
 *    number of bytes have been copied and -त्रुटि_सं on error.
 *
 *    This, together with splice_from_pipe_अणुbegin,end,nextपूर्ण, may be
 *    used to implement the functionality of __splice_from_pipe() when
 *    locking is required around copying the pipe buffers to the
 *    destination.
 */
अटल पूर्णांक splice_from_pipe_feed(काष्ठा pipe_inode_info *pipe, काष्ठा splice_desc *sd,
			  splice_actor *actor)
अणु
	अचिन्हित पूर्णांक head = pipe->head;
	अचिन्हित पूर्णांक tail = pipe->tail;
	अचिन्हित पूर्णांक mask = pipe->ring_size - 1;
	पूर्णांक ret;

	जबतक (!pipe_empty(head, tail)) अणु
		काष्ठा pipe_buffer *buf = &pipe->bufs[tail & mask];

		sd->len = buf->len;
		अगर (sd->len > sd->total_len)
			sd->len = sd->total_len;

		ret = pipe_buf_confirm(pipe, buf);
		अगर (unlikely(ret)) अणु
			अगर (ret == -ENODATA)
				ret = 0;
			वापस ret;
		पूर्ण

		ret = actor(pipe, buf, sd);
		अगर (ret <= 0)
			वापस ret;

		buf->offset += ret;
		buf->len -= ret;

		sd->num_spliced += ret;
		sd->len -= ret;
		sd->pos += ret;
		sd->total_len -= ret;

		अगर (!buf->len) अणु
			pipe_buf_release(pipe, buf);
			tail++;
			pipe->tail = tail;
			अगर (pipe->files)
				sd->need_wakeup = true;
		पूर्ण

		अगर (!sd->total_len)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/* We know we have a pipe buffer, but maybe it's empty? */
अटल अंतरभूत bool eat_empty_buffer(काष्ठा pipe_inode_info *pipe)
अणु
	अचिन्हित पूर्णांक tail = pipe->tail;
	अचिन्हित पूर्णांक mask = pipe->ring_size - 1;
	काष्ठा pipe_buffer *buf = &pipe->bufs[tail & mask];

	अगर (unlikely(!buf->len)) अणु
		pipe_buf_release(pipe, buf);
		pipe->tail = tail+1;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * splice_from_pipe_next - रुको क्रम some data to splice from
 * @pipe:	pipe to splice from
 * @sd:		inक्रमmation about the splice operation
 *
 * Description:
 *    This function will रुको क्रम some data and वापस a positive
 *    value (one) अगर pipe buffers are available.  It will वापस zero
 *    or -त्रुटि_सं अगर no more data needs to be spliced.
 */
अटल पूर्णांक splice_from_pipe_next(काष्ठा pipe_inode_info *pipe, काष्ठा splice_desc *sd)
अणु
	/*
	 * Check क्रम संकेत early to make process समाप्तable when there are
	 * always buffers available
	 */
	अगर (संकेत_pending(current))
		वापस -ERESTARTSYS;

repeat:
	जबतक (pipe_empty(pipe->head, pipe->tail)) अणु
		अगर (!pipe->ग_लिखोrs)
			वापस 0;

		अगर (sd->num_spliced)
			वापस 0;

		अगर (sd->flags & SPLICE_F_NONBLOCK)
			वापस -EAGAIN;

		अगर (संकेत_pending(current))
			वापस -ERESTARTSYS;

		अगर (sd->need_wakeup) अणु
			wakeup_pipe_ग_लिखोrs(pipe);
			sd->need_wakeup = false;
		पूर्ण

		pipe_रुको_पढ़ोable(pipe);
	पूर्ण

	अगर (eat_empty_buffer(pipe))
		जाओ repeat;

	वापस 1;
पूर्ण

/**
 * splice_from_pipe_begin - start splicing from pipe
 * @sd:		inक्रमmation about the splice operation
 *
 * Description:
 *    This function should be called beक्रमe a loop containing
 *    splice_from_pipe_next() and splice_from_pipe_feed() to
 *    initialize the necessary fields of @sd.
 */
अटल व्योम splice_from_pipe_begin(काष्ठा splice_desc *sd)
अणु
	sd->num_spliced = 0;
	sd->need_wakeup = false;
पूर्ण

/**
 * splice_from_pipe_end - finish splicing from pipe
 * @pipe:	pipe to splice from
 * @sd:		inक्रमmation about the splice operation
 *
 * Description:
 *    This function will wake up pipe ग_लिखोrs अगर necessary.  It should
 *    be called after a loop containing splice_from_pipe_next() and
 *    splice_from_pipe_feed().
 */
अटल व्योम splice_from_pipe_end(काष्ठा pipe_inode_info *pipe, काष्ठा splice_desc *sd)
अणु
	अगर (sd->need_wakeup)
		wakeup_pipe_ग_लिखोrs(pipe);
पूर्ण

/**
 * __splice_from_pipe - splice data from a pipe to given actor
 * @pipe:	pipe to splice from
 * @sd:		inक्रमmation to @actor
 * @actor:	handler that splices the data
 *
 * Description:
 *    This function करोes little more than loop over the pipe and call
 *    @actor to करो the actual moving of a single काष्ठा pipe_buffer to
 *    the desired destination. See pipe_to_file, pipe_to_sendpage, or
 *    pipe_to_user.
 *
 */
sमाप_प्रकार __splice_from_pipe(काष्ठा pipe_inode_info *pipe, काष्ठा splice_desc *sd,
			   splice_actor *actor)
अणु
	पूर्णांक ret;

	splice_from_pipe_begin(sd);
	करो अणु
		cond_resched();
		ret = splice_from_pipe_next(pipe, sd);
		अगर (ret > 0)
			ret = splice_from_pipe_feed(pipe, sd, actor);
	पूर्ण जबतक (ret > 0);
	splice_from_pipe_end(pipe, sd);

	वापस sd->num_spliced ? sd->num_spliced : ret;
पूर्ण
EXPORT_SYMBOL(__splice_from_pipe);

/**
 * splice_from_pipe - splice data from a pipe to a file
 * @pipe:	pipe to splice from
 * @out:	file to splice to
 * @ppos:	position in @out
 * @len:	how many bytes to splice
 * @flags:	splice modअगरier flags
 * @actor:	handler that splices the data
 *
 * Description:
 *    See __splice_from_pipe. This function locks the pipe inode,
 *    otherwise it's identical to __splice_from_pipe().
 *
 */
sमाप_प्रकार splice_from_pipe(काष्ठा pipe_inode_info *pipe, काष्ठा file *out,
			 loff_t *ppos, माप_प्रकार len, अचिन्हित पूर्णांक flags,
			 splice_actor *actor)
अणु
	sमाप_प्रकार ret;
	काष्ठा splice_desc sd = अणु
		.total_len = len,
		.flags = flags,
		.pos = *ppos,
		.u.file = out,
	पूर्ण;

	pipe_lock(pipe);
	ret = __splice_from_pipe(pipe, &sd, actor);
	pipe_unlock(pipe);

	वापस ret;
पूर्ण

/**
 * iter_file_splice_ग_लिखो - splice data from a pipe to a file
 * @pipe:	pipe info
 * @out:	file to ग_लिखो to
 * @ppos:	position in @out
 * @len:	number of bytes to splice
 * @flags:	splice modअगरier flags
 *
 * Description:
 *    Will either move or copy pages (determined by @flags options) from
 *    the given pipe inode to the given file.
 *    This one is ->ग_लिखो_iter-based.
 *
 */
sमाप_प्रकार
iter_file_splice_ग_लिखो(काष्ठा pipe_inode_info *pipe, काष्ठा file *out,
			  loff_t *ppos, माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा splice_desc sd = अणु
		.total_len = len,
		.flags = flags,
		.pos = *ppos,
		.u.file = out,
	पूर्ण;
	पूर्णांक nbufs = pipe->max_usage;
	काष्ठा bio_vec *array = kसुस्मृति(nbufs, माप(काष्ठा bio_vec),
					GFP_KERNEL);
	sमाप_प्रकार ret;

	अगर (unlikely(!array))
		वापस -ENOMEM;

	pipe_lock(pipe);

	splice_from_pipe_begin(&sd);
	जबतक (sd.total_len) अणु
		काष्ठा iov_iter from;
		अचिन्हित पूर्णांक head, tail, mask;
		माप_प्रकार left;
		पूर्णांक n;

		ret = splice_from_pipe_next(pipe, &sd);
		अगर (ret <= 0)
			अवरोध;

		अगर (unlikely(nbufs < pipe->max_usage)) अणु
			kमुक्त(array);
			nbufs = pipe->max_usage;
			array = kसुस्मृति(nbufs, माप(काष्ठा bio_vec),
					GFP_KERNEL);
			अगर (!array) अणु
				ret = -ENOMEM;
				अवरोध;
			पूर्ण
		पूर्ण

		head = pipe->head;
		tail = pipe->tail;
		mask = pipe->ring_size - 1;

		/* build the vector */
		left = sd.total_len;
		क्रम (n = 0; !pipe_empty(head, tail) && left && n < nbufs; tail++) अणु
			काष्ठा pipe_buffer *buf = &pipe->bufs[tail & mask];
			माप_प्रकार this_len = buf->len;

			/* zero-length bvecs are not supported, skip them */
			अगर (!this_len)
				जारी;
			this_len = min(this_len, left);

			ret = pipe_buf_confirm(pipe, buf);
			अगर (unlikely(ret)) अणु
				अगर (ret == -ENODATA)
					ret = 0;
				जाओ करोne;
			पूर्ण

			array[n].bv_page = buf->page;
			array[n].bv_len = this_len;
			array[n].bv_offset = buf->offset;
			left -= this_len;
			n++;
		पूर्ण

		iov_iter_bvec(&from, WRITE, array, n, sd.total_len - left);
		ret = vfs_iter_ग_लिखो(out, &from, &sd.pos, 0);
		अगर (ret <= 0)
			अवरोध;

		sd.num_spliced += ret;
		sd.total_len -= ret;
		*ppos = sd.pos;

		/* dismiss the fully eaten buffers, adjust the partial one */
		tail = pipe->tail;
		जबतक (ret) अणु
			काष्ठा pipe_buffer *buf = &pipe->bufs[tail & mask];
			अगर (ret >= buf->len) अणु
				ret -= buf->len;
				buf->len = 0;
				pipe_buf_release(pipe, buf);
				tail++;
				pipe->tail = tail;
				अगर (pipe->files)
					sd.need_wakeup = true;
			पूर्ण अन्यथा अणु
				buf->offset += ret;
				buf->len -= ret;
				ret = 0;
			पूर्ण
		पूर्ण
	पूर्ण
करोne:
	kमुक्त(array);
	splice_from_pipe_end(pipe, &sd);

	pipe_unlock(pipe);

	अगर (sd.num_spliced)
		ret = sd.num_spliced;

	वापस ret;
पूर्ण

EXPORT_SYMBOL(iter_file_splice_ग_लिखो);

/**
 * generic_splice_sendpage - splice data from a pipe to a socket
 * @pipe:	pipe to splice from
 * @out:	socket to ग_लिखो to
 * @ppos:	position in @out
 * @len:	number of bytes to splice
 * @flags:	splice modअगरier flags
 *
 * Description:
 *    Will send @len bytes from the pipe to a network socket. No data copying
 *    is involved.
 *
 */
sमाप_प्रकार generic_splice_sendpage(काष्ठा pipe_inode_info *pipe, काष्ठा file *out,
				loff_t *ppos, माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	वापस splice_from_pipe(pipe, out, ppos, len, flags, pipe_to_sendpage);
पूर्ण

EXPORT_SYMBOL(generic_splice_sendpage);

अटल पूर्णांक warn_unsupported(काष्ठा file *file, स्थिर अक्षर *op)
अणु
	pr_debug_ratelimited(
		"splice %s not supported for file %pD4 (pid: %d comm: %.20s)\n",
		op, file, current->pid, current->comm);
	वापस -EINVAL;
पूर्ण

/*
 * Attempt to initiate a splice from pipe to file.
 */
अटल दीर्घ करो_splice_from(काष्ठा pipe_inode_info *pipe, काष्ठा file *out,
			   loff_t *ppos, माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	अगर (unlikely(!out->f_op->splice_ग_लिखो))
		वापस warn_unsupported(out, "write");
	वापस out->f_op->splice_ग_लिखो(pipe, out, ppos, len, flags);
पूर्ण

/*
 * Attempt to initiate a splice from a file to a pipe.
 */
अटल दीर्घ करो_splice_to(काष्ठा file *in, loff_t *ppos,
			 काष्ठा pipe_inode_info *pipe, माप_प्रकार len,
			 अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक p_space;
	पूर्णांक ret;

	अगर (unlikely(!(in->f_mode & FMODE_READ)))
		वापस -EBADF;

	/* Don't try to पढ़ो more the pipe has space क्रम. */
	p_space = pipe->max_usage - pipe_occupancy(pipe->head, pipe->tail);
	len = min_t(माप_प्रकार, len, p_space << PAGE_SHIFT);

	ret = rw_verअगरy_area(READ, in, ppos, len);
	अगर (unlikely(ret < 0))
		वापस ret;

	अगर (unlikely(len > MAX_RW_COUNT))
		len = MAX_RW_COUNT;

	अगर (unlikely(!in->f_op->splice_पढ़ो))
		वापस warn_unsupported(in, "read");
	वापस in->f_op->splice_पढ़ो(in, ppos, pipe, len, flags);
पूर्ण

/**
 * splice_direct_to_actor - splices data directly between two non-pipes
 * @in:		file to splice from
 * @sd:		actor inक्रमmation on where to splice to
 * @actor:	handles the data splicing
 *
 * Description:
 *    This is a special हाल helper to splice directly between two
 *    poपूर्णांकs, without requiring an explicit pipe. Internally an allocated
 *    pipe is cached in the process, and reused during the lअगरeसमय of
 *    that process.
 *
 */
sमाप_प्रकार splice_direct_to_actor(काष्ठा file *in, काष्ठा splice_desc *sd,
			       splice_direct_actor *actor)
अणु
	काष्ठा pipe_inode_info *pipe;
	दीर्घ ret, bytes;
	umode_t i_mode;
	माप_प्रकार len;
	पूर्णांक i, flags, more;

	/*
	 * We require the input being a regular file, as we करोn't want to
	 * अक्रमomly drop data क्रम eg socket -> socket splicing. Use the
	 * piped splicing क्रम that!
	 */
	i_mode = file_inode(in)->i_mode;
	अगर (unlikely(!S_ISREG(i_mode) && !S_ISBLK(i_mode)))
		वापस -EINVAL;

	/*
	 * neither in nor out is a pipe, setup an पूर्णांकernal pipe attached to
	 * 'out' and transfer the wanted data from 'in' to 'out' through that
	 */
	pipe = current->splice_pipe;
	अगर (unlikely(!pipe)) अणु
		pipe = alloc_pipe_info();
		अगर (!pipe)
			वापस -ENOMEM;

		/*
		 * We करोn't have an immediate reader, but we'll पढ़ो the stuff
		 * out of the pipe right after the splice_to_pipe(). So set
		 * PIPE_READERS appropriately.
		 */
		pipe->पढ़ोers = 1;

		current->splice_pipe = pipe;
	पूर्ण

	/*
	 * Do the splice.
	 */
	ret = 0;
	bytes = 0;
	len = sd->total_len;
	flags = sd->flags;

	/*
	 * Don't block on output, we have to drain the direct pipe.
	 */
	sd->flags &= ~SPLICE_F_NONBLOCK;
	more = sd->flags & SPLICE_F_MORE;

	WARN_ON_ONCE(!pipe_empty(pipe->head, pipe->tail));

	जबतक (len) अणु
		माप_प्रकार पढ़ो_len;
		loff_t pos = sd->pos, prev_pos = pos;

		ret = करो_splice_to(in, &pos, pipe, len, flags);
		अगर (unlikely(ret <= 0))
			जाओ out_release;

		पढ़ो_len = ret;
		sd->total_len = पढ़ो_len;

		/*
		 * If more data is pending, set SPLICE_F_MORE
		 * If this is the last data and SPLICE_F_MORE was not set
		 * initially, clears it.
		 */
		अगर (पढ़ो_len < len)
			sd->flags |= SPLICE_F_MORE;
		अन्यथा अगर (!more)
			sd->flags &= ~SPLICE_F_MORE;
		/*
		 * NOTE: nonblocking mode only applies to the input. We
		 * must not करो the output in nonblocking mode as then we
		 * could get stuck data in the पूर्णांकernal pipe:
		 */
		ret = actor(pipe, sd);
		अगर (unlikely(ret <= 0)) अणु
			sd->pos = prev_pos;
			जाओ out_release;
		पूर्ण

		bytes += ret;
		len -= ret;
		sd->pos = pos;

		अगर (ret < पढ़ो_len) अणु
			sd->pos = prev_pos + ret;
			जाओ out_release;
		पूर्ण
	पूर्ण

करोne:
	pipe->tail = pipe->head = 0;
	file_accessed(in);
	वापस bytes;

out_release:
	/*
	 * If we did an incomplete transfer we must release
	 * the pipe buffers in question:
	 */
	क्रम (i = 0; i < pipe->ring_size; i++) अणु
		काष्ठा pipe_buffer *buf = &pipe->bufs[i];

		अगर (buf->ops)
			pipe_buf_release(pipe, buf);
	पूर्ण

	अगर (!bytes)
		bytes = ret;

	जाओ करोne;
पूर्ण
EXPORT_SYMBOL(splice_direct_to_actor);

अटल पूर्णांक direct_splice_actor(काष्ठा pipe_inode_info *pipe,
			       काष्ठा splice_desc *sd)
अणु
	काष्ठा file *file = sd->u.file;

	वापस करो_splice_from(pipe, file, sd->opos, sd->total_len,
			      sd->flags);
पूर्ण

/**
 * करो_splice_direct - splices data directly between two files
 * @in:		file to splice from
 * @ppos:	input file offset
 * @out:	file to splice to
 * @opos:	output file offset
 * @len:	number of bytes to splice
 * @flags:	splice modअगरier flags
 *
 * Description:
 *    For use by करो_sendfile(). splice can easily emulate sendfile, but
 *    करोing it in the application would incur an extra प्रणाली call
 *    (splice in + splice out, as compared to just sendfile()). So this helper
 *    can splice directly through a process-निजी pipe.
 *
 */
दीर्घ करो_splice_direct(काष्ठा file *in, loff_t *ppos, काष्ठा file *out,
		      loff_t *opos, माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा splice_desc sd = अणु
		.len		= len,
		.total_len	= len,
		.flags		= flags,
		.pos		= *ppos,
		.u.file		= out,
		.opos		= opos,
	पूर्ण;
	दीर्घ ret;

	अगर (unlikely(!(out->f_mode & FMODE_WRITE)))
		वापस -EBADF;

	अगर (unlikely(out->f_flags & O_APPEND))
		वापस -EINVAL;

	ret = rw_verअगरy_area(WRITE, out, opos, len);
	अगर (unlikely(ret < 0))
		वापस ret;

	ret = splice_direct_to_actor(in, &sd, direct_splice_actor);
	अगर (ret > 0)
		*ppos = sd.pos;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(करो_splice_direct);

अटल पूर्णांक रुको_क्रम_space(काष्ठा pipe_inode_info *pipe, अचिन्हित flags)
अणु
	क्रम (;;) अणु
		अगर (unlikely(!pipe->पढ़ोers)) अणु
			send_sig(SIGPIPE, current, 0);
			वापस -EPIPE;
		पूर्ण
		अगर (!pipe_full(pipe->head, pipe->tail, pipe->max_usage))
			वापस 0;
		अगर (flags & SPLICE_F_NONBLOCK)
			वापस -EAGAIN;
		अगर (संकेत_pending(current))
			वापस -ERESTARTSYS;
		pipe_रुको_writable(pipe);
	पूर्ण
पूर्ण

अटल पूर्णांक splice_pipe_to_pipe(काष्ठा pipe_inode_info *ipipe,
			       काष्ठा pipe_inode_info *opipe,
			       माप_प्रकार len, अचिन्हित पूर्णांक flags);

दीर्घ splice_file_to_pipe(काष्ठा file *in,
			 काष्ठा pipe_inode_info *opipe,
			 loff_t *offset,
			 माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	दीर्घ ret;

	pipe_lock(opipe);
	ret = रुको_क्रम_space(opipe, flags);
	अगर (!ret)
		ret = करो_splice_to(in, offset, opipe, len, flags);
	pipe_unlock(opipe);
	अगर (ret > 0)
		wakeup_pipe_पढ़ोers(opipe);
	वापस ret;
पूर्ण

/*
 * Determine where to splice to/from.
 */
दीर्घ करो_splice(काष्ठा file *in, loff_t *off_in, काष्ठा file *out,
	       loff_t *off_out, माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा pipe_inode_info *ipipe;
	काष्ठा pipe_inode_info *opipe;
	loff_t offset;
	दीर्घ ret;

	अगर (unlikely(!(in->f_mode & FMODE_READ) ||
		     !(out->f_mode & FMODE_WRITE)))
		वापस -EBADF;

	ipipe = get_pipe_info(in, true);
	opipe = get_pipe_info(out, true);

	अगर (ipipe && opipe) अणु
		अगर (off_in || off_out)
			वापस -ESPIPE;

		/* Splicing to self would be fun, but... */
		अगर (ipipe == opipe)
			वापस -EINVAL;

		अगर ((in->f_flags | out->f_flags) & O_NONBLOCK)
			flags |= SPLICE_F_NONBLOCK;

		वापस splice_pipe_to_pipe(ipipe, opipe, len, flags);
	पूर्ण

	अगर (ipipe) अणु
		अगर (off_in)
			वापस -ESPIPE;
		अगर (off_out) अणु
			अगर (!(out->f_mode & FMODE_PWRITE))
				वापस -EINVAL;
			offset = *off_out;
		पूर्ण अन्यथा अणु
			offset = out->f_pos;
		पूर्ण

		अगर (unlikely(out->f_flags & O_APPEND))
			वापस -EINVAL;

		ret = rw_verअगरy_area(WRITE, out, &offset, len);
		अगर (unlikely(ret < 0))
			वापस ret;

		अगर (in->f_flags & O_NONBLOCK)
			flags |= SPLICE_F_NONBLOCK;

		file_start_ग_लिखो(out);
		ret = करो_splice_from(ipipe, out, &offset, len, flags);
		file_end_ग_लिखो(out);

		अगर (!off_out)
			out->f_pos = offset;
		अन्यथा
			*off_out = offset;

		वापस ret;
	पूर्ण

	अगर (opipe) अणु
		अगर (off_out)
			वापस -ESPIPE;
		अगर (off_in) अणु
			अगर (!(in->f_mode & FMODE_PREAD))
				वापस -EINVAL;
			offset = *off_in;
		पूर्ण अन्यथा अणु
			offset = in->f_pos;
		पूर्ण

		अगर (out->f_flags & O_NONBLOCK)
			flags |= SPLICE_F_NONBLOCK;

		ret = splice_file_to_pipe(in, opipe, &offset, len, flags);
		अगर (!off_in)
			in->f_pos = offset;
		अन्यथा
			*off_in = offset;

		वापस ret;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल दीर्घ __करो_splice(काष्ठा file *in, loff_t __user *off_in,
			काष्ठा file *out, loff_t __user *off_out,
			माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा pipe_inode_info *ipipe;
	काष्ठा pipe_inode_info *opipe;
	loff_t offset, *__off_in = शून्य, *__off_out = शून्य;
	दीर्घ ret;

	ipipe = get_pipe_info(in, true);
	opipe = get_pipe_info(out, true);

	अगर (ipipe && off_in)
		वापस -ESPIPE;
	अगर (opipe && off_out)
		वापस -ESPIPE;

	अगर (off_out) अणु
		अगर (copy_from_user(&offset, off_out, माप(loff_t)))
			वापस -EFAULT;
		__off_out = &offset;
	पूर्ण
	अगर (off_in) अणु
		अगर (copy_from_user(&offset, off_in, माप(loff_t)))
			वापस -EFAULT;
		__off_in = &offset;
	पूर्ण

	ret = करो_splice(in, __off_in, out, __off_out, len, flags);
	अगर (ret < 0)
		वापस ret;

	अगर (__off_out && copy_to_user(off_out, __off_out, माप(loff_t)))
		वापस -EFAULT;
	अगर (__off_in && copy_to_user(off_in, __off_in, माप(loff_t)))
		वापस -EFAULT;

	वापस ret;
पूर्ण

अटल पूर्णांक iter_to_pipe(काष्ठा iov_iter *from,
			काष्ठा pipe_inode_info *pipe,
			अचिन्हित flags)
अणु
	काष्ठा pipe_buffer buf = अणु
		.ops = &user_page_pipe_buf_ops,
		.flags = flags
	पूर्ण;
	माप_प्रकार total = 0;
	पूर्णांक ret = 0;
	bool failed = false;

	जबतक (iov_iter_count(from) && !failed) अणु
		काष्ठा page *pages[16];
		sमाप_प्रकार copied;
		माप_प्रकार start;
		पूर्णांक n;

		copied = iov_iter_get_pages(from, pages, ~0UL, 16, &start);
		अगर (copied <= 0) अणु
			ret = copied;
			अवरोध;
		पूर्ण

		क्रम (n = 0; copied; n++, start = 0) अणु
			पूर्णांक size = min_t(पूर्णांक, copied, PAGE_SIZE - start);
			अगर (!failed) अणु
				buf.page = pages[n];
				buf.offset = start;
				buf.len = size;
				ret = add_to_pipe(pipe, &buf);
				अगर (unlikely(ret < 0)) अणु
					failed = true;
				पूर्ण अन्यथा अणु
					iov_iter_advance(from, ret);
					total += ret;
				पूर्ण
			पूर्ण अन्यथा अणु
				put_page(pages[n]);
			पूर्ण
			copied -= size;
		पूर्ण
	पूर्ण
	वापस total ? total : ret;
पूर्ण

अटल पूर्णांक pipe_to_user(काष्ठा pipe_inode_info *pipe, काष्ठा pipe_buffer *buf,
			काष्ठा splice_desc *sd)
अणु
	पूर्णांक n = copy_page_to_iter(buf->page, buf->offset, sd->len, sd->u.data);
	वापस n == sd->len ? n : -EFAULT;
पूर्ण

/*
 * For lack of a better implementation, implement vmsplice() to userspace
 * as a simple copy of the pipes pages to the user iov.
 */
अटल दीर्घ vmsplice_to_user(काष्ठा file *file, काष्ठा iov_iter *iter,
			     अचिन्हित पूर्णांक flags)
अणु
	काष्ठा pipe_inode_info *pipe = get_pipe_info(file, true);
	काष्ठा splice_desc sd = अणु
		.total_len = iov_iter_count(iter),
		.flags = flags,
		.u.data = iter
	पूर्ण;
	दीर्घ ret = 0;

	अगर (!pipe)
		वापस -EBADF;

	अगर (sd.total_len) अणु
		pipe_lock(pipe);
		ret = __splice_from_pipe(pipe, &sd, pipe_to_user);
		pipe_unlock(pipe);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * vmsplice splices a user address range पूर्णांकo a pipe. It can be thought of
 * as splice-from-memory, where the regular splice is splice-from-file (or
 * to file). In both हालs the output is a pipe, naturally.
 */
अटल दीर्घ vmsplice_to_pipe(काष्ठा file *file, काष्ठा iov_iter *iter,
			     अचिन्हित पूर्णांक flags)
अणु
	काष्ठा pipe_inode_info *pipe;
	दीर्घ ret = 0;
	अचिन्हित buf_flag = 0;

	अगर (flags & SPLICE_F_GIFT)
		buf_flag = PIPE_BUF_FLAG_GIFT;

	pipe = get_pipe_info(file, true);
	अगर (!pipe)
		वापस -EBADF;

	pipe_lock(pipe);
	ret = रुको_क्रम_space(pipe, flags);
	अगर (!ret)
		ret = iter_to_pipe(iter, pipe, buf_flag);
	pipe_unlock(pipe);
	अगर (ret > 0)
		wakeup_pipe_पढ़ोers(pipe);
	वापस ret;
पूर्ण

अटल पूर्णांक vmsplice_type(काष्ठा fd f, पूर्णांक *type)
अणु
	अगर (!f.file)
		वापस -EBADF;
	अगर (f.file->f_mode & FMODE_WRITE) अणु
		*type = WRITE;
	पूर्ण अन्यथा अगर (f.file->f_mode & FMODE_READ) अणु
		*type = READ;
	पूर्ण अन्यथा अणु
		fdput(f);
		वापस -EBADF;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Note that vmsplice only really supports true splicing _from_ user memory
 * to a pipe, not the other way around. Splicing from user memory is a simple
 * operation that can be supported without any funky alignment restrictions
 * or nasty vm tricks. We simply map in the user memory and fill them पूर्णांकo
 * a pipe. The reverse isn't quite as easy, though. There are two possible
 * solutions क्रम that:
 *
 *	- स_नकल() the data पूर्णांकernally, at which poपूर्णांक we might as well just
 *	  करो a regular पढ़ो() on the buffer anyway.
 *	- Lots of nasty vm tricks, that are neither fast nor flexible (it
 *	  has restriction limitations on both ends of the pipe).
 *
 * Currently we punt and implement it as a normal copy, see pipe_to_user().
 *
 */
SYSCALL_DEFINE4(vmsplice, पूर्णांक, fd, स्थिर काष्ठा iovec __user *, uiov,
		अचिन्हित दीर्घ, nr_segs, अचिन्हित पूर्णांक, flags)
अणु
	काष्ठा iovec iovstack[UIO_FASTIOV];
	काष्ठा iovec *iov = iovstack;
	काष्ठा iov_iter iter;
	sमाप_प्रकार error;
	काष्ठा fd f;
	पूर्णांक type;

	अगर (unlikely(flags & ~SPLICE_F_ALL))
		वापस -EINVAL;

	f = fdget(fd);
	error = vmsplice_type(f, &type);
	अगर (error)
		वापस error;

	error = import_iovec(type, uiov, nr_segs,
			     ARRAY_SIZE(iovstack), &iov, &iter);
	अगर (error < 0)
		जाओ out_fdput;

	अगर (!iov_iter_count(&iter))
		error = 0;
	अन्यथा अगर (iov_iter_rw(&iter) == WRITE)
		error = vmsplice_to_pipe(f.file, &iter, flags);
	अन्यथा
		error = vmsplice_to_user(f.file, &iter, flags);

	kमुक्त(iov);
out_fdput:
	fdput(f);
	वापस error;
पूर्ण

SYSCALL_DEFINE6(splice, पूर्णांक, fd_in, loff_t __user *, off_in,
		पूर्णांक, fd_out, loff_t __user *, off_out,
		माप_प्रकार, len, अचिन्हित पूर्णांक, flags)
अणु
	काष्ठा fd in, out;
	दीर्घ error;

	अगर (unlikely(!len))
		वापस 0;

	अगर (unlikely(flags & ~SPLICE_F_ALL))
		वापस -EINVAL;

	error = -EBADF;
	in = fdget(fd_in);
	अगर (in.file) अणु
		out = fdget(fd_out);
		अगर (out.file) अणु
			error = __करो_splice(in.file, off_in, out.file, off_out,
						len, flags);
			fdput(out);
		पूर्ण
		fdput(in);
	पूर्ण
	वापस error;
पूर्ण

/*
 * Make sure there's data to पढ़ो. Wait क्रम input अगर we can, otherwise
 * वापस an appropriate error.
 */
अटल पूर्णांक ipipe_prep(काष्ठा pipe_inode_info *pipe, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक ret;

	/*
	 * Check the pipe occupancy without the inode lock first. This function
	 * is speculative anyways, so missing one is ok.
	 */
	अगर (!pipe_empty(pipe->head, pipe->tail))
		वापस 0;

	ret = 0;
	pipe_lock(pipe);

	जबतक (pipe_empty(pipe->head, pipe->tail)) अणु
		अगर (संकेत_pending(current)) अणु
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		अगर (!pipe->ग_लिखोrs)
			अवरोध;
		अगर (flags & SPLICE_F_NONBLOCK) अणु
			ret = -EAGAIN;
			अवरोध;
		पूर्ण
		pipe_रुको_पढ़ोable(pipe);
	पूर्ण

	pipe_unlock(pipe);
	वापस ret;
पूर्ण

/*
 * Make sure there's ग_लिखोable room. Wait क्रम room अगर we can, otherwise
 * वापस an appropriate error.
 */
अटल पूर्णांक opipe_prep(काष्ठा pipe_inode_info *pipe, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक ret;

	/*
	 * Check pipe occupancy without the inode lock first. This function
	 * is speculative anyways, so missing one is ok.
	 */
	अगर (!pipe_full(pipe->head, pipe->tail, pipe->max_usage))
		वापस 0;

	ret = 0;
	pipe_lock(pipe);

	जबतक (pipe_full(pipe->head, pipe->tail, pipe->max_usage)) अणु
		अगर (!pipe->पढ़ोers) अणु
			send_sig(SIGPIPE, current, 0);
			ret = -EPIPE;
			अवरोध;
		पूर्ण
		अगर (flags & SPLICE_F_NONBLOCK) अणु
			ret = -EAGAIN;
			अवरोध;
		पूर्ण
		अगर (संकेत_pending(current)) अणु
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		pipe_रुको_writable(pipe);
	पूर्ण

	pipe_unlock(pipe);
	वापस ret;
पूर्ण

/*
 * Splice contents of ipipe to opipe.
 */
अटल पूर्णांक splice_pipe_to_pipe(काष्ठा pipe_inode_info *ipipe,
			       काष्ठा pipe_inode_info *opipe,
			       माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा pipe_buffer *ibuf, *obuf;
	अचिन्हित पूर्णांक i_head, o_head;
	अचिन्हित पूर्णांक i_tail, o_tail;
	अचिन्हित पूर्णांक i_mask, o_mask;
	पूर्णांक ret = 0;
	bool input_wakeup = false;


retry:
	ret = ipipe_prep(ipipe, flags);
	अगर (ret)
		वापस ret;

	ret = opipe_prep(opipe, flags);
	अगर (ret)
		वापस ret;

	/*
	 * Potential ABBA deadlock, work around it by ordering lock
	 * grabbing by pipe info address. Otherwise two dअगरferent processes
	 * could deadlock (one करोing tee from A -> B, the other from B -> A).
	 */
	pipe_द्विगुन_lock(ipipe, opipe);

	i_tail = ipipe->tail;
	i_mask = ipipe->ring_size - 1;
	o_head = opipe->head;
	o_mask = opipe->ring_size - 1;

	करो अणु
		माप_प्रकार o_len;

		अगर (!opipe->पढ़ोers) अणु
			send_sig(SIGPIPE, current, 0);
			अगर (!ret)
				ret = -EPIPE;
			अवरोध;
		पूर्ण

		i_head = ipipe->head;
		o_tail = opipe->tail;

		अगर (pipe_empty(i_head, i_tail) && !ipipe->ग_लिखोrs)
			अवरोध;

		/*
		 * Cannot make any progress, because either the input
		 * pipe is empty or the output pipe is full.
		 */
		अगर (pipe_empty(i_head, i_tail) ||
		    pipe_full(o_head, o_tail, opipe->max_usage)) अणु
			/* Alपढ़ोy processed some buffers, अवरोध */
			अगर (ret)
				अवरोध;

			अगर (flags & SPLICE_F_NONBLOCK) अणु
				ret = -EAGAIN;
				अवरोध;
			पूर्ण

			/*
			 * We raced with another पढ़ोer/ग_लिखोr and haven't
			 * managed to process any buffers.  A zero वापस
			 * value means खातापूर्ण, so retry instead.
			 */
			pipe_unlock(ipipe);
			pipe_unlock(opipe);
			जाओ retry;
		पूर्ण

		ibuf = &ipipe->bufs[i_tail & i_mask];
		obuf = &opipe->bufs[o_head & o_mask];

		अगर (len >= ibuf->len) अणु
			/*
			 * Simply move the whole buffer from ipipe to opipe
			 */
			*obuf = *ibuf;
			ibuf->ops = शून्य;
			i_tail++;
			ipipe->tail = i_tail;
			input_wakeup = true;
			o_len = obuf->len;
			o_head++;
			opipe->head = o_head;
		पूर्ण अन्यथा अणु
			/*
			 * Get a reference to this pipe buffer,
			 * so we can copy the contents over.
			 */
			अगर (!pipe_buf_get(ipipe, ibuf)) अणु
				अगर (ret == 0)
					ret = -EFAULT;
				अवरोध;
			पूर्ण
			*obuf = *ibuf;

			/*
			 * Don't inherit the gअगरt and merge flags, we need to
			 * prevent multiple steals of this page.
			 */
			obuf->flags &= ~PIPE_BUF_FLAG_GIFT;
			obuf->flags &= ~PIPE_BUF_FLAG_CAN_MERGE;

			obuf->len = len;
			ibuf->offset += len;
			ibuf->len -= len;
			o_len = len;
			o_head++;
			opipe->head = o_head;
		पूर्ण
		ret += o_len;
		len -= o_len;
	पूर्ण जबतक (len);

	pipe_unlock(ipipe);
	pipe_unlock(opipe);

	/*
	 * If we put data in the output pipe, wakeup any potential पढ़ोers.
	 */
	अगर (ret > 0)
		wakeup_pipe_पढ़ोers(opipe);

	अगर (input_wakeup)
		wakeup_pipe_ग_लिखोrs(ipipe);

	वापस ret;
पूर्ण

/*
 * Link contents of ipipe to opipe.
 */
अटल पूर्णांक link_pipe(काष्ठा pipe_inode_info *ipipe,
		     काष्ठा pipe_inode_info *opipe,
		     माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा pipe_buffer *ibuf, *obuf;
	अचिन्हित पूर्णांक i_head, o_head;
	अचिन्हित पूर्णांक i_tail, o_tail;
	अचिन्हित पूर्णांक i_mask, o_mask;
	पूर्णांक ret = 0;

	/*
	 * Potential ABBA deadlock, work around it by ordering lock
	 * grabbing by pipe info address. Otherwise two dअगरferent processes
	 * could deadlock (one करोing tee from A -> B, the other from B -> A).
	 */
	pipe_द्विगुन_lock(ipipe, opipe);

	i_tail = ipipe->tail;
	i_mask = ipipe->ring_size - 1;
	o_head = opipe->head;
	o_mask = opipe->ring_size - 1;

	करो अणु
		अगर (!opipe->पढ़ोers) अणु
			send_sig(SIGPIPE, current, 0);
			अगर (!ret)
				ret = -EPIPE;
			अवरोध;
		पूर्ण

		i_head = ipipe->head;
		o_tail = opipe->tail;

		/*
		 * If we have iterated all input buffers or run out of
		 * output room, अवरोध.
		 */
		अगर (pipe_empty(i_head, i_tail) ||
		    pipe_full(o_head, o_tail, opipe->max_usage))
			अवरोध;

		ibuf = &ipipe->bufs[i_tail & i_mask];
		obuf = &opipe->bufs[o_head & o_mask];

		/*
		 * Get a reference to this pipe buffer,
		 * so we can copy the contents over.
		 */
		अगर (!pipe_buf_get(ipipe, ibuf)) अणु
			अगर (ret == 0)
				ret = -EFAULT;
			अवरोध;
		पूर्ण

		*obuf = *ibuf;

		/*
		 * Don't inherit the gअगरt and merge flag, we need to prevent
		 * multiple steals of this page.
		 */
		obuf->flags &= ~PIPE_BUF_FLAG_GIFT;
		obuf->flags &= ~PIPE_BUF_FLAG_CAN_MERGE;

		अगर (obuf->len > len)
			obuf->len = len;
		ret += obuf->len;
		len -= obuf->len;

		o_head++;
		opipe->head = o_head;
		i_tail++;
	पूर्ण जबतक (len);

	pipe_unlock(ipipe);
	pipe_unlock(opipe);

	/*
	 * If we put data in the output pipe, wakeup any potential पढ़ोers.
	 */
	अगर (ret > 0)
		wakeup_pipe_पढ़ोers(opipe);

	वापस ret;
पूर्ण

/*
 * This is a tee(1) implementation that works on pipes. It करोesn't copy
 * any data, it simply references the 'in' pages on the 'out' pipe.
 * The 'flags' used are the SPLICE_F_* variants, currently the only
 * applicable one is SPLICE_F_NONBLOCK.
 */
दीर्घ करो_tee(काष्ठा file *in, काष्ठा file *out, माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा pipe_inode_info *ipipe = get_pipe_info(in, true);
	काष्ठा pipe_inode_info *opipe = get_pipe_info(out, true);
	पूर्णांक ret = -EINVAL;

	अगर (unlikely(!(in->f_mode & FMODE_READ) ||
		     !(out->f_mode & FMODE_WRITE)))
		वापस -EBADF;

	/*
	 * Duplicate the contents of ipipe to opipe without actually
	 * copying the data.
	 */
	अगर (ipipe && opipe && ipipe != opipe) अणु
		अगर ((in->f_flags | out->f_flags) & O_NONBLOCK)
			flags |= SPLICE_F_NONBLOCK;

		/*
		 * Keep going, unless we encounter an error. The ipipe/opipe
		 * ordering करोesn't really matter.
		 */
		ret = ipipe_prep(ipipe, flags);
		अगर (!ret) अणु
			ret = opipe_prep(opipe, flags);
			अगर (!ret)
				ret = link_pipe(ipipe, opipe, len, flags);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

SYSCALL_DEFINE4(tee, पूर्णांक, fdin, पूर्णांक, fकरोut, माप_प्रकार, len, अचिन्हित पूर्णांक, flags)
अणु
	काष्ठा fd in, out;
	पूर्णांक error;

	अगर (unlikely(flags & ~SPLICE_F_ALL))
		वापस -EINVAL;

	अगर (unlikely(!len))
		वापस 0;

	error = -EBADF;
	in = fdget(fdin);
	अगर (in.file) अणु
		out = fdget(fकरोut);
		अगर (out.file) अणु
			error = करो_tee(in.file, out.file, len, flags);
			fdput(out);
		पूर्ण
 		fdput(in);
 	पूर्ण

	वापस error;
पूर्ण
