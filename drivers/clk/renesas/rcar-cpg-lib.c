<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * R-Car Gen3 Clock Pulse Generator Library
 *
 * Copyright (C) 2015-2018 Glider bvba
 * Copyright (C) 2019 Renesas Electronics Corp.
 *
 * Based on clk-rcar-gen3.c
 *
 * Copyright (C) 2015 Renesas Electronics Corp.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>

#समावेश "rcar-cpg-lib.h"

spinlock_t cpg_lock;

व्योम cpg_reg_modअगरy(व्योम __iomem *reg, u32 clear, u32 set)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&cpg_lock, flags);
	val = पढ़ोl(reg);
	val &= ~clear;
	val |= set;
	ग_लिखोl(val, reg);
	spin_unlock_irqrestore(&cpg_lock, flags);
पूर्ण;

अटल पूर्णांक cpg_simple_notअगरier_call(काष्ठा notअगरier_block *nb,
				    अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा cpg_simple_notअगरier *csn =
		container_of(nb, काष्ठा cpg_simple_notअगरier, nb);

	चयन (action) अणु
	हाल PM_EVENT_SUSPEND:
		csn->saved = पढ़ोl(csn->reg);
		वापस NOTIFY_OK;

	हाल PM_EVENT_RESUME:
		ग_लिखोl(csn->saved, csn->reg);
		वापस NOTIFY_OK;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

व्योम cpg_simple_notअगरier_रेजिस्टर(काष्ठा raw_notअगरier_head *notअगरiers,
				  काष्ठा cpg_simple_notअगरier *csn)
अणु
	csn->nb.notअगरier_call = cpg_simple_notअगरier_call;
	raw_notअगरier_chain_रेजिस्टर(notअगरiers, &csn->nb);
पूर्ण

/*
 * SDn Clock
 */
#घोषणा CPG_SD_STP_HCK		BIT(9)
#घोषणा CPG_SD_STP_CK		BIT(8)

#घोषणा CPG_SD_STP_MASK		(CPG_SD_STP_HCK | CPG_SD_STP_CK)
#घोषणा CPG_SD_FC_MASK		(0x7 << 2 | 0x3 << 0)

#घोषणा CPG_SD_DIV_TABLE_DATA(stp_hck, sd_srcfc, sd_fc, sd_भाग) \
अणु \
	.val = ((stp_hck) ? CPG_SD_STP_HCK : 0) | \
	       ((sd_srcfc) << 2) | \
	       ((sd_fc) << 0), \
	.भाग = (sd_भाग), \
पूर्ण

काष्ठा sd_भाग_प्रकारable अणु
	u32 val;
	अचिन्हित पूर्णांक भाग;
पूर्ण;

काष्ठा sd_घड़ी अणु
	काष्ठा clk_hw hw;
	स्थिर काष्ठा sd_भाग_प्रकारable *भाग_प्रकारable;
	काष्ठा cpg_simple_notअगरier csn;
	अचिन्हित पूर्णांक भाग_num;
	अचिन्हित पूर्णांक cur_भाग_idx;
पूर्ण;

/* SDn भागider
 *           sd_srcfc   sd_fc   भाग
 * stp_hck   (भाग)      (भाग)     = sd_srcfc x sd_fc
 *---------------------------------------------------------
 *  0         0 (1)      1 (4)      4 : SDR104 / HS200 / HS400 (8 TAP)
 *  0         1 (2)      1 (4)      8 : SDR50
 *  1         2 (4)      1 (4)     16 : HS / SDR25
 *  1         3 (8)      1 (4)     32 : NS / SDR12
 *  1         4 (16)     1 (4)     64
 *  0         0 (1)      0 (2)      2
 *  0         1 (2)      0 (2)      4 : SDR104 / HS200 / HS400 (4 TAP)
 *  1         2 (4)      0 (2)      8
 *  1         3 (8)      0 (2)     16
 *  1         4 (16)     0 (2)     32
 *
 *  NOTE: There is a quirk option to ignore the first row of the भागiders
 *  table when searching क्रम suitable settings. This is because HS400 on
 *  early ES versions of H3 and M3-W requires a specअगरic setting to work.
 */
अटल स्थिर काष्ठा sd_भाग_प्रकारable cpg_sd_भाग_प्रकारable[] = अणु
/*	CPG_SD_DIV_TABLE_DATA(stp_hck,  sd_srcfc,   sd_fc,  sd_भाग) */
	CPG_SD_DIV_TABLE_DATA(0,        0,          1,        4),
	CPG_SD_DIV_TABLE_DATA(0,        1,          1,        8),
	CPG_SD_DIV_TABLE_DATA(1,        2,          1,       16),
	CPG_SD_DIV_TABLE_DATA(1,        3,          1,       32),
	CPG_SD_DIV_TABLE_DATA(1,        4,          1,       64),
	CPG_SD_DIV_TABLE_DATA(0,        0,          0,        2),
	CPG_SD_DIV_TABLE_DATA(0,        1,          0,        4),
	CPG_SD_DIV_TABLE_DATA(1,        2,          0,        8),
	CPG_SD_DIV_TABLE_DATA(1,        3,          0,       16),
	CPG_SD_DIV_TABLE_DATA(1,        4,          0,       32),
पूर्ण;

#घोषणा to_sd_घड़ी(_hw) container_of(_hw, काष्ठा sd_घड़ी, hw)

अटल पूर्णांक cpg_sd_घड़ी_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा sd_घड़ी *घड़ी = to_sd_घड़ी(hw);

	cpg_reg_modअगरy(घड़ी->csn.reg, CPG_SD_STP_MASK,
		       घड़ी->भाग_प्रकारable[घड़ी->cur_भाग_idx].val &
		       CPG_SD_STP_MASK);

	वापस 0;
पूर्ण

अटल व्योम cpg_sd_घड़ी_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा sd_घड़ी *घड़ी = to_sd_घड़ी(hw);

	cpg_reg_modअगरy(घड़ी->csn.reg, 0, CPG_SD_STP_MASK);
पूर्ण

अटल पूर्णांक cpg_sd_घड़ी_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा sd_घड़ी *घड़ी = to_sd_घड़ी(hw);

	वापस !(पढ़ोl(घड़ी->csn.reg) & CPG_SD_STP_MASK);
पूर्ण

अटल अचिन्हित दीर्घ cpg_sd_घड़ी_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sd_घड़ी *घड़ी = to_sd_घड़ी(hw);

	वापस DIV_ROUND_CLOSEST(parent_rate,
				 घड़ी->भाग_प्रकारable[घड़ी->cur_भाग_idx].भाग);
पूर्ण

अटल पूर्णांक cpg_sd_घड़ी_determine_rate(काष्ठा clk_hw *hw,
				       काष्ठा clk_rate_request *req)
अणु
	अचिन्हित दीर्घ best_rate = अच_दीर्घ_उच्च, dअगरf_min = अच_दीर्घ_उच्च;
	काष्ठा sd_घड़ी *घड़ी = to_sd_घड़ी(hw);
	अचिन्हित दीर्घ calc_rate, dअगरf;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < घड़ी->भाग_num; i++) अणु
		calc_rate = DIV_ROUND_CLOSEST(req->best_parent_rate,
					      घड़ी->भाग_प्रकारable[i].भाग);
		अगर (calc_rate < req->min_rate || calc_rate > req->max_rate)
			जारी;

		dअगरf = calc_rate > req->rate ? calc_rate - req->rate
					     : req->rate - calc_rate;
		अगर (dअगरf < dअगरf_min) अणु
			best_rate = calc_rate;
			dअगरf_min = dअगरf;
		पूर्ण
	पूर्ण

	अगर (best_rate == अच_दीर्घ_उच्च)
		वापस -EINVAL;

	req->rate = best_rate;
	वापस 0;
पूर्ण

अटल पूर्णांक cpg_sd_घड़ी_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sd_घड़ी *घड़ी = to_sd_घड़ी(hw);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < घड़ी->भाग_num; i++)
		अगर (rate == DIV_ROUND_CLOSEST(parent_rate,
					      घड़ी->भाग_प्रकारable[i].भाग))
			अवरोध;

	अगर (i >= घड़ी->भाग_num)
		वापस -EINVAL;

	घड़ी->cur_भाग_idx = i;

	cpg_reg_modअगरy(घड़ी->csn.reg, CPG_SD_STP_MASK | CPG_SD_FC_MASK,
		       घड़ी->भाग_प्रकारable[i].val &
		       (CPG_SD_STP_MASK | CPG_SD_FC_MASK));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops cpg_sd_घड़ी_ops = अणु
	.enable = cpg_sd_घड़ी_enable,
	.disable = cpg_sd_घड़ी_disable,
	.is_enabled = cpg_sd_घड़ी_is_enabled,
	.recalc_rate = cpg_sd_घड़ी_recalc_rate,
	.determine_rate = cpg_sd_घड़ी_determine_rate,
	.set_rate = cpg_sd_घड़ी_set_rate,
पूर्ण;

काष्ठा clk * __init cpg_sd_clk_रेजिस्टर(स्थिर अक्षर *name,
	व्योम __iomem *base, अचिन्हित पूर्णांक offset, स्थिर अक्षर *parent_name,
	काष्ठा raw_notअगरier_head *notअगरiers, bool skip_first)
अणु
	काष्ठा clk_init_data init = अणुपूर्ण;
	काष्ठा sd_घड़ी *घड़ी;
	काष्ठा clk *clk;
	u32 val;

	घड़ी = kzalloc(माप(*घड़ी), GFP_KERNEL);
	अगर (!घड़ी)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &cpg_sd_घड़ी_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	घड़ी->csn.reg = base + offset;
	घड़ी->hw.init = &init;
	घड़ी->भाग_प्रकारable = cpg_sd_भाग_प्रकारable;
	घड़ी->भाग_num = ARRAY_SIZE(cpg_sd_भाग_प्रकारable);

	अगर (skip_first) अणु
		घड़ी->भाग_प्रकारable++;
		घड़ी->भाग_num--;
	पूर्ण

	val = पढ़ोl(घड़ी->csn.reg) & ~CPG_SD_FC_MASK;
	val |= CPG_SD_STP_MASK | (घड़ी->भाग_प्रकारable[0].val & CPG_SD_FC_MASK);
	ग_लिखोl(val, घड़ी->csn.reg);

	clk = clk_रेजिस्टर(शून्य, &घड़ी->hw);
	अगर (IS_ERR(clk))
		जाओ मुक्त_घड़ी;

	cpg_simple_notअगरier_रेजिस्टर(notअगरiers, &घड़ी->csn);
	वापस clk;

मुक्त_घड़ी:
	kमुक्त(घड़ी);
	वापस clk;
पूर्ण


