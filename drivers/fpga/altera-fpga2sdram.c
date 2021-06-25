<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FPGA to SDRAM Bridge Driver क्रम Altera SoCFPGA Devices
 *
 *  Copyright (C) 2013-2016 Altera Corporation, All Rights Reserved.
 */

/*
 * This driver manages a bridge between an FPGA and the SDRAM used by the ARM
 * host processor प्रणाली (HPS).
 *
 * The bridge contains 4 पढ़ो ports, 4 ग_लिखो ports, and 6 command ports.
 * Reconfiguring these ports requires that no SDRAM transactions occur during
 * reconfiguration.  The code reconfiguring the ports cannot run out of SDRAM
 * nor can the FPGA access the SDRAM during reconfiguration.  This driver करोes
 * not support reconfiguring the ports.  The ports are configured by code
 * running out of on chip ram beक्रमe Linux is started and the configuration
 * is passed in a hanकरोff रेजिस्टर in the प्रणाली manager.
 *
 * This driver supports enabling and disabling of the configured ports, which
 * allows क्रम safe reprogramming of the FPGA, assuming that the new FPGA image
 * uses the same port configuration.  Bridges must be disabled beक्रमe
 * reprogramming the FPGA and re-enabled after the FPGA has been programmed.
 */

#समावेश <linux/fpga/fpga-bridge.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>

#घोषणा ALT_SDR_CTL_FPGAPORTRST_OFST		0x80
#घोषणा ALT_SDR_CTL_FPGAPORTRST_PORTRSTN_MSK	0x00003fff
#घोषणा ALT_SDR_CTL_FPGAPORTRST_RD_SHIFT	0
#घोषणा ALT_SDR_CTL_FPGAPORTRST_WR_SHIFT	4
#घोषणा ALT_SDR_CTL_FPGAPORTRST_CTRL_SHIFT	8

/*
 * From the Cyclone V HPS Memory Map करोcument:
 *   These रेजिस्टरs are used to store hanकरोff inक्रमmation between the
 *   preloader and the OS. These 8 रेजिस्टरs can be used to store any
 *   inक्रमmation. The contents of these रेजिस्टरs have no impact on
 *   the state of the HPS hardware.
 */
#घोषणा SYSMGR_ISWGRP_HANDOFF3          (0x8C)

#घोषणा F2S_BRIDGE_NAME "fpga2sdram"

काष्ठा alt_fpga2sdram_data अणु
	काष्ठा device *dev;
	काष्ठा regmap *sdrctl;
	पूर्णांक mask;
पूर्ण;

अटल पूर्णांक alt_fpga2sdram_enable_show(काष्ठा fpga_bridge *bridge)
अणु
	काष्ठा alt_fpga2sdram_data *priv = bridge->priv;
	पूर्णांक value;

	regmap_पढ़ो(priv->sdrctl, ALT_SDR_CTL_FPGAPORTRST_OFST, &value);

	वापस (value & priv->mask) == priv->mask;
पूर्ण

अटल अंतरभूत पूर्णांक _alt_fpga2sdram_enable_set(काष्ठा alt_fpga2sdram_data *priv,
					     bool enable)
अणु
	वापस regmap_update_bits(priv->sdrctl, ALT_SDR_CTL_FPGAPORTRST_OFST,
				  priv->mask, enable ? priv->mask : 0);
पूर्ण

अटल पूर्णांक alt_fpga2sdram_enable_set(काष्ठा fpga_bridge *bridge, bool enable)
अणु
	वापस _alt_fpga2sdram_enable_set(bridge->priv, enable);
पूर्ण

काष्ठा prop_map अणु
	अक्षर *prop_name;
	u32 *prop_value;
	u32 prop_max;
पूर्ण;

अटल स्थिर काष्ठा fpga_bridge_ops altera_fpga2sdram_br_ops = अणु
	.enable_set = alt_fpga2sdram_enable_set,
	.enable_show = alt_fpga2sdram_enable_show,
पूर्ण;

अटल स्थिर काष्ठा of_device_id altera_fpga_of_match[] = अणु
	अणु .compatible = "altr,socfpga-fpga2sdram-bridge" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक alt_fpga_bridge_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा alt_fpga2sdram_data *priv;
	काष्ठा fpga_bridge *br;
	u32 enable;
	काष्ठा regmap *sysmgr;
	पूर्णांक ret = 0;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;

	priv->sdrctl = syscon_regmap_lookup_by_compatible("altr,sdr-ctl");
	अगर (IS_ERR(priv->sdrctl)) अणु
		dev_err(dev, "regmap for altr,sdr-ctl lookup failed.\n");
		वापस PTR_ERR(priv->sdrctl);
	पूर्ण

	sysmgr = syscon_regmap_lookup_by_compatible("altr,sys-mgr");
	अगर (IS_ERR(sysmgr)) अणु
		dev_err(dev, "regmap for altr,sys-mgr lookup failed.\n");
		वापस PTR_ERR(sysmgr);
	पूर्ण

	/* Get f2s bridge configuration saved in hanकरोff रेजिस्टर */
	regmap_पढ़ो(sysmgr, SYSMGR_ISWGRP_HANDOFF3, &priv->mask);

	br = devm_fpga_bridge_create(dev, F2S_BRIDGE_NAME,
				     &altera_fpga2sdram_br_ops, priv);
	अगर (!br)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, br);

	ret = fpga_bridge_रेजिस्टर(br);
	अगर (ret)
		वापस ret;

	dev_info(dev, "driver initialized with handoff %08x\n", priv->mask);

	अगर (!of_property_पढ़ो_u32(dev->of_node, "bridge-enable", &enable)) अणु
		अगर (enable > 1) अणु
			dev_warn(dev, "invalid bridge-enable %u > 1\n", enable);
		पूर्ण अन्यथा अणु
			dev_info(dev, "%s bridge\n",
				 (enable ? "enabling" : "disabling"));
			ret = _alt_fpga2sdram_enable_set(priv, enable);
			अगर (ret) अणु
				fpga_bridge_unरेजिस्टर(br);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक alt_fpga_bridge_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fpga_bridge *br = platक्रमm_get_drvdata(pdev);

	fpga_bridge_unरेजिस्टर(br);

	वापस 0;
पूर्ण

MODULE_DEVICE_TABLE(of, altera_fpga_of_match);

अटल काष्ठा platक्रमm_driver altera_fpga_driver = अणु
	.probe = alt_fpga_bridge_probe,
	.हटाओ = alt_fpga_bridge_हटाओ,
	.driver = अणु
		.name	= "altera_fpga2sdram_bridge",
		.of_match_table = of_match_ptr(altera_fpga_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(altera_fpga_driver);

MODULE_DESCRIPTION("Altera SoCFPGA FPGA to SDRAM Bridge");
MODULE_AUTHOR("Alan Tull <atull@opensource.altera.com>");
MODULE_LICENSE("GPL v2");
