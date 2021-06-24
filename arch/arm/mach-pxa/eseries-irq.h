<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  eseries-irq.h
 *
 *  Copyright (C) Ian Molton <spyro@f2s.com>
 */

#घोषणा ANGELX_IRQ_BASE (IRQ_BOARD_START+8)
#घोषणा IRQ_ANGELX(n) (ANGELX_IRQ_BASE + (n))

#घोषणा ANGELX_RDY0_IRQ IRQ_ANGELX(0)
#घोषणा ANGELX_ST0_IRQ  IRQ_ANGELX(1)
#घोषणा ANGELX_CD0_IRQ  IRQ_ANGELX(2)
#घोषणा ANGELX_RDY1_IRQ IRQ_ANGELX(3)
#घोषणा ANGELX_ST1_IRQ  IRQ_ANGELX(4)
#घोषणा ANGELX_CD1_IRQ  IRQ_ANGELX(5)

#घोषणा TMIO_IRQ_BASE (IRQ_BOARD_START+0)
#घोषणा IRQ_TMIO(n) (TMIO_IRQ_BASE + (n))

#घोषणा TMIO_SD_IRQ     IRQ_TMIO(1)
#घोषणा TMIO_USB_IRQ    IRQ_TMIO(2)

#घोषणा ESERIES_NR_IRQS	(IRQ_BOARD_START + 16)
