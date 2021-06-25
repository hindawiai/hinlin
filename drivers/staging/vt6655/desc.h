<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: desc.h
 *
 * Purpose:The header file of descriptor
 *
 * Revision History:
 *
 * Author: Tevin Chen
 *
 * Date: May 21, 1996
 *
 */

#अगर_अघोषित __DESC_H__
#घोषणा __DESC_H__

#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश "linux/ieee80211.h"

#घोषणा B_OWNED_BY_CHIP     1
#घोषणा B_OWNED_BY_HOST     0

/* Bits in the RSR रेजिस्टर */
#घोषणा RSR_ADDRBROAD       0x80
#घोषणा RSR_ADDRMULTI       0x40
#घोषणा RSR_ADDRUNI         0x00
#घोषणा RSR_IVLDTYP         0x20
#घोषणा RSR_IVLDLEN         0x10        /* invalid len (> 2312 byte) */
#घोषणा RSR_BSSIDOK         0x08
#घोषणा RSR_CRCOK           0x04
#घोषणा RSR_BCNSSIDOK       0x02
#घोषणा RSR_ADDROK          0x01

/* Bits in the new RSR रेजिस्टर */
#घोषणा NEWRSR_DECRYPTOK    0x10
#घोषणा NEWRSR_CFPIND       0x08
#घोषणा NEWRSR_HWUTSF       0x04
#घोषणा NEWRSR_BCNHITAID    0x02
#घोषणा NEWRSR_BCNHITAID0   0x01

/* Bits in the TSR0 रेजिस्टर */
#घोषणा TSR0_PWRSTS1_2      0xC0
#घोषणा TSR0_PWRSTS7        0x20
#घोषणा TSR0_NCR            0x1F

/* Bits in the TSR1 रेजिस्टर */
#घोषणा TSR1_TERR           0x80
#घोषणा TSR1_PWRSTS4_6      0x70
#घोषणा TSR1_RETRYTMO       0x08
#घोषणा TSR1_TMO            0x04
#घोषणा TSR1_PWRSTS3        0x02
#घोषणा ACK_DATA            0x01

/* Bits in the TCR रेजिस्टर */
#घोषणा EDMSDU              0x04        /* end of sdu */
#घोषणा TCR_EDP             0x02        /* end of packet */
#घोषणा TCR_STP             0x01        /* start of packet */

/* max transmit or receive buffer size */
#घोषणा CB_MAX_BUF_SIZE     2900U
					/* NOTE: must be multiple of 4 */
#घोषणा CB_MAX_TX_BUF_SIZE          CB_MAX_BUF_SIZE
#घोषणा CB_MAX_RX_BUF_SIZE_NORMAL   CB_MAX_BUF_SIZE

#घोषणा CB_BEACON_BUF_SIZE  512U

#घोषणा CB_MAX_RX_DESC      128
#घोषणा CB_MIN_RX_DESC      16
#घोषणा CB_MAX_TX_DESC      64
#घोषणा CB_MIN_TX_DESC      16

#घोषणा CB_MAX_RECEIVED_PACKETS     16
				/*
				 * limit our receive routine to indicating
				 * this many at a समय क्रम 2 reasons:
				 * 1. driver flow control to protocol layer
				 * 2. limit the समय used in ISR routine
				 */

#घोषणा CB_EXTRA_RD_NUM     32
#घोषणा CB_RD_NUM           32
#घोषणा CB_TD_NUM           32

/*
 * max number of physical segments in a single NDIS packet. Above this
 * threshold, the packet is copied पूर्णांकo a single physically contiguous buffer
 */
#घोषणा CB_MAX_SEGMENT      4

#घोषणा CB_MIN_MAP_REG_NUM  4
#घोषणा CB_MAX_MAP_REG_NUM  CB_MAX_TX_DESC

#घोषणा CB_PROTOCOL_RESERVED_SECTION    16

/*
 * अगर retrys excess 15 बार , tx will पात, and अगर tx fअगरo underflow,
 * tx will fail, we should try to resend it
 */
#घोषणा CB_MAX_TX_ABORT_RETRY   3

/* WMAC definition FIFO Control */
#घोषणा FIFOCTL_AUTO_FB_1   0x1000
#घोषणा FIFOCTL_AUTO_FB_0   0x0800
#घोषणा FIFOCTL_GRPACK      0x0400
#घोषणा FIFOCTL_11GA        0x0300
#घोषणा FIFOCTL_11GB        0x0200
#घोषणा FIFOCTL_11B         0x0100
#घोषणा FIFOCTL_11A         0x0000
#घोषणा FIFOCTL_RTS         0x0080
#घोषणा FIFOCTL_ISDMA0      0x0040
#घोषणा FIFOCTL_GENINT      0x0020
#घोषणा FIFOCTL_TMOEN       0x0010
#घोषणा FIFOCTL_LRETRY      0x0008
#घोषणा FIFOCTL_CRCDIS      0x0004
#घोषणा FIFOCTL_NEEDACK     0x0002
#घोषणा FIFOCTL_LHEAD       0x0001

/* WMAC definition Frag Control */
#घोषणा FRAGCTL_AES         0x0300
#घोषणा FRAGCTL_TKIP        0x0200
#घोषणा FRAGCTL_LEGACY      0x0100
#घोषणा FRAGCTL_NONENCRYPT  0x0000
#घोषणा FRAGCTL_ENDFRAG     0x0003
#घोषणा FRAGCTL_MIDFRAG     0x0002
#घोषणा FRAGCTL_STAFRAG     0x0001
#घोषणा FRAGCTL_NONFRAG     0x0000

#घोषणा TYPE_TXDMA0     0
#घोषणा TYPE_AC0DMA     1
#घोषणा TYPE_ATIMDMA    2
#घोषणा TYPE_SYNCDMA    3
#घोषणा TYPE_MAXTD      2

#घोषणा TYPE_BEACONDMA  4

#घोषणा TYPE_RXDMA0     0
#घोषणा TYPE_RXDMA1     1
#घोषणा TYPE_MAXRD      2

/* TD_INFO flags control bit */
#घोषणा TD_FLAGS_NETIF_SKB      0x01    /* check अगर need release skb */
/* check अगर called from निजी skb (hostap) */
#घोषणा TD_FLAGS_PRIV_SKB       0x02
#घोषणा TD_FLAGS_PS_RETRY       0x04    /* check अगर PS STA frame re-transmit */

/*
 * ref_sk_buff is used क्रम mapping the skb काष्ठाure between pre-built
 * driver-obj & running kernel. Since dअगरferent kernel version (2.4x) may
 * change skb काष्ठाure, i.e. pre-built driver-obj may link to older skb that
 * leads error.
 */

काष्ठा vnt_rd_info अणु
	काष्ठा sk_buff *skb;
	dma_addr_t  skb_dma;
पूर्ण;

काष्ठा vnt_rdes0 अणु
	अस्थिर __le16 res_count;
#अगर_घोषित __BIG_ENDIAN
	जोड़ अणु
		अस्थिर u16 f15_reserved;
		काष्ठा अणु
			अस्थिर u8 f8_reserved1;
			अस्थिर u8 owner:1;
			अस्थिर u8 f7_reserved:7;
		पूर्ण __packed;
	पूर्ण __packed;
#अन्यथा
	u16 f15_reserved:15;
	u16 owner:1;
#पूर्ण_अगर
पूर्ण __packed;

काष्ठा vnt_rdes1 अणु
	__le16 req_count;
	u16 reserved;
पूर्ण __packed;

/* Rx descriptor*/
काष्ठा vnt_rx_desc अणु
	अस्थिर काष्ठा vnt_rdes0 rd0;
	अस्थिर काष्ठा vnt_rdes1 rd1;
	अस्थिर __le32 buff_addr;
	अस्थिर __le32 next_desc;
	काष्ठा vnt_rx_desc *next __aligned(8);
	काष्ठा vnt_rd_info *rd_info __aligned(8);
पूर्ण __packed;

काष्ठा vnt_tdes0 अणु
	अस्थिर u8 tsr0;
	अस्थिर u8 tsr1;
#अगर_घोषित __BIG_ENDIAN
	जोड़ अणु
		अस्थिर u16 f15_txसमय;
		काष्ठा अणु
			अस्थिर u8 f8_reserved;
			अस्थिर u8 owner:1;
			अस्थिर u8 f7_reserved:7;
		पूर्ण __packed;
	पूर्ण __packed;
#अन्यथा
	अस्थिर u16 f15_txसमय:15;
	अस्थिर u16 owner:1;
#पूर्ण_अगर
पूर्ण __packed;

काष्ठा vnt_tdes1 अणु
	अस्थिर __le16 req_count;
	अस्थिर u8 tcr;
	अस्थिर u8 reserved;
पूर्ण __packed;

काष्ठा vnt_td_info अणु
	व्योम *mic_hdr;
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *buf;
	dma_addr_t buf_dma;
	u16 req_count;
	u8 flags;
पूर्ण;

/* transmit descriptor */
काष्ठा vnt_tx_desc अणु
	अस्थिर काष्ठा vnt_tdes0 td0;
	अस्थिर काष्ठा vnt_tdes1 td1;
	अस्थिर __le32 buff_addr;
	अस्थिर __le32 next_desc;
	काष्ठा vnt_tx_desc *next __aligned(8);
	काष्ठा vnt_td_info *td_info __aligned(8);
पूर्ण __packed;

/* Length, Service, and Signal fields of Phy क्रम Tx */
काष्ठा vnt_phy_field अणु
	u8 संकेत;
	u8 service;
	__le16 len;
पूर्ण __packed;

जोड़ vnt_phy_field_swap अणु
	काष्ठा vnt_phy_field field_पढ़ो;
	u16 swap[2];
	u32 field_ग_लिखो;
पूर्ण;

#पूर्ण_अगर /* __DESC_H__ */
