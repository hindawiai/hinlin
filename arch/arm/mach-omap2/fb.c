<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Framebuffer device registration क्रम TI OMAP platक्रमms
 *
 * Copyright (C) 2006 Nokia Corporation
 * Author: Imre Deak <imre.deak@nokia.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/memblock.h>
#समावेश <linux/पन.स>
#समावेश <linux/omapfb.h>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/mach/map.h>

#समावेश "soc.h"
#समावेश "display.h"

#अगर_घोषित CONFIG_OMAP2_VRFB

/*
 * The first memory resource is the रेजिस्टर region क्रम VRFB,
 * the rest are VRFB भव memory areas क्रम each VRFB context.
 */

अटल स्थिर काष्ठा resource omap2_vrfb_resources[] = अणु
	DEFINE_RES_MEM_NAMED(0x68008000u, 0x40, "vrfb-regs"),
	DEFINE_RES_MEM_NAMED(0x70000000u, 0x4000000, "vrfb-area-0"),
	DEFINE_RES_MEM_NAMED(0x74000000u, 0x4000000, "vrfb-area-1"),
	DEFINE_RES_MEM_NAMED(0x78000000u, 0x4000000, "vrfb-area-2"),
	DEFINE_RES_MEM_NAMED(0x7c000000u, 0x4000000, "vrfb-area-3"),
पूर्ण;

अटल स्थिर काष्ठा resource omap3_vrfb_resources[] = अणु
	DEFINE_RES_MEM_NAMED(0x6C000180u, 0xc0, "vrfb-regs"),
	DEFINE_RES_MEM_NAMED(0x70000000u, 0x4000000, "vrfb-area-0"),
	DEFINE_RES_MEM_NAMED(0x74000000u, 0x4000000, "vrfb-area-1"),
	DEFINE_RES_MEM_NAMED(0x78000000u, 0x4000000, "vrfb-area-2"),
	DEFINE_RES_MEM_NAMED(0x7c000000u, 0x4000000, "vrfb-area-3"),
	DEFINE_RES_MEM_NAMED(0xe0000000u, 0x4000000, "vrfb-area-4"),
	DEFINE_RES_MEM_NAMED(0xe4000000u, 0x4000000, "vrfb-area-5"),
	DEFINE_RES_MEM_NAMED(0xe8000000u, 0x4000000, "vrfb-area-6"),
	DEFINE_RES_MEM_NAMED(0xec000000u, 0x4000000, "vrfb-area-7"),
	DEFINE_RES_MEM_NAMED(0xf0000000u, 0x4000000, "vrfb-area-8"),
	DEFINE_RES_MEM_NAMED(0xf4000000u, 0x4000000, "vrfb-area-9"),
	DEFINE_RES_MEM_NAMED(0xf8000000u, 0x4000000, "vrfb-area-10"),
	DEFINE_RES_MEM_NAMED(0xfc000000u, 0x4000000, "vrfb-area-11"),
पूर्ण;

पूर्णांक __init omap_init_vrfb(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	स्थिर काष्ठा resource *res;
	अचिन्हित पूर्णांक num_res;

	अगर (cpu_is_omap24xx()) अणु
		res = omap2_vrfb_resources;
		num_res = ARRAY_SIZE(omap2_vrfb_resources);
	पूर्ण अन्यथा अगर (cpu_is_omap34xx()) अणु
		res = omap3_vrfb_resources;
		num_res = ARRAY_SIZE(omap3_vrfb_resources);
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	pdev = platक्रमm_device_रेजिस्टर_resndata(शून्य, "omapvrfb", -1,
			res, num_res, शून्य, 0);

	वापस PTR_ERR_OR_ZERO(pdev);
पूर्ण
#अन्यथा
पूर्णांक __init omap_init_vrfb(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_FB_OMAP2)

अटल u64 omap_fb_dma_mask = ~(u32)0;
अटल काष्ठा omapfb_platक्रमm_data omapfb_config;

अटल काष्ठा platक्रमm_device omap_fb_device = अणु
	.name		= "omapfb",
	.id		= -1,
	.dev = अणु
		.dma_mask		= &omap_fb_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &omapfb_config,
	पूर्ण,
	.num_resources = 0,
पूर्ण;

पूर्णांक __init omap_init_fb(व्योम)
अणु
	वापस platक्रमm_device_रेजिस्टर(&omap_fb_device);
पूर्ण
#अन्यथा
पूर्णांक __init omap_init_fb(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर
