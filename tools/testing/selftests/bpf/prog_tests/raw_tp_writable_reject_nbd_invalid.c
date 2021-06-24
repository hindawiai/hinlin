<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <test_progs.h>
#समावेश <linux/nbd.h>

व्योम test_raw_tp_writable_reject_nbd_invalid(व्योम)
अणु
	__u32 duration = 0;
	अक्षर error[4096];
	पूर्णांक bpf_fd = -1, tp_fd = -1;

	स्थिर काष्ठा bpf_insn program[] = अणु
		/* r6 is our tp buffer */
		BPF_LDX_MEM(BPF_DW, BPF_REG_6, BPF_REG_1, 0),
		/* one byte beyond the end of the nbd_request काष्ठा */
		BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_6,
			    माप(काष्ठा nbd_request)),
		BPF_EXIT_INSN(),
	पूर्ण;

	काष्ठा bpf_load_program_attr load_attr = अणु
		.prog_type = BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE,
		.license = "GPL v2",
		.insns = program,
		.insns_cnt = माप(program) / माप(काष्ठा bpf_insn),
		.log_level = 2,
	पूर्ण;

	bpf_fd = bpf_load_program_xattr(&load_attr, error, माप(error));
	अगर (CHECK(bpf_fd < 0, "bpf_raw_tracepoint_writable load",
		  "failed: %d errno %d\n", bpf_fd, त्रुटि_सं))
		वापस;

	tp_fd = bpf_raw_tracepoपूर्णांक_खोलो("nbd_send_request", bpf_fd);
	अगर (CHECK(tp_fd >= 0, "bpf_raw_tracepoint_writable open",
		  "erroneously succeeded\n"))
		जाओ out_bpffd;

	बंद(tp_fd);
out_bpffd:
	बंद(bpf_fd);
पूर्ण
