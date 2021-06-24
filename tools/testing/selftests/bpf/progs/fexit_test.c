<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook */
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

__u64 test1_result = 0;
SEC("fexit/bpf_fentry_test1")
पूर्णांक BPF_PROG(test1, पूर्णांक a, पूर्णांक ret)
अणु
	test1_result = a == 1 && ret == 2;
	वापस 0;
पूर्ण

__u64 test2_result = 0;
SEC("fexit/bpf_fentry_test2")
पूर्णांक BPF_PROG(test2, पूर्णांक a, __u64 b, पूर्णांक ret)
अणु
	test2_result = a == 2 && b == 3 && ret == 5;
	वापस 0;
पूर्ण

__u64 test3_result = 0;
SEC("fexit/bpf_fentry_test3")
पूर्णांक BPF_PROG(test3, अक्षर a, पूर्णांक b, __u64 c, पूर्णांक ret)
अणु
	test3_result = a == 4 && b == 5 && c == 6 && ret == 15;
	वापस 0;
पूर्ण

__u64 test4_result = 0;
SEC("fexit/bpf_fentry_test4")
पूर्णांक BPF_PROG(test4, व्योम *a, अक्षर b, पूर्णांक c, __u64 d, पूर्णांक ret)
अणु
	test4_result = a == (व्योम *)7 && b == 8 && c == 9 && d == 10 &&
		ret == 34;
	वापस 0;
पूर्ण

__u64 test5_result = 0;
SEC("fexit/bpf_fentry_test5")
पूर्णांक BPF_PROG(test5, __u64 a, व्योम *b, लघु c, पूर्णांक d, __u64 e, पूर्णांक ret)
अणु
	test5_result = a == 11 && b == (व्योम *)12 && c == 13 && d == 14 &&
		e == 15 && ret == 65;
	वापस 0;
पूर्ण

__u64 test6_result = 0;
SEC("fexit/bpf_fentry_test6")
पूर्णांक BPF_PROG(test6, __u64 a, व्योम *b, लघु c, पूर्णांक d, व्योम *e, __u64 f, पूर्णांक ret)
अणु
	test6_result = a == 16 && b == (व्योम *)17 && c == 18 && d == 19 &&
		e == (व्योम *)20 && f == 21 && ret == 111;
	वापस 0;
पूर्ण

काष्ठा bpf_fentry_test_t अणु
	काष्ठा bpf_fentry_test *a;
पूर्ण;

__u64 test7_result = 0;
SEC("fexit/bpf_fentry_test7")
पूर्णांक BPF_PROG(test7, काष्ठा bpf_fentry_test_t *arg)
अणु
	अगर (!arg)
		test7_result = 1;
	वापस 0;
पूर्ण

__u64 test8_result = 0;
SEC("fexit/bpf_fentry_test8")
पूर्णांक BPF_PROG(test8, काष्ठा bpf_fentry_test_t *arg)
अणु
	अगर (!arg->a)
		test8_result = 1;
	वापस 0;
पूर्ण
