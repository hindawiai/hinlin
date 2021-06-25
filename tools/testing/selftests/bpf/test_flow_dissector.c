<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Inject packets with all sorts of encapsulation पूर्णांकo the kernel.
 *
 * IPv4/IPv6	outer layer 3
 * GRE/GUE/BARE outer layer 4, where bare is IPIP/SIT/IPv4-in-IPv6/..
 * IPv4/IPv6    inner layer 3
 */

#घोषणा _GNU_SOURCE

#समावेश <मानकघोष.स>
#समावेश <arpa/inet.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <error.h>
#समावेश <त्रुटिसं.स>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/ipv6.h>
#समावेश <netinet/ip.h>
#समावेश <netinet/in.h>
#समावेश <netinet/udp.h>
#समावेश <poll.h>
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

#घोषणा CFG_PORT_INNER	8000

/* Add some protocol definitions that करो not exist in userspace */

काष्ठा grehdr अणु
	uपूर्णांक16_t unused;
	uपूर्णांक16_t protocol;
पूर्ण __attribute__((packed));

काष्ठा guehdr अणु
	जोड़ अणु
		काष्ठा अणु
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
			__u8	hlen:5,
				control:1,
				version:2;
#या_अगर defined (__BIG_ENDIAN_BITFIELD)
			__u8	version:2,
				control:1,
				hlen:5;
#अन्यथा
#त्रुटि  "Please fix <asm/byteorder.h>"
#पूर्ण_अगर
			__u8	proto_ctype;
			__be16	flags;
		पूर्ण;
		__be32	word;
	पूर्ण;
पूर्ण;

अटल uपूर्णांक8_t	cfg_dsfield_inner;
अटल uपूर्णांक8_t	cfg_dsfield_outer;
अटल uपूर्णांक8_t	cfg_encap_proto;
अटल bool	cfg_expect_failure = false;
अटल पूर्णांक	cfg_l3_extra = AF_UNSPEC;	/* optional SIT prefix */
अटल पूर्णांक	cfg_l3_inner = AF_UNSPEC;
अटल पूर्णांक	cfg_l3_outer = AF_UNSPEC;
अटल पूर्णांक	cfg_num_pkt = 10;
अटल पूर्णांक	cfg_num_secs = 0;
अटल अक्षर	cfg_payload_अक्षर = 'a';
अटल पूर्णांक	cfg_payload_len = 100;
अटल पूर्णांक	cfg_port_gue = 6080;
अटल bool	cfg_only_rx;
अटल bool	cfg_only_tx;
अटल पूर्णांक	cfg_src_port = 9;

अटल अक्षर	buf[ETH_DATA_LEN];

#घोषणा INIT_ADDR4(name, addr4, port)				\
	अटल काष्ठा sockaddr_in name = अणु			\
		.sin_family = AF_INET,				\
		.sin_port = __स्थिरant_htons(port),		\
		.sin_addr.s_addr = __स्थिरant_htonl(addr4),	\
	पूर्ण;

#घोषणा INIT_ADDR6(name, addr6, port)				\
	अटल काष्ठा sockaddr_in6 name = अणु			\
		.sin6_family = AF_INET6,			\
		.sin6_port = __स्थिरant_htons(port),		\
		.sin6_addr = addr6,				\
	पूर्ण;

INIT_ADDR4(in_daddr4, INADDR_LOOPBACK, CFG_PORT_INNER)
INIT_ADDR4(in_saddr4, INADDR_LOOPBACK + 2, 0)
INIT_ADDR4(out_daddr4, INADDR_LOOPBACK, 0)
INIT_ADDR4(out_saddr4, INADDR_LOOPBACK + 1, 0)
INIT_ADDR4(extra_daddr4, INADDR_LOOPBACK, 0)
INIT_ADDR4(extra_saddr4, INADDR_LOOPBACK + 1, 0)

INIT_ADDR6(in_daddr6, IN6ADDR_LOOPBACK_INIT, CFG_PORT_INNER)
INIT_ADDR6(in_saddr6, IN6ADDR_LOOPBACK_INIT, 0)
INIT_ADDR6(out_daddr6, IN6ADDR_LOOPBACK_INIT, 0)
INIT_ADDR6(out_saddr6, IN6ADDR_LOOPBACK_INIT, 0)
INIT_ADDR6(extra_daddr6, IN6ADDR_LOOPBACK_INIT, 0)
INIT_ADDR6(extra_saddr6, IN6ADDR_LOOPBACK_INIT, 0)

अटल अचिन्हित दीर्घ util_समय_लो(व्योम)
अणु
	काष्ठा समयval tv;

	समय_लोofday(&tv, शून्य);
	वापस (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
पूर्ण

अटल व्योम util_prपूर्णांकaddr(स्थिर अक्षर *msg, काष्ठा sockaddr *addr)
अणु
	अचिन्हित दीर्घ off = 0;
	अक्षर nbuf[INET6_ADDRSTRLEN];

	चयन (addr->sa_family) अणु
	हाल PF_INET:
		off = __builtin_दुरत्व(काष्ठा sockaddr_in, sin_addr);
		अवरोध;
	हाल PF_INET6:
		off = __builtin_दुरत्व(काष्ठा sockaddr_in6, sin6_addr);
		अवरोध;
	शेष:
		error(1, 0, "printaddr: unsupported family %u\n",
		      addr->sa_family);
	पूर्ण

	अगर (!inet_ntop(addr->sa_family, ((व्योम *) addr) + off, nbuf,
		       माप(nbuf)))
		error(1, त्रुटि_सं, "inet_ntop");

	ख_लिखो(मानक_त्रुटि, "%s: %s\n", msg, nbuf);
पूर्ण

अटल अचिन्हित दीर्घ add_csum_hword(स्थिर uपूर्णांक16_t *start, पूर्णांक num_u16)
अणु
	अचिन्हित दीर्घ sum = 0;
	पूर्णांक i;

	क्रम (i = 0; i < num_u16; i++)
		sum += start[i];

	वापस sum;
पूर्ण

अटल uपूर्णांक16_t build_ip_csum(स्थिर uपूर्णांक16_t *start, पूर्णांक num_u16,
			      अचिन्हित दीर्घ sum)
अणु
	sum += add_csum_hword(start, num_u16);

	जबतक (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);

	वापस ~sum;
पूर्ण

अटल व्योम build_ipv4_header(व्योम *header, uपूर्णांक8_t proto,
			      uपूर्णांक32_t src, uपूर्णांक32_t dst,
			      पूर्णांक payload_len, uपूर्णांक8_t tos)
अणु
	काष्ठा iphdr *iph = header;

	iph->ihl = 5;
	iph->version = 4;
	iph->tos = tos;
	iph->ttl = 8;
	iph->tot_len = htons(माप(*iph) + payload_len);
	iph->id = htons(1337);
	iph->protocol = proto;
	iph->saddr = src;
	iph->daddr = dst;
	iph->check = build_ip_csum((व्योम *) iph, iph->ihl << 1, 0);
पूर्ण

अटल व्योम ipv6_set_dsfield(काष्ठा ipv6hdr *ip6h, uपूर्णांक8_t dsfield)
अणु
	uपूर्णांक16_t val, *ptr = (uपूर्णांक16_t *)ip6h;

	val = ntohs(*ptr);
	val &= 0xF00F;
	val |= ((uपूर्णांक16_t) dsfield) << 4;
	*ptr = htons(val);
पूर्ण

अटल व्योम build_ipv6_header(व्योम *header, uपूर्णांक8_t proto,
			      काष्ठा sockaddr_in6 *src,
			      काष्ठा sockaddr_in6 *dst,
			      पूर्णांक payload_len, uपूर्णांक8_t dsfield)
अणु
	काष्ठा ipv6hdr *ip6h = header;

	ip6h->version = 6;
	ip6h->payload_len = htons(payload_len);
	ip6h->nexthdr = proto;
	ip6h->hop_limit = 8;
	ipv6_set_dsfield(ip6h, dsfield);

	स_नकल(&ip6h->saddr, &src->sin6_addr, माप(ip6h->saddr));
	स_नकल(&ip6h->daddr, &dst->sin6_addr, माप(ip6h->daddr));
पूर्ण

अटल uपूर्णांक16_t build_udp_v4_csum(स्थिर काष्ठा iphdr *iph,
				  स्थिर काष्ठा udphdr *udph,
				  पूर्णांक num_words)
अणु
	अचिन्हित दीर्घ pseuकरो_sum;
	पूर्णांक num_u16 = माप(iph->saddr);	/* halfwords: twice byte len */

	pseuकरो_sum = add_csum_hword((व्योम *) &iph->saddr, num_u16);
	pseuकरो_sum += htons(IPPROTO_UDP);
	pseuकरो_sum += udph->len;
	वापस build_ip_csum((व्योम *) udph, num_words, pseuकरो_sum);
पूर्ण

अटल uपूर्णांक16_t build_udp_v6_csum(स्थिर काष्ठा ipv6hdr *ip6h,
				  स्थिर काष्ठा udphdr *udph,
				  पूर्णांक num_words)
अणु
	अचिन्हित दीर्घ pseuकरो_sum;
	पूर्णांक num_u16 = माप(ip6h->saddr);	/* halfwords: twice byte len */

	pseuकरो_sum = add_csum_hword((व्योम *) &ip6h->saddr, num_u16);
	pseuकरो_sum += htons(ip6h->nexthdr);
	pseuकरो_sum += ip6h->payload_len;
	वापस build_ip_csum((व्योम *) udph, num_words, pseuकरो_sum);
पूर्ण

अटल व्योम build_udp_header(व्योम *header, पूर्णांक payload_len,
			     uपूर्णांक16_t dport, पूर्णांक family)
अणु
	काष्ठा udphdr *udph = header;
	पूर्णांक len = माप(*udph) + payload_len;

	udph->source = htons(cfg_src_port);
	udph->dest = htons(dport);
	udph->len = htons(len);
	udph->check = 0;
	अगर (family == AF_INET)
		udph->check = build_udp_v4_csum(header - माप(काष्ठा iphdr),
						udph, len >> 1);
	अन्यथा
		udph->check = build_udp_v6_csum(header - माप(काष्ठा ipv6hdr),
						udph, len >> 1);
पूर्ण

अटल व्योम build_gue_header(व्योम *header, uपूर्णांक8_t proto)
अणु
	काष्ठा guehdr *gueh = header;

	gueh->proto_ctype = proto;
पूर्ण

अटल व्योम build_gre_header(व्योम *header, uपूर्णांक16_t proto)
अणु
	काष्ठा grehdr *greh = header;

	greh->protocol = htons(proto);
पूर्ण

अटल पूर्णांक l3_length(पूर्णांक family)
अणु
	अगर (family == AF_INET)
		वापस माप(काष्ठा iphdr);
	अन्यथा
		वापस माप(काष्ठा ipv6hdr);
पूर्ण

अटल पूर्णांक build_packet(व्योम)
अणु
	पूर्णांक ol3_len = 0, ol4_len = 0, il3_len = 0, il4_len = 0;
	पूर्णांक el3_len = 0;

	अगर (cfg_l3_extra)
		el3_len = l3_length(cfg_l3_extra);

	/* calculate header offsets */
	अगर (cfg_encap_proto) अणु
		ol3_len = l3_length(cfg_l3_outer);

		अगर (cfg_encap_proto == IPPROTO_GRE)
			ol4_len = माप(काष्ठा grehdr);
		अन्यथा अगर (cfg_encap_proto == IPPROTO_UDP)
			ol4_len = माप(काष्ठा udphdr) + माप(काष्ठा guehdr);
	पूर्ण

	il3_len = l3_length(cfg_l3_inner);
	il4_len = माप(काष्ठा udphdr);

	अगर (el3_len + ol3_len + ol4_len + il3_len + il4_len + cfg_payload_len >=
	    माप(buf))
		error(1, 0, "packet too large\n");

	/*
	 * Fill packet from inside out, to calculate correct checksums.
	 * But create ip beक्रमe udp headers, as udp uses ip क्रम pseuकरो-sum.
	 */
	स_रखो(buf + el3_len + ol3_len + ol4_len + il3_len + il4_len,
	       cfg_payload_अक्षर, cfg_payload_len);

	/* add zero byte क्रम udp csum padding */
	buf[el3_len + ol3_len + ol4_len + il3_len + il4_len + cfg_payload_len] = 0;

	चयन (cfg_l3_inner) अणु
	हाल PF_INET:
		build_ipv4_header(buf + el3_len + ol3_len + ol4_len,
				  IPPROTO_UDP,
				  in_saddr4.sin_addr.s_addr,
				  in_daddr4.sin_addr.s_addr,
				  il4_len + cfg_payload_len,
				  cfg_dsfield_inner);
		अवरोध;
	हाल PF_INET6:
		build_ipv6_header(buf + el3_len + ol3_len + ol4_len,
				  IPPROTO_UDP,
				  &in_saddr6, &in_daddr6,
				  il4_len + cfg_payload_len,
				  cfg_dsfield_inner);
		अवरोध;
	पूर्ण

	build_udp_header(buf + el3_len + ol3_len + ol4_len + il3_len,
			 cfg_payload_len, CFG_PORT_INNER, cfg_l3_inner);

	अगर (!cfg_encap_proto)
		वापस il3_len + il4_len + cfg_payload_len;

	चयन (cfg_l3_outer) अणु
	हाल PF_INET:
		build_ipv4_header(buf + el3_len, cfg_encap_proto,
				  out_saddr4.sin_addr.s_addr,
				  out_daddr4.sin_addr.s_addr,
				  ol4_len + il3_len + il4_len + cfg_payload_len,
				  cfg_dsfield_outer);
		अवरोध;
	हाल PF_INET6:
		build_ipv6_header(buf + el3_len, cfg_encap_proto,
				  &out_saddr6, &out_daddr6,
				  ol4_len + il3_len + il4_len + cfg_payload_len,
				  cfg_dsfield_outer);
		अवरोध;
	पूर्ण

	चयन (cfg_encap_proto) अणु
	हाल IPPROTO_UDP:
		build_gue_header(buf + el3_len + ol3_len + ol4_len -
				 माप(काष्ठा guehdr),
				 cfg_l3_inner == PF_INET ? IPPROTO_IPIP
							 : IPPROTO_IPV6);
		build_udp_header(buf + el3_len + ol3_len,
				 माप(काष्ठा guehdr) + il3_len + il4_len +
				 cfg_payload_len,
				 cfg_port_gue, cfg_l3_outer);
		अवरोध;
	हाल IPPROTO_GRE:
		build_gre_header(buf + el3_len + ol3_len,
				 cfg_l3_inner == PF_INET ? ETH_P_IP
							 : ETH_P_IPV6);
		अवरोध;
	पूर्ण

	चयन (cfg_l3_extra) अणु
	हाल PF_INET:
		build_ipv4_header(buf,
				  cfg_l3_outer == PF_INET ? IPPROTO_IPIP
							  : IPPROTO_IPV6,
				  extra_saddr4.sin_addr.s_addr,
				  extra_daddr4.sin_addr.s_addr,
				  ol3_len + ol4_len + il3_len + il4_len +
				  cfg_payload_len, 0);
		अवरोध;
	हाल PF_INET6:
		build_ipv6_header(buf,
				  cfg_l3_outer == PF_INET ? IPPROTO_IPIP
							  : IPPROTO_IPV6,
				  &extra_saddr6, &extra_daddr6,
				  ol3_len + ol4_len + il3_len + il4_len +
				  cfg_payload_len, 0);
		अवरोध;
	पूर्ण

	वापस el3_len + ol3_len + ol4_len + il3_len + il4_len +
	       cfg_payload_len;
पूर्ण

/* sender transmits encapsulated over RAW or unencap'd over UDP */
अटल पूर्णांक setup_tx(व्योम)
अणु
	पूर्णांक family, fd, ret;

	अगर (cfg_l3_extra)
		family = cfg_l3_extra;
	अन्यथा अगर (cfg_l3_outer)
		family = cfg_l3_outer;
	अन्यथा
		family = cfg_l3_inner;

	fd = socket(family, SOCK_RAW, IPPROTO_RAW);
	अगर (fd == -1)
		error(1, त्रुटि_सं, "socket tx");

	अगर (cfg_l3_extra) अणु
		अगर (cfg_l3_extra == PF_INET)
			ret = connect(fd, (व्योम *) &extra_daddr4,
				      माप(extra_daddr4));
		अन्यथा
			ret = connect(fd, (व्योम *) &extra_daddr6,
				      माप(extra_daddr6));
		अगर (ret)
			error(1, त्रुटि_सं, "connect tx");
	पूर्ण अन्यथा अगर (cfg_l3_outer) अणु
		/* connect to destination अगर not encapsulated */
		अगर (cfg_l3_outer == PF_INET)
			ret = connect(fd, (व्योम *) &out_daddr4,
				      माप(out_daddr4));
		अन्यथा
			ret = connect(fd, (व्योम *) &out_daddr6,
				      माप(out_daddr6));
		अगर (ret)
			error(1, त्रुटि_सं, "connect tx");
	पूर्ण अन्यथा अणु
		/* otherwise using loopback */
		अगर (cfg_l3_inner == PF_INET)
			ret = connect(fd, (व्योम *) &in_daddr4,
				      माप(in_daddr4));
		अन्यथा
			ret = connect(fd, (व्योम *) &in_daddr6,
				      माप(in_daddr6));
		अगर (ret)
			error(1, त्रुटि_सं, "connect tx");
	पूर्ण

	वापस fd;
पूर्ण

/* receiver पढ़ोs unencapsulated UDP */
अटल पूर्णांक setup_rx(व्योम)
अणु
	पूर्णांक fd, ret;

	fd = socket(cfg_l3_inner, SOCK_DGRAM, 0);
	अगर (fd == -1)
		error(1, त्रुटि_सं, "socket rx");

	अगर (cfg_l3_inner == PF_INET)
		ret = bind(fd, (व्योम *) &in_daddr4, माप(in_daddr4));
	अन्यथा
		ret = bind(fd, (व्योम *) &in_daddr6, माप(in_daddr6));
	अगर (ret)
		error(1, त्रुटि_सं, "bind rx");

	वापस fd;
पूर्ण

अटल पूर्णांक करो_tx(पूर्णांक fd, स्थिर अक्षर *pkt, पूर्णांक len)
अणु
	पूर्णांक ret;

	ret = ग_लिखो(fd, pkt, len);
	अगर (ret == -1)
		error(1, त्रुटि_सं, "send");
	अगर (ret != len)
		error(1, त्रुटि_सं, "send: len (%d < %d)\n", ret, len);

	वापस 1;
पूर्ण

अटल पूर्णांक करो_poll(पूर्णांक fd, लघु events, पूर्णांक समयout)
अणु
	काष्ठा pollfd pfd;
	पूर्णांक ret;

	pfd.fd = fd;
	pfd.events = events;

	ret = poll(&pfd, 1, समयout);
	अगर (ret == -1)
		error(1, त्रुटि_सं, "poll");
	अगर (ret && !(pfd.revents & POLLIN))
		error(1, त्रुटि_सं, "poll: unexpected event 0x%x\n", pfd.revents);

	वापस ret;
पूर्ण

अटल पूर्णांक करो_rx(पूर्णांक fd)
अणु
	अक्षर rbuf;
	पूर्णांक ret, num = 0;

	जबतक (1) अणु
		ret = recv(fd, &rbuf, 1, MSG_DONTWAIT);
		अगर (ret == -1 && त्रुटि_सं == EAGAIN)
			अवरोध;
		अगर (ret == -1)
			error(1, त्रुटि_सं, "recv");
		अगर (rbuf != cfg_payload_अक्षर)
			error(1, 0, "recv: payload mismatch");
		num++;
	पूर्ण

	वापस num;
पूर्ण

अटल पूर्णांक करो_मुख्य(व्योम)
अणु
	अचिन्हित दीर्घ tstop, treport, tcur;
	पूर्णांक fdt = -1, fdr = -1, len, tx = 0, rx = 0;

	अगर (!cfg_only_tx)
		fdr = setup_rx();
	अगर (!cfg_only_rx)
		fdt = setup_tx();

	len = build_packet();

	tcur = util_समय_लो();
	treport = tcur + 1000;
	tstop = tcur + (cfg_num_secs * 1000);

	जबतक (1) अणु
		अगर (!cfg_only_rx)
			tx += करो_tx(fdt, buf, len);

		अगर (!cfg_only_tx)
			rx += करो_rx(fdr);

		अगर (cfg_num_secs) अणु
			tcur = util_समय_लो();
			अगर (tcur >= tstop)
				अवरोध;
			अगर (tcur >= treport) अणु
				ख_लिखो(मानक_त्रुटि, "pkts: tx=%u rx=%u\n", tx, rx);
				tx = 0;
				rx = 0;
				treport = tcur + 1000;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (tx == cfg_num_pkt)
				अवरोध;
		पूर्ण
	पूर्ण

	/* पढ़ो straggler packets, अगर any */
	अगर (rx < tx) अणु
		tstop = util_समय_लो() + 100;
		जबतक (rx < tx) अणु
			tcur = util_समय_लो();
			अगर (tcur >= tstop)
				अवरोध;

			करो_poll(fdr, POLLIN, tstop - tcur);
			rx += करो_rx(fdr);
		पूर्ण
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "pkts: tx=%u rx=%u\n", tx, rx);

	अगर (fdr != -1 && बंद(fdr))
		error(1, त्रुटि_सं, "close rx");
	अगर (fdt != -1 && बंद(fdt))
		error(1, त्रुटि_सं, "close tx");

	/*
	 * success (== 0) only अगर received all packets
	 * unless failure is expected, in which हाल none must arrive.
	 */
	अगर (cfg_expect_failure)
		वापस rx != 0;
	अन्यथा
		वापस rx != tx;
पूर्ण


अटल व्योम __attribute__((noवापस)) usage(स्थिर अक्षर *filepath)
अणु
	ख_लिखो(मानक_त्रुटि, "Usage: %s [-e gre|gue|bare|none] [-i 4|6] [-l len] "
			"[-O 4|6] [-o 4|6] [-n num] [-t secs] [-R] [-T] "
			"[-s <osrc> [-d <odst>] [-S <isrc>] [-D <idst>] "
			"[-x <otos>] [-X <itos>] [-f <isport>] [-F]\n",
		filepath);
	निकास(1);
पूर्ण

अटल व्योम parse_addr(पूर्णांक family, व्योम *addr, स्थिर अक्षर *optarg)
अणु
	पूर्णांक ret;

	ret = inet_pton(family, optarg, addr);
	अगर (ret == -1)
		error(1, त्रुटि_सं, "inet_pton");
	अगर (ret == 0)
		error(1, 0, "inet_pton: bad string");
पूर्ण

अटल व्योम parse_addr4(काष्ठा sockaddr_in *addr, स्थिर अक्षर *optarg)
अणु
	parse_addr(AF_INET, &addr->sin_addr, optarg);
पूर्ण

अटल व्योम parse_addr6(काष्ठा sockaddr_in6 *addr, स्थिर अक्षर *optarg)
अणु
	parse_addr(AF_INET6, &addr->sin6_addr, optarg);
पूर्ण

अटल पूर्णांक parse_protocol_family(स्थिर अक्षर *filepath, स्थिर अक्षर *optarg)
अणु
	अगर (!म_भेद(optarg, "4"))
		वापस PF_INET;
	अगर (!म_भेद(optarg, "6"))
		वापस PF_INET6;

	usage(filepath);
पूर्ण

अटल व्योम parse_opts(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक c;

	जबतक ((c = getopt(argc, argv, "d:D:e:f:Fhi:l:n:o:O:Rs:S:t:Tx:X:")) != -1) अणु
		चयन (c) अणु
		हाल 'd':
			अगर (cfg_l3_outer == AF_UNSPEC)
				error(1, 0, "-d must be preceded by -o");
			अगर (cfg_l3_outer == AF_INET)
				parse_addr4(&out_daddr4, optarg);
			अन्यथा
				parse_addr6(&out_daddr6, optarg);
			अवरोध;
		हाल 'D':
			अगर (cfg_l3_inner == AF_UNSPEC)
				error(1, 0, "-D must be preceded by -i");
			अगर (cfg_l3_inner == AF_INET)
				parse_addr4(&in_daddr4, optarg);
			अन्यथा
				parse_addr6(&in_daddr6, optarg);
			अवरोध;
		हाल 'e':
			अगर (!म_भेद(optarg, "gre"))
				cfg_encap_proto = IPPROTO_GRE;
			अन्यथा अगर (!म_भेद(optarg, "gue"))
				cfg_encap_proto = IPPROTO_UDP;
			अन्यथा अगर (!म_भेद(optarg, "bare"))
				cfg_encap_proto = IPPROTO_IPIP;
			अन्यथा अगर (!म_भेद(optarg, "none"))
				cfg_encap_proto = IPPROTO_IP;	/* == 0 */
			अन्यथा
				usage(argv[0]);
			अवरोध;
		हाल 'f':
			cfg_src_port = म_से_दीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'F':
			cfg_expect_failure = true;
			अवरोध;
		हाल 'h':
			usage(argv[0]);
			अवरोध;
		हाल 'i':
			अगर (!म_भेद(optarg, "4"))
				cfg_l3_inner = PF_INET;
			अन्यथा अगर (!म_भेद(optarg, "6"))
				cfg_l3_inner = PF_INET6;
			अन्यथा
				usage(argv[0]);
			अवरोध;
		हाल 'l':
			cfg_payload_len = म_से_दीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'n':
			cfg_num_pkt = म_से_दीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'o':
			cfg_l3_outer = parse_protocol_family(argv[0], optarg);
			अवरोध;
		हाल 'O':
			cfg_l3_extra = parse_protocol_family(argv[0], optarg);
			अवरोध;
		हाल 'R':
			cfg_only_rx = true;
			अवरोध;
		हाल 's':
			अगर (cfg_l3_outer == AF_INET)
				parse_addr4(&out_saddr4, optarg);
			अन्यथा
				parse_addr6(&out_saddr6, optarg);
			अवरोध;
		हाल 'S':
			अगर (cfg_l3_inner == AF_INET)
				parse_addr4(&in_saddr4, optarg);
			अन्यथा
				parse_addr6(&in_saddr6, optarg);
			अवरोध;
		हाल 't':
			cfg_num_secs = म_से_दीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'T':
			cfg_only_tx = true;
			अवरोध;
		हाल 'x':
			cfg_dsfield_outer = म_से_दीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'X':
			cfg_dsfield_inner = म_से_दीर्घ(optarg, शून्य, 0);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (cfg_only_rx && cfg_only_tx)
		error(1, 0, "options: cannot combine rx-only and tx-only");

	अगर (cfg_encap_proto && cfg_l3_outer == AF_UNSPEC)
		error(1, 0, "options: must specify outer with encap");
	अन्यथा अगर ((!cfg_encap_proto) && cfg_l3_outer != AF_UNSPEC)
		error(1, 0, "options: cannot combine no-encap and outer");
	अन्यथा अगर ((!cfg_encap_proto) && cfg_l3_extra != AF_UNSPEC)
		error(1, 0, "options: cannot combine no-encap and extra");

	अगर (cfg_l3_inner == AF_UNSPEC)
		cfg_l3_inner = AF_INET6;
	अगर (cfg_l3_inner == AF_INET6 && cfg_encap_proto == IPPROTO_IPIP)
		cfg_encap_proto = IPPROTO_IPV6;

	/* RFC 6040 4.2:
	 *   on decap, अगर outer encountered congestion (CE == 0x3),
	 *   but inner cannot encode ECN (NoECT == 0x0), then drop packet.
	 */
	अगर (((cfg_dsfield_outer & 0x3) == 0x3) &&
	    ((cfg_dsfield_inner & 0x3) == 0x0))
		cfg_expect_failure = true;
पूर्ण

अटल व्योम prपूर्णांक_opts(व्योम)
अणु
	अगर (cfg_l3_inner == PF_INET6) अणु
		util_prपूर्णांकaddr("inner.dest6", (व्योम *) &in_daddr6);
		util_prपूर्णांकaddr("inner.source6", (व्योम *) &in_saddr6);
	पूर्ण अन्यथा अणु
		util_prपूर्णांकaddr("inner.dest4", (व्योम *) &in_daddr4);
		util_prपूर्णांकaddr("inner.source4", (व्योम *) &in_saddr4);
	पूर्ण

	अगर (!cfg_l3_outer)
		वापस;

	ख_लिखो(मानक_त्रुटि, "encap proto:   %u\n", cfg_encap_proto);

	अगर (cfg_l3_outer == PF_INET6) अणु
		util_prपूर्णांकaddr("outer.dest6", (व्योम *) &out_daddr6);
		util_prपूर्णांकaddr("outer.source6", (व्योम *) &out_saddr6);
	पूर्ण अन्यथा अणु
		util_prपूर्णांकaddr("outer.dest4", (व्योम *) &out_daddr4);
		util_prपूर्णांकaddr("outer.source4", (व्योम *) &out_saddr4);
	पूर्ण

	अगर (!cfg_l3_extra)
		वापस;

	अगर (cfg_l3_outer == PF_INET6) अणु
		util_prपूर्णांकaddr("extra.dest6", (व्योम *) &extra_daddr6);
		util_prपूर्णांकaddr("extra.source6", (व्योम *) &extra_saddr6);
	पूर्ण अन्यथा अणु
		util_prपूर्णांकaddr("extra.dest4", (व्योम *) &extra_daddr4);
		util_prपूर्णांकaddr("extra.source4", (व्योम *) &extra_saddr4);
	पूर्ण

पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	parse_opts(argc, argv);
	prपूर्णांक_opts();
	वापस करो_मुख्य();
पूर्ण
