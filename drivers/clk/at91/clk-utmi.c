<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2013 Boris BREZILLON <b.brezillon@overkiz.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk/at91_pmc.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <soc/at91/aपंचांगel-sfr.h>

#समावेश "pmc.h"

/*
 * The purpose of this घड़ी is to generate a 480 MHz संकेत. A dअगरferent
 * rate can't be configured.
 */
#घोषणा UTMI_RATE	480000000

काष्ठा clk_uपंचांगi अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap_pmc;
	काष्ठा regmap *regmap_sfr;
पूर्ण;

#घोषणा to_clk_uपंचांगi(hw) container_of(hw, काष्ठा clk_uपंचांगi, hw)

अटल अंतरभूत bool clk_uपंचांगi_पढ़ोy(काष्ठा regmap *regmap)
अणु
	अचिन्हित पूर्णांक status;

	regmap_पढ़ो(regmap, AT91_PMC_SR, &status);

	वापस status & AT91_PMC_LOCKU;
पूर्ण

अटल पूर्णांक clk_uपंचांगi_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw *hw_parent;
	काष्ठा clk_uपंचांगi *uपंचांगi = to_clk_uपंचांगi(hw);
	अचिन्हित पूर्णांक uckr = AT91_PMC_UPLLEN | AT91_PMC_UPLLCOUNT |
			    AT91_PMC_BIASEN;
	अचिन्हित पूर्णांक uपंचांगi_ref_clk_freq;
	अचिन्हित दीर्घ parent_rate;

	/*
	 * If मुख्यck rate is dअगरferent from 12 MHz, we have to configure the
	 * FREQ field of the SFR_UTMICKTRIM रेजिस्टर to generate properly
	 * the uपंचांगi घड़ी.
	 */
	hw_parent = clk_hw_get_parent(hw);
	parent_rate = clk_hw_get_rate(hw_parent);

	चयन (parent_rate) अणु
	हाल 12000000:
		uपंचांगi_ref_clk_freq = 0;
		अवरोध;
	हाल 16000000:
		uपंचांगi_ref_clk_freq = 1;
		अवरोध;
	हाल 24000000:
		uपंचांगi_ref_clk_freq = 2;
		अवरोध;
	/*
	 * Not supported on SAMA5D2 but it's not an issue since MAINCK
	 * maximum value is 24 MHz.
	 */
	हाल 48000000:
		uपंचांगi_ref_clk_freq = 3;
		अवरोध;
	शेष:
		pr_err("UTMICK: unsupported mainck rate\n");
		वापस -EINVAL;
	पूर्ण

	अगर (uपंचांगi->regmap_sfr) अणु
		regmap_update_bits(uपंचांगi->regmap_sfr, AT91_SFR_UTMICKTRIM,
				   AT91_UTMICKTRIM_FREQ, uपंचांगi_ref_clk_freq);
	पूर्ण अन्यथा अगर (uपंचांगi_ref_clk_freq) अणु
		pr_err("UTMICK: sfr node required\n");
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(uपंचांगi->regmap_pmc, AT91_CKGR_UCKR, uckr, uckr);

	जबतक (!clk_uपंचांगi_पढ़ोy(uपंचांगi->regmap_pmc))
		cpu_relax();

	वापस 0;
पूर्ण

अटल पूर्णांक clk_uपंचांगi_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_uपंचांगi *uपंचांगi = to_clk_uपंचांगi(hw);

	वापस clk_uपंचांगi_पढ़ोy(uपंचांगi->regmap_pmc);
पूर्ण

अटल व्योम clk_uपंचांगi_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_uपंचांगi *uपंचांगi = to_clk_uपंचांगi(hw);

	regmap_update_bits(uपंचांगi->regmap_pmc, AT91_CKGR_UCKR,
			   AT91_PMC_UPLLEN, 0);
पूर्ण

अटल अचिन्हित दीर्घ clk_uपंचांगi_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	/* UTMI clk rate is fixed. */
	वापस UTMI_RATE;
पूर्ण

अटल स्थिर काष्ठा clk_ops uपंचांगi_ops = अणु
	.prepare = clk_uपंचांगi_prepare,
	.unprepare = clk_uपंचांगi_unprepare,
	.is_prepared = clk_uपंचांगi_is_prepared,
	.recalc_rate = clk_uपंचांगi_recalc_rate,
पूर्ण;

अटल काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_uपंचांगi_पूर्णांकernal(काष्ठा regmap *regmap_pmc,
				काष्ठा regmap *regmap_sfr,
				स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
				स्थिर काष्ठा clk_ops *ops, अचिन्हित दीर्घ flags)
अणु
	काष्ठा clk_uपंचांगi *uपंचांगi;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	uपंचांगi = kzalloc(माप(*uपंचांगi), GFP_KERNEL);
	अगर (!uपंचांगi)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = ops;
	init.parent_names = parent_name ? &parent_name : शून्य;
	init.num_parents = parent_name ? 1 : 0;
	init.flags = flags;

	uपंचांगi->hw.init = &init;
	uपंचांगi->regmap_pmc = regmap_pmc;
	uपंचांगi->regmap_sfr = regmap_sfr;

	hw = &uपंचांगi->hw;
	ret = clk_hw_रेजिस्टर(शून्य, &uपंचांगi->hw);
	अगर (ret) अणु
		kमुक्त(uपंचांगi);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_uपंचांगi(काष्ठा regmap *regmap_pmc, काष्ठा regmap *regmap_sfr,
		       स्थिर अक्षर *name, स्थिर अक्षर *parent_name)
अणु
	वापस at91_clk_रेजिस्टर_uपंचांगi_पूर्णांकernal(regmap_pmc, regmap_sfr, name,
			parent_name, &uपंचांगi_ops, CLK_SET_RATE_GATE);
पूर्ण

अटल पूर्णांक clk_uपंचांगi_sama7g5_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_uपंचांगi *uपंचांगi = to_clk_uपंचांगi(hw);
	काष्ठा clk_hw *hw_parent;
	अचिन्हित दीर्घ parent_rate;
	अचिन्हित पूर्णांक val;

	hw_parent = clk_hw_get_parent(hw);
	parent_rate = clk_hw_get_rate(hw_parent);

	चयन (parent_rate) अणु
	हाल 16000000:
		val = 0;
		अवरोध;
	हाल 20000000:
		val = 2;
		अवरोध;
	हाल 24000000:
		val = 3;
		अवरोध;
	हाल 32000000:
		val = 5;
		अवरोध;
	शेष:
		pr_err("UTMICK: unsupported main_xtal rate\n");
		वापस -EINVAL;
	पूर्ण

	regmap_ग_लिखो(uपंचांगi->regmap_pmc, AT91_PMC_XTALF, val);

	वापस 0;

पूर्ण

अटल पूर्णांक clk_uपंचांगi_sama7g5_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_uपंचांगi *uपंचांगi = to_clk_uपंचांगi(hw);
	काष्ठा clk_hw *hw_parent;
	अचिन्हित दीर्घ parent_rate;
	अचिन्हित पूर्णांक val;

	hw_parent = clk_hw_get_parent(hw);
	parent_rate = clk_hw_get_rate(hw_parent);

	regmap_पढ़ो(uपंचांगi->regmap_pmc, AT91_PMC_XTALF, &val);
	चयन (val & 0x7) अणु
	हाल 0:
		अगर (parent_rate == 16000000)
			वापस 1;
		अवरोध;
	हाल 2:
		अगर (parent_rate == 20000000)
			वापस 1;
		अवरोध;
	हाल 3:
		अगर (parent_rate == 24000000)
			वापस 1;
		अवरोध;
	हाल 5:
		अगर (parent_rate == 32000000)
			वापस 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops sama7g5_uपंचांगi_ops = अणु
	.prepare = clk_uपंचांगi_sama7g5_prepare,
	.is_prepared = clk_uपंचांगi_sama7g5_is_prepared,
	.recalc_rate = clk_uपंचांगi_recalc_rate,
पूर्ण;

काष्ठा clk_hw * __init
at91_clk_sama7g5_रेजिस्टर_uपंचांगi(काष्ठा regmap *regmap_pmc, स्थिर अक्षर *name,
			       स्थिर अक्षर *parent_name)
अणु
	वापस at91_clk_रेजिस्टर_uपंचांगi_पूर्णांकernal(regmap_pmc, शून्य, name,
			parent_name, &sama7g5_uपंचांगi_ops, 0);
पूर्ण
