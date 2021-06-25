<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 MediaTek Inc.
 * Author: Hongzhou.Yang <hongzhou.yang@mediatek.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/mfd/mt6397/core.h>

#समावेश "pinctrl-mtk-common.h"
#समावेश "pinctrl-mtk-mt6397.h"

#घोषणा MT6397_PIN_REG_BASE  0xc000

अटल स्थिर काष्ठा mtk_pinctrl_devdata mt6397_pinctrl_data = अणु
	.pins = mtk_pins_mt6397,
	.npins = ARRAY_SIZE(mtk_pins_mt6397),
	.dir_offset = (MT6397_PIN_REG_BASE + 0x000),
	.ies_offset = MTK_PINCTRL_NOT_SUPPORT,
	.smt_offset = MTK_PINCTRL_NOT_SUPPORT,
	.pullen_offset = (MT6397_PIN_REG_BASE + 0x020),
	.pullsel_offset = (MT6397_PIN_REG_BASE + 0x040),
	.करोut_offset = (MT6397_PIN_REG_BASE + 0x080),
	.din_offset = (MT6397_PIN_REG_BASE + 0x0a0),
	.pinmux_offset = (MT6397_PIN_REG_BASE + 0x0c0),
	.type1_start = 41,
	.type1_end = 41,
	.port_shf = 3,
	.port_mask = 0x3,
	.port_align = 2,
पूर्ण;

अटल पूर्णांक mt6397_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mt6397_chip *mt6397;

	mt6397 = dev_get_drvdata(pdev->dev.parent);
	वापस mtk_pctrl_init(pdev, &mt6397_pinctrl_data, mt6397->regmap);
पूर्ण

अटल स्थिर काष्ठा of_device_id mt6397_pctrl_match[] = अणु
	अणु .compatible = "mediatek,mt6397-pinctrl", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver mtk_pinctrl_driver = अणु
	.probe = mt6397_pinctrl_probe,
	.driver = अणु
		.name = "mediatek-mt6397-pinctrl",
		.of_match_table = mt6397_pctrl_match,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(mtk_pinctrl_driver);
