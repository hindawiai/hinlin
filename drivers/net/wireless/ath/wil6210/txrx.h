<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2012-2016 Qualcomm Atheros, Inc.
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित WIL6210_TXRX_H
#घोषणा WIL6210_TXRX_H

#समावेश "wil6210.h"
#समावेश "txrx_edma.h"

#घोषणा BUF_SW_OWNED    (1)
#घोषणा BUF_HW_OWNED    (0)

/* शेष size of MAC Tx/Rx buffers */
#घोषणा TXRX_BUF_LEN_DEFAULT (2048)

/* how many bytes to reserve क्रम rtap header? */
#घोषणा WIL6210_RTAP_SIZE (128)

/* Tx/Rx path */

अटल अंतरभूत dma_addr_t wil_desc_addr(काष्ठा wil_ring_dma_addr *addr)
अणु
	वापस le32_to_cpu(addr->addr_low) |
			   ((u64)le16_to_cpu(addr->addr_high) << 32);
पूर्ण

अटल अंतरभूत व्योम wil_desc_addr_set(काष्ठा wil_ring_dma_addr *addr,
				     dma_addr_t pa)
अणु
	addr->addr_low = cpu_to_le32(lower_32_bits(pa));
	addr->addr_high = cpu_to_le16((u16)upper_32_bits(pa));
पूर्ण

/* Tx descriptor - MAC part
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
 * bit      5 : mac_id_en:1
 * bit   6..7 : mac_id:2
 * bit  8..14 : reserved0:7
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
 * bit 22..31 : reserved0:10
 * [dword 3]
 * bit  0.. 31: ucode_cmd:32
 */
काष्ठा vring_tx_mac अणु
	u32 d[3];
	u32 ucode_cmd;
पूर्ण __packed;

/* TX MAC Dword 0 */
#घोषणा MAC_CFG_DESC_TX_0_LIFETIME_EXPIRY_VALUE_POS 0
#घोषणा MAC_CFG_DESC_TX_0_LIFETIME_EXPIRY_VALUE_LEN 10
#घोषणा MAC_CFG_DESC_TX_0_LIFETIME_EXPIRY_VALUE_MSK 0x3FF

#घोषणा MAC_CFG_DESC_TX_0_INTERRUP_EN_POS 10
#घोषणा MAC_CFG_DESC_TX_0_INTERRUP_EN_LEN 1
#घोषणा MAC_CFG_DESC_TX_0_INTERRUP_EN_MSK 0x400

#घोषणा MAC_CFG_DESC_TX_0_STATUS_EN_POS 11
#घोषणा MAC_CFG_DESC_TX_0_STATUS_EN_LEN 1
#घोषणा MAC_CFG_DESC_TX_0_STATUS_EN_MSK 0x800

#घोषणा MAC_CFG_DESC_TX_0_TXSS_OVERRIDE_POS 12
#घोषणा MAC_CFG_DESC_TX_0_TXSS_OVERRIDE_LEN 2
#घोषणा MAC_CFG_DESC_TX_0_TXSS_OVERRIDE_MSK 0x3000

#घोषणा MAC_CFG_DESC_TX_0_TIMESTAMP_INSERTION_POS 14
#घोषणा MAC_CFG_DESC_TX_0_TIMESTAMP_INSERTION_LEN 1
#घोषणा MAC_CFG_DESC_TX_0_TIMESTAMP_INSERTION_MSK 0x4000

#घोषणा MAC_CFG_DESC_TX_0_DURATION_PRESERVE_POS 15
#घोषणा MAC_CFG_DESC_TX_0_DURATION_PRESERVE_LEN 1
#घोषणा MAC_CFG_DESC_TX_0_DURATION_PRESERVE_MSK 0x8000

#घोषणा MAC_CFG_DESC_TX_0_MCS_INDEX_POS 22
#घोषणा MAC_CFG_DESC_TX_0_MCS_INDEX_LEN 5
#घोषणा MAC_CFG_DESC_TX_0_MCS_INDEX_MSK 0x7C00000

#घोषणा MAC_CFG_DESC_TX_0_MCS_EN_POS 27
#घोषणा MAC_CFG_DESC_TX_0_MCS_EN_LEN 1
#घोषणा MAC_CFG_DESC_TX_0_MCS_EN_MSK 0x8000000

#घोषणा MAC_CFG_DESC_TX_0_SN_PRESERVED_POS 31
#घोषणा MAC_CFG_DESC_TX_0_SN_PRESERVED_LEN 1
#घोषणा MAC_CFG_DESC_TX_0_SN_PRESERVED_MSK 0x80000000

/* TX MAC Dword 1 */
#घोषणा MAC_CFG_DESC_TX_1_PKT_MODE_POS 0
#घोषणा MAC_CFG_DESC_TX_1_PKT_MODE_LEN 4
#घोषणा MAC_CFG_DESC_TX_1_PKT_MODE_MSK 0xF

#घोषणा MAC_CFG_DESC_TX_1_PKT_MODE_EN_POS 4
#घोषणा MAC_CFG_DESC_TX_1_PKT_MODE_EN_LEN 1
#घोषणा MAC_CFG_DESC_TX_1_PKT_MODE_EN_MSK 0x10

#घोषणा MAC_CFG_DESC_TX_1_MAC_ID_EN_POS 5
#घोषणा MAC_CFG_DESC_TX_1_MAC_ID_EN_LEN 1
#घोषणा MAC_CFG_DESC_TX_1_MAC_ID_EN_MSK 0x20

#घोषणा MAC_CFG_DESC_TX_1_MAC_ID_POS 6
#घोषणा MAC_CFG_DESC_TX_1_MAC_ID_LEN 2
#घोषणा MAC_CFG_DESC_TX_1_MAC_ID_MSK 0xc0

#घोषणा MAC_CFG_DESC_TX_1_ACK_POLICY_EN_POS 15
#घोषणा MAC_CFG_DESC_TX_1_ACK_POLICY_EN_LEN 1
#घोषणा MAC_CFG_DESC_TX_1_ACK_POLICY_EN_MSK 0x8000

#घोषणा MAC_CFG_DESC_TX_1_DST_INDEX_POS 16
#घोषणा MAC_CFG_DESC_TX_1_DST_INDEX_LEN 4
#घोषणा MAC_CFG_DESC_TX_1_DST_INDEX_MSK 0xF0000

#घोषणा MAC_CFG_DESC_TX_1_DST_INDEX_EN_POS 20
#घोषणा MAC_CFG_DESC_TX_1_DST_INDEX_EN_LEN 1
#घोषणा MAC_CFG_DESC_TX_1_DST_INDEX_EN_MSK 0x100000

#घोषणा MAC_CFG_DESC_TX_1_ACK_POLICY_POS 21
#घोषणा MAC_CFG_DESC_TX_1_ACK_POLICY_LEN 2
#घोषणा MAC_CFG_DESC_TX_1_ACK_POLICY_MSK 0x600000

#घोषणा MAC_CFG_DESC_TX_1_LIFETIME_EN_POS 23
#घोषणा MAC_CFG_DESC_TX_1_LIFETIME_EN_LEN 1
#घोषणा MAC_CFG_DESC_TX_1_LIFETIME_EN_MSK 0x800000

#घोषणा MAC_CFG_DESC_TX_1_MAX_RETRY_POS 24
#घोषणा MAC_CFG_DESC_TX_1_MAX_RETRY_LEN 7
#घोषणा MAC_CFG_DESC_TX_1_MAX_RETRY_MSK 0x7F000000

#घोषणा MAC_CFG_DESC_TX_1_MAX_RETRY_EN_POS 31
#घोषणा MAC_CFG_DESC_TX_1_MAX_RETRY_EN_LEN 1
#घोषणा MAC_CFG_DESC_TX_1_MAX_RETRY_EN_MSK 0x80000000

/* TX MAC Dword 2 */
#घोषणा MAC_CFG_DESC_TX_2_NUM_OF_DESCRIPTORS_POS 0
#घोषणा MAC_CFG_DESC_TX_2_NUM_OF_DESCRIPTORS_LEN 8
#घोषणा MAC_CFG_DESC_TX_2_NUM_OF_DESCRIPTORS_MSK 0xFF

#घोषणा MAC_CFG_DESC_TX_2_RESERVED_POS 8
#घोषणा MAC_CFG_DESC_TX_2_RESERVED_LEN 10
#घोषणा MAC_CFG_DESC_TX_2_RESERVED_MSK 0x3FF00

#घोषणा MAC_CFG_DESC_TX_2_L2_TRANSLATION_TYPE_POS 18
#घोषणा MAC_CFG_DESC_TX_2_L2_TRANSLATION_TYPE_LEN 2
#घोषणा MAC_CFG_DESC_TX_2_L2_TRANSLATION_TYPE_MSK 0xC0000

#घोषणा MAC_CFG_DESC_TX_2_SNAP_HDR_INSERTION_EN_POS 20
#घोषणा MAC_CFG_DESC_TX_2_SNAP_HDR_INSERTION_EN_LEN 1
#घोषणा MAC_CFG_DESC_TX_2_SNAP_HDR_INSERTION_EN_MSK 0x100000

#घोषणा MAC_CFG_DESC_TX_2_VLAN_REMOVAL_EN_POS 21
#घोषणा MAC_CFG_DESC_TX_2_VLAN_REMOVAL_EN_LEN 1
#घोषणा MAC_CFG_DESC_TX_2_VLAN_REMOVAL_EN_MSK 0x200000

/* TX MAC Dword 3 */
#घोषणा MAC_CFG_DESC_TX_3_UCODE_CMD_POS 0
#घोषणा MAC_CFG_DESC_TX_3_UCODE_CMD_LEN 32
#घोषणा MAC_CFG_DESC_TX_3_UCODE_CMD_MSK 0xFFFFFFFF

/* TX DMA Dword 0 */
#घोषणा DMA_CFG_DESC_TX_0_L4_LENGTH_POS 0
#घोषणा DMA_CFG_DESC_TX_0_L4_LENGTH_LEN 8
#घोषणा DMA_CFG_DESC_TX_0_L4_LENGTH_MSK 0xFF

#घोषणा DMA_CFG_DESC_TX_0_CMD_EOP_POS 8
#घोषणा DMA_CFG_DESC_TX_0_CMD_EOP_LEN 1
#घोषणा DMA_CFG_DESC_TX_0_CMD_EOP_MSK 0x100

#घोषणा DMA_CFG_DESC_TX_0_CMD_MARK_WB_POS 9
#घोषणा DMA_CFG_DESC_TX_0_CMD_MARK_WB_LEN 1
#घोषणा DMA_CFG_DESC_TX_0_CMD_MARK_WB_MSK 0x200

#घोषणा DMA_CFG_DESC_TX_0_CMD_DMA_IT_POS 10
#घोषणा DMA_CFG_DESC_TX_0_CMD_DMA_IT_LEN 1
#घोषणा DMA_CFG_DESC_TX_0_CMD_DMA_IT_MSK 0x400

#घोषणा DMA_CFG_DESC_TX_0_SEGMENT_BUF_DETAILS_POS 11
#घोषणा DMA_CFG_DESC_TX_0_SEGMENT_BUF_DETAILS_LEN 2
#घोषणा DMA_CFG_DESC_TX_0_SEGMENT_BUF_DETAILS_MSK 0x1800

#घोषणा DMA_CFG_DESC_TX_0_TCP_SEG_EN_POS 13
#घोषणा DMA_CFG_DESC_TX_0_TCP_SEG_EN_LEN 1
#घोषणा DMA_CFG_DESC_TX_0_TCP_SEG_EN_MSK 0x2000

#घोषणा DMA_CFG_DESC_TX_0_IPV4_CHECKSUM_EN_POS 14
#घोषणा DMA_CFG_DESC_TX_0_IPV4_CHECKSUM_EN_LEN 1
#घोषणा DMA_CFG_DESC_TX_0_IPV4_CHECKSUM_EN_MSK 0x4000

#घोषणा DMA_CFG_DESC_TX_0_TCP_UDP_CHECKSUM_EN_POS 15
#घोषणा DMA_CFG_DESC_TX_0_TCP_UDP_CHECKSUM_EN_LEN 1
#घोषणा DMA_CFG_DESC_TX_0_TCP_UDP_CHECKSUM_EN_MSK 0x8000

#घोषणा DMA_CFG_DESC_TX_0_QID_POS 16
#घोषणा DMA_CFG_DESC_TX_0_QID_LEN 5
#घोषणा DMA_CFG_DESC_TX_0_QID_MSK 0x1F0000

#घोषणा DMA_CFG_DESC_TX_0_PSEUDO_HEADER_CALC_EN_POS 21
#घोषणा DMA_CFG_DESC_TX_0_PSEUDO_HEADER_CALC_EN_LEN 1
#घोषणा DMA_CFG_DESC_TX_0_PSEUDO_HEADER_CALC_EN_MSK 0x200000

#घोषणा DMA_CFG_DESC_TX_0_L4_TYPE_POS 30
#घोषणा DMA_CFG_DESC_TX_0_L4_TYPE_LEN 2
#घोषणा DMA_CFG_DESC_TX_0_L4_TYPE_MSK 0xC0000000 /* L4 type: 0-UDP, 2-TCP */

#घोषणा DMA_CFG_DESC_TX_OFFLOAD_CFG_MAC_LEN_POS 0
#घोषणा DMA_CFG_DESC_TX_OFFLOAD_CFG_MAC_LEN_LEN 7
#घोषणा DMA_CFG_DESC_TX_OFFLOAD_CFG_MAC_LEN_MSK 0x7F /* MAC hdr len */

#घोषणा DMA_CFG_DESC_TX_OFFLOAD_CFG_L3T_IPV4_POS 7
#घोषणा DMA_CFG_DESC_TX_OFFLOAD_CFG_L3T_IPV4_LEN 1
#घोषणा DMA_CFG_DESC_TX_OFFLOAD_CFG_L3T_IPV4_MSK 0x80 /* 1-IPv4, 0-IPv6 */

#घोषणा TX_DMA_STATUS_DU         BIT(0)

/* Tx descriptor - DMA part
 * [dword 0]
 * bit  0.. 7 : l4_length:8 layer 4 length
 * bit      8 : cmd_eop:1 This descriptor is the last one in the packet
 * bit      9 : reserved
 * bit     10 : cmd_dma_it:1 immediate पूर्णांकerrupt
 * bit 11..12 : SBD - Segment Buffer Details
 *		00 - Header Segment
 *		01 - First Data Segment
 *		10 - Medium Data Segment
 *		11 - Last Data Segment
 * bit     13 : TSE - TCP Segmentation Enable
 * bit     14 : IIC - Directs the HW to Insert IPv4 Checksum
 * bit     15 : ITC - Directs the HW to Insert TCP/UDP Checksum
 * bit 16..20 : QID - The target QID that the packet should be stored
 *		in the MAC.
 * bit     21 : PO - Pseuकरो header Offload:
 *		0 - Use the pseuकरो header value from the TCP checksum field
 *		1- Calculate Pseuकरो header Checksum
 * bit     22 : NC - No UDP Checksum
 * bit 23..29 : reserved
 * bit 30..31 : L4T - Layer 4 Type: 00 - UDP , 10 - TCP , 10, 11 - Reserved
 *		If L4Len equal 0, no L4 at all
 * [dword 1]
 * bit  0..31 : addr_low:32 The payload buffer low address
 * [dword 2]
 * bit  0..15 : addr_high:16 The payload buffer high address
 * bit 16..23 : ip_length:8 The IP header length क्रम the TX IP checksum
 *		offload feature
 * bit 24..30 : mac_length:7
 * bit     31 : ip_version:1 1 - IPv4, 0 - IPv6
 * [dword 3]
 *  [byte 12] error
 * bit  0   2 : mac_status:3
 * bit  3   7 : reserved:5
 *  [byte 13] status
 * bit      0 : DU:1 Descriptor Used
 * bit  1   7 : reserved:7
 *  [word 7] length
 */
काष्ठा vring_tx_dma अणु
	u32 d0;
	काष्ठा wil_ring_dma_addr addr;
	u8  ip_length;
	u8  b11;       /* 0..6: mac_length; 7:ip_version */
	u8  error;     /* 0..2: err; 3..7: reserved; */
	u8  status;    /* 0: used; 1..7; reserved */
	__le16 length;
पूर्ण __packed;

/* TSO type used in dma descriptor d0 bits 11-12 */
क्रमागत अणु
	wil_tso_type_hdr = 0,
	wil_tso_type_first = 1,
	wil_tso_type_mid  = 2,
	wil_tso_type_lst  = 3,
पूर्ण;

/* Rx descriptor - MAC part
 * [dword 0]
 * bit  0.. 3 : tid:4 The QoS (b3-0) TID Field
 * bit  4.. 6 : cid:3 The Source index that  was found during parsing the TA.
 *		This field is used to define the source of the packet
 * bit      7 : MAC_id_valid:1, 1 अगर MAC भव number is valid.
 * bit  8.. 9 : mid:2 The MAC भव number
 * bit 10..11 : frame_type:2 : The FC (b3-2) - MPDU Type
 *		(management, data, control and extension)
 * bit 12..15 : frame_subtype:4 : The FC (b7-4) - Frame Subtype
 * bit 16..27 : seq_number:12 The received Sequence number field
 * bit 28..31 : extended:4 extended subtype
 * [dword 1]
 * bit  0.. 3 : reserved
 * bit  4.. 5 : key_id:2
 * bit      6 : decrypt_bypass:1
 * bit      7 : security:1 FC (b14)
 * bit  8.. 9 : ds_bits:2 FC (b9-8)
 * bit     10 : a_msdu_present:1  QoS (b7)
 * bit     11 : a_msdu_type:1  QoS (b8)
 * bit     12 : a_mpdu:1  part of AMPDU aggregation
 * bit     13 : broadcast:1
 * bit     14 : mutlicast:1
 * bit     15 : reserved:1
 * bit 16..20 : rx_mac_qid:5 The Queue Identअगरier that the packet
 *		is received from
 * bit 21..24 : mcs:4
 * bit 25..28 : mic_icr:4 this संकेत tells the DMA to निश्चित an पूर्णांकerrupt
 *		after it ग_लिखोs the packet
 * bit 29..31 : reserved:3
 * [dword 2]
 * bit  0.. 2 : समय_slot:3 The बारlot that the MPDU is received
 * bit  3.. 4 : fc_protocol_ver:1 The FC (b1-0) - Protocol Version
 * bit      5 : fc_order:1 The FC Control (b15) -Order
 * bit  6.. 7 : qos_ack_policy:2 The QoS (b6-5) ack policy Field
 * bit      8 : esop:1 The QoS (b4) ESOP field
 * bit      9 : qos_rdg_more_ppdu:1 The QoS (b9) RDG field
 * bit 10..14 : qos_reserved:5 The QoS (b14-10) Reserved field
 * bit     15 : qos_ac_स्थिरraपूर्णांक:1 QoS (b15)
 * bit 16..31 : pn_15_0:16 low 2 bytes of PN
 * [dword 3]
 * bit  0..31 : pn_47_16:32 high 4 bytes of PN
 */
काष्ठा vring_rx_mac अणु
	u32 d0;
	u32 d1;
	u16 w4;
	u16 pn_15_0;
	u32 pn_47_16;
पूर्ण __packed;

/* Rx descriptor - DMA part
 * [dword 0]
 * bit  0.. 7 : l4_length:8 layer 4 length. The field is only valid अगर
 *		L4I bit is set
 * bit      8 : cmd_eop:1 set to 1
 * bit      9 : cmd_rt:1 set to 1
 * bit     10 : cmd_dma_it:1 immediate पूर्णांकerrupt
 * bit 11..15 : reserved:5
 * bit 16..29 : phy_info_length:14 It is valid when the PII is set.
 *		When the FFM bit is set bits 29-27 are used क्रम क्रम
 *		Flex Filter Match. Matching Index to one of the L2
 *		EtherType Flex Filter
 * bit 30..31 : l4_type:2 valid अगर the L4I bit is set in the status field
 *		00 - UDP, 01 - TCP, 10, 11 - reserved
 * [dword 1]
 * bit  0..31 : addr_low:32 The payload buffer low address
 * [dword 2]
 * bit  0..15 : addr_high:16 The payload buffer high address
 * bit 16..23 : ip_length:8 The filed is valid only अगर the L3I bit is set
 * bit 24..30 : mac_length:7
 * bit     31 : ip_version:1 1 - IPv4, 0 - IPv6
 * [dword 3]
 *  [byte 12] error
 * bit      0 : FCS:1
 * bit      1 : MIC:1
 * bit      2 : Key miss:1
 * bit      3 : Replay:1
 * bit      4 : L3:1 IPv4 checksum
 * bit      5 : L4:1 TCP/UDP checksum
 * bit  6   7 : reserved:2
 *  [byte 13] status
 * bit      0 : DU:1 Descriptor Used
 * bit      1 : EOP:1 The descriptor indicates the End of Packet
 * bit      2 : error:1
 * bit      3 : MI:1 MAC Interrupt is निश्चितed (according to parser decision)
 * bit      4 : L3I:1 L3 identअगरied and checksum calculated
 * bit      5 : L4I:1 L4 identअगरied and checksum calculated
 * bit      6 : PII:1 PHY Info Included in the packet
 * bit      7 : FFM:1 EtherType Flex Filter Match
 *  [word 7] length
 */

#घोषणा RX_DMA_D0_CMD_DMA_EOP	BIT(8)
#घोषणा RX_DMA_D0_CMD_DMA_RT	BIT(9)  /* always 1 */
#घोषणा RX_DMA_D0_CMD_DMA_IT	BIT(10) /* पूर्णांकerrupt */
#घोषणा RX_MAC_D0_MAC_ID_VALID	BIT(7)

/* Error field */
#घोषणा RX_DMA_ERROR_FCS	BIT(0)
#घोषणा RX_DMA_ERROR_MIC	BIT(1)
#घोषणा RX_DMA_ERROR_KEY	BIT(2) /* Key missing */
#घोषणा RX_DMA_ERROR_REPLAY	BIT(3)
#घोषणा RX_DMA_ERROR_L3_ERR	BIT(4)
#घोषणा RX_DMA_ERROR_L4_ERR	BIT(5)

/* Status field */
#घोषणा RX_DMA_STATUS_DU	BIT(0)
#घोषणा RX_DMA_STATUS_EOP	BIT(1)
#घोषणा RX_DMA_STATUS_ERROR	BIT(2)
#घोषणा RX_DMA_STATUS_MI	BIT(3) /* MAC Interrupt is निश्चितed */
#घोषणा RX_DMA_STATUS_L3I	BIT(4)
#घोषणा RX_DMA_STATUS_L4I	BIT(5)
#घोषणा RX_DMA_STATUS_PHY_INFO	BIT(6)
#घोषणा RX_DMA_STATUS_FFM	BIT(7) /* EtherType Flex Filter Match */

/* IEEE 802.11, 8.5.2 EAPOL-Key frames */
#घोषणा WIL_KEY_INFO_KEY_TYPE BIT(3) /* val of 1 = Pairwise, 0 = Group key */

#घोषणा WIL_KEY_INFO_MIC BIT(8)
#घोषणा WIL_KEY_INFO_ENCR_KEY_DATA BIT(12) /* क्रम rsn only */

#घोषणा WIL_EAP_NONCE_LEN 32
#घोषणा WIL_EAP_KEY_RSC_LEN 8
#घोषणा WIL_EAP_REPLAY_COUNTER_LEN 8
#घोषणा WIL_EAP_KEY_IV_LEN 16
#घोषणा WIL_EAP_KEY_ID_LEN 8

क्रमागत अणु
	WIL_1X_TYPE_EAP_PACKET = 0,
	WIL_1X_TYPE_EAPOL_START = 1,
	WIL_1X_TYPE_EAPOL_LOGOFF = 2,
	WIL_1X_TYPE_EAPOL_KEY = 3,
पूर्ण;

#घोषणा WIL_EAPOL_KEY_TYPE_RSN 2
#घोषणा WIL_EAPOL_KEY_TYPE_WPA 254

काष्ठा wil_1x_hdr अणु
	u8 version;
	u8 type;
	__be16 length;
	/* followed by data */
पूर्ण __packed;

काष्ठा wil_eapol_key अणु
	u8 type;
	__be16 key_info;
	__be16 key_length;
	u8 replay_counter[WIL_EAP_REPLAY_COUNTER_LEN];
	u8 key_nonce[WIL_EAP_NONCE_LEN];
	u8 key_iv[WIL_EAP_KEY_IV_LEN];
	u8 key_rsc[WIL_EAP_KEY_RSC_LEN];
	u8 key_id[WIL_EAP_KEY_ID_LEN];
पूर्ण __packed;

काष्ठा vring_rx_dma अणु
	u32 d0;
	काष्ठा wil_ring_dma_addr addr;
	u8  ip_length;
	u8  b11;
	u8  error;
	u8  status;
	__le16 length;
पूर्ण __packed;

काष्ठा vring_tx_desc अणु
	काष्ठा vring_tx_mac mac;
	काष्ठा vring_tx_dma dma;
पूर्ण __packed;

जोड़ wil_tx_desc अणु
	काष्ठा vring_tx_desc legacy;
	काष्ठा wil_tx_enhanced_desc enhanced;
पूर्ण __packed;

काष्ठा vring_rx_desc अणु
	काष्ठा vring_rx_mac mac;
	काष्ठा vring_rx_dma dma;
पूर्ण __packed;

जोड़ wil_rx_desc अणु
	काष्ठा vring_rx_desc legacy;
	काष्ठा wil_rx_enhanced_desc enhanced;
पूर्ण __packed;

जोड़ wil_ring_desc अणु
	जोड़ wil_tx_desc tx;
	जोड़ wil_rx_desc rx;
पूर्ण __packed;

काष्ठा packet_rx_info अणु
	u8 cid;
पूर्ण;

/* this काष्ठा will be stored in the skb cb buffer
 * max length of the काष्ठा is limited to 48 bytes
 */
काष्ठा skb_rx_info अणु
	काष्ठा vring_rx_desc rx_desc;
	काष्ठा packet_rx_info rx_info;
पूर्ण;

अटल अंतरभूत पूर्णांक wil_rxdesc_tid(काष्ठा vring_rx_desc *d)
अणु
	वापस WIL_GET_BITS(d->mac.d0, 0, 3);
पूर्ण

अटल अंतरभूत पूर्णांक wil_rxdesc_cid(काष्ठा vring_rx_desc *d)
अणु
	वापस WIL_GET_BITS(d->mac.d0, 4, 6);
पूर्ण

अटल अंतरभूत पूर्णांक wil_rxdesc_mid(काष्ठा vring_rx_desc *d)
अणु
	वापस (d->mac.d0 & RX_MAC_D0_MAC_ID_VALID) ?
		WIL_GET_BITS(d->mac.d0, 8, 9) : 0;
पूर्ण

अटल अंतरभूत पूर्णांक wil_rxdesc_ftype(काष्ठा vring_rx_desc *d)
अणु
	वापस WIL_GET_BITS(d->mac.d0, 10, 11);
पूर्ण

अटल अंतरभूत पूर्णांक wil_rxdesc_subtype(काष्ठा vring_rx_desc *d)
अणु
	वापस WIL_GET_BITS(d->mac.d0, 12, 15);
पूर्ण

/* 1-st byte (with frame type/subtype) of FC field */
अटल अंतरभूत u8 wil_rxdesc_fc1(काष्ठा vring_rx_desc *d)
अणु
	वापस (u8)(WIL_GET_BITS(d->mac.d0, 10, 15) << 2);
पूर्ण

अटल अंतरभूत पूर्णांक wil_rxdesc_seq(काष्ठा vring_rx_desc *d)
अणु
	वापस WIL_GET_BITS(d->mac.d0, 16, 27);
पूर्ण

अटल अंतरभूत पूर्णांक wil_rxdesc_ext_subtype(काष्ठा vring_rx_desc *d)
अणु
	वापस WIL_GET_BITS(d->mac.d0, 28, 31);
पूर्ण

अटल अंतरभूत पूर्णांक wil_rxdesc_retry(काष्ठा vring_rx_desc *d)
अणु
	वापस WIL_GET_BITS(d->mac.d0, 31, 31);
पूर्ण

अटल अंतरभूत पूर्णांक wil_rxdesc_key_id(काष्ठा vring_rx_desc *d)
अणु
	वापस WIL_GET_BITS(d->mac.d1, 4, 5);
पूर्ण

अटल अंतरभूत पूर्णांक wil_rxdesc_security(काष्ठा vring_rx_desc *d)
अणु
	वापस WIL_GET_BITS(d->mac.d1, 7, 7);
पूर्ण

अटल अंतरभूत पूर्णांक wil_rxdesc_ds_bits(काष्ठा vring_rx_desc *d)
अणु
	वापस WIL_GET_BITS(d->mac.d1, 8, 9);
पूर्ण

अटल अंतरभूत पूर्णांक wil_rxdesc_mcs(काष्ठा vring_rx_desc *d)
अणु
	वापस WIL_GET_BITS(d->mac.d1, 21, 24);
पूर्ण

अटल अंतरभूत पूर्णांक wil_rxdesc_mcast(काष्ठा vring_rx_desc *d)
अणु
	वापस WIL_GET_BITS(d->mac.d1, 13, 14);
पूर्ण

अटल अंतरभूत काष्ठा vring_rx_desc *wil_skb_rxdesc(काष्ठा sk_buff *skb)
अणु
	वापस (व्योम *)skb->cb;
पूर्ण

अटल अंतरभूत पूर्णांक wil_ring_is_empty(काष्ठा wil_ring *ring)
अणु
	वापस ring->swhead == ring->swtail;
पूर्ण

अटल अंतरभूत u32 wil_ring_next_tail(काष्ठा wil_ring *ring)
अणु
	वापस (ring->swtail + 1) % ring->size;
पूर्ण

अटल अंतरभूत व्योम wil_ring_advance_head(काष्ठा wil_ring *ring, पूर्णांक n)
अणु
	ring->swhead = (ring->swhead + n) % ring->size;
पूर्ण

अटल अंतरभूत पूर्णांक wil_ring_is_full(काष्ठा wil_ring *ring)
अणु
	वापस wil_ring_next_tail(ring) == ring->swhead;
पूर्ण

अटल अंतरभूत u8 *wil_skb_get_da(काष्ठा sk_buff *skb)
अणु
	काष्ठा ethhdr *eth = (व्योम *)skb->data;

	वापस eth->h_dest;
पूर्ण

अटल अंतरभूत u8 *wil_skb_get_sa(काष्ठा sk_buff *skb)
अणु
	काष्ठा ethhdr *eth = (व्योम *)skb->data;

	वापस eth->h_source;
पूर्ण

अटल अंतरभूत bool wil_need_txstat(काष्ठा sk_buff *skb)
अणु
	स्थिर u8 *da = wil_skb_get_da(skb);

	वापस is_unicast_ether_addr(da) && skb->sk &&
	       (skb_shinfo(skb)->tx_flags & SKBTX_WIFI_STATUS);
पूर्ण

अटल अंतरभूत व्योम wil_consume_skb(काष्ठा sk_buff *skb, bool acked)
अणु
	अगर (unlikely(wil_need_txstat(skb)))
		skb_complete_wअगरi_ack(skb, acked);
	अन्यथा
		acked ? dev_consume_skb_any(skb) : dev_kमुक्त_skb_any(skb);
पूर्ण

/* Used space in Tx ring */
अटल अंतरभूत पूर्णांक wil_ring_used_tx(काष्ठा wil_ring *ring)
अणु
	u32 swhead = ring->swhead;
	u32 swtail = ring->swtail;

	वापस (ring->size + swhead - swtail) % ring->size;
पूर्ण

/* Available space in Tx ring */
अटल अंतरभूत पूर्णांक wil_ring_avail_tx(काष्ठा wil_ring *ring)
अणु
	वापस ring->size - wil_ring_used_tx(ring) - 1;
पूर्ण

अटल अंतरभूत पूर्णांक wil_get_min_tx_ring_id(काष्ठा wil6210_priv *wil)
अणु
	/* In Enhanced DMA ring 0 is reserved क्रम RX */
	वापस wil->use_enhanced_dma_hw ? 1 : 0;
पूर्ण

/* similar to ieee80211_ version, but FC contain only 1-st byte */
अटल अंतरभूत पूर्णांक wil_is_back_req(u8 fc)
अणु
	वापस (fc & (IEEE80211_FCTL_FTYPE | IEEE80211_FCTL_STYPE)) ==
	       (IEEE80211_FTYPE_CTL | IEEE80211_STYPE_BACK_REQ);
पूर्ण

/* wil_val_in_range - check अगर value in [min,max) */
अटल अंतरभूत bool wil_val_in_range(पूर्णांक val, पूर्णांक min, पूर्णांक max)
अणु
	वापस val >= min && val < max;
पूर्ण

अटल अंतरभूत u8 wil_skb_get_cid(काष्ठा sk_buff *skb)
अणु
	काष्ठा skb_rx_info *skb_rx_info = (व्योम *)skb->cb;

	वापस skb_rx_info->rx_info.cid;
पूर्ण

अटल अंतरभूत व्योम wil_skb_set_cid(काष्ठा sk_buff *skb, u8 cid)
अणु
	काष्ठा skb_rx_info *skb_rx_info = (व्योम *)skb->cb;

	skb_rx_info->rx_info.cid = cid;
पूर्ण

व्योम wil_netअगर_rx_any(काष्ठा sk_buff *skb, काष्ठा net_device *ndev);
व्योम wil_netअगर_rx(काष्ठा sk_buff *skb, काष्ठा net_device *ndev, पूर्णांक cid,
		  काष्ठा wil_net_stats *stats, bool gro);
व्योम wil_rx_reorder(काष्ठा wil6210_priv *wil, काष्ठा sk_buff *skb);
व्योम wil_rx_bar(काष्ठा wil6210_priv *wil, काष्ठा wil6210_vअगर *vअगर,
		u8 cid, u8 tid, u16 seq);
काष्ठा wil_tid_ampdu_rx *wil_tid_ampdu_rx_alloc(काष्ठा wil6210_priv *wil,
						पूर्णांक size, u16 ssn);
व्योम wil_tid_ampdu_rx_मुक्त(काष्ठा wil6210_priv *wil,
			   काष्ठा wil_tid_ampdu_rx *r);
व्योम wil_tx_data_init(काष्ठा wil_ring_tx_data *txdata);
व्योम wil_init_txrx_ops_legacy_dma(काष्ठा wil6210_priv *wil);
व्योम wil_tx_latency_calc(काष्ठा wil6210_priv *wil, काष्ठा sk_buff *skb,
			 काष्ठा wil_sta_info *sta);

#पूर्ण_अगर /* WIL6210_TXRX_H */
