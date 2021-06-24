<शैली गुरु>
/*
 * Written by: Patricia Gaughen <gone@us.ibm.com>, IBM Corporation
 * August 2002: added remote node KVA remap - Martin J. Bligh 
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
 */

#समावेश <linux/memblock.h>
#समावेश <linux/init.h>

#समावेश "numa_internal.h"

बाह्य अचिन्हित दीर्घ highend_pfn, highstart_pfn;

व्योम __init iniपंचांगem_init(व्योम)
अणु
	x86_numa_init();

#अगर_घोषित CONFIG_HIGHMEM
	highstart_pfn = highend_pfn = max_pfn;
	अगर (max_pfn > max_low_pfn)
		highstart_pfn = max_low_pfn;
	prपूर्णांकk(KERN_NOTICE "%ldMB HIGHMEM available.\n",
	       pages_to_mb(highend_pfn - highstart_pfn));
	high_memory = (व्योम *) __va(highstart_pfn * PAGE_SIZE - 1) + 1;
#अन्यथा
	high_memory = (व्योम *) __va(max_low_pfn * PAGE_SIZE - 1) + 1;
#पूर्ण_अगर
	prपूर्णांकk(KERN_NOTICE "%ldMB LOWMEM available.\n",
			pages_to_mb(max_low_pfn));
	prपूर्णांकk(KERN_DEBUG "max_low_pfn = %lx, highstart_pfn = %lx\n",
			max_low_pfn, highstart_pfn);

	prपूर्णांकk(KERN_DEBUG "Low memory ends at vaddr %08lx\n",
			(uदीर्घ) pfn_to_kaddr(max_low_pfn));

	prपूर्णांकk(KERN_DEBUG "High memory starts at vaddr %08lx\n",
			(uदीर्घ) pfn_to_kaddr(highstart_pfn));

	__vदो_स्मृति_start_set = true;
	setup_booपंचांगem_allocator();
पूर्ण
