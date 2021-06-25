<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_ARM_TOPOLOGY_H
#घोषणा _ASM_ARM_TOPOLOGY_H

#अगर_घोषित CONFIG_ARM_CPU_TOPOLOGY

#समावेश <linux/cpumask.h>
#समावेश <linux/arch_topology.h>

/* big.LITTLE चयनer is incompatible with frequency invariance */
#अगर_अघोषित CONFIG_BL_SWITCHER
/* Replace task scheduler's शेष frequency-invariant accounting */
#घोषणा arch_set_freq_scale topology_set_freq_scale
#घोषणा arch_scale_freq_capacity topology_get_freq_scale
#घोषणा arch_scale_freq_invariant topology_scale_freq_invariant
#पूर्ण_अगर

/* Replace task scheduler's शेष cpu-invariant accounting */
#घोषणा arch_scale_cpu_capacity topology_get_cpu_scale

/* Enable topology flag updates */
#घोषणा arch_update_cpu_topology topology_update_cpu_topology

/* Replace task scheduler's शेष thermal pressure API */
#घोषणा arch_scale_thermal_pressure topology_get_thermal_pressure
#घोषणा arch_set_thermal_pressure   topology_set_thermal_pressure

#अन्यथा

अटल अंतरभूत व्योम init_cpu_topology(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम store_cpu_topology(अचिन्हित पूर्णांक cpuid) अणु पूर्ण

#पूर्ण_अगर

#समावेश <यंत्र-generic/topology.h>

#पूर्ण_अगर /* _ASM_ARM_TOPOLOGY_H */
