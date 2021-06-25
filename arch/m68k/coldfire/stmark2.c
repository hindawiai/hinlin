<शैली गुरु>
/*
 * sपंचांगark2.c -- Support क्रम Sysam AMCORE खोलो board
 *
 * (C) Copyright 2017, Angelo Dureghello <angelo@sysam.it>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi-fsl-dspi.h>
#समावेश <linux/spi/flash.h>
#समावेश <linux/dma-mapping.h>
#समावेश <यंत्र/mcfsim.h>

/*
 * Partitioning of parallel NOR flash (39VF3201B)
 */
अटल काष्ठा mtd_partition sपंचांगark2_partitions[] = अणु
	अणु
		.name = "U-Boot (1024K)",
		.size = 0x100000,
		.offset = 0x0
	पूर्ण, अणु
		.name = "Kernel+initramfs (7168K)",
		.size = 0x700000,
		.offset = MTDPART_OFS_APPEND
	पूर्ण, अणु
		.name = "Flash Free Space (8192K)",
		.size = MTDPART_SIZ_FULL,
		.offset = MTDPART_OFS_APPEND
	पूर्ण
पूर्ण;

अटल काष्ठा flash_platक्रमm_data sपंचांगark2_spi_flash_data = अणु
	.name = "is25lp128",
	.parts = sपंचांगark2_partitions,
	.nr_parts = ARRAY_SIZE(sपंचांगark2_partitions),
	.type = "is25lp128",
पूर्ण;

अटल काष्ठा spi_board_info sपंचांगark2_board_info[] __initdata = अणु
	अणु
		.modalias = "m25p80",
		.max_speed_hz = 5000000,
		.bus_num = 0,
		.chip_select = 1,
		.platक्रमm_data = &sपंचांगark2_spi_flash_data,
		.mode = SPI_MODE_3,
	पूर्ण
पूर्ण;

/* SPI controller data, SPI (0) */
अटल काष्ठा fsl_dspi_platक्रमm_data dspi_spi0_info = अणु
	.cs_num = 4,
	.bus_num = 0,
	.sck_cs_delay = 100,
	.cs_sck_delay = 100,
पूर्ण;

अटल काष्ठा resource dspi_spi0_resource[] = अणु
	[0] = अणु
		.start = MCFDSPI_BASE0,
		.end   = MCFDSPI_BASE0 + 0xFF,
		.flags = IORESOURCE_MEM,
		पूर्ण,
	[1] = अणु
		.start = 12,
		.end   = 13,
		.flags = IORESOURCE_DMA,
	पूर्ण,
	[2] = अणु
		.start = MCF_IRQ_DSPI0,
		.end   = MCF_IRQ_DSPI0,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल u64 sपंचांगark2_dspi_mask = DMA_BIT_MASK(32);

/* SPI controller, id = bus number */
अटल काष्ठा platक्रमm_device dspi_spi0_device = अणु
	.name = "fsl-dspi",
	.id = 0,
	.num_resources = ARRAY_SIZE(dspi_spi0_resource),
	.resource = dspi_spi0_resource,
	.dev = अणु
		.platक्रमm_data = &dspi_spi0_info,
		.dma_mask = &sपंचांगark2_dspi_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *sपंचांगark2_devices[] __initdata = अणु
	&dspi_spi0_device,
पूर्ण;

/*
 * Note: proper pin-mux setup is mandatory क्रम proper SPI functionality.
 */
अटल पूर्णांक __init init_sपंचांगark2(व्योम)
अणु
	/* DSPI0, all pins as DSPI, and using CS1 */
	__raw_ग_लिखोb(0x80, MCFGPIO_PAR_DSPIOWL);
	__raw_ग_लिखोb(0xfc, MCFGPIO_PAR_DSPIOWH);

	/* Board gpio setup */
	__raw_ग_लिखोb(0x00, MCFGPIO_PAR_BE);
	__raw_ग_लिखोb(0x00, MCFGPIO_PAR_FBCTL);
	__raw_ग_लिखोb(0x00, MCFGPIO_PAR_CS);
	__raw_ग_लिखोb(0x00, MCFGPIO_PAR_CANI2C);

	platक्रमm_add_devices(sपंचांगark2_devices, ARRAY_SIZE(sपंचांगark2_devices));

	spi_रेजिस्टर_board_info(sपंचांगark2_board_info,
				ARRAY_SIZE(sपंचांगark2_board_info));

	वापस 0;
पूर्ण

late_initcall(init_sपंचांगark2);
