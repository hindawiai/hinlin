<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 1998-2004 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *	Stephane Eranian <eranian@hpl.hp.com>
 * Copyright (C) 2003 Intel Co
 *	Suresh Siddha <suresh.b.siddha@पूर्णांकel.com>
 *	Fenghua Yu <fenghua.yu@पूर्णांकel.com>
 *	Arun Sharma <arun.sharma@पूर्णांकel.com>
 *
 * 12/07/98	S. Eranian	added pt_regs & चयन_stack
 * 12/21/98	D. Mosberger	updated to match latest code
 *  6/17/99	D. Mosberger	added second unat member to "struct switch_stack"
 *
 */
#अगर_अघोषित _ASM_IA64_PTRACE_H
#घोषणा _ASM_IA64_PTRACE_H

#अगर_अघोषित ASM_OFFSETS_C
#समावेश <यंत्र/यंत्र-offsets.h>
#पूर्ण_अगर
#समावेश <uapi/यंत्र/ptrace.h>

/*
 * Base-2 logarithm of number of pages to allocate per task काष्ठाure
 * (including रेजिस्टर backing store and memory stack):
 */
#अगर defined(CONFIG_IA64_PAGE_SIZE_4KB)
# define KERNEL_STACK_SIZE_ORDER		3
#या_अगर defined(CONFIG_IA64_PAGE_SIZE_8KB)
# define KERNEL_STACK_SIZE_ORDER		2
#या_अगर defined(CONFIG_IA64_PAGE_SIZE_16KB)
# define KERNEL_STACK_SIZE_ORDER		1
#अन्यथा
# define KERNEL_STACK_SIZE_ORDER		0
#पूर्ण_अगर

#घोषणा IA64_RBS_OFFSET			((IA64_TASK_SIZE + IA64_THREAD_INFO_SIZE + 31) & ~31)
#घोषणा IA64_STK_OFFSET			((1 << KERNEL_STACK_SIZE_ORDER)*PAGE_SIZE)

#घोषणा KERNEL_STACK_SIZE		IA64_STK_OFFSET

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/current.h>
#समावेश <यंत्र/page.h>

/*
 * We use the ia64_psr(regs)->ri to determine which of the three
 * inकाष्ठाions in bundle (16 bytes) took the sample. Generate
 * the canonical representation by adding to inकाष्ठाion poपूर्णांकer.
 */
# define inकाष्ठाion_poपूर्णांकer(regs) ((regs)->cr_iip + ia64_psr(regs)->ri)

अटल अंतरभूत अचिन्हित दीर्घ user_stack_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->r12;
पूर्ण

अटल अंतरभूत पूर्णांक is_syscall_success(काष्ठा pt_regs *regs)
अणु
	वापस regs->r10 != -1;
पूर्ण

अटल अंतरभूत दीर्घ regs_वापस_value(काष्ठा pt_regs *regs)
अणु
	अगर (is_syscall_success(regs))
		वापस regs->r8;
	अन्यथा
		वापस -regs->r8;
पूर्ण

/* Conserve space in histogram by encoding slot bits in address
 * bits 2 and 3 rather than bits 0 and 1.
 */
#घोषणा profile_pc(regs)						\
(अणु									\
	अचिन्हित दीर्घ __ip = inकाष्ठाion_poपूर्णांकer(regs);			\
	(__ip & ~3UL) + ((__ip & 3UL) << 2);				\
पूर्ण)

  /* given a poपूर्णांकer to a task_काष्ठा, वापस the user's pt_regs */
# define task_pt_regs(t)		(((काष्ठा pt_regs *) ((अक्षर *) (t) + IA64_STK_OFFSET)) - 1)
# define ia64_psr(regs)			((काष्ठा ia64_psr *) &(regs)->cr_ipsr)
# define user_mode(regs)		(((काष्ठा ia64_psr *) &(regs)->cr_ipsr)->cpl != 0)
# define user_stack(task,regs)	((दीर्घ) regs - (दीर्घ) task == IA64_STK_OFFSET - माप(*regs))
# define fsys_mode(task,regs)					\
  (अणु								\
	  काष्ठा task_काष्ठा *_task = (task);			\
	  काष्ठा pt_regs *_regs = (regs);			\
	  !user_mode(_regs) && user_stack(_task, _regs);	\
  पूर्ण)

  /*
   * System call handlers that, upon successful completion, need to वापस a negative value
   * should call क्रमce_successful_syscall_वापस() right beक्रमe वापसing.  On architectures
   * where the syscall convention provides क्रम a separate error flag (e.g., alpha, ia64,
   * ppcअणु,64पूर्ण, sparcअणु,64पूर्ण, possibly others), this macro can be used to ensure that the error
   * flag will not get set.  On architectures which करो not support a separate error flag,
   * the macro is a no-op and the spurious error condition needs to be filtered out by some
   * other means (e.g., in user-level, by passing an extra argument to the syscall handler,
   * or something aदीर्घ those lines).
   *
   * On ia64, we can clear the user's pt_regs->r8 to क्रमce a successful syscall.
   */
# define क्रमce_successful_syscall_वापस()	(task_pt_regs(current)->r8 = 0)

  काष्ठा task_काष्ठा;			/* क्रमward decl */
  काष्ठा unw_frame_info;		/* क्रमward decl */

  बाह्य अचिन्हित दीर्घ ia64_get_user_rbs_end (काष्ठा task_काष्ठा *, काष्ठा pt_regs *,
					      अचिन्हित दीर्घ *);
  बाह्य दीर्घ ia64_peek (काष्ठा task_काष्ठा *, काष्ठा चयन_stack *, अचिन्हित दीर्घ,
			 अचिन्हित दीर्घ, दीर्घ *);
  बाह्य दीर्घ ia64_poke (काष्ठा task_काष्ठा *, काष्ठा चयन_stack *, अचिन्हित दीर्घ,
			 अचिन्हित दीर्घ, दीर्घ);
  बाह्य व्योम ia64_flush_fph (काष्ठा task_काष्ठा *);
  बाह्य व्योम ia64_sync_fph (काष्ठा task_काष्ठा *);
  बाह्य व्योम ia64_sync_krbs(व्योम);
  बाह्य दीर्घ ia64_sync_user_rbs (काष्ठा task_काष्ठा *, काष्ठा चयन_stack *,
				  अचिन्हित दीर्घ, अचिन्हित दीर्घ);

  /* get nat bits क्रम scratch रेजिस्टरs such that bit N==1 अगरf scratch रेजिस्टर rN is a NaT */
  बाह्य अचिन्हित दीर्घ ia64_get_scratch_nat_bits (काष्ठा pt_regs *pt, अचिन्हित दीर्घ scratch_unat);
  /* put nat bits क्रम scratch रेजिस्टरs such that scratch रेजिस्टर rN is a NaT अगरf bit N==1 */
  बाह्य अचिन्हित दीर्घ ia64_put_scratch_nat_bits (काष्ठा pt_regs *pt, अचिन्हित दीर्घ nat);

  बाह्य व्योम ia64_increment_ip (काष्ठा pt_regs *pt);
  बाह्य व्योम ia64_decrement_ip (काष्ठा pt_regs *pt);

  बाह्य व्योम ia64_ptrace_stop(व्योम);
  #घोषणा arch_ptrace_stop(code, info) \
	ia64_ptrace_stop()
  #घोषणा arch_ptrace_stop_needed(code, info) \
	(!test_thपढ़ो_flag(TIF_RESTORE_RSE))

  बाह्य व्योम ptrace_attach_sync_user_rbs (काष्ठा task_काष्ठा *);
  #घोषणा arch_ptrace_attach(child) \
	ptrace_attach_sync_user_rbs(child)

  #घोषणा arch_has_single_step()  (1)
  #घोषणा arch_has_block_step()   (1)

#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_IA64_PTRACE_H */
