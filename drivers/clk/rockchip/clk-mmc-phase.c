<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2014 Google, Inc
 * Author: Alexandru M Stan <amstan@chromium.org>
 */

#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश "clk.h"

काष्ठा rockchip_mmc_घड़ी अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*reg;
	पूर्णांक		id;
	पूर्णांक		shअगरt;
	पूर्णांक		cached_phase;
	काष्ठा notअगरier_block clk_rate_change_nb;
पूर्ण;

#घोषणा to_mmc_घड़ी(_hw) container_of(_hw, काष्ठा rockchip_mmc_घड़ी, hw)

#घोषणा RK3288_MMC_CLKGEN_DIV 2

अटल अचिन्हित दीर्घ rockchip_mmc_recalc(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	वापस parent_rate / RK3288_MMC_CLKGEN_DIV;
पूर्ण

#घोषणा ROCKCHIP_MMC_DELAY_SEL BIT(10)
#घोषणा ROCKCHIP_MMC_DEGREE_MASK 0x3
#घोषणा ROCKCHIP_MMC_DELAYNUM_OFFSET 2
#घोषणा ROCKCHIP_MMC_DELAYNUM_MASK (0xff << ROCKCHIP_MMC_DELAYNUM_OFFSET)

#घोषणा PSECS_PER_SEC 1000000000000LL

/*
 * Each fine delay is between 44ps-77ps. Assume each fine delay is 60ps to
 * simplअगरy calculations. So 45degs could be anywhere between 33deg and 57.8deg.
 */
#घोषणा ROCKCHIP_MMC_DELAY_ELEMENT_PSEC 60

अटल पूर्णांक rockchip_mmc_get_phase(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_mmc_घड़ी *mmc_घड़ी = to_mmc_घड़ी(hw);
	अचिन्हित दीर्घ rate = clk_hw_get_rate(hw);
	u32 raw_value;
	u16 degrees;
	u32 delay_num = 0;

	/* Constant संकेत, no measurable phase shअगरt */
	अगर (!rate)
		वापस 0;

	raw_value = पढ़ोl(mmc_घड़ी->reg) >> (mmc_घड़ी->shअगरt);

	degrees = (raw_value & ROCKCHIP_MMC_DEGREE_MASK) * 90;

	अगर (raw_value & ROCKCHIP_MMC_DELAY_SEL) अणु
		/* degrees/delaynum * 1000000 */
		अचिन्हित दीर्घ factor = (ROCKCHIP_MMC_DELAY_ELEMENT_PSEC / 10) *
					36 * (rate / 10000);

		delay_num = (raw_value & ROCKCHIP_MMC_DELAYNUM_MASK);
		delay_num >>= ROCKCHIP_MMC_DELAYNUM_OFFSET;
		degrees += DIV_ROUND_CLOSEST(delay_num * factor, 1000000);
	पूर्ण

	वापस degrees % 360;
पूर्ण

अटल पूर्णांक rockchip_mmc_set_phase(काष्ठा clk_hw *hw, पूर्णांक degrees)
अणु
	काष्ठा rockchip_mmc_घड़ी *mmc_घड़ी = to_mmc_घड़ी(hw);
	अचिन्हित दीर्घ rate = clk_hw_get_rate(hw);
	u8 nineties, reमुख्यder;
	u8 delay_num;
	u32 raw_value;
	u32 delay;

	/*
	 * The below calculation is based on the output घड़ी from
	 * MMC host to the card, which expects the phase घड़ी inherits
	 * the घड़ी rate from its parent, namely the output घड़ी
	 * provider of MMC host. However, things may go wrong अगर
	 * (1) It is orphan.
	 * (2) It is asचिन्हित to the wrong parent.
	 *
	 * This check help debug the हाल (1), which seems to be the
	 * most likely problem we often face and which makes it dअगरficult
	 * क्रम people to debug unstable mmc tuning results.
	 */
	अगर (!rate) अणु
		pr_err("%s: invalid clk rate\n", __func__);
		वापस -EINVAL;
	पूर्ण

	nineties = degrees / 90;
	reमुख्यder = (degrees % 90);

	/*
	 * Due to the inexact nature of the "fine" delay, we might
	 * actually go non-monotonic.  We करोn't go _too_ monotonic
	 * though, so we should be OK.  Here are options of how we may
	 * work:
	 *
	 * Ideally we end up with:
	 *   1.0, 2.0, ..., 69.0, 70.0, ...,  89.0, 90.0
	 *
	 * On one extreme (अगर delay is actually 44ps):
	 *   .73, 1.5, ..., 50.6, 51.3, ...,  65.3, 90.0
	 * The other (अगर delay is actually 77ps):
	 *   1.3, 2.6, ..., 88.6. 89.8, ..., 114.0, 90
	 *
	 * It's possible we might make a delay that is up to 25
	 * degrees off from what we think we're making.  That's OK
	 * though because we should be REALLY far from any bad range.
	 */

	/*
	 * Convert to delay; करो a little extra work to make sure we
	 * करोn't overflow 32-bit / 64-bit numbers.
	 */
	delay = 10000000; /* PSECS_PER_SEC / 10000 / 10 */
	delay *= reमुख्यder;
	delay = DIV_ROUND_CLOSEST(delay,
			(rate / 1000) * 36 *
				(ROCKCHIP_MMC_DELAY_ELEMENT_PSEC / 10));

	delay_num = (u8) min_t(u32, delay, 255);

	raw_value = delay_num ? ROCKCHIP_MMC_DELAY_SEL : 0;
	raw_value |= delay_num << ROCKCHIP_MMC_DELAYNUM_OFFSET;
	raw_value |= nineties;
	ग_लिखोl(HIWORD_UPDATE(raw_value, 0x07ff, mmc_घड़ी->shअगरt),
	       mmc_घड़ी->reg);

	pr_debug("%s->set_phase(%d) delay_nums=%u reg[0x%p]=0x%03x actual_degrees=%d\n",
		clk_hw_get_name(hw), degrees, delay_num,
		mmc_घड़ी->reg, raw_value>>(mmc_घड़ी->shअगरt),
		rockchip_mmc_get_phase(hw)
	);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops rockchip_mmc_clk_ops = अणु
	.recalc_rate	= rockchip_mmc_recalc,
	.get_phase	= rockchip_mmc_get_phase,
	.set_phase	= rockchip_mmc_set_phase,
पूर्ण;

#घोषणा to_rockchip_mmc_घड़ी(x) \
	container_of(x, काष्ठा rockchip_mmc_घड़ी, clk_rate_change_nb)
अटल पूर्णांक rockchip_mmc_clk_rate_notअगरy(काष्ठा notअगरier_block *nb,
					अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा rockchip_mmc_घड़ी *mmc_घड़ी = to_rockchip_mmc_घड़ी(nb);
	काष्ठा clk_notअगरier_data *ndata = data;

	/*
	 * rockchip_mmc_clk is mostly used by mmc controllers to sample
	 * the पूर्णांकput data, which expects the fixed phase after the tuning
	 * process. However अगर the घड़ी rate is changed, the phase is stale
	 * and may अवरोध the data sampling. So here we try to restore the phase
	 * क्रम that हाल, except that
	 * (1) cached_phase is invaild since we inevitably cached it when the
	 * घड़ी provider be reparented from orphan to its real parent in the
	 * first place. Otherwise we may mess up the initialization of MMC cards
	 * since we only set the शेष sample phase and drive phase later on.
	 * (2) the new coming rate is higher than the older one since mmc driver
	 * set the max-frequency to match the boards' ability but we can't go
	 * over the heads of that, otherwise the tests smoke out the issue.
	 */
	अगर (ndata->old_rate <= ndata->new_rate)
		वापस NOTIFY_DONE;

	अगर (event == PRE_RATE_CHANGE)
		mmc_घड़ी->cached_phase =
			rockchip_mmc_get_phase(&mmc_घड़ी->hw);
	अन्यथा अगर (mmc_घड़ी->cached_phase != -EINVAL &&
		 event == POST_RATE_CHANGE)
		rockchip_mmc_set_phase(&mmc_घड़ी->hw, mmc_घड़ी->cached_phase);

	वापस NOTIFY_DONE;
पूर्ण

काष्ठा clk *rockchip_clk_रेजिस्टर_mmc(स्थिर अक्षर *name,
				स्थिर अक्षर *स्थिर *parent_names, u8 num_parents,
				व्योम __iomem *reg, पूर्णांक shअगरt)
अणु
	काष्ठा clk_init_data init;
	काष्ठा rockchip_mmc_घड़ी *mmc_घड़ी;
	काष्ठा clk *clk;
	पूर्णांक ret;

	mmc_घड़ी = kदो_स्मृति(माप(*mmc_घड़ी), GFP_KERNEL);
	अगर (!mmc_घड़ी)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.flags = 0;
	init.num_parents = num_parents;
	init.parent_names = parent_names;
	init.ops = &rockchip_mmc_clk_ops;

	mmc_घड़ी->hw.init = &init;
	mmc_घड़ी->reg = reg;
	mmc_घड़ी->shअगरt = shअगरt;

	clk = clk_रेजिस्टर(शून्य, &mmc_घड़ी->hw);
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		जाओ err_रेजिस्टर;
	पूर्ण

	mmc_घड़ी->clk_rate_change_nb.notअगरier_call =
				&rockchip_mmc_clk_rate_notअगरy;
	ret = clk_notअगरier_रेजिस्टर(clk, &mmc_घड़ी->clk_rate_change_nb);
	अगर (ret)
		जाओ err_notअगरier;

	वापस clk;
err_notअगरier:
	clk_unरेजिस्टर(clk);
err_रेजिस्टर:
	kमुक्त(mmc_घड़ी);
	वापस ERR_PTR(ret);
पूर्ण
