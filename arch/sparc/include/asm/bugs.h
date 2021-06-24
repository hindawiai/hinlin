<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* include/यंत्र/bugs.h:  Sparc probes क्रम various bugs.
 *
 * Copyright (C) 1996, 2007 David S. Miller (davem@davemloft.net)
 */

#अगर_घोषित CONFIG_SPARC32
#समावेश <यंत्र/cpudata.h>
#पूर्ण_अगर

बाह्य अचिन्हित दीर्घ loops_per_jअगरfy;

अटल व्योम __init check_bugs(व्योम)
अणु
#अगर defined(CONFIG_SPARC32) && !defined(CONFIG_SMP)
	cpu_data(0).udelay_val = loops_per_jअगरfy;
#पूर्ण_अगर
पूर्ण
