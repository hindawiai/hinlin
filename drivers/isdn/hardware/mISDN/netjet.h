<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * NETjet common header file
 *
 * Author	Karsten Keil
 *              based on work of Matt Henderson and Daniel Potts,
 *              Traverse Technologies P/L www.traverse.com.au
 *
 * Copyright 2009  by Karsten Keil <keil@isdn4linux.de>
 */

#घोषणा NJ_CTRL			0x00
#घोषणा NJ_DMACTRL		0x01
#घोषणा NJ_AUXCTRL		0x02
#घोषणा NJ_AUXDATA		0x03
#घोषणा NJ_IRQMASK0		0x04
#घोषणा NJ_IRQMASK1		0x05
#घोषणा NJ_IRQSTAT0		0x06
#घोषणा NJ_IRQSTAT1		0x07
#घोषणा NJ_DMA_READ_START	0x08
#घोषणा NJ_DMA_READ_IRQ		0x0c
#घोषणा NJ_DMA_READ_END		0x10
#घोषणा NJ_DMA_READ_ADR		0x14
#घोषणा NJ_DMA_WRITE_START	0x18
#घोषणा NJ_DMA_WRITE_IRQ	0x1c
#घोषणा NJ_DMA_WRITE_END	0x20
#घोषणा NJ_DMA_WRITE_ADR	0x24
#घोषणा NJ_PULSE_CNT		0x28

#घोषणा NJ_ISAC_OFF		0xc0
#घोषणा NJ_ISACIRQ		0x10

#घोषणा NJ_IRQM0_RD_MASK	0x03
#घोषणा NJ_IRQM0_RD_IRQ		0x01
#घोषणा NJ_IRQM0_RD_END		0x02
#घोषणा NJ_IRQM0_WR_MASK	0x0c
#घोषणा NJ_IRQM0_WR_IRQ		0x04
#घोषणा NJ_IRQM0_WR_END		0x08

/* one page here is no need to be smaller */
#घोषणा NJ_DMA_SIZE		4096
/* 2 * 64 byte is a compromise between IRQ count and latency */
#घोषणा NJ_DMA_RXSIZE		128  /* 2 * 64 */
#घोषणा NJ_DMA_TXSIZE		128  /* 2 * 64 */
