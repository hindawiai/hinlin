<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  RouterBoard 500 Platक्रमm devices
 *
 *  Copyright (C) 2006 Felix Fietkau <nbd@खोलोwrt.org>
 *  Copyright (C) 2007 Florian Fainelli <florian@खोलोwrt.org>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/platnand.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/serial_8250.h>

#समावेश <यंत्र/bootinfo.h>

#समावेश <यंत्र/mach-rc32434/rc32434.h>
#समावेश <यंत्र/mach-rc32434/dma.h>
#समावेश <यंत्र/mach-rc32434/dma_v.h>
#समावेश <यंत्र/mach-rc32434/eth.h>
#समावेश <यंत्र/mach-rc32434/rb.h>
#समावेश <यंत्र/mach-rc32434/पूर्णांकeg.h>
#समावेश <यंत्र/mach-rc32434/gpपन.स>
#समावेश <यंत्र/mach-rc32434/irq.h>

#घोषणा ETH0_RX_DMA_ADDR  (DMA0_BASE_ADDR + 0 * DMA_CHAN_OFFSET)
#घोषणा ETH0_TX_DMA_ADDR  (DMA0_BASE_ADDR + 1 * DMA_CHAN_OFFSET)

बाह्य अचिन्हित पूर्णांक idt_cpu_freq;

अटल काष्ठा mpmc_device dev3;

व्योम set_latch_u5(अचिन्हित अक्षर or_mask, अचिन्हित अक्षर nand_mask)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev3.lock, flags);

	dev3.state = (dev3.state | or_mask) & ~nand_mask;
	ग_लिखोb(dev3.state, dev3.base);

	spin_unlock_irqrestore(&dev3.lock, flags);
पूर्ण
EXPORT_SYMBOL(set_latch_u5);

अचिन्हित अक्षर get_latch_u5(व्योम)
अणु
	वापस dev3.state;
पूर्ण
EXPORT_SYMBOL(get_latch_u5);

अटल काष्ठा resource korina_dev0_res[] = अणु
	अणु
		.name = "emac",
		.start = ETH0_BASE_ADDR,
		.end = ETH0_BASE_ADDR + माप(काष्ठा eth_regs),
		.flags = IORESOURCE_MEM,
	 पूर्ण, अणु
		.name = "rx",
		.start = ETH0_DMA_RX_IRQ,
		.end = ETH0_DMA_RX_IRQ,
		.flags = IORESOURCE_IRQ
	पूर्ण, अणु
		.name = "tx",
		.start = ETH0_DMA_TX_IRQ,
		.end = ETH0_DMA_TX_IRQ,
		.flags = IORESOURCE_IRQ
	पूर्ण, अणु
		.name = "dma_rx",
		.start = ETH0_RX_DMA_ADDR,
		.end = ETH0_RX_DMA_ADDR + DMA_CHAN_OFFSET - 1,
		.flags = IORESOURCE_MEM,
	 पूर्ण, अणु
		.name = "dma_tx",
		.start = ETH0_TX_DMA_ADDR,
		.end = ETH0_TX_DMA_ADDR + DMA_CHAN_OFFSET - 1,
		.flags = IORESOURCE_MEM,
	 पूर्ण
पूर्ण;

अटल काष्ठा korina_device korina_dev0_data = अणु
	.name = "korina0",
	.mac = अणु0xde, 0xca, 0xff, 0xc0, 0xff, 0xeeपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device korina_dev0 = अणु
	.id = -1,
	.name = "korina",
	.resource = korina_dev0_res,
	.num_resources = ARRAY_SIZE(korina_dev0_res),
	.dev = अणु
		.platक्रमm_data = &korina_dev0_data.mac,
	पूर्ण
पूर्ण;

अटल काष्ठा resource cf_slot0_res[] = अणु
	अणु
		.name = "cf_membase",
		.flags = IORESOURCE_MEM
	पूर्ण, अणु
		.name = "cf_irq",
		.start = (8 + 4 * 32 + CF_GPIO_NUM),	/* 149 */
		.end = (8 + 4 * 32 + CF_GPIO_NUM),
		.flags = IORESOURCE_IRQ
	पूर्ण
पूर्ण;

अटल काष्ठा gpiod_lookup_table cf_slot0_gpio_table = अणु
	.dev_id = "pata-rb532-cf",
	.table = अणु
		GPIO_LOOKUP("gpio0", CF_GPIO_NUM,
			    शून्य, GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device cf_slot0 = अणु
	.id = -1,
	.name = "pata-rb532-cf",
	.resource = cf_slot0_res,
	.num_resources = ARRAY_SIZE(cf_slot0_res),
पूर्ण;

/* Resources and device क्रम न_अंकD */
अटल पूर्णांक rb532_dev_पढ़ोy(काष्ठा nand_chip *chip)
अणु
	वापस gpio_get_value(GPIO_RDY);
पूर्ण

अटल व्योम rb532_cmd_ctrl(काष्ठा nand_chip *chip, पूर्णांक cmd, अचिन्हित पूर्णांक ctrl)
अणु
	अचिन्हित अक्षर orbits, nandbits;

	अगर (ctrl & न_अंकD_CTRL_CHANGE) अणु
		orbits = (ctrl & न_अंकD_CLE) << 1;
		orbits |= (ctrl & न_अंकD_ALE) >> 1;

		nandbits = (~ctrl & न_अंकD_CLE) << 1;
		nandbits |= (~ctrl & न_अंकD_ALE) >> 1;

		set_latch_u5(orbits, nandbits);
	पूर्ण
	अगर (cmd != न_अंकD_CMD_NONE)
		ग_लिखोb(cmd, chip->legacy.IO_ADDR_W);
पूर्ण

अटल काष्ठा resource nand_slot0_res[] = अणु
	[0] = अणु
		.name = "nand_membase",
		.flags = IORESOURCE_MEM
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_nand_data rb532_nand_data = अणु
	.ctrl.dev_पढ़ोy = rb532_dev_पढ़ोy,
	.ctrl.cmd_ctrl	= rb532_cmd_ctrl,
पूर्ण;

अटल काष्ठा platक्रमm_device nand_slot0 = अणु
	.name = "gen_nand",
	.id = -1,
	.resource = nand_slot0_res,
	.num_resources = ARRAY_SIZE(nand_slot0_res),
	.dev.platक्रमm_data = &rb532_nand_data,
पूर्ण;

अटल काष्ठा mtd_partition rb532_partition_info[] = अणु
	अणु
		.name = "Routerboard NAND boot",
		.offset = 0,
		.size = 4 * 1024 * 1024,
	पूर्ण, अणु
		.name = "rootfs",
		.offset = MTDPART_OFS_NXTBLK,
		.size = MTDPART_SIZ_FULL,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device rb532_led = अणु
	.name = "rb532-led",
	.id = -1,
पूर्ण;

अटल काष्ठा platक्रमm_device rb532_button = अणु
	.name	= "rb532-button",
	.id	= -1,
पूर्ण;

अटल काष्ठा resource rb532_wdt_res[] = अणु
	अणु
		.name = "rb532_wdt_res",
		.start = INTEG0_BASE_ADDR,
		.end = INTEG0_BASE_ADDR + माप(काष्ठा पूर्णांकeg),
		.flags = IORESOURCE_MEM,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device rb532_wdt = अणु
	.name		= "rc32434_wdt",
	.id		= -1,
	.resource	= rb532_wdt_res,
	.num_resources	= ARRAY_SIZE(rb532_wdt_res),
पूर्ण;

अटल काष्ठा plat_serial8250_port rb532_uart_res[] = अणु
	अणु
		.type           = PORT_16550A,
		.membase	= (अक्षर *)KSEG1ADDR(REGBASE + UART0BASE),
		.irq		= UART0_IRQ,
		.regshअगरt	= 2,
		.iotype		= UPIO_MEM,
		.flags		= UPF_BOOT_AUTOCONF,
	पूर्ण,
	अणु
		.flags		= 0,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device rb532_uart = अणु
	.name		   = "serial8250",
	.id		   = PLAT8250_DEV_PLATFORM,
	.dev.platक्रमm_data = &rb532_uart_res,
पूर्ण;

अटल काष्ठा platक्रमm_device *rb532_devs[] = अणु
	&korina_dev0,
	&nand_slot0,
	&cf_slot0,
	&rb532_led,
	&rb532_button,
	&rb532_uart,
	&rb532_wdt
पूर्ण;

/* न_अंकD definitions */
#घोषणा न_अंकD_CHIP_DELAY 25

अटल व्योम __init rb532_nand_setup(व्योम)
अणु
	चयन (mips_machtype) अणु
	हाल MACH_MIKROTIK_RB532A:
		set_latch_u5(LO_FOFF | LO_CEX,
				LO_ULED | LO_ALE | LO_CLE | LO_WPX);
		अवरोध;
	शेष:
		set_latch_u5(LO_WPX | LO_FOFF | LO_CEX,
				LO_ULED | LO_ALE | LO_CLE);
		अवरोध;
	पूर्ण

	/* Setup न_अंकD specअगरic settings */
	rb532_nand_data.chip.nr_chips = 1;
	rb532_nand_data.chip.nr_partitions = ARRAY_SIZE(rb532_partition_info);
	rb532_nand_data.chip.partitions = rb532_partition_info;
	rb532_nand_data.chip.chip_delay = न_अंकD_CHIP_DELAY;
पूर्ण


अटल पूर्णांक __init plat_setup_devices(व्योम)
अणु
	/* Look क्रम the CF card पढ़ोer */
	अगर (!पढ़ोl(IDT434_REG_BASE + DEV1MASK))
		rb532_devs[2] = शून्य;	/* disable cf_slot0 at index 2 */
	अन्यथा अणु
		cf_slot0_res[0].start =
		    पढ़ोl(IDT434_REG_BASE + DEV1BASE);
		cf_slot0_res[0].end = cf_slot0_res[0].start + 0x1000;
	पूर्ण

	/* Read the न_अंकD resources from the device controller */
	nand_slot0_res[0].start = पढ़ोl(IDT434_REG_BASE + DEV2BASE);
	nand_slot0_res[0].end = nand_slot0_res[0].start + 0x1000;

	/* Read and map device controller 3 */
	dev3.base = ioremap(पढ़ोl(IDT434_REG_BASE + DEV3BASE), 1);

	अगर (!dev3.base) अणु
		prपूर्णांकk(KERN_ERR "rb532: cannot remap device controller 3\n");
		वापस -ENXIO;
	पूर्ण

	/* Initialise the न_अंकD device */
	rb532_nand_setup();

	/* set the uart घड़ी to the current cpu frequency */
	rb532_uart_res[0].uartclk = idt_cpu_freq;

	gpiod_add_lookup_table(&cf_slot0_gpio_table);
	वापस platक्रमm_add_devices(rb532_devs, ARRAY_SIZE(rb532_devs));
पूर्ण

#अगर_घोषित CONFIG_NET

अटल पूर्णांक __init setup_kmac(अक्षर *s)
अणु
	prपूर्णांकk(KERN_INFO "korina mac = %s\n", s);
	अगर (!mac_pton(s, korina_dev0_data.mac)) अणु
		prपूर्णांकk(KERN_ERR "Invalid mac\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

__setup("kmac=", setup_kmac);

#पूर्ण_अगर /* CONFIG_NET */

arch_initcall(plat_setup_devices);
