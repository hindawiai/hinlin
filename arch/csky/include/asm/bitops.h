<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_BITOPS_H
#घोषणा __ASM_CSKY_BITOPS_H

#समावेश <linux/compiler.h>
#समावेश <यंत्र/barrier.h>

/*
 * यंत्र-generic/bitops/ffs.h
 */
अटल अंतरभूत पूर्णांक ffs(पूर्णांक x)
अणु
	अगर (!x)
		वापस 0;

	यंत्र अस्थिर (
		"brev %0\n"
		"ff1  %0\n"
		"addi %0, 1\n"
		: "=&r"(x)
		: "0"(x));
	वापस x;
पूर्ण

/*
 * यंत्र-generic/bitops/__ffs.h
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ __ffs(अचिन्हित दीर्घ x)
अणु
	यंत्र अस्थिर (
		"brev %0\n"
		"ff1  %0\n"
		: "=&r"(x)
		: "0"(x));
	वापस x;
पूर्ण

/*
 * यंत्र-generic/bitops/fls.h
 */
अटल __always_अंतरभूत पूर्णांक fls(अचिन्हित पूर्णांक x)
अणु
	यंत्र अस्थिर(
		"ff1 %0\n"
		: "=&r"(x)
		: "0"(x));

	वापस (32 - x);
पूर्ण

/*
 * यंत्र-generic/bitops/__fls.h
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ __fls(अचिन्हित दीर्घ x)
अणु
	वापस fls(x) - 1;
पूर्ण

#समावेश <यंत्र-generic/bitops/ffz.h>
#समावेश <यंत्र-generic/bitops/fls64.h>
#समावेश <यंत्र-generic/bitops/find.h>

#अगर_अघोषित _LINUX_BITOPS_H
#त्रुटि only <linux/bitops.h> can be included directly
#पूर्ण_अगर

#समावेश <यंत्र-generic/bitops/sched.h>
#समावेश <यंत्र-generic/bitops/hweight.h>
#समावेश <यंत्र-generic/bitops/lock.h>
#समावेश <यंत्र-generic/bitops/atomic.h>

/*
 * bug fix, why only could use atomic!!!!
 */
#समावेश <यंत्र-generic/bitops/non-atomic.h>
#घोषणा __clear_bit(nr, vaddr) clear_bit(nr, vaddr)

#समावेश <यंत्र-generic/bitops/le.h>
#समावेश <यंत्र-generic/bitops/ext2-atomic.h>
#पूर्ण_अगर /* __ASM_CSKY_BITOPS_H */
