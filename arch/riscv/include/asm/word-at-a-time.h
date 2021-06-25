<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 *
 * Derived from arch/x86/include/यंत्र/word-at-a-समय.स
 */

#अगर_अघोषित _ASM_RISCV_WORD_AT_A_TIME_H
#घोषणा _ASM_RISCV_WORD_AT_A_TIME_H


#समावेश <linux/kernel.h>

काष्ठा word_at_a_समय अणु
	स्थिर अचिन्हित दीर्घ one_bits, high_bits;
पूर्ण;

#घोषणा WORD_AT_A_TIME_CONSTANTS अणु REPEAT_BYTE(0x01), REPEAT_BYTE(0x80) पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ has_zero(अचिन्हित दीर्घ val,
	अचिन्हित दीर्घ *bits, स्थिर काष्ठा word_at_a_समय *c)
अणु
	अचिन्हित दीर्घ mask = ((val - c->one_bits) & ~val) & c->high_bits;
	*bits = mask;
	वापस mask;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ prep_zero_mask(अचिन्हित दीर्घ val,
	अचिन्हित दीर्घ bits, स्थिर काष्ठा word_at_a_समय *c)
अणु
	वापस bits;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ create_zero_mask(अचिन्हित दीर्घ bits)
अणु
	bits = (bits - 1) & ~bits;
	वापस bits >> 7;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ find_zero(अचिन्हित दीर्घ mask)
अणु
	वापस fls64(mask) >> 3;
पूर्ण

/* The mask we created is directly usable as a bytemask */
#घोषणा zero_bytemask(mask) (mask)

#पूर्ण_अगर /* _ASM_RISCV_WORD_AT_A_TIME_H */
