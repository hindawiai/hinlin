<शैली गुरु>
/*
 * arch/arm/mach-spear3xx/spear320.c
 *
 * SPEAr320 machine source file
 *
 * Copyright (C) 2009-2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#घोषणा pr_fmt(fmt) "SPEAr320: " fmt

#समावेश <linux/amba/pl022.h>
#समावेश <linux/amba/pl08x.h>
#समावेश <linux/amba/serial.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश "generic.h"
#समावेश <mach/spear.h>

#घोषणा SPEAR320_UART1_BASE		UL(0xA3000000)
#घोषणा SPEAR320_UART2_BASE		UL(0xA4000000)
#घोषणा SPEAR320_SSP0_BASE		UL(0xA5000000)
#घोषणा SPEAR320_SSP1_BASE		UL(0xA6000000)

/* DMAC platक्रमm data's slave info */
काष्ठा pl08x_channel_data spear320_dma_info[] = अणु
	अणु
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
		.bus_id = "i2c0_rx",
		.min_संकेत = 10,
		.max_संकेत = 10,
		.muxval = 0,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "i2c0_tx",
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
		.periph_buses = PL08X_AHB1,
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
		.bus_id = "ssp1_rx",
		.min_संकेत = 0,
		.max_संकेत = 0,
		.muxval = 1,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ssp1_tx",
		.min_संकेत = 1,
		.max_संकेत = 1,
		.muxval = 1,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ssp2_rx",
		.min_संकेत = 2,
		.max_संकेत = 2,
		.muxval = 1,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ssp2_tx",
		.min_संकेत = 3,
		.max_संकेत = 3,
		.muxval = 1,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "uart1_rx",
		.min_संकेत = 4,
		.max_संकेत = 4,
		.muxval = 1,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "uart1_tx",
		.min_संकेत = 5,
		.max_संकेत = 5,
		.muxval = 1,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "uart2_rx",
		.min_संकेत = 6,
		.max_संकेत = 6,
		.muxval = 1,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "uart2_tx",
		.min_संकेत = 7,
		.max_संकेत = 7,
		.muxval = 1,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "i2c1_rx",
		.min_संकेत = 8,
		.max_संकेत = 8,
		.muxval = 1,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "i2c1_tx",
		.min_संकेत = 9,
		.max_संकेत = 9,
		.muxval = 1,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "i2c2_rx",
		.min_संकेत = 10,
		.max_संकेत = 10,
		.muxval = 1,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "i2c2_tx",
		.min_संकेत = 11,
		.max_संकेत = 11,
		.muxval = 1,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "i2s_rx",
		.min_संकेत = 12,
		.max_संकेत = 12,
		.muxval = 1,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "i2s_tx",
		.min_संकेत = 13,
		.max_संकेत = 13,
		.muxval = 1,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "rs485_rx",
		.min_संकेत = 14,
		.max_संकेत = 14,
		.muxval = 1,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "rs485_tx",
		.min_संकेत = 15,
		.max_संकेत = 15,
		.muxval = 1,
		.periph_buses = PL08X_AHB2,
	पूर्ण,
पूर्ण;

अटल काष्ठा pl022_ssp_controller spear320_ssp_data[] = अणु
	अणु
		.bus_id = 1,
		.enable_dma = 1,
		.dma_filter = pl08x_filter_id,
		.dma_tx_param = "ssp1_tx",
		.dma_rx_param = "ssp1_rx",
	पूर्ण, अणु
		.bus_id = 2,
		.enable_dma = 1,
		.dma_filter = pl08x_filter_id,
		.dma_tx_param = "ssp2_tx",
		.dma_rx_param = "ssp2_rx",
	पूर्ण
पूर्ण;

अटल काष्ठा amba_pl011_data spear320_uart_data[] = अणु
	अणु
		.dma_filter = pl08x_filter_id,
		.dma_tx_param = "uart1_tx",
		.dma_rx_param = "uart1_rx",
	पूर्ण, अणु
		.dma_filter = pl08x_filter_id,
		.dma_tx_param = "uart2_tx",
		.dma_rx_param = "uart2_rx",
	पूर्ण,
पूर्ण;

/* Add SPEAr310 auxdata to pass platक्रमm data */
अटल काष्ठा of_dev_auxdata spear320_auxdata_lookup[] __initdata = अणु
	OF_DEV_AUXDATA("arm,pl022", SPEAR3XX_ICM1_SSP_BASE, शून्य,
			&pl022_plat_data),
	OF_DEV_AUXDATA("arm,pl080", SPEAR_ICM3_DMA_BASE, शून्य,
			&pl080_plat_data),
	OF_DEV_AUXDATA("arm,pl022", SPEAR320_SSP0_BASE, शून्य,
			&spear320_ssp_data[0]),
	OF_DEV_AUXDATA("arm,pl022", SPEAR320_SSP1_BASE, शून्य,
			&spear320_ssp_data[1]),
	OF_DEV_AUXDATA("arm,pl011", SPEAR320_UART1_BASE, शून्य,
			&spear320_uart_data[0]),
	OF_DEV_AUXDATA("arm,pl011", SPEAR320_UART2_BASE, शून्य,
			&spear320_uart_data[1]),
	अणुपूर्ण
पूर्ण;

अटल व्योम __init spear320_dt_init(व्योम)
अणु
	pl080_plat_data.slave_channels = spear320_dma_info;
	pl080_plat_data.num_slave_channels = ARRAY_SIZE(spear320_dma_info);

	of_platक्रमm_शेष_populate(शून्य, spear320_auxdata_lookup, शून्य);
पूर्ण

अटल स्थिर अक्षर * स्थिर spear320_dt_board_compat[] = अणु
	"st,spear320",
	"st,spear320-evb",
	"st,spear320-hmi",
	शून्य,
पूर्ण;

काष्ठा map_desc spear320_io_desc[] __initdata = अणु
	अणु
		.भव	= (अचिन्हित दीर्घ)VA_SPEAR320_SOC_CONFIG_BASE,
		.pfn		= __phys_to_pfn(SPEAR320_SOC_CONFIG_BASE),
		.length		= SZ_16M,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;

अटल व्योम __init spear320_map_io(व्योम)
अणु
	iotable_init(spear320_io_desc, ARRAY_SIZE(spear320_io_desc));
	spear3xx_map_io();
पूर्ण

DT_MACHINE_START(SPEAR320_DT, "ST SPEAr320 SoC with Flattened Device Tree")
	.map_io		=	spear320_map_io,
	.init_समय	=	spear3xx_समयr_init,
	.init_machine	=	spear320_dt_init,
	.restart	=	spear_restart,
	.dt_compat	=	spear320_dt_board_compat,
MACHINE_END
