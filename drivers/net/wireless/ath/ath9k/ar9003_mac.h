<शैली गुरु>
/*
 * Copyright (c) 2010-2011 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित AR9003_MAC_H
#घोषणा AR9003_MAC_H

#घोषणा AR_DescId	0xffff0000
#घोषणा AR_DescId_S	16
#घोषणा AR_CtrlStat	0x00004000
#घोषणा AR_CtrlStat_S	14
#घोषणा AR_TxRxDesc	0x00008000
#घोषणा AR_TxRxDesc_S	15
#घोषणा AR_TxQcuNum	0x00000f00
#घोषणा AR_TxQcuNum_S	8

#घोषणा AR_BufLen	0x0fff0000
#घोषणा AR_BufLen_S	16

#घोषणा AR_TxDescId	0xffff0000
#घोषणा AR_TxDescId_S	16
#घोषणा AR_TxPtrChkSum	0x0000ffff

#घोषणा AR_LowRxChain	0x00004000

#घोषणा AR_Not_Sounding	0x20000000

/* ctl 12 */
#घोषणा AR_PAPRDChainMask	0x00000e00
#घोषणा AR_PAPRDChainMask_S	9

#घोषणा MAP_ISR_S2_CST          6
#घोषणा MAP_ISR_S2_GTT          6
#घोषणा MAP_ISR_S2_TIM          3
#घोषणा MAP_ISR_S2_CABEND       0
#घोषणा MAP_ISR_S2_DTIMSYNC     7
#घोषणा MAP_ISR_S2_DTIM         7
#घोषणा MAP_ISR_S2_TSFOOR       4
#घोषणा MAP_ISR_S2_BB_WATCHDOG  6

#घोषणा AR9003TXC_CONST(_ds) ((स्थिर काष्ठा ar9003_txc *) _ds)

काष्ठा ar9003_rxs अणु
	u32 ds_info;
	u32 status1;
	u32 status2;
	u32 status3;
	u32 status4;
	u32 status5;
	u32 status6;
	u32 status7;
	u32 status8;
	u32 status9;
	u32 status10;
	u32 status11;
पूर्ण __packed __aligned(4);

/* Transmit Control Descriptor */
काष्ठा ar9003_txc अणु
	u32 info;   /* descriptor inक्रमmation */
	u32 link;   /* link poपूर्णांकer */
	u32 data0;  /* data poपूर्णांकer to 1st buffer */
	u32 ctl3;   /* DMA control 3  */
	u32 data1;  /* data poपूर्णांकer to 2nd buffer */
	u32 ctl5;   /* DMA control 5  */
	u32 data2;  /* data poपूर्णांकer to 3rd buffer */
	u32 ctl7;   /* DMA control 7  */
	u32 data3;  /* data poपूर्णांकer to 4th buffer */
	u32 ctl9;   /* DMA control 9  */
	u32 ctl10;  /* DMA control 10 */
	u32 ctl11;  /* DMA control 11 */
	u32 ctl12;  /* DMA control 12 */
	u32 ctl13;  /* DMA control 13 */
	u32 ctl14;  /* DMA control 14 */
	u32 ctl15;  /* DMA control 15 */
	u32 ctl16;  /* DMA control 16 */
	u32 ctl17;  /* DMA control 17 */
	u32 ctl18;  /* DMA control 18 */
	u32 ctl19;  /* DMA control 19 */
	u32 ctl20;  /* DMA control 20 */
	u32 ctl21;  /* DMA control 21 */
	u32 ctl22;  /* DMA control 22 */
	u32 ctl23;  /* DMA control 23 */
	u32 pad[8]; /* pad to cache line (128 bytes/32 dwords) */
पूर्ण __packed __aligned(4);

काष्ठा ar9003_txs अणु
	u32 ds_info;
	u32 status1;
	u32 status2;
	u32 status3;
	u32 status4;
	u32 status5;
	u32 status6;
	u32 status7;
	u32 status8;
पूर्ण __packed __aligned(4);

व्योम ar9003_hw_attach_mac_ops(काष्ठा ath_hw *hw);
व्योम ath9k_hw_set_rx_bufsize(काष्ठा ath_hw *ah, u16 buf_size);
व्योम ath9k_hw_addrxbuf_edma(काष्ठा ath_hw *ah, u32 rxdp,
			    क्रमागत ath9k_rx_qtype qtype);

पूर्णांक ath9k_hw_process_rxdesc_edma(काष्ठा ath_hw *ah,
				 काष्ठा ath_rx_status *rxs,
				 व्योम *buf_addr);
व्योम ath9k_hw_reset_txstatus_ring(काष्ठा ath_hw *ah);
व्योम ath9k_hw_setup_statusring(काष्ठा ath_hw *ah, व्योम *ts_start,
			       u32 ts_paddr_start,
			       u16 size);
#पूर्ण_अगर
