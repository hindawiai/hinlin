<शैली गुरु>
/*
 * Test functionality of BPF filters क्रम SO_REUSEPORT.  The tests below will use
 * a BPF program (both classic and extended) to पढ़ो the first word from an
 * incoming packet (expected to be in network byte-order), calculate a modulus
 * of that number, and then dispatch the packet to the Nth socket using the
 * result.  These tests are run क्रम each supported address family and protocol.
 * Additionally, a few edge हालs in the implementation are tested.
 */

#समावेश <त्रुटिसं.स>
#समावेश <error.h>
#समावेश <fcntl.h>
#समावेश <linux/bpf.h>
#समावेश <linux/filter.h>
#समावेश <linux/unistd.h>
#समावेश <netinet/in.h>
#समावेश <netinet/tcp.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/epoll.h>
#समावेश <sys/types.h>
#समावेश <sys/socket.h>
#समावेश <sys/resource.h>
#समावेश <unistd.h>

#अगर_अघोषित ARRAY_SIZE
#घोषणा ARRAY_SIZE(arr) (माप(arr) / माप((arr)[0]))
#पूर्ण_अगर

काष्ठा test_params अणु
	पूर्णांक recv_family;
	पूर्णांक send_family;
	पूर्णांक protocol;
	माप_प्रकार recv_socks;
	uपूर्णांक16_t recv_port;
	uपूर्णांक16_t send_port_min;
पूर्ण;

अटल माप_प्रकार sockaddr_size(व्योम)
अणु
	वापस माप(काष्ठा sockaddr_storage);
पूर्ण

अटल काष्ठा sockaddr *new_any_sockaddr(पूर्णांक family, uपूर्णांक16_t port)
अणु
	काष्ठा sockaddr_storage *addr;
	काष्ठा sockaddr_in *addr4;
	काष्ठा sockaddr_in6 *addr6;

	addr = दो_स्मृति(माप(काष्ठा sockaddr_storage));
	स_रखो(addr, 0, माप(काष्ठा sockaddr_storage));

	चयन (family) अणु
	हाल AF_INET:
		addr4 = (काष्ठा sockaddr_in *)addr;
		addr4->sin_family = AF_INET;
		addr4->sin_addr.s_addr = htonl(INADDR_ANY);
		addr4->sin_port = htons(port);
		अवरोध;
	हाल AF_INET6:
		addr6 = (काष्ठा sockaddr_in6 *)addr;
		addr6->sin6_family = AF_INET6;
		addr6->sin6_addr = in6addr_any;
		addr6->sin6_port = htons(port);
		अवरोध;
	शेष:
		error(1, 0, "Unsupported family %d", family);
	पूर्ण
	वापस (काष्ठा sockaddr *)addr;
पूर्ण

अटल काष्ठा sockaddr *new_loopback_sockaddr(पूर्णांक family, uपूर्णांक16_t port)
अणु
	काष्ठा sockaddr *addr = new_any_sockaddr(family, port);
	काष्ठा sockaddr_in *addr4;
	काष्ठा sockaddr_in6 *addr6;

	चयन (family) अणु
	हाल AF_INET:
		addr4 = (काष्ठा sockaddr_in *)addr;
		addr4->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		अवरोध;
	हाल AF_INET6:
		addr6 = (काष्ठा sockaddr_in6 *)addr;
		addr6->sin6_addr = in6addr_loopback;
		अवरोध;
	शेष:
		error(1, 0, "Unsupported family %d", family);
	पूर्ण
	वापस addr;
पूर्ण

अटल व्योम attach_ebpf(पूर्णांक fd, uपूर्णांक16_t mod)
अणु
	अटल अक्षर bpf_log_buf[65536];
	अटल स्थिर अक्षर bpf_license[] = "GPL";

	पूर्णांक bpf_fd;
	स्थिर काष्ठा bpf_insn prog[] = अणु
		/* BPF_MOV64_REG(BPF_REG_6, BPF_REG_1) */
		अणु BPF_ALU64 | BPF_MOV | BPF_X, BPF_REG_6, BPF_REG_1, 0, 0 पूर्ण,
		/* BPF_LD_ABS(BPF_W, 0) R0 = (uपूर्णांक32_t)skb[0] */
		अणु BPF_LD | BPF_ABS | BPF_W, 0, 0, 0, 0 पूर्ण,
		/* BPF_ALU64_IMM(BPF_MOD, BPF_REG_0, mod) */
		अणु BPF_ALU64 | BPF_MOD | BPF_K, BPF_REG_0, 0, 0, mod पूर्ण,
		/* BPF_EXIT_INSN() */
		अणु BPF_JMP | BPF_EXIT, 0, 0, 0, 0 पूर्ण
	पूर्ण;
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.prog_type = BPF_PROG_TYPE_SOCKET_FILTER;
	attr.insn_cnt = ARRAY_SIZE(prog);
	attr.insns = (अचिन्हित दीर्घ) &prog;
	attr.license = (अचिन्हित दीर्घ) &bpf_license;
	attr.log_buf = (अचिन्हित दीर्घ) &bpf_log_buf;
	attr.log_size = माप(bpf_log_buf);
	attr.log_level = 1;
	attr.kern_version = 0;

	bpf_fd = syscall(__NR_bpf, BPF_PROG_LOAD, &attr, माप(attr));
	अगर (bpf_fd < 0)
		error(1, त्रुटि_सं, "ebpf error. log:\n%s\n", bpf_log_buf);

	अगर (setsockopt(fd, SOL_SOCKET, SO_ATTACH_REUSEPORT_EBPF, &bpf_fd,
			माप(bpf_fd)))
		error(1, त्रुटि_सं, "failed to set SO_ATTACH_REUSEPORT_EBPF");

	बंद(bpf_fd);
पूर्ण

अटल व्योम attach_cbpf(पूर्णांक fd, uपूर्णांक16_t mod)
अणु
	काष्ठा sock_filter code[] = अणु
		/* A = (uपूर्णांक32_t)skb[0] */
		अणु BPF_LD  | BPF_W | BPF_ABS, 0, 0, 0 पूर्ण,
		/* A = A % mod */
		अणु BPF_ALU | BPF_MOD, 0, 0, mod पूर्ण,
		/* वापस A */
		अणु BPF_RET | BPF_A, 0, 0, 0 पूर्ण,
	पूर्ण;
	काष्ठा sock_fprog p = अणु
		.len = ARRAY_SIZE(code),
		.filter = code,
	पूर्ण;

	अगर (setsockopt(fd, SOL_SOCKET, SO_ATTACH_REUSEPORT_CBPF, &p, माप(p)))
		error(1, त्रुटि_सं, "failed to set SO_ATTACH_REUSEPORT_CBPF");
पूर्ण

अटल व्योम build_recv_group(स्थिर काष्ठा test_params p, पूर्णांक fd[], uपूर्णांक16_t mod,
			     व्योम (*attach_bpf)(पूर्णांक, uपूर्णांक16_t))
अणु
	काष्ठा sockaddr * स्थिर addr =
		new_any_sockaddr(p.recv_family, p.recv_port);
	पूर्णांक i, opt;

	क्रम (i = 0; i < p.recv_socks; ++i) अणु
		fd[i] = socket(p.recv_family, p.protocol, 0);
		अगर (fd[i] < 0)
			error(1, त्रुटि_सं, "failed to create recv %d", i);

		opt = 1;
		अगर (setsockopt(fd[i], SOL_SOCKET, SO_REUSEPORT, &opt,
			       माप(opt)))
			error(1, त्रुटि_सं, "failed to set SO_REUSEPORT on %d", i);

		अगर (i == 0)
			attach_bpf(fd[i], mod);

		अगर (bind(fd[i], addr, sockaddr_size()))
			error(1, त्रुटि_सं, "failed to bind recv socket %d", i);

		अगर (p.protocol == SOCK_STREAM) अणु
			opt = 4;
			अगर (setsockopt(fd[i], SOL_TCP, TCP_FASTOPEN, &opt,
				       माप(opt)))
				error(1, त्रुटि_सं,
				      "failed to set TCP_FASTOPEN on %d", i);
			अगर (listen(fd[i], p.recv_socks * 10))
				error(1, त्रुटि_सं, "failed to listen on socket");
		पूर्ण
	पूर्ण
	मुक्त(addr);
पूर्ण

अटल व्योम send_from(काष्ठा test_params p, uपूर्णांक16_t sport, अक्षर *buf,
		      माप_प्रकार len)
अणु
	काष्ठा sockaddr * स्थिर saddr = new_any_sockaddr(p.send_family, sport);
	काष्ठा sockaddr * स्थिर daddr =
		new_loopback_sockaddr(p.send_family, p.recv_port);
	स्थिर पूर्णांक fd = socket(p.send_family, p.protocol, 0), one = 1;

	अगर (fd < 0)
		error(1, त्रुटि_सं, "failed to create send socket");

	अगर (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, माप(one)))
		error(1, त्रुटि_सं, "failed to set reuseaddr");

	अगर (bind(fd, saddr, sockaddr_size()))
		error(1, त्रुटि_सं, "failed to bind send socket");

	अगर (sendto(fd, buf, len, MSG_FASTOPEN, daddr, sockaddr_size()) < 0)
		error(1, त्रुटि_सं, "failed to send message");

	बंद(fd);
	मुक्त(saddr);
	मुक्त(daddr);
पूर्ण

अटल व्योम test_recv_order(स्थिर काष्ठा test_params p, पूर्णांक fd[], पूर्णांक mod)
अणु
	अक्षर recv_buf[8], send_buf[8];
	काष्ठा msghdr msg;
	काष्ठा iovec recv_io = अणु recv_buf, 8 पूर्ण;
	काष्ठा epoll_event ev;
	पूर्णांक epfd, conn, i, sport, expected;
	uपूर्णांक32_t data, ndata;

	epfd = epoll_create(1);
	अगर (epfd < 0)
		error(1, त्रुटि_सं, "failed to create epoll");
	क्रम (i = 0; i < p.recv_socks; ++i) अणु
		ev.events = EPOLLIN;
		ev.data.fd = fd[i];
		अगर (epoll_ctl(epfd, EPOLL_CTL_ADD, fd[i], &ev))
			error(1, त्रुटि_सं, "failed to register sock %d epoll", i);
	पूर्ण

	स_रखो(&msg, 0, माप(msg));
	msg.msg_iov = &recv_io;
	msg.msg_iovlen = 1;

	क्रम (data = 0; data < p.recv_socks * 2; ++data) अणु
		sport = p.send_port_min + data;
		ndata = htonl(data);
		स_नकल(send_buf, &ndata, माप(ndata));
		send_from(p, sport, send_buf, माप(ndata));

		i = epoll_रुको(epfd, &ev, 1, -1);
		अगर (i < 0)
			error(1, त्रुटि_सं, "epoll wait failed");

		अगर (p.protocol == SOCK_STREAM) अणु
			conn = accept(ev.data.fd, शून्य, शून्य);
			अगर (conn < 0)
				error(1, त्रुटि_सं, "error accepting");
			i = recvmsg(conn, &msg, 0);
			बंद(conn);
		पूर्ण अन्यथा अणु
			i = recvmsg(ev.data.fd, &msg, 0);
		पूर्ण
		अगर (i < 0)
			error(1, त्रुटि_सं, "recvmsg error");
		अगर (i != माप(ndata))
			error(1, 0, "expected size %zd got %d",
			      माप(ndata), i);

		क्रम (i = 0; i < p.recv_socks; ++i)
			अगर (ev.data.fd == fd[i])
				अवरोध;
		स_नकल(&ndata, recv_buf, माप(ndata));
		ख_लिखो(मानक_त्रुटि, "Socket %d: %d\n", i, ntohl(ndata));

		expected = (sport % mod);
		अगर (i != expected)
			error(1, 0, "expected socket %d", expected);
	पूर्ण
पूर्ण

अटल व्योम test_reuseport_ebpf(काष्ठा test_params p)
अणु
	पूर्णांक i, fd[p.recv_socks];

	ख_लिखो(मानक_त्रुटि, "Testing EBPF mod %zd...\n", p.recv_socks);
	build_recv_group(p, fd, p.recv_socks, attach_ebpf);
	test_recv_order(p, fd, p.recv_socks);

	p.send_port_min += p.recv_socks * 2;
	ख_लिखो(मानक_त्रुटि, "Reprograming, testing mod %zd...\n", p.recv_socks / 2);
	attach_ebpf(fd[0], p.recv_socks / 2);
	test_recv_order(p, fd, p.recv_socks / 2);

	क्रम (i = 0; i < p.recv_socks; ++i)
		बंद(fd[i]);
पूर्ण

अटल व्योम test_reuseport_cbpf(काष्ठा test_params p)
अणु
	पूर्णांक i, fd[p.recv_socks];

	ख_लिखो(मानक_त्रुटि, "Testing CBPF mod %zd...\n", p.recv_socks);
	build_recv_group(p, fd, p.recv_socks, attach_cbpf);
	test_recv_order(p, fd, p.recv_socks);

	p.send_port_min += p.recv_socks * 2;
	ख_लिखो(मानक_त्रुटि, "Reprograming, testing mod %zd...\n", p.recv_socks / 2);
	attach_cbpf(fd[0], p.recv_socks / 2);
	test_recv_order(p, fd, p.recv_socks / 2);

	क्रम (i = 0; i < p.recv_socks; ++i)
		बंद(fd[i]);
पूर्ण

अटल व्योम test_extra_filter(स्थिर काष्ठा test_params p)
अणु
	काष्ठा sockaddr * स्थिर addr =
		new_any_sockaddr(p.recv_family, p.recv_port);
	पूर्णांक fd1, fd2, opt;

	ख_लिखो(मानक_त्रुटि, "Testing too many filters...\n");
	fd1 = socket(p.recv_family, p.protocol, 0);
	अगर (fd1 < 0)
		error(1, त्रुटि_सं, "failed to create socket 1");
	fd2 = socket(p.recv_family, p.protocol, 0);
	अगर (fd2 < 0)
		error(1, त्रुटि_सं, "failed to create socket 2");

	opt = 1;
	अगर (setsockopt(fd1, SOL_SOCKET, SO_REUSEPORT, &opt, माप(opt)))
		error(1, त्रुटि_सं, "failed to set SO_REUSEPORT on socket 1");
	अगर (setsockopt(fd2, SOL_SOCKET, SO_REUSEPORT, &opt, माप(opt)))
		error(1, त्रुटि_सं, "failed to set SO_REUSEPORT on socket 2");

	attach_ebpf(fd1, 10);
	attach_ebpf(fd2, 10);

	अगर (bind(fd1, addr, sockaddr_size()))
		error(1, त्रुटि_सं, "failed to bind recv socket 1");

	अगर (!bind(fd2, addr, sockaddr_size()) && त्रुटि_सं != EADDRINUSE)
		error(1, त्रुटि_सं, "bind socket 2 should fail with EADDRINUSE");

	मुक्त(addr);
पूर्ण

अटल व्योम test_filter_no_reuseport(स्थिर काष्ठा test_params p)
अणु
	काष्ठा sockaddr * स्थिर addr =
		new_any_sockaddr(p.recv_family, p.recv_port);
	स्थिर अक्षर bpf_license[] = "GPL";
	काष्ठा bpf_insn ecode[] = अणु
		अणु BPF_ALU64 | BPF_MOV | BPF_K, BPF_REG_0, 0, 0, 10 पूर्ण,
		अणु BPF_JMP | BPF_EXIT, 0, 0, 0, 0 पूर्ण
	पूर्ण;
	काष्ठा sock_filter ccode[] = अणुअणु BPF_RET | BPF_A, 0, 0, 0 पूर्णपूर्ण;
	जोड़ bpf_attr eprog;
	काष्ठा sock_fprog cprog;
	पूर्णांक fd, bpf_fd;

	ख_लिखो(मानक_त्रुटि, "Testing filters on non-SO_REUSEPORT socket...\n");

	स_रखो(&eprog, 0, माप(eprog));
	eprog.prog_type = BPF_PROG_TYPE_SOCKET_FILTER;
	eprog.insn_cnt = ARRAY_SIZE(ecode);
	eprog.insns = (अचिन्हित दीर्घ) &ecode;
	eprog.license = (अचिन्हित दीर्घ) &bpf_license;
	eprog.kern_version = 0;

	स_रखो(&cprog, 0, माप(cprog));
	cprog.len = ARRAY_SIZE(ccode);
	cprog.filter = ccode;


	bpf_fd = syscall(__NR_bpf, BPF_PROG_LOAD, &eprog, माप(eprog));
	अगर (bpf_fd < 0)
		error(1, त्रुटि_सं, "ebpf error");
	fd = socket(p.recv_family, p.protocol, 0);
	अगर (fd < 0)
		error(1, त्रुटि_सं, "failed to create socket 1");

	अगर (bind(fd, addr, sockaddr_size()))
		error(1, त्रुटि_सं, "failed to bind recv socket 1");

	त्रुटि_सं = 0;
	अगर (!setsockopt(fd, SOL_SOCKET, SO_ATTACH_REUSEPORT_EBPF, &bpf_fd,
			माप(bpf_fd)) || त्रुटि_सं != EINVAL)
		error(1, त्रुटि_सं, "setsockopt should have returned EINVAL");

	त्रुटि_सं = 0;
	अगर (!setsockopt(fd, SOL_SOCKET, SO_ATTACH_REUSEPORT_CBPF, &cprog,
		       माप(cprog)) || त्रुटि_सं != EINVAL)
		error(1, त्रुटि_सं, "setsockopt should have returned EINVAL");

	मुक्त(addr);
पूर्ण

अटल व्योम test_filter_without_bind(व्योम)
अणु
	पूर्णांक fd1, fd2, opt = 1;

	ख_लिखो(मानक_त्रुटि, "Testing filter add without bind...\n");
	fd1 = socket(AF_INET, SOCK_DGRAM, 0);
	अगर (fd1 < 0)
		error(1, त्रुटि_सं, "failed to create socket 1");
	fd2 = socket(AF_INET, SOCK_DGRAM, 0);
	अगर (fd2 < 0)
		error(1, त्रुटि_सं, "failed to create socket 2");
	अगर (setsockopt(fd1, SOL_SOCKET, SO_REUSEPORT, &opt, माप(opt)))
		error(1, त्रुटि_सं, "failed to set SO_REUSEPORT on socket 1");
	अगर (setsockopt(fd2, SOL_SOCKET, SO_REUSEPORT, &opt, माप(opt)))
		error(1, त्रुटि_सं, "failed to set SO_REUSEPORT on socket 2");

	attach_ebpf(fd1, 10);
	attach_cbpf(fd2, 10);

	बंद(fd1);
	बंद(fd2);
पूर्ण

व्योम enable_fastखोलो(व्योम)
अणु
	पूर्णांक fd = खोलो("/proc/sys/net/ipv4/tcp_fastopen", 0);
	पूर्णांक rw_mask = 3;  /* bit 1: client side; bit-2 server side */
	पूर्णांक val, size;
	अक्षर buf[16];

	अगर (fd < 0)
		error(1, त्रुटि_सं, "Unable to open tcp_fastopen sysctl");
	अगर (पढ़ो(fd, buf, माप(buf)) <= 0)
		error(1, त्रुटि_सं, "Unable to read tcp_fastopen sysctl");
	val = म_से_प(buf);
	बंद(fd);

	अगर ((val & rw_mask) != rw_mask) अणु
		fd = खोलो("/proc/sys/net/ipv4/tcp_fastopen", O_RDWR);
		अगर (fd < 0)
			error(1, त्रुटि_सं,
			      "Unable to open tcp_fastopen sysctl for writing");
		val |= rw_mask;
		size = snम_लिखो(buf, 16, "%d", val);
		अगर (ग_लिखो(fd, buf, size) <= 0)
			error(1, त्रुटि_सं, "Unable to write tcp_fastopen sysctl");
		बंद(fd);
	पूर्ण
पूर्ण

अटल काष्ठा rlimit rlim_old;

अटल  __attribute__((स्थिरructor)) व्योम मुख्य_ctor(व्योम)
अणु
	getrlimit(RLIMIT_MEMLOCK, &rlim_old);

	अगर (rlim_old.rlim_cur != RLIM_अनन्त) अणु
		काष्ठा rlimit rlim_new;

		rlim_new.rlim_cur = rlim_old.rlim_cur + (1UL << 20);
		rlim_new.rlim_max = rlim_old.rlim_max + (1UL << 20);
		setrlimit(RLIMIT_MEMLOCK, &rlim_new);
	पूर्ण
पूर्ण

अटल __attribute__((deकाष्ठाor)) व्योम मुख्य_dtor(व्योम)
अणु
	setrlimit(RLIMIT_MEMLOCK, &rlim_old);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "---- IPv4 UDP ----\n");
	/* NOTE: UDP socket lookups traverse a dअगरferent code path when there
	 * are > 10 sockets in a group.  Run the bpf test through both paths.
	 */
	test_reuseport_ebpf((काष्ठा test_params) अणु
		.recv_family = AF_INET,
		.send_family = AF_INET,
		.protocol = SOCK_DGRAM,
		.recv_socks = 10,
		.recv_port = 8000,
		.send_port_min = 9000पूर्ण);
	test_reuseport_ebpf((काष्ठा test_params) अणु
		.recv_family = AF_INET,
		.send_family = AF_INET,
		.protocol = SOCK_DGRAM,
		.recv_socks = 20,
		.recv_port = 8000,
		.send_port_min = 9000पूर्ण);
	test_reuseport_cbpf((काष्ठा test_params) अणु
		.recv_family = AF_INET,
		.send_family = AF_INET,
		.protocol = SOCK_DGRAM,
		.recv_socks = 10,
		.recv_port = 8001,
		.send_port_min = 9020पूर्ण);
	test_reuseport_cbpf((काष्ठा test_params) अणु
		.recv_family = AF_INET,
		.send_family = AF_INET,
		.protocol = SOCK_DGRAM,
		.recv_socks = 20,
		.recv_port = 8001,
		.send_port_min = 9020पूर्ण);
	test_extra_filter((काष्ठा test_params) अणु
		.recv_family = AF_INET,
		.protocol = SOCK_DGRAM,
		.recv_port = 8002पूर्ण);
	test_filter_no_reuseport((काष्ठा test_params) अणु
		.recv_family = AF_INET,
		.protocol = SOCK_DGRAM,
		.recv_port = 8008पूर्ण);

	ख_लिखो(मानक_त्रुटि, "---- IPv6 UDP ----\n");
	test_reuseport_ebpf((काष्ठा test_params) अणु
		.recv_family = AF_INET6,
		.send_family = AF_INET6,
		.protocol = SOCK_DGRAM,
		.recv_socks = 10,
		.recv_port = 8003,
		.send_port_min = 9040पूर्ण);
	test_reuseport_ebpf((काष्ठा test_params) अणु
		.recv_family = AF_INET6,
		.send_family = AF_INET6,
		.protocol = SOCK_DGRAM,
		.recv_socks = 20,
		.recv_port = 8003,
		.send_port_min = 9040पूर्ण);
	test_reuseport_cbpf((काष्ठा test_params) अणु
		.recv_family = AF_INET6,
		.send_family = AF_INET6,
		.protocol = SOCK_DGRAM,
		.recv_socks = 10,
		.recv_port = 8004,
		.send_port_min = 9060पूर्ण);
	test_reuseport_cbpf((काष्ठा test_params) अणु
		.recv_family = AF_INET6,
		.send_family = AF_INET6,
		.protocol = SOCK_DGRAM,
		.recv_socks = 20,
		.recv_port = 8004,
		.send_port_min = 9060पूर्ण);
	test_extra_filter((काष्ठा test_params) अणु
		.recv_family = AF_INET6,
		.protocol = SOCK_DGRAM,
		.recv_port = 8005पूर्ण);
	test_filter_no_reuseport((काष्ठा test_params) अणु
		.recv_family = AF_INET6,
		.protocol = SOCK_DGRAM,
		.recv_port = 8009पूर्ण);

	ख_लिखो(मानक_त्रुटि, "---- IPv6 UDP w/ mapped IPv4 ----\n");
	test_reuseport_ebpf((काष्ठा test_params) अणु
		.recv_family = AF_INET6,
		.send_family = AF_INET,
		.protocol = SOCK_DGRAM,
		.recv_socks = 20,
		.recv_port = 8006,
		.send_port_min = 9080पूर्ण);
	test_reuseport_ebpf((काष्ठा test_params) अणु
		.recv_family = AF_INET6,
		.send_family = AF_INET,
		.protocol = SOCK_DGRAM,
		.recv_socks = 10,
		.recv_port = 8006,
		.send_port_min = 9080पूर्ण);
	test_reuseport_cbpf((काष्ठा test_params) अणु
		.recv_family = AF_INET6,
		.send_family = AF_INET,
		.protocol = SOCK_DGRAM,
		.recv_socks = 10,
		.recv_port = 8007,
		.send_port_min = 9100पूर्ण);
	test_reuseport_cbpf((काष्ठा test_params) अणु
		.recv_family = AF_INET6,
		.send_family = AF_INET,
		.protocol = SOCK_DGRAM,
		.recv_socks = 20,
		.recv_port = 8007,
		.send_port_min = 9100पूर्ण);

	/* TCP fastखोलो is required क्रम the TCP tests */
	enable_fastखोलो();
	ख_लिखो(मानक_त्रुटि, "---- IPv4 TCP ----\n");
	test_reuseport_ebpf((काष्ठा test_params) अणु
		.recv_family = AF_INET,
		.send_family = AF_INET,
		.protocol = SOCK_STREAM,
		.recv_socks = 10,
		.recv_port = 8008,
		.send_port_min = 9120पूर्ण);
	test_reuseport_cbpf((काष्ठा test_params) अणु
		.recv_family = AF_INET,
		.send_family = AF_INET,
		.protocol = SOCK_STREAM,
		.recv_socks = 10,
		.recv_port = 8009,
		.send_port_min = 9160पूर्ण);
	test_extra_filter((काष्ठा test_params) अणु
		.recv_family = AF_INET,
		.protocol = SOCK_STREAM,
		.recv_port = 8010पूर्ण);
	test_filter_no_reuseport((काष्ठा test_params) अणु
		.recv_family = AF_INET,
		.protocol = SOCK_STREAM,
		.recv_port = 8011पूर्ण);

	ख_लिखो(मानक_त्रुटि, "---- IPv6 TCP ----\n");
	test_reuseport_ebpf((काष्ठा test_params) अणु
		.recv_family = AF_INET6,
		.send_family = AF_INET6,
		.protocol = SOCK_STREAM,
		.recv_socks = 10,
		.recv_port = 8012,
		.send_port_min = 9200पूर्ण);
	test_reuseport_cbpf((काष्ठा test_params) अणु
		.recv_family = AF_INET6,
		.send_family = AF_INET6,
		.protocol = SOCK_STREAM,
		.recv_socks = 10,
		.recv_port = 8013,
		.send_port_min = 9240पूर्ण);
	test_extra_filter((काष्ठा test_params) अणु
		.recv_family = AF_INET6,
		.protocol = SOCK_STREAM,
		.recv_port = 8014पूर्ण);
	test_filter_no_reuseport((काष्ठा test_params) अणु
		.recv_family = AF_INET6,
		.protocol = SOCK_STREAM,
		.recv_port = 8015पूर्ण);

	ख_लिखो(मानक_त्रुटि, "---- IPv6 TCP w/ mapped IPv4 ----\n");
	test_reuseport_ebpf((काष्ठा test_params) अणु
		.recv_family = AF_INET6,
		.send_family = AF_INET,
		.protocol = SOCK_STREAM,
		.recv_socks = 10,
		.recv_port = 8016,
		.send_port_min = 9320पूर्ण);
	test_reuseport_cbpf((काष्ठा test_params) अणु
		.recv_family = AF_INET6,
		.send_family = AF_INET,
		.protocol = SOCK_STREAM,
		.recv_socks = 10,
		.recv_port = 8017,
		.send_port_min = 9360पूर्ण);

	test_filter_without_bind();

	ख_लिखो(मानक_त्रुटि, "SUCCESS\n");
	वापस 0;
पूर्ण
