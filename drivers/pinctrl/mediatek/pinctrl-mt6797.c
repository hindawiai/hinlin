<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Based on pinctrl-mt6765.c
 *
 * Copyright (C) 2018 MediaTek Inc.
 *
 * Author: ZH Chen <zh.chen@mediatek.com>
 *
 * Copyright (C) Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>
 *
 */

#समावेश "pinctrl-mtk-mt6797.h"
#समावेश "pinctrl-paris.h"

/*
 * MT6797 have multiple bases to program pin configuration listed as the below:
 * gpio:0x10005000, iocfg[l]:0x10002000, iocfg[b]:0x10002400,
 * iocfg[r]:0x10002800, iocfg[t]:0x10002C00.
 * _i_base could be used to indicate what base the pin should be mapped पूर्णांकo.
 */

अटल स्थिर काष्ठा mtk_pin_field_calc mt6797_pin_mode_range[] = अणु
	PIN_FIELD(0, 261, 0x300, 0x10, 0, 4),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt6797_pin_dir_range[] = अणु
	PIN_FIELD(0, 261, 0x0, 0x10, 0, 1),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt6797_pin_di_range[] = अणु
	PIN_FIELD(0, 261, 0x200, 0x10, 0, 1),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt6797_pin_करो_range[] = अणु
	PIN_FIELD(0, 261, 0x100, 0x10, 0, 1),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_reg_calc mt6797_reg_cals[PINCTRL_PIN_REG_MAX] = अणु
	[PINCTRL_PIN_REG_MODE] = MTK_RANGE(mt6797_pin_mode_range),
	[PINCTRL_PIN_REG_सूची] = MTK_RANGE(mt6797_pin_dir_range),
	[PINCTRL_PIN_REG_DI] = MTK_RANGE(mt6797_pin_di_range),
	[PINCTRL_PIN_REG_DO] = MTK_RANGE(mt6797_pin_करो_range),
पूर्ण;

अटल स्थिर अक्षर * स्थिर mt6797_pinctrl_रेजिस्टर_base_names[] = अणु
	"gpio", "iocfgl", "iocfgb", "iocfgr", "iocfgt",
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_soc mt6797_data = अणु
	.reg_cal = mt6797_reg_cals,
	.pins = mtk_pins_mt6797,
	.npins = ARRAY_SIZE(mtk_pins_mt6797),
	.ngrps = ARRAY_SIZE(mtk_pins_mt6797),
	.gpio_m = 0,
	.base_names = mt6797_pinctrl_रेजिस्टर_base_names,
	.nbase_names = ARRAY_SIZE(mt6797_pinctrl_रेजिस्टर_base_names),
पूर्ण;

अटल स्थिर काष्ठा of_device_id mt6797_pinctrl_of_match[] = अणु
	अणु .compatible = "mediatek,mt6797-pinctrl", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक mt6797_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस mtk_paris_pinctrl_probe(pdev, &mt6797_data);
पूर्ण

अटल काष्ठा platक्रमm_driver mt6797_pinctrl_driver = अणु
	.driver = अणु
		.name = "mt6797-pinctrl",
		.of_match_table = mt6797_pinctrl_of_match,
	पूर्ण,
	.probe = mt6797_pinctrl_probe,
पूर्ण;

अटल पूर्णांक __init mt6797_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mt6797_pinctrl_driver);
पूर्ण
arch_initcall(mt6797_pinctrl_init);
