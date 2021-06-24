<शैली गुरु>
/*
 * Strictly speaking, this is not a test. But it can report during test
 * runs so relative perक्रमmace can be measured.
 */
#घोषणा _GNU_SOURCE
#समावेश <निश्चित.स>
#समावेश <सीमा.स>
#समावेश <stdbool.h>
#समावेश <मानकघोष.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <समय.स>
#समावेश <unistd.h>
#समावेश <linux/filter.h>
#समावेश <linux/seccomp.h>
#समावेश <sys/param.h>
#समावेश <sys/prctl.h>
#समावेश <sys/syscall.h>
#समावेश <sys/types.h>

#घोषणा ARRAY_SIZE(a)    (माप(a) / माप(a[0]))

अचिन्हित दीर्घ दीर्घ timing(घड़ीid_t clk_id, अचिन्हित दीर्घ दीर्घ samples)
अणु
	काष्ठा बारpec start, finish;
	अचिन्हित दीर्घ दीर्घ i;
	pid_t pid, ret;

	pid = getpid();
	निश्चित(घड़ी_समय_लो(clk_id, &start) == 0);
	क्रम (i = 0; i < samples; i++) अणु
		ret = syscall(__NR_getpid);
		निश्चित(pid == ret);
	पूर्ण
	निश्चित(घड़ी_समय_लो(clk_id, &finish) == 0);

	i = finish.tv_sec - start.tv_sec;
	i *= 1000000000ULL;
	i += finish.tv_nsec - start.tv_nsec;

	म_लिखो("%lu.%09lu - %lu.%09lu = %llu (%.1fs)\n",
		finish.tv_sec, finish.tv_nsec,
		start.tv_sec, start.tv_nsec,
		i, (द्विगुन)i / 1000000000.0);

	वापस i;
पूर्ण

अचिन्हित दीर्घ दीर्घ calibrate(व्योम)
अणु
	काष्ठा बारpec start, finish;
	अचिन्हित दीर्घ दीर्घ i, samples, step = 9973;
	pid_t pid, ret;
	पूर्णांक seconds = 15;

	म_लिखो("Calibrating sample size for %d seconds worth of syscalls ...\n", seconds);

	samples = 0;
	pid = getpid();
	निश्चित(घड़ी_समय_लो(CLOCK_MONOTONIC, &start) == 0);
	करो अणु
		क्रम (i = 0; i < step; i++) अणु
			ret = syscall(__NR_getpid);
			निश्चित(pid == ret);
		पूर्ण
		निश्चित(घड़ी_समय_लो(CLOCK_MONOTONIC, &finish) == 0);

		samples += step;
		i = finish.tv_sec - start.tv_sec;
		i *= 1000000000ULL;
		i += finish.tv_nsec - start.tv_nsec;
	पूर्ण जबतक (i < 1000000000ULL);

	वापस samples * seconds;
पूर्ण

bool approx(पूर्णांक i_one, पूर्णांक i_two)
अणु
	द्विगुन one = i_one, one_bump = one * 0.01;
	द्विगुन two = i_two, two_bump = two * 0.01;

	one_bump = one + MAX(one_bump, 2.0);
	two_bump = two + MAX(two_bump, 2.0);

	/* Equal to, or within 1% or 2 digits */
	अगर (one == two ||
	    (one > two && one <= two_bump) ||
	    (two > one && two <= one_bump))
		वापस true;
	वापस false;
पूर्ण

bool le(पूर्णांक i_one, पूर्णांक i_two)
अणु
	अगर (i_one <= i_two)
		वापस true;
	वापस false;
पूर्ण

दीर्घ compare(स्थिर अक्षर *name_one, स्थिर अक्षर *name_eval, स्थिर अक्षर *name_two,
	     अचिन्हित दीर्घ दीर्घ one, bool (*eval)(पूर्णांक, पूर्णांक), अचिन्हित दीर्घ दीर्घ two)
अणु
	bool good;

	म_लिखो("\t%s %s %s (%lld %s %lld): ", name_one, name_eval, name_two,
	       (दीर्घ दीर्घ)one, name_eval, (दीर्घ दीर्घ)two);
	अगर (one > पूर्णांक_उच्च) अणु
		म_लिखो("Miscalculation! Measurement went negative: %lld\n", (दीर्घ दीर्घ)one);
		वापस 1;
	पूर्ण
	अगर (two > पूर्णांक_उच्च) अणु
		म_लिखो("Miscalculation! Measurement went negative: %lld\n", (दीर्घ दीर्घ)two);
		वापस 1;
	पूर्ण

	good = eval(one, two);
	म_लिखो("%s\n", good ? "ैoच" : "ै");

	वापस good ? 0 : 1;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा sock_filter biपंचांगap_filter[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS, दुरत्व(काष्ठा seccomp_data, nr)),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog biपंचांगap_prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(biपंचांगap_filter),
		.filter = biपंचांगap_filter,
	पूर्ण;
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS, दुरत्व(काष्ठा seccomp_data, args[0])),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;

	दीर्घ ret, bits;
	अचिन्हित दीर्घ दीर्घ samples, calc;
	अचिन्हित दीर्घ दीर्घ native, filter1, filter2, biपंचांगap1, biपंचांगap2;
	अचिन्हित दीर्घ दीर्घ entry, per_filter1, per_filter2;

	म_लिखो("Current BPF sysctl settings:\n");
	प्रणाली("sysctl net.core.bpf_jit_enable");
	प्रणाली("sysctl net.core.bpf_jit_harden");

	अगर (argc > 1)
		samples = म_से_अदीर्घl(argv[1], शून्य, 0);
	अन्यथा
		samples = calibrate();

	म_लिखो("Benchmarking %llu syscalls...\n", samples);

	/* Native call */
	native = timing(CLOCK_PROCESS_CPUTIME_ID, samples) / samples;
	म_लिखो("getpid native: %llu ns\n", native);

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	निश्चित(ret == 0);

	/* One filter resulting in a biपंचांगap */
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &biपंचांगap_prog);
	निश्चित(ret == 0);

	biपंचांगap1 = timing(CLOCK_PROCESS_CPUTIME_ID, samples) / samples;
	म_लिखो("getpid RET_ALLOW 1 filter (bitmap): %llu ns\n", biपंचांगap1);

	/* Second filter resulting in a biपंचांगap */
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &biपंचांगap_prog);
	निश्चित(ret == 0);

	biपंचांगap2 = timing(CLOCK_PROCESS_CPUTIME_ID, samples) / samples;
	म_लिखो("getpid RET_ALLOW 2 filters (bitmap): %llu ns\n", biपंचांगap2);

	/* Third filter, can no दीर्घer be converted to biपंचांगap */
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog);
	निश्चित(ret == 0);

	filter1 = timing(CLOCK_PROCESS_CPUTIME_ID, samples) / samples;
	म_लिखो("getpid RET_ALLOW 3 filters (full): %llu ns\n", filter1);

	/* Fourth filter, can not be converted to biपंचांगap because of filter 3 */
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &biपंचांगap_prog);
	निश्चित(ret == 0);

	filter2 = timing(CLOCK_PROCESS_CPUTIME_ID, samples) / samples;
	म_लिखो("getpid RET_ALLOW 4 filters (full): %llu ns\n", filter2);

	/* Estimations */
#घोषणा ESTIMATE(fmt, var, what)	करो अणु			\
		var = (what);					\
		म_लिखो("Estimated " fmt ": %llu ns\n", var);	\
		अगर (var > पूर्णांक_उच्च)				\
			जाओ more_samples;			\
	पूर्ण जबतक (0)

	ESTIMATE("total seccomp overhead for 1 bitmapped filter", calc,
		 biपंचांगap1 - native);
	ESTIMATE("total seccomp overhead for 2 bitmapped filters", calc,
		 biपंचांगap2 - native);
	ESTIMATE("total seccomp overhead for 3 full filters", calc,
		 filter1 - native);
	ESTIMATE("total seccomp overhead for 4 full filters", calc,
		 filter2 - native);
	ESTIMATE("seccomp entry overhead", entry,
		 biपंचांगap1 - native - (biपंचांगap2 - biपंचांगap1));
	ESTIMATE("seccomp per-filter overhead (last 2 diff)", per_filter1,
		 filter2 - filter1);
	ESTIMATE("seccomp per-filter overhead (filters / 4)", per_filter2,
		 (filter2 - native - entry) / 4);

	म_लिखो("Expectations:\n");
	ret |= compare("native", "ै	अ", "1 bitmap", native, le, biपंचांगap1);
	bits = compare("native", "ै	अ", "1 filter", native, le, filter1);
	अगर (bits)
		जाओ more_samples;

	ret |= compare("per-filter (last 2 diff)", "ै	", "per-filter (filters / 4)",
			per_filter1, approx, per_filter2);

	bits = compare("1 bitmapped", "ै	", "2 bitmapped",
			biपंचांगap1 - native, approx, biपंचांगap2 - native);
	अगर (bits) अणु
		म_लिखो("Skipping constant action bitmap expectations: they appear unsupported.\n");
		जाओ out;
	पूर्ण

	ret |= compare("entry", "ै	", "1 bitmapped", entry, approx, biपंचांगap1 - native);
	ret |= compare("entry", "ै	", "2 bitmapped", entry, approx, biपंचांगap2 - native);
	ret |= compare("native + entry + (per filter * 4)", "ै	", "4 filters total",
			entry + (per_filter1 * 4) + native, approx, filter2);
	अगर (ret == 0)
		जाओ out;

more_samples:
	म_लिखो("Saw unexpected benchmark result. Try running again with more samples?\n");
out:
	वापस 0;
पूर्ण
