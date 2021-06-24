<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/plat-omap/sram.c
 *
 * OMAP SRAM detection and management
 *
 * Copyright (C) 2005 Nokia Corporation
 * Written by Tony Lindgren <tony@atomide.com>
 *
 * Copyright (C) 2009-2012 Texas Instruments
 * Added OMAP4/5 support - Santosh Shilimkar <santosh.shilimkar@ti.com>
 */
#अघोषित DEBUG

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/fncpy.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/set_memory.h>

#समावेश <यंत्र/mach/map.h>

#समावेश <plat/sram.h>

#घोषणा ROUND_DOWN(value,boundary)	((value) & (~((boundary)-1)))

अटल व्योम __iomem *omap_sram_base;
अटल अचिन्हित दीर्घ omap_sram_skip;
अटल अचिन्हित दीर्घ omap_sram_size;
अटल व्योम __iomem *omap_sram_उच्चमान;

/*
 * Memory allocator क्रम SRAM: calculates the new उच्चमानing address
 * क्रम pushing a function using the fncpy API.
 *
 * Note that fncpy requires the वापसed address to be aligned
 * to an 8-byte boundary.
 */
अटल व्योम *omap_sram_push_address(अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ available, new_उच्चमान = (अचिन्हित दीर्घ)omap_sram_उच्चमान;

	available = omap_sram_उच्चमान - (omap_sram_base + omap_sram_skip);

	अगर (size > available) अणु
		pr_err("Not enough space in SRAM\n");
		वापस शून्य;
	पूर्ण

	new_उच्चमान -= size;
	new_उच्चमान = ROUND_DOWN(new_उच्चमान, FNCPY_ALIGN);
	omap_sram_उच्चमान = IOMEM(new_उच्चमान);

	वापस (व्योम *)omap_sram_उच्चमान;
पूर्ण

व्योम *omap_sram_push(व्योम *funcp, अचिन्हित दीर्घ size)
अणु
	व्योम *sram;
	अचिन्हित दीर्घ base;
	पूर्णांक pages;
	व्योम *dst = शून्य;

	sram = omap_sram_push_address(size);
	अगर (!sram)
		वापस शून्य;

	base = (अचिन्हित दीर्घ)sram & PAGE_MASK;
	pages = PAGE_ALIGN(size) / PAGE_SIZE;

	set_memory_rw(base, pages);

	dst = fncpy(sram, funcp, size);

	set_memory_ro(base, pages);
	set_memory_x(base, pages);

	वापस dst;
पूर्ण

/*
 * The SRAM context is lost during off-idle and stack
 * needs to be reset.
 */
व्योम omap_sram_reset(व्योम)
अणु
	omap_sram_उच्चमान = omap_sram_base + omap_sram_size;
पूर्ण

/*
 * Note that we cannot use ioremap क्रम SRAM, as घड़ी init needs SRAM early.
 */
व्योम __init omap_map_sram(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size,
				 अचिन्हित दीर्घ skip, पूर्णांक cached)
अणु
	अचिन्हित दीर्घ base;
	पूर्णांक pages;

	अगर (size == 0)
		वापस;

	start = ROUND_DOWN(start, PAGE_SIZE);
	omap_sram_size = size;
	omap_sram_skip = skip;
	omap_sram_base = __arm_ioremap_exec(start, size, cached);
	अगर (!omap_sram_base) अणु
		pr_err("SRAM: Could not map\n");
		वापस;
	पूर्ण

	omap_sram_reset();

	/*
	 * Looks like we need to preserve some bootloader code at the
	 * beginning of SRAM क्रम jumping to flash क्रम reboot to work...
	 */
	स_रखो_io(omap_sram_base + omap_sram_skip, 0,
		  omap_sram_size - omap_sram_skip);

	base = (अचिन्हित दीर्घ)omap_sram_base;
	pages = PAGE_ALIGN(omap_sram_size) / PAGE_SIZE;

	set_memory_ro(base, pages);
	set_memory_x(base, pages);
पूर्ण
