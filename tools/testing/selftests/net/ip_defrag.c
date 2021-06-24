<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा _GNU_SOURCE

#समावेश <arpa/inet.h>
#समावेश <त्रुटिसं.स>
#समावेश <error.h>
#समावेश <linux/in.h>
#समावेश <netinet/ip.h>
#समावेश <netinet/ip6.h>
#समावेश <netinet/udp.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <समय.स>
#समावेश <unistd.h>

अटल bool		cfg_करो_ipv4;
अटल bool		cfg_करो_ipv6;
अटल bool		cfg_verbose;
अटल bool		cfg_overlap;
अटल bool		cfg_permissive;
अटल अचिन्हित लघु	cfg_port = 9000;

स्थिर काष्ठा in_addr addr4 = अणु .s_addr = __स्थिरant_htonl(INADDR_LOOPBACK + 2) पूर्ण;
स्थिर काष्ठा in6_addr addr6 = IN6ADDR_LOOPBACK_INIT;

#घोषणा IP4_HLEN	(माप(काष्ठा iphdr))
#घोषणा IP6_HLEN	(माप(काष्ठा ip6_hdr))
#घोषणा UDP_HLEN	(माप(काष्ठा udphdr))

/* IPv6 fragment header lenth. */
#घोषणा FRAG_HLEN	8

अटल पूर्णांक payload_len;
अटल पूर्णांक max_frag_len;

#घोषणा MSG_LEN_MAX	10000	/* Max UDP payload length. */

#घोषणा IP4_MF		(1u << 13)  /* IPv4 MF flag. */
#घोषणा IP6_MF		(1)  /* IPv6 MF flag. */

#घोषणा CSUM_MANGLED_0 (0xffff)

अटल uपूर्णांक8_t udp_payload[MSG_LEN_MAX];
अटल uपूर्णांक8_t ip_frame[IP_MAXPACKET];
अटल uपूर्णांक32_t ip_id = 0xabcd;
अटल पूर्णांक msg_counter;
अटल पूर्णांक frag_counter;
अटल अचिन्हित पूर्णांक seed;

/* Receive a UDP packet. Validate it matches udp_payload. */
अटल व्योम recv_validate_udp(पूर्णांक fd_udp)
अणु
	sमाप_प्रकार ret;
	अटल uपूर्णांक8_t recv_buff[MSG_LEN_MAX];

	ret = recv(fd_udp, recv_buff, payload_len, 0);
	msg_counter++;

	अगर (cfg_overlap) अणु
		अगर (ret == -1 && (त्रुटि_सं == ETIMEDOUT || त्रुटि_सं == EAGAIN))
			वापस;  /* OK */
		अगर (!cfg_permissive) अणु
			अगर (ret != -1)
				error(1, 0, "recv: expected timeout; got %d",
					(पूर्णांक)ret);
			error(1, त्रुटि_सं, "recv: expected timeout: %d", त्रुटि_सं);
		पूर्ण
	पूर्ण

	अगर (ret == -1)
		error(1, त्रुटि_सं, "recv: payload_len = %d max_frag_len = %d",
			payload_len, max_frag_len);
	अगर (ret != payload_len)
		error(1, 0, "recv: wrong size: %d vs %d", (पूर्णांक)ret, payload_len);
	अगर (स_भेद(udp_payload, recv_buff, payload_len))
		error(1, 0, "recv: wrong data");
पूर्ण

अटल uपूर्णांक32_t raw_checksum(uपूर्णांक8_t *buf, पूर्णांक len, uपूर्णांक32_t sum)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < (len & ~1U); i += 2) अणु
		sum += (u_पूर्णांक16_t)ntohs(*((u_पूर्णांक16_t *)(buf + i)));
		अगर (sum > 0xffff)
			sum -= 0xffff;
	पूर्ण

	अगर (i < len) अणु
		sum += buf[i] << 8;
		अगर (sum > 0xffff)
			sum -= 0xffff;
	पूर्ण

	वापस sum;
पूर्ण

अटल uपूर्णांक16_t udp_checksum(काष्ठा ip *iphdr, काष्ठा udphdr *udphdr)
अणु
	uपूर्णांक32_t sum = 0;
	uपूर्णांक16_t res;

	sum = raw_checksum((uपूर्णांक8_t *)&iphdr->ip_src, 2 * माप(iphdr->ip_src),
				IPPROTO_UDP + (uपूर्णांक32_t)(UDP_HLEN + payload_len));
	sum = raw_checksum((uपूर्णांक8_t *)udphdr, UDP_HLEN, sum);
	sum = raw_checksum((uपूर्णांक8_t *)udp_payload, payload_len, sum);
	res = 0xffff & ~sum;
	अगर (res)
		वापस htons(res);
	अन्यथा
		वापस CSUM_MANGLED_0;
पूर्ण

अटल uपूर्णांक16_t udp6_checksum(काष्ठा ip6_hdr *iphdr, काष्ठा udphdr *udphdr)
अणु
	uपूर्णांक32_t sum = 0;
	uपूर्णांक16_t res;

	sum = raw_checksum((uपूर्णांक8_t *)&iphdr->ip6_src, 2 * माप(iphdr->ip6_src),
				IPPROTO_UDP);
	sum = raw_checksum((uपूर्णांक8_t *)&udphdr->len, माप(udphdr->len), sum);
	sum = raw_checksum((uपूर्णांक8_t *)udphdr, UDP_HLEN, sum);
	sum = raw_checksum((uपूर्णांक8_t *)udp_payload, payload_len, sum);
	res = 0xffff & ~sum;
	अगर (res)
		वापस htons(res);
	अन्यथा
		वापस CSUM_MANGLED_0;
पूर्ण

अटल व्योम send_fragment(पूर्णांक fd_raw, काष्ठा sockaddr *addr, socklen_t alen,
				पूर्णांक offset, bool ipv6)
अणु
	पूर्णांक frag_len;
	पूर्णांक res;
	पूर्णांक payload_offset = offset > 0 ? offset - UDP_HLEN : 0;
	uपूर्णांक8_t *frag_start = ipv6 ? ip_frame + IP6_HLEN + FRAG_HLEN :
					ip_frame + IP4_HLEN;

	अगर (offset == 0) अणु
		काष्ठा udphdr udphdr;
		udphdr.source = htons(cfg_port + 1);
		udphdr.dest = htons(cfg_port);
		udphdr.len = htons(UDP_HLEN + payload_len);
		udphdr.check = 0;
		अगर (ipv6)
			udphdr.check = udp6_checksum((काष्ठा ip6_hdr *)ip_frame, &udphdr);
		अन्यथा
			udphdr.check = udp_checksum((काष्ठा ip *)ip_frame, &udphdr);
		स_नकल(frag_start, &udphdr, UDP_HLEN);
	पूर्ण

	अगर (ipv6) अणु
		काष्ठा ip6_hdr *ip6hdr = (काष्ठा ip6_hdr *)ip_frame;
		काष्ठा ip6_frag *fraghdr = (काष्ठा ip6_frag *)(ip_frame + IP6_HLEN);
		अगर (payload_len - payload_offset <= max_frag_len && offset > 0) अणु
			/* This is the last fragment. */
			frag_len = FRAG_HLEN + payload_len - payload_offset;
			fraghdr->ip6f_offlg = htons(offset);
		पूर्ण अन्यथा अणु
			frag_len = FRAG_HLEN + max_frag_len;
			fraghdr->ip6f_offlg = htons(offset | IP6_MF);
		पूर्ण
		ip6hdr->ip6_plen = htons(frag_len);
		अगर (offset == 0)
			स_नकल(frag_start + UDP_HLEN, udp_payload,
				frag_len - FRAG_HLEN - UDP_HLEN);
		अन्यथा
			स_नकल(frag_start, udp_payload + payload_offset,
				frag_len - FRAG_HLEN);
		frag_len += IP6_HLEN;
	पूर्ण अन्यथा अणु
		काष्ठा ip *iphdr = (काष्ठा ip *)ip_frame;
		अगर (payload_len - payload_offset <= max_frag_len && offset > 0) अणु
			/* This is the last fragment. */
			frag_len = IP4_HLEN + payload_len - payload_offset;
			iphdr->ip_off = htons(offset / 8);
		पूर्ण अन्यथा अणु
			frag_len = IP4_HLEN + max_frag_len;
			iphdr->ip_off = htons(offset / 8 | IP4_MF);
		पूर्ण
		iphdr->ip_len = htons(frag_len);
		अगर (offset == 0)
			स_नकल(frag_start + UDP_HLEN, udp_payload,
				frag_len - IP4_HLEN - UDP_HLEN);
		अन्यथा
			स_नकल(frag_start, udp_payload + payload_offset,
				frag_len - IP4_HLEN);
	पूर्ण

	res = sendto(fd_raw, ip_frame, frag_len, 0, addr, alen);
	अगर (res < 0 && त्रुटि_सं != EPERM)
		error(1, त्रुटि_सं, "send_fragment");
	अगर (res >= 0 && res != frag_len)
		error(1, 0, "send_fragment: %d vs %d", res, frag_len);

	frag_counter++;
पूर्ण

अटल व्योम send_udp_frags(पूर्णांक fd_raw, काष्ठा sockaddr *addr,
				socklen_t alen, bool ipv6)
अणु
	काष्ठा ip *iphdr = (काष्ठा ip *)ip_frame;
	काष्ठा ip6_hdr *ip6hdr = (काष्ठा ip6_hdr *)ip_frame;
	पूर्णांक res;
	पूर्णांक offset;
	पूर्णांक frag_len;

	/* Send the UDP datagram using raw IP fragments: the 0th fragment
	 * has the UDP header; other fragments are pieces of udp_payload
	 * split in chunks of frag_len size.
	 *
	 * Odd fragments (1st, 3rd, 5th, etc.) are sent out first, then
	 * even fragments (0th, 2nd, etc.) are sent out.
	 */
	अगर (ipv6) अणु
		काष्ठा ip6_frag *fraghdr = (काष्ठा ip6_frag *)(ip_frame + IP6_HLEN);
		((काष्ठा sockaddr_in6 *)addr)->sin6_port = 0;
		स_रखो(ip6hdr, 0, माप(*ip6hdr));
		ip6hdr->ip6_flow = htonl(6<<28);  /* Version. */
		ip6hdr->ip6_nxt = IPPROTO_FRAGMENT;
		ip6hdr->ip6_hops = 255;
		ip6hdr->ip6_src = addr6;
		ip6hdr->ip6_dst = addr6;
		fraghdr->ip6f_nxt = IPPROTO_UDP;
		fraghdr->ip6f_reserved = 0;
		fraghdr->ip6f_ident = htonl(ip_id++);
	पूर्ण अन्यथा अणु
		स_रखो(iphdr, 0, माप(*iphdr));
		iphdr->ip_hl = 5;
		iphdr->ip_v = 4;
		iphdr->ip_tos = 0;
		iphdr->ip_id = htons(ip_id++);
		iphdr->ip_ttl = 0x40;
		iphdr->ip_p = IPPROTO_UDP;
		iphdr->ip_src.s_addr = htonl(INADDR_LOOPBACK);
		iphdr->ip_dst = addr4;
		iphdr->ip_sum = 0;
	पूर्ण

	/* Occasionally test in-order fragments. */
	अगर (!cfg_overlap && (अक्रम() % 100 < 15)) अणु
		offset = 0;
		जबतक (offset < (UDP_HLEN + payload_len)) अणु
			send_fragment(fd_raw, addr, alen, offset, ipv6);
			offset += max_frag_len;
		पूर्ण
		वापस;
	पूर्ण

	/* Occasionally test IPv4 "runs" (see net/ipv4/ip_fragment.c) */
	अगर (!cfg_overlap && (अक्रम() % 100 < 20) &&
			(payload_len > 9 * max_frag_len)) अणु
		offset = 6 * max_frag_len;
		जबतक (offset < (UDP_HLEN + payload_len)) अणु
			send_fragment(fd_raw, addr, alen, offset, ipv6);
			offset += max_frag_len;
		पूर्ण
		offset = 3 * max_frag_len;
		जबतक (offset < 6 * max_frag_len) अणु
			send_fragment(fd_raw, addr, alen, offset, ipv6);
			offset += max_frag_len;
		पूर्ण
		offset = 0;
		जबतक (offset < 3 * max_frag_len) अणु
			send_fragment(fd_raw, addr, alen, offset, ipv6);
			offset += max_frag_len;
		पूर्ण
		वापस;
	पूर्ण

	/* Odd fragments. */
	offset = max_frag_len;
	जबतक (offset < (UDP_HLEN + payload_len)) अणु
		send_fragment(fd_raw, addr, alen, offset, ipv6);
		/* IPv4 ignores duplicates, so अक्रमomly send a duplicate. */
		अगर (अक्रम() % 100 == 1)
			send_fragment(fd_raw, addr, alen, offset, ipv6);
		offset += 2 * max_frag_len;
	पूर्ण

	अगर (cfg_overlap) अणु
		/* Send an extra अक्रमom fragment.
		 *
		 * Duplicates and some fragments completely inside
		 * previously sent fragments are dropped/ignored. So
		 * अक्रमom offset and frag_len can result in a dropped
		 * fragment instead of a dropped queue/packet. Thus we
		 * hard-code offset and frag_len.
		 */
		अगर (max_frag_len * 4 < payload_len || max_frag_len < 16) अणु
			/* not enough payload क्रम अक्रमom offset and frag_len. */
			offset = 8;
			frag_len = UDP_HLEN + max_frag_len;
		पूर्ण अन्यथा अणु
			offset = अक्रम() % (payload_len / 2);
			frag_len = 2 * max_frag_len + 1 + अक्रम() % 256;
		पूर्ण
		अगर (ipv6) अणु
			काष्ठा ip6_frag *fraghdr = (काष्ठा ip6_frag *)(ip_frame + IP6_HLEN);
			/* sendto() वापसs EINVAL अगर offset + frag_len is too small. */
			/* In IPv6 अगर !!(frag_len % 8), the fragment is dropped. */
			frag_len &= ~0x7;
			fraghdr->ip6f_offlg = htons(offset / 8 | IP6_MF);
			ip6hdr->ip6_plen = htons(frag_len);
			frag_len += IP6_HLEN;
		पूर्ण अन्यथा अणु
			frag_len += IP4_HLEN;
			iphdr->ip_off = htons(offset / 8 | IP4_MF);
			iphdr->ip_len = htons(frag_len);
		पूर्ण
		res = sendto(fd_raw, ip_frame, frag_len, 0, addr, alen);
		अगर (res < 0 && त्रुटि_सं != EPERM)
			error(1, त्रुटि_सं, "sendto overlap: %d", frag_len);
		अगर (res >= 0 && res != frag_len)
			error(1, 0, "sendto overlap: %d vs %d", (पूर्णांक)res, frag_len);
		frag_counter++;
	पूर्ण

	/* Event fragments. */
	offset = 0;
	जबतक (offset < (UDP_HLEN + payload_len)) अणु
		send_fragment(fd_raw, addr, alen, offset, ipv6);
		/* IPv4 ignores duplicates, so अक्रमomly send a duplicate. */
		अगर (अक्रम() % 100 == 1)
			send_fragment(fd_raw, addr, alen, offset, ipv6);
		offset += 2 * max_frag_len;
	पूर्ण
पूर्ण

अटल व्योम run_test(काष्ठा sockaddr *addr, socklen_t alen, bool ipv6)
अणु
	पूर्णांक fd_tx_raw, fd_rx_udp;
	/* Frag queue समयout is set to one second in the calling script;
	 * socket समयout should be just a bit दीर्घer to aव्योम tests पूर्णांकerfering
	 * with each other.
	 */
	काष्ठा समयval tv = अणु .tv_sec = 1, .tv_usec = 10 पूर्ण;
	पूर्णांक idx;
	पूर्णांक min_frag_len = 8;

	/* Initialize the payload. */
	क्रम (idx = 0; idx < MSG_LEN_MAX; ++idx)
		udp_payload[idx] = idx % 256;

	/* Open sockets. */
	fd_tx_raw = socket(addr->sa_family, SOCK_RAW, IPPROTO_RAW);
	अगर (fd_tx_raw == -1)
		error(1, त्रुटि_सं, "socket tx_raw");

	fd_rx_udp = socket(addr->sa_family, SOCK_DGRAM, 0);
	अगर (fd_rx_udp == -1)
		error(1, त्रुटि_सं, "socket rx_udp");
	अगर (bind(fd_rx_udp, addr, alen))
		error(1, त्रुटि_सं, "bind");
	/* Fail fast. */
	अगर (setsockopt(fd_rx_udp, SOL_SOCKET, SO_RCVTIMEO, &tv, माप(tv)))
		error(1, त्रुटि_सं, "setsockopt rcv timeout");

	क्रम (payload_len = min_frag_len; payload_len < MSG_LEN_MAX;
			payload_len += (अक्रम() % 4096)) अणु
		अगर (cfg_verbose)
			म_लिखो("payload_len: %d\n", payload_len);

		अगर (cfg_overlap) अणु
			/* With overlaps, one send/receive pair below takes
			 * at least one second (== समयout) to run, so there
			 * is not enough test समय to run a nested loop:
			 * the full overlap test takes 20-30 seconds.
			 */
			max_frag_len = min_frag_len +
				अक्रम() % (1500 - FRAG_HLEN - min_frag_len);
			send_udp_frags(fd_tx_raw, addr, alen, ipv6);
			recv_validate_udp(fd_rx_udp);
		पूर्ण अन्यथा अणु
			/* Without overlaps, each packet reassembly (== one
			 * send/receive pair below) takes very little समय to
			 * run, so we can easily afक्रमd more thourough testing
			 * with a nested loop: the full non-overlap test takes
			 * less than one second).
			 */
			max_frag_len = min_frag_len;
			करो अणु
				send_udp_frags(fd_tx_raw, addr, alen, ipv6);
				recv_validate_udp(fd_rx_udp);
				max_frag_len += 8 * (अक्रम() % 8);
			पूर्ण जबतक (max_frag_len < (1500 - FRAG_HLEN) &&
				 max_frag_len <= payload_len);
		पूर्ण
	पूर्ण

	/* Cleanup. */
	अगर (बंद(fd_tx_raw))
		error(1, त्रुटि_सं, "close tx_raw");
	अगर (बंद(fd_rx_udp))
		error(1, त्रुटि_सं, "close rx_udp");

	अगर (cfg_verbose)
		म_लिखो("processed %d messages, %d fragments\n",
			msg_counter, frag_counter);

	ख_लिखो(मानक_त्रुटि, "PASS\n");
पूर्ण


अटल व्योम run_test_v4(व्योम)
अणु
	काष्ठा sockaddr_in addr = अणु0पूर्ण;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(cfg_port);
	addr.sin_addr = addr4;

	run_test((व्योम *)&addr, माप(addr), false /* !ipv6 */);
पूर्ण

अटल व्योम run_test_v6(व्योम)
अणु
	काष्ठा sockaddr_in6 addr = अणु0पूर्ण;

	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(cfg_port);
	addr.sin6_addr = addr6;

	run_test((व्योम *)&addr, माप(addr), true /* ipv6 */);
पूर्ण

अटल व्योम parse_opts(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक c;

	जबतक ((c = getopt(argc, argv, "46opv")) != -1) अणु
		चयन (c) अणु
		हाल '4':
			cfg_करो_ipv4 = true;
			अवरोध;
		हाल '6':
			cfg_करो_ipv6 = true;
			अवरोध;
		हाल 'o':
			cfg_overlap = true;
			अवरोध;
		हाल 'p':
			cfg_permissive = true;
			अवरोध;
		हाल 'v':
			cfg_verbose = true;
			अवरोध;
		शेष:
			error(1, 0, "%s: parse error", argv[0]);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	parse_opts(argc, argv);
	seed = समय(शून्य);
	बेक्रम(seed);
	/* Prपूर्णांक the seed to track/reproduce potential failures. */
	म_लिखो("seed = %d\n", seed);

	अगर (cfg_करो_ipv4)
		run_test_v4();
	अगर (cfg_करो_ipv6)
		run_test_v6();

	वापस 0;
पूर्ण
