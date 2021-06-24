<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook

#समावेश <test_progs.h>
#समावेश <network_helpers.h>

#समावेश "map_ptr_kern.skel.h"

व्योम test_map_ptr(व्योम)
अणु
	काष्ठा map_ptr_kern *skel;
	__u32 duration = 0, retval;
	अक्षर buf[128];
	पूर्णांक err;
	पूर्णांक page_size = getpagesize();

	skel = map_ptr_kern__खोलो();
	अगर (!ASSERT_OK_PTR(skel, "skel_open"))
		वापस;

	err = bpf_map__set_max_entries(skel->maps.m_ringbuf, page_size);
	अगर (!ASSERT_OK(err, "bpf_map__set_max_entries"))
		जाओ cleanup;

	err = map_ptr_kern__load(skel);
	अगर (!ASSERT_OK(err, "skel_load"))
		जाओ cleanup;

	skel->bss->page_size = page_size;

	err = bpf_prog_test_run(bpf_program__fd(skel->progs.cg_skb), 1, &pkt_v4,
				माप(pkt_v4), buf, शून्य, &retval, शून्य);

	अगर (CHECK(err, "test_run", "err=%d errno=%d\n", err, त्रुटि_सं))
		जाओ cleanup;

	अगर (CHECK(!retval, "retval", "retval=%d map_type=%u line=%u\n", retval,
		  skel->bss->g_map_type, skel->bss->g_line))
		जाओ cleanup;

cleanup:
	map_ptr_kern__destroy(skel);
पूर्ण
