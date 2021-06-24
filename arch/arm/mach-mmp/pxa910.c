<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-mmp/pxa910.c
 *
 *  Code specअगरic to PXA910
 */
#समावेश <linux/clk/mmp.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip/mmp.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/hardware/cache-tauros2.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश "addr-map.h"
#समावेश "regs-apbc.h"
#समावेश <linux/soc/mmp/cputype.h>
#समावेश "irqs.h"
#समावेश "mfp.h"
#समावेश "devices.h"
#समावेश "pm-pxa910.h"
#समावेश "pxa910.h"

#समावेश "common.h"

#घोषणा MFPR_VIRT_BASE	(APB_VIRT_BASE + 0x1e000)

अटल काष्ठा mfp_addr_map pxa910_mfp_addr_map[] __initdata =
अणु
	MFP_ADDR_X(GPIO0, GPIO54, 0xdc),
	MFP_ADDR_X(GPIO67, GPIO98, 0x1b8),
	MFP_ADDR_X(GPIO100, GPIO109, 0x238),

	MFP_ADDR(GPIO123, 0xcc),
	MFP_ADDR(GPIO124, 0xd0),

	MFP_ADDR(DF_IO0, 0x40),
	MFP_ADDR(DF_IO1, 0x3c),
	MFP_ADDR(DF_IO2, 0x38),
	MFP_ADDR(DF_IO3, 0x34),
	MFP_ADDR(DF_IO4, 0x30),
	MFP_ADDR(DF_IO5, 0x2c),
	MFP_ADDR(DF_IO6, 0x28),
	MFP_ADDR(DF_IO7, 0x24),
	MFP_ADDR(DF_IO8, 0x20),
	MFP_ADDR(DF_IO9, 0x1c),
	MFP_ADDR(DF_IO10, 0x18),
	MFP_ADDR(DF_IO11, 0x14),
	MFP_ADDR(DF_IO12, 0x10),
	MFP_ADDR(DF_IO13, 0xc),
	MFP_ADDR(DF_IO14, 0x8),
	MFP_ADDR(DF_IO15, 0x4),

	MFP_ADDR(DF_nCS0_SM_nCS2, 0x44),
	MFP_ADDR(DF_nCS1_SM_nCS3, 0x48),
	MFP_ADDR(SM_nCS0, 0x4c),
	MFP_ADDR(SM_nCS1, 0x50),
	MFP_ADDR(DF_WEn, 0x54),
	MFP_ADDR(DF_REn, 0x58),
	MFP_ADDR(DF_CLE_SM_OEn, 0x5c),
	MFP_ADDR(DF_ALE_SM_WEn, 0x60),
	MFP_ADDR(SM_SCLK, 0x64),
	MFP_ADDR(DF_RDY0, 0x68),
	MFP_ADDR(SM_BE0, 0x6c),
	MFP_ADDR(SM_BE1, 0x70),
	MFP_ADDR(SM_ADV, 0x74),
	MFP_ADDR(DF_RDY1, 0x78),
	MFP_ADDR(SM_ADVMUX, 0x7c),
	MFP_ADDR(SM_RDY, 0x80),

	MFP_ADDR_X(MMC1_DAT7, MMC1_WP, 0x84),

	MFP_ADDR_END,
पूर्ण;

व्योम __init pxa910_init_irq(व्योम)
अणु
	icu_init_irq();
#अगर_घोषित CONFIG_PM
	icu_irq_chip.irq_set_wake = pxa910_set_wake;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __init pxa910_init(व्योम)
अणु
	अगर (cpu_is_pxa910()) अणु
#अगर_घोषित CONFIG_CACHE_TAUROS2
		tauros2_init(0);
#पूर्ण_अगर
		mfp_init_base(MFPR_VIRT_BASE);
		mfp_init_addr(pxa910_mfp_addr_map);
		pxa910_clk_init(APB_PHYS_BASE + 0x50000,
				AXI_PHYS_BASE + 0x82800,
				APB_PHYS_BASE + 0x15000,
				APB_PHYS_BASE + 0x3b000);
	पूर्ण

	वापस 0;
पूर्ण
postcore_initcall(pxa910_init);

/* प्रणाली समयr - घड़ी enabled, 3.25MHz */
#घोषणा TIMER_CLK_RST	(APBC_APBCLK | APBC_FNCLK | APBC_FNCLKSEL(3))
#घोषणा APBC_TIMERS	APBC_REG(0x34)

व्योम __init pxa910_समयr_init(व्योम)
अणु
	/* reset and configure */
	__raw_ग_लिखोl(APBC_APBCLK | APBC_RST, APBC_TIMERS);
	__raw_ग_लिखोl(TIMER_CLK_RST, APBC_TIMERS);

	mmp_समयr_init(IRQ_PXA910_AP1_TIMER1, 3250000);
पूर्ण

/* on-chip devices */

/* NOTE: there are totally 3 UARTs on PXA910:
 *
 *   UART1   - Slow UART (can be used both by AP and CP)
 *   UART2/3 - Fast UART
 *
 * To be backward compatible with the legacy FFUART/BTUART/STUART sequence,
 * they are re-ordered as:
 *
 *   pxa910_device_uart1 - UART2 as FFUART
 *   pxa910_device_uart2 - UART3 as BTUART
 *
 * UART1 is not used by AP क्रम the moment.
 */
PXA910_DEVICE(uart1, "pxa2xx-uart", 0, UART2, 0xd4017000, 0x30, 21, 22);
PXA910_DEVICE(uart2, "pxa2xx-uart", 1, UART3, 0xd4018000, 0x30, 23, 24);
PXA910_DEVICE(twsi0, "pxa2xx-i2c", 0, TWSI0, 0xd4011000, 0x28);
PXA910_DEVICE(twsi1, "pxa2xx-i2c", 1, TWSI1, 0xd4025000, 0x28);
PXA910_DEVICE(pwm1, "pxa910-pwm", 0, NONE, 0xd401a000, 0x10);
PXA910_DEVICE(pwm2, "pxa910-pwm", 1, NONE, 0xd401a400, 0x10);
PXA910_DEVICE(pwm3, "pxa910-pwm", 2, NONE, 0xd401a800, 0x10);
PXA910_DEVICE(pwm4, "pxa910-pwm", 3, NONE, 0xd401ac00, 0x10);
PXA910_DEVICE(nand, "pxa3xx-nand", -1, न_अंकD, 0xd4283000, 0x80, 97, 99);
PXA910_DEVICE(disp, "mmp-disp", 0, LCD, 0xd420b000, 0x1ec);
PXA910_DEVICE(fb, "mmp-fb", -1, NONE, 0, 0);
PXA910_DEVICE(panel, "tpo-hvga", -1, NONE, 0, 0);

काष्ठा resource pxa910_resource_gpio[] = अणु
	अणु
		.start	= 0xd4019000,
		.end	= 0xd4019fff,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.start	= IRQ_PXA910_AP_GPIO,
		.end	= IRQ_PXA910_AP_GPIO,
		.name	= "gpio_mux",
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa910_device_gpio = अणु
	.name		= "mmp-gpio",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(pxa910_resource_gpio),
	.resource	= pxa910_resource_gpio,
पूर्ण;

अटल काष्ठा resource pxa910_resource_rtc[] = अणु
	अणु
		.start	= 0xd4010000,
		.end	= 0xd401003f,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.start	= IRQ_PXA910_RTC_INT,
		.end	= IRQ_PXA910_RTC_INT,
		.name	= "rtc 1Hz",
		.flags	= IORESOURCE_IRQ,
	पूर्ण, अणु
		.start	= IRQ_PXA910_RTC_ALARM,
		.end	= IRQ_PXA910_RTC_ALARM,
		.name	= "rtc alarm",
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa910_device_rtc = अणु
	.name		= "sa1100-rtc",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(pxa910_resource_rtc),
	.resource	= pxa910_resource_rtc,
पूर्ण;
