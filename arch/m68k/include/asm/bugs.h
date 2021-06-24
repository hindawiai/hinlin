<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  include/यंत्र-m68k/bugs.h
 *
 *  Copyright (C) 1994  Linus Torvalds
 */

/*
 * This is included by init/मुख्य.c to check क्रम architecture-dependent bugs.
 *
 * Needs:
 *	व्योम check_bugs(व्योम);
 */

#अगर_घोषित CONFIG_MMU
बाह्य व्योम check_bugs(व्योम);	/* in arch/m68k/kernel/setup.c */
#अन्यथा
अटल व्योम check_bugs(व्योम)
अणु
पूर्ण
#पूर्ण_अगर
