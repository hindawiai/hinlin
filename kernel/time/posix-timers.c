<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * 2002-10-15  Posix Clocks & समयrs
 *                           by George Anzinger george@mvista.com
 *			     Copyright (C) 2002 2003 by MontaVista Software.
 *
 * 2004-06-01  Fix CLOCK_REALTIME घड़ी/समयr TIMER_ABSTIME bug.
 *			     Copyright (C) 2004 Boris Hu
 *
 * These are all the functions necessary to implement POSIX घड़ीs & समयrs
 */
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/mutex.h>
#समावेश <linux/sched/task.h>

#समावेश <linux/uaccess.h>
#समावेश <linux/list.h>
#समावेश <linux/init.h>
#समावेश <linux/compiler.h>
#समावेश <linux/hash.h>
#समावेश <linux/posix-घड़ी.h>
#समावेश <linux/posix-समयrs.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/export.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/compat.h>
#समावेश <linux/nospec.h>
#समावेश <linux/समय_namespace.h>

#समावेश "timekeeping.h"
#समावेश "posix-timers.h"

/*
 * Management arrays क्रम POSIX समयrs. Timers are now kept in अटल hash table
 * with 512 entries.
 * Timer ids are allocated by local routine, which selects proper hash head by
 * key, स्थिरructed from current->संकेत address and per संकेत काष्ठा counter.
 * This keeps समयr ids unique per process, but now they can पूर्णांकersect between
 * processes.
 */

/*
 * Lets keep our समयrs in a slab cache :-)
 */
अटल काष्ठा kmem_cache *posix_समयrs_cache;

अटल DEFINE_HASHTABLE(posix_समयrs_hashtable, 9);
अटल DEFINE_SPINLOCK(hash_lock);

अटल स्थिर काष्ठा k_घड़ी * स्थिर posix_घड़ीs[];
अटल स्थिर काष्ठा k_घड़ी *घड़ीid_to_kघड़ी(स्थिर घड़ीid_t id);
अटल स्थिर काष्ठा k_घड़ी घड़ी_realसमय, घड़ी_monotonic;

/*
 * we assume that the new SIGEV_THREAD_ID shares no bits with the other
 * SIGEV values.  Here we put out an error अगर this assumption fails.
 */
#अगर SIGEV_THREAD_ID != (SIGEV_THREAD_ID & \
                       ~(SIGEV_SIGNAL | SIGEV_NONE | SIGEV_THREAD))
#त्रुटि "SIGEV_THREAD_ID must not share bit with other SIGEV values!"
#पूर्ण_अगर

/*
 * The समयr ID is turned पूर्णांकo a समयr address by idr_find().
 * Verअगरying a valid ID consists of:
 *
 * a) checking that idr_find() वापसs other than -1.
 * b) checking that the समयr id matches the one in the समयr itself.
 * c) that the समयr owner is in the callers thपढ़ो group.
 */

/*
 * CLOCKs: The POSIX standard calls क्रम a couple of घड़ीs and allows us
 *	    to implement others.  This काष्ठाure defines the various
 *	    घड़ीs.
 *
 * RESOLUTION: Clock resolution is used to round up समयr and पूर्णांकerval
 *	    बार, NOT to report घड़ी बार, which are reported with as
 *	    much resolution as the प्रणाली can muster.  In some हालs this
 *	    resolution may depend on the underlying घड़ी hardware and
 *	    may not be quantअगरiable until run समय, and only then is the
 *	    necessary code is written.	The standard says we should say
 *	    something about this issue in the करोcumentation...
 *
 * FUNCTIONS: The CLOCKs काष्ठाure defines possible functions to
 *	    handle various घड़ी functions.
 *
 *	    The standard POSIX समयr management code assumes the
 *	    following: 1.) The k_iसमयr काष्ठा (sched.h) is used क्रम
 *	    the समयr.  2.) The list, it_lock, it_घड़ी, it_id and
 *	    it_pid fields are not modअगरied by समयr code.
 *
 * Permissions: It is assumed that the घड़ी_समय_रखो() function defined
 *	    क्रम each घड़ी will take care of permission checks.	 Some
 *	    घड़ीs may be set able by any user (i.e. local process
 *	    घड़ीs) others not.	 Currently the only set able घड़ी we
 *	    have is CLOCK_REALTIME and its high res counter part, both of
 *	    which we beg off on and pass to करो_sys_समय_रखोofday().
 */
अटल काष्ठा k_iसमयr *__lock_समयr(समयr_t समयr_id, अचिन्हित दीर्घ *flags);

#घोषणा lock_समयr(tid, flags)						   \
(अणु	काष्ठा k_iसमयr *__timr;					   \
	__cond_lock(&__timr->it_lock, __timr = __lock_समयr(tid, flags));  \
	__timr;								   \
पूर्ण)

अटल पूर्णांक hash(काष्ठा संकेत_काष्ठा *sig, अचिन्हित पूर्णांक nr)
अणु
	वापस hash_32(hash32_ptr(sig) ^ nr, HASH_BITS(posix_समयrs_hashtable));
पूर्ण

अटल काष्ठा k_iसमयr *__posix_समयrs_find(काष्ठा hlist_head *head,
					    काष्ठा संकेत_काष्ठा *sig,
					    समयr_t id)
अणु
	काष्ठा k_iसमयr *समयr;

	hlist_क्रम_each_entry_rcu(समयr, head, t_hash,
				 lockdep_is_held(&hash_lock)) अणु
		अगर ((समयr->it_संकेत == sig) && (समयr->it_id == id))
			वापस समयr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा k_iसमयr *posix_समयr_by_id(समयr_t id)
अणु
	काष्ठा संकेत_काष्ठा *sig = current->संकेत;
	काष्ठा hlist_head *head = &posix_समयrs_hashtable[hash(sig, id)];

	वापस __posix_समयrs_find(head, sig, id);
पूर्ण

अटल पूर्णांक posix_समयr_add(काष्ठा k_iसमयr *समयr)
अणु
	काष्ठा संकेत_काष्ठा *sig = current->संकेत;
	पूर्णांक first_मुक्त_id = sig->posix_समयr_id;
	काष्ठा hlist_head *head;
	पूर्णांक ret = -ENOENT;

	करो अणु
		spin_lock(&hash_lock);
		head = &posix_समयrs_hashtable[hash(sig, sig->posix_समयr_id)];
		अगर (!__posix_समयrs_find(head, sig, sig->posix_समयr_id)) अणु
			hlist_add_head_rcu(&समयr->t_hash, head);
			ret = sig->posix_समयr_id;
		पूर्ण
		अगर (++sig->posix_समयr_id < 0)
			sig->posix_समयr_id = 0;
		अगर ((sig->posix_समयr_id == first_मुक्त_id) && (ret == -ENOENT))
			/* Loop over all possible ids completed */
			ret = -EAGAIN;
		spin_unlock(&hash_lock);
	पूर्ण जबतक (ret == -ENOENT);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम unlock_समयr(काष्ठा k_iसमयr *timr, अचिन्हित दीर्घ flags)
अणु
	spin_unlock_irqrestore(&timr->it_lock, flags);
पूर्ण

/* Get घड़ी_realसमय */
अटल पूर्णांक posix_get_realसमय_प्रकारimespec(घड़ीid_t which_घड़ी, काष्ठा बारpec64 *tp)
अणु
	kसमय_get_real_ts64(tp);
	वापस 0;
पूर्ण

अटल kसमय_प्रकार posix_get_realसमय_kसमय(घड़ीid_t which_घड़ी)
अणु
	वापस kसमय_get_real();
पूर्ण

/* Set घड़ी_realसमय */
अटल पूर्णांक posix_घड़ी_realसमय_set(स्थिर घड़ीid_t which_घड़ी,
				    स्थिर काष्ठा बारpec64 *tp)
अणु
	वापस करो_sys_समय_रखोofday64(tp, शून्य);
पूर्ण

अटल पूर्णांक posix_घड़ी_realसमय_adj(स्थिर घड़ीid_t which_घड़ी,
				    काष्ठा __kernel_समयx *t)
अणु
	वापस करो_adjसमयx(t);
पूर्ण

/*
 * Get monotonic समय क्रम posix समयrs
 */
अटल पूर्णांक posix_get_monotonic_बारpec(घड़ीid_t which_घड़ी, काष्ठा बारpec64 *tp)
अणु
	kसमय_get_ts64(tp);
	समयns_add_monotonic(tp);
	वापस 0;
पूर्ण

अटल kसमय_प्रकार posix_get_monotonic_kसमय(घड़ीid_t which_घड़ी)
अणु
	वापस kसमय_get();
पूर्ण

/*
 * Get monotonic-raw समय क्रम posix समयrs
 */
अटल पूर्णांक posix_get_monotonic_raw(घड़ीid_t which_घड़ी, काष्ठा बारpec64 *tp)
अणु
	kसमय_get_raw_ts64(tp);
	समयns_add_monotonic(tp);
	वापस 0;
पूर्ण


अटल पूर्णांक posix_get_realसमय_coarse(घड़ीid_t which_घड़ी, काष्ठा बारpec64 *tp)
अणु
	kसमय_get_coarse_real_ts64(tp);
	वापस 0;
पूर्ण

अटल पूर्णांक posix_get_monotonic_coarse(घड़ीid_t which_घड़ी,
						काष्ठा बारpec64 *tp)
अणु
	kसमय_get_coarse_ts64(tp);
	समयns_add_monotonic(tp);
	वापस 0;
पूर्ण

अटल पूर्णांक posix_get_coarse_res(स्थिर घड़ीid_t which_घड़ी, काष्ठा बारpec64 *tp)
अणु
	*tp = kसमय_प्रकारo_बारpec64(KTIME_LOW_RES);
	वापस 0;
पूर्ण

अटल पूर्णांक posix_get_bootसमय_प्रकारimespec(स्थिर घड़ीid_t which_घड़ी, काष्ठा बारpec64 *tp)
अणु
	kसमय_get_bootसमय_प्रकारs64(tp);
	समयns_add_bootसमय(tp);
	वापस 0;
पूर्ण

अटल kसमय_प्रकार posix_get_bootसमय_kसमय(स्थिर घड़ीid_t which_घड़ी)
अणु
	वापस kसमय_get_bootसमय();
पूर्ण

अटल पूर्णांक posix_get_tai_बारpec(घड़ीid_t which_घड़ी, काष्ठा बारpec64 *tp)
अणु
	kसमय_get_घड़ीtai_ts64(tp);
	वापस 0;
पूर्ण

अटल kसमय_प्रकार posix_get_tai_kसमय(घड़ीid_t which_घड़ी)
अणु
	वापस kसमय_get_घड़ीtai();
पूर्ण

अटल पूर्णांक posix_get_hrसमयr_res(घड़ीid_t which_घड़ी, काष्ठा बारpec64 *tp)
अणु
	tp->tv_sec = 0;
	tp->tv_nsec = hrसमयr_resolution;
	वापस 0;
पूर्ण

/*
 * Initialize everything, well, just everything in Posix घड़ीs/समयrs ;)
 */
अटल __init पूर्णांक init_posix_समयrs(व्योम)
अणु
	posix_समयrs_cache = kmem_cache_create("posix_timers_cache",
					माप (काष्ठा k_iसमयr), 0, SLAB_PANIC,
					शून्य);
	वापस 0;
पूर्ण
__initcall(init_posix_समयrs);

/*
 * The siginfo si_overrun field and the वापस value of समयr_getoverrun(2)
 * are of type पूर्णांक. Clamp the overrun value to पूर्णांक_उच्च
 */
अटल अंतरभूत पूर्णांक समयr_overrun_to_पूर्णांक(काष्ठा k_iसमयr *timr, पूर्णांक baseval)
अणु
	s64 sum = timr->it_overrun_last + (s64)baseval;

	वापस sum > (s64)पूर्णांक_उच्च ? पूर्णांक_उच्च : (पूर्णांक)sum;
पूर्ण

अटल व्योम common_hrसमयr_rearm(काष्ठा k_iसमयr *timr)
अणु
	काष्ठा hrसमयr *समयr = &timr->it.real.समयr;

	timr->it_overrun += hrसमयr_क्रमward(समयr, समयr->base->get_समय(),
					    timr->it_पूर्णांकerval);
	hrसमयr_restart(समयr);
पूर्ण

/*
 * This function is exported क्रम use by the संकेत deliver code.  It is
 * called just prior to the info block being released and passes that
 * block to us.  It's function is to update the overrun entry AND to
 * restart the समयr.  It should only be called अगर the समयr is to be
 * restarted (i.e. we have flagged this in the sys_निजी entry of the
 * info block).
 *
 * To protect against the समयr going away जबतक the पूर्णांकerrupt is queued,
 * we require that the it_requeue_pending flag be set.
 */
व्योम posixसमयr_rearm(काष्ठा kernel_siginfo *info)
अणु
	काष्ठा k_iसमयr *timr;
	अचिन्हित दीर्घ flags;

	timr = lock_समयr(info->si_tid, &flags);
	अगर (!timr)
		वापस;

	अगर (timr->it_पूर्णांकerval && timr->it_requeue_pending == info->si_sys_निजी) अणु
		timr->kघड़ी->समयr_rearm(timr);

		timr->it_active = 1;
		timr->it_overrun_last = timr->it_overrun;
		timr->it_overrun = -1LL;
		++timr->it_requeue_pending;

		info->si_overrun = समयr_overrun_to_पूर्णांक(timr, info->si_overrun);
	पूर्ण

	unlock_समयr(timr, flags);
पूर्ण

पूर्णांक posix_समयr_event(काष्ठा k_iसमयr *timr, पूर्णांक si_निजी)
अणु
	क्रमागत pid_type type;
	पूर्णांक ret = -1;
	/*
	 * FIXME: अगर ->sigq is queued we can race with
	 * dequeue_संकेत()->posixसमयr_rearm().
	 *
	 * If dequeue_संकेत() sees the "right" value of
	 * si_sys_निजी it calls posixसमयr_rearm().
	 * We re-queue ->sigq and drop ->it_lock().
	 * posixसमयr_rearm() locks the समयr
	 * and re-schedules it जबतक ->sigq is pending.
	 * Not really bad, but not that we want.
	 */
	timr->sigq->info.si_sys_निजी = si_निजी;

	type = !(timr->it_sigev_notअगरy & SIGEV_THREAD_ID) ? PIDTYPE_TGID : PIDTYPE_PID;
	ret = send_sigqueue(timr->sigq, timr->it_pid, type);
	/* If we failed to send the संकेत the समयr stops. */
	वापस ret > 0;
पूर्ण

/*
 * This function माला_लो called when a POSIX.1b पूर्णांकerval समयr expires.  It
 * is used as a callback from the kernel पूर्णांकernal समयr.  The
 * run_समयr_list code ALWAYS calls with पूर्णांकerrupts on.

 * This code is क्रम CLOCK_REALTIME* and CLOCK_MONOTONIC* समयrs.
 */
अटल क्रमागत hrसमयr_restart posix_समयr_fn(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा k_iसमयr *timr;
	अचिन्हित दीर्घ flags;
	पूर्णांक si_निजी = 0;
	क्रमागत hrसमयr_restart ret = HRTIMER_NORESTART;

	timr = container_of(समयr, काष्ठा k_iसमयr, it.real.समयr);
	spin_lock_irqsave(&timr->it_lock, flags);

	timr->it_active = 0;
	अगर (timr->it_पूर्णांकerval != 0)
		si_निजी = ++timr->it_requeue_pending;

	अगर (posix_समयr_event(timr, si_निजी)) अणु
		/*
		 * संकेत was not sent because of sig_ignor
		 * we will not get a call back to restart it AND
		 * it should be restarted.
		 */
		अगर (timr->it_पूर्णांकerval != 0) अणु
			kसमय_प्रकार now = hrसमयr_cb_get_समय(समयr);

			/*
			 * FIXME: What we really want, is to stop this
			 * समयr completely and restart it in हाल the
			 * संक_छोड़ो is हटाओd. This is a non trivial
			 * change which involves sighand locking
			 * (sigh !), which we करोn't want to करो late in
			 * the release cycle.
			 *
			 * For now we just let समयrs with an पूर्णांकerval
			 * less than a jअगरfie expire every jअगरfie to
			 * aव्योम softirq starvation in हाल of संक_छोड़ो
			 * and a very small पूर्णांकerval, which would put
			 * the समयr right back on the softirq pending
			 * list. By moving now ahead of समय we trick
			 * hrसमयr_क्रमward() to expire the समयr
			 * later, जबतक we still मुख्यtain the overrun
			 * accuracy, but have some inconsistency in
			 * the समयr_समय_लो() हाल. This is at least
			 * better than a starved softirq. A more
			 * complex fix which solves also another related
			 * inconsistency is alपढ़ोy in the pipeline.
			 */
#अगर_घोषित CONFIG_HIGH_RES_TIMERS
			अणु
				kसमय_प्रकार kj = NSEC_PER_SEC / HZ;

				अगर (timr->it_पूर्णांकerval < kj)
					now = kसमय_add(now, kj);
			पूर्ण
#पूर्ण_अगर
			timr->it_overrun += hrसमयr_क्रमward(समयr, now,
							    timr->it_पूर्णांकerval);
			ret = HRTIMER_RESTART;
			++timr->it_requeue_pending;
			timr->it_active = 1;
		पूर्ण
	पूर्ण

	unlock_समयr(timr, flags);
	वापस ret;
पूर्ण

अटल काष्ठा pid *good_sigevent(sigevent_t * event)
अणु
	काष्ठा pid *pid = task_tgid(current);
	काष्ठा task_काष्ठा *rtn;

	चयन (event->sigev_notअगरy) अणु
	हाल SIGEV_SIGNAL | SIGEV_THREAD_ID:
		pid = find_vpid(event->sigev_notअगरy_thपढ़ो_id);
		rtn = pid_task(pid, PIDTYPE_PID);
		अगर (!rtn || !same_thपढ़ो_group(rtn, current))
			वापस शून्य;
		fallthrough;
	हाल SIGEV_SIGNAL:
	हाल SIGEV_THREAD:
		अगर (event->sigev_signo <= 0 || event->sigev_signo > SIGRTMAX)
			वापस शून्य;
		fallthrough;
	हाल SIGEV_NONE:
		वापस pid;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा k_iसमयr * alloc_posix_समयr(व्योम)
अणु
	काष्ठा k_iसमयr *पंचांगr;
	पंचांगr = kmem_cache_zalloc(posix_समयrs_cache, GFP_KERNEL);
	अगर (!पंचांगr)
		वापस पंचांगr;
	अगर (unlikely(!(पंचांगr->sigq = sigqueue_alloc()))) अणु
		kmem_cache_मुक्त(posix_समयrs_cache, पंचांगr);
		वापस शून्य;
	पूर्ण
	clear_siginfo(&पंचांगr->sigq->info);
	वापस पंचांगr;
पूर्ण

अटल व्योम k_iसमयr_rcu_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा k_iसमयr *पंचांगr = container_of(head, काष्ठा k_iसमयr, rcu);

	kmem_cache_मुक्त(posix_समयrs_cache, पंचांगr);
पूर्ण

#घोषणा IT_ID_SET	1
#घोषणा IT_ID_NOT_SET	0
अटल व्योम release_posix_समयr(काष्ठा k_iसमयr *पंचांगr, पूर्णांक it_id_set)
अणु
	अगर (it_id_set) अणु
		अचिन्हित दीर्घ flags;
		spin_lock_irqsave(&hash_lock, flags);
		hlist_del_rcu(&पंचांगr->t_hash);
		spin_unlock_irqrestore(&hash_lock, flags);
	पूर्ण
	put_pid(पंचांगr->it_pid);
	sigqueue_मुक्त(पंचांगr->sigq);
	call_rcu(&पंचांगr->rcu, k_iसमयr_rcu_मुक्त);
पूर्ण

अटल पूर्णांक common_समयr_create(काष्ठा k_iसमयr *new_समयr)
अणु
	hrसमयr_init(&new_समयr->it.real.समयr, new_समयr->it_घड़ी, 0);
	वापस 0;
पूर्ण

/* Create a POSIX.1b पूर्णांकerval समयr. */
अटल पूर्णांक करो_समयr_create(घड़ीid_t which_घड़ी, काष्ठा sigevent *event,
			   समयr_t __user *created_समयr_id)
अणु
	स्थिर काष्ठा k_घड़ी *kc = घड़ीid_to_kघड़ी(which_घड़ी);
	काष्ठा k_iसमयr *new_समयr;
	पूर्णांक error, new_समयr_id;
	पूर्णांक it_id_set = IT_ID_NOT_SET;

	अगर (!kc)
		वापस -EINVAL;
	अगर (!kc->समयr_create)
		वापस -EOPNOTSUPP;

	new_समयr = alloc_posix_समयr();
	अगर (unlikely(!new_समयr))
		वापस -EAGAIN;

	spin_lock_init(&new_समयr->it_lock);
	new_समयr_id = posix_समयr_add(new_समयr);
	अगर (new_समयr_id < 0) अणु
		error = new_समयr_id;
		जाओ out;
	पूर्ण

	it_id_set = IT_ID_SET;
	new_समयr->it_id = (समयr_t) new_समयr_id;
	new_समयr->it_घड़ी = which_घड़ी;
	new_समयr->kघड़ी = kc;
	new_समयr->it_overrun = -1LL;

	अगर (event) अणु
		rcu_पढ़ो_lock();
		new_समयr->it_pid = get_pid(good_sigevent(event));
		rcu_पढ़ो_unlock();
		अगर (!new_समयr->it_pid) अणु
			error = -EINVAL;
			जाओ out;
		पूर्ण
		new_समयr->it_sigev_notअगरy     = event->sigev_notअगरy;
		new_समयr->sigq->info.si_signo = event->sigev_signo;
		new_समयr->sigq->info.si_value = event->sigev_value;
	पूर्ण अन्यथा अणु
		new_समयr->it_sigev_notअगरy     = SIGEV_SIGNAL;
		new_समयr->sigq->info.si_signo = SIGALRM;
		स_रखो(&new_समयr->sigq->info.si_value, 0, माप(sigval_t));
		new_समयr->sigq->info.si_value.sival_पूर्णांक = new_समयr->it_id;
		new_समयr->it_pid = get_pid(task_tgid(current));
	पूर्ण

	new_समयr->sigq->info.si_tid   = new_समयr->it_id;
	new_समयr->sigq->info.si_code  = SI_TIMER;

	अगर (copy_to_user(created_समयr_id,
			 &new_समयr_id, माप (new_समयr_id))) अणु
		error = -EFAULT;
		जाओ out;
	पूर्ण

	error = kc->समयr_create(new_समयr);
	अगर (error)
		जाओ out;

	spin_lock_irq(&current->sighand->siglock);
	new_समयr->it_संकेत = current->संकेत;
	list_add(&new_समयr->list, &current->संकेत->posix_समयrs);
	spin_unlock_irq(&current->sighand->siglock);

	वापस 0;
	/*
	 * In the हाल of the समयr beदीर्घing to another task, after
	 * the task is unlocked, the समयr is owned by the other task
	 * and may cease to exist at any समय.  Don't use or modअगरy
	 * new_समयr after the unlock call.
	 */
out:
	release_posix_समयr(new_समयr, it_id_set);
	वापस error;
पूर्ण

SYSCALL_DEFINE3(समयr_create, स्थिर घड़ीid_t, which_घड़ी,
		काष्ठा sigevent __user *, समयr_event_spec,
		समयr_t __user *, created_समयr_id)
अणु
	अगर (समयr_event_spec) अणु
		sigevent_t event;

		अगर (copy_from_user(&event, समयr_event_spec, माप (event)))
			वापस -EFAULT;
		वापस करो_समयr_create(which_घड़ी, &event, created_समयr_id);
	पूर्ण
	वापस करो_समयr_create(which_घड़ी, शून्य, created_समयr_id);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE3(समयr_create, घड़ीid_t, which_घड़ी,
		       काष्ठा compat_sigevent __user *, समयr_event_spec,
		       समयr_t __user *, created_समयr_id)
अणु
	अगर (समयr_event_spec) अणु
		sigevent_t event;

		अगर (get_compat_sigevent(&event, समयr_event_spec))
			वापस -EFAULT;
		वापस करो_समयr_create(which_घड़ी, &event, created_समयr_id);
	पूर्ण
	वापस करो_समयr_create(which_घड़ी, शून्य, created_समयr_id);
पूर्ण
#पूर्ण_अगर

/*
 * Locking issues: We need to protect the result of the id look up until
 * we get the समयr locked करोwn so it is not deleted under us.  The
 * removal is करोne under the idr spinlock so we use that here to bridge
 * the find to the समयr lock.  To aव्योम a dead lock, the समयr id MUST
 * be release with out holding the समयr lock.
 */
अटल काष्ठा k_iसमयr *__lock_समयr(समयr_t समयr_id, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा k_iसमयr *timr;

	/*
	 * समयr_t could be any type >= पूर्णांक and we want to make sure any
	 * @समयr_id outside positive पूर्णांक range fails lookup.
	 */
	अगर ((अचिन्हित दीर्घ दीर्घ)समयr_id > पूर्णांक_उच्च)
		वापस शून्य;

	rcu_पढ़ो_lock();
	timr = posix_समयr_by_id(समयr_id);
	अगर (timr) अणु
		spin_lock_irqsave(&timr->it_lock, *flags);
		अगर (timr->it_संकेत == current->संकेत) अणु
			rcu_पढ़ो_unlock();
			वापस timr;
		पूर्ण
		spin_unlock_irqrestore(&timr->it_lock, *flags);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस शून्य;
पूर्ण

अटल kसमय_प्रकार common_hrसमयr_reमुख्यing(काष्ठा k_iसमयr *timr, kसमय_प्रकार now)
अणु
	काष्ठा hrसमयr *समयr = &timr->it.real.समयr;

	वापस __hrसमयr_expires_reमुख्यing_adjusted(समयr, now);
पूर्ण

अटल s64 common_hrसमयr_क्रमward(काष्ठा k_iसमयr *timr, kसमय_प्रकार now)
अणु
	काष्ठा hrसमयr *समयr = &timr->it.real.समयr;

	वापस hrसमयr_क्रमward(समयr, now, timr->it_पूर्णांकerval);
पूर्ण

/*
 * Get the समय reमुख्यing on a POSIX.1b पूर्णांकerval समयr.  This function
 * is ALWAYS called with spin_lock_irq on the समयr, thus it must not
 * mess with irq.
 *
 * We have a couple of messes to clean up here.  First there is the हाल
 * of a समयr that has a requeue pending.  These समयrs should appear to
 * be in the समयr list with an expiry as अगर we were to requeue them
 * now.
 *
 * The second issue is the SIGEV_NONE समयr which may be active but is
 * not really ever put in the समयr list (to save प्रणाली resources).
 * This समयr may be expired, and अगर so, we will करो it here.  Otherwise
 * it is the same as a requeue pending समयr WRT to what we should
 * report.
 */
व्योम common_समयr_get(काष्ठा k_iसमयr *timr, काष्ठा iसमयrspec64 *cur_setting)
अणु
	स्थिर काष्ठा k_घड़ी *kc = timr->kघड़ी;
	kसमय_प्रकार now, reमुख्यing, iv;
	bool sig_none;

	sig_none = timr->it_sigev_notअगरy == SIGEV_NONE;
	iv = timr->it_पूर्णांकerval;

	/* पूर्णांकerval समयr ? */
	अगर (iv) अणु
		cur_setting->it_पूर्णांकerval = kसमय_प्रकारo_बारpec64(iv);
	पूर्ण अन्यथा अगर (!timr->it_active) अणु
		/*
		 * SIGEV_NONE oneshot समयrs are never queued. Check them
		 * below.
		 */
		अगर (!sig_none)
			वापस;
	पूर्ण

	now = kc->घड़ी_get_kसमय(timr->it_घड़ी);

	/*
	 * When a requeue is pending or this is a SIGEV_NONE समयr move the
	 * expiry समय क्रमward by पूर्णांकervals, so expiry is > now.
	 */
	अगर (iv && (timr->it_requeue_pending & REQUEUE_PENDING || sig_none))
		timr->it_overrun += kc->समयr_क्रमward(timr, now);

	reमुख्यing = kc->समयr_reमुख्यing(timr, now);
	/* Return 0 only, when the समयr is expired and not pending */
	अगर (reमुख्यing <= 0) अणु
		/*
		 * A single shot SIGEV_NONE समयr must वापस 0, when
		 * it is expired !
		 */
		अगर (!sig_none)
			cur_setting->it_value.tv_nsec = 1;
	पूर्ण अन्यथा अणु
		cur_setting->it_value = kसमय_प्रकारo_बारpec64(reमुख्यing);
	पूर्ण
पूर्ण

/* Get the समय reमुख्यing on a POSIX.1b पूर्णांकerval समयr. */
अटल पूर्णांक करो_समयr_समय_लो(समयr_t समयr_id,  काष्ठा iसमयrspec64 *setting)
अणु
	काष्ठा k_iसमयr *timr;
	स्थिर काष्ठा k_घड़ी *kc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	timr = lock_समयr(समयr_id, &flags);
	अगर (!timr)
		वापस -EINVAL;

	स_रखो(setting, 0, माप(*setting));
	kc = timr->kघड़ी;
	अगर (WARN_ON_ONCE(!kc || !kc->समयr_get))
		ret = -EINVAL;
	अन्यथा
		kc->समयr_get(timr, setting);

	unlock_समयr(timr, flags);
	वापस ret;
पूर्ण

/* Get the समय reमुख्यing on a POSIX.1b पूर्णांकerval समयr. */
SYSCALL_DEFINE2(समयr_समय_लो, समयr_t, समयr_id,
		काष्ठा __kernel_iसमयrspec __user *, setting)
अणु
	काष्ठा iसमयrspec64 cur_setting;

	पूर्णांक ret = करो_समयr_समय_लो(समयr_id, &cur_setting);
	अगर (!ret) अणु
		अगर (put_iसमयrspec64(&cur_setting, setting))
			ret = -EFAULT;
	पूर्ण
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME

SYSCALL_DEFINE2(समयr_समय_लो32, समयr_t, समयr_id,
		काष्ठा old_iसमयrspec32 __user *, setting)
अणु
	काष्ठा iसमयrspec64 cur_setting;

	पूर्णांक ret = करो_समयr_समय_लो(समयr_id, &cur_setting);
	अगर (!ret) अणु
		अगर (put_old_iसमयrspec32(&cur_setting, setting))
			ret = -EFAULT;
	पूर्ण
	वापस ret;
पूर्ण

#पूर्ण_अगर

/*
 * Get the number of overruns of a POSIX.1b पूर्णांकerval समयr.  This is to
 * be the overrun of the समयr last delivered.  At the same समय we are
 * accumulating overruns on the next समयr.  The overrun is frozen when
 * the संकेत is delivered, either at the notअगरy समय (अगर the info block
 * is not queued) or at the actual delivery समय (as we are inक्रमmed by
 * the call back to posixसमयr_rearm().  So all we need to करो is
 * to pick up the frozen overrun.
 */
SYSCALL_DEFINE1(समयr_getoverrun, समयr_t, समयr_id)
अणु
	काष्ठा k_iसमयr *timr;
	पूर्णांक overrun;
	अचिन्हित दीर्घ flags;

	timr = lock_समयr(समयr_id, &flags);
	अगर (!timr)
		वापस -EINVAL;

	overrun = समयr_overrun_to_पूर्णांक(timr, 0);
	unlock_समयr(timr, flags);

	वापस overrun;
पूर्ण

अटल व्योम common_hrसमयr_arm(काष्ठा k_iसमयr *timr, kसमय_प्रकार expires,
			       bool असलolute, bool sigev_none)
अणु
	काष्ठा hrसमयr *समयr = &timr->it.real.समयr;
	क्रमागत hrसमयr_mode mode;

	mode = असलolute ? HRTIMER_MODE_ABS : HRTIMER_MODE_REL;
	/*
	 * Posix magic: Relative CLOCK_REALTIME समयrs are not affected by
	 * घड़ी modअगरications, so they become CLOCK_MONOTONIC based under the
	 * hood. See hrसमयr_init(). Update timr->kघड़ी, so the generic
	 * functions which use timr->kघड़ी->घड़ी_get_*() work.
	 *
	 * Note: it_घड़ी stays unmodअगरied, because the next समयr_set() might
	 * use ABSTIME, so it needs to चयन back.
	 */
	अगर (timr->it_घड़ी == CLOCK_REALTIME)
		timr->kघड़ी = असलolute ? &घड़ी_realसमय : &घड़ी_monotonic;

	hrसमयr_init(&timr->it.real.समयr, timr->it_घड़ी, mode);
	timr->it.real.समयr.function = posix_समयr_fn;

	अगर (!असलolute)
		expires = kसमय_add_safe(expires, समयr->base->get_समय());
	hrसमयr_set_expires(समयr, expires);

	अगर (!sigev_none)
		hrसमयr_start_expires(समयr, HRTIMER_MODE_ABS);
पूर्ण

अटल पूर्णांक common_hrसमयr_try_to_cancel(काष्ठा k_iसमयr *timr)
अणु
	वापस hrसमयr_try_to_cancel(&timr->it.real.समयr);
पूर्ण

अटल व्योम common_समयr_रुको_running(काष्ठा k_iसमयr *समयr)
अणु
	hrसमयr_cancel_रुको_running(&समयr->it.real.समयr);
पूर्ण

/*
 * On PREEMPT_RT this prevent priority inversion against softirq kthपढ़ो in
 * हाल it माला_लो preempted जबतक executing a समयr callback. See comments in
 * hrसमयr_cancel_रुको_running. For PREEMPT_RT=n this just results in a
 * cpu_relax().
 */
अटल काष्ठा k_iसमयr *समयr_रुको_running(काष्ठा k_iसमयr *समयr,
					   अचिन्हित दीर्घ *flags)
अणु
	स्थिर काष्ठा k_घड़ी *kc = READ_ONCE(समयr->kघड़ी);
	समयr_t समयr_id = READ_ONCE(समयr->it_id);

	/* Prevent kमुक्त(समयr) after dropping the lock */
	rcu_पढ़ो_lock();
	unlock_समयr(समयr, *flags);

	अगर (!WARN_ON_ONCE(!kc->समयr_रुको_running))
		kc->समयr_रुको_running(समयr);

	rcu_पढ़ो_unlock();
	/* Relock the समयr. It might be not दीर्घer hashed. */
	वापस lock_समयr(समयr_id, flags);
पूर्ण

/* Set a POSIX.1b पूर्णांकerval समयr. */
पूर्णांक common_समयr_set(काष्ठा k_iसमयr *timr, पूर्णांक flags,
		     काष्ठा iसमयrspec64 *new_setting,
		     काष्ठा iसमयrspec64 *old_setting)
अणु
	स्थिर काष्ठा k_घड़ी *kc = timr->kघड़ी;
	bool sigev_none;
	kसमय_प्रकार expires;

	अगर (old_setting)
		common_समयr_get(timr, old_setting);

	/* Prevent rearming by clearing the पूर्णांकerval */
	timr->it_पूर्णांकerval = 0;
	/*
	 * Careful here. On SMP प्रणालीs the समयr expiry function could be
	 * active and spinning on timr->it_lock.
	 */
	अगर (kc->समयr_try_to_cancel(timr) < 0)
		वापस TIMER_RETRY;

	timr->it_active = 0;
	timr->it_requeue_pending = (timr->it_requeue_pending + 2) &
		~REQUEUE_PENDING;
	timr->it_overrun_last = 0;

	/* Switch off the समयr when it_value is zero */
	अगर (!new_setting->it_value.tv_sec && !new_setting->it_value.tv_nsec)
		वापस 0;

	timr->it_पूर्णांकerval = बारpec64_to_kसमय(new_setting->it_पूर्णांकerval);
	expires = बारpec64_to_kसमय(new_setting->it_value);
	अगर (flags & TIMER_ABSTIME)
		expires = समयns_kसमय_प्रकारo_host(timr->it_घड़ी, expires);
	sigev_none = timr->it_sigev_notअगरy == SIGEV_NONE;

	kc->समयr_arm(timr, expires, flags & TIMER_ABSTIME, sigev_none);
	timr->it_active = !sigev_none;
	वापस 0;
पूर्ण

अटल पूर्णांक करो_समयr_समय_रखो(समयr_t समयr_id, पूर्णांक पंचांगr_flags,
			    काष्ठा iसमयrspec64 *new_spec64,
			    काष्ठा iसमयrspec64 *old_spec64)
अणु
	स्थिर काष्ठा k_घड़ी *kc;
	काष्ठा k_iसमयr *timr;
	अचिन्हित दीर्घ flags;
	पूर्णांक error = 0;

	अगर (!बारpec64_valid(&new_spec64->it_पूर्णांकerval) ||
	    !बारpec64_valid(&new_spec64->it_value))
		वापस -EINVAL;

	अगर (old_spec64)
		स_रखो(old_spec64, 0, माप(*old_spec64));

	timr = lock_समयr(समयr_id, &flags);
retry:
	अगर (!timr)
		वापस -EINVAL;

	kc = timr->kघड़ी;
	अगर (WARN_ON_ONCE(!kc || !kc->समयr_set))
		error = -EINVAL;
	अन्यथा
		error = kc->समयr_set(timr, पंचांगr_flags, new_spec64, old_spec64);

	अगर (error == TIMER_RETRY) अणु
		// We alपढ़ोy got the old समय...
		old_spec64 = शून्य;
		/* Unlocks and relocks the समयr अगर it still exists */
		timr = समयr_रुको_running(timr, &flags);
		जाओ retry;
	पूर्ण
	unlock_समयr(timr, flags);

	वापस error;
पूर्ण

/* Set a POSIX.1b पूर्णांकerval समयr */
SYSCALL_DEFINE4(समयr_समय_रखो, समयr_t, समयr_id, पूर्णांक, flags,
		स्थिर काष्ठा __kernel_iसमयrspec __user *, new_setting,
		काष्ठा __kernel_iसमयrspec __user *, old_setting)
अणु
	काष्ठा iसमयrspec64 new_spec, old_spec;
	काष्ठा iसमयrspec64 *rtn = old_setting ? &old_spec : शून्य;
	पूर्णांक error = 0;

	अगर (!new_setting)
		वापस -EINVAL;

	अगर (get_iसमयrspec64(&new_spec, new_setting))
		वापस -EFAULT;

	error = करो_समयr_समय_रखो(समयr_id, flags, &new_spec, rtn);
	अगर (!error && old_setting) अणु
		अगर (put_iसमयrspec64(&old_spec, old_setting))
			error = -EFAULT;
	पूर्ण
	वापस error;
पूर्ण

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
SYSCALL_DEFINE4(समयr_समय_रखो32, समयr_t, समयr_id, पूर्णांक, flags,
		काष्ठा old_iसमयrspec32 __user *, new,
		काष्ठा old_iसमयrspec32 __user *, old)
अणु
	काष्ठा iसमयrspec64 new_spec, old_spec;
	काष्ठा iसमयrspec64 *rtn = old ? &old_spec : शून्य;
	पूर्णांक error = 0;

	अगर (!new)
		वापस -EINVAL;
	अगर (get_old_iसमयrspec32(&new_spec, new))
		वापस -EFAULT;

	error = करो_समयr_समय_रखो(समयr_id, flags, &new_spec, rtn);
	अगर (!error && old) अणु
		अगर (put_old_iसमयrspec32(&old_spec, old))
			error = -EFAULT;
	पूर्ण
	वापस error;
पूर्ण
#पूर्ण_अगर

पूर्णांक common_समयr_del(काष्ठा k_iसमयr *समयr)
अणु
	स्थिर काष्ठा k_घड़ी *kc = समयr->kघड़ी;

	समयr->it_पूर्णांकerval = 0;
	अगर (kc->समयr_try_to_cancel(समयr) < 0)
		वापस TIMER_RETRY;
	समयr->it_active = 0;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक समयr_delete_hook(काष्ठा k_iसमयr *समयr)
अणु
	स्थिर काष्ठा k_घड़ी *kc = समयr->kघड़ी;

	अगर (WARN_ON_ONCE(!kc || !kc->समयr_del))
		वापस -EINVAL;
	वापस kc->समयr_del(समयr);
पूर्ण

/* Delete a POSIX.1b पूर्णांकerval समयr. */
SYSCALL_DEFINE1(समयr_delete, समयr_t, समयr_id)
अणु
	काष्ठा k_iसमयr *समयr;
	अचिन्हित दीर्घ flags;

	समयr = lock_समयr(समयr_id, &flags);

retry_delete:
	अगर (!समयr)
		वापस -EINVAL;

	अगर (unlikely(समयr_delete_hook(समयr) == TIMER_RETRY)) अणु
		/* Unlocks and relocks the समयr अगर it still exists */
		समयr = समयr_रुको_running(समयr, &flags);
		जाओ retry_delete;
	पूर्ण

	spin_lock(&current->sighand->siglock);
	list_del(&समयr->list);
	spin_unlock(&current->sighand->siglock);
	/*
	 * This keeps any tasks रुकोing on the spin lock from thinking
	 * they got something (see the lock code above).
	 */
	समयr->it_संकेत = शून्य;

	unlock_समयr(समयr, flags);
	release_posix_समयr(समयr, IT_ID_SET);
	वापस 0;
पूर्ण

/*
 * वापस समयr owned by the process, used by निकास_iसमयrs
 */
अटल व्योम iसमयr_delete(काष्ठा k_iसमयr *समयr)
अणु
retry_delete:
	spin_lock_irq(&समयr->it_lock);

	अगर (समयr_delete_hook(समयr) == TIMER_RETRY) अणु
		spin_unlock_irq(&समयr->it_lock);
		जाओ retry_delete;
	पूर्ण
	list_del(&समयr->list);

	spin_unlock_irq(&समयr->it_lock);
	release_posix_समयr(समयr, IT_ID_SET);
पूर्ण

/*
 * This is called by करो_निकास or de_thपढ़ो, only when there are no more
 * references to the shared संकेत_काष्ठा.
 */
व्योम निकास_iसमयrs(काष्ठा संकेत_काष्ठा *sig)
अणु
	काष्ठा k_iसमयr *पंचांगr;

	जबतक (!list_empty(&sig->posix_समयrs)) अणु
		पंचांगr = list_entry(sig->posix_समयrs.next, काष्ठा k_iसमयr, list);
		iसमयr_delete(पंचांगr);
	पूर्ण
पूर्ण

SYSCALL_DEFINE2(घड़ी_समय_रखो, स्थिर घड़ीid_t, which_घड़ी,
		स्थिर काष्ठा __kernel_बारpec __user *, tp)
अणु
	स्थिर काष्ठा k_घड़ी *kc = घड़ीid_to_kघड़ी(which_घड़ी);
	काष्ठा बारpec64 new_tp;

	अगर (!kc || !kc->घड़ी_set)
		वापस -EINVAL;

	अगर (get_बारpec64(&new_tp, tp))
		वापस -EFAULT;

	वापस kc->घड़ी_set(which_घड़ी, &new_tp);
पूर्ण

SYSCALL_DEFINE2(घड़ी_समय_लो, स्थिर घड़ीid_t, which_घड़ी,
		काष्ठा __kernel_बारpec __user *, tp)
अणु
	स्थिर काष्ठा k_घड़ी *kc = घड़ीid_to_kघड़ी(which_घड़ी);
	काष्ठा बारpec64 kernel_tp;
	पूर्णांक error;

	अगर (!kc)
		वापस -EINVAL;

	error = kc->घड़ी_get_बारpec(which_घड़ी, &kernel_tp);

	अगर (!error && put_बारpec64(&kernel_tp, tp))
		error = -EFAULT;

	वापस error;
पूर्ण

पूर्णांक करो_घड़ी_adjसमय(स्थिर घड़ीid_t which_घड़ी, काष्ठा __kernel_समयx * ktx)
अणु
	स्थिर काष्ठा k_घड़ी *kc = घड़ीid_to_kघड़ी(which_घड़ी);

	अगर (!kc)
		वापस -EINVAL;
	अगर (!kc->घड़ी_adj)
		वापस -EOPNOTSUPP;

	वापस kc->घड़ी_adj(which_घड़ी, ktx);
पूर्ण

SYSCALL_DEFINE2(घड़ी_adjसमय, स्थिर घड़ीid_t, which_घड़ी,
		काष्ठा __kernel_समयx __user *, utx)
अणु
	काष्ठा __kernel_समयx ktx;
	पूर्णांक err;

	अगर (copy_from_user(&ktx, utx, माप(ktx)))
		वापस -EFAULT;

	err = करो_घड़ी_adjसमय(which_घड़ी, &ktx);

	अगर (err >= 0 && copy_to_user(utx, &ktx, माप(ktx)))
		वापस -EFAULT;

	वापस err;
पूर्ण

SYSCALL_DEFINE2(घड़ी_getres, स्थिर घड़ीid_t, which_घड़ी,
		काष्ठा __kernel_बारpec __user *, tp)
अणु
	स्थिर काष्ठा k_घड़ी *kc = घड़ीid_to_kघड़ी(which_घड़ी);
	काष्ठा बारpec64 rtn_tp;
	पूर्णांक error;

	अगर (!kc)
		वापस -EINVAL;

	error = kc->घड़ी_getres(which_घड़ी, &rtn_tp);

	अगर (!error && tp && put_बारpec64(&rtn_tp, tp))
		error = -EFAULT;

	वापस error;
पूर्ण

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME

SYSCALL_DEFINE2(घड़ी_समय_रखो32, घड़ीid_t, which_घड़ी,
		काष्ठा old_बारpec32 __user *, tp)
अणु
	स्थिर काष्ठा k_घड़ी *kc = घड़ीid_to_kघड़ी(which_घड़ी);
	काष्ठा बारpec64 ts;

	अगर (!kc || !kc->घड़ी_set)
		वापस -EINVAL;

	अगर (get_old_बारpec32(&ts, tp))
		वापस -EFAULT;

	वापस kc->घड़ी_set(which_घड़ी, &ts);
पूर्ण

SYSCALL_DEFINE2(घड़ी_समय_लो32, घड़ीid_t, which_घड़ी,
		काष्ठा old_बारpec32 __user *, tp)
अणु
	स्थिर काष्ठा k_घड़ी *kc = घड़ीid_to_kघड़ी(which_घड़ी);
	काष्ठा बारpec64 ts;
	पूर्णांक err;

	अगर (!kc)
		वापस -EINVAL;

	err = kc->घड़ी_get_बारpec(which_घड़ी, &ts);

	अगर (!err && put_old_बारpec32(&ts, tp))
		err = -EFAULT;

	वापस err;
पूर्ण

SYSCALL_DEFINE2(घड़ी_adjसमय32, घड़ीid_t, which_घड़ी,
		काष्ठा old_समयx32 __user *, utp)
अणु
	काष्ठा __kernel_समयx ktx;
	पूर्णांक err;

	err = get_old_समयx32(&ktx, utp);
	अगर (err)
		वापस err;

	err = करो_घड़ी_adjसमय(which_घड़ी, &ktx);

	अगर (err >= 0 && put_old_समयx32(utp, &ktx))
		वापस -EFAULT;

	वापस err;
पूर्ण

SYSCALL_DEFINE2(घड़ी_getres_समय32, घड़ीid_t, which_घड़ी,
		काष्ठा old_बारpec32 __user *, tp)
अणु
	स्थिर काष्ठा k_घड़ी *kc = घड़ीid_to_kघड़ी(which_घड़ी);
	काष्ठा बारpec64 ts;
	पूर्णांक err;

	अगर (!kc)
		वापस -EINVAL;

	err = kc->घड़ी_getres(which_घड़ी, &ts);
	अगर (!err && tp && put_old_बारpec32(&ts, tp))
		वापस -EFAULT;

	वापस err;
पूर्ण

#पूर्ण_अगर

/*
 * nanosleep क्रम monotonic and realसमय घड़ीs
 */
अटल पूर्णांक common_nsleep(स्थिर घड़ीid_t which_घड़ी, पूर्णांक flags,
			 स्थिर काष्ठा बारpec64 *rqtp)
अणु
	kसमय_प्रकार texp = बारpec64_to_kसमय(*rqtp);

	वापस hrसमयr_nanosleep(texp, flags & TIMER_ABSTIME ?
				 HRTIMER_MODE_ABS : HRTIMER_MODE_REL,
				 which_घड़ी);
पूर्ण

अटल पूर्णांक common_nsleep_समयns(स्थिर घड़ीid_t which_घड़ी, पूर्णांक flags,
			 स्थिर काष्ठा बारpec64 *rqtp)
अणु
	kसमय_प्रकार texp = बारpec64_to_kसमय(*rqtp);

	अगर (flags & TIMER_ABSTIME)
		texp = समयns_kसमय_प्रकारo_host(which_घड़ी, texp);

	वापस hrसमयr_nanosleep(texp, flags & TIMER_ABSTIME ?
				 HRTIMER_MODE_ABS : HRTIMER_MODE_REL,
				 which_घड़ी);
पूर्ण

SYSCALL_DEFINE4(घड़ी_nanosleep, स्थिर घड़ीid_t, which_घड़ी, पूर्णांक, flags,
		स्थिर काष्ठा __kernel_बारpec __user *, rqtp,
		काष्ठा __kernel_बारpec __user *, rmtp)
अणु
	स्थिर काष्ठा k_घड़ी *kc = घड़ीid_to_kघड़ी(which_घड़ी);
	काष्ठा बारpec64 t;

	अगर (!kc)
		वापस -EINVAL;
	अगर (!kc->nsleep)
		वापस -EOPNOTSUPP;

	अगर (get_बारpec64(&t, rqtp))
		वापस -EFAULT;

	अगर (!बारpec64_valid(&t))
		वापस -EINVAL;
	अगर (flags & TIMER_ABSTIME)
		rmtp = शून्य;
	current->restart_block.nanosleep.type = rmtp ? TT_NATIVE : TT_NONE;
	current->restart_block.nanosleep.rmtp = rmtp;

	वापस kc->nsleep(which_घड़ी, flags, &t);
पूर्ण

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME

SYSCALL_DEFINE4(घड़ी_nanosleep_समय32, घड़ीid_t, which_घड़ी, पूर्णांक, flags,
		काष्ठा old_बारpec32 __user *, rqtp,
		काष्ठा old_बारpec32 __user *, rmtp)
अणु
	स्थिर काष्ठा k_घड़ी *kc = घड़ीid_to_kघड़ी(which_घड़ी);
	काष्ठा बारpec64 t;

	अगर (!kc)
		वापस -EINVAL;
	अगर (!kc->nsleep)
		वापस -EOPNOTSUPP;

	अगर (get_old_बारpec32(&t, rqtp))
		वापस -EFAULT;

	अगर (!बारpec64_valid(&t))
		वापस -EINVAL;
	अगर (flags & TIMER_ABSTIME)
		rmtp = शून्य;
	current->restart_block.nanosleep.type = rmtp ? TT_COMPAT : TT_NONE;
	current->restart_block.nanosleep.compat_rmtp = rmtp;

	वापस kc->nsleep(which_घड़ी, flags, &t);
पूर्ण

#पूर्ण_अगर

अटल स्थिर काष्ठा k_घड़ी घड़ी_realसमय = अणु
	.घड़ी_getres		= posix_get_hrसमयr_res,
	.घड़ी_get_बारpec	= posix_get_realसमय_प्रकारimespec,
	.घड़ी_get_kसमय	= posix_get_realसमय_kसमय,
	.घड़ी_set		= posix_घड़ी_realसमय_set,
	.घड़ी_adj		= posix_घड़ी_realसमय_adj,
	.nsleep			= common_nsleep,
	.समयr_create		= common_समयr_create,
	.समयr_set		= common_समयr_set,
	.समयr_get		= common_समयr_get,
	.समयr_del		= common_समयr_del,
	.समयr_rearm		= common_hrसमयr_rearm,
	.समयr_क्रमward		= common_hrसमयr_क्रमward,
	.समयr_reमुख्यing	= common_hrसमयr_reमुख्यing,
	.समयr_try_to_cancel	= common_hrसमयr_try_to_cancel,
	.समयr_रुको_running	= common_समयr_रुको_running,
	.समयr_arm		= common_hrसमयr_arm,
पूर्ण;

अटल स्थिर काष्ठा k_घड़ी घड़ी_monotonic = अणु
	.घड़ी_getres		= posix_get_hrसमयr_res,
	.घड़ी_get_बारpec	= posix_get_monotonic_बारpec,
	.घड़ी_get_kसमय	= posix_get_monotonic_kसमय,
	.nsleep			= common_nsleep_समयns,
	.समयr_create		= common_समयr_create,
	.समयr_set		= common_समयr_set,
	.समयr_get		= common_समयr_get,
	.समयr_del		= common_समयr_del,
	.समयr_rearm		= common_hrसमयr_rearm,
	.समयr_क्रमward		= common_hrसमयr_क्रमward,
	.समयr_reमुख्यing	= common_hrसमयr_reमुख्यing,
	.समयr_try_to_cancel	= common_hrसमयr_try_to_cancel,
	.समयr_रुको_running	= common_समयr_रुको_running,
	.समयr_arm		= common_hrसमयr_arm,
पूर्ण;

अटल स्थिर काष्ठा k_घड़ी घड़ी_monotonic_raw = अणु
	.घड़ी_getres		= posix_get_hrसमयr_res,
	.घड़ी_get_बारpec	= posix_get_monotonic_raw,
पूर्ण;

अटल स्थिर काष्ठा k_घड़ी घड़ी_realसमय_coarse = अणु
	.घड़ी_getres		= posix_get_coarse_res,
	.घड़ी_get_बारpec	= posix_get_realसमय_coarse,
पूर्ण;

अटल स्थिर काष्ठा k_घड़ी घड़ी_monotonic_coarse = अणु
	.घड़ी_getres		= posix_get_coarse_res,
	.घड़ी_get_बारpec	= posix_get_monotonic_coarse,
पूर्ण;

अटल स्थिर काष्ठा k_घड़ी घड़ी_प्रकारai = अणु
	.घड़ी_getres		= posix_get_hrसमयr_res,
	.घड़ी_get_kसमय	= posix_get_tai_kसमय,
	.घड़ी_get_बारpec	= posix_get_tai_बारpec,
	.nsleep			= common_nsleep,
	.समयr_create		= common_समयr_create,
	.समयr_set		= common_समयr_set,
	.समयr_get		= common_समयr_get,
	.समयr_del		= common_समयr_del,
	.समयr_rearm		= common_hrसमयr_rearm,
	.समयr_क्रमward		= common_hrसमयr_क्रमward,
	.समयr_reमुख्यing	= common_hrसमयr_reमुख्यing,
	.समयr_try_to_cancel	= common_hrसमयr_try_to_cancel,
	.समयr_रुको_running	= common_समयr_रुको_running,
	.समयr_arm		= common_hrसमयr_arm,
पूर्ण;

अटल स्थिर काष्ठा k_घड़ी घड़ी_bootसमय = अणु
	.घड़ी_getres		= posix_get_hrसमयr_res,
	.घड़ी_get_kसमय	= posix_get_bootसमय_kसमय,
	.घड़ी_get_बारpec	= posix_get_bootसमय_प्रकारimespec,
	.nsleep			= common_nsleep_समयns,
	.समयr_create		= common_समयr_create,
	.समयr_set		= common_समयr_set,
	.समयr_get		= common_समयr_get,
	.समयr_del		= common_समयr_del,
	.समयr_rearm		= common_hrसमयr_rearm,
	.समयr_क्रमward		= common_hrसमयr_क्रमward,
	.समयr_reमुख्यing	= common_hrसमयr_reमुख्यing,
	.समयr_try_to_cancel	= common_hrसमयr_try_to_cancel,
	.समयr_रुको_running	= common_समयr_रुको_running,
	.समयr_arm		= common_hrसमयr_arm,
पूर्ण;

अटल स्थिर काष्ठा k_घड़ी * स्थिर posix_घड़ीs[] = अणु
	[CLOCK_REALTIME]		= &घड़ी_realसमय,
	[CLOCK_MONOTONIC]		= &घड़ी_monotonic,
	[CLOCK_PROCESS_CPUTIME_ID]	= &घड़ी_process,
	[CLOCK_THREAD_CPUTIME_ID]	= &घड़ी_प्रकारhपढ़ो,
	[CLOCK_MONOTONIC_RAW]		= &घड़ी_monotonic_raw,
	[CLOCK_REALTIME_COARSE]		= &घड़ी_realसमय_coarse,
	[CLOCK_MONOTONIC_COARSE]	= &घड़ी_monotonic_coarse,
	[CLOCK_BOOTTIME]		= &घड़ी_bootसमय,
	[CLOCK_REALTIME_ALARM]		= &alarm_घड़ी,
	[CLOCK_BOOTTIME_ALARM]		= &alarm_घड़ी,
	[CLOCK_TAI]			= &घड़ी_प्रकारai,
पूर्ण;

अटल स्थिर काष्ठा k_घड़ी *घड़ीid_to_kघड़ी(स्थिर घड़ीid_t id)
अणु
	घड़ीid_t idx = id;

	अगर (id < 0) अणु
		वापस (id & CLOCKFD_MASK) == CLOCKFD ?
			&घड़ी_posix_dynamic : &घड़ी_posix_cpu;
	पूर्ण

	अगर (id >= ARRAY_SIZE(posix_घड़ीs))
		वापस शून्य;

	वापस posix_घड़ीs[array_index_nospec(idx, ARRAY_SIZE(posix_घड़ीs))];
पूर्ण
