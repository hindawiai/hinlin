<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note
/*
 * vdso_घड़ी_getres.c: Sample code to test घड़ी_getres.
 * Copyright (c) 2019 Arm Ltd.
 *
 * Compile with:
 * gcc -std=gnu99 vdso_घड़ी_getres.c
 *
 * Tested on ARM, ARM64, MIPS32, x86 (32-bit and 64-bit),
 * Power (32-bit and 64-bit), S390x (32-bit and 64-bit).
 * Might work on other architectures.
 */

#घोषणा _GNU_SOURCE
#समावेश <elf.h>
#समावेश <err.h>
#समावेश <fcntl.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <समय.स>
#समावेश <sys/auxv.h>
#समावेश <sys/mman.h>
#समावेश <sys/समय.स>
#समावेश <unistd.h>
#समावेश <sys/syscall.h>

#समावेश "../kselftest.h"

अटल दीर्घ syscall_घड़ी_getres(घड़ीid_t _clkid, काष्ठा बारpec *_ts)
अणु
	दीर्घ ret;

	ret = syscall(SYS_घड़ी_getres, _clkid, _ts);

	वापस ret;
पूर्ण

स्थिर अक्षर *vdso_घड़ी_name[12] = अणु
	"CLOCK_REALTIME",
	"CLOCK_MONOTONIC",
	"CLOCK_PROCESS_CPUTIME_ID",
	"CLOCK_THREAD_CPUTIME_ID",
	"CLOCK_MONOTONIC_RAW",
	"CLOCK_REALTIME_COARSE",
	"CLOCK_MONOTONIC_COARSE",
	"CLOCK_BOOTTIME",
	"CLOCK_REALTIME_ALARM",
	"CLOCK_BOOTTIME_ALARM",
	"CLOCK_SGI_CYCLE",
	"CLOCK_TAI",
पूर्ण;

/*
 * This function calls घड़ी_getres in vdso and by प्रणाली call
 * with dअगरferent values क्रम घड़ी_id.
 *
 * Example of output:
 *
 * घड़ी_id: CLOCK_REALTIME [PASS]
 * घड़ी_id: CLOCK_BOOTTIME [PASS]
 * घड़ी_id: CLOCK_TAI [PASS]
 * घड़ी_id: CLOCK_REALTIME_COARSE [PASS]
 * घड़ी_id: CLOCK_MONOTONIC [PASS]
 * घड़ी_id: CLOCK_MONOTONIC_RAW [PASS]
 * घड़ी_id: CLOCK_MONOTONIC_COARSE [PASS]
 */
अटल अंतरभूत पूर्णांक vdso_test_घड़ी(अचिन्हित पूर्णांक घड़ी_id)
अणु
	काष्ठा बारpec x, y;

	म_लिखो("clock_id: %s", vdso_घड़ी_name[घड़ी_id]);
	घड़ी_getres(घड़ी_id, &x);
	syscall_घड़ी_getres(घड़ी_id, &y);

	अगर ((x.tv_sec != y.tv_sec) || (x.tv_nsec != y.tv_nsec)) अणु
		म_लिखो(" [FAIL]\n");
		वापस KSFT_FAIL;
	पूर्ण

	म_लिखो(" [PASS]\n");
	वापस KSFT_PASS;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक ret;

#अगर _POSIX_TIMERS > 0

#अगर_घोषित CLOCK_REALTIME
	ret = vdso_test_घड़ी(CLOCK_REALTIME);
#पूर्ण_अगर

#अगर_घोषित CLOCK_BOOTTIME
	ret += vdso_test_घड़ी(CLOCK_BOOTTIME);
#पूर्ण_अगर

#अगर_घोषित CLOCK_TAI
	ret += vdso_test_घड़ी(CLOCK_TAI);
#पूर्ण_अगर

#अगर_घोषित CLOCK_REALTIME_COARSE
	ret += vdso_test_घड़ी(CLOCK_REALTIME_COARSE);
#पूर्ण_अगर

#अगर_घोषित CLOCK_MONOTONIC
	ret += vdso_test_घड़ी(CLOCK_MONOTONIC);
#पूर्ण_अगर

#अगर_घोषित CLOCK_MONOTONIC_RAW
	ret += vdso_test_घड़ी(CLOCK_MONOTONIC_RAW);
#पूर्ण_अगर

#अगर_घोषित CLOCK_MONOTONIC_COARSE
	ret += vdso_test_घड़ी(CLOCK_MONOTONIC_COARSE);
#पूर्ण_अगर

#पूर्ण_अगर
	अगर (ret > 0)
		वापस KSFT_FAIL;

	वापस KSFT_PASS;
पूर्ण
