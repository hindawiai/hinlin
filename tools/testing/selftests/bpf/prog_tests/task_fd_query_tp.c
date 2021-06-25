<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>

अटल व्योम test_task_fd_query_tp_core(स्थिर अक्षर *probe_name,
				       स्थिर अक्षर *tp_name)
अणु
	स्थिर अक्षर *file = "./test_tracepoint.o";
	पूर्णांक err, bytes, efd, prog_fd, pmu_fd;
	काष्ठा perf_event_attr attr = अणुपूर्ण;
	__u64 probe_offset, probe_addr;
	__u32 len, prog_id, fd_type;
	काष्ठा bpf_object *obj = शून्य;
	__u32 duration = 0;
	अक्षर buf[256];

	err = bpf_prog_load(file, BPF_PROG_TYPE_TRACEPOINT, &obj, &prog_fd);
	अगर (CHECK(err, "bpf_prog_load", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ बंद_prog;

	snम_लिखो(buf, माप(buf),
		 "/sys/kernel/debug/tracing/events/%s/id", probe_name);
	efd = खोलो(buf, O_RDONLY, 0);
	अगर (CHECK(efd < 0, "open", "err %d errno %d\n", efd, त्रुटि_सं))
		जाओ बंद_prog;
	bytes = पढ़ो(efd, buf, माप(buf));
	बंद(efd);
	अगर (CHECK(bytes <= 0 || bytes >= माप(buf), "read",
		  "bytes %d errno %d\n", bytes, त्रुटि_सं))
		जाओ बंद_prog;

	attr.config = म_से_दीर्घ(buf, शून्य, 0);
	attr.type = PERF_TYPE_TRACEPOINT;
	attr.sample_type = PERF_SAMPLE_RAW;
	attr.sample_period = 1;
	attr.wakeup_events = 1;
	pmu_fd = syscall(__NR_perf_event_खोलो, &attr, -1 /* pid */,
			 0 /* cpu 0 */, -1 /* group id */,
			 0 /* flags */);
	अगर (CHECK(err, "perf_event_open", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ बंद_pmu;

	err = ioctl(pmu_fd, PERF_EVENT_IOC_ENABLE, 0);
	अगर (CHECK(err, "perf_event_ioc_enable", "err %d errno %d\n", err,
		  त्रुटि_सं))
		जाओ बंद_pmu;

	err = ioctl(pmu_fd, PERF_EVENT_IOC_SET_BPF, prog_fd);
	अगर (CHECK(err, "perf_event_ioc_set_bpf", "err %d errno %d\n", err,
		  त्रुटि_सं))
		जाओ बंद_pmu;

	/* query (getpid(), pmu_fd) */
	len = माप(buf);
	err = bpf_task_fd_query(getpid(), pmu_fd, 0, buf, &len, &prog_id,
				&fd_type, &probe_offset, &probe_addr);
	अगर (CHECK(err < 0, "bpf_task_fd_query", "err %d errno %d\n", err,
		  त्रुटि_सं))
		जाओ बंद_pmu;

	err = (fd_type == BPF_FD_TYPE_TRACEPOINT) && !म_भेद(buf, tp_name);
	अगर (CHECK(!err, "check_results", "fd_type %d tp_name %s\n",
		  fd_type, buf))
		जाओ बंद_pmu;

बंद_pmu:
	बंद(pmu_fd);
बंद_prog:
	bpf_object__बंद(obj);
पूर्ण

व्योम test_task_fd_query_tp(व्योम)
अणु
	test_task_fd_query_tp_core("sched/sched_switch",
				   "sched_switch");
	test_task_fd_query_tp_core("syscalls/sys_enter_read",
				   "sys_enter_read");
पूर्ण
