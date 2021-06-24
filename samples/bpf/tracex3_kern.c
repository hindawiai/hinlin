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

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, दीर्घ);
	__type(value, u64);
	__uपूर्णांक(max_entries, 4096);
पूर्ण my_map SEC(".maps");

/* kprobe is NOT a stable ABI. If kernel पूर्णांकernals change this bpf+kprobe
 * example will no दीर्घer be meaningful
 */
SEC("kprobe/blk_mq_start_request")
पूर्णांक bpf_prog1(काष्ठा pt_regs *ctx)
अणु
	दीर्घ rq = PT_REGS_PARM1(ctx);
	u64 val = bpf_kसमय_get_ns();

	bpf_map_update_elem(&my_map, &rq, &val, BPF_ANY);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक log2l(अचिन्हित दीर्घ दीर्घ n)
अणु
#घोषणा S(k) अगर (n >= (1ull << k)) अणु i += k; n >>= k; पूर्ण
	पूर्णांक i = -(n == 0);
	S(32); S(16); S(8); S(4); S(2); S(1);
	वापस i;
#अघोषित S
पूर्ण

#घोषणा SLOTS 100

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(key_size, माप(u32));
	__uपूर्णांक(value_size, माप(u64));
	__uपूर्णांक(max_entries, SLOTS);
पूर्ण lat_map SEC(".maps");

SEC("kprobe/blk_account_io_done")
पूर्णांक bpf_prog2(काष्ठा pt_regs *ctx)
अणु
	दीर्घ rq = PT_REGS_PARM1(ctx);
	u64 *value, l, base;
	u32 index;

	value = bpf_map_lookup_elem(&my_map, &rq);
	अगर (!value)
		वापस 0;

	u64 cur_समय = bpf_kसमय_get_ns();
	u64 delta = cur_समय - *value;

	bpf_map_delete_elem(&my_map, &rq);

	/* the lines below are computing index = log10(delta)*10
	 * using पूर्णांकeger arithmetic
	 * index = 29 ~ 1 usec
	 * index = 59 ~ 1 msec
	 * index = 89 ~ 1 sec
	 * index = 99 ~ 10sec or more
	 * log10(x)*10 = log2(x)*10/log2(10) = log2(x)*3
	 */
	l = log2l(delta);
	base = 1ll << l;
	index = (l * 64 + (delta - base) * 64 / base) * 3 / 64;

	अगर (index >= SLOTS)
		index = SLOTS - 1;

	value = bpf_map_lookup_elem(&lat_map, &index);
	अगर (value)
		*value += 1;

	वापस 0;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
