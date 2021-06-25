<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* 
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#अगर_अघोषित __USER_H__
#घोषणा __USER_H__

#समावेश <generated/यंत्र-offsets.h>

/*
 * The usual definition - copied here because the kernel provides its own,
 * fancier, type-safe, definition.  Using that one would require
 * copying too much infraकाष्ठाure क्रम my taste, so userspace files
 * get less checking than kernel files.
 */
#घोषणा ARRAY_SIZE(x) (माप(x) / माप((x)[0]))

/* This is to get माप_प्रकार */
#अगर_अघोषित __UM_HOST__
#समावेश <linux/types.h>
#अन्यथा
#समावेश <मानकघोष.स>
#पूर्ण_अगर

बाह्य व्योम panic(स्थिर अक्षर *fmt, ...)
	__attribute__ ((क्रमmat (म_लिखो, 1, 2)));

/* Requires preincluding include/linux/kern_levels.h */
#घोषणा UM_KERN_EMERG	KERN_EMERG
#घोषणा UM_KERN_ALERT	KERN_ALERT
#घोषणा UM_KERN_CRIT	KERN_CRIT
#घोषणा UM_KERN_ERR	KERN_ERR
#घोषणा UM_KERN_WARNING	KERN_WARNING
#घोषणा UM_KERN_NOTICE	KERN_NOTICE
#घोषणा UM_KERN_INFO	KERN_INFO
#घोषणा UM_KERN_DEBUG	KERN_DEBUG
#घोषणा UM_KERN_CONT	KERN_CONT

#अगर_घोषित UML_CONFIG_PRINTK
बाह्य पूर्णांक prपूर्णांकk(स्थिर अक्षर *fmt, ...)
	__attribute__ ((क्रमmat (म_लिखो, 1, 2)));
#अन्यथा
अटल अंतरभूत पूर्णांक prपूर्णांकk(स्थिर अक्षर *fmt, ...)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक in_aton(अक्षर *str);
बाह्य माप_प्रकार strlcpy(अक्षर *, स्थिर अक्षर *, माप_प्रकार);
बाह्य माप_प्रकार strlcat(अक्षर *, स्थिर अक्षर *, माप_प्रकार);

/* Copied from linux/compiler-gcc.h since we can't include it directly */
#घोषणा barrier() __यंत्र__ __अस्थिर__("": : :"memory")

#पूर्ण_अगर
