<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  capcella.h, Include file क्रम ZAO Networks Capcella.
 *
 *  Copyright (C) 2002-2004  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#अगर_अघोषित __ZAO_CAPCELLA_H
#घोषणा __ZAO_CAPCELLA_H

#समावेश <यंत्र/vr41xx/irq.h>

/*
 * General-Purpose I/O Pin Number
 */
#घोषणा PC104PLUS_INTA_PIN		2
#घोषणा PC104PLUS_INTB_PIN		3
#घोषणा PC104PLUS_INTC_PIN		4
#घोषणा PC104PLUS_INTD_PIN		5

/*
 * Interrupt Number
 */
#घोषणा RTL8139_1_IRQ			GIU_IRQ(PC104PLUS_INTC_PIN)
#घोषणा RTL8139_2_IRQ			GIU_IRQ(PC104PLUS_INTD_PIN)
#घोषणा PC104PLUS_INTA_IRQ		GIU_IRQ(PC104PLUS_INTA_PIN)
#घोषणा PC104PLUS_INTB_IRQ		GIU_IRQ(PC104PLUS_INTB_PIN)
#घोषणा PC104PLUS_INTC_IRQ		GIU_IRQ(PC104PLUS_INTC_PIN)
#घोषणा PC104PLUS_INTD_IRQ		GIU_IRQ(PC104PLUS_INTD_PIN)

#पूर्ण_अगर /* __ZAO_CAPCELLA_H */
