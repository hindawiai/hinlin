<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap1/serial.c
 *
 * OMAP1 serial support.
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/delay.h>
#समावेश <linux/serial.h>
#समावेश <linux/tty.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/mach-types.h>

#समावेश <mach/mux.h>

#समावेश "pm.h"
#समावेश "soc.h"

अटल काष्ठा clk * uart1_ck;
अटल काष्ठा clk * uart2_ck;
अटल काष्ठा clk * uart3_ck;

अटल अंतरभूत अचिन्हित पूर्णांक omap_serial_in(काष्ठा plat_serial8250_port *up,
					  पूर्णांक offset)
अणु
	offset <<= up->regshअगरt;
	वापस (अचिन्हित पूर्णांक)__raw_पढ़ोb(up->membase + offset);
पूर्ण

अटल अंतरभूत व्योम omap_serial_outp(काष्ठा plat_serial8250_port *p, पूर्णांक offset,
				    पूर्णांक value)
अणु
	offset <<= p->regshअगरt;
	__raw_ग_लिखोb(value, p->membase + offset);
पूर्ण

/*
 * Internal UARTs need to be initialized क्रम the 8250 स्वतःconfig to work
 * properly. Note that the TX watermark initialization may not be needed
 * once the 8250.c watermark handling code is merged.
 */
अटल व्योम __init omap_serial_reset(काष्ठा plat_serial8250_port *p)
अणु
	omap_serial_outp(p, UART_OMAP_MDR1,
			UART_OMAP_MDR1_DISABLE);	/* disable UART */
	omap_serial_outp(p, UART_OMAP_SCR, 0x08);	/* TX watermark */
	omap_serial_outp(p, UART_OMAP_MDR1,
			UART_OMAP_MDR1_16X_MODE);	/* enable UART */

	अगर (!cpu_is_omap15xx()) अणु
		omap_serial_outp(p, UART_OMAP_SYSC, 0x01);
		जबतक (!(omap_serial_in(p, UART_OMAP_SYSC) & 0x01));
	पूर्ण
पूर्ण

अटल काष्ठा plat_serial8250_port serial_platक्रमm_data[] = अणु
	अणु
		.mapbase	= OMAP1_UART1_BASE,
		.irq		= INT_UART1,
		.flags		= UPF_BOOT_AUTOCONF,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
		.uartclk	= OMAP16XX_BASE_BAUD * 16,
	पूर्ण,
	अणु
		.mapbase	= OMAP1_UART2_BASE,
		.irq		= INT_UART2,
		.flags		= UPF_BOOT_AUTOCONF,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
		.uartclk	= OMAP16XX_BASE_BAUD * 16,
	पूर्ण,
	अणु
		.mapbase	= OMAP1_UART3_BASE,
		.irq		= INT_UART3,
		.flags		= UPF_BOOT_AUTOCONF,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
		.uartclk	= OMAP16XX_BASE_BAUD * 16,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device serial_device = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev			= अणु
		.platक्रमm_data	= serial_platक्रमm_data,
	पूर्ण,
पूर्ण;

/*
 * Note that on Innovator-1510 UART2 pins conflict with USB2.
 * By शेष UART2 करोes not work on Innovator-1510 अगर you have
 * USB OHCI enabled. To use UART2, you must disable USB2 first.
 */
व्योम __init omap_serial_init(व्योम)
अणु
	पूर्णांक i;

	अगर (cpu_is_omap7xx()) अणु
		serial_platक्रमm_data[0].regshअगरt = 0;
		serial_platक्रमm_data[1].regshअगरt = 0;
		serial_platक्रमm_data[0].irq = INT_7XX_UART_MODEM_1;
		serial_platक्रमm_data[1].irq = INT_7XX_UART_MODEM_IRDA_2;
	पूर्ण

	अगर (cpu_is_omap15xx()) अणु
		serial_platक्रमm_data[0].uartclk = OMAP1510_BASE_BAUD * 16;
		serial_platक्रमm_data[1].uartclk = OMAP1510_BASE_BAUD * 16;
		serial_platक्रमm_data[2].uartclk = OMAP1510_BASE_BAUD * 16;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(serial_platक्रमm_data) - 1; i++) अणु

		/* Don't look at UARTs higher than 2 क्रम omap7xx */
		अगर (cpu_is_omap7xx() && i > 1) अणु
			serial_platक्रमm_data[i].membase = शून्य;
			serial_platक्रमm_data[i].mapbase = 0;
			जारी;
		पूर्ण

		/* Static mapping, never released */
		serial_platक्रमm_data[i].membase =
			ioremap(serial_platक्रमm_data[i].mapbase, SZ_2K);
		अगर (!serial_platक्रमm_data[i].membase) अणु
			prपूर्णांकk(KERN_ERR "Could not ioremap uart%i\n", i);
			जारी;
		पूर्ण
		चयन (i) अणु
		हाल 0:
			uart1_ck = clk_get(शून्य, "uart1_ck");
			अगर (IS_ERR(uart1_ck))
				prपूर्णांकk("Could not get uart1_ck\n");
			अन्यथा अणु
				clk_enable(uart1_ck);
				अगर (cpu_is_omap15xx())
					clk_set_rate(uart1_ck, 12000000);
			पूर्ण
			अवरोध;
		हाल 1:
			uart2_ck = clk_get(शून्य, "uart2_ck");
			अगर (IS_ERR(uart2_ck))
				prपूर्णांकk("Could not get uart2_ck\n");
			अन्यथा अणु
				clk_enable(uart2_ck);
				अगर (cpu_is_omap15xx())
					clk_set_rate(uart2_ck, 12000000);
				अन्यथा
					clk_set_rate(uart2_ck, 48000000);
			पूर्ण
			अवरोध;
		हाल 2:
			uart3_ck = clk_get(शून्य, "uart3_ck");
			अगर (IS_ERR(uart3_ck))
				prपूर्णांकk("Could not get uart3_ck\n");
			अन्यथा अणु
				clk_enable(uart3_ck);
				अगर (cpu_is_omap15xx())
					clk_set_rate(uart3_ck, 12000000);
			पूर्ण
			अवरोध;
		पूर्ण
		omap_serial_reset(&serial_platक्रमm_data[i]);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_OMAP_SERIAL_WAKE

अटल irqवापस_t omap_serial_wake_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	/* Need to करो something with serial port right after wake-up? */
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Reroutes serial RX lines to GPIO lines क्रम the duration of
 * sleep to allow waking up the device from serial port even
 * in deep sleep.
 */
व्योम omap_serial_wake_trigger(पूर्णांक enable)
अणु
	अगर (!cpu_is_omap16xx())
		वापस;

	अगर (uart1_ck != शून्य) अणु
		अगर (enable)
			omap_cfg_reg(V14_16XX_GPIO37);
		अन्यथा
			omap_cfg_reg(V14_16XX_UART1_RX);
	पूर्ण
	अगर (uart2_ck != शून्य) अणु
		अगर (enable)
			omap_cfg_reg(R9_16XX_GPIO18);
		अन्यथा
			omap_cfg_reg(R9_16XX_UART2_RX);
	पूर्ण
	अगर (uart3_ck != शून्य) अणु
		अगर (enable)
			omap_cfg_reg(L14_16XX_GPIO49);
		अन्यथा
			omap_cfg_reg(L14_16XX_UART3_RX);
	पूर्ण
पूर्ण

अटल व्योम __init omap_serial_set_port_wakeup(पूर्णांक gpio_nr)
अणु
	पूर्णांक ret;

	ret = gpio_request(gpio_nr, "UART wake");
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "Could not request UART wake GPIO: %i\n",
		       gpio_nr);
		वापस;
	पूर्ण
	gpio_direction_input(gpio_nr);
	ret = request_irq(gpio_to_irq(gpio_nr), &omap_serial_wake_पूर्णांकerrupt,
			  IRQF_TRIGGER_RISING, "serial wakeup", शून्य);
	अगर (ret) अणु
		gpio_मुक्त(gpio_nr);
		prपूर्णांकk(KERN_ERR "No interrupt for UART wake GPIO: %i\n",
		       gpio_nr);
		वापस;
	पूर्ण
	enable_irq_wake(gpio_to_irq(gpio_nr));
पूर्ण

पूर्णांक __init omap_serial_wakeup_init(व्योम)
अणु
	अगर (!cpu_is_omap16xx())
		वापस 0;

	अगर (uart1_ck != शून्य)
		omap_serial_set_port_wakeup(37);
	अगर (uart2_ck != शून्य)
		omap_serial_set_port_wakeup(18);
	अगर (uart3_ck != शून्य)
		omap_serial_set_port_wakeup(49);

	वापस 0;
पूर्ण

#पूर्ण_अगर	/* CONFIG_OMAP_SERIAL_WAKE */

अटल पूर्णांक __init omap_init(व्योम)
अणु
	अगर (!cpu_class_is_omap1())
		वापस -ENODEV;

	वापस platक्रमm_device_रेजिस्टर(&serial_device);
पूर्ण
arch_initcall(omap_init);
