<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <त्रुटिसं.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <समय.स>
#समावेश <arpa/inet.h>

#समावेश <libmnl/libmnl.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nfnetlink_queue.h>

काष्ठा options अणु
	bool count_packets;
	bool gso_enabled;
	पूर्णांक verbose;
	अचिन्हित पूर्णांक queue_num;
	अचिन्हित पूर्णांक समयout;
	uपूर्णांक32_t verdict;
	uपूर्णांक32_t delay_ms;
पूर्ण;

अटल अचिन्हित पूर्णांक queue_stats[5];
अटल काष्ठा options opts;

अटल व्योम help(स्थिर अक्षर *p)
अणु
	म_लिखो("Usage: %s [-c|-v [-vv] ] [-t timeout] [-q queue_num] [-Qdst_queue ] [ -d ms_delay ] [-G]\n", p);
पूर्ण

अटल पूर्णांक parse_attr_cb(स्थिर काष्ठा nlattr *attr, व्योम *data)
अणु
	स्थिर काष्ठा nlattr **tb = data;
	पूर्णांक type = mnl_attr_get_type(attr);

	/* skip unsupported attribute in user-space */
	अगर (mnl_attr_type_valid(attr, NFQA_MAX) < 0)
		वापस MNL_CB_OK;

	चयन (type) अणु
	हाल NFQA_MARK:
	हाल NFQA_IFINDEX_INDEV:
	हाल NFQA_IFINDEX_OUTDEV:
	हाल NFQA_IFINDEX_PHYSINDEV:
	हाल NFQA_IFINDEX_PHYSOUTDEV:
		अगर (mnl_attr_validate(attr, MNL_TYPE_U32) < 0) अणु
			लिखो_त्रुटि("mnl_attr_validate");
			वापस MNL_CB_ERROR;
		पूर्ण
		अवरोध;
	हाल NFQA_TIMESTAMP:
		अगर (mnl_attr_validate2(attr, MNL_TYPE_UNSPEC,
		    माप(काष्ठा nfqnl_msg_packet_बारtamp)) < 0) अणु
			लिखो_त्रुटि("mnl_attr_validate2");
			वापस MNL_CB_ERROR;
		पूर्ण
		अवरोध;
	हाल NFQA_HWADDR:
		अगर (mnl_attr_validate2(attr, MNL_TYPE_UNSPEC,
		    माप(काष्ठा nfqnl_msg_packet_hw)) < 0) अणु
			लिखो_त्रुटि("mnl_attr_validate2");
			वापस MNL_CB_ERROR;
		पूर्ण
		अवरोध;
	हाल NFQA_PAYLOAD:
		अवरोध;
	पूर्ण
	tb[type] = attr;
	वापस MNL_CB_OK;
पूर्ण

अटल पूर्णांक queue_cb(स्थिर काष्ठा nlmsghdr *nlh, व्योम *data)
अणु
	काष्ठा nlattr *tb[NFQA_MAX+1] = अणु 0 पूर्ण;
	काष्ठा nfqnl_msg_packet_hdr *ph = शून्य;
	uपूर्णांक32_t id = 0;

	(व्योम)data;

	mnl_attr_parse(nlh, माप(काष्ठा nfgenmsg), parse_attr_cb, tb);
	अगर (tb[NFQA_PACKET_HDR]) अणु
		ph = mnl_attr_get_payload(tb[NFQA_PACKET_HDR]);
		id = ntohl(ph->packet_id);

		अगर (opts.verbose > 0)
			म_लिखो("packet hook=%u, hwproto 0x%x",
				ntohs(ph->hw_protocol), ph->hook);

		अगर (ph->hook >= 5) अणु
			ख_लिखो(मानक_त्रुटि, "Unknown hook %d\n", ph->hook);
			वापस MNL_CB_ERROR;
		पूर्ण

		अगर (opts.verbose > 0) अणु
			uपूर्णांक32_t skbinfo = 0;

			अगर (tb[NFQA_SKB_INFO])
				skbinfo = ntohl(mnl_attr_get_u32(tb[NFQA_SKB_INFO]));
			अगर (skbinfo & NFQA_SKB_CSUMNOTREADY)
				म_लिखो(" csumnotready");
			अगर (skbinfo & NFQA_SKB_GSO)
				म_लिखो(" gso");
			अगर (skbinfo & NFQA_SKB_CSUM_NOTVERIFIED)
				म_लिखो(" csumnotverified");
			माला_दो("");
		पूर्ण

		अगर (opts.count_packets)
			queue_stats[ph->hook]++;
	पूर्ण

	वापस MNL_CB_OK + id;
पूर्ण

अटल काष्ठा nlmsghdr *
nfq_build_cfg_request(अक्षर *buf, uपूर्णांक8_t command, पूर्णांक queue_num)
अणु
	काष्ठा nlmsghdr *nlh = mnl_nlmsg_put_header(buf);
	काष्ठा nfqnl_msg_config_cmd cmd = अणु
		.command = command,
		.pf = htons(AF_INET),
	पूर्ण;
	काष्ठा nfgenmsg *nfg;

	nlh->nlmsg_type	= (NFNL_SUBSYS_QUEUE << 8) | NFQNL_MSG_CONFIG;
	nlh->nlmsg_flags = NLM_F_REQUEST;

	nfg = mnl_nlmsg_put_extra_header(nlh, माप(*nfg));

	nfg->nfgen_family = AF_UNSPEC;
	nfg->version = NFNETLINK_V0;
	nfg->res_id = htons(queue_num);

	mnl_attr_put(nlh, NFQA_CFG_CMD, माप(cmd), &cmd);

	वापस nlh;
पूर्ण

अटल काष्ठा nlmsghdr *
nfq_build_cfg_params(अक्षर *buf, uपूर्णांक8_t mode, पूर्णांक range, पूर्णांक queue_num)
अणु
	काष्ठा nlmsghdr *nlh = mnl_nlmsg_put_header(buf);
	काष्ठा nfqnl_msg_config_params params = अणु
		.copy_range = htonl(range),
		.copy_mode = mode,
	पूर्ण;
	काष्ठा nfgenmsg *nfg;

	nlh->nlmsg_type	= (NFNL_SUBSYS_QUEUE << 8) | NFQNL_MSG_CONFIG;
	nlh->nlmsg_flags = NLM_F_REQUEST;

	nfg = mnl_nlmsg_put_extra_header(nlh, माप(*nfg));
	nfg->nfgen_family = AF_UNSPEC;
	nfg->version = NFNETLINK_V0;
	nfg->res_id = htons(queue_num);

	mnl_attr_put(nlh, NFQA_CFG_PARAMS, माप(params), &params);

	वापस nlh;
पूर्ण

अटल काष्ठा nlmsghdr *
nfq_build_verdict(अक्षर *buf, पूर्णांक id, पूर्णांक queue_num, uपूर्णांक32_t verd)
अणु
	काष्ठा nfqnl_msg_verdict_hdr vh = अणु
		.verdict = htonl(verd),
		.id = htonl(id),
	पूर्ण;
	काष्ठा nlmsghdr *nlh;
	काष्ठा nfgenmsg *nfg;

	nlh = mnl_nlmsg_put_header(buf);
	nlh->nlmsg_type = (NFNL_SUBSYS_QUEUE << 8) | NFQNL_MSG_VERDICT;
	nlh->nlmsg_flags = NLM_F_REQUEST;
	nfg = mnl_nlmsg_put_extra_header(nlh, माप(*nfg));
	nfg->nfgen_family = AF_UNSPEC;
	nfg->version = NFNETLINK_V0;
	nfg->res_id = htons(queue_num);

	mnl_attr_put(nlh, NFQA_VERDICT_HDR, माप(vh), &vh);

	वापस nlh;
पूर्ण

अटल व्योम prपूर्णांक_stats(व्योम)
अणु
	अचिन्हित पूर्णांक last, total;
	पूर्णांक i;

	total = 0;
	last = queue_stats[0];

	क्रम (i = 0; i < 5; i++) अणु
		म_लिखो("hook %d packets %08u\n", i, queue_stats[i]);
		last = queue_stats[i];
		total += last;
	पूर्ण

	म_लिखो("%u packets total\n", total);
पूर्ण

काष्ठा mnl_socket *खोलो_queue(व्योम)
अणु
	अक्षर buf[MNL_SOCKET_BUFFER_SIZE];
	अचिन्हित पूर्णांक queue_num;
	काष्ठा mnl_socket *nl;
	काष्ठा nlmsghdr *nlh;
	काष्ठा समयval tv;
	uपूर्णांक32_t flags;

	nl = mnl_socket_खोलो(NETLINK_NETFILTER);
	अगर (nl == शून्य) अणु
		लिखो_त्रुटि("mnl_socket_open");
		निकास(निकास_त्रुटि);
	पूर्ण

	अगर (mnl_socket_bind(nl, 0, MNL_SOCKET_AUTOPID) < 0) अणु
		लिखो_त्रुटि("mnl_socket_bind");
		निकास(निकास_त्रुटि);
	पूर्ण

	queue_num = opts.queue_num;
	nlh = nfq_build_cfg_request(buf, NFQNL_CFG_CMD_BIND, queue_num);

	अगर (mnl_socket_sendto(nl, nlh, nlh->nlmsg_len) < 0) अणु
		लिखो_त्रुटि("mnl_socket_sendto");
		निकास(निकास_त्रुटि);
	पूर्ण

	nlh = nfq_build_cfg_params(buf, NFQNL_COPY_PACKET, 0xFFFF, queue_num);

	flags = opts.gso_enabled ? NFQA_CFG_F_GSO : 0;
	flags |= NFQA_CFG_F_UID_GID;
	mnl_attr_put_u32(nlh, NFQA_CFG_FLAGS, htonl(flags));
	mnl_attr_put_u32(nlh, NFQA_CFG_MASK, htonl(flags));

	अगर (mnl_socket_sendto(nl, nlh, nlh->nlmsg_len) < 0) अणु
		लिखो_त्रुटि("mnl_socket_sendto");
		निकास(निकास_त्रुटि);
	पूर्ण

	स_रखो(&tv, 0, माप(tv));
	tv.tv_sec = opts.समयout;
	अगर (opts.समयout && setsockopt(mnl_socket_get_fd(nl),
				       SOL_SOCKET, SO_RCVTIMEO,
				       &tv, माप(tv))) अणु
		लिखो_त्रुटि("setsockopt(SO_RCVTIMEO)");
		निकास(निकास_त्रुटि);
	पूर्ण

	वापस nl;
पूर्ण

अटल व्योम sleep_ms(uपूर्णांक32_t delay)
अणु
	काष्ठा बारpec ts = अणु .tv_sec = delay / 1000 पूर्ण;

	delay %= 1000;

	ts.tv_nsec = delay * 1000llu * 1000llu;

	nanosleep(&ts, शून्य);
पूर्ण

अटल पूर्णांक मुख्यloop(व्योम)
अणु
	अचिन्हित पूर्णांक buflen = 64 * 1024 + MNL_SOCKET_BUFFER_SIZE;
	काष्ठा mnl_socket *nl;
	काष्ठा nlmsghdr *nlh;
	अचिन्हित पूर्णांक portid;
	अक्षर *buf;
	पूर्णांक ret;

	buf = दो_स्मृति(buflen);
	अगर (!buf) अणु
		लिखो_त्रुटि("malloc");
		निकास(निकास_त्रुटि);
	पूर्ण

	nl = खोलो_queue();
	portid = mnl_socket_get_portid(nl);

	क्रम (;;) अणु
		uपूर्णांक32_t id;

		ret = mnl_socket_recvfrom(nl, buf, buflen);
		अगर (ret == -1) अणु
			अगर (त्रुटि_सं == ENOBUFS || त्रुटि_सं == EINTR)
				जारी;

			अगर (त्रुटि_सं == EAGAIN) अणु
				त्रुटि_सं = 0;
				ret = 0;
				अवरोध;
			पूर्ण

			लिखो_त्रुटि("mnl_socket_recvfrom");
			निकास(निकास_त्रुटि);
		पूर्ण

		ret = mnl_cb_run(buf, ret, 0, portid, queue_cb, शून्य);
		अगर (ret < 0) अणु
			लिखो_त्रुटि("mnl_cb_run");
			निकास(निकास_त्रुटि);
		पूर्ण

		id = ret - MNL_CB_OK;
		अगर (opts.delay_ms)
			sleep_ms(opts.delay_ms);

		nlh = nfq_build_verdict(buf, id, opts.queue_num, opts.verdict);
		अगर (mnl_socket_sendto(nl, nlh, nlh->nlmsg_len) < 0) अणु
			लिखो_त्रुटि("mnl_socket_sendto");
			निकास(निकास_त्रुटि);
		पूर्ण
	पूर्ण

	mnl_socket_बंद(nl);

	वापस ret;
पूर्ण

अटल व्योम parse_opts(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक c;

	जबतक ((c = getopt(argc, argv, "chvt:q:Q:d:G")) != -1) अणु
		चयन (c) अणु
		हाल 'c':
			opts.count_packets = true;
			अवरोध;
		हाल 'h':
			help(argv[0]);
			निकास(0);
			अवरोध;
		हाल 'q':
			opts.queue_num = म_से_प(optarg);
			अगर (opts.queue_num > 0xffff)
				opts.queue_num = 0;
			अवरोध;
		हाल 'Q':
			opts.verdict = म_से_प(optarg);
			अगर (opts.verdict > 0xffff) अणु
				ख_लिखो(मानक_त्रुटि, "Expected destination queue number\n");
				निकास(1);
			पूर्ण

			opts.verdict <<= 16;
			opts.verdict |= NF_QUEUE;
			अवरोध;
		हाल 'd':
			opts.delay_ms = म_से_प(optarg);
			अगर (opts.delay_ms == 0) अणु
				ख_लिखो(मानक_त्रुटि, "Expected nonzero delay (in milliseconds)\n");
				निकास(1);
			पूर्ण
			अवरोध;
		हाल 't':
			opts.समयout = म_से_प(optarg);
			अवरोध;
		हाल 'G':
			opts.gso_enabled = false;
			अवरोध;
		हाल 'v':
			opts.verbose++;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (opts.verdict != NF_ACCEPT && (opts.verdict >> 16 == opts.queue_num)) अणु
		ख_लिखो(मानक_त्रुटि, "Cannot use same destination and source queue\n");
		निकास(1);
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक ret;

	opts.verdict = NF_ACCEPT;
	opts.gso_enabled = true;

	parse_opts(argc, argv);

	ret = मुख्यloop();
	अगर (opts.count_packets)
		prपूर्णांक_stats();

	वापस ret;
पूर्ण
