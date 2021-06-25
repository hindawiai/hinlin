<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bpf.h>

#समावेश <bpf/bpf_helpers.h>

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PROG_ARRAY);
	__uपूर्णांक(max_entries, 3);
	__uपूर्णांक(key_size, माप(__u32));
	__uपूर्णांक(value_size, माप(__u32));
पूर्ण jmp_table SEC(".maps");

अटल अस्थिर पूर्णांक selector;

#घोषणा TAIL_FUNC(x)				\
	SEC("classifier/" #x)			\
	पूर्णांक bpf_func_##x(काष्ठा __sk_buff *skb)	\
	अणु					\
		वापस x;			\
	पूर्ण
TAIL_FUNC(0)
TAIL_FUNC(1)
TAIL_FUNC(2)

SEC("classifier")
पूर्णांक entry(काष्ठा __sk_buff *skb)
अणु
	bpf_tail_call(skb, &jmp_table, selector);
	वापस 3;
पूर्ण

अक्षर __license[] SEC("license") = "GPL";
पूर्णांक _version SEC("version") = 1;
