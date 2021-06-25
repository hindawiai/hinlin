<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/clk/at91/sckc.c
 *
 *  Copyright (C) 2013 Boris BREZILLON <b.brezillon@overkiz.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/पन.स>

#घोषणा SLOW_CLOCK_FREQ		32768
#घोषणा SLOWCK_SW_CYCLES	5
#घोषणा SLOWCK_SW_TIME_USEC	((SLOWCK_SW_CYCLES * USEC_PER_SEC) / \
				 SLOW_CLOCK_FREQ)

#घोषणा	AT91_SCKC_CR			0x00

काष्ठा clk_slow_bits अणु
	u32 cr_rcen;
	u32 cr_osc32en;
	u32 cr_osc32byp;
	u32 cr_oscsel;
पूर्ण;

काष्ठा clk_slow_osc अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *sckcr;
	स्थिर काष्ठा clk_slow_bits *bits;
	अचिन्हित दीर्घ startup_usec;
पूर्ण;

#घोषणा to_clk_slow_osc(hw) container_of(hw, काष्ठा clk_slow_osc, hw)

काष्ठा clk_sama5d4_slow_osc अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *sckcr;
	स्थिर काष्ठा clk_slow_bits *bits;
	अचिन्हित दीर्घ startup_usec;
	bool prepared;
पूर्ण;

#घोषणा to_clk_sama5d4_slow_osc(hw) container_of(hw, काष्ठा clk_sama5d4_slow_osc, hw)

काष्ठा clk_slow_rc_osc अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *sckcr;
	स्थिर काष्ठा clk_slow_bits *bits;
	अचिन्हित दीर्घ frequency;
	अचिन्हित दीर्घ accuracy;
	अचिन्हित दीर्घ startup_usec;
पूर्ण;

#घोषणा to_clk_slow_rc_osc(hw) container_of(hw, काष्ठा clk_slow_rc_osc, hw)

काष्ठा clk_sam9x5_slow अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *sckcr;
	स्थिर काष्ठा clk_slow_bits *bits;
	u8 parent;
पूर्ण;

#घोषणा to_clk_sam9x5_slow(hw) container_of(hw, काष्ठा clk_sam9x5_slow, hw)

अटल पूर्णांक clk_slow_osc_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_slow_osc *osc = to_clk_slow_osc(hw);
	व्योम __iomem *sckcr = osc->sckcr;
	u32 पंचांगp = पढ़ोl(sckcr);

	अगर (पंचांगp & (osc->bits->cr_osc32byp | osc->bits->cr_osc32en))
		वापस 0;

	ग_लिखोl(पंचांगp | osc->bits->cr_osc32en, sckcr);

	अगर (प्रणाली_state < SYSTEM_RUNNING)
		udelay(osc->startup_usec);
	अन्यथा
		usleep_range(osc->startup_usec, osc->startup_usec + 1);

	वापस 0;
पूर्ण

अटल व्योम clk_slow_osc_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_slow_osc *osc = to_clk_slow_osc(hw);
	व्योम __iomem *sckcr = osc->sckcr;
	u32 पंचांगp = पढ़ोl(sckcr);

	अगर (पंचांगp & osc->bits->cr_osc32byp)
		वापस;

	ग_लिखोl(पंचांगp & ~osc->bits->cr_osc32en, sckcr);
पूर्ण

अटल पूर्णांक clk_slow_osc_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_slow_osc *osc = to_clk_slow_osc(hw);
	व्योम __iomem *sckcr = osc->sckcr;
	u32 पंचांगp = पढ़ोl(sckcr);

	अगर (पंचांगp & osc->bits->cr_osc32byp)
		वापस 1;

	वापस !!(पंचांगp & osc->bits->cr_osc32en);
पूर्ण

अटल स्थिर काष्ठा clk_ops slow_osc_ops = अणु
	.prepare = clk_slow_osc_prepare,
	.unprepare = clk_slow_osc_unprepare,
	.is_prepared = clk_slow_osc_is_prepared,
पूर्ण;

अटल काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_slow_osc(व्योम __iomem *sckcr,
			   स्थिर अक्षर *name,
			   स्थिर अक्षर *parent_name,
			   अचिन्हित दीर्घ startup,
			   bool bypass,
			   स्थिर काष्ठा clk_slow_bits *bits)
अणु
	काष्ठा clk_slow_osc *osc;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	अगर (!sckcr || !name || !parent_name)
		वापस ERR_PTR(-EINVAL);

	osc = kzalloc(माप(*osc), GFP_KERNEL);
	अगर (!osc)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &slow_osc_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = CLK_IGNORE_UNUSED;

	osc->hw.init = &init;
	osc->sckcr = sckcr;
	osc->startup_usec = startup;
	osc->bits = bits;

	अगर (bypass)
		ग_लिखोl((पढ़ोl(sckcr) & ~osc->bits->cr_osc32en) |
					osc->bits->cr_osc32byp, sckcr);

	hw = &osc->hw;
	ret = clk_hw_रेजिस्टर(शून्य, &osc->hw);
	अगर (ret) अणु
		kमुक्त(osc);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

अटल व्योम at91_clk_unरेजिस्टर_slow_osc(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_slow_osc *osc = to_clk_slow_osc(hw);

	clk_hw_unरेजिस्टर(hw);
	kमुक्त(osc);
पूर्ण

अटल अचिन्हित दीर्घ clk_slow_rc_osc_recalc_rate(काष्ठा clk_hw *hw,
						 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_slow_rc_osc *osc = to_clk_slow_rc_osc(hw);

	वापस osc->frequency;
पूर्ण

अटल अचिन्हित दीर्घ clk_slow_rc_osc_recalc_accuracy(काष्ठा clk_hw *hw,
						     अचिन्हित दीर्घ parent_acc)
अणु
	काष्ठा clk_slow_rc_osc *osc = to_clk_slow_rc_osc(hw);

	वापस osc->accuracy;
पूर्ण

अटल पूर्णांक clk_slow_rc_osc_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_slow_rc_osc *osc = to_clk_slow_rc_osc(hw);
	व्योम __iomem *sckcr = osc->sckcr;

	ग_लिखोl(पढ़ोl(sckcr) | osc->bits->cr_rcen, sckcr);

	अगर (प्रणाली_state < SYSTEM_RUNNING)
		udelay(osc->startup_usec);
	अन्यथा
		usleep_range(osc->startup_usec, osc->startup_usec + 1);

	वापस 0;
पूर्ण

अटल व्योम clk_slow_rc_osc_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_slow_rc_osc *osc = to_clk_slow_rc_osc(hw);
	व्योम __iomem *sckcr = osc->sckcr;

	ग_लिखोl(पढ़ोl(sckcr) & ~osc->bits->cr_rcen, sckcr);
पूर्ण

अटल पूर्णांक clk_slow_rc_osc_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_slow_rc_osc *osc = to_clk_slow_rc_osc(hw);

	वापस !!(पढ़ोl(osc->sckcr) & osc->bits->cr_rcen);
पूर्ण

अटल स्थिर काष्ठा clk_ops slow_rc_osc_ops = अणु
	.prepare = clk_slow_rc_osc_prepare,
	.unprepare = clk_slow_rc_osc_unprepare,
	.is_prepared = clk_slow_rc_osc_is_prepared,
	.recalc_rate = clk_slow_rc_osc_recalc_rate,
	.recalc_accuracy = clk_slow_rc_osc_recalc_accuracy,
पूर्ण;

अटल काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_slow_rc_osc(व्योम __iomem *sckcr,
			      स्थिर अक्षर *name,
			      अचिन्हित दीर्घ frequency,
			      अचिन्हित दीर्घ accuracy,
			      अचिन्हित दीर्घ startup,
			      स्थिर काष्ठा clk_slow_bits *bits)
अणु
	काष्ठा clk_slow_rc_osc *osc;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	अगर (!sckcr || !name)
		वापस ERR_PTR(-EINVAL);

	osc = kzalloc(माप(*osc), GFP_KERNEL);
	अगर (!osc)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &slow_rc_osc_ops;
	init.parent_names = शून्य;
	init.num_parents = 0;
	init.flags = CLK_IGNORE_UNUSED;

	osc->hw.init = &init;
	osc->sckcr = sckcr;
	osc->bits = bits;
	osc->frequency = frequency;
	osc->accuracy = accuracy;
	osc->startup_usec = startup;

	hw = &osc->hw;
	ret = clk_hw_रेजिस्टर(शून्य, &osc->hw);
	अगर (ret) अणु
		kमुक्त(osc);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

अटल व्योम at91_clk_unरेजिस्टर_slow_rc_osc(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_slow_rc_osc *osc = to_clk_slow_rc_osc(hw);

	clk_hw_unरेजिस्टर(hw);
	kमुक्त(osc);
पूर्ण

अटल पूर्णांक clk_sam9x5_slow_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_sam9x5_slow *slowck = to_clk_sam9x5_slow(hw);
	व्योम __iomem *sckcr = slowck->sckcr;
	u32 पंचांगp;

	अगर (index > 1)
		वापस -EINVAL;

	पंचांगp = पढ़ोl(sckcr);

	अगर ((!index && !(पंचांगp & slowck->bits->cr_oscsel)) ||
	    (index && (पंचांगp & slowck->bits->cr_oscsel)))
		वापस 0;

	अगर (index)
		पंचांगp |= slowck->bits->cr_oscsel;
	अन्यथा
		पंचांगp &= ~slowck->bits->cr_oscsel;

	ग_लिखोl(पंचांगp, sckcr);

	अगर (प्रणाली_state < SYSTEM_RUNNING)
		udelay(SLOWCK_SW_TIME_USEC);
	अन्यथा
		usleep_range(SLOWCK_SW_TIME_USEC, SLOWCK_SW_TIME_USEC + 1);

	वापस 0;
पूर्ण

अटल u8 clk_sam9x5_slow_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_sam9x5_slow *slowck = to_clk_sam9x5_slow(hw);

	वापस !!(पढ़ोl(slowck->sckcr) & slowck->bits->cr_oscsel);
पूर्ण

अटल स्थिर काष्ठा clk_ops sam9x5_slow_ops = अणु
	.set_parent = clk_sam9x5_slow_set_parent,
	.get_parent = clk_sam9x5_slow_get_parent,
पूर्ण;

अटल काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_sam9x5_slow(व्योम __iomem *sckcr,
			      स्थिर अक्षर *name,
			      स्थिर अक्षर **parent_names,
			      पूर्णांक num_parents,
			      स्थिर काष्ठा clk_slow_bits *bits)
अणु
	काष्ठा clk_sam9x5_slow *slowck;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	अगर (!sckcr || !name || !parent_names || !num_parents)
		वापस ERR_PTR(-EINVAL);

	slowck = kzalloc(माप(*slowck), GFP_KERNEL);
	अगर (!slowck)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &sam9x5_slow_ops;
	init.parent_names = parent_names;
	init.num_parents = num_parents;
	init.flags = 0;

	slowck->hw.init = &init;
	slowck->sckcr = sckcr;
	slowck->bits = bits;
	slowck->parent = !!(पढ़ोl(sckcr) & slowck->bits->cr_oscsel);

	hw = &slowck->hw;
	ret = clk_hw_रेजिस्टर(शून्य, &slowck->hw);
	अगर (ret) अणु
		kमुक्त(slowck);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

अटल व्योम at91_clk_unरेजिस्टर_sam9x5_slow(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_sam9x5_slow *slowck = to_clk_sam9x5_slow(hw);

	clk_hw_unरेजिस्टर(hw);
	kमुक्त(slowck);
पूर्ण

अटल व्योम __init at91sam9x5_sckc_रेजिस्टर(काष्ठा device_node *np,
					    अचिन्हित पूर्णांक rc_osc_startup_us,
					    स्थिर काष्ठा clk_slow_bits *bits)
अणु
	स्थिर अक्षर *parent_names[2] = अणु "slow_rc_osc", "slow_osc" पूर्ण;
	व्योम __iomem *regbase = of_iomap(np, 0);
	काष्ठा device_node *child = शून्य;
	स्थिर अक्षर *xtal_name;
	काष्ठा clk_hw *slow_rc, *slow_osc, *slowck;
	bool bypass;
	पूर्णांक ret;

	अगर (!regbase)
		वापस;

	slow_rc = at91_clk_रेजिस्टर_slow_rc_osc(regbase, parent_names[0],
						32768, 50000000,
						rc_osc_startup_us, bits);
	अगर (IS_ERR(slow_rc))
		वापस;

	xtal_name = of_clk_get_parent_name(np, 0);
	अगर (!xtal_name) अणु
		/* DT backward compatibility */
		child = of_get_compatible_child(np, "atmel,at91sam9x5-clk-slow-osc");
		अगर (!child)
			जाओ unरेजिस्टर_slow_rc;

		xtal_name = of_clk_get_parent_name(child, 0);
		bypass = of_property_पढ़ो_bool(child, "atmel,osc-bypass");

		child =  of_get_compatible_child(np, "atmel,at91sam9x5-clk-slow");
	पूर्ण अन्यथा अणु
		bypass = of_property_पढ़ो_bool(np, "atmel,osc-bypass");
	पूर्ण

	अगर (!xtal_name)
		जाओ unरेजिस्टर_slow_rc;

	slow_osc = at91_clk_रेजिस्टर_slow_osc(regbase, parent_names[1],
					      xtal_name, 1200000, bypass, bits);
	अगर (IS_ERR(slow_osc))
		जाओ unरेजिस्टर_slow_rc;

	slowck = at91_clk_रेजिस्टर_sam9x5_slow(regbase, "slowck", parent_names,
					       2, bits);
	अगर (IS_ERR(slowck))
		जाओ unरेजिस्टर_slow_osc;

	/* DT backward compatibility */
	अगर (child)
		ret = of_clk_add_hw_provider(child, of_clk_hw_simple_get,
					     slowck);
	अन्यथा
		ret = of_clk_add_hw_provider(np, of_clk_hw_simple_get, slowck);

	अगर (WARN_ON(ret))
		जाओ unरेजिस्टर_slowck;

	वापस;

unरेजिस्टर_slowck:
	at91_clk_unरेजिस्टर_sam9x5_slow(slowck);
unरेजिस्टर_slow_osc:
	at91_clk_unरेजिस्टर_slow_osc(slow_osc);
unरेजिस्टर_slow_rc:
	at91_clk_unरेजिस्टर_slow_rc_osc(slow_rc);
पूर्ण

अटल स्थिर काष्ठा clk_slow_bits at91sam9x5_bits = अणु
	.cr_rcen = BIT(0),
	.cr_osc32en = BIT(1),
	.cr_osc32byp = BIT(2),
	.cr_oscsel = BIT(3),
पूर्ण;

अटल व्योम __init of_at91sam9x5_sckc_setup(काष्ठा device_node *np)
अणु
	at91sam9x5_sckc_रेजिस्टर(np, 75, &at91sam9x5_bits);
पूर्ण
CLK_OF_DECLARE(at91sam9x5_clk_sckc, "atmel,at91sam9x5-sckc",
	       of_at91sam9x5_sckc_setup);

अटल व्योम __init of_sama5d3_sckc_setup(काष्ठा device_node *np)
अणु
	at91sam9x5_sckc_रेजिस्टर(np, 500, &at91sam9x5_bits);
पूर्ण
CLK_OF_DECLARE(sama5d3_clk_sckc, "atmel,sama5d3-sckc",
	       of_sama5d3_sckc_setup);

अटल स्थिर काष्ठा clk_slow_bits at91sam9x60_bits = अणु
	.cr_osc32en = BIT(1),
	.cr_osc32byp = BIT(2),
	.cr_oscsel = BIT(24),
पूर्ण;

अटल व्योम __init of_sam9x60_sckc_setup(काष्ठा device_node *np)
अणु
	व्योम __iomem *regbase = of_iomap(np, 0);
	काष्ठा clk_hw_onecell_data *clk_data;
	काष्ठा clk_hw *slow_rc, *slow_osc;
	स्थिर अक्षर *xtal_name;
	स्थिर अक्षर *parent_names[2] = अणु "slow_rc_osc", "slow_osc" पूर्ण;
	bool bypass;
	पूर्णांक ret;

	अगर (!regbase)
		वापस;

	slow_rc = clk_hw_रेजिस्टर_fixed_rate_with_accuracy(शून्य, parent_names[0],
							   शून्य, 0, 32768,
							   93750000);
	अगर (IS_ERR(slow_rc))
		वापस;

	xtal_name = of_clk_get_parent_name(np, 0);
	अगर (!xtal_name)
		जाओ unरेजिस्टर_slow_rc;

	bypass = of_property_पढ़ो_bool(np, "atmel,osc-bypass");
	slow_osc = at91_clk_रेजिस्टर_slow_osc(regbase, parent_names[1],
					      xtal_name, 5000000, bypass,
					      &at91sam9x60_bits);
	अगर (IS_ERR(slow_osc))
		जाओ unरेजिस्टर_slow_rc;

	clk_data = kzalloc(काष्ठा_size(clk_data, hws, 2), GFP_KERNEL);
	अगर (!clk_data)
		जाओ unरेजिस्टर_slow_osc;

	/* MD_SLCK and TD_SLCK. */
	clk_data->num = 2;
	clk_data->hws[0] = clk_hw_रेजिस्टर_fixed_rate(शून्य, "md_slck",
						      parent_names[0],
						      0, 32768);
	अगर (IS_ERR(clk_data->hws[0]))
		जाओ clk_data_मुक्त;

	clk_data->hws[1] = at91_clk_रेजिस्टर_sam9x5_slow(regbase, "td_slck",
							 parent_names, 2,
							 &at91sam9x60_bits);
	अगर (IS_ERR(clk_data->hws[1]))
		जाओ unरेजिस्टर_md_slck;

	ret = of_clk_add_hw_provider(np, of_clk_hw_onecell_get, clk_data);
	अगर (WARN_ON(ret))
		जाओ unरेजिस्टर_td_slck;

	वापस;

unरेजिस्टर_td_slck:
	at91_clk_unरेजिस्टर_sam9x5_slow(clk_data->hws[1]);
unरेजिस्टर_md_slck:
	clk_hw_unरेजिस्टर(clk_data->hws[0]);
clk_data_मुक्त:
	kमुक्त(clk_data);
unरेजिस्टर_slow_osc:
	at91_clk_unरेजिस्टर_slow_osc(slow_osc);
unरेजिस्टर_slow_rc:
	clk_hw_unरेजिस्टर(slow_rc);
पूर्ण
CLK_OF_DECLARE(sam9x60_clk_sckc, "microchip,sam9x60-sckc",
	       of_sam9x60_sckc_setup);

अटल पूर्णांक clk_sama5d4_slow_osc_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_sama5d4_slow_osc *osc = to_clk_sama5d4_slow_osc(hw);

	अगर (osc->prepared)
		वापस 0;

	/*
	 * Assume that अगर it has alपढ़ोy been selected (क्रम example by the
	 * bootloader), enough समय has aपढ़ोy passed.
	 */
	अगर ((पढ़ोl(osc->sckcr) & osc->bits->cr_oscsel)) अणु
		osc->prepared = true;
		वापस 0;
	पूर्ण

	अगर (प्रणाली_state < SYSTEM_RUNNING)
		udelay(osc->startup_usec);
	अन्यथा
		usleep_range(osc->startup_usec, osc->startup_usec + 1);
	osc->prepared = true;

	वापस 0;
पूर्ण

अटल पूर्णांक clk_sama5d4_slow_osc_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_sama5d4_slow_osc *osc = to_clk_sama5d4_slow_osc(hw);

	वापस osc->prepared;
पूर्ण

अटल स्थिर काष्ठा clk_ops sama5d4_slow_osc_ops = अणु
	.prepare = clk_sama5d4_slow_osc_prepare,
	.is_prepared = clk_sama5d4_slow_osc_is_prepared,
पूर्ण;

अटल स्थिर काष्ठा clk_slow_bits at91sama5d4_bits = अणु
	.cr_oscsel = BIT(3),
पूर्ण;

अटल व्योम __init of_sama5d4_sckc_setup(काष्ठा device_node *np)
अणु
	व्योम __iomem *regbase = of_iomap(np, 0);
	काष्ठा clk_hw *slow_rc, *slowck;
	काष्ठा clk_sama5d4_slow_osc *osc;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *xtal_name;
	स्थिर अक्षर *parent_names[2] = अणु "slow_rc_osc", "slow_osc" पूर्ण;
	पूर्णांक ret;

	अगर (!regbase)
		वापस;

	slow_rc = clk_hw_रेजिस्टर_fixed_rate_with_accuracy(शून्य,
							   parent_names[0],
							   शून्य, 0, 32768,
							   250000000);
	अगर (IS_ERR(slow_rc))
		वापस;

	xtal_name = of_clk_get_parent_name(np, 0);

	osc = kzalloc(माप(*osc), GFP_KERNEL);
	अगर (!osc)
		जाओ unरेजिस्टर_slow_rc;

	init.name = parent_names[1];
	init.ops = &sama5d4_slow_osc_ops;
	init.parent_names = &xtal_name;
	init.num_parents = 1;
	init.flags = CLK_IGNORE_UNUSED;

	osc->hw.init = &init;
	osc->sckcr = regbase;
	osc->startup_usec = 1200000;
	osc->bits = &at91sama5d4_bits;

	ret = clk_hw_रेजिस्टर(शून्य, &osc->hw);
	अगर (ret)
		जाओ मुक्त_slow_osc_data;

	slowck = at91_clk_रेजिस्टर_sam9x5_slow(regbase, "slowck",
					       parent_names, 2,
					       &at91sama5d4_bits);
	अगर (IS_ERR(slowck))
		जाओ unरेजिस्टर_slow_osc;

	ret = of_clk_add_hw_provider(np, of_clk_hw_simple_get, slowck);
	अगर (WARN_ON(ret))
		जाओ unरेजिस्टर_slowck;

	वापस;

unरेजिस्टर_slowck:
	at91_clk_unरेजिस्टर_sam9x5_slow(slowck);
unरेजिस्टर_slow_osc:
	clk_hw_unरेजिस्टर(&osc->hw);
मुक्त_slow_osc_data:
	kमुक्त(osc);
unरेजिस्टर_slow_rc:
	clk_hw_unरेजिस्टर(slow_rc);
पूर्ण
CLK_OF_DECLARE(sama5d4_clk_sckc, "atmel,sama5d4-sckc",
	       of_sama5d4_sckc_setup);
