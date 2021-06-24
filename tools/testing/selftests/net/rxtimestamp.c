<शैली गुरु>
#समावेश <त्रुटिसं.स>
#समावेश <error.h>
#समावेश <getopt.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>

#समावेश <sys/समय.स>
#समावेश <sys/socket.h>
#समावेश <sys/select.h>
#समावेश <sys/ioctl.h>
#समावेश <arpa/inet.h>
#समावेश <net/अगर.h>

#समावेश <यंत्र/types.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/errqueue.h>

#घोषणा ARRAY_SIZE(arr) (माप(arr) / माप((arr)[0]))

काष्ठा options अणु
	पूर्णांक so_बारtamp;
	पूर्णांक so_बारtampns;
	पूर्णांक so_बारtamping;
पूर्ण;

काष्ठा tstamps अणु
	bool tstamp;
	bool tstampns;
	bool swtstamp;
	bool hwtstamp;
पूर्ण;

काष्ठा socket_type अणु
	अक्षर *मित्रly_name;
	पूर्णांक type;
	पूर्णांक protocol;
	bool enabled;
पूर्ण;

काष्ठा test_हाल अणु
	काष्ठा options sockopt;
	काष्ठा tstamps expected;
	bool enabled;
	bool warn_on_fail;
पूर्ण;

काष्ठा sof_flag अणु
	पूर्णांक mask;
	अक्षर *name;
पूर्ण;

अटल काष्ठा sof_flag sof_flags[] = अणु
#घोषणा SOF_FLAG(f) अणु f, #f पूर्ण
	SOF_FLAG(SOF_TIMESTAMPING_SOFTWARE),
	SOF_FLAG(SOF_TIMESTAMPING_RX_SOFTWARE),
	SOF_FLAG(SOF_TIMESTAMPING_RX_HARDWARE),
पूर्ण;

अटल काष्ठा socket_type socket_types[] = अणु
	अणु "ip",		SOCK_RAW,	IPPROTO_EGP पूर्ण,
	अणु "udp",	SOCK_DGRAM,	IPPROTO_UDP पूर्ण,
	अणु "tcp",	SOCK_STREAM,	IPPROTO_TCP पूर्ण,
पूर्ण;

अटल काष्ठा test_हाल test_हालs[] = अणु
	अणु अणुपूर्ण, अणुपूर्ण पूर्ण,
	अणु
		अणु .so_बारtamp = 1 पूर्ण,
		अणु .tstamp = true पूर्ण
	पूर्ण,
	अणु
		अणु .so_बारtampns = 1 पूर्ण,
		अणु .tstampns = true पूर्ण
	पूर्ण,
	अणु
		अणु .so_बारtamp = 1, .so_बारtampns = 1 पूर्ण,
		अणु .tstampns = true पूर्ण
	पूर्ण,
	अणु
		अणु .so_बारtamping = SOF_TIMESTAMPING_RX_SOFTWARE पूर्ण,
		अणुपूर्ण
	पूर्ण,
	अणु
		/* Loopback device करोes not support hw बारtamps. */
		अणु .so_बारtamping = SOF_TIMESTAMPING_RX_HARDWARE पूर्ण,
		अणुपूर्ण
	पूर्ण,
	अणु
		अणु .so_बारtamping = SOF_TIMESTAMPING_SOFTWARE पूर्ण,
		.warn_on_fail = true
	पूर्ण,
	अणु
		अणु .so_बारtamping = SOF_TIMESTAMPING_RX_SOFTWARE
			| SOF_TIMESTAMPING_RX_HARDWARE पूर्ण,
		अणुपूर्ण
	पूर्ण,
	अणु
		अणु .so_बारtamping = SOF_TIMESTAMPING_SOFTWARE
			| SOF_TIMESTAMPING_RX_SOFTWARE पूर्ण,
		अणु .swtstamp = true पूर्ण
	पूर्ण,
	अणु
		अणु .so_बारtamp = 1, .so_बारtamping = SOF_TIMESTAMPING_SOFTWARE
			| SOF_TIMESTAMPING_RX_SOFTWARE पूर्ण,
		अणु .tstamp = true, .swtstamp = true पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा option दीर्घ_options[] = अणु
	अणु "list_tests", no_argument, 0, 'l' पूर्ण,
	अणु "test_num", required_argument, 0, 'n' पूर्ण,
	अणु "op_size", required_argument, 0, 's' पूर्ण,
	अणु "tcp", no_argument, 0, 't' पूर्ण,
	अणु "udp", no_argument, 0, 'u' पूर्ण,
	अणु "ip", no_argument, 0, 'i' पूर्ण,
	अणु "strict", no_argument, 0, 'S' पूर्ण,
	अणु "ipv4", no_argument, 0, '4' पूर्ण,
	अणु "ipv6", no_argument, 0, '6' पूर्ण,
	अणु शून्य, 0, शून्य, 0 पूर्ण,
पूर्ण;

अटल पूर्णांक next_port = 19999;
अटल पूर्णांक op_size = 10 * 1024;

व्योम prपूर्णांक_test_हाल(काष्ठा test_हाल *t)
अणु
	पूर्णांक f = 0;

	म_लिखो("sockopts {");
	अगर (t->sockopt.so_बारtamp)
		म_लिखो(" SO_TIMESTAMP ");
	अगर (t->sockopt.so_बारtampns)
		म_लिखो(" SO_TIMESTAMPNS ");
	अगर (t->sockopt.so_बारtamping) अणु
		म_लिखो(" SO_TIMESTAMPING: {");
		क्रम (f = 0; f < ARRAY_SIZE(sof_flags); f++)
			अगर (t->sockopt.so_बारtamping & sof_flags[f].mask)
				म_लिखो(" %s |", sof_flags[f].name);
		म_लिखो("}");
	पूर्ण
	म_लिखो("} expected cmsgs: {");
	अगर (t->expected.tstamp)
		म_लिखो(" SCM_TIMESTAMP ");
	अगर (t->expected.tstampns)
		म_लिखो(" SCM_TIMESTAMPNS ");
	अगर (t->expected.swtstamp || t->expected.hwtstamp) अणु
		म_लिखो(" SCM_TIMESTAMPING {");
		अगर (t->expected.swtstamp)
			म_लिखो("0");
		अगर (t->expected.swtstamp && t->expected.hwtstamp)
			म_लिखो(",");
		अगर (t->expected.hwtstamp)
			म_लिखो("2");
		म_लिखो("}");
	पूर्ण
	म_लिखो("}\n");
पूर्ण

व्योम करो_send(पूर्णांक src)
अणु
	पूर्णांक r;
	अक्षर *buf = दो_स्मृति(op_size);

	स_रखो(buf, 'z', op_size);
	r = ग_लिखो(src, buf, op_size);
	अगर (r < 0)
		error(1, त्रुटि_सं, "Failed to sendmsg");

	मुक्त(buf);
पूर्ण

bool करो_recv(पूर्णांक rcv, पूर्णांक पढ़ो_size, काष्ठा tstamps expected)
अणु
	स्थिर पूर्णांक CMSG_SIZE = 1024;

	काष्ठा scm_बारtamping *ts;
	काष्ठा tstamps actual = अणुपूर्ण;
	अक्षर cmsg_buf[CMSG_SIZE];
	काष्ठा iovec recv_iov;
	काष्ठा cmsghdr *cmsg;
	bool failed = false;
	काष्ठा msghdr hdr;
	पूर्णांक flags = 0;
	पूर्णांक r;

	स_रखो(&hdr, 0, माप(hdr));
	hdr.msg_iov = &recv_iov;
	hdr.msg_iovlen = 1;
	recv_iov.iov_base = दो_स्मृति(पढ़ो_size);
	recv_iov.iov_len = पढ़ो_size;

	hdr.msg_control = cmsg_buf;
	hdr.msg_controllen = माप(cmsg_buf);

	r = recvmsg(rcv, &hdr, flags);
	अगर (r < 0)
		error(1, त्रुटि_सं, "Failed to recvmsg");
	अगर (r != पढ़ो_size)
		error(1, 0, "Only received %d bytes of payload.", r);

	अगर (hdr.msg_flags & (MSG_TRUNC | MSG_CTRUNC))
		error(1, 0, "Message was truncated.");

	क्रम (cmsg = CMSG_FIRSTHDR(&hdr); cmsg != शून्य;
	     cmsg = CMSG_NXTHDR(&hdr, cmsg)) अणु
		अगर (cmsg->cmsg_level != SOL_SOCKET)
			error(1, 0, "Unexpected cmsg_level %d",
			      cmsg->cmsg_level);
		चयन (cmsg->cmsg_type) अणु
		हाल SCM_TIMESTAMP:
			actual.tstamp = true;
			अवरोध;
		हाल SCM_TIMESTAMPNS:
			actual.tstampns = true;
			अवरोध;
		हाल SCM_TIMESTAMPING:
			ts = (काष्ठा scm_बारtamping *)CMSG_DATA(cmsg);
			actual.swtstamp = !!ts->ts[0].tv_sec;
			अगर (ts->ts[1].tv_sec != 0)
				error(0, 0, "ts[1] should not be set.");
			actual.hwtstamp = !!ts->ts[2].tv_sec;
			अवरोध;
		शेष:
			error(1, 0, "Unexpected cmsg_type %d", cmsg->cmsg_type);
		पूर्ण
	पूर्ण

#घोषणा VALIDATE(field) \
	करो अणु \
		अगर (expected.field != actual.field) अणु \
			अगर (expected.field) \
				error(0, 0, "Expected " #field " to be set."); \
			अन्यथा \
				error(0, 0, \
				      "Expected " #field " to not be set."); \
			failed = true; \
		पूर्ण \
	पूर्ण जबतक (0)

	VALIDATE(tstamp);
	VALIDATE(tstampns);
	VALIDATE(swtstamp);
	VALIDATE(hwtstamp);
#अघोषित VALIDATE

	मुक्त(recv_iov.iov_base);

	वापस failed;
पूर्ण

व्योम config_so_flags(पूर्णांक rcv, काष्ठा options o)
अणु
	पूर्णांक on = 1;

	अगर (setsockopt(rcv, SOL_SOCKET, SO_REUSEADDR, &on, माप(on)) < 0)
		error(1, त्रुटि_सं, "Failed to enable SO_REUSEADDR");

	अगर (o.so_बारtamp &&
	    setsockopt(rcv, SOL_SOCKET, SO_TIMESTAMP,
		       &o.so_बारtamp, माप(o.so_बारtamp)) < 0)
		error(1, त्रुटि_सं, "Failed to enable SO_TIMESTAMP");

	अगर (o.so_बारtampns &&
	    setsockopt(rcv, SOL_SOCKET, SO_TIMESTAMPNS,
		       &o.so_बारtampns, माप(o.so_बारtampns)) < 0)
		error(1, त्रुटि_सं, "Failed to enable SO_TIMESTAMPNS");

	अगर (o.so_बारtamping &&
	    setsockopt(rcv, SOL_SOCKET, SO_TIMESTAMPING,
		       &o.so_बारtamping, माप(o.so_बारtamping)) < 0)
		error(1, त्रुटि_सं, "Failed to set SO_TIMESTAMPING");
पूर्ण

bool run_test_हाल(काष्ठा socket_type *s, पूर्णांक test_num, अक्षर ip_version,
		   bool strict)
अणु
	जोड़ अणु
		काष्ठा sockaddr_in6 addr6;
		काष्ठा sockaddr_in addr4;
		काष्ठा sockaddr addr_un;
	पूर्ण addr;
	पूर्णांक पढ़ो_size = op_size;
	पूर्णांक src, dst, rcv, port;
	socklen_t addr_size;
	bool failed = false;

	port = (s->type == SOCK_RAW) ? 0 : next_port++;
	स_रखो(&addr, 0, माप(addr));
	अगर (ip_version == '4') अणु
		addr.addr4.sin_family = AF_INET;
		addr.addr4.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		addr.addr4.sin_port = htons(port);
		addr_size = माप(addr.addr4);
		अगर (s->type == SOCK_RAW)
			पढ़ो_size += 20;  /* क्रम IPv4 header */
	पूर्ण अन्यथा अणु
		addr.addr6.sin6_family = AF_INET6;
		addr.addr6.sin6_addr = in6addr_loopback;
		addr.addr6.sin6_port = htons(port);
		addr_size = माप(addr.addr6);
	पूर्ण
	म_लिखो("Starting testcase %d over ipv%c...\n", test_num, ip_version);
	src = socket(addr.addr_un.sa_family, s->type,
		     s->protocol);
	अगर (src < 0)
		error(1, त्रुटि_सं, "Failed to open src socket");

	dst = socket(addr.addr_un.sa_family, s->type,
		     s->protocol);
	अगर (dst < 0)
		error(1, त्रुटि_सं, "Failed to open dst socket");

	अगर (bind(dst, &addr.addr_un, addr_size) < 0)
		error(1, त्रुटि_सं, "Failed to bind to port %d", port);

	अगर (s->type == SOCK_STREAM && (listen(dst, 1) < 0))
		error(1, त्रुटि_सं, "Failed to listen");

	अगर (connect(src, &addr.addr_un, addr_size) < 0)
		error(1, त्रुटि_सं, "Failed to connect");

	अगर (s->type == SOCK_STREAM) अणु
		rcv = accept(dst, शून्य, शून्य);
		अगर (rcv < 0)
			error(1, त्रुटि_सं, "Failed to accept");
		बंद(dst);
	पूर्ण अन्यथा अणु
		rcv = dst;
	पूर्ण

	config_so_flags(rcv, test_हालs[test_num].sockopt);
	usleep(20000); /* setsockopt क्रम SO_TIMESTAMPING is asynchronous */
	करो_send(src);

	failed = करो_recv(rcv, पढ़ो_size, test_हालs[test_num].expected);

	बंद(rcv);
	बंद(src);

	अगर (failed) अणु
		म_लिखो("FAILURE in testcase %d over ipv%c ", test_num,
		       ip_version);
		prपूर्णांक_test_हाल(&test_हालs[test_num]);
		अगर (!strict && test_हालs[test_num].warn_on_fail)
			failed = false;
	पूर्ण
	वापस failed;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	bool all_protocols = true;
	bool all_tests = true;
	bool cfg_ipv4 = false;
	bool cfg_ipv6 = false;
	bool strict = false;
	पूर्णांक arg_index = 0;
	पूर्णांक failures = 0;
	पूर्णांक s, t, opt;

	जबतक ((opt = getopt_दीर्घ(argc, argv, "", दीर्घ_options,
				  &arg_index)) != -1) अणु
		चयन (opt) अणु
		हाल 'l':
			क्रम (t = 0; t < ARRAY_SIZE(test_हालs); t++) अणु
				म_लिखो("%d\t", t);
				prपूर्णांक_test_हाल(&test_हालs[t]);
			पूर्ण
			वापस 0;
		हाल 'n':
			t = म_से_प(optarg);
			अगर (t >= ARRAY_SIZE(test_हालs))
				error(1, 0, "Invalid test case: %d", t);
			all_tests = false;
			test_हालs[t].enabled = true;
			अवरोध;
		हाल 's':
			op_size = म_से_प(optarg);
			अवरोध;
		हाल 't':
			all_protocols = false;
			socket_types[2].enabled = true;
			अवरोध;
		हाल 'u':
			all_protocols = false;
			socket_types[1].enabled = true;
			अवरोध;
		हाल 'i':
			all_protocols = false;
			socket_types[0].enabled = true;
			अवरोध;
		हाल 'S':
			strict = true;
			अवरोध;
		हाल '4':
			cfg_ipv4 = true;
			अवरोध;
		हाल '6':
			cfg_ipv6 = true;
			अवरोध;
		शेष:
			error(1, 0, "Failed to parse parameters.");
		पूर्ण
	पूर्ण

	क्रम (s = 0; s < ARRAY_SIZE(socket_types); s++) अणु
		अगर (!all_protocols && !socket_types[s].enabled)
			जारी;

		म_लिखो("Testing %s...\n", socket_types[s].मित्रly_name);
		क्रम (t = 0; t < ARRAY_SIZE(test_हालs); t++) अणु
			अगर (!all_tests && !test_हालs[t].enabled)
				जारी;
			अगर (cfg_ipv4 || !cfg_ipv6)
				अगर (run_test_हाल(&socket_types[s], t, '4',
						  strict))
					failures++;
			अगर (cfg_ipv6 || !cfg_ipv4)
				अगर (run_test_हाल(&socket_types[s], t, '6',
						  strict))
					failures++;
		पूर्ण
	पूर्ण
	अगर (!failures)
		म_लिखो("PASSED.\n");
	वापस failures;
पूर्ण
