<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _ASM_VERMAGIC_H
#घोषणा _ASM_VERMAGIC_H

#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
# अगरdef CONFIG_CPU_SH2
#  define MODULE_PROC_FAMILY "SH2LE "
# elअगर defined  CONFIG_CPU_SH3
#  define MODULE_PROC_FAMILY "SH3LE "
# elअगर defined  CONFIG_CPU_SH4
#  define MODULE_PROC_FAMILY "SH4LE "
# अन्यथा
#  error unknown processor family
# endअगर
#अन्यथा
# अगरdef CONFIG_CPU_SH2
#  define MODULE_PROC_FAMILY "SH2BE "
# elअगर defined  CONFIG_CPU_SH3
#  define MODULE_PROC_FAMILY "SH3BE "
# elअगर defined  CONFIG_CPU_SH4
#  define MODULE_PROC_FAMILY "SH4BE "
# अन्यथा
#  error unknown processor family
# endअगर
#पूर्ण_अगर

#घोषणा MODULE_ARCH_VERMAGIC MODULE_PROC_FAMILY

#पूर्ण_अगर /* _ASM_VERMAGIC_H */
