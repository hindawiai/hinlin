<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * timberdale.c timberdale FPGA MFD driver
 * Copyright (c) 2009 Intel Corporation
 */

/* Supports:
 * Timberdale FPGA
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/msi.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/slab.h>

#समावेश <linux/timb_gpपन.स>

#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/i2c-ocores.h>
#समावेश <linux/platक्रमm_data/i2c-xiic.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/xilinx_spi.h>
#समावेश <linux/spi/max7301.h>
#समावेश <linux/spi/mc33880.h>

#समावेश <linux/platक्रमm_data/tsc2007.h>
#समावेश <linux/platक्रमm_data/media/timb_radपन.स>
#समावेश <linux/platक्रमm_data/media/timb_video.h>

#समावेश <linux/timb_dma.h>

#समावेश <linux/ks8842.h>

#समावेश "timberdale.h"

#घोषणा DRIVER_NAME "timberdale"

काष्ठा timberdale_device अणु
	resource_माप_प्रकार		ctl_mapbase;
	अचिन्हित अक्षर __iomem   *ctl_membase;
	काष्ठा अणु
		u32 major;
		u32 minor;
		u32 config;
	पूर्ण fw;
पूर्ण;

/*--------------------------------------------------------------------------*/

अटल काष्ठा tsc2007_platक्रमm_data timberdale_tsc2007_platक्रमm_data = अणु
	.model = 2003,
	.x_plate_ohms = 100
पूर्ण;

अटल काष्ठा i2c_board_info timberdale_i2c_board_info[] = अणु
	अणु
		I2C_BOARD_INFO("tsc2007", 0x48),
		.platक्रमm_data = &timberdale_tsc2007_platक्रमm_data,
		.irq = IRQ_TIMBERDALE_TSC_INT
	पूर्ण,
पूर्ण;

अटल काष्ठा xiic_i2c_platक्रमm_data
timberdale_xiic_platक्रमm_data = अणु
	.devices = timberdale_i2c_board_info,
	.num_devices = ARRAY_SIZE(timberdale_i2c_board_info)
पूर्ण;

अटल काष्ठा ocores_i2c_platक्रमm_data
timberdale_ocores_platक्रमm_data = अणु
	.reg_shअगरt = 2,
	.घड़ी_khz = 62500,
	.devices = timberdale_i2c_board_info,
	.num_devices = ARRAY_SIZE(timberdale_i2c_board_info)
पूर्ण;

अटल स्थिर काष्ठा resource timberdale_xiic_resources[] = अणु
	अणु
		.start	= XIICOFFSET,
		.end	= XIICEND,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= IRQ_TIMBERDALE_I2C,
		.end	= IRQ_TIMBERDALE_I2C,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource timberdale_ocores_resources[] = अणु
	अणु
		.start	= OCORESOFFSET,
		.end	= OCORESEND,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start 	= IRQ_TIMBERDALE_I2C,
		.end	= IRQ_TIMBERDALE_I2C,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा max7301_platक्रमm_data timberdale_max7301_platक्रमm_data = अणु
	.base = 200
पूर्ण;

अटल स्थिर काष्ठा mc33880_platक्रमm_data timberdale_mc33880_platक्रमm_data = अणु
	.base = 100
पूर्ण;

अटल काष्ठा spi_board_info timberdale_spi_16bit_board_info[] = अणु
	अणु
		.modalias = "max7301",
		.max_speed_hz = 26000,
		.chip_select = 2,
		.mode = SPI_MODE_0,
		.platक्रमm_data = &timberdale_max7301_platक्रमm_data
	पूर्ण,
पूर्ण;

अटल काष्ठा spi_board_info timberdale_spi_8bit_board_info[] = अणु
	अणु
		.modalias = "mc33880",
		.max_speed_hz = 4000,
		.chip_select = 1,
		.mode = SPI_MODE_1,
		.platक्रमm_data = &timberdale_mc33880_platक्रमm_data
	पूर्ण,
पूर्ण;

अटल काष्ठा xspi_platक्रमm_data timberdale_xspi_platक्रमm_data = अणु
	.num_chipselect = 3,
	/* bits per word and devices will be filled in runसमय depending
	 * on the HW config
	 */
पूर्ण;

अटल स्थिर काष्ठा resource timberdale_spi_resources[] = अणु
	अणु
		.start 	= SPIOFFSET,
		.end	= SPIEND,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= IRQ_TIMBERDALE_SPI,
		.end	= IRQ_TIMBERDALE_SPI,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा ks8842_platक्रमm_data
	timberdale_ks8842_platक्रमm_data = अणु
	.rx_dma_channel = DMA_ETH_RX,
	.tx_dma_channel = DMA_ETH_TX
पूर्ण;

अटल स्थिर काष्ठा resource timberdale_eth_resources[] = अणु
	अणु
		.start	= ETHOFFSET,
		.end	= ETHEND,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= IRQ_TIMBERDALE_ETHSW_IF,
		.end	= IRQ_TIMBERDALE_ETHSW_IF,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा timbgpio_platक्रमm_data
	timberdale_gpio_platक्रमm_data = अणु
	.gpio_base = 0,
	.nr_pins = GPIO_NR_PINS,
	.irq_base = 200,
पूर्ण;

अटल स्थिर काष्ठा resource timberdale_gpio_resources[] = अणु
	अणु
		.start	= GPIOOFFSET,
		.end	= GPIOEND,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= IRQ_TIMBERDALE_GPIO,
		.end	= IRQ_TIMBERDALE_GPIO,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource timberdale_mlogicore_resources[] = अणु
	अणु
		.start	= MLCORखातापूर्णFSET,
		.end	= MLCOREEND,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= IRQ_TIMBERDALE_MLCORE,
		.end	= IRQ_TIMBERDALE_MLCORE,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= IRQ_TIMBERDALE_MLCORE_BUF,
		.end	= IRQ_TIMBERDALE_MLCORE_BUF,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource timberdale_uart_resources[] = अणु
	अणु
		.start	= UARTOFFSET,
		.end	= UARTEND,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= IRQ_TIMBERDALE_UART,
		.end	= IRQ_TIMBERDALE_UART,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource timberdale_uartlite_resources[] = अणु
	अणु
		.start	= UARTLITखातापूर्णFSET,
		.end	= UARTLITEEND,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= IRQ_TIMBERDALE_UARTLITE,
		.end	= IRQ_TIMBERDALE_UARTLITE,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा i2c_board_info timberdale_adv7180_i2c_board_info = अणु
	/* Requires jumper JP9 to be off */
	I2C_BOARD_INFO("adv7180", 0x42 >> 1),
	.irq = IRQ_TIMBERDALE_ADV7180
पूर्ण;

अटल काष्ठा timb_video_platक्रमm_data
	timberdale_video_platक्रमm_data = अणु
	.dma_channel = DMA_VIDEO_RX,
	.i2c_adapter = 0,
	.encoder = अणु
		.info = &timberdale_adv7180_i2c_board_info
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा resource
timberdale_radio_resources[] = अणु
	अणु
		.start	= RDSOFFSET,
		.end	= RDSEND,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= IRQ_TIMBERDALE_RDS,
		.end	= IRQ_TIMBERDALE_RDS,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा i2c_board_info timberdale_tef6868_i2c_board_info = अणु
	I2C_BOARD_INFO("tef6862", 0x60)
पूर्ण;

अटल काष्ठा i2c_board_info timberdale_saa7706_i2c_board_info = अणु
	I2C_BOARD_INFO("saa7706h", 0x1C)
पूर्ण;

अटल काष्ठा timb_radio_platक्रमm_data
	timberdale_radio_platक्रमm_data = अणु
	.i2c_adapter = 0,
	.tuner = &timberdale_tef6868_i2c_board_info,
	.dsp = &timberdale_saa7706_i2c_board_info
पूर्ण;

अटल स्थिर काष्ठा resource timberdale_video_resources[] = अणु
	अणु
		.start	= LOGIWOFFSET,
		.end	= LOGIWEND,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	/*
	note that the "frame buffer" is located in DMA area
	starting at 0x1200000
	*/
पूर्ण;

अटल काष्ठा timb_dma_platक्रमm_data timb_dma_platक्रमm_data = अणु
	.nr_channels = 10,
	.channels = अणु
		अणु
			/* UART RX */
			.rx = true,
			.descriptors = 2,
			.descriptor_elements = 1
		पूर्ण,
		अणु
			/* UART TX */
			.rx = false,
			.descriptors = 2,
			.descriptor_elements = 1
		पूर्ण,
		अणु
			/* MLB RX */
			.rx = true,
			.descriptors = 2,
			.descriptor_elements = 1
		पूर्ण,
		अणु
			/* MLB TX */
			.rx = false,
			.descriptors = 2,
			.descriptor_elements = 1
		पूर्ण,
		अणु
			/* Video RX */
			.rx = true,
			.bytes_per_line = 1440,
			.descriptors = 2,
			.descriptor_elements = 16
		पूर्ण,
		अणु
			/* Video framedrop */
		पूर्ण,
		अणु
			/* SDHCI RX */
			.rx = true,
		पूर्ण,
		अणु
			/* SDHCI TX */
		पूर्ण,
		अणु
			/* ETH RX */
			.rx = true,
			.descriptors = 2,
			.descriptor_elements = 1
		पूर्ण,
		अणु
			/* ETH TX */
			.rx = false,
			.descriptors = 2,
			.descriptor_elements = 1
		पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा resource timberdale_dma_resources[] = अणु
	अणु
		.start	= DMAOFFSET,
		.end	= DMAEND,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= IRQ_TIMBERDALE_DMA,
		.end	= IRQ_TIMBERDALE_DMA,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell timberdale_cells_bar0_cfg0[] = अणु
	अणु
		.name = "timb-dma",
		.num_resources = ARRAY_SIZE(timberdale_dma_resources),
		.resources = timberdale_dma_resources,
		.platक्रमm_data = &timb_dma_platक्रमm_data,
		.pdata_size = माप(timb_dma_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "timb-uart",
		.num_resources = ARRAY_SIZE(timberdale_uart_resources),
		.resources = timberdale_uart_resources,
	पूर्ण,
	अणु
		.name = "xiic-i2c",
		.num_resources = ARRAY_SIZE(timberdale_xiic_resources),
		.resources = timberdale_xiic_resources,
		.platक्रमm_data = &timberdale_xiic_platक्रमm_data,
		.pdata_size = माप(timberdale_xiic_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "timb-gpio",
		.num_resources = ARRAY_SIZE(timberdale_gpio_resources),
		.resources = timberdale_gpio_resources,
		.platक्रमm_data = &timberdale_gpio_platक्रमm_data,
		.pdata_size = माप(timberdale_gpio_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "timb-video",
		.num_resources = ARRAY_SIZE(timberdale_video_resources),
		.resources = timberdale_video_resources,
		.platक्रमm_data = &timberdale_video_platक्रमm_data,
		.pdata_size = माप(timberdale_video_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "timb-radio",
		.num_resources = ARRAY_SIZE(timberdale_radio_resources),
		.resources = timberdale_radio_resources,
		.platक्रमm_data = &timberdale_radio_platक्रमm_data,
		.pdata_size = माप(timberdale_radio_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "xilinx_spi",
		.num_resources = ARRAY_SIZE(timberdale_spi_resources),
		.resources = timberdale_spi_resources,
		.platक्रमm_data = &timberdale_xspi_platक्रमm_data,
		.pdata_size = माप(timberdale_xspi_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "ks8842",
		.num_resources = ARRAY_SIZE(timberdale_eth_resources),
		.resources = timberdale_eth_resources,
		.platक्रमm_data = &timberdale_ks8842_platक्रमm_data,
		.pdata_size = माप(timberdale_ks8842_platक्रमm_data),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell timberdale_cells_bar0_cfg1[] = अणु
	अणु
		.name = "timb-dma",
		.num_resources = ARRAY_SIZE(timberdale_dma_resources),
		.resources = timberdale_dma_resources,
		.platक्रमm_data = &timb_dma_platक्रमm_data,
		.pdata_size = माप(timb_dma_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "timb-uart",
		.num_resources = ARRAY_SIZE(timberdale_uart_resources),
		.resources = timberdale_uart_resources,
	पूर्ण,
	अणु
		.name = "uartlite",
		.num_resources = ARRAY_SIZE(timberdale_uartlite_resources),
		.resources = timberdale_uartlite_resources,
	पूर्ण,
	अणु
		.name = "xiic-i2c",
		.num_resources = ARRAY_SIZE(timberdale_xiic_resources),
		.resources = timberdale_xiic_resources,
		.platक्रमm_data = &timberdale_xiic_platक्रमm_data,
		.pdata_size = माप(timberdale_xiic_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "timb-gpio",
		.num_resources = ARRAY_SIZE(timberdale_gpio_resources),
		.resources = timberdale_gpio_resources,
		.platक्रमm_data = &timberdale_gpio_platक्रमm_data,
		.pdata_size = माप(timberdale_gpio_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "timb-mlogicore",
		.num_resources = ARRAY_SIZE(timberdale_mlogicore_resources),
		.resources = timberdale_mlogicore_resources,
	पूर्ण,
	अणु
		.name = "timb-video",
		.num_resources = ARRAY_SIZE(timberdale_video_resources),
		.resources = timberdale_video_resources,
		.platक्रमm_data = &timberdale_video_platक्रमm_data,
		.pdata_size = माप(timberdale_video_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "timb-radio",
		.num_resources = ARRAY_SIZE(timberdale_radio_resources),
		.resources = timberdale_radio_resources,
		.platक्रमm_data = &timberdale_radio_platक्रमm_data,
		.pdata_size = माप(timberdale_radio_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "xilinx_spi",
		.num_resources = ARRAY_SIZE(timberdale_spi_resources),
		.resources = timberdale_spi_resources,
		.platक्रमm_data = &timberdale_xspi_platक्रमm_data,
		.pdata_size = माप(timberdale_xspi_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "ks8842",
		.num_resources = ARRAY_SIZE(timberdale_eth_resources),
		.resources = timberdale_eth_resources,
		.platक्रमm_data = &timberdale_ks8842_platक्रमm_data,
		.pdata_size = माप(timberdale_ks8842_platक्रमm_data),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell timberdale_cells_bar0_cfg2[] = अणु
	अणु
		.name = "timb-dma",
		.num_resources = ARRAY_SIZE(timberdale_dma_resources),
		.resources = timberdale_dma_resources,
		.platक्रमm_data = &timb_dma_platक्रमm_data,
		.pdata_size = माप(timb_dma_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "timb-uart",
		.num_resources = ARRAY_SIZE(timberdale_uart_resources),
		.resources = timberdale_uart_resources,
	पूर्ण,
	अणु
		.name = "xiic-i2c",
		.num_resources = ARRAY_SIZE(timberdale_xiic_resources),
		.resources = timberdale_xiic_resources,
		.platक्रमm_data = &timberdale_xiic_platक्रमm_data,
		.pdata_size = माप(timberdale_xiic_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "timb-gpio",
		.num_resources = ARRAY_SIZE(timberdale_gpio_resources),
		.resources = timberdale_gpio_resources,
		.platक्रमm_data = &timberdale_gpio_platक्रमm_data,
		.pdata_size = माप(timberdale_gpio_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "timb-video",
		.num_resources = ARRAY_SIZE(timberdale_video_resources),
		.resources = timberdale_video_resources,
		.platक्रमm_data = &timberdale_video_platक्रमm_data,
		.pdata_size = माप(timberdale_video_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "timb-radio",
		.num_resources = ARRAY_SIZE(timberdale_radio_resources),
		.resources = timberdale_radio_resources,
		.platक्रमm_data = &timberdale_radio_platक्रमm_data,
		.pdata_size = माप(timberdale_radio_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "xilinx_spi",
		.num_resources = ARRAY_SIZE(timberdale_spi_resources),
		.resources = timberdale_spi_resources,
		.platक्रमm_data = &timberdale_xspi_platक्रमm_data,
		.pdata_size = माप(timberdale_xspi_platक्रमm_data),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell timberdale_cells_bar0_cfg3[] = अणु
	अणु
		.name = "timb-dma",
		.num_resources = ARRAY_SIZE(timberdale_dma_resources),
		.resources = timberdale_dma_resources,
		.platक्रमm_data = &timb_dma_platक्रमm_data,
		.pdata_size = माप(timb_dma_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "timb-uart",
		.num_resources = ARRAY_SIZE(timberdale_uart_resources),
		.resources = timberdale_uart_resources,
	पूर्ण,
	अणु
		.name = "ocores-i2c",
		.num_resources = ARRAY_SIZE(timberdale_ocores_resources),
		.resources = timberdale_ocores_resources,
		.platक्रमm_data = &timberdale_ocores_platक्रमm_data,
		.pdata_size = माप(timberdale_ocores_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "timb-gpio",
		.num_resources = ARRAY_SIZE(timberdale_gpio_resources),
		.resources = timberdale_gpio_resources,
		.platक्रमm_data = &timberdale_gpio_platक्रमm_data,
		.pdata_size = माप(timberdale_gpio_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "timb-video",
		.num_resources = ARRAY_SIZE(timberdale_video_resources),
		.resources = timberdale_video_resources,
		.platक्रमm_data = &timberdale_video_platक्रमm_data,
		.pdata_size = माप(timberdale_video_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "timb-radio",
		.num_resources = ARRAY_SIZE(timberdale_radio_resources),
		.resources = timberdale_radio_resources,
		.platक्रमm_data = &timberdale_radio_platक्रमm_data,
		.pdata_size = माप(timberdale_radio_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "xilinx_spi",
		.num_resources = ARRAY_SIZE(timberdale_spi_resources),
		.resources = timberdale_spi_resources,
		.platक्रमm_data = &timberdale_xspi_platक्रमm_data,
		.pdata_size = माप(timberdale_xspi_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "ks8842",
		.num_resources = ARRAY_SIZE(timberdale_eth_resources),
		.resources = timberdale_eth_resources,
		.platक्रमm_data = &timberdale_ks8842_platक्रमm_data,
		.pdata_size = माप(timberdale_ks8842_platक्रमm_data),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource timberdale_sdhc_resources[] = अणु
	/* located in bar 1 and bar 2 */
	अणु
		.start	= SDHC0OFFSET,
		.end	= SDHC0END,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= IRQ_TIMBERDALE_SDHC,
		.end	= IRQ_TIMBERDALE_SDHC,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell timberdale_cells_bar1[] = अणु
	अणु
		.name = "sdhci",
		.num_resources = ARRAY_SIZE(timberdale_sdhc_resources),
		.resources = timberdale_sdhc_resources,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell timberdale_cells_bar2[] = अणु
	अणु
		.name = "sdhci",
		.num_resources = ARRAY_SIZE(timberdale_sdhc_resources),
		.resources = timberdale_sdhc_resources,
	पूर्ण,
पूर्ण;

अटल sमाप_प्रकार show_fw_ver(काष्ठा device *dev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा timberdale_device *priv = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d.%d.%d\n", priv->fw.major, priv->fw.minor,
		priv->fw.config);
पूर्ण

अटल DEVICE_ATTR(fw_ver, S_IRUGO, show_fw_ver, शून्य);

/*--------------------------------------------------------------------------*/

अटल पूर्णांक timb_probe(काष्ठा pci_dev *dev,
	स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा timberdale_device *priv;
	पूर्णांक err, i;
	resource_माप_प्रकार mapbase;
	काष्ठा msix_entry *msix_entries = शून्य;
	u8 ip_setup;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	pci_set_drvdata(dev, priv);

	err = pci_enable_device(dev);
	अगर (err)
		जाओ err_enable;

	mapbase = pci_resource_start(dev, 0);
	अगर (!mapbase) अणु
		dev_err(&dev->dev, "No resource\n");
		जाओ err_start;
	पूर्ण

	/* create a resource क्रम the PCI master रेजिस्टर */
	priv->ctl_mapbase = mapbase + CHIPCTLOFFSET;
	अगर (!request_mem_region(priv->ctl_mapbase, CHIPCTLSIZE, "timb-ctl")) अणु
		dev_err(&dev->dev, "Failed to request ctl mem\n");
		जाओ err_start;
	पूर्ण

	priv->ctl_membase = ioremap(priv->ctl_mapbase, CHIPCTLSIZE);
	अगर (!priv->ctl_membase) अणु
		dev_err(&dev->dev, "ioremap failed for ctl mem\n");
		जाओ err_ioremap;
	पूर्ण

	/* पढ़ो the HW config */
	priv->fw.major = ioपढ़ो32(priv->ctl_membase + TIMB_REV_MAJOR);
	priv->fw.minor = ioपढ़ो32(priv->ctl_membase + TIMB_REV_MINOR);
	priv->fw.config = ioपढ़ो32(priv->ctl_membase + TIMB_HW_CONFIG);

	अगर (priv->fw.major > TIMB_SUPPORTED_MAJOR) अणु
		dev_err(&dev->dev, "The driver supports an older "
			"version of the FPGA, please update the driver to "
			"support %d.%d\n", priv->fw.major, priv->fw.minor);
		जाओ err_config;
	पूर्ण
	अगर (priv->fw.major < TIMB_SUPPORTED_MAJOR ||
		priv->fw.minor < TIMB_REQUIRED_MINOR) अणु
		dev_err(&dev->dev, "The FPGA image is too old (%d.%d), "
			"please upgrade the FPGA to at least: %d.%d\n",
			priv->fw.major, priv->fw.minor,
			TIMB_SUPPORTED_MAJOR, TIMB_REQUIRED_MINOR);
		जाओ err_config;
	पूर्ण

	msix_entries = kसुस्मृति(TIMBERDALE_NR_IRQS, माप(*msix_entries),
			       GFP_KERNEL);
	अगर (!msix_entries)
		जाओ err_config;

	क्रम (i = 0; i < TIMBERDALE_NR_IRQS; i++)
		msix_entries[i].entry = i;

	err = pci_enable_msix_exact(dev, msix_entries, TIMBERDALE_NR_IRQS);
	अगर (err) अणु
		dev_err(&dev->dev,
			"MSI-X init failed: %d, expected entries: %d\n",
			err, TIMBERDALE_NR_IRQS);
		जाओ err_msix;
	पूर्ण

	err = device_create_file(&dev->dev, &dev_attr_fw_ver);
	अगर (err)
		जाओ err_create_file;

	/* Reset all FPGA PLB peripherals */
	ioग_लिखो32(0x1, priv->ctl_membase + TIMB_SW_RST);

	/* update IRQ offsets in I2C board info */
	क्रम (i = 0; i < ARRAY_SIZE(timberdale_i2c_board_info); i++)
		timberdale_i2c_board_info[i].irq =
			msix_entries[timberdale_i2c_board_info[i].irq].vector;

	/* Update the SPI configuration depending on the HW (8 or 16 bit) */
	अगर (priv->fw.config & TIMB_HW_CONFIG_SPI_8BIT) अणु
		timberdale_xspi_platक्रमm_data.bits_per_word = 8;
		timberdale_xspi_platक्रमm_data.devices =
			timberdale_spi_8bit_board_info;
		timberdale_xspi_platक्रमm_data.num_devices =
			ARRAY_SIZE(timberdale_spi_8bit_board_info);
	पूर्ण अन्यथा अणु
		timberdale_xspi_platक्रमm_data.bits_per_word = 16;
		timberdale_xspi_platक्रमm_data.devices =
			timberdale_spi_16bit_board_info;
		timberdale_xspi_platक्रमm_data.num_devices =
			ARRAY_SIZE(timberdale_spi_16bit_board_info);
	पूर्ण

	ip_setup = priv->fw.config & TIMB_HW_VER_MASK;
	चयन (ip_setup) अणु
	हाल TIMB_HW_VER0:
		err = mfd_add_devices(&dev->dev, -1,
			timberdale_cells_bar0_cfg0,
			ARRAY_SIZE(timberdale_cells_bar0_cfg0),
			&dev->resource[0], msix_entries[0].vector, शून्य);
		अवरोध;
	हाल TIMB_HW_VER1:
		err = mfd_add_devices(&dev->dev, -1,
			timberdale_cells_bar0_cfg1,
			ARRAY_SIZE(timberdale_cells_bar0_cfg1),
			&dev->resource[0], msix_entries[0].vector, शून्य);
		अवरोध;
	हाल TIMB_HW_VER2:
		err = mfd_add_devices(&dev->dev, -1,
			timberdale_cells_bar0_cfg2,
			ARRAY_SIZE(timberdale_cells_bar0_cfg2),
			&dev->resource[0], msix_entries[0].vector, शून्य);
		अवरोध;
	हाल TIMB_HW_VER3:
		err = mfd_add_devices(&dev->dev, -1,
			timberdale_cells_bar0_cfg3,
			ARRAY_SIZE(timberdale_cells_bar0_cfg3),
			&dev->resource[0], msix_entries[0].vector, शून्य);
		अवरोध;
	शेष:
		dev_err(&dev->dev, "Unknown IP setup: %d.%d.%d\n",
			priv->fw.major, priv->fw.minor, ip_setup);
		err = -ENODEV;
		जाओ err_mfd;
	पूर्ण

	अगर (err) अणु
		dev_err(&dev->dev, "mfd_add_devices failed: %d\n", err);
		जाओ err_mfd;
	पूर्ण

	err = mfd_add_devices(&dev->dev, 0,
		timberdale_cells_bar1, ARRAY_SIZE(timberdale_cells_bar1),
		&dev->resource[1], msix_entries[0].vector, शून्य);
	अगर (err) अणु
		dev_err(&dev->dev, "mfd_add_devices failed: %d\n", err);
		जाओ err_mfd2;
	पूर्ण

	/* only version 0 and 3 have the iNand routed to SDHCI */
	अगर (((priv->fw.config & TIMB_HW_VER_MASK) == TIMB_HW_VER0) ||
		((priv->fw.config & TIMB_HW_VER_MASK) == TIMB_HW_VER3)) अणु
		err = mfd_add_devices(&dev->dev, 1, timberdale_cells_bar2,
			ARRAY_SIZE(timberdale_cells_bar2),
			&dev->resource[2], msix_entries[0].vector, शून्य);
		अगर (err) अणु
			dev_err(&dev->dev, "mfd_add_devices failed: %d\n", err);
			जाओ err_mfd2;
		पूर्ण
	पूर्ण

	kमुक्त(msix_entries);

	dev_info(&dev->dev,
		"Found Timberdale Card. Rev: %d.%d, HW config: 0x%02x\n",
		priv->fw.major, priv->fw.minor, priv->fw.config);

	वापस 0;

err_mfd2:
	mfd_हटाओ_devices(&dev->dev);
err_mfd:
	device_हटाओ_file(&dev->dev, &dev_attr_fw_ver);
err_create_file:
	pci_disable_msix(dev);
err_msix:
	kमुक्त(msix_entries);
err_config:
	iounmap(priv->ctl_membase);
err_ioremap:
	release_mem_region(priv->ctl_mapbase, CHIPCTLSIZE);
err_start:
	pci_disable_device(dev);
err_enable:
	kमुक्त(priv);
	वापस -ENODEV;
पूर्ण

अटल व्योम timb_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा timberdale_device *priv = pci_get_drvdata(dev);

	mfd_हटाओ_devices(&dev->dev);

	device_हटाओ_file(&dev->dev, &dev_attr_fw_ver);

	iounmap(priv->ctl_membase);
	release_mem_region(priv->ctl_mapbase, CHIPCTLSIZE);

	pci_disable_msix(dev);
	pci_disable_device(dev);
	kमुक्त(priv);
पूर्ण

अटल स्थिर काष्ठा pci_device_id timberdale_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_TIMB, PCI_DEVICE_ID_TIMB) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, timberdale_pci_tbl);

अटल काष्ठा pci_driver timberdale_pci_driver = अणु
	.name = DRIVER_NAME,
	.id_table = timberdale_pci_tbl,
	.probe = timb_probe,
	.हटाओ = timb_हटाओ,
पूर्ण;

module_pci_driver(timberdale_pci_driver);

MODULE_AUTHOR("Mocean Laboratories <info@mocean-labs.com>");
MODULE_VERSION(DRV_VERSION);
MODULE_LICENSE("GPL v2");
