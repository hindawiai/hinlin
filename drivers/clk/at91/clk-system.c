<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2013 Boris BREZILLON <b.brezillon@overkiz.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk/at91_pmc.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश "pmc.h"

#घोषणा SYSTEM_MAX_ID		31

#घोषणा SYSTEM_MAX_NAME_SZ	32

#घोषणा to_clk_प्रणाली(hw) container_of(hw, काष्ठा clk_प्रणाली, hw)
काष्ठा clk_प्रणाली अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	u8 id;
पूर्ण;

अटल अंतरभूत पूर्णांक is_pck(पूर्णांक id)
अणु
	वापस (id >= 8) && (id <= 15);
पूर्ण

अटल अंतरभूत bool clk_प्रणाली_पढ़ोy(काष्ठा regmap *regmap, पूर्णांक id)
अणु
	अचिन्हित पूर्णांक status;

	regmap_पढ़ो(regmap, AT91_PMC_SR, &status);

	वापस !!(status & (1 << id));
पूर्ण

अटल पूर्णांक clk_प्रणाली_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_प्रणाली *sys = to_clk_प्रणाली(hw);

	regmap_ग_लिखो(sys->regmap, AT91_PMC_SCER, 1 << sys->id);

	अगर (!is_pck(sys->id))
		वापस 0;

	जबतक (!clk_प्रणाली_पढ़ोy(sys->regmap, sys->id))
		cpu_relax();

	वापस 0;
पूर्ण

अटल व्योम clk_प्रणाली_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_प्रणाली *sys = to_clk_प्रणाली(hw);

	regmap_ग_लिखो(sys->regmap, AT91_PMC_SCDR, 1 << sys->id);
पूर्ण

अटल पूर्णांक clk_प्रणाली_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_प्रणाली *sys = to_clk_प्रणाली(hw);
	अचिन्हित पूर्णांक status;

	regmap_पढ़ो(sys->regmap, AT91_PMC_SCSR, &status);

	अगर (!(status & (1 << sys->id)))
		वापस 0;

	अगर (!is_pck(sys->id))
		वापस 1;

	regmap_पढ़ो(sys->regmap, AT91_PMC_SR, &status);

	वापस !!(status & (1 << sys->id));
पूर्ण

अटल स्थिर काष्ठा clk_ops प्रणाली_ops = अणु
	.prepare = clk_प्रणाली_prepare,
	.unprepare = clk_प्रणाली_unprepare,
	.is_prepared = clk_प्रणाली_is_prepared,
पूर्ण;

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_प्रणाली(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			 स्थिर अक्षर *parent_name, u8 id)
अणु
	काष्ठा clk_प्रणाली *sys;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	अगर (!parent_name || id > SYSTEM_MAX_ID)
		वापस ERR_PTR(-EINVAL);

	sys = kzalloc(माप(*sys), GFP_KERNEL);
	अगर (!sys)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &प्रणाली_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = CLK_SET_RATE_PARENT;

	sys->id = id;
	sys->hw.init = &init;
	sys->regmap = regmap;

	hw = &sys->hw;
	ret = clk_hw_रेजिस्टर(शून्य, &sys->hw);
	अगर (ret) अणु
		kमुक्त(sys);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
