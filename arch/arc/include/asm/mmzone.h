<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित _ASM_ARC_MMZONE_H
#घोषणा _ASM_ARC_MMZONE_H

#अगर_घोषित CONFIG_DISCONTIGMEM

बाह्य काष्ठा pglist_data node_data[];
#घोषणा NODE_DATA(nid) (&node_data[nid])

अटल अंतरभूत पूर्णांक pfn_to_nid(अचिन्हित दीर्घ pfn)
अणु
	पूर्णांक is_end_low = 1;

	अगर (IS_ENABLED(CONFIG_ARC_HAS_PAE40))
		is_end_low = pfn <= virt_to_pfn(0xFFFFFFFFUL);

	/*
	 * node 0: lowmem:             0x8000_0000   to 0xFFFF_FFFF
	 * node 1: HIGHMEM w/o  PAE40: 0x0           to 0x7FFF_FFFF
	 *         HIGHMEM with PAE40: 0x1_0000_0000 to ...
	 */
	अगर (pfn >= ARCH_PFN_OFFSET && is_end_low)
		वापस 0;

	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक pfn_valid(अचिन्हित दीर्घ pfn)
अणु
	पूर्णांक nid = pfn_to_nid(pfn);

	वापस (pfn <= node_end_pfn(nid));
पूर्ण
#पूर्ण_अगर /* CONFIG_DISCONTIGMEM  */

#पूर्ण_अगर
