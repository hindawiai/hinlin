<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook
#समावेश <test_progs.h>
अटल पूर्णांक libbpf_debug_prपूर्णांक(क्रमागत libbpf_prपूर्णांक_level level,
			      स्थिर अक्षर *क्रमmat, बहु_सूची args)
अणु
	अगर (level != LIBBPF_DEBUG) अणु
		भ_लिखो(क्रमmat, args);
		वापस 0;
	पूर्ण

	अगर (!म_माला(क्रमmat, "verifier log"))
		वापस 0;
	भ_लिखो("%s", args);
	वापस 0;
पूर्ण

बाह्य पूर्णांक extra_prog_load_log_flags;

अटल पूर्णांक check_load(स्थिर अक्षर *file, क्रमागत bpf_prog_type type)
अणु
	काष्ठा bpf_prog_load_attr attr;
	काष्ठा bpf_object *obj = शून्य;
	पूर्णांक err, prog_fd;

	स_रखो(&attr, 0, माप(काष्ठा bpf_prog_load_attr));
	attr.file = file;
	attr.prog_type = type;
	attr.log_level = 4 | extra_prog_load_log_flags;
	attr.prog_flags = BPF_F_TEST_RND_HI32;
	err = bpf_prog_load_xattr(&attr, &obj, &prog_fd);
	bpf_object__बंद(obj);
	वापस err;
पूर्ण

काष्ठा scale_test_def अणु
	स्थिर अक्षर *file;
	क्रमागत bpf_prog_type attach_type;
	bool fails;
पूर्ण;

व्योम test_bpf_verअगर_scale(व्योम)
अणु
	काष्ठा scale_test_def tests[] = अणु
		अणु "loop3.o", BPF_PROG_TYPE_RAW_TRACEPOINT, true /* fails */ पूर्ण,

		अणु "test_verif_scale1.o", BPF_PROG_TYPE_SCHED_CLS पूर्ण,
		अणु "test_verif_scale2.o", BPF_PROG_TYPE_SCHED_CLS पूर्ण,
		अणु "test_verif_scale3.o", BPF_PROG_TYPE_SCHED_CLS पूर्ण,

		अणु "pyperf_global.o", BPF_PROG_TYPE_RAW_TRACEPOINT पूर्ण,
		अणु "pyperf_subprogs.o", BPF_PROG_TYPE_RAW_TRACEPOINT पूर्ण,

		/* full unroll by llvm */
		अणु "pyperf50.o", BPF_PROG_TYPE_RAW_TRACEPOINT पूर्ण,
		अणु "pyperf100.o", BPF_PROG_TYPE_RAW_TRACEPOINT पूर्ण,
		अणु "pyperf180.o", BPF_PROG_TYPE_RAW_TRACEPOINT पूर्ण,

		/* partial unroll. llvm will unroll loop ~150 बार.
		 * C loop count -> 600.
		 * Asm loop count -> 4.
		 * 16k insns in loop body.
		 * Total of 5 such loops. Total program size ~82k insns.
		 */
		अणु "pyperf600.o", BPF_PROG_TYPE_RAW_TRACEPOINT पूर्ण,

		/* no unroll at all.
		 * C loop count -> 600.
		 * ASM loop count -> 600.
		 * ~110 insns in loop body.
		 * Total of 5 such loops. Total program size ~1500 insns.
		 */
		अणु "pyperf600_nounroll.o", BPF_PROG_TYPE_RAW_TRACEPOINT पूर्ण,

		अणु "loop1.o", BPF_PROG_TYPE_RAW_TRACEPOINT पूर्ण,
		अणु "loop2.o", BPF_PROG_TYPE_RAW_TRACEPOINT पूर्ण,
		अणु "loop4.o", BPF_PROG_TYPE_SCHED_CLS पूर्ण,
		अणु "loop5.o", BPF_PROG_TYPE_SCHED_CLS पूर्ण,
		अणु "loop6.o", BPF_PROG_TYPE_KPROBE पूर्ण,

		/* partial unroll. 19k insn in a loop.
		 * Total program size 20.8k insn.
		 * ~350k processed_insns
		 */
		अणु "strobemeta.o", BPF_PROG_TYPE_RAW_TRACEPOINT पूर्ण,

		/* no unroll, tiny loops */
		अणु "strobemeta_nounroll1.o", BPF_PROG_TYPE_RAW_TRACEPOINT पूर्ण,
		अणु "strobemeta_nounroll2.o", BPF_PROG_TYPE_RAW_TRACEPOINT पूर्ण,

		/* non-अंतरभूतd subprogs */
		अणु "strobemeta_subprogs.o", BPF_PROG_TYPE_RAW_TRACEPOINT पूर्ण,

		अणु "test_sysctl_loop1.o", BPF_PROG_TYPE_CGROUP_SYSCTL पूर्ण,
		अणु "test_sysctl_loop2.o", BPF_PROG_TYPE_CGROUP_SYSCTL पूर्ण,

		अणु "test_xdp_loop.o", BPF_PROG_TYPE_XDP पूर्ण,
		अणु "test_seg6_loop.o", BPF_PROG_TYPE_LWT_SEG6LOCAL पूर्ण,
	पूर्ण;
	libbpf_prपूर्णांक_fn_t old_prपूर्णांक_fn = शून्य;
	पूर्णांक err, i;

	अगर (env.verअगरier_stats) अणु
		test__क्रमce_log();
		old_prपूर्णांक_fn = libbpf_set_prपूर्णांक(libbpf_debug_prपूर्णांक);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(tests); i++) अणु
		स्थिर काष्ठा scale_test_def *test = &tests[i];

		अगर (!test__start_subtest(test->file))
			जारी;

		err = check_load(test->file, test->attach_type);
		CHECK_FAIL(err && !test->fails);
	पूर्ण

	अगर (env.verअगरier_stats)
		libbpf_set_prपूर्णांक(old_prपूर्णांक_fn);
पूर्ण
