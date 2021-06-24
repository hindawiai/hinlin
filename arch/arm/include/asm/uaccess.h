<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/uaccess.h
 */
#अगर_अघोषित _ASMARM_UACCESS_H
#घोषणा _ASMARM_UACCESS_H

/*
 * User space memory access functions
 */
#समावेश <linux/माला.स>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/करोमुख्य.h>
#समावेश <यंत्र/unअगरied.h>
#समावेश <यंत्र/compiler.h>

#समावेश <यंत्र/extable.h>

/*
 * These two functions allow hooking accesses to userspace to increase
 * प्रणाली पूर्णांकegrity by ensuring that the kernel can not inadvertantly
 * perक्रमm such accesses (eg, via list poison values) which could then
 * be exploited क्रम priviledge escalation.
 */
अटल __always_अंतरभूत अचिन्हित पूर्णांक uaccess_save_and_enable(व्योम)
अणु
#अगर_घोषित CONFIG_CPU_SW_DOMAIN_PAN
	अचिन्हित पूर्णांक old_करोमुख्य = get_करोमुख्य();

	/* Set the current करोमुख्य access to permit user accesses */
	set_करोमुख्य((old_करोमुख्य & ~करोमुख्य_mask(DOMAIN_USER)) |
		   करोमुख्य_val(DOMAIN_USER, DOMAIN_CLIENT));

	वापस old_करोमुख्य;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल __always_अंतरभूत व्योम uaccess_restore(अचिन्हित पूर्णांक flags)
अणु
#अगर_घोषित CONFIG_CPU_SW_DOMAIN_PAN
	/* Restore the user access mask */
	set_करोमुख्य(flags);
#पूर्ण_अगर
पूर्ण

/*
 * These two are पूर्णांकentionally not defined anywhere - अगर the kernel
 * code generates any references to them, that's a bug.
 */
बाह्य पूर्णांक __get_user_bad(व्योम);
बाह्य पूर्णांक __put_user_bad(व्योम);

/*
 * Note that this is actually 0x1,0000,0000
 */
#घोषणा KERNEL_DS	0x00000000

#अगर_घोषित CONFIG_MMU

#घोषणा USER_DS		TASK_SIZE
#घोषणा get_fs()	(current_thपढ़ो_info()->addr_limit)

अटल अंतरभूत व्योम set_fs(mm_segment_t fs)
अणु
	current_thपढ़ो_info()->addr_limit = fs;

	/*
	 * Prevent a mispredicted conditional call to set_fs from क्रमwarding
	 * the wrong address limit to access_ok under speculation.
	 */
	dsb(nsh);
	isb();

	modअगरy_करोमुख्य(DOMAIN_KERNEL, fs ? DOMAIN_CLIENT : DOMAIN_MANAGER);
पूर्ण

#घोषणा uaccess_kernel()	(get_fs() == KERNEL_DS)

/*
 * We use 33-bit arithmetic here.  Success वापसs zero, failure वापसs
 * addr_limit.  We take advantage that addr_limit will be zero क्रम KERNEL_DS,
 * so this will always वापस success in that हाल.
 */
#घोषणा __range_ok(addr, size) (अणु \
	अचिन्हित दीर्घ flag, roksum; \
	__chk_user_ptr(addr);	\
	__यंत्र__(".syntax unified\n" \
		"adds %1, %2, %3; sbcscc %1, %1, %0; movcc %0, #0" \
		: "=&r" (flag), "=&r" (roksum) \
		: "r" (addr), "Ir" (size), "0" (current_thपढ़ो_info()->addr_limit) \
		: "cc"); \
	flag; पूर्ण)

/*
 * This is a type: either अचिन्हित दीर्घ, अगर the argument fits पूर्णांकo
 * that type, or otherwise अचिन्हित दीर्घ दीर्घ.
 */
#घोषणा __पूर्णांकtype(x) \
	__typeof__(__builtin_choose_expr(माप(x) > माप(0UL), 0ULL, 0UL))

/*
 * Sanitise a uaccess poपूर्णांकer such that it becomes शून्य अगर addr+size
 * is above the current addr_limit.
 */
#घोषणा uaccess_mask_range_ptr(ptr, size)			\
	((__typeof__(ptr))__uaccess_mask_range_ptr(ptr, size))
अटल अंतरभूत व्योम __user *__uaccess_mask_range_ptr(स्थिर व्योम __user *ptr,
						    माप_प्रकार size)
अणु
	व्योम __user *safe_ptr = (व्योम __user *)ptr;
	अचिन्हित दीर्घ पंचांगp;

	यंत्र अस्थिर(
	"	.syntax unified\n"
	"	sub	%1, %3, #1\n"
	"	subs	%1, %1, %0\n"
	"	addhs	%1, %1, #1\n"
	"	subshs	%1, %1, %2\n"
	"	movlo	%0, #0\n"
	: "+r" (safe_ptr), "=&r" (पंचांगp)
	: "r" (size), "r" (current_thपढ़ो_info()->addr_limit)
	: "cc");

	csdb();
	वापस safe_ptr;
पूर्ण

/*
 * Single-value transfer routines.  They स्वतःmatically use the right
 * size अगर we just have the right poपूर्णांकer type.  Note that the functions
 * which पढ़ो from user space (*get_*) need to take care not to leak
 * kernel data even अगर the calling code is buggy and fails to check
 * the वापस value.  This means zeroing out the destination variable
 * or buffer on error.  Normally this is करोne out of line by the
 * fixup code, but there are a few places where it पूर्णांकrudes on the
 * मुख्य code path.  When we only ग_लिखो to user space, there is no
 * problem.
 */
बाह्य पूर्णांक __get_user_1(व्योम *);
बाह्य पूर्णांक __get_user_2(व्योम *);
बाह्य पूर्णांक __get_user_4(व्योम *);
बाह्य पूर्णांक __get_user_32t_8(व्योम *);
बाह्य पूर्णांक __get_user_8(व्योम *);
बाह्य पूर्णांक __get_user_64t_1(व्योम *);
बाह्य पूर्णांक __get_user_64t_2(व्योम *);
बाह्य पूर्णांक __get_user_64t_4(व्योम *);

#घोषणा __GUP_CLOBBER_1	"lr", "cc"
#अगर_घोषित CONFIG_CPU_USE_DOMAINS
#घोषणा __GUP_CLOBBER_2	"ip", "lr", "cc"
#अन्यथा
#घोषणा __GUP_CLOBBER_2 "lr", "cc"
#पूर्ण_अगर
#घोषणा __GUP_CLOBBER_4	"lr", "cc"
#घोषणा __GUP_CLOBBER_32t_8 "lr", "cc"
#घोषणा __GUP_CLOBBER_8	"lr", "cc"

#घोषणा __get_user_x(__r2, __p, __e, __l, __s)				\
	   __यंत्र__ __अस्थिर__ (					\
		__यंत्रeq("%0", "r0") __यंत्रeq("%1", "r2")			\
		__यंत्रeq("%3", "r1")					\
		"bl	__get_user_" #__s				\
		: "=&r" (__e), "=r" (__r2)				\
		: "0" (__p), "r" (__l)					\
		: __GUP_CLOBBER_##__s)

/* narrowing a द्विगुन-word get पूर्णांकo a single 32bit word रेजिस्टर: */
#अगर_घोषित __ARMEB__
#घोषणा __get_user_x_32t(__r2, __p, __e, __l, __s)			\
	__get_user_x(__r2, __p, __e, __l, 32t_8)
#अन्यथा
#घोषणा __get_user_x_32t __get_user_x
#पूर्ण_अगर

/*
 * storing result पूर्णांकo proper least signअगरicant word of 64bit target var,
 * dअगरferent only क्रम big endian हाल where 64 bit __r2 lsw is r3:
 */
#अगर_घोषित __ARMEB__
#घोषणा __get_user_x_64t(__r2, __p, __e, __l, __s)		        \
	   __यंत्र__ __अस्थिर__ (					\
		__यंत्रeq("%0", "r0") __यंत्रeq("%1", "r2")			\
		__यंत्रeq("%3", "r1")					\
		"bl	__get_user_64t_" #__s				\
		: "=&r" (__e), "=r" (__r2)				\
		: "0" (__p), "r" (__l)					\
		: __GUP_CLOBBER_##__s)
#अन्यथा
#घोषणा __get_user_x_64t __get_user_x
#पूर्ण_अगर


#घोषणा __get_user_check(x, p)						\
	(अणु								\
		अचिन्हित दीर्घ __limit = current_thपढ़ो_info()->addr_limit - 1; \
		रेजिस्टर typeof(*(p)) __user *__p यंत्र("r0") = (p);	\
		रेजिस्टर __पूर्णांकtype(x) __r2 यंत्र("r2");			\
		रेजिस्टर अचिन्हित दीर्घ __l यंत्र("r1") = __limit;		\
		रेजिस्टर पूर्णांक __e यंत्र("r0");				\
		अचिन्हित पूर्णांक __ua_flags = uaccess_save_and_enable();	\
		चयन (माप(*(__p))) अणु				\
		हाल 1:							\
			अगर (माप((x)) >= 8)				\
				__get_user_x_64t(__r2, __p, __e, __l, 1); \
			अन्यथा						\
				__get_user_x(__r2, __p, __e, __l, 1);	\
			अवरोध;						\
		हाल 2:							\
			अगर (माप((x)) >= 8)				\
				__get_user_x_64t(__r2, __p, __e, __l, 2); \
			अन्यथा						\
				__get_user_x(__r2, __p, __e, __l, 2);	\
			अवरोध;						\
		हाल 4:							\
			अगर (माप((x)) >= 8)				\
				__get_user_x_64t(__r2, __p, __e, __l, 4); \
			अन्यथा						\
				__get_user_x(__r2, __p, __e, __l, 4);	\
			अवरोध;						\
		हाल 8:							\
			अगर (माप((x)) < 8)				\
				__get_user_x_32t(__r2, __p, __e, __l, 4); \
			अन्यथा						\
				__get_user_x(__r2, __p, __e, __l, 8);	\
			अवरोध;						\
		शेष: __e = __get_user_bad(); अवरोध;			\
		पूर्ण							\
		uaccess_restore(__ua_flags);				\
		x = (typeof(*(p))) __r2;				\
		__e;							\
	पूर्ण)

#घोषणा get_user(x, p)							\
	(अणु								\
		might_fault();						\
		__get_user_check(x, p);					\
	 पूर्ण)

बाह्य पूर्णांक __put_user_1(व्योम *, अचिन्हित पूर्णांक);
बाह्य पूर्णांक __put_user_2(व्योम *, अचिन्हित पूर्णांक);
बाह्य पूर्णांक __put_user_4(व्योम *, अचिन्हित पूर्णांक);
बाह्य पूर्णांक __put_user_8(व्योम *, अचिन्हित दीर्घ दीर्घ);

#घोषणा __put_user_check(__pu_val, __ptr, __err, __s)			\
	(अणु								\
		अचिन्हित दीर्घ __limit = current_thपढ़ो_info()->addr_limit - 1; \
		रेजिस्टर typeof(__pu_val) __r2 यंत्र("r2") = __pu_val;	\
		रेजिस्टर स्थिर व्योम __user *__p यंत्र("r0") = __ptr;	\
		रेजिस्टर अचिन्हित दीर्घ __l यंत्र("r1") = __limit;		\
		रेजिस्टर पूर्णांक __e यंत्र("r0");				\
		__यंत्र__ __अस्थिर__ (					\
			__यंत्रeq("%0", "r0") __यंत्रeq("%2", "r2")		\
			__यंत्रeq("%3", "r1")				\
			"bl	__put_user_" #__s			\
			: "=&r" (__e)					\
			: "0" (__p), "r" (__r2), "r" (__l)		\
			: "ip", "lr", "cc");				\
		__err = __e;						\
	पूर्ण)

#अन्यथा /* CONFIG_MMU */

/*
 * uClinux has only one addr space, so has simplअगरied address limits.
 */
#घोषणा USER_DS			KERNEL_DS

#घोषणा uaccess_kernel()	(true)
#घोषणा __addr_ok(addr)		((व्योम)(addr), 1)
#घोषणा __range_ok(addr, size)	((व्योम)(addr), 0)
#घोषणा get_fs()		(KERNEL_DS)

अटल अंतरभूत व्योम set_fs(mm_segment_t fs)
अणु
पूर्ण

#घोषणा get_user(x, p)	__get_user(x, p)
#घोषणा __put_user_check __put_user_nocheck

#पूर्ण_अगर /* CONFIG_MMU */

#घोषणा access_ok(addr, size)	(__range_ok(addr, size) == 0)

#घोषणा user_addr_max() \
	(uaccess_kernel() ? ~0UL : get_fs())

#अगर_घोषित CONFIG_CPU_SPECTRE
/*
 * When mitigating Spectre variant 1, it is not worth fixing the non-
 * verअगरying accessors, because we need to add verअगरication of the
 * address space there.  Force these to use the standard get_user()
 * version instead.
 */
#घोषणा __get_user(x, ptr) get_user(x, ptr)
#अन्यथा

/*
 * The "__xxx" versions of the user access functions करो not verअगरy the
 * address space - it must have been करोne previously with a separate
 * "access_ok()" call.
 *
 * The "xxx_error" versions set the third argument to EFAULT अगर an
 * error occurs, and leave it unchanged on success.  Note that these
 * versions are व्योम (ie, करोn't वापस a value as such).
 */
#घोषणा __get_user(x, ptr)						\
(अणु									\
	दीर्घ __gu_err = 0;						\
	__get_user_err((x), (ptr), __gu_err);				\
	__gu_err;							\
पूर्ण)

#घोषणा __get_user_err(x, ptr, err)					\
करो अणु									\
	अचिन्हित दीर्घ __gu_addr = (अचिन्हित दीर्घ)(ptr);			\
	अचिन्हित दीर्घ __gu_val;						\
	अचिन्हित पूर्णांक __ua_flags;					\
	__chk_user_ptr(ptr);						\
	might_fault();							\
	__ua_flags = uaccess_save_and_enable();				\
	चयन (माप(*(ptr))) अणु					\
	हाल 1:	__get_user_यंत्र_byte(__gu_val, __gu_addr, err);	अवरोध;	\
	हाल 2:	__get_user_यंत्र_half(__gu_val, __gu_addr, err);	अवरोध;	\
	हाल 4:	__get_user_यंत्र_word(__gu_val, __gu_addr, err);	अवरोध;	\
	शेष: (__gu_val) = __get_user_bad();				\
	पूर्ण								\
	uaccess_restore(__ua_flags);					\
	(x) = (__typeof__(*(ptr)))__gu_val;				\
पूर्ण जबतक (0)

#घोषणा __get_user_यंत्र(x, addr, err, instr)			\
	__यंत्र__ __अस्थिर__(					\
	"1:	" TUSER(instr) " %1, [%2], #0\n"		\
	"2:\n"							\
	"	.pushsection .text.fixup,\"ax\"\n"		\
	"	.align	2\n"					\
	"3:	mov	%0, %3\n"				\
	"	mov	%1, #0\n"				\
	"	b	2b\n"					\
	"	.popsection\n"					\
	"	.pushsection __ex_table,\"a\"\n"		\
	"	.align	3\n"					\
	"	.long	1b, 3b\n"				\
	"	.popsection"					\
	: "+r" (err), "=&r" (x)					\
	: "r" (addr), "i" (-EFAULT)				\
	: "cc")

#घोषणा __get_user_यंत्र_byte(x, addr, err)			\
	__get_user_यंत्र(x, addr, err, ldrb)

#अगर __LINUX_ARM_ARCH__ >= 6

#घोषणा __get_user_यंत्र_half(x, addr, err)			\
	__get_user_यंत्र(x, addr, err, ldrh)

#अन्यथा

#अगर_अघोषित __ARMEB__
#घोषणा __get_user_यंत्र_half(x, __gu_addr, err)			\
(अणु								\
	अचिन्हित दीर्घ __b1, __b2;				\
	__get_user_यंत्र_byte(__b1, __gu_addr, err);		\
	__get_user_यंत्र_byte(__b2, __gu_addr + 1, err);		\
	(x) = __b1 | (__b2 << 8);				\
पूर्ण)
#अन्यथा
#घोषणा __get_user_यंत्र_half(x, __gu_addr, err)			\
(अणु								\
	अचिन्हित दीर्घ __b1, __b2;				\
	__get_user_यंत्र_byte(__b1, __gu_addr, err);		\
	__get_user_यंत्र_byte(__b2, __gu_addr + 1, err);		\
	(x) = (__b1 << 8) | __b2;				\
पूर्ण)
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_ARM_ARCH__ >= 6 */

#घोषणा __get_user_यंत्र_word(x, addr, err)			\
	__get_user_यंत्र(x, addr, err, ldr)
#पूर्ण_अगर


#घोषणा __put_user_चयन(x, ptr, __err, __fn)				\
	करो अणु								\
		स्थिर __typeof__(*(ptr)) __user *__pu_ptr = (ptr);	\
		__typeof__(*(ptr)) __pu_val = (x);			\
		अचिन्हित पूर्णांक __ua_flags;				\
		might_fault();						\
		__ua_flags = uaccess_save_and_enable();			\
		चयन (माप(*(ptr))) अणु				\
		हाल 1: __fn(__pu_val, __pu_ptr, __err, 1); अवरोध;	\
		हाल 2:	__fn(__pu_val, __pu_ptr, __err, 2); अवरोध;	\
		हाल 4:	__fn(__pu_val, __pu_ptr, __err, 4); अवरोध;	\
		हाल 8:	__fn(__pu_val, __pu_ptr, __err, 8); अवरोध;	\
		शेष: __err = __put_user_bad(); अवरोध;		\
		पूर्ण							\
		uaccess_restore(__ua_flags);				\
	पूर्ण जबतक (0)

#घोषणा put_user(x, ptr)						\
(अणु									\
	पूर्णांक __pu_err = 0;						\
	__put_user_चयन((x), (ptr), __pu_err, __put_user_check);	\
	__pu_err;							\
पूर्ण)

#अगर_घोषित CONFIG_CPU_SPECTRE
/*
 * When mitigating Spectre variant 1.1, all accessors need to include
 * verअगरication of the address space.
 */
#घोषणा __put_user(x, ptr) put_user(x, ptr)

#अन्यथा
#घोषणा __put_user(x, ptr)						\
(अणु									\
	दीर्घ __pu_err = 0;						\
	__put_user_चयन((x), (ptr), __pu_err, __put_user_nocheck);	\
	__pu_err;							\
पूर्ण)

#घोषणा __put_user_nocheck(x, __pu_ptr, __err, __size)			\
	करो अणु								\
		अचिन्हित दीर्घ __pu_addr = (अचिन्हित दीर्घ)__pu_ptr;	\
		__put_user_nocheck_##__size(x, __pu_addr, __err);	\
	पूर्ण जबतक (0)

#घोषणा __put_user_nocheck_1 __put_user_यंत्र_byte
#घोषणा __put_user_nocheck_2 __put_user_यंत्र_half
#घोषणा __put_user_nocheck_4 __put_user_यंत्र_word
#घोषणा __put_user_nocheck_8 __put_user_यंत्र_dword

#घोषणा __put_user_यंत्र(x, __pu_addr, err, instr)		\
	__यंत्र__ __अस्थिर__(					\
	"1:	" TUSER(instr) " %1, [%2], #0\n"		\
	"2:\n"							\
	"	.pushsection .text.fixup,\"ax\"\n"		\
	"	.align	2\n"					\
	"3:	mov	%0, %3\n"				\
	"	b	2b\n"					\
	"	.popsection\n"					\
	"	.pushsection __ex_table,\"a\"\n"		\
	"	.align	3\n"					\
	"	.long	1b, 3b\n"				\
	"	.popsection"					\
	: "+r" (err)						\
	: "r" (x), "r" (__pu_addr), "i" (-EFAULT)		\
	: "cc")

#घोषणा __put_user_यंत्र_byte(x, __pu_addr, err)			\
	__put_user_यंत्र(x, __pu_addr, err, strb)

#अगर __LINUX_ARM_ARCH__ >= 6

#घोषणा __put_user_यंत्र_half(x, __pu_addr, err)			\
	__put_user_यंत्र(x, __pu_addr, err, strh)

#अन्यथा

#अगर_अघोषित __ARMEB__
#घोषणा __put_user_यंत्र_half(x, __pu_addr, err)			\
(अणु								\
	अचिन्हित दीर्घ __temp = (__क्रमce अचिन्हित दीर्घ)(x);	\
	__put_user_यंत्र_byte(__temp, __pu_addr, err);		\
	__put_user_यंत्र_byte(__temp >> 8, __pu_addr + 1, err);	\
पूर्ण)
#अन्यथा
#घोषणा __put_user_यंत्र_half(x, __pu_addr, err)			\
(अणु								\
	अचिन्हित दीर्घ __temp = (__क्रमce अचिन्हित दीर्घ)(x);	\
	__put_user_यंत्र_byte(__temp >> 8, __pu_addr, err);	\
	__put_user_यंत्र_byte(__temp, __pu_addr + 1, err);	\
पूर्ण)
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_ARM_ARCH__ >= 6 */

#घोषणा __put_user_यंत्र_word(x, __pu_addr, err)			\
	__put_user_यंत्र(x, __pu_addr, err, str)

#अगर_अघोषित __ARMEB__
#घोषणा	__reg_oper0	"%R2"
#घोषणा	__reg_oper1	"%Q2"
#अन्यथा
#घोषणा	__reg_oper0	"%Q2"
#घोषणा	__reg_oper1	"%R2"
#पूर्ण_अगर

#घोषणा __put_user_यंत्र_dword(x, __pu_addr, err)			\
	__यंत्र__ __अस्थिर__(					\
 ARM(	"1:	" TUSER(str) "	" __reg_oper1 ", [%1], #4\n"	) \
 ARM(	"2:	" TUSER(str) "	" __reg_oper0 ", [%1]\n"	) \
 THUMB(	"1:	" TUSER(str) "	" __reg_oper1 ", [%1]\n"	) \
 THUMB(	"2:	" TUSER(str) "	" __reg_oper0 ", [%1, #4]\n"	) \
	"3:\n"							\
	"	.pushsection .text.fixup,\"ax\"\n"		\
	"	.align	2\n"					\
	"4:	mov	%0, %3\n"				\
	"	b	3b\n"					\
	"	.popsection\n"					\
	"	.pushsection __ex_table,\"a\"\n"		\
	"	.align	3\n"					\
	"	.long	1b, 4b\n"				\
	"	.long	2b, 4b\n"				\
	"	.popsection"					\
	: "+r" (err), "+r" (__pu_addr)				\
	: "r" (x), "i" (-EFAULT)				\
	: "cc")

#पूर्ण_अगर /* !CONFIG_CPU_SPECTRE */

#अगर_घोषित CONFIG_MMU
बाह्य अचिन्हित दीर्घ __must_check
arm_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n);

अटल अंतरभूत अचिन्हित दीर्घ __must_check
raw_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	अचिन्हित पूर्णांक __ua_flags;

	__ua_flags = uaccess_save_and_enable();
	n = arm_copy_from_user(to, from, n);
	uaccess_restore(__ua_flags);
	वापस n;
पूर्ण

बाह्य अचिन्हित दीर्घ __must_check
arm_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n);
बाह्य अचिन्हित दीर्घ __must_check
__copy_to_user_std(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n);

अटल अंतरभूत अचिन्हित दीर्घ __must_check
raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
#अगर_अघोषित CONFIG_UACCESS_WITH_MEMCPY
	अचिन्हित पूर्णांक __ua_flags;
	__ua_flags = uaccess_save_and_enable();
	n = arm_copy_to_user(to, from, n);
	uaccess_restore(__ua_flags);
	वापस n;
#अन्यथा
	वापस arm_copy_to_user(to, from, n);
#पूर्ण_अगर
पूर्ण

बाह्य अचिन्हित दीर्घ __must_check
arm_clear_user(व्योम __user *addr, अचिन्हित दीर्घ n);
बाह्य अचिन्हित दीर्घ __must_check
__clear_user_std(व्योम __user *addr, अचिन्हित दीर्घ n);

अटल अंतरभूत अचिन्हित दीर्घ __must_check
__clear_user(व्योम __user *addr, अचिन्हित दीर्घ n)
अणु
	अचिन्हित पूर्णांक __ua_flags = uaccess_save_and_enable();
	n = arm_clear_user(addr, n);
	uaccess_restore(__ua_flags);
	वापस n;
पूर्ण

#अन्यथा
अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	स_नकल(to, (स्थिर व्योम __क्रमce *)from, n);
	वापस 0;
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	स_नकल((व्योम __क्रमce *)to, from, n);
	वापस 0;
पूर्ण
#घोषणा __clear_user(addr, n)		(स_रखो((व्योम __क्रमce *)addr, 0, n), 0)
#पूर्ण_अगर
#घोषणा INLINE_COPY_TO_USER
#घोषणा INLINE_COPY_FROM_USER

अटल अंतरभूत अचिन्हित दीर्घ __must_check clear_user(व्योम __user *to, अचिन्हित दीर्घ n)
अणु
	अगर (access_ok(to, n))
		n = __clear_user(to, n);
	वापस n;
पूर्ण

/* These are from lib/ code, and use __get_user() and मित्रs */
बाह्य दीर्घ म_नकलन_from_user(अक्षर *dest, स्थिर अक्षर __user *src, दीर्घ count);

बाह्य __must_check दीर्घ strnlen_user(स्थिर अक्षर __user *str, दीर्घ n);

#पूर्ण_अगर /* _ASMARM_UACCESS_H */
