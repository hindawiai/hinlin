<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <test_progs.h>
#समावेश <linux/nbd.h>

व्योम test_raw_tp_writable_test_run(व्योम)
अणु
	__u32 duration = 0;
	अक्षर error[4096];

	स्थिर काष्ठा bpf_insn trace_program[] = अणु
		BPF_LDX_MEM(BPF_DW, BPF_REG_6, BPF_REG_1, 0),
		BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_6, 0),
		BPF_MOV64_IMM(BPF_REG_0, 42),
		BPF_STX_MEM(BPF_W, BPF_REG_6, BPF_REG_0, 0),
		BPF_EXIT_INSN(),
	पूर्ण;

	काष्ठा bpf_load_program_attr load_attr = अणु
		.prog_type = BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE,
		.license = "GPL v2",
		.insns = trace_program,
		.insns_cnt = माप(trace_program) / माप(काष्ठा bpf_insn),
		.log_level = 2,
	पूर्ण;

	पूर्णांक bpf_fd = bpf_load_program_xattr(&load_attr, error, माप(error));
	अगर (CHECK(bpf_fd < 0, "bpf_raw_tracepoint_writable loaded",
		  "failed: %d errno %d\n", bpf_fd, त्रुटि_सं))
		वापस;

	स्थिर काष्ठा bpf_insn skb_program[] = अणु
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
	पूर्ण;

	काष्ठा bpf_load_program_attr skb_load_attr = अणु
		.prog_type = BPF_PROG_TYPE_SOCKET_FILTER,
		.license = "GPL v2",
		.insns = skb_program,
		.insns_cnt = माप(skb_program) / माप(काष्ठा bpf_insn),
	पूर्ण;

	पूर्णांक filter_fd =
		bpf_load_program_xattr(&skb_load_attr, error, माप(error));
	अगर (CHECK(filter_fd < 0, "test_program_loaded", "failed: %d errno %d\n",
		  filter_fd, त्रुटि_सं))
		जाओ out_bpffd;

	पूर्णांक tp_fd = bpf_raw_tracepoपूर्णांक_खोलो("bpf_test_finish", bpf_fd);
	अगर (CHECK(tp_fd < 0, "bpf_raw_tracepoint_writable opened",
		  "failed: %d errno %d\n", tp_fd, त्रुटि_सं))
		जाओ out_filterfd;

	अक्षर test_skb[128] = अणु
		0,
	पूर्ण;

	__u32 prog_ret;
	पूर्णांक err = bpf_prog_test_run(filter_fd, 1, test_skb, माप(test_skb), 0,
				    0, &prog_ret, 0);
	CHECK(err != 42, "test_run",
	      "tracepoint did not modify return value\n");
	CHECK(prog_ret != 0, "test_run_ret",
	      "socket_filter did not return 0\n");

	बंद(tp_fd);

	err = bpf_prog_test_run(filter_fd, 1, test_skb, माप(test_skb), 0, 0,
				&prog_ret, 0);
	CHECK(err != 0, "test_run_notrace",
	      "test_run failed with %d errno %d\n", err, त्रुटि_सं);
	CHECK(prog_ret != 0, "test_run_ret_notrace",
	      "socket_filter did not return 0\n");

out_filterfd:
	बंद(filter_fd);
out_bpffd:
	बंद(bpf_fd);
पूर्ण
