<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <test_progs.h>

#समावेश "cgroup_helpers.h"

#घोषणा PING_CMD	"ping -q -c1 -w1 127.0.0.1 > /dev/null"

अटल अक्षर bpf_log_buf[BPF_LOG_BUF_SIZE];

अटल पूर्णांक map_fd = -1;

अटल पूर्णांक prog_load_cnt(पूर्णांक verdict, पूर्णांक val)
अणु
	पूर्णांक cgroup_storage_fd, percpu_cgroup_storage_fd;

	अगर (map_fd < 0)
		map_fd = bpf_create_map(BPF_MAP_TYPE_ARRAY, 4, 8, 1, 0);
	अगर (map_fd < 0) अणु
		म_लिखो("failed to create map '%s'\n", म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	cgroup_storage_fd = bpf_create_map(BPF_MAP_TYPE_CGROUP_STORAGE,
				माप(काष्ठा bpf_cgroup_storage_key), 8, 0, 0);
	अगर (cgroup_storage_fd < 0) अणु
		म_लिखो("failed to create map '%s'\n", म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	percpu_cgroup_storage_fd = bpf_create_map(
		BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE,
		माप(काष्ठा bpf_cgroup_storage_key), 8, 0, 0);
	अगर (percpu_cgroup_storage_fd < 0) अणु
		म_लिखो("failed to create map '%s'\n", म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	काष्ठा bpf_insn prog[] = अणु
		BPF_MOV32_IMM(BPF_REG_0, 0),
		BPF_STX_MEM(BPF_W, BPF_REG_10, BPF_REG_0, -4), /* *(u32 *)(fp - 4) = r0 */
		BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -4), /* r2 = fp - 4 */
		BPF_LD_MAP_FD(BPF_REG_1, map_fd),
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
		BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 2),
		BPF_MOV64_IMM(BPF_REG_1, val), /* r1 = 1 */
		BPF_ATOMIC_OP(BPF_DW, BPF_ADD, BPF_REG_0, BPF_REG_1, 0),

		BPF_LD_MAP_FD(BPF_REG_1, cgroup_storage_fd),
		BPF_MOV64_IMM(BPF_REG_2, 0),
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_get_local_storage),
		BPF_MOV64_IMM(BPF_REG_1, val),
		BPF_ATOMIC_OP(BPF_W, BPF_ADD, BPF_REG_0, BPF_REG_1, 0),

		BPF_LD_MAP_FD(BPF_REG_1, percpu_cgroup_storage_fd),
		BPF_MOV64_IMM(BPF_REG_2, 0),
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_get_local_storage),
		BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_0, 0),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_3, 0x1),
		BPF_STX_MEM(BPF_W, BPF_REG_0, BPF_REG_3, 0),

		BPF_MOV64_IMM(BPF_REG_0, verdict), /* r0 = verdict */
		BPF_EXIT_INSN(),
	पूर्ण;
	माप_प्रकार insns_cnt = माप(prog) / माप(काष्ठा bpf_insn);
	पूर्णांक ret;

	ret = bpf_load_program(BPF_PROG_TYPE_CGROUP_SKB,
			       prog, insns_cnt, "GPL", 0,
			       bpf_log_buf, BPF_LOG_BUF_SIZE);

	बंद(cgroup_storage_fd);
	वापस ret;
पूर्ण

व्योम test_cgroup_attach_multi(व्योम)
अणु
	__u32 prog_ids[4], prog_cnt = 0, attach_flags, saved_prog_id;
	पूर्णांक cg1 = 0, cg2 = 0, cg3 = 0, cg4 = 0, cg5 = 0, key = 0;
	DECLARE_LIBBPF_OPTS(bpf_prog_attach_opts, attach_opts);
	पूर्णांक allow_prog[7] = अणु-1पूर्ण;
	अचिन्हित दीर्घ दीर्घ value;
	__u32 duration = 0;
	पूर्णांक i = 0;

	क्रम (i = 0; i < ARRAY_SIZE(allow_prog); i++) अणु
		allow_prog[i] = prog_load_cnt(1, 1 << i);
		अगर (CHECK(allow_prog[i] < 0, "prog_load",
			  "verifier output:\n%s\n-------\n", bpf_log_buf))
			जाओ err;
	पूर्ण

	अगर (CHECK_FAIL(setup_cgroup_environment()))
		जाओ err;

	cg1 = create_and_get_cgroup("/cg1");
	अगर (CHECK_FAIL(cg1 < 0))
		जाओ err;
	cg2 = create_and_get_cgroup("/cg1/cg2");
	अगर (CHECK_FAIL(cg2 < 0))
		जाओ err;
	cg3 = create_and_get_cgroup("/cg1/cg2/cg3");
	अगर (CHECK_FAIL(cg3 < 0))
		जाओ err;
	cg4 = create_and_get_cgroup("/cg1/cg2/cg3/cg4");
	अगर (CHECK_FAIL(cg4 < 0))
		जाओ err;
	cg5 = create_and_get_cgroup("/cg1/cg2/cg3/cg4/cg5");
	अगर (CHECK_FAIL(cg5 < 0))
		जाओ err;

	अगर (CHECK_FAIL(join_cgroup("/cg1/cg2/cg3/cg4/cg5")))
		जाओ err;

	अगर (CHECK(bpf_prog_attach(allow_prog[0], cg1, BPF_CGROUP_INET_EGRESS,
				  BPF_F_ALLOW_MULTI),
		  "prog0_attach_to_cg1_multi", "errno=%d\n", त्रुटि_सं))
		जाओ err;

	अगर (CHECK(!bpf_prog_attach(allow_prog[0], cg1, BPF_CGROUP_INET_EGRESS,
				   BPF_F_ALLOW_MULTI),
		  "fail_same_prog_attach_to_cg1", "unexpected success\n"))
		जाओ err;

	अगर (CHECK(bpf_prog_attach(allow_prog[1], cg1, BPF_CGROUP_INET_EGRESS,
				  BPF_F_ALLOW_MULTI),
		  "prog1_attach_to_cg1_multi", "errno=%d\n", त्रुटि_सं))
		जाओ err;

	अगर (CHECK(bpf_prog_attach(allow_prog[2], cg2, BPF_CGROUP_INET_EGRESS,
				  BPF_F_ALLOW_OVERRIDE),
		  "prog2_attach_to_cg2_override", "errno=%d\n", त्रुटि_सं))
		जाओ err;

	अगर (CHECK(bpf_prog_attach(allow_prog[3], cg3, BPF_CGROUP_INET_EGRESS,
				  BPF_F_ALLOW_MULTI),
		  "prog3_attach_to_cg3_multi", "errno=%d\n", त्रुटि_सं))
		जाओ err;

	अगर (CHECK(bpf_prog_attach(allow_prog[4], cg4, BPF_CGROUP_INET_EGRESS,
			    BPF_F_ALLOW_OVERRIDE),
		  "prog4_attach_to_cg4_override", "errno=%d\n", त्रुटि_सं))
		जाओ err;

	अगर (CHECK(bpf_prog_attach(allow_prog[5], cg5, BPF_CGROUP_INET_EGRESS, 0),
		  "prog5_attach_to_cg5_none", "errno=%d\n", त्रुटि_सं))
		जाओ err;

	CHECK_FAIL(प्रणाली(PING_CMD));
	CHECK_FAIL(bpf_map_lookup_elem(map_fd, &key, &value));
	CHECK_FAIL(value != 1 + 2 + 8 + 32);

	/* query the number of effective progs in cg5 */
	CHECK_FAIL(bpf_prog_query(cg5, BPF_CGROUP_INET_EGRESS,
				  BPF_F_QUERY_EFFECTIVE, शून्य, शून्य, &prog_cnt));
	CHECK_FAIL(prog_cnt != 4);
	/* retrieve prog_ids of effective progs in cg5 */
	CHECK_FAIL(bpf_prog_query(cg5, BPF_CGROUP_INET_EGRESS,
				  BPF_F_QUERY_EFFECTIVE, &attach_flags,
				  prog_ids, &prog_cnt));
	CHECK_FAIL(prog_cnt != 4);
	CHECK_FAIL(attach_flags != 0);
	saved_prog_id = prog_ids[0];
	/* check enospc handling */
	prog_ids[0] = 0;
	prog_cnt = 2;
	CHECK_FAIL(bpf_prog_query(cg5, BPF_CGROUP_INET_EGRESS,
				  BPF_F_QUERY_EFFECTIVE, &attach_flags,
				  prog_ids, &prog_cnt) != -1);
	CHECK_FAIL(त्रुटि_सं != ENOSPC);
	CHECK_FAIL(prog_cnt != 4);
	/* check that prog_ids are वापसed even when buffer is too small */
	CHECK_FAIL(prog_ids[0] != saved_prog_id);
	/* retrieve prog_id of single attached prog in cg5 */
	prog_ids[0] = 0;
	CHECK_FAIL(bpf_prog_query(cg5, BPF_CGROUP_INET_EGRESS, 0, शून्य,
				  prog_ids, &prog_cnt));
	CHECK_FAIL(prog_cnt != 1);
	CHECK_FAIL(prog_ids[0] != saved_prog_id);

	/* detach bottom program and ping again */
	अगर (CHECK(bpf_prog_detach2(-1, cg5, BPF_CGROUP_INET_EGRESS),
		  "prog_detach_from_cg5", "errno=%d\n", त्रुटि_सं))
		जाओ err;

	value = 0;
	CHECK_FAIL(bpf_map_update_elem(map_fd, &key, &value, 0));
	CHECK_FAIL(प्रणाली(PING_CMD));
	CHECK_FAIL(bpf_map_lookup_elem(map_fd, &key, &value));
	CHECK_FAIL(value != 1 + 2 + 8 + 16);

	/* test replace */

	attach_opts.flags = BPF_F_ALLOW_OVERRIDE | BPF_F_REPLACE;
	attach_opts.replace_prog_fd = allow_prog[0];
	अगर (CHECK(!bpf_prog_attach_xattr(allow_prog[6], cg1,
					 BPF_CGROUP_INET_EGRESS, &attach_opts),
		  "fail_prog_replace_override", "unexpected success\n"))
		जाओ err;
	CHECK_FAIL(त्रुटि_सं != EINVAL);

	attach_opts.flags = BPF_F_REPLACE;
	अगर (CHECK(!bpf_prog_attach_xattr(allow_prog[6], cg1,
					 BPF_CGROUP_INET_EGRESS, &attach_opts),
		  "fail_prog_replace_no_multi", "unexpected success\n"))
		जाओ err;
	CHECK_FAIL(त्रुटि_सं != EINVAL);

	attach_opts.flags = BPF_F_ALLOW_MULTI | BPF_F_REPLACE;
	attach_opts.replace_prog_fd = -1;
	अगर (CHECK(!bpf_prog_attach_xattr(allow_prog[6], cg1,
					 BPF_CGROUP_INET_EGRESS, &attach_opts),
		  "fail_prog_replace_bad_fd", "unexpected success\n"))
		जाओ err;
	CHECK_FAIL(त्रुटि_सं != EBADF);

	/* replacing a program that is not attached to cgroup should fail  */
	attach_opts.replace_prog_fd = allow_prog[3];
	अगर (CHECK(!bpf_prog_attach_xattr(allow_prog[6], cg1,
					 BPF_CGROUP_INET_EGRESS, &attach_opts),
		  "fail_prog_replace_no_ent", "unexpected success\n"))
		जाओ err;
	CHECK_FAIL(त्रुटि_सं != ENOENT);

	/* replace 1st from the top program */
	attach_opts.replace_prog_fd = allow_prog[0];
	अगर (CHECK(bpf_prog_attach_xattr(allow_prog[6], cg1,
					BPF_CGROUP_INET_EGRESS, &attach_opts),
		  "prog_replace", "errno=%d\n", त्रुटि_सं))
		जाओ err;

	/* replace program with itself */
	attach_opts.replace_prog_fd = allow_prog[6];
	अगर (CHECK(bpf_prog_attach_xattr(allow_prog[6], cg1,
					BPF_CGROUP_INET_EGRESS, &attach_opts),
		  "prog_replace", "errno=%d\n", त्रुटि_सं))
		जाओ err;

	value = 0;
	CHECK_FAIL(bpf_map_update_elem(map_fd, &key, &value, 0));
	CHECK_FAIL(प्रणाली(PING_CMD));
	CHECK_FAIL(bpf_map_lookup_elem(map_fd, &key, &value));
	CHECK_FAIL(value != 64 + 2 + 8 + 16);

	/* detach 3rd from bottom program and ping again */
	अगर (CHECK(!bpf_prog_detach2(0, cg3, BPF_CGROUP_INET_EGRESS),
		  "fail_prog_detach_from_cg3", "unexpected success\n"))
		जाओ err;

	अगर (CHECK(bpf_prog_detach2(allow_prog[3], cg3, BPF_CGROUP_INET_EGRESS),
		  "prog3_detach_from_cg3", "errno=%d\n", त्रुटि_सं))
		जाओ err;

	value = 0;
	CHECK_FAIL(bpf_map_update_elem(map_fd, &key, &value, 0));
	CHECK_FAIL(प्रणाली(PING_CMD));
	CHECK_FAIL(bpf_map_lookup_elem(map_fd, &key, &value));
	CHECK_FAIL(value != 64 + 2 + 16);

	/* detach 2nd from bottom program and ping again */
	अगर (CHECK(bpf_prog_detach2(-1, cg4, BPF_CGROUP_INET_EGRESS),
		  "prog_detach_from_cg4", "errno=%d\n", त्रुटि_सं))
		जाओ err;

	value = 0;
	CHECK_FAIL(bpf_map_update_elem(map_fd, &key, &value, 0));
	CHECK_FAIL(प्रणाली(PING_CMD));
	CHECK_FAIL(bpf_map_lookup_elem(map_fd, &key, &value));
	CHECK_FAIL(value != 64 + 2 + 4);

	prog_cnt = 4;
	CHECK_FAIL(bpf_prog_query(cg5, BPF_CGROUP_INET_EGRESS,
				  BPF_F_QUERY_EFFECTIVE, &attach_flags,
				  prog_ids, &prog_cnt));
	CHECK_FAIL(prog_cnt != 3);
	CHECK_FAIL(attach_flags != 0);
	CHECK_FAIL(bpf_prog_query(cg5, BPF_CGROUP_INET_EGRESS, 0, शून्य,
				  prog_ids, &prog_cnt));
	CHECK_FAIL(prog_cnt != 0);

err:
	क्रम (i = 0; i < ARRAY_SIZE(allow_prog); i++)
		अगर (allow_prog[i] >= 0)
			बंद(allow_prog[i]);
	बंद(cg1);
	बंद(cg2);
	बंद(cg3);
	बंद(cg4);
	बंद(cg5);
	cleanup_cgroup_environment();
पूर्ण
