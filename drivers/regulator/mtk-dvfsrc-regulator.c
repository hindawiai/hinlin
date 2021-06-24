<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2020 MediaTek Inc.

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/soc/mediatek/mtk_dvfsrc.h>

#घोषणा DVFSRC_ID_VCORE		0
#घोषणा DVFSRC_ID_VSCP		1

#घोषणा MT_DVFSRC_REGULAR(match, _name,	_volt_table)	\
[DVFSRC_ID_##_name] = अणु					\
	.desc = अणु					\
		.name = match,				\
		.of_match = of_match_ptr(match),	\
		.ops = &dvfsrc_vcore_ops,		\
		.type = REGULATOR_VOLTAGE,		\
		.id = DVFSRC_ID_##_name,		\
		.owner = THIS_MODULE,			\
		.n_voltages = ARRAY_SIZE(_volt_table),	\
		.volt_table = _volt_table,		\
	पूर्ण,	\
पूर्ण

/*
 * DVFSRC regulators' inक्रमmation
 *
 * @desc: standard fields of regulator description.
 * @voltage_selector:  Selector used क्रम get_voltage_sel() and
 *			   set_voltage_sel() callbacks
 */

काष्ठा dvfsrc_regulator अणु
	काष्ठा regulator_desc	desc;
पूर्ण;

/*
 * MTK DVFSRC regulators' init data
 *
 * @size: num of regulators
 * @regulator_info: regulator info.
 */
काष्ठा dvfsrc_regulator_init_data अणु
	u32 size;
	काष्ठा dvfsrc_regulator *regulator_info;
पूर्ण;

अटल अंतरभूत काष्ठा device *to_dvfsrc_dev(काष्ठा regulator_dev *rdev)
अणु
	वापस rdev_get_dev(rdev)->parent;
पूर्ण

अटल पूर्णांक dvfsrc_set_voltage_sel(काष्ठा regulator_dev *rdev,
				  अचिन्हित पूर्णांक selector)
अणु
	काष्ठा device *dvfsrc_dev = to_dvfsrc_dev(rdev);
	पूर्णांक id = rdev_get_id(rdev);

	अगर (id == DVFSRC_ID_VCORE)
		mtk_dvfsrc_send_request(dvfsrc_dev,
					MTK_DVFSRC_CMD_VCORE_REQUEST,
					selector);
	अन्यथा अगर (id == DVFSRC_ID_VSCP)
		mtk_dvfsrc_send_request(dvfsrc_dev,
					MTK_DVFSRC_CMD_VSCP_REQUEST,
					selector);
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक dvfsrc_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा device *dvfsrc_dev = to_dvfsrc_dev(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	पूर्णांक val, ret;

	अगर (id == DVFSRC_ID_VCORE)
		ret = mtk_dvfsrc_query_info(dvfsrc_dev,
					    MTK_DVFSRC_CMD_VCORE_LEVEL_QUERY,
					    &val);
	अन्यथा अगर (id == DVFSRC_ID_VSCP)
		ret = mtk_dvfsrc_query_info(dvfsrc_dev,
					    MTK_DVFSRC_CMD_VSCP_LEVEL_QUERY,
					    &val);
	अन्यथा
		वापस -EINVAL;

	अगर (ret != 0)
		वापस ret;

	वापस val;
पूर्ण

अटल स्थिर काष्ठा regulator_ops dvfsrc_vcore_ops = अणु
	.list_voltage = regulator_list_voltage_table,
	.get_voltage_sel = dvfsrc_get_voltage_sel,
	.set_voltage_sel = dvfsrc_set_voltage_sel,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mt8183_voltages[] = अणु
	725000,
	800000,
पूर्ण;

अटल काष्ठा dvfsrc_regulator mt8183_regulators[] = अणु
	MT_DVFSRC_REGULAR("dvfsrc-vcore", VCORE,
			  mt8183_voltages),
पूर्ण;

अटल स्थिर काष्ठा dvfsrc_regulator_init_data regulator_mt8183_data = अणु
	.size = ARRAY_SIZE(mt8183_regulators),
	.regulator_info = &mt8183_regulators[0],
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mt6873_voltages[] = अणु
	575000,
	600000,
	650000,
	725000,
पूर्ण;

अटल काष्ठा dvfsrc_regulator mt6873_regulators[] = अणु
	MT_DVFSRC_REGULAR("dvfsrc-vcore", VCORE,
			  mt6873_voltages),
	MT_DVFSRC_REGULAR("dvfsrc-vscp", VSCP,
			  mt6873_voltages),
पूर्ण;

अटल स्थिर काष्ठा dvfsrc_regulator_init_data regulator_mt6873_data = अणु
	.size = ARRAY_SIZE(mt6873_regulators),
	.regulator_info = &mt6873_regulators[0],
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_dvfsrc_regulator_match[] = अणु
	अणु
		.compatible = "mediatek,mt8183-dvfsrc",
		.data = &regulator_mt8183_data,
	पूर्ण, अणु
		.compatible = "mediatek,mt8192-dvfsrc",
		.data = &regulator_mt6873_data,
	पूर्ण, अणु
		.compatible = "mediatek,mt6873-dvfsrc",
		.data = &regulator_mt6873_data,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_dvfsrc_regulator_match);

अटल पूर्णांक dvfsrc_vcore_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	स्थिर काष्ठा dvfsrc_regulator_init_data *regulator_init_data;
	काष्ठा dvfsrc_regulator *mt_regulators;
	पूर्णांक i;

	match = of_match_node(mtk_dvfsrc_regulator_match, dev->parent->of_node);

	अगर (!match) अणु
		dev_err(dev, "invalid compatible string\n");
		वापस -ENODEV;
	पूर्ण

	regulator_init_data = match->data;

	mt_regulators = regulator_init_data->regulator_info;
	क्रम (i = 0; i < regulator_init_data->size; i++) अणु
		config.dev = dev->parent;
		config.driver_data = (mt_regulators + i);
		rdev = devm_regulator_रेजिस्टर(dev->parent,
					       &(mt_regulators + i)->desc,
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(dev, "failed to register %s\n",
				(mt_regulators + i)->desc.name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mtk_dvfsrc_regulator_driver = अणु
	.driver = अणु
		.name  = "mtk-dvfsrc-regulator",
	पूर्ण,
	.probe = dvfsrc_vcore_regulator_probe,
पूर्ण;

अटल पूर्णांक __init mtk_dvfsrc_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mtk_dvfsrc_regulator_driver);
पूर्ण
subsys_initcall(mtk_dvfsrc_regulator_init);

अटल व्योम __निकास mtk_dvfsrc_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mtk_dvfsrc_regulator_driver);
पूर्ण
module_निकास(mtk_dvfsrc_regulator_निकास);

MODULE_AUTHOR("Arvin wang <arvin.wang@mediatek.com>");
MODULE_LICENSE("GPL v2");
