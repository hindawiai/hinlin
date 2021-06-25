<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *  Copyright(c) 2018 Jesper Dangaard Brouer.
 *
 * XDP/TC VLAN manipulation example
 *
 * GOTCHA: Remember to disable NIC hardware offloading of VLANs,
 * अन्यथा the VLAN tags are NOT अंतरभूतd in the packet payload:
 *
 *  # ethtool -K ixgbe2 rxvlan off
 *
 * Verअगरy setting:
 *  # ethtool -k ixgbe2 | grep rx-vlan-offload
 *  rx-vlan-offload: off
 *
 */
#समावेश <मानकघोष.स>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/in.h>
#समावेश <linux/pkt_cls.h>

#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

/* linux/अगर_vlan.h have not exposed this as UAPI, thus mirror some here
 *
 *	काष्ठा vlan_hdr - vlan header
 *	@h_vlan_TCI: priority and VLAN ID
 *	@h_vlan_encapsulated_proto: packet type ID or len
 */
काष्ठा _vlan_hdr अणु
	__be16 h_vlan_TCI;
	__be16 h_vlan_encapsulated_proto;
पूर्ण;
#घोषणा VLAN_PRIO_MASK		0xe000 /* Priority Code Poपूर्णांक */
#घोषणा VLAN_PRIO_SHIFT		13
#घोषणा VLAN_CFI_MASK		0x1000 /* Canonical Format Indicator */
#घोषणा VLAN_TAG_PRESENT	VLAN_CFI_MASK
#घोषणा VLAN_VID_MASK		0x0fff /* VLAN Identअगरier */
#घोषणा VLAN_N_VID		4096

काष्ठा parse_pkt अणु
	__u16 l3_proto;
	__u16 l3_offset;
	__u16 vlan_outer;
	__u16 vlan_inner;
	__u8  vlan_outer_offset;
	__u8  vlan_inner_offset;
पूर्ण;

अक्षर _license[] SEC("license") = "GPL";

अटल __always_अंतरभूत
bool parse_eth_frame(काष्ठा ethhdr *eth, व्योम *data_end, काष्ठा parse_pkt *pkt)
अणु
	__u16 eth_type;
	__u8 offset;

	offset = माप(*eth);
	/* Make sure packet is large enough क्रम parsing eth + 2 VLAN headers */
	अगर ((व्योम *)eth + offset + (2*माप(काष्ठा _vlan_hdr)) > data_end)
		वापस false;

	eth_type = eth->h_proto;

	/* Handle outer VLAN tag */
	अगर (eth_type == bpf_htons(ETH_P_8021Q)
	    || eth_type == bpf_htons(ETH_P_8021AD)) अणु
		काष्ठा _vlan_hdr *vlan_hdr;

		vlan_hdr = (व्योम *)eth + offset;
		pkt->vlan_outer_offset = offset;
		pkt->vlan_outer = bpf_ntohs(vlan_hdr->h_vlan_TCI)
				& VLAN_VID_MASK;
		eth_type        = vlan_hdr->h_vlan_encapsulated_proto;
		offset += माप(*vlan_hdr);
	पूर्ण

	/* Handle inner (द्विगुन) VLAN tag */
	अगर (eth_type == bpf_htons(ETH_P_8021Q)
	    || eth_type == bpf_htons(ETH_P_8021AD)) अणु
		काष्ठा _vlan_hdr *vlan_hdr;

		vlan_hdr = (व्योम *)eth + offset;
		pkt->vlan_inner_offset = offset;
		pkt->vlan_inner = bpf_ntohs(vlan_hdr->h_vlan_TCI)
				& VLAN_VID_MASK;
		eth_type        = vlan_hdr->h_vlan_encapsulated_proto;
		offset += माप(*vlan_hdr);
	पूर्ण

	pkt->l3_proto = bpf_ntohs(eth_type); /* Convert to host-byte-order */
	pkt->l3_offset = offset;

	वापस true;
पूर्ण

/* Hपूर्णांक, VLANs are choosen to hit network-byte-order issues */
#घोषणा TESTVLAN 4011 /* 0xFAB */
// #घोषणा TO_VLAN  4000 /* 0xFA0 (hपूर्णांक 0xOA0 = 160) */

SEC("xdp_drop_vlan_4011")
पूर्णांक  xdp_prognum0(काष्ठा xdp_md *ctx)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data     = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा parse_pkt pkt = अणु 0 पूर्ण;

	अगर (!parse_eth_frame(data, data_end, &pkt))
		वापस XDP_ABORTED;

	/* Drop specअगरic VLAN ID example */
	अगर (pkt.vlan_outer == TESTVLAN)
		वापस XDP_ABORTED;
	/*
	 * Using XDP_ABORTED makes it possible to record this event,
	 * via tracepoपूर्णांक xdp:xdp_exception like:
	 *  # perf record -a -e xdp:xdp_exception
	 *  # perf script
	 */
	वापस XDP_PASS;
पूर्ण
/*
Commands to setup VLAN on Linux to test packets माला_लो dropped:

 export ROOTDEV=ixgbe2
 export VLANID=4011
 ip link add link $ROOTDEV name $ROOTDEV.$VLANID type vlan id $VLANID
 ip link set dev  $ROOTDEV.$VLANID up

 ip link set dev $ROOTDEV mtu 1508
 ip addr add 100.64.40.11/24 dev $ROOTDEV.$VLANID

Load prog with ip tool:

 ip link set $ROOTDEV xdp off
 ip link set $ROOTDEV xdp object xdp_vlan01_kern.o section xdp_drop_vlan_4011

*/

/* Changing VLAN to zero, have same practical effect as removing the VLAN. */
#घोषणा TO_VLAN	0

SEC("xdp_vlan_change")
पूर्णांक  xdp_prognum1(काष्ठा xdp_md *ctx)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data     = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा parse_pkt pkt = अणु 0 पूर्ण;

	अगर (!parse_eth_frame(data, data_end, &pkt))
		वापस XDP_ABORTED;

	/* Change specअगरic VLAN ID */
	अगर (pkt.vlan_outer == TESTVLAN) अणु
		काष्ठा _vlan_hdr *vlan_hdr = data + pkt.vlan_outer_offset;

		/* Modअगरying VLAN, preserve top 4 bits */
		vlan_hdr->h_vlan_TCI =
			bpf_htons((bpf_ntohs(vlan_hdr->h_vlan_TCI) & 0xf000)
				  | TO_VLAN);
	पूर्ण

	वापस XDP_PASS;
पूर्ण

/*
 * Show XDP+TC can cooperate, on creating a VLAN reग_लिखोr.
 * 1. Create a XDP prog that can "pop"/हटाओ a VLAN header.
 * 2. Create a TC-bpf prog that egress can add a VLAN header.
 */

#अगर_अघोषित ETH_ALEN /* Ethernet MAC address length */
#घोषणा ETH_ALEN	6	/* bytes */
#पूर्ण_अगर
#घोषणा VLAN_HDR_SZ	4	/* bytes */

SEC("xdp_vlan_remove_outer")
पूर्णांक  xdp_prognum2(काष्ठा xdp_md *ctx)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data     = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा parse_pkt pkt = अणु 0 पूर्ण;
	अक्षर *dest;

	अगर (!parse_eth_frame(data, data_end, &pkt))
		वापस XDP_ABORTED;

	/* Skip packet अगर no outer VLAN was detected */
	अगर (pkt.vlan_outer_offset == 0)
		वापस XDP_PASS;

	/* Moving Ethernet header, dest overlap with src, स_हटाओ handle this */
	dest = data;
	dest+= VLAN_HDR_SZ;
	/*
	 * Notice: Taking over vlan_hdr->h_vlan_encapsulated_proto, by
	 * only moving two MAC addrs (12 bytes), not overwriting last 2 bytes
	 */
	__builtin_स_हटाओ(dest, data, ETH_ALEN * 2);
	/* Note: LLVM built-in स_हटाओ inlining require size to be स्थिरant */

	/* Move start of packet header seen by Linux kernel stack */
	bpf_xdp_adjust_head(ctx, VLAN_HDR_SZ);

	वापस XDP_PASS;
पूर्ण

अटल __always_अंतरभूत
व्योम shअगरt_mac_4bytes_16bit(व्योम *data)
अणु
	__u16 *p = data;

	p[7] = p[5]; /* delete p[7] was vlan_hdr->h_vlan_TCI */
	p[6] = p[4]; /* delete p[6] was ethhdr->h_proto */
	p[5] = p[3];
	p[4] = p[2];
	p[3] = p[1];
	p[2] = p[0];
पूर्ण

अटल __always_अंतरभूत
व्योम shअगरt_mac_4bytes_32bit(व्योम *data)
अणु
	__u32 *p = data;

	/* Assuming VLAN hdr present. The 4 bytes in p[3] that माला_लो
	 * overwritten, is ethhdr->h_proto and vlan_hdr->h_vlan_TCI.
	 * The vlan_hdr->h_vlan_encapsulated_proto take over role as
	 * ethhdr->h_proto.
	 */
	p[3] = p[2];
	p[2] = p[1];
	p[1] = p[0];
पूर्ण

SEC("xdp_vlan_remove_outer2")
पूर्णांक  xdp_prognum3(काष्ठा xdp_md *ctx)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data     = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा ethhdr *orig_eth = data;
	काष्ठा parse_pkt pkt = अणु 0 पूर्ण;

	अगर (!parse_eth_frame(orig_eth, data_end, &pkt))
		वापस XDP_ABORTED;

	/* Skip packet अगर no outer VLAN was detected */
	अगर (pkt.vlan_outer_offset == 0)
		वापस XDP_PASS;

	/* Simply shअगरt करोwn MAC addrs 4 bytes, overग_लिखो h_proto + TCI */
	shअगरt_mac_4bytes_32bit(data);

	/* Move start of packet header seen by Linux kernel stack */
	bpf_xdp_adjust_head(ctx, VLAN_HDR_SZ);

	वापस XDP_PASS;
पूर्ण

/*=====================================
 *  BELOW: TC-hook based ebpf programs
 * ====================================
 * The TC-clsact eBPF programs (currently) need to be attach via TC commands
 */

SEC("tc_vlan_push")
पूर्णांक _tc_progA(काष्ठा __sk_buff *ctx)
अणु
	bpf_skb_vlan_push(ctx, bpf_htons(ETH_P_8021Q), TESTVLAN);

	वापस TC_ACT_OK;
पूर्ण
/*
Commands to setup TC to use above bpf prog:

export ROOTDEV=ixgbe2
export खाता=xdp_vlan01_kern.o

# Re-attach clsact to clear/flush existing role
tc qdisc del dev $ROOTDEV clsact 2> /dev/null ;\
tc qdisc add dev $ROOTDEV clsact

# Attach BPF prog EGRESS
tc filter add dev $ROOTDEV egress \
  prio 1 handle 1 bpf da obj $खाता sec tc_vlan_push

tc filter show dev $ROOTDEV egress
*/
