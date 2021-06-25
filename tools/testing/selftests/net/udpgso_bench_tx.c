<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा _GNU_SOURCE

#समावेश <arpa/inet.h>
#समावेश <त्रुटिसं.स>
#समावेश <error.h>
#समावेश <linux/errqueue.h>
#समावेश <linux/net_tstamp.h>
#समावेश <netinet/अगर_ether.h>
#समावेश <netinet/in.h>
#समावेश <netinet/ip.h>
#समावेश <netinet/ip6.h>
#समावेश <netinet/udp.h>
#समावेश <poll.h>
#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/socket.h>
#समावेश <sys/समय.स>
#समावेश <sys/poll.h>
#समावेश <sys/types.h>
#समावेश <unistd.h>

#समावेश "../kselftest.h"

#अगर_अघोषित ETH_MAX_MTU
#घोषणा ETH_MAX_MTU 0xFFFFU
#पूर्ण_अगर

#अगर_अघोषित UDP_SEGMENT
#घोषणा UDP_SEGMENT		103
#पूर्ण_अगर

#अगर_अघोषित SO_ZEROCOPY
#घोषणा SO_ZEROCOPY	60
#पूर्ण_अगर

#अगर_अघोषित SO_EE_ORIGIN_ZEROCOPY
#घोषणा SO_EE_ORIGIN_ZEROCOPY 5
#पूर्ण_अगर

#अगर_अघोषित MSG_ZEROCOPY
#घोषणा MSG_ZEROCOPY	0x4000000
#पूर्ण_अगर

#अगर_अघोषित ENOTSUPP
#घोषणा ENOTSUPP	524
#पूर्ण_अगर

#घोषणा NUM_PKT		100

अटल bool	cfg_cache_trash;
अटल पूर्णांक	cfg_cpu		= -1;
अटल पूर्णांक	cfg_connected	= true;
अटल पूर्णांक	cfg_family	= PF_UNSPEC;
अटल uपूर्णांक16_t	cfg_mss;
अटल पूर्णांक	cfg_payload_len	= (1472 * 42);
अटल पूर्णांक	cfg_port	= 8000;
अटल पूर्णांक	cfg_runसमय_ms	= -1;
अटल bool	cfg_poll;
अटल bool	cfg_segment;
अटल bool	cfg_sendmmsg;
अटल bool	cfg_tcp;
अटल uपूर्णांक32_t	cfg_tx_ts = SOF_TIMESTAMPING_TX_SOFTWARE;
अटल bool	cfg_tx_tstamp;
अटल bool	cfg_audit;
अटल bool	cfg_verbose;
अटल bool	cfg_zerocopy;
अटल पूर्णांक	cfg_msg_nr;
अटल uपूर्णांक16_t	cfg_gso_size;
अटल अचिन्हित दीर्घ total_num_msgs;
अटल अचिन्हित दीर्घ total_num_sends;
अटल अचिन्हित दीर्घ stat_tx_ts;
अटल अचिन्हित दीर्घ stat_tx_ts_errors;
अटल अचिन्हित दीर्घ tstart;
अटल अचिन्हित दीर्घ tend;
अटल अचिन्हित दीर्घ stat_zcopies;

अटल socklen_t cfg_alen;
अटल काष्ठा sockaddr_storage cfg_dst_addr;

अटल bool पूर्णांकerrupted;
अटल अक्षर buf[NUM_PKT][ETH_MAX_MTU];

अटल व्योम sigपूर्णांक_handler(पूर्णांक signum)
अणु
	अगर (signum == संक_विघ्न)
		पूर्णांकerrupted = true;
पूर्ण

अटल अचिन्हित दीर्घ समय_लोofday_ms(व्योम)
अणु
	काष्ठा समयval tv;

	समय_लोofday(&tv, शून्य);
	वापस (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
पूर्ण

अटल पूर्णांक set_cpu(पूर्णांक cpu)
अणु
	cpu_set_t mask;

	CPU_ZERO(&mask);
	CPU_SET(cpu, &mask);
	अगर (sched_setaffinity(0, माप(mask), &mask))
		error(1, 0, "setaffinity %d", cpu);

	वापस 0;
पूर्ण

अटल व्योम setup_sockaddr(पूर्णांक करोमुख्य, स्थिर अक्षर *str_addr, व्योम *sockaddr)
अणु
	काष्ठा sockaddr_in6 *addr6 = (व्योम *) sockaddr;
	काष्ठा sockaddr_in *addr4 = (व्योम *) sockaddr;

	चयन (करोमुख्य) अणु
	हाल PF_INET:
		addr4->sin_family = AF_INET;
		addr4->sin_port = htons(cfg_port);
		अगर (inet_pton(AF_INET, str_addr, &(addr4->sin_addr)) != 1)
			error(1, 0, "ipv4 parse error: %s", str_addr);
		अवरोध;
	हाल PF_INET6:
		addr6->sin6_family = AF_INET6;
		addr6->sin6_port = htons(cfg_port);
		अगर (inet_pton(AF_INET6, str_addr, &(addr6->sin6_addr)) != 1)
			error(1, 0, "ipv6 parse error: %s", str_addr);
		अवरोध;
	शेष:
		error(1, 0, "illegal domain");
	पूर्ण
पूर्ण

अटल व्योम flush_cmsg(काष्ठा cmsghdr *cmsg)
अणु
	काष्ठा sock_extended_err *err;
	काष्ठा scm_बारtamping *tss;
	__u32 lo;
	__u32 hi;
	पूर्णांक i;

	चयन (cmsg->cmsg_level) अणु
	हाल SOL_SOCKET:
		अगर (cmsg->cmsg_type == SO_TIMESTAMPING) अणु
			i = (cfg_tx_ts == SOF_TIMESTAMPING_TX_HARDWARE) ? 2 : 0;
			tss = (काष्ठा scm_बारtamping *)CMSG_DATA(cmsg);
			अगर (tss->ts[i].tv_sec == 0)
				stat_tx_ts_errors++;
		पूर्ण अन्यथा अणु
			error(1, 0, "unknown SOL_SOCKET cmsg type=%u\n",
			      cmsg->cmsg_type);
		पूर्ण
		अवरोध;
	हाल SOL_IP:
	हाल SOL_IPV6:
		चयन (cmsg->cmsg_type) अणु
		हाल IP_RECVERR:
		हाल IPV6_RECVERR:
		अणु
			err = (काष्ठा sock_extended_err *)CMSG_DATA(cmsg);
			चयन (err->ee_origin) अणु
			हाल SO_EE_ORIGIN_TIMESTAMPING:
				/* Got a TX बारtamp from error queue */
				stat_tx_ts++;
				अवरोध;
			हाल SO_EE_ORIGIN_ICMP:
			हाल SO_EE_ORIGIN_ICMP6:
				अगर (cfg_verbose)
					ख_लिखो(मानक_त्रुटि,
						"received ICMP error: type=%u, code=%u\n",
						err->ee_type, err->ee_code);
				अवरोध;
			हाल SO_EE_ORIGIN_ZEROCOPY:
			अणु
				lo = err->ee_info;
				hi = err->ee_data;
				/* range of IDs acknowledged */
				stat_zcopies += hi - lo + 1;
				अवरोध;
			पूर्ण
			हाल SO_EE_ORIGIN_LOCAL:
				अगर (cfg_verbose)
					ख_लिखो(मानक_त्रुटि,
						"received packet with local origin: %u\n",
						err->ee_origin);
				अवरोध;
			शेष:
				error(0, 1, "received packet with origin: %u",
				      err->ee_origin);
			पूर्ण
			अवरोध;
		पूर्ण
		शेष:
			error(0, 1, "unknown IP msg type=%u\n",
			      cmsg->cmsg_type);
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		error(0, 1, "unknown cmsg level=%u\n",
		      cmsg->cmsg_level);
	पूर्ण
पूर्ण

अटल व्योम flush_errqueue_recv(पूर्णांक fd)
अणु
	अक्षर control[CMSG_SPACE(माप(काष्ठा scm_बारtamping)) +
		     CMSG_SPACE(माप(काष्ठा sock_extended_err)) +
		     CMSG_SPACE(माप(काष्ठा sockaddr_in6))] = अणु0पूर्ण;
	काष्ठा msghdr msg = अणु0पूर्ण;
	काष्ठा cmsghdr *cmsg;
	पूर्णांक ret;

	जबतक (1) अणु
		msg.msg_control = control;
		msg.msg_controllen = माप(control);
		ret = recvmsg(fd, &msg, MSG_ERRQUEUE);
		अगर (ret == -1 && त्रुटि_सं == EAGAIN)
			अवरोध;
		अगर (ret == -1)
			error(1, त्रुटि_सं, "errqueue");
		अगर (msg.msg_flags != MSG_ERRQUEUE)
			error(1, 0, "errqueue: flags 0x%x\n", msg.msg_flags);
		अगर (cfg_audit) अणु
			क्रम (cmsg = CMSG_FIRSTHDR(&msg);
					cmsg;
					cmsg = CMSG_NXTHDR(&msg, cmsg))
				flush_cmsg(cmsg);
		पूर्ण
		msg.msg_flags = 0;
	पूर्ण
पूर्ण

अटल व्योम flush_errqueue(पूर्णांक fd, स्थिर bool करो_poll)
अणु
	अगर (करो_poll) अणु
		काष्ठा pollfd fds = अणु0पूर्ण;
		पूर्णांक ret;

		fds.fd = fd;
		ret = poll(&fds, 1, 500);
		अगर (ret == 0) अणु
			अगर (cfg_verbose)
				ख_लिखो(मानक_त्रुटि, "poll timeout\n");
		पूर्ण अन्यथा अगर (ret < 0) अणु
			error(1, त्रुटि_सं, "poll");
		पूर्ण
	पूर्ण

	flush_errqueue_recv(fd);
पूर्ण

अटल पूर्णांक send_tcp(पूर्णांक fd, अक्षर *data)
अणु
	पूर्णांक ret, करोne = 0, count = 0;

	जबतक (करोne < cfg_payload_len) अणु
		ret = send(fd, data + करोne, cfg_payload_len - करोne,
			   cfg_zerocopy ? MSG_ZEROCOPY : 0);
		अगर (ret == -1)
			error(1, त्रुटि_सं, "write");

		करोne += ret;
		count++;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक send_udp(पूर्णांक fd, अक्षर *data)
अणु
	पूर्णांक ret, total_len, len, count = 0;

	total_len = cfg_payload_len;

	जबतक (total_len) अणु
		len = total_len < cfg_mss ? total_len : cfg_mss;

		ret = sendto(fd, data, len, cfg_zerocopy ? MSG_ZEROCOPY : 0,
			     cfg_connected ? शून्य : (व्योम *)&cfg_dst_addr,
			     cfg_connected ? 0 : cfg_alen);
		अगर (ret == -1)
			error(1, त्रुटि_सं, "write");
		अगर (ret != len)
			error(1, त्रुटि_सं, "write: %uB != %uB\n", ret, len);

		total_len -= len;
		count++;
	पूर्ण

	वापस count;
पूर्ण

अटल व्योम send_ts_cmsg(काष्ठा cmsghdr *cm)
अणु
	uपूर्णांक32_t *valp;

	cm->cmsg_level = SOL_SOCKET;
	cm->cmsg_type = SO_TIMESTAMPING;
	cm->cmsg_len = CMSG_LEN(माप(cfg_tx_ts));
	valp = (व्योम *)CMSG_DATA(cm);
	*valp = cfg_tx_ts;
पूर्ण

अटल पूर्णांक send_udp_sendmmsg(पूर्णांक fd, अक्षर *data)
अणु
	अक्षर control[CMSG_SPACE(माप(cfg_tx_ts))] = अणु0पूर्ण;
	स्थिर पूर्णांक max_nr_msg = ETH_MAX_MTU / ETH_DATA_LEN;
	काष्ठा mmsghdr mmsgs[max_nr_msg];
	काष्ठा iovec iov[max_nr_msg];
	अचिन्हित पूर्णांक off = 0, left;
	माप_प्रकार msg_controllen = 0;
	पूर्णांक i = 0, ret;

	स_रखो(mmsgs, 0, माप(mmsgs));

	अगर (cfg_tx_tstamp) अणु
		काष्ठा msghdr msg = अणु0पूर्ण;
		काष्ठा cmsghdr *cmsg;

		msg.msg_control = control;
		msg.msg_controllen = माप(control);
		cmsg = CMSG_FIRSTHDR(&msg);
		send_ts_cmsg(cmsg);
		msg_controllen += CMSG_SPACE(माप(cfg_tx_ts));
	पूर्ण

	left = cfg_payload_len;
	जबतक (left) अणु
		अगर (i == max_nr_msg)
			error(1, 0, "sendmmsg: exceeds max_nr_msg");

		iov[i].iov_base = data + off;
		iov[i].iov_len = cfg_mss < left ? cfg_mss : left;

		mmsgs[i].msg_hdr.msg_iov = iov + i;
		mmsgs[i].msg_hdr.msg_iovlen = 1;

		mmsgs[i].msg_hdr.msg_name = (व्योम *)&cfg_dst_addr;
		mmsgs[i].msg_hdr.msg_namelen = cfg_alen;
		अगर (msg_controllen) अणु
			mmsgs[i].msg_hdr.msg_control = control;
			mmsgs[i].msg_hdr.msg_controllen = msg_controllen;
		पूर्ण

		off += iov[i].iov_len;
		left -= iov[i].iov_len;
		i++;
	पूर्ण

	ret = sendmmsg(fd, mmsgs, i, cfg_zerocopy ? MSG_ZEROCOPY : 0);
	अगर (ret == -1)
		error(1, त्रुटि_सं, "sendmmsg");

	वापस ret;
पूर्ण

अटल व्योम send_udp_segment_cmsg(काष्ठा cmsghdr *cm)
अणु
	uपूर्णांक16_t *valp;

	cm->cmsg_level = SOL_UDP;
	cm->cmsg_type = UDP_SEGMENT;
	cm->cmsg_len = CMSG_LEN(माप(cfg_gso_size));
	valp = (व्योम *)CMSG_DATA(cm);
	*valp = cfg_gso_size;
पूर्ण

अटल पूर्णांक send_udp_segment(पूर्णांक fd, अक्षर *data)
अणु
	अक्षर control[CMSG_SPACE(माप(cfg_gso_size)) +
		     CMSG_SPACE(माप(cfg_tx_ts))] = अणु0पूर्ण;
	काष्ठा msghdr msg = अणु0पूर्ण;
	काष्ठा iovec iov = अणु0पूर्ण;
	माप_प्रकार msg_controllen;
	काष्ठा cmsghdr *cmsg;
	पूर्णांक ret;

	iov.iov_base = data;
	iov.iov_len = cfg_payload_len;

	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;

	msg.msg_control = control;
	msg.msg_controllen = माप(control);
	cmsg = CMSG_FIRSTHDR(&msg);
	send_udp_segment_cmsg(cmsg);
	msg_controllen = CMSG_SPACE(माप(cfg_mss));
	अगर (cfg_tx_tstamp) अणु
		cmsg = CMSG_NXTHDR(&msg, cmsg);
		send_ts_cmsg(cmsg);
		msg_controllen += CMSG_SPACE(माप(cfg_tx_ts));
	पूर्ण

	msg.msg_controllen = msg_controllen;
	msg.msg_name = (व्योम *)&cfg_dst_addr;
	msg.msg_namelen = cfg_alen;

	ret = sendmsg(fd, &msg, cfg_zerocopy ? MSG_ZEROCOPY : 0);
	अगर (ret == -1)
		error(1, त्रुटि_सं, "sendmsg");
	अगर (ret != iov.iov_len)
		error(1, 0, "sendmsg: %u != %llu\n", ret,
			(अचिन्हित दीर्घ दीर्घ)iov.iov_len);

	वापस 1;
पूर्ण

अटल व्योम usage(स्थिर अक्षर *filepath)
अणु
	error(1, 0, "Usage: %s [-46acmHPtTuvz] [-C cpu] [-D dst ip] [-l secs] [-M messagenr] [-p port] [-s sendsize] [-S gsosize]",
		    filepath);
पूर्ण

अटल व्योम parse_opts(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक max_len, hdrlen;
	पूर्णांक c;

	जबतक ((c = getopt(argc, argv, "46acC:D:Hl:mM:p:s:PS:tTuvz")) != -1) अणु
		चयन (c) अणु
		हाल '4':
			अगर (cfg_family != PF_UNSPEC)
				error(1, 0, "Pass one of -4 or -6");
			cfg_family = PF_INET;
			cfg_alen = माप(काष्ठा sockaddr_in);
			अवरोध;
		हाल '6':
			अगर (cfg_family != PF_UNSPEC)
				error(1, 0, "Pass one of -4 or -6");
			cfg_family = PF_INET6;
			cfg_alen = माप(काष्ठा sockaddr_in6);
			अवरोध;
		हाल 'a':
			cfg_audit = true;
			अवरोध;
		हाल 'c':
			cfg_cache_trash = true;
			अवरोध;
		हाल 'C':
			cfg_cpu = म_से_दीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'D':
			setup_sockaddr(cfg_family, optarg, &cfg_dst_addr);
			अवरोध;
		हाल 'l':
			cfg_runसमय_ms = म_से_अदीर्घ(optarg, शून्य, 10) * 1000;
			अवरोध;
		हाल 'm':
			cfg_sendmmsg = true;
			अवरोध;
		हाल 'M':
			cfg_msg_nr = म_से_अदीर्घ(optarg, शून्य, 10);
			अवरोध;
		हाल 'p':
			cfg_port = म_से_अदीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'P':
			cfg_poll = true;
			अवरोध;
		हाल 's':
			cfg_payload_len = म_से_अदीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'S':
			cfg_gso_size = म_से_अदीर्घ(optarg, शून्य, 0);
			cfg_segment = true;
			अवरोध;
		हाल 'H':
			cfg_tx_ts = SOF_TIMESTAMPING_TX_HARDWARE;
			cfg_tx_tstamp = true;
			अवरोध;
		हाल 't':
			cfg_tcp = true;
			अवरोध;
		हाल 'T':
			cfg_tx_tstamp = true;
			अवरोध;
		हाल 'u':
			cfg_connected = false;
			अवरोध;
		हाल 'v':
			cfg_verbose = true;
			अवरोध;
		हाल 'z':
			cfg_zerocopy = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (optind != argc)
		usage(argv[0]);

	अगर (cfg_family == PF_UNSPEC)
		error(1, 0, "must pass one of -4 or -6");
	अगर (cfg_tcp && !cfg_connected)
		error(1, 0, "connectionless tcp makes no sense");
	अगर (cfg_segment && cfg_sendmmsg)
		error(1, 0, "cannot combine segment offload and sendmmsg");
	अगर (cfg_tx_tstamp && !(cfg_segment || cfg_sendmmsg))
		error(1, 0, "Options -T and -H require either -S or -m option");

	अगर (cfg_family == PF_INET)
		hdrlen = माप(काष्ठा iphdr) + माप(काष्ठा udphdr);
	अन्यथा
		hdrlen = माप(काष्ठा ip6_hdr) + माप(काष्ठा udphdr);

	cfg_mss = ETH_DATA_LEN - hdrlen;
	max_len = ETH_MAX_MTU - hdrlen;
	अगर (!cfg_gso_size)
		cfg_gso_size = cfg_mss;

	अगर (cfg_payload_len > max_len)
		error(1, 0, "payload length %u exceeds max %u",
		      cfg_payload_len, max_len);
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

अटल व्योम set_tx_बारtamping(पूर्णांक fd)
अणु
	पूर्णांक val = SOF_TIMESTAMPING_OPT_CMSG | SOF_TIMESTAMPING_OPT_ID |
			SOF_TIMESTAMPING_OPT_TSONLY;

	अगर (cfg_tx_ts == SOF_TIMESTAMPING_TX_SOFTWARE)
		val |= SOF_TIMESTAMPING_SOFTWARE;
	अन्यथा
		val |= SOF_TIMESTAMPING_RAW_HARDWARE;

	अगर (setsockopt(fd, SOL_SOCKET, SO_TIMESTAMPING, &val, माप(val)))
		error(1, त्रुटि_सं, "setsockopt tx timestamping");
पूर्ण

अटल व्योम prपूर्णांक_audit_report(अचिन्हित दीर्घ num_msgs, अचिन्हित दीर्घ num_sends)
अणु
	अचिन्हित दीर्घ tdelta;

	tdelta = tend - tstart;
	अगर (!tdelta)
		वापस;

	ख_लिखो(मानक_त्रुटि, "Summary over %lu.%03lu seconds...\n",
			tdelta / 1000, tdelta % 1000);
	ख_लिखो(मानक_त्रुटि,
		"sum %s tx: %6lu MB/s %10lu calls (%lu/s) %10lu msgs (%lu/s)\n",
		cfg_tcp ? "tcp" : "udp",
		((num_msgs * cfg_payload_len) >> 10) / tdelta,
		num_sends, num_sends * 1000 / tdelta,
		num_msgs, num_msgs * 1000 / tdelta);

	अगर (cfg_tx_tstamp) अणु
		अगर (stat_tx_ts_errors)
			error(1, 0,
			      "Expected clean TX Timestamps: %9lu msgs received %6lu errors",
			      stat_tx_ts, stat_tx_ts_errors);
		अगर (stat_tx_ts != num_sends)
			error(1, 0,
			      "Unexpected number of TX Timestamps: %9lu expected %9lu received",
			      num_sends, stat_tx_ts);
		ख_लिखो(मानक_त्रुटि,
			"Tx Timestamps: %19lu received %17lu errors\n",
			stat_tx_ts, stat_tx_ts_errors);
	पूर्ण

	अगर (cfg_zerocopy) अणु
		अगर (stat_zcopies != num_sends)
			error(1, 0, "Unexpected number of Zerocopy completions: %9lu expected %9lu received",
			      num_sends, stat_zcopies);
		ख_लिखो(मानक_त्रुटि,
			"Zerocopy acks: %19lu\n",
			stat_zcopies);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_report(अचिन्हित दीर्घ num_msgs, अचिन्हित दीर्घ num_sends)
अणु
	ख_लिखो(मानक_त्रुटि,
		"%s tx: %6lu MB/s %8lu calls/s %6lu msg/s\n",
		cfg_tcp ? "tcp" : "udp",
		(num_msgs * cfg_payload_len) >> 20,
		num_sends, num_msgs);

	अगर (cfg_audit) अणु
		total_num_msgs += num_msgs;
		total_num_sends += num_sends;
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अचिन्हित दीर्घ num_msgs, num_sends;
	अचिन्हित दीर्घ tnow, treport, tstop;
	पूर्णांक fd, i, val, ret;

	parse_opts(argc, argv);

	अगर (cfg_cpu > 0)
		set_cpu(cfg_cpu);

	क्रम (i = 0; i < माप(buf[0]); i++)
		buf[0][i] = 'a' + (i % 26);
	क्रम (i = 1; i < NUM_PKT; i++)
		स_नकल(buf[i], buf[0], माप(buf[0]));

	संकेत(संक_विघ्न, sigपूर्णांक_handler);

	fd = socket(cfg_family, cfg_tcp ? SOCK_STREAM : SOCK_DGRAM, 0);
	अगर (fd == -1)
		error(1, त्रुटि_सं, "socket");

	अगर (cfg_zerocopy) अणु
		val = 1;

		ret = setsockopt(fd, SOL_SOCKET, SO_ZEROCOPY,
				 &val, माप(val));
		अगर (ret) अणु
			अगर (त्रुटि_सं == ENOPROTOOPT || त्रुटि_सं == ENOTSUPP) अणु
				ख_लिखो(मानक_त्रुटि, "SO_ZEROCOPY not supported");
				निकास(KSFT_SKIP);
			पूर्ण
			error(1, त्रुटि_सं, "setsockopt zerocopy");
		पूर्ण
	पूर्ण

	अगर (cfg_connected &&
	    connect(fd, (व्योम *)&cfg_dst_addr, cfg_alen))
		error(1, त्रुटि_सं, "connect");

	अगर (cfg_segment)
		set_pmtu_discover(fd, cfg_family == PF_INET);

	अगर (cfg_tx_tstamp)
		set_tx_बारtamping(fd);

	num_msgs = num_sends = 0;
	tnow = समय_लोofday_ms();
	tstart = tnow;
	tend = tnow;
	tstop = tnow + cfg_runसमय_ms;
	treport = tnow + 1000;

	i = 0;
	करो अणु
		अगर (cfg_tcp)
			num_sends += send_tcp(fd, buf[i]);
		अन्यथा अगर (cfg_segment)
			num_sends += send_udp_segment(fd, buf[i]);
		अन्यथा अगर (cfg_sendmmsg)
			num_sends += send_udp_sendmmsg(fd, buf[i]);
		अन्यथा
			num_sends += send_udp(fd, buf[i]);
		num_msgs++;
		अगर ((cfg_zerocopy && ((num_msgs & 0xF) == 0)) || cfg_tx_tstamp)
			flush_errqueue(fd, cfg_poll);

		अगर (cfg_msg_nr && num_msgs >= cfg_msg_nr)
			अवरोध;

		tnow = समय_लोofday_ms();
		अगर (tnow >= treport) अणु
			prपूर्णांक_report(num_msgs, num_sends);
			num_msgs = num_sends = 0;
			treport = tnow + 1000;
		पूर्ण

		/* cold cache when writing buffer */
		अगर (cfg_cache_trash)
			i = ++i < NUM_PKT ? i : 0;

	पूर्ण जबतक (!पूर्णांकerrupted && (cfg_runसमय_ms == -1 || tnow < tstop));

	अगर (cfg_zerocopy || cfg_tx_tstamp)
		flush_errqueue(fd, true);

	अगर (बंद(fd))
		error(1, त्रुटि_सं, "close");

	अगर (cfg_audit) अणु
		tend = tnow;
		total_num_msgs += num_msgs;
		total_num_sends += num_sends;
		prपूर्णांक_audit_report(total_num_msgs, total_num_sends);
	पूर्ण

	वापस 0;
पूर्ण
