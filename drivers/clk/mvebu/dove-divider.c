<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Marvell Dove PMU Core PLL भागider driver
 *
 * Cleaned up by substantially rewriting, and converted to DT by
 * Russell King.  Origin is not known.
 */
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश "dove-divider.h"

काष्ठा करोve_clk अणु
	स्थिर अक्षर *name;
	काष्ठा clk_hw hw;
	व्योम __iomem *base;
	spinlock_t *lock;
	u8 भाग_bit_start;
	u8 भाग_bit_end;
	u8 भाग_bit_load;
	u8 भाग_bit_size;
	u32 *भागider_table;
पूर्ण;

क्रमागत अणु
	DIV_CTRL0 = 0,
	DIV_CTRL1 = 4,
	DIV_CTRL1_N_RESET_MASK = BIT(10),
पूर्ण;

#घोषणा to_करोve_clk(hw) container_of(hw, काष्ठा करोve_clk, hw)

अटल व्योम करोve_load_भागider(व्योम __iomem *base, u32 val, u32 mask, u32 load)
अणु
	u32 v;

	v = पढ़ोl_relaxed(base + DIV_CTRL1) | DIV_CTRL1_N_RESET_MASK;
	ग_लिखोl_relaxed(v, base + DIV_CTRL1);

	v = (पढ़ोl_relaxed(base + DIV_CTRL0) & ~(mask | load)) | val;
	ग_लिखोl_relaxed(v, base + DIV_CTRL0);
	ग_लिखोl_relaxed(v | load, base + DIV_CTRL0);
	ndelay(250);
	ग_लिखोl_relaxed(v, base + DIV_CTRL0);
पूर्ण

अटल अचिन्हित पूर्णांक करोve_get_भागider(काष्ठा करोve_clk *dc)
अणु
	अचिन्हित पूर्णांक भागider;
	u32 val;

	val = पढ़ोl_relaxed(dc->base + DIV_CTRL0);
	val >>= dc->भाग_bit_start;

	भागider = val & ~(~0 << dc->भाग_bit_size);

	अगर (dc->भागider_table)
		भागider = dc->भागider_table[भागider];

	वापस भागider;
पूर्ण

अटल पूर्णांक करोve_calc_भागider(स्थिर काष्ठा करोve_clk *dc, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate, bool set)
अणु
	अचिन्हित पूर्णांक भागider, max;

	भागider = DIV_ROUND_CLOSEST(parent_rate, rate);

	अगर (dc->भागider_table) अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; dc->भागider_table[i]; i++)
			अगर (भागider == dc->भागider_table[i]) अणु
				भागider = i;
				अवरोध;
			पूर्ण

		अगर (!dc->भागider_table[i])
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		max = 1 << dc->भाग_bit_size;

		अगर (set && (भागider == 0 || भागider >= max))
			वापस -EINVAL;
		अगर (भागider >= max)
			भागider = max - 1;
		अन्यथा अगर (भागider == 0)
			भागider = 1;
	पूर्ण

	वापस भागider;
पूर्ण

अटल अचिन्हित दीर्घ करोve_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent)
अणु
	काष्ठा करोve_clk *dc = to_करोve_clk(hw);
	अचिन्हित पूर्णांक भागider = करोve_get_भागider(dc);
	अचिन्हित दीर्घ rate = DIV_ROUND_CLOSEST(parent, भागider);

	pr_debug("%s(): %s divider=%u parent=%lu rate=%lu\n",
		 __func__, dc->name, भागider, parent, rate);

	वापस rate;
पूर्ण

अटल दीर्घ करोve_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ *parent)
अणु
	काष्ठा करोve_clk *dc = to_करोve_clk(hw);
	अचिन्हित दीर्घ parent_rate = *parent;
	पूर्णांक भागider;

	भागider = करोve_calc_भागider(dc, rate, parent_rate, false);
	अगर (भागider < 0)
		वापस भागider;

	rate = DIV_ROUND_CLOSEST(parent_rate, भागider);

	pr_debug("%s(): %s divider=%u parent=%lu rate=%lu\n",
		 __func__, dc->name, भागider, parent_rate, rate);

	वापस rate;
पूर्ण

अटल पूर्णांक करोve_set_घड़ी(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा करोve_clk *dc = to_करोve_clk(hw);
	u32 mask, load, भाग;
	पूर्णांक भागider;

	भागider = करोve_calc_भागider(dc, rate, parent_rate, true);
	अगर (भागider < 0)
		वापस भागider;

	pr_debug("%s(): %s divider=%u parent=%lu rate=%lu\n",
		 __func__, dc->name, भागider, parent_rate, rate);

	भाग = (u32)भागider << dc->भाग_bit_start;
	mask = ~(~0 << dc->भाग_bit_size) << dc->भाग_bit_start;
	load = BIT(dc->भाग_bit_load);

	spin_lock(dc->lock);
	करोve_load_भागider(dc->base, भाग, mask, load);
	spin_unlock(dc->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops करोve_भागider_ops = अणु
	.set_rate	= करोve_set_घड़ी,
	.round_rate	= करोve_round_rate,
	.recalc_rate	= करोve_recalc_rate,
पूर्ण;

अटल काष्ठा clk *clk_रेजिस्टर_करोve_भागider(काष्ठा device *dev,
	काष्ठा करोve_clk *dc, स्थिर अक्षर **parent_names, माप_प्रकार num_parents,
	व्योम __iomem *base)
अणु
	अक्षर name[32];
	काष्ठा clk_init_data init = अणु
		.name = name,
		.ops = &करोve_भागider_ops,
		.parent_names = parent_names,
		.num_parents = num_parents,
	पूर्ण;

	strlcpy(name, dc->name, माप(name));

	dc->hw.init = &init;
	dc->base = base;
	dc->भाग_bit_size = dc->भाग_bit_end - dc->भाग_bit_start + 1;

	वापस clk_रेजिस्टर(dev, &dc->hw);
पूर्ण

अटल DEFINE_SPINLOCK(करोve_भागider_lock);

अटल u32 axi_भागider[] = अणु-1, 2, 1, 3, 4, 6, 5, 7, 8, 10, 9, 0पूर्ण;

अटल काष्ठा करोve_clk करोve_hw_घड़ीs[4] = अणु
	अणु
		.name = "axi",
		.lock = &करोve_भागider_lock,
		.भाग_bit_start = 1,
		.भाग_bit_end = 6,
		.भाग_bit_load = 7,
		.भागider_table = axi_भागider,
	पूर्ण, अणु
		.name = "gpu",
		.lock = &करोve_भागider_lock,
		.भाग_bit_start = 8,
		.भाग_bit_end = 13,
		.भाग_bit_load = 14,
	पूर्ण, अणु
		.name = "vmeta",
		.lock = &करोve_भागider_lock,
		.भाग_bit_start = 15,
		.भाग_bit_end = 20,
		.भाग_bit_load = 21,
	पूर्ण, अणु
		.name = "lcd",
		.lock = &करोve_भागider_lock,
		.भाग_bit_start = 22,
		.भाग_bit_end = 27,
		.भाग_bit_load = 28,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *core_pll[] = अणु
	"core-pll",
पूर्ण;

अटल पूर्णांक करोve_भागider_init(काष्ठा device *dev, व्योम __iomem *base,
	काष्ठा clk **clks)
अणु
	काष्ठा clk *clk;
	पूर्णांक i;

	/*
	 * Create the core PLL घड़ी.  We treat this as a fixed rate
	 * घड़ी as we करोn't know any better, and करोcumentation is sparse.
	 */
	clk = clk_रेजिस्टर_fixed_rate(dev, core_pll[0], शून्य, 0, 2000000000UL);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	क्रम (i = 0; i < ARRAY_SIZE(करोve_hw_घड़ीs); i++)
		clks[i] = clk_रेजिस्टर_करोve_भागider(dev, &करोve_hw_घड़ीs[i],
						    core_pll,
						    ARRAY_SIZE(core_pll), base);

	वापस 0;
पूर्ण

अटल काष्ठा clk *करोve_भागider_घड़ीs[4];

अटल काष्ठा clk_onecell_data करोve_भागider_data = अणु
	.clks = करोve_भागider_घड़ीs,
	.clk_num = ARRAY_SIZE(करोve_भागider_घड़ीs),
पूर्ण;

व्योम __init करोve_भागider_clk_init(काष्ठा device_node *np)
अणु
	व्योम __iomem *base;

	base = of_iomap(np, 0);
	अगर (WARN_ON(!base))
		वापस;

	अगर (WARN_ON(करोve_भागider_init(शून्य, base, करोve_भागider_घड़ीs))) अणु
		iounmap(base);
		वापस;
	पूर्ण

	of_clk_add_provider(np, of_clk_src_onecell_get, &करोve_भागider_data);
पूर्ण
