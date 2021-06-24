<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014-2015 MediaTek Inc.
 * Author: Chaotian.Jing <chaotian.jing@mediatek.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/ioport.h>
#समावेश <linux/irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/reset.h>

#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/core.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/sd.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/slot-gpपन.स>

#समावेश "cqhci.h"

#घोषणा MAX_BD_NUM          1024
#घोषणा MSDC_NR_CLOCKS      3

/*--------------------------------------------------------------------------*/
/* Common Definition                                                        */
/*--------------------------------------------------------------------------*/
#घोषणा MSDC_BUS_1BITS          0x0
#घोषणा MSDC_BUS_4BITS          0x1
#घोषणा MSDC_BUS_8BITS          0x2

#घोषणा MSDC_BURST_64B          0x6

/*--------------------------------------------------------------------------*/
/* Register Offset                                                          */
/*--------------------------------------------------------------------------*/
#घोषणा MSDC_CFG         0x0
#घोषणा MSDC_IOCON       0x04
#घोषणा MSDC_PS          0x08
#घोषणा MSDC_INT         0x0c
#घोषणा MSDC_INTEN       0x10
#घोषणा MSDC_FIFOCS      0x14
#घोषणा SDC_CFG          0x30
#घोषणा SDC_CMD          0x34
#घोषणा SDC_ARG          0x38
#घोषणा SDC_STS          0x3c
#घोषणा SDC_RESP0        0x40
#घोषणा SDC_RESP1        0x44
#घोषणा SDC_RESP2        0x48
#घोषणा SDC_RESP3        0x4c
#घोषणा SDC_BLK_NUM      0x50
#घोषणा SDC_ADV_CFG0     0x64
#घोषणा EMMC_IOCON       0x7c
#घोषणा SDC_ACMD_RESP    0x80
#घोषणा DMA_SA_H4BIT     0x8c
#घोषणा MSDC_DMA_SA      0x90
#घोषणा MSDC_DMA_CTRL    0x98
#घोषणा MSDC_DMA_CFG     0x9c
#घोषणा MSDC_PATCH_BIT   0xb0
#घोषणा MSDC_PATCH_BIT1  0xb4
#घोषणा MSDC_PATCH_BIT2  0xb8
#घोषणा MSDC_PAD_TUNE    0xec
#घोषणा MSDC_PAD_TUNE0   0xf0
#घोषणा PAD_DS_TUNE      0x188
#घोषणा PAD_CMD_TUNE     0x18c
#घोषणा EMMC51_CFG0	 0x204
#घोषणा EMMC50_CFG0      0x208
#घोषणा EMMC50_CFG1      0x20c
#घोषणा EMMC50_CFG3      0x220
#घोषणा SDC_FIFO_CFG     0x228
#घोषणा CQHCI_SETTING	 0x7fc

/*--------------------------------------------------------------------------*/
/* Top Pad Register Offset                                                  */
/*--------------------------------------------------------------------------*/
#घोषणा EMMC_TOP_CONTROL	0x00
#घोषणा EMMC_TOP_CMD		0x04
#घोषणा EMMC50_PAD_DS_TUNE	0x0c

/*--------------------------------------------------------------------------*/
/* Register Mask                                                            */
/*--------------------------------------------------------------------------*/

/* MSDC_CFG mask */
#घोषणा MSDC_CFG_MODE           (0x1 << 0)	/* RW */
#घोषणा MSDC_CFG_CKPDN          (0x1 << 1)	/* RW */
#घोषणा MSDC_CFG_RST            (0x1 << 2)	/* RW */
#घोषणा MSDC_CFG_PIO            (0x1 << 3)	/* RW */
#घोषणा MSDC_CFG_CKDRVEN        (0x1 << 4)	/* RW */
#घोषणा MSDC_CFG_BV18SDT        (0x1 << 5)	/* RW */
#घोषणा MSDC_CFG_BV18PSS        (0x1 << 6)	/* R  */
#घोषणा MSDC_CFG_CKSTB          (0x1 << 7)	/* R  */
#घोषणा MSDC_CFG_CKDIV          (0xff << 8)	/* RW */
#घोषणा MSDC_CFG_CKMOD          (0x3 << 16)	/* RW */
#घोषणा MSDC_CFG_HS400_CK_MODE  (0x1 << 18)	/* RW */
#घोषणा MSDC_CFG_HS400_CK_MODE_EXTRA  (0x1 << 22)	/* RW */
#घोषणा MSDC_CFG_CKDIV_EXTRA    (0xfff << 8)	/* RW */
#घोषणा MSDC_CFG_CKMOD_EXTRA    (0x3 << 20)	/* RW */

/* MSDC_IOCON mask */
#घोषणा MSDC_IOCON_SDR104CKS    (0x1 << 0)	/* RW */
#घोषणा MSDC_IOCON_RSPL         (0x1 << 1)	/* RW */
#घोषणा MSDC_IOCON_DSPL         (0x1 << 2)	/* RW */
#घोषणा MSDC_IOCON_DDLSEL       (0x1 << 3)	/* RW */
#घोषणा MSDC_IOCON_DDR50CKD     (0x1 << 4)	/* RW */
#घोषणा MSDC_IOCON_DSPLSEL      (0x1 << 5)	/* RW */
#घोषणा MSDC_IOCON_W_DSPL       (0x1 << 8)	/* RW */
#घोषणा MSDC_IOCON_D0SPL        (0x1 << 16)	/* RW */
#घोषणा MSDC_IOCON_D1SPL        (0x1 << 17)	/* RW */
#घोषणा MSDC_IOCON_D2SPL        (0x1 << 18)	/* RW */
#घोषणा MSDC_IOCON_D3SPL        (0x1 << 19)	/* RW */
#घोषणा MSDC_IOCON_D4SPL        (0x1 << 20)	/* RW */
#घोषणा MSDC_IOCON_D5SPL        (0x1 << 21)	/* RW */
#घोषणा MSDC_IOCON_D6SPL        (0x1 << 22)	/* RW */
#घोषणा MSDC_IOCON_D7SPL        (0x1 << 23)	/* RW */
#घोषणा MSDC_IOCON_RISCSZ       (0x3 << 24)	/* RW */

/* MSDC_PS mask */
#घोषणा MSDC_PS_CDEN            (0x1 << 0)	/* RW */
#घोषणा MSDC_PS_CDSTS           (0x1 << 1)	/* R  */
#घोषणा MSDC_PS_CDDEBOUNCE      (0xf << 12)	/* RW */
#घोषणा MSDC_PS_DAT             (0xff << 16)	/* R  */
#घोषणा MSDC_PS_DATA1           (0x1 << 17)	/* R  */
#घोषणा MSDC_PS_CMD             (0x1 << 24)	/* R  */
#घोषणा MSDC_PS_WP              (0x1 << 31)	/* R  */

/* MSDC_INT mask */
#घोषणा MSDC_INT_MMCIRQ         (0x1 << 0)	/* W1C */
#घोषणा MSDC_INT_CDSC           (0x1 << 1)	/* W1C */
#घोषणा MSDC_INT_ACMDRDY        (0x1 << 3)	/* W1C */
#घोषणा MSDC_INT_ACMDTMO        (0x1 << 4)	/* W1C */
#घोषणा MSDC_INT_ACMDCRCERR     (0x1 << 5)	/* W1C */
#घोषणा MSDC_INT_DMAQ_EMPTY     (0x1 << 6)	/* W1C */
#घोषणा MSDC_INT_SDIOIRQ        (0x1 << 7)	/* W1C */
#घोषणा MSDC_INT_CMDRDY         (0x1 << 8)	/* W1C */
#घोषणा MSDC_INT_CMDTMO         (0x1 << 9)	/* W1C */
#घोषणा MSDC_INT_RSPCRCERR      (0x1 << 10)	/* W1C */
#घोषणा MSDC_INT_CSTA           (0x1 << 11)	/* R */
#घोषणा MSDC_INT_XFER_COMPL     (0x1 << 12)	/* W1C */
#घोषणा MSDC_INT_DXFER_DONE     (0x1 << 13)	/* W1C */
#घोषणा MSDC_INT_DATTMO         (0x1 << 14)	/* W1C */
#घोषणा MSDC_INT_DATCRCERR      (0x1 << 15)	/* W1C */
#घोषणा MSDC_INT_ACMD19_DONE    (0x1 << 16)	/* W1C */
#घोषणा MSDC_INT_DMA_BDCSERR    (0x1 << 17)	/* W1C */
#घोषणा MSDC_INT_DMA_GPDCSERR   (0x1 << 18)	/* W1C */
#घोषणा MSDC_INT_DMA_PROTECT    (0x1 << 19)	/* W1C */
#घोषणा MSDC_INT_CMDQ           (0x1 << 28)	/* W1C */

/* MSDC_INTEN mask */
#घोषणा MSDC_INTEN_MMCIRQ       (0x1 << 0)	/* RW */
#घोषणा MSDC_INTEN_CDSC         (0x1 << 1)	/* RW */
#घोषणा MSDC_INTEN_ACMDRDY      (0x1 << 3)	/* RW */
#घोषणा MSDC_INTEN_ACMDTMO      (0x1 << 4)	/* RW */
#घोषणा MSDC_INTEN_ACMDCRCERR   (0x1 << 5)	/* RW */
#घोषणा MSDC_INTEN_DMAQ_EMPTY   (0x1 << 6)	/* RW */
#घोषणा MSDC_INTEN_SDIOIRQ      (0x1 << 7)	/* RW */
#घोषणा MSDC_INTEN_CMDRDY       (0x1 << 8)	/* RW */
#घोषणा MSDC_INTEN_CMDTMO       (0x1 << 9)	/* RW */
#घोषणा MSDC_INTEN_RSPCRCERR    (0x1 << 10)	/* RW */
#घोषणा MSDC_INTEN_CSTA         (0x1 << 11)	/* RW */
#घोषणा MSDC_INTEN_XFER_COMPL   (0x1 << 12)	/* RW */
#घोषणा MSDC_INTEN_DXFER_DONE   (0x1 << 13)	/* RW */
#घोषणा MSDC_INTEN_DATTMO       (0x1 << 14)	/* RW */
#घोषणा MSDC_INTEN_DATCRCERR    (0x1 << 15)	/* RW */
#घोषणा MSDC_INTEN_ACMD19_DONE  (0x1 << 16)	/* RW */
#घोषणा MSDC_INTEN_DMA_BDCSERR  (0x1 << 17)	/* RW */
#घोषणा MSDC_INTEN_DMA_GPDCSERR (0x1 << 18)	/* RW */
#घोषणा MSDC_INTEN_DMA_PROTECT  (0x1 << 19)	/* RW */

/* MSDC_FIFOCS mask */
#घोषणा MSDC_FIFOCS_RXCNT       (0xff << 0)	/* R */
#घोषणा MSDC_FIFOCS_TXCNT       (0xff << 16)	/* R */
#घोषणा MSDC_FIFOCS_CLR         (0x1 << 31)	/* RW */

/* SDC_CFG mask */
#घोषणा SDC_CFG_SDIOINTWKUP     (0x1 << 0)	/* RW */
#घोषणा SDC_CFG_INSWKUP         (0x1 << 1)	/* RW */
#घोषणा SDC_CFG_WRDTOC          (0x1fff  << 2)  /* RW */
#घोषणा SDC_CFG_BUSWIDTH        (0x3 << 16)	/* RW */
#घोषणा SDC_CFG_SDIO            (0x1 << 19)	/* RW */
#घोषणा SDC_CFG_SDIOIDE         (0x1 << 20)	/* RW */
#घोषणा SDC_CFG_INTATGAP        (0x1 << 21)	/* RW */
#घोषणा SDC_CFG_DTOC            (0xff << 24)	/* RW */

/* SDC_STS mask */
#घोषणा SDC_STS_SDCBUSY         (0x1 << 0)	/* RW */
#घोषणा SDC_STS_CMDBUSY         (0x1 << 1)	/* RW */
#घोषणा SDC_STS_SWR_COMPL       (0x1 << 31)	/* RW */

#घोषणा SDC_DAT1_IRQ_TRIGGER	(0x1 << 19)	/* RW */
/* SDC_ADV_CFG0 mask */
#घोषणा SDC_RX_ENHANCE_EN	(0x1 << 20)	/* RW */

/* DMA_SA_H4BIT mask */
#घोषणा DMA_ADDR_HIGH_4BIT      (0xf << 0)      /* RW */

/* MSDC_DMA_CTRL mask */
#घोषणा MSDC_DMA_CTRL_START     (0x1 << 0)	/* W */
#घोषणा MSDC_DMA_CTRL_STOP      (0x1 << 1)	/* W */
#घोषणा MSDC_DMA_CTRL_RESUME    (0x1 << 2)	/* W */
#घोषणा MSDC_DMA_CTRL_MODE      (0x1 << 8)	/* RW */
#घोषणा MSDC_DMA_CTRL_LASTBUF   (0x1 << 10)	/* RW */
#घोषणा MSDC_DMA_CTRL_BRUSTSZ   (0x7 << 12)	/* RW */

/* MSDC_DMA_CFG mask */
#घोषणा MSDC_DMA_CFG_STS        (0x1 << 0)	/* R */
#घोषणा MSDC_DMA_CFG_DECSEN     (0x1 << 1)	/* RW */
#घोषणा MSDC_DMA_CFG_AHBHPROT2  (0x2 << 8)	/* RW */
#घोषणा MSDC_DMA_CFG_ACTIVEEN   (0x2 << 12)	/* RW */
#घोषणा MSDC_DMA_CFG_CS12B16B   (0x1 << 16)	/* RW */

/* MSDC_PATCH_BIT mask */
#घोषणा MSDC_PATCH_BIT_ODDSUPP    (0x1 <<  1)	/* RW */
#घोषणा MSDC_INT_DAT_LATCH_CK_SEL (0x7 <<  7)
#घोषणा MSDC_CKGEN_MSDC_DLY_SEL   (0x1f << 10)
#घोषणा MSDC_PATCH_BIT_IODSSEL    (0x1 << 16)	/* RW */
#घोषणा MSDC_PATCH_BIT_IOINTSEL   (0x1 << 17)	/* RW */
#घोषणा MSDC_PATCH_BIT_BUSYDLY    (0xf << 18)	/* RW */
#घोषणा MSDC_PATCH_BIT_WDOD       (0xf << 22)	/* RW */
#घोषणा MSDC_PATCH_BIT_IDRTSEL    (0x1 << 26)	/* RW */
#घोषणा MSDC_PATCH_BIT_CMDFSEL    (0x1 << 27)	/* RW */
#घोषणा MSDC_PATCH_BIT_INTDLSEL   (0x1 << 28)	/* RW */
#घोषणा MSDC_PATCH_BIT_SPCPUSH    (0x1 << 29)	/* RW */
#घोषणा MSDC_PATCH_BIT_DECRCTMO   (0x1 << 30)	/* RW */

#घोषणा MSDC_PATCH_BIT1_CMDTA     (0x7 << 3)    /* RW */
#घोषणा MSDC_PB1_BUSY_CHECK_SEL   (0x1 << 7)    /* RW */
#घोषणा MSDC_PATCH_BIT1_STOP_DLY  (0xf << 8)    /* RW */

#घोषणा MSDC_PATCH_BIT2_CFGRESP   (0x1 << 15)   /* RW */
#घोषणा MSDC_PATCH_BIT2_CFGCRCSTS (0x1 << 28)   /* RW */
#घोषणा MSDC_PB2_SUPPORT_64G      (0x1 << 1)    /* RW */
#घोषणा MSDC_PB2_RESPWAIT         (0x3 << 2)    /* RW */
#घोषणा MSDC_PB2_RESPSTSENSEL     (0x7 << 16)   /* RW */
#घोषणा MSDC_PB2_CRCSTSENSEL      (0x7 << 29)   /* RW */

#घोषणा MSDC_PAD_TUNE_DATWRDLY	  (0x1f <<  0)	/* RW */
#घोषणा MSDC_PAD_TUNE_DATRRDLY	  (0x1f <<  8)	/* RW */
#घोषणा MSDC_PAD_TUNE_CMDRDLY	  (0x1f << 16)  /* RW */
#घोषणा MSDC_PAD_TUNE_CMDRRDLY	  (0x1f << 22)	/* RW */
#घोषणा MSDC_PAD_TUNE_CLKTDLY	  (0x1f << 27)  /* RW */
#घोषणा MSDC_PAD_TUNE_RXDLYSEL	  (0x1 << 15)   /* RW */
#घोषणा MSDC_PAD_TUNE_RD_SEL	  (0x1 << 13)   /* RW */
#घोषणा MSDC_PAD_TUNE_CMD_SEL	  (0x1 << 21)   /* RW */

#घोषणा PAD_DS_TUNE_DLY1	  (0x1f << 2)   /* RW */
#घोषणा PAD_DS_TUNE_DLY2	  (0x1f << 7)   /* RW */
#घोषणा PAD_DS_TUNE_DLY3	  (0x1f << 12)  /* RW */

#घोषणा PAD_CMD_TUNE_RX_DLY3	  (0x1f << 1)  /* RW */

/* EMMC51_CFG0 mask */
#घोषणा CMDQ_RDAT_CNT		  (0x3ff << 12)	/* RW */

#घोषणा EMMC50_CFG_PADCMD_LATCHCK (0x1 << 0)   /* RW */
#घोषणा EMMC50_CFG_CRCSTS_EDGE    (0x1 << 3)   /* RW */
#घोषणा EMMC50_CFG_CFCSTS_SEL     (0x1 << 4)   /* RW */
#घोषणा EMMC50_CFG_CMD_RESP_SEL   (0x1 << 9)   /* RW */

/* EMMC50_CFG1 mask */
#घोषणा EMMC50_CFG1_DS_CFG        (0x1 << 28)  /* RW */

#घोषणा EMMC50_CFG3_OUTS_WR       (0x1f << 0)  /* RW */

#घोषणा SDC_FIFO_CFG_WRVALIDSEL   (0x1 << 24)  /* RW */
#घोषणा SDC_FIFO_CFG_RDVALIDSEL   (0x1 << 25)  /* RW */

/* CQHCI_SETTING */
#घोषणा CQHCI_RD_CMD_WND_SEL	  (0x1 << 14) /* RW */
#घोषणा CQHCI_WR_CMD_WND_SEL	  (0x1 << 15) /* RW */

/* EMMC_TOP_CONTROL mask */
#घोषणा PAD_RXDLY_SEL           (0x1 << 0)      /* RW */
#घोषणा DELAY_EN                (0x1 << 1)      /* RW */
#घोषणा PAD_DAT_RD_RXDLY2       (0x1f << 2)     /* RW */
#घोषणा PAD_DAT_RD_RXDLY        (0x1f << 7)     /* RW */
#घोषणा PAD_DAT_RD_RXDLY2_SEL   (0x1 << 12)     /* RW */
#घोषणा PAD_DAT_RD_RXDLY_SEL    (0x1 << 13)     /* RW */
#घोषणा DATA_K_VALUE_SEL        (0x1 << 14)     /* RW */
#घोषणा SDC_RX_ENH_EN           (0x1 << 15)     /* TW */

/* EMMC_TOP_CMD mask */
#घोषणा PAD_CMD_RXDLY2          (0x1f << 0)     /* RW */
#घोषणा PAD_CMD_RXDLY           (0x1f << 5)     /* RW */
#घोषणा PAD_CMD_RD_RXDLY2_SEL   (0x1 << 10)     /* RW */
#घोषणा PAD_CMD_RD_RXDLY_SEL    (0x1 << 11)     /* RW */
#घोषणा PAD_CMD_TX_DLY          (0x1f << 12)    /* RW */

#घोषणा REQ_CMD_EIO  (0x1 << 0)
#घोषणा REQ_CMD_TMO  (0x1 << 1)
#घोषणा REQ_DAT_ERR  (0x1 << 2)
#घोषणा REQ_STOP_EIO (0x1 << 3)
#घोषणा REQ_STOP_TMO (0x1 << 4)
#घोषणा REQ_CMD_BUSY (0x1 << 5)

#घोषणा MSDC_PREPARE_FLAG (0x1 << 0)
#घोषणा MSDC_ASYNC_FLAG (0x1 << 1)
#घोषणा MSDC_MMAP_FLAG (0x1 << 2)

#घोषणा MTK_MMC_AUTOSUSPEND_DELAY	50
#घोषणा CMD_TIMEOUT         (HZ/10 * 5)	/* 100ms x5 */
#घोषणा DAT_TIMEOUT         (HZ    * 5)	/* 1000ms x5 */

#घोषणा DEFAULT_DEBOUNCE	(8)	/* 8 cycles CD debounce */

#घोषणा PAD_DELAY_MAX	32 /* PAD delay cells */
/*--------------------------------------------------------------------------*/
/* Descriptor Structure                                                     */
/*--------------------------------------------------------------------------*/
काष्ठा mt_gpdma_desc अणु
	u32 gpd_info;
#घोषणा GPDMA_DESC_HWO		(0x1 << 0)
#घोषणा GPDMA_DESC_BDP		(0x1 << 1)
#घोषणा GPDMA_DESC_CHECKSUM	(0xff << 8) /* bit8 ~ bit15 */
#घोषणा GPDMA_DESC_INT		(0x1 << 16)
#घोषणा GPDMA_DESC_NEXT_H4	(0xf << 24)
#घोषणा GPDMA_DESC_PTR_H4	(0xf << 28)
	u32 next;
	u32 ptr;
	u32 gpd_data_len;
#घोषणा GPDMA_DESC_BUFLEN	(0xffff) /* bit0 ~ bit15 */
#घोषणा GPDMA_DESC_EXTLEN	(0xff << 16) /* bit16 ~ bit23 */
	u32 arg;
	u32 blknum;
	u32 cmd;
पूर्ण;

काष्ठा mt_bdma_desc अणु
	u32 bd_info;
#घोषणा BDMA_DESC_EOL		(0x1 << 0)
#घोषणा BDMA_DESC_CHECKSUM	(0xff << 8) /* bit8 ~ bit15 */
#घोषणा BDMA_DESC_BLKPAD	(0x1 << 17)
#घोषणा BDMA_DESC_DWPAD		(0x1 << 18)
#घोषणा BDMA_DESC_NEXT_H4	(0xf << 24)
#घोषणा BDMA_DESC_PTR_H4	(0xf << 28)
	u32 next;
	u32 ptr;
	u32 bd_data_len;
#घोषणा BDMA_DESC_BUFLEN	(0xffff) /* bit0 ~ bit15 */
#घोषणा BDMA_DESC_BUFLEN_EXT	(0xffffff) /* bit0 ~ bit23 */
पूर्ण;

काष्ठा msdc_dma अणु
	काष्ठा scatterlist *sg;	/* I/O scatter list */
	काष्ठा mt_gpdma_desc *gpd;		/* poपूर्णांकer to gpd array */
	काष्ठा mt_bdma_desc *bd;		/* poपूर्णांकer to bd array */
	dma_addr_t gpd_addr;	/* the physical address of gpd array */
	dma_addr_t bd_addr;	/* the physical address of bd array */
पूर्ण;

काष्ठा msdc_save_para अणु
	u32 msdc_cfg;
	u32 iocon;
	u32 sdc_cfg;
	u32 pad_tune;
	u32 patch_bit0;
	u32 patch_bit1;
	u32 patch_bit2;
	u32 pad_ds_tune;
	u32 pad_cmd_tune;
	u32 emmc50_cfg0;
	u32 emmc50_cfg3;
	u32 sdc_fअगरo_cfg;
	u32 emmc_top_control;
	u32 emmc_top_cmd;
	u32 emmc50_pad_ds_tune;
पूर्ण;

काष्ठा mtk_mmc_compatible अणु
	u8 clk_भाग_bits;
	bool recheck_sdio_irq;
	bool hs400_tune; /* only used क्रम MT8173 */
	u32 pad_tune_reg;
	bool async_fअगरo;
	bool data_tune;
	bool busy_check;
	bool stop_clk_fix;
	bool enhance_rx;
	bool support_64g;
	bool use_पूर्णांकernal_cd;
पूर्ण;

काष्ठा msdc_tune_para अणु
	u32 iocon;
	u32 pad_tune;
	u32 pad_cmd_tune;
	u32 emmc_top_control;
	u32 emmc_top_cmd;
पूर्ण;

काष्ठा msdc_delay_phase अणु
	u8 maxlen;
	u8 start;
	u8 final_phase;
पूर्ण;

काष्ठा msdc_host अणु
	काष्ठा device *dev;
	स्थिर काष्ठा mtk_mmc_compatible *dev_comp;
	पूर्णांक cmd_rsp;

	spinlock_t lock;
	काष्ठा mmc_request *mrq;
	काष्ठा mmc_command *cmd;
	काष्ठा mmc_data *data;
	पूर्णांक error;

	व्योम __iomem *base;		/* host base address */
	व्योम __iomem *top_base;		/* host top रेजिस्टर base address */

	काष्ठा msdc_dma dma;	/* dma channel */
	u64 dma_mask;

	u32 समयout_ns;		/* data समयout ns */
	u32 समयout_clks;	/* data समयout clks */

	काष्ठा pinctrl *pinctrl;
	काष्ठा pinctrl_state *pins_शेष;
	काष्ठा pinctrl_state *pins_uhs;
	काष्ठा delayed_work req_समयout;
	पूर्णांक irq;		/* host पूर्णांकerrupt */
	काष्ठा reset_control *reset;

	काष्ठा clk *src_clk;	/* msdc source घड़ी */
	काष्ठा clk *h_clk;      /* msdc h_clk */
	काष्ठा clk *bus_clk;	/* bus घड़ी which used to access रेजिस्टर */
	काष्ठा clk *src_clk_cg; /* msdc source घड़ी control gate */
	काष्ठा clk *sys_clk_cg;	/* msdc subsys घड़ी control gate */
	काष्ठा clk_bulk_data bulk_clks[MSDC_NR_CLOCKS];
	u32 mclk;		/* mmc subप्रणाली घड़ी frequency */
	u32 src_clk_freq;	/* source घड़ी frequency */
	अचिन्हित अक्षर timing;
	bool vqmmc_enabled;
	u32 latch_ck;
	u32 hs400_ds_delay;
	u32 hs200_cmd_पूर्णांक_delay; /* cmd पूर्णांकernal delay क्रम HS200/SDR104 */
	u32 hs400_cmd_पूर्णांक_delay; /* cmd पूर्णांकernal delay क्रम HS400 */
	bool hs400_cmd_resp_sel_rising;
				 /* cmd response sample selection क्रम HS400 */
	bool hs400_mode;	/* current eMMC will run at hs400 mode */
	bool पूर्णांकernal_cd;	/* Use पूर्णांकernal card-detect logic */
	bool cqhci;		/* support eMMC hw cmdq */
	काष्ठा msdc_save_para save_para; /* used when gate HCLK */
	काष्ठा msdc_tune_para def_tune_para; /* शेष tune setting */
	काष्ठा msdc_tune_para saved_tune_para; /* tune result of CMD21/CMD19 */
	काष्ठा cqhci_host *cq_host;
पूर्ण;

अटल स्थिर काष्ठा mtk_mmc_compatible mt8135_compat = अणु
	.clk_भाग_bits = 8,
	.recheck_sdio_irq = true,
	.hs400_tune = false,
	.pad_tune_reg = MSDC_PAD_TUNE,
	.async_fअगरo = false,
	.data_tune = false,
	.busy_check = false,
	.stop_clk_fix = false,
	.enhance_rx = false,
	.support_64g = false,
पूर्ण;

अटल स्थिर काष्ठा mtk_mmc_compatible mt8173_compat = अणु
	.clk_भाग_bits = 8,
	.recheck_sdio_irq = true,
	.hs400_tune = true,
	.pad_tune_reg = MSDC_PAD_TUNE,
	.async_fअगरo = false,
	.data_tune = false,
	.busy_check = false,
	.stop_clk_fix = false,
	.enhance_rx = false,
	.support_64g = false,
पूर्ण;

अटल स्थिर काष्ठा mtk_mmc_compatible mt8183_compat = अणु
	.clk_भाग_bits = 12,
	.recheck_sdio_irq = false,
	.hs400_tune = false,
	.pad_tune_reg = MSDC_PAD_TUNE0,
	.async_fअगरo = true,
	.data_tune = true,
	.busy_check = true,
	.stop_clk_fix = true,
	.enhance_rx = true,
	.support_64g = true,
पूर्ण;

अटल स्थिर काष्ठा mtk_mmc_compatible mt2701_compat = अणु
	.clk_भाग_bits = 12,
	.recheck_sdio_irq = true,
	.hs400_tune = false,
	.pad_tune_reg = MSDC_PAD_TUNE0,
	.async_fअगरo = true,
	.data_tune = true,
	.busy_check = false,
	.stop_clk_fix = false,
	.enhance_rx = false,
	.support_64g = false,
पूर्ण;

अटल स्थिर काष्ठा mtk_mmc_compatible mt2712_compat = अणु
	.clk_भाग_bits = 12,
	.recheck_sdio_irq = false,
	.hs400_tune = false,
	.pad_tune_reg = MSDC_PAD_TUNE0,
	.async_fअगरo = true,
	.data_tune = true,
	.busy_check = true,
	.stop_clk_fix = true,
	.enhance_rx = true,
	.support_64g = true,
पूर्ण;

अटल स्थिर काष्ठा mtk_mmc_compatible mt7622_compat = अणु
	.clk_भाग_bits = 12,
	.recheck_sdio_irq = true,
	.hs400_tune = false,
	.pad_tune_reg = MSDC_PAD_TUNE0,
	.async_fअगरo = true,
	.data_tune = true,
	.busy_check = true,
	.stop_clk_fix = true,
	.enhance_rx = true,
	.support_64g = false,
पूर्ण;

अटल स्थिर काष्ठा mtk_mmc_compatible mt8516_compat = अणु
	.clk_भाग_bits = 12,
	.recheck_sdio_irq = true,
	.hs400_tune = false,
	.pad_tune_reg = MSDC_PAD_TUNE0,
	.async_fअगरo = true,
	.data_tune = true,
	.busy_check = true,
	.stop_clk_fix = true,
पूर्ण;

अटल स्थिर काष्ठा mtk_mmc_compatible mt7620_compat = अणु
	.clk_भाग_bits = 8,
	.recheck_sdio_irq = true,
	.hs400_tune = false,
	.pad_tune_reg = MSDC_PAD_TUNE,
	.async_fअगरo = false,
	.data_tune = false,
	.busy_check = false,
	.stop_clk_fix = false,
	.enhance_rx = false,
	.use_पूर्णांकernal_cd = true,
पूर्ण;

अटल स्थिर काष्ठा mtk_mmc_compatible mt6779_compat = अणु
	.clk_भाग_bits = 12,
	.recheck_sdio_irq = false,
	.hs400_tune = false,
	.pad_tune_reg = MSDC_PAD_TUNE0,
	.async_fअगरo = true,
	.data_tune = true,
	.busy_check = true,
	.stop_clk_fix = true,
	.enhance_rx = true,
	.support_64g = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id msdc_of_ids[] = अणु
	अणु .compatible = "mediatek,mt8135-mmc", .data = &mt8135_compatपूर्ण,
	अणु .compatible = "mediatek,mt8173-mmc", .data = &mt8173_compatपूर्ण,
	अणु .compatible = "mediatek,mt8183-mmc", .data = &mt8183_compatपूर्ण,
	अणु .compatible = "mediatek,mt2701-mmc", .data = &mt2701_compatपूर्ण,
	अणु .compatible = "mediatek,mt2712-mmc", .data = &mt2712_compatपूर्ण,
	अणु .compatible = "mediatek,mt7622-mmc", .data = &mt7622_compatपूर्ण,
	अणु .compatible = "mediatek,mt8516-mmc", .data = &mt8516_compatपूर्ण,
	अणु .compatible = "mediatek,mt7620-mmc", .data = &mt7620_compatपूर्ण,
	अणु .compatible = "mediatek,mt6779-mmc", .data = &mt6779_compatपूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, msdc_of_ids);

अटल व्योम sdr_set_bits(व्योम __iomem *reg, u32 bs)
अणु
	u32 val = पढ़ोl(reg);

	val |= bs;
	ग_लिखोl(val, reg);
पूर्ण

अटल व्योम sdr_clr_bits(व्योम __iomem *reg, u32 bs)
अणु
	u32 val = पढ़ोl(reg);

	val &= ~bs;
	ग_लिखोl(val, reg);
पूर्ण

अटल व्योम sdr_set_field(व्योम __iomem *reg, u32 field, u32 val)
अणु
	अचिन्हित पूर्णांक tv = पढ़ोl(reg);

	tv &= ~field;
	tv |= ((val) << (ffs((अचिन्हित पूर्णांक)field) - 1));
	ग_लिखोl(tv, reg);
पूर्ण

अटल व्योम sdr_get_field(व्योम __iomem *reg, u32 field, u32 *val)
अणु
	अचिन्हित पूर्णांक tv = पढ़ोl(reg);

	*val = ((tv & field) >> (ffs((अचिन्हित पूर्णांक)field) - 1));
पूर्ण

अटल व्योम msdc_reset_hw(काष्ठा msdc_host *host)
अणु
	u32 val;

	sdr_set_bits(host->base + MSDC_CFG, MSDC_CFG_RST);
	जबतक (पढ़ोl(host->base + MSDC_CFG) & MSDC_CFG_RST)
		cpu_relax();

	sdr_set_bits(host->base + MSDC_FIFOCS, MSDC_FIFOCS_CLR);
	जबतक (पढ़ोl(host->base + MSDC_FIFOCS) & MSDC_FIFOCS_CLR)
		cpu_relax();

	val = पढ़ोl(host->base + MSDC_INT);
	ग_लिखोl(val, host->base + MSDC_INT);
पूर्ण

अटल व्योम msdc_cmd_next(काष्ठा msdc_host *host,
		काष्ठा mmc_request *mrq, काष्ठा mmc_command *cmd);
अटल व्योम __msdc_enable_sdio_irq(काष्ठा msdc_host *host, पूर्णांक enb);

अटल स्थिर u32 cmd_पूर्णांकs_mask = MSDC_INTEN_CMDRDY | MSDC_INTEN_RSPCRCERR |
			MSDC_INTEN_CMDTMO | MSDC_INTEN_ACMDRDY |
			MSDC_INTEN_ACMDCRCERR | MSDC_INTEN_ACMDTMO;
अटल स्थिर u32 data_पूर्णांकs_mask = MSDC_INTEN_XFER_COMPL | MSDC_INTEN_DATTMO |
			MSDC_INTEN_DATCRCERR | MSDC_INTEN_DMA_BDCSERR |
			MSDC_INTEN_DMA_GPDCSERR | MSDC_INTEN_DMA_PROTECT;

अटल u8 msdc_dma_calcs(u8 *buf, u32 len)
अणु
	u32 i, sum = 0;

	क्रम (i = 0; i < len; i++)
		sum += buf[i];
	वापस 0xff - (u8) sum;
पूर्ण

अटल अंतरभूत व्योम msdc_dma_setup(काष्ठा msdc_host *host, काष्ठा msdc_dma *dma,
		काष्ठा mmc_data *data)
अणु
	अचिन्हित पूर्णांक j, dma_len;
	dma_addr_t dma_address;
	u32 dma_ctrl;
	काष्ठा scatterlist *sg;
	काष्ठा mt_gpdma_desc *gpd;
	काष्ठा mt_bdma_desc *bd;

	sg = data->sg;

	gpd = dma->gpd;
	bd = dma->bd;

	/* modअगरy gpd */
	gpd->gpd_info |= GPDMA_DESC_HWO;
	gpd->gpd_info |= GPDMA_DESC_BDP;
	/* need to clear first. use these bits to calc checksum */
	gpd->gpd_info &= ~GPDMA_DESC_CHECKSUM;
	gpd->gpd_info |= msdc_dma_calcs((u8 *) gpd, 16) << 8;

	/* modअगरy bd */
	क्रम_each_sg(data->sg, sg, data->sg_count, j) अणु
		dma_address = sg_dma_address(sg);
		dma_len = sg_dma_len(sg);

		/* init bd */
		bd[j].bd_info &= ~BDMA_DESC_BLKPAD;
		bd[j].bd_info &= ~BDMA_DESC_DWPAD;
		bd[j].ptr = lower_32_bits(dma_address);
		अगर (host->dev_comp->support_64g) अणु
			bd[j].bd_info &= ~BDMA_DESC_PTR_H4;
			bd[j].bd_info |= (upper_32_bits(dma_address) & 0xf)
					 << 28;
		पूर्ण

		अगर (host->dev_comp->support_64g) अणु
			bd[j].bd_data_len &= ~BDMA_DESC_BUFLEN_EXT;
			bd[j].bd_data_len |= (dma_len & BDMA_DESC_BUFLEN_EXT);
		पूर्ण अन्यथा अणु
			bd[j].bd_data_len &= ~BDMA_DESC_BUFLEN;
			bd[j].bd_data_len |= (dma_len & BDMA_DESC_BUFLEN);
		पूर्ण

		अगर (j == data->sg_count - 1) /* the last bd */
			bd[j].bd_info |= BDMA_DESC_EOL;
		अन्यथा
			bd[j].bd_info &= ~BDMA_DESC_EOL;

		/* checksume need to clear first */
		bd[j].bd_info &= ~BDMA_DESC_CHECKSUM;
		bd[j].bd_info |= msdc_dma_calcs((u8 *)(&bd[j]), 16) << 8;
	पूर्ण

	sdr_set_field(host->base + MSDC_DMA_CFG, MSDC_DMA_CFG_DECSEN, 1);
	dma_ctrl = पढ़ोl_relaxed(host->base + MSDC_DMA_CTRL);
	dma_ctrl &= ~(MSDC_DMA_CTRL_BRUSTSZ | MSDC_DMA_CTRL_MODE);
	dma_ctrl |= (MSDC_BURST_64B << 12 | 1 << 8);
	ग_लिखोl_relaxed(dma_ctrl, host->base + MSDC_DMA_CTRL);
	अगर (host->dev_comp->support_64g)
		sdr_set_field(host->base + DMA_SA_H4BIT, DMA_ADDR_HIGH_4BIT,
			      upper_32_bits(dma->gpd_addr) & 0xf);
	ग_लिखोl(lower_32_bits(dma->gpd_addr), host->base + MSDC_DMA_SA);
पूर्ण

अटल व्योम msdc_prepare_data(काष्ठा msdc_host *host, काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_data *data = mrq->data;

	अगर (!(data->host_cookie & MSDC_PREPARE_FLAG)) अणु
		data->host_cookie |= MSDC_PREPARE_FLAG;
		data->sg_count = dma_map_sg(host->dev, data->sg, data->sg_len,
					    mmc_get_dma_dir(data));
	पूर्ण
पूर्ण

अटल व्योम msdc_unprepare_data(काष्ठा msdc_host *host, काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_data *data = mrq->data;

	अगर (data->host_cookie & MSDC_ASYNC_FLAG)
		वापस;

	अगर (data->host_cookie & MSDC_PREPARE_FLAG) अणु
		dma_unmap_sg(host->dev, data->sg, data->sg_len,
			     mmc_get_dma_dir(data));
		data->host_cookie &= ~MSDC_PREPARE_FLAG;
	पूर्ण
पूर्ण

अटल u64 msdc_समयout_cal(काष्ठा msdc_host *host, u64 ns, u64 clks)
अणु
	काष्ठा mmc_host *mmc = mmc_from_priv(host);
	u64 समयout, clk_ns;
	u32 mode = 0;

	अगर (mmc->actual_घड़ी == 0) अणु
		समयout = 0;
	पूर्ण अन्यथा अणु
		clk_ns  = 1000000000ULL;
		करो_भाग(clk_ns, mmc->actual_घड़ी);
		समयout = ns + clk_ns - 1;
		करो_भाग(समयout, clk_ns);
		समयout += clks;
		/* in 1048576 sclk cycle unit */
		समयout = DIV_ROUND_UP(समयout, (0x1 << 20));
		अगर (host->dev_comp->clk_भाग_bits == 8)
			sdr_get_field(host->base + MSDC_CFG,
				      MSDC_CFG_CKMOD, &mode);
		अन्यथा
			sdr_get_field(host->base + MSDC_CFG,
				      MSDC_CFG_CKMOD_EXTRA, &mode);
		/*DDR mode will द्विगुन the clk cycles क्रम data समयout */
		समयout = mode >= 2 ? समयout * 2 : समयout;
		समयout = समयout > 1 ? समयout - 1 : 0;
	पूर्ण
	वापस समयout;
पूर्ण

/* घड़ी control primitives */
अटल व्योम msdc_set_समयout(काष्ठा msdc_host *host, u64 ns, u64 clks)
अणु
	u64 समयout;

	host->समयout_ns = ns;
	host->समयout_clks = clks;

	समयout = msdc_समयout_cal(host, ns, clks);
	sdr_set_field(host->base + SDC_CFG, SDC_CFG_DTOC,
		      (u32)(समयout > 255 ? 255 : समयout));
पूर्ण

अटल व्योम msdc_set_busy_समयout(काष्ठा msdc_host *host, u64 ns, u64 clks)
अणु
	u64 समयout;

	समयout = msdc_समयout_cal(host, ns, clks);
	sdr_set_field(host->base + SDC_CFG, SDC_CFG_WRDTOC,
		      (u32)(समयout > 8191 ? 8191 : समयout));
पूर्ण

अटल व्योम msdc_gate_घड़ी(काष्ठा msdc_host *host)
अणु
	clk_bulk_disable_unprepare(MSDC_NR_CLOCKS, host->bulk_clks);
	clk_disable_unprepare(host->src_clk_cg);
	clk_disable_unprepare(host->src_clk);
	clk_disable_unprepare(host->bus_clk);
	clk_disable_unprepare(host->h_clk);
पूर्ण

अटल व्योम msdc_ungate_घड़ी(काष्ठा msdc_host *host)
अणु
	पूर्णांक ret;

	clk_prepare_enable(host->h_clk);
	clk_prepare_enable(host->bus_clk);
	clk_prepare_enable(host->src_clk);
	clk_prepare_enable(host->src_clk_cg);
	ret = clk_bulk_prepare_enable(MSDC_NR_CLOCKS, host->bulk_clks);
	अगर (ret) अणु
		dev_err(host->dev, "Cannot enable pclk/axi/ahb clock gates\n");
		वापस;
	पूर्ण

	जबतक (!(पढ़ोl(host->base + MSDC_CFG) & MSDC_CFG_CKSTB))
		cpu_relax();
पूर्ण

अटल व्योम msdc_set_mclk(काष्ठा msdc_host *host, अचिन्हित अक्षर timing, u32 hz)
अणु
	काष्ठा mmc_host *mmc = mmc_from_priv(host);
	u32 mode;
	u32 flags;
	u32 भाग;
	u32 sclk;
	u32 tune_reg = host->dev_comp->pad_tune_reg;

	अगर (!hz) अणु
		dev_dbg(host->dev, "set mclk to 0\n");
		host->mclk = 0;
		mmc->actual_घड़ी = 0;
		sdr_clr_bits(host->base + MSDC_CFG, MSDC_CFG_CKPDN);
		वापस;
	पूर्ण

	flags = पढ़ोl(host->base + MSDC_INTEN);
	sdr_clr_bits(host->base + MSDC_INTEN, flags);
	अगर (host->dev_comp->clk_भाग_bits == 8)
		sdr_clr_bits(host->base + MSDC_CFG, MSDC_CFG_HS400_CK_MODE);
	अन्यथा
		sdr_clr_bits(host->base + MSDC_CFG,
			     MSDC_CFG_HS400_CK_MODE_EXTRA);
	अगर (timing == MMC_TIMING_UHS_DDR50 ||
	    timing == MMC_TIMING_MMC_DDR52 ||
	    timing == MMC_TIMING_MMC_HS400) अणु
		अगर (timing == MMC_TIMING_MMC_HS400)
			mode = 0x3;
		अन्यथा
			mode = 0x2; /* ddr mode and use भागisor */

		अगर (hz >= (host->src_clk_freq >> 2)) अणु
			भाग = 0; /* mean भाग = 1/4 */
			sclk = host->src_clk_freq >> 2; /* sclk = clk / 4 */
		पूर्ण अन्यथा अणु
			भाग = (host->src_clk_freq + ((hz << 2) - 1)) / (hz << 2);
			sclk = (host->src_clk_freq >> 2) / भाग;
			भाग = (भाग >> 1);
		पूर्ण

		अगर (timing == MMC_TIMING_MMC_HS400 &&
		    hz >= (host->src_clk_freq >> 1)) अणु
			अगर (host->dev_comp->clk_भाग_bits == 8)
				sdr_set_bits(host->base + MSDC_CFG,
					     MSDC_CFG_HS400_CK_MODE);
			अन्यथा
				sdr_set_bits(host->base + MSDC_CFG,
					     MSDC_CFG_HS400_CK_MODE_EXTRA);
			sclk = host->src_clk_freq >> 1;
			भाग = 0; /* भाग is ignore when bit18 is set */
		पूर्ण
	पूर्ण अन्यथा अगर (hz >= host->src_clk_freq) अणु
		mode = 0x1; /* no भागisor */
		भाग = 0;
		sclk = host->src_clk_freq;
	पूर्ण अन्यथा अणु
		mode = 0x0; /* use भागisor */
		अगर (hz >= (host->src_clk_freq >> 1)) अणु
			भाग = 0; /* mean भाग = 1/2 */
			sclk = host->src_clk_freq >> 1; /* sclk = clk / 2 */
		पूर्ण अन्यथा अणु
			भाग = (host->src_clk_freq + ((hz << 2) - 1)) / (hz << 2);
			sclk = (host->src_clk_freq >> 2) / भाग;
		पूर्ण
	पूर्ण
	sdr_clr_bits(host->base + MSDC_CFG, MSDC_CFG_CKPDN);
	/*
	 * As src_clk/HCLK use the same bit to gate/ungate,
	 * So अगर want to only gate src_clk, need gate its parent(mux).
	 */
	अगर (host->src_clk_cg)
		clk_disable_unprepare(host->src_clk_cg);
	अन्यथा
		clk_disable_unprepare(clk_get_parent(host->src_clk));
	अगर (host->dev_comp->clk_भाग_bits == 8)
		sdr_set_field(host->base + MSDC_CFG,
			      MSDC_CFG_CKMOD | MSDC_CFG_CKDIV,
			      (mode << 8) | भाग);
	अन्यथा
		sdr_set_field(host->base + MSDC_CFG,
			      MSDC_CFG_CKMOD_EXTRA | MSDC_CFG_CKDIV_EXTRA,
			      (mode << 12) | भाग);
	अगर (host->src_clk_cg)
		clk_prepare_enable(host->src_clk_cg);
	अन्यथा
		clk_prepare_enable(clk_get_parent(host->src_clk));

	जबतक (!(पढ़ोl(host->base + MSDC_CFG) & MSDC_CFG_CKSTB))
		cpu_relax();
	sdr_set_bits(host->base + MSDC_CFG, MSDC_CFG_CKPDN);
	mmc->actual_घड़ी = sclk;
	host->mclk = hz;
	host->timing = timing;
	/* need because clk changed. */
	msdc_set_समयout(host, host->समयout_ns, host->समयout_clks);
	sdr_set_bits(host->base + MSDC_INTEN, flags);

	/*
	 * mmc_select_hs400() will drop to 50Mhz and High speed mode,
	 * tune result of hs200/200Mhz is not suitable क्रम 50Mhz
	 */
	अगर (mmc->actual_घड़ी <= 52000000) अणु
		ग_लिखोl(host->def_tune_para.iocon, host->base + MSDC_IOCON);
		अगर (host->top_base) अणु
			ग_लिखोl(host->def_tune_para.emmc_top_control,
			       host->top_base + EMMC_TOP_CONTROL);
			ग_लिखोl(host->def_tune_para.emmc_top_cmd,
			       host->top_base + EMMC_TOP_CMD);
		पूर्ण अन्यथा अणु
			ग_लिखोl(host->def_tune_para.pad_tune,
			       host->base + tune_reg);
		पूर्ण
	पूर्ण अन्यथा अणु
		ग_लिखोl(host->saved_tune_para.iocon, host->base + MSDC_IOCON);
		ग_लिखोl(host->saved_tune_para.pad_cmd_tune,
		       host->base + PAD_CMD_TUNE);
		अगर (host->top_base) अणु
			ग_लिखोl(host->saved_tune_para.emmc_top_control,
			       host->top_base + EMMC_TOP_CONTROL);
			ग_लिखोl(host->saved_tune_para.emmc_top_cmd,
			       host->top_base + EMMC_TOP_CMD);
		पूर्ण अन्यथा अणु
			ग_लिखोl(host->saved_tune_para.pad_tune,
			       host->base + tune_reg);
		पूर्ण
	पूर्ण

	अगर (timing == MMC_TIMING_MMC_HS400 &&
	    host->dev_comp->hs400_tune)
		sdr_set_field(host->base + tune_reg,
			      MSDC_PAD_TUNE_CMDRRDLY,
			      host->hs400_cmd_पूर्णांक_delay);
	dev_dbg(host->dev, "sclk: %d, timing: %d\n", mmc->actual_घड़ी,
		timing);
पूर्ण

अटल अंतरभूत u32 msdc_cmd_find_resp(काष्ठा msdc_host *host,
		काष्ठा mmc_request *mrq, काष्ठा mmc_command *cmd)
अणु
	u32 resp;

	चयन (mmc_resp_type(cmd)) अणु
		/* Actually, R1, R5, R6, R7 are the same */
	हाल MMC_RSP_R1:
		resp = 0x1;
		अवरोध;
	हाल MMC_RSP_R1B:
		resp = 0x7;
		अवरोध;
	हाल MMC_RSP_R2:
		resp = 0x2;
		अवरोध;
	हाल MMC_RSP_R3:
		resp = 0x3;
		अवरोध;
	हाल MMC_RSP_NONE:
	शेष:
		resp = 0x0;
		अवरोध;
	पूर्ण

	वापस resp;
पूर्ण

अटल अंतरभूत u32 msdc_cmd_prepare_raw_cmd(काष्ठा msdc_host *host,
		काष्ठा mmc_request *mrq, काष्ठा mmc_command *cmd)
अणु
	काष्ठा mmc_host *mmc = mmc_from_priv(host);
	/* rawcmd :
	 * vol_swt << 30 | स्वतः_cmd << 28 | blklen << 16 | go_irq << 15 |
	 * stop << 14 | rw << 13 | dtype << 11 | rsptyp << 7 | brk << 6 | opcode
	 */
	u32 opcode = cmd->opcode;
	u32 resp = msdc_cmd_find_resp(host, mrq, cmd);
	u32 rawcmd = (opcode & 0x3f) | ((resp & 0x7) << 7);

	host->cmd_rsp = resp;

	अगर ((opcode == SD_IO_RW_सूचीECT && cmd->flags == (अचिन्हित पूर्णांक) -1) ||
	    opcode == MMC_STOP_TRANSMISSION)
		rawcmd |= (0x1 << 14);
	अन्यथा अगर (opcode == SD_SWITCH_VOLTAGE)
		rawcmd |= (0x1 << 30);
	अन्यथा अगर (opcode == SD_APP_SEND_SCR ||
		 opcode == SD_APP_SEND_NUM_WR_BLKS ||
		 (opcode == SD_SWITCH && mmc_cmd_type(cmd) == MMC_CMD_ADTC) ||
		 (opcode == SD_APP_SD_STATUS && mmc_cmd_type(cmd) == MMC_CMD_ADTC) ||
		 (opcode == MMC_SEND_EXT_CSD && mmc_cmd_type(cmd) == MMC_CMD_ADTC))
		rawcmd |= (0x1 << 11);

	अगर (cmd->data) अणु
		काष्ठा mmc_data *data = cmd->data;

		अगर (mmc_op_multi(opcode)) अणु
			अगर (mmc_card_mmc(mmc->card) && mrq->sbc &&
			    !(mrq->sbc->arg & 0xFFFF0000))
				rawcmd |= 0x2 << 28; /* AutoCMD23 */
		पूर्ण

		rawcmd |= ((data->blksz & 0xFFF) << 16);
		अगर (data->flags & MMC_DATA_WRITE)
			rawcmd |= (0x1 << 13);
		अगर (data->blocks > 1)
			rawcmd |= (0x2 << 11);
		अन्यथा
			rawcmd |= (0x1 << 11);
		/* Always use dma mode */
		sdr_clr_bits(host->base + MSDC_CFG, MSDC_CFG_PIO);

		अगर (host->समयout_ns != data->समयout_ns ||
		    host->समयout_clks != data->समयout_clks)
			msdc_set_समयout(host, data->समयout_ns,
					data->समयout_clks);

		ग_लिखोl(data->blocks, host->base + SDC_BLK_NUM);
	पूर्ण
	वापस rawcmd;
पूर्ण

अटल व्योम msdc_start_data(काष्ठा msdc_host *host, काष्ठा mmc_request *mrq,
			    काष्ठा mmc_command *cmd, काष्ठा mmc_data *data)
अणु
	bool पढ़ो;

	WARN_ON(host->data);
	host->data = data;
	पढ़ो = data->flags & MMC_DATA_READ;

	mod_delayed_work(प्रणाली_wq, &host->req_समयout, DAT_TIMEOUT);
	msdc_dma_setup(host, &host->dma, data);
	sdr_set_bits(host->base + MSDC_INTEN, data_पूर्णांकs_mask);
	sdr_set_field(host->base + MSDC_DMA_CTRL, MSDC_DMA_CTRL_START, 1);
	dev_dbg(host->dev, "DMA start\n");
	dev_dbg(host->dev, "%s: cmd=%d DMA data: %d blocks; read=%d\n",
			__func__, cmd->opcode, data->blocks, पढ़ो);
पूर्ण

अटल पूर्णांक msdc_स्वतः_cmd_करोne(काष्ठा msdc_host *host, पूर्णांक events,
		काष्ठा mmc_command *cmd)
अणु
	u32 *rsp = cmd->resp;

	rsp[0] = पढ़ोl(host->base + SDC_ACMD_RESP);

	अगर (events & MSDC_INT_ACMDRDY) अणु
		cmd->error = 0;
	पूर्ण अन्यथा अणु
		msdc_reset_hw(host);
		अगर (events & MSDC_INT_ACMDCRCERR) अणु
			cmd->error = -EILSEQ;
			host->error |= REQ_STOP_EIO;
		पूर्ण अन्यथा अगर (events & MSDC_INT_ACMDTMO) अणु
			cmd->error = -ETIMEDOUT;
			host->error |= REQ_STOP_TMO;
		पूर्ण
		dev_err(host->dev,
			"%s: AUTO_CMD%d arg=%08X; rsp %08X; cmd_error=%d\n",
			__func__, cmd->opcode, cmd->arg, rsp[0], cmd->error);
	पूर्ण
	वापस cmd->error;
पूर्ण

/*
 * msdc_recheck_sdio_irq - recheck whether the SDIO irq is lost
 *
 * Host controller may lost पूर्णांकerrupt in some special हाल.
 * Add SDIO irq recheck mechanism to make sure all पूर्णांकerrupts
 * can be processed immediately
 */
अटल व्योम msdc_recheck_sdio_irq(काष्ठा msdc_host *host)
अणु
	काष्ठा mmc_host *mmc = mmc_from_priv(host);
	u32 reg_पूर्णांक, reg_पूर्णांकen, reg_ps;

	अगर (mmc->caps & MMC_CAP_SDIO_IRQ) अणु
		reg_पूर्णांकen = पढ़ोl(host->base + MSDC_INTEN);
		अगर (reg_पूर्णांकen & MSDC_INTEN_SDIOIRQ) अणु
			reg_पूर्णांक = पढ़ोl(host->base + MSDC_INT);
			reg_ps = पढ़ोl(host->base + MSDC_PS);
			अगर (!(reg_पूर्णांक & MSDC_INT_SDIOIRQ ||
			      reg_ps & MSDC_PS_DATA1)) अणु
				__msdc_enable_sdio_irq(host, 0);
				sdio_संकेत_irq(mmc);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम msdc_track_cmd_data(काष्ठा msdc_host *host,
				काष्ठा mmc_command *cmd, काष्ठा mmc_data *data)
अणु
	अगर (host->error)
		dev_dbg(host->dev, "%s: cmd=%d arg=%08X; host->error=0x%08X\n",
			__func__, cmd->opcode, cmd->arg, host->error);
पूर्ण

अटल व्योम msdc_request_करोne(काष्ठा msdc_host *host, काष्ठा mmc_request *mrq)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * No need check the वापस value of cancel_delayed_work, as only ONE
	 * path will go here!
	 */
	cancel_delayed_work(&host->req_समयout);

	spin_lock_irqsave(&host->lock, flags);
	host->mrq = शून्य;
	spin_unlock_irqrestore(&host->lock, flags);

	msdc_track_cmd_data(host, mrq->cmd, mrq->data);
	अगर (mrq->data)
		msdc_unprepare_data(host, mrq);
	अगर (host->error)
		msdc_reset_hw(host);
	mmc_request_करोne(mmc_from_priv(host), mrq);
	अगर (host->dev_comp->recheck_sdio_irq)
		msdc_recheck_sdio_irq(host);
पूर्ण

/* वापसs true अगर command is fully handled; वापसs false otherwise */
अटल bool msdc_cmd_करोne(काष्ठा msdc_host *host, पूर्णांक events,
			  काष्ठा mmc_request *mrq, काष्ठा mmc_command *cmd)
अणु
	bool करोne = false;
	bool sbc_error;
	अचिन्हित दीर्घ flags;
	u32 *rsp;

	अगर (mrq->sbc && cmd == mrq->cmd &&
	    (events & (MSDC_INT_ACMDRDY | MSDC_INT_ACMDCRCERR
				   | MSDC_INT_ACMDTMO)))
		msdc_स्वतः_cmd_करोne(host, events, mrq->sbc);

	sbc_error = mrq->sbc && mrq->sbc->error;

	अगर (!sbc_error && !(events & (MSDC_INT_CMDRDY
					| MSDC_INT_RSPCRCERR
					| MSDC_INT_CMDTMO)))
		वापस करोne;

	spin_lock_irqsave(&host->lock, flags);
	करोne = !host->cmd;
	host->cmd = शून्य;
	spin_unlock_irqrestore(&host->lock, flags);

	अगर (करोne)
		वापस true;
	rsp = cmd->resp;

	sdr_clr_bits(host->base + MSDC_INTEN, cmd_पूर्णांकs_mask);

	अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		अगर (cmd->flags & MMC_RSP_136) अणु
			rsp[0] = पढ़ोl(host->base + SDC_RESP3);
			rsp[1] = पढ़ोl(host->base + SDC_RESP2);
			rsp[2] = पढ़ोl(host->base + SDC_RESP1);
			rsp[3] = पढ़ोl(host->base + SDC_RESP0);
		पूर्ण अन्यथा अणु
			rsp[0] = पढ़ोl(host->base + SDC_RESP0);
		पूर्ण
	पूर्ण

	अगर (!sbc_error && !(events & MSDC_INT_CMDRDY)) अणु
		अगर (events & MSDC_INT_CMDTMO ||
		    (cmd->opcode != MMC_SEND_TUNING_BLOCK &&
		     cmd->opcode != MMC_SEND_TUNING_BLOCK_HS200))
			/*
			 * should not clear fअगरo/पूर्णांकerrupt as the tune data
			 * may have alreay come when cmd19/cmd21 माला_लो response
			 * CRC error.
			 */
			msdc_reset_hw(host);
		अगर (events & MSDC_INT_RSPCRCERR) अणु
			cmd->error = -EILSEQ;
			host->error |= REQ_CMD_EIO;
		पूर्ण अन्यथा अगर (events & MSDC_INT_CMDTMO) अणु
			cmd->error = -ETIMEDOUT;
			host->error |= REQ_CMD_TMO;
		पूर्ण
	पूर्ण
	अगर (cmd->error)
		dev_dbg(host->dev,
				"%s: cmd=%d arg=%08X; rsp %08X; cmd_error=%d\n",
				__func__, cmd->opcode, cmd->arg, rsp[0],
				cmd->error);

	msdc_cmd_next(host, mrq, cmd);
	वापस true;
पूर्ण

/* It is the core layer's responsibility to ensure card status
 * is correct beक्रमe issue a request. but host design करो below
 * checks recommended.
 */
अटल अंतरभूत bool msdc_cmd_is_पढ़ोy(काष्ठा msdc_host *host,
		काष्ठा mmc_request *mrq, काष्ठा mmc_command *cmd)
अणु
	/* The max busy समय we can endure is 20ms */
	अचिन्हित दीर्घ पंचांगo = jअगरfies + msecs_to_jअगरfies(20);

	जबतक ((पढ़ोl(host->base + SDC_STS) & SDC_STS_CMDBUSY) &&
			समय_beक्रमe(jअगरfies, पंचांगo))
		cpu_relax();
	अगर (पढ़ोl(host->base + SDC_STS) & SDC_STS_CMDBUSY) अणु
		dev_err(host->dev, "CMD bus busy detected\n");
		host->error |= REQ_CMD_BUSY;
		msdc_cmd_करोne(host, MSDC_INT_CMDTMO, mrq, cmd);
		वापस false;
	पूर्ण

	अगर (mmc_resp_type(cmd) == MMC_RSP_R1B || cmd->data) अणु
		पंचांगo = jअगरfies + msecs_to_jअगरfies(20);
		/* R1B or with data, should check SDCBUSY */
		जबतक ((पढ़ोl(host->base + SDC_STS) & SDC_STS_SDCBUSY) &&
				समय_beक्रमe(jअगरfies, पंचांगo))
			cpu_relax();
		अगर (पढ़ोl(host->base + SDC_STS) & SDC_STS_SDCBUSY) अणु
			dev_err(host->dev, "Controller busy detected\n");
			host->error |= REQ_CMD_BUSY;
			msdc_cmd_करोne(host, MSDC_INT_CMDTMO, mrq, cmd);
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम msdc_start_command(काष्ठा msdc_host *host,
		काष्ठा mmc_request *mrq, काष्ठा mmc_command *cmd)
अणु
	u32 rawcmd;
	अचिन्हित दीर्घ flags;

	WARN_ON(host->cmd);
	host->cmd = cmd;

	mod_delayed_work(प्रणाली_wq, &host->req_समयout, DAT_TIMEOUT);
	अगर (!msdc_cmd_is_पढ़ोy(host, mrq, cmd))
		वापस;

	अगर ((पढ़ोl(host->base + MSDC_FIFOCS) & MSDC_FIFOCS_TXCNT) >> 16 ||
	    पढ़ोl(host->base + MSDC_FIFOCS) & MSDC_FIFOCS_RXCNT) अणु
		dev_err(host->dev, "TX/RX FIFO non-empty before start of IO. Reset\n");
		msdc_reset_hw(host);
	पूर्ण

	cmd->error = 0;
	rawcmd = msdc_cmd_prepare_raw_cmd(host, mrq, cmd);

	spin_lock_irqsave(&host->lock, flags);
	sdr_set_bits(host->base + MSDC_INTEN, cmd_पूर्णांकs_mask);
	spin_unlock_irqrestore(&host->lock, flags);

	ग_लिखोl(cmd->arg, host->base + SDC_ARG);
	ग_लिखोl(rawcmd, host->base + SDC_CMD);
पूर्ण

अटल व्योम msdc_cmd_next(काष्ठा msdc_host *host,
		काष्ठा mmc_request *mrq, काष्ठा mmc_command *cmd)
अणु
	अगर ((cmd->error &&
	    !(cmd->error == -EILSEQ &&
	      (cmd->opcode == MMC_SEND_TUNING_BLOCK ||
	       cmd->opcode == MMC_SEND_TUNING_BLOCK_HS200))) ||
	    (mrq->sbc && mrq->sbc->error))
		msdc_request_करोne(host, mrq);
	अन्यथा अगर (cmd == mrq->sbc)
		msdc_start_command(host, mrq, mrq->cmd);
	अन्यथा अगर (!cmd->data)
		msdc_request_करोne(host, mrq);
	अन्यथा
		msdc_start_data(host, mrq, cmd, cmd->data);
पूर्ण

अटल व्योम msdc_ops_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा msdc_host *host = mmc_priv(mmc);

	host->error = 0;
	WARN_ON(host->mrq);
	host->mrq = mrq;

	अगर (mrq->data)
		msdc_prepare_data(host, mrq);

	/* अगर SBC is required, we have HW option and SW option.
	 * अगर HW option is enabled, and SBC करोes not have "special" flags,
	 * use HW option,  otherwise use SW option
	 */
	अगर (mrq->sbc && (!mmc_card_mmc(mmc->card) ||
	    (mrq->sbc->arg & 0xFFFF0000)))
		msdc_start_command(host, mrq, mrq->sbc);
	अन्यथा
		msdc_start_command(host, mrq, mrq->cmd);
पूर्ण

अटल व्योम msdc_pre_req(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा msdc_host *host = mmc_priv(mmc);
	काष्ठा mmc_data *data = mrq->data;

	अगर (!data)
		वापस;

	msdc_prepare_data(host, mrq);
	data->host_cookie |= MSDC_ASYNC_FLAG;
पूर्ण

अटल व्योम msdc_post_req(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq,
		पूर्णांक err)
अणु
	काष्ठा msdc_host *host = mmc_priv(mmc);
	काष्ठा mmc_data *data;

	data = mrq->data;
	अगर (!data)
		वापस;
	अगर (data->host_cookie) अणु
		data->host_cookie &= ~MSDC_ASYNC_FLAG;
		msdc_unprepare_data(host, mrq);
	पूर्ण
पूर्ण

अटल व्योम msdc_data_xfer_next(काष्ठा msdc_host *host,
				काष्ठा mmc_request *mrq, काष्ठा mmc_data *data)
अणु
	अगर (mmc_op_multi(mrq->cmd->opcode) && mrq->stop && !mrq->stop->error &&
	    !mrq->sbc)
		msdc_start_command(host, mrq, mrq->stop);
	अन्यथा
		msdc_request_करोne(host, mrq);
पूर्ण

अटल bool msdc_data_xfer_करोne(काष्ठा msdc_host *host, u32 events,
				काष्ठा mmc_request *mrq, काष्ठा mmc_data *data)
अणु
	काष्ठा mmc_command *stop;
	अचिन्हित दीर्घ flags;
	bool करोne;
	अचिन्हित पूर्णांक check_data = events &
	    (MSDC_INT_XFER_COMPL | MSDC_INT_DATCRCERR | MSDC_INT_DATTMO
	     | MSDC_INT_DMA_BDCSERR | MSDC_INT_DMA_GPDCSERR
	     | MSDC_INT_DMA_PROTECT);

	spin_lock_irqsave(&host->lock, flags);
	करोne = !host->data;
	अगर (check_data)
		host->data = शून्य;
	spin_unlock_irqrestore(&host->lock, flags);

	अगर (करोne)
		वापस true;
	stop = data->stop;

	अगर (check_data || (stop && stop->error)) अणु
		dev_dbg(host->dev, "DMA status: 0x%8X\n",
				पढ़ोl(host->base + MSDC_DMA_CFG));
		sdr_set_field(host->base + MSDC_DMA_CTRL, MSDC_DMA_CTRL_STOP,
				1);
		जबतक (पढ़ोl(host->base + MSDC_DMA_CFG) & MSDC_DMA_CFG_STS)
			cpu_relax();
		sdr_clr_bits(host->base + MSDC_INTEN, data_पूर्णांकs_mask);
		dev_dbg(host->dev, "DMA stop\n");

		अगर ((events & MSDC_INT_XFER_COMPL) && (!stop || !stop->error)) अणु
			data->bytes_xfered = data->blocks * data->blksz;
		पूर्ण अन्यथा अणु
			dev_dbg(host->dev, "interrupt events: %x\n", events);
			msdc_reset_hw(host);
			host->error |= REQ_DAT_ERR;
			data->bytes_xfered = 0;

			अगर (events & MSDC_INT_DATTMO)
				data->error = -ETIMEDOUT;
			अन्यथा अगर (events & MSDC_INT_DATCRCERR)
				data->error = -EILSEQ;

			dev_dbg(host->dev, "%s: cmd=%d; blocks=%d",
				__func__, mrq->cmd->opcode, data->blocks);
			dev_dbg(host->dev, "data_error=%d xfer_size=%d\n",
				(पूर्णांक)data->error, data->bytes_xfered);
		पूर्ण

		msdc_data_xfer_next(host, mrq, data);
		करोne = true;
	पूर्ण
	वापस करोne;
पूर्ण

अटल व्योम msdc_set_buswidth(काष्ठा msdc_host *host, u32 width)
अणु
	u32 val = पढ़ोl(host->base + SDC_CFG);

	val &= ~SDC_CFG_BUSWIDTH;

	चयन (width) अणु
	शेष:
	हाल MMC_BUS_WIDTH_1:
		val |= (MSDC_BUS_1BITS << 16);
		अवरोध;
	हाल MMC_BUS_WIDTH_4:
		val |= (MSDC_BUS_4BITS << 16);
		अवरोध;
	हाल MMC_BUS_WIDTH_8:
		val |= (MSDC_BUS_8BITS << 16);
		अवरोध;
	पूर्ण

	ग_लिखोl(val, host->base + SDC_CFG);
	dev_dbg(host->dev, "Bus Width = %d", width);
पूर्ण

अटल पूर्णांक msdc_ops_चयन_volt(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा msdc_host *host = mmc_priv(mmc);
	पूर्णांक ret;

	अगर (!IS_ERR(mmc->supply.vqmmc)) अणु
		अगर (ios->संकेत_voltage != MMC_SIGNAL_VOLTAGE_330 &&
		    ios->संकेत_voltage != MMC_SIGNAL_VOLTAGE_180) अणु
			dev_err(host->dev, "Unsupported signal voltage!\n");
			वापस -EINVAL;
		पूर्ण

		ret = mmc_regulator_set_vqmmc(mmc, ios);
		अगर (ret < 0) अणु
			dev_dbg(host->dev, "Regulator set error %d (%d)\n",
				ret, ios->संकेत_voltage);
			वापस ret;
		पूर्ण

		/* Apply dअगरferent pinctrl settings क्रम dअगरferent संकेत voltage */
		अगर (ios->संकेत_voltage == MMC_SIGNAL_VOLTAGE_180)
			pinctrl_select_state(host->pinctrl, host->pins_uhs);
		अन्यथा
			pinctrl_select_state(host->pinctrl, host->pins_शेष);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक msdc_card_busy(काष्ठा mmc_host *mmc)
अणु
	काष्ठा msdc_host *host = mmc_priv(mmc);
	u32 status = पढ़ोl(host->base + MSDC_PS);

	/* only check अगर data0 is low */
	वापस !(status & BIT(16));
पूर्ण

अटल व्योम msdc_request_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा msdc_host *host = container_of(work, काष्ठा msdc_host,
			req_समयout.work);

	/* simulate HW समयout status */
	dev_err(host->dev, "%s: aborting cmd/data/mrq\n", __func__);
	अगर (host->mrq) अणु
		dev_err(host->dev, "%s: aborting mrq=%p cmd=%d\n", __func__,
				host->mrq, host->mrq->cmd->opcode);
		अगर (host->cmd) अणु
			dev_err(host->dev, "%s: aborting cmd=%d\n",
					__func__, host->cmd->opcode);
			msdc_cmd_करोne(host, MSDC_INT_CMDTMO, host->mrq,
					host->cmd);
		पूर्ण अन्यथा अगर (host->data) अणु
			dev_err(host->dev, "%s: abort data: cmd%d; %d blocks\n",
					__func__, host->mrq->cmd->opcode,
					host->data->blocks);
			msdc_data_xfer_करोne(host, MSDC_INT_DATTMO, host->mrq,
					host->data);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __msdc_enable_sdio_irq(काष्ठा msdc_host *host, पूर्णांक enb)
अणु
	अगर (enb) अणु
		sdr_set_bits(host->base + MSDC_INTEN, MSDC_INTEN_SDIOIRQ);
		sdr_set_bits(host->base + SDC_CFG, SDC_CFG_SDIOIDE);
		अगर (host->dev_comp->recheck_sdio_irq)
			msdc_recheck_sdio_irq(host);
	पूर्ण अन्यथा अणु
		sdr_clr_bits(host->base + MSDC_INTEN, MSDC_INTEN_SDIOIRQ);
		sdr_clr_bits(host->base + SDC_CFG, SDC_CFG_SDIOIDE);
	पूर्ण
पूर्ण

अटल व्योम msdc_enable_sdio_irq(काष्ठा mmc_host *mmc, पूर्णांक enb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा msdc_host *host = mmc_priv(mmc);

	spin_lock_irqsave(&host->lock, flags);
	__msdc_enable_sdio_irq(host, enb);
	spin_unlock_irqrestore(&host->lock, flags);

	अगर (enb)
		pm_runसमय_get_noresume(host->dev);
	अन्यथा
		pm_runसमय_put_noidle(host->dev);
पूर्ण

अटल irqवापस_t msdc_cmdq_irq(काष्ठा msdc_host *host, u32 पूर्णांकsts)
अणु
	काष्ठा mmc_host *mmc = mmc_from_priv(host);
	पूर्णांक cmd_err = 0, dat_err = 0;

	अगर (पूर्णांकsts & MSDC_INT_RSPCRCERR) अणु
		cmd_err = -EILSEQ;
		dev_err(host->dev, "%s: CMD CRC ERR", __func__);
	पूर्ण अन्यथा अगर (पूर्णांकsts & MSDC_INT_CMDTMO) अणु
		cmd_err = -ETIMEDOUT;
		dev_err(host->dev, "%s: CMD TIMEOUT ERR", __func__);
	पूर्ण

	अगर (पूर्णांकsts & MSDC_INT_DATCRCERR) अणु
		dat_err = -EILSEQ;
		dev_err(host->dev, "%s: DATA CRC ERR", __func__);
	पूर्ण अन्यथा अगर (पूर्णांकsts & MSDC_INT_DATTMO) अणु
		dat_err = -ETIMEDOUT;
		dev_err(host->dev, "%s: DATA TIMEOUT ERR", __func__);
	पूर्ण

	अगर (cmd_err || dat_err) अणु
		dev_err(host->dev, "cmd_err = %d, dat_err =%d, intsts = 0x%x",
			cmd_err, dat_err, पूर्णांकsts);
	पूर्ण

	वापस cqhci_irq(mmc, 0, cmd_err, dat_err);
पूर्ण

अटल irqवापस_t msdc_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा msdc_host *host = (काष्ठा msdc_host *) dev_id;
	काष्ठा mmc_host *mmc = mmc_from_priv(host);

	जबतक (true) अणु
		काष्ठा mmc_request *mrq;
		काष्ठा mmc_command *cmd;
		काष्ठा mmc_data *data;
		u32 events, event_mask;

		spin_lock(&host->lock);
		events = पढ़ोl(host->base + MSDC_INT);
		event_mask = पढ़ोl(host->base + MSDC_INTEN);
		अगर ((events & event_mask) & MSDC_INT_SDIOIRQ)
			__msdc_enable_sdio_irq(host, 0);
		/* clear पूर्णांकerrupts */
		ग_लिखोl(events & event_mask, host->base + MSDC_INT);

		mrq = host->mrq;
		cmd = host->cmd;
		data = host->data;
		spin_unlock(&host->lock);

		अगर ((events & event_mask) & MSDC_INT_SDIOIRQ)
			sdio_संकेत_irq(mmc);

		अगर ((events & event_mask) & MSDC_INT_CDSC) अणु
			अगर (host->पूर्णांकernal_cd)
				mmc_detect_change(mmc, msecs_to_jअगरfies(20));
			events &= ~MSDC_INT_CDSC;
		पूर्ण

		अगर (!(events & (event_mask & ~MSDC_INT_SDIOIRQ)))
			अवरोध;

		अगर ((mmc->caps2 & MMC_CAP2_CQE) &&
		    (events & MSDC_INT_CMDQ)) अणु
			msdc_cmdq_irq(host, events);
			/* clear पूर्णांकerrupts */
			ग_लिखोl(events, host->base + MSDC_INT);
			वापस IRQ_HANDLED;
		पूर्ण

		अगर (!mrq) अणु
			dev_err(host->dev,
				"%s: MRQ=NULL; events=%08X; event_mask=%08X\n",
				__func__, events, event_mask);
			WARN_ON(1);
			अवरोध;
		पूर्ण

		dev_dbg(host->dev, "%s: events=%08X\n", __func__, events);

		अगर (cmd)
			msdc_cmd_करोne(host, events, mrq, cmd);
		अन्यथा अगर (data)
			msdc_data_xfer_करोne(host, events, mrq, data);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम msdc_init_hw(काष्ठा msdc_host *host)
अणु
	u32 val;
	u32 tune_reg = host->dev_comp->pad_tune_reg;

	अगर (host->reset) अणु
		reset_control_निश्चित(host->reset);
		usleep_range(10, 50);
		reset_control_deनिश्चित(host->reset);
	पूर्ण

	/* Configure to MMC/SD mode, घड़ी मुक्त running */
	sdr_set_bits(host->base + MSDC_CFG, MSDC_CFG_MODE | MSDC_CFG_CKPDN);

	/* Reset */
	msdc_reset_hw(host);

	/* Disable and clear all पूर्णांकerrupts */
	ग_लिखोl(0, host->base + MSDC_INTEN);
	val = पढ़ोl(host->base + MSDC_INT);
	ग_लिखोl(val, host->base + MSDC_INT);

	/* Configure card detection */
	अगर (host->पूर्णांकernal_cd) अणु
		sdr_set_field(host->base + MSDC_PS, MSDC_PS_CDDEBOUNCE,
			      DEFAULT_DEBOUNCE);
		sdr_set_bits(host->base + MSDC_PS, MSDC_PS_CDEN);
		sdr_set_bits(host->base + MSDC_INTEN, MSDC_INTEN_CDSC);
		sdr_set_bits(host->base + SDC_CFG, SDC_CFG_INSWKUP);
	पूर्ण अन्यथा अणु
		sdr_clr_bits(host->base + SDC_CFG, SDC_CFG_INSWKUP);
		sdr_clr_bits(host->base + MSDC_PS, MSDC_PS_CDEN);
		sdr_clr_bits(host->base + MSDC_INTEN, MSDC_INTEN_CDSC);
	पूर्ण

	अगर (host->top_base) अणु
		ग_लिखोl(0, host->top_base + EMMC_TOP_CONTROL);
		ग_लिखोl(0, host->top_base + EMMC_TOP_CMD);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0, host->base + tune_reg);
	पूर्ण
	ग_लिखोl(0, host->base + MSDC_IOCON);
	sdr_set_field(host->base + MSDC_IOCON, MSDC_IOCON_DDLSEL, 0);
	ग_लिखोl(0x403c0046, host->base + MSDC_PATCH_BIT);
	sdr_set_field(host->base + MSDC_PATCH_BIT, MSDC_CKGEN_MSDC_DLY_SEL, 1);
	ग_लिखोl(0xffff4089, host->base + MSDC_PATCH_BIT1);
	sdr_set_bits(host->base + EMMC50_CFG0, EMMC50_CFG_CFCSTS_SEL);

	अगर (host->dev_comp->stop_clk_fix) अणु
		sdr_set_field(host->base + MSDC_PATCH_BIT1,
			      MSDC_PATCH_BIT1_STOP_DLY, 3);
		sdr_clr_bits(host->base + SDC_FIFO_CFG,
			     SDC_FIFO_CFG_WRVALIDSEL);
		sdr_clr_bits(host->base + SDC_FIFO_CFG,
			     SDC_FIFO_CFG_RDVALIDSEL);
	पूर्ण

	अगर (host->dev_comp->busy_check)
		sdr_clr_bits(host->base + MSDC_PATCH_BIT1, (1 << 7));

	अगर (host->dev_comp->async_fअगरo) अणु
		sdr_set_field(host->base + MSDC_PATCH_BIT2,
			      MSDC_PB2_RESPWAIT, 3);
		अगर (host->dev_comp->enhance_rx) अणु
			अगर (host->top_base)
				sdr_set_bits(host->top_base + EMMC_TOP_CONTROL,
					     SDC_RX_ENH_EN);
			अन्यथा
				sdr_set_bits(host->base + SDC_ADV_CFG0,
					     SDC_RX_ENHANCE_EN);
		पूर्ण अन्यथा अणु
			sdr_set_field(host->base + MSDC_PATCH_BIT2,
				      MSDC_PB2_RESPSTSENSEL, 2);
			sdr_set_field(host->base + MSDC_PATCH_BIT2,
				      MSDC_PB2_CRCSTSENSEL, 2);
		पूर्ण
		/* use async fअगरo, then no need tune पूर्णांकernal delay */
		sdr_clr_bits(host->base + MSDC_PATCH_BIT2,
			     MSDC_PATCH_BIT2_CFGRESP);
		sdr_set_bits(host->base + MSDC_PATCH_BIT2,
			     MSDC_PATCH_BIT2_CFGCRCSTS);
	पूर्ण

	अगर (host->dev_comp->support_64g)
		sdr_set_bits(host->base + MSDC_PATCH_BIT2,
			     MSDC_PB2_SUPPORT_64G);
	अगर (host->dev_comp->data_tune) अणु
		अगर (host->top_base) अणु
			sdr_set_bits(host->top_base + EMMC_TOP_CONTROL,
				     PAD_DAT_RD_RXDLY_SEL);
			sdr_clr_bits(host->top_base + EMMC_TOP_CONTROL,
				     DATA_K_VALUE_SEL);
			sdr_set_bits(host->top_base + EMMC_TOP_CMD,
				     PAD_CMD_RD_RXDLY_SEL);
		पूर्ण अन्यथा अणु
			sdr_set_bits(host->base + tune_reg,
				     MSDC_PAD_TUNE_RD_SEL |
				     MSDC_PAD_TUNE_CMD_SEL);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* choose घड़ी tune */
		अगर (host->top_base)
			sdr_set_bits(host->top_base + EMMC_TOP_CONTROL,
				     PAD_RXDLY_SEL);
		अन्यथा
			sdr_set_bits(host->base + tune_reg,
				     MSDC_PAD_TUNE_RXDLYSEL);
	पूर्ण

	/* Configure to enable SDIO mode.
	 * it's must otherwise sdio cmd5 failed
	 */
	sdr_set_bits(host->base + SDC_CFG, SDC_CFG_SDIO);

	/* Config SDIO device detect पूर्णांकerrupt function */
	sdr_clr_bits(host->base + SDC_CFG, SDC_CFG_SDIOIDE);
	sdr_set_bits(host->base + SDC_ADV_CFG0, SDC_DAT1_IRQ_TRIGGER);

	/* Configure to शेष data समयout */
	sdr_set_field(host->base + SDC_CFG, SDC_CFG_DTOC, 3);

	host->def_tune_para.iocon = पढ़ोl(host->base + MSDC_IOCON);
	host->saved_tune_para.iocon = पढ़ोl(host->base + MSDC_IOCON);
	अगर (host->top_base) अणु
		host->def_tune_para.emmc_top_control =
			पढ़ोl(host->top_base + EMMC_TOP_CONTROL);
		host->def_tune_para.emmc_top_cmd =
			पढ़ोl(host->top_base + EMMC_TOP_CMD);
		host->saved_tune_para.emmc_top_control =
			पढ़ोl(host->top_base + EMMC_TOP_CONTROL);
		host->saved_tune_para.emmc_top_cmd =
			पढ़ोl(host->top_base + EMMC_TOP_CMD);
	पूर्ण अन्यथा अणु
		host->def_tune_para.pad_tune = पढ़ोl(host->base + tune_reg);
		host->saved_tune_para.pad_tune = पढ़ोl(host->base + tune_reg);
	पूर्ण
	dev_dbg(host->dev, "init hardware done!");
पूर्ण

अटल व्योम msdc_deinit_hw(काष्ठा msdc_host *host)
अणु
	u32 val;

	अगर (host->पूर्णांकernal_cd) अणु
		/* Disabled card-detect */
		sdr_clr_bits(host->base + MSDC_PS, MSDC_PS_CDEN);
		sdr_clr_bits(host->base + SDC_CFG, SDC_CFG_INSWKUP);
	पूर्ण

	/* Disable and clear all पूर्णांकerrupts */
	ग_लिखोl(0, host->base + MSDC_INTEN);

	val = पढ़ोl(host->base + MSDC_INT);
	ग_लिखोl(val, host->base + MSDC_INT);
पूर्ण

/* init gpd and bd list in msdc_drv_probe */
अटल व्योम msdc_init_gpd_bd(काष्ठा msdc_host *host, काष्ठा msdc_dma *dma)
अणु
	काष्ठा mt_gpdma_desc *gpd = dma->gpd;
	काष्ठा mt_bdma_desc *bd = dma->bd;
	dma_addr_t dma_addr;
	पूर्णांक i;

	स_रखो(gpd, 0, माप(काष्ठा mt_gpdma_desc) * 2);

	dma_addr = dma->gpd_addr + माप(काष्ठा mt_gpdma_desc);
	gpd->gpd_info = GPDMA_DESC_BDP; /* hwo, cs, bd poपूर्णांकer */
	/* gpd->next is must set क्रम desc DMA
	 * That's why must alloc 2 gpd काष्ठाure.
	 */
	gpd->next = lower_32_bits(dma_addr);
	अगर (host->dev_comp->support_64g)
		gpd->gpd_info |= (upper_32_bits(dma_addr) & 0xf) << 24;

	dma_addr = dma->bd_addr;
	gpd->ptr = lower_32_bits(dma->bd_addr); /* physical address */
	अगर (host->dev_comp->support_64g)
		gpd->gpd_info |= (upper_32_bits(dma_addr) & 0xf) << 28;

	स_रखो(bd, 0, माप(काष्ठा mt_bdma_desc) * MAX_BD_NUM);
	क्रम (i = 0; i < (MAX_BD_NUM - 1); i++) अणु
		dma_addr = dma->bd_addr + माप(*bd) * (i + 1);
		bd[i].next = lower_32_bits(dma_addr);
		अगर (host->dev_comp->support_64g)
			bd[i].bd_info |= (upper_32_bits(dma_addr) & 0xf) << 24;
	पूर्ण
पूर्ण

अटल व्योम msdc_ops_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा msdc_host *host = mmc_priv(mmc);
	पूर्णांक ret;

	msdc_set_buswidth(host, ios->bus_width);

	/* Suspend/Resume will करो घातer off/on */
	चयन (ios->घातer_mode) अणु
	हाल MMC_POWER_UP:
		अगर (!IS_ERR(mmc->supply.vmmc)) अणु
			msdc_init_hw(host);
			ret = mmc_regulator_set_ocr(mmc, mmc->supply.vmmc,
					ios->vdd);
			अगर (ret) अणु
				dev_err(host->dev, "Failed to set vmmc power!\n");
				वापस;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल MMC_POWER_ON:
		अगर (!IS_ERR(mmc->supply.vqmmc) && !host->vqmmc_enabled) अणु
			ret = regulator_enable(mmc->supply.vqmmc);
			अगर (ret)
				dev_err(host->dev, "Failed to set vqmmc power!\n");
			अन्यथा
				host->vqmmc_enabled = true;
		पूर्ण
		अवरोध;
	हाल MMC_POWER_OFF:
		अगर (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);

		अगर (!IS_ERR(mmc->supply.vqmmc) && host->vqmmc_enabled) अणु
			regulator_disable(mmc->supply.vqmmc);
			host->vqmmc_enabled = false;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (host->mclk != ios->घड़ी || host->timing != ios->timing)
		msdc_set_mclk(host, ios->timing, ios->घड़ी);
पूर्ण

अटल u32 test_delay_bit(u32 delay, u32 bit)
अणु
	bit %= PAD_DELAY_MAX;
	वापस delay & (1 << bit);
पूर्ण

अटल पूर्णांक get_delay_len(u32 delay, u32 start_bit)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < (PAD_DELAY_MAX - start_bit); i++) अणु
		अगर (test_delay_bit(delay, start_bit + i) == 0)
			वापस i;
	पूर्ण
	वापस PAD_DELAY_MAX - start_bit;
पूर्ण

अटल काष्ठा msdc_delay_phase get_best_delay(काष्ठा msdc_host *host, u32 delay)
अणु
	पूर्णांक start = 0, len = 0;
	पूर्णांक start_final = 0, len_final = 0;
	u8 final_phase = 0xff;
	काष्ठा msdc_delay_phase delay_phase = अणु 0, पूर्ण;

	अगर (delay == 0) अणु
		dev_err(host->dev, "phase error: [map:%x]\n", delay);
		delay_phase.final_phase = final_phase;
		वापस delay_phase;
	पूर्ण

	जबतक (start < PAD_DELAY_MAX) अणु
		len = get_delay_len(delay, start);
		अगर (len_final < len) अणु
			start_final = start;
			len_final = len;
		पूर्ण
		start += len ? len : 1;
		अगर (len >= 12 && start_final < 4)
			अवरोध;
	पूर्ण

	/* The rule is that to find the smallest delay cell */
	अगर (start_final == 0)
		final_phase = (start_final + len_final / 3) % PAD_DELAY_MAX;
	अन्यथा
		final_phase = (start_final + len_final / 2) % PAD_DELAY_MAX;
	dev_info(host->dev, "phase: [map:%x] [maxlen:%d] [final:%d]\n",
		 delay, len_final, final_phase);

	delay_phase.maxlen = len_final;
	delay_phase.start = start_final;
	delay_phase.final_phase = final_phase;
	वापस delay_phase;
पूर्ण

अटल अंतरभूत व्योम msdc_set_cmd_delay(काष्ठा msdc_host *host, u32 value)
अणु
	u32 tune_reg = host->dev_comp->pad_tune_reg;

	अगर (host->top_base)
		sdr_set_field(host->top_base + EMMC_TOP_CMD, PAD_CMD_RXDLY,
			      value);
	अन्यथा
		sdr_set_field(host->base + tune_reg, MSDC_PAD_TUNE_CMDRDLY,
			      value);
पूर्ण

अटल अंतरभूत व्योम msdc_set_data_delay(काष्ठा msdc_host *host, u32 value)
अणु
	u32 tune_reg = host->dev_comp->pad_tune_reg;

	अगर (host->top_base)
		sdr_set_field(host->top_base + EMMC_TOP_CONTROL,
			      PAD_DAT_RD_RXDLY, value);
	अन्यथा
		sdr_set_field(host->base + tune_reg, MSDC_PAD_TUNE_DATRRDLY,
			      value);
पूर्ण

अटल पूर्णांक msdc_tune_response(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा msdc_host *host = mmc_priv(mmc);
	u32 rise_delay = 0, fall_delay = 0;
	काष्ठा msdc_delay_phase final_rise_delay, final_fall_delay = अणु 0,पूर्ण;
	काष्ठा msdc_delay_phase पूर्णांकernal_delay_phase;
	u8 final_delay, final_maxlen;
	u32 पूर्णांकernal_delay = 0;
	u32 tune_reg = host->dev_comp->pad_tune_reg;
	पूर्णांक cmd_err;
	पूर्णांक i, j;

	अगर (mmc->ios.timing == MMC_TIMING_MMC_HS200 ||
	    mmc->ios.timing == MMC_TIMING_UHS_SDR104)
		sdr_set_field(host->base + tune_reg,
			      MSDC_PAD_TUNE_CMDRRDLY,
			      host->hs200_cmd_पूर्णांक_delay);

	sdr_clr_bits(host->base + MSDC_IOCON, MSDC_IOCON_RSPL);
	क्रम (i = 0 ; i < PAD_DELAY_MAX; i++) अणु
		msdc_set_cmd_delay(host, i);
		/*
		 * Using the same parameters, it may someबार pass the test,
		 * but someबार it may fail. To make sure the parameters are
		 * more stable, we test each set of parameters 3 बार.
		 */
		क्रम (j = 0; j < 3; j++) अणु
			mmc_send_tuning(mmc, opcode, &cmd_err);
			अगर (!cmd_err) अणु
				rise_delay |= (1 << i);
			पूर्ण अन्यथा अणु
				rise_delay &= ~(1 << i);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	final_rise_delay = get_best_delay(host, rise_delay);
	/* अगर rising edge has enough margin, then करो not scan falling edge */
	अगर (final_rise_delay.maxlen >= 12 ||
	    (final_rise_delay.start == 0 && final_rise_delay.maxlen >= 4))
		जाओ skip_fall;

	sdr_set_bits(host->base + MSDC_IOCON, MSDC_IOCON_RSPL);
	क्रम (i = 0; i < PAD_DELAY_MAX; i++) अणु
		msdc_set_cmd_delay(host, i);
		/*
		 * Using the same parameters, it may someबार pass the test,
		 * but someबार it may fail. To make sure the parameters are
		 * more stable, we test each set of parameters 3 बार.
		 */
		क्रम (j = 0; j < 3; j++) अणु
			mmc_send_tuning(mmc, opcode, &cmd_err);
			अगर (!cmd_err) अणु
				fall_delay |= (1 << i);
			पूर्ण अन्यथा अणु
				fall_delay &= ~(1 << i);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	final_fall_delay = get_best_delay(host, fall_delay);

skip_fall:
	final_maxlen = max(final_rise_delay.maxlen, final_fall_delay.maxlen);
	अगर (final_fall_delay.maxlen >= 12 && final_fall_delay.start < 4)
		final_maxlen = final_fall_delay.maxlen;
	अगर (final_maxlen == final_rise_delay.maxlen) अणु
		sdr_clr_bits(host->base + MSDC_IOCON, MSDC_IOCON_RSPL);
		final_delay = final_rise_delay.final_phase;
	पूर्ण अन्यथा अणु
		sdr_set_bits(host->base + MSDC_IOCON, MSDC_IOCON_RSPL);
		final_delay = final_fall_delay.final_phase;
	पूर्ण
	msdc_set_cmd_delay(host, final_delay);

	अगर (host->dev_comp->async_fअगरo || host->hs200_cmd_पूर्णांक_delay)
		जाओ skip_पूर्णांकernal;

	क्रम (i = 0; i < PAD_DELAY_MAX; i++) अणु
		sdr_set_field(host->base + tune_reg,
			      MSDC_PAD_TUNE_CMDRRDLY, i);
		mmc_send_tuning(mmc, opcode, &cmd_err);
		अगर (!cmd_err)
			पूर्णांकernal_delay |= (1 << i);
	पूर्ण
	dev_dbg(host->dev, "Final internal delay: 0x%x\n", पूर्णांकernal_delay);
	पूर्णांकernal_delay_phase = get_best_delay(host, पूर्णांकernal_delay);
	sdr_set_field(host->base + tune_reg, MSDC_PAD_TUNE_CMDRRDLY,
		      पूर्णांकernal_delay_phase.final_phase);
skip_पूर्णांकernal:
	dev_dbg(host->dev, "Final cmd pad delay: %x\n", final_delay);
	वापस final_delay == 0xff ? -EIO : 0;
पूर्ण

अटल पूर्णांक hs400_tune_response(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा msdc_host *host = mmc_priv(mmc);
	u32 cmd_delay = 0;
	काष्ठा msdc_delay_phase final_cmd_delay = अणु 0,पूर्ण;
	u8 final_delay;
	पूर्णांक cmd_err;
	पूर्णांक i, j;

	/* select EMMC50 PAD CMD tune */
	sdr_set_bits(host->base + PAD_CMD_TUNE, BIT(0));
	sdr_set_field(host->base + MSDC_PATCH_BIT1, MSDC_PATCH_BIT1_CMDTA, 2);

	अगर (mmc->ios.timing == MMC_TIMING_MMC_HS200 ||
	    mmc->ios.timing == MMC_TIMING_UHS_SDR104)
		sdr_set_field(host->base + MSDC_PAD_TUNE,
			      MSDC_PAD_TUNE_CMDRRDLY,
			      host->hs200_cmd_पूर्णांक_delay);

	अगर (host->hs400_cmd_resp_sel_rising)
		sdr_clr_bits(host->base + MSDC_IOCON, MSDC_IOCON_RSPL);
	अन्यथा
		sdr_set_bits(host->base + MSDC_IOCON, MSDC_IOCON_RSPL);
	क्रम (i = 0 ; i < PAD_DELAY_MAX; i++) अणु
		sdr_set_field(host->base + PAD_CMD_TUNE,
			      PAD_CMD_TUNE_RX_DLY3, i);
		/*
		 * Using the same parameters, it may someबार pass the test,
		 * but someबार it may fail. To make sure the parameters are
		 * more stable, we test each set of parameters 3 बार.
		 */
		क्रम (j = 0; j < 3; j++) अणु
			mmc_send_tuning(mmc, opcode, &cmd_err);
			अगर (!cmd_err) अणु
				cmd_delay |= (1 << i);
			पूर्ण अन्यथा अणु
				cmd_delay &= ~(1 << i);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	final_cmd_delay = get_best_delay(host, cmd_delay);
	sdr_set_field(host->base + PAD_CMD_TUNE, PAD_CMD_TUNE_RX_DLY3,
		      final_cmd_delay.final_phase);
	final_delay = final_cmd_delay.final_phase;

	dev_dbg(host->dev, "Final cmd pad delay: %x\n", final_delay);
	वापस final_delay == 0xff ? -EIO : 0;
पूर्ण

अटल पूर्णांक msdc_tune_data(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा msdc_host *host = mmc_priv(mmc);
	u32 rise_delay = 0, fall_delay = 0;
	काष्ठा msdc_delay_phase final_rise_delay, final_fall_delay = अणु 0,पूर्ण;
	u8 final_delay, final_maxlen;
	पूर्णांक i, ret;

	sdr_set_field(host->base + MSDC_PATCH_BIT, MSDC_INT_DAT_LATCH_CK_SEL,
		      host->latch_ck);
	sdr_clr_bits(host->base + MSDC_IOCON, MSDC_IOCON_DSPL);
	sdr_clr_bits(host->base + MSDC_IOCON, MSDC_IOCON_W_DSPL);
	क्रम (i = 0 ; i < PAD_DELAY_MAX; i++) अणु
		msdc_set_data_delay(host, i);
		ret = mmc_send_tuning(mmc, opcode, शून्य);
		अगर (!ret)
			rise_delay |= (1 << i);
	पूर्ण
	final_rise_delay = get_best_delay(host, rise_delay);
	/* अगर rising edge has enough margin, then करो not scan falling edge */
	अगर (final_rise_delay.maxlen >= 12 ||
	    (final_rise_delay.start == 0 && final_rise_delay.maxlen >= 4))
		जाओ skip_fall;

	sdr_set_bits(host->base + MSDC_IOCON, MSDC_IOCON_DSPL);
	sdr_set_bits(host->base + MSDC_IOCON, MSDC_IOCON_W_DSPL);
	क्रम (i = 0; i < PAD_DELAY_MAX; i++) अणु
		msdc_set_data_delay(host, i);
		ret = mmc_send_tuning(mmc, opcode, शून्य);
		अगर (!ret)
			fall_delay |= (1 << i);
	पूर्ण
	final_fall_delay = get_best_delay(host, fall_delay);

skip_fall:
	final_maxlen = max(final_rise_delay.maxlen, final_fall_delay.maxlen);
	अगर (final_maxlen == final_rise_delay.maxlen) अणु
		sdr_clr_bits(host->base + MSDC_IOCON, MSDC_IOCON_DSPL);
		sdr_clr_bits(host->base + MSDC_IOCON, MSDC_IOCON_W_DSPL);
		final_delay = final_rise_delay.final_phase;
	पूर्ण अन्यथा अणु
		sdr_set_bits(host->base + MSDC_IOCON, MSDC_IOCON_DSPL);
		sdr_set_bits(host->base + MSDC_IOCON, MSDC_IOCON_W_DSPL);
		final_delay = final_fall_delay.final_phase;
	पूर्ण
	msdc_set_data_delay(host, final_delay);

	dev_dbg(host->dev, "Final data pad delay: %x\n", final_delay);
	वापस final_delay == 0xff ? -EIO : 0;
पूर्ण

/*
 * MSDC IP which supports data tune + async fअगरo can करो CMD/DAT tune
 * together, which can save the tuning समय.
 */
अटल पूर्णांक msdc_tune_together(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा msdc_host *host = mmc_priv(mmc);
	u32 rise_delay = 0, fall_delay = 0;
	काष्ठा msdc_delay_phase final_rise_delay, final_fall_delay = अणु 0,पूर्ण;
	u8 final_delay, final_maxlen;
	पूर्णांक i, ret;

	sdr_set_field(host->base + MSDC_PATCH_BIT, MSDC_INT_DAT_LATCH_CK_SEL,
		      host->latch_ck);

	sdr_clr_bits(host->base + MSDC_IOCON, MSDC_IOCON_RSPL);
	sdr_clr_bits(host->base + MSDC_IOCON,
		     MSDC_IOCON_DSPL | MSDC_IOCON_W_DSPL);
	क्रम (i = 0 ; i < PAD_DELAY_MAX; i++) अणु
		msdc_set_cmd_delay(host, i);
		msdc_set_data_delay(host, i);
		ret = mmc_send_tuning(mmc, opcode, शून्य);
		अगर (!ret)
			rise_delay |= (1 << i);
	पूर्ण
	final_rise_delay = get_best_delay(host, rise_delay);
	/* अगर rising edge has enough margin, then करो not scan falling edge */
	अगर (final_rise_delay.maxlen >= 12 ||
	    (final_rise_delay.start == 0 && final_rise_delay.maxlen >= 4))
		जाओ skip_fall;

	sdr_set_bits(host->base + MSDC_IOCON, MSDC_IOCON_RSPL);
	sdr_set_bits(host->base + MSDC_IOCON,
		     MSDC_IOCON_DSPL | MSDC_IOCON_W_DSPL);
	क्रम (i = 0; i < PAD_DELAY_MAX; i++) अणु
		msdc_set_cmd_delay(host, i);
		msdc_set_data_delay(host, i);
		ret = mmc_send_tuning(mmc, opcode, शून्य);
		अगर (!ret)
			fall_delay |= (1 << i);
	पूर्ण
	final_fall_delay = get_best_delay(host, fall_delay);

skip_fall:
	final_maxlen = max(final_rise_delay.maxlen, final_fall_delay.maxlen);
	अगर (final_maxlen == final_rise_delay.maxlen) अणु
		sdr_clr_bits(host->base + MSDC_IOCON, MSDC_IOCON_RSPL);
		sdr_clr_bits(host->base + MSDC_IOCON,
			     MSDC_IOCON_DSPL | MSDC_IOCON_W_DSPL);
		final_delay = final_rise_delay.final_phase;
	पूर्ण अन्यथा अणु
		sdr_set_bits(host->base + MSDC_IOCON, MSDC_IOCON_RSPL);
		sdr_set_bits(host->base + MSDC_IOCON,
			     MSDC_IOCON_DSPL | MSDC_IOCON_W_DSPL);
		final_delay = final_fall_delay.final_phase;
	पूर्ण

	msdc_set_cmd_delay(host, final_delay);
	msdc_set_data_delay(host, final_delay);

	dev_dbg(host->dev, "Final pad delay: %x\n", final_delay);
	वापस final_delay == 0xff ? -EIO : 0;
पूर्ण

अटल पूर्णांक msdc_execute_tuning(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा msdc_host *host = mmc_priv(mmc);
	पूर्णांक ret;
	u32 tune_reg = host->dev_comp->pad_tune_reg;

	अगर (host->dev_comp->data_tune && host->dev_comp->async_fअगरo) अणु
		ret = msdc_tune_together(mmc, opcode);
		अगर (host->hs400_mode) अणु
			sdr_clr_bits(host->base + MSDC_IOCON,
				     MSDC_IOCON_DSPL | MSDC_IOCON_W_DSPL);
			msdc_set_data_delay(host, 0);
		पूर्ण
		जाओ tune_करोne;
	पूर्ण
	अगर (host->hs400_mode &&
	    host->dev_comp->hs400_tune)
		ret = hs400_tune_response(mmc, opcode);
	अन्यथा
		ret = msdc_tune_response(mmc, opcode);
	अगर (ret == -EIO) अणु
		dev_err(host->dev, "Tune response fail!\n");
		वापस ret;
	पूर्ण
	अगर (host->hs400_mode == false) अणु
		ret = msdc_tune_data(mmc, opcode);
		अगर (ret == -EIO)
			dev_err(host->dev, "Tune data fail!\n");
	पूर्ण

tune_करोne:
	host->saved_tune_para.iocon = पढ़ोl(host->base + MSDC_IOCON);
	host->saved_tune_para.pad_tune = पढ़ोl(host->base + tune_reg);
	host->saved_tune_para.pad_cmd_tune = पढ़ोl(host->base + PAD_CMD_TUNE);
	अगर (host->top_base) अणु
		host->saved_tune_para.emmc_top_control = पढ़ोl(host->top_base +
				EMMC_TOP_CONTROL);
		host->saved_tune_para.emmc_top_cmd = पढ़ोl(host->top_base +
				EMMC_TOP_CMD);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक msdc_prepare_hs400_tuning(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा msdc_host *host = mmc_priv(mmc);
	host->hs400_mode = true;

	अगर (host->top_base)
		ग_लिखोl(host->hs400_ds_delay,
		       host->top_base + EMMC50_PAD_DS_TUNE);
	अन्यथा
		ग_लिखोl(host->hs400_ds_delay, host->base + PAD_DS_TUNE);
	/* hs400 mode must set it to 0 */
	sdr_clr_bits(host->base + MSDC_PATCH_BIT2, MSDC_PATCH_BIT2_CFGCRCSTS);
	/* to improve पढ़ो perक्रमmance, set outstanding to 2 */
	sdr_set_field(host->base + EMMC50_CFG3, EMMC50_CFG3_OUTS_WR, 2);

	वापस 0;
पूर्ण

अटल व्योम msdc_hw_reset(काष्ठा mmc_host *mmc)
अणु
	काष्ठा msdc_host *host = mmc_priv(mmc);

	sdr_set_bits(host->base + EMMC_IOCON, 1);
	udelay(10); /* 10us is enough */
	sdr_clr_bits(host->base + EMMC_IOCON, 1);
पूर्ण

अटल व्योम msdc_ack_sdio_irq(काष्ठा mmc_host *mmc)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा msdc_host *host = mmc_priv(mmc);

	spin_lock_irqsave(&host->lock, flags);
	__msdc_enable_sdio_irq(host, 1);
	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल पूर्णांक msdc_get_cd(काष्ठा mmc_host *mmc)
अणु
	काष्ठा msdc_host *host = mmc_priv(mmc);
	पूर्णांक val;

	अगर (mmc->caps & MMC_CAP_NONREMOVABLE)
		वापस 1;

	अगर (!host->पूर्णांकernal_cd)
		वापस mmc_gpio_get_cd(mmc);

	val = पढ़ोl(host->base + MSDC_PS) & MSDC_PS_CDSTS;
	अगर (mmc->caps2 & MMC_CAP2_CD_ACTIVE_HIGH)
		वापस !!val;
	अन्यथा
		वापस !val;
पूर्ण

अटल व्योम msdc_hs400_enhanced_strobe(काष्ठा mmc_host *mmc,
				       काष्ठा mmc_ios *ios)
अणु
	काष्ठा msdc_host *host = mmc_priv(mmc);

	अगर (ios->enhanced_strobe) अणु
		msdc_prepare_hs400_tuning(mmc, ios);
		sdr_set_field(host->base + EMMC50_CFG0, EMMC50_CFG_PADCMD_LATCHCK, 1);
		sdr_set_field(host->base + EMMC50_CFG0, EMMC50_CFG_CMD_RESP_SEL, 1);
		sdr_set_field(host->base + EMMC50_CFG1, EMMC50_CFG1_DS_CFG, 1);

		sdr_clr_bits(host->base + CQHCI_SETTING, CQHCI_RD_CMD_WND_SEL);
		sdr_clr_bits(host->base + CQHCI_SETTING, CQHCI_WR_CMD_WND_SEL);
		sdr_clr_bits(host->base + EMMC51_CFG0, CMDQ_RDAT_CNT);
	पूर्ण अन्यथा अणु
		sdr_set_field(host->base + EMMC50_CFG0, EMMC50_CFG_PADCMD_LATCHCK, 0);
		sdr_set_field(host->base + EMMC50_CFG0, EMMC50_CFG_CMD_RESP_SEL, 0);
		sdr_set_field(host->base + EMMC50_CFG1, EMMC50_CFG1_DS_CFG, 0);

		sdr_set_bits(host->base + CQHCI_SETTING, CQHCI_RD_CMD_WND_SEL);
		sdr_set_bits(host->base + CQHCI_SETTING, CQHCI_WR_CMD_WND_SEL);
		sdr_set_field(host->base + EMMC51_CFG0, CMDQ_RDAT_CNT, 0xb4);
	पूर्ण
पूर्ण

अटल व्योम msdc_cqe_enable(काष्ठा mmc_host *mmc)
अणु
	काष्ठा msdc_host *host = mmc_priv(mmc);

	/* enable cmdq irq */
	ग_लिखोl(MSDC_INT_CMDQ, host->base + MSDC_INTEN);
	/* enable busy check */
	sdr_set_bits(host->base + MSDC_PATCH_BIT1, MSDC_PB1_BUSY_CHECK_SEL);
	/* शेष ग_लिखो data / busy समयout 20s */
	msdc_set_busy_समयout(host, 20 * 1000000000ULL, 0);
	/* शेष पढ़ो data समयout 1s */
	msdc_set_समयout(host, 1000000000ULL, 0);
पूर्ण

अटल व्योम msdc_cqe_disable(काष्ठा mmc_host *mmc, bool recovery)
अणु
	काष्ठा msdc_host *host = mmc_priv(mmc);

	/* disable cmdq irq */
	sdr_clr_bits(host->base + MSDC_INTEN, MSDC_INT_CMDQ);
	/* disable busy check */
	sdr_clr_bits(host->base + MSDC_PATCH_BIT1, MSDC_PB1_BUSY_CHECK_SEL);

	अगर (recovery) अणु
		sdr_set_field(host->base + MSDC_DMA_CTRL,
			      MSDC_DMA_CTRL_STOP, 1);
		msdc_reset_hw(host);
	पूर्ण
पूर्ण

अटल व्योम msdc_cqe_pre_enable(काष्ठा mmc_host *mmc)
अणु
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;
	u32 reg;

	reg = cqhci_पढ़ोl(cq_host, CQHCI_CFG);
	reg |= CQHCI_ENABLE;
	cqhci_ग_लिखोl(cq_host, reg, CQHCI_CFG);
पूर्ण

अटल व्योम msdc_cqe_post_disable(काष्ठा mmc_host *mmc)
अणु
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;
	u32 reg;

	reg = cqhci_पढ़ोl(cq_host, CQHCI_CFG);
	reg &= ~CQHCI_ENABLE;
	cqhci_ग_लिखोl(cq_host, reg, CQHCI_CFG);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops mt_msdc_ops = अणु
	.post_req = msdc_post_req,
	.pre_req = msdc_pre_req,
	.request = msdc_ops_request,
	.set_ios = msdc_ops_set_ios,
	.get_ro = mmc_gpio_get_ro,
	.get_cd = msdc_get_cd,
	.hs400_enhanced_strobe = msdc_hs400_enhanced_strobe,
	.enable_sdio_irq = msdc_enable_sdio_irq,
	.ack_sdio_irq = msdc_ack_sdio_irq,
	.start_संकेत_voltage_चयन = msdc_ops_चयन_volt,
	.card_busy = msdc_card_busy,
	.execute_tuning = msdc_execute_tuning,
	.prepare_hs400_tuning = msdc_prepare_hs400_tuning,
	.hw_reset = msdc_hw_reset,
पूर्ण;

अटल स्थिर काष्ठा cqhci_host_ops msdc_cmdq_ops = अणु
	.enable         = msdc_cqe_enable,
	.disable        = msdc_cqe_disable,
	.pre_enable = msdc_cqe_pre_enable,
	.post_disable = msdc_cqe_post_disable,
पूर्ण;

अटल व्योम msdc_of_property_parse(काष्ठा platक्रमm_device *pdev,
				   काष्ठा msdc_host *host)
अणु
	of_property_पढ़ो_u32(pdev->dev.of_node, "mediatek,latch-ck",
			     &host->latch_ck);

	of_property_पढ़ो_u32(pdev->dev.of_node, "hs400-ds-delay",
			     &host->hs400_ds_delay);

	of_property_पढ़ो_u32(pdev->dev.of_node, "mediatek,hs200-cmd-int-delay",
			     &host->hs200_cmd_पूर्णांक_delay);

	of_property_पढ़ो_u32(pdev->dev.of_node, "mediatek,hs400-cmd-int-delay",
			     &host->hs400_cmd_पूर्णांक_delay);

	अगर (of_property_पढ़ो_bool(pdev->dev.of_node,
				  "mediatek,hs400-cmd-resp-sel-rising"))
		host->hs400_cmd_resp_sel_rising = true;
	अन्यथा
		host->hs400_cmd_resp_sel_rising = false;

	अगर (of_property_पढ़ो_bool(pdev->dev.of_node,
				  "supports-cqe"))
		host->cqhci = true;
	अन्यथा
		host->cqhci = false;
पूर्ण

अटल पूर्णांक msdc_of_घड़ी_parse(काष्ठा platक्रमm_device *pdev,
			       काष्ठा msdc_host *host)
अणु
	पूर्णांक ret;

	host->src_clk = devm_clk_get(&pdev->dev, "source");
	अगर (IS_ERR(host->src_clk))
		वापस PTR_ERR(host->src_clk);

	host->h_clk = devm_clk_get(&pdev->dev, "hclk");
	अगर (IS_ERR(host->h_clk))
		वापस PTR_ERR(host->h_clk);

	host->bus_clk = devm_clk_get_optional(&pdev->dev, "bus_clk");
	अगर (IS_ERR(host->bus_clk))
		host->bus_clk = शून्य;

	/*source घड़ी control gate is optional घड़ी*/
	host->src_clk_cg = devm_clk_get_optional(&pdev->dev, "source_cg");
	अगर (IS_ERR(host->src_clk_cg))
		host->src_clk_cg = शून्य;

	host->sys_clk_cg = devm_clk_get_optional(&pdev->dev, "sys_cg");
	अगर (IS_ERR(host->sys_clk_cg))
		host->sys_clk_cg = शून्य;

	/* If present, always enable क्रम this घड़ी gate */
	clk_prepare_enable(host->sys_clk_cg);

	host->bulk_clks[0].id = "pclk_cg";
	host->bulk_clks[1].id = "axi_cg";
	host->bulk_clks[2].id = "ahb_cg";
	ret = devm_clk_bulk_get_optional(&pdev->dev, MSDC_NR_CLOCKS,
					 host->bulk_clks);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot get pclk/axi/ahb clock gates\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक msdc_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_host *mmc;
	काष्ठा msdc_host *host;
	काष्ठा resource *res;
	पूर्णांक ret;

	अगर (!pdev->dev.of_node) अणु
		dev_err(&pdev->dev, "No DT found\n");
		वापस -EINVAL;
	पूर्ण

	/* Allocate MMC host क्रम this device */
	mmc = mmc_alloc_host(माप(काष्ठा msdc_host), &pdev->dev);
	अगर (!mmc)
		वापस -ENOMEM;

	host = mmc_priv(mmc);
	ret = mmc_of_parse(mmc);
	अगर (ret)
		जाओ host_मुक्त;

	host->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(host->base)) अणु
		ret = PTR_ERR(host->base);
		जाओ host_मुक्त;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (res) अणु
		host->top_base = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(host->top_base))
			host->top_base = शून्य;
	पूर्ण

	ret = mmc_regulator_get_supply(mmc);
	अगर (ret)
		जाओ host_मुक्त;

	ret = msdc_of_घड़ी_parse(pdev, host);
	अगर (ret)
		जाओ host_मुक्त;

	host->reset = devm_reset_control_get_optional_exclusive(&pdev->dev,
								"hrst");
	अगर (IS_ERR(host->reset)) अणु
		ret = PTR_ERR(host->reset);
		जाओ host_मुक्त;
	पूर्ण

	host->irq = platक्रमm_get_irq(pdev, 0);
	अगर (host->irq < 0) अणु
		ret = -EINVAL;
		जाओ host_मुक्त;
	पूर्ण

	host->pinctrl = devm_pinctrl_get(&pdev->dev);
	अगर (IS_ERR(host->pinctrl)) अणु
		ret = PTR_ERR(host->pinctrl);
		dev_err(&pdev->dev, "Cannot find pinctrl!\n");
		जाओ host_मुक्त;
	पूर्ण

	host->pins_शेष = pinctrl_lookup_state(host->pinctrl, "default");
	अगर (IS_ERR(host->pins_शेष)) अणु
		ret = PTR_ERR(host->pins_शेष);
		dev_err(&pdev->dev, "Cannot find pinctrl default!\n");
		जाओ host_मुक्त;
	पूर्ण

	host->pins_uhs = pinctrl_lookup_state(host->pinctrl, "state_uhs");
	अगर (IS_ERR(host->pins_uhs)) अणु
		ret = PTR_ERR(host->pins_uhs);
		dev_err(&pdev->dev, "Cannot find pinctrl uhs!\n");
		जाओ host_मुक्त;
	पूर्ण

	msdc_of_property_parse(pdev, host);

	host->dev = &pdev->dev;
	host->dev_comp = of_device_get_match_data(&pdev->dev);
	host->src_clk_freq = clk_get_rate(host->src_clk);
	/* Set host parameters to mmc */
	mmc->ops = &mt_msdc_ops;
	अगर (host->dev_comp->clk_भाग_bits == 8)
		mmc->f_min = DIV_ROUND_UP(host->src_clk_freq, 4 * 255);
	अन्यथा
		mmc->f_min = DIV_ROUND_UP(host->src_clk_freq, 4 * 4095);

	अगर (!(mmc->caps & MMC_CAP_NONREMOVABLE) &&
	    !mmc_can_gpio_cd(mmc) &&
	    host->dev_comp->use_पूर्णांकernal_cd) अणु
		/*
		 * Is removable but no GPIO declared, so
		 * use पूर्णांकernal functionality.
		 */
		host->पूर्णांकernal_cd = true;
	पूर्ण

	अगर (mmc->caps & MMC_CAP_SDIO_IRQ)
		mmc->caps2 |= MMC_CAP2_SDIO_IRQ_NOTHREAD;

	mmc->caps |= MMC_CAP_CMD23;
	अगर (host->cqhci)
		mmc->caps2 |= MMC_CAP2_CQE | MMC_CAP2_CQE_DCMD;
	/* MMC core transfer sizes tunable parameters */
	mmc->max_segs = MAX_BD_NUM;
	अगर (host->dev_comp->support_64g)
		mmc->max_seg_size = BDMA_DESC_BUFLEN_EXT;
	अन्यथा
		mmc->max_seg_size = BDMA_DESC_BUFLEN;
	mmc->max_blk_size = 2048;
	mmc->max_req_size = 512 * 1024;
	mmc->max_blk_count = mmc->max_req_size / 512;
	अगर (host->dev_comp->support_64g)
		host->dma_mask = DMA_BIT_MASK(36);
	अन्यथा
		host->dma_mask = DMA_BIT_MASK(32);
	mmc_dev(mmc)->dma_mask = &host->dma_mask;

	अगर (mmc->caps2 & MMC_CAP2_CQE) अणु
		host->cq_host = devm_kzalloc(mmc->parent,
					     माप(*host->cq_host),
					     GFP_KERNEL);
		अगर (!host->cq_host) अणु
			ret = -ENOMEM;
			जाओ host_मुक्त;
		पूर्ण
		host->cq_host->caps |= CQHCI_TASK_DESC_SZ_128;
		host->cq_host->mmio = host->base + 0x800;
		host->cq_host->ops = &msdc_cmdq_ops;
		ret = cqhci_init(host->cq_host, mmc, true);
		अगर (ret)
			जाओ host_मुक्त;
		mmc->max_segs = 128;
		/* cqhci 16bit length */
		/* 0 size, means 65536 so we करोn't have to -1 here */
		mmc->max_seg_size = 64 * 1024;
	पूर्ण

	host->समयout_clks = 3 * 1048576;
	host->dma.gpd = dma_alloc_coherent(&pdev->dev,
				2 * माप(काष्ठा mt_gpdma_desc),
				&host->dma.gpd_addr, GFP_KERNEL);
	host->dma.bd = dma_alloc_coherent(&pdev->dev,
				MAX_BD_NUM * माप(काष्ठा mt_bdma_desc),
				&host->dma.bd_addr, GFP_KERNEL);
	अगर (!host->dma.gpd || !host->dma.bd) अणु
		ret = -ENOMEM;
		जाओ release_mem;
	पूर्ण
	msdc_init_gpd_bd(host, &host->dma);
	INIT_DELAYED_WORK(&host->req_समयout, msdc_request_समयout);
	spin_lock_init(&host->lock);

	platक्रमm_set_drvdata(pdev, mmc);
	msdc_ungate_घड़ी(host);
	msdc_init_hw(host);

	ret = devm_request_irq(&pdev->dev, host->irq, msdc_irq,
			       IRQF_TRIGGER_NONE, pdev->name, host);
	अगर (ret)
		जाओ release;

	pm_runसमय_set_active(host->dev);
	pm_runसमय_set_स्वतःsuspend_delay(host->dev, MTK_MMC_AUTOSUSPEND_DELAY);
	pm_runसमय_use_स्वतःsuspend(host->dev);
	pm_runसमय_enable(host->dev);
	ret = mmc_add_host(mmc);

	अगर (ret)
		जाओ end;

	वापस 0;
end:
	pm_runसमय_disable(host->dev);
release:
	platक्रमm_set_drvdata(pdev, शून्य);
	msdc_deinit_hw(host);
	msdc_gate_घड़ी(host);
release_mem:
	अगर (host->dma.gpd)
		dma_मुक्त_coherent(&pdev->dev,
			2 * माप(काष्ठा mt_gpdma_desc),
			host->dma.gpd, host->dma.gpd_addr);
	अगर (host->dma.bd)
		dma_मुक्त_coherent(&pdev->dev,
			MAX_BD_NUM * माप(काष्ठा mt_bdma_desc),
			host->dma.bd, host->dma.bd_addr);
host_मुक्त:
	mmc_मुक्त_host(mmc);

	वापस ret;
पूर्ण

अटल पूर्णांक msdc_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_host *mmc;
	काष्ठा msdc_host *host;

	mmc = platक्रमm_get_drvdata(pdev);
	host = mmc_priv(mmc);

	pm_runसमय_get_sync(host->dev);

	platक्रमm_set_drvdata(pdev, शून्य);
	mmc_हटाओ_host(mmc);
	msdc_deinit_hw(host);
	msdc_gate_घड़ी(host);

	pm_runसमय_disable(host->dev);
	pm_runसमय_put_noidle(host->dev);
	dma_मुक्त_coherent(&pdev->dev,
			2 * माप(काष्ठा mt_gpdma_desc),
			host->dma.gpd, host->dma.gpd_addr);
	dma_मुक्त_coherent(&pdev->dev, MAX_BD_NUM * माप(काष्ठा mt_bdma_desc),
			host->dma.bd, host->dma.bd_addr);

	mmc_मुक्त_host(mmc);

	वापस 0;
पूर्ण

अटल व्योम msdc_save_reg(काष्ठा msdc_host *host)
अणु
	u32 tune_reg = host->dev_comp->pad_tune_reg;

	host->save_para.msdc_cfg = पढ़ोl(host->base + MSDC_CFG);
	host->save_para.iocon = पढ़ोl(host->base + MSDC_IOCON);
	host->save_para.sdc_cfg = पढ़ोl(host->base + SDC_CFG);
	host->save_para.patch_bit0 = पढ़ोl(host->base + MSDC_PATCH_BIT);
	host->save_para.patch_bit1 = पढ़ोl(host->base + MSDC_PATCH_BIT1);
	host->save_para.patch_bit2 = पढ़ोl(host->base + MSDC_PATCH_BIT2);
	host->save_para.pad_ds_tune = पढ़ोl(host->base + PAD_DS_TUNE);
	host->save_para.pad_cmd_tune = पढ़ोl(host->base + PAD_CMD_TUNE);
	host->save_para.emmc50_cfg0 = पढ़ोl(host->base + EMMC50_CFG0);
	host->save_para.emmc50_cfg3 = पढ़ोl(host->base + EMMC50_CFG3);
	host->save_para.sdc_fअगरo_cfg = पढ़ोl(host->base + SDC_FIFO_CFG);
	अगर (host->top_base) अणु
		host->save_para.emmc_top_control =
			पढ़ोl(host->top_base + EMMC_TOP_CONTROL);
		host->save_para.emmc_top_cmd =
			पढ़ोl(host->top_base + EMMC_TOP_CMD);
		host->save_para.emmc50_pad_ds_tune =
			पढ़ोl(host->top_base + EMMC50_PAD_DS_TUNE);
	पूर्ण अन्यथा अणु
		host->save_para.pad_tune = पढ़ोl(host->base + tune_reg);
	पूर्ण
पूर्ण

अटल व्योम msdc_restore_reg(काष्ठा msdc_host *host)
अणु
	काष्ठा mmc_host *mmc = mmc_from_priv(host);
	u32 tune_reg = host->dev_comp->pad_tune_reg;

	ग_लिखोl(host->save_para.msdc_cfg, host->base + MSDC_CFG);
	ग_लिखोl(host->save_para.iocon, host->base + MSDC_IOCON);
	ग_लिखोl(host->save_para.sdc_cfg, host->base + SDC_CFG);
	ग_लिखोl(host->save_para.patch_bit0, host->base + MSDC_PATCH_BIT);
	ग_लिखोl(host->save_para.patch_bit1, host->base + MSDC_PATCH_BIT1);
	ग_लिखोl(host->save_para.patch_bit2, host->base + MSDC_PATCH_BIT2);
	ग_लिखोl(host->save_para.pad_ds_tune, host->base + PAD_DS_TUNE);
	ग_लिखोl(host->save_para.pad_cmd_tune, host->base + PAD_CMD_TUNE);
	ग_लिखोl(host->save_para.emmc50_cfg0, host->base + EMMC50_CFG0);
	ग_लिखोl(host->save_para.emmc50_cfg3, host->base + EMMC50_CFG3);
	ग_लिखोl(host->save_para.sdc_fअगरo_cfg, host->base + SDC_FIFO_CFG);
	अगर (host->top_base) अणु
		ग_लिखोl(host->save_para.emmc_top_control,
		       host->top_base + EMMC_TOP_CONTROL);
		ग_लिखोl(host->save_para.emmc_top_cmd,
		       host->top_base + EMMC_TOP_CMD);
		ग_लिखोl(host->save_para.emmc50_pad_ds_tune,
		       host->top_base + EMMC50_PAD_DS_TUNE);
	पूर्ण अन्यथा अणु
		ग_लिखोl(host->save_para.pad_tune, host->base + tune_reg);
	पूर्ण

	अगर (sdio_irq_claimed(mmc))
		__msdc_enable_sdio_irq(host, 1);
पूर्ण

अटल पूर्णांक __maybe_unused msdc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा mmc_host *mmc = dev_get_drvdata(dev);
	काष्ठा msdc_host *host = mmc_priv(mmc);

	msdc_save_reg(host);
	msdc_gate_घड़ी(host);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused msdc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा mmc_host *mmc = dev_get_drvdata(dev);
	काष्ठा msdc_host *host = mmc_priv(mmc);

	msdc_ungate_घड़ी(host);
	msdc_restore_reg(host);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused msdc_suspend(काष्ठा device *dev)
अणु
	काष्ठा mmc_host *mmc = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (mmc->caps2 & MMC_CAP2_CQE) अणु
		ret = cqhci_suspend(mmc);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस pm_runसमय_क्रमce_suspend(dev);
पूर्ण

अटल पूर्णांक __maybe_unused msdc_resume(काष्ठा device *dev)
अणु
	वापस pm_runसमय_क्रमce_resume(dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops msdc_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(msdc_suspend, msdc_resume)
	SET_RUNTIME_PM_OPS(msdc_runसमय_suspend, msdc_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver mt_msdc_driver = अणु
	.probe = msdc_drv_probe,
	.हटाओ = msdc_drv_हटाओ,
	.driver = अणु
		.name = "mtk-msdc",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = msdc_of_ids,
		.pm = &msdc_dev_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mt_msdc_driver);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MediaTek SD/MMC Card Driver");
