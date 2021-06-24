<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test the SO_TXTIME API
 *
 * Takes a stream of अणु payload, delivery समय पूर्ण[], to be sent across two
 * processes. Start this program on two separate network namespaces or
 * connected hosts, one instance in transmit mode and the other in receive
 * mode using the '-r' option. Receiver will compare arrival बारtamps to
 * the expected stream. Sender will पढ़ो transmit बारtamps from the error
 * queue. The streams can dअगरfer due to out-of-order delivery and drops.
 */

#घोषणा _GNU_SOURCE

#समावेश <arpa/inet.h>
#समावेश <error.h>
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/errqueue.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/udp.h>
#समावेश <stdbool.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <sys/socket.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश <समय.स>
#समावेश <unistd.h>
#समावेश <poll.h>

अटल पूर्णांक	cfg_घड़ीid	= CLOCK_TAI;
अटल uपूर्णांक16_t	cfg_port	= 8000;
अटल पूर्णांक	cfg_variance_us	= 4000;
अटल uपूर्णांक64_t	cfg_start_समय_ns;
अटल पूर्णांक	cfg_mark;
अटल bool	cfg_rx;

अटल uपूर्णांक64_t glob_tstart;
अटल uपूर्णांक64_t tdeliver_max;

/* encode one समयd transmission (of a 1B payload) */
काष्ठा समयd_send अणु
	अक्षर	data;
	पूर्णांक64_t	delay_us;
पूर्ण;

#घोषणा MAX_NUM_PKT	8
अटल काष्ठा समयd_send cfg_buf[MAX_NUM_PKT];
अटल पूर्णांक cfg_num_pkt;

अटल पूर्णांक cfg_errq_level;
अटल पूर्णांक cfg_errq_type;

अटल काष्ठा sockaddr_storage cfg_dst_addr;
अटल काष्ठा sockaddr_storage cfg_src_addr;
अटल socklen_t cfg_alen;

अटल uपूर्णांक64_t समय_लो_ns(घड़ीid_t घड़ी)
अणु
	काष्ठा बारpec ts;

	अगर (घड़ी_समय_लो(घड़ी, &ts))
		error(1, त्रुटि_सं, "gettime");

	वापस ts.tv_sec * (1000ULL * 1000 * 1000) + ts.tv_nsec;
पूर्ण

अटल व्योम करो_send_one(पूर्णांक fdt, काष्ठा समयd_send *ts)
अणु
	अक्षर control[CMSG_SPACE(माप(uपूर्णांक64_t))];
	काष्ठा msghdr msg = अणु0पूर्ण;
	काष्ठा iovec iov = अणु0पूर्ण;
	काष्ठा cmsghdr *cm;
	uपूर्णांक64_t tdeliver;
	पूर्णांक ret;

	iov.iov_base = &ts->data;
	iov.iov_len = 1;

	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_name = (काष्ठा sockaddr *)&cfg_dst_addr;
	msg.msg_namelen = cfg_alen;

	अगर (ts->delay_us >= 0) अणु
		स_रखो(control, 0, माप(control));
		msg.msg_control = &control;
		msg.msg_controllen = माप(control);

		tdeliver = glob_tstart + ts->delay_us * 1000;
		tdeliver_max = tdeliver_max > tdeliver ?
			       tdeliver_max : tdeliver;

		cm = CMSG_FIRSTHDR(&msg);
		cm->cmsg_level = SOL_SOCKET;
		cm->cmsg_type = SCM_TXTIME;
		cm->cmsg_len = CMSG_LEN(माप(tdeliver));
		स_नकल(CMSG_DATA(cm), &tdeliver, माप(tdeliver));
	पूर्ण

	ret = sendmsg(fdt, &msg, 0);
	अगर (ret == -1)
		error(1, त्रुटि_सं, "write");
	अगर (ret == 0)
		error(1, 0, "write: 0B");

पूर्ण

अटल व्योम करो_recv_one(पूर्णांक fdr, काष्ठा समयd_send *ts)
अणु
	पूर्णांक64_t tstop, texpect;
	अक्षर rbuf[2];
	पूर्णांक ret;

	ret = recv(fdr, rbuf, माप(rbuf), 0);
	अगर (ret == -1 && त्रुटि_सं == EAGAIN)
		error(1, EAGAIN, "recv: timeout");
	अगर (ret == -1)
		error(1, त्रुटि_सं, "read");
	अगर (ret != 1)
		error(1, 0, "read: %dB", ret);

	tstop = (समय_लो_ns(cfg_घड़ीid) - glob_tstart) / 1000;
	texpect = ts->delay_us >= 0 ? ts->delay_us : 0;

	ख_लिखो(मानक_त्रुटि, "payload:%c delay:%lld expected:%lld (us)\n",
			rbuf[0], (दीर्घ दीर्घ)tstop, (दीर्घ दीर्घ)texpect);

	अगर (rbuf[0] != ts->data)
		error(1, 0, "payload mismatch. expected %c", ts->data);

	अगर (lद_असल(tstop - texpect) > cfg_variance_us)
		error(1, 0, "exceeds variance (%d us)", cfg_variance_us);
पूर्ण

अटल व्योम करो_recv_verअगरy_empty(पूर्णांक fdr)
अणु
	अक्षर rbuf[1];
	पूर्णांक ret;

	ret = recv(fdr, rbuf, माप(rbuf), 0);
	अगर (ret != -1 || त्रुटि_सं != EAGAIN)
		error(1, 0, "recv: not empty as expected (%d, %d)", ret, त्रुटि_सं);
पूर्ण

अटल पूर्णांक करो_recv_errqueue_समयout(पूर्णांक fdt)
अणु
	अक्षर control[CMSG_SPACE(माप(काष्ठा sock_extended_err)) +
		     CMSG_SPACE(माप(काष्ठा sockaddr_in6))] = अणु0पूर्ण;
	अक्षर data[माप(काष्ठा ethhdr) + माप(काष्ठा ipv6hdr) +
		  माप(काष्ठा udphdr) + 1];
	काष्ठा sock_extended_err *err;
	पूर्णांक ret, num_tstamp = 0;
	काष्ठा msghdr msg = अणु0पूर्ण;
	काष्ठा iovec iov = अणु0पूर्ण;
	काष्ठा cmsghdr *cm;
	पूर्णांक64_t tstamp = 0;

	iov.iov_base = data;
	iov.iov_len = माप(data);

	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;

	msg.msg_control = control;
	msg.msg_controllen = माप(control);

	जबतक (1) अणु
		स्थिर अक्षर *reason;

		ret = recvmsg(fdt, &msg, MSG_ERRQUEUE);
		अगर (ret == -1 && त्रुटि_सं == EAGAIN)
			अवरोध;
		अगर (ret == -1)
			error(1, त्रुटि_सं, "errqueue");
		अगर (msg.msg_flags != MSG_ERRQUEUE)
			error(1, 0, "errqueue: flags 0x%x\n", msg.msg_flags);

		cm = CMSG_FIRSTHDR(&msg);
		अगर (cm->cmsg_level != cfg_errq_level ||
		    cm->cmsg_type != cfg_errq_type)
			error(1, 0, "errqueue: type 0x%x.0x%x\n",
				    cm->cmsg_level, cm->cmsg_type);

		err = (काष्ठा sock_extended_err *)CMSG_DATA(cm);
		अगर (err->ee_origin != SO_EE_ORIGIN_TXTIME)
			error(1, 0, "errqueue: origin 0x%x\n", err->ee_origin);

		चयन (err->ee_त्रुटि_सं) अणु
		हाल ECANCELED:
			अगर (err->ee_code != SO_EE_CODE_TXTIME_MISSED)
				error(1, 0, "errqueue: unknown ECANCELED %u\n",
				      err->ee_code);
			reason = "missed txtime";
		अवरोध;
		हाल EINVAL:
			अगर (err->ee_code != SO_EE_CODE_TXTIME_INVALID_PARAM)
				error(1, 0, "errqueue: unknown EINVAL %u\n",
				      err->ee_code);
			reason = "invalid txtime";
		अवरोध;
		शेष:
			error(1, 0, "errqueue: errno %u code %u\n",
			      err->ee_त्रुटि_सं, err->ee_code);
		पूर्ण

		tstamp = ((पूर्णांक64_t) err->ee_data) << 32 | err->ee_info;
		tstamp -= (पूर्णांक64_t) glob_tstart;
		tstamp /= 1000 * 1000;
		ख_लिखो(मानक_त्रुटि, "send: pkt %c at %" PRId64 "ms dropped: %s\n",
			data[ret - 1], tstamp, reason);

		msg.msg_flags = 0;
		msg.msg_controllen = माप(control);
		num_tstamp++;
	पूर्ण

	वापस num_tstamp;
पूर्ण

अटल व्योम recv_errqueue_msgs(पूर्णांक fdt)
अणु
	काष्ठा pollfd pfd = अणु .fd = fdt, .events = POLLERR पूर्ण;
	स्थिर पूर्णांक समयout_ms = 10;
	पूर्णांक ret, num_tstamp = 0;

	करो अणु
		ret = poll(&pfd, 1, समयout_ms);
		अगर (ret == -1)
			error(1, त्रुटि_सं, "poll");

		अगर (ret && (pfd.revents & POLLERR))
			num_tstamp += करो_recv_errqueue_समयout(fdt);

		अगर (num_tstamp == cfg_num_pkt)
			अवरोध;

	पूर्ण जबतक (समय_लो_ns(cfg_घड़ीid) < tdeliver_max);
पूर्ण

अटल व्योम start_समय_रुको(व्योम)
अणु
	uपूर्णांक64_t now;
	पूर्णांक err;

	अगर (!cfg_start_समय_ns)
		वापस;

	now = समय_लो_ns(CLOCK_REALTIME);
	अगर (cfg_start_समय_ns < now)
		वापस;

	err = usleep((cfg_start_समय_ns - now) / 1000);
	अगर (err)
		error(1, त्रुटि_सं, "usleep");
पूर्ण

अटल व्योम setsockopt_txसमय(पूर्णांक fd)
अणु
	काष्ठा sock_txसमय so_txसमय_val = अणु .घड़ीid = cfg_घड़ीid पूर्ण;
	काष्ठा sock_txसमय so_txसमय_val_पढ़ो = अणु 0 पूर्ण;
	socklen_t vallen = माप(so_txसमय_val);

	so_txसमय_val.flags = SOF_TXTIME_REPORT_ERRORS;

	अगर (setsockopt(fd, SOL_SOCKET, SO_TXTIME,
		       &so_txसमय_val, माप(so_txसमय_val)))
		error(1, त्रुटि_सं, "setsockopt txtime");

	अगर (माला_लोockopt(fd, SOL_SOCKET, SO_TXTIME,
		       &so_txसमय_val_पढ़ो, &vallen))
		error(1, त्रुटि_सं, "getsockopt txtime");

	अगर (vallen != माप(so_txसमय_val) ||
	    स_भेद(&so_txसमय_val, &so_txसमय_val_पढ़ो, vallen))
		error(1, 0, "getsockopt txtime: mismatch");
पूर्ण

अटल पूर्णांक setup_tx(काष्ठा sockaddr *addr, socklen_t alen)
अणु
	पूर्णांक fd;

	fd = socket(addr->sa_family, SOCK_DGRAM, 0);
	अगर (fd == -1)
		error(1, त्रुटि_सं, "socket t");

	अगर (connect(fd, addr, alen))
		error(1, त्रुटि_सं, "connect");

	setsockopt_txसमय(fd);

	अगर (cfg_mark &&
	    setsockopt(fd, SOL_SOCKET, SO_MARK, &cfg_mark, माप(cfg_mark)))
		error(1, त्रुटि_सं, "setsockopt mark");

	वापस fd;
पूर्ण

अटल पूर्णांक setup_rx(काष्ठा sockaddr *addr, socklen_t alen)
अणु
	काष्ठा समयval tv = अणु .tv_usec = 100 * 1000 पूर्ण;
	पूर्णांक fd;

	fd = socket(addr->sa_family, SOCK_DGRAM, 0);
	अगर (fd == -1)
		error(1, त्रुटि_सं, "socket r");

	अगर (bind(fd, addr, alen))
		error(1, त्रुटि_सं, "bind");

	अगर (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, माप(tv)))
		error(1, त्रुटि_सं, "setsockopt rcv timeout");

	वापस fd;
पूर्ण

अटल व्योम करो_test_tx(काष्ठा sockaddr *addr, socklen_t alen)
अणु
	पूर्णांक fdt, i;

	ख_लिखो(मानक_त्रुटि, "\nSO_TXTIME ipv%c clock %s\n",
			addr->sa_family == PF_INET ? '4' : '6',
			cfg_घड़ीid == CLOCK_TAI ? "tai" : "monotonic");

	fdt = setup_tx(addr, alen);

	start_समय_रुको();
	glob_tstart = समय_लो_ns(cfg_घड़ीid);

	क्रम (i = 0; i < cfg_num_pkt; i++)
		करो_send_one(fdt, &cfg_buf[i]);

	recv_errqueue_msgs(fdt);

	अगर (बंद(fdt))
		error(1, त्रुटि_सं, "close t");
पूर्ण

अटल व्योम करो_test_rx(काष्ठा sockaddr *addr, socklen_t alen)
अणु
	पूर्णांक fdr, i;

	fdr = setup_rx(addr, alen);

	start_समय_रुको();
	glob_tstart = समय_लो_ns(cfg_घड़ीid);

	क्रम (i = 0; i < cfg_num_pkt; i++)
		करो_recv_one(fdr, &cfg_buf[i]);

	करो_recv_verअगरy_empty(fdr);

	अगर (बंद(fdr))
		error(1, त्रुटि_सं, "close r");
पूर्ण

अटल व्योम setup_sockaddr(पूर्णांक करोमुख्य, स्थिर अक्षर *str_addr,
			   काष्ठा sockaddr_storage *sockaddr)
अणु
	काष्ठा sockaddr_in6 *addr6 = (व्योम *) sockaddr;
	काष्ठा sockaddr_in *addr4 = (व्योम *) sockaddr;

	चयन (करोमुख्य) अणु
	हाल PF_INET:
		स_रखो(addr4, 0, माप(*addr4));
		addr4->sin_family = AF_INET;
		addr4->sin_port = htons(cfg_port);
		अगर (str_addr &&
		    inet_pton(AF_INET, str_addr, &(addr4->sin_addr)) != 1)
			error(1, 0, "ipv4 parse error: %s", str_addr);
		अवरोध;
	हाल PF_INET6:
		स_रखो(addr6, 0, माप(*addr6));
		addr6->sin6_family = AF_INET6;
		addr6->sin6_port = htons(cfg_port);
		अगर (str_addr &&
		    inet_pton(AF_INET6, str_addr, &(addr6->sin6_addr)) != 1)
			error(1, 0, "ipv6 parse error: %s", str_addr);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक parse_io(स्थिर अक्षर *optarg, काष्ठा समयd_send *array)
अणु
	अक्षर *arg, *tok;
	पूर्णांक aoff = 0;

	arg = strdup(optarg);
	अगर (!arg)
		error(1, त्रुटि_सं, "strdup");

	जबतक ((tok = म_मोहर(arg, ","))) अणु
		arg = शून्य;	/* only pass non-zero on first call */

		अगर (aoff / 2 == MAX_NUM_PKT)
			error(1, 0, "exceeds max pkt count (%d)", MAX_NUM_PKT);

		अगर (aoff & 1) अणु	/* parse delay */
			array->delay_us = म_से_दीर्घ(tok, शून्य, 0) * 1000;
			array++;
		पूर्ण अन्यथा अणु	/* parse अक्षरacter */
			array->data = tok[0];
		पूर्ण

		aoff++;
	पूर्ण

	मुक्त(arg);

	वापस aoff / 2;
पूर्ण

अटल व्योम usage(स्थिर अक्षर *progname)
अणु
	ख_लिखो(मानक_त्रुटि, "\nUsage: %s [options] <payload>\n"
			"Options:\n"
			"  -4            only IPv4\n"
			"  -6            only IPv6\n"
			"  -c <clock>    monotonic (default) or tai\n"
			"  -D <addr>     destination IP address (server)\n"
			"  -S <addr>     source IP address (client)\n"
			"  -r            run rx mode\n"
			"  -t <nsec>     start time (UTC nanoseconds)\n"
			"  -m <mark>     socket mark\n"
			"\n",
			progname);
	निकास(1);
पूर्ण

अटल व्योम parse_opts(पूर्णांक argc, अक्षर **argv)
अणु
	अक्षर *daddr = शून्य, *saddr = शून्य;
	पूर्णांक करोमुख्य = PF_UNSPEC;
	पूर्णांक c;

	जबतक ((c = getopt(argc, argv, "46c:S:D:rt:m:")) != -1) अणु
		चयन (c) अणु
		हाल '4':
			अगर (करोमुख्य != PF_UNSPEC)
				error(1, 0, "Pass one of -4 or -6");
			करोमुख्य = PF_INET;
			cfg_alen = माप(काष्ठा sockaddr_in);
			cfg_errq_level = SOL_IP;
			cfg_errq_type = IP_RECVERR;
			अवरोध;
		हाल '6':
			अगर (करोमुख्य != PF_UNSPEC)
				error(1, 0, "Pass one of -4 or -6");
			करोमुख्य = PF_INET6;
			cfg_alen = माप(काष्ठा sockaddr_in6);
			cfg_errq_level = SOL_IPV6;
			cfg_errq_type = IPV6_RECVERR;
			अवरोध;
		हाल 'c':
			अगर (!म_भेद(optarg, "tai"))
				cfg_घड़ीid = CLOCK_TAI;
			अन्यथा अगर (!म_भेद(optarg, "monotonic") ||
				 !म_भेद(optarg, "mono"))
				cfg_घड़ीid = CLOCK_MONOTONIC;
			अन्यथा
				error(1, 0, "unknown clock id %s", optarg);
			अवरोध;
		हाल 'S':
			saddr = optarg;
			अवरोध;
		हाल 'D':
			daddr = optarg;
			अवरोध;
		हाल 'r':
			cfg_rx = true;
			अवरोध;
		हाल 't':
			cfg_start_समय_ns = म_से_दीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'm':
			cfg_mark = म_से_दीर्घ(optarg, शून्य, 0);
			अवरोध;
		शेष:
			usage(argv[0]);
		पूर्ण
	पूर्ण

	अगर (argc - optind != 1)
		usage(argv[0]);

	अगर (करोमुख्य == PF_UNSPEC)
		error(1, 0, "Pass one of -4 or -6");
	अगर (!daddr)
		error(1, 0, "-D <server addr> required\n");
	अगर (!cfg_rx && !saddr)
		error(1, 0, "-S <client addr> required\n");

	setup_sockaddr(करोमुख्य, daddr, &cfg_dst_addr);
	setup_sockaddr(करोमुख्य, saddr, &cfg_src_addr);

	cfg_num_pkt = parse_io(argv[optind], cfg_buf);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	parse_opts(argc, argv);

	अगर (cfg_rx)
		करो_test_rx((व्योम *)&cfg_dst_addr, cfg_alen);
	अन्यथा
		करो_test_tx((व्योम *)&cfg_src_addr, cfg_alen);

	वापस 0;
पूर्ण
