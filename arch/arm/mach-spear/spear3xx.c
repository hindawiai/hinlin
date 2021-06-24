<शैली गुरु>
/*
 * arch/arm/mach-spear3xx/spear3xx.c
 *
 * SPEAr3XX machines common source file
 *
 * Copyright (C) 2009-2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#घोषणा pr_fmt(fmt) "SPEAr3xx: " fmt

#समावेश <linux/amba/pl022.h>
#समावेश <linux/amba/pl080.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/mach/map.h>
#समावेश "pl080.h"
#समावेश "generic.h"
#समावेश <mach/spear.h>
#समावेश <mach/misc_regs.h>

/* ssp device registration */
काष्ठा pl022_ssp_controller pl022_plat_data = अणु
	.bus_id = 0,
	.enable_dma = 1,
	.dma_filter = pl08x_filter_id,
	.dma_tx_param = "ssp0_tx",
	.dma_rx_param = "ssp0_rx",
पूर्ण;

/* dmac device registration */
काष्ठा pl08x_platक्रमm_data pl080_plat_data = अणु
	.स_नकल_burst_size = PL08X_BURST_SZ_16,
	.स_नकल_bus_width = PL08X_BUS_WIDTH_32_BITS,
	.स_नकल_prot_buff = true,
	.स_नकल_prot_cache = true,
	.lli_buses = PL08X_AHB1,
	.mem_buses = PL08X_AHB1,
	.get_xfer_संकेत = pl080_get_संकेत,
	.put_xfer_संकेत = pl080_put_संकेत,
पूर्ण;

/*
 * Following will create 16MB अटल भव/physical mappings
 * PHYSICAL		VIRTUAL
 * 0xD0000000		0xFD000000
 * 0xFC000000		0xFC000000
 */
काष्ठा map_desc spear3xx_io_desc[] __initdata = अणु
	अणु
		.भव	= (अचिन्हित दीर्घ)VA_SPEAR_ICM1_2_BASE,
		.pfn		= __phys_to_pfn(SPEAR_ICM1_2_BASE),
		.length		= SZ_16M,
		.type		= MT_DEVICE
	पूर्ण, अणु
		.भव	= (अचिन्हित दीर्घ)VA_SPEAR_ICM3_SMI_CTRL_BASE,
		.pfn		= __phys_to_pfn(SPEAR_ICM3_SMI_CTRL_BASE),
		.length		= SZ_16M,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;

/* This will create अटल memory mapping क्रम selected devices */
व्योम __init spear3xx_map_io(व्योम)
अणु
	iotable_init(spear3xx_io_desc, ARRAY_SIZE(spear3xx_io_desc));
पूर्ण

व्योम __init spear3xx_समयr_init(व्योम)
अणु
	अक्षर pclk_name[] = "pll3_clk";
	काष्ठा clk *gpt_clk, *pclk;

	spear3xx_clk_init(MISC_BASE, VA_SPEAR320_SOC_CONFIG_BASE);

	/* get the प्रणाली समयr घड़ी */
	gpt_clk = clk_get_sys("gpt0", शून्य);
	अगर (IS_ERR(gpt_clk)) अणु
		pr_err("%s:couldn't get clk for gpt\n", __func__);
		BUG();
	पूर्ण

	/* get the suitable parent घड़ी क्रम समयr*/
	pclk = clk_get(शून्य, pclk_name);
	अगर (IS_ERR(pclk)) अणु
		pr_err("%s:couldn't get %s as parent for gpt\n",
				__func__, pclk_name);
		BUG();
	पूर्ण

	clk_set_parent(gpt_clk, pclk);
	clk_put(gpt_clk);
	clk_put(pclk);

	spear_setup_of_समयr();
पूर्ण
