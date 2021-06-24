<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <sched.h>
#समावेश <समय.स>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <sys/syscall.h>
#समावेश <dlfcn.h>

#समावेश "log.h"
#समावेश "timens.h"

प्रकार पूर्णांक (*vसमय_लो_t)(घड़ीid_t, काष्ठा बारpec *);

vसमय_लो_t vdso_घड़ी_समय_लो;

अटल व्योम fill_function_poपूर्णांकers(व्योम)
अणु
	व्योम *vdso = dlखोलो("linux-vdso.so.1",
			    RTLD_LAZY | RTLD_LOCAL | RTLD_NOLOAD);
	अगर (!vdso)
		vdso = dlखोलो("linux-gate.so.1",
			      RTLD_LAZY | RTLD_LOCAL | RTLD_NOLOAD);
	अगर (!vdso)
		vdso = dlखोलो("linux-vdso32.so.1",
			      RTLD_LAZY | RTLD_LOCAL | RTLD_NOLOAD);
	अगर (!vdso)
		vdso = dlखोलो("linux-vdso64.so.1",
			      RTLD_LAZY | RTLD_LOCAL | RTLD_NOLOAD);
	अगर (!vdso) अणु
		pr_err("[WARN]\tfailed to find vDSO\n");
		वापस;
	पूर्ण

	vdso_घड़ी_समय_लो = (vसमय_लो_t)dlsym(vdso, "__vdso_clock_gettime");
	अगर (!vdso_घड़ी_समय_लो)
		vdso_घड़ी_समय_लो = (vसमय_लो_t)dlsym(vdso, "__kernel_clock_gettime");
	अगर (!vdso_घड़ी_समय_लो)
		pr_err("Warning: failed to find clock_gettime in vDSO\n");

पूर्ण

अटल व्योम test(घड़ी_प्रकार घड़ीid, अक्षर *घड़ीstr, bool in_ns)
अणु
	काष्ठा बारpec tp, start;
	दीर्घ i = 0;
	स्थिर पूर्णांक समयout = 3;

	vdso_घड़ी_समय_लो(घड़ीid, &start);
	tp = start;
	क्रम (tp = start; start.tv_sec + समयout > tp.tv_sec ||
			 (start.tv_sec + समयout == tp.tv_sec &&
			  start.tv_nsec > tp.tv_nsec); i++) अणु
		vdso_घड़ी_समय_लो(घड़ीid, &tp);
	पूर्ण

	ksft_test_result_pass("%s:\tclock: %10s\tcycles:\t%10ld\n",
			      in_ns ? "ns" : "host", घड़ीstr, i);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	समय_प्रकार offset = 10;
	पूर्णांक nsfd;

	ksft_set_plan(8);

	fill_function_poपूर्णांकers();

	test(CLOCK_MONOTONIC, "monotonic", false);
	test(CLOCK_MONOTONIC_COARSE, "monotonic-coarse", false);
	test(CLOCK_MONOTONIC_RAW, "monotonic-raw", false);
	test(CLOCK_BOOTTIME, "boottime", false);

	nscheck();

	अगर (unshare_समयns())
		वापस 1;

	nsfd = खोलो("/proc/self/ns/time_for_children", O_RDONLY);
	अगर (nsfd < 0)
		वापस pr_लिखो_त्रुटि("Can't open a time namespace");

	अगर (_समय_रखो(CLOCK_MONOTONIC, offset))
		वापस 1;
	अगर (_समय_रखो(CLOCK_BOOTTIME, offset))
		वापस 1;

	अगर (setns(nsfd, CLONE_NEWTIME))
		वापस pr_लिखो_त्रुटि("setns");

	test(CLOCK_MONOTONIC, "monotonic", true);
	test(CLOCK_MONOTONIC_COARSE, "monotonic-coarse", true);
	test(CLOCK_MONOTONIC_RAW, "monotonic-raw", true);
	test(CLOCK_BOOTTIME, "boottime", true);

	ksft_निकास_pass();
	वापस 0;
पूर्ण
