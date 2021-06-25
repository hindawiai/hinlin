<शैली गुरु>
/* eBPF example program:
 *
 * - Creates arraymap in kernel with 4 bytes keys and 8 byte values
 *
 * - Loads eBPF program
 *
 *   The eBPF program accesses the map passed in to store two pieces of
 *   inक्रमmation. The number of invocations of the program, which maps
 *   to the number of packets received, is stored to key 0. Key 1 is
 *   incremented on each iteration by the number of bytes stored in
 *   the skb.
 *
 * - Attaches the new program to a cgroup using BPF_PROG_ATTACH
 *
 * - Every second, पढ़ोs map[0] and map[1] to see how many bytes and
 *   packets were seen on any socket of tasks in the given cgroup.
 */

#घोषणा _GNU_SOURCE

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <मानकघोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf.h>

#समावेश "bpf_insn.h"

क्रमागत अणु
	MAP_KEY_PACKETS,
	MAP_KEY_BYTES,
पूर्ण;

अक्षर bpf_log_buf[BPF_LOG_BUF_SIZE];

अटल पूर्णांक prog_load(पूर्णांक map_fd, पूर्णांक verdict)
अणु
	काष्ठा bpf_insn prog[] = अणु
		BPF_MOV64_REG(BPF_REG_6, BPF_REG_1), /* save r6 so it's not clobbered by BPF_CALL */

		/* Count packets */
		BPF_MOV64_IMM(BPF_REG_0, MAP_KEY_PACKETS), /* r0 = 0 */
		BPF_STX_MEM(BPF_W, BPF_REG_10, BPF_REG_0, -4), /* *(u32 *)(fp - 4) = r0 */
		BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -4), /* r2 = fp - 4 */
		BPF_LD_MAP_FD(BPF_REG_1, map_fd), /* load map fd to r1 */
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
		BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 2),
		BPF_MOV64_IMM(BPF_REG_1, 1), /* r1 = 1 */
		BPF_ATOMIC_OP(BPF_DW, BPF_ADD, BPF_REG_0, BPF_REG_1, 0),

		/* Count bytes */
		BPF_MOV64_IMM(BPF_REG_0, MAP_KEY_BYTES), /* r0 = 1 */
		BPF_STX_MEM(BPF_W, BPF_REG_10, BPF_REG_0, -4), /* *(u32 *)(fp - 4) = r0 */
		BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -4), /* r2 = fp - 4 */
		BPF_LD_MAP_FD(BPF_REG_1, map_fd),
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
		BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 2),
		BPF_LDX_MEM(BPF_W, BPF_REG_1, BPF_REG_6, दुरत्व(काष्ठा __sk_buff, len)), /* r1 = skb->len */

		BPF_ATOMIC_OP(BPF_DW, BPF_ADD, BPF_REG_0, BPF_REG_1, 0),

		BPF_MOV64_IMM(BPF_REG_0, verdict), /* r0 = verdict */
		BPF_EXIT_INSN(),
	पूर्ण;
	माप_प्रकार insns_cnt = माप(prog) / माप(काष्ठा bpf_insn);

	वापस bpf_load_program(BPF_PROG_TYPE_CGROUP_SKB,
				prog, insns_cnt, "GPL", 0,
				bpf_log_buf, BPF_LOG_BUF_SIZE);
पूर्ण

अटल पूर्णांक usage(स्थिर अक्षर *argv0)
अणु
	म_लिखो("Usage: %s [-d] [-D] <cg-path> <egress|ingress>\n", argv0);
	म_लिखो("	-d	Drop Traffic\n");
	म_लिखो("	-D	Detach filter, and exit\n");
	वापस निकास_त्रुटि;
पूर्ण

अटल पूर्णांक attach_filter(पूर्णांक cg_fd, पूर्णांक type, पूर्णांक verdict)
अणु
	पूर्णांक prog_fd, map_fd, ret, key;
	दीर्घ दीर्घ pkt_cnt, byte_cnt;

	map_fd = bpf_create_map(BPF_MAP_TYPE_ARRAY,
				माप(key), माप(byte_cnt),
				256, 0);
	अगर (map_fd < 0) अणु
		म_लिखो("Failed to create map: '%s'\n", म_त्रुटि(त्रुटि_सं));
		वापस निकास_त्रुटि;
	पूर्ण

	prog_fd = prog_load(map_fd, verdict);
	म_लिखो("Output from kernel verifier:\n%s\n-------\n", bpf_log_buf);

	अगर (prog_fd < 0) अणु
		म_लिखो("Failed to load prog: '%s'\n", म_त्रुटि(त्रुटि_सं));
		वापस निकास_त्रुटि;
	पूर्ण

	ret = bpf_prog_attach(prog_fd, cg_fd, type, 0);
	अगर (ret < 0) अणु
		म_लिखो("Failed to attach prog to cgroup: '%s'\n",
		       म_त्रुटि(त्रुटि_सं));
		वापस निकास_त्रुटि;
	पूर्ण
	जबतक (1) अणु
		key = MAP_KEY_PACKETS;
		निश्चित(bpf_map_lookup_elem(map_fd, &key, &pkt_cnt) == 0);

		key = MAP_KEY_BYTES;
		निश्चित(bpf_map_lookup_elem(map_fd, &key, &byte_cnt) == 0);

		म_लिखो("cgroup received %lld packets, %lld bytes\n",
		       pkt_cnt, byte_cnt);
		sleep(1);
	पूर्ण

	वापस निकास_सफल;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक detach_only = 0, verdict = 1;
	क्रमागत bpf_attach_type type;
	पूर्णांक opt, cg_fd, ret;

	जबतक ((opt = getopt(argc, argv, "Dd")) != -1) अणु
		चयन (opt) अणु
		हाल 'd':
			verdict = 0;
			अवरोध;
		हाल 'D':
			detach_only = 1;
			अवरोध;
		शेष:
			वापस usage(argv[0]);
		पूर्ण
	पूर्ण

	अगर (argc - optind < 2)
		वापस usage(argv[0]);

	अगर (म_भेद(argv[optind + 1], "ingress") == 0)
		type = BPF_CGROUP_INET_INGRESS;
	अन्यथा अगर (म_भेद(argv[optind + 1], "egress") == 0)
		type = BPF_CGROUP_INET_EGRESS;
	अन्यथा
		वापस usage(argv[0]);

	cg_fd = खोलो(argv[optind], O_सूचीECTORY | O_RDONLY);
	अगर (cg_fd < 0) अणु
		म_लिखो("Failed to open cgroup path: '%s'\n", म_त्रुटि(त्रुटि_सं));
		वापस निकास_त्रुटि;
	पूर्ण

	अगर (detach_only) अणु
		ret = bpf_prog_detach(cg_fd, type);
		म_लिखो("bpf_prog_detach() returned '%s' (%d)\n",
		       म_त्रुटि(त्रुटि_सं), त्रुटि_सं);
	पूर्ण अन्यथा
		ret = attach_filter(cg_fd, type, verdict);

	वापस ret;
पूर्ण
