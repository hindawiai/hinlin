<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2020 Google LLC.
 */

#समावेश <test_progs.h>
#समावेश "modify_return.skel.h"

#घोषणा LOWER(x) ((x) & 0xffff)
#घोषणा UPPER(x) ((x) >> 16)


अटल व्योम run_test(__u32 input_retval, __u16 want_side_effect, __s16 want_ret)
अणु
	काष्ठा modअगरy_वापस *skel = शून्य;
	पूर्णांक err, prog_fd;
	__u32 duration = 0, retval;
	__u16 side_effect;
	__s16 ret;

	skel = modअगरy_वापस__खोलो_and_load();
	अगर (CHECK(!skel, "skel_load", "modify_return skeleton failed\n"))
		जाओ cleanup;

	err = modअगरy_वापस__attach(skel);
	अगर (CHECK(err, "modify_return", "attach failed: %d\n", err))
		जाओ cleanup;

	skel->bss->input_retval = input_retval;
	prog_fd = bpf_program__fd(skel->progs.भ_शेष_ret_test);
	err = bpf_prog_test_run(prog_fd, 1, शून्य, 0, शून्य, 0,
				&retval, &duration);

	CHECK(err, "test_run", "err %d errno %d\n", err, त्रुटि_सं);

	side_effect = UPPER(retval);
	ret  = LOWER(retval);

	CHECK(ret != want_ret, "test_run",
	      "unexpected ret: %d, expected: %d\n", ret, want_ret);
	CHECK(side_effect != want_side_effect, "modify_return",
	      "unexpected side_effect: %d\n", side_effect);

	CHECK(skel->bss->fentry_result != 1, "modify_return",
	      "fentry failed\n");
	CHECK(skel->bss->fनिकास_result != 1, "modify_return",
	      "fexit failed\n");
	CHECK(skel->bss->भ_शेष_ret_result != 1, "modify_return",
	      "fmod_ret failed\n");

cleanup:
	modअगरy_वापस__destroy(skel);
पूर्ण

व्योम test_modअगरy_वापस(व्योम)
अणु
	run_test(0 /* input_retval */,
		 1 /* want_side_effect */,
		 4 /* want_ret */);
	run_test(-EINVAL /* input_retval */,
		 0 /* want_side_effect */,
		 -EINVAL /* want_ret */);
पूर्ण

