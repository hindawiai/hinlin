<शैली गुरु>
/*
 * include/linux/topology.h
 *
 * Written by: Matthew Dobson, IBM Corporation
 *
 * Copyright (C) 2002, IBM Corp.
 *
 * All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Send feedback to <colpatch@us.ibm.com>
 */
#अगर_अघोषित _LINUX_TOPOLOGY_H
#घोषणा _LINUX_TOPOLOGY_H

#समावेश <linux/arch_topology.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/smp.h>
#समावेश <linux/percpu.h>
#समावेश <यंत्र/topology.h>

#अगर_अघोषित nr_cpus_node
#घोषणा nr_cpus_node(node) cpumask_weight(cpumask_of_node(node))
#पूर्ण_अगर

#घोषणा क्रम_each_node_with_cpus(node)			\
	क्रम_each_online_node(node)			\
		अगर (nr_cpus_node(node))

पूर्णांक arch_update_cpu_topology(व्योम);

/* Conक्रमm to ACPI 2.0 SLIT distance definitions */
#घोषणा LOCAL_DISTANCE		10
#घोषणा REMOTE_DISTANCE		20
#घोषणा DISTANCE_BITS           8
#अगर_अघोषित node_distance
#घोषणा node_distance(from,to)	((from) == (to) ? LOCAL_DISTANCE : REMOTE_DISTANCE)
#पूर्ण_अगर
#अगर_अघोषित RECLAIM_DISTANCE
/*
 * If the distance between nodes in a प्रणाली is larger than RECLAIM_DISTANCE
 * (in whatever arch specअगरic measurement units वापसed by node_distance())
 * and node_reclaim_mode is enabled then the VM will only call node_reclaim()
 * on nodes within this distance.
 */
#घोषणा RECLAIM_DISTANCE 30
#पूर्ण_अगर

/*
 * The following tunable allows platक्रमms to override the शेष node
 * reclaim distance (RECLAIM_DISTANCE) अगर remote memory accesses are
 * sufficiently fast that the शेष value actually hurts
 * perक्रमmance.
 *
 * AMD EPYC machines use this because even though the 2-hop distance
 * is 32 (3.2x slower than a local memory access) perक्रमmance actually
 * *improves* अगर allowed to reclaim memory and load balance tasks
 * between NUMA nodes 2-hops apart.
 */
बाह्य पूर्णांक __पढ़ो_mostly node_reclaim_distance;

#अगर_अघोषित PENALTY_FOR_NODE_WITH_CPUS
#घोषणा PENALTY_FOR_NODE_WITH_CPUS	(1)
#पूर्ण_अगर

#अगर_घोषित CONFIG_USE_PERCPU_NUMA_NODE_ID
DECLARE_PER_CPU(पूर्णांक, numa_node);

#अगर_अघोषित numa_node_id
/* Returns the number of the current Node. */
अटल अंतरभूत पूर्णांक numa_node_id(व्योम)
अणु
	वापस raw_cpu_पढ़ो(numa_node);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित cpu_to_node
अटल अंतरभूत पूर्णांक cpu_to_node(पूर्णांक cpu)
अणु
	वापस per_cpu(numa_node, cpu);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित set_numa_node
अटल अंतरभूत व्योम set_numa_node(पूर्णांक node)
अणु
	this_cpu_ग_लिखो(numa_node, node);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित set_cpu_numa_node
अटल अंतरभूत व्योम set_cpu_numa_node(पूर्णांक cpu, पूर्णांक node)
अणु
	per_cpu(numa_node, cpu) = node;
पूर्ण
#पूर्ण_अगर

#अन्यथा	/* !CONFIG_USE_PERCPU_NUMA_NODE_ID */

/* Returns the number of the current Node. */
#अगर_अघोषित numa_node_id
अटल अंतरभूत पूर्णांक numa_node_id(व्योम)
अणु
	वापस cpu_to_node(raw_smp_processor_id());
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* [!]CONFIG_USE_PERCPU_NUMA_NODE_ID */

#अगर_घोषित CONFIG_HAVE_MEMORYLESS_NODES

/*
 * N.B., Do NOT reference the '_numa_mem_' per cpu variable directly.
 * It will not be defined when CONFIG_HAVE_MEMORYLESS_NODES is not defined.
 * Use the accessor functions set_numa_mem(), numa_mem_id() and cpu_to_mem().
 */
DECLARE_PER_CPU(पूर्णांक, _numa_mem_);

#अगर_अघोषित set_numa_mem
अटल अंतरभूत व्योम set_numa_mem(पूर्णांक node)
अणु
	this_cpu_ग_लिखो(_numa_mem_, node);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित numa_mem_id
/* Returns the number of the nearest Node with memory */
अटल अंतरभूत पूर्णांक numa_mem_id(व्योम)
अणु
	वापस raw_cpu_पढ़ो(_numa_mem_);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित cpu_to_mem
अटल अंतरभूत पूर्णांक cpu_to_mem(पूर्णांक cpu)
अणु
	वापस per_cpu(_numa_mem_, cpu);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित set_cpu_numa_mem
अटल अंतरभूत व्योम set_cpu_numa_mem(पूर्णांक cpu, पूर्णांक node)
अणु
	per_cpu(_numa_mem_, cpu) = node;
पूर्ण
#पूर्ण_अगर

#अन्यथा	/* !CONFIG_HAVE_MEMORYLESS_NODES */

#अगर_अघोषित numa_mem_id
/* Returns the number of the nearest Node with memory */
अटल अंतरभूत पूर्णांक numa_mem_id(व्योम)
अणु
	वापस numa_node_id();
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित cpu_to_mem
अटल अंतरभूत पूर्णांक cpu_to_mem(पूर्णांक cpu)
अणु
	वापस cpu_to_node(cpu);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* [!]CONFIG_HAVE_MEMORYLESS_NODES */

#अगर_अघोषित topology_physical_package_id
#घोषणा topology_physical_package_id(cpu)	((व्योम)(cpu), -1)
#पूर्ण_अगर
#अगर_अघोषित topology_die_id
#घोषणा topology_die_id(cpu)			((व्योम)(cpu), -1)
#पूर्ण_अगर
#अगर_अघोषित topology_core_id
#घोषणा topology_core_id(cpu)			((व्योम)(cpu), 0)
#पूर्ण_अगर
#अगर_अघोषित topology_sibling_cpumask
#घोषणा topology_sibling_cpumask(cpu)		cpumask_of(cpu)
#पूर्ण_अगर
#अगर_अघोषित topology_core_cpumask
#घोषणा topology_core_cpumask(cpu)		cpumask_of(cpu)
#पूर्ण_अगर
#अगर_अघोषित topology_die_cpumask
#घोषणा topology_die_cpumask(cpu)		cpumask_of(cpu)
#पूर्ण_अगर

#अगर defined(CONFIG_SCHED_SMT) && !defined(cpu_smt_mask)
अटल अंतरभूत स्थिर काष्ठा cpumask *cpu_smt_mask(पूर्णांक cpu)
अणु
	वापस topology_sibling_cpumask(cpu);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत स्थिर काष्ठा cpumask *cpu_cpu_mask(पूर्णांक cpu)
अणु
	वापस cpumask_of_node(cpu_to_node(cpu));
पूर्ण


#पूर्ण_अगर /* _LINUX_TOPOLOGY_H */
