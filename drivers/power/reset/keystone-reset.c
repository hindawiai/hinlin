<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI keystone reboot driver
 *
 * Copyright (C) 2014 Texas Instruments Incorporated. https://www.ti.com/
 *
 * Author: Ivan Khoronzhuk <ivan.khoronzhuk@ti.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_platक्रमm.h>

#घोषणा RSTYPE_RG			0x0
#घोषणा RSCTRL_RG			0x4
#घोषणा RSCFG_RG			0x8
#घोषणा RSISO_RG			0xc

#घोषणा RSCTRL_KEY_MASK			0x0000ffff
#घोषणा RSCTRL_RESET_MASK		BIT(16)
#घोषणा RSCTRL_KEY			0x5a69

#घोषणा RSMUX_OMODE_MASK		0xe
#घोषणा RSMUX_OMODE_RESET_ON		0xa
#घोषणा RSMUX_OMODE_RESET_OFF		0x0
#घोषणा RSMUX_LOCK_MASK			0x1
#घोषणा RSMUX_LOCK_SET			0x1

#घोषणा RSCFG_RSTYPE_SOFT		0x300f
#घोषणा RSCFG_RSTYPE_HARD		0x0

#घोषणा WDT_MUX_NUMBER			0x4

अटल पूर्णांक rspll_offset;
अटल काष्ठा regmap *pllctrl_regs;

/**
 * rsctrl_enable_rspll_ग_लिखो - enable access to RSCTRL, RSCFG
 * To be able to access to RSCTRL, RSCFG रेजिस्टरs
 * we have to ग_लिखो a key beक्रमe
 */
अटल अंतरभूत पूर्णांक rsctrl_enable_rspll_ग_लिखो(व्योम)
अणु
	वापस regmap_update_bits(pllctrl_regs, rspll_offset + RSCTRL_RG,
				  RSCTRL_KEY_MASK, RSCTRL_KEY);
पूर्ण

अटल पूर्णांक rsctrl_restart_handler(काष्ठा notअगरier_block *this,
				  अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	/* enable ग_लिखो access to RSTCTRL */
	rsctrl_enable_rspll_ग_लिखो();

	/* reset the SOC */
	regmap_update_bits(pllctrl_regs, rspll_offset + RSCTRL_RG,
			   RSCTRL_RESET_MASK, 0);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block rsctrl_restart_nb = अणु
	.notअगरier_call = rsctrl_restart_handler,
	.priority = 128,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rsctrl_of_match[] = अणु
	अणु.compatible = "ti,keystone-reset", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक rsctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	u32 val;
	अचिन्हित पूर्णांक rg;
	u32 rsmux_offset;
	काष्ठा regmap *devctrl_regs;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;

	अगर (!np)
		वापस -ENODEV;

	/* get regmaps */
	pllctrl_regs = syscon_regmap_lookup_by_phandle(np, "ti,syscon-pll");
	अगर (IS_ERR(pllctrl_regs))
		वापस PTR_ERR(pllctrl_regs);

	devctrl_regs = syscon_regmap_lookup_by_phandle(np, "ti,syscon-dev");
	अगर (IS_ERR(devctrl_regs))
		वापस PTR_ERR(devctrl_regs);

	ret = of_property_पढ़ो_u32_index(np, "ti,syscon-pll", 1, &rspll_offset);
	अगर (ret) अणु
		dev_err(dev, "couldn't read the reset pll offset!\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32_index(np, "ti,syscon-dev", 1, &rsmux_offset);
	अगर (ret) अणु
		dev_err(dev, "couldn't read the rsmux offset!\n");
		वापस -EINVAL;
	पूर्ण

	/* set soft/hard reset */
	val = of_property_पढ़ो_bool(np, "ti,soft-reset");
	val = val ? RSCFG_RSTYPE_SOFT : RSCFG_RSTYPE_HARD;

	ret = rsctrl_enable_rspll_ग_लिखो();
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(pllctrl_regs, rspll_offset + RSCFG_RG, val);
	अगर (ret)
		वापस ret;

	/* disable a reset isolation क्रम all module घड़ीs */
	ret = regmap_ग_लिखो(pllctrl_regs, rspll_offset + RSISO_RG, 0);
	अगर (ret)
		वापस ret;

	/* enable a reset क्रम watchकरोgs from wdt-list */
	क्रम (i = 0; i < WDT_MUX_NUMBER; i++) अणु
		ret = of_property_पढ़ो_u32_index(np, "ti,wdt-list", i, &val);
		अगर (ret == -EOVERFLOW && !i) अणु
			dev_err(dev, "ti,wdt-list property has to contain at"
				"least one entry\n");
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (ret) अणु
			अवरोध;
		पूर्ण

		अगर (val >= WDT_MUX_NUMBER) अणु
			dev_err(dev, "ti,wdt-list property can contain "
				"only numbers < 4\n");
			वापस -EINVAL;
		पूर्ण

		rg = rsmux_offset + val * 4;

		ret = regmap_update_bits(devctrl_regs, rg, RSMUX_OMODE_MASK,
					 RSMUX_OMODE_RESET_ON |
					 RSMUX_LOCK_SET);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = रेजिस्टर_restart_handler(&rsctrl_restart_nb);
	अगर (ret)
		dev_err(dev, "cannot register restart handler (err=%d)\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver rsctrl_driver = अणु
	.probe = rsctrl_probe,
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = rsctrl_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rsctrl_driver);

MODULE_AUTHOR("Ivan Khoronzhuk <ivan.khoronzhuk@ti.com>");
MODULE_DESCRIPTION("Texas Instruments keystone reset driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" KBUILD_MODNAME);
