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
 * Is sp valid as the address of the next kernel stack frame after prev_sp?
 * The next frame may be in a dअगरferent stack area but should not go
 * back करोwn in the same stack area.
 */
अटल पूर्णांक valid_next_sp(अचिन्हित दीर्घ sp, अचिन्हित दीर्घ prev_sp)
अणु
	अगर (sp & 0xf)
		वापस 0;		/* must be 16-byte aligned */
	अगर (!validate_sp(sp, current, STACK_FRAME_OVERHEAD))
		वापस 0;
	अगर (sp >= prev_sp + STACK_FRAME_MIN_SIZE)
		वापस 1;
	/*
	 * sp could decrease when we jump off an पूर्णांकerrupt stack
	 * back to the regular process stack.
	 */
	अगर ((sp & ~(THREAD_SIZE - 1)) != (prev_sp & ~(THREAD_SIZE - 1)))
		वापस 1;
	वापस 0;
पूर्ण

व्योम
perf_callchain_kernel(काष्ठा perf_callchain_entry_ctx *entry, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ sp, next_sp;
	अचिन्हित दीर्घ next_ip;
	अचिन्हित दीर्घ lr;
	दीर्घ level = 0;
	अचिन्हित दीर्घ *fp;

	lr = regs->link;
	sp = regs->gpr[1];
	perf_callchain_store(entry, perf_inकाष्ठाion_poपूर्णांकer(regs));

	अगर (!validate_sp(sp, current, STACK_FRAME_OVERHEAD))
		वापस;

	क्रम (;;) अणु
		fp = (अचिन्हित दीर्घ *) sp;
		next_sp = fp[0];

		अगर (next_sp == sp + STACK_INT_FRAME_SIZE &&
		    fp[STACK_FRAME_MARKER] == STACK_FRAME_REGS_MARKER) अणु
			/*
			 * This looks like an पूर्णांकerrupt frame क्रम an
			 * पूर्णांकerrupt that occurred in the kernel
			 */
			regs = (काष्ठा pt_regs *)(sp + STACK_FRAME_OVERHEAD);
			next_ip = regs->nip;
			lr = regs->link;
			level = 0;
			perf_callchain_store_context(entry, PERF_CONTEXT_KERNEL);

		पूर्ण अन्यथा अणु
			अगर (level == 0)
				next_ip = lr;
			अन्यथा
				next_ip = fp[STACK_FRAME_LR_SAVE];

			/*
			 * We can't tell which of the first two addresses
			 * we get are valid, but we can filter out the
			 * obviously bogus ones here.  We replace them
			 * with 0 rather than removing them entirely so
			 * that userspace can tell which is which.
			 */
			अगर ((level == 1 && next_ip == lr) ||
			    (level <= 1 && !kernel_text_address(next_ip)))
				next_ip = 0;

			++level;
		पूर्ण

		perf_callchain_store(entry, next_ip);
		अगर (!valid_next_sp(next_sp, sp))
			वापस;
		sp = next_sp;
	पूर्ण
पूर्ण

व्योम
perf_callchain_user(काष्ठा perf_callchain_entry_ctx *entry, काष्ठा pt_regs *regs)
अणु
	अगर (!is_32bit_task())
		perf_callchain_user_64(entry, regs);
	अन्यथा
		perf_callchain_user_32(entry, regs);
पूर्ण
