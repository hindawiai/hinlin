<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/arm/mach-ep93xx/ts72xx.c
 * Technologic Systems TS72xx SBC support.
 *
 * Copyright (C) 2006 Lennert Buytenhek <buytenh@wantstofly.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/mtd/platnand.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/flash.h>
#समावेश <linux/spi/mmc_spi.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/platक्रमm_data/spi-ep93xx.h>
#समावेश <linux/gpio/machine.h>

#समावेश "gpio-ep93xx.h"
#समावेश "hardware.h"
#समावेश <mach/irqs.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "soc.h"
#समावेश "ts72xx.h"

/*************************************************************************
 * IO map
 *************************************************************************/
अटल काष्ठा map_desc ts72xx_io_desc[] __initdata = अणु
	अणु
		.भव	= (अचिन्हित दीर्घ)TS72XX_MODEL_VIRT_BASE,
		.pfn		= __phys_to_pfn(TS72XX_MODEL_PHYS_BASE),
		.length		= TS72XX_MODEL_SIZE,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= (अचिन्हित दीर्घ)TS72XX_OPTIONS_VIRT_BASE,
		.pfn		= __phys_to_pfn(TS72XX_OPTIONS_PHYS_BASE),
		.length		= TS72XX_OPTIONS_SIZE,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= (अचिन्हित दीर्घ)TS72XX_OPTIONS2_VIRT_BASE,
		.pfn		= __phys_to_pfn(TS72XX_OPTIONS2_PHYS_BASE),
		.length		= TS72XX_OPTIONS2_SIZE,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= (अचिन्हित दीर्घ)TS72XX_CPLDVER_VIRT_BASE,
		.pfn		= __phys_to_pfn(TS72XX_CPLDVER_PHYS_BASE),
		.length		= TS72XX_CPLDVER_SIZE,
		.type		= MT_DEVICE,
	पूर्ण
पूर्ण;

अटल व्योम __init ts72xx_map_io(व्योम)
अणु
	ep93xx_map_io();
	iotable_init(ts72xx_io_desc, ARRAY_SIZE(ts72xx_io_desc));
पूर्ण


/*************************************************************************
 * न_अंकD flash
 *************************************************************************/
#घोषणा TS72XX_न_अंकD_CONTROL_ADDR_LINE	22	/* 0xN0400000 */
#घोषणा TS72XX_न_अंकD_BUSY_ADDR_LINE	23	/* 0xN0800000 */

अटल व्योम ts72xx_nand_hwcontrol(काष्ठा nand_chip *chip,
				  पूर्णांक cmd, अचिन्हित पूर्णांक ctrl)
अणु
	अगर (ctrl & न_अंकD_CTRL_CHANGE) अणु
		व्योम __iomem *addr = chip->legacy.IO_ADDR_R;
		अचिन्हित अक्षर bits;

		addr += (1 << TS72XX_न_अंकD_CONTROL_ADDR_LINE);

		bits = __raw_पढ़ोb(addr) & ~0x07;
		bits |= (ctrl & न_अंकD_NCE) << 2;	/* bit 0 -> bit 2 */
		bits |= (ctrl & न_अंकD_CLE);	/* bit 1 -> bit 1 */
		bits |= (ctrl & न_अंकD_ALE) >> 2;	/* bit 2 -> bit 0 */

		__raw_ग_लिखोb(bits, addr);
	पूर्ण

	अगर (cmd != न_अंकD_CMD_NONE)
		__raw_ग_लिखोb(cmd, chip->legacy.IO_ADDR_W);
पूर्ण

अटल पूर्णांक ts72xx_nand_device_पढ़ोy(काष्ठा nand_chip *chip)
अणु
	व्योम __iomem *addr = chip->legacy.IO_ADDR_R;

	addr += (1 << TS72XX_न_अंकD_BUSY_ADDR_LINE);

	वापस !!(__raw_पढ़ोb(addr) & 0x20);
पूर्ण

#घोषणा TS72XX_BOOTROM_PART_SIZE	(SZ_16K)
#घोषणा TS72XX_REDBOOT_PART_SIZE	(SZ_2M + SZ_1M)

अटल काष्ठा mtd_partition ts72xx_nand_parts[] = अणु
	अणु
		.name		= "TS-BOOTROM",
		.offset		= 0,
		.size		= TS72XX_BOOTROM_PART_SIZE,
		.mask_flags	= MTD_WRITEABLE,	/* क्रमce पढ़ो-only */
	पूर्ण, अणु
		.name		= "Linux",
		.offset		= MTDPART_OFS_RETAIN,
		.size		= TS72XX_REDBOOT_PART_SIZE,
				/* leave so much क्रम last partition */
	पूर्ण, अणु
		.name		= "RedBoot",
		.offset		= MTDPART_OFS_APPEND,
		.size		= MTDPART_SIZ_FULL,
		.mask_flags	= MTD_WRITEABLE,	/* क्रमce पढ़ो-only */
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_nand_data ts72xx_nand_data = अणु
	.chip = अणु
		.nr_chips	= 1,
		.chip_offset	= 0,
		.chip_delay	= 15,
	पूर्ण,
	.ctrl = अणु
		.cmd_ctrl	= ts72xx_nand_hwcontrol,
		.dev_पढ़ोy	= ts72xx_nand_device_पढ़ोy,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource ts72xx_nand_resource[] = अणु
	अणु
		.start		= 0,			/* filled in later */
		.end		= 0,			/* filled in later */
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device ts72xx_nand_flash = अणु
	.name			= "gen_nand",
	.id			= -1,
	.dev.platक्रमm_data	= &ts72xx_nand_data,
	.resource		= ts72xx_nand_resource,
	.num_resources		= ARRAY_SIZE(ts72xx_nand_resource),
पूर्ण;

व्योम __init ts72xx_रेजिस्टर_flash(काष्ठा mtd_partition *parts, पूर्णांक n,
				  resource_माप_प्रकार start)
अणु
	/*
	 * TS7200 has NOR flash all other TS72xx board have न_अंकD flash.
	 */
	अगर (board_is_ts7200()) अणु
		ep93xx_रेजिस्टर_flash(2, EP93XX_CS6_PHYS_BASE, SZ_16M);
	पूर्ण अन्यथा अणु
		ts72xx_nand_resource[0].start = start;
		ts72xx_nand_resource[0].end = start + SZ_16M - 1;

		ts72xx_nand_data.chip.partitions = parts;
		ts72xx_nand_data.chip.nr_partitions = n;

		platक्रमm_device_रेजिस्टर(&ts72xx_nand_flash);
	पूर्ण
पूर्ण

/*************************************************************************
 * RTC M48T86
 *************************************************************************/
#घोषणा TS72XX_RTC_INDEX_PHYS_BASE	(EP93XX_CS1_PHYS_BASE + 0x00800000)
#घोषणा TS72XX_RTC_DATA_PHYS_BASE	(EP93XX_CS1_PHYS_BASE + 0x01700000)

अटल काष्ठा resource ts72xx_rtc_resources[] = अणु
	DEFINE_RES_MEM(TS72XX_RTC_INDEX_PHYS_BASE, 0x01),
	DEFINE_RES_MEM(TS72XX_RTC_DATA_PHYS_BASE, 0x01),
पूर्ण;

अटल काष्ठा platक्रमm_device ts72xx_rtc_device = अणु
	.name		= "rtc-m48t86",
	.id		= -1,
	.resource	= ts72xx_rtc_resources,
	.num_resources 	= ARRAY_SIZE(ts72xx_rtc_resources),
पूर्ण;

/*************************************************************************
 * Watchकरोg (in CPLD)
 *************************************************************************/
#घोषणा TS72XX_WDT_CONTROL_PHYS_BASE	(EP93XX_CS2_PHYS_BASE + 0x03800000)
#घोषणा TS72XX_WDT_FEED_PHYS_BASE	(EP93XX_CS2_PHYS_BASE + 0x03c00000)

अटल काष्ठा resource ts72xx_wdt_resources[] = अणु
	DEFINE_RES_MEM(TS72XX_WDT_CONTROL_PHYS_BASE, 0x01),
	DEFINE_RES_MEM(TS72XX_WDT_FEED_PHYS_BASE, 0x01),
पूर्ण;

अटल काष्ठा platक्रमm_device ts72xx_wdt_device = अणु
	.name		= "ts72xx-wdt",
	.id		= -1,
	.resource	= ts72xx_wdt_resources,
	.num_resources	= ARRAY_SIZE(ts72xx_wdt_resources),
पूर्ण;

/*************************************************************************
 * ETH
 *************************************************************************/
अटल काष्ठा ep93xx_eth_data __initdata ts72xx_eth_data = अणु
	.phy_id		= 1,
पूर्ण;

/*************************************************************************
 * SPI SD/MMC host
 *************************************************************************/
#घोषणा BK3_EN_SDCARD_PHYS_BASE         0x12400000
#घोषणा BK3_EN_SDCARD_PWR 0x0
#घोषणा BK3_DIS_SDCARD_PWR 0x0C
अटल व्योम bk3_mmc_spi_setघातer(काष्ठा device *dev, अचिन्हित पूर्णांक vdd)
अणु
	व्योम __iomem *pwr_sd = ioremap(BK3_EN_SDCARD_PHYS_BASE, SZ_4K);

	अगर (!pwr_sd) अणु
		pr_err("Failed to enable SD card power!");
		वापस;
	पूर्ण

	pr_debug("%s: SD card pwr %s VDD:0x%x\n", __func__,
		 !!vdd ? "ON" : "OFF", vdd);

	अगर (!!vdd)
		__raw_ग_लिखोb(BK3_EN_SDCARD_PWR, pwr_sd);
	अन्यथा
		__raw_ग_लिखोb(BK3_DIS_SDCARD_PWR, pwr_sd);

	iounmap(pwr_sd);
पूर्ण

अटल काष्ठा mmc_spi_platक्रमm_data bk3_spi_mmc_data = अणु
	.detect_delay	= 500,
	.घातerup_msecs	= 100,
	.ocr_mask	= MMC_VDD_32_33 | MMC_VDD_33_34,
	.caps		= MMC_CAP_NONREMOVABLE,
	.setघातer       = bk3_mmc_spi_setघातer,
पूर्ण;

/*************************************************************************
 * SPI Bus - SD card access
 *************************************************************************/
अटल काष्ठा spi_board_info bk3_spi_board_info[] __initdata = अणु
	अणु
		.modalias		= "mmc_spi",
		.platक्रमm_data		= &bk3_spi_mmc_data,
		.max_speed_hz		= 7.4E6,
		.bus_num		= 0,
		.chip_select		= 0,
		.mode			= SPI_MODE_0,
	पूर्ण,
पूर्ण;

/*
 * This is a stub -> the FGPIO[3] pin is not connected on the schematic
 * The all work is perक्रमmed स्वतःmatically by !SPI_FRAME (SFRM1) and
 * goes through CPLD
 */
अटल काष्ठा gpiod_lookup_table bk3_spi_cs_gpio_table = अणु
	.dev_id = "spi0",
	.table = अणु
		GPIO_LOOKUP("F", 3, "cs", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा ep93xx_spi_info bk3_spi_master __initdata = अणु
	.use_dma	= 1,
पूर्ण;

/*************************************************************************
 * TS72XX support code
 *************************************************************************/
#अगर IS_ENABLED(CONFIG_FPGA_MGR_TS73XX)

/* Relative to EP93XX_CS1_PHYS_BASE */
#घोषणा TS73XX_FPGA_LOADER_BASE		0x03c00000

अटल काष्ठा resource ts73xx_fpga_resources[] = अणु
	अणु
		.start	= EP93XX_CS1_PHYS_BASE + TS73XX_FPGA_LOADER_BASE,
		.end	= EP93XX_CS1_PHYS_BASE + TS73XX_FPGA_LOADER_BASE + 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device ts73xx_fpga_device = अणु
	.name	= "ts73xx-fpga-mgr",
	.id	= -1,
	.resource = ts73xx_fpga_resources,
	.num_resources = ARRAY_SIZE(ts73xx_fpga_resources),
पूर्ण;

#पूर्ण_अगर

/*************************************************************************
 * SPI Bus
 *************************************************************************/
अटल काष्ठा spi_board_info ts72xx_spi_devices[] __initdata = अणु
	अणु
		.modalias		= "tmp122",
		.max_speed_hz		= 2 * 1000 * 1000,
		.bus_num		= 0,
		.chip_select		= 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table ts72xx_spi_cs_gpio_table = अणु
	.dev_id = "spi0",
	.table = अणु
		/* DIO_17 */
		GPIO_LOOKUP("F", 2, "cs", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा ep93xx_spi_info ts72xx_spi_info __initdata = अणु
	/* Intentionally left blank */
पूर्ण;

अटल व्योम __init ts72xx_init_machine(व्योम)
अणु
	ep93xx_init_devices();
	ts72xx_रेजिस्टर_flash(ts72xx_nand_parts, ARRAY_SIZE(ts72xx_nand_parts),
			      is_ts9420_installed() ?
			      EP93XX_CS7_PHYS_BASE : EP93XX_CS6_PHYS_BASE);
	platक्रमm_device_रेजिस्टर(&ts72xx_rtc_device);
	platक्रमm_device_रेजिस्टर(&ts72xx_wdt_device);

	ep93xx_रेजिस्टर_eth(&ts72xx_eth_data, 1);
#अगर IS_ENABLED(CONFIG_FPGA_MGR_TS73XX)
	अगर (board_is_ts7300())
		platक्रमm_device_रेजिस्टर(&ts73xx_fpga_device);
#पूर्ण_अगर
	gpiod_add_lookup_table(&ts72xx_spi_cs_gpio_table);
	ep93xx_रेजिस्टर_spi(&ts72xx_spi_info, ts72xx_spi_devices,
			    ARRAY_SIZE(ts72xx_spi_devices));
पूर्ण

MACHINE_START(TS72XX, "Technologic Systems TS-72xx SBC")
	/* Maपूर्णांकainer: Lennert Buytenhek <buytenh@wantstofly.org> */
	.atag_offset	= 0x100,
	.map_io		= ts72xx_map_io,
	.init_irq	= ep93xx_init_irq,
	.init_समय	= ep93xx_समयr_init,
	.init_machine	= ts72xx_init_machine,
	.init_late	= ep93xx_init_late,
	.restart	= ep93xx_restart,
MACHINE_END

/*************************************************************************
 * EP93xx I2S audio peripheral handling
 *************************************************************************/
अटल काष्ठा resource ep93xx_i2s_resource[] = अणु
	DEFINE_RES_MEM(EP93XX_I2S_PHYS_BASE, 0x100),
	DEFINE_RES_IRQ_NAMED(IRQ_EP93XX_SAI, "spilink i2s slave"),
पूर्ण;

अटल काष्ठा platक्रमm_device ep93xx_i2s_device = अणु
	.name		= "ep93xx-spilink-i2s",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(ep93xx_i2s_resource),
	.resource	= ep93xx_i2s_resource,
पूर्ण;

/*************************************************************************
 * BK3 support code
 *************************************************************************/
अटल काष्ठा mtd_partition bk3_nand_parts[] = अणु
	अणु
		.name		= "System",
		.offset	= 0x00000000,
		.size		= 0x01e00000,
	पूर्ण, अणु
		.name		= "Data",
		.offset	= 0x01e00000,
		.size		= 0x05f20000
	पूर्ण, अणु
		.name		= "RedBoot",
		.offset	= 0x07d20000,
		.size		= 0x002e0000,
		.mask_flags	= MTD_WRITEABLE,	/* क्रमce RO */
	पूर्ण,
पूर्ण;

अटल व्योम __init bk3_init_machine(व्योम)
अणु
	ep93xx_init_devices();

	ts72xx_रेजिस्टर_flash(bk3_nand_parts, ARRAY_SIZE(bk3_nand_parts),
			      EP93XX_CS6_PHYS_BASE);

	ep93xx_रेजिस्टर_eth(&ts72xx_eth_data, 1);

	gpiod_add_lookup_table(&bk3_spi_cs_gpio_table);
	ep93xx_रेजिस्टर_spi(&bk3_spi_master, bk3_spi_board_info,
			    ARRAY_SIZE(bk3_spi_board_info));

	/* Configure ep93xx's I2S to use AC97 pins */
	ep93xx_devcfg_set_bits(EP93XX_SYSCON_DEVCFG_I2SONAC97);
	platक्रमm_device_रेजिस्टर(&ep93xx_i2s_device);
पूर्ण

MACHINE_START(BK3, "Liebherr controller BK3.1")
	/* Maपूर्णांकainer: Lukasz Majewski <lukma@denx.de> */
	.atag_offset	= 0x100,
	.map_io		= ts72xx_map_io,
	.init_irq	= ep93xx_init_irq,
	.init_समय	= ep93xx_समयr_init,
	.init_machine	= bk3_init_machine,
	.init_late	= ep93xx_init_late,
	.restart	= ep93xx_restart,
MACHINE_END
