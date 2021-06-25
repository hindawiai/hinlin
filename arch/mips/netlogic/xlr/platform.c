<शैली गुरु>
/*
 * Copyright 2011, Netlogic Microप्रणालीs.
 * Copyright 2004, Matt Porter <mporter@kernel.crashing.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/resource.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/i2c.h>
#समावेश <linux/usb/ehci_pdriver.h>
#समावेश <linux/usb/ohci_pdriver.h>

#समावेश <यंत्र/netlogic/haldefs.h>
#समावेश <यंत्र/netlogic/xlr/iomap.h>
#समावेश <यंत्र/netlogic/xlr/pic.h>
#समावेश <यंत्र/netlogic/xlr/xlr.h>

अटल अचिन्हित पूर्णांक nlm_xlr_uart_in(काष्ठा uart_port *p, पूर्णांक offset)
अणु
	uपूर्णांक64_t uartbase;
	अचिन्हित पूर्णांक value;

	/* sign extend to 64 bits, अगर needed */
	uartbase = (uपूर्णांक64_t)(दीर्घ)p->membase;
	value = nlm_पढ़ो_reg(uartbase, offset);

	/* See XLR/XLS errata */
	अगर (offset == UART_MSR)
		value ^= 0xF0;
	अन्यथा अगर (offset == UART_MCR)
		value ^= 0x3;

	वापस value;
पूर्ण

अटल व्योम nlm_xlr_uart_out(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	uपूर्णांक64_t uartbase;

	/* sign extend to 64 bits, अगर needed */
	uartbase = (uपूर्णांक64_t)(दीर्घ)p->membase;

	/* See XLR/XLS errata */
	अगर (offset == UART_MSR)
		value ^= 0xF0;
	अन्यथा अगर (offset == UART_MCR)
		value ^= 0x3;

	nlm_ग_लिखो_reg(uartbase, offset, value);
पूर्ण

#घोषणा PORT(_irq)					\
	अणु						\
		.irq		= _irq,			\
		.regshअगरt	= 2,			\
		.iotype		= UPIO_MEM32,		\
		.flags		= (UPF_SKIP_TEST |	\
			 UPF_FIXED_TYPE | UPF_BOOT_AUTOCONF),\
		.uartclk	= PIC_CLK_HZ,		\
		.type		= PORT_16550A,		\
		.serial_in	= nlm_xlr_uart_in,	\
		.serial_out	= nlm_xlr_uart_out,	\
	पूर्ण

अटल काष्ठा plat_serial8250_port xlr_uart_data[] = अणु
	PORT(PIC_UART_0_IRQ),
	PORT(PIC_UART_1_IRQ),
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device uart_device = अणु
	.name		= "serial8250",
	.id		= PLAT8250_DEV_PLATFORM,
	.dev = अणु
		.platक्रमm_data = xlr_uart_data,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init nlm_uart_init(व्योम)
अणु
	अचिन्हित दीर्घ uartbase;

	uartbase = (अचिन्हित दीर्घ)nlm_mmio_base(NETLOGIC_IO_UART_0_OFFSET);
	xlr_uart_data[0].membase = (व्योम __iomem *)uartbase;
	xlr_uart_data[0].mapbase = CPHYSADDR(uartbase);

	uartbase = (अचिन्हित दीर्घ)nlm_mmio_base(NETLOGIC_IO_UART_1_OFFSET);
	xlr_uart_data[1].membase = (व्योम __iomem *)uartbase;
	xlr_uart_data[1].mapbase = CPHYSADDR(uartbase);

	वापस platक्रमm_device_रेजिस्टर(&uart_device);
पूर्ण

arch_initcall(nlm_uart_init);

#अगर_घोषित CONFIG_USB
/* Platक्रमm USB devices, only on XLS chips */
अटल u64 xls_usb_dmamask = ~(u32)0;
#घोषणा USB_PLATFORM_DEV(n, i, irq)					\
	अणु								\
		.name		= n,					\
		.id		= i,					\
		.num_resources	= 2,					\
		.dev		= अणु					\
			.dma_mask	= &xls_usb_dmamask,		\
			.coherent_dma_mask = 0xffffffff,		\
		पूर्ण,							\
		.resource	= (काष्ठा resource[]) अणु			\
			अणु						\
				.flags = IORESOURCE_MEM,		\
			पूर्ण,						\
			अणु						\
				.start	= irq,				\
				.end	= irq,				\
				.flags = IORESOURCE_IRQ,		\
			पूर्ण,						\
		पूर्ण,							\
	पूर्ण

अटल काष्ठा usb_ehci_pdata xls_usb_ehci_pdata = अणु
	.caps_offset	= 0,
पूर्ण;

अटल काष्ठा usb_ohci_pdata xls_usb_ohci_pdata;

अटल काष्ठा platक्रमm_device xls_usb_ehci_device =
			 USB_PLATFORM_DEV("ehci-platform", 0, PIC_USB_IRQ);
अटल काष्ठा platक्रमm_device xls_usb_ohci_device_0 =
			 USB_PLATFORM_DEV("ohci-platform", 1, PIC_USB_IRQ);
अटल काष्ठा platक्रमm_device xls_usb_ohci_device_1 =
			 USB_PLATFORM_DEV("ohci-platform", 2, PIC_USB_IRQ);

अटल काष्ठा platक्रमm_device *xls_platक्रमm_devices[] = अणु
	&xls_usb_ehci_device,
	&xls_usb_ohci_device_0,
	&xls_usb_ohci_device_1,
पूर्ण;

पूर्णांक xls_platक्रमm_usb_init(व्योम)
अणु
	uपूर्णांक64_t usb_mmio, gpio_mmio;
	अचिन्हित दीर्घ memres;
	uपूर्णांक32_t val;

	अगर (!nlm_chip_is_xls())
		वापस 0;

	gpio_mmio = nlm_mmio_base(NETLOGIC_IO_GPIO_OFFSET);
	usb_mmio  = nlm_mmio_base(NETLOGIC_IO_USB_1_OFFSET);

	/* Clear Rogue Phy INTs */
	nlm_ग_लिखो_reg(usb_mmio, 49, 0x10000000);
	/* Enable all पूर्णांकerrupts */
	nlm_ग_लिखो_reg(usb_mmio, 50, 0x1f000000);

	/* Enable ports */
	nlm_ग_लिखो_reg(usb_mmio,	 1, 0x07000500);

	val = nlm_पढ़ो_reg(gpio_mmio, 21);
	अगर (((val >> 22) & 0x01) == 0) अणु
		pr_info("Detected USB Device mode - Not supported!\n");
		nlm_ग_लिखो_reg(usb_mmio,	 0, 0x01000000);
		वापस 0;
	पूर्ण

	pr_info("Detected USB Host mode - Adding XLS USB devices.\n");
	/* Clear reset, host mode */
	nlm_ग_लिखो_reg(usb_mmio,	 0, 0x02000000);

	/* Memory resource क्रम various XLS usb ports */
	usb_mmio = nlm_mmio_base(NETLOGIC_IO_USB_0_OFFSET);
	memres = CPHYSADDR((अचिन्हित दीर्घ)usb_mmio);
	xls_usb_ehci_device.resource[0].start = memres;
	xls_usb_ehci_device.resource[0].end = memres + 0x400 - 1;
	xls_usb_ehci_device.dev.platक्रमm_data = &xls_usb_ehci_pdata;

	memres += 0x400;
	xls_usb_ohci_device_0.resource[0].start = memres;
	xls_usb_ohci_device_0.resource[0].end = memres + 0x400 - 1;
	xls_usb_ohci_device_0.dev.platक्रमm_data = &xls_usb_ohci_pdata;

	memres += 0x400;
	xls_usb_ohci_device_1.resource[0].start = memres;
	xls_usb_ohci_device_1.resource[0].end = memres + 0x400 - 1;
	xls_usb_ohci_device_1.dev.platक्रमm_data = &xls_usb_ohci_pdata;

	वापस platक्रमm_add_devices(xls_platक्रमm_devices,
				ARRAY_SIZE(xls_platक्रमm_devices));
पूर्ण

arch_initcall(xls_platक्रमm_usb_init);
#पूर्ण_अगर

#अगर_घोषित CONFIG_I2C
अटल काष्ठा i2c_board_info nlm_i2c_board_info1[] __initdata = अणु
	/* All XLR boards have this RTC and Max6657 Temp Chip */
	[0] = अणु
		.type	= "ds1374",
		.addr	= 0x68
	पूर्ण,
	[1] = अणु
		.type	= "lm90",
		.addr	= 0x4c
	पूर्ण,
पूर्ण;

अटल काष्ठा resource i2c_resources[] = अणु
	[0] = अणु
		.start	= 0,	/* filled at init */
		.end	= 0,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device nlm_xlr_i2c_1 = अणु
	.name		= "xlr-i2cbus",
	.id		= 1,
	.num_resources	= 1,
	.resource	= i2c_resources,
पूर्ण;

अटल पूर्णांक __init nlm_i2c_init(व्योम)
अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक offset;

	/* I2C bus 0 करोes not have any useful devices, configure only bus 1 */
	offset = NETLOGIC_IO_I2C_1_OFFSET;
	nlm_xlr_i2c_1.resource[0].start = CPHYSADDR(nlm_mmio_base(offset));
	nlm_xlr_i2c_1.resource[0].end = nlm_xlr_i2c_1.resource[0].start + 0xfff;

	platक्रमm_device_रेजिस्टर(&nlm_xlr_i2c_1);

	err = i2c_रेजिस्टर_board_info(1, nlm_i2c_board_info1,
				ARRAY_SIZE(nlm_i2c_board_info1));
	अगर (err < 0)
		pr_err("nlm-i2c: cannot register board I2C devices\n");
	वापस err;
पूर्ण

arch_initcall(nlm_i2c_init);
#पूर्ण_अगर
