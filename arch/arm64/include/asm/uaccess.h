<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/uaccess.h
 *
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_UACCESS_H
#घोषणा __ASM_UACCESS_H

#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/kernel-pgtable.h>
#समावेश <यंत्र/sysreg.h>

/*
 * User space memory access functions
 */
#समावेश <linux/bitops.h>
#समावेश <linux/kasan-checks.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/mte.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/extable.h>

#घोषणा HAVE_GET_KERNEL_NOFAULT

/*
 * Test whether a block of memory is a valid user space address.
 * Returns 1 अगर the range is valid, 0 otherwise.
 *
 * This is equivalent to the following test:
 * (u65)addr + (u65)size <= (u65)TASK_SIZE_MAX
 */
अटल अंतरभूत अचिन्हित दीर्घ __range_ok(स्थिर व्योम __user *addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ ret, limit = TASK_SIZE_MAX - 1;

	/*
	 * Asynchronous I/O running in a kernel thपढ़ो करोes not have the
	 * TIF_TAGGED_ADDR flag of the process owning the mm, so always untag
	 * the user address beक्रमe checking.
	 */
	अगर (IS_ENABLED(CONFIG_ARM64_TAGGED_ADDR_ABI) &&
	    (current->flags & PF_KTHREAD || test_thपढ़ो_flag(TIF_TAGGED_ADDR)))
		addr = untagged_addr(addr);

	__chk_user_ptr(addr);
	यंत्र अस्थिर(
	// A + B <= C + 1 क्रम all A,B,C, in four easy steps:
	// 1: X = A + B; X' = X % 2^64
	"	adds	%0, %3, %2\n"
	// 2: Set C = 0 अगर X > 2^64, to guarantee X' > C in step 4
	"	csel	%1, xzr, %1, hi\n"
	// 3: Set X' = ~0 if X >= 2^64. For X == 2^64, this decrements X'
	//    to compensate क्रम the carry flag being set in step 4. For
	//    X > 2^64, X' merely has to reमुख्य nonzero, which it करोes.
	"	csinv	%0, %0, xzr, cc\n"
	// 4: For X < 2^64, this gives us X' - C - 1 <= 0, where the -1
	//    comes from the carry in being clear. Otherwise, we are
	//    testing X' - C == 0, subject to the previous adjusपंचांगents.
	"	sbcs	xzr, %0, %1\n"
	"	cset	%0, ls\n"
	: "=&r" (ret), "+r" (limit) : "Ir" (size), "0" (addr) : "cc");

	वापस ret;
पूर्ण

#घोषणा access_ok(addr, size)	__range_ok(addr, size)

#घोषणा _ASM_EXTABLE(from, to)						\
	"	.pushsection	__ex_table, \"a\"\n"			\
	"	.align		3\n"					\
	"	.long		(" #from " - .), (" #to " - .)\n"	\
	"	.popsection\n"

/*
 * User access enabling/disabling.
 */
#अगर_घोषित CONFIG_ARM64_SW_TTBR0_PAN
अटल अंतरभूत व्योम __uaccess_ttbr0_disable(व्योम)
अणु
	अचिन्हित दीर्घ flags, ttbr;

	local_irq_save(flags);
	ttbr = पढ़ो_sysreg(ttbr1_el1);
	ttbr &= ~TTBR_ASID_MASK;
	/* reserved_pg_dir placed beक्रमe swapper_pg_dir */
	ग_लिखो_sysreg(ttbr - RESERVED_SWAPPER_OFFSET, ttbr0_el1);
	isb();
	/* Set reserved ASID */
	ग_लिखो_sysreg(ttbr, ttbr1_el1);
	isb();
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत व्योम __uaccess_ttbr0_enable(व्योम)
अणु
	अचिन्हित दीर्घ flags, ttbr0, ttbr1;

	/*
	 * Disable पूर्णांकerrupts to aव्योम preemption between पढ़ोing the 'ttbr0'
	 * variable and the MSR. A context चयन could trigger an ASID
	 * roll-over and an update of 'ttbr0'.
	 */
	local_irq_save(flags);
	ttbr0 = READ_ONCE(current_thपढ़ो_info()->ttbr0);

	/* Restore active ASID */
	ttbr1 = पढ़ो_sysreg(ttbr1_el1);
	ttbr1 &= ~TTBR_ASID_MASK;		/* safety measure */
	ttbr1 |= ttbr0 & TTBR_ASID_MASK;
	ग_लिखो_sysreg(ttbr1, ttbr1_el1);
	isb();

	/* Restore user page table */
	ग_लिखो_sysreg(ttbr0, ttbr0_el1);
	isb();
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत bool uaccess_ttbr0_disable(व्योम)
अणु
	अगर (!प्रणाली_uses_ttbr0_pan())
		वापस false;
	__uaccess_ttbr0_disable();
	वापस true;
पूर्ण

अटल अंतरभूत bool uaccess_ttbr0_enable(व्योम)
अणु
	अगर (!प्रणाली_uses_ttbr0_pan())
		वापस false;
	__uaccess_ttbr0_enable();
	वापस true;
पूर्ण
#अन्यथा
अटल अंतरभूत bool uaccess_ttbr0_disable(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool uaccess_ttbr0_enable(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम __uaccess_disable_hw_pan(व्योम)
अणु
	यंत्र(ALTERNATIVE("nop", SET_PSTATE_PAN(0), ARM64_HAS_PAN,
			CONFIG_ARM64_PAN));
पूर्ण

अटल अंतरभूत व्योम __uaccess_enable_hw_pan(व्योम)
अणु
	यंत्र(ALTERNATIVE("nop", SET_PSTATE_PAN(1), ARM64_HAS_PAN,
			CONFIG_ARM64_PAN));
पूर्ण

/*
 * The Tag Check Flag (TCF) mode क्रम MTE is per EL, hence TCF0
 * affects EL0 and TCF affects EL1 irrespective of which TTBR is
 * used.
 * The kernel accesses TTBR0 usually with LDTR/STTR inकाष्ठाions
 * when UAO is available, so these would act as EL0 accesses using
 * TCF0.
 * However futex.h code uses exclusives which would be executed as
 * EL1, this can potentially cause a tag check fault even अगर the
 * user disables TCF0.
 *
 * To address the problem we set the PSTATE.TCO bit in uaccess_enable()
 * and reset it in uaccess_disable().
 *
 * The Tag check override (TCO) bit disables temporarily the tag checking
 * preventing the issue.
 */
अटल अंतरभूत व्योम __uaccess_disable_tco(व्योम)
अणु
	यंत्र अस्थिर(ALTERNATIVE("nop", SET_PSTATE_TCO(0),
				 ARM64_MTE, CONFIG_KASAN_HW_TAGS));
पूर्ण

अटल अंतरभूत व्योम __uaccess_enable_tco(व्योम)
अणु
	यंत्र अस्थिर(ALTERNATIVE("nop", SET_PSTATE_TCO(1),
				 ARM64_MTE, CONFIG_KASAN_HW_TAGS));
पूर्ण

/*
 * These functions disable tag checking only अगर in MTE async mode
 * since the sync mode generates exceptions synchronously and the
 * nofault or load_unaligned_zeropad can handle them.
 */
अटल अंतरभूत व्योम __uaccess_disable_tco_async(व्योम)
अणु
	अगर (प्रणाली_uses_mte_async_mode())
		 __uaccess_disable_tco();
पूर्ण

अटल अंतरभूत व्योम __uaccess_enable_tco_async(व्योम)
अणु
	अगर (प्रणाली_uses_mte_async_mode())
		__uaccess_enable_tco();
पूर्ण

अटल अंतरभूत व्योम uaccess_disable_privileged(व्योम)
अणु
	__uaccess_disable_tco();

	अगर (uaccess_ttbr0_disable())
		वापस;

	__uaccess_enable_hw_pan();
पूर्ण

अटल अंतरभूत व्योम uaccess_enable_privileged(व्योम)
अणु
	__uaccess_enable_tco();

	अगर (uaccess_ttbr0_enable())
		वापस;

	__uaccess_disable_hw_pan();
पूर्ण

/*
 * Sanitise a uaccess poपूर्णांकer such that it becomes शून्य अगर above the maximum
 * user address. In हाल the poपूर्णांकer is tagged (has the top byte set), untag
 * the poपूर्णांकer beक्रमe checking.
 */
#घोषणा uaccess_mask_ptr(ptr) (__typeof__(ptr))__uaccess_mask_ptr(ptr)
अटल अंतरभूत व्योम __user *__uaccess_mask_ptr(स्थिर व्योम __user *ptr)
अणु
	व्योम __user *safe_ptr;

	यंत्र अस्थिर(
	"	bics	xzr, %3, %2\n"
	"	csel	%0, %1, xzr, eq\n"
	: "=&r" (safe_ptr)
	: "r" (ptr), "r" (TASK_SIZE_MAX - 1),
	  "r" (untagged_addr(ptr))
	: "cc");

	csdb();
	वापस safe_ptr;
पूर्ण

/*
 * The "__xxx" versions of the user access functions करो not verअगरy the address
 * space - it must have been करोne previously with a separate "access_ok()"
 * call.
 *
 * The "__xxx_error" versions set the third argument to -EFAULT अगर an error
 * occurs, and leave it unchanged on success.
 */
#घोषणा __get_mem_यंत्र(load, reg, x, addr, err)				\
	यंत्र अस्थिर(							\
	"1:	" load "	" reg "1, [%2]\n"			\
	"2:\n"								\
	"	.section .fixup, \"ax\"\n"				\
	"	.align	2\n"						\
	"3:	mov	%w0, %3\n"					\
	"	mov	%1, #0\n"					\
	"	b	2b\n"						\
	"	.previous\n"						\
	_ASM_EXTABLE(1b, 3b)						\
	: "+r" (err), "=&r" (x)						\
	: "r" (addr), "i" (-EFAULT))

#घोषणा __raw_get_mem(ldr, x, ptr, err)					\
करो अणु									\
	अचिन्हित दीर्घ __gu_val;						\
	चयन (माप(*(ptr))) अणु					\
	हाल 1:								\
		__get_mem_यंत्र(ldr "b", "%w", __gu_val, (ptr), (err));	\
		अवरोध;							\
	हाल 2:								\
		__get_mem_यंत्र(ldr "h", "%w", __gu_val, (ptr), (err));	\
		अवरोध;							\
	हाल 4:								\
		__get_mem_यंत्र(ldr, "%w", __gu_val, (ptr), (err));	\
		अवरोध;							\
	हाल 8:								\
		__get_mem_यंत्र(ldr, "%x",  __gu_val, (ptr), (err));	\
		अवरोध;							\
	शेष:							\
		BUILD_BUG();						\
	पूर्ण								\
	(x) = (__क्रमce __typeof__(*(ptr)))__gu_val;			\
पूर्ण जबतक (0)

#घोषणा __raw_get_user(x, ptr, err)					\
करो अणु									\
	__chk_user_ptr(ptr);						\
	uaccess_ttbr0_enable();						\
	__raw_get_mem("ldtr", x, ptr, err);				\
	uaccess_ttbr0_disable();					\
पूर्ण जबतक (0)

#घोषणा __get_user_error(x, ptr, err)					\
करो अणु									\
	__typeof__(*(ptr)) __user *__p = (ptr);				\
	might_fault();							\
	अगर (access_ok(__p, माप(*__p))) अणु				\
		__p = uaccess_mask_ptr(__p);				\
		__raw_get_user((x), __p, (err));			\
	पूर्ण अन्यथा अणु							\
		(x) = (__क्रमce __typeof__(x))0; (err) = -EFAULT;	\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा __get_user(x, ptr)						\
(अणु									\
	पूर्णांक __gu_err = 0;						\
	__get_user_error((x), (ptr), __gu_err);				\
	__gu_err;							\
पूर्ण)

#घोषणा get_user	__get_user

#घोषणा __get_kernel_nofault(dst, src, type, err_label)			\
करो अणु									\
	पूर्णांक __gkn_err = 0;						\
									\
	__uaccess_enable_tco_async();					\
	__raw_get_mem("ldr", *((type *)(dst)),				\
		      (__क्रमce type *)(src), __gkn_err);		\
	__uaccess_disable_tco_async();					\
	अगर (unlikely(__gkn_err))					\
		जाओ err_label;						\
पूर्ण जबतक (0)

#घोषणा __put_mem_यंत्र(store, reg, x, addr, err)				\
	यंत्र अस्थिर(							\
	"1:	" store "	" reg "1, [%2]\n"			\
	"2:\n"								\
	"	.section .fixup,\"ax\"\n"				\
	"	.align	2\n"						\
	"3:	mov	%w0, %3\n"					\
	"	b	2b\n"						\
	"	.previous\n"						\
	_ASM_EXTABLE(1b, 3b)						\
	: "+r" (err)							\
	: "r" (x), "r" (addr), "i" (-EFAULT))

#घोषणा __raw_put_mem(str, x, ptr, err)					\
करो अणु									\
	__typeof__(*(ptr)) __pu_val = (x);				\
	चयन (माप(*(ptr))) अणु					\
	हाल 1:								\
		__put_mem_यंत्र(str "b", "%w", __pu_val, (ptr), (err));	\
		अवरोध;							\
	हाल 2:								\
		__put_mem_यंत्र(str "h", "%w", __pu_val, (ptr), (err));	\
		अवरोध;							\
	हाल 4:								\
		__put_mem_यंत्र(str, "%w", __pu_val, (ptr), (err));	\
		अवरोध;							\
	हाल 8:								\
		__put_mem_यंत्र(str, "%x", __pu_val, (ptr), (err));	\
		अवरोध;							\
	शेष:							\
		BUILD_BUG();						\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा __raw_put_user(x, ptr, err)					\
करो अणु									\
	__chk_user_ptr(ptr);						\
	uaccess_ttbr0_enable();						\
	__raw_put_mem("sttr", x, ptr, err);				\
	uaccess_ttbr0_disable();					\
पूर्ण जबतक (0)

#घोषणा __put_user_error(x, ptr, err)					\
करो अणु									\
	__typeof__(*(ptr)) __user *__p = (ptr);				\
	might_fault();							\
	अगर (access_ok(__p, माप(*__p))) अणु				\
		__p = uaccess_mask_ptr(__p);				\
		__raw_put_user((x), __p, (err));			\
	पूर्ण अन्यथा	अणु							\
		(err) = -EFAULT;					\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा __put_user(x, ptr)						\
(अणु									\
	पूर्णांक __pu_err = 0;						\
	__put_user_error((x), (ptr), __pu_err);				\
	__pu_err;							\
पूर्ण)

#घोषणा put_user	__put_user

#घोषणा __put_kernel_nofault(dst, src, type, err_label)			\
करो अणु									\
	पूर्णांक __pkn_err = 0;						\
									\
	__uaccess_enable_tco_async();					\
	__raw_put_mem("str", *((type *)(src)),				\
		      (__क्रमce type *)(dst), __pkn_err);		\
	__uaccess_disable_tco_async();					\
	अगर (unlikely(__pkn_err))					\
		जाओ err_label;						\
पूर्ण जबतक(0)

बाह्य अचिन्हित दीर्घ __must_check __arch_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n);
#घोषणा raw_copy_from_user(to, from, n)					\
(अणु									\
	अचिन्हित दीर्घ __acfu_ret;					\
	uaccess_ttbr0_enable();						\
	__acfu_ret = __arch_copy_from_user((to),			\
				      __uaccess_mask_ptr(from), (n));	\
	uaccess_ttbr0_disable();					\
	__acfu_ret;							\
पूर्ण)

बाह्य अचिन्हित दीर्घ __must_check __arch_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n);
#घोषणा raw_copy_to_user(to, from, n)					\
(अणु									\
	अचिन्हित दीर्घ __actu_ret;					\
	uaccess_ttbr0_enable();						\
	__actu_ret = __arch_copy_to_user(__uaccess_mask_ptr(to),	\
				    (from), (n));			\
	uaccess_ttbr0_disable();					\
	__actu_ret;							\
पूर्ण)

बाह्य अचिन्हित दीर्घ __must_check __arch_copy_in_user(व्योम __user *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n);
#घोषणा raw_copy_in_user(to, from, n)					\
(अणु									\
	अचिन्हित दीर्घ __aciu_ret;					\
	uaccess_ttbr0_enable();						\
	__aciu_ret = __arch_copy_in_user(__uaccess_mask_ptr(to),	\
				    __uaccess_mask_ptr(from), (n));	\
	uaccess_ttbr0_disable();					\
	__aciu_ret;							\
पूर्ण)

#घोषणा INLINE_COPY_TO_USER
#घोषणा INLINE_COPY_FROM_USER

बाह्य अचिन्हित दीर्घ __must_check __arch_clear_user(व्योम __user *to, अचिन्हित दीर्घ n);
अटल अंतरभूत अचिन्हित दीर्घ __must_check __clear_user(व्योम __user *to, अचिन्हित दीर्घ n)
अणु
	अगर (access_ok(to, n)) अणु
		uaccess_ttbr0_enable();
		n = __arch_clear_user(__uaccess_mask_ptr(to), n);
		uaccess_ttbr0_disable();
	पूर्ण
	वापस n;
पूर्ण
#घोषणा clear_user	__clear_user

बाह्य दीर्घ म_नकलन_from_user(अक्षर *dest, स्थिर अक्षर __user *src, दीर्घ count);

बाह्य __must_check दीर्घ strnlen_user(स्थिर अक्षर __user *str, दीर्घ n);

#अगर_घोषित CONFIG_ARCH_HAS_UACCESS_FLUSHCACHE
काष्ठा page;
व्योम स_नकल_page_flushcache(अक्षर *to, काष्ठा page *page, माप_प्रकार offset, माप_प्रकार len);
बाह्य अचिन्हित दीर्घ __must_check __copy_user_flushcache(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n);

अटल अंतरभूत पूर्णांक __copy_from_user_flushcache(व्योम *dst, स्थिर व्योम __user *src, अचिन्हित size)
अणु
	kasan_check_ग_लिखो(dst, size);
	वापस __copy_user_flushcache(dst, __uaccess_mask_ptr(src), size);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_UACCESS_H */
