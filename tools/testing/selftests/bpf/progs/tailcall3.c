<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bpf.h>

#समावेश <bpf/bpf_helpers.h>

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PROG_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__uपूर्णांक(key_size, माप(__u32));
	__uपूर्णांक(value_size, माप(__u32));
पूर्ण jmp_table SEC(".maps");

अटल अस्थिर पूर्णांक count;

SEC("classifier/0")
पूर्णांक bpf_func_0(काष्ठा __sk_buff *skb)
अणु
	count++;
	bpf_tail_call_अटल(skb, &jmp_table, 0);
	वापस 1;
पूर्ण

SEC("classifier")
पूर्णांक entry(काष्ठा __sk_buff *skb)
अणु
	bpf_tail_call_अटल(skb, &jmp_table, 0);
	वापस 0;
पूर्ण

अक्षर __license[] SEC("license") = "GPL";
पूर्णांक _version SEC("version") = 1;
