<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Clock drivers क्रम TI DaVinci PLL and PSC controllers
 *
 * Copyright (C) 2018 David Lechner <david@lechnology.com>
 */

#अगर_अघोषित __LINUX_CLK_DAVINCI_PLL_H___
#घोषणा __LINUX_CLK_DAVINCI_PLL_H___

#समावेश <linux/device.h>
#समावेश <linux/regmap.h>

/* function क्रम रेजिस्टरing घड़ीs in early boot */

#अगर_घोषित CONFIG_ARCH_DAVINCI_DA830
पूर्णांक da830_pll_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DA850
पूर्णांक da850_pll0_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DM355
पूर्णांक dm355_pll1_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip);
पूर्णांक dm355_psc_init(काष्ठा device *dev, व्योम __iomem *base);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DM365
पूर्णांक dm365_pll1_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip);
पूर्णांक dm365_pll2_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip);
पूर्णांक dm365_psc_init(काष्ठा device *dev, व्योम __iomem *base);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DM644x
पूर्णांक dm644x_pll1_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip);
पूर्णांक dm644x_psc_init(काष्ठा device *dev, व्योम __iomem *base);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DM646x
पूर्णांक dm646x_pll1_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip);
पूर्णांक dm646x_psc_init(काष्ठा device *dev, व्योम __iomem *base);
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_CLK_DAVINCI_PLL_H___ */
