<शैली गुरु>
/*
 * arch/arm/mach-ixp4xx/common.c
 *
 * Generic code shared across all IXP4XX platक्रमms
 *
 * Maपूर्णांकainer: Deepak Saxena <dsaxena@plनिकासy.net>
 *
 * Copyright 2002 (c) Intel Corporation
 * Copyright 2003-2004 (c) MontaVista, Software, Inc. 
 * 
 * This file is licensed under  the terms of the GNU General Public 
 * License version 2. This program is licensed "as is" without any 
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/tty.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>
#समावेश <linux/export.h>
#समावेश <linux/cpu.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/irqchip/irq-ixp4xx.h>
#समावेश <linux/platक्रमm_data/समयr-ixp4xx.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <mach/udc.h>
#समावेश <mach/hardware.h>
#समावेश <mach/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/mach/समय.स>

#समावेश "irqs.h"

#घोषणा IXP4XX_TIMER_FREQ 66666000

/*************************************************************************
 * IXP4xx chipset I/O mapping
 *************************************************************************/
अटल काष्ठा map_desc ixp4xx_io_desc[] __initdata = अणु
	अणु	/* UART, Interrupt ctrl, GPIO, समयrs, NPEs, MACs, USB .... */
		.भव	= (अचिन्हित दीर्घ)IXP4XX_PERIPHERAL_BASE_VIRT,
		.pfn		= __phys_to_pfn(IXP4XX_PERIPHERAL_BASE_PHYS),
		.length		= IXP4XX_PERIPHERAL_REGION_SIZE,
		.type		= MT_DEVICE
	पूर्ण, अणु	/* Expansion Bus Config Registers */
		.भव	= (अचिन्हित दीर्घ)IXP4XX_EXP_CFG_BASE_VIRT,
		.pfn		= __phys_to_pfn(IXP4XX_EXP_CFG_BASE_PHYS),
		.length		= IXP4XX_EXP_CFG_REGION_SIZE,
		.type		= MT_DEVICE
	पूर्ण, अणु	/* PCI Registers */
		.भव	= (अचिन्हित दीर्घ)IXP4XX_PCI_CFG_BASE_VIRT,
		.pfn		= __phys_to_pfn(IXP4XX_PCI_CFG_BASE_PHYS),
		.length		= IXP4XX_PCI_CFG_REGION_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;

व्योम __init ixp4xx_map_io(व्योम)
अणु
  	iotable_init(ixp4xx_io_desc, ARRAY_SIZE(ixp4xx_io_desc));
पूर्ण

व्योम __init ixp4xx_init_irq(व्योम)
अणु
	/*
	 * ixp4xx करोes not implement the XScale PWRMODE रेजिस्टर
	 * so it must not call cpu_करो_idle().
	 */
	cpu_idle_poll_ctrl(true);

	ixp4xx_irq_init(IXP4XX_INTC_BASE_PHYS,
			(cpu_is_ixp46x() || cpu_is_ixp43x()));
पूर्ण

व्योम __init ixp4xx_समयr_init(व्योम)
अणु
	वापस ixp4xx_समयr_setup(IXP4XX_TIMER_BASE_PHYS,
				  IRQ_IXP4XX_TIMER1,
				  IXP4XX_TIMER_FREQ);
पूर्ण

अटल काष्ठा pxa2xx_udc_mach_info ixp4xx_udc_info;

व्योम __init ixp4xx_set_udc_info(काष्ठा pxa2xx_udc_mach_info *info)
अणु
	स_नकल(&ixp4xx_udc_info, info, माप *info);
पूर्ण

अटल काष्ठा resource ixp4xx_udc_resources[] = अणु
	[0] = अणु
		.start  = 0xc800b000,
		.end    = 0xc800bfff,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = IRQ_IXP4XX_USB,
		.end    = IRQ_IXP4XX_USB,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource ixp4xx_gpio_resource[] = अणु
	अणु
		.start = IXP4XX_GPIO_BASE_PHYS,
		.end = IXP4XX_GPIO_BASE_PHYS + 0xfff,
		.flags = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device ixp4xx_gpio_device = अणु
	.name           = "ixp4xx-gpio",
	.id             = -1,
	.dev = अणु
		.coherent_dma_mask      = DMA_BIT_MASK(32),
	पूर्ण,
	.resource = ixp4xx_gpio_resource,
	.num_resources  = ARRAY_SIZE(ixp4xx_gpio_resource),
पूर्ण;

/*
 * USB device controller. The IXP4xx uses the same controller as PXA25X,
 * so we just use the same device.
 */
अटल काष्ठा platक्रमm_device ixp4xx_udc_device = अणु
	.name           = "pxa25x-udc",
	.id             = -1,
	.num_resources  = 2,
	.resource       = ixp4xx_udc_resources,
	.dev            = अणु
		.platक्रमm_data = &ixp4xx_udc_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource ixp4xx_npe_resources[] = अणु
	अणु
		.start = IXP4XX_NPEA_BASE_PHYS,
		.end = IXP4XX_NPEA_BASE_PHYS + 0xfff,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start = IXP4XX_NPEB_BASE_PHYS,
		.end = IXP4XX_NPEB_BASE_PHYS + 0xfff,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start = IXP4XX_NPEC_BASE_PHYS,
		.end = IXP4XX_NPEC_BASE_PHYS + 0xfff,
		.flags = IORESOURCE_MEM,
	पूर्ण,

पूर्ण;

अटल काष्ठा platक्रमm_device ixp4xx_npe_device = अणु
	.name           = "ixp4xx-npe",
	.id             = -1,
	.num_resources  = ARRAY_SIZE(ixp4xx_npe_resources),
	.resource       = ixp4xx_npe_resources,
पूर्ण;

अटल काष्ठा resource ixp4xx_qmgr_resources[] = अणु
	अणु
		.start = IXP4XX_QMGR_BASE_PHYS,
		.end = IXP4XX_QMGR_BASE_PHYS + 0x3fff,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start = IRQ_IXP4XX_QM1,
		.end = IRQ_IXP4XX_QM1,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start = IRQ_IXP4XX_QM2,
		.end = IRQ_IXP4XX_QM2,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device ixp4xx_qmgr_device = अणु
	.name           = "ixp4xx-qmgr",
	.id             = -1,
	.num_resources  = ARRAY_SIZE(ixp4xx_qmgr_resources),
	.resource       = ixp4xx_qmgr_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device *ixp4xx_devices[] __initdata = अणु
	&ixp4xx_npe_device,
	&ixp4xx_qmgr_device,
	&ixp4xx_gpio_device,
	&ixp4xx_udc_device,
पूर्ण;

अटल काष्ठा resource ixp46x_i2c_resources[] = अणु
	[0] = अणु
		.start 	= 0xc8011000,
		.end	= 0xc801101c,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start 	= IRQ_IXP4XX_I2C,
		.end	= IRQ_IXP4XX_I2C,
		.flags	= IORESOURCE_IRQ
	पूर्ण
पूर्ण;

/*
 * I2C controller. The IXP46x uses the same block as the IOP3xx, so
 * we just use the same device name.
 */
अटल काष्ठा platक्रमm_device ixp46x_i2c_controller = अणु
	.name		= "IOP3xx-I2C",
	.id		= 0,
	.num_resources	= 2,
	.resource	= ixp46x_i2c_resources
पूर्ण;

अटल काष्ठा platक्रमm_device *ixp46x_devices[] __initdata = अणु
	&ixp46x_i2c_controller
पूर्ण;

अचिन्हित दीर्घ ixp4xx_exp_bus_size;
EXPORT_SYMBOL(ixp4xx_exp_bus_size);

व्योम __init ixp4xx_sys_init(व्योम)
अणु
	ixp4xx_exp_bus_size = SZ_16M;

	platक्रमm_add_devices(ixp4xx_devices, ARRAY_SIZE(ixp4xx_devices));

	अगर (cpu_is_ixp46x()) अणु
		पूर्णांक region;

		platक्रमm_add_devices(ixp46x_devices,
				ARRAY_SIZE(ixp46x_devices));

		क्रम (region = 0; region < 7; region++) अणु
			अगर((*(IXP4XX_EXP_REG(0x4 * region)) & 0x200)) अणु
				ixp4xx_exp_bus_size = SZ_32M;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	prपूर्णांकk("IXP4xx: Using %luMiB expansion bus window size\n",
			ixp4xx_exp_bus_size >> 20);
पूर्ण

अचिन्हित दीर्घ ixp4xx_समयr_freq = IXP4XX_TIMER_FREQ;
EXPORT_SYMBOL(ixp4xx_समयr_freq);

व्योम ixp4xx_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	अगर (mode == REBOOT_SOFT) अणु
		/* Jump पूर्णांकo ROM at address 0 */
		soft_restart(0);
	पूर्ण अन्यथा अणु
		/* Use on-chip reset capability */

		/* set the "key" रेजिस्टर to enable access to
		 * "timer" and "enable" रेजिस्टरs
		 */
		*IXP4XX_OSWK = IXP4XX_WDT_KEY;

		/* ग_लिखो 0 to the समयr रेजिस्टर क्रम an immediate reset */
		*IXP4XX_OSWT = 0;

		*IXP4XX_OSWE = IXP4XX_WDT_RESET_ENABLE | IXP4XX_WDT_COUNT_ENABLE;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PCI
अटल पूर्णांक ixp4xx_needs_bounce(काष्ठा device *dev, dma_addr_t dma_addr, माप_प्रकार size)
अणु
	वापस (dma_addr + size) > SZ_64M;
पूर्ण

अटल पूर्णांक ixp4xx_platक्रमm_notअगरy_हटाओ(काष्ठा device *dev)
अणु
	अगर (dev_is_pci(dev))
		dmabounce_unरेजिस्टर_dev(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Setup DMA mask to 64MB on PCI devices and 4 GB on all other things.
 */
अटल पूर्णांक ixp4xx_platक्रमm_notअगरy(काष्ठा device *dev)
अणु
	dev->dma_mask = &dev->coherent_dma_mask;

#अगर_घोषित CONFIG_PCI
	अगर (dev_is_pci(dev)) अणु
		dev->coherent_dma_mask = DMA_BIT_MASK(28); /* 64 MB */
		dmabounce_रेजिस्टर_dev(dev, 2048, 4096, ixp4xx_needs_bounce);
		वापस 0;
	पूर्ण
#पूर्ण_अगर

	dev->coherent_dma_mask = DMA_BIT_MASK(32);
	वापस 0;
पूर्ण

पूर्णांक dma_set_coherent_mask(काष्ठा device *dev, u64 mask)
अणु
	अगर (dev_is_pci(dev))
		mask &= DMA_BIT_MASK(28); /* 64 MB */

	अगर ((mask & DMA_BIT_MASK(28)) == DMA_BIT_MASK(28)) अणु
		dev->coherent_dma_mask = mask;
		वापस 0;
	पूर्ण

	वापस -EIO;		/* device wanted sub-64MB mask */
पूर्ण
EXPORT_SYMBOL(dma_set_coherent_mask);

#अगर_घोषित CONFIG_IXP4XX_INसूचीECT_PCI
/*
 * In the हाल of using indirect PCI, we simply वापस the actual PCI
 * address and our पढ़ो/ग_लिखो implementation use that to drive the
 * access रेजिस्टरs. If something outside of PCI is ioremap'd, we
 * fallback to the शेष.
 */

अटल व्योम __iomem *ixp4xx_ioremap_caller(phys_addr_t addr, माप_प्रकार size,
					   अचिन्हित पूर्णांक mtype, व्योम *caller)
अणु
	अगर (!is_pci_memory(addr))
		वापस __arm_ioremap_caller(addr, size, mtype, caller);

	वापस (व्योम __iomem *)addr;
पूर्ण

अटल व्योम ixp4xx_iounmap(अस्थिर व्योम __iomem *addr)
अणु
	अगर (!is_pci_memory((__क्रमce u32)addr))
		__iounmap(addr);
पूर्ण
#पूर्ण_अगर

व्योम __init ixp4xx_init_early(व्योम)
अणु
	platक्रमm_notअगरy = ixp4xx_platक्रमm_notअगरy;
#अगर_घोषित CONFIG_PCI
	platक्रमm_notअगरy_हटाओ = ixp4xx_platक्रमm_notअगरy_हटाओ;
#पूर्ण_अगर
#अगर_घोषित CONFIG_IXP4XX_INसूचीECT_PCI
	arch_ioremap_caller = ixp4xx_ioremap_caller;
	arch_iounmap = ixp4xx_iounmap;
#पूर्ण_अगर
पूर्ण
