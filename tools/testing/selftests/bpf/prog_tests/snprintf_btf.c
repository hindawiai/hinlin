<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <linux/btf.h>
#समावेश "netif_receive_skb.skel.h"

/* Demonstrate that bpf_snम_लिखो_btf succeeds and that various data types
 * are क्रमmatted correctly.
 */
व्योम test_snम_लिखो_btf(व्योम)
अणु
	काष्ठा netअगर_receive_skb *skel;
	काष्ठा netअगर_receive_skb__bss *bss;
	पूर्णांक err, duration = 0;

	skel = netअगर_receive_skb__खोलो();
	अगर (CHECK(!skel, "skel_open", "failed to open skeleton\n"))
		वापस;

	err = netअगर_receive_skb__load(skel);
	अगर (CHECK(err, "skel_load", "failed to load skeleton: %d\n", err))
		जाओ cleanup;

	bss = skel->bss;

	err = netअगर_receive_skb__attach(skel);
	अगर (CHECK(err, "skel_attach", "skeleton attach failed: %d\n", err))
		जाओ cleanup;

	/* generate receive event */
	err = प्रणाली("ping -c 1 127.0.0.1 > /dev/null");
	अगर (CHECK(err, "system", "ping failed: %d\n", err))
		जाओ cleanup;

	अगर (bss->skip) अणु
		म_लिखो("%s:SKIP:no __builtin_btf_type_id\n", __func__);
		test__skip();
		जाओ cleanup;
	पूर्ण

	/*
	 * Make sure netअगर_receive_skb program was triggered
	 * and it set expected वापस values from bpf_trace_prपूर्णांकk()s
	 * and all tests ran.
	 */
	अगर (!ASSERT_GT(bss->ret, 0, "bpf_snprintf_ret"))
		जाओ cleanup;

	अगर (CHECK(bss->ran_subtests == 0, "check if subtests ran",
		  "no subtests ran, did BPF program run?"))
		जाओ cleanup;

	अगर (CHECK(bss->num_subtests != bss->ran_subtests,
		  "check all subtests ran",
		  "only ran %d of %d tests\n", bss->num_subtests,
		  bss->ran_subtests))
		जाओ cleanup;

cleanup:
	netअगर_receive_skb__destroy(skel);
पूर्ण
