<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/mach-tegra/io.c
 *
 * Copyright (C) 2010 Google, Inc.
 *
 * Author:
 *	Colin Cross <ccross@google.com>
 *	Erik Gilling <konkers@google.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/page.h>

#समावेश "board.h"
#समावेश "iomap.h"

अटल काष्ठा map_desc tegra_io_desc[] __initdata = अणु
	अणु
		.भव = (अचिन्हित दीर्घ)IO_PPSB_VIRT,
		.pfn = __phys_to_pfn(IO_PPSB_PHYS),
		.length = IO_PPSB_SIZE,
		.type = MT_DEVICE,
	पूर्ण,
	अणु
		.भव = (अचिन्हित दीर्घ)IO_APB_VIRT,
		.pfn = __phys_to_pfn(IO_APB_PHYS),
		.length = IO_APB_SIZE,
		.type = MT_DEVICE,
	पूर्ण,
	अणु
		.भव = (अचिन्हित दीर्घ)IO_CPU_VIRT,
		.pfn = __phys_to_pfn(IO_CPU_PHYS),
		.length = IO_CPU_SIZE,
		.type = MT_DEVICE,
	पूर्ण,
	अणु
		.भव = (अचिन्हित दीर्घ)IO_IRAM_VIRT,
		.pfn = __phys_to_pfn(IO_IRAM_PHYS),
		.length = IO_IRAM_SIZE,
		.type = MT_DEVICE,
	पूर्ण,
पूर्ण;

व्योम __init tegra_map_common_io(व्योम)
अणु
	debug_ll_io_init();
	iotable_init(tegra_io_desc, ARRAY_SIZE(tegra_io_desc));
पूर्ण
