<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996 David S. Miller (dm@sgi.com)
 * Compatibility with board caches, Ulf Carlsson
 */
#समावेश <linux/kernel.h>
#समावेश <यंत्र/sgialib.h>
#समावेश <यंत्र/bcache.h>
#समावेश <यंत्र/setup.h>

#अगर defined(CONFIG_64BIT) && defined(CONFIG_FW_ARC32)
/*
 * For 64bit kernels working with a 32bit ARC PROM poपूर्णांकer arguments
 * क्रम ARC calls need to reside in CKEG0/1. But as soon as the kernel
 * चयनes to it's first kernel thपढ़ो stack is set to an address in
 * XKPHYS, so anything on stack can't be used anymore. This is solved
 * by using a * अटल declartion variables are put पूर्णांकo BSS, which is
 * linked to a CKSEG0 address. Since this is only used on UP platक्रमms
 * there is not spinlock needed
 */
#घोषणा O32_STATIC	अटल
#अन्यथा
#घोषणा O32_STATIC
#पूर्ण_अगर

/*
 * IP22 boardcache is not compatible with board caches.	 Thus we disable it
 * during romvec action.  Since r4xx0.c is always compiled and linked with your
 * kernel, this shouldn't cause any harm regardless what MIPS processor you
 * have.
 *
 * The ARC ग_लिखो and पढ़ो functions seem to पूर्णांकerfere with the serial lines
 * in some way. You should be careful with them.
 */

व्योम prom_अक्षर_दो(अक्षर c)
अणु
	O32_STATIC ULONG cnt;
	O32_STATIC CHAR it;

	it = c;

	bc_disable();
	ArcWrite(1, &it, 1, &cnt);
	bc_enable();
पूर्ण

अक्षर prom_अक्षर_लो(व्योम)
अणु
	O32_STATIC ULONG cnt;
	O32_STATIC CHAR c;

	bc_disable();
	ArcRead(0, &c, 1, &cnt);
	bc_enable();

	वापस c;
पूर्ण
