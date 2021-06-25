<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश <stdbool.h>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

पूर्णांक in = 0;
पूर्णांक out = 0;

SEC("raw_tp/sys_enter")
पूर्णांक raw_tp_prog(स्थिर व्योम *ctx)
अणु
	out = in;
	वापस 0;
पूर्ण

SEC("tp_btf/sys_enter")
पूर्णांक tp_btf_prog(स्थिर व्योम *ctx)
अणु
	out = in;
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
