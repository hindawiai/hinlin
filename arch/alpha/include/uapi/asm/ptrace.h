<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ASMAXP_PTRACE_H
#घोषणा _UAPI_ASMAXP_PTRACE_H


/*
 * This काष्ठा defines the way the रेजिस्टरs are stored on the
 * kernel stack during a प्रणाली call or other kernel entry
 *
 * NOTE! I want to minimize the overhead of प्रणाली calls, so this
 * काष्ठा has as little inक्रमmation as possible. It करोes not have
 *
 *  - भग्नing poपूर्णांक regs: the kernel करोesn't change those
 *  - r9-15: saved by the C compiler
 *
 * This makes "fork()" and "exec()" a bit more complex, but should
 * give us low प्रणाली call latency.
 */

काष्ठा pt_regs अणु
	अचिन्हित दीर्घ r0;
	अचिन्हित दीर्घ r1;
	अचिन्हित दीर्घ r2;
	अचिन्हित दीर्घ r3;
	अचिन्हित दीर्घ r4;
	अचिन्हित दीर्घ r5;
	अचिन्हित दीर्घ r6;
	अचिन्हित दीर्घ r7;
	अचिन्हित दीर्घ r8;
	अचिन्हित दीर्घ r19;
	अचिन्हित दीर्घ r20;
	अचिन्हित दीर्घ r21;
	अचिन्हित दीर्घ r22;
	अचिन्हित दीर्घ r23;
	अचिन्हित दीर्घ r24;
	अचिन्हित दीर्घ r25;
	अचिन्हित दीर्घ r26;
	अचिन्हित दीर्घ r27;
	अचिन्हित दीर्घ r28;
	अचिन्हित दीर्घ hae;
/* JRP - These are the values provided to a0-a2 by PALcode */
	अचिन्हित दीर्घ trap_a0;
	अचिन्हित दीर्घ trap_a1;
	अचिन्हित दीर्घ trap_a2;
/* These are saved by PAL-code: */
	अचिन्हित दीर्घ ps;
	अचिन्हित दीर्घ pc;
	अचिन्हित दीर्घ gp;
	अचिन्हित दीर्घ r16;
	अचिन्हित दीर्घ r17;
	अचिन्हित दीर्घ r18;
पूर्ण;

/*
 * This is the extended stack used by संकेत handlers and the context
 * चयनer: it's pushed after the normal "struct pt_regs".
 */
काष्ठा चयन_stack अणु
	अचिन्हित दीर्घ r9;
	अचिन्हित दीर्घ r10;
	अचिन्हित दीर्घ r11;
	अचिन्हित दीर्घ r12;
	अचिन्हित दीर्घ r13;
	अचिन्हित दीर्घ r14;
	अचिन्हित दीर्घ r15;
	अचिन्हित दीर्घ r26;
	अचिन्हित दीर्घ fp[32];	/* fp[31] is fpcr */
पूर्ण;


#पूर्ण_अगर /* _UAPI_ASMAXP_PTRACE_H */
