<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/glue-proc.h
 *
 *  Copyright (C) 1997-1999 Russell King
 *  Copyright (C) 2000 Deep Blue Solutions Ltd
 */
#अगर_अघोषित ASM_GLUE_PROC_H
#घोषणा ASM_GLUE_PROC_H

#समावेश <यंत्र/glue.h>

/*
 * Work out अगर we need multiple CPU support
 */
#अघोषित MULTI_CPU
#अघोषित CPU_NAME

/*
 * CPU_NAME - the prefix क्रम CPU related functions
 */

#अगर_घोषित CONFIG_CPU_ARM7TDMI
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_arm7tdmi
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_ARM720T
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_arm720
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_ARM740T
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_arm740
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_ARM9TDMI
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_arm9tdmi
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_ARM920T
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_arm920
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_ARM922T
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_arm922
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_FA526
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_fa526
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_ARM925T
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_arm925
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_ARM926T
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_arm926
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_ARM940T
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_arm940
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_ARM946E
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_arm946
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_SA110
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_sa110
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_SA1100
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_sa1100
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_ARM1020
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_arm1020
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_ARM1020E
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_arm1020e
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_ARM1022
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_arm1022
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_ARM1026
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_arm1026
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_XSCALE
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_xscale
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_XSC3
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_xsc3
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_MOHAWK
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_mohawk
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_FEROCEON
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_feroceon
# endअगर
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_V6) || defined(CONFIG_CPU_V6K)
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_v6
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_V7M
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_v7m
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_PJ4B
# अगरdef CPU_NAME
#  undef  MULTI_CPU
#  define MULTI_CPU
# अन्यथा
#  define CPU_NAME cpu_pj4b
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_V7
/*
 * Cortex-A9 needs a dअगरferent suspend/resume function, so we need
 * multiple CPU support क्रम ARMv7 anyway.
 */
#  undef  MULTI_CPU
#  define MULTI_CPU
#पूर्ण_अगर

#अगर_अघोषित MULTI_CPU
#घोषणा cpu_proc_init			__glue(CPU_NAME,_proc_init)
#घोषणा cpu_proc_fin			__glue(CPU_NAME,_proc_fin)
#घोषणा cpu_reset			__glue(CPU_NAME,_reset)
#घोषणा cpu_करो_idle			__glue(CPU_NAME,_करो_idle)
#घोषणा cpu_dcache_clean_area		__glue(CPU_NAME,_dcache_clean_area)
#घोषणा cpu_करो_चयन_mm		__glue(CPU_NAME,_चयन_mm)
#घोषणा cpu_set_pte_ext			__glue(CPU_NAME,_set_pte_ext)
#घोषणा cpu_suspend_size		__glue(CPU_NAME,_suspend_size)
#घोषणा cpu_करो_suspend			__glue(CPU_NAME,_करो_suspend)
#घोषणा cpu_करो_resume			__glue(CPU_NAME,_करो_resume)
#पूर्ण_अगर

#पूर्ण_अगर
