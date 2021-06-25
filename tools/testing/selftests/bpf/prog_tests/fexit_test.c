<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook */
#समावेश <test_progs.h>
#समावेश "fexit_test.skel.h"

अटल पूर्णांक fनिकास_test(काष्ठा fनिकास_test *fनिकास_skel)
अणु
	पूर्णांक err, prog_fd, i;
	__u32 duration = 0, retval;
	काष्ठा bpf_link *link;
	__u64 *result;

	err = fनिकास_test__attach(fनिकास_skel);
	अगर (!ASSERT_OK(err, "fexit_attach"))
		वापस err;

	/* Check that alपढ़ोy linked program can't be attached again. */
	link = bpf_program__attach(fनिकास_skel->progs.test1);
	अगर (!ASSERT_ERR_PTR(link, "fexit_attach_link"))
		वापस -1;

	prog_fd = bpf_program__fd(fनिकास_skel->progs.test1);
	err = bpf_prog_test_run(prog_fd, 1, शून्य, 0,
				शून्य, शून्य, &retval, &duration);
	ASSERT_OK(err, "test_run");
	ASSERT_EQ(retval, 0, "test_run");

	result = (__u64 *)fनिकास_skel->bss;
	क्रम (i = 0; i < माप(*fनिकास_skel->bss) / माप(__u64); i++) अणु
		अगर (!ASSERT_EQ(result[i], 1, "fexit_result"))
			वापस -1;
	पूर्ण

	fनिकास_test__detach(fनिकास_skel);

	/* zero results क्रम re-attach test */
	स_रखो(fनिकास_skel->bss, 0, माप(*fनिकास_skel->bss));
	वापस 0;
पूर्ण

व्योम test_fनिकास_test(व्योम)
अणु
	काष्ठा fनिकास_test *fनिकास_skel = शून्य;
	पूर्णांक err;

	fनिकास_skel = fनिकास_test__खोलो_and_load();
	अगर (!ASSERT_OK_PTR(fनिकास_skel, "fexit_skel_load"))
		जाओ cleanup;

	err = fनिकास_test(fनिकास_skel);
	अगर (!ASSERT_OK(err, "fexit_first_attach"))
		जाओ cleanup;

	err = fनिकास_test(fनिकास_skel);
	ASSERT_OK(err, "fexit_second_attach");

cleanup:
	fनिकास_test__destroy(fनिकास_skel);
पूर्ण
