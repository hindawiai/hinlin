<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Written by Kanoj Sarcar (kanoj@sgi.com) Aug 99
 *
 * PowerPC64 port:
 * Copyright (C) 2002 Anton Blanअक्षरd, IBM Corp.
 */
#अगर_अघोषित _ASM_MMZONE_H_
#घोषणा _ASM_MMZONE_H_
#अगर_घोषित __KERNEL__

#समावेश <linux/cpumask.h>

/*
 * generic non-linear memory support:
 *
 * 1) we will not split memory पूर्णांकo more chunks than will fit पूर्णांकo the
 *    flags field of the काष्ठा page
 */

#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES

बाह्य काष्ठा pglist_data *node_data[];
/*
 * Return a poपूर्णांकer to the node data क्रम node n.
 */
#घोषणा NODE_DATA(nid)		(node_data[nid])

/*
 * Following are specअगरic to this numa platक्रमm.
 */

बाह्य पूर्णांक numa_cpu_lookup_table[];
बाह्य cpumask_var_t node_to_cpumask_map[];
#अगर_घोषित CONFIG_MEMORY_HOTPLUG
बाह्य अचिन्हित दीर्घ max_pfn;
u64 memory_hotplug_max(व्योम);
#अन्यथा
#घोषणा memory_hotplug_max() memblock_end_of_DRAM()
#पूर्ण_अगर

#अन्यथा
#घोषणा memory_hotplug_max() memblock_end_of_DRAM()
#पूर्ण_अगर /* CONFIG_NEED_MULTIPLE_NODES */
#अगर_घोषित CONFIG_FA_DUMP
#घोषणा __HAVE_ARCH_RESERVED_KERNEL_PAGES
#पूर्ण_अगर

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
बाह्य पूर्णांक create_section_mapping(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				  पूर्णांक nid, pgprot_t prot);
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_MMZONE_H_ */
