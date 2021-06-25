<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_TRAP_PF_H
#घोषणा _ASM_X86_TRAP_PF_H

/*
 * Page fault error code bits:
 *
 *   bit 0 ==	 0: no page found	1: protection fault
 *   bit 1 ==	 0: पढ़ो access		1: ग_लिखो access
 *   bit 2 ==	 0: kernel-mode access	1: user-mode access
 *   bit 3 ==				1: use of reserved bit detected
 *   bit 4 ==				1: fault was an inकाष्ठाion fetch
 *   bit 5 ==				1: protection keys block access
 *   bit 15 ==				1: SGX MMU page-fault
 */
क्रमागत x86_pf_error_code अणु
	X86_PF_PROT	=		1 << 0,
	X86_PF_WRITE	=		1 << 1,
	X86_PF_USER	=		1 << 2,
	X86_PF_RSVD	=		1 << 3,
	X86_PF_INSTR	=		1 << 4,
	X86_PF_PK	=		1 << 5,
	X86_PF_SGX	=		1 << 15,
पूर्ण;

#पूर्ण_अगर /* _ASM_X86_TRAP_PF_H */
