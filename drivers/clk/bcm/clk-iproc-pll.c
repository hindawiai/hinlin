<शैली गुरु>
/*
 * Copyright (C) 2014 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/of_address.h>
#समावेश <linux/delay.h>

#समावेश "clk-iproc.h"

#घोषणा PLL_VCO_HIGH_SHIFT 19
#घोषणा PLL_VCO_LOW_SHIFT  30

/*
 * PLL MACRO_SELECT modes 0 to 5 choose pre-calculated PLL output frequencies
 * from a look-up table. Mode 7 allows user to manipulate PLL घड़ी भागiders
 */
#घोषणा PLL_USER_MODE 7

/* number of delay loops रुकोing क्रम PLL to lock */
#घोषणा LOCK_DELAY 100

/* number of VCO frequency bands */
#घोषणा NUM_FREQ_BANDS 8

#घोषणा NUM_KP_BANDS 3
क्रमागत kp_band अणु
	KP_BAND_MID = 0,
	KP_BAND_HIGH,
	KP_BAND_HIGH_HIGH
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक kp_table[NUM_KP_BANDS][NUM_FREQ_BANDS] = अणु
	अणु 5, 6, 6, 7, 7, 8, 9, 10 पूर्ण,
	अणु 4, 4, 5, 5, 6, 7, 8, 9  पूर्ण,
	अणु 4, 5, 5, 6, 7, 8, 9, 10 पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ ref_freq_table[NUM_FREQ_BANDS][2] = अणु
	अणु 10000000,  12500000  पूर्ण,
	अणु 12500000,  15000000  पूर्ण,
	अणु 15000000,  20000000  पूर्ण,
	अणु 20000000,  25000000  पूर्ण,
	अणु 25000000,  50000000  पूर्ण,
	अणु 50000000,  75000000  पूर्ण,
	अणु 75000000,  100000000 पूर्ण,
	अणु 100000000, 125000000 पूर्ण,
पूर्ण;

क्रमागत vco_freq_range अणु
	VCO_LOW       = 700000000U,
	VCO_MID       = 1200000000U,
	VCO_HIGH      = 2200000000U,
	VCO_HIGH_HIGH = 3100000000U,
	VCO_MAX       = 4000000000U,
पूर्ण;

काष्ठा iproc_pll अणु
	व्योम __iomem *status_base;
	व्योम __iomem *control_base;
	व्योम __iomem *pwr_base;
	व्योम __iomem *asiu_base;

	स्थिर काष्ठा iproc_pll_ctrl *ctrl;
	स्थिर काष्ठा iproc_pll_vco_param *vco_param;
	अचिन्हित पूर्णांक num_vco_entries;
पूर्ण;

काष्ठा iproc_clk अणु
	काष्ठा clk_hw hw;
	काष्ठा iproc_pll *pll;
	स्थिर काष्ठा iproc_clk_ctrl *ctrl;
पूर्ण;

#घोषणा to_iproc_clk(hw) container_of(hw, काष्ठा iproc_clk, hw)

अटल पूर्णांक pll_calc_param(अचिन्हित दीर्घ target_rate,
			अचिन्हित दीर्घ parent_rate,
			काष्ठा iproc_pll_vco_param *vco_out)
अणु
	u64 nभाग_पूर्णांक, nभाग_frac, residual;

	nभाग_पूर्णांक = target_rate / parent_rate;

	अगर (!nभाग_पूर्णांक || (nभाग_पूर्णांक > 255))
		वापस -EINVAL;

	residual = target_rate - (nभाग_पूर्णांक * parent_rate);
	residual <<= 20;

	/*
	 * Add half of the भागisor so the result will be rounded to बंदst
	 * instead of rounded करोwn.
	 */
	residual += (parent_rate / 2);
	nभाग_frac = भाग64_u64((u64)residual, (u64)parent_rate);

	vco_out->nभाग_पूर्णांक = nभाग_पूर्णांक;
	vco_out->nभाग_frac = nभाग_frac;
	vco_out->pभाग = 1;

	vco_out->rate = vco_out->nभाग_पूर्णांक * parent_rate;
	residual = (u64)vco_out->nभाग_frac * (u64)parent_rate;
	residual >>= 20;
	vco_out->rate += residual;

	वापस 0;
पूर्ण

/*
 * Based on the target frequency, find a match from the VCO frequency parameter
 * table and वापस its index
 */
अटल पूर्णांक pll_get_rate_index(काष्ठा iproc_pll *pll, अचिन्हित पूर्णांक target_rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pll->num_vco_entries; i++)
		अगर (target_rate == pll->vco_param[i].rate)
			अवरोध;

	अगर (i >= pll->num_vco_entries)
		वापस -EINVAL;

	वापस i;
पूर्ण

अटल पूर्णांक get_kp(अचिन्हित दीर्घ ref_freq, क्रमागत kp_band kp_index)
अणु
	पूर्णांक i;

	अगर (ref_freq < ref_freq_table[0][0])
		वापस -EINVAL;

	क्रम (i = 0; i < NUM_FREQ_BANDS; i++) अणु
		अगर (ref_freq >= ref_freq_table[i][0] &&
		    ref_freq < ref_freq_table[i][1])
			वापस kp_table[kp_index][i];
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक pll_रुको_क्रम_lock(काष्ठा iproc_pll *pll)
अणु
	पूर्णांक i;
	स्थिर काष्ठा iproc_pll_ctrl *ctrl = pll->ctrl;

	क्रम (i = 0; i < LOCK_DELAY; i++) अणु
		u32 val = पढ़ोl(pll->status_base + ctrl->status.offset);

		अगर (val & (1 << ctrl->status.shअगरt))
			वापस 0;
		udelay(10);
	पूर्ण

	वापस -EIO;
पूर्ण

अटल व्योम iproc_pll_ग_लिखो(स्थिर काष्ठा iproc_pll *pll, व्योम __iomem *base,
			    स्थिर u32 offset, u32 val)
अणु
	स्थिर काष्ठा iproc_pll_ctrl *ctrl = pll->ctrl;

	ग_लिखोl(val, base + offset);

	अगर (unlikely(ctrl->flags & IPROC_CLK_NEEDS_READ_BACK &&
		     (base == pll->status_base || base == pll->control_base)))
		val = पढ़ोl(base + offset);
पूर्ण

अटल व्योम __pll_disable(काष्ठा iproc_pll *pll)
अणु
	स्थिर काष्ठा iproc_pll_ctrl *ctrl = pll->ctrl;
	u32 val;

	अगर (ctrl->flags & IPROC_CLK_PLL_ASIU) अणु
		val = पढ़ोl(pll->asiu_base + ctrl->asiu.offset);
		val &= ~(1 << ctrl->asiu.en_shअगरt);
		iproc_pll_ग_लिखो(pll, pll->asiu_base, ctrl->asiu.offset, val);
	पूर्ण

	अगर (ctrl->flags & IPROC_CLK_EMBED_PWRCTRL) अणु
		val = पढ़ोl(pll->control_base + ctrl->aon.offset);
		val |= bit_mask(ctrl->aon.pwr_width) << ctrl->aon.pwr_shअगरt;
		iproc_pll_ग_लिखो(pll, pll->control_base, ctrl->aon.offset, val);
	पूर्ण

	अगर (pll->pwr_base) अणु
		/* latch input value so core घातer can be shut करोwn */
		val = पढ़ोl(pll->pwr_base + ctrl->aon.offset);
		val |= 1 << ctrl->aon.iso_shअगरt;
		iproc_pll_ग_लिखो(pll, pll->pwr_base, ctrl->aon.offset, val);

		/* घातer करोwn the core */
		val &= ~(bit_mask(ctrl->aon.pwr_width) << ctrl->aon.pwr_shअगरt);
		iproc_pll_ग_लिखो(pll, pll->pwr_base, ctrl->aon.offset, val);
	पूर्ण
पूर्ण

अटल पूर्णांक __pll_enable(काष्ठा iproc_pll *pll)
अणु
	स्थिर काष्ठा iproc_pll_ctrl *ctrl = pll->ctrl;
	u32 val;

	अगर (ctrl->flags & IPROC_CLK_EMBED_PWRCTRL) अणु
		val = पढ़ोl(pll->control_base + ctrl->aon.offset);
		val &= ~(bit_mask(ctrl->aon.pwr_width) << ctrl->aon.pwr_shअगरt);
		iproc_pll_ग_लिखो(pll, pll->control_base, ctrl->aon.offset, val);
	पूर्ण

	अगर (pll->pwr_base) अणु
		/* घातer up the PLL and make sure it's not latched */
		val = पढ़ोl(pll->pwr_base + ctrl->aon.offset);
		val |= bit_mask(ctrl->aon.pwr_width) << ctrl->aon.pwr_shअगरt;
		val &= ~(1 << ctrl->aon.iso_shअगरt);
		iproc_pll_ग_लिखो(pll, pll->pwr_base, ctrl->aon.offset, val);
	पूर्ण

	/* certain PLLs also need to be ungated from the ASIU top level */
	अगर (ctrl->flags & IPROC_CLK_PLL_ASIU) अणु
		val = पढ़ोl(pll->asiu_base + ctrl->asiu.offset);
		val |= (1 << ctrl->asiu.en_shअगरt);
		iproc_pll_ग_लिखो(pll, pll->asiu_base, ctrl->asiu.offset, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __pll_put_in_reset(काष्ठा iproc_pll *pll)
अणु
	u32 val;
	स्थिर काष्ठा iproc_pll_ctrl *ctrl = pll->ctrl;
	स्थिर काष्ठा iproc_pll_reset_ctrl *reset = &ctrl->reset;

	val = पढ़ोl(pll->control_base + reset->offset);
	अगर (ctrl->flags & IPROC_CLK_PLL_RESET_ACTIVE_LOW)
		val |= BIT(reset->reset_shअगरt) | BIT(reset->p_reset_shअगरt);
	अन्यथा
		val &= ~(BIT(reset->reset_shअगरt) | BIT(reset->p_reset_shअगरt));
	iproc_pll_ग_लिखो(pll, pll->control_base, reset->offset, val);
पूर्ण

अटल व्योम __pll_bring_out_reset(काष्ठा iproc_pll *pll, अचिन्हित पूर्णांक kp,
				  अचिन्हित पूर्णांक ka, अचिन्हित पूर्णांक ki)
अणु
	u32 val;
	स्थिर काष्ठा iproc_pll_ctrl *ctrl = pll->ctrl;
	स्थिर काष्ठा iproc_pll_reset_ctrl *reset = &ctrl->reset;
	स्थिर काष्ठा iproc_pll_dig_filter_ctrl *dig_filter = &ctrl->dig_filter;

	val = पढ़ोl(pll->control_base + dig_filter->offset);
	val &= ~(bit_mask(dig_filter->ki_width) << dig_filter->ki_shअगरt |
		bit_mask(dig_filter->kp_width) << dig_filter->kp_shअगरt |
		bit_mask(dig_filter->ka_width) << dig_filter->ka_shअगरt);
	val |= ki << dig_filter->ki_shअगरt | kp << dig_filter->kp_shअगरt |
	       ka << dig_filter->ka_shअगरt;
	iproc_pll_ग_लिखो(pll, pll->control_base, dig_filter->offset, val);

	val = पढ़ोl(pll->control_base + reset->offset);
	अगर (ctrl->flags & IPROC_CLK_PLL_RESET_ACTIVE_LOW)
		val &= ~(BIT(reset->reset_shअगरt) | BIT(reset->p_reset_shअगरt));
	अन्यथा
		val |= BIT(reset->reset_shअगरt) | BIT(reset->p_reset_shअगरt);
	iproc_pll_ग_लिखो(pll, pll->control_base, reset->offset, val);
पूर्ण

/*
 * Determines अगर the change to be applied to the PLL is minor (just an update
 * or the fractional भागider). If so, then we can aव्योम going through a
 * disruptive reset and lock sequence.
 */
अटल bool pll_fractional_change_only(काष्ठा iproc_pll *pll,
				       काष्ठा iproc_pll_vco_param *vco)
अणु
	स्थिर काष्ठा iproc_pll_ctrl *ctrl = pll->ctrl;
	u32 val;
	u32 nभाग_पूर्णांक;
	अचिन्हित पूर्णांक pभाग;

	/* PLL needs to be locked */
	val = पढ़ोl(pll->status_base + ctrl->status.offset);
	अगर ((val & (1 << ctrl->status.shअगरt)) == 0)
		वापस false;

	val = पढ़ोl(pll->control_base + ctrl->nभाग_पूर्णांक.offset);
	nभाग_पूर्णांक = (val >> ctrl->nभाग_पूर्णांक.shअगरt) &
		bit_mask(ctrl->nभाग_पूर्णांक.width);

	अगर (nभाग_पूर्णांक != vco->nभाग_पूर्णांक)
		वापस false;

	val = पढ़ोl(pll->control_base + ctrl->pभाग.offset);
	pभाग = (val >> ctrl->pभाग.shअगरt) & bit_mask(ctrl->pभाग.width);

	अगर (pभाग != vco->pभाग)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक pll_set_rate(काष्ठा iproc_clk *clk, काष्ठा iproc_pll_vco_param *vco,
			अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा iproc_pll *pll = clk->pll;
	स्थिर काष्ठा iproc_pll_ctrl *ctrl = pll->ctrl;
	पूर्णांक ka = 0, ki, kp, ret;
	अचिन्हित दीर्घ rate = vco->rate;
	u32 val;
	क्रमागत kp_band kp_index;
	अचिन्हित दीर्घ ref_freq;
	स्थिर अक्षर *clk_name = clk_hw_get_name(&clk->hw);

	/*
	 * reference frequency = parent frequency / PDIV
	 * If PDIV = 0, then it becomes a multiplier (x2)
	 */
	अगर (vco->pभाग == 0)
		ref_freq = parent_rate * 2;
	अन्यथा
		ref_freq = parent_rate / vco->pभाग;

	/* determine Ki and Kp index based on target VCO frequency */
	अगर (rate >= VCO_LOW && rate < VCO_HIGH) अणु
		ki = 4;
		kp_index = KP_BAND_MID;
	पूर्ण अन्यथा अगर (rate >= VCO_HIGH && rate < VCO_HIGH_HIGH) अणु
		ki = 3;
		kp_index = KP_BAND_HIGH;
	पूर्ण अन्यथा अगर (rate >= VCO_HIGH_HIGH && rate < VCO_MAX) अणु
		ki = 3;
		kp_index = KP_BAND_HIGH_HIGH;
	पूर्ण अन्यथा अणु
		pr_err("%s: pll: %s has invalid rate: %lu\n", __func__,
				clk_name, rate);
		वापस -EINVAL;
	पूर्ण

	kp = get_kp(ref_freq, kp_index);
	अगर (kp < 0) अणु
		pr_err("%s: pll: %s has invalid kp\n", __func__, clk_name);
		वापस kp;
	पूर्ण

	ret = __pll_enable(pll);
	अगर (ret) अणु
		pr_err("%s: pll: %s fails to enable\n", __func__, clk_name);
		वापस ret;
	पूर्ण

	अगर (pll_fractional_change_only(clk->pll, vco)) अणु
		/* program fractional part of NDIV */
		अगर (ctrl->flags & IPROC_CLK_PLL_HAS_NDIV_FRAC) अणु
			val = पढ़ोl(pll->control_base + ctrl->nभाग_frac.offset);
			val &= ~(bit_mask(ctrl->nभाग_frac.width) <<
				 ctrl->nभाग_frac.shअगरt);
			val |= vco->nभाग_frac << ctrl->nभाग_frac.shअगरt;
			iproc_pll_ग_लिखो(pll, pll->control_base,
					ctrl->nभाग_frac.offset, val);
			वापस 0;
		पूर्ण
	पूर्ण

	/* put PLL in reset */
	__pll_put_in_reset(pll);

	/* set PLL in user mode beक्रमe modअगरying PLL controls */
	अगर (ctrl->flags & IPROC_CLK_PLL_USER_MODE_ON) अणु
		val = पढ़ोl(pll->control_base + ctrl->macro_mode.offset);
		val &= ~(bit_mask(ctrl->macro_mode.width) <<
			ctrl->macro_mode.shअगरt);
		val |= PLL_USER_MODE << ctrl->macro_mode.shअगरt;
		iproc_pll_ग_लिखो(pll, pll->control_base,
			ctrl->macro_mode.offset, val);
	पूर्ण

	iproc_pll_ग_लिखो(pll, pll->control_base, ctrl->vco_ctrl.u_offset, 0);

	val = पढ़ोl(pll->control_base + ctrl->vco_ctrl.l_offset);

	अगर (rate >= VCO_LOW && rate < VCO_MID)
		val |= (1 << PLL_VCO_LOW_SHIFT);

	अगर (rate < VCO_HIGH)
		val &= ~(1 << PLL_VCO_HIGH_SHIFT);
	अन्यथा
		val |= (1 << PLL_VCO_HIGH_SHIFT);

	iproc_pll_ग_लिखो(pll, pll->control_base, ctrl->vco_ctrl.l_offset, val);

	/* program पूर्णांकeger part of NDIV */
	val = पढ़ोl(pll->control_base + ctrl->nभाग_पूर्णांक.offset);
	val &= ~(bit_mask(ctrl->nभाग_पूर्णांक.width) << ctrl->nभाग_पूर्णांक.shअगरt);
	val |= vco->nभाग_पूर्णांक << ctrl->nभाग_पूर्णांक.shअगरt;
	iproc_pll_ग_लिखो(pll, pll->control_base, ctrl->nभाग_पूर्णांक.offset, val);

	/* program fractional part of NDIV */
	अगर (ctrl->flags & IPROC_CLK_PLL_HAS_NDIV_FRAC) अणु
		val = पढ़ोl(pll->control_base + ctrl->nभाग_frac.offset);
		val &= ~(bit_mask(ctrl->nभाग_frac.width) <<
			 ctrl->nभाग_frac.shअगरt);
		val |= vco->nभाग_frac << ctrl->nभाग_frac.shअगरt;
		iproc_pll_ग_लिखो(pll, pll->control_base, ctrl->nभाग_frac.offset,
				val);
	पूर्ण

	/* program PDIV */
	val = पढ़ोl(pll->control_base + ctrl->pभाग.offset);
	val &= ~(bit_mask(ctrl->pभाग.width) << ctrl->pभाग.shअगरt);
	val |= vco->pभाग << ctrl->pभाग.shअगरt;
	iproc_pll_ग_लिखो(pll, pll->control_base, ctrl->pभाग.offset, val);

	__pll_bring_out_reset(pll, kp, ka, ki);

	ret = pll_रुको_क्रम_lock(pll);
	अगर (ret < 0) अणु
		pr_err("%s: pll: %s failed to lock\n", __func__, clk_name);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iproc_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा iproc_clk *clk = to_iproc_clk(hw);
	काष्ठा iproc_pll *pll = clk->pll;

	वापस __pll_enable(pll);
पूर्ण

अटल व्योम iproc_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा iproc_clk *clk = to_iproc_clk(hw);
	काष्ठा iproc_pll *pll = clk->pll;
	स्थिर काष्ठा iproc_pll_ctrl *ctrl = pll->ctrl;

	अगर (ctrl->flags & IPROC_CLK_AON)
		वापस;

	__pll_disable(pll);
पूर्ण

अटल अचिन्हित दीर्घ iproc_pll_recalc_rate(काष्ठा clk_hw *hw,
					   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा iproc_clk *clk = to_iproc_clk(hw);
	काष्ठा iproc_pll *pll = clk->pll;
	स्थिर काष्ठा iproc_pll_ctrl *ctrl = pll->ctrl;
	u32 val;
	u64 nभाग, nभाग_पूर्णांक, nभाग_frac;
	अचिन्हित पूर्णांक pभाग;
	अचिन्हित दीर्घ rate;

	अगर (parent_rate == 0)
		वापस 0;

	/* PLL needs to be locked */
	val = पढ़ोl(pll->status_base + ctrl->status.offset);
	अगर ((val & (1 << ctrl->status.shअगरt)) == 0)
		वापस 0;

	/*
	 * PLL output frequency =
	 *
	 * ((nभाग_पूर्णांक + nभाग_frac / 2^20) * (parent घड़ी rate / pभाग)
	 */
	val = पढ़ोl(pll->control_base + ctrl->nभाग_पूर्णांक.offset);
	nभाग_पूर्णांक = (val >> ctrl->nभाग_पूर्णांक.shअगरt) &
		bit_mask(ctrl->nभाग_पूर्णांक.width);
	nभाग = nभाग_पूर्णांक << 20;

	अगर (ctrl->flags & IPROC_CLK_PLL_HAS_NDIV_FRAC) अणु
		val = पढ़ोl(pll->control_base + ctrl->nभाग_frac.offset);
		nभाग_frac = (val >> ctrl->nभाग_frac.shअगरt) &
			bit_mask(ctrl->nभाग_frac.width);
		nभाग += nभाग_frac;
	पूर्ण

	val = पढ़ोl(pll->control_base + ctrl->pभाग.offset);
	pभाग = (val >> ctrl->pभाग.shअगरt) & bit_mask(ctrl->pभाग.width);

	rate = (nभाग * parent_rate) >> 20;

	अगर (pभाग == 0)
		rate *= 2;
	अन्यथा
		rate /= pभाग;

	वापस rate;
पूर्ण

अटल पूर्णांक iproc_pll_determine_rate(काष्ठा clk_hw *hw,
		काष्ठा clk_rate_request *req)
अणु
	अचिन्हित पूर्णांक  i;
	काष्ठा iproc_clk *clk = to_iproc_clk(hw);
	काष्ठा iproc_pll *pll = clk->pll;
	स्थिर काष्ठा iproc_pll_ctrl *ctrl = pll->ctrl;
	अचिन्हित दीर्घ  dअगरf, best_dअगरf;
	अचिन्हित पूर्णांक  best_idx = 0;
	पूर्णांक ret;

	अगर (req->rate == 0 || req->best_parent_rate == 0)
		वापस -EINVAL;

	अगर (ctrl->flags & IPROC_CLK_PLL_CALC_PARAM) अणु
		काष्ठा iproc_pll_vco_param vco_param;

		ret = pll_calc_param(req->rate, req->best_parent_rate,
					&vco_param);
		अगर (ret)
			वापस ret;

		req->rate = vco_param.rate;
		वापस 0;
	पूर्ण

	अगर (!pll->vco_param)
		वापस -EINVAL;

	best_dअगरf = अच_दीर्घ_उच्च;
	क्रम (i = 0; i < pll->num_vco_entries; i++) अणु
		dअगरf = असल(req->rate - pll->vco_param[i].rate);
		अगर (dअगरf <= best_dअगरf) अणु
			best_dअगरf = dअगरf;
			best_idx = i;
		पूर्ण
		/* अवरोध now अगर perfect match */
		अगर (dअगरf == 0)
			अवरोध;
	पूर्ण

	req->rate = pll->vco_param[best_idx].rate;

	वापस 0;
पूर्ण

अटल पूर्णांक iproc_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा iproc_clk *clk = to_iproc_clk(hw);
	काष्ठा iproc_pll *pll = clk->pll;
	स्थिर काष्ठा iproc_pll_ctrl *ctrl = pll->ctrl;
	काष्ठा iproc_pll_vco_param vco_param;
	पूर्णांक rate_index, ret;

	अगर (ctrl->flags & IPROC_CLK_PLL_CALC_PARAM) अणु
		ret = pll_calc_param(rate, parent_rate, &vco_param);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		rate_index = pll_get_rate_index(pll, rate);
		अगर (rate_index < 0)
			वापस rate_index;

		vco_param = pll->vco_param[rate_index];
	पूर्ण

	ret = pll_set_rate(clk, &vco_param, parent_rate);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops iproc_pll_ops = अणु
	.enable = iproc_pll_enable,
	.disable = iproc_pll_disable,
	.recalc_rate = iproc_pll_recalc_rate,
	.determine_rate = iproc_pll_determine_rate,
	.set_rate = iproc_pll_set_rate,
पूर्ण;

अटल पूर्णांक iproc_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा iproc_clk *clk = to_iproc_clk(hw);
	स्थिर काष्ठा iproc_clk_ctrl *ctrl = clk->ctrl;
	काष्ठा iproc_pll *pll = clk->pll;
	u32 val;

	/* channel enable is active low */
	val = पढ़ोl(pll->control_base + ctrl->enable.offset);
	val &= ~(1 << ctrl->enable.enable_shअगरt);
	iproc_pll_ग_लिखो(pll, pll->control_base, ctrl->enable.offset, val);

	/* also make sure channel is not held */
	val = पढ़ोl(pll->control_base + ctrl->enable.offset);
	val &= ~(1 << ctrl->enable.hold_shअगरt);
	iproc_pll_ग_लिखो(pll, pll->control_base, ctrl->enable.offset, val);

	वापस 0;
पूर्ण

अटल व्योम iproc_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा iproc_clk *clk = to_iproc_clk(hw);
	स्थिर काष्ठा iproc_clk_ctrl *ctrl = clk->ctrl;
	काष्ठा iproc_pll *pll = clk->pll;
	u32 val;

	अगर (ctrl->flags & IPROC_CLK_AON)
		वापस;

	val = पढ़ोl(pll->control_base + ctrl->enable.offset);
	val |= 1 << ctrl->enable.enable_shअगरt;
	iproc_pll_ग_लिखो(pll, pll->control_base, ctrl->enable.offset, val);
पूर्ण

अटल अचिन्हित दीर्घ iproc_clk_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा iproc_clk *clk = to_iproc_clk(hw);
	स्थिर काष्ठा iproc_clk_ctrl *ctrl = clk->ctrl;
	काष्ठा iproc_pll *pll = clk->pll;
	u32 val;
	अचिन्हित पूर्णांक mभाग;
	अचिन्हित दीर्घ rate;

	अगर (parent_rate == 0)
		वापस 0;

	val = पढ़ोl(pll->control_base + ctrl->mभाग.offset);
	mभाग = (val >> ctrl->mभाग.shअगरt) & bit_mask(ctrl->mभाग.width);
	अगर (mभाग == 0)
		mभाग = 256;

	अगर (ctrl->flags & IPROC_CLK_MCLK_DIV_BY_2)
		rate = parent_rate / (mभाग * 2);
	अन्यथा
		rate = parent_rate / mभाग;

	वापस rate;
पूर्ण

अटल पूर्णांक iproc_clk_determine_rate(काष्ठा clk_hw *hw,
		काष्ठा clk_rate_request *req)
अणु
	अचिन्हित पूर्णांक bestभाग;

	अगर (req->rate == 0)
		वापस -EINVAL;
	अगर (req->rate == req->best_parent_rate)
		वापस 0;

	bestभाग = DIV_ROUND_CLOSEST(req->best_parent_rate, req->rate);
	अगर (bestभाग < 2)
		req->rate = req->best_parent_rate;

	अगर (bestभाग > 256)
		bestभाग = 256;

	req->rate = req->best_parent_rate / bestभाग;

	वापस 0;
पूर्ण

अटल पूर्णांक iproc_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा iproc_clk *clk = to_iproc_clk(hw);
	स्थिर काष्ठा iproc_clk_ctrl *ctrl = clk->ctrl;
	काष्ठा iproc_pll *pll = clk->pll;
	u32 val;
	अचिन्हित पूर्णांक भाग;

	अगर (rate == 0 || parent_rate == 0)
		वापस -EINVAL;

	भाग = DIV_ROUND_CLOSEST(parent_rate, rate);
	अगर (ctrl->flags & IPROC_CLK_MCLK_DIV_BY_2)
		भाग /=  2;

	अगर (भाग > 256)
		वापस -EINVAL;

	val = पढ़ोl(pll->control_base + ctrl->mभाग.offset);
	अगर (भाग == 256) अणु
		val &= ~(bit_mask(ctrl->mभाग.width) << ctrl->mभाग.shअगरt);
	पूर्ण अन्यथा अणु
		val &= ~(bit_mask(ctrl->mभाग.width) << ctrl->mभाग.shअगरt);
		val |= भाग << ctrl->mभाग.shअगरt;
	पूर्ण
	iproc_pll_ग_लिखो(pll, pll->control_base, ctrl->mभाग.offset, val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops iproc_clk_ops = अणु
	.enable = iproc_clk_enable,
	.disable = iproc_clk_disable,
	.recalc_rate = iproc_clk_recalc_rate,
	.determine_rate = iproc_clk_determine_rate,
	.set_rate = iproc_clk_set_rate,
पूर्ण;

/*
 * Some PLLs require the PLL SW override bit to be set beक्रमe changes can be
 * applied to the PLL
 */
अटल व्योम iproc_pll_sw_cfg(काष्ठा iproc_pll *pll)
अणु
	स्थिर काष्ठा iproc_pll_ctrl *ctrl = pll->ctrl;

	अगर (ctrl->flags & IPROC_CLK_PLL_NEEDS_SW_CFG) अणु
		u32 val;

		val = पढ़ोl(pll->control_base + ctrl->sw_ctrl.offset);
		val |= BIT(ctrl->sw_ctrl.shअगरt);
		iproc_pll_ग_लिखो(pll, pll->control_base, ctrl->sw_ctrl.offset,
				val);
	पूर्ण
पूर्ण

व्योम iproc_pll_clk_setup(काष्ठा device_node *node,
			 स्थिर काष्ठा iproc_pll_ctrl *pll_ctrl,
			 स्थिर काष्ठा iproc_pll_vco_param *vco,
			 अचिन्हित पूर्णांक num_vco_entries,
			 स्थिर काष्ठा iproc_clk_ctrl *clk_ctrl,
			 अचिन्हित पूर्णांक num_clks)
अणु
	पूर्णांक i, ret;
	काष्ठा iproc_pll *pll;
	काष्ठा iproc_clk *iclk;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *parent_name;
	काष्ठा iproc_clk *iclk_array;
	काष्ठा clk_hw_onecell_data *clk_data;

	अगर (WARN_ON(!pll_ctrl) || WARN_ON(!clk_ctrl))
		वापस;

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (WARN_ON(!pll))
		वापस;

	clk_data = kzalloc(काष्ठा_size(clk_data, hws, num_clks), GFP_KERNEL);
	अगर (WARN_ON(!clk_data))
		जाओ err_clk_data;
	clk_data->num = num_clks;

	iclk_array = kसुस्मृति(num_clks, माप(काष्ठा iproc_clk), GFP_KERNEL);
	अगर (WARN_ON(!iclk_array))
		जाओ err_clks;

	pll->control_base = of_iomap(node, 0);
	अगर (WARN_ON(!pll->control_base))
		जाओ err_pll_iomap;

	/* Some SoCs करो not require the pwr_base, thus failing is not fatal */
	pll->pwr_base = of_iomap(node, 1);

	/* some PLLs require gating control at the top ASIU level */
	अगर (pll_ctrl->flags & IPROC_CLK_PLL_ASIU) अणु
		pll->asiu_base = of_iomap(node, 2);
		अगर (WARN_ON(!pll->asiu_base))
			जाओ err_asiu_iomap;
	पूर्ण

	अगर (pll_ctrl->flags & IPROC_CLK_PLL_SPLIT_STAT_CTRL) अणु
		/* Some SoCs have a split status/control.  If this करोes not
		 * exist, assume they are unअगरied.
		 */
		pll->status_base = of_iomap(node, 2);
		अगर (!pll->status_base)
			जाओ err_status_iomap;
	पूर्ण अन्यथा
		pll->status_base = pll->control_base;

	/* initialize and रेजिस्टर the PLL itself */
	pll->ctrl = pll_ctrl;

	iclk = &iclk_array[0];
	iclk->pll = pll;

	init.name = node->name;
	init.ops = &iproc_pll_ops;
	init.flags = 0;
	parent_name = of_clk_get_parent_name(node, 0);
	init.parent_names = (parent_name ? &parent_name : शून्य);
	init.num_parents = (parent_name ? 1 : 0);
	iclk->hw.init = &init;

	अगर (vco) अणु
		pll->num_vco_entries = num_vco_entries;
		pll->vco_param = vco;
	पूर्ण

	iproc_pll_sw_cfg(pll);

	ret = clk_hw_रेजिस्टर(शून्य, &iclk->hw);
	अगर (WARN_ON(ret))
		जाओ err_pll_रेजिस्टर;

	clk_data->hws[0] = &iclk->hw;

	/* now initialize and रेजिस्टर all leaf घड़ीs */
	क्रम (i = 1; i < num_clks; i++) अणु
		स्थिर अक्षर *clk_name;

		स_रखो(&init, 0, माप(init));
		parent_name = node->name;

		ret = of_property_पढ़ो_string_index(node, "clock-output-names",
						    i, &clk_name);
		अगर (WARN_ON(ret))
			जाओ err_clk_रेजिस्टर;

		iclk = &iclk_array[i];
		iclk->pll = pll;
		iclk->ctrl = &clk_ctrl[i];

		init.name = clk_name;
		init.ops = &iproc_clk_ops;
		init.flags = 0;
		init.parent_names = (parent_name ? &parent_name : शून्य);
		init.num_parents = (parent_name ? 1 : 0);
		iclk->hw.init = &init;

		ret = clk_hw_रेजिस्टर(शून्य, &iclk->hw);
		अगर (WARN_ON(ret))
			जाओ err_clk_रेजिस्टर;

		clk_data->hws[i] = &iclk->hw;
	पूर्ण

	ret = of_clk_add_hw_provider(node, of_clk_hw_onecell_get, clk_data);
	अगर (WARN_ON(ret))
		जाओ err_clk_रेजिस्टर;

	वापस;

err_clk_रेजिस्टर:
	जबतक (--i >= 0)
		clk_hw_unरेजिस्टर(clk_data->hws[i]);

err_pll_रेजिस्टर:
	अगर (pll->status_base != pll->control_base)
		iounmap(pll->status_base);

err_status_iomap:
	अगर (pll->asiu_base)
		iounmap(pll->asiu_base);

err_asiu_iomap:
	अगर (pll->pwr_base)
		iounmap(pll->pwr_base);

	iounmap(pll->control_base);

err_pll_iomap:
	kमुक्त(iclk_array);

err_clks:
	kमुक्त(clk_data);

err_clk_data:
	kमुक्त(pll);
पूर्ण
