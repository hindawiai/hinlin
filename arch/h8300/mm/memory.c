<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/h8300/mm/memory.c
 *
 *  Copyright (C) 2002  Yoshinori Sato <ysato@users.sourceक्रमge.jp>,
 *
 *  Based on:
 *
 *  linux/arch/m68knommu/mm/memory.c
 *
 *  Copyright (C) 1998  Kenneth Albanowski <kjahds@kjahds.com>,
 *  Copyright (C) 1999-2002, Greg Ungerer (gerg@snapgear.com)
 *
 *  Based on:
 *
 *  linux/arch/m68k/mm/memory.c
 *
 *  Copyright (C) 1995  Hamish Macकरोnald
 */

#समावेश <linux/mm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/पन.स>

व्योम cache_clear(अचिन्हित दीर्घ paddr, पूर्णांक len)
अणु
पूर्ण


व्योम cache_push(अचिन्हित दीर्घ paddr, पूर्णांक len)
अणु
पूर्ण

व्योम cache_push_v(अचिन्हित दीर्घ vaddr, पूर्णांक len)
अणु
पूर्ण

/*
 * Map some physical address range पूर्णांकo the kernel address space.
 */

अचिन्हित दीर्घ kernel_map(अचिन्हित दीर्घ paddr, अचिन्हित दीर्घ size,
			 पूर्णांक nocacheflag, अचिन्हित दीर्घ *memavailp)
अणु
	वापस paddr;
पूर्ण
