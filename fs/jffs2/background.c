<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2001-2007 Red Hat, Inc.
 * Copyright तऊ 2004-2010 David Woodhouse <dwmw2@infradead.org>
 *
 * Created by David Woodhouse <dwmw2@infradead.org>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/jffs2.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/completion.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश "nodelist.h"


अटल पूर्णांक jffs2_garbage_collect_thपढ़ो(व्योम *);

व्योम jffs2_garbage_collect_trigger(काष्ठा jffs2_sb_info *c)
अणु
	निश्चित_spin_locked(&c->erase_completion_lock);
	अगर (c->gc_task && jffs2_thपढ़ो_should_wake(c))
		send_sig(SIGHUP, c->gc_task, 1);
पूर्ण

/* This must only ever be called when no GC thपढ़ो is currently running */
पूर्णांक jffs2_start_garbage_collect_thपढ़ो(काष्ठा jffs2_sb_info *c)
अणु
	काष्ठा task_काष्ठा *tsk;
	पूर्णांक ret = 0;

	BUG_ON(c->gc_task);

	init_completion(&c->gc_thपढ़ो_start);
	init_completion(&c->gc_thपढ़ो_निकास);

	tsk = kthपढ़ो_run(jffs2_garbage_collect_thपढ़ो, c, "jffs2_gcd_mtd%d", c->mtd->index);
	अगर (IS_ERR(tsk)) अणु
		pr_warn("fork failed for JFFS2 garbage collect thread: %ld\n",
			-PTR_ERR(tsk));
		complete(&c->gc_thपढ़ो_निकास);
		ret = PTR_ERR(tsk);
	पूर्ण अन्यथा अणु
		/* Wait क्रम it... */
		jffs2_dbg(1, "Garbage collect thread is pid %d\n", tsk->pid);
		रुको_क्रम_completion(&c->gc_thपढ़ो_start);
		ret = tsk->pid;
	पूर्ण

	वापस ret;
पूर्ण

व्योम jffs2_stop_garbage_collect_thपढ़ो(काष्ठा jffs2_sb_info *c)
अणु
	पूर्णांक रुको = 0;
	spin_lock(&c->erase_completion_lock);
	अगर (c->gc_task) अणु
		jffs2_dbg(1, "Killing GC task %d\n", c->gc_task->pid);
		send_sig(SIGKILL, c->gc_task, 1);
		रुको = 1;
	पूर्ण
	spin_unlock(&c->erase_completion_lock);
	अगर (रुको)
		रुको_क्रम_completion(&c->gc_thपढ़ो_निकास);
पूर्ण

अटल पूर्णांक jffs2_garbage_collect_thपढ़ो(व्योम *_c)
अणु
	काष्ठा jffs2_sb_info *c = _c;
	sigset_t hupmask;

	siginitset(&hupmask, sigmask(SIGHUP));
	allow_संकेत(SIGKILL);
	allow_संकेत(SIGSTOP);
	allow_संकेत(SIGHUP);

	c->gc_task = current;
	complete(&c->gc_thपढ़ो_start);

	set_user_nice(current, 10);

	set_मुक्तzable();
	क्रम (;;) अणु
		sigprocmask(SIG_UNBLOCK, &hupmask, शून्य);
	again:
		spin_lock(&c->erase_completion_lock);
		अगर (!jffs2_thपढ़ो_should_wake(c)) अणु
			set_current_state (TASK_INTERRUPTIBLE);
			spin_unlock(&c->erase_completion_lock);
			jffs2_dbg(1, "%s(): sleeping...\n", __func__);
			schedule();
		पूर्ण अन्यथा अणु
			spin_unlock(&c->erase_completion_lock);
		पूर्ण
		/* Problem - immediately after bootup, the GCD spends a lot
		 * of समय in places like jffs2_समाप्त_fragtree(); so much so
		 * that userspace processes (like gdm and X) are starved
		 * despite plenty of cond_resched()s and renicing.  Yield()
		 * करोesn't help, either (presumably because userspace and GCD
		 * are generally competing क्रम a higher latency resource -
		 * disk).
		 * This क्रमces the GCD to slow the hell करोwn.   Pulling an
		 * inode in with पढ़ो_inode() is much preferable to having
		 * the GC thपढ़ो get there first. */
		schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(50));

		अगर (kthपढ़ो_should_stop()) अणु
			jffs2_dbg(1, "%s(): kthread_stop() called\n", __func__);
			जाओ die;
		पूर्ण

		/* Put_super will send a SIGKILL and then रुको on the sem.
		 */
		जबतक (संकेत_pending(current) || मुक्तzing(current)) अणु
			अचिन्हित दीर्घ signr;

			अगर (try_to_मुक्तze())
				जाओ again;

			signr = kernel_dequeue_संकेत();

			चयन(signr) अणु
			हाल SIGSTOP:
				jffs2_dbg(1, "%s(): SIGSTOP received\n",
					  __func__);
				kernel_संकेत_stop();
				अवरोध;

			हाल SIGKILL:
				jffs2_dbg(1, "%s(): SIGKILL received\n",
					  __func__);
				जाओ die;

			हाल SIGHUP:
				jffs2_dbg(1, "%s(): SIGHUP received\n",
					  __func__);
				अवरोध;
			शेष:
				jffs2_dbg(1, "%s(): signal %ld received\n",
					  __func__, signr);
			पूर्ण
		पूर्ण
		/* We करोn't want SIGHUP to पूर्णांकerrupt us. STOP and KILL are OK though. */
		sigprocmask(SIG_BLOCK, &hupmask, शून्य);

		jffs2_dbg(1, "%s(): pass\n", __func__);
		अगर (jffs2_garbage_collect_pass(c) == -ENOSPC) अणु
			pr_notice("No space for garbage collection. Aborting GC thread\n");
			जाओ die;
		पूर्ण
	पूर्ण
 die:
	spin_lock(&c->erase_completion_lock);
	c->gc_task = शून्य;
	spin_unlock(&c->erase_completion_lock);
	complete_and_निकास(&c->gc_thपढ़ो_निकास, 0);
पूर्ण
