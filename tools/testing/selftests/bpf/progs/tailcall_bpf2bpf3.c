<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश "bpf_legacy.h"

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PROG_ARRAY);
	__uपूर्णांक(max_entries, 2);
	__uपूर्णांक(key_size, माप(__u32));
	__uपूर्णांक(value_size, माप(__u32));
पूर्ण jmp_table SEC(".maps");

__noअंतरभूत
पूर्णांक subprog_tail2(काष्ठा __sk_buff *skb)
अणु
	अस्थिर अक्षर arr[64] = अणुपूर्ण;

	अगर (load_word(skb, 0) || load_half(skb, 0))
		bpf_tail_call_अटल(skb, &jmp_table, 10);
	अन्यथा
		bpf_tail_call_अटल(skb, &jmp_table, 1);

	वापस skb->len;
पूर्ण

अटल __noअंतरभूत
पूर्णांक subprog_tail(काष्ठा __sk_buff *skb)
अणु
	अस्थिर अक्षर arr[64] = अणुपूर्ण;

	bpf_tail_call_अटल(skb, &jmp_table, 0);

	वापस skb->len * 2;
पूर्ण

SEC("classifier/0")
पूर्णांक bpf_func_0(काष्ठा __sk_buff *skb)
अणु
	अस्थिर अक्षर arr[128] = अणुपूर्ण;

	वापस subprog_tail2(skb);
पूर्ण

SEC("classifier/1")
पूर्णांक bpf_func_1(काष्ठा __sk_buff *skb)
अणु
	अस्थिर अक्षर arr[128] = अणुपूर्ण;

	वापस skb->len * 3;
पूर्ण

SEC("classifier")
पूर्णांक entry(काष्ठा __sk_buff *skb)
अणु
	अस्थिर अक्षर arr[128] = अणुपूर्ण;

	वापस subprog_tail(skb);
पूर्ण

अक्षर __license[] SEC("license") = "GPL";
पूर्णांक _version SEC("version") = 1;
