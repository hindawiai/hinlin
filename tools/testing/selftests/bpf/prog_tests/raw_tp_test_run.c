<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2019 Facebook */
#समावेश <test_progs.h>
#समावेश <linux/bpf.h>
#समावेश "bpf/libbpf_internal.h"
#समावेश "test_raw_tp_test_run.skel.h"

अटल पूर्णांक duration;

व्योम test_raw_tp_test_run(व्योम)
अणु
	काष्ठा bpf_prog_test_run_attr test_attr = अणुपूर्ण;
	पूर्णांक comm_fd = -1, err, nr_online, i, prog_fd;
	__u64 args[2] = अणु0x1234ULL, 0x5678ULLपूर्ण;
	पूर्णांक expected_retval = 0x1234 + 0x5678;
	काष्ठा test_raw_tp_test_run *skel;
	अक्षर buf[] = "new_name";
	bool *online = शून्य;
	DECLARE_LIBBPF_OPTS(bpf_test_run_opts, opts,
			    .ctx_in = args,
			    .ctx_size_in = माप(args),
			    .flags = BPF_F_TEST_RUN_ON_CPU,
		);

	err = parse_cpu_mask_file("/sys/devices/system/cpu/online", &online,
				  &nr_online);
	अगर (CHECK(err, "parse_cpu_mask_file", "err %d\n", err))
		वापस;

	skel = test_raw_tp_test_run__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open", "failed to open skeleton\n"))
		जाओ cleanup;

	err = test_raw_tp_test_run__attach(skel);
	अगर (CHECK(err, "skel_attach", "skeleton attach failed: %d\n", err))
		जाओ cleanup;

	comm_fd = खोलो("/proc/self/comm", O_WRONLY|O_TRUNC);
	अगर (CHECK(comm_fd < 0, "open /proc/self/comm", "err %d\n", त्रुटि_सं))
		जाओ cleanup;

	err = ग_लिखो(comm_fd, buf, माप(buf));
	CHECK(err < 0, "task rename", "err %d", त्रुटि_सं);

	CHECK(skel->bss->count == 0, "check_count", "didn't increase\n");
	CHECK(skel->data->on_cpu != 0xffffffff, "check_on_cpu", "got wrong value\n");

	prog_fd = bpf_program__fd(skel->progs.नाम);
	test_attr.prog_fd = prog_fd;
	test_attr.ctx_in = args;
	test_attr.ctx_size_in = माप(__u64);

	err = bpf_prog_test_run_xattr(&test_attr);
	CHECK(err == 0, "test_run", "should fail for too small ctx\n");

	test_attr.ctx_size_in = माप(args);
	err = bpf_prog_test_run_xattr(&test_attr);
	CHECK(err < 0, "test_run", "err %d\n", त्रुटि_सं);
	CHECK(test_attr.retval != expected_retval, "check_retval",
	      "expect 0x%x, got 0x%x\n", expected_retval, test_attr.retval);

	क्रम (i = 0; i < nr_online; i++) अणु
		अगर (!online[i])
			जारी;

		opts.cpu = i;
		opts.retval = 0;
		err = bpf_prog_test_run_opts(prog_fd, &opts);
		CHECK(err < 0, "test_run_opts", "err %d\n", त्रुटि_सं);
		CHECK(skel->data->on_cpu != i, "check_on_cpu",
		      "expect %d got %d\n", i, skel->data->on_cpu);
		CHECK(opts.retval != expected_retval,
		      "check_retval", "expect 0x%x, got 0x%x\n",
		      expected_retval, opts.retval);
	पूर्ण

	/* invalid cpu ID should fail with ENXIO */
	opts.cpu = 0xffffffff;
	err = bpf_prog_test_run_opts(prog_fd, &opts);
	CHECK(err != -1 || त्रुटि_सं != ENXIO,
	      "test_run_opts_fail",
	      "should failed with ENXIO\n");

	/* non-zero cpu w/o BPF_F_TEST_RUN_ON_CPU should fail with EINVAL */
	opts.cpu = 1;
	opts.flags = 0;
	err = bpf_prog_test_run_opts(prog_fd, &opts);
	CHECK(err != -1 || त्रुटि_सं != EINVAL,
	      "test_run_opts_fail",
	      "should failed with EINVAL\n");

cleanup:
	बंद(comm_fd);
	test_raw_tp_test_run__destroy(skel);
	मुक्त(online);
पूर्ण
