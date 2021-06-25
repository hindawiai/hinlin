<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 1992 Darren Senn
 */

/* These are all the functions necessary to implement iसमयrs */

#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/समय.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <linux/posix-समयrs.h>
#समावेश <linux/hrसमयr.h>
#समावेश <trace/events/समयr.h>
#समावेश <linux/compat.h>

#समावेश <linux/uaccess.h>

/**
 * iसमयr_get_remसमय - get reमुख्यing समय क्रम the समयr
 *
 * @समयr: the समयr to पढ़ो
 *
 * Returns the delta between the expiry समय and now, which can be
 * less than zero or 1usec क्रम an pending expired समयr
 */
अटल काष्ठा बारpec64 iसमयr_get_remसमय(काष्ठा hrसमयr *समयr)
अणु
	kसमय_प्रकार rem = __hrसमयr_get_reमुख्यing(समयr, true);

	/*
	 * Racy but safe: अगर the iसमयr expires after the above
	 * hrसमयr_get_remसमय() call but beक्रमe this condition
	 * then we वापस 0 - which is correct.
	 */
	अगर (hrसमयr_active(समयr)) अणु
		अगर (rem <= 0)
			rem = NSEC_PER_USEC;
	पूर्ण अन्यथा
		rem = 0;

	वापस kसमय_प्रकारo_बारpec64(rem);
पूर्ण

अटल व्योम get_cpu_iसमयr(काष्ठा task_काष्ठा *tsk, अचिन्हित पूर्णांक घड़ी_id,
			   काष्ठा iसमयrspec64 *स्थिर value)
अणु
	u64 val, पूर्णांकerval;
	काष्ठा cpu_iसमयr *it = &tsk->संकेत->it[घड़ी_id];

	spin_lock_irq(&tsk->sighand->siglock);

	val = it->expires;
	पूर्णांकerval = it->incr;
	अगर (val) अणु
		u64 t, samples[CPUCLOCK_MAX];

		thपढ़ो_group_sample_cpuसमय(tsk, samples);
		t = samples[घड़ी_id];

		अगर (val < t)
			/* about to fire */
			val = TICK_NSEC;
		अन्यथा
			val -= t;
	पूर्ण

	spin_unlock_irq(&tsk->sighand->siglock);

	value->it_value = ns_to_बारpec64(val);
	value->it_पूर्णांकerval = ns_to_बारpec64(पूर्णांकerval);
पूर्ण

अटल पूर्णांक करो_getiसमयr(पूर्णांक which, काष्ठा iसमयrspec64 *value)
अणु
	काष्ठा task_काष्ठा *tsk = current;

	चयन (which) अणु
	हाल ITIMER_REAL:
		spin_lock_irq(&tsk->sighand->siglock);
		value->it_value = iसमयr_get_remसमय(&tsk->संकेत->real_समयr);
		value->it_पूर्णांकerval =
			kसमय_प्रकारo_बारpec64(tsk->संकेत->it_real_incr);
		spin_unlock_irq(&tsk->sighand->siglock);
		अवरोध;
	हाल ITIMER_VIRTUAL:
		get_cpu_iसमयr(tsk, CPUCLOCK_VIRT, value);
		अवरोध;
	हाल ITIMER_PROF:
		get_cpu_iसमयr(tsk, CPUCLOCK_PROF, value);
		अवरोध;
	शेष:
		वापस(-EINVAL);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक put_iसमयrval(काष्ठा __kernel_old_iसमयrval __user *o,
			 स्थिर काष्ठा iसमयrspec64 *i)
अणु
	काष्ठा __kernel_old_iसमयrval v;

	v.it_पूर्णांकerval.tv_sec = i->it_पूर्णांकerval.tv_sec;
	v.it_पूर्णांकerval.tv_usec = i->it_पूर्णांकerval.tv_nsec / NSEC_PER_USEC;
	v.it_value.tv_sec = i->it_value.tv_sec;
	v.it_value.tv_usec = i->it_value.tv_nsec / NSEC_PER_USEC;
	वापस copy_to_user(o, &v, माप(काष्ठा __kernel_old_iसमयrval)) ? -EFAULT : 0;
पूर्ण


SYSCALL_DEFINE2(getiसमयr, पूर्णांक, which, काष्ठा __kernel_old_iसमयrval __user *, value)
अणु
	काष्ठा iसमयrspec64 get_buffer;
	पूर्णांक error = करो_getiसमयr(which, &get_buffer);

	अगर (!error && put_iसमयrval(value, &get_buffer))
		error = -EFAULT;
	वापस error;
पूर्ण

#अगर defined(CONFIG_COMPAT) || defined(CONFIG_ALPHA)
काष्ठा old_iसमयrval32 अणु
	काष्ठा old_समयval32	it_पूर्णांकerval;
	काष्ठा old_समयval32	it_value;
पूर्ण;

अटल पूर्णांक put_old_iसमयrval32(काष्ठा old_iसमयrval32 __user *o,
			       स्थिर काष्ठा iसमयrspec64 *i)
अणु
	काष्ठा old_iसमयrval32 v32;

	v32.it_पूर्णांकerval.tv_sec = i->it_पूर्णांकerval.tv_sec;
	v32.it_पूर्णांकerval.tv_usec = i->it_पूर्णांकerval.tv_nsec / NSEC_PER_USEC;
	v32.it_value.tv_sec = i->it_value.tv_sec;
	v32.it_value.tv_usec = i->it_value.tv_nsec / NSEC_PER_USEC;
	वापस copy_to_user(o, &v32, माप(काष्ठा old_iसमयrval32)) ? -EFAULT : 0;
पूर्ण

COMPAT_SYSCALL_DEFINE2(getiसमयr, पूर्णांक, which,
		       काष्ठा old_iसमयrval32 __user *, value)
अणु
	काष्ठा iसमयrspec64 get_buffer;
	पूर्णांक error = करो_getiसमयr(which, &get_buffer);

	अगर (!error && put_old_iसमयrval32(value, &get_buffer))
		error = -EFAULT;
	वापस error;
पूर्ण
#पूर्ण_अगर

/*
 * The समयr is स्वतःmagically restarted, when पूर्णांकerval != 0
 */
क्रमागत hrसमयr_restart it_real_fn(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा संकेत_काष्ठा *sig =
		container_of(समयr, काष्ठा संकेत_काष्ठा, real_समयr);
	काष्ठा pid *leader_pid = sig->pids[PIDTYPE_TGID];

	trace_iसमयr_expire(ITIMER_REAL, leader_pid, 0);
	समाप्त_pid_info(SIGALRM, SEND_SIG_PRIV, leader_pid);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल व्योम set_cpu_iसमयr(काष्ठा task_काष्ठा *tsk, अचिन्हित पूर्णांक घड़ी_id,
			   स्थिर काष्ठा iसमयrspec64 *स्थिर value,
			   काष्ठा iसमयrspec64 *स्थिर ovalue)
अणु
	u64 oval, nval, oपूर्णांकerval, nपूर्णांकerval;
	काष्ठा cpu_iसमयr *it = &tsk->संकेत->it[घड़ी_id];

	nval = बारpec64_to_ns(&value->it_value);
	nपूर्णांकerval = बारpec64_to_ns(&value->it_पूर्णांकerval);

	spin_lock_irq(&tsk->sighand->siglock);

	oval = it->expires;
	oपूर्णांकerval = it->incr;
	अगर (oval || nval) अणु
		अगर (nval > 0)
			nval += TICK_NSEC;
		set_process_cpu_समयr(tsk, घड़ी_id, &nval, &oval);
	पूर्ण
	it->expires = nval;
	it->incr = nपूर्णांकerval;
	trace_iसमयr_state(घड़ी_id == CPUCLOCK_VIRT ?
			   ITIMER_VIRTUAL : ITIMER_PROF, value, nval);

	spin_unlock_irq(&tsk->sighand->siglock);

	अगर (ovalue) अणु
		ovalue->it_value = ns_to_बारpec64(oval);
		ovalue->it_पूर्णांकerval = ns_to_बारpec64(oपूर्णांकerval);
	पूर्ण
पूर्ण

/*
 * Returns true अगर the समयval is in canonical क्रमm
 */
#घोषणा समयval_valid(t) \
	(((t)->tv_sec >= 0) && (((अचिन्हित दीर्घ) (t)->tv_usec) < USEC_PER_SEC))

अटल पूर्णांक करो_setiसमयr(पूर्णांक which, काष्ठा iसमयrspec64 *value,
			काष्ठा iसमयrspec64 *ovalue)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	काष्ठा hrसमयr *समयr;
	kसमय_प्रकार expires;

	चयन (which) अणु
	हाल ITIMER_REAL:
again:
		spin_lock_irq(&tsk->sighand->siglock);
		समयr = &tsk->संकेत->real_समयr;
		अगर (ovalue) अणु
			ovalue->it_value = iसमयr_get_remसमय(समयr);
			ovalue->it_पूर्णांकerval
				= kसमय_प्रकारo_बारpec64(tsk->संकेत->it_real_incr);
		पूर्ण
		/* We are sharing ->siglock with it_real_fn() */
		अगर (hrसमयr_try_to_cancel(समयr) < 0) अणु
			spin_unlock_irq(&tsk->sighand->siglock);
			hrसमयr_cancel_रुको_running(समयr);
			जाओ again;
		पूर्ण
		expires = बारpec64_to_kसमय(value->it_value);
		अगर (expires != 0) अणु
			tsk->संकेत->it_real_incr =
				बारpec64_to_kसमय(value->it_पूर्णांकerval);
			hrसमयr_start(समयr, expires, HRTIMER_MODE_REL);
		पूर्ण अन्यथा
			tsk->संकेत->it_real_incr = 0;

		trace_iसमयr_state(ITIMER_REAL, value, 0);
		spin_unlock_irq(&tsk->sighand->siglock);
		अवरोध;
	हाल ITIMER_VIRTUAL:
		set_cpu_iसमयr(tsk, CPUCLOCK_VIRT, value, ovalue);
		अवरोध;
	हाल ITIMER_PROF:
		set_cpu_iसमयr(tsk, CPUCLOCK_PROF, value, ovalue);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SECURITY_SELINUX
व्योम clear_iसमयr(व्योम)
अणु
	काष्ठा iसमयrspec64 v = अणुपूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++)
		करो_setiसमयr(i, &v, शून्य);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित __ARCH_WANT_SYS_ALARM

/**
 * alarm_setiसमयr - set alarm in seconds
 *
 * @seconds:	number of seconds until alarm
 *		0 disables the alarm
 *
 * Returns the reमुख्यing समय in seconds of a pending समयr or 0 when
 * the समयr is not active.
 *
 * On 32 bit machines the seconds value is limited to (पूर्णांक_उच्च/2) to aव्योम
 * negative समयval settings which would cause immediate expiry.
 */
अटल अचिन्हित पूर्णांक alarm_setiसमयr(अचिन्हित पूर्णांक seconds)
अणु
	काष्ठा iसमयrspec64 it_new, it_old;

#अगर BITS_PER_LONG < 64
	अगर (seconds > पूर्णांक_उच्च)
		seconds = पूर्णांक_उच्च;
#पूर्ण_अगर
	it_new.it_value.tv_sec = seconds;
	it_new.it_value.tv_nsec = 0;
	it_new.it_पूर्णांकerval.tv_sec = it_new.it_पूर्णांकerval.tv_nsec = 0;

	करो_setiसमयr(ITIMER_REAL, &it_new, &it_old);

	/*
	 * We can't return 0 if we have an alarm pending ...  And we'd
	 * better वापस too much than too little anyway
	 */
	अगर ((!it_old.it_value.tv_sec && it_old.it_value.tv_nsec) ||
	      it_old.it_value.tv_nsec >= (NSEC_PER_SEC / 2))
		it_old.it_value.tv_sec++;

	वापस it_old.it_value.tv_sec;
पूर्ण

/*
 * For backwards compatibility?  This can be करोne in libc so Alpha
 * and all newer ports shouldn't need it.
 */
SYSCALL_DEFINE1(alarm, अचिन्हित पूर्णांक, seconds)
अणु
	वापस alarm_setiसमयr(seconds);
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक get_iसमयrval(काष्ठा iसमयrspec64 *o, स्थिर काष्ठा __kernel_old_iसमयrval __user *i)
अणु
	काष्ठा __kernel_old_iसमयrval v;

	अगर (copy_from_user(&v, i, माप(काष्ठा __kernel_old_iसमयrval)))
		वापस -EFAULT;

	/* Validate the समयvals in value. */
	अगर (!समयval_valid(&v.it_value) ||
	    !समयval_valid(&v.it_पूर्णांकerval))
		वापस -EINVAL;

	o->it_पूर्णांकerval.tv_sec = v.it_पूर्णांकerval.tv_sec;
	o->it_पूर्णांकerval.tv_nsec = v.it_पूर्णांकerval.tv_usec * NSEC_PER_USEC;
	o->it_value.tv_sec = v.it_value.tv_sec;
	o->it_value.tv_nsec = v.it_value.tv_usec * NSEC_PER_USEC;
	वापस 0;
पूर्ण

SYSCALL_DEFINE3(setiसमयr, पूर्णांक, which, काष्ठा __kernel_old_iसमयrval __user *, value,
		काष्ठा __kernel_old_iसमयrval __user *, ovalue)
अणु
	काष्ठा iसमयrspec64 set_buffer, get_buffer;
	पूर्णांक error;

	अगर (value) अणु
		error = get_iसमयrval(&set_buffer, value);
		अगर (error)
			वापस error;
	पूर्ण अन्यथा अणु
		स_रखो(&set_buffer, 0, माप(set_buffer));
		prपूर्णांकk_once(KERN_WARNING "%s calls setitimer() with new_value NULL pointer."
			    " Misfeature support will be removed\n",
			    current->comm);
	पूर्ण

	error = करो_setiसमयr(which, &set_buffer, ovalue ? &get_buffer : शून्य);
	अगर (error || !ovalue)
		वापस error;

	अगर (put_iसमयrval(ovalue, &get_buffer))
		वापस -EFAULT;
	वापस 0;
पूर्ण

#अगर defined(CONFIG_COMPAT) || defined(CONFIG_ALPHA)
अटल पूर्णांक get_old_iसमयrval32(काष्ठा iसमयrspec64 *o, स्थिर काष्ठा old_iसमयrval32 __user *i)
अणु
	काष्ठा old_iसमयrval32 v32;

	अगर (copy_from_user(&v32, i, माप(काष्ठा old_iसमयrval32)))
		वापस -EFAULT;

	/* Validate the समयvals in value.  */
	अगर (!समयval_valid(&v32.it_value) ||
	    !समयval_valid(&v32.it_पूर्णांकerval))
		वापस -EINVAL;

	o->it_पूर्णांकerval.tv_sec = v32.it_पूर्णांकerval.tv_sec;
	o->it_पूर्णांकerval.tv_nsec = v32.it_पूर्णांकerval.tv_usec * NSEC_PER_USEC;
	o->it_value.tv_sec = v32.it_value.tv_sec;
	o->it_value.tv_nsec = v32.it_value.tv_usec * NSEC_PER_USEC;
	वापस 0;
पूर्ण

COMPAT_SYSCALL_DEFINE3(setiसमयr, पूर्णांक, which,
		       काष्ठा old_iसमयrval32 __user *, value,
		       काष्ठा old_iसमयrval32 __user *, ovalue)
अणु
	काष्ठा iसमयrspec64 set_buffer, get_buffer;
	पूर्णांक error;

	अगर (value) अणु
		error = get_old_iसमयrval32(&set_buffer, value);
		अगर (error)
			वापस error;
	पूर्ण अन्यथा अणु
		स_रखो(&set_buffer, 0, माप(set_buffer));
		prपूर्णांकk_once(KERN_WARNING "%s calls setitimer() with new_value NULL pointer."
			    " Misfeature support will be removed\n",
			    current->comm);
	पूर्ण

	error = करो_setiसमयr(which, &set_buffer, ovalue ? &get_buffer : शून्य);
	अगर (error || !ovalue)
		वापस error;
	अगर (put_old_iसमयrval32(ovalue, &get_buffer))
		वापस -EFAULT;
	वापस 0;
पूर्ण
#पूर्ण_अगर
