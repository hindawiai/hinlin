<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Freescale QUICC Engine HDLC Device Driver
 *
 * Copyright 2014 Freescale Semiconductor Inc.
 */

#अगर_अघोषित _UCC_HDLC_H_
#घोषणा _UCC_HDLC_H_

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>

#समावेश <soc/fsl/qe/immap_qe.h>
#समावेश <soc/fsl/qe/qe.h>

#समावेश <soc/fsl/qe/ucc.h>
#समावेश <soc/fsl/qe/ucc_fast.h>

/* UCC HDLC event रेजिस्टर */
#घोषणा UCCE_HDLC_RX_EVENTS	\
(UCC_HDLC_UCCE_RXF | UCC_HDLC_UCCE_RXB | UCC_HDLC_UCCE_BSY)
#घोषणा UCCE_HDLC_TX_EVENTS	(UCC_HDLC_UCCE_TXB | UCC_HDLC_UCCE_TXE)

काष्ठा ucc_hdlc_param अणु
	__be16 riptr;
	__be16 tiptr;
	__be16 res0;
	__be16 mrblr;
	__be32 rstate;
	__be32 rbase;
	__be16 rbdstat;
	__be16 rbdlen;
	__be32 rdptr;
	__be32 tstate;
	__be32 tbase;
	__be16 tbdstat;
	__be16 tbdlen;
	__be32 tdptr;
	__be32 rbptr;
	__be32 tbptr;
	__be32 rcrc;
	__be32 res1;
	__be32 tcrc;
	__be32 res2;
	__be32 res3;
	__be32 c_mask;
	__be32 c_pres;
	__be16 disfc;
	__be16 crcec;
	__be16 abtsc;
	__be16 nmarc;
	__be32 max_cnt;
	__be16 mflr;
	__be16 rfthr;
	__be16 rfcnt;
	__be16 hmask;
	__be16 haddr1;
	__be16 haddr2;
	__be16 haddr3;
	__be16 haddr4;
	__be16 ts_पंचांगp;
	__be16 पंचांगp_mb;
पूर्ण;

काष्ठा ucc_hdlc_निजी अणु
	काष्ठा ucc_tdm	*utdm;
	काष्ठा ucc_tdm_info *ut_info;
	काष्ठा ucc_fast_निजी *uccf;
	काष्ठा device *dev;
	काष्ठा net_device *ndev;
	काष्ठा napi_काष्ठा napi;
	काष्ठा ucc_fast __iomem *uf_regs;	/* UCC Fast रेजिस्टरs */
	काष्ठा ucc_hdlc_param __iomem *ucc_pram;
	u16 tsa;
	bool hdlc_busy;
	bool loopback;
	bool hdlc_bus;

	u8 *tx_buffer;
	u8 *rx_buffer;
	dma_addr_t dma_tx_addr;
	dma_addr_t dma_rx_addr;

	काष्ठा qe_bd *tx_bd_base;
	काष्ठा qe_bd *rx_bd_base;
	dma_addr_t dma_tx_bd;
	dma_addr_t dma_rx_bd;
	काष्ठा qe_bd *curtx_bd;
	काष्ठा qe_bd *currx_bd;
	काष्ठा qe_bd *dirty_tx;
	u16 currx_bdnum;

	काष्ठा sk_buff **tx_skbuff;
	काष्ठा sk_buff **rx_skbuff;
	u16 skb_curtx;
	u16 skb_currx;
	अचिन्हित लघु skb_dirtytx;

	अचिन्हित लघु tx_ring_size;
	अचिन्हित लघु rx_ring_size;
	s32 ucc_pram_offset;

	अचिन्हित लघु encoding;
	अचिन्हित लघु parity;
	अचिन्हित लघु hmask;
	u32 घड़ीing;
	spinlock_t lock;	/* lock क्रम Tx BD and Tx buffer */
#अगर_घोषित CONFIG_PM
	काष्ठा ucc_hdlc_param *ucc_pram_bak;
	u32 gumr;
	u8 guemr;
	u32 cmxsi1cr_l, cmxsi1cr_h;
	u32 cmxsi1syr;
	u32 cmxucr[4];
#पूर्ण_अगर
पूर्ण;

#घोषणा TX_BD_RING_LEN	0x10
#घोषणा RX_BD_RING_LEN	0x20
#घोषणा RX_CLEAN_MAX	0x10
#घोषणा NUM_OF_BUF	4
#घोषणा MAX_RX_BUF_LENGTH	(48 * 0x20)
#घोषणा MAX_FRAME_LENGTH	(MAX_RX_BUF_LENGTH + 8)
#घोषणा ALIGNMENT_OF_UCC_HDLC_PRAM	64
#घोषणा SI_BANK_SIZE	128
#घोषणा MAX_HDLC_NUM	4
#घोषणा HDLC_HEAD_LEN	2
#घोषणा HDLC_CRC_SIZE	2
#घोषणा TX_RING_MOD_MASK(size) (size - 1)
#घोषणा RX_RING_MOD_MASK(size) (size - 1)

#घोषणा HDLC_HEAD_MASK		0x0000
#घोषणा DEFAULT_HDLC_HEAD	0xff44
#घोषणा DEFAULT_ADDR_MASK	0x00ff
#घोषणा DEFAULT_HDLC_ADDR	0x00ff

#घोषणा BMR_GBL			0x20000000
#घोषणा BMR_BIG_ENDIAN		0x10000000
#घोषणा CRC_16BIT_MASK		0x0000F0B8
#घोषणा CRC_16BIT_PRES		0x0000FFFF
#घोषणा DEFAULT_RFTHR		1

#घोषणा DEFAULT_PPP_HEAD    0xff03

#पूर्ण_अगर
