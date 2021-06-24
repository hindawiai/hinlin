<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Rafaध Miधecki <rafal@milecki.pl>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा PMU_XTAL_FREQ_RATIO			0x66c
#घोषणा  XTAL_ALP_PER_4ILP			0x00001fff
#घोषणा  XTAL_CTL_EN				0x80000000
#घोषणा PMU_SLOW_CLK_PERIOD			0x6dc

काष्ठा bcm53573_ilp अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
पूर्ण;

अटल पूर्णांक bcm53573_ilp_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा bcm53573_ilp *ilp = container_of(hw, काष्ठा bcm53573_ilp, hw);

	regmap_ग_लिखो(ilp->regmap, PMU_SLOW_CLK_PERIOD, 0x10199);
	regmap_ग_लिखो(ilp->regmap, 0x674, 0x10000);

	वापस 0;
पूर्ण

अटल व्योम bcm53573_ilp_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा bcm53573_ilp *ilp = container_of(hw, काष्ठा bcm53573_ilp, hw);

	regmap_ग_लिखो(ilp->regmap, PMU_SLOW_CLK_PERIOD, 0);
	regmap_ग_लिखो(ilp->regmap, 0x674, 0);
पूर्ण

अटल अचिन्हित दीर्घ bcm53573_ilp_recalc_rate(काष्ठा clk_hw *hw,
					      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा bcm53573_ilp *ilp = container_of(hw, काष्ठा bcm53573_ilp, hw);
	काष्ठा regmap *regmap = ilp->regmap;
	u32 last_val, cur_val;
	पूर्णांक sum = 0, num = 0, loop_num = 0;
	पूर्णांक avg;

	/* Enable measurement */
	regmap_ग_लिखो(regmap, PMU_XTAL_FREQ_RATIO, XTAL_CTL_EN);

	/* Read initial value */
	regmap_पढ़ो(regmap, PMU_XTAL_FREQ_RATIO, &last_val);
	last_val &= XTAL_ALP_PER_4ILP;

	/*
	 * At minimum we should loop क्रम a bit to let hardware करो the
	 * measurement. This isn't very accurate however, so क्रम a better
	 * precision lets try getting 20 dअगरferent values क्रम and use average.
	 */
	जबतक (num < 20) अणु
		regmap_पढ़ो(regmap, PMU_XTAL_FREQ_RATIO, &cur_val);
		cur_val &= XTAL_ALP_PER_4ILP;

		अगर (cur_val != last_val) अणु
			/* Got dअगरferent value, use it */
			sum += cur_val;
			num++;
			loop_num = 0;
			last_val = cur_val;
		पूर्ण अन्यथा अगर (++loop_num > 5000) अणु
			/* Same value over and over, give up */
			sum += cur_val;
			num++;
			अवरोध;
		पूर्ण

		cpu_relax();
	पूर्ण

	/* Disable measurement to save घातer */
	regmap_ग_लिखो(regmap, PMU_XTAL_FREQ_RATIO, 0x0);

	avg = sum / num;

	वापस parent_rate * 4 / avg;
पूर्ण

अटल स्थिर काष्ठा clk_ops bcm53573_ilp_clk_ops = अणु
	.enable = bcm53573_ilp_enable,
	.disable = bcm53573_ilp_disable,
	.recalc_rate = bcm53573_ilp_recalc_rate,
पूर्ण;

अटल व्योम bcm53573_ilp_init(काष्ठा device_node *np)
अणु
	काष्ठा bcm53573_ilp *ilp;
	काष्ठा clk_init_data init = अणु पूर्ण;
	स्थिर अक्षर *parent_name;
	पूर्णांक err;

	ilp = kzalloc(माप(*ilp), GFP_KERNEL);
	अगर (!ilp)
		वापस;

	parent_name = of_clk_get_parent_name(np, 0);
	अगर (!parent_name) अणु
		err = -ENOENT;
		जाओ err_मुक्त_ilp;
	पूर्ण

	ilp->regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(ilp->regmap)) अणु
		err = PTR_ERR(ilp->regmap);
		जाओ err_मुक्त_ilp;
	पूर्ण

	init.name = np->name;
	init.ops = &bcm53573_ilp_clk_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	ilp->hw.init = &init;
	err = clk_hw_रेजिस्टर(शून्य, &ilp->hw);
	अगर (err)
		जाओ err_मुक्त_ilp;

	err = of_clk_add_hw_provider(np, of_clk_hw_simple_get, &ilp->hw);
	अगर (err)
		जाओ err_clk_hw_unरेजिस्टर;

	वापस;

err_clk_hw_unरेजिस्टर:
	clk_hw_unरेजिस्टर(&ilp->hw);
err_मुक्त_ilp:
	kमुक्त(ilp);
	pr_err("Failed to init ILP clock: %d\n", err);
पूर्ण

/* We need it very early क्रम arch code, beक्रमe device model माला_लो पढ़ोy */
CLK_OF_DECLARE(bcm53573_ilp_clk, "brcm,bcm53573-ilp", bcm53573_ilp_init);
