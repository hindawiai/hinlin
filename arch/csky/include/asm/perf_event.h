<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_PERF_EVENT_H
#घोषणा __ASM_CSKY_PERF_EVENT_H

#समावेश <abi/regdef.h>

#घोषणा perf_arch_fetch_caller_regs(regs, __ip) अणु \
	(regs)->pc = (__ip); \
	regs_fp(regs) = (अचिन्हित दीर्घ) __builtin_frame_address(0); \
	यंत्र अस्थिर("mov %0, sp\n":"=r"((regs)->usp)); \
पूर्ण

#पूर्ण_अगर /* __ASM_PERF_EVENT_ELF_H */
