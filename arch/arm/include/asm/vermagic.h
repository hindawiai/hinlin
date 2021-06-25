<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_VERMAGIC_H
#घोषणा _ASM_VERMAGIC_H

#समावेश <linux/stringअगरy.h>

/*
 * Add the ARM architecture version to the version magic string
 */
#घोषणा MODULE_ARCH_VERMAGIC_ARMVSN "ARMv" __stringअगरy(__LINUX_ARM_ARCH__) " "

/* Add __virt_to_phys patching state as well */
#अगर_घोषित CONFIG_ARM_PATCH_PHYS_VIRT
#घोषणा MODULE_ARCH_VERMAGIC_P2V "p2v8 "
#अन्यथा
#घोषणा MODULE_ARCH_VERMAGIC_P2V ""
#पूर्ण_अगर

/* Add inकाष्ठाion set architecture tag to distinguish ARM/Thumb kernels */
#अगर_घोषित CONFIG_THUMB2_KERNEL
#घोषणा MODULE_ARCH_VERMAGIC_ARMTHUMB "thumb2 "
#अन्यथा
#घोषणा MODULE_ARCH_VERMAGIC_ARMTHUMB ""
#पूर्ण_अगर

#घोषणा MODULE_ARCH_VERMAGIC \
	MODULE_ARCH_VERMAGIC_ARMVSN \
	MODULE_ARCH_VERMAGIC_ARMTHUMB \
	MODULE_ARCH_VERMAGIC_P2V

#पूर्ण_अगर /* _ASM_VERMAGIC_H */
