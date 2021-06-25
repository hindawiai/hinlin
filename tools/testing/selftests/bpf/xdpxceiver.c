<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2020 Intel Corporation. */

/*
 * Some functions in this program are taken from
 * Linux kernel samples/bpf/xdpsock* and modअगरied
 * क्रम use.
 *
 * See test_xsk.sh क्रम detailed inक्रमmation on test topology
 * and prerequisite network setup.
 *
 * This test program contains two thपढ़ोs, each thपढ़ो is single socket with
 * a unique UMEM. It validates in-order packet delivery and packet content
 * by sending packets to each other.
 *
 * Tests Inक्रमmation:
 * ------------------
 * These selftests test AF_XDP SKB and Native/DRV modes using veth
 * Virtual Ethernet पूर्णांकerfaces.
 *
 * For each mode, the following tests are run:
 *    a. nopoll - soft-irq processing
 *    b. poll - using poll() syscall
 *    c. Socket Tearकरोwn
 *       Create a Tx and a Rx socket, Tx from one socket, Rx on another. Destroy
 *       both sockets, then repeat multiple बार. Only nopoll mode is used
 *    d. Bi-directional sockets
 *       Configure sockets as bi-directional tx/rx sockets, sets up fill and
 *       completion rings on each socket, tx/rx in both directions. Only nopoll
 *       mode is used
 *    e. Statistics
 *       Trigger some error conditions and ensure that the appropriate statistics
 *       are incremented. Within this test, the following statistics are tested:
 *       i.   rx dropped
 *            Increase the UMEM frame headroom to a value which results in
 *            insufficient space in the rx buffer क्रम both the packet and the headroom.
 *       ii.  tx invalid
 *            Set the 'len' field of tx descriptors to an invalid value (umem frame
 *            size + 1).
 *       iii. rx ring full
 *            Reduce the size of the RX ring to a fraction of the fill ring size.
 *       iv.  fill queue empty
 *            Do not populate the fill queue and then try to receive pkts.
 *    f. bpf_link resource persistence
 *       Configure sockets at indexes 0 and 1, run a traffic on queue ids 0,
 *       then हटाओ xsk sockets from queue 0 on both veth पूर्णांकerfaces and
 *       finally run a traffic on queues ids 1
 *
 * Total tests: 12
 *
 * Flow:
 * -----
 * - Single process spawns two thपढ़ोs: Tx and Rx
 * - Each of these two thपढ़ोs attach to a veth पूर्णांकerface within their asचिन्हित
 *   namespaces
 * - Each thपढ़ो Creates one AF_XDP socket connected to a unique umem क्रम each
 *   veth पूर्णांकerface
 * - Tx thपढ़ो Transmits 10k packets from veth<xxxx> to veth<yyyy>
 * - Rx thपढ़ो verअगरies अगर all 10k packets were received and delivered in-order,
 *   and have the right content
 *
 * Enable/disable packet dump mode:
 * --------------------------
 * To enable L2 - L4 headers and payload dump of each packet on STDOUT, add
 * parameter -D to params array in test_xsk.sh, i.e. params=("-S" "-D")
 */

#घोषणा _GNU_SOURCE
#समावेश <fcntl.h>
#समावेश <त्रुटिसं.स>
#समावेश <getopt.h>
#समावेश <यंत्र/barrier.h>
प्रकार __u16 __sum16;
#समावेश <linux/अगर_link.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/ip.h>
#समावेश <linux/udp.h>
#समावेश <arpa/inet.h>
#समावेश <net/अगर.h>
#समावेश <क्षेत्र.स>
#समावेश <poll.h>
#समावेश <pthपढ़ो.h>
#समावेश <संकेत.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानकघोष.स>
#समावेश <sys/mman.h>
#समावेश <sys/resource.h>
#समावेश <sys/types.h>
#समावेश <sys/queue.h>
#समावेश <समय.स>
#समावेश <unistd.h>
#समावेश <stdatomic.h>
#समावेश <bpf/xsk.h>
#समावेश "xdpxceiver.h"
#समावेश "../kselftest.h"

अटल स्थिर अक्षर *MAC1 = "\x00\x0A\x56\x9E\xEE\x62";
अटल स्थिर अक्षर *MAC2 = "\x00\x0A\x56\x9E\xEE\x61";
अटल स्थिर अक्षर *IP1 = "192.168.100.162";
अटल स्थिर अक्षर *IP2 = "192.168.100.161";
अटल स्थिर u16 UDP_PORT1 = 2020;
अटल स्थिर u16 UDP_PORT2 = 2121;

अटल व्योम __निकास_with_error(पूर्णांक error, स्थिर अक्षर *file, स्थिर अक्षर *func, पूर्णांक line)
अणु
	अगर (configured_mode == TEST_MODE_UNCONFIGURED) अणु
		ksft_निकास_fail_msg
		("[%s:%s:%i]: ERROR: %d/\"%s\"\n", file, func, line, error, म_त्रुटि(error));
	पूर्ण अन्यथा अणु
		ksft_test_result_fail
		("[%s:%s:%i]: ERROR: %d/\"%s\"\n", file, func, line, error, म_त्रुटि(error));
		ksft_निकास_xfail();
	पूर्ण
पूर्ण

#घोषणा निकास_with_error(error) __निकास_with_error(error, __खाता__, __func__, __LINE__)

#घोषणा prपूर्णांक_ksft_result(व्योम)\
	(ksft_test_result_pass("PASS: %s %s %s%s%s%s\n", configured_mode ? "DRV" : "SKB",\
			       test_type == TEST_TYPE_POLL ? "POLL" : "NOPOLL",\
			       test_type == TEST_TYPE_TEARDOWN ? "Socket Teardown" : "",\
			       test_type == TEST_TYPE_BIDI ? "Bi-directional Sockets" : "",\
			       test_type == TEST_TYPE_STATS ? "Stats" : "",\
			       test_type == TEST_TYPE_BPF_RES ? "BPF RES" : ""))

अटल व्योम *स_रखो32_htonl(व्योम *dest, u32 val, u32 size)
अणु
	u32 *ptr = (u32 *)dest;
	पूर्णांक i;

	val = htonl(val);

	क्रम (i = 0; i < (size & (~0x3)); i += 4)
		ptr[i >> 2] = val;

	क्रम (; i < size; i++)
		((अक्षर *)dest)[i] = ((अक्षर *)&val)[i & 3];

	वापस dest;
पूर्ण

/*
 * Fold a partial checksum
 * This function code has been taken from
 * Linux kernel include/यंत्र-generic/checksum.h
 */
अटल __u16 csum_fold(__u32 csum)
अणु
	u32 sum = (__क्रमce u32)csum;

	sum = (sum & 0xffff) + (sum >> 16);
	sum = (sum & 0xffff) + (sum >> 16);
	वापस (__क्रमce __u16)~sum;
पूर्ण

/*
 * This function code has been taken from
 * Linux kernel lib/checksum.c
 */
अटल u32 from64to32(u64 x)
अणु
	/* add up 32-bit and 32-bit क्रम 32+c bit */
	x = (x & 0xffffffff) + (x >> 32);
	/* add up carry.. */
	x = (x & 0xffffffff) + (x >> 32);
	वापस (u32)x;
पूर्ण

/*
 * This function code has been taken from
 * Linux kernel lib/checksum.c
 */
अटल __u32 csum_tcpudp_nofold(__be32 saddr, __be32 daddr, __u32 len, __u8 proto, __u32 sum)
अणु
	अचिन्हित दीर्घ दीर्घ s = (__क्रमce u32)sum;

	s += (__क्रमce u32)saddr;
	s += (__क्रमce u32)daddr;
#अगर_घोषित __BIG_ENDIAN__
	s += proto + len;
#अन्यथा
	s += (proto + len) << 8;
#पूर्ण_अगर
	वापस (__क्रमce __u32)from64to32(s);
पूर्ण

/*
 * This function has been taken from
 * Linux kernel include/यंत्र-generic/checksum.h
 */
अटल __u16 csum_tcpudp_magic(__be32 saddr, __be32 daddr, __u32 len, __u8 proto, __u32 sum)
अणु
	वापस csum_fold(csum_tcpudp_nofold(saddr, daddr, len, proto, sum));
पूर्ण

अटल u16 udp_csum(u32 saddr, u32 daddr, u32 len, u8 proto, u16 *udp_pkt)
अणु
	u32 csum = 0;
	u32 cnt = 0;

	/* udp hdr and data */
	क्रम (; cnt < len; cnt += 2)
		csum += udp_pkt[cnt >> 1];

	वापस csum_tcpudp_magic(saddr, daddr, len, proto, csum);
पूर्ण

अटल व्योम gen_eth_hdr(काष्ठा अगरobject *अगरobject, काष्ठा ethhdr *eth_hdr)
अणु
	स_नकल(eth_hdr->h_dest, अगरobject->dst_mac, ETH_ALEN);
	स_नकल(eth_hdr->h_source, अगरobject->src_mac, ETH_ALEN);
	eth_hdr->h_proto = htons(ETH_P_IP);
पूर्ण

अटल व्योम gen_ip_hdr(काष्ठा अगरobject *अगरobject, काष्ठा iphdr *ip_hdr)
अणु
	ip_hdr->version = IP_PKT_VER;
	ip_hdr->ihl = 0x5;
	ip_hdr->tos = IP_PKT_TOS;
	ip_hdr->tot_len = htons(IP_PKT_SIZE);
	ip_hdr->id = 0;
	ip_hdr->frag_off = 0;
	ip_hdr->ttl = IPDEFTTL;
	ip_hdr->protocol = IPPROTO_UDP;
	ip_hdr->saddr = अगरobject->src_ip;
	ip_hdr->daddr = अगरobject->dst_ip;
	ip_hdr->check = 0;
पूर्ण

अटल व्योम gen_udp_hdr(काष्ठा generic_data *data, काष्ठा अगरobject *अगरobject,
			काष्ठा udphdr *udp_hdr)
अणु
	udp_hdr->source = htons(अगरobject->src_port);
	udp_hdr->dest = htons(अगरobject->dst_port);
	udp_hdr->len = htons(UDP_PKT_SIZE);
	स_रखो32_htonl(pkt_data + PKT_HDR_SIZE, htonl(data->seqnum), UDP_PKT_DATA_SIZE);
पूर्ण

अटल व्योम gen_udp_csum(काष्ठा udphdr *udp_hdr, काष्ठा iphdr *ip_hdr)
अणु
	udp_hdr->check = 0;
	udp_hdr->check =
	    udp_csum(ip_hdr->saddr, ip_hdr->daddr, UDP_PKT_SIZE, IPPROTO_UDP, (u16 *)udp_hdr);
पूर्ण

अटल व्योम gen_eth_frame(काष्ठा xsk_umem_info *umem, u64 addr)
अणु
	स_नकल(xsk_umem__get_data(umem->buffer, addr), pkt_data, PKT_SIZE);
पूर्ण

अटल व्योम xsk_configure_umem(काष्ठा अगरobject *data, व्योम *buffer, पूर्णांक idx)
अणु
	काष्ठा xsk_umem_config cfg = अणु
		.fill_size = XSK_RING_PROD__DEFAULT_NUM_DESCS,
		.comp_size = XSK_RING_CONS__DEFAULT_NUM_DESCS,
		.frame_size = XSK_UMEM__DEFAULT_FRAME_SIZE,
		.frame_headroom = frame_headroom,
		.flags = XSK_UMEM__DEFAULT_FLAGS
	पूर्ण;
	पूर्णांक size = num_frames * XSK_UMEM__DEFAULT_FRAME_SIZE;
	काष्ठा xsk_umem_info *umem;
	पूर्णांक ret;

	umem = सुस्मृति(1, माप(काष्ठा xsk_umem_info));
	अगर (!umem)
		निकास_with_error(त्रुटि_सं);

	ret = xsk_umem__create(&umem->umem, buffer, size,
			       &umem->fq, &umem->cq, &cfg);
	अगर (ret)
		निकास_with_error(ret);

	umem->buffer = buffer;

	data->umem_arr[idx] = umem;
पूर्ण

अटल व्योम xsk_populate_fill_ring(काष्ठा xsk_umem_info *umem)
अणु
	पूर्णांक ret, i;
	u32 idx = 0;

	ret = xsk_ring_prod__reserve(&umem->fq, XSK_RING_PROD__DEFAULT_NUM_DESCS, &idx);
	अगर (ret != XSK_RING_PROD__DEFAULT_NUM_DESCS)
		निकास_with_error(ret);
	क्रम (i = 0; i < XSK_RING_PROD__DEFAULT_NUM_DESCS; i++)
		*xsk_ring_prod__fill_addr(&umem->fq, idx++) = i * XSK_UMEM__DEFAULT_FRAME_SIZE;
	xsk_ring_prod__submit(&umem->fq, XSK_RING_PROD__DEFAULT_NUM_DESCS);
पूर्ण

अटल पूर्णांक xsk_configure_socket(काष्ठा अगरobject *अगरobject, पूर्णांक idx)
अणु
	काष्ठा xsk_socket_config cfg;
	काष्ठा xsk_socket_info *xsk;
	काष्ठा xsk_ring_cons *rxr;
	काष्ठा xsk_ring_prod *txr;
	पूर्णांक ret;

	xsk = सुस्मृति(1, माप(काष्ठा xsk_socket_info));
	अगर (!xsk)
		निकास_with_error(त्रुटि_सं);

	xsk->umem = अगरobject->umem;
	cfg.rx_size = rxqsize;
	cfg.tx_size = XSK_RING_PROD__DEFAULT_NUM_DESCS;
	cfg.libbpf_flags = 0;
	cfg.xdp_flags = xdp_flags;
	cfg.bind_flags = xdp_bind_flags;

	अगर (test_type != TEST_TYPE_BIDI) अणु
		rxr = (अगरobject->fv.vector == rx) ? &xsk->rx : शून्य;
		txr = (अगरobject->fv.vector == tx) ? &xsk->tx : शून्य;
	पूर्ण अन्यथा अणु
		rxr = &xsk->rx;
		txr = &xsk->tx;
	पूर्ण

	ret = xsk_socket__create(&xsk->xsk, अगरobject->अगरname, idx,
				 अगरobject->umem->umem, rxr, txr, &cfg);
	अगर (ret)
		वापस 1;

	अगरobject->xsk_arr[idx] = xsk;

	वापस 0;
पूर्ण

अटल काष्ठा option दीर्घ_options[] = अणु
	अणु"interface", required_argument, 0, 'i'पूर्ण,
	अणु"queue", optional_argument, 0, 'q'पूर्ण,
	अणु"dump-pkts", optional_argument, 0, 'D'पूर्ण,
	अणु"verbose", no_argument, 0, 'v'पूर्ण,
	अणु"tx-pkt-count", optional_argument, 0, 'C'पूर्ण,
	अणु0, 0, 0, 0पूर्ण
पूर्ण;

अटल व्योम usage(स्थिर अक्षर *prog)
अणु
	स्थिर अक्षर *str =
	    "  Usage: %s [OPTIONS]\n"
	    "  Options:\n"
	    "  -i, --interface      Use interface\n"
	    "  -q, --queue=n        Use queue n (default 0)\n"
	    "  -D, --dump-pkts      Dump packets L2 - L5\n"
	    "  -v, --verbose        Verbose output\n"
	    "  -C, --tx-pkt-count=n Number of packets to send\n";
	ksft_prपूर्णांक_msg(str, prog);
पूर्ण

अटल पूर्णांक चयन_namespace(स्थिर अक्षर *nsname)
अणु
	अक्षर fqns[26] = "/var/run/netns/";
	पूर्णांक nsfd;

	अगर (!nsname || म_माप(nsname) == 0)
		वापस -1;

	म_जोड़न(fqns, nsname, माप(fqns) - म_माप(fqns) - 1);
	nsfd = खोलो(fqns, O_RDONLY);

	अगर (nsfd == -1)
		निकास_with_error(त्रुटि_सं);

	अगर (setns(nsfd, 0) == -1)
		निकास_with_error(त्रुटि_सं);

	prपूर्णांक_verbose("NS switched: %s\n", nsname);

	वापस nsfd;
पूर्ण

अटल पूर्णांक validate_पूर्णांकerfaces(व्योम)
अणु
	bool ret = true;

	क्रम (पूर्णांक i = 0; i < MAX_INTERFACES; i++) अणु
		अगर (!म_भेद(अगरdict[i]->अगरname, "")) अणु
			ret = false;
			ksft_test_result_fail("ERROR: interfaces: -i <int>,<ns> -i <int>,<ns>.");
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम parse_command_line(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक option_index, पूर्णांकerface_index = 0, c;

	opterr = 0;

	क्रम (;;) अणु
		c = getopt_दीर्घ(argc, argv, "i:DC:v", दीर्घ_options, &option_index);

		अगर (c == -1)
			अवरोध;

		चयन (c) अणु
		हाल 'i':
			अगर (पूर्णांकerface_index == MAX_INTERFACES)
				अवरोध;
			अक्षर *sptr, *token;

			sptr = strndupa(optarg, म_माप(optarg));
			स_नकल(अगरdict[पूर्णांकerface_index]->अगरname,
			       strsep(&sptr, ","), MAX_INTERFACE_NAME_CHARS);
			token = strsep(&sptr, ",");
			अगर (token)
				स_नकल(अगरdict[पूर्णांकerface_index]->nsname, token,
				       MAX_INTERFACES_NAMESPACE_CHARS);
			पूर्णांकerface_index++;
			अवरोध;
		हाल 'D':
			debug_pkt_dump = 1;
			अवरोध;
		हाल 'C':
			opt_pkt_count = म_से_प(optarg);
			अवरोध;
		हाल 'v':
			opt_verbose = 1;
			अवरोध;
		शेष:
			usage(basename(argv[0]));
			ksft_निकास_xfail();
		पूर्ण
	पूर्ण

	अगर (!opt_pkt_count) अणु
		prपूर्णांक_verbose("No tx-pkt-count specified, using default %u\n", DEFAULT_PKT_CNT);
		opt_pkt_count = DEFAULT_PKT_CNT;
	पूर्ण

	अगर (!validate_पूर्णांकerfaces()) अणु
		usage(basename(argv[0]));
		ksft_निकास_xfail();
	पूर्ण
पूर्ण

अटल व्योम kick_tx(काष्ठा xsk_socket_info *xsk)
अणु
	पूर्णांक ret;

	ret = sendto(xsk_socket__fd(xsk->xsk), शून्य, 0, MSG_DONTWAIT, शून्य, 0);
	अगर (ret >= 0 || त्रुटि_सं == ENOBUFS || त्रुटि_सं == EAGAIN || त्रुटि_सं == EBUSY || त्रुटि_सं == ENETDOWN)
		वापस;
	निकास_with_error(त्रुटि_सं);
पूर्ण

अटल व्योम complete_tx_only(काष्ठा xsk_socket_info *xsk, पूर्णांक batch_size)
अणु
	अचिन्हित पूर्णांक rcvd;
	u32 idx;

	अगर (!xsk->outstanding_tx)
		वापस;

	अगर (xsk_ring_prod__needs_wakeup(&xsk->tx))
		kick_tx(xsk);

	rcvd = xsk_ring_cons__peek(&xsk->umem->cq, batch_size, &idx);
	अगर (rcvd) अणु
		xsk_ring_cons__release(&xsk->umem->cq, rcvd);
		xsk->outstanding_tx -= rcvd;
		xsk->tx_npkts += rcvd;
	पूर्ण
पूर्ण

अटल व्योम rx_pkt(काष्ठा xsk_socket_info *xsk, काष्ठा pollfd *fds)
अणु
	अचिन्हित पूर्णांक rcvd, i;
	u32 idx_rx = 0, idx_fq = 0;
	पूर्णांक ret;

	rcvd = xsk_ring_cons__peek(&xsk->rx, BATCH_SIZE, &idx_rx);
	अगर (!rcvd) अणु
		अगर (xsk_ring_prod__needs_wakeup(&xsk->umem->fq)) अणु
			ret = poll(fds, 1, POLL_TMOUT);
			अगर (ret < 0)
				निकास_with_error(ret);
		पूर्ण
		वापस;
	पूर्ण

	ret = xsk_ring_prod__reserve(&xsk->umem->fq, rcvd, &idx_fq);
	जबतक (ret != rcvd) अणु
		अगर (ret < 0)
			निकास_with_error(ret);
		अगर (xsk_ring_prod__needs_wakeup(&xsk->umem->fq)) अणु
			ret = poll(fds, 1, POLL_TMOUT);
			अगर (ret < 0)
				निकास_with_error(ret);
		पूर्ण
		ret = xsk_ring_prod__reserve(&xsk->umem->fq, rcvd, &idx_fq);
	पूर्ण

	क्रम (i = 0; i < rcvd; i++) अणु
		u64 addr, orig;

		addr = xsk_ring_cons__rx_desc(&xsk->rx, idx_rx)->addr;
		xsk_ring_cons__rx_desc(&xsk->rx, idx_rx++);
		orig = xsk_umem__extract_addr(addr);

		addr = xsk_umem__add_offset_to_addr(addr);
		pkt_node_rx = दो_स्मृति(माप(काष्ठा pkt) + PKT_SIZE);
		अगर (!pkt_node_rx)
			निकास_with_error(त्रुटि_सं);

		pkt_node_rx->pkt_frame = दो_स्मृति(PKT_SIZE);
		अगर (!pkt_node_rx->pkt_frame)
			निकास_with_error(त्रुटि_सं);

		स_नकल(pkt_node_rx->pkt_frame, xsk_umem__get_data(xsk->umem->buffer, addr),
		       PKT_SIZE);

		TAILQ_INSERT_HEAD(&head, pkt_node_rx, pkt_nodes);

		*xsk_ring_prod__fill_addr(&xsk->umem->fq, idx_fq++) = orig;
	पूर्ण

	xsk_ring_prod__submit(&xsk->umem->fq, rcvd);
	xsk_ring_cons__release(&xsk->rx, rcvd);
	xsk->rx_npkts += rcvd;
पूर्ण

अटल व्योम tx_only(काष्ठा xsk_socket_info *xsk, u32 *frameptr, पूर्णांक batch_size)
अणु
	u32 idx = 0;
	अचिन्हित पूर्णांक i;
	bool tx_invalid_test = stat_test_type == STAT_TEST_TX_INVALID;
	u32 len = tx_invalid_test ? XSK_UMEM__DEFAULT_FRAME_SIZE + 1 : PKT_SIZE;

	जबतक (xsk_ring_prod__reserve(&xsk->tx, batch_size, &idx) < batch_size)
		complete_tx_only(xsk, batch_size);

	क्रम (i = 0; i < batch_size; i++) अणु
		काष्ठा xdp_desc *tx_desc = xsk_ring_prod__tx_desc(&xsk->tx, idx + i);

		tx_desc->addr = (*frameptr + i) << XSK_UMEM__DEFAULT_FRAME_SHIFT;
		tx_desc->len = len;
	पूर्ण

	xsk_ring_prod__submit(&xsk->tx, batch_size);
	अगर (!tx_invalid_test) अणु
		xsk->outstanding_tx += batch_size;
	पूर्ण अन्यथा अगर (xsk_ring_prod__needs_wakeup(&xsk->tx)) अणु
		kick_tx(xsk);
	पूर्ण
	*frameptr += batch_size;
	*frameptr %= num_frames;
	complete_tx_only(xsk, batch_size);
पूर्ण

अटल पूर्णांक get_batch_size(पूर्णांक pkt_cnt)
अणु
	अगर (!opt_pkt_count)
		वापस BATCH_SIZE;

	अगर (pkt_cnt + BATCH_SIZE <= opt_pkt_count)
		वापस BATCH_SIZE;

	वापस opt_pkt_count - pkt_cnt;
पूर्ण

अटल व्योम complete_tx_only_all(काष्ठा अगरobject *अगरobject)
अणु
	bool pending;

	करो अणु
		pending = false;
		अगर (अगरobject->xsk->outstanding_tx) अणु
			complete_tx_only(अगरobject->xsk, BATCH_SIZE);
			pending = !!अगरobject->xsk->outstanding_tx;
		पूर्ण
	पूर्ण जबतक (pending);
पूर्ण

अटल व्योम tx_only_all(काष्ठा अगरobject *अगरobject)
अणु
	काष्ठा pollfd fds[MAX_SOCKS] = अणु पूर्ण;
	u32 frame_nb = 0;
	पूर्णांक pkt_cnt = 0;
	पूर्णांक ret;

	fds[0].fd = xsk_socket__fd(अगरobject->xsk->xsk);
	fds[0].events = POLLOUT;

	जबतक ((opt_pkt_count && pkt_cnt < opt_pkt_count) || !opt_pkt_count) अणु
		पूर्णांक batch_size = get_batch_size(pkt_cnt);

		अगर (test_type == TEST_TYPE_POLL) अणु
			ret = poll(fds, 1, POLL_TMOUT);
			अगर (ret <= 0)
				जारी;

			अगर (!(fds[0].revents & POLLOUT))
				जारी;
		पूर्ण

		tx_only(अगरobject->xsk, &frame_nb, batch_size);
		pkt_cnt += batch_size;
	पूर्ण

	अगर (opt_pkt_count)
		complete_tx_only_all(अगरobject);
पूर्ण

अटल व्योम worker_pkt_dump(व्योम)
अणु
	काष्ठा ethhdr *ethhdr;
	काष्ठा iphdr *iphdr;
	काष्ठा udphdr *udphdr;
	अक्षर s[128];
	पूर्णांक payload;
	व्योम *ptr;

	ख_लिखो(मानक_निकास, "---------------------------------------\n");
	क्रम (पूर्णांक iter = 0; iter < num_frames - 1; iter++) अणु
		ptr = pkt_buf[iter]->payload;
		ethhdr = ptr;
		iphdr = ptr + माप(*ethhdr);
		udphdr = ptr + माप(*ethhdr) + माप(*iphdr);

		/*extract L2 frame */
		ख_लिखो(मानक_निकास, "DEBUG>> L2: dst mac: ");
		क्रम (पूर्णांक i = 0; i < ETH_ALEN; i++)
			ख_लिखो(मानक_निकास, "%02X", ethhdr->h_dest[i]);

		ख_लिखो(मानक_निकास, "\nDEBUG>> L2: src mac: ");
		क्रम (पूर्णांक i = 0; i < ETH_ALEN; i++)
			ख_लिखो(मानक_निकास, "%02X", ethhdr->h_source[i]);

		/*extract L3 frame */
		ख_लिखो(मानक_निकास, "\nDEBUG>> L3: ip_hdr->ihl: %02X\n", iphdr->ihl);
		ख_लिखो(मानक_निकास, "DEBUG>> L3: ip_hdr->saddr: %s\n",
			inet_ntop(AF_INET, &iphdr->saddr, s, माप(s)));
		ख_लिखो(मानक_निकास, "DEBUG>> L3: ip_hdr->daddr: %s\n",
			inet_ntop(AF_INET, &iphdr->daddr, s, माप(s)));
		/*extract L4 frame */
		ख_लिखो(मानक_निकास, "DEBUG>> L4: udp_hdr->src: %d\n", ntohs(udphdr->source));
		ख_लिखो(मानक_निकास, "DEBUG>> L4: udp_hdr->dst: %d\n", ntohs(udphdr->dest));
		/*extract L5 frame */
		payload = *((uपूर्णांक32_t *)(ptr + PKT_HDR_SIZE));

		अगर (payload == EOT) अणु
			prपूर्णांक_verbose("End-of-transmission frame received\n");
			ख_लिखो(मानक_निकास, "---------------------------------------\n");
			अवरोध;
		पूर्ण
		ख_लिखो(मानक_निकास, "DEBUG>> L5: payload: %d\n", payload);
		ख_लिखो(मानक_निकास, "---------------------------------------\n");
	पूर्ण
पूर्ण

अटल व्योम worker_stats_validate(काष्ठा अगरobject *अगरobject)
अणु
	काष्ठा xdp_statistics stats;
	socklen_t optlen;
	पूर्णांक err;
	काष्ठा xsk_socket *xsk = stat_test_type == STAT_TEST_TX_INVALID ?
							अगरdict[!अगरobject->अगरdict_index]->xsk->xsk :
							अगरobject->xsk->xsk;
	पूर्णांक fd = xsk_socket__fd(xsk);
	अचिन्हित दीर्घ xsk_stat = 0, expected_stat = opt_pkt_count;

	sigvar = 0;

	optlen = माप(stats);
	err = माला_लोockopt(fd, SOL_XDP, XDP_STATISTICS, &stats, &optlen);
	अगर (err)
		वापस;

	अगर (optlen == माप(काष्ठा xdp_statistics)) अणु
		चयन (stat_test_type) अणु
		हाल STAT_TEST_RX_DROPPED:
			xsk_stat = stats.rx_dropped;
			अवरोध;
		हाल STAT_TEST_TX_INVALID:
			xsk_stat = stats.tx_invalid_descs;
			अवरोध;
		हाल STAT_TEST_RX_FULL:
			xsk_stat = stats.rx_ring_full;
			expected_stat -= RX_FULL_RXQSIZE;
			अवरोध;
		हाल STAT_TEST_RX_FILL_EMPTY:
			xsk_stat = stats.rx_fill_ring_empty_descs;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (xsk_stat == expected_stat)
			sigvar = 1;
	पूर्ण
पूर्ण

अटल व्योम worker_pkt_validate(व्योम)
अणु
	u32 payloadseqnum = -2;
	काष्ठा iphdr *iphdr;

	जबतक (1) अणु
		pkt_node_rx_q = TAILQ_LAST(&head, head_s);
		अगर (!pkt_node_rx_q)
			अवरोध;

		iphdr = (काष्ठा iphdr *)(pkt_node_rx_q->pkt_frame + माप(काष्ठा ethhdr));

		/*करो not increment pktcounter अगर !(tos=0x9 and ipv4) */
		अगर (iphdr->version == IP_PKT_VER && iphdr->tos == IP_PKT_TOS) अणु
			payloadseqnum = *((uपूर्णांक32_t *)(pkt_node_rx_q->pkt_frame + PKT_HDR_SIZE));
			अगर (debug_pkt_dump && payloadseqnum != EOT) अणु
				pkt_obj = दो_स्मृति(माप(*pkt_obj));
				pkt_obj->payload = दो_स्मृति(PKT_SIZE);
				स_नकल(pkt_obj->payload, pkt_node_rx_q->pkt_frame, PKT_SIZE);
				pkt_buf[payloadseqnum] = pkt_obj;
			पूर्ण

			अगर (payloadseqnum == EOT) अणु
				prपूर्णांक_verbose("End-of-transmission frame received: PASS\n");
				sigvar = 1;
				अवरोध;
			पूर्ण

			अगर (prev_pkt + 1 != payloadseqnum) अणु
				ksft_test_result_fail
				    ("ERROR: [%s] prev_pkt [%d], payloadseqnum [%d]\n",
				     __func__, prev_pkt, payloadseqnum);
				ksft_निकास_xfail();
			पूर्ण

			prev_pkt = payloadseqnum;
			pkt_counter++;
		पूर्ण अन्यथा अणु
			ksft_prपूर्णांक_msg("Invalid frame received: ");
			ksft_prपूर्णांक_msg("[IP_PKT_VER: %02X], [IP_PKT_TOS: %02X]\n", iphdr->version,
				       iphdr->tos);
		पूर्ण

		TAILQ_REMOVE(&head, pkt_node_rx_q, pkt_nodes);
		मुक्त(pkt_node_rx_q->pkt_frame);
		मुक्त(pkt_node_rx_q);
		pkt_node_rx_q = शून्य;
	पूर्ण
पूर्ण

अटल व्योम thपढ़ो_common_ops(काष्ठा अगरobject *अगरobject, व्योम *bufs)
अणु
	पूर्णांक umem_sz = num_frames * XSK_UMEM__DEFAULT_FRAME_SIZE;
	पूर्णांक ctr = 0;
	पूर्णांक ret;

	अगरobject->ns_fd = चयन_namespace(अगरobject->nsname);

	अगर (test_type == TEST_TYPE_BPF_RES)
		umem_sz *= 2;

	bufs = mmap(शून्य, umem_sz,
		    PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	अगर (bufs == MAP_FAILED)
		निकास_with_error(त्रुटि_सं);

	xsk_configure_umem(अगरobject, bufs, 0);
	अगरobject->umem = अगरobject->umem_arr[0];
	ret = xsk_configure_socket(अगरobject, 0);

	/* Retry Create Socket अगर it fails as xsk_socket__create()
	 * is asynchronous
	 */
	जबतक (ret && ctr < SOCK_RECONF_CTR) अणु
		xsk_configure_umem(अगरobject, bufs, 0);
		अगरobject->umem = अगरobject->umem_arr[0];
		ret = xsk_configure_socket(अगरobject, 0);
		usleep(USLEEP_MAX);
		ctr++;
	पूर्ण

	अगर (ctr >= SOCK_RECONF_CTR)
		निकास_with_error(ret);

	अगरobject->umem = अगरobject->umem_arr[0];
	अगरobject->xsk = अगरobject->xsk_arr[0];

	अगर (test_type == TEST_TYPE_BPF_RES) अणु
		xsk_configure_umem(अगरobject, (u8 *)bufs + (umem_sz / 2), 1);
		अगरobject->umem = अगरobject->umem_arr[1];
		ret = xsk_configure_socket(अगरobject, 1);
	पूर्ण

	अगरobject->umem = अगरobject->umem_arr[0];
	अगरobject->xsk = अगरobject->xsk_arr[0];
	prपूर्णांक_verbose("Interface [%s] vector [%s]\n",
		      अगरobject->अगरname, अगरobject->fv.vector == tx ? "Tx" : "Rx");
पूर्ण

अटल bool testapp_is_test_two_stepped(व्योम)
अणु
	वापस (test_type != TEST_TYPE_BIDI && test_type != TEST_TYPE_BPF_RES) || second_step;
पूर्ण

अटल व्योम testapp_cleanup_xsk_res(काष्ठा अगरobject *अगरobj)
अणु
	अगर (testapp_is_test_two_stepped()) अणु
		xsk_socket__delete(अगरobj->xsk->xsk);
		(व्योम)xsk_umem__delete(अगरobj->umem->umem);
	पूर्ण
पूर्ण

अटल व्योम *worker_testapp_validate_tx(व्योम *arg)
अणु
	काष्ठा udphdr *udp_hdr =
	    (काष्ठा udphdr *)(pkt_data + माप(काष्ठा ethhdr) + माप(काष्ठा iphdr));
	काष्ठा iphdr *ip_hdr = (काष्ठा iphdr *)(pkt_data + माप(काष्ठा ethhdr));
	काष्ठा ethhdr *eth_hdr = (काष्ठा ethhdr *)pkt_data;
	काष्ठा अगरobject *अगरobject = (काष्ठा अगरobject *)arg;
	काष्ठा generic_data data;
	व्योम *bufs = शून्य;

	अगर (!second_step)
		thपढ़ो_common_ops(अगरobject, bufs);

	क्रम (पूर्णांक i = 0; i < num_frames; i++) अणु
		/*send EOT frame */
		अगर (i == (num_frames - 1))
			data.seqnum = -1;
		अन्यथा
			data.seqnum = i;
		gen_udp_hdr(&data, अगरobject, udp_hdr);
		gen_ip_hdr(अगरobject, ip_hdr);
		gen_udp_csum(udp_hdr, ip_hdr);
		gen_eth_hdr(अगरobject, eth_hdr);
		gen_eth_frame(अगरobject->umem, i * XSK_UMEM__DEFAULT_FRAME_SIZE);
	पूर्ण

	prपूर्णांक_verbose("Sending %d packets on interface %s\n",
		      (opt_pkt_count - 1), अगरobject->अगरname);
	tx_only_all(अगरobject);

	testapp_cleanup_xsk_res(अगरobject);
	pthपढ़ो_निकास(शून्य);
पूर्ण

अटल व्योम *worker_testapp_validate_rx(व्योम *arg)
अणु
	काष्ठा अगरobject *अगरobject = (काष्ठा अगरobject *)arg;
	काष्ठा pollfd fds[MAX_SOCKS] = अणु पूर्ण;
	व्योम *bufs = शून्य;

	अगर (!second_step)
		thपढ़ो_common_ops(अगरobject, bufs);

	अगर (stat_test_type != STAT_TEST_RX_FILL_EMPTY)
		xsk_populate_fill_ring(अगरobject->umem);

	TAILQ_INIT(&head);
	अगर (debug_pkt_dump) अणु
		pkt_buf = सुस्मृति(num_frames, माप(*pkt_buf));
		अगर (!pkt_buf)
			निकास_with_error(त्रुटि_सं);
	पूर्ण

	fds[0].fd = xsk_socket__fd(अगरobject->xsk->xsk);
	fds[0].events = POLLIN;

	pthपढ़ो_barrier_रुको(&barr);

	जबतक (1) अणु
		अगर (test_type != TEST_TYPE_STATS) अणु
			rx_pkt(अगरobject->xsk, fds);
			worker_pkt_validate();
		पूर्ण अन्यथा अणु
			worker_stats_validate(अगरobject);
		पूर्ण
		अगर (sigvar)
			अवरोध;
	पूर्ण

	prपूर्णांक_verbose("Received %d packets on interface %s\n",
		      pkt_counter, अगरobject->अगरname);

	अगर (test_type == TEST_TYPE_TEARDOWN)
		prपूर्णांक_verbose("Destroying socket\n");

	testapp_cleanup_xsk_res(अगरobject);
	pthपढ़ो_निकास(शून्य);
पूर्ण

अटल व्योम testapp_validate(व्योम)
अणु
	bool bidi = test_type == TEST_TYPE_BIDI;
	bool bpf = test_type == TEST_TYPE_BPF_RES;

	अगर (pthपढ़ो_barrier_init(&barr, शून्य, 2))
		निकास_with_error(त्रुटि_सं);

	/*Spawn RX thपढ़ो */
	pthपढ़ो_create(&t0, शून्य, अगरdict_rx->func_ptr, अगरdict_rx);

	pthपढ़ो_barrier_रुको(&barr);
	अगर (pthपढ़ो_barrier_destroy(&barr))
		निकास_with_error(त्रुटि_सं);

	/*Spawn TX thपढ़ो */
	pthपढ़ो_create(&t1, शून्य, अगरdict_tx->func_ptr, अगरdict_tx);

	pthपढ़ो_join(t1, शून्य);
	pthपढ़ो_join(t0, शून्य);

	अगर (debug_pkt_dump && test_type != TEST_TYPE_STATS) अणु
		worker_pkt_dump();
		क्रम (पूर्णांक iter = 0; iter < num_frames - 1; iter++) अणु
			मुक्त(pkt_buf[iter]->payload);
			मुक्त(pkt_buf[iter]);
		पूर्ण
		मुक्त(pkt_buf);
	पूर्ण

	अगर (!(test_type == TEST_TYPE_TEARDOWN) && !bidi && !bpf && !(test_type == TEST_TYPE_STATS))
		prपूर्णांक_ksft_result();
पूर्ण

अटल व्योम testapp_tearकरोwn(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_TEARDOWN_ITER; i++) अणु
		pkt_counter = 0;
		prev_pkt = -1;
		sigvar = 0;
		prपूर्णांक_verbose("Creating socket\n");
		testapp_validate();
	पूर्ण

	prपूर्णांक_ksft_result();
पूर्ण

अटल व्योम swap_vectors(काष्ठा अगरobject *अगरobj1, काष्ठा अगरobject *अगरobj2)
अणु
	व्योम *(*पंचांगp_func_ptr)(व्योम *) = अगरobj1->func_ptr;
	क्रमागत fvector पंचांगp_vector = अगरobj1->fv.vector;

	अगरobj1->func_ptr = अगरobj2->func_ptr;
	अगरobj1->fv.vector = अगरobj2->fv.vector;

	अगरobj2->func_ptr = पंचांगp_func_ptr;
	अगरobj2->fv.vector = पंचांगp_vector;

	अगरdict_tx = अगरobj1;
	अगरdict_rx = अगरobj2;
पूर्ण

अटल व्योम testapp_bidi(व्योम)
अणु
	क्रम (पूर्णांक i = 0; i < MAX_BIDI_ITER; i++) अणु
		pkt_counter = 0;
		prev_pkt = -1;
		sigvar = 0;
		prपूर्णांक_verbose("Creating socket\n");
		testapp_validate();
		अगर (!second_step) अणु
			prपूर्णांक_verbose("Switching Tx/Rx vectors\n");
			swap_vectors(अगरdict[1], अगरdict[0]);
		पूर्ण
		second_step = true;
	पूर्ण

	swap_vectors(अगरdict[0], अगरdict[1]);

	prपूर्णांक_ksft_result();
पूर्ण

अटल व्योम swap_xsk_res(व्योम)
अणु
	xsk_socket__delete(अगरdict_tx->xsk->xsk);
	xsk_umem__delete(अगरdict_tx->umem->umem);
	xsk_socket__delete(अगरdict_rx->xsk->xsk);
	xsk_umem__delete(अगरdict_rx->umem->umem);
	अगरdict_tx->umem = अगरdict_tx->umem_arr[1];
	अगरdict_tx->xsk = अगरdict_tx->xsk_arr[1];
	अगरdict_rx->umem = अगरdict_rx->umem_arr[1];
	अगरdict_rx->xsk = अगरdict_rx->xsk_arr[1];
पूर्ण

अटल व्योम testapp_bpf_res(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_BPF_ITER; i++) अणु
		pkt_counter = 0;
		prev_pkt = -1;
		sigvar = 0;
		prपूर्णांक_verbose("Creating socket\n");
		testapp_validate();
		अगर (!second_step)
			swap_xsk_res();
		second_step = true;
	पूर्ण

	prपूर्णांक_ksft_result();
पूर्ण

अटल व्योम testapp_stats(व्योम)
अणु
	क्रम (पूर्णांक i = 0; i < STAT_TEST_TYPE_MAX; i++) अणु
		stat_test_type = i;

		/* reset शेषs */
		rxqsize = XSK_RING_CONS__DEFAULT_NUM_DESCS;
		frame_headroom = XSK_UMEM__DEFAULT_FRAME_HEADROOM;

		चयन (stat_test_type) अणु
		हाल STAT_TEST_RX_DROPPED:
			frame_headroom = XSK_UMEM__DEFAULT_FRAME_SIZE -
						XDP_PACKET_HEADROOM - 1;
			अवरोध;
		हाल STAT_TEST_RX_FULL:
			rxqsize = RX_FULL_RXQSIZE;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		testapp_validate();
	पूर्ण

	prपूर्णांक_ksft_result();
पूर्ण

अटल व्योम init_अगरace(काष्ठा अगरobject *अगरobj, स्थिर अक्षर *dst_mac,
		       स्थिर अक्षर *src_mac, स्थिर अक्षर *dst_ip,
		       स्थिर अक्षर *src_ip, स्थिर u16 dst_port,
		       स्थिर u16 src_port, क्रमागत fvector vector)
अणु
	काष्ठा in_addr ip;

	स_नकल(अगरobj->dst_mac, dst_mac, ETH_ALEN);
	स_नकल(अगरobj->src_mac, src_mac, ETH_ALEN);

	inet_aton(dst_ip, &ip);
	अगरobj->dst_ip = ip.s_addr;

	inet_aton(src_ip, &ip);
	अगरobj->src_ip = ip.s_addr;

	अगरobj->dst_port = dst_port;
	अगरobj->src_port = src_port;

	अगर (vector == tx) अणु
		अगरobj->fv.vector = tx;
		अगरobj->func_ptr = worker_testapp_validate_tx;
		अगरdict_tx = अगरobj;
	पूर्ण अन्यथा अणु
		अगरobj->fv.vector = rx;
		अगरobj->func_ptr = worker_testapp_validate_rx;
		अगरdict_rx = अगरobj;
	पूर्ण
पूर्ण

अटल व्योम run_pkt_test(पूर्णांक mode, पूर्णांक type)
अणु
	test_type = type;

	/* reset शेषs after potential previous test */
	xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST;
	pkt_counter = 0;
	second_step = 0;
	prev_pkt = -1;
	sigvar = 0;
	stat_test_type = -1;
	rxqsize = XSK_RING_CONS__DEFAULT_NUM_DESCS;
	frame_headroom = XSK_UMEM__DEFAULT_FRAME_HEADROOM;

	configured_mode = mode;

	चयन (mode) अणु
	हाल (TEST_MODE_SKB):
		xdp_flags |= XDP_FLAGS_SKB_MODE;
		अवरोध;
	हाल (TEST_MODE_DRV):
		xdp_flags |= XDP_FLAGS_DRV_MODE;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (test_type) अणु
	हाल TEST_TYPE_STATS:
		testapp_stats();
		अवरोध;
	हाल TEST_TYPE_TEARDOWN:
		testapp_tearकरोwn();
		अवरोध;
	हाल TEST_TYPE_BIDI:
		testapp_bidi();
		अवरोध;
	हाल TEST_TYPE_BPF_RES:
		testapp_bpf_res();
		अवरोध;
	शेष:
		testapp_validate();
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा rlimit _rlim = अणु RLIM_अनन्त, RLIM_अनन्त पूर्ण;
	bool failure = false;
	पूर्णांक i, j;

	अगर (setrlimit(RLIMIT_MEMLOCK, &_rlim))
		निकास_with_error(त्रुटि_सं);

	क्रम (पूर्णांक i = 0; i < MAX_INTERFACES; i++) अणु
		अगरdict[i] = दो_स्मृति(माप(काष्ठा अगरobject));
		अगर (!अगरdict[i])
			निकास_with_error(त्रुटि_सं);

		अगरdict[i]->अगरdict_index = i;
		अगरdict[i]->xsk_arr = सुस्मृति(2, माप(काष्ठा xsk_socket_info *));
		अगर (!अगरdict[i]->xsk_arr) अणु
			failure = true;
			जाओ cleanup;
		पूर्ण
		अगरdict[i]->umem_arr = सुस्मृति(2, माप(काष्ठा xsk_umem_info *));
		अगर (!अगरdict[i]->umem_arr) अणु
			failure = true;
			जाओ cleanup;
		पूर्ण
	पूर्ण

	रखो_क्षेत्र(LC_ALL, "");

	parse_command_line(argc, argv);

	num_frames = ++opt_pkt_count;

	init_अगरace(अगरdict[0], MAC1, MAC2, IP1, IP2, UDP_PORT1, UDP_PORT2, tx);
	init_अगरace(अगरdict[1], MAC2, MAC1, IP2, IP1, UDP_PORT2, UDP_PORT1, rx);

	ksft_set_plan(TEST_MODE_MAX * TEST_TYPE_MAX);

	क्रम (i = 0; i < TEST_MODE_MAX; i++) अणु
		क्रम (j = 0; j < TEST_TYPE_MAX; j++)
			run_pkt_test(i, j);
	पूर्ण

cleanup:
	क्रम (पूर्णांक i = 0; i < MAX_INTERFACES; i++) अणु
		अगर (अगरdict[i]->ns_fd != -1)
			बंद(अगरdict[i]->ns_fd);
		मुक्त(अगरdict[i]->xsk_arr);
		मुक्त(अगरdict[i]->umem_arr);
		मुक्त(अगरdict[i]);
	पूर्ण

	अगर (failure)
		निकास_with_error(त्रुटि_सं);

	ksft_निकास_pass();

	वापस 0;
पूर्ण
