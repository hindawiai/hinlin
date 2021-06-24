<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_UACCESS_H
#घोषणा _ASM_IA64_UACCESS_H

/*
 * This file defines various macros to transfer memory areas across
 * the user/kernel boundary.  This needs to be करोne carefully because
 * this code is executed in kernel mode and uses user-specअगरied
 * addresses.  Thus, we need to be careful not to let the user to
 * trick us पूर्णांकo accessing kernel memory that would normally be
 * inaccessible.  This code is also fairly perक्रमmance sensitive,
 * so we want to spend as little समय करोing safety checks as
 * possible.
 *
 * To make matters a bit more पूर्णांकeresting, these macros someबार also
 * called from within the kernel itself, in which हाल the address
 * validity check must be skipped.  The get_fs() macro tells us what
 * to करो: अगर get_fs()==USER_DS, checking is perक्रमmed, अगर
 * get_fs()==KERNEL_DS, checking is bypassed.
 *
 * Note that even अगर the memory area specअगरied by the user is in a
 * valid address range, it is still possible that we'll get a page
 * fault जबतक accessing it.  This is handled by filling out an
 * exception handler fixup entry क्रम each inकाष्ठाion that has the
 * potential to fault.  When such a fault occurs, the page fault
 * handler checks to see whether the faulting inकाष्ठाion has a fixup
 * associated and, अगर so, sets r8 to -EFAULT and clears r9 to 0 and
 * then resumes execution at the continuation poपूर्णांक.
 *
 * Based on <यंत्र-alpha/uaccess.h>.
 *
 * Copyright (C) 1998, 1999, 2001-2004 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */

#समावेश <linux/compiler.h>
#समावेश <linux/page-flags.h>

#समावेश <यंत्र/पूर्णांकrinsics.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/extable.h>

/*
 * For historical reasons, the following macros are grossly misnamed:
 */
#घोषणा KERNEL_DS	((mm_segment_t) अणु ~0UL पूर्ण)		/* cf. access_ok() */
#घोषणा USER_DS		((mm_segment_t) अणु TASK_SIZE-1 पूर्ण)	/* cf. access_ok() */

#घोषणा get_fs()  (current_thपढ़ो_info()->addr_limit)
#घोषणा set_fs(x) (current_thपढ़ो_info()->addr_limit = (x))

#घोषणा uaccess_kernel()	(get_fs().seg == KERNEL_DS.seg)

/*
 * When accessing user memory, we need to make sure the entire area really is in
 * user-level space.  In order to करो this efficiently, we make sure that the page at
 * address TASK_SIZE is never valid.  We also need to make sure that the address करोesn't
 * poपूर्णांक inside the भवly mapped linear page table.
 */
अटल अंतरभूत पूर्णांक __access_ok(स्थिर व्योम __user *p, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)p;
	अचिन्हित दीर्घ seg = get_fs().seg;
	वापस likely(addr <= seg) &&
	 (seg == KERNEL_DS.seg || likely(REGION_OFFSET(addr) < RGN_MAP_LIMIT));
पूर्ण
#घोषणा access_ok(addr, size)	__access_ok((addr), (size))

/*
 * These are the मुख्य single-value transfer routines.  They स्वतःmatically
 * use the right size अगर we just have the right poपूर्णांकer type.
 *
 * Careful to not
 * (a) re-use the arguments क्रम side effects (माप/typeof is ok)
 * (b) require any knowledge of processes at this stage
 */
#घोषणा put_user(x, ptr)	__put_user_check((__typeof__(*(ptr))) (x), (ptr), माप(*(ptr)))
#घोषणा get_user(x, ptr)	__get_user_check((x), (ptr), माप(*(ptr)))

/*
 * The "__xxx" versions करो not करो address space checking, useful when
 * करोing multiple accesses to the same area (the programmer has to करो the
 * checks by hand with "access_ok()")
 */
#घोषणा __put_user(x, ptr)	__put_user_nocheck((__typeof__(*(ptr))) (x), (ptr), माप(*(ptr)))
#घोषणा __get_user(x, ptr)	__get_user_nocheck((x), (ptr), माप(*(ptr)))

#अगर_घोषित ASM_SUPPORTED
  काष्ठा __large_काष्ठा अणु अचिन्हित दीर्घ buf[100]; पूर्ण;
# define __m(x) (*(काष्ठा __large_काष्ठा __user *)(x))

/* We need to declare the __ex_table section beक्रमe we can use it in .xdata.  */
यंत्र (".section \"__ex_table\", \"a\"\n\t.previous");

# define __get_user_size(val, addr, n, err)							\
करो अणु												\
	रेजिस्टर दीर्घ __gu_r8 यंत्र ("r8") = 0;							\
	रेजिस्टर दीर्घ __gu_r9 यंत्र ("r9");							\
	यंत्र ("\n[1:]\tld"#n" %0=%2%P2\t// %0 and %1 get overwritten by exception handler\n"	\
	     "\t.xdata4 \"__ex_table\", 1b-., 1f-.+4\n"						\
	     "[1:]"										\
	     : "=r"(__gu_r9), "=r"(__gu_r8) : "m"(__m(addr)), "1"(__gu_r8));			\
	(err) = __gu_r8;									\
	(val) = __gu_r9;									\
पूर्ण जबतक (0)

/*
 * The "__put_user_size()" macro tells gcc it पढ़ोs from memory instead of writing it.  This
 * is because they करो not ग_लिखो to any memory gcc knows about, so there are no aliasing
 * issues.
 */
# define __put_user_size(val, addr, n, err)							\
करो अणु												\
	रेजिस्टर दीर्घ __pu_r8 यंत्र ("r8") = 0;							\
	यंत्र अस्थिर ("\n[1:]\tst"#n" %1=%r2%P1\t// %0 gets overwritten by exception handler\n"	\
		      "\t.xdata4 \"__ex_table\", 1b-., 1f-.\n"					\
		      "[1:]"									\
		      : "=r"(__pu_r8) : "m"(__m(addr)), "rO"(val), "0"(__pu_r8));		\
	(err) = __pu_r8;									\
पूर्ण जबतक (0)

#अन्यथा /* !ASM_SUPPORTED */
# define RELOC_TYPE	2	/* ip-rel */
# define __get_user_size(val, addr, n, err)				\
करो अणु									\
	__ld_user("__ex_table", (अचिन्हित दीर्घ) addr, n, RELOC_TYPE);	\
	(err) = ia64_getreg(_IA64_REG_R8);				\
	(val) = ia64_getreg(_IA64_REG_R9);				\
पूर्ण जबतक (0)
# define __put_user_size(val, addr, n, err)				\
करो अणु									\
	__st_user("__ex_table", (अचिन्हित दीर्घ) addr, n, RELOC_TYPE,	\
		  (__क्रमce अचिन्हित दीर्घ) (val));			\
	(err) = ia64_getreg(_IA64_REG_R8);				\
पूर्ण जबतक (0)
#पूर्ण_अगर /* !ASM_SUPPORTED */

बाह्य व्योम __get_user_unknown (व्योम);

/*
 * Evaluating arguments X, PTR, SIZE, and SEGMENT may involve subroutine-calls, which
 * could clobber r8 and r9 (among others).  Thus, be careful not to evaluate it जबतक
 * using r8/r9.
 */
#घोषणा __करो_get_user(check, x, ptr, size)						\
(अणु											\
	स्थिर __typeof__(*(ptr)) __user *__gu_ptr = (ptr);				\
	__typeof__ (size) __gu_size = (size);						\
	दीर्घ __gu_err = -EFAULT;							\
	अचिन्हित दीर्घ __gu_val = 0;							\
	अगर (!check || __access_ok(__gu_ptr, size))					\
		चयन (__gu_size) अणु							\
		      हाल 1: __get_user_size(__gu_val, __gu_ptr, 1, __gu_err); अवरोध;	\
		      हाल 2: __get_user_size(__gu_val, __gu_ptr, 2, __gu_err); अवरोध;	\
		      हाल 4: __get_user_size(__gu_val, __gu_ptr, 4, __gu_err); अवरोध;	\
		      हाल 8: __get_user_size(__gu_val, __gu_ptr, 8, __gu_err); अवरोध;	\
		      शेष: __get_user_unknown(); अवरोध;				\
		पूर्ण									\
	(x) = (__क्रमce __typeof__(*(__gu_ptr))) __gu_val;				\
	__gu_err;									\
पूर्ण)

#घोषणा __get_user_nocheck(x, ptr, size)	__करो_get_user(0, x, ptr, size)
#घोषणा __get_user_check(x, ptr, size)	__करो_get_user(1, x, ptr, size)

बाह्य व्योम __put_user_unknown (व्योम);

/*
 * Evaluating arguments X, PTR, SIZE, and SEGMENT may involve subroutine-calls, which
 * could clobber r8 (among others).  Thus, be careful not to evaluate them जबतक using r8.
 */
#घोषणा __करो_put_user(check, x, ptr, size)						\
(अणु											\
	__typeof__ (x) __pu_x = (x);							\
	__typeof__ (*(ptr)) __user *__pu_ptr = (ptr);					\
	__typeof__ (size) __pu_size = (size);						\
	दीर्घ __pu_err = -EFAULT;							\
											\
	अगर (!check || __access_ok(__pu_ptr, __pu_size))					\
		चयन (__pu_size) अणु							\
		      हाल 1: __put_user_size(__pu_x, __pu_ptr, 1, __pu_err); अवरोध;	\
		      हाल 2: __put_user_size(__pu_x, __pu_ptr, 2, __pu_err); अवरोध;	\
		      हाल 4: __put_user_size(__pu_x, __pu_ptr, 4, __pu_err); अवरोध;	\
		      हाल 8: __put_user_size(__pu_x, __pu_ptr, 8, __pu_err); अवरोध;	\
		      शेष: __put_user_unknown(); अवरोध;				\
		पूर्ण									\
	__pu_err;									\
पूर्ण)

#घोषणा __put_user_nocheck(x, ptr, size)	__करो_put_user(0, x, ptr, size)
#घोषणा __put_user_check(x, ptr, size)	__करो_put_user(1, x, ptr, size)

/*
 * Complex access routines
 */
बाह्य अचिन्हित दीर्घ __must_check __copy_user (व्योम __user *to, स्थिर व्योम __user *from,
					       अचिन्हित दीर्घ count);

अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ count)
अणु
	वापस __copy_user(to, (__क्रमce व्योम __user *) from, count);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ count)
अणु
	वापस __copy_user((__क्रमce व्योम __user *) to, from, count);
पूर्ण

#घोषणा INLINE_COPY_FROM_USER
#घोषणा INLINE_COPY_TO_USER

बाह्य अचिन्हित दीर्घ __करो_clear_user (व्योम __user *, अचिन्हित दीर्घ);

#घोषणा __clear_user(to, n)		__करो_clear_user(to, n)

#घोषणा clear_user(to, n)					\
(अणु								\
	अचिन्हित दीर्घ __cu_len = (n);				\
	अगर (__access_ok(to, __cu_len))				\
		__cu_len = __करो_clear_user(to, __cu_len);	\
	__cu_len;						\
पूर्ण)


/*
 * Returns: -EFAULT अगर exception beक्रमe terminator, N अगर the entire buffer filled, अन्यथा
 * म_माप.
 */
बाह्य दीर्घ __must_check __म_नकलन_from_user (अक्षर *to, स्थिर अक्षर __user *from, दीर्घ to_len);

#घोषणा म_नकलन_from_user(to, from, n)					\
(अणु									\
	स्थिर अक्षर __user * __sfu_from = (from);			\
	दीर्घ __sfu_ret = -EFAULT;					\
	अगर (__access_ok(__sfu_from, 0))					\
		__sfu_ret = __म_नकलन_from_user((to), __sfu_from, (n));	\
	__sfu_ret;							\
पूर्ण)

/*
 * Returns: 0 अगर exception beक्रमe NUL or reaching the supplied limit
 * (N), a value greater than N अगर the limit would be exceeded, अन्यथा
 * म_माप.
 */
बाह्य अचिन्हित दीर्घ __strnlen_user (स्थिर अक्षर __user *, दीर्घ);

#घोषणा strnlen_user(str, len)					\
(अणु								\
	स्थिर अक्षर __user *__su_str = (str);			\
	अचिन्हित दीर्घ __su_ret = 0;				\
	अगर (__access_ok(__su_str, 0))				\
		__su_ret = __strnlen_user(__su_str, len);	\
	__su_ret;						\
पूर्ण)

#घोषणा ARCH_HAS_TRANSLATE_MEM_PTR	1
अटल __अंतरभूत__ व्योम *
xlate_dev_mem_ptr(phys_addr_t p)
अणु
	काष्ठा page *page;
	व्योम *ptr;

	page = pfn_to_page(p >> PAGE_SHIFT);
	अगर (PageUncached(page))
		ptr = (व्योम *)p + __IA64_UNCACHED_OFFSET;
	अन्यथा
		ptr = __va(p);

	वापस ptr;
पूर्ण

#पूर्ण_अगर /* _ASM_IA64_UACCESS_H */
