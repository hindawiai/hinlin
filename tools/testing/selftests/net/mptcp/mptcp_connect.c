<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा _GNU_SOURCE

#समावेश <त्रुटिसं.स>
#समावेश <सीमा.स>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <stdbool.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <strings.h>
#समावेश <संकेत.स>
#समावेश <unistd.h>

#समावेश <sys/poll.h>
#समावेश <sys/sendfile.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/socket.h>
#समावेश <sys/types.h>
#समावेश <sys/mman.h>

#समावेश <netdb.h>
#समावेश <netinet/in.h>

#समावेश <linux/tcp.h>

बाह्य पूर्णांक optind;

#अगर_अघोषित IPPROTO_MPTCP
#घोषणा IPPROTO_MPTCP 262
#पूर्ण_अगर
#अगर_अघोषित TCP_ULP
#घोषणा TCP_ULP 31
#पूर्ण_अगर

अटल पूर्णांक  poll_समयout = 10 * 1000;
अटल bool listen_mode;
अटल bool quit;

क्रमागत cfg_mode अणु
	CFG_MODE_POLL,
	CFG_MODE_MMAP,
	CFG_MODE_SENDखाता,
पूर्ण;

क्रमागत cfg_peek अणु
	CFG_NONE_PEEK,
	CFG_WITH_PEEK,
	CFG_AFTER_PEEK,
पूर्ण;

अटल क्रमागत cfg_mode cfg_mode = CFG_MODE_POLL;
अटल क्रमागत cfg_peek cfg_peek = CFG_NONE_PEEK;
अटल स्थिर अक्षर *cfg_host;
अटल स्थिर अक्षर *cfg_port	= "12000";
अटल पूर्णांक cfg_sock_proto	= IPPROTO_MPTCP;
अटल bool tcpulp_audit;
अटल पूर्णांक pf = AF_INET;
अटल पूर्णांक cfg_sndbuf;
अटल पूर्णांक cfg_rcvbuf;
अटल bool cfg_join;
अटल bool cfg_हटाओ;
अटल अचिन्हित पूर्णांक cfg_करो_w;
अटल पूर्णांक cfg_रुको;
अटल uपूर्णांक32_t cfg_mark;

अटल व्योम die_usage(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "Usage: mptcp_connect [-6] [-u] [-s MPTCP|TCP] [-p port] [-m mode]"
		"[-l] [-w sec] connect_address\n");
	ख_लिखो(मानक_त्रुटि, "\t-6 use ipv6\n");
	ख_लिखो(मानक_त्रुटि, "\t-t num -- set poll timeout to num\n");
	ख_लिखो(मानक_त्रुटि, "\t-S num -- set SO_SNDBUF to num\n");
	ख_लिखो(मानक_त्रुटि, "\t-R num -- set SO_RCVBUF to num\n");
	ख_लिखो(मानक_त्रुटि, "\t-p num -- use port num\n");
	ख_लिखो(मानक_त्रुटि, "\t-s [MPTCP|TCP] -- use mptcp(default) or tcp sockets\n");
	ख_लिखो(मानक_त्रुटि, "\t-m [poll|mmap|sendfile] -- use poll(default)/mmap+write/sendfile\n");
	ख_लिखो(मानक_त्रुटि, "\t-M mark -- set socket packet mark\n");
	ख_लिखो(मानक_त्रुटि, "\t-u -- check mptcp ulp\n");
	ख_लिखो(मानक_त्रुटि, "\t-w num -- wait num sec before closing the socket\n");
	ख_लिखो(मानक_त्रुटि,
		"\t-P [saveWithPeek|saveAfterPeek] -- save data with/after MSG_PEEK form tcp socket\n");
	निकास(1);
पूर्ण

अटल व्योम handle_संकेत(पूर्णांक nr)
अणु
	quit = true;
पूर्ण

अटल स्थिर अक्षर *getxinfo_strerr(पूर्णांक err)
अणु
	अगर (err == EAI_SYSTEM)
		वापस म_त्रुटि(त्रुटि_सं);

	वापस gai_म_त्रुटि(err);
पूर्ण

अटल व्योम xgetnameinfo(स्थिर काष्ठा sockaddr *addr, socklen_t addrlen,
			 अक्षर *host, socklen_t hostlen,
			 अक्षर *serv, socklen_t servlen)
अणु
	पूर्णांक flags = NI_NUMERICHOST | NI_NUMERICSERV;
	पूर्णांक err = getnameinfo(addr, addrlen, host, hostlen, serv, servlen,
			      flags);

	अगर (err) अणु
		स्थिर अक्षर *errstr = getxinfo_strerr(err);

		ख_लिखो(मानक_त्रुटि, "Fatal: getnameinfo: %s\n", errstr);
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम xgetaddrinfo(स्थिर अक्षर *node, स्थिर अक्षर *service,
			 स्थिर काष्ठा addrinfo *hपूर्णांकs,
			 काष्ठा addrinfo **res)
अणु
	पूर्णांक err = getaddrinfo(node, service, hपूर्णांकs, res);

	अगर (err) अणु
		स्थिर अक्षर *errstr = getxinfo_strerr(err);

		ख_लिखो(मानक_त्रुटि, "Fatal: getaddrinfo(%s:%s): %s\n",
			node ? node : "", service ? service : "", errstr);
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम set_rcvbuf(पूर्णांक fd, अचिन्हित पूर्णांक size)
अणु
	पूर्णांक err;

	err = setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &size, माप(size));
	अगर (err) अणु
		लिखो_त्रुटि("set SO_RCVBUF");
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम set_sndbuf(पूर्णांक fd, अचिन्हित पूर्णांक size)
अणु
	पूर्णांक err;

	err = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &size, माप(size));
	अगर (err) अणु
		लिखो_त्रुटि("set SO_SNDBUF");
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम set_mark(पूर्णांक fd, uपूर्णांक32_t mark)
अणु
	पूर्णांक err;

	err = setsockopt(fd, SOL_SOCKET, SO_MARK, &mark, माप(mark));
	अगर (err) अणु
		लिखो_त्रुटि("set SO_MARK");
		निकास(1);
	पूर्ण
पूर्ण

अटल पूर्णांक sock_listen_mptcp(स्थिर अक्षर * स्थिर listenaddr,
			     स्थिर अक्षर * स्थिर port)
अणु
	पूर्णांक sock;
	काष्ठा addrinfo hपूर्णांकs = अणु
		.ai_protocol = IPPROTO_TCP,
		.ai_socktype = SOCK_STREAM,
		.ai_flags = AI_PASSIVE | AI_NUMERICHOST
	पूर्ण;

	hपूर्णांकs.ai_family = pf;

	काष्ठा addrinfo *a, *addr;
	पूर्णांक one = 1;

	xgetaddrinfo(listenaddr, port, &hपूर्णांकs, &addr);
	hपूर्णांकs.ai_family = pf;

	क्रम (a = addr; a; a = a->ai_next) अणु
		sock = socket(a->ai_family, a->ai_socktype, cfg_sock_proto);
		अगर (sock < 0)
			जारी;

		अगर (-1 == setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one,
				     माप(one)))
			लिखो_त्रुटि("setsockopt");

		अगर (bind(sock, a->ai_addr, a->ai_addrlen) == 0)
			अवरोध; /* success */

		लिखो_त्रुटि("bind");
		बंद(sock);
		sock = -1;
	पूर्ण

	मुक्तaddrinfo(addr);

	अगर (sock < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Could not create listen socket\n");
		वापस sock;
	पूर्ण

	अगर (listen(sock, 20)) अणु
		लिखो_त्रुटि("listen");
		बंद(sock);
		वापस -1;
	पूर्ण

	वापस sock;
पूर्ण

अटल bool sock_test_tcpulp(स्थिर अक्षर * स्थिर remoteaddr,
			     स्थिर अक्षर * स्थिर port)
अणु
	काष्ठा addrinfo hपूर्णांकs = अणु
		.ai_protocol = IPPROTO_TCP,
		.ai_socktype = SOCK_STREAM,
	पूर्ण;
	काष्ठा addrinfo *a, *addr;
	पूर्णांक sock = -1, ret = 0;
	bool test_pass = false;

	hपूर्णांकs.ai_family = AF_INET;

	xgetaddrinfo(remoteaddr, port, &hपूर्णांकs, &addr);
	क्रम (a = addr; a; a = a->ai_next) अणु
		sock = socket(a->ai_family, a->ai_socktype, IPPROTO_TCP);
		अगर (sock < 0) अणु
			लिखो_त्रुटि("socket");
			जारी;
		पूर्ण
		ret = setsockopt(sock, IPPROTO_TCP, TCP_ULP, "mptcp",
				 माप("mptcp"));
		अगर (ret == -1 && त्रुटि_सं == EOPNOTSUPP)
			test_pass = true;
		बंद(sock);

		अगर (test_pass)
			अवरोध;
		अगर (!ret)
			ख_लिखो(मानक_त्रुटि,
				"setsockopt(TCP_ULP) returned 0\n");
		अन्यथा
			लिखो_त्रुटि("setsockopt(TCP_ULP)");
	पूर्ण
	वापस test_pass;
पूर्ण

अटल पूर्णांक sock_connect_mptcp(स्थिर अक्षर * स्थिर remoteaddr,
			      स्थिर अक्षर * स्थिर port, पूर्णांक proto)
अणु
	काष्ठा addrinfo hपूर्णांकs = अणु
		.ai_protocol = IPPROTO_TCP,
		.ai_socktype = SOCK_STREAM,
	पूर्ण;
	काष्ठा addrinfo *a, *addr;
	पूर्णांक sock = -1;

	hपूर्णांकs.ai_family = pf;

	xgetaddrinfo(remoteaddr, port, &hपूर्णांकs, &addr);
	क्रम (a = addr; a; a = a->ai_next) अणु
		sock = socket(a->ai_family, a->ai_socktype, proto);
		अगर (sock < 0) अणु
			लिखो_त्रुटि("socket");
			जारी;
		पूर्ण

		अगर (cfg_mark)
			set_mark(sock, cfg_mark);

		अगर (connect(sock, a->ai_addr, a->ai_addrlen) == 0)
			अवरोध; /* success */

		लिखो_त्रुटि("connect()");
		बंद(sock);
		sock = -1;
	पूर्ण

	मुक्तaddrinfo(addr);
	वापस sock;
पूर्ण

अटल माप_प्रकार करो_rnd_ग_लिखो(स्थिर पूर्णांक fd, अक्षर *buf, स्थिर माप_प्रकार len)
अणु
	अटल bool first = true;
	अचिन्हित पूर्णांक करो_w;
	sमाप_प्रकार bw;

	करो_w = अक्रम() & 0xffff;
	अगर (करो_w == 0 || करो_w > len)
		करो_w = len;

	अगर (cfg_join && first && करो_w > 100)
		करो_w = 100;

	अगर (cfg_हटाओ && करो_w > cfg_करो_w)
		करो_w = cfg_करो_w;

	bw = ग_लिखो(fd, buf, करो_w);
	अगर (bw < 0)
		लिखो_त्रुटि("write");

	/* let the join handshake complete, beक्रमe going on */
	अगर (cfg_join && first) अणु
		usleep(200000);
		first = false;
	पूर्ण

	अगर (cfg_हटाओ)
		usleep(200000);

	वापस bw;
पूर्ण

अटल माप_प्रकार करो_ग_लिखो(स्थिर पूर्णांक fd, अक्षर *buf, स्थिर माप_प्रकार len)
अणु
	माप_प्रकार offset = 0;

	जबतक (offset < len) अणु
		माप_प्रकार written;
		sमाप_प्रकार bw;

		bw = ग_लिखो(fd, buf + offset, len - offset);
		अगर (bw < 0) अणु
			लिखो_त्रुटि("write");
			वापस 0;
		पूर्ण

		written = (माप_प्रकार)bw;
		offset += written;
	पूर्ण

	वापस offset;
पूर्ण

अटल sमाप_प्रकार करो_rnd_पढ़ो(स्थिर पूर्णांक fd, अक्षर *buf, स्थिर माप_प्रकार len)
अणु
	पूर्णांक ret = 0;
	अक्षर पंचांगp[16384];
	माप_प्रकार cap = अक्रम();

	cap &= 0xffff;

	अगर (cap == 0)
		cap = 1;
	अन्यथा अगर (cap > len)
		cap = len;

	अगर (cfg_peek == CFG_WITH_PEEK) अणु
		ret = recv(fd, buf, cap, MSG_PEEK);
		ret = (ret < 0) ? ret : पढ़ो(fd, पंचांगp, ret);
	पूर्ण अन्यथा अगर (cfg_peek == CFG_AFTER_PEEK) अणु
		ret = recv(fd, buf, cap, MSG_PEEK);
		ret = (ret < 0) ? ret : पढ़ो(fd, buf, cap);
	पूर्ण अन्यथा अणु
		ret = पढ़ो(fd, buf, cap);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम set_nonblock(पूर्णांक fd)
अणु
	पूर्णांक flags = fcntl(fd, F_GETFL);

	अगर (flags == -1)
		वापस;

	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
पूर्ण

अटल पूर्णांक copyfd_io_poll(पूर्णांक infd, पूर्णांक peerfd, पूर्णांक outfd)
अणु
	काष्ठा pollfd fds = अणु
		.fd = peerfd,
		.events = POLLIN | POLLOUT,
	पूर्ण;
	अचिन्हित पूर्णांक woff = 0, wlen = 0;
	अक्षर wbuf[8192];

	set_nonblock(peerfd);

	क्रम (;;) अणु
		अक्षर rbuf[8192];
		sमाप_प्रकार len;

		अगर (fds.events == 0)
			अवरोध;

		चयन (poll(&fds, 1, poll_समयout)) अणु
		हाल -1:
			अगर (त्रुटि_सं == EINTR)
				जारी;
			लिखो_त्रुटि("poll");
			वापस 1;
		हाल 0:
			ख_लिखो(मानक_त्रुटि, "%s: poll timed out (events: "
				"POLLIN %u, POLLOUT %u)\n", __func__,
				fds.events & POLLIN, fds.events & POLLOUT);
			वापस 2;
		पूर्ण

		अगर (fds.revents & POLLIN) अणु
			len = करो_rnd_पढ़ो(peerfd, rbuf, माप(rbuf));
			अगर (len == 0) अणु
				/* no more data to receive:
				 * peer has बंदd its ग_लिखो side
				 */
				fds.events &= ~POLLIN;

				अगर ((fds.events & POLLOUT) == 0)
					/* and nothing more to send */
					अवरोध;

			/* Else, still have data to transmit */
			पूर्ण अन्यथा अगर (len < 0) अणु
				लिखो_त्रुटि("read");
				वापस 3;
			पूर्ण

			करो_ग_लिखो(outfd, rbuf, len);
		पूर्ण

		अगर (fds.revents & POLLOUT) अणु
			अगर (wlen == 0) अणु
				woff = 0;
				wlen = पढ़ो(infd, wbuf, माप(wbuf));
			पूर्ण

			अगर (wlen > 0) अणु
				sमाप_प्रकार bw;

				bw = करो_rnd_ग_लिखो(peerfd, wbuf + woff, wlen);
				अगर (bw < 0)
					वापस 111;

				woff += bw;
				wlen -= bw;
			पूर्ण अन्यथा अगर (wlen == 0) अणु
				/* We have no more data to send. */
				fds.events &= ~POLLOUT;

				अगर ((fds.events & POLLIN) == 0)
					/* ... and peer also बंदd alपढ़ोy */
					अवरोध;

				/* ... but we still receive.
				 * Close our ग_लिखो side, ev. give some समय
				 * क्रम address notअगरication and/or checking
				 * the current status
				 */
				अगर (cfg_रुको)
					usleep(cfg_रुको);
				shutकरोwn(peerfd, SHUT_WR);
			पूर्ण अन्यथा अणु
				अगर (त्रुटि_सं == EINTR)
					जारी;
				लिखो_त्रुटि("read");
				वापस 4;
			पूर्ण
		पूर्ण

		अगर (fds.revents & (POLLERR | POLLNVAL)) अणु
			ख_लिखो(मानक_त्रुटि, "Unexpected revents: "
				"POLLERR/POLLNVAL(%x)\n", fds.revents);
			वापस 5;
		पूर्ण
	पूर्ण

	/* leave some समय क्रम late join/announce */
	अगर (cfg_join || cfg_हटाओ)
		usleep(cfg_रुको);

	बंद(peerfd);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_recvfile(पूर्णांक infd, पूर्णांक outfd)
अणु
	sमाप_प्रकार r;

	करो अणु
		अक्षर buf[16384];

		r = करो_rnd_पढ़ो(infd, buf, माप(buf));
		अगर (r > 0) अणु
			अगर (ग_लिखो(outfd, buf, r) != r)
				अवरोध;
		पूर्ण अन्यथा अगर (r < 0) अणु
			लिखो_त्रुटि("read");
		पूर्ण
	पूर्ण जबतक (r > 0);

	वापस (पूर्णांक)r;
पूर्ण

अटल पूर्णांक करो_mmap(पूर्णांक infd, पूर्णांक outfd, अचिन्हित पूर्णांक size)
अणु
	अक्षर *inbuf = mmap(शून्य, size, PROT_READ, MAP_SHARED, infd, 0);
	sमाप_प्रकार ret = 0, off = 0;
	माप_प्रकार rem;

	अगर (inbuf == MAP_FAILED) अणु
		लिखो_त्रुटि("mmap");
		वापस 1;
	पूर्ण

	rem = size;

	जबतक (rem > 0) अणु
		ret = ग_लिखो(outfd, inbuf + off, rem);

		अगर (ret < 0) अणु
			लिखो_त्रुटि("write");
			अवरोध;
		पूर्ण

		off += ret;
		rem -= ret;
	पूर्ण

	munmap(inbuf, size);
	वापस rem;
पूर्ण

अटल पूर्णांक get_infd_size(पूर्णांक fd)
अणु
	काष्ठा stat sb;
	sमाप_प्रकार count;
	पूर्णांक err;

	err = ख_स्थिति(fd, &sb);
	अगर (err < 0) अणु
		लिखो_त्रुटि("fstat");
		वापस -1;
	पूर्ण

	अगर ((sb.st_mode & S_IFMT) != S_IFREG) अणु
		ख_लिखो(मानक_त्रुटि, "%s: stdin is not a regular file\n", __func__);
		वापस -2;
	पूर्ण

	count = sb.st_size;
	अगर (count > पूर्णांक_उच्च) अणु
		ख_लिखो(मानक_त्रुटि, "File too large: %zu\n", count);
		वापस -3;
	पूर्ण

	वापस (पूर्णांक)count;
पूर्ण

अटल पूर्णांक करो_sendfile(पूर्णांक infd, पूर्णांक outfd, अचिन्हित पूर्णांक count)
अणु
	जबतक (count > 0) अणु
		sमाप_प्रकार r;

		r = sendfile(outfd, infd, शून्य, count);
		अगर (r < 0) अणु
			लिखो_त्रुटि("sendfile");
			वापस 3;
		पूर्ण

		count -= r;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक copyfd_io_mmap(पूर्णांक infd, पूर्णांक peerfd, पूर्णांक outfd,
			  अचिन्हित पूर्णांक size)
अणु
	पूर्णांक err;

	अगर (listen_mode) अणु
		err = करो_recvfile(peerfd, outfd);
		अगर (err)
			वापस err;

		err = करो_mmap(infd, peerfd, size);
	पूर्ण अन्यथा अणु
		err = करो_mmap(infd, peerfd, size);
		अगर (err)
			वापस err;

		shutकरोwn(peerfd, SHUT_WR);

		err = करो_recvfile(peerfd, outfd);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक copyfd_io_sendfile(पूर्णांक infd, पूर्णांक peerfd, पूर्णांक outfd,
			      अचिन्हित पूर्णांक size)
अणु
	पूर्णांक err;

	अगर (listen_mode) अणु
		err = करो_recvfile(peerfd, outfd);
		अगर (err)
			वापस err;

		err = करो_sendfile(infd, peerfd, size);
	पूर्ण अन्यथा अणु
		err = करो_sendfile(infd, peerfd, size);
		अगर (err)
			वापस err;
		err = करो_recvfile(peerfd, outfd);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक copyfd_io(पूर्णांक infd, पूर्णांक peerfd, पूर्णांक outfd)
अणु
	पूर्णांक file_size;

	चयन (cfg_mode) अणु
	हाल CFG_MODE_POLL:
		वापस copyfd_io_poll(infd, peerfd, outfd);
	हाल CFG_MODE_MMAP:
		file_size = get_infd_size(infd);
		अगर (file_size < 0)
			वापस file_size;
		वापस copyfd_io_mmap(infd, peerfd, outfd, file_size);
	हाल CFG_MODE_SENDखाता:
		file_size = get_infd_size(infd);
		अगर (file_size < 0)
			वापस file_size;
		वापस copyfd_io_sendfile(infd, peerfd, outfd, file_size);
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "Invalid mode %d\n", cfg_mode);

	die_usage();
	वापस 1;
पूर्ण

अटल व्योम check_sockaddr(पूर्णांक pf, काष्ठा sockaddr_storage *ss,
			   socklen_t salen)
अणु
	काष्ठा sockaddr_in6 *sin6;
	काष्ठा sockaddr_in *sin;
	socklen_t wanted_size = 0;

	चयन (pf) अणु
	हाल AF_INET:
		wanted_size = माप(*sin);
		sin = (व्योम *)ss;
		अगर (!sin->sin_port)
			ख_लिखो(मानक_त्रुटि, "accept: something wrong: ip connection from port 0");
		अवरोध;
	हाल AF_INET6:
		wanted_size = माप(*sin6);
		sin6 = (व्योम *)ss;
		अगर (!sin6->sin6_port)
			ख_लिखो(मानक_त्रुटि, "accept: something wrong: ipv6 connection from port 0");
		अवरोध;
	शेष:
		ख_लिखो(मानक_त्रुटि, "accept: Unknown pf %d, salen %u\n", pf, salen);
		वापस;
	पूर्ण

	अगर (salen != wanted_size)
		ख_लिखो(मानक_त्रुटि, "accept: size mismatch, got %d expected %d\n",
			(पूर्णांक)salen, wanted_size);

	अगर (ss->ss_family != pf)
		ख_लिखो(मानक_त्रुटि, "accept: pf mismatch, expect %d, ss_family is %d\n",
			(पूर्णांक)ss->ss_family, pf);
पूर्ण

अटल व्योम check_getpeername(पूर्णांक fd, काष्ठा sockaddr_storage *ss, socklen_t salen)
अणु
	काष्ठा sockaddr_storage peerss;
	socklen_t peersalen = माप(peerss);

	अगर (getpeername(fd, (काष्ठा sockaddr *)&peerss, &peersalen) < 0) अणु
		लिखो_त्रुटि("getpeername");
		वापस;
	पूर्ण

	अगर (peersalen != salen) अणु
		ख_लिखो(मानक_त्रुटि, "%s: %d vs %d\n", __func__, peersalen, salen);
		वापस;
	पूर्ण

	अगर (स_भेद(ss, &peerss, peersalen)) अणु
		अक्षर a[INET6_ADDRSTRLEN];
		अक्षर b[INET6_ADDRSTRLEN];
		अक्षर c[INET6_ADDRSTRLEN];
		अक्षर d[INET6_ADDRSTRLEN];

		xgetnameinfo((काष्ठा sockaddr *)ss, salen,
			     a, माप(a), b, माप(b));

		xgetnameinfo((काष्ठा sockaddr *)&peerss, peersalen,
			     c, माप(c), d, माप(d));

		ख_लिखो(मानक_त्रुटि, "%s: memcmp failure: accept %s vs peername %s, %s vs %s salen %d vs %d\n",
			__func__, a, c, b, d, peersalen, salen);
	पूर्ण
पूर्ण

अटल व्योम check_getpeername_connect(पूर्णांक fd)
अणु
	काष्ठा sockaddr_storage ss;
	socklen_t salen = माप(ss);
	अक्षर a[INET6_ADDRSTRLEN];
	अक्षर b[INET6_ADDRSTRLEN];

	अगर (getpeername(fd, (काष्ठा sockaddr *)&ss, &salen) < 0) अणु
		लिखो_त्रुटि("getpeername");
		वापस;
	पूर्ण

	xgetnameinfo((काष्ठा sockaddr *)&ss, salen,
		     a, माप(a), b, माप(b));

	अगर (म_भेद(cfg_host, a) || म_भेद(cfg_port, b))
		ख_लिखो(मानक_त्रुटि, "%s: %s vs %s, %s vs %s\n", __func__,
			cfg_host, a, cfg_port, b);
पूर्ण

अटल व्योम maybe_बंद(पूर्णांक fd)
अणु
	अचिन्हित पूर्णांक r = अक्रम();

	अगर (!(cfg_join || cfg_हटाओ) && (r & 1))
		बंद(fd);
पूर्ण

पूर्णांक मुख्य_loop_s(पूर्णांक listensock)
अणु
	काष्ठा sockaddr_storage ss;
	काष्ठा pollfd polls;
	socklen_t salen;
	पूर्णांक remotesock;

	polls.fd = listensock;
	polls.events = POLLIN;

	चयन (poll(&polls, 1, poll_समयout)) अणु
	हाल -1:
		लिखो_त्रुटि("poll");
		वापस 1;
	हाल 0:
		ख_लिखो(मानक_त्रुटि, "%s: timed out\n", __func__);
		बंद(listensock);
		वापस 2;
	पूर्ण

	salen = माप(ss);
	remotesock = accept(listensock, (काष्ठा sockaddr *)&ss, &salen);
	अगर (remotesock >= 0) अणु
		maybe_बंद(listensock);
		check_sockaddr(pf, &ss, salen);
		check_getpeername(remotesock, &ss, salen);

		वापस copyfd_io(0, remotesock, 1);
	पूर्ण

	लिखो_त्रुटि("accept");

	वापस 1;
पूर्ण

अटल व्योम init_rng(व्योम)
अणु
	पूर्णांक fd = खोलो("/dev/urandom", O_RDONLY);
	अचिन्हित पूर्णांक foo;

	अगर (fd > 0) अणु
		पूर्णांक ret = पढ़ो(fd, &foo, माप(foo));

		अगर (ret < 0)
			बेक्रम(fd + foo);
		बंद(fd);
	पूर्ण

	बेक्रम(foo);
पूर्ण

पूर्णांक मुख्य_loop(व्योम)
अणु
	पूर्णांक fd;

	/* listener is पढ़ोy. */
	fd = sock_connect_mptcp(cfg_host, cfg_port, cfg_sock_proto);
	अगर (fd < 0)
		वापस 2;

	check_getpeername_connect(fd);

	अगर (cfg_rcvbuf)
		set_rcvbuf(fd, cfg_rcvbuf);
	अगर (cfg_sndbuf)
		set_sndbuf(fd, cfg_sndbuf);

	वापस copyfd_io(0, fd, 1);
पूर्ण

पूर्णांक parse_proto(स्थिर अक्षर *proto)
अणु
	अगर (!strहालcmp(proto, "MPTCP"))
		वापस IPPROTO_MPTCP;
	अगर (!strहालcmp(proto, "TCP"))
		वापस IPPROTO_TCP;

	ख_लिखो(मानक_त्रुटि, "Unknown protocol: %s\n.", proto);
	die_usage();

	/* silence compiler warning */
	वापस 0;
पूर्ण

पूर्णांक parse_mode(स्थिर अक्षर *mode)
अणु
	अगर (!strहालcmp(mode, "poll"))
		वापस CFG_MODE_POLL;
	अगर (!strहालcmp(mode, "mmap"))
		वापस CFG_MODE_MMAP;
	अगर (!strहालcmp(mode, "sendfile"))
		वापस CFG_MODE_SENDखाता;

	ख_लिखो(मानक_त्रुटि, "Unknown test mode: %s\n", mode);
	ख_लिखो(मानक_त्रुटि, "Supported modes are:\n");
	ख_लिखो(मानक_त्रुटि, "\t\t\"poll\" - interleaved read/write using poll()\n");
	ख_लिखो(मानक_त्रुटि, "\t\t\"mmap\" - send entire input file (mmap+write), then read response (-l will read input first)\n");
	ख_लिखो(मानक_त्रुटि, "\t\t\"sendfile\" - send entire input file (sendfile), then read response (-l will read input first)\n");

	die_usage();

	/* silence compiler warning */
	वापस 0;
पूर्ण

पूर्णांक parse_peek(स्थिर अक्षर *mode)
अणु
	अगर (!strहालcmp(mode, "saveWithPeek"))
		वापस CFG_WITH_PEEK;
	अगर (!strहालcmp(mode, "saveAfterPeek"))
		वापस CFG_AFTER_PEEK;

	ख_लिखो(मानक_त्रुटि, "Unknown: %s\n", mode);
	ख_लिखो(मानक_त्रुटि, "Supported MSG_PEEK mode are:\n");
	ख_लिखो(मानक_त्रुटि,
		"\t\t\"saveWithPeek\" - recv data with flags 'MSG_PEEK' and save the peek data into file\n");
	ख_लिखो(मानक_त्रुटि,
		"\t\t\"saveAfterPeek\" - read and save data into file after recv with flags 'MSG_PEEK'\n");

	die_usage();

	/* silence compiler warning */
	वापस 0;
पूर्ण

अटल पूर्णांक parse_पूर्णांक(स्थिर अक्षर *size)
अणु
	अचिन्हित दीर्घ s;

	त्रुटि_सं = 0;

	s = म_से_अदीर्घ(size, शून्य, 0);

	अगर (त्रुटि_सं) अणु
		ख_लिखो(मानक_त्रुटि, "Invalid sndbuf size %s (%s)\n",
			size, म_त्रुटि(त्रुटि_सं));
		die_usage();
	पूर्ण

	अगर (s > पूर्णांक_उच्च) अणु
		ख_लिखो(मानक_त्रुटि, "Invalid sndbuf size %s (%s)\n",
			size, म_त्रुटि(दुस्फल));
		die_usage();
	पूर्ण

	वापस (पूर्णांक)s;
पूर्ण

अटल व्योम parse_opts(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक c;

	जबतक ((c = getopt(argc, argv, "6jr:lp:s:hut:m:S:R:w:M:P:")) != -1) अणु
		चयन (c) अणु
		हाल 'j':
			cfg_join = true;
			cfg_mode = CFG_MODE_POLL;
			cfg_रुको = 400000;
			अवरोध;
		हाल 'r':
			cfg_हटाओ = true;
			cfg_mode = CFG_MODE_POLL;
			cfg_रुको = 400000;
			cfg_करो_w = म_से_प(optarg);
			अगर (cfg_करो_w <= 0)
				cfg_करो_w = 50;
			अवरोध;
		हाल 'l':
			listen_mode = true;
			अवरोध;
		हाल 'p':
			cfg_port = optarg;
			अवरोध;
		हाल 's':
			cfg_sock_proto = parse_proto(optarg);
			अवरोध;
		हाल 'h':
			die_usage();
			अवरोध;
		हाल 'u':
			tcpulp_audit = true;
			अवरोध;
		हाल '6':
			pf = AF_INET6;
			अवरोध;
		हाल 't':
			poll_समयout = म_से_प(optarg) * 1000;
			अगर (poll_समयout <= 0)
				poll_समयout = -1;
			अवरोध;
		हाल 'm':
			cfg_mode = parse_mode(optarg);
			अवरोध;
		हाल 'S':
			cfg_sndbuf = parse_पूर्णांक(optarg);
			अवरोध;
		हाल 'R':
			cfg_rcvbuf = parse_पूर्णांक(optarg);
			अवरोध;
		हाल 'w':
			cfg_रुको = म_से_प(optarg)*1000000;
			अवरोध;
		हाल 'M':
			cfg_mark = म_से_दीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'P':
			cfg_peek = parse_peek(optarg);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (optind + 1 != argc)
		die_usage();
	cfg_host = argv[optind];

	अगर (म_अक्षर(cfg_host, ':'))
		pf = AF_INET6;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	init_rng();

	संकेत(SIGUSR1, handle_संकेत);
	parse_opts(argc, argv);

	अगर (tcpulp_audit)
		वापस sock_test_tcpulp(cfg_host, cfg_port) ? 0 : 1;

	अगर (listen_mode) अणु
		पूर्णांक fd = sock_listen_mptcp(cfg_host, cfg_port);

		अगर (fd < 0)
			वापस 1;

		अगर (cfg_rcvbuf)
			set_rcvbuf(fd, cfg_rcvbuf);
		अगर (cfg_sndbuf)
			set_sndbuf(fd, cfg_sndbuf);
		अगर (cfg_mark)
			set_mark(fd, cfg_mark);

		वापस मुख्य_loop_s(fd);
	पूर्ण

	वापस मुख्य_loop();
पूर्ण
