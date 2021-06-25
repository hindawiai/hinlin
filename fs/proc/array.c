<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/proc/array.c
 *
 *  Copyright (C) 1992  by Linus Torvalds
 *  based on ideas by Darren Senn
 *
 * Fixes:
 * Michael. K. Johnson: stat,staपंचांग extensions.
 *                      <johnsonm@stolaf.edu>
 *
 * Pauline Middelink :  Made cmdline,envline only अवरोध at '\0's, to
 *                      make sure SET_PROCTITLE works. Also हटाओd
 *                      bad '!' which क्रमced address recalculation क्रम
 *                      EVERY अक्षरacter on the current page.
 *                      <middelin@polyware.iaf.nl>
 *
 * Danny ter Haar    :	added cpuinfo
 *			<dth@cistron.nl>
 *
 * Alessandro Rubini :  profile extension.
 *                      <rubini@ipvvis.unipv.it>
 *
 * Jeff Tranter      :  added BogoMips field to cpuinfo
 *                      <Jeff_Tranter@Mitel.COM>
 *
 * Bruno Haible      :  हटाओ 4K limit क्रम the maps file
 *			<haible@ma2s2.mathematik.uni-karlsruhe.de>
 *
 * Yves Arrouye      :  हटाओ removal of trailing spaces in get_array.
 *			<Yves.Arrouye@marin.fdn.fr>
 *
 * Jerome Forissier  :  added per-CPU समय inक्रमmation to /proc/stat
 *                      and /proc/<pid>/cpu extension
 *                      <क्रमissier@isia.cma.fr>
 *			- Incorporation and non-SMP safe operation
 *			of क्रमissier patch in 2.1.78 by
 *			Hans Marcus <crowbar@concepts.nl>
 *
 * aeb@cwi.nl        :  /proc/partitions
 *
 *
 * Alan Cox	     :  security fixes.
 *			<alan@lxorguk.ukuu.org.uk>
 *
 * Al Viro           :  safe handling of mm_काष्ठा
 *
 * Gerhard Wichert   :  added BIGMEM support
 * Siemens AG           <Gerhard.Wichert@pdb.siemens.de>
 *
 * Al Viro & Jeff Garzik :  moved most of the thing पूर्णांकo base.c and
 *			 :  proc_misc.c. The rest may eventually go पूर्णांकo
 *			 :  base.c too.
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समय.स>
#समावेश <linux/समय_namespace.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/tty.h>
#समावेश <linux/माला.स>
#समावेश <linux/mman.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/numa_balancing.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/ioport.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/swap.h>
#समावेश <linux/smp.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/file.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/बार.h>
#समावेश <linux/cpuset.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/delayacct.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/prctl.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/string_helpers.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/fs_काष्ठा.h>

#समावेश <यंत्र/processor.h>
#समावेश "internal.h"

व्योम proc_task_name(काष्ठा seq_file *m, काष्ठा task_काष्ठा *p, bool escape)
अणु
	अक्षर *buf;
	माप_प्रकार size;
	अक्षर tcomm[64];
	पूर्णांक ret;

	अगर (p->flags & PF_WQ_WORKER)
		wq_worker_comm(tcomm, माप(tcomm), p);
	अन्यथा
		__get_task_comm(tcomm, माप(tcomm), p);

	size = seq_get_buf(m, &buf);
	अगर (escape) अणु
		ret = string_escape_str(tcomm, buf, size,
					ESCAPE_SPACE | ESCAPE_SPECIAL, "\n\\");
		अगर (ret >= size)
			ret = -1;
	पूर्ण अन्यथा अणु
		ret = strscpy(buf, tcomm, size);
	पूर्ण

	seq_commit(m, ret);
पूर्ण

/*
 * The task state array is a strange "bitmap" of
 * reasons to sleep. Thus "running" is zero, and
 * you can test क्रम combinations of others with
 * simple bit tests.
 */
अटल स्थिर अक्षर * स्थिर task_state_array[] = अणु

	/* states in TASK_REPORT: */
	"R (running)",		/* 0x00 */
	"S (sleeping)",		/* 0x01 */
	"D (disk sleep)",	/* 0x02 */
	"T (stopped)",		/* 0x04 */
	"t (tracing stop)",	/* 0x08 */
	"X (dead)",		/* 0x10 */
	"Z (zombie)",		/* 0x20 */
	"P (parked)",		/* 0x40 */

	/* states beyond TASK_REPORT: */
	"I (idle)",		/* 0x80 */
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *get_task_state(काष्ठा task_काष्ठा *tsk)
अणु
	BUILD_BUG_ON(1 + ilog2(TASK_REPORT_MAX) != ARRAY_SIZE(task_state_array));
	वापस task_state_array[task_state_index(tsk)];
पूर्ण

अटल अंतरभूत व्योम task_state(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
				काष्ठा pid *pid, काष्ठा task_काष्ठा *p)
अणु
	काष्ठा user_namespace *user_ns = seq_user_ns(m);
	काष्ठा group_info *group_info;
	पूर्णांक g, umask = -1;
	काष्ठा task_काष्ठा *tracer;
	स्थिर काष्ठा cred *cred;
	pid_t ppid, tpid = 0, tgid, ngid;
	अचिन्हित पूर्णांक max_fds = 0;

	rcu_पढ़ो_lock();
	ppid = pid_alive(p) ?
		task_tgid_nr_ns(rcu_dereference(p->real_parent), ns) : 0;

	tracer = ptrace_parent(p);
	अगर (tracer)
		tpid = task_pid_nr_ns(tracer, ns);

	tgid = task_tgid_nr_ns(p, ns);
	ngid = task_numa_group_id(p);
	cred = get_task_cred(p);

	task_lock(p);
	अगर (p->fs)
		umask = p->fs->umask;
	अगर (p->files)
		max_fds = files_fdtable(p->files)->max_fds;
	task_unlock(p);
	rcu_पढ़ो_unlock();

	अगर (umask >= 0)
		seq_म_लिखो(m, "Umask:\t%#04o\n", umask);
	seq_माला_दो(m, "State:\t");
	seq_माला_दो(m, get_task_state(p));

	seq_put_decimal_ull(m, "\nTgid:\t", tgid);
	seq_put_decimal_ull(m, "\nNgid:\t", ngid);
	seq_put_decimal_ull(m, "\nPid:\t", pid_nr_ns(pid, ns));
	seq_put_decimal_ull(m, "\nPPid:\t", ppid);
	seq_put_decimal_ull(m, "\nTracerPid:\t", tpid);
	seq_put_decimal_ull(m, "\nUid:\t", from_kuid_munged(user_ns, cred->uid));
	seq_put_decimal_ull(m, "\t", from_kuid_munged(user_ns, cred->euid));
	seq_put_decimal_ull(m, "\t", from_kuid_munged(user_ns, cred->suid));
	seq_put_decimal_ull(m, "\t", from_kuid_munged(user_ns, cred->fsuid));
	seq_put_decimal_ull(m, "\nGid:\t", from_kgid_munged(user_ns, cred->gid));
	seq_put_decimal_ull(m, "\t", from_kgid_munged(user_ns, cred->egid));
	seq_put_decimal_ull(m, "\t", from_kgid_munged(user_ns, cred->sgid));
	seq_put_decimal_ull(m, "\t", from_kgid_munged(user_ns, cred->fsgid));
	seq_put_decimal_ull(m, "\nFDSize:\t", max_fds);

	seq_माला_दो(m, "\nGroups:\t");
	group_info = cred->group_info;
	क्रम (g = 0; g < group_info->ngroups; g++)
		seq_put_decimal_ull(m, g ? " " : "",
				from_kgid_munged(user_ns, group_info->gid[g]));
	put_cred(cred);
	/* Trailing space shouldn't have been added in the first place. */
	seq_अ_दो(m, ' ');

#अगर_घोषित CONFIG_PID_NS
	seq_माला_दो(m, "\nNStgid:");
	क्रम (g = ns->level; g <= pid->level; g++)
		seq_put_decimal_ull(m, "\t", task_tgid_nr_ns(p, pid->numbers[g].ns));
	seq_माला_दो(m, "\nNSpid:");
	क्रम (g = ns->level; g <= pid->level; g++)
		seq_put_decimal_ull(m, "\t", task_pid_nr_ns(p, pid->numbers[g].ns));
	seq_माला_दो(m, "\nNSpgid:");
	क्रम (g = ns->level; g <= pid->level; g++)
		seq_put_decimal_ull(m, "\t", task_pgrp_nr_ns(p, pid->numbers[g].ns));
	seq_माला_दो(m, "\nNSsid:");
	क्रम (g = ns->level; g <= pid->level; g++)
		seq_put_decimal_ull(m, "\t", task_session_nr_ns(p, pid->numbers[g].ns));
#पूर्ण_अगर
	seq_अ_दो(m, '\n');
पूर्ण

व्योम render_sigset_t(काष्ठा seq_file *m, स्थिर अक्षर *header,
				sigset_t *set)
अणु
	पूर्णांक i;

	seq_माला_दो(m, header);

	i = _NSIG;
	करो अणु
		पूर्णांक x = 0;

		i -= 4;
		अगर (sigismember(set, i+1)) x |= 1;
		अगर (sigismember(set, i+2)) x |= 2;
		अगर (sigismember(set, i+3)) x |= 4;
		अगर (sigismember(set, i+4)) x |= 8;
		seq_अ_दो(m, hex_asc[x]);
	पूर्ण जबतक (i >= 4);

	seq_अ_दो(m, '\n');
पूर्ण

अटल व्योम collect_sigign_sigcatch(काष्ठा task_काष्ठा *p, sigset_t *sigign,
				    sigset_t *sigcatch)
अणु
	काष्ठा k_sigaction *k;
	पूर्णांक i;

	k = p->sighand->action;
	क्रम (i = 1; i <= _NSIG; ++i, ++k) अणु
		अगर (k->sa.sa_handler == संक_छोड़ो)
			sigaddset(sigign, i);
		अन्यथा अगर (k->sa.sa_handler != संक_पूर्व)
			sigaddset(sigcatch, i);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम task_sig(काष्ठा seq_file *m, काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ flags;
	sigset_t pending, shpending, blocked, ignored, caught;
	पूर्णांक num_thपढ़ोs = 0;
	अचिन्हित पूर्णांक qsize = 0;
	अचिन्हित दीर्घ qlim = 0;

	sigemptyset(&pending);
	sigemptyset(&shpending);
	sigemptyset(&blocked);
	sigemptyset(&ignored);
	sigemptyset(&caught);

	अगर (lock_task_sighand(p, &flags)) अणु
		pending = p->pending.संकेत;
		shpending = p->संकेत->shared_pending.संकेत;
		blocked = p->blocked;
		collect_sigign_sigcatch(p, &ignored, &caught);
		num_thपढ़ोs = get_nr_thपढ़ोs(p);
		rcu_पढ़ो_lock();  /* FIXME: is this correct? */
		qsize = atomic_पढ़ो(&__task_cred(p)->user->संक_बाकी);
		rcu_पढ़ो_unlock();
		qlim = task_rlimit(p, RLIMIT_SIGPENDING);
		unlock_task_sighand(p, &flags);
	पूर्ण

	seq_put_decimal_ull(m, "Threads:\t", num_thपढ़ोs);
	seq_put_decimal_ull(m, "\nSigQ:\t", qsize);
	seq_put_decimal_ull(m, "/", qlim);

	/* render them all */
	render_sigset_t(m, "\nSigPnd:\t", &pending);
	render_sigset_t(m, "ShdPnd:\t", &shpending);
	render_sigset_t(m, "SigBlk:\t", &blocked);
	render_sigset_t(m, "SigIgn:\t", &ignored);
	render_sigset_t(m, "SigCgt:\t", &caught);
पूर्ण

अटल व्योम render_cap_t(काष्ठा seq_file *m, स्थिर अक्षर *header,
			kernel_cap_t *a)
अणु
	अचिन्हित __capi;

	seq_माला_दो(m, header);
	CAP_FOR_EACH_U32(__capi) अणु
		seq_put_hex_ll(m, शून्य,
			   a->cap[CAP_LAST_U32 - __capi], 8);
	पूर्ण
	seq_अ_दो(m, '\n');
पूर्ण

अटल अंतरभूत व्योम task_cap(काष्ठा seq_file *m, काष्ठा task_काष्ठा *p)
अणु
	स्थिर काष्ठा cred *cred;
	kernel_cap_t cap_inheritable, cap_permitted, cap_effective,
			cap_bset, cap_ambient;

	rcu_पढ़ो_lock();
	cred = __task_cred(p);
	cap_inheritable	= cred->cap_inheritable;
	cap_permitted	= cred->cap_permitted;
	cap_effective	= cred->cap_effective;
	cap_bset	= cred->cap_bset;
	cap_ambient	= cred->cap_ambient;
	rcu_पढ़ो_unlock();

	render_cap_t(m, "CapInh:\t", &cap_inheritable);
	render_cap_t(m, "CapPrm:\t", &cap_permitted);
	render_cap_t(m, "CapEff:\t", &cap_effective);
	render_cap_t(m, "CapBnd:\t", &cap_bset);
	render_cap_t(m, "CapAmb:\t", &cap_ambient);
पूर्ण

अटल अंतरभूत व्योम task_seccomp(काष्ठा seq_file *m, काष्ठा task_काष्ठा *p)
अणु
	seq_put_decimal_ull(m, "NoNewPrivs:\t", task_no_new_privs(p));
#अगर_घोषित CONFIG_SECCOMP
	seq_put_decimal_ull(m, "\nSeccomp:\t", p->seccomp.mode);
#अगर_घोषित CONFIG_SECCOMP_FILTER
	seq_put_decimal_ull(m, "\nSeccomp_filters:\t",
			    atomic_पढ़ो(&p->seccomp.filter_count));
#पूर्ण_अगर
#पूर्ण_अगर
	seq_माला_दो(m, "\nSpeculation_Store_Bypass:\t");
	चयन (arch_prctl_spec_ctrl_get(p, PR_SPEC_STORE_BYPASS)) अणु
	हाल -EINVAL:
		seq_माला_दो(m, "unknown");
		अवरोध;
	हाल PR_SPEC_NOT_AFFECTED:
		seq_माला_दो(m, "not vulnerable");
		अवरोध;
	हाल PR_SPEC_PRCTL | PR_SPEC_FORCE_DISABLE:
		seq_माला_दो(m, "thread force mitigated");
		अवरोध;
	हाल PR_SPEC_PRCTL | PR_SPEC_DISABLE:
		seq_माला_दो(m, "thread mitigated");
		अवरोध;
	हाल PR_SPEC_PRCTL | PR_SPEC_ENABLE:
		seq_माला_दो(m, "thread vulnerable");
		अवरोध;
	हाल PR_SPEC_DISABLE:
		seq_माला_दो(m, "globally mitigated");
		अवरोध;
	शेष:
		seq_माला_दो(m, "vulnerable");
		अवरोध;
	पूर्ण

	seq_माला_दो(m, "\nSpeculationIndirectBranch:\t");
	चयन (arch_prctl_spec_ctrl_get(p, PR_SPEC_INसूचीECT_BRANCH)) अणु
	हाल -EINVAL:
		seq_माला_दो(m, "unsupported");
		अवरोध;
	हाल PR_SPEC_NOT_AFFECTED:
		seq_माला_दो(m, "not affected");
		अवरोध;
	हाल PR_SPEC_PRCTL | PR_SPEC_FORCE_DISABLE:
		seq_माला_दो(m, "conditional force disabled");
		अवरोध;
	हाल PR_SPEC_PRCTL | PR_SPEC_DISABLE:
		seq_माला_दो(m, "conditional disabled");
		अवरोध;
	हाल PR_SPEC_PRCTL | PR_SPEC_ENABLE:
		seq_माला_दो(m, "conditional enabled");
		अवरोध;
	हाल PR_SPEC_ENABLE:
		seq_माला_दो(m, "always enabled");
		अवरोध;
	हाल PR_SPEC_DISABLE:
		seq_माला_दो(m, "always disabled");
		अवरोध;
	शेष:
		seq_माला_दो(m, "unknown");
		अवरोध;
	पूर्ण
	seq_अ_दो(m, '\n');
पूर्ण

अटल अंतरभूत व्योम task_context_चयन_counts(काष्ठा seq_file *m,
						काष्ठा task_काष्ठा *p)
अणु
	seq_put_decimal_ull(m, "voluntary_ctxt_switches:\t", p->nvcsw);
	seq_put_decimal_ull(m, "\nnonvoluntary_ctxt_switches:\t", p->nivcsw);
	seq_अ_दो(m, '\n');
पूर्ण

अटल व्योम task_cpus_allowed(काष्ठा seq_file *m, काष्ठा task_काष्ठा *task)
अणु
	seq_म_लिखो(m, "Cpus_allowed:\t%*pb\n",
		   cpumask_pr_args(&task->cpus_mask));
	seq_म_लिखो(m, "Cpus_allowed_list:\t%*pbl\n",
		   cpumask_pr_args(&task->cpus_mask));
पूर्ण

अटल अंतरभूत व्योम task_core_dumping(काष्ठा seq_file *m, काष्ठा mm_काष्ठा *mm)
अणु
	seq_put_decimal_ull(m, "CoreDumping:\t", !!mm->core_state);
	seq_अ_दो(m, '\n');
पूर्ण

अटल अंतरभूत व्योम task_thp_status(काष्ठा seq_file *m, काष्ठा mm_काष्ठा *mm)
अणु
	bool thp_enabled = IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE);

	अगर (thp_enabled)
		thp_enabled = !test_bit(MMF_DISABLE_THP, &mm->flags);
	seq_म_लिखो(m, "THP_enabled:\t%d\n", thp_enabled);
पूर्ण

पूर्णांक proc_pid_status(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
			काष्ठा pid *pid, काष्ठा task_काष्ठा *task)
अणु
	काष्ठा mm_काष्ठा *mm = get_task_mm(task);

	seq_माला_दो(m, "Name:\t");
	proc_task_name(m, task, true);
	seq_अ_दो(m, '\n');

	task_state(m, ns, pid, task);

	अगर (mm) अणु
		task_mem(m, mm);
		task_core_dumping(m, mm);
		task_thp_status(m, mm);
		mmput(mm);
	पूर्ण
	task_sig(m, task);
	task_cap(m, task);
	task_seccomp(m, task);
	task_cpus_allowed(m, task);
	cpuset_task_status_allowed(m, task);
	task_context_चयन_counts(m, task);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_task_stat(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
			काष्ठा pid *pid, काष्ठा task_काष्ठा *task, पूर्णांक whole)
अणु
	अचिन्हित दीर्घ vsize, eip, esp, wchan = 0;
	पूर्णांक priority, nice;
	पूर्णांक tty_pgrp = -1, tty_nr = 0;
	sigset_t sigign, sigcatch;
	अक्षर state;
	pid_t ppid = 0, pgid = -1, sid = -1;
	पूर्णांक num_thपढ़ोs = 0;
	पूर्णांक permitted;
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित दीर्घ दीर्घ start_समय;
	अचिन्हित दीर्घ cmin_flt = 0, cmaj_flt = 0;
	अचिन्हित दीर्घ  min_flt = 0,  maj_flt = 0;
	u64 cuसमय, csसमय, uसमय, sसमय;
	u64 cgसमय, gसमय;
	अचिन्हित दीर्घ rsslim = 0;
	अचिन्हित दीर्घ flags;

	state = *get_task_state(task);
	vsize = eip = esp = 0;
	permitted = ptrace_may_access(task, PTRACE_MODE_READ_FSCREDS | PTRACE_MODE_NOAUDIT);
	mm = get_task_mm(task);
	अगर (mm) अणु
		vsize = task_vsize(mm);
		/*
		 * esp and eip are पूर्णांकentionally zeroed out.  There is no
		 * non-racy way to पढ़ो them without मुक्तzing the task.
		 * Programs that need reliable values can use ptrace(2).
		 *
		 * The only exception is अगर the task is core dumping because
		 * a program is not able to use ptrace(2) in that हाल. It is
		 * safe because the task has stopped executing permanently.
		 */
		अगर (permitted && (task->flags & (PF_EXITING|PF_DUMPCORE))) अणु
			अगर (try_get_task_stack(task)) अणु
				eip = KSTK_EIP(task);
				esp = KSTK_ESP(task);
				put_task_stack(task);
			पूर्ण
		पूर्ण
	पूर्ण

	sigemptyset(&sigign);
	sigemptyset(&sigcatch);
	cuसमय = csसमय = uसमय = sसमय = 0;
	cgसमय = gसमय = 0;

	अगर (lock_task_sighand(task, &flags)) अणु
		काष्ठा संकेत_काष्ठा *sig = task->संकेत;

		अगर (sig->tty) अणु
			काष्ठा pid *pgrp = tty_get_pgrp(sig->tty);
			tty_pgrp = pid_nr_ns(pgrp, ns);
			put_pid(pgrp);
			tty_nr = new_encode_dev(tty_devnum(sig->tty));
		पूर्ण

		num_thपढ़ोs = get_nr_thपढ़ोs(task);
		collect_sigign_sigcatch(task, &sigign, &sigcatch);

		cmin_flt = sig->cmin_flt;
		cmaj_flt = sig->cmaj_flt;
		cuसमय = sig->cuसमय;
		csसमय = sig->csसमय;
		cgसमय = sig->cgसमय;
		rsslim = READ_ONCE(sig->rlim[RLIMIT_RSS].rlim_cur);

		/* add up live thपढ़ो stats at the group level */
		अगर (whole) अणु
			काष्ठा task_काष्ठा *t = task;
			करो अणु
				min_flt += t->min_flt;
				maj_flt += t->maj_flt;
				gसमय += task_gसमय(t);
			पूर्ण जबतक_each_thपढ़ो(task, t);

			min_flt += sig->min_flt;
			maj_flt += sig->maj_flt;
			thपढ़ो_group_cpuसमय_adjusted(task, &uसमय, &sसमय);
			gसमय += sig->gसमय;
		पूर्ण

		sid = task_session_nr_ns(task, ns);
		ppid = task_tgid_nr_ns(task->real_parent, ns);
		pgid = task_pgrp_nr_ns(task, ns);

		unlock_task_sighand(task, &flags);
	पूर्ण

	अगर (permitted && (!whole || num_thपढ़ोs < 2))
		wchan = get_wchan(task);
	अगर (!whole) अणु
		min_flt = task->min_flt;
		maj_flt = task->maj_flt;
		task_cpuसमय_adjusted(task, &uसमय, &sसमय);
		gसमय = task_gसमय(task);
	पूर्ण

	/* scale priority and nice values from बारlices to -20..20 */
	/* to make it look like a "normal" Unix priority/nice value  */
	priority = task_prio(task);
	nice = task_nice(task);

	/* apply समयns offset क्रम bootसमय and convert nsec -> ticks */
	start_समय =
		nsec_to_घड़ी_प्रकार(समयns_add_bootसमय_ns(task->start_bootसमय));

	seq_put_decimal_ull(m, "", pid_nr_ns(pid, ns));
	seq_माला_दो(m, " (");
	proc_task_name(m, task, false);
	seq_माला_दो(m, ") ");
	seq_अ_दो(m, state);
	seq_put_decimal_ll(m, " ", ppid);
	seq_put_decimal_ll(m, " ", pgid);
	seq_put_decimal_ll(m, " ", sid);
	seq_put_decimal_ll(m, " ", tty_nr);
	seq_put_decimal_ll(m, " ", tty_pgrp);
	seq_put_decimal_ull(m, " ", task->flags);
	seq_put_decimal_ull(m, " ", min_flt);
	seq_put_decimal_ull(m, " ", cmin_flt);
	seq_put_decimal_ull(m, " ", maj_flt);
	seq_put_decimal_ull(m, " ", cmaj_flt);
	seq_put_decimal_ull(m, " ", nsec_to_घड़ी_प्रकार(uसमय));
	seq_put_decimal_ull(m, " ", nsec_to_घड़ी_प्रकार(sसमय));
	seq_put_decimal_ll(m, " ", nsec_to_घड़ी_प्रकार(cuसमय));
	seq_put_decimal_ll(m, " ", nsec_to_घड़ी_प्रकार(csसमय));
	seq_put_decimal_ll(m, " ", priority);
	seq_put_decimal_ll(m, " ", nice);
	seq_put_decimal_ll(m, " ", num_thपढ़ोs);
	seq_put_decimal_ull(m, " ", 0);
	seq_put_decimal_ull(m, " ", start_समय);
	seq_put_decimal_ull(m, " ", vsize);
	seq_put_decimal_ull(m, " ", mm ? get_mm_rss(mm) : 0);
	seq_put_decimal_ull(m, " ", rsslim);
	seq_put_decimal_ull(m, " ", mm ? (permitted ? mm->start_code : 1) : 0);
	seq_put_decimal_ull(m, " ", mm ? (permitted ? mm->end_code : 1) : 0);
	seq_put_decimal_ull(m, " ", (permitted && mm) ? mm->start_stack : 0);
	seq_put_decimal_ull(m, " ", esp);
	seq_put_decimal_ull(m, " ", eip);
	/* The संकेत inक्रमmation here is obsolete.
	 * It must be decimal क्रम Linux 2.0 compatibility.
	 * Use /proc/#/status क्रम real-समय संकेतs.
	 */
	seq_put_decimal_ull(m, " ", task->pending.संकेत.sig[0] & 0x7fffffffUL);
	seq_put_decimal_ull(m, " ", task->blocked.sig[0] & 0x7fffffffUL);
	seq_put_decimal_ull(m, " ", sigign.sig[0] & 0x7fffffffUL);
	seq_put_decimal_ull(m, " ", sigcatch.sig[0] & 0x7fffffffUL);

	/*
	 * We used to output the असलolute kernel address, but that's an
	 * inक्रमmation leak - so instead we show a 0/1 flag here, to संकेत
	 * to user-space whether there's a wchan field in /proc/PID/wchan.
	 *
	 * This works with older implementations of procps as well.
	 */
	अगर (wchan)
		seq_माला_दो(m, " 1");
	अन्यथा
		seq_माला_दो(m, " 0");

	seq_put_decimal_ull(m, " ", 0);
	seq_put_decimal_ull(m, " ", 0);
	seq_put_decimal_ll(m, " ", task->निकास_संकेत);
	seq_put_decimal_ll(m, " ", task_cpu(task));
	seq_put_decimal_ull(m, " ", task->rt_priority);
	seq_put_decimal_ull(m, " ", task->policy);
	seq_put_decimal_ull(m, " ", delayacct_blkio_ticks(task));
	seq_put_decimal_ull(m, " ", nsec_to_घड़ी_प्रकार(gसमय));
	seq_put_decimal_ll(m, " ", nsec_to_घड़ी_प्रकार(cgसमय));

	अगर (mm && permitted) अणु
		seq_put_decimal_ull(m, " ", mm->start_data);
		seq_put_decimal_ull(m, " ", mm->end_data);
		seq_put_decimal_ull(m, " ", mm->start_brk);
		seq_put_decimal_ull(m, " ", mm->arg_start);
		seq_put_decimal_ull(m, " ", mm->arg_end);
		seq_put_decimal_ull(m, " ", mm->env_start);
		seq_put_decimal_ull(m, " ", mm->env_end);
	पूर्ण अन्यथा
		seq_माला_दो(m, " 0 0 0 0 0 0 0");

	अगर (permitted)
		seq_put_decimal_ll(m, " ", task->निकास_code);
	अन्यथा
		seq_माला_दो(m, " 0");

	seq_अ_दो(m, '\n');
	अगर (mm)
		mmput(mm);
	वापस 0;
पूर्ण

पूर्णांक proc_tid_stat(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
			काष्ठा pid *pid, काष्ठा task_काष्ठा *task)
अणु
	वापस करो_task_stat(m, ns, pid, task, 0);
पूर्ण

पूर्णांक proc_tgid_stat(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
			काष्ठा pid *pid, काष्ठा task_काष्ठा *task)
अणु
	वापस करो_task_stat(m, ns, pid, task, 1);
पूर्ण

पूर्णांक proc_pid_staपंचांग(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
			काष्ठा pid *pid, काष्ठा task_काष्ठा *task)
अणु
	काष्ठा mm_काष्ठा *mm = get_task_mm(task);

	अगर (mm) अणु
		अचिन्हित दीर्घ size;
		अचिन्हित दीर्घ resident = 0;
		अचिन्हित दीर्घ shared = 0;
		अचिन्हित दीर्घ text = 0;
		अचिन्हित दीर्घ data = 0;

		size = task_staपंचांग(mm, &shared, &text, &data, &resident);
		mmput(mm);

		/*
		 * For quick पढ़ो, खोलो code by putting numbers directly
		 * expected क्रमmat is
		 * seq_म_लिखो(m, "%lu %lu %lu %lu 0 %lu 0\n",
		 *               size, resident, shared, text, data);
		 */
		seq_put_decimal_ull(m, "", size);
		seq_put_decimal_ull(m, " ", resident);
		seq_put_decimal_ull(m, " ", shared);
		seq_put_decimal_ull(m, " ", text);
		seq_put_decimal_ull(m, " ", 0);
		seq_put_decimal_ull(m, " ", data);
		seq_put_decimal_ull(m, " ", 0);
		seq_अ_दो(m, '\n');
	पूर्ण अन्यथा अणु
		seq_ग_लिखो(m, "0 0 0 0 0 0 0\n", 14);
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PROC_CHILDREN
अटल काष्ठा pid *
get_children_pid(काष्ठा inode *inode, काष्ठा pid *pid_prev, loff_t pos)
अणु
	काष्ठा task_काष्ठा *start, *task;
	काष्ठा pid *pid = शून्य;

	पढ़ो_lock(&tasklist_lock);

	start = pid_task(proc_pid(inode), PIDTYPE_PID);
	अगर (!start)
		जाओ out;

	/*
	 * Lets try to जारी searching first, this gives
	 * us signअगरicant speedup on children-rich processes.
	 */
	अगर (pid_prev) अणु
		task = pid_task(pid_prev, PIDTYPE_PID);
		अगर (task && task->real_parent == start &&
		    !(list_empty(&task->sibling))) अणु
			अगर (list_is_last(&task->sibling, &start->children))
				जाओ out;
			task = list_first_entry(&task->sibling,
						काष्ठा task_काष्ठा, sibling);
			pid = get_pid(task_pid(task));
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * Slow search हाल.
	 *
	 * We might miss some children here अगर children
	 * are निकासed जबतक we were not holding the lock,
	 * but it was never promised to be accurate that
	 * much.
	 *
	 * "Just suppose that the parent sleeps, but N children
	 *  निकास after we prपूर्णांकed their tids. Now the slow paths
	 *  skips N extra children, we miss N tasks." (c)
	 *
	 * So one need to stop or मुक्तze the leader and all
	 * its children to get a precise result.
	 */
	list_क्रम_each_entry(task, &start->children, sibling) अणु
		अगर (pos-- == 0) अणु
			pid = get_pid(task_pid(task));
			अवरोध;
		पूर्ण
	पूर्ण

out:
	पढ़ो_unlock(&tasklist_lock);
	वापस pid;
पूर्ण

अटल पूर्णांक children_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा inode *inode = file_inode(seq->file);

	seq_म_लिखो(seq, "%d ", pid_nr_ns(v, proc_pid_ns(inode->i_sb)));
	वापस 0;
पूर्ण

अटल व्योम *children_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	वापस get_children_pid(file_inode(seq->file), शून्य, *pos);
पूर्ण

अटल व्योम *children_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा pid *pid;

	pid = get_children_pid(file_inode(seq->file), v, *pos + 1);
	put_pid(v);

	++*pos;
	वापस pid;
पूर्ण

अटल व्योम children_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	put_pid(v);
पूर्ण

अटल स्थिर काष्ठा seq_operations children_seq_ops = अणु
	.start	= children_seq_start,
	.next	= children_seq_next,
	.stop	= children_seq_stop,
	.show	= children_seq_show,
पूर्ण;

अटल पूर्णांक children_seq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &children_seq_ops);
पूर्ण

स्थिर काष्ठा file_operations proc_tid_children_operations = अणु
	.खोलो    = children_seq_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PROC_CHILDREN */
