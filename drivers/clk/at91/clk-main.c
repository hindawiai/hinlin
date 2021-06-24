<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2013 Boris BREZILLON <b.brezillon@overkiz.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk/at91_pmc.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश "pmc.h"

#घोषणा SLOW_CLOCK_FREQ		32768
#घोषणा MAINF_DIV		16
#घोषणा MAINFRDY_TIMEOUT	(((MAINF_DIV + 1) * USEC_PER_SEC) / \
				 SLOW_CLOCK_FREQ)
#घोषणा MAINF_LOOP_MIN_WAIT	(USEC_PER_SEC / SLOW_CLOCK_FREQ)
#घोषणा MAINF_LOOP_MAX_WAIT	MAINFRDY_TIMEOUT

#घोषणा MOR_KEY_MASK		(0xff << 16)

#घोषणा clk_मुख्य_parent_select(s)	(((s) & \
					(AT91_PMC_MOSCEN | \
					AT91_PMC_OSCBYPASS)) ? 1 : 0)

काष्ठा clk_मुख्य_osc अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
पूर्ण;

#घोषणा to_clk_मुख्य_osc(hw) container_of(hw, काष्ठा clk_मुख्य_osc, hw)

काष्ठा clk_मुख्य_rc_osc अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	अचिन्हित दीर्घ frequency;
	अचिन्हित दीर्घ accuracy;
पूर्ण;

#घोषणा to_clk_मुख्य_rc_osc(hw) container_of(hw, काष्ठा clk_मुख्य_rc_osc, hw)

काष्ठा clk_rm9200_मुख्य अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
पूर्ण;

#घोषणा to_clk_rm9200_मुख्य(hw) container_of(hw, काष्ठा clk_rm9200_मुख्य, hw)

काष्ठा clk_sam9x5_मुख्य अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	u8 parent;
पूर्ण;

#घोषणा to_clk_sam9x5_मुख्य(hw) container_of(hw, काष्ठा clk_sam9x5_मुख्य, hw)

अटल अंतरभूत bool clk_मुख्य_osc_पढ़ोy(काष्ठा regmap *regmap)
अणु
	अचिन्हित पूर्णांक status;

	regmap_पढ़ो(regmap, AT91_PMC_SR, &status);

	वापस status & AT91_PMC_MOSCS;
पूर्ण

अटल पूर्णांक clk_मुख्य_osc_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_मुख्य_osc *osc = to_clk_मुख्य_osc(hw);
	काष्ठा regmap *regmap = osc->regmap;
	u32 पंचांगp;

	regmap_पढ़ो(regmap, AT91_CKGR_MOR, &पंचांगp);
	पंचांगp &= ~MOR_KEY_MASK;

	अगर (पंचांगp & AT91_PMC_OSCBYPASS)
		वापस 0;

	अगर (!(पंचांगp & AT91_PMC_MOSCEN)) अणु
		पंचांगp |= AT91_PMC_MOSCEN | AT91_PMC_KEY;
		regmap_ग_लिखो(regmap, AT91_CKGR_MOR, पंचांगp);
	पूर्ण

	जबतक (!clk_मुख्य_osc_पढ़ोy(regmap))
		cpu_relax();

	वापस 0;
पूर्ण

अटल व्योम clk_मुख्य_osc_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_मुख्य_osc *osc = to_clk_मुख्य_osc(hw);
	काष्ठा regmap *regmap = osc->regmap;
	u32 पंचांगp;

	regmap_पढ़ो(regmap, AT91_CKGR_MOR, &पंचांगp);
	अगर (पंचांगp & AT91_PMC_OSCBYPASS)
		वापस;

	अगर (!(पंचांगp & AT91_PMC_MOSCEN))
		वापस;

	पंचांगp &= ~(AT91_PMC_KEY | AT91_PMC_MOSCEN);
	regmap_ग_लिखो(regmap, AT91_CKGR_MOR, पंचांगp | AT91_PMC_KEY);
पूर्ण

अटल पूर्णांक clk_मुख्य_osc_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_मुख्य_osc *osc = to_clk_मुख्य_osc(hw);
	काष्ठा regmap *regmap = osc->regmap;
	u32 पंचांगp, status;

	regmap_पढ़ो(regmap, AT91_CKGR_MOR, &पंचांगp);
	अगर (पंचांगp & AT91_PMC_OSCBYPASS)
		वापस 1;

	regmap_पढ़ो(regmap, AT91_PMC_SR, &status);

	वापस (status & AT91_PMC_MOSCS) && clk_मुख्य_parent_select(पंचांगp);
पूर्ण

अटल स्थिर काष्ठा clk_ops मुख्य_osc_ops = अणु
	.prepare = clk_मुख्य_osc_prepare,
	.unprepare = clk_मुख्य_osc_unprepare,
	.is_prepared = clk_मुख्य_osc_is_prepared,
पूर्ण;

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_मुख्य_osc(काष्ठा regmap *regmap,
			   स्थिर अक्षर *name,
			   स्थिर अक्षर *parent_name,
			   bool bypass)
अणु
	काष्ठा clk_मुख्य_osc *osc;
	काष्ठा clk_init_data init;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	अगर (!name || !parent_name)
		वापस ERR_PTR(-EINVAL);

	osc = kzalloc(माप(*osc), GFP_KERNEL);
	अगर (!osc)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &मुख्य_osc_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = CLK_IGNORE_UNUSED;

	osc->hw.init = &init;
	osc->regmap = regmap;

	अगर (bypass)
		regmap_update_bits(regmap,
				   AT91_CKGR_MOR, MOR_KEY_MASK |
				   AT91_PMC_OSCBYPASS,
				   AT91_PMC_OSCBYPASS | AT91_PMC_KEY);

	hw = &osc->hw;
	ret = clk_hw_रेजिस्टर(शून्य, &osc->hw);
	अगर (ret) अणु
		kमुक्त(osc);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

अटल bool clk_मुख्य_rc_osc_पढ़ोy(काष्ठा regmap *regmap)
अणु
	अचिन्हित पूर्णांक status;

	regmap_पढ़ो(regmap, AT91_PMC_SR, &status);

	वापस !!(status & AT91_PMC_MOSCRCS);
पूर्ण

अटल पूर्णांक clk_मुख्य_rc_osc_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_मुख्य_rc_osc *osc = to_clk_मुख्य_rc_osc(hw);
	काष्ठा regmap *regmap = osc->regmap;
	अचिन्हित पूर्णांक mor;

	regmap_पढ़ो(regmap, AT91_CKGR_MOR, &mor);

	अगर (!(mor & AT91_PMC_MOSCRCEN))
		regmap_update_bits(regmap, AT91_CKGR_MOR,
				   MOR_KEY_MASK | AT91_PMC_MOSCRCEN,
				   AT91_PMC_MOSCRCEN | AT91_PMC_KEY);

	जबतक (!clk_मुख्य_rc_osc_पढ़ोy(regmap))
		cpu_relax();

	वापस 0;
पूर्ण

अटल व्योम clk_मुख्य_rc_osc_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_मुख्य_rc_osc *osc = to_clk_मुख्य_rc_osc(hw);
	काष्ठा regmap *regmap = osc->regmap;
	अचिन्हित पूर्णांक mor;

	regmap_पढ़ो(regmap, AT91_CKGR_MOR, &mor);

	अगर (!(mor & AT91_PMC_MOSCRCEN))
		वापस;

	regmap_update_bits(regmap, AT91_CKGR_MOR,
			   MOR_KEY_MASK | AT91_PMC_MOSCRCEN, AT91_PMC_KEY);
पूर्ण

अटल पूर्णांक clk_मुख्य_rc_osc_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_मुख्य_rc_osc *osc = to_clk_मुख्य_rc_osc(hw);
	काष्ठा regmap *regmap = osc->regmap;
	अचिन्हित पूर्णांक mor, status;

	regmap_पढ़ो(regmap, AT91_CKGR_MOR, &mor);
	regmap_पढ़ो(regmap, AT91_PMC_SR, &status);

	वापस (mor & AT91_PMC_MOSCRCEN) && (status & AT91_PMC_MOSCRCS);
पूर्ण

अटल अचिन्हित दीर्घ clk_मुख्य_rc_osc_recalc_rate(काष्ठा clk_hw *hw,
						 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_मुख्य_rc_osc *osc = to_clk_मुख्य_rc_osc(hw);

	वापस osc->frequency;
पूर्ण

अटल अचिन्हित दीर्घ clk_मुख्य_rc_osc_recalc_accuracy(काष्ठा clk_hw *hw,
						     अचिन्हित दीर्घ parent_acc)
अणु
	काष्ठा clk_मुख्य_rc_osc *osc = to_clk_मुख्य_rc_osc(hw);

	वापस osc->accuracy;
पूर्ण

अटल स्थिर काष्ठा clk_ops मुख्य_rc_osc_ops = अणु
	.prepare = clk_मुख्य_rc_osc_prepare,
	.unprepare = clk_मुख्य_rc_osc_unprepare,
	.is_prepared = clk_मुख्य_rc_osc_is_prepared,
	.recalc_rate = clk_मुख्य_rc_osc_recalc_rate,
	.recalc_accuracy = clk_मुख्य_rc_osc_recalc_accuracy,
पूर्ण;

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_मुख्य_rc_osc(काष्ठा regmap *regmap,
			      स्थिर अक्षर *name,
			      u32 frequency, u32 accuracy)
अणु
	काष्ठा clk_मुख्य_rc_osc *osc;
	काष्ठा clk_init_data init;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	अगर (!name || !frequency)
		वापस ERR_PTR(-EINVAL);

	osc = kzalloc(माप(*osc), GFP_KERNEL);
	अगर (!osc)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &मुख्य_rc_osc_ops;
	init.parent_names = शून्य;
	init.num_parents = 0;
	init.flags = CLK_IGNORE_UNUSED;

	osc->hw.init = &init;
	osc->regmap = regmap;
	osc->frequency = frequency;
	osc->accuracy = accuracy;

	hw = &osc->hw;
	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(osc);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

अटल पूर्णांक clk_मुख्य_probe_frequency(काष्ठा regmap *regmap)
अणु
	अचिन्हित दीर्घ prep_समय, समयout;
	अचिन्हित पूर्णांक mcfr;

	समयout = jअगरfies + usecs_to_jअगरfies(MAINFRDY_TIMEOUT);
	करो अणु
		prep_समय = jअगरfies;
		regmap_पढ़ो(regmap, AT91_CKGR_MCFR, &mcfr);
		अगर (mcfr & AT91_PMC_MAINRDY)
			वापस 0;
		अगर (प्रणाली_state < SYSTEM_RUNNING)
			udelay(MAINF_LOOP_MIN_WAIT);
		अन्यथा
			usleep_range(MAINF_LOOP_MIN_WAIT, MAINF_LOOP_MAX_WAIT);
	पूर्ण जबतक (समय_beक्रमe(prep_समय, समयout));

	वापस -ETIMEDOUT;
पूर्ण

अटल अचिन्हित दीर्घ clk_मुख्य_recalc_rate(काष्ठा regmap *regmap,
					  अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित पूर्णांक mcfr;

	अगर (parent_rate)
		वापस parent_rate;

	pr_warn("Main crystal frequency not set, using approximate value\n");
	regmap_पढ़ो(regmap, AT91_CKGR_MCFR, &mcfr);
	अगर (!(mcfr & AT91_PMC_MAINRDY))
		वापस 0;

	वापस ((mcfr & AT91_PMC_MAINF) * SLOW_CLOCK_FREQ) / MAINF_DIV;
पूर्ण

अटल पूर्णांक clk_rm9200_मुख्य_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_rm9200_मुख्य *clkमुख्य = to_clk_rm9200_मुख्य(hw);

	वापस clk_मुख्य_probe_frequency(clkमुख्य->regmap);
पूर्ण

अटल पूर्णांक clk_rm9200_मुख्य_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_rm9200_मुख्य *clkमुख्य = to_clk_rm9200_मुख्य(hw);
	अचिन्हित पूर्णांक status;

	regmap_पढ़ो(clkमुख्य->regmap, AT91_CKGR_MCFR, &status);

	वापस !!(status & AT91_PMC_MAINRDY);
पूर्ण

अटल अचिन्हित दीर्घ clk_rm9200_मुख्य_recalc_rate(काष्ठा clk_hw *hw,
						 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_rm9200_मुख्य *clkमुख्य = to_clk_rm9200_मुख्य(hw);

	वापस clk_मुख्य_recalc_rate(clkमुख्य->regmap, parent_rate);
पूर्ण

अटल स्थिर काष्ठा clk_ops rm9200_मुख्य_ops = अणु
	.prepare = clk_rm9200_मुख्य_prepare,
	.is_prepared = clk_rm9200_मुख्य_is_prepared,
	.recalc_rate = clk_rm9200_मुख्य_recalc_rate,
पूर्ण;

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_rm9200_मुख्य(काष्ठा regmap *regmap,
			      स्थिर अक्षर *name,
			      स्थिर अक्षर *parent_name)
अणु
	काष्ठा clk_rm9200_मुख्य *clkमुख्य;
	काष्ठा clk_init_data init;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	अगर (!name)
		वापस ERR_PTR(-EINVAL);

	अगर (!parent_name)
		वापस ERR_PTR(-EINVAL);

	clkमुख्य = kzalloc(माप(*clkमुख्य), GFP_KERNEL);
	अगर (!clkमुख्य)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &rm9200_मुख्य_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = 0;

	clkमुख्य->hw.init = &init;
	clkमुख्य->regmap = regmap;

	hw = &clkमुख्य->hw;
	ret = clk_hw_रेजिस्टर(शून्य, &clkमुख्य->hw);
	अगर (ret) अणु
		kमुक्त(clkमुख्य);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

अटल अंतरभूत bool clk_sam9x5_मुख्य_पढ़ोy(काष्ठा regmap *regmap)
अणु
	अचिन्हित पूर्णांक status;

	regmap_पढ़ो(regmap, AT91_PMC_SR, &status);

	वापस !!(status & AT91_PMC_MOSCSELS);
पूर्ण

अटल पूर्णांक clk_sam9x5_मुख्य_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_sam9x5_मुख्य *clkमुख्य = to_clk_sam9x5_मुख्य(hw);
	काष्ठा regmap *regmap = clkमुख्य->regmap;

	जबतक (!clk_sam9x5_मुख्य_पढ़ोy(regmap))
		cpu_relax();

	वापस clk_मुख्य_probe_frequency(regmap);
पूर्ण

अटल पूर्णांक clk_sam9x5_मुख्य_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_sam9x5_मुख्य *clkमुख्य = to_clk_sam9x5_मुख्य(hw);

	वापस clk_sam9x5_मुख्य_पढ़ोy(clkमुख्य->regmap);
पूर्ण

अटल अचिन्हित दीर्घ clk_sam9x5_मुख्य_recalc_rate(काष्ठा clk_hw *hw,
						 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_sam9x5_मुख्य *clkमुख्य = to_clk_sam9x5_मुख्य(hw);

	वापस clk_मुख्य_recalc_rate(clkमुख्य->regmap, parent_rate);
पूर्ण

अटल पूर्णांक clk_sam9x5_मुख्य_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_sam9x5_मुख्य *clkमुख्य = to_clk_sam9x5_मुख्य(hw);
	काष्ठा regmap *regmap = clkमुख्य->regmap;
	अचिन्हित पूर्णांक पंचांगp;

	अगर (index > 1)
		वापस -EINVAL;

	regmap_पढ़ो(regmap, AT91_CKGR_MOR, &पंचांगp);

	अगर (index && !(पंचांगp & AT91_PMC_MOSCSEL))
		पंचांगp = AT91_PMC_MOSCSEL;
	अन्यथा अगर (!index && (पंचांगp & AT91_PMC_MOSCSEL))
		पंचांगp = 0;
	अन्यथा
		वापस 0;

	regmap_update_bits(regmap, AT91_CKGR_MOR,
			   AT91_PMC_MOSCSEL | MOR_KEY_MASK,
			   पंचांगp | AT91_PMC_KEY);

	जबतक (!clk_sam9x5_मुख्य_पढ़ोy(regmap))
		cpu_relax();

	वापस 0;
पूर्ण

अटल u8 clk_sam9x5_मुख्य_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_sam9x5_मुख्य *clkमुख्य = to_clk_sam9x5_मुख्य(hw);
	अचिन्हित पूर्णांक status;

	regmap_पढ़ो(clkमुख्य->regmap, AT91_CKGR_MOR, &status);

	वापस clk_मुख्य_parent_select(status);
पूर्ण

अटल स्थिर काष्ठा clk_ops sam9x5_मुख्य_ops = अणु
	.prepare = clk_sam9x5_मुख्य_prepare,
	.is_prepared = clk_sam9x5_मुख्य_is_prepared,
	.recalc_rate = clk_sam9x5_मुख्य_recalc_rate,
	.set_parent = clk_sam9x5_मुख्य_set_parent,
	.get_parent = clk_sam9x5_मुख्य_get_parent,
पूर्ण;

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_sam9x5_मुख्य(काष्ठा regmap *regmap,
			      स्थिर अक्षर *name,
			      स्थिर अक्षर **parent_names,
			      पूर्णांक num_parents)
अणु
	काष्ठा clk_sam9x5_मुख्य *clkमुख्य;
	काष्ठा clk_init_data init;
	अचिन्हित पूर्णांक status;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	अगर (!name)
		वापस ERR_PTR(-EINVAL);

	अगर (!parent_names || !num_parents)
		वापस ERR_PTR(-EINVAL);

	clkमुख्य = kzalloc(माप(*clkमुख्य), GFP_KERNEL);
	अगर (!clkमुख्य)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &sam9x5_मुख्य_ops;
	init.parent_names = parent_names;
	init.num_parents = num_parents;
	init.flags = CLK_SET_PARENT_GATE;

	clkमुख्य->hw.init = &init;
	clkमुख्य->regmap = regmap;
	regmap_पढ़ो(clkमुख्य->regmap, AT91_CKGR_MOR, &status);
	clkमुख्य->parent = clk_मुख्य_parent_select(status);

	hw = &clkमुख्य->hw;
	ret = clk_hw_रेजिस्टर(शून्य, &clkमुख्य->hw);
	अगर (ret) अणु
		kमुक्त(clkमुख्य);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
