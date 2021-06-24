<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */

#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

/* weak and shared between both files */
स्थिर अस्थिर पूर्णांक my_tid __weak;
दीर्घ syscall_id __weak;

पूर्णांक output_val2;
पूर्णांक output_ctx2;
पूर्णांक output_weak2; /* should stay zero */

/* same "subprog" name in all files, but it's ok because they all are अटल */
अटल __noअंतरभूत पूर्णांक subprog(पूर्णांक x)
अणु
	/* but dअगरferent क्रमmula */
	वापस x * 2;
पूर्ण

/* Global functions can't be व्योम */
पूर्णांक set_output_val2(पूर्णांक x)
अणु
	output_val2 = 2 * x + 2 * subprog(x);
	वापस 2 * x;
पूर्ण

/* This function can't be verअगरied as global, as it assumes raw_tp/sys_enter
 * context and accesses syscall id (second argument). So we mark it as
 * __hidden, so that libbpf will mark it as अटल in the final object file,
 * right beक्रमe verअगरying it in the kernel.
 *
 * But we करोn't mark it as __hidden here, rather at बाह्य site. __hidden is
 * "contaminating" visibility, so it will get propagated from either बाह्य or
 * actual definition (including from the losing __weak definition).
 */
व्योम set_output_ctx2(__u64 *ctx)
अणु
	output_ctx2 = ctx[1]; /* दीर्घ id, same as in BPF_PROG below */
पूर्ण

/* this weak instance should lose, because it will be processed second */
__weak पूर्णांक set_output_weak(पूर्णांक x)
अणु
	output_weak2 = x;
	वापस 2 * x;
पूर्ण

बाह्य पूर्णांक set_output_val1(पूर्णांक x);

/* here we'll क्रमce set_output_ctx1() to be __hidden in the final obj file */
__hidden बाह्य व्योम set_output_ctx1(__u64 *ctx);

SEC("raw_tp/sys_enter")
पूर्णांक BPF_PROG(handler2, काष्ठा pt_regs *regs, दीर्घ id)
अणु
	अगर (my_tid != (u32)bpf_get_current_pid_tgid() || id != syscall_id)
		वापस 0;

	set_output_val1(2000);
	set_output_ctx1(ctx); /* ctx definition is hidden in BPF_PROG macro */

	/* keep input value the same across both files to aव्योम dependency on
	 * handler call order; dअगरferentiate by output_weak1 vs output_weak2.
	 */
	set_output_weak(42);

	वापस 0;
पूर्ण

अक्षर LICENSE[] SEC("license") = "GPL";
