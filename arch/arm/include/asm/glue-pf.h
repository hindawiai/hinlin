<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/glue-pf.h
 *
 *  Copyright (C) 1997-1999 Russell King
 *  Copyright (C) 2000-2002 Deep Blue Solutions Ltd.
 */
#अगर_अघोषित ASM_GLUE_PF_H
#घोषणा ASM_GLUE_PF_H

#समावेश <यंत्र/glue.h>

/*
 *	Prefetch Abort Model
 *	================
 *
 *	We have the following to choose from:
 *	  legacy	- no IFSR, no IFAR
 *	  v6		- ARMv6: IFSR, no IFAR
 *	  v7		- ARMv7: IFSR and IFAR
 */

#अघोषित CPU_PABORT_HANDLER
#अघोषित MULTI_PABORT

#अगर_घोषित CONFIG_CPU_PABRT_LEGACY
# अगरdef CPU_PABORT_HANDLER
#  define MULTI_PABORT 1
# अन्यथा
#  define CPU_PABORT_HANDLER legacy_pपात
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_PABRT_V6
# अगरdef CPU_PABORT_HANDLER
#  define MULTI_PABORT 1
# अन्यथा
#  define CPU_PABORT_HANDLER v6_pपात
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_PABRT_V7
# अगरdef CPU_PABORT_HANDLER
#  define MULTI_PABORT 1
# अन्यथा
#  define CPU_PABORT_HANDLER v7_pपात
# endअगर
#पूर्ण_अगर

#अगर_अघोषित CPU_PABORT_HANDLER
#त्रुटि Unknown prefetch पात handler type
#पूर्ण_अगर

#पूर्ण_अगर
