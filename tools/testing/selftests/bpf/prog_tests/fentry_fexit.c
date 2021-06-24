<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook */
#समावेश <test_progs.h>
#समावेश "fentry_test.skel.h"
#समावेश "fexit_test.skel.h"

व्योम test_fentry_fनिकास(व्योम)
अणु
	काष्ठा fentry_test *fentry_skel = शून्य;
	काष्ठा fनिकास_test *fनिकास_skel = शून्य;
	__u64 *fentry_res, *fनिकास_res;
	__u32 duration = 0, retval;
	पूर्णांक err, prog_fd, i;

	fentry_skel = fentry_test__खोलो_and_load();
	अगर (CHECK(!fentry_skel, "fentry_skel_load", "fentry skeleton failed\n"))
		जाओ बंद_prog;
	fनिकास_skel = fनिकास_test__खोलो_and_load();
	अगर (CHECK(!fनिकास_skel, "fexit_skel_load", "fexit skeleton failed\n"))
		जाओ बंद_prog;

	err = fentry_test__attach(fentry_skel);
	अगर (CHECK(err, "fentry_attach", "fentry attach failed: %d\n", err))
		जाओ बंद_prog;
	err = fनिकास_test__attach(fनिकास_skel);
	अगर (CHECK(err, "fexit_attach", "fexit attach failed: %d\n", err))
		जाओ बंद_prog;

	prog_fd = bpf_program__fd(fनिकास_skel->progs.test1);
	err = bpf_prog_test_run(prog_fd, 1, शून्य, 0,
				शून्य, शून्य, &retval, &duration);
	CHECK(err || retval, "ipv6",
	      "err %d errno %d retval %d duration %d\n",
	      err, त्रुटि_सं, retval, duration);

	fentry_res = (__u64 *)fentry_skel->bss;
	fनिकास_res = (__u64 *)fनिकास_skel->bss;
	म_लिखो("%lld\n", fentry_skel->bss->test1_result);
	क्रम (i = 0; i < 8; i++) अणु
		CHECK(fentry_res[i] != 1, "result",
		      "fentry_test%d failed err %lld\n", i + 1, fentry_res[i]);
		CHECK(fनिकास_res[i] != 1, "result",
		      "fexit_test%d failed err %lld\n", i + 1, fनिकास_res[i]);
	पूर्ण

बंद_prog:
	fentry_test__destroy(fentry_skel);
	fनिकास_test__destroy(fनिकास_skel);
पूर्ण
