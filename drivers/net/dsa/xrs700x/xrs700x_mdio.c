<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 NovaTech LLC
 * George McCollister <george.mccollister@gmail.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bits.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/module.h>
#समावेश <linux/phy.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/of.h>
#समावेश "xrs700x.h"
#समावेश "xrs700x_reg.h"

#घोषणा XRS_MDIO_IBA0	0x10
#घोषणा XRS_MDIO_IBA1	0x11
#घोषणा XRS_MDIO_IBD	0x14

#घोषणा XRS_IB_READ	0x0
#घोषणा XRS_IB_WRITE	0x1

अटल पूर्णांक xrs700x_mdio_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				 अचिन्हित पूर्णांक *val)
अणु
	काष्ठा mdio_device *mdiodev = context;
	काष्ठा device *dev = &mdiodev->dev;
	u16 uval;
	पूर्णांक ret;

	uval = (u16)FIELD_GET(GENMASK(31, 16), reg);

	ret = mdiobus_ग_लिखो(mdiodev->bus, mdiodev->addr, XRS_MDIO_IBA1, uval);
	अगर (ret < 0) अणु
		dev_err(dev, "xrs mdiobus_write returned %d\n", ret);
		वापस ret;
	पूर्ण

	uval = (u16)((reg & GENMASK(15, 1)) | XRS_IB_READ);

	ret = mdiobus_ग_लिखो(mdiodev->bus, mdiodev->addr, XRS_MDIO_IBA0, uval);
	अगर (ret < 0) अणु
		dev_err(dev, "xrs mdiobus_write returned %d\n", ret);
		वापस ret;
	पूर्ण

	ret = mdiobus_पढ़ो(mdiodev->bus, mdiodev->addr, XRS_MDIO_IBD);
	अगर (ret < 0) अणु
		dev_err(dev, "xrs mdiobus_read returned %d\n", ret);
		वापस ret;
	पूर्ण

	*val = (अचिन्हित पूर्णांक)ret;

	वापस 0;
पूर्ण

अटल पूर्णांक xrs700x_mdio_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक val)
अणु
	काष्ठा mdio_device *mdiodev = context;
	काष्ठा device *dev = &mdiodev->dev;
	u16 uval;
	पूर्णांक ret;

	ret = mdiobus_ग_लिखो(mdiodev->bus, mdiodev->addr, XRS_MDIO_IBD, (u16)val);
	अगर (ret < 0) अणु
		dev_err(dev, "xrs mdiobus_write returned %d\n", ret);
		वापस ret;
	पूर्ण

	uval = (u16)FIELD_GET(GENMASK(31, 16), reg);

	ret = mdiobus_ग_लिखो(mdiodev->bus, mdiodev->addr, XRS_MDIO_IBA1, uval);
	अगर (ret < 0) अणु
		dev_err(dev, "xrs mdiobus_write returned %d\n", ret);
		वापस ret;
	पूर्ण

	uval = (u16)((reg & GENMASK(15, 1)) | XRS_IB_WRITE);

	ret = mdiobus_ग_लिखो(mdiodev->bus, mdiodev->addr, XRS_MDIO_IBA0, uval);
	अगर (ret < 0) अणु
		dev_err(dev, "xrs mdiobus_write returned %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config xrs700x_mdio_regmap_config = अणु
	.val_bits = 16,
	.reg_stride = 2,
	.reg_bits = 32,
	.pad_bits = 0,
	.ग_लिखो_flag_mask = 0,
	.पढ़ो_flag_mask = 0,
	.reg_पढ़ो = xrs700x_mdio_reg_पढ़ो,
	.reg_ग_लिखो = xrs700x_mdio_reg_ग_लिखो,
	.max_रेजिस्टर = XRS_VLAN(VLAN_N_VID - 1),
	.cache_type = REGCACHE_NONE,
	.reg_क्रमmat_endian = REGMAP_ENDIAN_BIG,
	.val_क्रमmat_endian = REGMAP_ENDIAN_BIG
पूर्ण;

अटल पूर्णांक xrs700x_mdio_probe(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा xrs700x *priv;
	पूर्णांक ret;

	priv = xrs700x_चयन_alloc(&mdiodev->dev, mdiodev);
	अगर (!priv)
		वापस -ENOMEM;

	priv->regmap = devm_regmap_init(&mdiodev->dev, शून्य, mdiodev,
					&xrs700x_mdio_regmap_config);
	अगर (IS_ERR(priv->regmap)) अणु
		ret = PTR_ERR(priv->regmap);
		dev_err(&mdiodev->dev, "Failed to initialize regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	dev_set_drvdata(&mdiodev->dev, priv);

	ret = xrs700x_चयन_रेजिस्टर(priv);

	/* Main DSA driver may not be started yet. */
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम xrs700x_mdio_हटाओ(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा xrs700x *priv = dev_get_drvdata(&mdiodev->dev);

	xrs700x_चयन_हटाओ(priv);
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused xrs700x_mdio_dt_ids[] = अणु
	अणु .compatible = "arrow,xrs7003e", .data = &xrs7003e_info पूर्ण,
	अणु .compatible = "arrow,xrs7003f", .data = &xrs7003f_info पूर्ण,
	अणु .compatible = "arrow,xrs7004e", .data = &xrs7004e_info पूर्ण,
	अणु .compatible = "arrow,xrs7004f", .data = &xrs7004f_info पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xrs700x_mdio_dt_ids);

अटल काष्ठा mdio_driver xrs700x_mdio_driver = अणु
	.mdiodrv.driver = अणु
		.name	= "xrs700x-mdio",
		.of_match_table = of_match_ptr(xrs700x_mdio_dt_ids),
	पूर्ण,
	.probe	= xrs700x_mdio_probe,
	.हटाओ	= xrs700x_mdio_हटाओ,
पूर्ण;

mdio_module_driver(xrs700x_mdio_driver);

MODULE_AUTHOR("George McCollister <george.mccollister@gmail.com>");
MODULE_DESCRIPTION("Arrow SpeedChips XRS700x DSA MDIO driver");
MODULE_LICENSE("GPL v2");
