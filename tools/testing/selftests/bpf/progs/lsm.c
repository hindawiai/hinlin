<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2020 Google LLC.
 */

#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश  <त्रुटिसं.स>

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण array SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण hash SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_LRU_HASH);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण lru_hash SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण percpu_array SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_HASH);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण percpu_hash SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_LRU_PERCPU_HASH);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण lru_percpu_hash SEC(".maps");

काष्ठा inner_map अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, पूर्णांक);
	__type(value, __u64);
पूर्ण inner_map SEC(".maps");

काष्ठा outer_arr अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY_OF_MAPS);
	__uपूर्णांक(max_entries, 1);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
	__array(values, काष्ठा inner_map);
पूर्ण outer_arr SEC(".maps") = अणु
	.values = अणु [0] = &inner_map पूर्ण,
पूर्ण;

काष्ठा outer_hash अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH_OF_MAPS);
	__uपूर्णांक(max_entries, 1);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__array(values, काष्ठा inner_map);
पूर्ण outer_hash SEC(".maps") = अणु
	.values = अणु [0] = &inner_map पूर्ण,
पूर्ण;

अक्षर _license[] SEC("license") = "GPL";

पूर्णांक monitored_pid = 0;
पूर्णांक mprotect_count = 0;
पूर्णांक bprm_count = 0;

SEC("lsm/file_mprotect")
पूर्णांक BPF_PROG(test_पूर्णांक_hook, काष्ठा vm_area_काष्ठा *vma,
	     अचिन्हित दीर्घ reqprot, अचिन्हित दीर्घ prot, पूर्णांक ret)
अणु
	अगर (ret != 0)
		वापस ret;

	__u32 pid = bpf_get_current_pid_tgid() >> 32;
	पूर्णांक is_stack = 0;

	is_stack = (vma->vm_start <= vma->vm_mm->start_stack &&
		    vma->vm_end >= vma->vm_mm->start_stack);

	अगर (is_stack && monitored_pid == pid) अणु
		mprotect_count++;
		ret = -EPERM;
	पूर्ण

	वापस ret;
पूर्ण

SEC("lsm.s/bprm_committed_creds")
पूर्णांक BPF_PROG(test_व्योम_hook, काष्ठा linux_binprm *bprm)
अणु
	__u32 pid = bpf_get_current_pid_tgid() >> 32;
	काष्ठा inner_map *inner_map;
	अक्षर args[64];
	__u32 key = 0;
	__u64 *value;

	अगर (monitored_pid == pid)
		bprm_count++;

	bpf_copy_from_user(args, माप(args), (व्योम *)bprm->vma->vm_mm->arg_start);
	bpf_copy_from_user(args, माप(args), (व्योम *)bprm->mm->arg_start);

	value = bpf_map_lookup_elem(&array, &key);
	अगर (value)
		*value = 0;
	value = bpf_map_lookup_elem(&hash, &key);
	अगर (value)
		*value = 0;
	value = bpf_map_lookup_elem(&lru_hash, &key);
	अगर (value)
		*value = 0;
	value = bpf_map_lookup_elem(&percpu_array, &key);
	अगर (value)
		*value = 0;
	value = bpf_map_lookup_elem(&percpu_hash, &key);
	अगर (value)
		*value = 0;
	value = bpf_map_lookup_elem(&lru_percpu_hash, &key);
	अगर (value)
		*value = 0;
	inner_map = bpf_map_lookup_elem(&outer_arr, &key);
	अगर (inner_map) अणु
		value = bpf_map_lookup_elem(inner_map, &key);
		अगर (value)
			*value = 0;
	पूर्ण
	inner_map = bpf_map_lookup_elem(&outer_hash, &key);
	अगर (inner_map) अणु
		value = bpf_map_lookup_elem(inner_map, &key);
		अगर (value)
			*value = 0;
	पूर्ण

	वापस 0;
पूर्ण
SEC("lsm/task_free") /* lsm/ is ok, lsm.s/ fails */
पूर्णांक BPF_PROG(test_task_मुक्त, काष्ठा task_काष्ठा *task)
अणु
	वापस 0;
पूर्ण

पूर्णांक copy_test = 0;

SEC("fentry.s/__x64_sys_setdomainname")
पूर्णांक BPF_PROG(test_sys_setकरोमुख्यname, काष्ठा pt_regs *regs)
अणु
	व्योम *ptr = (व्योम *)PT_REGS_PARM1(regs);
	पूर्णांक len = PT_REGS_PARM2(regs);
	पूर्णांक buf = 0;
	दीर्घ ret;

	ret = bpf_copy_from_user(&buf, माप(buf), ptr);
	अगर (len == -2 && ret == 0 && buf == 1234)
		copy_test++;
	अगर (len == -3 && ret == -EFAULT)
		copy_test++;
	अगर (len == -4 && ret == -EFAULT)
		copy_test++;
	वापस 0;
पूर्ण
