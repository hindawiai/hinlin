<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 MediaTek, Inc.
 *
 * Author: Chen Zhong <chen.zhong@mediatek.com>
 */

#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/mt6323/रेजिस्टरs.h>
#समावेश <linux/mfd/mt6397/core.h>
#समावेश <linux/mfd/mt6397/रेजिस्टरs.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा MTK_PMIC_PWRKEY_RST_EN_MASK	0x1
#घोषणा MTK_PMIC_PWRKEY_RST_EN_SHIFT	6
#घोषणा MTK_PMIC_HOMEKEY_RST_EN_MASK	0x1
#घोषणा MTK_PMIC_HOMEKEY_RST_EN_SHIFT	5
#घोषणा MTK_PMIC_RST_DU_MASK		0x3
#घोषणा MTK_PMIC_RST_DU_SHIFT		8

#घोषणा MTK_PMIC_PWRKEY_RST		\
	(MTK_PMIC_PWRKEY_RST_EN_MASK << MTK_PMIC_PWRKEY_RST_EN_SHIFT)
#घोषणा MTK_PMIC_HOMEKEY_RST		\
	(MTK_PMIC_HOMEKEY_RST_EN_MASK << MTK_PMIC_HOMEKEY_RST_EN_SHIFT)

#घोषणा MTK_PMIC_PWRKEY_INDEX	0
#घोषणा MTK_PMIC_HOMEKEY_INDEX	1
#घोषणा MTK_PMIC_MAX_KEY_COUNT	2

काष्ठा mtk_pmic_keys_regs अणु
	u32 deb_reg;
	u32 deb_mask;
	u32 पूर्णांकsel_reg;
	u32 पूर्णांकsel_mask;
पूर्ण;

#घोषणा MTK_PMIC_KEYS_REGS(_deb_reg, _deb_mask,		\
	_पूर्णांकsel_reg, _पूर्णांकsel_mask)			\
अणु							\
	.deb_reg		= _deb_reg,		\
	.deb_mask		= _deb_mask,		\
	.पूर्णांकsel_reg		= _पूर्णांकsel_reg,		\
	.पूर्णांकsel_mask		= _पूर्णांकsel_mask,		\
पूर्ण

काष्ठा mtk_pmic_regs अणु
	स्थिर काष्ठा mtk_pmic_keys_regs keys_regs[MTK_PMIC_MAX_KEY_COUNT];
	u32 pmic_rst_reg;
पूर्ण;

अटल स्थिर काष्ठा mtk_pmic_regs mt6397_regs = अणु
	.keys_regs[MTK_PMIC_PWRKEY_INDEX] =
		MTK_PMIC_KEYS_REGS(MT6397_CHRSTATUS,
		0x8, MT6397_INT_RSV, 0x10),
	.keys_regs[MTK_PMIC_HOMEKEY_INDEX] =
		MTK_PMIC_KEYS_REGS(MT6397_OCSTATUS2,
		0x10, MT6397_INT_RSV, 0x8),
	.pmic_rst_reg = MT6397_TOP_RST_MISC,
पूर्ण;

अटल स्थिर काष्ठा mtk_pmic_regs mt6323_regs = अणु
	.keys_regs[MTK_PMIC_PWRKEY_INDEX] =
		MTK_PMIC_KEYS_REGS(MT6323_CHRSTATUS,
		0x2, MT6323_INT_MISC_CON, 0x10),
	.keys_regs[MTK_PMIC_HOMEKEY_INDEX] =
		MTK_PMIC_KEYS_REGS(MT6323_CHRSTATUS,
		0x4, MT6323_INT_MISC_CON, 0x8),
	.pmic_rst_reg = MT6323_TOP_RST_MISC,
पूर्ण;

काष्ठा mtk_pmic_keys_info अणु
	काष्ठा mtk_pmic_keys *keys;
	स्थिर काष्ठा mtk_pmic_keys_regs *regs;
	अचिन्हित पूर्णांक keycode;
	पूर्णांक irq;
	bool wakeup:1;
पूर्ण;

काष्ठा mtk_pmic_keys अणु
	काष्ठा input_dev *input_dev;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा mtk_pmic_keys_info keys[MTK_PMIC_MAX_KEY_COUNT];
पूर्ण;

क्रमागत mtk_pmic_keys_lp_mode अणु
	LP_DISABLE,
	LP_ONEKEY,
	LP_TWOKEY,
पूर्ण;

अटल व्योम mtk_pmic_keys_lp_reset_setup(काष्ठा mtk_pmic_keys *keys,
		u32 pmic_rst_reg)
अणु
	पूर्णांक ret;
	u32 दीर्घ_press_mode, दीर्घ_press_debounce;

	ret = of_property_पढ़ो_u32(keys->dev->of_node,
		"power-off-time-sec", &दीर्घ_press_debounce);
	अगर (ret)
		दीर्घ_press_debounce = 0;

	regmap_update_bits(keys->regmap, pmic_rst_reg,
			   MTK_PMIC_RST_DU_MASK << MTK_PMIC_RST_DU_SHIFT,
			   दीर्घ_press_debounce << MTK_PMIC_RST_DU_SHIFT);

	ret = of_property_पढ़ो_u32(keys->dev->of_node,
		"mediatek,long-press-mode", &दीर्घ_press_mode);
	अगर (ret)
		दीर्घ_press_mode = LP_DISABLE;

	चयन (दीर्घ_press_mode) अणु
	हाल LP_ONEKEY:
		regmap_update_bits(keys->regmap, pmic_rst_reg,
				   MTK_PMIC_PWRKEY_RST,
				   MTK_PMIC_PWRKEY_RST);
		regmap_update_bits(keys->regmap, pmic_rst_reg,
				   MTK_PMIC_HOMEKEY_RST,
				   0);
		अवरोध;
	हाल LP_TWOKEY:
		regmap_update_bits(keys->regmap, pmic_rst_reg,
				   MTK_PMIC_PWRKEY_RST,
				   MTK_PMIC_PWRKEY_RST);
		regmap_update_bits(keys->regmap, pmic_rst_reg,
				   MTK_PMIC_HOMEKEY_RST,
				   MTK_PMIC_HOMEKEY_RST);
		अवरोध;
	हाल LP_DISABLE:
		regmap_update_bits(keys->regmap, pmic_rst_reg,
				   MTK_PMIC_PWRKEY_RST,
				   0);
		regmap_update_bits(keys->regmap, pmic_rst_reg,
				   MTK_PMIC_HOMEKEY_RST,
				   0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल irqवापस_t mtk_pmic_keys_irq_handler_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mtk_pmic_keys_info *info = data;
	u32 key_deb, pressed;

	regmap_पढ़ो(info->keys->regmap, info->regs->deb_reg, &key_deb);

	key_deb &= info->regs->deb_mask;

	pressed = !key_deb;

	input_report_key(info->keys->input_dev, info->keycode, pressed);
	input_sync(info->keys->input_dev);

	dev_dbg(info->keys->dev, "(%s) key =%d using PMIC\n",
		 pressed ? "pressed" : "released", info->keycode);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mtk_pmic_key_setup(काष्ठा mtk_pmic_keys *keys,
		काष्ठा mtk_pmic_keys_info *info)
अणु
	पूर्णांक ret;

	info->keys = keys;

	ret = regmap_update_bits(keys->regmap, info->regs->पूर्णांकsel_reg,
				 info->regs->पूर्णांकsel_mask,
				 info->regs->पूर्णांकsel_mask);
	अगर (ret < 0)
		वापस ret;

	ret = devm_request_thपढ़ोed_irq(keys->dev, info->irq, शून्य,
					mtk_pmic_keys_irq_handler_thपढ़ो,
					IRQF_ONESHOT | IRQF_TRIGGER_HIGH,
					"mtk-pmic-keys", info);
	अगर (ret) अणु
		dev_err(keys->dev, "Failed to request IRQ: %d: %d\n",
			info->irq, ret);
		वापस ret;
	पूर्ण

	input_set_capability(keys->input_dev, EV_KEY, info->keycode);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtk_pmic_keys_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_pmic_keys *keys = dev_get_drvdata(dev);
	पूर्णांक index;

	क्रम (index = 0; index < MTK_PMIC_MAX_KEY_COUNT; index++) अणु
		अगर (keys->keys[index].wakeup)
			enable_irq_wake(keys->keys[index].irq);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtk_pmic_keys_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_pmic_keys *keys = dev_get_drvdata(dev);
	पूर्णांक index;

	क्रम (index = 0; index < MTK_PMIC_MAX_KEY_COUNT; index++) अणु
		अगर (keys->keys[index].wakeup)
			disable_irq_wake(keys->keys[index].irq);
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mtk_pmic_keys_pm_ops, mtk_pmic_keys_suspend,
			mtk_pmic_keys_resume);

अटल स्थिर काष्ठा of_device_id of_mtk_pmic_keys_match_tbl[] = अणु
	अणु
		.compatible = "mediatek,mt6397-keys",
		.data = &mt6397_regs,
	पूर्ण, अणु
		.compatible = "mediatek,mt6323-keys",
		.data = &mt6323_regs,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_mtk_pmic_keys_match_tbl);

अटल पूर्णांक mtk_pmic_keys_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक error, index = 0;
	अचिन्हित पूर्णांक keycount;
	काष्ठा mt6397_chip *pmic_chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device_node *node = pdev->dev.of_node, *child;
	काष्ठा mtk_pmic_keys *keys;
	स्थिर काष्ठा mtk_pmic_regs *mtk_pmic_regs;
	काष्ठा input_dev *input_dev;
	स्थिर काष्ठा of_device_id *of_id =
		of_match_device(of_mtk_pmic_keys_match_tbl, &pdev->dev);

	keys = devm_kzalloc(&pdev->dev, माप(*keys), GFP_KERNEL);
	अगर (!keys)
		वापस -ENOMEM;

	keys->dev = &pdev->dev;
	keys->regmap = pmic_chip->regmap;
	mtk_pmic_regs = of_id->data;

	keys->input_dev = input_dev = devm_input_allocate_device(keys->dev);
	अगर (!input_dev) अणु
		dev_err(keys->dev, "input allocate device fail.\n");
		वापस -ENOMEM;
	पूर्ण

	input_dev->name = "mtk-pmic-keys";
	input_dev->id.bustype = BUS_HOST;
	input_dev->id.venकरोr = 0x0001;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0001;

	keycount = of_get_available_child_count(node);
	अगर (keycount > MTK_PMIC_MAX_KEY_COUNT) अणु
		dev_err(keys->dev, "too many keys defined (%d)\n", keycount);
		वापस -EINVAL;
	पूर्ण

	क्रम_each_child_of_node(node, child) अणु
		keys->keys[index].regs = &mtk_pmic_regs->keys_regs[index];

		keys->keys[index].irq = platक्रमm_get_irq(pdev, index);
		अगर (keys->keys[index].irq < 0) अणु
			of_node_put(child);
			वापस keys->keys[index].irq;
		पूर्ण

		error = of_property_पढ़ो_u32(child,
			"linux,keycodes", &keys->keys[index].keycode);
		अगर (error) अणु
			dev_err(keys->dev,
				"failed to read key:%d linux,keycode property: %d\n",
				index, error);
			of_node_put(child);
			वापस error;
		पूर्ण

		अगर (of_property_पढ़ो_bool(child, "wakeup-source"))
			keys->keys[index].wakeup = true;

		error = mtk_pmic_key_setup(keys, &keys->keys[index]);
		अगर (error) अणु
			of_node_put(child);
			वापस error;
		पूर्ण

		index++;
	पूर्ण

	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		dev_err(&pdev->dev,
			"register input device failed (%d)\n", error);
		वापस error;
	पूर्ण

	mtk_pmic_keys_lp_reset_setup(keys, mtk_pmic_regs->pmic_rst_reg);

	platक्रमm_set_drvdata(pdev, keys);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pmic_keys_pdrv = अणु
	.probe = mtk_pmic_keys_probe,
	.driver = अणु
		   .name = "mtk-pmic-keys",
		   .of_match_table = of_mtk_pmic_keys_match_tbl,
		   .pm = &mtk_pmic_keys_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(pmic_keys_pdrv);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Chen Zhong <chen.zhong@mediatek.com>");
MODULE_DESCRIPTION("MTK pmic-keys driver v0.1");
