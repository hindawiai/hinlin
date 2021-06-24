<शैली गुरु>
/* Copyright (c) 2015 PLUMgrid, http://plumgrid.com
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#समावेश <linux/ptrace.h>
#समावेश <linux/version.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

काष्ठा pair अणु
	u64 val;
	u64 ip;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, दीर्घ);
	__type(value, काष्ठा pair);
	__uपूर्णांक(max_entries, 1000000);
पूर्ण my_map SEC(".maps");

/* kprobe is NOT a stable ABI. If kernel पूर्णांकernals change this bpf+kprobe
 * example will no दीर्घer be meaningful
 */
SEC("kprobe/kmem_cache_free")
पूर्णांक bpf_prog1(काष्ठा pt_regs *ctx)
अणु
	दीर्घ ptr = PT_REGS_PARM2(ctx);

	bpf_map_delete_elem(&my_map, &ptr);
	वापस 0;
पूर्ण

SEC("kretprobe/kmem_cache_alloc_node")
पूर्णांक bpf_prog2(काष्ठा pt_regs *ctx)
अणु
	दीर्घ ptr = PT_REGS_RC(ctx);
	दीर्घ ip = 0;

	/* get ip address of kmem_cache_alloc_node() caller */
	BPF_KRETPROBE_READ_RET_IP(ip, ctx);

	काष्ठा pair v = अणु
		.val = bpf_kसमय_get_ns(),
		.ip = ip,
	पूर्ण;

	bpf_map_update_elem(&my_map, &ptr, &v, BPF_ANY);
	वापस 0;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
