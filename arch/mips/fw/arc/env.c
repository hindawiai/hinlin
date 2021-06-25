<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * env.c: ARCS environment variable routines.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/fw/arc/types.h>
#समावेश <यंत्र/sgialib.h>

PCHAR __init
ArcGetEnvironmentVariable(CHAR *name)
अणु
	वापस (CHAR *) ARC_CALL1(get_evar, name);
पूर्ण
