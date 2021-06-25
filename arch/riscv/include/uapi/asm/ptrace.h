<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only WITH Linux-syscall-note */
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _UAPI_ASM_RISCV_PTRACE_H
#घोषणा _UAPI_ASM_RISCV_PTRACE_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>

/*
 * User-mode रेजिस्टर state क्रम core dumps, ptrace, sigcontext
 *
 * This decouples काष्ठा pt_regs from the userspace ABI.
 * काष्ठा user_regs_काष्ठा must क्रमm a prefix of काष्ठा pt_regs.
 */
काष्ठा user_regs_काष्ठा अणु
	अचिन्हित दीर्घ pc;
	अचिन्हित दीर्घ ra;
	अचिन्हित दीर्घ sp;
	अचिन्हित दीर्घ gp;
	अचिन्हित दीर्घ tp;
	अचिन्हित दीर्घ t0;
	अचिन्हित दीर्घ t1;
	अचिन्हित दीर्घ t2;
	अचिन्हित दीर्घ s0;
	अचिन्हित दीर्घ s1;
	अचिन्हित दीर्घ a0;
	अचिन्हित दीर्घ a1;
	अचिन्हित दीर्घ a2;
	अचिन्हित दीर्घ a3;
	अचिन्हित दीर्घ a4;
	अचिन्हित दीर्घ a5;
	अचिन्हित दीर्घ a6;
	अचिन्हित दीर्घ a7;
	अचिन्हित दीर्घ s2;
	अचिन्हित दीर्घ s3;
	अचिन्हित दीर्घ s4;
	अचिन्हित दीर्घ s5;
	अचिन्हित दीर्घ s6;
	अचिन्हित दीर्घ s7;
	अचिन्हित दीर्घ s8;
	अचिन्हित दीर्घ s9;
	अचिन्हित दीर्घ s10;
	अचिन्हित दीर्घ s11;
	अचिन्हित दीर्घ t3;
	अचिन्हित दीर्घ t4;
	अचिन्हित दीर्घ t5;
	अचिन्हित दीर्घ t6;
पूर्ण;

काष्ठा __riscv_f_ext_state अणु
	__u32 f[32];
	__u32 fcsr;
पूर्ण;

काष्ठा __riscv_d_ext_state अणु
	__u64 f[32];
	__u32 fcsr;
पूर्ण;

काष्ठा __riscv_q_ext_state अणु
	__u64 f[64] __attribute__((aligned(16)));
	__u32 fcsr;
	/*
	 * Reserved क्रम expansion of sigcontext काष्ठाure.  Currently zeroed
	 * upon संकेत, and must be zero upon sigवापस.
	 */
	__u32 reserved[3];
पूर्ण;

जोड़ __riscv_fp_state अणु
	काष्ठा __riscv_f_ext_state f;
	काष्ठा __riscv_d_ext_state d;
	काष्ठा __riscv_q_ext_state q;
पूर्ण;

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _UAPI_ASM_RISCV_PTRACE_H */
