<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TOOLS_LINUX_STRING_H_
#घोषणा _TOOLS_LINUX_STRING_H_

#समावेश <linux/types.h>	/* क्रम माप_प्रकार */
#समावेश <माला.स>

व्योम *memdup(स्थिर व्योम *src, माप_प्रकार len);

अक्षर **argv_split(स्थिर अक्षर *str, पूर्णांक *argcp);
व्योम argv_मुक्त(अक्षर **argv);

पूर्णांक strtobool(स्थिर अक्षर *s, bool *res);

/*
 * glibc based builds needs the बाह्य जबतक uClibc करोesn't.
 * However uClibc headers also define __GLIBC__ hence the hack below
 */
#अगर defined(__GLIBC__) && !defined(__UCLIBC__)
// pragma diagnostic was पूर्णांकroduced in gcc 4.6
#अगर __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#आशय GCC diagnostic push
#आशय GCC diagnostic ignored "-Wredundant-decls"
#पूर्ण_अगर
बाह्य माप_प्रकार strlcpy(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार size);
#अगर __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#आशय GCC diagnostic pop
#पूर्ण_अगर
#पूर्ण_अगर

अक्षर *str_error_r(पूर्णांक errnum, अक्षर *buf, माप_प्रकार buflen);

अक्षर *strreplace(अक्षर *s, अक्षर old, अक्षर new);

/**
 * strstarts - करोes @str start with @prefix?
 * @str: string to examine
 * @prefix: prefix to look क्रम.
 */
अटल अंतरभूत bool strstarts(स्थिर अक्षर *str, स्थिर अक्षर *prefix)
अणु
	वापस म_भेदन(str, prefix, म_माप(prefix)) == 0;
पूर्ण

बाह्य अक्षर * __must_check skip_spaces(स्थिर अक्षर *);

बाह्य अक्षर *strim(अक्षर *);

बाह्य व्योम *स_प्रथम_inv(स्थिर व्योम *start, पूर्णांक c, माप_प्रकार bytes);
#पूर्ण_अगर /* _TOOLS_LINUX_STRING_H_ */
