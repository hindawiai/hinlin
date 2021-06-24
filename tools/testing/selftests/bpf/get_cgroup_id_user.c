<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Facebook

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <syscall.h>
#समावेश <unistd.h>
#समावेश <linux/perf_event.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#समावेश "cgroup_helpers.h"
#समावेश "bpf_rlimit.h"

#घोषणा CHECK(condition, tag, क्रमmat...) (अणु		\
	पूर्णांक __ret = !!(condition);			\
	अगर (__ret) अणु					\
		म_लिखो("%s:FAIL:%s ", __func__, tag);	\
		म_लिखो(क्रमmat);				\
	पूर्ण अन्यथा अणु					\
		म_लिखो("%s:PASS:%s\n", __func__, tag);	\
	पूर्ण						\
	__ret;						\
पूर्ण)

अटल पूर्णांक bpf_find_map(स्थिर अक्षर *test, काष्ठा bpf_object *obj,
			स्थिर अक्षर *name)
अणु
	काष्ठा bpf_map *map;

	map = bpf_object__find_map_by_name(obj, name);
	अगर (!map)
		वापस -1;
	वापस bpf_map__fd(map);
पूर्ण

#घोषणा TEST_CGROUP "/test-bpf-get-cgroup-id/"

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर अक्षर *probe_name = "syscalls/sys_enter_nanosleep";
	स्थिर अक्षर *file = "get_cgroup_id_kern.o";
	पूर्णांक err, bytes, efd, prog_fd, pmu_fd;
	पूर्णांक cgroup_fd, cgidmap_fd, pidmap_fd;
	काष्ठा perf_event_attr attr = अणुपूर्ण;
	काष्ठा bpf_object *obj;
	__u64 kcgid = 0, ucgid;
	__u32 key = 0, pid;
	पूर्णांक निकास_code = 1;
	अक्षर buf[256];
	स्थिर काष्ठा बारpec req = अणु
		.tv_sec = 1,
		.tv_nsec = 0,
	पूर्ण;

	cgroup_fd = cgroup_setup_and_join(TEST_CGROUP);
	अगर (CHECK(cgroup_fd < 0, "cgroup_setup_and_join", "err %d errno %d\n", cgroup_fd, त्रुटि_सं))
		वापस 1;

	err = bpf_prog_load(file, BPF_PROG_TYPE_TRACEPOINT, &obj, &prog_fd);
	अगर (CHECK(err, "bpf_prog_load", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ cleanup_cgroup_env;

	cgidmap_fd = bpf_find_map(__func__, obj, "cg_ids");
	अगर (CHECK(cgidmap_fd < 0, "bpf_find_map", "err %d errno %d\n",
		  cgidmap_fd, त्रुटि_सं))
		जाओ बंद_prog;

	pidmap_fd = bpf_find_map(__func__, obj, "pidmap");
	अगर (CHECK(pidmap_fd < 0, "bpf_find_map", "err %d errno %d\n",
		  pidmap_fd, त्रुटि_सं))
		जाओ बंद_prog;

	pid = getpid();
	bpf_map_update_elem(pidmap_fd, &key, &pid, 0);

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

	/* attach to this pid so the all bpf invocations will be in the
	 * cgroup associated with this pid.
	 */
	pmu_fd = syscall(__NR_perf_event_खोलो, &attr, getpid(), -1, -1, 0);
	अगर (CHECK(pmu_fd < 0, "perf_event_open", "err %d errno %d\n", pmu_fd,
		  त्रुटि_सं))
		जाओ बंद_prog;

	err = ioctl(pmu_fd, PERF_EVENT_IOC_ENABLE, 0);
	अगर (CHECK(err, "perf_event_ioc_enable", "err %d errno %d\n", err,
		  त्रुटि_सं))
		जाओ बंद_pmu;

	err = ioctl(pmu_fd, PERF_EVENT_IOC_SET_BPF, prog_fd);
	अगर (CHECK(err, "perf_event_ioc_set_bpf", "err %d errno %d\n", err,
		  त्रुटि_सं))
		जाओ बंद_pmu;

	/* trigger some syscalls */
	syscall(__NR_nanosleep, &req, शून्य);

	err = bpf_map_lookup_elem(cgidmap_fd, &key, &kcgid);
	अगर (CHECK(err, "bpf_map_lookup_elem", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ बंद_pmu;

	ucgid = get_cgroup_id(TEST_CGROUP);
	अगर (CHECK(kcgid != ucgid, "compare_cgroup_id",
		  "kern cgid %llx user cgid %llx", kcgid, ucgid))
		जाओ बंद_pmu;

	निकास_code = 0;
	म_लिखो("%s:PASS\n", argv[0]);

बंद_pmu:
	बंद(pmu_fd);
बंद_prog:
	bpf_object__बंद(obj);
cleanup_cgroup_env:
	cleanup_cgroup_environment();
	वापस निकास_code;
पूर्ण
