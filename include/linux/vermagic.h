<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_VERMAGIC_H
#घोषणा _LINUX_VERMAGIC_H

#अगर_अघोषित INCLUDE_VERMAGIC
#त्रुटि "This header can be included from kernel/module.c or *.mod.c only"
#पूर्ण_अगर

#समावेश <generated/utsrelease.h>
#समावेश <यंत्र/vermagic.h>

/* Simply sanity version stamp क्रम modules. */
#अगर_घोषित CONFIG_SMP
#घोषणा MODULE_VERMAGIC_SMP "SMP "
#अन्यथा
#घोषणा MODULE_VERMAGIC_SMP ""
#पूर्ण_अगर
#अगर_घोषित CONFIG_PREEMPT
#घोषणा MODULE_VERMAGIC_PREEMPT "preempt "
#या_अगर defined(CONFIG_PREEMPT_RT)
#घोषणा MODULE_VERMAGIC_PREEMPT "preempt_rt "
#अन्यथा
#घोषणा MODULE_VERMAGIC_PREEMPT ""
#पूर्ण_अगर
#अगर_घोषित CONFIG_MODULE_UNLOAD
#घोषणा MODULE_VERMAGIC_MODULE_UNLOAD "mod_unload "
#अन्यथा
#घोषणा MODULE_VERMAGIC_MODULE_UNLOAD ""
#पूर्ण_अगर
#अगर_घोषित CONFIG_MODVERSIONS
#घोषणा MODULE_VERMAGIC_MODVERSIONS "modversions "
#अन्यथा
#घोषणा MODULE_VERMAGIC_MODVERSIONS ""
#पूर्ण_अगर
#अगर_घोषित RANDSTRUCT_PLUGIN
#समावेश <generated/अक्रमomize_layout_hash.h>
#घोषणा MODULE_RANDSTRUCT_PLUGIN "RANDSTRUCT_PLUGIN_" RANDSTRUCT_HASHED_SEED
#अन्यथा
#घोषणा MODULE_RANDSTRUCT_PLUGIN
#पूर्ण_अगर

#घोषणा VERMAGIC_STRING 						\
	UTS_RELEASE " "							\
	MODULE_VERMAGIC_SMP MODULE_VERMAGIC_PREEMPT 			\
	MODULE_VERMAGIC_MODULE_UNLOAD MODULE_VERMAGIC_MODVERSIONS	\
	MODULE_ARCH_VERMAGIC						\
	MODULE_RANDSTRUCT_PLUGIN

#पूर्ण_अगर /* _LINUX_VERMAGIC_H */
