<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Most of the string-functions are rather heavily hand-optimized,
 * see especially strsep,म_माला,str[c]spn. They should work, but are not
 * very easy to understand. Everything is करोne entirely within the रेजिस्टर
 * set, making the functions fast and clean. String inकाष्ठाions have been
 * used through-out, making क्रम "slightly" unclear code :-)
 *
 * AK: On P4 and K7 using non string inकाष्ठाion implementations might be faster
 * क्रम large memory blocks. But most of them are unlikely to be used on large
 * strings.
 */

#समावेश <linux/माला.स>
#समावेश <linux/export.h>

#अगर_घोषित __HAVE_ARCH_STRCPY
अक्षर *म_नकल(अक्षर *dest, स्थिर अक्षर *src)
अणु
	पूर्णांक d0, d1, d2;
	यंत्र अस्थिर("1:\tlodsb\n\t"
		"stosb\n\t"
		"testb %%al,%%al\n\t"
		"jne 1b"
		: "=&S" (d0), "=&D" (d1), "=&a" (d2)
		: "0" (src), "1" (dest) : "memory");
	वापस dest;
पूर्ण
EXPORT_SYMBOL(म_नकल);
#पूर्ण_अगर

#अगर_घोषित __HAVE_ARCH_STRNCPY
अक्षर *म_नकलन(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार count)
अणु
	पूर्णांक d0, d1, d2, d3;
	यंत्र अस्थिर("1:\tdecl %2\n\t"
		"js 2f\n\t"
		"lodsb\n\t"
		"stosb\n\t"
		"testb %%al,%%al\n\t"
		"jne 1b\n\t"
		"rep\n\t"
		"stosb\n"
		"2:"
		: "=&S" (d0), "=&D" (d1), "=&c" (d2), "=&a" (d3)
		: "0" (src), "1" (dest), "2" (count) : "memory");
	वापस dest;
पूर्ण
EXPORT_SYMBOL(म_नकलन);
#पूर्ण_अगर

#अगर_घोषित __HAVE_ARCH_STRCAT
अक्षर *म_जोड़ो(अक्षर *dest, स्थिर अक्षर *src)
अणु
	पूर्णांक d0, d1, d2, d3;
	यंत्र अस्थिर("repne\n\t"
		"scasb\n\t"
		"decl %1\n"
		"1:\tlodsb\n\t"
		"stosb\n\t"
		"testb %%al,%%al\n\t"
		"jne 1b"
		: "=&S" (d0), "=&D" (d1), "=&a" (d2), "=&c" (d3)
		: "0" (src), "1" (dest), "2" (0), "3" (0xffffffffu) : "memory");
	वापस dest;
पूर्ण
EXPORT_SYMBOL(म_जोड़ो);
#पूर्ण_अगर

#अगर_घोषित __HAVE_ARCH_STRNCAT
अक्षर *म_जोड़न(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार count)
अणु
	पूर्णांक d0, d1, d2, d3;
	यंत्र अस्थिर("repne\n\t"
		"scasb\n\t"
		"decl %1\n\t"
		"movl %8,%3\n"
		"1:\tdecl %3\n\t"
		"js 2f\n\t"
		"lodsb\n\t"
		"stosb\n\t"
		"testb %%al,%%al\n\t"
		"jne 1b\n"
		"2:\txorl %2,%2\n\t"
		"stosb"
		: "=&S" (d0), "=&D" (d1), "=&a" (d2), "=&c" (d3)
		: "0" (src), "1" (dest), "2" (0), "3" (0xffffffffu), "g" (count)
		: "memory");
	वापस dest;
पूर्ण
EXPORT_SYMBOL(म_जोड़न);
#पूर्ण_अगर

#अगर_घोषित __HAVE_ARCH_STRCMP
पूर्णांक म_भेद(स्थिर अक्षर *cs, स्थिर अक्षर *ct)
अणु
	पूर्णांक d0, d1;
	पूर्णांक res;
	यंत्र अस्थिर("1:\tlodsb\n\t"
		"scasb\n\t"
		"jne 2f\n\t"
		"testb %%al,%%al\n\t"
		"jne 1b\n\t"
		"xorl %%eax,%%eax\n\t"
		"jmp 3f\n"
		"2:\tsbbl %%eax,%%eax\n\t"
		"orb $1,%%al\n"
		"3:"
		: "=a" (res), "=&S" (d0), "=&D" (d1)
		: "1" (cs), "2" (ct)
		: "memory");
	वापस res;
पूर्ण
EXPORT_SYMBOL(म_भेद);
#पूर्ण_अगर

#अगर_घोषित __HAVE_ARCH_STRNCMP
पूर्णांक म_भेदन(स्थिर अक्षर *cs, स्थिर अक्षर *ct, माप_प्रकार count)
अणु
	पूर्णांक res;
	पूर्णांक d0, d1, d2;
	यंत्र अस्थिर("1:\tdecl %3\n\t"
		"js 2f\n\t"
		"lodsb\n\t"
		"scasb\n\t"
		"jne 3f\n\t"
		"testb %%al,%%al\n\t"
		"jne 1b\n"
		"2:\txorl %%eax,%%eax\n\t"
		"jmp 4f\n"
		"3:\tsbbl %%eax,%%eax\n\t"
		"orb $1,%%al\n"
		"4:"
		: "=a" (res), "=&S" (d0), "=&D" (d1), "=&c" (d2)
		: "1" (cs), "2" (ct), "3" (count)
		: "memory");
	वापस res;
पूर्ण
EXPORT_SYMBOL(म_भेदन);
#पूर्ण_अगर

#अगर_घोषित __HAVE_ARCH_STRCHR
अक्षर *म_अक्षर(स्थिर अक्षर *s, पूर्णांक c)
अणु
	पूर्णांक d0;
	अक्षर *res;
	यंत्र अस्थिर("movb %%al,%%ah\n"
		"1:\tlodsb\n\t"
		"cmpb %%ah,%%al\n\t"
		"je 2f\n\t"
		"testb %%al,%%al\n\t"
		"jne 1b\n\t"
		"movl $1,%1\n"
		"2:\tmovl %1,%0\n\t"
		"decl %0"
		: "=a" (res), "=&S" (d0)
		: "1" (s), "0" (c)
		: "memory");
	वापस res;
पूर्ण
EXPORT_SYMBOL(म_अक्षर);
#पूर्ण_अगर

#अगर_घोषित __HAVE_ARCH_STRLEN
माप_प्रकार म_माप(स्थिर अक्षर *s)
अणु
	पूर्णांक d0;
	माप_प्रकार res;
	यंत्र अस्थिर("repne\n\t"
		"scasb"
		: "=c" (res), "=&D" (d0)
		: "1" (s), "a" (0), "0" (0xffffffffu)
		: "memory");
	वापस ~res - 1;
पूर्ण
EXPORT_SYMBOL(म_माप);
#पूर्ण_अगर

#अगर_घोषित __HAVE_ARCH_MEMCHR
व्योम *स_प्रथम(स्थिर व्योम *cs, पूर्णांक c, माप_प्रकार count)
अणु
	पूर्णांक d0;
	व्योम *res;
	अगर (!count)
		वापस शून्य;
	यंत्र अस्थिर("repne\n\t"
		"scasb\n\t"
		"je 1f\n\t"
		"movl $1,%0\n"
		"1:\tdecl %0"
		: "=D" (res), "=&c" (d0)
		: "a" (c), "0" (cs), "1" (count)
		: "memory");
	वापस res;
पूर्ण
EXPORT_SYMBOL(स_प्रथम);
#पूर्ण_अगर

#अगर_घोषित __HAVE_ARCH_MEMSCAN
व्योम *memscan(व्योम *addr, पूर्णांक c, माप_प्रकार size)
अणु
	अगर (!size)
		वापस addr;
	यंत्र अस्थिर("repnz; scasb\n\t"
	    "jnz 1f\n\t"
	    "dec %%edi\n"
	    "1:"
	    : "=D" (addr), "=c" (size)
	    : "0" (addr), "1" (size), "a" (c)
	    : "memory");
	वापस addr;
पूर्ण
EXPORT_SYMBOL(memscan);
#पूर्ण_अगर

#अगर_घोषित __HAVE_ARCH_STRNLEN
माप_प्रकार strnlen(स्थिर अक्षर *s, माप_प्रकार count)
अणु
	पूर्णांक d0;
	पूर्णांक res;
	यंत्र अस्थिर("movl %2,%0\n\t"
		"jmp 2f\n"
		"1:\tcmpb $0,(%0)\n\t"
		"je 3f\n\t"
		"incl %0\n"
		"2:\tdecl %1\n\t"
		"cmpl $-1,%1\n\t"
		"jne 1b\n"
		"3:\tsubl %2,%0"
		: "=a" (res), "=&d" (d0)
		: "c" (s), "1" (count)
		: "memory");
	वापस res;
पूर्ण
EXPORT_SYMBOL(strnlen);
#पूर्ण_अगर
