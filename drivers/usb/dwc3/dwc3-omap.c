<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dwc3-omap.c - OMAP Specअगरic Glue layer
 *
 * Copyright (C) 2010-2011 Texas Instruments Incorporated - https://www.ti.com
 *
 * Authors: Felipe Balbi <balbi@ti.com>,
 *	    Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/extcon.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <linux/usb/otg.h>

/*
 * All these रेजिस्टरs beदीर्घ to OMAP's Wrapper around the
 * DesignWare USB3 Core.
 */

#घोषणा USBOTGSS_REVISION			0x0000
#घोषणा USBOTGSS_SYSCONFIG			0x0010
#घोषणा USBOTGSS_IRQ_EOI			0x0020
#घोषणा USBOTGSS_EOI_OFFSET			0x0008
#घोषणा USBOTGSS_IRQSTATUS_RAW_0		0x0024
#घोषणा USBOTGSS_IRQSTATUS_0			0x0028
#घोषणा USBOTGSS_IRQENABLE_SET_0		0x002c
#घोषणा USBOTGSS_IRQENABLE_CLR_0		0x0030
#घोषणा USBOTGSS_IRQ0_OFFSET			0x0004
#घोषणा USBOTGSS_IRQSTATUS_RAW_1		0x0030
#घोषणा USBOTGSS_IRQSTATUS_1			0x0034
#घोषणा USBOTGSS_IRQENABLE_SET_1		0x0038
#घोषणा USBOTGSS_IRQENABLE_CLR_1		0x003c
#घोषणा USBOTGSS_IRQSTATUS_RAW_2		0x0040
#घोषणा USBOTGSS_IRQSTATUS_2			0x0044
#घोषणा USBOTGSS_IRQENABLE_SET_2		0x0048
#घोषणा USBOTGSS_IRQENABLE_CLR_2		0x004c
#घोषणा USBOTGSS_IRQSTATUS_RAW_3		0x0050
#घोषणा USBOTGSS_IRQSTATUS_3			0x0054
#घोषणा USBOTGSS_IRQENABLE_SET_3		0x0058
#घोषणा USBOTGSS_IRQENABLE_CLR_3		0x005c
#घोषणा USBOTGSS_IRQSTATUS_EOI_MISC		0x0030
#घोषणा USBOTGSS_IRQSTATUS_RAW_MISC		0x0034
#घोषणा USBOTGSS_IRQSTATUS_MISC			0x0038
#घोषणा USBOTGSS_IRQENABLE_SET_MISC		0x003c
#घोषणा USBOTGSS_IRQENABLE_CLR_MISC		0x0040
#घोषणा USBOTGSS_IRQMISC_OFFSET			0x03fc
#घोषणा USBOTGSS_UTMI_OTG_STATUS		0x0080
#घोषणा USBOTGSS_UTMI_OTG_CTRL			0x0084
#घोषणा USBOTGSS_UTMI_OTG_OFFSET		0x0480
#घोषणा USBOTGSS_TXFIFO_DEPTH			0x0508
#घोषणा USBOTGSS_RXFIFO_DEPTH			0x050c
#घोषणा USBOTGSS_MMRAM_OFFSET			0x0100
#घोषणा USBOTGSS_FLADJ				0x0104
#घोषणा USBOTGSS_DEBUG_CFG			0x0108
#घोषणा USBOTGSS_DEBUG_DATA			0x010c
#घोषणा USBOTGSS_DEV_EBC_EN			0x0110
#घोषणा USBOTGSS_DEBUG_OFFSET			0x0600

/* SYSCONFIG REGISTER */
#घोषणा USBOTGSS_SYSCONFIG_DMADISABLE		BIT(16)

/* IRQ_EOI REGISTER */
#घोषणा USBOTGSS_IRQ_EOI_LINE_NUMBER		BIT(0)

/* IRQS0 BITS */
#घोषणा USBOTGSS_IRQO_COREIRQ_ST		BIT(0)

/* IRQMISC BITS */
#घोषणा USBOTGSS_IRQMISC_DMADISABLECLR		BIT(17)
#घोषणा USBOTGSS_IRQMISC_OEVT			BIT(16)
#घोषणा USBOTGSS_IRQMISC_DRVVBUS_RISE		BIT(13)
#घोषणा USBOTGSS_IRQMISC_CHRGVBUS_RISE		BIT(12)
#घोषणा USBOTGSS_IRQMISC_DISCHRGVBUS_RISE	BIT(11)
#घोषणा USBOTGSS_IRQMISC_IDPULLUP_RISE		BIT(8)
#घोषणा USBOTGSS_IRQMISC_DRVVBUS_FALL		BIT(5)
#घोषणा USBOTGSS_IRQMISC_CHRGVBUS_FALL		BIT(4)
#घोषणा USBOTGSS_IRQMISC_DISCHRGVBUS_FALL		BIT(3)
#घोषणा USBOTGSS_IRQMISC_IDPULLUP_FALL		BIT(0)

/* UTMI_OTG_STATUS REGISTER */
#घोषणा USBOTGSS_UTMI_OTG_STATUS_DRVVBUS	BIT(5)
#घोषणा USBOTGSS_UTMI_OTG_STATUS_CHRGVBUS	BIT(4)
#घोषणा USBOTGSS_UTMI_OTG_STATUS_DISCHRGVBUS	BIT(3)
#घोषणा USBOTGSS_UTMI_OTG_STATUS_IDPULLUP	BIT(0)

/* UTMI_OTG_CTRL REGISTER */
#घोषणा USBOTGSS_UTMI_OTG_CTRL_SW_MODE		BIT(31)
#घोषणा USBOTGSS_UTMI_OTG_CTRL_POWERPRESENT	BIT(9)
#घोषणा USBOTGSS_UTMI_OTG_CTRL_TXBITSTUFFENABLE BIT(8)
#घोषणा USBOTGSS_UTMI_OTG_CTRL_IDDIG		BIT(4)
#घोषणा USBOTGSS_UTMI_OTG_CTRL_SESSEND		BIT(3)
#घोषणा USBOTGSS_UTMI_OTG_CTRL_SESSVALID	BIT(2)
#घोषणा USBOTGSS_UTMI_OTG_CTRL_VBUSVALID	BIT(1)

क्रमागत dwc3_omap_uपंचांगi_mode अणु
	DWC3_OMAP_UTMI_MODE_UNKNOWN = 0,
	DWC3_OMAP_UTMI_MODE_HW,
	DWC3_OMAP_UTMI_MODE_SW,
पूर्ण;

काष्ठा dwc3_omap अणु
	काष्ठा device		*dev;

	पूर्णांक			irq;
	व्योम __iomem		*base;

	u32			uपंचांगi_otg_ctrl;
	u32			uपंचांगi_otg_offset;
	u32			irqmisc_offset;
	u32			irq_eoi_offset;
	u32			debug_offset;
	u32			irq0_offset;

	काष्ठा extcon_dev	*edev;
	काष्ठा notअगरier_block	vbus_nb;
	काष्ठा notअगरier_block	id_nb;

	काष्ठा regulator	*vbus_reg;
पूर्ण;

क्रमागत omap_dwc3_vbus_id_status अणु
	OMAP_DWC3_ID_FLOAT,
	OMAP_DWC3_ID_GROUND,
	OMAP_DWC3_VBUS_OFF,
	OMAP_DWC3_VBUS_VALID,
पूर्ण;

अटल अंतरभूत u32 dwc3_omap_पढ़ोl(व्योम __iomem *base, u32 offset)
अणु
	वापस पढ़ोl(base + offset);
पूर्ण

अटल अंतरभूत व्योम dwc3_omap_ग_लिखोl(व्योम __iomem *base, u32 offset, u32 value)
अणु
	ग_लिखोl(value, base + offset);
पूर्ण

अटल u32 dwc3_omap_पढ़ो_uपंचांगi_ctrl(काष्ठा dwc3_omap *omap)
अणु
	वापस dwc3_omap_पढ़ोl(omap->base, USBOTGSS_UTMI_OTG_CTRL +
							omap->uपंचांगi_otg_offset);
पूर्ण

अटल व्योम dwc3_omap_ग_लिखो_uपंचांगi_ctrl(काष्ठा dwc3_omap *omap, u32 value)
अणु
	dwc3_omap_ग_लिखोl(omap->base, USBOTGSS_UTMI_OTG_CTRL +
					omap->uपंचांगi_otg_offset, value);

पूर्ण

अटल u32 dwc3_omap_पढ़ो_irq0_status(काष्ठा dwc3_omap *omap)
अणु
	वापस dwc3_omap_पढ़ोl(omap->base, USBOTGSS_IRQSTATUS_RAW_0 -
						omap->irq0_offset);
पूर्ण

अटल व्योम dwc3_omap_ग_लिखो_irq0_status(काष्ठा dwc3_omap *omap, u32 value)
अणु
	dwc3_omap_ग_लिखोl(omap->base, USBOTGSS_IRQSTATUS_0 -
						omap->irq0_offset, value);

पूर्ण

अटल u32 dwc3_omap_पढ़ो_irqmisc_status(काष्ठा dwc3_omap *omap)
अणु
	वापस dwc3_omap_पढ़ोl(omap->base, USBOTGSS_IRQSTATUS_RAW_MISC +
						omap->irqmisc_offset);
पूर्ण

अटल व्योम dwc3_omap_ग_लिखो_irqmisc_status(काष्ठा dwc3_omap *omap, u32 value)
अणु
	dwc3_omap_ग_लिखोl(omap->base, USBOTGSS_IRQSTATUS_MISC +
					omap->irqmisc_offset, value);

पूर्ण

अटल व्योम dwc3_omap_ग_लिखो_irqmisc_set(काष्ठा dwc3_omap *omap, u32 value)
अणु
	dwc3_omap_ग_लिखोl(omap->base, USBOTGSS_IRQENABLE_SET_MISC +
						omap->irqmisc_offset, value);

पूर्ण

अटल व्योम dwc3_omap_ग_लिखो_irq0_set(काष्ठा dwc3_omap *omap, u32 value)
अणु
	dwc3_omap_ग_लिखोl(omap->base, USBOTGSS_IRQENABLE_SET_0 -
						omap->irq0_offset, value);
पूर्ण

अटल व्योम dwc3_omap_ग_लिखो_irqmisc_clr(काष्ठा dwc3_omap *omap, u32 value)
अणु
	dwc3_omap_ग_लिखोl(omap->base, USBOTGSS_IRQENABLE_CLR_MISC +
						omap->irqmisc_offset, value);
पूर्ण

अटल व्योम dwc3_omap_ग_लिखो_irq0_clr(काष्ठा dwc3_omap *omap, u32 value)
अणु
	dwc3_omap_ग_लिखोl(omap->base, USBOTGSS_IRQENABLE_CLR_0 -
						omap->irq0_offset, value);
पूर्ण

अटल व्योम dwc3_omap_set_mailbox(काष्ठा dwc3_omap *omap,
	क्रमागत omap_dwc3_vbus_id_status status)
अणु
	पूर्णांक	ret;
	u32	val;

	चयन (status) अणु
	हाल OMAP_DWC3_ID_GROUND:
		अगर (omap->vbus_reg) अणु
			ret = regulator_enable(omap->vbus_reg);
			अगर (ret) अणु
				dev_err(omap->dev, "regulator enable failed\n");
				वापस;
			पूर्ण
		पूर्ण

		val = dwc3_omap_पढ़ो_uपंचांगi_ctrl(omap);
		val &= ~USBOTGSS_UTMI_OTG_CTRL_IDDIG;
		dwc3_omap_ग_लिखो_uपंचांगi_ctrl(omap, val);
		अवरोध;

	हाल OMAP_DWC3_VBUS_VALID:
		val = dwc3_omap_पढ़ो_uपंचांगi_ctrl(omap);
		val &= ~USBOTGSS_UTMI_OTG_CTRL_SESSEND;
		val |= USBOTGSS_UTMI_OTG_CTRL_VBUSVALID
				| USBOTGSS_UTMI_OTG_CTRL_SESSVALID;
		dwc3_omap_ग_लिखो_uपंचांगi_ctrl(omap, val);
		अवरोध;

	हाल OMAP_DWC3_ID_FLOAT:
		अगर (omap->vbus_reg)
			regulator_disable(omap->vbus_reg);
		val = dwc3_omap_पढ़ो_uपंचांगi_ctrl(omap);
		val |= USBOTGSS_UTMI_OTG_CTRL_IDDIG;
		dwc3_omap_ग_लिखो_uपंचांगi_ctrl(omap, val);
		अवरोध;

	हाल OMAP_DWC3_VBUS_OFF:
		val = dwc3_omap_पढ़ो_uपंचांगi_ctrl(omap);
		val &= ~(USBOTGSS_UTMI_OTG_CTRL_SESSVALID
				| USBOTGSS_UTMI_OTG_CTRL_VBUSVALID);
		val |= USBOTGSS_UTMI_OTG_CTRL_SESSEND;
		dwc3_omap_ग_लिखो_uपंचांगi_ctrl(omap, val);
		अवरोध;

	शेष:
		dev_WARN(omap->dev, "invalid state\n");
	पूर्ण
पूर्ण

अटल व्योम dwc3_omap_enable_irqs(काष्ठा dwc3_omap *omap);
अटल व्योम dwc3_omap_disable_irqs(काष्ठा dwc3_omap *omap);

अटल irqवापस_t dwc3_omap_पूर्णांकerrupt(पूर्णांक irq, व्योम *_omap)
अणु
	काष्ठा dwc3_omap	*omap = _omap;

	अगर (dwc3_omap_पढ़ो_irqmisc_status(omap) ||
	    dwc3_omap_पढ़ो_irq0_status(omap)) अणु
		/* mask irqs */
		dwc3_omap_disable_irqs(omap);
		वापस IRQ_WAKE_THREAD;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t dwc3_omap_पूर्णांकerrupt_thपढ़ो(पूर्णांक irq, व्योम *_omap)
अणु
	काष्ठा dwc3_omap	*omap = _omap;
	u32			reg;

	/* clear irq status flags */
	reg = dwc3_omap_पढ़ो_irqmisc_status(omap);
	dwc3_omap_ग_लिखो_irqmisc_status(omap, reg);

	reg = dwc3_omap_पढ़ो_irq0_status(omap);
	dwc3_omap_ग_लिखो_irq0_status(omap, reg);

	/* unmask irqs */
	dwc3_omap_enable_irqs(omap);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम dwc3_omap_enable_irqs(काष्ठा dwc3_omap *omap)
अणु
	u32			reg;

	/* enable all IRQs */
	reg = USBOTGSS_IRQO_COREIRQ_ST;
	dwc3_omap_ग_लिखो_irq0_set(omap, reg);

	reg = (USBOTGSS_IRQMISC_OEVT |
			USBOTGSS_IRQMISC_DRVVBUS_RISE |
			USBOTGSS_IRQMISC_CHRGVBUS_RISE |
			USBOTGSS_IRQMISC_DISCHRGVBUS_RISE |
			USBOTGSS_IRQMISC_IDPULLUP_RISE |
			USBOTGSS_IRQMISC_DRVVBUS_FALL |
			USBOTGSS_IRQMISC_CHRGVBUS_FALL |
			USBOTGSS_IRQMISC_DISCHRGVBUS_FALL |
			USBOTGSS_IRQMISC_IDPULLUP_FALL);

	dwc3_omap_ग_लिखो_irqmisc_set(omap, reg);
पूर्ण

अटल व्योम dwc3_omap_disable_irqs(काष्ठा dwc3_omap *omap)
अणु
	u32			reg;

	/* disable all IRQs */
	reg = USBOTGSS_IRQO_COREIRQ_ST;
	dwc3_omap_ग_लिखो_irq0_clr(omap, reg);

	reg = (USBOTGSS_IRQMISC_OEVT |
			USBOTGSS_IRQMISC_DRVVBUS_RISE |
			USBOTGSS_IRQMISC_CHRGVBUS_RISE |
			USBOTGSS_IRQMISC_DISCHRGVBUS_RISE |
			USBOTGSS_IRQMISC_IDPULLUP_RISE |
			USBOTGSS_IRQMISC_DRVVBUS_FALL |
			USBOTGSS_IRQMISC_CHRGVBUS_FALL |
			USBOTGSS_IRQMISC_DISCHRGVBUS_FALL |
			USBOTGSS_IRQMISC_IDPULLUP_FALL);

	dwc3_omap_ग_लिखो_irqmisc_clr(omap, reg);
पूर्ण

अटल पूर्णांक dwc3_omap_id_notअगरier(काष्ठा notअगरier_block *nb,
	अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा dwc3_omap *omap = container_of(nb, काष्ठा dwc3_omap, id_nb);

	अगर (event)
		dwc3_omap_set_mailbox(omap, OMAP_DWC3_ID_GROUND);
	अन्यथा
		dwc3_omap_set_mailbox(omap, OMAP_DWC3_ID_FLOAT);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक dwc3_omap_vbus_notअगरier(काष्ठा notअगरier_block *nb,
	अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा dwc3_omap *omap = container_of(nb, काष्ठा dwc3_omap, vbus_nb);

	अगर (event)
		dwc3_omap_set_mailbox(omap, OMAP_DWC3_VBUS_VALID);
	अन्यथा
		dwc3_omap_set_mailbox(omap, OMAP_DWC3_VBUS_OFF);

	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम dwc3_omap_map_offset(काष्ठा dwc3_omap *omap)
अणु
	काष्ठा device_node	*node = omap->dev->of_node;

	/*
	 * Dअगरferentiate between OMAP5 and AM437x.
	 *
	 * For OMAP5(ES2.0) and AM437x wrapper revision is same, even
	 * though there are changes in wrapper रेजिस्टर offsets.
	 *
	 * Using dt compatible to dअगरferentiate AM437x.
	 */
	अगर (of_device_is_compatible(node, "ti,am437x-dwc3")) अणु
		omap->irq_eoi_offset = USBOTGSS_EOI_OFFSET;
		omap->irq0_offset = USBOTGSS_IRQ0_OFFSET;
		omap->irqmisc_offset = USBOTGSS_IRQMISC_OFFSET;
		omap->uपंचांगi_otg_offset = USBOTGSS_UTMI_OTG_OFFSET;
		omap->debug_offset = USBOTGSS_DEBUG_OFFSET;
	पूर्ण
पूर्ण

अटल व्योम dwc3_omap_set_uपंचांगi_mode(काष्ठा dwc3_omap *omap)
अणु
	u32			reg;
	काष्ठा device_node	*node = omap->dev->of_node;
	u32			uपंचांगi_mode = 0;

	reg = dwc3_omap_पढ़ो_uपंचांगi_ctrl(omap);

	of_property_पढ़ो_u32(node, "utmi-mode", &uपंचांगi_mode);

	चयन (uपंचांगi_mode) अणु
	हाल DWC3_OMAP_UTMI_MODE_SW:
		reg |= USBOTGSS_UTMI_OTG_CTRL_SW_MODE;
		अवरोध;
	हाल DWC3_OMAP_UTMI_MODE_HW:
		reg &= ~USBOTGSS_UTMI_OTG_CTRL_SW_MODE;
		अवरोध;
	शेष:
		dev_WARN(omap->dev, "UNKNOWN utmi mode %d\n", uपंचांगi_mode);
	पूर्ण

	dwc3_omap_ग_लिखो_uपंचांगi_ctrl(omap, reg);
पूर्ण

अटल पूर्णांक dwc3_omap_extcon_रेजिस्टर(काष्ठा dwc3_omap *omap)
अणु
	पूर्णांक			ret;
	काष्ठा device_node	*node = omap->dev->of_node;
	काष्ठा extcon_dev	*edev;

	अगर (of_property_पढ़ो_bool(node, "extcon")) अणु
		edev = extcon_get_edev_by_phandle(omap->dev, 0);
		अगर (IS_ERR(edev)) अणु
			dev_vdbg(omap->dev, "couldn't get extcon device\n");
			वापस -EPROBE_DEFER;
		पूर्ण

		omap->vbus_nb.notअगरier_call = dwc3_omap_vbus_notअगरier;
		ret = devm_extcon_रेजिस्टर_notअगरier(omap->dev, edev,
						EXTCON_USB, &omap->vbus_nb);
		अगर (ret < 0)
			dev_vdbg(omap->dev, "failed to register notifier for USB\n");

		omap->id_nb.notअगरier_call = dwc3_omap_id_notअगरier;
		ret = devm_extcon_रेजिस्टर_notअगरier(omap->dev, edev,
						EXTCON_USB_HOST, &omap->id_nb);
		अगर (ret < 0)
			dev_vdbg(omap->dev, "failed to register notifier for USB-HOST\n");

		अगर (extcon_get_state(edev, EXTCON_USB) == true)
			dwc3_omap_set_mailbox(omap, OMAP_DWC3_VBUS_VALID);
		अन्यथा
			dwc3_omap_set_mailbox(omap, OMAP_DWC3_VBUS_OFF);

		अगर (extcon_get_state(edev, EXTCON_USB_HOST) == true)
			dwc3_omap_set_mailbox(omap, OMAP_DWC3_ID_GROUND);
		अन्यथा
			dwc3_omap_set_mailbox(omap, OMAP_DWC3_ID_FLOAT);

		omap->edev = edev;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_omap_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node	*node = pdev->dev.of_node;

	काष्ठा dwc3_omap	*omap;
	काष्ठा device		*dev = &pdev->dev;
	काष्ठा regulator	*vbus_reg = शून्य;

	पूर्णांक			ret;
	पूर्णांक			irq;

	व्योम __iomem		*base;

	अगर (!node) अणु
		dev_err(dev, "device node not found\n");
		वापस -EINVAL;
	पूर्ण

	omap = devm_kzalloc(dev, माप(*omap), GFP_KERNEL);
	अगर (!omap)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, omap);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	अगर (of_property_पढ़ो_bool(node, "vbus-supply")) अणु
		vbus_reg = devm_regulator_get(dev, "vbus");
		अगर (IS_ERR(vbus_reg)) अणु
			dev_err(dev, "vbus init failed\n");
			वापस PTR_ERR(vbus_reg);
		पूर्ण
	पूर्ण

	omap->dev	= dev;
	omap->irq	= irq;
	omap->base	= base;
	omap->vbus_reg	= vbus_reg;

	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "get_sync failed with err %d\n", ret);
		जाओ err1;
	पूर्ण

	dwc3_omap_map_offset(omap);
	dwc3_omap_set_uपंचांगi_mode(omap);

	ret = dwc3_omap_extcon_रेजिस्टर(omap);
	अगर (ret < 0)
		जाओ err1;

	ret = of_platक्रमm_populate(node, शून्य, शून्य, dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to create dwc3 core\n");
		जाओ err1;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, omap->irq, dwc3_omap_पूर्णांकerrupt,
					dwc3_omap_पूर्णांकerrupt_thपढ़ो, IRQF_SHARED,
					"dwc3-omap", omap);
	अगर (ret) अणु
		dev_err(dev, "failed to request IRQ #%d --> %d\n",
			omap->irq, ret);
		जाओ err1;
	पूर्ण
	dwc3_omap_enable_irqs(omap);
	वापस 0;

err1:
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_omap_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dwc3_omap	*omap = platक्रमm_get_drvdata(pdev);

	dwc3_omap_disable_irqs(omap);
	disable_irq(omap->irq);
	of_platक्रमm_depopulate(omap->dev);
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_dwc3_match[] = अणु
	अणु
		.compatible =	"ti,dwc3"
	पूर्ण,
	अणु
		.compatible =	"ti,am437x-dwc3"
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_dwc3_match);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक dwc3_omap_suspend(काष्ठा device *dev)
अणु
	काष्ठा dwc3_omap	*omap = dev_get_drvdata(dev);

	omap->uपंचांगi_otg_ctrl = dwc3_omap_पढ़ो_uपंचांगi_ctrl(omap);
	dwc3_omap_disable_irqs(omap);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_omap_resume(काष्ठा device *dev)
अणु
	काष्ठा dwc3_omap	*omap = dev_get_drvdata(dev);

	dwc3_omap_ग_लिखो_uपंचांगi_ctrl(omap, omap->uपंचांगi_otg_ctrl);
	dwc3_omap_enable_irqs(omap);

	pm_runसमय_disable(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	वापस 0;
पूर्ण

अटल व्योम dwc3_omap_complete(काष्ठा device *dev)
अणु
	काष्ठा dwc3_omap	*omap = dev_get_drvdata(dev);

	अगर (extcon_get_state(omap->edev, EXTCON_USB))
		dwc3_omap_set_mailbox(omap, OMAP_DWC3_VBUS_VALID);
	अन्यथा
		dwc3_omap_set_mailbox(omap, OMAP_DWC3_VBUS_OFF);

	अगर (extcon_get_state(omap->edev, EXTCON_USB_HOST))
		dwc3_omap_set_mailbox(omap, OMAP_DWC3_ID_GROUND);
	अन्यथा
		dwc3_omap_set_mailbox(omap, OMAP_DWC3_ID_FLOAT);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dwc3_omap_dev_pm_ops = अणु

	SET_SYSTEM_SLEEP_PM_OPS(dwc3_omap_suspend, dwc3_omap_resume)
	.complete = dwc3_omap_complete,
पूर्ण;

#घोषणा DEV_PM_OPS	(&dwc3_omap_dev_pm_ops)
#अन्यथा
#घोषणा DEV_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा platक्रमm_driver dwc3_omap_driver = अणु
	.probe		= dwc3_omap_probe,
	.हटाओ		= dwc3_omap_हटाओ,
	.driver		= अणु
		.name	= "omap-dwc3",
		.of_match_table	= of_dwc3_match,
		.pm	= DEV_PM_OPS,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dwc3_omap_driver);

MODULE_ALIAS("platform:omap-dwc3");
MODULE_AUTHOR("Felipe Balbi <balbi@ti.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("DesignWare USB3 OMAP Glue Layer");
