<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * phy-brcm-usb.c - Broadcom USB Phy Driver
 *
 * Copyright (C) 2015-2017 Broadcom
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/soc/brcmstb/brcmstb.h>
#समावेश <dt-bindings/phy/phy.h>
#समावेश <linux/mfd/syscon.h>

#समावेश "phy-brcm-usb-init.h"

अटल DEFINE_MUTEX(sysfs_lock);

क्रमागत brcm_usb_phy_id अणु
	BRCM_USB_PHY_2_0 = 0,
	BRCM_USB_PHY_3_0,
	BRCM_USB_PHY_ID_MAX
पूर्ण;

काष्ठा value_to_name_map अणु
	पूर्णांक value;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा match_chip_info अणु
	व्योम (*init_func)(काष्ठा brcm_usb_init_params *params);
	u8 required_regs[BRCM_REGS_MAX + 1];
	u8 optional_reg;
पूर्ण;

अटल स्थिर काष्ठा value_to_name_map brcm_dr_mode_to_name[] = अणु
	अणु USB_CTLR_MODE_HOST, "host" पूर्ण,
	अणु USB_CTLR_MODE_DEVICE, "peripheral" पूर्ण,
	अणु USB_CTLR_MODE_DRD, "drd" पूर्ण,
	अणु USB_CTLR_MODE_TYPEC_PD, "typec-pd" पूर्ण
पूर्ण;

अटल स्थिर काष्ठा value_to_name_map brcm_dual_mode_to_name[] = अणु
	अणु 0, "host" पूर्ण,
	अणु 1, "device" पूर्ण,
	अणु 2, "auto" पूर्ण,
पूर्ण;

काष्ठा brcm_usb_phy अणु
	काष्ठा phy *phy;
	अचिन्हित पूर्णांक id;
	bool inited;
पूर्ण;

काष्ठा brcm_usb_phy_data अणु
	काष्ठा  brcm_usb_init_params ini;
	bool			has_eohci;
	bool			has_xhci;
	काष्ठा clk		*usb_20_clk;
	काष्ठा clk		*usb_30_clk;
	काष्ठा clk		*suspend_clk;
	काष्ठा mutex		mutex;	/* serialize phy init */
	पूर्णांक			init_count;
	पूर्णांक			wake_irq;
	काष्ठा brcm_usb_phy	phys[BRCM_USB_PHY_ID_MAX];
पूर्ण;

अटल s8 *node_reg_names[BRCM_REGS_MAX] = अणु
	"crtl", "xhci_ec", "xhci_gbl", "usb_phy", "usb_mdio", "bdc_ec"
पूर्ण;

अटल irqवापस_t brcm_usb_phy_wake_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा phy *gphy = dev_id;

	pm_wakeup_event(&gphy->dev, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक brcm_usb_phy_init(काष्ठा phy *gphy)
अणु
	काष्ठा brcm_usb_phy *phy = phy_get_drvdata(gphy);
	काष्ठा brcm_usb_phy_data *priv =
		container_of(phy, काष्ठा brcm_usb_phy_data, phys[phy->id]);

	/*
	 * Use a lock to make sure a second caller रुकोs until
	 * the base phy is inited beक्रमe using it.
	 */
	mutex_lock(&priv->mutex);
	अगर (priv->init_count++ == 0) अणु
		clk_prepare_enable(priv->usb_20_clk);
		clk_prepare_enable(priv->usb_30_clk);
		clk_prepare_enable(priv->suspend_clk);
		brcm_usb_init_common(&priv->ini);
	पूर्ण
	mutex_unlock(&priv->mutex);
	अगर (phy->id == BRCM_USB_PHY_2_0)
		brcm_usb_init_eohci(&priv->ini);
	अन्यथा अगर (phy->id == BRCM_USB_PHY_3_0)
		brcm_usb_init_xhci(&priv->ini);
	phy->inited = true;
	dev_dbg(&gphy->dev, "INIT, id: %d, total: %d\n", phy->id,
		priv->init_count);

	वापस 0;
पूर्ण

अटल पूर्णांक brcm_usb_phy_निकास(काष्ठा phy *gphy)
अणु
	काष्ठा brcm_usb_phy *phy = phy_get_drvdata(gphy);
	काष्ठा brcm_usb_phy_data *priv =
		container_of(phy, काष्ठा brcm_usb_phy_data, phys[phy->id]);

	dev_dbg(&gphy->dev, "EXIT\n");
	अगर (phy->id == BRCM_USB_PHY_2_0)
		brcm_usb_uninit_eohci(&priv->ini);
	अगर (phy->id == BRCM_USB_PHY_3_0)
		brcm_usb_uninit_xhci(&priv->ini);

	/* If both xhci and eohci are gone, reset everything अन्यथा */
	mutex_lock(&priv->mutex);
	अगर (--priv->init_count == 0) अणु
		brcm_usb_uninit_common(&priv->ini);
		clk_disable_unprepare(priv->usb_20_clk);
		clk_disable_unprepare(priv->usb_30_clk);
		clk_disable_unprepare(priv->suspend_clk);
	पूर्ण
	mutex_unlock(&priv->mutex);
	phy->inited = false;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops brcm_usb_phy_ops = अणु
	.init		= brcm_usb_phy_init,
	.निकास		= brcm_usb_phy_निकास,
	.owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा phy *brcm_usb_phy_xlate(काष्ठा device *dev,
				      काष्ठा of_phandle_args *args)
अणु
	काष्ठा brcm_usb_phy_data *data = dev_get_drvdata(dev);

	/*
	 * values 0 and 1 are क्रम backward compatibility with
	 * device tree nodes from older bootloaders.
	 */
	चयन (args->args[0]) अणु
	हाल 0:
	हाल PHY_TYPE_USB2:
		अगर (data->phys[BRCM_USB_PHY_2_0].phy)
			वापस data->phys[BRCM_USB_PHY_2_0].phy;
		dev_warn(dev, "Error, 2.0 Phy not found\n");
		अवरोध;
	हाल 1:
	हाल PHY_TYPE_USB3:
		अगर (data->phys[BRCM_USB_PHY_3_0].phy)
			वापस data->phys[BRCM_USB_PHY_3_0].phy;
		dev_warn(dev, "Error, 3.0 Phy not found\n");
		अवरोध;
	पूर्ण
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल पूर्णांक name_to_value(स्थिर काष्ठा value_to_name_map *table, पूर्णांक count,
			 स्थिर अक्षर *name, पूर्णांक *value)
अणु
	पूर्णांक x;

	*value = 0;
	क्रम (x = 0; x < count; x++) अणु
		अगर (sysfs_streq(name, table[x].name)) अणु
			*value = x;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर अक्षर *value_to_name(स्थिर काष्ठा value_to_name_map *table, पूर्णांक count,
				 पूर्णांक value)
अणु
	अगर (value >= count)
		वापस "unknown";
	वापस table[value].name;
पूर्ण

अटल sमाप_प्रकार dr_mode_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा brcm_usb_phy_data *priv = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n",
		value_to_name(&brcm_dr_mode_to_name[0],
			      ARRAY_SIZE(brcm_dr_mode_to_name),
			      priv->ini.mode));
पूर्ण
अटल DEVICE_ATTR_RO(dr_mode);

अटल sमाप_प्रकार dual_select_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा brcm_usb_phy_data *priv = dev_get_drvdata(dev);
	पूर्णांक value;
	पूर्णांक res;

	mutex_lock(&sysfs_lock);
	res = name_to_value(&brcm_dual_mode_to_name[0],
			    ARRAY_SIZE(brcm_dual_mode_to_name), buf, &value);
	अगर (!res) अणु
		brcm_usb_set_dual_select(&priv->ini, value);
		res = len;
	पूर्ण
	mutex_unlock(&sysfs_lock);
	वापस res;
पूर्ण

अटल sमाप_प्रकार dual_select_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा brcm_usb_phy_data *priv = dev_get_drvdata(dev);
	पूर्णांक value;

	mutex_lock(&sysfs_lock);
	value = brcm_usb_get_dual_select(&priv->ini);
	mutex_unlock(&sysfs_lock);
	वापस प्र_लिखो(buf, "%s\n",
		value_to_name(&brcm_dual_mode_to_name[0],
			      ARRAY_SIZE(brcm_dual_mode_to_name),
			      value));
पूर्ण
अटल DEVICE_ATTR_RW(dual_select);

अटल काष्ठा attribute *brcm_usb_phy_attrs[] = अणु
	&dev_attr_dr_mode.attr,
	&dev_attr_dual_select.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group brcm_usb_phy_group = अणु
	.attrs = brcm_usb_phy_attrs,
पूर्ण;

अटल स्थिर काष्ठा match_chip_info chip_info_7216 = अणु
	.init_func = &brcm_usb_dvr_init_7216,
	.required_regs = अणु
		BRCM_REGS_CTRL,
		BRCM_REGS_XHCI_EC,
		BRCM_REGS_XHCI_GBL,
		-1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा match_chip_info chip_info_7211b0 = अणु
	.init_func = &brcm_usb_dvr_init_7211b0,
	.required_regs = अणु
		BRCM_REGS_CTRL,
		BRCM_REGS_XHCI_EC,
		BRCM_REGS_XHCI_GBL,
		BRCM_REGS_USB_PHY,
		BRCM_REGS_USB_MDIO,
		-1,
	पूर्ण,
	.optional_reg = BRCM_REGS_BDC_EC,
पूर्ण;

अटल स्थिर काष्ठा match_chip_info chip_info_7445 = अणु
	.init_func = &brcm_usb_dvr_init_7445,
	.required_regs = अणु
		BRCM_REGS_CTRL,
		BRCM_REGS_XHCI_EC,
		-1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id brcm_usb_dt_ids[] = अणु
	अणु
		.compatible = "brcm,bcm4908-usb-phy",
		.data = &chip_info_7445,
	पूर्ण,
	अणु
		.compatible = "brcm,bcm7216-usb-phy",
		.data = &chip_info_7216,
	पूर्ण,
	अणु
		.compatible = "brcm,bcm7211-usb-phy",
		.data = &chip_info_7211b0,
	पूर्ण,
	अणु
		.compatible = "brcm,brcmstb-usb-phy",
		.data = &chip_info_7445,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक brcm_usb_get_regs(काष्ठा platक्रमm_device *pdev,
			     क्रमागत brcmusb_reg_sel regs,
			     काष्ठा  brcm_usb_init_params *ini,
			     bool optional)
अणु
	काष्ठा resource *res;

	/* Older DT nodes have ctrl and optional xhci_ec by index only */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						node_reg_names[regs]);
	अगर (res == शून्य) अणु
		अगर (regs == BRCM_REGS_CTRL) अणु
			res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		पूर्ण अन्यथा अगर (regs == BRCM_REGS_XHCI_EC) अणु
			res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
			/* XHCI_EC रेजिस्टरs are optional */
			अगर (res == शून्य)
				वापस 0;
		पूर्ण
		अगर (res == शून्य) अणु
			अगर (optional) अणु
				dev_dbg(&pdev->dev,
					"Optional reg %s not found\n",
					node_reg_names[regs]);
				वापस 0;
			पूर्ण
			dev_err(&pdev->dev, "can't get %s base addr\n",
				node_reg_names[regs]);
			वापस 1;
		पूर्ण
	पूर्ण
	ini->regs[regs] = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(ini->regs[regs])) अणु
		dev_err(&pdev->dev, "can't map %s register space\n",
			node_reg_names[regs]);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक brcm_usb_phy_dvr_init(काष्ठा platक्रमm_device *pdev,
				 काष्ठा brcm_usb_phy_data *priv,
				 काष्ठा device_node *dn)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy *gphy = शून्य;
	पूर्णांक err;

	priv->usb_20_clk = of_clk_get_by_name(dn, "sw_usb");
	अगर (IS_ERR(priv->usb_20_clk)) अणु
		अगर (PTR_ERR(priv->usb_20_clk) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_info(dev, "Clock not found in Device Tree\n");
		priv->usb_20_clk = शून्य;
	पूर्ण
	err = clk_prepare_enable(priv->usb_20_clk);
	अगर (err)
		वापस err;

	अगर (priv->has_eohci) अणु
		gphy = devm_phy_create(dev, शून्य, &brcm_usb_phy_ops);
		अगर (IS_ERR(gphy)) अणु
			dev_err(dev, "failed to create EHCI/OHCI PHY\n");
			वापस PTR_ERR(gphy);
		पूर्ण
		priv->phys[BRCM_USB_PHY_2_0].phy = gphy;
		priv->phys[BRCM_USB_PHY_2_0].id = BRCM_USB_PHY_2_0;
		phy_set_drvdata(gphy, &priv->phys[BRCM_USB_PHY_2_0]);
	पूर्ण

	अगर (priv->has_xhci) अणु
		gphy = devm_phy_create(dev, शून्य, &brcm_usb_phy_ops);
		अगर (IS_ERR(gphy)) अणु
			dev_err(dev, "failed to create XHCI PHY\n");
			वापस PTR_ERR(gphy);
		पूर्ण
		priv->phys[BRCM_USB_PHY_3_0].phy = gphy;
		priv->phys[BRCM_USB_PHY_3_0].id = BRCM_USB_PHY_3_0;
		phy_set_drvdata(gphy, &priv->phys[BRCM_USB_PHY_3_0]);

		priv->usb_30_clk = of_clk_get_by_name(dn, "sw_usb3");
		अगर (IS_ERR(priv->usb_30_clk)) अणु
			अगर (PTR_ERR(priv->usb_30_clk) == -EPROBE_DEFER)
				वापस -EPROBE_DEFER;
			dev_info(dev,
				 "USB3.0 clock not found in Device Tree\n");
			priv->usb_30_clk = शून्य;
		पूर्ण
		err = clk_prepare_enable(priv->usb_30_clk);
		अगर (err)
			वापस err;
	पूर्ण

	priv->suspend_clk = clk_get(dev, "usb0_freerun");
	अगर (IS_ERR(priv->suspend_clk)) अणु
		अगर (PTR_ERR(priv->suspend_clk) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_err(dev, "Suspend Clock not found in Device Tree\n");
		priv->suspend_clk = शून्य;
	पूर्ण

	priv->wake_irq = platक्रमm_get_irq_byname(pdev, "wake");
	अगर (priv->wake_irq < 0)
		priv->wake_irq = platक्रमm_get_irq_byname(pdev, "wakeup");
	अगर (priv->wake_irq >= 0) अणु
		err = devm_request_irq(dev, priv->wake_irq,
				       brcm_usb_phy_wake_isr, 0,
				       dev_name(dev), gphy);
		अगर (err < 0)
			वापस err;
		device_set_wakeup_capable(dev, 1);
	पूर्ण अन्यथा अणु
		dev_info(dev,
			 "Wake interrupt missing, system wake not supported\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक brcm_usb_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा brcm_usb_phy_data *priv;
	काष्ठा phy_provider *phy_provider;
	काष्ठा device_node *dn = pdev->dev.of_node;
	पूर्णांक err;
	स्थिर अक्षर *mode;
	स्थिर काष्ठा match_chip_info *info;
	काष्ठा regmap *rmap;
	पूर्णांक x;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, priv);

	priv->ini.family_id = brcmstb_get_family_id();
	priv->ini.product_id = brcmstb_get_product_id();

	info = of_device_get_match_data(&pdev->dev);
	अगर (!info)
		वापस -ENOENT;

	info->init_func(&priv->ini);

	dev_dbg(dev, "Best mapping table is for %s\n",
		priv->ini.family_name);

	of_property_पढ़ो_u32(dn, "brcm,ipp", &priv->ini.ipp);
	of_property_पढ़ो_u32(dn, "brcm,ioc", &priv->ini.ioc);

	priv->ini.mode = USB_CTLR_MODE_HOST;
	err = of_property_पढ़ो_string(dn, "dr_mode", &mode);
	अगर (err == 0) अणु
		name_to_value(&brcm_dr_mode_to_name[0],
			      ARRAY_SIZE(brcm_dr_mode_to_name),
			mode, &priv->ini.mode);
	पूर्ण
	अगर (of_property_पढ़ो_bool(dn, "brcm,has-xhci"))
		priv->has_xhci = true;
	अगर (of_property_पढ़ो_bool(dn, "brcm,has-eohci"))
		priv->has_eohci = true;

	क्रम (x = 0; x < BRCM_REGS_MAX; x++) अणु
		अगर (info->required_regs[x] >= BRCM_REGS_MAX)
			अवरोध;

		err = brcm_usb_get_regs(pdev, info->required_regs[x],
					&priv->ini, false);
		अगर (err)
			वापस -EINVAL;
	पूर्ण
	अगर (info->optional_reg) अणु
		err = brcm_usb_get_regs(pdev, info->optional_reg,
					&priv->ini, true);
		अगर (err)
			वापस -EINVAL;
	पूर्ण

	err = brcm_usb_phy_dvr_init(pdev, priv, dn);
	अगर (err)
		वापस err;

	mutex_init(&priv->mutex);

	/* make sure invert settings are correct */
	brcm_usb_init_ipp(&priv->ini);

	/*
	 * Create sysfs entries क्रम mode.
	 * Remove "dual_select" attribute अगर not in dual mode
	 */
	अगर (priv->ini.mode != USB_CTLR_MODE_DRD)
		brcm_usb_phy_attrs[1] = शून्य;
	err = sysfs_create_group(&dev->kobj, &brcm_usb_phy_group);
	अगर (err)
		dev_warn(dev, "Error creating sysfs attributes\n");

	/* Get piarbctl syscon अगर it exists */
	rmap = syscon_regmap_lookup_by_phandle(dev->of_node,
						 "syscon-piarbctl");
	अगर (IS_ERR(rmap))
		rmap = syscon_regmap_lookup_by_phandle(dev->of_node,
						       "brcm,syscon-piarbctl");
	अगर (!IS_ERR(rmap))
		priv->ini.syscon_piarbctl = rmap;

	/* start with everything off */
	अगर (priv->has_xhci)
		brcm_usb_uninit_xhci(&priv->ini);
	अगर (priv->has_eohci)
		brcm_usb_uninit_eohci(&priv->ini);
	brcm_usb_uninit_common(&priv->ini);
	clk_disable_unprepare(priv->usb_20_clk);
	clk_disable_unprepare(priv->usb_30_clk);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, brcm_usb_phy_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल पूर्णांक brcm_usb_phy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	sysfs_हटाओ_group(&pdev->dev.kobj, &brcm_usb_phy_group);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक brcm_usb_phy_suspend(काष्ठा device *dev)
अणु
	काष्ठा brcm_usb_phy_data *priv = dev_get_drvdata(dev);

	अगर (priv->init_count) अणु
		priv->ini.wake_enabled = device_may_wakeup(dev);
		अगर (priv->phys[BRCM_USB_PHY_3_0].inited)
			brcm_usb_uninit_xhci(&priv->ini);
		अगर (priv->phys[BRCM_USB_PHY_2_0].inited)
			brcm_usb_uninit_eohci(&priv->ini);
		brcm_usb_uninit_common(&priv->ini);

		/*
		 * Handle the घड़ीs unless needed क्रम wake. This has
		 * to work क्रम both older XHCI->3.0-clks, EOHCI->2.0-clks
		 * and newer XHCI->2.0-clks/3.0-clks.
		 */

		अगर (!priv->ini.suspend_with_घड़ीs) अणु
			अगर (priv->phys[BRCM_USB_PHY_3_0].inited)
				clk_disable_unprepare(priv->usb_30_clk);
			अगर (priv->phys[BRCM_USB_PHY_2_0].inited ||
			    !priv->has_eohci)
				clk_disable_unprepare(priv->usb_20_clk);
		पूर्ण
		अगर (priv->wake_irq >= 0)
			enable_irq_wake(priv->wake_irq);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक brcm_usb_phy_resume(काष्ठा device *dev)
अणु
	काष्ठा brcm_usb_phy_data *priv = dev_get_drvdata(dev);

	clk_prepare_enable(priv->usb_20_clk);
	clk_prepare_enable(priv->usb_30_clk);
	brcm_usb_init_ipp(&priv->ini);

	/*
	 * Initialize anything that was previously initialized.
	 * Uninitialize anything that wasn't previously initialized.
	 */
	अगर (priv->init_count) अणु
		अगर (priv->wake_irq >= 0)
			disable_irq_wake(priv->wake_irq);
		brcm_usb_init_common(&priv->ini);
		अगर (priv->phys[BRCM_USB_PHY_2_0].inited) अणु
			brcm_usb_init_eohci(&priv->ini);
		पूर्ण अन्यथा अगर (priv->has_eohci) अणु
			brcm_usb_uninit_eohci(&priv->ini);
			clk_disable_unprepare(priv->usb_20_clk);
		पूर्ण
		अगर (priv->phys[BRCM_USB_PHY_3_0].inited) अणु
			brcm_usb_init_xhci(&priv->ini);
		पूर्ण अन्यथा अगर (priv->has_xhci) अणु
			brcm_usb_uninit_xhci(&priv->ini);
			clk_disable_unprepare(priv->usb_30_clk);
			अगर (!priv->has_eohci)
				clk_disable_unprepare(priv->usb_20_clk);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (priv->has_xhci)
			brcm_usb_uninit_xhci(&priv->ini);
		अगर (priv->has_eohci)
			brcm_usb_uninit_eohci(&priv->ini);
		brcm_usb_uninit_common(&priv->ini);
		clk_disable_unprepare(priv->usb_20_clk);
		clk_disable_unprepare(priv->usb_30_clk);
	पूर्ण
	priv->ini.wake_enabled = false;
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops brcm_usb_phy_pm_ops = अणु
	SET_LATE_SYSTEM_SLEEP_PM_OPS(brcm_usb_phy_suspend, brcm_usb_phy_resume)
पूर्ण;

MODULE_DEVICE_TABLE(of, brcm_usb_dt_ids);

अटल काष्ठा platक्रमm_driver brcm_usb_driver = अणु
	.probe		= brcm_usb_phy_probe,
	.हटाओ		= brcm_usb_phy_हटाओ,
	.driver		= अणु
		.name	= "brcmstb-usb-phy",
		.pm = &brcm_usb_phy_pm_ops,
		.of_match_table = brcm_usb_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(brcm_usb_driver);

MODULE_ALIAS("platform:brcmstb-usb-phy");
MODULE_AUTHOR("Al Cooper <acooper@broadcom.com>");
MODULE_DESCRIPTION("BRCM USB PHY driver");
MODULE_LICENSE("GPL v2");
