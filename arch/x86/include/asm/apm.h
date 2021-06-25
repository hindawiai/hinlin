<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Machine specअगरic APM BIOS functions क्रम generic.
 *  Split out from apm.c by Osamu Tomita <tomita@cinet.co.jp>
 */

#अगर_अघोषित _ASM_X86_MACH_DEFAULT_APM_H
#घोषणा _ASM_X86_MACH_DEFAULT_APM_H

#अगर_घोषित APM_ZERO_SEGS
#	define APM_DO_ZERO_SEGS \
		"pushl %%ds\n\t" \
		"pushl %%es\n\t" \
		"xorl %%edx, %%edx\n\t" \
		"mov %%dx, %%ds\n\t" \
		"mov %%dx, %%es\n\t" \
		"mov %%dx, %%fs\n\t" \
		"mov %%dx, %%gs\n\t"
#	define APM_DO_POP_SEGS \
		"popl %%es\n\t" \
		"popl %%ds\n\t"
#अन्यथा
#	define APM_DO_ZERO_SEGS
#	define APM_DO_POP_SEGS
#पूर्ण_अगर

अटल अंतरभूत व्योम apm_bios_call_यंत्र(u32 func, u32 ebx_in, u32 ecx_in,
					u32 *eax, u32 *ebx, u32 *ecx,
					u32 *edx, u32 *esi)
अणु
	/*
	 * N.B. We करो NOT need a cld after the BIOS call
	 * because we always save and restore the flags.
	 */
	__यंत्र__ __अस्थिर__(APM_DO_ZERO_SEGS
		"pushl %%edi\n\t"
		"pushl %%ebp\n\t"
		"lcall *%%cs:apm_bios_entry\n\t"
		"setc %%al\n\t"
		"popl %%ebp\n\t"
		"popl %%edi\n\t"
		APM_DO_POP_SEGS
		: "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx),
		  "=S" (*esi)
		: "a" (func), "b" (ebx_in), "c" (ecx_in)
		: "memory", "cc");
पूर्ण

अटल अंतरभूत bool apm_bios_call_simple_यंत्र(u32 func, u32 ebx_in,
					    u32 ecx_in, u32 *eax)
अणु
	पूर्णांक	cx, dx, si;
	bool	error;

	/*
	 * N.B. We करो NOT need a cld after the BIOS call
	 * because we always save and restore the flags.
	 */
	__यंत्र__ __अस्थिर__(APM_DO_ZERO_SEGS
		"pushl %%edi\n\t"
		"pushl %%ebp\n\t"
		"lcall *%%cs:apm_bios_entry\n\t"
		"setc %%bl\n\t"
		"popl %%ebp\n\t"
		"popl %%edi\n\t"
		APM_DO_POP_SEGS
		: "=a" (*eax), "=b" (error), "=c" (cx), "=d" (dx),
		  "=S" (si)
		: "a" (func), "b" (ebx_in), "c" (ecx_in)
		: "memory", "cc");
	वापस error;
पूर्ण

#पूर्ण_अगर /* _ASM_X86_MACH_DEFAULT_APM_H */
