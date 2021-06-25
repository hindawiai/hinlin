<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_MMZONE_H
#घोषणा _SPARC64_MMZONE_H

#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES

#समावेश <linux/cpumask.h>

बाह्य काष्ठा pglist_data *node_data[];

#घोषणा NODE_DATA(nid)		(node_data[nid])

बाह्य पूर्णांक numa_cpu_lookup_table[];
बाह्य cpumask_t numa_cpumask_lookup_table[];

#पूर्ण_अगर /* CONFIG_NEED_MULTIPLE_NODES */

#पूर्ण_अगर /* _SPARC64_MMZONE_H */
