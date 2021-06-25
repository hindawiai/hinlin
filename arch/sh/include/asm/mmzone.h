<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_MMZONE_H
#घोषणा __ASM_SH_MMZONE_H

#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
#समावेश <linux/numa.h>

बाह्य काष्ठा pglist_data *node_data[];
#घोषणा NODE_DATA(nid)		(node_data[nid])

अटल अंतरभूत पूर्णांक pfn_to_nid(अचिन्हित दीर्घ pfn)
अणु
	पूर्णांक nid;

	क्रम (nid = 0; nid < MAX_NUMNODES; nid++)
		अगर (pfn >= node_start_pfn(nid) && pfn <= node_end_pfn(nid))
			अवरोध;

	वापस nid;
पूर्ण

अटल अंतरभूत काष्ठा pglist_data *pfn_to_pgdat(अचिन्हित दीर्घ pfn)
अणु
	वापस NODE_DATA(pfn_to_nid(pfn));
पूर्ण

/* arch/sh/mm/numa.c */
व्योम __init setup_booपंचांगem_node(पूर्णांक nid, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
#अन्यथा
अटल अंतरभूत व्योम
setup_booपंचांगem_node(पूर्णांक nid, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_NEED_MULTIPLE_NODES */

/* Platक्रमm specअगरic mem init */
व्योम __init plat_mem_setup(व्योम);

/* arch/sh/kernel/setup.c */
व्योम __init __add_active_range(अचिन्हित पूर्णांक nid, अचिन्हित दीर्घ start_pfn,
			       अचिन्हित दीर्घ end_pfn);
/* arch/sh/mm/init.c */
व्योम __init allocate_pgdat(अचिन्हित पूर्णांक nid);

#पूर्ण_अगर /* __ASM_SH_MMZONE_H */
