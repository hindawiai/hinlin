<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/include/यंत्र/fncpy.h - helper macros क्रम function body copying
 *
 * Copyright (C) 2011 Linaro Limited
 */

/*
 * These macros are पूर्णांकended क्रम use when there is a need to copy a low-level
 * function body पूर्णांकo special memory.
 *
 * For example, when reconfiguring the SDRAM controller, the code करोing the
 * reconfiguration may need to run from SRAM.
 *
 * NOTE: that the copied function body must be entirely self-contained and
 * position-independent in order क्रम this to work properly.
 *
 * NOTE: in order क्रम embedded literals and data to get referenced correctly,
 * the alignment of functions must be preserved when copying.  To ensure this,
 * the source and destination addresses क्रम fncpy() must be aligned to a
 * multiple of 8 bytes: you will be get a BUG() अगर this condition is not met.
 * You will typically need a ".align 3" directive in the assembler where the
 * function to be copied is defined, and ensure that your allocator क्रम the
 * destination buffer वापसs 8-byte-aligned poपूर्णांकers.
 *
 * Typical usage example:
 *
 * बाह्य पूर्णांक f(args);
 * बाह्य uपूर्णांक32_t size_of_f;
 * पूर्णांक (*copied_f)(args);
 * व्योम *sram_buffer;
 *
 * copied_f = fncpy(sram_buffer, &f, size_of_f);
 *
 * ... later, call the function: ...
 *
 * copied_f(args);
 *
 * The size of the function to be copied can't be determined from C:
 * this must be determined by other means, such as adding assmbler directives
 * in the file where f is defined.
 */

#अगर_अघोषित __ASM_FNCPY_H
#घोषणा __ASM_FNCPY_H

#समावेश <linux/types.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/bug.h>
#समावेश <यंत्र/cacheflush.h>

/*
 * Minimum alignment requirement क्रम the source and destination addresses
 * क्रम function copying.
 */
#घोषणा FNCPY_ALIGN 8

#घोषणा fncpy(dest_buf, funcp, size) (अणु					\
	uपूर्णांकptr_t __funcp_address;					\
	typeof(funcp) __result;						\
									\
	यंत्र("" : "=r" (__funcp_address) : "0" (funcp));			\
									\
	/*								\
	 * Ensure alignment of source and destination addresses,	\
	 * disregarding the function's Thumb bit:			\
	 */								\
	BUG_ON((uपूर्णांकptr_t)(dest_buf) & (FNCPY_ALIGN - 1) ||		\
		(__funcp_address & ~(uपूर्णांकptr_t)1 & (FNCPY_ALIGN - 1)));	\
									\
	स_नकल(dest_buf, (व्योम स्थिर *)(__funcp_address & ~1), size);	\
	flush_icache_range((अचिन्हित दीर्घ)(dest_buf),			\
		(अचिन्हित दीर्घ)(dest_buf) + (size));			\
									\
	यंत्र("" : "=r" (__result)					\
		: "0" ((uपूर्णांकptr_t)(dest_buf) | (__funcp_address & 1)));	\
									\
	__result;							\
पूर्ण)

#पूर्ण_अगर /* !__ASM_FNCPY_H */
