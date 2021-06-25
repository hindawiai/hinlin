<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* include/यंत्र/current.h
 *
 * Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation
 * Copyright (C) 2002 Pete Zaitcev (zaitcev@yahoo.com)
 * Copyright (C) 2007 David S. Miller (davem@davemloft.net)
 *
 *  Derived from "include/asm-s390/current.h" by
 *  Martin Schwidefsky (schwidefsky@de.ibm.com)
 *  Derived from "include/asm-i386/current.h"
*/
#अगर_अघोषित _SPARC_CURRENT_H
#घोषणा _SPARC_CURRENT_H

#समावेश <linux/thपढ़ो_info.h>

#अगर_घोषित CONFIG_SPARC64
रेजिस्टर काष्ठा task_काष्ठा *current यंत्र("g4");
#पूर्ण_अगर

#अगर_घोषित CONFIG_SPARC32
/* We might want to consider using %g4 like sparc64 to shave a few cycles.
 *
 * Two stage process (अंतरभूत + #घोषणा) क्रम type-checking.
 * We also obfuscate get_current() to check अगर anyone used that by mistake.
 */
काष्ठा task_काष्ठा;
अटल अंतरभूत काष्ठा task_काष्ठा *__get_current(व्योम)
अणु
	वापस current_thपढ़ो_info()->task;
पूर्ण
#घोषणा current __get_current()
#पूर्ण_अगर

#पूर्ण_अगर /* !(_SPARC_CURRENT_H) */
