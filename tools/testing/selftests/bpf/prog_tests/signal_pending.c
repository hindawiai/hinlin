<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <network_helpers.h>

अटल व्योम sigalrm_handler(पूर्णांक s) अणुपूर्ण
अटल काष्ठा sigaction sigalrm_action = अणु
	.sa_handler = sigalrm_handler,
पूर्ण;

अटल व्योम test_संकेत_pending_by_type(क्रमागत bpf_prog_type prog_type)
अणु
	काष्ठा bpf_insn prog[4096];
	काष्ठा iसमयrval समयo = अणु
		.it_value.tv_usec = 100000, /* 100ms */
	पूर्ण;
	__u32 duration = 0, retval;
	पूर्णांक prog_fd;
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(prog); i++)
		prog[i] = BPF_ALU64_IMM(BPF_MOV, BPF_REG_0, 0);
	prog[ARRAY_SIZE(prog) - 1] = BPF_EXIT_INSN();

	prog_fd = bpf_load_program(prog_type, prog, ARRAY_SIZE(prog),
				   "GPL", 0, शून्य, 0);
	CHECK(prog_fd < 0, "test-run", "errno %d\n", त्रुटि_सं);

	err = sigaction(SIGALRM, &sigalrm_action, शून्य);
	CHECK(err, "test-run-signal-sigaction", "errno %d\n", त्रुटि_सं);

	err = setiसमयr(ITIMER_REAL, &समयo, शून्य);
	CHECK(err, "test-run-signal-timer", "errno %d\n", त्रुटि_सं);

	err = bpf_prog_test_run(prog_fd, 0xffffffff, &pkt_v4, माप(pkt_v4),
				शून्य, शून्य, &retval, &duration);
	CHECK(duration > 500000000, /* 500ms */
	      "test-run-signal-duration",
	      "duration %dns > 500ms\n",
	      duration);

	संकेत(SIGALRM, संक_पूर्व);
पूर्ण

व्योम test_संकेत_pending(क्रमागत bpf_prog_type prog_type)
अणु
	test_संकेत_pending_by_type(BPF_PROG_TYPE_SOCKET_FILTER);
	test_संकेत_pending_by_type(BPF_PROG_TYPE_FLOW_DISSECTOR);
पूर्ण
