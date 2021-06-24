<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Clock driver क्रम TI Davinci PSC controllers
 *
 * Copyright (C) 2018 David Lechner <david@lechnology.com>
 */

#अगर_अघोषित __CLK_DAVINCI_PLL_H___
#घोषणा __CLK_DAVINCI_PLL_H___

#समावेश <linux/bitops.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>

#घोषणा PLL_HAS_CLKMODE			BIT(0) /* PLL has PLLCTL[CLKMODE] */
#घोषणा PLL_HAS_PREDIV			BIT(1) /* has preभाग beक्रमe PLL */
#घोषणा PLL_PREDIV_ALWAYS_ENABLED	BIT(2) /* करोn't clear DEN bit */
#घोषणा PLL_PREDIV_FIXED_DIV		BIT(3) /* fixed भागider value */
#घोषणा PLL_HAS_POSTDIV			BIT(4) /* has postभाग after PLL */
#घोषणा PLL_POSTDIV_ALWAYS_ENABLED	BIT(5) /* करोn't clear DEN bit */
#घोषणा PLL_POSTDIV_FIXED_DIV		BIT(6) /* fixed भागider value */
#घोषणा PLL_HAS_EXTCLKSRC		BIT(7) /* has selectable bypass */
#घोषणा PLL_PLLM_2X			BIT(8) /* PLLM value is 2x (DM365) */
#घोषणा PLL_PREDIV_FIXED8		BIT(9) /* DM355 quirk */

/** davinci_pll_clk_info - controller-specअगरic PLL info
 * @name: The name of the PLL
 * @unlock_reg: Option CFGCHIP रेजिस्टर क्रम unlocking PLL
 * @unlock_mask: Biपंचांगask used with @unlock_reg
 * @pllm_mask: Biपंचांगask क्रम PLLM[PLLM] value
 * @pllm_min: Minimum allowable value क्रम PLLM[PLLM]
 * @pllm_max: Maximum allowable value क्रम PLLM[PLLM]
 * @pllout_min_rate: Minimum allowable rate क्रम PLLOUT
 * @pllout_max_rate: Maximum allowable rate क्रम PLLOUT
 * @flags: Biपंचांगap of PLL_* flags.
 */
काष्ठा davinci_pll_clk_info अणु
	स्थिर अक्षर *name;
	u32 unlock_reg;
	u32 unlock_mask;
	u32 pllm_mask;
	u32 pllm_min;
	u32 pllm_max;
	अचिन्हित दीर्घ pllout_min_rate;
	अचिन्हित दीर्घ pllout_max_rate;
	u32 flags;
पूर्ण;

#घोषणा SYSCLK_ARM_RATE		BIT(0) /* Controls ARM rate */
#घोषणा SYSCLK_ALWAYS_ENABLED	BIT(1) /* Or bad things happen */
#घोषणा SYSCLK_FIXED_DIV	BIT(2) /* Fixed भागider */

/** davinci_pll_sysclk_info - SYSCLKn-specअगरic info
 * @name: The name of the घड़ी
 * @parent_name: The name of the parent घड़ी
 * @id: "n" in "SYSCLKn"
 * @ratio_width: Width (in bits) of RATIO in PLLDIVn रेजिस्टर
 * @flags: Biपंचांगap of SYSCLK_* flags.
 */
काष्ठा davinci_pll_sysclk_info अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	u32 id;
	u32 ratio_width;
	u32 flags;
पूर्ण;

#घोषणा SYSCLK(i, n, p, w, f)				\
अटल स्थिर काष्ठा davinci_pll_sysclk_info n = अणु	\
	.name		= #n,				\
	.parent_name	= #p,				\
	.id		= (i),				\
	.ratio_width	= (w),				\
	.flags		= (f),				\
पूर्ण

/** davinci_pll_obsclk_info - OBSCLK-specअगरic info
 * @name: The name of the घड़ी
 * @parent_names: Array of names of the parent घड़ीs
 * @num_parents: Length of @parent_names
 * @table: Array of values to ग_लिखो to OCSEL[OCSRC] cooresponding to
 *         @parent_names
 * @ocsrc_mask: Biपंचांगask क्रम OCSEL[OCSRC]
 */
काष्ठा davinci_pll_obsclk_info अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *parent_names;
	u8 num_parents;
	u32 *table;
	u32 ocsrc_mask;
पूर्ण;

काष्ठा clk *davinci_pll_clk_रेजिस्टर(काष्ठा device *dev,
				     स्थिर काष्ठा davinci_pll_clk_info *info,
				     स्थिर अक्षर *parent_name,
				     व्योम __iomem *base,
				     काष्ठा regmap *cfgchip);
काष्ठा clk *davinci_pll_auxclk_रेजिस्टर(काष्ठा device *dev,
					स्थिर अक्षर *name,
					व्योम __iomem *base);
काष्ठा clk *davinci_pll_sysclkbp_clk_रेजिस्टर(काष्ठा device *dev,
					      स्थिर अक्षर *name,
					      व्योम __iomem *base);
काष्ठा clk *
davinci_pll_obsclk_रेजिस्टर(काष्ठा device *dev,
			    स्थिर काष्ठा davinci_pll_obsclk_info *info,
			    व्योम __iomem *base);
काष्ठा clk *
davinci_pll_sysclk_रेजिस्टर(काष्ठा device *dev,
			    स्थिर काष्ठा davinci_pll_sysclk_info *info,
			    व्योम __iomem *base);

पूर्णांक of_davinci_pll_init(काष्ठा device *dev, काष्ठा device_node *node,
			स्थिर काष्ठा davinci_pll_clk_info *info,
			स्थिर काष्ठा davinci_pll_obsclk_info *obsclk_info,
			स्थिर काष्ठा davinci_pll_sysclk_info **भाग_info,
			u8 max_sysclk_id,
			व्योम __iomem *base,
			काष्ठा regmap *cfgchip);

/* Platक्रमm-specअगरic callbacks */

#अगर_घोषित CONFIG_ARCH_DAVINCI_DA850
पूर्णांक da850_pll1_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip);
व्योम of_da850_pll0_init(काष्ठा device_node *node);
पूर्णांक of_da850_pll1_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DM355
पूर्णांक dm355_pll2_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DM644x
पूर्णांक dm644x_pll2_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DM646x
पूर्णांक dm646x_pll2_init(काष्ठा device *dev, व्योम __iomem *base, काष्ठा regmap *cfgchip);
#पूर्ण_अगर

#पूर्ण_अगर /* __CLK_DAVINCI_PLL_H___ */
