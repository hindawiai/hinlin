<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 */

/*
 * Each of the CPU clusters (Power and Perf) on msm8996 are
 * घड़ीed via 2 PLLs, a primary and alternate. There are also
 * 2 Mux'es, a primary and secondary all connected together
 * as shown below
 *
 *                              +-------+
 *               XO             |       |
 *           +------------------>0      |
 *                              |       |
 *                    PLL/2     | SMUX  +----+
 *                      +------->1      |    |
 *                      |       |       |    |
 *                      |       +-------+    |    +-------+
 *                      |                    +---->0      |
 *                      |                         |       |
 * +---------------+    |             +----------->1      | CPU clk
 * |Primary PLL    +----+ PLL_EARLY   |           |       +------>
 * |               +------+-----------+    +------>2 PMUX |
 * +---------------+      |                |      |       |
 *                        |   +------+     |   +-->3      |
 *                        +--^+  ACD +-----+   |  +-------+
 * +---------------+          +------+         |
 * |Alt PLL        |                           |
 * |               +---------------------------+
 * +---------------+         PLL_EARLY
 *
 * The primary PLL is what drives the CPU clk, except क्रम बार
 * when we are reprogramming the PLL itself (क्रम rate changes) when
 * we temporarily चयन to an alternate PLL.
 *
 * The primary PLL operates on a single VCO range, between 600MHz
 * and 3GHz. However the CPUs करो support OPPs with frequencies
 * between 300MHz and 600MHz. In order to support running the CPUs
 * at those frequencies we end up having to lock the PLL at twice
 * the rate and drive the CPU clk via the PLL/2 output and SMUX.
 *
 * So क्रम frequencies above 600MHz we follow the following path
 *  Primary PLL --> PLL_EARLY --> PMUX(1) --> CPU clk
 * and क्रम frequencies between 300MHz and 600MHz we follow
 *  Primary PLL --> PLL/2 --> SMUX(1) --> PMUX(0) --> CPU clk
 *
 * ACD stands क्रम Adaptive Clock Distribution and is used to
 * detect voltage droops.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <soc/qcom/kryo-l2-accessors.h>

#समावेश "clk-alpha-pll.h"
#समावेश "clk-regmap.h"

क्रमागत _pmux_input अणु
	DIV_2_INDEX = 0,
	PLL_INDEX,
	ACD_INDEX,
	ALT_INDEX,
	NUM_OF_PMUX_INPUTS
पूर्ण;

#घोषणा DIV_2_THRESHOLD		600000000
#घोषणा PWRCL_REG_OFFSET 0x0
#घोषणा PERFCL_REG_OFFSET 0x80000
#घोषणा MUX_OFFSET	0x40
#घोषणा ALT_PLL_OFFSET	0x100
#घोषणा SSSCTL_OFFSET 0x160

अटल स्थिर u8 prim_pll_regs[PLL_OFF_MAX_REGS] = अणु
	[PLL_OFF_L_VAL] = 0x04,
	[PLL_OFF_ALPHA_VAL] = 0x08,
	[PLL_OFF_USER_CTL] = 0x10,
	[PLL_OFF_CONFIG_CTL] = 0x18,
	[PLL_OFF_CONFIG_CTL_U] = 0x1c,
	[PLL_OFF_TEST_CTL] = 0x20,
	[PLL_OFF_TEST_CTL_U] = 0x24,
	[PLL_OFF_STATUS] = 0x28,
पूर्ण;

अटल स्थिर u8 alt_pll_regs[PLL_OFF_MAX_REGS] = अणु
	[PLL_OFF_L_VAL] = 0x04,
	[PLL_OFF_ALPHA_VAL] = 0x08,
	[PLL_OFF_ALPHA_VAL_U] = 0x0c,
	[PLL_OFF_USER_CTL] = 0x10,
	[PLL_OFF_USER_CTL_U] = 0x14,
	[PLL_OFF_CONFIG_CTL] = 0x18,
	[PLL_OFF_TEST_CTL] = 0x20,
	[PLL_OFF_TEST_CTL_U] = 0x24,
	[PLL_OFF_STATUS] = 0x28,
पूर्ण;

/* PLLs */

अटल स्थिर काष्ठा alpha_pll_config hfpll_config = अणु
	.l = 60,
	.config_ctl_val = 0x200d4aa8,
	.config_ctl_hi_val = 0x006,
	.pre_भाग_mask = BIT(12),
	.post_भाग_mask = 0x3 << 8,
	.post_भाग_val = 0x1 << 8,
	.मुख्य_output_mask = BIT(0),
	.early_output_mask = BIT(3),
पूर्ण;

अटल काष्ठा clk_alpha_pll perfcl_pll = अणु
	.offset = PERFCL_REG_OFFSET,
	.regs = prim_pll_regs,
	.flags = SUPPORTS_DYNAMIC_UPDATE | SUPPORTS_FSM_MODE,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "perfcl_pll",
		.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_huayra_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll pwrcl_pll = अणु
	.offset = PWRCL_REG_OFFSET,
	.regs = prim_pll_regs,
	.flags = SUPPORTS_DYNAMIC_UPDATE | SUPPORTS_FSM_MODE,
	.clkr.hw.init = &(काष्ठा clk_init_data)अणु
		.name = "pwrcl_pll",
		.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_huayra_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pll_vco alt_pll_vco_modes[] = अणु
	VCO(3,  250000000,  500000000),
	VCO(2,  500000000,  750000000),
	VCO(1,  750000000, 1000000000),
	VCO(0, 1000000000, 2150400000),
पूर्ण;

अटल स्थिर काष्ठा alpha_pll_config altpll_config = अणु
	.l = 16,
	.vco_val = 0x3 << 20,
	.vco_mask = 0x3 << 20,
	.config_ctl_val = 0x4001051b,
	.post_भाग_mask = 0x3 << 8,
	.post_भाग_val = 0x1 << 8,
	.मुख्य_output_mask = BIT(0),
	.early_output_mask = BIT(3),
पूर्ण;

अटल काष्ठा clk_alpha_pll perfcl_alt_pll = अणु
	.offset = PERFCL_REG_OFFSET + ALT_PLL_OFFSET,
	.regs = alt_pll_regs,
	.vco_table = alt_pll_vco_modes,
	.num_vco = ARRAY_SIZE(alt_pll_vco_modes),
	.flags = SUPPORTS_OFFLINE_REQ | SUPPORTS_FSM_MODE,
	.clkr.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "perfcl_alt_pll",
		.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_hwfsm_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_alpha_pll pwrcl_alt_pll = अणु
	.offset = PWRCL_REG_OFFSET + ALT_PLL_OFFSET,
	.regs = alt_pll_regs,
	.vco_table = alt_pll_vco_modes,
	.num_vco = ARRAY_SIZE(alt_pll_vco_modes),
	.flags = SUPPORTS_OFFLINE_REQ | SUPPORTS_FSM_MODE,
	.clkr.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "pwrcl_alt_pll",
		.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
		.num_parents = 1,
		.ops = &clk_alpha_pll_hwfsm_ops,
	पूर्ण,
पूर्ण;

काष्ठा clk_cpu_8996_mux अणु
	u32	reg;
	u8	shअगरt;
	u8	width;
	काष्ठा notअगरier_block nb;
	काष्ठा clk_hw	*pll;
	काष्ठा clk_hw	*pll_भाग_2;
	काष्ठा clk_regmap clkr;
पूर्ण;

अटल पूर्णांक cpu_clk_notअगरier_cb(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			       व्योम *data);

#घोषणा to_clk_cpu_8996_mux_nb(_nb) \
	container_of(_nb, काष्ठा clk_cpu_8996_mux, nb)

अटल अंतरभूत काष्ठा clk_cpu_8996_mux *to_clk_cpu_8996_mux_hw(काष्ठा clk_hw *hw)
अणु
	वापस container_of(to_clk_regmap(hw), काष्ठा clk_cpu_8996_mux, clkr);
पूर्ण

अटल u8 clk_cpu_8996_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap *clkr = to_clk_regmap(hw);
	काष्ठा clk_cpu_8996_mux *cpuclk = to_clk_cpu_8996_mux_hw(hw);
	u32 mask = GENMASK(cpuclk->width - 1, 0);
	u32 val;

	regmap_पढ़ो(clkr->regmap, cpuclk->reg, &val);
	val >>= cpuclk->shअगरt;

	वापस val & mask;
पूर्ण

अटल पूर्णांक clk_cpu_8996_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_regmap *clkr = to_clk_regmap(hw);
	काष्ठा clk_cpu_8996_mux *cpuclk = to_clk_cpu_8996_mux_hw(hw);
	u32 mask = GENMASK(cpuclk->width + cpuclk->shअगरt - 1, cpuclk->shअगरt);
	u32 val;

	val = index;
	val <<= cpuclk->shअगरt;

	वापस regmap_update_bits(clkr->regmap, cpuclk->reg, mask, val);
पूर्ण

अटल पूर्णांक clk_cpu_8996_mux_determine_rate(काष्ठा clk_hw *hw,
					   काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_cpu_8996_mux *cpuclk = to_clk_cpu_8996_mux_hw(hw);
	काष्ठा clk_hw *parent = cpuclk->pll;

	अगर (cpuclk->pll_भाग_2 && req->rate < DIV_2_THRESHOLD) अणु
		अगर (req->rate < (DIV_2_THRESHOLD / 2))
			वापस -EINVAL;

		parent = cpuclk->pll_भाग_2;
	पूर्ण

	req->best_parent_rate = clk_hw_round_rate(parent, req->rate);
	req->best_parent_hw = parent;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_cpu_8996_mux_ops = अणु
	.set_parent = clk_cpu_8996_mux_set_parent,
	.get_parent = clk_cpu_8996_mux_get_parent,
	.determine_rate = clk_cpu_8996_mux_determine_rate,
पूर्ण;

अटल काष्ठा clk_cpu_8996_mux pwrcl_smux = अणु
	.reg = PWRCL_REG_OFFSET + MUX_OFFSET,
	.shअगरt = 2,
	.width = 2,
	.clkr.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "pwrcl_smux",
		.parent_names = (स्थिर अक्षर *[])अणु
			"xo",
			"pwrcl_pll_main",
		पूर्ण,
		.num_parents = 2,
		.ops = &clk_cpu_8996_mux_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_cpu_8996_mux perfcl_smux = अणु
	.reg = PERFCL_REG_OFFSET + MUX_OFFSET,
	.shअगरt = 2,
	.width = 2,
	.clkr.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "perfcl_smux",
		.parent_names = (स्थिर अक्षर *[])अणु
			"xo",
			"perfcl_pll_main",
		पूर्ण,
		.num_parents = 2,
		.ops = &clk_cpu_8996_mux_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_cpu_8996_mux pwrcl_pmux = अणु
	.reg = PWRCL_REG_OFFSET + MUX_OFFSET,
	.shअगरt = 0,
	.width = 2,
	.pll = &pwrcl_pll.clkr.hw,
	.pll_भाग_2 = &pwrcl_smux.clkr.hw,
	.nb.notअगरier_call = cpu_clk_notअगरier_cb,
	.clkr.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "pwrcl_pmux",
		.parent_names = (स्थिर अक्षर *[])अणु
			"pwrcl_smux",
			"pwrcl_pll",
			"pwrcl_pll_acd",
			"pwrcl_alt_pll",
		पूर्ण,
		.num_parents = 4,
		.ops = &clk_cpu_8996_mux_ops,
		/* CPU घड़ी is critical and should never be gated */
		.flags = CLK_SET_RATE_PARENT | CLK_IS_CRITICAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_cpu_8996_mux perfcl_pmux = अणु
	.reg = PERFCL_REG_OFFSET + MUX_OFFSET,
	.shअगरt = 0,
	.width = 2,
	.pll = &perfcl_pll.clkr.hw,
	.pll_भाग_2 = &perfcl_smux.clkr.hw,
	.nb.notअगरier_call = cpu_clk_notअगरier_cb,
	.clkr.hw.init = &(काष्ठा clk_init_data) अणु
		.name = "perfcl_pmux",
		.parent_names = (स्थिर अक्षर *[])अणु
			"perfcl_smux",
			"perfcl_pll",
			"perfcl_pll_acd",
			"perfcl_alt_pll",
		पूर्ण,
		.num_parents = 4,
		.ops = &clk_cpu_8996_mux_ops,
		/* CPU घड़ी is critical and should never be gated */
		.flags = CLK_SET_RATE_PARENT | CLK_IS_CRITICAL,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config cpu_msm8996_regmap_config = अणु
	.reg_bits		= 32,
	.reg_stride		= 4,
	.val_bits		= 32,
	.max_रेजिस्टर		= 0x80210,
	.fast_io		= true,
	.val_क्रमmat_endian	= REGMAP_ENDIAN_LITTLE,
पूर्ण;

अटल काष्ठा clk_regmap *cpu_msm8996_clks[] = अणु
	&perfcl_pll.clkr,
	&pwrcl_pll.clkr,
	&perfcl_alt_pll.clkr,
	&pwrcl_alt_pll.clkr,
	&perfcl_smux.clkr,
	&pwrcl_smux.clkr,
	&perfcl_pmux.clkr,
	&pwrcl_pmux.clkr,
पूर्ण;

अटल पूर्णांक qcom_cpu_clk_msm8996_रेजिस्टर_clks(काष्ठा device *dev,
					      काष्ठा regmap *regmap)
अणु
	पूर्णांक i, ret;

	perfcl_smux.pll = clk_hw_रेजिस्टर_fixed_factor(dev, "perfcl_pll_main",
						       "perfcl_pll",
						       CLK_SET_RATE_PARENT,
						       1, 2);
	अगर (IS_ERR(perfcl_smux.pll)) अणु
		dev_err(dev, "Failed to initialize perfcl_pll_main\n");
		वापस PTR_ERR(perfcl_smux.pll);
	पूर्ण

	pwrcl_smux.pll = clk_hw_रेजिस्टर_fixed_factor(dev, "pwrcl_pll_main",
						      "pwrcl_pll",
						      CLK_SET_RATE_PARENT,
						      1, 2);
	अगर (IS_ERR(pwrcl_smux.pll)) अणु
		dev_err(dev, "Failed to initialize pwrcl_pll_main\n");
		clk_hw_unरेजिस्टर(perfcl_smux.pll);
		वापस PTR_ERR(pwrcl_smux.pll);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(cpu_msm8996_clks); i++) अणु
		ret = devm_clk_रेजिस्टर_regmap(dev, cpu_msm8996_clks[i]);
		अगर (ret) अणु
			clk_hw_unरेजिस्टर(perfcl_smux.pll);
			clk_hw_unरेजिस्टर(pwrcl_smux.pll);
			वापस ret;
		पूर्ण
	पूर्ण

	clk_alpha_pll_configure(&perfcl_pll, regmap, &hfpll_config);
	clk_alpha_pll_configure(&pwrcl_pll, regmap, &hfpll_config);
	clk_alpha_pll_configure(&perfcl_alt_pll, regmap, &altpll_config);
	clk_alpha_pll_configure(&pwrcl_alt_pll, regmap, &altpll_config);

	/* Enable alt PLLs */
	clk_prepare_enable(pwrcl_alt_pll.clkr.hw.clk);
	clk_prepare_enable(perfcl_alt_pll.clkr.hw.clk);

	clk_notअगरier_रेजिस्टर(pwrcl_pmux.clkr.hw.clk, &pwrcl_pmux.nb);
	clk_notअगरier_रेजिस्टर(perfcl_pmux.clkr.hw.clk, &perfcl_pmux.nb);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_cpu_clk_msm8996_unरेजिस्टर_clks(व्योम)
अणु
	पूर्णांक ret = 0;

	ret = clk_notअगरier_unरेजिस्टर(pwrcl_pmux.clkr.hw.clk, &pwrcl_pmux.nb);
	अगर (ret)
		वापस ret;

	ret = clk_notअगरier_unरेजिस्टर(perfcl_pmux.clkr.hw.clk, &perfcl_pmux.nb);
	अगर (ret)
		वापस ret;

	clk_hw_unरेजिस्टर(perfcl_smux.pll);
	clk_hw_unरेजिस्टर(pwrcl_smux.pll);

	वापस 0;
पूर्ण

#घोषणा CPU_AFINITY_MASK 0xFFF
#घोषणा PWRCL_CPU_REG_MASK 0x3
#घोषणा PERFCL_CPU_REG_MASK 0x103

#घोषणा L2ACDCR_REG 0x580ULL
#घोषणा L2ACDTD_REG 0x581ULL
#घोषणा L2ACDDVMRC_REG 0x584ULL
#घोषणा L2ACDSSCR_REG 0x589ULL

अटल DEFINE_SPINLOCK(qcom_clk_acd_lock);
अटल व्योम __iomem *base;

अटल व्योम qcom_cpu_clk_msm8996_acd_init(व्योम __iomem *base)
अणु
	u64 hwid;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qcom_clk_acd_lock, flags);

	hwid = पढ़ो_cpuid_mpidr() & CPU_AFINITY_MASK;

	kryo_l2_set_indirect_reg(L2ACDTD_REG, 0x00006a11);
	kryo_l2_set_indirect_reg(L2ACDDVMRC_REG, 0x000e0f0f);
	kryo_l2_set_indirect_reg(L2ACDSSCR_REG, 0x00000601);

	अगर (PWRCL_CPU_REG_MASK == (hwid | PWRCL_CPU_REG_MASK)) अणु
		ग_लिखोl(0xf, base + PWRCL_REG_OFFSET + SSSCTL_OFFSET);
		kryo_l2_set_indirect_reg(L2ACDCR_REG, 0x002c5ffd);
	पूर्ण

	अगर (PERFCL_CPU_REG_MASK == (hwid | PERFCL_CPU_REG_MASK)) अणु
		kryo_l2_set_indirect_reg(L2ACDCR_REG, 0x002c5ffd);
		ग_लिखोl(0xf, base + PERFCL_REG_OFFSET + SSSCTL_OFFSET);
	पूर्ण

	spin_unlock_irqrestore(&qcom_clk_acd_lock, flags);
पूर्ण

अटल पूर्णांक cpu_clk_notअगरier_cb(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			       व्योम *data)
अणु
	काष्ठा clk_cpu_8996_mux *cpuclk = to_clk_cpu_8996_mux_nb(nb);
	काष्ठा clk_notअगरier_data *cnd = data;
	पूर्णांक ret;

	चयन (event) अणु
	हाल PRE_RATE_CHANGE:
		ret = clk_cpu_8996_mux_set_parent(&cpuclk->clkr.hw, ALT_INDEX);
		qcom_cpu_clk_msm8996_acd_init(base);
		अवरोध;
	हाल POST_RATE_CHANGE:
		अगर (cnd->new_rate < DIV_2_THRESHOLD)
			ret = clk_cpu_8996_mux_set_parent(&cpuclk->clkr.hw,
							  DIV_2_INDEX);
		अन्यथा
			ret = clk_cpu_8996_mux_set_parent(&cpuclk->clkr.hw,
							  ACD_INDEX);
		अवरोध;
	शेष:
		ret = 0;
		अवरोध;
	पूर्ण

	वापस notअगरier_from_त्रुटि_सं(ret);
पूर्ण;

अटल पूर्णांक qcom_cpu_clk_msm8996_driver_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;
	काष्ठा clk_hw_onecell_data *data;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	data = devm_kzalloc(dev, काष्ठा_size(data, hws, 2), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	regmap = devm_regmap_init_mmio(dev, base, &cpu_msm8996_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	ret = qcom_cpu_clk_msm8996_रेजिस्टर_clks(dev, regmap);
	अगर (ret)
		वापस ret;

	qcom_cpu_clk_msm8996_acd_init(base);

	data->hws[0] = &pwrcl_pmux.clkr.hw;
	data->hws[1] = &perfcl_pmux.clkr.hw;
	data->num = 2;

	वापस devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get, data);
पूर्ण

अटल पूर्णांक qcom_cpu_clk_msm8996_driver_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस qcom_cpu_clk_msm8996_unरेजिस्टर_clks();
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_cpu_clk_msm8996_match_table[] = अणु
	अणु .compatible = "qcom,msm8996-apcc" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_cpu_clk_msm8996_match_table);

अटल काष्ठा platक्रमm_driver qcom_cpu_clk_msm8996_driver = अणु
	.probe = qcom_cpu_clk_msm8996_driver_probe,
	.हटाओ = qcom_cpu_clk_msm8996_driver_हटाओ,
	.driver = अणु
		.name = "qcom-msm8996-apcc",
		.of_match_table = qcom_cpu_clk_msm8996_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qcom_cpu_clk_msm8996_driver);

MODULE_DESCRIPTION("QCOM MSM8996 CPU Clock Driver");
MODULE_LICENSE("GPL v2");
