<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014 Google Inc.
 * Author: willemb@google.com (Willem de Bruijn)
 *
 * Test software tx बारtamping, including
 *
 * - SCHED, SND and ACK बारtamps
 * - RAW, UDP and TCP
 * - IPv4 and IPv6
 * - various packet sizes (to test GSO and TSO)
 *
 * Consult the command line arguments क्रम help on running
 * the various testहालs.
 *
 * This test requires a dummy TCP server.
 * A simple `nc6 [-u] -l -p $DESTPORT` will करो
 */

#घोषणा _GNU_SOURCE

#समावेश <arpa/inet.h>
#समावेश <यंत्र/types.h>
#समावेश <error.h>
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <linux/errqueue.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/net_tstamp.h>
#समावेश <netdb.h>
#समावेश <net/अगर.h>
#समावेश <netinet/in.h>
#समावेश <netinet/ip.h>
#समावेश <netinet/udp.h>
#समावेश <netinet/tcp.h>
#समावेश <poll.h>
#समावेश <मानकतर्क.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/epoll.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/select.h>
#समावेश <sys/socket.h>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश <समय.स>
#समावेश <unistd.h>

#घोषणा NSEC_PER_USEC	1000L
#घोषणा USEC_PER_SEC	1000000L
#घोषणा NSEC_PER_SEC	1000000000LL

/* command line parameters */
अटल पूर्णांक cfg_proto = SOCK_STREAM;
अटल पूर्णांक cfg_ipproto = IPPROTO_TCP;
अटल पूर्णांक cfg_num_pkts = 4;
अटल पूर्णांक करो_ipv4 = 1;
अटल पूर्णांक करो_ipv6 = 1;
अटल पूर्णांक cfg_payload_len = 10;
अटल पूर्णांक cfg_poll_समयout = 100;
अटल पूर्णांक cfg_delay_snd;
अटल पूर्णांक cfg_delay_ack;
अटल पूर्णांक cfg_delay_tolerance_usec = 500;
अटल bool cfg_show_payload;
अटल bool cfg_करो_pktinfo;
अटल bool cfg_busy_poll;
अटल पूर्णांक cfg_sleep_usec = 50 * 1000;
अटल bool cfg_loop_nodata;
अटल bool cfg_use_cmsg;
अटल bool cfg_use_pf_packet;
अटल bool cfg_use_epoll;
अटल bool cfg_epollet;
अटल bool cfg_करो_listen;
अटल uपूर्णांक16_t dest_port = 9000;
अटल bool cfg_prपूर्णांक_nsec;

अटल काष्ठा sockaddr_in daddr;
अटल काष्ठा sockaddr_in6 daddr6;
अटल काष्ठा बारpec ts_usr;

अटल पूर्णांक saved_tskey = -1;
अटल पूर्णांक saved_tskey_type = -1;

काष्ठा timing_event अणु
	पूर्णांक64_t min;
	पूर्णांक64_t max;
	पूर्णांक64_t total;
	पूर्णांक count;
पूर्ण;

अटल काष्ठा timing_event usr_enq;
अटल काष्ठा timing_event usr_snd;
अटल काष्ठा timing_event usr_ack;

अटल bool test_failed;

अटल पूर्णांक64_t बारpec_to_ns64(काष्ठा बारpec *ts)
अणु
	वापस ts->tv_sec * NSEC_PER_SEC + ts->tv_nsec;
पूर्ण

अटल पूर्णांक64_t बारpec_to_us64(काष्ठा बारpec *ts)
अणु
	वापस ts->tv_sec * USEC_PER_SEC + ts->tv_nsec / NSEC_PER_USEC;
पूर्ण

अटल व्योम init_timing_event(काष्ठा timing_event *te)
अणु
	te->min = INT64_MAX;
	te->max = 0;
	te->total = 0;
	te->count = 0;
पूर्ण

अटल व्योम add_timing_event(काष्ठा timing_event *te,
		काष्ठा बारpec *t_start, काष्ठा बारpec *t_end)
अणु
	पूर्णांक64_t ts_delta = बारpec_to_ns64(t_end) - बारpec_to_ns64(t_start);

	te->count++;
	अगर (ts_delta < te->min)
		te->min = ts_delta;
	अगर (ts_delta > te->max)
		te->max = ts_delta;
	te->total += ts_delta;
पूर्ण

अटल व्योम validate_key(पूर्णांक tskey, पूर्णांक tstype)
अणु
	पूर्णांक stepsize;

	/* compare key क्रम each subsequent request
	 * must only test क्रम one type, the first one requested
	 */
	अगर (saved_tskey == -1)
		saved_tskey_type = tstype;
	अन्यथा अगर (saved_tskey_type != tstype)
		वापस;

	stepsize = cfg_proto == SOCK_STREAM ? cfg_payload_len : 1;
	अगर (tskey != saved_tskey + stepsize) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: key %d, expected %d\n",
				tskey, saved_tskey + stepsize);
		test_failed = true;
	पूर्ण

	saved_tskey = tskey;
पूर्ण

अटल व्योम validate_बारtamp(काष्ठा बारpec *cur, पूर्णांक min_delay)
अणु
	पूर्णांक64_t cur64, start64;
	पूर्णांक max_delay;

	cur64 = बारpec_to_us64(cur);
	start64 = बारpec_to_us64(&ts_usr);
	max_delay = min_delay + cfg_delay_tolerance_usec;

	अगर (cur64 < start64 + min_delay || cur64 > start64 + max_delay) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: %lu us expected between %d and %d\n",
				cur64 - start64, min_delay, max_delay);
		test_failed = true;
	पूर्ण
पूर्ण

अटल व्योम __prपूर्णांक_ts_delta_क्रमmatted(पूर्णांक64_t ts_delta)
अणु
	अगर (cfg_prपूर्णांक_nsec)
		ख_लिखो(मानक_त्रुटि, "%lu ns", ts_delta);
	अन्यथा
		ख_लिखो(मानक_त्रुटि, "%lu us", ts_delta / NSEC_PER_USEC);
पूर्ण

अटल व्योम __prपूर्णांक_बारtamp(स्थिर अक्षर *name, काष्ठा बारpec *cur,
			      uपूर्णांक32_t key, पूर्णांक payload_len)
अणु
	पूर्णांक64_t ts_delta;

	अगर (!(cur->tv_sec | cur->tv_nsec))
		वापस;

	अगर (cfg_prपूर्णांक_nsec)
		ख_लिखो(मानक_त्रुटि, "  %s: %lu s %lu ns (seq=%u, len=%u)",
				name, cur->tv_sec, cur->tv_nsec,
				key, payload_len);
	अन्यथा
		ख_लिखो(मानक_त्रुटि, "  %s: %lu s %lu us (seq=%u, len=%u)",
				name, cur->tv_sec, cur->tv_nsec / NSEC_PER_USEC,
				key, payload_len);

	अगर (cur != &ts_usr) अणु
		ts_delta = बारpec_to_ns64(cur) - बारpec_to_ns64(&ts_usr);
		ख_लिखो(मानक_त्रुटि, "  (USR +");
		__prपूर्णांक_ts_delta_क्रमmatted(ts_delta);
		ख_लिखो(मानक_त्रुटि, ")");
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "\n");
पूर्ण

अटल व्योम prपूर्णांक_बारtamp_usr(व्योम)
अणु
	अगर (घड़ी_समय_लो(CLOCK_REALTIME, &ts_usr))
		error(1, त्रुटि_सं, "clock_gettime");

	__prपूर्णांक_बारtamp("  USR", &ts_usr, 0, 0);
पूर्ण

अटल व्योम prपूर्णांक_बारtamp(काष्ठा scm_बारtamping *tss, पूर्णांक tstype,
			    पूर्णांक tskey, पूर्णांक payload_len)
अणु
	स्थिर अक्षर *tsname;

	validate_key(tskey, tstype);

	चयन (tstype) अणु
	हाल SCM_TSTAMP_SCHED:
		tsname = "  ENQ";
		validate_बारtamp(&tss->ts[0], 0);
		add_timing_event(&usr_enq, &ts_usr, &tss->ts[0]);
		अवरोध;
	हाल SCM_TSTAMP_SND:
		tsname = "  SND";
		validate_बारtamp(&tss->ts[0], cfg_delay_snd);
		add_timing_event(&usr_snd, &ts_usr, &tss->ts[0]);
		अवरोध;
	हाल SCM_TSTAMP_ACK:
		tsname = "  ACK";
		validate_बारtamp(&tss->ts[0], cfg_delay_ack);
		add_timing_event(&usr_ack, &ts_usr, &tss->ts[0]);
		अवरोध;
	शेष:
		error(1, 0, "unknown timestamp type: %u",
		tstype);
	पूर्ण
	__prपूर्णांक_बारtamp(tsname, &tss->ts[0], tskey, payload_len);
पूर्ण

अटल व्योम prपूर्णांक_timing_event(अक्षर *name, काष्ठा timing_event *te)
अणु
	अगर (!te->count)
		वापस;

	ख_लिखो(मानक_त्रुटि, "    %s: count=%d", name, te->count);
	ख_लिखो(मानक_त्रुटि, ", avg=");
	__prपूर्णांक_ts_delta_क्रमmatted((पूर्णांक64_t)(te->total / te->count));
	ख_लिखो(मानक_त्रुटि, ", min=");
	__prपूर्णांक_ts_delta_क्रमmatted(te->min);
	ख_लिखो(मानक_त्रुटि, ", max=");
	__prपूर्णांक_ts_delta_क्रमmatted(te->max);
	ख_लिखो(मानक_त्रुटि, "\n");
पूर्ण

/* TODO: convert to check_and_prपूर्णांक payload once API is stable */
अटल व्योम prपूर्णांक_payload(अक्षर *data, पूर्णांक len)
अणु
	पूर्णांक i;

	अगर (!len)
		वापस;

	अगर (len > 70)
		len = 70;

	ख_लिखो(मानक_त्रुटि, "payload: ");
	क्रम (i = 0; i < len; i++)
		ख_लिखो(मानक_त्रुटि, "%02hhx ", data[i]);
	ख_लिखो(मानक_त्रुटि, "\n");
पूर्ण

अटल व्योम prपूर्णांक_pktinfo(पूर्णांक family, पूर्णांक अगरindex, व्योम *saddr, व्योम *daddr)
अणु
	अक्षर sa[INET6_ADDRSTRLEN], da[INET6_ADDRSTRLEN];

	ख_लिखो(मानक_त्रुटि, "         pktinfo: ifindex=%u src=%s dst=%s\n",
		अगरindex,
		saddr ? inet_ntop(family, saddr, sa, माप(sa)) : "unknown",
		daddr ? inet_ntop(family, daddr, da, माप(da)) : "unknown");
पूर्ण

अटल व्योम __epoll(पूर्णांक epfd)
अणु
	काष्ठा epoll_event events;
	पूर्णांक ret;

	स_रखो(&events, 0, माप(events));
	ret = epoll_रुको(epfd, &events, 1, cfg_poll_समयout);
	अगर (ret != 1)
		error(1, त्रुटि_सं, "epoll_wait");
पूर्ण

अटल व्योम __poll(पूर्णांक fd)
अणु
	काष्ठा pollfd pollfd;
	पूर्णांक ret;

	स_रखो(&pollfd, 0, माप(pollfd));
	pollfd.fd = fd;
	ret = poll(&pollfd, 1, cfg_poll_समयout);
	अगर (ret != 1)
		error(1, त्रुटि_सं, "poll");
पूर्ण

अटल व्योम __recv_errmsg_cmsg(काष्ठा msghdr *msg, पूर्णांक payload_len)
अणु
	काष्ठा sock_extended_err *serr = शून्य;
	काष्ठा scm_बारtamping *tss = शून्य;
	काष्ठा cmsghdr *cm;
	पूर्णांक batch = 0;

	क्रम (cm = CMSG_FIRSTHDR(msg);
	     cm && cm->cmsg_len;
	     cm = CMSG_NXTHDR(msg, cm)) अणु
		अगर (cm->cmsg_level == SOL_SOCKET &&
		    cm->cmsg_type == SCM_TIMESTAMPING) अणु
			tss = (व्योम *) CMSG_DATA(cm);
		पूर्ण अन्यथा अगर ((cm->cmsg_level == SOL_IP &&
			    cm->cmsg_type == IP_RECVERR) ||
			   (cm->cmsg_level == SOL_IPV6 &&
			    cm->cmsg_type == IPV6_RECVERR) ||
			   (cm->cmsg_level == SOL_PACKET &&
			    cm->cmsg_type == PACKET_TX_TIMESTAMP)) अणु
			serr = (व्योम *) CMSG_DATA(cm);
			अगर (serr->ee_त्रुटि_सं != ENOMSG ||
			    serr->ee_origin != SO_EE_ORIGIN_TIMESTAMPING) अणु
				ख_लिखो(मानक_त्रुटि, "unknown ip error %d %d\n",
						serr->ee_त्रुटि_सं,
						serr->ee_origin);
				serr = शून्य;
			पूर्ण
		पूर्ण अन्यथा अगर (cm->cmsg_level == SOL_IP &&
			   cm->cmsg_type == IP_PKTINFO) अणु
			काष्ठा in_pktinfo *info = (व्योम *) CMSG_DATA(cm);
			prपूर्णांक_pktinfo(AF_INET, info->ipi_अगरindex,
				      &info->ipi_spec_dst, &info->ipi_addr);
		पूर्ण अन्यथा अगर (cm->cmsg_level == SOL_IPV6 &&
			   cm->cmsg_type == IPV6_PKTINFO) अणु
			काष्ठा in6_pktinfo *info6 = (व्योम *) CMSG_DATA(cm);
			prपूर्णांक_pktinfo(AF_INET6, info6->ipi6_अगरindex,
				      शून्य, &info6->ipi6_addr);
		पूर्ण अन्यथा
			ख_लिखो(मानक_त्रुटि, "unknown cmsg %d,%d\n",
					cm->cmsg_level, cm->cmsg_type);

		अगर (serr && tss) अणु
			prपूर्णांक_बारtamp(tss, serr->ee_info, serr->ee_data,
					payload_len);
			serr = शून्य;
			tss = शून्य;
			batch++;
		पूर्ण
	पूर्ण

	अगर (batch > 1)
		ख_लिखो(मानक_त्रुटि, "batched %d timestamps\n", batch);
पूर्ण

अटल पूर्णांक recv_errmsg(पूर्णांक fd)
अणु
	अटल अक्षर ctrl[1024 /* overprovision*/];
	अटल काष्ठा msghdr msg;
	काष्ठा iovec entry;
	अटल अक्षर *data;
	पूर्णांक ret = 0;

	data = दो_स्मृति(cfg_payload_len);
	अगर (!data)
		error(1, 0, "malloc");

	स_रखो(&msg, 0, माप(msg));
	स_रखो(&entry, 0, माप(entry));
	स_रखो(ctrl, 0, माप(ctrl));

	entry.iov_base = data;
	entry.iov_len = cfg_payload_len;
	msg.msg_iov = &entry;
	msg.msg_iovlen = 1;
	msg.msg_name = शून्य;
	msg.msg_namelen = 0;
	msg.msg_control = ctrl;
	msg.msg_controllen = माप(ctrl);

	ret = recvmsg(fd, &msg, MSG_ERRQUEUE);
	अगर (ret == -1 && त्रुटि_सं != EAGAIN)
		error(1, त्रुटि_सं, "recvmsg");

	अगर (ret >= 0) अणु
		__recv_errmsg_cmsg(&msg, ret);
		अगर (cfg_show_payload)
			prपूर्णांक_payload(data, cfg_payload_len);
	पूर्ण

	मुक्त(data);
	वापस ret == -1;
पूर्ण

अटल uपूर्णांक16_t get_ip_csum(स्थिर uपूर्णांक16_t *start, पूर्णांक num_words,
			    अचिन्हित दीर्घ sum)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_words; i++)
		sum += start[i];

	जबतक (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);

	वापस ~sum;
पूर्ण

अटल uपूर्णांक16_t get_udp_csum(स्थिर काष्ठा udphdr *udph, पूर्णांक alen)
अणु
	अचिन्हित दीर्घ pseuकरो_sum, csum_len;
	स्थिर व्योम *csum_start = udph;

	pseuकरो_sum = htons(IPPROTO_UDP);
	pseuकरो_sum += udph->len;

	/* checksum ip(v6) addresses + udp header + payload */
	csum_start -= alen * 2;
	csum_len = ntohs(udph->len) + alen * 2;

	वापस get_ip_csum(csum_start, csum_len >> 1, pseuकरो_sum);
पूर्ण

अटल पूर्णांक fill_header_ipv4(व्योम *p)
अणु
	काष्ठा iphdr *iph = p;

	स_रखो(iph, 0, माप(*iph));

	iph->ihl	= 5;
	iph->version	= 4;
	iph->ttl	= 2;
	iph->saddr	= daddr.sin_addr.s_addr;	/* set क्रम udp csum calc */
	iph->daddr	= daddr.sin_addr.s_addr;
	iph->protocol	= IPPROTO_UDP;

	/* kernel ग_लिखोs saddr, csum, len */

	वापस माप(*iph);
पूर्ण

अटल पूर्णांक fill_header_ipv6(व्योम *p)
अणु
	काष्ठा ipv6hdr *ip6h = p;

	स_रखो(ip6h, 0, माप(*ip6h));

	ip6h->version		= 6;
	ip6h->payload_len	= htons(माप(काष्ठा udphdr) + cfg_payload_len);
	ip6h->nexthdr		= IPPROTO_UDP;
	ip6h->hop_limit		= 64;

	ip6h->saddr             = daddr6.sin6_addr;
	ip6h->daddr		= daddr6.sin6_addr;

	/* kernel करोes not ग_लिखो saddr in हाल of ipv6 */

	वापस माप(*ip6h);
पूर्ण

अटल व्योम fill_header_udp(व्योम *p, bool is_ipv4)
अणु
	काष्ठा udphdr *udph = p;

	udph->source = ntohs(dest_port + 1);	/* spoof */
	udph->dest   = ntohs(dest_port);
	udph->len    = ntohs(माप(*udph) + cfg_payload_len);
	udph->check  = 0;

	udph->check  = get_udp_csum(udph, is_ipv4 ? माप(काष्ठा in_addr) :
						    माप(काष्ठा in6_addr));
पूर्ण

अटल व्योम करो_test(पूर्णांक family, अचिन्हित पूर्णांक report_opt)
अणु
	अक्षर control[CMSG_SPACE(माप(uपूर्णांक32_t))];
	काष्ठा sockaddr_ll laddr;
	अचिन्हित पूर्णांक sock_opt;
	काष्ठा cmsghdr *cmsg;
	काष्ठा msghdr msg;
	काष्ठा iovec iov;
	अक्षर *buf;
	पूर्णांक fd, i, val = 1, total_len, epfd = 0;

	init_timing_event(&usr_enq);
	init_timing_event(&usr_snd);
	init_timing_event(&usr_ack);

	total_len = cfg_payload_len;
	अगर (cfg_use_pf_packet || cfg_proto == SOCK_RAW) अणु
		total_len += माप(काष्ठा udphdr);
		अगर (cfg_use_pf_packet || cfg_ipproto == IPPROTO_RAW) अणु
			अगर (family == PF_INET)
				total_len += माप(काष्ठा iphdr);
			अन्यथा
				total_len += माप(काष्ठा ipv6hdr);
		पूर्ण
		/* special हाल, only rawv6_sendmsg:
		 * pass proto in sin6_port अगर not connected
		 * also see ANK comment in net/ipv4/raw.c
		 */
		daddr6.sin6_port = htons(cfg_ipproto);
	पूर्ण

	buf = दो_स्मृति(total_len);
	अगर (!buf)
		error(1, 0, "malloc");

	fd = socket(cfg_use_pf_packet ? PF_PACKET : family,
		    cfg_proto, cfg_ipproto);
	अगर (fd < 0)
		error(1, त्रुटि_सं, "socket");

	अगर (cfg_use_epoll) अणु
		काष्ठा epoll_event ev;

		स_रखो(&ev, 0, माप(ev));
		ev.data.fd = fd;
		अगर (cfg_epollet)
			ev.events |= EPOLLET;
		epfd = epoll_create(1);
		अगर (epfd <= 0)
			error(1, त्रुटि_सं, "epoll_create");
		अगर (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev))
			error(1, त्रुटि_सं, "epoll_ctl");
	पूर्ण

	/* reset expected key on each new socket */
	saved_tskey = -1;

	अगर (cfg_proto == SOCK_STREAM) अणु
		अगर (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY,
			       (अक्षर*) &val, माप(val)))
			error(1, 0, "setsockopt no nagle");

		अगर (family == PF_INET) अणु
			अगर (connect(fd, (व्योम *) &daddr, माप(daddr)))
				error(1, त्रुटि_सं, "connect ipv4");
		पूर्ण अन्यथा अणु
			अगर (connect(fd, (व्योम *) &daddr6, माप(daddr6)))
				error(1, त्रुटि_सं, "connect ipv6");
		पूर्ण
	पूर्ण

	अगर (cfg_करो_pktinfo) अणु
		अगर (family == AF_INET6) अणु
			अगर (setsockopt(fd, SOL_IPV6, IPV6_RECVPKTINFO,
				       &val, माप(val)))
				error(1, त्रुटि_सं, "setsockopt pktinfo ipv6");
		पूर्ण अन्यथा अणु
			अगर (setsockopt(fd, SOL_IP, IP_PKTINFO,
				       &val, माप(val)))
				error(1, त्रुटि_सं, "setsockopt pktinfo ipv4");
		पूर्ण
	पूर्ण

	sock_opt = SOF_TIMESTAMPING_SOFTWARE |
		   SOF_TIMESTAMPING_OPT_CMSG |
		   SOF_TIMESTAMPING_OPT_ID;

	अगर (!cfg_use_cmsg)
		sock_opt |= report_opt;

	अगर (cfg_loop_nodata)
		sock_opt |= SOF_TIMESTAMPING_OPT_TSONLY;

	अगर (setsockopt(fd, SOL_SOCKET, SO_TIMESTAMPING,
		       (अक्षर *) &sock_opt, माप(sock_opt)))
		error(1, 0, "setsockopt timestamping");

	क्रम (i = 0; i < cfg_num_pkts; i++) अणु
		स_रखो(&msg, 0, माप(msg));
		स_रखो(buf, 'a' + i, total_len);

		अगर (cfg_use_pf_packet || cfg_proto == SOCK_RAW) अणु
			पूर्णांक off = 0;

			अगर (cfg_use_pf_packet || cfg_ipproto == IPPROTO_RAW) अणु
				अगर (family == PF_INET)
					off = fill_header_ipv4(buf);
				अन्यथा
					off = fill_header_ipv6(buf);
			पूर्ण

			fill_header_udp(buf + off, family == PF_INET);
		पूर्ण

		prपूर्णांक_बारtamp_usr();

		iov.iov_base = buf;
		iov.iov_len = total_len;

		अगर (cfg_proto != SOCK_STREAM) अणु
			अगर (cfg_use_pf_packet) अणु
				स_रखो(&laddr, 0, माप(laddr));

				laddr.sll_family	= AF_PACKET;
				laddr.sll_अगरindex	= 1;
				laddr.sll_protocol	= htons(family == AF_INET ? ETH_P_IP : ETH_P_IPV6);
				laddr.sll_halen		= ETH_ALEN;

				msg.msg_name = (व्योम *)&laddr;
				msg.msg_namelen = माप(laddr);
			पूर्ण अन्यथा अगर (family == PF_INET) अणु
				msg.msg_name = (व्योम *)&daddr;
				msg.msg_namelen = माप(daddr);
			पूर्ण अन्यथा अणु
				msg.msg_name = (व्योम *)&daddr6;
				msg.msg_namelen = माप(daddr6);
			पूर्ण
		पूर्ण

		msg.msg_iov = &iov;
		msg.msg_iovlen = 1;

		अगर (cfg_use_cmsg) अणु
			स_रखो(control, 0, माप(control));

			msg.msg_control = control;
			msg.msg_controllen = माप(control);

			cmsg = CMSG_FIRSTHDR(&msg);
			cmsg->cmsg_level = SOL_SOCKET;
			cmsg->cmsg_type = SO_TIMESTAMPING;
			cmsg->cmsg_len = CMSG_LEN(माप(uपूर्णांक32_t));

			*((uपूर्णांक32_t *) CMSG_DATA(cmsg)) = report_opt;
		पूर्ण

		val = sendmsg(fd, &msg, 0);
		अगर (val != total_len)
			error(1, त्रुटि_सं, "send");

		/* रुको क्रम all errors to be queued, अन्यथा ACKs arrive OOO */
		अगर (cfg_sleep_usec)
			usleep(cfg_sleep_usec);

		अगर (!cfg_busy_poll) अणु
			अगर (cfg_use_epoll)
				__epoll(epfd);
			अन्यथा
				__poll(fd);
		पूर्ण

		जबतक (!recv_errmsg(fd)) अणुपूर्ण
	पूर्ण

	prपूर्णांक_timing_event("USR-ENQ", &usr_enq);
	prपूर्णांक_timing_event("USR-SND", &usr_snd);
	prपूर्णांक_timing_event("USR-ACK", &usr_ack);

	अगर (बंद(fd))
		error(1, त्रुटि_सं, "close");

	मुक्त(buf);
	usleep(100 * NSEC_PER_USEC);
पूर्ण

अटल व्योम __attribute__((noवापस)) usage(स्थिर अक्षर *filepath)
अणु
	ख_लिखो(मानक_त्रुटि, "\nUsage: %s [options] hostname\n"
			"\nwhere options are:\n"
			"  -4:   only IPv4\n"
			"  -6:   only IPv6\n"
			"  -h:   show this message\n"
			"  -b:   busy poll to read from error queue\n"
			"  -c N: number of packets for each test\n"
			"  -C:   use cmsg to set tstamp recording options\n"
			"  -e:   use level-triggered epoll() instead of poll()\n"
			"  -E:   use event-triggered epoll() instead of poll()\n"
			"  -F:   poll()/epoll() waits forever for an event\n"
			"  -I:   request PKTINFO\n"
			"  -l N: send N bytes at a time\n"
			"  -L    listen on hostname and port\n"
			"  -n:   set no-payload option\n"
			"  -N:   print timestamps and durations in nsec (instead of usec)\n"
			"  -p N: connect to port N\n"
			"  -P:   use PF_PACKET\n"
			"  -r:   use raw\n"
			"  -R:   use raw (IP_HDRINCL)\n"
			"  -S N: usec to sleep before reading error queue\n"
			"  -t N: tolerance (usec) for timestamp validation\n"
			"  -u:   use udp\n"
			"  -v:   validate SND delay (usec)\n"
			"  -V:   validate ACK delay (usec)\n"
			"  -x:   show payload (up to 70 bytes)\n",
			filepath);
	निकास(1);
पूर्ण

अटल व्योम parse_opt(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक proto_count = 0;
	पूर्णांक c;

	जबतक ((c = getopt(argc, argv,
				"46bc:CeEFhIl:LnNp:PrRS:t:uv:V:x")) != -1) अणु
		चयन (c) अणु
		हाल '4':
			करो_ipv6 = 0;
			अवरोध;
		हाल '6':
			करो_ipv4 = 0;
			अवरोध;
		हाल 'b':
			cfg_busy_poll = true;
			अवरोध;
		हाल 'c':
			cfg_num_pkts = म_से_अदीर्घ(optarg, शून्य, 10);
			अवरोध;
		हाल 'C':
			cfg_use_cmsg = true;
			अवरोध;
		हाल 'e':
			cfg_use_epoll = true;
			अवरोध;
		हाल 'E':
			cfg_use_epoll = true;
			cfg_epollet = true;
		हाल 'F':
			cfg_poll_समयout = -1;
			अवरोध;
		हाल 'I':
			cfg_करो_pktinfo = true;
			अवरोध;
		हाल 'l':
			cfg_payload_len = म_से_अदीर्घ(optarg, शून्य, 10);
			अवरोध;
		हाल 'L':
			cfg_करो_listen = true;
			अवरोध;
		हाल 'n':
			cfg_loop_nodata = true;
			अवरोध;
		हाल 'N':
			cfg_prपूर्णांक_nsec = true;
			अवरोध;
		हाल 'p':
			dest_port = म_से_अदीर्घ(optarg, शून्य, 10);
			अवरोध;
		हाल 'P':
			proto_count++;
			cfg_use_pf_packet = true;
			cfg_proto = SOCK_DGRAM;
			cfg_ipproto = 0;
			अवरोध;
		हाल 'r':
			proto_count++;
			cfg_proto = SOCK_RAW;
			cfg_ipproto = IPPROTO_UDP;
			अवरोध;
		हाल 'R':
			proto_count++;
			cfg_proto = SOCK_RAW;
			cfg_ipproto = IPPROTO_RAW;
			अवरोध;
		हाल 'S':
			cfg_sleep_usec = म_से_अदीर्घ(optarg, शून्य, 10);
			अवरोध;
		हाल 't':
			cfg_delay_tolerance_usec = म_से_अदीर्घ(optarg, शून्य, 10);
			अवरोध;
		हाल 'u':
			proto_count++;
			cfg_proto = SOCK_DGRAM;
			cfg_ipproto = IPPROTO_UDP;
			अवरोध;
		हाल 'v':
			cfg_delay_snd = म_से_अदीर्घ(optarg, शून्य, 10);
			अवरोध;
		हाल 'V':
			cfg_delay_ack = म_से_अदीर्घ(optarg, शून्य, 10);
			अवरोध;
		हाल 'x':
			cfg_show_payload = true;
			अवरोध;
		हाल 'h':
		शेष:
			usage(argv[0]);
		पूर्ण
	पूर्ण

	अगर (!cfg_payload_len)
		error(1, 0, "payload may not be nonzero");
	अगर (cfg_proto != SOCK_STREAM && cfg_payload_len > 1472)
		error(1, 0, "udp packet might exceed expected MTU");
	अगर (!करो_ipv4 && !करो_ipv6)
		error(1, 0, "pass -4 or -6, not both");
	अगर (proto_count > 1)
		error(1, 0, "pass -P, -r, -R or -u, not multiple");
	अगर (cfg_करो_pktinfo && cfg_use_pf_packet)
		error(1, 0, "cannot ask for pktinfo over pf_packet");
	अगर (cfg_busy_poll && cfg_use_epoll)
		error(1, 0, "pass epoll or busy_poll, not both");

	अगर (optind != argc - 1)
		error(1, 0, "missing required hostname argument");
पूर्ण

अटल व्योम resolve_hostname(स्थिर अक्षर *hostname)
अणु
	काष्ठा addrinfo hपूर्णांकs = अणु .ai_family = करो_ipv4 ? AF_INET : AF_INET6 पूर्ण;
	काष्ठा addrinfo *addrs, *cur;
	पूर्णांक have_ipv4 = 0, have_ipv6 = 0;

retry:
	अगर (getaddrinfo(hostname, शून्य, &hपूर्णांकs, &addrs))
		error(1, त्रुटि_सं, "getaddrinfo");

	cur = addrs;
	जबतक (cur && !have_ipv4 && !have_ipv6) अणु
		अगर (!have_ipv4 && cur->ai_family == AF_INET) अणु
			स_नकल(&daddr, cur->ai_addr, माप(daddr));
			daddr.sin_port = htons(dest_port);
			have_ipv4 = 1;
		पूर्ण
		अन्यथा अगर (!have_ipv6 && cur->ai_family == AF_INET6) अणु
			स_नकल(&daddr6, cur->ai_addr, माप(daddr6));
			daddr6.sin6_port = htons(dest_port);
			have_ipv6 = 1;
		पूर्ण
		cur = cur->ai_next;
	पूर्ण
	अगर (addrs)
		मुक्तaddrinfo(addrs);

	अगर (करो_ipv6 && hपूर्णांकs.ai_family != AF_INET6) अणु
		hपूर्णांकs.ai_family = AF_INET6;
		जाओ retry;
	पूर्ण

	करो_ipv4 &= have_ipv4;
	करो_ipv6 &= have_ipv6;
पूर्ण

अटल व्योम करो_listen(पूर्णांक family, व्योम *addr, पूर्णांक alen)
अणु
	पूर्णांक fd, type;

	type = cfg_proto == SOCK_RAW ? SOCK_DGRAM : cfg_proto;

	fd = socket(family, type, 0);
	अगर (fd == -1)
		error(1, त्रुटि_सं, "socket rx");

	अगर (bind(fd, addr, alen))
		error(1, त्रुटि_सं, "bind rx");

	अगर (type == SOCK_STREAM && listen(fd, 10))
		error(1, त्रुटि_सं, "listen rx");

	/* leave fd खोलो, will be बंदd on process निकास.
	 * this enables connect() to succeed and aव्योमs icmp replies
	 */
पूर्ण

अटल व्योम करो_मुख्य(पूर्णांक family)
अणु
	ख_लिखो(मानक_त्रुटि, "family:       %s %s\n",
			family == PF_INET ? "INET" : "INET6",
			cfg_use_pf_packet ? "(PF_PACKET)" : "");

	ख_लिखो(मानक_त्रुटि, "test SND\n");
	करो_test(family, SOF_TIMESTAMPING_TX_SOFTWARE);

	ख_लिखो(मानक_त्रुटि, "test ENQ\n");
	करो_test(family, SOF_TIMESTAMPING_TX_SCHED);

	ख_लिखो(मानक_त्रुटि, "test ENQ + SND\n");
	करो_test(family, SOF_TIMESTAMPING_TX_SCHED |
			SOF_TIMESTAMPING_TX_SOFTWARE);

	अगर (cfg_proto == SOCK_STREAM) अणु
		ख_लिखो(मानक_त्रुटि, "\ntest ACK\n");
		करो_test(family, SOF_TIMESTAMPING_TX_ACK);

		ख_लिखो(मानक_त्रुटि, "\ntest SND + ACK\n");
		करो_test(family, SOF_TIMESTAMPING_TX_SOFTWARE |
				SOF_TIMESTAMPING_TX_ACK);

		ख_लिखो(मानक_त्रुटि, "\ntest ENQ + SND + ACK\n");
		करो_test(family, SOF_TIMESTAMPING_TX_SCHED |
				SOF_TIMESTAMPING_TX_SOFTWARE |
				SOF_TIMESTAMPING_TX_ACK);
	पूर्ण
पूर्ण

स्थिर अक्षर *sock_names[] = अणु शून्य, "TCP", "UDP", "RAW" पूर्ण;

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अगर (argc == 1)
		usage(argv[0]);

	parse_opt(argc, argv);
	resolve_hostname(argv[argc - 1]);

	ख_लिखो(मानक_त्रुटि, "protocol:     %s\n", sock_names[cfg_proto]);
	ख_लिखो(मानक_त्रुटि, "payload:      %u\n", cfg_payload_len);
	ख_लिखो(मानक_त्रुटि, "server port:  %u\n", dest_port);
	ख_लिखो(मानक_त्रुटि, "\n");

	अगर (करो_ipv4) अणु
		अगर (cfg_करो_listen)
			करो_listen(PF_INET, &daddr, माप(daddr));
		करो_मुख्य(PF_INET);
	पूर्ण

	अगर (करो_ipv6) अणु
		अगर (cfg_करो_listen)
			करो_listen(PF_INET6, &daddr6, माप(daddr6));
		करो_मुख्य(PF_INET6);
	पूर्ण

	वापस test_failed;
पूर्ण
