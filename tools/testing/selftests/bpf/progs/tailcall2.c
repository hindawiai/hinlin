<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bpf.h>

#समावेश <bpf/bpf_helpers.h>

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PROG_ARRAY);
	__uपूर्णांक(max_entries, 5);
	__uपूर्णांक(key_size, माप(__u32));
	__uपूर्णांक(value_size, माप(__u32));
पूर्ण jmp_table SEC(".maps");

SEC("classifier/0")
पूर्णांक bpf_func_0(काष्ठा __sk_buff *skb)
अणु
	bpf_tail_call_अटल(skb, &jmp_table, 1);
	वापस 0;
पूर्ण

SEC("classifier/1")
पूर्णांक bpf_func_1(काष्ठा __sk_buff *skb)
अणु
	bpf_tail_call_अटल(skb, &jmp_table, 2);
	वापस 1;
पूर्ण

SEC("classifier/2")
पूर्णांक bpf_func_2(काष्ठा __sk_buff *skb)
अणु
	वापस 2;
पूर्ण

SEC("classifier/3")
पूर्णांक bpf_func_3(काष्ठा __sk_buff *skb)
अणु
	bpf_tail_call_अटल(skb, &jmp_table, 4);
	वापस 3;
पूर्ण

SEC("classifier/4")
पूर्णांक bpf_func_4(काष्ठा __sk_buff *skb)
अणु
	bpf_tail_call_अटल(skb, &jmp_table, 3);
	वापस 4;
पूर्ण

SEC("classifier")
पूर्णांक entry(काष्ठा __sk_buff *skb)
अणु
	bpf_tail_call_अटल(skb, &jmp_table, 0);
	/* Check multi-prog update. */
	bpf_tail_call_अटल(skb, &jmp_table, 2);
	/* Check tail call limit. */
	bpf_tail_call_अटल(skb, &jmp_table, 3);
	वापस 3;
पूर्ण

अक्षर __license[] SEC("license") = "GPL";
पूर्णांक _version SEC("version") = 1;
