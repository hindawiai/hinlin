<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Perक्रमmance counter callchain support - घातerpc architecture code
 *
 * Copyright तऊ 2009 Paul Mackerras, IBM Corporation.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/percpu.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/sigcontext.h>
#समावेश <यंत्र/ucontext.h>
#समावेश <यंत्र/vdso.h>
#समावेश <यंत्र/pte-walk.h>

#समावेश "callchain.h"

/*
 * On 64-bit we करोn't want to invoke hash_page on user addresses from
 * पूर्णांकerrupt context, so अगर the access faults, we पढ़ो the page tables
 * to find which page (अगर any) is mapped and access it directly. Radix
 * has no need क्रम this so it करोesn't use पढ़ो_user_stack_slow.
 */
पूर्णांक पढ़ो_user_stack_slow(स्थिर व्योम __user *ptr, व्योम *buf, पूर्णांक nb)
अणु

	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) ptr;
	अचिन्हित दीर्घ offset;
	काष्ठा page *page;
	व्योम *kaddr;

	अगर (get_user_page_fast_only(addr, FOLL_WRITE, &page)) अणु
		kaddr = page_address(page);

		/* align address to page boundary */
		offset = addr & ~PAGE_MASK;

		स_नकल(buf, kaddr + offset, nb);
		put_page(page);
		वापस 0;
	पूर्ण
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक पढ़ो_user_stack_64(स्थिर अचिन्हित दीर्घ __user *ptr, अचिन्हित दीर्घ *ret)
अणु
	वापस __पढ़ो_user_stack(ptr, ret, माप(*ret));
पूर्ण

/*
 * 64-bit user processes use the same stack frame क्रम RT and non-RT संकेतs.
 */
काष्ठा संकेत_frame_64 अणु
	अक्षर		dummy[__SIGNAL_FRAMESIZE];
	काष्ठा ucontext	uc;
	अचिन्हित दीर्घ	unused[2];
	अचिन्हित पूर्णांक	tramp[6];
	काष्ठा siginfo	*pinfo;
	व्योम		*puc;
	काष्ठा siginfo	info;
	अक्षर		abigap[288];
पूर्ण;

अटल पूर्णांक is_sigवापस_64_address(अचिन्हित दीर्घ nip, अचिन्हित दीर्घ fp)
अणु
	अगर (nip == fp + दुरत्व(काष्ठा संकेत_frame_64, tramp))
		वापस 1;
	अगर (current->mm->context.vdso &&
	    nip == VDSO64_SYMBOL(current->mm->context.vdso, sigtramp_rt64))
		वापस 1;
	वापस 0;
पूर्ण

/*
 * Do some sanity checking on the संकेत frame poपूर्णांकed to by sp.
 * We check the pinfo and puc poपूर्णांकers in the frame.
 */
अटल पूर्णांक sane_संकेत_64_frame(अचिन्हित दीर्घ sp)
अणु
	काष्ठा संकेत_frame_64 __user *sf;
	अचिन्हित दीर्घ pinfo, puc;

	sf = (काष्ठा संकेत_frame_64 __user *) sp;
	अगर (पढ़ो_user_stack_64((अचिन्हित दीर्घ __user *) &sf->pinfo, &pinfo) ||
	    पढ़ो_user_stack_64((अचिन्हित दीर्घ __user *) &sf->puc, &puc))
		वापस 0;
	वापस pinfo == (अचिन्हित दीर्घ) &sf->info &&
		puc == (अचिन्हित दीर्घ) &sf->uc;
पूर्ण

व्योम perf_callchain_user_64(काष्ठा perf_callchain_entry_ctx *entry,
			    काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ sp, next_sp;
	अचिन्हित दीर्घ next_ip;
	अचिन्हित दीर्घ lr;
	दीर्घ level = 0;
	काष्ठा संकेत_frame_64 __user *sigframe;
	अचिन्हित दीर्घ __user *fp, *uregs;

	next_ip = perf_inकाष्ठाion_poपूर्णांकer(regs);
	lr = regs->link;
	sp = regs->gpr[1];
	perf_callchain_store(entry, next_ip);

	जबतक (entry->nr < entry->max_stack) अणु
		fp = (अचिन्हित दीर्घ __user *) sp;
		अगर (invalid_user_sp(sp) || पढ़ो_user_stack_64(fp, &next_sp))
			वापस;
		अगर (level > 0 && पढ़ो_user_stack_64(&fp[2], &next_ip))
			वापस;

		/*
		 * Note: the next_sp - sp >= संकेत frame size check
		 * is true when next_sp < sp, which can happen when
		 * transitioning from an alternate संकेत stack to the
		 * normal stack.
		 */
		अगर (next_sp - sp >= माप(काष्ठा संकेत_frame_64) &&
		    (is_sigवापस_64_address(next_ip, sp) ||
		     (level <= 1 && is_sigवापस_64_address(lr, sp))) &&
		    sane_संकेत_64_frame(sp)) अणु
			/*
			 * This looks like an संकेत frame
			 */
			sigframe = (काष्ठा संकेत_frame_64 __user *) sp;
			uregs = sigframe->uc.uc_mcontext.gp_regs;
			अगर (पढ़ो_user_stack_64(&uregs[PT_NIP], &next_ip) ||
			    पढ़ो_user_stack_64(&uregs[PT_LNK], &lr) ||
			    पढ़ो_user_stack_64(&uregs[PT_R1], &sp))
				वापस;
			level = 0;
			perf_callchain_store_context(entry, PERF_CONTEXT_USER);
			perf_callchain_store(entry, next_ip);
			जारी;
		पूर्ण

		अगर (level == 0)
			next_ip = lr;
		perf_callchain_store(entry, next_ip);
		++level;
		sp = next_sp;
	पूर्ण
पूर्ण
