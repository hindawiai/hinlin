<शैली गुरु>
/*
 * mmp mix(भाग and mux) घड़ी operation source file
 *
 * Copyright (C) 2014 Marvell
 * Chao Xie <chao.xie@marvell.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>

#समावेश "clk.h"

/*
 * The mix घड़ी is a घड़ी combined mux and भाग type घड़ी.
 * Because the भाग field and mux field need to be set at same
 * समय, we can not भागide it पूर्णांकo 2 types of घड़ी
 */

#घोषणा to_clk_mix(hw)	container_of(hw, काष्ठा mmp_clk_mix, hw)

अटल अचिन्हित पूर्णांक _get_maxभाग(काष्ठा mmp_clk_mix *mix)
अणु
	अचिन्हित पूर्णांक भाग_mask = (1 << mix->reg_info.width_भाग) - 1;
	अचिन्हित पूर्णांक maxभाग = 0;
	काष्ठा clk_भाग_प्रकारable *clkt;

	अगर (mix->भाग_flags & CLK_DIVIDER_ONE_BASED)
		वापस भाग_mask;
	अगर (mix->भाग_flags & CLK_DIVIDER_POWER_OF_TWO)
		वापस 1 << भाग_mask;
	अगर (mix->भाग_प्रकारable) अणु
		क्रम (clkt = mix->भाग_प्रकारable; clkt->भाग; clkt++)
			अगर (clkt->भाग > maxभाग)
				maxभाग = clkt->भाग;
		वापस maxभाग;
	पूर्ण
	वापस भाग_mask + 1;
पूर्ण

अटल अचिन्हित पूर्णांक _get_भाग(काष्ठा mmp_clk_mix *mix, अचिन्हित पूर्णांक val)
अणु
	काष्ठा clk_भाग_प्रकारable *clkt;

	अगर (mix->भाग_flags & CLK_DIVIDER_ONE_BASED)
		वापस val;
	अगर (mix->भाग_flags & CLK_DIVIDER_POWER_OF_TWO)
		वापस 1 << val;
	अगर (mix->भाग_प्रकारable) अणु
		क्रम (clkt = mix->भाग_प्रकारable; clkt->भाग; clkt++)
			अगर (clkt->val == val)
				वापस clkt->भाग;
		अगर (clkt->भाग == 0)
			वापस 0;
	पूर्ण
	वापस val + 1;
पूर्ण

अटल अचिन्हित पूर्णांक _get_mux(काष्ठा mmp_clk_mix *mix, अचिन्हित पूर्णांक val)
अणु
	पूर्णांक num_parents = clk_hw_get_num_parents(&mix->hw);
	पूर्णांक i;

	अगर (mix->mux_flags & CLK_MUX_INDEX_BIT)
		वापस ffs(val) - 1;
	अगर (mix->mux_flags & CLK_MUX_INDEX_ONE)
		वापस val - 1;
	अगर (mix->mux_table) अणु
		क्रम (i = 0; i < num_parents; i++)
			अगर (mix->mux_table[i] == val)
				वापस i;
		अगर (i == num_parents)
			वापस 0;
	पूर्ण

	वापस val;
पूर्ण
अटल अचिन्हित पूर्णांक _get_भाग_val(काष्ठा mmp_clk_mix *mix, अचिन्हित पूर्णांक भाग)
अणु
	काष्ठा clk_भाग_प्रकारable *clkt;

	अगर (mix->भाग_flags & CLK_DIVIDER_ONE_BASED)
		वापस भाग;
	अगर (mix->भाग_flags & CLK_DIVIDER_POWER_OF_TWO)
		वापस __ffs(भाग);
	अगर (mix->भाग_प्रकारable) अणु
		क्रम (clkt = mix->भाग_प्रकारable; clkt->भाग; clkt++)
			अगर (clkt->भाग == भाग)
				वापस clkt->val;
		अगर (clkt->भाग == 0)
			वापस 0;
	पूर्ण

	वापस भाग - 1;
पूर्ण

अटल अचिन्हित पूर्णांक _get_mux_val(काष्ठा mmp_clk_mix *mix, अचिन्हित पूर्णांक mux)
अणु
	अगर (mix->mux_table)
		वापस mix->mux_table[mux];

	वापस mux;
पूर्ण

अटल व्योम _filter_clk_table(काष्ठा mmp_clk_mix *mix,
				काष्ठा mmp_clk_mix_clk_table *table,
				अचिन्हित पूर्णांक table_size)
अणु
	पूर्णांक i;
	काष्ठा mmp_clk_mix_clk_table *item;
	काष्ठा clk_hw *parent, *hw;
	अचिन्हित दीर्घ parent_rate;

	hw = &mix->hw;

	क्रम (i = 0; i < table_size; i++) अणु
		item = &table[i];
		parent = clk_hw_get_parent_by_index(hw, item->parent_index);
		parent_rate = clk_hw_get_rate(parent);
		अगर (parent_rate % item->rate) अणु
			item->valid = 0;
		पूर्ण अन्यथा अणु
			item->भागisor = parent_rate / item->rate;
			item->valid = 1;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक _set_rate(काष्ठा mmp_clk_mix *mix, u32 mux_val, u32 भाग_val,
			अचिन्हित पूर्णांक change_mux, अचिन्हित पूर्णांक change_भाग)
अणु
	काष्ठा mmp_clk_mix_reg_info *ri = &mix->reg_info;
	u8 width, shअगरt;
	u32 mux_भाग, fc_req;
	पूर्णांक ret, समयout = 50;
	अचिन्हित दीर्घ flags = 0;

	अगर (!change_mux && !change_भाग)
		वापस -EINVAL;

	अगर (mix->lock)
		spin_lock_irqsave(mix->lock, flags);

	अगर (mix->type == MMP_CLK_MIX_TYPE_V1
		|| mix->type == MMP_CLK_MIX_TYPE_V2)
		mux_भाग = पढ़ोl(ri->reg_clk_ctrl);
	अन्यथा
		mux_भाग = पढ़ोl(ri->reg_clk_sel);

	अगर (change_भाग) अणु
		width = ri->width_भाग;
		shअगरt = ri->shअगरt_भाग;
		mux_भाग &= ~MMP_CLK_BITS_MASK(width, shअगरt);
		mux_भाग |= MMP_CLK_BITS_SET_VAL(भाग_val, width, shअगरt);
	पूर्ण

	अगर (change_mux) अणु
		width = ri->width_mux;
		shअगरt = ri->shअगरt_mux;
		mux_भाग &= ~MMP_CLK_BITS_MASK(width, shअगरt);
		mux_भाग |= MMP_CLK_BITS_SET_VAL(mux_val, width, shअगरt);
	पूर्ण

	अगर (mix->type == MMP_CLK_MIX_TYPE_V1) अणु
		ग_लिखोl(mux_भाग, ri->reg_clk_ctrl);
	पूर्ण अन्यथा अगर (mix->type == MMP_CLK_MIX_TYPE_V2) अणु
		mux_भाग |= (1 << ri->bit_fc);
		ग_लिखोl(mux_भाग, ri->reg_clk_ctrl);

		करो अणु
			fc_req = पढ़ोl(ri->reg_clk_ctrl);
			समयout--;
			अगर (!(fc_req & (1 << ri->bit_fc)))
				अवरोध;
		पूर्ण जबतक (समयout);

		अगर (समयout == 0) अणु
			pr_err("%s:%s cannot do frequency change\n",
				__func__, clk_hw_get_name(&mix->hw));
			ret = -EBUSY;
			जाओ error;
		पूर्ण
	पूर्ण अन्यथा अणु
		fc_req = पढ़ोl(ri->reg_clk_ctrl);
		fc_req |= 1 << ri->bit_fc;
		ग_लिखोl(fc_req, ri->reg_clk_ctrl);
		ग_लिखोl(mux_भाग, ri->reg_clk_sel);
		fc_req &= ~(1 << ri->bit_fc);
	पूर्ण

	ret = 0;
error:
	अगर (mix->lock)
		spin_unlock_irqrestore(mix->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक mmp_clk_mix_determine_rate(काष्ठा clk_hw *hw,
				      काष्ठा clk_rate_request *req)
अणु
	काष्ठा mmp_clk_mix *mix = to_clk_mix(hw);
	काष्ठा mmp_clk_mix_clk_table *item;
	काष्ठा clk_hw *parent, *parent_best;
	अचिन्हित दीर्घ parent_rate, mix_rate, mix_rate_best, parent_rate_best;
	अचिन्हित दीर्घ gap, gap_best;
	u32 भाग_val_max;
	अचिन्हित पूर्णांक भाग;
	पूर्णांक i, j;


	mix_rate_best = 0;
	parent_rate_best = 0;
	gap_best = अच_दीर्घ_उच्च;
	parent_best = शून्य;

	अगर (mix->table) अणु
		क्रम (i = 0; i < mix->table_size; i++) अणु
			item = &mix->table[i];
			अगर (item->valid == 0)
				जारी;
			parent = clk_hw_get_parent_by_index(hw,
							item->parent_index);
			parent_rate = clk_hw_get_rate(parent);
			mix_rate = parent_rate / item->भागisor;
			gap = असल(mix_rate - req->rate);
			अगर (!parent_best || gap < gap_best) अणु
				parent_best = parent;
				parent_rate_best = parent_rate;
				mix_rate_best = mix_rate;
				gap_best = gap;
				अगर (gap_best == 0)
					जाओ found;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < clk_hw_get_num_parents(hw); i++) अणु
			parent = clk_hw_get_parent_by_index(hw, i);
			parent_rate = clk_hw_get_rate(parent);
			भाग_val_max = _get_maxभाग(mix);
			क्रम (j = 0; j < भाग_val_max; j++) अणु
				भाग = _get_भाग(mix, j);
				mix_rate = parent_rate / भाग;
				gap = असल(mix_rate - req->rate);
				अगर (!parent_best || gap < gap_best) अणु
					parent_best = parent;
					parent_rate_best = parent_rate;
					mix_rate_best = mix_rate;
					gap_best = gap;
					अगर (gap_best == 0)
						जाओ found;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

found:
	अगर (!parent_best)
		वापस -EINVAL;

	req->best_parent_rate = parent_rate_best;
	req->best_parent_hw = parent_best;
	req->rate = mix_rate_best;

	वापस 0;
पूर्ण

अटल पूर्णांक mmp_clk_mix_set_rate_and_parent(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ rate,
						अचिन्हित दीर्घ parent_rate,
						u8 index)
अणु
	काष्ठा mmp_clk_mix *mix = to_clk_mix(hw);
	अचिन्हित पूर्णांक भाग;
	u32 भाग_val, mux_val;

	भाग = parent_rate / rate;
	भाग_val = _get_भाग_val(mix, भाग);
	mux_val = _get_mux_val(mix, index);

	वापस _set_rate(mix, mux_val, भाग_val, 1, 1);
पूर्ण

अटल u8 mmp_clk_mix_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा mmp_clk_mix *mix = to_clk_mix(hw);
	काष्ठा mmp_clk_mix_reg_info *ri = &mix->reg_info;
	अचिन्हित दीर्घ flags = 0;
	u32 mux_भाग = 0;
	u8 width, shअगरt;
	u32 mux_val;

	अगर (mix->lock)
		spin_lock_irqsave(mix->lock, flags);

	अगर (mix->type == MMP_CLK_MIX_TYPE_V1
		|| mix->type == MMP_CLK_MIX_TYPE_V2)
		mux_भाग = पढ़ोl(ri->reg_clk_ctrl);
	अन्यथा
		mux_भाग = पढ़ोl(ri->reg_clk_sel);

	अगर (mix->lock)
		spin_unlock_irqrestore(mix->lock, flags);

	width = mix->reg_info.width_mux;
	shअगरt = mix->reg_info.shअगरt_mux;

	mux_val = MMP_CLK_BITS_GET_VAL(mux_भाग, width, shअगरt);

	वापस _get_mux(mix, mux_val);
पूर्ण

अटल अचिन्हित दीर्घ mmp_clk_mix_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा mmp_clk_mix *mix = to_clk_mix(hw);
	काष्ठा mmp_clk_mix_reg_info *ri = &mix->reg_info;
	अचिन्हित दीर्घ flags = 0;
	u32 mux_भाग = 0;
	u8 width, shअगरt;
	अचिन्हित पूर्णांक भाग;

	अगर (mix->lock)
		spin_lock_irqsave(mix->lock, flags);

	अगर (mix->type == MMP_CLK_MIX_TYPE_V1
		|| mix->type == MMP_CLK_MIX_TYPE_V2)
		mux_भाग = पढ़ोl(ri->reg_clk_ctrl);
	अन्यथा
		mux_भाग = पढ़ोl(ri->reg_clk_sel);

	अगर (mix->lock)
		spin_unlock_irqrestore(mix->lock, flags);

	width = mix->reg_info.width_भाग;
	shअगरt = mix->reg_info.shअगरt_भाग;

	भाग = _get_भाग(mix, MMP_CLK_BITS_GET_VAL(mux_भाग, width, shअगरt));

	वापस parent_rate / भाग;
पूर्ण

अटल पूर्णांक mmp_clk_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा mmp_clk_mix *mix = to_clk_mix(hw);
	काष्ठा mmp_clk_mix_clk_table *item;
	पूर्णांक i;
	u32 भाग_val, mux_val;

	अगर (mix->table) अणु
		क्रम (i = 0; i < mix->table_size; i++) अणु
			item = &mix->table[i];
			अगर (item->valid == 0)
				जारी;
			अगर (item->parent_index == index)
				अवरोध;
		पूर्ण
		अगर (i < mix->table_size) अणु
			भाग_val = _get_भाग_val(mix, item->भागisor);
			mux_val = _get_mux_val(mix, item->parent_index);
		पूर्ण अन्यथा
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		mux_val = _get_mux_val(mix, index);
		भाग_val = 0;
	पूर्ण

	वापस _set_rate(mix, mux_val, भाग_val, 1, भाग_val ? 1 : 0);
पूर्ण

अटल पूर्णांक mmp_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ best_parent_rate)
अणु
	काष्ठा mmp_clk_mix *mix = to_clk_mix(hw);
	काष्ठा mmp_clk_mix_clk_table *item;
	अचिन्हित दीर्घ parent_rate;
	अचिन्हित पूर्णांक best_भागisor;
	काष्ठा clk_hw *parent;
	पूर्णांक i;

	best_भागisor = best_parent_rate / rate;

	अगर (mix->table) अणु
		क्रम (i = 0; i < mix->table_size; i++) अणु
			item = &mix->table[i];
			अगर (item->valid == 0)
				जारी;
			parent = clk_hw_get_parent_by_index(hw,
							item->parent_index);
			parent_rate = clk_hw_get_rate(parent);
			अगर (parent_rate == best_parent_rate
				&& item->भागisor == best_भागisor)
				अवरोध;
		पूर्ण
		अगर (i < mix->table_size)
			वापस _set_rate(mix,
					_get_mux_val(mix, item->parent_index),
					_get_भाग_val(mix, item->भागisor),
					1, 1);
		अन्यथा
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < clk_hw_get_num_parents(hw); i++) अणु
			parent = clk_hw_get_parent_by_index(hw, i);
			parent_rate = clk_hw_get_rate(parent);
			अगर (parent_rate == best_parent_rate)
				अवरोध;
		पूर्ण
		अगर (i < clk_hw_get_num_parents(hw))
			वापस _set_rate(mix, _get_mux_val(mix, i),
					_get_भाग_val(mix, best_भागisor), 1, 1);
		अन्यथा
			वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mmp_clk_mix_init(काष्ठा clk_hw *hw)
अणु
	काष्ठा mmp_clk_mix *mix = to_clk_mix(hw);

	अगर (mix->table)
		_filter_clk_table(mix, mix->table, mix->table_size);

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops mmp_clk_mix_ops = अणु
	.determine_rate = mmp_clk_mix_determine_rate,
	.set_rate_and_parent = mmp_clk_mix_set_rate_and_parent,
	.set_rate = mmp_clk_set_rate,
	.set_parent = mmp_clk_set_parent,
	.get_parent = mmp_clk_mix_get_parent,
	.recalc_rate = mmp_clk_mix_recalc_rate,
	.init = mmp_clk_mix_init,
पूर्ण;

काष्ठा clk *mmp_clk_रेजिस्टर_mix(काष्ठा device *dev,
					स्थिर अक्षर *name,
					स्थिर अक्षर * स्थिर *parent_names,
					u8 num_parents,
					अचिन्हित दीर्घ flags,
					काष्ठा mmp_clk_mix_config *config,
					spinlock_t *lock)
अणु
	काष्ठा mmp_clk_mix *mix;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;
	माप_प्रकार table_bytes;

	mix = kzalloc(माप(*mix), GFP_KERNEL);
	अगर (!mix)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.flags = flags | CLK_GET_RATE_NOCACHE;
	init.parent_names = parent_names;
	init.num_parents = num_parents;
	init.ops = &mmp_clk_mix_ops;

	स_नकल(&mix->reg_info, &config->reg_info, माप(config->reg_info));
	अगर (config->table) अणु
		table_bytes = माप(*config->table) * config->table_size;
		mix->table = kmemdup(config->table, table_bytes, GFP_KERNEL);
		अगर (!mix->table)
			जाओ मुक्त_mix;

		mix->table_size = config->table_size;
	पूर्ण

	अगर (config->mux_table) अणु
		table_bytes = माप(u32) * num_parents;
		mix->mux_table = kmemdup(config->mux_table, table_bytes,
					 GFP_KERNEL);
		अगर (!mix->mux_table) अणु
			kमुक्त(mix->table);
			जाओ मुक्त_mix;
		पूर्ण
	पूर्ण

	mix->भाग_flags = config->भाग_flags;
	mix->mux_flags = config->mux_flags;
	mix->lock = lock;
	mix->hw.init = &init;

	अगर (config->reg_info.bit_fc >= 32)
		mix->type = MMP_CLK_MIX_TYPE_V1;
	अन्यथा अगर (config->reg_info.reg_clk_sel)
		mix->type = MMP_CLK_MIX_TYPE_V3;
	अन्यथा
		mix->type = MMP_CLK_MIX_TYPE_V2;
	clk = clk_रेजिस्टर(dev, &mix->hw);

	अगर (IS_ERR(clk)) अणु
		kमुक्त(mix->mux_table);
		kमुक्त(mix->table);
		kमुक्त(mix);
	पूर्ण

	वापस clk;

मुक्त_mix:
	kमुक्त(mix);
	वापस ERR_PTR(-ENOMEM);
पूर्ण
