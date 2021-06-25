<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Cloudflare
/*
 * Tests क्रम sockmap/sockhash holding kTLS sockets.
 */

#समावेश "test_progs.h"

#घोषणा MAX_TEST_NAME 80
#घोषणा TCP_ULP 31

अटल पूर्णांक tcp_server(पूर्णांक family)
अणु
	पूर्णांक err, s;

	s = socket(family, SOCK_STREAM, 0);
	अगर (CHECK_FAIL(s == -1)) अणु
		लिखो_त्रुटि("socket");
		वापस -1;
	पूर्ण

	err = listen(s, SOMAXCONN);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("listen");
		वापस -1;
	पूर्ण

	वापस s;
पूर्ण

अटल पूर्णांक disconnect(पूर्णांक fd)
अणु
	काष्ठा sockaddr unspec = अणु AF_UNSPEC पूर्ण;

	वापस connect(fd, &unspec, माप(unspec));
पूर्ण

/* Disconnect (unhash) a kTLS socket after removing it from sockmap. */
अटल व्योम test_sockmap_ktls_disconnect_after_delete(पूर्णांक family, पूर्णांक map)
अणु
	काष्ठा sockaddr_storage addr = अणु0पूर्ण;
	socklen_t len = माप(addr);
	पूर्णांक err, cli, srv, zero = 0;

	srv = tcp_server(family);
	अगर (srv == -1)
		वापस;

	err = माला_लोockname(srv, (काष्ठा sockaddr *)&addr, &len);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("getsockopt");
		जाओ बंद_srv;
	पूर्ण

	cli = socket(family, SOCK_STREAM, 0);
	अगर (CHECK_FAIL(cli == -1)) अणु
		लिखो_त्रुटि("socket");
		जाओ बंद_srv;
	पूर्ण

	err = connect(cli, (काष्ठा sockaddr *)&addr, len);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("connect");
		जाओ बंद_cli;
	पूर्ण

	err = bpf_map_update_elem(map, &zero, &cli, 0);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("bpf_map_update_elem");
		जाओ बंद_cli;
	पूर्ण

	err = setsockopt(cli, IPPROTO_TCP, TCP_ULP, "tls", म_माप("tls"));
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("setsockopt(TCP_ULP)");
		जाओ बंद_cli;
	पूर्ण

	err = bpf_map_delete_elem(map, &zero);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("bpf_map_delete_elem");
		जाओ बंद_cli;
	पूर्ण

	err = disconnect(cli);
	अगर (CHECK_FAIL(err))
		लिखो_त्रुटि("disconnect");

बंद_cli:
	बंद(cli);
बंद_srv:
	बंद(srv);
पूर्ण

अटल व्योम run_tests(पूर्णांक family, क्रमागत bpf_map_type map_type)
अणु
	अक्षर test_name[MAX_TEST_NAME];
	पूर्णांक map;

	map = bpf_create_map(map_type, माप(पूर्णांक), माप(पूर्णांक), 1, 0);
	अगर (CHECK_FAIL(map == -1)) अणु
		लिखो_त्रुटि("bpf_map_create");
		वापस;
	पूर्ण

	snम_लिखो(test_name, MAX_TEST_NAME,
		 "sockmap_ktls disconnect_after_delete %s %s",
		 family == AF_INET ? "IPv4" : "IPv6",
		 map_type == BPF_MAP_TYPE_SOCKMAP ? "SOCKMAP" : "SOCKHASH");
	अगर (!test__start_subtest(test_name))
		वापस;

	test_sockmap_ktls_disconnect_after_delete(family, map);

	बंद(map);
पूर्ण

व्योम test_sockmap_ktls(व्योम)
अणु
	run_tests(AF_INET, BPF_MAP_TYPE_SOCKMAP);
	run_tests(AF_INET, BPF_MAP_TYPE_SOCKHASH);
	run_tests(AF_INET6, BPF_MAP_TYPE_SOCKMAP);
	run_tests(AF_INET6, BPF_MAP_TYPE_SOCKHASH);
पूर्ण
