<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_BITOPS_SCHED_H_
#घोषणा _ASM_GENERIC_BITOPS_SCHED_H_

#समावेश <linux/compiler.h>	/* unlikely() */
#समावेश <यंत्र/types.h>

/*
 * Every architecture must define this function. It's the fastest
 * way of searching a 100-bit biपंचांगap.  It's guaranteed that at least
 * one of the 100 bits is cleared.
 */
अटल अंतरभूत पूर्णांक sched_find_first_bit(स्थिर अचिन्हित दीर्घ *b)
अणु
#अगर BITS_PER_LONG == 64
	अगर (b[0])
		वापस __ffs(b[0]);
	वापस __ffs(b[1]) + 64;
#या_अगर BITS_PER_LONG == 32
	अगर (b[0])
		वापस __ffs(b[0]);
	अगर (b[1])
		वापस __ffs(b[1]) + 32;
	अगर (b[2])
		वापस __ffs(b[2]) + 64;
	वापस __ffs(b[3]) + 96;
#अन्यथा
#त्रुटि BITS_PER_LONG not defined
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* _ASM_GENERIC_BITOPS_SCHED_H_ */
