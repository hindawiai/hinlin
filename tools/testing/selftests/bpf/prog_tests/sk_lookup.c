<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
// Copyright (c) 2020 Cloudflare
/*
 * Test BPF attach poपूर्णांक क्रम INET socket lookup (BPF_SK_LOOKUP).
 *
 * Tests exercise:
 *  - attaching/detaching/querying programs to BPF_SK_LOOKUP hook,
 *  - redirecting socket lookup to a socket selected by BPF program,
 *  - failing a socket lookup on BPF program's request,
 *  - error scenarios क्रम selecting a socket from BPF program,
 *  - accessing BPF program context,
 *  - attaching and running multiple BPF programs.
 *
 * Tests run in a dedicated network namespace.
 */

#घोषणा _GNU_SOURCE
#समावेश <arpa/inet.h>
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <error.h>
#समावेश <fcntl.h>
#समावेश <sched.h>
#समावेश <मानकपन.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>

#समावेश <bpf/libbpf.h>
#समावेश <bpf/bpf.h>

#समावेश "test_progs.h"
#समावेश "bpf_rlimit.h"
#समावेश "bpf_util.h"
#समावेश "cgroup_helpers.h"
#समावेश "network_helpers.h"
#समावेश "testing_helpers.h"
#समावेश "test_sk_lookup.skel.h"

/* External (address, port) pairs the client sends packets to. */
#घोषणा EXT_IP4		"127.0.0.1"
#घोषणा EXT_IP6		"fd00::1"
#घोषणा EXT_PORT	7007

/* Internal (address, port) pairs the server listens/receives at. */
#घोषणा INT_IP4		"127.0.0.2"
#घोषणा INT_IP4_V6	"::ffff:127.0.0.2"
#घोषणा INT_IP6		"fd00::2"
#घोषणा INT_PORT	8008

#घोषणा IO_TIMEOUT_SEC	3

क्रमागत server अणु
	SERVER_A = 0,
	SERVER_B = 1,
	MAX_SERVERS,
पूर्ण;

क्रमागत अणु
	PROG1 = 0,
	PROG2,
पूर्ण;

काष्ठा inet_addr अणु
	स्थिर अक्षर *ip;
	अचिन्हित लघु port;
पूर्ण;

काष्ठा test अणु
	स्थिर अक्षर *desc;
	काष्ठा bpf_program *lookup_prog;
	काष्ठा bpf_program *reuseport_prog;
	काष्ठा bpf_map *sock_map;
	पूर्णांक sotype;
	काष्ठा inet_addr connect_to;
	काष्ठा inet_addr listen_at;
	क्रमागत server accept_on;
	bool reuseport_has_conns; /* Add a connected socket to reuseport group */
पूर्ण;

अटल __u32 duration;		/* क्रम CHECK macro */

अटल bool is_ipv6(स्थिर अक्षर *ip)
अणु
	वापस !!म_अक्षर(ip, ':');
पूर्ण

अटल पूर्णांक attach_reuseport(पूर्णांक sock_fd, काष्ठा bpf_program *reuseport_prog)
अणु
	पूर्णांक err, prog_fd;

	prog_fd = bpf_program__fd(reuseport_prog);
	अगर (prog_fd < 0) अणु
		त्रुटि_सं = -prog_fd;
		वापस -1;
	पूर्ण

	err = setsockopt(sock_fd, SOL_SOCKET, SO_ATTACH_REUSEPORT_EBPF,
			 &prog_fd, माप(prog_fd));
	अगर (err)
		वापस -1;

	वापस 0;
पूर्ण

अटल socklen_t inetaddr_len(स्थिर काष्ठा sockaddr_storage *addr)
अणु
	वापस (addr->ss_family == AF_INET ? माप(काष्ठा sockaddr_in) :
		addr->ss_family == AF_INET6 ? माप(काष्ठा sockaddr_in6) : 0);
पूर्ण

अटल पूर्णांक make_socket(पूर्णांक sotype, स्थिर अक्षर *ip, पूर्णांक port,
		       काष्ठा sockaddr_storage *addr)
अणु
	काष्ठा समयval समयo = अणु .tv_sec = IO_TIMEOUT_SEC पूर्ण;
	पूर्णांक err, family, fd;

	family = is_ipv6(ip) ? AF_INET6 : AF_INET;
	err = make_sockaddr(family, ip, port, addr, शून्य);
	अगर (CHECK(err, "make_address", "failed\n"))
		वापस -1;

	fd = socket(addr->ss_family, sotype, 0);
	अगर (CHECK(fd < 0, "socket", "failed\n")) अणु
		log_err("failed to make socket");
		वापस -1;
	पूर्ण

	err = setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &समयo, माप(समयo));
	अगर (CHECK(err, "setsockopt(SO_SNDTIMEO)", "failed\n")) अणु
		log_err("failed to set SNDTIMEO");
		बंद(fd);
		वापस -1;
	पूर्ण

	err = setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &समयo, माप(समयo));
	अगर (CHECK(err, "setsockopt(SO_RCVTIMEO)", "failed\n")) अणु
		log_err("failed to set RCVTIMEO");
		बंद(fd);
		वापस -1;
	पूर्ण

	वापस fd;
पूर्ण

अटल पूर्णांक make_server(पूर्णांक sotype, स्थिर अक्षर *ip, पूर्णांक port,
		       काष्ठा bpf_program *reuseport_prog)
अणु
	काष्ठा sockaddr_storage addr = अणु0पूर्ण;
	स्थिर पूर्णांक one = 1;
	पूर्णांक err, fd = -1;

	fd = make_socket(sotype, ip, port, &addr);
	अगर (fd < 0)
		वापस -1;

	/* Enabled क्रम UDPv6 sockets क्रम IPv4-mapped IPv6 to work. */
	अगर (sotype == SOCK_DGRAM) अणु
		err = setsockopt(fd, SOL_IP, IP_RECVORIGDSTADDR, &one,
				 माप(one));
		अगर (CHECK(err, "setsockopt(IP_RECVORIGDSTADDR)", "failed\n")) अणु
			log_err("failed to enable IP_RECVORIGDSTADDR");
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (sotype == SOCK_DGRAM && addr.ss_family == AF_INET6) अणु
		err = setsockopt(fd, SOL_IPV6, IPV6_RECVORIGDSTADDR, &one,
				 माप(one));
		अगर (CHECK(err, "setsockopt(IPV6_RECVORIGDSTADDR)", "failed\n")) अणु
			log_err("failed to enable IPV6_RECVORIGDSTADDR");
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (sotype == SOCK_STREAM) अणु
		err = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one,
				 माप(one));
		अगर (CHECK(err, "setsockopt(SO_REUSEADDR)", "failed\n")) अणु
			log_err("failed to enable SO_REUSEADDR");
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (reuseport_prog) अणु
		err = setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &one,
				 माप(one));
		अगर (CHECK(err, "setsockopt(SO_REUSEPORT)", "failed\n")) अणु
			log_err("failed to enable SO_REUSEPORT");
			जाओ fail;
		पूर्ण
	पूर्ण

	err = bind(fd, (व्योम *)&addr, inetaddr_len(&addr));
	अगर (CHECK(err, "bind", "failed\n")) अणु
		log_err("failed to bind listen socket");
		जाओ fail;
	पूर्ण

	अगर (sotype == SOCK_STREAM) अणु
		err = listen(fd, SOMAXCONN);
		अगर (CHECK(err, "make_server", "listen")) अणु
			log_err("failed to listen on port %d", port);
			जाओ fail;
		पूर्ण
	पूर्ण

	/* Late attach reuseport prog so we can have one init path */
	अगर (reuseport_prog) अणु
		err = attach_reuseport(fd, reuseport_prog);
		अगर (CHECK(err, "attach_reuseport", "failed\n")) अणु
			log_err("failed to attach reuseport prog");
			जाओ fail;
		पूर्ण
	पूर्ण

	वापस fd;
fail:
	बंद(fd);
	वापस -1;
पूर्ण

अटल पूर्णांक make_client(पूर्णांक sotype, स्थिर अक्षर *ip, पूर्णांक port)
अणु
	काष्ठा sockaddr_storage addr = अणु0पूर्ण;
	पूर्णांक err, fd;

	fd = make_socket(sotype, ip, port, &addr);
	अगर (fd < 0)
		वापस -1;

	err = connect(fd, (व्योम *)&addr, inetaddr_len(&addr));
	अगर (CHECK(err, "make_client", "connect")) अणु
		log_err("failed to connect client socket");
		जाओ fail;
	पूर्ण

	वापस fd;
fail:
	बंद(fd);
	वापस -1;
पूर्ण

अटल __u64 socket_cookie(पूर्णांक fd)
अणु
	__u64 cookie;
	socklen_t cookie_len = माप(cookie);

	अगर (CHECK(माला_लोockopt(fd, SOL_SOCKET, SO_COOKIE, &cookie, &cookie_len) < 0,
		  "getsockopt(SO_COOKIE)", "%s\n", म_त्रुटि(त्रुटि_सं)))
		वापस 0;
	वापस cookie;
पूर्ण

अटल पूर्णांक fill_sk_lookup_ctx(काष्ठा bpf_sk_lookup *ctx, स्थिर अक्षर *local_ip, __u16 local_port,
			      स्थिर अक्षर *remote_ip, __u16 remote_port)
अणु
	व्योम *local, *remote;
	पूर्णांक err;

	स_रखो(ctx, 0, माप(*ctx));
	ctx->local_port = local_port;
	ctx->remote_port = htons(remote_port);

	अगर (is_ipv6(local_ip)) अणु
		ctx->family = AF_INET6;
		local = &ctx->local_ip6[0];
		remote = &ctx->remote_ip6[0];
	पूर्ण अन्यथा अणु
		ctx->family = AF_INET;
		local = &ctx->local_ip4;
		remote = &ctx->remote_ip4;
	पूर्ण

	err = inet_pton(ctx->family, local_ip, local);
	अगर (CHECK(err != 1, "inet_pton", "local_ip failed\n"))
		वापस 1;

	err = inet_pton(ctx->family, remote_ip, remote);
	अगर (CHECK(err != 1, "inet_pton", "remote_ip failed\n"))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक send_byte(पूर्णांक fd)
अणु
	sमाप_प्रकार n;

	त्रुटि_सं = 0;
	n = send(fd, "a", 1, 0);
	अगर (CHECK(n <= 0, "send_byte", "send")) अणु
		log_err("failed/partial send");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक recv_byte(पूर्णांक fd)
अणु
	अक्षर buf[1];
	sमाप_प्रकार n;

	n = recv(fd, buf, माप(buf), 0);
	अगर (CHECK(n <= 0, "recv_byte", "recv")) अणु
		log_err("failed/partial recv");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tcp_recv_send(पूर्णांक server_fd)
अणु
	अक्षर buf[1];
	पूर्णांक ret, fd;
	sमाप_प्रकार n;

	fd = accept(server_fd, शून्य, शून्य);
	अगर (CHECK(fd < 0, "accept", "failed\n")) अणु
		log_err("failed to accept");
		वापस -1;
	पूर्ण

	n = recv(fd, buf, माप(buf), 0);
	अगर (CHECK(n <= 0, "recv", "failed\n")) अणु
		log_err("failed/partial recv");
		ret = -1;
		जाओ बंद;
	पूर्ण

	n = send(fd, buf, n, 0);
	अगर (CHECK(n <= 0, "send", "failed\n")) अणु
		log_err("failed/partial send");
		ret = -1;
		जाओ बंद;
	पूर्ण

	ret = 0;
बंद:
	बंद(fd);
	वापस ret;
पूर्ण

अटल व्योम v4_to_v6(काष्ठा sockaddr_storage *ss)
अणु
	काष्ठा sockaddr_in6 *v6 = (काष्ठा sockaddr_in6 *)ss;
	काष्ठा sockaddr_in v4 = *(काष्ठा sockaddr_in *)ss;

	v6->sin6_family = AF_INET6;
	v6->sin6_port = v4.sin_port;
	v6->sin6_addr.s6_addr[10] = 0xff;
	v6->sin6_addr.s6_addr[11] = 0xff;
	स_नकल(&v6->sin6_addr.s6_addr[12], &v4.sin_addr.s_addr, 4);
	स_रखो(&v6->sin6_addr.s6_addr[0], 0, 10);
पूर्ण

अटल पूर्णांक udp_recv_send(पूर्णांक server_fd)
अणु
	अक्षर cmsg_buf[CMSG_SPACE(माप(काष्ठा sockaddr_storage))];
	काष्ठा sockaddr_storage _src_addr = अणु 0 पूर्ण;
	काष्ठा sockaddr_storage *src_addr = &_src_addr;
	काष्ठा sockaddr_storage *dst_addr = शून्य;
	काष्ठा msghdr msg = अणु 0 पूर्ण;
	काष्ठा iovec iov = अणु 0 पूर्ण;
	काष्ठा cmsghdr *cm;
	अक्षर buf[1];
	पूर्णांक ret, fd;
	sमाप_प्रकार n;

	iov.iov_base = buf;
	iov.iov_len = माप(buf);

	msg.msg_name = src_addr;
	msg.msg_namelen = माप(*src_addr);
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = cmsg_buf;
	msg.msg_controllen = माप(cmsg_buf);

	त्रुटि_सं = 0;
	n = recvmsg(server_fd, &msg, 0);
	अगर (CHECK(n <= 0, "recvmsg", "failed\n")) अणु
		log_err("failed to receive");
		वापस -1;
	पूर्ण
	अगर (CHECK(msg.msg_flags & MSG_CTRUNC, "recvmsg", "truncated cmsg\n"))
		वापस -1;

	क्रम (cm = CMSG_FIRSTHDR(&msg); cm; cm = CMSG_NXTHDR(&msg, cm)) अणु
		अगर ((cm->cmsg_level == SOL_IP &&
		     cm->cmsg_type == IP_ORIGDSTADDR) ||
		    (cm->cmsg_level == SOL_IPV6 &&
		     cm->cmsg_type == IPV6_ORIGDSTADDR)) अणु
			dst_addr = (काष्ठा sockaddr_storage *)CMSG_DATA(cm);
			अवरोध;
		पूर्ण
		log_err("warning: ignored cmsg at level %d type %d",
			cm->cmsg_level, cm->cmsg_type);
	पूर्ण
	अगर (CHECK(!dst_addr, "recvmsg", "missing ORIGDSTADDR\n"))
		वापस -1;

	/* Server socket bound to IPv4-mapped IPv6 address */
	अगर (src_addr->ss_family == AF_INET6 &&
	    dst_addr->ss_family == AF_INET) अणु
		v4_to_v6(dst_addr);
	पूर्ण

	/* Reply from original destination address. */
	fd = socket(dst_addr->ss_family, SOCK_DGRAM, 0);
	अगर (CHECK(fd < 0, "socket", "failed\n")) अणु
		log_err("failed to create tx socket");
		वापस -1;
	पूर्ण

	ret = bind(fd, (काष्ठा sockaddr *)dst_addr, माप(*dst_addr));
	अगर (CHECK(ret, "bind", "failed\n")) अणु
		log_err("failed to bind tx socket");
		जाओ out;
	पूर्ण

	msg.msg_control = शून्य;
	msg.msg_controllen = 0;
	n = sendmsg(fd, &msg, 0);
	अगर (CHECK(n <= 0, "sendmsg", "failed\n")) अणु
		log_err("failed to send echo reply");
		ret = -1;
		जाओ out;
	पूर्ण

	ret = 0;
out:
	बंद(fd);
	वापस ret;
पूर्ण

अटल पूर्णांक tcp_echo_test(पूर्णांक client_fd, पूर्णांक server_fd)
अणु
	पूर्णांक err;

	err = send_byte(client_fd);
	अगर (err)
		वापस -1;
	err = tcp_recv_send(server_fd);
	अगर (err)
		वापस -1;
	err = recv_byte(client_fd);
	अगर (err)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक udp_echo_test(पूर्णांक client_fd, पूर्णांक server_fd)
अणु
	पूर्णांक err;

	err = send_byte(client_fd);
	अगर (err)
		वापस -1;
	err = udp_recv_send(server_fd);
	अगर (err)
		वापस -1;
	err = recv_byte(client_fd);
	अगर (err)
		वापस -1;

	वापस 0;
पूर्ण

अटल काष्ठा bpf_link *attach_lookup_prog(काष्ठा bpf_program *prog)
अणु
	काष्ठा bpf_link *link;
	पूर्णांक net_fd;

	net_fd = खोलो("/proc/self/ns/net", O_RDONLY);
	अगर (CHECK(net_fd < 0, "open", "failed\n")) अणु
		log_err("failed to open /proc/self/ns/net");
		वापस शून्य;
	पूर्ण

	link = bpf_program__attach_netns(prog, net_fd);
	अगर (CHECK(IS_ERR(link), "bpf_program__attach_netns", "failed\n")) अणु
		त्रुटि_सं = -PTR_ERR(link);
		log_err("failed to attach program '%s' to netns",
			bpf_program__name(prog));
		link = शून्य;
	पूर्ण

	बंद(net_fd);
	वापस link;
पूर्ण

अटल पूर्णांक update_lookup_map(काष्ठा bpf_map *map, पूर्णांक index, पूर्णांक sock_fd)
अणु
	पूर्णांक err, map_fd;
	uपूर्णांक64_t value;

	map_fd = bpf_map__fd(map);
	अगर (CHECK(map_fd < 0, "bpf_map__fd", "failed\n")) अणु
		त्रुटि_सं = -map_fd;
		log_err("failed to get map FD");
		वापस -1;
	पूर्ण

	value = (uपूर्णांक64_t)sock_fd;
	err = bpf_map_update_elem(map_fd, &index, &value, BPF_NOEXIST);
	अगर (CHECK(err, "bpf_map_update_elem", "failed\n")) अणु
		log_err("failed to update redir_map @ %d", index);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम query_lookup_prog(काष्ठा test_sk_lookup *skel)
अणु
	काष्ठा bpf_link *link[3] = अणुपूर्ण;
	काष्ठा bpf_link_info info;
	__u32 attach_flags = 0;
	__u32 prog_ids[3] = अणुपूर्ण;
	__u32 prog_cnt = 3;
	__u32 prog_id;
	पूर्णांक net_fd;
	पूर्णांक err;

	net_fd = खोलो("/proc/self/ns/net", O_RDONLY);
	अगर (CHECK(net_fd < 0, "open", "failed\n")) अणु
		log_err("failed to open /proc/self/ns/net");
		वापस;
	पूर्ण

	link[0] = attach_lookup_prog(skel->progs.lookup_pass);
	अगर (!link[0])
		जाओ बंद;
	link[1] = attach_lookup_prog(skel->progs.lookup_pass);
	अगर (!link[1])
		जाओ detach;
	link[2] = attach_lookup_prog(skel->progs.lookup_drop);
	अगर (!link[2])
		जाओ detach;

	err = bpf_prog_query(net_fd, BPF_SK_LOOKUP, 0 /* query flags */,
			     &attach_flags, prog_ids, &prog_cnt);
	अगर (CHECK(err, "bpf_prog_query", "failed\n")) अणु
		log_err("failed to query lookup prog");
		जाओ detach;
	पूर्ण

	त्रुटि_सं = 0;
	अगर (CHECK(attach_flags != 0, "bpf_prog_query",
		  "wrong attach_flags on query: %u", attach_flags))
		जाओ detach;
	अगर (CHECK(prog_cnt != 3, "bpf_prog_query",
		  "wrong program count on query: %u", prog_cnt))
		जाओ detach;
	prog_id = link_info_prog_id(link[0], &info);
	CHECK(prog_ids[0] != prog_id, "bpf_prog_query",
	      "invalid program #0 id on query: %u != %u\n",
	      prog_ids[0], prog_id);
	CHECK(info.netns.netns_ino == 0, "netns_ino",
	      "unexpected netns_ino: %u\n", info.netns.netns_ino);
	prog_id = link_info_prog_id(link[1], &info);
	CHECK(prog_ids[1] != prog_id, "bpf_prog_query",
	      "invalid program #1 id on query: %u != %u\n",
	      prog_ids[1], prog_id);
	CHECK(info.netns.netns_ino == 0, "netns_ino",
	      "unexpected netns_ino: %u\n", info.netns.netns_ino);
	prog_id = link_info_prog_id(link[2], &info);
	CHECK(prog_ids[2] != prog_id, "bpf_prog_query",
	      "invalid program #2 id on query: %u != %u\n",
	      prog_ids[2], prog_id);
	CHECK(info.netns.netns_ino == 0, "netns_ino",
	      "unexpected netns_ino: %u\n", info.netns.netns_ino);

	err = bpf_link__detach(link[0]);
	अगर (CHECK(err, "link_detach", "failed %d\n", err))
		जाओ detach;

	/* prog id is still there, but netns_ino is zeroed out */
	prog_id = link_info_prog_id(link[0], &info);
	CHECK(prog_ids[0] != prog_id, "bpf_prog_query",
	      "invalid program #0 id on query: %u != %u\n",
	      prog_ids[0], prog_id);
	CHECK(info.netns.netns_ino != 0, "netns_ino",
	      "unexpected netns_ino: %u\n", info.netns.netns_ino);

detach:
	अगर (link[2])
		bpf_link__destroy(link[2]);
	अगर (link[1])
		bpf_link__destroy(link[1]);
	अगर (link[0])
		bpf_link__destroy(link[0]);
बंद:
	बंद(net_fd);
पूर्ण

अटल व्योम run_lookup_prog(स्थिर काष्ठा test *t)
अणु
	पूर्णांक server_fds[MAX_SERVERS] = अणु -1 पूर्ण;
	पूर्णांक client_fd, reuse_conn_fd = -1;
	काष्ठा bpf_link *lookup_link;
	पूर्णांक i, err;

	lookup_link = attach_lookup_prog(t->lookup_prog);
	अगर (!lookup_link)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(server_fds); i++) अणु
		server_fds[i] = make_server(t->sotype, t->listen_at.ip,
					    t->listen_at.port,
					    t->reuseport_prog);
		अगर (server_fds[i] < 0)
			जाओ बंद;

		err = update_lookup_map(t->sock_map, i, server_fds[i]);
		अगर (err)
			जाओ बंद;

		/* want just one server क्रम non-reuseport test */
		अगर (!t->reuseport_prog)
			अवरोध;
	पूर्ण

	/* Regular UDP socket lookup with reuseport behaves
	 * dअगरferently when reuseport group contains connected
	 * sockets. Check that adding a connected UDP socket to the
	 * reuseport group करोes not affect how reuseport works with
	 * BPF socket lookup.
	 */
	अगर (t->reuseport_has_conns) अणु
		काष्ठा sockaddr_storage addr = अणुपूर्ण;
		socklen_t len = माप(addr);

		/* Add an extra socket to reuseport group */
		reuse_conn_fd = make_server(t->sotype, t->listen_at.ip,
					    t->listen_at.port,
					    t->reuseport_prog);
		अगर (reuse_conn_fd < 0)
			जाओ बंद;

		/* Connect the extra socket to itself */
		err = माला_लोockname(reuse_conn_fd, (व्योम *)&addr, &len);
		अगर (CHECK(err, "getsockname", "errno %d\n", त्रुटि_सं))
			जाओ बंद;
		err = connect(reuse_conn_fd, (व्योम *)&addr, len);
		अगर (CHECK(err, "connect", "errno %d\n", त्रुटि_सं))
			जाओ बंद;
	पूर्ण

	client_fd = make_client(t->sotype, t->connect_to.ip, t->connect_to.port);
	अगर (client_fd < 0)
		जाओ बंद;

	अगर (t->sotype == SOCK_STREAM)
		tcp_echo_test(client_fd, server_fds[t->accept_on]);
	अन्यथा
		udp_echo_test(client_fd, server_fds[t->accept_on]);

	बंद(client_fd);
बंद:
	अगर (reuse_conn_fd != -1)
		बंद(reuse_conn_fd);
	क्रम (i = 0; i < ARRAY_SIZE(server_fds); i++) अणु
		अगर (server_fds[i] != -1)
			बंद(server_fds[i]);
	पूर्ण
	bpf_link__destroy(lookup_link);
पूर्ण

अटल व्योम test_redirect_lookup(काष्ठा test_sk_lookup *skel)
अणु
	स्थिर काष्ठा test tests[] = अणु
		अणु
			.desc		= "TCP IPv4 redir port",
			.lookup_prog	= skel->progs.redir_port,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_STREAM,
			.connect_to	= अणु EXT_IP4, EXT_PORT पूर्ण,
			.listen_at	= अणु EXT_IP4, INT_PORT पूर्ण,
		पूर्ण,
		अणु
			.desc		= "TCP IPv4 redir addr",
			.lookup_prog	= skel->progs.redir_ip4,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_STREAM,
			.connect_to	= अणु EXT_IP4, EXT_PORT पूर्ण,
			.listen_at	= अणु INT_IP4, EXT_PORT पूर्ण,
		पूर्ण,
		अणु
			.desc		= "TCP IPv4 redir with reuseport",
			.lookup_prog	= skel->progs.select_sock_a,
			.reuseport_prog	= skel->progs.select_sock_b,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_STREAM,
			.connect_to	= अणु EXT_IP4, EXT_PORT पूर्ण,
			.listen_at	= अणु INT_IP4, INT_PORT पूर्ण,
			.accept_on	= SERVER_B,
		पूर्ण,
		अणु
			.desc		= "TCP IPv4 redir skip reuseport",
			.lookup_prog	= skel->progs.select_sock_a_no_reuseport,
			.reuseport_prog	= skel->progs.select_sock_b,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_STREAM,
			.connect_to	= अणु EXT_IP4, EXT_PORT पूर्ण,
			.listen_at	= अणु INT_IP4, INT_PORT पूर्ण,
			.accept_on	= SERVER_A,
		पूर्ण,
		अणु
			.desc		= "TCP IPv6 redir port",
			.lookup_prog	= skel->progs.redir_port,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_STREAM,
			.connect_to	= अणु EXT_IP6, EXT_PORT पूर्ण,
			.listen_at	= अणु EXT_IP6, INT_PORT पूर्ण,
		पूर्ण,
		अणु
			.desc		= "TCP IPv6 redir addr",
			.lookup_prog	= skel->progs.redir_ip6,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_STREAM,
			.connect_to	= अणु EXT_IP6, EXT_PORT पूर्ण,
			.listen_at	= अणु INT_IP6, EXT_PORT पूर्ण,
		पूर्ण,
		अणु
			.desc		= "TCP IPv4->IPv6 redir port",
			.lookup_prog	= skel->progs.redir_port,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_STREAM,
			.connect_to	= अणु EXT_IP4, EXT_PORT पूर्ण,
			.listen_at	= अणु INT_IP4_V6, INT_PORT पूर्ण,
		पूर्ण,
		अणु
			.desc		= "TCP IPv6 redir with reuseport",
			.lookup_prog	= skel->progs.select_sock_a,
			.reuseport_prog	= skel->progs.select_sock_b,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_STREAM,
			.connect_to	= अणु EXT_IP6, EXT_PORT पूर्ण,
			.listen_at	= अणु INT_IP6, INT_PORT पूर्ण,
			.accept_on	= SERVER_B,
		पूर्ण,
		अणु
			.desc		= "TCP IPv6 redir skip reuseport",
			.lookup_prog	= skel->progs.select_sock_a_no_reuseport,
			.reuseport_prog	= skel->progs.select_sock_b,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_STREAM,
			.connect_to	= अणु EXT_IP6, EXT_PORT पूर्ण,
			.listen_at	= अणु INT_IP6, INT_PORT पूर्ण,
			.accept_on	= SERVER_A,
		पूर्ण,
		अणु
			.desc		= "UDP IPv4 redir port",
			.lookup_prog	= skel->progs.redir_port,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_DGRAM,
			.connect_to	= अणु EXT_IP4, EXT_PORT पूर्ण,
			.listen_at	= अणु EXT_IP4, INT_PORT पूर्ण,
		पूर्ण,
		अणु
			.desc		= "UDP IPv4 redir addr",
			.lookup_prog	= skel->progs.redir_ip4,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_DGRAM,
			.connect_to	= अणु EXT_IP4, EXT_PORT पूर्ण,
			.listen_at	= अणु INT_IP4, EXT_PORT पूर्ण,
		पूर्ण,
		अणु
			.desc		= "UDP IPv4 redir with reuseport",
			.lookup_prog	= skel->progs.select_sock_a,
			.reuseport_prog	= skel->progs.select_sock_b,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_DGRAM,
			.connect_to	= अणु EXT_IP4, EXT_PORT पूर्ण,
			.listen_at	= अणु INT_IP4, INT_PORT पूर्ण,
			.accept_on	= SERVER_B,
		पूर्ण,
		अणु
			.desc		= "UDP IPv4 redir and reuseport with conns",
			.lookup_prog	= skel->progs.select_sock_a,
			.reuseport_prog	= skel->progs.select_sock_b,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_DGRAM,
			.connect_to	= अणु EXT_IP4, EXT_PORT पूर्ण,
			.listen_at	= अणु INT_IP4, INT_PORT पूर्ण,
			.accept_on	= SERVER_B,
			.reuseport_has_conns = true,
		पूर्ण,
		अणु
			.desc		= "UDP IPv4 redir skip reuseport",
			.lookup_prog	= skel->progs.select_sock_a_no_reuseport,
			.reuseport_prog	= skel->progs.select_sock_b,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_DGRAM,
			.connect_to	= अणु EXT_IP4, EXT_PORT पूर्ण,
			.listen_at	= अणु INT_IP4, INT_PORT पूर्ण,
			.accept_on	= SERVER_A,
		पूर्ण,
		अणु
			.desc		= "UDP IPv6 redir port",
			.lookup_prog	= skel->progs.redir_port,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_DGRAM,
			.connect_to	= अणु EXT_IP6, EXT_PORT पूर्ण,
			.listen_at	= अणु EXT_IP6, INT_PORT पूर्ण,
		पूर्ण,
		अणु
			.desc		= "UDP IPv6 redir addr",
			.lookup_prog	= skel->progs.redir_ip6,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_DGRAM,
			.connect_to	= अणु EXT_IP6, EXT_PORT पूर्ण,
			.listen_at	= अणु INT_IP6, EXT_PORT पूर्ण,
		पूर्ण,
		अणु
			.desc		= "UDP IPv4->IPv6 redir port",
			.lookup_prog	= skel->progs.redir_port,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_DGRAM,
			.listen_at	= अणु INT_IP4_V6, INT_PORT पूर्ण,
			.connect_to	= अणु EXT_IP4, EXT_PORT पूर्ण,
		पूर्ण,
		अणु
			.desc		= "UDP IPv6 redir and reuseport",
			.lookup_prog	= skel->progs.select_sock_a,
			.reuseport_prog	= skel->progs.select_sock_b,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_DGRAM,
			.connect_to	= अणु EXT_IP6, EXT_PORT पूर्ण,
			.listen_at	= अणु INT_IP6, INT_PORT पूर्ण,
			.accept_on	= SERVER_B,
		पूर्ण,
		अणु
			.desc		= "UDP IPv6 redir and reuseport with conns",
			.lookup_prog	= skel->progs.select_sock_a,
			.reuseport_prog	= skel->progs.select_sock_b,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_DGRAM,
			.connect_to	= अणु EXT_IP6, EXT_PORT पूर्ण,
			.listen_at	= अणु INT_IP6, INT_PORT पूर्ण,
			.accept_on	= SERVER_B,
			.reuseport_has_conns = true,
		पूर्ण,
		अणु
			.desc		= "UDP IPv6 redir skip reuseport",
			.lookup_prog	= skel->progs.select_sock_a_no_reuseport,
			.reuseport_prog	= skel->progs.select_sock_b,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_DGRAM,
			.connect_to	= अणु EXT_IP6, EXT_PORT पूर्ण,
			.listen_at	= अणु INT_IP6, INT_PORT पूर्ण,
			.accept_on	= SERVER_A,
		पूर्ण,
	पूर्ण;
	स्थिर काष्ठा test *t;

	क्रम (t = tests; t < tests + ARRAY_SIZE(tests); t++) अणु
		अगर (test__start_subtest(t->desc))
			run_lookup_prog(t);
	पूर्ण
पूर्ण

अटल व्योम drop_on_lookup(स्थिर काष्ठा test *t)
अणु
	काष्ठा sockaddr_storage dst = अणुपूर्ण;
	पूर्णांक client_fd, server_fd, err;
	काष्ठा bpf_link *lookup_link;
	sमाप_प्रकार n;

	lookup_link = attach_lookup_prog(t->lookup_prog);
	अगर (!lookup_link)
		वापस;

	server_fd = make_server(t->sotype, t->listen_at.ip, t->listen_at.port,
				t->reuseport_prog);
	अगर (server_fd < 0)
		जाओ detach;

	client_fd = make_socket(t->sotype, t->connect_to.ip,
				t->connect_to.port, &dst);
	अगर (client_fd < 0)
		जाओ बंद_srv;

	err = connect(client_fd, (व्योम *)&dst, inetaddr_len(&dst));
	अगर (t->sotype == SOCK_DGRAM) अणु
		err = send_byte(client_fd);
		अगर (err)
			जाओ बंद_all;

		/* Read out asynchronous error */
		n = recv(client_fd, शून्य, 0, 0);
		err = n == -1;
	पूर्ण
	अगर (CHECK(!err || त्रुटि_सं != ECONNREFUSED, "connect",
		  "unexpected success or error\n"))
		log_err("expected ECONNREFUSED on connect");

बंद_all:
	बंद(client_fd);
बंद_srv:
	बंद(server_fd);
detach:
	bpf_link__destroy(lookup_link);
पूर्ण

अटल व्योम test_drop_on_lookup(काष्ठा test_sk_lookup *skel)
अणु
	स्थिर काष्ठा test tests[] = अणु
		अणु
			.desc		= "TCP IPv4 drop on lookup",
			.lookup_prog	= skel->progs.lookup_drop,
			.sotype		= SOCK_STREAM,
			.connect_to	= अणु EXT_IP4, EXT_PORT पूर्ण,
			.listen_at	= अणु EXT_IP4, EXT_PORT पूर्ण,
		पूर्ण,
		अणु
			.desc		= "TCP IPv6 drop on lookup",
			.lookup_prog	= skel->progs.lookup_drop,
			.sotype		= SOCK_STREAM,
			.connect_to	= अणु EXT_IP6, EXT_PORT पूर्ण,
			.listen_at	= अणु EXT_IP6, EXT_PORT पूर्ण,
		पूर्ण,
		अणु
			.desc		= "UDP IPv4 drop on lookup",
			.lookup_prog	= skel->progs.lookup_drop,
			.sotype		= SOCK_DGRAM,
			.connect_to	= अणु EXT_IP4, EXT_PORT पूर्ण,
			.listen_at	= अणु EXT_IP4, EXT_PORT पूर्ण,
		पूर्ण,
		अणु
			.desc		= "UDP IPv6 drop on lookup",
			.lookup_prog	= skel->progs.lookup_drop,
			.sotype		= SOCK_DGRAM,
			.connect_to	= अणु EXT_IP6, EXT_PORT पूर्ण,
			.listen_at	= अणु EXT_IP6, INT_PORT पूर्ण,
		पूर्ण,
	पूर्ण;
	स्थिर काष्ठा test *t;

	क्रम (t = tests; t < tests + ARRAY_SIZE(tests); t++) अणु
		अगर (test__start_subtest(t->desc))
			drop_on_lookup(t);
	पूर्ण
पूर्ण

अटल व्योम drop_on_reuseport(स्थिर काष्ठा test *t)
अणु
	काष्ठा sockaddr_storage dst = अणु 0 पूर्ण;
	पूर्णांक client, server1, server2, err;
	काष्ठा bpf_link *lookup_link;
	sमाप_प्रकार n;

	lookup_link = attach_lookup_prog(t->lookup_prog);
	अगर (!lookup_link)
		वापस;

	server1 = make_server(t->sotype, t->listen_at.ip, t->listen_at.port,
			      t->reuseport_prog);
	अगर (server1 < 0)
		जाओ detach;

	err = update_lookup_map(t->sock_map, SERVER_A, server1);
	अगर (err)
		जाओ detach;

	/* second server on destination address we should never reach */
	server2 = make_server(t->sotype, t->connect_to.ip, t->connect_to.port,
			      शून्य /* reuseport prog */);
	अगर (server2 < 0)
		जाओ बंद_srv1;

	client = make_socket(t->sotype, t->connect_to.ip,
			     t->connect_to.port, &dst);
	अगर (client < 0)
		जाओ बंद_srv2;

	err = connect(client, (व्योम *)&dst, inetaddr_len(&dst));
	अगर (t->sotype == SOCK_DGRAM) अणु
		err = send_byte(client);
		अगर (err)
			जाओ बंद_all;

		/* Read out asynchronous error */
		n = recv(client, शून्य, 0, 0);
		err = n == -1;
	पूर्ण
	अगर (CHECK(!err || त्रुटि_सं != ECONNREFUSED, "connect",
		  "unexpected success or error\n"))
		log_err("expected ECONNREFUSED on connect");

बंद_all:
	बंद(client);
बंद_srv2:
	बंद(server2);
बंद_srv1:
	बंद(server1);
detach:
	bpf_link__destroy(lookup_link);
पूर्ण

अटल व्योम test_drop_on_reuseport(काष्ठा test_sk_lookup *skel)
अणु
	स्थिर काष्ठा test tests[] = अणु
		अणु
			.desc		= "TCP IPv4 drop on reuseport",
			.lookup_prog	= skel->progs.select_sock_a,
			.reuseport_prog	= skel->progs.reuseport_drop,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_STREAM,
			.connect_to	= अणु EXT_IP4, EXT_PORT पूर्ण,
			.listen_at	= अणु INT_IP4, INT_PORT पूर्ण,
		पूर्ण,
		अणु
			.desc		= "TCP IPv6 drop on reuseport",
			.lookup_prog	= skel->progs.select_sock_a,
			.reuseport_prog	= skel->progs.reuseport_drop,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_STREAM,
			.connect_to	= अणु EXT_IP6, EXT_PORT पूर्ण,
			.listen_at	= अणु INT_IP6, INT_PORT पूर्ण,
		पूर्ण,
		अणु
			.desc		= "UDP IPv4 drop on reuseport",
			.lookup_prog	= skel->progs.select_sock_a,
			.reuseport_prog	= skel->progs.reuseport_drop,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_DGRAM,
			.connect_to	= अणु EXT_IP4, EXT_PORT पूर्ण,
			.listen_at	= अणु INT_IP4, INT_PORT पूर्ण,
		पूर्ण,
		अणु
			.desc		= "TCP IPv6 drop on reuseport",
			.lookup_prog	= skel->progs.select_sock_a,
			.reuseport_prog	= skel->progs.reuseport_drop,
			.sock_map	= skel->maps.redir_map,
			.sotype		= SOCK_STREAM,
			.connect_to	= अणु EXT_IP6, EXT_PORT पूर्ण,
			.listen_at	= अणु INT_IP6, INT_PORT पूर्ण,
		पूर्ण,
	पूर्ण;
	स्थिर काष्ठा test *t;

	क्रम (t = tests; t < tests + ARRAY_SIZE(tests); t++) अणु
		अगर (test__start_subtest(t->desc))
			drop_on_reuseport(t);
	पूर्ण
पूर्ण

अटल व्योम run_sk_assign(काष्ठा test_sk_lookup *skel,
			  काष्ठा bpf_program *lookup_prog,
			  स्थिर अक्षर *remote_ip, स्थिर अक्षर *local_ip)
अणु
	पूर्णांक server_fds[MAX_SERVERS] = अणु -1 पूर्ण;
	काष्ठा bpf_sk_lookup ctx;
	__u64 server_cookie;
	पूर्णांक i, err;

	DECLARE_LIBBPF_OPTS(bpf_test_run_opts, opts,
		.ctx_in = &ctx,
		.ctx_size_in = माप(ctx),
		.ctx_out = &ctx,
		.ctx_size_out = माप(ctx),
	);

	अगर (fill_sk_lookup_ctx(&ctx, local_ip, EXT_PORT, remote_ip, INT_PORT))
		वापस;

	ctx.protocol = IPPROTO_TCP;

	क्रम (i = 0; i < ARRAY_SIZE(server_fds); i++) अणु
		server_fds[i] = make_server(SOCK_STREAM, local_ip, 0, शून्य);
		अगर (server_fds[i] < 0)
			जाओ बंद_servers;

		err = update_lookup_map(skel->maps.redir_map, i,
					server_fds[i]);
		अगर (err)
			जाओ बंद_servers;
	पूर्ण

	server_cookie = socket_cookie(server_fds[SERVER_B]);
	अगर (!server_cookie)
		वापस;

	err = bpf_prog_test_run_opts(bpf_program__fd(lookup_prog), &opts);
	अगर (CHECK(err, "test_run", "failed with error %d\n", त्रुटि_सं))
		जाओ बंद_servers;

	अगर (CHECK(ctx.cookie == 0, "ctx.cookie", "no socket selected\n"))
		जाओ बंद_servers;

	CHECK(ctx.cookie != server_cookie, "ctx.cookie",
	      "selected sk %llu instead of %llu\n", ctx.cookie, server_cookie);

बंद_servers:
	क्रम (i = 0; i < ARRAY_SIZE(server_fds); i++) अणु
		अगर (server_fds[i] != -1)
			बंद(server_fds[i]);
	पूर्ण
पूर्ण

अटल व्योम run_sk_assign_v4(काष्ठा test_sk_lookup *skel,
			     काष्ठा bpf_program *lookup_prog)
अणु
	run_sk_assign(skel, lookup_prog, INT_IP4, EXT_IP4);
पूर्ण

अटल व्योम run_sk_assign_v6(काष्ठा test_sk_lookup *skel,
			     काष्ठा bpf_program *lookup_prog)
अणु
	run_sk_assign(skel, lookup_prog, INT_IP6, EXT_IP6);
पूर्ण

अटल व्योम run_sk_assign_connected(काष्ठा test_sk_lookup *skel,
				    पूर्णांक sotype)
अणु
	पूर्णांक err, client_fd, connected_fd, server_fd;
	काष्ठा bpf_link *lookup_link;

	server_fd = make_server(sotype, EXT_IP4, EXT_PORT, शून्य);
	अगर (server_fd < 0)
		वापस;

	connected_fd = make_client(sotype, EXT_IP4, EXT_PORT);
	अगर (connected_fd < 0)
		जाओ out_बंद_server;

	/* Put a connected socket in redirect map */
	err = update_lookup_map(skel->maps.redir_map, SERVER_A, connected_fd);
	अगर (err)
		जाओ out_बंद_connected;

	lookup_link = attach_lookup_prog(skel->progs.sk_assign_esocknosupport);
	अगर (!lookup_link)
		जाओ out_बंद_connected;

	/* Try to redirect TCP SYN / UDP packet to a connected socket */
	client_fd = make_client(sotype, EXT_IP4, EXT_PORT);
	अगर (client_fd < 0)
		जाओ out_unlink_prog;
	अगर (sotype == SOCK_DGRAM) अणु
		send_byte(client_fd);
		recv_byte(server_fd);
	पूर्ण

	बंद(client_fd);
out_unlink_prog:
	bpf_link__destroy(lookup_link);
out_बंद_connected:
	बंद(connected_fd);
out_बंद_server:
	बंद(server_fd);
पूर्ण

अटल व्योम test_sk_assign_helper(काष्ठा test_sk_lookup *skel)
अणु
	अगर (test__start_subtest("sk_assign returns EEXIST"))
		run_sk_assign_v4(skel, skel->progs.sk_assign_eexist);
	अगर (test__start_subtest("sk_assign honors F_REPLACE"))
		run_sk_assign_v4(skel, skel->progs.sk_assign_replace_flag);
	अगर (test__start_subtest("sk_assign accepts NULL socket"))
		run_sk_assign_v4(skel, skel->progs.sk_assign_null);
	अगर (test__start_subtest("access ctx->sk"))
		run_sk_assign_v4(skel, skel->progs.access_ctx_sk);
	अगर (test__start_subtest("narrow access to ctx v4"))
		run_sk_assign_v4(skel, skel->progs.ctx_narrow_access);
	अगर (test__start_subtest("narrow access to ctx v6"))
		run_sk_assign_v6(skel, skel->progs.ctx_narrow_access);
	अगर (test__start_subtest("sk_assign rejects TCP established"))
		run_sk_assign_connected(skel, SOCK_STREAM);
	अगर (test__start_subtest("sk_assign rejects UDP connected"))
		run_sk_assign_connected(skel, SOCK_DGRAM);
पूर्ण

काष्ठा test_multi_prog अणु
	स्थिर अक्षर *desc;
	काष्ठा bpf_program *prog1;
	काष्ठा bpf_program *prog2;
	काष्ठा bpf_map *redir_map;
	काष्ठा bpf_map *run_map;
	पूर्णांक expect_त्रुटि_सं;
	काष्ठा inet_addr listen_at;
पूर्ण;

अटल व्योम run_multi_prog_lookup(स्थिर काष्ठा test_multi_prog *t)
अणु
	काष्ठा sockaddr_storage dst = अणुपूर्ण;
	पूर्णांक map_fd, server_fd, client_fd;
	काष्ठा bpf_link *link1, *link2;
	पूर्णांक prog_idx, करोne, err;

	map_fd = bpf_map__fd(t->run_map);

	करोne = 0;
	prog_idx = PROG1;
	err = bpf_map_update_elem(map_fd, &prog_idx, &करोne, BPF_ANY);
	अगर (CHECK(err, "bpf_map_update_elem", "failed\n"))
		वापस;
	prog_idx = PROG2;
	err = bpf_map_update_elem(map_fd, &prog_idx, &करोne, BPF_ANY);
	अगर (CHECK(err, "bpf_map_update_elem", "failed\n"))
		वापस;

	link1 = attach_lookup_prog(t->prog1);
	अगर (!link1)
		वापस;
	link2 = attach_lookup_prog(t->prog2);
	अगर (!link2)
		जाओ out_unlink1;

	server_fd = make_server(SOCK_STREAM, t->listen_at.ip,
				t->listen_at.port, शून्य);
	अगर (server_fd < 0)
		जाओ out_unlink2;

	err = update_lookup_map(t->redir_map, SERVER_A, server_fd);
	अगर (err)
		जाओ out_बंद_server;

	client_fd = make_socket(SOCK_STREAM, EXT_IP4, EXT_PORT, &dst);
	अगर (client_fd < 0)
		जाओ out_बंद_server;

	err = connect(client_fd, (व्योम *)&dst, inetaddr_len(&dst));
	अगर (CHECK(err && !t->expect_त्रुटि_सं, "connect",
		  "unexpected error %d\n", त्रुटि_सं))
		जाओ out_बंद_client;
	अगर (CHECK(err && t->expect_त्रुटि_सं && त्रुटि_सं != t->expect_त्रुटि_सं,
		  "connect", "unexpected error %d\n", त्रुटि_सं))
		जाओ out_बंद_client;

	करोne = 0;
	prog_idx = PROG1;
	err = bpf_map_lookup_elem(map_fd, &prog_idx, &करोne);
	CHECK(err, "bpf_map_lookup_elem", "failed\n");
	CHECK(!करोne, "bpf_map_lookup_elem", "PROG1 !done\n");

	करोne = 0;
	prog_idx = PROG2;
	err = bpf_map_lookup_elem(map_fd, &prog_idx, &करोne);
	CHECK(err, "bpf_map_lookup_elem", "failed\n");
	CHECK(!करोne, "bpf_map_lookup_elem", "PROG2 !done\n");

out_बंद_client:
	बंद(client_fd);
out_बंद_server:
	बंद(server_fd);
out_unlink2:
	bpf_link__destroy(link2);
out_unlink1:
	bpf_link__destroy(link1);
पूर्ण

अटल व्योम test_multi_prog_lookup(काष्ठा test_sk_lookup *skel)
अणु
	काष्ठा test_multi_prog tests[] = अणु
		अणु
			.desc		= "multi prog - pass, pass",
			.prog1		= skel->progs.multi_prog_pass1,
			.prog2		= skel->progs.multi_prog_pass2,
			.listen_at	= अणु EXT_IP4, EXT_PORT पूर्ण,
		पूर्ण,
		अणु
			.desc		= "multi prog - drop, drop",
			.prog1		= skel->progs.multi_prog_drop1,
			.prog2		= skel->progs.multi_prog_drop2,
			.listen_at	= अणु EXT_IP4, EXT_PORT पूर्ण,
			.expect_त्रुटि_सं	= ECONNREFUSED,
		पूर्ण,
		अणु
			.desc		= "multi prog - pass, drop",
			.prog1		= skel->progs.multi_prog_pass1,
			.prog2		= skel->progs.multi_prog_drop2,
			.listen_at	= अणु EXT_IP4, EXT_PORT पूर्ण,
			.expect_त्रुटि_सं	= ECONNREFUSED,
		पूर्ण,
		अणु
			.desc		= "multi prog - drop, pass",
			.prog1		= skel->progs.multi_prog_drop1,
			.prog2		= skel->progs.multi_prog_pass2,
			.listen_at	= अणु EXT_IP4, EXT_PORT पूर्ण,
			.expect_त्रुटि_सं	= ECONNREFUSED,
		पूर्ण,
		अणु
			.desc		= "multi prog - pass, redir",
			.prog1		= skel->progs.multi_prog_pass1,
			.prog2		= skel->progs.multi_prog_redir2,
			.listen_at	= अणु INT_IP4, INT_PORT पूर्ण,
		पूर्ण,
		अणु
			.desc		= "multi prog - redir, pass",
			.prog1		= skel->progs.multi_prog_redir1,
			.prog2		= skel->progs.multi_prog_pass2,
			.listen_at	= अणु INT_IP4, INT_PORT पूर्ण,
		पूर्ण,
		अणु
			.desc		= "multi prog - drop, redir",
			.prog1		= skel->progs.multi_prog_drop1,
			.prog2		= skel->progs.multi_prog_redir2,
			.listen_at	= अणु INT_IP4, INT_PORT पूर्ण,
		पूर्ण,
		अणु
			.desc		= "multi prog - redir, drop",
			.prog1		= skel->progs.multi_prog_redir1,
			.prog2		= skel->progs.multi_prog_drop2,
			.listen_at	= अणु INT_IP4, INT_PORT पूर्ण,
		पूर्ण,
		अणु
			.desc		= "multi prog - redir, redir",
			.prog1		= skel->progs.multi_prog_redir1,
			.prog2		= skel->progs.multi_prog_redir2,
			.listen_at	= अणु INT_IP4, INT_PORT पूर्ण,
		पूर्ण,
	पूर्ण;
	काष्ठा test_multi_prog *t;

	क्रम (t = tests; t < tests + ARRAY_SIZE(tests); t++) अणु
		t->redir_map = skel->maps.redir_map;
		t->run_map = skel->maps.run_map;
		अगर (test__start_subtest(t->desc))
			run_multi_prog_lookup(t);
	पूर्ण
पूर्ण

अटल व्योम run_tests(काष्ठा test_sk_lookup *skel)
अणु
	अगर (test__start_subtest("query lookup prog"))
		query_lookup_prog(skel);
	test_redirect_lookup(skel);
	test_drop_on_lookup(skel);
	test_drop_on_reuseport(skel);
	test_sk_assign_helper(skel);
	test_multi_prog_lookup(skel);
पूर्ण

अटल पूर्णांक चयन_netns(व्योम)
अणु
	अटल स्थिर अक्षर * स्थिर setup_script[] = अणु
		"ip -6 addr add dev lo " EXT_IP6 "/128",
		"ip -6 addr add dev lo " INT_IP6 "/128",
		"ip link set dev lo up",
		शून्य,
	पूर्ण;
	स्थिर अक्षर * स्थिर *cmd;
	पूर्णांक err;

	err = unshare(CLONE_NEWNET);
	अगर (CHECK(err, "unshare", "failed\n")) अणु
		log_err("unshare(CLONE_NEWNET)");
		वापस -1;
	पूर्ण

	क्रम (cmd = setup_script; *cmd; cmd++) अणु
		err = प्रणाली(*cmd);
		अगर (CHECK(err, "system", "failed\n")) अणु
			log_err("system(%s)", *cmd);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम test_sk_lookup(व्योम)
अणु
	काष्ठा test_sk_lookup *skel;
	पूर्णांक err;

	err = चयन_netns();
	अगर (err)
		वापस;

	skel = test_sk_lookup__खोलो_and_load();
	अगर (CHECK(!skel, "skel open_and_load", "failed\n"))
		वापस;

	run_tests(skel);

	test_sk_lookup__destroy(skel);
पूर्ण
