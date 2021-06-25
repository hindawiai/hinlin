<शैली गुरु>
/* Copyright (c) 2016 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#समावेश <linux/version.h>
#समावेश <linux/ptrace.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

#घोषणा _(P)                                                                   \
	(अणु                                                                     \
		typeof(P) val = 0;                                             \
		bpf_probe_पढ़ो_kernel(&val, माप(val), &(P));                \
		val;                                                           \
	पूर्ण)

SEC("kprobe/__set_task_comm")
पूर्णांक prog(काष्ठा pt_regs *ctx)
अणु
	काष्ठा संकेत_काष्ठा *संकेत;
	काष्ठा task_काष्ठा *tsk;
	अक्षर oldcomm[16] = अणुपूर्ण;
	अक्षर newcomm[16] = अणुपूर्ण;
	u16 oom_score_adj;
	u32 pid;

	tsk = (व्योम *)PT_REGS_PARM1(ctx);

	pid = _(tsk->pid);
	bpf_probe_पढ़ो_kernel(oldcomm, माप(oldcomm), &tsk->comm);
	bpf_probe_पढ़ो_kernel(newcomm, माप(newcomm),
			      (व्योम *)PT_REGS_PARM2(ctx));
	संकेत = _(tsk->संकेत);
	oom_score_adj = _(संकेत->oom_score_adj);
	वापस 0;
पूर्ण

SEC("kprobe/urandom_read")
पूर्णांक prog2(काष्ठा pt_regs *ctx)
अणु
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
