<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-mmp/devices.c
 */

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/irq.h>
#समावेश "irqs.h"
#समावेश "devices.h"
#समावेश <linux/soc/mmp/cputype.h>
#समावेश "regs-usb.h"

पूर्णांक __init pxa_रेजिस्टर_device(काष्ठा pxa_device_desc *desc,
				व्योम *data, माप_प्रकार size)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा resource res[2 + MAX_RESOURCE_DMA];
	पूर्णांक i, ret = 0, nres = 0;

	pdev = platक्रमm_device_alloc(desc->drv_name, desc->id);
	अगर (pdev == शून्य)
		वापस -ENOMEM;

	pdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);

	स_रखो(res, 0, माप(res));

	अगर (desc->start != -1ul && desc->size > 0) अणु
		res[nres].start	= desc->start;
		res[nres].end	= desc->start + desc->size - 1;
		res[nres].flags	= IORESOURCE_MEM;
		nres++;
	पूर्ण

	अगर (desc->irq != NO_IRQ) अणु
		res[nres].start	= desc->irq;
		res[nres].end	= desc->irq;
		res[nres].flags	= IORESOURCE_IRQ;
		nres++;
	पूर्ण

	क्रम (i = 0; i < MAX_RESOURCE_DMA; i++, nres++) अणु
		अगर (desc->dma[i] == 0)
			अवरोध;

		res[nres].start	= desc->dma[i];
		res[nres].end	= desc->dma[i];
		res[nres].flags	= IORESOURCE_DMA;
	पूर्ण

	ret = platक्रमm_device_add_resources(pdev, res, nres);
	अगर (ret) अणु
		platक्रमm_device_put(pdev);
		वापस ret;
	पूर्ण

	अगर (data && size) अणु
		ret = platक्रमm_device_add_data(pdev, data, size);
		अगर (ret) अणु
			platक्रमm_device_put(pdev);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस platक्रमm_device_add(pdev);
पूर्ण

#अगर IS_ENABLED(CONFIG_USB) || IS_ENABLED(CONFIG_USB_GADGET)
#अगर IS_ENABLED(CONFIG_USB_MV_UDC) || IS_ENABLED(CONFIG_USB_EHCI_MV)
#अगर IS_ENABLED(CONFIG_CPU_PXA910) || IS_ENABLED(CONFIG_CPU_PXA168)

/*****************************************************************************
 * The रेजिस्टरs पढ़ो/ग_लिखो routines
 *****************************************************************************/

अटल अचिन्हित पूर्णांक u2o_get(व्योम __iomem *base, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl_relaxed(base + offset);
पूर्ण

अटल व्योम u2o_set(व्योम __iomem *base, अचिन्हित पूर्णांक offset,
		अचिन्हित पूर्णांक value)
अणु
	u32 reg;

	reg = पढ़ोl_relaxed(base + offset);
	reg |= value;
	ग_लिखोl_relaxed(reg, base + offset);
	पढ़ोl_relaxed(base + offset);
पूर्ण

अटल व्योम u2o_clear(व्योम __iomem *base, अचिन्हित पूर्णांक offset,
		अचिन्हित पूर्णांक value)
अणु
	u32 reg;

	reg = पढ़ोl_relaxed(base + offset);
	reg &= ~value;
	ग_लिखोl_relaxed(reg, base + offset);
	पढ़ोl_relaxed(base + offset);
पूर्ण

अटल व्योम u2o_ग_लिखो(व्योम __iomem *base, अचिन्हित पूर्णांक offset,
		अचिन्हित पूर्णांक value)
अणु
	ग_लिखोl_relaxed(value, base + offset);
	पढ़ोl_relaxed(base + offset);
पूर्ण


अटल DEFINE_MUTEX(phy_lock);
अटल पूर्णांक phy_init_cnt;

अटल पूर्णांक usb_phy_init_पूर्णांकernal(व्योम __iomem *base)
अणु
	पूर्णांक loops;

	pr_info("Init usb phy!!!\n");

	/* Initialize the USB PHY घातer */
	अगर (cpu_is_pxa910()) अणु
		u2o_set(base, UTMI_CTRL, (1<<UTMI_CTRL_INPKT_DELAY_SOF_SHIFT)
			| (1<<UTMI_CTRL_PU_REF_SHIFT));
	पूर्ण

	u2o_set(base, UTMI_CTRL, 1<<UTMI_CTRL_PLL_PWR_UP_SHIFT);
	u2o_set(base, UTMI_CTRL, 1<<UTMI_CTRL_PWR_UP_SHIFT);

	/* UTMI_PLL settings */
	u2o_clear(base, UTMI_PLL, UTMI_PLL_PLLVDD18_MASK
		| UTMI_PLL_PLLVDD12_MASK | UTMI_PLL_PLLCALI12_MASK
		| UTMI_PLL_FBDIV_MASK | UTMI_PLL_REFDIV_MASK
		| UTMI_PLL_ICP_MASK | UTMI_PLL_KVCO_MASK);

	u2o_set(base, UTMI_PLL, 0xee<<UTMI_PLL_FBDIV_SHIFT
		| 0xb<<UTMI_PLL_REFDIV_SHIFT | 3<<UTMI_PLL_PLLVDD18_SHIFT
		| 3<<UTMI_PLL_PLLVDD12_SHIFT | 3<<UTMI_PLL_PLLCALI12_SHIFT
		| 1<<UTMI_PLL_ICP_SHIFT | 3<<UTMI_PLL_KVCO_SHIFT);

	/* UTMI_TX */
	u2o_clear(base, UTMI_TX, UTMI_TX_REG_EXT_FS_RCAL_EN_MASK
		| UTMI_TX_TXVDD12_MASK | UTMI_TX_CK60_PHSEL_MASK
		| UTMI_TX_IMPCAL_VTH_MASK | UTMI_TX_REG_EXT_FS_RCAL_MASK
		| UTMI_TX_AMP_MASK);
	u2o_set(base, UTMI_TX, 3<<UTMI_TX_TXVDD12_SHIFT
		| 4<<UTMI_TX_CK60_PHSEL_SHIFT | 4<<UTMI_TX_IMPCAL_VTH_SHIFT
		| 8<<UTMI_TX_REG_EXT_FS_RCAL_SHIFT | 3<<UTMI_TX_AMP_SHIFT);

	/* UTMI_RX */
	u2o_clear(base, UTMI_RX, UTMI_RX_SQ_THRESH_MASK
		| UTMI_REG_SQ_LENGTH_MASK);
	u2o_set(base, UTMI_RX, 7<<UTMI_RX_SQ_THRESH_SHIFT
		| 2<<UTMI_REG_SQ_LENGTH_SHIFT);

	/* UTMI_IVREF */
	अगर (cpu_is_pxa168())
		/* fixing Microsoft Altair board पूर्णांकerface with NEC hub issue -
		 * Set UTMI_IVREF from 0x4a3 to 0x4bf */
		u2o_ग_लिखो(base, UTMI_IVREF, 0x4bf);

	/* toggle VCOCAL_START bit of UTMI_PLL */
	udelay(200);
	u2o_set(base, UTMI_PLL, VCOCAL_START);
	udelay(40);
	u2o_clear(base, UTMI_PLL, VCOCAL_START);

	/* toggle REG_RCAL_START bit of UTMI_TX */
	udelay(400);
	u2o_set(base, UTMI_TX, REG_RCAL_START);
	udelay(40);
	u2o_clear(base, UTMI_TX, REG_RCAL_START);
	udelay(400);

	/* Make sure PHY PLL is पढ़ोy */
	loops = 0;
	जबतक ((u2o_get(base, UTMI_PLL) & PLL_READY) == 0) अणु
		mdelay(1);
		loops++;
		अगर (loops > 100) अणु
			prपूर्णांकk(KERN_WARNING "calibrate timeout, UTMI_PLL %x\n",
				u2o_get(base, UTMI_PLL));
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (cpu_is_pxa168()) अणु
		u2o_set(base, UTMI_RESERVE, 1 << 5);
		/* Turn on UTMI PHY OTG extension */
		u2o_ग_लिखो(base, UTMI_OTG_ADDON, 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक usb_phy_deinit_पूर्णांकernal(व्योम __iomem *base)
अणु
	pr_info("Deinit usb phy!!!\n");

	अगर (cpu_is_pxa168())
		u2o_clear(base, UTMI_OTG_ADDON, UTMI_OTG_ADDON_OTG_ON);

	u2o_clear(base, UTMI_CTRL, UTMI_CTRL_RXBUF_PDWN);
	u2o_clear(base, UTMI_CTRL, UTMI_CTRL_TXBUF_PDWN);
	u2o_clear(base, UTMI_CTRL, UTMI_CTRL_USB_CLK_EN);
	u2o_clear(base, UTMI_CTRL, 1<<UTMI_CTRL_PWR_UP_SHIFT);
	u2o_clear(base, UTMI_CTRL, 1<<UTMI_CTRL_PLL_PWR_UP_SHIFT);

	वापस 0;
पूर्ण

पूर्णांक pxa_usb_phy_init(व्योम __iomem *phy_reg)
अणु
	mutex_lock(&phy_lock);
	अगर (phy_init_cnt++ == 0)
		usb_phy_init_पूर्णांकernal(phy_reg);
	mutex_unlock(&phy_lock);
	वापस 0;
पूर्ण

व्योम pxa_usb_phy_deinit(व्योम __iomem *phy_reg)
अणु
	WARN_ON(phy_init_cnt == 0);

	mutex_lock(&phy_lock);
	अगर (--phy_init_cnt == 0)
		usb_phy_deinit_पूर्णांकernal(phy_reg);
	mutex_unlock(&phy_lock);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_USB_SUPPORT)
अटल u64 __maybe_unused usb_dma_mask = ~(u32)0;

#अगर IS_ENABLED(CONFIG_PHY_PXA_USB)
काष्ठा resource pxa168_usb_phy_resources[] = अणु
	[0] = अणु
		.start	= PXA168_U2O_PHYBASE,
		.end	= PXA168_U2O_PHYBASE + USB_PHY_RANGE,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa168_device_usb_phy = अणु
	.name		= "pxa-usb-phy",
	.id		= -1,
	.resource	= pxa168_usb_phy_resources,
	.num_resources	= ARRAY_SIZE(pxa168_usb_phy_resources),
	.dev		=  अणु
		.dma_mask	= &usb_dma_mask,
		.coherent_dma_mask = 0xffffffff,
	पूर्ण
पूर्ण;
#पूर्ण_अगर /* CONFIG_PHY_PXA_USB */

#अगर IS_ENABLED(CONFIG_USB_MV_UDC)
काष्ठा resource pxa168_u2o_resources[] = अणु
	/* regbase */
	[0] = अणु
		.start	= PXA168_U2O_REGBASE + U2x_CAPREGS_OFFSET,
		.end	= PXA168_U2O_REGBASE + USB_REG_RANGE,
		.flags	= IORESOURCE_MEM,
		.name	= "capregs",
	पूर्ण,
	/* phybase */
	[1] = अणु
		.start	= PXA168_U2O_PHYBASE,
		.end	= PXA168_U2O_PHYBASE + USB_PHY_RANGE,
		.flags	= IORESOURCE_MEM,
		.name	= "phyregs",
	पूर्ण,
	[2] = अणु
		.start	= IRQ_PXA168_USB1,
		.end	= IRQ_PXA168_USB1,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa168_device_u2o = अणु
	.name		= "mv-udc",
	.id		= -1,
	.resource	= pxa168_u2o_resources,
	.num_resources	= ARRAY_SIZE(pxa168_u2o_resources),
	.dev		=  अणु
		.dma_mask	= &usb_dma_mask,
		.coherent_dma_mask = 0xffffffff,
	पूर्ण
पूर्ण;
#पूर्ण_अगर /* CONFIG_USB_MV_UDC */

#अगर IS_ENABLED(CONFIG_USB_EHCI_MV_U2O)
काष्ठा resource pxa168_u2oehci_resources[] = अणु
	[0] = अणु
		.start	= PXA168_U2O_REGBASE,
		.end	= PXA168_U2O_REGBASE + USB_REG_RANGE,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_PXA168_USB1,
		.end	= IRQ_PXA168_USB1,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa168_device_u2oehci = अणु
	.name		= "pxa-u2oehci",
	.id		= -1,
	.dev		= अणु
		.dma_mask		= &usb_dma_mask,
		.coherent_dma_mask	= 0xffffffff,
	पूर्ण,

	.num_resources	= ARRAY_SIZE(pxa168_u2oehci_resources),
	.resource	= pxa168_u2oehci_resources,
पूर्ण;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_USB_MV_OTG)
काष्ठा resource pxa168_u2ootg_resources[] = अणु
	/* regbase */
	[0] = अणु
		.start	= PXA168_U2O_REGBASE + U2x_CAPREGS_OFFSET,
		.end	= PXA168_U2O_REGBASE + USB_REG_RANGE,
		.flags	= IORESOURCE_MEM,
		.name	= "capregs",
	पूर्ण,
	/* phybase */
	[1] = अणु
		.start	= PXA168_U2O_PHYBASE,
		.end	= PXA168_U2O_PHYBASE + USB_PHY_RANGE,
		.flags	= IORESOURCE_MEM,
		.name	= "phyregs",
	पूर्ण,
	[2] = अणु
		.start	= IRQ_PXA168_USB1,
		.end	= IRQ_PXA168_USB1,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa168_device_u2ootg = अणु
	.name		= "mv-otg",
	.id		= -1,
	.dev  = अणु
		.dma_mask          = &usb_dma_mask,
		.coherent_dma_mask = 0xffffffff,
	पूर्ण,

	.num_resources	= ARRAY_SIZE(pxa168_u2ootg_resources),
	.resource      = pxa168_u2ootg_resources,
पूर्ण;
#पूर्ण_अगर /* CONFIG_USB_MV_OTG */

#पूर्ण_अगर
