<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* 
 * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)
 * Copyright (C) 2015 Riअक्षरd Weinberger (riअक्षरd@nod.at)
 */

#अगर_अघोषित __UM_UACCESS_H
#घोषणा __UM_UACCESS_H

#समावेश <यंत्र/elf.h>

#घोषणा __under_task_size(addr, size) \
	(((अचिन्हित दीर्घ) (addr) < TASK_SIZE) && \
	 (((अचिन्हित दीर्घ) (addr) + (size)) < TASK_SIZE))

#घोषणा __access_ok_vsyscall(addr, size) \
	  (((अचिन्हित दीर्घ) (addr) >= FIXADDR_USER_START) && \
	  ((अचिन्हित दीर्घ) (addr) + (size) <= FIXADDR_USER_END) && \
	  ((अचिन्हित दीर्घ) (addr) + (size) >= (अचिन्हित दीर्घ)(addr)))

#घोषणा __addr_range_nowrap(addr, size) \
	((अचिन्हित दीर्घ) (addr) <= ((अचिन्हित दीर्घ) (addr) + (size)))

बाह्य अचिन्हित दीर्घ raw_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n);
बाह्य अचिन्हित दीर्घ raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n);
बाह्य दीर्घ __म_नकलन_from_user(अक्षर *dst, स्थिर अक्षर __user *src, दीर्घ count);
बाह्य दीर्घ __strnlen_user(स्थिर व्योम __user *str, दीर्घ len);
बाह्य अचिन्हित दीर्घ __clear_user(व्योम __user *mem, अचिन्हित दीर्घ len);
अटल अंतरभूत पूर्णांक __access_ok(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size);

/* Teach यंत्र-generic/uaccess.h that we have C functions क्रम these. */
#घोषणा __access_ok __access_ok
#घोषणा __clear_user __clear_user
#घोषणा __strnlen_user __strnlen_user
#घोषणा __म_नकलन_from_user __म_नकलन_from_user
#घोषणा INLINE_COPY_FROM_USER
#घोषणा INLINE_COPY_TO_USER

#समावेश <यंत्र-generic/uaccess.h>

अटल अंतरभूत पूर्णांक __access_ok(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	वापस __addr_range_nowrap(addr, size) &&
		(__under_task_size(addr, size) ||
		__access_ok_vsyscall(addr, size) ||
		uaccess_kernel());
पूर्ण

#पूर्ण_अगर
