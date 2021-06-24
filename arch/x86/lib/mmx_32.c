<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	MMX 3DNow! library helper functions
 *
 *	To करो:
 *	We can use MMX just क्रम prefetch in IRQ's. This may be a win.
 *		(reported so on K6-III)
 *	We should use a better code neutral filler क्रम the लघु jump
 *		leal ebx. [ebx] is apparently best क्रम K6-2, but Cyrix ??
 *	We also want to clobber the filler रेजिस्टर so we करोn't get any
 *		रेजिस्टर क्रमwarding stalls on the filler.
 *
 *	Add *user handling. Checksums are not a win with MMX on any CPU
 *	tested so far क्रम any MMX solution figured.
 *
 *	22/09/2000 - Arjan van de Ven
 *		Improved क्रम non-engineering-sample Athlons
 *
 */
#समावेश <linux/hardirq.h>
#समावेश <linux/माला.स>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/fpu/api.h>
#समावेश <यंत्र/यंत्र.h>

/*
 * Use KFPU_387.  MMX inकाष्ठाions are not affected by MXCSR,
 * but both AMD and Intel करोcumentation states that even पूर्णांकeger MMX
 * operations will result in #MF अगर an exception is pending in FCW.
 *
 * EMMS is not needed afterwards because, after calling kernel_fpu_end(),
 * any subsequent user of the 387 stack will reinitialize it using
 * KFPU_387.
 */

व्योम *_mmx_स_नकल(व्योम *to, स्थिर व्योम *from, माप_प्रकार len)
अणु
	व्योम *p;
	पूर्णांक i;

	अगर (unlikely(in_पूर्णांकerrupt()))
		वापस __स_नकल(to, from, len);

	p = to;
	i = len >> 6; /* len/64 */

	kernel_fpu_begin_mask(KFPU_387);

	__यंत्र__ __अस्थिर__ (
		"1: prefetch (%0)\n"		/* This set is 28 bytes */
		"   prefetch 64(%0)\n"
		"   prefetch 128(%0)\n"
		"   prefetch 192(%0)\n"
		"   prefetch 256(%0)\n"
		"2:  \n"
		".section .fixup, \"ax\"\n"
		"3: movw $0x1AEB, 1b\n"	/* jmp on 26 bytes */
		"   jmp 2b\n"
		".previous\n"
			_ASM_EXTABLE(1b, 3b)
			: : "r" (from));

	क्रम ( ; i > 5; i--) अणु
		__यंत्र__ __अस्थिर__ (
		"1:  prefetch 320(%0)\n"
		"2:  movq (%0), %%mm0\n"
		"  movq 8(%0), %%mm1\n"
		"  movq 16(%0), %%mm2\n"
		"  movq 24(%0), %%mm3\n"
		"  movq %%mm0, (%1)\n"
		"  movq %%mm1, 8(%1)\n"
		"  movq %%mm2, 16(%1)\n"
		"  movq %%mm3, 24(%1)\n"
		"  movq 32(%0), %%mm0\n"
		"  movq 40(%0), %%mm1\n"
		"  movq 48(%0), %%mm2\n"
		"  movq 56(%0), %%mm3\n"
		"  movq %%mm0, 32(%1)\n"
		"  movq %%mm1, 40(%1)\n"
		"  movq %%mm2, 48(%1)\n"
		"  movq %%mm3, 56(%1)\n"
		".section .fixup, \"ax\"\n"
		"3: movw $0x05EB, 1b\n"	/* jmp on 5 bytes */
		"   jmp 2b\n"
		".previous\n"
			_ASM_EXTABLE(1b, 3b)
			: : "r" (from), "r" (to) : "memory");

		from += 64;
		to += 64;
	पूर्ण

	क्रम ( ; i > 0; i--) अणु
		__यंत्र__ __अस्थिर__ (
		"  movq (%0), %%mm0\n"
		"  movq 8(%0), %%mm1\n"
		"  movq 16(%0), %%mm2\n"
		"  movq 24(%0), %%mm3\n"
		"  movq %%mm0, (%1)\n"
		"  movq %%mm1, 8(%1)\n"
		"  movq %%mm2, 16(%1)\n"
		"  movq %%mm3, 24(%1)\n"
		"  movq 32(%0), %%mm0\n"
		"  movq 40(%0), %%mm1\n"
		"  movq 48(%0), %%mm2\n"
		"  movq 56(%0), %%mm3\n"
		"  movq %%mm0, 32(%1)\n"
		"  movq %%mm1, 40(%1)\n"
		"  movq %%mm2, 48(%1)\n"
		"  movq %%mm3, 56(%1)\n"
			: : "r" (from), "r" (to) : "memory");

		from += 64;
		to += 64;
	पूर्ण
	/*
	 * Now करो the tail of the block:
	 */
	__स_नकल(to, from, len & 63);
	kernel_fpu_end();

	वापस p;
पूर्ण
EXPORT_SYMBOL(_mmx_स_नकल);

#अगर_घोषित CONFIG_MK7

/*
 *	The K7 has streaming cache bypass load/store. The Cyrix III, K6 and
 *	other MMX using processors करो not.
 */

अटल व्योम fast_clear_page(व्योम *page)
अणु
	पूर्णांक i;

	kernel_fpu_begin_mask(KFPU_387);

	__यंत्र__ __अस्थिर__ (
		"  pxor %%mm0, %%mm0\n" : :
	);

	क्रम (i = 0; i < 4096/64; i++) अणु
		__यंत्र__ __अस्थिर__ (
		"  movntq %%mm0, (%0)\n"
		"  movntq %%mm0, 8(%0)\n"
		"  movntq %%mm0, 16(%0)\n"
		"  movntq %%mm0, 24(%0)\n"
		"  movntq %%mm0, 32(%0)\n"
		"  movntq %%mm0, 40(%0)\n"
		"  movntq %%mm0, 48(%0)\n"
		"  movntq %%mm0, 56(%0)\n"
		: : "r" (page) : "memory");
		page += 64;
	पूर्ण

	/*
	 * Since movntq is weakly-ordered, a "sfence" is needed to become
	 * ordered again:
	 */
	__यंत्र__ __अस्थिर__("sfence\n"::);

	kernel_fpu_end();
पूर्ण

अटल व्योम fast_copy_page(व्योम *to, व्योम *from)
अणु
	पूर्णांक i;

	kernel_fpu_begin_mask(KFPU_387);

	/*
	 * maybe the prefetch stuff can go beक्रमe the expensive fnsave...
	 * but that is क्रम later. -AV
	 */
	__यंत्र__ __अस्थिर__(
		"1: prefetch (%0)\n"
		"   prefetch 64(%0)\n"
		"   prefetch 128(%0)\n"
		"   prefetch 192(%0)\n"
		"   prefetch 256(%0)\n"
		"2:  \n"
		".section .fixup, \"ax\"\n"
		"3: movw $0x1AEB, 1b\n"	/* jmp on 26 bytes */
		"   jmp 2b\n"
		".previous\n"
			_ASM_EXTABLE(1b, 3b) : : "r" (from));

	क्रम (i = 0; i < (4096-320)/64; i++) अणु
		__यंत्र__ __अस्थिर__ (
		"1: prefetch 320(%0)\n"
		"2: movq (%0), %%mm0\n"
		"   movntq %%mm0, (%1)\n"
		"   movq 8(%0), %%mm1\n"
		"   movntq %%mm1, 8(%1)\n"
		"   movq 16(%0), %%mm2\n"
		"   movntq %%mm2, 16(%1)\n"
		"   movq 24(%0), %%mm3\n"
		"   movntq %%mm3, 24(%1)\n"
		"   movq 32(%0), %%mm4\n"
		"   movntq %%mm4, 32(%1)\n"
		"   movq 40(%0), %%mm5\n"
		"   movntq %%mm5, 40(%1)\n"
		"   movq 48(%0), %%mm6\n"
		"   movntq %%mm6, 48(%1)\n"
		"   movq 56(%0), %%mm7\n"
		"   movntq %%mm7, 56(%1)\n"
		".section .fixup, \"ax\"\n"
		"3: movw $0x05EB, 1b\n"	/* jmp on 5 bytes */
		"   jmp 2b\n"
		".previous\n"
		_ASM_EXTABLE(1b, 3b) : : "r" (from), "r" (to) : "memory");

		from += 64;
		to += 64;
	पूर्ण

	क्रम (i = (4096-320)/64; i < 4096/64; i++) अणु
		__यंत्र__ __अस्थिर__ (
		"2: movq (%0), %%mm0\n"
		"   movntq %%mm0, (%1)\n"
		"   movq 8(%0), %%mm1\n"
		"   movntq %%mm1, 8(%1)\n"
		"   movq 16(%0), %%mm2\n"
		"   movntq %%mm2, 16(%1)\n"
		"   movq 24(%0), %%mm3\n"
		"   movntq %%mm3, 24(%1)\n"
		"   movq 32(%0), %%mm4\n"
		"   movntq %%mm4, 32(%1)\n"
		"   movq 40(%0), %%mm5\n"
		"   movntq %%mm5, 40(%1)\n"
		"   movq 48(%0), %%mm6\n"
		"   movntq %%mm6, 48(%1)\n"
		"   movq 56(%0), %%mm7\n"
		"   movntq %%mm7, 56(%1)\n"
			: : "r" (from), "r" (to) : "memory");
		from += 64;
		to += 64;
	पूर्ण
	/*
	 * Since movntq is weakly-ordered, a "sfence" is needed to become
	 * ordered again:
	 */
	__यंत्र__ __अस्थिर__("sfence \n"::);
	kernel_fpu_end();
पूर्ण

#अन्यथा /* CONFIG_MK7 */

/*
 *	Generic MMX implementation without K7 specअगरic streaming
 */
अटल व्योम fast_clear_page(व्योम *page)
अणु
	पूर्णांक i;

	kernel_fpu_begin_mask(KFPU_387);

	__यंत्र__ __अस्थिर__ (
		"  pxor %%mm0, %%mm0\n" : :
	);

	क्रम (i = 0; i < 4096/128; i++) अणु
		__यंत्र__ __अस्थिर__ (
		"  movq %%mm0, (%0)\n"
		"  movq %%mm0, 8(%0)\n"
		"  movq %%mm0, 16(%0)\n"
		"  movq %%mm0, 24(%0)\n"
		"  movq %%mm0, 32(%0)\n"
		"  movq %%mm0, 40(%0)\n"
		"  movq %%mm0, 48(%0)\n"
		"  movq %%mm0, 56(%0)\n"
		"  movq %%mm0, 64(%0)\n"
		"  movq %%mm0, 72(%0)\n"
		"  movq %%mm0, 80(%0)\n"
		"  movq %%mm0, 88(%0)\n"
		"  movq %%mm0, 96(%0)\n"
		"  movq %%mm0, 104(%0)\n"
		"  movq %%mm0, 112(%0)\n"
		"  movq %%mm0, 120(%0)\n"
			: : "r" (page) : "memory");
		page += 128;
	पूर्ण

	kernel_fpu_end();
पूर्ण

अटल व्योम fast_copy_page(व्योम *to, व्योम *from)
अणु
	पूर्णांक i;

	kernel_fpu_begin_mask(KFPU_387);

	__यंत्र__ __अस्थिर__ (
		"1: prefetch (%0)\n"
		"   prefetch 64(%0)\n"
		"   prefetch 128(%0)\n"
		"   prefetch 192(%0)\n"
		"   prefetch 256(%0)\n"
		"2:  \n"
		".section .fixup, \"ax\"\n"
		"3: movw $0x1AEB, 1b\n"	/* jmp on 26 bytes */
		"   jmp 2b\n"
		".previous\n"
			_ASM_EXTABLE(1b, 3b) : : "r" (from));

	क्रम (i = 0; i < 4096/64; i++) अणु
		__यंत्र__ __अस्थिर__ (
		"1: prefetch 320(%0)\n"
		"2: movq (%0), %%mm0\n"
		"   movq 8(%0), %%mm1\n"
		"   movq 16(%0), %%mm2\n"
		"   movq 24(%0), %%mm3\n"
		"   movq %%mm0, (%1)\n"
		"   movq %%mm1, 8(%1)\n"
		"   movq %%mm2, 16(%1)\n"
		"   movq %%mm3, 24(%1)\n"
		"   movq 32(%0), %%mm0\n"
		"   movq 40(%0), %%mm1\n"
		"   movq 48(%0), %%mm2\n"
		"   movq 56(%0), %%mm3\n"
		"   movq %%mm0, 32(%1)\n"
		"   movq %%mm1, 40(%1)\n"
		"   movq %%mm2, 48(%1)\n"
		"   movq %%mm3, 56(%1)\n"
		".section .fixup, \"ax\"\n"
		"3: movw $0x05EB, 1b\n"	/* jmp on 5 bytes */
		"   jmp 2b\n"
		".previous\n"
			_ASM_EXTABLE(1b, 3b)
			: : "r" (from), "r" (to) : "memory");

		from += 64;
		to += 64;
	पूर्ण
	kernel_fpu_end();
पूर्ण

#पूर्ण_अगर /* !CONFIG_MK7 */

/*
 * Favour MMX क्रम page clear and copy:
 */
अटल व्योम slow_zero_page(व्योम *page)
अणु
	पूर्णांक d0, d1;

	__यंत्र__ __अस्थिर__(
		"cld\n\t"
		"rep ; stosl"

			: "=&c" (d0), "=&D" (d1)
			:"a" (0), "1" (page), "0" (1024)
			:"memory");
पूर्ण

व्योम mmx_clear_page(व्योम *page)
अणु
	अगर (unlikely(in_पूर्णांकerrupt()))
		slow_zero_page(page);
	अन्यथा
		fast_clear_page(page);
पूर्ण
EXPORT_SYMBOL(mmx_clear_page);

अटल व्योम slow_copy_page(व्योम *to, व्योम *from)
अणु
	पूर्णांक d0, d1, d2;

	__यंत्र__ __अस्थिर__(
		"cld\n\t"
		"rep ; movsl"
		: "=&c" (d0), "=&D" (d1), "=&S" (d2)
		: "0" (1024), "1" ((दीर्घ) to), "2" ((दीर्घ) from)
		: "memory");
पूर्ण

व्योम mmx_copy_page(व्योम *to, व्योम *from)
अणु
	अगर (unlikely(in_पूर्णांकerrupt()))
		slow_copy_page(to, from);
	अन्यथा
		fast_copy_page(to, from);
पूर्ण
EXPORT_SYMBOL(mmx_copy_page);
