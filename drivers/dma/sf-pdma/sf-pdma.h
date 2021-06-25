<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * SiFive FU540 Platक्रमm DMA driver
 * Copyright (C) 2019 SiFive
 *
 * Based partially on:
 * - drivers/dma/fsl-edma.c
 * - drivers/dma/dw-edma/
 * - drivers/dma/pxa-dma.c
 *
 * See the following sources क्रम further करोcumentation:
 * - Chapter 12 "Platform DMA Engine (PDMA)" of
 *   SiFive FU540-C000 v1.0
 *   https://अटल.dev.sअगरive.com/FU540-C000-v1.0.pdf
 */
#अगर_अघोषित _SF_PDMA_H
#घोषणा _SF_PDMA_H

#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-direction.h>

#समावेश "../dmaengine.h"
#समावेश "../virt-dma.h"

#घोषणा PDMA_NR_CH					4

#अगर (PDMA_NR_CH != 4)
#त्रुटि "Please define PDMA_NR_CH to 4"
#पूर्ण_अगर

#घोषणा PDMA_BASE_ADDR					0x3000000
#घोषणा PDMA_CHAN_OFFSET				0x1000

/* Register Offset */
#घोषणा PDMA_CTRL					0x000
#घोषणा PDMA_XFER_TYPE					0x004
#घोषणा PDMA_XFER_SIZE					0x008
#घोषणा PDMA_DST_ADDR					0x010
#घोषणा PDMA_SRC_ADDR					0x018
#घोषणा PDMA_ACT_TYPE					0x104 /* Read-only */
#घोषणा PDMA_REMAINING_BYTE				0x108 /* Read-only */
#घोषणा PDMA_CUR_DST_ADDR				0x110 /* Read-only*/
#घोषणा PDMA_CUR_SRC_ADDR				0x118 /* Read-only*/

/* CTRL */
#घोषणा PDMA_CLEAR_CTRL					0x0
#घोषणा PDMA_CLAIM_MASK					GENMASK(0, 0)
#घोषणा PDMA_RUN_MASK					GENMASK(1, 1)
#घोषणा PDMA_ENABLE_DONE_INT_MASK			GENMASK(14, 14)
#घोषणा PDMA_ENABLE_ERR_INT_MASK			GENMASK(15, 15)
#घोषणा PDMA_DONE_STATUS_MASK				GENMASK(30, 30)
#घोषणा PDMA_ERR_STATUS_MASK				GENMASK(31, 31)

/* Transfer Type */
#घोषणा PDMA_FULL_SPEED					0xFF000008

/* Error Recovery */
#घोषणा MAX_RETRY					1

#घोषणा SF_PDMA_REG_BASE(ch)	(pdma->membase + (PDMA_CHAN_OFFSET * (ch)))

काष्ठा pdma_regs अणु
	/* पढ़ो-ग_लिखो regs */
	व्योम __iomem *ctrl;		/* 4 bytes */

	व्योम __iomem *xfer_type;	/* 4 bytes */
	व्योम __iomem *xfer_size;	/* 8 bytes */
	व्योम __iomem *dst_addr;		/* 8 bytes */
	व्योम __iomem *src_addr;		/* 8 bytes */

	/* पढ़ो-only */
	व्योम __iomem *act_type;		/* 4 bytes */
	व्योम __iomem *residue;		/* 8 bytes */
	व्योम __iomem *cur_dst_addr;	/* 8 bytes */
	व्योम __iomem *cur_src_addr;	/* 8 bytes */
पूर्ण;

काष्ठा sf_pdma_desc अणु
	u32				xfer_type;
	u64				xfer_size;
	u64				dst_addr;
	u64				src_addr;
	काष्ठा virt_dma_desc		vdesc;
	काष्ठा sf_pdma_chan		*chan;
	bool				in_use;
	क्रमागत dma_transfer_direction	dirn;
	काष्ठा dma_async_tx_descriptor *async_tx;
पूर्ण;

क्रमागत sf_pdma_pm_state अणु
	RUNNING = 0,
	SUSPENDED,
पूर्ण;

काष्ठा sf_pdma_chan अणु
	काष्ठा virt_dma_chan		vchan;
	क्रमागत dma_status			status;
	क्रमागत sf_pdma_pm_state		pm_state;
	u32				slave_id;
	काष्ठा sf_pdma			*pdma;
	काष्ठा sf_pdma_desc		*desc;
	काष्ठा dma_slave_config		cfg;
	u32				attr;
	dma_addr_t			dma_dev_addr;
	u32				dma_dev_size;
	काष्ठा tasklet_काष्ठा		करोne_tasklet;
	काष्ठा tasklet_काष्ठा		err_tasklet;
	काष्ठा pdma_regs		regs;
	spinlock_t			lock; /* protect chan data */
	bool				xfer_err;
	पूर्णांक				txirq;
	पूर्णांक				errirq;
	पूर्णांक				retries;
पूर्ण;

काष्ठा sf_pdma अणु
	काष्ठा dma_device       dma_dev;
	व्योम __iomem            *membase;
	व्योम __iomem            *mappedbase;
	u32			n_chans;
	काष्ठा sf_pdma_chan	chans[PDMA_NR_CH];
पूर्ण;

#पूर्ण_अगर /* _SF_PDMA_H */
