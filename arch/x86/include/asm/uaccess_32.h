<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_UACCESS_32_H
#घोषणा _ASM_X86_UACCESS_32_H

/*
 * User space memory access functions
 */
#समावेश <linux/माला.स>
#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/page.h>

अचिन्हित दीर्घ __must_check __copy_user_ll
		(व्योम *to, स्थिर व्योम *from, अचिन्हित दीर्घ n);
अचिन्हित दीर्घ __must_check __copy_from_user_ll_nocache_nozero
		(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n);

अटल __always_अंतरभूत अचिन्हित दीर्घ __must_check
raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	वापस __copy_user_ll((__क्रमce व्योम *)to, from, n);
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ
raw_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	वापस __copy_user_ll(to, (__क्रमce स्थिर व्योम *)from, n);
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ
__copy_from_user_inatomic_nocache(व्योम *to, स्थिर व्योम __user *from,
				  अचिन्हित दीर्घ n)
अणु
       वापस __copy_from_user_ll_nocache_nozero(to, from, n);
पूर्ण

#पूर्ण_अगर /* _ASM_X86_UACCESS_32_H */
