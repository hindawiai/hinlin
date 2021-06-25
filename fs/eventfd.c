<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  fs/eventfd.c
 *
 *  Copyright (C) 2007  Davide Libenzi <davidel@xmailserver.org>
 *
 */

#समावेश <linux/file.h>
#समावेश <linux/poll.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/export.h>
#समावेश <linux/kref.h>
#समावेश <linux/eventfd.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/idr.h>
#समावेश <linux/uपन.स>

DEFINE_PER_CPU(पूर्णांक, eventfd_wake_count);

अटल DEFINE_IDA(eventfd_ida);

काष्ठा eventfd_ctx अणु
	काष्ठा kref kref;
	रुको_queue_head_t wqh;
	/*
	 * Every समय that a ग_लिखो(2) is perक्रमmed on an eventfd, the
	 * value of the __u64 being written is added to "count" and a
	 * wakeup is perक्रमmed on "wqh". A पढ़ो(2) will वापस the "count"
	 * value to userspace, and will reset "count" to zero. The kernel
	 * side eventfd_संकेत() also, adds to the "count" counter and
	 * issue a wakeup.
	 */
	__u64 count;
	अचिन्हित पूर्णांक flags;
	पूर्णांक id;
पूर्ण;

/**
 * eventfd_संकेत - Adds @n to the eventfd counter.
 * @ctx: [in] Poपूर्णांकer to the eventfd context.
 * @n: [in] Value of the counter to be added to the eventfd पूर्णांकernal counter.
 *          The value cannot be negative.
 *
 * This function is supposed to be called by the kernel in paths that करो not
 * allow sleeping. In this function we allow the counter to reach the ULदीर्घ_उच्च
 * value, and we संकेत this as overflow condition by वापसing a EPOLLERR
 * to poll(2).
 *
 * Returns the amount by which the counter was incremented.  This will be less
 * than @n अगर the counter has overflowed.
 */
__u64 eventfd_संकेत(काष्ठा eventfd_ctx *ctx, __u64 n)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * Deadlock or stack overflow issues can happen अगर we recurse here
	 * through रुकोqueue wakeup handlers. If the caller users potentially
	 * nested रुकोqueues with custom wakeup handlers, then it should
	 * check eventfd_संकेत_count() beक्रमe calling this function. If
	 * it वापसs true, the eventfd_संकेत() call should be deferred to a
	 * safe context.
	 */
	अगर (WARN_ON_ONCE(this_cpu_पढ़ो(eventfd_wake_count)))
		वापस 0;

	spin_lock_irqsave(&ctx->wqh.lock, flags);
	this_cpu_inc(eventfd_wake_count);
	अगर (ULदीर्घ_उच्च - ctx->count < n)
		n = ULदीर्घ_उच्च - ctx->count;
	ctx->count += n;
	अगर (रुकोqueue_active(&ctx->wqh))
		wake_up_locked_poll(&ctx->wqh, EPOLLIN);
	this_cpu_dec(eventfd_wake_count);
	spin_unlock_irqrestore(&ctx->wqh.lock, flags);

	वापस n;
पूर्ण
EXPORT_SYMBOL_GPL(eventfd_संकेत);

अटल व्योम eventfd_मुक्त_ctx(काष्ठा eventfd_ctx *ctx)
अणु
	अगर (ctx->id >= 0)
		ida_simple_हटाओ(&eventfd_ida, ctx->id);
	kमुक्त(ctx);
पूर्ण

अटल व्योम eventfd_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा eventfd_ctx *ctx = container_of(kref, काष्ठा eventfd_ctx, kref);

	eventfd_मुक्त_ctx(ctx);
पूर्ण

/**
 * eventfd_ctx_put - Releases a reference to the पूर्णांकernal eventfd context.
 * @ctx: [in] Poपूर्णांकer to eventfd context.
 *
 * The eventfd context reference must have been previously acquired either
 * with eventfd_ctx_fdget() or eventfd_ctx_fileget().
 */
व्योम eventfd_ctx_put(काष्ठा eventfd_ctx *ctx)
अणु
	kref_put(&ctx->kref, eventfd_मुक्त);
पूर्ण
EXPORT_SYMBOL_GPL(eventfd_ctx_put);

अटल पूर्णांक eventfd_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा eventfd_ctx *ctx = file->निजी_data;

	wake_up_poll(&ctx->wqh, EPOLLHUP);
	eventfd_ctx_put(ctx);
	वापस 0;
पूर्ण

अटल __poll_t eventfd_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा eventfd_ctx *ctx = file->निजी_data;
	__poll_t events = 0;
	u64 count;

	poll_रुको(file, &ctx->wqh, रुको);

	/*
	 * All ग_लिखोs to ctx->count occur within ctx->wqh.lock.  This पढ़ो
	 * can be करोne outside ctx->wqh.lock because we know that poll_रुको
	 * takes that lock (through add_रुको_queue) अगर our caller will sleep.
	 *
	 * The पढ़ो _can_ thereक्रमe seep पूर्णांकo add_रुको_queue's critical
	 * section, but cannot move above it!  add_रुको_queue's spin_lock acts
	 * as an acquire barrier and ensures that the पढ़ो be ordered properly
	 * against the ग_लिखोs.  The following CAN happen and is safe:
	 *
	 *     poll                               ग_लिखो
	 *     -----------------                  ------------
	 *     lock ctx->wqh.lock (in poll_रुको)
	 *     count = ctx->count
	 *     __add_रुको_queue
	 *     unlock ctx->wqh.lock
	 *                                        lock ctx->qwh.lock
	 *                                        ctx->count += n
	 *                                        अगर (रुकोqueue_active)
	 *                                          wake_up_locked_poll
	 *                                        unlock ctx->qwh.lock
	 *     eventfd_poll वापसs 0
	 *
	 * but the following, which would miss a wakeup, cannot happen:
	 *
	 *     poll                               ग_लिखो
	 *     -----------------                  ------------
	 *     count = ctx->count (INVALID!)
	 *                                        lock ctx->qwh.lock
	 *                                        ctx->count += n
	 *                                        **रुकोqueue_active is false**
	 *                                        **no wake_up_locked_poll!**
	 *                                        unlock ctx->qwh.lock
	 *     lock ctx->wqh.lock (in poll_रुको)
	 *     __add_रुको_queue
	 *     unlock ctx->wqh.lock
	 *     eventfd_poll वापसs 0
	 */
	count = READ_ONCE(ctx->count);

	अगर (count > 0)
		events |= EPOLLIN;
	अगर (count == ULदीर्घ_उच्च)
		events |= EPOLLERR;
	अगर (ULदीर्घ_उच्च - 1 > count)
		events |= EPOLLOUT;

	वापस events;
पूर्ण

व्योम eventfd_ctx_करो_पढ़ो(काष्ठा eventfd_ctx *ctx, __u64 *cnt)
अणु
	lockdep_निश्चित_held(&ctx->wqh.lock);

	*cnt = (ctx->flags & EFD_SEMAPHORE) ? 1 : ctx->count;
	ctx->count -= *cnt;
पूर्ण
EXPORT_SYMBOL_GPL(eventfd_ctx_करो_पढ़ो);

/**
 * eventfd_ctx_हटाओ_रुको_queue - Read the current counter and हटाओs रुको queue.
 * @ctx: [in] Poपूर्णांकer to eventfd context.
 * @रुको: [in] Wait queue to be हटाओd.
 * @cnt: [out] Poपूर्णांकer to the 64-bit counter value.
 *
 * Returns %0 अगर successful, or the following error codes:
 *
 * -EAGAIN      : The operation would have blocked.
 *
 * This is used to atomically हटाओ a रुको queue entry from the eventfd रुको
 * queue head, and पढ़ो/reset the counter value.
 */
पूर्णांक eventfd_ctx_हटाओ_रुको_queue(काष्ठा eventfd_ctx *ctx, रुको_queue_entry_t *रुको,
				  __u64 *cnt)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->wqh.lock, flags);
	eventfd_ctx_करो_पढ़ो(ctx, cnt);
	__हटाओ_रुको_queue(&ctx->wqh, रुको);
	अगर (*cnt != 0 && रुकोqueue_active(&ctx->wqh))
		wake_up_locked_poll(&ctx->wqh, EPOLLOUT);
	spin_unlock_irqrestore(&ctx->wqh.lock, flags);

	वापस *cnt != 0 ? 0 : -EAGAIN;
पूर्ण
EXPORT_SYMBOL_GPL(eventfd_ctx_हटाओ_रुको_queue);

अटल sमाप_प्रकार eventfd_पढ़ो(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा eventfd_ctx *ctx = file->निजी_data;
	__u64 ucnt = 0;
	DECLARE_WAITQUEUE(रुको, current);

	अगर (iov_iter_count(to) < माप(ucnt))
		वापस -EINVAL;
	spin_lock_irq(&ctx->wqh.lock);
	अगर (!ctx->count) अणु
		अगर ((file->f_flags & O_NONBLOCK) ||
		    (iocb->ki_flags & IOCB_NOWAIT)) अणु
			spin_unlock_irq(&ctx->wqh.lock);
			वापस -EAGAIN;
		पूर्ण
		__add_रुको_queue(&ctx->wqh, &रुको);
		क्रम (;;) अणु
			set_current_state(TASK_INTERRUPTIBLE);
			अगर (ctx->count)
				अवरोध;
			अगर (संकेत_pending(current)) अणु
				__हटाओ_रुको_queue(&ctx->wqh, &रुको);
				__set_current_state(TASK_RUNNING);
				spin_unlock_irq(&ctx->wqh.lock);
				वापस -ERESTARTSYS;
			पूर्ण
			spin_unlock_irq(&ctx->wqh.lock);
			schedule();
			spin_lock_irq(&ctx->wqh.lock);
		पूर्ण
		__हटाओ_रुको_queue(&ctx->wqh, &रुको);
		__set_current_state(TASK_RUNNING);
	पूर्ण
	eventfd_ctx_करो_पढ़ो(ctx, &ucnt);
	अगर (रुकोqueue_active(&ctx->wqh))
		wake_up_locked_poll(&ctx->wqh, EPOLLOUT);
	spin_unlock_irq(&ctx->wqh.lock);
	अगर (unlikely(copy_to_iter(&ucnt, माप(ucnt), to) != माप(ucnt)))
		वापस -EFAULT;

	वापस माप(ucnt);
पूर्ण

अटल sमाप_प्रकार eventfd_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count,
			     loff_t *ppos)
अणु
	काष्ठा eventfd_ctx *ctx = file->निजी_data;
	sमाप_प्रकार res;
	__u64 ucnt;
	DECLARE_WAITQUEUE(रुको, current);

	अगर (count < माप(ucnt))
		वापस -EINVAL;
	अगर (copy_from_user(&ucnt, buf, माप(ucnt)))
		वापस -EFAULT;
	अगर (ucnt == ULदीर्घ_उच्च)
		वापस -EINVAL;
	spin_lock_irq(&ctx->wqh.lock);
	res = -EAGAIN;
	अगर (ULदीर्घ_उच्च - ctx->count > ucnt)
		res = माप(ucnt);
	अन्यथा अगर (!(file->f_flags & O_NONBLOCK)) अणु
		__add_रुको_queue(&ctx->wqh, &रुको);
		क्रम (res = 0;;) अणु
			set_current_state(TASK_INTERRUPTIBLE);
			अगर (ULदीर्घ_उच्च - ctx->count > ucnt) अणु
				res = माप(ucnt);
				अवरोध;
			पूर्ण
			अगर (संकेत_pending(current)) अणु
				res = -ERESTARTSYS;
				अवरोध;
			पूर्ण
			spin_unlock_irq(&ctx->wqh.lock);
			schedule();
			spin_lock_irq(&ctx->wqh.lock);
		पूर्ण
		__हटाओ_रुको_queue(&ctx->wqh, &रुको);
		__set_current_state(TASK_RUNNING);
	पूर्ण
	अगर (likely(res > 0)) अणु
		ctx->count += ucnt;
		अगर (रुकोqueue_active(&ctx->wqh))
			wake_up_locked_poll(&ctx->wqh, EPOLLIN);
	पूर्ण
	spin_unlock_irq(&ctx->wqh.lock);

	वापस res;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम eventfd_show_fdinfo(काष्ठा seq_file *m, काष्ठा file *f)
अणु
	काष्ठा eventfd_ctx *ctx = f->निजी_data;

	spin_lock_irq(&ctx->wqh.lock);
	seq_म_लिखो(m, "eventfd-count: %16llx\n",
		   (अचिन्हित दीर्घ दीर्घ)ctx->count);
	spin_unlock_irq(&ctx->wqh.lock);
	seq_म_लिखो(m, "eventfd-id: %d\n", ctx->id);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations eventfd_fops = अणु
#अगर_घोषित CONFIG_PROC_FS
	.show_fdinfo	= eventfd_show_fdinfo,
#पूर्ण_अगर
	.release	= eventfd_release,
	.poll		= eventfd_poll,
	.पढ़ो_iter	= eventfd_पढ़ो,
	.ग_लिखो		= eventfd_ग_लिखो,
	.llseek		= noop_llseek,
पूर्ण;

/**
 * eventfd_fget - Acquire a reference of an eventfd file descriptor.
 * @fd: [in] Eventfd file descriptor.
 *
 * Returns a poपूर्णांकer to the eventfd file काष्ठाure in हाल of success, or the
 * following error poपूर्णांकer:
 *
 * -EBADF    : Invalid @fd file descriptor.
 * -EINVAL   : The @fd file descriptor is not an eventfd file.
 */
काष्ठा file *eventfd_fget(पूर्णांक fd)
अणु
	काष्ठा file *file;

	file = fget(fd);
	अगर (!file)
		वापस ERR_PTR(-EBADF);
	अगर (file->f_op != &eventfd_fops) अणु
		fput(file);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस file;
पूर्ण
EXPORT_SYMBOL_GPL(eventfd_fget);

/**
 * eventfd_ctx_fdget - Acquires a reference to the पूर्णांकernal eventfd context.
 * @fd: [in] Eventfd file descriptor.
 *
 * Returns a poपूर्णांकer to the पूर्णांकernal eventfd context, otherwise the error
 * poपूर्णांकers वापसed by the following functions:
 *
 * eventfd_fget
 */
काष्ठा eventfd_ctx *eventfd_ctx_fdget(पूर्णांक fd)
अणु
	काष्ठा eventfd_ctx *ctx;
	काष्ठा fd f = fdget(fd);
	अगर (!f.file)
		वापस ERR_PTR(-EBADF);
	ctx = eventfd_ctx_fileget(f.file);
	fdput(f);
	वापस ctx;
पूर्ण
EXPORT_SYMBOL_GPL(eventfd_ctx_fdget);

/**
 * eventfd_ctx_fileget - Acquires a reference to the पूर्णांकernal eventfd context.
 * @file: [in] Eventfd file poपूर्णांकer.
 *
 * Returns a poपूर्णांकer to the पूर्णांकernal eventfd context, otherwise the error
 * poपूर्णांकer:
 *
 * -EINVAL   : The @fd file descriptor is not an eventfd file.
 */
काष्ठा eventfd_ctx *eventfd_ctx_fileget(काष्ठा file *file)
अणु
	काष्ठा eventfd_ctx *ctx;

	अगर (file->f_op != &eventfd_fops)
		वापस ERR_PTR(-EINVAL);

	ctx = file->निजी_data;
	kref_get(&ctx->kref);
	वापस ctx;
पूर्ण
EXPORT_SYMBOL_GPL(eventfd_ctx_fileget);

अटल पूर्णांक करो_eventfd(अचिन्हित पूर्णांक count, पूर्णांक flags)
अणु
	काष्ठा eventfd_ctx *ctx;
	काष्ठा file *file;
	पूर्णांक fd;

	/* Check the EFD_* स्थिरants क्रम consistency.  */
	BUILD_BUG_ON(EFD_CLOEXEC != O_CLOEXEC);
	BUILD_BUG_ON(EFD_NONBLOCK != O_NONBLOCK);

	अगर (flags & ~EFD_FLAGS_SET)
		वापस -EINVAL;

	ctx = kदो_स्मृति(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	kref_init(&ctx->kref);
	init_रुकोqueue_head(&ctx->wqh);
	ctx->count = count;
	ctx->flags = flags;
	ctx->id = ida_simple_get(&eventfd_ida, 0, 0, GFP_KERNEL);

	flags &= EFD_SHARED_FCNTL_FLAGS;
	flags |= O_RDWR;
	fd = get_unused_fd_flags(flags);
	अगर (fd < 0)
		जाओ err;

	file = anon_inode_getfile("[eventfd]", &eventfd_fops, ctx, flags);
	अगर (IS_ERR(file)) अणु
		put_unused_fd(fd);
		fd = PTR_ERR(file);
		जाओ err;
	पूर्ण

	file->f_mode |= FMODE_NOWAIT;
	fd_install(fd, file);
	वापस fd;
err:
	eventfd_मुक्त_ctx(ctx);
	वापस fd;
पूर्ण

SYSCALL_DEFINE2(eventfd2, अचिन्हित पूर्णांक, count, पूर्णांक, flags)
अणु
	वापस करो_eventfd(count, flags);
पूर्ण

SYSCALL_DEFINE1(eventfd, अचिन्हित पूर्णांक, count)
अणु
	वापस करो_eventfd(count, 0);
पूर्ण

