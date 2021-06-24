<शैली गुरु>
/*
 * include/यंत्र-xtensa/ptrace.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */
#अगर_अघोषित _XTENSA_PTRACE_H
#घोषणा _XTENSA_PTRACE_H

#समावेश <यंत्र/kmem_layout.h>
#समावेश <uapi/यंत्र/ptrace.h>

/*
 * Kernel stack
 *
 *		+-----------------------+  -------- STACK_SIZE
 *		|     रेजिस्टर file     |  |
 *		+-----------------------+  |
 *		|    काष्ठा pt_regs     |  |
 *		+-----------------------+  | ------ PT_REGS_OFFSET
 * द्विगुन	:  16 bytes spill area  :  |  ^
 * excetion	:- - - - - - - - - - - -:  |  |
 * frame	:    काष्ठा pt_regs     :  |  |
 *		:- - - - - - - - - - - -:  |  |
 *		|                       |  |  |
 *		|     memory stack      |  |  |
 *		|                       |  |  |
 *		~                       ~  ~  ~
 *		~                       ~  ~  ~
 *		|                       |  |  |
 *		|                       |  |  |
 *		+-----------------------+  |  | --- STACK_BIAS
 *		|  काष्ठा task_काष्ठा   |  |  |  ^
 *  current --> +-----------------------+  |  |  |
 *		|  काष्ठा thपढ़ो_info   |  |  |  |
 *		+-----------------------+ --------
 */

#घोषणा NO_SYSCALL (-1)

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/coprocessor.h>

/*
 * This काष्ठा defines the way the रेजिस्टरs are stored on the
 * kernel stack during a प्रणाली call or other kernel entry.
 */
काष्ठा pt_regs अणु
	अचिन्हित दीर्घ pc;		/*   4 */
	अचिन्हित दीर्घ ps;		/*   8 */
	अचिन्हित दीर्घ depc;		/*  12 */
	अचिन्हित दीर्घ exccause;		/*  16 */
	अचिन्हित दीर्घ excvaddr;		/*  20 */
	अचिन्हित दीर्घ debugcause;	/*  24 */
	अचिन्हित दीर्घ wmask;		/*  28 */
	अचिन्हित दीर्घ lbeg;		/*  32 */
	अचिन्हित दीर्घ lend;		/*  36 */
	अचिन्हित दीर्घ lcount;		/*  40 */
	अचिन्हित दीर्घ sar;		/*  44 */
	अचिन्हित दीर्घ winकरोwbase;	/*  48 */
	अचिन्हित दीर्घ winकरोwstart;	/*  52 */
	अचिन्हित दीर्घ syscall;		/*  56 */
	अचिन्हित दीर्घ icountlevel;	/*  60 */
	अचिन्हित दीर्घ scompare1;	/*  64 */
	अचिन्हित दीर्घ thपढ़ोptr;	/*  68 */

	/* Additional configurable रेजिस्टरs that are used by the compiler. */
	xtregs_opt_t xtregs_opt;

	/* Make sure the areg field is 16 bytes aligned. */
	पूर्णांक align[0] __attribute__ ((aligned(16)));

	/* current रेजिस्टर frame.
	 * Note: The ESF क्रम kernel exceptions ends after 16 रेजिस्टरs!
	 */
	अचिन्हित दीर्घ areg[16];
पूर्ण;

#समावेश <यंत्र/core.h>

# define arch_has_single_step()	(1)
# define task_pt_regs(tsk) ((काष्ठा pt_regs*) \
	(task_stack_page(tsk) + KERNEL_STACK_SIZE - (XCHAL_NUM_AREGS-16)*4) - 1)
# define user_mode(regs) (((regs)->ps & 0x00000020)!=0)
# define inकाष्ठाion_poपूर्णांकer(regs) ((regs)->pc)
# define वापस_poपूर्णांकer(regs) (MAKE_PC_FROM_RA((regs)->areg[0], \
					       (regs)->areg[1]))

# अगरndef CONFIG_SMP
#  define profile_pc(regs) inकाष्ठाion_poपूर्णांकer(regs)
# अन्यथा
#  define profile_pc(regs)						\
	(अणु								\
		in_lock_functions(inकाष्ठाion_poपूर्णांकer(regs)) ?		\
		वापस_poपूर्णांकer(regs) : inकाष्ठाion_poपूर्णांकer(regs);	\
	पूर्ण)
# endअगर

#घोषणा user_stack_poपूर्णांकer(regs) ((regs)->areg[1])

अटल अंतरभूत अचिन्हित दीर्घ regs_वापस_value(काष्ठा pt_regs *regs)
अणु
	वापस regs->areg[2];
पूर्ण

#अन्यथा	/* __ASSEMBLY__ */

# include <यंत्र/यंत्र-offsets.h>
#घोषणा PT_REGS_OFFSET	  (KERNEL_STACK_SIZE - PT_USER_SIZE)

#पूर्ण_अगर	/* !__ASSEMBLY__ */

#पूर्ण_अगर	/* _XTENSA_PTRACE_H */
