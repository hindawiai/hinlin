<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Goramo MultiLink router platक्रमm code
 * Copyright (C) 2006-2009 Krzysztof Halasa <khc@pm.waw.pl>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/hdlc.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_data/wan_ixp4xx_hss.h>
#समावेश <linux/serial_8250.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/flash.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश <यंत्र/प्रणाली_info.h>

#समावेश "irqs.h"

#घोषणा SLOT_ETHA		0x0B	/* IDSEL = AD21 */
#घोषणा SLOT_ETHB		0x0C	/* IDSEL = AD20 */
#घोषणा SLOT_MPCI		0x0D	/* IDSEL = AD19 */
#घोषणा SLOT_NEC		0x0E	/* IDSEL = AD18 */

/* GPIO lines */
#घोषणा GPIO_SCL		0
#घोषणा GPIO_SDA		1
#घोषणा GPIO_STR		2
#घोषणा GPIO_IRQ_NEC		3
#घोषणा GPIO_IRQ_ETHA		4
#घोषणा GPIO_IRQ_ETHB		5
#घोषणा GPIO_HSS0_DCD_N		6
#घोषणा GPIO_HSS1_DCD_N		7
#घोषणा GPIO_UART0_DCD		8
#घोषणा GPIO_UART1_DCD		9
#घोषणा GPIO_HSS0_CTS_N		10
#घोषणा GPIO_HSS1_CTS_N		11
#घोषणा GPIO_IRQ_MPCI		12
#घोषणा GPIO_HSS1_RTS_N		13
#घोषणा GPIO_HSS0_RTS_N		14
/* GPIO15 is not connected */

/* Control outमाला_दो from 74HC4094 */
#घोषणा CONTROL_HSS0_CLK_INT	0
#घोषणा CONTROL_HSS1_CLK_INT	1
#घोषणा CONTROL_HSS0_DTR_N	2
#घोषणा CONTROL_HSS1_DTR_N	3
#घोषणा CONTROL_EXT		4
#घोषणा CONTROL_AUTO_RESET	5
#घोषणा CONTROL_PCI_RESET_N	6
#घोषणा CONTROL_EEPROM_WC_N	7

/* offsets from start of flash ROM = 0x50000000 */
#घोषणा CFG_ETH0_ADDRESS	0x40 /* 6 bytes */
#घोषणा CFG_ETH1_ADDRESS	0x46 /* 6 bytes */
#घोषणा CFG_REV			0x4C /* u32 */
#घोषणा CFG_SDRAM_SIZE		0x50 /* u32 */
#घोषणा CFG_SDRAM_CONF		0x54 /* u32 */
#घोषणा CFG_SDRAM_MODE		0x58 /* u32 */
#घोषणा CFG_SDRAM_REFRESH	0x5C /* u32 */

#घोषणा CFG_HW_BITS		0x60 /* u32 */
#घोषणा  CFG_HW_USB_PORTS	0x00000007 /* 0 = no NEC chip, 1-5 = ports # */
#घोषणा  CFG_HW_HAS_PCI_SLOT	0x00000008
#घोषणा  CFG_HW_HAS_ETH0	0x00000010
#घोषणा  CFG_HW_HAS_ETH1	0x00000020
#घोषणा  CFG_HW_HAS_HSS0	0x00000040
#घोषणा  CFG_HW_HAS_HSS1	0x00000080
#घोषणा  CFG_HW_HAS_UART0	0x00000100
#घोषणा  CFG_HW_HAS_UART1	0x00000200
#घोषणा  CFG_HW_HAS_EEPROM	0x00000400

#घोषणा FLASH_CMD_READ_ARRAY	0xFF
#घोषणा FLASH_CMD_READ_ID	0x90
#घोषणा FLASH_SER_OFF		0x102 /* 0x81 in 16-bit mode */

अटल u32 hw_bits = 0xFFFFFFFD;    /* assume all hardware present */;
अटल u8 control_value;

/*
 * FIXME: this is reimplementing I2C bit-bangining. Move this
 * over to using driver/i2c/busses/i2c-gpio.c like all other boards
 * and रेजिस्टर proper I2C device(s) on the bus क्रम this. (See
 * other IXP4xx boards क्रम examples.)
 */
अटल व्योम set_scl(u8 value)
अणु
	gpio_set_value(GPIO_SCL, !!value);
	udelay(3);
पूर्ण

अटल व्योम set_sda(u8 value)
अणु
	gpio_set_value(GPIO_SDA, !!value);
	udelay(3);
पूर्ण

अटल व्योम set_str(u8 value)
अणु
	gpio_set_value(GPIO_STR, !!value);
	udelay(3);
पूर्ण

अटल अंतरभूत व्योम set_control(पूर्णांक line, पूर्णांक value)
अणु
	अगर (value)
		control_value |=  (1 << line);
	अन्यथा
		control_value &= ~(1 << line);
पूर्ण


अटल व्योम output_control(व्योम)
अणु
	पूर्णांक i;

	gpio_direction_output(GPIO_SCL, 1);
	gpio_direction_output(GPIO_SDA, 1);

	क्रम (i = 0; i < 8; i++) अणु
		set_scl(0);
		set_sda(control_value & (0x80 >> i)); /* MSB first */
		set_scl(1);	/* active edge */
	पूर्ण

	set_str(1);
	set_str(0);

	set_scl(0);
	set_sda(1);		/* Be पढ़ोy क्रम START */
	set_scl(1);
पूर्ण


अटल व्योम (*set_carrier_cb_tab[2])(व्योम *pdev, पूर्णांक carrier);

अटल पूर्णांक hss_set_घड़ी(पूर्णांक port, अचिन्हित पूर्णांक घड़ी_प्रकारype)
अणु
	पूर्णांक ctrl_पूर्णांक = port ? CONTROL_HSS1_CLK_INT : CONTROL_HSS0_CLK_INT;

	चयन (घड़ी_प्रकारype) अणु
	हाल CLOCK_DEFAULT:
	हाल CLOCK_EXT:
		set_control(ctrl_पूर्णांक, 0);
		output_control();
		वापस CLOCK_EXT;

	हाल CLOCK_INT:
		set_control(ctrl_पूर्णांक, 1);
		output_control();
		वापस CLOCK_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल irqवापस_t hss_dcd_irq(पूर्णांक irq, व्योम *pdev)
अणु
	पूर्णांक port = (irq == IXP4XX_GPIO_IRQ(GPIO_HSS1_DCD_N));
	पूर्णांक i = gpio_get_value(port ? GPIO_HSS1_DCD_N : GPIO_HSS0_DCD_N);
	set_carrier_cb_tab[port](pdev, !i);
	वापस IRQ_HANDLED;
पूर्ण


अटल पूर्णांक hss_खोलो(पूर्णांक port, व्योम *pdev,
		    व्योम (*set_carrier_cb)(व्योम *pdev, पूर्णांक carrier))
अणु
	पूर्णांक i, irq;

	अगर (!port)
		irq = IXP4XX_GPIO_IRQ(GPIO_HSS0_DCD_N);
	अन्यथा
		irq = IXP4XX_GPIO_IRQ(GPIO_HSS1_DCD_N);

	i = gpio_get_value(port ? GPIO_HSS1_DCD_N : GPIO_HSS0_DCD_N);
	set_carrier_cb(pdev, !i);

	set_carrier_cb_tab[!!port] = set_carrier_cb;

	अगर ((i = request_irq(irq, hss_dcd_irq, 0, "IXP4xx HSS", pdev)) != 0) अणु
		prपूर्णांकk(KERN_ERR "ixp4xx_hss: failed to request IRQ%i (%i)\n",
		       irq, i);
		वापस i;
	पूर्ण

	set_control(port ? CONTROL_HSS1_DTR_N : CONTROL_HSS0_DTR_N, 0);
	output_control();
	gpio_set_value(port ? GPIO_HSS1_RTS_N : GPIO_HSS0_RTS_N, 0);
	वापस 0;
पूर्ण

अटल व्योम hss_बंद(पूर्णांक port, व्योम *pdev)
अणु
	मुक्त_irq(port ? IXP4XX_GPIO_IRQ(GPIO_HSS1_DCD_N) :
		 IXP4XX_GPIO_IRQ(GPIO_HSS0_DCD_N), pdev);
	set_carrier_cb_tab[!!port] = शून्य; /* catch bugs */

	set_control(port ? CONTROL_HSS1_DTR_N : CONTROL_HSS0_DTR_N, 1);
	output_control();
	gpio_set_value(port ? GPIO_HSS1_RTS_N : GPIO_HSS0_RTS_N, 1);
पूर्ण


/* Flash memory */
अटल काष्ठा flash_platक्रमm_data flash_data = अणु
	.map_name	= "cfi_probe",
	.width		= 2,
पूर्ण;

अटल काष्ठा resource flash_resource = अणु
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device device_flash = अणु
	.name		= "IXP4XX-Flash",
	.id		= 0,
	.dev		= अणु .platक्रमm_data = &flash_data पूर्ण,
	.num_resources	= 1,
	.resource	= &flash_resource,
पूर्ण;

/* IXP425 2 UART ports */
अटल काष्ठा resource uart_resources[] = अणु
	अणु
		.start		= IXP4XX_UART1_BASE_PHYS,
		.end		= IXP4XX_UART1_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start		= IXP4XX_UART2_BASE_PHYS,
		.end		= IXP4XX_UART2_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण
पूर्ण;

अटल काष्ठा plat_serial8250_port uart_data[] = अणु
	अणु
		.mapbase	= IXP4XX_UART1_BASE_PHYS,
		.membase	= (अक्षर __iomem *)IXP4XX_UART1_BASE_VIRT +
			REG_OFFSET,
		.irq		= IRQ_IXP4XX_UART1,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
		.uartclk	= IXP4XX_UART_XTAL,
	पूर्ण,
	अणु
		.mapbase	= IXP4XX_UART2_BASE_PHYS,
		.membase	= (अक्षर __iomem *)IXP4XX_UART2_BASE_VIRT +
			REG_OFFSET,
		.irq		= IRQ_IXP4XX_UART2,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
		.uartclk	= IXP4XX_UART_XTAL,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device device_uarts = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev.platक्रमm_data	= uart_data,
	.num_resources		= 2,
	.resource		= uart_resources,
पूर्ण;


/* Built-in 10/100 Ethernet MAC पूर्णांकerfaces */
अटल काष्ठा resource eth_npeb_resources[] = अणु
	अणु
		.start		= IXP4XX_EthB_BASE_PHYS,
		.end		= IXP4XX_EthB_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource eth_npec_resources[] = अणु
	अणु
		.start		= IXP4XX_EthC_BASE_PHYS,
		.end		= IXP4XX_EthC_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा eth_plat_info eth_plat[] = अणु
	अणु
		.phy		= 0,
		.rxq		= 3,
		.txपढ़ोyq	= 32,
	पूर्ण, अणु
		.phy		= 1,
		.rxq		= 4,
		.txपढ़ोyq	= 33,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device device_eth_tab[] = अणु
	अणु
		.name			= "ixp4xx_eth",
		.id			= IXP4XX_ETH_NPEB,
		.dev.platक्रमm_data	= eth_plat,
		.num_resources		= ARRAY_SIZE(eth_npeb_resources),
		.resource		= eth_npeb_resources,
	पूर्ण, अणु
		.name			= "ixp4xx_eth",
		.id			= IXP4XX_ETH_NPEC,
		.dev.platक्रमm_data	= eth_plat + 1,
		.num_resources		= ARRAY_SIZE(eth_npec_resources),
		.resource		= eth_npec_resources,
	पूर्ण
पूर्ण;


/* IXP425 2 synchronous serial ports */
अटल काष्ठा hss_plat_info hss_plat[] = अणु
	अणु
		.set_घड़ी	= hss_set_घड़ी,
		.खोलो		= hss_खोलो,
		.बंद		= hss_बंद,
		.txपढ़ोyq	= 34,
	पूर्ण, अणु
		.set_घड़ी	= hss_set_घड़ी,
		.खोलो		= hss_खोलो,
		.बंद		= hss_बंद,
		.txपढ़ोyq	= 35,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device device_hss_tab[] = अणु
	अणु
		.name			= "ixp4xx_hss",
		.id			= 0,
		.dev.platक्रमm_data	= hss_plat,
	पूर्ण, अणु
		.name			= "ixp4xx_hss",
		.id			= 1,
		.dev.platक्रमm_data	= hss_plat + 1,
	पूर्ण
पूर्ण;


अटल काष्ठा platक्रमm_device *device_tab[7] __initdata = अणु
	&device_flash,		/* index 0 */
पूर्ण;

अटल अंतरभूत u8 __init flash_पढ़ोb(u8 __iomem *flash, u32 addr)
अणु
#अगर_घोषित __ARMEB__
	वापस __raw_पढ़ोb(flash + addr);
#अन्यथा
	वापस __raw_पढ़ोb(flash + (addr ^ 3));
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत u16 __init flash_पढ़ोw(u8 __iomem *flash, u32 addr)
अणु
#अगर_घोषित __ARMEB__
	वापस __raw_पढ़ोw(flash + addr);
#अन्यथा
	वापस __raw_पढ़ोw(flash + (addr ^ 2));
#पूर्ण_अगर
पूर्ण

अटल व्योम __init gmlr_init(व्योम)
अणु
	u8 __iomem *flash;
	पूर्णांक i, devices = 1; /* flash */

	ixp4xx_sys_init();

	अगर ((flash = ioremap(IXP4XX_EXP_BUS_BASE_PHYS, 0x80)) == शून्य)
		prपूर्णांकk(KERN_ERR "goramo-mlr: unable to access system"
		       " configuration data\n");
	अन्यथा अणु
		प्रणाली_rev = __raw_पढ़ोl(flash + CFG_REV);
		hw_bits = __raw_पढ़ोl(flash + CFG_HW_BITS);

		क्रम (i = 0; i < ETH_ALEN; i++) अणु
			eth_plat[0].hwaddr[i] =
				flash_पढ़ोb(flash, CFG_ETH0_ADDRESS + i);
			eth_plat[1].hwaddr[i] =
				flash_पढ़ोb(flash, CFG_ETH1_ADDRESS + i);
		पूर्ण

		__raw_ग_लिखोw(FLASH_CMD_READ_ID, flash);
		प्रणाली_serial_high = flash_पढ़ोw(flash, FLASH_SER_OFF);
		प्रणाली_serial_high <<= 16;
		प्रणाली_serial_high |= flash_पढ़ोw(flash, FLASH_SER_OFF + 2);
		प्रणाली_serial_low = flash_पढ़ोw(flash, FLASH_SER_OFF + 4);
		प्रणाली_serial_low <<= 16;
		प्रणाली_serial_low |= flash_पढ़ोw(flash, FLASH_SER_OFF + 6);
		__raw_ग_लिखोw(FLASH_CMD_READ_ARRAY, flash);

		iounmap(flash);
	पूर्ण

	चयन (hw_bits & (CFG_HW_HAS_UART0 | CFG_HW_HAS_UART1)) अणु
	हाल CFG_HW_HAS_UART0:
		स_रखो(&uart_data[1], 0, माप(uart_data[1]));
		device_uarts.num_resources = 1;
		अवरोध;

	हाल CFG_HW_HAS_UART1:
		device_uarts.dev.platक्रमm_data = &uart_data[1];
		device_uarts.resource = &uart_resources[1];
		device_uarts.num_resources = 1;
		अवरोध;
	पूर्ण
	अगर (hw_bits & (CFG_HW_HAS_UART0 | CFG_HW_HAS_UART1))
		device_tab[devices++] = &device_uarts; /* max index 1 */

	अगर (hw_bits & CFG_HW_HAS_ETH0)
		device_tab[devices++] = &device_eth_tab[0]; /* max index 2 */
	अगर (hw_bits & CFG_HW_HAS_ETH1)
		device_tab[devices++] = &device_eth_tab[1]; /* max index 3 */

	अगर (hw_bits & CFG_HW_HAS_HSS0)
		device_tab[devices++] = &device_hss_tab[0]; /* max index 4 */
	अगर (hw_bits & CFG_HW_HAS_HSS1)
		device_tab[devices++] = &device_hss_tab[1]; /* max index 5 */

	hss_plat[0].समयr_freq = ixp4xx_समयr_freq;
	hss_plat[1].समयr_freq = ixp4xx_समयr_freq;

	gpio_request(GPIO_SCL, "SCL/clock");
	gpio_request(GPIO_SDA, "SDA/data");
	gpio_request(GPIO_STR, "strobe");
	gpio_request(GPIO_HSS0_RTS_N, "HSS0 RTS");
	gpio_request(GPIO_HSS1_RTS_N, "HSS1 RTS");
	gpio_request(GPIO_HSS0_DCD_N, "HSS0 DCD");
	gpio_request(GPIO_HSS1_DCD_N, "HSS1 DCD");

	gpio_direction_output(GPIO_SCL, 1);
	gpio_direction_output(GPIO_SDA, 1);
	gpio_direction_output(GPIO_STR, 0);
	gpio_direction_output(GPIO_HSS0_RTS_N, 1);
	gpio_direction_output(GPIO_HSS1_RTS_N, 1);
	gpio_direction_input(GPIO_HSS0_DCD_N);
	gpio_direction_input(GPIO_HSS1_DCD_N);
	irq_set_irq_type(IXP4XX_GPIO_IRQ(GPIO_HSS0_DCD_N), IRQ_TYPE_EDGE_BOTH);
	irq_set_irq_type(IXP4XX_GPIO_IRQ(GPIO_HSS1_DCD_N), IRQ_TYPE_EDGE_BOTH);

	set_control(CONTROL_HSS0_DTR_N, 1);
	set_control(CONTROL_HSS1_DTR_N, 1);
	set_control(CONTROL_EEPROM_WC_N, 1);
	set_control(CONTROL_PCI_RESET_N, 1);
	output_control();

	msleep(1);	      /* Wait क्रम PCI devices to initialize */

	flash_resource.start = IXP4XX_EXP_BUS_BASE(0);
	flash_resource.end = IXP4XX_EXP_BUS_BASE(0) + ixp4xx_exp_bus_size - 1;

	platक्रमm_add_devices(device_tab, devices);
पूर्ण


#अगर_घोषित CONFIG_PCI
अटल व्योम __init gmlr_pci_preinit(व्योम)
अणु
	irq_set_irq_type(IXP4XX_GPIO_IRQ(GPIO_IRQ_ETHA), IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(IXP4XX_GPIO_IRQ(GPIO_IRQ_ETHB), IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(IXP4XX_GPIO_IRQ(GPIO_IRQ_NEC), IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(IXP4XX_GPIO_IRQ(GPIO_IRQ_MPCI), IRQ_TYPE_LEVEL_LOW);
	ixp4xx_pci_preinit();
पूर्ण

अटल व्योम __init gmlr_pci_postinit(व्योम)
अणु
	अगर ((hw_bits & CFG_HW_USB_PORTS) >= 2 &&
	    (hw_bits & CFG_HW_USB_PORTS) < 5) अणु
		/* need to adjust number of USB ports on NEC chip */
		u32 value, addr = BIT(32 - SLOT_NEC) | 0xE0;
		अगर (!ixp4xx_pci_पढ़ो(addr, NP_CMD_CONFIGREAD, &value)) अणु
			value &= ~7;
			value |= (hw_bits & CFG_HW_USB_PORTS);
			ixp4xx_pci_ग_लिखो(addr, NP_CMD_CONFIGWRITE, value);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __init gmlr_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	चयन(slot) अणु
	हाल SLOT_ETHA:	वापस IXP4XX_GPIO_IRQ(GPIO_IRQ_ETHA);
	हाल SLOT_ETHB:	वापस IXP4XX_GPIO_IRQ(GPIO_IRQ_ETHB);
	हाल SLOT_NEC:	वापस IXP4XX_GPIO_IRQ(GPIO_IRQ_NEC);
	शेष:	वापस IXP4XX_GPIO_IRQ(GPIO_IRQ_MPCI);
	पूर्ण
पूर्ण

अटल काष्ठा hw_pci gmlr_hw_pci __initdata = अणु
	.nr_controllers = 1,
	.ops		= &ixp4xx_ops,
	.preinit	= gmlr_pci_preinit,
	.postinit	= gmlr_pci_postinit,
	.setup		= ixp4xx_setup,
	.map_irq	= gmlr_map_irq,
पूर्ण;

अटल पूर्णांक __init gmlr_pci_init(व्योम)
अणु
	अगर (machine_is_goramo_mlr() &&
	    (hw_bits & (CFG_HW_USB_PORTS | CFG_HW_HAS_PCI_SLOT)))
		pci_common_init(&gmlr_hw_pci);
	वापस 0;
पूर्ण

subsys_initcall(gmlr_pci_init);
#पूर्ण_अगर /* CONFIG_PCI */


MACHINE_START(GORAMO_MLR, "MultiLink")
	/* Maपूर्णांकainer: Krzysztof Halasa */
	.map_io		= ixp4xx_map_io,
	.init_early	= ixp4xx_init_early,
	.init_irq	= ixp4xx_init_irq,
	.init_समय	= ixp4xx_समयr_init,
	.atag_offset	= 0x100,
	.init_machine	= gmlr_init,
#अगर defined(CONFIG_PCI)
	.dma_zone_size	= SZ_64M,
#पूर्ण_अगर
	.restart	= ixp4xx_restart,
MACHINE_END
