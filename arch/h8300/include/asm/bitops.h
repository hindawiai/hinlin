<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _H8300_BITOPS_H
#घोषणा _H8300_BITOPS_H

/*
 * Copyright 1992, Linus Torvalds.
 * Copyright 2002, Yoshinori Sato
 */

#समावेश <linux/compiler.h>

#समावेश <यंत्र-generic/bitops/fls.h>
#समावेश <यंत्र-generic/bitops/__fls.h>
#समावेश <यंत्र-generic/bitops/fls64.h>

#अगर_घोषित __KERNEL__

#अगर_अघोषित _LINUX_BITOPS_H
#त्रुटि only <linux/bitops.h> can be included directly
#पूर्ण_अगर

/*
 * Function prototypes to keep gcc -Wall happy
 */

/*
 * ffz = Find First Zero in word. Undefined अगर no zero exists,
 * so code should check against ~0UL first..
 */
अटल अंतरभूत अचिन्हित दीर्घ ffz(अचिन्हित दीर्घ word)
अणु
	अचिन्हित दीर्घ result;

	result = -1;
	__यंत्र__("1:\n\t"
		"shlr.l %1\n\t"
		"adds #1,%0\n\t"
		"bcs 1b"
		: "=r"(result),"=r"(word)
		: "0"(result), "1"(word));
	वापस result;
पूर्ण

#घोषणा H8300_GEN_BITOP(FNAME, OP)				\
अटल अंतरभूत व्योम FNAME(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)	\
अणु								\
	अचिन्हित अक्षर *b_addr;					\
	अचिन्हित अक्षर bit = nr & 7;				\
								\
	b_addr = (अचिन्हित अक्षर *)addr + ((nr >> 3) ^ 3);	\
	अगर (__builtin_स्थिरant_p(nr)) अणु				\
		__यंत्र__(OP " %1,%0" : "+WU"(*b_addr) : "i"(nr & 7));	\
	पूर्ण अन्यथा अणु						\
		__यंत्र__(OP " %s1,%0" : "+WU"(*b_addr) : "r"(bit));	\
	पूर्ण							\
पूर्ण

H8300_GEN_BITOP(set_bit,    "bset")
H8300_GEN_BITOP(clear_bit,  "bclr")
H8300_GEN_BITOP(change_bit, "bnot")
#घोषणा __set_bit(nr, addr)    set_bit((nr), (addr))
#घोषणा __clear_bit(nr, addr)  clear_bit((nr), (addr))
#घोषणा __change_bit(nr, addr) change_bit((nr), (addr))

#अघोषित H8300_GEN_BITOP

अटल अंतरभूत पूर्णांक test_bit(पूर्णांक nr, स्थिर अस्थिर अचिन्हित दीर्घ *addr)
अणु
	पूर्णांक ret = 0;
	अचिन्हित अक्षर *b_addr;
	अचिन्हित अक्षर bit = nr & 7;

	b_addr = (अचिन्हित अक्षर *)addr + ((nr >> 3) ^ 3);
	अगर (__builtin_स्थिरant_p(nr)) अणु
		__यंत्र__("bld %Z2,%1\n\t"
			"rotxl %0\n\t"
			: "=r"(ret)
			: "WU"(*b_addr), "i"(nr & 7), "0"(ret) : "cc");
	पूर्ण अन्यथा अणु
		__यंत्र__("btst %w2,%1\n\t"
			"beq 1f\n\t"
			"inc.l #1,%0\n"
			"1:"
			: "=r"(ret)
			: "WU"(*b_addr), "r"(bit), "0"(ret) : "cc");
	पूर्ण
	वापस ret;
पूर्ण

#घोषणा __test_bit(nr, addr) test_bit(nr, addr)

#घोषणा H8300_GEN_TEST_BITOP(FNNAME, OP)				\
अटल अंतरभूत पूर्णांक FNNAME(पूर्णांक nr, व्योम *addr)				\
अणु									\
	पूर्णांक retval = 0;							\
	अक्षर ccrsave;							\
	अचिन्हित अक्षर *b_addr;						\
	अचिन्हित अक्षर bit = nr & 7;					\
									\
	b_addr = (अचिन्हित अक्षर *)addr + ((nr >> 3) ^ 3);		\
	अगर (__builtin_स्थिरant_p(nr)) अणु					\
		__यंत्र__("stc ccr,%s2\n\t"				\
			"orc #0x80,ccr\n\t"				\
			"bld %4,%1\n\t"					\
			OP " %4,%1\n\t"					\
			"rotxl.l %0\n\t"				\
			"ldc %s2,ccr"					\
			: "=r"(retval), "+WU" (*b_addr), "=&r"(ccrsave)	\
			: "0"(retval), "i"(nr & 7) : "cc");		\
	पूर्ण अन्यथा अणु							\
		__यंत्र__("stc ccr,%t3\n\t"				\
			"orc #0x80,ccr\n\t"				\
			"btst %s3,%1\n\t"				\
			OP " %s3,%1\n\t"				\
			"beq 1f\n\t"					\
			"inc.l #1,%0\n\t"				\
			"1:\n"						\
			"ldc %t3,ccr"					\
			: "=r"(retval), "+WU" (*b_addr)			\
			: "0" (retval), "r"(bit) : "cc");		\
	पूर्ण								\
	वापस retval;							\
पूर्ण									\
									\
अटल अंतरभूत पूर्णांक __ ## FNNAME(पूर्णांक nr, व्योम *addr)			\
अणु									\
	पूर्णांक retval = 0;							\
	अचिन्हित अक्षर *b_addr;						\
	अचिन्हित अक्षर bit = nr & 7;					\
									\
	b_addr = (अचिन्हित अक्षर *)addr + ((nr >> 3) ^ 3);		\
	अगर (__builtin_स्थिरant_p(nr)) अणु					\
		__यंत्र__("bld %3,%1\n\t"					\
			OP " %3,%1\n\t"					\
			"rotxl.l %0\n\t"				\
			: "=r"(retval), "+WU"(*b_addr)			\
			: "0" (retval), "i"(nr & 7));			\
	पूर्ण अन्यथा अणु							\
		__यंत्र__("btst %s3,%1\n\t"				\
			OP " %s3,%1\n\t"				\
			"beq 1f\n\t"					\
			"inc.l #1,%0\n\t"				\
			"1:"						\
			: "=r"(retval), "+WU"(*b_addr)			\
			: "0" (retval), "r"(bit));			\
	पूर्ण								\
	वापस retval;							\
पूर्ण

H8300_GEN_TEST_BITOP(test_and_set_bit,	  "bset")
H8300_GEN_TEST_BITOP(test_and_clear_bit,  "bclr")
H8300_GEN_TEST_BITOP(test_and_change_bit, "bnot")
#अघोषित H8300_GEN_TEST_BITOP

#समावेश <यंत्र-generic/bitops/ffs.h>

अटल अंतरभूत अचिन्हित दीर्घ __ffs(अचिन्हित दीर्घ word)
अणु
	अचिन्हित दीर्घ result;

	result = -1;
	__यंत्र__("1:\n\t"
		"shlr.l %1\n\t"
		"adds #1,%0\n\t"
		"bcc 1b"
		: "=r" (result),"=r"(word)
		: "0"(result), "1"(word));
	वापस result;
पूर्ण

#समावेश <यंत्र-generic/bitops/find.h>
#समावेश <यंत्र-generic/bitops/sched.h>
#समावेश <यंत्र-generic/bitops/hweight.h>
#समावेश <यंत्र-generic/bitops/lock.h>
#समावेश <यंत्र-generic/bitops/le.h>
#समावेश <यंत्र-generic/bitops/ext2-atomic.h>

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _H8300_BITOPS_H */
