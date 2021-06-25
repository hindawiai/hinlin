<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 by Ralf Baechle (ralf@linux-mips.org)
 */
#अगर_अघोषित __ASM_R4K_TIMER_H
#घोषणा __ASM_R4K_TIMER_H

#समावेश <linux/compiler.h>

#अगर_घोषित CONFIG_SYNC_R4K

बाह्य व्योम synchronise_count_master(पूर्णांक cpu);
बाह्य व्योम synchronise_count_slave(पूर्णांक cpu);

#अन्यथा

अटल अंतरभूत व्योम synchronise_count_master(पूर्णांक cpu)
अणु
पूर्ण

अटल अंतरभूत व्योम synchronise_count_slave(पूर्णांक cpu)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_R4K_TIMER_H */
