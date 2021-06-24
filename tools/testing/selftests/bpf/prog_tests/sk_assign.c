<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Facebook
// Copyright (c) 2019 Cloudflare
// Copyright (c) 2020 Isovalent, Inc.
/*
 * Test that the socket assign program is able to redirect traffic towards a
 * socket, regardless of whether the port or address destination of the traffic
 * matches the port.
 */

#घोषणा _GNU_SOURCE
#समावेश <fcntl.h>
#समावेश <संकेत.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>

#समावेश "test_progs.h"

#घोषणा BIND_PORT 1234
#घोषणा CONNECT_PORT 4321
#घोषणा TEST_DADDR (0xC0A80203)
#घोषणा NS_SELF "/proc/self/ns/net"
#घोषणा SERVER_MAP_PATH "/sys/fs/bpf/tc/globals/server_map"

अटल स्थिर काष्ठा समयval समयo_sec = अणु .tv_sec = 3 पूर्ण;
अटल स्थिर माप_प्रकार समयo_optlen = माप(समयo_sec);
अटल पूर्णांक stop, duration;

अटल bool
configure_stack(व्योम)
अणु
	अक्षर tc_cmd[बफ_मान];

	/* Move to a new networking namespace */
	अगर (CHECK_FAIL(unshare(CLONE_NEWNET)))
		वापस false;

	/* Configure necessary links, routes */
	अगर (CHECK_FAIL(प्रणाली("ip link set dev lo up")))
		वापस false;
	अगर (CHECK_FAIL(प्रणाली("ip route add local default dev lo")))
		वापस false;
	अगर (CHECK_FAIL(प्रणाली("ip -6 route add local default dev lo")))
		वापस false;

	/* Load qdisc, BPF program */
	अगर (CHECK_FAIL(प्रणाली("tc qdisc add dev lo clsact")))
		वापस false;
	प्र_लिखो(tc_cmd, "%s %s %s %s", "tc filter add dev lo ingress bpf",
		       "direct-action object-file ./test_sk_assign.o",
		       "section classifier/sk_assign_test",
		       (env.verbosity < VERBOSE_VERY) ? " 2>/dev/null" : "verbose");
	अगर (CHECK(प्रणाली(tc_cmd), "BPF load failed;",
		  "run with -vv for more info\n"))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक
start_server(स्थिर काष्ठा sockaddr *addr, socklen_t len, पूर्णांक type)
अणु
	पूर्णांक fd;

	fd = socket(addr->sa_family, type, 0);
	अगर (CHECK_FAIL(fd == -1))
		जाओ out;
	अगर (CHECK_FAIL(setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &समयo_sec,
				  समयo_optlen)))
		जाओ बंद_out;
	अगर (CHECK_FAIL(bind(fd, addr, len) == -1))
		जाओ बंद_out;
	अगर (type == SOCK_STREAM && CHECK_FAIL(listen(fd, 128) == -1))
		जाओ बंद_out;

	जाओ out;
बंद_out:
	बंद(fd);
	fd = -1;
out:
	वापस fd;
पूर्ण

अटल पूर्णांक
connect_to_server(स्थिर काष्ठा sockaddr *addr, socklen_t len, पूर्णांक type)
अणु
	पूर्णांक fd = -1;

	fd = socket(addr->sa_family, type, 0);
	अगर (CHECK_FAIL(fd == -1))
		जाओ out;
	अगर (CHECK_FAIL(setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &समयo_sec,
				  समयo_optlen)))
		जाओ बंद_out;
	अगर (CHECK_FAIL(connect(fd, addr, len)))
		जाओ बंद_out;

	जाओ out;
बंद_out:
	बंद(fd);
	fd = -1;
out:
	वापस fd;
पूर्ण

अटल in_port_t
get_port(पूर्णांक fd)
अणु
	काष्ठा sockaddr_storage ss;
	socklen_t slen = माप(ss);
	in_port_t port = 0;

	अगर (CHECK_FAIL(माला_लोockname(fd, (काष्ठा sockaddr *)&ss, &slen)))
		वापस port;

	चयन (ss.ss_family) अणु
	हाल AF_INET:
		port = ((काष्ठा sockaddr_in *)&ss)->sin_port;
		अवरोध;
	हाल AF_INET6:
		port = ((काष्ठा sockaddr_in6 *)&ss)->sin6_port;
		अवरोध;
	शेष:
		CHECK(1, "Invalid address family", "%d\n", ss.ss_family);
	पूर्ण
	वापस port;
पूर्ण

अटल sमाप_प्रकार
rcv_msg(पूर्णांक srv_client, पूर्णांक type)
अणु
	काष्ठा sockaddr_storage ss;
	अक्षर buf[बफ_मान];
	socklen_t slen;

	अगर (type == SOCK_STREAM)
		वापस पढ़ो(srv_client, &buf, माप(buf));
	अन्यथा
		वापस recvfrom(srv_client, &buf, माप(buf), 0,
				(काष्ठा sockaddr *)&ss, &slen);
पूर्ण

अटल पूर्णांक
run_test(पूर्णांक server_fd, स्थिर काष्ठा sockaddr *addr, socklen_t len, पूर्णांक type)
अणु
	पूर्णांक client = -1, srv_client = -1;
	अक्षर buf[] = "testing";
	in_port_t port;
	पूर्णांक ret = 1;

	client = connect_to_server(addr, len, type);
	अगर (client == -1) अणु
		लिखो_त्रुटि("Cannot connect to server");
		जाओ out;
	पूर्ण

	अगर (type == SOCK_STREAM) अणु
		srv_client = accept(server_fd, शून्य, शून्य);
		अगर (CHECK_FAIL(srv_client == -1)) अणु
			लिखो_त्रुटि("Can't accept connection");
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		srv_client = server_fd;
	पूर्ण
	अगर (CHECK_FAIL(ग_लिखो(client, buf, माप(buf)) != माप(buf))) अणु
		लिखो_त्रुटि("Can't write on client");
		जाओ out;
	पूर्ण
	अगर (CHECK_FAIL(rcv_msg(srv_client, type) != माप(buf))) अणु
		लिखो_त्रुटि("Can't read on server");
		जाओ out;
	पूर्ण

	port = get_port(srv_client);
	अगर (CHECK_FAIL(!port))
		जाओ out;
	/* SOCK_STREAM is connected via accept(), so the server's local address
	 * will be the CONNECT_PORT rather than the BIND port that corresponds
	 * to the listen socket. SOCK_DGRAM on the other hand is connectionless
	 * so we can't really do the same check there; the server doesn't ever
	 * create a socket with CONNECT_PORT.
	 */
	अगर (type == SOCK_STREAM &&
	    CHECK(port != htons(CONNECT_PORT), "Expected", "port %u but got %u",
		  CONNECT_PORT, ntohs(port)))
		जाओ out;
	अन्यथा अगर (type == SOCK_DGRAM &&
		 CHECK(port != htons(BIND_PORT), "Expected",
		       "port %u but got %u", BIND_PORT, ntohs(port)))
		जाओ out;

	ret = 0;
out:
	बंद(client);
	अगर (srv_client != server_fd)
		बंद(srv_client);
	अगर (ret)
		WRITE_ONCE(stop, 1);
	वापस ret;
पूर्ण

अटल व्योम
prepare_addr(काष्ठा sockaddr *addr, पूर्णांक family, __u16 port, bool reग_लिखो_addr)
अणु
	काष्ठा sockaddr_in *addr4;
	काष्ठा sockaddr_in6 *addr6;

	चयन (family) अणु
	हाल AF_INET:
		addr4 = (काष्ठा sockaddr_in *)addr;
		स_रखो(addr4, 0, माप(*addr4));
		addr4->sin_family = family;
		addr4->sin_port = htons(port);
		अगर (reग_लिखो_addr)
			addr4->sin_addr.s_addr = htonl(TEST_DADDR);
		अन्यथा
			addr4->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		अवरोध;
	हाल AF_INET6:
		addr6 = (काष्ठा sockaddr_in6 *)addr;
		स_रखो(addr6, 0, माप(*addr6));
		addr6->sin6_family = family;
		addr6->sin6_port = htons(port);
		addr6->sin6_addr = in6addr_loopback;
		अगर (reग_लिखो_addr)
			addr6->sin6_addr.s6_addr32[3] = htonl(TEST_DADDR);
		अवरोध;
	शेष:
		ख_लिखो(मानक_त्रुटि, "Invalid family %d", family);
	पूर्ण
पूर्ण

काष्ठा test_sk_cfg अणु
	स्थिर अक्षर *name;
	पूर्णांक family;
	काष्ठा sockaddr *addr;
	socklen_t len;
	पूर्णांक type;
	bool reग_लिखो_addr;
पूर्ण;

#घोषणा TEST(NAME, FAMILY, TYPE, REWRITE)				\
अणु									\
	.name = NAME,							\
	.family = FAMILY,						\
	.addr = (FAMILY == AF_INET) ? (काष्ठा sockaddr *)&addr4		\
				    : (काष्ठा sockaddr *)&addr6,	\
	.len = (FAMILY == AF_INET) ? माप(addr4) : माप(addr6),	\
	.type = TYPE,							\
	.reग_लिखो_addr = REWRITE,					\
पूर्ण

व्योम test_sk_assign(व्योम)
अणु
	काष्ठा sockaddr_in addr4;
	काष्ठा sockaddr_in6 addr6;
	काष्ठा test_sk_cfg tests[] = अणु
		TEST("ipv4 tcp port redir", AF_INET, SOCK_STREAM, false),
		TEST("ipv4 tcp addr redir", AF_INET, SOCK_STREAM, true),
		TEST("ipv6 tcp port redir", AF_INET6, SOCK_STREAM, false),
		TEST("ipv6 tcp addr redir", AF_INET6, SOCK_STREAM, true),
		TEST("ipv4 udp port redir", AF_INET, SOCK_DGRAM, false),
		TEST("ipv4 udp addr redir", AF_INET, SOCK_DGRAM, true),
		TEST("ipv6 udp port redir", AF_INET6, SOCK_DGRAM, false),
		TEST("ipv6 udp addr redir", AF_INET6, SOCK_DGRAM, true),
	पूर्ण;
	__s64 server = -1;
	पूर्णांक server_map;
	पूर्णांक self_net;
	पूर्णांक i;

	self_net = खोलो(NS_SELF, O_RDONLY);
	अगर (CHECK_FAIL(self_net < 0)) अणु
		लिखो_त्रुटि("Unable to open "NS_SELF);
		वापस;
	पूर्ण

	अगर (!configure_stack()) अणु
		लिखो_त्रुटि("configure_stack");
		जाओ cleanup;
	पूर्ण

	server_map = bpf_obj_get(SERVER_MAP_PATH);
	अगर (CHECK_FAIL(server_map < 0)) अणु
		लिखो_त्रुटि("Unable to open " SERVER_MAP_PATH);
		जाओ cleanup;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(tests) && !READ_ONCE(stop); i++) अणु
		काष्ठा test_sk_cfg *test = &tests[i];
		स्थिर काष्ठा sockaddr *addr;
		स्थिर पूर्णांक zero = 0;
		पूर्णांक err;

		अगर (!test__start_subtest(test->name))
			जारी;
		prepare_addr(test->addr, test->family, BIND_PORT, false);
		addr = (स्थिर काष्ठा sockaddr *)test->addr;
		server = start_server(addr, test->len, test->type);
		अगर (server == -1)
			जाओ बंद;

		err = bpf_map_update_elem(server_map, &zero, &server, BPF_ANY);
		अगर (CHECK_FAIL(err)) अणु
			लिखो_त्रुटि("Unable to update server_map");
			जाओ बंद;
		पूर्ण

		/* connect to unbound ports */
		prepare_addr(test->addr, test->family, CONNECT_PORT,
			     test->reग_लिखो_addr);
		अगर (run_test(server, addr, test->len, test->type))
			जाओ बंद;

		बंद(server);
		server = -1;
	पूर्ण

बंद:
	बंद(server);
	बंद(server_map);
cleanup:
	अगर (CHECK_FAIL(unlink(SERVER_MAP_PATH)))
		लिखो_त्रुटि("Unable to unlink " SERVER_MAP_PATH);
	अगर (CHECK_FAIL(setns(self_net, CLONE_NEWNET)))
		लिखो_त्रुटि("Failed to setns("NS_SELF")");
	बंद(self_net);
पूर्ण
