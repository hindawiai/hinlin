<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook

#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_core_पढ़ो.h>

अक्षर _license[] SEC("license") = "GPL";

/* shuffled layout क्रम relocatable (CO-RE) पढ़ोs */
काष्ठा callback_head___shuffled अणु
	व्योम (*func)(काष्ठा callback_head___shuffled *head);
	काष्ठा callback_head___shuffled *next;
पूर्ण;

काष्ठा callback_head k_probe_in = अणुपूर्ण;
काष्ठा callback_head___shuffled k_core_in = अणुपूर्ण;

काष्ठा callback_head *u_probe_in = 0;
काष्ठा callback_head___shuffled *u_core_in = 0;

दीर्घ k_probe_out = 0;
दीर्घ u_probe_out = 0;

दीर्घ k_core_out = 0;
दीर्घ u_core_out = 0;

पूर्णांक my_pid = 0;

SEC("raw_tracepoint/sys_enter")
पूर्णांक handler(व्योम *ctx)
अणु
	पूर्णांक pid = bpf_get_current_pid_tgid() >> 32;

	अगर (my_pid != pid)
		वापस 0;

	/* next poपूर्णांकers क्रम kernel address space have to be initialized from
	 * BPF side, user-space mmaped addresses are stil user-space addresses
	 */
	k_probe_in.next = &k_probe_in;
	__builtin_preserve_access_index((अणुk_core_in.next = &k_core_in;पूर्ण));

	k_probe_out = (दीर्घ)BPF_PROBE_READ(&k_probe_in, next, next, func);
	k_core_out = (दीर्घ)BPF_CORE_READ(&k_core_in, next, next, func);
	u_probe_out = (दीर्घ)BPF_PROBE_READ_USER(u_probe_in, next, next, func);
	u_core_out = (दीर्घ)BPF_CORE_READ_USER(u_core_in, next, next, func);

	वापस 0;
पूर्ण
