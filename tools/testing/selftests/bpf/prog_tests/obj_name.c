<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>

व्योम test_obj_name(व्योम)
अणु
	काष्ठा अणु
		स्थिर अक्षर *name;
		पूर्णांक success;
		पूर्णांक expected_त्रुटि_सं;
	पूर्ण tests[] = अणु
		अणु "", 1, 0 पूर्ण,
		अणु "_123456789ABCDE", 1, 0 पूर्ण,
		अणु "_123456789ABCDEF", 0, EINVAL पूर्ण,
		अणु "_123456789ABCD\n", 0, EINVAL पूर्ण,
	पूर्ण;
	काष्ठा bpf_insn prog[] = अणु
		BPF_ALU64_IMM(BPF_MOV, BPF_REG_0, 0),
		BPF_EXIT_INSN(),
	पूर्ण;
	__u32 duration = 0;
	पूर्णांक i;

	क्रम (i = 0; i < माप(tests) / माप(tests[0]); i++) अणु
		माप_प्रकार name_len = म_माप(tests[i].name) + 1;
		जोड़ bpf_attr attr;
		माप_प्रकार ncopy;
		पूर्णांक fd;

		/* test dअगरferent attr.prog_name during BPF_PROG_LOAD */
		ncopy = name_len < माप(attr.prog_name) ?
			name_len : माप(attr.prog_name);
		bzero(&attr, माप(attr));
		attr.prog_type = BPF_PROG_TYPE_SCHED_CLS;
		attr.insn_cnt = 2;
		attr.insns = ptr_to_u64(prog);
		attr.license = ptr_to_u64("");
		स_नकल(attr.prog_name, tests[i].name, ncopy);

		fd = syscall(__NR_bpf, BPF_PROG_LOAD, &attr, माप(attr));
		CHECK((tests[i].success && fd < 0) ||
		      (!tests[i].success && fd != -1) ||
		      (!tests[i].success && त्रुटि_सं != tests[i].expected_त्रुटि_सं),
		      "check-bpf-prog-name",
		      "fd %d(%d) errno %d(%d)\n",
		       fd, tests[i].success, त्रुटि_सं, tests[i].expected_त्रुटि_सं);

		अगर (fd != -1)
			बंद(fd);

		/* test dअगरferent attr.map_name during BPF_MAP_CREATE */
		ncopy = name_len < माप(attr.map_name) ?
			name_len : माप(attr.map_name);
		bzero(&attr, माप(attr));
		attr.map_type = BPF_MAP_TYPE_ARRAY;
		attr.key_size = 4;
		attr.value_size = 4;
		attr.max_entries = 1;
		attr.map_flags = 0;
		स_नकल(attr.map_name, tests[i].name, ncopy);
		fd = syscall(__NR_bpf, BPF_MAP_CREATE, &attr, माप(attr));
		CHECK((tests[i].success && fd < 0) ||
		      (!tests[i].success && fd != -1) ||
		      (!tests[i].success && त्रुटि_सं != tests[i].expected_त्रुटि_सं),
		      "check-bpf-map-name",
		      "fd %d(%d) errno %d(%d)\n",
		      fd, tests[i].success, त्रुटि_सं, tests[i].expected_त्रुटि_सं);

		अगर (fd != -1)
			बंद(fd);
	पूर्ण
पूर्ण
