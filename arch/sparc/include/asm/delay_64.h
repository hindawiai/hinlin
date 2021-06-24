<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* delay.h: Linux delay routines on sparc64.
 *
 * Copyright (C) 1996, 2004, 2007 David S. Miller (davem@davemloft.net).
 */

#अगर_अघोषित _SPARC64_DELAY_H
#घोषणा _SPARC64_DELAY_H

#अगर_अघोषित __ASSEMBLY__

व्योम __delay(अचिन्हित दीर्घ loops);
व्योम udelay(अचिन्हित दीर्घ usecs);
#घोषणा mdelay(n)	udelay((n) * 1000)

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _SPARC64_DELAY_H */
