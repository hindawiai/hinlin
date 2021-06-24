<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/pipe.c
 *
 *  Copyright (C) 1991, 1992, 1999  Linus Torvalds
 */

#समावेश <linux/mm.h>
#समावेश <linux/file.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/log2.h>
#समावेश <linux/mount.h>
#समावेश <linux/pseuकरो_fs.h>
#समावेश <linux/magic.h>
#समावेश <linux/pipe_fs_i.h>
#समावेश <linux/uपन.स>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/audit.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/watch_queue.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ioctls.h>

#समावेश "internal.h"

/*
 * The max size that a non-root user is allowed to grow the pipe. Can
 * be set by root in /proc/sys/fs/pipe-max-size
 */
अचिन्हित पूर्णांक pipe_max_size = 1048576;

/* Maximum allocatable pages per user. Hard limit is unset by शेष, soft
 * matches शेष values.
 */
अचिन्हित दीर्घ pipe_user_pages_hard;
अचिन्हित दीर्घ pipe_user_pages_soft = PIPE_DEF_BUFFERS * INR_OPEN_CUR;

/*
 * We use head and tail indices that aren't masked off, except at the poपूर्णांक of
 * dereference, but rather they're allowed to wrap naturally.  This means there
 * isn't a dead spot in the buffer, but the ring has to be a घातer of two and
 * <= 2^31.
 * -- David Howells 2019-09-23.
 *
 * Reads with count = 0 should always वापस 0.
 * -- Julian Bradfield 1999-06-07.
 *
 * FIFOs and Pipes now generate SIGIO क्रम both पढ़ोers and ग_लिखोrs.
 * -- Jeremy Elson <jelson@circlemud.org> 2001-08-16
 *
 * pipe_पढ़ो & ग_लिखो cleanup
 * -- Manfred Spraul <manfred@colorfullअगरe.com> 2002-05-09
 */

अटल व्योम pipe_lock_nested(काष्ठा pipe_inode_info *pipe, पूर्णांक subclass)
अणु
	अगर (pipe->files)
		mutex_lock_nested(&pipe->mutex, subclass);
पूर्ण

व्योम pipe_lock(काष्ठा pipe_inode_info *pipe)
अणु
	/*
	 * pipe_lock() nests non-pipe inode locks (क्रम writing to a file)
	 */
	pipe_lock_nested(pipe, I_MUTEX_PARENT);
पूर्ण
EXPORT_SYMBOL(pipe_lock);

व्योम pipe_unlock(काष्ठा pipe_inode_info *pipe)
अणु
	अगर (pipe->files)
		mutex_unlock(&pipe->mutex);
पूर्ण
EXPORT_SYMBOL(pipe_unlock);

अटल अंतरभूत व्योम __pipe_lock(काष्ठा pipe_inode_info *pipe)
अणु
	mutex_lock_nested(&pipe->mutex, I_MUTEX_PARENT);
पूर्ण

अटल अंतरभूत व्योम __pipe_unlock(काष्ठा pipe_inode_info *pipe)
अणु
	mutex_unlock(&pipe->mutex);
पूर्ण

व्योम pipe_द्विगुन_lock(काष्ठा pipe_inode_info *pipe1,
		      काष्ठा pipe_inode_info *pipe2)
अणु
	BUG_ON(pipe1 == pipe2);

	अगर (pipe1 < pipe2) अणु
		pipe_lock_nested(pipe1, I_MUTEX_PARENT);
		pipe_lock_nested(pipe2, I_MUTEX_CHILD);
	पूर्ण अन्यथा अणु
		pipe_lock_nested(pipe2, I_MUTEX_PARENT);
		pipe_lock_nested(pipe1, I_MUTEX_CHILD);
	पूर्ण
पूर्ण

अटल व्योम anon_pipe_buf_release(काष्ठा pipe_inode_info *pipe,
				  काष्ठा pipe_buffer *buf)
अणु
	काष्ठा page *page = buf->page;

	/*
	 * If nobody अन्यथा uses this page, and we करोn't alपढ़ोy have a
	 * temporary page, let's keep track of it as a one-deep
	 * allocation cache. (Otherwise just release our reference to it)
	 */
	अगर (page_count(page) == 1 && !pipe->पंचांगp_page)
		pipe->पंचांगp_page = page;
	अन्यथा
		put_page(page);
पूर्ण

अटल bool anon_pipe_buf_try_steal(काष्ठा pipe_inode_info *pipe,
		काष्ठा pipe_buffer *buf)
अणु
	काष्ठा page *page = buf->page;

	अगर (page_count(page) != 1)
		वापस false;
	memcg_kmem_unअक्षरge_page(page, 0);
	__SetPageLocked(page);
	वापस true;
पूर्ण

/**
 * generic_pipe_buf_try_steal - attempt to take ownership of a &pipe_buffer
 * @pipe:	the pipe that the buffer beदीर्घs to
 * @buf:	the buffer to attempt to steal
 *
 * Description:
 *	This function attempts to steal the &काष्ठा page attached to
 *	@buf. If successful, this function वापसs 0 and वापसs with
 *	the page locked. The caller may then reuse the page क्रम whatever
 *	he wishes; the typical use is insertion पूर्णांकo a dअगरferent file
 *	page cache.
 */
bool generic_pipe_buf_try_steal(काष्ठा pipe_inode_info *pipe,
		काष्ठा pipe_buffer *buf)
अणु
	काष्ठा page *page = buf->page;

	/*
	 * A reference of one is golden, that means that the owner of this
	 * page is the only one holding a reference to it. lock the page
	 * and वापस OK.
	 */
	अगर (page_count(page) == 1) अणु
		lock_page(page);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL(generic_pipe_buf_try_steal);

/**
 * generic_pipe_buf_get - get a reference to a &काष्ठा pipe_buffer
 * @pipe:	the pipe that the buffer beदीर्घs to
 * @buf:	the buffer to get a reference to
 *
 * Description:
 *	This function grअसल an extra reference to @buf. It's used in
 *	the tee() प्रणाली call, when we duplicate the buffers in one
 *	pipe पूर्णांकo another.
 */
bool generic_pipe_buf_get(काष्ठा pipe_inode_info *pipe, काष्ठा pipe_buffer *buf)
अणु
	वापस try_get_page(buf->page);
पूर्ण
EXPORT_SYMBOL(generic_pipe_buf_get);

/**
 * generic_pipe_buf_release - put a reference to a &काष्ठा pipe_buffer
 * @pipe:	the pipe that the buffer beदीर्घs to
 * @buf:	the buffer to put a reference to
 *
 * Description:
 *	This function releases a reference to @buf.
 */
व्योम generic_pipe_buf_release(काष्ठा pipe_inode_info *pipe,
			      काष्ठा pipe_buffer *buf)
अणु
	put_page(buf->page);
पूर्ण
EXPORT_SYMBOL(generic_pipe_buf_release);

अटल स्थिर काष्ठा pipe_buf_operations anon_pipe_buf_ops = अणु
	.release	= anon_pipe_buf_release,
	.try_steal	= anon_pipe_buf_try_steal,
	.get		= generic_pipe_buf_get,
पूर्ण;

/* Done जबतक रुकोing without holding the pipe lock - thus the READ_ONCE() */
अटल अंतरभूत bool pipe_पढ़ोable(स्थिर काष्ठा pipe_inode_info *pipe)
अणु
	अचिन्हित पूर्णांक head = READ_ONCE(pipe->head);
	अचिन्हित पूर्णांक tail = READ_ONCE(pipe->tail);
	अचिन्हित पूर्णांक ग_लिखोrs = READ_ONCE(pipe->ग_लिखोrs);

	वापस !pipe_empty(head, tail) || !ग_लिखोrs;
पूर्ण

अटल sमाप_प्रकार
pipe_पढ़ो(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	माप_प्रकार total_len = iov_iter_count(to);
	काष्ठा file *filp = iocb->ki_filp;
	काष्ठा pipe_inode_info *pipe = filp->निजी_data;
	bool was_full, wake_next_पढ़ोer = false;
	sमाप_प्रकार ret;

	/* Null पढ़ो succeeds. */
	अगर (unlikely(total_len == 0))
		वापस 0;

	ret = 0;
	__pipe_lock(pipe);

	/*
	 * We only wake up ग_लिखोrs अगर the pipe was full when we started
	 * पढ़ोing in order to aव्योम unnecessary wakeups.
	 *
	 * But when we करो wake up ग_लिखोrs, we करो so using a sync wakeup
	 * (WF_SYNC), because we want them to get going and generate more
	 * data क्रम us.
	 */
	was_full = pipe_full(pipe->head, pipe->tail, pipe->max_usage);
	क्रम (;;) अणु
		अचिन्हित पूर्णांक head = pipe->head;
		अचिन्हित पूर्णांक tail = pipe->tail;
		अचिन्हित पूर्णांक mask = pipe->ring_size - 1;

#अगर_घोषित CONFIG_WATCH_QUEUE
		अगर (pipe->note_loss) अणु
			काष्ठा watch_notअगरication n;

			अगर (total_len < 8) अणु
				अगर (ret == 0)
					ret = -ENOBUFS;
				अवरोध;
			पूर्ण

			n.type = WATCH_TYPE_META;
			n.subtype = WATCH_META_LOSS_NOTIFICATION;
			n.info = watch_माप(n);
			अगर (copy_to_iter(&n, माप(n), to) != माप(n)) अणु
				अगर (ret == 0)
					ret = -EFAULT;
				अवरोध;
			पूर्ण
			ret += माप(n);
			total_len -= माप(n);
			pipe->note_loss = false;
		पूर्ण
#पूर्ण_अगर

		अगर (!pipe_empty(head, tail)) अणु
			काष्ठा pipe_buffer *buf = &pipe->bufs[tail & mask];
			माप_प्रकार अक्षरs = buf->len;
			माप_प्रकार written;
			पूर्णांक error;

			अगर (अक्षरs > total_len) अणु
				अगर (buf->flags & PIPE_BUF_FLAG_WHOLE) अणु
					अगर (ret == 0)
						ret = -ENOBUFS;
					अवरोध;
				पूर्ण
				अक्षरs = total_len;
			पूर्ण

			error = pipe_buf_confirm(pipe, buf);
			अगर (error) अणु
				अगर (!ret)
					ret = error;
				अवरोध;
			पूर्ण

			written = copy_page_to_iter(buf->page, buf->offset, अक्षरs, to);
			अगर (unlikely(written < अक्षरs)) अणु
				अगर (!ret)
					ret = -EFAULT;
				अवरोध;
			पूर्ण
			ret += अक्षरs;
			buf->offset += अक्षरs;
			buf->len -= अक्षरs;

			/* Was it a packet buffer? Clean up and निकास */
			अगर (buf->flags & PIPE_BUF_FLAG_PACKET) अणु
				total_len = अक्षरs;
				buf->len = 0;
			पूर्ण

			अगर (!buf->len) अणु
				pipe_buf_release(pipe, buf);
				spin_lock_irq(&pipe->rd_रुको.lock);
#अगर_घोषित CONFIG_WATCH_QUEUE
				अगर (buf->flags & PIPE_BUF_FLAG_LOSS)
					pipe->note_loss = true;
#पूर्ण_अगर
				tail++;
				pipe->tail = tail;
				spin_unlock_irq(&pipe->rd_रुको.lock);
			पूर्ण
			total_len -= अक्षरs;
			अगर (!total_len)
				अवरोध;	/* common path: पढ़ो succeeded */
			अगर (!pipe_empty(head, tail))	/* More to करो? */
				जारी;
		पूर्ण

		अगर (!pipe->ग_लिखोrs)
			अवरोध;
		अगर (ret)
			अवरोध;
		अगर (filp->f_flags & O_NONBLOCK) अणु
			ret = -EAGAIN;
			अवरोध;
		पूर्ण
		__pipe_unlock(pipe);

		/*
		 * We only get here अगर we didn't actually पढ़ो anything.
		 *
		 * However, we could have seen (and हटाओd) a zero-sized
		 * pipe buffer, and might have made space in the buffers
		 * that way.
		 *
		 * You can't make zero-sized pipe buffers by करोing an empty
		 * ग_लिखो (not even in packet mode), but they can happen अगर
		 * the ग_लिखोr माला_लो an EFAULT when trying to fill a buffer
		 * that alपढ़ोy got allocated and inserted in the buffer
		 * array.
		 *
		 * So we still need to wake up any pending ग_लिखोrs in the
		 * _very_ unlikely हाल that the pipe was full, but we got
		 * no data.
		 */
		अगर (unlikely(was_full)) अणु
			wake_up_पूर्णांकerruptible_sync_poll(&pipe->wr_रुको, EPOLLOUT | EPOLLWRNORM);
			समाप्त_fasync(&pipe->fasync_ग_लिखोrs, SIGIO, POLL_OUT);
		पूर्ण

		/*
		 * But because we didn't पढ़ो anything, at this poपूर्णांक we can
		 * just वापस directly with -ERESTARTSYS अगर we're पूर्णांकerrupted,
		 * since we've done any required wakeups and there's no need
		 * to mark anything accessed. And we've dropped the lock.
		 */
		अगर (रुको_event_पूर्णांकerruptible_exclusive(pipe->rd_रुको, pipe_पढ़ोable(pipe)) < 0)
			वापस -ERESTARTSYS;

		__pipe_lock(pipe);
		was_full = pipe_full(pipe->head, pipe->tail, pipe->max_usage);
		wake_next_पढ़ोer = true;
	पूर्ण
	अगर (pipe_empty(pipe->head, pipe->tail))
		wake_next_पढ़ोer = false;
	__pipe_unlock(pipe);

	अगर (was_full) अणु
		wake_up_पूर्णांकerruptible_sync_poll(&pipe->wr_रुको, EPOLLOUT | EPOLLWRNORM);
		समाप्त_fasync(&pipe->fasync_ग_लिखोrs, SIGIO, POLL_OUT);
	पूर्ण
	अगर (wake_next_पढ़ोer)
		wake_up_पूर्णांकerruptible_sync_poll(&pipe->rd_रुको, EPOLLIN | EPOLLRDNORM);
	अगर (ret > 0)
		file_accessed(filp);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक is_packetized(काष्ठा file *file)
अणु
	वापस (file->f_flags & O_सूचीECT) != 0;
पूर्ण

/* Done जबतक रुकोing without holding the pipe lock - thus the READ_ONCE() */
अटल अंतरभूत bool pipe_writable(स्थिर काष्ठा pipe_inode_info *pipe)
अणु
	अचिन्हित पूर्णांक head = READ_ONCE(pipe->head);
	अचिन्हित पूर्णांक tail = READ_ONCE(pipe->tail);
	अचिन्हित पूर्णांक max_usage = READ_ONCE(pipe->max_usage);

	वापस !pipe_full(head, tail, max_usage) ||
		!READ_ONCE(pipe->पढ़ोers);
पूर्ण

अटल sमाप_प्रकार
pipe_ग_लिखो(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *filp = iocb->ki_filp;
	काष्ठा pipe_inode_info *pipe = filp->निजी_data;
	अचिन्हित पूर्णांक head;
	sमाप_प्रकार ret = 0;
	माप_प्रकार total_len = iov_iter_count(from);
	sमाप_प्रकार अक्षरs;
	bool was_empty = false;
	bool wake_next_ग_लिखोr = false;

	/* Null ग_लिखो succeeds. */
	अगर (unlikely(total_len == 0))
		वापस 0;

	__pipe_lock(pipe);

	अगर (!pipe->पढ़ोers) अणु
		send_sig(SIGPIPE, current, 0);
		ret = -EPIPE;
		जाओ out;
	पूर्ण

#अगर_घोषित CONFIG_WATCH_QUEUE
	अगर (pipe->watch_queue) अणु
		ret = -EXDEV;
		जाओ out;
	पूर्ण
#पूर्ण_अगर

	/*
	 * Only wake up अगर the pipe started out empty, since
	 * otherwise there should be no पढ़ोers रुकोing.
	 *
	 * If it wasn't empty we try to merge new data पूर्णांकo
	 * the last buffer.
	 *
	 * That naturally merges small ग_लिखोs, but it also
	 * page-aligs the rest of the ग_लिखोs क्रम large ग_लिखोs
	 * spanning multiple pages.
	 */
	head = pipe->head;
	was_empty = pipe_empty(head, pipe->tail);
	अक्षरs = total_len & (PAGE_SIZE-1);
	अगर (अक्षरs && !was_empty) अणु
		अचिन्हित पूर्णांक mask = pipe->ring_size - 1;
		काष्ठा pipe_buffer *buf = &pipe->bufs[(head - 1) & mask];
		पूर्णांक offset = buf->offset + buf->len;

		अगर ((buf->flags & PIPE_BUF_FLAG_CAN_MERGE) &&
		    offset + अक्षरs <= PAGE_SIZE) अणु
			ret = pipe_buf_confirm(pipe, buf);
			अगर (ret)
				जाओ out;

			ret = copy_page_from_iter(buf->page, offset, अक्षरs, from);
			अगर (unlikely(ret < अक्षरs)) अणु
				ret = -EFAULT;
				जाओ out;
			पूर्ण

			buf->len += ret;
			अगर (!iov_iter_count(from))
				जाओ out;
		पूर्ण
	पूर्ण

	क्रम (;;) अणु
		अगर (!pipe->पढ़ोers) अणु
			send_sig(SIGPIPE, current, 0);
			अगर (!ret)
				ret = -EPIPE;
			अवरोध;
		पूर्ण

		head = pipe->head;
		अगर (!pipe_full(head, pipe->tail, pipe->max_usage)) अणु
			अचिन्हित पूर्णांक mask = pipe->ring_size - 1;
			काष्ठा pipe_buffer *buf = &pipe->bufs[head & mask];
			काष्ठा page *page = pipe->पंचांगp_page;
			पूर्णांक copied;

			अगर (!page) अणु
				page = alloc_page(GFP_HIGHUSER | __GFP_ACCOUNT);
				अगर (unlikely(!page)) अणु
					ret = ret ? : -ENOMEM;
					अवरोध;
				पूर्ण
				pipe->पंचांगp_page = page;
			पूर्ण

			/* Allocate a slot in the ring in advance and attach an
			 * empty buffer.  If we fault or otherwise fail to use
			 * it, either the पढ़ोer will consume it or it'll still
			 * be there क्रम the next ग_लिखो.
			 */
			spin_lock_irq(&pipe->rd_रुको.lock);

			head = pipe->head;
			अगर (pipe_full(head, pipe->tail, pipe->max_usage)) अणु
				spin_unlock_irq(&pipe->rd_रुको.lock);
				जारी;
			पूर्ण

			pipe->head = head + 1;
			spin_unlock_irq(&pipe->rd_रुको.lock);

			/* Insert it पूर्णांकo the buffer array */
			buf = &pipe->bufs[head & mask];
			buf->page = page;
			buf->ops = &anon_pipe_buf_ops;
			buf->offset = 0;
			buf->len = 0;
			अगर (is_packetized(filp))
				buf->flags = PIPE_BUF_FLAG_PACKET;
			अन्यथा
				buf->flags = PIPE_BUF_FLAG_CAN_MERGE;
			pipe->पंचांगp_page = शून्य;

			copied = copy_page_from_iter(page, 0, PAGE_SIZE, from);
			अगर (unlikely(copied < PAGE_SIZE && iov_iter_count(from))) अणु
				अगर (!ret)
					ret = -EFAULT;
				अवरोध;
			पूर्ण
			ret += copied;
			buf->offset = 0;
			buf->len = copied;

			अगर (!iov_iter_count(from))
				अवरोध;
		पूर्ण

		अगर (!pipe_full(head, pipe->tail, pipe->max_usage))
			जारी;

		/* Wait क्रम buffer space to become available. */
		अगर (filp->f_flags & O_NONBLOCK) अणु
			अगर (!ret)
				ret = -EAGAIN;
			अवरोध;
		पूर्ण
		अगर (संकेत_pending(current)) अणु
			अगर (!ret)
				ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		/*
		 * We're going to release the pipe lock and रुको क्रम more
		 * space. We wake up any पढ़ोers अगर necessary, and then
		 * after रुकोing we need to re-check whether the pipe
		 * become empty जबतक we dropped the lock.
		 */
		__pipe_unlock(pipe);
		अगर (was_empty) अणु
			wake_up_पूर्णांकerruptible_sync_poll(&pipe->rd_रुको, EPOLLIN | EPOLLRDNORM);
			समाप्त_fasync(&pipe->fasync_पढ़ोers, SIGIO, POLL_IN);
		पूर्ण
		रुको_event_पूर्णांकerruptible_exclusive(pipe->wr_रुको, pipe_writable(pipe));
		__pipe_lock(pipe);
		was_empty = pipe_empty(pipe->head, pipe->tail);
		wake_next_ग_लिखोr = true;
	पूर्ण
out:
	अगर (pipe_full(pipe->head, pipe->tail, pipe->max_usage))
		wake_next_ग_लिखोr = false;
	__pipe_unlock(pipe);

	/*
	 * If we करो करो a wakeup event, we करो a 'sync' wakeup, because we
	 * want the पढ़ोer to start processing things asap, rather than
	 * leave the data pending.
	 *
	 * This is particularly important क्रम small ग_लिखोs, because of
	 * how (क्रम example) the GNU make jobserver uses small ग_लिखोs to
	 * wake up pending jobs
	 */
	अगर (was_empty) अणु
		wake_up_पूर्णांकerruptible_sync_poll(&pipe->rd_रुको, EPOLLIN | EPOLLRDNORM);
		समाप्त_fasync(&pipe->fasync_पढ़ोers, SIGIO, POLL_IN);
	पूर्ण
	अगर (wake_next_ग_लिखोr)
		wake_up_पूर्णांकerruptible_sync_poll(&pipe->wr_रुको, EPOLLOUT | EPOLLWRNORM);
	अगर (ret > 0 && sb_start_ग_लिखो_trylock(file_inode(filp)->i_sb)) अणु
		पूर्णांक err = file_update_समय(filp);
		अगर (err)
			ret = err;
		sb_end_ग_लिखो(file_inode(filp)->i_sb);
	पूर्ण
	वापस ret;
पूर्ण

अटल दीर्घ pipe_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा pipe_inode_info *pipe = filp->निजी_data;
	पूर्णांक count, head, tail, mask;

	चयन (cmd) अणु
	हाल FIONREAD:
		__pipe_lock(pipe);
		count = 0;
		head = pipe->head;
		tail = pipe->tail;
		mask = pipe->ring_size - 1;

		जबतक (tail != head) अणु
			count += pipe->bufs[tail & mask].len;
			tail++;
		पूर्ण
		__pipe_unlock(pipe);

		वापस put_user(count, (पूर्णांक __user *)arg);

#अगर_घोषित CONFIG_WATCH_QUEUE
	हाल IOC_WATCH_QUEUE_SET_SIZE: अणु
		पूर्णांक ret;
		__pipe_lock(pipe);
		ret = watch_queue_set_size(pipe, arg);
		__pipe_unlock(pipe);
		वापस ret;
	पूर्ण

	हाल IOC_WATCH_QUEUE_SET_FILTER:
		वापस watch_queue_set_filter(
			pipe, (काष्ठा watch_notअगरication_filter __user *)arg);
#पूर्ण_अगर

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

/* No kernel lock held - fine */
अटल __poll_t
pipe_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	__poll_t mask;
	काष्ठा pipe_inode_info *pipe = filp->निजी_data;
	अचिन्हित पूर्णांक head, tail;

	/*
	 * Reading pipe state only -- no need क्रम acquiring the semaphore.
	 *
	 * But because this is racy, the code has to add the
	 * entry to the poll table _first_ ..
	 */
	अगर (filp->f_mode & FMODE_READ)
		poll_रुको(filp, &pipe->rd_रुको, रुको);
	अगर (filp->f_mode & FMODE_WRITE)
		poll_रुको(filp, &pipe->wr_रुको, रुको);

	/*
	 * .. and only then can you करो the racy tests. That way,
	 * अगर something changes and you got it wrong, the poll
	 * table entry will wake you up and fix it.
	 */
	head = READ_ONCE(pipe->head);
	tail = READ_ONCE(pipe->tail);

	mask = 0;
	अगर (filp->f_mode & FMODE_READ) अणु
		अगर (!pipe_empty(head, tail))
			mask |= EPOLLIN | EPOLLRDNORM;
		अगर (!pipe->ग_लिखोrs && filp->f_version != pipe->w_counter)
			mask |= EPOLLHUP;
	पूर्ण

	अगर (filp->f_mode & FMODE_WRITE) अणु
		अगर (!pipe_full(head, tail, pipe->max_usage))
			mask |= EPOLLOUT | EPOLLWRNORM;
		/*
		 * Most Unices करो not set EPOLLERR क्रम FIFOs but on Linux they
		 * behave exactly like pipes क्रम poll().
		 */
		अगर (!pipe->पढ़ोers)
			mask |= EPOLLERR;
	पूर्ण

	वापस mask;
पूर्ण

अटल व्योम put_pipe_info(काष्ठा inode *inode, काष्ठा pipe_inode_info *pipe)
अणु
	पूर्णांक समाप्त = 0;

	spin_lock(&inode->i_lock);
	अगर (!--pipe->files) अणु
		inode->i_pipe = शून्य;
		समाप्त = 1;
	पूर्ण
	spin_unlock(&inode->i_lock);

	अगर (समाप्त)
		मुक्त_pipe_info(pipe);
पूर्ण

अटल पूर्णांक
pipe_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा pipe_inode_info *pipe = file->निजी_data;

	__pipe_lock(pipe);
	अगर (file->f_mode & FMODE_READ)
		pipe->पढ़ोers--;
	अगर (file->f_mode & FMODE_WRITE)
		pipe->ग_लिखोrs--;

	/* Was that the last पढ़ोer or ग_लिखोr, but not the other side? */
	अगर (!pipe->पढ़ोers != !pipe->ग_लिखोrs) अणु
		wake_up_पूर्णांकerruptible_all(&pipe->rd_रुको);
		wake_up_पूर्णांकerruptible_all(&pipe->wr_रुको);
		समाप्त_fasync(&pipe->fasync_पढ़ोers, SIGIO, POLL_IN);
		समाप्त_fasync(&pipe->fasync_ग_लिखोrs, SIGIO, POLL_OUT);
	पूर्ण
	__pipe_unlock(pipe);

	put_pipe_info(inode, pipe);
	वापस 0;
पूर्ण

अटल पूर्णांक
pipe_fasync(पूर्णांक fd, काष्ठा file *filp, पूर्णांक on)
अणु
	काष्ठा pipe_inode_info *pipe = filp->निजी_data;
	पूर्णांक retval = 0;

	__pipe_lock(pipe);
	अगर (filp->f_mode & FMODE_READ)
		retval = fasync_helper(fd, filp, on, &pipe->fasync_पढ़ोers);
	अगर ((filp->f_mode & FMODE_WRITE) && retval >= 0) अणु
		retval = fasync_helper(fd, filp, on, &pipe->fasync_ग_लिखोrs);
		अगर (retval < 0 && (filp->f_mode & FMODE_READ))
			/* this can happen only अगर on == T */
			fasync_helper(-1, filp, 0, &pipe->fasync_पढ़ोers);
	पूर्ण
	__pipe_unlock(pipe);
	वापस retval;
पूर्ण

अचिन्हित दीर्घ account_pipe_buffers(काष्ठा user_काष्ठा *user,
				   अचिन्हित दीर्घ old, अचिन्हित दीर्घ new)
अणु
	वापस atomic_दीर्घ_add_वापस(new - old, &user->pipe_bufs);
पूर्ण

bool too_many_pipe_buffers_soft(अचिन्हित दीर्घ user_bufs)
अणु
	अचिन्हित दीर्घ soft_limit = READ_ONCE(pipe_user_pages_soft);

	वापस soft_limit && user_bufs > soft_limit;
पूर्ण

bool too_many_pipe_buffers_hard(अचिन्हित दीर्घ user_bufs)
अणु
	अचिन्हित दीर्घ hard_limit = READ_ONCE(pipe_user_pages_hard);

	वापस hard_limit && user_bufs > hard_limit;
पूर्ण

bool pipe_is_unprivileged_user(व्योम)
अणु
	वापस !capable(CAP_SYS_RESOURCE) && !capable(CAP_SYS_ADMIN);
पूर्ण

काष्ठा pipe_inode_info *alloc_pipe_info(व्योम)
अणु
	काष्ठा pipe_inode_info *pipe;
	अचिन्हित दीर्घ pipe_bufs = PIPE_DEF_BUFFERS;
	काष्ठा user_काष्ठा *user = get_current_user();
	अचिन्हित दीर्घ user_bufs;
	अचिन्हित पूर्णांक max_size = READ_ONCE(pipe_max_size);

	pipe = kzalloc(माप(काष्ठा pipe_inode_info), GFP_KERNEL_ACCOUNT);
	अगर (pipe == शून्य)
		जाओ out_मुक्त_uid;

	अगर (pipe_bufs * PAGE_SIZE > max_size && !capable(CAP_SYS_RESOURCE))
		pipe_bufs = max_size >> PAGE_SHIFT;

	user_bufs = account_pipe_buffers(user, 0, pipe_bufs);

	अगर (too_many_pipe_buffers_soft(user_bufs) && pipe_is_unprivileged_user()) अणु
		user_bufs = account_pipe_buffers(user, pipe_bufs, 1);
		pipe_bufs = 1;
	पूर्ण

	अगर (too_many_pipe_buffers_hard(user_bufs) && pipe_is_unprivileged_user())
		जाओ out_revert_acct;

	pipe->bufs = kसुस्मृति(pipe_bufs, माप(काष्ठा pipe_buffer),
			     GFP_KERNEL_ACCOUNT);

	अगर (pipe->bufs) अणु
		init_रुकोqueue_head(&pipe->rd_रुको);
		init_रुकोqueue_head(&pipe->wr_रुको);
		pipe->r_counter = pipe->w_counter = 1;
		pipe->max_usage = pipe_bufs;
		pipe->ring_size = pipe_bufs;
		pipe->nr_accounted = pipe_bufs;
		pipe->user = user;
		mutex_init(&pipe->mutex);
		वापस pipe;
	पूर्ण

out_revert_acct:
	(व्योम) account_pipe_buffers(user, pipe_bufs, 0);
	kमुक्त(pipe);
out_मुक्त_uid:
	मुक्त_uid(user);
	वापस शून्य;
पूर्ण

व्योम मुक्त_pipe_info(काष्ठा pipe_inode_info *pipe)
अणु
	पूर्णांक i;

#अगर_घोषित CONFIG_WATCH_QUEUE
	अगर (pipe->watch_queue) अणु
		watch_queue_clear(pipe->watch_queue);
		put_watch_queue(pipe->watch_queue);
	पूर्ण
#पूर्ण_अगर

	(व्योम) account_pipe_buffers(pipe->user, pipe->nr_accounted, 0);
	मुक्त_uid(pipe->user);
	क्रम (i = 0; i < pipe->ring_size; i++) अणु
		काष्ठा pipe_buffer *buf = pipe->bufs + i;
		अगर (buf->ops)
			pipe_buf_release(pipe, buf);
	पूर्ण
	अगर (pipe->पंचांगp_page)
		__मुक्त_page(pipe->पंचांगp_page);
	kमुक्त(pipe->bufs);
	kमुक्त(pipe);
पूर्ण

अटल काष्ठा vfsmount *pipe_mnt __पढ़ो_mostly;

/*
 * pipefs_dname() is called from d_path().
 */
अटल अक्षर *pipefs_dname(काष्ठा dentry *dentry, अक्षर *buffer, पूर्णांक buflen)
अणु
	वापस dynamic_dname(dentry, buffer, buflen, "pipe:[%lu]",
				d_inode(dentry)->i_ino);
पूर्ण

अटल स्थिर काष्ठा dentry_operations pipefs_dentry_operations = अणु
	.d_dname	= pipefs_dname,
पूर्ण;

अटल काष्ठा inode * get_pipe_inode(व्योम)
अणु
	काष्ठा inode *inode = new_inode_pseuकरो(pipe_mnt->mnt_sb);
	काष्ठा pipe_inode_info *pipe;

	अगर (!inode)
		जाओ fail_inode;

	inode->i_ino = get_next_ino();

	pipe = alloc_pipe_info();
	अगर (!pipe)
		जाओ fail_iput;

	inode->i_pipe = pipe;
	pipe->files = 2;
	pipe->पढ़ोers = pipe->ग_लिखोrs = 1;
	inode->i_fop = &pipefअगरo_fops;

	/*
	 * Mark the inode dirty from the very beginning,
	 * that way it will never be moved to the dirty
	 * list because "mark_inode_dirty()" will think
	 * that it alपढ़ोy _is_ on the dirty list.
	 */
	inode->i_state = I_सूचीTY;
	inode->i_mode = S_IFIFO | S_IRUSR | S_IWUSR;
	inode->i_uid = current_fsuid();
	inode->i_gid = current_fsgid();
	inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);

	वापस inode;

fail_iput:
	iput(inode);

fail_inode:
	वापस शून्य;
पूर्ण

पूर्णांक create_pipe_files(काष्ठा file **res, पूर्णांक flags)
अणु
	काष्ठा inode *inode = get_pipe_inode();
	काष्ठा file *f;
	पूर्णांक error;

	अगर (!inode)
		वापस -ENखाता;

	अगर (flags & O_NOTIFICATION_PIPE) अणु
		error = watch_queue_init(inode->i_pipe);
		अगर (error) अणु
			मुक्त_pipe_info(inode->i_pipe);
			iput(inode);
			वापस error;
		पूर्ण
	पूर्ण

	f = alloc_file_pseuकरो(inode, pipe_mnt, "",
				O_WRONLY | (flags & (O_NONBLOCK | O_सूचीECT)),
				&pipefअगरo_fops);
	अगर (IS_ERR(f)) अणु
		मुक्त_pipe_info(inode->i_pipe);
		iput(inode);
		वापस PTR_ERR(f);
	पूर्ण

	f->निजी_data = inode->i_pipe;

	res[0] = alloc_file_clone(f, O_RDONLY | (flags & O_NONBLOCK),
				  &pipefअगरo_fops);
	अगर (IS_ERR(res[0])) अणु
		put_pipe_info(inode, inode->i_pipe);
		fput(f);
		वापस PTR_ERR(res[0]);
	पूर्ण
	res[0]->निजी_data = inode->i_pipe;
	res[1] = f;
	stream_खोलो(inode, res[0]);
	stream_खोलो(inode, res[1]);
	वापस 0;
पूर्ण

अटल पूर्णांक __करो_pipe_flags(पूर्णांक *fd, काष्ठा file **files, पूर्णांक flags)
अणु
	पूर्णांक error;
	पूर्णांक fdw, fdr;

	अगर (flags & ~(O_CLOEXEC | O_NONBLOCK | O_सूचीECT | O_NOTIFICATION_PIPE))
		वापस -EINVAL;

	error = create_pipe_files(files, flags);
	अगर (error)
		वापस error;

	error = get_unused_fd_flags(flags);
	अगर (error < 0)
		जाओ err_पढ़ो_pipe;
	fdr = error;

	error = get_unused_fd_flags(flags);
	अगर (error < 0)
		जाओ err_fdr;
	fdw = error;

	audit_fd_pair(fdr, fdw);
	fd[0] = fdr;
	fd[1] = fdw;
	वापस 0;

 err_fdr:
	put_unused_fd(fdr);
 err_पढ़ो_pipe:
	fput(files[0]);
	fput(files[1]);
	वापस error;
पूर्ण

पूर्णांक करो_pipe_flags(पूर्णांक *fd, पूर्णांक flags)
अणु
	काष्ठा file *files[2];
	पूर्णांक error = __करो_pipe_flags(fd, files, flags);
	अगर (!error) अणु
		fd_install(fd[0], files[0]);
		fd_install(fd[1], files[1]);
	पूर्ण
	वापस error;
पूर्ण

/*
 * sys_pipe() is the normal C calling standard क्रम creating
 * a pipe. It's not the way Unix traditionally करोes this, though.
 */
अटल पूर्णांक करो_pipe2(पूर्णांक __user *fildes, पूर्णांक flags)
अणु
	काष्ठा file *files[2];
	पूर्णांक fd[2];
	पूर्णांक error;

	error = __करो_pipe_flags(fd, files, flags);
	अगर (!error) अणु
		अगर (unlikely(copy_to_user(fildes, fd, माप(fd)))) अणु
			fput(files[0]);
			fput(files[1]);
			put_unused_fd(fd[0]);
			put_unused_fd(fd[1]);
			error = -EFAULT;
		पूर्ण अन्यथा अणु
			fd_install(fd[0], files[0]);
			fd_install(fd[1], files[1]);
		पूर्ण
	पूर्ण
	वापस error;
पूर्ण

SYSCALL_DEFINE2(pipe2, पूर्णांक __user *, fildes, पूर्णांक, flags)
अणु
	वापस करो_pipe2(fildes, flags);
पूर्ण

SYSCALL_DEFINE1(pipe, पूर्णांक __user *, fildes)
अणु
	वापस करो_pipe2(fildes, 0);
पूर्ण

/*
 * This is the stupid "wait for pipe to be readable or writable"
 * model.
 *
 * See pipe_पढ़ो/ग_लिखो() क्रम the proper kind of exclusive रुको,
 * but that requires that we wake up any other पढ़ोers/ग_लिखोrs
 * अगर we then करो not end up पढ़ोing everything (ie the whole
 * "wake_next_reader/writer" logic in pipe_पढ़ो/ग_लिखो()).
 */
व्योम pipe_रुको_पढ़ोable(काष्ठा pipe_inode_info *pipe)
अणु
	pipe_unlock(pipe);
	रुको_event_पूर्णांकerruptible(pipe->rd_रुको, pipe_पढ़ोable(pipe));
	pipe_lock(pipe);
पूर्ण

व्योम pipe_रुको_writable(काष्ठा pipe_inode_info *pipe)
अणु
	pipe_unlock(pipe);
	रुको_event_पूर्णांकerruptible(pipe->wr_रुको, pipe_writable(pipe));
	pipe_lock(pipe);
पूर्ण

/*
 * This depends on both the रुको (here) and the wakeup (wake_up_partner)
 * holding the pipe lock, so "*cnt" is stable and we know a wakeup cannot
 * race with the count check and रुकोqueue prep.
 *
 * Normally in order to aव्योम races, you'd करो the prepare_to_रुको() first,
 * then check the condition you're रुकोing क्रम, and only then sleep. But
 * because of the pipe lock, we can check the condition beक्रमe being on
 * the रुको queue.
 *
 * We use the 'rd_wait' रुकोqueue क्रम pipe partner रुकोing.
 */
अटल पूर्णांक रुको_क्रम_partner(काष्ठा pipe_inode_info *pipe, अचिन्हित पूर्णांक *cnt)
अणु
	DEFINE_WAIT(rdरुको);
	पूर्णांक cur = *cnt;

	जबतक (cur == *cnt) अणु
		prepare_to_रुको(&pipe->rd_रुको, &rdरुको, TASK_INTERRUPTIBLE);
		pipe_unlock(pipe);
		schedule();
		finish_रुको(&pipe->rd_रुको, &rdरुको);
		pipe_lock(pipe);
		अगर (संकेत_pending(current))
			अवरोध;
	पूर्ण
	वापस cur == *cnt ? -ERESTARTSYS : 0;
पूर्ण

अटल व्योम wake_up_partner(काष्ठा pipe_inode_info *pipe)
अणु
	wake_up_पूर्णांकerruptible_all(&pipe->rd_रुको);
पूर्ण

अटल पूर्णांक fअगरo_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा pipe_inode_info *pipe;
	bool is_pipe = inode->i_sb->s_magic == PIPEFS_MAGIC;
	पूर्णांक ret;

	filp->f_version = 0;

	spin_lock(&inode->i_lock);
	अगर (inode->i_pipe) अणु
		pipe = inode->i_pipe;
		pipe->files++;
		spin_unlock(&inode->i_lock);
	पूर्ण अन्यथा अणु
		spin_unlock(&inode->i_lock);
		pipe = alloc_pipe_info();
		अगर (!pipe)
			वापस -ENOMEM;
		pipe->files = 1;
		spin_lock(&inode->i_lock);
		अगर (unlikely(inode->i_pipe)) अणु
			inode->i_pipe->files++;
			spin_unlock(&inode->i_lock);
			मुक्त_pipe_info(pipe);
			pipe = inode->i_pipe;
		पूर्ण अन्यथा अणु
			inode->i_pipe = pipe;
			spin_unlock(&inode->i_lock);
		पूर्ण
	पूर्ण
	filp->निजी_data = pipe;
	/* OK, we have a pipe and it's pinned करोwn */

	__pipe_lock(pipe);

	/* We can only करो regular पढ़ो/ग_लिखो on fअगरos */
	stream_खोलो(inode, filp);

	चयन (filp->f_mode & (FMODE_READ | FMODE_WRITE)) अणु
	हाल FMODE_READ:
	/*
	 *  O_RDONLY
	 *  POSIX.1 says that O_NONBLOCK means वापस with the FIFO
	 *  खोलोed, even when there is no process writing the FIFO.
	 */
		pipe->r_counter++;
		अगर (pipe->पढ़ोers++ == 0)
			wake_up_partner(pipe);

		अगर (!is_pipe && !pipe->ग_लिखोrs) अणु
			अगर ((filp->f_flags & O_NONBLOCK)) अणु
				/* suppress EPOLLHUP until we have
				 * seen a ग_लिखोr */
				filp->f_version = pipe->w_counter;
			पूर्ण अन्यथा अणु
				अगर (रुको_क्रम_partner(pipe, &pipe->w_counter))
					जाओ err_rd;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल FMODE_WRITE:
	/*
	 *  O_WRONLY
	 *  POSIX.1 says that O_NONBLOCK means वापस -1 with
	 *  त्रुटि_सं=ENXIO when there is no process पढ़ोing the FIFO.
	 */
		ret = -ENXIO;
		अगर (!is_pipe && (filp->f_flags & O_NONBLOCK) && !pipe->पढ़ोers)
			जाओ err;

		pipe->w_counter++;
		अगर (!pipe->ग_लिखोrs++)
			wake_up_partner(pipe);

		अगर (!is_pipe && !pipe->पढ़ोers) अणु
			अगर (रुको_क्रम_partner(pipe, &pipe->r_counter))
				जाओ err_wr;
		पूर्ण
		अवरोध;

	हाल FMODE_READ | FMODE_WRITE:
	/*
	 *  O_RDWR
	 *  POSIX.1 leaves this हाल "undefined" when O_NONBLOCK is set.
	 *  This implementation will NEVER block on a O_RDWR खोलो, since
	 *  the process can at least talk to itself.
	 */

		pipe->पढ़ोers++;
		pipe->ग_लिखोrs++;
		pipe->r_counter++;
		pipe->w_counter++;
		अगर (pipe->पढ़ोers == 1 || pipe->ग_लिखोrs == 1)
			wake_up_partner(pipe);
		अवरोध;

	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* Ok! */
	__pipe_unlock(pipe);
	वापस 0;

err_rd:
	अगर (!--pipe->पढ़ोers)
		wake_up_पूर्णांकerruptible(&pipe->wr_रुको);
	ret = -ERESTARTSYS;
	जाओ err;

err_wr:
	अगर (!--pipe->ग_लिखोrs)
		wake_up_पूर्णांकerruptible_all(&pipe->rd_रुको);
	ret = -ERESTARTSYS;
	जाओ err;

err:
	__pipe_unlock(pipe);

	put_pipe_info(inode, pipe);
	वापस ret;
पूर्ण

स्थिर काष्ठा file_operations pipefअगरo_fops = अणु
	.खोलो		= fअगरo_खोलो,
	.llseek		= no_llseek,
	.पढ़ो_iter	= pipe_पढ़ो,
	.ग_लिखो_iter	= pipe_ग_लिखो,
	.poll		= pipe_poll,
	.unlocked_ioctl	= pipe_ioctl,
	.release	= pipe_release,
	.fasync		= pipe_fasync,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
पूर्ण;

/*
 * Currently we rely on the pipe array holding a घातer-of-2 number
 * of pages. Returns 0 on error.
 */
अचिन्हित पूर्णांक round_pipe_size(अचिन्हित दीर्घ size)
अणु
	अगर (size > (1U << 31))
		वापस 0;

	/* Minimum pipe size, as required by POSIX */
	अगर (size < PAGE_SIZE)
		वापस PAGE_SIZE;

	वापस roundup_घात_of_two(size);
पूर्ण

/*
 * Resize the pipe ring to a number of slots.
 */
पूर्णांक pipe_resize_ring(काष्ठा pipe_inode_info *pipe, अचिन्हित पूर्णांक nr_slots)
अणु
	काष्ठा pipe_buffer *bufs;
	अचिन्हित पूर्णांक head, tail, mask, n;

	/*
	 * We can shrink the pipe, अगर arg is greater than the ring occupancy.
	 * Since we करोn't expect a lot of shrink+grow operations, just मुक्त and
	 * allocate again like we would करो क्रम growing.  If the pipe currently
	 * contains more buffers than arg, then वापस busy.
	 */
	mask = pipe->ring_size - 1;
	head = pipe->head;
	tail = pipe->tail;
	n = pipe_occupancy(pipe->head, pipe->tail);
	अगर (nr_slots < n)
		वापस -EBUSY;

	bufs = kसुस्मृति(nr_slots, माप(*bufs),
		       GFP_KERNEL_ACCOUNT | __GFP_NOWARN);
	अगर (unlikely(!bufs))
		वापस -ENOMEM;

	/*
	 * The pipe array wraps around, so just start the new one at zero
	 * and adjust the indices.
	 */
	अगर (n > 0) अणु
		अचिन्हित पूर्णांक h = head & mask;
		अचिन्हित पूर्णांक t = tail & mask;
		अगर (h > t) अणु
			स_नकल(bufs, pipe->bufs + t,
			       n * माप(काष्ठा pipe_buffer));
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक tsize = pipe->ring_size - t;
			अगर (h > 0)
				स_नकल(bufs + tsize, pipe->bufs,
				       h * माप(काष्ठा pipe_buffer));
			स_नकल(bufs, pipe->bufs + t,
			       tsize * माप(काष्ठा pipe_buffer));
		पूर्ण
	पूर्ण

	head = n;
	tail = 0;

	kमुक्त(pipe->bufs);
	pipe->bufs = bufs;
	pipe->ring_size = nr_slots;
	अगर (pipe->max_usage > nr_slots)
		pipe->max_usage = nr_slots;
	pipe->tail = tail;
	pipe->head = head;

	/* This might have made more room क्रम ग_लिखोrs */
	wake_up_पूर्णांकerruptible(&pipe->wr_रुको);
	वापस 0;
पूर्ण

/*
 * Allocate a new array of pipe buffers and copy the info over. Returns the
 * pipe size अगर successful, or वापस -ERROR on error.
 */
अटल दीर्घ pipe_set_size(काष्ठा pipe_inode_info *pipe, अचिन्हित दीर्घ arg)
अणु
	अचिन्हित दीर्घ user_bufs;
	अचिन्हित पूर्णांक nr_slots, size;
	दीर्घ ret = 0;

#अगर_घोषित CONFIG_WATCH_QUEUE
	अगर (pipe->watch_queue)
		वापस -EBUSY;
#पूर्ण_अगर

	size = round_pipe_size(arg);
	nr_slots = size >> PAGE_SHIFT;

	अगर (!nr_slots)
		वापस -EINVAL;

	/*
	 * If trying to increase the pipe capacity, check that an
	 * unprivileged user is not trying to exceed various limits
	 * (soft limit check here, hard limit check just below).
	 * Decreasing the pipe capacity is always permitted, even
	 * अगर the user is currently over a limit.
	 */
	अगर (nr_slots > pipe->max_usage &&
			size > pipe_max_size && !capable(CAP_SYS_RESOURCE))
		वापस -EPERM;

	user_bufs = account_pipe_buffers(pipe->user, pipe->nr_accounted, nr_slots);

	अगर (nr_slots > pipe->max_usage &&
			(too_many_pipe_buffers_hard(user_bufs) ||
			 too_many_pipe_buffers_soft(user_bufs)) &&
			pipe_is_unprivileged_user()) अणु
		ret = -EPERM;
		जाओ out_revert_acct;
	पूर्ण

	ret = pipe_resize_ring(pipe, nr_slots);
	अगर (ret < 0)
		जाओ out_revert_acct;

	pipe->max_usage = nr_slots;
	pipe->nr_accounted = nr_slots;
	वापस pipe->max_usage * PAGE_SIZE;

out_revert_acct:
	(व्योम) account_pipe_buffers(pipe->user, nr_slots, pipe->nr_accounted);
	वापस ret;
पूर्ण

/*
 * Note that i_pipe and i_cdev share the same location, so checking ->i_pipe is
 * not enough to verअगरy that this is a pipe.
 */
काष्ठा pipe_inode_info *get_pipe_info(काष्ठा file *file, bool क्रम_splice)
अणु
	काष्ठा pipe_inode_info *pipe = file->निजी_data;

	अगर (file->f_op != &pipefअगरo_fops || !pipe)
		वापस शून्य;
#अगर_घोषित CONFIG_WATCH_QUEUE
	अगर (क्रम_splice && pipe->watch_queue)
		वापस शून्य;
#पूर्ण_अगर
	वापस pipe;
पूर्ण

दीर्घ pipe_fcntl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा pipe_inode_info *pipe;
	दीर्घ ret;

	pipe = get_pipe_info(file, false);
	अगर (!pipe)
		वापस -EBADF;

	__pipe_lock(pipe);

	चयन (cmd) अणु
	हाल F_SETPIPE_SZ:
		ret = pipe_set_size(pipe, arg);
		अवरोध;
	हाल F_GETPIPE_SZ:
		ret = pipe->max_usage * PAGE_SIZE;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	__pipe_unlock(pipe);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा super_operations pipefs_ops = अणु
	.destroy_inode = मुक्त_inode_nonrcu,
	.statfs = simple_statfs,
पूर्ण;

/*
 * pipefs should _never_ be mounted by userland - too much of security hassle,
 * no real gain from having the whole whorehouse mounted. So we करोn't need
 * any operations on the root directory. However, we need a non-trivial
 * d_name - pipe: will go nicely and समाप्त the special-casing in procfs.
 */

अटल पूर्णांक pipefs_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा pseuकरो_fs_context *ctx = init_pseuकरो(fc, PIPEFS_MAGIC);
	अगर (!ctx)
		वापस -ENOMEM;
	ctx->ops = &pipefs_ops;
	ctx->करोps = &pipefs_dentry_operations;
	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type pipe_fs_type = अणु
	.name		= "pipefs",
	.init_fs_context = pipefs_init_fs_context,
	.समाप्त_sb	= समाप्त_anon_super,
पूर्ण;

अटल पूर्णांक __init init_pipe_fs(व्योम)
अणु
	पूर्णांक err = रेजिस्टर_fileप्रणाली(&pipe_fs_type);

	अगर (!err) अणु
		pipe_mnt = kern_mount(&pipe_fs_type);
		अगर (IS_ERR(pipe_mnt)) अणु
			err = PTR_ERR(pipe_mnt);
			unरेजिस्टर_fileप्रणाली(&pipe_fs_type);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

fs_initcall(init_pipe_fs);
