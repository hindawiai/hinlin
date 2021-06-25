<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  tb0287.h, Include file क्रम TANBAC TB0287 mini-ITX board.
 *
 *  Copyright (C) 2005	Media Lab Inc. <ito@mlb.co.jp>
 *
 *  This code is largely based on tb0219.h.
 */
#अगर_अघोषित __TANBAC_TB0287_H
#घोषणा __TANBAC_TB0287_H

#समावेश <यंत्र/vr41xx/irq.h>

/*
 * General-Purpose I/O Pin Number
 */
#घोषणा TB0287_PCI_SLOT_PIN		2
#घोषणा TB0287_SM501_PIN		3
#घोषणा TB0287_SIL680A_PIN		8
#घोषणा TB0287_RTL8110_PIN		13

/*
 * Interrupt Number
 */
#घोषणा TB0287_PCI_SLOT_IRQ		GIU_IRQ(TB0287_PCI_SLOT_PIN)
#घोषणा TB0287_SM501_IRQ		GIU_IRQ(TB0287_SM501_PIN)
#घोषणा TB0287_SIL680A_IRQ		GIU_IRQ(TB0287_SIL680A_PIN)
#घोषणा TB0287_RTL8110_IRQ		GIU_IRQ(TB0287_RTL8110_PIN)

#पूर्ण_अगर /* __TANBAC_TB0287_H */
