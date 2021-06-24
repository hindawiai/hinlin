<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/media/i2c/ccs-pll.c
 *
 * Generic MIPI CCS/SMIA/SMIA++ PLL calculator
 *
 * Copyright (C) 2020 Intel Corporation
 * Copyright (C) 2011--2012 Nokia Corporation
 * Contact: Sakari Ailus <sakari.ailus@linux.पूर्णांकel.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/gcd.h>
#समावेश <linux/lcm.h>
#समावेश <linux/module.h>

#समावेश "ccs-pll.h"

/* Return an even number or one. */
अटल अंतरभूत u32 clk_भाग_even(u32 a)
अणु
	वापस max_t(u32, 1, a & ~1);
पूर्ण

/* Return an even number or one. */
अटल अंतरभूत u32 clk_भाग_even_up(u32 a)
अणु
	अगर (a == 1)
		वापस 1;
	वापस (a + 1) & ~1;
पूर्ण

अटल अंतरभूत u32 is_one_or_even(u32 a)
अणु
	अगर (a == 1)
		वापस 1;
	अगर (a & 1)
		वापस 0;

	वापस 1;
पूर्ण

अटल अंतरभूत u32 one_or_more(u32 a)
अणु
	वापस a ?: 1;
पूर्ण

अटल पूर्णांक bounds_check(काष्ठा device *dev, u32 val,
			u32 min, u32 max, स्थिर अक्षर *prefix,
			अक्षर *str)
अणु
	अगर (val >= min && val <= max)
		वापस 0;

	dev_dbg(dev, "%s_%s out of bounds: %d (%d--%d)\n", prefix,
		str, val, min, max);

	वापस -EINVAL;
पूर्ण

#घोषणा PLL_OP 1
#घोषणा PLL_VT 2

अटल स्थिर अक्षर *pll_string(अचिन्हित पूर्णांक which)
अणु
	चयन (which) अणु
	हाल PLL_OP:
		वापस "op";
	हाल PLL_VT:
		वापस "vt";
	पूर्ण

	वापस शून्य;
पूर्ण

#घोषणा PLL_FL(f) CCS_PLL_FLAG_##f

अटल व्योम prपूर्णांक_pll(काष्ठा device *dev, काष्ठा ccs_pll *pll)
अणु
	स्थिर काष्ठा अणु
		काष्ठा ccs_pll_branch_fr *fr;
		काष्ठा ccs_pll_branch_bk *bk;
		अचिन्हित पूर्णांक which;
	पूर्ण branches[] = अणु
		अणु &pll->vt_fr, &pll->vt_bk, PLL_VT पूर्ण,
		अणु &pll->op_fr, &pll->op_bk, PLL_OP पूर्ण
	पूर्ण, *br;
	अचिन्हित पूर्णांक i;

	dev_dbg(dev, "ext_clk_freq_hz\t\t%u\n", pll->ext_clk_freq_hz);

	क्रम (i = 0, br = branches; i < ARRAY_SIZE(branches); i++, br++) अणु
		स्थिर अक्षर *s = pll_string(br->which);

		अगर (pll->flags & CCS_PLL_FLAG_DUAL_PLL ||
		    br->which == PLL_VT) अणु
			dev_dbg(dev, "%s_pre_pll_clk_div\t\t%u\n",  s,
				br->fr->pre_pll_clk_भाग);
			dev_dbg(dev, "%s_pll_multiplier\t\t%u\n",  s,
				br->fr->pll_multiplier);

			dev_dbg(dev, "%s_pll_ip_clk_freq_hz\t%u\n", s,
				br->fr->pll_ip_clk_freq_hz);
			dev_dbg(dev, "%s_pll_op_clk_freq_hz\t%u\n", s,
				br->fr->pll_op_clk_freq_hz);
		पूर्ण

		अगर (!(pll->flags & CCS_PLL_FLAG_NO_OP_CLOCKS) ||
		    br->which == PLL_VT) अणु
			dev_dbg(dev, "%s_sys_clk_div\t\t%u\n",  s,
				br->bk->sys_clk_भाग);
			dev_dbg(dev, "%s_pix_clk_div\t\t%u\n", s,
				br->bk->pix_clk_भाग);

			dev_dbg(dev, "%s_sys_clk_freq_hz\t%u\n", s,
				br->bk->sys_clk_freq_hz);
			dev_dbg(dev, "%s_pix_clk_freq_hz\t%u\n", s,
				br->bk->pix_clk_freq_hz);
		पूर्ण
	पूर्ण

	dev_dbg(dev, "pixel rate in pixel array:\t%u\n",
		pll->pixel_rate_pixel_array);
	dev_dbg(dev, "pixel rate on CSI-2 bus:\t%u\n",
		pll->pixel_rate_csi);

	dev_dbg(dev, "flags%s%s%s%s%s%s%s%s%s\n",
		pll->flags & PLL_FL(LANE_SPEED_MODEL) ? " lane-speed" : "",
		pll->flags & PLL_FL(LINK_DECOUPLED) ? " link-decoupled" : "",
		pll->flags & PLL_FL(EXT_IP_PLL_DIVIDER) ?
		" ext-ip-pll-divider" : "",
		pll->flags & PLL_FL(FLEXIBLE_OP_PIX_CLK_DIV) ?
		" flexible-op-pix-div" : "",
		pll->flags & PLL_FL(FIFO_DERATING) ? " fifo-derating" : "",
		pll->flags & PLL_FL(FIFO_OVERRATING) ? " fifo-overrating" : "",
		pll->flags & PLL_FL(DUAL_PLL) ? " dual-pll" : "",
		pll->flags & PLL_FL(OP_SYS_DDR) ? " op-sys-ddr" : "",
		pll->flags & PLL_FL(OP_PIX_DDR) ? " op-pix-ddr" : "");
पूर्ण

अटल u32 op_sys_ddr(u32 flags)
अणु
	वापस flags & CCS_PLL_FLAG_OP_SYS_DDR ? 1 : 0;
पूर्ण

अटल u32 op_pix_ddr(u32 flags)
अणु
	वापस flags & CCS_PLL_FLAG_OP_PIX_DDR ? 1 : 0;
पूर्ण

अटल पूर्णांक check_fr_bounds(काष्ठा device *dev,
			   स्थिर काष्ठा ccs_pll_limits *lim,
			   काष्ठा ccs_pll *pll, अचिन्हित पूर्णांक which)
अणु
	स्थिर काष्ठा ccs_pll_branch_limits_fr *lim_fr;
	काष्ठा ccs_pll_branch_fr *pll_fr;
	स्थिर अक्षर *s = pll_string(which);
	पूर्णांक rval;

	अगर (which == PLL_OP) अणु
		lim_fr = &lim->op_fr;
		pll_fr = &pll->op_fr;
	पूर्ण अन्यथा अणु
		lim_fr = &lim->vt_fr;
		pll_fr = &pll->vt_fr;
	पूर्ण

	rval = bounds_check(dev, pll_fr->pre_pll_clk_भाग,
			    lim_fr->min_pre_pll_clk_भाग,
			    lim_fr->max_pre_pll_clk_भाग, s, "pre_pll_clk_div");

	अगर (!rval)
		rval = bounds_check(dev, pll_fr->pll_ip_clk_freq_hz,
				    lim_fr->min_pll_ip_clk_freq_hz,
				    lim_fr->max_pll_ip_clk_freq_hz,
				    s, "pll_ip_clk_freq_hz");
	अगर (!rval)
		rval = bounds_check(dev, pll_fr->pll_multiplier,
				    lim_fr->min_pll_multiplier,
				    lim_fr->max_pll_multiplier,
				    s, "pll_multiplier");
	अगर (!rval)
		rval = bounds_check(dev, pll_fr->pll_op_clk_freq_hz,
				    lim_fr->min_pll_op_clk_freq_hz,
				    lim_fr->max_pll_op_clk_freq_hz,
				    s, "pll_op_clk_freq_hz");

	वापस rval;
पूर्ण

अटल पूर्णांक check_bk_bounds(काष्ठा device *dev,
			   स्थिर काष्ठा ccs_pll_limits *lim,
			   काष्ठा ccs_pll *pll, अचिन्हित पूर्णांक which)
अणु
	स्थिर काष्ठा ccs_pll_branch_limits_bk *lim_bk;
	काष्ठा ccs_pll_branch_bk *pll_bk;
	स्थिर अक्षर *s = pll_string(which);
	पूर्णांक rval;

	अगर (which == PLL_OP) अणु
		अगर (pll->flags & CCS_PLL_FLAG_NO_OP_CLOCKS)
			वापस 0;

		lim_bk = &lim->op_bk;
		pll_bk = &pll->op_bk;
	पूर्ण अन्यथा अणु
		lim_bk = &lim->vt_bk;
		pll_bk = &pll->vt_bk;
	पूर्ण

	rval = bounds_check(dev, pll_bk->sys_clk_भाग,
			    lim_bk->min_sys_clk_भाग,
			    lim_bk->max_sys_clk_भाग, s, "op_sys_clk_div");
	अगर (!rval)
		rval = bounds_check(dev, pll_bk->sys_clk_freq_hz,
				    lim_bk->min_sys_clk_freq_hz,
				    lim_bk->max_sys_clk_freq_hz,
				    s, "sys_clk_freq_hz");
	अगर (!rval)
		rval = bounds_check(dev, pll_bk->sys_clk_भाग,
				    lim_bk->min_sys_clk_भाग,
				    lim_bk->max_sys_clk_भाग,
				    s, "sys_clk_div");
	अगर (!rval)
		rval = bounds_check(dev, pll_bk->pix_clk_freq_hz,
				    lim_bk->min_pix_clk_freq_hz,
				    lim_bk->max_pix_clk_freq_hz,
				    s, "pix_clk_freq_hz");

	वापस rval;
पूर्ण

अटल पूर्णांक check_ext_bounds(काष्ठा device *dev, काष्ठा ccs_pll *pll)
अणु
	अगर (!(pll->flags & CCS_PLL_FLAG_FIFO_DERATING) &&
	    pll->pixel_rate_pixel_array > pll->pixel_rate_csi) अणु
		dev_dbg(dev, "device does not support derating\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!(pll->flags & CCS_PLL_FLAG_FIFO_OVERRATING) &&
	    pll->pixel_rate_pixel_array < pll->pixel_rate_csi) अणु
		dev_dbg(dev, "device does not support overrating\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
ccs_pll_find_vt_sys_भाग(काष्ठा device *dev, स्थिर काष्ठा ccs_pll_limits *lim,
			काष्ठा ccs_pll *pll, काष्ठा ccs_pll_branch_fr *pll_fr,
			u16 min_vt_भाग, u16 max_vt_भाग,
			u16 *min_sys_भाग, u16 *max_sys_भाग)
अणु
	/*
	 * Find limits क्रम sys_clk_भाग. Not all values are possible with all
	 * values of pix_clk_भाग.
	 */
	*min_sys_भाग = lim->vt_bk.min_sys_clk_भाग;
	dev_dbg(dev, "min_sys_div: %u\n", *min_sys_भाग);
	*min_sys_भाग = max_t(u16, *min_sys_भाग,
			     DIV_ROUND_UP(min_vt_भाग,
					  lim->vt_bk.max_pix_clk_भाग));
	dev_dbg(dev, "min_sys_div: max_vt_pix_clk_div: %u\n", *min_sys_भाग);
	*min_sys_भाग = max_t(u16, *min_sys_भाग,
			     pll_fr->pll_op_clk_freq_hz
			     / lim->vt_bk.max_sys_clk_freq_hz);
	dev_dbg(dev, "min_sys_div: max_pll_op_clk_freq_hz: %u\n", *min_sys_भाग);
	*min_sys_भाग = clk_भाग_even_up(*min_sys_भाग);
	dev_dbg(dev, "min_sys_div: one or even: %u\n", *min_sys_भाग);

	*max_sys_भाग = lim->vt_bk.max_sys_clk_भाग;
	dev_dbg(dev, "max_sys_div: %u\n", *max_sys_भाग);
	*max_sys_भाग = min_t(u16, *max_sys_भाग,
			     DIV_ROUND_UP(max_vt_भाग,
					  lim->vt_bk.min_pix_clk_भाग));
	dev_dbg(dev, "max_sys_div: min_vt_pix_clk_div: %u\n", *max_sys_भाग);
	*max_sys_भाग = min_t(u16, *max_sys_भाग,
			     DIV_ROUND_UP(pll_fr->pll_op_clk_freq_hz,
					  lim->vt_bk.min_pix_clk_freq_hz));
	dev_dbg(dev, "max_sys_div: min_vt_pix_clk_freq_hz: %u\n", *max_sys_भाग);
पूर्ण

#घोषणा CPHY_CONST		7
#घोषणा DPHY_CONST		16
#घोषणा PHY_CONST_DIV		16

अटल अंतरभूत पूर्णांक
__ccs_pll_calculate_vt_tree(काष्ठा device *dev,
			    स्थिर काष्ठा ccs_pll_limits *lim,
			    काष्ठा ccs_pll *pll, u32 mul, u32 भाग)
अणु
	स्थिर काष्ठा ccs_pll_branch_limits_fr *lim_fr = &lim->vt_fr;
	स्थिर काष्ठा ccs_pll_branch_limits_bk *lim_bk = &lim->vt_bk;
	काष्ठा ccs_pll_branch_fr *pll_fr = &pll->vt_fr;
	काष्ठा ccs_pll_branch_bk *pll_bk = &pll->vt_bk;
	u32 more_mul;
	u16 best_pix_भाग = लघु_उच्च >> 1, best_भाग;
	u16 vt_भाग, min_sys_भाग, max_sys_भाग, sys_भाग;

	pll_fr->pll_ip_clk_freq_hz =
		pll->ext_clk_freq_hz / pll_fr->pre_pll_clk_भाग;

	dev_dbg(dev, "vt_pll_ip_clk_freq_hz %u\n", pll_fr->pll_ip_clk_freq_hz);

	more_mul = one_or_more(DIV_ROUND_UP(lim_fr->min_pll_op_clk_freq_hz,
					    pll_fr->pll_ip_clk_freq_hz * mul));

	dev_dbg(dev, "more_mul: %u\n", more_mul);
	more_mul *= DIV_ROUND_UP(lim_fr->min_pll_multiplier, mul * more_mul);
	dev_dbg(dev, "more_mul2: %u\n", more_mul);

	pll_fr->pll_multiplier = mul * more_mul;

	अगर (pll_fr->pll_multiplier * pll_fr->pll_ip_clk_freq_hz >
	    lim_fr->max_pll_op_clk_freq_hz)
		वापस -EINVAL;

	pll_fr->pll_op_clk_freq_hz =
		pll_fr->pll_ip_clk_freq_hz * pll_fr->pll_multiplier;

	vt_भाग = भाग * more_mul;

	ccs_pll_find_vt_sys_भाग(dev, lim, pll, pll_fr, vt_भाग, vt_भाग,
				&min_sys_भाग, &max_sys_भाग);

	max_sys_भाग = (vt_भाग & 1) ? 1 : max_sys_भाग;

	dev_dbg(dev, "vt min/max_sys_div: %u,%u\n", min_sys_भाग, max_sys_भाग);

	क्रम (sys_भाग = min_sys_भाग; sys_भाग <= max_sys_भाग;
	     sys_भाग += 2 - (sys_भाग & 1)) अणु
		u16 pix_भाग;

		अगर (vt_भाग % sys_भाग)
			जारी;

		pix_भाग = vt_भाग / sys_भाग;

		अगर (pix_भाग < lim_bk->min_pix_clk_भाग ||
		    pix_भाग > lim_bk->max_pix_clk_भाग) अणु
			dev_dbg(dev,
				"pix_div %u too small or too big (%u--%u)\n",
				pix_भाग,
				lim_bk->min_pix_clk_भाग,
				lim_bk->max_pix_clk_भाग);
			जारी;
		पूर्ण

		dev_dbg(dev, "sys/pix/best_pix: %u,%u,%u\n", sys_भाग, pix_भाग,
			best_pix_भाग);

		अगर (pix_भाग * sys_भाग <= best_pix_भाग) अणु
			best_pix_भाग = pix_भाग;
			best_भाग = pix_भाग * sys_भाग;
		पूर्ण
	पूर्ण
	अगर (best_pix_भाग == लघु_उच्च >> 1)
		वापस -EINVAL;

	pll_bk->sys_clk_भाग = best_भाग / best_pix_भाग;
	pll_bk->pix_clk_भाग = best_pix_भाग;

	pll_bk->sys_clk_freq_hz =
		pll_fr->pll_op_clk_freq_hz / pll_bk->sys_clk_भाग;
	pll_bk->pix_clk_freq_hz =
		pll_bk->sys_clk_freq_hz / pll_bk->pix_clk_भाग;

	pll->pixel_rate_pixel_array =
		pll_bk->pix_clk_freq_hz * pll->vt_lanes;

	वापस 0;
पूर्ण

अटल पूर्णांक ccs_pll_calculate_vt_tree(काष्ठा device *dev,
				     स्थिर काष्ठा ccs_pll_limits *lim,
				     काष्ठा ccs_pll *pll)
अणु
	स्थिर काष्ठा ccs_pll_branch_limits_fr *lim_fr = &lim->vt_fr;
	काष्ठा ccs_pll_branch_fr *pll_fr = &pll->vt_fr;
	u16 min_pre_pll_clk_भाग = lim_fr->min_pre_pll_clk_भाग;
	u16 max_pre_pll_clk_भाग = lim_fr->max_pre_pll_clk_भाग;
	u32 pre_mul, pre_भाग;

	pre_भाग = gcd(pll->pixel_rate_csi,
		      pll->ext_clk_freq_hz * pll->vt_lanes);
	pre_mul = pll->pixel_rate_csi / pre_भाग;
	pre_भाग = pll->ext_clk_freq_hz * pll->vt_lanes / pre_भाग;

	/* Make sure PLL input frequency is within limits */
	max_pre_pll_clk_भाग =
		min_t(u16, max_pre_pll_clk_भाग,
		      DIV_ROUND_UP(pll->ext_clk_freq_hz,
				   lim_fr->min_pll_ip_clk_freq_hz));

	min_pre_pll_clk_भाग = max_t(u16, min_pre_pll_clk_भाग,
				    pll->ext_clk_freq_hz /
				    lim_fr->max_pll_ip_clk_freq_hz);

	dev_dbg(dev, "vt min/max_pre_pll_clk_div: %u,%u\n",
		min_pre_pll_clk_भाग, max_pre_pll_clk_भाग);

	क्रम (pll_fr->pre_pll_clk_भाग = min_pre_pll_clk_भाग;
	     pll_fr->pre_pll_clk_भाग <= max_pre_pll_clk_भाग;
	     pll_fr->pre_pll_clk_भाग +=
		     (pll->flags & CCS_PLL_FLAG_EXT_IP_PLL_DIVIDER) ? 1 :
		     2 - (pll_fr->pre_pll_clk_भाग & 1)) अणु
		u32 mul, भाग;
		पूर्णांक rval;

		भाग = gcd(pre_mul * pll_fr->pre_pll_clk_भाग, pre_भाग);
		mul = pre_mul * pll_fr->pre_pll_clk_भाग / भाग;
		भाग = pre_भाग / भाग;

		dev_dbg(dev, "vt pre-div/mul/div: %u,%u,%u\n",
			pll_fr->pre_pll_clk_भाग, mul, भाग);

		rval = __ccs_pll_calculate_vt_tree(dev, lim, pll,
						   mul, भाग);
		अगर (rval)
			जारी;

		rval = check_fr_bounds(dev, lim, pll, PLL_VT);
		अगर (rval)
			जारी;

		rval = check_bk_bounds(dev, lim, pll, PLL_VT);
		अगर (rval)
			जारी;

		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम
ccs_pll_calculate_vt(काष्ठा device *dev, स्थिर काष्ठा ccs_pll_limits *lim,
		     स्थिर काष्ठा ccs_pll_branch_limits_bk *op_lim_bk,
		     काष्ठा ccs_pll *pll, काष्ठा ccs_pll_branch_fr *pll_fr,
		     काष्ठा ccs_pll_branch_bk *op_pll_bk, bool cphy,
		     u32 phy_स्थिर)
अणु
	u16 sys_भाग;
	u16 best_pix_भाग = लघु_उच्च >> 1;
	u16 vt_op_binning_भाग;
	u16 min_vt_भाग, max_vt_भाग, vt_भाग;
	u16 min_sys_भाग, max_sys_भाग;

	अगर (pll->flags & CCS_PLL_FLAG_NO_OP_CLOCKS)
		जाओ out_calc_pixel_rate;

	/*
	 * Find out whether a sensor supports derating. If it करोes not, VT and
	 * OP करोमुख्यs are required to run at the same pixel rate.
	 */
	अगर (!(pll->flags & CCS_PLL_FLAG_FIFO_DERATING)) अणु
		min_vt_भाग =
			op_pll_bk->sys_clk_भाग * op_pll_bk->pix_clk_भाग
			* pll->vt_lanes * phy_स्थिर / pll->op_lanes
			/ (PHY_CONST_DIV << op_pix_ddr(pll->flags));
	पूर्ण अन्यथा अणु
		/*
		 * Some sensors perक्रमm analogue binning and some करो this
		 * digitally. The ones करोing this digitally can be roughly be
		 * found out using this क्रमmula. The ones करोing this digitally
		 * should run at higher घड़ी rate, so smaller भागisor is used
		 * on video timing side.
		 */
		अगर (lim->min_line_length_pck_bin > lim->min_line_length_pck
		    / pll->binning_horizontal)
			vt_op_binning_भाग = pll->binning_horizontal;
		अन्यथा
			vt_op_binning_भाग = 1;
		dev_dbg(dev, "vt_op_binning_div: %u\n", vt_op_binning_भाग);

		/*
		 * Profile 2 supports vt_pix_clk_भाग E [4, 10]
		 *
		 * Horizontal binning can be used as a base क्रम dअगरference in
		 * भागisors. One must make sure that horizontal blanking is
		 * enough to accommodate the CSI-2 sync codes.
		 *
		 * Take scaling factor and number of VT lanes पूर्णांकo account as well.
		 *
		 * Find असलolute limits क्रम the factor of vt भागider.
		 */
		dev_dbg(dev, "scale_m: %u\n", pll->scale_m);
		min_vt_भाग =
			DIV_ROUND_UP(pll->bits_per_pixel
				     * op_pll_bk->sys_clk_भाग * pll->scale_n
				     * pll->vt_lanes * phy_स्थिर,
				     (pll->flags &
				      CCS_PLL_FLAG_LANE_SPEED_MODEL ?
				      pll->csi2.lanes : 1)
				     * vt_op_binning_भाग * pll->scale_m
				     * PHY_CONST_DIV << op_pix_ddr(pll->flags));
	पूर्ण

	/* Find smallest and biggest allowed vt भागisor. */
	dev_dbg(dev, "min_vt_div: %u\n", min_vt_भाग);
	min_vt_भाग = max_t(u16, min_vt_भाग,
			   DIV_ROUND_UP(pll_fr->pll_op_clk_freq_hz,
					lim->vt_bk.max_pix_clk_freq_hz));
	dev_dbg(dev, "min_vt_div: max_vt_pix_clk_freq_hz: %u\n",
		min_vt_भाग);
	min_vt_भाग = max_t(u16, min_vt_भाग, lim->vt_bk.min_pix_clk_भाग
					    * lim->vt_bk.min_sys_clk_भाग);
	dev_dbg(dev, "min_vt_div: min_vt_clk_div: %u\n", min_vt_भाग);

	max_vt_भाग = lim->vt_bk.max_sys_clk_भाग * lim->vt_bk.max_pix_clk_भाग;
	dev_dbg(dev, "max_vt_div: %u\n", max_vt_भाग);
	max_vt_भाग = min_t(u16, max_vt_भाग,
			   DIV_ROUND_UP(pll_fr->pll_op_clk_freq_hz,
				      lim->vt_bk.min_pix_clk_freq_hz));
	dev_dbg(dev, "max_vt_div: min_vt_pix_clk_freq_hz: %u\n",
		max_vt_भाग);

	ccs_pll_find_vt_sys_भाग(dev, lim, pll, pll_fr, min_vt_भाग,
				max_vt_भाग, &min_sys_भाग, &max_sys_भाग);

	/*
	 * Find pix_भाग such that a legal pix_भाग * sys_भाग results
	 * पूर्णांकo a value which is not smaller than भाग, the desired
	 * भागisor.
	 */
	क्रम (vt_भाग = min_vt_भाग; vt_भाग <= max_vt_भाग; vt_भाग++) अणु
		u16 __max_sys_भाग = vt_भाग & 1 ? 1 : max_sys_भाग;

		क्रम (sys_भाग = min_sys_भाग; sys_भाग <= __max_sys_भाग;
		     sys_भाग += 2 - (sys_भाग & 1)) अणु
			u16 pix_भाग;
			u16 rounded_भाग;

			pix_भाग = DIV_ROUND_UP(vt_भाग, sys_भाग);

			अगर (pix_भाग < lim->vt_bk.min_pix_clk_भाग
			    || pix_भाग > lim->vt_bk.max_pix_clk_भाग) अणु
				dev_dbg(dev,
					"pix_div %u too small or too big (%u--%u)\n",
					pix_भाग,
					lim->vt_bk.min_pix_clk_भाग,
					lim->vt_bk.max_pix_clk_भाग);
				जारी;
			पूर्ण

			rounded_भाग = roundup(vt_भाग, best_pix_भाग);

			/* Check अगर this one is better. */
			अगर (pix_भाग * sys_भाग <= rounded_भाग)
				best_pix_भाग = pix_भाग;

			/* Bail out अगर we've alपढ़ोy found the best value. */
			अगर (vt_भाग == rounded_भाग)
				अवरोध;
		पूर्ण
		अगर (best_pix_भाग < लघु_उच्च >> 1)
			अवरोध;
	पूर्ण

	pll->vt_bk.sys_clk_भाग = DIV_ROUND_UP(vt_भाग, best_pix_भाग);
	pll->vt_bk.pix_clk_भाग = best_pix_भाग;

	pll->vt_bk.sys_clk_freq_hz =
		pll_fr->pll_op_clk_freq_hz / pll->vt_bk.sys_clk_भाग;
	pll->vt_bk.pix_clk_freq_hz =
		pll->vt_bk.sys_clk_freq_hz / pll->vt_bk.pix_clk_भाग;

out_calc_pixel_rate:
	pll->pixel_rate_pixel_array =
		pll->vt_bk.pix_clk_freq_hz * pll->vt_lanes;
पूर्ण

/*
 * Heuristically guess the PLL tree क्रम a given common multiplier and
 * भागisor. Begin with the operational timing and जारी to video
 * timing once operational timing has been verअगरied.
 *
 * @mul is the PLL multiplier and @भाग is the common भागisor
 * (pre_pll_clk_भाग and op_sys_clk_भाग combined). The final PLL
 * multiplier will be a multiple of @mul.
 *
 * @वापस Zero on success, error code on error.
 */
अटल पूर्णांक
ccs_pll_calculate_op(काष्ठा device *dev, स्थिर काष्ठा ccs_pll_limits *lim,
		     स्थिर काष्ठा ccs_pll_branch_limits_fr *op_lim_fr,
		     स्थिर काष्ठा ccs_pll_branch_limits_bk *op_lim_bk,
		     काष्ठा ccs_pll *pll, काष्ठा ccs_pll_branch_fr *op_pll_fr,
		     काष्ठा ccs_pll_branch_bk *op_pll_bk, u32 mul,
		     u32 भाग, u32 op_sys_clk_freq_hz_sdr, u32 l,
		     bool cphy, u32 phy_स्थिर)
अणु
	/*
	 * Higher multipliers (and भागisors) are often required than
	 * necessitated by the बाह्यal घड़ी and the output घड़ीs.
	 * There are limits क्रम all values in the घड़ी tree. These
	 * are the minimum and maximum multiplier क्रम mul.
	 */
	u32 more_mul_min, more_mul_max;
	u32 more_mul_factor;
	u32 i;

	/*
	 * Get pre_pll_clk_भाग so that our pll_op_clk_freq_hz won't be
	 * too high.
	 */
	dev_dbg(dev, "op_pre_pll_clk_div %u\n", op_pll_fr->pre_pll_clk_भाग);

	/* Don't go above max pll multiplier. */
	more_mul_max = op_lim_fr->max_pll_multiplier / mul;
	dev_dbg(dev, "more_mul_max: max_op_pll_multiplier check: %u\n",
		more_mul_max);
	/* Don't go above max pll op frequency. */
	more_mul_max =
		min_t(u32,
		      more_mul_max,
		      op_lim_fr->max_pll_op_clk_freq_hz
		      / (pll->ext_clk_freq_hz /
			 op_pll_fr->pre_pll_clk_भाग * mul));
	dev_dbg(dev, "more_mul_max: max_pll_op_clk_freq_hz check: %u\n",
		more_mul_max);
	/* Don't go above the भागision capability of op sys घड़ी भागider. */
	more_mul_max = min(more_mul_max,
			   op_lim_bk->max_sys_clk_भाग * op_pll_fr->pre_pll_clk_भाग
			   / भाग);
	dev_dbg(dev, "more_mul_max: max_op_sys_clk_div check: %u\n",
		more_mul_max);
	/* Ensure we won't go above max_pll_multiplier. */
	more_mul_max = min(more_mul_max, op_lim_fr->max_pll_multiplier / mul);
	dev_dbg(dev, "more_mul_max: min_pll_multiplier check: %u\n",
		more_mul_max);

	/* Ensure we won't go below min_pll_op_clk_freq_hz. */
	more_mul_min = DIV_ROUND_UP(op_lim_fr->min_pll_op_clk_freq_hz,
				    pll->ext_clk_freq_hz /
				    op_pll_fr->pre_pll_clk_भाग * mul);
	dev_dbg(dev, "more_mul_min: min_op_pll_op_clk_freq_hz check: %u\n",
		more_mul_min);
	/* Ensure we won't go below min_pll_multiplier. */
	more_mul_min = max(more_mul_min,
			   DIV_ROUND_UP(op_lim_fr->min_pll_multiplier, mul));
	dev_dbg(dev, "more_mul_min: min_op_pll_multiplier check: %u\n",
		more_mul_min);

	अगर (more_mul_min > more_mul_max) अणु
		dev_dbg(dev,
			"unable to compute more_mul_min and more_mul_max\n");
		वापस -EINVAL;
	पूर्ण

	more_mul_factor = lcm(भाग, op_pll_fr->pre_pll_clk_भाग) / भाग;
	dev_dbg(dev, "more_mul_factor: %u\n", more_mul_factor);
	more_mul_factor = lcm(more_mul_factor, op_lim_bk->min_sys_clk_भाग);
	dev_dbg(dev, "more_mul_factor: min_op_sys_clk_div: %d\n",
		more_mul_factor);
	i = roundup(more_mul_min, more_mul_factor);
	अगर (!is_one_or_even(i))
		i <<= 1;

	dev_dbg(dev, "final more_mul: %u\n", i);
	अगर (i > more_mul_max) अणु
		dev_dbg(dev, "final more_mul is bad, max %u\n", more_mul_max);
		वापस -EINVAL;
	पूर्ण

	op_pll_fr->pll_multiplier = mul * i;
	op_pll_bk->sys_clk_भाग = भाग * i / op_pll_fr->pre_pll_clk_भाग;
	dev_dbg(dev, "op_sys_clk_div: %u\n", op_pll_bk->sys_clk_भाग);

	op_pll_fr->pll_ip_clk_freq_hz = pll->ext_clk_freq_hz
		/ op_pll_fr->pre_pll_clk_भाग;

	op_pll_fr->pll_op_clk_freq_hz = op_pll_fr->pll_ip_clk_freq_hz
		* op_pll_fr->pll_multiplier;

	अगर (pll->flags & CCS_PLL_FLAG_LANE_SPEED_MODEL)
		op_pll_bk->pix_clk_भाग =
			(pll->bits_per_pixel
			 * pll->op_lanes * (phy_स्थिर << op_sys_ddr(pll->flags))
			 / PHY_CONST_DIV / pll->csi2.lanes / l)
			>> op_pix_ddr(pll->flags);
	अन्यथा
		op_pll_bk->pix_clk_भाग =
			(pll->bits_per_pixel
			 * (phy_स्थिर << op_sys_ddr(pll->flags))
			 / PHY_CONST_DIV / l) >> op_pix_ddr(pll->flags);

	op_pll_bk->pix_clk_freq_hz =
		(op_sys_clk_freq_hz_sdr >> op_pix_ddr(pll->flags))
		/ op_pll_bk->pix_clk_भाग;
	op_pll_bk->sys_clk_freq_hz =
		op_sys_clk_freq_hz_sdr >> op_sys_ddr(pll->flags);

	dev_dbg(dev, "op_pix_clk_div: %u\n", op_pll_bk->pix_clk_भाग);

	वापस 0;
पूर्ण

पूर्णांक ccs_pll_calculate(काष्ठा device *dev, स्थिर काष्ठा ccs_pll_limits *lim,
		      काष्ठा ccs_pll *pll)
अणु
	स्थिर काष्ठा ccs_pll_branch_limits_fr *op_lim_fr;
	स्थिर काष्ठा ccs_pll_branch_limits_bk *op_lim_bk;
	काष्ठा ccs_pll_branch_fr *op_pll_fr;
	काष्ठा ccs_pll_branch_bk *op_pll_bk;
	bool cphy = pll->bus_type == CCS_PLL_BUS_TYPE_CSI2_CPHY;
	u32 phy_स्थिर = cphy ? CPHY_CONST : DPHY_CONST;
	u32 op_sys_clk_freq_hz_sdr;
	u16 min_op_pre_pll_clk_भाग;
	u16 max_op_pre_pll_clk_भाग;
	u32 mul, भाग;
	u32 l = (!pll->op_bits_per_lane ||
		 pll->op_bits_per_lane >= pll->bits_per_pixel) ? 1 : 2;
	u32 i;
	पूर्णांक rval = -EINVAL;

	अगर (!(pll->flags & CCS_PLL_FLAG_LANE_SPEED_MODEL)) अणु
		pll->op_lanes = 1;
		pll->vt_lanes = 1;
	पूर्ण

	अगर (pll->flags & CCS_PLL_FLAG_DUAL_PLL) अणु
		op_lim_fr = &lim->op_fr;
		op_lim_bk = &lim->op_bk;
		op_pll_fr = &pll->op_fr;
		op_pll_bk = &pll->op_bk;
	पूर्ण अन्यथा अगर (pll->flags & CCS_PLL_FLAG_NO_OP_CLOCKS) अणु
		/*
		 * If there's no OP PLL at all, use the VT values
		 * instead. The OP values are ignored क्रम the rest of
		 * the PLL calculation.
		 */
		op_lim_fr = &lim->vt_fr;
		op_lim_bk = &lim->vt_bk;
		op_pll_fr = &pll->vt_fr;
		op_pll_bk = &pll->vt_bk;
	पूर्ण अन्यथा अणु
		op_lim_fr = &lim->vt_fr;
		op_lim_bk = &lim->op_bk;
		op_pll_fr = &pll->vt_fr;
		op_pll_bk = &pll->op_bk;
	पूर्ण

	अगर (!pll->op_lanes || !pll->vt_lanes || !pll->bits_per_pixel ||
	    !pll->ext_clk_freq_hz || !pll->link_freq || !pll->scale_m ||
	    !op_lim_fr->min_pll_ip_clk_freq_hz ||
	    !op_lim_fr->max_pll_ip_clk_freq_hz ||
	    !op_lim_fr->min_pll_op_clk_freq_hz ||
	    !op_lim_fr->max_pll_op_clk_freq_hz ||
	    !op_lim_bk->max_sys_clk_भाग || !op_lim_fr->max_pll_multiplier)
		वापस -EINVAL;

	/*
	 * Make sure op_pix_clk_भाग will be पूर्णांकeger --- unless flexible
	 * op_pix_clk_भाग is supported
	 */
	अगर (!(pll->flags & CCS_PLL_FLAG_FLEXIBLE_OP_PIX_CLK_DIV) &&
	    (pll->bits_per_pixel * pll->op_lanes) %
	    (pll->csi2.lanes * l << op_pix_ddr(pll->flags))) अणु
		dev_dbg(dev, "op_pix_clk_div not an integer (bpp %u, op lanes %u, lanes %u, l %u)\n",
			pll->bits_per_pixel, pll->op_lanes, pll->csi2.lanes, l);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dev, "vt_lanes: %u\n", pll->vt_lanes);
	dev_dbg(dev, "op_lanes: %u\n", pll->op_lanes);

	dev_dbg(dev, "binning: %ux%u\n", pll->binning_horizontal,
		pll->binning_vertical);

	चयन (pll->bus_type) अणु
	हाल CCS_PLL_BUS_TYPE_CSI2_DPHY:
	हाल CCS_PLL_BUS_TYPE_CSI2_CPHY:
		op_sys_clk_freq_hz_sdr = pll->link_freq * 2
			* (pll->flags & CCS_PLL_FLAG_LANE_SPEED_MODEL ?
			   1 : pll->csi2.lanes);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	pll->pixel_rate_csi =
		भाग_u64((uपूर्णांक64_t)op_sys_clk_freq_hz_sdr
			* (pll->flags & CCS_PLL_FLAG_LANE_SPEED_MODEL ?
			   pll->csi2.lanes : 1) * PHY_CONST_DIV,
			phy_स्थिर * pll->bits_per_pixel * l);

	/* Figure out limits क्रम OP pre-pll भागider based on extclk */
	dev_dbg(dev, "min / max op_pre_pll_clk_div: %u / %u\n",
		op_lim_fr->min_pre_pll_clk_भाग, op_lim_fr->max_pre_pll_clk_भाग);
	max_op_pre_pll_clk_भाग =
		min_t(u16, op_lim_fr->max_pre_pll_clk_भाग,
		      clk_भाग_even(pll->ext_clk_freq_hz /
				   op_lim_fr->min_pll_ip_clk_freq_hz));
	min_op_pre_pll_clk_भाग =
		max_t(u16, op_lim_fr->min_pre_pll_clk_भाग,
		      clk_भाग_even_up(
			      DIV_ROUND_UP(pll->ext_clk_freq_hz,
					   op_lim_fr->max_pll_ip_clk_freq_hz)));
	dev_dbg(dev, "pre-pll check: min / max op_pre_pll_clk_div: %u / %u\n",
		min_op_pre_pll_clk_भाग, max_op_pre_pll_clk_भाग);

	i = gcd(op_sys_clk_freq_hz_sdr,
		pll->ext_clk_freq_hz << op_pix_ddr(pll->flags));
	mul = op_sys_clk_freq_hz_sdr / i;
	भाग = (pll->ext_clk_freq_hz << op_pix_ddr(pll->flags)) / i;
	dev_dbg(dev, "mul %u / div %u\n", mul, भाग);

	min_op_pre_pll_clk_भाग =
		max_t(u16, min_op_pre_pll_clk_भाग,
		      clk_भाग_even_up(
			      mul /
			      one_or_more(
				      DIV_ROUND_UP(op_lim_fr->max_pll_op_clk_freq_hz,
						   pll->ext_clk_freq_hz))));
	dev_dbg(dev, "pll_op check: min / max op_pre_pll_clk_div: %u / %u\n",
		min_op_pre_pll_clk_भाग, max_op_pre_pll_clk_भाग);

	क्रम (op_pll_fr->pre_pll_clk_भाग = min_op_pre_pll_clk_भाग;
	     op_pll_fr->pre_pll_clk_भाग <= max_op_pre_pll_clk_भाग;
	     op_pll_fr->pre_pll_clk_भाग +=
		     (pll->flags & CCS_PLL_FLAG_EXT_IP_PLL_DIVIDER) ? 1 :
		     2 - (op_pll_fr->pre_pll_clk_भाग & 1)) अणु
		rval = ccs_pll_calculate_op(dev, lim, op_lim_fr, op_lim_bk, pll,
					    op_pll_fr, op_pll_bk, mul, भाग,
					    op_sys_clk_freq_hz_sdr, l, cphy,
					    phy_स्थिर);
		अगर (rval)
			जारी;

		rval = check_fr_bounds(dev, lim, pll,
				       pll->flags & CCS_PLL_FLAG_DUAL_PLL ?
				       PLL_OP : PLL_VT);
		अगर (rval)
			जारी;

		rval = check_bk_bounds(dev, lim, pll, PLL_OP);
		अगर (rval)
			जारी;

		अगर (pll->flags & CCS_PLL_FLAG_DUAL_PLL)
			अवरोध;

		ccs_pll_calculate_vt(dev, lim, op_lim_bk, pll, op_pll_fr,
				     op_pll_bk, cphy, phy_स्थिर);

		rval = check_bk_bounds(dev, lim, pll, PLL_VT);
		अगर (rval)
			जारी;
		rval = check_ext_bounds(dev, pll);
		अगर (rval)
			जारी;

		अवरोध;
	पूर्ण

	अगर (rval) अणु
		dev_dbg(dev, "unable to compute pre_pll divisor\n");

		वापस rval;
	पूर्ण

	अगर (pll->flags & CCS_PLL_FLAG_DUAL_PLL) अणु
		rval = ccs_pll_calculate_vt_tree(dev, lim, pll);

		अगर (rval)
			वापस rval;
	पूर्ण

	prपूर्णांक_pll(dev, pll);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ccs_pll_calculate);

MODULE_AUTHOR("Sakari Ailus <sakari.ailus@linux.intel.com>");
MODULE_DESCRIPTION("Generic MIPI CCS/SMIA/SMIA++ PLL calculator");
MODULE_LICENSE("GPL");
