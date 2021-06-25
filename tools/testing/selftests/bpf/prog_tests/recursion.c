<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */
#समावेश <test_progs.h>
#समावेश "recursion.skel.h"

व्योम test_recursion(व्योम)
अणु
	काष्ठा bpf_prog_info prog_info = अणुपूर्ण;
	__u32 prog_info_len = माप(prog_info);
	काष्ठा recursion *skel;
	पूर्णांक key = 0;
	पूर्णांक err;

	skel = recursion__खोलो_and_load();
	अगर (!ASSERT_OK_PTR(skel, "skel_open_and_load"))
		वापस;

	err = recursion__attach(skel);
	अगर (!ASSERT_OK(err, "skel_attach"))
		जाओ out;

	ASSERT_EQ(skel->bss->pass1, 0, "pass1 == 0");
	bpf_map_lookup_elem(bpf_map__fd(skel->maps.hash1), &key, 0);
	ASSERT_EQ(skel->bss->pass1, 1, "pass1 == 1");
	bpf_map_lookup_elem(bpf_map__fd(skel->maps.hash1), &key, 0);
	ASSERT_EQ(skel->bss->pass1, 2, "pass1 == 2");

	ASSERT_EQ(skel->bss->pass2, 0, "pass2 == 0");
	bpf_map_lookup_elem(bpf_map__fd(skel->maps.hash2), &key, 0);
	ASSERT_EQ(skel->bss->pass2, 1, "pass2 == 1");
	bpf_map_lookup_elem(bpf_map__fd(skel->maps.hash2), &key, 0);
	ASSERT_EQ(skel->bss->pass2, 2, "pass2 == 2");

	err = bpf_obj_get_info_by_fd(bpf_program__fd(skel->progs.on_lookup),
				     &prog_info, &prog_info_len);
	अगर (!ASSERT_OK(err, "get_prog_info"))
		जाओ out;
	ASSERT_EQ(prog_info.recursion_misses, 2, "recursion_misses");
out:
	recursion__destroy(skel);
पूर्ण
