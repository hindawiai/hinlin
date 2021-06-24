<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook */
#समावेश <test_progs.h>

/* that's kernel पूर्णांकernal BPF_MAX_TRAMP_PROGS define */
#घोषणा CNT 38

व्योम test_fनिकास_stress(व्योम)
अणु
	अक्षर test_skb[128] = अणुपूर्ण;
	पूर्णांक fनिकास_fd[CNT] = अणुपूर्ण;
	पूर्णांक link_fd[CNT] = अणुपूर्ण;
	__u32 duration = 0;
	अक्षर error[4096];
	__u32 prog_ret;
	पूर्णांक err, i, filter_fd;

	स्थिर काष्ठा bpf_insn trace_program[] = अणु
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
	पूर्ण;

	काष्ठा bpf_load_program_attr load_attr = अणु
		.prog_type = BPF_PROG_TYPE_TRACING,
		.license = "GPL",
		.insns = trace_program,
		.insns_cnt = माप(trace_program) / माप(काष्ठा bpf_insn),
		.expected_attach_type = BPF_TRACE_FEXIT,
	पूर्ण;

	स्थिर काष्ठा bpf_insn skb_program[] = अणु
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
	पूर्ण;

	काष्ठा bpf_load_program_attr skb_load_attr = अणु
		.prog_type = BPF_PROG_TYPE_SOCKET_FILTER,
		.license = "GPL",
		.insns = skb_program,
		.insns_cnt = माप(skb_program) / माप(काष्ठा bpf_insn),
	पूर्ण;

	err = libbpf_find_vmlinux_btf_id("bpf_fentry_test1",
					 load_attr.expected_attach_type);
	अगर (CHECK(err <= 0, "find_vmlinux_btf_id", "failed: %d\n", err))
		जाओ out;
	load_attr.attach_btf_id = err;

	क्रम (i = 0; i < CNT; i++) अणु
		fनिकास_fd[i] = bpf_load_program_xattr(&load_attr, error, माप(error));
		अगर (CHECK(fनिकास_fd[i] < 0, "fexit loaded",
			  "failed: %d errno %d\n", fनिकास_fd[i], त्रुटि_सं))
			जाओ out;
		link_fd[i] = bpf_raw_tracepoपूर्णांक_खोलो(शून्य, fनिकास_fd[i]);
		अगर (CHECK(link_fd[i] < 0, "fexit attach failed",
			  "prog %d failed: %d err %d\n", i, link_fd[i], त्रुटि_सं))
			जाओ out;
	पूर्ण

	filter_fd = bpf_load_program_xattr(&skb_load_attr, error, माप(error));
	अगर (CHECK(filter_fd < 0, "test_program_loaded", "failed: %d errno %d\n",
		  filter_fd, त्रुटि_सं))
		जाओ out;

	err = bpf_prog_test_run(filter_fd, 1, test_skb, माप(test_skb), 0,
				0, &prog_ret, 0);
	बंद(filter_fd);
	CHECK_FAIL(err);
out:
	क्रम (i = 0; i < CNT; i++) अणु
		अगर (link_fd[i])
			बंद(link_fd[i]);
		अगर (fनिकास_fd[i])
			बंद(fनिकास_fd[i]);
	पूर्ण
पूर्ण
