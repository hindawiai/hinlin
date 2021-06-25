<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/glue-df.h
 *
 *  Copyright (C) 1997-1999 Russell King
 *  Copyright (C) 2000-2002 Deep Blue Solutions Ltd.
 */
#अगर_अघोषित ASM_GLUE_DF_H
#घोषणा ASM_GLUE_DF_H

#समावेश <यंत्र/glue.h>

/*
 *	Data Abort Model
 *	================
 *
 *	We have the following to choose from:
 *	  arm7		- ARM7 style
 *	  v4_early	- ARMv4 without Thumb early पात handler
 *	  v4t_late	- ARMv4 with Thumb late पात handler
 *	  v4t_early	- ARMv4 with Thumb early पात handler
 *	  v5t_early	- ARMv5 with Thumb early पात handler
 *	  v5tj_early	- ARMv5 with Thumb and Java early पात handler
 *	  xscale	- ARMv5 with Thumb with Xscale extensions
 *	  v6_early	- ARMv6 generic early पात handler
 *	  v7_early	- ARMv7 generic early पात handler
 */
#अघोषित CPU_DABORT_HANDLER
#अघोषित MULTI_DABORT

#अगर_घोषित CONFIG_CPU_ABRT_EV4
# अगरdef CPU_DABORT_HANDLER
#  define MULTI_DABORT 1
# अन्यथा
#  define CPU_DABORT_HANDLER v4_early_पात
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_ABRT_LV4T
# अगरdef CPU_DABORT_HANDLER
#  define MULTI_DABORT 1
# अन्यथा
#  define CPU_DABORT_HANDLER v4t_late_पात
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_ABRT_EV4T
# अगरdef CPU_DABORT_HANDLER
#  define MULTI_DABORT 1
# अन्यथा
#  define CPU_DABORT_HANDLER v4t_early_पात
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_ABRT_EV5T
# अगरdef CPU_DABORT_HANDLER
#  define MULTI_DABORT 1
# अन्यथा
#  define CPU_DABORT_HANDLER v5t_early_पात
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_ABRT_EV5TJ
# अगरdef CPU_DABORT_HANDLER
#  define MULTI_DABORT 1
# अन्यथा
#  define CPU_DABORT_HANDLER v5tj_early_पात
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_ABRT_EV6
# अगरdef CPU_DABORT_HANDLER
#  define MULTI_DABORT 1
# अन्यथा
#  define CPU_DABORT_HANDLER v6_early_पात
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_ABRT_EV7
# अगरdef CPU_DABORT_HANDLER
#  define MULTI_DABORT 1
# अन्यथा
#  define CPU_DABORT_HANDLER v7_early_पात
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_ABRT_NOMMU
# अगरdef CPU_DABORT_HANDLER
#  define MULTI_DABORT 1
# अन्यथा
#  define CPU_DABORT_HANDLER nommu_early_पात
# endअगर
#पूर्ण_अगर

#अगर_अघोषित CPU_DABORT_HANDLER
#त्रुटि Unknown data पात handler type
#पूर्ण_अगर

#पूर्ण_अगर
