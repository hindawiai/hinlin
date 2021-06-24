<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2007 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *	http://armlinux.simtec.co.uk/
 *
 * S3C2443 घड़ी रेजिस्टर definitions
 */

#अगर_अघोषित __ASM_ARM_REGS_S3C2443_CLOCK
#घोषणा __ASM_ARM_REGS_S3C2443_CLOCK

#समावेश <linux/delay.h>
#समावेश "map-s3c.h"

#घोषणा S3C2443_CLKREG(x)		((x) + S3C24XX_VA_CLKPWR)

#घोषणा S3C2443_PLLCON_MDIVSHIFT	16
#घोषणा S3C2443_PLLCON_PDIVSHIFT	8
#घोषणा S3C2443_PLLCON_SDIVSHIFT	0
#घोषणा S3C2443_PLLCON_MDIVMASK		((1<<(1+(23-16)))-1)
#घोषणा S3C2443_PLLCON_PDIVMASK		((1<<(1+(9-8)))-1)
#घोषणा S3C2443_PLLCON_SDIVMASK		(3)

#घोषणा S3C2443_MPLLCON			S3C2443_CLKREG(0x10)
#घोषणा S3C2443_EPLLCON			S3C2443_CLKREG(0x18)
#घोषणा S3C2443_CLKSRC			S3C2443_CLKREG(0x20)
#घोषणा S3C2443_CLKDIV0			S3C2443_CLKREG(0x24)
#घोषणा S3C2443_CLKDIV1			S3C2443_CLKREG(0x28)
#घोषणा S3C2443_HCLKCON			S3C2443_CLKREG(0x30)
#घोषणा S3C2443_PCLKCON			S3C2443_CLKREG(0x34)
#घोषणा S3C2443_SCLKCON			S3C2443_CLKREG(0x38)
#घोषणा S3C2443_PWRMODE			S3C2443_CLKREG(0x40)
#घोषणा S3C2443_SWRST			S3C2443_CLKREG(0x44)
#घोषणा S3C2443_BUSPRI0			S3C2443_CLKREG(0x50)
#घोषणा S3C2443_SYSID			S3C2443_CLKREG(0x5C)
#घोषणा S3C2443_PWRCFG			S3C2443_CLKREG(0x60)
#घोषणा S3C2443_RSTCON			S3C2443_CLKREG(0x64)
#घोषणा S3C2443_PHYCTRL			S3C2443_CLKREG(0x80)
#घोषणा S3C2443_PHYPWR			S3C2443_CLKREG(0x84)
#घोषणा S3C2443_URSTCON			S3C2443_CLKREG(0x88)
#घोषणा S3C2443_UCLKCON			S3C2443_CLKREG(0x8C)

#घोषणा S3C2443_PLLCON_OFF		(1<<24)

#घोषणा S3C2443_CLKSRC_EPLLREF_XTAL	(2<<7)
#घोषणा S3C2443_CLKSRC_EPLLREF_EXTCLK	(3<<7)
#घोषणा S3C2443_CLKSRC_EPLLREF_MPLLREF	(0<<7)
#घोषणा S3C2443_CLKSRC_EPLLREF_MPLLREF2	(1<<7)
#घोषणा S3C2443_CLKSRC_EPLLREF_MASK	(3<<7)

#घोषणा S3C2443_CLKSRC_EXTCLK_DIV	(1<<3)

#घोषणा S3C2443_CLKDIV0_HALF_HCLK	(1<<3)
#घोषणा S3C2443_CLKDIV0_HALF_PCLK	(1<<2)

#घोषणा S3C2443_CLKDIV0_HCLKDIV_MASK	(3<<0)

#घोषणा S3C2443_CLKDIV0_EXTDIV_MASK	(3<<6)
#घोषणा S3C2443_CLKDIV0_EXTDIV_SHIFT	(6)

#घोषणा S3C2443_CLKDIV0_PREDIV_MASK	(3<<4)
#घोषणा S3C2443_CLKDIV0_PREDIV_SHIFT	(4)

#घोषणा S3C2416_CLKDIV0_ARMDIV_MASK	(7 << 9)
#घोषणा S3C2443_CLKDIV0_ARMDIV_MASK	(15<<9)
#घोषणा S3C2443_CLKDIV0_ARMDIV_SHIFT	(9)
#घोषणा S3C2443_CLKDIV0_ARMDIV_1	(0<<9)
#घोषणा S3C2443_CLKDIV0_ARMDIV_2	(8<<9)
#घोषणा S3C2443_CLKDIV0_ARMDIV_3	(2<<9)
#घोषणा S3C2443_CLKDIV0_ARMDIV_4	(9<<9)
#घोषणा S3C2443_CLKDIV0_ARMDIV_6	(10<<9)
#घोषणा S3C2443_CLKDIV0_ARMDIV_8	(11<<9)
#घोषणा S3C2443_CLKDIV0_ARMDIV_12	(13<<9)
#घोषणा S3C2443_CLKDIV0_ARMDIV_16	(15<<9)

/* S3C2443_CLKDIV1 हटाओd, only used in घड़ी.c code */

#घोषणा S3C2443_CLKCON_न_अंकD

#घोषणा S3C2443_HCLKCON_DMA0		(1<<0)
#घोषणा S3C2443_HCLKCON_DMA1		(1<<1)
#घोषणा S3C2443_HCLKCON_DMA2		(1<<2)
#घोषणा S3C2443_HCLKCON_DMA3		(1<<3)
#घोषणा S3C2443_HCLKCON_DMA4		(1<<4)
#घोषणा S3C2443_HCLKCON_DMA5		(1<<5)
#घोषणा S3C2443_HCLKCON_CAMIF		(1<<8)
#घोषणा S3C2443_HCLKCON_LCDC		(1<<9)
#घोषणा S3C2443_HCLKCON_USBH		(1<<11)
#घोषणा S3C2443_HCLKCON_USBD		(1<<12)
#घोषणा S3C2416_HCLKCON_HSMMC0		(1<<15)
#घोषणा S3C2443_HCLKCON_HSMMC		(1<<16)
#घोषणा S3C2443_HCLKCON_CFC		(1<<17)
#घोषणा S3C2443_HCLKCON_SSMC		(1<<18)
#घोषणा S3C2443_HCLKCON_DRAMC		(1<<19)

#घोषणा S3C2443_PCLKCON_UART0		(1<<0)
#घोषणा S3C2443_PCLKCON_UART1		(1<<1)
#घोषणा S3C2443_PCLKCON_UART2		(1<<2)
#घोषणा S3C2443_PCLKCON_UART3		(1<<3)
#घोषणा S3C2443_PCLKCON_IIC		(1<<4)
#घोषणा S3C2443_PCLKCON_SDI		(1<<5)
#घोषणा S3C2443_PCLKCON_HSSPI		(1<<6)
#घोषणा S3C2443_PCLKCON_ADC		(1<<7)
#घोषणा S3C2443_PCLKCON_AC97		(1<<8)
#घोषणा S3C2443_PCLKCON_IIS		(1<<9)
#घोषणा S3C2443_PCLKCON_PWMT		(1<<10)
#घोषणा S3C2443_PCLKCON_WDT		(1<<11)
#घोषणा S3C2443_PCLKCON_RTC		(1<<12)
#घोषणा S3C2443_PCLKCON_GPIO		(1<<13)
#घोषणा S3C2443_PCLKCON_SPI0		(1<<14)
#घोषणा S3C2443_PCLKCON_SPI1		(1<<15)

#घोषणा S3C2443_SCLKCON_DDRCLK		(1<<16)
#घोषणा S3C2443_SCLKCON_SSMCCLK		(1<<15)
#घोषणा S3C2443_SCLKCON_HSSPICLK	(1<<14)
#घोषणा S3C2443_SCLKCON_HSMMCCLK_EXT	(1<<13)
#घोषणा S3C2443_SCLKCON_HSMMCCLK_EPLL	(1<<12)
#घोषणा S3C2443_SCLKCON_CAMCLK		(1<<11)
#घोषणा S3C2443_SCLKCON_DISPCLK		(1<<10)
#घोषणा S3C2443_SCLKCON_I2SCLK		(1<<9)
#घोषणा S3C2443_SCLKCON_UARTCLK		(1<<8)
#घोषणा S3C2443_SCLKCON_USBHOST		(1<<1)

#घोषणा S3C2443_PWRCFG_SLEEP		(1<<15)

#घोषणा S3C2443_PWRCFG_USBPHY		(1 << 4)

#घोषणा S3C2443_URSTCON_FUNCRST		(1 << 2)
#घोषणा S3C2443_URSTCON_PHYRST		(1 << 0)

#घोषणा S3C2443_PHYCTRL_CLKSEL		(1 << 3)
#घोषणा S3C2443_PHYCTRL_EXTCLK		(1 << 2)
#घोषणा S3C2443_PHYCTRL_PLLSEL		(1 << 1)
#घोषणा S3C2443_PHYCTRL_DSPORT		(1 << 0)

#घोषणा S3C2443_PHYPWR_COMMON_ON	(1 << 31)
#घोषणा S3C2443_PHYPWR_ANALOG_PD	(1 << 4)
#घोषणा S3C2443_PHYPWR_PLL_REFCLK	(1 << 3)
#घोषणा S3C2443_PHYPWR_XO_ON		(1 << 2)
#घोषणा S3C2443_PHYPWR_PLL_PWRDN	(1 << 1)
#घोषणा S3C2443_PHYPWR_FSUSPEND		(1 << 0)

#घोषणा S3C2443_UCLKCON_DETECT_VBUS	(1 << 31)
#घोषणा S3C2443_UCLKCON_FUNC_CLKEN	(1 << 2)
#घोषणा S3C2443_UCLKCON_TCLKEN		(1 << 0)

#समावेश <यंत्र/भाग64.h>

अटल अंतरभूत अचिन्हित पूर्णांक
s3c2443_get_mpll(अचिन्हित पूर्णांक pllval, अचिन्हित पूर्णांक baseclk)
अणु
	अचिन्हित पूर्णांक mभाग, pभाग, sभाग;
	uपूर्णांक64_t fvco;

	mभाग = pllval >> S3C2443_PLLCON_MDIVSHIFT;
	pभाग = pllval >> S3C2443_PLLCON_PDIVSHIFT;
	sभाग = pllval >> S3C2443_PLLCON_SDIVSHIFT;

	mभाग &= S3C2443_PLLCON_MDIVMASK;
	pभाग &= S3C2443_PLLCON_PDIVMASK;
	sभाग &= S3C2443_PLLCON_SDIVMASK;

	fvco = (uपूर्णांक64_t)baseclk * (2 * (mभाग + 8));
	करो_भाग(fvco, pभाग << sभाग);

	वापस (अचिन्हित पूर्णांक)fvco;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
s3c2443_get_epll(अचिन्हित पूर्णांक pllval, अचिन्हित पूर्णांक baseclk)
अणु
	अचिन्हित पूर्णांक mभाग, pभाग, sभाग;
	uपूर्णांक64_t fvco;

	mभाग = pllval >> S3C2443_PLLCON_MDIVSHIFT;
	pभाग = pllval >> S3C2443_PLLCON_PDIVSHIFT;
	sभाग = pllval >> S3C2443_PLLCON_SDIVSHIFT;

	mभाग &= S3C2443_PLLCON_MDIVMASK;
	pभाग &= S3C2443_PLLCON_PDIVMASK;
	sभाग &= S3C2443_PLLCON_SDIVMASK;

	fvco = (uपूर्णांक64_t)baseclk * (mभाग + 8);
	करो_भाग(fvco, (pभाग + 2) << sभाग);

	वापस (अचिन्हित पूर्णांक)fvco;
पूर्ण

अटल अंतरभूत व्योम s3c_hsudc_init_phy(व्योम)
अणु
	u32 cfg;

	cfg = पढ़ोl(S3C2443_PWRCFG) | S3C2443_PWRCFG_USBPHY;
	ग_लिखोl(cfg, S3C2443_PWRCFG);

	cfg = पढ़ोl(S3C2443_URSTCON);
	cfg |= (S3C2443_URSTCON_FUNCRST | S3C2443_URSTCON_PHYRST);
	ग_लिखोl(cfg, S3C2443_URSTCON);
	mdelay(1);

	cfg = पढ़ोl(S3C2443_URSTCON);
	cfg &= ~(S3C2443_URSTCON_FUNCRST | S3C2443_URSTCON_PHYRST);
	ग_लिखोl(cfg, S3C2443_URSTCON);

	cfg = पढ़ोl(S3C2443_PHYCTRL);
	cfg &= ~(S3C2443_PHYCTRL_CLKSEL | S3C2443_PHYCTRL_DSPORT);
	cfg |= (S3C2443_PHYCTRL_EXTCLK | S3C2443_PHYCTRL_PLLSEL);
	ग_लिखोl(cfg, S3C2443_PHYCTRL);

	cfg = पढ़ोl(S3C2443_PHYPWR);
	cfg &= ~(S3C2443_PHYPWR_FSUSPEND | S3C2443_PHYPWR_PLL_PWRDN |
		S3C2443_PHYPWR_XO_ON | S3C2443_PHYPWR_PLL_REFCLK |
		S3C2443_PHYPWR_ANALOG_PD);
	cfg |= S3C2443_PHYPWR_COMMON_ON;
	ग_लिखोl(cfg, S3C2443_PHYPWR);

	cfg = पढ़ोl(S3C2443_UCLKCON);
	cfg |= (S3C2443_UCLKCON_DETECT_VBUS | S3C2443_UCLKCON_FUNC_CLKEN |
		S3C2443_UCLKCON_TCLKEN);
	ग_लिखोl(cfg, S3C2443_UCLKCON);
पूर्ण

अटल अंतरभूत व्योम s3c_hsudc_uninit_phy(व्योम)
अणु
	u32 cfg;

	cfg = पढ़ोl(S3C2443_PWRCFG) & ~S3C2443_PWRCFG_USBPHY;
	ग_लिखोl(cfg, S3C2443_PWRCFG);

	ग_लिखोl(S3C2443_PHYPWR_FSUSPEND, S3C2443_PHYPWR);

	cfg = पढ़ोl(S3C2443_UCLKCON) & ~S3C2443_UCLKCON_FUNC_CLKEN;
	ग_लिखोl(cfg, S3C2443_UCLKCON);
पूर्ण

#पूर्ण_अगर /*  __ASM_ARM_REGS_S3C2443_CLOCK */

