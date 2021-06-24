<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * USB block घातer/access management असलtraction.
 *
 * Au1000+: The OHCI block control रेजिस्टर is at the far end of the OHCI memory
 *	    area. Au1550 has OHCI on dअगरferent base address. No need to handle
 *	    UDC here.
 * Au1200:  one रेजिस्टर to control access and घड़ीs to O/EHCI, UDC and OTG
 *	    as well as the PHY क्रम EHCI and UDC.
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/syscore_ops.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>

/* control रेजिस्टर offsets */
#घोषणा AU1000_OHCICFG	0x7fffc
#घोषणा AU1550_OHCICFG	0x07ffc
#घोषणा AU1200_USBCFG	0x04

/* Au1000 USB block config bits */
#घोषणा USBHEN_RD	(1 << 4)		/* OHCI reset-करोne indicator */
#घोषणा USBHEN_CE	(1 << 3)		/* OHCI block घड़ी enable */
#घोषणा USBHEN_E	(1 << 2)		/* OHCI block enable */
#घोषणा USBHEN_C	(1 << 1)		/* OHCI block coherency bit */
#घोषणा USBHEN_BE	(1 << 0)		/* OHCI Big-Endian */

/* Au1200 USB config bits */
#घोषणा USBCFG_PFEN	(1 << 31)		/* prefetch enable (unकरोc) */
#घोषणा USBCFG_RDCOMB	(1 << 30)		/* पढ़ो combining (unकरोc) */
#घोषणा USBCFG_UNKNOWN	(5 << 20)		/* unknown, leave this way */
#घोषणा USBCFG_SSD	(1 << 23)		/* serial लघु detect en */
#घोषणा USBCFG_PPE	(1 << 19)		/* HS PHY PLL */
#घोषणा USBCFG_UCE	(1 << 18)		/* UDC घड़ी enable */
#घोषणा USBCFG_ECE	(1 << 17)		/* EHCI घड़ी enable */
#घोषणा USBCFG_OCE	(1 << 16)		/* OHCI घड़ी enable */
#घोषणा USBCFG_FLA(x)	(((x) & 0x3f) << 8)
#घोषणा USBCFG_UCAM	(1 << 7)		/* coherent access (unकरोc) */
#घोषणा USBCFG_GME	(1 << 6)		/* OTG mem access */
#घोषणा USBCFG_DBE	(1 << 5)		/* UDC busmaster enable */
#घोषणा USBCFG_DME	(1 << 4)		/* UDC mem enable */
#घोषणा USBCFG_EBE	(1 << 3)		/* EHCI busmaster enable */
#घोषणा USBCFG_EME	(1 << 2)		/* EHCI mem enable */
#घोषणा USBCFG_OBE	(1 << 1)		/* OHCI busmaster enable */
#घोषणा USBCFG_OME	(1 << 0)		/* OHCI mem enable */
#घोषणा USBCFG_INIT_AU1200	(USBCFG_PFEN | USBCFG_RDCOMB | USBCFG_UNKNOWN |\
				 USBCFG_SSD | USBCFG_FLA(0x20) | USBCFG_UCAM | \
				 USBCFG_GME | USBCFG_DBE | USBCFG_DME |	       \
				 USBCFG_EBE | USBCFG_EME | USBCFG_OBE |	       \
				 USBCFG_OME)

/* Au1300 USB config रेजिस्टरs */
#घोषणा USB_DWC_CTRL1		0x00
#घोषणा USB_DWC_CTRL2		0x04
#घोषणा USB_VBUS_TIMER		0x10
#घोषणा USB_SBUS_CTRL		0x14
#घोषणा USB_MSR_ERR		0x18
#घोषणा USB_DWC_CTRL3		0x1C
#घोषणा USB_DWC_CTRL4		0x20
#घोषणा USB_OTG_STATUS		0x28
#घोषणा USB_DWC_CTRL5		0x2C
#घोषणा USB_DWC_CTRL6		0x30
#घोषणा USB_DWC_CTRL7		0x34
#घोषणा USB_PHY_STATUS		0xC0
#घोषणा USB_INT_STATUS		0xC4
#घोषणा USB_INT_ENABLE		0xC8

#घोषणा USB_DWC_CTRL1_OTGD	0x04 /* set to DISable OTG */
#घोषणा USB_DWC_CTRL1_HSTRS	0x02 /* set to ENable EHCI */
#घोषणा USB_DWC_CTRL1_DCRS	0x01 /* set to ENable UDC */

#घोषणा USB_DWC_CTRL2_PHY1RS	0x04 /* set to enable PHY1 */
#घोषणा USB_DWC_CTRL2_PHY0RS	0x02 /* set to enable PHY0 */
#घोषणा USB_DWC_CTRL2_PHYRS	0x01 /* set to enable PHY */

#घोषणा USB_DWC_CTRL3_OHCI1_CKEN	(1 << 19)
#घोषणा USB_DWC_CTRL3_OHCI0_CKEN	(1 << 18)
#घोषणा USB_DWC_CTRL3_EHCI0_CKEN	(1 << 17)
#घोषणा USB_DWC_CTRL3_OTG0_CKEN		(1 << 16)

#घोषणा USB_SBUS_CTRL_SBCA		0x04 /* coherent access */

#घोषणा USB_INTEN_FORCE			0x20
#घोषणा USB_INTEN_PHY			0x10
#घोषणा USB_INTEN_UDC			0x08
#घोषणा USB_INTEN_EHCI			0x04
#घोषणा USB_INTEN_OHCI1			0x02
#घोषणा USB_INTEN_OHCI0			0x01

अटल DEFINE_SPINLOCK(alchemy_usb_lock);

अटल अंतरभूत व्योम __au1300_usb_phyctl(व्योम __iomem *base, पूर्णांक enable)
अणु
	अचिन्हित दीर्घ r, s;

	r = __raw_पढ़ोl(base + USB_DWC_CTRL2);
	s = __raw_पढ़ोl(base + USB_DWC_CTRL3);

	s &= USB_DWC_CTRL3_OHCI1_CKEN | USB_DWC_CTRL3_OHCI0_CKEN |
		USB_DWC_CTRL3_EHCI0_CKEN | USB_DWC_CTRL3_OTG0_CKEN;

	अगर (enable) अणु
		/* simply enable all PHYs */
		r |= USB_DWC_CTRL2_PHY1RS | USB_DWC_CTRL2_PHY0RS |
		     USB_DWC_CTRL2_PHYRS;
		__raw_ग_लिखोl(r, base + USB_DWC_CTRL2);
		wmb();
	पूर्ण अन्यथा अगर (!s) अणु
		/* no USB block active, करो disable all PHYs */
		r &= ~(USB_DWC_CTRL2_PHY1RS | USB_DWC_CTRL2_PHY0RS |
		       USB_DWC_CTRL2_PHYRS);
		__raw_ग_लिखोl(r, base + USB_DWC_CTRL2);
		wmb();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __au1300_ohci_control(व्योम __iomem *base, पूर्णांक enable, पूर्णांक id)
अणु
	अचिन्हित दीर्घ r;

	अगर (enable) अणु
		__raw_ग_लिखोl(1, base + USB_DWC_CTRL7);	/* start OHCI घड़ी */
		wmb();

		r = __raw_पढ़ोl(base + USB_DWC_CTRL3);	/* enable OHCI block */
		r |= (id == 0) ? USB_DWC_CTRL3_OHCI0_CKEN
			       : USB_DWC_CTRL3_OHCI1_CKEN;
		__raw_ग_लिखोl(r, base + USB_DWC_CTRL3);
		wmb();

		__au1300_usb_phyctl(base, enable);	/* घातer up the PHYs */

		r = __raw_पढ़ोl(base + USB_INT_ENABLE);
		r |= (id == 0) ? USB_INTEN_OHCI0 : USB_INTEN_OHCI1;
		__raw_ग_लिखोl(r, base + USB_INT_ENABLE);
		wmb();

		/* reset the OHCI start घड़ी bit */
		__raw_ग_लिखोl(0, base + USB_DWC_CTRL7);
		wmb();
	पूर्ण अन्यथा अणु
		r = __raw_पढ़ोl(base + USB_INT_ENABLE);
		r &= ~((id == 0) ? USB_INTEN_OHCI0 : USB_INTEN_OHCI1);
		__raw_ग_लिखोl(r, base + USB_INT_ENABLE);
		wmb();

		r = __raw_पढ़ोl(base + USB_DWC_CTRL3);
		r &= ~((id == 0) ? USB_DWC_CTRL3_OHCI0_CKEN
				 : USB_DWC_CTRL3_OHCI1_CKEN);
		__raw_ग_लिखोl(r, base + USB_DWC_CTRL3);
		wmb();

		__au1300_usb_phyctl(base, enable);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __au1300_ehci_control(व्योम __iomem *base, पूर्णांक enable)
अणु
	अचिन्हित दीर्घ r;

	अगर (enable) अणु
		r = __raw_पढ़ोl(base + USB_DWC_CTRL3);
		r |= USB_DWC_CTRL3_EHCI0_CKEN;
		__raw_ग_लिखोl(r, base + USB_DWC_CTRL3);
		wmb();

		r = __raw_पढ़ोl(base + USB_DWC_CTRL1);
		r |= USB_DWC_CTRL1_HSTRS;
		__raw_ग_लिखोl(r, base + USB_DWC_CTRL1);
		wmb();

		__au1300_usb_phyctl(base, enable);

		r = __raw_पढ़ोl(base + USB_INT_ENABLE);
		r |= USB_INTEN_EHCI;
		__raw_ग_लिखोl(r, base + USB_INT_ENABLE);
		wmb();
	पूर्ण अन्यथा अणु
		r = __raw_पढ़ोl(base + USB_INT_ENABLE);
		r &= ~USB_INTEN_EHCI;
		__raw_ग_लिखोl(r, base + USB_INT_ENABLE);
		wmb();

		r = __raw_पढ़ोl(base + USB_DWC_CTRL1);
		r &= ~USB_DWC_CTRL1_HSTRS;
		__raw_ग_लिखोl(r, base + USB_DWC_CTRL1);
		wmb();

		r = __raw_पढ़ोl(base + USB_DWC_CTRL3);
		r &= ~USB_DWC_CTRL3_EHCI0_CKEN;
		__raw_ग_लिखोl(r, base + USB_DWC_CTRL3);
		wmb();

		__au1300_usb_phyctl(base, enable);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __au1300_udc_control(व्योम __iomem *base, पूर्णांक enable)
अणु
	अचिन्हित दीर्घ r;

	अगर (enable) अणु
		r = __raw_पढ़ोl(base + USB_DWC_CTRL1);
		r |= USB_DWC_CTRL1_DCRS;
		__raw_ग_लिखोl(r, base + USB_DWC_CTRL1);
		wmb();

		__au1300_usb_phyctl(base, enable);

		r = __raw_पढ़ोl(base + USB_INT_ENABLE);
		r |= USB_INTEN_UDC;
		__raw_ग_लिखोl(r, base + USB_INT_ENABLE);
		wmb();
	पूर्ण अन्यथा अणु
		r = __raw_पढ़ोl(base + USB_INT_ENABLE);
		r &= ~USB_INTEN_UDC;
		__raw_ग_लिखोl(r, base + USB_INT_ENABLE);
		wmb();

		r = __raw_पढ़ोl(base + USB_DWC_CTRL1);
		r &= ~USB_DWC_CTRL1_DCRS;
		__raw_ग_लिखोl(r, base + USB_DWC_CTRL1);
		wmb();

		__au1300_usb_phyctl(base, enable);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __au1300_otg_control(व्योम __iomem *base, पूर्णांक enable)
अणु
	अचिन्हित दीर्घ r;
	अगर (enable) अणु
		r = __raw_पढ़ोl(base + USB_DWC_CTRL3);
		r |= USB_DWC_CTRL3_OTG0_CKEN;
		__raw_ग_लिखोl(r, base + USB_DWC_CTRL3);
		wmb();

		r = __raw_पढ़ोl(base + USB_DWC_CTRL1);
		r &= ~USB_DWC_CTRL1_OTGD;
		__raw_ग_लिखोl(r, base + USB_DWC_CTRL1);
		wmb();

		__au1300_usb_phyctl(base, enable);
	पूर्ण अन्यथा अणु
		r = __raw_पढ़ोl(base + USB_DWC_CTRL1);
		r |= USB_DWC_CTRL1_OTGD;
		__raw_ग_लिखोl(r, base + USB_DWC_CTRL1);
		wmb();

		r = __raw_पढ़ोl(base + USB_DWC_CTRL3);
		r &= ~USB_DWC_CTRL3_OTG0_CKEN;
		__raw_ग_लिखोl(r, base + USB_DWC_CTRL3);
		wmb();

		__au1300_usb_phyctl(base, enable);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक au1300_usb_control(पूर्णांक block, पूर्णांक enable)
अणु
	व्योम __iomem *base =
		(व्योम __iomem *)KSEG1ADDR(AU1300_USB_CTL_PHYS_ADDR);
	पूर्णांक ret = 0;

	चयन (block) अणु
	हाल ALCHEMY_USB_OHCI0:
		__au1300_ohci_control(base, enable, 0);
		अवरोध;
	हाल ALCHEMY_USB_OHCI1:
		__au1300_ohci_control(base, enable, 1);
		अवरोध;
	हाल ALCHEMY_USB_EHCI0:
		__au1300_ehci_control(base, enable);
		अवरोध;
	हाल ALCHEMY_USB_UDC0:
		__au1300_udc_control(base, enable);
		अवरोध;
	हाल ALCHEMY_USB_OTG0:
		__au1300_otg_control(base, enable);
		अवरोध;
	शेष:
		ret = -ENODEV;
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम au1300_usb_init(व्योम)
अणु
	व्योम __iomem *base =
		(व्योम __iomem *)KSEG1ADDR(AU1300_USB_CTL_PHYS_ADDR);

	/* set some sane शेषs.  Note: we करोn't fiddle with DWC_CTRL4
	 * here at all: Port 2 routing (EHCI or UDC) must be set either
	 * by boot firmware or platक्रमm init code; I can't स्वतःdetect
	 * a sane setting.
	 */
	__raw_ग_लिखोl(0, base + USB_INT_ENABLE); /* disable all USB irqs */
	wmb();
	__raw_ग_लिखोl(0, base + USB_DWC_CTRL3); /* disable all घड़ीs */
	wmb();
	__raw_ग_लिखोl(~0, base + USB_MSR_ERR); /* clear all errors */
	wmb();
	__raw_ग_लिखोl(~0, base + USB_INT_STATUS); /* clear पूर्णांक status */
	wmb();
	/* set coherent access bit */
	__raw_ग_लिखोl(USB_SBUS_CTRL_SBCA, base + USB_SBUS_CTRL);
	wmb();
पूर्ण

अटल अंतरभूत व्योम __au1200_ohci_control(व्योम __iomem *base, पूर्णांक enable)
अणु
	अचिन्हित दीर्घ r = __raw_पढ़ोl(base + AU1200_USBCFG);
	अगर (enable) अणु
		__raw_ग_लिखोl(r | USBCFG_OCE, base + AU1200_USBCFG);
		wmb();
		udelay(2000);
	पूर्ण अन्यथा अणु
		__raw_ग_लिखोl(r & ~USBCFG_OCE, base + AU1200_USBCFG);
		wmb();
		udelay(1000);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __au1200_ehci_control(व्योम __iomem *base, पूर्णांक enable)
अणु
	अचिन्हित दीर्घ r = __raw_पढ़ोl(base + AU1200_USBCFG);
	अगर (enable) अणु
		__raw_ग_लिखोl(r | USBCFG_ECE | USBCFG_PPE, base + AU1200_USBCFG);
		wmb();
		udelay(1000);
	पूर्ण अन्यथा अणु
		अगर (!(r & USBCFG_UCE))		/* UDC also off? */
			r &= ~USBCFG_PPE;	/* yes: disable HS PHY PLL */
		__raw_ग_लिखोl(r & ~USBCFG_ECE, base + AU1200_USBCFG);
		wmb();
		udelay(1000);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __au1200_udc_control(व्योम __iomem *base, पूर्णांक enable)
अणु
	अचिन्हित दीर्घ r = __raw_पढ़ोl(base + AU1200_USBCFG);
	अगर (enable) अणु
		__raw_ग_लिखोl(r | USBCFG_UCE | USBCFG_PPE, base + AU1200_USBCFG);
		wmb();
	पूर्ण अन्यथा अणु
		अगर (!(r & USBCFG_ECE))		/* EHCI also off? */
			r &= ~USBCFG_PPE;	/* yes: disable HS PHY PLL */
		__raw_ग_लिखोl(r & ~USBCFG_UCE, base + AU1200_USBCFG);
		wmb();
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक au1200_usb_control(पूर्णांक block, पूर्णांक enable)
अणु
	व्योम __iomem *base =
			(व्योम __iomem *)KSEG1ADDR(AU1200_USB_CTL_PHYS_ADDR);

	चयन (block) अणु
	हाल ALCHEMY_USB_OHCI0:
		__au1200_ohci_control(base, enable);
		अवरोध;
	हाल ALCHEMY_USB_UDC0:
		__au1200_udc_control(base, enable);
		अवरोध;
	हाल ALCHEMY_USB_EHCI0:
		__au1200_ehci_control(base, enable);
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण


/* initialize USB block(s) to a known working state */
अटल अंतरभूत व्योम au1200_usb_init(व्योम)
अणु
	व्योम __iomem *base =
			(व्योम __iomem *)KSEG1ADDR(AU1200_USB_CTL_PHYS_ADDR);
	__raw_ग_लिखोl(USBCFG_INIT_AU1200, base + AU1200_USBCFG);
	wmb();
	udelay(1000);
पूर्ण

अटल अंतरभूत पूर्णांक au1000_usb_init(अचिन्हित दीर्घ rb, पूर्णांक reg)
अणु
	व्योम __iomem *base = (व्योम __iomem *)KSEG1ADDR(rb + reg);
	अचिन्हित दीर्घ r = __raw_पढ़ोl(base);
	काष्ठा clk *c;

	/* 48MHz check. Don't init अगर no one can provide it */
	c = clk_get(शून्य, "usbh_clk");
	अगर (IS_ERR(c))
		वापस -ENODEV;
	अगर (clk_round_rate(c, 48000000) != 48000000) अणु
		clk_put(c);
		वापस -ENODEV;
	पूर्ण
	अगर (clk_set_rate(c, 48000000)) अणु
		clk_put(c);
		वापस -ENODEV;
	पूर्ण
	clk_put(c);

#अगर defined(__BIG_ENDIAN)
	r |= USBHEN_BE;
#पूर्ण_अगर
	r |= USBHEN_C;

	__raw_ग_लिखोl(r, base);
	wmb();
	udelay(1000);

	वापस 0;
पूर्ण


अटल अंतरभूत व्योम __au1xx0_ohci_control(पूर्णांक enable, अचिन्हित दीर्घ rb, पूर्णांक creg)
अणु
	व्योम __iomem *base = (व्योम __iomem *)KSEG1ADDR(rb);
	अचिन्हित दीर्घ r = __raw_पढ़ोl(base + creg);
	काष्ठा clk *c = clk_get(शून्य, "usbh_clk");

	अगर (IS_ERR(c))
		वापस;

	अगर (enable) अणु
		अगर (clk_prepare_enable(c))
			जाओ out;

		__raw_ग_लिखोl(r | USBHEN_CE, base + creg);
		wmb();
		udelay(1000);
		__raw_ग_लिखोl(r | USBHEN_CE | USBHEN_E, base + creg);
		wmb();
		udelay(1000);

		/* रुको क्रम reset complete (पढ़ो reg twice: au1500 erratum) */
		जबतक (__raw_पढ़ोl(base + creg),
			!(__raw_पढ़ोl(base + creg) & USBHEN_RD))
			udelay(1000);
	पूर्ण अन्यथा अणु
		__raw_ग_लिखोl(r & ~(USBHEN_CE | USBHEN_E), base + creg);
		wmb();
		clk_disable_unprepare(c);
	पूर्ण
out:
	clk_put(c);
पूर्ण

अटल अंतरभूत पूर्णांक au1000_usb_control(पूर्णांक block, पूर्णांक enable, अचिन्हित दीर्घ rb,
				     पूर्णांक creg)
अणु
	पूर्णांक ret = 0;

	चयन (block) अणु
	हाल ALCHEMY_USB_OHCI0:
		__au1xx0_ohci_control(enable, rb, creg);
		अवरोध;
	शेष:
		ret = -ENODEV;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * alchemy_usb_control - control Alchemy on-chip USB blocks
 * @block:	USB block to target
 * @enable:	set 1 to enable a block, 0 to disable
 */
पूर्णांक alchemy_usb_control(पूर्णांक block, पूर्णांक enable)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&alchemy_usb_lock, flags);
	चयन (alchemy_get_cputype()) अणु
	हाल ALCHEMY_CPU_AU1000:
	हाल ALCHEMY_CPU_AU1500:
	हाल ALCHEMY_CPU_AU1100:
		ret = au1000_usb_control(block, enable,
			AU1000_USB_OHCI_PHYS_ADDR, AU1000_OHCICFG);
		अवरोध;
	हाल ALCHEMY_CPU_AU1550:
		ret = au1000_usb_control(block, enable,
			AU1550_USB_OHCI_PHYS_ADDR, AU1550_OHCICFG);
		अवरोध;
	हाल ALCHEMY_CPU_AU1200:
		ret = au1200_usb_control(block, enable);
		अवरोध;
	हाल ALCHEMY_CPU_AU1300:
		ret = au1300_usb_control(block, enable);
		अवरोध;
	शेष:
		ret = -ENODEV;
	पूर्ण
	spin_unlock_irqrestore(&alchemy_usb_lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(alchemy_usb_control);


अटल अचिन्हित दीर्घ alchemy_usb_pmdata[2];

अटल व्योम au1000_usb_pm(अचिन्हित दीर्घ br, पूर्णांक creg, पूर्णांक susp)
अणु
	व्योम __iomem *base = (व्योम __iomem *)KSEG1ADDR(br);

	अगर (susp) अणु
		alchemy_usb_pmdata[0] = __raw_पढ़ोl(base + creg);
		/* There appears to be some unकरोcumented reset रेजिस्टर.... */
		__raw_ग_लिखोl(0, base + 0x04);
		wmb();
		__raw_ग_लिखोl(0, base + creg);
		wmb();
	पूर्ण अन्यथा अणु
		__raw_ग_लिखोl(alchemy_usb_pmdata[0], base + creg);
		wmb();
	पूर्ण
पूर्ण

अटल व्योम au1200_usb_pm(पूर्णांक susp)
अणु
	व्योम __iomem *base =
			(व्योम __iomem *)KSEG1ADDR(AU1200_USB_OTG_PHYS_ADDR);
	अगर (susp) अणु
		/* save OTG_CAP/MUX रेजिस्टरs which indicate port routing */
		/* FIXME: ग_लिखो an OTG driver to करो that */
		alchemy_usb_pmdata[0] = __raw_पढ़ोl(base + 0x00);
		alchemy_usb_pmdata[1] = __raw_पढ़ोl(base + 0x04);
	पूर्ण अन्यथा अणु
		/* restore access to all MMIO areas */
		au1200_usb_init();

		/* restore OTG_CAP/MUX रेजिस्टरs */
		__raw_ग_लिखोl(alchemy_usb_pmdata[0], base + 0x00);
		__raw_ग_लिखोl(alchemy_usb_pmdata[1], base + 0x04);
		wmb();
	पूर्ण
पूर्ण

अटल व्योम au1300_usb_pm(पूर्णांक susp)
अणु
	व्योम __iomem *base =
			(व्योम __iomem *)KSEG1ADDR(AU1300_USB_CTL_PHYS_ADDR);
	/* remember Port2 routing */
	अगर (susp) अणु
		alchemy_usb_pmdata[0] = __raw_पढ़ोl(base + USB_DWC_CTRL4);
	पूर्ण अन्यथा अणु
		au1300_usb_init();
		__raw_ग_लिखोl(alchemy_usb_pmdata[0], base + USB_DWC_CTRL4);
		wmb();
	पूर्ण
पूर्ण

अटल व्योम alchemy_usb_pm(पूर्णांक susp)
अणु
	चयन (alchemy_get_cputype()) अणु
	हाल ALCHEMY_CPU_AU1000:
	हाल ALCHEMY_CPU_AU1500:
	हाल ALCHEMY_CPU_AU1100:
		au1000_usb_pm(AU1000_USB_OHCI_PHYS_ADDR, AU1000_OHCICFG, susp);
		अवरोध;
	हाल ALCHEMY_CPU_AU1550:
		au1000_usb_pm(AU1550_USB_OHCI_PHYS_ADDR, AU1550_OHCICFG, susp);
		अवरोध;
	हाल ALCHEMY_CPU_AU1200:
		au1200_usb_pm(susp);
		अवरोध;
	हाल ALCHEMY_CPU_AU1300:
		au1300_usb_pm(susp);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक alchemy_usb_suspend(व्योम)
अणु
	alchemy_usb_pm(1);
	वापस 0;
पूर्ण

अटल व्योम alchemy_usb_resume(व्योम)
अणु
	alchemy_usb_pm(0);
पूर्ण

अटल काष्ठा syscore_ops alchemy_usb_pm_ops = अणु
	.suspend	= alchemy_usb_suspend,
	.resume		= alchemy_usb_resume,
पूर्ण;

अटल पूर्णांक __init alchemy_usb_init(व्योम)
अणु
	पूर्णांक ret = 0;

	चयन (alchemy_get_cputype()) अणु
	हाल ALCHEMY_CPU_AU1000:
	हाल ALCHEMY_CPU_AU1500:
	हाल ALCHEMY_CPU_AU1100:
		ret = au1000_usb_init(AU1000_USB_OHCI_PHYS_ADDR,
				      AU1000_OHCICFG);
		अवरोध;
	हाल ALCHEMY_CPU_AU1550:
		ret = au1000_usb_init(AU1550_USB_OHCI_PHYS_ADDR,
				      AU1550_OHCICFG);
		अवरोध;
	हाल ALCHEMY_CPU_AU1200:
		au1200_usb_init();
		अवरोध;
	हाल ALCHEMY_CPU_AU1300:
		au1300_usb_init();
		अवरोध;
	पूर्ण

	अगर (!ret)
		रेजिस्टर_syscore_ops(&alchemy_usb_pm_ops);

	वापस ret;
पूर्ण
arch_initcall(alchemy_usb_init);
