<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अस्थिर __u64 test_भ_शेष_ret = 0;
SEC("fmod_ret/security_new_get_constant")
पूर्णांक BPF_PROG(भ_शेष_ret_test, दीर्घ val, पूर्णांक ret)
अणु
	test_भ_शेष_ret = 1;
	वापस 120;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
