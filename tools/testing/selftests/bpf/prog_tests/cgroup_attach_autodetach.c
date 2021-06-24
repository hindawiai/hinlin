<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <test_progs.h>

#समावेश "cgroup_helpers.h"

#घोषणा PING_CMD	"ping -q -c1 -w1 127.0.0.1 > /dev/null"

अटल अक्षर bpf_log_buf[BPF_LOG_BUF_SIZE];

अटल पूर्णांक prog_load(व्योम)
अणु
	काष्ठा bpf_insn prog[] = अणु
		BPF_MOV64_IMM(BPF_REG_0, 1), /* r0 = 1 */
		BPF_EXIT_INSN(),
	पूर्ण;
	माप_प्रकार insns_cnt = माप(prog) / माप(काष्ठा bpf_insn);

	वापस bpf_load_program(BPF_PROG_TYPE_CGROUP_SKB,
			       prog, insns_cnt, "GPL", 0,
			       bpf_log_buf, BPF_LOG_BUF_SIZE);
पूर्ण

व्योम test_cgroup_attach_स्वतःdetach(व्योम)
अणु
	__u32 duration = 0, prog_cnt = 4, attach_flags;
	पूर्णांक allow_prog[2] = अणु-1पूर्ण;
	__u32 prog_ids[2] = अणु0पूर्ण;
	व्योम *ptr = शून्य;
	पूर्णांक cg = 0, i;
	पूर्णांक attempts;

	क्रम (i = 0; i < ARRAY_SIZE(allow_prog); i++) अणु
		allow_prog[i] = prog_load();
		अगर (CHECK(allow_prog[i] < 0, "prog_load",
			  "verifier output:\n%s\n-------\n", bpf_log_buf))
			जाओ err;
	पूर्ण

	अगर (CHECK_FAIL(setup_cgroup_environment()))
		जाओ err;

	/* create a cgroup, attach two programs and remember their ids */
	cg = create_and_get_cgroup("/cg_autodetach");
	अगर (CHECK_FAIL(cg < 0))
		जाओ err;

	अगर (CHECK_FAIL(join_cgroup("/cg_autodetach")))
		जाओ err;

	क्रम (i = 0; i < ARRAY_SIZE(allow_prog); i++)
		अगर (CHECK(bpf_prog_attach(allow_prog[i], cg,
					  BPF_CGROUP_INET_EGRESS,
					  BPF_F_ALLOW_MULTI),
			  "prog_attach", "prog[%d], errno=%d\n", i, त्रुटि_सं))
			जाओ err;

	/* make sure that programs are attached and run some traffic */
	अगर (CHECK(bpf_prog_query(cg, BPF_CGROUP_INET_EGRESS, 0, &attach_flags,
				 prog_ids, &prog_cnt),
		  "prog_query", "errno=%d\n", त्रुटि_सं))
		जाओ err;
	अगर (CHECK_FAIL(प्रणाली(PING_CMD)))
		जाओ err;

	/* allocate some memory (4Mb) to pin the original cgroup */
	ptr = दो_स्मृति(4 * (1 << 20));
	अगर (CHECK_FAIL(!ptr))
		जाओ err;

	/* बंद programs and cgroup fd */
	क्रम (i = 0; i < ARRAY_SIZE(allow_prog); i++) अणु
		बंद(allow_prog[i]);
		allow_prog[i] = -1;
	पूर्ण

	बंद(cg);
	cg = 0;

	/* leave the cgroup and हटाओ it. करोn't detach programs */
	cleanup_cgroup_environment();

	/* रुको क्रम the asynchronous स्वतः-detachment.
	 * रुको क्रम no more than 5 sec and give up.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(prog_ids); i++) अणु
		क्रम (attempts = 5; attempts >= 0; attempts--) अणु
			पूर्णांक fd = bpf_prog_get_fd_by_id(prog_ids[i]);

			अगर (fd < 0)
				अवरोध;

			/* करोn't leave the fd खोलो */
			बंद(fd);

			अगर (CHECK_FAIL(!attempts))
				जाओ err;

			sleep(1);
		पूर्ण
	पूर्ण

err:
	क्रम (i = 0; i < ARRAY_SIZE(allow_prog); i++)
		अगर (allow_prog[i] >= 0)
			बंद(allow_prog[i]);
	अगर (cg)
		बंद(cg);
	मुक्त(ptr);
	cleanup_cgroup_environment();
पूर्ण
