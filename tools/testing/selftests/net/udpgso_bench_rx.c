<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा _GNU_SOURCE

#समावेश <arpa/inet.h>
#समावेश <error.h>
#समावेश <त्रुटिसं.स>
#समावेश <सीमा.स>
#समावेश <linux/errqueue.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <net/ethernet.h>
#समावेश <net/अगर.h>
#समावेश <netinet/ip.h>
#समावेश <netinet/ip6.h>
#समावेश <netinet/tcp.h>
#समावेश <netinet/udp.h>
#समावेश <poll.h>
#समावेश <sched.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/socket.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

#अगर_अघोषित UDP_GRO
#घोषणा UDP_GRO		104
#पूर्ण_अगर

अटल पूर्णांक  cfg_port		= 8000;
अटल bool cfg_tcp;
अटल bool cfg_verअगरy;
अटल bool cfg_पढ़ो_all;
अटल bool cfg_gro_segment;
अटल पूर्णांक  cfg_family		= PF_INET6;
अटल पूर्णांक  cfg_alen 		= माप(काष्ठा sockaddr_in6);
अटल पूर्णांक  cfg_expected_pkt_nr;
अटल पूर्णांक  cfg_expected_pkt_len;
अटल पूर्णांक  cfg_expected_gso_size;
अटल पूर्णांक  cfg_connect_समयout_ms;
अटल पूर्णांक  cfg_rcv_समयout_ms;
अटल काष्ठा sockaddr_storage cfg_bind_addr;

अटल bool पूर्णांकerrupted;
अटल अचिन्हित दीर्घ packets, bytes;

अटल व्योम sigपूर्णांक_handler(पूर्णांक signum)
अणु
	अगर (signum == संक_विघ्न)
		पूर्णांकerrupted = true;
पूर्ण

अटल व्योम setup_sockaddr(पूर्णांक करोमुख्य, स्थिर अक्षर *str_addr, व्योम *sockaddr)
अणु
	काष्ठा sockaddr_in6 *addr6 = (व्योम *) sockaddr;
	काष्ठा sockaddr_in *addr4 = (व्योम *) sockaddr;

	चयन (करोमुख्य) अणु
	हाल PF_INET:
		addr4->sin_family = AF_INET;
		addr4->sin_port = htons(cfg_port);
		अगर (inet_pton(AF_INET, str_addr, &(addr4->sin_addr)) != 1)
			error(1, 0, "ipv4 parse error: %s", str_addr);
		अवरोध;
	हाल PF_INET6:
		addr6->sin6_family = AF_INET6;
		addr6->sin6_port = htons(cfg_port);
		अगर (inet_pton(AF_INET6, str_addr, &(addr6->sin6_addr)) != 1)
			error(1, 0, "ipv6 parse error: %s", str_addr);
		अवरोध;
	शेष:
		error(1, 0, "illegal domain");
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ समय_लोofday_ms(व्योम)
अणु
	काष्ठा समयval tv;

	समय_लोofday(&tv, शून्य);
	वापस (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
पूर्ण

अटल व्योम करो_poll(पूर्णांक fd, पूर्णांक समयout_ms)
अणु
	काष्ठा pollfd pfd;
	पूर्णांक ret;

	pfd.events = POLLIN;
	pfd.revents = 0;
	pfd.fd = fd;

	करो अणु
		ret = poll(&pfd, 1, 10);
		अगर (पूर्णांकerrupted)
			अवरोध;
		अगर (ret == -1)
			error(1, त्रुटि_सं, "poll");
		अगर (ret == 0) अणु
			अगर (!समयout_ms)
				जारी;

			समयout_ms -= 10;
			अगर (समयout_ms <= 0) अणु
				पूर्णांकerrupted = true;
				अवरोध;
			पूर्ण

			/* no events and more समय to रुको, करो poll again */
			जारी;
		पूर्ण
		अगर (pfd.revents != POLLIN)
			error(1, त्रुटि_सं, "poll: 0x%x expected 0x%x\n",
					pfd.revents, POLLIN);
	पूर्ण जबतक (!ret);
पूर्ण

अटल पूर्णांक करो_socket(bool करो_tcp)
अणु
	पूर्णांक fd, val;

	fd = socket(cfg_family, cfg_tcp ? SOCK_STREAM : SOCK_DGRAM, 0);
	अगर (fd == -1)
		error(1, त्रुटि_सं, "socket");

	val = 1 << 21;
	अगर (setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &val, माप(val)))
		error(1, त्रुटि_सं, "setsockopt rcvbuf");
	val = 1;
	अगर (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &val, माप(val)))
		error(1, त्रुटि_सं, "setsockopt reuseport");

	अगर (bind(fd, (व्योम *)&cfg_bind_addr, cfg_alen))
		error(1, त्रुटि_सं, "bind");

	अगर (करो_tcp) अणु
		पूर्णांक accept_fd = fd;

		अगर (listen(accept_fd, 1))
			error(1, त्रुटि_सं, "listen");

		करो_poll(accept_fd, cfg_connect_समयout_ms);
		अगर (पूर्णांकerrupted)
			निकास(0);

		fd = accept(accept_fd, शून्य, शून्य);
		अगर (fd == -1)
			error(1, त्रुटि_सं, "accept");
		अगर (बंद(accept_fd))
			error(1, त्रुटि_सं, "close accept fd");
	पूर्ण

	वापस fd;
पूर्ण

/* Flush all outstanding bytes क्रम the tcp receive queue */
अटल व्योम करो_flush_tcp(पूर्णांक fd)
अणु
	पूर्णांक ret;

	जबतक (true) अणु
		/* MSG_TRUNC flushes up to len bytes */
		ret = recv(fd, शून्य, 1 << 21, MSG_TRUNC | MSG_DONTWAIT);
		अगर (ret == -1 && त्रुटि_सं == EAGAIN)
			वापस;
		अगर (ret == -1)
			error(1, त्रुटि_सं, "flush");
		अगर (ret == 0) अणु
			/* client detached */
			निकास(0);
		पूर्ण

		packets++;
		bytes += ret;
	पूर्ण

पूर्ण

अटल अक्षर sanitized_अक्षर(अक्षर val)
अणु
	वापस (val >= 'a' && val <= 'z') ? val : '.';
पूर्ण

अटल व्योम करो_verअगरy_udp(स्थिर अक्षर *data, पूर्णांक len)
अणु
	अक्षर cur = data[0];
	पूर्णांक i;

	/* verअगरy contents */
	अगर (cur < 'a' || cur > 'z')
		error(1, 0, "data initial byte out of range");

	क्रम (i = 1; i < len; i++) अणु
		अगर (cur == 'z')
			cur = 'a';
		अन्यथा
			cur++;

		अगर (data[i] != cur)
			error(1, 0, "data[%d]: len %d, %c(%hhu) != %c(%hhu)\n",
			      i, len,
			      sanitized_अक्षर(data[i]), data[i],
			      sanitized_अक्षर(cur), cur);
	पूर्ण
पूर्ण

अटल पूर्णांक recv_msg(पूर्णांक fd, अक्षर *buf, पूर्णांक len, पूर्णांक *gso_size)
अणु
	अक्षर control[CMSG_SPACE(माप(uपूर्णांक16_t))] = अणु0पूर्ण;
	काष्ठा msghdr msg = अणु0पूर्ण;
	काष्ठा iovec iov = अणु0पूर्ण;
	काष्ठा cmsghdr *cmsg;
	uपूर्णांक16_t *gsosizeptr;
	पूर्णांक ret;

	iov.iov_base = buf;
	iov.iov_len = len;

	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;

	msg.msg_control = control;
	msg.msg_controllen = माप(control);

	*gso_size = -1;
	ret = recvmsg(fd, &msg, MSG_TRUNC | MSG_DONTWAIT);
	अगर (ret != -1) अणु
		क्रम (cmsg = CMSG_FIRSTHDR(&msg); cmsg != शून्य;
		     cmsg = CMSG_NXTHDR(&msg, cmsg)) अणु
			अगर (cmsg->cmsg_level == SOL_UDP
			    && cmsg->cmsg_type == UDP_GRO) अणु
				gsosizeptr = (uपूर्णांक16_t *) CMSG_DATA(cmsg);
				*gso_size = *gsosizeptr;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/* Flush all outstanding datagrams. Verअगरy first few bytes of each. */
अटल व्योम करो_flush_udp(पूर्णांक fd)
अणु
	अटल अक्षर rbuf[ETH_MAX_MTU];
	पूर्णांक ret, len, gso_size, budget = 256;

	len = cfg_पढ़ो_all ? माप(rbuf) : 0;
	जबतक (budget--) अणु
		/* MSG_TRUNC will make वापस value full datagram length */
		अगर (!cfg_expected_gso_size)
			ret = recv(fd, rbuf, len, MSG_TRUNC | MSG_DONTWAIT);
		अन्यथा
			ret = recv_msg(fd, rbuf, len, &gso_size);
		अगर (ret == -1 && त्रुटि_सं == EAGAIN)
			अवरोध;
		अगर (ret == -1)
			error(1, त्रुटि_सं, "recv");
		अगर (cfg_expected_pkt_len && ret != cfg_expected_pkt_len)
			error(1, 0, "recv: bad packet len, got %d,"
			      " expected %d\n", ret, cfg_expected_pkt_len);
		अगर (len && cfg_verअगरy) अणु
			अगर (ret == 0)
				error(1, त्रुटि_सं, "recv: 0 byte datagram\n");

			करो_verअगरy_udp(rbuf, ret);
		पूर्ण
		अगर (cfg_expected_gso_size && cfg_expected_gso_size != gso_size)
			error(1, 0, "recv: bad gso size, got %d, expected %d "
			      "(-1 == no gso cmsg))\n", gso_size,
			      cfg_expected_gso_size);

		packets++;
		bytes += ret;
		अगर (cfg_expected_pkt_nr && packets >= cfg_expected_pkt_nr)
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम usage(स्थिर अक्षर *filepath)
अणु
	error(1, 0, "Usage: %s [-C connect_timeout] [-Grtv] [-b addr] [-p port]"
	      " [-l pktlen] [-n packetnr] [-R rcv_timeout] [-S gsosize]",
	      filepath);
पूर्ण

अटल व्योम parse_opts(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक c;

	/* bind to any by शेष */
	setup_sockaddr(PF_INET6, "::", &cfg_bind_addr);
	जबतक ((c = getopt(argc, argv, "4b:C:Gl:n:p:rR:S:tv")) != -1) अणु
		चयन (c) अणु
		हाल '4':
			cfg_family = PF_INET;
			cfg_alen = माप(काष्ठा sockaddr_in);
			setup_sockaddr(PF_INET, "0.0.0.0", &cfg_bind_addr);
			अवरोध;
		हाल 'b':
			setup_sockaddr(cfg_family, optarg, &cfg_bind_addr);
			अवरोध;
		हाल 'C':
			cfg_connect_समयout_ms = म_से_अदीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'G':
			cfg_gro_segment = true;
			अवरोध;
		हाल 'l':
			cfg_expected_pkt_len = म_से_अदीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'n':
			cfg_expected_pkt_nr = म_से_अदीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'p':
			cfg_port = म_से_अदीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'r':
			cfg_पढ़ो_all = true;
			अवरोध;
		हाल 'R':
			cfg_rcv_समयout_ms = म_से_अदीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'S':
			cfg_expected_gso_size = म_से_दीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 't':
			cfg_tcp = true;
			अवरोध;
		हाल 'v':
			cfg_verअगरy = true;
			cfg_पढ़ो_all = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (optind != argc)
		usage(argv[0]);

	अगर (cfg_tcp && cfg_verअगरy)
		error(1, 0, "TODO: implement verify mode for tcp");
पूर्ण

अटल व्योम करो_recv(व्योम)
अणु
	पूर्णांक समयout_ms = cfg_tcp ? cfg_rcv_समयout_ms : cfg_connect_समयout_ms;
	अचिन्हित दीर्घ tnow, treport;
	पूर्णांक fd;

	fd = करो_socket(cfg_tcp);

	अगर (cfg_gro_segment && !cfg_tcp) अणु
		पूर्णांक val = 1;
		अगर (setsockopt(fd, IPPROTO_UDP, UDP_GRO, &val, माप(val)))
			error(1, त्रुटि_सं, "setsockopt UDP_GRO");
	पूर्ण

	treport = समय_लोofday_ms() + 1000;
	करो अणु
		करो_poll(fd, समयout_ms);

		अगर (cfg_tcp)
			करो_flush_tcp(fd);
		अन्यथा
			करो_flush_udp(fd);

		tnow = समय_लोofday_ms();
		अगर (tnow > treport) अणु
			अगर (packets)
				ख_लिखो(मानक_त्रुटि,
					"%s rx: %6lu MB/s %8lu calls/s\n",
					cfg_tcp ? "tcp" : "udp",
					bytes >> 20, packets);
			bytes = packets = 0;
			treport = tnow + 1000;
		पूर्ण

		समयout_ms = cfg_rcv_समयout_ms;

	पूर्ण जबतक (!पूर्णांकerrupted);

	अगर (cfg_expected_pkt_nr && (packets != cfg_expected_pkt_nr))
		error(1, 0, "wrong packet number! got %ld, expected %d\n",
		      packets, cfg_expected_pkt_nr);

	अगर (बंद(fd))
		error(1, त्रुटि_सं, "close");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	parse_opts(argc, argv);

	संकेत(संक_विघ्न, sigपूर्णांक_handler);

	करो_recv();

	वापस 0;
पूर्ण
