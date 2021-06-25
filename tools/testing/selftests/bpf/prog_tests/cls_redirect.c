<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
// Copyright (c) 2020 Cloudflare

#घोषणा _GNU_SOURCE

#समावेश <arpa/inet.h>
#समावेश <माला.स>

#समावेश <linux/pkt_cls.h>
#समावेश <netinet/tcp.h>

#समावेश <test_progs.h>

#समावेश "progs/test_cls_redirect.h"
#समावेश "test_cls_redirect.skel.h"
#समावेश "test_cls_redirect_subprogs.skel.h"

#घोषणा ENCAP_IP INADDR_LOOPBACK
#घोषणा ENCAP_PORT (1234)

अटल पूर्णांक duration = 0;

काष्ठा addr_port अणु
	in_port_t port;
	जोड़ अणु
		काष्ठा in_addr in_addr;
		काष्ठा in6_addr in6_addr;
	पूर्ण;
पूर्ण;

काष्ठा tuple अणु
	पूर्णांक family;
	काष्ठा addr_port src;
	काष्ठा addr_port dst;
पूर्ण;

अटल पूर्णांक start_server(स्थिर काष्ठा sockaddr *addr, socklen_t len, पूर्णांक type)
अणु
	पूर्णांक fd = socket(addr->sa_family, type, 0);
	अगर (CHECK_FAIL(fd == -1))
		वापस -1;
	अगर (CHECK_FAIL(bind(fd, addr, len) == -1))
		जाओ err;
	अगर (type == SOCK_STREAM && CHECK_FAIL(listen(fd, 128) == -1))
		जाओ err;

	वापस fd;

err:
	बंद(fd);
	वापस -1;
पूर्ण

अटल पूर्णांक connect_to_server(स्थिर काष्ठा sockaddr *addr, socklen_t len,
			     पूर्णांक type)
अणु
	पूर्णांक fd = socket(addr->sa_family, type, 0);
	अगर (CHECK_FAIL(fd == -1))
		वापस -1;
	अगर (CHECK_FAIL(connect(fd, addr, len)))
		जाओ err;

	वापस fd;

err:
	बंद(fd);
	वापस -1;
पूर्ण

अटल bool fill_addr_port(स्थिर काष्ठा sockaddr *sa, काष्ठा addr_port *ap)
अणु
	स्थिर काष्ठा sockaddr_in6 *in6;
	स्थिर काष्ठा sockaddr_in *in;

	चयन (sa->sa_family) अणु
	हाल AF_INET:
		in = (स्थिर काष्ठा sockaddr_in *)sa;
		ap->in_addr = in->sin_addr;
		ap->port = in->sin_port;
		वापस true;

	हाल AF_INET6:
		in6 = (स्थिर काष्ठा sockaddr_in6 *)sa;
		ap->in6_addr = in6->sin6_addr;
		ap->port = in6->sin6_port;
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool set_up_conn(स्थिर काष्ठा sockaddr *addr, socklen_t len, पूर्णांक type,
			पूर्णांक *server, पूर्णांक *conn, काष्ठा tuple *tuple)
अणु
	काष्ठा sockaddr_storage ss;
	socklen_t slen = माप(ss);
	काष्ठा sockaddr *sa = (काष्ठा sockaddr *)&ss;

	*server = start_server(addr, len, type);
	अगर (*server < 0)
		वापस false;

	अगर (CHECK_FAIL(माला_लोockname(*server, sa, &slen)))
		जाओ बंद_server;

	*conn = connect_to_server(sa, slen, type);
	अगर (*conn < 0)
		जाओ बंद_server;

	/* We want to simulate packets arriving at conn, so we have to
	 * swap src and dst.
	 */
	slen = माप(ss);
	अगर (CHECK_FAIL(माला_लोockname(*conn, sa, &slen)))
		जाओ बंद_conn;

	अगर (CHECK_FAIL(!fill_addr_port(sa, &tuple->dst)))
		जाओ बंद_conn;

	slen = माप(ss);
	अगर (CHECK_FAIL(getpeername(*conn, sa, &slen)))
		जाओ बंद_conn;

	अगर (CHECK_FAIL(!fill_addr_port(sa, &tuple->src)))
		जाओ बंद_conn;

	tuple->family = ss.ss_family;
	वापस true;

बंद_conn:
	बंद(*conn);
	*conn = -1;
बंद_server:
	बंद(*server);
	*server = -1;
	वापस false;
पूर्ण

अटल socklen_t prepare_addr(काष्ठा sockaddr_storage *addr, पूर्णांक family)
अणु
	काष्ठा sockaddr_in *addr4;
	काष्ठा sockaddr_in6 *addr6;

	चयन (family) अणु
	हाल AF_INET:
		addr4 = (काष्ठा sockaddr_in *)addr;
		स_रखो(addr4, 0, माप(*addr4));
		addr4->sin_family = family;
		addr4->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		वापस माप(*addr4);
	हाल AF_INET6:
		addr6 = (काष्ठा sockaddr_in6 *)addr;
		स_रखो(addr6, 0, माप(*addr6));
		addr6->sin6_family = family;
		addr6->sin6_addr = in6addr_loopback;
		वापस माप(*addr6);
	शेष:
		ख_लिखो(मानक_त्रुटि, "Invalid family %d", family);
		वापस 0;
	पूर्ण
पूर्ण

अटल bool was_decapsulated(काष्ठा bpf_prog_test_run_attr *tattr)
अणु
	वापस tattr->data_size_out < tattr->data_size_in;
पूर्ण

क्रमागत type अणु
	UDP,
	TCP,
	__NR_KIND,
पूर्ण;

क्रमागत hops अणु
	NO_HOPS,
	ONE_HOP,
पूर्ण;

क्रमागत flags अणु
	NONE,
	SYN,
	ACK,
पूर्ण;

क्रमागत conn अणु
	KNOWN_CONN,
	UNKNOWN_CONN,
पूर्ण;

क्रमागत result अणु
	ACCEPT,
	FORWARD,
पूर्ण;

काष्ठा test_cfg अणु
	क्रमागत type type;
	क्रमागत result result;
	क्रमागत conn conn;
	क्रमागत hops hops;
	क्रमागत flags flags;
पूर्ण;

अटल पूर्णांक test_str(व्योम *buf, माप_प्रकार len, स्थिर काष्ठा test_cfg *test,
		    पूर्णांक family)
अणु
	स्थिर अक्षर *family_str, *type, *conn, *hops, *result, *flags;

	family_str = "IPv4";
	अगर (family == AF_INET6)
		family_str = "IPv6";

	type = "TCP";
	अगर (test->type == UDP)
		type = "UDP";

	conn = "known";
	अगर (test->conn == UNKNOWN_CONN)
		conn = "unknown";

	hops = "no hops";
	अगर (test->hops == ONE_HOP)
		hops = "one hop";

	result = "accept";
	अगर (test->result == FORWARD)
		result = "forward";

	flags = "none";
	अगर (test->flags == SYN)
		flags = "SYN";
	अन्यथा अगर (test->flags == ACK)
		flags = "ACK";

	वापस snम_लिखो(buf, len, "%s %s %s %s (%s, flags: %s)", family_str,
			type, result, conn, hops, flags);
पूर्ण

अटल काष्ठा test_cfg tests[] = अणु
	अणु TCP, ACCEPT, UNKNOWN_CONN, NO_HOPS, SYN पूर्ण,
	अणु TCP, ACCEPT, UNKNOWN_CONN, NO_HOPS, ACK पूर्ण,
	अणु TCP, FORWARD, UNKNOWN_CONN, ONE_HOP, ACK पूर्ण,
	अणु TCP, ACCEPT, KNOWN_CONN, ONE_HOP, ACK पूर्ण,
	अणु UDP, ACCEPT, UNKNOWN_CONN, NO_HOPS, NONE पूर्ण,
	अणु UDP, FORWARD, UNKNOWN_CONN, ONE_HOP, NONE पूर्ण,
	अणु UDP, ACCEPT, KNOWN_CONN, ONE_HOP, NONE पूर्ण,
पूर्ण;

अटल व्योम encap_init(encap_headers_t *encap, uपूर्णांक8_t hop_count, uपूर्णांक8_t proto)
अणु
	स्थिर uपूर्णांक8_t hlen =
		(माप(काष्ठा guehdr) / माप(uपूर्णांक32_t)) + hop_count;
	*encap = (encap_headers_t)अणु
		.eth = अणु .h_proto = htons(ETH_P_IP) पूर्ण,
		.ip = अणु
			.ihl = 5,
			.version = 4,
			.ttl = IPDEFTTL,
			.protocol = IPPROTO_UDP,
			.daddr = htonl(ENCAP_IP)
		पूर्ण,
		.udp = अणु
			.dest = htons(ENCAP_PORT),
		पूर्ण,
		.gue = अणु
			.hlen = hlen,
			.proto_ctype = proto
		पूर्ण,
		.unigue = अणु
			.hop_count = hop_count
		पूर्ण,
	पूर्ण;
पूर्ण

अटल माप_प्रकार build_input(स्थिर काष्ठा test_cfg *test, व्योम *स्थिर buf,
			  स्थिर काष्ठा tuple *tuple)
अणु
	in_port_t sport = tuple->src.port;
	encap_headers_t encap;
	काष्ठा iphdr ip;
	काष्ठा ipv6hdr ipv6;
	काष्ठा tcphdr tcp;
	काष्ठा udphdr udp;
	काष्ठा in_addr next_hop;
	uपूर्णांक8_t *p = buf;
	पूर्णांक proto;

	proto = IPPROTO_IPIP;
	अगर (tuple->family == AF_INET6)
		proto = IPPROTO_IPV6;

	encap_init(&encap, test->hops == ONE_HOP ? 1 : 0, proto);
	p = mempcpy(p, &encap, माप(encap));

	अगर (test->hops == ONE_HOP) अणु
		next_hop = (काष्ठा in_addr)अणु .s_addr = htonl(0x7f000002) पूर्ण;
		p = mempcpy(p, &next_hop, माप(next_hop));
	पूर्ण

	proto = IPPROTO_TCP;
	अगर (test->type == UDP)
		proto = IPPROTO_UDP;

	चयन (tuple->family) अणु
	हाल AF_INET:
		ip = (काष्ठा iphdr)अणु
			.ihl = 5,
			.version = 4,
			.ttl = IPDEFTTL,
			.protocol = proto,
			.saddr = tuple->src.in_addr.s_addr,
			.daddr = tuple->dst.in_addr.s_addr,
		पूर्ण;
		p = mempcpy(p, &ip, माप(ip));
		अवरोध;
	हाल AF_INET6:
		ipv6 = (काष्ठा ipv6hdr)अणु
			.version = 6,
			.hop_limit = IPDEFTTL,
			.nexthdr = proto,
			.saddr = tuple->src.in6_addr,
			.daddr = tuple->dst.in6_addr,
		पूर्ण;
		p = mempcpy(p, &ipv6, माप(ipv6));
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (test->conn == UNKNOWN_CONN)
		sport--;

	चयन (test->type) अणु
	हाल TCP:
		tcp = (काष्ठा tcphdr)अणु
			.source = sport,
			.dest = tuple->dst.port,
		पूर्ण;
		अगर (test->flags == SYN)
			tcp.syn = true;
		अगर (test->flags == ACK)
			tcp.ack = true;
		p = mempcpy(p, &tcp, माप(tcp));
		अवरोध;
	हाल UDP:
		udp = (काष्ठा udphdr)अणु
			.source = sport,
			.dest = tuple->dst.port,
		पूर्ण;
		p = mempcpy(p, &udp, माप(udp));
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस (व्योम *)p - buf;
पूर्ण

अटल व्योम बंद_fds(पूर्णांक *fds, पूर्णांक n)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; i++)
		अगर (fds[i] > 0)
			बंद(fds[i]);
पूर्ण

अटल व्योम test_cls_redirect_common(काष्ठा bpf_program *prog)
अणु
	काष्ठा bpf_prog_test_run_attr tattr = अणुपूर्ण;
	पूर्णांक families[] = अणु AF_INET, AF_INET6 पूर्ण;
	काष्ठा sockaddr_storage ss;
	काष्ठा sockaddr *addr;
	socklen_t slen;
	पूर्णांक i, j, err;
	पूर्णांक servers[__NR_KIND][ARRAY_SIZE(families)] = अणुपूर्ण;
	पूर्णांक conns[__NR_KIND][ARRAY_SIZE(families)] = अणुपूर्ण;
	काष्ठा tuple tuples[__NR_KIND][ARRAY_SIZE(families)];

	addr = (काष्ठा sockaddr *)&ss;
	क्रम (i = 0; i < ARRAY_SIZE(families); i++) अणु
		slen = prepare_addr(&ss, families[i]);
		अगर (CHECK_FAIL(!slen))
			जाओ cleanup;

		अगर (CHECK_FAIL(!set_up_conn(addr, slen, SOCK_DGRAM,
					    &servers[UDP][i], &conns[UDP][i],
					    &tuples[UDP][i])))
			जाओ cleanup;

		अगर (CHECK_FAIL(!set_up_conn(addr, slen, SOCK_STREAM,
					    &servers[TCP][i], &conns[TCP][i],
					    &tuples[TCP][i])))
			जाओ cleanup;
	पूर्ण

	tattr.prog_fd = bpf_program__fd(prog);
	क्रम (i = 0; i < ARRAY_SIZE(tests); i++) अणु
		काष्ठा test_cfg *test = &tests[i];

		क्रम (j = 0; j < ARRAY_SIZE(families); j++) अणु
			काष्ठा tuple *tuple = &tuples[test->type][j];
			अक्षर input[256];
			अक्षर पंचांगp[256];

			test_str(पंचांगp, माप(पंचांगp), test, tuple->family);
			अगर (!test__start_subtest(पंचांगp))
				जारी;

			tattr.data_out = पंचांगp;
			tattr.data_size_out = माप(पंचांगp);

			tattr.data_in = input;
			tattr.data_size_in = build_input(test, input, tuple);
			अगर (CHECK_FAIL(!tattr.data_size_in))
				जारी;

			err = bpf_prog_test_run_xattr(&tattr);
			अगर (CHECK_FAIL(err))
				जारी;

			अगर (tattr.retval != TC_ACT_REसूचीECT) अणु
				PRINT_FAIL("expected TC_ACT_REDIRECT, got %d\n",
					   tattr.retval);
				जारी;
			पूर्ण

			चयन (test->result) अणु
			हाल ACCEPT:
				अगर (CHECK_FAIL(!was_decapsulated(&tattr)))
					जारी;
				अवरोध;
			हाल FORWARD:
				अगर (CHECK_FAIL(was_decapsulated(&tattr)))
					जारी;
				अवरोध;
			शेष:
				PRINT_FAIL("unknown result %d\n", test->result);
				जारी;
			पूर्ण
		पूर्ण
	पूर्ण

cleanup:
	बंद_fds((पूर्णांक *)servers, माप(servers) / माप(servers[0][0]));
	बंद_fds((पूर्णांक *)conns, माप(conns) / माप(conns[0][0]));
पूर्ण

अटल व्योम test_cls_redirect_अंतरभूतd(व्योम)
अणु
	काष्ठा test_cls_redirect *skel;
	पूर्णांक err;

	skel = test_cls_redirect__खोलो();
	अगर (CHECK(!skel, "skel_open", "failed\n"))
		वापस;

	skel->rodata->ENCAPSULATION_IP = htonl(ENCAP_IP);
	skel->rodata->ENCAPSULATION_PORT = htons(ENCAP_PORT);

	err = test_cls_redirect__load(skel);
	अगर (CHECK(err, "skel_load", "failed: %d\n", err))
		जाओ cleanup;

	test_cls_redirect_common(skel->progs.cls_redirect);

cleanup:
	test_cls_redirect__destroy(skel);
पूर्ण

अटल व्योम test_cls_redirect_subprogs(व्योम)
अणु
	काष्ठा test_cls_redirect_subprogs *skel;
	पूर्णांक err;

	skel = test_cls_redirect_subprogs__खोलो();
	अगर (CHECK(!skel, "skel_open", "failed\n"))
		वापस;

	skel->rodata->ENCAPSULATION_IP = htonl(ENCAP_IP);
	skel->rodata->ENCAPSULATION_PORT = htons(ENCAP_PORT);

	err = test_cls_redirect_subprogs__load(skel);
	अगर (CHECK(err, "skel_load", "failed: %d\n", err))
		जाओ cleanup;

	test_cls_redirect_common(skel->progs.cls_redirect);

cleanup:
	test_cls_redirect_subprogs__destroy(skel);
पूर्ण

व्योम test_cls_redirect(व्योम)
अणु
	अगर (test__start_subtest("cls_redirect_inlined"))
		test_cls_redirect_अंतरभूतd();
	अगर (test__start_subtest("cls_redirect_subprogs"))
		test_cls_redirect_subprogs();
पूर्ण
