<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Socionext Inc.
 *   Author: Masahiro Yamada <yamada.masahiro@socionext.com>
 */

#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset-controller.h>

काष्ठा uniphier_reset_data अणु
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक bit;
	अचिन्हित पूर्णांक flags;
#घोषणा UNIPHIER_RESET_ACTIVE_LOW		BIT(0)
पूर्ण;

#घोषणा UNIPHIER_RESET_ID_END		(अचिन्हित पूर्णांक)(-1)

#घोषणा UNIPHIER_RESET_END				\
	अणु .id = UNIPHIER_RESET_ID_END पूर्ण

#घोषणा UNIPHIER_RESET(_id, _reg, _bit)			\
	अणु						\
		.id = (_id),				\
		.reg = (_reg),				\
		.bit = (_bit),				\
	पूर्ण

#घोषणा UNIPHIER_RESETX(_id, _reg, _bit)		\
	अणु						\
		.id = (_id),				\
		.reg = (_reg),				\
		.bit = (_bit),				\
		.flags = UNIPHIER_RESET_ACTIVE_LOW,	\
	पूर्ण

/* System reset data */
अटल स्थिर काष्ठा uniphier_reset_data uniphier_ld4_sys_reset_data[] = अणु
	UNIPHIER_RESETX(2, 0x2000, 2),		/* न_अंकD */
	UNIPHIER_RESETX(8, 0x2000, 10),		/* STDMAC (Ether, HSC, MIO) */
	UNIPHIER_RESET_END,
पूर्ण;

अटल स्थिर काष्ठा uniphier_reset_data uniphier_pro4_sys_reset_data[] = अणु
	UNIPHIER_RESETX(2, 0x2000, 2),		/* न_अंकD */
	UNIPHIER_RESETX(6, 0x2000, 12),		/* Ether */
	UNIPHIER_RESETX(8, 0x2000, 10),		/* STDMAC (HSC, MIO, RLE) */
	UNIPHIER_RESETX(12, 0x2000, 6),		/* GIO (Ether, SATA, USB3) */
	UNIPHIER_RESETX(14, 0x2000, 17),	/* USB30 */
	UNIPHIER_RESETX(15, 0x2004, 17),	/* USB31 */
	UNIPHIER_RESETX(28, 0x2000, 18),	/* SATA0 */
	UNIPHIER_RESETX(29, 0x2004, 18),	/* SATA1 */
	UNIPHIER_RESETX(30, 0x2000, 19),	/* SATA-PHY */
	UNIPHIER_RESETX(40, 0x2000, 13),	/* AIO */
	UNIPHIER_RESET_END,
पूर्ण;

अटल स्थिर काष्ठा uniphier_reset_data uniphier_pro5_sys_reset_data[] = अणु
	UNIPHIER_RESETX(2, 0x2000, 2),		/* न_अंकD */
	UNIPHIER_RESETX(8, 0x2000, 10),		/* STDMAC (HSC) */
	UNIPHIER_RESETX(12, 0x2000, 6),		/* GIO (PCIe, USB3) */
	UNIPHIER_RESETX(14, 0x2000, 17),	/* USB30 */
	UNIPHIER_RESETX(15, 0x2004, 17),	/* USB31 */
	UNIPHIER_RESETX(24, 0x2008, 2),		/* PCIe */
	UNIPHIER_RESETX(40, 0x2000, 13),	/* AIO */
	UNIPHIER_RESET_END,
पूर्ण;

अटल स्थिर काष्ठा uniphier_reset_data uniphier_pxs2_sys_reset_data[] = अणु
	UNIPHIER_RESETX(2, 0x2000, 2),		/* न_अंकD */
	UNIPHIER_RESETX(6, 0x2000, 12),		/* Ether */
	UNIPHIER_RESETX(8, 0x2000, 10),		/* STDMAC (HSC, RLE) */
	UNIPHIER_RESETX(14, 0x2000, 17),	/* USB30 */
	UNIPHIER_RESETX(15, 0x2004, 17),	/* USB31 */
	UNIPHIER_RESETX(16, 0x2014, 4),		/* USB30-PHY0 */
	UNIPHIER_RESETX(17, 0x2014, 0),		/* USB30-PHY1 */
	UNIPHIER_RESETX(18, 0x2014, 2),		/* USB30-PHY2 */
	UNIPHIER_RESETX(20, 0x2014, 5),		/* USB31-PHY0 */
	UNIPHIER_RESETX(21, 0x2014, 1),		/* USB31-PHY1 */
	UNIPHIER_RESETX(28, 0x2014, 12),	/* SATA */
	UNIPHIER_RESET(30, 0x2014, 8),		/* SATA-PHY (active high) */
	UNIPHIER_RESETX(40, 0x2000, 13),	/* AIO */
	UNIPHIER_RESET_END,
पूर्ण;

अटल स्थिर काष्ठा uniphier_reset_data uniphier_ld11_sys_reset_data[] = अणु
	UNIPHIER_RESETX(2, 0x200c, 0),		/* न_अंकD */
	UNIPHIER_RESETX(4, 0x200c, 2),		/* eMMC */
	UNIPHIER_RESETX(6, 0x200c, 6),		/* Ether */
	UNIPHIER_RESETX(8, 0x200c, 8),		/* STDMAC (HSC, MIO) */
	UNIPHIER_RESETX(9, 0x200c, 9),		/* HSC */
	UNIPHIER_RESETX(40, 0x2008, 0),		/* AIO */
	UNIPHIER_RESETX(41, 0x2008, 1),		/* EVEA */
	UNIPHIER_RESETX(42, 0x2010, 2),		/* EXIV */
	UNIPHIER_RESET_END,
पूर्ण;

अटल स्थिर काष्ठा uniphier_reset_data uniphier_ld20_sys_reset_data[] = अणु
	UNIPHIER_RESETX(2, 0x200c, 0),		/* न_अंकD */
	UNIPHIER_RESETX(4, 0x200c, 2),		/* eMMC */
	UNIPHIER_RESETX(6, 0x200c, 6),		/* Ether */
	UNIPHIER_RESETX(8, 0x200c, 8),		/* STDMAC (HSC) */
	UNIPHIER_RESETX(9, 0x200c, 9),		/* HSC */
	UNIPHIER_RESETX(14, 0x200c, 5),		/* USB30 */
	UNIPHIER_RESETX(16, 0x200c, 12),	/* USB30-PHY0 */
	UNIPHIER_RESETX(17, 0x200c, 13),	/* USB30-PHY1 */
	UNIPHIER_RESETX(18, 0x200c, 14),	/* USB30-PHY2 */
	UNIPHIER_RESETX(19, 0x200c, 15),	/* USB30-PHY3 */
	UNIPHIER_RESETX(24, 0x200c, 4),		/* PCIe */
	UNIPHIER_RESETX(40, 0x2008, 0),		/* AIO */
	UNIPHIER_RESETX(41, 0x2008, 1),		/* EVEA */
	UNIPHIER_RESETX(42, 0x2010, 2),		/* EXIV */
	UNIPHIER_RESET_END,
पूर्ण;

अटल स्थिर काष्ठा uniphier_reset_data uniphier_pxs3_sys_reset_data[] = अणु
	UNIPHIER_RESETX(2, 0x200c, 0),		/* न_अंकD */
	UNIPHIER_RESETX(4, 0x200c, 2),		/* eMMC */
	UNIPHIER_RESETX(6, 0x200c, 9),		/* Ether0 */
	UNIPHIER_RESETX(7, 0x200c, 10),		/* Ether1 */
	UNIPHIER_RESETX(8, 0x200c, 12),		/* STDMAC */
	UNIPHIER_RESETX(12, 0x200c, 4),		/* USB30 link */
	UNIPHIER_RESETX(13, 0x200c, 5),		/* USB31 link */
	UNIPHIER_RESETX(16, 0x200c, 16),	/* USB30-PHY0 */
	UNIPHIER_RESETX(17, 0x200c, 18),	/* USB30-PHY1 */
	UNIPHIER_RESETX(18, 0x200c, 20),	/* USB30-PHY2 */
	UNIPHIER_RESETX(20, 0x200c, 17),	/* USB31-PHY0 */
	UNIPHIER_RESETX(21, 0x200c, 19),	/* USB31-PHY1 */
	UNIPHIER_RESETX(24, 0x200c, 3),		/* PCIe */
	UNIPHIER_RESETX(28, 0x200c, 7),		/* SATA0 */
	UNIPHIER_RESETX(29, 0x200c, 8),		/* SATA1 */
	UNIPHIER_RESETX(30, 0x200c, 21),	/* SATA-PHY */
	UNIPHIER_RESET_END,
पूर्ण;

/* Media I/O reset data */
#घोषणा UNIPHIER_MIO_RESET_SD(id, ch)			\
	UNIPHIER_RESETX((id), 0x110 + 0x200 * (ch), 0)

#घोषणा UNIPHIER_MIO_RESET_SD_BRIDGE(id, ch)		\
	UNIPHIER_RESETX((id), 0x110 + 0x200 * (ch), 26)

#घोषणा UNIPHIER_MIO_RESET_EMMC_HW_RESET(id, ch)	\
	UNIPHIER_RESETX((id), 0x80 + 0x200 * (ch), 0)

#घोषणा UNIPHIER_MIO_RESET_USB2(id, ch)			\
	UNIPHIER_RESETX((id), 0x114 + 0x200 * (ch), 0)

#घोषणा UNIPHIER_MIO_RESET_USB2_BRIDGE(id, ch)		\
	UNIPHIER_RESETX((id), 0x110 + 0x200 * (ch), 24)

#घोषणा UNIPHIER_MIO_RESET_DMAC(id)			\
	UNIPHIER_RESETX((id), 0x110, 17)

अटल स्थिर काष्ठा uniphier_reset_data uniphier_ld4_mio_reset_data[] = अणु
	UNIPHIER_MIO_RESET_SD(0, 0),
	UNIPHIER_MIO_RESET_SD(1, 1),
	UNIPHIER_MIO_RESET_SD(2, 2),
	UNIPHIER_MIO_RESET_SD_BRIDGE(3, 0),
	UNIPHIER_MIO_RESET_SD_BRIDGE(4, 1),
	UNIPHIER_MIO_RESET_SD_BRIDGE(5, 2),
	UNIPHIER_MIO_RESET_EMMC_HW_RESET(6, 1),
	UNIPHIER_MIO_RESET_DMAC(7),
	UNIPHIER_MIO_RESET_USB2(8, 0),
	UNIPHIER_MIO_RESET_USB2(9, 1),
	UNIPHIER_MIO_RESET_USB2(10, 2),
	UNIPHIER_MIO_RESET_USB2_BRIDGE(12, 0),
	UNIPHIER_MIO_RESET_USB2_BRIDGE(13, 1),
	UNIPHIER_MIO_RESET_USB2_BRIDGE(14, 2),
	UNIPHIER_RESET_END,
पूर्ण;

अटल स्थिर काष्ठा uniphier_reset_data uniphier_pro5_sd_reset_data[] = अणु
	UNIPHIER_MIO_RESET_SD(0, 0),
	UNIPHIER_MIO_RESET_SD(1, 1),
	UNIPHIER_MIO_RESET_EMMC_HW_RESET(6, 1),
	UNIPHIER_RESET_END,
पूर्ण;

/* Peripheral reset data */
#घोषणा UNIPHIER_PERI_RESET_UART(id, ch)		\
	UNIPHIER_RESETX((id), 0x114, 19 + (ch))

#घोषणा UNIPHIER_PERI_RESET_I2C(id, ch)			\
	UNIPHIER_RESETX((id), 0x114, 5 + (ch))

#घोषणा UNIPHIER_PERI_RESET_FI2C(id, ch)		\
	UNIPHIER_RESETX((id), 0x114, 24 + (ch))

#घोषणा UNIPHIER_PERI_RESET_SCSSI(id, ch)		\
	UNIPHIER_RESETX((id), 0x110, 17 + (ch))

#घोषणा UNIPHIER_PERI_RESET_MCSSI(id)			\
	UNIPHIER_RESETX((id), 0x114, 14)

अटल स्थिर काष्ठा uniphier_reset_data uniphier_ld4_peri_reset_data[] = अणु
	UNIPHIER_PERI_RESET_UART(0, 0),
	UNIPHIER_PERI_RESET_UART(1, 1),
	UNIPHIER_PERI_RESET_UART(2, 2),
	UNIPHIER_PERI_RESET_UART(3, 3),
	UNIPHIER_PERI_RESET_I2C(4, 0),
	UNIPHIER_PERI_RESET_I2C(5, 1),
	UNIPHIER_PERI_RESET_I2C(6, 2),
	UNIPHIER_PERI_RESET_I2C(7, 3),
	UNIPHIER_PERI_RESET_I2C(8, 4),
	UNIPHIER_PERI_RESET_SCSSI(11, 0),
	UNIPHIER_RESET_END,
पूर्ण;

अटल स्थिर काष्ठा uniphier_reset_data uniphier_pro4_peri_reset_data[] = अणु
	UNIPHIER_PERI_RESET_UART(0, 0),
	UNIPHIER_PERI_RESET_UART(1, 1),
	UNIPHIER_PERI_RESET_UART(2, 2),
	UNIPHIER_PERI_RESET_UART(3, 3),
	UNIPHIER_PERI_RESET_FI2C(4, 0),
	UNIPHIER_PERI_RESET_FI2C(5, 1),
	UNIPHIER_PERI_RESET_FI2C(6, 2),
	UNIPHIER_PERI_RESET_FI2C(7, 3),
	UNIPHIER_PERI_RESET_FI2C(8, 4),
	UNIPHIER_PERI_RESET_FI2C(9, 5),
	UNIPHIER_PERI_RESET_FI2C(10, 6),
	UNIPHIER_PERI_RESET_SCSSI(11, 0),
	UNIPHIER_PERI_RESET_SCSSI(12, 1),
	UNIPHIER_PERI_RESET_SCSSI(13, 2),
	UNIPHIER_PERI_RESET_SCSSI(14, 3),
	UNIPHIER_PERI_RESET_MCSSI(15),
	UNIPHIER_RESET_END,
पूर्ण;

/* Analog संकेत amplअगरiers reset data */
अटल स्थिर काष्ठा uniphier_reset_data uniphier_ld11_adamv_reset_data[] = अणु
	UNIPHIER_RESETX(0, 0x10, 6), /* EVEA */
	UNIPHIER_RESET_END,
पूर्ण;

/* core implementaton */
काष्ठा uniphier_reset_priv अणु
	काष्ठा reset_controller_dev rcdev;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	स्थिर काष्ठा uniphier_reset_data *data;
पूर्ण;

#घोषणा to_uniphier_reset_priv(_rcdev) \
			container_of(_rcdev, काष्ठा uniphier_reset_priv, rcdev)

अटल पूर्णांक uniphier_reset_update(काष्ठा reset_controller_dev *rcdev,
				 अचिन्हित दीर्घ id, पूर्णांक निश्चित)
अणु
	काष्ठा uniphier_reset_priv *priv = to_uniphier_reset_priv(rcdev);
	स्थिर काष्ठा uniphier_reset_data *p;

	क्रम (p = priv->data; p->id != UNIPHIER_RESET_ID_END; p++) अणु
		अचिन्हित पूर्णांक mask, val;

		अगर (p->id != id)
			जारी;

		mask = BIT(p->bit);

		अगर (निश्चित)
			val = mask;
		अन्यथा
			val = ~mask;

		अगर (p->flags & UNIPHIER_RESET_ACTIVE_LOW)
			val = ~val;

		वापस regmap_ग_लिखो_bits(priv->regmap, p->reg, mask, val);
	पूर्ण

	dev_err(priv->dev, "reset_id=%lu was not handled\n", id);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक uniphier_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
				 अचिन्हित दीर्घ id)
अणु
	वापस uniphier_reset_update(rcdev, id, 1);
पूर्ण

अटल पूर्णांक uniphier_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				   अचिन्हित दीर्घ id)
अणु
	वापस uniphier_reset_update(rcdev, id, 0);
पूर्ण

अटल पूर्णांक uniphier_reset_status(काष्ठा reset_controller_dev *rcdev,
				 अचिन्हित दीर्घ id)
अणु
	काष्ठा uniphier_reset_priv *priv = to_uniphier_reset_priv(rcdev);
	स्थिर काष्ठा uniphier_reset_data *p;

	क्रम (p = priv->data; p->id != UNIPHIER_RESET_ID_END; p++) अणु
		अचिन्हित पूर्णांक val;
		पूर्णांक ret, निश्चितed;

		अगर (p->id != id)
			जारी;

		ret = regmap_पढ़ो(priv->regmap, p->reg, &val);
		अगर (ret)
			वापस ret;

		निश्चितed = !!(val & BIT(p->bit));

		अगर (p->flags & UNIPHIER_RESET_ACTIVE_LOW)
			निश्चितed = !निश्चितed;

		वापस निश्चितed;
	पूर्ण

	dev_err(priv->dev, "reset_id=%lu was not found\n", id);
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops uniphier_reset_ops = अणु
	.निश्चित = uniphier_reset_निश्चित,
	.deनिश्चित = uniphier_reset_deनिश्चित,
	.status = uniphier_reset_status,
पूर्ण;

अटल पूर्णांक uniphier_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा uniphier_reset_priv *priv;
	स्थिर काष्ठा uniphier_reset_data *p, *data;
	काष्ठा regmap *regmap;
	काष्ठा device_node *parent;
	अचिन्हित पूर्णांक nr_resets = 0;

	data = of_device_get_match_data(dev);
	अगर (WARN_ON(!data))
		वापस -EINVAL;

	parent = of_get_parent(dev->of_node); /* parent should be syscon node */
	regmap = syscon_node_to_regmap(parent);
	of_node_put(parent);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "failed to get regmap (error %ld)\n",
			PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	क्रम (p = data; p->id != UNIPHIER_RESET_ID_END; p++)
		nr_resets = max(nr_resets, p->id + 1);

	priv->rcdev.ops = &uniphier_reset_ops;
	priv->rcdev.owner = dev->driver->owner;
	priv->rcdev.of_node = dev->of_node;
	priv->rcdev.nr_resets = nr_resets;
	priv->dev = dev;
	priv->regmap = regmap;
	priv->data = data;

	वापस devm_reset_controller_रेजिस्टर(&pdev->dev, &priv->rcdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id uniphier_reset_match[] = अणु
	/* System reset */
	अणु
		.compatible = "socionext,uniphier-ld4-reset",
		.data = uniphier_ld4_sys_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pro4-reset",
		.data = uniphier_pro4_sys_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-sld8-reset",
		.data = uniphier_ld4_sys_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pro5-reset",
		.data = uniphier_pro5_sys_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs2-reset",
		.data = uniphier_pxs2_sys_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld11-reset",
		.data = uniphier_ld11_sys_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld20-reset",
		.data = uniphier_ld20_sys_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs3-reset",
		.data = uniphier_pxs3_sys_reset_data,
	पूर्ण,
	/* Media I/O reset, SD reset */
	अणु
		.compatible = "socionext,uniphier-ld4-mio-reset",
		.data = uniphier_ld4_mio_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pro4-mio-reset",
		.data = uniphier_ld4_mio_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-sld8-mio-reset",
		.data = uniphier_ld4_mio_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pro5-sd-reset",
		.data = uniphier_pro5_sd_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs2-sd-reset",
		.data = uniphier_pro5_sd_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld11-mio-reset",
		.data = uniphier_ld4_mio_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld11-sd-reset",
		.data = uniphier_pro5_sd_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld20-sd-reset",
		.data = uniphier_pro5_sd_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs3-sd-reset",
		.data = uniphier_pro5_sd_reset_data,
	पूर्ण,
	/* Peripheral reset */
	अणु
		.compatible = "socionext,uniphier-ld4-peri-reset",
		.data = uniphier_ld4_peri_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pro4-peri-reset",
		.data = uniphier_pro4_peri_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-sld8-peri-reset",
		.data = uniphier_ld4_peri_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pro5-peri-reset",
		.data = uniphier_pro4_peri_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs2-peri-reset",
		.data = uniphier_pro4_peri_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld11-peri-reset",
		.data = uniphier_pro4_peri_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld20-peri-reset",
		.data = uniphier_pro4_peri_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs3-peri-reset",
		.data = uniphier_pro4_peri_reset_data,
	पूर्ण,
	/* Analog संकेत amplअगरiers reset */
	अणु
		.compatible = "socionext,uniphier-ld11-adamv-reset",
		.data = uniphier_ld11_adamv_reset_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld20-adamv-reset",
		.data = uniphier_ld11_adamv_reset_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, uniphier_reset_match);

अटल काष्ठा platक्रमm_driver uniphier_reset_driver = अणु
	.probe = uniphier_reset_probe,
	.driver = अणु
		.name = "uniphier-reset",
		.of_match_table = uniphier_reset_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(uniphier_reset_driver);

MODULE_AUTHOR("Masahiro Yamada <yamada.masahiro@socionext.com>");
MODULE_DESCRIPTION("UniPhier Reset Controller Driver");
MODULE_LICENSE("GPL");
