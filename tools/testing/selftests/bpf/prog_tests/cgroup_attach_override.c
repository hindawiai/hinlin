<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <test_progs.h>

#समावेश "cgroup_helpers.h"

#घोषणा FOO		"/foo"
#घोषणा BAR		"/foo/bar/"
#घोषणा PING_CMD	"ping -q -c1 -w1 127.0.0.1 > /dev/null"

अटल अक्षर bpf_log_buf[BPF_LOG_BUF_SIZE];

अटल पूर्णांक prog_load(पूर्णांक verdict)
अणु
	काष्ठा bpf_insn prog[] = अणु
		BPF_MOV64_IMM(BPF_REG_0, verdict), /* r0 = verdict */
		BPF_EXIT_INSN(),
	पूर्ण;
	माप_प्रकार insns_cnt = माप(prog) / माप(काष्ठा bpf_insn);

	वापस bpf_load_program(BPF_PROG_TYPE_CGROUP_SKB,
			       prog, insns_cnt, "GPL", 0,
			       bpf_log_buf, BPF_LOG_BUF_SIZE);
पूर्ण

व्योम test_cgroup_attach_override(व्योम)
अणु
	पूर्णांक drop_prog = -1, allow_prog = -1, foo = -1, bar = -1;
	__u32 duration = 0;

	allow_prog = prog_load(1);
	अगर (CHECK(allow_prog < 0, "prog_load_allow",
		  "verifier output:\n%s\n-------\n", bpf_log_buf))
		जाओ err;

	drop_prog = prog_load(0);
	अगर (CHECK(drop_prog < 0, "prog_load_drop",
		  "verifier output:\n%s\n-------\n", bpf_log_buf))
		जाओ err;

	foo = test__join_cgroup(FOO);
	अगर (CHECK(foo < 0, "cgroup_join_foo", "cgroup setup failed\n"))
		जाओ err;

	अगर (CHECK(bpf_prog_attach(drop_prog, foo, BPF_CGROUP_INET_EGRESS,
				  BPF_F_ALLOW_OVERRIDE),
		  "prog_attach_drop_foo_override",
		  "attach prog to %s failed, errno=%d\n", FOO, त्रुटि_सं))
		जाओ err;

	अगर (CHECK(!प्रणाली(PING_CMD), "ping_fail",
		  "ping unexpectedly succeeded\n"))
		जाओ err;

	bar = test__join_cgroup(BAR);
	अगर (CHECK(bar < 0, "cgroup_join_bar", "cgroup setup failed\n"))
		जाओ err;

	अगर (CHECK(!प्रणाली(PING_CMD), "ping_fail",
		  "ping unexpectedly succeeded\n"))
		जाओ err;

	अगर (CHECK(bpf_prog_attach(allow_prog, bar, BPF_CGROUP_INET_EGRESS,
				  BPF_F_ALLOW_OVERRIDE),
		  "prog_attach_allow_bar_override",
		  "attach prog to %s failed, errno=%d\n", BAR, त्रुटि_सं))
		जाओ err;

	अगर (CHECK(प्रणाली(PING_CMD), "ping_ok", "ping failed\n"))
		जाओ err;

	अगर (CHECK(bpf_prog_detach(bar, BPF_CGROUP_INET_EGRESS),
		  "prog_detach_bar",
		  "detach prog from %s failed, errno=%d\n", BAR, त्रुटि_सं))
		जाओ err;

	अगर (CHECK(!प्रणाली(PING_CMD), "ping_fail",
		  "ping unexpectedly succeeded\n"))
		जाओ err;

	अगर (CHECK(bpf_prog_attach(allow_prog, bar, BPF_CGROUP_INET_EGRESS,
				  BPF_F_ALLOW_OVERRIDE),
		  "prog_attach_allow_bar_override",
		  "attach prog to %s failed, errno=%d\n", BAR, त्रुटि_सं))
		जाओ err;

	अगर (CHECK(bpf_prog_detach(foo, BPF_CGROUP_INET_EGRESS),
		  "prog_detach_foo",
		  "detach prog from %s failed, errno=%d\n", FOO, त्रुटि_सं))
		जाओ err;

	अगर (CHECK(प्रणाली(PING_CMD), "ping_ok", "ping failed\n"))
		जाओ err;

	अगर (CHECK(bpf_prog_attach(allow_prog, bar, BPF_CGROUP_INET_EGRESS,
				  BPF_F_ALLOW_OVERRIDE),
		  "prog_attach_allow_bar_override",
		  "attach prog to %s failed, errno=%d\n", BAR, त्रुटि_सं))
		जाओ err;

	अगर (CHECK(!bpf_prog_attach(allow_prog, bar, BPF_CGROUP_INET_EGRESS, 0),
		  "fail_prog_attach_allow_bar_none",
		  "attach prog to %s unexpectedly succeeded\n", BAR))
		जाओ err;

	अगर (CHECK(bpf_prog_detach(bar, BPF_CGROUP_INET_EGRESS),
		  "prog_detach_bar",
		  "detach prog from %s failed, errno=%d\n", BAR, त्रुटि_सं))
		जाओ err;

	अगर (CHECK(!bpf_prog_detach(foo, BPF_CGROUP_INET_EGRESS),
		  "fail_prog_detach_foo",
		  "double detach from %s unexpectedly succeeded\n", FOO))
		जाओ err;

	अगर (CHECK(bpf_prog_attach(allow_prog, foo, BPF_CGROUP_INET_EGRESS, 0),
		  "prog_attach_allow_foo_none",
		  "attach prog to %s failed, errno=%d\n", FOO, त्रुटि_सं))
		जाओ err;

	अगर (CHECK(!bpf_prog_attach(allow_prog, bar, BPF_CGROUP_INET_EGRESS, 0),
		  "fail_prog_attach_allow_bar_none",
		  "attach prog to %s unexpectedly succeeded\n", BAR))
		जाओ err;

	अगर (CHECK(!bpf_prog_attach(allow_prog, bar, BPF_CGROUP_INET_EGRESS,
				   BPF_F_ALLOW_OVERRIDE),
		  "fail_prog_attach_allow_bar_override",
		  "attach prog to %s unexpectedly succeeded\n", BAR))
		जाओ err;

	अगर (CHECK(!bpf_prog_attach(allow_prog, foo, BPF_CGROUP_INET_EGRESS,
				   BPF_F_ALLOW_OVERRIDE),
		  "fail_prog_attach_allow_foo_override",
		  "attach prog to %s unexpectedly succeeded\n", FOO))
		जाओ err;

	अगर (CHECK(bpf_prog_attach(drop_prog, foo, BPF_CGROUP_INET_EGRESS, 0),
		  "prog_attach_drop_foo_none",
		  "attach prog to %s failed, errno=%d\n", FOO, त्रुटि_सं))
		जाओ err;

err:
	बंद(foo);
	बंद(bar);
	बंद(allow_prog);
	बंद(drop_prog);
पूर्ण
