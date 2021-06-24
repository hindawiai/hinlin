<शैली गुरु>
/* Copyright (c) 2013-2015 PLUMgrid, http://plumgrid.com
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/version.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश "trace_common.h"

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, दीर्घ);
	__type(value, दीर्घ);
	__uपूर्णांक(max_entries, 1024);
पूर्ण my_map SEC(".maps");

/* kprobe is NOT a stable ABI. If kernel पूर्णांकernals change this bpf+kprobe
 * example will no दीर्घer be meaningful
 */
SEC("kprobe/kfree_skb")
पूर्णांक bpf_prog2(काष्ठा pt_regs *ctx)
अणु
	दीर्घ loc = 0;
	दीर्घ init_val = 1;
	दीर्घ *value;

	/* पढ़ो ip of kमुक्त_skb caller.
	 * non-portable version of __builtin_वापस_address(0)
	 */
	BPF_KPROBE_READ_RET_IP(loc, ctx);

	value = bpf_map_lookup_elem(&my_map, &loc);
	अगर (value)
		*value += 1;
	अन्यथा
		bpf_map_update_elem(&my_map, &loc, &init_val, BPF_ANY);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक log2(अचिन्हित पूर्णांक v)
अणु
	अचिन्हित पूर्णांक r;
	अचिन्हित पूर्णांक shअगरt;

	r = (v > 0xFFFF) << 4; v >>= r;
	shअगरt = (v > 0xFF) << 3; v >>= shअगरt; r |= shअगरt;
	shअगरt = (v > 0xF) << 2; v >>= shअगरt; r |= shअगरt;
	shअगरt = (v > 0x3) << 1; v >>= shअगरt; r |= shअगरt;
	r |= (v >> 1);
	वापस r;
पूर्ण

अटल अचिन्हित पूर्णांक log2l(अचिन्हित दीर्घ v)
अणु
	अचिन्हित पूर्णांक hi = v >> 32;
	अगर (hi)
		वापस log2(hi) + 32;
	अन्यथा
		वापस log2(v);
पूर्ण

काष्ठा hist_key अणु
	अक्षर comm[16];
	u64 pid_tgid;
	u64 uid_gid;
	u64 index;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_HASH);
	__uपूर्णांक(key_size, माप(काष्ठा hist_key));
	__uपूर्णांक(value_size, माप(दीर्घ));
	__uपूर्णांक(max_entries, 1024);
पूर्ण my_hist_map SEC(".maps");

SEC("kprobe/" SYSCALL(sys_ग_लिखो))
पूर्णांक bpf_prog3(काष्ठा pt_regs *ctx)
अणु
	दीर्घ ग_लिखो_size = PT_REGS_PARM3(ctx);
	दीर्घ init_val = 1;
	दीर्घ *value;
	काष्ठा hist_key key;

	key.index = log2l(ग_लिखो_size);
	key.pid_tgid = bpf_get_current_pid_tgid();
	key.uid_gid = bpf_get_current_uid_gid();
	bpf_get_current_comm(&key.comm, माप(key.comm));

	value = bpf_map_lookup_elem(&my_hist_map, &key);
	अगर (value)
		__sync_fetch_and_add(value, 1);
	अन्यथा
		bpf_map_update_elem(&my_hist_map, &key, &init_val, BPF_ANY);
	वापस 0;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
