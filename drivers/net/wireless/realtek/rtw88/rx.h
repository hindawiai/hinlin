<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#अगर_अघोषित __RTW_RX_H_
#घोषणा __RTW_RX_H_

क्रमागत rtw_rx_desc_enc अणु
	RX_DESC_ENC_NONE	= 0,
	RX_DESC_ENC_WEP40	= 1,
	RX_DESC_ENC_TKIP_WO_MIC	= 2,
	RX_DESC_ENC_TKIP_MIC	= 3,
	RX_DESC_ENC_AES		= 4,
	RX_DESC_ENC_WEP104	= 5,
पूर्ण;

#घोषणा GET_RX_DESC_PHYST(rxdesc)                                              \
	le32_get_bits(*((__le32 *)(rxdesc) + 0x00), BIT(26))
#घोषणा GET_RX_DESC_ICV_ERR(rxdesc)                                            \
	le32_get_bits(*((__le32 *)(rxdesc) + 0x00), BIT(15))
#घोषणा GET_RX_DESC_CRC32(rxdesc)                                              \
	le32_get_bits(*((__le32 *)(rxdesc) + 0x00), BIT(14))
#घोषणा GET_RX_DESC_SWDEC(rxdesc)                                              \
	le32_get_bits(*((__le32 *)(rxdesc) + 0x00), BIT(27))
#घोषणा GET_RX_DESC_C2H(rxdesc)                                                \
	le32_get_bits(*((__le32 *)(rxdesc) + 0x02), BIT(28))
#घोषणा GET_RX_DESC_PKT_LEN(rxdesc)                                            \
	le32_get_bits(*((__le32 *)(rxdesc) + 0x00), GENMASK(13, 0))
#घोषणा GET_RX_DESC_DRV_INFO_SIZE(rxdesc)                                      \
	le32_get_bits(*((__le32 *)(rxdesc) + 0x00), GENMASK(19, 16))
#घोषणा GET_RX_DESC_SHIFT(rxdesc)                                              \
	le32_get_bits(*((__le32 *)(rxdesc) + 0x00), GENMASK(25, 24))
#घोषणा GET_RX_DESC_ENC_TYPE(rxdesc)                                           \
	le32_get_bits(*((__le32 *)(rxdesc) + 0x00), GENMASK(22, 20))
#घोषणा GET_RX_DESC_RX_RATE(rxdesc)                                            \
	le32_get_bits(*((__le32 *)(rxdesc) + 0x03), GENMASK(6, 0))
#घोषणा GET_RX_DESC_MACID(rxdesc)                                              \
	le32_get_bits(*((__le32 *)(rxdesc) + 0x01), GENMASK(6, 0))
#घोषणा GET_RX_DESC_PPDU_CNT(rxdesc)                                           \
	le32_get_bits(*((__le32 *)(rxdesc) + 0x02), GENMASK(30, 29))
#घोषणा GET_RX_DESC_TSFL(rxdesc)                                               \
	le32_get_bits(*((__le32 *)(rxdesc) + 0x05), GENMASK(31, 0))

व्योम rtw_rx_stats(काष्ठा rtw_dev *rtwdev, काष्ठा ieee80211_vअगर *vअगर,
		  काष्ठा sk_buff *skb);
व्योम rtw_rx_fill_rx_status(काष्ठा rtw_dev *rtwdev,
			   काष्ठा rtw_rx_pkt_stat *pkt_stat,
			   काष्ठा ieee80211_hdr *hdr,
			   काष्ठा ieee80211_rx_status *rx_status,
			   u8 *phy_status);

#पूर्ण_अगर
