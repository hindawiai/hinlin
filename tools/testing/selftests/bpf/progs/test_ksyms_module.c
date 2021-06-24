<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */

#समावेश "vmlinux.h"

#समावेश <bpf/bpf_helpers.h>

बाह्य स्थिर पूर्णांक bpf_tesपंचांगod_ksym_percpu __ksym;

पूर्णांक out_mod_ksym_global = 0;
bool triggered = false;

SEC("raw_tp/sys_enter")
पूर्णांक handler(स्थिर व्योम *ctx)
अणु
	पूर्णांक *val;
	__u32 cpu;

	val = (पूर्णांक *)bpf_this_cpu_ptr(&bpf_tesपंचांगod_ksym_percpu);
	out_mod_ksym_global = *val;
	triggered = true;

	वापस 0;
पूर्ण

अक्षर LICENSE[] SEC("license") = "GPL";
