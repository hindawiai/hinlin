<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * include/यंत्र-sh/dreamcast/sysasic.h
 *
 * Definitions क्रम the Dreamcast System ASIC and related peripherals.
 *
 * Copyright (c) 2001 M. R. Brown <mrbrown@linuxdc.org>
 * Copyright (C) 2003 Paul Mundt <lethal@linux-sh.org>
 *
 * This file is part of the LinuxDC project (www.linuxdc.org)
 */
#अगर_अघोषित __ASM_SH_DREAMCAST_SYSASIC_H
#घोषणा __ASM_SH_DREAMCAST_SYSASIC_H

#समावेश <यंत्र/irq.h>

/* Hardware events -

   Each of these events correspond to a bit within the Event Mask Registers/
   Event Status Registers.  Because of the भव IRQ numbering scheme, a
   base offset must be used when calculating the भव IRQ that each event
   takes.
*/

#घोषणा HW_EVENT_IRQ_BASE  48

/* IRQ 13 */
#घोषणा HW_EVENT_VSYNC     (HW_EVENT_IRQ_BASE +  5) /* VSync */
#घोषणा HW_EVENT_MAPLE_DMA (HW_EVENT_IRQ_BASE + 12) /* Maple DMA complete */
#घोषणा HW_EVENT_GDROM_DMA (HW_EVENT_IRQ_BASE + 14) /* GD-ROM DMA complete */
#घोषणा HW_EVENT_G2_DMA    (HW_EVENT_IRQ_BASE + 15) /* G2 DMA complete */
#घोषणा HW_EVENT_PVR2_DMA  (HW_EVENT_IRQ_BASE + 19) /* PVR2 DMA complete */

/* IRQ 11 */
#घोषणा HW_EVENT_GDROM_CMD (HW_EVENT_IRQ_BASE + 32) /* GD-ROM cmd. complete */
#घोषणा HW_EVENT_AICA_SYS  (HW_EVENT_IRQ_BASE + 33) /* AICA-related */
#घोषणा HW_EVENT_EXTERNAL  (HW_EVENT_IRQ_BASE + 35) /* Ext. (expansion) */

#घोषणा HW_EVENT_IRQ_MAX (HW_EVENT_IRQ_BASE + 95)

/* arch/sh/boards/mach-dreamcast/irq.c */
बाह्य पूर्णांक प्रणालीasic_irq_demux(पूर्णांक);
बाह्य व्योम प्रणालीasic_irq_init(व्योम);

#पूर्ण_अगर /* __ASM_SH_DREAMCAST_SYSASIC_H */

