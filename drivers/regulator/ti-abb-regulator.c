<शैली गुरु>
/*
 * Texas Instruments SoC Adaptive Body Bias(ABB) Regulator
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 * Mike Turquette <mturquette@ti.com>
 *
 * Copyright (C) 2012-2013 Texas Instruments, Inc.
 * Andrii Tseglytskyi <andrii.tseglytskyi@ti.com>
 * Nishanth Menon <nm@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>

/*
 * ABB LDO operating states:
 * NOMINAL_OPP:	bypasses the ABB LDO
 * FAST_OPP:	sets ABB LDO to Forward Body-Bias
 * SLOW_OPP:	sets ABB LDO to Reverse Body-Bias
 */
#घोषणा TI_ABB_NOMINAL_OPP	0
#घोषणा TI_ABB_FAST_OPP		1
#घोषणा TI_ABB_SLOW_OPP		3

/**
 * काष्ठा ti_abb_info - ABB inक्रमmation per voltage setting
 * @opp_sel:	one of TI_ABB macro
 * @vset:	(optional) vset value that LDOVBB needs to be overriden with.
 *
 * Array of per voltage entries organized in the same order as regulator_desc's
 * volt_table list. (selector is used to index from this array)
 */
काष्ठा ti_abb_info अणु
	u32 opp_sel;
	u32 vset;
पूर्ण;

/**
 * काष्ठा ti_abb_reg - Register description क्रम ABB block
 * @setup_off:			setup रेजिस्टर offset from base
 * @control_off:		control रेजिस्टर offset from base
 * @sr2_wtcnt_value_mask:	setup रेजिस्टर- sr2_wtcnt_value mask
 * @fbb_sel_mask:		setup रेजिस्टर- FBB sel mask
 * @rbb_sel_mask:		setup रेजिस्टर- RBB sel mask
 * @sr2_en_mask:		setup रेजिस्टर- enable mask
 * @opp_change_mask:		control रेजिस्टर - mask to trigger LDOVBB change
 * @opp_sel_mask:		control रेजिस्टर - mask क्रम mode to operate
 */
काष्ठा ti_abb_reg अणु
	u32 setup_off;
	u32 control_off;

	/* Setup रेजिस्टर fields */
	u32 sr2_wtcnt_value_mask;
	u32 fbb_sel_mask;
	u32 rbb_sel_mask;
	u32 sr2_en_mask;

	/* Control रेजिस्टर fields */
	u32 opp_change_mask;
	u32 opp_sel_mask;
पूर्ण;

/**
 * काष्ठा ti_abb - ABB instance data
 * @rdesc:			regulator descriptor
 * @clk:			घड़ी(usually sysclk) supplying ABB block
 * @base:			base address of ABB block
 * @setup_reg:			setup रेजिस्टर of ABB block
 * @control_reg:		control रेजिस्टर of ABB block
 * @पूर्णांक_base:			पूर्णांकerrupt रेजिस्टर base address
 * @efuse_base:			(optional) efuse base address क्रम ABB modes
 * @lकरो_base:			(optional) LDOVBB vset override base address
 * @regs:			poपूर्णांकer to काष्ठा ti_abb_reg क्रम ABB block
 * @txकरोne_mask:		mask on पूर्णांक_base क्रम tranxकरोne पूर्णांकerrupt
 * @lकरोvbb_override_mask:	mask to lकरो_base क्रम overriding शेष LDO VBB
 *				vset with value from efuse
 * @lकरोvbb_vset_mask:		mask to lकरो_base क्रम providing the VSET override
 * @info:			array to per voltage ABB configuration
 * @current_info_idx:		current index to info
 * @settling_समय:		SoC specअगरic settling समय क्रम LDO VBB
 */
काष्ठा ti_abb अणु
	काष्ठा regulator_desc rdesc;
	काष्ठा clk *clk;
	व्योम __iomem *base;
	व्योम __iomem *setup_reg;
	व्योम __iomem *control_reg;
	व्योम __iomem *पूर्णांक_base;
	व्योम __iomem *efuse_base;
	व्योम __iomem *lकरो_base;

	स्थिर काष्ठा ti_abb_reg *regs;
	u32 txकरोne_mask;
	u32 lकरोvbb_override_mask;
	u32 lकरोvbb_vset_mask;

	काष्ठा ti_abb_info *info;
	पूर्णांक current_info_idx;

	u32 settling_समय;
पूर्ण;

/**
 * ti_abb_rmw() - handy wrapper to set specअगरic रेजिस्टर bits
 * @mask:	mask क्रम रेजिस्टर field
 * @value:	value shअगरted to mask location and written
 * @reg:	रेजिस्टर address
 *
 * Return: final रेजिस्टर value (may be unused)
 */
अटल अंतरभूत u32 ti_abb_rmw(u32 mask, u32 value, व्योम __iomem *reg)
अणु
	u32 val;

	val = पढ़ोl(reg);
	val &= ~mask;
	val |= (value << __ffs(mask)) & mask;
	ग_लिखोl(val, reg);

	वापस val;
पूर्ण

/**
 * ti_abb_check_txकरोne() - handy wrapper to check ABB tranxकरोne status
 * @abb:	poपूर्णांकer to the abb instance
 *
 * Return: true or false
 */
अटल अंतरभूत bool ti_abb_check_txकरोne(स्थिर काष्ठा ti_abb *abb)
अणु
	वापस !!(पढ़ोl(abb->पूर्णांक_base) & abb->txकरोne_mask);
पूर्ण

/**
 * ti_abb_clear_txकरोne() - handy wrapper to clear ABB tranxकरोne status
 * @abb:	poपूर्णांकer to the abb instance
 */
अटल अंतरभूत व्योम ti_abb_clear_txकरोne(स्थिर काष्ठा ti_abb *abb)
अणु
	ग_लिखोl(abb->txकरोne_mask, abb->पूर्णांक_base);
पूर्ण;

/**
 * ti_abb_रुको_tranx() - रुकोs क्रम ABB tranxकरोne event
 * @dev:	device
 * @abb:	poपूर्णांकer to the abb instance
 *
 * Return: 0 on success or -ETIMEDOUT अगर the event is not cleared on समय.
 */
अटल पूर्णांक ti_abb_रुको_txकरोne(काष्ठा device *dev, काष्ठा ti_abb *abb)
अणु
	पूर्णांक समयout = 0;
	bool status;

	जबतक (समयout++ <= abb->settling_समय) अणु
		status = ti_abb_check_txकरोne(abb);
		अगर (status)
			वापस 0;

		udelay(1);
	पूर्ण

	dev_warn_ratelimited(dev, "%s:TRANXDONE timeout(%duS) int=0x%08x\n",
			     __func__, समयout, पढ़ोl(abb->पूर्णांक_base));
	वापस -ETIMEDOUT;
पूर्ण

/**
 * ti_abb_clear_all_txकरोne() - clears ABB tranxकरोne event
 * @dev:	device
 * @abb:	poपूर्णांकer to the abb instance
 *
 * Return: 0 on success or -ETIMEDOUT अगर the event is not cleared on समय.
 */
अटल पूर्णांक ti_abb_clear_all_txकरोne(काष्ठा device *dev, स्थिर काष्ठा ti_abb *abb)
अणु
	पूर्णांक समयout = 0;
	bool status;

	जबतक (समयout++ <= abb->settling_समय) अणु
		ti_abb_clear_txकरोne(abb);

		status = ti_abb_check_txकरोne(abb);
		अगर (!status)
			वापस 0;

		udelay(1);
	पूर्ण

	dev_warn_ratelimited(dev, "%s:TRANXDONE timeout(%duS) int=0x%08x\n",
			     __func__, समयout, पढ़ोl(abb->पूर्णांक_base));
	वापस -ETIMEDOUT;
पूर्ण

/**
 * ti_abb_program_lकरोvbb() - program LDOVBB रेजिस्टर क्रम override value
 * @dev:	device
 * @abb:	poपूर्णांकer to the abb instance
 * @info:	ABB info to program
 */
अटल व्योम ti_abb_program_lकरोvbb(काष्ठा device *dev, स्थिर काष्ठा ti_abb *abb,
				  काष्ठा ti_abb_info *info)
अणु
	u32 val;

	val = पढ़ोl(abb->lकरो_base);
	/* clear up previous values */
	val &= ~(abb->lकरोvbb_override_mask | abb->lकरोvbb_vset_mask);

	चयन (info->opp_sel) अणु
	हाल TI_ABB_SLOW_OPP:
	हाल TI_ABB_FAST_OPP:
		val |= abb->lकरोvbb_override_mask;
		val |= info->vset << __ffs(abb->lकरोvbb_vset_mask);
		अवरोध;
	पूर्ण

	ग_लिखोl(val, abb->lकरो_base);
पूर्ण

/**
 * ti_abb_set_opp() - Setup ABB and LDO VBB क्रम required bias
 * @rdev:	regulator device
 * @abb:	poपूर्णांकer to the abb instance
 * @info:	ABB info to program
 *
 * Return: 0 on success or appropriate error value when fails
 */
अटल पूर्णांक ti_abb_set_opp(काष्ठा regulator_dev *rdev, काष्ठा ti_abb *abb,
			  काष्ठा ti_abb_info *info)
अणु
	स्थिर काष्ठा ti_abb_reg *regs = abb->regs;
	काष्ठा device *dev = &rdev->dev;
	पूर्णांक ret;

	ret = ti_abb_clear_all_txकरोne(dev, abb);
	अगर (ret)
		जाओ out;

	ti_abb_rmw(regs->fbb_sel_mask | regs->rbb_sel_mask, 0, abb->setup_reg);

	चयन (info->opp_sel) अणु
	हाल TI_ABB_SLOW_OPP:
		ti_abb_rmw(regs->rbb_sel_mask, 1, abb->setup_reg);
		अवरोध;
	हाल TI_ABB_FAST_OPP:
		ti_abb_rmw(regs->fbb_sel_mask, 1, abb->setup_reg);
		अवरोध;
	पूर्ण

	/* program next state of ABB lकरो */
	ti_abb_rmw(regs->opp_sel_mask, info->opp_sel, abb->control_reg);

	/*
	 * program LDO VBB vset override अगर needed क्रम !bypass mode
	 * XXX: Do not चयन sequence - क्रम !bypass, LDO override reset *must*
	 * be perक्रमmed *beक्रमe* चयन to bias mode अन्यथा VBB glitches.
	 */
	अगर (abb->lकरो_base && info->opp_sel != TI_ABB_NOMINAL_OPP)
		ti_abb_program_lकरोvbb(dev, abb, info);

	/* Initiate ABB lकरो change */
	ti_abb_rmw(regs->opp_change_mask, 1, abb->control_reg);

	/* Wait क्रम ABB LDO to complete transition to new Bias setting */
	ret = ti_abb_रुको_txकरोne(dev, abb);
	अगर (ret)
		जाओ out;

	ret = ti_abb_clear_all_txकरोne(dev, abb);
	अगर (ret)
		जाओ out;

	/*
	 * Reset LDO VBB vset override bypass mode
	 * XXX: Do not चयन sequence - क्रम bypass, LDO override reset *must*
	 * be perक्रमmed *after* चयन to bypass अन्यथा VBB glitches.
	 */
	अगर (abb->lकरो_base && info->opp_sel == TI_ABB_NOMINAL_OPP)
		ti_abb_program_lकरोvbb(dev, abb, info);

out:
	वापस ret;
पूर्ण

/**
 * ti_abb_set_voltage_sel() - regulator accessor function to set ABB LDO
 * @rdev:	regulator device
 * @sel:	selector to index पूर्णांकo required ABB LDO settings (maps to
 *		regulator descriptor's volt_table)
 *
 * Return: 0 on success or appropriate error value when fails
 */
अटल पूर्णांक ti_abb_set_voltage_sel(काष्ठा regulator_dev *rdev, अचिन्हित sel)
अणु
	स्थिर काष्ठा regulator_desc *desc = rdev->desc;
	काष्ठा ti_abb *abb = rdev_get_drvdata(rdev);
	काष्ठा device *dev = &rdev->dev;
	काष्ठा ti_abb_info *info, *oinfo;
	पूर्णांक ret = 0;

	अगर (!abb) अणु
		dev_err_ratelimited(dev, "%s: No regulator drvdata\n",
				    __func__);
		वापस -ENODEV;
	पूर्ण

	अगर (!desc->n_voltages || !abb->info) अणु
		dev_err_ratelimited(dev,
				    "%s: No valid voltage table entries?\n",
				    __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (sel >= desc->n_voltages) अणु
		dev_err(dev, "%s: sel idx(%d) >= n_voltages(%d)\n", __func__,
			sel, desc->n_voltages);
		वापस -EINVAL;
	पूर्ण

	/* If we are in the same index as we were, nothing to करो here! */
	अगर (sel == abb->current_info_idx) अणु
		dev_dbg(dev, "%s: Already at sel=%d\n", __func__, sel);
		वापस ret;
	पूर्ण

	info = &abb->info[sel];
	/*
	 * When Linux kernel is starting up, we are'nt sure of the
	 * Bias configuration that bootloader has configured.
	 * So, we get to know the actual setting the first समय
	 * we are asked to transition.
	 */
	अगर (abb->current_info_idx == -EINVAL)
		जाओ just_set_abb;

	/* If data is exactly the same, then just update index, no change */
	oinfo = &abb->info[abb->current_info_idx];
	अगर (!स_भेद(info, oinfo, माप(*info))) अणु
		dev_dbg(dev, "%s: Same data new idx=%d, old idx=%d\n", __func__,
			sel, abb->current_info_idx);
		जाओ out;
	पूर्ण

just_set_abb:
	ret = ti_abb_set_opp(rdev, abb, info);

out:
	अगर (!ret)
		abb->current_info_idx = sel;
	अन्यथा
		dev_err_ratelimited(dev,
				    "%s: Volt[%d] idx[%d] mode[%d] Fail(%d)\n",
				    __func__, desc->volt_table[sel], sel,
				    info->opp_sel, ret);
	वापस ret;
पूर्ण

/**
 * ti_abb_get_voltage_sel() - Regulator accessor to get current ABB LDO setting
 * @rdev:	regulator device
 *
 * Return: 0 on success or appropriate error value when fails
 */
अटल पूर्णांक ti_abb_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	स्थिर काष्ठा regulator_desc *desc = rdev->desc;
	काष्ठा ti_abb *abb = rdev_get_drvdata(rdev);
	काष्ठा device *dev = &rdev->dev;

	अगर (!abb) अणु
		dev_err_ratelimited(dev, "%s: No regulator drvdata\n",
				    __func__);
		वापस -ENODEV;
	पूर्ण

	अगर (!desc->n_voltages || !abb->info) अणु
		dev_err_ratelimited(dev,
				    "%s: No valid voltage table entries?\n",
				    __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (abb->current_info_idx >= (पूर्णांक)desc->n_voltages) अणु
		dev_err(dev, "%s: Corrupted data? idx(%d) >= n_voltages(%d)\n",
			__func__, abb->current_info_idx, desc->n_voltages);
		वापस -EINVAL;
	पूर्ण

	वापस abb->current_info_idx;
पूर्ण

/**
 * ti_abb_init_timings() - setup ABB घड़ी timing क्रम the current platक्रमm
 * @dev:	device
 * @abb:	poपूर्णांकer to the abb instance
 *
 * Return: 0 अगर timing is updated, अन्यथा वापसs error result.
 */
अटल पूर्णांक ti_abb_init_timings(काष्ठा device *dev, काष्ठा ti_abb *abb)
अणु
	u32 घड़ी_cycles;
	u32 clk_rate, sr2_wt_cnt_val, cycle_rate;
	स्थिर काष्ठा ti_abb_reg *regs = abb->regs;
	पूर्णांक ret;
	अक्षर *pname = "ti,settling-time";

	/* पढ़ो device tree properties */
	ret = of_property_पढ़ो_u32(dev->of_node, pname, &abb->settling_समय);
	अगर (ret) अणु
		dev_err(dev, "Unable to get property '%s'(%d)\n", pname, ret);
		वापस ret;
	पूर्ण

	/* ABB LDO cannot be settle in 0 समय */
	अगर (!abb->settling_समय) अणु
		dev_err(dev, "Invalid property:'%s' set as 0!\n", pname);
		वापस -EINVAL;
	पूर्ण

	pname = "ti,clock-cycles";
	ret = of_property_पढ़ो_u32(dev->of_node, pname, &घड़ी_cycles);
	अगर (ret) अणु
		dev_err(dev, "Unable to get property '%s'(%d)\n", pname, ret);
		वापस ret;
	पूर्ण
	/* ABB LDO cannot be settle in 0 घड़ी cycles */
	अगर (!घड़ी_cycles) अणु
		dev_err(dev, "Invalid property:'%s' set as 0!\n", pname);
		वापस -EINVAL;
	पूर्ण

	abb->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(abb->clk)) अणु
		ret = PTR_ERR(abb->clk);
		dev_err(dev, "%s: Unable to get clk(%d)\n", __func__, ret);
		वापस ret;
	पूर्ण

	/*
	 * SR2_WTCNT_VALUE is the settling समय क्रम the ABB lकरो after a
	 * transition and must be programmed with the correct समय at boot.
	 * The value programmed पूर्णांकo the रेजिस्टर is the number of SYS_CLK
	 * घड़ी cycles that match a given wall समय profiled क्रम the lकरो.
	 * This value depends on:
	 * settling समय of lकरो in micro-seconds (varies per OMAP family)
	 * # of घड़ी cycles per SYS_CLK period (varies per OMAP family)
	 * the SYS_CLK frequency in MHz (varies per board)
	 * The क्रमmula is:
	 *
	 *                      lकरो settling समय (in micro-seconds)
	 * SR2_WTCNT_VALUE = ------------------------------------------
	 *                   (# प्रणाली घड़ी cycles) * (sys_clk period)
	 *
	 * Put another way:
	 *
	 * SR2_WTCNT_VALUE = settling समय / (# SYS_CLK cycles / SYS_CLK rate))
	 *
	 * To aव्योम भागiding by zero multiply both "# clock cycles" and
	 * "settling time" by 10 such that the final result is the one we want.
	 */

	/* Convert SYS_CLK rate to MHz & prevent भागide by zero */
	clk_rate = DIV_ROUND_CLOSEST(clk_get_rate(abb->clk), 1000000);

	/* Calculate cycle rate */
	cycle_rate = DIV_ROUND_CLOSEST(घड़ी_cycles * 10, clk_rate);

	/* Calulate SR2_WTCNT_VALUE */
	sr2_wt_cnt_val = DIV_ROUND_CLOSEST(abb->settling_समय * 10, cycle_rate);

	dev_dbg(dev, "%s: Clk_rate=%ld, sr2_cnt=0x%08x\n", __func__,
		clk_get_rate(abb->clk), sr2_wt_cnt_val);

	ti_abb_rmw(regs->sr2_wtcnt_value_mask, sr2_wt_cnt_val, abb->setup_reg);

	वापस 0;
पूर्ण

/**
 * ti_abb_init_table() - Initialize ABB table from device tree
 * @dev:	device
 * @abb:	poपूर्णांकer to the abb instance
 * @rinit_data:	regulator initdata
 *
 * Return: 0 on success or appropriate error value when fails
 */
अटल पूर्णांक ti_abb_init_table(काष्ठा device *dev, काष्ठा ti_abb *abb,
			     काष्ठा regulator_init_data *rinit_data)
अणु
	काष्ठा ti_abb_info *info;
	स्थिर u32 num_values = 6;
	अक्षर *pname = "ti,abb_info";
	u32 i;
	अचिन्हित पूर्णांक *volt_table;
	पूर्णांक num_entries, min_uV = पूर्णांक_उच्च, max_uV = 0;
	काष्ठा regulation_स्थिरraपूर्णांकs *c = &rinit_data->स्थिरraपूर्णांकs;

	/*
	 * Each abb_info is a set of n-tuple, where n is num_values, consisting
	 * of voltage and a set of detection logic क्रम ABB inक्रमmation क्रम that
	 * voltage to apply.
	 */
	num_entries = of_property_count_u32_elems(dev->of_node, pname);
	अगर (num_entries < 0) अणु
		dev_err(dev, "No '%s' property?\n", pname);
		वापस num_entries;
	पूर्ण

	अगर (!num_entries || (num_entries % num_values)) अणु
		dev_err(dev, "All '%s' list entries need %d vals\n", pname,
			num_values);
		वापस -EINVAL;
	पूर्ण
	num_entries /= num_values;

	info = devm_kसुस्मृति(dev, num_entries, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	abb->info = info;

	volt_table = devm_kसुस्मृति(dev, num_entries, माप(अचिन्हित पूर्णांक),
				  GFP_KERNEL);
	अगर (!volt_table)
		वापस -ENOMEM;

	abb->rdesc.n_voltages = num_entries;
	abb->rdesc.volt_table = volt_table;
	/* We करो not know where the OPP voltage is at the moment */
	abb->current_info_idx = -EINVAL;

	क्रम (i = 0; i < num_entries; i++, info++, volt_table++) अणु
		u32 efuse_offset, rbb_mask, fbb_mask, vset_mask;
		u32 efuse_val;

		/* NOTE: num_values should equal to entries picked up here */
		of_property_पढ़ो_u32_index(dev->of_node, pname, i * num_values,
					   volt_table);
		of_property_पढ़ो_u32_index(dev->of_node, pname,
					   i * num_values + 1, &info->opp_sel);
		of_property_पढ़ो_u32_index(dev->of_node, pname,
					   i * num_values + 2, &efuse_offset);
		of_property_पढ़ो_u32_index(dev->of_node, pname,
					   i * num_values + 3, &rbb_mask);
		of_property_पढ़ो_u32_index(dev->of_node, pname,
					   i * num_values + 4, &fbb_mask);
		of_property_पढ़ो_u32_index(dev->of_node, pname,
					   i * num_values + 5, &vset_mask);

		dev_dbg(dev,
			"[%d]v=%d ABB=%d ef=0x%x rbb=0x%x fbb=0x%x vset=0x%x\n",
			i, *volt_table, info->opp_sel, efuse_offset, rbb_mask,
			fbb_mask, vset_mask);

		/* Find min/max क्रम voltage set */
		अगर (min_uV > *volt_table)
			min_uV = *volt_table;
		अगर (max_uV < *volt_table)
			max_uV = *volt_table;

		अगर (!abb->efuse_base) अणु
			/* Ignore invalid data, but warn to help cleanup */
			अगर (efuse_offset || rbb_mask || fbb_mask || vset_mask)
				dev_err(dev, "prop '%s': v=%d,bad efuse/mask\n",
					pname, *volt_table);
			जाओ check_abb;
		पूर्ण

		efuse_val = पढ़ोl(abb->efuse_base + efuse_offset);

		/* Use ABB recommendation from Efuse */
		अगर (efuse_val & rbb_mask)
			info->opp_sel = TI_ABB_SLOW_OPP;
		अन्यथा अगर (efuse_val & fbb_mask)
			info->opp_sel = TI_ABB_FAST_OPP;
		अन्यथा अगर (rbb_mask || fbb_mask)
			info->opp_sel = TI_ABB_NOMINAL_OPP;

		dev_dbg(dev,
			"[%d]v=%d efusev=0x%x final ABB=%d\n",
			i, *volt_table, efuse_val, info->opp_sel);

		/* Use recommended Vset bits from Efuse */
		अगर (!abb->lकरो_base) अणु
			अगर (vset_mask)
				dev_err(dev, "prop'%s':v=%d vst=%x LDO base?\n",
					pname, *volt_table, vset_mask);
			जारी;
		पूर्ण
		info->vset = (efuse_val & vset_mask) >> __ffs(vset_mask);
		dev_dbg(dev, "[%d]v=%d vset=%x\n", i, *volt_table, info->vset);
check_abb:
		चयन (info->opp_sel) अणु
		हाल TI_ABB_NOMINAL_OPP:
		हाल TI_ABB_FAST_OPP:
		हाल TI_ABB_SLOW_OPP:
			/* Valid values */
			अवरोध;
		शेष:
			dev_err(dev, "%s:[%d]v=%d, ABB=%d is invalid! Abort!\n",
				__func__, i, *volt_table, info->opp_sel);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Setup the min/max voltage स्थिरraपूर्णांकs from the supported list */
	c->min_uV = min_uV;
	c->max_uV = max_uV;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regulator_ops ti_abb_reg_ops = अणु
	.list_voltage = regulator_list_voltage_table,

	.set_voltage_sel = ti_abb_set_voltage_sel,
	.get_voltage_sel = ti_abb_get_voltage_sel,
पूर्ण;

/* Default ABB block offsets, IF this changes in future, create new one */
अटल स्थिर काष्ठा ti_abb_reg abb_regs_v1 = अणु
	/* WARNING: रेजिस्टरs are wrongly करोcumented in TRM */
	.setup_off		= 0x04,
	.control_off		= 0x00,

	.sr2_wtcnt_value_mask	= (0xff << 8),
	.fbb_sel_mask		= (0x01 << 2),
	.rbb_sel_mask		= (0x01 << 1),
	.sr2_en_mask		= (0x01 << 0),

	.opp_change_mask	= (0x01 << 2),
	.opp_sel_mask		= (0x03 << 0),
पूर्ण;

अटल स्थिर काष्ठा ti_abb_reg abb_regs_v2 = अणु
	.setup_off		= 0x00,
	.control_off		= 0x04,

	.sr2_wtcnt_value_mask	= (0xff << 8),
	.fbb_sel_mask		= (0x01 << 2),
	.rbb_sel_mask		= (0x01 << 1),
	.sr2_en_mask		= (0x01 << 0),

	.opp_change_mask	= (0x01 << 2),
	.opp_sel_mask		= (0x03 << 0),
पूर्ण;

अटल स्थिर काष्ठा ti_abb_reg abb_regs_generic = अणु
	.sr2_wtcnt_value_mask	= (0xff << 8),
	.fbb_sel_mask		= (0x01 << 2),
	.rbb_sel_mask		= (0x01 << 1),
	.sr2_en_mask		= (0x01 << 0),

	.opp_change_mask	= (0x01 << 2),
	.opp_sel_mask		= (0x03 << 0),
पूर्ण;

अटल स्थिर काष्ठा of_device_id ti_abb_of_match[] = अणु
	अणु.compatible = "ti,abb-v1", .data = &abb_regs_v1पूर्ण,
	अणु.compatible = "ti,abb-v2", .data = &abb_regs_v2पूर्ण,
	अणु.compatible = "ti,abb-v3", .data = &abb_regs_genericपूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, ti_abb_of_match);

/**
 * ti_abb_probe() - Initialize an ABB lकरो instance
 * @pdev: ABB platक्रमm device
 *
 * Initializes an inभागidual ABB LDO क्रम required Body-Bias. ABB is used to
 * addional bias supply to SoC modules क्रम घातer savings or mandatory stability
 * configuration at certain Operating Perक्रमmance Poपूर्णांकs(OPPs).
 *
 * Return: 0 on success or appropriate error value when fails
 */
अटल पूर्णांक ti_abb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा resource *res;
	काष्ठा ti_abb *abb;
	काष्ठा regulator_init_data *initdata = शून्य;
	काष्ठा regulator_dev *rdev = शून्य;
	काष्ठा regulator_desc *desc;
	काष्ठा regulation_स्थिरraपूर्णांकs *c;
	काष्ठा regulator_config config = अणु पूर्ण;
	अक्षर *pname;
	पूर्णांक ret = 0;

	match = of_match_device(ti_abb_of_match, dev);
	अगर (!match) अणु
		/* We करो not expect this to happen */
		dev_err(dev, "%s: Unable to match device\n", __func__);
		वापस -ENODEV;
	पूर्ण
	अगर (!match->data) अणु
		dev_err(dev, "%s: Bad data in match\n", __func__);
		वापस -EINVAL;
	पूर्ण

	abb = devm_kzalloc(dev, माप(काष्ठा ti_abb), GFP_KERNEL);
	अगर (!abb)
		वापस -ENOMEM;
	abb->regs = match->data;

	/* Map ABB resources */
	अगर (abb->regs->setup_off || abb->regs->control_off) अणु
		pname = "base-address";
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, pname);
		abb->base = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(abb->base))
			वापस PTR_ERR(abb->base);

		abb->setup_reg = abb->base + abb->regs->setup_off;
		abb->control_reg = abb->base + abb->regs->control_off;

	पूर्ण अन्यथा अणु
		pname = "control-address";
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, pname);
		abb->control_reg = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(abb->control_reg))
			वापस PTR_ERR(abb->control_reg);

		pname = "setup-address";
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, pname);
		abb->setup_reg = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(abb->setup_reg))
			वापस PTR_ERR(abb->setup_reg);
	पूर्ण

	pname = "int-address";
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, pname);
	अगर (!res) अणु
		dev_err(dev, "Missing '%s' IO resource\n", pname);
		वापस -ENODEV;
	पूर्ण
	/*
	 * We may have shared पूर्णांकerrupt रेजिस्टर offsets which are
	 * ग_लिखो-1-to-clear between करोमुख्यs ensuring exclusivity.
	 */
	abb->पूर्णांक_base = devm_ioremap(dev, res->start,
					     resource_size(res));
	अगर (!abb->पूर्णांक_base) अणु
		dev_err(dev, "Unable to map '%s'\n", pname);
		वापस -ENOMEM;
	पूर्ण

	/* Map Optional resources */
	pname = "efuse-address";
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, pname);
	अगर (!res) अणु
		dev_dbg(dev, "Missing '%s' IO resource\n", pname);
		ret = -ENODEV;
		जाओ skip_opt;
	पूर्ण

	/*
	 * We may have shared efuse रेजिस्टर offsets which are पढ़ो-only
	 * between करोमुख्यs
	 */
	abb->efuse_base = devm_ioremap(dev, res->start,
					       resource_size(res));
	अगर (!abb->efuse_base) अणु
		dev_err(dev, "Unable to map '%s'\n", pname);
		वापस -ENOMEM;
	पूर्ण

	pname = "ldo-address";
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, pname);
	अगर (!res) अणु
		dev_dbg(dev, "Missing '%s' IO resource\n", pname);
		ret = -ENODEV;
		जाओ skip_opt;
	पूर्ण
	abb->lकरो_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(abb->lकरो_base))
		वापस PTR_ERR(abb->lकरो_base);

	/* IF lकरो_base is set, the following are mandatory */
	pname = "ti,ldovbb-override-mask";
	ret =
	    of_property_पढ़ो_u32(pdev->dev.of_node, pname,
				 &abb->lकरोvbb_override_mask);
	अगर (ret) अणु
		dev_err(dev, "Missing '%s' (%d)\n", pname, ret);
		वापस ret;
	पूर्ण
	अगर (!abb->lकरोvbb_override_mask) अणु
		dev_err(dev, "Invalid property:'%s' set as 0!\n", pname);
		वापस -EINVAL;
	पूर्ण

	pname = "ti,ldovbb-vset-mask";
	ret =
	    of_property_पढ़ो_u32(pdev->dev.of_node, pname,
				 &abb->lकरोvbb_vset_mask);
	अगर (ret) अणु
		dev_err(dev, "Missing '%s' (%d)\n", pname, ret);
		वापस ret;
	पूर्ण
	अगर (!abb->lकरोvbb_vset_mask) अणु
		dev_err(dev, "Invalid property:'%s' set as 0!\n", pname);
		वापस -EINVAL;
	पूर्ण

skip_opt:
	pname = "ti,tranxdone-status-mask";
	ret =
	    of_property_पढ़ो_u32(pdev->dev.of_node, pname,
				 &abb->txकरोne_mask);
	अगर (ret) अणु
		dev_err(dev, "Missing '%s' (%d)\n", pname, ret);
		वापस ret;
	पूर्ण
	अगर (!abb->txकरोne_mask) अणु
		dev_err(dev, "Invalid property:'%s' set as 0!\n", pname);
		वापस -EINVAL;
	पूर्ण

	initdata = of_get_regulator_init_data(dev, pdev->dev.of_node,
					      &abb->rdesc);
	अगर (!initdata) अणु
		dev_err(dev, "%s: Unable to alloc regulator init data\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	/* init ABB opp_sel table */
	ret = ti_abb_init_table(dev, abb, initdata);
	अगर (ret)
		वापस ret;

	/* init ABB timing */
	ret = ti_abb_init_timings(dev, abb);
	अगर (ret)
		वापस ret;

	desc = &abb->rdesc;
	desc->name = dev_name(dev);
	desc->owner = THIS_MODULE;
	desc->type = REGULATOR_VOLTAGE;
	desc->ops = &ti_abb_reg_ops;

	c = &initdata->स्थिरraपूर्णांकs;
	अगर (desc->n_voltages > 1)
		c->valid_ops_mask |= REGULATOR_CHANGE_VOLTAGE;
	c->always_on = true;

	config.dev = dev;
	config.init_data = initdata;
	config.driver_data = abb;
	config.of_node = pdev->dev.of_node;

	rdev = devm_regulator_रेजिस्टर(dev, desc, &config);
	अगर (IS_ERR(rdev)) अणु
		ret = PTR_ERR(rdev);
		dev_err(dev, "%s: failed to register regulator(%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण
	platक्रमm_set_drvdata(pdev, rdev);

	/* Enable the lकरो अगर not alपढ़ोy करोne by bootloader */
	ti_abb_rmw(abb->regs->sr2_en_mask, 1, abb->setup_reg);

	वापस 0;
पूर्ण

MODULE_ALIAS("platform:ti_abb");

अटल काष्ठा platक्रमm_driver ti_abb_driver = अणु
	.probe = ti_abb_probe,
	.driver = अणु
		   .name = "ti_abb",
		   .of_match_table = of_match_ptr(ti_abb_of_match),
		   पूर्ण,
पूर्ण;
module_platक्रमm_driver(ti_abb_driver);

MODULE_DESCRIPTION("Texas Instruments ABB LDO regulator driver");
MODULE_AUTHOR("Texas Instruments Inc.");
MODULE_LICENSE("GPL v2");
