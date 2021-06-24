<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/clk-provider.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "mcde_drm.h"
#समावेश "mcde_display_regs.h"

/* The MCDE पूर्णांकernal घड़ी भागiders क्रम FIFO A and B */
काष्ठा mcde_clk_भाग अणु
	काष्ठा clk_hw hw;
	काष्ठा mcde *mcde;
	u32 cr;
	u32 cr_भाग;
पूर्ण;

अटल पूर्णांक mcde_clk_भाग_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा mcde_clk_भाग *cभाग = container_of(hw, काष्ठा mcde_clk_भाग, hw);
	काष्ठा mcde *mcde = cभाग->mcde;
	u32 val;

	spin_lock(&mcde->fअगरo_crx1_lock);
	val = पढ़ोl(mcde->regs + cभाग->cr);
	/*
	 * Select the PLL72 (LCD) घड़ी as parent
	 * FIXME: implement other parents.
	 */
	val &= ~MCDE_CRX1_CLKSEL_MASK;
	val |= MCDE_CRX1_CLKSEL_CLKPLL72 << MCDE_CRX1_CLKSEL_SHIFT;
	/* Internal घड़ी */
	val |= MCDE_CRA1_CLKTYPE_TVXCLKSEL1;

	/* Clear then set the भागider */
	val &= ~(MCDE_CRX1_BCD | MCDE_CRX1_PCD_MASK);
	val |= cभाग->cr_भाग;

	ग_लिखोl(val, mcde->regs + cभाग->cr);
	spin_unlock(&mcde->fअगरo_crx1_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक mcde_clk_भाग_choose_भाग(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ *prate, bool set_parent)
अणु
	पूर्णांक best_भाग = 1, भाग;
	काष्ठा clk_hw *parent = clk_hw_get_parent(hw);
	अचिन्हित दीर्घ best_prate = 0;
	अचिन्हित दीर्घ best_dअगरf = ~0ul;
	पूर्णांक max_भाग = (1 << MCDE_CRX1_PCD_BITS) - 1;

	क्रम (भाग = 1; भाग < max_भाग; भाग++) अणु
		अचिन्हित दीर्घ this_prate, भाग_rate, dअगरf;

		अगर (set_parent)
			this_prate = clk_hw_round_rate(parent, rate * भाग);
		अन्यथा
			this_prate = *prate;
		भाग_rate = DIV_ROUND_UP_ULL(this_prate, भाग);
		dअगरf = असल(rate - भाग_rate);

		अगर (dअगरf < best_dअगरf) अणु
			best_भाग = भाग;
			best_dअगरf = dअगरf;
			best_prate = this_prate;
		पूर्ण
	पूर्ण

	*prate = best_prate;
	वापस best_भाग;
पूर्ण

अटल दीर्घ mcde_clk_भाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ *prate)
अणु
	पूर्णांक भाग = mcde_clk_भाग_choose_भाग(hw, rate, prate, true);

	वापस DIV_ROUND_UP_ULL(*prate, भाग);
पूर्ण

अटल अचिन्हित दीर्घ mcde_clk_भाग_recalc_rate(काष्ठा clk_hw *hw,
					       अचिन्हित दीर्घ prate)
अणु
	काष्ठा mcde_clk_भाग *cभाग = container_of(hw, काष्ठा mcde_clk_भाग, hw);
	काष्ठा mcde *mcde = cभाग->mcde;
	u32 cr;
	पूर्णांक भाग;

	/*
	 * If the MCDE is not घातered we can't access रेजिस्टरs.
	 * It will come up with 0 in the भागider रेजिस्टर bits, which
	 * means "divide by 2".
	 */
	अगर (!regulator_is_enabled(mcde->epod))
		वापस DIV_ROUND_UP_ULL(prate, 2);

	cr = पढ़ोl(mcde->regs + cभाग->cr);
	अगर (cr & MCDE_CRX1_BCD)
		वापस prate;

	/* 0 in the PCD means "divide by 2", 1 means "divide by 3" etc */
	भाग = cr & MCDE_CRX1_PCD_MASK;
	भाग += 2;

	वापस DIV_ROUND_UP_ULL(prate, भाग);
पूर्ण

अटल पूर्णांक mcde_clk_भाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ prate)
अणु
	काष्ठा mcde_clk_भाग *cभाग = container_of(hw, काष्ठा mcde_clk_भाग, hw);
	पूर्णांक भाग = mcde_clk_भाग_choose_भाग(hw, rate, &prate, false);
	u32 cr = 0;

	/*
	 * We cache the CR bits to set the भागide in the state so that
	 * we can call this beक्रमe we can even ग_लिखो to the hardware.
	 */
	अगर (भाग == 1) अणु
		/* Bypass घड़ी भागider */
		cr |= MCDE_CRX1_BCD;
	पूर्ण अन्यथा अणु
		भाग -= 2;
		cr |= भाग & MCDE_CRX1_PCD_MASK;
	पूर्ण
	cभाग->cr_भाग = cr;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops mcde_clk_भाग_ops = अणु
	.enable = mcde_clk_भाग_enable,
	.recalc_rate = mcde_clk_भाग_recalc_rate,
	.round_rate = mcde_clk_भाग_round_rate,
	.set_rate = mcde_clk_भाग_set_rate,
पूर्ण;

पूर्णांक mcde_init_घड़ी_भागider(काष्ठा mcde *mcde)
अणु
	काष्ठा device *dev = mcde->dev;
	काष्ठा mcde_clk_भाग *fअगरoa;
	काष्ठा mcde_clk_भाग *fअगरob;
	स्थिर अक्षर *parent_name;
	काष्ठा clk_init_data fअगरoa_init = अणु
		.name = "fifoa",
		.ops = &mcde_clk_भाग_ops,
		.parent_names = &parent_name,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण;
	काष्ठा clk_init_data fअगरob_init = अणु
		.name = "fifob",
		.ops = &mcde_clk_भाग_ops,
		.parent_names = &parent_name,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण;
	पूर्णांक ret;

	spin_lock_init(&mcde->fअगरo_crx1_lock);
	parent_name = __clk_get_name(mcde->lcd_clk);

	/* Allocate 2 घड़ीs */
	fअगरoa = devm_kzalloc(dev, माप(*fअगरoa), GFP_KERNEL);
	अगर (!fअगरoa)
		वापस -ENOMEM;
	fअगरob = devm_kzalloc(dev, माप(*fअगरob), GFP_KERNEL);
	अगर (!fअगरob)
		वापस -ENOMEM;

	fअगरoa->mcde = mcde;
	fअगरoa->cr = MCDE_CRA1;
	fअगरoa->hw.init = &fअगरoa_init;
	ret = devm_clk_hw_रेजिस्टर(dev, &fअगरoa->hw);
	अगर (ret) अणु
		dev_err(dev, "error registering FIFO A clock divider\n");
		वापस ret;
	पूर्ण
	mcde->fअगरoa_clk = fअगरoa->hw.clk;

	fअगरob->mcde = mcde;
	fअगरob->cr = MCDE_CRB1;
	fअगरob->hw.init = &fअगरob_init;
	ret = devm_clk_hw_रेजिस्टर(dev, &fअगरob->hw);
	अगर (ret) अणु
		dev_err(dev, "error registering FIFO B clock divider\n");
		वापस ret;
	पूर्ण
	mcde->fअगरob_clk = fअगरob->hw.clk;

	वापस 0;
पूर्ण
