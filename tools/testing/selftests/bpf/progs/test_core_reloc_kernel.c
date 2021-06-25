<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook

#समावेश <linux/bpf.h>
#समावेश <मानक_निवेशt.h>
#समावेश <stdbool.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_core_पढ़ो.h>

अक्षर _license[] SEC("license") = "GPL";

काष्ठा अणु
	अक्षर in[256];
	अक्षर out[256];
	bool skip;
	uपूर्णांक64_t my_pid_tgid;
पूर्ण data = अणुपूर्ण;

काष्ठा core_reloc_kernel_output अणु
	पूर्णांक valid[10];
	/* we have test_progs[-flavor], so cut flavor part */
	अक्षर comm[माप("test_progs")];
	पूर्णांक comm_len;
पूर्ण;

काष्ठा task_काष्ठा अणु
	पूर्णांक pid;
	पूर्णांक tgid;
	अक्षर comm[16];
	काष्ठा task_काष्ठा *group_leader;
पूर्ण;

#घोषणा CORE_READ(dst, src) bpf_core_पढ़ो(dst, माप(*(dst)), src)

SEC("raw_tracepoint/sys_enter")
पूर्णांक test_core_kernel(व्योम *ctx)
अणु
	काष्ठा task_काष्ठा *task = (व्योम *)bpf_get_current_task();
	काष्ठा core_reloc_kernel_output *out = (व्योम *)&data.out;
	uपूर्णांक64_t pid_tgid = bpf_get_current_pid_tgid();
	uपूर्णांक32_t real_tgid = (uपूर्णांक32_t)pid_tgid;
	पूर्णांक pid, tgid;

	अगर (data.my_pid_tgid != pid_tgid)
		वापस 0;

	अगर (CORE_READ(&pid, &task->pid) ||
	    CORE_READ(&tgid, &task->tgid))
		वापस 1;

	/* validate pid + tgid matches */
	out->valid[0] = (((uपूर्णांक64_t)pid << 32) | tgid) == pid_tgid;

	/* test variadic BPF_CORE_READ macros */
	out->valid[1] = BPF_CORE_READ(task,
				      tgid) == real_tgid;
	out->valid[2] = BPF_CORE_READ(task,
				      group_leader,
				      tgid) == real_tgid;
	out->valid[3] = BPF_CORE_READ(task,
				      group_leader, group_leader,
				      tgid) == real_tgid;
	out->valid[4] = BPF_CORE_READ(task,
				      group_leader, group_leader, group_leader,
				      tgid) == real_tgid;
	out->valid[5] = BPF_CORE_READ(task,
				      group_leader, group_leader, group_leader,
				      group_leader,
				      tgid) == real_tgid;
	out->valid[6] = BPF_CORE_READ(task,
				      group_leader, group_leader, group_leader,
				      group_leader, group_leader,
				      tgid) == real_tgid;
	out->valid[7] = BPF_CORE_READ(task,
				      group_leader, group_leader, group_leader,
				      group_leader, group_leader, group_leader,
				      tgid) == real_tgid;
	out->valid[8] = BPF_CORE_READ(task,
				      group_leader, group_leader, group_leader,
				      group_leader, group_leader, group_leader,
				      group_leader,
				      tgid) == real_tgid;
	out->valid[9] = BPF_CORE_READ(task,
				      group_leader, group_leader, group_leader,
				      group_leader, group_leader, group_leader,
				      group_leader, group_leader,
				      tgid) == real_tgid;

	/* test BPF_CORE_READ_STR_INTO() वापसs correct code and contents */
	out->comm_len = BPF_CORE_READ_STR_INTO(
		&out->comm, task,
		group_leader, group_leader, group_leader, group_leader,
		group_leader, group_leader, group_leader, group_leader,
		comm);

	वापस 0;
पूर्ण

