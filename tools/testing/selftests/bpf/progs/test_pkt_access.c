<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2017 Facebook
 */
#समावेश <मानकघोष.स>
#समावेश <माला.स>
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/in.h>
#समावेश <linux/tcp.h>
#समावेश <linux/pkt_cls.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

#घोषणा barrier() __यंत्र__ __अस्थिर__("": : :"memory")
पूर्णांक _version SEC("version") = 1;

/* llvm will optimize both subprograms पूर्णांकo exactly the same BPF assembly
 *
 * Disassembly of section .text:
 *
 * 0000000000000000 test_pkt_access_subprog1:
 * ; 	वापस skb->len * 2;
 *        0:	61 10 00 00 00 00 00 00	r0 = *(u32 *)(r1 + 0)
 *        1:	64 00 00 00 01 00 00 00	w0 <<= 1
 *        2:	95 00 00 00 00 00 00 00	निकास
 *
 * 0000000000000018 test_pkt_access_subprog2:
 * ; 	वापस skb->len * val;
 *        3:	61 10 00 00 00 00 00 00	r0 = *(u32 *)(r1 + 0)
 *        4:	64 00 00 00 01 00 00 00	w0 <<= 1
 *        5:	95 00 00 00 00 00 00 00	निकास
 *
 * Which makes it an पूर्णांकeresting test क्रम BTF-enabled verअगरier.
 */
अटल __attribute__ ((noअंतरभूत))
पूर्णांक test_pkt_access_subprog1(अस्थिर काष्ठा __sk_buff *skb)
अणु
	वापस skb->len * 2;
पूर्ण

अटल __attribute__ ((noअंतरभूत))
पूर्णांक test_pkt_access_subprog2(पूर्णांक val, अस्थिर काष्ठा __sk_buff *skb)
अणु
	वापस skb->len * val;
पूर्ण

#घोषणा MAX_STACK (512 - 2 * 32)

__attribute__ ((noअंतरभूत))
पूर्णांक get_skb_len(काष्ठा __sk_buff *skb)
अणु
	अस्थिर अक्षर buf[MAX_STACK] = अणुपूर्ण;

	वापस skb->len;
पूर्ण

__attribute__ ((noअंतरभूत))
पूर्णांक get_स्थिरant(दीर्घ val)
अणु
	वापस val - 122;
पूर्ण

पूर्णांक get_skb_अगरindex(पूर्णांक, काष्ठा __sk_buff *skb, पूर्णांक);

__attribute__ ((noअंतरभूत))
पूर्णांक test_pkt_access_subprog3(पूर्णांक val, काष्ठा __sk_buff *skb)
अणु
	वापस get_skb_len(skb) * get_skb_अगरindex(val, skb, get_स्थिरant(123));
पूर्ण

__attribute__ ((noअंतरभूत))
पूर्णांक get_skb_अगरindex(पूर्णांक val, काष्ठा __sk_buff *skb, पूर्णांक var)
अणु
	अस्थिर अक्षर buf[MAX_STACK] = अणुपूर्ण;

	वापस skb->अगरindex * val * var;
पूर्ण

__attribute__ ((noअंतरभूत))
पूर्णांक test_pkt_ग_लिखो_access_subprog(काष्ठा __sk_buff *skb, __u32 off)
अणु
	व्योम *data = (व्योम *)(दीर्घ)skb->data;
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;
	काष्ठा tcphdr *tcp = शून्य;

	अगर (off > माप(काष्ठा ethhdr) + माप(काष्ठा ipv6hdr))
		वापस -1;

	tcp = data + off;
	अगर (tcp + 1 > data_end)
		वापस -1;
	/* make modअगरication to the packet data */
	tcp->check++;
	वापस 0;
पूर्ण

SEC("classifier/test_pkt_access")
पूर्णांक test_pkt_access(काष्ठा __sk_buff *skb)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;
	व्योम *data = (व्योम *)(दीर्घ)skb->data;
	काष्ठा ethhdr *eth = (काष्ठा ethhdr *)(data);
	काष्ठा tcphdr *tcp = शून्य;
	__u8 proto = 255;
	__u64 ihl_len;

	अगर (eth + 1 > data_end)
		वापस TC_ACT_SHOT;

	अगर (eth->h_proto == bpf_htons(ETH_P_IP)) अणु
		काष्ठा iphdr *iph = (काष्ठा iphdr *)(eth + 1);

		अगर (iph + 1 > data_end)
			वापस TC_ACT_SHOT;
		ihl_len = iph->ihl * 4;
		proto = iph->protocol;
		tcp = (काष्ठा tcphdr *)((व्योम *)(iph) + ihl_len);
	पूर्ण अन्यथा अगर (eth->h_proto == bpf_htons(ETH_P_IPV6)) अणु
		काष्ठा ipv6hdr *ip6h = (काष्ठा ipv6hdr *)(eth + 1);

		अगर (ip6h + 1 > data_end)
			वापस TC_ACT_SHOT;
		ihl_len = माप(*ip6h);
		proto = ip6h->nexthdr;
		tcp = (काष्ठा tcphdr *)((व्योम *)(ip6h) + ihl_len);
	पूर्ण

	अगर (test_pkt_access_subprog1(skb) != skb->len * 2)
		वापस TC_ACT_SHOT;
	अगर (test_pkt_access_subprog2(2, skb) != skb->len * 2)
		वापस TC_ACT_SHOT;
	अगर (test_pkt_access_subprog3(3, skb) != skb->len * 3 * skb->अगरindex)
		वापस TC_ACT_SHOT;
	अगर (tcp) अणु
		अगर (test_pkt_ग_लिखो_access_subprog(skb, (व्योम *)tcp - data))
			वापस TC_ACT_SHOT;
		अगर (((व्योम *)(tcp) + 20) > data_end || proto != 6)
			वापस TC_ACT_SHOT;
		barrier(); /* to क्रमce ordering of checks */
		अगर (((व्योम *)(tcp) + 18) > data_end)
			वापस TC_ACT_SHOT;
		अगर (tcp->urg_ptr == 123)
			वापस TC_ACT_OK;
	पूर्ण

	वापस TC_ACT_UNSPEC;
पूर्ण
