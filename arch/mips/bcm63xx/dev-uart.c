<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <bcm63xx_cpu.h>

अटल काष्ठा resource uart0_resources[] = अणु
	अणु
		/* start & end filled at runसमय */
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		/* start filled at runसमय */
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource uart1_resources[] = अणु
	अणु
		/* start & end filled at runसमय */
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		/* start filled at runसमय */
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device bcm63xx_uart_devices[] = अणु
	अणु
		.name		= "bcm63xx_uart",
		.id		= 0,
		.num_resources	= ARRAY_SIZE(uart0_resources),
		.resource	= uart0_resources,
	पूर्ण,

	अणु
		.name		= "bcm63xx_uart",
		.id		= 1,
		.num_resources	= ARRAY_SIZE(uart1_resources),
		.resource	= uart1_resources,
	पूर्ण
पूर्ण;

पूर्णांक __init bcm63xx_uart_रेजिस्टर(अचिन्हित पूर्णांक id)
अणु
	अगर (id >= ARRAY_SIZE(bcm63xx_uart_devices))
		वापस -ENODEV;

	अगर (id == 1 && (!BCMCPU_IS_3368() && !BCMCPU_IS_6358() &&
		!BCMCPU_IS_6368()))
		वापस -ENODEV;

	अगर (id == 0) अणु
		uart0_resources[0].start = bcm63xx_regset_address(RSET_UART0);
		uart0_resources[0].end = uart0_resources[0].start +
			RSET_UART_SIZE - 1;
		uart0_resources[1].start = bcm63xx_get_irq_number(IRQ_UART0);
	पूर्ण

	अगर (id == 1) अणु
		uart1_resources[0].start = bcm63xx_regset_address(RSET_UART1);
		uart1_resources[0].end = uart1_resources[0].start +
			RSET_UART_SIZE - 1;
		uart1_resources[1].start = bcm63xx_get_irq_number(IRQ_UART1);
	पूर्ण

	वापस platक्रमm_device_रेजिस्टर(&bcm63xx_uart_devices[id]);
पूर्ण
