<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * arch/arm/mach-omap1/include/mach/lcdc.h
 *
 * Extracted from drivers/video/omap/lcdc.c
 * Copyright (C) 2004 Nokia Corporation
 * Author: Imre Deak <imre.deak@nokia.com>
 */
#अगर_अघोषित __MACH_LCDC_H__
#घोषणा __MACH_LCDC_H__

#घोषणा OMAP_LCDC_BASE			0xfffec000
#घोषणा OMAP_LCDC_SIZE			256
#घोषणा OMAP_LCDC_IRQ			INT_LCD_CTRL

#घोषणा OMAP_LCDC_CONTROL		(OMAP_LCDC_BASE + 0x00)
#घोषणा OMAP_LCDC_TIMING0		(OMAP_LCDC_BASE + 0x04)
#घोषणा OMAP_LCDC_TIMING1		(OMAP_LCDC_BASE + 0x08)
#घोषणा OMAP_LCDC_TIMING2		(OMAP_LCDC_BASE + 0x0c)
#घोषणा OMAP_LCDC_STATUS		(OMAP_LCDC_BASE + 0x10)
#घोषणा OMAP_LCDC_SUBPANEL		(OMAP_LCDC_BASE + 0x14)
#घोषणा OMAP_LCDC_LINE_INT		(OMAP_LCDC_BASE + 0x18)
#घोषणा OMAP_LCDC_DISPLAY_STATUS	(OMAP_LCDC_BASE + 0x1c)

#घोषणा OMAP_LCDC_STAT_DONE		(1 << 0)
#घोषणा OMAP_LCDC_STAT_VSYNC		(1 << 1)
#घोषणा OMAP_LCDC_STAT_SYNC_LOST	(1 << 2)
#घोषणा OMAP_LCDC_STAT_ABC		(1 << 3)
#घोषणा OMAP_LCDC_STAT_LINE_INT		(1 << 4)
#घोषणा OMAP_LCDC_STAT_FUF		(1 << 5)
#घोषणा OMAP_LCDC_STAT_LOADED_PALETTE	(1 << 6)

#घोषणा OMAP_LCDC_CTRL_LCD_EN		(1 << 0)
#घोषणा OMAP_LCDC_CTRL_LCD_TFT		(1 << 7)
#घोषणा OMAP_LCDC_CTRL_LINE_IRQ_CLR_SEL	(1 << 10)

#घोषणा OMAP_LCDC_IRQ_VSYNC		(1 << 2)
#घोषणा OMAP_LCDC_IRQ_DONE		(1 << 3)
#घोषणा OMAP_LCDC_IRQ_LOADED_PALETTE	(1 << 4)
#घोषणा OMAP_LCDC_IRQ_LINE_NIRQ		(1 << 5)
#घोषणा OMAP_LCDC_IRQ_LINE		(1 << 6)
#घोषणा OMAP_LCDC_IRQ_MASK		(((1 << 5) - 1) << 2)

#पूर्ण_अगर /* __MACH_LCDC_H__ */
