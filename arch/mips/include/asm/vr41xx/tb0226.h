<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  tb0226.h, Include file क्रम TANBAC TB0226.
 *
 *  Copyright (C) 2002-2004  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#अगर_अघोषित __TANBAC_TB0226_H
#घोषणा __TANBAC_TB0226_H

#समावेश <यंत्र/vr41xx/irq.h>

/*
 * General-Purpose I/O Pin Number
 */
#घोषणा GD82559_1_PIN			2
#घोषणा GD82559_2_PIN			3
#घोषणा UPD720100_INTA_PIN		4
#घोषणा UPD720100_INTB_PIN		8
#घोषणा UPD720100_INTC_PIN		13

/*
 * Interrupt Number
 */
#घोषणा GD82559_1_IRQ			GIU_IRQ(GD82559_1_PIN)
#घोषणा GD82559_2_IRQ			GIU_IRQ(GD82559_2_PIN)
#घोषणा UPD720100_INTA_IRQ		GIU_IRQ(UPD720100_INTA_PIN)
#घोषणा UPD720100_INTB_IRQ		GIU_IRQ(UPD720100_INTB_PIN)
#घोषणा UPD720100_INTC_IRQ		GIU_IRQ(UPD720100_INTC_PIN)

#पूर्ण_अगर /* __TANBAC_TB0226_H */
