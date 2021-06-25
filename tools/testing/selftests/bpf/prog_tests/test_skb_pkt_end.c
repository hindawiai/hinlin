<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश <test_progs.h>
#समावेश <network_helpers.h>
#समावेश "skb_pkt_end.skel.h"

अटल पूर्णांक sanity_run(काष्ठा bpf_program *prog)
अणु
	__u32 duration, retval;
	पूर्णांक err, prog_fd;

	prog_fd = bpf_program__fd(prog);
	err = bpf_prog_test_run(prog_fd, 1, &pkt_v4, माप(pkt_v4),
				शून्य, शून्य, &retval, &duration);
	अगर (CHECK(err || retval != 123, "test_run",
		  "err %d errno %d retval %d duration %d\n",
		  err, त्रुटि_सं, retval, duration))
		वापस -1;
	वापस 0;
पूर्ण

व्योम test_test_skb_pkt_end(व्योम)
अणु
	काष्ठा skb_pkt_end *skb_pkt_end_skel = शून्य;
	__u32 duration = 0;
	पूर्णांक err;

	skb_pkt_end_skel = skb_pkt_end__खोलो_and_load();
	अगर (CHECK(!skb_pkt_end_skel, "skb_pkt_end_skel_load", "skb_pkt_end skeleton failed\n"))
		जाओ cleanup;

	err = skb_pkt_end__attach(skb_pkt_end_skel);
	अगर (CHECK(err, "skb_pkt_end_attach", "skb_pkt_end attach failed: %d\n", err))
		जाओ cleanup;

	अगर (sanity_run(skb_pkt_end_skel->progs.मुख्य_prog))
		जाओ cleanup;

cleanup:
	skb_pkt_end__destroy(skb_pkt_end_skel);
पूर्ण
