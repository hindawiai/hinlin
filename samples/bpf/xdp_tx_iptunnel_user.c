<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2016 Facebook
 */
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_link.h>
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <net/अगर.h>
#समावेश <sys/resource.h>
#समावेश <arpa/inet.h>
#समावेश <netinet/ether.h>
#समावेश <unistd.h>
#समावेश <समय.स>
#समावेश <bpf/libbpf.h>
#समावेश <bpf/bpf.h>
#समावेश "bpf_util.h"
#समावेश "xdp_tx_iptunnel_common.h"

#घोषणा STATS_INTERVAL_S 2U

अटल पूर्णांक अगरindex = -1;
अटल __u32 xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST;
अटल पूर्णांक rxcnt_map_fd;
अटल __u32 prog_id;

अटल व्योम पूर्णांक_निकास(पूर्णांक sig)
अणु
	__u32 curr_prog_id = 0;

	अगर (अगरindex > -1) अणु
		अगर (bpf_get_link_xdp_id(अगरindex, &curr_prog_id, xdp_flags)) अणु
			म_लिखो("bpf_get_link_xdp_id failed\n");
			निकास(1);
		पूर्ण
		अगर (prog_id == curr_prog_id)
			bpf_set_link_xdp_fd(अगरindex, -1, xdp_flags);
		अन्यथा अगर (!curr_prog_id)
			म_लिखो("couldn't find a prog id on a given iface\n");
		अन्यथा
			म_लिखो("program on interface changed, not removing\n");
	पूर्ण
	निकास(0);
पूर्ण

/* simple per-protocol drop counter
 */
अटल व्योम poll_stats(अचिन्हित पूर्णांक समाप्त_after_s)
अणु
	स्थिर अचिन्हित पूर्णांक nr_protos = 256;
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	समय_प्रकार started_at = समय(शून्य);
	__u64 values[nr_cpus], prev[nr_protos][nr_cpus];
	__u32 proto;
	पूर्णांक i;

	स_रखो(prev, 0, माप(prev));

	जबतक (!समाप्त_after_s || समय(शून्य) - started_at <= समाप्त_after_s) अणु
		sleep(STATS_INTERVAL_S);

		क्रम (proto = 0; proto < nr_protos; proto++) अणु
			__u64 sum = 0;

			निश्चित(bpf_map_lookup_elem(rxcnt_map_fd, &proto,
						   values) == 0);
			क्रम (i = 0; i < nr_cpus; i++)
				sum += (values[i] - prev[proto][i]);

			अगर (sum)
				म_लिखो("proto %u: sum:%10llu pkts, rate:%10llu pkts/s\n",
				       proto, sum, sum / STATS_INTERVAL_S);
			स_नकल(prev[proto], values, माप(values));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम usage(स्थिर अक्षर *cmd)
अणु
	म_लिखो("Start a XDP prog which encapsulates incoming packets\n"
	       "in an IPv4/v6 header and XDP_TX it out.  The dst <VIP:PORT>\n"
	       "is used to select packets to encapsulate\n\n");
	म_लिखो("Usage: %s [...]\n", cmd);
	म_लिखो("    -i <ifname|ifindex> Interface\n");
	म_लिखो("    -a <vip-service-address> IPv4 or IPv6\n");
	म_लिखो("    -p <vip-service-port> A port range (e.g. 433-444) is also allowed\n");
	म_लिखो("    -s <source-ip> Used in the IPTunnel header\n");
	म_लिखो("    -d <dest-ip> Used in the IPTunnel header\n");
	म_लिखो("    -m <dest-MAC> Used in sending the IP Tunneled pkt\n");
	म_लिखो("    -T <stop-after-X-seconds> Default: 0 (forever)\n");
	म_लिखो("    -P <IP-Protocol> Default is TCP\n");
	म_लिखो("    -S use skb-mode\n");
	म_लिखो("    -N enforce native mode\n");
	म_लिखो("    -F Force loading the XDP prog\n");
	म_लिखो("    -h Display this help\n");
पूर्ण

अटल पूर्णांक parse_ipstr(स्थिर अक्षर *ipstr, अचिन्हित पूर्णांक *addr)
अणु
	अगर (inet_pton(AF_INET6, ipstr, addr) == 1) अणु
		वापस AF_INET6;
	पूर्ण अन्यथा अगर (inet_pton(AF_INET, ipstr, addr) == 1) अणु
		addr[1] = addr[2] = addr[3] = 0;
		वापस AF_INET;
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "%s is an invalid IP\n", ipstr);
	वापस AF_UNSPEC;
पूर्ण

अटल पूर्णांक parse_ports(स्थिर अक्षर *port_str, पूर्णांक *min_port, पूर्णांक *max_port)
अणु
	अक्षर *end;
	दीर्घ पंचांगp_min_port;
	दीर्घ पंचांगp_max_port;

	पंचांगp_min_port = म_से_दीर्घ(optarg, &end, 10);
	अगर (पंचांगp_min_port < 1 || पंचांगp_min_port > 65535) अणु
		ख_लिखो(मानक_त्रुटि, "Invalid port(s):%s\n", optarg);
		वापस 1;
	पूर्ण

	अगर (*end == '-') अणु
		end++;
		पंचांगp_max_port = म_से_दीर्घ(end, शून्य, 10);
		अगर (पंचांगp_max_port < 1 || पंचांगp_max_port > 65535) अणु
			ख_लिखो(मानक_त्रुटि, "Invalid port(s):%s\n", optarg);
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		पंचांगp_max_port = पंचांगp_min_port;
	पूर्ण

	अगर (पंचांगp_min_port > पंचांगp_max_port) अणु
		ख_लिखो(मानक_त्रुटि, "Invalid port(s):%s\n", optarg);
		वापस 1;
	पूर्ण

	अगर (पंचांगp_max_port - पंचांगp_min_port + 1 > MAX_IPTNL_ENTRIES) अणु
		ख_लिखो(मानक_त्रुटि, "Port range (%s) is larger than %u\n",
			port_str, MAX_IPTNL_ENTRIES);
		वापस 1;
	पूर्ण
	*min_port = पंचांगp_min_port;
	*max_port = पंचांगp_max_port;

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_prog_load_attr prog_load_attr = अणु
		.prog_type	= BPF_PROG_TYPE_XDP,
	पूर्ण;
	पूर्णांक min_port = 0, max_port = 0, vip2tnl_map_fd;
	स्थिर अक्षर *optstr = "i:a:p:s:d:m:T:P:FSNh";
	अचिन्हित अक्षर opt_flags[256] = अणुपूर्ण;
	काष्ठा bpf_prog_info info = अणुपूर्ण;
	__u32 info_len = माप(info);
	अचिन्हित पूर्णांक समाप्त_after_s = 0;
	काष्ठा iptnl_info tnl = अणुपूर्ण;
	काष्ठा bpf_object *obj;
	काष्ठा vip vip = अणुपूर्ण;
	अक्षर filename[256];
	पूर्णांक opt, prog_fd;
	पूर्णांक i, err;

	tnl.family = AF_UNSPEC;
	vip.protocol = IPPROTO_TCP;

	क्रम (i = 0; i < म_माप(optstr); i++)
		अगर (optstr[i] != 'h' && 'a' <= optstr[i] && optstr[i] <= 'z')
			opt_flags[(अचिन्हित अक्षर)optstr[i]] = 1;

	जबतक ((opt = getopt(argc, argv, optstr)) != -1) अणु
		अचिन्हित लघु family;
		अचिन्हित पूर्णांक *v6;

		चयन (opt) अणु
		हाल 'i':
			अगरindex = अगर_nametoindex(optarg);
			अगर (!अगरindex)
				अगरindex = म_से_प(optarg);
			अवरोध;
		हाल 'a':
			vip.family = parse_ipstr(optarg, vip.daddr.v6);
			अगर (vip.family == AF_UNSPEC)
				वापस 1;
			अवरोध;
		हाल 'p':
			अगर (parse_ports(optarg, &min_port, &max_port))
				वापस 1;
			अवरोध;
		हाल 'P':
			vip.protocol = म_से_प(optarg);
			अवरोध;
		हाल 's':
		हाल 'd':
			अगर (opt == 's')
				v6 = tnl.saddr.v6;
			अन्यथा
				v6 = tnl.daddr.v6;

			family = parse_ipstr(optarg, v6);
			अगर (family == AF_UNSPEC)
				वापस 1;
			अगर (tnl.family == AF_UNSPEC) अणु
				tnl.family = family;
			पूर्ण अन्यथा अगर (tnl.family != family) अणु
				ख_लिखो(मानक_त्रुटि,
					"The IP version of the src and dst addresses used in the IP encapsulation does not match\n");
				वापस 1;
			पूर्ण
			अवरोध;
		हाल 'm':
			अगर (!ether_aton_r(optarg,
					  (काष्ठा ether_addr *)tnl.dmac)) अणु
				ख_लिखो(मानक_त्रुटि, "Invalid mac address:%s\n",
					optarg);
				वापस 1;
			पूर्ण
			अवरोध;
		हाल 'T':
			समाप्त_after_s = म_से_प(optarg);
			अवरोध;
		हाल 'S':
			xdp_flags |= XDP_FLAGS_SKB_MODE;
			अवरोध;
		हाल 'N':
			/* शेष, set below */
			अवरोध;
		हाल 'F':
			xdp_flags &= ~XDP_FLAGS_UPDATE_IF_NOEXIST;
			अवरोध;
		शेष:
			usage(argv[0]);
			वापस 1;
		पूर्ण
		opt_flags[opt] = 0;
	पूर्ण

	अगर (!(xdp_flags & XDP_FLAGS_SKB_MODE))
		xdp_flags |= XDP_FLAGS_DRV_MODE;

	क्रम (i = 0; i < म_माप(optstr); i++) अणु
		अगर (opt_flags[(अचिन्हित पूर्णांक)optstr[i]]) अणु
			ख_लिखो(मानक_त्रुटि, "Missing argument -%c\n", optstr[i]);
			usage(argv[0]);
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (!अगरindex) अणु
		ख_लिखो(मानक_त्रुटि, "Invalid ifname\n");
		वापस 1;
	पूर्ण

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	prog_load_attr.file = filename;

	अगर (bpf_prog_load_xattr(&prog_load_attr, &obj, &prog_fd))
		वापस 1;

	अगर (!prog_fd) अणु
		म_लिखो("bpf_prog_load_xattr: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस 1;
	पूर्ण

	rxcnt_map_fd = bpf_object__find_map_fd_by_name(obj, "rxcnt");
	vip2tnl_map_fd = bpf_object__find_map_fd_by_name(obj, "vip2tnl");
	अगर (vip2tnl_map_fd < 0 || rxcnt_map_fd < 0) अणु
		म_लिखो("bpf_object__find_map_fd_by_name failed\n");
		वापस 1;
	पूर्ण

	संकेत(संक_विघ्न, पूर्णांक_निकास);
	संकेत(संक_इति, पूर्णांक_निकास);

	जबतक (min_port <= max_port) अणु
		vip.dport = htons(min_port++);
		अगर (bpf_map_update_elem(vip2tnl_map_fd, &vip, &tnl,
					BPF_NOEXIST)) अणु
			लिखो_त्रुटि("bpf_map_update_elem(&vip2tnl)");
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (bpf_set_link_xdp_fd(अगरindex, prog_fd, xdp_flags) < 0) अणु
		म_लिखो("link set xdp fd failed\n");
		वापस 1;
	पूर्ण

	err = bpf_obj_get_info_by_fd(prog_fd, &info, &info_len);
	अगर (err) अणु
		म_लिखो("can't get prog info - %s\n", म_त्रुटि(त्रुटि_सं));
		वापस err;
	पूर्ण
	prog_id = info.id;

	poll_stats(समाप्त_after_s);

	bpf_set_link_xdp_fd(अगरindex, -1, xdp_flags);

	वापस 0;
पूर्ण
