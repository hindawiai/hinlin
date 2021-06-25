<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018 Facebook */
#समावेश <uapi/linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

SEC("raw_tracepoint/task_rename")
पूर्णांक prog(काष्ठा bpf_raw_tracepoपूर्णांक_args *ctx)
अणु
	वापस 0;
पूर्ण

SEC("raw_tracepoint/urandom_read")
पूर्णांक prog2(काष्ठा bpf_raw_tracepoपूर्णांक_args *ctx)
अणु
	वापस 0;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
