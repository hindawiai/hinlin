<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
 * Google भव Ethernet (gve) driver
 *
 * Copyright (C) 2015-2019 Google, Inc.
 */

/* GVE Transmit Descriptor क्रमmats */

#अगर_अघोषित _GVE_DESC_H_
#घोषणा _GVE_DESC_H_

#समावेश <linux/build_bug.h>

/* A note on seg_addrs
 *
 * Base addresses encoded in seg_addr are not assumed to be physical
 * addresses. The ring क्रमmat assumes these come from some linear address
 * space. This could be physical memory, kernel भव memory, user भव
 * memory.
 * If raw dma addressing is not supported then gVNIC uses lists of रेजिस्टरed
 * pages. Each queue is assumed to be associated with a single such linear
 * address space to ensure a consistent meaning क्रम seg_addrs posted to its
 * rings.
 */

काष्ठा gve_tx_pkt_desc अणु
	u8	type_flags;  /* desc type is lower 4 bits, flags upper */
	u8	l4_csum_offset;  /* relative offset of L4 csum word */
	u8	l4_hdr_offset;  /* Offset of start of L4 headers in packet */
	u8	desc_cnt;  /* Total descriptors क्रम this packet */
	__be16	len;  /* Total length of this packet (in bytes) */
	__be16	seg_len;  /* Length of this descriptor's segment */
	__be64	seg_addr;  /* Base address (see note) of this segment */
पूर्ण __packed;

काष्ठा gve_tx_seg_desc अणु
	u8	type_flags;	/* type is lower 4 bits, flags upper	*/
	u8	l3_offset;	/* TSO: 2 byte units to start of IPH	*/
	__be16	reserved;
	__be16	mss;		/* TSO MSS				*/
	__be16	seg_len;
	__be64	seg_addr;
पूर्ण __packed;

/* GVE Transmit Descriptor Types */
#घोषणा	GVE_TXD_STD		(0x0 << 4) /* Std with Host Address	*/
#घोषणा	GVE_TXD_TSO		(0x1 << 4) /* TSO with Host Address	*/
#घोषणा	GVE_TXD_SEG		(0x2 << 4) /* Seg with Host Address	*/

/* GVE Transmit Descriptor Flags क्रम Std Pkts */
#घोषणा	GVE_TXF_L4CSUM	BIT(0)	/* Need csum offload */
#घोषणा	GVE_TXF_TSTAMP	BIT(2)	/* Timestamp required */

/* GVE Transmit Descriptor Flags क्रम TSO Segs */
#घोषणा	GVE_TXSF_IPV6	BIT(1)	/* IPv6 TSO */

/* GVE Receive Packet Descriptor */
/* The start of an ethernet packet comes 2 bytes पूर्णांकo the rx buffer.
 * gVNIC adds this padding so that both the DMA and the L3/4 protocol header
 * access is aligned.
 */
#घोषणा GVE_RX_PAD 2

काष्ठा gve_rx_desc अणु
	u8	padding[48];
	__be32	rss_hash;  /* Receive-side scaling hash (Toeplitz क्रम gVNIC) */
	__be16	mss;
	__be16	reserved;  /* Reserved to zero */
	u8	hdr_len;  /* Header length (L2-L4) including padding */
	u8	hdr_off;  /* 64-byte-scaled offset पूर्णांकo RX_DATA entry */
	__sum16	csum;  /* 1's-complement partial checksum of L3+ bytes */
	__be16	len;  /* Length of the received packet */
	__be16	flags_seq;  /* Flags [15:3] and sequence number [2:0] (1-7) */
पूर्ण __packed;
अटल_निश्चित(माप(काष्ठा gve_rx_desc) == 64);

/* If the device supports raw dma addressing then the addr in data slot is
 * the dma address of the buffer.
 * If the device only supports रेजिस्टरed segments then the addr is a byte
 * offset पूर्णांकo the रेजिस्टरed segment (an ordered list of pages) where the
 * buffer is.
 */
जोड़ gve_rx_data_slot अणु
	__be64 qpl_offset;
	__be64 addr;
पूर्ण;

/* GVE Recive Packet Descriptor Seq No */
#घोषणा GVE_SEQNO(x) (be16_to_cpu(x) & 0x7)

/* GVE Recive Packet Descriptor Flags */
#घोषणा GVE_RXFLG(x)	cpu_to_be16(1 << (3 + (x)))
#घोषणा	GVE_RXF_FRAG	GVE_RXFLG(3)	/* IP Fragment			*/
#घोषणा	GVE_RXF_IPV4	GVE_RXFLG(4)	/* IPv4				*/
#घोषणा	GVE_RXF_IPV6	GVE_RXFLG(5)	/* IPv6				*/
#घोषणा	GVE_RXF_TCP	GVE_RXFLG(6)	/* TCP Packet			*/
#घोषणा	GVE_RXF_UDP	GVE_RXFLG(7)	/* UDP Packet			*/
#घोषणा	GVE_RXF_ERR	GVE_RXFLG(8)	/* Packet Error Detected	*/

/* GVE IRQ */
#घोषणा GVE_IRQ_ACK	BIT(31)
#घोषणा GVE_IRQ_MASK	BIT(30)
#घोषणा GVE_IRQ_EVENT	BIT(29)

अटल अंतरभूत bool gve_needs_rss(__be16 flag)
अणु
	अगर (flag & GVE_RXF_FRAG)
		वापस false;
	अगर (flag & (GVE_RXF_IPV4 | GVE_RXF_IPV6))
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत u8 gve_next_seqno(u8 seq)
अणु
	वापस (seq + 1) == 8 ? 1 : seq + 1;
पूर्ण
#पूर्ण_अगर /* _GVE_DESC_H_ */
