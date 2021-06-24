<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

/*
 * Context चयन microbenchmark.
 *
 * Copyright 2018, Anton Blanअक्षरd, IBM Corp.
 */

#घोषणा _GNU_SOURCE
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <getopt.h>
#समावेश <सीमा.स>
#समावेश <linux/futex.h>
#समावेश <pthपढ़ो.h>
#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/shm.h>
#समावेश <sys/syscall.h>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

अटल अचिन्हित पूर्णांक समयout = 30;

अटल व्योम set_cpu(पूर्णांक cpu)
अणु
	cpu_set_t cpuset;

	अगर (cpu == -1)
		वापस;

	CPU_ZERO(&cpuset);
	CPU_SET(cpu, &cpuset);

	अगर (sched_setaffinity(0, माप(cpuset), &cpuset)) अणु
		लिखो_त्रुटि("sched_setaffinity");
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम start_process_on(व्योम *(*fn)(व्योम *), व्योम *arg, पूर्णांक cpu)
अणु
	पूर्णांक pid;

	pid = विभाजन();
	अगर (pid == -1) अणु
		लिखो_त्रुटि("fork");
		निकास(1);
	पूर्ण

	अगर (pid)
		वापस;

	set_cpu(cpu);

	fn(arg);

	निकास(0);
पूर्ण

अटल पूर्णांक cpu;
अटल पूर्णांक करो_विभाजन = 0;
अटल पूर्णांक करो_vविभाजन = 0;
अटल पूर्णांक करो_exec = 0;
अटल अक्षर *exec_file;
अटल पूर्णांक exec_target = 0;
अटल अचिन्हित दीर्घ iterations;
अटल अचिन्हित दीर्घ iterations_prev;

अटल व्योम run_exec(व्योम)
अणु
	अक्षर *स्थिर argv[] = अणु "./exec_target", शून्य पूर्ण;

	अगर (execve("./exec_target", argv, शून्य) == -1) अणु
		लिखो_त्रुटि("execve");
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम bench_विभाजन(व्योम)
अणु
	जबतक (1) अणु
		pid_t pid = विभाजन();
		अगर (pid == -1) अणु
			लिखो_त्रुटि("fork");
			निकास(1);
		पूर्ण
		अगर (pid == 0) अणु
			अगर (करो_exec)
				run_exec();
			_निकास(0);
		पूर्ण
		pid = रुकोpid(pid, शून्य, 0);
		अगर (pid == -1) अणु
			लिखो_त्रुटि("waitpid");
			निकास(1);
		पूर्ण
		iterations++;
	पूर्ण
पूर्ण

अटल व्योम bench_vविभाजन(व्योम)
अणु
	जबतक (1) अणु
		pid_t pid = vविभाजन();
		अगर (pid == -1) अणु
			लिखो_त्रुटि("fork");
			निकास(1);
		पूर्ण
		अगर (pid == 0) अणु
			अगर (करो_exec)
				run_exec();
			_निकास(0);
		पूर्ण
		pid = रुकोpid(pid, शून्य, 0);
		अगर (pid == -1) अणु
			लिखो_त्रुटि("waitpid");
			निकास(1);
		पूर्ण
		iterations++;
	पूर्ण
पूर्ण

अटल व्योम *null_fn(व्योम *arg)
अणु
	pthपढ़ो_निकास(शून्य);
पूर्ण

अटल व्योम bench_thपढ़ो(व्योम)
अणु
	pthपढ़ो_t tid;
	cpu_set_t cpuset;
	pthपढ़ो_attr_t attr;
	पूर्णांक rc;

	rc = pthपढ़ो_attr_init(&attr);
	अगर (rc) अणु
		त्रुटि_सं = rc;
		लिखो_त्रुटि("pthread_attr_init");
		निकास(1);
	पूर्ण

	अगर (cpu != -1) अणु
		CPU_ZERO(&cpuset);
		CPU_SET(cpu, &cpuset);

		rc = pthपढ़ो_attr_setaffinity_np(&attr, माप(cpu_set_t), &cpuset);
		अगर (rc) अणु
			त्रुटि_सं = rc;
			लिखो_त्रुटि("pthread_attr_setaffinity_np");
			निकास(1);
		पूर्ण
	पूर्ण

	जबतक (1) अणु
		rc = pthपढ़ो_create(&tid, &attr, null_fn, शून्य);
		अगर (rc) अणु
			त्रुटि_सं = rc;
			लिखो_त्रुटि("pthread_create");
			निकास(1);
		पूर्ण
		rc = pthपढ़ो_join(tid, शून्य);
		अगर (rc) अणु
			त्रुटि_सं = rc;
			लिखो_त्रुटि("pthread_join");
			निकास(1);
		पूर्ण
		iterations++;
	पूर्ण
पूर्ण

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

अटल व्योम *bench_proc(व्योम *arg)
अणु
	संकेत(SIGALRM, sigalrm_handler);
	alarm(1);

	अगर (करो_विभाजन)
		bench_विभाजन();
	अन्यथा अगर (करो_vविभाजन)
		bench_vविभाजन();
	अन्यथा
		bench_thपढ़ो();

	वापस शून्य;
पूर्ण

अटल काष्ठा option options[] = अणु
	अणु "fork", no_argument, &करो_विभाजन, 1 पूर्ण,
	अणु "vfork", no_argument, &करो_vविभाजन, 1 पूर्ण,
	अणु "exec", no_argument, &करो_exec, 1 पूर्ण,
	अणु "timeout", required_argument, 0, 's' पूर्ण,
	अणु "exec-target", no_argument, &exec_target, 1 पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल व्योम usage(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "Usage: fork <options> CPU\n\n");
	ख_लिखो(मानक_त्रुटि, "\t\t--fork\tUse fork() (default threads)\n");
	ख_लिखो(मानक_त्रुटि, "\t\t--vfork\tUse vfork() (default threads)\n");
	ख_लिखो(मानक_त्रुटि, "\t\t--exec\tAlso exec() (default no exec)\n");
	ख_लिखो(मानक_त्रुटि, "\t\t--timeout=X\tDuration in seconds to run (default 30)\n");
	ख_लिखो(मानक_त्रुटि, "\t\t--exec-target\tInternal option for exec workload\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	चिन्हित अक्षर c;

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

		हाल 's':
			समयout = म_से_प(optarg);
			अवरोध;

		शेष:
			usage();
			निकास(1);
		पूर्ण
	पूर्ण

	अगर (करो_विभाजन && करो_vविभाजन) अणु
		usage();
		निकास(1);
	पूर्ण
	अगर (करो_exec && !करो_विभाजन && !करो_vविभाजन) अणु
		usage();
		निकास(1);
	पूर्ण

	अगर (करो_exec) अणु
		अक्षर *स_नाम = strdup(argv[0]);
		पूर्णांक i;
		i = म_माप(स_नाम) - 1;
		जबतक (i) अणु
			अगर (स_नाम[i] == '/') अणु
				स_नाम[i] = '\0';
				अगर (स_बदलो(स_नाम) == -1) अणु
					लिखो_त्रुटि("chdir");
					निकास(1);
				पूर्ण
				अवरोध;
			पूर्ण
			i--;
		पूर्ण
	पूर्ण

	अगर (exec_target) अणु
		निकास(0);
	पूर्ण

	अगर (((argc - optind) != 1)) अणु
		cpu = -1;
	पूर्ण अन्यथा अणु
		cpu = म_से_प(argv[optind++]);
	पूर्ण

	अगर (करो_exec)
		exec_file = argv[0];

	set_cpu(cpu);

	म_लिखो("Using ");
	अगर (करो_विभाजन)
		म_लिखो("fork");
	अन्यथा अगर (करो_vविभाजन)
		म_लिखो("vfork");
	अन्यथा
		म_लिखो("clone");

	अगर (करो_exec)
		म_लिखो(" + exec");

	म_लिखो(" on cpu %d\n", cpu);

	/* Create a new process group so we can संकेत everyone क्रम निकास */
	setpgid(getpid(), getpid());

	संकेत(SIGUSR1, sigusr1_handler);

	start_process_on(bench_proc, शून्य, cpu);

	जबतक (1)
		sleep(3600);

	वापस 0;
पूर्ण
