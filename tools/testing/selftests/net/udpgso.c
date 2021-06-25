<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा _GNU_SOURCE

#समावेश <मानकघोष.स>
#समावेश <arpa/inet.h>
#समावेश <error.h>
#समावेश <त्रुटिसं.स>
#समावेश <net/अगर.h>
#समावेश <linux/in.h>
#समावेश <linux/netlink.h>
#समावेश <linux/rtnetlink.h>
#समावेश <netinet/अगर_ether.h>
#समावेश <netinet/ip.h>
#समावेश <netinet/ip6.h>
#समावेश <netinet/udp.h>
#समावेश <stdbool.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/socket.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश <unistd.h>

#अगर_अघोषित ETH_MAX_MTU
#घोषणा ETH_MAX_MTU	0xFFFFU
#पूर्ण_अगर

#अगर_अघोषित UDP_SEGMENT
#घोषणा UDP_SEGMENT		103
#पूर्ण_अगर

#अगर_अघोषित UDP_MAX_SEGMENTS
#घोषणा UDP_MAX_SEGMENTS	(1 << 6UL)
#पूर्ण_अगर

#घोषणा CONST_MTU_TEST	1500

#घोषणा CONST_HDRLEN_V4		(माप(काष्ठा iphdr) + माप(काष्ठा udphdr))
#घोषणा CONST_HDRLEN_V6		(माप(काष्ठा ip6_hdr) + माप(काष्ठा udphdr))

#घोषणा CONST_MSS_V4		(CONST_MTU_TEST - CONST_HDRLEN_V4)
#घोषणा CONST_MSS_V6		(CONST_MTU_TEST - CONST_HDRLEN_V6)

#घोषणा CONST_MAX_SEGS_V4	(ETH_MAX_MTU / CONST_MSS_V4)
#घोषणा CONST_MAX_SEGS_V6	(ETH_MAX_MTU / CONST_MSS_V6)

अटल bool		cfg_करो_ipv4;
अटल bool		cfg_करो_ipv6;
अटल bool		cfg_करो_connected;
अटल bool		cfg_करो_connectionless;
अटल bool		cfg_करो_msgmore;
अटल bool		cfg_करो_setsockopt;
अटल पूर्णांक		cfg_specअगरic_test_id = -1;

अटल स्थिर अक्षर	cfg_अगरname[] = "lo";
अटल अचिन्हित लघु	cfg_port = 9000;

अटल अक्षर buf[ETH_MAX_MTU];

काष्ठा testहाल अणु
	पूर्णांक tlen;		/* send() buffer size, may exceed mss */
	bool tfail;		/* send() call is expected to fail */
	पूर्णांक gso_len;		/* mss after applying gso */
	पूर्णांक r_num_mss;		/* recv(): number of calls of full mss */
	पूर्णांक r_len_last;		/* recv(): size of last non-mss dgram, अगर any */
पूर्ण;

स्थिर काष्ठा in6_addr addr6 = IN6ADDR_LOOPBACK_INIT;
स्थिर काष्ठा in_addr addr4 = अणु .s_addr = __स्थिरant_htonl(INADDR_LOOPBACK + 2) पूर्ण;

काष्ठा testहाल testहालs_v4[] = अणु
	अणु
		/* no GSO: send a single byte */
		.tlen = 1,
		.r_len_last = 1,
	पूर्ण,
	अणु
		/* no GSO: send a single MSS */
		.tlen = CONST_MSS_V4,
		.r_num_mss = 1,
	पूर्ण,
	अणु
		/* no GSO: send a single MSS + 1B: fail */
		.tlen = CONST_MSS_V4 + 1,
		.tfail = true,
	पूर्ण,
	अणु
		/* send a single MSS: will fall back to no GSO */
		.tlen = CONST_MSS_V4,
		.gso_len = CONST_MSS_V4,
		.r_num_mss = 1,
	पूर्ण,
	अणु
		/* send a single MSS + 1B */
		.tlen = CONST_MSS_V4 + 1,
		.gso_len = CONST_MSS_V4,
		.r_num_mss = 1,
		.r_len_last = 1,
	पूर्ण,
	अणु
		/* send exactly 2 MSS */
		.tlen = CONST_MSS_V4 * 2,
		.gso_len = CONST_MSS_V4,
		.r_num_mss = 2,
	पूर्ण,
	अणु
		/* send 2 MSS + 1B */
		.tlen = (CONST_MSS_V4 * 2) + 1,
		.gso_len = CONST_MSS_V4,
		.r_num_mss = 2,
		.r_len_last = 1,
	पूर्ण,
	अणु
		/* send MAX segs */
		.tlen = (ETH_MAX_MTU / CONST_MSS_V4) * CONST_MSS_V4,
		.gso_len = CONST_MSS_V4,
		.r_num_mss = (ETH_MAX_MTU / CONST_MSS_V4),
	पूर्ण,

	अणु
		/* send MAX bytes */
		.tlen = ETH_MAX_MTU - CONST_HDRLEN_V4,
		.gso_len = CONST_MSS_V4,
		.r_num_mss = CONST_MAX_SEGS_V4,
		.r_len_last = ETH_MAX_MTU - CONST_HDRLEN_V4 -
			      (CONST_MAX_SEGS_V4 * CONST_MSS_V4),
	पूर्ण,
	अणु
		/* send MAX + 1: fail */
		.tlen = ETH_MAX_MTU - CONST_HDRLEN_V4 + 1,
		.gso_len = CONST_MSS_V4,
		.tfail = true,
	पूर्ण,
	अणु
		/* send a single 1B MSS: will fall back to no GSO */
		.tlen = 1,
		.gso_len = 1,
		.r_num_mss = 1,
	पूर्ण,
	अणु
		/* send 2 1B segments */
		.tlen = 2,
		.gso_len = 1,
		.r_num_mss = 2,
	पूर्ण,
	अणु
		/* send 2B + 2B + 1B segments */
		.tlen = 5,
		.gso_len = 2,
		.r_num_mss = 2,
		.r_len_last = 1,
	पूर्ण,
	अणु
		/* send max number of min sized segments */
		.tlen = UDP_MAX_SEGMENTS - CONST_HDRLEN_V4,
		.gso_len = 1,
		.r_num_mss = UDP_MAX_SEGMENTS - CONST_HDRLEN_V4,
	पूर्ण,
	अणु
		/* send max number + 1 of min sized segments: fail */
		.tlen = UDP_MAX_SEGMENTS - CONST_HDRLEN_V4 + 1,
		.gso_len = 1,
		.tfail = true,
	पूर्ण,
	अणु
		/* EOL */
	पूर्ण
पूर्ण;

#अगर_अघोषित IP6_MAX_MTU
#घोषणा IP6_MAX_MTU	(ETH_MAX_MTU + माप(काष्ठा ip6_hdr))
#पूर्ण_अगर

काष्ठा testहाल testहालs_v6[] = अणु
	अणु
		/* no GSO: send a single byte */
		.tlen = 1,
		.r_len_last = 1,
	पूर्ण,
	अणु
		/* no GSO: send a single MSS */
		.tlen = CONST_MSS_V6,
		.r_num_mss = 1,
	पूर्ण,
	अणु
		/* no GSO: send a single MSS + 1B: fail */
		.tlen = CONST_MSS_V6 + 1,
		.tfail = true,
	पूर्ण,
	अणु
		/* send a single MSS: will fall back to no GSO */
		.tlen = CONST_MSS_V6,
		.gso_len = CONST_MSS_V6,
		.r_num_mss = 1,
	पूर्ण,
	अणु
		/* send a single MSS + 1B */
		.tlen = CONST_MSS_V6 + 1,
		.gso_len = CONST_MSS_V6,
		.r_num_mss = 1,
		.r_len_last = 1,
	पूर्ण,
	अणु
		/* send exactly 2 MSS */
		.tlen = CONST_MSS_V6 * 2,
		.gso_len = CONST_MSS_V6,
		.r_num_mss = 2,
	पूर्ण,
	अणु
		/* send 2 MSS + 1B */
		.tlen = (CONST_MSS_V6 * 2) + 1,
		.gso_len = CONST_MSS_V6,
		.r_num_mss = 2,
		.r_len_last = 1,
	पूर्ण,
	अणु
		/* send MAX segs */
		.tlen = (IP6_MAX_MTU / CONST_MSS_V6) * CONST_MSS_V6,
		.gso_len = CONST_MSS_V6,
		.r_num_mss = (IP6_MAX_MTU / CONST_MSS_V6),
	पूर्ण,

	अणु
		/* send MAX bytes */
		.tlen = IP6_MAX_MTU - CONST_HDRLEN_V6,
		.gso_len = CONST_MSS_V6,
		.r_num_mss = CONST_MAX_SEGS_V6,
		.r_len_last = IP6_MAX_MTU - CONST_HDRLEN_V6 -
			      (CONST_MAX_SEGS_V6 * CONST_MSS_V6),
	पूर्ण,
	अणु
		/* send MAX + 1: fail */
		.tlen = IP6_MAX_MTU - CONST_HDRLEN_V6 + 1,
		.gso_len = CONST_MSS_V6,
		.tfail = true,
	पूर्ण,
	अणु
		/* send a single 1B MSS: will fall back to no GSO */
		.tlen = 1,
		.gso_len = 1,
		.r_num_mss = 1,
	पूर्ण,
	अणु
		/* send 2 1B segments */
		.tlen = 2,
		.gso_len = 1,
		.r_num_mss = 2,
	पूर्ण,
	अणु
		/* send 2B + 2B + 1B segments */
		.tlen = 5,
		.gso_len = 2,
		.r_num_mss = 2,
		.r_len_last = 1,
	पूर्ण,
	अणु
		/* send max number of min sized segments */
		.tlen = UDP_MAX_SEGMENTS - CONST_HDRLEN_V6,
		.gso_len = 1,
		.r_num_mss = UDP_MAX_SEGMENTS - CONST_HDRLEN_V6,
	पूर्ण,
	अणु
		/* send max number + 1 of min sized segments: fail */
		.tlen = UDP_MAX_SEGMENTS - CONST_HDRLEN_V6 + 1,
		.gso_len = 1,
		.tfail = true,
	पूर्ण,
	अणु
		/* EOL */
	पूर्ण
पूर्ण;

अटल अचिन्हित पूर्णांक get_device_mtu(पूर्णांक fd, स्थिर अक्षर *अगरname)
अणु
	काष्ठा अगरreq अगरr;

	स_रखो(&अगरr, 0, माप(अगरr));

	म_नकल(अगरr.अगरr_name, अगरname);

	अगर (ioctl(fd, SIOCGIFMTU, &अगरr))
		error(1, त्रुटि_सं, "ioctl get mtu");

	वापस अगरr.अगरr_mtu;
पूर्ण

अटल व्योम __set_device_mtu(पूर्णांक fd, स्थिर अक्षर *अगरname, अचिन्हित पूर्णांक mtu)
अणु
	काष्ठा अगरreq अगरr;

	स_रखो(&अगरr, 0, माप(अगरr));

	अगरr.अगरr_mtu = mtu;
	म_नकल(अगरr.अगरr_name, अगरname);

	अगर (ioctl(fd, SIOCSIFMTU, &अगरr))
		error(1, त्रुटि_सं, "ioctl set mtu");
पूर्ण

अटल व्योम set_device_mtu(पूर्णांक fd, पूर्णांक mtu)
अणु
	पूर्णांक val;

	val = get_device_mtu(fd, cfg_अगरname);
	ख_लिखो(मानक_त्रुटि, "device mtu (orig): %u\n", val);

	__set_device_mtu(fd, cfg_अगरname, mtu);
	val = get_device_mtu(fd, cfg_अगरname);
	अगर (val != mtu)
		error(1, 0, "unable to set device mtu to %u\n", val);

	ख_लिखो(मानक_त्रुटि, "device mtu (test): %u\n", val);
पूर्ण

अटल व्योम set_pmtu_discover(पूर्णांक fd, bool is_ipv4)
अणु
	पूर्णांक level, name, val;

	अगर (is_ipv4) अणु
		level	= SOL_IP;
		name	= IP_MTU_DISCOVER;
		val	= IP_PMTUDISC_DO;
	पूर्ण अन्यथा अणु
		level	= SOL_IPV6;
		name	= IPV6_MTU_DISCOVER;
		val	= IPV6_PMTUDISC_DO;
	पूर्ण

	अगर (setsockopt(fd, level, name, &val, माप(val)))
		error(1, त्रुटि_सं, "setsockopt path mtu");
पूर्ण

अटल अचिन्हित पूर्णांक get_path_mtu(पूर्णांक fd, bool is_ipv4)
अणु
	socklen_t vallen;
	अचिन्हित पूर्णांक mtu;
	पूर्णांक ret;

	vallen = माप(mtu);
	अगर (is_ipv4)
		ret = माला_लोockopt(fd, SOL_IP, IP_MTU, &mtu, &vallen);
	अन्यथा
		ret = माला_लोockopt(fd, SOL_IPV6, IPV6_MTU, &mtu, &vallen);

	अगर (ret)
		error(1, त्रुटि_सं, "getsockopt mtu");


	ख_लिखो(मानक_त्रुटि, "path mtu (read):  %u\n", mtu);
	वापस mtu;
पूर्ण

/* very wordy version of प्रणाली("ip route add dev lo mtu 1500 127.0.0.3/32") */
अटल व्योम set_route_mtu(पूर्णांक mtu, bool is_ipv4)
अणु
	काष्ठा sockaddr_nl nladdr = अणु .nl_family = AF_NETLINK पूर्ण;
	काष्ठा nlmsghdr *nh;
	काष्ठा rtattr *rta;
	काष्ठा rपंचांगsg *rt;
	अक्षर data[NLMSG_ALIGN(माप(*nh)) +
		  NLMSG_ALIGN(माप(*rt)) +
		  NLMSG_ALIGN(RTA_LENGTH(माप(addr6))) +
		  NLMSG_ALIGN(RTA_LENGTH(माप(पूर्णांक))) +
		  NLMSG_ALIGN(RTA_LENGTH(0) + RTA_LENGTH(माप(पूर्णांक)))];
	पूर्णांक fd, ret, alen, off = 0;

	alen = is_ipv4 ? माप(addr4) : माप(addr6);

	fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
	अगर (fd == -1)
		error(1, त्रुटि_सं, "socket netlink");

	स_रखो(data, 0, माप(data));

	nh = (व्योम *)data;
	nh->nlmsg_type = RTM_NEWROUTE;
	nh->nlmsg_flags = NLM_F_REQUEST | NLM_F_CREATE;
	off += NLMSG_ALIGN(माप(*nh));

	rt = (व्योम *)(data + off);
	rt->rपंचांग_family = is_ipv4 ? AF_INET : AF_INET6;
	rt->rपंचांग_table = RT_TABLE_MAIN;
	rt->rपंचांग_dst_len = alen << 3;
	rt->rपंचांग_protocol = RTPROT_BOOT;
	rt->rपंचांग_scope = RT_SCOPE_UNIVERSE;
	rt->rपंचांग_type = RTN_UNICAST;
	off += NLMSG_ALIGN(माप(*rt));

	rta = (व्योम *)(data + off);
	rta->rta_type = RTA_DST;
	rta->rta_len = RTA_LENGTH(alen);
	अगर (is_ipv4)
		स_नकल(RTA_DATA(rta), &addr4, alen);
	अन्यथा
		स_नकल(RTA_DATA(rta), &addr6, alen);
	off += NLMSG_ALIGN(rta->rta_len);

	rta = (व्योम *)(data + off);
	rta->rta_type = RTA_OIF;
	rta->rta_len = RTA_LENGTH(माप(पूर्णांक));
	*((पूर्णांक *)(RTA_DATA(rta))) = 1; //अगर_nametoindex("lo");
	off += NLMSG_ALIGN(rta->rta_len);

	/* MTU is a subtype in a metrics type */
	rta = (व्योम *)(data + off);
	rta->rta_type = RTA_METRICS;
	rta->rta_len = RTA_LENGTH(0) + RTA_LENGTH(माप(पूर्णांक));
	off += NLMSG_ALIGN(rta->rta_len);

	/* now fill MTU subtype. Note that it fits within above rta_len */
	rta = (व्योम *)(((अक्षर *) rta) + RTA_LENGTH(0));
	rta->rta_type = RTAX_MTU;
	rta->rta_len = RTA_LENGTH(माप(पूर्णांक));
	*((पूर्णांक *)(RTA_DATA(rta))) = mtu;

	nh->nlmsg_len = off;

	ret = sendto(fd, data, off, 0, (व्योम *)&nladdr, माप(nladdr));
	अगर (ret != off)
		error(1, त्रुटि_सं, "send netlink: %uB != %uB\n", ret, off);

	अगर (बंद(fd))
		error(1, त्रुटि_सं, "close netlink");

	ख_लिखो(मानक_त्रुटि, "route mtu (test): %u\n", mtu);
पूर्ण

अटल bool __send_one(पूर्णांक fd, काष्ठा msghdr *msg, पूर्णांक flags)
अणु
	पूर्णांक ret;

	ret = sendmsg(fd, msg, flags);
	अगर (ret == -1 &&
	    (त्रुटि_सं == EMSGSIZE || त्रुटि_सं == ENOMEM || त्रुटि_सं == EINVAL))
		वापस false;
	अगर (ret == -1)
		error(1, त्रुटि_सं, "sendmsg");
	अगर (ret != msg->msg_iov->iov_len)
		error(1, 0, "sendto: %d != %llu", ret,
			(अचिन्हित दीर्घ दीर्घ)msg->msg_iov->iov_len);
	अगर (msg->msg_flags)
		error(1, 0, "sendmsg: return flags 0x%x\n", msg->msg_flags);

	वापस true;
पूर्ण

अटल bool send_one(पूर्णांक fd, पूर्णांक len, पूर्णांक gso_len,
		     काष्ठा sockaddr *addr, socklen_t alen)
अणु
	अक्षर control[CMSG_SPACE(माप(uपूर्णांक16_t))] = अणु0पूर्ण;
	काष्ठा msghdr msg = अणु0पूर्ण;
	काष्ठा iovec iov = अणु0पूर्ण;
	काष्ठा cmsghdr *cm;

	iov.iov_base = buf;
	iov.iov_len = len;

	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;

	msg.msg_name = addr;
	msg.msg_namelen = alen;

	अगर (gso_len && !cfg_करो_setsockopt) अणु
		msg.msg_control = control;
		msg.msg_controllen = माप(control);

		cm = CMSG_FIRSTHDR(&msg);
		cm->cmsg_level = SOL_UDP;
		cm->cmsg_type = UDP_SEGMENT;
		cm->cmsg_len = CMSG_LEN(माप(uपूर्णांक16_t));
		*((uपूर्णांक16_t *) CMSG_DATA(cm)) = gso_len;
	पूर्ण

	/* If MSG_MORE, send 1 byte followed by reमुख्यder */
	अगर (cfg_करो_msgmore && len > 1) अणु
		iov.iov_len = 1;
		अगर (!__send_one(fd, &msg, MSG_MORE))
			error(1, 0, "send 1B failed");

		iov.iov_base++;
		iov.iov_len = len - 1;
	पूर्ण

	वापस __send_one(fd, &msg, 0);
पूर्ण

अटल पूर्णांक recv_one(पूर्णांक fd, पूर्णांक flags)
अणु
	पूर्णांक ret;

	ret = recv(fd, buf, माप(buf), flags);
	अगर (ret == -1 && त्रुटि_सं == EAGAIN && (flags & MSG_DONTWAIT))
		वापस 0;
	अगर (ret == -1)
		error(1, त्रुटि_सं, "recv");

	वापस ret;
पूर्ण

अटल व्योम run_one(काष्ठा testहाल *test, पूर्णांक fdt, पूर्णांक fdr,
		    काष्ठा sockaddr *addr, socklen_t alen)
अणु
	पूर्णांक i, ret, val, mss;
	bool sent;

	ख_लिखो(मानक_त्रुटि, "ipv%d tx:%d gso:%d %s\n",
			addr->sa_family == AF_INET ? 4 : 6,
			test->tlen, test->gso_len,
			test->tfail ? "(fail)" : "");

	val = test->gso_len;
	अगर (cfg_करो_setsockopt) अणु
		अगर (setsockopt(fdt, SOL_UDP, UDP_SEGMENT, &val, माप(val)))
			error(1, त्रुटि_सं, "setsockopt udp segment");
	पूर्ण

	sent = send_one(fdt, test->tlen, test->gso_len, addr, alen);
	अगर (sent && test->tfail)
		error(1, 0, "send succeeded while expecting failure");
	अगर (!sent && !test->tfail)
		error(1, 0, "send failed while expecting success");
	अगर (!sent)
		वापस;

	अगर (test->gso_len)
		mss = test->gso_len;
	अन्यथा
		mss = addr->sa_family == AF_INET ? CONST_MSS_V4 : CONST_MSS_V6;


	/* Recv all full MSS datagrams */
	क्रम (i = 0; i < test->r_num_mss; i++) अणु
		ret = recv_one(fdr, 0);
		अगर (ret != mss)
			error(1, 0, "recv.%d: %d != %d", i, ret, mss);
	पूर्ण

	/* Recv the non-full last datagram, अगर tlen was not a multiple of mss */
	अगर (test->r_len_last) अणु
		ret = recv_one(fdr, 0);
		अगर (ret != test->r_len_last)
			error(1, 0, "recv.%d: %d != %d (last)",
			      i, ret, test->r_len_last);
	पूर्ण

	/* Verअगरy received all data */
	ret = recv_one(fdr, MSG_DONTWAIT);
	अगर (ret)
		error(1, 0, "recv: unexpected datagram");
पूर्ण

अटल व्योम run_all(पूर्णांक fdt, पूर्णांक fdr, काष्ठा sockaddr *addr, socklen_t alen)
अणु
	काष्ठा testहाल *tests, *test;

	tests = addr->sa_family == AF_INET ? testहालs_v4 : testहालs_v6;

	क्रम (test = tests; test->tlen; test++) अणु
		/* अगर a specअगरic test is given, then skip all others */
		अगर (cfg_specअगरic_test_id == -1 ||
		    cfg_specअगरic_test_id == test - tests)
			run_one(test, fdt, fdr, addr, alen);
	पूर्ण
पूर्ण

अटल व्योम run_test(काष्ठा sockaddr *addr, socklen_t alen)
अणु
	काष्ठा समयval tv = अणु .tv_usec = 100 * 1000 पूर्ण;
	पूर्णांक fdr, fdt, val;

	fdr = socket(addr->sa_family, SOCK_DGRAM, 0);
	अगर (fdr == -1)
		error(1, त्रुटि_सं, "socket r");

	अगर (bind(fdr, addr, alen))
		error(1, त्रुटि_सं, "bind");

	/* Have tests fail quickly instead of hang */
	अगर (setsockopt(fdr, SOL_SOCKET, SO_RCVTIMEO, &tv, माप(tv)))
		error(1, त्रुटि_सं, "setsockopt rcv timeout");

	fdt = socket(addr->sa_family, SOCK_DGRAM, 0);
	अगर (fdt == -1)
		error(1, त्रुटि_सं, "socket t");

	/* Do not fragment these datagrams: only succeed अगर GSO works */
	set_pmtu_discover(fdt, addr->sa_family == AF_INET);

	अगर (cfg_करो_connectionless) अणु
		set_device_mtu(fdt, CONST_MTU_TEST);
		run_all(fdt, fdr, addr, alen);
	पूर्ण

	अगर (cfg_करो_connected) अणु
		set_device_mtu(fdt, CONST_MTU_TEST + 100);
		set_route_mtu(CONST_MTU_TEST, addr->sa_family == AF_INET);

		अगर (connect(fdt, addr, alen))
			error(1, त्रुटि_सं, "connect");

		val = get_path_mtu(fdt, addr->sa_family == AF_INET);
		अगर (val != CONST_MTU_TEST)
			error(1, 0, "bad path mtu %u\n", val);

		run_all(fdt, fdr, addr, 0 /* use connected addr */);
	पूर्ण

	अगर (बंद(fdt))
		error(1, त्रुटि_सं, "close t");
	अगर (बंद(fdr))
		error(1, त्रुटि_सं, "close r");
पूर्ण

अटल व्योम run_test_v4(व्योम)
अणु
	काष्ठा sockaddr_in addr = अणु0पूर्ण;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(cfg_port);
	addr.sin_addr = addr4;

	run_test((व्योम *)&addr, माप(addr));
पूर्ण

अटल व्योम run_test_v6(व्योम)
अणु
	काष्ठा sockaddr_in6 addr = अणु0पूर्ण;

	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(cfg_port);
	addr.sin6_addr = addr6;

	run_test((व्योम *)&addr, माप(addr));
पूर्ण

अटल व्योम parse_opts(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक c;

	जबतक ((c = getopt(argc, argv, "46cCmst:")) != -1) अणु
		चयन (c) अणु
		हाल '4':
			cfg_करो_ipv4 = true;
			अवरोध;
		हाल '6':
			cfg_करो_ipv6 = true;
			अवरोध;
		हाल 'c':
			cfg_करो_connected = true;
			अवरोध;
		हाल 'C':
			cfg_करो_connectionless = true;
			अवरोध;
		हाल 'm':
			cfg_करो_msgmore = true;
			अवरोध;
		हाल 's':
			cfg_करो_setsockopt = true;
			अवरोध;
		हाल 't':
			cfg_specअगरic_test_id = म_से_अदीर्घ(optarg, शून्य, 0);
			अवरोध;
		शेष:
			error(1, 0, "%s: parse error", argv[0]);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	parse_opts(argc, argv);

	अगर (cfg_करो_ipv4)
		run_test_v4();
	अगर (cfg_करो_ipv6)
		run_test_v6();

	ख_लिखो(मानक_त्रुटि, "OK\n");
	वापस 0;
पूर्ण
