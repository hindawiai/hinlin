<शैली गुरु>
/*
 * OpenRISC समयr API
 *
 * Copyright (C) 2017 by Stafक्रमd Horne (shorne@gmail.com)
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#अगर_अघोषित __ASM_OR1K_TIME_H
#घोषणा __ASM_OR1K_TIME_H

बाह्य व्योम खोलोrisc_घड़ीevent_init(व्योम);

बाह्य व्योम खोलोrisc_समयr_set(अचिन्हित दीर्घ count);
बाह्य व्योम खोलोrisc_समयr_set_next(अचिन्हित दीर्घ delta);

#अगर_घोषित CONFIG_SMP
बाह्य व्योम synchronise_count_master(पूर्णांक cpu);
बाह्य व्योम synchronise_count_slave(पूर्णांक cpu);
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_OR1K_TIME_H */
