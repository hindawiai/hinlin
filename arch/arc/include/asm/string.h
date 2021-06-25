<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * vineetg: May 2011
 *  -We had half-optimised स_रखो/स_नकल, got better versions of those
 *  -Added स_भेद, म_अक्षर, म_नकल, म_भेद, म_माप
 *
 * Amit Bhor: Codito Technologies 2004
 */

#अगर_अघोषित _ASM_ARC_STRING_H
#घोषणा _ASM_ARC_STRING_H

#समावेश <linux/types.h>

#घोषणा __HAVE_ARCH_MEMSET
#घोषणा __HAVE_ARCH_MEMCPY
#घोषणा __HAVE_ARCH_MEMCMP
#घोषणा __HAVE_ARCH_STRCHR
#घोषणा __HAVE_ARCH_STRCPY
#घोषणा __HAVE_ARCH_STRCMP
#घोषणा __HAVE_ARCH_STRLEN

बाह्य व्योम *स_रखो(व्योम *ptr, पूर्णांक, __kernel_माप_प्रकार);
बाह्य व्योम *स_नकल(व्योम *, स्थिर व्योम *, __kernel_माप_प्रकार);
बाह्य व्योम memzero(व्योम *ptr, __kernel_माप_प्रकार n);
बाह्य पूर्णांक स_भेद(स्थिर व्योम *, स्थिर व्योम *, __kernel_माप_प्रकार);
बाह्य अक्षर *म_अक्षर(स्थिर अक्षर *s, पूर्णांक c);
बाह्य अक्षर *म_नकल(अक्षर *dest, स्थिर अक्षर *src);
बाह्य पूर्णांक म_भेद(स्थिर अक्षर *cs, स्थिर अक्षर *ct);
बाह्य __kernel_माप_प्रकार म_माप(स्थिर अक्षर *);

#पूर्ण_अगर /* _ASM_ARC_STRING_H */
