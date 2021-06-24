<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/generic.c
 *
 *  Author:	Nicolas Pitre
 *  Created:	Jun 15, 2001
 *  Copyright:	MontaVista Software Inc.
 *
 * Code common to all PXA machines.
 *
 * Since this file should be linked beक्रमe any other machine specअगरic file,
 * the __initcall() here will be executed first.  This serves as शेष
 * initialization stuff क्रम PXA machines which can be overridden later अगर
 * need be.
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach-types.h>

#समावेश <mach/irqs.h>
#समावेश <mach/reset.h>
#समावेश <mach/smemc.h>
#समावेश <mach/pxa3xx-regs.h>

#समावेश "generic.h"
#समावेश <घड़ीsource/pxa.h>

व्योम clear_reset_status(अचिन्हित पूर्णांक mask)
अणु
	अगर (cpu_is_pxa2xx())
		pxa2xx_clear_reset_status(mask);
	अन्यथा अणु
		/* RESET_STATUS_* has a 1:1 mapping with ARSR */
		ARSR = mask;
	पूर्ण
पूर्ण

/*
 * For non device-tree builds, keep legacy समयr init
 */
व्योम __init pxa_समयr_init(व्योम)
अणु
	अगर (cpu_is_pxa25x())
		pxa25x_घड़ीs_init();
	अगर (cpu_is_pxa27x())
		pxa27x_घड़ीs_init();
	अगर (cpu_is_pxa3xx())
		pxa3xx_घड़ीs_init();
	pxa_समयr_nodt_init(IRQ_OST0, io_p2v(0x40a00000));
पूर्ण

/*
 * Get the घड़ी frequency as reflected by CCCR and the turbo flag.
 * We assume these values have been applied via a fcs.
 * If info is not 0 we also display the current settings.
 */
अचिन्हित पूर्णांक get_clk_frequency_khz(पूर्णांक info)
अणु
	अगर (cpu_is_pxa25x())
		वापस pxa25x_get_clk_frequency_khz(info);
	अन्यथा अगर (cpu_is_pxa27x())
		वापस pxa27x_get_clk_frequency_khz(info);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(get_clk_frequency_khz);

/*
 * Intel PXA2xx पूर्णांकernal रेजिस्टर mapping.
 *
 * Note: भव 0xfffe0000-0xffffffff is reserved क्रम the vector table
 *       and cache flush area.
 */
अटल काष्ठा map_desc common_io_desc[] __initdata = अणु
  	अणु	/* Devs */
		.भव	= (अचिन्हित दीर्घ)PERIPH_VIRT,
		.pfn		= __phys_to_pfn(PERIPH_PHYS),
		.length		= PERIPH_SIZE,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;

व्योम __init pxa_map_io(व्योम)
अणु
	debug_ll_io_init();
	iotable_init(ARRAY_AND_SIZE(common_io_desc));
पूर्ण
