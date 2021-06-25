<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook */
#समावेश <linux/मानकघोष.स>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/bpf.h>
#समावेश <linux/tcp.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>
#समावेश <bpf/bpf_tracing.h>

काष्ठा sk_buff अणु
	अचिन्हित पूर्णांक len;
पूर्ण;

__u64 test_result = 0;
SEC("fexit/test_pkt_access")
पूर्णांक BPF_PROG(test_मुख्य, काष्ठा sk_buff *skb, पूर्णांक ret)
अणु
	पूर्णांक len;

	__builtin_preserve_access_index((अणु
		len = skb->len;
	पूर्ण));
	अगर (len != 74 || ret != 0)
		वापस 0;
	test_result = 1;
	वापस 0;
पूर्ण

__u64 test_result_subprog1 = 0;
SEC("fexit/test_pkt_access_subprog1")
पूर्णांक BPF_PROG(test_subprog1, काष्ठा sk_buff *skb, पूर्णांक ret)
अणु
	पूर्णांक len;

	__builtin_preserve_access_index((अणु
		len = skb->len;
	पूर्ण));
	अगर (len != 74 || ret != 148)
		वापस 0;
	test_result_subprog1 = 1;
	वापस 0;
पूर्ण

/* Though test_pkt_access_subprog2() is defined in C as:
 * अटल __attribute__ ((noअंतरभूत))
 * पूर्णांक test_pkt_access_subprog2(पूर्णांक val, अस्थिर काष्ठा __sk_buff *skb)
 * अणु
 *     वापस skb->len * val;
 * पूर्ण
 * llvm optimizations हटाओ 'int val' argument and generate BPF assembly:
 *   r0 = *(u32 *)(r1 + 0)
 *   w0 <<= 1
 *   निकास
 * In such हाल the verअगरier falls back to conservative and
 * tracing program can access arguments and वापस value as u64
 * instead of accurate types.
 */
काष्ठा args_subprog2 अणु
	__u64 args[5];
	__u64 ret;
पूर्ण;
__u64 test_result_subprog2 = 0;
SEC("fexit/test_pkt_access_subprog2")
पूर्णांक test_subprog2(काष्ठा args_subprog2 *ctx)
अणु
	काष्ठा sk_buff *skb = (व्योम *)ctx->args[0];
	__u64 ret;
	पूर्णांक len;

	bpf_probe_पढ़ो_kernel(&len, माप(len),
			      __builtin_preserve_access_index(&skb->len));

	ret = ctx->ret;
	/* bpf_prog_load() loads "test_pkt_access.o" with BPF_F_TEST_RND_HI32
	 * which अक्रमomizes upper 32 bits after BPF_ALU32 insns.
	 * Hence after 'w0 <<= 1' upper bits of $rax are अक्रमom.
	 * That is expected and correct. Trim them.
	 */
	ret = (__u32) ret;
	अगर (len != 74 || ret != 148)
		वापस 0;
	test_result_subprog2 = 1;
	वापस 0;
पूर्ण

__u64 test_result_subprog3 = 0;
SEC("fexit/test_pkt_access_subprog3")
पूर्णांक BPF_PROG(test_subprog3, पूर्णांक val, काष्ठा sk_buff *skb, पूर्णांक ret)
अणु
	पूर्णांक len;

	__builtin_preserve_access_index((अणु
		len = skb->len;
	पूर्ण));
	अगर (len != 74 || ret != 74 * val || val != 3)
		वापस 0;
	test_result_subprog3 = 1;
	वापस 0;
पूर्ण

__u64 test_get_skb_len = 0;
SEC("freplace/get_skb_len")
पूर्णांक new_get_skb_len(काष्ठा __sk_buff *skb)
अणु
	पूर्णांक len = skb->len;

	अगर (len != 74)
		वापस 0;
	test_get_skb_len = 1;
	वापस 74; /* original get_skb_len() वापसs skb->len */
पूर्ण

__u64 test_get_skb_अगरindex = 0;
SEC("freplace/get_skb_ifindex")
पूर्णांक new_get_skb_अगरindex(पूर्णांक val, काष्ठा __sk_buff *skb, पूर्णांक var)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;
	व्योम *data = (व्योम *)(दीर्घ)skb->data;
	काष्ठा ipv6hdr ip6, *ip6p;
	पूर्णांक अगरindex = skb->अगरindex;
	__u32 eth_proto;
	__u32 nh_off;

	/* check that BPF extension can पढ़ो packet via direct packet access */
	अगर (data + 14 + माप(ip6) > data_end)
		वापस 0;
	ip6p = data + 14;

	अगर (ip6p->nexthdr != 6 || ip6p->payload_len != __bpf_स्थिरant_htons(123))
		वापस 0;

	/* check that legacy packet access helper works too */
	अगर (bpf_skb_load_bytes(skb, 14, &ip6, माप(ip6)) < 0)
		वापस 0;
	ip6p = &ip6;
	अगर (ip6p->nexthdr != 6 || ip6p->payload_len != __bpf_स्थिरant_htons(123))
		वापस 0;

	अगर (अगरindex != 1 || val != 3 || var != 1)
		वापस 0;
	test_get_skb_अगरindex = 1;
	वापस 3; /* original get_skb_अगरindex() वापसs val * अगरindex * var */
पूर्ण

अस्थिर __u64 test_get_स्थिरant = 0;
SEC("freplace/get_constant")
पूर्णांक new_get_स्थिरant(दीर्घ val)
अणु
	अगर (val != 123)
		वापस 0;
	test_get_स्थिरant = 1;
	वापस test_get_स्थिरant; /* original get_स्थिरant() वापसs val - 122 */
पूर्ण

__u64 test_pkt_ग_लिखो_access_subprog = 0;
SEC("freplace/test_pkt_write_access_subprog")
पूर्णांक new_test_pkt_ग_लिखो_access_subprog(काष्ठा __sk_buff *skb, __u32 off)
अणु

	व्योम *data = (व्योम *)(दीर्घ)skb->data;
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;
	काष्ठा tcphdr *tcp;

	अगर (off > माप(काष्ठा ethhdr) + माप(काष्ठा ipv6hdr))
		वापस -1;

	tcp = data + off;
	अगर (tcp + 1 > data_end)
		वापस -1;

	/* make modअगरications to the packet data */
	tcp->check++;
	tcp->syn = 0;

	test_pkt_ग_लिखो_access_subprog = 1;
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
