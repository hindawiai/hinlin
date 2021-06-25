<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook */
#समावेश <test_progs.h>
#समावेश "fentry_test.skel.h"

अटल पूर्णांक fentry_test(काष्ठा fentry_test *fentry_skel)
अणु
	पूर्णांक err, prog_fd, i;
	__u32 duration = 0, retval;
	काष्ठा bpf_link *link;
	__u64 *result;

	err = fentry_test__attach(fentry_skel);
	अगर (!ASSERT_OK(err, "fentry_attach"))
		वापस err;

	/* Check that alपढ़ोy linked program can't be attached again. */
	link = bpf_program__attach(fentry_skel->progs.test1);
	अगर (!ASSERT_ERR_PTR(link, "fentry_attach_link"))
		वापस -1;

	prog_fd = bpf_program__fd(fentry_skel->progs.test1);
	err = bpf_prog_test_run(prog_fd, 1, शून्य, 0,
				शून्य, शून्य, &retval, &duration);
	ASSERT_OK(err, "test_run");
	ASSERT_EQ(retval, 0, "test_run");

	result = (__u64 *)fentry_skel->bss;
	क्रम (i = 0; i < माप(*fentry_skel->bss) / माप(__u64); i++) अणु
		अगर (!ASSERT_EQ(result[i], 1, "fentry_result"))
			वापस -1;
	पूर्ण

	fentry_test__detach(fentry_skel);

	/* zero results क्रम re-attach test */
	स_रखो(fentry_skel->bss, 0, माप(*fentry_skel->bss));
	वापस 0;
पूर्ण

व्योम test_fentry_test(व्योम)
अणु
	काष्ठा fentry_test *fentry_skel = शून्य;
	पूर्णांक err;

	fentry_skel = fentry_test__खोलो_and_load();
	अगर (!ASSERT_OK_PTR(fentry_skel, "fentry_skel_load"))
		जाओ cleanup;

	err = fentry_test(fentry_skel);
	अगर (!ASSERT_OK(err, "fentry_first_attach"))
		जाओ cleanup;

	err = fentry_test(fentry_skel);
	ASSERT_OK(err, "fentry_second_attach");

cleanup:
	fentry_test__destroy(fentry_skel);
पूर्ण
