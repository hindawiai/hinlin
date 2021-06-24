<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP2xxx DVFS भव घड़ी functions
 *
 * Copyright (C) 2005-2008, 2012 Texas Instruments, Inc.
 * Copyright (C) 2004-2010 Nokia Corporation
 *
 * Contacts:
 * Riअक्षरd Woodruff <r-woodruff2@ti.com>
 * Paul Walmsley
 *
 * Based on earlier work by Tuukka Tikkanen, Tony Lindgren,
 * Gorकरोn McNutt and RidgeRun, Inc.
 *
 * XXX Some of this code should be replaceable by the upcoming OPP layer
 * code.  However, some notion of "rate set" is probably still necessary
 * क्रम OMAP2xxx at least.  Rate sets should be generalized so they can be
 * used क्रम any OMAP chip, not just OMAP2xxx.  In particular, Riअक्षरd Woodruff
 * has in the past expressed a preference to use rate sets क्रम OPP changes,
 * rather than dynamically recalculating the घड़ी tree, so अगर someone wants
 * this badly enough to ग_लिखो the code to handle it, we should support it
 * as an option.
 */
#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/cpufreq.h>
#समावेश <linux/slab.h>

#समावेश "soc.h"
#समावेश "clock.h"
#समावेश "clock2xxx.h"
#समावेश "opp2xxx.h"
#समावेश "cm2xxx.h"
#समावेश "cm-regbits-24xx.h"
#समावेश "sdrc.h"
#समावेश "sram.h"

स्थिर काष्ठा prcm_config *curr_prcm_set;
स्थिर काष्ठा prcm_config *rate_table;

/*
 * sys_ck_rate: the rate of the बाह्यal high-frequency घड़ी
 * oscillator on the board.  Set by the SoC-specअगरic घड़ी init code.
 * Once set during a boot, will not change.
 */
अटल अचिन्हित दीर्घ sys_ck_rate;

/**
 * omap2_table_mpu_recalc - just वापस the MPU speed
 * @clk: virt_prcm_set काष्ठा clk
 *
 * Set virt_prcm_set's rate to the mpu_speed field of the current PRCM set.
 */
अचिन्हित दीर्घ omap2_table_mpu_recalc(काष्ठा clk_hw *clk,
				     अचिन्हित दीर्घ parent_rate)
अणु
	वापस curr_prcm_set->mpu_speed;
पूर्ण

/*
 * Look क्रम a rate equal or less than the target rate given a configuration set.
 *
 * What's not entirely clear is "which" field represents the key field.
 * Some might argue L3-DDR, others ARM, others IVA. This code is simple and
 * just uses the ARM rates.
 */
दीर्घ omap2_round_to_table_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *parent_rate)
अणु
	स्थिर काष्ठा prcm_config *ptr;
	दीर्घ highest_rate;

	highest_rate = -EINVAL;

	क्रम (ptr = rate_table; ptr->mpu_speed; ptr++) अणु
		अगर (!(ptr->flags & cpu_mask))
			जारी;
		अगर (ptr->xtal_speed != sys_ck_rate)
			जारी;

		highest_rate = ptr->mpu_speed;

		/* Can check only after xtal frequency check */
		अगर (ptr->mpu_speed <= rate)
			अवरोध;
	पूर्ण
	वापस highest_rate;
पूर्ण

/* Sets basic घड़ीs based on the specअगरied rate */
पूर्णांक omap2_select_table_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate)
अणु
	u32 cur_rate, करोne_rate, bypass = 0;
	स्थिर काष्ठा prcm_config *prcm;
	अचिन्हित दीर्घ found_speed = 0;
	अचिन्हित दीर्घ flags;

	क्रम (prcm = rate_table; prcm->mpu_speed; prcm++) अणु
		अगर (!(prcm->flags & cpu_mask))
			जारी;

		अगर (prcm->xtal_speed != sys_ck_rate)
			जारी;

		अगर (prcm->mpu_speed <= rate) अणु
			found_speed = prcm->mpu_speed;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found_speed) अणु
		prपूर्णांकk(KERN_INFO "Could not set MPU rate to %luMHz\n",
		       rate / 1000000);
		वापस -EINVAL;
	पूर्ण

	curr_prcm_set = prcm;
	cur_rate = omap2xxx_clk_get_core_rate();

	अगर (prcm->dpll_speed == cur_rate / 2) अणु
		omap2xxx_sdrc_reprogram(CORE_CLK_SRC_DPLL, 1);
	पूर्ण अन्यथा अगर (prcm->dpll_speed == cur_rate * 2) अणु
		omap2xxx_sdrc_reprogram(CORE_CLK_SRC_DPLL_X2, 1);
	पूर्ण अन्यथा अगर (prcm->dpll_speed != cur_rate) अणु
		local_irq_save(flags);

		अगर (prcm->dpll_speed == prcm->xtal_speed)
			bypass = 1;

		अगर ((prcm->cm_clksel2_pll & OMAP24XX_CORE_CLK_SRC_MASK) ==
		    CORE_CLK_SRC_DPLL_X2)
			करोne_rate = CORE_CLK_SRC_DPLL_X2;
		अन्यथा
			करोne_rate = CORE_CLK_SRC_DPLL;

		omap2xxx_cm_set_mod_भागiders(prcm->cm_clksel_mpu,
					     prcm->cm_clksel_dsp,
					     prcm->cm_clksel_gfx,
					     prcm->cm_clksel1_core,
					     prcm->cm_clksel_mdm);

		/* x2 to enter omap2xxx_sdrc_init_params() */
		omap2xxx_sdrc_reprogram(CORE_CLK_SRC_DPLL_X2, 1);

		omap2_set_prcm(prcm->cm_clksel1_pll, prcm->base_sdrc_rfr,
			       bypass);

		omap2xxx_sdrc_init_params(omap2xxx_sdrc_dll_is_unlocked());
		omap2xxx_sdrc_reprogram(करोne_rate, 0);

		local_irq_restore(flags);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * omap2xxx_clkt_vps_check_bootloader_rate - determine which of the rate
 * table sets matches the current CORE DPLL hardware rate
 *
 * Check the MPU rate set by bootloader.  Sets the 'curr_prcm_set'
 * global to poपूर्णांक to the active rate set when found; otherwise, sets
 * it to शून्य.  No वापस value;
 */
व्योम omap2xxx_clkt_vps_check_bootloader_rates(व्योम)
अणु
	स्थिर काष्ठा prcm_config *prcm = शून्य;
	अचिन्हित दीर्घ rate;

	rate = omap2xxx_clk_get_core_rate();
	क्रम (prcm = rate_table; prcm->mpu_speed; prcm++) अणु
		अगर (!(prcm->flags & cpu_mask))
			जारी;
		अगर (prcm->xtal_speed != sys_ck_rate)
			जारी;
		अगर (prcm->dpll_speed <= rate)
			अवरोध;
	पूर्ण
	curr_prcm_set = prcm;
पूर्ण

/**
 * omap2xxx_clkt_vps_late_init - store a copy of the sys_ck rate
 *
 * Store a copy of the sys_ck rate क्रम later use by the OMAP2xxx DVFS
 * code.  (The sys_ck rate करोes not -- or rather, must not -- change
 * during kernel runसमय.)  Must be called after we have a valid
 * sys_ck rate, but beक्रमe the virt_prcm_set घड़ी rate is
 * recalculated.  No वापस value.
 */
व्योम omap2xxx_clkt_vps_late_init(व्योम)
अणु
	काष्ठा clk *c;

	c = clk_get(शून्य, "sys_ck");
	अगर (IS_ERR(c)) अणु
		WARN(1, "could not locate sys_ck\n");
	पूर्ण अन्यथा अणु
		sys_ck_rate = clk_get_rate(c);
		clk_put(c);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_OF
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>

अटल स्थिर काष्ठा clk_ops virt_prcm_set_ops = अणु
	.recalc_rate	= &omap2_table_mpu_recalc,
	.set_rate	= &omap2_select_table_rate,
	.round_rate	= &omap2_round_to_table_rate,
पूर्ण;

/**
 * omap2xxx_clkt_vps_init - initialize virt_prcm_set घड़ी
 *
 * Does a manual init क्रम the भव prcm DVFS घड़ी क्रम OMAP2. This
 * function is called only from omap2 DT घड़ी init, as the भव
 * node is not modelled in the DT घड़ी data.
 */
व्योम omap2xxx_clkt_vps_init(व्योम)
अणु
	काष्ठा clk_init_data init = अणु शून्य पूर्ण;
	काष्ठा clk_hw_omap *hw = शून्य;
	काष्ठा clk *clk;
	स्थिर अक्षर *parent_name = "mpu_ck";

	omap2xxx_clkt_vps_late_init();
	omap2xxx_clkt_vps_check_bootloader_rates();

	hw = kzalloc(माप(*hw), GFP_KERNEL);
	अगर (!hw)
		वापस;
	init.name = "virt_prcm_set";
	init.ops = &virt_prcm_set_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	hw->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &hw->hw);
	अगर (IS_ERR(clk)) अणु
		prपूर्णांकk(KERN_ERR "Failed to register clock\n");
		kमुक्त(hw);
		वापस;
	पूर्ण

	clkdev_create(clk, "cpufreq_ck", शून्य);
पूर्ण
#पूर्ण_अगर
