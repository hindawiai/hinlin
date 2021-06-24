<शैली गुरु>
#अगर_अघोषित _ASM_WORD_AT_A_TIME_H
#घोषणा _ASM_WORD_AT_A_TIME_H

/*
 * Word-at-a-समय पूर्णांकerfaces क्रम PowerPC.
 */

#समावेश <linux/kernel.h>
#समावेश <यंत्र/यंत्र-compat.h>
#समावेश <यंत्र/ppc_यंत्र.h>

#अगर_घोषित __BIG_ENDIAN__

काष्ठा word_at_a_समय अणु
	स्थिर अचिन्हित दीर्घ high_bits, low_bits;
पूर्ण;

#घोषणा WORD_AT_A_TIME_CONSTANTS अणु REPEAT_BYTE(0xfe) + 1, REPEAT_BYTE(0x7f) पूर्ण

/* Bit set in the bytes that have a zero */
अटल अंतरभूत दीर्घ prep_zero_mask(अचिन्हित दीर्घ val, अचिन्हित दीर्घ rhs, स्थिर काष्ठा word_at_a_समय *c)
अणु
	अचिन्हित दीर्घ mask = (val & c->low_bits) + c->low_bits;
	वापस ~(mask | rhs);
पूर्ण

#घोषणा create_zero_mask(mask) (mask)

अटल अंतरभूत दीर्घ find_zero(अचिन्हित दीर्घ mask)
अणु
	दीर्घ leading_zero_bits;

	यंत्र (PPC_CNTLZL "%0,%1" : "=r" (leading_zero_bits) : "r" (mask));
	वापस leading_zero_bits >> 3;
पूर्ण

अटल अंतरभूत bool has_zero(अचिन्हित दीर्घ val, अचिन्हित दीर्घ *data, स्थिर काष्ठा word_at_a_समय *c)
अणु
	अचिन्हित दीर्घ rhs = val | c->low_bits;
	*data = rhs;
	वापस (val + c->high_bits) & ~rhs;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ zero_bytemask(अचिन्हित दीर्घ mask)
अणु
	वापस ~1ul << __fls(mask);
पूर्ण

#अन्यथा

#अगर_घोषित CONFIG_64BIT

/* unused */
काष्ठा word_at_a_समय अणु
पूर्ण;

#घोषणा WORD_AT_A_TIME_CONSTANTS अणु पूर्ण

/* This will give us 0xff क्रम a शून्य अक्षर and 0x00 अन्यथाwhere */
अटल अंतरभूत अचिन्हित दीर्घ has_zero(अचिन्हित दीर्घ a, अचिन्हित दीर्घ *bits, स्थिर काष्ठा word_at_a_समय *c)
अणु
	अचिन्हित दीर्घ ret;
	अचिन्हित दीर्घ zero = 0;

	यंत्र("cmpb %0,%1,%2" : "=r" (ret) : "r" (a), "r" (zero));
	*bits = ret;

	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ prep_zero_mask(अचिन्हित दीर्घ a, अचिन्हित दीर्घ bits, स्थिर काष्ठा word_at_a_समय *c)
अणु
	वापस bits;
पूर्ण

/* Alan Modra's little-endian म_माप tail क्रम 64-bit */
अटल अंतरभूत अचिन्हित दीर्घ create_zero_mask(अचिन्हित दीर्घ bits)
अणु
	अचिन्हित दीर्घ leading_zero_bits;
	दीर्घ trailing_zero_bit_mask;

	यंत्र("addi	%1,%2,-1\n\t"
	    "andc	%1,%1,%2\n\t"
	    "popcntd	%0,%1"
		: "=r" (leading_zero_bits), "=&r" (trailing_zero_bit_mask)
		: "b" (bits));

	वापस leading_zero_bits;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ find_zero(अचिन्हित दीर्घ mask)
अणु
	वापस mask >> 3;
पूर्ण

/* This assumes that we never ask क्रम an all 1s biपंचांगask */
अटल अंतरभूत अचिन्हित दीर्घ zero_bytemask(अचिन्हित दीर्घ mask)
अणु
	वापस (1UL << mask) - 1;
पूर्ण

#अन्यथा	/* 32-bit हाल */

काष्ठा word_at_a_समय अणु
	स्थिर अचिन्हित दीर्घ one_bits, high_bits;
पूर्ण;

#घोषणा WORD_AT_A_TIME_CONSTANTS अणु REPEAT_BYTE(0x01), REPEAT_BYTE(0x80) पूर्ण

/*
 * This is largely generic क्रम little-endian machines, but the
 * optimal byte mask counting is probably going to be something
 * that is architecture-specअगरic. If you have a reliably fast
 * bit count inकाष्ठाion, that might be better than the multiply
 * and shअगरt, क्रम example.
 */

/* Carl Chatfield / Jan Achrenius G+ version क्रम 32-bit */
अटल अंतरभूत दीर्घ count_masked_bytes(दीर्घ mask)
अणु
	/* (000000 0000ff 00ffff ffffff) -> ( 1 1 2 3 ) */
	दीर्घ a = (0x0ff0001+mask) >> 23;
	/* Fix the 1 क्रम 00 हाल */
	वापस a & mask;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ create_zero_mask(अचिन्हित दीर्घ bits)
अणु
	bits = (bits - 1) & ~bits;
	वापस bits >> 7;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ find_zero(अचिन्हित दीर्घ mask)
अणु
	वापस count_masked_bytes(mask);
पूर्ण

/* Return nonzero अगर it has a zero */
अटल अंतरभूत अचिन्हित दीर्घ has_zero(अचिन्हित दीर्घ a, अचिन्हित दीर्घ *bits, स्थिर काष्ठा word_at_a_समय *c)
अणु
	अचिन्हित दीर्घ mask = ((a - c->one_bits) & ~a) & c->high_bits;
	*bits = mask;
	वापस mask;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ prep_zero_mask(अचिन्हित दीर्घ a, अचिन्हित दीर्घ bits, स्थिर काष्ठा word_at_a_समय *c)
अणु
	वापस bits;
पूर्ण

/* The mask we created is directly usable as a bytemask */
#घोषणा zero_bytemask(mask) (mask)

#पूर्ण_अगर /* CONFIG_64BIT */

#पूर्ण_अगर /* __BIG_ENDIAN__ */

/*
 * We use load_unaligned_zero() in a selftest, which builds a userspace
 * program. Some linker scripts seem to discard the .fixup section, so allow
 * the test code to use a dअगरferent section name.
 */
#अगर_अघोषित FIXUP_SECTION
#घोषणा FIXUP_SECTION ".fixup"
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित दीर्घ load_unaligned_zeropad(स्थिर व्योम *addr)
अणु
	अचिन्हित दीर्घ ret, offset, पंचांगp;

	यंत्र(
	"1:	" PPC_LL "%[ret], 0(%[addr])\n"
	"2:\n"
	".section " FIXUP_SECTION ",\"ax\"\n"
	"3:	"
#अगर_घोषित __घातerpc64__
	"clrrdi		%[tmp], %[addr], 3\n\t"
	"clrlsldi	%[offset], %[addr], 61, 3\n\t"
	"ld		%[ret], 0(%[tmp])\n\t"
#अगर_घोषित __BIG_ENDIAN__
	"sld		%[ret], %[ret], %[offset]\n\t"
#अन्यथा
	"srd		%[ret], %[ret], %[offset]\n\t"
#पूर्ण_अगर
#अन्यथा
	"clrrwi		%[tmp], %[addr], 2\n\t"
	"clrlslwi	%[offset], %[addr], 30, 3\n\t"
	"lwz		%[ret], 0(%[tmp])\n\t"
#अगर_घोषित __BIG_ENDIAN__
	"slw		%[ret], %[ret], %[offset]\n\t"
#अन्यथा
	"srw		%[ret], %[ret], %[offset]\n\t"
#पूर्ण_अगर
#पूर्ण_अगर
	"b	2b\n"
	".previous\n"
	EX_TABLE(1b, 3b)
	: [पंचांगp] "=&b" (पंचांगp), [offset] "=&r" (offset), [ret] "=&r" (ret)
	: [addr] "b" (addr), "m" (*(अचिन्हित दीर्घ *)addr));

	वापस ret;
पूर्ण

#अघोषित FIXUP_SECTION

#पूर्ण_अगर /* _ASM_WORD_AT_A_TIME_H */
