<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook

#समावेश <मानकघोष.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

पूर्णांक valid = 0;
पूर्णांक required_size_out = 0;
पूर्णांक written_stack_out = 0;
पूर्णांक written_global_out = 0;

काष्ठा अणु
	__u64 _a;
	__u64 _b;
	__u64 _c;
पूर्ण fpbe[30] = अणु0पूर्ण;

SEC("perf_event")
पूर्णांक perf_branches(व्योम *ctx)
अणु
	__u64 entries[4 * 3] = अणु0पूर्ण;
	पूर्णांक required_size, written_stack, written_global;

	/* ग_लिखो to stack */
	written_stack = bpf_पढ़ो_branch_records(ctx, entries, माप(entries), 0);
	/* ignore spurious events */
	अगर (!written_stack)
		वापस 1;

	/* get required size */
	required_size = bpf_पढ़ो_branch_records(ctx, शून्य, 0,
						BPF_F_GET_BRANCH_RECORDS_SIZE);

	written_global = bpf_पढ़ो_branch_records(ctx, fpbe, माप(fpbe), 0);
	/* ignore spurious events */
	अगर (!written_global)
		वापस 1;

	required_size_out = required_size;
	written_stack_out = written_stack;
	written_global_out = written_global;
	valid = 1;

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
