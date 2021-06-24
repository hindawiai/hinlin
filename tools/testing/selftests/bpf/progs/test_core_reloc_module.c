<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_core_पढ़ो.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

काष्ठा bpf_tesपंचांगod_test_पढ़ो_ctx अणु
	/* field order is mixed up */
	माप_प्रकार len;
	अक्षर *buf;
	loff_t off;
पूर्ण __attribute__((preserve_access_index));

काष्ठा अणु
	अक्षर in[256];
	अक्षर out[256];
	bool skip;
	uपूर्णांक64_t my_pid_tgid;
पूर्ण data = अणुपूर्ण;

काष्ठा core_reloc_module_output अणु
	दीर्घ दीर्घ len;
	दीर्घ दीर्घ off;
	पूर्णांक पढ़ो_ctx_sz;
	bool पढ़ो_ctx_exists;
	bool buf_exists;
	bool len_exists;
	bool off_exists;
	/* we have test_progs[-flavor], so cut flavor part */
	अक्षर comm[माप("test_progs")];
	पूर्णांक comm_len;
पूर्ण;

SEC("raw_tp/bpf_testmod_test_read")
पूर्णांक BPF_PROG(test_core_module_probed,
	     काष्ठा task_काष्ठा *task,
	     काष्ठा bpf_tesपंचांगod_test_पढ़ो_ctx *पढ़ो_ctx)
अणु
#अगर __has_builtin(__builtin_preserve_क्रमागत_value)
	काष्ठा core_reloc_module_output *out = (व्योम *)&data.out;
	__u64 pid_tgid = bpf_get_current_pid_tgid();
	__u32 real_tgid = (__u32)(pid_tgid >> 32);
	__u32 real_pid = (__u32)pid_tgid;

	अगर (data.my_pid_tgid != pid_tgid)
		वापस 0;

	अगर (BPF_CORE_READ(task, pid) != real_pid || BPF_CORE_READ(task, tgid) != real_tgid)
		वापस 0;

	out->len = BPF_CORE_READ(पढ़ो_ctx, len);
	out->off = BPF_CORE_READ(पढ़ो_ctx, off);

	out->पढ़ो_ctx_sz = bpf_core_type_size(काष्ठा bpf_tesपंचांगod_test_पढ़ो_ctx);
	out->पढ़ो_ctx_exists = bpf_core_type_exists(काष्ठा bpf_tesपंचांगod_test_पढ़ो_ctx);
	out->buf_exists = bpf_core_field_exists(पढ़ो_ctx->buf);
	out->off_exists = bpf_core_field_exists(पढ़ो_ctx->off);
	out->len_exists = bpf_core_field_exists(पढ़ो_ctx->len);

	out->comm_len = BPF_CORE_READ_STR_INTO(&out->comm, task, comm);
#अन्यथा
	data.skip = true;
#पूर्ण_अगर

	वापस 0;
पूर्ण

SEC("tp_btf/bpf_testmod_test_read")
पूर्णांक BPF_PROG(test_core_module_direct,
	     काष्ठा task_काष्ठा *task,
	     काष्ठा bpf_tesपंचांगod_test_पढ़ो_ctx *पढ़ो_ctx)
अणु
#अगर __has_builtin(__builtin_preserve_क्रमागत_value)
	काष्ठा core_reloc_module_output *out = (व्योम *)&data.out;
	__u64 pid_tgid = bpf_get_current_pid_tgid();
	__u32 real_tgid = (__u32)(pid_tgid >> 32);
	__u32 real_pid = (__u32)pid_tgid;

	अगर (data.my_pid_tgid != pid_tgid)
		वापस 0;

	अगर (task->pid != real_pid || task->tgid != real_tgid)
		वापस 0;

	out->len = पढ़ो_ctx->len;
	out->off = पढ़ो_ctx->off;

	out->पढ़ो_ctx_sz = bpf_core_type_size(काष्ठा bpf_tesपंचांगod_test_पढ़ो_ctx);
	out->पढ़ो_ctx_exists = bpf_core_type_exists(काष्ठा bpf_tesपंचांगod_test_पढ़ो_ctx);
	out->buf_exists = bpf_core_field_exists(पढ़ो_ctx->buf);
	out->off_exists = bpf_core_field_exists(पढ़ो_ctx->off);
	out->len_exists = bpf_core_field_exists(पढ़ो_ctx->len);

	out->comm_len = BPF_CORE_READ_STR_INTO(&out->comm, task, comm);
#अन्यथा
	data.skip = true;
#पूर्ण_अगर

	वापस 0;
पूर्ण
