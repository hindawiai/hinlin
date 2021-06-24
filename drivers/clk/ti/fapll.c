<शैली गुरु>
/*
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/math64.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk/ti.h>

/* FAPLL Control Register PLL_CTRL */
#घोषणा FAPLL_MAIN_MULT_N_SHIFT	16
#घोषणा FAPLL_MAIN_DIV_P_SHIFT	8
#घोषणा FAPLL_MAIN_LOCK		BIT(7)
#घोषणा FAPLL_MAIN_PLLEN	BIT(3)
#घोषणा FAPLL_MAIN_BP		BIT(2)
#घोषणा FAPLL_MAIN_LOC_CTL	BIT(0)

#घोषणा FAPLL_MAIN_MAX_MULT_N	0xffff
#घोषणा FAPLL_MAIN_MAX_DIV_P	0xff
#घोषणा FAPLL_MAIN_CLEAR_MASK	\
	((FAPLL_MAIN_MAX_MULT_N << FAPLL_MAIN_MULT_N_SHIFT) | \
	 (FAPLL_MAIN_DIV_P_SHIFT << FAPLL_MAIN_DIV_P_SHIFT) | \
	 FAPLL_MAIN_LOC_CTL)

/* FAPLL घातerकरोwn रेजिस्टर PWD */
#घोषणा FAPLL_PWD_OFFSET	4

#घोषणा MAX_FAPLL_OUTPUTS	7
#घोषणा FAPLL_MAX_RETRIES	1000

#घोषणा to_fapll(_hw)		container_of(_hw, काष्ठा fapll_data, hw)
#घोषणा to_synth(_hw)		container_of(_hw, काष्ठा fapll_synth, hw)

/* The bypass bit is inverted on the ddr_pll.. */
#घोषणा fapll_is_ddr_pll(va)	(((u32)(va) & 0xffff) == 0x0440)

/*
 * The audio_pll_clk1 input is hard wired to the 27MHz bypass घड़ी,
 * and the audio_pll_clk1 synthesizer is hardwared to 32KiHz output.
 */
#घोषणा is_ddr_pll_clk1(va)	(((u32)(va) & 0xffff) == 0x044c)
#घोषणा is_audio_pll_clk1(va)	(((u32)(va) & 0xffff) == 0x04a8)

/* Synthesizer भागider रेजिस्टर */
#घोषणा SYNTH_LDMDIV1		BIT(8)

/* Synthesizer frequency रेजिस्टर */
#घोषणा SYNTH_LDFREQ		BIT(31)

#घोषणा SYNTH_PHASE_K		8
#घोषणा SYNTH_MAX_INT_DIV	0xf
#घोषणा SYNTH_MAX_DIV_M		0xff

काष्ठा fapll_data अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *base;
	स्थिर अक्षर *name;
	काष्ठा clk *clk_ref;
	काष्ठा clk *clk_bypass;
	काष्ठा clk_onecell_data outमाला_दो;
	bool bypass_bit_inverted;
पूर्ण;

काष्ठा fapll_synth अणु
	काष्ठा clk_hw hw;
	काष्ठा fapll_data *fd;
	पूर्णांक index;
	व्योम __iomem *freq;
	व्योम __iomem *भाग;
	स्थिर अक्षर *name;
	काष्ठा clk *clk_pll;
पूर्ण;

अटल bool ti_fapll_घड़ी_is_bypass(काष्ठा fapll_data *fd)
अणु
	u32 v = पढ़ोl_relaxed(fd->base);

	अगर (fd->bypass_bit_inverted)
		वापस !(v & FAPLL_MAIN_BP);
	अन्यथा
		वापस !!(v & FAPLL_MAIN_BP);
पूर्ण

अटल व्योम ti_fapll_set_bypass(काष्ठा fapll_data *fd)
अणु
	u32 v = पढ़ोl_relaxed(fd->base);

	अगर (fd->bypass_bit_inverted)
		v &= ~FAPLL_MAIN_BP;
	अन्यथा
		v |= FAPLL_MAIN_BP;
	ग_लिखोl_relaxed(v, fd->base);
पूर्ण

अटल व्योम ti_fapll_clear_bypass(काष्ठा fapll_data *fd)
अणु
	u32 v = पढ़ोl_relaxed(fd->base);

	अगर (fd->bypass_bit_inverted)
		v |= FAPLL_MAIN_BP;
	अन्यथा
		v &= ~FAPLL_MAIN_BP;
	ग_लिखोl_relaxed(v, fd->base);
पूर्ण

अटल पूर्णांक ti_fapll_रुको_lock(काष्ठा fapll_data *fd)
अणु
	पूर्णांक retries = FAPLL_MAX_RETRIES;
	u32 v;

	जबतक ((v = पढ़ोl_relaxed(fd->base))) अणु
		अगर (v & FAPLL_MAIN_LOCK)
			वापस 0;

		अगर (retries-- <= 0)
			अवरोध;

		udelay(1);
	पूर्ण

	pr_err("%s failed to lock\n", fd->name);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक ti_fapll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा fapll_data *fd = to_fapll(hw);
	u32 v = पढ़ोl_relaxed(fd->base);

	v |= FAPLL_MAIN_PLLEN;
	ग_लिखोl_relaxed(v, fd->base);
	ti_fapll_रुको_lock(fd);

	वापस 0;
पूर्ण

अटल व्योम ti_fapll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा fapll_data *fd = to_fapll(hw);
	u32 v = पढ़ोl_relaxed(fd->base);

	v &= ~FAPLL_MAIN_PLLEN;
	ग_लिखोl_relaxed(v, fd->base);
पूर्ण

अटल पूर्णांक ti_fapll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा fapll_data *fd = to_fapll(hw);
	u32 v = पढ़ोl_relaxed(fd->base);

	वापस v & FAPLL_MAIN_PLLEN;
पूर्ण

अटल अचिन्हित दीर्घ ti_fapll_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा fapll_data *fd = to_fapll(hw);
	u32 fapll_n, fapll_p, v;
	u64 rate;

	अगर (ti_fapll_घड़ी_is_bypass(fd))
		वापस parent_rate;

	rate = parent_rate;

	/* PLL pre-भागider is P and multiplier is N */
	v = पढ़ोl_relaxed(fd->base);
	fapll_p = (v >> 8) & 0xff;
	अगर (fapll_p)
		करो_भाग(rate, fapll_p);
	fapll_n = v >> 16;
	अगर (fapll_n)
		rate *= fapll_n;

	वापस rate;
पूर्ण

अटल u8 ti_fapll_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा fapll_data *fd = to_fapll(hw);

	अगर (ti_fapll_घड़ी_is_bypass(fd))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ti_fapll_set_भाग_mult(अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ parent_rate,
				 u32 *pre_भाग_p, u32 *mult_n)
अणु
	/*
	 * So far no luck getting decent घड़ी with PLL भागider,
	 * PLL करोes not seem to lock and the संकेत करोes not look
	 * right. It seems the भागider can only be used together
	 * with the multiplier?
	 */
	अगर (rate < parent_rate) अणु
		pr_warn("FAPLL main divider rates unsupported\n");
		वापस -EINVAL;
	पूर्ण

	*mult_n = rate / parent_rate;
	अगर (*mult_n > FAPLL_MAIN_MAX_MULT_N)
		वापस -EINVAL;
	*pre_भाग_p = 1;

	वापस 0;
पूर्ण

अटल दीर्घ ti_fapll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *parent_rate)
अणु
	u32 pre_भाग_p, mult_n;
	पूर्णांक error;

	अगर (!rate)
		वापस -EINVAL;

	error = ti_fapll_set_भाग_mult(rate, *parent_rate,
				      &pre_भाग_p, &mult_n);
	अगर (error)
		वापस error;

	rate = *parent_rate / pre_भाग_p;
	rate *= mult_n;

	वापस rate;
पूर्ण

अटल पूर्णांक ti_fapll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा fapll_data *fd = to_fapll(hw);
	u32 pre_भाग_p, mult_n, v;
	पूर्णांक error;

	अगर (!rate)
		वापस -EINVAL;

	error = ti_fapll_set_भाग_mult(rate, parent_rate,
				      &pre_भाग_p, &mult_n);
	अगर (error)
		वापस error;

	ti_fapll_set_bypass(fd);
	v = पढ़ोl_relaxed(fd->base);
	v &= ~FAPLL_MAIN_CLEAR_MASK;
	v |= pre_भाग_p << FAPLL_MAIN_DIV_P_SHIFT;
	v |= mult_n << FAPLL_MAIN_MULT_N_SHIFT;
	ग_लिखोl_relaxed(v, fd->base);
	अगर (ti_fapll_is_enabled(hw))
		ti_fapll_रुको_lock(fd);
	ti_fapll_clear_bypass(fd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops ti_fapll_ops = अणु
	.enable = ti_fapll_enable,
	.disable = ti_fapll_disable,
	.is_enabled = ti_fapll_is_enabled,
	.recalc_rate = ti_fapll_recalc_rate,
	.get_parent = ti_fapll_get_parent,
	.round_rate = ti_fapll_round_rate,
	.set_rate = ti_fapll_set_rate,
पूर्ण;

अटल पूर्णांक ti_fapll_synth_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा fapll_synth *synth = to_synth(hw);
	u32 v = पढ़ोl_relaxed(synth->fd->base + FAPLL_PWD_OFFSET);

	v &= ~(1 << synth->index);
	ग_लिखोl_relaxed(v, synth->fd->base + FAPLL_PWD_OFFSET);

	वापस 0;
पूर्ण

अटल व्योम ti_fapll_synth_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा fapll_synth *synth = to_synth(hw);
	u32 v = पढ़ोl_relaxed(synth->fd->base + FAPLL_PWD_OFFSET);

	v |= 1 << synth->index;
	ग_लिखोl_relaxed(v, synth->fd->base + FAPLL_PWD_OFFSET);
पूर्ण

अटल पूर्णांक ti_fapll_synth_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा fapll_synth *synth = to_synth(hw);
	u32 v = पढ़ोl_relaxed(synth->fd->base + FAPLL_PWD_OFFSET);

	वापस !(v & (1 << synth->index));
पूर्ण

/*
 * See dm816x TRM chapter 1.10.3 Flying Adder PLL क्रमe more info
 */
अटल अचिन्हित दीर्घ ti_fapll_synth_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा fapll_synth *synth = to_synth(hw);
	u32 synth_भाग_m;
	u64 rate;

	/* The audio_pll_clk1 is hardwired to produce 32.768KiHz घड़ी */
	अगर (!synth->भाग)
		वापस 32768;

	/*
	 * PLL in bypass sets the synths in bypass mode too. The PLL rate
	 * can be also be set to 27MHz, so we can't use parent_rate to
	 * check क्रम bypass mode.
	 */
	अगर (ti_fapll_घड़ी_is_bypass(synth->fd))
		वापस parent_rate;

	rate = parent_rate;

	/*
	 * Synth frequency पूर्णांकeger and fractional भागider.
	 * Note that the phase output K is 8, so the result needs
	 * to be multiplied by SYNTH_PHASE_K.
	 */
	अगर (synth->freq) अणु
		u32 v, synth_पूर्णांक_भाग, synth_frac_भाग, synth_भाग_freq;

		v = पढ़ोl_relaxed(synth->freq);
		synth_पूर्णांक_भाग = (v >> 24) & 0xf;
		synth_frac_भाग = v & 0xffffff;
		synth_भाग_freq = (synth_पूर्णांक_भाग * 10000000) + synth_frac_भाग;
		rate *= 10000000;
		करो_भाग(rate, synth_भाग_freq);
		rate *= SYNTH_PHASE_K;
	पूर्ण

	/* Synth post-भागider M */
	synth_भाग_m = पढ़ोl_relaxed(synth->भाग) & SYNTH_MAX_DIV_M;

	वापस DIV_ROUND_UP_ULL(rate, synth_भाग_m);
पूर्ण

अटल अचिन्हित दीर्घ ti_fapll_synth_get_frac_rate(काष्ठा clk_hw *hw,
						  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा fapll_synth *synth = to_synth(hw);
	अचिन्हित दीर्घ current_rate, frac_rate;
	u32 post_भाग_m;

	current_rate = ti_fapll_synth_recalc_rate(hw, parent_rate);
	post_भाग_m = पढ़ोl_relaxed(synth->भाग) & SYNTH_MAX_DIV_M;
	frac_rate = current_rate * post_भाग_m;

	वापस frac_rate;
पूर्ण

अटल u32 ti_fapll_synth_set_frac_rate(काष्ठा fapll_synth *synth,
					अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ parent_rate)
अणु
	u32 post_भाग_m, synth_पूर्णांक_भाग = 0, synth_frac_भाग = 0, v;

	post_भाग_m = DIV_ROUND_UP_ULL((u64)parent_rate * SYNTH_PHASE_K, rate);
	post_भाग_m = post_भाग_m / SYNTH_MAX_INT_DIV;
	अगर (post_भाग_m > SYNTH_MAX_DIV_M)
		वापस -EINVAL;
	अगर (!post_भाग_m)
		post_भाग_m = 1;

	क्रम (; post_भाग_m < SYNTH_MAX_DIV_M; post_भाग_m++) अणु
		synth_पूर्णांक_भाग = DIV_ROUND_UP_ULL((u64)parent_rate *
						 SYNTH_PHASE_K *
						 10000000,
						 rate * post_भाग_m);
		synth_frac_भाग = synth_पूर्णांक_भाग % 10000000;
		synth_पूर्णांक_भाग /= 10000000;

		अगर (synth_पूर्णांक_भाग <= SYNTH_MAX_INT_DIV)
			अवरोध;
	पूर्ण

	अगर (synth_पूर्णांक_भाग > SYNTH_MAX_INT_DIV)
		वापस -EINVAL;

	v = पढ़ोl_relaxed(synth->freq);
	v &= ~0x1fffffff;
	v |= (synth_पूर्णांक_भाग & SYNTH_MAX_INT_DIV) << 24;
	v |= (synth_frac_भाग & 0xffffff);
	v |= SYNTH_LDFREQ;
	ग_लिखोl_relaxed(v, synth->freq);

	वापस post_भाग_m;
पूर्ण

अटल दीर्घ ti_fapll_synth_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				      अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा fapll_synth *synth = to_synth(hw);
	काष्ठा fapll_data *fd = synth->fd;
	अचिन्हित दीर्घ r;

	अगर (ti_fapll_घड़ी_is_bypass(fd) || !synth->भाग || !rate)
		वापस -EINVAL;

	/* Only post भागider m available with no fractional भागider? */
	अगर (!synth->freq) अणु
		अचिन्हित दीर्घ frac_rate;
		u32 synth_post_भाग_m;

		frac_rate = ti_fapll_synth_get_frac_rate(hw, *parent_rate);
		synth_post_भाग_m = DIV_ROUND_UP(frac_rate, rate);
		r = DIV_ROUND_UP(frac_rate, synth_post_भाग_m);
		जाओ out;
	पूर्ण

	r = *parent_rate * SYNTH_PHASE_K;
	अगर (rate > r)
		जाओ out;

	r = DIV_ROUND_UP_ULL(r, SYNTH_MAX_INT_DIV * SYNTH_MAX_DIV_M);
	अगर (rate < r)
		जाओ out;

	r = rate;
out:
	वापस r;
पूर्ण

अटल पूर्णांक ti_fapll_synth_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा fapll_synth *synth = to_synth(hw);
	काष्ठा fapll_data *fd = synth->fd;
	अचिन्हित दीर्घ frac_rate, post_rate = 0;
	u32 post_भाग_m = 0, v;

	अगर (ti_fapll_घड़ी_is_bypass(fd) || !synth->भाग || !rate)
		वापस -EINVAL;

	/* Produce the rate with just post भागider M? */
	frac_rate = ti_fapll_synth_get_frac_rate(hw, parent_rate);
	अगर (frac_rate < rate) अणु
		अगर (!synth->freq)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		post_भाग_m = DIV_ROUND_UP(frac_rate, rate);
		अगर (post_भाग_m && (post_भाग_m <= SYNTH_MAX_DIV_M))
			post_rate = DIV_ROUND_UP(frac_rate, post_भाग_m);
		अगर (!synth->freq && !post_rate)
			वापस -EINVAL;
	पूर्ण

	/* Need to recalculate the fractional भागider? */
	अगर ((post_rate != rate) && synth->freq)
		post_भाग_m = ti_fapll_synth_set_frac_rate(synth,
							  rate,
							  parent_rate);

	v = पढ़ोl_relaxed(synth->भाग);
	v &= ~SYNTH_MAX_DIV_M;
	v |= post_भाग_m;
	v |= SYNTH_LDMDIV1;
	ग_लिखोl_relaxed(v, synth->भाग);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops ti_fapll_synt_ops = अणु
	.enable = ti_fapll_synth_enable,
	.disable = ti_fapll_synth_disable,
	.is_enabled = ti_fapll_synth_is_enabled,
	.recalc_rate = ti_fapll_synth_recalc_rate,
	.round_rate = ti_fapll_synth_round_rate,
	.set_rate = ti_fapll_synth_set_rate,
पूर्ण;

अटल काष्ठा clk * __init ti_fapll_synth_setup(काष्ठा fapll_data *fd,
						व्योम __iomem *freq,
						व्योम __iomem *भाग,
						पूर्णांक index,
						स्थिर अक्षर *name,
						स्थिर अक्षर *parent,
						काष्ठा clk *pll_clk)
अणु
	काष्ठा clk_init_data *init;
	काष्ठा fapll_synth *synth;
	काष्ठा clk *clk = ERR_PTR(-ENOMEM);

	init = kzalloc(माप(*init), GFP_KERNEL);
	अगर (!init)
		वापस ERR_PTR(-ENOMEM);

	init->ops = &ti_fapll_synt_ops;
	init->name = name;
	init->parent_names = &parent;
	init->num_parents = 1;

	synth = kzalloc(माप(*synth), GFP_KERNEL);
	अगर (!synth)
		जाओ मुक्त;

	synth->fd = fd;
	synth->index = index;
	synth->freq = freq;
	synth->भाग = भाग;
	synth->name = name;
	synth->hw.init = init;
	synth->clk_pll = pll_clk;

	clk = clk_रेजिस्टर(शून्य, &synth->hw);
	अगर (IS_ERR(clk)) अणु
		pr_err("failed to register clock\n");
		जाओ मुक्त;
	पूर्ण

	वापस clk;

मुक्त:
	kमुक्त(synth);
	kमुक्त(init);

	वापस clk;
पूर्ण

अटल व्योम __init ti_fapll_setup(काष्ठा device_node *node)
अणु
	काष्ठा fapll_data *fd;
	काष्ठा clk_init_data *init = शून्य;
	स्थिर अक्षर *parent_name[2];
	काष्ठा clk *pll_clk;
	पूर्णांक i;

	fd = kzalloc(माप(*fd), GFP_KERNEL);
	अगर (!fd)
		वापस;

	fd->outमाला_दो.clks = kzalloc(माप(काष्ठा clk *) *
				   MAX_FAPLL_OUTPUTS + 1,
				   GFP_KERNEL);
	अगर (!fd->outमाला_दो.clks)
		जाओ मुक्त;

	init = kzalloc(माप(*init), GFP_KERNEL);
	अगर (!init)
		जाओ मुक्त;

	init->ops = &ti_fapll_ops;
	init->name = node->name;

	init->num_parents = of_clk_get_parent_count(node);
	अगर (init->num_parents != 2) अणु
		pr_err("%pOFn must have two parents\n", node);
		जाओ मुक्त;
	पूर्ण

	of_clk_parent_fill(node, parent_name, 2);
	init->parent_names = parent_name;

	fd->clk_ref = of_clk_get(node, 0);
	अगर (IS_ERR(fd->clk_ref)) अणु
		pr_err("%pOFn could not get clk_ref\n", node);
		जाओ मुक्त;
	पूर्ण

	fd->clk_bypass = of_clk_get(node, 1);
	अगर (IS_ERR(fd->clk_bypass)) अणु
		pr_err("%pOFn could not get clk_bypass\n", node);
		जाओ मुक्त;
	पूर्ण

	fd->base = of_iomap(node, 0);
	अगर (!fd->base) अणु
		pr_err("%pOFn could not get IO base\n", node);
		जाओ मुक्त;
	पूर्ण

	अगर (fapll_is_ddr_pll(fd->base))
		fd->bypass_bit_inverted = true;

	fd->name = node->name;
	fd->hw.init = init;

	/* Register the parent PLL */
	pll_clk = clk_रेजिस्टर(शून्य, &fd->hw);
	अगर (IS_ERR(pll_clk))
		जाओ unmap;

	fd->outमाला_दो.clks[0] = pll_clk;
	fd->outमाला_दो.clk_num++;

	/*
	 * Set up the child synthesizers starting at index 1 as the
	 * PLL output is at index 0. We need to check the घड़ी-indices
	 * क्रम numbering in हाल there are holes in the synth mapping,
	 * and then probe the synth रेजिस्टर to see अगर it has a FREQ
	 * रेजिस्टर available.
	 */
	क्रम (i = 0; i < MAX_FAPLL_OUTPUTS; i++) अणु
		स्थिर अक्षर *output_name;
		व्योम __iomem *freq, *भाग;
		काष्ठा clk *synth_clk;
		पूर्णांक output_instance;
		u32 v;

		अगर (of_property_पढ़ो_string_index(node, "clock-output-names",
						  i, &output_name))
			जारी;

		अगर (of_property_पढ़ो_u32_index(node, "clock-indices", i,
					       &output_instance))
			output_instance = i;

		freq = fd->base + (output_instance * 8);
		भाग = freq + 4;

		/* Check क्रम hardwired audio_pll_clk1 */
		अगर (is_audio_pll_clk1(freq)) अणु
			freq = शून्य;
			भाग = शून्य;
		पूर्ण अन्यथा अणु
			/* Does the synthesizer have a FREQ रेजिस्टर? */
			v = पढ़ोl_relaxed(freq);
			अगर (!v)
				freq = शून्य;
		पूर्ण
		synth_clk = ti_fapll_synth_setup(fd, freq, भाग, output_instance,
						 output_name, node->name,
						 pll_clk);
		अगर (IS_ERR(synth_clk))
			जारी;

		fd->outमाला_दो.clks[output_instance] = synth_clk;
		fd->outमाला_दो.clk_num++;

		clk_रेजिस्टर_clkdev(synth_clk, output_name, शून्य);
	पूर्ण

	/* Register the child synthesizers as the FAPLL outमाला_दो */
	of_clk_add_provider(node, of_clk_src_onecell_get, &fd->outमाला_दो);
	/* Add घड़ी alias क्रम the outमाला_दो */

	kमुक्त(init);

	वापस;

unmap:
	iounmap(fd->base);
मुक्त:
	अगर (fd->clk_bypass)
		clk_put(fd->clk_bypass);
	अगर (fd->clk_ref)
		clk_put(fd->clk_ref);
	kमुक्त(fd->outमाला_दो.clks);
	kमुक्त(fd);
	kमुक्त(init);
पूर्ण

CLK_OF_DECLARE(ti_fapll_घड़ी, "ti,dm816-fapll-clock", ti_fapll_setup);
