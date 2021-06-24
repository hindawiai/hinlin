<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I/O remap functions क्रम Hexagon
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/पन.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>

व्योम __iomem *ioremap(अचिन्हित दीर्घ phys_addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ last_addr, addr;
	अचिन्हित दीर्घ offset = phys_addr & ~PAGE_MASK;
	काष्ठा vm_काष्ठा *area;

	pgprot_t prot = __pgprot(_PAGE_PRESENT|_PAGE_READ|_PAGE_WRITE
					|(__HEXAGON_C_DEV << 6));

	last_addr = phys_addr + size - 1;

	/*  Wrapping not allowed  */
	अगर (!size || (last_addr < phys_addr))
		वापस शून्य;

	/*  Rounds up to next page size, including whole-page offset */
	size = PAGE_ALIGN(offset + size);

	area = get_vm_area(size, VM_IOREMAP);
	addr = (अचिन्हित दीर्घ)area->addr;

	अगर (ioremap_page_range(addr, addr+size, phys_addr, prot)) अणु
		vunmap((व्योम *)addr);
		वापस शून्य;
	पूर्ण

	वापस (व्योम __iomem *) (offset + addr);
पूर्ण

व्योम iounmap(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	vunmap((व्योम *) ((अचिन्हित दीर्घ) addr & PAGE_MASK));
पूर्ण
