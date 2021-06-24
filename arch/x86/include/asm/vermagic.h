<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _ASM_VERMAGIC_H
#घोषणा _ASM_VERMAGIC_H

#अगर_घोषित CONFIG_X86_64
/* X86_64 करोes not define MODULE_PROC_FAMILY */
#या_अगर defined CONFIG_M486SX
#घोषणा MODULE_PROC_FAMILY "486SX "
#या_अगर defined CONFIG_M486
#घोषणा MODULE_PROC_FAMILY "486 "
#या_अगर defined CONFIG_M586
#घोषणा MODULE_PROC_FAMILY "586 "
#या_अगर defined CONFIG_M586TSC
#घोषणा MODULE_PROC_FAMILY "586TSC "
#या_अगर defined CONFIG_M586MMX
#घोषणा MODULE_PROC_FAMILY "586MMX "
#या_अगर defined CONFIG_MCORE2
#घोषणा MODULE_PROC_FAMILY "CORE2 "
#या_अगर defined CONFIG_MATOM
#घोषणा MODULE_PROC_FAMILY "ATOM "
#या_अगर defined CONFIG_M686
#घोषणा MODULE_PROC_FAMILY "686 "
#या_अगर defined CONFIG_MPENTIUMII
#घोषणा MODULE_PROC_FAMILY "PENTIUMII "
#या_अगर defined CONFIG_MPENTIUMIII
#घोषणा MODULE_PROC_FAMILY "PENTIUMIII "
#या_अगर defined CONFIG_MPENTIUMM
#घोषणा MODULE_PROC_FAMILY "PENTIUMM "
#या_अगर defined CONFIG_MPENTIUM4
#घोषणा MODULE_PROC_FAMILY "PENTIUM4 "
#या_अगर defined CONFIG_MK6
#घोषणा MODULE_PROC_FAMILY "K6 "
#या_अगर defined CONFIG_MK7
#घोषणा MODULE_PROC_FAMILY "K7 "
#या_अगर defined CONFIG_MK8
#घोषणा MODULE_PROC_FAMILY "K8 "
#या_अगर defined CONFIG_MELAN
#घोषणा MODULE_PROC_FAMILY "ELAN "
#या_अगर defined CONFIG_MCRUSOE
#घोषणा MODULE_PROC_FAMILY "CRUSOE "
#या_अगर defined CONFIG_MEFFICEON
#घोषणा MODULE_PROC_FAMILY "EFFICEON "
#या_अगर defined CONFIG_MWINCHIPC6
#घोषणा MODULE_PROC_FAMILY "WINCHIPC6 "
#या_अगर defined CONFIG_MWINCHIP3D
#घोषणा MODULE_PROC_FAMILY "WINCHIP3D "
#या_अगर defined CONFIG_MCYRIXIII
#घोषणा MODULE_PROC_FAMILY "CYRIXIII "
#या_अगर defined CONFIG_MVIAC3_2
#घोषणा MODULE_PROC_FAMILY "VIAC3-2 "
#या_अगर defined CONFIG_MVIAC7
#घोषणा MODULE_PROC_FAMILY "VIAC7 "
#या_अगर defined CONFIG_MGEODEGX1
#घोषणा MODULE_PROC_FAMILY "GEODEGX1 "
#या_अगर defined CONFIG_MGEODE_LX
#घोषणा MODULE_PROC_FAMILY "GEODE "
#अन्यथा
#त्रुटि unknown processor family
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_32
# define MODULE_ARCH_VERMAGIC MODULE_PROC_FAMILY
#अन्यथा
# define MODULE_ARCH_VERMAGIC ""
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_VERMAGIC_H */
