<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2017 HiSilicon Technologies Co., Ltd.
 *
 * Simple HiSilicon phase घड़ी implementation.
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "clk.h"

काष्ठा clk_hisi_phase अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*reg;
	u32		*phase_degrees;
	u32		*phase_regvals;
	u8		phase_num;
	u32		mask;
	u8		shअगरt;
	u8		flags;
	spinlock_t	*lock;
पूर्ण;

#घोषणा to_clk_hisi_phase(_hw) container_of(_hw, काष्ठा clk_hisi_phase, hw)

अटल पूर्णांक hisi_phase_regval_to_degrees(काष्ठा clk_hisi_phase *phase,
					u32 regval)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < phase->phase_num; i++)
		अगर (phase->phase_regvals[i] == regval)
			वापस phase->phase_degrees[i];

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hisi_clk_get_phase(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hisi_phase *phase = to_clk_hisi_phase(hw);
	u32 regval;

	regval = पढ़ोl(phase->reg);
	regval = (regval & phase->mask) >> phase->shअगरt;

	वापस hisi_phase_regval_to_degrees(phase, regval);
पूर्ण

अटल पूर्णांक hisi_phase_degrees_to_regval(काष्ठा clk_hisi_phase *phase,
					पूर्णांक degrees)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < phase->phase_num; i++)
		अगर (phase->phase_degrees[i] == degrees)
			वापस phase->phase_regvals[i];

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hisi_clk_set_phase(काष्ठा clk_hw *hw, पूर्णांक degrees)
अणु
	काष्ठा clk_hisi_phase *phase = to_clk_hisi_phase(hw);
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक regval;
	u32 val;

	regval = hisi_phase_degrees_to_regval(phase, degrees);
	अगर (regval < 0)
		वापस regval;

	spin_lock_irqsave(phase->lock, flags);

	val = पढ़ोl(phase->reg);
	val &= ~phase->mask;
	val |= regval << phase->shअगरt;
	ग_लिखोl(val, phase->reg);

	spin_unlock_irqrestore(phase->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_phase_ops = अणु
	.get_phase = hisi_clk_get_phase,
	.set_phase = hisi_clk_set_phase,
पूर्ण;

काष्ठा clk *clk_रेजिस्टर_hisi_phase(काष्ठा device *dev,
		स्थिर काष्ठा hisi_phase_घड़ी *clks,
		व्योम __iomem *base, spinlock_t *lock)
अणु
	काष्ठा clk_hisi_phase *phase;
	काष्ठा clk_init_data init;

	phase = devm_kzalloc(dev, माप(काष्ठा clk_hisi_phase), GFP_KERNEL);
	अगर (!phase)
		वापस ERR_PTR(-ENOMEM);

	init.name = clks->name;
	init.ops = &clk_phase_ops;
	init.flags = clks->flags;
	init.parent_names = clks->parent_names ? &clks->parent_names : शून्य;
	init.num_parents = clks->parent_names ? 1 : 0;

	phase->reg = base + clks->offset;
	phase->shअगरt = clks->shअगरt;
	phase->mask = (BIT(clks->width) - 1) << clks->shअगरt;
	phase->lock = lock;
	phase->phase_degrees = clks->phase_degrees;
	phase->phase_regvals = clks->phase_regvals;
	phase->phase_num = clks->phase_num;
	phase->hw.init = &init;

	वापस devm_clk_रेजिस्टर(dev, &phase->hw);
पूर्ण
EXPORT_SYMBOL_GPL(clk_रेजिस्टर_hisi_phase);
