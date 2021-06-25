<शैली गुरु>
/* Copyright (c) 2016, Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/version.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <uapi/linux/perf_event.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, दीर्घ);
	__type(value, दीर्घ);
	__uपूर्णांक(max_entries, 1024);
पूर्ण my_map SEC(".maps");
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_HASH);
	__uपूर्णांक(key_size, माप(दीर्घ));
	__uपूर्णांक(value_size, माप(दीर्घ));
	__uपूर्णांक(max_entries, 1024);
पूर्ण my_map2 SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_STACK_TRACE);
	__uपूर्णांक(key_size, माप(u32));
	__uपूर्णांक(value_size, PERF_MAX_STACK_DEPTH * माप(u64));
	__uपूर्णांक(max_entries, 10000);
पूर्ण stackmap SEC(".maps");

#घोषणा PROG(foo) \
पूर्णांक foo(काष्ठा pt_regs *ctx) \
अणु \
	दीर्घ v = PT_REGS_IP(ctx), *val; \
\
	val = bpf_map_lookup_elem(&my_map, &v); \
	bpf_map_update_elem(&my_map, &v, &v, BPF_ANY); \
	bpf_map_update_elem(&my_map2, &v, &v, BPF_ANY); \
	bpf_map_delete_elem(&my_map2, &v); \
	bpf_get_stackid(ctx, &stackmap, BPF_F_REUSE_STACKID); \
	वापस 0; \
पूर्ण

/* add kprobes to all possible *spin* functions */
SEC("kprobe/spin_unlock")PROG(p1)
SEC("kprobe/spin_lock")PROG(p2)
SEC("kprobe/mutex_spin_on_owner")PROG(p3)
SEC("kprobe/rwsem_spin_on_owner")PROG(p4)
SEC("kprobe/spin_unlock_irqrestore")PROG(p5)
SEC("kprobe/_raw_spin_unlock_irqrestore")PROG(p6)
SEC("kprobe/_raw_spin_unlock_bh")PROG(p7)
SEC("kprobe/_raw_spin_unlock")PROG(p8)
SEC("kprobe/_raw_spin_lock_irqsave")PROG(p9)
SEC("kprobe/_raw_spin_trylock_bh")PROG(p10)
SEC("kprobe/_raw_spin_lock_irq")PROG(p11)
SEC("kprobe/_raw_spin_trylock")PROG(p12)
SEC("kprobe/_raw_spin_lock")PROG(p13)
SEC("kprobe/_raw_spin_lock_bh")PROG(p14)
/* and to inner bpf helpers */
SEC("kprobe/htab_map_update_elem")PROG(p15)
SEC("kprobe/__htab_percpu_map_update_elem")PROG(p16)
SEC("kprobe/htab_map_alloc")PROG(p17)

अक्षर _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
