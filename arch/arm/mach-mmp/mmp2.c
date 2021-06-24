<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-mmp/mmp2.c
 *
 * code name MMP2
 *
 * Copyright (C) 2009 Marvell International Ltd.
 */
#समावेश <linux/clk/mmp.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
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
#समावेश "mmp2.h"
#समावेश "pm-mmp2.h"

#समावेश "common.h"

#घोषणा MFPR_VIRT_BASE	(APB_VIRT_BASE + 0x1e000)

अटल काष्ठा mfp_addr_map mmp2_addr_map[] __initdata = अणु

	MFP_ADDR_X(GPIO0, GPIO58, 0x54),
	MFP_ADDR_X(GPIO59, GPIO73, 0x280),
	MFP_ADDR_X(GPIO74, GPIO101, 0x170),

	MFP_ADDR(GPIO102, 0x0),
	MFP_ADDR(GPIO103, 0x4),
	MFP_ADDR(GPIO104, 0x1fc),
	MFP_ADDR(GPIO105, 0x1f8),
	MFP_ADDR(GPIO106, 0x1f4),
	MFP_ADDR(GPIO107, 0x1f0),
	MFP_ADDR(GPIO108, 0x21c),
	MFP_ADDR(GPIO109, 0x218),
	MFP_ADDR(GPIO110, 0x214),
	MFP_ADDR(GPIO111, 0x200),
	MFP_ADDR(GPIO112, 0x244),
	MFP_ADDR(GPIO113, 0x25c),
	MFP_ADDR(GPIO114, 0x164),
	MFP_ADDR_X(GPIO115, GPIO122, 0x260),

	MFP_ADDR(GPIO123, 0x148),
	MFP_ADDR_X(GPIO124, GPIO141, 0xc),

	MFP_ADDR(GPIO142, 0x8),
	MFP_ADDR_X(GPIO143, GPIO151, 0x220),
	MFP_ADDR_X(GPIO152, GPIO153, 0x248),
	MFP_ADDR_X(GPIO154, GPIO155, 0x254),
	MFP_ADDR_X(GPIO156, GPIO159, 0x14c),

	MFP_ADDR(GPIO160, 0x250),
	MFP_ADDR(GPIO161, 0x210),
	MFP_ADDR(GPIO162, 0x20c),
	MFP_ADDR(GPIO163, 0x208),
	MFP_ADDR(GPIO164, 0x204),
	MFP_ADDR(GPIO165, 0x1ec),
	MFP_ADDR(GPIO166, 0x1e8),
	MFP_ADDR(GPIO167, 0x1e4),
	MFP_ADDR(GPIO168, 0x1e0),

	MFP_ADDR_X(TWSI1_SCL, TWSI1_SDA, 0x140),
	MFP_ADDR_X(TWSI4_SCL, TWSI4_SDA, 0x2bc),

	MFP_ADDR(PMIC_INT, 0x2c4),
	MFP_ADDR(CLK_REQ, 0x160),

	MFP_ADDR_END,
पूर्ण;

व्योम mmp2_clear_pmic_पूर्णांक(व्योम)
अणु
	व्योम __iomem *mfpr_pmic;
	अचिन्हित दीर्घ data;

	mfpr_pmic = APB_VIRT_BASE + 0x1e000 + 0x2c4;
	data = __raw_पढ़ोl(mfpr_pmic);
	__raw_ग_लिखोl(data | (1 << 6), mfpr_pmic);
	__raw_ग_लिखोl(data, mfpr_pmic);
पूर्ण

व्योम __init mmp2_init_irq(व्योम)
अणु
	mmp2_init_icu();
#अगर_घोषित CONFIG_PM
	icu_irq_chip.irq_set_wake = mmp2_set_wake;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __init mmp2_init(व्योम)
अणु
	अगर (cpu_is_mmp2()) अणु
#अगर_घोषित CONFIG_CACHE_TAUROS2
		tauros2_init(0);
#पूर्ण_अगर
		mfp_init_base(MFPR_VIRT_BASE);
		mfp_init_addr(mmp2_addr_map);
		mmp2_clk_init(APB_PHYS_BASE + 0x50000,
			      AXI_PHYS_BASE + 0x82800,
			      APB_PHYS_BASE + 0x15000);
	पूर्ण

	वापस 0;
पूर्ण
postcore_initcall(mmp2_init);

#घोषणा APBC_TIMERS	APBC_REG(0x024)

व्योम __init mmp2_समयr_init(व्योम)
अणु
	अचिन्हित दीर्घ clk_rst;

	__raw_ग_लिखोl(APBC_APBCLK | APBC_RST, APBC_TIMERS);

	/*
	 * enable bus/functional घड़ी, enable 6.5MHz (भागider 4),
	 * release reset
	 */
	clk_rst = APBC_APBCLK | APBC_FNCLK | APBC_FNCLKSEL(1);
	__raw_ग_लिखोl(clk_rst, APBC_TIMERS);

	mmp_समयr_init(IRQ_MMP2_TIMER1, 6500000);
पूर्ण

/* on-chip devices */
MMP2_DEVICE(uart1, "pxa2xx-uart", 0, UART1, 0xd4030000, 0x30, 4, 5);
MMP2_DEVICE(uart2, "pxa2xx-uart", 1, UART2, 0xd4017000, 0x30, 20, 21);
MMP2_DEVICE(uart3, "pxa2xx-uart", 2, UART3, 0xd4018000, 0x30, 22, 23);
MMP2_DEVICE(uart4, "pxa2xx-uart", 3, UART4, 0xd4016000, 0x30, 18, 19);
MMP2_DEVICE(twsi1, "pxa2xx-i2c", 0, TWSI1, 0xd4011000, 0x70);
MMP2_DEVICE(twsi2, "pxa2xx-i2c", 1, TWSI2, 0xd4031000, 0x70);
MMP2_DEVICE(twsi3, "pxa2xx-i2c", 2, TWSI3, 0xd4032000, 0x70);
MMP2_DEVICE(twsi4, "pxa2xx-i2c", 3, TWSI4, 0xd4033000, 0x70);
MMP2_DEVICE(twsi5, "pxa2xx-i2c", 4, TWSI5, 0xd4033800, 0x70);
MMP2_DEVICE(twsi6, "pxa2xx-i2c", 5, TWSI6, 0xd4034000, 0x70);
MMP2_DEVICE(nand, "pxa3xx-nand", -1, न_अंकD, 0xd4283000, 0x100, 28, 29);
MMP2_DEVICE(sdh0, "sdhci-pxav3", 0, MMC, 0xd4280000, 0x120);
MMP2_DEVICE(sdh1, "sdhci-pxav3", 1, MMC2, 0xd4280800, 0x120);
MMP2_DEVICE(sdh2, "sdhci-pxav3", 2, MMC3, 0xd4281000, 0x120);
MMP2_DEVICE(sdh3, "sdhci-pxav3", 3, MMC4, 0xd4281800, 0x120);
MMP2_DEVICE(asram, "asram", -1, NONE, 0xe0000000, 0x4000);
/* 0xd1000000 ~ 0xd101ffff is reserved क्रम secure processor */
MMP2_DEVICE(isram, "isram", -1, NONE, 0xd1020000, 0x18000);

काष्ठा resource mmp2_resource_gpio[] = अणु
	अणु
		.start	= 0xd4019000,
		.end	= 0xd4019fff,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.start	= IRQ_MMP2_GPIO,
		.end	= IRQ_MMP2_GPIO,
		.name	= "gpio_mux",
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device mmp2_device_gpio = अणु
	.name		= "mmp2-gpio",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(mmp2_resource_gpio),
	.resource	= mmp2_resource_gpio,
पूर्ण;
