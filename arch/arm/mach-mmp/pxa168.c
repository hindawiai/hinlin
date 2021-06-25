<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-mmp/pxa168.c
 *
 *  Code specअगरic to PXA168
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/clk/mmp.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/mv_usb.h>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/mach/समय.स>
#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश "addr-map.h"
#समावेश "common.h"
#समावेश <linux/soc/mmp/cputype.h>
#समावेश "devices.h"
#समावेश "irqs.h"
#समावेश "mfp.h"
#समावेश "pxa168.h"
#समावेश "regs-apbc.h"
#समावेश "regs-apmu.h"
#समावेश "regs-usb.h"

#घोषणा MFPR_VIRT_BASE	(APB_VIRT_BASE + 0x1e000)

अटल काष्ठा mfp_addr_map pxa168_mfp_addr_map[] __initdata =
अणु
	MFP_ADDR_X(GPIO0,   GPIO36,  0x04c),
	MFP_ADDR_X(GPIO37,  GPIO55,  0x000),
	MFP_ADDR_X(GPIO56,  GPIO123, 0x0e0),
	MFP_ADDR_X(GPIO124, GPIO127, 0x0f4),

	MFP_ADDR_END,
पूर्ण;

व्योम __init pxa168_init_irq(व्योम)
अणु
	icu_init_irq();
पूर्ण

अटल पूर्णांक __init pxa168_init(व्योम)
अणु
	अगर (cpu_is_pxa168()) अणु
		mfp_init_base(MFPR_VIRT_BASE);
		mfp_init_addr(pxa168_mfp_addr_map);
		pxa168_clk_init(APB_PHYS_BASE + 0x50000,
				AXI_PHYS_BASE + 0x82800,
				APB_PHYS_BASE + 0x15000);
	पूर्ण

	वापस 0;
पूर्ण
postcore_initcall(pxa168_init);

/* प्रणाली समयr - घड़ी enabled, 3.25MHz */
#घोषणा TIMER_CLK_RST	(APBC_APBCLK | APBC_FNCLK | APBC_FNCLKSEL(3))
#घोषणा APBC_TIMERS	APBC_REG(0x34)

व्योम __init pxa168_समयr_init(व्योम)
अणु
	/* this is early, we have to initialize the CCU रेजिस्टरs by
	 * ourselves instead of using clk_* API. Clock rate is defined
	 * by APBC_TIMERS_CLK_RST (3.25MHz) and enabled मुक्त-running
	 */
	__raw_ग_लिखोl(APBC_APBCLK | APBC_RST, APBC_TIMERS);

	/* 3.25MHz, bus/functional घड़ी enabled, release reset */
	__raw_ग_लिखोl(TIMER_CLK_RST, APBC_TIMERS);

	mmp_समयr_init(IRQ_PXA168_TIMER1, 3250000);
पूर्ण

व्योम pxa168_clear_keypad_wakeup(व्योम)
अणु
	uपूर्णांक32_t val;
	uपूर्णांक32_t mask = APMU_PXA168_KP_WAKE_CLR;

	/* wake event clear is needed in order to clear keypad पूर्णांकerrupt */
	val = __raw_पढ़ोl(APMU_WAKE_CLR);
	__raw_ग_लिखोl(val |  mask, APMU_WAKE_CLR);
पूर्ण

/* on-chip devices */
PXA168_DEVICE(uart1, "pxa2xx-uart", 0, UART1, 0xd4017000, 0x30, 21, 22);
PXA168_DEVICE(uart2, "pxa2xx-uart", 1, UART2, 0xd4018000, 0x30, 23, 24);
PXA168_DEVICE(uart3, "pxa2xx-uart", 2, UART3, 0xd4026000, 0x30, 23, 24);
PXA168_DEVICE(twsi0, "pxa2xx-i2c", 0, TWSI0, 0xd4011000, 0x28);
PXA168_DEVICE(twsi1, "pxa2xx-i2c", 1, TWSI1, 0xd4025000, 0x28);
PXA168_DEVICE(pwm1, "pxa168-pwm", 0, NONE, 0xd401a000, 0x10);
PXA168_DEVICE(pwm2, "pxa168-pwm", 1, NONE, 0xd401a400, 0x10);
PXA168_DEVICE(pwm3, "pxa168-pwm", 2, NONE, 0xd401a800, 0x10);
PXA168_DEVICE(pwm4, "pxa168-pwm", 3, NONE, 0xd401ac00, 0x10);
PXA168_DEVICE(nand, "pxa3xx-nand", -1, न_अंकD, 0xd4283000, 0x80, 97, 99);
PXA168_DEVICE(ssp1, "pxa168-ssp", 0, SSP1, 0xd401b000, 0x40, 52, 53);
PXA168_DEVICE(ssp2, "pxa168-ssp", 1, SSP2, 0xd401c000, 0x40, 54, 55);
PXA168_DEVICE(ssp3, "pxa168-ssp", 2, SSP3, 0xd401f000, 0x40, 56, 57);
PXA168_DEVICE(ssp4, "pxa168-ssp", 3, SSP4, 0xd4020000, 0x40, 58, 59);
PXA168_DEVICE(ssp5, "pxa168-ssp", 4, SSP5, 0xd4021000, 0x40, 60, 61);
PXA168_DEVICE(fb, "pxa168-fb", -1, LCD, 0xd420b000, 0x1c8);
PXA168_DEVICE(keypad, "pxa27x-keypad", -1, KEYPAD, 0xd4012000, 0x4c);
PXA168_DEVICE(eth, "pxa168-eth", -1, MFU, 0xc0800000, 0x0fff);

काष्ठा resource pxa168_resource_gpio[] = अणु
	अणु
		.start	= 0xd4019000,
		.end	= 0xd4019fff,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.start	= IRQ_PXA168_GPIOX,
		.end	= IRQ_PXA168_GPIOX,
		.name	= "gpio_mux",
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa168_device_gpio = अणु
	.name		= "mmp-gpio",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(pxa168_resource_gpio),
	.resource	= pxa168_resource_gpio,
पूर्ण;

काष्ठा resource pxa168_usb_host_resources[] = अणु
	/* USB Host conroller रेजिस्टर base */
	[0] = अणु
		.start	= PXA168_U2H_REGBASE + U2x_CAPREGS_OFFSET,
		.end	= PXA168_U2H_REGBASE + USB_REG_RANGE,
		.flags	= IORESOURCE_MEM,
		.name	= "capregs",
	पूर्ण,
	/* USB PHY रेजिस्टर base */
	[1] = अणु
		.start	= PXA168_U2H_PHYBASE,
		.end	= PXA168_U2H_PHYBASE + USB_PHY_RANGE,
		.flags	= IORESOURCE_MEM,
		.name	= "phyregs",
	पूर्ण,
	[2] = अणु
		.start	= IRQ_PXA168_USB2,
		.end	= IRQ_PXA168_USB2,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल u64 pxa168_usb_host_dmamask = DMA_BIT_MASK(32);
काष्ठा platक्रमm_device pxa168_device_usb_host = अणु
	.name = "pxa-sph",
	.id   = -1,
	.dev  = अणु
		.dma_mask = &pxa168_usb_host_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,

	.num_resources = ARRAY_SIZE(pxa168_usb_host_resources),
	.resource      = pxa168_usb_host_resources,
पूर्ण;

पूर्णांक __init pxa168_add_usb_host(काष्ठा mv_usb_platक्रमm_data *pdata)
अणु
	pxa168_device_usb_host.dev.platक्रमm_data = pdata;
	वापस platक्रमm_device_रेजिस्टर(&pxa168_device_usb_host);
पूर्ण

व्योम pxa168_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	soft_restart(0xffff0000);
पूर्ण
