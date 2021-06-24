<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Samsung's S3C64XX generic DMA support using amba-pl08x driver.
//
// Copyright (c) 2013 Tomasz Figa <tomasz.figa@gmail.com>

#समावेश <linux/kernel.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/amba/pl080.h>
#समावेश <linux/amba/pl08x.h>
#समावेश <linux/of.h>

#समावेश "cpu.h"
#समावेश <mach/irqs.h>
#समावेश "map.h"

#समावेश "regs-sys-s3c64xx.h"

अटल पूर्णांक pl08x_get_xfer_संकेत(स्थिर काष्ठा pl08x_channel_data *cd)
अणु
	वापस cd->min_संकेत;
पूर्ण

अटल व्योम pl08x_put_xfer_संकेत(स्थिर काष्ठा pl08x_channel_data *cd, पूर्णांक ch)
अणु
पूर्ण

/*
 * DMA0
 */

अटल काष्ठा pl08x_channel_data s3c64xx_dma0_info[] = अणु
	अणु
		.bus_id = "uart0_tx",
		.min_संकेत = 0,
		.max_संकेत = 0,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "uart0_rx",
		.min_संकेत = 1,
		.max_संकेत = 1,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "uart1_tx",
		.min_संकेत = 2,
		.max_संकेत = 2,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "uart1_rx",
		.min_संकेत = 3,
		.max_संकेत = 3,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "uart2_tx",
		.min_संकेत = 4,
		.max_संकेत = 4,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "uart2_rx",
		.min_संकेत = 5,
		.max_संकेत = 5,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "uart3_tx",
		.min_संकेत = 6,
		.max_संकेत = 6,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "uart3_rx",
		.min_संकेत = 7,
		.max_संकेत = 7,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "pcm0_tx",
		.min_संकेत = 8,
		.max_संकेत = 8,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "pcm0_rx",
		.min_संकेत = 9,
		.max_संकेत = 9,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "i2s0_tx",
		.min_संकेत = 10,
		.max_संकेत = 10,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "i2s0_rx",
		.min_संकेत = 11,
		.max_संकेत = 11,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "spi0_tx",
		.min_संकेत = 12,
		.max_संकेत = 12,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "spi0_rx",
		.min_संकेत = 13,
		.max_संकेत = 13,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "i2s2_tx",
		.min_संकेत = 14,
		.max_संकेत = 14,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "i2s2_rx",
		.min_संकेत = 15,
		.max_संकेत = 15,
		.periph_buses = PL08X_AHB2,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dma_slave_map s3c64xx_dma0_slave_map[] = अणु
	अणु "s3c6400-uart.0", "tx", &s3c64xx_dma0_info[0] पूर्ण,
	अणु "s3c6400-uart.0", "rx", &s3c64xx_dma0_info[1] पूर्ण,
	अणु "s3c6400-uart.1", "tx", &s3c64xx_dma0_info[2] पूर्ण,
	अणु "s3c6400-uart.1", "rx", &s3c64xx_dma0_info[3] पूर्ण,
	अणु "s3c6400-uart.2", "tx", &s3c64xx_dma0_info[4] पूर्ण,
	अणु "s3c6400-uart.2", "rx", &s3c64xx_dma0_info[5] पूर्ण,
	अणु "s3c6400-uart.3", "tx", &s3c64xx_dma0_info[6] पूर्ण,
	अणु "s3c6400-uart.3", "rx", &s3c64xx_dma0_info[7] पूर्ण,
	अणु "samsung-pcm.0", "tx", &s3c64xx_dma0_info[8] पूर्ण,
	अणु "samsung-pcm.0", "rx", &s3c64xx_dma0_info[9] पूर्ण,
	अणु "samsung-i2s.0", "tx", &s3c64xx_dma0_info[10] पूर्ण,
	अणु "samsung-i2s.0", "rx", &s3c64xx_dma0_info[11] पूर्ण,
	अणु "s3c6410-spi.0", "tx", &s3c64xx_dma0_info[12] पूर्ण,
	अणु "s3c6410-spi.0", "rx", &s3c64xx_dma0_info[13] पूर्ण,
	अणु "samsung-i2s.2", "tx", &s3c64xx_dma0_info[14] पूर्ण,
	अणु "samsung-i2s.2", "rx", &s3c64xx_dma0_info[15] पूर्ण,
पूर्ण;

काष्ठा pl08x_platक्रमm_data s3c64xx_dma0_plat_data = अणु
	.स_नकल_burst_size = PL08X_BURST_SZ_4,
	.स_नकल_bus_width = PL08X_BUS_WIDTH_32_BITS,
	.स_नकल_prot_buff = true,
	.स_नकल_prot_cache = true,
	.lli_buses = PL08X_AHB1,
	.mem_buses = PL08X_AHB1,
	.get_xfer_संकेत = pl08x_get_xfer_संकेत,
	.put_xfer_संकेत = pl08x_put_xfer_संकेत,
	.slave_channels = s3c64xx_dma0_info,
	.num_slave_channels = ARRAY_SIZE(s3c64xx_dma0_info),
	.slave_map = s3c64xx_dma0_slave_map,
	.slave_map_len = ARRAY_SIZE(s3c64xx_dma0_slave_map),
पूर्ण;

अटल AMBA_AHB_DEVICE(s3c64xx_dma0, "dma-pl080s.0", 0,
			0x75000000, अणुIRQ_DMA0पूर्ण, &s3c64xx_dma0_plat_data);

/*
 * DMA1
 */

अटल काष्ठा pl08x_channel_data s3c64xx_dma1_info[] = अणु
	अणु
		.bus_id = "pcm1_tx",
		.min_संकेत = 0,
		.max_संकेत = 0,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "pcm1_rx",
		.min_संकेत = 1,
		.max_संकेत = 1,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "i2s1_tx",
		.min_संकेत = 2,
		.max_संकेत = 2,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "i2s1_rx",
		.min_संकेत = 3,
		.max_संकेत = 3,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "spi1_tx",
		.min_संकेत = 4,
		.max_संकेत = 4,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "spi1_rx",
		.min_संकेत = 5,
		.max_संकेत = 5,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ac97_out",
		.min_संकेत = 6,
		.max_संकेत = 6,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ac97_in",
		.min_संकेत = 7,
		.max_संकेत = 7,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "ac97_mic",
		.min_संकेत = 8,
		.max_संकेत = 8,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "pwm",
		.min_संकेत = 9,
		.max_संकेत = 9,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "irda",
		.min_संकेत = 10,
		.max_संकेत = 10,
		.periph_buses = PL08X_AHB2,
	पूर्ण, अणु
		.bus_id = "external",
		.min_संकेत = 11,
		.max_संकेत = 11,
		.periph_buses = PL08X_AHB2,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dma_slave_map s3c64xx_dma1_slave_map[] = अणु
	अणु "samsung-pcm.1", "tx", &s3c64xx_dma1_info[0] पूर्ण,
	अणु "samsung-pcm.1", "rx", &s3c64xx_dma1_info[1] पूर्ण,
	अणु "samsung-i2s.1", "tx", &s3c64xx_dma1_info[2] पूर्ण,
	अणु "samsung-i2s.1", "rx", &s3c64xx_dma1_info[3] पूर्ण,
	अणु "s3c6410-spi.1", "tx", &s3c64xx_dma1_info[4] पूर्ण,
	अणु "s3c6410-spi.1", "rx", &s3c64xx_dma1_info[5] पूर्ण,
पूर्ण;

काष्ठा pl08x_platक्रमm_data s3c64xx_dma1_plat_data = अणु
	.स_नकल_burst_size = PL08X_BURST_SZ_4,
	.स_नकल_bus_width = PL08X_BUS_WIDTH_32_BITS,
	.स_नकल_prot_buff = true,
	.स_नकल_prot_cache = true,
	.lli_buses = PL08X_AHB1,
	.mem_buses = PL08X_AHB1,
	.get_xfer_संकेत = pl08x_get_xfer_संकेत,
	.put_xfer_संकेत = pl08x_put_xfer_संकेत,
	.slave_channels = s3c64xx_dma1_info,
	.num_slave_channels = ARRAY_SIZE(s3c64xx_dma1_info),
	.slave_map = s3c64xx_dma1_slave_map,
	.slave_map_len = ARRAY_SIZE(s3c64xx_dma1_slave_map),
पूर्ण;

अटल AMBA_AHB_DEVICE(s3c64xx_dma1, "dma-pl080s.1", 0,
			0x75100000, अणुIRQ_DMA1पूर्ण, &s3c64xx_dma1_plat_data);

अटल पूर्णांक __init s3c64xx_pl080_init(व्योम)
अणु
	अगर (!soc_is_s3c64xx())
		वापस 0;

	/* Set all DMA configuration to be DMA, not SDMA */
	ग_लिखोl(0xffffff, S3C64XX_SDMA_SEL);

	अगर (of_have_populated_dt())
		वापस 0;

	amba_device_रेजिस्टर(&s3c64xx_dma0_device, &iomem_resource);
	amba_device_रेजिस्टर(&s3c64xx_dma1_device, &iomem_resource);

	वापस 0;
पूर्ण
arch_initcall(s3c64xx_pl080_init);
