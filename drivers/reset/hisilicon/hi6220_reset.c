<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hisilicon Hi6220 reset controller driver
 *
 * Copyright (c) 2016 Linaro Limited.
 * Copyright (c) 2015-2016 Hisilicon Limited.
 *
 * Author: Feng Chen <puck.chen@hisilicon.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/reset.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा PERIPH_ASSERT_OFFSET      0x300
#घोषणा PERIPH_DEASSERT_OFFSET    0x304
#घोषणा PERIPH_MAX_INDEX          0x509

#घोषणा SC_MEDIA_RSTEN            0x052C
#घोषणा SC_MEDIA_RSTDIS           0x0530
#घोषणा MEDIA_MAX_INDEX           8

#घोषणा to_reset_data(x) container_of(x, काष्ठा hi6220_reset_data, rc_dev)

क्रमागत hi6220_reset_ctrl_type अणु
	PERIPHERAL,
	MEDIA,
	AO,
पूर्ण;

काष्ठा hi6220_reset_data अणु
	काष्ठा reset_controller_dev rc_dev;
	काष्ठा regmap *regmap;
पूर्ण;

अटल पूर्णांक hi6220_peripheral_निश्चित(काष्ठा reset_controller_dev *rc_dev,
				    अचिन्हित दीर्घ idx)
अणु
	काष्ठा hi6220_reset_data *data = to_reset_data(rc_dev);
	काष्ठा regmap *regmap = data->regmap;
	u32 bank = idx >> 8;
	u32 offset = idx & 0xff;
	u32 reg = PERIPH_ASSERT_OFFSET + bank * 0x10;

	वापस regmap_ग_लिखो(regmap, reg, BIT(offset));
पूर्ण

अटल पूर्णांक hi6220_peripheral_deनिश्चित(काष्ठा reset_controller_dev *rc_dev,
				      अचिन्हित दीर्घ idx)
अणु
	काष्ठा hi6220_reset_data *data = to_reset_data(rc_dev);
	काष्ठा regmap *regmap = data->regmap;
	u32 bank = idx >> 8;
	u32 offset = idx & 0xff;
	u32 reg = PERIPH_DEASSERT_OFFSET + bank * 0x10;

	वापस regmap_ग_लिखो(regmap, reg, BIT(offset));
पूर्ण

अटल स्थिर काष्ठा reset_control_ops hi6220_peripheral_reset_ops = अणु
	.निश्चित = hi6220_peripheral_निश्चित,
	.deनिश्चित = hi6220_peripheral_deनिश्चित,
पूर्ण;

अटल पूर्णांक hi6220_media_निश्चित(काष्ठा reset_controller_dev *rc_dev,
			       अचिन्हित दीर्घ idx)
अणु
	काष्ठा hi6220_reset_data *data = to_reset_data(rc_dev);
	काष्ठा regmap *regmap = data->regmap;

	वापस regmap_ग_लिखो(regmap, SC_MEDIA_RSTEN, BIT(idx));
पूर्ण

अटल पूर्णांक hi6220_media_deनिश्चित(काष्ठा reset_controller_dev *rc_dev,
				 अचिन्हित दीर्घ idx)
अणु
	काष्ठा hi6220_reset_data *data = to_reset_data(rc_dev);
	काष्ठा regmap *regmap = data->regmap;

	वापस regmap_ग_लिखो(regmap, SC_MEDIA_RSTDIS, BIT(idx));
पूर्ण

अटल स्थिर काष्ठा reset_control_ops hi6220_media_reset_ops = अणु
	.निश्चित = hi6220_media_निश्चित,
	.deनिश्चित = hi6220_media_deनिश्चित,
पूर्ण;

#घोषणा AO_SCTRL_SC_PW_CLKEN0     0x800
#घोषणा AO_SCTRL_SC_PW_CLKDIS0    0x804

#घोषणा AO_SCTRL_SC_PW_RSTEN0     0x810
#घोषणा AO_SCTRL_SC_PW_RSTDIS0    0x814

#घोषणा AO_SCTRL_SC_PW_ISOEN0     0x820
#घोषणा AO_SCTRL_SC_PW_ISODIS0    0x824
#घोषणा AO_MAX_INDEX              12

अटल पूर्णांक hi6220_ao_निश्चित(काष्ठा reset_controller_dev *rc_dev,
			       अचिन्हित दीर्घ idx)
अणु
	काष्ठा hi6220_reset_data *data = to_reset_data(rc_dev);
	काष्ठा regmap *regmap = data->regmap;
	पूर्णांक ret;

	ret = regmap_ग_लिखो(regmap, AO_SCTRL_SC_PW_RSTEN0, BIT(idx));
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(regmap, AO_SCTRL_SC_PW_ISOEN0, BIT(idx));
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(regmap, AO_SCTRL_SC_PW_CLKDIS0, BIT(idx));
	वापस ret;
पूर्ण

अटल पूर्णांक hi6220_ao_deनिश्चित(काष्ठा reset_controller_dev *rc_dev,
				 अचिन्हित दीर्घ idx)
अणु
	काष्ठा hi6220_reset_data *data = to_reset_data(rc_dev);
	काष्ठा regmap *regmap = data->regmap;
	पूर्णांक ret;

	/*
	 * It was suggested to disable isolation beक्रमe enabling
	 * the घड़ीs and deनिश्चितing reset, to aव्योम glitches.
	 * But this order is preserved to keep it matching the
	 * venकरोr code.
	 */
	ret = regmap_ग_लिखो(regmap, AO_SCTRL_SC_PW_RSTDIS0, BIT(idx));
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(regmap, AO_SCTRL_SC_PW_ISODIS0, BIT(idx));
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(regmap, AO_SCTRL_SC_PW_CLKEN0, BIT(idx));
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops hi6220_ao_reset_ops = अणु
	.निश्चित = hi6220_ao_निश्चित,
	.deनिश्चित = hi6220_ao_deनिश्चित,
पूर्ण;

अटल पूर्णांक hi6220_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	क्रमागत hi6220_reset_ctrl_type type;
	काष्ठा hi6220_reset_data *data;
	काष्ठा regmap *regmap;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	type = (क्रमागत hi6220_reset_ctrl_type)of_device_get_match_data(dev);

	regmap = syscon_node_to_regmap(np);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "failed to get reset controller regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	data->regmap = regmap;
	data->rc_dev.of_node = np;
	अगर (type == MEDIA) अणु
		data->rc_dev.ops = &hi6220_media_reset_ops;
		data->rc_dev.nr_resets = MEDIA_MAX_INDEX;
	पूर्ण अन्यथा अगर (type == PERIPHERAL) अणु
		data->rc_dev.ops = &hi6220_peripheral_reset_ops;
		data->rc_dev.nr_resets = PERIPH_MAX_INDEX;
	पूर्ण अन्यथा अणु
		data->rc_dev.ops = &hi6220_ao_reset_ops;
		data->rc_dev.nr_resets = AO_MAX_INDEX;
	पूर्ण

	वापस reset_controller_रेजिस्टर(&data->rc_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id hi6220_reset_match[] = अणु
	अणु
		.compatible = "hisilicon,hi6220-sysctrl",
		.data = (व्योम *)PERIPHERAL,
	पूर्ण,
	अणु
		.compatible = "hisilicon,hi6220-mediactrl",
		.data = (व्योम *)MEDIA,
	पूर्ण,
	अणु
		.compatible = "hisilicon,hi6220-aoctrl",
		.data = (व्योम *)AO,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hi6220_reset_match);

अटल काष्ठा platक्रमm_driver hi6220_reset_driver = अणु
	.probe = hi6220_reset_probe,
	.driver = अणु
		.name = "reset-hi6220",
		.of_match_table = hi6220_reset_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init hi6220_reset_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&hi6220_reset_driver);
पूर्ण

postcore_initcall(hi6220_reset_init);

MODULE_LICENSE("GPL v2");
