<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/arch/arm/mach-omap2/devices.c
 *
 * OMAP2 platक्रमm device setup/initialization
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/machine.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/map.h>

#समावेश <linux/omap-dma.h>

#समावेश "iomap.h"
#समावेश "omap_hwmod.h"
#समावेश "omap_device.h"

#समावेश "soc.h"
#समावेश "common.h"
#समावेश "control.h"
#समावेश "display.h"

#घोषणा L3_MODULES_MAX_LEN 12
#घोषणा L3_MODULES 3

/*-------------------------------------------------------------------------*/

#अगर IS_ENABLED(CONFIG_VIDEO_OMAP2_VOUT)
#अगर IS_ENABLED(CONFIG_FB_OMAP2)
अटल काष्ठा resource omap_vout_resource[3 - CONFIG_FB_OMAP2_NUM_FBS] = अणु
पूर्ण;
#अन्यथा
अटल काष्ठा resource omap_vout_resource[2] = अणु
पूर्ण;
#पूर्ण_अगर

अटल u64 omap_vout_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device omap_vout_device = अणु
	.name		= "omap_vout",
	.num_resources	= ARRAY_SIZE(omap_vout_resource),
	.resource 	= &omap_vout_resource[0],
	.id		= -1,
	.dev		= अणु
		.dma_mask		= &omap_vout_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

पूर्णांक __init omap_init_vout(व्योम)
अणु
	वापस platक्रमm_device_रेजिस्टर(&omap_vout_device);
पूर्ण
#अन्यथा
पूर्णांक __init omap_init_vout(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर
