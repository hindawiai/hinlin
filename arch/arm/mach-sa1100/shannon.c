<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/arm/mach-sa1100/shannon.c
 */

#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_data/sa11x0-serial.h>
#समावेश <linux/tty.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/regulator/machine.h>

#समावेश <video/sa1100fb.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/setup.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/flash.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <linux/platक्रमm_data/mfd-mcp-sa11x0.h>
#समावेश <mach/shannon.h>
#समावेश <mach/irqs.h>

#समावेश "generic.h"

अटल काष्ठा mtd_partition shannon_partitions[] = अणु
	अणु
		.name		= "BLOB boot loader",
		.offset		= 0,
		.size		= 0x20000
	पूर्ण,
	अणु
		.name		= "kernel",
		.offset		= MTDPART_OFS_APPEND,
		.size		= 0xe0000
	पूर्ण,
	अणु
		.name		= "initrd",
		.offset		= MTDPART_OFS_APPEND,	
		.size		= MTDPART_SIZ_FULL
	पूर्ण
पूर्ण;

अटल काष्ठा flash_platक्रमm_data shannon_flash_data = अणु
	.map_name	= "cfi_probe",
	.parts		= shannon_partitions,
	.nr_parts	= ARRAY_SIZE(shannon_partitions),
पूर्ण;

अटल काष्ठा resource shannon_flash_resource =
	DEFINE_RES_MEM(SA1100_CS0_PHYS, SZ_4M);

अटल काष्ठा mcp_plat_data shannon_mcp_data = अणु
	.mccr0		= MCCR0_ADM,
	.sclk_rate	= 11981000,
पूर्ण;

अटल काष्ठा sa1100fb_mach_info shannon_lcd_info = अणु
	.pixघड़ी	= 152500,	.bpp		= 8,
	.xres		= 640,		.yres		= 480,

	.hsync_len	= 4,		.vsync_len	= 3,
	.left_margin	= 2,		.upper_margin	= 0,
	.right_margin	= 1,		.lower_margin	= 0,

	.sync		= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,

	.lccr0		= LCCR0_Color | LCCR0_Dual | LCCR0_Pas,
	.lccr3		= LCCR3_ACBsDiv(512),
पूर्ण;

अटल काष्ठा gpiod_lookup_table shannon_pcmcia0_gpio_table = अणु
	.dev_id = "sa11x0-pcmcia.0",
	.table = अणु
		GPIO_LOOKUP("gpio", 24, "detect", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio", 26, "ready", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table shannon_pcmcia1_gpio_table = अणु
	.dev_id = "sa11x0-pcmcia.1",
	.table = अणु
		GPIO_LOOKUP("gpio", 25, "detect", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio", 27, "ready", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा regulator_consumer_supply shannon_cf_vcc_consumers[] = अणु
	REGULATOR_SUPPLY("vcc", "sa11x0-pcmcia.0"),
	REGULATOR_SUPPLY("vcc", "sa11x0-pcmcia.1"),
पूर्ण;

अटल काष्ठा fixed_voltage_config shannon_cf_vcc_pdata __initdata = अणु
	.supply_name = "cf-power",
	.microvolts = 3300000,
	.enabled_at_boot = 1,
पूर्ण;

अटल काष्ठा gpiod_lookup_table shannon_display_gpio_table = अणु
	.dev_id = "sa11x0-fb",
	.table = अणु
		GPIO_LOOKUP("gpio", 22, "shannon-lcden", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init shannon_init(व्योम)
अणु
	sa11x0_रेजिस्टर_fixed_regulator(0, &shannon_cf_vcc_pdata,
					shannon_cf_vcc_consumers,
					ARRAY_SIZE(shannon_cf_vcc_consumers),
					false);
	sa11x0_रेजिस्टर_pcmcia(0, &shannon_pcmcia0_gpio_table);
	sa11x0_रेजिस्टर_pcmcia(1, &shannon_pcmcia1_gpio_table);
	sa11x0_ppc_configure_mcp();
	gpiod_add_lookup_table(&shannon_display_gpio_table);
	sa11x0_रेजिस्टर_lcd(&shannon_lcd_info);
	sa11x0_रेजिस्टर_mtd(&shannon_flash_data, &shannon_flash_resource, 1);
	sa11x0_रेजिस्टर_mcp(&shannon_mcp_data);
पूर्ण

अटल व्योम __init shannon_map_io(व्योम)
अणु
	sa1100_map_io();

	sa1100_रेजिस्टर_uart(0, 3);
	sa1100_रेजिस्टर_uart(1, 1);

	Ser1SDCR0 |= SDCR0_SUS;
	GAFR |= (GPIO_UART_TXD | GPIO_UART_RXD);
	GPDR |= GPIO_UART_TXD | SHANNON_GPIO_CODEC_RESET;
	GPDR &= ~GPIO_UART_RXD;
	PPAR |= PPAR_UPR;

	/* reset the codec */
	GPCR = SHANNON_GPIO_CODEC_RESET;
	GPSR = SHANNON_GPIO_CODEC_RESET;
पूर्ण

MACHINE_START(SHANNON, "Shannon (AKA: Tuxscreen)")
	.atag_offset	= 0x100,
	.map_io		= shannon_map_io,
	.nr_irqs	= SA1100_NR_IRQS,
	.init_irq	= sa1100_init_irq,
	.init_समय	= sa1100_समयr_init,
	.init_machine	= shannon_init,
	.init_late	= sa11x0_init_late,
	.restart	= sa11x0_restart,
MACHINE_END
