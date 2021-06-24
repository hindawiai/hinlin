<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_WORD_AT_A_TIME_H
#घोषणा __ASM_SH_WORD_AT_A_TIME_H

#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
# include <यंत्र-generic/word-at-a-समय.स>
#अन्यथा
/*
 * Little-endian version cribbed from x86.
 */
काष्ठा word_at_a_समय अणु
	स्थिर अचिन्हित दीर्घ one_bits, high_bits;
पूर्ण;

#घोषणा WORD_AT_A_TIME_CONSTANTS अणु REPEAT_BYTE(0x01), REPEAT_BYTE(0x80) पूर्ण

/* Carl Chatfield / Jan Achrenius G+ version क्रम 32-bit */
अटल अंतरभूत दीर्घ count_masked_bytes(दीर्घ mask)
अणु
	/* (000000 0000ff 00ffff ffffff) -> ( 1 1 2 3 ) */
	दीर्घ a = (0x0ff0001+mask) >> 23;
	/* Fix the 1 क्रम 00 हाल */
	वापस a & mask;
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

अटल अंतरभूत अचिन्हित दीर्घ create_zero_mask(अचिन्हित दीर्घ bits)
अणु
	bits = (bits - 1) & ~bits;
	वापस bits >> 7;
पूर्ण

/* The mask we created is directly usable as a bytemask */
#घोषणा zero_bytemask(mask) (mask)

अटल अंतरभूत अचिन्हित दीर्घ find_zero(अचिन्हित दीर्घ mask)
अणु
	वापस count_masked_bytes(mask);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
