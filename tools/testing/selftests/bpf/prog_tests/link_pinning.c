<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश <test_progs.h>
#समावेश <sys/स्थिति.स>

#समावेश "test_link_pinning.skel.h"

अटल पूर्णांक duration = 0;

व्योम test_link_pinning_subtest(काष्ठा bpf_program *prog,
			       काष्ठा test_link_pinning__bss *bss)
अणु
	स्थिर अक्षर *link_pin_path = "/sys/fs/bpf/pinned_link_test";
	काष्ठा stat statbuf = अणुपूर्ण;
	काष्ठा bpf_link *link;
	पूर्णांक err, i;

	link = bpf_program__attach(prog);
	अगर (CHECK(IS_ERR(link), "link_attach", "err: %ld\n", PTR_ERR(link)))
		जाओ cleanup;

	bss->in = 1;
	usleep(1);
	CHECK(bss->out != 1, "res_check1", "exp %d, got %d\n", 1, bss->out);

	/* pin link */
	err = bpf_link__pin(link, link_pin_path);
	अगर (CHECK(err, "link_pin", "err: %d\n", err))
		जाओ cleanup;

	CHECK(म_भेद(link_pin_path, bpf_link__pin_path(link)), "pin_path1",
	      "exp %s, got %s\n", link_pin_path, bpf_link__pin_path(link));

	/* check that link was pinned */
	err = stat(link_pin_path, &statbuf);
	अगर (CHECK(err, "stat_link", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ cleanup;

	bss->in = 2;
	usleep(1);
	CHECK(bss->out != 2, "res_check2", "exp %d, got %d\n", 2, bss->out);

	/* destroy link, pinned link should keep program attached */
	bpf_link__destroy(link);
	link = शून्य;

	bss->in = 3;
	usleep(1);
	CHECK(bss->out != 3, "res_check3", "exp %d, got %d\n", 3, bss->out);

	/* re-खोलो link from BPFFS */
	link = bpf_link__खोलो(link_pin_path);
	अगर (CHECK(IS_ERR(link), "link_open", "err: %ld\n", PTR_ERR(link)))
		जाओ cleanup;

	CHECK(म_भेद(link_pin_path, bpf_link__pin_path(link)), "pin_path2",
	      "exp %s, got %s\n", link_pin_path, bpf_link__pin_path(link));

	/* unpin link from BPFFS, program still attached */
	err = bpf_link__unpin(link);
	अगर (CHECK(err, "link_unpin", "err: %d\n", err))
		जाओ cleanup;

	/* still active, as we have FD खोलो now */
	bss->in = 4;
	usleep(1);
	CHECK(bss->out != 4, "res_check4", "exp %d, got %d\n", 4, bss->out);

	bpf_link__destroy(link);
	link = शून्य;

	/* Validate it's finally detached.
	 * Actual detachment might get delayed a bit, so there is no reliable
	 * way to validate it immediately here, let's count up क्रम दीर्घ enough
	 * and see अगर eventually output stops being updated
	 */
	क्रम (i = 5; i < 10000; i++) अणु
		bss->in = i;
		usleep(1);
		अगर (bss->out == i - 1)
			अवरोध;
	पूर्ण
	CHECK(i == 10000, "link_attached", "got to iteration #%d\n", i);

cleanup:
	अगर (!IS_ERR(link))
		bpf_link__destroy(link);
पूर्ण

व्योम test_link_pinning(व्योम)
अणु
	काष्ठा test_link_pinning* skel;

	skel = test_link_pinning__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open", "failed to open skeleton\n"))
		वापस;

	अगर (test__start_subtest("pin_raw_tp"))
		test_link_pinning_subtest(skel->progs.raw_tp_prog, skel->bss);
	अगर (test__start_subtest("pin_tp_btf"))
		test_link_pinning_subtest(skel->progs.tp_btf_prog, skel->bss);

	test_link_pinning__destroy(skel);
पूर्ण
