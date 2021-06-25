<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook

#समावेश <test_progs.h>

#समावेश "network_helpers.h"
#समावेश "cgroup_skb_sk_lookup_kern.skel.h"

अटल व्योम run_lookup_test(__u16 *g_serv_port, पूर्णांक out_sk)
अणु
	पूर्णांक serv_sk = -1, in_sk = -1, serv_in_sk = -1, err;
	काष्ठा sockaddr_in6 addr = अणुपूर्ण;
	socklen_t addr_len = माप(addr);
	__u32 duration = 0;

	serv_sk = start_server(AF_INET6, SOCK_STREAM, शून्य, 0, 0);
	अगर (CHECK(serv_sk < 0, "start_server", "failed to start server\n"))
		वापस;

	err = माला_लोockname(serv_sk, (काष्ठा sockaddr *)&addr, &addr_len);
	अगर (CHECK(err, "getsockname", "errno %d\n", त्रुटि_सं))
		जाओ cleanup;

	*g_serv_port = addr.sin6_port;

	/* Client outside of test cgroup should fail to connect by समयout. */
	err = connect_fd_to_fd(out_sk, serv_sk, 1000);
	अगर (CHECK(!err || त्रुटि_सं != EINPROGRESS, "connect_fd_to_fd",
		  "unexpected result err %d errno %d\n", err, त्रुटि_सं))
		जाओ cleanup;

	/* Client inside test cgroup should connect just fine. */
	in_sk = connect_to_fd(serv_sk, 0);
	अगर (CHECK(in_sk < 0, "connect_to_fd", "errno %d\n", त्रुटि_सं))
		जाओ cleanup;

	serv_in_sk = accept(serv_sk, शून्य, शून्य);
	अगर (CHECK(serv_in_sk < 0, "accept", "errno %d\n", त्रुटि_सं))
		जाओ cleanup;

cleanup:
	बंद(serv_in_sk);
	बंद(in_sk);
	बंद(serv_sk);
पूर्ण

अटल व्योम run_cgroup_bpf_test(स्थिर अक्षर *cg_path, पूर्णांक out_sk)
अणु
	काष्ठा cgroup_skb_sk_lookup_kern *skel;
	काष्ठा bpf_link *link;
	__u32 duration = 0;
	पूर्णांक cgfd = -1;

	skel = cgroup_skb_sk_lookup_kern__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open_load", "open_load failed\n"))
		वापस;

	cgfd = test__join_cgroup(cg_path);
	अगर (CHECK(cgfd < 0, "cgroup_join", "cgroup setup failed\n"))
		जाओ cleanup;

	link = bpf_program__attach_cgroup(skel->progs.ingress_lookup, cgfd);
	अगर (CHECK(IS_ERR(link), "cgroup_attach", "err: %ld\n", PTR_ERR(link)))
		जाओ cleanup;

	run_lookup_test(&skel->bss->g_serv_port, out_sk);

	bpf_link__destroy(link);

cleanup:
	बंद(cgfd);
	cgroup_skb_sk_lookup_kern__destroy(skel);
पूर्ण

व्योम test_cgroup_skb_sk_lookup(व्योम)
अणु
	स्थिर अक्षर *cg_path = "/foo";
	पूर्णांक out_sk;

	/* Create a socket beक्रमe joining testing cgroup so that its cgroup id
	 * dअगरfers from that of testing cgroup. Moving selftests process to
	 * testing cgroup won't change cgroup id of an alपढ़ोy created socket.
	 */
	out_sk = socket(AF_INET6, SOCK_STREAM, 0);
	अगर (CHECK_FAIL(out_sk < 0))
		वापस;

	run_cgroup_bpf_test(cg_path, out_sk);

	बंद(out_sk);
पूर्ण
