<शैली गुरु>
/*
 * arch/arm/mach-spear6xx/spear6xx.c
 *
 * SPEAr6XX machines common source file
 *
 * Copyright (C) 2009 ST Microelectronics
 * Rajeev Kumar<rajeev-dlh.kumar@st.com>
 *
 * Copyright 2012 Stefan Roese <sr@denx.de>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/amba/pl08x.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/amba/pl080.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <यंत्र/mach/map.h>
#समावेश "pl080.h"
#समावेश "generic.h"
#समावेश <mach/spear.h>
#समावेश <mach/misc_regs.h>

/* dmac device registration */
अटल काष्ठा pl08x_channel_data spear600_dma_info[] = अणु
	अणु
		.bus_id = "ssp1_rx",
		.min_संकेत = 0,
		.max_संकेत = 0,
		.muxval = 0,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "ssp1_tx",
		.min_संकेत = 1,
		.max_संकेत = 1,
		.muxval = 0,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "uart0_rx",
		.min_संकेत = 2,
		.max_संकेत = 2,
		.muxval = 0,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "uart0_tx",
		.min_संकेत = 3,
		.max_संकेत = 3,
		.muxval = 0,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "uart1_rx",
		.min_संकेत = 4,
		.max_संकेत = 4,
		.muxval = 0,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "uart1_tx",
		.min_संकेत = 5,
		.max_संकेत = 5,
		.muxval = 0,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "ssp2_rx",
		.min_संकेत = 6,
		.max_संकेत = 6,
		.muxval = 0,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ssp2_tx",
		.min_संकेत = 7,
		.max_संकेत = 7,
		.muxval = 0,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ssp0_rx",
		.min_संकेत = 8,
		.max_संकेत = 8,
		.muxval = 0,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "ssp0_tx",
		.min_संकेत = 9,
		.max_संकेत = 9,
		.muxval = 0,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "i2c_rx",
		.min_संकेत = 10,
		.max_संकेत = 10,
		.muxval = 0,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "i2c_tx",
		.min_संकेत = 11,
		.max_संकेत = 11,
		.muxval = 0,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "irda",
		.min_संकेत = 12,
		.max_संकेत = 12,
		.muxval = 0,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "adc",
		.min_संकेत = 13,
		.max_संकेत = 13,
		.muxval = 0,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "to_jpeg",
		.min_संकेत = 14,
		.max_संकेत = 14,
		.muxval = 0,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "from_jpeg",
		.min_संकेत = 15,
		.max_संकेत = 15,
		.muxval = 0,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "ras0_rx",
		.min_संकेत = 0,
		.max_संकेत = 0,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "ras0_tx",
		.min_संकेत = 1,
		.max_संकेत = 1,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "ras1_rx",
		.min_संकेत = 2,
		.max_संकेत = 2,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "ras1_tx",
		.min_संकेत = 3,
		.max_संकेत = 3,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "ras2_rx",
		.min_संकेत = 4,
		.max_संकेत = 4,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "ras2_tx",
		.min_संकेत = 5,
		.max_संकेत = 5,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "ras3_rx",
		.min_संकेत = 6,
		.max_संकेत = 6,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "ras3_tx",
		.min_संकेत = 7,
		.max_संकेत = 7,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "ras4_rx",
		.min_संकेत = 8,
		.max_संकेत = 8,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "ras4_tx",
		.min_संकेत = 9,
		.max_संकेत = 9,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "ras5_rx",
		.min_संकेत = 10,
		.max_संकेत = 10,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "ras5_tx",
		.min_संकेत = 11,
		.max_संकेत = 11,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "ras6_rx",
		.min_संकेत = 12,
		.max_संकेत = 12,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "ras6_tx",
		.min_संकेत = 13,
		.max_संकेत = 13,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "ras7_rx",
		.min_संकेत = 14,
		.max_संकेत = 14,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "ras7_tx",
		.min_संकेत = 15,
		.max_संकेत = 15,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "ext0_rx",
		.min_संकेत = 0,
		.max_संकेत = 0,
		.muxval = 2,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ext0_tx",
		.min_संकेत = 1,
		.max_संकेत = 1,
		.muxval = 2,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ext1_rx",
		.min_संकेत = 2,
		.max_संकेत = 2,
		.muxval = 2,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ext1_tx",
		.min_संकेत = 3,
		.max_संकेत = 3,
		.muxval = 2,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ext2_rx",
		.min_संकेत = 4,
		.max_संकेत = 4,
		.muxval = 2,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ext2_tx",
		.min_संकेत = 5,
		.max_संकेत = 5,
		.muxval = 2,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ext3_rx",
		.min_संकेत = 6,
		.max_संकेत = 6,
		.muxval = 2,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ext3_tx",
		.min_संकेत = 7,
		.max_संकेत = 7,
		.muxval = 2,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ext4_rx",
		.min_संकेत = 8,
		.max_संकेत = 8,
		.muxval = 2,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ext4_tx",
		.min_संकेत = 9,
		.max_संकेत = 9,
		.muxval = 2,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ext5_rx",
		.min_संकेत = 10,
		.max_संकेत = 10,
		.muxval = 2,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ext5_tx",
		.min_संकेत = 11,
		.max_संकेत = 11,
		.muxval = 2,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ext6_rx",
		.min_संकेत = 12,
		.max_संकेत = 12,
		.muxval = 2,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ext6_tx",
		.min_संकेत = 13,
		.max_संकेत = 13,
		.muxval = 2,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ext7_rx",
		.min_संकेत = 14,
		.max_संकेत = 14,
		.muxval = 2,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ext7_tx",
		.min_संकेत = 15,
		.max_संकेत = 15,
		.muxval = 2,
		.periph_buses = PL08X_AHB2,
	पूर्ण,
पूर्ण;

अटल काष्ठा pl08x_platक्रमm_data spear6xx_pl080_plat_data = अणु
	.स_नकल_burst_size = PL08X_BURST_SZ_16,
	.स_नकल_bus_width = PL08X_BUS_WIDTH_32_BITS,
	.स_नकल_prot_buff = true,
	.स_नकल_prot_cache = true,
	.lli_buses = PL08X_AHB1,
	.mem_buses = PL08X_AHB1,
	.get_xfer_संकेत = pl080_get_संकेत,
	.put_xfer_संकेत = pl080_put_संकेत,
	.slave_channels = spear600_dma_info,
	.num_slave_channels = ARRAY_SIZE(spear600_dma_info),
पूर्ण;

/*
 * Following will create 16MB अटल भव/physical mappings
 * PHYSICAL		VIRTUAL
 * 0xF0000000		0xF0000000
 * 0xF1000000		0xF1000000
 * 0xD0000000		0xFD000000
 * 0xFC000000		0xFC000000
 */
काष्ठा map_desc spear6xx_io_desc[] __initdata = अणु
	अणु
		.भव	= (अचिन्हित दीर्घ)VA_SPEAR6XX_ML_CPU_BASE,
		.pfn		= __phys_to_pfn(SPEAR_ICM3_ML1_2_BASE),
		.length		= 2 * SZ_16M,
		.type		= MT_DEVICE
	पूर्ण,	अणु
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
व्योम __init spear6xx_map_io(व्योम)
अणु
	iotable_init(spear6xx_io_desc, ARRAY_SIZE(spear6xx_io_desc));
पूर्ण

व्योम __init spear6xx_समयr_init(व्योम)
अणु
	अक्षर pclk_name[] = "pll3_clk";
	काष्ठा clk *gpt_clk, *pclk;

	spear6xx_clk_init(MISC_BASE);

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

/* Add auxdata to pass platक्रमm data */
काष्ठा of_dev_auxdata spear6xx_auxdata_lookup[] __initdata = अणु
	OF_DEV_AUXDATA("arm,pl080", SPEAR_ICM3_DMA_BASE, शून्य,
			&spear6xx_pl080_plat_data),
	अणुपूर्ण
पूर्ण;

अटल व्योम __init spear600_dt_init(व्योम)
अणु
	of_platक्रमm_शेष_populate(शून्य, spear6xx_auxdata_lookup, शून्य);
पूर्ण

अटल स्थिर अक्षर *spear600_dt_board_compat[] = अणु
	"st,spear600",
	शून्य
पूर्ण;

DT_MACHINE_START(SPEAR600_DT, "ST SPEAr600 (Flattened Device Tree)")
	.map_io		=	spear6xx_map_io,
	.init_समय	=	spear6xx_समयr_init,
	.init_machine	=	spear600_dt_init,
	.restart	=	spear_restart,
	.dt_compat	=	spear600_dt_board_compat,
MACHINE_END
