<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2020 Google LLC.
 */

#समावेश <linux/bpf.h>
#समावेश <त्रुटिसं.स>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_TASK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण secure_exec_task_map SEC(".maps");

SEC("lsm/bprm_creds_for_exec")
पूर्णांक BPF_PROG(secure_exec, काष्ठा linux_binprm *bprm)
अणु
	पूर्णांक *secureexec;

	secureexec = bpf_task_storage_get(&secure_exec_task_map,
				   bpf_get_current_task_btf(), 0,
				   BPF_LOCAL_STORAGE_GET_F_CREATE);

	अगर (secureexec && *secureexec)
		bpf_bprm_opts_set(bprm, BPF_F_BPRM_SECUREEXEC);

	वापस 0;
पूर्ण
