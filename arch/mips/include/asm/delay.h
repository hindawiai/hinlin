<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994 by Walकरोrf Electronics
 * Copyright (C) 1995 - 2000, 01, 03 by Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 * Copyright (C) 2007  Maciej W. Rozycki
 */
#अगर_अघोषित _ASM_DELAY_H
#घोषणा _ASM_DELAY_H

#समावेश <linux/param.h>

बाह्य व्योम __delay(अचिन्हित दीर्घ loops);
बाह्य व्योम __ndelay(अचिन्हित दीर्घ ns);
बाह्य व्योम __udelay(अचिन्हित दीर्घ us);

#घोषणा ndelay(ns) __ndelay(ns)
#घोषणा udelay(us) __udelay(us)

/* make sure "usecs *= ..." in udelay करो not overflow. */
#अगर HZ >= 1000
#घोषणा MAX_UDELAY_MS	1
#या_अगर HZ <= 200
#घोषणा MAX_UDELAY_MS	5
#अन्यथा
#घोषणा MAX_UDELAY_MS	(1000 / HZ)
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_DELAY_H */
