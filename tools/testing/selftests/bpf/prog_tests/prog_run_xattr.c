<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <network_helpers.h>

#समावेश "test_pkt_access.skel.h"

अटल स्थिर __u32 duration;

अटल व्योम check_run_cnt(पूर्णांक prog_fd, __u64 run_cnt)
अणु
	काष्ठा bpf_prog_info info = अणुपूर्ण;
	__u32 info_len = माप(info);
	पूर्णांक err;

	err = bpf_obj_get_info_by_fd(prog_fd, &info, &info_len);
	अगर (CHECK(err, "get_prog_info", "failed to get bpf_prog_info for fd %d\n", prog_fd))
		वापस;

	CHECK(run_cnt != info.run_cnt, "run_cnt",
	      "incorrect number of repetitions, want %llu have %llu\n", run_cnt, info.run_cnt);
पूर्ण

व्योम test_prog_run_xattr(व्योम)
अणु
	काष्ठा test_pkt_access *skel;
	पूर्णांक err, stats_fd = -1;
	अक्षर buf[10] = अणुपूर्ण;
	__u64 run_cnt = 0;

	काष्ठा bpf_prog_test_run_attr tattr = अणु
		.repeat = 1,
		.data_in = &pkt_v4,
		.data_size_in = माप(pkt_v4),
		.data_out = buf,
		.data_size_out = 5,
	पूर्ण;

	stats_fd = bpf_enable_stats(BPF_STATS_RUN_TIME);
	अगर (CHECK_ATTR(stats_fd < 0, "enable_stats", "failed %d\n", त्रुटि_सं))
		वापस;

	skel = test_pkt_access__खोलो_and_load();
	अगर (CHECK_ATTR(!skel, "open_and_load", "failed\n"))
		जाओ cleanup;

	tattr.prog_fd = bpf_program__fd(skel->progs.test_pkt_access);

	err = bpf_prog_test_run_xattr(&tattr);
	CHECK_ATTR(err != -1 || त्रुटि_सं != ENOSPC || tattr.retval, "run",
	      "err %d errno %d retval %d\n", err, त्रुटि_सं, tattr.retval);

	CHECK_ATTR(tattr.data_size_out != माप(pkt_v4), "data_size_out",
	      "incorrect output size, want %zu have %u\n",
	      माप(pkt_v4), tattr.data_size_out);

	CHECK_ATTR(buf[5] != 0, "overflow",
	      "BPF_PROG_TEST_RUN ignored size hint\n");

	run_cnt += tattr.repeat;
	check_run_cnt(tattr.prog_fd, run_cnt);

	tattr.data_out = शून्य;
	tattr.data_size_out = 0;
	tattr.repeat = 2;
	त्रुटि_सं = 0;

	err = bpf_prog_test_run_xattr(&tattr);
	CHECK_ATTR(err || त्रुटि_सं || tattr.retval, "run_no_output",
	      "err %d errno %d retval %d\n", err, त्रुटि_सं, tattr.retval);

	tattr.data_size_out = 1;
	err = bpf_prog_test_run_xattr(&tattr);
	CHECK_ATTR(err != -EINVAL, "run_wrong_size_out", "err %d\n", err);

	run_cnt += tattr.repeat;
	check_run_cnt(tattr.prog_fd, run_cnt);

cleanup:
	अगर (skel)
		test_pkt_access__destroy(skel);
	अगर (stats_fd != -1)
		बंद(stats_fd);
पूर्ण
