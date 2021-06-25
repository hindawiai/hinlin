<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/kernel/compat.c
 *
 *  Kernel compatibililty routines क्रम e.g. 32 bit syscall support
 *  on 64 bit kernels.
 *
 *  Copyright (C) 2002-2003 Stephen Rothwell, IBM Corporation
 */

#समावेश <linux/linkage.h>
#समावेश <linux/compat.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समय.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>	/* क्रम MAX_SCHEDULE_TIMEOUT */
#समावेश <linux/syscalls.h>
#समावेश <linux/unistd.h>
#समावेश <linux/security.h>
#समावेश <linux/export.h>
#समावेश <linux/migrate.h>
#समावेश <linux/posix-समयrs.h>
#समावेश <linux/बार.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/gfp.h>

#समावेश <linux/uaccess.h>

#अगर_घोषित __ARCH_WANT_SYS_SIGPROCMASK

/*
 * sys_sigprocmask SIG_SETMASK sets the first (compat) word of the
 * blocked set of संकेतs to the supplied संकेत set
 */
अटल अंतरभूत व्योम compat_sig_seपंचांगask(sigset_t *blocked, compat_sigset_word set)
अणु
	स_नकल(blocked->sig, &set, माप(set));
पूर्ण

COMPAT_SYSCALL_DEFINE3(sigprocmask, पूर्णांक, how,
		       compat_old_sigset_t __user *, nset,
		       compat_old_sigset_t __user *, oset)
अणु
	old_sigset_t old_set, new_set;
	sigset_t new_blocked;

	old_set = current->blocked.sig[0];

	अगर (nset) अणु
		अगर (get_user(new_set, nset))
			वापस -EFAULT;
		new_set &= ~(sigmask(SIGKILL) | sigmask(SIGSTOP));

		new_blocked = current->blocked;

		चयन (how) अणु
		हाल SIG_BLOCK:
			sigaddseपंचांगask(&new_blocked, new_set);
			अवरोध;
		हाल SIG_UNBLOCK:
			sigdअन्यथापंचांगask(&new_blocked, new_set);
			अवरोध;
		हाल SIG_SETMASK:
			compat_sig_seपंचांगask(&new_blocked, new_set);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		set_current_blocked(&new_blocked);
	पूर्ण

	अगर (oset) अणु
		अगर (put_user(old_set, oset))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर

पूर्णांक put_compat_rusage(स्थिर काष्ठा rusage *r, काष्ठा compat_rusage __user *ru)
अणु
	काष्ठा compat_rusage r32;
	स_रखो(&r32, 0, माप(r32));
	r32.ru_uसमय.tv_sec = r->ru_uसमय.tv_sec;
	r32.ru_uसमय.tv_usec = r->ru_uसमय.tv_usec;
	r32.ru_sसमय.tv_sec = r->ru_sसमय.tv_sec;
	r32.ru_sसमय.tv_usec = r->ru_sसमय.tv_usec;
	r32.ru_maxrss = r->ru_maxrss;
	r32.ru_ixrss = r->ru_ixrss;
	r32.ru_idrss = r->ru_idrss;
	r32.ru_isrss = r->ru_isrss;
	r32.ru_minflt = r->ru_minflt;
	r32.ru_majflt = r->ru_majflt;
	r32.ru_nswap = r->ru_nswap;
	r32.ru_inblock = r->ru_inblock;
	r32.ru_oublock = r->ru_oublock;
	r32.ru_msgsnd = r->ru_msgsnd;
	r32.ru_msgrcv = r->ru_msgrcv;
	r32.ru_nसंकेतs = r->ru_nसंकेतs;
	r32.ru_nvcsw = r->ru_nvcsw;
	r32.ru_nivcsw = r->ru_nivcsw;
	अगर (copy_to_user(ru, &r32, माप(r32)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक compat_get_user_cpu_mask(compat_uदीर्घ_t __user *user_mask_ptr,
				    अचिन्हित len, काष्ठा cpumask *new_mask)
अणु
	अचिन्हित दीर्घ *k;

	अगर (len < cpumask_size())
		स_रखो(new_mask, 0, cpumask_size());
	अन्यथा अगर (len > cpumask_size())
		len = cpumask_size();

	k = cpumask_bits(new_mask);
	वापस compat_get_biपंचांगap(k, user_mask_ptr, len * 8);
पूर्ण

COMPAT_SYSCALL_DEFINE3(sched_setaffinity, compat_pid_t, pid,
		       अचिन्हित पूर्णांक, len,
		       compat_uदीर्घ_t __user *, user_mask_ptr)
अणु
	cpumask_var_t new_mask;
	पूर्णांक retval;

	अगर (!alloc_cpumask_var(&new_mask, GFP_KERNEL))
		वापस -ENOMEM;

	retval = compat_get_user_cpu_mask(user_mask_ptr, len, new_mask);
	अगर (retval)
		जाओ out;

	retval = sched_setaffinity(pid, new_mask);
out:
	मुक्त_cpumask_var(new_mask);
	वापस retval;
पूर्ण

COMPAT_SYSCALL_DEFINE3(sched_getaffinity, compat_pid_t,  pid, अचिन्हित पूर्णांक, len,
		       compat_uदीर्घ_t __user *, user_mask_ptr)
अणु
	पूर्णांक ret;
	cpumask_var_t mask;

	अगर ((len * BITS_PER_BYTE) < nr_cpu_ids)
		वापस -EINVAL;
	अगर (len & (माप(compat_uदीर्घ_t)-1))
		वापस -EINVAL;

	अगर (!alloc_cpumask_var(&mask, GFP_KERNEL))
		वापस -ENOMEM;

	ret = sched_getaffinity(pid, mask);
	अगर (ret == 0) अणु
		अचिन्हित पूर्णांक retlen = min(len, cpumask_size());

		अगर (compat_put_biपंचांगap(user_mask_ptr, cpumask_bits(mask), retlen * 8))
			ret = -EFAULT;
		अन्यथा
			ret = retlen;
	पूर्ण
	मुक्त_cpumask_var(mask);

	वापस ret;
पूर्ण

/*
 * We currently only need the following fields from the sigevent
 * काष्ठाure: sigev_value, sigev_signo, sig_notअगरy and (someबार
 * sigev_notअगरy_thपढ़ो_id).  The others are handled in user mode.
 * We also assume that copying sigev_value.sival_पूर्णांक is sufficient
 * to keep all the bits of sigev_value.sival_ptr पूर्णांकact.
 */
पूर्णांक get_compat_sigevent(काष्ठा sigevent *event,
		स्थिर काष्ठा compat_sigevent __user *u_event)
अणु
	स_रखो(event, 0, माप(*event));
	वापस (!access_ok(u_event, माप(*u_event)) ||
		__get_user(event->sigev_value.sival_पूर्णांक,
			&u_event->sigev_value.sival_पूर्णांक) ||
		__get_user(event->sigev_signo, &u_event->sigev_signo) ||
		__get_user(event->sigev_notअगरy, &u_event->sigev_notअगरy) ||
		__get_user(event->sigev_notअगरy_thपढ़ो_id,
			&u_event->sigev_notअगरy_thपढ़ो_id))
		? -EFAULT : 0;
पूर्ण

दीर्घ compat_get_biपंचांगap(अचिन्हित दीर्घ *mask, स्थिर compat_uदीर्घ_t __user *umask,
		       अचिन्हित दीर्घ biपंचांगap_size)
अणु
	अचिन्हित दीर्घ nr_compat_दीर्घs;

	/* align biपंचांगap up to nearest compat_दीर्घ_t boundary */
	biपंचांगap_size = ALIGN(biपंचांगap_size, BITS_PER_COMPAT_LONG);
	nr_compat_दीर्घs = BITS_TO_COMPAT_LONGS(biपंचांगap_size);

	अगर (!user_पढ़ो_access_begin(umask, biपंचांगap_size / 8))
		वापस -EFAULT;

	जबतक (nr_compat_दीर्घs > 1) अणु
		compat_uदीर्घ_t l1, l2;
		unsafe_get_user(l1, umask++, Efault);
		unsafe_get_user(l2, umask++, Efault);
		*mask++ = ((अचिन्हित दीर्घ)l2 << BITS_PER_COMPAT_LONG) | l1;
		nr_compat_दीर्घs -= 2;
	पूर्ण
	अगर (nr_compat_दीर्घs)
		unsafe_get_user(*mask, umask++, Efault);
	user_पढ़ो_access_end();
	वापस 0;

Efault:
	user_पढ़ो_access_end();
	वापस -EFAULT;
पूर्ण

दीर्घ compat_put_biपंचांगap(compat_uदीर्घ_t __user *umask, अचिन्हित दीर्घ *mask,
		       अचिन्हित दीर्घ biपंचांगap_size)
अणु
	अचिन्हित दीर्घ nr_compat_दीर्घs;

	/* align biपंचांगap up to nearest compat_दीर्घ_t boundary */
	biपंचांगap_size = ALIGN(biपंचांगap_size, BITS_PER_COMPAT_LONG);
	nr_compat_दीर्घs = BITS_TO_COMPAT_LONGS(biपंचांगap_size);

	अगर (!user_ग_लिखो_access_begin(umask, biपंचांगap_size / 8))
		वापस -EFAULT;

	जबतक (nr_compat_दीर्घs > 1) अणु
		अचिन्हित दीर्घ m = *mask++;
		unsafe_put_user((compat_uदीर्घ_t)m, umask++, Efault);
		unsafe_put_user(m >> BITS_PER_COMPAT_LONG, umask++, Efault);
		nr_compat_दीर्घs -= 2;
	पूर्ण
	अगर (nr_compat_दीर्घs)
		unsafe_put_user((compat_uदीर्घ_t)*mask, umask++, Efault);
	user_ग_लिखो_access_end();
	वापस 0;
Efault:
	user_ग_लिखो_access_end();
	वापस -EFAULT;
पूर्ण

पूर्णांक
get_compat_sigset(sigset_t *set, स्थिर compat_sigset_t __user *compat)
अणु
#अगर_घोषित __BIG_ENDIAN
	compat_sigset_t v;
	अगर (copy_from_user(&v, compat, माप(compat_sigset_t)))
		वापस -EFAULT;
	चयन (_NSIG_WORDS) अणु
	हाल 4: set->sig[3] = v.sig[6] | (((दीर्घ)v.sig[7]) << 32 );
		fallthrough;
	हाल 3: set->sig[2] = v.sig[4] | (((दीर्घ)v.sig[5]) << 32 );
		fallthrough;
	हाल 2: set->sig[1] = v.sig[2] | (((दीर्घ)v.sig[3]) << 32 );
		fallthrough;
	हाल 1: set->sig[0] = v.sig[0] | (((दीर्घ)v.sig[1]) << 32 );
	पूर्ण
#अन्यथा
	अगर (copy_from_user(set, compat, माप(compat_sigset_t)))
		वापस -EFAULT;
#पूर्ण_अगर
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(get_compat_sigset);

/*
 * Allocate user-space memory क्रम the duration of a single प्रणाली call,
 * in order to marshall parameters inside a compat thunk.
 */
व्योम __user *compat_alloc_user_space(अचिन्हित दीर्घ len)
अणु
	व्योम __user *ptr;

	/* If len would occupy more than half of the entire compat space... */
	अगर (unlikely(len > (((compat_uptr_t)~0) >> 1)))
		वापस शून्य;

	ptr = arch_compat_alloc_user_space(len);

	अगर (unlikely(!access_ok(ptr, len)))
		वापस शून्य;

	वापस ptr;
पूर्ण
EXPORT_SYMBOL_GPL(compat_alloc_user_space);
