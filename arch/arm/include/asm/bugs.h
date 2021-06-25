<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/bugs.h
 *
 *  Copyright (C) 1995-2003 Russell King
 */
#अगर_अघोषित __ASM_BUGS_H
#घोषणा __ASM_BUGS_H

बाह्य व्योम check_ग_लिखोbuffer_bugs(व्योम);

#अगर_घोषित CONFIG_MMU
बाह्य व्योम check_bugs(व्योम);
बाह्य व्योम check_other_bugs(व्योम);
#अन्यथा
#घोषणा check_bugs() करो अणु पूर्ण जबतक (0)
#घोषणा check_other_bugs() करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर
