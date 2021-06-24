<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश "bpf_tcp_helpers.h"

बाह्य स्थिर पूर्णांक bpf_prog_active __ksym;
बाह्य __u64 bpf_kfunc_call_test1(काष्ठा sock *sk, __u32 a, __u64 b,
				  __u32 c, __u64 d) __ksym;
बाह्य काष्ठा sock *bpf_kfunc_call_test3(काष्ठा sock *sk) __ksym;
पूर्णांक active_res = -1;
पूर्णांक sk_state = -1;

पूर्णांक __noअंतरभूत f1(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_sock *sk = skb->sk;
	पूर्णांक *active;

	अगर (!sk)
		वापस -1;

	sk = bpf_sk_fullsock(sk);
	अगर (!sk)
		वापस -1;

	active = (पूर्णांक *)bpf_per_cpu_ptr(&bpf_prog_active,
					bpf_get_smp_processor_id());
	अगर (active)
		active_res = *active;

	sk_state = bpf_kfunc_call_test3((काष्ठा sock *)sk)->__sk_common.skc_state;

	वापस (__u32)bpf_kfunc_call_test1((काष्ठा sock *)sk, 1, 2, 3, 4);
पूर्ण

SEC("classifier")
पूर्णांक kfunc_call_test1(काष्ठा __sk_buff *skb)
अणु
	वापस f1(skb);
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
