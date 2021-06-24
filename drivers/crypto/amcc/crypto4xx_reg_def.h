<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * AMCC SoC PPC4xx Crypto Driver
 *
 * Copyright (c) 2008 Applied Micro Circuits Corporation.
 * All rights reserved. James Hsiao <jhsiao@amcc.com>
 *
 * This filr defines the रेजिस्टर set क्रम Security Subप्रणाली
 */

#अगर_अघोषित __CRYPTO4XX_REG_DEF_H__
#घोषणा __CRYPTO4XX_REG_DEF_H__

/* CRYPTO4XX Register offset */
#घोषणा CRYPTO4XX_DESCRIPTOR			0x00000000
#घोषणा CRYPTO4XX_CTRL_STAT			0x00000000
#घोषणा CRYPTO4XX_SOURCE			0x00000004
#घोषणा CRYPTO4XX_DEST				0x00000008
#घोषणा CRYPTO4XX_SA				0x0000000C
#घोषणा CRYPTO4XX_SA_LENGTH			0x00000010
#घोषणा CRYPTO4XX_LENGTH			0x00000014

#घोषणा CRYPTO4XX_PE_DMA_CFG			0x00000040
#घोषणा CRYPTO4XX_PE_DMA_STAT			0x00000044
#घोषणा CRYPTO4XX_PDR_BASE			0x00000048
#घोषणा CRYPTO4XX_RDR_BASE			0x0000004c
#घोषणा CRYPTO4XX_RING_SIZE			0x00000050
#घोषणा CRYPTO4XX_RING_CTRL			0x00000054
#घोषणा CRYPTO4XX_INT_RING_STAT			0x00000058
#घोषणा CRYPTO4XX_EXT_RING_STAT			0x0000005c
#घोषणा CRYPTO4XX_IO_THRESHOLD			0x00000060
#घोषणा CRYPTO4XX_GATH_RING_BASE		0x00000064
#घोषणा CRYPTO4XX_SCAT_RING_BASE		0x00000068
#घोषणा CRYPTO4XX_PART_RING_SIZE		0x0000006c
#घोषणा CRYPTO4XX_PART_RING_CFG		        0x00000070

#घोषणा CRYPTO4XX_PDR_BASE_UADDR		0x00000080
#घोषणा CRYPTO4XX_RDR_BASE_UADDR		0x00000084
#घोषणा CRYPTO4XX_PKT_SRC_UADDR			0x00000088
#घोषणा CRYPTO4XX_PKT_DEST_UADDR		0x0000008c
#घोषणा CRYPTO4XX_SA_UADDR			0x00000090
#घोषणा CRYPTO4XX_GATH_RING_BASE_UADDR		0x000000A0
#घोषणा CRYPTO4XX_SCAT_RING_BASE_UADDR		0x000000A4

#घोषणा CRYPTO4XX_SEQ_RD			0x00000408
#घोषणा CRYPTO4XX_SEQ_MASK_RD			0x0000040C

#घोषणा CRYPTO4XX_SA_CMD_0			0x00010600
#घोषणा CRYPTO4XX_SA_CMD_1			0x00010604

#घोषणा CRYPTO4XX_STATE_PTR			0x000106dc
#घोषणा CRYPTO4XX_STATE_IV			0x00010700
#घोषणा CRYPTO4XX_STATE_HASH_BYTE_CNT_0		0x00010710
#घोषणा CRYPTO4XX_STATE_HASH_BYTE_CNT_1		0x00010714

#घोषणा CRYPTO4XX_STATE_IDIGEST_0		0x00010718
#घोषणा CRYPTO4XX_STATE_IDIGEST_1		0x0001071c

#घोषणा CRYPTO4XX_DATA_IN			0x00018000
#घोषणा CRYPTO4XX_DATA_OUT			0x0001c000

#घोषणा CRYPTO4XX_INT_UNMASK_STAT		0x000500a0
#घोषणा CRYPTO4XX_INT_MASK_STAT			0x000500a4
#घोषणा CRYPTO4XX_INT_CLR			0x000500a4
#घोषणा CRYPTO4XX_INT_EN			0x000500a8

#घोषणा CRYPTO4XX_INT_PKA			0x00000002
#घोषणा CRYPTO4XX_INT_PDR_DONE			0x00008000
#घोषणा CRYPTO4XX_INT_MA_WR_ERR			0x00020000
#घोषणा CRYPTO4XX_INT_MA_RD_ERR			0x00010000
#घोषणा CRYPTO4XX_INT_PE_ERR			0x00000200
#घोषणा CRYPTO4XX_INT_USER_DMA_ERR		0x00000040
#घोषणा CRYPTO4XX_INT_SLAVE_ERR			0x00000010
#घोषणा CRYPTO4XX_INT_MASTER_ERR		0x00000008
#घोषणा CRYPTO4XX_INT_ERROR			0x00030258

#घोषणा CRYPTO4XX_INT_CFG			0x000500ac
#घोषणा CRYPTO4XX_INT_DESCR_RD			0x000500b0
#घोषणा CRYPTO4XX_INT_DESCR_CNT			0x000500b4
#घोषणा CRYPTO4XX_INT_TIMEOUT_CNT		0x000500b8

#घोषणा CRYPTO4XX_DEVICE_CTRL			0x00060080
#घोषणा CRYPTO4XX_DEVICE_ID			0x00060084
#घोषणा CRYPTO4XX_DEVICE_INFO			0x00060088
#घोषणा CRYPTO4XX_DMA_USER_SRC			0x00060094
#घोषणा CRYPTO4XX_DMA_USER_DEST			0x00060098
#घोषणा CRYPTO4XX_DMA_USER_CMD			0x0006009C

#घोषणा CRYPTO4XX_DMA_CFG	        	0x000600d4
#घोषणा CRYPTO4XX_BYTE_ORDER_CFG 		0x000600d8
#घोषणा CRYPTO4XX_ENDIAN_CFG			0x000600d8

#घोषणा CRYPTO4XX_PRNG_STAT			0x00070000
#घोषणा CRYPTO4XX_PRNG_STAT_BUSY		0x1
#घोषणा CRYPTO4XX_PRNG_CTRL			0x00070004
#घोषणा CRYPTO4XX_PRNG_SEED_L			0x00070008
#घोषणा CRYPTO4XX_PRNG_SEED_H			0x0007000c

#घोषणा CRYPTO4XX_PRNG_RES_0			0x00070020
#घोषणा CRYPTO4XX_PRNG_RES_1			0x00070024
#घोषणा CRYPTO4XX_PRNG_RES_2			0x00070028
#घोषणा CRYPTO4XX_PRNG_RES_3			0x0007002C

#घोषणा CRYPTO4XX_PRNG_LFSR_L			0x00070030
#घोषणा CRYPTO4XX_PRNG_LFSR_H			0x00070034

/*
 * Initialize CRYPTO ENGINE रेजिस्टरs, and memory bases.
 */
#घोषणा PPC4XX_PDR_POLL				0x3ff
#घोषणा PPC4XX_OUTPUT_THRESHOLD			2
#घोषणा PPC4XX_INPUT_THRESHOLD			2
#घोषणा PPC4XX_PD_SIZE				6
#घोषणा PPC4XX_CTX_DONE_INT			0x2000
#घोषणा PPC4XX_PD_DONE_INT			0x8000
#घोषणा PPC4XX_TMO_ERR_INT			0x40000
#घोषणा PPC4XX_BYTE_ORDER			0x22222
#घोषणा PPC4XX_INTERRUPT_CLR			0x3ffff
#घोषणा PPC4XX_PRNG_CTRL_AUTO_EN		0x3
#घोषणा PPC4XX_DC_3DES_EN			1
#घोषणा PPC4XX_TRNG_EN				0x00020000
#घोषणा PPC4XX_INT_DESCR_CNT			7
#घोषणा PPC4XX_INT_TIMEOUT_CNT			0
#घोषणा PPC4XX_INT_TIMEOUT_CNT_REVB		0x3FF
#घोषणा PPC4XX_INT_CFG				1
/*
 * all follow define are ad hoc
 */
#घोषणा PPC4XX_RING_RETRY			100
#घोषणा PPC4XX_RING_POLL			100
#घोषणा PPC4XX_SDR_SIZE				PPC4XX_NUM_SD
#घोषणा PPC4XX_GDR_SIZE				PPC4XX_NUM_GD

/*
  * Generic Security Association (SA) with all possible fields. These will
 * never likely used except क्रम reference purpose. These काष्ठाure क्रमmat
 * can be not changed as the hardware expects them to be layout as defined.
 * Field can be हटाओd or reduced but ordering can not be changed.
 */
#घोषणा CRYPTO4XX_DMA_CFG_OFFSET		0x40
जोड़ ce_pe_dma_cfg अणु
	काष्ठा अणु
		u32 rsv:7;
		u32 dir_host:1;
		u32 rsv1:2;
		u32 bo_td_en:1;
		u32 dis_pdr_upd:1;
		u32 bo_sgpd_en:1;
		u32 bo_data_en:1;
		u32 bo_sa_en:1;
		u32 bo_pd_en:1;
		u32 rsv2:4;
		u32 dynamic_sa_en:1;
		u32 pdr_mode:2;
		u32 pe_mode:1;
		u32 rsv3:5;
		u32 reset_sg:1;
		u32 reset_pdr:1;
		u32 reset_pe:1;
	पूर्ण bf;
    u32 w;
पूर्ण __attribute__((packed));

#घोषणा CRYPTO4XX_PDR_BASE_OFFSET		0x48
#घोषणा CRYPTO4XX_RDR_BASE_OFFSET		0x4c
#घोषणा CRYPTO4XX_RING_SIZE_OFFSET		0x50
जोड़ ce_ring_size अणु
	काष्ठा अणु
		u32 ring_offset:16;
		u32 rsv:6;
		u32 ring_size:10;
	पूर्ण bf;
    u32 w;
पूर्ण __attribute__((packed));

#घोषणा CRYPTO4XX_RING_CONTROL_OFFSET		0x54
जोड़ ce_ring_control अणु
	काष्ठा अणु
		u32 continuous:1;
		u32 rsv:5;
		u32 ring_retry_भागisor:10;
		u32 rsv1:4;
		u32 ring_poll_भागisor:10;
	पूर्ण bf;
    u32 w;
पूर्ण __attribute__((packed));

#घोषणा CRYPTO4XX_IO_THRESHOLD_OFFSET		0x60
जोड़ ce_io_threshold अणु
	काष्ठा अणु
		u32 rsv:6;
		u32 output_threshold:10;
		u32 rsv1:6;
		u32 input_threshold:10;
	पूर्ण bf;
    u32 w;
पूर्ण __attribute__((packed));

#घोषणा CRYPTO4XX_GATHER_RING_BASE_OFFSET	0x64
#घोषणा CRYPTO4XX_SCATTER_RING_BASE_OFFSET	0x68

जोड़ ce_part_ring_size  अणु
	काष्ठा अणु
		u32 sdr_size:16;
		u32 gdr_size:16;
	पूर्ण bf;
    u32 w;
पूर्ण __attribute__((packed));

#घोषणा MAX_BURST_SIZE_32			0
#घोषणा MAX_BURST_SIZE_64			1
#घोषणा MAX_BURST_SIZE_128			2
#घोषणा MAX_BURST_SIZE_256			3

/* gather descriptor control length */
काष्ठा gd_ctl_len अणु
	u32 len:16;
	u32 rsv:14;
	u32 करोne:1;
	u32 पढ़ोy:1;
पूर्ण __attribute__((packed));

काष्ठा ce_gd अणु
	u32 ptr;
	काष्ठा gd_ctl_len ctl_len;
पूर्ण __attribute__((packed));

काष्ठा sd_ctl अणु
	u32 ctl:30;
	u32 करोne:1;
	u32 rdy:1;
पूर्ण __attribute__((packed));

काष्ठा ce_sd अणु
    u32 ptr;
	काष्ठा sd_ctl ctl;
पूर्ण __attribute__((packed));

#घोषणा PD_PAD_CTL_32	0x10
#घोषणा PD_PAD_CTL_64	0x20
#घोषणा PD_PAD_CTL_128	0x40
#घोषणा PD_PAD_CTL_256	0x80
जोड़ ce_pd_ctl अणु
	काष्ठा अणु
		u32 pd_pad_ctl:8;
		u32 status:8;
		u32 next_hdr:8;
		u32 rsv:2;
		u32 cached_sa:1;
		u32 hash_final:1;
		u32 init_arc4:1;
		u32 rsv1:1;
		u32 pe_करोne:1;
		u32 host_पढ़ोy:1;
	पूर्ण bf;
	u32 w;
पूर्ण __attribute__((packed));
#घोषणा PD_CTL_HASH_FINAL	BIT(4)
#घोषणा PD_CTL_PE_DONE		BIT(1)
#घोषणा PD_CTL_HOST_READY	BIT(0)

जोड़ ce_pd_ctl_len अणु
	काष्ठा अणु
		u32 bypass:8;
		u32 pe_करोne:1;
		u32 host_पढ़ोy:1;
		u32 rsv:2;
		u32 pkt_len:20;
	पूर्ण bf;
	u32 w;
पूर्ण __attribute__((packed));

काष्ठा ce_pd अणु
	जोड़ ce_pd_ctl   pd_ctl;
	u32 src;
	u32 dest;
	u32 sa;                 /* get from ctx->sa_dma_addr */
	u32 sa_len;             /* only अगर dynamic sa is used */
	जोड़ ce_pd_ctl_len pd_ctl_len;

पूर्ण __attribute__((packed));
#पूर्ण_अगर
