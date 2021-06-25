<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Nuvoton Technology corporation.

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of_address.h>

/* NPCM7xx GCR रेजिस्टरs */
#घोषणा NPCM_MDLR_OFFSET	0x7C
#घोषणा NPCM_MDLR_USBD0		BIT(9)
#घोषणा NPCM_MDLR_USBD1		BIT(8)
#घोषणा NPCM_MDLR_USBD2_4	BIT(21)
#घोषणा NPCM_MDLR_USBD5_9	BIT(22)

#घोषणा NPCM_USB1PHYCTL_OFFSET	0x140
#घोषणा NPCM_USB2PHYCTL_OFFSET	0x144
#घोषणा NPCM_USBXPHYCTL_RS	BIT(28)

/* NPCM7xx Reset रेजिस्टरs */
#घोषणा NPCM_SWRSTR		0x14
#घोषणा NPCM_SWRST		BIT(2)

#घोषणा NPCM_IPSRST1		0x20
#घोषणा NPCM_IPSRST1_USBD1	BIT(5)
#घोषणा NPCM_IPSRST1_USBD2	BIT(8)
#घोषणा NPCM_IPSRST1_USBD3	BIT(25)
#घोषणा NPCM_IPSRST1_USBD4	BIT(22)
#घोषणा NPCM_IPSRST1_USBD5	BIT(23)
#घोषणा NPCM_IPSRST1_USBD6	BIT(24)

#घोषणा NPCM_IPSRST2		0x24
#घोषणा NPCM_IPSRST2_USB_HOST	BIT(26)

#घोषणा NPCM_IPSRST3		0x34
#घोषणा NPCM_IPSRST3_USBD0	BIT(4)
#घोषणा NPCM_IPSRST3_USBD7	BIT(5)
#घोषणा NPCM_IPSRST3_USBD8	BIT(6)
#घोषणा NPCM_IPSRST3_USBD9	BIT(7)
#घोषणा NPCM_IPSRST3_USBPHY1	BIT(24)
#घोषणा NPCM_IPSRST3_USBPHY2	BIT(25)

#घोषणा NPCM_RC_RESETS_PER_REG	32
#घोषणा NPCM_MASK_RESETS	GENMASK(4, 0)

काष्ठा npcm_rc_data अणु
	काष्ठा reset_controller_dev rcdev;
	काष्ठा notअगरier_block restart_nb;
	u32 sw_reset_number;
	व्योम __iomem *base;
	spinlock_t lock;
पूर्ण;

#घोषणा to_rc_data(p) container_of(p, काष्ठा npcm_rc_data, rcdev)

अटल पूर्णांक npcm_rc_restart(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ mode,
			   व्योम *cmd)
अणु
	काष्ठा npcm_rc_data *rc = container_of(nb, काष्ठा npcm_rc_data,
					       restart_nb);

	ग_लिखोl(NPCM_SWRST << rc->sw_reset_number, rc->base + NPCM_SWRSTR);
	mdelay(1000);

	pr_emerg("%s: unable to restart system\n", __func__);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक npcm_rc_setclear_reset(काष्ठा reset_controller_dev *rcdev,
				  अचिन्हित दीर्घ id, bool set)
अणु
	काष्ठा npcm_rc_data *rc = to_rc_data(rcdev);
	अचिन्हित पूर्णांक rst_bit = BIT(id & NPCM_MASK_RESETS);
	अचिन्हित पूर्णांक ctrl_offset = id >> 8;
	अचिन्हित दीर्घ flags;
	u32 stat;

	spin_lock_irqsave(&rc->lock, flags);
	stat = पढ़ोl(rc->base + ctrl_offset);
	अगर (set)
		ग_लिखोl(stat | rst_bit, rc->base + ctrl_offset);
	अन्यथा
		ग_लिखोl(stat & ~rst_bit, rc->base + ctrl_offset);
	spin_unlock_irqrestore(&rc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक npcm_rc_निश्चित(काष्ठा reset_controller_dev *rcdev, अचिन्हित दीर्घ id)
अणु
	वापस npcm_rc_setclear_reset(rcdev, id, true);
पूर्ण

अटल पूर्णांक npcm_rc_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
			    अचिन्हित दीर्घ id)
अणु
	वापस npcm_rc_setclear_reset(rcdev, id, false);
पूर्ण

अटल पूर्णांक npcm_rc_status(काष्ठा reset_controller_dev *rcdev,
			  अचिन्हित दीर्घ id)
अणु
	काष्ठा npcm_rc_data *rc = to_rc_data(rcdev);
	अचिन्हित पूर्णांक rst_bit = BIT(id & NPCM_MASK_RESETS);
	अचिन्हित पूर्णांक ctrl_offset = id >> 8;

	वापस (पढ़ोl(rc->base + ctrl_offset) & rst_bit);
पूर्ण

अटल पूर्णांक npcm_reset_xlate(काष्ठा reset_controller_dev *rcdev,
			    स्थिर काष्ठा of_phandle_args *reset_spec)
अणु
	अचिन्हित पूर्णांक offset, bit;

	offset = reset_spec->args[0];
	अगर (offset != NPCM_IPSRST1 && offset != NPCM_IPSRST2 &&
	    offset != NPCM_IPSRST3) अणु
		dev_err(rcdev->dev, "Error reset register (0x%x)\n", offset);
		वापस -EINVAL;
	पूर्ण
	bit = reset_spec->args[1];
	अगर (bit >= NPCM_RC_RESETS_PER_REG) अणु
		dev_err(rcdev->dev, "Error reset number (%d)\n", bit);
		वापस -EINVAL;
	पूर्ण

	वापस (offset << 8) | bit;
पूर्ण

अटल स्थिर काष्ठा of_device_id npcm_rc_match[] = अणु
	अणु .compatible = "nuvoton,npcm750-reset",
		.data = (व्योम *)"nuvoton,npcm750-gcr" पूर्ण,
	अणु पूर्ण
पूर्ण;

/*
 *  The following procedure should be observed in USB PHY, USB device and
 *  USB host initialization at BMC boot
 */
अटल पूर्णांक npcm_usb_reset(काष्ठा platक्रमm_device *pdev, काष्ठा npcm_rc_data *rc)
अणु
	u32 mdlr, iprst1, iprst2, iprst3;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regmap *gcr_regmap;
	u32 ipsrst1_bits = 0;
	u32 ipsrst2_bits = NPCM_IPSRST2_USB_HOST;
	u32 ipsrst3_bits = 0;
	स्थिर अक्षर *gcr_dt;

	gcr_dt = (स्थिर अक्षर *)
	of_match_device(dev->driver->of_match_table, dev)->data;

	gcr_regmap = syscon_regmap_lookup_by_compatible(gcr_dt);
	अगर (IS_ERR(gcr_regmap)) अणु
		dev_err(&pdev->dev, "Failed to find %s\n", gcr_dt);
		वापस PTR_ERR(gcr_regmap);
	पूर्ण

	/* checking which USB device is enabled */
	regmap_पढ़ो(gcr_regmap, NPCM_MDLR_OFFSET, &mdlr);
	अगर (!(mdlr & NPCM_MDLR_USBD0))
		ipsrst3_bits |= NPCM_IPSRST3_USBD0;
	अगर (!(mdlr & NPCM_MDLR_USBD1))
		ipsrst1_bits |= NPCM_IPSRST1_USBD1;
	अगर (!(mdlr & NPCM_MDLR_USBD2_4))
		ipsrst1_bits |= (NPCM_IPSRST1_USBD2 |
				 NPCM_IPSRST1_USBD3 |
				 NPCM_IPSRST1_USBD4);
	अगर (!(mdlr & NPCM_MDLR_USBD0)) अणु
		ipsrst1_bits |= (NPCM_IPSRST1_USBD5 |
				 NPCM_IPSRST1_USBD6);
		ipsrst3_bits |= (NPCM_IPSRST3_USBD7 |
				 NPCM_IPSRST3_USBD8 |
				 NPCM_IPSRST3_USBD9);
	पूर्ण

	/* निश्चित reset USB PHY and USB devices */
	iprst1 = पढ़ोl(rc->base + NPCM_IPSRST1);
	iprst2 = पढ़ोl(rc->base + NPCM_IPSRST2);
	iprst3 = पढ़ोl(rc->base + NPCM_IPSRST3);

	iprst1 |= ipsrst1_bits;
	iprst2 |= ipsrst2_bits;
	iprst3 |= (ipsrst3_bits | NPCM_IPSRST3_USBPHY1 |
		   NPCM_IPSRST3_USBPHY2);

	ग_लिखोl(iprst1, rc->base + NPCM_IPSRST1);
	ग_लिखोl(iprst2, rc->base + NPCM_IPSRST2);
	ग_लिखोl(iprst3, rc->base + NPCM_IPSRST3);

	/* clear USB PHY RS bit */
	regmap_update_bits(gcr_regmap, NPCM_USB1PHYCTL_OFFSET,
			   NPCM_USBXPHYCTL_RS, 0);
	regmap_update_bits(gcr_regmap, NPCM_USB2PHYCTL_OFFSET,
			   NPCM_USBXPHYCTL_RS, 0);

	/* deनिश्चित reset USB PHY */
	iprst3 &= ~(NPCM_IPSRST3_USBPHY1 | NPCM_IPSRST3_USBPHY2);
	ग_लिखोl(iprst3, rc->base + NPCM_IPSRST3);

	udelay(50);

	/* set USB PHY RS bit */
	regmap_update_bits(gcr_regmap, NPCM_USB1PHYCTL_OFFSET,
			   NPCM_USBXPHYCTL_RS, NPCM_USBXPHYCTL_RS);
	regmap_update_bits(gcr_regmap, NPCM_USB2PHYCTL_OFFSET,
			   NPCM_USBXPHYCTL_RS, NPCM_USBXPHYCTL_RS);

	/* deनिश्चित reset USB devices*/
	iprst1 &= ~ipsrst1_bits;
	iprst2 &= ~ipsrst2_bits;
	iprst3 &= ~ipsrst3_bits;

	ग_लिखोl(iprst1, rc->base + NPCM_IPSRST1);
	ग_लिखोl(iprst2, rc->base + NPCM_IPSRST2);
	ग_लिखोl(iprst3, rc->base + NPCM_IPSRST3);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops npcm_rc_ops = अणु
	.निश्चित		= npcm_rc_निश्चित,
	.deनिश्चित	= npcm_rc_deनिश्चित,
	.status		= npcm_rc_status,
पूर्ण;

अटल पूर्णांक npcm_rc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा npcm_rc_data *rc;
	पूर्णांक ret;

	rc = devm_kzalloc(&pdev->dev, माप(*rc), GFP_KERNEL);
	अगर (!rc)
		वापस -ENOMEM;

	rc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rc->base))
		वापस PTR_ERR(rc->base);

	spin_lock_init(&rc->lock);

	rc->rcdev.owner = THIS_MODULE;
	rc->rcdev.ops = &npcm_rc_ops;
	rc->rcdev.of_node = pdev->dev.of_node;
	rc->rcdev.of_reset_n_cells = 2;
	rc->rcdev.of_xlate = npcm_reset_xlate;

	platक्रमm_set_drvdata(pdev, rc);

	ret = devm_reset_controller_रेजिस्टर(&pdev->dev, &rc->rcdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to register device\n");
		वापस ret;
	पूर्ण

	अगर (npcm_usb_reset(pdev, rc))
		dev_warn(&pdev->dev, "NPCM USB reset failed, can cause issues with UDC and USB host\n");

	अगर (!of_property_पढ़ो_u32(pdev->dev.of_node, "nuvoton,sw-reset-number",
				  &rc->sw_reset_number)) अणु
		अगर (rc->sw_reset_number && rc->sw_reset_number < 5) अणु
			rc->restart_nb.priority = 192,
			rc->restart_nb.notअगरier_call = npcm_rc_restart,
			ret = रेजिस्टर_restart_handler(&rc->restart_nb);
			अगर (ret)
				dev_warn(&pdev->dev, "failed to register restart handler\n");
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver npcm_rc_driver = अणु
	.probe	= npcm_rc_probe,
	.driver	= अणु
		.name			= "npcm-reset",
		.of_match_table		= npcm_rc_match,
		.suppress_bind_attrs	= true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(npcm_rc_driver);
