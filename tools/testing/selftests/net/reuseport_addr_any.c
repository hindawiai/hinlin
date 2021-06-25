<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Test that sockets listening on a specअगरic address are preferred
 * over sockets listening on addr_any.
 */

#घोषणा _GNU_SOURCE

#समावेश <arpa/inet.h>
#समावेश <त्रुटिसं.स>
#समावेश <error.h>
#समावेश <linux/dccp.h>
#समावेश <linux/in.h>
#समावेश <linux/unistd.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/epoll.h>
#समावेश <sys/types.h>
#समावेश <sys/socket.h>
#समावेश <unistd.h>

#अगर_अघोषित SOL_DCCP
#घोषणा SOL_DCCP 269
#पूर्ण_अगर

अटल स्थिर अक्षर *IP4_ADDR = "127.0.0.1";
अटल स्थिर अक्षर *IP6_ADDR = "::1";
अटल स्थिर अक्षर *IP4_MAPPED6 = "::ffff:127.0.0.1";

अटल स्थिर पूर्णांक PORT = 8888;

अटल व्योम build_rcv_fd(पूर्णांक family, पूर्णांक proto, पूर्णांक *rcv_fds, पूर्णांक count,
			 स्थिर अक्षर *addr_str)
अणु
	काष्ठा sockaddr_in  addr4 = अणु0पूर्ण;
	काष्ठा sockaddr_in6 addr6 = अणु0पूर्ण;
	काष्ठा sockaddr *addr;
	पूर्णांक opt, i, sz;

	स_रखो(&addr, 0, माप(addr));

	चयन (family) अणु
	हाल AF_INET:
		addr4.sin_family = family;
		अगर (!addr_str)
			addr4.sin_addr.s_addr = htonl(INADDR_ANY);
		अन्यथा अगर (!inet_pton(family, addr_str, &addr4.sin_addr.s_addr))
			error(1, त्रुटि_सं, "inet_pton failed: %s", addr_str);
		addr4.sin_port = htons(PORT);
		sz = माप(addr4);
		addr = (काष्ठा sockaddr *)&addr4;
		अवरोध;
	हाल AF_INET6:
		addr6.sin6_family = AF_INET6;
		अगर (!addr_str)
			addr6.sin6_addr = in6addr_any;
		अन्यथा अगर (!inet_pton(family, addr_str, &addr6.sin6_addr))
			error(1, त्रुटि_सं, "inet_pton failed: %s", addr_str);
		addr6.sin6_port = htons(PORT);
		sz = माप(addr6);
		addr = (काष्ठा sockaddr *)&addr6;
		अवरोध;
	शेष:
		error(1, 0, "Unsupported family %d", family);
		/* clang करोes not recognize error() above as terminating
		 * the program, so it complains that saddr, sz are
		 * not initialized when this code path is taken. Silence it.
		 */
		वापस;
	पूर्ण

	क्रम (i = 0; i < count; ++i) अणु
		rcv_fds[i] = socket(family, proto, 0);
		अगर (rcv_fds[i] < 0)
			error(1, त्रुटि_सं, "failed to create receive socket");

		opt = 1;
		अगर (setsockopt(rcv_fds[i], SOL_SOCKET, SO_REUSEPORT, &opt,
			       माप(opt)))
			error(1, त्रुटि_सं, "failed to set SO_REUSEPORT");

		अगर (bind(rcv_fds[i], addr, sz))
			error(1, त्रुटि_सं, "failed to bind receive socket");

		अगर (proto == SOCK_STREAM && listen(rcv_fds[i], 10))
			error(1, त्रुटि_सं, "tcp: failed to listen on receive port");
		अन्यथा अगर (proto == SOCK_DCCP) अणु
			अगर (setsockopt(rcv_fds[i], SOL_DCCP,
					DCCP_SOCKOPT_SERVICE,
					&(पूर्णांक) अणुhtonl(42)पूर्ण, माप(पूर्णांक)))
				error(1, त्रुटि_सं, "failed to setsockopt");

			अगर (listen(rcv_fds[i], 10))
				error(1, त्रुटि_सं, "dccp: failed to listen on receive port");
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक connect_and_send(पूर्णांक family, पूर्णांक proto)
अणु
	काष्ठा sockaddr_in  saddr4 = अणु0पूर्ण;
	काष्ठा sockaddr_in  daddr4 = अणु0पूर्ण;
	काष्ठा sockaddr_in6 saddr6 = अणु0पूर्ण;
	काष्ठा sockaddr_in6 daddr6 = अणु0पूर्ण;
	काष्ठा sockaddr *saddr, *daddr;
	पूर्णांक fd, sz;

	चयन (family) अणु
	हाल AF_INET:
		saddr4.sin_family = AF_INET;
		saddr4.sin_addr.s_addr = htonl(INADDR_ANY);
		saddr4.sin_port = 0;

		daddr4.sin_family = AF_INET;
		अगर (!inet_pton(family, IP4_ADDR, &daddr4.sin_addr.s_addr))
			error(1, त्रुटि_सं, "inet_pton failed: %s", IP4_ADDR);
		daddr4.sin_port = htons(PORT);

		sz = माप(saddr4);
		saddr = (काष्ठा sockaddr *)&saddr4;
		daddr = (काष्ठा sockaddr *)&daddr4;
	अवरोध;
	हाल AF_INET6:
		saddr6.sin6_family = AF_INET6;
		saddr6.sin6_addr = in6addr_any;

		daddr6.sin6_family = AF_INET6;
		अगर (!inet_pton(family, IP6_ADDR, &daddr6.sin6_addr))
			error(1, त्रुटि_सं, "inet_pton failed: %s", IP6_ADDR);
		daddr6.sin6_port = htons(PORT);

		sz = माप(saddr6);
		saddr = (काष्ठा sockaddr *)&saddr6;
		daddr = (काष्ठा sockaddr *)&daddr6;
	अवरोध;
	शेष:
		error(1, 0, "Unsupported family %d", family);
		/* clang करोes not recognize error() above as terminating
		 * the program, so it complains that saddr, daddr, sz are
		 * not initialized when this code path is taken. Silence it.
		 */
		वापस -1;
	पूर्ण

	fd = socket(family, proto, 0);
	अगर (fd < 0)
		error(1, त्रुटि_सं, "failed to create send socket");

	अगर (proto == SOCK_DCCP &&
		setsockopt(fd, SOL_DCCP, DCCP_SOCKOPT_SERVICE,
				&(पूर्णांक)अणुhtonl(42)पूर्ण, माप(पूर्णांक)))
		error(1, त्रुटि_सं, "failed to setsockopt");

	अगर (bind(fd, saddr, sz))
		error(1, त्रुटि_सं, "failed to bind send socket");

	अगर (connect(fd, daddr, sz))
		error(1, त्रुटि_सं, "failed to connect send socket");

	अगर (send(fd, "a", 1, 0) < 0)
		error(1, त्रुटि_सं, "failed to send message");

	वापस fd;
पूर्ण

अटल पूर्णांक receive_once(पूर्णांक epfd, पूर्णांक proto)
अणु
	काष्ठा epoll_event ev;
	पूर्णांक i, fd;
	अक्षर buf[8];

	i = epoll_रुको(epfd, &ev, 1, 3);
	अगर (i < 0)
		error(1, त्रुटि_सं, "epoll_wait failed");

	अगर (proto == SOCK_STREAM || proto == SOCK_DCCP) अणु
		fd = accept(ev.data.fd, शून्य, शून्य);
		अगर (fd < 0)
			error(1, त्रुटि_सं, "failed to accept");
		i = recv(fd, buf, माप(buf), 0);
		बंद(fd);
	पूर्ण अन्यथा अणु
		i = recv(ev.data.fd, buf, माप(buf), 0);
	पूर्ण

	अगर (i < 0)
		error(1, त्रुटि_सं, "failed to recv");

	वापस ev.data.fd;
पूर्ण

अटल व्योम test(पूर्णांक *rcv_fds, पूर्णांक count, पूर्णांक family, पूर्णांक proto, पूर्णांक fd)
अणु
	काष्ठा epoll_event ev;
	पूर्णांक epfd, i, send_fd, recv_fd;

	epfd = epoll_create(1);
	अगर (epfd < 0)
		error(1, त्रुटि_सं, "failed to create epoll");

	ev.events = EPOLLIN;
	क्रम (i = 0; i < count; ++i) अणु
		ev.data.fd = rcv_fds[i];
		अगर (epoll_ctl(epfd, EPOLL_CTL_ADD, rcv_fds[i], &ev))
			error(1, त्रुटि_सं, "failed to register sock epoll");
	पूर्ण

	send_fd = connect_and_send(family, proto);

	recv_fd = receive_once(epfd, proto);
	अगर (recv_fd != fd)
		error(1, 0, "received on an unexpected socket");

	बंद(send_fd);
	बंद(epfd);
पूर्ण


अटल व्योम run_one_test(पूर्णांक fam_send, पूर्णांक fam_rcv, पूर्णांक proto,
			 स्थिर अक्षर *addr_str)
अणु
	/* Below we test that a socket listening on a specअगरic address
	 * is always selected in preference over a socket listening
	 * on addr_any. Bugs where this is not the हाल often result
	 * in sockets created first or last to get picked. So below
	 * we make sure that there are always addr_any sockets created
	 * beक्रमe and after a specअगरic socket is created.
	 */
	पूर्णांक rcv_fds[10], i;

	build_rcv_fd(AF_INET, proto, rcv_fds, 2, शून्य);
	build_rcv_fd(AF_INET6, proto, rcv_fds + 2, 2, शून्य);
	build_rcv_fd(fam_rcv, proto, rcv_fds + 4, 1, addr_str);
	build_rcv_fd(AF_INET, proto, rcv_fds + 5, 2, शून्य);
	build_rcv_fd(AF_INET6, proto, rcv_fds + 7, 2, शून्य);
	test(rcv_fds, 9, fam_send, proto, rcv_fds[4]);
	क्रम (i = 0; i < 9; ++i)
		बंद(rcv_fds[i]);
	ख_लिखो(मानक_त्रुटि, "pass\n");
पूर्ण

अटल व्योम test_proto(पूर्णांक proto, स्थिर अक्षर *proto_str)
अणु
	अगर (proto == SOCK_DCCP) अणु
		पूर्णांक test_fd;

		test_fd = socket(AF_INET, proto, 0);
		अगर (test_fd < 0) अणु
			अगर (त्रुटि_सं == ESOCKTNOSUPPORT) अणु
				ख_लिखो(मानक_त्रुटि, "DCCP not supported: skipping DCCP tests\n");
				वापस;
			पूर्ण अन्यथा
				error(1, त्रुटि_सं, "failed to create a DCCP socket");
		पूर्ण
		बंद(test_fd);
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "%s IPv4 ... ", proto_str);
	run_one_test(AF_INET, AF_INET, proto, IP4_ADDR);

	ख_लिखो(मानक_त्रुटि, "%s IPv6 ... ", proto_str);
	run_one_test(AF_INET6, AF_INET6, proto, IP6_ADDR);

	ख_लिखो(मानक_त्रुटि, "%s IPv4 mapped to IPv6 ... ", proto_str);
	run_one_test(AF_INET, AF_INET6, proto, IP4_MAPPED6);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	test_proto(SOCK_DGRAM, "UDP");
	test_proto(SOCK_STREAM, "TCP");
	test_proto(SOCK_DCCP, "DCCP");

	ख_लिखो(मानक_त्रुटि, "SUCCESS\n");
	वापस 0;
पूर्ण
