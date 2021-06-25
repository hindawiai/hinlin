<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Test IPV6_FLOWINFO cmsg on send and recv */

#घोषणा _GNU_SOURCE

#समावेश <arpa/inet.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <error.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <सीमा.स>
#समावेश <linux/in6.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/socket.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश <unistd.h>

/* uapi/glibc weirdness may leave this undefined */
#अगर_अघोषित IPV6_FLOWINFO
#घोषणा IPV6_FLOWINFO 11
#पूर्ण_अगर

#अगर_अघोषित IPV6_FLOWLABEL_MGR
#घोषणा IPV6_FLOWLABEL_MGR 32
#पूर्ण_अगर

#घोषणा FLOWLABEL_WILDCARD	((uपूर्णांक32_t) -1)

अटल स्थिर अक्षर cfg_data[]	= "a";
अटल uपूर्णांक32_t cfg_label	= 1;

अटल व्योम करो_send(पूर्णांक fd, bool with_flowlabel, uपूर्णांक32_t flowlabel)
अणु
	अक्षर control[CMSG_SPACE(माप(flowlabel))] = अणु0पूर्ण;
	काष्ठा msghdr msg = अणु0पूर्ण;
	काष्ठा iovec iov = अणु0पूर्ण;
	पूर्णांक ret;

	iov.iov_base = (अक्षर *)cfg_data;
	iov.iov_len = माप(cfg_data);

	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;

	अगर (with_flowlabel) अणु
		काष्ठा cmsghdr *cm;

		cm = (व्योम *)control;
		cm->cmsg_len = CMSG_LEN(माप(flowlabel));
		cm->cmsg_level = SOL_IPV6;
		cm->cmsg_type = IPV6_FLOWINFO;
		*(uपूर्णांक32_t *)CMSG_DATA(cm) = htonl(flowlabel);

		msg.msg_control = control;
		msg.msg_controllen = माप(control);
	पूर्ण

	ret = sendmsg(fd, &msg, 0);
	अगर (ret == -1)
		error(1, त्रुटि_सं, "send");

	अगर (with_flowlabel)
		ख_लिखो(मानक_त्रुटि, "sent with label %u\n", flowlabel);
	अन्यथा
		ख_लिखो(मानक_त्रुटि, "sent without label\n");
पूर्ण

अटल व्योम करो_recv(पूर्णांक fd, bool with_flowlabel, uपूर्णांक32_t expect)
अणु
	अक्षर control[CMSG_SPACE(माप(expect))];
	अक्षर data[माप(cfg_data)];
	काष्ठा msghdr msg = अणु0पूर्ण;
	काष्ठा iovec iov = अणु0पूर्ण;
	काष्ठा cmsghdr *cm;
	uपूर्णांक32_t flowlabel;
	पूर्णांक ret;

	iov.iov_base = data;
	iov.iov_len = माप(data);

	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;

	स_रखो(control, 0, माप(control));
	msg.msg_control = control;
	msg.msg_controllen = माप(control);

	ret = recvmsg(fd, &msg, 0);
	अगर (ret == -1)
		error(1, त्रुटि_सं, "recv");
	अगर (msg.msg_flags & (MSG_TRUNC | MSG_CTRUNC))
		error(1, 0, "recv: truncated");
	अगर (ret != माप(cfg_data))
		error(1, 0, "recv: length mismatch");
	अगर (स_भेद(data, cfg_data, माप(data)))
		error(1, 0, "recv: data mismatch");

	cm = CMSG_FIRSTHDR(&msg);
	अगर (with_flowlabel) अणु
		अगर (!cm)
			error(1, 0, "recv: missing cmsg");
		अगर (CMSG_NXTHDR(&msg, cm))
			error(1, 0, "recv: too many cmsg");
		अगर (cm->cmsg_level != SOL_IPV6 ||
		    cm->cmsg_type != IPV6_FLOWINFO)
			error(1, 0, "recv: unexpected cmsg level or type");

		flowlabel = ntohl(*(uपूर्णांक32_t *)CMSG_DATA(cm));
		ख_लिखो(मानक_त्रुटि, "recv with label %u\n", flowlabel);

		अगर (expect != FLOWLABEL_WILDCARD && expect != flowlabel)
			ख_लिखो(मानक_त्रुटि, "recv: incorrect flowlabel %u != %u\n",
					flowlabel, expect);

	पूर्ण अन्यथा अणु
		ख_लिखो(मानक_त्रुटि, "recv without label\n");
	पूर्ण
पूर्ण

अटल bool get_स्वतःflowlabel_enabled(व्योम)
अणु
	पूर्णांक fd, ret;
	अक्षर val;

	fd = खोलो("/proc/sys/net/ipv6/auto_flowlabels", O_RDONLY);
	अगर (fd == -1)
		error(1, त्रुटि_सं, "open sysctl");

	ret = पढ़ो(fd, &val, 1);
	अगर (ret == -1)
		error(1, त्रुटि_सं, "read sysctl");
	अगर (ret == 0)
		error(1, 0, "read sysctl: 0");

	अगर (बंद(fd))
		error(1, त्रुटि_सं, "close sysctl");

	वापस val == '1';
पूर्ण

अटल व्योम flowlabel_get(पूर्णांक fd, uपूर्णांक32_t label, uपूर्णांक8_t share, uपूर्णांक16_t flags)
अणु
	काष्ठा in6_flowlabel_req req = अणु
		.flr_action = IPV6_FL_A_GET,
		.flr_label = htonl(label),
		.flr_flags = flags,
		.flr_share = share,
	पूर्ण;

	/* करो not pass IPV6_ADDR_ANY or IPV6_ADDR_MAPPED */
	req.flr_dst.s6_addr[0] = 0xfd;
	req.flr_dst.s6_addr[15] = 0x1;

	अगर (setsockopt(fd, SOL_IPV6, IPV6_FLOWLABEL_MGR, &req, माप(req)))
		error(1, त्रुटि_सं, "setsockopt flowlabel get");
पूर्ण

अटल व्योम parse_opts(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक c;

	जबतक ((c = getopt(argc, argv, "l:")) != -1) अणु
		चयन (c) अणु
		हाल 'l':
			cfg_label = म_से_अदीर्घ(optarg, शून्य, 0);
			अवरोध;
		शेष:
			error(1, 0, "%s: parse error", argv[0]);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा sockaddr_in6 addr = अणु
		.sin6_family = AF_INET6,
		.sin6_port = htons(8000),
		.sin6_addr = IN6ADDR_LOOPBACK_INIT,
	पूर्ण;
	स्थिर पूर्णांक one = 1;
	पूर्णांक fdt, fdr;

	parse_opts(argc, argv);

	fdt = socket(PF_INET6, SOCK_DGRAM, 0);
	अगर (fdt == -1)
		error(1, त्रुटि_सं, "socket t");

	fdr = socket(PF_INET6, SOCK_DGRAM, 0);
	अगर (fdr == -1)
		error(1, त्रुटि_सं, "socket r");

	अगर (connect(fdt, (व्योम *)&addr, माप(addr)))
		error(1, त्रुटि_सं, "connect");
	अगर (bind(fdr, (व्योम *)&addr, माप(addr)))
		error(1, त्रुटि_सं, "bind");

	flowlabel_get(fdt, cfg_label, IPV6_FL_S_EXCL, IPV6_FL_F_CREATE);

	अगर (setsockopt(fdr, SOL_IPV6, IPV6_FLOWINFO, &one, माप(one)))
		error(1, त्रुटि_सं, "setsockopt flowinfo");

	अगर (get_स्वतःflowlabel_enabled()) अणु
		ख_लिखो(मानक_त्रुटि, "send no label: recv auto flowlabel\n");
		करो_send(fdt, false, 0);
		करो_recv(fdr, true, FLOWLABEL_WILDCARD);
	पूर्ण अन्यथा अणु
		ख_लिखो(मानक_त्रुटि, "send no label: recv no label (auto off)\n");
		करो_send(fdt, false, 0);
		करो_recv(fdr, false, 0);
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "send label\n");
	करो_send(fdt, true, cfg_label);
	करो_recv(fdr, true, cfg_label);

	अगर (बंद(fdr))
		error(1, त्रुटि_सं, "close r");
	अगर (बंद(fdt))
		error(1, त्रुटि_सं, "close t");

	वापस 0;
पूर्ण
