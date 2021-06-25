<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook */

#समावेश <test_progs.h>
#समावेश "test_static_linked.skel.h"

व्योम test_अटल_linked(व्योम)
अणु
	पूर्णांक err;
	काष्ठा test_अटल_linked* skel;

	skel = test_अटल_linked__खोलो();
	अगर (!ASSERT_OK_PTR(skel, "skel_open"))
		वापस;

	skel->rodata->rovar1 = 1;
	skel->bss->अटल_var1 = 2;
	skel->bss->अटल_var11 = 3;

	skel->rodata->rovar2 = 4;
	skel->bss->अटल_var2 = 5;
	skel->bss->अटल_var22 = 6;

	err = test_अटल_linked__load(skel);
	अगर (!ASSERT_OK(err, "skel_load"))
		जाओ cleanup;

	err = test_अटल_linked__attach(skel);
	अगर (!ASSERT_OK(err, "skel_attach"))
		जाओ cleanup;

	/* trigger */
	usleep(1);

	ASSERT_EQ(skel->bss->var1, 1 * 2 + 2 + 3, "var1");
	ASSERT_EQ(skel->bss->var2, 4 * 3 + 5 + 6, "var2");

cleanup:
	test_अटल_linked__destroy(skel);
पूर्ण
