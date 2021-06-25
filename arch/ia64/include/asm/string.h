<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_STRING_H
#घोषणा _ASM_IA64_STRING_H

/*
 * Here is where we want to put optimized versions of the string
 * routines.
 *
 * Copyright (C) 1998-2000, 2002 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */


#घोषणा __HAVE_ARCH_STRLEN	1 /* see arch/ia64/lib/म_माप.S */
#घोषणा __HAVE_ARCH_MEMSET	1 /* see arch/ia64/lib/स_रखो.S */
#घोषणा __HAVE_ARCH_MEMCPY	1 /* see arch/ia64/lib/स_नकल.S */

बाह्य __kernel_माप_प्रकार म_माप (स्थिर अक्षर *);
बाह्य व्योम *स_नकल (व्योम *, स्थिर व्योम *, __kernel_माप_प्रकार);
बाह्य व्योम *स_रखो (व्योम *, पूर्णांक, __kernel_माप_प्रकार);

#पूर्ण_अगर /* _ASM_IA64_STRING_H */
