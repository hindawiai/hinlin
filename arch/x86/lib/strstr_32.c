<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/माला.स>
#समावेश <linux/export.h>

अक्षर *म_माला(स्थिर अक्षर *cs, स्थिर अक्षर *ct)
अणु
पूर्णांक	d0, d1;
रेजिस्टर अक्षर *__res;
__यंत्र__ __अस्थिर__(
	"movl %6,%%edi\n\t"
	"repne\n\t"
	"scasb\n\t"
	"notl %%ecx\n\t"
	"decl %%ecx\n\t"	/* NOTE! This also sets Z अगर searchstring='' */
	"movl %%ecx,%%edx\n"
	"1:\tmovl %6,%%edi\n\t"
	"movl %%esi,%%eax\n\t"
	"movl %%edx,%%ecx\n\t"
	"repe\n\t"
	"cmpsb\n\t"
	"je 2f\n\t"		/* also works क्रम empty string, see above */
	"xchgl %%eax,%%esi\n\t"
	"incl %%esi\n\t"
	"cmpb $0,-1(%%eax)\n\t"
	"jne 1b\n\t"
	"xorl %%eax,%%eax\n\t"
	"2:"
	: "=a" (__res), "=&c" (d0), "=&S" (d1)
	: "0" (0), "1" (0xffffffff), "2" (cs), "g" (ct)
	: "dx", "di");
वापस __res;
पूर्ण
EXPORT_SYMBOL(म_माला);
