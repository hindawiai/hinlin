<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2012-2016,2018-2019, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित WIL6210_TXRX_EDMA_H
#घोषणा WIL6210_TXRX_EDMA_H

#समावेश "wil6210.h"

/* limit status ring size in range [ring size..max ring size] */
#घोषणा WIL_SRING_SIZE_ORDER_MIN	(WIL_RING_SIZE_ORDER_MIN)
#घोषणा WIL_SRING_SIZE_ORDER_MAX	(WIL_RING_SIZE_ORDER_MAX)
/* RX sring order should be bigger than RX ring order */
#घोषणा WIL_RX_SRING_SIZE_ORDER_DEFAULT	(12)
#घोषणा WIL_TX_SRING_SIZE_ORDER_DEFAULT	(14)
#घोषणा WIL_RX_BUFF_ARR_SIZE_DEFAULT (2600)

#घोषणा WIL_DEFAULT_RX_STATUS_RING_ID 0
#घोषणा WIL_RX_DESC_RING_ID 0
#घोषणा WIL_RX_STATUS_IRQ_IDX 0
#घोषणा WIL_TX_STATUS_IRQ_IDX 1

#घोषणा WIL_EDMA_AGG_WATERMARK (0xffff)
#घोषणा WIL_EDMA_AGG_WATERMARK_POS (16)

#घोषणा WIL_EDMA_IDLE_TIME_LIMIT_USEC (50)
#घोषणा WIL_EDMA_TIME_UNIT_CLK_CYCLES (330) /* fits 1 usec */

/* Error field */
#घोषणा WIL_RX_EDMA_ERROR_MIC	(1)
#घोषणा WIL_RX_EDMA_ERROR_KEY	(2) /* Key missing */
#घोषणा WIL_RX_EDMA_ERROR_REPLAY	(3)
#घोषणा WIL_RX_EDMA_ERROR_AMSDU	(4)
#घोषणा WIL_RX_EDMA_ERROR_FCS	(7)

#घोषणा WIL_RX_EDMA_ERROR_L3_ERR	(BIT(0) | BIT(1))
#घोषणा WIL_RX_EDMA_ERROR_L4_ERR	(BIT(0) | BIT(1))

#घोषणा WIL_RX_EDMA_DLPF_LU_MISS_BIT		BIT(11)
#घोषणा WIL_RX_EDMA_DLPF_LU_MISS_CID_TID_MASK	0x7
#घोषणा WIL_RX_EDMA_DLPF_LU_HIT_CID_TID_MASK	0xf

#घोषणा WIL_RX_EDMA_DLPF_LU_MISS_CID_POS	2
#घोषणा WIL_RX_EDMA_DLPF_LU_HIT_CID_POS		4

#घोषणा WIL_RX_EDMA_DLPF_LU_MISS_TID_POS	5

#घोषणा WIL_RX_EDMA_MID_VALID_BIT		BIT(20)

#घोषणा WIL_EDMA_DESC_TX_MAC_CFG_0_QID_POS 16
#घोषणा WIL_EDMA_DESC_TX_MAC_CFG_0_QID_LEN 6

#घोषणा WIL_EDMA_DESC_TX_CFG_EOP_POS 0
#घोषणा WIL_EDMA_DESC_TX_CFG_EOP_LEN 1

#घोषणा WIL_EDMA_DESC_TX_CFG_TSO_DESC_TYPE_POS 3
#घोषणा WIL_EDMA_DESC_TX_CFG_TSO_DESC_TYPE_LEN 2

#घोषणा WIL_EDMA_DESC_TX_CFG_SEG_EN_POS 5
#घोषणा WIL_EDMA_DESC_TX_CFG_SEG_EN_LEN 1

#घोषणा WIL_EDMA_DESC_TX_CFG_INSERT_IP_CHKSUM_POS 6
#घोषणा WIL_EDMA_DESC_TX_CFG_INSERT_IP_CHKSUM_LEN 1

#घोषणा WIL_EDMA_DESC_TX_CFG_INSERT_TCP_CHKSUM_POS 7
#घोषणा WIL_EDMA_DESC_TX_CFG_INSERT_TCP_CHKSUM_LEN 1

#घोषणा WIL_EDMA_DESC_TX_CFG_L4_TYPE_POS 15
#घोषणा WIL_EDMA_DESC_TX_CFG_L4_TYPE_LEN 1

#घोषणा WIL_EDMA_DESC_TX_CFG_PSEUDO_HEADER_CALC_EN_POS 5
#घोषणा WIL_EDMA_DESC_TX_CFG_PSEUDO_HEADER_CALC_EN_LEN 1

/* Enhanced Rx descriptor - MAC part
 * [dword 0] : Reserved
 * [dword 1] : Reserved
 * [dword 2] : Reserved
 * [dword 3]
 *	bit  0..15 : Buffer ID
 *	bit 16..31 : Reserved
 */
काष्ठा wil_ring_rx_enhanced_mac अणु
	u32 d[3];
	__le16 buff_id;
	u16 reserved;
पूर्ण __packed;

/* Enhanced Rx descriptor - DMA part
 * [dword 0] - Reserved
 * [dword 1]
 *	bit  0..31 : addr_low:32 The payload buffer address, bits 0-31
 * [dword 2]
 *	bit  0..15 : addr_high_low:16 The payload buffer address, bits 32-47
 *	bit 16..31 : Reserved
 * [dword 3]
 *	bit  0..15 : addr_high_high:16 The payload buffer address, bits 48-63
 *	bit 16..31 : length
 */
काष्ठा wil_ring_rx_enhanced_dma अणु
	u32 d0;
	काष्ठा wil_ring_dma_addr addr;
	u16 w5;
	__le16 addr_high_high;
	__le16 length;
पूर्ण __packed;

काष्ठा wil_rx_enhanced_desc अणु
	काष्ठा wil_ring_rx_enhanced_mac mac;
	काष्ठा wil_ring_rx_enhanced_dma dma;
पूर्ण __packed;

/* Enhanced Tx descriptor - DMA part
 * [dword 0]
 *	Same as legacy
 * [dword 1]
 * bit  0..31 : addr_low:32 The payload buffer address, bits 0-31
 * [dword 2]
 * bit  0..15 : addr_high_low:16 The payload buffer address, bits 32-47
 * bit 16..23 : ip_length:8 The IP header length क्रम the TX IP checksum
 *		offload feature
 * bit 24..30 : mac_length:7
 * bit     31 : ip_version:1 1 - IPv4, 0 - IPv6
 * [dword 3]
 * bit  0..15 : addr_high_high:16 The payload buffer address, bits 48-63
 * bit 16..31 : length
 */
काष्ठा wil_ring_tx_enhanced_dma अणु
	u8 l4_hdr_len;
	u8 cmd;
	u16 w1;
	काष्ठा wil_ring_dma_addr addr;
	u8  ip_length;
	u8  b11;       /* 0..6: mac_length; 7:ip_version */
	__le16 addr_high_high;
	__le16 length;
पूर्ण __packed;

/* Enhanced Tx descriptor - MAC part
 * [dword 0]
 * bit  0.. 9 : lअगरeसमय_expiry_value:10
 * bit     10 : पूर्णांकerrupt_en:1
 * bit     11 : status_en:1
 * bit 12..13 : txss_override:2
 * bit     14 : बारtamp_insertion:1
 * bit     15 : duration_preserve:1
 * bit 16..21 : reserved0:6
 * bit 22..26 : mcs_index:5
 * bit     27 : mcs_en:1
 * bit 28..30 : reserved1:3
 * bit     31 : sn_preserved:1
 * [dword 1]
 * bit  0.. 3 : pkt_mode:4
 * bit      4 : pkt_mode_en:1
 * bit  5..14 : reserved0:10
 * bit     15 : ack_policy_en:1
 * bit 16..19 : dst_index:4
 * bit     20 : dst_index_en:1
 * bit 21..22 : ack_policy:2
 * bit     23 : lअगरeसमय_en:1
 * bit 24..30 : max_retry:7
 * bit     31 : max_retry_en:1
 * [dword 2]
 * bit  0.. 7 : num_of_descriptors:8
 * bit  8..17 : reserved:10
 * bit 18..19 : l2_translation_type:2 00 - bypass, 01 - 802.3, 10 - 802.11
 * bit     20 : snap_hdr_insertion_en:1
 * bit     21 : vlan_removal_en:1
 * bit 22..23 : reserved0:2
 * bit	   24 : Dest ID extension:1
 * bit 25..31 : reserved0:7
 * [dword 3]
 * bit  0..15 : tso_mss:16
 * bit 16..31 : descriptor_scratchpad:16 - mailbox between driver and ucode
 */
काष्ठा wil_ring_tx_enhanced_mac अणु
	u32 d[3];
	__le16 tso_mss;
	u16 scratchpad;
पूर्ण __packed;

काष्ठा wil_tx_enhanced_desc अणु
	काष्ठा wil_ring_tx_enhanced_mac mac;
	काष्ठा wil_ring_tx_enhanced_dma dma;
पूर्ण __packed;

#घोषणा TX_STATUS_DESC_READY_POS 7

/* Enhanced TX status message
 * [dword 0]
 *	bit  0.. 7 : Number of Descriptor:8 - The number of descriptors that
 *		     are used to क्रमm the packets. It  is needed क्रम WB when
 *		     releasing the packet
 *	bit  8..15 : tx_ring_id:8 The transmission ring ID that is related to
 *		     the message
 *	bit 16..23 : Status:8 - The TX status Code
 *		0x0 - A successful transmission
 *		0x1 - Retry expired
 *		0x2 - Lअगरeसमय Expired
 *		0x3 - Released
 *		0x4-0xFF - Reserved
 *	bit 24..30 : Reserved:7
 *	bit     31 : Descriptor Ready bit:1 - It is initiated to
 *		zero by the driver when the ring is created. It is set by the HW
 *		to one क्रम each completed status message. Each wrap around,
 *		the DR bit value is flipped.
 * [dword 1]
 *	bit 0..31  : बारtamp:32 - Set when MPDU is transmitted.
 * [dword 2]
 *	bit  0.. 4 : MCS:5 - The transmitted MCS value
 *	bit      5 : Reserved:1
 *	bit  6.. 7 : CB mode:2 - 0-DMG 1-EDMG 2-Wide
 *	bit  8..12 : QID:5 - The QID that was used क्रम the transmission
 *	bit 13..15 : Reserved:3
 *	bit 16..20 : Num of MSDUs:5 - Number of MSDUs in the aggregation
 *	bit 21..22 : Reserved:2
 *	bit     23 : Retry:1 - An indication that the transmission was retried
 *	bit 24..31 : TX-Sector:8 - the antenna sector that was used क्रम
 *		     transmission
 * [dword 3]
 *	bit  0..11 : Sequence number:12 - The Sequence Number that was used
 *		     क्रम the MPDU transmission
 *	bit 12..31 : Reserved:20
 */
काष्ठा wil_ring_tx_status अणु
	u8 num_descriptors;
	u8 ring_id;
	u8 status;
	u8 desc_पढ़ोy; /* Only the last bit should be set */
	u32 बारtamp;
	u32 d2;
	u16 seq_number; /* Only the first 12 bits */
	u16 w7;
पूर्ण __packed;

/* Enhanced Rx status message - compressed part
 * [dword 0]
 *	bit  0.. 2 : L2 Rx Status:3 - The L2 packet reception Status
 *		     0-Success, 1-MIC Error, 2-Key Error, 3-Replay Error,
 *		     4-A-MSDU Error, 5-Reserved, 6-Reserved, 7-FCS Error
 *	bit  3.. 4 : L3 Rx Status:2 - Bit0 - L3I - L3 identअगरied and checksum
 *		     calculated, Bit1- L3Err - IPv4 Checksum Error
 *	bit  5.. 6 : L4 Rx Status:2 - Bit0 - L4I - L4 identअगरied and checksum
 *		     calculated, Bit1- L4Err - TCP/UDP Checksum Error
 *	bit      7 : Reserved:1
 *	bit  8..19 : Flow ID:12 - MSDU flow ID
 *	bit     20 : MID_V:1 - The MAC ID field is valid
 *	bit 21..22 : MID:2 - The MAC ID
 *	bit     23 : L3T:1 - IP types: 0-IPv6, 1-IPv4
 *	bit     24 : L4T:1 - Layer 4 Type: 0-UDP, 1-TCP
 *	bit     25 : BC:1 - The received MPDU is broadcast
 *	bit     26 : MC:1 - The received MPDU is multicast
 *	bit     27 : Raw:1 - The MPDU received with no translation
 *	bit     28 : Sec:1 - The FC control (b14) - Frame Protected
 *	bit     29 : Error:1 - An error is set when (L2 status != 0) ||
 *		(L3 status == 3) || (L4 status == 3)
 *	bit     30 : EOP:1 - End of MSDU संकेतing. It is set to mark the end
 *		     of the transfer, otherwise the status indicates buffer
 *		     only completion.
 *	bit     31 : Descriptor Ready bit:1 - It is initiated to
 *		     zero by the driver when the ring is created. It is set
 *		     by the HW to one क्रम each completed status message.
 *		     Each wrap around, the DR bit value is flipped.
 * [dword 1]
 *	bit  0.. 5 : MAC Len:6 - The number of bytes that are used क्रम L2 header
 *	bit  6..11 : IPLEN:6 - The number of DW that are used क्रम L3 header
 *	bit 12..15 : I4Len:4 - The number of DW that are used क्रम L4 header
 *	bit 16..21 : MCS:6 - The received MCS field from the PLCP Header
 *	bit 22..23 : CB mode:2 - The CB Mode: 0-DMG, 1-EDMG, 2-Wide
 *	bit 24..27 : Data Offset:4 - The data offset, a code that describe the
 *		     payload shअगरt from the beginning of the buffer:
 *		     0 - 0 Bytes, 3 - 2 Bytes
 *	bit     28 : A-MSDU Present:1 - The QoS (b7) A-MSDU present field
 *	bit     29 : A-MSDU Type:1 The QoS (b8) A-MSDU Type field
 *	bit     30 : A-MPDU:1 - Packet is part of aggregated MPDU
 *	bit     31 : Key ID:1 - The extracted Key ID from the encryption header
 * [dword 2]
 *	bit  0..15 : Buffer ID:16 - The Buffer Identअगरier
 *	bit 16..31 : Length:16 - It indicates the valid bytes that are stored
 *		     in the current descriptor buffer. For multiple buffer
 *		     descriptor, SW need to sum the total descriptor length
 *		     in all buffers to produce the packet length
 * [dword 3]
 *	bit  0..31  : बारtamp:32 - The MPDU Timestamp.
 */
काष्ठा wil_rx_status_compressed अणु
	u32 d0;
	u32 d1;
	__le16 buff_id;
	__le16 length;
	u32 बारtamp;
पूर्ण __packed;

/* Enhanced Rx status message - extension part
 * [dword 0]
 *	bit  0.. 4 : QID:5 - The Queue Identअगरier that the packet is received
 *		     from
 *	bit  5.. 7 : Reserved:3
 *	bit  8..11 : TID:4 - The QoS (b3-0) TID Field
 *	bit 12..15   Source index:4 - The Source index that was found
		     during Parsing the TA. This field is used to define the
		     source of the packet
 *	bit 16..18 : Destination index:3 - The Destination index that
		     was found during Parsing the RA.
 *	bit 19..20 : DS Type:2 - The FC Control (b9-8) - From / To DS
 *	bit 21..22 : MIC ICR:2 - this संकेत tells the DMA to निश्चित an
		     पूर्णांकerrupt after it ग_लिखोs the packet
 *	bit     23 : ESOP:1 - The QoS (b4) ESOP field
 *	bit     24 : RDG:1
 *	bit 25..31 : Reserved:7
 * [dword 1]
 *	bit  0.. 1 : Frame Type:2 - The FC Control (b3-2) - MPDU Type
		     (management, data, control and extension)
 *	bit  2.. 5 : Syb type:4 - The FC Control (b7-4) - Frame Subtype
 *	bit  6..11 : Ext sub type:6 - The FC Control (b11-8) - Frame Extended
 *                   Subtype
 *	bit 12..13 : ACK Policy:2 - The QoS (b6-5) ACK Policy fields
 *	bit 14     : DECRYPT_BYP:1 - The MPDU is bypass by the decryption unit
 *	bit 15..23 : Reserved:9
 *	bit 24..31 : RSSI/SNR:8 - The RSSI / SNR measurement क्रम the received
 *                   MPDU
 * [dword 2]
 *	bit  0..11 : SN:12 - The received Sequence number field
 *	bit 12..15 : Reserved:4
 *	bit 16..31 : PN bits [15:0]:16
 * [dword 3]
 *	bit  0..31 : PN bits [47:16]:32
 */
काष्ठा wil_rx_status_extension अणु
	u32 d0;
	u32 d1;
	__le16 seq_num; /* only lower 12 bits */
	u16 pn_15_0;
	u32 pn_47_16;
पूर्ण __packed;

काष्ठा wil_rx_status_extended अणु
	काष्ठा wil_rx_status_compressed comp;
	काष्ठा wil_rx_status_extension ext;
पूर्ण __packed;

अटल अंतरभूत व्योम *wil_skb_rxstatus(काष्ठा sk_buff *skb)
अणु
	वापस (व्योम *)skb->cb;
पूर्ण

अटल अंतरभूत __le16 wil_rx_status_get_length(व्योम *msg)
अणु
	वापस ((काष्ठा wil_rx_status_compressed *)msg)->length;
पूर्ण

अटल अंतरभूत u8 wil_rx_status_get_mcs(व्योम *msg)
अणु
	वापस WIL_GET_BITS(((काष्ठा wil_rx_status_compressed *)msg)->d1,
			    16, 21);
पूर्ण

अटल अंतरभूत u8 wil_rx_status_get_cb_mode(व्योम *msg)
अणु
	वापस WIL_GET_BITS(((काष्ठा wil_rx_status_compressed *)msg)->d1,
			    22, 23);
पूर्ण

अटल अंतरभूत u16 wil_rx_status_get_flow_id(व्योम *msg)
अणु
	वापस WIL_GET_BITS(((काष्ठा wil_rx_status_compressed *)msg)->d0,
			    8, 19);
पूर्ण

अटल अंतरभूत u8 wil_rx_status_get_mcast(व्योम *msg)
अणु
	वापस WIL_GET_BITS(((काष्ठा wil_rx_status_compressed *)msg)->d0,
			    26, 26);
पूर्ण

/**
 * In हाल of DLPF miss the parsing of flow Id should be as follows:
 * dest_id:2
 * src_id :3 - cid
 * tid:3
 * Otherwise:
 * tid:4
 * cid:4
 */

अटल अंतरभूत u8 wil_rx_status_get_cid(व्योम *msg)
अणु
	u16 val = wil_rx_status_get_flow_id(msg);

	अगर (val & WIL_RX_EDMA_DLPF_LU_MISS_BIT)
		/* CID is in bits 2..4 */
		वापस (val >> WIL_RX_EDMA_DLPF_LU_MISS_CID_POS) &
			WIL_RX_EDMA_DLPF_LU_MISS_CID_TID_MASK;
	अन्यथा
		/* CID is in bits 4..7 */
		वापस (val >> WIL_RX_EDMA_DLPF_LU_HIT_CID_POS) &
			WIL_RX_EDMA_DLPF_LU_HIT_CID_TID_MASK;
पूर्ण

अटल अंतरभूत u8 wil_rx_status_get_tid(व्योम *msg)
अणु
	u16 val = wil_rx_status_get_flow_id(msg);

	अगर (val & WIL_RX_EDMA_DLPF_LU_MISS_BIT)
		/* TID is in bits 5..7 */
		वापस (val >> WIL_RX_EDMA_DLPF_LU_MISS_TID_POS) &
			WIL_RX_EDMA_DLPF_LU_MISS_CID_TID_MASK;
	अन्यथा
		/* TID is in bits 0..3 */
		वापस val & WIL_RX_EDMA_DLPF_LU_MISS_CID_TID_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक wil_rx_status_get_eop(व्योम *msg) /* EoP = End of Packet */
अणु
	वापस WIL_GET_BITS(((काष्ठा wil_rx_status_compressed *)msg)->d0,
			    30, 30);
पूर्ण

अटल अंतरभूत व्योम wil_rx_status_reset_buff_id(काष्ठा wil_status_ring *s)
अणु
	((काष्ठा wil_rx_status_compressed *)
		(s->va + (s->elem_size * s->swhead)))->buff_id = 0;
पूर्ण

अटल अंतरभूत __le16 wil_rx_status_get_buff_id(व्योम *msg)
अणु
	वापस ((काष्ठा wil_rx_status_compressed *)msg)->buff_id;
पूर्ण

अटल अंतरभूत u8 wil_rx_status_get_data_offset(व्योम *msg)
अणु
	u8 val = WIL_GET_BITS(((काष्ठा wil_rx_status_compressed *)msg)->d1,
			      24, 27);

	चयन (val) अणु
	हाल 0: वापस 0;
	हाल 3: वापस 2;
	शेष: वापस 0xFF;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक wil_rx_status_get_frame_type(काष्ठा wil6210_priv *wil,
					       व्योम *msg)
अणु
	अगर (wil->use_compressed_rx_status)
		वापस IEEE80211_FTYPE_DATA;

	वापस WIL_GET_BITS(((काष्ठा wil_rx_status_extended *)msg)->ext.d1,
			    0, 1) << 2;
पूर्ण

अटल अंतरभूत पूर्णांक wil_rx_status_get_fc1(काष्ठा wil6210_priv *wil, व्योम *msg)
अणु
	अगर (wil->use_compressed_rx_status)
		वापस 0;

	वापस WIL_GET_BITS(((काष्ठा wil_rx_status_extended *)msg)->ext.d1,
			    0, 5) << 2;
पूर्ण

अटल अंतरभूत __le16 wil_rx_status_get_seq(काष्ठा wil6210_priv *wil, व्योम *msg)
अणु
	अगर (wil->use_compressed_rx_status)
		वापस 0;

	वापस ((काष्ठा wil_rx_status_extended *)msg)->ext.seq_num;
पूर्ण

अटल अंतरभूत u8 wil_rx_status_get_retry(व्योम *msg)
अणु
	/* retry bit is missing in EDMA HW. वापस 1 to be on the safe side */
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक wil_rx_status_get_mid(व्योम *msg)
अणु
	अगर (!(((काष्ठा wil_rx_status_compressed *)msg)->d0 &
	    WIL_RX_EDMA_MID_VALID_BIT))
		वापस 0; /* use the शेष MID */

	वापस WIL_GET_BITS(((काष्ठा wil_rx_status_compressed *)msg)->d0,
			    21, 22);
पूर्ण

अटल अंतरभूत पूर्णांक wil_rx_status_get_error(व्योम *msg)
अणु
	वापस WIL_GET_BITS(((काष्ठा wil_rx_status_compressed *)msg)->d0,
			    29, 29);
पूर्ण

अटल अंतरभूत पूर्णांक wil_rx_status_get_l2_rx_status(व्योम *msg)
अणु
	वापस WIL_GET_BITS(((काष्ठा wil_rx_status_compressed *)msg)->d0,
			    0, 2);
पूर्ण

अटल अंतरभूत पूर्णांक wil_rx_status_get_l3_rx_status(व्योम *msg)
अणु
	वापस WIL_GET_BITS(((काष्ठा wil_rx_status_compressed *)msg)->d0,
			    3, 4);
पूर्ण

अटल अंतरभूत पूर्णांक wil_rx_status_get_l4_rx_status(व्योम *msg)
अणु
	वापस WIL_GET_BITS(((काष्ठा wil_rx_status_compressed *)msg)->d0,
			    5, 6);
पूर्ण

/* L4	L3	Expected result
 * 0	0	Ok. No L3 and no L4 known protocols found.
 *		Treated as L2 packet. (no offloads on this packet)
 * 0	1	Ok. It means that L3 was found, and checksum check passed.
 *		No known L4 protocol was found.
 * 0	2	It means that L3 protocol was found, and checksum check failed.
 *		No L4 known protocol was found.
 * 1	any	Ok. It means that L4 was found, and checksum check passed.
 * 3	0	Not a possible scenario.
 * 3	1	Recalculate. It means that L3 protocol was found, and checksum
 *		passed. But L4 checksum failed. Need to see अगर really failed,
 *		or due to fragmentation.
 * 3	2	Both L3 and L4 checksum check failed.
 */
अटल अंतरभूत पूर्णांक wil_rx_status_get_checksum(व्योम *msg,
					     काष्ठा wil_net_stats *stats)
अणु
	पूर्णांक l3_rx_status = wil_rx_status_get_l3_rx_status(msg);
	पूर्णांक l4_rx_status = wil_rx_status_get_l4_rx_status(msg);

	अगर (l4_rx_status == 1)
		वापस CHECKSUM_UNNECESSARY;

	अगर (l4_rx_status == 0 && l3_rx_status == 1)
		वापस CHECKSUM_UNNECESSARY;

	अगर (l3_rx_status == 0 && l4_rx_status == 0)
		/* L2 packet */
		वापस CHECKSUM_NONE;

	/* If HW reports bad checksum, let IP stack re-check it
	 * For example, HW करोesn't understand Microsoft IP stack that
	 * mis-calculates TCP checksum - अगर it should be 0x0,
	 * it ग_लिखोs 0xffff in violation of RFC 1624
	 */
	stats->rx_csum_err++;
	वापस CHECKSUM_NONE;
पूर्ण

अटल अंतरभूत पूर्णांक wil_rx_status_get_security(व्योम *msg)
अणु
	वापस WIL_GET_BITS(((काष्ठा wil_rx_status_compressed *)msg)->d0,
			    28, 28);
पूर्ण

अटल अंतरभूत u8 wil_rx_status_get_key_id(व्योम *msg)
अणु
	वापस WIL_GET_BITS(((काष्ठा wil_rx_status_compressed *)msg)->d1,
			    31, 31);
पूर्ण

अटल अंतरभूत u8 wil_tx_status_get_mcs(काष्ठा wil_ring_tx_status *msg)
अणु
	वापस WIL_GET_BITS(msg->d2, 0, 4);
पूर्ण

अटल अंतरभूत u32 wil_ring_next_head(काष्ठा wil_ring *ring)
अणु
	वापस (ring->swhead + 1) % ring->size;
पूर्ण

अटल अंतरभूत व्योम wil_desc_set_addr_edma(काष्ठा wil_ring_dma_addr *addr,
					  __le16 *addr_high_high,
					  dma_addr_t pa)
अणु
	addr->addr_low = cpu_to_le32(lower_32_bits(pa));
	addr->addr_high = cpu_to_le16((u16)upper_32_bits(pa));
	*addr_high_high = cpu_to_le16((u16)(upper_32_bits(pa) >> 16));
पूर्ण

अटल अंतरभूत
dma_addr_t wil_tx_desc_get_addr_edma(काष्ठा wil_ring_tx_enhanced_dma *dma)
अणु
	वापस le32_to_cpu(dma->addr.addr_low) |
			   ((u64)le16_to_cpu(dma->addr.addr_high) << 32) |
			   ((u64)le16_to_cpu(dma->addr_high_high) << 48);
पूर्ण

अटल अंतरभूत
dma_addr_t wil_rx_desc_get_addr_edma(काष्ठा wil_ring_rx_enhanced_dma *dma)
अणु
	वापस le32_to_cpu(dma->addr.addr_low) |
			   ((u64)le16_to_cpu(dma->addr.addr_high) << 32) |
			   ((u64)le16_to_cpu(dma->addr_high_high) << 48);
पूर्ण

व्योम wil_configure_पूर्णांकerrupt_moderation_edma(काष्ठा wil6210_priv *wil);
पूर्णांक wil_tx_sring_handler(काष्ठा wil6210_priv *wil,
			 काष्ठा wil_status_ring *sring);
व्योम wil_rx_handle_edma(काष्ठा wil6210_priv *wil, पूर्णांक *quota);
व्योम wil_init_txrx_ops_edma(काष्ठा wil6210_priv *wil);

#पूर्ण_अगर /* WIL6210_TXRX_EDMA_H */

