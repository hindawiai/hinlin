<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on arch/arm/kernel/sys_arm.c
 *
 * Copyright (C) People who wrote linux/arch/i386/kernel/sys_i386.c
 * Copyright (C) 1995, 1996 Russell King.
 * Copyright (C) 2012 ARM Ltd.
 */

#समावेश <linux/compat.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/personality.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/unistd.h>

अटल दीर्घ
__करो_compat_cache_op(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	दीर्घ ret;

	करो अणु
		अचिन्हित दीर्घ chunk = min(PAGE_SIZE, end - start);

		अगर (fatal_संकेत_pending(current))
			वापस 0;

		अगर (cpus_have_स्थिर_cap(ARM64_WORKAROUND_1542419)) अणु
			/*
			 * The workaround requires an inner-shareable tlbi.
			 * We pick the reserved-ASID to minimise the impact.
			 */
			__tlbi(aside1is, __TLBI_VADDR(0, 0));
			dsb(ish);
		पूर्ण

		ret = __flush_cache_user_range(start, start + chunk);
		अगर (ret)
			वापस ret;

		cond_resched();
		start += chunk;
	पूर्ण जबतक (start < end);

	वापस 0;
पूर्ण

अटल अंतरभूत दीर्घ
करो_compat_cache_op(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, पूर्णांक flags)
अणु
	अगर (end < start || flags)
		वापस -EINVAL;

	अगर (!access_ok((स्थिर व्योम __user *)start, end - start))
		वापस -EFAULT;

	वापस __करो_compat_cache_op(start, end);
पूर्ण
/*
 * Handle all unrecognised प्रणाली calls.
 */
दीर्घ compat_arm_syscall(काष्ठा pt_regs *regs, पूर्णांक scno)
अणु
	अचिन्हित दीर्घ addr;

	चयन (scno) अणु
	/*
	 * Flush a region from भव address 'r0' to virtual address 'r1'
	 * _exclusive_.  There is no alignment requirement on either address;
	 * user space करोes not need to know the hardware cache layout.
	 *
	 * r2 contains flags.  It should ALWAYS be passed as ZERO until it
	 * is defined to be something अन्यथा.  For now we ignore it, but may
	 * the fires of hell burn in your belly अगर you अवरोध this rule. ;)
	 *
	 * (at a later date, we may want to allow this call to not flush
	 * various aspects of the cache.  Passing '0' will guarantee that
	 * everything necessary माला_लो flushed to मुख्यtain consistency in
	 * the specअगरied region).
	 */
	हाल __ARM_NR_compat_cacheflush:
		वापस करो_compat_cache_op(regs->regs[0], regs->regs[1], regs->regs[2]);

	हाल __ARM_NR_compat_set_tls:
		current->thपढ़ो.uw.tp_value = regs->regs[0];

		/*
		 * Protect against रेजिस्टर corruption from context चयन.
		 * See comment in tls_thपढ़ो_flush.
		 */
		barrier();
		ग_लिखो_sysreg(regs->regs[0], tpidrro_el0);
		वापस 0;

	शेष:
		/*
		 * Calls 0xf0xxx..0xf07ff are defined to वापस -ENOSYS
		 * अगर not implemented, rather than raising संक_अवैध. This
		 * way the calling program can gracefully determine whether
		 * a feature is supported.
		 */
		अगर (scno < __ARM_NR_COMPAT_END)
			वापस -ENOSYS;
		अवरोध;
	पूर्ण

	addr = inकाष्ठाion_poपूर्णांकer(regs) - (compat_thumb_mode(regs) ? 2 : 4);

	arm64_notअगरy_die("Oops - bad compat syscall(2)", regs,
			 संक_अवैध, ILL_ILLTRP, addr, scno);
	वापस 0;
पूर्ण
