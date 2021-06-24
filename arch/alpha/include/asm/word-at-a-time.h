<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_WORD_AT_A_TIME_H
#घोषणा _ASM_WORD_AT_A_TIME_H

#समावेश <यंत्र/compiler.h>

/*
 * word-at-a-समय पूर्णांकerface क्रम Alpha.
 */

/*
 * We करो not use the word_at_a_समय काष्ठा on Alpha, but it needs to be
 * implemented to humour the generic code.
 */
काष्ठा word_at_a_समय अणु
	स्थिर अचिन्हित दीर्घ unused;
पूर्ण;

#घोषणा WORD_AT_A_TIME_CONSTANTS अणु 0 पूर्ण

/* Return nonzero अगर val has a zero */
अटल अंतरभूत अचिन्हित दीर्घ has_zero(अचिन्हित दीर्घ val, अचिन्हित दीर्घ *bits, स्थिर काष्ठा word_at_a_समय *c)
अणु
	अचिन्हित दीर्घ zero_locations = __kernel_cmpbge(0, val);
	*bits = zero_locations;
	वापस zero_locations;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ prep_zero_mask(अचिन्हित दीर्घ val, अचिन्हित दीर्घ bits, स्थिर काष्ठा word_at_a_समय *c)
अणु
	वापस bits;
पूर्ण

#घोषणा create_zero_mask(bits) (bits)

अटल अंतरभूत अचिन्हित दीर्घ find_zero(अचिन्हित दीर्घ bits)
अणु
#अगर defined(CONFIG_ALPHA_EV6) && defined(CONFIG_ALPHA_EV67)
	/* Simple अगर have CIX inकाष्ठाions */
	वापस __kernel_cttz(bits);
#अन्यथा
	अचिन्हित दीर्घ t1, t2, t3;
	/* Retain lowest set bit only */
	bits &= -bits;
	/* Binary search क्रम lowest set bit */
	t1 = bits & 0xf0;
	t2 = bits & 0xcc;
	t3 = bits & 0xaa;
	अगर (t1) t1 = 4;
	अगर (t2) t2 = 2;
	अगर (t3) t3 = 1;
	वापस t1 + t2 + t3;
#पूर्ण_अगर
पूर्ण

#घोषणा zero_bytemask(mask) ((2ul << (find_zero(mask) * 8)) - 1)

#पूर्ण_अगर /* _ASM_WORD_AT_A_TIME_H */
