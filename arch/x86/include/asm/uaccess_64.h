<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_UACCESS_64_H
#घोषणा _ASM_X86_UACCESS_64_H

/*
 * User space memory access functions
 */
#समावेश <linux/compiler.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/kasan-checks.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/cpufeatures.h>
#समावेश <यंत्र/page.h>

/*
 * Copy To/From Userspace
 */

/* Handles exceptions in both to and from, but करोesn't करो access_ok */
__must_check अचिन्हित दीर्घ
copy_user_enhanced_fast_string(व्योम *to, स्थिर व्योम *from, अचिन्हित len);
__must_check अचिन्हित दीर्घ
copy_user_generic_string(व्योम *to, स्थिर व्योम *from, अचिन्हित len);
__must_check अचिन्हित दीर्घ
copy_user_generic_unrolled(व्योम *to, स्थिर व्योम *from, अचिन्हित len);

अटल __always_अंतरभूत __must_check अचिन्हित दीर्घ
copy_user_generic(व्योम *to, स्थिर व्योम *from, अचिन्हित len)
अणु
	अचिन्हित ret;

	/*
	 * If CPU has ERMS feature, use copy_user_enhanced_fast_string.
	 * Otherwise, अगर CPU has rep_good feature, use copy_user_generic_string.
	 * Otherwise, use copy_user_generic_unrolled.
	 */
	alternative_call_2(copy_user_generic_unrolled,
			 copy_user_generic_string,
			 X86_FEATURE_REP_GOOD,
			 copy_user_enhanced_fast_string,
			 X86_FEATURE_ERMS,
			 ASM_OUTPUT2("=a" (ret), "=D" (to), "=S" (from),
				     "=d" (len)),
			 "1" (to), "2" (from), "3" (len)
			 : "memory", "rcx", "r8", "r9", "r10", "r11");
	वापस ret;
पूर्ण

अटल __always_अंतरभूत __must_check अचिन्हित दीर्घ
raw_copy_from_user(व्योम *dst, स्थिर व्योम __user *src, अचिन्हित दीर्घ size)
अणु
	वापस copy_user_generic(dst, (__क्रमce व्योम *)src, size);
पूर्ण

अटल __always_अंतरभूत __must_check अचिन्हित दीर्घ
raw_copy_to_user(व्योम __user *dst, स्थिर व्योम *src, अचिन्हित दीर्घ size)
अणु
	वापस copy_user_generic((__क्रमce व्योम *)dst, src, size);
पूर्ण

अटल __always_अंतरभूत __must_check
अचिन्हित दीर्घ raw_copy_in_user(व्योम __user *dst, स्थिर व्योम __user *src, अचिन्हित दीर्घ size)
अणु
	वापस copy_user_generic((__क्रमce व्योम *)dst,
				 (__क्रमce व्योम *)src, size);
पूर्ण

बाह्य दीर्घ __copy_user_nocache(व्योम *dst, स्थिर व्योम __user *src,
				अचिन्हित size, पूर्णांक zerorest);

बाह्य दीर्घ __copy_user_flushcache(व्योम *dst, स्थिर व्योम __user *src, अचिन्हित size);
बाह्य व्योम स_नकल_page_flushcache(अक्षर *to, काष्ठा page *page, माप_प्रकार offset,
			   माप_प्रकार len);

अटल अंतरभूत पूर्णांक
__copy_from_user_inatomic_nocache(व्योम *dst, स्थिर व्योम __user *src,
				  अचिन्हित size)
अणु
	kasan_check_ग_लिखो(dst, size);
	वापस __copy_user_nocache(dst, src, size, 0);
पूर्ण

अटल अंतरभूत पूर्णांक
__copy_from_user_flushcache(व्योम *dst, स्थिर व्योम __user *src, अचिन्हित size)
अणु
	kasan_check_ग_लिखो(dst, size);
	वापस __copy_user_flushcache(dst, src, size);
पूर्ण
#पूर्ण_अगर /* _ASM_X86_UACCESS_64_H */
