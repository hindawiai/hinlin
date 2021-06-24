<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* 
 * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)
 */

#अगर_अघोषित __KERN_H__
#घोषणा __KERN_H__

/* These are all user-mode things which are convenient to call directly
 * from kernel code and क्रम which writing a wrapper is too much of a pain.
 * The regular include files can't be included because this file is included
 * only पूर्णांकo kernel code, and user-space includes conflict with kernel
 * includes.
 */

बाह्य पूर्णांक म_लिखो(स्थिर अक्षर *fmt, ...);
बाह्य व्योम *sbrk(पूर्णांक increment);
बाह्य पूर्णांक छोड़ो(व्योम);
बाह्य व्योम निकास(पूर्णांक);

#पूर्ण_अगर

