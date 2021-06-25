<शैली गुरु>
/* eBPF example program:
 *
 * - Loads eBPF program
 *
 *   The eBPF program sets the sk_bound_dev_अगर index in new AF_INETअणु6पूर्ण
 *   sockets खोलोed by processes in the cgroup.
 *
 * - Attaches the new program to a cgroup using BPF_PROG_ATTACH
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
#समावेश <net/अगर.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf.h>

#समावेश "bpf_insn.h"

अक्षर bpf_log_buf[BPF_LOG_BUF_SIZE];

अटल पूर्णांक prog_load(__u32 idx, __u32 mark, __u32 prio)
अणु
	/* save poपूर्णांकer to context */
	काष्ठा bpf_insn prog_start[] = अणु
		BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	पूर्ण;
	काष्ठा bpf_insn prog_end[] = अणु
		BPF_MOV64_IMM(BPF_REG_0, 1), /* r0 = verdict */
		BPF_EXIT_INSN(),
	पूर्ण;

	/* set sk_bound_dev_अगर on socket */
	काष्ठा bpf_insn prog_dev[] = अणु
		BPF_MOV64_IMM(BPF_REG_3, idx),
		BPF_MOV64_IMM(BPF_REG_2, दुरत्व(काष्ठा bpf_sock, bound_dev_अगर)),
		BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_3, दुरत्व(काष्ठा bpf_sock, bound_dev_अगर)),
	पूर्ण;

	/* set mark on socket */
	काष्ठा bpf_insn prog_mark[] = अणु
		/* get uid of process */
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0,
			     BPF_FUNC_get_current_uid_gid),
		BPF_ALU64_IMM(BPF_AND, BPF_REG_0, 0xffffffff),

		/* अगर uid is 0, use given mark, अन्यथा use the uid as the mark */
		BPF_MOV64_REG(BPF_REG_3, BPF_REG_0),
		BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 1),
		BPF_MOV64_IMM(BPF_REG_3, mark),

		/* set the mark on the new socket */
		BPF_MOV64_REG(BPF_REG_1, BPF_REG_6),
		BPF_MOV64_IMM(BPF_REG_2, दुरत्व(काष्ठा bpf_sock, mark)),
		BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_3, दुरत्व(काष्ठा bpf_sock, mark)),
	पूर्ण;

	/* set priority on socket */
	काष्ठा bpf_insn prog_prio[] = अणु
		BPF_MOV64_REG(BPF_REG_1, BPF_REG_6),
		BPF_MOV64_IMM(BPF_REG_3, prio),
		BPF_MOV64_IMM(BPF_REG_2, दुरत्व(काष्ठा bpf_sock, priority)),
		BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_3, दुरत्व(काष्ठा bpf_sock, priority)),
	पूर्ण;

	काष्ठा bpf_insn *prog;
	माप_प्रकार insns_cnt;
	व्योम *p;
	पूर्णांक ret;

	insns_cnt = माप(prog_start) + माप(prog_end);
	अगर (idx)
		insns_cnt += माप(prog_dev);

	अगर (mark)
		insns_cnt += माप(prog_mark);

	अगर (prio)
		insns_cnt += माप(prog_prio);

	p = prog = दो_स्मृति(insns_cnt);
	अगर (!prog) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to allocate memory for instructions\n");
		वापस निकास_त्रुटि;
	पूर्ण

	स_नकल(p, prog_start, माप(prog_start));
	p += माप(prog_start);

	अगर (idx) अणु
		स_नकल(p, prog_dev, माप(prog_dev));
		p += माप(prog_dev);
	पूर्ण

	अगर (mark) अणु
		स_नकल(p, prog_mark, माप(prog_mark));
		p += माप(prog_mark);
	पूर्ण

	अगर (prio) अणु
		स_नकल(p, prog_prio, माप(prog_prio));
		p += माप(prog_prio);
	पूर्ण

	स_नकल(p, prog_end, माप(prog_end));
	p += माप(prog_end);

	insns_cnt /= माप(काष्ठा bpf_insn);

	ret = bpf_load_program(BPF_PROG_TYPE_CGROUP_SOCK, prog, insns_cnt,
				"GPL", 0, bpf_log_buf, BPF_LOG_BUF_SIZE);

	मुक्त(prog);

	वापस ret;
पूर्ण

अटल पूर्णांक get_bind_to_device(पूर्णांक sd, अक्षर *name, माप_प्रकार len)
अणु
	socklen_t optlen = len;
	पूर्णांक rc;

	name[0] = '\0';
	rc = माला_लोockopt(sd, SOL_SOCKET, SO_BINDTODEVICE, name, &optlen);
	अगर (rc < 0)
		लिखो_त्रुटि("setsockopt(SO_BINDTODEVICE)");

	वापस rc;
पूर्ण

अटल अचिन्हित पूर्णांक get_somark(पूर्णांक sd)
अणु
	अचिन्हित पूर्णांक mark = 0;
	socklen_t optlen = माप(mark);
	पूर्णांक rc;

	rc = माला_लोockopt(sd, SOL_SOCKET, SO_MARK, &mark, &optlen);
	अगर (rc < 0)
		लिखो_त्रुटि("getsockopt(SO_MARK)");

	वापस mark;
पूर्ण

अटल अचिन्हित पूर्णांक get_priority(पूर्णांक sd)
अणु
	अचिन्हित पूर्णांक prio = 0;
	socklen_t optlen = माप(prio);
	पूर्णांक rc;

	rc = माला_लोockopt(sd, SOL_SOCKET, SO_PRIORITY, &prio, &optlen);
	अगर (rc < 0)
		लिखो_त्रुटि("getsockopt(SO_PRIORITY)");

	वापस prio;
पूर्ण

अटल पूर्णांक show_sockopts(पूर्णांक family)
अणु
	अचिन्हित पूर्णांक mark, prio;
	अक्षर name[16];
	पूर्णांक sd;

	sd = socket(family, SOCK_DGRAM, 17);
	अगर (sd < 0) अणु
		लिखो_त्रुटि("socket");
		वापस 1;
	पूर्ण

	अगर (get_bind_to_device(sd, name, माप(name)) < 0)
		वापस 1;

	mark = get_somark(sd);
	prio = get_priority(sd);

	बंद(sd);

	म_लिखो("sd %d: dev %s, mark %u, priority %u\n", sd, name, mark, prio);

	वापस 0;
पूर्ण

अटल पूर्णांक usage(स्थिर अक्षर *argv0)
अणु
	म_लिखो("Usage:\n");
	म_लिखो("  Attach a program\n");
	म_लिखो("  %s -b bind-to-dev -m mark -p prio cg-path\n", argv0);
	म_लिखो("\n");
	म_लिखो("  Detach a program\n");
	म_लिखो("  %s -d cg-path\n", argv0);
	म_लिखो("\n");
	म_लिखो("  Show inherited socket settings (mark, priority, and device)\n");
	म_लिखो("  %s [-6]\n", argv0);
	वापस निकास_त्रुटि;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	__u32 idx = 0, mark = 0, prio = 0;
	स्थिर अक्षर *cgrp_path = शून्य;
	पूर्णांक cg_fd, prog_fd, ret;
	पूर्णांक family = PF_INET;
	पूर्णांक करो_attach = 1;
	पूर्णांक rc;

	जबतक ((rc = getopt(argc, argv, "db:m:p:6")) != -1) अणु
		चयन (rc) अणु
		हाल 'd':
			करो_attach = 0;
			अवरोध;
		हाल 'b':
			idx = अगर_nametoindex(optarg);
			अगर (!idx) अणु
				idx = strtoumax(optarg, शून्य, 0);
				अगर (!idx) अणु
					म_लिखो("Invalid device name\n");
					वापस निकास_त्रुटि;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल 'm':
			mark = strtoumax(optarg, शून्य, 0);
			अवरोध;
		हाल 'p':
			prio = strtoumax(optarg, शून्य, 0);
			अवरोध;
		हाल '6':
			family = PF_INET6;
			अवरोध;
		शेष:
			वापस usage(argv[0]);
		पूर्ण
	पूर्ण

	अगर (optind == argc)
		वापस show_sockopts(family);

	cgrp_path = argv[optind];
	अगर (!cgrp_path) अणु
		ख_लिखो(मानक_त्रुटि, "cgroup path not given\n");
		वापस निकास_त्रुटि;
	पूर्ण

	अगर (करो_attach && !idx && !mark && !prio) अणु
		ख_लिखो(मानक_त्रुटि,
			"One of device, mark or priority must be given\n");
		वापस निकास_त्रुटि;
	पूर्ण

	cg_fd = खोलो(cgrp_path, O_सूचीECTORY | O_RDONLY);
	अगर (cg_fd < 0) अणु
		म_लिखो("Failed to open cgroup path: '%s'\n", म_त्रुटि(त्रुटि_सं));
		वापस निकास_त्रुटि;
	पूर्ण

	अगर (करो_attach) अणु
		prog_fd = prog_load(idx, mark, prio);
		अगर (prog_fd < 0) अणु
			म_लिखो("Failed to load prog: '%s'\n", म_त्रुटि(त्रुटि_सं));
			म_लिखो("Output from kernel verifier:\n%s\n-------\n",
			       bpf_log_buf);
			वापस निकास_त्रुटि;
		पूर्ण

		ret = bpf_prog_attach(prog_fd, cg_fd,
				      BPF_CGROUP_INET_SOCK_CREATE, 0);
		अगर (ret < 0) अणु
			म_लिखो("Failed to attach prog to cgroup: '%s'\n",
			       म_त्रुटि(त्रुटि_सं));
			वापस निकास_त्रुटि;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = bpf_prog_detach(cg_fd, BPF_CGROUP_INET_SOCK_CREATE);
		अगर (ret < 0) अणु
			म_लिखो("Failed to detach prog from cgroup: '%s'\n",
			       म_त्रुटि(त्रुटि_सं));
			वापस निकास_त्रुटि;
		पूर्ण
	पूर्ण

	बंद(cg_fd);
	वापस निकास_सफल;
पूर्ण
