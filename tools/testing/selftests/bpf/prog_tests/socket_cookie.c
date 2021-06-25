<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Google LLC.
// Copyright (c) 2018 Facebook

#समावेश <test_progs.h>
#समावेश "socket_cookie_prog.skel.h"
#समावेश "network_helpers.h"

अटल पूर्णांक duration;

काष्ठा socket_cookie अणु
	__u64 cookie_key;
	__u32 cookie_value;
पूर्ण;

व्योम test_socket_cookie(व्योम)
अणु
	पूर्णांक server_fd = 0, client_fd = 0, cgroup_fd = 0, err = 0;
	socklen_t addr_len = माप(काष्ठा sockaddr_in6);
	काष्ठा socket_cookie_prog *skel;
	__u32 cookie_expected_value;
	काष्ठा sockaddr_in6 addr;
	काष्ठा socket_cookie val;

	skel = socket_cookie_prog__खोलो_and_load();
	अगर (!ASSERT_OK_PTR(skel, "skel_open"))
		वापस;

	cgroup_fd = test__join_cgroup("/socket_cookie");
	अगर (CHECK(cgroup_fd < 0, "join_cgroup", "cgroup creation failed\n"))
		जाओ out;

	skel->links.set_cookie = bpf_program__attach_cgroup(
		skel->progs.set_cookie, cgroup_fd);
	अगर (!ASSERT_OK_PTR(skel->links.set_cookie, "prog_attach"))
		जाओ बंद_cgroup_fd;

	skel->links.update_cookie_sockops = bpf_program__attach_cgroup(
		skel->progs.update_cookie_sockops, cgroup_fd);
	अगर (!ASSERT_OK_PTR(skel->links.update_cookie_sockops, "prog_attach"))
		जाओ बंद_cgroup_fd;

	skel->links.update_cookie_tracing = bpf_program__attach(
		skel->progs.update_cookie_tracing);
	अगर (!ASSERT_OK_PTR(skel->links.update_cookie_tracing, "prog_attach"))
		जाओ बंद_cgroup_fd;

	server_fd = start_server(AF_INET6, SOCK_STREAM, "::1", 0, 0);
	अगर (CHECK(server_fd < 0, "start_server", "errno %d\n", त्रुटि_सं))
		जाओ बंद_cgroup_fd;

	client_fd = connect_to_fd(server_fd, 0);
	अगर (CHECK(client_fd < 0, "connect_to_fd", "errno %d\n", त्रुटि_सं))
		जाओ बंद_server_fd;

	err = bpf_map_lookup_elem(bpf_map__fd(skel->maps.socket_cookies),
				  &client_fd, &val);
	अगर (!ASSERT_OK(err, "map_lookup(socket_cookies)"))
		जाओ बंद_client_fd;

	err = माला_लोockname(client_fd, (काष्ठा sockaddr *)&addr, &addr_len);
	अगर (!ASSERT_OK(err, "getsockname"))
		जाओ बंद_client_fd;

	cookie_expected_value = (ntohs(addr.sin6_port) << 8) | 0xFF;
	ASSERT_EQ(val.cookie_value, cookie_expected_value, "cookie_value");

बंद_client_fd:
	बंद(client_fd);
बंद_server_fd:
	बंद(server_fd);
बंद_cgroup_fd:
	बंद(cgroup_fd);
out:
	socket_cookie_prog__destroy(skel);
पूर्ण
