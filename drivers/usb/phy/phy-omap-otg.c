<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * OMAP OTG controller driver
 *
 * Based on code from tahvo-usb.c and isp1301_omap.c drivers.
 *
 * Copyright (C) 2005-2006 Nokia Corporation
 * Copyright (C) 2004 Texas Instruments
 * Copyright (C) 2004 David Brownell
 */

#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/extcon.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/usb-omap1.h>

काष्ठा otg_device अणु
	व्योम __iomem			*base;
	bool				id;
	bool				vbus;
	काष्ठा extcon_dev		*extcon;
	काष्ठा notअगरier_block		vbus_nb;
	काष्ठा notअगरier_block		id_nb;
पूर्ण;

#घोषणा OMAP_OTG_CTRL		0x0c
#घोषणा OMAP_OTG_ASESSVLD	(1 << 20)
#घोषणा OMAP_OTG_BSESSEND	(1 << 19)
#घोषणा OMAP_OTG_BSESSVLD	(1 << 18)
#घोषणा OMAP_OTG_VBUSVLD	(1 << 17)
#घोषणा OMAP_OTG_ID		(1 << 16)
#घोषणा OMAP_OTG_XCEIV_OUTPUTS \
	(OMAP_OTG_ASESSVLD | OMAP_OTG_BSESSEND | OMAP_OTG_BSESSVLD | \
	 OMAP_OTG_VBUSVLD  | OMAP_OTG_ID)

अटल व्योम omap_otg_ctrl(काष्ठा otg_device *otg_dev, u32 outमाला_दो)
अणु
	u32 l;

	l = पढ़ोl(otg_dev->base + OMAP_OTG_CTRL);
	l &= ~OMAP_OTG_XCEIV_OUTPUTS;
	l |= outमाला_दो;
	ग_लिखोl(l, otg_dev->base + OMAP_OTG_CTRL);
पूर्ण

अटल व्योम omap_otg_set_mode(काष्ठा otg_device *otg_dev)
अणु
	अगर (!otg_dev->id && otg_dev->vbus)
		/* Set B-session valid. */
		omap_otg_ctrl(otg_dev, OMAP_OTG_ID | OMAP_OTG_BSESSVLD);
	अन्यथा अगर (otg_dev->vbus)
		/* Set A-session valid. */
		omap_otg_ctrl(otg_dev, OMAP_OTG_ASESSVLD);
	अन्यथा अगर (!otg_dev->id)
		/* Set B-session end to indicate no VBUS. */
		omap_otg_ctrl(otg_dev, OMAP_OTG_ID | OMAP_OTG_BSESSEND);
पूर्ण

अटल पूर्णांक omap_otg_id_notअगरier(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा otg_device *otg_dev = container_of(nb, काष्ठा otg_device, id_nb);

	otg_dev->id = event;
	omap_otg_set_mode(otg_dev);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक omap_otg_vbus_notअगरier(काष्ठा notअगरier_block *nb,
				  अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा otg_device *otg_dev = container_of(nb, काष्ठा otg_device,
						  vbus_nb);

	otg_dev->vbus = event;
	omap_otg_set_mode(otg_dev);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक omap_otg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा omap_usb_config *config = pdev->dev.platक्रमm_data;
	काष्ठा otg_device *otg_dev;
	काष्ठा extcon_dev *extcon;
	पूर्णांक ret;
	u32 rev;

	अगर (!config || !config->extcon)
		वापस -ENODEV;

	extcon = extcon_get_extcon_dev(config->extcon);
	अगर (!extcon)
		वापस -EPROBE_DEFER;

	otg_dev = devm_kzalloc(&pdev->dev, माप(*otg_dev), GFP_KERNEL);
	अगर (!otg_dev)
		वापस -ENOMEM;

	otg_dev->base = devm_ioremap_resource(&pdev->dev, &pdev->resource[0]);
	अगर (IS_ERR(otg_dev->base))
		वापस PTR_ERR(otg_dev->base);

	otg_dev->extcon = extcon;
	otg_dev->id_nb.notअगरier_call = omap_otg_id_notअगरier;
	otg_dev->vbus_nb.notअगरier_call = omap_otg_vbus_notअगरier;

	ret = devm_extcon_रेजिस्टर_notअगरier(&pdev->dev, extcon,
					EXTCON_USB_HOST, &otg_dev->id_nb);
	अगर (ret)
		वापस ret;

	ret = devm_extcon_रेजिस्टर_notअगरier(&pdev->dev, extcon,
					EXTCON_USB, &otg_dev->vbus_nb);
	अगर (ret) अणु
		वापस ret;
	पूर्ण

	otg_dev->id = extcon_get_state(extcon, EXTCON_USB_HOST);
	otg_dev->vbus = extcon_get_state(extcon, EXTCON_USB);
	omap_otg_set_mode(otg_dev);

	rev = पढ़ोl(otg_dev->base);

	dev_info(&pdev->dev,
		 "OMAP USB OTG controller rev %d.%d (%s, id=%d, vbus=%d)\n",
		 (rev >> 4) & 0xf, rev & 0xf, config->extcon, otg_dev->id,
		 otg_dev->vbus);

	platक्रमm_set_drvdata(pdev, otg_dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver omap_otg_driver = अणु
	.probe		= omap_otg_probe,
	.driver		= अणु
		.name	= "omap_otg",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(omap_otg_driver);

MODULE_DESCRIPTION("OMAP USB OTG controller driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aaro Koskinen <aaro.koskinen@iki.fi>");
