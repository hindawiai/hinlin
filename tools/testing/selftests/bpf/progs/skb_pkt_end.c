<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा BPF_NO_PRESERVE_ACCESS_INDEX
#समावेश <vmlinux.h>
#समावेश <bpf/bpf_core_पढ़ो.h>
#समावेश <bpf/bpf_helpers.h>

#घोषणा INLINE __always_अंतरभूत

#घोषणा skb_लघुer(skb, len) ((व्योम *)(दीर्घ)(skb)->data + (len) > (व्योम *)(दीर्घ)skb->data_end)

#घोषणा ETH_IPV4_TCP_SIZE (14 + माप(काष्ठा iphdr) + माप(काष्ठा tcphdr))

अटल INLINE काष्ठा iphdr *get_iphdr(काष्ठा __sk_buff *skb)
अणु
	काष्ठा iphdr *ip = शून्य;
	काष्ठा ethhdr *eth;

	अगर (skb_लघुer(skb, ETH_IPV4_TCP_SIZE))
		जाओ out;

	eth = (व्योम *)(दीर्घ)skb->data;
	ip = (व्योम *)(eth + 1);

out:
	वापस ip;
पूर्ण

SEC("classifier/cls")
पूर्णांक मुख्य_prog(काष्ठा __sk_buff *skb)
अणु
	काष्ठा iphdr *ip = शून्य;
	काष्ठा tcphdr *tcp;
	__u8 proto = 0;

	अगर (!(ip = get_iphdr(skb)))
		जाओ out;

	proto = ip->protocol;

	अगर (proto != IPPROTO_TCP)
		जाओ out;

	tcp = (व्योम*)(ip + 1);
	अगर (tcp->dest != 0)
		जाओ out;
	अगर (!tcp)
		जाओ out;

	वापस tcp->urg_ptr;
out:
	वापस -1;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
