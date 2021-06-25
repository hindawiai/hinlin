<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2007 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2007 Eugene Konev <ejka@खोलोwrt.org>
 */
#समावेश <linux/memblock.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/pfn.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/swap.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/sections.h>

#समावेश <यंत्र/mach-ar7/ar7.h>

अटल पूर्णांक __init memsize(व्योम)
अणु
	u32 size = (64 << 20);
	u32 *addr = (u32 *)KSEG1ADDR(AR7_SDRAM_BASE + size - 4);
	u32 *kernel_end = (u32 *)KSEG1ADDR(CPHYSADDR((u32)&_end));
	u32 *पंचांगpaddr = addr;

	जबतक (पंचांगpaddr > kernel_end) अणु
		*पंचांगpaddr = (u32)पंचांगpaddr;
		size >>= 1;
		पंचांगpaddr -= size >> 2;
	पूर्ण

	करो अणु
		पंचांगpaddr += size >> 2;
		अगर (*पंचांगpaddr != (u32)पंचांगpaddr)
			अवरोध;
		size <<= 1;
	पूर्ण जबतक (size < (64 << 20));

	ग_लिखोl((u32)पंचांगpaddr, &addr);

	वापस size;
पूर्ण

व्योम __init prom_meminit(व्योम)
अणु
	अचिन्हित दीर्घ pages;

	pages = memsize() >> PAGE_SHIFT;
	memblock_add(PHYS_OFFSET, pages << PAGE_SHIFT);
पूर्ण
