<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */
#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर LICENSE[] SEC("license") = "GPL";

पूर्णांक pid = 0;
पूर्णांक fentry_cnt = 0;
पूर्णांक fनिकास_cnt = 0;

SEC("fentry/__x64_sys_nanosleep")
पूर्णांक BPF_PROG(nanosleep_fentry, स्थिर काष्ठा pt_regs *regs)
अणु
	अगर ((पूर्णांक)bpf_get_current_pid_tgid() != pid)
		वापस 0;

	fentry_cnt++;
	वापस 0;
पूर्ण

SEC("fexit/__x64_sys_nanosleep")
पूर्णांक BPF_PROG(nanosleep_fनिकास, स्थिर काष्ठा pt_regs *regs, पूर्णांक ret)
अणु
	अगर ((पूर्णांक)bpf_get_current_pid_tgid() != pid)
		वापस 0;

	fनिकास_cnt++;
	वापस 0;
पूर्ण
