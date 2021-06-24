<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 2000,2003 Silicon Graphics, Inc.  All rights reserved.
 * Copyright (c) 2002 NEC Corp.
 * Copyright (c) 2002 Erich Focht <efocht@ess.nec.de>
 * Copyright (c) 2002 Kimio Suganuma <k-suganuma@da.jp.nec.com>
 */
#अगर_अघोषित _ASM_IA64_MMZONE_H
#घोषणा _ASM_IA64_MMZONE_H

#समावेश <linux/numa.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/meminit.h>

#अगर_घोषित CONFIG_NUMA

अटल अंतरभूत पूर्णांक pfn_to_nid(अचिन्हित दीर्घ pfn)
अणु
	बाह्य पूर्णांक paddr_to_nid(अचिन्हित दीर्घ);
	पूर्णांक nid = paddr_to_nid(pfn << PAGE_SHIFT);
	अगर (nid < 0)
		वापस 0;
	अन्यथा
		वापस nid;
पूर्ण

#घोषणा MAX_PHYSNODE_ID		2048
#पूर्ण_अगर /* CONFIG_NUMA */

#घोषणा NR_NODE_MEMBLKS		(MAX_NUMNODES * 4)

#पूर्ण_अगर /* _ASM_IA64_MMZONE_H */
