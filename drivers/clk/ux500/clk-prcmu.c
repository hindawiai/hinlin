<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PRCMU घड़ी implementation क्रम ux500 platक्रमm.
 *
 * Copyright (C) 2012 ST-Ericsson SA
 * Author: Ulf Hansson <ulf.hansson@linaro.org>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/mfd/dbx500-prcmu.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश "clk.h"

#घोषणा to_clk_prcmu(_hw) container_of(_hw, काष्ठा clk_prcmu, hw)

काष्ठा clk_prcmu अणु
	काष्ठा clk_hw hw;
	u8 cg_sel;
	पूर्णांक is_prepared;
	पूर्णांक is_enabled;
	पूर्णांक opp_requested;
पूर्ण;

/* PRCMU घड़ी operations. */

अटल पूर्णांक clk_prcmu_prepare(काष्ठा clk_hw *hw)
अणु
	पूर्णांक ret;
	काष्ठा clk_prcmu *clk = to_clk_prcmu(hw);

	ret = prcmu_request_घड़ी(clk->cg_sel, true);
	अगर (!ret)
		clk->is_prepared = 1;

	वापस ret;
पूर्ण

अटल व्योम clk_prcmu_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_prcmu *clk = to_clk_prcmu(hw);
	अगर (prcmu_request_घड़ी(clk->cg_sel, false))
		pr_err("clk_prcmu: %s failed to disable %s.\n", __func__,
			clk_hw_get_name(hw));
	अन्यथा
		clk->is_prepared = 0;
पूर्ण

अटल पूर्णांक clk_prcmu_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_prcmu *clk = to_clk_prcmu(hw);
	वापस clk->is_prepared;
पूर्ण

अटल पूर्णांक clk_prcmu_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_prcmu *clk = to_clk_prcmu(hw);
	clk->is_enabled = 1;
	वापस 0;
पूर्ण

अटल व्योम clk_prcmu_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_prcmu *clk = to_clk_prcmu(hw);
	clk->is_enabled = 0;
पूर्ण

अटल पूर्णांक clk_prcmu_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_prcmu *clk = to_clk_prcmu(hw);
	वापस clk->is_enabled;
पूर्ण

अटल अचिन्हित दीर्घ clk_prcmu_recalc_rate(काष्ठा clk_hw *hw,
					   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_prcmu *clk = to_clk_prcmu(hw);
	वापस prcmu_घड़ी_rate(clk->cg_sel);
पूर्ण

अटल दीर्घ clk_prcmu_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा clk_prcmu *clk = to_clk_prcmu(hw);
	वापस prcmu_round_घड़ी_rate(clk->cg_sel, rate);
पूर्ण

अटल पूर्णांक clk_prcmu_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_prcmu *clk = to_clk_prcmu(hw);
	वापस prcmu_set_घड़ी_rate(clk->cg_sel, rate);
पूर्ण

अटल पूर्णांक clk_prcmu_opp_prepare(काष्ठा clk_hw *hw)
अणु
	पूर्णांक err;
	काष्ठा clk_prcmu *clk = to_clk_prcmu(hw);

	अगर (!clk->opp_requested) अणु
		err = prcmu_qos_add_requirement(PRCMU_QOS_APE_OPP,
						(अक्षर *)clk_hw_get_name(hw),
						100);
		अगर (err) अणु
			pr_err("clk_prcmu: %s fail req APE OPP for %s.\n",
				__func__, clk_hw_get_name(hw));
			वापस err;
		पूर्ण
		clk->opp_requested = 1;
	पूर्ण

	err = prcmu_request_घड़ी(clk->cg_sel, true);
	अगर (err) अणु
		prcmu_qos_हटाओ_requirement(PRCMU_QOS_APE_OPP,
					(अक्षर *)clk_hw_get_name(hw));
		clk->opp_requested = 0;
		वापस err;
	पूर्ण

	clk->is_prepared = 1;
	वापस 0;
पूर्ण

अटल व्योम clk_prcmu_opp_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_prcmu *clk = to_clk_prcmu(hw);

	अगर (prcmu_request_घड़ी(clk->cg_sel, false)) अणु
		pr_err("clk_prcmu: %s failed to disable %s.\n", __func__,
			clk_hw_get_name(hw));
		वापस;
	पूर्ण

	अगर (clk->opp_requested) अणु
		prcmu_qos_हटाओ_requirement(PRCMU_QOS_APE_OPP,
					(अक्षर *)clk_hw_get_name(hw));
		clk->opp_requested = 0;
	पूर्ण

	clk->is_prepared = 0;
पूर्ण

अटल पूर्णांक clk_prcmu_opp_volt_prepare(काष्ठा clk_hw *hw)
अणु
	पूर्णांक err;
	काष्ठा clk_prcmu *clk = to_clk_prcmu(hw);

	अगर (!clk->opp_requested) अणु
		err = prcmu_request_ape_opp_100_voltage(true);
		अगर (err) अणु
			pr_err("clk_prcmu: %s fail req APE OPP VOLT for %s.\n",
				__func__, clk_hw_get_name(hw));
			वापस err;
		पूर्ण
		clk->opp_requested = 1;
	पूर्ण

	err = prcmu_request_घड़ी(clk->cg_sel, true);
	अगर (err) अणु
		prcmu_request_ape_opp_100_voltage(false);
		clk->opp_requested = 0;
		वापस err;
	पूर्ण

	clk->is_prepared = 1;
	वापस 0;
पूर्ण

अटल व्योम clk_prcmu_opp_volt_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_prcmu *clk = to_clk_prcmu(hw);

	अगर (prcmu_request_घड़ी(clk->cg_sel, false)) अणु
		pr_err("clk_prcmu: %s failed to disable %s.\n", __func__,
			clk_hw_get_name(hw));
		वापस;
	पूर्ण

	अगर (clk->opp_requested) अणु
		prcmu_request_ape_opp_100_voltage(false);
		clk->opp_requested = 0;
	पूर्ण

	clk->is_prepared = 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_prcmu_scalable_ops = अणु
	.prepare = clk_prcmu_prepare,
	.unprepare = clk_prcmu_unprepare,
	.is_prepared = clk_prcmu_is_prepared,
	.enable = clk_prcmu_enable,
	.disable = clk_prcmu_disable,
	.is_enabled = clk_prcmu_is_enabled,
	.recalc_rate = clk_prcmu_recalc_rate,
	.round_rate = clk_prcmu_round_rate,
	.set_rate = clk_prcmu_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops clk_prcmu_gate_ops = अणु
	.prepare = clk_prcmu_prepare,
	.unprepare = clk_prcmu_unprepare,
	.is_prepared = clk_prcmu_is_prepared,
	.enable = clk_prcmu_enable,
	.disable = clk_prcmu_disable,
	.is_enabled = clk_prcmu_is_enabled,
	.recalc_rate = clk_prcmu_recalc_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops clk_prcmu_scalable_rate_ops = अणु
	.is_enabled = clk_prcmu_is_enabled,
	.recalc_rate = clk_prcmu_recalc_rate,
	.round_rate = clk_prcmu_round_rate,
	.set_rate = clk_prcmu_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops clk_prcmu_rate_ops = अणु
	.is_enabled = clk_prcmu_is_enabled,
	.recalc_rate = clk_prcmu_recalc_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops clk_prcmu_opp_gate_ops = अणु
	.prepare = clk_prcmu_opp_prepare,
	.unprepare = clk_prcmu_opp_unprepare,
	.is_prepared = clk_prcmu_is_prepared,
	.enable = clk_prcmu_enable,
	.disable = clk_prcmu_disable,
	.is_enabled = clk_prcmu_is_enabled,
	.recalc_rate = clk_prcmu_recalc_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops clk_prcmu_opp_volt_scalable_ops = अणु
	.prepare = clk_prcmu_opp_volt_prepare,
	.unprepare = clk_prcmu_opp_volt_unprepare,
	.is_prepared = clk_prcmu_is_prepared,
	.enable = clk_prcmu_enable,
	.disable = clk_prcmu_disable,
	.is_enabled = clk_prcmu_is_enabled,
	.recalc_rate = clk_prcmu_recalc_rate,
	.round_rate = clk_prcmu_round_rate,
	.set_rate = clk_prcmu_set_rate,
पूर्ण;

अटल काष्ठा clk *clk_reg_prcmu(स्थिर अक्षर *name,
				 स्थिर अक्षर *parent_name,
				 u8 cg_sel,
				 अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ flags,
				 स्थिर काष्ठा clk_ops *clk_prcmu_ops)
अणु
	काष्ठा clk_prcmu *clk;
	काष्ठा clk_init_data clk_prcmu_init;
	काष्ठा clk *clk_reg;

	अगर (!name) अणु
		pr_err("clk_prcmu: %s invalid arguments passed\n", __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	clk = kzalloc(माप(*clk), GFP_KERNEL);
	अगर (!clk)
		वापस ERR_PTR(-ENOMEM);

	clk->cg_sel = cg_sel;
	clk->is_prepared = 1;
	clk->is_enabled = 1;
	clk->opp_requested = 0;
	/* "rate" can be used क्रम changing the initial frequency */
	अगर (rate)
		prcmu_set_घड़ी_rate(cg_sel, rate);

	clk_prcmu_init.name = name;
	clk_prcmu_init.ops = clk_prcmu_ops;
	clk_prcmu_init.flags = flags;
	clk_prcmu_init.parent_names = (parent_name ? &parent_name : शून्य);
	clk_prcmu_init.num_parents = (parent_name ? 1 : 0);
	clk->hw.init = &clk_prcmu_init;

	clk_reg = clk_रेजिस्टर(शून्य, &clk->hw);
	अगर (IS_ERR_OR_शून्य(clk_reg))
		जाओ मुक्त_clk;

	वापस clk_reg;

मुक्त_clk:
	kमुक्त(clk);
	pr_err("clk_prcmu: %s failed to register clk\n", __func__);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

काष्ठा clk *clk_reg_prcmu_scalable(स्थिर अक्षर *name,
				   स्थिर अक्षर *parent_name,
				   u8 cg_sel,
				   अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ flags)
अणु
	वापस clk_reg_prcmu(name, parent_name, cg_sel, rate, flags,
			&clk_prcmu_scalable_ops);
पूर्ण

काष्ठा clk *clk_reg_prcmu_gate(स्थिर अक्षर *name,
			       स्थिर अक्षर *parent_name,
			       u8 cg_sel,
			       अचिन्हित दीर्घ flags)
अणु
	वापस clk_reg_prcmu(name, parent_name, cg_sel, 0, flags,
			&clk_prcmu_gate_ops);
पूर्ण

काष्ठा clk *clk_reg_prcmu_scalable_rate(स्थिर अक्षर *name,
					स्थिर अक्षर *parent_name,
					u8 cg_sel,
					अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ flags)
अणु
	वापस clk_reg_prcmu(name, parent_name, cg_sel, rate, flags,
			&clk_prcmu_scalable_rate_ops);
पूर्ण

काष्ठा clk *clk_reg_prcmu_rate(स्थिर अक्षर *name,
			       स्थिर अक्षर *parent_name,
			       u8 cg_sel,
			       अचिन्हित दीर्घ flags)
अणु
	वापस clk_reg_prcmu(name, parent_name, cg_sel, 0, flags,
			&clk_prcmu_rate_ops);
पूर्ण

काष्ठा clk *clk_reg_prcmu_opp_gate(स्थिर अक्षर *name,
				   स्थिर अक्षर *parent_name,
				   u8 cg_sel,
				   अचिन्हित दीर्घ flags)
अणु
	वापस clk_reg_prcmu(name, parent_name, cg_sel, 0, flags,
			&clk_prcmu_opp_gate_ops);
पूर्ण

काष्ठा clk *clk_reg_prcmu_opp_volt_scalable(स्थिर अक्षर *name,
					    स्थिर अक्षर *parent_name,
					    u8 cg_sel,
					    अचिन्हित दीर्घ rate,
					    अचिन्हित दीर्घ flags)
अणु
	वापस clk_reg_prcmu(name, parent_name, cg_sel, rate, flags,
			&clk_prcmu_opp_volt_scalable_ops);
पूर्ण
