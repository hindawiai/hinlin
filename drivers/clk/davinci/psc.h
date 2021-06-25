<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Clock driver क्रम TI Davinci PSC controllers
 *
 * Copyright (C) 2018 David Lechner <david@lechnology.com>
 */

#अगर_अघोषित __CLK_DAVINCI_PSC_H__
#घोषणा __CLK_DAVINCI_PSC_H__

#समावेश <linux/clk-provider.h>
#समावेश <linux/types.h>

/* PSC quirk flags */
#घोषणा LPSC_ALWAYS_ENABLED	BIT(0) /* never disable this घड़ी */
#घोषणा LPSC_SET_RATE_PARENT	BIT(1) /* propagate set_rate to parent घड़ी */
#घोषणा LPSC_FORCE		BIT(2) /* requires MDCTL FORCE bit */
#घोषणा LPSC_LOCAL_RESET	BIT(3) /* acts as reset provider */

काष्ठा davinci_lpsc_clkdev_info अणु
	स्थिर अक्षर *con_id;
	स्थिर अक्षर *dev_id;
पूर्ण;

#घोषणा LPSC_CLKDEV(c, d) अणु	\
	.con_id = (c),		\
	.dev_id = (d)		\
पूर्ण

#घोषणा LPSC_CLKDEV1(n, c, d) \
अटल स्थिर काष्ठा davinci_lpsc_clkdev_info n[] __initस्थिर = अणु	\
	LPSC_CLKDEV((c), (d)),						\
	अणु पूर्ण								\
पूर्ण

#घोषणा LPSC_CLKDEV2(n, c1, d1, c2, d2) \
अटल स्थिर काष्ठा davinci_lpsc_clkdev_info n[] __initस्थिर = अणु	\
	LPSC_CLKDEV((c1), (d1)),					\
	LPSC_CLKDEV((c2), (d2)),					\
	अणु पूर्ण								\
पूर्ण

#घोषणा LPSC_CLKDEV3(n, c1, d1, c2, d2, c3, d3) \
अटल स्थिर काष्ठा davinci_lpsc_clkdev_info n[] __initस्थिर = अणु	\
	LPSC_CLKDEV((c1), (d1)),					\
	LPSC_CLKDEV((c2), (d2)),					\
	LPSC_CLKDEV((c3), (d3)),					\
	अणु पूर्ण								\
पूर्ण

/**
 * davinci_lpsc_clk_info - LPSC module-specअगरic घड़ी inक्रमmation
 * @name: the घड़ी name
 * @parent: the parent घड़ी name
 * @cdevs: optional array of clkdev lookup table info
 * @md: the local module करोमुख्य (LPSC id)
 * @pd: the घातer करोमुख्य id
 * @flags: biपंचांगask of LPSC_* flags
 */
काष्ठा davinci_lpsc_clk_info अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent;
	स्थिर काष्ठा davinci_lpsc_clkdev_info *cdevs;
	u32 md;
	u32 pd;
	अचिन्हित दीर्घ flags;
पूर्ण;

#घोषणा LPSC(m, d, n, p, c, f)	\
अणु				\
	.name	= #n,		\
	.parent	= #p,		\
	.cdevs	= (c),		\
	.md	= (m),		\
	.pd	= (d),		\
	.flags	= (f),		\
पूर्ण

पूर्णांक davinci_psc_रेजिस्टर_घड़ीs(काष्ठा device *dev,
				स्थिर काष्ठा davinci_lpsc_clk_info *info,
				u8 num_clks,
				व्योम __iomem *base);

पूर्णांक of_davinci_psc_clk_init(काष्ठा device *dev,
			    स्थिर काष्ठा davinci_lpsc_clk_info *info,
			    u8 num_clks,
			    व्योम __iomem *base);

/* Device-specअगरic data */

काष्ठा davinci_psc_init_data अणु
	काष्ठा clk_bulk_data *parent_clks;
	पूर्णांक num_parent_clks;
	पूर्णांक (*psc_init)(काष्ठा device *dev, व्योम __iomem *base);
पूर्ण;

#अगर_घोषित CONFIG_ARCH_DAVINCI_DA830
बाह्य स्थिर काष्ठा davinci_psc_init_data da830_psc0_init_data;
बाह्य स्थिर काष्ठा davinci_psc_init_data da830_psc1_init_data;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DA850
बाह्य स्थिर काष्ठा davinci_psc_init_data da850_psc0_init_data;
बाह्य स्थिर काष्ठा davinci_psc_init_data da850_psc1_init_data;
बाह्य स्थिर काष्ठा davinci_psc_init_data of_da850_psc0_init_data;
बाह्य स्थिर काष्ठा davinci_psc_init_data of_da850_psc1_init_data;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DM355
बाह्य स्थिर काष्ठा davinci_psc_init_data dm355_psc_init_data;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DM365
बाह्य स्थिर काष्ठा davinci_psc_init_data dm365_psc_init_data;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DM644x
बाह्य स्थिर काष्ठा davinci_psc_init_data dm644x_psc_init_data;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DM646x
बाह्य स्थिर काष्ठा davinci_psc_init_data dm646x_psc_init_data;
#पूर्ण_अगर

#पूर्ण_अगर /* __CLK_DAVINCI_PSC_H__ */
