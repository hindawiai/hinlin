<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Applied Micro X-Gene SoC Ethernet v2 Driver
 *
 * Copyright (c) 2017, Applied Micro Circuits Corporation
 * Author(s): Iyappan Subramanian <isubramanian@apm.com>
 *	      Keyur Chudgar <kchudgar@apm.com>
 */

#अगर_अघोषित __XGENE_ENET_V2_RING_H__
#घोषणा __XGENE_ENET_V2_RING_H__

#घोषणा XGENE_ENET_DESC_SIZE	64
#घोषणा XGENE_ENET_NUM_DESC	256
#घोषणा NUM_BUFS		8
#घोषणा SLOT_EMPTY		0xfff

#घोषणा DMATXCTRL		0xa180
#घोषणा DMATXDESCL		0xa184
#घोषणा DMATXDESCH		0xa1a0
#घोषणा DMATXSTATUS		0xa188
#घोषणा DMARXCTRL		0xa18c
#घोषणा DMARXDESCL		0xa190
#घोषणा DMARXDESCH		0xa1a4
#घोषणा DMARXSTATUS		0xa194
#घोषणा DMAINTRMASK		0xa198
#घोषणा DMAINTERRUPT		0xa19c

#घोषणा D_POS			62
#घोषणा D_LEN			2
#घोषणा E_POS			63
#घोषणा E_LEN			1
#घोषणा PKT_ADDRL_POS		0
#घोषणा PKT_ADDRL_LEN		32
#घोषणा PKT_ADDRH_POS		32
#घोषणा PKT_ADDRH_LEN		10
#घोषणा PKT_SIZE_POS		32
#घोषणा PKT_SIZE_LEN		12
#घोषणा NEXT_DESC_ADDRL_POS	0
#घोषणा NEXT_DESC_ADDRL_LEN	32
#घोषणा NEXT_DESC_ADDRH_POS	48
#घोषणा NEXT_DESC_ADDRH_LEN	10

#घोषणा TXPKTCOUNT_POS		16
#घोषणा TXPKTCOUNT_LEN		8
#घोषणा RXPKTCOUNT_POS		16
#घोषणा RXPKTCOUNT_LEN		8

#घोषणा TX_PKT_SENT		BIT(0)
#घोषणा TX_BUS_ERROR		BIT(3)
#घोषणा RX_PKT_RCVD		BIT(4)
#घोषणा RX_BUS_ERROR		BIT(7)
#घोषणा RXSTATUS_RXPKTRCVD	BIT(0)

काष्ठा xge_raw_desc अणु
	__le64 m0;
	__le64 m1;
	__le64 m2;
	__le64 m3;
	__le64 m4;
	__le64 m5;
	__le64 m6;
	__le64 m7;
पूर्ण;

काष्ठा pkt_info अणु
	काष्ठा sk_buff *skb;
	dma_addr_t dma_addr;
	व्योम *pkt_buf;
पूर्ण;

/* software context of a descriptor ring */
काष्ठा xge_desc_ring अणु
	काष्ठा net_device *ndev;
	dma_addr_t dma_addr;
	u8 head;
	u8 tail;
	जोड़ अणु
		व्योम *desc_addr;
		काष्ठा xge_raw_desc *raw_desc;
	पूर्ण;
	काष्ठा pkt_info (*pkt_info);
पूर्ण;

अटल अंतरभूत u64 xge_set_desc_bits(पूर्णांक pos, पूर्णांक len, u64 val)
अणु
	वापस (val & ((1ULL << len) - 1)) << pos;
पूर्ण

अटल अंतरभूत u64 xge_get_desc_bits(पूर्णांक pos, पूर्णांक len, u64 src)
अणु
	वापस (src >> pos) & ((1ULL << len) - 1);
पूर्ण

#घोषणा SET_BITS(field, val) \
		xge_set_desc_bits(field ## _POS, field ## _LEN, val)

#घोषणा GET_BITS(field, src) \
		xge_get_desc_bits(field ## _POS, field ## _LEN, src)

व्योम xge_setup_desc(काष्ठा xge_desc_ring *ring);
व्योम xge_update_tx_desc_addr(काष्ठा xge_pdata *pdata);
व्योम xge_update_rx_desc_addr(काष्ठा xge_pdata *pdata);
व्योम xge_पूर्णांकr_enable(काष्ठा xge_pdata *pdata);
व्योम xge_पूर्णांकr_disable(काष्ठा xge_pdata *pdata);

#पूर्ण_अगर  /* __XGENE_ENET_V2_RING_H__ */
