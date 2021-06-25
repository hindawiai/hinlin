<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test functionality of BPF filters with SO_REUSEPORT.  This program creates
 * an SO_REUSEPORT receiver group containing one socket per CPU core. It then
 * creates a BPF program that will select a socket from this group based
 * on the core id that receives the packet.  The sending code artअगरicially
 * moves itself to run on dअगरferent core ids and sends one message from
 * each core.  Since these packets are delivered over loopback, they should
 * arrive on the same core that sent them.  The receiving code then ensures
 * that the packet was received on the socket क्रम the corresponding core id.
 * This entire process is करोne क्रम several dअगरferent core id permutations
 * and क्रम each IPv4/IPv6 and TCP/UDP combination.
 */

#घोषणा _GNU_SOURCE

#समावेश <arpa/inet.h>
#समावेश <त्रुटिसं.स>
#समावेश <error.h>
#समावेश <linux/filter.h>
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
	काष्ठा sock_filter code[] = अणु
		/* A = raw_smp_processor_id() */
		अणु BPF_LD  | BPF_W | BPF_ABS, 0, 0, SKF_AD_OFF + SKF_AD_CPU पूर्ण,
		/* वापस A */
		अणु BPF_RET | BPF_A, 0, 0, 0 पूर्ण,
	पूर्ण;
	काष्ठा sock_fprog p = अणु
		.len = 2,
		.filter = code,
	पूर्ण;

	अगर (setsockopt(fd, SOL_SOCKET, SO_ATTACH_REUSEPORT_CBPF, &p, माप(p)))
		error(1, त्रुटि_सं, "failed to set SO_ATTACH_REUSEPORT_CBPF");
पूर्ण

अटल व्योम send_from_cpu(पूर्णांक cpu_id, पूर्णांक family, पूर्णांक proto)
अणु
	काष्ठा sockaddr_storage saddr, daddr;
	काष्ठा sockaddr_in  *saddr4, *daddr4;
	काष्ठा sockaddr_in6 *saddr6, *daddr6;
	cpu_set_t cpu_set;
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

	स_रखो(&cpu_set, 0, माप(cpu_set));
	CPU_SET(cpu_id, &cpu_set);
	अगर (sched_setaffinity(0, माप(cpu_set), &cpu_set) < 0)
		error(1, त्रुटि_सं, "failed to pin to cpu");

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
व्योम receive_on_cpu(पूर्णांक *rcv_fd, पूर्णांक len, पूर्णांक epfd, पूर्णांक cpu_id, पूर्णांक proto)
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
	ख_लिखो(मानक_त्रुटि, "send cpu %d, receive socket %d\n", cpu_id, i);
	अगर (cpu_id != i)
		error(1, 0, "cpu id/receive socket mismatch");
पूर्ण

अटल व्योम test(पूर्णांक *rcv_fd, पूर्णांक len, पूर्णांक family, पूर्णांक proto)
अणु
	काष्ठा epoll_event ev;
	पूर्णांक epfd, cpu;

	build_rcv_group(rcv_fd, len, family, proto);
	attach_bpf(rcv_fd[0]);

	epfd = epoll_create(1);
	अगर (epfd < 0)
		error(1, त्रुटि_सं, "failed to create epoll");
	क्रम (cpu = 0; cpu < len; ++cpu) अणु
		ev.events = EPOLLIN;
		ev.data.fd = rcv_fd[cpu];
		अगर (epoll_ctl(epfd, EPOLL_CTL_ADD, rcv_fd[cpu], &ev))
			error(1, त्रुटि_सं, "failed to register sock epoll");
	पूर्ण

	/* Forward iterate */
	क्रम (cpu = 0; cpu < len; ++cpu) अणु
		send_from_cpu(cpu, family, proto);
		receive_on_cpu(rcv_fd, len, epfd, cpu, proto);
	पूर्ण

	/* Reverse iterate */
	क्रम (cpu = len - 1; cpu >= 0; --cpu) अणु
		send_from_cpu(cpu, family, proto);
		receive_on_cpu(rcv_fd, len, epfd, cpu, proto);
	पूर्ण

	/* Even cores */
	क्रम (cpu = 0; cpu < len; cpu += 2) अणु
		send_from_cpu(cpu, family, proto);
		receive_on_cpu(rcv_fd, len, epfd, cpu, proto);
	पूर्ण

	/* Odd cores */
	क्रम (cpu = 1; cpu < len; cpu += 2) अणु
		send_from_cpu(cpu, family, proto);
		receive_on_cpu(rcv_fd, len, epfd, cpu, proto);
	पूर्ण

	बंद(epfd);
	क्रम (cpu = 0; cpu < len; ++cpu)
		बंद(rcv_fd[cpu]);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक *rcv_fd, cpus;

	cpus = sysconf(_SC_NPROCESSORS_ONLN);
	अगर (cpus <= 0)
		error(1, त्रुटि_सं, "failed counting cpus");

	rcv_fd = सुस्मृति(cpus, माप(पूर्णांक));
	अगर (!rcv_fd)
		error(1, 0, "failed to allocate array");

	ख_लिखो(मानक_त्रुटि, "---- IPv4 UDP ----\n");
	test(rcv_fd, cpus, AF_INET, SOCK_DGRAM);

	ख_लिखो(मानक_त्रुटि, "---- IPv6 UDP ----\n");
	test(rcv_fd, cpus, AF_INET6, SOCK_DGRAM);

	ख_लिखो(मानक_त्रुटि, "---- IPv4 TCP ----\n");
	test(rcv_fd, cpus, AF_INET, SOCK_STREAM);

	ख_लिखो(मानक_त्रुटि, "---- IPv6 TCP ----\n");
	test(rcv_fd, cpus, AF_INET6, SOCK_STREAM);

	मुक्त(rcv_fd);

	ख_लिखो(मानक_त्रुटि, "SUCCESS\n");
	वापस 0;
पूर्ण
