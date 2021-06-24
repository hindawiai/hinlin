<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *    Optimized memory copy routines.
 *
 *    Copyright (C) 2004 Ranकरोlph Chung <tausq@debian.org>
 *    Copyright (C) 2013-2017 Helge Deller <deller@gmx.de>
 *
 *    Portions derived from the GNU C Library
 *    Copyright (C) 1991, 1997, 2003 Free Software Foundation, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/compiler.h>
#समावेश <linux/uaccess.h>

#घोषणा get_user_space() (uaccess_kernel() ? 0 : mfsp(3))
#घोषणा get_kernel_space() (0)

/* Returns 0 क्रम success, otherwise, वापसs number of bytes not transferred. */
बाह्य अचिन्हित दीर्घ pa_स_नकल(व्योम *dst, स्थिर व्योम *src,
				अचिन्हित दीर्घ len);

अचिन्हित दीर्घ raw_copy_to_user(व्योम __user *dst, स्थिर व्योम *src,
			       अचिन्हित दीर्घ len)
अणु
	mtsp(get_kernel_space(), 1);
	mtsp(get_user_space(), 2);
	वापस pa_स_नकल((व्योम __क्रमce *)dst, src, len);
पूर्ण
EXPORT_SYMBOL(raw_copy_to_user);

अचिन्हित दीर्घ raw_copy_from_user(व्योम *dst, स्थिर व्योम __user *src,
			       अचिन्हित दीर्घ len)
अणु
	mtsp(get_user_space(), 1);
	mtsp(get_kernel_space(), 2);
	वापस pa_स_नकल(dst, (व्योम __क्रमce *)src, len);
पूर्ण
EXPORT_SYMBOL(raw_copy_from_user);

अचिन्हित दीर्घ raw_copy_in_user(व्योम __user *dst, स्थिर व्योम __user *src, अचिन्हित दीर्घ len)
अणु
	mtsp(get_user_space(), 1);
	mtsp(get_user_space(), 2);
	वापस pa_स_नकल((व्योम __क्रमce *)dst, (व्योम __क्रमce *)src, len);
पूर्ण


व्योम * स_नकल(व्योम * dst,स्थिर व्योम *src, माप_प्रकार count)
अणु
	mtsp(get_kernel_space(), 1);
	mtsp(get_kernel_space(), 2);
	pa_स_नकल(dst, src, count);
	वापस dst;
पूर्ण

EXPORT_SYMBOL(raw_copy_in_user);
EXPORT_SYMBOL(स_नकल);

bool copy_from_kernel_nofault_allowed(स्थिर व्योम *unsafe_src, माप_प्रकार size)
अणु
	अगर ((अचिन्हित दीर्घ)unsafe_src < PAGE_SIZE)
		वापस false;
	/* check क्रम I/O space F_EXTEND(0xfff00000) access as well? */
	वापस true;
पूर्ण
