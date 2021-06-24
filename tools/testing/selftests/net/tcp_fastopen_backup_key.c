<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Test key rotation क्रम TFO.
 * New keys are 'rotated' in two steps:
 * 1) Add new key as the 'backup' key 'behind' the primary key
 * 2) Make new key the primary by swapping the backup and primary keys
 *
 * The rotation is करोne in stages using multiple sockets bound
 * to the same port via SO_REUSEPORT. This simulates key rotation
 * behind say a load balancer. We verअगरy that across the rotation
 * there are no हालs in which a cookie is not accepted by verअगरying
 * that TcpExtTCPFastOpenPassiveFail reमुख्यs 0.
 */
#घोषणा _GNU_SOURCE
#समावेश <arpa/inet.h>
#समावेश <त्रुटिसं.स>
#समावेश <error.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/epoll.h>
#समावेश <unistd.h>
#समावेश <netinet/tcp.h>
#समावेश <fcntl.h>
#समावेश <समय.स>

#अगर_अघोषित TCP_FASTOPEN_KEY
#घोषणा TCP_FASTOPEN_KEY 33
#पूर्ण_अगर

#घोषणा N_LISTEN 10
#घोषणा PROC_FASTOPEN_KEY "/proc/sys/net/ipv4/tcp_fastopen_key"
#घोषणा KEY_LENGTH 16

#अगर_अघोषित ARRAY_SIZE
#घोषणा ARRAY_SIZE(arr) (माप(arr) / माप((arr)[0]))
#पूर्ण_अगर

अटल bool करो_ipv6;
अटल bool करो_sockopt;
अटल bool करो_rotate;
अटल पूर्णांक key_len = KEY_LENGTH;
अटल पूर्णांक rcv_fds[N_LISTEN];
अटल पूर्णांक proc_fd;
अटल स्थिर अक्षर *IP4_ADDR = "127.0.0.1";
अटल स्थिर अक्षर *IP6_ADDR = "::1";
अटल स्थिर पूर्णांक PORT = 8891;

अटल व्योम get_keys(पूर्णांक fd, uपूर्णांक32_t *keys)
अणु
	अक्षर buf[128];
	socklen_t len = KEY_LENGTH * 2;

	अगर (करो_sockopt) अणु
		अगर (माला_लोockopt(fd, SOL_TCP, TCP_FASTOPEN_KEY, keys, &len))
			error(1, त्रुटि_सं, "Unable to get key");
		वापस;
	पूर्ण
	lseek(proc_fd, 0, शुरू_से);
	अगर (पढ़ो(proc_fd, buf, माप(buf)) <= 0)
		error(1, त्रुटि_सं, "Unable to read %s", PROC_FASTOPEN_KEY);
	अगर (माला_पूछो(buf, "%x-%x-%x-%x,%x-%x-%x-%x", keys, keys + 1, keys + 2,
	    keys + 3, keys + 4, keys + 5, keys + 6, keys + 7) != 8)
		error(1, 0, "Unable to parse %s", PROC_FASTOPEN_KEY);
पूर्ण

अटल व्योम set_keys(पूर्णांक fd, uपूर्णांक32_t *keys)
अणु
	अक्षर buf[128];

	अगर (करो_sockopt) अणु
		अगर (setsockopt(fd, SOL_TCP, TCP_FASTOPEN_KEY, keys,
		    key_len))
			error(1, त्रुटि_सं, "Unable to set key");
		वापस;
	पूर्ण
	अगर (करो_rotate)
		snम_लिखो(buf, 128, "%08x-%08x-%08x-%08x,%08x-%08x-%08x-%08x",
			 keys[0], keys[1], keys[2], keys[3], keys[4], keys[5],
			 keys[6], keys[7]);
	अन्यथा
		snम_लिखो(buf, 128, "%08x-%08x-%08x-%08x",
			 keys[0], keys[1], keys[2], keys[3]);
	lseek(proc_fd, 0, शुरू_से);
	अगर (ग_लिखो(proc_fd, buf, माप(buf)) <= 0)
		error(1, त्रुटि_सं, "Unable to write %s", PROC_FASTOPEN_KEY);
पूर्ण

अटल व्योम build_rcv_fd(पूर्णांक family, पूर्णांक proto, पूर्णांक *rcv_fds)
अणु
	काष्ठा sockaddr_in  addr4 = अणु0पूर्ण;
	काष्ठा sockaddr_in6 addr6 = अणु0पूर्ण;
	काष्ठा sockaddr *addr;
	पूर्णांक opt = 1, i, sz;
	पूर्णांक qlen = 100;
	uपूर्णांक32_t keys[8];

	चयन (family) अणु
	हाल AF_INET:
		addr4.sin_family = family;
		addr4.sin_addr.s_addr = htonl(INADDR_ANY);
		addr4.sin_port = htons(PORT);
		sz = माप(addr4);
		addr = (काष्ठा sockaddr *)&addr4;
		अवरोध;
	हाल AF_INET6:
		addr6.sin6_family = AF_INET6;
		addr6.sin6_addr = in6addr_any;
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
	क्रम (i = 0; i < ARRAY_SIZE(keys); i++)
		keys[i] = अक्रम();
	क्रम (i = 0; i < N_LISTEN; i++) अणु
		rcv_fds[i] = socket(family, proto, 0);
		अगर (rcv_fds[i] < 0)
			error(1, त्रुटि_सं, "failed to create receive socket");
		अगर (setsockopt(rcv_fds[i], SOL_SOCKET, SO_REUSEPORT, &opt,
			       माप(opt)))
			error(1, त्रुटि_सं, "failed to set SO_REUSEPORT");
		अगर (bind(rcv_fds[i], addr, sz))
			error(1, त्रुटि_सं, "failed to bind receive socket");
		अगर (setsockopt(rcv_fds[i], SOL_TCP, TCP_FASTOPEN, &qlen,
			       माप(qlen)))
			error(1, त्रुटि_सं, "failed to set TCP_FASTOPEN");
		set_keys(rcv_fds[i], keys);
		अगर (proto == SOCK_STREAM && listen(rcv_fds[i], 10))
			error(1, त्रुटि_सं, "failed to listen on receive port");
	पूर्ण
पूर्ण

अटल पूर्णांक connect_and_send(पूर्णांक family, पूर्णांक proto)
अणु
	काष्ठा sockaddr_in  saddr4 = अणु0पूर्ण;
	काष्ठा sockaddr_in  daddr4 = अणु0पूर्ण;
	काष्ठा sockaddr_in6 saddr6 = अणु0पूर्ण;
	काष्ठा sockaddr_in6 daddr6 = अणु0पूर्ण;
	काष्ठा sockaddr *saddr, *daddr;
	पूर्णांक fd, sz, ret;
	अक्षर data[1];

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
	अगर (bind(fd, saddr, sz))
		error(1, त्रुटि_सं, "failed to bind send socket");
	data[0] = 'a';
	ret = sendto(fd, data, 1, MSG_FASTOPEN, daddr, sz);
	अगर (ret != 1)
		error(1, त्रुटि_सं, "failed to sendto");

	वापस fd;
पूर्ण

अटल bool is_listen_fd(पूर्णांक fd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < N_LISTEN; i++) अणु
		अगर (rcv_fds[i] == fd)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम rotate_key(पूर्णांक fd)
अणु
	अटल पूर्णांक iter;
	अटल uपूर्णांक32_t new_key[4];
	uपूर्णांक32_t keys[8];
	uपूर्णांक32_t पंचांगp_key[4];
	पूर्णांक i;

	अगर (iter < N_LISTEN) अणु
		/* first set new key as backups */
		अगर (iter == 0) अणु
			क्रम (i = 0; i < ARRAY_SIZE(new_key); i++)
				new_key[i] = अक्रम();
		पूर्ण
		get_keys(fd, keys);
		स_नकल(keys + 4, new_key, KEY_LENGTH);
		set_keys(fd, keys);
	पूर्ण अन्यथा अणु
		/* swap the keys */
		get_keys(fd, keys);
		स_नकल(पंचांगp_key, keys + 4, KEY_LENGTH);
		स_नकल(keys + 4, keys, KEY_LENGTH);
		स_नकल(keys, पंचांगp_key, KEY_LENGTH);
		set_keys(fd, keys);
	पूर्ण
	अगर (++iter >= (N_LISTEN * 2))
		iter = 0;
पूर्ण

अटल व्योम run_one_test(पूर्णांक family)
अणु
	काष्ठा epoll_event ev;
	पूर्णांक i, send_fd;
	पूर्णांक n_loops = 10000;
	पूर्णांक rotate_key_fd = 0;
	पूर्णांक key_rotate_पूर्णांकerval = 50;
	पूर्णांक fd, epfd;
	अक्षर buf[1];

	build_rcv_fd(family, SOCK_STREAM, rcv_fds);
	epfd = epoll_create(1);
	अगर (epfd < 0)
		error(1, त्रुटि_सं, "failed to create epoll");
	ev.events = EPOLLIN;
	क्रम (i = 0; i < N_LISTEN; i++) अणु
		ev.data.fd = rcv_fds[i];
		अगर (epoll_ctl(epfd, EPOLL_CTL_ADD, rcv_fds[i], &ev))
			error(1, त्रुटि_सं, "failed to register sock epoll");
	पूर्ण
	जबतक (n_loops--) अणु
		send_fd = connect_and_send(family, SOCK_STREAM);
		अगर (करो_rotate && ((n_loops % key_rotate_पूर्णांकerval) == 0)) अणु
			rotate_key(rcv_fds[rotate_key_fd]);
			अगर (++rotate_key_fd >= N_LISTEN)
				rotate_key_fd = 0;
		पूर्ण
		जबतक (1) अणु
			i = epoll_रुको(epfd, &ev, 1, -1);
			अगर (i < 0)
				error(1, त्रुटि_सं, "epoll_wait failed");
			अगर (is_listen_fd(ev.data.fd)) अणु
				fd = accept(ev.data.fd, शून्य, शून्य);
				अगर (fd < 0)
					error(1, त्रुटि_सं, "failed to accept");
				ev.data.fd = fd;
				अगर (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev))
					error(1, त्रुटि_सं, "failed epoll add");
				जारी;
			पूर्ण
			i = recv(ev.data.fd, buf, माप(buf), 0);
			अगर (i != 1)
				error(1, त्रुटि_सं, "failed recv data");
			अगर (epoll_ctl(epfd, EPOLL_CTL_DEL, ev.data.fd, शून्य))
				error(1, त्रुटि_सं, "failed epoll del");
			बंद(ev.data.fd);
			अवरोध;
		पूर्ण
		बंद(send_fd);
	पूर्ण
	क्रम (i = 0; i < N_LISTEN; i++)
		बंद(rcv_fds[i]);
पूर्ण

अटल व्योम parse_opts(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक c;

	जबतक ((c = getopt(argc, argv, "46sr")) != -1) अणु
		चयन (c) अणु
		हाल '4':
			करो_ipv6 = false;
			अवरोध;
		हाल '6':
			करो_ipv6 = true;
			अवरोध;
		हाल 's':
			करो_sockopt = true;
			अवरोध;
		हाल 'r':
			करो_rotate = true;
			key_len = KEY_LENGTH * 2;
			अवरोध;
		शेष:
			error(1, 0, "%s: parse error", argv[0]);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	parse_opts(argc, argv);
	proc_fd = खोलो(PROC_FASTOPEN_KEY, O_RDWR);
	अगर (proc_fd < 0)
		error(1, त्रुटि_सं, "Unable to open %s", PROC_FASTOPEN_KEY);
	बेक्रम(समय(शून्य));
	अगर (करो_ipv6)
		run_one_test(AF_INET6);
	अन्यथा
		run_one_test(AF_INET);
	बंद(proc_fd);
	ख_लिखो(मानक_त्रुटि, "PASS\n");
	वापस 0;
पूर्ण
