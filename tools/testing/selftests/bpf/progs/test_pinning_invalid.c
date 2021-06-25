<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

पूर्णांक _version SEC("version") = 1;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u64);
	__uपूर्णांक(pinning, 2); /* invalid */
पूर्ण nopinmap3 SEC(".maps");

अक्षर _license[] SEC("license") = "GPL";
