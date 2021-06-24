<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2013 Google Inc.
 * Author: Willem de Bruijn (willemb@google.com)
 *
 * A basic test of packet socket fanout behavior.
 *
 * Control:
 * - create fanout fails as expected with illegal flag combinations
 * - join   fanout fails as expected with भागerging types or flags
 *
 * Datapath:
 *   Open a pair of packet sockets and a pair of INET sockets, send a known
 *   number of packets across the two INET sockets and count the number of
 *   packets enqueued onto the two packet sockets.
 *
 *   The test currently runs क्रम
 *   - PACKET_FANOUT_HASH
 *   - PACKET_FANOUT_HASH with PACKET_FANOUT_FLAG_ROLLOVER
 *   - PACKET_FANOUT_LB
 *   - PACKET_FANOUT_CPU
 *   - PACKET_FANOUT_ROLLOVER
 *   - PACKET_FANOUT_CBPF
 *   - PACKET_FANOUT_EBPF
 *
 * Toकरो:
 * - functionality: PACKET_FANOUT_FLAG_DEFRAG
 */

#घोषणा _GNU_SOURCE		/* क्रम sched_setaffinity */

#समावेश <arpa/inet.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <linux/unistd.h>	/* क्रम __NR_bpf */
#समावेश <linux/filter.h>
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_packet.h>
#समावेश <net/अगर.h>
#समावेश <net/ethernet.h>
#समावेश <netinet/ip.h>
#समावेश <netinet/udp.h>
#समावेश <poll.h>
#समावेश <sched.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <sys/socket.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <unistd.h>

#समावेश "psock_lib.h"

#घोषणा RING_NUM_FRAMES			20

अटल uपूर्णांक32_t cfg_max_num_members;

/* Open a socket in a given fanout mode.
 * @वापस -1 अगर mode is bad, a valid socket otherwise */
अटल पूर्णांक sock_fanout_खोलो(uपूर्णांक16_t typeflags, uपूर्णांक16_t group_id)
अणु
	काष्ठा sockaddr_ll addr = अणु0पूर्ण;
	काष्ठा fanout_args args;
	पूर्णांक fd, val, err;

	fd = socket(PF_PACKET, SOCK_RAW, 0);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("socket packet");
		निकास(1);
	पूर्ण

	pair_udp_setfilter(fd);

	addr.sll_family = AF_PACKET;
	addr.sll_protocol = htons(ETH_P_IP);
	addr.sll_अगरindex = अगर_nametoindex("lo");
	अगर (addr.sll_अगरindex == 0) अणु
		लिखो_त्रुटि("if_nametoindex");
		निकास(1);
	पूर्ण
	अगर (bind(fd, (व्योम *) &addr, माप(addr))) अणु
		लिखो_त्रुटि("bind packet");
		निकास(1);
	पूर्ण

	अगर (cfg_max_num_members) अणु
		args.id = group_id;
		args.type_flags = typeflags;
		args.max_num_members = cfg_max_num_members;
		err = setsockopt(fd, SOL_PACKET, PACKET_FANOUT, &args,
				 माप(args));
	पूर्ण अन्यथा अणु
		val = (((पूर्णांक) typeflags) << 16) | group_id;
		err = setsockopt(fd, SOL_PACKET, PACKET_FANOUT, &val,
				 माप(val));
	पूर्ण
	अगर (err) अणु
		अगर (बंद(fd)) अणु
			लिखो_त्रुटि("close packet");
			निकास(1);
		पूर्ण
		वापस -1;
	पूर्ण

	वापस fd;
पूर्ण

अटल व्योम sock_fanout_set_cbpf(पूर्णांक fd)
अणु
	काष्ठा sock_filter bpf_filter[] = अणु
		BPF_STMT(BPF_LD+BPF_B+BPF_ABS, 80),	      /* ldb [80] */
		BPF_STMT(BPF_RET+BPF_A, 0),		      /* ret A */
	पूर्ण;
	काष्ठा sock_fprog bpf_prog;

	bpf_prog.filter = bpf_filter;
	bpf_prog.len = माप(bpf_filter) / माप(काष्ठा sock_filter);

	अगर (setsockopt(fd, SOL_PACKET, PACKET_FANOUT_DATA, &bpf_prog,
		       माप(bpf_prog))) अणु
		लिखो_त्रुटि("fanout data cbpf");
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम sock_fanout_getopts(पूर्णांक fd, uपूर्णांक16_t *typeflags, uपूर्णांक16_t *group_id)
अणु
	पूर्णांक sockopt;
	socklen_t sockopt_len = माप(sockopt);

	अगर (माला_लोockopt(fd, SOL_PACKET, PACKET_FANOUT,
		       &sockopt, &sockopt_len)) अणु
		लिखो_त्रुटि("failed to getsockopt");
		निकास(1);
	पूर्ण
	*typeflags = sockopt >> 16;
	*group_id = sockopt & 0xfffff;
पूर्ण

अटल व्योम sock_fanout_set_ebpf(पूर्णांक fd)
अणु
	अटल अक्षर log_buf[65536];

	स्थिर पूर्णांक len_off = __builtin_दुरत्व(काष्ठा __sk_buff, len);
	काष्ठा bpf_insn prog[] = अणु
		अणु BPF_ALU64 | BPF_MOV | BPF_X,   6, 1, 0, 0 पूर्ण,
		अणु BPF_LDX   | BPF_W   | BPF_MEM, 0, 6, len_off, 0 पूर्ण,
		अणु BPF_JMP   | BPF_JGE | BPF_K,   0, 0, 1, DATA_LEN पूर्ण,
		अणु BPF_JMP   | BPF_JA  | BPF_K,   0, 0, 4, 0 पूर्ण,
		अणु BPF_LD    | BPF_B   | BPF_ABS, 0, 0, 0, 0x50 पूर्ण,
		अणु BPF_JMP   | BPF_JEQ | BPF_K,   0, 0, 2, DATA_CHAR पूर्ण,
		अणु BPF_JMP   | BPF_JEQ | BPF_K,   0, 0, 1, DATA_CHAR_1 पूर्ण,
		अणु BPF_ALU   | BPF_MOV | BPF_K,   0, 0, 0, 0 पूर्ण,
		अणु BPF_JMP   | BPF_EXIT,          0, 0, 0, 0 पूर्ण
	पूर्ण;
	जोड़ bpf_attr attr;
	पूर्णांक pfd;

	स_रखो(&attr, 0, माप(attr));
	attr.prog_type = BPF_PROG_TYPE_SOCKET_FILTER;
	attr.insns = (अचिन्हित दीर्घ) prog;
	attr.insn_cnt = माप(prog) / माप(prog[0]);
	attr.license = (अचिन्हित दीर्घ) "GPL";
	attr.log_buf = (अचिन्हित दीर्घ) log_buf,
	attr.log_size = माप(log_buf),
	attr.log_level = 1,

	pfd = syscall(__NR_bpf, BPF_PROG_LOAD, &attr, माप(attr));
	अगर (pfd < 0) अणु
		लिखो_त्रुटि("bpf");
		ख_लिखो(मानक_त्रुटि, "bpf verifier:\n%s\n", log_buf);
		निकास(1);
	पूर्ण

	अगर (setsockopt(fd, SOL_PACKET, PACKET_FANOUT_DATA, &pfd, माप(pfd))) अणु
		लिखो_त्रुटि("fanout data ebpf");
		निकास(1);
	पूर्ण

	अगर (बंद(pfd)) अणु
		लिखो_त्रुटि("close ebpf");
		निकास(1);
	पूर्ण
पूर्ण

अटल अक्षर *sock_fanout_खोलो_ring(पूर्णांक fd)
अणु
	काष्ठा tpacket_req req = अणु
		.tp_block_size = getpagesize(),
		.tp_frame_size = getpagesize(),
		.tp_block_nr   = RING_NUM_FRAMES,
		.tp_frame_nr   = RING_NUM_FRAMES,
	पूर्ण;
	अक्षर *ring;
	पूर्णांक val = TPACKET_V2;

	अगर (setsockopt(fd, SOL_PACKET, PACKET_VERSION, (व्योम *) &val,
		       माप(val))) अणु
		लिखो_त्रुटि("packetsock ring setsockopt version");
		निकास(1);
	पूर्ण
	अगर (setsockopt(fd, SOL_PACKET, PACKET_RX_RING, (व्योम *) &req,
		       माप(req))) अणु
		लिखो_त्रुटि("packetsock ring setsockopt");
		निकास(1);
	पूर्ण

	ring = mmap(0, req.tp_block_size * req.tp_block_nr,
		    PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	अगर (ring == MAP_FAILED) अणु
		लिखो_त्रुटि("packetsock ring mmap");
		निकास(1);
	पूर्ण

	वापस ring;
पूर्ण

अटल पूर्णांक sock_fanout_पढ़ो_ring(पूर्णांक fd, व्योम *ring)
अणु
	काष्ठा tpacket2_hdr *header = ring;
	पूर्णांक count = 0;

	जबतक (count < RING_NUM_FRAMES && header->tp_status & TP_STATUS_USER) अणु
		count++;
		header = ring + (count * getpagesize());
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक sock_fanout_पढ़ो(पूर्णांक fds[], अक्षर *rings[], स्थिर पूर्णांक expect[])
अणु
	पूर्णांक ret[2];

	ret[0] = sock_fanout_पढ़ो_ring(fds[0], rings[0]);
	ret[1] = sock_fanout_पढ़ो_ring(fds[1], rings[1]);

	ख_लिखो(मानक_त्रुटि, "info: count=%d,%d, expect=%d,%d\n",
			ret[0], ret[1], expect[0], expect[1]);

	अगर ((!(ret[0] == expect[0] && ret[1] == expect[1])) &&
	    (!(ret[0] == expect[1] && ret[1] == expect[0]))) अणु
		ख_लिखो(मानक_त्रुटि, "warning: incorrect queue lengths\n");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/* Test illegal mode + flag combination */
अटल व्योम test_control_single(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "test: control single socket\n");

	अगर (sock_fanout_खोलो(PACKET_FANOUT_ROLLOVER |
			       PACKET_FANOUT_FLAG_ROLLOVER, 0) != -1) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: opened socket with dual rollover\n");
		निकास(1);
	पूर्ण
पूर्ण

/* Test illegal group with dअगरferent modes or flags */
अटल व्योम test_control_group(व्योम)
अणु
	पूर्णांक fds[2];

	ख_लिखो(मानक_त्रुटि, "test: control multiple sockets\n");

	fds[0] = sock_fanout_खोलो(PACKET_FANOUT_HASH, 0);
	अगर (fds[0] == -1) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: failed to open HASH socket\n");
		निकास(1);
	पूर्ण
	अगर (sock_fanout_खोलो(PACKET_FANOUT_HASH |
			       PACKET_FANOUT_FLAG_DEFRAG, 0) != -1) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: joined group with wrong flag defrag\n");
		निकास(1);
	पूर्ण
	अगर (sock_fanout_खोलो(PACKET_FANOUT_HASH |
			       PACKET_FANOUT_FLAG_ROLLOVER, 0) != -1) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: joined group with wrong flag ro\n");
		निकास(1);
	पूर्ण
	अगर (sock_fanout_खोलो(PACKET_FANOUT_CPU, 0) != -1) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: joined group with wrong mode\n");
		निकास(1);
	पूर्ण
	fds[1] = sock_fanout_खोलो(PACKET_FANOUT_HASH, 0);
	अगर (fds[1] == -1) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: failed to join group\n");
		निकास(1);
	पूर्ण
	अगर (बंद(fds[1]) || बंद(fds[0])) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: closing sockets\n");
		निकास(1);
	पूर्ण
पूर्ण

/* Test illegal max_num_members values */
अटल व्योम test_control_group_max_num_members(व्योम)
अणु
	पूर्णांक fds[3];

	ख_लिखो(मानक_त्रुटि, "test: control multiple sockets, max_num_members\n");

	/* expected failure on greater than PACKET_FANOUT_MAX */
	cfg_max_num_members = (1 << 16) + 1;
	अगर (sock_fanout_खोलो(PACKET_FANOUT_HASH, 0) != -1) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: max_num_members > PACKET_FANOUT_MAX\n");
		निकास(1);
	पूर्ण

	cfg_max_num_members = 256;
	fds[0] = sock_fanout_खोलो(PACKET_FANOUT_HASH, 0);
	अगर (fds[0] == -1) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: failed open\n");
		निकास(1);
	पूर्ण

	/* expected failure on joining group with dअगरferent max_num_members */
	cfg_max_num_members = 257;
	अगर (sock_fanout_खोलो(PACKET_FANOUT_HASH, 0) != -1) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: set different max_num_members\n");
		निकास(1);
	पूर्ण

	/* success on joining group with same max_num_members */
	cfg_max_num_members = 256;
	fds[1] = sock_fanout_खोलो(PACKET_FANOUT_HASH, 0);
	अगर (fds[1] == -1) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: failed to join group\n");
		निकास(1);
	पूर्ण

	/* success on joining group with max_num_members unspecअगरied */
	cfg_max_num_members = 0;
	fds[2] = sock_fanout_खोलो(PACKET_FANOUT_HASH, 0);
	अगर (fds[2] == -1) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: failed to join group\n");
		निकास(1);
	पूर्ण

	अगर (बंद(fds[2]) || बंद(fds[1]) || बंद(fds[0])) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: closing sockets\n");
		निकास(1);
	पूर्ण
पूर्ण

/* Test creating a unique fanout group ids */
अटल व्योम test_unique_fanout_group_ids(व्योम)
अणु
	पूर्णांक fds[3];
	uपूर्णांक16_t typeflags, first_group_id, second_group_id;

	ख_लिखो(मानक_त्रुटि, "test: unique ids\n");

	fds[0] = sock_fanout_खोलो(PACKET_FANOUT_HASH |
				  PACKET_FANOUT_FLAG_UNIQUEID, 0);
	अगर (fds[0] == -1) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: failed to create a unique id group.\n");
		निकास(1);
	पूर्ण

	sock_fanout_getopts(fds[0], &typeflags, &first_group_id);
	अगर (typeflags != PACKET_FANOUT_HASH) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: unexpected typeflags %x\n", typeflags);
		निकास(1);
	पूर्ण

	अगर (sock_fanout_खोलो(PACKET_FANOUT_CPU, first_group_id) != -1) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: joined group with wrong type.\n");
		निकास(1);
	पूर्ण

	fds[1] = sock_fanout_खोलो(PACKET_FANOUT_HASH, first_group_id);
	अगर (fds[1] == -1) अणु
		ख_लिखो(मानक_त्रुटि,
			"ERROR: failed to join previously created group.\n");
		निकास(1);
	पूर्ण

	fds[2] = sock_fanout_खोलो(PACKET_FANOUT_HASH |
				  PACKET_FANOUT_FLAG_UNIQUEID, 0);
	अगर (fds[2] == -1) अणु
		ख_लिखो(मानक_त्रुटि,
			"ERROR: failed to create a second unique id group.\n");
		निकास(1);
	पूर्ण

	sock_fanout_getopts(fds[2], &typeflags, &second_group_id);
	अगर (sock_fanout_खोलो(PACKET_FANOUT_HASH | PACKET_FANOUT_FLAG_UNIQUEID,
			     second_group_id) != -1) अणु
		ख_लिखो(मानक_त्रुटि,
			"ERROR: specified a group id when requesting unique id\n");
		निकास(1);
	पूर्ण

	अगर (बंद(fds[0]) || बंद(fds[1]) || बंद(fds[2])) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: closing sockets\n");
		निकास(1);
	पूर्ण
पूर्ण

अटल पूर्णांक test_datapath(uपूर्णांक16_t typeflags, पूर्णांक port_off,
			 स्थिर पूर्णांक expect1[], स्थिर पूर्णांक expect2[])
अणु
	स्थिर पूर्णांक expect0[] = अणु 0, 0 पूर्ण;
	अक्षर *rings[2];
	uपूर्णांक8_t type = typeflags & 0xFF;
	पूर्णांक fds[2], fds_udp[2][2], ret;

	ख_लिखो(मानक_त्रुटि, "\ntest: datapath 0x%hx ports %hu,%hu\n",
		typeflags, (uपूर्णांक16_t)PORT_BASE,
		(uपूर्णांक16_t)(PORT_BASE + port_off));

	fds[0] = sock_fanout_खोलो(typeflags, 0);
	fds[1] = sock_fanout_खोलो(typeflags, 0);
	अगर (fds[0] == -1 || fds[1] == -1) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: failed open\n");
		निकास(1);
	पूर्ण
	अगर (type == PACKET_FANOUT_CBPF)
		sock_fanout_set_cbpf(fds[0]);
	अन्यथा अगर (type == PACKET_FANOUT_EBPF)
		sock_fanout_set_ebpf(fds[0]);

	rings[0] = sock_fanout_खोलो_ring(fds[0]);
	rings[1] = sock_fanout_खोलो_ring(fds[1]);
	pair_udp_खोलो(fds_udp[0], PORT_BASE);
	pair_udp_खोलो(fds_udp[1], PORT_BASE + port_off);
	sock_fanout_पढ़ो(fds, rings, expect0);

	/* Send data, but not enough to overflow a queue */
	pair_udp_send(fds_udp[0], 15);
	pair_udp_send_अक्षर(fds_udp[1], 5, DATA_CHAR_1);
	ret = sock_fanout_पढ़ो(fds, rings, expect1);

	/* Send more data, overflow the queue */
	pair_udp_send_अक्षर(fds_udp[0], 15, DATA_CHAR_1);
	/* TODO: ensure consistent order between expect1 and expect2 */
	ret |= sock_fanout_पढ़ो(fds, rings, expect2);

	अगर (munmap(rings[1], RING_NUM_FRAMES * getpagesize()) ||
	    munmap(rings[0], RING_NUM_FRAMES * getpagesize())) अणु
		ख_लिखो(मानक_त्रुटि, "close rings\n");
		निकास(1);
	पूर्ण
	अगर (बंद(fds_udp[1][1]) || बंद(fds_udp[1][0]) ||
	    बंद(fds_udp[0][1]) || बंद(fds_udp[0][0]) ||
	    बंद(fds[1]) || बंद(fds[0])) अणु
		ख_लिखो(मानक_त्रुटि, "close datapath\n");
		निकास(1);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक set_cpuaffinity(पूर्णांक cpuid)
अणु
	cpu_set_t mask;

	CPU_ZERO(&mask);
	CPU_SET(cpuid, &mask);
	अगर (sched_setaffinity(0, माप(mask), &mask)) अणु
		अगर (त्रुटि_सं != EINVAL) अणु
			ख_लिखो(मानक_त्रुटि, "setaffinity %d\n", cpuid);
			निकास(1);
		पूर्ण
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर पूर्णांक expect_hash[2][2]	= अणु अणु 15, 5 पूर्ण,  अणु 20, 5 पूर्ण पूर्ण;
	स्थिर पूर्णांक expect_hash_rb[2][2]	= अणु अणु 15, 5 पूर्ण,  अणु 20, 15 पूर्ण पूर्ण;
	स्थिर पूर्णांक expect_lb[2][2]	= अणु अणु 10, 10 पूर्ण, अणु 18, 17 पूर्ण पूर्ण;
	स्थिर पूर्णांक expect_rb[2][2]	= अणु अणु 15, 5 पूर्ण,  अणु 20, 15 पूर्ण पूर्ण;
	स्थिर पूर्णांक expect_cpu0[2][2]	= अणु अणु 20, 0 पूर्ण,  अणु 20, 0 पूर्ण पूर्ण;
	स्थिर पूर्णांक expect_cpu1[2][2]	= अणु अणु 0, 20 पूर्ण,  अणु 0, 20 पूर्ण पूर्ण;
	स्थिर पूर्णांक expect_bpf[2][2]	= अणु अणु 15, 5 पूर्ण,  अणु 15, 20 पूर्ण पूर्ण;
	स्थिर पूर्णांक expect_uniqueid[2][2] = अणु अणु 20, 20पूर्ण,  अणु 20, 20 पूर्ण पूर्ण;
	पूर्णांक port_off = 2, tries = 20, ret;

	test_control_single();
	test_control_group();
	test_control_group_max_num_members();
	test_unique_fanout_group_ids();

	/* PACKET_FANOUT_MAX */
	cfg_max_num_members = 1 << 16;
	/* find a set of ports that करो not collide onto the same socket */
	ret = test_datapath(PACKET_FANOUT_HASH, port_off,
			    expect_hash[0], expect_hash[1]);
	जबतक (ret) अणु
		ख_लिखो(मानक_त्रुटि, "info: trying alternate ports (%d)\n", tries);
		ret = test_datapath(PACKET_FANOUT_HASH, ++port_off,
				    expect_hash[0], expect_hash[1]);
		अगर (!--tries) अणु
			ख_लिखो(मानक_त्रुटि, "too many collisions\n");
			वापस 1;
		पूर्ण
	पूर्ण

	ret |= test_datapath(PACKET_FANOUT_HASH | PACKET_FANOUT_FLAG_ROLLOVER,
			     port_off, expect_hash_rb[0], expect_hash_rb[1]);
	ret |= test_datapath(PACKET_FANOUT_LB,
			     port_off, expect_lb[0], expect_lb[1]);
	ret |= test_datapath(PACKET_FANOUT_ROLLOVER,
			     port_off, expect_rb[0], expect_rb[1]);

	ret |= test_datapath(PACKET_FANOUT_CBPF,
			     port_off, expect_bpf[0], expect_bpf[1]);
	ret |= test_datapath(PACKET_FANOUT_EBPF,
			     port_off, expect_bpf[0], expect_bpf[1]);

	set_cpuaffinity(0);
	ret |= test_datapath(PACKET_FANOUT_CPU, port_off,
			     expect_cpu0[0], expect_cpu0[1]);
	अगर (!set_cpuaffinity(1))
		/* TODO: test that choice alternates with previous */
		ret |= test_datapath(PACKET_FANOUT_CPU, port_off,
				     expect_cpu1[0], expect_cpu1[1]);

	ret |= test_datapath(PACKET_FANOUT_FLAG_UNIQUEID, port_off,
			     expect_uniqueid[0], expect_uniqueid[1]);

	अगर (ret)
		वापस 1;

	म_लिखो("OK. All tests passed\n");
	वापस 0;
पूर्ण
