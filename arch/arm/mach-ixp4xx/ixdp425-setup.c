<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/arm/mach-ixp4xx/ixdp425-setup.c
 *
 * IXDP425/IXCDP1100 board-setup
 *
 * Copyright (C) 2003-2005 MontaVista Software, Inc.
 *
 * Author: Deepak Saxena <dsaxena@plनिकासy.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/serial.h>
#समावेश <linux/tty.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/पन.स>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/platnand.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/memory.h>
#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/flash.h>

#समावेश "irqs.h"

#घोषणा IXDP425_SDA_PIN		7
#घोषणा IXDP425_SCL_PIN		6

/* न_अंकD Flash pins */
#घोषणा IXDP425_न_अंकD_NCE_PIN	12

#घोषणा IXDP425_न_अंकD_CMD_BYTE	0x01
#घोषणा IXDP425_न_अंकD_ADDR_BYTE	0x02

अटल काष्ठा flash_platक्रमm_data ixdp425_flash_data = अणु
	.map_name	= "cfi_probe",
	.width		= 2,
पूर्ण;

अटल काष्ठा resource ixdp425_flash_resource = अणु
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device ixdp425_flash = अणु
	.name		= "IXP4XX-Flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data = &ixdp425_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &ixdp425_flash_resource,
पूर्ण;

#अगर defined(CONFIG_MTD_न_अंकD_PLATFORM) || \
    defined(CONFIG_MTD_न_अंकD_PLATFORM_MODULE)

अटल काष्ठा mtd_partition ixdp425_partitions[] = अणु
	अणु
		.name	= "ixp400 NAND FS 0",
		.offset	= 0,
		.size 	= SZ_8M
	पूर्ण, अणु
		.name	= "ixp400 NAND FS 1",
		.offset	= MTDPART_OFS_APPEND,
		.size	= MTDPART_SIZ_FULL
	पूर्ण,
पूर्ण;

अटल व्योम
ixdp425_flash_nand_cmd_ctrl(काष्ठा nand_chip *this, पूर्णांक cmd, अचिन्हित पूर्णांक ctrl)
अणु
	पूर्णांक offset = (पूर्णांक)nand_get_controller_data(this);

	अगर (ctrl & न_अंकD_CTRL_CHANGE) अणु
		अगर (ctrl & न_अंकD_NCE) अणु
			gpio_set_value(IXDP425_न_अंकD_NCE_PIN, 0);
			udelay(5);
		पूर्ण अन्यथा
			gpio_set_value(IXDP425_न_अंकD_NCE_PIN, 1);

		offset = (ctrl & न_अंकD_CLE) ? IXDP425_न_अंकD_CMD_BYTE : 0;
		offset |= (ctrl & न_अंकD_ALE) ? IXDP425_न_अंकD_ADDR_BYTE : 0;
		nand_set_controller_data(this, (व्योम *)offset);
	पूर्ण

	अगर (cmd != न_अंकD_CMD_NONE)
		ग_लिखोb(cmd, this->legacy.IO_ADDR_W + offset);
पूर्ण

अटल काष्ठा platक्रमm_nand_data ixdp425_flash_nand_data = अणु
	.chip = अणु
		.nr_chips		= 1,
		.chip_delay		= 30,
		.partitions	 	= ixdp425_partitions,
		.nr_partitions	 	= ARRAY_SIZE(ixdp425_partitions),
	पूर्ण,
	.ctrl = अणु
		.cmd_ctrl 		= ixdp425_flash_nand_cmd_ctrl
	पूर्ण
पूर्ण;

अटल काष्ठा resource ixdp425_flash_nand_resource = अणु
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device ixdp425_flash_nand = अणु
	.name		= "gen_nand",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &ixdp425_flash_nand_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &ixdp425_flash_nand_resource,
पूर्ण;
#पूर्ण_अगर	/* CONFIG_MTD_न_अंकD_PLATFORM */

अटल काष्ठा gpiod_lookup_table ixdp425_i2c_gpiod_table = अणु
	.dev_id		= "i2c-gpio.0",
	.table		= अणु
		GPIO_LOOKUP_IDX("IXP4XX_GPIO_CHIP", IXDP425_SDA_PIN,
				शून्य, 0, GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
		GPIO_LOOKUP_IDX("IXP4XX_GPIO_CHIP", IXDP425_SCL_PIN,
				शून्य, 1, GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device ixdp425_i2c_gpio = अणु
	.name		= "i2c-gpio",
	.id		= 0,
	.dev	 = अणु
		.platक्रमm_data	= शून्य,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource ixdp425_uart_resources[] = अणु
	अणु
		.start		= IXP4XX_UART1_BASE_PHYS,
		.end		= IXP4XX_UART1_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM
	पूर्ण,
	अणु
		.start		= IXP4XX_UART2_BASE_PHYS,
		.end		= IXP4XX_UART2_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM
	पूर्ण
पूर्ण;

अटल काष्ठा plat_serial8250_port ixdp425_uart_data[] = अणु
	अणु
		.mapbase	= IXP4XX_UART1_BASE_PHYS,
		.membase	= (अक्षर *)IXP4XX_UART1_BASE_VIRT + REG_OFFSET,
		.irq		= IRQ_IXP4XX_UART1,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
		.uartclk	= IXP4XX_UART_XTAL,
	पूर्ण,
	अणु
		.mapbase	= IXP4XX_UART2_BASE_PHYS,
		.membase	= (अक्षर *)IXP4XX_UART2_BASE_VIRT + REG_OFFSET,
		.irq		= IRQ_IXP4XX_UART2,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
		.uartclk	= IXP4XX_UART_XTAL,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device ixdp425_uart = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev.platक्रमm_data	= ixdp425_uart_data,
	.num_resources		= 2,
	.resource		= ixdp425_uart_resources
पूर्ण;

/* Built-in 10/100 Ethernet MAC पूर्णांकerfaces */
अटल काष्ठा resource ixp425_npeb_resources[] = अणु
	अणु
		.start		= IXP4XX_EthB_BASE_PHYS,
		.end		= IXP4XX_EthB_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource ixp425_npec_resources[] = अणु
	अणु
		.start		= IXP4XX_EthC_BASE_PHYS,
		.end		= IXP4XX_EthC_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा eth_plat_info ixdp425_plat_eth[] = अणु
	अणु
		.phy		= 0,
		.rxq		= 3,
		.txपढ़ोyq	= 20,
	पूर्ण, अणु
		.phy		= 1,
		.rxq		= 4,
		.txपढ़ोyq	= 21,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device ixdp425_eth[] = अणु
	अणु
		.name			= "ixp4xx_eth",
		.id			= IXP4XX_ETH_NPEB,
		.dev.platक्रमm_data	= ixdp425_plat_eth,
		.num_resources		= ARRAY_SIZE(ixp425_npeb_resources),
		.resource		= ixp425_npeb_resources,
	पूर्ण, अणु
		.name			= "ixp4xx_eth",
		.id			= IXP4XX_ETH_NPEC,
		.dev.platक्रमm_data	= ixdp425_plat_eth + 1,
		.num_resources		= ARRAY_SIZE(ixp425_npec_resources),
		.resource		= ixp425_npec_resources,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device *ixdp425_devices[] __initdata = अणु
	&ixdp425_i2c_gpio,
	&ixdp425_flash,
#अगर defined(CONFIG_MTD_न_अंकD_PLATFORM) || \
    defined(CONFIG_MTD_न_अंकD_PLATFORM_MODULE)
	&ixdp425_flash_nand,
#पूर्ण_अगर
	&ixdp425_uart,
	&ixdp425_eth[0],
	&ixdp425_eth[1],
पूर्ण;

अटल व्योम __init ixdp425_init(व्योम)
अणु
	ixp4xx_sys_init();

	ixdp425_flash_resource.start = IXP4XX_EXP_BUS_BASE(0);
	ixdp425_flash_resource.end =
		IXP4XX_EXP_BUS_BASE(0) + ixp4xx_exp_bus_size - 1;

#अगर defined(CONFIG_MTD_न_अंकD_PLATFORM) || \
    defined(CONFIG_MTD_न_अंकD_PLATFORM_MODULE)
	ixdp425_flash_nand_resource.start = IXP4XX_EXP_BUS_BASE(3),
	ixdp425_flash_nand_resource.end   = IXP4XX_EXP_BUS_BASE(3) + 0x10 - 1;

	gpio_request(IXDP425_न_अंकD_NCE_PIN, "NAND NCE pin");
	gpio_direction_output(IXDP425_न_अंकD_NCE_PIN, 0);

	/* Configure expansion bus क्रम न_अंकD Flash */
	*IXP4XX_EXP_CS3 = IXP4XX_EXP_BUS_CS_EN |
			  IXP4XX_EXP_BUS_STROBE_T(1) |	/* extend by 1 घड़ी */
			  IXP4XX_EXP_BUS_CYCLES(0) |	/* Intel cycles */
			  IXP4XX_EXP_BUS_SIZE(0) |	/* 512bytes addr space*/
			  IXP4XX_EXP_BUS_WR_EN |
			  IXP4XX_EXP_BUS_BYTE_EN;	/* 8 bit data bus */
#पूर्ण_अगर

	अगर (cpu_is_ixp43x()) अणु
		ixdp425_uart.num_resources = 1;
		ixdp425_uart_data[1].flags = 0;
	पूर्ण

	gpiod_add_lookup_table(&ixdp425_i2c_gpiod_table);
	platक्रमm_add_devices(ixdp425_devices, ARRAY_SIZE(ixdp425_devices));
पूर्ण

#अगर_घोषित CONFIG_ARCH_IXDP425
MACHINE_START(IXDP425, "Intel IXDP425 Development Platform")
	/* Maपूर्णांकainer: MontaVista Software, Inc. */
	.map_io		= ixp4xx_map_io,
	.init_early	= ixp4xx_init_early,
	.init_irq	= ixp4xx_init_irq,
	.init_समय	= ixp4xx_समयr_init,
	.atag_offset	= 0x100,
	.init_machine	= ixdp425_init,
#अगर defined(CONFIG_PCI)
	.dma_zone_size	= SZ_64M,
#पूर्ण_अगर
	.restart	= ixp4xx_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_IXDP465
MACHINE_START(IXDP465, "Intel IXDP465 Development Platform")
	/* Maपूर्णांकainer: MontaVista Software, Inc. */
	.map_io		= ixp4xx_map_io,
	.init_early	= ixp4xx_init_early,
	.init_irq	= ixp4xx_init_irq,
	.init_समय	= ixp4xx_समयr_init,
	.atag_offset	= 0x100,
	.init_machine	= ixdp425_init,
#अगर defined(CONFIG_PCI)
	.dma_zone_size	= SZ_64M,
#पूर्ण_अगर
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_PRPMC1100
MACHINE_START(IXCDP1100, "Intel IXCDP1100 Development Platform")
	/* Maपूर्णांकainer: MontaVista Software, Inc. */
	.map_io		= ixp4xx_map_io,
	.init_early	= ixp4xx_init_early,
	.init_irq	= ixp4xx_init_irq,
	.init_समय	= ixp4xx_समयr_init,
	.atag_offset	= 0x100,
	.init_machine	= ixdp425_init,
#अगर defined(CONFIG_PCI)
	.dma_zone_size	= SZ_64M,
#पूर्ण_अगर
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_KIXRP435
MACHINE_START(KIXRP435, "Intel KIXRP435 Reference Platform")
	/* Maपूर्णांकainer: MontaVista Software, Inc. */
	.map_io		= ixp4xx_map_io,
	.init_early	= ixp4xx_init_early,
	.init_irq	= ixp4xx_init_irq,
	.init_समय	= ixp4xx_समयr_init,
	.atag_offset	= 0x100,
	.init_machine	= ixdp425_init,
#अगर defined(CONFIG_PCI)
	.dma_zone_size	= SZ_64M,
#पूर्ण_अगर
MACHINE_END
#पूर्ण_अगर
