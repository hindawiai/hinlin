<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश <bpf/bpf_core_पढ़ो.h>

bool prog1_called = false;
bool prog2_called = false;
bool prog3_called = false;

SEC("raw_tp/sys_enter")
पूर्णांक prog1(स्थिर व्योम *ctx)
अणु
	prog1_called = true;
	वापस 0;
पूर्ण

SEC("raw_tp/sys_exit")
पूर्णांक prog2(स्थिर व्योम *ctx)
अणु
	prog2_called = true;
	वापस 0;
पूर्ण

काष्ठा fake_kernel_काष्ठा अणु
	पूर्णांक whatever;
पूर्ण __attribute__((preserve_access_index));

SEC("fentry/unexisting-kprobe-will-fail-if-loaded")
पूर्णांक prog3(स्थिर व्योम *ctx)
अणु
	काष्ठा fake_kernel_काष्ठा *fake = (व्योम *)ctx;
	fake->whatever = 123;
	prog3_called = true;
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
