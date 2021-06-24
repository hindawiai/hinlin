<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
#अगर_अघोषित _ASM_POWERPC_SIGCONTEXT_H
#घोषणा _ASM_POWERPC_SIGCONTEXT_H

/*
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#समावेश <linux/compiler.h>
#समावेश <यंत्र/ptrace.h>
#अगर_घोषित __घातerpc64__
#समावेश <यंत्र/elf.h>
#पूर्ण_अगर

काष्ठा sigcontext अणु
	अचिन्हित दीर्घ	_unused[4];
	पूर्णांक		संकेत;
#अगर_घोषित __घातerpc64__
	पूर्णांक		_pad0;
#पूर्ण_अगर
	अचिन्हित दीर्घ	handler;
	अचिन्हित दीर्घ	oldmask;
#अगर_घोषित __KERNEL__
	काष्ठा user_pt_regs __user *regs;
#अन्यथा
	काष्ठा pt_regs	*regs;
#पूर्ण_अगर
#अगर_घोषित __घातerpc64__
	elf_gregset_t	gp_regs;
	elf_fpregset_t	fp_regs;
/*
 * To मुख्यtain compatibility with current implementations the sigcontext is
 * extended by appending a poपूर्णांकer (v_regs) to a quadword type (elf_vrreg_t)
 * followed by an unकाष्ठाured (vmx_reserve) field of 101 द्विगुनwords. This
 * allows the array of vector रेजिस्टरs to be quadword aligned independent of
 * the alignment of the containing sigcontext or ucontext. It is the
 * responsibility of the code setting the sigcontext to set this poपूर्णांकer to
 * either शून्य (अगर this processor करोes not support the VMX feature) or the
 * address of the first quadword within the allocated (vmx_reserve) area.
 *
 * The poपूर्णांकer (v_regs) of vector type (elf_vrreg_t) is type compatible with
 * an array of 34 quadword entries (elf_vrregset_t).  The entries with
 * indexes 0-31 contain the corresponding vector रेजिस्टरs.  The entry with
 * index 32 contains the vscr as the last word (offset 12) within the
 * quadword.  This allows the vscr to be stored as either a quadword (since
 * it must be copied via a vector रेजिस्टर to/from storage) or as a word.
 * The entry with index 33 contains the vrsave as the first word (offset 0)
 * within the quadword.
 *
 * Part of the VSX data is stored here also by extending vmx_restore
 * by an additional 32 द्विगुन words.  Architecturally the layout of
 * the VSR रेजिस्टरs and how they overlap on top of the legacy FPR and
 * VR रेजिस्टरs is shown below:
 *
 *                    VSR द्विगुनword 0               VSR द्विगुनword 1
 *           ----------------------------------------------------------------
 *   VSR[0]  |             FPR[0]            |                              |
 *           ----------------------------------------------------------------
 *   VSR[1]  |             FPR[1]            |                              |
 *           ----------------------------------------------------------------
 *           |              ...              |                              |
 *           |              ...              |                              |
 *           ----------------------------------------------------------------
 *   VSR[30] |             FPR[30]           |                              |
 *           ----------------------------------------------------------------
 *   VSR[31] |             FPR[31]           |                              |
 *           ----------------------------------------------------------------
 *   VSR[32] |                             VR[0]                            |
 *           ----------------------------------------------------------------
 *   VSR[33] |                             VR[1]                            |
 *           ----------------------------------------------------------------
 *           |                              ...                             |
 *           |                              ...                             |
 *           ----------------------------------------------------------------
 *   VSR[62] |                             VR[30]                           |
 *           ----------------------------------------------------------------
 *   VSR[63] |                             VR[31]                           |
 *           ----------------------------------------------------------------
 *
 * FPR/VSR 0-31 द्विगुनword 0 is stored in fp_regs, and VMX/VSR 32-63
 * is stored at the start of vmx_reserve.  vmx_reserve is extended क्रम
 * backwards compatility to store VSR 0-31 द्विगुनword 1 after the VMX
 * रेजिस्टरs and vscr/vrsave.
 */
	elf_vrreg_t	__user *v_regs;
	दीर्घ		vmx_reserve[ELF_NVRREG + ELF_NVRREG + 1 + 32];
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर /* _ASM_POWERPC_SIGCONTEXT_H */
