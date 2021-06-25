<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Cavium Networks CNS3420 Validation Board
 *
 * Copyright 2000 Deep Blue Solutions Ltd
 * Copyright 2008 ARM Limited
 * Copyright 2008 Cavium Networks
 *		  Scott Shu
 * Copyright 2010 MontaVista Software, LLC.
 *		  Anton Vorontsov <avorontsov@mvista.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/compiler.h>
#समावेश <linux/पन.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/usb/ehci_pdriver.h>
#समावेश <linux/usb/ohci_pdriver.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश "cns3xxx.h"
#समावेश "pm.h"
#समावेश "core.h"
#समावेश "devices.h"

/*
 * NOR Flash
 */
अटल काष्ठा mtd_partition cns3420_nor_partitions[] = अणु
	अणु
		.name		= "uboot",
		.size		= 0x00040000,
		.offset		= 0,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण, अणु
		.name		= "kernel",
		.size		= 0x004C0000,
		.offset		= MTDPART_OFS_APPEND,
	पूर्ण, अणु
		.name		= "filesystem",
		.size		= 0x7000000,
		.offset		= MTDPART_OFS_APPEND,
	पूर्ण, अणु
		.name		= "filesystem2",
		.size		= 0x0AE0000,
		.offset		= MTDPART_OFS_APPEND,
	पूर्ण, अणु
		.name		= "ubootenv",
		.size		= MTDPART_SIZ_FULL,
		.offset		= MTDPART_OFS_APPEND,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data cns3420_nor_pdata = अणु
	.width = 2,
	.parts = cns3420_nor_partitions,
	.nr_parts = ARRAY_SIZE(cns3420_nor_partitions),
पूर्ण;

अटल काष्ठा resource cns3420_nor_res = अणु
	.start = CNS3XXX_FLASH_BASE,
	.end = CNS3XXX_FLASH_BASE + SZ_128M - 1,
	.flags = IORESOURCE_MEM | IORESOURCE_MEM_32BIT,
पूर्ण;

अटल काष्ठा platक्रमm_device cns3420_nor_pdev = अणु
	.name = "physmap-flash",
	.id = 0,
	.resource = &cns3420_nor_res,
	.num_resources = 1,
	.dev = अणु
		.platक्रमm_data = &cns3420_nor_pdata,
	पूर्ण,
पूर्ण;

/*
 * UART
 */
अटल व्योम __init cns3420_early_serial_setup(व्योम)
अणु
#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE
	अटल काष्ठा uart_port cns3420_serial_port = अणु
		.membase        = (व्योम __iomem *)CNS3XXX_UART0_BASE_VIRT,
		.mapbase        = CNS3XXX_UART0_BASE,
		.irq            = IRQ_CNS3XXX_UART0,
		.iotype         = UPIO_MEM,
		.flags          = UPF_BOOT_AUTOCONF | UPF_FIXED_TYPE,
		.regshअगरt       = 2,
		.uartclk        = 24000000,
		.line           = 0,
		.type           = PORT_16550A,
		.fअगरosize       = 16,
	पूर्ण;

	early_serial_setup(&cns3420_serial_port);
#पूर्ण_अगर
पूर्ण

/*
 * USB
 */
अटल काष्ठा resource cns3xxx_usb_ehci_resources[] = अणु
	[0] = अणु
		.start = CNS3XXX_USB_BASE,
		.end   = CNS3XXX_USB_BASE + SZ_16M - 1,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start = IRQ_CNS3XXX_USB_EHCI,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल u64 cns3xxx_usb_ehci_dma_mask = DMA_BIT_MASK(32);

अटल पूर्णांक csn3xxx_usb_घातer_on(काष्ठा platक्रमm_device *pdev)
अणु
	/*
	 * EHCI and OHCI share the same घड़ी and घातer,
	 * resetting twice would cause the 1st controller been reset.
	 * Thereक्रमe only करो घातer up  at the first up device, and
	 * घातer करोwn at the last करोwn device.
	 *
	 * Set USB AHB INCR length to 16
	 */
	अगर (atomic_inc_वापस(&usb_pwr_ref) == 1) अणु
		cns3xxx_pwr_घातer_up(1 << PM_PLL_HM_PD_CTRL_REG_OFFSET_PLL_USB);
		cns3xxx_pwr_clk_en(1 << PM_CLK_GATE_REG_OFFSET_USB_HOST);
		cns3xxx_pwr_soft_rst(1 << PM_SOFT_RST_REG_OFFST_USB_HOST);
		__raw_ग_लिखोl((__raw_पढ़ोl(MISC_CHIP_CONFIG_REG) | (0X2 << 24)),
			MISC_CHIP_CONFIG_REG);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम csn3xxx_usb_घातer_off(काष्ठा platक्रमm_device *pdev)
अणु
	/*
	 * EHCI and OHCI share the same घड़ी and घातer,
	 * resetting twice would cause the 1st controller been reset.
	 * Thereक्रमe only करो घातer up  at the first up device, and
	 * घातer करोwn at the last करोwn device.
	 */
	अगर (atomic_dec_वापस(&usb_pwr_ref) == 0)
		cns3xxx_pwr_clk_dis(1 << PM_CLK_GATE_REG_OFFSET_USB_HOST);
पूर्ण

अटल काष्ठा usb_ehci_pdata cns3xxx_usb_ehci_pdata = अणु
	.घातer_on	= csn3xxx_usb_घातer_on,
	.घातer_off	= csn3xxx_usb_घातer_off,
पूर्ण;

अटल काष्ठा platक्रमm_device cns3xxx_usb_ehci_device = अणु
	.name          = "ehci-platform",
	.num_resources = ARRAY_SIZE(cns3xxx_usb_ehci_resources),
	.resource      = cns3xxx_usb_ehci_resources,
	.dev           = अणु
		.dma_mask          = &cns3xxx_usb_ehci_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
		.platक्रमm_data     = &cns3xxx_usb_ehci_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource cns3xxx_usb_ohci_resources[] = अणु
	[0] = अणु
		.start = CNS3XXX_USB_OHCI_BASE,
		.end   = CNS3XXX_USB_OHCI_BASE + SZ_16M - 1,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start = IRQ_CNS3XXX_USB_OHCI,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल u64 cns3xxx_usb_ohci_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा usb_ohci_pdata cns3xxx_usb_ohci_pdata = अणु
	.num_ports	= 1,
	.घातer_on	= csn3xxx_usb_घातer_on,
	.घातer_off	= csn3xxx_usb_घातer_off,
पूर्ण;

अटल काष्ठा platक्रमm_device cns3xxx_usb_ohci_device = अणु
	.name          = "ohci-platform",
	.num_resources = ARRAY_SIZE(cns3xxx_usb_ohci_resources),
	.resource      = cns3xxx_usb_ohci_resources,
	.dev           = अणु
		.dma_mask          = &cns3xxx_usb_ohci_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
		.platक्रमm_data	   = &cns3xxx_usb_ohci_pdata,
	पूर्ण,
पूर्ण;

/*
 * Initialization
 */
अटल काष्ठा platक्रमm_device *cns3420_pdevs[] __initdata = अणु
	&cns3420_nor_pdev,
	&cns3xxx_usb_ehci_device,
	&cns3xxx_usb_ohci_device,
पूर्ण;

अटल व्योम __init cns3420_init(व्योम)
अणु
	cns3xxx_l2x0_init();

	platक्रमm_add_devices(cns3420_pdevs, ARRAY_SIZE(cns3420_pdevs));

	cns3xxx_ahci_init();
	cns3xxx_sdhci_init();

	pm_घातer_off = cns3xxx_घातer_off;
पूर्ण

अटल काष्ठा map_desc cns3420_io_desc[] __initdata = अणु
	अणु
		.भव	= CNS3XXX_UART0_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_UART0_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	पूर्ण,
पूर्ण;

अटल व्योम __init cns3420_map_io(व्योम)
अणु
	cns3xxx_map_io();
	iotable_init(cns3420_io_desc, ARRAY_SIZE(cns3420_io_desc));

	cns3420_early_serial_setup();
पूर्ण

MACHINE_START(CNS3420VB, "Cavium Networks CNS3420 Validation Board")
	.atag_offset	= 0x100,
	.map_io		= cns3420_map_io,
	.init_irq	= cns3xxx_init_irq,
	.init_समय	= cns3xxx_समयr_init,
	.init_machine	= cns3420_init,
	.init_late      = cns3xxx_pcie_init_late,
	.restart	= cns3xxx_restart,
MACHINE_END
