<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2018 Google Inc.
 * Author: Soheil Hassas Yeganeh (soheil@google.com)
 *
 * Simple example on how to use TCP_INQ and TCP_CM_INQ.
 */
#घोषणा _GNU_SOURCE

#समावेश <error.h>
#समावेश <netinet/in.h>
#समावेश <netinet/tcp.h>
#समावेश <pthपढ़ो.h>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/socket.h>
#समावेश <unistd.h>

#अगर_अघोषित TCP_INQ
#घोषणा TCP_INQ 36
#पूर्ण_अगर

#अगर_अघोषित TCP_CM_INQ
#घोषणा TCP_CM_INQ TCP_INQ
#पूर्ण_अगर

#घोषणा BUF_SIZE 8192
#घोषणा CMSG_SIZE 32

अटल पूर्णांक family = AF_INET6;
अटल socklen_t addr_len = माप(काष्ठा sockaddr_in6);
अटल पूर्णांक port = 4974;

अटल व्योम setup_loopback_addr(पूर्णांक family, काष्ठा sockaddr_storage *sockaddr)
अणु
	काष्ठा sockaddr_in6 *addr6 = (व्योम *) sockaddr;
	काष्ठा sockaddr_in *addr4 = (व्योम *) sockaddr;

	चयन (family) अणु
	हाल PF_INET:
		स_रखो(addr4, 0, माप(*addr4));
		addr4->sin_family = AF_INET;
		addr4->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		addr4->sin_port = htons(port);
		अवरोध;
	हाल PF_INET6:
		स_रखो(addr6, 0, माप(*addr6));
		addr6->sin6_family = AF_INET6;
		addr6->sin6_addr = in6addr_loopback;
		addr6->sin6_port = htons(port);
		अवरोध;
	शेष:
		error(1, 0, "illegal family");
	पूर्ण
पूर्ण

व्योम *start_server(व्योम *arg)
अणु
	पूर्णांक server_fd = (पूर्णांक)(अचिन्हित दीर्घ)arg;
	काष्ठा sockaddr_in addr;
	socklen_t addrlen = माप(addr);
	अक्षर *buf;
	पूर्णांक fd;
	पूर्णांक r;

	buf = दो_स्मृति(BUF_SIZE);

	क्रम (;;) अणु
		fd = accept(server_fd, (काष्ठा sockaddr *)&addr, &addrlen);
		अगर (fd == -1) अणु
			लिखो_त्रुटि("accept");
			अवरोध;
		पूर्ण
		करो अणु
			r = send(fd, buf, BUF_SIZE, 0);
		पूर्ण जबतक (r < 0 && त्रुटि_सं == EINTR);
		अगर (r < 0)
			लिखो_त्रुटि("send");
		अगर (r != BUF_SIZE)
			ख_लिखो(मानक_त्रुटि, "can only send %d bytes\n", r);
		/* TCP_INQ can overestimate in-queue by one byte अगर we send
		 * the FIN packet. Sleep क्रम 1 second, so that the client
		 * likely invoked recvmsg().
		 */
		sleep(1);
		बंद(fd);
	पूर्ण

	मुक्त(buf);
	बंद(server_fd);
	pthपढ़ो_निकास(0);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा sockaddr_storage listen_addr, addr;
	पूर्णांक c, one = 1, inq = -1;
	pthपढ़ो_t server_thपढ़ो;
	अक्षर cmsgbuf[CMSG_SIZE];
	काष्ठा iovec iov[1];
	काष्ठा cmsghdr *cm;
	काष्ठा msghdr msg;
	पूर्णांक server_fd, fd;
	अक्षर *buf;

	जबतक ((c = getopt(argc, argv, "46p:")) != -1) अणु
		चयन (c) अणु
		हाल '4':
			family = PF_INET;
			addr_len = माप(काष्ठा sockaddr_in);
			अवरोध;
		हाल '6':
			family = PF_INET6;
			addr_len = माप(काष्ठा sockaddr_in6);
			अवरोध;
		हाल 'p':
			port = म_से_प(optarg);
			अवरोध;
		पूर्ण
	पूर्ण

	server_fd = socket(family, SOCK_STREAM, 0);
	अगर (server_fd < 0)
		error(1, त्रुटि_सं, "server socket");
	setup_loopback_addr(family, &listen_addr);
	अगर (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
		       &one, माप(one)) != 0)
		error(1, त्रुटि_सं, "setsockopt(SO_REUSEADDR)");
	अगर (bind(server_fd, (स्थिर काष्ठा sockaddr *)&listen_addr,
		 addr_len) == -1)
		error(1, त्रुटि_सं, "bind");
	अगर (listen(server_fd, 128) == -1)
		error(1, त्रुटि_सं, "listen");
	अगर (pthपढ़ो_create(&server_thपढ़ो, शून्य, start_server,
			   (व्योम *)(अचिन्हित दीर्घ)server_fd) != 0)
		error(1, त्रुटि_सं, "pthread_create");

	fd = socket(family, SOCK_STREAM, 0);
	अगर (fd < 0)
		error(1, त्रुटि_सं, "client socket");
	setup_loopback_addr(family, &addr);
	अगर (connect(fd, (स्थिर काष्ठा sockaddr *)&addr, addr_len) == -1)
		error(1, त्रुटि_सं, "connect");
	अगर (setsockopt(fd, SOL_TCP, TCP_INQ, &one, माप(one)) != 0)
		error(1, त्रुटि_सं, "setsockopt(TCP_INQ)");

	msg.msg_name = शून्य;
	msg.msg_namelen = 0;
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;
	msg.msg_control = cmsgbuf;
	msg.msg_controllen = माप(cmsgbuf);
	msg.msg_flags = 0;

	buf = दो_स्मृति(BUF_SIZE);
	iov[0].iov_base = buf;
	iov[0].iov_len = BUF_SIZE / 2;

	अगर (recvmsg(fd, &msg, 0) != iov[0].iov_len)
		error(1, त्रुटि_सं, "recvmsg");
	अगर (msg.msg_flags & MSG_CTRUNC)
		error(1, 0, "control message is truncated");

	क्रम (cm = CMSG_FIRSTHDR(&msg); cm; cm = CMSG_NXTHDR(&msg, cm))
		अगर (cm->cmsg_level == SOL_TCP && cm->cmsg_type == TCP_CM_INQ)
			inq = *((पूर्णांक *) CMSG_DATA(cm));

	अगर (inq != BUF_SIZE - iov[0].iov_len) अणु
		ख_लिखो(मानक_त्रुटि, "unexpected inq: %d\n", inq);
		निकास(1);
	पूर्ण

	म_लिखो("PASSED\n");
	मुक्त(buf);
	बंद(fd);
	वापस 0;
पूर्ण
