<शैली गुरु>
/*
 * arch/arm/mach-spear13xx/spear13xx.c
 *
 * SPEAr13XX machines common source file
 *
 * Copyright (C) 2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#घोषणा pr_fmt(fmt) "SPEAr13xx: " fmt

#समावेश <linux/amba/pl022.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk/spear.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <mach/spear.h>
#समावेश "generic.h"

व्योम __init spear13xx_l2x0_init(व्योम)
अणु
	/*
	 * 512KB (64KB/way), 8-way associativity, parity supported
	 *
	 * FIXME: 9th bit, of Auxillary Controller रेजिस्टर must be set
	 * क्रम some spear13xx devices क्रम stable L2 operation.
	 *
	 * Enable Early BRESP, L2 prefetch क्रम Inकाष्ठाion and Data,
	 * ग_लिखो alloc and 'Full line of zero' options
	 *
	 */
	अगर (!IS_ENABLED(CONFIG_CACHE_L2X0))
		वापस;

	ग_लिखोl_relaxed(0x06, VA_L2CC_BASE + L310_PREFETCH_CTRL);

	/*
	 * Program following latencies in order to make
	 * SPEAr1340 work at 600 MHz
	 */
	ग_लिखोl_relaxed(0x221, VA_L2CC_BASE + L310_TAG_LATENCY_CTRL);
	ग_लिखोl_relaxed(0x441, VA_L2CC_BASE + L310_DATA_LATENCY_CTRL);
	l2x0_init(VA_L2CC_BASE, 0x30a00001, 0xfe0fffff);
पूर्ण

/*
 * Following will create 16MB अटल भव/physical mappings
 * PHYSICAL		VIRTUAL
 * 0xB3000000		0xF9000000
 * 0xE0000000		0xFD000000
 * 0xEC000000		0xFC000000
 * 0xED000000		0xFB000000
 */
अटल काष्ठा map_desc spear13xx_io_desc[] __initdata = अणु
	अणु
		.भव	= (अचिन्हित दीर्घ)VA_PERIP_GRP2_BASE,
		.pfn		= __phys_to_pfn(PERIP_GRP2_BASE),
		.length		= SZ_16M,
		.type		= MT_DEVICE
	पूर्ण, अणु
		.भव	= (अचिन्हित दीर्घ)VA_PERIP_GRP1_BASE,
		.pfn		= __phys_to_pfn(PERIP_GRP1_BASE),
		.length		= SZ_16M,
		.type		= MT_DEVICE
	पूर्ण, अणु
		.भव	= (अचिन्हित दीर्घ)VA_A9SM_AND_MPMC_BASE,
		.pfn		= __phys_to_pfn(A9SM_AND_MPMC_BASE),
		.length		= SZ_16M,
		.type		= MT_DEVICE
	पूर्ण, अणु
		.भव	= (अचिन्हित दीर्घ)VA_L2CC_BASE,
		.pfn		= __phys_to_pfn(L2CC_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;

/* This will create अटल memory mapping क्रम selected devices */
व्योम __init spear13xx_map_io(व्योम)
अणु
	iotable_init(spear13xx_io_desc, ARRAY_SIZE(spear13xx_io_desc));
पूर्ण

अटल व्योम __init spear13xx_clk_init(व्योम)
अणु
	अगर (of_machine_is_compatible("st,spear1310"))
		spear1310_clk_init(VA_MISC_BASE, VA_SPEAR1310_RAS_BASE);
	अन्यथा अगर (of_machine_is_compatible("st,spear1340"))
		spear1340_clk_init(VA_MISC_BASE);
	अन्यथा
		pr_err("%s: Unknown machine\n", __func__);
पूर्ण

व्योम __init spear13xx_समयr_init(व्योम)
अणु
	अक्षर pclk_name[] = "osc_24m_clk";
	काष्ठा clk *gpt_clk, *pclk;

	spear13xx_clk_init();

	/* get the प्रणाली समयr घड़ी */
	gpt_clk = clk_get_sys("gpt0", शून्य);
	अगर (IS_ERR(gpt_clk)) अणु
		pr_err("%s:couldn't get clk for gpt\n", __func__);
		BUG();
	पूर्ण

	/* get the suitable parent घड़ी क्रम समयr*/
	pclk = clk_get(शून्य, pclk_name);
	अगर (IS_ERR(pclk)) अणु
		pr_err("%s:couldn't get %s as parent for gpt\n", __func__,
				pclk_name);
		BUG();
	पूर्ण

	clk_set_parent(gpt_clk, pclk);
	clk_put(gpt_clk);
	clk_put(pclk);

	spear_setup_of_समयr();
	समयr_probe();
पूर्ण
