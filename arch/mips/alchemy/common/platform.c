<शैली गुरु>
/*
 * Platक्रमm device support क्रम Au1x00 SoCs.
 *
 * Copyright 2004, Matt Porter <mporter@kernel.crashing.org>
 *
 * (C) Copyright Embedded Alley Solutions, Inc 2005
 * Author: Pantelis Antoniou <pantelis@embeddedalley.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb/ehci_pdriver.h>
#समावेश <linux/usb/ohci_pdriver.h>

#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-au1x00/au1xxx_dbdma.h>
#समावेश <यंत्र/mach-au1x00/au1100_mmc.h>
#समावेश <यंत्र/mach-au1x00/au1xxx_eth.h>

#समावेश <prom.h>

अटल व्योम alchemy_8250_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state,
			    अचिन्हित पूर्णांक old_state)
अणु
#अगर_घोषित CONFIG_SERIAL_8250
	चयन (state) अणु
	हाल 0:
		alchemy_uart_enable(CPHYSADDR(port->membase));
		serial8250_करो_pm(port, state, old_state);
		अवरोध;
	हाल 3:		/* घातer off */
		serial8250_करो_pm(port, state, old_state);
		alchemy_uart_disable(CPHYSADDR(port->membase));
		अवरोध;
	शेष:
		serial8250_करो_pm(port, state, old_state);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
पूर्ण

#घोषणा PORT(_base, _irq)					\
	अणु							\
		.mapbase	= _base,			\
		.irq		= _irq,				\
		.regshअगरt	= 2,				\
		.iotype		= UPIO_AU,			\
		.flags		= UPF_SKIP_TEST | UPF_IOREMAP | \
				  UPF_FIXED_TYPE,		\
		.type		= PORT_16550A,			\
		.pm		= alchemy_8250_pm,		\
	पूर्ण

अटल काष्ठा plat_serial8250_port au1x00_uart_data[][4] __initdata = अणु
	[ALCHEMY_CPU_AU1000] = अणु
		PORT(AU1000_UART0_PHYS_ADDR, AU1000_UART0_INT),
		PORT(AU1000_UART1_PHYS_ADDR, AU1000_UART1_INT),
		PORT(AU1000_UART2_PHYS_ADDR, AU1000_UART2_INT),
		PORT(AU1000_UART3_PHYS_ADDR, AU1000_UART3_INT),
	पूर्ण,
	[ALCHEMY_CPU_AU1500] = अणु
		PORT(AU1000_UART0_PHYS_ADDR, AU1500_UART0_INT),
		PORT(AU1000_UART3_PHYS_ADDR, AU1500_UART3_INT),
	पूर्ण,
	[ALCHEMY_CPU_AU1100] = अणु
		PORT(AU1000_UART0_PHYS_ADDR, AU1100_UART0_INT),
		PORT(AU1000_UART1_PHYS_ADDR, AU1100_UART1_INT),
		PORT(AU1000_UART3_PHYS_ADDR, AU1100_UART3_INT),
	पूर्ण,
	[ALCHEMY_CPU_AU1550] = अणु
		PORT(AU1000_UART0_PHYS_ADDR, AU1550_UART0_INT),
		PORT(AU1000_UART1_PHYS_ADDR, AU1550_UART1_INT),
		PORT(AU1000_UART3_PHYS_ADDR, AU1550_UART3_INT),
	पूर्ण,
	[ALCHEMY_CPU_AU1200] = अणु
		PORT(AU1000_UART0_PHYS_ADDR, AU1200_UART0_INT),
		PORT(AU1000_UART1_PHYS_ADDR, AU1200_UART1_INT),
	पूर्ण,
	[ALCHEMY_CPU_AU1300] = अणु
		PORT(AU1300_UART0_PHYS_ADDR, AU1300_UART0_INT),
		PORT(AU1300_UART1_PHYS_ADDR, AU1300_UART1_INT),
		PORT(AU1300_UART2_PHYS_ADDR, AU1300_UART2_INT),
		PORT(AU1300_UART3_PHYS_ADDR, AU1300_UART3_INT),
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device au1xx0_uart_device = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_AU1X00,
पूर्ण;

अटल व्योम __init alchemy_setup_uarts(पूर्णांक ctype)
अणु
	दीर्घ uartclk;
	पूर्णांक s = माप(काष्ठा plat_serial8250_port);
	पूर्णांक c = alchemy_get_uarts(ctype);
	काष्ठा plat_serial8250_port *ports;
	काष्ठा clk *clk = clk_get(शून्य, ALCHEMY_PERIPH_CLK);

	अगर (IS_ERR(clk))
		वापस;
	अगर (clk_prepare_enable(clk)) अणु
		clk_put(clk);
		वापस;
	पूर्ण
	uartclk = clk_get_rate(clk);
	clk_put(clk);

	ports = kसुस्मृति(s, (c + 1), GFP_KERNEL);
	अगर (!ports) अणु
		prपूर्णांकk(KERN_INFO "Alchemy: no memory for UART data\n");
		वापस;
	पूर्ण
	स_नकल(ports, au1x00_uart_data[ctype], s * c);
	au1xx0_uart_device.dev.platक्रमm_data = ports;

	/* Fill up uartclk. */
	क्रम (s = 0; s < c; s++)
		ports[s].uartclk = uartclk;
	अगर (platक्रमm_device_रेजिस्टर(&au1xx0_uart_device))
		prपूर्णांकk(KERN_INFO "Alchemy: failed to register UARTs\n");
पूर्ण


अटल u64 alchemy_all_dmamask = DMA_BIT_MASK(32);

/* Power on callback क्रम the ehci platक्रमm driver */
अटल पूर्णांक alchemy_ehci_घातer_on(काष्ठा platक्रमm_device *pdev)
अणु
	वापस alchemy_usb_control(ALCHEMY_USB_EHCI0, 1);
पूर्ण

/* Power off/suspend callback क्रम the ehci platक्रमm driver */
अटल व्योम alchemy_ehci_घातer_off(काष्ठा platक्रमm_device *pdev)
अणु
	alchemy_usb_control(ALCHEMY_USB_EHCI0, 0);
पूर्ण

अटल काष्ठा usb_ehci_pdata alchemy_ehci_pdata = अणु
	.no_io_watchकरोg = 1,
	.घातer_on	= alchemy_ehci_घातer_on,
	.घातer_off	= alchemy_ehci_घातer_off,
	.घातer_suspend	= alchemy_ehci_घातer_off,
पूर्ण;

/* Power on callback क्रम the ohci platक्रमm driver */
अटल पूर्णांक alchemy_ohci_घातer_on(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक unit;

	unit = (pdev->id == 1) ?
		ALCHEMY_USB_OHCI1 : ALCHEMY_USB_OHCI0;

	वापस alchemy_usb_control(unit, 1);
पूर्ण

/* Power off/suspend callback क्रम the ohci platक्रमm driver */
अटल व्योम alchemy_ohci_घातer_off(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक unit;

	unit = (pdev->id == 1) ?
		ALCHEMY_USB_OHCI1 : ALCHEMY_USB_OHCI0;

	alchemy_usb_control(unit, 0);
पूर्ण

अटल काष्ठा usb_ohci_pdata alchemy_ohci_pdata = अणु
	.घातer_on		= alchemy_ohci_घातer_on,
	.घातer_off		= alchemy_ohci_घातer_off,
	.घातer_suspend		= alchemy_ohci_घातer_off,
पूर्ण;

अटल अचिन्हित दीर्घ alchemy_ohci_data[][2] __initdata = अणु
	[ALCHEMY_CPU_AU1000] = अणु AU1000_USB_OHCI_PHYS_ADDR, AU1000_USB_HOST_INT पूर्ण,
	[ALCHEMY_CPU_AU1500] = अणु AU1000_USB_OHCI_PHYS_ADDR, AU1500_USB_HOST_INT पूर्ण,
	[ALCHEMY_CPU_AU1100] = अणु AU1000_USB_OHCI_PHYS_ADDR, AU1100_USB_HOST_INT पूर्ण,
	[ALCHEMY_CPU_AU1550] = अणु AU1550_USB_OHCI_PHYS_ADDR, AU1550_USB_HOST_INT पूर्ण,
	[ALCHEMY_CPU_AU1200] = अणु AU1200_USB_OHCI_PHYS_ADDR, AU1200_USB_INT पूर्ण,
	[ALCHEMY_CPU_AU1300] = अणु AU1300_USB_OHCI0_PHYS_ADDR, AU1300_USB_INT पूर्ण,
पूर्ण;

अटल अचिन्हित दीर्घ alchemy_ehci_data[][2] __initdata = अणु
	[ALCHEMY_CPU_AU1200] = अणु AU1200_USB_EHCI_PHYS_ADDR, AU1200_USB_INT पूर्ण,
	[ALCHEMY_CPU_AU1300] = अणु AU1300_USB_EHCI_PHYS_ADDR, AU1300_USB_INT पूर्ण,
पूर्ण;

अटल पूर्णांक __init _new_usbres(काष्ठा resource **r, काष्ठा platक्रमm_device **d)
अणु
	*r = kसुस्मृति(2, माप(काष्ठा resource), GFP_KERNEL);
	अगर (!*r)
		वापस -ENOMEM;
	*d = kzalloc(माप(काष्ठा platक्रमm_device), GFP_KERNEL);
	अगर (!*d) अणु
		kमुक्त(*r);
		वापस -ENOMEM;
	पूर्ण

	(*d)->dev.coherent_dma_mask = DMA_BIT_MASK(32);
	(*d)->num_resources = 2;
	(*d)->resource = *r;

	वापस 0;
पूर्ण

अटल व्योम __init alchemy_setup_usb(पूर्णांक ctype)
अणु
	काष्ठा resource *res;
	काष्ठा platक्रमm_device *pdev;

	/* setup OHCI0.  Every variant has one */
	अगर (_new_usbres(&res, &pdev))
		वापस;

	res[0].start = alchemy_ohci_data[ctype][0];
	res[0].end = res[0].start + 0x100 - 1;
	res[0].flags = IORESOURCE_MEM;
	res[1].start = alchemy_ohci_data[ctype][1];
	res[1].end = res[1].start;
	res[1].flags = IORESOURCE_IRQ;
	pdev->name = "ohci-platform";
	pdev->id = 0;
	pdev->dev.dma_mask = &alchemy_all_dmamask;
	pdev->dev.platक्रमm_data = &alchemy_ohci_pdata;

	अगर (platक्रमm_device_रेजिस्टर(pdev))
		prपूर्णांकk(KERN_INFO "Alchemy USB: cannot add OHCI0\n");


	/* setup EHCI0: Au1200/Au1300 */
	अगर ((ctype == ALCHEMY_CPU_AU1200) || (ctype == ALCHEMY_CPU_AU1300)) अणु
		अगर (_new_usbres(&res, &pdev))
			वापस;

		res[0].start = alchemy_ehci_data[ctype][0];
		res[0].end = res[0].start + 0x100 - 1;
		res[0].flags = IORESOURCE_MEM;
		res[1].start = alchemy_ehci_data[ctype][1];
		res[1].end = res[1].start;
		res[1].flags = IORESOURCE_IRQ;
		pdev->name = "ehci-platform";
		pdev->id = 0;
		pdev->dev.dma_mask = &alchemy_all_dmamask;
		pdev->dev.platक्रमm_data = &alchemy_ehci_pdata;

		अगर (platक्रमm_device_रेजिस्टर(pdev))
			prपूर्णांकk(KERN_INFO "Alchemy USB: cannot add EHCI0\n");
	पूर्ण

	/* Au1300: OHCI1 */
	अगर (ctype == ALCHEMY_CPU_AU1300) अणु
		अगर (_new_usbres(&res, &pdev))
			वापस;

		res[0].start = AU1300_USB_OHCI1_PHYS_ADDR;
		res[0].end = res[0].start + 0x100 - 1;
		res[0].flags = IORESOURCE_MEM;
		res[1].start = AU1300_USB_INT;
		res[1].end = res[1].start;
		res[1].flags = IORESOURCE_IRQ;
		pdev->name = "ohci-platform";
		pdev->id = 1;
		pdev->dev.dma_mask = &alchemy_all_dmamask;
		pdev->dev.platक्रमm_data = &alchemy_ohci_pdata;

		अगर (platक्रमm_device_रेजिस्टर(pdev))
			prपूर्णांकk(KERN_INFO "Alchemy USB: cannot add OHCI1\n");
	पूर्ण
पूर्ण

/* Macro to help defining the Ethernet MAC resources */
#घोषणा MAC_RES_COUNT	4	/* MAC regs, MAC en, MAC INT, MACDMA regs */
#घोषणा MAC_RES(_base, _enable, _irq, _macdma)		\
	अणु						\
		.start	= _base,			\
		.end	= _base + 0xffff,		\
		.flags	= IORESOURCE_MEM,		\
	पूर्ण,						\
	अणु						\
		.start	= _enable,			\
		.end	= _enable + 0x3,		\
		.flags	= IORESOURCE_MEM,		\
	पूर्ण,						\
	अणु						\
		.start	= _irq,				\
		.end	= _irq,				\
		.flags	= IORESOURCE_IRQ		\
	पूर्ण,						\
	अणु						\
		.start	= _macdma,			\
		.end	= _macdma + 0x1ff,		\
		.flags	= IORESOURCE_MEM,		\
	पूर्ण

अटल काष्ठा resource au1xxx_eth0_resources[][MAC_RES_COUNT] __initdata = अणु
	[ALCHEMY_CPU_AU1000] = अणु
		MAC_RES(AU1000_MAC0_PHYS_ADDR,
			AU1000_MACEN_PHYS_ADDR,
			AU1000_MAC0_DMA_INT,
			AU1000_MACDMA0_PHYS_ADDR)
	पूर्ण,
	[ALCHEMY_CPU_AU1500] = अणु
		MAC_RES(AU1500_MAC0_PHYS_ADDR,
			AU1500_MACEN_PHYS_ADDR,
			AU1500_MAC0_DMA_INT,
			AU1000_MACDMA0_PHYS_ADDR)
	पूर्ण,
	[ALCHEMY_CPU_AU1100] = अणु
		MAC_RES(AU1000_MAC0_PHYS_ADDR,
			AU1000_MACEN_PHYS_ADDR,
			AU1100_MAC0_DMA_INT,
			AU1000_MACDMA0_PHYS_ADDR)
	पूर्ण,
	[ALCHEMY_CPU_AU1550] = अणु
		MAC_RES(AU1000_MAC0_PHYS_ADDR,
			AU1000_MACEN_PHYS_ADDR,
			AU1550_MAC0_DMA_INT,
			AU1000_MACDMA0_PHYS_ADDR)
	पूर्ण,
पूर्ण;

अटल काष्ठा au1000_eth_platक्रमm_data au1xxx_eth0_platक्रमm_data = अणु
	.phy1_search_mac0 = 1,
पूर्ण;

अटल काष्ठा platक्रमm_device au1xxx_eth0_device = अणु
	.name		= "au1000-eth",
	.id		= 0,
	.num_resources	= MAC_RES_COUNT,
	.dev = अणु
		.dma_mask               = &alchemy_all_dmamask,
		.coherent_dma_mask      = DMA_BIT_MASK(32),
		.platक्रमm_data          = &au1xxx_eth0_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource au1xxx_eth1_resources[][MAC_RES_COUNT] __initdata = अणु
	[ALCHEMY_CPU_AU1000] = अणु
		MAC_RES(AU1000_MAC1_PHYS_ADDR,
			AU1000_MACEN_PHYS_ADDR + 4,
			AU1000_MAC1_DMA_INT,
			AU1000_MACDMA1_PHYS_ADDR)
	पूर्ण,
	[ALCHEMY_CPU_AU1500] = अणु
		MAC_RES(AU1500_MAC1_PHYS_ADDR,
			AU1500_MACEN_PHYS_ADDR + 4,
			AU1500_MAC1_DMA_INT,
			AU1000_MACDMA1_PHYS_ADDR)
	पूर्ण,
	[ALCHEMY_CPU_AU1550] = अणु
		MAC_RES(AU1000_MAC1_PHYS_ADDR,
			AU1000_MACEN_PHYS_ADDR + 4,
			AU1550_MAC1_DMA_INT,
			AU1000_MACDMA1_PHYS_ADDR)
	पूर्ण,
पूर्ण;

अटल काष्ठा au1000_eth_platक्रमm_data au1xxx_eth1_platक्रमm_data = अणु
	.phy1_search_mac0 = 1,
पूर्ण;

अटल काष्ठा platक्रमm_device au1xxx_eth1_device = अणु
	.name		= "au1000-eth",
	.id		= 1,
	.num_resources	= MAC_RES_COUNT,
	.dev = अणु
		.dma_mask               = &alchemy_all_dmamask,
		.coherent_dma_mask      = DMA_BIT_MASK(32),
		.platक्रमm_data          = &au1xxx_eth1_platक्रमm_data,
	पूर्ण,
पूर्ण;

व्योम __init au1xxx_override_eth_cfg(अचिन्हित पूर्णांक port,
			काष्ठा au1000_eth_platक्रमm_data *eth_data)
अणु
	अगर (!eth_data || port > 1)
		वापस;

	अगर (port == 0)
		स_नकल(&au1xxx_eth0_platक्रमm_data, eth_data,
			माप(काष्ठा au1000_eth_platक्रमm_data));
	अन्यथा
		स_नकल(&au1xxx_eth1_platक्रमm_data, eth_data,
			माप(काष्ठा au1000_eth_platक्रमm_data));
पूर्ण

अटल व्योम __init alchemy_setup_macs(पूर्णांक ctype)
अणु
	पूर्णांक ret, i;
	अचिन्हित अक्षर ethaddr[6];
	काष्ठा resource *macres;

	/* Handle 1st MAC */
	अगर (alchemy_get_macs(ctype) < 1)
		वापस;

	macres = kmemdup(au1xxx_eth0_resources[ctype],
			 माप(काष्ठा resource) * MAC_RES_COUNT, GFP_KERNEL);
	अगर (!macres) अणु
		prपूर्णांकk(KERN_INFO "Alchemy: no memory for MAC0 resources\n");
		वापस;
	पूर्ण
	au1xxx_eth0_device.resource = macres;

	i = prom_get_ethernet_addr(ethaddr);
	अगर (!i && !is_valid_ether_addr(au1xxx_eth0_platक्रमm_data.mac))
		स_नकल(au1xxx_eth0_platक्रमm_data.mac, ethaddr, 6);

	ret = platक्रमm_device_रेजिस्टर(&au1xxx_eth0_device);
	अगर (ret)
		prपूर्णांकk(KERN_INFO "Alchemy: failed to register MAC0\n");


	/* Handle 2nd MAC */
	अगर (alchemy_get_macs(ctype) < 2)
		वापस;

	macres = kmemdup(au1xxx_eth1_resources[ctype],
			 माप(काष्ठा resource) * MAC_RES_COUNT, GFP_KERNEL);
	अगर (!macres) अणु
		prपूर्णांकk(KERN_INFO "Alchemy: no memory for MAC1 resources\n");
		वापस;
	पूर्ण
	au1xxx_eth1_device.resource = macres;

	ethaddr[5] += 1;	/* next addr क्रम 2nd MAC */
	अगर (!i && !is_valid_ether_addr(au1xxx_eth1_platक्रमm_data.mac))
		स_नकल(au1xxx_eth1_platक्रमm_data.mac, ethaddr, 6);

	/* Register second MAC अगर enabled in pinfunc */
	अगर (!(alchemy_rdsys(AU1000_SYS_PINFUNC) & SYS_PF_NI2)) अणु
		ret = platक्रमm_device_रेजिस्टर(&au1xxx_eth1_device);
		अगर (ret)
			prपूर्णांकk(KERN_INFO "Alchemy: failed to register MAC1\n");
	पूर्ण
पूर्ण

अटल पूर्णांक __init au1xxx_platक्रमm_init(व्योम)
अणु
	पूर्णांक ctype = alchemy_get_cputype();

	alchemy_setup_uarts(ctype);
	alchemy_setup_macs(ctype);
	alchemy_setup_usb(ctype);

	वापस 0;
पूर्ण

arch_initcall(au1xxx_platक्रमm_init);
