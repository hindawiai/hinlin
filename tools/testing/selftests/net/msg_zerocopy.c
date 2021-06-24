<शैली गुरु>
/* Evaluate MSG_ZEROCOPY
 *
 * Send traffic between two processes over one of the supported
 * protocols and modes:
 *
 * PF_INET/PF_INET6
 * - SOCK_STREAM
 * - SOCK_DGRAM
 * - SOCK_DGRAM with UDP_CORK
 * - SOCK_RAW
 * - SOCK_RAW with IP_HDRINCL
 *
 * PF_PACKET
 * - SOCK_DGRAM
 * - SOCK_RAW
 *
 * PF_RDS
 * - SOCK_SEQPACKET
 *
 * Start this program on two connected hosts, one in send mode and
 * the other with option '-r' to put it in receiver mode.
 *
 * If zerocopy mode ('-z') is enabled, the sender will verअगरy that
 * the kernel queues completions on the error queue क्रम all zerocopy
 * transfers.
 */

#घोषणा _GNU_SOURCE

#समावेश <arpa/inet.h>
#समावेश <error.h>
#समावेश <त्रुटिसं.स>
#समावेश <सीमा.स>
#समावेश <linux/errqueue.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <net/ethernet.h>
#समावेश <net/अगर.h>
#समावेश <netinet/ip.h>
#समावेश <netinet/ip6.h>
#समावेश <netinet/tcp.h>
#समावेश <netinet/udp.h>
#समावेश <poll.h>
#समावेश <sched.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/socket.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>
#समावेश <linux/rds.h>

#अगर_अघोषित SO_EE_ORIGIN_ZEROCOPY
#घोषणा SO_EE_ORIGIN_ZEROCOPY		5
#पूर्ण_अगर

#अगर_अघोषित SO_ZEROCOPY
#घोषणा SO_ZEROCOPY	60
#पूर्ण_अगर

#अगर_अघोषित SO_EE_CODE_ZEROCOPY_COPIED
#घोषणा SO_EE_CODE_ZEROCOPY_COPIED	1
#पूर्ण_अगर

#अगर_अघोषित MSG_ZEROCOPY
#घोषणा MSG_ZEROCOPY	0x4000000
#पूर्ण_अगर

अटल पूर्णांक  cfg_cork;
अटल bool cfg_cork_mixed;
अटल पूर्णांक  cfg_cpu		= -1;		/* शेष: pin to last cpu */
अटल पूर्णांक  cfg_family		= PF_UNSPEC;
अटल पूर्णांक  cfg_अगरindex		= 1;
अटल पूर्णांक  cfg_payload_len;
अटल पूर्णांक  cfg_port		= 8000;
अटल bool cfg_rx;
अटल पूर्णांक  cfg_runसमय_ms	= 4200;
अटल पूर्णांक  cfg_verbose;
अटल पूर्णांक  cfg_रुकोसमय_ms	= 500;
अटल bool cfg_zerocopy;

अटल socklen_t cfg_alen;
अटल काष्ठा sockaddr_storage cfg_dst_addr;
अटल काष्ठा sockaddr_storage cfg_src_addr;

अटल अक्षर payload[IP_MAXPACKET];
अटल दीर्घ packets, bytes, completions, expected_completions;
अटल पूर्णांक  zerocopied = -1;
अटल uपूर्णांक32_t next_completion;

अटल अचिन्हित दीर्घ समय_लोofday_ms(व्योम)
अणु
	काष्ठा समयval tv;

	समय_लोofday(&tv, शून्य);
	वापस (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
पूर्ण

अटल uपूर्णांक16_t get_ip_csum(स्थिर uपूर्णांक16_t *start, पूर्णांक num_words)
अणु
	अचिन्हित दीर्घ sum = 0;
	पूर्णांक i;

	क्रम (i = 0; i < num_words; i++)
		sum += start[i];

	जबतक (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);

	वापस ~sum;
पूर्ण

अटल पूर्णांक करो_setcpu(पूर्णांक cpu)
अणु
	cpu_set_t mask;

	CPU_ZERO(&mask);
	CPU_SET(cpu, &mask);
	अगर (sched_setaffinity(0, माप(mask), &mask))
		ख_लिखो(मानक_त्रुटि, "cpu: unable to pin, may increase variance.\n");
	अन्यथा अगर (cfg_verbose)
		ख_लिखो(मानक_त्रुटि, "cpu: %u\n", cpu);

	वापस 0;
पूर्ण

अटल व्योम करो_setsockopt(पूर्णांक fd, पूर्णांक level, पूर्णांक optname, पूर्णांक val)
अणु
	अगर (setsockopt(fd, level, optname, &val, माप(val)))
		error(1, त्रुटि_सं, "setsockopt %d.%d: %d", level, optname, val);
पूर्ण

अटल पूर्णांक करो_poll(पूर्णांक fd, पूर्णांक events)
अणु
	काष्ठा pollfd pfd;
	पूर्णांक ret;

	pfd.events = events;
	pfd.revents = 0;
	pfd.fd = fd;

	ret = poll(&pfd, 1, cfg_रुकोसमय_ms);
	अगर (ret == -1)
		error(1, त्रुटि_सं, "poll");

	वापस ret && (pfd.revents & events);
पूर्ण

अटल पूर्णांक करो_accept(पूर्णांक fd)
अणु
	पूर्णांक fda = fd;

	fd = accept(fda, शून्य, शून्य);
	अगर (fd == -1)
		error(1, त्रुटि_सं, "accept");
	अगर (बंद(fda))
		error(1, त्रुटि_सं, "close listen sock");

	वापस fd;
पूर्ण

अटल व्योम add_zcopy_cookie(काष्ठा msghdr *msg, uपूर्णांक32_t cookie)
अणु
	काष्ठा cmsghdr *cm;

	अगर (!msg->msg_control)
		error(1, त्रुटि_सं, "NULL cookie");
	cm = (व्योम *)msg->msg_control;
	cm->cmsg_len = CMSG_LEN(माप(cookie));
	cm->cmsg_level = SOL_RDS;
	cm->cmsg_type = RDS_CMSG_ZCOPY_COOKIE;
	स_नकल(CMSG_DATA(cm), &cookie, माप(cookie));
पूर्ण

अटल bool करो_sendmsg(पूर्णांक fd, काष्ठा msghdr *msg, bool करो_zerocopy, पूर्णांक करोमुख्य)
अणु
	पूर्णांक ret, len, i, flags;
	अटल uपूर्णांक32_t cookie;
	अक्षर ckbuf[CMSG_SPACE(माप(cookie))];

	len = 0;
	क्रम (i = 0; i < msg->msg_iovlen; i++)
		len += msg->msg_iov[i].iov_len;

	flags = MSG_DONTWAIT;
	अगर (करो_zerocopy) अणु
		flags |= MSG_ZEROCOPY;
		अगर (करोमुख्य == PF_RDS) अणु
			स_रखो(&msg->msg_control, 0, माप(msg->msg_control));
			msg->msg_controllen = CMSG_SPACE(माप(cookie));
			msg->msg_control = (काष्ठा cmsghdr *)ckbuf;
			add_zcopy_cookie(msg, ++cookie);
		पूर्ण
	पूर्ण

	ret = sendmsg(fd, msg, flags);
	अगर (ret == -1 && त्रुटि_सं == EAGAIN)
		वापस false;
	अगर (ret == -1)
		error(1, त्रुटि_सं, "send");
	अगर (cfg_verbose && ret != len)
		ख_लिखो(मानक_त्रुटि, "send: ret=%u != %u\n", ret, len);

	अगर (len) अणु
		packets++;
		bytes += ret;
		अगर (करो_zerocopy && ret)
			expected_completions++;
	पूर्ण
	अगर (करो_zerocopy && करोमुख्य == PF_RDS) अणु
		msg->msg_control = शून्य;
		msg->msg_controllen = 0;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम करो_sendmsg_corked(पूर्णांक fd, काष्ठा msghdr *msg)
अणु
	bool करो_zerocopy = cfg_zerocopy;
	पूर्णांक i, payload_len, extra_len;

	/* split up the packet. क्रम non-multiple, make first buffer दीर्घer */
	payload_len = cfg_payload_len / cfg_cork;
	extra_len = cfg_payload_len - (cfg_cork * payload_len);

	करो_setsockopt(fd, IPPROTO_UDP, UDP_CORK, 1);

	क्रम (i = 0; i < cfg_cork; i++) अणु

		/* in mixed-frags mode, alternate zerocopy and copy frags
		 * start with non-zerocopy, to ensure attach later works
		 */
		अगर (cfg_cork_mixed)
			करो_zerocopy = (i & 1);

		msg->msg_iov[0].iov_len = payload_len + extra_len;
		extra_len = 0;

		करो_sendmsg(fd, msg, करो_zerocopy,
			   (cfg_dst_addr.ss_family == AF_INET ?
			    PF_INET : PF_INET6));
	पूर्ण

	करो_setsockopt(fd, IPPROTO_UDP, UDP_CORK, 0);
पूर्ण

अटल पूर्णांक setup_iph(काष्ठा iphdr *iph, uपूर्णांक16_t payload_len)
अणु
	काष्ठा sockaddr_in *daddr = (व्योम *) &cfg_dst_addr;
	काष्ठा sockaddr_in *saddr = (व्योम *) &cfg_src_addr;

	स_रखो(iph, 0, माप(*iph));

	iph->version	= 4;
	iph->tos	= 0;
	iph->ihl	= 5;
	iph->ttl	= 2;
	iph->saddr	= saddr->sin_addr.s_addr;
	iph->daddr	= daddr->sin_addr.s_addr;
	iph->protocol	= IPPROTO_EGP;
	iph->tot_len	= htons(माप(*iph) + payload_len);
	iph->check	= get_ip_csum((व्योम *) iph, iph->ihl << 1);

	वापस माप(*iph);
पूर्ण

अटल पूर्णांक setup_ip6h(काष्ठा ipv6hdr *ip6h, uपूर्णांक16_t payload_len)
अणु
	काष्ठा sockaddr_in6 *daddr = (व्योम *) &cfg_dst_addr;
	काष्ठा sockaddr_in6 *saddr = (व्योम *) &cfg_src_addr;

	स_रखो(ip6h, 0, माप(*ip6h));

	ip6h->version		= 6;
	ip6h->payload_len	= htons(payload_len);
	ip6h->nexthdr		= IPPROTO_EGP;
	ip6h->hop_limit		= 2;
	ip6h->saddr		= saddr->sin6_addr;
	ip6h->daddr		= daddr->sin6_addr;

	वापस माप(*ip6h);
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
	शेष:
		error(1, 0, "illegal domain");
	पूर्ण
पूर्ण

अटल पूर्णांक करो_setup_tx(पूर्णांक करोमुख्य, पूर्णांक type, पूर्णांक protocol)
अणु
	पूर्णांक fd;

	fd = socket(करोमुख्य, type, protocol);
	अगर (fd == -1)
		error(1, त्रुटि_सं, "socket t");

	करो_setsockopt(fd, SOL_SOCKET, SO_SNDBUF, 1 << 21);
	अगर (cfg_zerocopy)
		करो_setsockopt(fd, SOL_SOCKET, SO_ZEROCOPY, 1);

	अगर (करोमुख्य != PF_PACKET && करोमुख्य != PF_RDS)
		अगर (connect(fd, (व्योम *) &cfg_dst_addr, cfg_alen))
			error(1, त्रुटि_सं, "connect");

	अगर (करोमुख्य == PF_RDS) अणु
		अगर (bind(fd, (व्योम *) &cfg_src_addr, cfg_alen))
			error(1, त्रुटि_सं, "bind");
	पूर्ण

	वापस fd;
पूर्ण

अटल uपूर्णांक32_t करो_process_zerocopy_cookies(काष्ठा rds_zcopy_cookies *ck)
अणु
	पूर्णांक i;

	अगर (ck->num > RDS_MAX_ZCOOKIES)
		error(1, 0, "Returned %d cookies, max expected %d\n",
		      ck->num, RDS_MAX_ZCOOKIES);
	क्रम (i = 0; i < ck->num; i++)
		अगर (cfg_verbose >= 2)
			ख_लिखो(मानक_त्रुटि, "%d\n", ck->cookies[i]);
	वापस ck->num;
पूर्ण

अटल bool करो_recvmsg_completion(पूर्णांक fd)
अणु
	अक्षर cmsgbuf[CMSG_SPACE(माप(काष्ठा rds_zcopy_cookies))];
	काष्ठा rds_zcopy_cookies *ck;
	काष्ठा cmsghdr *cmsg;
	काष्ठा msghdr msg;
	bool ret = false;

	स_रखो(&msg, 0, माप(msg));
	msg.msg_control = cmsgbuf;
	msg.msg_controllen = माप(cmsgbuf);

	अगर (recvmsg(fd, &msg, MSG_DONTWAIT))
		वापस ret;

	अगर (msg.msg_flags & MSG_CTRUNC)
		error(1, त्रुटि_सं, "recvmsg notification: truncated");

	क्रम (cmsg = CMSG_FIRSTHDR(&msg); cmsg; cmsg = CMSG_NXTHDR(&msg, cmsg)) अणु
		अगर (cmsg->cmsg_level == SOL_RDS &&
		    cmsg->cmsg_type == RDS_CMSG_ZCOPY_COMPLETION) अणु

			ck = (काष्ठा rds_zcopy_cookies *)CMSG_DATA(cmsg);
			completions += करो_process_zerocopy_cookies(ck);
			ret = true;
			अवरोध;
		पूर्ण
		error(0, 0, "ignoring cmsg at level %d type %d\n",
			    cmsg->cmsg_level, cmsg->cmsg_type);
	पूर्ण
	वापस ret;
पूर्ण

अटल bool करो_recv_completion(पूर्णांक fd, पूर्णांक करोमुख्य)
अणु
	काष्ठा sock_extended_err *serr;
	काष्ठा msghdr msg = अणुपूर्ण;
	काष्ठा cmsghdr *cm;
	uपूर्णांक32_t hi, lo, range;
	पूर्णांक ret, zerocopy;
	अक्षर control[100];

	अगर (करोमुख्य == PF_RDS)
		वापस करो_recvmsg_completion(fd);

	msg.msg_control = control;
	msg.msg_controllen = माप(control);

	ret = recvmsg(fd, &msg, MSG_ERRQUEUE);
	अगर (ret == -1 && त्रुटि_सं == EAGAIN)
		वापस false;
	अगर (ret == -1)
		error(1, त्रुटि_सं, "recvmsg notification");
	अगर (msg.msg_flags & MSG_CTRUNC)
		error(1, त्रुटि_सं, "recvmsg notification: truncated");

	cm = CMSG_FIRSTHDR(&msg);
	अगर (!cm)
		error(1, 0, "cmsg: no cmsg");
	अगर (!((cm->cmsg_level == SOL_IP && cm->cmsg_type == IP_RECVERR) ||
	      (cm->cmsg_level == SOL_IPV6 && cm->cmsg_type == IPV6_RECVERR) ||
	      (cm->cmsg_level == SOL_PACKET && cm->cmsg_type == PACKET_TX_TIMESTAMP)))
		error(1, 0, "serr: wrong type: %d.%d",
		      cm->cmsg_level, cm->cmsg_type);

	serr = (व्योम *) CMSG_DATA(cm);

	अगर (serr->ee_origin != SO_EE_ORIGIN_ZEROCOPY)
		error(1, 0, "serr: wrong origin: %u", serr->ee_origin);
	अगर (serr->ee_त्रुटि_सं != 0)
		error(1, 0, "serr: wrong error code: %u", serr->ee_त्रुटि_सं);

	hi = serr->ee_data;
	lo = serr->ee_info;
	range = hi - lo + 1;

	/* Detect notअगरication gaps. These should not happen often, अगर at all.
	 * Gaps can occur due to drops, reordering and retransmissions.
	 */
	अगर (lo != next_completion)
		ख_लिखो(मानक_त्रुटि, "gap: %u..%u does not append to %u\n",
			lo, hi, next_completion);
	next_completion = hi + 1;

	zerocopy = !(serr->ee_code & SO_EE_CODE_ZEROCOPY_COPIED);
	अगर (zerocopied == -1)
		zerocopied = zerocopy;
	अन्यथा अगर (zerocopied != zerocopy) अणु
		ख_लिखो(मानक_त्रुटि, "serr: inconsistent\n");
		zerocopied = zerocopy;
	पूर्ण

	अगर (cfg_verbose >= 2)
		ख_लिखो(मानक_त्रुटि, "completed: %u (h=%u l=%u)\n",
			range, hi, lo);

	completions += range;
	वापस true;
पूर्ण

/* Read all outstanding messages on the errqueue */
अटल व्योम करो_recv_completions(पूर्णांक fd, पूर्णांक करोमुख्य)
अणु
	जबतक (करो_recv_completion(fd, करोमुख्य)) अणुपूर्ण
पूर्ण

/* Wait क्रम all reमुख्यing completions on the errqueue */
अटल व्योम करो_recv_reमुख्यing_completions(पूर्णांक fd, पूर्णांक करोमुख्य)
अणु
	पूर्णांक64_t tstop = समय_लोofday_ms() + cfg_रुकोसमय_ms;

	जबतक (completions < expected_completions &&
	       समय_लोofday_ms() < tstop) अणु
		अगर (करो_poll(fd, करोमुख्य == PF_RDS ? POLLIN : POLLERR))
			करो_recv_completions(fd, करोमुख्य);
	पूर्ण

	अगर (completions < expected_completions)
		ख_लिखो(मानक_त्रुटि, "missing notifications: %lu < %lu\n",
			completions, expected_completions);
पूर्ण

अटल व्योम करो_tx(पूर्णांक करोमुख्य, पूर्णांक type, पूर्णांक protocol)
अणु
	काष्ठा iovec iov[3] = अणु अणु0पूर्ण पूर्ण;
	काष्ठा sockaddr_ll laddr;
	काष्ठा msghdr msg = अणु0पूर्ण;
	काष्ठा ethhdr eth;
	जोड़ अणु
		काष्ठा ipv6hdr ip6h;
		काष्ठा iphdr iph;
	पूर्ण nh;
	uपूर्णांक64_t tstop;
	पूर्णांक fd;

	fd = करो_setup_tx(करोमुख्य, type, protocol);

	अगर (करोमुख्य == PF_PACKET) अणु
		uपूर्णांक16_t proto = cfg_family == PF_INET ? ETH_P_IP : ETH_P_IPV6;

		/* sock_raw passes ll header as data */
		अगर (type == SOCK_RAW) अणु
			स_रखो(eth.h_dest, 0x06, ETH_ALEN);
			स_रखो(eth.h_source, 0x02, ETH_ALEN);
			eth.h_proto = htons(proto);
			iov[0].iov_base = &eth;
			iov[0].iov_len = माप(eth);
			msg.msg_iovlen++;
		पूर्ण

		/* both sock_raw and sock_dgram expect name */
		स_रखो(&laddr, 0, माप(laddr));
		laddr.sll_family	= AF_PACKET;
		laddr.sll_अगरindex	= cfg_अगरindex;
		laddr.sll_protocol	= htons(proto);
		laddr.sll_halen		= ETH_ALEN;

		स_रखो(laddr.sll_addr, 0x06, ETH_ALEN);

		msg.msg_name		= &laddr;
		msg.msg_namelen		= माप(laddr);
	पूर्ण

	/* packet and raw sockets with hdrincl must pass network header */
	अगर (करोमुख्य == PF_PACKET || protocol == IPPROTO_RAW) अणु
		अगर (cfg_family == PF_INET)
			iov[1].iov_len = setup_iph(&nh.iph, cfg_payload_len);
		अन्यथा
			iov[1].iov_len = setup_ip6h(&nh.ip6h, cfg_payload_len);

		iov[1].iov_base = (व्योम *) &nh;
		msg.msg_iovlen++;
	पूर्ण

	अगर (करोमुख्य == PF_RDS) अणु
		msg.msg_name = &cfg_dst_addr;
		msg.msg_namelen =  (cfg_dst_addr.ss_family == AF_INET ?
				    माप(काष्ठा sockaddr_in) :
				    माप(काष्ठा sockaddr_in6));
	पूर्ण

	iov[2].iov_base = payload;
	iov[2].iov_len = cfg_payload_len;
	msg.msg_iovlen++;
	msg.msg_iov = &iov[3 - msg.msg_iovlen];

	tstop = समय_लोofday_ms() + cfg_runसमय_ms;
	करो अणु
		अगर (cfg_cork)
			करो_sendmsg_corked(fd, &msg);
		अन्यथा
			करो_sendmsg(fd, &msg, cfg_zerocopy, करोमुख्य);

		जबतक (!करो_poll(fd, POLLOUT)) अणु
			अगर (cfg_zerocopy)
				करो_recv_completions(fd, करोमुख्य);
		पूर्ण

	पूर्ण जबतक (समय_लोofday_ms() < tstop);

	अगर (cfg_zerocopy)
		करो_recv_reमुख्यing_completions(fd, करोमुख्य);

	अगर (बंद(fd))
		error(1, त्रुटि_सं, "close");

	ख_लिखो(मानक_त्रुटि, "tx=%lu (%lu MB) txc=%lu zc=%c\n",
		packets, bytes >> 20, completions,
		zerocopied == 1 ? 'y' : 'n');
पूर्ण

अटल पूर्णांक करो_setup_rx(पूर्णांक करोमुख्य, पूर्णांक type, पूर्णांक protocol)
अणु
	पूर्णांक fd;

	/* If tx over PF_PACKET, rx over PF_INET(6)/SOCK_RAW,
	 * to recv the only copy of the packet, not a clone
	 */
	अगर (करोमुख्य == PF_PACKET)
		error(1, 0, "Use PF_INET/SOCK_RAW to read");

	अगर (type == SOCK_RAW && protocol == IPPROTO_RAW)
		error(1, 0, "IPPROTO_RAW: not supported on Rx");

	fd = socket(करोमुख्य, type, protocol);
	अगर (fd == -1)
		error(1, त्रुटि_सं, "socket r");

	करो_setsockopt(fd, SOL_SOCKET, SO_RCVBUF, 1 << 21);
	करो_setsockopt(fd, SOL_SOCKET, SO_RCVLOWAT, 1 << 16);
	करो_setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, 1);

	अगर (bind(fd, (व्योम *) &cfg_dst_addr, cfg_alen))
		error(1, त्रुटि_सं, "bind");

	अगर (type == SOCK_STREAM) अणु
		अगर (listen(fd, 1))
			error(1, त्रुटि_सं, "listen");
		fd = करो_accept(fd);
	पूर्ण

	वापस fd;
पूर्ण

/* Flush all outstanding bytes क्रम the tcp receive queue */
अटल व्योम करो_flush_tcp(पूर्णांक fd)
अणु
	पूर्णांक ret;

	/* MSG_TRUNC flushes up to len bytes */
	ret = recv(fd, शून्य, 1 << 21, MSG_TRUNC | MSG_DONTWAIT);
	अगर (ret == -1 && त्रुटि_सं == EAGAIN)
		वापस;
	अगर (ret == -1)
		error(1, त्रुटि_सं, "flush");
	अगर (!ret)
		वापस;

	packets++;
	bytes += ret;
पूर्ण

/* Flush all outstanding datagrams. Verअगरy first few bytes of each. */
अटल व्योम करो_flush_datagram(पूर्णांक fd, पूर्णांक type)
अणु
	पूर्णांक ret, off = 0;
	अक्षर buf[64];

	/* MSG_TRUNC will वापस full datagram length */
	ret = recv(fd, buf, माप(buf), MSG_DONTWAIT | MSG_TRUNC);
	अगर (ret == -1 && त्रुटि_सं == EAGAIN)
		वापस;

	/* raw ipv4 वापस with header, raw ipv6 without */
	अगर (cfg_family == PF_INET && type == SOCK_RAW) अणु
		off += माप(काष्ठा iphdr);
		ret -= माप(काष्ठा iphdr);
	पूर्ण

	अगर (ret == -1)
		error(1, त्रुटि_सं, "recv");
	अगर (ret != cfg_payload_len)
		error(1, 0, "recv: ret=%u != %u", ret, cfg_payload_len);
	अगर (ret > माप(buf) - off)
		ret = माप(buf) - off;
	अगर (स_भेद(buf + off, payload, ret))
		error(1, 0, "recv: data mismatch");

	packets++;
	bytes += cfg_payload_len;
पूर्ण

अटल व्योम करो_rx(पूर्णांक करोमुख्य, पूर्णांक type, पूर्णांक protocol)
अणु
	स्थिर पूर्णांक cfg_receiver_रुको_ms = 400;
	uपूर्णांक64_t tstop;
	पूर्णांक fd;

	fd = करो_setup_rx(करोमुख्य, type, protocol);

	tstop = समय_लोofday_ms() + cfg_runसमय_ms + cfg_receiver_रुको_ms;
	करो अणु
		अगर (type == SOCK_STREAM)
			करो_flush_tcp(fd);
		अन्यथा
			करो_flush_datagram(fd, type);

		करो_poll(fd, POLLIN);

	पूर्ण जबतक (समय_लोofday_ms() < tstop);

	अगर (बंद(fd))
		error(1, त्रुटि_सं, "close");

	ख_लिखो(मानक_त्रुटि, "rx=%lu (%lu MB)\n", packets, bytes >> 20);
पूर्ण

अटल व्योम करो_test(पूर्णांक करोमुख्य, पूर्णांक type, पूर्णांक protocol)
अणु
	पूर्णांक i;

	अगर (cfg_cork && (करोमुख्य == PF_PACKET || type != SOCK_DGRAM))
		error(1, 0, "can only cork udp sockets");

	करो_setcpu(cfg_cpu);

	क्रम (i = 0; i < IP_MAXPACKET; i++)
		payload[i] = 'a' + (i % 26);

	अगर (cfg_rx)
		करो_rx(करोमुख्य, type, protocol);
	अन्यथा
		करो_tx(करोमुख्य, type, protocol);
पूर्ण

अटल व्योम usage(स्थिर अक्षर *filepath)
अणु
	error(1, 0, "Usage: %s [options] <test>", filepath);
पूर्ण

अटल व्योम parse_opts(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर पूर्णांक max_payload_len = माप(payload) -
				    माप(काष्ठा ipv6hdr) -
				    माप(काष्ठा tcphdr) -
				    40 /* max tcp options */;
	पूर्णांक c;
	अक्षर *daddr = शून्य, *saddr = शून्य;
	अक्षर *cfg_test;

	cfg_payload_len = max_payload_len;

	जबतक ((c = getopt(argc, argv, "46c:C:D:i:mp:rs:S:t:vz")) != -1) अणु
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
		हाल 'c':
			cfg_cork = म_से_दीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'C':
			cfg_cpu = म_से_दीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'D':
			daddr = optarg;
			अवरोध;
		हाल 'i':
			cfg_अगरindex = अगर_nametoindex(optarg);
			अगर (cfg_अगरindex == 0)
				error(1, त्रुटि_सं, "invalid iface: %s", optarg);
			अवरोध;
		हाल 'm':
			cfg_cork_mixed = true;
			अवरोध;
		हाल 'p':
			cfg_port = म_से_अदीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'r':
			cfg_rx = true;
			अवरोध;
		हाल 's':
			cfg_payload_len = म_से_अदीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'S':
			saddr = optarg;
			अवरोध;
		हाल 't':
			cfg_runसमय_ms = 200 + म_से_अदीर्घ(optarg, शून्य, 10) * 1000;
			अवरोध;
		हाल 'v':
			cfg_verbose++;
			अवरोध;
		हाल 'z':
			cfg_zerocopy = true;
			अवरोध;
		पूर्ण
	पूर्ण

	cfg_test = argv[argc - 1];
	अगर (म_भेद(cfg_test, "rds") == 0) अणु
		अगर (!daddr)
			error(1, 0, "-D <server addr> required for PF_RDS\n");
		अगर (!cfg_rx && !saddr)
			error(1, 0, "-S <client addr> required for PF_RDS\n");
	पूर्ण
	setup_sockaddr(cfg_family, daddr, &cfg_dst_addr);
	setup_sockaddr(cfg_family, saddr, &cfg_src_addr);

	अगर (cfg_payload_len > max_payload_len)
		error(1, 0, "-s: payload exceeds max (%d)", max_payload_len);
	अगर (cfg_cork_mixed && (!cfg_zerocopy || !cfg_cork))
		error(1, 0, "-m: cork_mixed requires corking and zerocopy");

	अगर (optind != argc - 1)
		usage(argv[0]);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर अक्षर *cfg_test;

	parse_opts(argc, argv);

	cfg_test = argv[argc - 1];

	अगर (!म_भेद(cfg_test, "packet"))
		करो_test(PF_PACKET, SOCK_RAW, 0);
	अन्यथा अगर (!म_भेद(cfg_test, "packet_dgram"))
		करो_test(PF_PACKET, SOCK_DGRAM, 0);
	अन्यथा अगर (!म_भेद(cfg_test, "raw"))
		करो_test(cfg_family, SOCK_RAW, IPPROTO_EGP);
	अन्यथा अगर (!म_भेद(cfg_test, "raw_hdrincl"))
		करो_test(cfg_family, SOCK_RAW, IPPROTO_RAW);
	अन्यथा अगर (!म_भेद(cfg_test, "tcp"))
		करो_test(cfg_family, SOCK_STREAM, 0);
	अन्यथा अगर (!म_भेद(cfg_test, "udp"))
		करो_test(cfg_family, SOCK_DGRAM, 0);
	अन्यथा अगर (!म_भेद(cfg_test, "rds"))
		करो_test(PF_RDS, SOCK_SEQPACKET, 0);
	अन्यथा
		error(1, 0, "unknown cfg_test %s", cfg_test);

	वापस 0;
पूर्ण
