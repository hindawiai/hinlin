<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2013-2016, The Linux Foundation. All rights reserved.
 */

/* EMAC DMA HW engine uses three rings:
 * Tx:
 *   TPD: Transmit Packet Descriptor ring.
 * Rx:
 *   RFD: Receive Free Descriptor ring.
 *     Ring of descriptors with empty buffers to be filled by Rx HW.
 *   RRD: Receive Return Descriptor ring.
 *     Ring of descriptors with buffers filled with received data.
 */

#अगर_अघोषित _EMAC_HW_H_
#घोषणा _EMAC_HW_H_

/* EMAC_CSR रेजिस्टर offsets */
#घोषणा EMAC_EMAC_WRAPPER_CSR1                                0x000000
#घोषणा EMAC_EMAC_WRAPPER_CSR2                                0x000004
#घोषणा EMAC_EMAC_WRAPPER_TX_TS_LO                            0x000104
#घोषणा EMAC_EMAC_WRAPPER_TX_TS_HI                            0x000108
#घोषणा EMAC_EMAC_WRAPPER_TX_TS_INX                           0x00010c

/* DMA Order Settings */
क्रमागत emac_dma_order अणु
	emac_dma_ord_in = 1,
	emac_dma_ord_enh = 2,
	emac_dma_ord_out = 4
पूर्ण;

क्रमागत emac_dma_req_block अणु
	emac_dma_req_128 = 0,
	emac_dma_req_256 = 1,
	emac_dma_req_512 = 2,
	emac_dma_req_1024 = 3,
	emac_dma_req_2048 = 4,
	emac_dma_req_4096 = 5
पूर्ण;

/* Returns the value of bits idx...idx+n_bits */
#घोषणा BITS_GET(val, lo, hi) ((le32_to_cpu(val) & GENMASK((hi), (lo))) >> lo)
#घोषणा BITS_SET(val, lo, hi, new_val) \
	val = cpu_to_le32((le32_to_cpu(val) & (~GENMASK((hi), (lo)))) |	\
		(((new_val) << (lo)) & GENMASK((hi), (lo))))

/* RRD (Receive Return Descriptor) */
काष्ठा emac_rrd अणु
	u32	word[6];

/* number of RFD */
#घोषणा RRD_NOR(rrd)			BITS_GET((rrd)->word[0], 16, 19)
/* start consumer index of rfd-ring */
#घोषणा RRD_SI(rrd)			BITS_GET((rrd)->word[0], 20, 31)
/* vlan-tag (CVID, CFI and PRI) */
#घोषणा RRD_CVALN_TAG(rrd)		BITS_GET((rrd)->word[2], 0, 15)
/* length of the packet */
#घोषणा RRD_PKT_SIZE(rrd)		BITS_GET((rrd)->word[3], 0, 13)
/* L4(TCP/UDP) checksum failed */
#घोषणा RRD_L4F(rrd)			BITS_GET((rrd)->word[3], 14, 14)
/* vlan tagged */
#घोषणा RRD_CVTAG(rrd)			BITS_GET((rrd)->word[3], 16, 16)
/* When set, indicates that the descriptor is updated by the IP core.
 * When cleared, indicates that the descriptor is invalid.
 */
#घोषणा RRD_UPDT(rrd)			BITS_GET((rrd)->word[3], 31, 31)
#घोषणा RRD_UPDT_SET(rrd, val)		BITS_SET((rrd)->word[3], 31, 31, val)
/* बारtamp low */
#घोषणा RRD_TS_LOW(rrd)			BITS_GET((rrd)->word[4], 0, 29)
/* बारtamp high */
#घोषणा RRD_TS_HI(rrd)			le32_to_cpu((rrd)->word[5])
पूर्ण;

/* TPD (Transmit Packet Descriptor) */
काष्ठा emac_tpd अणु
	u32				word[4];

/* Number of bytes of the transmit packet. (include 4-byte CRC) */
#घोषणा TPD_BUF_LEN_SET(tpd, val)	BITS_SET((tpd)->word[0], 0, 15, val)
/* Custom Checksum Offload: When set, ask IP core to offload custom checksum */
#घोषणा TPD_CSX_SET(tpd, val)		BITS_SET((tpd)->word[1], 8, 8, val)
/* TCP Large Send Offload: When set, ask IP core to करो offload TCP Large Send */
#घोषणा TPD_LSO(tpd)			BITS_GET((tpd)->word[1], 12, 12)
#घोषणा TPD_LSO_SET(tpd, val)		BITS_SET((tpd)->word[1], 12, 12, val)
/*  Large Send Offload Version: When set, indicates this is an LSOv2
 * (क्रम both IPv4 and IPv6). When cleared, indicates this is an LSOv1
 * (only क्रम IPv4).
 */
#घोषणा TPD_LSOV_SET(tpd, val)		BITS_SET((tpd)->word[1], 13, 13, val)
/* IPv4 packet: When set, indicates this is an  IPv4 packet, this bit is only
 * क्रम LSOV2 क्रमmat.
 */
#घोषणा TPD_IPV4_SET(tpd, val)		BITS_SET((tpd)->word[1], 16, 16, val)
/* 0: Ethernet   frame (DA+SA+TYPE+DATA+CRC)
 * 1: IEEE 802.3 frame (DA+SA+LEN+DSAP+SSAP+CTL+ORG+TYPE+DATA+CRC)
 */
#घोषणा TPD_TYP_SET(tpd, val)		BITS_SET((tpd)->word[1], 17, 17, val)
/* Low-32bit Buffer Address */
#घोषणा TPD_BUFFER_ADDR_L_SET(tpd, val)	((tpd)->word[2] = cpu_to_le32(val))
/* CVLAN Tag to be inserted अगर INS_VLAN_TAG is set, CVLAN TPID based on global
 * रेजिस्टर configuration.
 */
#घोषणा TPD_CVLAN_TAG_SET(tpd, val)	BITS_SET((tpd)->word[3], 0, 15, val)
/*  Insert CVlan Tag: When set, ask MAC to insert CVLAN TAG to outgoing packet
 */
#घोषणा TPD_INSTC_SET(tpd, val)		BITS_SET((tpd)->word[3], 17, 17, val)
/* High-14bit Buffer Address, So, the 64b-bit address is
 * अणुDESC_CTRL_11_TX_DATA_HIADDR[17:0],(रेजिस्टर) BUFFER_ADDR_H, BUFFER_ADDR_Lपूर्ण
 * Extend TPD_BUFFER_ADDR_H to [31, 18], because we never enable बारtamping.
 */
#घोषणा TPD_BUFFER_ADDR_H_SET(tpd, val)	BITS_SET((tpd)->word[3], 18, 31, val)
/* Format D. Word offset from the 1st byte of this packet to start to calculate
 * the custom checksum.
 */
#घोषणा TPD_PAYLOAD_OFFSET_SET(tpd, val) BITS_SET((tpd)->word[1], 0, 7, val)
/*  Format D. Word offset from the 1st byte of this packet to fill the custom
 * checksum to
 */
#घोषणा TPD_CXSUM_OFFSET_SET(tpd, val)	BITS_SET((tpd)->word[1], 18, 25, val)

/* Format C. TCP Header offset from the 1st byte of this packet. (byte unit) */
#घोषणा TPD_TCPHDR_OFFSET_SET(tpd, val)	BITS_SET((tpd)->word[1], 0, 7, val)
/* Format C. MSS (Maximum Segment Size) got from the protocol layer. (byte unit)
 */
#घोषणा TPD_MSS_SET(tpd, val)		BITS_SET((tpd)->word[1], 18, 30, val)
/* packet length in ext tpd */
#घोषणा TPD_PKT_LEN_SET(tpd, val)	((tpd)->word[2] = cpu_to_le32(val))
पूर्ण;

/* emac_ring_header represents a single, contiguous block of DMA space
 * mapped क्रम the three descriptor rings (tpd, rfd, rrd)
 */
काष्ठा emac_ring_header अणु
	व्योम			*v_addr;	/* भव address */
	dma_addr_t		dma_addr;	/* dma address */
	माप_प्रकार			size;		/* length in bytes */
	माप_प्रकार			used;
पूर्ण;

/* emac_buffer is wrapper around a poपूर्णांकer to a socket buffer
 * so a DMA handle can be stored aदीर्घ with the skb
 */
काष्ठा emac_buffer अणु
	काष्ठा sk_buff		*skb;		/* socket buffer */
	u16			length;		/* rx buffer length */
	dma_addr_t		dma_addr;	/* dma address */
पूर्ण;

/* receive मुक्त descriptor (rfd) ring */
काष्ठा emac_rfd_ring अणु
	काष्ठा emac_buffer	*rfbuff;
	u32			*v_addr;	/* भव address */
	dma_addr_t		dma_addr;	/* dma address */
	माप_प्रकार			size;		/* length in bytes */
	अचिन्हित पूर्णांक		count;		/* number of desc in the ring */
	अचिन्हित पूर्णांक		produce_idx;
	अचिन्हित पूर्णांक		process_idx;
	अचिन्हित पूर्णांक		consume_idx;	/* unused */
पूर्ण;

/* Receive Return Desciptor (RRD) ring */
काष्ठा emac_rrd_ring अणु
	u32			*v_addr;	/* भव address */
	dma_addr_t		dma_addr;	/* physical address */
	माप_प्रकार			size;		/* length in bytes */
	अचिन्हित पूर्णांक		count;		/* number of desc in the ring */
	अचिन्हित पूर्णांक		produce_idx;	/* unused */
	अचिन्हित पूर्णांक		consume_idx;
पूर्ण;

/* Rx queue */
काष्ठा emac_rx_queue अणु
	काष्ठा net_device	*netdev;	/* netdev ring beदीर्घs to */
	काष्ठा emac_rrd_ring	rrd;
	काष्ठा emac_rfd_ring	rfd;
	काष्ठा napi_काष्ठा	napi;
	काष्ठा emac_irq		*irq;

	u32			पूर्णांकr;
	u32			produce_mask;
	u32			process_mask;
	u32			consume_mask;

	u16			produce_reg;
	u16			process_reg;
	u16			consume_reg;

	u8			produce_shअगरt;
	u8			process_shft;
	u8			consume_shअगरt;
पूर्ण;

/* Transimit Packet Descriptor (tpd) ring */
काष्ठा emac_tpd_ring अणु
	काष्ठा emac_buffer	*tpbuff;
	u32			*v_addr;	/* भव address */
	dma_addr_t		dma_addr;	/* dma address */

	माप_प्रकार			size;		/* length in bytes */
	अचिन्हित पूर्णांक		count;		/* number of desc in the ring */
	अचिन्हित पूर्णांक		produce_idx;
	अचिन्हित पूर्णांक		consume_idx;
	अचिन्हित पूर्णांक		last_produce_idx;
पूर्ण;

/* Tx queue */
काष्ठा emac_tx_queue अणु
	काष्ठा emac_tpd_ring	tpd;

	u32			produce_mask;
	u32			consume_mask;

	u16			max_packets;	/* max packets per पूर्णांकerrupt */
	u16			produce_reg;
	u16			consume_reg;

	u8			produce_shअगरt;
	u8			consume_shअगरt;
पूर्ण;

काष्ठा emac_adapter;

पूर्णांक  emac_mac_up(काष्ठा emac_adapter *adpt);
व्योम emac_mac_करोwn(काष्ठा emac_adapter *adpt);
व्योम emac_mac_reset(काष्ठा emac_adapter *adpt);
व्योम emac_mac_stop(काष्ठा emac_adapter *adpt);
व्योम emac_mac_mode_config(काष्ठा emac_adapter *adpt);
व्योम emac_mac_rx_process(काष्ठा emac_adapter *adpt, काष्ठा emac_rx_queue *rx_q,
			 पूर्णांक *num_pkts, पूर्णांक max_pkts);
netdev_tx_t emac_mac_tx_buf_send(काष्ठा emac_adapter *adpt,
				 काष्ठा emac_tx_queue *tx_q,
				 काष्ठा sk_buff *skb);
व्योम emac_mac_tx_process(काष्ठा emac_adapter *adpt, काष्ठा emac_tx_queue *tx_q);
व्योम emac_mac_rx_tx_ring_init_all(काष्ठा platक्रमm_device *pdev,
				  काष्ठा emac_adapter *adpt);
पूर्णांक  emac_mac_rx_tx_rings_alloc_all(काष्ठा emac_adapter *adpt);
व्योम emac_mac_rx_tx_rings_मुक्त_all(काष्ठा emac_adapter *adpt);
व्योम emac_mac_multicast_addr_clear(काष्ठा emac_adapter *adpt);
व्योम emac_mac_multicast_addr_set(काष्ठा emac_adapter *adpt, u8 *addr);

#पूर्ण_अगर /*_EMAC_HW_H_*/
