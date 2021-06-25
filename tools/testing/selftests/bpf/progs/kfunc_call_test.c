<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश "bpf_tcp_helpers.h"

बाह्य पूर्णांक bpf_kfunc_call_test2(काष्ठा sock *sk, __u32 a, __u32 b) __ksym;
बाह्य __u64 bpf_kfunc_call_test1(काष्ठा sock *sk, __u32 a, __u64 b,
				  __u32 c, __u64 d) __ksym;

SEC("classifier")
पूर्णांक kfunc_call_test2(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_sock *sk = skb->sk;

	अगर (!sk)
		वापस -1;

	sk = bpf_sk_fullsock(sk);
	अगर (!sk)
		वापस -1;

	वापस bpf_kfunc_call_test2((काष्ठा sock *)sk, 1, 2);
पूर्ण

SEC("classifier")
पूर्णांक kfunc_call_test1(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_sock *sk = skb->sk;
	__u64 a = 1ULL << 32;
	__u32 ret;

	अगर (!sk)
		वापस -1;

	sk = bpf_sk_fullsock(sk);
	अगर (!sk)
		वापस -1;

	a = bpf_kfunc_call_test1((काष्ठा sock *)sk, 1, a | 2, 3, a | 4);
	ret = a >> 32;   /* ret should be 2 */
	ret += (__u32)a; /* ret should be 12 */

	वापस ret;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
