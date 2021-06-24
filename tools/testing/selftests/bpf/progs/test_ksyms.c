<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook */

#समावेश <stdbool.h>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

__u64 out__bpf_link_fops = -1;
__u64 out__bpf_link_fops1 = -1;
__u64 out__btf_size = -1;
__u64 out__per_cpu_start = -1;

बाह्य स्थिर व्योम bpf_link_fops __ksym;
बाह्य स्थिर व्योम __start_BTF __ksym;
बाह्य स्थिर व्योम __stop_BTF __ksym;
बाह्य स्थिर व्योम __per_cpu_start __ksym;
/* non-existing symbol, weak, शेष to zero */
बाह्य स्थिर व्योम bpf_link_fops1 __ksym __weak;

SEC("raw_tp/sys_enter")
पूर्णांक handler(स्थिर व्योम *ctx)
अणु
	out__bpf_link_fops = (__u64)&bpf_link_fops;
	out__btf_size = (__u64)(&__stop_BTF - &__start_BTF);
	out__per_cpu_start = (__u64)&__per_cpu_start;

	out__bpf_link_fops1 = (__u64)&bpf_link_fops1;

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
