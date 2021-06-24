<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Facebook
#समावेश <test_progs.h>

अटल पूर्णांक duration = 0;

काष्ठा sec_name_test अणु
	स्थिर अक्षर sec_name[32];
	काष्ठा अणु
		पूर्णांक rc;
		क्रमागत bpf_prog_type prog_type;
		क्रमागत bpf_attach_type expected_attach_type;
	पूर्ण expected_load;
	काष्ठा अणु
		पूर्णांक rc;
		क्रमागत bpf_attach_type attach_type;
	पूर्ण expected_attach;
पूर्ण;

अटल काष्ठा sec_name_test tests[] = अणु
	अणु"InvAliD", अणु-ESRCH, 0, 0पूर्ण, अणु-EINVAL, 0पूर्ण पूर्ण,
	अणु"cgroup", अणु-ESRCH, 0, 0पूर्ण, अणु-EINVAL, 0पूर्ण पूर्ण,
	अणु"socket", अणु0, BPF_PROG_TYPE_SOCKET_FILTER, 0पूर्ण, अणु-EINVAL, 0पूर्ण पूर्ण,
	अणु"kprobe/", अणु0, BPF_PROG_TYPE_KPROBE, 0पूर्ण, अणु-EINVAL, 0पूर्ण पूर्ण,
	अणु"uprobe/", अणु0, BPF_PROG_TYPE_KPROBE, 0पूर्ण, अणु-EINVAL, 0पूर्ण पूर्ण,
	अणु"kretprobe/", अणु0, BPF_PROG_TYPE_KPROBE, 0पूर्ण, अणु-EINVAL, 0पूर्ण पूर्ण,
	अणु"uretprobe/", अणु0, BPF_PROG_TYPE_KPROBE, 0पूर्ण, अणु-EINVAL, 0पूर्ण पूर्ण,
	अणु"classifier", अणु0, BPF_PROG_TYPE_SCHED_CLS, 0पूर्ण, अणु-EINVAL, 0पूर्ण पूर्ण,
	अणु"action", अणु0, BPF_PROG_TYPE_SCHED_ACT, 0पूर्ण, अणु-EINVAL, 0पूर्ण पूर्ण,
	अणु"tracepoint/", अणु0, BPF_PROG_TYPE_TRACEPOINT, 0पूर्ण, अणु-EINVAL, 0पूर्ण पूर्ण,
	अणु"tp/", अणु0, BPF_PROG_TYPE_TRACEPOINT, 0पूर्ण, अणु-EINVAL, 0पूर्ण पूर्ण,
	अणु
		"raw_tracepoint/",
		अणु0, BPF_PROG_TYPE_RAW_TRACEPOINT, 0पूर्ण,
		अणु-EINVAL, 0पूर्ण,
	पूर्ण,
	अणु"raw_tp/", अणु0, BPF_PROG_TYPE_RAW_TRACEPOINT, 0पूर्ण, अणु-EINVAL, 0पूर्ण पूर्ण,
	अणु"xdp", अणु0, BPF_PROG_TYPE_XDP, BPF_XDPपूर्ण, अणु0, BPF_XDPपूर्ण पूर्ण,
	अणु"perf_event", अणु0, BPF_PROG_TYPE_PERF_EVENT, 0पूर्ण, अणु-EINVAL, 0पूर्ण पूर्ण,
	अणु"lwt_in", अणु0, BPF_PROG_TYPE_LWT_IN, 0पूर्ण, अणु-EINVAL, 0पूर्ण पूर्ण,
	अणु"lwt_out", अणु0, BPF_PROG_TYPE_LWT_OUT, 0पूर्ण, अणु-EINVAL, 0पूर्ण पूर्ण,
	अणु"lwt_xmit", अणु0, BPF_PROG_TYPE_LWT_XMIT, 0पूर्ण, अणु-EINVAL, 0पूर्ण पूर्ण,
	अणु"lwt_seg6local", अणु0, BPF_PROG_TYPE_LWT_SEG6LOCAL, 0पूर्ण, अणु-EINVAL, 0पूर्ण पूर्ण,
	अणु
		"cgroup_skb/ingress",
		अणु0, BPF_PROG_TYPE_CGROUP_SKB, BPF_CGROUP_INET_INGRESSपूर्ण,
		अणु0, BPF_CGROUP_INET_INGRESSपूर्ण,
	पूर्ण,
	अणु
		"cgroup_skb/egress",
		अणु0, BPF_PROG_TYPE_CGROUP_SKB, BPF_CGROUP_INET_EGRESSपूर्ण,
		अणु0, BPF_CGROUP_INET_EGRESSपूर्ण,
	पूर्ण,
	अणु"cgroup/skb", अणु0, BPF_PROG_TYPE_CGROUP_SKB, 0पूर्ण, अणु-EINVAL, 0पूर्ण पूर्ण,
	अणु
		"cgroup/sock",
		अणु0, BPF_PROG_TYPE_CGROUP_SOCK, BPF_CGROUP_INET_SOCK_CREATEपूर्ण,
		अणु0, BPF_CGROUP_INET_SOCK_CREATEपूर्ण,
	पूर्ण,
	अणु
		"cgroup/post_bind4",
		अणु0, BPF_PROG_TYPE_CGROUP_SOCK, BPF_CGROUP_INET4_POST_BINDपूर्ण,
		अणु0, BPF_CGROUP_INET4_POST_BINDपूर्ण,
	पूर्ण,
	अणु
		"cgroup/post_bind6",
		अणु0, BPF_PROG_TYPE_CGROUP_SOCK, BPF_CGROUP_INET6_POST_BINDपूर्ण,
		अणु0, BPF_CGROUP_INET6_POST_BINDपूर्ण,
	पूर्ण,
	अणु
		"cgroup/dev",
		अणु0, BPF_PROG_TYPE_CGROUP_DEVICE, BPF_CGROUP_DEVICEपूर्ण,
		अणु0, BPF_CGROUP_DEVICEपूर्ण,
	पूर्ण,
	अणु
		"sockops",
		अणु0, BPF_PROG_TYPE_SOCK_OPS, BPF_CGROUP_SOCK_OPSपूर्ण,
		अणु0, BPF_CGROUP_SOCK_OPSपूर्ण,
	पूर्ण,
	अणु
		"sk_skb/stream_parser",
		अणु0, BPF_PROG_TYPE_SK_SKB, BPF_SK_SKB_STREAM_PARSERपूर्ण,
		अणु0, BPF_SK_SKB_STREAM_PARSERपूर्ण,
	पूर्ण,
	अणु
		"sk_skb/stream_verdict",
		अणु0, BPF_PROG_TYPE_SK_SKB, BPF_SK_SKB_STREAM_VERDICTपूर्ण,
		अणु0, BPF_SK_SKB_STREAM_VERDICTपूर्ण,
	पूर्ण,
	अणु"sk_skb", अणु0, BPF_PROG_TYPE_SK_SKB, 0पूर्ण, अणु-EINVAL, 0पूर्ण पूर्ण,
	अणु
		"sk_msg",
		अणु0, BPF_PROG_TYPE_SK_MSG, BPF_SK_MSG_VERDICTपूर्ण,
		अणु0, BPF_SK_MSG_VERDICTपूर्ण,
	पूर्ण,
	अणु
		"lirc_mode2",
		अणु0, BPF_PROG_TYPE_LIRC_MODE2, BPF_LIRC_MODE2पूर्ण,
		अणु0, BPF_LIRC_MODE2पूर्ण,
	पूर्ण,
	अणु
		"flow_dissector",
		अणु0, BPF_PROG_TYPE_FLOW_DISSECTOR, BPF_FLOW_DISSECTORपूर्ण,
		अणु0, BPF_FLOW_DISSECTORपूर्ण,
	पूर्ण,
	अणु
		"cgroup/bind4",
		अणु0, BPF_PROG_TYPE_CGROUP_SOCK_ADDR, BPF_CGROUP_INET4_BINDपूर्ण,
		अणु0, BPF_CGROUP_INET4_BINDपूर्ण,
	पूर्ण,
	अणु
		"cgroup/bind6",
		अणु0, BPF_PROG_TYPE_CGROUP_SOCK_ADDR, BPF_CGROUP_INET6_BINDपूर्ण,
		अणु0, BPF_CGROUP_INET6_BINDपूर्ण,
	पूर्ण,
	अणु
		"cgroup/connect4",
		अणु0, BPF_PROG_TYPE_CGROUP_SOCK_ADDR, BPF_CGROUP_INET4_CONNECTपूर्ण,
		अणु0, BPF_CGROUP_INET4_CONNECTपूर्ण,
	पूर्ण,
	अणु
		"cgroup/connect6",
		अणु0, BPF_PROG_TYPE_CGROUP_SOCK_ADDR, BPF_CGROUP_INET6_CONNECTपूर्ण,
		अणु0, BPF_CGROUP_INET6_CONNECTपूर्ण,
	पूर्ण,
	अणु
		"cgroup/sendmsg4",
		अणु0, BPF_PROG_TYPE_CGROUP_SOCK_ADDR, BPF_CGROUP_UDP4_SENDMSGपूर्ण,
		अणु0, BPF_CGROUP_UDP4_SENDMSGपूर्ण,
	पूर्ण,
	अणु
		"cgroup/sendmsg6",
		अणु0, BPF_PROG_TYPE_CGROUP_SOCK_ADDR, BPF_CGROUP_UDP6_SENDMSGपूर्ण,
		अणु0, BPF_CGROUP_UDP6_SENDMSGपूर्ण,
	पूर्ण,
	अणु
		"cgroup/recvmsg4",
		अणु0, BPF_PROG_TYPE_CGROUP_SOCK_ADDR, BPF_CGROUP_UDP4_RECVMSGपूर्ण,
		अणु0, BPF_CGROUP_UDP4_RECVMSGपूर्ण,
	पूर्ण,
	अणु
		"cgroup/recvmsg6",
		अणु0, BPF_PROG_TYPE_CGROUP_SOCK_ADDR, BPF_CGROUP_UDP6_RECVMSGपूर्ण,
		अणु0, BPF_CGROUP_UDP6_RECVMSGपूर्ण,
	पूर्ण,
	अणु
		"cgroup/sysctl",
		अणु0, BPF_PROG_TYPE_CGROUP_SYSCTL, BPF_CGROUP_SYSCTLपूर्ण,
		अणु0, BPF_CGROUP_SYSCTLपूर्ण,
	पूर्ण,
	अणु
		"cgroup/getsockopt",
		अणु0, BPF_PROG_TYPE_CGROUP_SOCKOPT, BPF_CGROUP_GETSOCKOPTपूर्ण,
		अणु0, BPF_CGROUP_GETSOCKOPTपूर्ण,
	पूर्ण,
	अणु
		"cgroup/setsockopt",
		अणु0, BPF_PROG_TYPE_CGROUP_SOCKOPT, BPF_CGROUP_SETSOCKOPTपूर्ण,
		अणु0, BPF_CGROUP_SETSOCKOPTपूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम test_prog_type_by_name(स्थिर काष्ठा sec_name_test *test)
अणु
	क्रमागत bpf_attach_type expected_attach_type;
	क्रमागत bpf_prog_type prog_type;
	पूर्णांक rc;

	rc = libbpf_prog_type_by_name(test->sec_name, &prog_type,
				      &expected_attach_type);

	CHECK(rc != test->expected_load.rc, "check_code",
	      "prog: unexpected rc=%d for %s\n", rc, test->sec_name);

	अगर (rc)
		वापस;

	CHECK(prog_type != test->expected_load.prog_type, "check_prog_type",
	      "prog: unexpected prog_type=%d for %s\n",
	      prog_type, test->sec_name);

	CHECK(expected_attach_type != test->expected_load.expected_attach_type,
	      "check_attach_type", "prog: unexpected expected_attach_type=%d for %s\n",
	      expected_attach_type, test->sec_name);
पूर्ण

अटल व्योम test_attach_type_by_name(स्थिर काष्ठा sec_name_test *test)
अणु
	क्रमागत bpf_attach_type attach_type;
	पूर्णांक rc;

	rc = libbpf_attach_type_by_name(test->sec_name, &attach_type);

	CHECK(rc != test->expected_attach.rc, "check_ret",
	      "attach: unexpected rc=%d for %s\n", rc, test->sec_name);

	अगर (rc)
		वापस;

	CHECK(attach_type != test->expected_attach.attach_type,
	      "check_attach_type", "attach: unexpected attach_type=%d for %s\n",
	      attach_type, test->sec_name);
पूर्ण

व्योम test_section_names(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tests); ++i) अणु
		काष्ठा sec_name_test *test = &tests[i];

		test_prog_type_by_name(test);
		test_attach_type_by_name(test);
	पूर्ण
पूर्ण
