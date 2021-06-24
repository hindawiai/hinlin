<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <test_progs.h>
#समावेश "cgroup_helpers.h"
#समावेश "testing_helpers.h"
#समावेश "test_cgroup_link.skel.h"

अटल __u32 duration = 0;
#घोषणा PING_CMD	"ping -q -c1 -w1 127.0.0.1 > /dev/null"

अटल काष्ठा test_cgroup_link *skel = शून्य;

पूर्णांक ping_and_check(पूर्णांक exp_calls, पूर्णांक exp_alt_calls)
अणु
	skel->bss->calls = 0;
	skel->bss->alt_calls = 0;
	CHECK_FAIL(प्रणाली(PING_CMD));
	अगर (CHECK(skel->bss->calls != exp_calls, "call_cnt",
		  "exp %d, got %d\n", exp_calls, skel->bss->calls))
		वापस -EINVAL;
	अगर (CHECK(skel->bss->alt_calls != exp_alt_calls, "alt_call_cnt",
		  "exp %d, got %d\n", exp_alt_calls, skel->bss->alt_calls))
		वापस -EINVAL;
	वापस 0;
पूर्ण

व्योम test_cgroup_link(व्योम)
अणु
	काष्ठा अणु
		स्थिर अक्षर *path;
		पूर्णांक fd;
	पूर्ण cgs[] = अणु
		अणु "/cg1" पूर्ण,
		अणु "/cg1/cg2" पूर्ण,
		अणु "/cg1/cg2/cg3" पूर्ण,
		अणु "/cg1/cg2/cg3/cg4" पूर्ण,
	पूर्ण;
	पूर्णांक last_cg = ARRAY_SIZE(cgs) - 1, cg_nr = ARRAY_SIZE(cgs);
	DECLARE_LIBBPF_OPTS(bpf_link_update_opts, link_upd_opts);
	काष्ठा bpf_link *links[ARRAY_SIZE(cgs)] = अणुपूर्ण, *पंचांगp_link;
	__u32 prog_ids[ARRAY_SIZE(cgs)], prog_cnt = 0, attach_flags, prog_id;
	काष्ठा bpf_link_info info;
	पूर्णांक i = 0, err, prog_fd;
	bool detach_legacy = false;

	skel = test_cgroup_link__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open_load", "failed to open/load skeleton\n"))
		वापस;
	prog_fd = bpf_program__fd(skel->progs.egress);

	err = setup_cgroup_environment();
	अगर (CHECK(err, "cg_init", "failed: %d\n", err))
		जाओ cleanup;

	क्रम (i = 0; i < cg_nr; i++) अणु
		cgs[i].fd = create_and_get_cgroup(cgs[i].path);
		अगर (!ASSERT_GE(cgs[i].fd, 0, "cg_create"))
			जाओ cleanup;
	पूर्ण

	err = join_cgroup(cgs[last_cg].path);
	अगर (CHECK(err, "cg_join", "fail: %d\n", err))
		जाओ cleanup;

	क्रम (i = 0; i < cg_nr; i++) अणु
		links[i] = bpf_program__attach_cgroup(skel->progs.egress,
						      cgs[i].fd);
		अगर (CHECK(IS_ERR(links[i]), "cg_attach", "i: %d, err: %ld\n",
				 i, PTR_ERR(links[i])))
			जाओ cleanup;
	पूर्ण

	ping_and_check(cg_nr, 0);

	/* query the number of effective progs and attach flags in root cg */
	err = bpf_prog_query(cgs[0].fd, BPF_CGROUP_INET_EGRESS,
			     BPF_F_QUERY_EFFECTIVE, &attach_flags, शून्य,
			     &prog_cnt);
	CHECK_FAIL(err);
	CHECK_FAIL(attach_flags != BPF_F_ALLOW_MULTI);
	अगर (CHECK(prog_cnt != 1, "effect_cnt", "exp %d, got %d\n", 1, prog_cnt))
		जाओ cleanup;

	/* query the number of effective progs in last cg */
	err = bpf_prog_query(cgs[last_cg].fd, BPF_CGROUP_INET_EGRESS,
			     BPF_F_QUERY_EFFECTIVE, शून्य, शून्य,
			     &prog_cnt);
	CHECK_FAIL(err);
	CHECK_FAIL(attach_flags != BPF_F_ALLOW_MULTI);
	अगर (CHECK(prog_cnt != cg_nr, "effect_cnt", "exp %d, got %d\n",
		  cg_nr, prog_cnt))
		जाओ cleanup;

	/* query the effective prog IDs in last cg */
	err = bpf_prog_query(cgs[last_cg].fd, BPF_CGROUP_INET_EGRESS,
			     BPF_F_QUERY_EFFECTIVE, &attach_flags,
			     prog_ids, &prog_cnt);
	CHECK_FAIL(err);
	CHECK_FAIL(attach_flags != BPF_F_ALLOW_MULTI);
	अगर (CHECK(prog_cnt != cg_nr, "effect_cnt", "exp %d, got %d\n",
		  cg_nr, prog_cnt))
		जाओ cleanup;
	क्रम (i = 1; i < prog_cnt; i++) अणु
		CHECK(prog_ids[i - 1] != prog_ids[i], "prog_id_check",
		      "idx %d, prev id %d, cur id %d\n",
		      i, prog_ids[i - 1], prog_ids[i]);
	पूर्ण

	/* detach bottom program and ping again */
	bpf_link__destroy(links[last_cg]);
	links[last_cg] = शून्य;

	ping_and_check(cg_nr - 1, 0);

	/* mix in with non link-based multi-attachments */
	err = bpf_prog_attach(prog_fd, cgs[last_cg].fd,
			      BPF_CGROUP_INET_EGRESS, BPF_F_ALLOW_MULTI);
	अगर (CHECK(err, "cg_attach_legacy", "errno=%d\n", त्रुटि_सं))
		जाओ cleanup;
	detach_legacy = true;

	links[last_cg] = bpf_program__attach_cgroup(skel->progs.egress,
						    cgs[last_cg].fd);
	अगर (CHECK(IS_ERR(links[last_cg]), "cg_attach", "err: %ld\n",
		  PTR_ERR(links[last_cg])))
		जाओ cleanup;

	ping_and_check(cg_nr + 1, 0);

	/* detach link */
	bpf_link__destroy(links[last_cg]);
	links[last_cg] = शून्य;

	/* detach legacy */
	err = bpf_prog_detach2(prog_fd, cgs[last_cg].fd, BPF_CGROUP_INET_EGRESS);
	अगर (CHECK(err, "cg_detach_legacy", "errno=%d\n", त्रुटि_सं))
		जाओ cleanup;
	detach_legacy = false;

	/* attach legacy exclusive prog attachment */
	err = bpf_prog_attach(prog_fd, cgs[last_cg].fd,
			      BPF_CGROUP_INET_EGRESS, 0);
	अगर (CHECK(err, "cg_attach_exclusive", "errno=%d\n", त्रुटि_सं))
		जाओ cleanup;
	detach_legacy = true;

	/* attempt to mix in with multi-attach bpf_link */
	पंचांगp_link = bpf_program__attach_cgroup(skel->progs.egress,
					      cgs[last_cg].fd);
	अगर (CHECK(!IS_ERR(पंचांगp_link), "cg_attach_fail", "unexpected success!\n")) अणु
		bpf_link__destroy(पंचांगp_link);
		जाओ cleanup;
	पूर्ण

	ping_and_check(cg_nr, 0);

	/* detach */
	err = bpf_prog_detach2(prog_fd, cgs[last_cg].fd, BPF_CGROUP_INET_EGRESS);
	अगर (CHECK(err, "cg_detach_legacy", "errno=%d\n", त्रुटि_सं))
		जाओ cleanup;
	detach_legacy = false;

	ping_and_check(cg_nr - 1, 0);

	/* attach back link-based one */
	links[last_cg] = bpf_program__attach_cgroup(skel->progs.egress,
						    cgs[last_cg].fd);
	अगर (CHECK(IS_ERR(links[last_cg]), "cg_attach", "err: %ld\n",
		  PTR_ERR(links[last_cg])))
		जाओ cleanup;

	ping_and_check(cg_nr, 0);

	/* check legacy exclusive prog can't be attached */
	err = bpf_prog_attach(prog_fd, cgs[last_cg].fd,
			      BPF_CGROUP_INET_EGRESS, 0);
	अगर (CHECK(!err, "cg_attach_exclusive", "unexpected success")) अणु
		bpf_prog_detach2(prog_fd, cgs[last_cg].fd, BPF_CGROUP_INET_EGRESS);
		जाओ cleanup;
	पूर्ण

	/* replace BPF programs inside their links क्रम all but first link */
	क्रम (i = 1; i < cg_nr; i++) अणु
		err = bpf_link__update_program(links[i], skel->progs.egress_alt);
		अगर (CHECK(err, "prog_upd", "link #%d\n", i))
			जाओ cleanup;
	पूर्ण

	ping_and_check(1, cg_nr - 1);

	/* Attempt program update with wrong expected BPF program */
	link_upd_opts.old_prog_fd = bpf_program__fd(skel->progs.egress_alt);
	link_upd_opts.flags = BPF_F_REPLACE;
	err = bpf_link_update(bpf_link__fd(links[0]),
			      bpf_program__fd(skel->progs.egress_alt),
			      &link_upd_opts);
	अगर (CHECK(err == 0 || त्रुटि_सं != EPERM, "prog_cmpxchg1",
		  "unexpectedly succeeded, err %d, errno %d\n", err, -त्रुटि_सं))
		जाओ cleanup;

	/* Compare-exchange single link program from egress to egress_alt */
	link_upd_opts.old_prog_fd = bpf_program__fd(skel->progs.egress);
	link_upd_opts.flags = BPF_F_REPLACE;
	err = bpf_link_update(bpf_link__fd(links[0]),
			      bpf_program__fd(skel->progs.egress_alt),
			      &link_upd_opts);
	अगर (CHECK(err, "prog_cmpxchg2", "errno %d\n", -त्रुटि_सं))
		जाओ cleanup;

	/* ping */
	ping_and_check(0, cg_nr);

	/* बंद cgroup FDs beक्रमe detaching links */
	क्रम (i = 0; i < cg_nr; i++) अणु
		अगर (cgs[i].fd > 0) अणु
			बंद(cgs[i].fd);
			cgs[i].fd = -1;
		पूर्ण
	पूर्ण

	/* BPF programs should still get called */
	ping_and_check(0, cg_nr);

	prog_id = link_info_prog_id(links[0], &info);
	CHECK(prog_id == 0, "link_info", "failed\n");
	CHECK(info.cgroup.cgroup_id == 0, "cgroup_id", "unexpected %llu\n", info.cgroup.cgroup_id);

	err = bpf_link__detach(links[0]);
	अगर (CHECK(err, "link_detach", "failed %d\n", err))
		जाओ cleanup;

	/* cgroup_id should be zero in link_info */
	prog_id = link_info_prog_id(links[0], &info);
	CHECK(prog_id == 0, "link_info", "failed\n");
	CHECK(info.cgroup.cgroup_id != 0, "cgroup_id", "unexpected %llu\n", info.cgroup.cgroup_id);

	/* First BPF program shouldn't be called anymore */
	ping_and_check(0, cg_nr - 1);

	/* leave cgroup and हटाओ them, करोn't detach programs */
	cleanup_cgroup_environment();

	/* BPF programs should have been स्वतः-detached */
	ping_and_check(0, 0);

cleanup:
	अगर (detach_legacy)
		bpf_prog_detach2(prog_fd, cgs[last_cg].fd,
				 BPF_CGROUP_INET_EGRESS);

	क्रम (i = 0; i < cg_nr; i++) अणु
		अगर (!IS_ERR(links[i]))
			bpf_link__destroy(links[i]);
	पूर्ण
	test_cgroup_link__destroy(skel);

	क्रम (i = 0; i < cg_nr; i++) अणु
		अगर (cgs[i].fd > 0)
			बंद(cgs[i].fd);
	पूर्ण
	cleanup_cgroup_environment();
पूर्ण
