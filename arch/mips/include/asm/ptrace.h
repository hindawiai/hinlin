<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994, 95, 96, 97, 98, 99, 2000 by Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_PTRACE_H
#घोषणा _ASM_PTRACE_H


#समावेश <linux/compiler.h>
#समावेश <linux/linkage.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/isadep.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/thपढ़ो_info.h>
#समावेश <uapi/यंत्र/ptrace.h>

/*
 * This काष्ठा defines the way the रेजिस्टरs are stored on the stack during a
 * प्रणाली call/exception. As usual the रेजिस्टरs k0/k1 aren't being saved.
 *
 * If you add a रेजिस्टर here, also add it to regoffset_table[] in
 * arch/mips/kernel/ptrace.c.
 */
काष्ठा pt_regs अणु
#अगर_घोषित CONFIG_32BIT
	/* Pad bytes क्रम argument save space on the stack. */
	अचिन्हित दीर्घ pad0[8];
#पूर्ण_अगर

	/* Saved मुख्य processor रेजिस्टरs. */
	अचिन्हित दीर्घ regs[32];

	/* Saved special रेजिस्टरs. */
	अचिन्हित दीर्घ cp0_status;
	अचिन्हित दीर्घ hi;
	अचिन्हित दीर्घ lo;
#अगर_घोषित CONFIG_CPU_HAS_SMARTMIPS
	अचिन्हित दीर्घ acx;
#पूर्ण_अगर
	अचिन्हित दीर्घ cp0_badvaddr;
	अचिन्हित दीर्घ cp0_cause;
	अचिन्हित दीर्घ cp0_epc;
#अगर_घोषित CONFIG_CPU_CAVIUM_OCTEON
	अचिन्हित दीर्घ दीर्घ mpl[6];        /* MTMअणु0-5पूर्ण */
	अचिन्हित दीर्घ दीर्घ mtp[6];        /* MTPअणु0-5पूर्ण */
#पूर्ण_अगर
	अचिन्हित दीर्घ __last[0];
पूर्ण __aligned(8);

अटल अंतरभूत अचिन्हित दीर्घ kernel_stack_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->regs[29];
पूर्ण

अटल अंतरभूत व्योम inकाष्ठाion_poपूर्णांकer_set(काष्ठा pt_regs *regs,
                                           अचिन्हित दीर्घ val)
अणु
	regs->cp0_epc = val;
पूर्ण

/* Query offset/name of रेजिस्टर from its name/offset */
बाह्य पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name);
#घोषणा MAX_REG_OFFSET (दुरत्व(काष्ठा pt_regs, __last))

/**
 * regs_get_रेजिस्टर() - get रेजिस्टर value from its offset
 * @regs:       pt_regs from which रेजिस्टर value is gotten.
 * @offset:     offset number of the रेजिस्टर.
 *
 * regs_get_रेजिस्टर वापसs the value of a रेजिस्टर. The @offset is the
 * offset of the रेजिस्टर in काष्ठा pt_regs address which specअगरied by @regs.
 * If @offset is bigger than MAX_REG_OFFSET, this वापसs 0.
 */
अटल अंतरभूत अचिन्हित दीर्घ regs_get_रेजिस्टर(काष्ठा pt_regs *regs,
                                              अचिन्हित पूर्णांक offset)
अणु
	अगर (unlikely(offset > MAX_REG_OFFSET))
		वापस 0;

	वापस *(अचिन्हित दीर्घ *)((अचिन्हित दीर्घ)regs + offset);
पूर्ण

/**
 * regs_within_kernel_stack() - check the address in the stack
 * @regs:       pt_regs which contains kernel stack poपूर्णांकer.
 * @addr:       address which is checked.
 *
 * regs_within_kernel_stack() checks @addr is within the kernel stack page(s).
 * If @addr is within the kernel stack, it वापसs true. If not, वापसs false.
 */
अटल अंतरभूत पूर्णांक regs_within_kernel_stack(काष्ठा pt_regs *regs,
                                           अचिन्हित दीर्घ addr)
अणु
	वापस ((addr & ~(THREAD_SIZE - 1))  ==
		(kernel_stack_poपूर्णांकer(regs) & ~(THREAD_SIZE - 1)));
पूर्ण

/**
 * regs_get_kernel_stack_nth() - get Nth entry of the stack
 * @regs:       pt_regs which contains kernel stack poपूर्णांकer.
 * @n:          stack entry number.
 *
 * regs_get_kernel_stack_nth() वापसs @n th entry of the kernel stack which
 * is specअगरied by @regs. If the @n th entry is NOT in the kernel stack,
 * this वापसs 0.
 */
अटल अंतरभूत अचिन्हित दीर्घ regs_get_kernel_stack_nth(काष्ठा pt_regs *regs,
                                                      अचिन्हित पूर्णांक n)
अणु
	अचिन्हित दीर्घ *addr = (अचिन्हित दीर्घ *)kernel_stack_poपूर्णांकer(regs);

	addr += n;
	अगर (regs_within_kernel_stack(regs, (अचिन्हित दीर्घ)addr))
		वापस *addr;
	अन्यथा
		वापस 0;
पूर्ण

काष्ठा task_काष्ठा;

बाह्य पूर्णांक ptrace_getregs(काष्ठा task_काष्ठा *child,
	काष्ठा user_pt_regs __user *data);
बाह्य पूर्णांक ptrace_setregs(काष्ठा task_काष्ठा *child,
	काष्ठा user_pt_regs __user *data);

बाह्य पूर्णांक ptrace_getfpregs(काष्ठा task_काष्ठा *child, __u32 __user *data);
बाह्य पूर्णांक ptrace_setfpregs(काष्ठा task_काष्ठा *child, __u32 __user *data);

बाह्य पूर्णांक ptrace_get_watch_regs(काष्ठा task_काष्ठा *child,
	काष्ठा pt_watch_regs __user *addr);
बाह्य पूर्णांक ptrace_set_watch_regs(काष्ठा task_काष्ठा *child,
	काष्ठा pt_watch_regs __user *addr);

/*
 * Does the process account क्रम user or क्रम प्रणाली समय?
 */
#घोषणा user_mode(regs) (((regs)->cp0_status & KU_MASK) == KU_USER)

अटल अंतरभूत पूर्णांक is_syscall_success(काष्ठा pt_regs *regs)
अणु
	वापस !regs->regs[7];
पूर्ण

अटल अंतरभूत दीर्घ regs_वापस_value(काष्ठा pt_regs *regs)
अणु
	अगर (is_syscall_success(regs) || !user_mode(regs))
		वापस regs->regs[2];
	अन्यथा
		वापस -regs->regs[2];
पूर्ण

#घोषणा inकाष्ठाion_poपूर्णांकer(regs) ((regs)->cp0_epc)
#घोषणा profile_pc(regs) inकाष्ठाion_poपूर्णांकer(regs)

बाह्य यंत्रlinkage दीर्घ syscall_trace_enter(काष्ठा pt_regs *regs, दीर्घ syscall);
बाह्य यंत्रlinkage व्योम syscall_trace_leave(काष्ठा pt_regs *regs);

बाह्य व्योम die(स्थिर अक्षर *, काष्ठा pt_regs *) __noवापस;

अटल अंतरभूत व्योम die_अगर_kernel(स्थिर अक्षर *str, काष्ठा pt_regs *regs)
अणु
	अगर (unlikely(!user_mode(regs)))
		die(str, regs);
पूर्ण

#घोषणा current_pt_regs()						\
(अणु									\
	अचिन्हित दीर्घ sp = (अचिन्हित दीर्घ)__builtin_frame_address(0);	\
	(काष्ठा pt_regs *)((sp | (THREAD_SIZE - 1)) + 1 - 32) - 1;	\
पूर्ण)

/* Helpers क्रम working with the user stack poपूर्णांकer */

अटल अंतरभूत अचिन्हित दीर्घ user_stack_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->regs[29];
पूर्ण

अटल अंतरभूत व्योम user_stack_poपूर्णांकer_set(काष्ठा pt_regs *regs,
	अचिन्हित दीर्घ val)
अणु
	regs->regs[29] = val;
पूर्ण

#पूर्ण_अगर /* _ASM_PTRACE_H */
