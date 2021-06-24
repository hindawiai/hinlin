<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas R-Car Gen3 क्रम USB2.0 PHY driver
 *
 * Copyright (C) 2015-2017 Renesas Electronics Corporation
 *
 * This is based on the phy-rcar-gen2 driver:
 * Copyright (C) 2014 Renesas Solutions Corp.
 * Copyright (C) 2014 Cogent Embedded, Inc.
 */

#समावेश <linux/extcon-provider.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/माला.स>
#समावेश <linux/usb/of.h>
#समावेश <linux/workqueue.h>

/******* USB2.0 Host रेजिस्टरs (original offset is +0x200) *******/
#घोषणा USB2_INT_ENABLE		0x000
#घोषणा USB2_USBCTR		0x00c
#घोषणा USB2_SPD_RSM_TIMSET	0x10c
#घोषणा USB2_OC_TIMSET		0x110
#घोषणा USB2_COMMCTRL		0x600
#घोषणा USB2_OBINTSTA		0x604
#घोषणा USB2_OBINTEN		0x608
#घोषणा USB2_VBCTRL		0x60c
#घोषणा USB2_LINECTRL1		0x610
#घोषणा USB2_ADPCTRL		0x630

/* INT_ENABLE */
#घोषणा USB2_INT_ENABLE_UCOM_INTEN	BIT(3)
#घोषणा USB2_INT_ENABLE_USBH_INTB_EN	BIT(2)	/* For EHCI */
#घोषणा USB2_INT_ENABLE_USBH_INTA_EN	BIT(1)	/* For OHCI */

/* USBCTR */
#घोषणा USB2_USBCTR_सूचीPD	BIT(2)
#घोषणा USB2_USBCTR_PLL_RST	BIT(1)

/* SPD_RSM_TIMSET */
#घोषणा USB2_SPD_RSM_TIMSET_INIT	0x014e029b

/* OC_TIMSET */
#घोषणा USB2_OC_TIMSET_INIT		0x000209ab

/* COMMCTRL */
#घोषणा USB2_COMMCTRL_OTG_PERI		BIT(31)	/* 1 = Peripheral mode */

/* OBINTSTA and OBINTEN */
#घोषणा USB2_OBINT_SESSVLDCHG		BIT(12)
#घोषणा USB2_OBINT_IDDIGCHG		BIT(11)
#घोषणा USB2_OBINT_BITS			(USB2_OBINT_SESSVLDCHG | \
					 USB2_OBINT_IDDIGCHG)

/* VBCTRL */
#घोषणा USB2_VBCTRL_OCCLREN		BIT(16)
#घोषणा USB2_VBCTRL_DRVVBUSSEL		BIT(8)

/* LINECTRL1 */
#घोषणा USB2_LINECTRL1_DPRPD_EN		BIT(19)
#घोषणा USB2_LINECTRL1_DP_RPD		BIT(18)
#घोषणा USB2_LINECTRL1_DMRPD_EN		BIT(17)
#घोषणा USB2_LINECTRL1_DM_RPD		BIT(16)
#घोषणा USB2_LINECTRL1_OPMODE_NODRV	BIT(6)

/* ADPCTRL */
#घोषणा USB2_ADPCTRL_OTGSESSVLD		BIT(20)
#घोषणा USB2_ADPCTRL_IDDIG		BIT(19)
#घोषणा USB2_ADPCTRL_IDPULLUP		BIT(5)	/* 1 = ID sampling is enabled */
#घोषणा USB2_ADPCTRL_DRVVBUS		BIT(4)

#घोषणा NUM_OF_PHYS			4
क्रमागत rcar_gen3_phy_index अणु
	PHY_INDEX_BOTH_HC,
	PHY_INDEX_OHCI,
	PHY_INDEX_EHCI,
	PHY_INDEX_HSUSB
पूर्ण;

अटल स्थिर u32 rcar_gen3_पूर्णांक_enable[NUM_OF_PHYS] = अणु
	USB2_INT_ENABLE_USBH_INTB_EN | USB2_INT_ENABLE_USBH_INTA_EN,
	USB2_INT_ENABLE_USBH_INTA_EN,
	USB2_INT_ENABLE_USBH_INTB_EN,
	0
पूर्ण;

काष्ठा rcar_gen3_phy अणु
	काष्ठा phy *phy;
	काष्ठा rcar_gen3_chan *ch;
	u32 पूर्णांक_enable_bits;
	bool initialized;
	bool otg_initialized;
	bool घातered;
पूर्ण;

काष्ठा rcar_gen3_chan अणु
	व्योम __iomem *base;
	काष्ठा device *dev;	/* platक्रमm_device's device */
	काष्ठा extcon_dev *extcon;
	काष्ठा rcar_gen3_phy rphys[NUM_OF_PHYS];
	काष्ठा regulator *vbus;
	काष्ठा work_काष्ठा work;
	काष्ठा mutex lock;	/* protects rphys[...].घातered */
	क्रमागत usb_dr_mode dr_mode;
	पूर्णांक irq;
	bool extcon_host;
	bool is_otg_channel;
	bool uses_otg_pins;
पूर्ण;

/*
 * Combination about is_otg_channel and uses_otg_pins:
 *
 * Parameters				|| Behaviors
 * is_otg_channel	| uses_otg_pins	|| irqs		| role sysfs
 * ---------------------+---------------++--------------+------------
 * true			| true		|| enabled	| enabled
 * true                 | false		|| disabled	| enabled
 * false                | any		|| disabled	| disabled
 */

अटल व्योम rcar_gen3_phy_usb2_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rcar_gen3_chan *ch = container_of(work, काष्ठा rcar_gen3_chan,
						 work);

	अगर (ch->extcon_host) अणु
		extcon_set_state_sync(ch->extcon, EXTCON_USB_HOST, true);
		extcon_set_state_sync(ch->extcon, EXTCON_USB, false);
	पूर्ण अन्यथा अणु
		extcon_set_state_sync(ch->extcon, EXTCON_USB_HOST, false);
		extcon_set_state_sync(ch->extcon, EXTCON_USB, true);
	पूर्ण
पूर्ण

अटल व्योम rcar_gen3_set_host_mode(काष्ठा rcar_gen3_chan *ch, पूर्णांक host)
अणु
	व्योम __iomem *usb2_base = ch->base;
	u32 val = पढ़ोl(usb2_base + USB2_COMMCTRL);

	dev_vdbg(ch->dev, "%s: %08x, %d\n", __func__, val, host);
	अगर (host)
		val &= ~USB2_COMMCTRL_OTG_PERI;
	अन्यथा
		val |= USB2_COMMCTRL_OTG_PERI;
	ग_लिखोl(val, usb2_base + USB2_COMMCTRL);
पूर्ण

अटल व्योम rcar_gen3_set_linectrl(काष्ठा rcar_gen3_chan *ch, पूर्णांक dp, पूर्णांक dm)
अणु
	व्योम __iomem *usb2_base = ch->base;
	u32 val = पढ़ोl(usb2_base + USB2_LINECTRL1);

	dev_vdbg(ch->dev, "%s: %08x, %d, %d\n", __func__, val, dp, dm);
	val &= ~(USB2_LINECTRL1_DP_RPD | USB2_LINECTRL1_DM_RPD);
	अगर (dp)
		val |= USB2_LINECTRL1_DP_RPD;
	अगर (dm)
		val |= USB2_LINECTRL1_DM_RPD;
	ग_लिखोl(val, usb2_base + USB2_LINECTRL1);
पूर्ण

अटल व्योम rcar_gen3_enable_vbus_ctrl(काष्ठा rcar_gen3_chan *ch, पूर्णांक vbus)
अणु
	व्योम __iomem *usb2_base = ch->base;
	u32 val = पढ़ोl(usb2_base + USB2_ADPCTRL);

	dev_vdbg(ch->dev, "%s: %08x, %d\n", __func__, val, vbus);
	अगर (vbus)
		val |= USB2_ADPCTRL_DRVVBUS;
	अन्यथा
		val &= ~USB2_ADPCTRL_DRVVBUS;
	ग_लिखोl(val, usb2_base + USB2_ADPCTRL);
पूर्ण

अटल व्योम rcar_gen3_control_otg_irq(काष्ठा rcar_gen3_chan *ch, पूर्णांक enable)
अणु
	व्योम __iomem *usb2_base = ch->base;
	u32 val = पढ़ोl(usb2_base + USB2_OBINTEN);

	अगर (ch->uses_otg_pins && enable)
		val |= USB2_OBINT_BITS;
	अन्यथा
		val &= ~USB2_OBINT_BITS;
	ग_लिखोl(val, usb2_base + USB2_OBINTEN);
पूर्ण

अटल व्योम rcar_gen3_init_क्रम_host(काष्ठा rcar_gen3_chan *ch)
अणु
	rcar_gen3_set_linectrl(ch, 1, 1);
	rcar_gen3_set_host_mode(ch, 1);
	rcar_gen3_enable_vbus_ctrl(ch, 1);

	ch->extcon_host = true;
	schedule_work(&ch->work);
पूर्ण

अटल व्योम rcar_gen3_init_क्रम_peri(काष्ठा rcar_gen3_chan *ch)
अणु
	rcar_gen3_set_linectrl(ch, 0, 1);
	rcar_gen3_set_host_mode(ch, 0);
	rcar_gen3_enable_vbus_ctrl(ch, 0);

	ch->extcon_host = false;
	schedule_work(&ch->work);
पूर्ण

अटल व्योम rcar_gen3_init_क्रम_b_host(काष्ठा rcar_gen3_chan *ch)
अणु
	व्योम __iomem *usb2_base = ch->base;
	u32 val;

	val = पढ़ोl(usb2_base + USB2_LINECTRL1);
	ग_लिखोl(val | USB2_LINECTRL1_OPMODE_NODRV, usb2_base + USB2_LINECTRL1);

	rcar_gen3_set_linectrl(ch, 1, 1);
	rcar_gen3_set_host_mode(ch, 1);
	rcar_gen3_enable_vbus_ctrl(ch, 0);

	val = पढ़ोl(usb2_base + USB2_LINECTRL1);
	ग_लिखोl(val & ~USB2_LINECTRL1_OPMODE_NODRV, usb2_base + USB2_LINECTRL1);
पूर्ण

अटल व्योम rcar_gen3_init_क्रम_a_peri(काष्ठा rcar_gen3_chan *ch)
अणु
	rcar_gen3_set_linectrl(ch, 0, 1);
	rcar_gen3_set_host_mode(ch, 0);
	rcar_gen3_enable_vbus_ctrl(ch, 1);
पूर्ण

अटल व्योम rcar_gen3_init_from_a_peri_to_a_host(काष्ठा rcar_gen3_chan *ch)
अणु
	rcar_gen3_control_otg_irq(ch, 0);

	rcar_gen3_enable_vbus_ctrl(ch, 1);
	rcar_gen3_init_क्रम_host(ch);

	rcar_gen3_control_otg_irq(ch, 1);
पूर्ण

अटल bool rcar_gen3_check_id(काष्ठा rcar_gen3_chan *ch)
अणु
	अगर (!ch->uses_otg_pins)
		वापस (ch->dr_mode == USB_DR_MODE_HOST) ? false : true;

	वापस !!(पढ़ोl(ch->base + USB2_ADPCTRL) & USB2_ADPCTRL_IDDIG);
पूर्ण

अटल व्योम rcar_gen3_device_recognition(काष्ठा rcar_gen3_chan *ch)
अणु
	अगर (!rcar_gen3_check_id(ch))
		rcar_gen3_init_क्रम_host(ch);
	अन्यथा
		rcar_gen3_init_क्रम_peri(ch);
पूर्ण

अटल bool rcar_gen3_is_host(काष्ठा rcar_gen3_chan *ch)
अणु
	वापस !(पढ़ोl(ch->base + USB2_COMMCTRL) & USB2_COMMCTRL_OTG_PERI);
पूर्ण

अटल क्रमागत phy_mode rcar_gen3_get_phy_mode(काष्ठा rcar_gen3_chan *ch)
अणु
	अगर (rcar_gen3_is_host(ch))
		वापस PHY_MODE_USB_HOST;

	वापस PHY_MODE_USB_DEVICE;
पूर्ण

अटल bool rcar_gen3_is_any_rphy_initialized(काष्ठा rcar_gen3_chan *ch)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_OF_PHYS; i++) अणु
		अगर (ch->rphys[i].initialized)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool rcar_gen3_needs_init_otg(काष्ठा rcar_gen3_chan *ch)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_OF_PHYS; i++) अणु
		अगर (ch->rphys[i].otg_initialized)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool rcar_gen3_are_all_rphys_घातer_off(काष्ठा rcar_gen3_chan *ch)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_OF_PHYS; i++) अणु
		अगर (ch->rphys[i].घातered)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल sमाप_प्रकार role_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा rcar_gen3_chan *ch = dev_get_drvdata(dev);
	bool is_b_device;
	क्रमागत phy_mode cur_mode, new_mode;

	अगर (!ch->is_otg_channel || !rcar_gen3_is_any_rphy_initialized(ch))
		वापस -EIO;

	अगर (sysfs_streq(buf, "host"))
		new_mode = PHY_MODE_USB_HOST;
	अन्यथा अगर (sysfs_streq(buf, "peripheral"))
		new_mode = PHY_MODE_USB_DEVICE;
	अन्यथा
		वापस -EINVAL;

	/* is_b_device: true is B-Device. false is A-Device. */
	is_b_device = rcar_gen3_check_id(ch);
	cur_mode = rcar_gen3_get_phy_mode(ch);

	/* If current and new mode is the same, this वापसs the error */
	अगर (cur_mode == new_mode)
		वापस -EINVAL;

	अगर (new_mode == PHY_MODE_USB_HOST) अणु /* And is_host must be false */
		अगर (!is_b_device)	/* A-Peripheral */
			rcar_gen3_init_from_a_peri_to_a_host(ch);
		अन्यथा			/* B-Peripheral */
			rcar_gen3_init_क्रम_b_host(ch);
	पूर्ण अन्यथा अणु			/* And is_host must be true */
		अगर (!is_b_device)	/* A-Host */
			rcar_gen3_init_क्रम_a_peri(ch);
		अन्यथा			/* B-Host */
			rcar_gen3_init_क्रम_peri(ch);
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार role_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा rcar_gen3_chan *ch = dev_get_drvdata(dev);

	अगर (!ch->is_otg_channel || !rcar_gen3_is_any_rphy_initialized(ch))
		वापस -EIO;

	वापस प्र_लिखो(buf, "%s\n", rcar_gen3_is_host(ch) ? "host" :
							    "peripheral");
पूर्ण
अटल DEVICE_ATTR_RW(role);

अटल व्योम rcar_gen3_init_otg(काष्ठा rcar_gen3_chan *ch)
अणु
	व्योम __iomem *usb2_base = ch->base;
	u32 val;

	/* Should not use functions of पढ़ो-modअगरy-ग_लिखो a रेजिस्टर */
	val = पढ़ोl(usb2_base + USB2_LINECTRL1);
	val = (val & ~USB2_LINECTRL1_DP_RPD) | USB2_LINECTRL1_DPRPD_EN |
	      USB2_LINECTRL1_DMRPD_EN | USB2_LINECTRL1_DM_RPD;
	ग_लिखोl(val, usb2_base + USB2_LINECTRL1);

	val = पढ़ोl(usb2_base + USB2_VBCTRL);
	val &= ~USB2_VBCTRL_OCCLREN;
	ग_लिखोl(val | USB2_VBCTRL_DRVVBUSSEL, usb2_base + USB2_VBCTRL);
	val = पढ़ोl(usb2_base + USB2_ADPCTRL);
	ग_लिखोl(val | USB2_ADPCTRL_IDPULLUP, usb2_base + USB2_ADPCTRL);

	msleep(20);

	ग_लिखोl(0xffffffff, usb2_base + USB2_OBINTSTA);
	ग_लिखोl(USB2_OBINT_BITS, usb2_base + USB2_OBINTEN);

	rcar_gen3_device_recognition(ch);
पूर्ण

अटल irqवापस_t rcar_gen3_phy_usb2_irq(पूर्णांक irq, व्योम *_ch)
अणु
	काष्ठा rcar_gen3_chan *ch = _ch;
	व्योम __iomem *usb2_base = ch->base;
	u32 status = पढ़ोl(usb2_base + USB2_OBINTSTA);
	irqवापस_t ret = IRQ_NONE;

	अगर (status & USB2_OBINT_BITS) अणु
		dev_vdbg(ch->dev, "%s: %08x\n", __func__, status);
		ग_लिखोl(USB2_OBINT_BITS, usb2_base + USB2_OBINTSTA);
		rcar_gen3_device_recognition(ch);
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rcar_gen3_phy_usb2_init(काष्ठा phy *p)
अणु
	काष्ठा rcar_gen3_phy *rphy = phy_get_drvdata(p);
	काष्ठा rcar_gen3_chan *channel = rphy->ch;
	व्योम __iomem *usb2_base = channel->base;
	u32 val;
	पूर्णांक ret;

	अगर (!rcar_gen3_is_any_rphy_initialized(channel) && channel->irq >= 0) अणु
		INIT_WORK(&channel->work, rcar_gen3_phy_usb2_work);
		ret = request_irq(channel->irq, rcar_gen3_phy_usb2_irq,
				  IRQF_SHARED, dev_name(channel->dev), channel);
		अगर (ret < 0) अणु
			dev_err(channel->dev, "No irq handler (%d)\n", channel->irq);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Initialize USB2 part */
	val = पढ़ोl(usb2_base + USB2_INT_ENABLE);
	val |= USB2_INT_ENABLE_UCOM_INTEN | rphy->पूर्णांक_enable_bits;
	ग_लिखोl(val, usb2_base + USB2_INT_ENABLE);
	ग_लिखोl(USB2_SPD_RSM_TIMSET_INIT, usb2_base + USB2_SPD_RSM_TIMSET);
	ग_लिखोl(USB2_OC_TIMSET_INIT, usb2_base + USB2_OC_TIMSET);

	/* Initialize otg part */
	अगर (channel->is_otg_channel) अणु
		अगर (rcar_gen3_needs_init_otg(channel))
			rcar_gen3_init_otg(channel);
		rphy->otg_initialized = true;
	पूर्ण

	rphy->initialized = true;

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_gen3_phy_usb2_निकास(काष्ठा phy *p)
अणु
	काष्ठा rcar_gen3_phy *rphy = phy_get_drvdata(p);
	काष्ठा rcar_gen3_chan *channel = rphy->ch;
	व्योम __iomem *usb2_base = channel->base;
	u32 val;

	rphy->initialized = false;

	अगर (channel->is_otg_channel)
		rphy->otg_initialized = false;

	val = पढ़ोl(usb2_base + USB2_INT_ENABLE);
	val &= ~rphy->पूर्णांक_enable_bits;
	अगर (!rcar_gen3_is_any_rphy_initialized(channel))
		val &= ~USB2_INT_ENABLE_UCOM_INTEN;
	ग_लिखोl(val, usb2_base + USB2_INT_ENABLE);

	अगर (channel->irq >= 0 && !rcar_gen3_is_any_rphy_initialized(channel))
		मुक्त_irq(channel->irq, channel);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_gen3_phy_usb2_घातer_on(काष्ठा phy *p)
अणु
	काष्ठा rcar_gen3_phy *rphy = phy_get_drvdata(p);
	काष्ठा rcar_gen3_chan *channel = rphy->ch;
	व्योम __iomem *usb2_base = channel->base;
	u32 val;
	पूर्णांक ret = 0;

	mutex_lock(&channel->lock);
	अगर (!rcar_gen3_are_all_rphys_घातer_off(channel))
		जाओ out;

	अगर (channel->vbus) अणु
		ret = regulator_enable(channel->vbus);
		अगर (ret)
			जाओ out;
	पूर्ण

	val = पढ़ोl(usb2_base + USB2_USBCTR);
	val |= USB2_USBCTR_PLL_RST;
	ग_लिखोl(val, usb2_base + USB2_USBCTR);
	val &= ~USB2_USBCTR_PLL_RST;
	ग_लिखोl(val, usb2_base + USB2_USBCTR);

out:
	/* The घातered flag should be set क्रम any other phys anyway */
	rphy->घातered = true;
	mutex_unlock(&channel->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_gen3_phy_usb2_घातer_off(काष्ठा phy *p)
अणु
	काष्ठा rcar_gen3_phy *rphy = phy_get_drvdata(p);
	काष्ठा rcar_gen3_chan *channel = rphy->ch;
	पूर्णांक ret = 0;

	mutex_lock(&channel->lock);
	rphy->घातered = false;

	अगर (!rcar_gen3_are_all_rphys_घातer_off(channel))
		जाओ out;

	अगर (channel->vbus)
		ret = regulator_disable(channel->vbus);

out:
	mutex_unlock(&channel->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा phy_ops rcar_gen3_phy_usb2_ops = अणु
	.init		= rcar_gen3_phy_usb2_init,
	.निकास		= rcar_gen3_phy_usb2_निकास,
	.घातer_on	= rcar_gen3_phy_usb2_घातer_on,
	.घातer_off	= rcar_gen3_phy_usb2_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा phy_ops rz_g1c_phy_usb2_ops = अणु
	.init		= rcar_gen3_phy_usb2_init,
	.निकास		= rcar_gen3_phy_usb2_निकास,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rcar_gen3_phy_usb2_match_table[] = अणु
	अणु
		.compatible = "renesas,usb2-phy-r8a77470",
		.data = &rz_g1c_phy_usb2_ops,
	पूर्ण,
	अणु
		.compatible = "renesas,usb2-phy-r8a7795",
		.data = &rcar_gen3_phy_usb2_ops,
	पूर्ण,
	अणु
		.compatible = "renesas,usb2-phy-r8a7796",
		.data = &rcar_gen3_phy_usb2_ops,
	पूर्ण,
	अणु
		.compatible = "renesas,usb2-phy-r8a77965",
		.data = &rcar_gen3_phy_usb2_ops,
	पूर्ण,
	अणु
		.compatible = "renesas,rcar-gen3-usb2-phy",
		.data = &rcar_gen3_phy_usb2_ops,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rcar_gen3_phy_usb2_match_table);

अटल स्थिर अचिन्हित पूर्णांक rcar_gen3_phy_cable[] = अणु
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_NONE,
पूर्ण;

अटल काष्ठा phy *rcar_gen3_phy_usb2_xlate(काष्ठा device *dev,
					    काष्ठा of_phandle_args *args)
अणु
	काष्ठा rcar_gen3_chan *ch = dev_get_drvdata(dev);

	अगर (args->args_count == 0)	/* For old version dts */
		वापस ch->rphys[PHY_INDEX_BOTH_HC].phy;
	अन्यथा अगर (args->args_count > 1)	/* Prevent invalid args count */
		वापस ERR_PTR(-ENODEV);

	अगर (args->args[0] >= NUM_OF_PHYS)
		वापस ERR_PTR(-ENODEV);

	वापस ch->rphys[args->args[0]].phy;
पूर्ण

अटल क्रमागत usb_dr_mode rcar_gen3_get_dr_mode(काष्ठा device_node *np)
अणु
	क्रमागत usb_dr_mode candidate = USB_DR_MODE_UNKNOWN;
	पूर्णांक i;

	/*
	 * If one of device nodes has other dr_mode except UNKNOWN,
	 * this function वापसs UNKNOWN. To achieve backward compatibility,
	 * this loop starts the index as 0.
	 */
	क्रम (i = 0; i < NUM_OF_PHYS; i++) अणु
		क्रमागत usb_dr_mode mode = of_usb_get_dr_mode_by_phy(np, i);

		अगर (mode != USB_DR_MODE_UNKNOWN) अणु
			अगर (candidate == USB_DR_MODE_UNKNOWN)
				candidate = mode;
			अन्यथा अगर (candidate != mode)
				वापस USB_DR_MODE_UNKNOWN;
		पूर्ण
	पूर्ण

	वापस candidate;
पूर्ण

अटल पूर्णांक rcar_gen3_phy_usb2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rcar_gen3_chan *channel;
	काष्ठा phy_provider *provider;
	स्थिर काष्ठा phy_ops *phy_usb2_ops;
	पूर्णांक ret = 0, i;

	अगर (!dev->of_node) अणु
		dev_err(dev, "This driver needs device tree\n");
		वापस -EINVAL;
	पूर्ण

	channel = devm_kzalloc(dev, माप(*channel), GFP_KERNEL);
	अगर (!channel)
		वापस -ENOMEM;

	channel->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(channel->base))
		वापस PTR_ERR(channel->base);

	/* get irq number here and request_irq क्रम OTG in phy_init */
	channel->irq = platक्रमm_get_irq_optional(pdev, 0);
	channel->dr_mode = rcar_gen3_get_dr_mode(dev->of_node);
	अगर (channel->dr_mode != USB_DR_MODE_UNKNOWN) अणु
		पूर्णांक ret;

		channel->is_otg_channel = true;
		channel->uses_otg_pins = !of_property_पढ़ो_bool(dev->of_node,
							"renesas,no-otg-pins");
		channel->extcon = devm_extcon_dev_allocate(dev,
							rcar_gen3_phy_cable);
		अगर (IS_ERR(channel->extcon))
			वापस PTR_ERR(channel->extcon);

		ret = devm_extcon_dev_रेजिस्टर(dev, channel->extcon);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to register extcon\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * devm_phy_create() will call pm_runसमय_enable(&phy->dev);
	 * And then, phy-core will manage runसमय pm क्रम this device.
	 */
	pm_runसमय_enable(dev);
	phy_usb2_ops = of_device_get_match_data(dev);
	अगर (!phy_usb2_ops) अणु
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	mutex_init(&channel->lock);
	क्रम (i = 0; i < NUM_OF_PHYS; i++) अणु
		channel->rphys[i].phy = devm_phy_create(dev, शून्य,
							phy_usb2_ops);
		अगर (IS_ERR(channel->rphys[i].phy)) अणु
			dev_err(dev, "Failed to create USB2 PHY\n");
			ret = PTR_ERR(channel->rphys[i].phy);
			जाओ error;
		पूर्ण
		channel->rphys[i].ch = channel;
		channel->rphys[i].पूर्णांक_enable_bits = rcar_gen3_पूर्णांक_enable[i];
		phy_set_drvdata(channel->rphys[i].phy, &channel->rphys[i]);
	पूर्ण

	channel->vbus = devm_regulator_get_optional(dev, "vbus");
	अगर (IS_ERR(channel->vbus)) अणु
		अगर (PTR_ERR(channel->vbus) == -EPROBE_DEFER) अणु
			ret = PTR_ERR(channel->vbus);
			जाओ error;
		पूर्ण
		channel->vbus = शून्य;
	पूर्ण

	platक्रमm_set_drvdata(pdev, channel);
	channel->dev = dev;

	provider = devm_of_phy_provider_रेजिस्टर(dev, rcar_gen3_phy_usb2_xlate);
	अगर (IS_ERR(provider)) अणु
		dev_err(dev, "Failed to register PHY provider\n");
		ret = PTR_ERR(provider);
		जाओ error;
	पूर्ण अन्यथा अगर (channel->is_otg_channel) अणु
		पूर्णांक ret;

		ret = device_create_file(dev, &dev_attr_role);
		अगर (ret < 0)
			जाओ error;
	पूर्ण

	वापस 0;

error:
	pm_runसमय_disable(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक rcar_gen3_phy_usb2_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_gen3_chan *channel = platक्रमm_get_drvdata(pdev);

	अगर (channel->is_otg_channel)
		device_हटाओ_file(&pdev->dev, &dev_attr_role);

	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण;

अटल काष्ठा platक्रमm_driver rcar_gen3_phy_usb2_driver = अणु
	.driver = अणु
		.name		= "phy_rcar_gen3_usb2",
		.of_match_table	= rcar_gen3_phy_usb2_match_table,
	पूर्ण,
	.probe	= rcar_gen3_phy_usb2_probe,
	.हटाओ = rcar_gen3_phy_usb2_हटाओ,
पूर्ण;
module_platक्रमm_driver(rcar_gen3_phy_usb2_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Renesas R-Car Gen3 USB 2.0 PHY");
MODULE_AUTHOR("Yoshihiro Shimoda <yoshihiro.shimoda.uh@renesas.com>");
