<शैली गुरु>
/*
 * arch/arm/mach-spear3xx/spear310.c
 *
 * SPEAr310 machine source file
 *
 * Copyright (C) 2009-2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#घोषणा pr_fmt(fmt) "SPEAr310: " fmt

#समावेश <linux/amba/pl08x.h>
#समावेश <linux/amba/serial.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश "generic.h"
#समावेश <mach/spear.h>

#घोषणा SPEAR310_UART1_BASE		UL(0xB2000000)
#घोषणा SPEAR310_UART2_BASE		UL(0xB2080000)
#घोषणा SPEAR310_UART3_BASE		UL(0xB2100000)
#घोषणा SPEAR310_UART4_BASE		UL(0xB2180000)
#घोषणा SPEAR310_UART5_BASE		UL(0xB2200000)

/* DMAC platक्रमm data's slave info */
काष्ठा pl08x_channel_data spear310_dma_info[] = अणु
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
		.bus_id = "uart1_rx",
		.min_संकेत = 0,
		.max_संकेत = 0,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "uart1_tx",
		.min_संकेत = 1,
		.max_संकेत = 1,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "uart2_rx",
		.min_संकेत = 2,
		.max_संकेत = 2,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "uart2_tx",
		.min_संकेत = 3,
		.max_संकेत = 3,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "uart3_rx",
		.min_संकेत = 4,
		.max_संकेत = 4,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "uart3_tx",
		.min_संकेत = 5,
		.max_संकेत = 5,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "uart4_rx",
		.min_संकेत = 6,
		.max_संकेत = 6,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "uart4_tx",
		.min_संकेत = 7,
		.max_संकेत = 7,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "uart5_rx",
		.min_संकेत = 8,
		.max_संकेत = 8,
		.muxval = 1,
		.periph_buses = PL08X_AHB1,
	पूर्ण, अणु
		.bus_id = "uart5_tx",
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
	पूर्ण,
पूर्ण;

/* uart devices plat data */
अटल काष्ठा amba_pl011_data spear310_uart_data[] = अणु
	अणु
		.dma_filter = pl08x_filter_id,
		.dma_tx_param = "uart1_tx",
		.dma_rx_param = "uart1_rx",
	पूर्ण, अणु
		.dma_filter = pl08x_filter_id,
		.dma_tx_param = "uart2_tx",
		.dma_rx_param = "uart2_rx",
	पूर्ण, अणु
		.dma_filter = pl08x_filter_id,
		.dma_tx_param = "uart3_tx",
		.dma_rx_param = "uart3_rx",
	पूर्ण, अणु
		.dma_filter = pl08x_filter_id,
		.dma_tx_param = "uart4_tx",
		.dma_rx_param = "uart4_rx",
	पूर्ण, अणु
		.dma_filter = pl08x_filter_id,
		.dma_tx_param = "uart5_tx",
		.dma_rx_param = "uart5_rx",
	पूर्ण,
पूर्ण;

/* Add SPEAr310 auxdata to pass platक्रमm data */
अटल काष्ठा of_dev_auxdata spear310_auxdata_lookup[] __initdata = अणु
	OF_DEV_AUXDATA("arm,pl022", SPEAR3XX_ICM1_SSP_BASE, शून्य,
			&pl022_plat_data),
	OF_DEV_AUXDATA("arm,pl080", SPEAR_ICM3_DMA_BASE, शून्य,
			&pl080_plat_data),
	OF_DEV_AUXDATA("arm,pl011", SPEAR310_UART1_BASE, शून्य,
			&spear310_uart_data[0]),
	OF_DEV_AUXDATA("arm,pl011", SPEAR310_UART2_BASE, शून्य,
			&spear310_uart_data[1]),
	OF_DEV_AUXDATA("arm,pl011", SPEAR310_UART3_BASE, शून्य,
			&spear310_uart_data[2]),
	OF_DEV_AUXDATA("arm,pl011", SPEAR310_UART4_BASE, शून्य,
			&spear310_uart_data[3]),
	OF_DEV_AUXDATA("arm,pl011", SPEAR310_UART5_BASE, शून्य,
			&spear310_uart_data[4]),
	अणुपूर्ण
पूर्ण;

अटल व्योम __init spear310_dt_init(व्योम)
अणु
	pl080_plat_data.slave_channels = spear310_dma_info;
	pl080_plat_data.num_slave_channels = ARRAY_SIZE(spear310_dma_info);

	of_platक्रमm_शेष_populate(शून्य, spear310_auxdata_lookup, शून्य);
पूर्ण

अटल स्थिर अक्षर * स्थिर spear310_dt_board_compat[] = अणु
	"st,spear310",
	"st,spear310-evb",
	शून्य,
पूर्ण;

अटल व्योम __init spear310_map_io(व्योम)
अणु
	spear3xx_map_io();
पूर्ण

DT_MACHINE_START(SPEAR310_DT, "ST SPEAr310 SoC with Flattened Device Tree")
	.map_io		=	spear310_map_io,
	.init_समय	=	spear3xx_समयr_init,
	.init_machine	=	spear310_dt_init,
	.restart	=	spear_restart,
	.dt_compat	=	spear310_dt_board_compat,
MACHINE_END
