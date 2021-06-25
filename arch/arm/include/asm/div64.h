<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARM_DIV64
#घोषणा __ASM_ARM_DIV64

#समावेश <linux/types.h>
#समावेश <यंत्र/compiler.h>

/*
 * The semantics of __भाग64_32() are:
 *
 * uपूर्णांक32_t __भाग64_32(uपूर्णांक64_t *n, uपूर्णांक32_t base)
 * अणु
 * 	uपूर्णांक32_t reमुख्यder = *n % base;
 * 	*n = *n / base;
 * 	वापस reमुख्यder;
 * पूर्ण
 *
 * In other words, a 64-bit भागidend with a 32-bit भागisor producing
 * a 64-bit result and a 32-bit reमुख्यder.  To accomplish this optimally
 * we override the generic version in lib/भाग64.c to call our __करो_भाग64
 * assembly implementation with completely non standard calling convention
 * क्रम arguments and results (beware).
 */
अटल अंतरभूत uपूर्णांक32_t __भाग64_32(uपूर्णांक64_t *n, uपूर्णांक32_t base)
अणु
	रेजिस्टर अचिन्हित पूर्णांक __base      यंत्र("r4") = base;
	रेजिस्टर अचिन्हित दीर्घ दीर्घ __n   यंत्र("r0") = *n;
	रेजिस्टर अचिन्हित दीर्घ दीर्घ __res यंत्र("r2");
	अचिन्हित पूर्णांक __rem;
	यंत्र(	__यंत्रeq("%0", "r0")
		__यंत्रeq("%1", "r2")
		__यंत्रeq("%2", "r4")
		"bl	__do_div64"
		: "+r" (__n), "=r" (__res)
		: "r" (__base)
		: "ip", "lr", "cc");
	__rem = __n >> 32;
	*n = __res;
	वापस __rem;
पूर्ण
#घोषणा __भाग64_32 __भाग64_32

#अगर !defined(CONFIG_AEABI)

/*
 * In OABI configurations, some uses of the करो_भाग function
 * cause gcc to run out of रेजिस्टरs. To work around that,
 * we can क्रमce the use of the out-of-line version क्रम
 * configurations that build a OABI kernel.
 */
#घोषणा करो_भाग(n, base) __भाग64_32(&(n), base)

#अन्यथा

/*
 * gcc versions earlier than 4.0 are simply too problematic क्रम the
 * __भाग64_स्थिर32() code in यंत्र-generic/भाग64.h. First there is
 * gcc PR 15089 that tend to trig on more complex स्थिरructs, spurious
 * .global __uभागsi3 are inserted even अगर none of those symbols are
 * referenced in the generated code, and those gcc versions are not able
 * to करो स्थिरant propagation on दीर्घ दीर्घ values anyway.
 */

#घोषणा __भाग64_स्थिर32_is_OK (__GNUC__ >= 4)

अटल अंतरभूत uपूर्णांक64_t __arch_xprod_64(uपूर्णांक64_t m, uपूर्णांक64_t n, bool bias)
अणु
	अचिन्हित दीर्घ दीर्घ res;
	रेजिस्टर अचिन्हित पूर्णांक पंचांगp यंत्र("ip") = 0;

	अगर (!bias) अणु
		यंत्र (	"umull	%Q0, %R0, %Q1, %Q2\n\t"
			"mov	%Q0, #0"
			: "=&r" (res)
			: "r" (m), "r" (n)
			: "cc");
	पूर्ण अन्यथा अगर (!(m & ((1ULL << 63) | (1ULL << 31)))) अणु
		res = m;
		यंत्र (	"umlal	%Q0, %R0, %Q1, %Q2\n\t"
			"mov	%Q0, #0"
			: "+&r" (res)
			: "r" (m), "r" (n)
			: "cc");
	पूर्ण अन्यथा अणु
		यंत्र (	"umull	%Q0, %R0, %Q2, %Q3\n\t"
			"cmn	%Q0, %Q2\n\t"
			"adcs	%R0, %R0, %R2\n\t"
			"adc	%Q0, %1, #0"
			: "=&r" (res), "+&r" (पंचांगp)
			: "r" (m), "r" (n)
			: "cc");
	पूर्ण

	अगर (!(m & ((1ULL << 63) | (1ULL << 31)))) अणु
		यंत्र (	"umlal	%R0, %Q0, %R1, %Q2\n\t"
			"umlal	%R0, %Q0, %Q1, %R2\n\t"
			"mov	%R0, #0\n\t"
			"umlal	%Q0, %R0, %R1, %R2"
			: "+&r" (res)
			: "r" (m), "r" (n)
			: "cc");
	पूर्ण अन्यथा अणु
		यंत्र (	"umlal	%R0, %Q0, %R2, %Q3\n\t"
			"umlal	%R0, %1, %Q2, %R3\n\t"
			"mov	%R0, #0\n\t"
			"adds	%Q0, %1, %Q0\n\t"
			"adc	%R0, %R0, #0\n\t"
			"umlal	%Q0, %R0, %R2, %R3"
			: "+&r" (res), "+&r" (पंचांगp)
			: "r" (m), "r" (n)
			: "cc");
	पूर्ण

	वापस res;
पूर्ण
#घोषणा __arch_xprod_64 __arch_xprod_64

#समावेश <यंत्र-generic/भाग64.h>

#पूर्ण_अगर

#पूर्ण_अगर
