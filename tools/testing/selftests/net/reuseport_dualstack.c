<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * It is possible to use SO_REUSEPORT to खोलो multiple sockets bound to
 * equivalent local addresses using AF_INET and AF_INET6 at the same समय.  If
 * the AF_INET6 socket has IPV6_V6ONLY set, it's clear which socket should
 * receive a given incoming packet.  However, when it is not set, incoming v4
 * packets should prefer the AF_INET socket(s).  This behavior was defined with
 * the original SO_REUSEPORT implementation, but broke with
 * e32ea7e74727 ("soreuseport: fast reuseport UDP socket selection")
 * This test creates these mixed AF_INET/AF_INET6 sockets and निश्चितs the
 * AF_INET preference क्रम v4 packets.
 */

#घोषणा _GNU_SOURCE

#समावेश <arpa/inet.h>
#समावेश <त्रुटिसं.स>
#समावेश <error.h>
#समावेश <linux/in.h>
#समावेश <linux/unistd.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/epoll.h>
#समावेश <sys/types.h>
#समावेश <sys/socket.h>
#समावेश <unistd.h>

अटल स्थिर पूर्णांक PORT = 8888;

अटल व्योम build_rcv_fd(पूर्णांक family, पूर्णांक proto, पूर्णांक *rcv_fds, पूर्णांक count)
अणु
	काष्ठा sockaddr_storage addr;
	काष्ठा sockaddr_in  *addr4;
	काष्ठा sockaddr_in6 *addr6;
	पूर्णांक opt, i;

	चयन (family) अणु
	हाल AF_INET:
		addr4 = (काष्ठा sockaddr_in *)&addr;
		addr4->sin_family = AF_INET;
		addr4->sin_addr.s_addr = htonl(INADDR_ANY);
		addr4->sin_port = htons(PORT);
		अवरोध;
	हाल AF_INET6:
		addr6 = (काष्ठा sockaddr_in6 *)&addr;
		addr6->sin6_family = AF_INET6;
		addr6->sin6_addr = in6addr_any;
		addr6->sin6_port = htons(PORT);
		अवरोध;
	शेष:
		error(1, 0, "Unsupported family %d", family);
	पूर्ण

	क्रम (i = 0; i < count; ++i) अणु
		rcv_fds[i] = socket(family, proto, 0);
		अगर (rcv_fds[i] < 0)
			error(1, त्रुटि_सं, "failed to create receive socket");

		opt = 1;
		अगर (setsockopt(rcv_fds[i], SOL_SOCKET, SO_REUSEPORT, &opt,
			       माप(opt)))
			error(1, त्रुटि_सं, "failed to set SO_REUSEPORT");

		अगर (bind(rcv_fds[i], (काष्ठा sockaddr *)&addr, माप(addr)))
			error(1, त्रुटि_सं, "failed to bind receive socket");

		अगर (proto == SOCK_STREAM && listen(rcv_fds[i], 10))
			error(1, त्रुटि_सं, "failed to listen on receive port");
	पूर्ण
पूर्ण

अटल व्योम send_from_v4(पूर्णांक proto)
अणु
	काष्ठा sockaddr_in  saddr, daddr;
	पूर्णांक fd;

	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = 0;

	daddr.sin_family = AF_INET;
	daddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	daddr.sin_port = htons(PORT);

	fd = socket(AF_INET, proto, 0);
	अगर (fd < 0)
		error(1, त्रुटि_सं, "failed to create send socket");

	अगर (bind(fd, (काष्ठा sockaddr *)&saddr, माप(saddr)))
		error(1, त्रुटि_सं, "failed to bind send socket");

	अगर (connect(fd, (काष्ठा sockaddr *)&daddr, माप(daddr)))
		error(1, त्रुटि_सं, "failed to connect send socket");

	अगर (send(fd, "a", 1, 0) < 0)
		error(1, त्रुटि_सं, "failed to send message");

	बंद(fd);
पूर्ण

अटल पूर्णांक receive_once(पूर्णांक epfd, पूर्णांक proto)
अणु
	काष्ठा epoll_event ev;
	पूर्णांक i, fd;
	अक्षर buf[8];

	i = epoll_रुको(epfd, &ev, 1, -1);
	अगर (i < 0)
		error(1, त्रुटि_सं, "epoll_wait failed");

	अगर (proto == SOCK_STREAM) अणु
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

अटल व्योम test(पूर्णांक *rcv_fds, पूर्णांक count, पूर्णांक proto)
अणु
	काष्ठा epoll_event ev;
	पूर्णांक epfd, i, test_fd;
	पूर्णांक test_family;
	socklen_t len;

	epfd = epoll_create(1);
	अगर (epfd < 0)
		error(1, त्रुटि_सं, "failed to create epoll");

	ev.events = EPOLLIN;
	क्रम (i = 0; i < count; ++i) अणु
		ev.data.fd = rcv_fds[i];
		अगर (epoll_ctl(epfd, EPOLL_CTL_ADD, rcv_fds[i], &ev))
			error(1, त्रुटि_सं, "failed to register sock epoll");
	पूर्ण

	send_from_v4(proto);

	test_fd = receive_once(epfd, proto);
	len = माप(test_family);
	अगर (माला_लोockopt(test_fd, SOL_SOCKET, SO_DOMAIN, &test_family, &len))
		error(1, त्रुटि_सं, "failed to read socket domain");
	अगर (test_family != AF_INET)
		error(1, 0, "expected to receive on v4 socket but got v6 (%d)",
		      test_family);

	बंद(epfd);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक rcv_fds[32], i;

	ख_लिखो(मानक_त्रुटि, "---- UDP IPv4 created before IPv6 ----\n");
	build_rcv_fd(AF_INET, SOCK_DGRAM, rcv_fds, 5);
	build_rcv_fd(AF_INET6, SOCK_DGRAM, &(rcv_fds[5]), 5);
	test(rcv_fds, 10, SOCK_DGRAM);
	क्रम (i = 0; i < 10; ++i)
		बंद(rcv_fds[i]);

	ख_लिखो(मानक_त्रुटि, "---- UDP IPv6 created before IPv4 ----\n");
	build_rcv_fd(AF_INET6, SOCK_DGRAM, rcv_fds, 5);
	build_rcv_fd(AF_INET, SOCK_DGRAM, &(rcv_fds[5]), 5);
	test(rcv_fds, 10, SOCK_DGRAM);
	क्रम (i = 0; i < 10; ++i)
		बंद(rcv_fds[i]);

	/* NOTE: UDP socket lookups traverse a dअगरferent code path when there
	 * are > 10 sockets in a group.
	 */
	ख_लिखो(मानक_त्रुटि, "---- UDP IPv4 created before IPv6 (large) ----\n");
	build_rcv_fd(AF_INET, SOCK_DGRAM, rcv_fds, 16);
	build_rcv_fd(AF_INET6, SOCK_DGRAM, &(rcv_fds[16]), 16);
	test(rcv_fds, 32, SOCK_DGRAM);
	क्रम (i = 0; i < 32; ++i)
		बंद(rcv_fds[i]);

	ख_लिखो(मानक_त्रुटि, "---- UDP IPv6 created before IPv4 (large) ----\n");
	build_rcv_fd(AF_INET6, SOCK_DGRAM, rcv_fds, 16);
	build_rcv_fd(AF_INET, SOCK_DGRAM, &(rcv_fds[16]), 16);
	test(rcv_fds, 32, SOCK_DGRAM);
	क्रम (i = 0; i < 32; ++i)
		बंद(rcv_fds[i]);

	ख_लिखो(मानक_त्रुटि, "---- TCP IPv4 created before IPv6 ----\n");
	build_rcv_fd(AF_INET, SOCK_STREAM, rcv_fds, 5);
	build_rcv_fd(AF_INET6, SOCK_STREAM, &(rcv_fds[5]), 5);
	test(rcv_fds, 10, SOCK_STREAM);
	क्रम (i = 0; i < 10; ++i)
		बंद(rcv_fds[i]);

	ख_लिखो(मानक_त्रुटि, "---- TCP IPv6 created before IPv4 ----\n");
	build_rcv_fd(AF_INET6, SOCK_STREAM, rcv_fds, 5);
	build_rcv_fd(AF_INET, SOCK_STREAM, &(rcv_fds[5]), 5);
	test(rcv_fds, 10, SOCK_STREAM);
	क्रम (i = 0; i < 10; ++i)
		बंद(rcv_fds[i]);

	ख_लिखो(मानक_त्रुटि, "SUCCESS\n");
	वापस 0;
पूर्ण
