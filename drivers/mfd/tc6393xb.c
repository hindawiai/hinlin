<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Toshiba TC6393XB SoC support
 *
 * Copyright(c) 2005-2006 Chris Humbert
 * Copyright(c) 2005 Dirk Opfer
 * Copyright(c) 2005 Ian Molton <spyro@f2s.com>
 * Copyright(c) 2007 Dmitry Baryshkov
 *
 * Based on code written by Sharp/Lineo क्रम 2.4 kernels
 * Based on locomo.c
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/पंचांगपन.स>
#समावेश <linux/mfd/tc6393xb.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/slab.h>

#घोषणा SCR_REVID	0x08		/* b Revision ID	*/
#घोषणा SCR_ISR		0x50		/* b Interrupt Status	*/
#घोषणा SCR_IMR		0x52		/* b Interrupt Mask	*/
#घोषणा SCR_IRR		0x54		/* b Interrupt Routing	*/
#घोषणा SCR_GPER	0x60		/* w GP Enable		*/
#घोषणा SCR_GPI_SR(i)	(0x64 + (i))	/* b3 GPI Status	*/
#घोषणा SCR_GPI_IMR(i)	(0x68 + (i))	/* b3 GPI INT Mask	*/
#घोषणा SCR_GPI_EDER(i)	(0x6c + (i))	/* b3 GPI Edge Detect Enable */
#घोषणा SCR_GPI_LIR(i)	(0x70 + (i))	/* b3 GPI Level Invert	*/
#घोषणा SCR_GPO_DSR(i)	(0x78 + (i))	/* b3 GPO Data Set	*/
#घोषणा SCR_GPO_DOECR(i) (0x7c + (i))	/* b3 GPO Data OE Control */
#घोषणा SCR_GP_IARCR(i)	(0x80 + (i))	/* b3 GP Internal Active Register Control */
#घोषणा SCR_GP_IARLCR(i) (0x84 + (i))	/* b3 GP INTERNAL Active Register Level Control */
#घोषणा SCR_GPI_BCR(i)	(0x88 + (i))	/* b3 GPI Buffer Control */
#घोषणा SCR_GPA_IARCR	0x8c		/* w GPa Internal Active Register Control */
#घोषणा SCR_GPA_IARLCR	0x90		/* w GPa Internal Active Register Level Control */
#घोषणा SCR_GPA_BCR	0x94		/* w GPa Buffer Control */
#घोषणा SCR_CCR		0x98		/* w Clock Control	*/
#घोषणा SCR_PLL2CR	0x9a		/* w PLL2 Control	*/
#घोषणा SCR_PLL1CR	0x9c		/* l PLL1 Control	*/
#घोषणा SCR_DIARCR	0xa0		/* b Device Internal Active Register Control */
#घोषणा SCR_DBOCR	0xa1		/* b Device Buffer Off Control */
#घोषणा SCR_FER		0xe0		/* b Function Enable	*/
#घोषणा SCR_MCR		0xe4		/* w Mode Control	*/
#घोषणा SCR_CONFIG	0xfc		/* b Configuration Control */
#घोषणा SCR_DEBUG	0xff		/* b Debug		*/

#घोषणा SCR_CCR_CK32K	BIT(0)
#घोषणा SCR_CCR_USBCK	BIT(1)
#घोषणा SCR_CCR_UNK1	BIT(4)
#घोषणा SCR_CCR_MCLK_MASK	(7 << 8)
#घोषणा SCR_CCR_MCLK_OFF	(0 << 8)
#घोषणा SCR_CCR_MCLK_12	(1 << 8)
#घोषणा SCR_CCR_MCLK_24	(2 << 8)
#घोषणा SCR_CCR_MCLK_48	(3 << 8)
#घोषणा SCR_CCR_HCLK_MASK	(3 << 12)
#घोषणा SCR_CCR_HCLK_24	(0 << 12)
#घोषणा SCR_CCR_HCLK_48	(1 << 12)

#घोषणा SCR_FER_USBEN		BIT(0)	/* USB host enable */
#घोषणा SCR_FER_LCDCVEN		BIT(1)	/* polysilicon TFT enable */
#घोषणा SCR_FER_SLCDEN		BIT(2)	/* SLCD enable */

#घोषणा SCR_MCR_RDY_MASK		(3 << 0)
#घोषणा SCR_MCR_RDY_OPENDRAIN	(0 << 0)
#घोषणा SCR_MCR_RDY_TRISTATE	(1 << 0)
#घोषणा SCR_MCR_RDY_PUSHPULL	(2 << 0)
#घोषणा SCR_MCR_RDY_UNK		BIT(2)
#घोषणा SCR_MCR_RDY_EN		BIT(3)
#घोषणा SCR_MCR_INT_MASK		(3 << 4)
#घोषणा SCR_MCR_INT_OPENDRAIN	(0 << 4)
#घोषणा SCR_MCR_INT_TRISTATE	(1 << 4)
#घोषणा SCR_MCR_INT_PUSHPULL	(2 << 4)
#घोषणा SCR_MCR_INT_UNK		BIT(6)
#घोषणा SCR_MCR_INT_EN		BIT(7)
/* bits 8 - 16 are unknown */

#घोषणा TC_GPIO_BIT(i)		(1 << (i & 0x7))

/*--------------------------------------------------------------------------*/

काष्ठा tc6393xb अणु
	व्योम __iomem		*scr;

	काष्ठा gpio_chip	gpio;

	काष्ठा clk		*clk; /* 3,6 Mhz */

	raw_spinlock_t		lock; /* protects RMW cycles */

	काष्ठा अणु
		u8		fer;
		u16		ccr;
		u8		gpi_bcr[3];
		u8		gpo_dsr[3];
		u8		gpo_करोecr[3];
	पूर्ण suspend_state;

	काष्ठा resource		rscr;
	काष्ठा resource		*iomem;
	पूर्णांक			irq;
	पूर्णांक			irq_base;
पूर्ण;

क्रमागत अणु
	TC6393XB_CELL_न_अंकD,
	TC6393XB_CELL_MMC,
	TC6393XB_CELL_OHCI,
	TC6393XB_CELL_FB,
पूर्ण;

/*--------------------------------------------------------------------------*/

अटल पूर्णांक tc6393xb_nand_enable(काष्ठा platक्रमm_device *nand)
अणु
	काष्ठा tc6393xb *tc6393xb = dev_get_drvdata(nand->dev.parent);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&tc6393xb->lock, flags);

	/* SMD buffer on */
	dev_dbg(nand->dev.parent, "SMD buffer on\n");
	पंचांगio_ioग_लिखो8(0xff, tc6393xb->scr + SCR_GPI_BCR(1));

	raw_spin_unlock_irqrestore(&tc6393xb->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा resource tc6393xb_nand_resources[] = अणु
	अणु
		.start	= 0x1000,
		.end	= 0x1007,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= 0x0100,
		.end	= 0x01ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= IRQ_TC6393_न_अंकD,
		.end	= IRQ_TC6393_न_अंकD,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource tc6393xb_mmc_resources[] = अणु
	अणु
		.start	= 0x800,
		.end	= 0x9ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= IRQ_TC6393_MMC,
		.end	= IRQ_TC6393_MMC,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource tc6393xb_ohci_resources[] = अणु
	अणु
		.start	= 0x3000,
		.end	= 0x31ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= 0x0300,
		.end	= 0x03ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= 0x010000,
		.end	= 0x017fff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= 0x018000,
		.end	= 0x01ffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= IRQ_TC6393_OHCI,
		.end	= IRQ_TC6393_OHCI,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource tc6393xb_fb_resources[] = अणु
	अणु
		.start	= 0x5000,
		.end	= 0x51ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= 0x0500,
		.end	= 0x05ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= 0x100000,
		.end	= 0x1fffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= IRQ_TC6393_FB,
		.end	= IRQ_TC6393_FB,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल पूर्णांक tc6393xb_ohci_enable(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा tc6393xb *tc6393xb = dev_get_drvdata(dev->dev.parent);
	अचिन्हित दीर्घ flags;
	u16 ccr;
	u8 fer;

	raw_spin_lock_irqsave(&tc6393xb->lock, flags);

	ccr = पंचांगio_ioपढ़ो16(tc6393xb->scr + SCR_CCR);
	ccr |= SCR_CCR_USBCK;
	पंचांगio_ioग_लिखो16(ccr, tc6393xb->scr + SCR_CCR);

	fer = पंचांगio_ioपढ़ो8(tc6393xb->scr + SCR_FER);
	fer |= SCR_FER_USBEN;
	पंचांगio_ioग_लिखो8(fer, tc6393xb->scr + SCR_FER);

	raw_spin_unlock_irqrestore(&tc6393xb->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक tc6393xb_ohci_disable(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा tc6393xb *tc6393xb = dev_get_drvdata(dev->dev.parent);
	अचिन्हित दीर्घ flags;
	u16 ccr;
	u8 fer;

	raw_spin_lock_irqsave(&tc6393xb->lock, flags);

	fer = पंचांगio_ioपढ़ो8(tc6393xb->scr + SCR_FER);
	fer &= ~SCR_FER_USBEN;
	पंचांगio_ioग_लिखो8(fer, tc6393xb->scr + SCR_FER);

	ccr = पंचांगio_ioपढ़ो16(tc6393xb->scr + SCR_CCR);
	ccr &= ~SCR_CCR_USBCK;
	पंचांगio_ioग_लिखो16(ccr, tc6393xb->scr + SCR_CCR);

	raw_spin_unlock_irqrestore(&tc6393xb->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक tc6393xb_ohci_suspend(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा tc6393xb_platक्रमm_data *tcpd = dev_get_platdata(dev->dev.parent);

	/* We can't properly store/restore OHCI state, so fail here */
	अगर (tcpd->resume_restore)
		वापस -EBUSY;

	वापस tc6393xb_ohci_disable(dev);
पूर्ण

अटल पूर्णांक tc6393xb_fb_enable(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा tc6393xb *tc6393xb = dev_get_drvdata(dev->dev.parent);
	अचिन्हित दीर्घ flags;
	u16 ccr;

	raw_spin_lock_irqsave(&tc6393xb->lock, flags);

	ccr = पंचांगio_ioपढ़ो16(tc6393xb->scr + SCR_CCR);
	ccr &= ~SCR_CCR_MCLK_MASK;
	ccr |= SCR_CCR_MCLK_48;
	पंचांगio_ioग_लिखो16(ccr, tc6393xb->scr + SCR_CCR);

	raw_spin_unlock_irqrestore(&tc6393xb->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक tc6393xb_fb_disable(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा tc6393xb *tc6393xb = dev_get_drvdata(dev->dev.parent);
	अचिन्हित दीर्घ flags;
	u16 ccr;

	raw_spin_lock_irqsave(&tc6393xb->lock, flags);

	ccr = पंचांगio_ioपढ़ो16(tc6393xb->scr + SCR_CCR);
	ccr &= ~SCR_CCR_MCLK_MASK;
	ccr |= SCR_CCR_MCLK_OFF;
	पंचांगio_ioग_लिखो16(ccr, tc6393xb->scr + SCR_CCR);

	raw_spin_unlock_irqrestore(&tc6393xb->lock, flags);

	वापस 0;
पूर्ण

पूर्णांक tc6393xb_lcd_set_घातer(काष्ठा platक्रमm_device *fb, bool on)
अणु
	काष्ठा tc6393xb *tc6393xb = dev_get_drvdata(fb->dev.parent);
	u8 fer;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&tc6393xb->lock, flags);

	fer = ioपढ़ो8(tc6393xb->scr + SCR_FER);
	अगर (on)
		fer |= SCR_FER_SLCDEN;
	अन्यथा
		fer &= ~SCR_FER_SLCDEN;
	ioग_लिखो8(fer, tc6393xb->scr + SCR_FER);

	raw_spin_unlock_irqrestore(&tc6393xb->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tc6393xb_lcd_set_घातer);

पूर्णांक tc6393xb_lcd_mode(काष्ठा platक्रमm_device *fb,
					स्थिर काष्ठा fb_videomode *mode) अणु
	काष्ठा tc6393xb *tc6393xb = dev_get_drvdata(fb->dev.parent);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&tc6393xb->lock, flags);

	ioग_लिखो16(mode->pixघड़ी, tc6393xb->scr + SCR_PLL1CR + 0);
	ioग_लिखो16(mode->pixघड़ी >> 16, tc6393xb->scr + SCR_PLL1CR + 2);

	raw_spin_unlock_irqrestore(&tc6393xb->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tc6393xb_lcd_mode);

अटल पूर्णांक tc6393xb_mmc_enable(काष्ठा platक्रमm_device *mmc)
अणु
	काष्ठा tc6393xb *tc6393xb = dev_get_drvdata(mmc->dev.parent);

	पंचांगio_core_mmc_enable(tc6393xb->scr + 0x200, 0,
		tc6393xb_mmc_resources[0].start & 0xfffe);

	वापस 0;
पूर्ण

अटल पूर्णांक tc6393xb_mmc_resume(काष्ठा platक्रमm_device *mmc)
अणु
	काष्ठा tc6393xb *tc6393xb = dev_get_drvdata(mmc->dev.parent);

	पंचांगio_core_mmc_resume(tc6393xb->scr + 0x200, 0,
		tc6393xb_mmc_resources[0].start & 0xfffe);

	वापस 0;
पूर्ण

अटल व्योम tc6393xb_mmc_pwr(काष्ठा platक्रमm_device *mmc, पूर्णांक state)
अणु
	काष्ठा tc6393xb *tc6393xb = dev_get_drvdata(mmc->dev.parent);

	पंचांगio_core_mmc_pwr(tc6393xb->scr + 0x200, 0, state);
पूर्ण

अटल व्योम tc6393xb_mmc_clk_भाग(काष्ठा platक्रमm_device *mmc, पूर्णांक state)
अणु
	काष्ठा tc6393xb *tc6393xb = dev_get_drvdata(mmc->dev.parent);

	पंचांगio_core_mmc_clk_भाग(tc6393xb->scr + 0x200, 0, state);
पूर्ण

अटल काष्ठा पंचांगio_mmc_data tc6393xb_mmc_data = अणु
	.hclk = 24000000,
	.set_pwr = tc6393xb_mmc_pwr,
	.set_clk_भाग = tc6393xb_mmc_clk_भाग,
पूर्ण;

अटल काष्ठा mfd_cell tc6393xb_cells[] = अणु
	[TC6393XB_CELL_न_अंकD] = अणु
		.name = "tmio-nand",
		.enable = tc6393xb_nand_enable,
		.num_resources = ARRAY_SIZE(tc6393xb_nand_resources),
		.resources = tc6393xb_nand_resources,
	पूर्ण,
	[TC6393XB_CELL_MMC] = अणु
		.name = "tmio-mmc",
		.enable = tc6393xb_mmc_enable,
		.resume = tc6393xb_mmc_resume,
		.platक्रमm_data = &tc6393xb_mmc_data,
		.pdata_size    = माप(tc6393xb_mmc_data),
		.num_resources = ARRAY_SIZE(tc6393xb_mmc_resources),
		.resources = tc6393xb_mmc_resources,
	पूर्ण,
	[TC6393XB_CELL_OHCI] = अणु
		.name = "tmio-ohci",
		.num_resources = ARRAY_SIZE(tc6393xb_ohci_resources),
		.resources = tc6393xb_ohci_resources,
		.enable = tc6393xb_ohci_enable,
		.suspend = tc6393xb_ohci_suspend,
		.resume = tc6393xb_ohci_enable,
		.disable = tc6393xb_ohci_disable,
	पूर्ण,
	[TC6393XB_CELL_FB] = अणु
		.name = "tmio-fb",
		.num_resources = ARRAY_SIZE(tc6393xb_fb_resources),
		.resources = tc6393xb_fb_resources,
		.enable = tc6393xb_fb_enable,
		.suspend = tc6393xb_fb_disable,
		.resume = tc6393xb_fb_enable,
		.disable = tc6393xb_fb_disable,
	पूर्ण,
पूर्ण;

/*--------------------------------------------------------------------------*/

अटल पूर्णांक tc6393xb_gpio_get(काष्ठा gpio_chip *chip,
		अचिन्हित offset)
अणु
	काष्ठा tc6393xb *tc6393xb = gpiochip_get_data(chip);

	/* XXX: करोes dsr also represent inमाला_दो? */
	वापस !!(पंचांगio_ioपढ़ो8(tc6393xb->scr + SCR_GPO_DSR(offset / 8))
		  & TC_GPIO_BIT(offset));
पूर्ण

अटल व्योम __tc6393xb_gpio_set(काष्ठा gpio_chip *chip,
		अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा tc6393xb *tc6393xb = gpiochip_get_data(chip);
	u8  dsr;

	dsr = पंचांगio_ioपढ़ो8(tc6393xb->scr + SCR_GPO_DSR(offset / 8));
	अगर (value)
		dsr |= TC_GPIO_BIT(offset);
	अन्यथा
		dsr &= ~TC_GPIO_BIT(offset);

	पंचांगio_ioग_लिखो8(dsr, tc6393xb->scr + SCR_GPO_DSR(offset / 8));
पूर्ण

अटल व्योम tc6393xb_gpio_set(काष्ठा gpio_chip *chip,
		अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा tc6393xb *tc6393xb = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&tc6393xb->lock, flags);

	__tc6393xb_gpio_set(chip, offset, value);

	raw_spin_unlock_irqrestore(&tc6393xb->lock, flags);
पूर्ण

अटल पूर्णांक tc6393xb_gpio_direction_input(काष्ठा gpio_chip *chip,
			अचिन्हित offset)
अणु
	काष्ठा tc6393xb *tc6393xb = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	u8 करोecr;

	raw_spin_lock_irqsave(&tc6393xb->lock, flags);

	करोecr = पंचांगio_ioपढ़ो8(tc6393xb->scr + SCR_GPO_DOECR(offset / 8));
	करोecr &= ~TC_GPIO_BIT(offset);
	पंचांगio_ioग_लिखो8(करोecr, tc6393xb->scr + SCR_GPO_DOECR(offset / 8));

	raw_spin_unlock_irqrestore(&tc6393xb->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक tc6393xb_gpio_direction_output(काष्ठा gpio_chip *chip,
			अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा tc6393xb *tc6393xb = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	u8 करोecr;

	raw_spin_lock_irqsave(&tc6393xb->lock, flags);

	__tc6393xb_gpio_set(chip, offset, value);

	करोecr = पंचांगio_ioपढ़ो8(tc6393xb->scr + SCR_GPO_DOECR(offset / 8));
	करोecr |= TC_GPIO_BIT(offset);
	पंचांगio_ioग_लिखो8(करोecr, tc6393xb->scr + SCR_GPO_DOECR(offset / 8));

	raw_spin_unlock_irqrestore(&tc6393xb->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक tc6393xb_रेजिस्टर_gpio(काष्ठा tc6393xb *tc6393xb, पूर्णांक gpio_base)
अणु
	tc6393xb->gpio.label = "tc6393xb";
	tc6393xb->gpio.base = gpio_base;
	tc6393xb->gpio.ngpio = 16;
	tc6393xb->gpio.set = tc6393xb_gpio_set;
	tc6393xb->gpio.get = tc6393xb_gpio_get;
	tc6393xb->gpio.direction_input = tc6393xb_gpio_direction_input;
	tc6393xb->gpio.direction_output = tc6393xb_gpio_direction_output;

	वापस gpiochip_add_data(&tc6393xb->gpio, tc6393xb);
पूर्ण

/*--------------------------------------------------------------------------*/

अटल व्योम tc6393xb_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा tc6393xb *tc6393xb = irq_desc_get_handler_data(desc);
	अचिन्हित पूर्णांक isr;
	अचिन्हित पूर्णांक i, irq_base;

	irq_base = tc6393xb->irq_base;

	जबतक ((isr = पंचांगio_ioपढ़ो8(tc6393xb->scr + SCR_ISR) &
				~पंचांगio_ioपढ़ो8(tc6393xb->scr + SCR_IMR)))
		क्रम (i = 0; i < TC6393XB_NR_IRQS; i++) अणु
			अगर (isr & (1 << i))
				generic_handle_irq(irq_base + i);
		पूर्ण
पूर्ण

अटल व्योम tc6393xb_irq_ack(काष्ठा irq_data *data)
अणु
पूर्ण

अटल व्योम tc6393xb_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा tc6393xb *tc6393xb = irq_data_get_irq_chip_data(data);
	अचिन्हित दीर्घ flags;
	u8 imr;

	raw_spin_lock_irqsave(&tc6393xb->lock, flags);
	imr = पंचांगio_ioपढ़ो8(tc6393xb->scr + SCR_IMR);
	imr |= 1 << (data->irq - tc6393xb->irq_base);
	पंचांगio_ioग_लिखो8(imr, tc6393xb->scr + SCR_IMR);
	raw_spin_unlock_irqrestore(&tc6393xb->lock, flags);
पूर्ण

अटल व्योम tc6393xb_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा tc6393xb *tc6393xb = irq_data_get_irq_chip_data(data);
	अचिन्हित दीर्घ flags;
	u8 imr;

	raw_spin_lock_irqsave(&tc6393xb->lock, flags);
	imr = पंचांगio_ioपढ़ो8(tc6393xb->scr + SCR_IMR);
	imr &= ~(1 << (data->irq - tc6393xb->irq_base));
	पंचांगio_ioग_लिखो8(imr, tc6393xb->scr + SCR_IMR);
	raw_spin_unlock_irqrestore(&tc6393xb->lock, flags);
पूर्ण

अटल काष्ठा irq_chip tc6393xb_chip = अणु
	.name		= "tc6393xb",
	.irq_ack	= tc6393xb_irq_ack,
	.irq_mask	= tc6393xb_irq_mask,
	.irq_unmask	= tc6393xb_irq_unmask,
पूर्ण;

अटल व्योम tc6393xb_attach_irq(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा tc6393xb *tc6393xb = platक्रमm_get_drvdata(dev);
	अचिन्हित पूर्णांक irq, irq_base;

	irq_base = tc6393xb->irq_base;

	क्रम (irq = irq_base; irq < irq_base + TC6393XB_NR_IRQS; irq++) अणु
		irq_set_chip_and_handler(irq, &tc6393xb_chip, handle_edge_irq);
		irq_set_chip_data(irq, tc6393xb);
		irq_clear_status_flags(irq, IRQ_NOREQUEST | IRQ_NOPROBE);
	पूर्ण

	irq_set_irq_type(tc6393xb->irq, IRQ_TYPE_EDGE_FALLING);
	irq_set_chained_handler_and_data(tc6393xb->irq, tc6393xb_irq,
					 tc6393xb);
पूर्ण

अटल व्योम tc6393xb_detach_irq(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा tc6393xb *tc6393xb = platक्रमm_get_drvdata(dev);
	अचिन्हित पूर्णांक irq, irq_base;

	irq_set_chained_handler_and_data(tc6393xb->irq, शून्य, शून्य);

	irq_base = tc6393xb->irq_base;

	क्रम (irq = irq_base; irq < irq_base + TC6393XB_NR_IRQS; irq++) अणु
		irq_set_status_flags(irq, IRQ_NOREQUEST | IRQ_NOPROBE);
		irq_set_chip(irq, शून्य);
		irq_set_chip_data(irq, शून्य);
	पूर्ण
पूर्ण

/*--------------------------------------------------------------------------*/

अटल पूर्णांक tc6393xb_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा tc6393xb_platक्रमm_data *tcpd = dev_get_platdata(&dev->dev);
	काष्ठा tc6393xb *tc6393xb;
	काष्ठा resource *iomem, *rscr;
	पूर्णांक ret;

	iomem = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (!iomem)
		वापस -EINVAL;

	tc6393xb = kzalloc(माप *tc6393xb, GFP_KERNEL);
	अगर (!tc6393xb) अणु
		ret = -ENOMEM;
		जाओ err_kzalloc;
	पूर्ण

	raw_spin_lock_init(&tc6393xb->lock);

	platक्रमm_set_drvdata(dev, tc6393xb);

	ret = platक्रमm_get_irq(dev, 0);
	अगर (ret >= 0)
		tc6393xb->irq = ret;
	अन्यथा
		जाओ err_noirq;

	tc6393xb->iomem = iomem;
	tc6393xb->irq_base = tcpd->irq_base;

	tc6393xb->clk = clk_get(&dev->dev, "CLK_CK3P6MI");
	अगर (IS_ERR(tc6393xb->clk)) अणु
		ret = PTR_ERR(tc6393xb->clk);
		जाओ err_clk_get;
	पूर्ण

	rscr = &tc6393xb->rscr;
	rscr->name = "tc6393xb-core";
	rscr->start = iomem->start;
	rscr->end = iomem->start + 0xff;
	rscr->flags = IORESOURCE_MEM;

	ret = request_resource(iomem, rscr);
	अगर (ret)
		जाओ err_request_scr;

	tc6393xb->scr = ioremap(rscr->start, resource_size(rscr));
	अगर (!tc6393xb->scr) अणु
		ret = -ENOMEM;
		जाओ err_ioremap;
	पूर्ण

	ret = clk_prepare_enable(tc6393xb->clk);
	अगर (ret)
		जाओ err_clk_enable;

	ret = tcpd->enable(dev);
	अगर (ret)
		जाओ err_enable;

	ioग_लिखो8(0,				tc6393xb->scr + SCR_FER);
	ioग_लिखो16(tcpd->scr_pll2cr,		tc6393xb->scr + SCR_PLL2CR);
	ioग_लिखो16(SCR_CCR_UNK1 | SCR_CCR_HCLK_48,
						tc6393xb->scr + SCR_CCR);
	ioग_लिखो16(SCR_MCR_RDY_OPENDRAIN | SCR_MCR_RDY_UNK | SCR_MCR_RDY_EN |
		  SCR_MCR_INT_OPENDRAIN | SCR_MCR_INT_UNK | SCR_MCR_INT_EN |
		  BIT(15),			tc6393xb->scr + SCR_MCR);
	ioग_लिखो16(tcpd->scr_gper,		tc6393xb->scr + SCR_GPER);
	ioग_लिखो8(0,				tc6393xb->scr + SCR_IRR);
	ioग_लिखो8(0xbf,				tc6393xb->scr + SCR_IMR);

	prपूर्णांकk(KERN_INFO "Toshiba tc6393xb revision %d at 0x%08lx, irq %d\n",
			पंचांगio_ioपढ़ो8(tc6393xb->scr + SCR_REVID),
			(अचिन्हित दीर्घ) iomem->start, tc6393xb->irq);

	tc6393xb->gpio.base = -1;

	अगर (tcpd->gpio_base >= 0) अणु
		ret = tc6393xb_रेजिस्टर_gpio(tc6393xb, tcpd->gpio_base);
		अगर (ret)
			जाओ err_gpio_add;
	पूर्ण

	tc6393xb_attach_irq(dev);

	अगर (tcpd->setup) अणु
		ret = tcpd->setup(dev);
		अगर (ret)
			जाओ err_setup;
	पूर्ण

	tc6393xb_cells[TC6393XB_CELL_न_अंकD].platक्रमm_data = tcpd->nand_data;
	tc6393xb_cells[TC6393XB_CELL_न_अंकD].pdata_size =
						माप(*tcpd->nand_data);
	tc6393xb_cells[TC6393XB_CELL_FB].platक्रमm_data = tcpd->fb_data;
	tc6393xb_cells[TC6393XB_CELL_FB].pdata_size = माप(*tcpd->fb_data);

	ret = mfd_add_devices(&dev->dev, dev->id,
			      tc6393xb_cells, ARRAY_SIZE(tc6393xb_cells),
			      iomem, tcpd->irq_base, शून्य);

	अगर (!ret)
		वापस 0;

	अगर (tcpd->tearकरोwn)
		tcpd->tearकरोwn(dev);

err_setup:
	tc6393xb_detach_irq(dev);

err_gpio_add:
	अगर (tc6393xb->gpio.base != -1)
		gpiochip_हटाओ(&tc6393xb->gpio);
	tcpd->disable(dev);
err_enable:
	clk_disable_unprepare(tc6393xb->clk);
err_clk_enable:
	iounmap(tc6393xb->scr);
err_ioremap:
	release_resource(&tc6393xb->rscr);
err_request_scr:
	clk_put(tc6393xb->clk);
err_noirq:
err_clk_get:
	kमुक्त(tc6393xb);
err_kzalloc:
	वापस ret;
पूर्ण

अटल पूर्णांक tc6393xb_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा tc6393xb_platक्रमm_data *tcpd = dev_get_platdata(&dev->dev);
	काष्ठा tc6393xb *tc6393xb = platक्रमm_get_drvdata(dev);
	पूर्णांक ret;

	mfd_हटाओ_devices(&dev->dev);

	अगर (tcpd->tearकरोwn)
		tcpd->tearकरोwn(dev);

	tc6393xb_detach_irq(dev);

	अगर (tc6393xb->gpio.base != -1)
		gpiochip_हटाओ(&tc6393xb->gpio);

	ret = tcpd->disable(dev);
	clk_disable_unprepare(tc6393xb->clk);
	iounmap(tc6393xb->scr);
	release_resource(&tc6393xb->rscr);
	clk_put(tc6393xb->clk);
	kमुक्त(tc6393xb);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक tc6393xb_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	काष्ठा tc6393xb_platक्रमm_data *tcpd = dev_get_platdata(&dev->dev);
	काष्ठा tc6393xb *tc6393xb = platक्रमm_get_drvdata(dev);
	पूर्णांक i, ret;

	tc6393xb->suspend_state.ccr = ioपढ़ो16(tc6393xb->scr + SCR_CCR);
	tc6393xb->suspend_state.fer = ioपढ़ो8(tc6393xb->scr + SCR_FER);

	क्रम (i = 0; i < 3; i++) अणु
		tc6393xb->suspend_state.gpo_dsr[i] =
			ioपढ़ो8(tc6393xb->scr + SCR_GPO_DSR(i));
		tc6393xb->suspend_state.gpo_करोecr[i] =
			ioपढ़ो8(tc6393xb->scr + SCR_GPO_DOECR(i));
		tc6393xb->suspend_state.gpi_bcr[i] =
			ioपढ़ो8(tc6393xb->scr + SCR_GPI_BCR(i));
	पूर्ण
	ret = tcpd->suspend(dev);
	clk_disable_unprepare(tc6393xb->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक tc6393xb_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा tc6393xb_platक्रमm_data *tcpd = dev_get_platdata(&dev->dev);
	काष्ठा tc6393xb *tc6393xb = platक्रमm_get_drvdata(dev);
	पूर्णांक ret;
	पूर्णांक i;

	ret = clk_prepare_enable(tc6393xb->clk);
	अगर (ret)
		वापस ret;

	ret = tcpd->resume(dev);
	अगर (ret)
		वापस ret;

	अगर (!tcpd->resume_restore)
		वापस 0;

	ioग_लिखो8(tc6393xb->suspend_state.fer,	tc6393xb->scr + SCR_FER);
	ioग_लिखो16(tcpd->scr_pll2cr,		tc6393xb->scr + SCR_PLL2CR);
	ioग_लिखो16(tc6393xb->suspend_state.ccr,	tc6393xb->scr + SCR_CCR);
	ioग_लिखो16(SCR_MCR_RDY_OPENDRAIN | SCR_MCR_RDY_UNK | SCR_MCR_RDY_EN |
		  SCR_MCR_INT_OPENDRAIN | SCR_MCR_INT_UNK | SCR_MCR_INT_EN |
		  BIT(15),			tc6393xb->scr + SCR_MCR);
	ioग_लिखो16(tcpd->scr_gper,		tc6393xb->scr + SCR_GPER);
	ioग_लिखो8(0,				tc6393xb->scr + SCR_IRR);
	ioग_लिखो8(0xbf,				tc6393xb->scr + SCR_IMR);

	क्रम (i = 0; i < 3; i++) अणु
		ioग_लिखो8(tc6393xb->suspend_state.gpo_dsr[i],
					tc6393xb->scr + SCR_GPO_DSR(i));
		ioग_लिखो8(tc6393xb->suspend_state.gpo_करोecr[i],
					tc6393xb->scr + SCR_GPO_DOECR(i));
		ioग_लिखो8(tc6393xb->suspend_state.gpi_bcr[i],
					tc6393xb->scr + SCR_GPI_BCR(i));
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा tc6393xb_suspend शून्य
#घोषणा tc6393xb_resume शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver tc6393xb_driver = अणु
	.probe = tc6393xb_probe,
	.हटाओ = tc6393xb_हटाओ,
	.suspend = tc6393xb_suspend,
	.resume = tc6393xb_resume,

	.driver = अणु
		.name = "tc6393xb",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init tc6393xb_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&tc6393xb_driver);
पूर्ण

अटल व्योम __निकास tc6393xb_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&tc6393xb_driver);
पूर्ण

subsys_initcall(tc6393xb_init);
module_निकास(tc6393xb_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Ian Molton, Dmitry Baryshkov and Dirk Opfer");
MODULE_DESCRIPTION("tc6393xb Toshiba Mobile IO Controller");
MODULE_ALIAS("platform:tc6393xb");

