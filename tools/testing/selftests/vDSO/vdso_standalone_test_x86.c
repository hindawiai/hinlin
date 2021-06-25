<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vdso_test.c: Sample code to test parse_vdso.c on x86
 * Copyright (c) 2011-2014 Andy Lutomirski
 *
 * You can amuse yourself by compiling with:
 * gcc -std=gnu99 -nostdlib
 *     -Os -fno-asynchronous-unwind-tables -flto -lgcc_s
 *      vdso_standalone_test_x86.c parse_vdso.c
 * to generate a small binary.  On x86_64, you can omit -lgcc_s
 * अगर you want the binary to be completely standalone.
 */

#समावेश <sys/syscall.h>
#समावेश <sys/समय.स>
#समावेश <unistd.h>
#समावेश <मानक_निवेशt.h>

#समावेश "parse_vdso.h"

/* We need a libc functions... */
पूर्णांक म_भेद(स्थिर अक्षर *a, स्थिर अक्षर *b)
अणु
	/* This implementation is buggy: it never वापसs -1. */
	जबतक (*a || *b) अणु
		अगर (*a != *b)
			वापस 1;
		अगर (*a == 0 || *b == 0)
			वापस 1;
		a++;
		b++;
	पूर्ण

	वापस 0;
पूर्ण

/* ...and two syscalls.  This is x86-specअगरic. */
अटल अंतरभूत दीर्घ x86_syscall3(दीर्घ nr, दीर्घ a0, दीर्घ a1, दीर्घ a2)
अणु
	दीर्घ ret;
#अगर_घोषित __x86_64__
	यंत्र अस्थिर ("syscall" : "=a" (ret) : "a" (nr),
		      "D" (a0), "S" (a1), "d" (a2) :
		      "cc", "memory", "rcx",
		      "r8", "r9", "r10", "r11" );
#अन्यथा
	यंत्र अस्थिर ("int $0x80" : "=a" (ret) : "a" (nr),
		      "b" (a0), "c" (a1), "d" (a2) :
		      "cc", "memory" );
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल अंतरभूत दीर्घ linux_ग_लिखो(पूर्णांक fd, स्थिर व्योम *data, माप_प्रकार len)
अणु
	वापस x86_syscall3(__NR_ग_लिखो, fd, (दीर्घ)data, (दीर्घ)len);
पूर्ण

अटल अंतरभूत व्योम linux_निकास(पूर्णांक code)
अणु
	x86_syscall3(__NR_निकास, code, 0, 0);
पूर्ण

व्योम to_base10(अक्षर *lastdig, समय_प्रकार n)
अणु
	जबतक (n) अणु
		*lastdig = (n % 10) + '0';
		n /= 10;
		lastdig--;
	पूर्ण
पूर्ण

__attribute__((बाह्यally_visible)) व्योम c_मुख्य(व्योम **stack)
अणु
	/* Parse the stack */
	दीर्घ argc = (दीर्घ)*stack;
	stack += argc + 2;

	/* Now we're poपूर्णांकing at the environment.  Skip it. */
	जबतक(*stack)
		stack++;
	stack++;

	/* Now we're poपूर्णांकing at auxv.  Initialize the vDSO parser. */
	vdso_init_from_auxv((व्योम *)stack);

	/* Find समय_लोofday. */
	प्रकार दीर्घ (*gtod_t)(काष्ठा समयval *tv, काष्ठा समयzone *tz);
	gtod_t gtod = (gtod_t)vdso_sym("LINUX_2.6", "__vdso_gettimeofday");

	अगर (!gtod)
		linux_निकास(1);

	काष्ठा समयval tv;
	दीर्घ ret = gtod(&tv, 0);

	अगर (ret == 0) अणु
		अक्षर buf[] = "The time is                     .000000\n";
		to_base10(buf + 31, tv.tv_sec);
		to_base10(buf + 38, tv.tv_usec);
		linux_ग_लिखो(1, buf, माप(buf) - 1);
	पूर्ण अन्यथा अणु
		linux_निकास(ret);
	पूर्ण

	linux_निकास(0);
पूर्ण

/*
 * This is the real entry poपूर्णांक.  It passes the initial stack पूर्णांकo
 * the C entry poपूर्णांक.
 */
यंत्र (
	".text\n"
	".global _start\n"
	".type _start,@function\n"
	"_start:\n\t"
#अगर_घोषित __x86_64__
	"mov %rsp,%rdi\n\t"
	"jmp c_main"
#अन्यथा
	"push %esp\n\t"
	"call c_main\n\t"
	"int $3"
#पूर्ण_अगर
	);
