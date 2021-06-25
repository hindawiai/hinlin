<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 */

#अगर_अघोषित __MT7601U_DMA_H
#घोषणा __MT7601U_DMA_H

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/skbuff.h>

#घोषणा MT_DMA_HDR_LEN			4
#घोषणा MT_RX_INFO_LEN			4
#घोषणा MT_FCE_INFO_LEN			4
#घोषणा MT_DMA_HDRS			(MT_DMA_HDR_LEN + MT_RX_INFO_LEN)

/* Common Tx DMA descriptor fields */
#घोषणा MT_TXD_INFO_LEN			GENMASK(15, 0)
#घोषणा MT_TXD_INFO_D_PORT		GENMASK(29, 27)
#घोषणा MT_TXD_INFO_TYPE		GENMASK(31, 30)

क्रमागत mt76_msg_port अणु
	WLAN_PORT,
	CPU_RX_PORT,
	CPU_TX_PORT,
	HOST_PORT,
	VIRTUAL_CPU_RX_PORT,
	VIRTUAL_CPU_TX_PORT,
	DISCARD,
पूर्ण;

क्रमागत mt76_info_type अणु
	DMA_PACKET,
	DMA_COMMAND,
पूर्ण;

/* Tx DMA packet specअगरic flags */
#घोषणा MT_TXD_PKT_INFO_NEXT_VLD	BIT(16)
#घोषणा MT_TXD_PKT_INFO_TX_BURST	BIT(17)
#घोषणा MT_TXD_PKT_INFO_80211		BIT(19)
#घोषणा MT_TXD_PKT_INFO_TSO		BIT(20)
#घोषणा MT_TXD_PKT_INFO_CSO		BIT(21)
#घोषणा MT_TXD_PKT_INFO_WIV		BIT(24)
#घोषणा MT_TXD_PKT_INFO_QSEL		GENMASK(26, 25)

क्रमागत mt76_qsel अणु
	MT_QSEL_MGMT,
	MT_QSEL_HCCA,
	MT_QSEL_EDCA,
	MT_QSEL_EDCA_2,
पूर्ण;

/* Tx DMA MCU command specअगरic flags */
#घोषणा MT_TXD_CMD_INFO_SEQ		GENMASK(19, 16)
#घोषणा MT_TXD_CMD_INFO_TYPE		GENMASK(26, 20)

अटल अंतरभूत पूर्णांक mt7601u_dma_skb_wrap(काष्ठा sk_buff *skb,
				       क्रमागत mt76_msg_port d_port,
				       क्रमागत mt76_info_type type, u32 flags)
अणु
	u32 info;

	/* Buffer layout:
	 *	|   4B   | xfer len |      pad       |  4B  |
	 *	| TXINFO | pkt/cmd  | zero pad to 4B | zero |
	 *
	 * length field of TXINFO should be set to 'xfer len'.
	 */

	info = flags |
		FIELD_PREP(MT_TXD_INFO_LEN, round_up(skb->len, 4)) |
		FIELD_PREP(MT_TXD_INFO_D_PORT, d_port) |
		FIELD_PREP(MT_TXD_INFO_TYPE, type);

	put_unaligned_le32(info, skb_push(skb, माप(info)));
	वापस skb_put_padto(skb, round_up(skb->len, 4) + 4);
पूर्ण

अटल अंतरभूत पूर्णांक
mt7601u_dma_skb_wrap_pkt(काष्ठा sk_buff *skb, क्रमागत mt76_qsel qsel, u32 flags)
अणु
	flags |= FIELD_PREP(MT_TXD_PKT_INFO_QSEL, qsel);
	वापस mt7601u_dma_skb_wrap(skb, WLAN_PORT, DMA_PACKET, flags);
पूर्ण

/* Common Rx DMA descriptor fields */
#घोषणा MT_RXD_INFO_LEN			GENMASK(13, 0)
#घोषणा MT_RXD_INFO_PCIE_INTR		BIT(24)
#घोषणा MT_RXD_INFO_QSEL		GENMASK(26, 25)
#घोषणा MT_RXD_INFO_PORT		GENMASK(29, 27)
#घोषणा MT_RXD_INFO_TYPE		GENMASK(31, 30)

/* Rx DMA packet specअगरic flags */
#घोषणा MT_RXD_PKT_INFO_UDP_ERR		BIT(16)
#घोषणा MT_RXD_PKT_INFO_TCP_ERR		BIT(17)
#घोषणा MT_RXD_PKT_INFO_IP_ERR		BIT(18)
#घोषणा MT_RXD_PKT_INFO_PKT_80211	BIT(19)
#घोषणा MT_RXD_PKT_INFO_L3L4_DONE	BIT(20)
#घोषणा MT_RXD_PKT_INFO_MAC_LEN		GENMASK(23, 21)

/* Rx DMA MCU command specअगरic flags */
#घोषणा MT_RXD_CMD_INFO_SELF_GEN	BIT(15)
#घोषणा MT_RXD_CMD_INFO_CMD_SEQ		GENMASK(19, 16)
#घोषणा MT_RXD_CMD_INFO_EVT_TYPE	GENMASK(23, 20)

क्रमागत mt76_evt_type अणु
	CMD_DONE,
	CMD_ERROR,
	CMD_RETRY,
	EVENT_PWR_RSP,
	EVENT_WOW_RSP,
	EVENT_CARRIER_DETECT_RSP,
	EVENT_DFS_DETECT_RSP,
पूर्ण;

#पूर्ण_अगर
