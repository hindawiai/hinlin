<शैली गुरु>
/*
 * Copyright (c) 2016, NVIDIA CORPORATION. All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#समावेश <subdev/clk.h>
#समावेश <subdev/volt.h>
#समावेश <subdev/समयr.h>
#समावेश <core/device.h>
#समावेश <core/tegra.h>

#समावेश "priv.h"
#समावेश "gk20a.h"

#घोषणा GPCPLL_CFG_SYNC_MODE	BIT(2)

#घोषणा BYPASSCTRL_SYS	(SYS_GPCPLL_CFG_BASE + 0x340)
#घोषणा BYPASSCTRL_SYS_GPCPLL_SHIFT	0
#घोषणा BYPASSCTRL_SYS_GPCPLL_WIDTH	1

#घोषणा GPCPLL_CFG2_SDM_DIN_SHIFT	0
#घोषणा GPCPLL_CFG2_SDM_DIN_WIDTH	8
#घोषणा GPCPLL_CFG2_SDM_DIN_MASK	\
	(MASK(GPCPLL_CFG2_SDM_DIN_WIDTH) << GPCPLL_CFG2_SDM_DIN_SHIFT)
#घोषणा GPCPLL_CFG2_SDM_DIN_NEW_SHIFT	8
#घोषणा GPCPLL_CFG2_SDM_DIN_NEW_WIDTH	15
#घोषणा GPCPLL_CFG2_SDM_DIN_NEW_MASK	\
	(MASK(GPCPLL_CFG2_SDM_DIN_NEW_WIDTH) << GPCPLL_CFG2_SDM_DIN_NEW_SHIFT)
#घोषणा GPCPLL_CFG2_SETUP2_SHIFT	16
#घोषणा GPCPLL_CFG2_PLL_STEPA_SHIFT	24

#घोषणा GPCPLL_DVFS0	(SYS_GPCPLL_CFG_BASE + 0x10)
#घोषणा GPCPLL_DVFS0_DFS_COEFF_SHIFT	0
#घोषणा GPCPLL_DVFS0_DFS_COEFF_WIDTH	7
#घोषणा GPCPLL_DVFS0_DFS_COEFF_MASK	\
	(MASK(GPCPLL_DVFS0_DFS_COEFF_WIDTH) << GPCPLL_DVFS0_DFS_COEFF_SHIFT)
#घोषणा GPCPLL_DVFS0_DFS_DET_MAX_SHIFT	8
#घोषणा GPCPLL_DVFS0_DFS_DET_MAX_WIDTH	7
#घोषणा GPCPLL_DVFS0_DFS_DET_MAX_MASK	\
	(MASK(GPCPLL_DVFS0_DFS_DET_MAX_WIDTH) << GPCPLL_DVFS0_DFS_DET_MAX_SHIFT)

#घोषणा GPCPLL_DVFS1		(SYS_GPCPLL_CFG_BASE + 0x14)
#घोषणा GPCPLL_DVFS1_DFS_EXT_DET_SHIFT		0
#घोषणा GPCPLL_DVFS1_DFS_EXT_DET_WIDTH		7
#घोषणा GPCPLL_DVFS1_DFS_EXT_STRB_SHIFT		7
#घोषणा GPCPLL_DVFS1_DFS_EXT_STRB_WIDTH		1
#घोषणा GPCPLL_DVFS1_DFS_EXT_CAL_SHIFT		8
#घोषणा GPCPLL_DVFS1_DFS_EXT_CAL_WIDTH		7
#घोषणा GPCPLL_DVFS1_DFS_EXT_SEL_SHIFT		15
#घोषणा GPCPLL_DVFS1_DFS_EXT_SEL_WIDTH		1
#घोषणा GPCPLL_DVFS1_DFS_CTRL_SHIFT		16
#घोषणा GPCPLL_DVFS1_DFS_CTRL_WIDTH		12
#घोषणा GPCPLL_DVFS1_EN_SDM_SHIFT		28
#घोषणा GPCPLL_DVFS1_EN_SDM_WIDTH		1
#घोषणा GPCPLL_DVFS1_EN_SDM_BIT			BIT(28)
#घोषणा GPCPLL_DVFS1_EN_DFS_SHIFT		29
#घोषणा GPCPLL_DVFS1_EN_DFS_WIDTH		1
#घोषणा GPCPLL_DVFS1_EN_DFS_BIT			BIT(29)
#घोषणा GPCPLL_DVFS1_EN_DFS_CAL_SHIFT		30
#घोषणा GPCPLL_DVFS1_EN_DFS_CAL_WIDTH		1
#घोषणा GPCPLL_DVFS1_EN_DFS_CAL_BIT		BIT(30)
#घोषणा GPCPLL_DVFS1_DFS_CAL_DONE_SHIFT		31
#घोषणा GPCPLL_DVFS1_DFS_CAL_DONE_WIDTH		1
#घोषणा GPCPLL_DVFS1_DFS_CAL_DONE_BIT		BIT(31)

#घोषणा GPC_BCAST_GPCPLL_DVFS2	(GPC_BCAST_GPCPLL_CFG_BASE + 0x20)
#घोषणा GPC_BCAST_GPCPLL_DVFS2_DFS_EXT_STROBE_BIT	BIT(16)

#घोषणा GPCPLL_CFG3_PLL_DFS_TESTOUT_SHIFT	24
#घोषणा GPCPLL_CFG3_PLL_DFS_TESTOUT_WIDTH	7

#घोषणा DFS_DET_RANGE	6	/* -2^6 ... 2^6-1 */
#घोषणा SDM_DIN_RANGE	12	/* -2^12 ... 2^12-1 */

काष्ठा gm20b_clk_dvfs_params अणु
	s32 coeff_slope;
	s32 coeff_offs;
	u32 vco_ctrl;
पूर्ण;

अटल स्थिर काष्ठा gm20b_clk_dvfs_params gm20b_dvfs_params = अणु
	.coeff_slope = -165230,
	.coeff_offs = 214007,
	.vco_ctrl = 0x7 << 3,
पूर्ण;

/*
 * base.n is now the *पूर्णांकeger* part of the N factor.
 * sdm_din contains n's decimal part.
 */
काष्ठा gm20b_pll अणु
	काष्ठा gk20a_pll base;
	u32 sdm_din;
पूर्ण;

काष्ठा gm20b_clk_dvfs अणु
	u32 dfs_coeff;
	s32 dfs_det_max;
	s32 dfs_ext_cal;
पूर्ण;

काष्ठा gm20b_clk अणु
	/* currently applied parameters */
	काष्ठा gk20a_clk base;
	काष्ठा gm20b_clk_dvfs dvfs;
	u32 uv;

	/* new parameters to apply */
	काष्ठा gk20a_pll new_pll;
	काष्ठा gm20b_clk_dvfs new_dvfs;
	u32 new_uv;

	स्थिर काष्ठा gm20b_clk_dvfs_params *dvfs_params;

	/* fused parameters */
	s32 uvdet_slope;
	s32 uvdet_offs;

	/* safe frequency we can use at minimum voltage */
	u32 safe_fmax_vmin;
पूर्ण;
#घोषणा gm20b_clk(p) container_of((gk20a_clk(p)), काष्ठा gm20b_clk, base)

अटल u32 pl_to_भाग(u32 pl)
अणु
	वापस pl;
पूर्ण

अटल u32 भाग_प्रकारo_pl(u32 भाग)
अणु
	वापस भाग;
पूर्ण

अटल स्थिर काष्ठा gk20a_clk_pllg_params gm20b_pllg_params = अणु
	.min_vco = 1300000, .max_vco = 2600000,
	.min_u = 12000, .max_u = 38400,
	.min_m = 1, .max_m = 255,
	.min_n = 8, .max_n = 255,
	.min_pl = 1, .max_pl = 31,
पूर्ण;

अटल व्योम
gm20b_pllg_पढ़ो_mnp(काष्ठा gm20b_clk *clk, काष्ठा gm20b_pll *pll)
अणु
	काष्ठा nvkm_subdev *subdev = &clk->base.base.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 val;

	gk20a_pllg_पढ़ो_mnp(&clk->base, &pll->base);
	val = nvkm_rd32(device, GPCPLL_CFG2);
	pll->sdm_din = (val >> GPCPLL_CFG2_SDM_DIN_SHIFT) &
		       MASK(GPCPLL_CFG2_SDM_DIN_WIDTH);
पूर्ण

अटल व्योम
gm20b_pllg_ग_लिखो_mnp(काष्ठा gm20b_clk *clk, स्थिर काष्ठा gm20b_pll *pll)
अणु
	काष्ठा nvkm_device *device = clk->base.base.subdev.device;

	nvkm_mask(device, GPCPLL_CFG2, GPCPLL_CFG2_SDM_DIN_MASK,
		  pll->sdm_din << GPCPLL_CFG2_SDM_DIN_SHIFT);
	gk20a_pllg_ग_लिखो_mnp(&clk->base, &pll->base);
पूर्ण

/*
 * Determine DFS_COEFF क्रम the requested voltage. Always select बाह्यal
 * calibration override equal to the voltage, and set maximum detection
 * limit "0" (to make sure that PLL output reमुख्यs under F/V curve when
 * voltage increases).
 */
अटल व्योम
gm20b_dvfs_calc_det_coeff(काष्ठा gm20b_clk *clk, s32 uv,
			  काष्ठा gm20b_clk_dvfs *dvfs)
अणु
	काष्ठा nvkm_subdev *subdev = &clk->base.base.subdev;
	स्थिर काष्ठा gm20b_clk_dvfs_params *p = clk->dvfs_params;
	u32 coeff;
	/* Work with mv as uv would likely trigger an overflow */
	s32 mv = DIV_ROUND_CLOSEST(uv, 1000);

	/* coeff = slope * voltage + offset */
	coeff = DIV_ROUND_CLOSEST(mv * p->coeff_slope, 1000) + p->coeff_offs;
	coeff = DIV_ROUND_CLOSEST(coeff, 1000);
	dvfs->dfs_coeff = min_t(u32, coeff, MASK(GPCPLL_DVFS0_DFS_COEFF_WIDTH));

	dvfs->dfs_ext_cal = DIV_ROUND_CLOSEST(uv - clk->uvdet_offs,
					     clk->uvdet_slope);
	/* should never happen */
	अगर (असल(dvfs->dfs_ext_cal) >= BIT(DFS_DET_RANGE))
		nvkm_error(subdev, "dfs_ext_cal overflow!\n");

	dvfs->dfs_det_max = 0;

	nvkm_debug(subdev, "%s uv: %d coeff: %x, ext_cal: %d, det_max: %d\n",
		   __func__, uv, dvfs->dfs_coeff, dvfs->dfs_ext_cal,
		   dvfs->dfs_det_max);
पूर्ण

/*
 * Solve equation क्रम पूर्णांकeger and fractional part of the effective NDIV:
 *
 * n_eff = n_पूर्णांक + 1/2 + (SDM_DIN / 2^(SDM_DIN_RANGE + 1)) +
 *         (DVFS_COEFF * DVFS_DET_DELTA) / 2^DFS_DET_RANGE
 *
 * The SDM_DIN LSB is finally shअगरted out, since it is not accessible by sw.
 */
अटल व्योम
gm20b_dvfs_calc_nभाग(काष्ठा gm20b_clk *clk, u32 n_eff, u32 *n_पूर्णांक, u32 *sdm_din)
अणु
	काष्ठा nvkm_subdev *subdev = &clk->base.base.subdev;
	स्थिर काष्ठा gk20a_clk_pllg_params *p = clk->base.params;
	u32 n;
	s32 det_delta;
	u32 rem, rem_range;

	/* calculate current ext_cal and subtract previous one */
	det_delta = DIV_ROUND_CLOSEST(((s32)clk->uv) - clk->uvdet_offs,
				      clk->uvdet_slope);
	det_delta -= clk->dvfs.dfs_ext_cal;
	det_delta = min(det_delta, clk->dvfs.dfs_det_max);
	det_delta *= clk->dvfs.dfs_coeff;

	/* पूर्णांकeger part of n */
	n = (n_eff << DFS_DET_RANGE) - det_delta;
	/* should never happen! */
	अगर (n <= 0) अणु
		nvkm_error(subdev, "ndiv <= 0 - setting to 1...\n");
		n = 1 << DFS_DET_RANGE;
	पूर्ण
	अगर (n >> DFS_DET_RANGE > p->max_n) अणु
		nvkm_error(subdev, "ndiv > max_n - setting to max_n...\n");
		n = p->max_n << DFS_DET_RANGE;
	पूर्ण
	*n_पूर्णांक = n >> DFS_DET_RANGE;

	/* fractional part of n */
	rem = ((u32)n) & MASK(DFS_DET_RANGE);
	rem_range = SDM_DIN_RANGE + 1 - DFS_DET_RANGE;
	/* subtract 2^SDM_DIN_RANGE to account क्रम the 1/2 of the equation */
	rem = (rem << rem_range) - BIT(SDM_DIN_RANGE);
	/* lose 8 LSB and clip - sdm_din only keeps the most signअगरicant byte */
	*sdm_din = (rem >> BITS_PER_BYTE) & MASK(GPCPLL_CFG2_SDM_DIN_WIDTH);

	nvkm_debug(subdev, "%s n_eff: %d, n_int: %d, sdm_din: %d\n", __func__,
		   n_eff, *n_पूर्णांक, *sdm_din);
पूर्ण

अटल पूर्णांक
gm20b_pllg_slide(काष्ठा gm20b_clk *clk, u32 n)
अणु
	काष्ठा nvkm_subdev *subdev = &clk->base.base.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा gm20b_pll pll;
	u32 n_पूर्णांक, sdm_din;
	पूर्णांक ret = 0;

	/* calculate the new n_पूर्णांक/sdm_din क्रम this n/uv */
	gm20b_dvfs_calc_nभाग(clk, n, &n_पूर्णांक, &sdm_din);

	/* get old coefficients */
	gm20b_pllg_पढ़ो_mnp(clk, &pll);
	/* करो nothing अगर NDIV is the same */
	अगर (n_पूर्णांक == pll.base.n && sdm_din == pll.sdm_din)
		वापस 0;

	/* pll slowकरोwn mode */
	nvkm_mask(device, GPCPLL_NDIV_SLOWDOWN,
		BIT(GPCPLL_NDIV_SLOWDOWN_SLOWDOWN_USING_PLL_SHIFT),
		BIT(GPCPLL_NDIV_SLOWDOWN_SLOWDOWN_USING_PLL_SHIFT));

	/* new nभाग पढ़ोy क्रम ramp */
	/* in DVFS mode SDM is updated via "new" field */
	nvkm_mask(device, GPCPLL_CFG2, GPCPLL_CFG2_SDM_DIN_NEW_MASK,
		  sdm_din << GPCPLL_CFG2_SDM_DIN_NEW_SHIFT);
	pll.base.n = n_पूर्णांक;
	udelay(1);
	gk20a_pllg_ग_लिखो_mnp(&clk->base, &pll.base);

	/* dynamic ramp to new nभाग */
	udelay(1);
	nvkm_mask(device, GPCPLL_NDIV_SLOWDOWN,
		  BIT(GPCPLL_NDIV_SLOWDOWN_EN_DYNRAMP_SHIFT),
		  BIT(GPCPLL_NDIV_SLOWDOWN_EN_DYNRAMP_SHIFT));

	/* रुको क्रम ramping to complete */
	अगर (nvkm_रुको_usec(device, 500, GPC_BCAST_NDIV_SLOWDOWN_DEBUG,
		GPC_BCAST_NDIV_SLOWDOWN_DEBUG_PLL_DYNRAMP_DONE_SYNCED_MASK,
		GPC_BCAST_NDIV_SLOWDOWN_DEBUG_PLL_DYNRAMP_DONE_SYNCED_MASK) < 0)
		ret = -ETIMEDOUT;

	/* in DVFS mode complete SDM update */
	nvkm_mask(device, GPCPLL_CFG2, GPCPLL_CFG2_SDM_DIN_MASK,
		  sdm_din << GPCPLL_CFG2_SDM_DIN_SHIFT);

	/* निकास slowकरोwn mode */
	nvkm_mask(device, GPCPLL_NDIV_SLOWDOWN,
		BIT(GPCPLL_NDIV_SLOWDOWN_SLOWDOWN_USING_PLL_SHIFT) |
		BIT(GPCPLL_NDIV_SLOWDOWN_EN_DYNRAMP_SHIFT), 0);
	nvkm_rd32(device, GPCPLL_NDIV_SLOWDOWN);

	वापस ret;
पूर्ण

अटल पूर्णांक
gm20b_pllg_enable(काष्ठा gm20b_clk *clk)
अणु
	काष्ठा nvkm_device *device = clk->base.base.subdev.device;

	nvkm_mask(device, GPCPLL_CFG, GPCPLL_CFG_ENABLE, GPCPLL_CFG_ENABLE);
	nvkm_rd32(device, GPCPLL_CFG);

	/* In DVFS mode lock cannot be used - so just delay */
	udelay(40);

	/* set SYNC_MODE क्रम glitchless चयन out of bypass */
	nvkm_mask(device, GPCPLL_CFG, GPCPLL_CFG_SYNC_MODE,
		       GPCPLL_CFG_SYNC_MODE);
	nvkm_rd32(device, GPCPLL_CFG);

	/* चयन to VCO mode */
	nvkm_mask(device, SEL_VCO, BIT(SEL_VCO_GPC2CLK_OUT_SHIFT),
		  BIT(SEL_VCO_GPC2CLK_OUT_SHIFT));

	वापस 0;
पूर्ण

अटल व्योम
gm20b_pllg_disable(काष्ठा gm20b_clk *clk)
अणु
	काष्ठा nvkm_device *device = clk->base.base.subdev.device;

	/* put PLL in bypass beक्रमe disabling it */
	nvkm_mask(device, SEL_VCO, BIT(SEL_VCO_GPC2CLK_OUT_SHIFT), 0);

	/* clear SYNC_MODE beक्रमe disabling PLL */
	nvkm_mask(device, GPCPLL_CFG, GPCPLL_CFG_SYNC_MODE, 0);

	nvkm_mask(device, GPCPLL_CFG, GPCPLL_CFG_ENABLE, 0);
	nvkm_rd32(device, GPCPLL_CFG);
पूर्ण

अटल पूर्णांक
gm20b_pllg_program_mnp(काष्ठा gm20b_clk *clk, स्थिर काष्ठा gk20a_pll *pll)
अणु
	काष्ठा nvkm_subdev *subdev = &clk->base.base.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा gm20b_pll cur_pll;
	u32 n_पूर्णांक, sdm_din;
	/* अगर we only change pभाग, we can करो a glitchless transition */
	bool pभाग_only;
	पूर्णांक ret;

	gm20b_dvfs_calc_nभाग(clk, pll->n, &n_पूर्णांक, &sdm_din);
	gm20b_pllg_पढ़ो_mnp(clk, &cur_pll);
	pभाग_only = cur_pll.base.n == n_पूर्णांक && cur_pll.sdm_din == sdm_din &&
		    cur_pll.base.m == pll->m;

	/* need full sequence अगर घड़ी not enabled yet */
	अगर (!gk20a_pllg_is_enabled(&clk->base))
		pभाग_only = false;

	/* split VCO-to-bypass jump in half by setting out भागider 1:2 */
	nvkm_mask(device, GPC2CLK_OUT, GPC2CLK_OUT_VCODIV_MASK,
		  GPC2CLK_OUT_VCODIV2 << GPC2CLK_OUT_VCODIV_SHIFT);
	/* Intentional 2nd ग_लिखो to assure linear भागider operation */
	nvkm_mask(device, GPC2CLK_OUT, GPC2CLK_OUT_VCODIV_MASK,
		  GPC2CLK_OUT_VCODIV2 << GPC2CLK_OUT_VCODIV_SHIFT);
	nvkm_rd32(device, GPC2CLK_OUT);
	udelay(2);

	अगर (pभाग_only) अणु
		u32 old = cur_pll.base.pl;
		u32 new = pll->pl;

		/*
		 * we can करो a glitchless transition only अगर the old and new PL
		 * parameters share at least one bit set to 1. If this is not
		 * the हाल, calculate and program an पूर्णांकerim PL that will allow
		 * us to respect that rule.
		 */
		अगर ((old & new) == 0) अणु
			cur_pll.base.pl = min(old | BIT(ffs(new) - 1),
					      new | BIT(ffs(old) - 1));
			gk20a_pllg_ग_लिखो_mnp(&clk->base, &cur_pll.base);
		पूर्ण

		cur_pll.base.pl = new;
		gk20a_pllg_ग_लिखो_mnp(&clk->base, &cur_pll.base);
	पूर्ण अन्यथा अणु
		/* disable beक्रमe programming अगर more than pभाग changes */
		gm20b_pllg_disable(clk);

		cur_pll.base = *pll;
		cur_pll.base.n = n_पूर्णांक;
		cur_pll.sdm_din = sdm_din;
		gm20b_pllg_ग_लिखो_mnp(clk, &cur_pll);

		ret = gm20b_pllg_enable(clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* restore out भागider 1:1 */
	udelay(2);
	nvkm_mask(device, GPC2CLK_OUT, GPC2CLK_OUT_VCODIV_MASK,
		  GPC2CLK_OUT_VCODIV1 << GPC2CLK_OUT_VCODIV_SHIFT);
	/* Intentional 2nd ग_लिखो to assure linear भागider operation */
	nvkm_mask(device, GPC2CLK_OUT, GPC2CLK_OUT_VCODIV_MASK,
		  GPC2CLK_OUT_VCODIV1 << GPC2CLK_OUT_VCODIV_SHIFT);
	nvkm_rd32(device, GPC2CLK_OUT);

	वापस 0;
पूर्ण

अटल पूर्णांक
gm20b_pllg_program_mnp_slide(काष्ठा gm20b_clk *clk, स्थिर काष्ठा gk20a_pll *pll)
अणु
	काष्ठा gk20a_pll cur_pll;
	पूर्णांक ret;

	अगर (gk20a_pllg_is_enabled(&clk->base)) अणु
		gk20a_pllg_पढ़ो_mnp(&clk->base, &cur_pll);

		/* just करो NDIV slide अगर there is no change to M and PL */
		अगर (pll->m == cur_pll.m && pll->pl == cur_pll.pl)
			वापस gm20b_pllg_slide(clk, pll->n);

		/* slide करोwn to current NDIV_LO */
		cur_pll.n = gk20a_pllg_n_lo(&clk->base, &cur_pll);
		ret = gm20b_pllg_slide(clk, cur_pll.n);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* program MNP with the new घड़ी parameters and new NDIV_LO */
	cur_pll = *pll;
	cur_pll.n = gk20a_pllg_n_lo(&clk->base, &cur_pll);
	ret = gm20b_pllg_program_mnp(clk, &cur_pll);
	अगर (ret)
		वापस ret;

	/* slide up to new NDIV */
	वापस gm20b_pllg_slide(clk, pll->n);
पूर्ण

अटल पूर्णांक
gm20b_clk_calc(काष्ठा nvkm_clk *base, काष्ठा nvkm_cstate *cstate)
अणु
	काष्ठा gm20b_clk *clk = gm20b_clk(base);
	काष्ठा nvkm_subdev *subdev = &base->subdev;
	काष्ठा nvkm_volt *volt = base->subdev.device->volt;
	पूर्णांक ret;

	ret = gk20a_pllg_calc_mnp(&clk->base, cstate->करोमुख्य[nv_clk_src_gpc] *
					     GK20A_CLK_GPC_MDIV, &clk->new_pll);
	अगर (ret)
		वापस ret;

	clk->new_uv = volt->vid[cstate->voltage].uv;
	gm20b_dvfs_calc_det_coeff(clk, clk->new_uv, &clk->new_dvfs);

	nvkm_debug(subdev, "%s uv: %d uv\n", __func__, clk->new_uv);

	वापस 0;
पूर्ण

/*
 * Compute PLL parameters that are always safe क्रम the current voltage
 */
अटल व्योम
gm20b_dvfs_calc_safe_pll(काष्ठा gm20b_clk *clk, काष्ठा gk20a_pll *pll)
अणु
	u32 rate = gk20a_pllg_calc_rate(&clk->base, pll) / KHZ;
	u32 parent_rate = clk->base.parent_rate / KHZ;
	u32 nmin, nsafe;

	/* हटाओ a safe margin of 10% */
	अगर (rate > clk->safe_fmax_vmin)
		rate = rate * (100 - 10) / 100;

	/* gpc2clk */
	rate *= 2;

	nmin = DIV_ROUND_UP(pll->m * clk->base.params->min_vco, parent_rate);
	nsafe = pll->m * rate / (clk->base.parent_rate);

	अगर (nsafe < nmin) अणु
		pll->pl = DIV_ROUND_UP(nmin * parent_rate, pll->m * rate);
		nsafe = nmin;
	पूर्ण

	pll->n = nsafe;
पूर्ण

अटल व्योम
gm20b_dvfs_program_coeff(काष्ठा gm20b_clk *clk, u32 coeff)
अणु
	काष्ठा nvkm_device *device = clk->base.base.subdev.device;

	/* strobe to पढ़ो बाह्यal DFS coefficient */
	nvkm_mask(device, GPC_BCAST_GPCPLL_DVFS2,
		  GPC_BCAST_GPCPLL_DVFS2_DFS_EXT_STROBE_BIT,
		  GPC_BCAST_GPCPLL_DVFS2_DFS_EXT_STROBE_BIT);

	nvkm_mask(device, GPCPLL_DVFS0, GPCPLL_DVFS0_DFS_COEFF_MASK,
		  coeff << GPCPLL_DVFS0_DFS_COEFF_SHIFT);

	udelay(1);
	nvkm_mask(device, GPC_BCAST_GPCPLL_DVFS2,
		  GPC_BCAST_GPCPLL_DVFS2_DFS_EXT_STROBE_BIT, 0);
पूर्ण

अटल व्योम
gm20b_dvfs_program_ext_cal(काष्ठा gm20b_clk *clk, u32 dfs_det_cal)
अणु
	काष्ठा nvkm_device *device = clk->base.base.subdev.device;
	u32 val;

	nvkm_mask(device, GPC_BCAST_GPCPLL_DVFS2, MASK(DFS_DET_RANGE + 1),
		  dfs_det_cal);
	udelay(1);

	val = nvkm_rd32(device, GPCPLL_DVFS1);
	अगर (!(val & BIT(25))) अणु
		/* Use बाह्यal value to overग_लिखो calibration value */
		val |= BIT(25) | BIT(16);
		nvkm_wr32(device, GPCPLL_DVFS1, val);
	पूर्ण
पूर्ण

अटल व्योम
gm20b_dvfs_program_dfs_detection(काष्ठा gm20b_clk *clk,
				 काष्ठा gm20b_clk_dvfs *dvfs)
अणु
	काष्ठा nvkm_device *device = clk->base.base.subdev.device;

	/* strobe to पढ़ो बाह्यal DFS coefficient */
	nvkm_mask(device, GPC_BCAST_GPCPLL_DVFS2,
		  GPC_BCAST_GPCPLL_DVFS2_DFS_EXT_STROBE_BIT,
		  GPC_BCAST_GPCPLL_DVFS2_DFS_EXT_STROBE_BIT);

	nvkm_mask(device, GPCPLL_DVFS0,
		  GPCPLL_DVFS0_DFS_COEFF_MASK | GPCPLL_DVFS0_DFS_DET_MAX_MASK,
		  dvfs->dfs_coeff << GPCPLL_DVFS0_DFS_COEFF_SHIFT |
		  dvfs->dfs_det_max << GPCPLL_DVFS0_DFS_DET_MAX_SHIFT);

	udelay(1);
	nvkm_mask(device, GPC_BCAST_GPCPLL_DVFS2,
		  GPC_BCAST_GPCPLL_DVFS2_DFS_EXT_STROBE_BIT, 0);

	gm20b_dvfs_program_ext_cal(clk, dvfs->dfs_ext_cal);
पूर्ण

अटल पूर्णांक
gm20b_clk_prog(काष्ठा nvkm_clk *base)
अणु
	काष्ठा gm20b_clk *clk = gm20b_clk(base);
	u32 cur_freq;
	पूर्णांक ret;

	/* No change in DVFS settings? */
	अगर (clk->uv == clk->new_uv)
		जाओ prog;

	/*
	 * Interim step क्रम changing DVFS detection settings: low enough
	 * frequency to be safe at at DVFS coeff = 0.
	 *
	 * 1. If voltage is increasing:
	 * - safe frequency target matches the lowest - old - frequency
	 * - DVFS settings are still old
	 * - Voltage alपढ़ोy increased to new level by volt, but maximum
	 *   detection limit assures PLL output reमुख्यs under F/V curve
	 *
	 * 2. If voltage is decreasing:
	 * - safe frequency target matches the lowest - new - frequency
	 * - DVFS settings are still old
	 * - Voltage is also old, it will be lowered by volt afterwards
	 *
	 * Interim step can be skipped अगर old frequency is below safe minimum,
	 * i.e., it is low enough to be safe at any voltage in operating range
	 * with zero DVFS coefficient.
	 */
	cur_freq = nvkm_clk_पढ़ो(&clk->base.base, nv_clk_src_gpc);
	अगर (cur_freq > clk->safe_fmax_vmin) अणु
		काष्ठा gk20a_pll pll_safe;

		अगर (clk->uv < clk->new_uv)
			/* voltage will उठाओ: safe frequency is current one */
			pll_safe = clk->base.pll;
		अन्यथा
			/* voltage will drop: safe frequency is new one */
			pll_safe = clk->new_pll;

		gm20b_dvfs_calc_safe_pll(clk, &pll_safe);
		ret = gm20b_pllg_program_mnp_slide(clk, &pll_safe);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * DVFS detection settings transition:
	 * - Set DVFS coefficient zero
	 * - Set calibration level to new voltage
	 * - Set DVFS coefficient to match new voltage
	 */
	gm20b_dvfs_program_coeff(clk, 0);
	gm20b_dvfs_program_ext_cal(clk, clk->new_dvfs.dfs_ext_cal);
	gm20b_dvfs_program_coeff(clk, clk->new_dvfs.dfs_coeff);
	gm20b_dvfs_program_dfs_detection(clk, &clk->new_dvfs);

prog:
	clk->uv = clk->new_uv;
	clk->dvfs = clk->new_dvfs;
	clk->base.pll = clk->new_pll;

	वापस gm20b_pllg_program_mnp_slide(clk, &clk->base.pll);
पूर्ण

अटल काष्ठा nvkm_pstate
gm20b_pstates[] = अणु
	अणु
		.base = अणु
			.करोमुख्य[nv_clk_src_gpc] = 76800,
			.voltage = 0,
		पूर्ण,
	पूर्ण,
	अणु
		.base = अणु
			.करोमुख्य[nv_clk_src_gpc] = 153600,
			.voltage = 1,
		पूर्ण,
	पूर्ण,
	अणु
		.base = अणु
			.करोमुख्य[nv_clk_src_gpc] = 230400,
			.voltage = 2,
		पूर्ण,
	पूर्ण,
	अणु
		.base = अणु
			.करोमुख्य[nv_clk_src_gpc] = 307200,
			.voltage = 3,
		पूर्ण,
	पूर्ण,
	अणु
		.base = अणु
			.करोमुख्य[nv_clk_src_gpc] = 384000,
			.voltage = 4,
		पूर्ण,
	पूर्ण,
	अणु
		.base = अणु
			.करोमुख्य[nv_clk_src_gpc] = 460800,
			.voltage = 5,
		पूर्ण,
	पूर्ण,
	अणु
		.base = अणु
			.करोमुख्य[nv_clk_src_gpc] = 537600,
			.voltage = 6,
		पूर्ण,
	पूर्ण,
	अणु
		.base = अणु
			.करोमुख्य[nv_clk_src_gpc] = 614400,
			.voltage = 7,
		पूर्ण,
	पूर्ण,
	अणु
		.base = अणु
			.करोमुख्य[nv_clk_src_gpc] = 691200,
			.voltage = 8,
		पूर्ण,
	पूर्ण,
	अणु
		.base = अणु
			.करोमुख्य[nv_clk_src_gpc] = 768000,
			.voltage = 9,
		पूर्ण,
	पूर्ण,
	अणु
		.base = अणु
			.करोमुख्य[nv_clk_src_gpc] = 844800,
			.voltage = 10,
		पूर्ण,
	पूर्ण,
	अणु
		.base = अणु
			.करोमुख्य[nv_clk_src_gpc] = 921600,
			.voltage = 11,
		पूर्ण,
	पूर्ण,
	अणु
		.base = अणु
			.करोमुख्य[nv_clk_src_gpc] = 998400,
			.voltage = 12,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम
gm20b_clk_fini(काष्ठा nvkm_clk *base)
अणु
	काष्ठा nvkm_device *device = base->subdev.device;
	काष्ठा gm20b_clk *clk = gm20b_clk(base);

	/* slide to VCO min */
	अगर (gk20a_pllg_is_enabled(&clk->base)) अणु
		काष्ठा gk20a_pll pll;
		u32 n_lo;

		gk20a_pllg_पढ़ो_mnp(&clk->base, &pll);
		n_lo = gk20a_pllg_n_lo(&clk->base, &pll);
		gm20b_pllg_slide(clk, n_lo);
	पूर्ण

	gm20b_pllg_disable(clk);

	/* set IDDQ */
	nvkm_mask(device, GPCPLL_CFG, GPCPLL_CFG_IDDQ, 1);
पूर्ण

अटल पूर्णांक
gm20b_clk_init_dvfs(काष्ठा gm20b_clk *clk)
अणु
	काष्ठा nvkm_subdev *subdev = &clk->base.base.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	bool fused = clk->uvdet_offs && clk->uvdet_slope;
	अटल स्थिर s32 ADC_SLOPE_UV = 10000; /* शेष ADC detection slope */
	u32 data;
	पूर्णांक ret;

	/* Enable NA DVFS */
	nvkm_mask(device, GPCPLL_DVFS1, GPCPLL_DVFS1_EN_DFS_BIT,
		  GPCPLL_DVFS1_EN_DFS_BIT);

	/* Set VCO_CTRL */
	अगर (clk->dvfs_params->vco_ctrl)
		nvkm_mask(device, GPCPLL_CFG3, GPCPLL_CFG3_VCO_CTRL_MASK,
		      clk->dvfs_params->vco_ctrl << GPCPLL_CFG3_VCO_CTRL_SHIFT);

	अगर (fused) अणु
		/* Start पूर्णांकernal calibration, but ignore results */
		nvkm_mask(device, GPCPLL_DVFS1, GPCPLL_DVFS1_EN_DFS_CAL_BIT,
			  GPCPLL_DVFS1_EN_DFS_CAL_BIT);

		/* got uvdev parameters from fuse, skip calibration */
		जाओ calibrated;
	पूर्ण

	/*
	 * If calibration parameters are not fused, start पूर्णांकernal calibration,
	 * रुको क्रम completion, and use results aदीर्घ with शेष slope to
	 * calculate ADC offset during boot.
	 */
	nvkm_mask(device, GPCPLL_DVFS1, GPCPLL_DVFS1_EN_DFS_CAL_BIT,
			  GPCPLL_DVFS1_EN_DFS_CAL_BIT);

	/* Wait क्रम पूर्णांकernal calibration करोne (spec < 2us). */
	ret = nvkm_रुको_usec(device, 10, GPCPLL_DVFS1,
			     GPCPLL_DVFS1_DFS_CAL_DONE_BIT,
			     GPCPLL_DVFS1_DFS_CAL_DONE_BIT);
	अगर (ret < 0) अणु
		nvkm_error(subdev, "GPCPLL calibration timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	data = nvkm_rd32(device, GPCPLL_CFG3) >>
			 GPCPLL_CFG3_PLL_DFS_TESTOUT_SHIFT;
	data &= MASK(GPCPLL_CFG3_PLL_DFS_TESTOUT_WIDTH);

	clk->uvdet_slope = ADC_SLOPE_UV;
	clk->uvdet_offs = ((s32)clk->uv) - data * ADC_SLOPE_UV;

	nvkm_debug(subdev, "calibrated DVFS parameters: offs %d, slope %d\n",
		   clk->uvdet_offs, clk->uvdet_slope);

calibrated:
	/* Compute and apply initial DVFS parameters */
	gm20b_dvfs_calc_det_coeff(clk, clk->uv, &clk->dvfs);
	gm20b_dvfs_program_coeff(clk, 0);
	gm20b_dvfs_program_ext_cal(clk, clk->dvfs.dfs_ext_cal);
	gm20b_dvfs_program_coeff(clk, clk->dvfs.dfs_coeff);
	gm20b_dvfs_program_dfs_detection(clk, &clk->new_dvfs);

	वापस 0;
पूर्ण

/* Forward declaration to detect speeकरो >=1 in gm20b_clk_init() */
अटल स्थिर काष्ठा nvkm_clk_func gm20b_clk;

अटल पूर्णांक
gm20b_clk_init(काष्ठा nvkm_clk *base)
अणु
	काष्ठा gk20a_clk *clk = gk20a_clk(base);
	काष्ठा nvkm_subdev *subdev = &clk->base.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	पूर्णांक ret;
	u32 data;

	/* get out from IDDQ */
	nvkm_mask(device, GPCPLL_CFG, GPCPLL_CFG_IDDQ, 0);
	nvkm_rd32(device, GPCPLL_CFG);
	udelay(5);

	nvkm_mask(device, GPC2CLK_OUT, GPC2CLK_OUT_INIT_MASK,
		  GPC2CLK_OUT_INIT_VAL);

	/* Set the global bypass control to VCO */
	nvkm_mask(device, BYPASSCTRL_SYS,
	       MASK(BYPASSCTRL_SYS_GPCPLL_WIDTH) << BYPASSCTRL_SYS_GPCPLL_SHIFT,
	       0);

	ret = gk20a_clk_setup_slide(clk);
	अगर (ret)
		वापस ret;

	/* If not fused, set RAM SVOP PDP data 0x2, and enable fuse override */
	data = nvkm_rd32(device, 0x021944);
	अगर (!(data & 0x3)) अणु
		data |= 0x2;
		nvkm_wr32(device, 0x021944, data);

		data = nvkm_rd32(device, 0x021948);
		data |=  0x1;
		nvkm_wr32(device, 0x021948, data);
	पूर्ण

	/* Disable idle slow करोwn  */
	nvkm_mask(device, 0x20160, 0x003f0000, 0x0);

	/* speeकरो >= 1? */
	अगर (clk->base.func == &gm20b_clk) अणु
		काष्ठा gm20b_clk *_clk = gm20b_clk(base);
		काष्ठा nvkm_volt *volt = device->volt;

		/* Get current voltage */
		_clk->uv = nvkm_volt_get(volt);

		/* Initialize DVFS */
		ret = gm20b_clk_init_dvfs(_clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Start with lowest frequency */
	base->func->calc(base, &base->func->pstates[0].base);
	ret = base->func->prog(base);
	अगर (ret) अणु
		nvkm_error(subdev, "cannot initialize clock\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_clk_func
gm20b_clk_speeकरो0 = अणु
	.init = gm20b_clk_init,
	.fini = gk20a_clk_fini,
	.पढ़ो = gk20a_clk_पढ़ो,
	.calc = gk20a_clk_calc,
	.prog = gk20a_clk_prog,
	.tidy = gk20a_clk_tidy,
	.pstates = gm20b_pstates,
	/* Speeकरो 0 only supports 12 voltages */
	.nr_pstates = ARRAY_SIZE(gm20b_pstates) - 1,
	.करोमुख्यs = अणु
		अणु nv_clk_src_crystal, 0xff पूर्ण,
		अणु nv_clk_src_gpc, 0xff, 0, "core", GK20A_CLK_GPC_MDIV पूर्ण,
		अणु nv_clk_src_max पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_clk_func
gm20b_clk = अणु
	.init = gm20b_clk_init,
	.fini = gm20b_clk_fini,
	.पढ़ो = gk20a_clk_पढ़ो,
	.calc = gm20b_clk_calc,
	.prog = gm20b_clk_prog,
	.tidy = gk20a_clk_tidy,
	.pstates = gm20b_pstates,
	.nr_pstates = ARRAY_SIZE(gm20b_pstates),
	.करोमुख्यs = अणु
		अणु nv_clk_src_crystal, 0xff पूर्ण,
		अणु nv_clk_src_gpc, 0xff, 0, "core", GK20A_CLK_GPC_MDIV पूर्ण,
		अणु nv_clk_src_max पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक
gm20b_clk_new_speeकरो0(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		      काष्ठा nvkm_clk **pclk)
अणु
	काष्ठा gk20a_clk *clk;
	पूर्णांक ret;

	clk = kzalloc(माप(*clk), GFP_KERNEL);
	अगर (!clk)
		वापस -ENOMEM;
	*pclk = &clk->base;

	ret = gk20a_clk_ctor(device, type, inst, &gm20b_clk_speeकरो0, &gm20b_pllg_params, clk);
	clk->pl_to_भाग = pl_to_भाग;
	clk->भाग_प्रकारo_pl = भाग_प्रकारo_pl;
	वापस ret;
पूर्ण

/* FUSE रेजिस्टर */
#घोषणा FUSE_RESERVED_CALIB0	0x204
#घोषणा FUSE_RESERVED_CALIB0_INTERCEPT_FRAC_SHIFT	0
#घोषणा FUSE_RESERVED_CALIB0_INTERCEPT_FRAC_WIDTH	4
#घोषणा FUSE_RESERVED_CALIB0_INTERCEPT_INT_SHIFT	4
#घोषणा FUSE_RESERVED_CALIB0_INTERCEPT_INT_WIDTH	10
#घोषणा FUSE_RESERVED_CALIB0_SLOPE_FRAC_SHIFT		14
#घोषणा FUSE_RESERVED_CALIB0_SLOPE_FRAC_WIDTH		10
#घोषणा FUSE_RESERVED_CALIB0_SLOPE_INT_SHIFT		24
#घोषणा FUSE_RESERVED_CALIB0_SLOPE_INT_WIDTH		6
#घोषणा FUSE_RESERVED_CALIB0_FUSE_REV_SHIFT		30
#घोषणा FUSE_RESERVED_CALIB0_FUSE_REV_WIDTH		2

अटल पूर्णांक
gm20b_clk_init_fused_params(काष्ठा gm20b_clk *clk)
अणु
	काष्ठा nvkm_subdev *subdev = &clk->base.base.subdev;
	u32 val = 0;
	u32 rev = 0;

#अगर IS_ENABLED(CONFIG_ARCH_TEGRA)
	tegra_fuse_पढ़ोl(FUSE_RESERVED_CALIB0, &val);
	rev = (val >> FUSE_RESERVED_CALIB0_FUSE_REV_SHIFT) &
	      MASK(FUSE_RESERVED_CALIB0_FUSE_REV_WIDTH);
#पूर्ण_अगर

	/* No fused parameters, we will calibrate later */
	अगर (rev == 0)
		वापस -EINVAL;

	/* Integer part in mV + fractional part in uV */
	clk->uvdet_slope = ((val >> FUSE_RESERVED_CALIB0_SLOPE_INT_SHIFT) &
			MASK(FUSE_RESERVED_CALIB0_SLOPE_INT_WIDTH)) * 1000 +
			((val >> FUSE_RESERVED_CALIB0_SLOPE_FRAC_SHIFT) &
			MASK(FUSE_RESERVED_CALIB0_SLOPE_FRAC_WIDTH));

	/* Integer part in mV + fractional part in 100uV */
	clk->uvdet_offs = ((val >> FUSE_RESERVED_CALIB0_INTERCEPT_INT_SHIFT) &
			MASK(FUSE_RESERVED_CALIB0_INTERCEPT_INT_WIDTH)) * 1000 +
			((val >> FUSE_RESERVED_CALIB0_INTERCEPT_FRAC_SHIFT) &
			 MASK(FUSE_RESERVED_CALIB0_INTERCEPT_FRAC_WIDTH)) * 100;

	nvkm_debug(subdev, "fused calibration data: slope %d, offs %d\n",
		   clk->uvdet_slope, clk->uvdet_offs);
	वापस 0;
पूर्ण

अटल पूर्णांक
gm20b_clk_init_safe_fmax(काष्ठा gm20b_clk *clk)
अणु
	काष्ठा nvkm_subdev *subdev = &clk->base.base.subdev;
	काष्ठा nvkm_volt *volt = subdev->device->volt;
	काष्ठा nvkm_pstate *pstates = clk->base.base.func->pstates;
	पूर्णांक nr_pstates = clk->base.base.func->nr_pstates;
	पूर्णांक vmin, id = 0;
	u32 fmax = 0;
	पूर्णांक i;

	/* find lowest voltage we can use */
	vmin = volt->vid[0].uv;
	क्रम (i = 1; i < volt->vid_nr; i++) अणु
		अगर (volt->vid[i].uv <= vmin) अणु
			vmin = volt->vid[i].uv;
			id = volt->vid[i].vid;
		पूर्ण
	पूर्ण

	/* find max frequency at this voltage */
	क्रम (i = 0; i < nr_pstates; i++)
		अगर (pstates[i].base.voltage == id)
			fmax = max(fmax,
				   pstates[i].base.करोमुख्य[nv_clk_src_gpc]);

	अगर (!fmax) अणु
		nvkm_error(subdev, "failed to evaluate safe fmax\n");
		वापस -EINVAL;
	पूर्ण

	/* we are safe at 90% of the max frequency */
	clk->safe_fmax_vmin = fmax * (100 - 10) / 100;
	nvkm_debug(subdev, "safe fmax @ vmin = %u Khz\n", clk->safe_fmax_vmin);

	वापस 0;
पूर्ण

पूर्णांक
gm20b_clk_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_clk **pclk)
अणु
	काष्ठा nvkm_device_tegra *tdev = device->func->tegra(device);
	काष्ठा gm20b_clk *clk;
	काष्ठा nvkm_subdev *subdev;
	काष्ठा gk20a_clk_pllg_params *clk_params;
	पूर्णांक ret;

	/* Speeकरो 0 GPUs cannot use noise-aware PLL */
	अगर (tdev->gpu_speeकरो_id == 0)
		वापस gm20b_clk_new_speeकरो0(device, type, inst, pclk);

	/* Speeकरो >= 1, use NAPLL */
	clk = kzalloc(माप(*clk) + माप(*clk_params), GFP_KERNEL);
	अगर (!clk)
		वापस -ENOMEM;
	*pclk = &clk->base.base;
	subdev = &clk->base.base.subdev;

	/* duplicate the घड़ी parameters since we will patch them below */
	clk_params = (व्योम *) (clk + 1);
	*clk_params = gm20b_pllg_params;
	ret = gk20a_clk_ctor(device, type, inst, &gm20b_clk, clk_params, &clk->base);
	अगर (ret)
		वापस ret;

	/*
	 * NAPLL can only work with max_u, clamp the m range so
	 * gk20a_pllg_calc_mnp always uses it
	 */
	clk_params->max_m = clk_params->min_m = DIV_ROUND_UP(clk_params->max_u,
						(clk->base.parent_rate / KHZ));
	अगर (clk_params->max_m == 0) अणु
		nvkm_warn(subdev, "cannot use NAPLL, using legacy clock...\n");
		kमुक्त(clk);
		वापस gm20b_clk_new_speeकरो0(device, type, inst, pclk);
	पूर्ण

	clk->base.pl_to_भाग = pl_to_भाग;
	clk->base.भाग_प्रकारo_pl = भाग_प्रकारo_pl;

	clk->dvfs_params = &gm20b_dvfs_params;

	ret = gm20b_clk_init_fused_params(clk);
	/*
	 * we will calibrate during init - should never happen on
	 * prod parts
	 */
	अगर (ret)
		nvkm_warn(subdev, "no fused calibration parameters\n");

	ret = gm20b_clk_init_safe_fmax(clk);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण
