<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 */

#अगर_अघोषित ___ASM_OPENRISC_IRQFLAGS_H
#घोषणा ___ASM_OPENRISC_IRQFLAGS_H

#समावेश <यंत्र/spr_defs.h>

#घोषणा ARCH_IRQ_DISABLED        0x00
#घोषणा ARCH_IRQ_ENABLED         (SPR_SR_IEE|SPR_SR_TEE)

#समावेश <यंत्र-generic/irqflags.h>

#पूर्ण_अगर /* ___ASM_OPENRISC_IRQFLAGS_H */
