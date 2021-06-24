<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/arm/mach-sa1100/simpad.c
 */

#समावेश <linux/module.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/tty.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/pm.h>
#समावेश <linux/platक्रमm_data/sa11x0-serial.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/ucb1x00.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpio/driver.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/irq.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/flash.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <linux/platक्रमm_data/mfd-mcp-sa11x0.h>
#समावेश <mach/simpad.h>
#समावेश <mach/irqs.h>

#समावेश <linux/serial_core.h>
#समावेश <linux/ioport.h>
#समावेश <linux/input.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/leds.h>
#समावेश <linux/platक्रमm_data/i2c-gpपन.स>

#समावेश "generic.h"

/*
 * CS3 support
 */

अटल दीर्घ cs3_shaकरोw;
अटल spinlock_t cs3_lock;
अटल काष्ठा gpio_chip cs3_gpio;

दीर्घ simpad_get_cs3_ro(व्योम)
अणु
	वापस पढ़ोl(CS3_BASE);
पूर्ण
EXPORT_SYMBOL(simpad_get_cs3_ro);

दीर्घ simpad_get_cs3_shaकरोw(व्योम)
अणु
	वापस cs3_shaकरोw;
पूर्ण
EXPORT_SYMBOL(simpad_get_cs3_shaकरोw);

अटल व्योम __simpad_ग_लिखो_cs3(व्योम)
अणु
	ग_लिखोl(cs3_shaकरोw, CS3_BASE);
पूर्ण

व्योम simpad_set_cs3_bit(पूर्णांक value)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cs3_lock, flags);
	cs3_shaकरोw |= value;
	__simpad_ग_लिखो_cs3();
	spin_unlock_irqrestore(&cs3_lock, flags);
पूर्ण
EXPORT_SYMBOL(simpad_set_cs3_bit);

व्योम simpad_clear_cs3_bit(पूर्णांक value)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cs3_lock, flags);
	cs3_shaकरोw &= ~value;
	__simpad_ग_लिखो_cs3();
	spin_unlock_irqrestore(&cs3_lock, flags);
पूर्ण
EXPORT_SYMBOL(simpad_clear_cs3_bit);

अटल व्योम cs3_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	अगर (offset > 15)
		वापस;
	अगर (value)
		simpad_set_cs3_bit(1 << offset);
	अन्यथा
		simpad_clear_cs3_bit(1 << offset);
पूर्ण;

अटल पूर्णांक cs3_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	अगर (offset > 15)
		वापस !!(simpad_get_cs3_ro() & (1 << (offset - 16)));
	वापस !!(simpad_get_cs3_shaकरोw() & (1 << offset));
पूर्ण;

अटल पूर्णांक cs3_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	अगर (offset > 15)
		वापस 0;
	वापस -EINVAL;
पूर्ण;

अटल पूर्णांक cs3_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित offset,
	पूर्णांक value)
अणु
	अगर (offset > 15)
		वापस -EINVAL;
	cs3_gpio_set(chip, offset, value);
	वापस 0;
पूर्ण;

अटल काष्ठा map_desc simpad_io_desc[] __initdata = अणु
	अणु	/* MQ200 */
		.भव	=  0xf2800000,
		.pfn		= __phys_to_pfn(0x4b800000),
		.length		= 0x00800000,
		.type		= MT_DEVICE
	पूर्ण, अणु	/* Simpad CS3 */
		.भव	= (अचिन्हित दीर्घ)CS3_BASE,
		.pfn		= __phys_to_pfn(SA1100_CS3_PHYS),
		.length		= 0x00100000,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;


अटल व्योम simpad_uart_pm(काष्ठा uart_port *port, u_पूर्णांक state, u_पूर्णांक oldstate)
अणु
	अगर (port->mapbase == (u_पूर्णांक)&Ser1UTCR0) अणु
		अगर (state)
		अणु
			simpad_clear_cs3_bit(RS232_ON);
			simpad_clear_cs3_bit(DECT_POWER_ON);
		पूर्णअन्यथा
		अणु
			simpad_set_cs3_bit(RS232_ON);
			simpad_set_cs3_bit(DECT_POWER_ON);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा sa1100_port_fns simpad_port_fns __initdata = अणु
	.pm	   = simpad_uart_pm,
पूर्ण;


अटल काष्ठा mtd_partition simpad_partitions[] = अणु
	अणु
		.name       = "SIMpad boot firmware",
		.size       = 0x00080000,
		.offset     = 0,
		.mask_flags = MTD_WRITEABLE,
	पूर्ण, अणु
		.name       = "SIMpad kernel",
		.size       = 0x0010000,
		.offset     = MTDPART_OFS_APPEND,
	पूर्ण, अणु
		.name       = "SIMpad root jffs2",
		.size       = MTDPART_SIZ_FULL,
		.offset     = MTDPART_OFS_APPEND,
	पूर्ण
पूर्ण;

अटल काष्ठा flash_platक्रमm_data simpad_flash_data = अणु
	.map_name    = "cfi_probe",
	.parts       = simpad_partitions,
	.nr_parts    = ARRAY_SIZE(simpad_partitions),
पूर्ण;


अटल काष्ठा resource simpad_flash_resources [] = अणु
	DEFINE_RES_MEM(SA1100_CS0_PHYS, SZ_16M),
	DEFINE_RES_MEM(SA1100_CS1_PHYS, SZ_16M),
पूर्ण;

अटल काष्ठा ucb1x00_plat_data simpad_ucb1x00_data = अणु
	.gpio_base	= SIMPAD_UCB1X00_GPIO_BASE,
पूर्ण;

अटल काष्ठा mcp_plat_data simpad_mcp_data = अणु
	.mccr0		= MCCR0_ADM,
	.sclk_rate	= 11981000,
	.codec_pdata	= &simpad_ucb1x00_data,
पूर्ण;



अटल व्योम __init simpad_map_io(व्योम)
अणु
	sa1100_map_io();

	iotable_init(simpad_io_desc, ARRAY_SIZE(simpad_io_desc));

	/* Initialize CS3 */
	cs3_shaकरोw = (EN1 | EN0 | LED2_ON | DISPLAY_ON |
		RS232_ON | ENABLE_5V | RESET_SIMCARD | DECT_POWER_ON);
	__simpad_ग_लिखो_cs3(); /* Spinlocks not yet initialized */

        sa1100_रेजिस्टर_uart_fns(&simpad_port_fns);
	sa1100_रेजिस्टर_uart(0, 3);  /* serial पूर्णांकerface */
	sa1100_रेजिस्टर_uart(1, 1);  /* DECT             */

	// Reassign UART 1 pins
	GAFR |= GPIO_UART_TXD | GPIO_UART_RXD;
	GPDR |= GPIO_UART_TXD | GPIO_LDD13 | GPIO_LDD15;
	GPDR &= ~GPIO_UART_RXD;
	PPAR |= PPAR_UPR;

	/*
	 * Set up रेजिस्टरs क्रम sleep mode.
	 */


	PWER = PWER_GPIO0| PWER_RTC;
	PGSR = 0x818;
	PCFR = 0;
	PSDR = 0;

पूर्ण

अटल व्योम simpad_घातer_off(व्योम)
अणु
	local_irq_disable();
	cs3_shaकरोw = SD_MEDIAQ;
	__simpad_ग_लिखो_cs3(); /* Bypass spinlock here */

	/* disable पूर्णांकernal oscillator, भग्न CS lines */
	PCFR = (PCFR_OPDE | PCFR_FP | PCFR_FS);
	/* enable wake-up on GPIO0 */
	PWER = GFER = GRER = PWER_GPIO0;
	/*
	 * set scratchpad to zero, just in हाल it is used as a
	 * restart address by the bootloader.
	 */
	PSPR = 0;
	PGSR = 0;
	/* enter sleep mode */
	PMCR = PMCR_SF;
	जबतक(1);

	local_irq_enable(); /* we won't ever call it */


पूर्ण

/*
 * gpio_keys
*/

अटल काष्ठा gpio_keys_button simpad_button_table[] = अणु
	अणु KEY_POWER, IRQ_GPIO_POWER_BUTTON, 1, "power button" पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data simpad_keys_data = अणु
	.buttons = simpad_button_table,
	.nbuttons = ARRAY_SIZE(simpad_button_table),
पूर्ण;

अटल काष्ठा platक्रमm_device simpad_keys = अणु
	.name = "gpio-keys",
	.dev = अणु
		.platक्रमm_data = &simpad_keys_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_button simpad_polled_button_table[] = अणु
	अणु KEY_PROG1, SIMPAD_UCB1X00_GPIO_PROG1, 1, "prog1 button" पूर्ण,
	अणु KEY_PROG2, SIMPAD_UCB1X00_GPIO_PROG2, 1, "prog2 button" पूर्ण,
	अणु KEY_UP,    SIMPAD_UCB1X00_GPIO_UP,    1, "up button" पूर्ण,
	अणु KEY_DOWN,  SIMPAD_UCB1X00_GPIO_DOWN,  1, "down button" पूर्ण,
	अणु KEY_LEFT,  SIMPAD_UCB1X00_GPIO_LEFT,  1, "left button" पूर्ण,
	अणु KEY_RIGHT, SIMPAD_UCB1X00_GPIO_RIGHT, 1, "right button" पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data simpad_polled_keys_data = अणु
	.buttons = simpad_polled_button_table,
	.nbuttons = ARRAY_SIZE(simpad_polled_button_table),
	.poll_पूर्णांकerval = 50,
पूर्ण;

अटल काष्ठा platक्रमm_device simpad_polled_keys = अणु
	.name = "gpio-keys-polled",
	.dev = अणु
		.platक्रमm_data = &simpad_polled_keys_data,
	पूर्ण,
पूर्ण;

/*
 * GPIO LEDs
 */

अटल काष्ठा gpio_led simpad_leds[] = अणु
	अणु
		.name = "simpad:power",
		.gpio = SIMPAD_CS3_LED2_ON,
		.active_low = 0,
		.शेष_trigger = "default-on",
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data simpad_led_data = अणु
	.num_leds = ARRAY_SIZE(simpad_leds),
	.leds = simpad_leds,
पूर्ण;

अटल काष्ठा platक्रमm_device simpad_gpio_leds = अणु
	.name = "leds-gpio",
	.id = 0,
	.dev = अणु
		.platक्रमm_data = &simpad_led_data,
	पूर्ण,
पूर्ण;

/*
 * i2c
 */
अटल काष्ठा gpiod_lookup_table simpad_i2c_gpiod_table = अणु
	.dev_id = "i2c-gpio.0",
	.table = अणु
		GPIO_LOOKUP_IDX("gpio", 21, शून्य, 0,
				GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
		GPIO_LOOKUP_IDX("gpio", 25, शून्य, 1,
				GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
	पूर्ण,
पूर्ण;

अटल काष्ठा i2c_gpio_platक्रमm_data simpad_i2c_data = अणु
	.udelay = 10,
	.समयout = HZ,
पूर्ण;

अटल काष्ठा platक्रमm_device simpad_i2c = अणु
	.name = "i2c-gpio",
	.id = 0,
	.dev = अणु
		.platक्रमm_data = &simpad_i2c_data,
	पूर्ण,
पूर्ण;

/*
 * MediaQ Video Device
 */
अटल काष्ठा platक्रमm_device simpad_mq200fb = अणु
	.name = "simpad-mq200",
	.id   = 0,
पूर्ण;

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&simpad_keys,
	&simpad_polled_keys,
	&simpad_mq200fb,
	&simpad_gpio_leds,
	&simpad_i2c,
पूर्ण;

/* Compact Flash */
अटल काष्ठा gpiod_lookup_table simpad_cf_gpio_table = अणु
	.dev_id = "sa11x0-pcmcia",
	.table = अणु
		GPIO_LOOKUP("gpio", GPIO_CF_IRQ, "cf-ready", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio", GPIO_CF_CD, "cf-detect", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;


अटल पूर्णांक __init simpad_init(व्योम)
अणु
	पूर्णांक ret;

	spin_lock_init(&cs3_lock);

	cs3_gpio.label = "simpad_cs3";
	cs3_gpio.base = SIMPAD_CS3_GPIO_BASE;
	cs3_gpio.ngpio = 24;
	cs3_gpio.set = cs3_gpio_set;
	cs3_gpio.get = cs3_gpio_get;
	cs3_gpio.direction_input = cs3_gpio_direction_input;
	cs3_gpio.direction_output = cs3_gpio_direction_output;
	ret = gpiochip_add_data(&cs3_gpio, शून्य);
	अगर (ret)
		prपूर्णांकk(KERN_WARNING "simpad: Unable to register cs3 GPIO device");

	pm_घातer_off = simpad_घातer_off;

	sa11x0_रेजिस्टर_pcmcia(-1, &simpad_cf_gpio_table);
	sa11x0_ppc_configure_mcp();
	sa11x0_रेजिस्टर_mtd(&simpad_flash_data, simpad_flash_resources,
			      ARRAY_SIZE(simpad_flash_resources));
	sa11x0_रेजिस्टर_mcp(&simpad_mcp_data);

	gpiod_add_lookup_table(&simpad_i2c_gpiod_table);
	ret = platक्रमm_add_devices(devices, ARRAY_SIZE(devices));
	अगर(ret)
		prपूर्णांकk(KERN_WARNING "simpad: Unable to register mq200 framebuffer device");

	वापस 0;
पूर्ण

arch_initcall(simpad_init);


MACHINE_START(SIMPAD, "Simpad")
	/* Maपूर्णांकainer: Holger Freyther */
	.atag_offset	= 0x100,
	.map_io		= simpad_map_io,
	.nr_irqs	= SA1100_NR_IRQS,
	.init_irq	= sa1100_init_irq,
	.init_late	= sa11x0_init_late,
	.init_समय	= sa1100_समयr_init,
	.restart	= sa11x0_restart,
MACHINE_END
