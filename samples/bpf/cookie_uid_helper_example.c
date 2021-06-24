<शैली गुरु>
/* This test is a demo of using get_socket_uid and get_socket_cookie
 * helper function to करो per socket based network traffic monitoring.
 * It requires iptables version higher then 1.6.1. to load pinned eBPF
 * program पूर्णांकo the xt_bpf match.
 *
 * TEST:
 * ./run_cookie_uid_helper_example.sh -option
 * option:
 *	-t: करो traffic monitoring test, the program will continuously
 * prपूर्णांक out network traffic happens after program started A sample
 * output is shown below:
 *
 * cookie: 877, uid: 0x3e8, Pakcet Count: 20, Bytes Count: 11058
 * cookie: 132, uid: 0x0, Pakcet Count: 2, Bytes Count: 286
 * cookie: 812, uid: 0x3e8, Pakcet Count: 3, Bytes Count: 1726
 * cookie: 802, uid: 0x3e8, Pakcet Count: 2, Bytes Count: 104
 * cookie: 877, uid: 0x3e8, Pakcet Count: 20, Bytes Count: 11058
 * cookie: 831, uid: 0x3e8, Pakcet Count: 2, Bytes Count: 104
 * cookie: 0, uid: 0x0, Pakcet Count: 6, Bytes Count: 712
 * cookie: 880, uid: 0xfffe, Pakcet Count: 1, Bytes Count: 70
 *
 *	-s: करो माला_लोockopt SO_COOKIE test, the program will set up a pair of
 * UDP sockets and send packets between them. And पढ़ो out the traffic data
 * directly from the ebpf map based on the socket cookie.
 *
 * Clean up: अगर using shell script, the script file will delete the iptables
 * rule and unmount the bpf program when निकास. Else the iptables rule need
 * to be deleted by hand, see run_cookie_uid_helper_example.sh क्रम detail.
 */

#घोषणा _GNU_SOURCE

#घोषणा दुरत्व(type, member)	__builtin_दुरत्व(type, member)
#घोषणा ARRAY_SIZE(x) (माप(x) / माप(*(x)))

#समावेश <arpa/inet.h>
#समावेश <त्रुटिसं.स>
#समावेश <error.h>
#समावेश <सीमा.स>
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_ether.h>
#समावेश <net/अगर.h>
#समावेश <संकेत.स>
#समावेश <stdbool.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/socket.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <unistd.h>
#समावेश <bpf/bpf.h>
#समावेश "bpf_insn.h"

#घोषणा PORT 8888

काष्ठा stats अणु
	uपूर्णांक32_t uid;
	uपूर्णांक64_t packets;
	uपूर्णांक64_t bytes;
पूर्ण;

अटल पूर्णांक map_fd, prog_fd;

अटल bool test_finish;

अटल व्योम maps_create(व्योम)
अणु
	map_fd = bpf_create_map(BPF_MAP_TYPE_HASH, माप(uपूर्णांक32_t),
				माप(काष्ठा stats), 100, 0);
	अगर (map_fd < 0)
		error(1, त्रुटि_सं, "map create failed!\n");
पूर्ण

अटल व्योम prog_load(व्योम)
अणु
	अटल अक्षर log_buf[1 << 16];

	काष्ठा bpf_insn prog[] = अणु
		/*
		 * Save sk_buff क्रम future usage. value stored in R6 to R10 will
		 * not be reset after a bpf helper function call.
		 */
		BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
		/*
		 * pc1: BPF_FUNC_get_socket_cookie takes one parameter,
		 * R1: sk_buff
		 */
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0,
				BPF_FUNC_get_socket_cookie),
		/* pc2-4: save &socketCookie to r7 क्रम future usage*/
		BPF_STX_MEM(BPF_DW, BPF_REG_10, BPF_REG_0, -8),
		BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
		/*
		 * pc5-8: set up the रेजिस्टरs क्रम BPF_FUNC_map_lookup_elem,
		 * it takes two parameters (R1: map_fd,  R2: &socket_cookie)
		 */
		BPF_LD_MAP_FD(BPF_REG_1, map_fd),
		BPF_MOV64_REG(BPF_REG_2, BPF_REG_7),
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0,
				BPF_FUNC_map_lookup_elem),
		/*
		 * pc9. अगर r0 != 0x0, go to pc+14, since we have the cookie
		 * stored alपढ़ोy
		 * Otherwise करो pc10-22 to setup a new data entry.
		 */
		BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 14),
		BPF_MOV64_REG(BPF_REG_1, BPF_REG_6),
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0,
				BPF_FUNC_get_socket_uid),
		/*
		 * Place a काष्ठा stats in the R10 stack and sequentially
		 * place the member value पूर्णांकo the memory. Packets value
		 * is set by directly place a IMM value 1 पूर्णांकo the stack.
		 */
		BPF_STX_MEM(BPF_DW, BPF_REG_10, BPF_REG_0,
			    -32 + (__s16)दुरत्व(काष्ठा stats, uid)),
		BPF_ST_MEM(BPF_DW, BPF_REG_10,
			   -32 + (__s16)दुरत्व(काष्ठा stats, packets), 1),
		/*
		 * __sk_buff is a special काष्ठा used क्रम eBPF program to
		 * directly access some sk_buff field.
		 */
		BPF_LDX_MEM(BPF_W, BPF_REG_1, BPF_REG_6,
				दुरत्व(काष्ठा __sk_buff, len)),
		BPF_STX_MEM(BPF_DW, BPF_REG_10, BPF_REG_1,
			    -32 + (__s16)दुरत्व(काष्ठा stats, bytes)),
		/*
		 * add new map entry using BPF_FUNC_map_update_elem, it takes
		 * 4 parameters (R1: map_fd, R2: &socket_cookie, R3: &stats,
		 * R4: flags)
		 */
		BPF_LD_MAP_FD(BPF_REG_1, map_fd),
		BPF_MOV64_REG(BPF_REG_2, BPF_REG_7),
		BPF_MOV64_REG(BPF_REG_3, BPF_REG_10),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_3, -32),
		BPF_MOV64_IMM(BPF_REG_4, 0),
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0,
				BPF_FUNC_map_update_elem),
		BPF_JMP_IMM(BPF_JA, 0, 0, 5),
		/*
		 * pc24-30 update the packet info to a exist data entry, it can
		 * be करोne by directly ग_लिखो to poपूर्णांकers instead of using
		 * BPF_FUNC_map_update_elem helper function
		 */
		BPF_MOV64_REG(BPF_REG_9, BPF_REG_0),
		BPF_MOV64_IMM(BPF_REG_1, 1),
		BPF_ATOMIC_OP(BPF_DW, BPF_ADD, BPF_REG_9, BPF_REG_1,
			      दुरत्व(काष्ठा stats, packets)),
		BPF_LDX_MEM(BPF_W, BPF_REG_1, BPF_REG_6,
				दुरत्व(काष्ठा __sk_buff, len)),
		BPF_ATOMIC_OP(BPF_DW, BPF_ADD, BPF_REG_9, BPF_REG_1,
			      दुरत्व(काष्ठा stats, bytes)),
		BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_6,
				दुरत्व(काष्ठा __sk_buff, len)),
		BPF_EXIT_INSN(),
	पूर्ण;
	prog_fd = bpf_load_program(BPF_PROG_TYPE_SOCKET_FILTER, prog,
					ARRAY_SIZE(prog), "GPL", 0,
					log_buf, माप(log_buf));
	अगर (prog_fd < 0)
		error(1, त्रुटि_सं, "failed to load prog\n%s\n", log_buf);
पूर्ण

अटल व्योम prog_attach_iptables(अक्षर *file)
अणु
	पूर्णांक ret;
	अक्षर rules[100];

	अगर (bpf_obj_pin(prog_fd, file))
		error(1, त्रुटि_सं, "bpf_obj_pin");
	अगर (म_माप(file) > 50) अणु
		म_लिखो("file path too long: %s\n", file);
		निकास(1);
	पूर्ण
	प्र_लिखो(rules, "iptables -A OUTPUT -m bpf --object-pinned %s -j ACCEPT",
		file);
	ret = प्रणाली(rules);
	अगर (ret < 0) अणु
		म_लिखो("iptables rule update failed: %d/n", WEXITSTATUS(ret));
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_table(व्योम)
अणु
	काष्ठा stats curEntry;
	uपूर्णांक32_t curN = UINT32_MAX;
	uपूर्णांक32_t nextN;
	पूर्णांक res;

	जबतक (bpf_map_get_next_key(map_fd, &curN, &nextN) > -1) अणु
		curN = nextN;
		res = bpf_map_lookup_elem(map_fd, &curN, &curEntry);
		अगर (res < 0) अणु
			error(1, त्रुटि_सं, "fail to get entry value of Key: %u\n",
				curN);
		पूर्ण अन्यथा अणु
			म_लिखो("cookie: %u, uid: 0x%x, Packet Count: %lu,"
				" Bytes Count: %lu\n", curN, curEntry.uid,
				curEntry.packets, curEntry.bytes);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम udp_client(व्योम)
अणु
	काष्ठा sockaddr_in si_other = अणु0पूर्ण;
	काष्ठा sockaddr_in si_me = अणु0पूर्ण;
	काष्ठा stats dataEntry;
	पूर्णांक s_rcv, s_send, i, recv_len;
	अक्षर message = 'a';
	अक्षर buf;
	uपूर्णांक64_t cookie;
	पूर्णांक res;
	socklen_t cookie_len = माप(cookie);
	socklen_t slen = माप(si_other);

	s_rcv = socket(PF_INET, SOCK_DGRAM, 0);
	अगर (s_rcv < 0)
		error(1, त्रुटि_सं, "rcv socket creat failed!\n");
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	अगर (inet_aton("127.0.0.1", &si_other.sin_addr) == 0)
		error(1, त्रुटि_सं, "inet_aton\n");
	अगर (bind(s_rcv, (काष्ठा sockaddr *)&si_other, माप(si_other)) == -1)
		error(1, त्रुटि_सं, "bind\n");
	s_send = socket(PF_INET, SOCK_DGRAM, 0);
	अगर (s_send < 0)
		error(1, त्रुटि_सं, "send socket creat failed!\n");
	res = माला_लोockopt(s_send, SOL_SOCKET, SO_COOKIE, &cookie, &cookie_len);
	अगर (res < 0)
		म_लिखो("get cookie failed: %s\n", म_त्रुटि(त्रुटि_सं));
	res = bpf_map_lookup_elem(map_fd, &cookie, &dataEntry);
	अगर (res != -1)
		error(1, त्रुटि_सं, "socket stat found while flow not active\n");
	क्रम (i = 0; i < 10; i++) अणु
		res = sendto(s_send, &message, माप(message), 0,
			     (काष्ठा sockaddr *)&si_other, slen);
		अगर (res == -1)
			error(1, त्रुटि_सं, "send\n");
		अगर (res != माप(message))
			error(1, 0, "%uB != %luB\n", res, माप(message));
		recv_len = recvfrom(s_rcv, &buf, माप(buf), 0,
			     (काष्ठा sockaddr *)&si_me, &slen);
		अगर (recv_len < 0)
			error(1, त्रुटि_सं, "receive\n");
		res = स_भेद(&(si_other.sin_addr), &(si_me.sin_addr),
			   माप(si_me.sin_addr));
		अगर (res != 0)
			error(1, EFAULT, "sender addr error: %d\n", res);
		म_लिखो("Message received: %c\n", buf);
		res = bpf_map_lookup_elem(map_fd, &cookie, &dataEntry);
		अगर (res < 0)
			error(1, त्रुटि_सं, "lookup sk stat failed, cookie: %lu\n",
			      cookie);
		म_लिखो("cookie: %lu, uid: 0x%x, Packet Count: %lu,"
			" Bytes Count: %lu\n\n", cookie, dataEntry.uid,
			dataEntry.packets, dataEntry.bytes);
	पूर्ण
	बंद(s_send);
	बंद(s_rcv);
पूर्ण

अटल पूर्णांक usage(व्योम)
अणु
	म_लिखो("Usage: ./run_cookie_uid_helper_example.sh"
		" bpfObjName -option\n"
		"	-t	traffic monitor test\n"
		"	-s	getsockopt cookie test\n");
	वापस 1;
पूर्ण

अटल व्योम finish(पूर्णांक ret)
अणु
	test_finish = true;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक opt;
	bool cfg_test_traffic = false;
	bool cfg_test_cookie = false;

	अगर (argc != 3)
		वापस usage();
	जबतक ((opt = getopt(argc, argv, "ts")) != -1) अणु
		चयन (opt) अणु
		हाल 't':
			cfg_test_traffic = true;
			अवरोध;
		हाल 's':
			cfg_test_cookie = true;
			अवरोध;

		शेष:
			म_लिखो("unknown option %c\n", opt);
			usage();
			वापस -1;
		पूर्ण
	पूर्ण
	maps_create();
	prog_load();
	prog_attach_iptables(argv[2]);
	अगर (cfg_test_traffic) अणु
		अगर (संकेत(संक_विघ्न, finish) == संक_त्रुटि)
			error(1, त्रुटि_सं, "register SIGINT handler failed");
		अगर (संकेत(संक_इति, finish) == संक_त्रुटि)
			error(1, त्रुटि_सं, "register SIGTERM handler failed");
		जबतक (!test_finish) अणु
			prपूर्णांक_table();
			म_लिखो("\n");
			sleep(1);
		पूर्ण
	पूर्ण अन्यथा अगर (cfg_test_cookie) अणु
		udp_client();
	पूर्ण
	बंद(prog_fd);
	बंद(map_fd);
	वापस 0;
पूर्ण
