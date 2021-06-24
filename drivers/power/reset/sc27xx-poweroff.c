<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Spपढ़ोtrum Communications Inc.
 * Copyright (C) 2018 Linaro Ltd.
 */

#समावेश <linux/cpu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/syscore_ops.h>

#घोषणा SC27XX_PWR_PD_HW	0xc2c
#घोषणा SC27XX_PWR_OFF_EN	BIT(0)
#घोषणा SC27XX_SLP_CTRL		0xdf0
#घोषणा SC27XX_LDO_XTL_EN	BIT(3)

अटल काष्ठा regmap *regmap;

/*
 * On Spपढ़ोtrum platक्रमm, we need घातer off प्रणाली through बाह्यal SC27xx
 * series PMICs, and it is one similar SPI bus mapped by regmap to access PMIC,
 * which is not fast io access.
 *
 * So beक्रमe stopping other cores, we need release other cores' resource by
 * taking cpus करोwn to aव्योम racing regmap or spi mutex lock when घातeroff
 * प्रणाली through PMIC.
 */
अटल व्योम sc27xx_घातeroff_shutकरोwn(व्योम)
अणु
#अगर_घोषित CONFIG_HOTPLUG_CPU
	पूर्णांक cpu;

	क्रम_each_online_cpu(cpu) अणु
		अगर (cpu != smp_processor_id())
			हटाओ_cpu(cpu);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल काष्ठा syscore_ops घातeroff_syscore_ops = अणु
	.shutकरोwn = sc27xx_घातeroff_shutकरोwn,
पूर्ण;

अटल व्योम sc27xx_घातeroff_करो_घातeroff(व्योम)
अणु
	/* Disable the बाह्यal subsys connection's घातer firstly */
	regmap_ग_लिखो(regmap, SC27XX_SLP_CTRL, SC27XX_LDO_XTL_EN);

	regmap_ग_लिखो(regmap, SC27XX_PWR_PD_HW, SC27XX_PWR_OFF_EN);
पूर्ण

अटल पूर्णांक sc27xx_घातeroff_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (regmap)
		वापस -EINVAL;

	regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!regmap)
		वापस -ENODEV;

	pm_घातer_off = sc27xx_घातeroff_करो_घातeroff;
	रेजिस्टर_syscore_ops(&घातeroff_syscore_ops);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sc27xx_घातeroff_driver = अणु
	.probe = sc27xx_घातeroff_probe,
	.driver = अणु
		.name = "sc27xx-poweroff",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sc27xx_घातeroff_driver);

MODULE_DESCRIPTION("Power off driver for SC27XX PMIC Device");
MODULE_AUTHOR("Baolin Wang <baolin.wang@unisoc.com>");
MODULE_LICENSE("GPL v2");
