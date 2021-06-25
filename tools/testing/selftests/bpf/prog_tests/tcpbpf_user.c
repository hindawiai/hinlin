<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <network_helpers.h>

#समावेश "test_tcpbpf.h"
#समावेश "test_tcpbpf_kern.skel.h"

#घोषणा LO_ADDR6 "::1"
#घोषणा CG_NAME "/tcpbpf-user-test"

अटल __u32 duration;

अटल व्योम verअगरy_result(काष्ठा tcpbpf_globals *result)
अणु
	__u32 expected_events = ((1 << BPF_SOCK_OPS_TIMEOUT_INIT) |
				 (1 << BPF_SOCK_OPS_RWND_INIT) |
				 (1 << BPF_SOCK_OPS_TCP_CONNECT_CB) |
				 (1 << BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB) |
				 (1 << BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB) |
				 (1 << BPF_SOCK_OPS_NEEDS_ECN) |
				 (1 << BPF_SOCK_OPS_STATE_CB) |
				 (1 << BPF_SOCK_OPS_TCP_LISTEN_CB));

	/* check global map */
	CHECK(expected_events != result->event_map, "event_map",
	      "unexpected event_map: actual 0x%08x != expected 0x%08x\n",
	      result->event_map, expected_events);

	ASSERT_EQ(result->bytes_received, 501, "bytes_received");
	ASSERT_EQ(result->bytes_acked, 1002, "bytes_acked");
	ASSERT_EQ(result->data_segs_in, 1, "data_segs_in");
	ASSERT_EQ(result->data_segs_out, 1, "data_segs_out");
	ASSERT_EQ(result->bad_cb_test_rv, 0x80, "bad_cb_test_rv");
	ASSERT_EQ(result->good_cb_test_rv, 0, "good_cb_test_rv");
	ASSERT_EQ(result->num_listen, 1, "num_listen");

	/* 3 comes from one listening socket + both ends of the connection */
	ASSERT_EQ(result->num_बंद_events, 3, "num_close_events");

	/* check setsockopt क्रम SAVE_SYN */
	ASSERT_EQ(result->tcp_save_syn, 0, "tcp_save_syn");

	/* check माला_लोockopt क्रम SAVED_SYN */
	ASSERT_EQ(result->tcp_saved_syn, 1, "tcp_saved_syn");

	/* check माला_लोockopt क्रम winकरोw_clamp */
	ASSERT_EQ(result->winकरोw_clamp_client, 9216, "window_clamp_client");
	ASSERT_EQ(result->winकरोw_clamp_server, 9216, "window_clamp_server");
पूर्ण

अटल व्योम run_test(काष्ठा tcpbpf_globals *result)
अणु
	पूर्णांक listen_fd = -1, cli_fd = -1, accept_fd = -1;
	अक्षर buf[1000];
	पूर्णांक err = -1;
	पूर्णांक i, rv;

	listen_fd = start_server(AF_INET6, SOCK_STREAM, LO_ADDR6, 0, 0);
	अगर (CHECK(listen_fd == -1, "start_server", "listen_fd:%d errno:%d\n",
		  listen_fd, त्रुटि_सं))
		जाओ करोne;

	cli_fd = connect_to_fd(listen_fd, 0);
	अगर (CHECK(cli_fd == -1, "connect_to_fd(listen_fd)",
		  "cli_fd:%d errno:%d\n", cli_fd, त्रुटि_सं))
		जाओ करोne;

	accept_fd = accept(listen_fd, शून्य, शून्य);
	अगर (CHECK(accept_fd == -1, "accept(listen_fd)",
		  "accept_fd:%d errno:%d\n", accept_fd, त्रुटि_सं))
		जाओ करोne;

	/* Send 1000B of '+'s from cli_fd -> accept_fd */
	क्रम (i = 0; i < 1000; i++)
		buf[i] = '+';

	rv = send(cli_fd, buf, 1000, 0);
	अगर (CHECK(rv != 1000, "send(cli_fd)", "rv:%d errno:%d\n", rv, त्रुटि_सं))
		जाओ करोne;

	rv = recv(accept_fd, buf, 1000, 0);
	अगर (CHECK(rv != 1000, "recv(accept_fd)", "rv:%d errno:%d\n", rv, त्रुटि_सं))
		जाओ करोne;

	/* Send 500B of '.'s from accept_fd ->cli_fd */
	क्रम (i = 0; i < 500; i++)
		buf[i] = '.';

	rv = send(accept_fd, buf, 500, 0);
	अगर (CHECK(rv != 500, "send(accept_fd)", "rv:%d errno:%d\n", rv, त्रुटि_सं))
		जाओ करोne;

	rv = recv(cli_fd, buf, 500, 0);
	अगर (CHECK(rv != 500, "recv(cli_fd)", "rv:%d errno:%d\n", rv, त्रुटि_सं))
		जाओ करोne;

	/*
	 * shutकरोwn accept first to guarantee correct ordering क्रम
	 * bytes_received and bytes_acked when we go to verअगरy the results.
	 */
	shutकरोwn(accept_fd, SHUT_WR);
	err = recv(cli_fd, buf, 1, 0);
	अगर (CHECK(err, "recv(cli_fd) for fin", "err:%d errno:%d\n", err, त्रुटि_सं))
		जाओ करोne;

	shutकरोwn(cli_fd, SHUT_WR);
	err = recv(accept_fd, buf, 1, 0);
	CHECK(err, "recv(accept_fd) for fin", "err:%d errno:%d\n", err, त्रुटि_सं);
करोne:
	अगर (accept_fd != -1)
		बंद(accept_fd);
	अगर (cli_fd != -1)
		बंद(cli_fd);
	अगर (listen_fd != -1)
		बंद(listen_fd);

	अगर (!err)
		verअगरy_result(result);
पूर्ण

व्योम test_tcpbpf_user(व्योम)
अणु
	काष्ठा test_tcpbpf_kern *skel;
	पूर्णांक cg_fd = -1;

	skel = test_tcpbpf_kern__खोलो_and_load();
	अगर (CHECK(!skel, "open and load skel", "failed"))
		वापस;

	cg_fd = test__join_cgroup(CG_NAME);
	अगर (CHECK(cg_fd < 0, "test__join_cgroup(" CG_NAME ")",
		  "cg_fd:%d errno:%d", cg_fd, त्रुटि_सं))
		जाओ err;

	skel->links.bpf_testcb = bpf_program__attach_cgroup(skel->progs.bpf_testcb, cg_fd);
	अगर (!ASSERT_OK_PTR(skel->links.bpf_testcb, "attach_cgroup(bpf_testcb)"))
		जाओ err;

	run_test(&skel->bss->global);

err:
	अगर (cg_fd != -1)
		बंद(cg_fd);
	test_tcpbpf_kern__destroy(skel);
पूर्ण
