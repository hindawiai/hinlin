<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित UACCESS_H
#घोषणा UACCESS_H

#समावेश <linux/compiler.h>

बाह्य व्योम *__user_addr_min, *__user_addr_max;

अटल अंतरभूत व्योम __chk_user_ptr(स्थिर अस्थिर व्योम *p, माप_प्रकार size)
अणु
	निश्चित(p >= __user_addr_min && p + size <= __user_addr_max);
पूर्ण

#घोषणा put_user(x, ptr)					\
(अणु								\
	typeof(ptr) __pu_ptr = (ptr);				\
	__chk_user_ptr(__pu_ptr, माप(*__pu_ptr));		\
	WRITE_ONCE(*(__pu_ptr), x);				\
	0;							\
पूर्ण)

#घोषणा get_user(x, ptr)					\
(अणु								\
	typeof(ptr) __pu_ptr = (ptr);				\
	__chk_user_ptr(__pu_ptr, माप(*__pu_ptr));		\
	x = READ_ONCE(*(__pu_ptr));				\
	0;							\
पूर्ण)

अटल व्योम अस्थिर_स_नकल(अस्थिर अक्षर *to, स्थिर अस्थिर अक्षर *from, 
			    अचिन्हित दीर्घ n)
अणु
	जबतक (n--)
		*(to++) = *(from++);
पूर्ण

अटल अंतरभूत पूर्णांक copy_from_user(व्योम *to, स्थिर व्योम __user अस्थिर *from,
				 अचिन्हित दीर्घ n)
अणु
	__chk_user_ptr(from, n);
	अस्थिर_स_नकल(to, from, n);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक copy_to_user(व्योम __user अस्थिर *to, स्थिर व्योम *from,
			       अचिन्हित दीर्घ n)
अणु
	__chk_user_ptr(to, n);
	अस्थिर_स_नकल(to, from, n);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* UACCESS_H */
