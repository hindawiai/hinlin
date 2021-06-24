<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP SRAM detection and management
 *
 * Copyright (C) 2005 Nokia Corporation
 * Written by Tony Lindgren <tony@atomide.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/fncpy.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/cacheflush.h>

#समावेश <यंत्र/mach/map.h>

#समावेश "soc.h"
#समावेश "sram.h"

#घोषणा OMAP1_SRAM_PA		0x20000000
#घोषणा SRAM_BOOTLOADER_SZ	0x80

/*
 * The amount of SRAM depends on the core type.
 * Note that we cannot try to test क्रम SRAM here because ग_लिखोs
 * to secure SRAM will hang the प्रणाली. Also the SRAM is not
 * yet mapped at this poपूर्णांक.
 */
अटल व्योम __init omap_detect_and_map_sram(व्योम)
अणु
	अचिन्हित दीर्घ omap_sram_skip = SRAM_BOOTLOADER_SZ;
	अचिन्हित दीर्घ omap_sram_start = OMAP1_SRAM_PA;
	अचिन्हित दीर्घ omap_sram_size;

	अगर (cpu_is_omap7xx())
		omap_sram_size = 0x32000;	/* 200K */
	अन्यथा अगर (cpu_is_omap15xx())
		omap_sram_size = 0x30000;	/* 192K */
	अन्यथा अगर (cpu_is_omap1610() || cpu_is_omap1611() ||
			cpu_is_omap1621() || cpu_is_omap1710())
		omap_sram_size = 0x4000;	/* 16K */
	अन्यथा अणु
		pr_err("Could not detect SRAM size\n");
		omap_sram_size = 0x4000;
	पूर्ण

	omap_map_sram(omap_sram_start, omap_sram_size,
		omap_sram_skip, 1);
पूर्ण

अटल व्योम (*_omap_sram_reprogram_घड़ी)(u32 dpllctl, u32 ckctl);

व्योम omap_sram_reprogram_घड़ी(u32 dpllctl, u32 ckctl)
अणु
	BUG_ON(!_omap_sram_reprogram_घड़ी);
	/* On 730, bit 13 must always be 1 */
	अगर (cpu_is_omap7xx())
		ckctl |= 0x2000;
	_omap_sram_reprogram_घड़ी(dpllctl, ckctl);
पूर्ण

पूर्णांक __init omap_sram_init(व्योम)
अणु
	omap_detect_and_map_sram();
	_omap_sram_reprogram_घड़ी =
			omap_sram_push(omap1_sram_reprogram_घड़ी,
					omap1_sram_reprogram_घड़ी_sz);

	वापस 0;
पूर्ण
