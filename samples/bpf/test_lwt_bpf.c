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

#समावेश <मानक_निवेशt.h>
#समावेश <मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <linux/ip.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/अगर_ether.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <माला.स>

# define prपूर्णांकk(fmt, ...)						\
		(अणु							\
			अक्षर ____fmt[] = fmt;				\
			bpf_trace_prपूर्णांकk(____fmt, माप(____fmt),	\
				     ##__VA_ARGS__);			\
		पूर्ण)

#घोषणा CB_MAGIC 1234

/* Test: Pass all packets through */
SEC("nop")
पूर्णांक करो_nop(काष्ठा __sk_buff *skb)
अणु
	वापस BPF_OK;
पूर्ण

/* Test: Verअगरy context inक्रमmation can be accessed */
SEC("test_ctx")
पूर्णांक करो_test_ctx(काष्ठा __sk_buff *skb)
अणु
	skb->cb[0] = CB_MAGIC;
	prपूर्णांकk("len %d hash %d protocol %d\n", skb->len, skb->hash,
	       skb->protocol);
	prपूर्णांकk("cb %d ingress_ifindex %d ifindex %d\n", skb->cb[0],
	       skb->ingress_अगरindex, skb->अगरindex);

	वापस BPF_OK;
पूर्ण

/* Test: Ensure skb->cb[] buffer is cleared */
SEC("test_cb")
पूर्णांक करो_test_cb(काष्ठा __sk_buff *skb)
अणु
	prपूर्णांकk("cb0: %x cb1: %x cb2: %x\n", skb->cb[0], skb->cb[1],
	       skb->cb[2]);
	prपूर्णांकk("cb3: %x cb4: %x\n", skb->cb[3], skb->cb[4]);

	वापस BPF_OK;
पूर्ण

/* Test: Verअगरy skb data can be पढ़ो */
SEC("test_data")
पूर्णांक करो_test_data(काष्ठा __sk_buff *skb)
अणु
	व्योम *data = (व्योम *)(दीर्घ)skb->data;
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;
	काष्ठा iphdr *iph = data;

	अगर (data + माप(*iph) > data_end) अणु
		prपूर्णांकk("packet truncated\n");
		वापस BPF_DROP;
	पूर्ण

	prपूर्णांकk("src: %x dst: %x\n", iph->saddr, iph->daddr);

	वापस BPF_OK;
पूर्ण

#घोषणा IP_CSUM_OFF दुरत्व(काष्ठा iphdr, check)
#घोषणा IP_DST_OFF दुरत्व(काष्ठा iphdr, daddr)
#घोषणा IP_SRC_OFF दुरत्व(काष्ठा iphdr, saddr)
#घोषणा IP_PROTO_OFF दुरत्व(काष्ठा iphdr, protocol)
#घोषणा TCP_CSUM_OFF दुरत्व(काष्ठा tcphdr, check)
#घोषणा UDP_CSUM_OFF दुरत्व(काष्ठा udphdr, check)
#घोषणा IS_PSEUDO 0x10

अटल अंतरभूत पूर्णांक reग_लिखो(काष्ठा __sk_buff *skb, uपूर्णांक32_t old_ip,
			  uपूर्णांक32_t new_ip, पूर्णांक rw_daddr)
अणु
	पूर्णांक ret, off = 0, flags = IS_PSEUDO;
	uपूर्णांक8_t proto;

	ret = bpf_skb_load_bytes(skb, IP_PROTO_OFF, &proto, 1);
	अगर (ret < 0) अणु
		prपूर्णांकk("bpf_l4_csum_replace failed: %d\n", ret);
		वापस BPF_DROP;
	पूर्ण

	चयन (proto) अणु
	हाल IPPROTO_TCP:
		off = TCP_CSUM_OFF;
		अवरोध;

	हाल IPPROTO_UDP:
		off = UDP_CSUM_OFF;
		flags |= BPF_F_MARK_MANGLED_0;
		अवरोध;

	हाल IPPROTO_ICMPV6:
		off = दुरत्व(काष्ठा icmp6hdr, icmp6_cksum);
		अवरोध;
	पूर्ण

	अगर (off) अणु
		ret = bpf_l4_csum_replace(skb, off, old_ip, new_ip,
					  flags | माप(new_ip));
		अगर (ret < 0) अणु
			prपूर्णांकk("bpf_l4_csum_replace failed: %d\n");
			वापस BPF_DROP;
		पूर्ण
	पूर्ण

	ret = bpf_l3_csum_replace(skb, IP_CSUM_OFF, old_ip, new_ip, माप(new_ip));
	अगर (ret < 0) अणु
		prपूर्णांकk("bpf_l3_csum_replace failed: %d\n", ret);
		वापस BPF_DROP;
	पूर्ण

	अगर (rw_daddr)
		ret = bpf_skb_store_bytes(skb, IP_DST_OFF, &new_ip, माप(new_ip), 0);
	अन्यथा
		ret = bpf_skb_store_bytes(skb, IP_SRC_OFF, &new_ip, माप(new_ip), 0);

	अगर (ret < 0) अणु
		prपूर्णांकk("bpf_skb_store_bytes() failed: %d\n", ret);
		वापस BPF_DROP;
	पूर्ण

	वापस BPF_OK;
पूर्ण

/* Test: Verअगरy skb data can be modअगरied */
SEC("test_rewrite")
पूर्णांक करो_test_reग_लिखो(काष्ठा __sk_buff *skb)
अणु
	uपूर्णांक32_t old_ip, new_ip = 0x3fea8c0;
	पूर्णांक ret;

	ret = bpf_skb_load_bytes(skb, IP_DST_OFF, &old_ip, 4);
	अगर (ret < 0) अणु
		prपूर्णांकk("bpf_skb_load_bytes failed: %d\n", ret);
		वापस BPF_DROP;
	पूर्ण

	अगर (old_ip == 0x2fea8c0) अणु
		prपूर्णांकk("out: rewriting from %x to %x\n", old_ip, new_ip);
		वापस reग_लिखो(skb, old_ip, new_ip, 1);
	पूर्ण

	वापस BPF_OK;
पूर्ण

अटल अंतरभूत पूर्णांक __करो_push_ll_and_redirect(काष्ठा __sk_buff *skb)
अणु
	uपूर्णांक64_t smac = SRC_MAC, dmac = DST_MAC;
	पूर्णांक ret, अगरindex = DST_IFINDEX;
	काष्ठा ethhdr ehdr;

	ret = bpf_skb_change_head(skb, 14, 0);
	अगर (ret < 0) अणु
		prपूर्णांकk("skb_change_head() failed: %d\n", ret);
	पूर्ण

	ehdr.h_proto = __स्थिरant_htons(ETH_P_IP);
	स_नकल(&ehdr.h_source, &smac, 6);
	स_नकल(&ehdr.h_dest, &dmac, 6);

	ret = bpf_skb_store_bytes(skb, 0, &ehdr, माप(ehdr), 0);
	अगर (ret < 0) अणु
		prपूर्णांकk("skb_store_bytes() failed: %d\n", ret);
		वापस BPF_DROP;
	पूर्ण

	वापस bpf_redirect(अगरindex, 0);
पूर्ण

SEC("push_ll_and_redirect_silent")
पूर्णांक करो_push_ll_and_redirect_silent(काष्ठा __sk_buff *skb)
अणु
	वापस __करो_push_ll_and_redirect(skb);
पूर्ण

SEC("push_ll_and_redirect")
पूर्णांक करो_push_ll_and_redirect(काष्ठा __sk_buff *skb)
अणु
	पूर्णांक ret, अगरindex = DST_IFINDEX;

	ret = __करो_push_ll_and_redirect(skb);
	अगर (ret >= 0)
		prपूर्णांकk("redirected to %d\n", अगरindex);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम __fill_garbage(काष्ठा __sk_buff *skb)
अणु
	uपूर्णांक64_t f = 0xFFFFFFFFFFFFFFFF;

	bpf_skb_store_bytes(skb, 0, &f, माप(f), 0);
	bpf_skb_store_bytes(skb, 8, &f, माप(f), 0);
	bpf_skb_store_bytes(skb, 16, &f, माप(f), 0);
	bpf_skb_store_bytes(skb, 24, &f, माप(f), 0);
	bpf_skb_store_bytes(skb, 32, &f, माप(f), 0);
	bpf_skb_store_bytes(skb, 40, &f, माप(f), 0);
	bpf_skb_store_bytes(skb, 48, &f, माप(f), 0);
	bpf_skb_store_bytes(skb, 56, &f, माप(f), 0);
	bpf_skb_store_bytes(skb, 64, &f, माप(f), 0);
	bpf_skb_store_bytes(skb, 72, &f, माप(f), 0);
	bpf_skb_store_bytes(skb, 80, &f, माप(f), 0);
	bpf_skb_store_bytes(skb, 88, &f, माप(f), 0);
पूर्ण

SEC("fill_garbage")
पूर्णांक करो_fill_garbage(काष्ठा __sk_buff *skb)
अणु
	__fill_garbage(skb);
	prपूर्णांकk("Set initial 96 bytes of header to FF\n");
	वापस BPF_OK;
पूर्ण

SEC("fill_garbage_and_redirect")
पूर्णांक करो_fill_garbage_and_redirect(काष्ठा __sk_buff *skb)
अणु
	पूर्णांक अगरindex = DST_IFINDEX;
	__fill_garbage(skb);
	prपूर्णांकk("redirected to %d\n", अगरindex);
	वापस bpf_redirect(अगरindex, 0);
पूर्ण

/* Drop all packets */
SEC("drop_all")
पूर्णांक करो_drop_all(काष्ठा __sk_buff *skb)
अणु
	prपूर्णांकk("dropping with: %d\n", BPF_DROP);
	वापस BPF_DROP;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
