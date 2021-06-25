<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 * Copyright (c) 2018 Jesper Dangaard Brouer, Red Hat Inc.
 *
 * Example howto transfer info from XDP to SKB, e.g. skb->mark
 * -----------------------------------------------------------
 * This uses the XDP data_meta infraकाष्ठाure, and is a cooperation
 * between two bpf-programs (1) XDP and (2) clsact at TC-ingress hook.
 *
 * Notice: This example करोes not use the BPF C-loader,
 * but instead rely on the iproute2 TC tool क्रम loading BPF-objects.
 */
#समावेश <uapi/linux/bpf.h>
#समावेश <uapi/linux/pkt_cls.h>

#समावेश <bpf/bpf_helpers.h>

/*
 * This काष्ठा is stored in the XDP 'data_meta' area, which is located
 * just in-front-of the raw packet payload data.  The meaning is
 * specअगरic to these two BPF programs that use it as a communication
 * channel.  XDP adjust/increase the area via a bpf-helper, and TC use
 * boundary checks to see अगर data have been provided.
 *
 * The काष्ठा must be 4 byte aligned, which here is enक्रमced by the
 * काष्ठा __attribute__((aligned(4))).
 */
काष्ठा meta_info अणु
	__u32 mark;
पूर्ण __attribute__((aligned(4)));

SEC("xdp_mark")
पूर्णांक _xdp_mark(काष्ठा xdp_md *ctx)
अणु
	काष्ठा meta_info *meta;
	व्योम *data, *data_end;
	पूर्णांक ret;

	/* Reserve space in-front of data poपूर्णांकer क्रम our meta info.
	 * (Notice drivers not supporting data_meta will fail here!)
	 */
	ret = bpf_xdp_adjust_meta(ctx, -(पूर्णांक)माप(*meta));
	अगर (ret < 0)
		वापस XDP_ABORTED;

	/* Notice: Kernel-side verअगरier requires that loading of
	 * ctx->data MUST happen _after_ helper bpf_xdp_adjust_meta(),
	 * as pkt-data poपूर्णांकers are invalidated.  Helpers that require
	 * this are determined/marked by bpf_helper_changes_pkt_data()
	 */
	data = (व्योम *)(अचिन्हित दीर्घ)ctx->data;

	/* Check data_meta have room क्रम meta_info काष्ठा */
	meta = (व्योम *)(अचिन्हित दीर्घ)ctx->data_meta;
	अगर (meta + 1 > data)
		वापस XDP_ABORTED;

	meta->mark = 42;

	वापस XDP_PASS;
पूर्ण

SEC("tc_mark")
पूर्णांक _tc_mark(काष्ठा __sk_buff *ctx)
अणु
	व्योम *data      = (व्योम *)(अचिन्हित दीर्घ)ctx->data;
	व्योम *data_end  = (व्योम *)(अचिन्हित दीर्घ)ctx->data_end;
	व्योम *data_meta = (व्योम *)(अचिन्हित दीर्घ)ctx->data_meta;
	काष्ठा meta_info *meta = data_meta;

	/* Check XDP gave us some data_meta */
	अगर (meta + 1 > data) अणु
		ctx->mark = 41;
		 /* Skip "accept" अगर no data_meta is avail */
		वापस TC_ACT_OK;
	पूर्ण

	/* Hपूर्णांक: See func tc_cls_act_is_valid_access() क्रम BPF_WRITE access */
	ctx->mark = meta->mark; /* Transfer XDP-mark to SKB-mark */

	वापस TC_ACT_OK;
पूर्ण

/* Manually attaching these programs:
export DEV=ixgbe2
export खाता=xdp2skb_meta_kern.o

# via TC command
tc qdisc del dev $DEV clsact 2> /dev/null
tc qdisc add dev $DEV clsact
tc filter  add dev $DEV ingress prio 1 handle 1 bpf da obj $खाता sec tc_mark
tc filter show dev $DEV ingress

# XDP via IP command:
ip link set dev $DEV xdp off
ip link set dev $DEV xdp obj $खाता sec xdp_mark

# Use iptable to "see" अगर SKBs are marked
iptables -I INPUT -p icmp -m mark --mark 41  # == 0x29
iptables -I INPUT -p icmp -m mark --mark 42  # == 0x2a

# Hपूर्णांक: catch XDP_ABORTED errors via
perf record -e xdp:*
perf script

*/
