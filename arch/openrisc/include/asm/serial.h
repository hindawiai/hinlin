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

#अगर_अघोषित __ASM_OPENRISC_SERIAL_H
#घोषणा __ASM_OPENRISC_SERIAL_H

#अगर_घोषित __KERNEL__

#समावेश <यंत्र/cpuinfo.h>

/* There's a generic version of this file, but it assumes a 1.8MHz UART clk...
 * this, on the other hand, assumes the UART घड़ी is tied to the प्रणाली
 * घड़ी... 8250_early.c (early 8250 serial console) actually uses this, so
 * it needs to be correct to get the early console working.
 */

#घोषणा BASE_BAUD (cpuinfo_or1k[smp_processor_id()].घड़ी_frequency/16)

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ASM_OPENRISC_SERIAL_H */
