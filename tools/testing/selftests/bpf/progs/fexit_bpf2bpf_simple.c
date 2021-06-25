<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook */
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

काष्ठा sk_buff अणु
	अचिन्हित पूर्णांक len;
पूर्ण;

__u64 test_result = 0;

SEC("fexit/test_pkt_md_access")
पूर्णांक BPF_PROG(test_मुख्य2, काष्ठा sk_buff *skb, पूर्णांक ret)
अणु
	पूर्णांक len;

	__builtin_preserve_access_index((अणु
		len = skb->len;
	पूर्ण));
	अगर (len != 74 || ret != 0)
		वापस 0;

	test_result = 1;
	वापस 0;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
