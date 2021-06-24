<शैली गुरु>
/* Copyright (c) 2016 Thomas Graf <tgraf@tgraf.ch>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License क्रम more details.
 */

#समावेश <uapi/linux/bpf.h>
#समावेश <uapi/linux/अगर_ether.h>
#समावेश <uapi/linux/ip.h>
#समावेश <uapi/linux/in.h>
#समावेश <bpf/bpf_helpers.h>

# define prपूर्णांकk(fmt, ...)						\
		(अणु							\
			अक्षर ____fmt[] = fmt;				\
			bpf_trace_prपूर्णांकk(____fmt, माप(____fmt),	\
				     ##__VA_ARGS__);			\
		पूर्ण)

काष्ठा bpf_elf_map अणु
	__u32 type;
	__u32 size_key;
	__u32 size_value;
	__u32 max_elem;
	__u32 flags;
	__u32 id;
	__u32 pinning;
पूर्ण;

काष्ठा bpf_elf_map SEC("maps") lwt_len_hist_map = अणु
	.type = BPF_MAP_TYPE_PERCPU_HASH,
	.size_key = माप(__u64),
	.size_value = माप(__u64),
	.pinning = 2,
	.max_elem = 1024,
पूर्ण;

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

SEC("len_hist")
पूर्णांक करो_len_hist(काष्ठा __sk_buff *skb)
अणु
	__u64 *value, key, init_val = 1;

	key = log2l(skb->len);

	value = bpf_map_lookup_elem(&lwt_len_hist_map, &key);
	अगर (value)
		__sync_fetch_and_add(value, 1);
	अन्यथा
		bpf_map_update_elem(&lwt_len_hist_map, &key, &init_val, BPF_ANY);

	वापस BPF_OK;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
