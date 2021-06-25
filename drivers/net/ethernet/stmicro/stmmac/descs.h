<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*******************************************************************************
  Header File to describe the DMA descriptors and related definitions.
  This is क्रम DWMAC100 and 1000 cores.


  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#अगर_अघोषित __DESCS_H__
#घोषणा __DESCS_H__

#समावेश <linux/bitops.h>

/* Normal receive descriptor defines */

/* RDES0 */
#घोषणा	RDES0_PAYLOAD_CSUM_ERR	BIT(0)
#घोषणा	RDES0_CRC_ERROR		BIT(1)
#घोषणा	RDES0_DRIBBLING		BIT(2)
#घोषणा	RDES0_MII_ERROR		BIT(3)
#घोषणा	RDES0_RECEIVE_WATCHDOG	BIT(4)
#घोषणा	RDES0_FRAME_TYPE	BIT(5)
#घोषणा	RDES0_COLLISION		BIT(6)
#घोषणा	RDES0_IPC_CSUM_ERROR	BIT(7)
#घोषणा	RDES0_LAST_DESCRIPTOR	BIT(8)
#घोषणा	RDES0_FIRST_DESCRIPTOR	BIT(9)
#घोषणा	RDES0_VLAN_TAG		BIT(10)
#घोषणा	RDES0_OVERFLOW_ERROR	BIT(11)
#घोषणा	RDES0_LENGTH_ERROR	BIT(12)
#घोषणा	RDES0_SA_FILTER_FAIL	BIT(13)
#घोषणा	RDES0_DESCRIPTOR_ERROR	BIT(14)
#घोषणा	RDES0_ERROR_SUMMARY	BIT(15)
#घोषणा	RDES0_FRAME_LEN_MASK	GENMASK(29, 16)
#घोषणा RDES0_FRAME_LEN_SHIFT	16
#घोषणा	RDES0_DA_FILTER_FAIL	BIT(30)
#घोषणा	RDES0_OWN		BIT(31)
			/* RDES1 */
#घोषणा	RDES1_BUFFER1_SIZE_MASK		GENMASK(10, 0)
#घोषणा	RDES1_BUFFER2_SIZE_MASK		GENMASK(21, 11)
#घोषणा	RDES1_BUFFER2_SIZE_SHIFT	11
#घोषणा	RDES1_SECOND_ADDRESS_CHAINED	BIT(24)
#घोषणा	RDES1_END_RING			BIT(25)
#घोषणा	RDES1_DISABLE_IC		BIT(31)

/* Enhanced receive descriptor defines */

/* RDES0 (similar to normal RDES) */
#घोषणा	 ERDES0_RX_MAC_ADDR	BIT(0)

/* RDES1: completely dअगरfer from normal desc definitions */
#घोषणा	ERDES1_BUFFER1_SIZE_MASK	GENMASK(12, 0)
#घोषणा	ERDES1_SECOND_ADDRESS_CHAINED	BIT(14)
#घोषणा	ERDES1_END_RING			BIT(15)
#घोषणा	ERDES1_BUFFER2_SIZE_MASK	GENMASK(28, 16)
#घोषणा ERDES1_BUFFER2_SIZE_SHIFT	16
#घोषणा	ERDES1_DISABLE_IC		BIT(31)

/* Normal transmit descriptor defines */
/* TDES0 */
#घोषणा	TDES0_DEFERRED			BIT(0)
#घोषणा	TDES0_UNDERFLOW_ERROR		BIT(1)
#घोषणा	TDES0_EXCESSIVE_DEFERRAL	BIT(2)
#घोषणा	TDES0_COLLISION_COUNT_MASK	GENMASK(6, 3)
#घोषणा	TDES0_VLAN_FRAME		BIT(7)
#घोषणा	TDES0_EXCESSIVE_COLLISIONS	BIT(8)
#घोषणा	TDES0_LATE_COLLISION		BIT(9)
#घोषणा	TDES0_NO_CARRIER		BIT(10)
#घोषणा	TDES0_LOSS_CARRIER		BIT(11)
#घोषणा	TDES0_PAYLOAD_ERROR		BIT(12)
#घोषणा	TDES0_FRAME_FLUSHED		BIT(13)
#घोषणा	TDES0_JABBER_TIMEOUT		BIT(14)
#घोषणा	TDES0_ERROR_SUMMARY		BIT(15)
#घोषणा	TDES0_IP_HEADER_ERROR		BIT(16)
#घोषणा	TDES0_TIME_STAMP_STATUS		BIT(17)
#घोषणा	TDES0_OWN			((u32)BIT(31))	/* silence sparse */
/* TDES1 */
#घोषणा	TDES1_BUFFER1_SIZE_MASK		GENMASK(10, 0)
#घोषणा	TDES1_BUFFER2_SIZE_MASK		GENMASK(21, 11)
#घोषणा	TDES1_BUFFER2_SIZE_SHIFT	11
#घोषणा	TDES1_TIME_STAMP_ENABLE		BIT(22)
#घोषणा	TDES1_DISABLE_PADDING		BIT(23)
#घोषणा	TDES1_SECOND_ADDRESS_CHAINED	BIT(24)
#घोषणा	TDES1_END_RING			BIT(25)
#घोषणा	TDES1_CRC_DISABLE		BIT(26)
#घोषणा	TDES1_CHECKSUM_INSERTION_MASK	GENMASK(28, 27)
#घोषणा	TDES1_CHECKSUM_INSERTION_SHIFT	27
#घोषणा	TDES1_FIRST_SEGMENT		BIT(29)
#घोषणा	TDES1_LAST_SEGMENT		BIT(30)
#घोषणा	TDES1_INTERRUPT			BIT(31)

/* Enhanced transmit descriptor defines */
/* TDES0 */
#घोषणा	ETDES0_DEFERRED			BIT(0)
#घोषणा	ETDES0_UNDERFLOW_ERROR		BIT(1)
#घोषणा	ETDES0_EXCESSIVE_DEFERRAL	BIT(2)
#घोषणा	ETDES0_COLLISION_COUNT_MASK	GENMASK(6, 3)
#घोषणा	ETDES0_VLAN_FRAME		BIT(7)
#घोषणा	ETDES0_EXCESSIVE_COLLISIONS	BIT(8)
#घोषणा	ETDES0_LATE_COLLISION		BIT(9)
#घोषणा	ETDES0_NO_CARRIER		BIT(10)
#घोषणा	ETDES0_LOSS_CARRIER		BIT(11)
#घोषणा	ETDES0_PAYLOAD_ERROR		BIT(12)
#घोषणा	ETDES0_FRAME_FLUSHED		BIT(13)
#घोषणा	ETDES0_JABBER_TIMEOUT		BIT(14)
#घोषणा	ETDES0_ERROR_SUMMARY		BIT(15)
#घोषणा	ETDES0_IP_HEADER_ERROR		BIT(16)
#घोषणा	ETDES0_TIME_STAMP_STATUS	BIT(17)
#घोषणा	ETDES0_SECOND_ADDRESS_CHAINED	BIT(20)
#घोषणा	ETDES0_END_RING			BIT(21)
#घोषणा	ETDES0_CHECKSUM_INSERTION_MASK	GENMASK(23, 22)
#घोषणा	ETDES0_CHECKSUM_INSERTION_SHIFT	22
#घोषणा	ETDES0_TIME_STAMP_ENABLE	BIT(25)
#घोषणा	ETDES0_DISABLE_PADDING		BIT(26)
#घोषणा	ETDES0_CRC_DISABLE		BIT(27)
#घोषणा	ETDES0_FIRST_SEGMENT		BIT(28)
#घोषणा	ETDES0_LAST_SEGMENT		BIT(29)
#घोषणा	ETDES0_INTERRUPT		BIT(30)
#घोषणा	ETDES0_OWN			((u32)BIT(31))	/* silence sparse */
/* TDES1 */
#घोषणा	ETDES1_BUFFER1_SIZE_MASK	GENMASK(12, 0)
#घोषणा	ETDES1_BUFFER2_SIZE_MASK	GENMASK(28, 16)
#घोषणा	ETDES1_BUFFER2_SIZE_SHIFT	16

/* Extended Receive descriptor definitions */
#घोषणा	ERDES4_IP_PAYLOAD_TYPE_MASK	GENMASK(6, 2)
#घोषणा	ERDES4_IP_HDR_ERR		BIT(3)
#घोषणा	ERDES4_IP_PAYLOAD_ERR		BIT(4)
#घोषणा	ERDES4_IP_CSUM_BYPASSED		BIT(5)
#घोषणा	ERDES4_IPV4_PKT_RCVD		BIT(6)
#घोषणा	ERDES4_IPV6_PKT_RCVD		BIT(7)
#घोषणा	ERDES4_MSG_TYPE_MASK		GENMASK(11, 8)
#घोषणा	ERDES4_PTP_FRAME_TYPE		BIT(12)
#घोषणा	ERDES4_PTP_VER			BIT(13)
#घोषणा	ERDES4_TIMESTAMP_DROPPED	BIT(14)
#घोषणा	ERDES4_AV_PKT_RCVD		BIT(16)
#घोषणा	ERDES4_AV_TAGGED_PKT_RCVD	BIT(17)
#घोषणा	ERDES4_VLAN_TAG_PRI_VAL_MASK	GENMASK(20, 18)
#घोषणा	ERDES4_L3_FILTER_MATCH		BIT(24)
#घोषणा	ERDES4_L4_FILTER_MATCH		BIT(25)
#घोषणा	ERDES4_L3_L4_FILT_NO_MATCH_MASK	GENMASK(27, 26)

/* Extended RDES4 message type definitions */
#घोषणा RDES_EXT_NO_PTP			0x0
#घोषणा RDES_EXT_SYNC			0x1
#घोषणा RDES_EXT_FOLLOW_UP		0x2
#घोषणा RDES_EXT_DELAY_REQ		0x3
#घोषणा RDES_EXT_DELAY_RESP		0x4
#घोषणा RDES_EXT_PDELAY_REQ		0x5
#घोषणा RDES_EXT_PDELAY_RESP		0x6
#घोषणा RDES_EXT_PDELAY_FOLLOW_UP	0x7
#घोषणा RDES_PTP_ANNOUNCE		0x8
#घोषणा RDES_PTP_MANAGEMENT		0x9
#घोषणा RDES_PTP_SIGNALING		0xa
#घोषणा RDES_PTP_PKT_RESERVED_TYPE	0xf

/* Basic descriptor काष्ठाure क्रम normal and alternate descriptors */
काष्ठा dma_desc अणु
	__le32 des0;
	__le32 des1;
	__le32 des2;
	__le32 des3;
पूर्ण;

/* Extended descriptor काष्ठाure (e.g. >= databook 3.50a) */
काष्ठा dma_extended_desc अणु
	काष्ठा dma_desc basic;	/* Basic descriptors */
	__le32 des4;	/* Extended Status */
	__le32 des5;	/* Reserved */
	__le32 des6;	/* Tx/Rx Timestamp Low */
	__le32 des7;	/* Tx/Rx Timestamp High */
पूर्ण;

/* Enhanced descriptor क्रम TBS */
काष्ठा dma_edesc अणु
	__le32 des4;
	__le32 des5;
	__le32 des6;
	__le32 des7;
	काष्ठा dma_desc basic;
पूर्ण;

/* Transmit checksum insertion control */
#घोषणा	TX_CIC_FULL	3	/* Include IP header and pseuकरोheader */

#पूर्ण_अगर /* __DESCS_H__ */
