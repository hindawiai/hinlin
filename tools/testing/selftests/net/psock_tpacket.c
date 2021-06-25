<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2013 Red Hat, Inc.
 * Author: Daniel Borkmann <dborkman@redhat.com>
 *         Chetan Loke <loke.chetan@gmail.com> (TPACKET_V3 usage example)
 *
 * A basic test of packet socket's TPACKET_V1/TPACKET_V2/TPACKET_V3 behavior.
 *
 * Control:
 *   Test the setup of the TPACKET socket with dअगरferent patterns that are
 *   known to fail (TODO) resp. succeed (OK).
 *
 * Datapath:
 *   Open a pair of packet sockets and send resp. receive an a priori known
 *   packet pattern accross the sockets and check अगर it was received resp.
 *   sent correctly. Fanout in combination with RX_RING is currently not
 *   tested here.
 *
 *   The test currently runs क्रम
 *   - TPACKET_V1: RX_RING, TX_RING
 *   - TPACKET_V2: RX_RING, TX_RING
 *   - TPACKET_V3: RX_RING
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/socket.h>
#समावेश <sys/mman.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/filter.h>
#समावेश <प्रकार.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <bits/wordsize.h>
#समावेश <net/ethernet.h>
#समावेश <netinet/ip.h>
#समावेश <arpa/inet.h>
#समावेश <मानक_निवेशt.h>
#समावेश <माला.स>
#समावेश <निश्चित.स>
#समावेश <net/अगर.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <poll.h>

#समावेश "psock_lib.h"

#समावेश "../kselftest.h"

#अगर_अघोषित bug_on
# define bug_on(cond)		निश्चित(!(cond))
#पूर्ण_अगर

#अगर_अघोषित __aligned_tpacket
# define __aligned_tpacket	__attribute__((aligned(TPACKET_ALIGNMENT)))
#पूर्ण_अगर

#अगर_अघोषित __align_tpacket
# define __align_tpacket(x)	__attribute__((aligned(TPACKET_ALIGN(x))))
#पूर्ण_अगर

#घोषणा NUM_PACKETS		100
#घोषणा ALIGN_8(x)		(((x) + 8 - 1) & ~(8 - 1))

काष्ठा ring अणु
	काष्ठा iovec *rd;
	uपूर्णांक8_t *mm_space;
	माप_प्रकार mm_len, rd_len;
	काष्ठा sockaddr_ll ll;
	व्योम (*walk)(पूर्णांक sock, काष्ठा ring *ring);
	पूर्णांक type, rd_num, flen, version;
	जोड़ अणु
		काष्ठा tpacket_req  req;
		काष्ठा tpacket_req3 req3;
	पूर्ण;
पूर्ण;

काष्ठा block_desc अणु
	uपूर्णांक32_t version;
	uपूर्णांक32_t offset_to_priv;
	काष्ठा tpacket_hdr_v1 h1;
पूर्ण;

जोड़ frame_map अणु
	काष्ठा अणु
		काष्ठा tpacket_hdr tp_h __aligned_tpacket;
		काष्ठा sockaddr_ll s_ll __align_tpacket(माप(काष्ठा tpacket_hdr));
	पूर्ण *v1;
	काष्ठा अणु
		काष्ठा tpacket2_hdr tp_h __aligned_tpacket;
		काष्ठा sockaddr_ll s_ll __align_tpacket(माप(काष्ठा tpacket2_hdr));
	पूर्ण *v2;
	व्योम *raw;
पूर्ण;

अटल अचिन्हित पूर्णांक total_packets, total_bytes;

अटल पूर्णांक pfsocket(पूर्णांक ver)
अणु
	पूर्णांक ret, sock = socket(PF_PACKET, SOCK_RAW, 0);
	अगर (sock == -1) अणु
		लिखो_त्रुटि("socket");
		निकास(1);
	पूर्ण

	ret = setsockopt(sock, SOL_PACKET, PACKET_VERSION, &ver, माप(ver));
	अगर (ret == -1) अणु
		लिखो_त्रुटि("setsockopt");
		निकास(1);
	पूर्ण

	वापस sock;
पूर्ण

अटल व्योम status_bar_update(व्योम)
अणु
	अगर (total_packets % 10 == 0) अणु
		ख_लिखो(मानक_त्रुटि, ".");
		ख_साफ(मानक_त्रुटि);
	पूर्ण
पूर्ण

अटल व्योम test_payload(व्योम *pay, माप_प्रकार len)
अणु
	काष्ठा ethhdr *eth = pay;

	अगर (len < माप(काष्ठा ethhdr)) अणु
		ख_लिखो(मानक_त्रुटि, "test_payload: packet too "
			"small: %zu bytes!\n", len);
		निकास(1);
	पूर्ण

	अगर (eth->h_proto != htons(ETH_P_IP)) अणु
		ख_लिखो(मानक_त्रुटि, "test_payload: wrong ethernet "
			"type: 0x%x!\n", ntohs(eth->h_proto));
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम create_payload(व्योम *pay, माप_प्रकार *len)
अणु
	पूर्णांक i;
	काष्ठा ethhdr *eth = pay;
	काष्ठा iphdr *ip = pay + माप(*eth);

	/* Lets create some broken crap, that still passes
	 * our BPF filter.
	 */

	*len = DATA_LEN + 42;

	स_रखो(pay, 0xff, ETH_ALEN * 2);
	eth->h_proto = htons(ETH_P_IP);

	क्रम (i = 0; i < माप(*ip); ++i)
		((uपूर्णांक8_t *) pay)[i + माप(*eth)] = (uपूर्णांक8_t) अक्रम();

	ip->ihl = 5;
	ip->version = 4;
	ip->protocol = 0x11;
	ip->frag_off = 0;
	ip->ttl = 64;
	ip->tot_len = htons((uपूर्णांक16_t) *len - माप(*eth));

	ip->saddr = htonl(INADDR_LOOPBACK);
	ip->daddr = htonl(INADDR_LOOPBACK);

	स_रखो(pay + माप(*eth) + माप(*ip),
	       DATA_CHAR, DATA_LEN);
पूर्ण

अटल अंतरभूत पूर्णांक __v1_rx_kernel_पढ़ोy(काष्ठा tpacket_hdr *hdr)
अणु
	वापस ((hdr->tp_status & TP_STATUS_USER) == TP_STATUS_USER);
पूर्ण

अटल अंतरभूत व्योम __v1_rx_user_पढ़ोy(काष्ठा tpacket_hdr *hdr)
अणु
	hdr->tp_status = TP_STATUS_KERNEL;
	__sync_synchronize();
पूर्ण

अटल अंतरभूत पूर्णांक __v2_rx_kernel_पढ़ोy(काष्ठा tpacket2_hdr *hdr)
अणु
	वापस ((hdr->tp_status & TP_STATUS_USER) == TP_STATUS_USER);
पूर्ण

अटल अंतरभूत व्योम __v2_rx_user_पढ़ोy(काष्ठा tpacket2_hdr *hdr)
अणु
	hdr->tp_status = TP_STATUS_KERNEL;
	__sync_synchronize();
पूर्ण

अटल अंतरभूत पूर्णांक __v1_v2_rx_kernel_पढ़ोy(व्योम *base, पूर्णांक version)
अणु
	चयन (version) अणु
	हाल TPACKET_V1:
		वापस __v1_rx_kernel_पढ़ोy(base);
	हाल TPACKET_V2:
		वापस __v2_rx_kernel_पढ़ोy(base);
	शेष:
		bug_on(1);
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __v1_v2_rx_user_पढ़ोy(व्योम *base, पूर्णांक version)
अणु
	चयन (version) अणु
	हाल TPACKET_V1:
		__v1_rx_user_पढ़ोy(base);
		अवरोध;
	हाल TPACKET_V2:
		__v2_rx_user_पढ़ोy(base);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम walk_v1_v2_rx(पूर्णांक sock, काष्ठा ring *ring)
अणु
	काष्ठा pollfd pfd;
	पूर्णांक udp_sock[2];
	जोड़ frame_map ppd;
	अचिन्हित पूर्णांक frame_num = 0;

	bug_on(ring->type != PACKET_RX_RING);

	pair_udp_खोलो(udp_sock, PORT_BASE);

	स_रखो(&pfd, 0, माप(pfd));
	pfd.fd = sock;
	pfd.events = POLLIN | POLLERR;
	pfd.revents = 0;

	pair_udp_send(udp_sock, NUM_PACKETS);

	जबतक (total_packets < NUM_PACKETS * 2) अणु
		जबतक (__v1_v2_rx_kernel_पढ़ोy(ring->rd[frame_num].iov_base,
					       ring->version)) अणु
			ppd.raw = ring->rd[frame_num].iov_base;

			चयन (ring->version) अणु
			हाल TPACKET_V1:
				test_payload((uपूर्णांक8_t *) ppd.raw + ppd.v1->tp_h.tp_mac,
					     ppd.v1->tp_h.tp_snaplen);
				total_bytes += ppd.v1->tp_h.tp_snaplen;
				अवरोध;

			हाल TPACKET_V2:
				test_payload((uपूर्णांक8_t *) ppd.raw + ppd.v2->tp_h.tp_mac,
					     ppd.v2->tp_h.tp_snaplen);
				total_bytes += ppd.v2->tp_h.tp_snaplen;
				अवरोध;
			पूर्ण

			status_bar_update();
			total_packets++;

			__v1_v2_rx_user_पढ़ोy(ppd.raw, ring->version);

			frame_num = (frame_num + 1) % ring->rd_num;
		पूर्ण

		poll(&pfd, 1, 1);
	पूर्ण

	pair_udp_बंद(udp_sock);

	अगर (total_packets != 2 * NUM_PACKETS) अणु
		ख_लिखो(मानक_त्रुटि, "walk_v%d_rx: received %u out of %u pkts\n",
			ring->version, total_packets, NUM_PACKETS);
		निकास(1);
	पूर्ण

	ख_लिखो(मानक_त्रुटि, " %u pkts (%u bytes)", NUM_PACKETS, total_bytes >> 1);
पूर्ण

अटल अंतरभूत पूर्णांक __v1_tx_kernel_पढ़ोy(काष्ठा tpacket_hdr *hdr)
अणु
	वापस !(hdr->tp_status & (TP_STATUS_SEND_REQUEST | TP_STATUS_SENDING));
पूर्ण

अटल अंतरभूत व्योम __v1_tx_user_पढ़ोy(काष्ठा tpacket_hdr *hdr)
अणु
	hdr->tp_status = TP_STATUS_SEND_REQUEST;
	__sync_synchronize();
पूर्ण

अटल अंतरभूत पूर्णांक __v2_tx_kernel_पढ़ोy(काष्ठा tpacket2_hdr *hdr)
अणु
	वापस !(hdr->tp_status & (TP_STATUS_SEND_REQUEST | TP_STATUS_SENDING));
पूर्ण

अटल अंतरभूत व्योम __v2_tx_user_पढ़ोy(काष्ठा tpacket2_hdr *hdr)
अणु
	hdr->tp_status = TP_STATUS_SEND_REQUEST;
	__sync_synchronize();
पूर्ण

अटल अंतरभूत पूर्णांक __v3_tx_kernel_पढ़ोy(काष्ठा tpacket3_hdr *hdr)
अणु
	वापस !(hdr->tp_status & (TP_STATUS_SEND_REQUEST | TP_STATUS_SENDING));
पूर्ण

अटल अंतरभूत व्योम __v3_tx_user_पढ़ोy(काष्ठा tpacket3_hdr *hdr)
अणु
	hdr->tp_status = TP_STATUS_SEND_REQUEST;
	__sync_synchronize();
पूर्ण

अटल अंतरभूत पूर्णांक __tx_kernel_पढ़ोy(व्योम *base, पूर्णांक version)
अणु
	चयन (version) अणु
	हाल TPACKET_V1:
		वापस __v1_tx_kernel_पढ़ोy(base);
	हाल TPACKET_V2:
		वापस __v2_tx_kernel_पढ़ोy(base);
	हाल TPACKET_V3:
		वापस __v3_tx_kernel_पढ़ोy(base);
	शेष:
		bug_on(1);
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __tx_user_पढ़ोy(व्योम *base, पूर्णांक version)
अणु
	चयन (version) अणु
	हाल TPACKET_V1:
		__v1_tx_user_पढ़ोy(base);
		अवरोध;
	हाल TPACKET_V2:
		__v2_tx_user_पढ़ोy(base);
		अवरोध;
	हाल TPACKET_V3:
		__v3_tx_user_पढ़ोy(base);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __v1_v2_set_packet_loss_discard(पूर्णांक sock)
अणु
	पूर्णांक ret, discard = 1;

	ret = setsockopt(sock, SOL_PACKET, PACKET_LOSS, (व्योम *) &discard,
			 माप(discard));
	अगर (ret == -1) अणु
		लिखो_त्रुटि("setsockopt");
		निकास(1);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम *get_next_frame(काष्ठा ring *ring, पूर्णांक n)
अणु
	uपूर्णांक8_t *f0 = ring->rd[0].iov_base;

	चयन (ring->version) अणु
	हाल TPACKET_V1:
	हाल TPACKET_V2:
		वापस ring->rd[n].iov_base;
	हाल TPACKET_V3:
		वापस f0 + (n * ring->req3.tp_frame_size);
	शेष:
		bug_on(1);
	पूर्ण
पूर्ण

अटल व्योम walk_tx(पूर्णांक sock, काष्ठा ring *ring)
अणु
	काष्ठा pollfd pfd;
	पूर्णांक rcv_sock, ret;
	माप_प्रकार packet_len;
	जोड़ frame_map ppd;
	अक्षर packet[1024];
	अचिन्हित पूर्णांक frame_num = 0, got = 0;
	काष्ठा sockaddr_ll ll = अणु
		.sll_family = PF_PACKET,
		.sll_halen = ETH_ALEN,
	पूर्ण;
	पूर्णांक nframes;

	/* TPACKET_Vअणु1,2पूर्ण sets up the ring->rd* related variables based
	 * on frames (e.g., rd_num is tp_frame_nr) whereas V3 sets these
	 * up based on blocks (e.g, rd_num is  tp_block_nr)
	 */
	अगर (ring->version <= TPACKET_V2)
		nframes = ring->rd_num;
	अन्यथा
		nframes = ring->req3.tp_frame_nr;

	bug_on(ring->type != PACKET_TX_RING);
	bug_on(nframes < NUM_PACKETS);

	rcv_sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	अगर (rcv_sock == -1) अणु
		लिखो_त्रुटि("socket");
		निकास(1);
	पूर्ण

	pair_udp_setfilter(rcv_sock);

	ll.sll_अगरindex = अगर_nametoindex("lo");
	ret = bind(rcv_sock, (काष्ठा sockaddr *) &ll, माप(ll));
	अगर (ret == -1) अणु
		लिखो_त्रुटि("bind");
		निकास(1);
	पूर्ण

	स_रखो(&pfd, 0, माप(pfd));
	pfd.fd = sock;
	pfd.events = POLLOUT | POLLERR;
	pfd.revents = 0;

	total_packets = NUM_PACKETS;
	create_payload(packet, &packet_len);

	जबतक (total_packets > 0) अणु
		व्योम *next = get_next_frame(ring, frame_num);

		जबतक (__tx_kernel_पढ़ोy(next, ring->version) &&
		       total_packets > 0) अणु
			ppd.raw = next;

			चयन (ring->version) अणु
			हाल TPACKET_V1:
				ppd.v1->tp_h.tp_snaplen = packet_len;
				ppd.v1->tp_h.tp_len = packet_len;

				स_नकल((uपूर्णांक8_t *) ppd.raw + TPACKET_HDRLEN -
				       माप(काष्ठा sockaddr_ll), packet,
				       packet_len);
				total_bytes += ppd.v1->tp_h.tp_snaplen;
				अवरोध;

			हाल TPACKET_V2:
				ppd.v2->tp_h.tp_snaplen = packet_len;
				ppd.v2->tp_h.tp_len = packet_len;

				स_नकल((uपूर्णांक8_t *) ppd.raw + TPACKET2_HDRLEN -
				       माप(काष्ठा sockaddr_ll), packet,
				       packet_len);
				total_bytes += ppd.v2->tp_h.tp_snaplen;
				अवरोध;
			हाल TPACKET_V3: अणु
				काष्ठा tpacket3_hdr *tx = next;

				tx->tp_snaplen = packet_len;
				tx->tp_len = packet_len;
				tx->tp_next_offset = 0;

				स_नकल((uपूर्णांक8_t *)tx + TPACKET3_HDRLEN -
				       माप(काष्ठा sockaddr_ll), packet,
				       packet_len);
				total_bytes += tx->tp_snaplen;
				अवरोध;
			पूर्ण
			पूर्ण

			status_bar_update();
			total_packets--;

			__tx_user_पढ़ोy(next, ring->version);

			frame_num = (frame_num + 1) % nframes;
		पूर्ण

		poll(&pfd, 1, 1);
	पूर्ण

	bug_on(total_packets != 0);

	ret = sendto(sock, शून्य, 0, 0, शून्य, 0);
	अगर (ret == -1) अणु
		लिखो_त्रुटि("sendto");
		निकास(1);
	पूर्ण

	जबतक ((ret = recvfrom(rcv_sock, packet, माप(packet),
			       0, शून्य, शून्य)) > 0 &&
	       total_packets < NUM_PACKETS) अणु
		got += ret;
		test_payload(packet, ret);

		status_bar_update();
		total_packets++;
	पूर्ण

	बंद(rcv_sock);

	अगर (total_packets != NUM_PACKETS) अणु
		ख_लिखो(मानक_त्रुटि, "walk_v%d_rx: received %u out of %u pkts\n",
			ring->version, total_packets, NUM_PACKETS);
		निकास(1);
	पूर्ण

	ख_लिखो(मानक_त्रुटि, " %u pkts (%u bytes)", NUM_PACKETS, got);
पूर्ण

अटल व्योम walk_v1_v2(पूर्णांक sock, काष्ठा ring *ring)
अणु
	अगर (ring->type == PACKET_RX_RING)
		walk_v1_v2_rx(sock, ring);
	अन्यथा
		walk_tx(sock, ring);
पूर्ण

अटल uपूर्णांक64_t __v3_prev_block_seq_num = 0;

व्योम __v3_test_block_seq_num(काष्ठा block_desc *pbd)
अणु
	अगर (__v3_prev_block_seq_num + 1 != pbd->h1.seq_num) अणु
		ख_लिखो(मानक_त्रुटि, "\nprev_block_seq_num:%"PRIu64", expected "
			"seq:%"PRIu64" != actual seq:%"PRIu64"\n",
			__v3_prev_block_seq_num, __v3_prev_block_seq_num + 1,
			(uपूर्णांक64_t) pbd->h1.seq_num);
		निकास(1);
	पूर्ण

	__v3_prev_block_seq_num = pbd->h1.seq_num;
पूर्ण

अटल व्योम __v3_test_block_len(काष्ठा block_desc *pbd, uपूर्णांक32_t bytes, पूर्णांक block_num)
अणु
	अगर (pbd->h1.num_pkts && bytes != pbd->h1.blk_len) अणु
		ख_लिखो(मानक_त्रुटि, "\nblock:%u with %upackets, expected "
			"len:%u != actual len:%u\n", block_num,
			pbd->h1.num_pkts, bytes, pbd->h1.blk_len);
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम __v3_test_block_header(काष्ठा block_desc *pbd, स्थिर पूर्णांक block_num)
अणु
	अगर ((pbd->h1.block_status & TP_STATUS_USER) == 0) अणु
		ख_लिखो(मानक_त्रुटि, "\nblock %u: not in TP_STATUS_USER\n", block_num);
		निकास(1);
	पूर्ण

	__v3_test_block_seq_num(pbd);
पूर्ण

अटल व्योम __v3_walk_block(काष्ठा block_desc *pbd, स्थिर पूर्णांक block_num)
अणु
	पूर्णांक num_pkts = pbd->h1.num_pkts, i;
	अचिन्हित दीर्घ bytes = 0, bytes_with_padding = ALIGN_8(माप(*pbd));
	काष्ठा tpacket3_hdr *ppd;

	__v3_test_block_header(pbd, block_num);

	ppd = (काष्ठा tpacket3_hdr *) ((uपूर्णांक8_t *) pbd +
				       pbd->h1.offset_to_first_pkt);

	क्रम (i = 0; i < num_pkts; ++i) अणु
		bytes += ppd->tp_snaplen;

		अगर (ppd->tp_next_offset)
			bytes_with_padding += ppd->tp_next_offset;
		अन्यथा
			bytes_with_padding += ALIGN_8(ppd->tp_snaplen + ppd->tp_mac);

		test_payload((uपूर्णांक8_t *) ppd + ppd->tp_mac, ppd->tp_snaplen);

		status_bar_update();
		total_packets++;

		ppd = (काष्ठा tpacket3_hdr *) ((uपूर्णांक8_t *) ppd + ppd->tp_next_offset);
		__sync_synchronize();
	पूर्ण

	__v3_test_block_len(pbd, bytes_with_padding, block_num);
	total_bytes += bytes;
पूर्ण

व्योम __v3_flush_block(काष्ठा block_desc *pbd)
अणु
	pbd->h1.block_status = TP_STATUS_KERNEL;
	__sync_synchronize();
पूर्ण

अटल व्योम walk_v3_rx(पूर्णांक sock, काष्ठा ring *ring)
अणु
	अचिन्हित पूर्णांक block_num = 0;
	काष्ठा pollfd pfd;
	काष्ठा block_desc *pbd;
	पूर्णांक udp_sock[2];

	bug_on(ring->type != PACKET_RX_RING);

	pair_udp_खोलो(udp_sock, PORT_BASE);

	स_रखो(&pfd, 0, माप(pfd));
	pfd.fd = sock;
	pfd.events = POLLIN | POLLERR;
	pfd.revents = 0;

	pair_udp_send(udp_sock, NUM_PACKETS);

	जबतक (total_packets < NUM_PACKETS * 2) अणु
		pbd = (काष्ठा block_desc *) ring->rd[block_num].iov_base;

		जबतक ((pbd->h1.block_status & TP_STATUS_USER) == 0)
			poll(&pfd, 1, 1);

		__v3_walk_block(pbd, block_num);
		__v3_flush_block(pbd);

		block_num = (block_num + 1) % ring->rd_num;
	पूर्ण

	pair_udp_बंद(udp_sock);

	अगर (total_packets != 2 * NUM_PACKETS) अणु
		ख_लिखो(मानक_त्रुटि, "walk_v3_rx: received %u out of %u pkts\n",
			total_packets, NUM_PACKETS);
		निकास(1);
	पूर्ण

	ख_लिखो(मानक_त्रुटि, " %u pkts (%u bytes)", NUM_PACKETS, total_bytes >> 1);
पूर्ण

अटल व्योम walk_v3(पूर्णांक sock, काष्ठा ring *ring)
अणु
	अगर (ring->type == PACKET_RX_RING)
		walk_v3_rx(sock, ring);
	अन्यथा
		walk_tx(sock, ring);
पूर्ण

अटल व्योम __v1_v2_fill(काष्ठा ring *ring, अचिन्हित पूर्णांक blocks)
अणु
	ring->req.tp_block_size = getpagesize() << 2;
	ring->req.tp_frame_size = TPACKET_ALIGNMENT << 7;
	ring->req.tp_block_nr = blocks;

	ring->req.tp_frame_nr = ring->req.tp_block_size /
				ring->req.tp_frame_size *
				ring->req.tp_block_nr;

	ring->mm_len = ring->req.tp_block_size * ring->req.tp_block_nr;
	ring->walk = walk_v1_v2;
	ring->rd_num = ring->req.tp_frame_nr;
	ring->flen = ring->req.tp_frame_size;
पूर्ण

अटल व्योम __v3_fill(काष्ठा ring *ring, अचिन्हित पूर्णांक blocks, पूर्णांक type)
अणु
	अगर (type == PACKET_RX_RING) अणु
		ring->req3.tp_retire_blk_tov = 64;
		ring->req3.tp_माप_priv = 0;
		ring->req3.tp_feature_req_word = TP_FT_REQ_FILL_RXHASH;
	पूर्ण
	ring->req3.tp_block_size = getpagesize() << 2;
	ring->req3.tp_frame_size = TPACKET_ALIGNMENT << 7;
	ring->req3.tp_block_nr = blocks;

	ring->req3.tp_frame_nr = ring->req3.tp_block_size /
				 ring->req3.tp_frame_size *
				 ring->req3.tp_block_nr;

	ring->mm_len = ring->req3.tp_block_size * ring->req3.tp_block_nr;
	ring->walk = walk_v3;
	ring->rd_num = ring->req3.tp_block_nr;
	ring->flen = ring->req3.tp_block_size;
पूर्ण

अटल व्योम setup_ring(पूर्णांक sock, काष्ठा ring *ring, पूर्णांक version, पूर्णांक type)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक blocks = 256;

	ring->type = type;
	ring->version = version;

	चयन (version) अणु
	हाल TPACKET_V1:
	हाल TPACKET_V2:
		अगर (type == PACKET_TX_RING)
			__v1_v2_set_packet_loss_discard(sock);
		__v1_v2_fill(ring, blocks);
		ret = setsockopt(sock, SOL_PACKET, type, &ring->req,
				 माप(ring->req));
		अवरोध;

	हाल TPACKET_V3:
		__v3_fill(ring, blocks, type);
		ret = setsockopt(sock, SOL_PACKET, type, &ring->req3,
				 माप(ring->req3));
		अवरोध;
	पूर्ण

	अगर (ret == -1) अणु
		लिखो_त्रुटि("setsockopt");
		निकास(1);
	पूर्ण

	ring->rd_len = ring->rd_num * माप(*ring->rd);
	ring->rd = दो_स्मृति(ring->rd_len);
	अगर (ring->rd == शून्य) अणु
		लिखो_त्रुटि("malloc");
		निकास(1);
	पूर्ण

	total_packets = 0;
	total_bytes = 0;
पूर्ण

अटल व्योम mmap_ring(पूर्णांक sock, काष्ठा ring *ring)
अणु
	पूर्णांक i;

	ring->mm_space = mmap(0, ring->mm_len, PROT_READ | PROT_WRITE,
			      MAP_SHARED | MAP_LOCKED | MAP_POPULATE, sock, 0);
	अगर (ring->mm_space == MAP_FAILED) अणु
		लिखो_त्रुटि("mmap");
		निकास(1);
	पूर्ण

	स_रखो(ring->rd, 0, ring->rd_len);
	क्रम (i = 0; i < ring->rd_num; ++i) अणु
		ring->rd[i].iov_base = ring->mm_space + (i * ring->flen);
		ring->rd[i].iov_len = ring->flen;
	पूर्ण
पूर्ण

अटल व्योम bind_ring(पूर्णांक sock, काष्ठा ring *ring)
अणु
	पूर्णांक ret;

	pair_udp_setfilter(sock);

	ring->ll.sll_family = PF_PACKET;
	ring->ll.sll_protocol = htons(ETH_P_ALL);
	ring->ll.sll_अगरindex = अगर_nametoindex("lo");
	ring->ll.sll_hatype = 0;
	ring->ll.sll_pkttype = 0;
	ring->ll.sll_halen = 0;

	ret = bind(sock, (काष्ठा sockaddr *) &ring->ll, माप(ring->ll));
	अगर (ret == -1) अणु
		लिखो_त्रुटि("bind");
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम walk_ring(पूर्णांक sock, काष्ठा ring *ring)
अणु
	ring->walk(sock, ring);
पूर्ण

अटल व्योम unmap_ring(पूर्णांक sock, काष्ठा ring *ring)
अणु
	munmap(ring->mm_space, ring->mm_len);
	मुक्त(ring->rd);
पूर्ण

अटल पूर्णांक test_kernel_bit_width(व्योम)
अणु
	अक्षर in[512], *ptr;
	पूर्णांक num = 0, fd;
	sमाप_प्रकार ret;

	fd = खोलो("/proc/kallsyms", O_RDONLY);
	अगर (fd == -1) अणु
		लिखो_त्रुटि("open");
		निकास(1);
	पूर्ण

	ret = पढ़ो(fd, in, माप(in));
	अगर (ret <= 0) अणु
		लिखो_त्रुटि("read");
		निकास(1);
	पूर्ण

	बंद(fd);

	ptr = in;
	जबतक(!है_खाली(*ptr)) अणु
		num++;
		ptr++;
	पूर्ण

	वापस num * 4;
पूर्ण

अटल पूर्णांक test_user_bit_width(व्योम)
अणु
	वापस __WORDSIZE;
पूर्ण

अटल स्थिर अक्षर *tpacket_str[] = अणु
	[TPACKET_V1] = "TPACKET_V1",
	[TPACKET_V2] = "TPACKET_V2",
	[TPACKET_V3] = "TPACKET_V3",
पूर्ण;

अटल स्थिर अक्षर *type_str[] = अणु
	[PACKET_RX_RING] = "PACKET_RX_RING",
	[PACKET_TX_RING] = "PACKET_TX_RING",
पूर्ण;

अटल पूर्णांक test_tpacket(पूर्णांक version, पूर्णांक type)
अणु
	पूर्णांक sock;
	काष्ठा ring ring;

	ख_लिखो(मानक_त्रुटि, "test: %s with %s ", tpacket_str[version],
		type_str[type]);
	ख_साफ(मानक_त्रुटि);

	अगर (version == TPACKET_V1 &&
	    test_kernel_bit_width() != test_user_bit_width()) अणु
		ख_लिखो(मानक_त्रुटि, "test: skip %s %s since user and kernel "
			"space have different bit width\n",
			tpacket_str[version], type_str[type]);
		वापस KSFT_SKIP;
	पूर्ण

	sock = pfsocket(version);
	स_रखो(&ring, 0, माप(ring));
	setup_ring(sock, &ring, version, type);
	mmap_ring(sock, &ring);
	bind_ring(sock, &ring);
	walk_ring(sock, &ring);
	unmap_ring(sock, &ring);
	बंद(sock);

	ख_लिखो(मानक_त्रुटि, "\n");
	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक ret = 0;

	ret |= test_tpacket(TPACKET_V1, PACKET_RX_RING);
	ret |= test_tpacket(TPACKET_V1, PACKET_TX_RING);

	ret |= test_tpacket(TPACKET_V2, PACKET_RX_RING);
	ret |= test_tpacket(TPACKET_V2, PACKET_TX_RING);

	ret |= test_tpacket(TPACKET_V3, PACKET_RX_RING);
	ret |= test_tpacket(TPACKET_V3, PACKET_TX_RING);

	अगर (ret)
		वापस 1;

	म_लिखो("OK. All tests passed\n");
	वापस 0;
पूर्ण
