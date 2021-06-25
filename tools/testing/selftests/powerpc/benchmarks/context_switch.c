<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Context चयन microbenchmark.
 *
 * Copyright (C) 2015 Anton Blanअक्षरd <anton@au.ibm.com>, IBM
 */

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <sched.h>
#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <getopt.h>
#समावेश <संकेत.स>
#समावेश <निश्चित.स>
#समावेश <pthपढ़ो.h>
#समावेश <सीमा.स>
#समावेश <sys/समय.स>
#समावेश <sys/syscall.h>
#समावेश <sys/sysinfo.h>
#समावेश <sys/types.h>
#समावेश <sys/shm.h>
#समावेश <linux/futex.h>
#अगर_घोषित __घातerpc__
#समावेश <altivec.h>
#पूर्ण_अगर
#समावेश "utils.h"

अटल अचिन्हित पूर्णांक समयout = 30;

अटल पूर्णांक touch_vdso;
काष्ठा समयval tv;

अटल पूर्णांक touch_fp = 1;
द्विगुन fp;

अटल पूर्णांक touch_vector = 1;
vector पूर्णांक a, b, c;

#अगर_घोषित __घातerpc__
अटल पूर्णांक touch_altivec = 1;

/*
 * Note: LTO (Link Time Optimisation) करोesn't play well with this function
 * attribute. Be very careful enabling LTO क्रम this test.
 */
अटल व्योम __attribute__((__target__("no-vsx"))) altivec_touch_fn(व्योम)
अणु
	c = a + b;
पूर्ण
#पूर्ण_अगर

अटल व्योम touch(व्योम)
अणु
	अगर (touch_vdso)
		समय_लोofday(&tv, शून्य);

	अगर (touch_fp)
		fp += 0.1;

#अगर_घोषित __घातerpc__
	अगर (touch_altivec)
		altivec_touch_fn();
#पूर्ण_अगर

	अगर (touch_vector)
		c = a + b;

	यंत्र अस्थिर("# %0 %1 %2": : "r"(&tv), "r"(&fp), "r"(&c));
पूर्ण

अटल व्योम start_thपढ़ो_on(व्योम *(*fn)(व्योम *), व्योम *arg, अचिन्हित दीर्घ cpu)
अणु
	पूर्णांक rc;
	pthपढ़ो_t tid;
	cpu_set_t cpuset;
	pthपढ़ो_attr_t attr;

	CPU_ZERO(&cpuset);
	CPU_SET(cpu, &cpuset);

	rc = pthपढ़ो_attr_init(&attr);
	अगर (rc) अणु
		त्रुटि_सं = rc;
		लिखो_त्रुटि("pthread_attr_init");
		निकास(1);
	पूर्ण

	rc = pthपढ़ो_attr_setaffinity_np(&attr, माप(cpu_set_t), &cpuset);
	अगर (rc)	अणु
		त्रुटि_सं = rc;
		लिखो_त्रुटि("pthread_attr_setaffinity_np");
		निकास(1);
	पूर्ण

	rc = pthपढ़ो_create(&tid, &attr, fn, arg);
	अगर (rc) अणु
		त्रुटि_सं = rc;
		लिखो_त्रुटि("pthread_create");
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम start_process_on(व्योम *(*fn)(व्योम *), व्योम *arg, अचिन्हित दीर्घ cpu)
अणु
	पूर्णांक pid, ncpus;
	cpu_set_t *cpuset;
	माप_प्रकार size;

	pid = विभाजन();
	अगर (pid == -1) अणु
		लिखो_त्रुटि("fork");
		निकास(1);
	पूर्ण

	अगर (pid)
		वापस;

	ncpus = get_nprocs();
	size = CPU_ALLOC_SIZE(ncpus);
	cpuset = CPU_ALLOC(ncpus);
	अगर (!cpuset) अणु
		लिखो_त्रुटि("malloc");
		निकास(1);
	पूर्ण
	CPU_ZERO_S(size, cpuset);
	CPU_SET_S(cpu, size, cpuset);

	अगर (sched_setaffinity(0, size, cpuset)) अणु
		लिखो_त्रुटि("sched_setaffinity");
		CPU_FREE(cpuset);
		निकास(1);
	पूर्ण

	CPU_FREE(cpuset);
	fn(arg);

	निकास(0);
पूर्ण

अटल अचिन्हित दीर्घ iterations;
अटल अचिन्हित दीर्घ iterations_prev;

अटल व्योम sigalrm_handler(पूर्णांक junk)
अणु
	अचिन्हित दीर्घ i = iterations;

	म_लिखो("%ld\n", i - iterations_prev);
	iterations_prev = i;

	अगर (--समयout == 0)
		समाप्त(0, SIGUSR1);

	alarm(1);
पूर्ण

अटल व्योम sigusr1_handler(पूर्णांक junk)
अणु
	निकास(0);
पूर्ण

काष्ठा actions अणु
	व्योम (*setup)(पूर्णांक, पूर्णांक);
	व्योम *(*thपढ़ो1)(व्योम *);
	व्योम *(*thपढ़ो2)(व्योम *);
पूर्ण;

#घोषणा READ 0
#घोषणा WRITE 1

अटल पूर्णांक pipe_fd1[2];
अटल पूर्णांक pipe_fd2[2];

अटल व्योम pipe_setup(पूर्णांक cpu1, पूर्णांक cpu2)
अणु
	अगर (pipe(pipe_fd1) || pipe(pipe_fd2))
		निकास(1);
पूर्ण

अटल व्योम *pipe_thपढ़ो1(व्योम *arg)
अणु
	संकेत(SIGALRM, sigalrm_handler);
	alarm(1);

	जबतक (1) अणु
		निश्चित(पढ़ो(pipe_fd1[READ], &c, 1) == 1);
		touch();

		निश्चित(ग_लिखो(pipe_fd2[WRITE], &c, 1) == 1);
		touch();

		iterations += 2;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *pipe_thपढ़ो2(व्योम *arg)
अणु
	जबतक (1) अणु
		निश्चित(ग_लिखो(pipe_fd1[WRITE], &c, 1) == 1);
		touch();

		निश्चित(पढ़ो(pipe_fd2[READ], &c, 1) == 1);
		touch();
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा actions pipe_actions = अणु
	.setup = pipe_setup,
	.thपढ़ो1 = pipe_thपढ़ो1,
	.thपढ़ो2 = pipe_thपढ़ो2,
पूर्ण;

अटल व्योम yield_setup(पूर्णांक cpu1, पूर्णांक cpu2)
अणु
	अगर (cpu1 != cpu2) अणु
		ख_लिखो(मानक_त्रुटि, "Both threads must be on the same CPU for yield test\n");
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम *yield_thपढ़ो1(व्योम *arg)
अणु
	संकेत(SIGALRM, sigalrm_handler);
	alarm(1);

	जबतक (1) अणु
		sched_yield();
		touch();

		iterations += 2;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *yield_thपढ़ो2(व्योम *arg)
अणु
	जबतक (1) अणु
		sched_yield();
		touch();
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा actions yield_actions = अणु
	.setup = yield_setup,
	.thपढ़ो1 = yield_thपढ़ो1,
	.thपढ़ो2 = yield_thपढ़ो2,
पूर्ण;

अटल दीर्घ sys_futex(व्योम *addr1, पूर्णांक op, पूर्णांक val1, काष्ठा बारpec *समयout,
		      व्योम *addr2, पूर्णांक val3)
अणु
	वापस syscall(SYS_futex, addr1, op, val1, समयout, addr2, val3);
पूर्ण

अटल अचिन्हित दीर्घ cmpxchg(अचिन्हित दीर्घ *p, अचिन्हित दीर्घ expected,
			     अचिन्हित दीर्घ desired)
अणु
	अचिन्हित दीर्घ exp = expected;

	__atomic_compare_exchange_n(p, &exp, desired, 0,
				    __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
	वापस exp;
पूर्ण

अटल अचिन्हित दीर्घ xchg(अचिन्हित दीर्घ *p, अचिन्हित दीर्घ val)
अणु
	वापस __atomic_exchange_n(p, val, __ATOMIC_SEQ_CST);
पूर्ण

अटल पूर्णांक processes;

अटल पूर्णांक mutex_lock(अचिन्हित दीर्घ *m)
अणु
	पूर्णांक c;
	पूर्णांक flags = FUTEX_WAIT;
	अगर (!processes)
		flags |= FUTEX_PRIVATE_FLAG;

	c = cmpxchg(m, 0, 1);
	अगर (!c)
		वापस 0;

	अगर (c == 1)
		c = xchg(m, 2);

	जबतक (c) अणु
		sys_futex(m, flags, 2, शून्य, शून्य, 0);
		c = xchg(m, 2);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mutex_unlock(अचिन्हित दीर्घ *m)
अणु
	पूर्णांक flags = FUTEX_WAKE;
	अगर (!processes)
		flags |= FUTEX_PRIVATE_FLAG;

	अगर (*m == 2)
		*m = 0;
	अन्यथा अगर (xchg(m, 0) == 1)
		वापस 0;

	sys_futex(m, flags, 1, शून्य, शून्य, 0);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ *m1, *m2;

अटल व्योम futex_setup(पूर्णांक cpu1, पूर्णांक cpu2)
अणु
	अगर (!processes) अणु
		अटल अचिन्हित दीर्घ _m1, _m2;
		m1 = &_m1;
		m2 = &_m2;
	पूर्ण अन्यथा अणु
		पूर्णांक shmid;
		व्योम *shmaddr;

		shmid = shmget(IPC_PRIVATE, getpagesize(), SHM_R | SHM_W);
		अगर (shmid < 0) अणु
			लिखो_त्रुटि("shmget");
			निकास(1);
		पूर्ण

		shmaddr = shmat(shmid, शून्य, 0);
		अगर (shmaddr == (अक्षर *)-1) अणु
			लिखो_त्रुटि("shmat");
			shmctl(shmid, IPC_RMID, शून्य);
			निकास(1);
		पूर्ण

		shmctl(shmid, IPC_RMID, शून्य);

		m1 = shmaddr;
		m2 = shmaddr + माप(*m1);
	पूर्ण

	*m1 = 0;
	*m2 = 0;

	mutex_lock(m1);
	mutex_lock(m2);
पूर्ण

अटल व्योम *futex_thपढ़ो1(व्योम *arg)
अणु
	संकेत(SIGALRM, sigalrm_handler);
	alarm(1);

	जबतक (1) अणु
		mutex_lock(m2);
		mutex_unlock(m1);

		iterations += 2;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *futex_thपढ़ो2(व्योम *arg)
अणु
	जबतक (1) अणु
		mutex_unlock(m2);
		mutex_lock(m1);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा actions futex_actions = अणु
	.setup = futex_setup,
	.thपढ़ो1 = futex_thपढ़ो1,
	.thपढ़ो2 = futex_thपढ़ो2,
पूर्ण;

अटल काष्ठा option options[] = अणु
	अणु "test", required_argument, 0, 't' पूर्ण,
	अणु "process", no_argument, &processes, 1 पूर्ण,
	अणु "timeout", required_argument, 0, 's' पूर्ण,
	अणु "vdso", no_argument, &touch_vdso, 1 पूर्ण,
	अणु "no-fp", no_argument, &touch_fp, 0 पूर्ण,
#अगर_घोषित __घातerpc__
	अणु "no-altivec", no_argument, &touch_altivec, 0 पूर्ण,
#पूर्ण_अगर
	अणु "no-vector", no_argument, &touch_vector, 0 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

अटल व्योम usage(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "Usage: context_switch2 <options> CPU1 CPU2\n\n");
	ख_लिखो(मानक_त्रुटि, "\t\t--test=X\tpipe, futex or yield (default)\n");
	ख_लिखो(मानक_त्रुटि, "\t\t--process\tUse processes (default threads)\n");
	ख_लिखो(मानक_त्रुटि, "\t\t--timeout=X\tDuration in seconds to run (default 30)\n");
	ख_लिखो(मानक_त्रुटि, "\t\t--vdso\t\ttouch VDSO\n");
	ख_लिखो(मानक_त्रुटि, "\t\t--no-fp\t\tDon't touch FP\n");
#अगर_घोषित __घातerpc__
	ख_लिखो(मानक_त्रुटि, "\t\t--no-altivec\tDon't touch altivec\n");
#पूर्ण_अगर
	ख_लिखो(मानक_त्रुटि, "\t\t--no-vector\tDon't touch vector\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	चिन्हित अक्षर c;
	काष्ठा actions *actions = &yield_actions;
	पूर्णांक cpu1;
	पूर्णांक cpu2;
	अटल व्योम (*start_fn)(व्योम *(*fn)(व्योम *), व्योम *arg, अचिन्हित दीर्घ cpu);

	जबतक (1) अणु
		पूर्णांक option_index = 0;

		c = getopt_दीर्घ(argc, argv, "", options, &option_index);

		अगर (c == -1)
			अवरोध;

		चयन (c) अणु
		हाल 0:
			अगर (options[option_index].flag != 0)
				अवरोध;

			usage();
			निकास(1);
			अवरोध;

		हाल 't':
			अगर (!म_भेद(optarg, "pipe")) अणु
				actions = &pipe_actions;
			पूर्ण अन्यथा अगर (!म_भेद(optarg, "yield")) अणु
				actions = &yield_actions;
			पूर्ण अन्यथा अगर (!म_भेद(optarg, "futex")) अणु
				actions = &futex_actions;
			पूर्ण अन्यथा अणु
				usage();
				निकास(1);
			पूर्ण
			अवरोध;

		हाल 's':
			समयout = म_से_प(optarg);
			अवरोध;

		शेष:
			usage();
			निकास(1);
		पूर्ण
	पूर्ण

	अगर (processes)
		start_fn = start_process_on;
	अन्यथा
		start_fn = start_thपढ़ो_on;

	अगर (((argc - optind) != 2)) अणु
		cpu1 = cpu2 = pick_online_cpu();
	पूर्ण अन्यथा अणु
		cpu1 = म_से_प(argv[optind++]);
		cpu2 = म_से_प(argv[optind++]);
	पूर्ण

	म_लिखो("Using %s with ", processes ? "processes" : "threads");

	अगर (actions == &pipe_actions)
		म_लिखो("pipe");
	अन्यथा अगर (actions == &yield_actions)
		म_लिखो("yield");
	अन्यथा
		म_लिखो("futex");

	अगर (!have_hwcap(PPC_FEATURE_HAS_ALTIVEC))
		touch_altivec = 0;

	अगर (!have_hwcap(PPC_FEATURE_HAS_VSX))
		touch_vector = 0;

	म_लिखो(" on cpus %d/%d touching FP:%s altivec:%s vector:%s vdso:%s\n",
	       cpu1, cpu2, touch_fp ?  "yes" : "no", touch_altivec ? "yes" : "no",
	       touch_vector ? "yes" : "no", touch_vdso ? "yes" : "no");

	/* Create a new process group so we can संकेत everyone क्रम निकास */
	setpgid(getpid(), getpid());

	संकेत(SIGUSR1, sigusr1_handler);

	actions->setup(cpu1, cpu2);

	start_fn(actions->thपढ़ो1, शून्य, cpu1);
	start_fn(actions->thपढ़ो2, शून्य, cpu2);

	जबतक (1)
		sleep(3600);

	वापस 0;
पूर्ण
