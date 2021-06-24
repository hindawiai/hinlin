<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PARISC_UACCESS_H
#घोषणा __PARISC_UACCESS_H

/*
 * User space memory access functions
 */
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/cache.h>

#समावेश <linux/bug.h>
#समावेश <linux/माला.स>

#घोषणा KERNEL_DS	((mm_segment_t)अणु0पूर्ण)
#घोषणा USER_DS 	((mm_segment_t)अणु1पूर्ण)

#घोषणा uaccess_kernel() (get_fs().seg == KERNEL_DS.seg)

#घोषणा get_fs()	(current_thपढ़ो_info()->addr_limit)
#घोषणा set_fs(x)	(current_thपढ़ो_info()->addr_limit = (x))

/*
 * Note that since kernel addresses are in a separate address space on
 * parisc, we करोn't need to करो anything क्रम access_ok().
 * We just let the page fault handler करो the right thing. This also means
 * that put_user is the same as __put_user, etc.
 */

#घोषणा access_ok(uaddr, size)	\
	( (uaddr) == (uaddr) )

#घोषणा put_user __put_user
#घोषणा get_user __get_user

#अगर !defined(CONFIG_64BIT)
#घोषणा LDD_USER(val, ptr)	__get_user_यंत्र64(val, ptr)
#घोषणा STD_USER(x, ptr)	__put_user_यंत्र64(x, ptr)
#अन्यथा
#घोषणा LDD_USER(val, ptr)	__get_user_यंत्र(val, "ldd", ptr)
#घोषणा STD_USER(x, ptr)	__put_user_यंत्र("std", x, ptr)
#पूर्ण_अगर

/*
 * The exception table contains two values: the first is the relative offset to
 * the address of the inकाष्ठाion that is allowed to fault, and the second is
 * the relative offset to the address of the fixup routine. Since relative
 * addresses are used, 32bit values are sufficient even on 64bit kernel.
 */

#घोषणा ARCH_HAS_RELATIVE_EXTABLE
काष्ठा exception_table_entry अणु
	पूर्णांक insn;	/* relative address of insn that is allowed to fault. */
	पूर्णांक fixup;	/* relative address of fixup routine */
पूर्ण;

#घोषणा ASM_EXCEPTIONTABLE_ENTRY( fault_addr, except_addr )\
	".section __ex_table,\"aw\"\n"			   \
	".word (" #fault_addr " - .), (" #except_addr " - .)\n\t" \
	".previous\n"

/*
 * ASM_EXCEPTIONTABLE_ENTRY_EFAULT() creates a special exception table entry
 * (with lowest bit set) क्रम which the fault handler in fixup_exception() will
 * load -EFAULT पूर्णांकo %r8 क्रम a पढ़ो or ग_लिखो fault, and zeroes the target
 * रेजिस्टर in हाल of a पढ़ो fault in get_user().
 */
#घोषणा ASM_EXCEPTIONTABLE_ENTRY_EFAULT( fault_addr, except_addr )\
	ASM_EXCEPTIONTABLE_ENTRY( fault_addr, except_addr + 1)

/*
 * load_sr2() preloads the space रेजिस्टर %%sr2 - based on the value of
 * get_fs() - with either a value of 0 to access kernel space (KERNEL_DS which
 * is 0), or with the current value of %%sr3 to access user space (USER_DS)
 * memory. The following __get_user_यंत्र() and __put_user_यंत्र() functions have
 * %%sr2 hard-coded to access the requested memory.
 */
#घोषणा load_sr2() \
	__यंत्र__(" or,=  %0,%%r0,%%r0\n\t"	\
		" mfsp %%sr3,%0\n\t"		\
		" mtsp %0,%%sr2\n\t"		\
		: : "r"(get_fs()) : )

#घोषणा __get_user_पूर्णांकernal(val, ptr)			\
(अणु							\
	रेजिस्टर दीर्घ __gu_err __यंत्र__ ("r8") = 0;	\
							\
	चयन (माप(*(ptr))) अणु			\
	हाल 1: __get_user_यंत्र(val, "ldb", ptr); अवरोध;	\
	हाल 2: __get_user_यंत्र(val, "ldh", ptr); अवरोध; \
	हाल 4: __get_user_यंत्र(val, "ldw", ptr); अवरोध; \
	हाल 8: LDD_USER(val, ptr); अवरोध;		\
	शेष: BUILD_BUG();				\
	पूर्ण						\
							\
	__gu_err;					\
पूर्ण)

#घोषणा __get_user(val, ptr)				\
(अणु							\
	load_sr2();					\
	__get_user_पूर्णांकernal(val, ptr);			\
पूर्ण)

#घोषणा __get_user_यंत्र(val, ldx, ptr)			\
अणु							\
	रेजिस्टर दीर्घ __gu_val;				\
							\
	__यंत्र__("1: " ldx " 0(%%sr2,%2),%0\n"		\
		"9:\n"					\
		ASM_EXCEPTIONTABLE_ENTRY_EFAULT(1b, 9b)	\
		: "=r"(__gu_val), "=r"(__gu_err)        \
		: "r"(ptr), "1"(__gu_err));		\
							\
	(val) = (__क्रमce __typeof__(*(ptr))) __gu_val;	\
पूर्ण

#अगर !defined(CONFIG_64BIT)

#घोषणा __get_user_यंत्र64(val, ptr)			\
अणु							\
	जोड़ अणु						\
		अचिन्हित दीर्घ दीर्घ	l;		\
		__typeof__(*(ptr))	t;		\
	पूर्ण __gu_पंचांगp;					\
							\
	__यंत्र__("   copy %%r0,%R0\n"			\
		"1: ldw 0(%%sr2,%2),%0\n"		\
		"2: ldw 4(%%sr2,%2),%R0\n"		\
		"9:\n"					\
		ASM_EXCEPTIONTABLE_ENTRY_EFAULT(1b, 9b)	\
		ASM_EXCEPTIONTABLE_ENTRY_EFAULT(2b, 9b)	\
		: "=&r"(__gu_पंचांगp.l), "=r"(__gu_err)	\
		: "r"(ptr), "1"(__gu_err));		\
							\
	(val) = __gu_पंचांगp.t;				\
पूर्ण

#पूर्ण_अगर /* !defined(CONFIG_64BIT) */


#घोषणा __put_user_पूर्णांकernal(x, ptr)				\
(अणु								\
	रेजिस्टर दीर्घ __pu_err __यंत्र__ ("r8") = 0;      	\
        __typeof__(*(ptr)) __x = (__typeof__(*(ptr)))(x);	\
								\
	चयन (माप(*(ptr))) अणु				\
	हाल 1: __put_user_यंत्र("stb", __x, ptr); अवरोध;		\
	हाल 2: __put_user_यंत्र("sth", __x, ptr); अवरोध;		\
	हाल 4: __put_user_यंत्र("stw", __x, ptr); अवरोध;		\
	हाल 8: STD_USER(__x, ptr); अवरोध;			\
	शेष: BUILD_BUG();					\
	पूर्ण							\
								\
	__pu_err;						\
पूर्ण)

#घोषणा __put_user(x, ptr)					\
(अणु								\
	load_sr2();						\
	__put_user_पूर्णांकernal(x, ptr);				\
पूर्ण)


/*
 * The "__put_user/kernel_asm()" macros tell gcc they पढ़ो from memory
 * instead of writing. This is because they करो not ग_लिखो to any memory
 * gcc knows about, so there are no aliasing issues. These macros must
 * also be aware that fixups are executed in the context of the fault,
 * and any रेजिस्टरs used there must be listed as clobbers.
 * r8 is alपढ़ोy listed as err.
 */

#घोषणा __put_user_यंत्र(stx, x, ptr)                         \
	__यंत्र__ __अस्थिर__ (                              \
		"1: " stx " %2,0(%%sr2,%1)\n"		    \
		"9:\n"					    \
		ASM_EXCEPTIONTABLE_ENTRY_EFAULT(1b, 9b)	    \
		: "=r"(__pu_err)                            \
		: "r"(ptr), "r"(x), "0"(__pu_err))


#अगर !defined(CONFIG_64BIT)

#घोषणा __put_user_यंत्र64(__val, ptr) करो अणु	    	    \
	__यंत्र__ __अस्थिर__ (				    \
		"1: stw %2,0(%%sr2,%1)\n"		    \
		"2: stw %R2,4(%%sr2,%1)\n"		    \
		"9:\n"					    \
		ASM_EXCEPTIONTABLE_ENTRY_EFAULT(1b, 9b)	    \
		ASM_EXCEPTIONTABLE_ENTRY_EFAULT(2b, 9b)	    \
		: "=r"(__pu_err)                            \
		: "r"(ptr), "r"(__val), "0"(__pu_err));	    \
पूर्ण जबतक (0)

#पूर्ण_अगर /* !defined(CONFIG_64BIT) */


/*
 * Complex access routines -- बाह्यal declarations
 */

बाह्य दीर्घ म_नकलन_from_user(अक्षर *, स्थिर अक्षर __user *, दीर्घ);
बाह्य अचिन्हित lclear_user(व्योम __user *, अचिन्हित दीर्घ);
बाह्य दीर्घ lstrnlen_user(स्थिर अक्षर __user *, दीर्घ);
/*
 * Complex access routines -- macros
 */
#घोषणा user_addr_max() (~0UL)

#घोषणा strnlen_user lstrnlen_user
#घोषणा clear_user lclear_user
#घोषणा __clear_user lclear_user

अचिन्हित दीर्घ __must_check raw_copy_to_user(व्योम __user *dst, स्थिर व्योम *src,
					    अचिन्हित दीर्घ len);
अचिन्हित दीर्घ __must_check raw_copy_from_user(व्योम *dst, स्थिर व्योम __user *src,
					    अचिन्हित दीर्घ len);
अचिन्हित दीर्घ __must_check raw_copy_in_user(व्योम __user *dst, स्थिर व्योम __user *src,
					    अचिन्हित दीर्घ len);
#घोषणा INLINE_COPY_TO_USER
#घोषणा INLINE_COPY_FROM_USER

काष्ठा pt_regs;
पूर्णांक fixup_exception(काष्ठा pt_regs *regs);

#पूर्ण_अगर /* __PARISC_UACCESS_H */
