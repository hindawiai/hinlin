<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Miscellaneous ARCS PROM routines.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1999 Ralf Baechle (ralf@gnu.org)
 * Copyright (C) 1999 Silicon Graphics, Inc.
 */
#समावेश <linux/compiler.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/irqflags.h>

#समावेश <यंत्र/bcache.h>

#समावेश <यंत्र/fw/arc/types.h>
#समावेश <यंत्र/sgialib.h>
#समावेश <यंत्र/bootinfo.h>

VOID __noवापस
ArcEnterInteractiveMode(VOID)
अणु
	bc_disable();
	local_irq_disable();
	ARC_CALL0(imode);

	unreachable();
पूर्ण

DISPLAY_STATUS * __init ArcGetDisplayStatus(ULONG FileID)
अणु
	वापस (DISPLAY_STATUS *) ARC_CALL1(GetDisplayStatus, FileID);
पूर्ण
