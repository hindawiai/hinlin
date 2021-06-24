<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>

व्योम test_tp_attach_query(व्योम)
अणु
	स्थिर पूर्णांक num_progs = 3;
	पूर्णांक i, j, bytes, efd, err, prog_fd[num_progs], pmu_fd[num_progs];
	__u32 duration = 0, info_len, saved_prog_ids[num_progs];
	स्थिर अक्षर *file = "./test_tracepoint.o";
	काष्ठा perf_event_query_bpf *query;
	काष्ठा perf_event_attr attr = अणुपूर्ण;
	काष्ठा bpf_object *obj[num_progs];
	काष्ठा bpf_prog_info prog_info;
	अक्षर buf[256];

	क्रम (i = 0; i < num_progs; i++)
		obj[i] = शून्य;

	snम_लिखो(buf, माप(buf),
		 "/sys/kernel/debug/tracing/events/sched/sched_switch/id");
	efd = खोलो(buf, O_RDONLY, 0);
	अगर (CHECK(efd < 0, "open", "err %d errno %d\n", efd, त्रुटि_सं))
		वापस;
	bytes = पढ़ो(efd, buf, माप(buf));
	बंद(efd);
	अगर (CHECK(bytes <= 0 || bytes >= माप(buf),
		  "read", "bytes %d errno %d\n", bytes, त्रुटि_सं))
		वापस;

	attr.config = म_से_दीर्घ(buf, शून्य, 0);
	attr.type = PERF_TYPE_TRACEPOINT;
	attr.sample_type = PERF_SAMPLE_RAW | PERF_SAMPLE_CALLCHAIN;
	attr.sample_period = 1;
	attr.wakeup_events = 1;

	query = दो_स्मृति(माप(*query) + माप(__u32) * num_progs);
	क्रम (i = 0; i < num_progs; i++) अणु
		err = bpf_prog_load(file, BPF_PROG_TYPE_TRACEPOINT, &obj[i],
				    &prog_fd[i]);
		अगर (CHECK(err, "prog_load", "err %d errno %d\n", err, त्रुटि_सं))
			जाओ cleanup1;

		bzero(&prog_info, माप(prog_info));
		prog_info.jited_prog_len = 0;
		prog_info.xlated_prog_len = 0;
		prog_info.nr_map_ids = 0;
		info_len = माप(prog_info);
		err = bpf_obj_get_info_by_fd(prog_fd[i], &prog_info, &info_len);
		अगर (CHECK(err, "bpf_obj_get_info_by_fd", "err %d errno %d\n",
			  err, त्रुटि_सं))
			जाओ cleanup1;
		saved_prog_ids[i] = prog_info.id;

		pmu_fd[i] = syscall(__NR_perf_event_खोलो, &attr, -1 /* pid */,
				    0 /* cpu 0 */, -1 /* group id */,
				    0 /* flags */);
		अगर (CHECK(pmu_fd[i] < 0, "perf_event_open", "err %d errno %d\n",
			  pmu_fd[i], त्रुटि_सं))
			जाओ cleanup2;
		err = ioctl(pmu_fd[i], PERF_EVENT_IOC_ENABLE, 0);
		अगर (CHECK(err, "perf_event_ioc_enable", "err %d errno %d\n",
			  err, त्रुटि_सं))
			जाओ cleanup3;

		अगर (i == 0) अणु
			/* check शून्य prog array query */
			query->ids_len = num_progs;
			err = ioctl(pmu_fd[i], PERF_EVENT_IOC_QUERY_BPF, query);
			अगर (CHECK(err || query->prog_cnt != 0,
				  "perf_event_ioc_query_bpf",
				  "err %d errno %d query->prog_cnt %u\n",
				  err, त्रुटि_सं, query->prog_cnt))
				जाओ cleanup3;
		पूर्ण

		err = ioctl(pmu_fd[i], PERF_EVENT_IOC_SET_BPF, prog_fd[i]);
		अगर (CHECK(err, "perf_event_ioc_set_bpf", "err %d errno %d\n",
			  err, त्रुटि_सं))
			जाओ cleanup3;

		अगर (i == 1) अणु
			/* try to get # of programs only */
			query->ids_len = 0;
			err = ioctl(pmu_fd[i], PERF_EVENT_IOC_QUERY_BPF, query);
			अगर (CHECK(err || query->prog_cnt != 2,
				  "perf_event_ioc_query_bpf",
				  "err %d errno %d query->prog_cnt %u\n",
				  err, त्रुटि_सं, query->prog_cnt))
				जाओ cleanup3;

			/* try a few negative tests */
			/* invalid query poपूर्णांकer */
			err = ioctl(pmu_fd[i], PERF_EVENT_IOC_QUERY_BPF,
				    (काष्ठा perf_event_query_bpf *)0x1);
			अगर (CHECK(!err || त्रुटि_सं != EFAULT,
				  "perf_event_ioc_query_bpf",
				  "err %d errno %d\n", err, त्रुटि_सं))
				जाओ cleanup3;

			/* no enough space */
			query->ids_len = 1;
			err = ioctl(pmu_fd[i], PERF_EVENT_IOC_QUERY_BPF, query);
			अगर (CHECK(!err || त्रुटि_सं != ENOSPC || query->prog_cnt != 2,
				  "perf_event_ioc_query_bpf",
				  "err %d errno %d query->prog_cnt %u\n",
				  err, त्रुटि_सं, query->prog_cnt))
				जाओ cleanup3;
		पूर्ण

		query->ids_len = num_progs;
		err = ioctl(pmu_fd[i], PERF_EVENT_IOC_QUERY_BPF, query);
		अगर (CHECK(err || query->prog_cnt != (i + 1),
			  "perf_event_ioc_query_bpf",
			  "err %d errno %d query->prog_cnt %u\n",
			  err, त्रुटि_सं, query->prog_cnt))
			जाओ cleanup3;
		क्रम (j = 0; j < i + 1; j++)
			अगर (CHECK(saved_prog_ids[j] != query->ids[j],
				  "perf_event_ioc_query_bpf",
				  "#%d saved_prog_id %x query prog_id %x\n",
				  j, saved_prog_ids[j], query->ids[j]))
				जाओ cleanup3;
	पूर्ण

	i = num_progs - 1;
	क्रम (; i >= 0; i--) अणु
 cleanup3:
		ioctl(pmu_fd[i], PERF_EVENT_IOC_DISABLE);
 cleanup2:
		बंद(pmu_fd[i]);
 cleanup1:
		bpf_object__बंद(obj[i]);
	पूर्ण
	मुक्त(query);
पूर्ण
