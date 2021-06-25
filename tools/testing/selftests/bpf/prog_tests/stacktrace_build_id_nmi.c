<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश "test_stacktrace_build_id.skel.h"

अटल __u64 पढ़ो_perf_max_sample_freq(व्योम)
अणु
	__u64 sample_freq = 5000; /* fallback to 5000 on error */
	खाता *f;
	__u32 duration = 0;

	f = ख_खोलो("/proc/sys/kernel/perf_event_max_sample_rate", "r");
	अगर (f == शून्य)
		वापस sample_freq;
	CHECK(ख_पूछो(f, "%llu", &sample_freq) != 1, "Get max sample rate",
		  "return default value: 5000,err %d\n", -त्रुटि_सं);
	ख_बंद(f);
	वापस sample_freq;
पूर्ण

व्योम test_stacktrace_build_id_nmi(व्योम)
अणु
	पूर्णांक control_map_fd, stackid_hmap_fd, stackmap_fd;
	काष्ठा test_stacktrace_build_id *skel;
	पूर्णांक err, pmu_fd;
	काष्ठा perf_event_attr attr = अणु
		.freq = 1,
		.type = PERF_TYPE_HARDWARE,
		.config = PERF_COUNT_HW_CPU_CYCLES,
	पूर्ण;
	__u32 key, previous_key, val, duration = 0;
	अक्षर buf[256];
	पूर्णांक i, j;
	काष्ठा bpf_stack_build_id id_offs[PERF_MAX_STACK_DEPTH];
	पूर्णांक build_id_matches = 0;
	पूर्णांक retry = 1;

	attr.sample_freq = पढ़ो_perf_max_sample_freq();

retry:
	skel = test_stacktrace_build_id__खोलो();
	अगर (CHECK(!skel, "skel_open", "skeleton open failed\n"))
		वापस;

	/* override program type */
	bpf_program__set_perf_event(skel->progs.oncpu);

	err = test_stacktrace_build_id__load(skel);
	अगर (CHECK(err, "skel_load", "skeleton load failed: %d\n", err))
		जाओ cleanup;

	pmu_fd = syscall(__NR_perf_event_खोलो, &attr, -1 /* pid */,
			 0 /* cpu 0 */, -1 /* group id */,
			 0 /* flags */);
	अगर (pmu_fd < 0 && त्रुटि_सं == ENOENT) अणु
		म_लिखो("%s:SKIP:no PERF_COUNT_HW_CPU_CYCLES\n", __func__);
		test__skip();
		जाओ cleanup;
	पूर्ण
	अगर (CHECK(pmu_fd < 0, "perf_event_open", "err %d errno %d\n",
		  pmu_fd, त्रुटि_सं))
		जाओ cleanup;

	skel->links.oncpu = bpf_program__attach_perf_event(skel->progs.oncpu,
							   pmu_fd);
	अगर (CHECK(IS_ERR(skel->links.oncpu), "attach_perf_event",
		  "err %ld\n", PTR_ERR(skel->links.oncpu))) अणु
		बंद(pmu_fd);
		जाओ cleanup;
	पूर्ण

	/* find map fds */
	control_map_fd = bpf_map__fd(skel->maps.control_map);
	stackid_hmap_fd = bpf_map__fd(skel->maps.stackid_hmap);
	stackmap_fd = bpf_map__fd(skel->maps.stackmap);

	अगर (CHECK_FAIL(प्रणाली("dd if=/dev/urandom of=/dev/zero count=4 2> /dev/null")))
		जाओ cleanup;
	अगर (CHECK_FAIL(प्रणाली("taskset 0x1 ./urandom_read 100000")))
		जाओ cleanup;
	/* disable stack trace collection */
	key = 0;
	val = 1;
	bpf_map_update_elem(control_map_fd, &key, &val, 0);

	/* क्रम every element in stackid_hmap, we can find a corresponding one
	 * in stackmap, and vise versa.
	 */
	err = compare_map_keys(stackid_hmap_fd, stackmap_fd);
	अगर (CHECK(err, "compare_map_keys stackid_hmap vs. stackmap",
		  "err %d errno %d\n", err, त्रुटि_सं))
		जाओ cleanup;

	err = compare_map_keys(stackmap_fd, stackid_hmap_fd);
	अगर (CHECK(err, "compare_map_keys stackmap vs. stackid_hmap",
		  "err %d errno %d\n", err, त्रुटि_सं))
		जाओ cleanup;

	err = extract_build_id(buf, 256);

	अगर (CHECK(err, "get build_id with readelf",
		  "err %d errno %d\n", err, त्रुटि_सं))
		जाओ cleanup;

	err = bpf_map_get_next_key(stackmap_fd, शून्य, &key);
	अगर (CHECK(err, "get_next_key from stackmap",
		  "err %d, errno %d\n", err, त्रुटि_सं))
		जाओ cleanup;

	करो अणु
		अक्षर build_id[64];

		err = bpf_map_lookup_elem(stackmap_fd, &key, id_offs);
		अगर (CHECK(err, "lookup_elem from stackmap",
			  "err %d, errno %d\n", err, त्रुटि_सं))
			जाओ cleanup;
		क्रम (i = 0; i < PERF_MAX_STACK_DEPTH; ++i)
			अगर (id_offs[i].status == BPF_STACK_BUILD_ID_VALID &&
			    id_offs[i].offset != 0) अणु
				क्रम (j = 0; j < 20; ++j)
					प्र_लिखो(build_id + 2 * j, "%02x",
						id_offs[i].build_id[j] & 0xff);
				अगर (म_माला(buf, build_id) != शून्य)
					build_id_matches = 1;
			पूर्ण
		previous_key = key;
	पूर्ण जबतक (bpf_map_get_next_key(stackmap_fd, &previous_key, &key) == 0);

	/* stack_map_get_build_id_offset() is racy and someबार can वापस
	 * BPF_STACK_BUILD_ID_IP instead of BPF_STACK_BUILD_ID_VALID;
	 * try it one more समय.
	 */
	अगर (build_id_matches < 1 && retry--) अणु
		test_stacktrace_build_id__destroy(skel);
		म_लिखो("%s:WARN:Didn't find expected build ID from the map, retrying\n",
		       __func__);
		जाओ retry;
	पूर्ण

	अगर (CHECK(build_id_matches < 1, "build id match",
		  "Didn't find expected build ID from the map\n"))
		जाओ cleanup;

	/*
	 * We पूर्णांकentionally skip compare_stack_ips(). This is because we
	 * only support one in_nmi() ips-to-build_id translation per cpu
	 * at any समय, thus stack_amap here will always fallback to
	 * BPF_STACK_BUILD_ID_IP;
	 */

cleanup:
	test_stacktrace_build_id__destroy(skel);
पूर्ण
