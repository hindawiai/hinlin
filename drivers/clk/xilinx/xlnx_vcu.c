<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xilinx VCU Init
 *
 * Copyright (C) 2016 - 2017 Xilinx, Inc.
 *
 * Contacts   Dhaval Shah <dshah@xilinx.com>
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/xlnx-vcu.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/xlnx-vcu.h>

#घोषणा VCU_PLL_CTRL			0x24
#घोषणा VCU_PLL_CTRL_RESET		BIT(0)
#घोषणा VCU_PLL_CTRL_POR_IN		BIT(1)
#घोषणा VCU_PLL_CTRL_PWR_POR		BIT(2)
#घोषणा VCU_PLL_CTRL_BYPASS		BIT(3)
#घोषणा VCU_PLL_CTRL_FBDIV		GENMASK(14, 8)
#घोषणा VCU_PLL_CTRL_CLKOUTDIV		GENMASK(18, 16)

#घोषणा VCU_PLL_CFG			0x28
#घोषणा VCU_PLL_CFG_RES			GENMASK(3, 0)
#घोषणा VCU_PLL_CFG_CP			GENMASK(8, 5)
#घोषणा VCU_PLL_CFG_LFHF		GENMASK(12, 10)
#घोषणा VCU_PLL_CFG_LOCK_CNT		GENMASK(22, 13)
#घोषणा VCU_PLL_CFG_LOCK_DLY		GENMASK(31, 25)
#घोषणा VCU_ENC_CORE_CTRL		0x30
#घोषणा VCU_ENC_MCU_CTRL		0x34
#घोषणा VCU_DEC_CORE_CTRL		0x38
#घोषणा VCU_DEC_MCU_CTRL		0x3c
#घोषणा VCU_PLL_STATUS			0x60
#घोषणा VCU_PLL_STATUS_LOCK_STATUS	BIT(0)

#घोषणा MHZ				1000000
#घोषणा FVCO_MIN			(1500U * MHZ)
#घोषणा FVCO_MAX			(3000U * MHZ)

/**
 * काष्ठा xvcu_device - Xilinx VCU init device काष्ठाure
 * @dev: Platक्रमm device
 * @pll_ref: pll ref घड़ी source
 * @aclk: axi घड़ी source
 * @logicore_reg_ba: logicore reg base address
 * @vcu_slcr_ba: vcu_slcr Register base address
 * @pll: handle क्रम the VCU PLL
 * @pll_post: handle क्रम the VCU PLL post भागider
 * @clk_data: घड़ीs provided by the vcu घड़ी provider
 */
काष्ठा xvcu_device अणु
	काष्ठा device *dev;
	काष्ठा clk *pll_ref;
	काष्ठा clk *aclk;
	काष्ठा regmap *logicore_reg_ba;
	व्योम __iomem *vcu_slcr_ba;
	काष्ठा clk_hw *pll;
	काष्ठा clk_hw *pll_post;
	काष्ठा clk_hw_onecell_data *clk_data;
पूर्ण;

अटल काष्ठा regmap_config vcu_settings_regmap_config = अणु
	.name = "regmap",
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = 0xfff,
	.cache_type = REGCACHE_NONE,
पूर्ण;

/**
 * काष्ठा xvcu_pll_cfg - Helper data
 * @fbभाग: The पूर्णांकeger portion of the feedback भागider to the PLL
 * @cp: PLL अक्षरge pump control
 * @res: PLL loop filter resistor control
 * @lfhf: PLL loop filter high frequency capacitor control
 * @lock_dly: Lock circuit configuration settings क्रम lock winकरोwsize
 * @lock_cnt: Lock circuit counter setting
 */
काष्ठा xvcu_pll_cfg अणु
	u32 fbभाग;
	u32 cp;
	u32 res;
	u32 lfhf;
	u32 lock_dly;
	u32 lock_cnt;
पूर्ण;

अटल स्थिर काष्ठा xvcu_pll_cfg xvcu_pll_cfg[] = अणु
	अणु 25, 3, 10, 3, 63, 1000 पूर्ण,
	अणु 26, 3, 10, 3, 63, 1000 पूर्ण,
	अणु 27, 4, 6, 3, 63, 1000 पूर्ण,
	अणु 28, 4, 6, 3, 63, 1000 पूर्ण,
	अणु 29, 4, 6, 3, 63, 1000 पूर्ण,
	अणु 30, 4, 6, 3, 63, 1000 पूर्ण,
	अणु 31, 6, 1, 3, 63, 1000 पूर्ण,
	अणु 32, 6, 1, 3, 63, 1000 पूर्ण,
	अणु 33, 4, 10, 3, 63, 1000 पूर्ण,
	अणु 34, 5, 6, 3, 63, 1000 पूर्ण,
	अणु 35, 5, 6, 3, 63, 1000 पूर्ण,
	अणु 36, 5, 6, 3, 63, 1000 पूर्ण,
	अणु 37, 5, 6, 3, 63, 1000 पूर्ण,
	अणु 38, 5, 6, 3, 63, 975 पूर्ण,
	अणु 39, 3, 12, 3, 63, 950 पूर्ण,
	अणु 40, 3, 12, 3, 63, 925 पूर्ण,
	अणु 41, 3, 12, 3, 63, 900 पूर्ण,
	अणु 42, 3, 12, 3, 63, 875 पूर्ण,
	अणु 43, 3, 12, 3, 63, 850 पूर्ण,
	अणु 44, 3, 12, 3, 63, 850 पूर्ण,
	अणु 45, 3, 12, 3, 63, 825 पूर्ण,
	अणु 46, 3, 12, 3, 63, 800 पूर्ण,
	अणु 47, 3, 12, 3, 63, 775 पूर्ण,
	अणु 48, 3, 12, 3, 63, 775 पूर्ण,
	अणु 49, 3, 12, 3, 63, 750 पूर्ण,
	अणु 50, 3, 12, 3, 63, 750 पूर्ण,
	अणु 51, 3, 2, 3, 63, 725 पूर्ण,
	अणु 52, 3, 2, 3, 63, 700 पूर्ण,
	अणु 53, 3, 2, 3, 63, 700 पूर्ण,
	अणु 54, 3, 2, 3, 63, 675 पूर्ण,
	अणु 55, 3, 2, 3, 63, 675 पूर्ण,
	अणु 56, 3, 2, 3, 63, 650 पूर्ण,
	अणु 57, 3, 2, 3, 63, 650 पूर्ण,
	अणु 58, 3, 2, 3, 63, 625 पूर्ण,
	अणु 59, 3, 2, 3, 63, 625 पूर्ण,
	अणु 60, 3, 2, 3, 63, 625 पूर्ण,
	अणु 61, 3, 2, 3, 63, 600 पूर्ण,
	अणु 62, 3, 2, 3, 63, 600 पूर्ण,
	अणु 63, 3, 2, 3, 63, 600 पूर्ण,
	अणु 64, 3, 2, 3, 63, 600 पूर्ण,
	अणु 65, 3, 2, 3, 63, 600 पूर्ण,
	अणु 66, 3, 2, 3, 63, 600 पूर्ण,
	अणु 67, 3, 2, 3, 63, 600 पूर्ण,
	अणु 68, 3, 2, 3, 63, 600 पूर्ण,
	अणु 69, 3, 2, 3, 63, 600 पूर्ण,
	अणु 70, 3, 2, 3, 63, 600 पूर्ण,
	अणु 71, 3, 2, 3, 63, 600 पूर्ण,
	अणु 72, 3, 2, 3, 63, 600 पूर्ण,
	अणु 73, 3, 2, 3, 63, 600 पूर्ण,
	अणु 74, 3, 2, 3, 63, 600 पूर्ण,
	अणु 75, 3, 2, 3, 63, 600 पूर्ण,
	अणु 76, 3, 2, 3, 63, 600 पूर्ण,
	अणु 77, 3, 2, 3, 63, 600 पूर्ण,
	अणु 78, 3, 2, 3, 63, 600 पूर्ण,
	अणु 79, 3, 2, 3, 63, 600 पूर्ण,
	अणु 80, 3, 2, 3, 63, 600 पूर्ण,
	अणु 81, 3, 2, 3, 63, 600 पूर्ण,
	अणु 82, 3, 2, 3, 63, 600 पूर्ण,
	अणु 83, 4, 2, 3, 63, 600 पूर्ण,
	अणु 84, 4, 2, 3, 63, 600 पूर्ण,
	अणु 85, 4, 2, 3, 63, 600 पूर्ण,
	अणु 86, 4, 2, 3, 63, 600 पूर्ण,
	अणु 87, 4, 2, 3, 63, 600 पूर्ण,
	अणु 88, 4, 2, 3, 63, 600 पूर्ण,
	अणु 89, 4, 2, 3, 63, 600 पूर्ण,
	अणु 90, 4, 2, 3, 63, 600 पूर्ण,
	अणु 91, 4, 2, 3, 63, 600 पूर्ण,
	अणु 92, 4, 2, 3, 63, 600 पूर्ण,
	अणु 93, 4, 2, 3, 63, 600 पूर्ण,
	अणु 94, 4, 2, 3, 63, 600 पूर्ण,
	अणु 95, 4, 2, 3, 63, 600 पूर्ण,
	अणु 96, 4, 2, 3, 63, 600 पूर्ण,
	अणु 97, 4, 2, 3, 63, 600 पूर्ण,
	अणु 98, 4, 2, 3, 63, 600 पूर्ण,
	अणु 99, 4, 2, 3, 63, 600 पूर्ण,
	अणु 100, 4, 2, 3, 63, 600 पूर्ण,
	अणु 101, 4, 2, 3, 63, 600 पूर्ण,
	अणु 102, 4, 2, 3, 63, 600 पूर्ण,
	अणु 103, 5, 2, 3, 63, 600 पूर्ण,
	अणु 104, 5, 2, 3, 63, 600 पूर्ण,
	अणु 105, 5, 2, 3, 63, 600 पूर्ण,
	अणु 106, 5, 2, 3, 63, 600 पूर्ण,
	अणु 107, 3, 4, 3, 63, 600 पूर्ण,
	अणु 108, 3, 4, 3, 63, 600 पूर्ण,
	अणु 109, 3, 4, 3, 63, 600 पूर्ण,
	अणु 110, 3, 4, 3, 63, 600 पूर्ण,
	अणु 111, 3, 4, 3, 63, 600 पूर्ण,
	अणु 112, 3, 4, 3, 63, 600 पूर्ण,
	अणु 113, 3, 4, 3, 63, 600 पूर्ण,
	अणु 114, 3, 4, 3, 63, 600 पूर्ण,
	अणु 115, 3, 4, 3, 63, 600 पूर्ण,
	अणु 116, 3, 4, 3, 63, 600 पूर्ण,
	अणु 117, 3, 4, 3, 63, 600 पूर्ण,
	अणु 118, 3, 4, 3, 63, 600 पूर्ण,
	अणु 119, 3, 4, 3, 63, 600 पूर्ण,
	अणु 120, 3, 4, 3, 63, 600 पूर्ण,
	अणु 121, 3, 4, 3, 63, 600 पूर्ण,
	अणु 122, 3, 4, 3, 63, 600 पूर्ण,
	अणु 123, 3, 4, 3, 63, 600 पूर्ण,
	अणु 124, 3, 4, 3, 63, 600 पूर्ण,
	अणु 125, 3, 4, 3, 63, 600 पूर्ण,
पूर्ण;

/**
 * xvcu_पढ़ो - Read from the VCU रेजिस्टर space
 * @iomem:	vcu reg space base address
 * @offset:	vcu reg offset from base
 *
 * Return:	Returns 32bit value from VCU रेजिस्टर specअगरied
 *
 */
अटल अंतरभूत u32 xvcu_पढ़ो(व्योम __iomem *iomem, u32 offset)
अणु
	वापस ioपढ़ो32(iomem + offset);
पूर्ण

/**
 * xvcu_ग_लिखो - Write to the VCU रेजिस्टर space
 * @iomem:	vcu reg space base address
 * @offset:	vcu reg offset from base
 * @value:	Value to ग_लिखो
 */
अटल अंतरभूत व्योम xvcu_ग_लिखो(व्योम __iomem *iomem, u32 offset, u32 value)
अणु
	ioग_लिखो32(value, iomem + offset);
पूर्ण

#घोषणा to_vcu_pll(_hw) container_of(_hw, काष्ठा vcu_pll, hw)

काष्ठा vcu_pll अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *reg_base;
	अचिन्हित दीर्घ fvco_min;
	अचिन्हित दीर्घ fvco_max;
पूर्ण;

अटल पूर्णांक xvcu_pll_रुको_क्रम_lock(काष्ठा vcu_pll *pll)
अणु
	व्योम __iomem *base = pll->reg_base;
	अचिन्हित दीर्घ समयout;
	u32 lock_status;

	समयout = jअगरfies + msecs_to_jअगरfies(2000);
	करो अणु
		lock_status = xvcu_पढ़ो(base, VCU_PLL_STATUS);
		अगर (lock_status & VCU_PLL_STATUS_LOCK_STATUS)
			वापस 0;
	पूर्ण जबतक (!समय_after(jअगरfies, समयout));

	वापस -ETIMEDOUT;
पूर्ण

अटल काष्ठा clk_hw *xvcu_रेजिस्टर_pll_post(काष्ठा device *dev,
					     स्थिर अक्षर *name,
					     स्थिर काष्ठा clk_hw *parent_hw,
					     व्योम __iomem *reg_base)
अणु
	u32 भाग;
	u32 vcu_pll_ctrl;

	/*
	 * The output भागider of the PLL must be set to 1/2 to meet the
	 * timing in the design.
	 */
	vcu_pll_ctrl = xvcu_पढ़ो(reg_base, VCU_PLL_CTRL);
	भाग = FIELD_GET(VCU_PLL_CTRL_CLKOUTDIV, vcu_pll_ctrl);
	अगर (भाग != 1)
		वापस ERR_PTR(-EINVAL);

	वापस clk_hw_रेजिस्टर_fixed_factor(dev, "vcu_pll_post",
					    clk_hw_get_name(parent_hw),
					    CLK_SET_RATE_PARENT, 1, 2);
पूर्ण

अटल स्थिर काष्ठा xvcu_pll_cfg *xvcu_find_cfg(पूर्णांक भाग)
अणु
	स्थिर काष्ठा xvcu_pll_cfg *cfg = शून्य;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(xvcu_pll_cfg) - 1; i++)
		अगर (xvcu_pll_cfg[i].fbभाग == भाग)
			cfg = &xvcu_pll_cfg[i];

	वापस cfg;
पूर्ण

अटल पूर्णांक xvcu_pll_set_भाग(काष्ठा vcu_pll *pll, पूर्णांक भाग)
अणु
	व्योम __iomem *base = pll->reg_base;
	स्थिर काष्ठा xvcu_pll_cfg *cfg = शून्य;
	u32 vcu_pll_ctrl;
	u32 cfg_val;

	cfg = xvcu_find_cfg(भाग);
	अगर (!cfg)
		वापस -EINVAL;

	vcu_pll_ctrl = xvcu_पढ़ो(base, VCU_PLL_CTRL);
	vcu_pll_ctrl &= ~VCU_PLL_CTRL_FBDIV;
	vcu_pll_ctrl |= FIELD_PREP(VCU_PLL_CTRL_FBDIV, cfg->fbभाग);
	xvcu_ग_लिखो(base, VCU_PLL_CTRL, vcu_pll_ctrl);

	cfg_val = FIELD_PREP(VCU_PLL_CFG_RES, cfg->res) |
		  FIELD_PREP(VCU_PLL_CFG_CP, cfg->cp) |
		  FIELD_PREP(VCU_PLL_CFG_LFHF, cfg->lfhf) |
		  FIELD_PREP(VCU_PLL_CFG_LOCK_CNT, cfg->lock_cnt) |
		  FIELD_PREP(VCU_PLL_CFG_LOCK_DLY, cfg->lock_dly);
	xvcu_ग_लिखो(base, VCU_PLL_CFG, cfg_val);

	वापस 0;
पूर्ण

अटल दीर्घ xvcu_pll_round_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ rate, अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा vcu_pll *pll = to_vcu_pll(hw);
	अचिन्हित पूर्णांक feedback_भाग;

	rate = clamp_t(अचिन्हित दीर्घ, rate, pll->fvco_min, pll->fvco_max);

	feedback_भाग = DIV_ROUND_CLOSEST_ULL(rate, *parent_rate);
	feedback_भाग = clamp_t(अचिन्हित पूर्णांक, feedback_भाग, 25, 125);

	वापस *parent_rate * feedback_भाग;
पूर्ण

अटल अचिन्हित दीर्घ xvcu_pll_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा vcu_pll *pll = to_vcu_pll(hw);
	व्योम __iomem *base = pll->reg_base;
	अचिन्हित पूर्णांक भाग;
	u32 vcu_pll_ctrl;

	vcu_pll_ctrl = xvcu_पढ़ो(base, VCU_PLL_CTRL);
	भाग = FIELD_GET(VCU_PLL_CTRL_FBDIV, vcu_pll_ctrl);

	वापस भाग * parent_rate;
पूर्ण

अटल पूर्णांक xvcu_pll_set_rate(काष्ठा clk_hw *hw,
			     अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा vcu_pll *pll = to_vcu_pll(hw);

	वापस xvcu_pll_set_भाग(pll, rate / parent_rate);
पूर्ण

अटल पूर्णांक xvcu_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा vcu_pll *pll = to_vcu_pll(hw);
	व्योम __iomem *base = pll->reg_base;
	u32 vcu_pll_ctrl;
	पूर्णांक ret;

	vcu_pll_ctrl = xvcu_पढ़ो(base, VCU_PLL_CTRL);
	vcu_pll_ctrl |= VCU_PLL_CTRL_BYPASS;
	xvcu_ग_लिखो(base, VCU_PLL_CTRL, vcu_pll_ctrl);

	vcu_pll_ctrl = xvcu_पढ़ो(base, VCU_PLL_CTRL);
	vcu_pll_ctrl &= ~VCU_PLL_CTRL_POR_IN;
	vcu_pll_ctrl &= ~VCU_PLL_CTRL_PWR_POR;
	vcu_pll_ctrl &= ~VCU_PLL_CTRL_RESET;
	xvcu_ग_लिखो(base, VCU_PLL_CTRL, vcu_pll_ctrl);

	ret = xvcu_pll_रुको_क्रम_lock(pll);
	अगर (ret) अणु
		pr_err("VCU PLL is not locked\n");
		जाओ err;
	पूर्ण

	vcu_pll_ctrl = xvcu_पढ़ो(base, VCU_PLL_CTRL);
	vcu_pll_ctrl &= ~VCU_PLL_CTRL_BYPASS;
	xvcu_ग_लिखो(base, VCU_PLL_CTRL, vcu_pll_ctrl);

err:
	वापस ret;
पूर्ण

अटल व्योम xvcu_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा vcu_pll *pll = to_vcu_pll(hw);
	व्योम __iomem *base = pll->reg_base;
	u32 vcu_pll_ctrl;

	vcu_pll_ctrl = xvcu_पढ़ो(base, VCU_PLL_CTRL);
	vcu_pll_ctrl |= VCU_PLL_CTRL_POR_IN;
	vcu_pll_ctrl |= VCU_PLL_CTRL_PWR_POR;
	vcu_pll_ctrl |= VCU_PLL_CTRL_RESET;
	xvcu_ग_लिखो(base, VCU_PLL_CTRL, vcu_pll_ctrl);
पूर्ण

अटल स्थिर काष्ठा clk_ops vcu_pll_ops = अणु
	.enable = xvcu_pll_enable,
	.disable = xvcu_pll_disable,
	.round_rate = xvcu_pll_round_rate,
	.recalc_rate = xvcu_pll_recalc_rate,
	.set_rate = xvcu_pll_set_rate,
पूर्ण;

अटल काष्ठा clk_hw *xvcu_रेजिस्टर_pll(काष्ठा device *dev,
					व्योम __iomem *reg_base,
					स्थिर अक्षर *name, स्थिर अक्षर *parent,
					अचिन्हित दीर्घ flags)
अणु
	काष्ठा vcu_pll *pll;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	init.name = name;
	init.parent_names = &parent;
	init.ops = &vcu_pll_ops;
	init.num_parents = 1;
	init.flags = flags;

	pll = devm_kदो_स्मृति(dev, माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	pll->hw.init = &init;
	pll->reg_base = reg_base;
	pll->fvco_min = FVCO_MIN;
	pll->fvco_max = FVCO_MAX;

	hw = &pll->hw;
	ret = devm_clk_hw_रेजिस्टर(dev, hw);
	अगर (ret)
		वापस ERR_PTR(ret);

	clk_hw_set_rate_range(hw, pll->fvco_min, pll->fvco_max);

	वापस hw;
पूर्ण

अटल काष्ठा clk_hw *xvcu_clk_hw_रेजिस्टर_leaf(काष्ठा device *dev,
						स्थिर अक्षर *name,
						स्थिर काष्ठा clk_parent_data *parent_data,
						u8 num_parents,
						व्योम __iomem *reg)
अणु
	u8 mux_flags = CLK_MUX_ROUND_CLOSEST;
	u8 भागider_flags = CLK_DIVIDER_ONE_BASED | CLK_DIVIDER_ALLOW_ZERO |
			   CLK_DIVIDER_ROUND_CLOSEST;
	काष्ठा clk_hw *mux = शून्य;
	काष्ठा clk_hw *भागider = शून्य;
	काष्ठा clk_hw *gate = शून्य;
	अक्षर *name_mux;
	अक्षर *name_भाग;
	पूर्णांक err;
	/* Protect रेजिस्टर shared by घड़ीs */
	spinlock_t *lock;

	lock = devm_kzalloc(dev, माप(*lock), GFP_KERNEL);
	अगर (!lock)
		वापस ERR_PTR(-ENOMEM);
	spin_lock_init(lock);

	name_mux = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s%s", name, "_mux");
	अगर (!name_mux)
		वापस ERR_PTR(-ENOMEM);
	mux = clk_hw_रेजिस्टर_mux_parent_data(dev, name_mux,
					      parent_data, num_parents,
					      CLK_SET_RATE_PARENT,
					      reg, 0, 1, mux_flags, lock);
	अगर (IS_ERR(mux))
		वापस mux;

	name_भाग = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s%s", name, "_div");
	अगर (!name_भाग) अणु
		err = -ENOMEM;
		जाओ unरेजिस्टर_mux;
	पूर्ण
	भागider = clk_hw_रेजिस्टर_भागider_parent_hw(dev, name_भाग, mux,
						    CLK_SET_RATE_PARENT,
						    reg, 4, 6, भागider_flags,
						    lock);
	अगर (IS_ERR(भागider)) अणु
		err = PTR_ERR(भागider);
		जाओ unरेजिस्टर_mux;
	पूर्ण

	gate = clk_hw_रेजिस्टर_gate_parent_hw(dev, name, भागider,
					      CLK_SET_RATE_PARENT, reg, 12, 0,
					      lock);
	अगर (IS_ERR(gate)) अणु
		err = PTR_ERR(gate);
		जाओ unरेजिस्टर_भागider;
	पूर्ण

	वापस gate;

unरेजिस्टर_भागider:
	clk_hw_unरेजिस्टर_भागider(भागider);
unरेजिस्टर_mux:
	clk_hw_unरेजिस्टर_mux(mux);

	वापस ERR_PTR(err);
पूर्ण

अटल व्योम xvcu_clk_hw_unरेजिस्टर_leaf(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw *gate = hw;
	काष्ठा clk_hw *भागider;
	काष्ठा clk_hw *mux;

	अगर (!gate)
		वापस;

	भागider = clk_hw_get_parent(gate);
	clk_hw_unरेजिस्टर_gate(gate);
	अगर (!भागider)
		वापस;

	mux = clk_hw_get_parent(भागider);
	clk_hw_unरेजिस्टर_mux(mux);
	अगर (!भागider)
		वापस;

	clk_hw_unरेजिस्टर_भागider(भागider);
पूर्ण

अटल पूर्णांक xvcu_रेजिस्टर_घड़ी_provider(काष्ठा xvcu_device *xvcu)
अणु
	काष्ठा device *dev = xvcu->dev;
	काष्ठा clk_parent_data parent_data[2] = अणु 0 पूर्ण;
	काष्ठा clk_hw_onecell_data *data;
	काष्ठा clk_hw **hws;
	काष्ठा clk_hw *hw;
	व्योम __iomem *reg_base = xvcu->vcu_slcr_ba;

	data = devm_kzalloc(dev, काष्ठा_size(data, hws, CLK_XVCU_NUM_CLOCKS), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	data->num = CLK_XVCU_NUM_CLOCKS;
	hws = data->hws;

	xvcu->clk_data = data;

	hw = xvcu_रेजिस्टर_pll(dev, reg_base,
			       "vcu_pll", __clk_get_name(xvcu->pll_ref),
			       CLK_SET_RATE_NO_REPARENT | CLK_OPS_PARENT_ENABLE);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	xvcu->pll = hw;

	hw = xvcu_रेजिस्टर_pll_post(dev, "vcu_pll_post", xvcu->pll, reg_base);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	xvcu->pll_post = hw;

	parent_data[0].fw_name = "pll_ref";
	parent_data[1].hw = xvcu->pll_post;

	hws[CLK_XVCU_ENC_CORE] =
		xvcu_clk_hw_रेजिस्टर_leaf(dev, "venc_core_clk",
					  parent_data,
					  ARRAY_SIZE(parent_data),
					  reg_base + VCU_ENC_CORE_CTRL);
	hws[CLK_XVCU_ENC_MCU] =
		xvcu_clk_hw_रेजिस्टर_leaf(dev, "venc_mcu_clk",
					  parent_data,
					  ARRAY_SIZE(parent_data),
					  reg_base + VCU_ENC_MCU_CTRL);
	hws[CLK_XVCU_DEC_CORE] =
		xvcu_clk_hw_रेजिस्टर_leaf(dev, "vdec_core_clk",
					  parent_data,
					  ARRAY_SIZE(parent_data),
					  reg_base + VCU_DEC_CORE_CTRL);
	hws[CLK_XVCU_DEC_MCU] =
		xvcu_clk_hw_रेजिस्टर_leaf(dev, "vdec_mcu_clk",
					  parent_data,
					  ARRAY_SIZE(parent_data),
					  reg_base + VCU_DEC_MCU_CTRL);

	वापस devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get, data);
पूर्ण

अटल व्योम xvcu_unरेजिस्टर_घड़ी_provider(काष्ठा xvcu_device *xvcu)
अणु
	काष्ठा clk_hw_onecell_data *data = xvcu->clk_data;
	काष्ठा clk_hw **hws = data->hws;

	अगर (!IS_ERR_OR_शून्य(hws[CLK_XVCU_DEC_MCU]))
		xvcu_clk_hw_unरेजिस्टर_leaf(hws[CLK_XVCU_DEC_MCU]);
	अगर (!IS_ERR_OR_शून्य(hws[CLK_XVCU_DEC_CORE]))
		xvcu_clk_hw_unरेजिस्टर_leaf(hws[CLK_XVCU_DEC_CORE]);
	अगर (!IS_ERR_OR_शून्य(hws[CLK_XVCU_ENC_MCU]))
		xvcu_clk_hw_unरेजिस्टर_leaf(hws[CLK_XVCU_ENC_MCU]);
	अगर (!IS_ERR_OR_शून्य(hws[CLK_XVCU_ENC_CORE]))
		xvcu_clk_hw_unरेजिस्टर_leaf(hws[CLK_XVCU_ENC_CORE]);

	clk_hw_unरेजिस्टर_fixed_factor(xvcu->pll_post);
पूर्ण

/**
 * xvcu_probe - Probe existence of the logicoreIP
 *			and initialize PLL
 *
 * @pdev:	Poपूर्णांकer to the platक्रमm_device काष्ठाure
 *
 * Return:	Returns 0 on success
 *		Negative error code otherwise
 */
अटल पूर्णांक xvcu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा xvcu_device *xvcu;
	व्योम __iomem *regs;
	पूर्णांक ret;

	xvcu = devm_kzalloc(&pdev->dev, माप(*xvcu), GFP_KERNEL);
	अगर (!xvcu)
		वापस -ENOMEM;

	xvcu->dev = &pdev->dev;
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "vcu_slcr");
	अगर (!res) अणु
		dev_err(&pdev->dev, "get vcu_slcr memory resource failed.\n");
		वापस -ENODEV;
	पूर्ण

	xvcu->vcu_slcr_ba = devm_ioremap(&pdev->dev, res->start,
					 resource_size(res));
	अगर (!xvcu->vcu_slcr_ba) अणु
		dev_err(&pdev->dev, "vcu_slcr register mapping failed.\n");
		वापस -ENOMEM;
	पूर्ण

	xvcu->logicore_reg_ba =
		syscon_regmap_lookup_by_compatible("xlnx,vcu-settings");
	अगर (IS_ERR(xvcu->logicore_reg_ba)) अणु
		dev_info(&pdev->dev,
			 "could not find xlnx,vcu-settings: trying direct register access\n");

		res = platक्रमm_get_resource_byname(pdev,
						   IORESOURCE_MEM, "logicore");
		अगर (!res) अणु
			dev_err(&pdev->dev, "get logicore memory resource failed.\n");
			वापस -ENODEV;
		पूर्ण

		regs = devm_ioremap(&pdev->dev, res->start, resource_size(res));
		अगर (!regs) अणु
			dev_err(&pdev->dev, "logicore register mapping failed.\n");
			वापस -ENOMEM;
		पूर्ण

		xvcu->logicore_reg_ba =
			devm_regmap_init_mmio(&pdev->dev, regs,
					      &vcu_settings_regmap_config);
		अगर (IS_ERR(xvcu->logicore_reg_ba)) अणु
			dev_err(&pdev->dev, "failed to init regmap\n");
			वापस PTR_ERR(xvcu->logicore_reg_ba);
		पूर्ण
	पूर्ण

	xvcu->aclk = devm_clk_get(&pdev->dev, "aclk");
	अगर (IS_ERR(xvcu->aclk)) अणु
		dev_err(&pdev->dev, "Could not get aclk clock\n");
		वापस PTR_ERR(xvcu->aclk);
	पूर्ण

	xvcu->pll_ref = devm_clk_get(&pdev->dev, "pll_ref");
	अगर (IS_ERR(xvcu->pll_ref)) अणु
		dev_err(&pdev->dev, "Could not get pll_ref clock\n");
		वापस PTR_ERR(xvcu->pll_ref);
	पूर्ण

	ret = clk_prepare_enable(xvcu->aclk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "aclk clock enable failed\n");
		वापस ret;
	पूर्ण

	/*
	 * Do the Gasket isolation and put the VCU out of reset
	 * Bit 0 : Gasket isolation
	 * Bit 1 : put VCU out of reset
	 */
	regmap_ग_लिखो(xvcu->logicore_reg_ba, VCU_GASKET_INIT, VCU_GASKET_VALUE);

	ret = xvcu_रेजिस्टर_घड़ी_provider(xvcu);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register clock provider\n");
		जाओ error_clk_provider;
	पूर्ण

	dev_set_drvdata(&pdev->dev, xvcu);

	वापस 0;

error_clk_provider:
	xvcu_unरेजिस्टर_घड़ी_provider(xvcu);
	clk_disable_unprepare(xvcu->aclk);
	वापस ret;
पूर्ण

/**
 * xvcu_हटाओ - Insert gasket isolation
 *			and disable the घड़ी
 * @pdev:	Poपूर्णांकer to the platक्रमm_device काष्ठाure
 *
 * Return:	Returns 0 on success
 *		Negative error code otherwise
 */
अटल पूर्णांक xvcu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xvcu_device *xvcu;

	xvcu = platक्रमm_get_drvdata(pdev);
	अगर (!xvcu)
		वापस -ENODEV;

	xvcu_unरेजिस्टर_घड़ी_provider(xvcu);

	/* Add the Gasket isolation and put the VCU in reset. */
	regmap_ग_लिखो(xvcu->logicore_reg_ba, VCU_GASKET_INIT, 0);

	clk_disable_unprepare(xvcu->aclk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id xvcu_of_id_table[] = अणु
	अणु .compatible = "xlnx,vcu" पूर्ण,
	अणु .compatible = "xlnx,vcu-logicoreip-1.0" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, xvcu_of_id_table);

अटल काष्ठा platक्रमm_driver xvcu_driver = अणु
	.driver = अणु
		.name           = "xilinx-vcu",
		.of_match_table = xvcu_of_id_table,
	पूर्ण,
	.probe                  = xvcu_probe,
	.हटाओ                 = xvcu_हटाओ,
पूर्ण;

module_platक्रमm_driver(xvcu_driver);

MODULE_AUTHOR("Dhaval Shah <dshah@xilinx.com>");
MODULE_DESCRIPTION("Xilinx VCU init Driver");
MODULE_LICENSE("GPL v2");
