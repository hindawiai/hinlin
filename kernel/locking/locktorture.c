<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Module-based torture test facility क्रम locking
 *
 * Copyright (C) IBM Corporation, 2014
 *
 * Authors: Paul E. McKenney <paulmck@linux.ibm.com>
 *          Davidlohr Bueso <dave@stgoद_असल.net>
 *	Based on kernel/rcu/torture.c.
 */

#घोषणा pr_fmt(fmt) fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched/rt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <uapi/linux/sched/types.h>
#समावेश <linux/rपंचांगutex.h>
#समावेश <linux/atomic.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/torture.h>
#समावेश <linux/reboot.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Paul E. McKenney <paulmck@linux.ibm.com>");

torture_param(पूर्णांक, nग_लिखोrs_stress, -1,
	     "Number of write-locking stress-test threads");
torture_param(पूर्णांक, nपढ़ोers_stress, -1,
	     "Number of read-locking stress-test threads");
torture_param(पूर्णांक, onoff_holकरोff, 0, "Time after boot before CPU hotplugs (s)");
torture_param(पूर्णांक, onoff_पूर्णांकerval, 0,
	     "Time between CPU hotplugs (s), 0=disable");
torture_param(पूर्णांक, shuffle_पूर्णांकerval, 3,
	     "Number of jiffies between shuffles, 0=disable");
torture_param(पूर्णांक, shutकरोwn_secs, 0, "Shutdown time (j), <= zero to disable.");
torture_param(पूर्णांक, stat_पूर्णांकerval, 60,
	     "Number of seconds between stats printk()s");
torture_param(पूर्णांक, stutter, 5, "Number of jiffies to run/halt test, 0=disable");
torture_param(पूर्णांक, verbose, 1,
	     "Enable verbose debugging printk()s");

अटल अक्षर *torture_type = "spin_lock";
module_param(torture_type, अक्षरp, 0444);
MODULE_PARM_DESC(torture_type,
		 "Type of lock to torture (spin_lock, spin_lock_irq, mutex_lock, ...)");

अटल काष्ठा task_काष्ठा *stats_task;
अटल काष्ठा task_काष्ठा **ग_लिखोr_tasks;
अटल काष्ठा task_काष्ठा **पढ़ोer_tasks;

अटल bool lock_is_ग_लिखो_held;
अटल bool lock_is_पढ़ो_held;
अटल अचिन्हित दीर्घ last_lock_release;

काष्ठा lock_stress_stats अणु
	दीर्घ n_lock_fail;
	दीर्घ n_lock_acquired;
पूर्ण;

/* Forward reference. */
अटल व्योम lock_torture_cleanup(व्योम);

/*
 * Operations vector क्रम selecting dअगरferent types of tests.
 */
काष्ठा lock_torture_ops अणु
	व्योम (*init)(व्योम);
	व्योम (*निकास)(व्योम);
	पूर्णांक (*ग_लिखोlock)(पूर्णांक tid);
	व्योम (*ग_लिखो_delay)(काष्ठा torture_अक्रमom_state *trsp);
	व्योम (*task_boost)(काष्ठा torture_अक्रमom_state *trsp);
	व्योम (*ग_लिखोunlock)(पूर्णांक tid);
	पूर्णांक (*पढ़ोlock)(पूर्णांक tid);
	व्योम (*पढ़ो_delay)(काष्ठा torture_अक्रमom_state *trsp);
	व्योम (*पढ़ोunlock)(पूर्णांक tid);

	अचिन्हित दीर्घ flags; /* क्रम irq spinlocks */
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा lock_torture_cxt अणु
	पूर्णांक nrealग_लिखोrs_stress;
	पूर्णांक nrealपढ़ोers_stress;
	bool debug_lock;
	bool init_called;
	atomic_t n_lock_torture_errors;
	काष्ठा lock_torture_ops *cur_ops;
	काष्ठा lock_stress_stats *lwsa; /* ग_लिखोr statistics */
	काष्ठा lock_stress_stats *lrsa; /* पढ़ोer statistics */
पूर्ण;
अटल काष्ठा lock_torture_cxt cxt = अणु 0, 0, false, false,
				       ATOMIC_INIT(0),
				       शून्य, शून्यपूर्ण;
/*
 * Definitions क्रम lock torture testing.
 */

अटल पूर्णांक torture_lock_busted_ग_लिखो_lock(पूर्णांक tid __maybe_unused)
अणु
	वापस 0;  /* BUGGY, करो not use in real lअगरe!!! */
पूर्ण

अटल व्योम torture_lock_busted_ग_लिखो_delay(काष्ठा torture_अक्रमom_state *trsp)
अणु
	स्थिर अचिन्हित दीर्घ दीर्घdelay_ms = 100;

	/* We want a दीर्घ delay occasionally to क्रमce massive contention.  */
	अगर (!(torture_अक्रमom(trsp) %
	      (cxt.nrealग_लिखोrs_stress * 2000 * दीर्घdelay_ms)))
		mdelay(दीर्घdelay_ms);
	अगर (!(torture_अक्रमom(trsp) % (cxt.nrealग_लिखोrs_stress * 20000)))
		torture_preempt_schedule();  /* Allow test to be preempted. */
पूर्ण

अटल व्योम torture_lock_busted_ग_लिखो_unlock(पूर्णांक tid __maybe_unused)
अणु
	  /* BUGGY, करो not use in real lअगरe!!! */
पूर्ण

अटल व्योम torture_boost_dummy(काष्ठा torture_अक्रमom_state *trsp)
अणु
	/* Only rपंचांगutexes care about priority */
पूर्ण

अटल काष्ठा lock_torture_ops lock_busted_ops = अणु
	.ग_लिखोlock	= torture_lock_busted_ग_लिखो_lock,
	.ग_लिखो_delay	= torture_lock_busted_ग_लिखो_delay,
	.task_boost     = torture_boost_dummy,
	.ग_लिखोunlock	= torture_lock_busted_ग_लिखो_unlock,
	.पढ़ोlock       = शून्य,
	.पढ़ो_delay     = शून्य,
	.पढ़ोunlock     = शून्य,
	.name		= "lock_busted"
पूर्ण;

अटल DEFINE_SPINLOCK(torture_spinlock);

अटल पूर्णांक torture_spin_lock_ग_लिखो_lock(पूर्णांक tid __maybe_unused)
__acquires(torture_spinlock)
अणु
	spin_lock(&torture_spinlock);
	वापस 0;
पूर्ण

अटल व्योम torture_spin_lock_ग_लिखो_delay(काष्ठा torture_अक्रमom_state *trsp)
अणु
	स्थिर अचिन्हित दीर्घ लघुdelay_us = 2;
	स्थिर अचिन्हित दीर्घ दीर्घdelay_ms = 100;

	/* We want a लघु delay mostly to emulate likely code, and
	 * we want a दीर्घ delay occasionally to क्रमce massive contention.
	 */
	अगर (!(torture_अक्रमom(trsp) %
	      (cxt.nrealग_लिखोrs_stress * 2000 * दीर्घdelay_ms)))
		mdelay(दीर्घdelay_ms);
	अगर (!(torture_अक्रमom(trsp) %
	      (cxt.nrealग_लिखोrs_stress * 2 * लघुdelay_us)))
		udelay(लघुdelay_us);
	अगर (!(torture_अक्रमom(trsp) % (cxt.nrealग_लिखोrs_stress * 20000)))
		torture_preempt_schedule();  /* Allow test to be preempted. */
पूर्ण

अटल व्योम torture_spin_lock_ग_लिखो_unlock(पूर्णांक tid __maybe_unused)
__releases(torture_spinlock)
अणु
	spin_unlock(&torture_spinlock);
पूर्ण

अटल काष्ठा lock_torture_ops spin_lock_ops = अणु
	.ग_लिखोlock	= torture_spin_lock_ग_लिखो_lock,
	.ग_लिखो_delay	= torture_spin_lock_ग_लिखो_delay,
	.task_boost     = torture_boost_dummy,
	.ग_लिखोunlock	= torture_spin_lock_ग_लिखो_unlock,
	.पढ़ोlock       = शून्य,
	.पढ़ो_delay     = शून्य,
	.पढ़ोunlock     = शून्य,
	.name		= "spin_lock"
पूर्ण;

अटल पूर्णांक torture_spin_lock_ग_लिखो_lock_irq(पूर्णांक tid __maybe_unused)
__acquires(torture_spinlock)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&torture_spinlock, flags);
	cxt.cur_ops->flags = flags;
	वापस 0;
पूर्ण

अटल व्योम torture_lock_spin_ग_लिखो_unlock_irq(पूर्णांक tid __maybe_unused)
__releases(torture_spinlock)
अणु
	spin_unlock_irqrestore(&torture_spinlock, cxt.cur_ops->flags);
पूर्ण

अटल काष्ठा lock_torture_ops spin_lock_irq_ops = अणु
	.ग_लिखोlock	= torture_spin_lock_ग_लिखो_lock_irq,
	.ग_लिखो_delay	= torture_spin_lock_ग_लिखो_delay,
	.task_boost     = torture_boost_dummy,
	.ग_लिखोunlock	= torture_lock_spin_ग_लिखो_unlock_irq,
	.पढ़ोlock       = शून्य,
	.पढ़ो_delay     = शून्य,
	.पढ़ोunlock     = शून्य,
	.name		= "spin_lock_irq"
पूर्ण;

अटल DEFINE_RWLOCK(torture_rwlock);

अटल पूर्णांक torture_rwlock_ग_लिखो_lock(पूर्णांक tid __maybe_unused)
__acquires(torture_rwlock)
अणु
	ग_लिखो_lock(&torture_rwlock);
	वापस 0;
पूर्ण

अटल व्योम torture_rwlock_ग_लिखो_delay(काष्ठा torture_अक्रमom_state *trsp)
अणु
	स्थिर अचिन्हित दीर्घ लघुdelay_us = 2;
	स्थिर अचिन्हित दीर्घ दीर्घdelay_ms = 100;

	/* We want a लघु delay mostly to emulate likely code, and
	 * we want a दीर्घ delay occasionally to क्रमce massive contention.
	 */
	अगर (!(torture_अक्रमom(trsp) %
	      (cxt.nrealग_लिखोrs_stress * 2000 * दीर्घdelay_ms)))
		mdelay(दीर्घdelay_ms);
	अन्यथा
		udelay(लघुdelay_us);
पूर्ण

अटल व्योम torture_rwlock_ग_लिखो_unlock(पूर्णांक tid __maybe_unused)
__releases(torture_rwlock)
अणु
	ग_लिखो_unlock(&torture_rwlock);
पूर्ण

अटल पूर्णांक torture_rwlock_पढ़ो_lock(पूर्णांक tid __maybe_unused)
__acquires(torture_rwlock)
अणु
	पढ़ो_lock(&torture_rwlock);
	वापस 0;
पूर्ण

अटल व्योम torture_rwlock_पढ़ो_delay(काष्ठा torture_अक्रमom_state *trsp)
अणु
	स्थिर अचिन्हित दीर्घ लघुdelay_us = 10;
	स्थिर अचिन्हित दीर्घ दीर्घdelay_ms = 100;

	/* We want a लघु delay mostly to emulate likely code, and
	 * we want a दीर्घ delay occasionally to क्रमce massive contention.
	 */
	अगर (!(torture_अक्रमom(trsp) %
	      (cxt.nrealपढ़ोers_stress * 2000 * दीर्घdelay_ms)))
		mdelay(दीर्घdelay_ms);
	अन्यथा
		udelay(लघुdelay_us);
पूर्ण

अटल व्योम torture_rwlock_पढ़ो_unlock(पूर्णांक tid __maybe_unused)
__releases(torture_rwlock)
अणु
	पढ़ो_unlock(&torture_rwlock);
पूर्ण

अटल काष्ठा lock_torture_ops rw_lock_ops = अणु
	.ग_लिखोlock	= torture_rwlock_ग_लिखो_lock,
	.ग_लिखो_delay	= torture_rwlock_ग_लिखो_delay,
	.task_boost     = torture_boost_dummy,
	.ग_लिखोunlock	= torture_rwlock_ग_लिखो_unlock,
	.पढ़ोlock       = torture_rwlock_पढ़ो_lock,
	.पढ़ो_delay     = torture_rwlock_पढ़ो_delay,
	.पढ़ोunlock     = torture_rwlock_पढ़ो_unlock,
	.name		= "rw_lock"
पूर्ण;

अटल पूर्णांक torture_rwlock_ग_लिखो_lock_irq(पूर्णांक tid __maybe_unused)
__acquires(torture_rwlock)
अणु
	अचिन्हित दीर्घ flags;

	ग_लिखो_lock_irqsave(&torture_rwlock, flags);
	cxt.cur_ops->flags = flags;
	वापस 0;
पूर्ण

अटल व्योम torture_rwlock_ग_लिखो_unlock_irq(पूर्णांक tid __maybe_unused)
__releases(torture_rwlock)
अणु
	ग_लिखो_unlock_irqrestore(&torture_rwlock, cxt.cur_ops->flags);
पूर्ण

अटल पूर्णांक torture_rwlock_पढ़ो_lock_irq(पूर्णांक tid __maybe_unused)
__acquires(torture_rwlock)
अणु
	अचिन्हित दीर्घ flags;

	पढ़ो_lock_irqsave(&torture_rwlock, flags);
	cxt.cur_ops->flags = flags;
	वापस 0;
पूर्ण

अटल व्योम torture_rwlock_पढ़ो_unlock_irq(पूर्णांक tid __maybe_unused)
__releases(torture_rwlock)
अणु
	पढ़ो_unlock_irqrestore(&torture_rwlock, cxt.cur_ops->flags);
पूर्ण

अटल काष्ठा lock_torture_ops rw_lock_irq_ops = अणु
	.ग_लिखोlock	= torture_rwlock_ग_लिखो_lock_irq,
	.ग_लिखो_delay	= torture_rwlock_ग_लिखो_delay,
	.task_boost     = torture_boost_dummy,
	.ग_लिखोunlock	= torture_rwlock_ग_लिखो_unlock_irq,
	.पढ़ोlock       = torture_rwlock_पढ़ो_lock_irq,
	.पढ़ो_delay     = torture_rwlock_पढ़ो_delay,
	.पढ़ोunlock     = torture_rwlock_पढ़ो_unlock_irq,
	.name		= "rw_lock_irq"
पूर्ण;

अटल DEFINE_MUTEX(torture_mutex);

अटल पूर्णांक torture_mutex_lock(पूर्णांक tid __maybe_unused)
__acquires(torture_mutex)
अणु
	mutex_lock(&torture_mutex);
	वापस 0;
पूर्ण

अटल व्योम torture_mutex_delay(काष्ठा torture_अक्रमom_state *trsp)
अणु
	स्थिर अचिन्हित दीर्घ दीर्घdelay_ms = 100;

	/* We want a दीर्घ delay occasionally to क्रमce massive contention.  */
	अगर (!(torture_अक्रमom(trsp) %
	      (cxt.nrealग_लिखोrs_stress * 2000 * दीर्घdelay_ms)))
		mdelay(दीर्घdelay_ms * 5);
	अन्यथा
		mdelay(दीर्घdelay_ms / 5);
	अगर (!(torture_अक्रमom(trsp) % (cxt.nrealग_लिखोrs_stress * 20000)))
		torture_preempt_schedule();  /* Allow test to be preempted. */
पूर्ण

अटल व्योम torture_mutex_unlock(पूर्णांक tid __maybe_unused)
__releases(torture_mutex)
अणु
	mutex_unlock(&torture_mutex);
पूर्ण

अटल काष्ठा lock_torture_ops mutex_lock_ops = अणु
	.ग_लिखोlock	= torture_mutex_lock,
	.ग_लिखो_delay	= torture_mutex_delay,
	.task_boost     = torture_boost_dummy,
	.ग_लिखोunlock	= torture_mutex_unlock,
	.पढ़ोlock       = शून्य,
	.पढ़ो_delay     = शून्य,
	.पढ़ोunlock     = शून्य,
	.name		= "mutex_lock"
पूर्ण;

#समावेश <linux/ww_mutex.h>
/*
 * The torture ww_mutexes should beदीर्घ to the same lock class as
 * torture_ww_class to aव्योम lockdep problem. The ww_mutex_init()
 * function is called क्रम initialization to ensure that.
 */
अटल DEFINE_WD_CLASS(torture_ww_class);
अटल काष्ठा ww_mutex torture_ww_mutex_0, torture_ww_mutex_1, torture_ww_mutex_2;
अटल काष्ठा ww_acquire_ctx *ww_acquire_ctxs;

अटल व्योम torture_ww_mutex_init(व्योम)
अणु
	ww_mutex_init(&torture_ww_mutex_0, &torture_ww_class);
	ww_mutex_init(&torture_ww_mutex_1, &torture_ww_class);
	ww_mutex_init(&torture_ww_mutex_2, &torture_ww_class);

	ww_acquire_ctxs = kदो_स्मृति_array(cxt.nrealग_लिखोrs_stress,
					माप(*ww_acquire_ctxs),
					GFP_KERNEL);
	अगर (!ww_acquire_ctxs)
		VERBOSE_TOROUT_STRING("ww_acquire_ctx: Out of memory");
पूर्ण

अटल व्योम torture_ww_mutex_निकास(व्योम)
अणु
	kमुक्त(ww_acquire_ctxs);
पूर्ण

अटल पूर्णांक torture_ww_mutex_lock(पूर्णांक tid)
__acquires(torture_ww_mutex_0)
__acquires(torture_ww_mutex_1)
__acquires(torture_ww_mutex_2)
अणु
	LIST_HEAD(list);
	काष्ठा reorder_lock अणु
		काष्ठा list_head link;
		काष्ठा ww_mutex *lock;
	पूर्ण locks[3], *ll, *ln;
	काष्ठा ww_acquire_ctx *ctx = &ww_acquire_ctxs[tid];

	locks[0].lock = &torture_ww_mutex_0;
	list_add(&locks[0].link, &list);

	locks[1].lock = &torture_ww_mutex_1;
	list_add(&locks[1].link, &list);

	locks[2].lock = &torture_ww_mutex_2;
	list_add(&locks[2].link, &list);

	ww_acquire_init(ctx, &torture_ww_class);

	list_क्रम_each_entry(ll, &list, link) अणु
		पूर्णांक err;

		err = ww_mutex_lock(ll->lock, ctx);
		अगर (!err)
			जारी;

		ln = ll;
		list_क्रम_each_entry_जारी_reverse(ln, &list, link)
			ww_mutex_unlock(ln->lock);

		अगर (err != -EDEADLK)
			वापस err;

		ww_mutex_lock_slow(ll->lock, ctx);
		list_move(&ll->link, &list);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम torture_ww_mutex_unlock(पूर्णांक tid)
__releases(torture_ww_mutex_0)
__releases(torture_ww_mutex_1)
__releases(torture_ww_mutex_2)
अणु
	काष्ठा ww_acquire_ctx *ctx = &ww_acquire_ctxs[tid];

	ww_mutex_unlock(&torture_ww_mutex_0);
	ww_mutex_unlock(&torture_ww_mutex_1);
	ww_mutex_unlock(&torture_ww_mutex_2);
	ww_acquire_fini(ctx);
पूर्ण

अटल काष्ठा lock_torture_ops ww_mutex_lock_ops = अणु
	.init		= torture_ww_mutex_init,
	.निकास		= torture_ww_mutex_निकास,
	.ग_लिखोlock	= torture_ww_mutex_lock,
	.ग_लिखो_delay	= torture_mutex_delay,
	.task_boost     = torture_boost_dummy,
	.ग_लिखोunlock	= torture_ww_mutex_unlock,
	.पढ़ोlock       = शून्य,
	.पढ़ो_delay     = शून्य,
	.पढ़ोunlock     = शून्य,
	.name		= "ww_mutex_lock"
पूर्ण;

#अगर_घोषित CONFIG_RT_MUTEXES
अटल DEFINE_RT_MUTEX(torture_rपंचांगutex);

अटल पूर्णांक torture_rपंचांगutex_lock(पूर्णांक tid __maybe_unused)
__acquires(torture_rपंचांगutex)
अणु
	rt_mutex_lock(&torture_rपंचांगutex);
	वापस 0;
पूर्ण

अटल व्योम torture_rपंचांगutex_boost(काष्ठा torture_अक्रमom_state *trsp)
अणु
	स्थिर अचिन्हित पूर्णांक factor = 50000; /* yes, quite arbitrary */

	अगर (!rt_task(current)) अणु
		/*
		 * Boost priority once every ~50k operations. When the
		 * task tries to take the lock, the rपंचांगutex it will account
		 * क्रम the new priority, and करो any corresponding pi-dance.
		 */
		अगर (trsp && !(torture_अक्रमom(trsp) %
			      (cxt.nrealग_लिखोrs_stress * factor))) अणु
			sched_set_fअगरo(current);
		पूर्ण अन्यथा /* common हाल, करो nothing */
			वापस;
	पूर्ण अन्यथा अणु
		/*
		 * The task will reमुख्य boosted क्रम another ~500k operations,
		 * then restored back to its original prio, and so क्रमth.
		 *
		 * When @trsp is nil, we want to क्रमce-reset the task क्रम
		 * stopping the kthपढ़ो.
		 */
		अगर (!trsp || !(torture_अक्रमom(trsp) %
			       (cxt.nrealग_लिखोrs_stress * factor * 2))) अणु
			sched_set_normal(current, 0);
		पूर्ण अन्यथा /* common हाल, करो nothing */
			वापस;
	पूर्ण
पूर्ण

अटल व्योम torture_rपंचांगutex_delay(काष्ठा torture_अक्रमom_state *trsp)
अणु
	स्थिर अचिन्हित दीर्घ लघुdelay_us = 2;
	स्थिर अचिन्हित दीर्घ दीर्घdelay_ms = 100;

	/*
	 * We want a लघु delay mostly to emulate likely code, and
	 * we want a दीर्घ delay occasionally to क्रमce massive contention.
	 */
	अगर (!(torture_अक्रमom(trsp) %
	      (cxt.nrealग_लिखोrs_stress * 2000 * दीर्घdelay_ms)))
		mdelay(दीर्घdelay_ms);
	अगर (!(torture_अक्रमom(trsp) %
	      (cxt.nrealग_लिखोrs_stress * 2 * लघुdelay_us)))
		udelay(लघुdelay_us);
	अगर (!(torture_अक्रमom(trsp) % (cxt.nrealग_लिखोrs_stress * 20000)))
		torture_preempt_schedule();  /* Allow test to be preempted. */
पूर्ण

अटल व्योम torture_rपंचांगutex_unlock(पूर्णांक tid __maybe_unused)
__releases(torture_rपंचांगutex)
अणु
	rt_mutex_unlock(&torture_rपंचांगutex);
पूर्ण

अटल काष्ठा lock_torture_ops rपंचांगutex_lock_ops = अणु
	.ग_लिखोlock	= torture_rपंचांगutex_lock,
	.ग_लिखो_delay	= torture_rपंचांगutex_delay,
	.task_boost     = torture_rपंचांगutex_boost,
	.ग_लिखोunlock	= torture_rपंचांगutex_unlock,
	.पढ़ोlock       = शून्य,
	.पढ़ो_delay     = शून्य,
	.पढ़ोunlock     = शून्य,
	.name		= "rtmutex_lock"
पूर्ण;
#पूर्ण_अगर

अटल DECLARE_RWSEM(torture_rwsem);
अटल पूर्णांक torture_rwsem_करोwn_ग_लिखो(पूर्णांक tid __maybe_unused)
__acquires(torture_rwsem)
अणु
	करोwn_ग_लिखो(&torture_rwsem);
	वापस 0;
पूर्ण

अटल व्योम torture_rwsem_ग_लिखो_delay(काष्ठा torture_अक्रमom_state *trsp)
अणु
	स्थिर अचिन्हित दीर्घ दीर्घdelay_ms = 100;

	/* We want a दीर्घ delay occasionally to क्रमce massive contention.  */
	अगर (!(torture_अक्रमom(trsp) %
	      (cxt.nrealग_लिखोrs_stress * 2000 * दीर्घdelay_ms)))
		mdelay(दीर्घdelay_ms * 10);
	अन्यथा
		mdelay(दीर्घdelay_ms / 10);
	अगर (!(torture_अक्रमom(trsp) % (cxt.nrealग_लिखोrs_stress * 20000)))
		torture_preempt_schedule();  /* Allow test to be preempted. */
पूर्ण

अटल व्योम torture_rwsem_up_ग_लिखो(पूर्णांक tid __maybe_unused)
__releases(torture_rwsem)
अणु
	up_ग_लिखो(&torture_rwsem);
पूर्ण

अटल पूर्णांक torture_rwsem_करोwn_पढ़ो(पूर्णांक tid __maybe_unused)
__acquires(torture_rwsem)
अणु
	करोwn_पढ़ो(&torture_rwsem);
	वापस 0;
पूर्ण

अटल व्योम torture_rwsem_पढ़ो_delay(काष्ठा torture_अक्रमom_state *trsp)
अणु
	स्थिर अचिन्हित दीर्घ दीर्घdelay_ms = 100;

	/* We want a दीर्घ delay occasionally to क्रमce massive contention.  */
	अगर (!(torture_अक्रमom(trsp) %
	      (cxt.nrealपढ़ोers_stress * 2000 * दीर्घdelay_ms)))
		mdelay(दीर्घdelay_ms * 2);
	अन्यथा
		mdelay(दीर्घdelay_ms / 2);
	अगर (!(torture_अक्रमom(trsp) % (cxt.nrealपढ़ोers_stress * 20000)))
		torture_preempt_schedule();  /* Allow test to be preempted. */
पूर्ण

अटल व्योम torture_rwsem_up_पढ़ो(पूर्णांक tid __maybe_unused)
__releases(torture_rwsem)
अणु
	up_पढ़ो(&torture_rwsem);
पूर्ण

अटल काष्ठा lock_torture_ops rwsem_lock_ops = अणु
	.ग_लिखोlock	= torture_rwsem_करोwn_ग_लिखो,
	.ग_लिखो_delay	= torture_rwsem_ग_लिखो_delay,
	.task_boost     = torture_boost_dummy,
	.ग_लिखोunlock	= torture_rwsem_up_ग_लिखो,
	.पढ़ोlock       = torture_rwsem_करोwn_पढ़ो,
	.पढ़ो_delay     = torture_rwsem_पढ़ो_delay,
	.पढ़ोunlock     = torture_rwsem_up_पढ़ो,
	.name		= "rwsem_lock"
पूर्ण;

#समावेश <linux/percpu-rwsem.h>
अटल काष्ठा percpu_rw_semaphore pcpu_rwsem;

अटल व्योम torture_percpu_rwsem_init(व्योम)
अणु
	BUG_ON(percpu_init_rwsem(&pcpu_rwsem));
पूर्ण

अटल व्योम torture_percpu_rwsem_निकास(व्योम)
अणु
	percpu_मुक्त_rwsem(&pcpu_rwsem);
पूर्ण

अटल पूर्णांक torture_percpu_rwsem_करोwn_ग_लिखो(पूर्णांक tid __maybe_unused)
__acquires(pcpu_rwsem)
अणु
	percpu_करोwn_ग_लिखो(&pcpu_rwsem);
	वापस 0;
पूर्ण

अटल व्योम torture_percpu_rwsem_up_ग_लिखो(पूर्णांक tid __maybe_unused)
__releases(pcpu_rwsem)
अणु
	percpu_up_ग_लिखो(&pcpu_rwsem);
पूर्ण

अटल पूर्णांक torture_percpu_rwsem_करोwn_पढ़ो(पूर्णांक tid __maybe_unused)
__acquires(pcpu_rwsem)
अणु
	percpu_करोwn_पढ़ो(&pcpu_rwsem);
	वापस 0;
पूर्ण

अटल व्योम torture_percpu_rwsem_up_पढ़ो(पूर्णांक tid __maybe_unused)
__releases(pcpu_rwsem)
अणु
	percpu_up_पढ़ो(&pcpu_rwsem);
पूर्ण

अटल काष्ठा lock_torture_ops percpu_rwsem_lock_ops = अणु
	.init		= torture_percpu_rwsem_init,
	.निकास		= torture_percpu_rwsem_निकास,
	.ग_लिखोlock	= torture_percpu_rwsem_करोwn_ग_लिखो,
	.ग_लिखो_delay	= torture_rwsem_ग_लिखो_delay,
	.task_boost     = torture_boost_dummy,
	.ग_लिखोunlock	= torture_percpu_rwsem_up_ग_लिखो,
	.पढ़ोlock       = torture_percpu_rwsem_करोwn_पढ़ो,
	.पढ़ो_delay     = torture_rwsem_पढ़ो_delay,
	.पढ़ोunlock     = torture_percpu_rwsem_up_पढ़ो,
	.name		= "percpu_rwsem_lock"
पूर्ण;

/*
 * Lock torture ग_लिखोr kthपढ़ो.  Repeatedly acquires and releases
 * the lock, checking क्रम duplicate acquisitions.
 */
अटल पूर्णांक lock_torture_ग_लिखोr(व्योम *arg)
अणु
	काष्ठा lock_stress_stats *lwsp = arg;
	पूर्णांक tid = lwsp - cxt.lwsa;
	DEFINE_TORTURE_RANDOM(अक्रम);

	VERBOSE_TOROUT_STRING("lock_torture_writer task started");
	set_user_nice(current, MAX_NICE);

	करो अणु
		अगर ((torture_अक्रमom(&अक्रम) & 0xfffff) == 0)
			schedule_समयout_unपूर्णांकerruptible(1);

		cxt.cur_ops->task_boost(&अक्रम);
		cxt.cur_ops->ग_लिखोlock(tid);
		अगर (WARN_ON_ONCE(lock_is_ग_लिखो_held))
			lwsp->n_lock_fail++;
		lock_is_ग_लिखो_held = true;
		अगर (WARN_ON_ONCE(lock_is_पढ़ो_held))
			lwsp->n_lock_fail++; /* rare, but... */

		lwsp->n_lock_acquired++;
		cxt.cur_ops->ग_लिखो_delay(&अक्रम);
		lock_is_ग_लिखो_held = false;
		WRITE_ONCE(last_lock_release, jअगरfies);
		cxt.cur_ops->ग_लिखोunlock(tid);

		stutter_रुको("lock_torture_writer");
	पूर्ण जबतक (!torture_must_stop());

	cxt.cur_ops->task_boost(शून्य); /* reset prio */
	torture_kthपढ़ो_stopping("lock_torture_writer");
	वापस 0;
पूर्ण

/*
 * Lock torture पढ़ोer kthपढ़ो.  Repeatedly acquires and releases
 * the पढ़ोer lock.
 */
अटल पूर्णांक lock_torture_पढ़ोer(व्योम *arg)
अणु
	काष्ठा lock_stress_stats *lrsp = arg;
	पूर्णांक tid = lrsp - cxt.lrsa;
	DEFINE_TORTURE_RANDOM(अक्रम);

	VERBOSE_TOROUT_STRING("lock_torture_reader task started");
	set_user_nice(current, MAX_NICE);

	करो अणु
		अगर ((torture_अक्रमom(&अक्रम) & 0xfffff) == 0)
			schedule_समयout_unपूर्णांकerruptible(1);

		cxt.cur_ops->पढ़ोlock(tid);
		lock_is_पढ़ो_held = true;
		अगर (WARN_ON_ONCE(lock_is_ग_लिखो_held))
			lrsp->n_lock_fail++; /* rare, but... */

		lrsp->n_lock_acquired++;
		cxt.cur_ops->पढ़ो_delay(&अक्रम);
		lock_is_पढ़ो_held = false;
		cxt.cur_ops->पढ़ोunlock(tid);

		stutter_रुको("lock_torture_reader");
	पूर्ण जबतक (!torture_must_stop());
	torture_kthपढ़ो_stopping("lock_torture_reader");
	वापस 0;
पूर्ण

/*
 * Create an lock-torture-statistics message in the specअगरied buffer.
 */
अटल व्योम __torture_prपूर्णांक_stats(अक्षर *page,
				  काष्ठा lock_stress_stats *statp, bool ग_लिखो)
अणु
	bool fail = false;
	पूर्णांक i, n_stress;
	दीर्घ max = 0, min = statp ? statp[0].n_lock_acquired : 0;
	दीर्घ दीर्घ sum = 0;

	n_stress = ग_लिखो ? cxt.nrealग_लिखोrs_stress : cxt.nrealपढ़ोers_stress;
	क्रम (i = 0; i < n_stress; i++) अणु
		अगर (statp[i].n_lock_fail)
			fail = true;
		sum += statp[i].n_lock_acquired;
		अगर (max < statp[i].n_lock_acquired)
			max = statp[i].n_lock_acquired;
		अगर (min > statp[i].n_lock_acquired)
			min = statp[i].n_lock_acquired;
	पूर्ण
	page += प्र_लिखो(page,
			"%s:  Total: %lld  Max/Min: %ld/%ld %s  Fail: %d %s\n",
			ग_लिखो ? "Writes" : "Reads ",
			sum, max, min,
			!onoff_पूर्णांकerval && max / 2 > min ? "???" : "",
			fail, fail ? "!!!" : "");
	अगर (fail)
		atomic_inc(&cxt.n_lock_torture_errors);
पूर्ण

/*
 * Prपूर्णांक torture statistics.  Caller must ensure that there is only one
 * call to this function at a given समय!!!  This is normally accomplished
 * by relying on the module प्रणाली to only have one copy of the module
 * loaded, and then by giving the lock_torture_stats kthपढ़ो full control
 * (or the init/cleanup functions when lock_torture_stats thपढ़ो is not
 * running).
 */
अटल व्योम lock_torture_stats_prपूर्णांक(व्योम)
अणु
	पूर्णांक size = cxt.nrealग_लिखोrs_stress * 200 + 8192;
	अक्षर *buf;

	अगर (cxt.cur_ops->पढ़ोlock)
		size += cxt.nrealपढ़ोers_stress * 200 + 8192;

	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buf) अणु
		pr_err("lock_torture_stats_print: Out of memory, need: %d",
		       size);
		वापस;
	पूर्ण

	__torture_prपूर्णांक_stats(buf, cxt.lwsa, true);
	pr_alert("%s", buf);
	kमुक्त(buf);

	अगर (cxt.cur_ops->पढ़ोlock) अणु
		buf = kदो_स्मृति(size, GFP_KERNEL);
		अगर (!buf) अणु
			pr_err("lock_torture_stats_print: Out of memory, need: %d",
			       size);
			वापस;
		पूर्ण

		__torture_prपूर्णांक_stats(buf, cxt.lrsa, false);
		pr_alert("%s", buf);
		kमुक्त(buf);
	पूर्ण
पूर्ण

/*
 * Periodically prपूर्णांकs torture statistics, अगर periodic statistics prपूर्णांकing
 * was specअगरied via the stat_पूर्णांकerval module parameter.
 *
 * No need to worry about fullstop here, since this one करोesn't reference
 * अस्थिर state or रेजिस्टर callbacks.
 */
अटल पूर्णांक lock_torture_stats(व्योम *arg)
अणु
	VERBOSE_TOROUT_STRING("lock_torture_stats task started");
	करो अणु
		schedule_समयout_पूर्णांकerruptible(stat_पूर्णांकerval * HZ);
		lock_torture_stats_prपूर्णांक();
		torture_shutकरोwn_असलorb("lock_torture_stats");
	पूर्ण जबतक (!torture_must_stop());
	torture_kthपढ़ो_stopping("lock_torture_stats");
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
lock_torture_prपूर्णांक_module_parms(काष्ठा lock_torture_ops *cur_ops,
				स्थिर अक्षर *tag)
अणु
	pr_alert("%s" TORTURE_FLAG
		 "--- %s%s: nwriters_stress=%d nreaders_stress=%d stat_interval=%d verbose=%d shuffle_interval=%d stutter=%d shutdown_secs=%d onoff_interval=%d onoff_holdoff=%d\n",
		 torture_type, tag, cxt.debug_lock ? " [debug]": "",
		 cxt.nrealग_लिखोrs_stress, cxt.nrealपढ़ोers_stress, stat_पूर्णांकerval,
		 verbose, shuffle_पूर्णांकerval, stutter, shutकरोwn_secs,
		 onoff_पूर्णांकerval, onoff_holकरोff);
पूर्ण

अटल व्योम lock_torture_cleanup(व्योम)
अणु
	पूर्णांक i;

	अगर (torture_cleanup_begin())
		वापस;

	/*
	 * Indicates early cleanup, meaning that the test has not run,
	 * such as when passing bogus args when loading the module.
	 * However cxt->cur_ops.init() may have been invoked, so beside
	 * perक्रमm the underlying torture-specअगरic cleanups, cur_ops.निकास()
	 * will be invoked अगर needed.
	 */
	अगर (!cxt.lwsa && !cxt.lrsa)
		जाओ end;

	अगर (ग_लिखोr_tasks) अणु
		क्रम (i = 0; i < cxt.nrealग_लिखोrs_stress; i++)
			torture_stop_kthपढ़ो(lock_torture_ग_लिखोr,
					     ग_लिखोr_tasks[i]);
		kमुक्त(ग_लिखोr_tasks);
		ग_लिखोr_tasks = शून्य;
	पूर्ण

	अगर (पढ़ोer_tasks) अणु
		क्रम (i = 0; i < cxt.nrealपढ़ोers_stress; i++)
			torture_stop_kthपढ़ो(lock_torture_पढ़ोer,
					     पढ़ोer_tasks[i]);
		kमुक्त(पढ़ोer_tasks);
		पढ़ोer_tasks = शून्य;
	पूर्ण

	torture_stop_kthपढ़ो(lock_torture_stats, stats_task);
	lock_torture_stats_prपूर्णांक();  /* -After- the stats thपढ़ो is stopped! */

	अगर (atomic_पढ़ो(&cxt.n_lock_torture_errors))
		lock_torture_prपूर्णांक_module_parms(cxt.cur_ops,
						"End of test: FAILURE");
	अन्यथा अगर (torture_onoff_failures())
		lock_torture_prपूर्णांक_module_parms(cxt.cur_ops,
						"End of test: LOCK_HOTPLUG");
	अन्यथा
		lock_torture_prपूर्णांक_module_parms(cxt.cur_ops,
						"End of test: SUCCESS");

	kमुक्त(cxt.lwsa);
	cxt.lwsa = शून्य;
	kमुक्त(cxt.lrsa);
	cxt.lrsa = शून्य;

end:
	अगर (cxt.init_called) अणु
		अगर (cxt.cur_ops->निकास)
			cxt.cur_ops->निकास();
		cxt.init_called = false;
	पूर्ण
	torture_cleanup_end();
पूर्ण

अटल पूर्णांक __init lock_torture_init(व्योम)
अणु
	पूर्णांक i, j;
	पूर्णांक firsterr = 0;
	अटल काष्ठा lock_torture_ops *torture_ops[] = अणु
		&lock_busted_ops,
		&spin_lock_ops, &spin_lock_irq_ops,
		&rw_lock_ops, &rw_lock_irq_ops,
		&mutex_lock_ops,
		&ww_mutex_lock_ops,
#अगर_घोषित CONFIG_RT_MUTEXES
		&rपंचांगutex_lock_ops,
#पूर्ण_अगर
		&rwsem_lock_ops,
		&percpu_rwsem_lock_ops,
	पूर्ण;

	अगर (!torture_init_begin(torture_type, verbose))
		वापस -EBUSY;

	/* Process args and tell the world that the torturer is on the job. */
	क्रम (i = 0; i < ARRAY_SIZE(torture_ops); i++) अणु
		cxt.cur_ops = torture_ops[i];
		अगर (म_भेद(torture_type, cxt.cur_ops->name) == 0)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(torture_ops)) अणु
		pr_alert("lock-torture: invalid torture type: \"%s\"\n",
			 torture_type);
		pr_alert("lock-torture types:");
		क्रम (i = 0; i < ARRAY_SIZE(torture_ops); i++)
			pr_alert(" %s", torture_ops[i]->name);
		pr_alert("\n");
		firsterr = -EINVAL;
		जाओ unwind;
	पूर्ण

	अगर (nग_लिखोrs_stress == 0 &&
	    (!cxt.cur_ops->पढ़ोlock || nपढ़ोers_stress == 0)) अणु
		pr_alert("lock-torture: must run at least one locking thread\n");
		firsterr = -EINVAL;
		जाओ unwind;
	पूर्ण

	अगर (nग_लिखोrs_stress >= 0)
		cxt.nrealग_लिखोrs_stress = nग_लिखोrs_stress;
	अन्यथा
		cxt.nrealग_लिखोrs_stress = 2 * num_online_cpus();

	अगर (cxt.cur_ops->init) अणु
		cxt.cur_ops->init();
		cxt.init_called = true;
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_MUTEXES
	अगर (str_has_prefix(torture_type, "mutex"))
		cxt.debug_lock = true;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_RT_MUTEXES
	अगर (str_has_prefix(torture_type, "rtmutex"))
		cxt.debug_lock = true;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_SPINLOCK
	अगर ((str_has_prefix(torture_type, "spin")) ||
	    (str_has_prefix(torture_type, "rw_lock")))
		cxt.debug_lock = true;
#पूर्ण_अगर

	/* Initialize the statistics so that each run माला_लो its own numbers. */
	अगर (nग_लिखोrs_stress) अणु
		lock_is_ग_लिखो_held = false;
		cxt.lwsa = kदो_स्मृति_array(cxt.nrealग_लिखोrs_stress,
					 माप(*cxt.lwsa),
					 GFP_KERNEL);
		अगर (cxt.lwsa == शून्य) अणु
			VERBOSE_TOROUT_STRING("cxt.lwsa: Out of memory");
			firsterr = -ENOMEM;
			जाओ unwind;
		पूर्ण

		क्रम (i = 0; i < cxt.nrealग_लिखोrs_stress; i++) अणु
			cxt.lwsa[i].n_lock_fail = 0;
			cxt.lwsa[i].n_lock_acquired = 0;
		पूर्ण
	पूर्ण

	अगर (cxt.cur_ops->पढ़ोlock) अणु
		अगर (nपढ़ोers_stress >= 0)
			cxt.nrealपढ़ोers_stress = nपढ़ोers_stress;
		अन्यथा अणु
			/*
			 * By शेष distribute evenly the number of
			 * पढ़ोers and ग_लिखोrs. We still run the same number
			 * of thपढ़ोs as the ग_लिखोr-only locks शेष.
			 */
			अगर (nग_लिखोrs_stress < 0) /* user करोesn't care */
				cxt.nrealग_लिखोrs_stress = num_online_cpus();
			cxt.nrealपढ़ोers_stress = cxt.nrealग_लिखोrs_stress;
		पूर्ण

		अगर (nपढ़ोers_stress) अणु
			lock_is_पढ़ो_held = false;
			cxt.lrsa = kदो_स्मृति_array(cxt.nrealपढ़ोers_stress,
						 माप(*cxt.lrsa),
						 GFP_KERNEL);
			अगर (cxt.lrsa == शून्य) अणु
				VERBOSE_TOROUT_STRING("cxt.lrsa: Out of memory");
				firsterr = -ENOMEM;
				kमुक्त(cxt.lwsa);
				cxt.lwsa = शून्य;
				जाओ unwind;
			पूर्ण

			क्रम (i = 0; i < cxt.nrealपढ़ोers_stress; i++) अणु
				cxt.lrsa[i].n_lock_fail = 0;
				cxt.lrsa[i].n_lock_acquired = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	lock_torture_prपूर्णांक_module_parms(cxt.cur_ops, "Start of test");

	/* Prepare torture context. */
	अगर (onoff_पूर्णांकerval > 0) अणु
		firsterr = torture_onoff_init(onoff_holकरोff * HZ,
					      onoff_पूर्णांकerval * HZ, शून्य);
		अगर (firsterr)
			जाओ unwind;
	पूर्ण
	अगर (shuffle_पूर्णांकerval > 0) अणु
		firsterr = torture_shuffle_init(shuffle_पूर्णांकerval);
		अगर (firsterr)
			जाओ unwind;
	पूर्ण
	अगर (shutकरोwn_secs > 0) अणु
		firsterr = torture_shutकरोwn_init(shutकरोwn_secs,
						 lock_torture_cleanup);
		अगर (firsterr)
			जाओ unwind;
	पूर्ण
	अगर (stutter > 0) अणु
		firsterr = torture_stutter_init(stutter, stutter);
		अगर (firsterr)
			जाओ unwind;
	पूर्ण

	अगर (nग_लिखोrs_stress) अणु
		ग_लिखोr_tasks = kसुस्मृति(cxt.nrealग_लिखोrs_stress,
				       माप(ग_लिखोr_tasks[0]),
				       GFP_KERNEL);
		अगर (ग_लिखोr_tasks == शून्य) अणु
			VERBOSE_TOROUT_ERRSTRING("writer_tasks: Out of memory");
			firsterr = -ENOMEM;
			जाओ unwind;
		पूर्ण
	पूर्ण

	अगर (cxt.cur_ops->पढ़ोlock) अणु
		पढ़ोer_tasks = kसुस्मृति(cxt.nrealपढ़ोers_stress,
				       माप(पढ़ोer_tasks[0]),
				       GFP_KERNEL);
		अगर (पढ़ोer_tasks == शून्य) अणु
			VERBOSE_TOROUT_ERRSTRING("reader_tasks: Out of memory");
			kमुक्त(ग_लिखोr_tasks);
			ग_लिखोr_tasks = शून्य;
			firsterr = -ENOMEM;
			जाओ unwind;
		पूर्ण
	पूर्ण

	/*
	 * Create the kthपढ़ोs and start torturing (oh, those poor little locks).
	 *
	 * TODO: Note that we पूर्णांकerleave ग_लिखोrs with पढ़ोers, giving ग_लिखोrs a
	 * slight advantage, by creating its kthपढ़ो first. This can be modअगरied
	 * क्रम very specअगरic needs, or even let the user choose the policy, अगर
	 * ever wanted.
	 */
	क्रम (i = 0, j = 0; i < cxt.nrealग_लिखोrs_stress ||
		    j < cxt.nrealपढ़ोers_stress; i++, j++) अणु
		अगर (i >= cxt.nrealग_लिखोrs_stress)
			जाओ create_पढ़ोer;

		/* Create ग_लिखोr. */
		firsterr = torture_create_kthपढ़ो(lock_torture_ग_लिखोr, &cxt.lwsa[i],
						  ग_लिखोr_tasks[i]);
		अगर (firsterr)
			जाओ unwind;

	create_पढ़ोer:
		अगर (cxt.cur_ops->पढ़ोlock == शून्य || (j >= cxt.nrealपढ़ोers_stress))
			जारी;
		/* Create पढ़ोer. */
		firsterr = torture_create_kthपढ़ो(lock_torture_पढ़ोer, &cxt.lrsa[j],
						  पढ़ोer_tasks[j]);
		अगर (firsterr)
			जाओ unwind;
	पूर्ण
	अगर (stat_पूर्णांकerval > 0) अणु
		firsterr = torture_create_kthपढ़ो(lock_torture_stats, शून्य,
						  stats_task);
		अगर (firsterr)
			जाओ unwind;
	पूर्ण
	torture_init_end();
	वापस 0;

unwind:
	torture_init_end();
	lock_torture_cleanup();
	अगर (shutकरोwn_secs) अणु
		WARN_ON(!IS_MODULE(CONFIG_LOCK_TORTURE_TEST));
		kernel_घातer_off();
	पूर्ण
	वापस firsterr;
पूर्ण

module_init(lock_torture_init);
module_निकास(lock_torture_cleanup);
