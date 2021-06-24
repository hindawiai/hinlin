<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PROG_ARRAY);
	__uपूर्णांक(max_entries, 2);
	__uपूर्णांक(key_size, माप(__u32));
	__uपूर्णांक(value_size, माप(__u32));
पूर्ण jmp_table SEC(".maps");

#घोषणा TAIL_FUNC(x) 				\
	SEC("classifier/" #x)			\
	पूर्णांक bpf_func_##x(काष्ठा __sk_buff *skb)	\
	अणु					\
		वापस x;			\
	पूर्ण
TAIL_FUNC(0)
TAIL_FUNC(1)

अटल __noअंतरभूत
पूर्णांक subprog_tail(काष्ठा __sk_buff *skb)
अणु
	bpf_tail_call_अटल(skb, &jmp_table, 0);

	वापस skb->len * 2;
पूर्ण

SEC("classifier")
पूर्णांक entry(काष्ठा __sk_buff *skb)
अणु
	bpf_tail_call_अटल(skb, &jmp_table, 1);

	वापस subprog_tail(skb);
पूर्ण

अक्षर __license[] SEC("license") = "GPL";
पूर्णांक _version SEC("version") = 1;
