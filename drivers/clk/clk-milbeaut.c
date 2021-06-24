<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Socionext Inc.
 * Copyright (C) 2016 Linaro Ltd.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#घोषणा M10V_CLKSEL1		0x0
#घोषणा CLKSEL(n)	(((n) - 1) * 4 + M10V_CLKSEL1)

#घोषणा M10V_PLL1		"pll1"
#घोषणा M10V_PLL1DIV2		"pll1-2"
#घोषणा M10V_PLL2		"pll2"
#घोषणा M10V_PLL2DIV2		"pll2-2"
#घोषणा M10V_PLL6		"pll6"
#घोषणा M10V_PLL6DIV2		"pll6-2"
#घोषणा M10V_PLL6DIV3		"pll6-3"
#घोषणा M10V_PLL7		"pll7"
#घोषणा M10V_PLL7DIV2		"pll7-2"
#घोषणा M10V_PLL7DIV5		"pll7-5"
#घोषणा M10V_PLL9		"pll9"
#घोषणा M10V_PLL10		"pll10"
#घोषणा M10V_PLL10DIV2		"pll10-2"
#घोषणा M10V_PLL11		"pll11"

#घोषणा M10V_SPI_PARENT0	"spi-parent0"
#घोषणा M10V_SPI_PARENT1	"spi-parent1"
#घोषणा M10V_SPI_PARENT2	"spi-parent2"
#घोषणा M10V_UHS1CLK2_PARENT0	"uhs1clk2-parent0"
#घोषणा M10V_UHS1CLK2_PARENT1	"uhs1clk2-parent1"
#घोषणा M10V_UHS1CLK2_PARENT2	"uhs1clk2-parent2"
#घोषणा M10V_UHS1CLK1_PARENT0	"uhs1clk1-parent0"
#घोषणा M10V_UHS1CLK1_PARENT1	"uhs1clk1-parent1"
#घोषणा M10V_NFCLK_PARENT0	"nfclk-parent0"
#घोषणा M10V_NFCLK_PARENT1	"nfclk-parent1"
#घोषणा M10V_NFCLK_PARENT2	"nfclk-parent2"
#घोषणा M10V_NFCLK_PARENT3	"nfclk-parent3"
#घोषणा M10V_NFCLK_PARENT4	"nfclk-parent4"
#घोषणा M10V_NFCLK_PARENT5	"nfclk-parent5"

#घोषणा M10V_DCHREQ		1
#घोषणा M10V_UPOLL_RATE		1
#घोषणा M10V_UTIMEOUT		250

#घोषणा M10V_EMMCCLK_ID		0
#घोषणा M10V_ACLK_ID		1
#घोषणा M10V_HCLK_ID		2
#घोषणा M10V_PCLK_ID		3
#घोषणा M10V_RCLK_ID		4
#घोषणा M10V_SPICLK_ID		5
#घोषणा M10V_NFCLK_ID		6
#घोषणा M10V_UHS1CLK2_ID	7
#घोषणा M10V_NUM_CLKS		8

#घोषणा to_m10v_भाग(_hw)        container_of(_hw, काष्ठा m10v_clk_भागider, hw)

अटल काष्ठा clk_hw_onecell_data *m10v_clk_data;

अटल DEFINE_SPINLOCK(m10v_crglock);

काष्ठा m10v_clk_भाग_factors अणु
	स्थिर अक्षर			*name;
	स्थिर अक्षर			*parent_name;
	u32				offset;
	u8				shअगरt;
	u8				width;
	स्थिर काष्ठा clk_भाग_प्रकारable	*table;
	अचिन्हित दीर्घ			भाग_flags;
	पूर्णांक				onecell_idx;
पूर्ण;

काष्ठा m10v_clk_भाग_fixed_data अणु
	स्थिर अक्षर	*name;
	स्थिर अक्षर	*parent_name;
	u8		भाग;
	u8		mult;
	पूर्णांक		onecell_idx;
पूर्ण;

काष्ठा m10v_clk_mux_factors अणु
	स्थिर अक्षर		*name;
	स्थिर अक्षर * स्थिर	*parent_names;
	u8			num_parents;
	u32			offset;
	u8			shअगरt;
	u8			mask;
	u32			*table;
	अचिन्हित दीर्घ		mux_flags;
	पूर्णांक			onecell_idx;
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable emmcclk_table[] = अणु
	अणु .val = 0, .भाग = 8 पूर्ण,
	अणु .val = 1, .भाग = 9 पूर्ण,
	अणु .val = 2, .भाग = 10 पूर्ण,
	अणु .val = 3, .भाग = 15 पूर्ण,
	अणु .भाग = 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable mclk400_table[] = अणु
	अणु .val = 1, .भाग = 2 पूर्ण,
	अणु .val = 3, .भाग = 4 पूर्ण,
	अणु .भाग = 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable mclk200_table[] = अणु
	अणु .val = 3, .भाग = 4 पूर्ण,
	अणु .val = 7, .भाग = 8 पूर्ण,
	अणु .भाग = 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable aclk400_table[] = अणु
	अणु .val = 1, .भाग = 2 पूर्ण,
	अणु .val = 3, .भाग = 4 पूर्ण,
	अणु .भाग = 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable aclk300_table[] = अणु
	अणु .val = 0, .भाग = 2 पूर्ण,
	अणु .val = 1, .भाग = 3 पूर्ण,
	अणु .भाग = 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable aclk_table[] = अणु
	अणु .val = 3, .भाग = 4 पूर्ण,
	अणु .val = 7, .भाग = 8 पूर्ण,
	अणु .भाग = 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable aclkexs_table[] = अणु
	अणु .val = 3, .भाग = 4 पूर्ण,
	अणु .val = 4, .भाग = 5 पूर्ण,
	अणु .val = 5, .भाग = 6 पूर्ण,
	अणु .val = 7, .भाग = 8 पूर्ण,
	अणु .भाग = 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable hclk_table[] = अणु
	अणु .val = 7, .भाग = 8 पूर्ण,
	अणु .val = 15, .भाग = 16 पूर्ण,
	अणु .भाग = 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable hclkbmh_table[] = अणु
	अणु .val = 3, .भाग = 4 पूर्ण,
	अणु .val = 7, .भाग = 8 पूर्ण,
	अणु .भाग = 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable pclk_table[] = अणु
	अणु .val = 15, .भाग = 16 पूर्ण,
	अणु .val = 31, .भाग = 32 पूर्ण,
	अणु .भाग = 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable rclk_table[] = अणु
	अणु .val = 0, .भाग = 8 पूर्ण,
	अणु .val = 1, .भाग = 16 पूर्ण,
	अणु .val = 2, .भाग = 24 पूर्ण,
	अणु .val = 3, .भाग = 32 पूर्ण,
	अणु .भाग = 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable uhs1clk0_table[] = अणु
	अणु .val = 0, .भाग = 2 पूर्ण,
	अणु .val = 1, .भाग = 3 पूर्ण,
	अणु .val = 2, .भाग = 4 पूर्ण,
	अणु .val = 3, .भाग = 8 पूर्ण,
	अणु .val = 4, .भाग = 16 पूर्ण,
	अणु .भाग = 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable uhs2clk_table[] = अणु
	अणु .val = 0, .भाग = 9 पूर्ण,
	अणु .val = 1, .भाग = 10 पूर्ण,
	अणु .val = 2, .भाग = 11 पूर्ण,
	अणु .val = 3, .भाग = 12 पूर्ण,
	अणु .val = 4, .भाग = 13 पूर्ण,
	अणु .val = 5, .भाग = 14 पूर्ण,
	अणु .val = 6, .भाग = 16 पूर्ण,
	अणु .val = 7, .भाग = 18 पूर्ण,
	अणु .भाग = 0 पूर्ण,
पूर्ण;

अटल u32 spi_mux_table[] = अणु0, 1, 2पूर्ण;
अटल स्थिर अक्षर * स्थिर spi_mux_names[] = अणु
	M10V_SPI_PARENT0, M10V_SPI_PARENT1, M10V_SPI_PARENT2
पूर्ण;

अटल u32 uhs1clk2_mux_table[] = अणु2, 3, 4, 8पूर्ण;
अटल स्थिर अक्षर * स्थिर uhs1clk2_mux_names[] = अणु
	M10V_UHS1CLK2_PARENT0, M10V_UHS1CLK2_PARENT1,
	M10V_UHS1CLK2_PARENT2, M10V_PLL6DIV2
पूर्ण;

अटल u32 uhs1clk1_mux_table[] = अणु3, 4, 8पूर्ण;
अटल स्थिर अक्षर * स्थिर uhs1clk1_mux_names[] = अणु
	M10V_UHS1CLK1_PARENT0, M10V_UHS1CLK1_PARENT1, M10V_PLL6DIV2
पूर्ण;

अटल u32 nfclk_mux_table[] = अणु0, 1, 2, 3, 4, 8पूर्ण;
अटल स्थिर अक्षर * स्थिर nfclk_mux_names[] = अणु
	M10V_NFCLK_PARENT0, M10V_NFCLK_PARENT1, M10V_NFCLK_PARENT2,
	M10V_NFCLK_PARENT3, M10V_NFCLK_PARENT4, M10V_NFCLK_PARENT5
पूर्ण;

अटल स्थिर काष्ठा m10v_clk_भाग_fixed_data m10v_pll_fixed_data[] = अणु
	अणुM10V_PLL1, शून्य, 1, 40, -1पूर्ण,
	अणुM10V_PLL2, शून्य, 1, 30, -1पूर्ण,
	अणुM10V_PLL6, शून्य, 1, 35, -1पूर्ण,
	अणुM10V_PLL7, शून्य, 1, 40, -1पूर्ण,
	अणुM10V_PLL9, शून्य, 1, 33, -1पूर्ण,
	अणुM10V_PLL10, शून्य, 5, 108, -1पूर्ण,
	अणुM10V_PLL10DIV2, M10V_PLL10, 2, 1, -1पूर्ण,
	अणुM10V_PLL11, शून्य, 2, 75, -1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा m10v_clk_भाग_fixed_data m10v_भाग_fixed_data[] = अणु
	अणु"usb2", शून्य, 2, 1, -1पूर्ण,
	अणु"pcisuppclk", शून्य, 20, 1, -1पूर्ण,
	अणुM10V_PLL1DIV2, M10V_PLL1, 2, 1, -1पूर्ण,
	अणुM10V_PLL2DIV2, M10V_PLL2, 2, 1, -1पूर्ण,
	अणुM10V_PLL6DIV2, M10V_PLL6, 2, 1, -1पूर्ण,
	अणुM10V_PLL6DIV3, M10V_PLL6, 3, 1, -1पूर्ण,
	अणुM10V_PLL7DIV2, M10V_PLL7, 2, 1, -1पूर्ण,
	अणुM10V_PLL7DIV5, M10V_PLL7, 5, 1, -1पूर्ण,
	अणु"ca7wd", M10V_PLL2DIV2, 12, 1, -1पूर्ण,
	अणु"pclkca7wd", M10V_PLL1DIV2, 16, 1, -1पूर्ण,
	अणुM10V_SPI_PARENT0, M10V_PLL10DIV2, 2, 1, -1पूर्ण,
	अणुM10V_SPI_PARENT1, M10V_PLL10DIV2, 4, 1, -1पूर्ण,
	अणुM10V_SPI_PARENT2, M10V_PLL7DIV2, 8, 1, -1पूर्ण,
	अणुM10V_UHS1CLK2_PARENT0, M10V_PLL7, 4, 1, -1पूर्ण,
	अणुM10V_UHS1CLK2_PARENT1, M10V_PLL7, 8, 1, -1पूर्ण,
	अणुM10V_UHS1CLK2_PARENT2, M10V_PLL7, 16, 1, -1पूर्ण,
	अणुM10V_UHS1CLK1_PARENT0, M10V_PLL7, 8, 1, -1पूर्ण,
	अणुM10V_UHS1CLK1_PARENT1, M10V_PLL7, 16, 1, -1पूर्ण,
	अणुM10V_NFCLK_PARENT0, M10V_PLL7DIV2, 8, 1, -1पूर्ण,
	अणुM10V_NFCLK_PARENT1, M10V_PLL7DIV2, 10, 1, -1पूर्ण,
	अणुM10V_NFCLK_PARENT2, M10V_PLL7DIV2, 13, 1, -1पूर्ण,
	अणुM10V_NFCLK_PARENT3, M10V_PLL7DIV2, 16, 1, -1पूर्ण,
	अणुM10V_NFCLK_PARENT4, M10V_PLL7DIV2, 40, 1, -1पूर्ण,
	अणुM10V_NFCLK_PARENT5, M10V_PLL7DIV5, 10, 1, -1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा m10v_clk_भाग_factors m10v_भाग_factor_data[] = अणु
	अणु"emmc", M10V_PLL11, CLKSEL(1), 28, 3, emmcclk_table, 0,
		M10V_EMMCCLK_IDपूर्ण,
	अणु"mclk400", M10V_PLL1DIV2, CLKSEL(10), 7, 3, mclk400_table, 0, -1पूर्ण,
	अणु"mclk200", M10V_PLL1DIV2, CLKSEL(10), 3, 4, mclk200_table, 0, -1पूर्ण,
	अणु"aclk400", M10V_PLL1DIV2, CLKSEL(10), 0, 3, aclk400_table, 0, -1पूर्ण,
	अणु"aclk300", M10V_PLL2DIV2, CLKSEL(12), 0, 2, aclk300_table, 0, -1पूर्ण,
	अणु"aclk", M10V_PLL1DIV2, CLKSEL(9), 20, 4, aclk_table, 0, M10V_ACLK_IDपूर्ण,
	अणु"aclkexs", M10V_PLL1DIV2, CLKSEL(9), 16, 4, aclkexs_table, 0, -1पूर्ण,
	अणु"hclk", M10V_PLL1DIV2, CLKSEL(9), 7, 5, hclk_table, 0, M10V_HCLK_IDपूर्ण,
	अणु"hclkbmh", M10V_PLL1DIV2, CLKSEL(9), 12, 4, hclkbmh_table, 0, -1पूर्ण,
	अणु"pclk", M10V_PLL1DIV2, CLKSEL(9), 0, 7, pclk_table, 0, M10V_PCLK_IDपूर्ण,
	अणु"uhs1clk0", M10V_PLL7, CLKSEL(1), 3, 5, uhs1clk0_table, 0, -1पूर्ण,
	अणु"uhs2clk", M10V_PLL6DIV3, CLKSEL(1), 18, 4, uhs2clk_table, 0, -1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा m10v_clk_mux_factors m10v_mux_factor_data[] = अणु
	अणु"spi", spi_mux_names, ARRAY_SIZE(spi_mux_names),
		CLKSEL(8), 3, 7, spi_mux_table, 0, M10V_SPICLK_IDपूर्ण,
	अणु"uhs1clk2", uhs1clk2_mux_names, ARRAY_SIZE(uhs1clk2_mux_names),
		CLKSEL(1), 13, 31, uhs1clk2_mux_table, 0, M10V_UHS1CLK2_IDपूर्ण,
	अणु"uhs1clk1", uhs1clk1_mux_names, ARRAY_SIZE(uhs1clk1_mux_names),
		CLKSEL(1), 8, 31, uhs1clk1_mux_table, 0, -1पूर्ण,
	अणु"nfclk", nfclk_mux_names, ARRAY_SIZE(nfclk_mux_names),
		CLKSEL(1), 22, 127, nfclk_mux_table, 0, M10V_NFCLK_IDपूर्ण,
पूर्ण;

अटल u8 m10v_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_mux *mux = to_clk_mux(hw);
	u32 val;

	val = पढ़ोl(mux->reg) >> mux->shअगरt;
	val &= mux->mask;

	वापस clk_mux_val_to_index(hw, mux->table, mux->flags, val);
पूर्ण

अटल पूर्णांक m10v_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_mux *mux = to_clk_mux(hw);
	u32 val = clk_mux_index_to_val(mux->table, mux->flags, index);
	अचिन्हित दीर्घ flags = 0;
	u32 reg;
	u32 ग_लिखो_en = BIT(fls(mux->mask) - 1);

	अगर (mux->lock)
		spin_lock_irqsave(mux->lock, flags);
	अन्यथा
		__acquire(mux->lock);

	reg = पढ़ोl(mux->reg);
	reg &= ~(mux->mask << mux->shअगरt);

	val = (val | ग_लिखो_en) << mux->shअगरt;
	reg |= val;
	ग_लिखोl(reg, mux->reg);

	अगर (mux->lock)
		spin_unlock_irqrestore(mux->lock, flags);
	अन्यथा
		__release(mux->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops m10v_mux_ops = अणु
	.get_parent = m10v_mux_get_parent,
	.set_parent = m10v_mux_set_parent,
	.determine_rate = __clk_mux_determine_rate,
पूर्ण;

अटल काष्ठा clk_hw *m10v_clk_hw_रेजिस्टर_mux(काष्ठा device *dev,
			स्थिर अक्षर *name, स्थिर अक्षर * स्थिर *parent_names,
			u8 num_parents, अचिन्हित दीर्घ flags, व्योम __iomem *reg,
			u8 shअगरt, u32 mask, u8 clk_mux_flags, u32 *table,
			spinlock_t *lock)
अणु
	काष्ठा clk_mux *mux;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	mux = kzalloc(माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &m10v_mux_ops;
	init.flags = flags;
	init.parent_names = parent_names;
	init.num_parents = num_parents;

	mux->reg = reg;
	mux->shअगरt = shअगरt;
	mux->mask = mask;
	mux->flags = clk_mux_flags;
	mux->lock = lock;
	mux->table = table;
	mux->hw.init = &init;

	hw = &mux->hw;
	ret = clk_hw_रेजिस्टर(dev, hw);
	अगर (ret) अणु
		kमुक्त(mux);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;

पूर्ण

काष्ठा m10v_clk_भागider अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*reg;
	u8		shअगरt;
	u8		width;
	u8		flags;
	स्थिर काष्ठा clk_भाग_प्रकारable	*table;
	spinlock_t	*lock;
	व्योम __iomem	*ग_लिखो_valid_reg;
पूर्ण;

अटल अचिन्हित दीर्घ m10v_clk_भागider_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा m10v_clk_भागider *भागider = to_m10v_भाग(hw);
	अचिन्हित पूर्णांक val;

	val = पढ़ोl(भागider->reg) >> भागider->shअगरt;
	val &= clk_भाग_mask(भागider->width);

	वापस भागider_recalc_rate(hw, parent_rate, val, भागider->table,
				   भागider->flags, भागider->width);
पूर्ण

अटल दीर्घ m10v_clk_भागider_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *prate)
अणु
	काष्ठा m10v_clk_भागider *भागider = to_m10v_भाग(hw);

	/* अगर पढ़ो only, just वापस current value */
	अगर (भागider->flags & CLK_DIVIDER_READ_ONLY) अणु
		u32 val;

		val = पढ़ोl(भागider->reg) >> भागider->shअगरt;
		val &= clk_भाग_mask(भागider->width);

		वापस भागider_ro_round_rate(hw, rate, prate, भागider->table,
					     भागider->width, भागider->flags,
					     val);
	पूर्ण

	वापस भागider_round_rate(hw, rate, prate, भागider->table,
				  भागider->width, भागider->flags);
पूर्ण

अटल पूर्णांक m10v_clk_भागider_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा m10v_clk_भागider *भागider = to_m10v_भाग(hw);
	पूर्णांक value;
	अचिन्हित दीर्घ flags = 0;
	u32 val;
	u32 ग_लिखो_en = BIT(भागider->width - 1);

	value = भागider_get_val(rate, parent_rate, भागider->table,
				भागider->width, भागider->flags);
	अगर (value < 0)
		वापस value;

	अगर (भागider->lock)
		spin_lock_irqsave(भागider->lock, flags);
	अन्यथा
		__acquire(भागider->lock);

	val = पढ़ोl(भागider->reg);
	val &= ~(clk_भाग_mask(भागider->width) << भागider->shअगरt);

	val |= ((u32)value | ग_लिखो_en) << भागider->shअगरt;
	ग_लिखोl(val, भागider->reg);

	अगर (भागider->ग_लिखो_valid_reg) अणु
		ग_लिखोl(M10V_DCHREQ, भागider->ग_लिखो_valid_reg);
		अगर (पढ़ोl_poll_समयout(भागider->ग_लिखो_valid_reg, val,
			!val, M10V_UPOLL_RATE, M10V_UTIMEOUT))
			pr_err("%s:%s couldn't stabilize\n",
				__func__, clk_hw_get_name(hw));
	पूर्ण

	अगर (भागider->lock)
		spin_unlock_irqrestore(भागider->lock, flags);
	अन्यथा
		__release(भागider->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops m10v_clk_भागider_ops = अणु
	.recalc_rate = m10v_clk_भागider_recalc_rate,
	.round_rate = m10v_clk_भागider_round_rate,
	.set_rate = m10v_clk_भागider_set_rate,
पूर्ण;

अटल काष्ठा clk_hw *m10v_clk_hw_रेजिस्टर_भागider(काष्ठा device *dev,
		स्थिर अक्षर *name, स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		व्योम __iomem *reg, u8 shअगरt, u8 width,
		u8 clk_भागider_flags, स्थिर काष्ठा clk_भाग_प्रकारable *table,
		spinlock_t *lock, व्योम __iomem *ग_लिखो_valid_reg)
अणु
	काष्ठा m10v_clk_भागider *भाग;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	भाग = kzalloc(माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &m10v_clk_भागider_ops;
	init.flags = flags;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	भाग->reg = reg;
	भाग->shअगरt = shअगरt;
	भाग->width = width;
	भाग->flags = clk_भागider_flags;
	भाग->lock = lock;
	भाग->hw.init = &init;
	भाग->table = table;
	भाग->ग_लिखो_valid_reg = ग_लिखो_valid_reg;

	/* रेजिस्टर the घड़ी */
	hw = &भाग->hw;
	ret = clk_hw_रेजिस्टर(dev, hw);
	अगर (ret) अणु
		kमुक्त(भाग);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

अटल व्योम m10v_reg_भाग_pre(स्थिर काष्ठा m10v_clk_भाग_factors *factors,
			     काष्ठा clk_hw_onecell_data *clk_data,
			     व्योम __iomem *base)
अणु
	काष्ठा clk_hw *hw;
	व्योम __iomem *ग_लिखो_valid_reg;

	/*
	 * The रेजिस्टरs on CLKSEL(9) or CLKSEL(10) need additional
	 * writing to become valid.
	 */
	अगर ((factors->offset == CLKSEL(9)) || (factors->offset == CLKSEL(10)))
		ग_लिखो_valid_reg = base + CLKSEL(11);
	अन्यथा
		ग_लिखो_valid_reg = शून्य;

	hw = m10v_clk_hw_रेजिस्टर_भागider(शून्य, factors->name,
					  factors->parent_name,
					  CLK_SET_RATE_PARENT,
					  base + factors->offset,
					  factors->shअगरt,
					  factors->width, factors->भाग_flags,
					  factors->table,
					  &m10v_crglock, ग_लिखो_valid_reg);

	अगर (factors->onecell_idx >= 0)
		clk_data->hws[factors->onecell_idx] = hw;
पूर्ण

अटल व्योम m10v_reg_fixed_pre(स्थिर काष्ठा m10v_clk_भाग_fixed_data *factors,
			       काष्ठा clk_hw_onecell_data *clk_data,
			       स्थिर अक्षर *parent_name)
अणु
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *pn = factors->parent_name ?
				factors->parent_name : parent_name;

	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, factors->name, pn, 0,
					  factors->mult, factors->भाग);

	अगर (factors->onecell_idx >= 0)
		clk_data->hws[factors->onecell_idx] = hw;
पूर्ण

अटल व्योम m10v_reg_mux_pre(स्थिर काष्ठा m10v_clk_mux_factors *factors,
			       काष्ठा clk_hw_onecell_data *clk_data,
			       व्योम __iomem *base)
अणु
	काष्ठा clk_hw *hw;

	hw = m10v_clk_hw_रेजिस्टर_mux(शून्य, factors->name,
				      factors->parent_names,
				      factors->num_parents,
				      CLK_SET_RATE_PARENT,
				      base + factors->offset, factors->shअगरt,
				      factors->mask, factors->mux_flags,
				      factors->table, &m10v_crglock);

	अगर (factors->onecell_idx >= 0)
		clk_data->hws[factors->onecell_idx] = hw;
पूर्ण

अटल पूर्णांक m10v_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक id;
	काष्ठा resource *res;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	व्योम __iomem *base;
	स्थिर अक्षर *parent_name;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	parent_name = of_clk_get_parent_name(np, 0);

	क्रम (id = 0; id < ARRAY_SIZE(m10v_भाग_factor_data); ++id)
		m10v_reg_भाग_pre(&m10v_भाग_factor_data[id],
				 m10v_clk_data, base);

	क्रम (id = 0; id < ARRAY_SIZE(m10v_भाग_fixed_data); ++id)
		m10v_reg_fixed_pre(&m10v_भाग_fixed_data[id],
				   m10v_clk_data, parent_name);

	क्रम (id = 0; id < ARRAY_SIZE(m10v_mux_factor_data); ++id)
		m10v_reg_mux_pre(&m10v_mux_factor_data[id],
				 m10v_clk_data, base);

	क्रम (id = 0; id < M10V_NUM_CLKS; id++) अणु
		अगर (IS_ERR(m10v_clk_data->hws[id]))
			वापस PTR_ERR(m10v_clk_data->hws[id]);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id m10v_clk_dt_ids[] = अणु
	अणु .compatible = "socionext,milbeaut-m10v-ccu", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver m10v_clk_driver = अणु
	.probe  = m10v_clk_probe,
	.driver = अणु
		.name = "m10v-ccu",
		.of_match_table = m10v_clk_dt_ids,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(m10v_clk_driver);

अटल व्योम __init m10v_cc_init(काष्ठा device_node *np)
अणु
	पूर्णांक id;
	व्योम __iomem *base;
	स्थिर अक्षर *parent_name;
	काष्ठा clk_hw *hw;

	m10v_clk_data = kzalloc(काष्ठा_size(m10v_clk_data, hws,
					M10V_NUM_CLKS),
					GFP_KERNEL);

	अगर (!m10v_clk_data)
		वापस;

	base = of_iomap(np, 0);
	अगर (!base) अणु
		kमुक्त(m10v_clk_data);
		वापस;
	पूर्ण

	parent_name = of_clk_get_parent_name(np, 0);
	अगर (!parent_name) अणु
		kमुक्त(m10v_clk_data);
		iounmap(base);
		वापस;
	पूर्ण

	/*
	 * This way all घड़ीs fetched beक्रमe the platक्रमm device probes,
	 * except those we assign here क्रम early use, will be deferred.
	 */
	क्रम (id = 0; id < M10V_NUM_CLKS; id++)
		m10v_clk_data->hws[id] = ERR_PTR(-EPROBE_DEFER);

	/*
	 * PLLs are set by bootloader so this driver रेजिस्टरs them as the
	 * fixed factor.
	 */
	क्रम (id = 0; id < ARRAY_SIZE(m10v_pll_fixed_data); ++id)
		m10v_reg_fixed_pre(&m10v_pll_fixed_data[id],
				   m10v_clk_data, parent_name);

	/*
	 * समयr consumes "rclk" so it needs to रेजिस्टर here.
	 */
	hw = m10v_clk_hw_रेजिस्टर_भागider(शून्य, "rclk", M10V_PLL10DIV2, 0,
					base + CLKSEL(1), 0, 3, 0, rclk_table,
					&m10v_crglock, शून्य);
	m10v_clk_data->hws[M10V_RCLK_ID] = hw;

	m10v_clk_data->num = M10V_NUM_CLKS;
	of_clk_add_hw_provider(np, of_clk_hw_onecell_get, m10v_clk_data);
पूर्ण
CLK_OF_DECLARE_DRIVER(m10v_cc, "socionext,milbeaut-m10v-ccu", m10v_cc_init);
