<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश "test_enable_stats.skel.h"

व्योम test_enable_stats(व्योम)
अणु
	काष्ठा test_enable_stats *skel;
	पूर्णांक stats_fd, err, prog_fd;
	काष्ठा bpf_prog_info info;
	__u32 info_len = माप(info);
	पूर्णांक duration = 0;

	skel = test_enable_stats__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open_and_load", "skeleton open/load failed\n"))
		वापस;

	stats_fd = bpf_enable_stats(BPF_STATS_RUN_TIME);
	अगर (CHECK(stats_fd < 0, "get_stats_fd", "failed %d\n", त्रुटि_सं)) अणु
		test_enable_stats__destroy(skel);
		वापस;
	पूर्ण

	err = test_enable_stats__attach(skel);
	अगर (CHECK(err, "attach_raw_tp", "err %d\n", err))
		जाओ cleanup;

	test_enable_stats__detach(skel);

	prog_fd = bpf_program__fd(skel->progs.test_enable_stats);
	स_रखो(&info, 0, info_len);
	err = bpf_obj_get_info_by_fd(prog_fd, &info, &info_len);
	अगर (CHECK(err, "get_prog_info",
		  "failed to get bpf_prog_info for fd %d\n", prog_fd))
		जाओ cleanup;
	अगर (CHECK(info.run_समय_ns == 0, "check_stats_enabled",
		  "failed to enable run_time_ns stats\n"))
		जाओ cleanup;

	CHECK(info.run_cnt != skel->bss->count, "check_run_cnt_valid",
	      "invalid run_cnt stats\n");

cleanup:
	test_enable_stats__destroy(skel);
	बंद(stats_fd);
पूर्ण
