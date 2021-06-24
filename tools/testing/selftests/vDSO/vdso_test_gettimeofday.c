<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vdso_test_समय_लोofday.c: Sample code to test parse_vdso.c and
 *                           vDSO समय_लोofday()
 * Copyright (c) 2014 Andy Lutomirski
 *
 * Compile with:
 * gcc -std=gnu99 vdso_test_समय_लोofday.c parse_vdso_समय_लोofday.c
 *
 * Tested on x86, 32-bit and 64-bit.  It may work on other architectures, too.
 */

#समावेश <मानक_निवेशt.h>
#समावेश <elf.h>
#समावेश <मानकपन.स>
#समावेश <sys/auxv.h>
#समावेश <sys/समय.स>

#समावेश "../kselftest.h"
#समावेश "parse_vdso.h"

/*
 * ARM64's vDSO exports its समय_लोofday() implementation with a dअगरferent
 * name and version from other architectures, so we need to handle it as
 * a special हाल.
 */
#अगर defined(__aarch64__)
स्थिर अक्षर *version = "LINUX_2.6.39";
स्थिर अक्षर *name = "__kernel_gettimeofday";
#अन्यथा
स्थिर अक्षर *version = "LINUX_2.6";
स्थिर अक्षर *name = "__vdso_gettimeofday";
#पूर्ण_अगर

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अचिन्हित दीर्घ sysinfo_ehdr = getauxval(AT_SYSINFO_EHDR);
	अगर (!sysinfo_ehdr) अणु
		म_लिखो("AT_SYSINFO_EHDR is not present!\n");
		वापस KSFT_SKIP;
	पूर्ण

	vdso_init_from_sysinfo_ehdr(getauxval(AT_SYSINFO_EHDR));

	/* Find समय_लोofday. */
	प्रकार दीर्घ (*gtod_t)(काष्ठा समयval *tv, काष्ठा समयzone *tz);
	gtod_t gtod = (gtod_t)vdso_sym(version, name);

	अगर (!gtod) अणु
		म_लिखो("Could not find %s\n", name);
		वापस KSFT_SKIP;
	पूर्ण

	काष्ठा समयval tv;
	दीर्घ ret = gtod(&tv, 0);

	अगर (ret == 0) अणु
		म_लिखो("The time is %lld.%06lld\n",
		       (दीर्घ दीर्घ)tv.tv_sec, (दीर्घ दीर्घ)tv.tv_usec);
	पूर्ण अन्यथा अणु
		म_लिखो("%s failed\n", name);
		वापस KSFT_FAIL;
	पूर्ण

	वापस 0;
पूर्ण
