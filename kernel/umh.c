<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * umh - the kernel usermode helper
 */
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/unistd.h>
#समावेश <linux/kmod.h>
#समावेश <linux/slab.h>
#समावेश <linux/completion.h>
#समावेश <linux/cred.h>
#समावेश <linux/file.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/security.h>
#समावेश <linux/mount.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/resource.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/suspend.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/async.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/initrd.h>

#समावेश <trace/events/module.h>

#घोषणा CAP_BSET	(व्योम *)1
#घोषणा CAP_PI		(व्योम *)2

अटल kernel_cap_t usermodehelper_bset = CAP_FULL_SET;
अटल kernel_cap_t usermodehelper_inheritable = CAP_FULL_SET;
अटल DEFINE_SPINLOCK(umh_sysctl_lock);
अटल DECLARE_RWSEM(umhelper_sem);

अटल व्योम call_usermodehelper_मुक्तinfo(काष्ठा subprocess_info *info)
अणु
	अगर (info->cleanup)
		(*info->cleanup)(info);
	kमुक्त(info);
पूर्ण

अटल व्योम umh_complete(काष्ठा subprocess_info *sub_info)
अणु
	काष्ठा completion *comp = xchg(&sub_info->complete, शून्य);
	/*
	 * See call_usermodehelper_exec(). If xchg() वापसs शून्य
	 * we own sub_info, the UMH_KILLABLE caller has gone away
	 * or the caller used UMH_NO_WAIT.
	 */
	अगर (comp)
		complete(comp);
	अन्यथा
		call_usermodehelper_मुक्तinfo(sub_info);
पूर्ण

/*
 * This is the task which runs the usermode application
 */
अटल पूर्णांक call_usermodehelper_exec_async(व्योम *data)
अणु
	काष्ठा subprocess_info *sub_info = data;
	काष्ठा cred *new;
	पूर्णांक retval;

	spin_lock_irq(&current->sighand->siglock);
	flush_संकेत_handlers(current, 1);
	spin_unlock_irq(&current->sighand->siglock);

	/*
	 * Initial kernel thपढ़ोs share ther FS with init, in order to
	 * get the init root directory. But we've now created a new
	 * thपढ़ो that is going to execve a user process and has its own
	 * 'struct fs_struct'. Reset umask to the शेष.
	 */
	current->fs->umask = 0022;

	/*
	 * Our parent (unbound workqueue) runs with elevated scheduling
	 * priority. Aव्योम propagating that पूर्णांकo the userspace child.
	 */
	set_user_nice(current, 0);

	retval = -ENOMEM;
	new = prepare_kernel_cred(current);
	अगर (!new)
		जाओ out;

	spin_lock(&umh_sysctl_lock);
	new->cap_bset = cap_पूर्णांकersect(usermodehelper_bset, new->cap_bset);
	new->cap_inheritable = cap_पूर्णांकersect(usermodehelper_inheritable,
					     new->cap_inheritable);
	spin_unlock(&umh_sysctl_lock);

	अगर (sub_info->init) अणु
		retval = sub_info->init(sub_info, new);
		अगर (retval) अणु
			पात_creds(new);
			जाओ out;
		पूर्ण
	पूर्ण

	commit_creds(new);

	रुको_क्रम_initramfs();
	retval = kernel_execve(sub_info->path,
			       (स्थिर अक्षर *स्थिर *)sub_info->argv,
			       (स्थिर अक्षर *स्थिर *)sub_info->envp);
out:
	sub_info->retval = retval;
	/*
	 * call_usermodehelper_exec_sync() will call umh_complete
	 * अगर UHM_WAIT_PROC.
	 */
	अगर (!(sub_info->रुको & UMH_WAIT_PROC))
		umh_complete(sub_info);
	अगर (!retval)
		वापस 0;
	करो_निकास(0);
पूर्ण

/* Handles UMH_WAIT_PROC.  */
अटल व्योम call_usermodehelper_exec_sync(काष्ठा subprocess_info *sub_info)
अणु
	pid_t pid;

	/* If SIGCLD is ignored करो_रुको won't populate the status. */
	kernel_sigaction(SIGCHLD, संक_पूर्व);
	pid = kernel_thपढ़ो(call_usermodehelper_exec_async, sub_info, SIGCHLD);
	अगर (pid < 0)
		sub_info->retval = pid;
	अन्यथा
		kernel_रुको(pid, &sub_info->retval);

	/* Restore शेष kernel sig handler */
	kernel_sigaction(SIGCHLD, संक_छोड़ो);
	umh_complete(sub_info);
पूर्ण

/*
 * We need to create the usermodehelper kernel thपढ़ो from a task that is affine
 * to an optimized set of CPUs (or nohz housekeeping ones) such that they
 * inherit a widest affinity irrespective of call_usermodehelper() callers with
 * possibly reduced affinity (eg: per-cpu workqueues). We करोn't want
 * usermodehelper tarमाला_लो to contend a busy CPU.
 *
 * Unbound workqueues provide such wide affinity and allow to block on
 * UMH_WAIT_PROC requests without blocking pending request (up to some limit).
 *
 * Besides, workqueues provide the privilege level that caller might not have
 * to perक्रमm the usermodehelper request.
 *
 */
अटल व्योम call_usermodehelper_exec_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा subprocess_info *sub_info =
		container_of(work, काष्ठा subprocess_info, work);

	अगर (sub_info->रुको & UMH_WAIT_PROC) अणु
		call_usermodehelper_exec_sync(sub_info);
	पूर्ण अन्यथा अणु
		pid_t pid;
		/*
		 * Use CLONE_PARENT to reparent it to kthपढ़ोd; we करो not
		 * want to pollute current->children, and we need a parent
		 * that always ignores SIGCHLD to ensure स्वतः-reaping.
		 */
		pid = kernel_thपढ़ो(call_usermodehelper_exec_async, sub_info,
				    CLONE_PARENT | SIGCHLD);
		अगर (pid < 0) अणु
			sub_info->retval = pid;
			umh_complete(sub_info);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * If set, call_usermodehelper_exec() will निकास immediately वापसing -EBUSY
 * (used क्रम preventing user land processes from being created after the user
 * land has been frozen during a प्रणाली-wide hibernation or suspend operation).
 * Should always be manipulated under umhelper_sem acquired क्रम ग_लिखो.
 */
अटल क्रमागत umh_disable_depth usermodehelper_disabled = UMH_DISABLED;

/* Number of helpers running */
अटल atomic_t running_helpers = ATOMIC_INIT(0);

/*
 * Wait queue head used by usermodehelper_disable() to रुको क्रम all running
 * helpers to finish.
 */
अटल DECLARE_WAIT_QUEUE_HEAD(running_helpers_रुकोq);

/*
 * Used by usermodehelper_पढ़ो_lock_रुको() to रुको क्रम usermodehelper_disabled
 * to become 'false'.
 */
अटल DECLARE_WAIT_QUEUE_HEAD(usermodehelper_disabled_रुकोq);

/*
 * Time to रुको क्रम running_helpers to become zero beक्रमe the setting of
 * usermodehelper_disabled in usermodehelper_disable() fails
 */
#घोषणा RUNNING_HELPERS_TIMEOUT	(5 * HZ)

पूर्णांक usermodehelper_पढ़ो_trylock(व्योम)
अणु
	DEFINE_WAIT(रुको);
	पूर्णांक ret = 0;

	करोwn_पढ़ो(&umhelper_sem);
	क्रम (;;) अणु
		prepare_to_रुको(&usermodehelper_disabled_रुकोq, &रुको,
				TASK_INTERRUPTIBLE);
		अगर (!usermodehelper_disabled)
			अवरोध;

		अगर (usermodehelper_disabled == UMH_DISABLED)
			ret = -EAGAIN;

		up_पढ़ो(&umhelper_sem);

		अगर (ret)
			अवरोध;

		schedule();
		try_to_मुक्तze();

		करोwn_पढ़ो(&umhelper_sem);
	पूर्ण
	finish_रुको(&usermodehelper_disabled_रुकोq, &रुको);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usermodehelper_पढ़ो_trylock);

दीर्घ usermodehelper_पढ़ो_lock_रुको(दीर्घ समयout)
अणु
	DEFINE_WAIT(रुको);

	अगर (समयout < 0)
		वापस -EINVAL;

	करोwn_पढ़ो(&umhelper_sem);
	क्रम (;;) अणु
		prepare_to_रुको(&usermodehelper_disabled_रुकोq, &रुको,
				TASK_UNINTERRUPTIBLE);
		अगर (!usermodehelper_disabled)
			अवरोध;

		up_पढ़ो(&umhelper_sem);

		समयout = schedule_समयout(समयout);
		अगर (!समयout)
			अवरोध;

		करोwn_पढ़ो(&umhelper_sem);
	पूर्ण
	finish_रुको(&usermodehelper_disabled_रुकोq, &रुको);
	वापस समयout;
पूर्ण
EXPORT_SYMBOL_GPL(usermodehelper_पढ़ो_lock_रुको);

व्योम usermodehelper_पढ़ो_unlock(व्योम)
अणु
	up_पढ़ो(&umhelper_sem);
पूर्ण
EXPORT_SYMBOL_GPL(usermodehelper_पढ़ो_unlock);

/**
 * __usermodehelper_set_disable_depth - Modअगरy usermodehelper_disabled.
 * @depth: New value to assign to usermodehelper_disabled.
 *
 * Change the value of usermodehelper_disabled (under umhelper_sem locked क्रम
 * writing) and wakeup tasks रुकोing क्रम it to change.
 */
व्योम __usermodehelper_set_disable_depth(क्रमागत umh_disable_depth depth)
अणु
	करोwn_ग_लिखो(&umhelper_sem);
	usermodehelper_disabled = depth;
	wake_up(&usermodehelper_disabled_रुकोq);
	up_ग_लिखो(&umhelper_sem);
पूर्ण

/**
 * __usermodehelper_disable - Prevent new helpers from being started.
 * @depth: New value to assign to usermodehelper_disabled.
 *
 * Set usermodehelper_disabled to @depth and रुको क्रम running helpers to निकास.
 */
पूर्णांक __usermodehelper_disable(क्रमागत umh_disable_depth depth)
अणु
	दीर्घ retval;

	अगर (!depth)
		वापस -EINVAL;

	करोwn_ग_लिखो(&umhelper_sem);
	usermodehelper_disabled = depth;
	up_ग_लिखो(&umhelper_sem);

	/*
	 * From now on call_usermodehelper_exec() won't start any new
	 * helpers, so it is sufficient अगर running_helpers turns out to
	 * be zero at one poपूर्णांक (it may be increased later, but that
	 * करोesn't matter).
	 */
	retval = रुको_event_समयout(running_helpers_रुकोq,
					atomic_पढ़ो(&running_helpers) == 0,
					RUNNING_HELPERS_TIMEOUT);
	अगर (retval)
		वापस 0;

	__usermodehelper_set_disable_depth(UMH_ENABLED);
	वापस -EAGAIN;
पूर्ण

अटल व्योम helper_lock(व्योम)
अणु
	atomic_inc(&running_helpers);
	smp_mb__after_atomic();
पूर्ण

अटल व्योम helper_unlock(व्योम)
अणु
	अगर (atomic_dec_and_test(&running_helpers))
		wake_up(&running_helpers_रुकोq);
पूर्ण

/**
 * call_usermodehelper_setup - prepare to call a usermode helper
 * @path: path to usermode executable
 * @argv: arg vector क्रम process
 * @envp: environment क्रम process
 * @gfp_mask: gfp mask क्रम memory allocation
 * @init: an init function
 * @cleanup: a cleanup function
 * @data: arbitrary context sensitive data
 *
 * Returns either %शून्य on allocation failure, or a subprocess_info
 * काष्ठाure.  This should be passed to call_usermodehelper_exec to
 * exec the process and मुक्त the काष्ठाure.
 *
 * The init function is used to customize the helper process prior to
 * exec.  A non-zero वापस code causes the process to error out, निकास,
 * and वापस the failure to the calling process
 *
 * The cleanup function is just beक्रमe the subprocess_info is about to
 * be मुक्तd.  This can be used क्रम मुक्तing the argv and envp.  The
 * Function must be runnable in either a process context or the
 * context in which call_usermodehelper_exec is called.
 */
काष्ठा subprocess_info *call_usermodehelper_setup(स्थिर अक्षर *path, अक्षर **argv,
		अक्षर **envp, gfp_t gfp_mask,
		पूर्णांक (*init)(काष्ठा subprocess_info *info, काष्ठा cred *new),
		व्योम (*cleanup)(काष्ठा subprocess_info *info),
		व्योम *data)
अणु
	काष्ठा subprocess_info *sub_info;
	sub_info = kzalloc(माप(काष्ठा subprocess_info), gfp_mask);
	अगर (!sub_info)
		जाओ out;

	INIT_WORK(&sub_info->work, call_usermodehelper_exec_work);

#अगर_घोषित CONFIG_STATIC_USERMODEHELPER
	sub_info->path = CONFIG_STATIC_USERMODEHELPER_PATH;
#अन्यथा
	sub_info->path = path;
#पूर्ण_अगर
	sub_info->argv = argv;
	sub_info->envp = envp;

	sub_info->cleanup = cleanup;
	sub_info->init = init;
	sub_info->data = data;
  out:
	वापस sub_info;
पूर्ण
EXPORT_SYMBOL(call_usermodehelper_setup);

/**
 * call_usermodehelper_exec - start a usermode application
 * @sub_info: inक्रमmation about the subprocess
 * @रुको: रुको क्रम the application to finish and वापस status.
 *        when UMH_NO_WAIT करोn't रुको at all, but you get no useful error back
 *        when the program couldn't be exec'ed. This makes it safe to call
 *        from पूर्णांकerrupt context.
 *
 * Runs a user-space application.  The application is started
 * asynchronously अगर रुको is not set, and runs as a child of प्रणाली workqueues.
 * (ie. it runs with full root capabilities and optimized affinity).
 *
 * Note: successful वापस value करोes not guarantee the helper was called at
 * all. You can't rely on sub_info->अणुinit,cleanupपूर्ण being called even क्रम
 * UMH_WAIT_* रुको modes as STATIC_USERMODEHELPER_PATH="" turns all helpers
 * पूर्णांकo a successful no-op.
 */
पूर्णांक call_usermodehelper_exec(काष्ठा subprocess_info *sub_info, पूर्णांक रुको)
अणु
	DECLARE_COMPLETION_ONSTACK(करोne);
	पूर्णांक retval = 0;

	अगर (!sub_info->path) अणु
		call_usermodehelper_मुक्तinfo(sub_info);
		वापस -EINVAL;
	पूर्ण
	helper_lock();
	अगर (usermodehelper_disabled) अणु
		retval = -EBUSY;
		जाओ out;
	पूर्ण

	/*
	 * If there is no binary क्रम us to call, then just वापस and get out of
	 * here.  This allows us to set STATIC_USERMODEHELPER_PATH to "" and
	 * disable all call_usermodehelper() calls.
	 */
	अगर (म_माप(sub_info->path) == 0)
		जाओ out;

	/*
	 * Set the completion poपूर्णांकer only अगर there is a रुकोer.
	 * This makes it possible to use umh_complete to मुक्त
	 * the data काष्ठाure in हाल of UMH_NO_WAIT.
	 */
	sub_info->complete = (रुको == UMH_NO_WAIT) ? शून्य : &करोne;
	sub_info->रुको = रुको;

	queue_work(प्रणाली_unbound_wq, &sub_info->work);
	अगर (रुको == UMH_NO_WAIT)	/* task has मुक्तd sub_info */
		जाओ unlock;

	अगर (रुको & UMH_KILLABLE) अणु
		retval = रुको_क्रम_completion_समाप्तable(&करोne);
		अगर (!retval)
			जाओ रुको_करोne;

		/* umh_complete() will see शून्य and मुक्त sub_info */
		अगर (xchg(&sub_info->complete, शून्य))
			जाओ unlock;
		/* fallthrough, umh_complete() was alपढ़ोy called */
	पूर्ण

	रुको_क्रम_completion(&करोne);
रुको_करोne:
	retval = sub_info->retval;
out:
	call_usermodehelper_मुक्तinfo(sub_info);
unlock:
	helper_unlock();
	वापस retval;
पूर्ण
EXPORT_SYMBOL(call_usermodehelper_exec);

/**
 * call_usermodehelper() - prepare and start a usermode application
 * @path: path to usermode executable
 * @argv: arg vector क्रम process
 * @envp: environment क्रम process
 * @रुको: रुको क्रम the application to finish and वापस status.
 *        when UMH_NO_WAIT करोn't रुको at all, but you get no useful error back
 *        when the program couldn't be exec'ed. This makes it safe to call
 *        from पूर्णांकerrupt context.
 *
 * This function is the equivalent to use call_usermodehelper_setup() and
 * call_usermodehelper_exec().
 */
पूर्णांक call_usermodehelper(स्थिर अक्षर *path, अक्षर **argv, अक्षर **envp, पूर्णांक रुको)
अणु
	काष्ठा subprocess_info *info;
	gfp_t gfp_mask = (रुको == UMH_NO_WAIT) ? GFP_ATOMIC : GFP_KERNEL;

	info = call_usermodehelper_setup(path, argv, envp, gfp_mask,
					 शून्य, शून्य, शून्य);
	अगर (info == शून्य)
		वापस -ENOMEM;

	वापस call_usermodehelper_exec(info, रुको);
पूर्ण
EXPORT_SYMBOL(call_usermodehelper);

अटल पूर्णांक proc_cap_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			 व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा ctl_table t;
	अचिन्हित दीर्घ cap_array[_KERNEL_CAPABILITY_U32S];
	kernel_cap_t new_cap;
	पूर्णांक err, i;

	अगर (ग_लिखो && (!capable(CAP_SETPCAP) ||
		      !capable(CAP_SYS_MODULE)))
		वापस -EPERM;

	/*
	 * convert from the global kernel_cap_t to the uदीर्घ array to prपूर्णांक to
	 * userspace अगर this is a पढ़ो.
	 */
	spin_lock(&umh_sysctl_lock);
	क्रम (i = 0; i < _KERNEL_CAPABILITY_U32S; i++)  अणु
		अगर (table->data == CAP_BSET)
			cap_array[i] = usermodehelper_bset.cap[i];
		अन्यथा अगर (table->data == CAP_PI)
			cap_array[i] = usermodehelper_inheritable.cap[i];
		अन्यथा
			BUG();
	पूर्ण
	spin_unlock(&umh_sysctl_lock);

	t = *table;
	t.data = &cap_array;

	/*
	 * actually पढ़ो or ग_लिखो and array of uदीर्घs from userspace.  Remember
	 * these are least signअगरicant 32 bits first
	 */
	err = proc_करोuदीर्घvec_minmax(&t, ग_लिखो, buffer, lenp, ppos);
	अगर (err < 0)
		वापस err;

	/*
	 * convert from the sysctl array of uदीर्घs to the kernel_cap_t
	 * पूर्णांकernal representation
	 */
	क्रम (i = 0; i < _KERNEL_CAPABILITY_U32S; i++)
		new_cap.cap[i] = cap_array[i];

	/*
	 * Drop everything not in the new_cap (but करोn't add things)
	 */
	अगर (ग_लिखो) अणु
		spin_lock(&umh_sysctl_lock);
		अगर (table->data == CAP_BSET)
			usermodehelper_bset = cap_पूर्णांकersect(usermodehelper_bset, new_cap);
		अगर (table->data == CAP_PI)
			usermodehelper_inheritable = cap_पूर्णांकersect(usermodehelper_inheritable, new_cap);
		spin_unlock(&umh_sysctl_lock);
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा ctl_table usermodehelper_table[] = अणु
	अणु
		.procname	= "bset",
		.data		= CAP_BSET,
		.maxlen		= _KERNEL_CAPABILITY_U32S * माप(अचिन्हित दीर्घ),
		.mode		= 0600,
		.proc_handler	= proc_cap_handler,
	पूर्ण,
	अणु
		.procname	= "inheritable",
		.data		= CAP_PI,
		.maxlen		= _KERNEL_CAPABILITY_U32S * माप(अचिन्हित दीर्घ),
		.mode		= 0600,
		.proc_handler	= proc_cap_handler,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
