<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  fs/समयrfd.c
 *
 *  Copyright (C) 2007  Davide Libenzi <davidel@xmailserver.org>
 *
 *
 *  Thanks to Thomas Gleixner क्रम code reviews and useful comments.
 *
 */

#समावेश <linux/alarmसमयr.h>
#समावेश <linux/file.h>
#समावेश <linux/poll.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समय.स>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/समयrfd.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/compat.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/समय_namespace.h>

काष्ठा समयrfd_ctx अणु
	जोड़ अणु
		काष्ठा hrसमयr पंचांगr;
		काष्ठा alarm alarm;
	पूर्ण t;
	kसमय_प्रकार tपूर्णांकv;
	kसमय_प्रकार moffs;
	रुको_queue_head_t wqh;
	u64 ticks;
	पूर्णांक घड़ीid;
	लघु अचिन्हित expired;
	लघु अचिन्हित समय_रखो_flags;	/* to show in fdinfo */
	काष्ठा rcu_head rcu;
	काष्ठा list_head clist;
	spinlock_t cancel_lock;
	bool might_cancel;
पूर्ण;

अटल LIST_HEAD(cancel_list);
अटल DEFINE_SPINLOCK(cancel_lock);

अटल अंतरभूत bool isalarm(काष्ठा समयrfd_ctx *ctx)
अणु
	वापस ctx->घड़ीid == CLOCK_REALTIME_ALARM ||
		ctx->घड़ीid == CLOCK_BOOTTIME_ALARM;
पूर्ण

/*
 * This माला_लो called when the समयr event triggers. We set the "expired"
 * flag, but we करो not re-arm the समयr (in हाल it's necessary,
 * tपूर्णांकv != 0) until the समयr is accessed.
 */
अटल व्योम समयrfd_triggered(काष्ठा समयrfd_ctx *ctx)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->wqh.lock, flags);
	ctx->expired = 1;
	ctx->ticks++;
	wake_up_locked_poll(&ctx->wqh, EPOLLIN);
	spin_unlock_irqrestore(&ctx->wqh.lock, flags);
पूर्ण

अटल क्रमागत hrसमयr_restart समयrfd_पंचांगrproc(काष्ठा hrसमयr *hपंचांगr)
अणु
	काष्ठा समयrfd_ctx *ctx = container_of(hपंचांगr, काष्ठा समयrfd_ctx,
					       t.पंचांगr);
	समयrfd_triggered(ctx);
	वापस HRTIMER_NORESTART;
पूर्ण

अटल क्रमागत alarmसमयr_restart समयrfd_alarmproc(काष्ठा alarm *alarm,
	kसमय_प्रकार now)
अणु
	काष्ठा समयrfd_ctx *ctx = container_of(alarm, काष्ठा समयrfd_ctx,
					       t.alarm);
	समयrfd_triggered(ctx);
	वापस ALARMTIMER_NORESTART;
पूर्ण

/*
 * Called when the घड़ी was set to cancel the समयrs in the cancel
 * list. This will wake up processes रुकोing on these समयrs. The
 * wake-up requires ctx->ticks to be non zero, thereक्रमe we increment
 * it beक्रमe calling wake_up_locked().
 */
व्योम समयrfd_घड़ी_was_set(व्योम)
अणु
	kसमय_प्रकार moffs = kसमय_mono_to_real(0);
	काष्ठा समयrfd_ctx *ctx;
	अचिन्हित दीर्घ flags;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ctx, &cancel_list, clist) अणु
		अगर (!ctx->might_cancel)
			जारी;
		spin_lock_irqsave(&ctx->wqh.lock, flags);
		अगर (ctx->moffs != moffs) अणु
			ctx->moffs = KTIME_MAX;
			ctx->ticks++;
			wake_up_locked_poll(&ctx->wqh, EPOLLIN);
		पूर्ण
		spin_unlock_irqrestore(&ctx->wqh.lock, flags);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम __समयrfd_हटाओ_cancel(काष्ठा समयrfd_ctx *ctx)
अणु
	अगर (ctx->might_cancel) अणु
		ctx->might_cancel = false;
		spin_lock(&cancel_lock);
		list_del_rcu(&ctx->clist);
		spin_unlock(&cancel_lock);
	पूर्ण
पूर्ण

अटल व्योम समयrfd_हटाओ_cancel(काष्ठा समयrfd_ctx *ctx)
अणु
	spin_lock(&ctx->cancel_lock);
	__समयrfd_हटाओ_cancel(ctx);
	spin_unlock(&ctx->cancel_lock);
पूर्ण

अटल bool समयrfd_canceled(काष्ठा समयrfd_ctx *ctx)
अणु
	अगर (!ctx->might_cancel || ctx->moffs != KTIME_MAX)
		वापस false;
	ctx->moffs = kसमय_mono_to_real(0);
	वापस true;
पूर्ण

अटल व्योम समयrfd_setup_cancel(काष्ठा समयrfd_ctx *ctx, पूर्णांक flags)
अणु
	spin_lock(&ctx->cancel_lock);
	अगर ((ctx->घड़ीid == CLOCK_REALTIME ||
	     ctx->घड़ीid == CLOCK_REALTIME_ALARM) &&
	    (flags & TFD_TIMER_ABSTIME) && (flags & TFD_TIMER_CANCEL_ON_SET)) अणु
		अगर (!ctx->might_cancel) अणु
			ctx->might_cancel = true;
			spin_lock(&cancel_lock);
			list_add_rcu(&ctx->clist, &cancel_list);
			spin_unlock(&cancel_lock);
		पूर्ण
	पूर्ण अन्यथा अणु
		__समयrfd_हटाओ_cancel(ctx);
	पूर्ण
	spin_unlock(&ctx->cancel_lock);
पूर्ण

अटल kसमय_प्रकार समयrfd_get_reमुख्यing(काष्ठा समयrfd_ctx *ctx)
अणु
	kसमय_प्रकार reमुख्यing;

	अगर (isalarm(ctx))
		reमुख्यing = alarm_expires_reमुख्यing(&ctx->t.alarm);
	अन्यथा
		reमुख्यing = hrसमयr_expires_reमुख्यing_adjusted(&ctx->t.पंचांगr);

	वापस reमुख्यing < 0 ? 0: reमुख्यing;
पूर्ण

अटल पूर्णांक समयrfd_setup(काष्ठा समयrfd_ctx *ctx, पूर्णांक flags,
			 स्थिर काष्ठा iसमयrspec64 *kपंचांगr)
अणु
	क्रमागत hrसमयr_mode hपंचांगode;
	kसमय_प्रकार texp;
	पूर्णांक घड़ीid = ctx->घड़ीid;

	hपंचांगode = (flags & TFD_TIMER_ABSTIME) ?
		HRTIMER_MODE_ABS: HRTIMER_MODE_REL;

	texp = बारpec64_to_kसमय(kपंचांगr->it_value);
	ctx->expired = 0;
	ctx->ticks = 0;
	ctx->tपूर्णांकv = बारpec64_to_kसमय(kपंचांगr->it_पूर्णांकerval);

	अगर (isalarm(ctx)) अणु
		alarm_init(&ctx->t.alarm,
			   ctx->घड़ीid == CLOCK_REALTIME_ALARM ?
			   ALARM_REALTIME : ALARM_BOOTTIME,
			   समयrfd_alarmproc);
	पूर्ण अन्यथा अणु
		hrसमयr_init(&ctx->t.पंचांगr, घड़ीid, hपंचांगode);
		hrसमयr_set_expires(&ctx->t.पंचांगr, texp);
		ctx->t.पंचांगr.function = समयrfd_पंचांगrproc;
	पूर्ण

	अगर (texp != 0) अणु
		अगर (flags & TFD_TIMER_ABSTIME)
			texp = समयns_kसमय_प्रकारo_host(घड़ीid, texp);
		अगर (isalarm(ctx)) अणु
			अगर (flags & TFD_TIMER_ABSTIME)
				alarm_start(&ctx->t.alarm, texp);
			अन्यथा
				alarm_start_relative(&ctx->t.alarm, texp);
		पूर्ण अन्यथा अणु
			hrसमयr_start(&ctx->t.पंचांगr, texp, hपंचांगode);
		पूर्ण

		अगर (समयrfd_canceled(ctx))
			वापस -ECANCELED;
	पूर्ण

	ctx->समय_रखो_flags = flags & TFD_SETTIME_FLAGS;
	वापस 0;
पूर्ण

अटल पूर्णांक समयrfd_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा समयrfd_ctx *ctx = file->निजी_data;

	समयrfd_हटाओ_cancel(ctx);

	अगर (isalarm(ctx))
		alarm_cancel(&ctx->t.alarm);
	अन्यथा
		hrसमयr_cancel(&ctx->t.पंचांगr);
	kमुक्त_rcu(ctx, rcu);
	वापस 0;
पूर्ण

अटल __poll_t समयrfd_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा समयrfd_ctx *ctx = file->निजी_data;
	__poll_t events = 0;
	अचिन्हित दीर्घ flags;

	poll_रुको(file, &ctx->wqh, रुको);

	spin_lock_irqsave(&ctx->wqh.lock, flags);
	अगर (ctx->ticks)
		events |= EPOLLIN;
	spin_unlock_irqrestore(&ctx->wqh.lock, flags);

	वापस events;
पूर्ण

अटल sमाप_प्रकार समयrfd_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			    loff_t *ppos)
अणु
	काष्ठा समयrfd_ctx *ctx = file->निजी_data;
	sमाप_प्रकार res;
	u64 ticks = 0;

	अगर (count < माप(ticks))
		वापस -EINVAL;
	spin_lock_irq(&ctx->wqh.lock);
	अगर (file->f_flags & O_NONBLOCK)
		res = -EAGAIN;
	अन्यथा
		res = रुको_event_पूर्णांकerruptible_locked_irq(ctx->wqh, ctx->ticks);

	/*
	 * If घड़ी has changed, we करो not care about the
	 * ticks and we करो not rearm the समयr. Userspace must
	 * reevaluate anyway.
	 */
	अगर (समयrfd_canceled(ctx)) अणु
		ctx->ticks = 0;
		ctx->expired = 0;
		res = -ECANCELED;
	पूर्ण

	अगर (ctx->ticks) अणु
		ticks = ctx->ticks;

		अगर (ctx->expired && ctx->tपूर्णांकv) अणु
			/*
			 * If tपूर्णांकv != 0, this is a periodic समयr that
			 * needs to be re-armed. We aव्योम करोing it in the समयr
			 * callback to aव्योम DoS attacks specअगरying a very
			 * लघु समयr period.
			 */
			अगर (isalarm(ctx)) अणु
				ticks += alarm_क्रमward_now(
					&ctx->t.alarm, ctx->tपूर्णांकv) - 1;
				alarm_restart(&ctx->t.alarm);
			पूर्ण अन्यथा अणु
				ticks += hrसमयr_क्रमward_now(&ctx->t.पंचांगr,
							     ctx->tपूर्णांकv) - 1;
				hrसमयr_restart(&ctx->t.पंचांगr);
			पूर्ण
		पूर्ण
		ctx->expired = 0;
		ctx->ticks = 0;
	पूर्ण
	spin_unlock_irq(&ctx->wqh.lock);
	अगर (ticks)
		res = put_user(ticks, (u64 __user *) buf) ? -EFAULT: माप(ticks);
	वापस res;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम समयrfd_show(काष्ठा seq_file *m, काष्ठा file *file)
अणु
	काष्ठा समयrfd_ctx *ctx = file->निजी_data;
	काष्ठा बारpec64 value, पूर्णांकerval;

	spin_lock_irq(&ctx->wqh.lock);
	value = kसमय_प्रकारo_बारpec64(समयrfd_get_reमुख्यing(ctx));
	पूर्णांकerval = kसमय_प्रकारo_बारpec64(ctx->tपूर्णांकv);
	spin_unlock_irq(&ctx->wqh.lock);

	seq_म_लिखो(m,
		   "clockid: %d\n"
		   "ticks: %llu\n"
		   "settime flags: 0%o\n"
		   "it_value: (%llu, %llu)\n"
		   "it_interval: (%llu, %llu)\n",
		   ctx->घड़ीid,
		   (अचिन्हित दीर्घ दीर्घ)ctx->ticks,
		   ctx->समय_रखो_flags,
		   (अचिन्हित दीर्घ दीर्घ)value.tv_sec,
		   (अचिन्हित दीर्घ दीर्घ)value.tv_nsec,
		   (अचिन्हित दीर्घ दीर्घ)पूर्णांकerval.tv_sec,
		   (अचिन्हित दीर्घ दीर्घ)पूर्णांकerval.tv_nsec);
पूर्ण
#अन्यथा
#घोषणा समयrfd_show शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_CHECKPOINT_RESTORE
अटल दीर्घ समयrfd_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा समयrfd_ctx *ctx = file->निजी_data;
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल TFD_IOC_SET_TICKS: अणु
		u64 ticks;

		अगर (copy_from_user(&ticks, (u64 __user *)arg, माप(ticks)))
			वापस -EFAULT;
		अगर (!ticks)
			वापस -EINVAL;

		spin_lock_irq(&ctx->wqh.lock);
		अगर (!समयrfd_canceled(ctx)) अणु
			ctx->ticks = ticks;
			wake_up_locked_poll(&ctx->wqh, EPOLLIN);
		पूर्ण अन्यथा
			ret = -ECANCELED;
		spin_unlock_irq(&ctx->wqh.lock);
		अवरोध;
	पूर्ण
	शेष:
		ret = -ENOTTY;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
#अन्यथा
#घोषणा समयrfd_ioctl शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations समयrfd_fops = अणु
	.release	= समयrfd_release,
	.poll		= समयrfd_poll,
	.पढ़ो		= समयrfd_पढ़ो,
	.llseek		= noop_llseek,
	.show_fdinfo	= समयrfd_show,
	.unlocked_ioctl	= समयrfd_ioctl,
पूर्ण;

अटल पूर्णांक समयrfd_fget(पूर्णांक fd, काष्ठा fd *p)
अणु
	काष्ठा fd f = fdget(fd);
	अगर (!f.file)
		वापस -EBADF;
	अगर (f.file->f_op != &समयrfd_fops) अणु
		fdput(f);
		वापस -EINVAL;
	पूर्ण
	*p = f;
	वापस 0;
पूर्ण

SYSCALL_DEFINE2(समयrfd_create, पूर्णांक, घड़ीid, पूर्णांक, flags)
अणु
	पूर्णांक ufd;
	काष्ठा समयrfd_ctx *ctx;

	/* Check the TFD_* स्थिरants क्रम consistency.  */
	BUILD_BUG_ON(TFD_CLOEXEC != O_CLOEXEC);
	BUILD_BUG_ON(TFD_NONBLOCK != O_NONBLOCK);

	अगर ((flags & ~TFD_CREATE_FLAGS) ||
	    (घड़ीid != CLOCK_MONOTONIC &&
	     घड़ीid != CLOCK_REALTIME &&
	     घड़ीid != CLOCK_REALTIME_ALARM &&
	     घड़ीid != CLOCK_BOOTTIME &&
	     घड़ीid != CLOCK_BOOTTIME_ALARM))
		वापस -EINVAL;

	अगर ((घड़ीid == CLOCK_REALTIME_ALARM ||
	     घड़ीid == CLOCK_BOOTTIME_ALARM) &&
	    !capable(CAP_WAKE_ALARM))
		वापस -EPERM;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	init_रुकोqueue_head(&ctx->wqh);
	spin_lock_init(&ctx->cancel_lock);
	ctx->घड़ीid = घड़ीid;

	अगर (isalarm(ctx))
		alarm_init(&ctx->t.alarm,
			   ctx->घड़ीid == CLOCK_REALTIME_ALARM ?
			   ALARM_REALTIME : ALARM_BOOTTIME,
			   समयrfd_alarmproc);
	अन्यथा
		hrसमयr_init(&ctx->t.पंचांगr, घड़ीid, HRTIMER_MODE_ABS);

	ctx->moffs = kसमय_mono_to_real(0);

	ufd = anon_inode_getfd("[timerfd]", &समयrfd_fops, ctx,
			       O_RDWR | (flags & TFD_SHARED_FCNTL_FLAGS));
	अगर (ufd < 0)
		kमुक्त(ctx);

	वापस ufd;
पूर्ण

अटल पूर्णांक करो_समयrfd_समय_रखो(पूर्णांक ufd, पूर्णांक flags, 
		स्थिर काष्ठा iसमयrspec64 *new,
		काष्ठा iसमयrspec64 *old)
अणु
	काष्ठा fd f;
	काष्ठा समयrfd_ctx *ctx;
	पूर्णांक ret;

	अगर ((flags & ~TFD_SETTIME_FLAGS) ||
		 !iसमयrspec64_valid(new))
		वापस -EINVAL;

	ret = समयrfd_fget(ufd, &f);
	अगर (ret)
		वापस ret;
	ctx = f.file->निजी_data;

	अगर (isalarm(ctx) && !capable(CAP_WAKE_ALARM)) अणु
		fdput(f);
		वापस -EPERM;
	पूर्ण

	समयrfd_setup_cancel(ctx, flags);

	/*
	 * We need to stop the existing समयr beक्रमe reprogramming
	 * it to the new values.
	 */
	क्रम (;;) अणु
		spin_lock_irq(&ctx->wqh.lock);

		अगर (isalarm(ctx)) अणु
			अगर (alarm_try_to_cancel(&ctx->t.alarm) >= 0)
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (hrसमयr_try_to_cancel(&ctx->t.पंचांगr) >= 0)
				अवरोध;
		पूर्ण
		spin_unlock_irq(&ctx->wqh.lock);

		अगर (isalarm(ctx))
			hrसमयr_cancel_रुको_running(&ctx->t.alarm.समयr);
		अन्यथा
			hrसमयr_cancel_रुको_running(&ctx->t.पंचांगr);
	पूर्ण

	/*
	 * If the समयr is expired and it's periodic, we need to advance it
	 * because the caller may want to know the previous expiration समय.
	 * We करो not update "ticks" and "expired" since the समयr will be
	 * re-programmed again in the following समयrfd_setup() call.
	 */
	अगर (ctx->expired && ctx->tपूर्णांकv) अणु
		अगर (isalarm(ctx))
			alarm_क्रमward_now(&ctx->t.alarm, ctx->tपूर्णांकv);
		अन्यथा
			hrसमयr_क्रमward_now(&ctx->t.पंचांगr, ctx->tपूर्णांकv);
	पूर्ण

	old->it_value = kसमय_प्रकारo_बारpec64(समयrfd_get_reमुख्यing(ctx));
	old->it_पूर्णांकerval = kसमय_प्रकारo_बारpec64(ctx->tपूर्णांकv);

	/*
	 * Re-program the समयr to the new value ...
	 */
	ret = समयrfd_setup(ctx, flags, new);

	spin_unlock_irq(&ctx->wqh.lock);
	fdput(f);
	वापस ret;
पूर्ण

अटल पूर्णांक करो_समयrfd_समय_लो(पूर्णांक ufd, काष्ठा iसमयrspec64 *t)
अणु
	काष्ठा fd f;
	काष्ठा समयrfd_ctx *ctx;
	पूर्णांक ret = समयrfd_fget(ufd, &f);
	अगर (ret)
		वापस ret;
	ctx = f.file->निजी_data;

	spin_lock_irq(&ctx->wqh.lock);
	अगर (ctx->expired && ctx->tपूर्णांकv) अणु
		ctx->expired = 0;

		अगर (isalarm(ctx)) अणु
			ctx->ticks +=
				alarm_क्रमward_now(
					&ctx->t.alarm, ctx->tपूर्णांकv) - 1;
			alarm_restart(&ctx->t.alarm);
		पूर्ण अन्यथा अणु
			ctx->ticks +=
				hrसमयr_क्रमward_now(&ctx->t.पंचांगr, ctx->tपूर्णांकv)
				- 1;
			hrसमयr_restart(&ctx->t.पंचांगr);
		पूर्ण
	पूर्ण
	t->it_value = kसमय_प्रकारo_बारpec64(समयrfd_get_reमुख्यing(ctx));
	t->it_पूर्णांकerval = kसमय_प्रकारo_बारpec64(ctx->tपूर्णांकv);
	spin_unlock_irq(&ctx->wqh.lock);
	fdput(f);
	वापस 0;
पूर्ण

SYSCALL_DEFINE4(समयrfd_समय_रखो, पूर्णांक, ufd, पूर्णांक, flags,
		स्थिर काष्ठा __kernel_iसमयrspec __user *, uपंचांगr,
		काष्ठा __kernel_iसमयrspec __user *, oपंचांगr)
अणु
	काष्ठा iसमयrspec64 new, old;
	पूर्णांक ret;

	अगर (get_iसमयrspec64(&new, uपंचांगr))
		वापस -EFAULT;
	ret = करो_समयrfd_समय_रखो(ufd, flags, &new, &old);
	अगर (ret)
		वापस ret;
	अगर (oपंचांगr && put_iसमयrspec64(&old, oपंचांगr))
		वापस -EFAULT;

	वापस ret;
पूर्ण

SYSCALL_DEFINE2(समयrfd_समय_लो, पूर्णांक, ufd, काष्ठा __kernel_iसमयrspec __user *, oपंचांगr)
अणु
	काष्ठा iसमयrspec64 koपंचांगr;
	पूर्णांक ret = करो_समयrfd_समय_लो(ufd, &koपंचांगr);
	अगर (ret)
		वापस ret;
	वापस put_iसमयrspec64(&koपंचांगr, oपंचांगr) ? -EFAULT : 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
SYSCALL_DEFINE4(समयrfd_समय_रखो32, पूर्णांक, ufd, पूर्णांक, flags,
		स्थिर काष्ठा old_iसमयrspec32 __user *, uपंचांगr,
		काष्ठा old_iसमयrspec32 __user *, oपंचांगr)
अणु
	काष्ठा iसमयrspec64 new, old;
	पूर्णांक ret;

	अगर (get_old_iसमयrspec32(&new, uपंचांगr))
		वापस -EFAULT;
	ret = करो_समयrfd_समय_रखो(ufd, flags, &new, &old);
	अगर (ret)
		वापस ret;
	अगर (oपंचांगr && put_old_iसमयrspec32(&old, oपंचांगr))
		वापस -EFAULT;
	वापस ret;
पूर्ण

SYSCALL_DEFINE2(समयrfd_समय_लो32, पूर्णांक, ufd,
		काष्ठा old_iसमयrspec32 __user *, oपंचांगr)
अणु
	काष्ठा iसमयrspec64 koपंचांगr;
	पूर्णांक ret = करो_समयrfd_समय_लो(ufd, &koपंचांगr);
	अगर (ret)
		वापस ret;
	वापस put_old_iसमयrspec32(&koपंचांगr, oपंचांगr) ? -EFAULT : 0;
पूर्ण
#पूर्ण_अगर
