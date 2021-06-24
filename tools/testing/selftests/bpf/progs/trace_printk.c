<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020, Oracle and/or its affiliates.

#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

पूर्णांक trace_prपूर्णांकk_ret = 0;
पूर्णांक trace_prपूर्णांकk_ran = 0;

SEC("tp/raw_syscalls/sys_enter")
पूर्णांक sys_enter(व्योम *ctx)
अणु
	अटल स्थिर अक्षर fmt[] = "testing,testing %d\n";

	trace_prपूर्णांकk_ret = bpf_trace_prपूर्णांकk(fmt, माप(fmt),
					    ++trace_prपूर्णांकk_ran);
	वापस 0;
पूर्ण
