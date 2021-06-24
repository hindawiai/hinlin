<शैली गुरु>
/* eBPF example program:
 * - creates arraymap in kernel with key 4 bytes and value 8 bytes
 *
 * - loads eBPF program:
 *   r0 = skb->data[ETH_HLEN + दुरत्व(काष्ठा iphdr, protocol)];
 *   *(u32*)(fp - 4) = r0;
 *   // assuming packet is IPv4, lookup ip->proto in a map
 *   value = bpf_map_lookup_elem(map_fd, fp - 4);
 *   अगर (value)
 *        (*(u64*)value) += 1;
 *
 * - attaches this program to loopback पूर्णांकerface "lo" raw socket
 *
 * - every second user space पढ़ोs map[tcp], map[udp], map[icmp] to see
 *   how many packets of given protocol were seen on "lo"
 */
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <निश्चित.स>
#समावेश <linux/bpf.h>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <त्रुटिसं.स>
#समावेश <sys/socket.h>
#समावेश <arpa/inet.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/ip.h>
#समावेश <मानकघोष.स>
#समावेश <bpf/bpf.h>
#समावेश "bpf_insn.h"
#समावेश "sock_example.h"

अक्षर bpf_log_buf[BPF_LOG_BUF_SIZE];

अटल पूर्णांक test_sock(व्योम)
अणु
	पूर्णांक sock = -1, map_fd, prog_fd, i, key;
	दीर्घ दीर्घ value = 0, tcp_cnt, udp_cnt, icmp_cnt;

	map_fd = bpf_create_map(BPF_MAP_TYPE_ARRAY, माप(key), माप(value),
				256, 0);
	अगर (map_fd < 0) अणु
		म_लिखो("failed to create map '%s'\n", म_त्रुटि(त्रुटि_सं));
		जाओ cleanup;
	पूर्ण

	काष्ठा bpf_insn prog[] = अणु
		BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
		BPF_LD_ABS(BPF_B, ETH_HLEN + दुरत्व(काष्ठा iphdr, protocol) /* R0 = ip->proto */),
		BPF_STX_MEM(BPF_W, BPF_REG_10, BPF_REG_0, -4), /* *(u32 *)(fp - 4) = r0 */
		BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -4), /* r2 = fp - 4 */
		BPF_LD_MAP_FD(BPF_REG_1, map_fd),
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
		BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 2),
		BPF_MOV64_IMM(BPF_REG_1, 1), /* r1 = 1 */
		BPF_ATOMIC_OP(BPF_DW, BPF_ADD, BPF_REG_0, BPF_REG_1, 0),
		BPF_MOV64_IMM(BPF_REG_0, 0), /* r0 = 0 */
		BPF_EXIT_INSN(),
	पूर्ण;
	माप_प्रकार insns_cnt = माप(prog) / माप(काष्ठा bpf_insn);

	prog_fd = bpf_load_program(BPF_PROG_TYPE_SOCKET_FILTER, prog, insns_cnt,
				   "GPL", 0, bpf_log_buf, BPF_LOG_BUF_SIZE);
	अगर (prog_fd < 0) अणु
		म_लिखो("failed to load prog '%s'\n", म_त्रुटि(त्रुटि_सं));
		जाओ cleanup;
	पूर्ण

	sock = खोलो_raw_sock("lo");

	अगर (setsockopt(sock, SOL_SOCKET, SO_ATTACH_BPF, &prog_fd,
		       माप(prog_fd)) < 0) अणु
		म_लिखो("setsockopt %s\n", म_त्रुटि(त्रुटि_सं));
		जाओ cleanup;
	पूर्ण

	क्रम (i = 0; i < 10; i++) अणु
		key = IPPROTO_TCP;
		निश्चित(bpf_map_lookup_elem(map_fd, &key, &tcp_cnt) == 0);

		key = IPPROTO_UDP;
		निश्चित(bpf_map_lookup_elem(map_fd, &key, &udp_cnt) == 0);

		key = IPPROTO_ICMP;
		निश्चित(bpf_map_lookup_elem(map_fd, &key, &icmp_cnt) == 0);

		म_लिखो("TCP %lld UDP %lld ICMP %lld packets\n",
		       tcp_cnt, udp_cnt, icmp_cnt);
		sleep(1);
	पूर्ण

cleanup:
	/* maps, programs, raw sockets will स्वतः cleanup on process निकास */
	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	खाता *f;

	f = pखोलो("ping -4 -c5 localhost", "r");
	(व्योम)f;

	वापस test_sock();
पूर्ण
