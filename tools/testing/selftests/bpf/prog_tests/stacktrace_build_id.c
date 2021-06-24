<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश "test_stacktrace_build_id.skel.h"

व्योम test_stacktrace_build_id(व्योम)
अणु

	पूर्णांक control_map_fd, stackid_hmap_fd, stackmap_fd, stack_amap_fd;
	काष्ठा test_stacktrace_build_id *skel;
	पूर्णांक err, stack_trace_len;
	__u32 key, previous_key, val, duration = 0;
	अक्षर buf[256];
	पूर्णांक i, j;
	काष्ठा bpf_stack_build_id id_offs[PERF_MAX_STACK_DEPTH];
	पूर्णांक build_id_matches = 0;
	पूर्णांक retry = 1;

retry:
	skel = test_stacktrace_build_id__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open_and_load", "skeleton open/load failed\n"))
		वापस;

	err = test_stacktrace_build_id__attach(skel);
	अगर (CHECK(err, "attach_tp", "err %d\n", err))
		जाओ cleanup;

	/* find map fds */
	control_map_fd = bpf_map__fd(skel->maps.control_map);
	stackid_hmap_fd = bpf_map__fd(skel->maps.stackid_hmap);
	stackmap_fd = bpf_map__fd(skel->maps.stackmap);
	stack_amap_fd = bpf_map__fd(skel->maps.stack_amap);

	अगर (CHECK_FAIL(प्रणाली("dd if=/dev/urandom of=/dev/zero count=4 2> /dev/null")))
		जाओ cleanup;
	अगर (CHECK_FAIL(प्रणाली("./urandom_read")))
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

	stack_trace_len = PERF_MAX_STACK_DEPTH *
			  माप(काष्ठा bpf_stack_build_id);
	err = compare_stack_ips(stackmap_fd, stack_amap_fd, stack_trace_len);
	CHECK(err, "compare_stack_ips stackmap vs. stack_amap",
	      "err %d errno %d\n", err, त्रुटि_सं);

cleanup:
	test_stacktrace_build_id__destroy(skel);
पूर्ण
