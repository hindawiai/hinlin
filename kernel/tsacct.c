<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * tsacct.c - System accounting over taskstats पूर्णांकerface
 *
 * Copyright (C) Jay Lan,	<jlan@sgi.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <linux/tsacct_kern.h>
#समावेश <linux/acct.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mm.h>

/*
 * fill in basic accounting fields
 */
व्योम bacct_add_tsk(काष्ठा user_namespace *user_ns,
		   काष्ठा pid_namespace *pid_ns,
		   काष्ठा taskstats *stats, काष्ठा task_काष्ठा *tsk)
अणु
	स्थिर काष्ठा cred *tcred;
	u64 uसमय, sसमय, uबारcaled, sबारcaled;
	u64 delta;
	समय64_t bसमय;

	BUILD_BUG_ON(TS_COMM_LEN < TASK_COMM_LEN);

	/* calculate task elapsed समय in nsec */
	delta = kसमय_get_ns() - tsk->start_समय;
	/* Convert to micro seconds */
	करो_भाग(delta, NSEC_PER_USEC);
	stats->ac_eसमय = delta;
	/* Convert to seconds क्रम bसमय (note y2106 limit) */
	bसमय = kसमय_get_real_seconds() - भाग_u64(delta, USEC_PER_SEC);
	stats->ac_bसमय = clamp_t(समय64_t, bसमय, 0, U32_MAX);
	stats->ac_bसमय64 = bसमय;

	अगर (thपढ़ो_group_leader(tsk)) अणु
		stats->ac_निकासcode = tsk->निकास_code;
		अगर (tsk->flags & PF_FORKNOEXEC)
			stats->ac_flag |= AFORK;
	पूर्ण
	अगर (tsk->flags & PF_SUPERPRIV)
		stats->ac_flag |= ASU;
	अगर (tsk->flags & PF_DUMPCORE)
		stats->ac_flag |= ACORE;
	अगर (tsk->flags & PF_SIGNALED)
		stats->ac_flag |= AXSIG;
	stats->ac_nice	 = task_nice(tsk);
	stats->ac_sched	 = tsk->policy;
	stats->ac_pid	 = task_pid_nr_ns(tsk, pid_ns);
	rcu_पढ़ो_lock();
	tcred = __task_cred(tsk);
	stats->ac_uid	 = from_kuid_munged(user_ns, tcred->uid);
	stats->ac_gid	 = from_kgid_munged(user_ns, tcred->gid);
	stats->ac_ppid	 = pid_alive(tsk) ?
		task_tgid_nr_ns(rcu_dereference(tsk->real_parent), pid_ns) : 0;
	rcu_पढ़ो_unlock();

	task_cpuसमय(tsk, &uसमय, &sसमय);
	stats->ac_uसमय = भाग_u64(uसमय, NSEC_PER_USEC);
	stats->ac_sसमय = भाग_u64(sसमय, NSEC_PER_USEC);

	task_cpuसमय_scaled(tsk, &uबारcaled, &sबारcaled);
	stats->ac_uबारcaled = भाग_u64(uबारcaled, NSEC_PER_USEC);
	stats->ac_sबारcaled = भाग_u64(sबारcaled, NSEC_PER_USEC);

	stats->ac_minflt = tsk->min_flt;
	stats->ac_majflt = tsk->maj_flt;

	म_नकलन(stats->ac_comm, tsk->comm, माप(stats->ac_comm));
पूर्ण


#अगर_घोषित CONFIG_TASK_XACCT

#घोषणा KB 1024
#घोषणा MB (1024*KB)
#घोषणा KB_MASK (~(KB-1))
/*
 * fill in extended accounting fields
 */
व्योम xacct_add_tsk(काष्ठा taskstats *stats, काष्ठा task_काष्ठा *p)
अणु
	काष्ठा mm_काष्ठा *mm;

	/* convert pages-nsec/1024 to Mbyte-usec, see __acct_update_पूर्णांकegrals */
	stats->coremem = p->acct_rss_mem1 * PAGE_SIZE;
	करो_भाग(stats->coremem, 1000 * KB);
	stats->virपंचांगem = p->acct_vm_mem1 * PAGE_SIZE;
	करो_भाग(stats->virपंचांगem, 1000 * KB);
	mm = get_task_mm(p);
	अगर (mm) अणु
		/* adjust to KB unit */
		stats->hiwater_rss   = get_mm_hiwater_rss(mm) * PAGE_SIZE / KB;
		stats->hiwater_vm    = get_mm_hiwater_vm(mm)  * PAGE_SIZE / KB;
		mmput(mm);
	पूर्ण
	stats->पढ़ो_अक्षर	= p->ioac.rअक्षर & KB_MASK;
	stats->ग_लिखो_अक्षर	= p->ioac.wअक्षर & KB_MASK;
	stats->पढ़ो_syscalls	= p->ioac.syscr & KB_MASK;
	stats->ग_लिखो_syscalls	= p->ioac.syscw & KB_MASK;
#अगर_घोषित CONFIG_TASK_IO_ACCOUNTING
	stats->पढ़ो_bytes	= p->ioac.पढ़ो_bytes & KB_MASK;
	stats->ग_लिखो_bytes	= p->ioac.ग_लिखो_bytes & KB_MASK;
	stats->cancelled_ग_लिखो_bytes = p->ioac.cancelled_ग_लिखो_bytes & KB_MASK;
#अन्यथा
	stats->पढ़ो_bytes	= 0;
	stats->ग_लिखो_bytes	= 0;
	stats->cancelled_ग_लिखो_bytes = 0;
#पूर्ण_अगर
पूर्ण
#अघोषित KB
#अघोषित MB

अटल व्योम __acct_update_पूर्णांकegrals(काष्ठा task_काष्ठा *tsk,
				    u64 uसमय, u64 sसमय)
अणु
	u64 समय, delta;

	अगर (!likely(tsk->mm))
		वापस;

	समय = sसमय + uसमय;
	delta = समय - tsk->acct_समयxpd;

	अगर (delta < TICK_NSEC)
		वापस;

	tsk->acct_समयxpd = समय;
	/*
	 * Divide by 1024 to aव्योम overflow, and to aव्योम भागision.
	 * The final unit reported to userspace is Mbyte-usecs,
	 * the rest of the math is करोne in xacct_add_tsk.
	 */
	tsk->acct_rss_mem1 += delta * get_mm_rss(tsk->mm) >> 10;
	tsk->acct_vm_mem1 += delta * tsk->mm->total_vm >> 10;
पूर्ण

/**
 * acct_update_पूर्णांकegrals - update mm पूर्णांकegral fields in task_काष्ठा
 * @tsk: task_काष्ठा क्रम accounting
 */
व्योम acct_update_पूर्णांकegrals(काष्ठा task_काष्ठा *tsk)
अणु
	u64 uसमय, sसमय;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	task_cpuसमय(tsk, &uसमय, &sसमय);
	__acct_update_पूर्णांकegrals(tsk, uसमय, sसमय);
	local_irq_restore(flags);
पूर्ण

/**
 * acct_account_cpuसमय - update mm पूर्णांकegral after cpuसमय update
 * @tsk: task_काष्ठा क्रम accounting
 */
व्योम acct_account_cpuसमय(काष्ठा task_काष्ठा *tsk)
अणु
	__acct_update_पूर्णांकegrals(tsk, tsk->uसमय, tsk->sसमय);
पूर्ण

/**
 * acct_clear_पूर्णांकegrals - clear the mm पूर्णांकegral fields in task_काष्ठा
 * @tsk: task_काष्ठा whose accounting fields are cleared
 */
व्योम acct_clear_पूर्णांकegrals(काष्ठा task_काष्ठा *tsk)
अणु
	tsk->acct_समयxpd = 0;
	tsk->acct_rss_mem1 = 0;
	tsk->acct_vm_mem1 = 0;
पूर्ण
#पूर्ण_अगर
