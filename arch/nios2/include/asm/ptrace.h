<शैली गुरु>
/*
 * Copyright (C) 2013 Altera Corporation
 * Copyright (C) 2010 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2004 Microtronix Datacom Ltd
 *
 * based on m68k यंत्र/processor.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _ASM_NIOS2_PTRACE_H
#घोषणा _ASM_NIOS2_PTRACE_H

#समावेश <uapi/यंत्र/ptrace.h>

/* This काष्ठा defines the way the रेजिस्टरs are stored on the
   stack during a प्रणाली call.  */

#अगर_अघोषित __ASSEMBLY__
काष्ठा pt_regs अणु
	अचिन्हित दीर्घ  r8;	/* r8-r15 Caller-saved GP रेजिस्टरs */
	अचिन्हित दीर्घ  r9;
	अचिन्हित दीर्घ  r10;
	अचिन्हित दीर्घ  r11;
	अचिन्हित दीर्घ  r12;
	अचिन्हित दीर्घ  r13;
	अचिन्हित दीर्घ  r14;
	अचिन्हित दीर्घ  r15;
	अचिन्हित दीर्घ  r1;	/* Assembler temporary */
	अचिन्हित दीर्घ  r2;	/* Retval LS 32bits */
	अचिन्हित दीर्घ  r3;	/* Retval MS 32bits */
	अचिन्हित दीर्घ  r4;	/* r4-r7 Register arguments */
	अचिन्हित दीर्घ  r5;
	अचिन्हित दीर्घ  r6;
	अचिन्हित दीर्घ  r7;
	अचिन्हित दीर्घ  orig_r2;	/* Copy of r2 ?? */
	अचिन्हित दीर्घ  ra;	/* Return address */
	अचिन्हित दीर्घ  fp;	/* Frame poपूर्णांकer */
	अचिन्हित दीर्घ  sp;	/* Stack poपूर्णांकer */
	अचिन्हित दीर्घ  gp;	/* Global poपूर्णांकer */
	अचिन्हित दीर्घ  estatus;
	अचिन्हित दीर्घ  ea;	/* Exception वापस address (pc) */
	अचिन्हित दीर्घ  orig_r7;
पूर्ण;

/*
 * This is the extended stack used by संकेत handlers and the context
 * चयनer: it's pushed after the normal "struct pt_regs".
 */
काष्ठा चयन_stack अणु
	अचिन्हित दीर्घ  r16;	/* r16-r23 Callee-saved GP रेजिस्टरs */
	अचिन्हित दीर्घ  r17;
	अचिन्हित दीर्घ  r18;
	अचिन्हित दीर्घ  r19;
	अचिन्हित दीर्घ  r20;
	अचिन्हित दीर्घ  r21;
	अचिन्हित दीर्घ  r22;
	अचिन्हित दीर्घ  r23;
	अचिन्हित दीर्घ  fp;
	अचिन्हित दीर्घ  gp;
	अचिन्हित दीर्घ  ra;
पूर्ण;

#घोषणा user_mode(regs)	(((regs)->estatus & ESTATUS_EU))

#घोषणा inकाष्ठाion_poपूर्णांकer(regs)	((regs)->ra)
#घोषणा profile_pc(regs)		inकाष्ठाion_poपूर्णांकer(regs)
#घोषणा user_stack_poपूर्णांकer(regs)	((regs)->sp)
बाह्य व्योम show_regs(काष्ठा pt_regs *);

#घोषणा current_pt_regs() \
	((काष्ठा pt_regs *)((अचिन्हित दीर्घ)current_thपढ़ो_info() + THREAD_SIZE)\
		- 1)

पूर्णांक करो_syscall_trace_enter(व्योम);
व्योम करो_syscall_trace_निकास(व्योम);
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_NIOS2_PTRACE_H */
