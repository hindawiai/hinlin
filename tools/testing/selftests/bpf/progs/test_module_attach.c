<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश <bpf/bpf_core_पढ़ो.h>
#समावेश "../bpf_testmod/bpf_testmod.h"

__u32 raw_tp_पढ़ो_sz = 0;

SEC("raw_tp/bpf_testmod_test_read")
पूर्णांक BPF_PROG(handle_raw_tp,
	     काष्ठा task_काष्ठा *task, काष्ठा bpf_tesपंचांगod_test_पढ़ो_ctx *पढ़ो_ctx)
अणु
	raw_tp_पढ़ो_sz = BPF_CORE_READ(पढ़ो_ctx, len);
	वापस 0;
पूर्ण

__u32 raw_tp_bare_ग_लिखो_sz = 0;

SEC("raw_tp/bpf_testmod_test_write_bare")
पूर्णांक BPF_PROG(handle_raw_tp_bare,
	     काष्ठा task_काष्ठा *task, काष्ठा bpf_tesपंचांगod_test_ग_लिखो_ctx *ग_लिखो_ctx)
अणु
	raw_tp_bare_ग_लिखो_sz = BPF_CORE_READ(ग_लिखो_ctx, len);
	वापस 0;
पूर्ण

__u32 tp_btf_पढ़ो_sz = 0;

SEC("tp_btf/bpf_testmod_test_read")
पूर्णांक BPF_PROG(handle_tp_btf,
	     काष्ठा task_काष्ठा *task, काष्ठा bpf_tesपंचांगod_test_पढ़ो_ctx *पढ़ो_ctx)
अणु
	tp_btf_पढ़ो_sz = पढ़ो_ctx->len;
	वापस 0;
पूर्ण

__u32 fentry_पढ़ो_sz = 0;

SEC("fentry/bpf_testmod_test_read")
पूर्णांक BPF_PROG(handle_fentry,
	     काष्ठा file *file, काष्ठा kobject *kobj,
	     काष्ठा bin_attribute *bin_attr, अक्षर *buf, loff_t off, माप_प्रकार len)
अणु
	fentry_पढ़ो_sz = len;
	वापस 0;
पूर्ण

__u32 fentry_manual_पढ़ो_sz = 0;

SEC("fentry/placeholder")
पूर्णांक BPF_PROG(handle_fentry_manual,
	     काष्ठा file *file, काष्ठा kobject *kobj,
	     काष्ठा bin_attribute *bin_attr, अक्षर *buf, loff_t off, माप_प्रकार len)
अणु
	fentry_manual_पढ़ो_sz = len;
	वापस 0;
पूर्ण

__u32 fनिकास_पढ़ो_sz = 0;
पूर्णांक fनिकास_ret = 0;

SEC("fexit/bpf_testmod_test_read")
पूर्णांक BPF_PROG(handle_fनिकास,
	     काष्ठा file *file, काष्ठा kobject *kobj,
	     काष्ठा bin_attribute *bin_attr, अक्षर *buf, loff_t off, माप_प्रकार len,
	     पूर्णांक ret)
अणु
	fनिकास_पढ़ो_sz = len;
	fनिकास_ret = ret;
	वापस 0;
पूर्ण

__u32 भ_शेष_ret_पढ़ो_sz = 0;

SEC("fmod_ret/bpf_testmod_test_read")
पूर्णांक BPF_PROG(handle_भ_शेष_ret,
	     काष्ठा file *file, काष्ठा kobject *kobj,
	     काष्ठा bin_attribute *bin_attr, अक्षर *buf, loff_t off, माप_प्रकार len)
अणु
	भ_शेष_ret_पढ़ो_sz = len;
	वापस 0; /* करोn't override the निकास code */
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
