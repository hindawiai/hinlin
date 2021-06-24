<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

अस्थिर __u64 test_get_स्थिरant = 0;
SEC("freplace/get_constant")
पूर्णांक security_new_get_स्थिरant(दीर्घ val)
अणु
	अगर (val != 123)
		वापस 0;
	test_get_स्थिरant = 1;
	वापस test_get_स्थिरant; /* original get_स्थिरant() वापसs val - 122 */
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
