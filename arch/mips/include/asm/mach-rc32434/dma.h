<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2002 Integrated Device Technology, Inc.
 *		All rights reserved.
 *
 * DMA रेजिस्टर definition.
 *
 * Author : ryan.holmQVist@idt.com
 * Date	  : 20011005
 */

#अगर_अघोषित __ASM_RC32434_DMA_H
#घोषणा __ASM_RC32434_DMA_H

#समावेश <यंत्र/mach-rc32434/rb.h>

#घोषणा DMA0_BASE_ADDR			0x18040000

/*
 * DMA descriptor (in physical memory).
 */

काष्ठा dma_desc अणु
	u32 control;			/* Control. use DMAD_* */
	u32 ca;				/* Current Address. */
	u32 devcs;			/* Device control and status. */
	u32 link;			/* Next descriptor in chain. */
पूर्ण;

#घोषणा DMA_DESC_SIZ			माप(काष्ठा dma_desc)
#घोषणा DMA_DESC_COUNT_BIT		0
#घोषणा DMA_DESC_COUNT_MSK		0x0003ffff
#घोषणा DMA_DESC_DS_BIT			20
#घोषणा DMA_DESC_DS_MSK			0x00300000

#घोषणा DMA_DESC_DEV_CMD_BIT		22
#घोषणा DMA_DESC_DEV_CMD_MSK		0x01c00000

/* DMA command sizes */
#घोषणा DMA_DESC_DEV_CMD_BYTE		0
#घोषणा DMA_DESC_DEV_CMD_HLF_WD		1
#घोषणा DMA_DESC_DEV_CMD_WORD		2
#घोषणा DMA_DESC_DEV_CMD_2WORDS		3
#घोषणा DMA_DESC_DEV_CMD_4WORDS		4
#घोषणा DMA_DESC_DEV_CMD_6WORDS		5
#घोषणा DMA_DESC_DEV_CMD_8WORDS		6
#घोषणा DMA_DESC_DEV_CMD_16WORDS	7

/* DMA descriptors पूर्णांकerrupts */
#घोषणा DMA_DESC_COF			(1 << 25) /* Chain on finished */
#घोषणा DMA_DESC_COD			(1 << 26) /* Chain on करोne */
#घोषणा DMA_DESC_IOF			(1 << 27) /* Interrupt on finished */
#घोषणा DMA_DESC_IOD			(1 << 28) /* Interrupt on करोne */
#घोषणा DMA_DESC_TERM			(1 << 29) /* Terminated */
#घोषणा DMA_DESC_DONE			(1 << 30) /* Done */
#घोषणा DMA_DESC_FINI			(1 << 31) /* Finished */

/*
 * DMA रेजिस्टर (within Internal Register Map).
 */

काष्ठा dma_reg अणु
	u32 dmac;		/* Control. */
	u32 dmas;		/* Status. */
	u32 dmयंत्र;		/* Mask. */
	u32 dmadptr;		/* Descriptor poपूर्णांकer. */
	u32 dmandptr;		/* Next descriptor poपूर्णांकer. */
पूर्ण;

/* DMA channels specअगरic रेजिस्टरs */
#घोषणा DMA_CHAN_RUN_BIT		(1 << 0)
#घोषणा DMA_CHAN_DONE_BIT		(1 << 1)
#घोषणा DMA_CHAN_MODE_BIT		(1 << 2)
#घोषणा DMA_CHAN_MODE_MSK		0x0000000c
#घोषणा	 DMA_CHAN_MODE_AUTO		0
#घोषणा	 DMA_CHAN_MODE_BURST		1
#घोषणा	 DMA_CHAN_MODE_XFRT		2
#घोषणा	 DMA_CHAN_MODE_RSVD		3
#घोषणा DMA_CHAN_ACT_BIT		(1 << 4)

/* DMA status रेजिस्टरs */
#घोषणा DMA_STAT_FINI			(1 << 0)
#घोषणा DMA_STAT_DONE			(1 << 1)
#घोषणा DMA_STAT_CHAIN			(1 << 2)
#घोषणा DMA_STAT_ERR			(1 << 3)
#घोषणा DMA_STAT_HALT			(1 << 4)

/*
 * DMA channel definitions
 */

#घोषणा DMA_CHAN_ETH_RCV		0
#घोषणा DMA_CHAN_ETH_XMT		1
#घोषणा DMA_CHAN_MEM_TO_FIFO		2
#घोषणा DMA_CHAN_FIFO_TO_MEM		3
#घोषणा DMA_CHAN_PCI_TO_MEM		4
#घोषणा DMA_CHAN_MEM_TO_PCI		5
#घोषणा DMA_CHAN_COUNT			6

काष्ठा dma_channel अणु
	काष्ठा dma_reg ch[DMA_CHAN_COUNT];
पूर्ण;

#पूर्ण_अगर	/* __ASM_RC32434_DMA_H */
