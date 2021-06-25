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

#अगर_अघोषित __ASM_OPENRISC_BITOPS_H
#घोषणा __ASM_OPENRISC_BITOPS_H

/*
 * Where we haven't written assembly versions yet, we fall back to the
 * generic implementations.  Otherwise, we pull in our (hopefully)
 * optimized versions.
 */

#समावेश <linux/irqflags.h>
#समावेश <linux/compiler.h>
#समावेश <यंत्र/barrier.h>

#समावेश <यंत्र/bitops/__ffs.h>
#समावेश <यंत्र-generic/bitops/ffz.h>
#समावेश <यंत्र/bitops/fls.h>
#समावेश <यंत्र/bitops/__fls.h>
#समावेश <यंत्र-generic/bitops/fls64.h>
#समावेश <यंत्र-generic/bitops/find.h>

#अगर_अघोषित _LINUX_BITOPS_H
#त्रुटि only <linux/bitops.h> can be included directly
#पूर्ण_अगर

#समावेश <यंत्र-generic/bitops/sched.h>
#समावेश <यंत्र/bitops/ffs.h>
#समावेश <यंत्र-generic/bitops/hweight.h>
#समावेश <यंत्र-generic/bitops/lock.h>

#समावेश <यंत्र/bitops/atomic.h>
#समावेश <यंत्र-generic/bitops/non-atomic.h>
#समावेश <यंत्र-generic/bitops/le.h>
#समावेश <यंत्र-generic/bitops/ext2-atomic.h>

#पूर्ण_अगर /* __ASM_GENERIC_BITOPS_H */
