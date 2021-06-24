<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

पूर्णांक _version SEC("version") = 1;
अक्षर _license[] SEC("license") = "GPL";

SEC("skb_ctx")
पूर्णांक process(काष्ठा __sk_buff *skb)
अणु
	#आशय clang loop unroll(full)
	क्रम (पूर्णांक i = 0; i < 5; i++) अणु
		अगर (skb->cb[i] != i + 1)
			वापस 1;
		skb->cb[i]++;
	पूर्ण
	skb->priority++;
	skb->tstamp++;
	skb->mark++;

	अगर (skb->wire_len != 100)
		वापस 1;
	अगर (skb->gso_segs != 8)
		वापस 1;
	अगर (skb->gso_size != 10)
		वापस 1;

	वापस 0;
पूर्ण
