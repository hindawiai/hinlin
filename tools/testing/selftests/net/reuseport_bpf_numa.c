<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test functionality of BPF filters with SO_REUSEPORT. Same test as
 * in reuseport_bpf_cpu, only as one socket per NUMA node.
 */

#घोषणा _GNU_SOURCE

#समावेश <arpa/inet.h>
#समावेश <त्रुटिसं.स>
#समावेश <error.h>
#समावेश <linux/filter.h>
#समावेश <linux/bpf.h>
#समावेश <linux/in.h>
#समावेश <linux/unistd.h>
#समावेश <sched.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/epoll.h>
#समावेश <sys/types.h>
#समावेश <sys/socket.h>
#समावेश <unistd.h>
#समावेश <numa.h>

#समावेश "../kselftest.h"

अटल स्थिर पूर्णांक PORT = 8888;

अटल व्योम build_rcv_group(पूर्णांक *rcv_fd, माप_प्रकार len, पूर्णांक family, पूर्णांक proto)
अणु
	काष्ठा sockaddr_storage addr;
	काष्ठा sockaddr_in  *addr4;
	काष्ठा sockaddr_in6 *addr6;
	माप_प्रकार i;
	पूर्णांक opt;

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

	क्रम (i = 0; i < len; ++i) अणु
		rcv_fd[i] = socket(family, proto, 0);
		अगर (rcv_fd[i] < 0)
			error(1, त्रुटि_सं, "failed to create receive socket");

		opt = 1;
		अगर (setsockopt(rcv_fd[i], SOL_SOCKET, SO_REUSEPORT, &opt,
			       माप(opt)))
			error(1, त्रुटि_सं, "failed to set SO_REUSEPORT");

		अगर (bind(rcv_fd[i], (काष्ठा sockaddr *)&addr, माप(addr)))
			error(1, त्रुटि_सं, "failed to bind receive socket");

		अगर (proto == SOCK_STREAM && listen(rcv_fd[i], len * 10))
			error(1, त्रुटि_सं, "failed to listen on receive port");
	पूर्ण
पूर्ण

अटल व्योम attach_bpf(पूर्णांक fd)
अणु
	अटल अक्षर bpf_log_buf[65536];
	अटल स्थिर अक्षर bpf_license[] = "";

	पूर्णांक bpf_fd;
	स्थिर काष्ठा bpf_insn prog[] = अणु
		/* R0 = bpf_get_numa_node_id() */
		अणु BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_get_numa_node_id पूर्ण,
		/* वापस R0 */
		अणु BPF_JMP | BPF_EXIT, 0, 0, 0, 0 पूर्ण
	पूर्ण;
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.prog_type = BPF_PROG_TYPE_SOCKET_FILTER;
	attr.insn_cnt = माप(prog) / माप(prog[0]);
	attr.insns = (अचिन्हित दीर्घ) &prog;
	attr.license = (अचिन्हित दीर्घ) &bpf_license;
	attr.log_buf = (अचिन्हित दीर्घ) &bpf_log_buf;
	attr.log_size = माप(bpf_log_buf);
	attr.log_level = 1;

	bpf_fd = syscall(__NR_bpf, BPF_PROG_LOAD, &attr, माप(attr));
	अगर (bpf_fd < 0)
		error(1, त्रुटि_सं, "ebpf error. log:\n%s\n", bpf_log_buf);

	अगर (setsockopt(fd, SOL_SOCKET, SO_ATTACH_REUSEPORT_EBPF, &bpf_fd,
			माप(bpf_fd)))
		error(1, त्रुटि_सं, "failed to set SO_ATTACH_REUSEPORT_EBPF");

	बंद(bpf_fd);
पूर्ण

अटल व्योम send_from_node(पूर्णांक node_id, पूर्णांक family, पूर्णांक proto)
अणु
	काष्ठा sockaddr_storage saddr, daddr;
	काष्ठा sockaddr_in  *saddr4, *daddr4;
	काष्ठा sockaddr_in6 *saddr6, *daddr6;
	पूर्णांक fd;

	चयन (family) अणु
	हाल AF_INET:
		saddr4 = (काष्ठा sockaddr_in *)&saddr;
		saddr4->sin_family = AF_INET;
		saddr4->sin_addr.s_addr = htonl(INADDR_ANY);
		saddr4->sin_port = 0;

		daddr4 = (काष्ठा sockaddr_in *)&daddr;
		daddr4->sin_family = AF_INET;
		daddr4->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		daddr4->sin_port = htons(PORT);
		अवरोध;
	हाल AF_INET6:
		saddr6 = (काष्ठा sockaddr_in6 *)&saddr;
		saddr6->sin6_family = AF_INET6;
		saddr6->sin6_addr = in6addr_any;
		saddr6->sin6_port = 0;

		daddr6 = (काष्ठा sockaddr_in6 *)&daddr;
		daddr6->sin6_family = AF_INET6;
		daddr6->sin6_addr = in6addr_loopback;
		daddr6->sin6_port = htons(PORT);
		अवरोध;
	शेष:
		error(1, 0, "Unsupported family %d", family);
	पूर्ण

	अगर (numa_run_on_node(node_id) < 0)
		error(1, त्रुटि_सं, "failed to pin to node");

	fd = socket(family, proto, 0);
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

अटल
व्योम receive_on_node(पूर्णांक *rcv_fd, पूर्णांक len, पूर्णांक epfd, पूर्णांक node_id, पूर्णांक proto)
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

	क्रम (i = 0; i < len; ++i)
		अगर (ev.data.fd == rcv_fd[i])
			अवरोध;
	अगर (i == len)
		error(1, 0, "failed to find socket");
	ख_लिखो(मानक_त्रुटि, "send node %d, receive socket %d\n", node_id, i);
	अगर (node_id != i)
		error(1, 0, "node id/receive socket mismatch");
पूर्ण

अटल व्योम test(पूर्णांक *rcv_fd, पूर्णांक len, पूर्णांक family, पूर्णांक proto)
अणु
	काष्ठा epoll_event ev;
	पूर्णांक epfd, node;

	build_rcv_group(rcv_fd, len, family, proto);
	attach_bpf(rcv_fd[0]);

	epfd = epoll_create(1);
	अगर (epfd < 0)
		error(1, त्रुटि_सं, "failed to create epoll");
	क्रम (node = 0; node < len; ++node) अणु
		ev.events = EPOLLIN;
		ev.data.fd = rcv_fd[node];
		अगर (epoll_ctl(epfd, EPOLL_CTL_ADD, rcv_fd[node], &ev))
			error(1, त्रुटि_सं, "failed to register sock epoll");
	पूर्ण

	/* Forward iterate */
	क्रम (node = 0; node < len; ++node) अणु
		send_from_node(node, family, proto);
		receive_on_node(rcv_fd, len, epfd, node, proto);
	पूर्ण

	/* Reverse iterate */
	क्रम (node = len - 1; node >= 0; --node) अणु
		send_from_node(node, family, proto);
		receive_on_node(rcv_fd, len, epfd, node, proto);
	पूर्ण

	बंद(epfd);
	क्रम (node = 0; node < len; ++node)
		बंद(rcv_fd[node]);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक *rcv_fd, nodes;

	अगर (numa_available() < 0)
		ksft_निकास_skip("no numa api support\n");

	nodes = numa_max_node() + 1;

	rcv_fd = सुस्मृति(nodes, माप(पूर्णांक));
	अगर (!rcv_fd)
		error(1, 0, "failed to allocate array");

	ख_लिखो(मानक_त्रुटि, "---- IPv4 UDP ----\n");
	test(rcv_fd, nodes, AF_INET, SOCK_DGRAM);

	ख_लिखो(मानक_त्रुटि, "---- IPv6 UDP ----\n");
	test(rcv_fd, nodes, AF_INET6, SOCK_DGRAM);

	ख_लिखो(मानक_त्रुटि, "---- IPv4 TCP ----\n");
	test(rcv_fd, nodes, AF_INET, SOCK_STREAM);

	ख_लिखो(मानक_त्रुटि, "---- IPv6 TCP ----\n");
	test(rcv_fd, nodes, AF_INET6, SOCK_STREAM);

	मुक्त(rcv_fd);

	ख_लिखो(मानक_त्रुटि, "SUCCESS\n");
	वापस 0;
पूर्ण
