<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_NUMA_H
#घोषणा _LINUX_NUMA_H


#अगर_घोषित CONFIG_NODES_SHIFT
#घोषणा NODES_SHIFT     CONFIG_NODES_SHIFT
#अन्यथा
#घोषणा NODES_SHIFT     0
#पूर्ण_अगर

#घोषणा MAX_NUMNODES    (1 << NODES_SHIFT)

#घोषणा	NUMA_NO_NODE	(-1)

#पूर्ण_अगर /* _LINUX_NUMA_H */
