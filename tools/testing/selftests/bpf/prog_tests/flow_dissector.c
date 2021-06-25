<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <network_helpers.h>
#समावेश <error.h>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_tun.h>
#समावेश <sys/uपन.स>

#समावेश "bpf_flow.skel.h"

#अगर_अघोषित IP_MF
#घोषणा IP_MF 0x2000
#पूर्ण_अगर

#घोषणा CHECK_FLOW_KEYS(desc, got, expected)				\
	CHECK_ATTR(स_भेद(&got, &expected, माप(got)) != 0,		\
	      desc,							\
	      "nhoff=%u/%u "						\
	      "thoff=%u/%u "						\
	      "addr_proto=0x%x/0x%x "					\
	      "is_frag=%u/%u "						\
	      "is_first_frag=%u/%u "					\
	      "is_encap=%u/%u "						\
	      "ip_proto=0x%x/0x%x "					\
	      "n_proto=0x%x/0x%x "					\
	      "flow_label=0x%x/0x%x "					\
	      "sport=%u/%u "						\
	      "dport=%u/%u\n",						\
	      got.nhoff, expected.nhoff,				\
	      got.thoff, expected.thoff,				\
	      got.addr_proto, expected.addr_proto,			\
	      got.is_frag, expected.is_frag,				\
	      got.is_first_frag, expected.is_first_frag,		\
	      got.is_encap, expected.is_encap,				\
	      got.ip_proto, expected.ip_proto,				\
	      got.n_proto, expected.n_proto,				\
	      got.flow_label, expected.flow_label,			\
	      got.sport, expected.sport,				\
	      got.dport, expected.dport)

काष्ठा ipv4_pkt अणु
	काष्ठा ethhdr eth;
	काष्ठा iphdr iph;
	काष्ठा tcphdr tcp;
पूर्ण __packed;

काष्ठा ipip_pkt अणु
	काष्ठा ethhdr eth;
	काष्ठा iphdr iph;
	काष्ठा iphdr iph_inner;
	काष्ठा tcphdr tcp;
पूर्ण __packed;

काष्ठा svlan_ipv4_pkt अणु
	काष्ठा ethhdr eth;
	__u16 vlan_tci;
	__u16 vlan_proto;
	काष्ठा iphdr iph;
	काष्ठा tcphdr tcp;
पूर्ण __packed;

काष्ठा ipv6_pkt अणु
	काष्ठा ethhdr eth;
	काष्ठा ipv6hdr iph;
	काष्ठा tcphdr tcp;
पूर्ण __packed;

काष्ठा ipv6_frag_pkt अणु
	काष्ठा ethhdr eth;
	काष्ठा ipv6hdr iph;
	काष्ठा frag_hdr अणु
		__u8 nexthdr;
		__u8 reserved;
		__be16 frag_off;
		__be32 identअगरication;
	पूर्ण ipf;
	काष्ठा tcphdr tcp;
पूर्ण __packed;

काष्ठा dvlan_ipv6_pkt अणु
	काष्ठा ethhdr eth;
	__u16 vlan_tci;
	__u16 vlan_proto;
	__u16 vlan_tci2;
	__u16 vlan_proto2;
	काष्ठा ipv6hdr iph;
	काष्ठा tcphdr tcp;
पूर्ण __packed;

काष्ठा test अणु
	स्थिर अक्षर *name;
	जोड़ अणु
		काष्ठा ipv4_pkt ipv4;
		काष्ठा svlan_ipv4_pkt svlan_ipv4;
		काष्ठा ipip_pkt ipip;
		काष्ठा ipv6_pkt ipv6;
		काष्ठा ipv6_frag_pkt ipv6_frag;
		काष्ठा dvlan_ipv6_pkt dvlan_ipv6;
	पूर्ण pkt;
	काष्ठा bpf_flow_keys keys;
	__u32 flags;
पूर्ण;

#घोषणा VLAN_HLEN	4

अटल __u32 duration;
काष्ठा test tests[] = अणु
	अणु
		.name = "ipv4",
		.pkt.ipv4 = अणु
			.eth.h_proto = __bpf_स्थिरant_htons(ETH_P_IP),
			.iph.ihl = 5,
			.iph.protocol = IPPROTO_TCP,
			.iph.tot_len = __bpf_स्थिरant_htons(MAGIC_BYTES),
			.tcp.करोff = 5,
			.tcp.source = 80,
			.tcp.dest = 8080,
		पूर्ण,
		.keys = अणु
			.nhoff = ETH_HLEN,
			.thoff = ETH_HLEN + माप(काष्ठा iphdr),
			.addr_proto = ETH_P_IP,
			.ip_proto = IPPROTO_TCP,
			.n_proto = __bpf_स्थिरant_htons(ETH_P_IP),
			.sport = 80,
			.dport = 8080,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "ipv6",
		.pkt.ipv6 = अणु
			.eth.h_proto = __bpf_स्थिरant_htons(ETH_P_IPV6),
			.iph.nexthdr = IPPROTO_TCP,
			.iph.payload_len = __bpf_स्थिरant_htons(MAGIC_BYTES),
			.tcp.करोff = 5,
			.tcp.source = 80,
			.tcp.dest = 8080,
		पूर्ण,
		.keys = अणु
			.nhoff = ETH_HLEN,
			.thoff = ETH_HLEN + माप(काष्ठा ipv6hdr),
			.addr_proto = ETH_P_IPV6,
			.ip_proto = IPPROTO_TCP,
			.n_proto = __bpf_स्थिरant_htons(ETH_P_IPV6),
			.sport = 80,
			.dport = 8080,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "802.1q-ipv4",
		.pkt.svlan_ipv4 = अणु
			.eth.h_proto = __bpf_स्थिरant_htons(ETH_P_8021Q),
			.vlan_proto = __bpf_स्थिरant_htons(ETH_P_IP),
			.iph.ihl = 5,
			.iph.protocol = IPPROTO_TCP,
			.iph.tot_len = __bpf_स्थिरant_htons(MAGIC_BYTES),
			.tcp.करोff = 5,
			.tcp.source = 80,
			.tcp.dest = 8080,
		पूर्ण,
		.keys = अणु
			.nhoff = ETH_HLEN + VLAN_HLEN,
			.thoff = ETH_HLEN + VLAN_HLEN + माप(काष्ठा iphdr),
			.addr_proto = ETH_P_IP,
			.ip_proto = IPPROTO_TCP,
			.n_proto = __bpf_स्थिरant_htons(ETH_P_IP),
			.sport = 80,
			.dport = 8080,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "802.1ad-ipv6",
		.pkt.dvlan_ipv6 = अणु
			.eth.h_proto = __bpf_स्थिरant_htons(ETH_P_8021AD),
			.vlan_proto = __bpf_स्थिरant_htons(ETH_P_8021Q),
			.vlan_proto2 = __bpf_स्थिरant_htons(ETH_P_IPV6),
			.iph.nexthdr = IPPROTO_TCP,
			.iph.payload_len = __bpf_स्थिरant_htons(MAGIC_BYTES),
			.tcp.करोff = 5,
			.tcp.source = 80,
			.tcp.dest = 8080,
		पूर्ण,
		.keys = अणु
			.nhoff = ETH_HLEN + VLAN_HLEN * 2,
			.thoff = ETH_HLEN + VLAN_HLEN * 2 +
				माप(काष्ठा ipv6hdr),
			.addr_proto = ETH_P_IPV6,
			.ip_proto = IPPROTO_TCP,
			.n_proto = __bpf_स्थिरant_htons(ETH_P_IPV6),
			.sport = 80,
			.dport = 8080,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "ipv4-frag",
		.pkt.ipv4 = अणु
			.eth.h_proto = __bpf_स्थिरant_htons(ETH_P_IP),
			.iph.ihl = 5,
			.iph.protocol = IPPROTO_TCP,
			.iph.tot_len = __bpf_स्थिरant_htons(MAGIC_BYTES),
			.iph.frag_off = __bpf_स्थिरant_htons(IP_MF),
			.tcp.करोff = 5,
			.tcp.source = 80,
			.tcp.dest = 8080,
		पूर्ण,
		.keys = अणु
			.flags = BPF_FLOW_DISSECTOR_F_PARSE_1ST_FRAG,
			.nhoff = ETH_HLEN,
			.thoff = ETH_HLEN + माप(काष्ठा iphdr),
			.addr_proto = ETH_P_IP,
			.ip_proto = IPPROTO_TCP,
			.n_proto = __bpf_स्थिरant_htons(ETH_P_IP),
			.is_frag = true,
			.is_first_frag = true,
			.sport = 80,
			.dport = 8080,
		पूर्ण,
		.flags = BPF_FLOW_DISSECTOR_F_PARSE_1ST_FRAG,
	पूर्ण,
	अणु
		.name = "ipv4-no-frag",
		.pkt.ipv4 = अणु
			.eth.h_proto = __bpf_स्थिरant_htons(ETH_P_IP),
			.iph.ihl = 5,
			.iph.protocol = IPPROTO_TCP,
			.iph.tot_len = __bpf_स्थिरant_htons(MAGIC_BYTES),
			.iph.frag_off = __bpf_स्थिरant_htons(IP_MF),
			.tcp.करोff = 5,
			.tcp.source = 80,
			.tcp.dest = 8080,
		पूर्ण,
		.keys = अणु
			.nhoff = ETH_HLEN,
			.thoff = ETH_HLEN + माप(काष्ठा iphdr),
			.addr_proto = ETH_P_IP,
			.ip_proto = IPPROTO_TCP,
			.n_proto = __bpf_स्थिरant_htons(ETH_P_IP),
			.is_frag = true,
			.is_first_frag = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "ipv6-frag",
		.pkt.ipv6_frag = अणु
			.eth.h_proto = __bpf_स्थिरant_htons(ETH_P_IPV6),
			.iph.nexthdr = IPPROTO_FRAGMENT,
			.iph.payload_len = __bpf_स्थिरant_htons(MAGIC_BYTES),
			.ipf.nexthdr = IPPROTO_TCP,
			.tcp.करोff = 5,
			.tcp.source = 80,
			.tcp.dest = 8080,
		पूर्ण,
		.keys = अणु
			.flags = BPF_FLOW_DISSECTOR_F_PARSE_1ST_FRAG,
			.nhoff = ETH_HLEN,
			.thoff = ETH_HLEN + माप(काष्ठा ipv6hdr) +
				माप(काष्ठा frag_hdr),
			.addr_proto = ETH_P_IPV6,
			.ip_proto = IPPROTO_TCP,
			.n_proto = __bpf_स्थिरant_htons(ETH_P_IPV6),
			.is_frag = true,
			.is_first_frag = true,
			.sport = 80,
			.dport = 8080,
		पूर्ण,
		.flags = BPF_FLOW_DISSECTOR_F_PARSE_1ST_FRAG,
	पूर्ण,
	अणु
		.name = "ipv6-no-frag",
		.pkt.ipv6_frag = अणु
			.eth.h_proto = __bpf_स्थिरant_htons(ETH_P_IPV6),
			.iph.nexthdr = IPPROTO_FRAGMENT,
			.iph.payload_len = __bpf_स्थिरant_htons(MAGIC_BYTES),
			.ipf.nexthdr = IPPROTO_TCP,
			.tcp.करोff = 5,
			.tcp.source = 80,
			.tcp.dest = 8080,
		पूर्ण,
		.keys = अणु
			.nhoff = ETH_HLEN,
			.thoff = ETH_HLEN + माप(काष्ठा ipv6hdr) +
				माप(काष्ठा frag_hdr),
			.addr_proto = ETH_P_IPV6,
			.ip_proto = IPPROTO_TCP,
			.n_proto = __bpf_स्थिरant_htons(ETH_P_IPV6),
			.is_frag = true,
			.is_first_frag = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "ipv6-flow-label",
		.pkt.ipv6 = अणु
			.eth.h_proto = __bpf_स्थिरant_htons(ETH_P_IPV6),
			.iph.nexthdr = IPPROTO_TCP,
			.iph.payload_len = __bpf_स्थिरant_htons(MAGIC_BYTES),
			.iph.flow_lbl = अणु 0xb, 0xee, 0xef पूर्ण,
			.tcp.करोff = 5,
			.tcp.source = 80,
			.tcp.dest = 8080,
		पूर्ण,
		.keys = अणु
			.nhoff = ETH_HLEN,
			.thoff = ETH_HLEN + माप(काष्ठा ipv6hdr),
			.addr_proto = ETH_P_IPV6,
			.ip_proto = IPPROTO_TCP,
			.n_proto = __bpf_स्थिरant_htons(ETH_P_IPV6),
			.sport = 80,
			.dport = 8080,
			.flow_label = __bpf_स्थिरant_htonl(0xbeeef),
		पूर्ण,
	पूर्ण,
	अणु
		.name = "ipv6-no-flow-label",
		.pkt.ipv6 = अणु
			.eth.h_proto = __bpf_स्थिरant_htons(ETH_P_IPV6),
			.iph.nexthdr = IPPROTO_TCP,
			.iph.payload_len = __bpf_स्थिरant_htons(MAGIC_BYTES),
			.iph.flow_lbl = अणु 0xb, 0xee, 0xef पूर्ण,
			.tcp.करोff = 5,
			.tcp.source = 80,
			.tcp.dest = 8080,
		पूर्ण,
		.keys = अणु
			.flags = BPF_FLOW_DISSECTOR_F_STOP_AT_FLOW_LABEL,
			.nhoff = ETH_HLEN,
			.thoff = ETH_HLEN + माप(काष्ठा ipv6hdr),
			.addr_proto = ETH_P_IPV6,
			.ip_proto = IPPROTO_TCP,
			.n_proto = __bpf_स्थिरant_htons(ETH_P_IPV6),
			.flow_label = __bpf_स्थिरant_htonl(0xbeeef),
		पूर्ण,
		.flags = BPF_FLOW_DISSECTOR_F_STOP_AT_FLOW_LABEL,
	पूर्ण,
	अणु
		.name = "ipip-encap",
		.pkt.ipip = अणु
			.eth.h_proto = __bpf_स्थिरant_htons(ETH_P_IP),
			.iph.ihl = 5,
			.iph.protocol = IPPROTO_IPIP,
			.iph.tot_len = __bpf_स्थिरant_htons(MAGIC_BYTES),
			.iph_inner.ihl = 5,
			.iph_inner.protocol = IPPROTO_TCP,
			.iph_inner.tot_len =
				__bpf_स्थिरant_htons(MAGIC_BYTES) -
				माप(काष्ठा iphdr),
			.tcp.करोff = 5,
			.tcp.source = 80,
			.tcp.dest = 8080,
		पूर्ण,
		.keys = अणु
			.nhoff = ETH_HLEN,
			.thoff = ETH_HLEN + माप(काष्ठा iphdr) +
				माप(काष्ठा iphdr),
			.addr_proto = ETH_P_IP,
			.ip_proto = IPPROTO_TCP,
			.n_proto = __bpf_स्थिरant_htons(ETH_P_IP),
			.is_encap = true,
			.sport = 80,
			.dport = 8080,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "ipip-no-encap",
		.pkt.ipip = अणु
			.eth.h_proto = __bpf_स्थिरant_htons(ETH_P_IP),
			.iph.ihl = 5,
			.iph.protocol = IPPROTO_IPIP,
			.iph.tot_len = __bpf_स्थिरant_htons(MAGIC_BYTES),
			.iph_inner.ihl = 5,
			.iph_inner.protocol = IPPROTO_TCP,
			.iph_inner.tot_len =
				__bpf_स्थिरant_htons(MAGIC_BYTES) -
				माप(काष्ठा iphdr),
			.tcp.करोff = 5,
			.tcp.source = 80,
			.tcp.dest = 8080,
		पूर्ण,
		.keys = अणु
			.flags = BPF_FLOW_DISSECTOR_F_STOP_AT_ENCAP,
			.nhoff = ETH_HLEN,
			.thoff = ETH_HLEN + माप(काष्ठा iphdr),
			.addr_proto = ETH_P_IP,
			.ip_proto = IPPROTO_IPIP,
			.n_proto = __bpf_स्थिरant_htons(ETH_P_IP),
			.is_encap = true,
		पूर्ण,
		.flags = BPF_FLOW_DISSECTOR_F_STOP_AT_ENCAP,
	पूर्ण,
पूर्ण;

अटल पूर्णांक create_tap(स्थिर अक्षर *अगरname)
अणु
	काष्ठा अगरreq अगरr = अणु
		.अगरr_flags = IFF_TAP | IFF_NO_PI | IFF_NAPI | IFF_NAPI_FRAGS,
	पूर्ण;
	पूर्णांक fd, ret;

	म_नकलन(अगरr.अगरr_name, अगरname, माप(अगरr.अगरr_name));

	fd = खोलो("/dev/net/tun", O_RDWR);
	अगर (fd < 0)
		वापस -1;

	ret = ioctl(fd, TUNSETIFF, &अगरr);
	अगर (ret)
		वापस -1;

	वापस fd;
पूर्ण

अटल पूर्णांक tx_tap(पूर्णांक fd, व्योम *pkt, माप_प्रकार len)
अणु
	काष्ठा iovec iov[] = अणु
		अणु
			.iov_len = len,
			.iov_base = pkt,
		पूर्ण,
	पूर्ण;
	वापस ग_लिखोv(fd, iov, ARRAY_SIZE(iov));
पूर्ण

अटल पूर्णांक अगरup(स्थिर अक्षर *अगरname)
अणु
	काष्ठा अगरreq अगरr = अणुपूर्ण;
	पूर्णांक sk, ret;

	म_नकलन(अगरr.अगरr_name, अगरname, माप(अगरr.अगरr_name));

	sk = socket(PF_INET, SOCK_DGRAM, 0);
	अगर (sk < 0)
		वापस -1;

	ret = ioctl(sk, SIOCGIFFLAGS, &अगरr);
	अगर (ret) अणु
		बंद(sk);
		वापस -1;
	पूर्ण

	अगरr.अगरr_flags |= IFF_UP;
	ret = ioctl(sk, SIOCSIFFLAGS, &अगरr);
	अगर (ret) अणु
		बंद(sk);
		वापस -1;
	पूर्ण

	बंद(sk);
	वापस 0;
पूर्ण

अटल पूर्णांक init_prog_array(काष्ठा bpf_object *obj, काष्ठा bpf_map *prog_array)
अणु
	पूर्णांक i, err, map_fd, prog_fd;
	काष्ठा bpf_program *prog;
	अक्षर prog_name[32];

	map_fd = bpf_map__fd(prog_array);
	अगर (map_fd < 0)
		वापस -1;

	क्रम (i = 0; i < bpf_map__def(prog_array)->max_entries; i++) अणु
		snम_लिखो(prog_name, माप(prog_name), "flow_dissector/%i", i);

		prog = bpf_object__find_program_by_title(obj, prog_name);
		अगर (!prog)
			वापस -1;

		prog_fd = bpf_program__fd(prog);
		अगर (prog_fd < 0)
			वापस -1;

		err = bpf_map_update_elem(map_fd, &i, &prog_fd, BPF_ANY);
		अगर (err)
			वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम run_tests_skb_less(पूर्णांक tap_fd, काष्ठा bpf_map *keys)
अणु
	पूर्णांक i, err, keys_fd;

	keys_fd = bpf_map__fd(keys);
	अगर (CHECK(keys_fd < 0, "bpf_map__fd", "err %d\n", keys_fd))
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(tests); i++) अणु
		/* Keep in sync with 'flags' from eth_get_headlen. */
		__u32 eth_get_headlen_flags =
			BPF_FLOW_DISSECTOR_F_PARSE_1ST_FRAG;
		काष्ठा bpf_prog_test_run_attr tattr = अणुपूर्ण;
		काष्ठा bpf_flow_keys flow_keys = अणुपूर्ण;
		__u32 key = (__u32)(tests[i].keys.sport) << 16 |
			    tests[i].keys.dport;

		/* For skb-less हाल we can't pass input flags; run
		 * only the tests that have a matching set of flags.
		 */

		अगर (tests[i].flags != eth_get_headlen_flags)
			जारी;

		err = tx_tap(tap_fd, &tests[i].pkt, माप(tests[i].pkt));
		CHECK(err < 0, "tx_tap", "err %d errno %d\n", err, त्रुटि_सं);

		err = bpf_map_lookup_elem(keys_fd, &key, &flow_keys);
		CHECK_ATTR(err, tests[i].name, "bpf_map_lookup_elem %d\n", err);

		CHECK_ATTR(err, tests[i].name, "skb-less err %d\n", err);
		CHECK_FLOW_KEYS(tests[i].name, flow_keys, tests[i].keys);

		err = bpf_map_delete_elem(keys_fd, &key);
		CHECK_ATTR(err, tests[i].name, "bpf_map_delete_elem %d\n", err);
	पूर्ण
पूर्ण

अटल व्योम test_skb_less_prog_attach(काष्ठा bpf_flow *skel, पूर्णांक tap_fd)
अणु
	पूर्णांक err, prog_fd;

	prog_fd = bpf_program__fd(skel->progs._dissect);
	अगर (CHECK(prog_fd < 0, "bpf_program__fd", "err %d\n", prog_fd))
		वापस;

	err = bpf_prog_attach(prog_fd, 0, BPF_FLOW_DISSECTOR, 0);
	अगर (CHECK(err, "bpf_prog_attach", "err %d errno %d\n", err, त्रुटि_सं))
		वापस;

	run_tests_skb_less(tap_fd, skel->maps.last_dissection);

	err = bpf_prog_detach2(prog_fd, 0, BPF_FLOW_DISSECTOR);
	CHECK(err, "bpf_prog_detach2", "err %d errno %d\n", err, त्रुटि_सं);
पूर्ण

अटल व्योम test_skb_less_link_create(काष्ठा bpf_flow *skel, पूर्णांक tap_fd)
अणु
	काष्ठा bpf_link *link;
	पूर्णांक err, net_fd;

	net_fd = खोलो("/proc/self/ns/net", O_RDONLY);
	अगर (CHECK(net_fd < 0, "open(/proc/self/ns/net)", "err %d\n", त्रुटि_सं))
		वापस;

	link = bpf_program__attach_netns(skel->progs._dissect, net_fd);
	अगर (CHECK(IS_ERR(link), "attach_netns", "err %ld\n", PTR_ERR(link)))
		जाओ out_बंद;

	run_tests_skb_less(tap_fd, skel->maps.last_dissection);

	err = bpf_link__destroy(link);
	CHECK(err, "bpf_link__destroy", "err %d\n", err);
out_बंद:
	बंद(net_fd);
पूर्ण

व्योम test_flow_dissector(व्योम)
अणु
	पूर्णांक i, err, prog_fd, keys_fd = -1, tap_fd;
	काष्ठा bpf_flow *skel;

	skel = bpf_flow__खोलो_and_load();
	अगर (CHECK(!skel, "skel", "failed to open/load skeleton\n"))
		वापस;

	prog_fd = bpf_program__fd(skel->progs._dissect);
	अगर (CHECK(prog_fd < 0, "bpf_program__fd", "err %d\n", prog_fd))
		जाओ out_destroy_skel;
	keys_fd = bpf_map__fd(skel->maps.last_dissection);
	अगर (CHECK(keys_fd < 0, "bpf_map__fd", "err %d\n", keys_fd))
		जाओ out_destroy_skel;
	err = init_prog_array(skel->obj, skel->maps.jmp_table);
	अगर (CHECK(err, "init_prog_array", "err %d\n", err))
		जाओ out_destroy_skel;

	क्रम (i = 0; i < ARRAY_SIZE(tests); i++) अणु
		काष्ठा bpf_flow_keys flow_keys;
		काष्ठा bpf_prog_test_run_attr tattr = अणु
			.prog_fd = prog_fd,
			.data_in = &tests[i].pkt,
			.data_size_in = माप(tests[i].pkt),
			.data_out = &flow_keys,
		पूर्ण;
		अटल काष्ठा bpf_flow_keys ctx = अणुपूर्ण;

		अगर (tests[i].flags) अणु
			tattr.ctx_in = &ctx;
			tattr.ctx_size_in = माप(ctx);
			ctx.flags = tests[i].flags;
		पूर्ण

		err = bpf_prog_test_run_xattr(&tattr);
		CHECK_ATTR(tattr.data_size_out != माप(flow_keys) ||
			   err || tattr.retval != 1,
			   tests[i].name,
			   "err %d errno %d retval %d duration %d size %u/%zu\n",
			   err, त्रुटि_सं, tattr.retval, tattr.duration,
			   tattr.data_size_out, माप(flow_keys));
		CHECK_FLOW_KEYS(tests[i].name, flow_keys, tests[i].keys);
	पूर्ण

	/* Do the same tests but क्रम skb-less flow dissector.
	 * We use a known path in the net/tun driver that calls
	 * eth_get_headlen and we manually export bpf_flow_keys
	 * via BPF map in this हाल.
	 */

	tap_fd = create_tap("tap0");
	CHECK(tap_fd < 0, "create_tap", "tap_fd %d errno %d\n", tap_fd, त्रुटि_सं);
	err = अगरup("tap0");
	CHECK(err, "ifup", "err %d errno %d\n", err, त्रुटि_सं);

	/* Test direct prog attachment */
	test_skb_less_prog_attach(skel, tap_fd);
	/* Test indirect prog attachment via link */
	test_skb_less_link_create(skel, tap_fd);

	बंद(tap_fd);
out_destroy_skel:
	bpf_flow__destroy(skel);
पूर्ण
