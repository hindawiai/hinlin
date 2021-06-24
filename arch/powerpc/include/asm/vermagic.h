<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_VERMAGIC_H
#घोषणा _ASM_VERMAGIC_H

#अगर_घोषित CONFIG_MPROखाता_KERNEL
#घोषणा MODULE_ARCH_VERMAGIC_FTRACE	"mprofile-kernel "
#अन्यथा
#घोषणा MODULE_ARCH_VERMAGIC_FTRACE	""
#पूर्ण_अगर

#अगर_घोषित CONFIG_RELOCATABLE
#घोषणा MODULE_ARCH_VERMAGIC_RELOCATABLE	"relocatable "
#अन्यथा
#घोषणा MODULE_ARCH_VERMAGIC_RELOCATABLE	""
#पूर्ण_अगर

#घोषणा MODULE_ARCH_VERMAGIC \
		MODULE_ARCH_VERMAGIC_FTRACE MODULE_ARCH_VERMAGIC_RELOCATABLE

#पूर्ण_अगर /* _ASM_VERMAGIC_H */
