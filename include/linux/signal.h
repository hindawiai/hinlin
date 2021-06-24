<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SIGNAL_H
#घोषणा _LINUX_SIGNAL_H

#समावेश <linux/bug.h>
#समावेश <linux/संकेत_types.h>
#समावेश <linux/माला.स>

काष्ठा task_काष्ठा;

/* क्रम sysctl */
बाह्य पूर्णांक prपूर्णांक_fatal_संकेतs;

अटल अंतरभूत व्योम copy_siginfo(kernel_siginfo_t *to,
				स्थिर kernel_siginfo_t *from)
अणु
	स_नकल(to, from, माप(*to));
पूर्ण

अटल अंतरभूत व्योम clear_siginfo(kernel_siginfo_t *info)
अणु
	स_रखो(info, 0, माप(*info));
पूर्ण

#घोषणा SI_EXPANSION_SIZE (माप(काष्ठा siginfo) - माप(काष्ठा kernel_siginfo))

अटल अंतरभूत व्योम copy_siginfo_to_बाह्यal(siginfo_t *to,
					    स्थिर kernel_siginfo_t *from)
अणु
	स_नकल(to, from, माप(*from));
	स_रखो(((अक्षर *)to) + माप(काष्ठा kernel_siginfo), 0,
		SI_EXPANSION_SIZE);
पूर्ण

पूर्णांक copy_siginfo_to_user(siginfo_t __user *to, स्थिर kernel_siginfo_t *from);
पूर्णांक copy_siginfo_from_user(kernel_siginfo_t *to, स्थिर siginfo_t __user *from);

क्रमागत siginfo_layout अणु
	SIL_KILL,
	SIL_TIMER,
	SIL_POLL,
	SIL_FAULT,
	SIL_FAULT_TRAPNO,
	SIL_FAULT_MCEERR,
	SIL_FAULT_BNDERR,
	SIL_FAULT_PKUERR,
	SIL_PERF_EVENT,
	SIL_CHLD,
	SIL_RT,
	SIL_SYS,
पूर्ण;

क्रमागत siginfo_layout siginfo_layout(अचिन्हित sig, पूर्णांक si_code);

/*
 * Define some primitives to manipulate sigset_t.
 */

#अगर_अघोषित __HAVE_ARCH_SIG_BITOPS
#समावेश <linux/bitops.h>

/* We करोn't use <linux/bitops.h> क्रम these because there is no need to
   be atomic.  */
अटल अंतरभूत व्योम sigaddset(sigset_t *set, पूर्णांक _sig)
अणु
	अचिन्हित दीर्घ sig = _sig - 1;
	अगर (_NSIG_WORDS == 1)
		set->sig[0] |= 1UL << sig;
	अन्यथा
		set->sig[sig / _NSIG_BPW] |= 1UL << (sig % _NSIG_BPW);
पूर्ण

अटल अंतरभूत व्योम sigdअन्यथाt(sigset_t *set, पूर्णांक _sig)
अणु
	अचिन्हित दीर्घ sig = _sig - 1;
	अगर (_NSIG_WORDS == 1)
		set->sig[0] &= ~(1UL << sig);
	अन्यथा
		set->sig[sig / _NSIG_BPW] &= ~(1UL << (sig % _NSIG_BPW));
पूर्ण

अटल अंतरभूत पूर्णांक sigismember(sigset_t *set, पूर्णांक _sig)
अणु
	अचिन्हित दीर्घ sig = _sig - 1;
	अगर (_NSIG_WORDS == 1)
		वापस 1 & (set->sig[0] >> sig);
	अन्यथा
		वापस 1 & (set->sig[sig / _NSIG_BPW] >> (sig % _NSIG_BPW));
पूर्ण

#पूर्ण_अगर /* __HAVE_ARCH_SIG_BITOPS */

अटल अंतरभूत पूर्णांक sigisemptyset(sigset_t *set)
अणु
	चयन (_NSIG_WORDS) अणु
	हाल 4:
		वापस (set->sig[3] | set->sig[2] |
			set->sig[1] | set->sig[0]) == 0;
	हाल 2:
		वापस (set->sig[1] | set->sig[0]) == 0;
	हाल 1:
		वापस set->sig[0] == 0;
	शेष:
		BUILD_BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक sigequalsets(स्थिर sigset_t *set1, स्थिर sigset_t *set2)
अणु
	चयन (_NSIG_WORDS) अणु
	हाल 4:
		वापस	(set1->sig[3] == set2->sig[3]) &&
			(set1->sig[2] == set2->sig[2]) &&
			(set1->sig[1] == set2->sig[1]) &&
			(set1->sig[0] == set2->sig[0]);
	हाल 2:
		वापस	(set1->sig[1] == set2->sig[1]) &&
			(set1->sig[0] == set2->sig[0]);
	हाल 1:
		वापस	set1->sig[0] == set2->sig[0];
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा sigmask(sig)	(1UL << ((sig) - 1))

#अगर_अघोषित __HAVE_ARCH_SIG_SETOPS
#समावेश <linux/माला.स>

#घोषणा _SIG_SET_BINOP(name, op)					\
अटल अंतरभूत व्योम name(sigset_t *r, स्थिर sigset_t *a, स्थिर sigset_t *b) \
अणु									\
	अचिन्हित दीर्घ a0, a1, a2, a3, b0, b1, b2, b3;			\
									\
	चयन (_NSIG_WORDS) अणु						\
	हाल 4:								\
		a3 = a->sig[3]; a2 = a->sig[2];				\
		b3 = b->sig[3]; b2 = b->sig[2];				\
		r->sig[3] = op(a3, b3);					\
		r->sig[2] = op(a2, b2);					\
		fallthrough;						\
	हाल 2:								\
		a1 = a->sig[1]; b1 = b->sig[1];				\
		r->sig[1] = op(a1, b1);					\
		fallthrough;						\
	हाल 1:								\
		a0 = a->sig[0]; b0 = b->sig[0];				\
		r->sig[0] = op(a0, b0);					\
		अवरोध;							\
	शेष:							\
		BUILD_BUG();						\
	पूर्ण								\
पूर्ण

#घोषणा _sig_or(x,y)	((x) | (y))
_SIG_SET_BINOP(sigorsets, _sig_or)

#घोषणा _sig_and(x,y)	((x) & (y))
_SIG_SET_BINOP(sigandsets, _sig_and)

#घोषणा _sig_andn(x,y)	((x) & ~(y))
_SIG_SET_BINOP(sigandnsets, _sig_andn)

#अघोषित _SIG_SET_BINOP
#अघोषित _sig_or
#अघोषित _sig_and
#अघोषित _sig_andn

#घोषणा _SIG_SET_OP(name, op)						\
अटल अंतरभूत व्योम name(sigset_t *set)					\
अणु									\
	चयन (_NSIG_WORDS) अणु						\
	हाल 4:	set->sig[3] = op(set->sig[3]);				\
		set->sig[2] = op(set->sig[2]);				\
		fallthrough;						\
	हाल 2:	set->sig[1] = op(set->sig[1]);				\
		fallthrough;						\
	हाल 1:	set->sig[0] = op(set->sig[0]);				\
		    अवरोध;						\
	शेष:							\
		BUILD_BUG();						\
	पूर्ण								\
पूर्ण

#घोषणा _sig_not(x)	(~(x))
_SIG_SET_OP(signotset, _sig_not)

#अघोषित _SIG_SET_OP
#अघोषित _sig_not

अटल अंतरभूत व्योम sigemptyset(sigset_t *set)
अणु
	चयन (_NSIG_WORDS) अणु
	शेष:
		स_रखो(set, 0, माप(sigset_t));
		अवरोध;
	हाल 2: set->sig[1] = 0;
		fallthrough;
	हाल 1:	set->sig[0] = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sigfillset(sigset_t *set)
अणु
	चयन (_NSIG_WORDS) अणु
	शेष:
		स_रखो(set, -1, माप(sigset_t));
		अवरोध;
	हाल 2: set->sig[1] = -1;
		fallthrough;
	हाल 1:	set->sig[0] = -1;
		अवरोध;
	पूर्ण
पूर्ण

/* Some extensions क्रम manipulating the low 32 संकेतs in particular.  */

अटल अंतरभूत व्योम sigaddseपंचांगask(sigset_t *set, अचिन्हित दीर्घ mask)
अणु
	set->sig[0] |= mask;
पूर्ण

अटल अंतरभूत व्योम sigdअन्यथापंचांगask(sigset_t *set, अचिन्हित दीर्घ mask)
अणु
	set->sig[0] &= ~mask;
पूर्ण

अटल अंतरभूत पूर्णांक sigtestseपंचांगask(sigset_t *set, अचिन्हित दीर्घ mask)
अणु
	वापस (set->sig[0] & mask) != 0;
पूर्ण

अटल अंतरभूत व्योम siginitset(sigset_t *set, अचिन्हित दीर्घ mask)
अणु
	set->sig[0] = mask;
	चयन (_NSIG_WORDS) अणु
	शेष:
		स_रखो(&set->sig[1], 0, माप(दीर्घ)*(_NSIG_WORDS-1));
		अवरोध;
	हाल 2: set->sig[1] = 0;
		अवरोध;
	हाल 1: ;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम siginitsetinv(sigset_t *set, अचिन्हित दीर्घ mask)
अणु
	set->sig[0] = ~mask;
	चयन (_NSIG_WORDS) अणु
	शेष:
		स_रखो(&set->sig[1], -1, माप(दीर्घ)*(_NSIG_WORDS-1));
		अवरोध;
	हाल 2: set->sig[1] = -1;
		अवरोध;
	हाल 1: ;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* __HAVE_ARCH_SIG_SETOPS */

अटल अंतरभूत व्योम init_संक_बाकी(काष्ठा संक_बाकी *sig)
अणु
	sigemptyset(&sig->संकेत);
	INIT_LIST_HEAD(&sig->list);
पूर्ण

बाह्य व्योम flush_sigqueue(काष्ठा संक_बाकी *queue);
बाह्य व्योम निकास_task_sigqueue_cache(काष्ठा task_काष्ठा *tsk);

/* Test अगर 'sig' is valid संकेत. Use this instead of testing _NSIG directly */
अटल अंतरभूत पूर्णांक valid_संकेत(अचिन्हित दीर्घ sig)
अणु
	वापस sig <= _NSIG ? 1 : 0;
पूर्ण

काष्ठा बारpec;
काष्ठा pt_regs;
क्रमागत pid_type;

बाह्य पूर्णांक next_संकेत(काष्ठा संक_बाकी *pending, sigset_t *mask);
बाह्य पूर्णांक करो_send_sig_info(पूर्णांक sig, काष्ठा kernel_siginfo *info,
				काष्ठा task_काष्ठा *p, क्रमागत pid_type type);
बाह्य पूर्णांक group_send_sig_info(पूर्णांक sig, काष्ठा kernel_siginfo *info,
			       काष्ठा task_काष्ठा *p, क्रमागत pid_type type);
बाह्य पूर्णांक __group_send_sig_info(पूर्णांक, काष्ठा kernel_siginfo *, काष्ठा task_काष्ठा *);
बाह्य पूर्णांक sigprocmask(पूर्णांक, sigset_t *, sigset_t *);
बाह्य व्योम set_current_blocked(sigset_t *);
बाह्य व्योम __set_current_blocked(स्थिर sigset_t *);
बाह्य पूर्णांक show_unhandled_संकेतs;

बाह्य bool get_संकेत(काष्ठा kसंकेत *ksig);
बाह्य व्योम संकेत_setup_करोne(पूर्णांक failed, काष्ठा kसंकेत *ksig, पूर्णांक stepping);
बाह्य व्योम निकास_संकेतs(काष्ठा task_काष्ठा *tsk);
बाह्य व्योम kernel_sigaction(पूर्णांक, __sighandler_t);

#घोषणा SIG_KTHREAD ((__क्रमce __sighandler_t)2)
#घोषणा SIG_KTHREAD_KERNEL ((__क्रमce __sighandler_t)3)

अटल अंतरभूत व्योम allow_संकेत(पूर्णांक sig)
अणु
	/*
	 * Kernel thपढ़ोs handle their own संकेतs. Let the संकेत code
	 * know it'll be handled, so that they don't get converted to
	 * SIGKILL or just silently dropped.
	 */
	kernel_sigaction(sig, SIG_KTHREAD);
पूर्ण

अटल अंतरभूत व्योम allow_kernel_संकेत(पूर्णांक sig)
अणु
	/*
	 * Kernel thपढ़ोs handle their own संकेतs. Let the संकेत code
	 * know संकेतs sent by the kernel will be handled, so that they
	 * करोn't get silently dropped.
	 */
	kernel_sigaction(sig, SIG_KTHREAD_KERNEL);
पूर्ण

अटल अंतरभूत व्योम disallow_संकेत(पूर्णांक sig)
अणु
	kernel_sigaction(sig, संक_छोड़ो);
पूर्ण

बाह्य काष्ठा kmem_cache *sighand_cachep;

बाह्य bool unhandled_संकेत(काष्ठा task_काष्ठा *tsk, पूर्णांक sig);

/*
 * In POSIX a संकेत is sent either to a specअगरic thपढ़ो (Linux task)
 * or to the process as a whole (Linux thपढ़ो group).  How the संकेत
 * is sent determines whether it's to one thपढ़ो or the whole group,
 * which determines which संकेत mask(s) are involved in blocking it
 * from being delivered until later.  When the संकेत is delivered,
 * either it's caught or ignored by a user handler or it has a शेष
 * effect that applies to the whole thपढ़ो group (POSIX process).
 *
 * The possible effects an unblocked संकेत set to संक_पूर्व can have are:
 *   ignore	- Nothing Happens
 *   terminate	- समाप्त the process, i.e. all thपढ़ोs in the group,
 * 		  similar to निकास_group.  The group leader (only) reports
 *		  WIFSIGNALED status to its parent.
 *   coredump	- ग_लिखो a core dump file describing all thपढ़ोs using
 *		  the same mm and then समाप्त all those thपढ़ोs
 *   stop 	- stop all the thपढ़ोs in the group, i.e. TASK_STOPPED state
 *
 * SIGKILL and SIGSTOP cannot be caught, blocked, or ignored.
 * Other संकेतs when not blocked and set to संक_पूर्व behaves as follows.
 * The job control संकेतs also have other special effects.
 *
 *	+--------------------+------------------+
 *	|  POSIX संकेत      |  शेष action  |
 *	+--------------------+------------------+
 *	|  SIGHUP            |  terminate	|
 *	|  संक_विघ्न            |	terminate	|
 *	|  SIGQUIT           |	coredump 	|
 *	|  संक_अवैध            |	coredump 	|
 *	|  SIGTRAP           |	coredump 	|
 *	|  SIGABRT/SIGIOT    |	coredump 	|
 *	|  SIGBUS            |	coredump 	|
 *	|  संक_भ_त्रुटि            |	coredump 	|
 *	|  SIGKILL           |	terminate(+)	|
 *	|  SIGUSR1           |	terminate	|
 *	|  संक_अंश           |	coredump 	|
 *	|  SIGUSR2           |	terminate	|
 *	|  SIGPIPE           |	terminate	|
 *	|  SIGALRM           |	terminate	|
 *	|  संक_इति           |	terminate	|
 *	|  SIGCHLD           |	ignore   	|
 *	|  SIGCONT           |	ignore(*)	|
 *	|  SIGSTOP           |	stop(*)(+)  	|
 *	|  SIGTSTP           |	stop(*)  	|
 *	|  SIGTTIN           |	stop(*)  	|
 *	|  SIGTTOU           |	stop(*)  	|
 *	|  SIGURG            |	ignore   	|
 *	|  SIGXCPU           |	coredump 	|
 *	|  SIGXFSZ           |	coredump 	|
 *	|  SIGVTALRM         |	terminate	|
 *	|  SIGPROF           |	terminate	|
 *	|  SIGPOLL/SIGIO     |	terminate	|
 *	|  SIGSYS/SIGUNUSED  |	coredump 	|
 *	|  SIGSTKFLT         |	terminate	|
 *	|  SIGWINCH          |	ignore   	|
 *	|  SIGPWR            |	terminate	|
 *	|  SIGRTMIN-SIGRTMAX |	terminate       |
 *	+--------------------+------------------+
 *	|  non-POSIX संकेत  |  शेष action  |
 *	+--------------------+------------------+
 *	|  SIGEMT            |  coredump	|
 *	+--------------------+------------------+
 *
 * (+) For SIGKILL and SIGSTOP the action is "always", not just "default".
 * (*) Special job control effects:
 * When SIGCONT is sent, it resumes the process (all thपढ़ोs in the group)
 * from TASK_STOPPED state and also clears any pending/queued stop संकेतs
 * (any of those marked with "stop(*)").  This happens regardless of blocking,
 * catching, or ignoring SIGCONT.  When any stop संकेत is sent, it clears
 * any pending/queued SIGCONT संकेतs; this happens regardless of blocking,
 * catching, or ignored the stop संकेत, though (except क्रम SIGSTOP) the
 * शेष action of stopping the process may happen later or never.
 */

#अगर_घोषित SIGEMT
#घोषणा SIGEMT_MASK	rt_sigmask(SIGEMT)
#अन्यथा
#घोषणा SIGEMT_MASK	0
#पूर्ण_अगर

#अगर SIGRTMIN > BITS_PER_LONG
#घोषणा rt_sigmask(sig)	(1ULL << ((sig)-1))
#अन्यथा
#घोषणा rt_sigmask(sig)	sigmask(sig)
#पूर्ण_अगर

#घोषणा siginmask(sig, mask) \
	((sig) > 0 && (sig) < SIGRTMIN && (rt_sigmask(sig) & (mask)))

#घोषणा SIG_KERNEL_ONLY_MASK (\
	rt_sigmask(SIGKILL)   |  rt_sigmask(SIGSTOP))

#घोषणा SIG_KERNEL_STOP_MASK (\
	rt_sigmask(SIGSTOP)   |  rt_sigmask(SIGTSTP)   | \
	rt_sigmask(SIGTTIN)   |  rt_sigmask(SIGTTOU)   )

#घोषणा SIG_KERNEL_COREDUMP_MASK (\
        rt_sigmask(SIGQUIT)   |  rt_sigmask(संक_अवैध)    | \
	rt_sigmask(SIGTRAP)   |  rt_sigmask(SIGABRT)   | \
        rt_sigmask(संक_भ_त्रुटि)    |  rt_sigmask(संक_अंश)   | \
	rt_sigmask(SIGBUS)    |  rt_sigmask(SIGSYS)    | \
        rt_sigmask(SIGXCPU)   |  rt_sigmask(SIGXFSZ)   | \
	SIGEMT_MASK				       )

#घोषणा SIG_KERNEL_IGNORE_MASK (\
        rt_sigmask(SIGCONT)   |  rt_sigmask(SIGCHLD)   | \
	rt_sigmask(SIGWINCH)  |  rt_sigmask(SIGURG)    )

#घोषणा SIG_SPECIFIC_SICODES_MASK (\
	rt_sigmask(संक_अवैध)    |  rt_sigmask(संक_भ_त्रुटि)    | \
	rt_sigmask(संक_अंश)   |  rt_sigmask(SIGBUS)    | \
	rt_sigmask(SIGTRAP)   |  rt_sigmask(SIGCHLD)   | \
	rt_sigmask(SIGPOLL)   |  rt_sigmask(SIGSYS)    | \
	SIGEMT_MASK                                    )

#घोषणा sig_kernel_only(sig)		siginmask(sig, SIG_KERNEL_ONLY_MASK)
#घोषणा sig_kernel_coredump(sig)	siginmask(sig, SIG_KERNEL_COREDUMP_MASK)
#घोषणा sig_kernel_ignore(sig)		siginmask(sig, SIG_KERNEL_IGNORE_MASK)
#घोषणा sig_kernel_stop(sig)		siginmask(sig, SIG_KERNEL_STOP_MASK)
#घोषणा sig_specअगरic_sicodes(sig)	siginmask(sig, SIG_SPECIFIC_SICODES_MASK)

#घोषणा sig_fatal(t, signr) \
	(!siginmask(signr, SIG_KERNEL_IGNORE_MASK|SIG_KERNEL_STOP_MASK) && \
	 (t)->sighand->action[(signr)-1].sa.sa_handler == संक_पूर्व)

व्योम संकेतs_init(व्योम);

पूर्णांक restore_altstack(स्थिर stack_t __user *);
पूर्णांक __save_altstack(stack_t __user *, अचिन्हित दीर्घ);

#घोषणा unsafe_save_altstack(uss, sp, label) करो अणु \
	stack_t __user *__uss = uss; \
	काष्ठा task_काष्ठा *t = current; \
	unsafe_put_user((व्योम __user *)t->sas_ss_sp, &__uss->ss_sp, label); \
	unsafe_put_user(t->sas_ss_flags, &__uss->ss_flags, label); \
	unsafe_put_user(t->sas_ss_size, &__uss->ss_size, label); \
	अगर (t->sas_ss_flags & SS_AUTODISARM) \
		sas_ss_reset(t); \
पूर्ण जबतक (0);

#अगर_घोषित CONFIG_PROC_FS
काष्ठा seq_file;
बाह्य व्योम render_sigset_t(काष्ठा seq_file *, स्थिर अक्षर *, sigset_t *);
#पूर्ण_अगर

#अगर_अघोषित arch_untagged_si_addr
/*
 * Given a fault address and a संकेत and si_code which correspond to the
 * _sigfault जोड़ member, वापसs the address that must appear in si_addr अगर
 * the संकेत handler करोes not have SA_EXPOSE_TAGBITS enabled in sa_flags.
 */
अटल अंतरभूत व्योम __user *arch_untagged_si_addr(व्योम __user *addr,
						 अचिन्हित दीर्घ sig,
						 अचिन्हित दीर्घ si_code)
अणु
	वापस addr;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_SIGNAL_H */
