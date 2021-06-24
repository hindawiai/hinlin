<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

#घोषणा MAX_STACK_RAWTP 10

SEC("raw_tracepoint/sys_enter")
पूर्णांक bpf_prog2(व्योम *ctx)
अणु
	__u64 stack[MAX_STACK_RAWTP];
	पूर्णांक error;

	/* set all the flags which should वापस -EINVAL */
	error = bpf_get_stack(ctx, stack, 0, -1);
	अगर (error < 0)
		जाओ loop;

	वापस error;
loop:
	जबतक (1) अणु
		error++;
	पूर्ण
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
