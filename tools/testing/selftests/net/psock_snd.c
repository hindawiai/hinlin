<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा _GNU_SOURCE

#समावेश <arpa/inet.h>
#समावेश <त्रुटिसं.स>
#समावेश <error.h>
#समावेश <fcntl.h>
#समावेश <सीमा.स>
#समावेश <linux/filter.h>
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/virtio_net.h>
#समावेश <net/अगर.h>
#समावेश <net/ethernet.h>
#समावेश <netinet/ip.h>
#समावेश <netinet/udp.h>
#समावेश <poll.h>
#समावेश <sched.h>
#समावेश <stdbool.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <sys/socket.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <unistd.h>

#समावेश "psock_lib.h"

अटल bool	cfg_use_bind;
अटल bool	cfg_use_csum_off;
अटल bool	cfg_use_csum_off_bad;
अटल bool	cfg_use_dgram;
अटल bool	cfg_use_gso;
अटल bool	cfg_use_qdisc_bypass;
अटल bool	cfg_use_vlan;
अटल bool	cfg_use_vnet;

अटल अक्षर	*cfg_अगरname = "lo";
अटल पूर्णांक	cfg_mtu	= 1500;
अटल पूर्णांक	cfg_payload_len = DATA_LEN;
अटल पूर्णांक	cfg_truncate_len = पूर्णांक_उच्च;
अटल uपूर्णांक16_t	cfg_port = 8000;

/* test sending up to max mtu + 1 */
#घोषणा TEST_SZ	(माप(काष्ठा virtio_net_hdr) + ETH_HLEN + ETH_MAX_MTU + 1)

अटल अक्षर tbuf[TEST_SZ], rbuf[TEST_SZ];

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

अटल पूर्णांक build_vnet_header(व्योम *header)
अणु
	काष्ठा virtio_net_hdr *vh = header;

	vh->hdr_len = ETH_HLEN + माप(काष्ठा iphdr) + माप(काष्ठा udphdr);

	अगर (cfg_use_csum_off) अणु
		vh->flags |= VIRTIO_NET_HDR_F_NEEDS_CSUM;
		vh->csum_start = ETH_HLEN + माप(काष्ठा iphdr);
		vh->csum_offset = __builtin_दुरत्व(काष्ठा udphdr, check);

		/* position check field exactly one byte beyond end of packet */
		अगर (cfg_use_csum_off_bad)
			vh->csum_start += माप(काष्ठा udphdr) + cfg_payload_len -
					  vh->csum_offset - 1;
	पूर्ण

	अगर (cfg_use_gso) अणु
		vh->gso_type = VIRTIO_NET_HDR_GSO_UDP;
		vh->gso_size = cfg_mtu - माप(काष्ठा iphdr);
	पूर्ण

	वापस माप(*vh);
पूर्ण

अटल पूर्णांक build_eth_header(व्योम *header)
अणु
	काष्ठा ethhdr *eth = header;

	अगर (cfg_use_vlan) अणु
		uपूर्णांक16_t *tag = header + ETH_HLEN;

		eth->h_proto = htons(ETH_P_8021Q);
		tag[1] = htons(ETH_P_IP);
		वापस ETH_HLEN + 4;
	पूर्ण

	eth->h_proto = htons(ETH_P_IP);
	वापस ETH_HLEN;
पूर्ण

अटल पूर्णांक build_ipv4_header(व्योम *header, पूर्णांक payload_len)
अणु
	काष्ठा iphdr *iph = header;

	iph->ihl = 5;
	iph->version = 4;
	iph->ttl = 8;
	iph->tot_len = htons(माप(*iph) + माप(काष्ठा udphdr) + payload_len);
	iph->id = htons(1337);
	iph->protocol = IPPROTO_UDP;
	iph->saddr = htonl((172 << 24) | (17 << 16) | 2);
	iph->daddr = htonl((172 << 24) | (17 << 16) | 1);
	iph->check = build_ip_csum((व्योम *) iph, iph->ihl << 1, 0);

	वापस iph->ihl << 2;
पूर्ण

अटल पूर्णांक build_udp_header(व्योम *header, पूर्णांक payload_len)
अणु
	स्थिर पूर्णांक alen = माप(uपूर्णांक32_t);
	काष्ठा udphdr *udph = header;
	पूर्णांक len = माप(*udph) + payload_len;

	udph->source = htons(9);
	udph->dest = htons(cfg_port);
	udph->len = htons(len);

	अगर (cfg_use_csum_off)
		udph->check = build_ip_csum(header - (2 * alen), alen,
					    htons(IPPROTO_UDP) + udph->len);
	अन्यथा
		udph->check = 0;

	वापस माप(*udph);
पूर्ण

अटल पूर्णांक build_packet(पूर्णांक payload_len)
अणु
	पूर्णांक off = 0;

	off += build_vnet_header(tbuf);
	off += build_eth_header(tbuf + off);
	off += build_ipv4_header(tbuf + off, payload_len);
	off += build_udp_header(tbuf + off, payload_len);

	अगर (off + payload_len > माप(tbuf))
		error(1, 0, "payload length exceeds max");

	स_रखो(tbuf + off, DATA_CHAR, payload_len);

	वापस off + payload_len;
पूर्ण

अटल व्योम करो_bind(पूर्णांक fd)
अणु
	काष्ठा sockaddr_ll laddr = अणु0पूर्ण;

	laddr.sll_family = AF_PACKET;
	laddr.sll_protocol = htons(ETH_P_IP);
	laddr.sll_अगरindex = अगर_nametoindex(cfg_अगरname);
	अगर (!laddr.sll_अगरindex)
		error(1, त्रुटि_सं, "if_nametoindex");

	अगर (bind(fd, (व्योम *)&laddr, माप(laddr)))
		error(1, त्रुटि_सं, "bind");
पूर्ण

अटल व्योम करो_send(पूर्णांक fd, अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक ret;

	अगर (!cfg_use_vnet) अणु
		buf += माप(काष्ठा virtio_net_hdr);
		len -= माप(काष्ठा virtio_net_hdr);
	पूर्ण
	अगर (cfg_use_dgram) अणु
		buf += ETH_HLEN;
		len -= ETH_HLEN;
	पूर्ण

	अगर (cfg_use_bind) अणु
		ret = ग_लिखो(fd, buf, len);
	पूर्ण अन्यथा अणु
		काष्ठा sockaddr_ll laddr = अणु0पूर्ण;

		laddr.sll_protocol = htons(ETH_P_IP);
		laddr.sll_अगरindex = अगर_nametoindex(cfg_अगरname);
		अगर (!laddr.sll_अगरindex)
			error(1, त्रुटि_सं, "if_nametoindex");

		ret = sendto(fd, buf, len, 0, (व्योम *)&laddr, माप(laddr));
	पूर्ण

	अगर (ret == -1)
		error(1, त्रुटि_सं, "write");
	अगर (ret != len)
		error(1, 0, "write: %u %u", ret, len);

	ख_लिखो(मानक_त्रुटि, "tx: %u\n", ret);
पूर्ण

अटल पूर्णांक करो_tx(व्योम)
अणु
	स्थिर पूर्णांक one = 1;
	पूर्णांक fd, len;

	fd = socket(PF_PACKET, cfg_use_dgram ? SOCK_DGRAM : SOCK_RAW, 0);
	अगर (fd == -1)
		error(1, त्रुटि_सं, "socket t");

	अगर (cfg_use_bind)
		करो_bind(fd);

	अगर (cfg_use_qdisc_bypass &&
	    setsockopt(fd, SOL_PACKET, PACKET_QDISC_BYPASS, &one, माप(one)))
		error(1, त्रुटि_सं, "setsockopt qdisc bypass");

	अगर (cfg_use_vnet &&
	    setsockopt(fd, SOL_PACKET, PACKET_VNET_HDR, &one, माप(one)))
		error(1, त्रुटि_सं, "setsockopt vnet");

	len = build_packet(cfg_payload_len);

	अगर (cfg_truncate_len < len)
		len = cfg_truncate_len;

	करो_send(fd, tbuf, len);

	अगर (बंद(fd))
		error(1, त्रुटि_सं, "close t");

	वापस len;
पूर्ण

अटल पूर्णांक setup_rx(व्योम)
अणु
	काष्ठा समयval tv = अणु .tv_usec = 100 * 1000 पूर्ण;
	काष्ठा sockaddr_in raddr = अणु0पूर्ण;
	पूर्णांक fd;

	fd = socket(PF_INET, SOCK_DGRAM, 0);
	अगर (fd == -1)
		error(1, त्रुटि_सं, "socket r");

	अगर (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, माप(tv)))
		error(1, त्रुटि_सं, "setsockopt rcv timeout");

	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(cfg_port);
	raddr.sin_addr.s_addr = htonl(INADDR_ANY);

	अगर (bind(fd, (व्योम *)&raddr, माप(raddr)))
		error(1, त्रुटि_सं, "bind r");

	वापस fd;
पूर्ण

अटल व्योम करो_rx(पूर्णांक fd, पूर्णांक expected_len, अक्षर *expected)
अणु
	पूर्णांक ret;

	ret = recv(fd, rbuf, माप(rbuf), 0);
	अगर (ret == -1)
		error(1, त्रुटि_सं, "recv");
	अगर (ret != expected_len)
		error(1, 0, "recv: %u != %u", ret, expected_len);

	अगर (स_भेद(rbuf, expected, ret))
		error(1, 0, "recv: data mismatch");

	ख_लिखो(मानक_त्रुटि, "rx: %u\n", ret);
पूर्ण

अटल पूर्णांक setup_snअगरfer(व्योम)
अणु
	काष्ठा समयval tv = अणु .tv_usec = 100 * 1000 पूर्ण;
	पूर्णांक fd;

	fd = socket(PF_PACKET, SOCK_RAW, 0);
	अगर (fd == -1)
		error(1, त्रुटि_सं, "socket p");

	अगर (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, माप(tv)))
		error(1, त्रुटि_सं, "setsockopt rcv timeout");

	pair_udp_setfilter(fd);
	करो_bind(fd);

	वापस fd;
पूर्ण

अटल व्योम parse_opts(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक c;

	जबतक ((c = getopt(argc, argv, "bcCdgl:qt:vV")) != -1) अणु
		चयन (c) अणु
		हाल 'b':
			cfg_use_bind = true;
			अवरोध;
		हाल 'c':
			cfg_use_csum_off = true;
			अवरोध;
		हाल 'C':
			cfg_use_csum_off_bad = true;
			अवरोध;
		हाल 'd':
			cfg_use_dgram = true;
			अवरोध;
		हाल 'g':
			cfg_use_gso = true;
			अवरोध;
		हाल 'l':
			cfg_payload_len = म_से_अदीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'q':
			cfg_use_qdisc_bypass = true;
			अवरोध;
		हाल 't':
			cfg_truncate_len = म_से_अदीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'v':
			cfg_use_vnet = true;
			अवरोध;
		हाल 'V':
			cfg_use_vlan = true;
			अवरोध;
		शेष:
			error(1, 0, "%s: parse error", argv[0]);
		पूर्ण
	पूर्ण

	अगर (cfg_use_vlan && cfg_use_dgram)
		error(1, 0, "option vlan (-V) conflicts with dgram (-d)");

	अगर (cfg_use_csum_off && !cfg_use_vnet)
		error(1, 0, "option csum offload (-c) requires vnet (-v)");

	अगर (cfg_use_csum_off_bad && !cfg_use_csum_off)
		error(1, 0, "option csum bad (-C) requires csum offload (-c)");

	अगर (cfg_use_gso && !cfg_use_csum_off)
		error(1, 0, "option gso (-g) requires csum offload (-c)");
पूर्ण

अटल व्योम run_test(व्योम)
अणु
	पूर्णांक fdr, fds, total_len;

	fdr = setup_rx();
	fds = setup_snअगरfer();

	total_len = करो_tx();

	/* BPF filter accepts only this length, vlan changes MAC */
	अगर (cfg_payload_len == DATA_LEN && !cfg_use_vlan)
		करो_rx(fds, total_len - माप(काष्ठा virtio_net_hdr),
		      tbuf + माप(काष्ठा virtio_net_hdr));

	करो_rx(fdr, cfg_payload_len, tbuf + total_len - cfg_payload_len);

	अगर (बंद(fds))
		error(1, त्रुटि_सं, "close s");
	अगर (बंद(fdr))
		error(1, त्रुटि_सं, "close r");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	parse_opts(argc, argv);

	अगर (प्रणाली("ip link set dev lo mtu 1500"))
		error(1, त्रुटि_सं, "ip link set mtu");
	अगर (प्रणाली("ip addr add dev lo 172.17.0.1/24"))
		error(1, त्रुटि_सं, "ip addr add");

	run_test();

	ख_लिखो(मानक_त्रुटि, "OK\n\n");
	वापस 0;
पूर्ण
