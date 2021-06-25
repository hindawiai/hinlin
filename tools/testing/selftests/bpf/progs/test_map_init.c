<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Tessares SA <http://www.tessares.net> */

#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>

__u64 inKey = 0;
__u64 inValue = 0;
__u32 inPid = 0;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_HASH);
	__uपूर्णांक(max_entries, 2);
	__type(key, __u64);
	__type(value, __u64);
पूर्ण hashmap1 SEC(".maps");


SEC("tp/syscalls/sys_enter_getpgid")
पूर्णांक sysenter_getpgid(स्थिर व्योम *ctx)
अणु
	/* Just करो it क्रम once, when called from our own test prog. This
	 * ensures the map value is only updated क्रम a single CPU.
	 */
	पूर्णांक cur_pid = bpf_get_current_pid_tgid() >> 32;

	अगर (cur_pid == inPid)
		bpf_map_update_elem(&hashmap1, &inKey, &inValue, BPF_NOEXIST);

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
