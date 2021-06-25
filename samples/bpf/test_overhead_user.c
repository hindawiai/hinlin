<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2016 Facebook
 */
#घोषणा _GNU_SOURCE
#समावेश <sched.h>
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <sys/types.h>
#समावेश <यंत्र/unistd.h>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <निश्चित.स>
#समावेश <sys/रुको.h>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <linux/bpf.h>
#समावेश <माला.स>
#समावेश <समय.स>
#समावेश <sys/resource.h>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#घोषणा MAX_CNT 1000000

अटल काष्ठा bpf_link *links[2];
अटल काष्ठा bpf_object *obj;
अटल पूर्णांक cnt;

अटल __u64 समय_get_ns(व्योम)
अणु
	काष्ठा बारpec ts;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &ts);
	वापस ts.tv_sec * 1000000000ull + ts.tv_nsec;
पूर्ण

अटल व्योम test_task_नाम(पूर्णांक cpu)
अणु
	__u64 start_समय;
	अक्षर buf[] = "test\n";
	पूर्णांक i, fd;

	fd = खोलो("/proc/self/comm", O_WRONLY|O_TRUNC);
	अगर (fd < 0) अणु
		म_लिखो("couldn't open /proc\n");
		निकास(1);
	पूर्ण
	start_समय = समय_get_ns();
	क्रम (i = 0; i < MAX_CNT; i++) अणु
		अगर (ग_लिखो(fd, buf, माप(buf)) < 0) अणु
			म_लिखो("task rename failed: %s\n", म_त्रुटि(त्रुटि_सं));
			बंद(fd);
			वापस;
		पूर्ण
	पूर्ण
	म_लिखो("task_rename:%d: %lld events per sec\n",
	       cpu, MAX_CNT * 1000000000ll / (समय_get_ns() - start_समय));
	बंद(fd);
पूर्ण

अटल व्योम test_uअक्रमom_पढ़ो(पूर्णांक cpu)
अणु
	__u64 start_समय;
	अक्षर buf[4];
	पूर्णांक i, fd;

	fd = खोलो("/dev/urandom", O_RDONLY);
	अगर (fd < 0) अणु
		म_लिखो("couldn't open /dev/urandom\n");
		निकास(1);
	पूर्ण
	start_समय = समय_get_ns();
	क्रम (i = 0; i < MAX_CNT; i++) अणु
		अगर (पढ़ो(fd, buf, माप(buf)) < 0) अणु
			म_लिखो("failed to read from /dev/urandom: %s\n", म_त्रुटि(त्रुटि_सं));
			बंद(fd);
			वापस;
		पूर्ण
	पूर्ण
	म_लिखो("urandom_read:%d: %lld events per sec\n",
	       cpu, MAX_CNT * 1000000000ll / (समय_get_ns() - start_समय));
	बंद(fd);
पूर्ण

अटल व्योम loop(पूर्णांक cpu, पूर्णांक flags)
अणु
	cpu_set_t cpuset;

	CPU_ZERO(&cpuset);
	CPU_SET(cpu, &cpuset);
	sched_setaffinity(0, माप(cpuset), &cpuset);

	अगर (flags & 1)
		test_task_नाम(cpu);
	अगर (flags & 2)
		test_uअक्रमom_पढ़ो(cpu);
पूर्ण

अटल व्योम run_perf_test(पूर्णांक tasks, पूर्णांक flags)
अणु
	pid_t pid[tasks];
	पूर्णांक i;

	क्रम (i = 0; i < tasks; i++) अणु
		pid[i] = विभाजन();
		अगर (pid[i] == 0) अणु
			loop(i, flags);
			निकास(0);
		पूर्ण अन्यथा अगर (pid[i] == -1) अणु
			म_लिखो("couldn't spawn #%d process\n", i);
			निकास(1);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < tasks; i++) अणु
		पूर्णांक status;

		निश्चित(रुकोpid(pid[i], &status, 0) == pid[i]);
		निश्चित(status == 0);
	पूर्ण
पूर्ण

अटल पूर्णांक load_progs(अक्षर *filename)
अणु
	काष्ठा bpf_program *prog;
	पूर्णांक err = 0;

	obj = bpf_object__खोलो_file(filename, शून्य);
	err = libbpf_get_error(obj);
	अगर (err < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: opening BPF object file failed\n");
		वापस err;
	पूर्ण

	/* load BPF program */
	err = bpf_object__load(obj);
	अगर (err < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: loading BPF object file failed\n");
		वापस err;
	पूर्ण

	bpf_object__क्रम_each_program(prog, obj) अणु
		links[cnt] = bpf_program__attach(prog);
		err = libbpf_get_error(links[cnt]);
		अगर (err < 0) अणु
			ख_लिखो(मानक_त्रुटि, "ERROR: bpf_program__attach failed\n");
			links[cnt] = शून्य;
			वापस err;
		पूर्ण
		cnt++;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम unload_progs(व्योम)
अणु
	जबतक (cnt)
		bpf_link__destroy(links[--cnt]);

	bpf_object__बंद(obj);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक num_cpu = sysconf(_SC_NPROCESSORS_ONLN);
	पूर्णांक test_flags = ~0;
	अक्षर filename[256];
	पूर्णांक err = 0;


	अगर (argc > 1)
		test_flags = म_से_प(argv[1]) ? : test_flags;
	अगर (argc > 2)
		num_cpu = म_से_प(argv[2]) ? : num_cpu;

	अगर (test_flags & 0x3) अणु
		म_लिखो("BASE\n");
		run_perf_test(num_cpu, test_flags);
	पूर्ण

	अगर (test_flags & 0xC) अणु
		snम_लिखो(filename, माप(filename),
			 "%s_kprobe_kern.o", argv[0]);

		म_लिखो("w/KPROBE\n");
		err = load_progs(filename);
		अगर (!err)
			run_perf_test(num_cpu, test_flags >> 2);

		unload_progs();
	पूर्ण

	अगर (test_flags & 0x30) अणु
		snम_लिखो(filename, माप(filename),
			 "%s_tp_kern.o", argv[0]);
		म_लिखो("w/TRACEPOINT\n");
		err = load_progs(filename);
		अगर (!err)
			run_perf_test(num_cpu, test_flags >> 4);

		unload_progs();
	पूर्ण

	अगर (test_flags & 0xC0) अणु
		snम_लिखो(filename, माप(filename),
			 "%s_raw_tp_kern.o", argv[0]);
		म_लिखो("w/RAW_TRACEPOINT\n");
		err = load_progs(filename);
		अगर (!err)
			run_perf_test(num_cpu, test_flags >> 6);

		unload_progs();
	पूर्ण

	वापस err;
पूर्ण
