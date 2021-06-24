<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 STMicroelectronics R&D Ltd
 */

/*
 * Authors:
 * Stephen Gallimore <stephen.gallimore@st.com>,
 * Pankaj Dev <pankaj.dev@st.com>.
 */

#समावेश <linux/slab.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>

#समावेश "clkgen.h"

/*
 * Maximum input घड़ी to the PLL beक्रमe we भागide it करोwn by 2
 * although in reality in actual प्रणालीs this has never been seen to
 * be used.
 */
#घोषणा QUADFS_NDIV_THRESHOLD 30000000

#घोषणा PLL_BW_GOODREF   (0L)
#घोषणा PLL_BW_VBADREF   (1L)
#घोषणा PLL_BW_BADREF    (2L)
#घोषणा PLL_BW_VGOODREF  (3L)

#घोषणा QUADFS_MAX_CHAN 4

काष्ठा sपंचांग_fs अणु
	अचिन्हित दीर्घ nभाग;
	अचिन्हित दीर्घ mभाग;
	अचिन्हित दीर्घ pe;
	अचिन्हित दीर्घ sभाग;
	अचिन्हित दीर्घ nsभाग;
पूर्ण;

काष्ठा clkgen_quadfs_data अणु
	bool reset_present;
	bool bwfilter_present;
	bool lockstatus_present;
	bool घातerup_polarity;
	bool standby_polarity;
	bool nsभाग_present;
	bool nrst_present;
	काष्ठा clkgen_field nभाग;
	काष्ठा clkgen_field ref_bw;
	काष्ठा clkgen_field nreset;
	काष्ठा clkgen_field npda;
	काष्ठा clkgen_field lock_status;

	काष्ठा clkgen_field nrst[QUADFS_MAX_CHAN];
	काष्ठा clkgen_field nsb[QUADFS_MAX_CHAN];
	काष्ठा clkgen_field en[QUADFS_MAX_CHAN];
	काष्ठा clkgen_field mभाग[QUADFS_MAX_CHAN];
	काष्ठा clkgen_field pe[QUADFS_MAX_CHAN];
	काष्ठा clkgen_field sभाग[QUADFS_MAX_CHAN];
	काष्ठा clkgen_field nsभाग[QUADFS_MAX_CHAN];

	स्थिर काष्ठा clk_ops *pll_ops;
	पूर्णांक  (*get_params)(अचिन्हित दीर्घ, अचिन्हित दीर्घ, काष्ठा sपंचांग_fs *);
	पूर्णांक  (*get_rate)(अचिन्हित दीर्घ , स्थिर काष्ठा sपंचांग_fs *,
			अचिन्हित दीर्घ *);
पूर्ण;

अटल स्थिर काष्ठा clk_ops st_quadfs_pll_c32_ops;

अटल पूर्णांक clk_fs660c32_dig_get_params(अचिन्हित दीर्घ input,
		अचिन्हित दीर्घ output, काष्ठा sपंचांग_fs *fs);
अटल पूर्णांक clk_fs660c32_dig_get_rate(अचिन्हित दीर्घ, स्थिर काष्ठा sपंचांग_fs *,
		अचिन्हित दीर्घ *);

अटल स्थिर काष्ठा clkgen_quadfs_data st_fs660c32_C = अणु
	.nrst_present = true,
	.nrst	= अणु CLKGEN_FIELD(0x2f0, 0x1, 0),
		    CLKGEN_FIELD(0x2f0, 0x1, 1),
		    CLKGEN_FIELD(0x2f0, 0x1, 2),
		    CLKGEN_FIELD(0x2f0, 0x1, 3) पूर्ण,
	.npda	= CLKGEN_FIELD(0x2f0, 0x1, 12),
	.nsb	= अणु CLKGEN_FIELD(0x2f0, 0x1, 8),
		    CLKGEN_FIELD(0x2f0, 0x1, 9),
		    CLKGEN_FIELD(0x2f0, 0x1, 10),
		    CLKGEN_FIELD(0x2f0, 0x1, 11) पूर्ण,
	.nsभाग_present = true,
	.nsभाग	= अणु CLKGEN_FIELD(0x304, 0x1, 24),
		    CLKGEN_FIELD(0x308, 0x1, 24),
		    CLKGEN_FIELD(0x30c, 0x1, 24),
		    CLKGEN_FIELD(0x310, 0x1, 24) पूर्ण,
	.mभाग	= अणु CLKGEN_FIELD(0x304, 0x1f, 15),
		    CLKGEN_FIELD(0x308, 0x1f, 15),
		    CLKGEN_FIELD(0x30c, 0x1f, 15),
		    CLKGEN_FIELD(0x310, 0x1f, 15) पूर्ण,
	.en	= अणु CLKGEN_FIELD(0x2fc, 0x1, 0),
		    CLKGEN_FIELD(0x2fc, 0x1, 1),
		    CLKGEN_FIELD(0x2fc, 0x1, 2),
		    CLKGEN_FIELD(0x2fc, 0x1, 3) पूर्ण,
	.nभाग	= CLKGEN_FIELD(0x2f4, 0x7, 16),
	.pe	= अणु CLKGEN_FIELD(0x304, 0x7fff, 0),
		    CLKGEN_FIELD(0x308, 0x7fff, 0),
		    CLKGEN_FIELD(0x30c, 0x7fff, 0),
		    CLKGEN_FIELD(0x310, 0x7fff, 0) पूर्ण,
	.sभाग	= अणु CLKGEN_FIELD(0x304, 0xf, 20),
		    CLKGEN_FIELD(0x308, 0xf, 20),
		    CLKGEN_FIELD(0x30c, 0xf, 20),
		    CLKGEN_FIELD(0x310, 0xf, 20) पूर्ण,
	.lockstatus_present = true,
	.lock_status = CLKGEN_FIELD(0x2f0, 0x1, 24),
	.घातerup_polarity = 1,
	.standby_polarity = 1,
	.pll_ops	= &st_quadfs_pll_c32_ops,
	.get_params	= clk_fs660c32_dig_get_params,
	.get_rate	= clk_fs660c32_dig_get_rate,
पूर्ण;

अटल स्थिर काष्ठा clkgen_quadfs_data st_fs660c32_D = अणु
	.nrst_present = true,
	.nrst	= अणु CLKGEN_FIELD(0x2a0, 0x1, 0),
		    CLKGEN_FIELD(0x2a0, 0x1, 1),
		    CLKGEN_FIELD(0x2a0, 0x1, 2),
		    CLKGEN_FIELD(0x2a0, 0x1, 3) पूर्ण,
	.nभाग	= CLKGEN_FIELD(0x2a4, 0x7, 16),
	.pe	= अणु CLKGEN_FIELD(0x2b4, 0x7fff, 0),
		    CLKGEN_FIELD(0x2b8, 0x7fff, 0),
		    CLKGEN_FIELD(0x2bc, 0x7fff, 0),
		    CLKGEN_FIELD(0x2c0, 0x7fff, 0) पूर्ण,
	.sभाग	= अणु CLKGEN_FIELD(0x2b4, 0xf, 20),
		    CLKGEN_FIELD(0x2b8, 0xf, 20),
		    CLKGEN_FIELD(0x2bc, 0xf, 20),
		    CLKGEN_FIELD(0x2c0, 0xf, 20) पूर्ण,
	.npda	= CLKGEN_FIELD(0x2a0, 0x1, 12),
	.nsb	= अणु CLKGEN_FIELD(0x2a0, 0x1, 8),
		    CLKGEN_FIELD(0x2a0, 0x1, 9),
		    CLKGEN_FIELD(0x2a0, 0x1, 10),
		    CLKGEN_FIELD(0x2a0, 0x1, 11) पूर्ण,
	.nsभाग_present = true,
	.nsभाग	= अणु CLKGEN_FIELD(0x2b4, 0x1, 24),
		    CLKGEN_FIELD(0x2b8, 0x1, 24),
		    CLKGEN_FIELD(0x2bc, 0x1, 24),
		    CLKGEN_FIELD(0x2c0, 0x1, 24) पूर्ण,
	.mभाग	= अणु CLKGEN_FIELD(0x2b4, 0x1f, 15),
		    CLKGEN_FIELD(0x2b8, 0x1f, 15),
		    CLKGEN_FIELD(0x2bc, 0x1f, 15),
		    CLKGEN_FIELD(0x2c0, 0x1f, 15) पूर्ण,
	.en	= अणु CLKGEN_FIELD(0x2ac, 0x1, 0),
		    CLKGEN_FIELD(0x2ac, 0x1, 1),
		    CLKGEN_FIELD(0x2ac, 0x1, 2),
		    CLKGEN_FIELD(0x2ac, 0x1, 3) पूर्ण,
	.lockstatus_present = true,
	.lock_status = CLKGEN_FIELD(0x2A0, 0x1, 24),
	.घातerup_polarity = 1,
	.standby_polarity = 1,
	.pll_ops	= &st_quadfs_pll_c32_ops,
	.get_params	= clk_fs660c32_dig_get_params,
	.get_rate	= clk_fs660c32_dig_get_rate,पूर्ण;

/**
 * DOC: A Frequency Synthesizer that multiples its input घड़ी by a fixed factor
 *
 * Traits of this घड़ी:
 * prepare - clk_(un)prepare only ensures parent is (un)prepared
 * enable - clk_enable and clk_disable are functional & control the Fsyn
 * rate - inherits rate from parent. set_rate/round_rate/recalc_rate
 * parent - fixed parent.  No clk_set_parent support
 */

/**
 * काष्ठा st_clk_quadfs_pll - A pll which outमाला_दो a fixed multiplier of
 *                                  its parent घड़ी, found inside a type of
 *                                  ST quad channel frequency synthesizer block
 *
 * @hw: handle between common and hardware-specअगरic पूर्णांकerfaces.
 * @regs_base: base address of the configuration रेजिस्टरs.
 * @lock: spinlock.
 * @data: local driver data
 * @nभाग: regmap field क्रम the nभाग control.
 */
काष्ठा st_clk_quadfs_pll अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*regs_base;
	spinlock_t	*lock;
	काष्ठा clkgen_quadfs_data *data;
	u32 nभाग;
पूर्ण;

#घोषणा to_quadfs_pll(_hw) container_of(_hw, काष्ठा st_clk_quadfs_pll, hw)

अटल पूर्णांक quadfs_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा st_clk_quadfs_pll *pll = to_quadfs_pll(hw);
	अचिन्हित दीर्घ flags = 0, समयout = jअगरfies + msecs_to_jअगरfies(10);

	अगर (pll->lock)
		spin_lock_irqsave(pll->lock, flags);

	/*
	 * Bring block out of reset अगर we have reset control.
	 */
	अगर (pll->data->reset_present)
		CLKGEN_WRITE(pll, nreset, 1);

	/*
	 * Use a fixed input घड़ी noise bandwidth filter क्रम the moment
	 */
	अगर (pll->data->bwfilter_present)
		CLKGEN_WRITE(pll, ref_bw, PLL_BW_GOODREF);


	CLKGEN_WRITE(pll, nभाग, pll->nभाग);

	/*
	 * Power up the PLL
	 */
	CLKGEN_WRITE(pll, npda, !pll->data->घातerup_polarity);

	अगर (pll->lock)
		spin_unlock_irqrestore(pll->lock, flags);

	अगर (pll->data->lockstatus_present)
		जबतक (!CLKGEN_READ(pll, lock_status)) अणु
			अगर (समय_after(jअगरfies, समयout))
				वापस -ETIMEDOUT;
			cpu_relax();
		पूर्ण

	वापस 0;
पूर्ण

अटल व्योम quadfs_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा st_clk_quadfs_pll *pll = to_quadfs_pll(hw);
	अचिन्हित दीर्घ flags = 0;

	अगर (pll->lock)
		spin_lock_irqsave(pll->lock, flags);

	/*
	 * Powerकरोwn the PLL and then put block पूर्णांकo soft reset अगर we have
	 * reset control.
	 */
	CLKGEN_WRITE(pll, npda, pll->data->घातerup_polarity);

	अगर (pll->data->reset_present)
		CLKGEN_WRITE(pll, nreset, 0);

	अगर (pll->lock)
		spin_unlock_irqrestore(pll->lock, flags);
पूर्ण

अटल पूर्णांक quadfs_pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा st_clk_quadfs_pll *pll = to_quadfs_pll(hw);
	u32 npda = CLKGEN_READ(pll, npda);

	वापस pll->data->घातerup_polarity ? !npda : !!npda;
पूर्ण

अटल पूर्णांक clk_fs660c32_vco_get_rate(अचिन्हित दीर्घ input, काष्ठा sपंचांग_fs *fs,
			   अचिन्हित दीर्घ *rate)
अणु
	अचिन्हित दीर्घ nd = fs->nभाग + 16; /* nभाग value */

	*rate = input * nd;

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ quadfs_pll_fs660c32_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा st_clk_quadfs_pll *pll = to_quadfs_pll(hw);
	अचिन्हित दीर्घ rate = 0;
	काष्ठा sपंचांग_fs params;

	params.nभाग = CLKGEN_READ(pll, nभाग);
	अगर (clk_fs660c32_vco_get_rate(parent_rate, &params, &rate))
		pr_err("%s:%s error calculating rate\n",
		       clk_hw_get_name(hw), __func__);

	pll->nभाग = params.nभाग;

	वापस rate;
पूर्ण

अटल पूर्णांक clk_fs660c32_vco_get_params(अचिन्हित दीर्घ input,
				अचिन्हित दीर्घ output, काष्ठा sपंचांग_fs *fs)
अणु
/* Formula
   VCO frequency = (fin x nभाग) / pभाग
   nभाग = VCOfreq * pभाग / fin
   */
	अचिन्हित दीर्घ pभाग = 1, n;

	/* Output घड़ी range: 384Mhz to 660Mhz */
	अगर (output < 384000000 || output > 660000000)
		वापस -EINVAL;

	अगर (input > 40000000)
		/* This means that PDIV would be 2 instead of 1.
		   Not supported today. */
		वापस -EINVAL;

	input /= 1000;
	output /= 1000;

	n = output * pभाग / input;
	अगर (n < 16)
		n = 16;
	fs->nभाग = n - 16; /* Converting क्रमmula value to reg value */

	वापस 0;
पूर्ण

अटल दीर्घ quadfs_pll_fs660c32_round_rate(काष्ठा clk_hw *hw,
					   अचिन्हित दीर्घ rate,
					   अचिन्हित दीर्घ *prate)
अणु
	काष्ठा sपंचांग_fs params;

	अगर (clk_fs660c32_vco_get_params(*prate, rate, &params))
		वापस rate;

	clk_fs660c32_vco_get_rate(*prate, &params, &rate);

	pr_debug("%s: %s new rate %ld [ndiv=%u]\n",
		 __func__, clk_hw_get_name(hw),
		 rate, (अचिन्हित पूर्णांक)params.nभाग);

	वापस rate;
पूर्ण

अटल पूर्णांक quadfs_pll_fs660c32_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा st_clk_quadfs_pll *pll = to_quadfs_pll(hw);
	काष्ठा sपंचांग_fs params;
	दीर्घ hwrate = 0;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret;

	अगर (!rate || !parent_rate)
		वापस -EINVAL;

	ret = clk_fs660c32_vco_get_params(parent_rate, rate, &params);
	अगर (ret)
		वापस ret;

	clk_fs660c32_vco_get_rate(parent_rate, &params, &hwrate);

	pr_debug("%s: %s new rate %ld [ndiv=0x%x]\n",
		 __func__, clk_hw_get_name(hw),
		 hwrate, (अचिन्हित पूर्णांक)params.nभाग);

	अगर (!hwrate)
		वापस -EINVAL;

	pll->nभाग = params.nभाग;

	अगर (pll->lock)
		spin_lock_irqsave(pll->lock, flags);

	CLKGEN_WRITE(pll, nभाग, pll->nभाग);

	अगर (pll->lock)
		spin_unlock_irqrestore(pll->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops st_quadfs_pll_c32_ops = अणु
	.enable		= quadfs_pll_enable,
	.disable	= quadfs_pll_disable,
	.is_enabled	= quadfs_pll_is_enabled,
	.recalc_rate	= quadfs_pll_fs660c32_recalc_rate,
	.round_rate	= quadfs_pll_fs660c32_round_rate,
	.set_rate	= quadfs_pll_fs660c32_set_rate,
पूर्ण;

अटल काष्ठा clk * __init st_clk_रेजिस्टर_quadfs_pll(
		स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		काष्ठा clkgen_quadfs_data *quadfs, व्योम __iomem *reg,
		spinlock_t *lock)
अणु
	काष्ठा st_clk_quadfs_pll *pll;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;

	/*
	 * Sanity check required poपूर्णांकers.
	 */
	अगर (WARN_ON(!name || !parent_name))
		वापस ERR_PTR(-EINVAL);

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = quadfs->pll_ops;
	init.flags = CLK_GET_RATE_NOCACHE;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	pll->data = quadfs;
	pll->regs_base = reg;
	pll->lock = lock;
	pll->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &pll->hw);

	अगर (IS_ERR(clk))
		kमुक्त(pll);

	वापस clk;
पूर्ण

/**
 * DOC: A digital frequency synthesizer
 *
 * Traits of this घड़ी:
 * prepare - clk_(un)prepare only ensures parent is (un)prepared
 * enable - clk_enable and clk_disable are functional
 * rate - set rate is functional
 * parent - fixed parent.  No clk_set_parent support
 */

/*
 * काष्ठा st_clk_quadfs_fsynth - One घड़ी output from a four channel digital
 *                                  frequency synthesizer (fsynth) block.
 *
 * @hw: handle between common and hardware-specअगरic पूर्णांकerfaces
 *
 * @nsb: regmap field in the output control रेजिस्टर क्रम the digital
 *       standby of this fsynth channel. This control is active low so
 *       the channel is in standby when the control bit is cleared.
 *
 * @nsभाग: regmap field in the output control रेजिस्टर क्रम
 *          क्रम the optional भागide by 3 of this fsynth channel. This control
 *          is active low so the भागide by 3 is active when the control bit is
 *          cleared and the भागide is bypassed when the bit is set.
 */
काष्ठा st_clk_quadfs_fsynth अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*regs_base;
	spinlock_t	*lock;
	काष्ठा clkgen_quadfs_data *data;

	u32 chan;
	/*
	 * Cached hardware values from set_rate so we can program the
	 * hardware in enable. There are two reasons क्रम this:
	 *
	 *  1. The रेजिस्टरs may not be writable until the parent has been
	 *     enabled.
	 *
	 *  2. It restores the घड़ी rate when a driver करोes an enable
	 *     on PM restore, after a suspend to RAM has lost the hardware
	 *     setup.
	 */
	u32 md;
	u32 pe;
	u32 sभाग;
	u32 nsभाग;
पूर्ण;

#घोषणा to_quadfs_fsynth(_hw) \
	container_of(_hw, काष्ठा st_clk_quadfs_fsynth, hw)

अटल व्योम quadfs_fsynth_program_enable(काष्ठा st_clk_quadfs_fsynth *fs)
अणु
	/*
	 * Pulse the program enable रेजिस्टर lsb to make the hardware take
	 * notice of the new md/pe values with a glitchless transition.
	 */
	CLKGEN_WRITE(fs, en[fs->chan], 1);
	CLKGEN_WRITE(fs, en[fs->chan], 0);
पूर्ण

अटल व्योम quadfs_fsynth_program_rate(काष्ठा st_clk_quadfs_fsynth *fs)
अणु
	अचिन्हित दीर्घ flags = 0;

	/*
	 * Ensure the md/pe parameters are ignored जबतक we are
	 * reprogramming them so we can get a glitchless change
	 * when fine tuning the speed of a running घड़ी.
	 */
	CLKGEN_WRITE(fs, en[fs->chan], 0);

	CLKGEN_WRITE(fs, mभाग[fs->chan], fs->md);
	CLKGEN_WRITE(fs, pe[fs->chan], fs->pe);
	CLKGEN_WRITE(fs, sभाग[fs->chan], fs->sभाग);

	अगर (fs->lock)
		spin_lock_irqsave(fs->lock, flags);

	अगर (fs->data->nsभाग_present)
		CLKGEN_WRITE(fs, nsभाग[fs->chan], fs->nsभाग);

	अगर (fs->lock)
		spin_unlock_irqrestore(fs->lock, flags);
पूर्ण

अटल पूर्णांक quadfs_fsynth_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा st_clk_quadfs_fsynth *fs = to_quadfs_fsynth(hw);
	अचिन्हित दीर्घ flags = 0;

	pr_debug("%s: %s\n", __func__, clk_hw_get_name(hw));

	quadfs_fsynth_program_rate(fs);

	अगर (fs->lock)
		spin_lock_irqsave(fs->lock, flags);

	CLKGEN_WRITE(fs, nsb[fs->chan], !fs->data->standby_polarity);

	अगर (fs->data->nrst_present)
		CLKGEN_WRITE(fs, nrst[fs->chan], 0);

	अगर (fs->lock)
		spin_unlock_irqrestore(fs->lock, flags);

	quadfs_fsynth_program_enable(fs);

	वापस 0;
पूर्ण

अटल व्योम quadfs_fsynth_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा st_clk_quadfs_fsynth *fs = to_quadfs_fsynth(hw);
	अचिन्हित दीर्घ flags = 0;

	pr_debug("%s: %s\n", __func__, clk_hw_get_name(hw));

	अगर (fs->lock)
		spin_lock_irqsave(fs->lock, flags);

	CLKGEN_WRITE(fs, nsb[fs->chan], fs->data->standby_polarity);

	अगर (fs->lock)
		spin_unlock_irqrestore(fs->lock, flags);
पूर्ण

अटल पूर्णांक quadfs_fsynth_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा st_clk_quadfs_fsynth *fs = to_quadfs_fsynth(hw);
	u32 nsb = CLKGEN_READ(fs, nsb[fs->chan]);

	pr_debug("%s: %s enable bit = 0x%x\n",
		 __func__, clk_hw_get_name(hw), nsb);

	वापस fs->data->standby_polarity ? !nsb : !!nsb;
पूर्ण

#घोषणा P20		(uपूर्णांक64_t)(1 << 20)

अटल पूर्णांक clk_fs660c32_dig_get_rate(अचिन्हित दीर्घ input,
				स्थिर काष्ठा sपंचांग_fs *fs, अचिन्हित दीर्घ *rate)
अणु
	अचिन्हित दीर्घ s = (1 << fs->sभाग);
	अचिन्हित दीर्घ ns;
	uपूर्णांक64_t res;

	/*
	 * 'nsdiv' is a register value ('BIN') which is translated
	 * to a decimal value according to following rules.
	 *
	 *     nsभाग      ns.dec
	 *       0        3
	 *       1        1
	 */
	ns = (fs->nsभाग == 1) ? 1 : 3;

	res = (P20 * (32 + fs->mभाग) + 32 * fs->pe) * s * ns;
	*rate = (अचिन्हित दीर्घ)भाग64_u64(input * P20 * 32, res);

	वापस 0;
पूर्ण


अटल पूर्णांक clk_fs660c32_get_pe(पूर्णांक m, पूर्णांक si, अचिन्हित दीर्घ *deviation,
		चिन्हित दीर्घ input, अचिन्हित दीर्घ output, uपूर्णांक64_t *p,
		काष्ठा sपंचांग_fs *fs)
अणु
	अचिन्हित दीर्घ new_freq, new_deviation;
	काष्ठा sपंचांग_fs fs_पंचांगp;
	uपूर्णांक64_t val;

	val = (uपूर्णांक64_t)output << si;

	*p = (uपूर्णांक64_t)input * P20 - (32LL  + (uपूर्णांक64_t)m) * val * (P20 / 32LL);

	*p = भाग64_u64(*p, val);

	अगर (*p > 32767LL)
		वापस 1;

	fs_पंचांगp.mभाग = (अचिन्हित दीर्घ) m;
	fs_पंचांगp.pe = (अचिन्हित दीर्घ)*p;
	fs_पंचांगp.sभाग = si;
	fs_पंचांगp.nsभाग = 1;

	clk_fs660c32_dig_get_rate(input, &fs_पंचांगp, &new_freq);

	new_deviation = असल(output - new_freq);

	अगर (new_deviation < *deviation) अणु
		fs->mभाग = m;
		fs->pe = (अचिन्हित दीर्घ)*p;
		fs->sभाग = si;
		fs->nsभाग = 1;
		*deviation = new_deviation;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक clk_fs660c32_dig_get_params(अचिन्हित दीर्घ input,
		अचिन्हित दीर्घ output, काष्ठा sपंचांग_fs *fs)
अणु
	पूर्णांक si;	/* sभाग_reg (8 करोwnto 0) */
	पूर्णांक m; /* md value */
	अचिन्हित दीर्घ new_freq, new_deviation;
	/* initial condition to say: "infinite deviation" */
	अचिन्हित दीर्घ deviation = ~0;
	uपूर्णांक64_t p, p1, p2;	/* pe value */
	पूर्णांक r1, r2;

	काष्ठा sपंचांग_fs fs_पंचांगp;

	क्रम (si = 0; (si <= 8) && deviation; si++) अणु

		/* Boundary test to aव्योम useless iteration */
		r1 = clk_fs660c32_get_pe(0, si, &deviation,
				input, output, &p1, fs);
		r2 = clk_fs660c32_get_pe(31, si, &deviation,
				input, output, &p2, fs);

		/* No solution */
		अगर (r1 && r2 && (p1 > p2))
			जारी;

		/* Try to find best deviation */
		क्रम (m = 1; (m < 31) && deviation; m++)
			clk_fs660c32_get_pe(m, si, &deviation,
					input, output, &p, fs);

	पूर्ण

	अगर (deviation == ~0) /* No solution found */
		वापस -1;

	/* pe fine tuning अगर deviation not 0: +/- 2 around computed pe value */
	अगर (deviation) अणु
		fs_पंचांगp.mभाग = fs->mभाग;
		fs_पंचांगp.sभाग = fs->sभाग;
		fs_पंचांगp.nsभाग = fs->nsभाग;

		अगर (fs->pe > 2)
			p2 = fs->pe - 2;
		अन्यथा
			p2 = 0;

		क्रम (; p2 < 32768ll && (p2 <= (fs->pe + 2)); p2++) अणु
			fs_पंचांगp.pe = (अचिन्हित दीर्घ)p2;

			clk_fs660c32_dig_get_rate(input, &fs_पंचांगp, &new_freq);

			new_deviation = असल(output - new_freq);

			/* Check अगर this is a better solution */
			अगर (new_deviation < deviation) अणु
				fs->pe = (अचिन्हित दीर्घ)p2;
				deviation = new_deviation;

			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक quadfs_fsynt_get_hw_value_क्रम_recalc(काष्ठा st_clk_quadfs_fsynth *fs,
		काष्ठा sपंचांग_fs *params)
अणु
	/*
	 * Get the initial hardware values क्रम recalc_rate
	 */
	params->mभाग	= CLKGEN_READ(fs, mभाग[fs->chan]);
	params->pe	= CLKGEN_READ(fs, pe[fs->chan]);
	params->sभाग	= CLKGEN_READ(fs, sभाग[fs->chan]);

	अगर (fs->data->nsभाग_present)
		params->nsभाग = CLKGEN_READ(fs, nsभाग[fs->chan]);
	अन्यथा
		params->nsभाग = 1;

	/*
	 * If All are शून्य then assume no घड़ी rate is programmed.
	 */
	अगर (!params->mभाग && !params->pe && !params->sभाग)
		वापस 1;

	fs->md = params->mभाग;
	fs->pe = params->pe;
	fs->sभाग = params->sभाग;
	fs->nsभाग = params->nsभाग;

	वापस 0;
पूर्ण

अटल दीर्घ quadfs_find_best_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
				अचिन्हित दीर्घ prate, काष्ठा sपंचांग_fs *params)
अणु
	काष्ठा st_clk_quadfs_fsynth *fs = to_quadfs_fsynth(hw);
	पूर्णांक (*clk_fs_get_rate)(अचिन्हित दीर्घ ,
				स्थिर काष्ठा sपंचांग_fs *, अचिन्हित दीर्घ *);
	पूर्णांक (*clk_fs_get_params)(अचिन्हित दीर्घ, अचिन्हित दीर्घ, काष्ठा sपंचांग_fs *);
	अचिन्हित दीर्घ rate = 0;

	clk_fs_get_rate = fs->data->get_rate;
	clk_fs_get_params = fs->data->get_params;

	अगर (!clk_fs_get_params(prate, drate, params))
		clk_fs_get_rate(prate, params, &rate);

	वापस rate;
पूर्ण

अटल अचिन्हित दीर्घ quadfs_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा st_clk_quadfs_fsynth *fs = to_quadfs_fsynth(hw);
	अचिन्हित दीर्घ rate = 0;
	काष्ठा sपंचांग_fs params;
	पूर्णांक (*clk_fs_get_rate)(अचिन्हित दीर्घ ,
				स्थिर काष्ठा sपंचांग_fs *, अचिन्हित दीर्घ *);

	clk_fs_get_rate = fs->data->get_rate;

	अगर (quadfs_fsynt_get_hw_value_क्रम_recalc(fs, &params))
		वापस 0;

	अगर (clk_fs_get_rate(parent_rate, &params, &rate)) अणु
		pr_err("%s:%s error calculating rate\n",
		       clk_hw_get_name(hw), __func__);
	पूर्ण

	pr_debug("%s:%s rate %lu\n", clk_hw_get_name(hw), __func__, rate);

	वापस rate;
पूर्ण

अटल दीर्घ quadfs_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ *prate)
अणु
	काष्ठा sपंचांग_fs params;

	rate = quadfs_find_best_rate(hw, rate, *prate, &params);

	pr_debug("%s: %s new rate %ld [sdiv=0x%x,md=0x%x,pe=0x%x,nsdiv3=%u]\n",
		 __func__, clk_hw_get_name(hw),
		 rate, (अचिन्हित पूर्णांक)params.sभाग, (अचिन्हित पूर्णांक)params.mभाग,
			 (अचिन्हित पूर्णांक)params.pe, (अचिन्हित पूर्णांक)params.nsभाग);

	वापस rate;
पूर्ण


अटल व्योम quadfs_program_and_enable(काष्ठा st_clk_quadfs_fsynth *fs,
		काष्ठा sपंचांग_fs *params)
अणु
	fs->md = params->mभाग;
	fs->pe = params->pe;
	fs->sभाग = params->sभाग;
	fs->nsभाग = params->nsभाग;

	/*
	 * In some पूर्णांकegrations you can only change the fsynth programming when
	 * the parent entity containing it is enabled.
	 */
	quadfs_fsynth_program_rate(fs);
	quadfs_fsynth_program_enable(fs);
पूर्ण

अटल पूर्णांक quadfs_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा st_clk_quadfs_fsynth *fs = to_quadfs_fsynth(hw);
	काष्ठा sपंचांग_fs params;
	दीर्घ hwrate;

	अगर (!rate || !parent_rate)
		वापस -EINVAL;

	स_रखो(&params, 0, माप(काष्ठा sपंचांग_fs));

	hwrate = quadfs_find_best_rate(hw, rate, parent_rate, &params);
	अगर (!hwrate)
		वापस -EINVAL;

	quadfs_program_and_enable(fs, &params);

	वापस 0;
पूर्ण



अटल स्थिर काष्ठा clk_ops st_quadfs_ops = अणु
	.enable		= quadfs_fsynth_enable,
	.disable	= quadfs_fsynth_disable,
	.is_enabled	= quadfs_fsynth_is_enabled,
	.round_rate	= quadfs_round_rate,
	.set_rate	= quadfs_set_rate,
	.recalc_rate	= quadfs_recalc_rate,
पूर्ण;

अटल काष्ठा clk * __init st_clk_रेजिस्टर_quadfs_fsynth(
		स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		काष्ठा clkgen_quadfs_data *quadfs, व्योम __iomem *reg, u32 chan,
		अचिन्हित दीर्घ flags, spinlock_t *lock)
अणु
	काष्ठा st_clk_quadfs_fsynth *fs;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;

	/*
	 * Sanity check required poपूर्णांकers, note that nsभाग3 is optional.
	 */
	अगर (WARN_ON(!name || !parent_name))
		वापस ERR_PTR(-EINVAL);

	fs = kzalloc(माप(*fs), GFP_KERNEL);
	अगर (!fs)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &st_quadfs_ops;
	init.flags = flags | CLK_GET_RATE_NOCACHE;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	fs->data = quadfs;
	fs->regs_base = reg;
	fs->chan = chan;
	fs->lock = lock;
	fs->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &fs->hw);

	अगर (IS_ERR(clk))
		kमुक्त(fs);

	वापस clk;
पूर्ण

अटल व्योम __init st_of_create_quadfs_fsynths(
		काष्ठा device_node *np, स्थिर अक्षर *pll_name,
		काष्ठा clkgen_quadfs_data *quadfs, व्योम __iomem *reg,
		spinlock_t *lock)
अणु
	काष्ठा clk_onecell_data *clk_data;
	पूर्णांक fschan;

	clk_data = kzalloc(माप(*clk_data), GFP_KERNEL);
	अगर (!clk_data)
		वापस;

	clk_data->clk_num = QUADFS_MAX_CHAN;
	clk_data->clks = kसुस्मृति(QUADFS_MAX_CHAN, माप(काष्ठा clk *),
				 GFP_KERNEL);

	अगर (!clk_data->clks) अणु
		kमुक्त(clk_data);
		वापस;
	पूर्ण

	क्रम (fschan = 0; fschan < QUADFS_MAX_CHAN; fschan++) अणु
		काष्ठा clk *clk;
		स्थिर अक्षर *clk_name;
		अचिन्हित दीर्घ flags = 0;

		अगर (of_property_पढ़ो_string_index(np, "clock-output-names",
						  fschan, &clk_name)) अणु
			अवरोध;
		पूर्ण

		/*
		 * If we पढ़ो an empty घड़ी name then the channel is unused
		 */
		अगर (*clk_name == '\0')
			जारी;

		of_clk_detect_critical(np, fschan, &flags);

		clk = st_clk_रेजिस्टर_quadfs_fsynth(clk_name, pll_name,
						    quadfs, reg, fschan,
						    flags, lock);

		/*
		 * If there was an error रेजिस्टरing this घड़ी output, clean
		 * up and move on to the next one.
		 */
		अगर (!IS_ERR(clk)) अणु
			clk_data->clks[fschan] = clk;
			pr_debug("%s: parent %s rate %u\n",
				__clk_get_name(clk),
				__clk_get_name(clk_get_parent(clk)),
				(अचिन्हित पूर्णांक)clk_get_rate(clk));
		पूर्ण
	पूर्ण

	of_clk_add_provider(np, of_clk_src_onecell_get, clk_data);
पूर्ण

अटल व्योम __init st_of_quadfs_setup(काष्ठा device_node *np,
		काष्ठा clkgen_quadfs_data *data)
अणु
	काष्ठा clk *clk;
	स्थिर अक्षर *pll_name, *clk_parent_name;
	व्योम __iomem *reg;
	spinlock_t *lock;

	reg = of_iomap(np, 0);
	अगर (!reg)
		वापस;

	clk_parent_name = of_clk_get_parent_name(np, 0);
	अगर (!clk_parent_name)
		वापस;

	pll_name = kaप्र_लिखो(GFP_KERNEL, "%pOFn.pll", np);
	अगर (!pll_name)
		वापस;

	lock = kzalloc(माप(*lock), GFP_KERNEL);
	अगर (!lock)
		जाओ err_निकास;

	spin_lock_init(lock);

	clk = st_clk_रेजिस्टर_quadfs_pll(pll_name, clk_parent_name, data,
			reg, lock);
	अगर (IS_ERR(clk))
		जाओ err_निकास;
	अन्यथा
		pr_debug("%s: parent %s rate %u\n",
			__clk_get_name(clk),
			__clk_get_name(clk_get_parent(clk)),
			(अचिन्हित पूर्णांक)clk_get_rate(clk));

	st_of_create_quadfs_fsynths(np, pll_name, data, reg, lock);

err_निकास:
	kमुक्त(pll_name); /* No दीर्घer need local copy of the PLL name */
पूर्ण

अटल व्योम __init st_of_quadfs660C_setup(काष्ठा device_node *np)
अणु
	st_of_quadfs_setup(np, (काष्ठा clkgen_quadfs_data *) &st_fs660c32_C);
पूर्ण
CLK_OF_DECLARE(quadfs660C, "st,quadfs-pll", st_of_quadfs660C_setup);

अटल व्योम __init st_of_quadfs660D_setup(काष्ठा device_node *np)
अणु
	st_of_quadfs_setup(np, (काष्ठा clkgen_quadfs_data *) &st_fs660c32_D);
पूर्ण
CLK_OF_DECLARE(quadfs660D, "st,quadfs", st_of_quadfs660D_setup);
