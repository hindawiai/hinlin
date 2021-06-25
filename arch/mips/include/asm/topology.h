<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2007 by Ralf Baechle
 */
#अगर_अघोषित __ASM_TOPOLOGY_H
#घोषणा __ASM_TOPOLOGY_H

#समावेश <topology.h>
#समावेश <linux/smp.h>

#अगर_घोषित CONFIG_SMP
#घोषणा topology_physical_package_id(cpu)	(cpu_data[cpu].package)
#घोषणा topology_core_id(cpu)			(cpu_core(&cpu_data[cpu]))
#घोषणा topology_core_cpumask(cpu)		(&cpu_core_map[cpu])
#घोषणा topology_sibling_cpumask(cpu)		(&cpu_sibling_map[cpu])
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_TOPOLOGY_H */
