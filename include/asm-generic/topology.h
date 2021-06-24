<शैली गुरु>
/*
 * linux/include/यंत्र-generic/topology.h
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
#अगर_अघोषित _ASM_GENERIC_TOPOLOGY_H
#घोषणा _ASM_GENERIC_TOPOLOGY_H

#अगर_अघोषित	CONFIG_NUMA

/* Other architectures wishing to use this simple topology API should fill
   in the below functions as appropriate in their own <यंत्र/topology.h> file. */
#अगर_अघोषित cpu_to_node
#घोषणा cpu_to_node(cpu)	((व्योम)(cpu),0)
#पूर्ण_अगर
#अगर_अघोषित set_numa_node
#घोषणा set_numa_node(node)
#पूर्ण_अगर
#अगर_अघोषित set_cpu_numa_node
#घोषणा set_cpu_numa_node(cpu, node)
#पूर्ण_अगर
#अगर_अघोषित cpu_to_mem
#घोषणा cpu_to_mem(cpu)		((व्योम)(cpu),0)
#पूर्ण_अगर

#अगर_अघोषित cpumask_of_node
  #अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
    #घोषणा cpumask_of_node(node)	((node) == 0 ? cpu_online_mask : cpu_none_mask)
  #अन्यथा
    #घोषणा cpumask_of_node(node)	((व्योम)(node), cpu_online_mask)
  #पूर्ण_अगर
#पूर्ण_अगर
#अगर_अघोषित pcibus_to_node
#घोषणा pcibus_to_node(bus)	((व्योम)(bus), -1)
#पूर्ण_अगर

#अगर_अघोषित cpumask_of_pcibus
#घोषणा cpumask_of_pcibus(bus)	(pcibus_to_node(bus) == -1 ?		\
				 cpu_all_mask :				\
				 cpumask_of_node(pcibus_to_node(bus)))
#पूर्ण_अगर

#पूर्ण_अगर	/* CONFIG_NUMA */

#अगर !defined(CONFIG_NUMA) || !defined(CONFIG_HAVE_MEMORYLESS_NODES)

#अगर_अघोषित set_numa_mem
#घोषणा set_numa_mem(node)
#पूर्ण_अगर
#अगर_अघोषित set_cpu_numa_mem
#घोषणा set_cpu_numa_mem(cpu, node)
#पूर्ण_अगर

#पूर्ण_अगर	/* !CONFIG_NUMA || !CONFIG_HAVE_MEMORYLESS_NODES */

#पूर्ण_अगर /* _ASM_GENERIC_TOPOLOGY_H */
