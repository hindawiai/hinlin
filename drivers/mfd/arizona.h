<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * wm5102.h  --  WM5102 MFD पूर्णांकernals
 *
 * Copyright 2012 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#अगर_अघोषित _WM5102_H
#घोषणा _WM5102_H

#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/pm.h>

बाह्य स्थिर काष्ठा regmap_config wm5102_i2c_regmap;
बाह्य स्थिर काष्ठा regmap_config wm5102_spi_regmap;

बाह्य स्थिर काष्ठा regmap_config wm5110_i2c_regmap;
बाह्य स्थिर काष्ठा regmap_config wm5110_spi_regmap;

बाह्य स्थिर काष्ठा regmap_config cs47l24_spi_regmap;

बाह्य स्थिर काष्ठा regmap_config wm8997_i2c_regmap;

बाह्य स्थिर काष्ठा regmap_config wm8998_i2c_regmap;

बाह्य स्थिर काष्ठा dev_pm_ops arizona_pm_ops;

बाह्य स्थिर काष्ठा of_device_id arizona_of_match[];

बाह्य स्थिर काष्ठा regmap_irq_chip wm5102_aod;
बाह्य स्थिर काष्ठा regmap_irq_chip wm5102_irq;

बाह्य स्थिर काष्ठा regmap_irq_chip wm5110_aod;
बाह्य स्थिर काष्ठा regmap_irq_chip wm5110_irq;
बाह्य स्थिर काष्ठा regmap_irq_chip wm5110_revd_irq;

बाह्य स्थिर काष्ठा regmap_irq_chip cs47l24_irq;

बाह्य स्थिर काष्ठा regmap_irq_chip wm8997_aod;
बाह्य स्थिर काष्ठा regmap_irq_chip wm8997_irq;

बाह्य काष्ठा regmap_irq_chip wm8998_aod;
बाह्य काष्ठा regmap_irq_chip wm8998_irq;

पूर्णांक arizona_dev_init(काष्ठा arizona *arizona);
पूर्णांक arizona_dev_निकास(काष्ठा arizona *arizona);
पूर्णांक arizona_irq_init(काष्ठा arizona *arizona);
पूर्णांक arizona_irq_निकास(काष्ठा arizona *arizona);

#पूर्ण_अगर
