<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानककोष.स>

#अगर !defined(__UCLIBC__)
#समावेश <gnu/libc-version.h>
#अन्यथा
#घोषणा XSTR(s) STR(s)
#घोषणा STR(s) #s
#पूर्ण_अगर

पूर्णांक मुख्य(व्योम)
अणु
#अगर !defined(__UCLIBC__)
	स्थिर अक्षर *version = gnu_get_libc_version();
#अन्यथा
	स्थिर अक्षर *version = XSTR(__GLIBC__) "." XSTR(__GLIBC_MINOR__);
#पूर्ण_अगर

	वापस (दीर्घ)version;
पूर्ण
