<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2019 Facebook */
#घोषणा _GNU_SOURCE
#समावेश <sched.h>
#समावेश <sys/prctl.h>
#समावेश <test_progs.h>

#घोषणा MAX_CNT 100000

अटल __u64 समय_get_ns(व्योम)
अणु
	काष्ठा बारpec ts;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &ts);
	वापस ts.tv_sec * 1000000000ull + ts.tv_nsec;
पूर्ण

अटल पूर्णांक test_task_नाम(स्थिर अक्षर *prog)
अणु
	पूर्णांक i, fd, duration = 0, err;
	अक्षर buf[] = "test_overhead";
	__u64 start_समय;

	fd = खोलो("/proc/self/comm", O_WRONLY|O_TRUNC);
	अगर (CHECK(fd < 0, "open /proc", "err %d", त्रुटि_सं))
		वापस -1;
	start_समय = समय_get_ns();
	क्रम (i = 0; i < MAX_CNT; i++) अणु
		err = ग_लिखो(fd, buf, माप(buf));
		अगर (err < 0) अणु
			CHECK(err < 0, "task rename", "err %d", त्रुटि_सं);
			बंद(fd);
			वापस -1;
		पूर्ण
	पूर्ण
	म_लिखो("task_rename %s\t%lluK events per sec\n", prog,
	       MAX_CNT * 1000000ll / (समय_get_ns() - start_समय));
	बंद(fd);
	वापस 0;
पूर्ण

अटल व्योम test_run(स्थिर अक्षर *prog)
अणु
	test_task_नाम(prog);
पूर्ण

अटल व्योम setaffinity(व्योम)
अणु
	cpu_set_t cpuset;
	पूर्णांक cpu = 0;

	CPU_ZERO(&cpuset);
	CPU_SET(cpu, &cpuset);
	sched_setaffinity(0, माप(cpuset), &cpuset);
पूर्ण

व्योम test_test_overhead(व्योम)
अणु
	स्थिर अक्षर *kprobe_name = "kprobe/__set_task_comm";
	स्थिर अक्षर *kretprobe_name = "kretprobe/__set_task_comm";
	स्थिर अक्षर *raw_tp_name = "raw_tp/task_rename";
	स्थिर अक्षर *fentry_name = "fentry/__set_task_comm";
	स्थिर अक्षर *fनिकास_name = "fexit/__set_task_comm";
	स्थिर अक्षर *kprobe_func = "__set_task_comm";
	काष्ठा bpf_program *kprobe_prog, *kretprobe_prog, *raw_tp_prog;
	काष्ठा bpf_program *fentry_prog, *fनिकास_prog;
	काष्ठा bpf_object *obj;
	काष्ठा bpf_link *link;
	पूर्णांक err, duration = 0;
	अक्षर comm[16] = अणुपूर्ण;

	अगर (CHECK_FAIL(prctl(PR_GET_NAME, comm, 0L, 0L, 0L)))
		वापस;

	obj = bpf_object__खोलो_file("./test_overhead.o", शून्य);
	अगर (CHECK(IS_ERR(obj), "obj_open_file", "err %ld\n", PTR_ERR(obj)))
		वापस;

	kprobe_prog = bpf_object__find_program_by_title(obj, kprobe_name);
	अगर (CHECK(!kprobe_prog, "find_probe",
		  "prog '%s' not found\n", kprobe_name))
		जाओ cleanup;
	kretprobe_prog = bpf_object__find_program_by_title(obj, kretprobe_name);
	अगर (CHECK(!kretprobe_prog, "find_probe",
		  "prog '%s' not found\n", kretprobe_name))
		जाओ cleanup;
	raw_tp_prog = bpf_object__find_program_by_title(obj, raw_tp_name);
	अगर (CHECK(!raw_tp_prog, "find_probe",
		  "prog '%s' not found\n", raw_tp_name))
		जाओ cleanup;
	fentry_prog = bpf_object__find_program_by_title(obj, fentry_name);
	अगर (CHECK(!fentry_prog, "find_probe",
		  "prog '%s' not found\n", fentry_name))
		जाओ cleanup;
	fनिकास_prog = bpf_object__find_program_by_title(obj, fनिकास_name);
	अगर (CHECK(!fनिकास_prog, "find_probe",
		  "prog '%s' not found\n", fनिकास_name))
		जाओ cleanup;
	err = bpf_object__load(obj);
	अगर (CHECK(err, "obj_load", "err %d\n", err))
		जाओ cleanup;

	setaffinity();

	/* base line run */
	test_run("base");

	/* attach kprobe */
	link = bpf_program__attach_kprobe(kprobe_prog, false /* retprobe */,
					  kprobe_func);
	अगर (CHECK(IS_ERR(link), "attach_kprobe", "err %ld\n", PTR_ERR(link)))
		जाओ cleanup;
	test_run("kprobe");
	bpf_link__destroy(link);

	/* attach kretprobe */
	link = bpf_program__attach_kprobe(kretprobe_prog, true /* retprobe */,
					  kprobe_func);
	अगर (CHECK(IS_ERR(link), "attach kretprobe", "err %ld\n", PTR_ERR(link)))
		जाओ cleanup;
	test_run("kretprobe");
	bpf_link__destroy(link);

	/* attach raw_tp */
	link = bpf_program__attach_raw_tracepoपूर्णांक(raw_tp_prog, "task_rename");
	अगर (CHECK(IS_ERR(link), "attach fentry", "err %ld\n", PTR_ERR(link)))
		जाओ cleanup;
	test_run("raw_tp");
	bpf_link__destroy(link);

	/* attach fentry */
	link = bpf_program__attach_trace(fentry_prog);
	अगर (CHECK(IS_ERR(link), "attach fentry", "err %ld\n", PTR_ERR(link)))
		जाओ cleanup;
	test_run("fentry");
	bpf_link__destroy(link);

	/* attach fनिकास */
	link = bpf_program__attach_trace(fनिकास_prog);
	अगर (CHECK(IS_ERR(link), "attach fexit", "err %ld\n", PTR_ERR(link)))
		जाओ cleanup;
	test_run("fexit");
	bpf_link__destroy(link);

cleanup:
	prctl(PR_SET_NAME, comm, 0L, 0L, 0L);
	bpf_object__बंद(obj);
पूर्ण
