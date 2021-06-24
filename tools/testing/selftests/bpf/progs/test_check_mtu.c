<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Jesper Dangaard Brouer */

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <linux/अगर_ether.h>

#समावेश <मानकघोष.स>
#समावेश <मानक_निवेशt.h>

अक्षर _license[] SEC("license") = "GPL";

/* Userspace will update with MTU it can see on device */
अटल अस्थिर स्थिर पूर्णांक GLOBAL_USER_MTU;
अटल अस्थिर स्थिर __u32 GLOBAL_USER_IFINDEX;

/* BPF-prog will update these with MTU values it can see */
__u32 global_bpf_mtu_xdp = 0;
__u32 global_bpf_mtu_tc  = 0;

SEC("xdp")
पूर्णांक xdp_use_helper_basic(काष्ठा xdp_md *ctx)
अणु
	__u32 mtu_len = 0;

	अगर (bpf_check_mtu(ctx, 0, &mtu_len, 0, 0))
		वापस XDP_ABORTED;

	वापस XDP_PASS;
पूर्ण

SEC("xdp")
पूर्णांक xdp_use_helper(काष्ठा xdp_md *ctx)
अणु
	पूर्णांक retval = XDP_PASS; /* Expected retval on successful test */
	__u32 mtu_len = 0;
	__u32 अगरindex = 0;
	पूर्णांक delta = 0;

	/* When अगरindex is zero, save net_device lookup and use ctx netdev */
	अगर (GLOBAL_USER_IFINDEX > 0)
		अगरindex = GLOBAL_USER_IFINDEX;

	अगर (bpf_check_mtu(ctx, अगरindex, &mtu_len, delta, 0)) अणु
		/* mtu_len is also valid when check fail */
		retval = XDP_ABORTED;
		जाओ out;
	पूर्ण

	अगर (mtu_len != GLOBAL_USER_MTU)
		retval = XDP_DROP;

out:
	global_bpf_mtu_xdp = mtu_len;
	वापस retval;
पूर्ण

SEC("xdp")
पूर्णांक xdp_exceed_mtu(काष्ठा xdp_md *ctx)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data = (व्योम *)(दीर्घ)ctx->data;
	__u32 अगरindex = GLOBAL_USER_IFINDEX;
	__u32 data_len = data_end - data;
	पूर्णांक retval = XDP_ABORTED; /* Fail */
	__u32 mtu_len = 0;
	पूर्णांक delta;
	पूर्णांक err;

	/* Exceed MTU with 1 via delta adjust */
	delta = GLOBAL_USER_MTU - (data_len - ETH_HLEN) + 1;

	err = bpf_check_mtu(ctx, अगरindex, &mtu_len, delta, 0);
	अगर (err) अणु
		retval = XDP_PASS; /* Success in exceeding MTU check */
		अगर (err != BPF_MTU_CHK_RET_FRAG_NEEDED)
			retval = XDP_DROP;
	पूर्ण

	global_bpf_mtu_xdp = mtu_len;
	वापस retval;
पूर्ण

SEC("xdp")
पूर्णांक xdp_minus_delta(काष्ठा xdp_md *ctx)
अणु
	पूर्णांक retval = XDP_PASS; /* Expected retval on successful test */
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data = (व्योम *)(दीर्घ)ctx->data;
	__u32 अगरindex = GLOBAL_USER_IFINDEX;
	__u32 data_len = data_end - data;
	__u32 mtu_len = 0;
	पूर्णांक delta;

	/* Borderline test हाल: Minus delta exceeding packet length allowed */
	delta = -((data_len - ETH_HLEN) + 1);

	/* Minus length (adjusted via delta) still pass MTU check, other helpers
	 * are responsible क्रम catching this, when करोing actual size adjust
	 */
	अगर (bpf_check_mtu(ctx, अगरindex, &mtu_len, delta, 0))
		retval = XDP_ABORTED;

	global_bpf_mtu_xdp = mtu_len;
	वापस retval;
पूर्ण

SEC("xdp")
पूर्णांक xdp_input_len(काष्ठा xdp_md *ctx)
अणु
	पूर्णांक retval = XDP_PASS; /* Expected retval on successful test */
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data = (व्योम *)(दीर्घ)ctx->data;
	__u32 अगरindex = GLOBAL_USER_IFINDEX;
	__u32 data_len = data_end - data;

	/* API allow user give length to check as input via mtu_len param,
	 * resulting MTU value is still output in mtu_len param after call.
	 *
	 * Input len is L3, like MTU and iph->tot_len.
	 * Remember XDP data_len is L2.
	 */
	__u32 mtu_len = data_len - ETH_HLEN;

	अगर (bpf_check_mtu(ctx, अगरindex, &mtu_len, 0, 0))
		retval = XDP_ABORTED;

	global_bpf_mtu_xdp = mtu_len;
	वापस retval;
पूर्ण

SEC("xdp")
पूर्णांक xdp_input_len_exceed(काष्ठा xdp_md *ctx)
अणु
	पूर्णांक retval = XDP_ABORTED; /* Fail */
	__u32 अगरindex = GLOBAL_USER_IFINDEX;
	पूर्णांक err;

	/* API allow user give length to check as input via mtu_len param,
	 * resulting MTU value is still output in mtu_len param after call.
	 *
	 * Input length value is L3 size like MTU.
	 */
	__u32 mtu_len = GLOBAL_USER_MTU;

	mtu_len += 1; /* Exceed with 1 */

	err = bpf_check_mtu(ctx, अगरindex, &mtu_len, 0, 0);
	अगर (err == BPF_MTU_CHK_RET_FRAG_NEEDED)
		retval = XDP_PASS ; /* Success in exceeding MTU check */

	global_bpf_mtu_xdp = mtu_len;
	वापस retval;
पूर्ण

SEC("classifier")
पूर्णांक tc_use_helper(काष्ठा __sk_buff *ctx)
अणु
	पूर्णांक retval = BPF_OK; /* Expected retval on successful test */
	__u32 mtu_len = 0;
	पूर्णांक delta = 0;

	अगर (bpf_check_mtu(ctx, 0, &mtu_len, delta, 0)) अणु
		retval = BPF_DROP;
		जाओ out;
	पूर्ण

	अगर (mtu_len != GLOBAL_USER_MTU)
		retval = BPF_REसूचीECT;
out:
	global_bpf_mtu_tc = mtu_len;
	वापस retval;
पूर्ण

SEC("classifier")
पूर्णांक tc_exceed_mtu(काष्ठा __sk_buff *ctx)
अणु
	__u32 अगरindex = GLOBAL_USER_IFINDEX;
	पूर्णांक retval = BPF_DROP; /* Fail */
	__u32 skb_len = ctx->len;
	__u32 mtu_len = 0;
	पूर्णांक delta;
	पूर्णांक err;

	/* Exceed MTU with 1 via delta adjust */
	delta = GLOBAL_USER_MTU - (skb_len - ETH_HLEN) + 1;

	err = bpf_check_mtu(ctx, अगरindex, &mtu_len, delta, 0);
	अगर (err) अणु
		retval = BPF_OK; /* Success in exceeding MTU check */
		अगर (err != BPF_MTU_CHK_RET_FRAG_NEEDED)
			retval = BPF_DROP;
	पूर्ण

	global_bpf_mtu_tc = mtu_len;
	वापस retval;
पूर्ण

SEC("classifier")
पूर्णांक tc_exceed_mtu_da(काष्ठा __sk_buff *ctx)
अणु
	/* SKB Direct-Access variant */
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data = (व्योम *)(दीर्घ)ctx->data;
	__u32 अगरindex = GLOBAL_USER_IFINDEX;
	__u32 data_len = data_end - data;
	पूर्णांक retval = BPF_DROP; /* Fail */
	__u32 mtu_len = 0;
	पूर्णांक delta;
	पूर्णांक err;

	/* Exceed MTU with 1 via delta adjust */
	delta = GLOBAL_USER_MTU - (data_len - ETH_HLEN) + 1;

	err = bpf_check_mtu(ctx, अगरindex, &mtu_len, delta, 0);
	अगर (err) अणु
		retval = BPF_OK; /* Success in exceeding MTU check */
		अगर (err != BPF_MTU_CHK_RET_FRAG_NEEDED)
			retval = BPF_DROP;
	पूर्ण

	global_bpf_mtu_tc = mtu_len;
	वापस retval;
पूर्ण

SEC("classifier")
पूर्णांक tc_minus_delta(काष्ठा __sk_buff *ctx)
अणु
	पूर्णांक retval = BPF_OK; /* Expected retval on successful test */
	__u32 अगरindex = GLOBAL_USER_IFINDEX;
	__u32 skb_len = ctx->len;
	__u32 mtu_len = 0;
	पूर्णांक delta;

	/* Borderline test हाल: Minus delta exceeding packet length allowed */
	delta = -((skb_len - ETH_HLEN) + 1);

	/* Minus length (adjusted via delta) still pass MTU check, other helpers
	 * are responsible क्रम catching this, when करोing actual size adjust
	 */
	अगर (bpf_check_mtu(ctx, अगरindex, &mtu_len, delta, 0))
		retval = BPF_DROP;

	global_bpf_mtu_xdp = mtu_len;
	वापस retval;
पूर्ण

SEC("classifier")
पूर्णांक tc_input_len(काष्ठा __sk_buff *ctx)
अणु
	पूर्णांक retval = BPF_OK; /* Expected retval on successful test */
	__u32 अगरindex = GLOBAL_USER_IFINDEX;

	/* API allow user give length to check as input via mtu_len param,
	 * resulting MTU value is still output in mtu_len param after call.
	 *
	 * Input length value is L3 size.
	 */
	__u32 mtu_len = GLOBAL_USER_MTU;

	अगर (bpf_check_mtu(ctx, अगरindex, &mtu_len, 0, 0))
		retval = BPF_DROP;

	global_bpf_mtu_xdp = mtu_len;
	वापस retval;
पूर्ण

SEC("classifier")
पूर्णांक tc_input_len_exceed(काष्ठा __sk_buff *ctx)
अणु
	पूर्णांक retval = BPF_DROP; /* Fail */
	__u32 अगरindex = GLOBAL_USER_IFINDEX;
	पूर्णांक err;

	/* API allow user give length to check as input via mtu_len param,
	 * resulting MTU value is still output in mtu_len param after call.
	 *
	 * Input length value is L3 size like MTU.
	 */
	__u32 mtu_len = GLOBAL_USER_MTU;

	mtu_len += 1; /* Exceed with 1 */

	err = bpf_check_mtu(ctx, अगरindex, &mtu_len, 0, 0);
	अगर (err == BPF_MTU_CHK_RET_FRAG_NEEDED)
		retval = BPF_OK; /* Success in exceeding MTU check */

	global_bpf_mtu_xdp = mtu_len;
	वापस retval;
पूर्ण
