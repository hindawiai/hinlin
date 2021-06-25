<शैली गुरु>
/*
 * Header file क्रम using the wbflush routine
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 1998 Harald Koerfgen
 * Copyright (C) 2002 Maciej W. Rozycki
 */
#अगर_अघोषित _ASM_WBFLUSH_H
#घोषणा _ASM_WBFLUSH_H


#अगर_घोषित CONFIG_CPU_HAS_WB

बाह्य व्योम (*__wbflush)(व्योम);
बाह्य व्योम wbflush_setup(व्योम);

#घोषणा wbflush()			\
	करो अणु				\
		__sync();		\
		__wbflush();		\
	पूर्ण जबतक (0)

#अन्यथा /* !CONFIG_CPU_HAS_WB */

#घोषणा wbflush_setup() करो अणु पूर्ण जबतक (0)

#घोषणा wbflush() fast_iob()

#पूर्ण_अगर /* !CONFIG_CPU_HAS_WB */

#पूर्ण_अगर /* _ASM_WBFLUSH_H */
