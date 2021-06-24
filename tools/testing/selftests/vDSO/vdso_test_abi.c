<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * vdso_full_test.c: Sample code to test all the समयrs.
 * Copyright (c) 2019 Arm Ltd.
 *
 * Compile with:
 * gcc -std=gnu99 vdso_full_test.c parse_vdso.c
 *
 */

#समावेश <मानक_निवेशt.h>
#समावेश <elf.h>
#समावेश <मानकपन.स>
#समावेश <समय.स>
#समावेश <sys/auxv.h>
#समावेश <sys/समय.स>
#घोषणा _GNU_SOURCE
#समावेश <unistd.h>
#समावेश <sys/syscall.h>

#समावेश "../kselftest.h"
#समावेश "vdso_config.h"

बाह्य व्योम *vdso_sym(स्थिर अक्षर *version, स्थिर अक्षर *name);
बाह्य व्योम vdso_init_from_sysinfo_ehdr(uपूर्णांकptr_t base);
बाह्य व्योम vdso_init_from_auxv(व्योम *auxv);

अटल स्थिर अक्षर *version;
अटल स्थिर अक्षर **name;

प्रकार दीर्घ (*vdso_समय_लोofday_t)(काष्ठा समयval *tv, काष्ठा समयzone *tz);
प्रकार दीर्घ (*vdso_घड़ी_समय_लो_t)(घड़ीid_t clk_id, काष्ठा बारpec *ts);
प्रकार दीर्घ (*vdso_घड़ी_getres_t)(घड़ीid_t clk_id, काष्ठा बारpec *ts);
प्रकार समय_प्रकार (*vdso_समय_प्रकार)(समय_प्रकार *t);

अटल पूर्णांक vdso_test_समय_लोofday(व्योम)
अणु
	/* Find समय_लोofday. */
	vdso_समय_लोofday_t vdso_समय_लोofday =
		(vdso_समय_लोofday_t)vdso_sym(version, name[0]);

	अगर (!vdso_समय_लोofday) अणु
		म_लिखो("Could not find %s\n", name[0]);
		वापस KSFT_SKIP;
	पूर्ण

	काष्ठा समयval tv;
	दीर्घ ret = vdso_समय_लोofday(&tv, 0);

	अगर (ret == 0) अणु
		म_लिखो("The time is %lld.%06lld\n",
		       (दीर्घ दीर्घ)tv.tv_sec, (दीर्घ दीर्घ)tv.tv_usec);
	पूर्ण अन्यथा अणु
		म_लिखो("%s failed\n", name[0]);
		वापस KSFT_FAIL;
	पूर्ण

	वापस KSFT_PASS;
पूर्ण

अटल पूर्णांक vdso_test_घड़ी_समय_लो(घड़ीid_t clk_id)
अणु
	/* Find घड़ी_समय_लो. */
	vdso_घड़ी_समय_लो_t vdso_घड़ी_समय_लो =
		(vdso_घड़ी_समय_लो_t)vdso_sym(version, name[1]);

	अगर (!vdso_घड़ी_समय_लो) अणु
		म_लिखो("Could not find %s\n", name[1]);
		वापस KSFT_SKIP;
	पूर्ण

	काष्ठा बारpec ts;
	दीर्घ ret = vdso_घड़ी_समय_लो(clk_id, &ts);

	अगर (ret == 0) अणु
		म_लिखो("The time is %lld.%06lld\n",
		       (दीर्घ दीर्घ)ts.tv_sec, (दीर्घ दीर्घ)ts.tv_nsec);
	पूर्ण अन्यथा अणु
		म_लिखो("%s failed\n", name[1]);
		वापस KSFT_FAIL;
	पूर्ण

	वापस KSFT_PASS;
पूर्ण

अटल पूर्णांक vdso_test_समय(व्योम)
अणु
	/* Find समय. */
	vdso_समय_प्रकार vdso_समय =
		(vdso_समय_प्रकार)vdso_sym(version, name[2]);

	अगर (!vdso_समय) अणु
		म_लिखो("Could not find %s\n", name[2]);
		वापस KSFT_SKIP;
	पूर्ण

	दीर्घ ret = vdso_समय(शून्य);

	अगर (ret > 0) अणु
		म_लिखो("The time in hours since January 1, 1970 is %lld\n",
				(दीर्घ दीर्घ)(ret / 3600));
	पूर्ण अन्यथा अणु
		म_लिखो("%s failed\n", name[2]);
		वापस KSFT_FAIL;
	पूर्ण

	वापस KSFT_PASS;
पूर्ण

अटल पूर्णांक vdso_test_घड़ी_getres(घड़ीid_t clk_id)
अणु
	/* Find घड़ी_getres. */
	vdso_घड़ी_getres_t vdso_घड़ी_getres =
		(vdso_घड़ी_getres_t)vdso_sym(version, name[3]);

	अगर (!vdso_घड़ी_getres) अणु
		म_लिखो("Could not find %s\n", name[3]);
		वापस KSFT_SKIP;
	पूर्ण

	काष्ठा बारpec ts, sys_ts;
	दीर्घ ret = vdso_घड़ी_getres(clk_id, &ts);

	अगर (ret == 0) अणु
		म_लिखो("The resolution is %lld %lld\n",
		       (दीर्घ दीर्घ)ts.tv_sec, (दीर्घ दीर्घ)ts.tv_nsec);
	पूर्ण अन्यथा अणु
		म_लिखो("%s failed\n", name[3]);
		वापस KSFT_FAIL;
	पूर्ण

	ret = syscall(SYS_घड़ी_getres, clk_id, &sys_ts);

	अगर ((sys_ts.tv_sec != ts.tv_sec) || (sys_ts.tv_nsec != ts.tv_nsec)) अणु
		म_लिखो("%s failed\n", name[3]);
		वापस KSFT_FAIL;
	पूर्ण

	वापस KSFT_PASS;
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
 * This function calls vdso_test_घड़ी_समय_लो and vdso_test_घड़ी_getres
 * with dअगरferent values क्रम घड़ी_id.
 */
अटल अंतरभूत पूर्णांक vdso_test_घड़ी(घड़ीid_t घड़ी_id)
अणु
	पूर्णांक ret0, ret1;

	ret0 = vdso_test_घड़ी_समय_लो(घड़ी_id);
	/* A skipped test is considered passed */
	अगर (ret0 == KSFT_SKIP)
		ret0 = KSFT_PASS;

	ret1 = vdso_test_घड़ी_getres(घड़ी_id);
	/* A skipped test is considered passed */
	अगर (ret1 == KSFT_SKIP)
		ret1 = KSFT_PASS;

	ret0 += ret1;

	म_लिखो("clock_id: %s", vdso_घड़ी_name[घड़ी_id]);

	अगर (ret0 > 0)
		म_लिखो(" [FAIL]\n");
	अन्यथा
		म_लिखो(" [PASS]\n");

	वापस ret0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अचिन्हित दीर्घ sysinfo_ehdr = getauxval(AT_SYSINFO_EHDR);
	पूर्णांक ret;

	अगर (!sysinfo_ehdr) अणु
		म_लिखो("AT_SYSINFO_EHDR is not present!\n");
		वापस KSFT_SKIP;
	पूर्ण

	version = versions[VDSO_VERSION];
	name = (स्थिर अक्षर **)&names[VDSO_NAMES];

	म_लिखो("[vDSO kselftest] VDSO_VERSION: %s\n", version);

	vdso_init_from_sysinfo_ehdr(getauxval(AT_SYSINFO_EHDR));

	ret = vdso_test_समय_लोofday();

#अगर _POSIX_TIMERS > 0

#अगर_घोषित CLOCK_REALTIME
	ret += vdso_test_घड़ी(CLOCK_REALTIME);
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

	ret += vdso_test_समय();

	अगर (ret > 0)
		वापस KSFT_FAIL;

	वापस KSFT_PASS;
पूर्ण
