<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * arch/xtensa/platक्रमm/xtavnet/setup.c
 *
 * ...
 *
 * Authors:	Chris Zankel <chris@zankel.net>
 *		Joe Taylor <joe@tensilica.com>
 *
 * Copyright 2001 - 2006 Tensilica Inc.
 */
#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/reboot.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/types.h>
#समावेश <linux/major.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/समयx.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/platक्रमm.h>
#समावेश <यंत्र/bootparam.h>
#समावेश <platक्रमm/lcd.h>
#समावेश <platक्रमm/hardware.h>

व्योम platक्रमm_halt(व्योम)
अणु
	lcd_disp_at_pos(" HALT ", 0);
	local_irq_disable();
	जबतक (1)
		cpu_relax();
पूर्ण

व्योम platक्रमm_घातer_off(व्योम)
अणु
	lcd_disp_at_pos("POWEROFF", 0);
	local_irq_disable();
	जबतक (1)
		cpu_relax();
पूर्ण

व्योम platक्रमm_restart(व्योम)
अणु
	/* Flush and reset the mmu, simulate a processor reset, and
	 * jump to the reset vector. */
	cpu_reset();
	/* control never माला_लो here */
पूर्ण

#अगर_घोषित CONFIG_XTENSA_CALIBRATE_CCOUNT

व्योम __init platक्रमm_calibrate_ccount(व्योम)
अणु
	ccount_freq = *(दीर्घ *)XTFPGA_CLKFRQ_VADDR;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_OF

अटल व्योम __init xtfpga_clk_setup(काष्ठा device_node *np)
अणु
	व्योम __iomem *base = of_iomap(np, 0);
	काष्ठा clk *clk;
	u32 freq;

	अगर (!base) अणु
		pr_err("%pOFn: invalid address\n", np);
		वापस;
	पूर्ण

	freq = __raw_पढ़ोl(base);
	iounmap(base);
	clk = clk_रेजिस्टर_fixed_rate(शून्य, np->name, शून्य, 0, freq);

	अगर (IS_ERR(clk)) अणु
		pr_err("%pOFn: clk registration failed\n", np);
		वापस;
	पूर्ण

	अगर (of_clk_add_provider(np, of_clk_src_simple_get, clk)) अणु
		pr_err("%pOFn: clk provider registration failed\n", np);
		वापस;
	पूर्ण
पूर्ण
CLK_OF_DECLARE(xtfpga_clk, "cdns,xtfpga-clock", xtfpga_clk_setup);

#घोषणा MAC_LEN 6
अटल व्योम __init update_local_mac(काष्ठा device_node *node)
अणु
	काष्ठा property *newmac;
	स्थिर u8* macaddr;
	पूर्णांक prop_len;

	macaddr = of_get_property(node, "local-mac-address", &prop_len);
	अगर (macaddr == शून्य || prop_len != MAC_LEN)
		वापस;

	newmac = kzalloc(माप(*newmac) + MAC_LEN, GFP_KERNEL);
	अगर (newmac == शून्य)
		वापस;

	newmac->value = newmac + 1;
	newmac->length = MAC_LEN;
	newmac->name = kstrdup("local-mac-address", GFP_KERNEL);
	अगर (newmac->name == शून्य) अणु
		kमुक्त(newmac);
		वापस;
	पूर्ण

	स_नकल(newmac->value, macaddr, MAC_LEN);
	((u8*)newmac->value)[5] = (*(u32*)DIP_SWITCHES_VADDR) & 0x3f;
	of_update_property(node, newmac);
पूर्ण

अटल पूर्णांक __init machine_setup(व्योम)
अणु
	काष्ठा device_node *eth = शून्य;

	अगर ((eth = of_find_compatible_node(eth, शून्य, "opencores,ethoc")))
		update_local_mac(eth);
	वापस 0;
पूर्ण
arch_initcall(machine_setup);

#अन्यथा

#समावेश <linux/serial_8250.h>
#समावेश <linux/अगर.h>
#समावेश <net/ethoc.h>
#समावेश <linux/usb/c67x00.h>

/*----------------------------------------------------------------------------
 *  Ethernet -- OpenCores Ethernet MAC (ethoc driver)
 */

अटल काष्ठा resource ethoc_res[] = अणु
	[0] = अणु /* रेजिस्टर space */
		.start = OETH_REGS_PADDR,
		.end   = OETH_REGS_PADDR + OETH_REGS_SIZE - 1,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु /* buffer space */
		.start = OETH_SRAMBUFF_PADDR,
		.end   = OETH_SRAMBUFF_PADDR + OETH_SRAMBUFF_SIZE - 1,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[2] = अणु /* IRQ number */
		.start = XTENSA_PIC_LINUX_IRQ(OETH_IRQ),
		.end   = XTENSA_PIC_LINUX_IRQ(OETH_IRQ),
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा ethoc_platक्रमm_data ethoc_pdata = अणु
	/*
	 * The MAC address क्रम these boards is 00:50:c2:13:6f:xx.
	 * The last byte (here as zero) is पढ़ो from the DIP चयनes on the
	 * board.
	 */
	.hwaddr = अणु 0x00, 0x50, 0xc2, 0x13, 0x6f, 0 पूर्ण,
	.phy_id = -1,
	.big_endian = XCHAL_HAVE_BE,
पूर्ण;

अटल काष्ठा platक्रमm_device ethoc_device = अणु
	.name = "ethoc",
	.id = -1,
	.num_resources = ARRAY_SIZE(ethoc_res),
	.resource = ethoc_res,
	.dev = अणु
		.platक्रमm_data = &ethoc_pdata,
	पूर्ण,
पूर्ण;

/*----------------------------------------------------------------------------
 *  USB Host/Device -- Cypress CY7C67300
 */

अटल काष्ठा resource c67x00_res[] = अणु
	[0] = अणु /* रेजिस्टर space */
		.start = C67X00_PADDR,
		.end   = C67X00_PADDR + C67X00_SIZE - 1,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु /* IRQ number */
		.start = XTENSA_PIC_LINUX_IRQ(C67X00_IRQ),
		.end   = XTENSA_PIC_LINUX_IRQ(C67X00_IRQ),
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा c67x00_platक्रमm_data c67x00_pdata = अणु
	.sie_config = C67X00_SIE1_HOST | C67X00_SIE2_UNUSED,
	.hpi_regstep = 4,
पूर्ण;

अटल काष्ठा platक्रमm_device c67x00_device = अणु
	.name = "c67x00",
	.id = -1,
	.num_resources = ARRAY_SIZE(c67x00_res),
	.resource = c67x00_res,
	.dev = अणु
		.platक्रमm_data = &c67x00_pdata,
	पूर्ण,
पूर्ण;

/*----------------------------------------------------------------------------
 *  UART
 */

अटल काष्ठा resource serial_resource = अणु
	.start	= DUART16552_PADDR,
	.end	= DUART16552_PADDR + 0x1f,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा plat_serial8250_port serial_platक्रमm_data[] = अणु
	[0] = अणु
		.mapbase	= DUART16552_PADDR,
		.irq		= XTENSA_PIC_LINUX_IRQ(DUART16552_INTNUM),
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST |
				  UPF_IOREMAP,
		.iotype		= XCHAL_HAVE_BE ? UPIO_MEM32BE : UPIO_MEM32,
		.regshअगरt	= 2,
		.uartclk	= 0,    /* set in xtavnet_init() */
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device xtavnet_uart = अणु
	.name		= "serial8250",
	.id		= PLAT8250_DEV_PLATFORM,
	.dev		= अणु
		.platक्रमm_data	= serial_platक्रमm_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &serial_resource,
पूर्ण;

/* platक्रमm devices */
अटल काष्ठा platक्रमm_device *platक्रमm_devices[] __initdata = अणु
	&ethoc_device,
	&c67x00_device,
	&xtavnet_uart,
पूर्ण;


अटल पूर्णांक __init xtavnet_init(व्योम)
अणु
	/* Ethernet MAC address.  */
	ethoc_pdata.hwaddr[5] = *(u32 *)DIP_SWITCHES_VADDR;

	/* Clock rate varies among FPGA bitstreams; board specअगरic FPGA रेजिस्टर
	 * reports the actual घड़ी rate.
	 */
	serial_platक्रमm_data[0].uartclk = *(दीर्घ *)XTFPGA_CLKFRQ_VADDR;


	/* रेजिस्टर platक्रमm devices */
	platक्रमm_add_devices(platक्रमm_devices, ARRAY_SIZE(platक्रमm_devices));

	/* ETHOC driver is a bit quiet; at least display Ethernet MAC, so user
	 * knows whether they set it correctly on the DIP चयनes.
	 */
	pr_info("XTFPGA: Ethernet MAC %pM\n", ethoc_pdata.hwaddr);
	ethoc_pdata.eth_clkfreq = *(दीर्घ *)XTFPGA_CLKFRQ_VADDR;

	वापस 0;
पूर्ण

/*
 * Register to be करोne during करो_initcalls().
 */
arch_initcall(xtavnet_init);

#पूर्ण_अगर /* CONFIG_OF */
