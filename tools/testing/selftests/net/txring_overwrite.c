<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Verअगरy that consecutive sends over packet tx_ring are mirrored
 * with their original content पूर्णांकact.
 */

#घोषणा _GNU_SOURCE

#समावेश <arpa/inet.h>
#समावेश <निश्चित.स>
#समावेश <error.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <linux/filter.h>
#समावेश <linux/अगर_packet.h>
#समावेश <net/ethernet.h>
#समावेश <net/अगर.h>
#समावेश <netinet/in.h>
#समावेश <netinet/ip.h>
#समावेश <netinet/udp.h>
#समावेश <poll.h>
#समावेश <pthपढ़ो.h>
#समावेश <sched.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/mman.h>
#समावेश <sys/socket.h>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश <sys/utsname.h>
#समावेश <stdbool.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>

स्थिर पूर्णांक eth_off = TPACKET_HDRLEN - माप(काष्ठा sockaddr_ll);
स्थिर पूर्णांक cfg_frame_size = 1000;

अटल व्योम build_packet(व्योम *buffer, माप_प्रकार blen, अक्षर payload_अक्षर)
अणु
	काष्ठा udphdr *udph;
	काष्ठा ethhdr *eth;
	काष्ठा iphdr *iph;
	माप_प्रकार off = 0;

	स_रखो(buffer, 0, blen);

	eth = buffer;
	eth->h_proto = htons(ETH_P_IP);

	off += माप(*eth);
	iph = buffer + off;
	iph->ttl	= 8;
	iph->ihl	= 5;
	iph->version	= 4;
	iph->saddr	= htonl(INADDR_LOOPBACK);
	iph->daddr	= htonl(INADDR_LOOPBACK + 1);
	iph->protocol	= IPPROTO_UDP;
	iph->tot_len	= htons(blen - off);
	iph->check	= 0;

	off += माप(*iph);
	udph = buffer + off;
	udph->dest	= htons(8000);
	udph->source	= htons(8001);
	udph->len	= htons(blen - off);
	udph->check	= 0;

	off += माप(*udph);
	स_रखो(buffer + off, payload_अक्षर, blen - off);
पूर्ण

अटल पूर्णांक setup_rx(व्योम)
अणु
	पूर्णांक fdr;

	fdr = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP));
	अगर (fdr == -1)
		error(1, त्रुटि_सं, "socket r");

	वापस fdr;
पूर्ण

अटल पूर्णांक setup_tx(अक्षर **ring)
अणु
	काष्ठा sockaddr_ll laddr = अणुपूर्ण;
	काष्ठा tpacket_req req = अणुपूर्ण;
	पूर्णांक fdt;

	fdt = socket(PF_PACKET, SOCK_RAW, 0);
	अगर (fdt == -1)
		error(1, त्रुटि_सं, "socket t");

	laddr.sll_family = AF_PACKET;
	laddr.sll_protocol = htons(0);
	laddr.sll_अगरindex = अगर_nametoindex("lo");
	अगर (!laddr.sll_अगरindex)
		error(1, त्रुटि_सं, "if_nametoindex");

	अगर (bind(fdt, (व्योम *)&laddr, माप(laddr)))
		error(1, त्रुटि_सं, "bind fdt");

	req.tp_block_size = getpagesize();
	req.tp_block_nr   = 1;
	req.tp_frame_size = getpagesize();
	req.tp_frame_nr   = 1;

	अगर (setsockopt(fdt, SOL_PACKET, PACKET_TX_RING,
		       (व्योम *)&req, माप(req)))
		error(1, त्रुटि_सं, "setsockopt ring");

	*ring = mmap(0, req.tp_block_size * req.tp_block_nr,
		     PROT_READ | PROT_WRITE, MAP_SHARED, fdt, 0);
	अगर (*ring == MAP_FAILED)
		error(1, त्रुटि_सं, "mmap");

	वापस fdt;
पूर्ण

अटल व्योम send_pkt(पूर्णांक fdt, व्योम *slot, अक्षर payload_अक्षर)
अणु
	काष्ठा tpacket_hdr *header = slot;
	पूर्णांक ret;

	जबतक (header->tp_status != TP_STATUS_AVAILABLE)
		usleep(1000);

	build_packet(slot + eth_off, cfg_frame_size, payload_अक्षर);

	header->tp_len = cfg_frame_size;
	header->tp_status = TP_STATUS_SEND_REQUEST;

	ret = sendto(fdt, शून्य, 0, 0, शून्य, 0);
	अगर (ret == -1)
		error(1, त्रुटि_सं, "kick tx");
पूर्ण

अटल पूर्णांक पढ़ो_verअगरy_pkt(पूर्णांक fdr, अक्षर payload_अक्षर)
अणु
	अक्षर buf[100];
	पूर्णांक ret;

	ret = पढ़ो(fdr, buf, माप(buf));
	अगर (ret != माप(buf))
		error(1, त्रुटि_सं, "read");

	अगर (buf[60] != payload_अक्षर) अणु
		म_लिखो("wrong pattern: 0x%x != 0x%x\n", buf[60], payload_अक्षर);
		वापस 1;
	पूर्ण

	म_लिखो("read: %c (0x%x)\n", buf[60], buf[60]);
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर अक्षर payload_patterns[] = "ab";
	अक्षर *ring;
	पूर्णांक fdr, fdt, ret = 0;

	fdr = setup_rx();
	fdt = setup_tx(&ring);

	send_pkt(fdt, ring, payload_patterns[0]);
	send_pkt(fdt, ring, payload_patterns[1]);

	ret |= पढ़ो_verअगरy_pkt(fdr, payload_patterns[0]);
	ret |= पढ़ो_verअगरy_pkt(fdr, payload_patterns[1]);

	अगर (बंद(fdt))
		error(1, त्रुटि_सं, "close t");
	अगर (बंद(fdr))
		error(1, त्रुटि_सं, "close r");

	वापस ret;
पूर्ण
