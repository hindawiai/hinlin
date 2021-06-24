<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */

#समावेश <test_progs.h>
#समावेश <sys/syscall.h>
#समावेश "linked_vars.skel.h"

व्योम test_linked_vars(व्योम)
अणु
	पूर्णांक err;
	काष्ठा linked_vars *skel;

	skel = linked_vars__खोलो();
	अगर (!ASSERT_OK_PTR(skel, "skel_open"))
		वापस;

	skel->bss->input_bss1 = 1000;
	skel->bss->input_bss2 = 2000;
	skel->bss->input_bss_weak = 3000;

	err = linked_vars__load(skel);
	अगर (!ASSERT_OK(err, "skel_load"))
		जाओ cleanup;

	err = linked_vars__attach(skel);
	अगर (!ASSERT_OK(err, "skel_attach"))
		जाओ cleanup;

	/* trigger */
	syscall(SYS_getpgid);

	ASSERT_EQ(skel->bss->output_bss1, 1000 + 2000 + 3000, "output_bss1");
	ASSERT_EQ(skel->bss->output_bss2, 1000 + 2000 + 3000, "output_bss2");
	/* 10 comes from "winner" input_data_weak in first obj file */
	ASSERT_EQ(skel->bss->output_data1, 1 + 2 + 10, "output_bss1");
	ASSERT_EQ(skel->bss->output_data2, 1 + 2 + 10, "output_bss2");
	/* 100 comes from "winner" input_rodata_weak in first obj file */
	ASSERT_EQ(skel->bss->output_rodata1, 11 + 22 + 100, "output_weak1");
	ASSERT_EQ(skel->bss->output_rodata2, 11 + 22 + 100, "output_weak2");

cleanup:
	linked_vars__destroy(skel);
पूर्ण
