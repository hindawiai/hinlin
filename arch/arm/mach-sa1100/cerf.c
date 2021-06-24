<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-sa1100/cerf.c
 *
 * Apr-2003 : Removed some old PDA crud [FB]
 * Oct-2003 : Added uart2 resource [FB]
 * Jan-2004 : Removed io map क्रम flash [FB]
 */

#समावेश <linux/init.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/kernel.h>
#समावेश <linux/tty.h>
#समावेश <linux/platक्रमm_data/sa11x0-serial.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/irq.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/leds.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/setup.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/flash.h>
#समावेश <यंत्र/mach/map.h>

#समावेश <mach/cerf.h>
#समावेश <linux/platक्रमm_data/mfd-mcp-sa11x0.h>
#समावेश <mach/irqs.h>
#समावेश "generic.h"

अटल काष्ठा resource cerfuart2_resources[] = अणु
	[0] = DEFINE_RES_MEM(0x80030000, SZ_64K),
पूर्ण;

अटल काष्ठा platक्रमm_device cerfuart2_device = अणु
	.name		= "sa11x0-uart",
	.id		= 2,
	.num_resources	= ARRAY_SIZE(cerfuart2_resources),
	.resource	= cerfuart2_resources,
पूर्ण;

/* Compact Flash */
अटल काष्ठा gpiod_lookup_table cerf_cf_gpio_table = अणु
	.dev_id = "sa11x0-pcmcia.1",
	.table = अणु
		GPIO_LOOKUP("gpio", 19, "bvd2", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio", 20, "bvd1", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio", 21, "reset", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio", 22, "ready", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio", 23, "detect", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

/* LEDs */
काष्ठा gpio_led cerf_gpio_leds[] = अणु
	अणु
		.name			= "cerf:d0",
		.शेष_trigger	= "heartbeat",
		.gpio			= 0,
	पूर्ण,
	अणु
		.name			= "cerf:d1",
		.शेष_trigger	= "cpu0",
		.gpio			= 1,
	पूर्ण,
	अणु
		.name			= "cerf:d2",
		.शेष_trigger	= "default-on",
		.gpio			= 2,
	पूर्ण,
	अणु
		.name			= "cerf:d3",
		.शेष_trigger	= "default-on",
		.gpio			= 3,
	पूर्ण,

पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data cerf_gpio_led_info = अणु
	.leds		= cerf_gpio_leds,
	.num_leds	= ARRAY_SIZE(cerf_gpio_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device *cerf_devices[] __initdata = अणु
	&cerfuart2_device,
पूर्ण;

#अगर_घोषित CONFIG_SA1100_CERF_FLASH_32MB
#  define CERF_FLASH_SIZE	0x02000000
#या_अगर defined CONFIG_SA1100_CERF_FLASH_16MB
#  define CERF_FLASH_SIZE	0x01000000
#या_अगर defined CONFIG_SA1100_CERF_FLASH_8MB
#  define CERF_FLASH_SIZE	0x00800000
#अन्यथा
#  error "Undefined flash size for CERF"
#पूर्ण_अगर

अटल काष्ठा mtd_partition cerf_partitions[] = अणु
	अणु
		.name		= "Bootloader",
		.size		= 0x00020000,
		.offset		= 0x00000000,
	पूर्ण, अणु
		.name		= "Params",
		.size		= 0x00040000,
		.offset		= 0x00020000,
	पूर्ण, अणु
		.name		= "Kernel",
		.size		= 0x00100000,
		.offset		= 0x00060000,
	पूर्ण, अणु
		.name		= "Filesystem",
		.size		= CERF_FLASH_SIZE-0x00160000,
		.offset		= 0x00160000,
	पूर्ण
पूर्ण;

अटल काष्ठा flash_platक्रमm_data cerf_flash_data = अणु
	.map_name	= "cfi_probe",
	.parts		= cerf_partitions,
	.nr_parts	= ARRAY_SIZE(cerf_partitions),
पूर्ण;

अटल काष्ठा resource cerf_flash_resource =
	DEFINE_RES_MEM(SA1100_CS0_PHYS, SZ_32M);

अटल व्योम __init cerf_init_irq(व्योम)
अणु
	sa1100_init_irq();
	irq_set_irq_type(CERF_ETH_IRQ, IRQ_TYPE_EDGE_RISING);
पूर्ण

अटल काष्ठा map_desc cerf_io_desc[] __initdata = अणु
  	अणु	/* Crystal Ethernet Chip */
		.भव	=  0xf0000000,
		.pfn		= __phys_to_pfn(0x08000000),
		.length		= 0x00100000,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;

अटल व्योम __init cerf_map_io(व्योम)
अणु
	sa1100_map_io();
	iotable_init(cerf_io_desc, ARRAY_SIZE(cerf_io_desc));

	sa1100_रेजिस्टर_uart(0, 3);
	sa1100_रेजिस्टर_uart(1, 2); /* disable this and the uart2 device क्रम sa1100_fir */
	sa1100_रेजिस्टर_uart(2, 1);
पूर्ण

अटल काष्ठा mcp_plat_data cerf_mcp_data = अणु
	.mccr0		= MCCR0_ADM,
	.sclk_rate	= 11981000,
पूर्ण;

अटल व्योम __init cerf_init(व्योम)
अणु
	sa11x0_ppc_configure_mcp();
	platक्रमm_add_devices(cerf_devices, ARRAY_SIZE(cerf_devices));
	gpio_led_रेजिस्टर_device(-1, &cerf_gpio_led_info);
	sa11x0_रेजिस्टर_mtd(&cerf_flash_data, &cerf_flash_resource, 1);
	sa11x0_रेजिस्टर_mcp(&cerf_mcp_data);
	sa11x0_रेजिस्टर_pcmcia(1, &cerf_cf_gpio_table);
पूर्ण

MACHINE_START(CERF, "Intrinsyc CerfBoard/CerfCube")
	/* Maपूर्णांकainer: support@पूर्णांकrinsyc.com */
	.map_io		= cerf_map_io,
	.nr_irqs	= SA1100_NR_IRQS,
	.init_irq	= cerf_init_irq,
	.init_समय	= sa1100_समयr_init,
	.init_machine	= cerf_init,
	.init_late	= sa11x0_init_late,
	.restart	= sa11x0_restart,
MACHINE_END
