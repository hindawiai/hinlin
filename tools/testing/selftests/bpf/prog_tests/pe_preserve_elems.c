<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2019 Facebook */
#समावेश <test_progs.h>
#समावेश <linux/bpf.h>
#समावेश "test_pe_preserve_elems.skel.h"

अटल पूर्णांक duration;

अटल व्योम test_one_map(काष्ठा bpf_map *map, काष्ठा bpf_program *prog,
			 bool has_share_pe)
अणु
	पूर्णांक err, key = 0, pfd = -1, mfd = bpf_map__fd(map);
	DECLARE_LIBBPF_OPTS(bpf_test_run_opts, opts);
	काष्ठा perf_event_attr attr = अणु
		.size = माप(काष्ठा perf_event_attr),
		.type = PERF_TYPE_SOFTWARE,
		.config = PERF_COUNT_SW_CPU_CLOCK,
	पूर्ण;

	pfd = syscall(__NR_perf_event_खोलो, &attr, 0 /* pid */,
		      -1 /* cpu 0 */, -1 /* group id */, 0 /* flags */);
	अगर (CHECK(pfd < 0, "perf_event_open", "failed\n"))
		वापस;

	err = bpf_map_update_elem(mfd, &key, &pfd, BPF_ANY);
	बंद(pfd);
	अगर (CHECK(err < 0, "bpf_map_update_elem", "failed\n"))
		वापस;

	err = bpf_prog_test_run_opts(bpf_program__fd(prog), &opts);
	अगर (CHECK(err < 0, "bpf_prog_test_run_opts", "failed\n"))
		वापस;
	अगर (CHECK(opts.retval != 0, "bpf_perf_event_read_value",
		  "failed with %d\n", opts.retval))
		वापस;

	/* closing mfd, prog still holds a reference on map */
	बंद(mfd);

	err = bpf_prog_test_run_opts(bpf_program__fd(prog), &opts);
	अगर (CHECK(err < 0, "bpf_prog_test_run_opts", "failed\n"))
		वापस;

	अगर (has_share_pe) अणु
		CHECK(opts.retval != 0, "bpf_perf_event_read_value",
		      "failed with %d\n", opts.retval);
	पूर्ण अन्यथा अणु
		CHECK(opts.retval != -ENOENT, "bpf_perf_event_read_value",
		      "should have failed with %d, but got %d\n", -ENOENT,
		      opts.retval);
	पूर्ण
पूर्ण

व्योम test_pe_preserve_elems(व्योम)
अणु
	काष्ठा test_pe_preserve_elems *skel;

	skel = test_pe_preserve_elems__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open", "failed to open skeleton\n"))
		वापस;

	test_one_map(skel->maps.array_1, skel->progs.पढ़ो_array_1, false);
	test_one_map(skel->maps.array_2, skel->progs.पढ़ो_array_2, true);

	test_pe_preserve_elems__destroy(skel);
पूर्ण
