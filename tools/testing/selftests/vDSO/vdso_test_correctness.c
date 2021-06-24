<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ldt_gdt.c - Test हालs क्रम LDT and GDT access
 * Copyright (c) 2011-2015 Andrew Lutomirski
 */

#घोषणा _GNU_SOURCE

#समावेश <मानकपन.स>
#समावेश <sys/समय.स>
#समावेश <समय.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <sys/syscall.h>
#समावेश <dlfcn.h>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <sched.h>
#समावेश <stdbool.h>
#समावेश <सीमा.स>

#समावेश "vdso_config.h"

अटल स्थिर अक्षर **name;

#अगर_अघोषित SYS_अ_लोpu
# अगरdef __x86_64__
#  define SYS_अ_लोpu 309
# अन्यथा
#  define SYS_अ_लोpu 318
# endअगर
#पूर्ण_अगर

#अगर_अघोषित __NR_घड़ी_समय_लो64
#घोषणा __NR_घड़ी_समय_लो64	403
#पूर्ण_अगर

#अगर_अघोषित __kernel_बारpec
काष्ठा __kernel_बारpec अणु
	दीर्घ दीर्घ	tv_sec;
	दीर्घ दीर्घ	tv_nsec;
पूर्ण;
#पूर्ण_अगर

/* max length of lines in /proc/self/maps - anything दीर्घer is skipped here */
#घोषणा MAPS_LINE_LEN 128

पूर्णांक nerrs = 0;

प्रकार पूर्णांक (*vसमय_लो_t)(घड़ीid_t, काष्ठा बारpec *);

vसमय_लो_t vdso_घड़ी_समय_लो;

प्रकार पूर्णांक (*vसमय_लो64_t)(घड़ीid_t, काष्ठा __kernel_बारpec *);

vसमय_लो64_t vdso_घड़ी_समय_लो64;

प्रकार दीर्घ (*vgtod_t)(काष्ठा समयval *tv, काष्ठा समयzone *tz);

vgtod_t vdso_समय_लोofday;

प्रकार दीर्घ (*अ_लोpu_t)(अचिन्हित *, अचिन्हित *, व्योम *);

अ_लोpu_t vअ_लोpu;
अ_लोpu_t vdso_अ_लोpu;

अटल व्योम *vsyscall_अ_लोpu(व्योम)
अणु
#अगर_घोषित __x86_64__
	खाता *maps;
	अक्षर line[MAPS_LINE_LEN];
	bool found = false;

	maps = ख_खोलो("/proc/self/maps", "r");
	अगर (!maps) /* might still be present, but ignore it here, as we test vDSO not vsyscall */
		वापस शून्य;

	जबतक (ख_माला_लो(line, MAPS_LINE_LEN, maps)) अणु
		अक्षर r, x;
		व्योम *start, *end;
		अक्षर name[MAPS_LINE_LEN];

		/* माला_पूछो() is safe here as म_माप(name) >= म_माप(line) */
		अगर (माला_पूछो(line, "%p-%p %c-%cp %*x %*x:%*x %*u %s",
			   &start, &end, &r, &x, name) != 5)
			जारी;

		अगर (म_भेद(name, "[vsyscall]"))
			जारी;

		/* assume entries are OK, as we test vDSO here not vsyscall */
		found = true;
		अवरोध;
	पूर्ण

	ख_बंद(maps);

	अगर (!found) अणु
		म_लिखो("Warning: failed to find vsyscall getcpu\n");
		वापस शून्य;
	पूर्ण
	वापस (व्योम *) (0xffffffffff600800);
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण


अटल व्योम fill_function_poपूर्णांकers()
अणु
	व्योम *vdso = dlखोलो("linux-vdso.so.1",
			    RTLD_LAZY | RTLD_LOCAL | RTLD_NOLOAD);
	अगर (!vdso)
		vdso = dlखोलो("linux-gate.so.1",
			      RTLD_LAZY | RTLD_LOCAL | RTLD_NOLOAD);
	अगर (!vdso) अणु
		म_लिखो("[WARN]\tfailed to find vDSO\n");
		वापस;
	पूर्ण

	vdso_अ_लोpu = (अ_लोpu_t)dlsym(vdso, name[4]);
	अगर (!vdso_अ_लोpu)
		म_लिखो("Warning: failed to find getcpu in vDSO\n");

	vअ_लोpu = (अ_लोpu_t) vsyscall_अ_लोpu();

	vdso_घड़ी_समय_लो = (vसमय_लो_t)dlsym(vdso, name[1]);
	अगर (!vdso_घड़ी_समय_लो)
		म_लिखो("Warning: failed to find clock_gettime in vDSO\n");

#अगर defined(VDSO_32BIT)
	vdso_घड़ी_समय_लो64 = (vसमय_लो64_t)dlsym(vdso, name[5]);
	अगर (!vdso_घड़ी_समय_लो64)
		म_लिखो("Warning: failed to find clock_gettime64 in vDSO\n");
#पूर्ण_अगर

	vdso_समय_लोofday = (vgtod_t)dlsym(vdso, name[0]);
	अगर (!vdso_समय_लोofday)
		म_लिखो("Warning: failed to find gettimeofday in vDSO\n");

पूर्ण

अटल दीर्घ sys_अ_लोpu(अचिन्हित * cpu, अचिन्हित * node,
		       व्योम* cache)
अणु
	वापस syscall(__NR_अ_लोpu, cpu, node, cache);
पूर्ण

अटल अंतरभूत पूर्णांक sys_घड़ी_समय_लो(घड़ीid_t id, काष्ठा बारpec *ts)
अणु
	वापस syscall(__NR_घड़ी_समय_लो, id, ts);
पूर्ण

अटल अंतरभूत पूर्णांक sys_घड़ी_समय_लो64(घड़ीid_t id, काष्ठा __kernel_बारpec *ts)
अणु
	वापस syscall(__NR_घड़ी_समय_लो64, id, ts);
पूर्ण

अटल अंतरभूत पूर्णांक sys_समय_लोofday(काष्ठा समयval *tv, काष्ठा समयzone *tz)
अणु
	वापस syscall(__NR_समय_लोofday, tv, tz);
पूर्ण

अटल व्योम test_अ_लोpu(व्योम)
अणु
	म_लिखो("[RUN]\tTesting getcpu...\n");

	क्रम (पूर्णांक cpu = 0; ; cpu++) अणु
		cpu_set_t cpuset;
		CPU_ZERO(&cpuset);
		CPU_SET(cpu, &cpuset);
		अगर (sched_setaffinity(0, माप(cpuset), &cpuset) != 0)
			वापस;

		अचिन्हित cpu_sys, cpu_vdso, cpu_vsys,
			node_sys, node_vdso, node_vsys;
		दीर्घ ret_sys, ret_vdso = 1, ret_vsys = 1;
		अचिन्हित node;

		ret_sys = sys_अ_लोpu(&cpu_sys, &node_sys, 0);
		अगर (vdso_अ_लोpu)
			ret_vdso = vdso_अ_लोpu(&cpu_vdso, &node_vdso, 0);
		अगर (vअ_लोpu)
			ret_vsys = vअ_लोpu(&cpu_vsys, &node_vsys, 0);

		अगर (!ret_sys)
			node = node_sys;
		अन्यथा अगर (!ret_vdso)
			node = node_vdso;
		अन्यथा अगर (!ret_vsys)
			node = node_vsys;

		bool ok = true;
		अगर (!ret_sys && (cpu_sys != cpu || node_sys != node))
			ok = false;
		अगर (!ret_vdso && (cpu_vdso != cpu || node_vdso != node))
			ok = false;
		अगर (!ret_vsys && (cpu_vsys != cpu || node_vsys != node))
			ok = false;

		म_लिखो("[%s]\tCPU %u:", ok ? "OK" : "FAIL", cpu);
		अगर (!ret_sys)
			म_लिखो(" syscall: cpu %u, node %u", cpu_sys, node_sys);
		अगर (!ret_vdso)
			म_लिखो(" vdso: cpu %u, node %u", cpu_vdso, node_vdso);
		अगर (!ret_vsys)
			म_लिखो(" vsyscall: cpu %u, node %u", cpu_vsys,
			       node_vsys);
		म_लिखो("\n");

		अगर (!ok)
			nerrs++;
	पूर्ण
पूर्ण

अटल bool ts_leq(स्थिर काष्ठा बारpec *a, स्थिर काष्ठा बारpec *b)
अणु
	अगर (a->tv_sec != b->tv_sec)
		वापस a->tv_sec < b->tv_sec;
	अन्यथा
		वापस a->tv_nsec <= b->tv_nsec;
पूर्ण

अटल bool ts64_leq(स्थिर काष्ठा __kernel_बारpec *a,
		     स्थिर काष्ठा __kernel_बारpec *b)
अणु
	अगर (a->tv_sec != b->tv_sec)
		वापस a->tv_sec < b->tv_sec;
	अन्यथा
		वापस a->tv_nsec <= b->tv_nsec;
पूर्ण

अटल bool tv_leq(स्थिर काष्ठा समयval *a, स्थिर काष्ठा समयval *b)
अणु
	अगर (a->tv_sec != b->tv_sec)
		वापस a->tv_sec < b->tv_sec;
	अन्यथा
		वापस a->tv_usec <= b->tv_usec;
पूर्ण

अटल अक्षर स्थिर * स्थिर घड़ीnames[] = अणु
	[0] = "CLOCK_REALTIME",
	[1] = "CLOCK_MONOTONIC",
	[2] = "CLOCK_PROCESS_CPUTIME_ID",
	[3] = "CLOCK_THREAD_CPUTIME_ID",
	[4] = "CLOCK_MONOTONIC_RAW",
	[5] = "CLOCK_REALTIME_COARSE",
	[6] = "CLOCK_MONOTONIC_COARSE",
	[7] = "CLOCK_BOOTTIME",
	[8] = "CLOCK_REALTIME_ALARM",
	[9] = "CLOCK_BOOTTIME_ALARM",
	[10] = "CLOCK_SGI_CYCLE",
	[11] = "CLOCK_TAI",
पूर्ण;

अटल व्योम test_one_घड़ी_समय_लो(पूर्णांक घड़ी, स्थिर अक्षर *name)
अणु
	काष्ठा बारpec start, vdso, end;
	पूर्णांक vdso_ret, end_ret;

	म_लिखो("[RUN]\tTesting clock_gettime for clock %s (%d)...\n", name, घड़ी);

	अगर (sys_घड़ी_समय_लो(घड़ी, &start) < 0) अणु
		अगर (त्रुटि_सं == EINVAL) अणु
			vdso_ret = vdso_घड़ी_समय_लो(घड़ी, &vdso);
			अगर (vdso_ret == -EINVAL) अणु
				म_लिखो("[OK]\tNo such clock.\n");
			पूर्ण अन्यथा अणु
				म_लिखो("[FAIL]\tNo such clock, but __vdso_clock_gettime returned %d\n", vdso_ret);
				nerrs++;
			पूर्ण
		पूर्ण अन्यथा अणु
			म_लिखो("[WARN]\t clock_gettime(%d) syscall returned error %d\n", घड़ी, त्रुटि_सं);
		पूर्ण
		वापस;
	पूर्ण

	vdso_ret = vdso_घड़ी_समय_लो(घड़ी, &vdso);
	end_ret = sys_घड़ी_समय_लो(घड़ी, &end);

	अगर (vdso_ret != 0 || end_ret != 0) अणु
		म_लिखो("[FAIL]\tvDSO returned %d, syscall errno=%d\n",
		       vdso_ret, त्रुटि_सं);
		nerrs++;
		वापस;
	पूर्ण

	म_लिखो("\t%llu.%09ld %llu.%09ld %llu.%09ld\n",
	       (अचिन्हित दीर्घ दीर्घ)start.tv_sec, start.tv_nsec,
	       (अचिन्हित दीर्घ दीर्घ)vdso.tv_sec, vdso.tv_nsec,
	       (अचिन्हित दीर्घ दीर्घ)end.tv_sec, end.tv_nsec);

	अगर (!ts_leq(&start, &vdso) || !ts_leq(&vdso, &end)) अणु
		म_लिखो("[FAIL]\tTimes are out of sequence\n");
		nerrs++;
		वापस;
	पूर्ण

	म_लिखो("[OK]\tTest Passed.\n");
पूर्ण

अटल व्योम test_घड़ी_समय_लो(व्योम)
अणु
	अगर (!vdso_घड़ी_समय_लो) अणु
		म_लिखो("[SKIP]\tNo vDSO, so skipping clock_gettime() tests\n");
		वापस;
	पूर्ण

	क्रम (पूर्णांक घड़ी = 0; घड़ी < माप(घड़ीnames) / माप(घड़ीnames[0]);
	     घड़ी++) अणु
		test_one_घड़ी_समय_लो(घड़ी, घड़ीnames[घड़ी]);
	पूर्ण

	/* Also test some invalid घड़ी ids */
	test_one_घड़ी_समय_लो(-1, "invalid");
	test_one_घड़ी_समय_लो(पूर्णांक_न्यून, "invalid");
	test_one_घड़ी_समय_लो(पूर्णांक_उच्च, "invalid");
पूर्ण

अटल व्योम test_one_घड़ी_समय_लो64(पूर्णांक घड़ी, स्थिर अक्षर *name)
अणु
	काष्ठा __kernel_बारpec start, vdso, end;
	पूर्णांक vdso_ret, end_ret;

	म_लिखो("[RUN]\tTesting clock_gettime64 for clock %s (%d)...\n", name, घड़ी);

	अगर (sys_घड़ी_समय_लो64(घड़ी, &start) < 0) अणु
		अगर (त्रुटि_सं == EINVAL) अणु
			vdso_ret = vdso_घड़ी_समय_लो64(घड़ी, &vdso);
			अगर (vdso_ret == -EINVAL) अणु
				म_लिखो("[OK]\tNo such clock.\n");
			पूर्ण अन्यथा अणु
				म_लिखो("[FAIL]\tNo such clock, but __vdso_clock_gettime64 returned %d\n", vdso_ret);
				nerrs++;
			पूर्ण
		पूर्ण अन्यथा अणु
			म_लिखो("[WARN]\t clock_gettime64(%d) syscall returned error %d\n", घड़ी, त्रुटि_सं);
		पूर्ण
		वापस;
	पूर्ण

	vdso_ret = vdso_घड़ी_समय_लो64(घड़ी, &vdso);
	end_ret = sys_घड़ी_समय_लो64(घड़ी, &end);

	अगर (vdso_ret != 0 || end_ret != 0) अणु
		म_लिखो("[FAIL]\tvDSO returned %d, syscall errno=%d\n",
		       vdso_ret, त्रुटि_सं);
		nerrs++;
		वापस;
	पूर्ण

	म_लिखो("\t%llu.%09lld %llu.%09lld %llu.%09lld\n",
	       (अचिन्हित दीर्घ दीर्घ)start.tv_sec, start.tv_nsec,
	       (अचिन्हित दीर्घ दीर्घ)vdso.tv_sec, vdso.tv_nsec,
	       (अचिन्हित दीर्घ दीर्घ)end.tv_sec, end.tv_nsec);

	अगर (!ts64_leq(&start, &vdso) || !ts64_leq(&vdso, &end)) अणु
		म_लिखो("[FAIL]\tTimes are out of sequence\n");
		nerrs++;
		वापस;
	पूर्ण

	म_लिखो("[OK]\tTest Passed.\n");
पूर्ण

अटल व्योम test_घड़ी_समय_लो64(व्योम)
अणु
	अगर (!vdso_घड़ी_समय_लो64) अणु
		म_लिखो("[SKIP]\tNo vDSO, so skipping clock_gettime64() tests\n");
		वापस;
	पूर्ण

	क्रम (पूर्णांक घड़ी = 0; घड़ी < माप(घड़ीnames) / माप(घड़ीnames[0]);
	     घड़ी++) अणु
		test_one_घड़ी_समय_लो64(घड़ी, घड़ीnames[घड़ी]);
	पूर्ण

	/* Also test some invalid घड़ी ids */
	test_one_घड़ी_समय_लो64(-1, "invalid");
	test_one_घड़ी_समय_लो64(पूर्णांक_न्यून, "invalid");
	test_one_घड़ी_समय_लो64(पूर्णांक_उच्च, "invalid");
पूर्ण

अटल व्योम test_समय_लोofday(व्योम)
अणु
	काष्ठा समयval start, vdso, end;
	काष्ठा समयzone sys_tz, vdso_tz;
	पूर्णांक vdso_ret, end_ret;

	अगर (!vdso_समय_लोofday)
		वापस;

	म_लिखो("[RUN]\tTesting gettimeofday...\n");

	अगर (sys_समय_लोofday(&start, &sys_tz) < 0) अणु
		म_लिखो("[FAIL]\tsys_gettimeofday failed (%d)\n", त्रुटि_सं);
		nerrs++;
		वापस;
	पूर्ण

	vdso_ret = vdso_समय_लोofday(&vdso, &vdso_tz);
	end_ret = sys_समय_लोofday(&end, शून्य);

	अगर (vdso_ret != 0 || end_ret != 0) अणु
		म_लिखो("[FAIL]\tvDSO returned %d, syscall errno=%d\n",
		       vdso_ret, त्रुटि_सं);
		nerrs++;
		वापस;
	पूर्ण

	म_लिखो("\t%llu.%06ld %llu.%06ld %llu.%06ld\n",
	       (अचिन्हित दीर्घ दीर्घ)start.tv_sec, start.tv_usec,
	       (अचिन्हित दीर्घ दीर्घ)vdso.tv_sec, vdso.tv_usec,
	       (अचिन्हित दीर्घ दीर्घ)end.tv_sec, end.tv_usec);

	अगर (!tv_leq(&start, &vdso) || !tv_leq(&vdso, &end)) अणु
		म_लिखो("[FAIL]\tTimes are out of sequence\n");
		nerrs++;
	पूर्ण

	अगर (sys_tz.tz_minuteswest == vdso_tz.tz_minuteswest &&
	    sys_tz.tz_dstसमय == vdso_tz.tz_dstसमय) अणु
		म_लिखो("[OK]\ttimezones match: minuteswest=%d, dsttime=%d\n",
		       sys_tz.tz_minuteswest, sys_tz.tz_dstसमय);
	पूर्ण अन्यथा अणु
		म_लिखो("[FAIL]\ttimezones do not match\n");
		nerrs++;
	पूर्ण

	/* And make sure that passing शून्य क्रम tz करोesn't crash. */
	vdso_समय_लोofday(&vdso, शून्य);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	name = (स्थिर अक्षर **)&names[VDSO_NAMES];

	fill_function_poपूर्णांकers();

	test_घड़ी_समय_लो();
	test_घड़ी_समय_लो64();
	test_समय_लोofday();

	/*
	 * Test अ_लोpu() last so that, अगर something goes wrong setting affinity,
	 * we still run the other tests.
	 */
	test_अ_लोpu();

	वापस nerrs ? 1 : 0;
पूर्ण
