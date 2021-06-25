<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_UACCESS_H
#घोषणा __ASM_CSKY_UACCESS_H

#घोषणा user_addr_max() \
	(uaccess_kernel() ? KERNEL_DS.seg : get_fs().seg)

अटल अंतरभूत पूर्णांक __access_ok(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ limit = current_thपढ़ो_info()->addr_limit.seg;

	वापस ((addr < limit) && ((addr + size) < limit));
पूर्ण
#घोषणा __access_ok __access_ok

/*
 * __put_user_fn
 */
बाह्य पूर्णांक __put_user_bad(व्योम);

#घोषणा __put_user_यंत्र_b(x, ptr, err)			\
करो अणु							\
	पूर्णांक errcode;					\
	__यंत्र__ __अस्थिर__(				\
	"1:     stb   %1, (%2,0)	\n"		\
	"       br    3f		\n"		\
	"2:     mov   %0, %3		\n"		\
	"       br    3f		\n"		\
	".section __ex_table, \"a\"	\n"		\
	".align   2			\n"		\
	".long    1b,2b			\n"		\
	".previous			\n"		\
	"3:				\n"		\
	: "=r"(err), "=r"(x), "=r"(ptr), "=r"(errcode)	\
	: "0"(err), "1"(x), "2"(ptr), "3"(-EFAULT)	\
	: "memory");					\
पूर्ण जबतक (0)

#घोषणा __put_user_यंत्र_h(x, ptr, err)			\
करो अणु							\
	पूर्णांक errcode;					\
	__यंत्र__ __अस्थिर__(				\
	"1:     sth   %1, (%2,0)	\n"		\
	"       br    3f		\n"		\
	"2:     mov   %0, %3		\n"		\
	"       br    3f		\n"		\
	".section __ex_table, \"a\"	\n"		\
	".align   2			\n"		\
	".long    1b,2b			\n"		\
	".previous			\n"		\
	"3:				\n"		\
	: "=r"(err), "=r"(x), "=r"(ptr), "=r"(errcode)	\
	: "0"(err), "1"(x), "2"(ptr), "3"(-EFAULT)	\
	: "memory");					\
पूर्ण जबतक (0)

#घोषणा __put_user_यंत्र_w(x, ptr, err)			\
करो अणु							\
	पूर्णांक errcode;					\
	__यंत्र__ __अस्थिर__(				\
	"1:     stw   %1, (%2,0)	\n"		\
	"       br    3f		\n"		\
	"2:     mov   %0, %3		\n"		\
	"       br    3f		\n"		\
	".section __ex_table,\"a\"	\n"		\
	".align   2			\n"		\
	".long    1b, 2b		\n"		\
	".previous			\n"		\
	"3:				\n"		\
	: "=r"(err), "=r"(x), "=r"(ptr), "=r"(errcode)	\
	: "0"(err), "1"(x), "2"(ptr), "3"(-EFAULT)	\
	: "memory");					\
पूर्ण जबतक (0)

#घोषणा __put_user_यंत्र_64(x, ptr, err)			\
करो अणु							\
	पूर्णांक पंचांगp;					\
	पूर्णांक errcode;					\
							\
	__यंत्र__ __अस्थिर__(				\
	"     ldw     %3, (%1, 0)     \n"		\
	"1:   stw     %3, (%2, 0)     \n"		\
	"     ldw     %3, (%1, 4)     \n"		\
	"2:   stw     %3, (%2, 4)     \n"		\
	"     br      4f              \n"		\
	"3:   mov     %0, %4          \n"		\
	"     br      4f              \n"		\
	".section __ex_table, \"a\"   \n"		\
	".align   2                   \n"		\
	".long    1b, 3b              \n"		\
	".long    2b, 3b              \n"		\
	".previous                    \n"		\
	"4:                           \n"		\
	: "=r"(err), "=r"(x), "=r"(ptr),		\
	  "=r"(पंचांगp), "=r"(errcode)			\
	: "0"(err), "1"(x), "2"(ptr), "3"(0),		\
	  "4"(-EFAULT)					\
	: "memory");					\
पूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक __put_user_fn(माप_प्रकार size, व्योम __user *ptr, व्योम *x)
अणु
	पूर्णांक retval = 0;
	u32 पंचांगp;

	चयन (size) अणु
	हाल 1:
		पंचांगp = *(u8 *)x;
		__put_user_यंत्र_b(पंचांगp, ptr, retval);
		अवरोध;
	हाल 2:
		पंचांगp = *(u16 *)x;
		__put_user_यंत्र_h(पंचांगp, ptr, retval);
		अवरोध;
	हाल 4:
		पंचांगp = *(u32 *)x;
		__put_user_यंत्र_w(पंचांगp, ptr, retval);
		अवरोध;
	हाल 8:
		__put_user_यंत्र_64(x, (u64 *)ptr, retval);
		अवरोध;
	पूर्ण

	वापस retval;
पूर्ण
#घोषणा __put_user_fn __put_user_fn

/*
 * __get_user_fn
 */
बाह्य पूर्णांक __get_user_bad(व्योम);

#घोषणा __get_user_यंत्र_common(x, ptr, ins, err)		\
करो अणु							\
	पूर्णांक errcode;					\
	__यंत्र__ __अस्थिर__(				\
	"1:   " ins " %1, (%4, 0)	\n"		\
	"       br    3f		\n"		\
	"2:     mov   %0, %2		\n"		\
	"       movi  %1, 0		\n"		\
	"       br    3f		\n"		\
	".section __ex_table,\"a\"      \n"		\
	".align   2			\n"		\
	".long    1b, 2b		\n"		\
	".previous			\n"		\
	"3:				\n" 		\
	: "=r"(err), "=r"(x), "=r"(errcode)		\
	: "0"(0), "r"(ptr), "2"(-EFAULT)		\
	: "memory");					\
पूर्ण जबतक (0)

#घोषणा __get_user_यंत्र_64(x, ptr, err)			\
करो अणु							\
	पूर्णांक पंचांगp;					\
	पूर्णांक errcode;					\
							\
	__यंत्र__ __अस्थिर__(				\
	"1:   ldw     %3, (%2, 0)     \n"		\
	"     stw     %3, (%1, 0)     \n"		\
	"2:   ldw     %3, (%2, 4)     \n"		\
	"     stw     %3, (%1, 4)     \n"		\
	"     br      4f              \n"		\
	"3:   mov     %0, %4          \n"		\
	"     br      4f              \n"		\
	".section __ex_table, \"a\"   \n"		\
	".align   2                   \n"		\
	".long    1b, 3b              \n"		\
	".long    2b, 3b              \n"		\
	".previous                    \n"		\
	"4:                           \n"		\
	: "=r"(err), "=r"(x), "=r"(ptr),		\
	  "=r"(पंचांगp), "=r"(errcode)			\
	: "0"(err), "1"(x), "2"(ptr), "3"(0),		\
	  "4"(-EFAULT)					\
	: "memory");					\
पूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक __get_user_fn(माप_प्रकार size, स्थिर व्योम __user *ptr, व्योम *x)
अणु
	पूर्णांक retval;
	u32 पंचांगp;

	चयन (size) अणु
	हाल 1:
		__get_user_यंत्र_common(पंचांगp, ptr, "ldb", retval);
		*(u8 *)x = (u8)पंचांगp;
		अवरोध;
	हाल 2:
		__get_user_यंत्र_common(पंचांगp, ptr, "ldh", retval);
		*(u16 *)x = (u16)पंचांगp;
		अवरोध;
	हाल 4:
		__get_user_यंत्र_common(पंचांगp, ptr, "ldw", retval);
		*(u32 *)x = (u32)पंचांगp;
		अवरोध;
	हाल 8:
		__get_user_यंत्र_64(x, ptr, retval);
		अवरोध;
	पूर्ण

	वापस retval;
पूर्ण
#घोषणा __get_user_fn __get_user_fn

अचिन्हित दीर्घ raw_copy_from_user(व्योम *to, स्थिर व्योम *from, अचिन्हित दीर्घ n);
अचिन्हित दीर्घ raw_copy_to_user(व्योम *to, स्थिर व्योम *from, अचिन्हित दीर्घ n);

अचिन्हित दीर्घ __clear_user(व्योम __user *to, अचिन्हित दीर्घ n);
#घोषणा __clear_user __clear_user

दीर्घ __म_नकलन_from_user(अक्षर *dst, स्थिर अक्षर *src, दीर्घ count);
#घोषणा __म_नकलन_from_user __म_नकलन_from_user

दीर्घ __strnlen_user(स्थिर अक्षर *s, दीर्घ n);
#घोषणा __strnlen_user __strnlen_user

#समावेश <यंत्र/segment.h>
#समावेश <यंत्र-generic/uaccess.h>

#पूर्ण_अगर /* __ASM_CSKY_UACCESS_H */
