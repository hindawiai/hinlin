<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support क्रम Compaq iPAQ H3100 and H3600 handheld computers (common code)
 *
 * Copyright (c) 2000,1 Compaq Computer Corporation. (Author: Jamey Hicks)
 * Copyright (c) 2009 Dmitry Artamonow <mad_soft@inbox.ru>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/platक्रमm_data/gpio-htc-egpपन.स>
#समावेश <linux/platक्रमm_data/sa11x0-serial.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_core.h>

#समावेश <यंत्र/mach/flash.h>
#समावेश <यंत्र/mach/map.h>

#समावेश <mach/h3xxx.h>
#समावेश <mach/irqs.h>

#समावेश "generic.h"

/*
 * H3xxx flash support
 */
अटल काष्ठा mtd_partition h3xxx_partitions[] = अणु
	अणु
		.name		= "H3XXX boot firmware",
		.size		= 0x00040000,
		.offset		= 0,
		.mask_flags	= MTD_WRITEABLE,  /* क्रमce पढ़ो-only */
	पूर्ण, अणु
		.name		= "H3XXX rootfs",
		.size		= MTDPART_SIZ_FULL,
		.offset		= 0x00040000,
	पूर्ण
पूर्ण;

अटल व्योम h3xxx_set_vpp(पूर्णांक vpp)
अणु
	gpio_set_value(H3XXX_EGPIO_VPP_ON, vpp);
पूर्ण

अटल पूर्णांक h3xxx_flash_init(व्योम)
अणु
	पूर्णांक err = gpio_request(H3XXX_EGPIO_VPP_ON, "Flash Vpp");
	अगर (err) अणु
		pr_err("%s: can't request H3XXX_EGPIO_VPP_ON\n", __func__);
		वापस err;
	पूर्ण

	err = gpio_direction_output(H3XXX_EGPIO_VPP_ON, 0);
	अगर (err)
		gpio_मुक्त(H3XXX_EGPIO_VPP_ON);

	वापस err;
पूर्ण

अटल व्योम h3xxx_flash_निकास(व्योम)
अणु
	gpio_मुक्त(H3XXX_EGPIO_VPP_ON);
पूर्ण

अटल काष्ठा flash_platक्रमm_data h3xxx_flash_data = अणु
	.map_name	= "cfi_probe",
	.set_vpp	= h3xxx_set_vpp,
	.init		= h3xxx_flash_init,
	.निकास		= h3xxx_flash_निकास,
	.parts		= h3xxx_partitions,
	.nr_parts	= ARRAY_SIZE(h3xxx_partitions),
पूर्ण;

अटल काष्ठा resource h3xxx_flash_resource =
	DEFINE_RES_MEM(SA1100_CS0_PHYS, SZ_32M);


/*
 * H3xxx uart support
 */
अटल व्योम h3xxx_uart_pm(काष्ठा uart_port *port, u_पूर्णांक state, u_पूर्णांक oldstate)
अणु
	अगर (port->mapbase == _Ser3UTCR0) अणु
		अगर (!gpio_request(H3XXX_EGPIO_RS232_ON, "RS232 transceiver")) अणु
			gpio_direction_output(H3XXX_EGPIO_RS232_ON, !state);
			gpio_मुक्त(H3XXX_EGPIO_RS232_ON);
		पूर्ण अन्यथा अणु
			pr_err("%s: can't request H3XXX_EGPIO_RS232_ON\n",
				__func__);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Enable/Disable wake up events क्रम this serial port.
 * Obviously, we only support this on the normal COM port.
 */
अटल पूर्णांक h3xxx_uart_set_wake(काष्ठा uart_port *port, u_पूर्णांक enable)
अणु
	पूर्णांक err = -EINVAL;

	अगर (port->mapbase == _Ser3UTCR0) अणु
		अगर (enable)
			PWER |= PWER_GPIO23 | PWER_GPIO25; /* DCD and CTS */
		अन्यथा
			PWER &= ~(PWER_GPIO23 | PWER_GPIO25); /* DCD and CTS */
		err = 0;
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा sa1100_port_fns h3xxx_port_fns __initdata = अणु
	.pm		= h3xxx_uart_pm,
	.set_wake	= h3xxx_uart_set_wake,
पूर्ण;

अटल काष्ठा gpiod_lookup_table h3xxx_uart3_gpio_table = अणु
	.dev_id = "sa11x0-uart.3",
	.table = अणु
		GPIO_LOOKUP("gpio", H3XXX_GPIO_COM_DCD, "dcd", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio", H3XXX_GPIO_COM_CTS, "cts", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio", H3XXX_GPIO_COM_RTS, "rts", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

/*
 * EGPIO
 */

अटल काष्ठा resource egpio_resources[] = अणु
	[0] = DEFINE_RES_MEM(H3600_EGPIO_PHYS, 0x4),
पूर्ण;

अटल काष्ठा htc_egpio_chip egpio_chips[] = अणु
	[0] = अणु
		.reg_start	= 0,
		.gpio_base	= H3XXX_EGPIO_BASE,
		.num_gpios	= 16,
		.direction	= HTC_EGPIO_OUTPUT,
		.initial_values	= 0x0080, /* H3XXX_EGPIO_RS232_ON */
	पूर्ण,
पूर्ण;

अटल काष्ठा htc_egpio_platक्रमm_data egpio_info = अणु
	.reg_width	= 16,
	.bus_width	= 16,
	.chip		= egpio_chips,
	.num_chips	= ARRAY_SIZE(egpio_chips),
पूर्ण;

अटल काष्ठा platक्रमm_device h3xxx_egpio = अणु
	.name		= "htc-egpio",
	.id		= -1,
	.resource	= egpio_resources,
	.num_resources	= ARRAY_SIZE(egpio_resources),
	.dev		= अणु
		.platक्रमm_data = &egpio_info,
	पूर्ण,
पूर्ण;

/*
 * GPIO keys
 */

अटल काष्ठा gpio_keys_button h3xxx_button_table[] = अणु
	अणु
		.code		= KEY_POWER,
		.gpio		= H3XXX_GPIO_PWR_BUTTON,
		.desc		= "Power Button",
		.active_low	= 1,
		.type		= EV_KEY,
		.wakeup		= 1,
	पूर्ण, अणु
		.code		= KEY_ENTER,
		.gpio		= H3XXX_GPIO_ACTION_BUTTON,
		.active_low	= 1,
		.desc		= "Action button",
		.type		= EV_KEY,
		.wakeup		= 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data h3xxx_keys_data = अणु
	.buttons  = h3xxx_button_table,
	.nbuttons = ARRAY_SIZE(h3xxx_button_table),
पूर्ण;

अटल काष्ठा platक्रमm_device h3xxx_keys = अणु
	.name	= "gpio-keys",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data = &h3xxx_keys_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource h3xxx_micro_resources[] = अणु
	DEFINE_RES_MEM(0x80010000, SZ_4K),
	DEFINE_RES_MEM(0x80020000, SZ_4K),
	DEFINE_RES_IRQ(IRQ_Ser1UART),
पूर्ण;

काष्ठा platक्रमm_device h3xxx_micro_asic = अणु
	.name = "ipaq-h3xxx-micro",
	.id = -1,
	.resource = h3xxx_micro_resources,
	.num_resources = ARRAY_SIZE(h3xxx_micro_resources),
पूर्ण;

अटल काष्ठा platक्रमm_device *h3xxx_devices[] = अणु
	&h3xxx_egpio,
	&h3xxx_keys,
	&h3xxx_micro_asic,
पूर्ण;

अटल काष्ठा gpiod_lookup_table h3xxx_pcmcia_gpio_table = अणु
	.dev_id = "sa11x0-pcmcia",
	.table = अणु
		GPIO_LOOKUP("gpio", H3XXX_GPIO_PCMCIA_CD0,
			    "pcmcia0-detect", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio", H3XXX_GPIO_PCMCIA_IRQ0,
			    "pcmcia0-ready", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio", H3XXX_GPIO_PCMCIA_CD1,
			    "pcmcia1-detect", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio", H3XXX_GPIO_PCMCIA_IRQ1,
			    "pcmcia1-ready", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

व्योम __init h3xxx_mach_init(व्योम)
अणु
	gpiod_add_lookup_table(&h3xxx_pcmcia_gpio_table);
	gpiod_add_lookup_table(&h3xxx_uart3_gpio_table);
	sa1100_रेजिस्टर_uart_fns(&h3xxx_port_fns);
	sa11x0_रेजिस्टर_mtd(&h3xxx_flash_data, &h3xxx_flash_resource, 1);
	platक्रमm_add_devices(h3xxx_devices, ARRAY_SIZE(h3xxx_devices));
पूर्ण

अटल काष्ठा map_desc h3600_io_desc[] __initdata = अणु
	अणु	/* अटल memory bank 2  CS#2 */
		.भव	=  H3600_BANK_2_VIRT,
		.pfn		= __phys_to_pfn(SA1100_CS2_PHYS),
		.length		= 0x02800000,
		.type		= MT_DEVICE
	पूर्ण, अणु	/* अटल memory bank 4  CS#4 */
		.भव	=  H3600_BANK_4_VIRT,
		.pfn		= __phys_to_pfn(SA1100_CS4_PHYS),
		.length		= 0x00800000,
		.type		= MT_DEVICE
	पूर्ण, अणु	/* EGPIO 0		CS#5 */
		.भव	=  H3600_EGPIO_VIRT,
		.pfn		= __phys_to_pfn(H3600_EGPIO_PHYS),
		.length		= 0x01000000,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;

/*
 * Common map_io initialization
 */

व्योम __init h3xxx_map_io(व्योम)
अणु
	sa1100_map_io();
	iotable_init(h3600_io_desc, ARRAY_SIZE(h3600_io_desc));

	sa1100_रेजिस्टर_uart(0, 3); /* Common serial port */
//	sa1100_रेजिस्टर_uart(1, 1); /* Microcontroller on 3100/3600 */

	/* Ensure those pins are outमाला_दो and driving low  */
	PPDR |= PPC_TXD4 | PPC_SCLK | PPC_SFRM;
	PPSR &= ~(PPC_TXD4 | PPC_SCLK | PPC_SFRM);

	/* Configure suspend conditions */
	PGSR = 0;
	PCFR = PCFR_OPDE;
	PSDR = 0;

	GPCR = 0x0fffffff;	/* All outमाला_दो are set low by शेष */
	GPDR = 0;		/* Configure all GPIOs as input */
पूर्ण

