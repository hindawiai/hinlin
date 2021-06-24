<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_IF_PACKET_H
#घोषणा __LINUX_IF_PACKET_H

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/types.h>

काष्ठा sockaddr_pkt अणु
	अचिन्हित लघु spkt_family;
	अचिन्हित अक्षर spkt_device[14];
	__be16 spkt_protocol;
पूर्ण;

काष्ठा sockaddr_ll अणु
	अचिन्हित लघु	sll_family;
	__be16		sll_protocol;
	पूर्णांक		sll_अगरindex;
	अचिन्हित लघु	sll_hatype;
	अचिन्हित अक्षर	sll_pkttype;
	अचिन्हित अक्षर	sll_halen;
	अचिन्हित अक्षर	sll_addr[8];
पूर्ण;

/* Packet types */

#घोषणा PACKET_HOST		0		/* To us		*/
#घोषणा PACKET_BROADCAST	1		/* To all		*/
#घोषणा PACKET_MULTICAST	2		/* To group		*/
#घोषणा PACKET_OTHERHOST	3		/* To someone अन्यथा 	*/
#घोषणा PACKET_OUTGOING		4		/* Outgoing of any type */
#घोषणा PACKET_LOOPBACK		5		/* MC/BRD frame looped back */
#घोषणा PACKET_USER		6		/* To user space	*/
#घोषणा PACKET_KERNEL		7		/* To kernel space	*/
/* Unused, PACKET_FASTROUTE and PACKET_LOOPBACK are invisible to user space */
#घोषणा PACKET_FASTROUTE	6		/* Fastrouted frame	*/

/* Packet socket options */

#घोषणा PACKET_ADD_MEMBERSHIP		1
#घोषणा PACKET_DROP_MEMBERSHIP		2
#घोषणा PACKET_RECV_OUTPUT		3
/* Value 4 is still used by obsolete turbo-packet. */
#घोषणा PACKET_RX_RING			5
#घोषणा PACKET_STATISTICS		6
#घोषणा PACKET_COPY_THRESH		7
#घोषणा PACKET_AUXDATA			8
#घोषणा PACKET_ORIGDEV			9
#घोषणा PACKET_VERSION			10
#घोषणा PACKET_HDRLEN			11
#घोषणा PACKET_RESERVE			12
#घोषणा PACKET_TX_RING			13
#घोषणा PACKET_LOSS			14
#घोषणा PACKET_VNET_HDR			15
#घोषणा PACKET_TX_TIMESTAMP		16
#घोषणा PACKET_TIMESTAMP		17
#घोषणा PACKET_FANOUT			18
#घोषणा PACKET_TX_HAS_OFF		19
#घोषणा PACKET_QDISC_BYPASS		20
#घोषणा PACKET_ROLLOVER_STATS		21
#घोषणा PACKET_FANOUT_DATA		22
#घोषणा PACKET_IGNORE_OUTGOING		23

#घोषणा PACKET_FANOUT_HASH		0
#घोषणा PACKET_FANOUT_LB		1
#घोषणा PACKET_FANOUT_CPU		2
#घोषणा PACKET_FANOUT_ROLLOVER		3
#घोषणा PACKET_FANOUT_RND		4
#घोषणा PACKET_FANOUT_QM		5
#घोषणा PACKET_FANOUT_CBPF		6
#घोषणा PACKET_FANOUT_EBPF		7
#घोषणा PACKET_FANOUT_FLAG_ROLLOVER	0x1000
#घोषणा PACKET_FANOUT_FLAG_UNIQUEID	0x2000
#घोषणा PACKET_FANOUT_FLAG_DEFRAG	0x8000

काष्ठा tpacket_stats अणु
	अचिन्हित पूर्णांक	tp_packets;
	अचिन्हित पूर्णांक	tp_drops;
पूर्ण;

काष्ठा tpacket_stats_v3 अणु
	अचिन्हित पूर्णांक	tp_packets;
	अचिन्हित पूर्णांक	tp_drops;
	अचिन्हित पूर्णांक	tp_मुक्तze_q_cnt;
पूर्ण;

काष्ठा tpacket_rollover_stats अणु
	__aligned_u64	tp_all;
	__aligned_u64	tp_huge;
	__aligned_u64	tp_failed;
पूर्ण;

जोड़ tpacket_stats_u अणु
	काष्ठा tpacket_stats stats1;
	काष्ठा tpacket_stats_v3 stats3;
पूर्ण;

काष्ठा tpacket_auxdata अणु
	__u32		tp_status;
	__u32		tp_len;
	__u32		tp_snaplen;
	__u16		tp_mac;
	__u16		tp_net;
	__u16		tp_vlan_tci;
	__u16		tp_vlan_tpid;
पूर्ण;

/* Rx ring - header status */
#घोषणा TP_STATUS_KERNEL		      0
#घोषणा TP_STATUS_USER			(1 << 0)
#घोषणा TP_STATUS_COPY			(1 << 1)
#घोषणा TP_STATUS_LOSING		(1 << 2)
#घोषणा TP_STATUS_CSUMNOTREADY		(1 << 3)
#घोषणा TP_STATUS_VLAN_VALID		(1 << 4) /* auxdata has valid tp_vlan_tci */
#घोषणा TP_STATUS_BLK_TMO		(1 << 5)
#घोषणा TP_STATUS_VLAN_TPID_VALID	(1 << 6) /* auxdata has valid tp_vlan_tpid */
#घोषणा TP_STATUS_CSUM_VALID		(1 << 7)

/* Tx ring - header status */
#घोषणा TP_STATUS_AVAILABLE	      0
#घोषणा TP_STATUS_SEND_REQUEST	(1 << 0)
#घोषणा TP_STATUS_SENDING	(1 << 1)
#घोषणा TP_STATUS_WRONG_FORMAT	(1 << 2)

/* Rx and Tx ring - header status */
#घोषणा TP_STATUS_TS_SOFTWARE		(1 << 29)
#घोषणा TP_STATUS_TS_SYS_HARDWARE	(1 << 30) /* deprecated, never set */
#घोषणा TP_STATUS_TS_RAW_HARDWARE	(1U << 31)

/* Rx ring - feature request bits */
#घोषणा TP_FT_REQ_FILL_RXHASH	0x1

काष्ठा tpacket_hdr अणु
	अचिन्हित दीर्घ	tp_status;
	अचिन्हित पूर्णांक	tp_len;
	अचिन्हित पूर्णांक	tp_snaplen;
	अचिन्हित लघु	tp_mac;
	अचिन्हित लघु	tp_net;
	अचिन्हित पूर्णांक	tp_sec;
	अचिन्हित पूर्णांक	tp_usec;
पूर्ण;

#घोषणा TPACKET_ALIGNMENT	16
#घोषणा TPACKET_ALIGN(x)	(((x)+TPACKET_ALIGNMENT-1)&~(TPACKET_ALIGNMENT-1))
#घोषणा TPACKET_HDRLEN		(TPACKET_ALIGN(माप(काष्ठा tpacket_hdr)) + माप(काष्ठा sockaddr_ll))

काष्ठा tpacket2_hdr अणु
	__u32		tp_status;
	__u32		tp_len;
	__u32		tp_snaplen;
	__u16		tp_mac;
	__u16		tp_net;
	__u32		tp_sec;
	__u32		tp_nsec;
	__u16		tp_vlan_tci;
	__u16		tp_vlan_tpid;
	__u8		tp_padding[4];
पूर्ण;

काष्ठा tpacket_hdr_variant1 अणु
	__u32	tp_rxhash;
	__u32	tp_vlan_tci;
	__u16	tp_vlan_tpid;
	__u16	tp_padding;
पूर्ण;

काष्ठा tpacket3_hdr अणु
	__u32		tp_next_offset;
	__u32		tp_sec;
	__u32		tp_nsec;
	__u32		tp_snaplen;
	__u32		tp_len;
	__u32		tp_status;
	__u16		tp_mac;
	__u16		tp_net;
	/* pkt_hdr variants */
	जोड़ अणु
		काष्ठा tpacket_hdr_variant1 hv1;
	पूर्ण;
	__u8		tp_padding[8];
पूर्ण;

काष्ठा tpacket_bd_ts अणु
	अचिन्हित पूर्णांक ts_sec;
	जोड़ अणु
		अचिन्हित पूर्णांक ts_usec;
		अचिन्हित पूर्णांक ts_nsec;
	पूर्ण;
पूर्ण;

काष्ठा tpacket_hdr_v1 अणु
	__u32	block_status;
	__u32	num_pkts;
	__u32	offset_to_first_pkt;

	/* Number of valid bytes (including padding)
	 * blk_len <= tp_block_size
	 */
	__u32	blk_len;

	/*
	 * Quite a few uses of sequence number:
	 * 1. Make sure cache flush etc worked.
	 *    Well, one can argue - why not use the increasing ts below?
	 *    But look at 2. below first.
	 * 2. When you pass around blocks to other user space decoders,
	 *    you can see which blk[s] is[are] outstanding etc.
	 * 3. Validate kernel code.
	 */
	__aligned_u64	seq_num;

	/*
	 * ts_last_pkt:
	 *
	 * Case 1.	Block has 'N'(N >=1) packets and TMO'd(समयd out)
	 *		ts_last_pkt == 'time-stamp of last packet' and NOT the
	 *		समय when the समयr fired and the block was बंदd.
	 *		By providing the ts of the last packet we can असलolutely
	 *		guarantee that समय-stamp wise, the first packet in the
	 *		next block will never precede the last packet of the
	 *		previous block.
	 * Case 2.	Block has zero packets and TMO'd
	 *		ts_last_pkt = समय when the समयr fired and the block
	 *		was बंदd.
	 * Case 3.	Block has 'N' packets and NO TMO.
	 *		ts_last_pkt = समय-stamp of the last pkt in the block.
	 *
	 * ts_first_pkt:
	 *		Is always the समय-stamp when the block was खोलोed.
	 *		Case a)	ZERO packets
	 *			No packets to deal with but atleast you know the
	 *			समय-पूर्णांकerval of this block.
	 *		Case b) Non-zero packets
	 *			Use the ts of the first packet in the block.
	 *
	 */
	काष्ठा tpacket_bd_ts	ts_first_pkt, ts_last_pkt;
पूर्ण;

जोड़ tpacket_bd_header_u अणु
	काष्ठा tpacket_hdr_v1 bh1;
पूर्ण;

काष्ठा tpacket_block_desc अणु
	__u32 version;
	__u32 offset_to_priv;
	जोड़ tpacket_bd_header_u hdr;
पूर्ण;

#घोषणा TPACKET2_HDRLEN		(TPACKET_ALIGN(माप(काष्ठा tpacket2_hdr)) + माप(काष्ठा sockaddr_ll))
#घोषणा TPACKET3_HDRLEN		(TPACKET_ALIGN(माप(काष्ठा tpacket3_hdr)) + माप(काष्ठा sockaddr_ll))

क्रमागत tpacket_versions अणु
	TPACKET_V1,
	TPACKET_V2,
	TPACKET_V3
पूर्ण;

/*
   Frame काष्ठाure:

   - Start. Frame must be aligned to TPACKET_ALIGNMENT=16
   - काष्ठा tpacket_hdr
   - pad to TPACKET_ALIGNMENT=16
   - काष्ठा sockaddr_ll
   - Gap, chosen so that packet data (Start+tp_net) alignes to TPACKET_ALIGNMENT=16
   - Start+tp_mac: [ Optional MAC header ]
   - Start+tp_net: Packet data, aligned to TPACKET_ALIGNMENT=16.
   - Pad to align to TPACKET_ALIGNMENT=16
 */

काष्ठा tpacket_req अणु
	अचिन्हित पूर्णांक	tp_block_size;	/* Minimal size of contiguous block */
	अचिन्हित पूर्णांक	tp_block_nr;	/* Number of blocks */
	अचिन्हित पूर्णांक	tp_frame_size;	/* Size of frame */
	अचिन्हित पूर्णांक	tp_frame_nr;	/* Total number of frames */
पूर्ण;

काष्ठा tpacket_req3 अणु
	अचिन्हित पूर्णांक	tp_block_size;	/* Minimal size of contiguous block */
	अचिन्हित पूर्णांक	tp_block_nr;	/* Number of blocks */
	अचिन्हित पूर्णांक	tp_frame_size;	/* Size of frame */
	अचिन्हित पूर्णांक	tp_frame_nr;	/* Total number of frames */
	अचिन्हित पूर्णांक	tp_retire_blk_tov; /* समयout in msecs */
	अचिन्हित पूर्णांक	tp_माप_priv; /* offset to निजी data area */
	अचिन्हित पूर्णांक	tp_feature_req_word;
पूर्ण;

जोड़ tpacket_req_u अणु
	काष्ठा tpacket_req	req;
	काष्ठा tpacket_req3	req3;
पूर्ण;

काष्ठा packet_mreq अणु
	पूर्णांक		mr_अगरindex;
	अचिन्हित लघु	mr_type;
	अचिन्हित लघु	mr_alen;
	अचिन्हित अक्षर	mr_address[8];
पूर्ण;

काष्ठा fanout_args अणु
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u16		id;
	__u16		type_flags;
#अन्यथा
	__u16		type_flags;
	__u16		id;
#पूर्ण_अगर
	__u32		max_num_members;
पूर्ण;

#घोषणा PACKET_MR_MULTICAST	0
#घोषणा PACKET_MR_PROMISC	1
#घोषणा PACKET_MR_ALLMULTI	2
#घोषणा PACKET_MR_UNICAST	3

#पूर्ण_अगर
