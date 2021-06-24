<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DPLL + CORE_CLK composite घड़ी functions
 *
 * Copyright (C) 2005-2008 Texas Instruments, Inc.
 * Copyright (C) 2004-2010 Nokia Corporation
 *
 * Contacts:
 * Riअक्षरd Woodruff <r-woodruff2@ti.com>
 * Paul Walmsley
 *
 * Based on earlier work by Tuukka Tikkanen, Tony Lindgren,
 * Gorकरोn McNutt and RidgeRun, Inc.
 *
 * XXX The DPLL and CORE घड़ीs should be split पूर्णांकo two separate घड़ी
 * types.
 */
#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>

#समावेश "clock.h"
#समावेश "clock2xxx.h"
#समावेश "opp2xxx.h"
#समावेश "cm2xxx.h"
#समावेश "cm-regbits-24xx.h"
#समावेश "sdrc.h"
#समावेश "sram.h"

/* #घोषणा DOWN_VARIABLE_DPLL 1 */		/* Experimental */

/*
 * dpll_core_ck: poपूर्णांकer to the combined dpll_ck + core_ck on OMAP2xxx
 * (currently defined as "dpll_ck" in the OMAP2xxx घड़ी tree).  Set
 * during dpll_ck init and used later by omap2xxx_clk_get_core_rate().
 */
अटल काष्ठा clk_hw_omap *dpll_core_ck;

/**
 * omap2xxx_clk_get_core_rate - वापस the CORE_CLK rate
 *
 * Returns the CORE_CLK rate.  CORE_CLK can have one of three rate
 * sources on OMAP2xxx: the DPLL CLKOUT rate, DPLL CLKOUTX2, or 32KHz
 * (the latter is unusual).  This currently should be called with
 * काष्ठा clk *dpll_ck, which is a composite घड़ी of dpll_ck and
 * core_ck.
 */
अचिन्हित दीर्घ omap2xxx_clk_get_core_rate(व्योम)
अणु
	दीर्घ दीर्घ core_clk;
	u32 v;

	WARN_ON(!dpll_core_ck);

	core_clk = omap2_get_dpll_rate(dpll_core_ck);

	v = omap2xxx_cm_get_core_clk_src();

	अगर (v == CORE_CLK_SRC_32K)
		core_clk = 32768;
	अन्यथा
		core_clk *= v;

	वापस core_clk;
पूर्ण

/*
 * Uses the current prcm set to tell अगर a rate is valid.
 * You can go slower, but not faster within a given rate set.
 */
अटल दीर्घ omap2_dpllcore_round_rate(अचिन्हित दीर्घ target_rate)
अणु
	u32 high, low, core_clk_src;

	core_clk_src = omap2xxx_cm_get_core_clk_src();

	अगर (core_clk_src == CORE_CLK_SRC_DPLL) अणु	/* DPLL घड़ीout */
		high = curr_prcm_set->dpll_speed * 2;
		low = curr_prcm_set->dpll_speed;
	पूर्ण अन्यथा अणु				/* DPLL घड़ीout x 2 */
		high = curr_prcm_set->dpll_speed;
		low = curr_prcm_set->dpll_speed / 2;
	पूर्ण

#अगर_घोषित DOWN_VARIABLE_DPLL
	अगर (target_rate > high)
		वापस high;
	अन्यथा
		वापस target_rate;
#अन्यथा
	अगर (target_rate > low)
		वापस high;
	अन्यथा
		वापस low;
#पूर्ण_अगर

पूर्ण

अचिन्हित दीर्घ omap2_dpllcore_recalc(काष्ठा clk_hw *hw,
				    अचिन्हित दीर्घ parent_rate)
अणु
	वापस omap2xxx_clk_get_core_rate();
पूर्ण

पूर्णांक omap2_reprogram_dpllcore(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	u32 cur_rate, low, mult, भाग, valid_rate, करोne_rate;
	u32 bypass = 0;
	काष्ठा prcm_config पंचांगpset;
	स्थिर काष्ठा dpll_data *dd;

	cur_rate = omap2xxx_clk_get_core_rate();
	mult = omap2xxx_cm_get_core_clk_src();

	अगर ((rate == (cur_rate / 2)) && (mult == 2)) अणु
		omap2xxx_sdrc_reprogram(CORE_CLK_SRC_DPLL, 1);
	पूर्ण अन्यथा अगर ((rate == (cur_rate * 2)) && (mult == 1)) अणु
		omap2xxx_sdrc_reprogram(CORE_CLK_SRC_DPLL_X2, 1);
	पूर्ण अन्यथा अगर (rate != cur_rate) अणु
		valid_rate = omap2_dpllcore_round_rate(rate);
		अगर (valid_rate != rate)
			वापस -EINVAL;

		अगर (mult == 1)
			low = curr_prcm_set->dpll_speed;
		अन्यथा
			low = curr_prcm_set->dpll_speed / 2;

		dd = clk->dpll_data;
		अगर (!dd)
			वापस -EINVAL;

		पंचांगpset.cm_clksel1_pll =
			omap_clk_ll_ops.clk_पढ़ोl(&dd->mult_भाग1_reg);
		पंचांगpset.cm_clksel1_pll &= ~(dd->mult_mask |
					   dd->भाग1_mask);
		भाग = ((curr_prcm_set->xtal_speed / 1000000) - 1);
		पंचांगpset.cm_clksel2_pll = omap2xxx_cm_get_core_pll_config();
		पंचांगpset.cm_clksel2_pll &= ~OMAP24XX_CORE_CLK_SRC_MASK;
		अगर (rate > low) अणु
			पंचांगpset.cm_clksel2_pll |= CORE_CLK_SRC_DPLL_X2;
			mult = ((rate / 2) / 1000000);
			करोne_rate = CORE_CLK_SRC_DPLL_X2;
		पूर्ण अन्यथा अणु
			पंचांगpset.cm_clksel2_pll |= CORE_CLK_SRC_DPLL;
			mult = (rate / 1000000);
			करोne_rate = CORE_CLK_SRC_DPLL;
		पूर्ण
		पंचांगpset.cm_clksel1_pll |= (भाग << __ffs(dd->mult_mask));
		पंचांगpset.cm_clksel1_pll |= (mult << __ffs(dd->भाग1_mask));

		/* Worst हाल */
		पंचांगpset.base_sdrc_rfr = SDRC_RFR_CTRL_BYPASS;

		अगर (rate == curr_prcm_set->xtal_speed)	/* If asking क्रम 1-1 */
			bypass = 1;

		/* For omap2xxx_sdrc_init_params() */
		omap2xxx_sdrc_reprogram(CORE_CLK_SRC_DPLL_X2, 1);

		/* Force dll lock mode */
		omap2_set_prcm(पंचांगpset.cm_clksel1_pll, पंचांगpset.base_sdrc_rfr,
			       bypass);

		/* Errata: ret dll entry state */
		omap2xxx_sdrc_init_params(omap2xxx_sdrc_dll_is_unlocked());
		omap2xxx_sdrc_reprogram(करोne_rate, 0);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * omap2xxx_clkt_dpllcore_init - clk init function क्रम dpll_ck
 * @clk: काष्ठा clk *dpll_ck
 *
 * Store a local copy of @clk in dpll_core_ck so other code can query
 * the core rate without having to clk_get(), which can sleep.  Must
 * only be called once.  No वापस value.  XXX If the घड़ी
 * registration process is ever changed such that dpll_ck is no दीर्घer
 * अटलally defined, this code may need to change to increment some
 * kind of use count on dpll_ck.
 */
व्योम omap2xxx_clkt_dpllcore_init(काष्ठा clk_hw *hw)
अणु
	WARN(dpll_core_ck, "dpll_core_ck already set - should never happen");
	dpll_core_ck = to_clk_hw_omap(hw);
पूर्ण
