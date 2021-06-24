<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments CPSW Port's PHY Interface Mode selection Driver
 *
 * Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Based on cpsw-phy-sel.c driver created by Mugunthan V N <mugunthanvnm@ti.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_net.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regmap.h>

/* AM33xx SoC specअगरic definitions क्रम the CONTROL port */
#घोषणा AM33XX_GMII_SEL_MODE_MII	0
#घोषणा AM33XX_GMII_SEL_MODE_RMII	1
#घोषणा AM33XX_GMII_SEL_MODE_RGMII	2

क्रमागत अणु
	PHY_GMII_SEL_PORT_MODE = 0,
	PHY_GMII_SEL_RGMII_ID_MODE,
	PHY_GMII_SEL_RMII_IO_CLK_EN,
	PHY_GMII_SEL_LAST,
पूर्ण;

काष्ठा phy_gmii_sel_phy_priv अणु
	काष्ठा phy_gmii_sel_priv *priv;
	u32		id;
	काष्ठा phy	*अगर_phy;
	पूर्णांक		rmii_घड़ी_बाह्यal;
	पूर्णांक		phy_अगर_mode;
	काष्ठा regmap_field *fields[PHY_GMII_SEL_LAST];
पूर्ण;

काष्ठा phy_gmii_sel_soc_data अणु
	u32 num_ports;
	u32 features;
	स्थिर काष्ठा reg_field (*regfields)[PHY_GMII_SEL_LAST];
	bool use_of_data;
पूर्ण;

काष्ठा phy_gmii_sel_priv अणु
	काष्ठा device *dev;
	स्थिर काष्ठा phy_gmii_sel_soc_data *soc_data;
	काष्ठा regmap *regmap;
	काष्ठा phy_provider *phy_provider;
	काष्ठा phy_gmii_sel_phy_priv *अगर_phys;
	u32 num_ports;
	u32 reg_offset;
पूर्ण;

अटल पूर्णांक phy_gmii_sel_mode(काष्ठा phy *phy, क्रमागत phy_mode mode, पूर्णांक submode)
अणु
	काष्ठा phy_gmii_sel_phy_priv *अगर_phy = phy_get_drvdata(phy);
	स्थिर काष्ठा phy_gmii_sel_soc_data *soc_data = अगर_phy->priv->soc_data;
	काष्ठा device *dev = अगर_phy->priv->dev;
	काष्ठा regmap_field *regfield;
	पूर्णांक ret, rgmii_id = 0;
	u32 gmii_sel_mode = 0;

	अगर (mode != PHY_MODE_ETHERNET)
		वापस -EINVAL;

	चयन (submode) अणु
	हाल PHY_INTERFACE_MODE_RMII:
		gmii_sel_mode = AM33XX_GMII_SEL_MODE_RMII;
		अवरोध;

	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
		gmii_sel_mode = AM33XX_GMII_SEL_MODE_RGMII;
		अवरोध;

	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		gmii_sel_mode = AM33XX_GMII_SEL_MODE_RGMII;
		rgmii_id = 1;
		अवरोध;

	हाल PHY_INTERFACE_MODE_MII:
	हाल PHY_INTERFACE_MODE_GMII:
		gmii_sel_mode = AM33XX_GMII_SEL_MODE_MII;
		अवरोध;

	शेष:
		dev_warn(dev, "port%u: unsupported mode: \"%s\"\n",
			 अगर_phy->id, phy_modes(submode));
		वापस -EINVAL;
	पूर्ण

	अगर_phy->phy_अगर_mode = submode;

	dev_dbg(dev, "%s id:%u mode:%u rgmii_id:%d rmii_clk_ext:%d\n",
		__func__, अगर_phy->id, submode, rgmii_id,
		अगर_phy->rmii_घड़ी_बाह्यal);

	regfield = अगर_phy->fields[PHY_GMII_SEL_PORT_MODE];
	ret = regmap_field_ग_लिखो(regfield, gmii_sel_mode);
	अगर (ret) अणु
		dev_err(dev, "port%u: set mode fail %d", अगर_phy->id, ret);
		वापस ret;
	पूर्ण

	अगर (soc_data->features & BIT(PHY_GMII_SEL_RGMII_ID_MODE) &&
	    अगर_phy->fields[PHY_GMII_SEL_RGMII_ID_MODE]) अणु
		regfield = अगर_phy->fields[PHY_GMII_SEL_RGMII_ID_MODE];
		ret = regmap_field_ग_लिखो(regfield, rgmii_id);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (soc_data->features & BIT(PHY_GMII_SEL_RMII_IO_CLK_EN) &&
	    अगर_phy->fields[PHY_GMII_SEL_RMII_IO_CLK_EN]) अणु
		regfield = अगर_phy->fields[PHY_GMII_SEL_RMII_IO_CLK_EN];
		ret = regmap_field_ग_लिखो(regfield,
					 अगर_phy->rmii_घड़ी_बाह्यal);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर
काष्ठा reg_field phy_gmii_sel_fields_am33xx[][PHY_GMII_SEL_LAST] = अणु
	अणु
		[PHY_GMII_SEL_PORT_MODE] = REG_FIELD(0x650, 0, 1),
		[PHY_GMII_SEL_RGMII_ID_MODE] = REG_FIELD(0x650, 4, 4),
		[PHY_GMII_SEL_RMII_IO_CLK_EN] = REG_FIELD(0x650, 6, 6),
	पूर्ण,
	अणु
		[PHY_GMII_SEL_PORT_MODE] = REG_FIELD(0x650, 2, 3),
		[PHY_GMII_SEL_RGMII_ID_MODE] = REG_FIELD(0x650, 5, 5),
		[PHY_GMII_SEL_RMII_IO_CLK_EN] = REG_FIELD(0x650, 7, 7),
	पूर्ण,
पूर्ण;

अटल स्थिर
काष्ठा phy_gmii_sel_soc_data phy_gmii_sel_soc_am33xx = अणु
	.num_ports = 2,
	.features = BIT(PHY_GMII_SEL_RGMII_ID_MODE) |
		    BIT(PHY_GMII_SEL_RMII_IO_CLK_EN),
	.regfields = phy_gmii_sel_fields_am33xx,
पूर्ण;

अटल स्थिर
काष्ठा reg_field phy_gmii_sel_fields_dra7[][PHY_GMII_SEL_LAST] = अणु
	अणु
		[PHY_GMII_SEL_PORT_MODE] = REG_FIELD(0x554, 0, 1),
	पूर्ण,
	अणु
		[PHY_GMII_SEL_PORT_MODE] = REG_FIELD(0x554, 4, 5),
	पूर्ण,
पूर्ण;

अटल स्थिर
काष्ठा phy_gmii_sel_soc_data phy_gmii_sel_soc_dra7 = अणु
	.num_ports = 2,
	.regfields = phy_gmii_sel_fields_dra7,
पूर्ण;

अटल स्थिर
काष्ठा phy_gmii_sel_soc_data phy_gmii_sel_soc_dm814 = अणु
	.num_ports = 2,
	.features = BIT(PHY_GMII_SEL_RGMII_ID_MODE),
	.regfields = phy_gmii_sel_fields_am33xx,
पूर्ण;

अटल स्थिर
काष्ठा reg_field phy_gmii_sel_fields_am654[][PHY_GMII_SEL_LAST] = अणु
	अणु [PHY_GMII_SEL_PORT_MODE] = REG_FIELD(0x0, 0, 2), पूर्ण,
	अणु [PHY_GMII_SEL_PORT_MODE] = REG_FIELD(0x4, 0, 2), पूर्ण,
	अणु [PHY_GMII_SEL_PORT_MODE] = REG_FIELD(0x8, 0, 2), पूर्ण,
	अणु [PHY_GMII_SEL_PORT_MODE] = REG_FIELD(0xC, 0, 2), पूर्ण,
	अणु [PHY_GMII_SEL_PORT_MODE] = REG_FIELD(0x10, 0, 2), पूर्ण,
	अणु [PHY_GMII_SEL_PORT_MODE] = REG_FIELD(0x14, 0, 2), पूर्ण,
	अणु [PHY_GMII_SEL_PORT_MODE] = REG_FIELD(0x18, 0, 2), पूर्ण,
	अणु [PHY_GMII_SEL_PORT_MODE] = REG_FIELD(0x1C, 0, 2), पूर्ण,
पूर्ण;

अटल स्थिर
काष्ठा phy_gmii_sel_soc_data phy_gmii_sel_soc_am654 = अणु
	.use_of_data = true,
	.regfields = phy_gmii_sel_fields_am654,
पूर्ण;

अटल स्थिर काष्ठा of_device_id phy_gmii_sel_id_table[] = अणु
	अणु
		.compatible	= "ti,am3352-phy-gmii-sel",
		.data		= &phy_gmii_sel_soc_am33xx,
	पूर्ण,
	अणु
		.compatible	= "ti,dra7xx-phy-gmii-sel",
		.data		= &phy_gmii_sel_soc_dra7,
	पूर्ण,
	अणु
		.compatible	= "ti,am43xx-phy-gmii-sel",
		.data		= &phy_gmii_sel_soc_am33xx,
	पूर्ण,
	अणु
		.compatible	= "ti,dm814-phy-gmii-sel",
		.data		= &phy_gmii_sel_soc_dm814,
	पूर्ण,
	अणु
		.compatible	= "ti,am654-phy-gmii-sel",
		.data		= &phy_gmii_sel_soc_am654,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, phy_gmii_sel_id_table);

अटल स्थिर काष्ठा phy_ops phy_gmii_sel_ops = अणु
	.set_mode	= phy_gmii_sel_mode,
	.owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा phy *phy_gmii_sel_of_xlate(काष्ठा device *dev,
					 काष्ठा of_phandle_args *args)
अणु
	काष्ठा phy_gmii_sel_priv *priv = dev_get_drvdata(dev);
	पूर्णांक phy_id = args->args[0];

	अगर (args->args_count < 1)
		वापस ERR_PTR(-EINVAL);
	अगर (!priv || !priv->अगर_phys)
		वापस ERR_PTR(-ENODEV);
	अगर (priv->soc_data->features & BIT(PHY_GMII_SEL_RMII_IO_CLK_EN) &&
	    args->args_count < 2)
		वापस ERR_PTR(-EINVAL);
	अगर (phy_id > priv->num_ports)
		वापस ERR_PTR(-EINVAL);
	अगर (phy_id != priv->अगर_phys[phy_id - 1].id)
		वापस ERR_PTR(-EINVAL);

	phy_id--;
	अगर (priv->soc_data->features & BIT(PHY_GMII_SEL_RMII_IO_CLK_EN))
		priv->अगर_phys[phy_id].rmii_घड़ी_बाह्यal = args->args[1];
	dev_dbg(dev, "%s id:%u ext:%d\n", __func__,
		priv->अगर_phys[phy_id].id, args->args[1]);

	वापस priv->अगर_phys[phy_id].अगर_phy;
पूर्ण

अटल पूर्णांक phy_gmii_init_phy(काष्ठा phy_gmii_sel_priv *priv, पूर्णांक port,
			     काष्ठा phy_gmii_sel_phy_priv *अगर_phy)
अणु
	स्थिर काष्ठा phy_gmii_sel_soc_data *soc_data = priv->soc_data;
	काष्ठा device *dev = priv->dev;
	स्थिर काष्ठा reg_field *fields;
	काष्ठा regmap_field *regfield;
	काष्ठा reg_field field;
	पूर्णांक ret;

	अगर_phy->id = port;
	अगर_phy->priv = priv;

	fields = soc_data->regfields[port - 1];
	field = *fields++;
	field.reg += priv->reg_offset;
	dev_dbg(dev, "%s field %x %d %d\n", __func__,
		field.reg, field.msb, field.lsb);

	regfield = devm_regmap_field_alloc(dev, priv->regmap, field);
	अगर (IS_ERR(regfield))
		वापस PTR_ERR(regfield);
	अगर_phy->fields[PHY_GMII_SEL_PORT_MODE] = regfield;

	field = *fields++;
	field.reg += priv->reg_offset;
	अगर (soc_data->features & BIT(PHY_GMII_SEL_RGMII_ID_MODE)) अणु
		regfield = devm_regmap_field_alloc(dev,
						   priv->regmap,
						   field);
		अगर (IS_ERR(regfield))
			वापस PTR_ERR(regfield);
		अगर_phy->fields[PHY_GMII_SEL_RGMII_ID_MODE] = regfield;
		dev_dbg(dev, "%s field %x %d %d\n", __func__,
			field.reg, field.msb, field.lsb);
	पूर्ण

	field = *fields;
	field.reg += priv->reg_offset;
	अगर (soc_data->features & BIT(PHY_GMII_SEL_RMII_IO_CLK_EN)) अणु
		regfield = devm_regmap_field_alloc(dev,
						   priv->regmap,
						   field);
		अगर (IS_ERR(regfield))
			वापस PTR_ERR(regfield);
		अगर_phy->fields[PHY_GMII_SEL_RMII_IO_CLK_EN] = regfield;
		dev_dbg(dev, "%s field %x %d %d\n", __func__,
			field.reg, field.msb, field.lsb);
	पूर्ण

	अगर_phy->अगर_phy = devm_phy_create(dev,
					 priv->dev->of_node,
					 &phy_gmii_sel_ops);
	अगर (IS_ERR(अगर_phy->अगर_phy)) अणु
		ret = PTR_ERR(अगर_phy->अगर_phy);
		dev_err(dev, "Failed to create phy%d %d\n", port, ret);
		वापस ret;
	पूर्ण
	phy_set_drvdata(अगर_phy->अगर_phy, अगर_phy);

	वापस 0;
पूर्ण

अटल पूर्णांक phy_gmii_sel_init_ports(काष्ठा phy_gmii_sel_priv *priv)
अणु
	स्थिर काष्ठा phy_gmii_sel_soc_data *soc_data = priv->soc_data;
	काष्ठा phy_gmii_sel_phy_priv *अगर_phys;
	काष्ठा device *dev = priv->dev;
	पूर्णांक i, ret;

	अगर (soc_data->use_of_data) अणु
		स्थिर __be32 *offset;
		u64 size;

		offset = of_get_address(dev->of_node, 0, &size, शून्य);
		priv->num_ports = size / माप(u32);
		अगर (!priv->num_ports)
			वापस -EINVAL;
		priv->reg_offset = __be32_to_cpu(*offset);
	पूर्ण

	अगर_phys = devm_kसुस्मृति(dev, priv->num_ports,
			       माप(*अगर_phys), GFP_KERNEL);
	अगर (!अगर_phys)
		वापस -ENOMEM;
	dev_dbg(dev, "%s %d\n", __func__, priv->num_ports);

	क्रम (i = 0; i < priv->num_ports; i++) अणु
		ret = phy_gmii_init_phy(priv, i + 1, &अगर_phys[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	priv->अगर_phys = अगर_phys;
	वापस 0;
पूर्ण

अटल पूर्णांक phy_gmii_sel_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा phy_gmii_sel_priv *priv;
	पूर्णांक ret;

	of_id = of_match_node(phy_gmii_sel_id_table, pdev->dev.of_node);
	अगर (!of_id)
		वापस -EINVAL;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = &pdev->dev;
	priv->soc_data = of_id->data;
	priv->num_ports = priv->soc_data->num_ports;

	priv->regmap = syscon_node_to_regmap(node->parent);
	अगर (IS_ERR(priv->regmap)) अणु
		ret = PTR_ERR(priv->regmap);
		dev_err(dev, "Failed to get syscon %d\n", ret);
		वापस ret;
	पूर्ण

	ret = phy_gmii_sel_init_ports(priv);
	अगर (ret)
		वापस ret;

	dev_set_drvdata(&pdev->dev, priv);

	priv->phy_provider =
		devm_of_phy_provider_रेजिस्टर(dev,
					      phy_gmii_sel_of_xlate);
	अगर (IS_ERR(priv->phy_provider)) अणु
		ret = PTR_ERR(priv->phy_provider);
		dev_err(dev, "Failed to create phy provider %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver phy_gmii_sel_driver = अणु
	.probe		= phy_gmii_sel_probe,
	.driver		= अणु
		.name	= "phy-gmii-sel",
		.of_match_table = phy_gmii_sel_id_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(phy_gmii_sel_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Grygorii Strashko <grygorii.strashko@ti.com>");
MODULE_DESCRIPTION("TI CPSW Port's PHY Interface Mode selection Driver");
