<शैली गुरु>
// SPDX-License-Identअगरier:	GPL-2.0
/*
 * Copyright (C) 2017, Intel Corporation
 */
#समावेश <linux/slab.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>

#समावेश "stratix10-clk.h"
#समावेश "clk.h"

#घोषणा CLK_MGR_FREE_SHIFT		16
#घोषणा CLK_MGR_FREE_MASK		0x7
#घोषणा SWCTRLBTCLKSEN_SHIFT		8

#घोषणा to_periph_clk(p) container_of(p, काष्ठा socfpga_periph_clk, hw.hw)

अटल अचिन्हित दीर्घ n5x_clk_peri_c_clk_recalc_rate(काष्ठा clk_hw *hwclk,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा socfpga_periph_clk *socfpgaclk = to_periph_clk(hwclk);
	अचिन्हित दीर्घ भाग;
	अचिन्हित दीर्घ shअगरt = socfpgaclk->shअगरt;
	u32 val;

	val = पढ़ोl(socfpgaclk->hw.reg);
	val &= (0x1f << shअगरt);
	भाग = (val >> shअगरt) + 1;

	वापस parent_rate / भाग;
पूर्ण

अटल अचिन्हित दीर्घ clk_peri_c_clk_recalc_rate(काष्ठा clk_hw *hwclk,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा socfpga_periph_clk *socfpgaclk = to_periph_clk(hwclk);
	अचिन्हित दीर्घ भाग = 1;
	u32 val;

	val = पढ़ोl(socfpgaclk->hw.reg);
	val &= GENMASK(SWCTRLBTCLKSEN_SHIFT - 1, 0);
	parent_rate /= val;

	वापस parent_rate / भाग;
पूर्ण

अटल अचिन्हित दीर्घ clk_peri_cnt_clk_recalc_rate(काष्ठा clk_hw *hwclk,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा socfpga_periph_clk *socfpgaclk = to_periph_clk(hwclk);
	अचिन्हित दीर्घ भाग = 1;

	अगर (socfpgaclk->fixed_भाग) अणु
		भाग = socfpgaclk->fixed_भाग;
	पूर्ण अन्यथा अणु
		अगर (socfpgaclk->hw.reg)
			भाग = ((पढ़ोl(socfpgaclk->hw.reg) & 0x7ff) + 1);
	पूर्ण

	वापस parent_rate / भाग;
पूर्ण

अटल u8 clk_periclk_get_parent(काष्ठा clk_hw *hwclk)
अणु
	काष्ठा socfpga_periph_clk *socfpgaclk = to_periph_clk(hwclk);
	u32 clk_src, mask;
	u8 parent;

	अगर (socfpgaclk->bypass_reg) अणु
		mask = (0x1 << socfpgaclk->bypass_shअगरt);
		parent = ((पढ़ोl(socfpgaclk->bypass_reg) & mask) >>
			   socfpgaclk->bypass_shअगरt);
	पूर्ण अन्यथा अणु
		clk_src = पढ़ोl(socfpgaclk->hw.reg);
		parent = (clk_src >> CLK_MGR_FREE_SHIFT) &
			CLK_MGR_FREE_MASK;
	पूर्ण
	वापस parent;
पूर्ण

अटल स्थिर काष्ठा clk_ops n5x_peri_c_clk_ops = अणु
	.recalc_rate = n5x_clk_peri_c_clk_recalc_rate,
	.get_parent = clk_periclk_get_parent,
पूर्ण;

अटल स्थिर काष्ठा clk_ops peri_c_clk_ops = अणु
	.recalc_rate = clk_peri_c_clk_recalc_rate,
	.get_parent = clk_periclk_get_parent,
पूर्ण;

अटल स्थिर काष्ठा clk_ops peri_cnt_clk_ops = अणु
	.recalc_rate = clk_peri_cnt_clk_recalc_rate,
	.get_parent = clk_periclk_get_parent,
पूर्ण;

काष्ठा clk_hw *s10_रेजिस्टर_periph(स्थिर काष्ठा stratix10_perip_c_घड़ी *clks,
				व्योम __iomem *reg)
अणु
	काष्ठा clk_hw *hw_clk;
	काष्ठा socfpga_periph_clk *periph_clk;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *name = clks->name;
	स्थिर अक्षर *parent_name = clks->parent_name;
	पूर्णांक ret;

	periph_clk = kzalloc(माप(*periph_clk), GFP_KERNEL);
	अगर (WARN_ON(!periph_clk))
		वापस शून्य;

	periph_clk->hw.reg = reg + clks->offset;

	init.name = name;
	init.ops = &peri_c_clk_ops;
	init.flags = clks->flags;

	init.num_parents = clks->num_parents;
	init.parent_names = parent_name ? &parent_name : शून्य;
	अगर (init.parent_names == शून्य)
		init.parent_data = clks->parent_data;

	periph_clk->hw.hw.init = &init;
	hw_clk = &periph_clk->hw.hw;

	ret = clk_hw_रेजिस्टर(शून्य, hw_clk);
	अगर (ret) अणु
		kमुक्त(periph_clk);
		वापस ERR_PTR(ret);
	पूर्ण
	वापस hw_clk;
पूर्ण

काष्ठा clk_hw *n5x_रेजिस्टर_periph(स्थिर काष्ठा n5x_perip_c_घड़ी *clks,
				व्योम __iomem *regbase)
अणु
	काष्ठा clk_hw *hw_clk;
	काष्ठा socfpga_periph_clk *periph_clk;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *name = clks->name;
	स्थिर अक्षर *parent_name = clks->parent_name;
	पूर्णांक ret;

	periph_clk = kzalloc(माप(*periph_clk), GFP_KERNEL);
	अगर (WARN_ON(!periph_clk))
		वापस शून्य;

	periph_clk->hw.reg = regbase + clks->offset;
	periph_clk->shअगरt = clks->shअगरt;

	init.name = name;
	init.ops = &n5x_peri_c_clk_ops;
	init.flags = clks->flags;

	init.num_parents = clks->num_parents;
	init.parent_names = parent_name ? &parent_name : शून्य;

	periph_clk->hw.hw.init = &init;
	hw_clk = &periph_clk->hw.hw;

	ret = clk_hw_रेजिस्टर(शून्य, hw_clk);
	अगर (ret) अणु
		kमुक्त(periph_clk);
		वापस ERR_PTR(ret);
	पूर्ण
	वापस hw_clk;
पूर्ण

काष्ठा clk_hw *s10_रेजिस्टर_cnt_periph(स्थिर काष्ठा stratix10_perip_cnt_घड़ी *clks,
				    व्योम __iomem *regbase)
अणु
	काष्ठा clk_hw *hw_clk;
	काष्ठा socfpga_periph_clk *periph_clk;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *name = clks->name;
	स्थिर अक्षर *parent_name = clks->parent_name;
	पूर्णांक ret;

	periph_clk = kzalloc(माप(*periph_clk), GFP_KERNEL);
	अगर (WARN_ON(!periph_clk))
		वापस शून्य;

	अगर (clks->offset)
		periph_clk->hw.reg = regbase + clks->offset;
	अन्यथा
		periph_clk->hw.reg = शून्य;

	अगर (clks->bypass_reg)
		periph_clk->bypass_reg = regbase + clks->bypass_reg;
	अन्यथा
		periph_clk->bypass_reg = शून्य;
	periph_clk->bypass_shअगरt = clks->bypass_shअगरt;
	periph_clk->fixed_भाग = clks->fixed_भागider;

	init.name = name;
	init.ops = &peri_cnt_clk_ops;
	init.flags = clks->flags;

	init.num_parents = clks->num_parents;
	init.parent_names = parent_name ? &parent_name : शून्य;
	अगर (init.parent_names == शून्य)
		init.parent_data = clks->parent_data;

	periph_clk->hw.hw.init = &init;
	hw_clk = &periph_clk->hw.hw;

	ret = clk_hw_रेजिस्टर(शून्य, hw_clk);
	अगर (ret) अणु
		kमुक्त(periph_clk);
		वापस ERR_PTR(ret);
	पूर्ण
	वापस hw_clk;
पूर्ण
