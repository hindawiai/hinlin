<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2013 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_MMU_H
#घोषणा _XTENSA_MMU_H

#अगर_अघोषित CONFIG_MMU
#समावेश <यंत्र-generic/mmu.h>
#अन्यथा

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ asid[NR_CPUS];
	अचिन्हित पूर्णांक cpu;
पूर्ण mm_context_t;

#पूर्ण_अगर /* CONFIG_MMU */
#पूर्ण_अगर	/* _XTENSA_MMU_H */
