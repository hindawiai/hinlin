<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics 2017
 * Author: Gabriel Fernandez <gabriel.fernandez@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/sपंचांग32h7-clks.h>

/* Reset Clock Control Registers */
#घोषणा RCC_CR		0x00
#घोषणा RCC_CFGR	0x10
#घोषणा RCC_D1CFGR	0x18
#घोषणा RCC_D2CFGR	0x1C
#घोषणा RCC_D3CFGR	0x20
#घोषणा RCC_PLLCKSELR	0x28
#घोषणा RCC_PLLCFGR	0x2C
#घोषणा RCC_PLL1DIVR	0x30
#घोषणा RCC_PLL1FRACR	0x34
#घोषणा RCC_PLL2DIVR	0x38
#घोषणा RCC_PLL2FRACR	0x3C
#घोषणा RCC_PLL3DIVR	0x40
#घोषणा RCC_PLL3FRACR	0x44
#घोषणा RCC_D1CCIPR	0x4C
#घोषणा RCC_D2CCIP1R	0x50
#घोषणा RCC_D2CCIP2R	0x54
#घोषणा RCC_D3CCIPR	0x58
#घोषणा RCC_BDCR	0x70
#घोषणा RCC_CSR		0x74
#घोषणा RCC_AHB3ENR	0xD4
#घोषणा RCC_AHB1ENR	0xD8
#घोषणा RCC_AHB2ENR	0xDC
#घोषणा RCC_AHB4ENR	0xE0
#घोषणा RCC_APB3ENR	0xE4
#घोषणा RCC_APB1LENR	0xE8
#घोषणा RCC_APB1HENR	0xEC
#घोषणा RCC_APB2ENR	0xF0
#घोषणा RCC_APB4ENR	0xF4

अटल DEFINE_SPINLOCK(sपंचांग32rcc_lock);

अटल व्योम __iomem *base;
अटल काष्ठा clk_hw **hws;

/* System घड़ी parent */
अटल स्थिर अक्षर * स्थिर sys_src[] = अणु
	"hsi_ck", "csi_ck", "hse_ck", "pll1_p" पूर्ण;

अटल स्थिर अक्षर * स्थिर tracein_src[] = अणु
	"hsi_ck", "csi_ck", "hse_ck", "pll1_r" पूर्ण;

अटल स्थिर अक्षर * स्थिर per_src[] = अणु
	"hsi_ker", "csi_ker", "hse_ck", "disabled" पूर्ण;

अटल स्थिर अक्षर * स्थिर pll_src[] = अणु
	"hsi_ck", "csi_ck", "hse_ck", "no clock" पूर्ण;

अटल स्थिर अक्षर * स्थिर sdmmc_src[] = अणु "pll1_q", "pll2_r" पूर्ण;

अटल स्थिर अक्षर * स्थिर dsi_src[] = अणु "ck_dsi_phy", "pll2_q" पूर्ण;

अटल स्थिर अक्षर * स्थिर qspi_src[] = अणु
	"hclk", "pll1_q", "pll2_r", "per_ck" पूर्ण;

अटल स्थिर अक्षर * स्थिर fmc_src[] = अणु
	"hclk", "pll1_q", "pll2_r", "per_ck" पूर्ण;

/* Kernel घड़ी parent */
अटल स्थिर अक्षर * स्थिर swp_src[] = अणु	"pclk1", "hsi_ker" पूर्ण;

अटल स्थिर अक्षर * स्थिर fdcan_src[] = अणु "hse_ck", "pll1_q", "pll2_q" पूर्ण;

अटल स्थिर अक्षर * स्थिर dfsdm1_src[] = अणु "pclk2", "sys_ck" पूर्ण;

अटल स्थिर अक्षर * स्थिर spdअगरrx_src[] = अणु
	"pll1_q", "pll2_r", "pll3_r", "hsi_ker" पूर्ण;

अटल स्थिर अक्षर *spi_src1[5] = अणु
	"pll1_q", "pll2_p", "pll3_p", शून्य, "per_ck" पूर्ण;

अटल स्थिर अक्षर * स्थिर spi_src2[] = अणु
	"pclk2", "pll2_q", "pll3_q", "hsi_ker", "csi_ker", "hse_ck" पूर्ण;

अटल स्थिर अक्षर * स्थिर spi_src3[] = अणु
	"pclk4", "pll2_q", "pll3_q", "hsi_ker", "csi_ker", "hse_ck" पूर्ण;

अटल स्थिर अक्षर * स्थिर lptim_src1[] = अणु
	"pclk1", "pll2_p", "pll3_r", "lse_ck", "lsi_ck", "per_ck" पूर्ण;

अटल स्थिर अक्षर * स्थिर lptim_src2[] = अणु
	"pclk4", "pll2_p", "pll3_r", "lse_ck", "lsi_ck", "per_ck" पूर्ण;

अटल स्थिर अक्षर * स्थिर cec_src[] = अणु"lse_ck", "lsi_ck", "csi_ker_div122" पूर्ण;

अटल स्थिर अक्षर * स्थिर usbotg_src[] = अणु"pll1_q", "pll3_q", "rc48_ck" पूर्ण;

/* i2c 1,2,3 src */
अटल स्थिर अक्षर * स्थिर i2c_src1[] = अणु
	"pclk1", "pll3_r", "hsi_ker", "csi_ker" पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c_src2[] = अणु
	"pclk4", "pll3_r", "hsi_ker", "csi_ker" पूर्ण;

अटल स्थिर अक्षर * स्थिर rng_src[] = अणु
	"rc48_ck", "pll1_q", "lse_ck", "lsi_ck" पूर्ण;

/* usart 1,6 src */
अटल स्थिर अक्षर * स्थिर usart_src1[] = अणु
	"pclk2", "pll2_q", "pll3_q", "hsi_ker", "csi_ker", "lse_ck" पूर्ण;

/* usart 2,3,4,5,7,8 src */
अटल स्थिर अक्षर * स्थिर usart_src2[] = अणु
	"pclk1", "pll2_q", "pll3_q", "hsi_ker", "csi_ker", "lse_ck" पूर्ण;

अटल स्थिर अक्षर *sai_src[5] = अणु
	"pll1_q", "pll2_p", "pll3_p", शून्य, "per_ck" पूर्ण;

अटल स्थिर अक्षर * स्थिर adc_src[] = अणु "pll2_p", "pll3_r", "per_ck" पूर्ण;

/* lptim 2,3,4,5 src */
अटल स्थिर अक्षर * स्थिर lpuart1_src[] = अणु
	"pclk3", "pll2_q", "pll3_q", "csi_ker", "lse_ck" पूर्ण;

अटल स्थिर अक्षर * स्थिर hrtim_src[] = अणु "tim2_ker", "d1cpre" पूर्ण;

/* RTC घड़ी parent */
अटल स्थिर अक्षर * स्थिर rtc_src[] = अणु "off", "lse_ck", "lsi_ck", "hse_1M" पूर्ण;

/* Micro-controller output घड़ी parent */
अटल स्थिर अक्षर * स्थिर mco_src1[] = अणु
	"hsi_ck", "lse_ck", "hse_ck", "pll1_q",	"rc48_ck" पूर्ण;

अटल स्थिर अक्षर * स्थिर mco_src2[] = अणु
	"sys_ck", "pll2_p", "hse_ck", "pll1_p", "csi_ck", "lsi_ck" पूर्ण;

/* LCD घड़ी */
अटल स्थिर अक्षर * स्थिर ltdc_src[] = अणु"pll3_r"पूर्ण;

/* Gate घड़ी with पढ़ोy bit and backup करोमुख्य management */
काष्ठा sपंचांग32_पढ़ोy_gate अणु
	काष्ठा	clk_gate gate;
	u8	bit_rdy;
पूर्ण;

#घोषणा to_पढ़ोy_gate_clk(_rgate) container_of(_rgate, काष्ठा sपंचांग32_पढ़ोy_gate,\
		gate)

#घोषणा RGATE_TIMEOUT 10000

अटल पूर्णांक पढ़ोy_gate_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gate *gate = to_clk_gate(hw);
	काष्ठा sपंचांग32_पढ़ोy_gate *rgate = to_पढ़ोy_gate_clk(gate);
	पूर्णांक bit_status;
	अचिन्हित पूर्णांक समयout = RGATE_TIMEOUT;

	अगर (clk_gate_ops.is_enabled(hw))
		वापस 0;

	clk_gate_ops.enable(hw);

	/* We can't use पढ़ोl_poll_समयout() because we can blocked अगर
	 * someone enables this घड़ी beक्रमe घड़ीsource changes.
	 * Only jअगरfies counter is available. Jअगरfies are incremented by
	 * पूर्णांकerruptions and enable op करोes not allow to be पूर्णांकerrupted.
	 */
	करो अणु
		bit_status = !(पढ़ोl(gate->reg) & BIT(rgate->bit_rdy));

		अगर (bit_status)
			udelay(100);

	पूर्ण जबतक (bit_status && --समयout);

	वापस bit_status;
पूर्ण

अटल व्योम पढ़ोy_gate_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gate *gate = to_clk_gate(hw);
	काष्ठा sपंचांग32_पढ़ोy_gate *rgate = to_पढ़ोy_gate_clk(gate);
	पूर्णांक bit_status;
	अचिन्हित पूर्णांक समयout = RGATE_TIMEOUT;

	अगर (!clk_gate_ops.is_enabled(hw))
		वापस;

	clk_gate_ops.disable(hw);

	करो अणु
		bit_status = !!(पढ़ोl(gate->reg) & BIT(rgate->bit_rdy));

		अगर (bit_status)
			udelay(100);

	पूर्ण जबतक (bit_status && --समयout);
पूर्ण

अटल स्थिर काष्ठा clk_ops पढ़ोy_gate_clk_ops = अणु
	.enable		= पढ़ोy_gate_clk_enable,
	.disable	= पढ़ोy_gate_clk_disable,
	.is_enabled	= clk_gate_is_enabled,
पूर्ण;

अटल काष्ठा clk_hw *clk_रेजिस्टर_पढ़ोy_gate(काष्ठा device *dev,
		स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		व्योम __iomem *reg, u8 bit_idx, u8 bit_rdy,
		अचिन्हित दीर्घ flags, spinlock_t *lock)
अणु
	काष्ठा sपंचांग32_पढ़ोy_gate *rgate;
	काष्ठा clk_init_data init = अणु शून्य पूर्ण;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	rgate = kzalloc(माप(*rgate), GFP_KERNEL);
	अगर (!rgate)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &पढ़ोy_gate_clk_ops;
	init.flags = flags;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	rgate->bit_rdy = bit_rdy;
	rgate->gate.lock = lock;
	rgate->gate.reg = reg;
	rgate->gate.bit_idx = bit_idx;
	rgate->gate.hw.init = &init;

	hw = &rgate->gate.hw;
	ret = clk_hw_रेजिस्टर(dev, hw);
	अगर (ret) अणु
		kमुक्त(rgate);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

काष्ठा gate_cfg अणु
	u32 offset;
	u8  bit_idx;
पूर्ण;

काष्ठा muxभाग_cfg अणु
	u32 offset;
	u8 shअगरt;
	u8 width;
पूर्ण;

काष्ठा composite_clk_cfg अणु
	काष्ठा gate_cfg *gate;
	काष्ठा muxभाग_cfg *mux;
	काष्ठा muxभाग_cfg *भाग;
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *parent_name;
	पूर्णांक num_parents;
	u32 flags;
पूर्ण;

काष्ठा composite_clk_gcfg_t अणु
	u8 flags;
	स्थिर काष्ठा clk_ops *ops;
पूर्ण;

/*
 * General config definition of a composite घड़ी (only घड़ी भागiser क्रम rate)
 */
काष्ठा composite_clk_gcfg अणु
	काष्ठा composite_clk_gcfg_t *mux;
	काष्ठा composite_clk_gcfg_t *भाग;
	काष्ठा composite_clk_gcfg_t *gate;
पूर्ण;

#घोषणा M_CFG_MUX(_mux_ops, _mux_flags)\
	.mux = &(काष्ठा composite_clk_gcfg_t) अणु _mux_flags, _mux_opsपूर्ण

#घोषणा M_CFG_DIV(_rate_ops, _rate_flags)\
	.भाग = &(काष्ठा composite_clk_gcfg_t) अणु_rate_flags, _rate_opsपूर्ण

#घोषणा M_CFG_GATE(_gate_ops, _gate_flags)\
	.gate = &(काष्ठा composite_clk_gcfg_t) अणु _gate_flags, _gate_opsपूर्ण

अटल काष्ठा clk_mux *_get_cmux(व्योम __iomem *reg, u8 shअगरt, u8 width,
		u32 flags, spinlock_t *lock)
अणु
	काष्ठा clk_mux *mux;

	mux = kzalloc(माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस ERR_PTR(-ENOMEM);

	mux->reg	= reg;
	mux->shअगरt	= shअगरt;
	mux->mask	= (1 << width) - 1;
	mux->flags	= flags;
	mux->lock	= lock;

	वापस mux;
पूर्ण

अटल काष्ठा clk_भागider *_get_cभाग(व्योम __iomem *reg, u8 shअगरt, u8 width,
		u32 flags, spinlock_t *lock)
अणु
	काष्ठा clk_भागider *भाग;

	भाग = kzalloc(माप(*भाग), GFP_KERNEL);

	अगर (!भाग)
		वापस ERR_PTR(-ENOMEM);

	भाग->reg   = reg;
	भाग->shअगरt = shअगरt;
	भाग->width = width;
	भाग->flags = flags;
	भाग->lock  = lock;

	वापस भाग;
पूर्ण

अटल काष्ठा clk_gate *_get_cgate(व्योम __iomem *reg, u8 bit_idx, u32 flags,
		spinlock_t *lock)
अणु
	काष्ठा clk_gate *gate;

	gate = kzalloc(माप(*gate), GFP_KERNEL);
	अगर (!gate)
		वापस ERR_PTR(-ENOMEM);

	gate->reg	= reg;
	gate->bit_idx	= bit_idx;
	gate->flags	= flags;
	gate->lock	= lock;

	वापस gate;
पूर्ण

काष्ठा composite_cfg अणु
	काष्ठा clk_hw *mux_hw;
	काष्ठा clk_hw *भाग_hw;
	काष्ठा clk_hw *gate_hw;

	स्थिर काष्ठा clk_ops *mux_ops;
	स्थिर काष्ठा clk_ops *भाग_ops;
	स्थिर काष्ठा clk_ops *gate_ops;
पूर्ण;

अटल व्योम get_cfg_composite_भाग(स्थिर काष्ठा composite_clk_gcfg *gcfg,
		स्थिर काष्ठा composite_clk_cfg *cfg,
		काष्ठा composite_cfg *composite, spinlock_t *lock)
अणु
	काष्ठा clk_mux     *mux = शून्य;
	काष्ठा clk_भागider *भाग = शून्य;
	काष्ठा clk_gate    *gate = शून्य;
	स्थिर काष्ठा clk_ops *mux_ops, *भाग_ops, *gate_ops;
	काष्ठा clk_hw *mux_hw;
	काष्ठा clk_hw *भाग_hw;
	काष्ठा clk_hw *gate_hw;

	mux_ops = भाग_ops = gate_ops = शून्य;
	mux_hw = भाग_hw = gate_hw = शून्य;

	अगर (gcfg->mux && cfg->mux) अणु
		mux = _get_cmux(base + cfg->mux->offset,
				cfg->mux->shअगरt,
				cfg->mux->width,
				gcfg->mux->flags, lock);

		अगर (!IS_ERR(mux)) अणु
			mux_hw = &mux->hw;
			mux_ops = gcfg->mux->ops ?
				  gcfg->mux->ops : &clk_mux_ops;
		पूर्ण
	पूर्ण

	अगर (gcfg->भाग && cfg->भाग) अणु
		भाग = _get_cभाग(base + cfg->भाग->offset,
				cfg->भाग->shअगरt,
				cfg->भाग->width,
				gcfg->भाग->flags, lock);

		अगर (!IS_ERR(भाग)) अणु
			भाग_hw = &भाग->hw;
			भाग_ops = gcfg->भाग->ops ?
				  gcfg->भाग->ops : &clk_भागider_ops;
		पूर्ण
	पूर्ण

	अगर (gcfg->gate && cfg->gate) अणु
		gate = _get_cgate(base + cfg->gate->offset,
				cfg->gate->bit_idx,
				gcfg->gate->flags, lock);

		अगर (!IS_ERR(gate)) अणु
			gate_hw = &gate->hw;
			gate_ops = gcfg->gate->ops ?
				   gcfg->gate->ops : &clk_gate_ops;
		पूर्ण
	पूर्ण

	composite->mux_hw = mux_hw;
	composite->mux_ops = mux_ops;

	composite->भाग_hw = भाग_hw;
	composite->भाग_ops = भाग_ops;

	composite->gate_hw = gate_hw;
	composite->gate_ops = gate_ops;
पूर्ण

/* Kernel Timer */
काष्ठा समयr_ker अणु
	u8 dppre_shअगरt;
	काष्ठा clk_hw hw;
	spinlock_t *lock;
पूर्ण;

#घोषणा to_समयr_ker(_hw) container_of(_hw, काष्ठा समयr_ker, hw)

अटल अचिन्हित दीर्घ समयr_ker_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा समयr_ker *clk_elem = to_समयr_ker(hw);
	u32 timpre;
	u32 dppre_shअगरt = clk_elem->dppre_shअगरt;
	u32 prescaler;
	u32 mul;

	timpre = (पढ़ोl(base + RCC_CFGR) >> 15) & 0x01;

	prescaler = (पढ़ोl(base + RCC_D2CFGR) >> dppre_shअगरt) & 0x03;

	mul = 2;

	अगर (prescaler < 4)
		mul = 1;

	अन्यथा अगर (timpre && prescaler > 4)
		mul = 4;

	वापस parent_rate * mul;
पूर्ण

अटल स्थिर काष्ठा clk_ops समयr_ker_ops = अणु
	.recalc_rate = समयr_ker_recalc_rate,
पूर्ण;

अटल काष्ठा clk_hw *clk_रेजिस्टर_sपंचांग32_समयr_ker(काष्ठा device *dev,
		स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		अचिन्हित दीर्घ flags,
		u8 dppre_shअगरt,
		spinlock_t *lock)
अणु
	काष्ठा समयr_ker *element;
	काष्ठा clk_init_data init;
	काष्ठा clk_hw *hw;
	पूर्णांक err;

	element = kzalloc(माप(*element), GFP_KERNEL);
	अगर (!element)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &समयr_ker_ops;
	init.flags = flags;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	element->hw.init = &init;
	element->lock = lock;
	element->dppre_shअगरt = dppre_shअगरt;

	hw = &element->hw;
	err = clk_hw_रेजिस्टर(dev, hw);

	अगर (err) अणु
		kमुक्त(element);
		वापस ERR_PTR(err);
	पूर्ण

	वापस hw;
पूर्ण

अटल स्थिर काष्ठा clk_भाग_प्रकारable d1cpre_भाग_प्रकारable[] = अणु
	अणु 0, 1 पूर्ण, अणु 1, 1 पूर्ण, अणु 2, 1 पूर्ण, अणु 3, 1पूर्ण,
	अणु 4, 1 पूर्ण, अणु 5, 1 पूर्ण, अणु 6, 1 पूर्ण, अणु 7, 1पूर्ण,
	अणु 8, 2 पूर्ण, अणु 9, 4 पूर्ण, अणु 10, 8 पूर्ण, अणु 11, 16 पूर्ण,
	अणु 12, 64 पूर्ण, अणु 13, 128 पूर्ण, अणु 14, 256 पूर्ण,
	अणु 15, 512 पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable ppre_भाग_प्रकारable[] = अणु
	अणु 0, 1 पूर्ण, अणु 1, 1 पूर्ण, अणु 2, 1 पूर्ण, अणु 3, 1पूर्ण,
	अणु 4, 2 पूर्ण, अणु 5, 4 पूर्ण, अणु 6, 8 पूर्ण, अणु 7, 16 पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल व्योम रेजिस्टर_core_and_bus_घड़ीs(व्योम)
अणु
	/* CORE AND BUS */
	hws[SYS_D1CPRE] = clk_hw_रेजिस्टर_भागider_table(शून्य, "d1cpre",
			"sys_ck", CLK_IGNORE_UNUSED, base + RCC_D1CFGR, 8, 4, 0,
			d1cpre_भाग_प्रकारable, &sपंचांग32rcc_lock);

	hws[HCLK] = clk_hw_रेजिस्टर_भागider_table(शून्य, "hclk", "d1cpre",
			CLK_IGNORE_UNUSED, base + RCC_D1CFGR, 0, 4, 0,
			d1cpre_भाग_प्रकारable, &sपंचांग32rcc_lock);

	/* D1 DOMAIN */
	/* * CPU Systick */
	hws[CPU_SYSTICK] = clk_hw_रेजिस्टर_fixed_factor(शून्य, "systick",
			"d1cpre", 0, 1, 8);

	/* * APB3 peripheral */
	hws[PCLK3] = clk_hw_रेजिस्टर_भागider_table(शून्य, "pclk3", "hclk", 0,
			base + RCC_D1CFGR, 4, 3, 0,
			ppre_भाग_प्रकारable, &sपंचांग32rcc_lock);

	/* D2 DOMAIN */
	/* * APB1 peripheral */
	hws[PCLK1] = clk_hw_रेजिस्टर_भागider_table(शून्य, "pclk1", "hclk", 0,
			base + RCC_D2CFGR, 4, 3, 0,
			ppre_भाग_प्रकारable, &sपंचांग32rcc_lock);

	/* Timers prescaler घड़ीs */
	clk_रेजिस्टर_sपंचांग32_समयr_ker(शून्य, "tim1_ker", "pclk1", 0,
			4, &sपंचांग32rcc_lock);

	/* * APB2 peripheral */
	hws[PCLK2] = clk_hw_रेजिस्टर_भागider_table(शून्य, "pclk2", "hclk", 0,
			base + RCC_D2CFGR, 8, 3, 0, ppre_भाग_प्रकारable,
			&sपंचांग32rcc_lock);

	clk_रेजिस्टर_sपंचांग32_समयr_ker(शून्य, "tim2_ker", "pclk2", 0, 8,
			&sपंचांग32rcc_lock);

	/* D3 DOMAIN */
	/* * APB4 peripheral */
	hws[PCLK4] = clk_hw_रेजिस्टर_भागider_table(शून्य, "pclk4", "hclk", 0,
			base + RCC_D3CFGR, 4, 3, 0,
			ppre_भाग_प्रकारable, &sपंचांग32rcc_lock);
पूर्ण

/* MUX घड़ी configuration */
काष्ठा sपंचांग32_mux_clk अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *parents;
	u8 num_parents;
	u32 offset;
	u8 shअगरt;
	u8 width;
	u32 flags;
पूर्ण;

#घोषणा M_MCLOCF(_name, _parents, _mux_offset, _mux_shअगरt, _mux_width, _flags)\
अणु\
	.name		= _name,\
	.parents	= _parents,\
	.num_parents	= ARRAY_SIZE(_parents),\
	.offset		= _mux_offset,\
	.shअगरt		= _mux_shअगरt,\
	.width		= _mux_width,\
	.flags		= _flags,\
पूर्ण

#घोषणा M_MCLOC(_name, _parents, _mux_offset, _mux_shअगरt, _mux_width)\
	M_MCLOCF(_name, _parents, _mux_offset, _mux_shअगरt, _mux_width, 0)\

अटल स्थिर काष्ठा sपंचांग32_mux_clk sपंचांग32_mclk[] __initस्थिर = अणु
	M_MCLOC("per_ck",	per_src,	RCC_D1CCIPR,	28, 3),
	M_MCLOC("pllsrc",	pll_src,	RCC_PLLCKSELR,	 0, 3),
	M_MCLOC("sys_ck",	sys_src,	RCC_CFGR,	 0, 3),
	M_MCLOC("tracein_ck",	tracein_src,	RCC_CFGR,	 0, 3),
पूर्ण;

/* Oscillary घड़ी configuration */
काष्ठा sपंचांग32_osc_clk अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent;
	u32 gate_offset;
	u8 bit_idx;
	u8 bit_rdy;
	u32 flags;
पूर्ण;

#घोषणा OSC_CLKF(_name, _parent, _gate_offset, _bit_idx, _bit_rdy, _flags)\
अणु\
	.name		= _name,\
	.parent		= _parent,\
	.gate_offset	= _gate_offset,\
	.bit_idx	= _bit_idx,\
	.bit_rdy	= _bit_rdy,\
	.flags		= _flags,\
पूर्ण

#घोषणा OSC_CLK(_name, _parent, _gate_offset, _bit_idx, _bit_rdy)\
	OSC_CLKF(_name, _parent, _gate_offset, _bit_idx, _bit_rdy, 0)

अटल स्थिर काष्ठा sपंचांग32_osc_clk sपंचांग32_oclk[] __initस्थिर = अणु
	OSC_CLKF("hsi_ck",  "hsidiv",   RCC_CR,   0,  2, CLK_IGNORE_UNUSED),
	OSC_CLKF("hsi_ker", "hsidiv",   RCC_CR,   1,  2, CLK_IGNORE_UNUSED),
	OSC_CLKF("csi_ck",  "clk-csi",  RCC_CR,   7,  8, CLK_IGNORE_UNUSED),
	OSC_CLKF("csi_ker", "clk-csi",  RCC_CR,   9,  8, CLK_IGNORE_UNUSED),
	OSC_CLKF("rc48_ck", "clk-rc48", RCC_CR,  12, 13, CLK_IGNORE_UNUSED),
	OSC_CLKF("lsi_ck",  "clk-lsi",  RCC_CSR,  0,  1, CLK_IGNORE_UNUSED),
पूर्ण;

/* PLL configuration */
काष्ठा st32h7_pll_cfg अणु
	u8 bit_idx;
	u32 offset_भागr;
	u8 bit_frac_en;
	u32 offset_frac;
	u8 भागm;
पूर्ण;

काष्ठा sपंचांग32_pll_data अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	अचिन्हित दीर्घ flags;
	स्थिर काष्ठा st32h7_pll_cfg *cfg;
पूर्ण;

अटल स्थिर काष्ठा st32h7_pll_cfg sपंचांग32h7_pll1 = अणु
	.bit_idx = 24,
	.offset_भागr = RCC_PLL1DIVR,
	.bit_frac_en = 0,
	.offset_frac = RCC_PLL1FRACR,
	.भागm = 4,
पूर्ण;

अटल स्थिर काष्ठा st32h7_pll_cfg sपंचांग32h7_pll2 = अणु
	.bit_idx = 26,
	.offset_भागr = RCC_PLL2DIVR,
	.bit_frac_en = 4,
	.offset_frac = RCC_PLL2FRACR,
	.भागm = 12,
पूर्ण;

अटल स्थिर काष्ठा st32h7_pll_cfg sपंचांग32h7_pll3 = अणु
	.bit_idx = 28,
	.offset_भागr = RCC_PLL3DIVR,
	.bit_frac_en = 8,
	.offset_frac = RCC_PLL3FRACR,
	.भागm = 20,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_pll_data sपंचांग32_pll[] = अणु
	अणु "vco1", "pllsrc", CLK_IGNORE_UNUSED, &sपंचांग32h7_pll1 पूर्ण,
	अणु "vco2", "pllsrc", 0, &sपंचांग32h7_pll2 पूर्ण,
	अणु "vco3", "pllsrc", 0, &sपंचांग32h7_pll3 पूर्ण,
पूर्ण;

काष्ठा sपंचांग32_fractional_भागider अणु
	व्योम __iomem	*mreg;
	u8		mshअगरt;
	u8		mwidth;
	u32		mmask;

	व्योम __iomem	*nreg;
	u8		nshअगरt;
	u8		nwidth;

	व्योम __iomem	*freg_status;
	u8		freg_bit;
	व्योम __iomem	*freg_value;
	u8		fshअगरt;
	u8		fwidth;

	u8		flags;
	काष्ठा clk_hw	hw;
	spinlock_t	*lock;
पूर्ण;

काष्ठा sपंचांग32_pll_obj अणु
	spinlock_t *lock;
	काष्ठा sपंचांग32_fractional_भागider भाग;
	काष्ठा sपंचांग32_पढ़ोy_gate rgate;
	काष्ठा clk_hw hw;
पूर्ण;

#घोषणा to_pll(_hw) container_of(_hw, काष्ठा sपंचांग32_pll_obj, hw)

अटल पूर्णांक pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा sपंचांग32_pll_obj *clk_elem = to_pll(hw);
	काष्ठा clk_hw *_hw = &clk_elem->rgate.gate.hw;

	__clk_hw_set_clk(_hw, hw);

	वापस पढ़ोy_gate_clk_ops.is_enabled(_hw);
पूर्ण

अटल पूर्णांक pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा sपंचांग32_pll_obj *clk_elem = to_pll(hw);
	काष्ठा clk_hw *_hw = &clk_elem->rgate.gate.hw;

	__clk_hw_set_clk(_hw, hw);

	वापस पढ़ोy_gate_clk_ops.enable(_hw);
पूर्ण

अटल व्योम pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा sपंचांग32_pll_obj *clk_elem = to_pll(hw);
	काष्ठा clk_hw *_hw = &clk_elem->rgate.gate.hw;

	__clk_hw_set_clk(_hw, hw);

	पढ़ोy_gate_clk_ops.disable(_hw);
पूर्ण

अटल पूर्णांक pll_frac_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा sपंचांग32_pll_obj *clk_elem = to_pll(hw);
	काष्ठा sपंचांग32_fractional_भागider *fd = &clk_elem->भाग;

	वापस (पढ़ोl(fd->freg_status) >> fd->freg_bit) & 0x01;
पूर्ण

अटल अचिन्हित दीर्घ pll_पढ़ो_frac(काष्ठा clk_hw *hw)
अणु
	काष्ठा sपंचांग32_pll_obj *clk_elem = to_pll(hw);
	काष्ठा sपंचांग32_fractional_भागider *fd = &clk_elem->भाग;

	वापस (पढ़ोl(fd->freg_value) >> fd->fshअगरt) &
		GENMASK(fd->fwidth - 1, 0);
पूर्ण

अटल अचिन्हित दीर्घ pll_fd_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sपंचांग32_pll_obj *clk_elem = to_pll(hw);
	काष्ठा sपंचांग32_fractional_भागider *fd = &clk_elem->भाग;
	अचिन्हित दीर्घ m, n;
	u32 val, mask;
	u64 rate, rate1 = 0;

	val = पढ़ोl(fd->mreg);
	mask = GENMASK(fd->mwidth - 1, 0) << fd->mshअगरt;
	m = (val & mask) >> fd->mshअगरt;

	val = पढ़ोl(fd->nreg);
	mask = GENMASK(fd->nwidth - 1, 0) << fd->nshअगरt;
	n = ((val & mask) >> fd->nshअगरt) + 1;

	अगर (!n || !m)
		वापस parent_rate;

	rate = (u64)parent_rate * n;
	करो_भाग(rate, m);

	अगर (pll_frac_is_enabled(hw)) अणु
		val = pll_पढ़ो_frac(hw);
		rate1 = (u64)parent_rate * (u64)val;
		करो_भाग(rate1, (m * 8191));
	पूर्ण

	वापस rate + rate1;
पूर्ण

अटल स्थिर काष्ठा clk_ops pll_ops = अणु
	.enable		= pll_enable,
	.disable	= pll_disable,
	.is_enabled	= pll_is_enabled,
	.recalc_rate	= pll_fd_recalc_rate,
पूर्ण;

अटल काष्ठा clk_hw *clk_रेजिस्टर_sपंचांग32_pll(काष्ठा device *dev,
		स्थिर अक्षर *name,
		स्थिर अक्षर *parent,
		अचिन्हित दीर्घ flags,
		स्थिर काष्ठा st32h7_pll_cfg *cfg,
		spinlock_t *lock)
अणु
	काष्ठा sपंचांग32_pll_obj *pll;
	काष्ठा clk_init_data init = अणु शून्य पूर्ण;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;
	काष्ठा sपंचांग32_fractional_भागider *भाग = शून्य;
	काष्ठा sपंचांग32_पढ़ोy_gate *rgate;

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &pll_ops;
	init.flags = flags;
	init.parent_names = &parent;
	init.num_parents = 1;
	pll->hw.init = &init;

	hw = &pll->hw;
	rgate = &pll->rgate;

	rgate->bit_rdy = cfg->bit_idx + 1;
	rgate->gate.lock = lock;
	rgate->gate.reg = base + RCC_CR;
	rgate->gate.bit_idx = cfg->bit_idx;

	भाग = &pll->भाग;
	भाग->flags = 0;
	भाग->mreg = base + RCC_PLLCKSELR;
	भाग->mshअगरt = cfg->भागm;
	भाग->mwidth = 6;
	भाग->nreg = base +  cfg->offset_भागr;
	भाग->nshअगरt = 0;
	भाग->nwidth = 9;

	भाग->freg_status = base + RCC_PLLCFGR;
	भाग->freg_bit = cfg->bit_frac_en;
	भाग->freg_value = base +  cfg->offset_frac;
	भाग->fshअगरt = 3;
	भाग->fwidth = 13;

	भाग->lock = lock;

	ret = clk_hw_रेजिस्टर(dev, hw);
	अगर (ret) अणु
		kमुक्त(pll);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

/* ODF CLOCKS */
अटल अचिन्हित दीर्घ odf_भागider_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	वापस clk_भागider_ops.recalc_rate(hw, parent_rate);
पूर्ण

अटल दीर्घ odf_भागider_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ *prate)
अणु
	वापस clk_भागider_ops.round_rate(hw, rate, prate);
पूर्ण

अटल पूर्णांक odf_भागider_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_hw *hwp;
	पूर्णांक pll_status;
	पूर्णांक ret;

	hwp = clk_hw_get_parent(hw);

	pll_status = pll_is_enabled(hwp);

	अगर (pll_status)
		pll_disable(hwp);

	ret = clk_भागider_ops.set_rate(hw, rate, parent_rate);

	अगर (pll_status)
		pll_enable(hwp);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops odf_भागider_ops = अणु
	.recalc_rate	= odf_भागider_recalc_rate,
	.round_rate	= odf_भागider_round_rate,
	.set_rate	= odf_भागider_set_rate,
पूर्ण;

अटल पूर्णांक odf_gate_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw *hwp;
	पूर्णांक pll_status;
	पूर्णांक ret;

	अगर (clk_gate_ops.is_enabled(hw))
		वापस 0;

	hwp = clk_hw_get_parent(hw);

	pll_status = pll_is_enabled(hwp);

	अगर (pll_status)
		pll_disable(hwp);

	ret = clk_gate_ops.enable(hw);

	अगर (pll_status)
		pll_enable(hwp);

	वापस ret;
पूर्ण

अटल व्योम odf_gate_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw *hwp;
	पूर्णांक pll_status;

	अगर (!clk_gate_ops.is_enabled(hw))
		वापस;

	hwp = clk_hw_get_parent(hw);

	pll_status = pll_is_enabled(hwp);

	अगर (pll_status)
		pll_disable(hwp);

	clk_gate_ops.disable(hw);

	अगर (pll_status)
		pll_enable(hwp);
पूर्ण

अटल स्थिर काष्ठा clk_ops odf_gate_ops = अणु
	.enable		= odf_gate_enable,
	.disable	= odf_gate_disable,
	.is_enabled	= clk_gate_is_enabled,
पूर्ण;

अटल काष्ठा composite_clk_gcfg odf_clk_gcfg = अणु
	M_CFG_DIV(&odf_भागider_ops, 0),
	M_CFG_GATE(&odf_gate_ops, 0),
पूर्ण;

#घोषणा M_ODF_F(_name, _parent, _gate_offset,  _bit_idx, _rate_offset,\
		_rate_shअगरt, _rate_width, _flags)\
अणु\
	.mux = शून्य,\
	.भाग = &(काष्ठा muxभाग_cfg) अणु_rate_offset, _rate_shअगरt, _rate_widthपूर्ण,\
	.gate = &(काष्ठा gate_cfg) अणु_gate_offset, _bit_idx पूर्ण,\
	.name = _name,\
	.parent_name = &(स्थिर अक्षर *) अणु_parentपूर्ण,\
	.num_parents = 1,\
	.flags = _flags,\
पूर्ण

#घोषणा M_ODF(_name, _parent, _gate_offset,  _bit_idx, _rate_offset,\
		_rate_shअगरt, _rate_width)\
M_ODF_F(_name, _parent, _gate_offset,  _bit_idx, _rate_offset,\
		_rate_shअगरt, _rate_width, 0)\

अटल स्थिर काष्ठा composite_clk_cfg sपंचांग32_odf[3][3] = अणु
	अणु
		M_ODF_F("pll1_p", "vco1", RCC_PLLCFGR, 16, RCC_PLL1DIVR,  9, 7,
				CLK_IGNORE_UNUSED),
		M_ODF_F("pll1_q", "vco1", RCC_PLLCFGR, 17, RCC_PLL1DIVR, 16, 7,
				CLK_IGNORE_UNUSED),
		M_ODF_F("pll1_r", "vco1", RCC_PLLCFGR, 18, RCC_PLL1DIVR, 24, 7,
				CLK_IGNORE_UNUSED),
	पूर्ण,

	अणु
		M_ODF("pll2_p", "vco2", RCC_PLLCFGR, 19, RCC_PLL2DIVR,  9, 7),
		M_ODF("pll2_q", "vco2", RCC_PLLCFGR, 20, RCC_PLL2DIVR, 16, 7),
		M_ODF("pll2_r", "vco2", RCC_PLLCFGR, 21, RCC_PLL2DIVR, 24, 7),
	पूर्ण,
	अणु
		M_ODF("pll3_p", "vco3", RCC_PLLCFGR, 22, RCC_PLL3DIVR,  9, 7),
		M_ODF("pll3_q", "vco3", RCC_PLLCFGR, 23, RCC_PLL3DIVR, 16, 7),
		M_ODF("pll3_r", "vco3", RCC_PLLCFGR, 24, RCC_PLL3DIVR, 24, 7),
	पूर्ण
पूर्ण;

/* PERIF CLOCKS */
काष्ठा pclk_t अणु
	u32 gate_offset;
	u8 bit_idx;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent;
	u32 flags;
पूर्ण;

#घोषणा PER_CLKF(_gate_offset, _bit_idx, _name, _parent, _flags)\
अणु\
	.gate_offset	= _gate_offset,\
	.bit_idx	= _bit_idx,\
	.name		= _name,\
	.parent		= _parent,\
	.flags		= _flags,\
पूर्ण

#घोषणा PER_CLK(_gate_offset, _bit_idx, _name, _parent)\
	PER_CLKF(_gate_offset, _bit_idx, _name, _parent, 0)

अटल स्थिर काष्ठा pclk_t pclk[] = अणु
	PER_CLK(RCC_AHB3ENR, 31, "d1sram1", "hclk"),
	PER_CLK(RCC_AHB3ENR, 30, "itcm", "hclk"),
	PER_CLK(RCC_AHB3ENR, 29, "dtcm2", "hclk"),
	PER_CLK(RCC_AHB3ENR, 28, "dtcm1", "hclk"),
	PER_CLK(RCC_AHB3ENR, 8, "flitf", "hclk"),
	PER_CLK(RCC_AHB3ENR, 5, "jpgdec", "hclk"),
	PER_CLK(RCC_AHB3ENR, 4, "dma2d", "hclk"),
	PER_CLK(RCC_AHB3ENR, 0, "mdma", "hclk"),
	PER_CLK(RCC_AHB1ENR, 28, "usb2ulpi", "hclk"),
	PER_CLK(RCC_AHB1ENR, 26, "usb1ulpi", "hclk"),
	PER_CLK(RCC_AHB1ENR, 17, "eth1rx", "hclk"),
	PER_CLK(RCC_AHB1ENR, 16, "eth1tx", "hclk"),
	PER_CLK(RCC_AHB1ENR, 15, "eth1mac", "hclk"),
	PER_CLK(RCC_AHB1ENR, 14, "art", "hclk"),
	PER_CLK(RCC_AHB1ENR, 1, "dma2", "hclk"),
	PER_CLK(RCC_AHB1ENR, 0, "dma1", "hclk"),
	PER_CLK(RCC_AHB2ENR, 31, "d2sram3", "hclk"),
	PER_CLK(RCC_AHB2ENR, 30, "d2sram2", "hclk"),
	PER_CLK(RCC_AHB2ENR, 29, "d2sram1", "hclk"),
	PER_CLK(RCC_AHB2ENR, 5, "hash", "hclk"),
	PER_CLK(RCC_AHB2ENR, 4, "crypt", "hclk"),
	PER_CLK(RCC_AHB2ENR, 0, "camitf", "hclk"),
	PER_CLK(RCC_AHB4ENR, 28, "bkpram", "hclk"),
	PER_CLK(RCC_AHB4ENR, 25, "hsem", "hclk"),
	PER_CLK(RCC_AHB4ENR, 21, "bdma", "hclk"),
	PER_CLK(RCC_AHB4ENR, 19, "crc", "hclk"),
	PER_CLK(RCC_AHB4ENR, 10, "gpiok", "hclk"),
	PER_CLK(RCC_AHB4ENR, 9, "gpioj", "hclk"),
	PER_CLK(RCC_AHB4ENR, 8, "gpioi", "hclk"),
	PER_CLK(RCC_AHB4ENR, 7, "gpioh", "hclk"),
	PER_CLK(RCC_AHB4ENR, 6, "gpiog", "hclk"),
	PER_CLK(RCC_AHB4ENR, 5, "gpiof", "hclk"),
	PER_CLK(RCC_AHB4ENR, 4, "gpioe", "hclk"),
	PER_CLK(RCC_AHB4ENR, 3, "gpiod", "hclk"),
	PER_CLK(RCC_AHB4ENR, 2, "gpioc", "hclk"),
	PER_CLK(RCC_AHB4ENR, 1, "gpiob", "hclk"),
	PER_CLK(RCC_AHB4ENR, 0, "gpioa", "hclk"),
	PER_CLK(RCC_APB3ENR, 6, "wwdg1", "pclk3"),
	PER_CLK(RCC_APB1LENR, 29, "dac12", "pclk1"),
	PER_CLK(RCC_APB1LENR, 11, "wwdg2", "pclk1"),
	PER_CLK(RCC_APB1LENR, 8, "tim14", "tim1_ker"),
	PER_CLK(RCC_APB1LENR, 7, "tim13", "tim1_ker"),
	PER_CLK(RCC_APB1LENR, 6, "tim12", "tim1_ker"),
	PER_CLK(RCC_APB1LENR, 5, "tim7", "tim1_ker"),
	PER_CLK(RCC_APB1LENR, 4, "tim6", "tim1_ker"),
	PER_CLK(RCC_APB1LENR, 3, "tim5", "tim1_ker"),
	PER_CLK(RCC_APB1LENR, 2, "tim4", "tim1_ker"),
	PER_CLK(RCC_APB1LENR, 1, "tim3", "tim1_ker"),
	PER_CLK(RCC_APB1LENR, 0, "tim2", "tim1_ker"),
	PER_CLK(RCC_APB1HENR, 5, "mdios", "pclk1"),
	PER_CLK(RCC_APB1HENR, 4, "opamp", "pclk1"),
	PER_CLK(RCC_APB1HENR, 1, "crs", "pclk1"),
	PER_CLK(RCC_APB2ENR, 18, "tim17", "tim2_ker"),
	PER_CLK(RCC_APB2ENR, 17, "tim16", "tim2_ker"),
	PER_CLK(RCC_APB2ENR, 16, "tim15", "tim2_ker"),
	PER_CLK(RCC_APB2ENR, 1, "tim8", "tim2_ker"),
	PER_CLK(RCC_APB2ENR, 0, "tim1", "tim2_ker"),
	PER_CLK(RCC_APB4ENR, 26, "tmpsens", "pclk4"),
	PER_CLK(RCC_APB4ENR, 16, "rtcapb", "pclk4"),
	PER_CLK(RCC_APB4ENR, 15, "vref", "pclk4"),
	PER_CLK(RCC_APB4ENR, 14, "comp12", "pclk4"),
	PER_CLK(RCC_APB4ENR, 1, "syscfg", "pclk4"),
पूर्ण;

/* KERNEL CLOCKS */
#घोषणा KER_CLKF(_gate_offset, _bit_idx,\
		_mux_offset, _mux_shअगरt, _mux_width,\
		_name, _parent_name,\
		_flags) \
अणु \
	.gate = &(काष्ठा gate_cfg) अणु_gate_offset, _bit_idxपूर्ण,\
	.mux = &(काष्ठा muxभाग_cfg) अणु_mux_offset, _mux_shअगरt, _mux_width पूर्ण,\
	.name = _name, \
	.parent_name = _parent_name, \
	.num_parents = ARRAY_SIZE(_parent_name),\
	.flags = _flags,\
पूर्ण

#घोषणा KER_CLK(_gate_offset, _bit_idx, _mux_offset, _mux_shअगरt, _mux_width,\
		_name, _parent_name) \
KER_CLKF(_gate_offset, _bit_idx, _mux_offset, _mux_shअगरt, _mux_width,\
		_name, _parent_name, 0)\

#घोषणा KER_CLKF_NOMUX(_gate_offset, _bit_idx,\
		_name, _parent_name,\
		_flags) \
अणु \
	.gate = &(काष्ठा gate_cfg) अणु_gate_offset, _bit_idxपूर्ण,\
	.mux = शून्य,\
	.name = _name, \
	.parent_name = _parent_name, \
	.num_parents = 1,\
	.flags = _flags,\
पूर्ण

अटल स्थिर काष्ठा composite_clk_cfg kclk[] = अणु
	KER_CLK(RCC_AHB3ENR,  16, RCC_D1CCIPR,	16, 1, "sdmmc1", sdmmc_src),
	KER_CLKF(RCC_AHB3ENR, 14, RCC_D1CCIPR,	 4, 2, "quadspi", qspi_src,
			CLK_IGNORE_UNUSED),
	KER_CLKF(RCC_AHB3ENR, 12, RCC_D1CCIPR,	 0, 2, "fmc", fmc_src,
			CLK_IGNORE_UNUSED),
	KER_CLK(RCC_AHB1ENR,  27, RCC_D2CCIP2R,	20, 2, "usb2otg", usbotg_src),
	KER_CLK(RCC_AHB1ENR,  25, RCC_D2CCIP2R, 20, 2, "usb1otg", usbotg_src),
	KER_CLK(RCC_AHB1ENR,   5, RCC_D3CCIPR,	16, 2, "adc12", adc_src),
	KER_CLK(RCC_AHB2ENR,   9, RCC_D1CCIPR,	16, 1, "sdmmc2", sdmmc_src),
	KER_CLK(RCC_AHB2ENR,   6, RCC_D2CCIP2R,	 8, 2, "rng", rng_src),
	KER_CLK(RCC_AHB4ENR,  24, RCC_D3CCIPR,  16, 2, "adc3", adc_src),
	KER_CLKF(RCC_APB3ENR,   4, RCC_D1CCIPR,	 8, 1, "dsi", dsi_src,
			CLK_SET_RATE_PARENT),
	KER_CLKF_NOMUX(RCC_APB3ENR, 3, "ltdc", ltdc_src, CLK_SET_RATE_PARENT),
	KER_CLK(RCC_APB1LENR, 31, RCC_D2CCIP2R,  0, 3, "usart8", usart_src2),
	KER_CLK(RCC_APB1LENR, 30, RCC_D2CCIP2R,  0, 3, "usart7", usart_src2),
	KER_CLK(RCC_APB1LENR, 27, RCC_D2CCIP2R, 22, 2, "hdmicec", cec_src),
	KER_CLK(RCC_APB1LENR, 23, RCC_D2CCIP2R, 12, 2, "i2c3", i2c_src1),
	KER_CLK(RCC_APB1LENR, 22, RCC_D2CCIP2R, 12, 2, "i2c2", i2c_src1),
	KER_CLK(RCC_APB1LENR, 21, RCC_D2CCIP2R, 12, 2, "i2c1", i2c_src1),
	KER_CLK(RCC_APB1LENR, 20, RCC_D2CCIP2R,	 0, 3, "uart5", usart_src2),
	KER_CLK(RCC_APB1LENR, 19, RCC_D2CCIP2R,  0, 3, "uart4", usart_src2),
	KER_CLK(RCC_APB1LENR, 18, RCC_D2CCIP2R,  0, 3, "usart3", usart_src2),
	KER_CLK(RCC_APB1LENR, 17, RCC_D2CCIP2R,  0, 3, "usart2", usart_src2),
	KER_CLK(RCC_APB1LENR, 16, RCC_D2CCIP1R, 20, 2, "spdifrx", spdअगरrx_src),
	KER_CLK(RCC_APB1LENR, 15, RCC_D2CCIP1R, 16, 3, "spi3", spi_src1),
	KER_CLK(RCC_APB1LENR, 14, RCC_D2CCIP1R, 16, 3, "spi2", spi_src1),
	KER_CLK(RCC_APB1LENR,  9, RCC_D2CCIP2R, 28, 3, "lptim1", lptim_src1),
	KER_CLK(RCC_APB1HENR,  8, RCC_D2CCIP1R, 28, 2, "fdcan", fdcan_src),
	KER_CLK(RCC_APB1HENR,  2, RCC_D2CCIP1R, 31, 1, "swp", swp_src),
	KER_CLK(RCC_APB2ENR,  29, RCC_CFGR,	14, 1, "hrtim", hrtim_src),
	KER_CLK(RCC_APB2ENR,  28, RCC_D2CCIP1R, 24, 1, "dfsdm1", dfsdm1_src),
	KER_CLKF(RCC_APB2ENR,  24, RCC_D2CCIP1R,  6, 3, "sai3", sai_src,
		 CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT),
	KER_CLKF(RCC_APB2ENR,  23, RCC_D2CCIP1R,  6, 3, "sai2", sai_src,
		 CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT),
	KER_CLKF(RCC_APB2ENR,  22, RCC_D2CCIP1R,  0, 3, "sai1", sai_src,
		 CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT),
	KER_CLK(RCC_APB2ENR,  20, RCC_D2CCIP1R, 16, 3, "spi5", spi_src2),
	KER_CLK(RCC_APB2ENR,  13, RCC_D2CCIP1R, 16, 3, "spi4", spi_src2),
	KER_CLK(RCC_APB2ENR,  12, RCC_D2CCIP1R, 16, 3, "spi1", spi_src1),
	KER_CLK(RCC_APB2ENR,   5, RCC_D2CCIP2R,  3, 3, "usart6", usart_src1),
	KER_CLK(RCC_APB2ENR,   4, RCC_D2CCIP2R,  3, 3, "usart1", usart_src1),
	KER_CLK(RCC_APB4ENR,  21, RCC_D3CCIPR,	24, 3, "sai4b", sai_src),
	KER_CLK(RCC_APB4ENR,  21, RCC_D3CCIPR,	21, 3, "sai4a", sai_src),
	KER_CLK(RCC_APB4ENR,  12, RCC_D3CCIPR,	13, 3, "lptim5", lptim_src2),
	KER_CLK(RCC_APB4ENR,  11, RCC_D3CCIPR,	13, 3, "lptim4", lptim_src2),
	KER_CLK(RCC_APB4ENR,  10, RCC_D3CCIPR,	13, 3, "lptim3", lptim_src2),
	KER_CLK(RCC_APB4ENR,   9, RCC_D3CCIPR,	10, 3, "lptim2", lptim_src2),
	KER_CLK(RCC_APB4ENR,   7, RCC_D3CCIPR,	 8, 2, "i2c4", i2c_src2),
	KER_CLK(RCC_APB4ENR,   5, RCC_D3CCIPR,	28, 3, "spi6", spi_src3),
	KER_CLK(RCC_APB4ENR,   3, RCC_D3CCIPR,	 0, 3, "lpuart1", lpuart1_src),
पूर्ण;

अटल काष्ठा composite_clk_gcfg kernel_clk_cfg = अणु
	M_CFG_MUX(शून्य, 0),
	M_CFG_GATE(शून्य, 0),
पूर्ण;

/* RTC घड़ी */
/*
 * RTC & LSE रेजिस्टरs are रक्षित against parasitic ग_लिखो access.
 * PWR_CR_DBP bit must be set to enable ग_लिखो access to RTC रेजिस्टरs.
 */
/* STM32_PWR_CR */
#घोषणा PWR_CR				0x00
/* STM32_PWR_CR bit field */
#घोषणा PWR_CR_DBP			BIT(8)

अटल काष्ठा composite_clk_gcfg rtc_clk_cfg = अणु
	M_CFG_MUX(शून्य, 0),
	M_CFG_GATE(शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा composite_clk_cfg rtc_clk =
	KER_CLK(RCC_BDCR, 15, RCC_BDCR, 8, 2, "rtc_ck", rtc_src);

/* Micro-controller output घड़ी */
अटल काष्ठा composite_clk_gcfg mco_clk_cfg = अणु
	M_CFG_MUX(शून्य, 0),
	M_CFG_DIV(शून्य,	CLK_DIVIDER_ONE_BASED | CLK_DIVIDER_ALLOW_ZERO),
पूर्ण;

#घोषणा M_MCO_F(_name, _parents, _mux_offset,  _mux_shअगरt, _mux_width,\
		_rate_offset, _rate_shअगरt, _rate_width,\
		_flags)\
अणु\
	.mux = &(काष्ठा muxभाग_cfg) अणु_mux_offset, _mux_shअगरt, _mux_width पूर्ण,\
	.भाग = &(काष्ठा muxभाग_cfg) अणु_rate_offset, _rate_shअगरt, _rate_widthपूर्ण,\
	.gate = शून्य,\
	.name = _name,\
	.parent_name = _parents,\
	.num_parents = ARRAY_SIZE(_parents),\
	.flags = _flags,\
पूर्ण

अटल स्थिर काष्ठा composite_clk_cfg mco_clk[] = अणु
	M_MCO_F("mco1", mco_src1, RCC_CFGR, 22, 4, RCC_CFGR, 18, 4, 0),
	M_MCO_F("mco2", mco_src2, RCC_CFGR, 29, 3, RCC_CFGR, 25, 4, 0),
पूर्ण;

अटल व्योम __init sपंचांग32h7_rcc_init(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw_onecell_data *clk_data;
	काष्ठा composite_cfg c_cfg;
	पूर्णांक n;
	स्थिर अक्षर *hse_clk, *lse_clk, *i2s_clk;
	काष्ठा regmap *pdrm;

	clk_data = kzalloc(काष्ठा_size(clk_data, hws, STM32H7_MAX_CLKS),
			   GFP_KERNEL);
	अगर (!clk_data)
		वापस;

	clk_data->num = STM32H7_MAX_CLKS;

	hws = clk_data->hws;

	क्रम (n = 0; n < STM32H7_MAX_CLKS; n++)
		hws[n] = ERR_PTR(-ENOENT);

	/* get RCC base @ from DT */
	base = of_iomap(np, 0);
	अगर (!base) अणु
		pr_err("%pOFn: unable to map resource", np);
		जाओ err_मुक्त_clks;
	पूर्ण

	pdrm = syscon_regmap_lookup_by_phandle(np, "st,syscfg");
	अगर (IS_ERR(pdrm))
		pr_warn("%s: Unable to get syscfg\n", __func__);
	अन्यथा
		/* In any हाल disable backup करोमुख्य ग_लिखो protection
		 * and will never be enabled.
		 * Needed by LSE & RTC घड़ीs.
		 */
		regmap_update_bits(pdrm, PWR_CR, PWR_CR_DBP, PWR_CR_DBP);

	/* Put parent names from DT */
	hse_clk = of_clk_get_parent_name(np, 0);
	lse_clk = of_clk_get_parent_name(np, 1);
	i2s_clk = of_clk_get_parent_name(np, 2);

	sai_src[3] = i2s_clk;
	spi_src1[3] = i2s_clk;

	/* Register Internal oscillators */
	clk_hw_रेजिस्टर_fixed_rate(शून्य, "clk-hsi", शून्य, 0, 64000000);
	clk_hw_रेजिस्टर_fixed_rate(शून्य, "clk-csi", शून्य, 0, 4000000);
	clk_hw_रेजिस्टर_fixed_rate(शून्य, "clk-lsi", शून्य, 0, 32000);
	clk_hw_रेजिस्टर_fixed_rate(शून्य, "clk-rc48", शून्य, 0, 48000);

	/* This घड़ी is coming from outside. Frequencies unknown */
	hws[CK_DSI_PHY] = clk_hw_रेजिस्टर_fixed_rate(शून्य, "ck_dsi_phy", शून्य,
			0, 0);

	hws[HSI_DIV] = clk_hw_रेजिस्टर_भागider(शून्य, "hsidiv", "clk-hsi", 0,
			base + RCC_CR, 3, 2, CLK_DIVIDER_POWER_OF_TWO,
			&sपंचांग32rcc_lock);

	hws[HSE_1M] = clk_hw_रेजिस्टर_भागider(शून्य, "hse_1M", "hse_ck",	0,
			base + RCC_CFGR, 8, 6, CLK_DIVIDER_ONE_BASED |
			CLK_DIVIDER_ALLOW_ZERO,
			&sपंचांग32rcc_lock);

	/* Mux प्रणाली घड़ीs */
	क्रम (n = 0; n < ARRAY_SIZE(sपंचांग32_mclk); n++)
		hws[MCLK_BANK + n] = clk_hw_रेजिस्टर_mux(शून्य,
				sपंचांग32_mclk[n].name,
				sपंचांग32_mclk[n].parents,
				sपंचांग32_mclk[n].num_parents,
				sपंचांग32_mclk[n].flags,
				sपंचांग32_mclk[n].offset + base,
				sपंचांग32_mclk[n].shअगरt,
				sपंचांग32_mclk[n].width,
				0,
				&sपंचांग32rcc_lock);

	रेजिस्टर_core_and_bus_घड़ीs();

	/* Oscillary घड़ीs */
	क्रम (n = 0; n < ARRAY_SIZE(sपंचांग32_oclk); n++)
		hws[OSC_BANK + n] = clk_रेजिस्टर_पढ़ोy_gate(शून्य,
				sपंचांग32_oclk[n].name,
				sपंचांग32_oclk[n].parent,
				sपंचांग32_oclk[n].gate_offset + base,
				sपंचांग32_oclk[n].bit_idx,
				sपंचांग32_oclk[n].bit_rdy,
				sपंचांग32_oclk[n].flags,
				&sपंचांग32rcc_lock);

	hws[HSE_CK] = clk_रेजिस्टर_पढ़ोy_gate(शून्य,
				"hse_ck",
				hse_clk,
				RCC_CR + base,
				16, 17,
				0,
				&sपंचांग32rcc_lock);

	hws[LSE_CK] = clk_रेजिस्टर_पढ़ोy_gate(शून्य,
				"lse_ck",
				lse_clk,
				RCC_BDCR + base,
				0, 1,
				0,
				&sपंचांग32rcc_lock);

	hws[CSI_KER_DIV122 + n] = clk_hw_रेजिस्टर_fixed_factor(शून्य,
			"csi_ker_div122", "csi_ker", 0, 1, 122);

	/* PLLs */
	क्रम (n = 0; n < ARRAY_SIZE(sपंचांग32_pll); n++) अणु
		पूर्णांक odf;

		/* Register the VCO */
		clk_रेजिस्टर_sपंचांग32_pll(शून्य, sपंचांग32_pll[n].name,
				sपंचांग32_pll[n].parent_name, sपंचांग32_pll[n].flags,
				sपंचांग32_pll[n].cfg,
				&sपंचांग32rcc_lock);

		/* Register the 3 output भागiders */
		क्रम (odf = 0; odf < 3; odf++) अणु
			पूर्णांक idx = n * 3 + odf;

			get_cfg_composite_भाग(&odf_clk_gcfg, &sपंचांग32_odf[n][odf],
					&c_cfg,	&sपंचांग32rcc_lock);

			hws[ODF_BANK + idx] = clk_hw_रेजिस्टर_composite(शून्य,
					sपंचांग32_odf[n][odf].name,
					sपंचांग32_odf[n][odf].parent_name,
					sपंचांग32_odf[n][odf].num_parents,
					c_cfg.mux_hw, c_cfg.mux_ops,
					c_cfg.भाग_hw, c_cfg.भाग_ops,
					c_cfg.gate_hw, c_cfg.gate_ops,
					sपंचांग32_odf[n][odf].flags);
		पूर्ण
	पूर्ण

	/* Peripheral घड़ीs */
	क्रम (n = 0; n < ARRAY_SIZE(pclk); n++)
		hws[PERIF_BANK + n] = clk_hw_रेजिस्टर_gate(शून्य, pclk[n].name,
				pclk[n].parent,
				pclk[n].flags, base + pclk[n].gate_offset,
				pclk[n].bit_idx, pclk[n].flags, &sपंचांग32rcc_lock);

	/* Kernel घड़ीs */
	क्रम (n = 0; n < ARRAY_SIZE(kclk); n++) अणु
		get_cfg_composite_भाग(&kernel_clk_cfg, &kclk[n], &c_cfg,
				&sपंचांग32rcc_lock);

		hws[KERN_BANK + n] = clk_hw_रेजिस्टर_composite(शून्य,
				kclk[n].name,
				kclk[n].parent_name,
				kclk[n].num_parents,
				c_cfg.mux_hw, c_cfg.mux_ops,
				c_cfg.भाग_hw, c_cfg.भाग_ops,
				c_cfg.gate_hw, c_cfg.gate_ops,
				kclk[n].flags);
	पूर्ण

	/* RTC घड़ी (शेष state is off) */
	clk_hw_रेजिस्टर_fixed_rate(शून्य, "off", शून्य, 0, 0);

	get_cfg_composite_भाग(&rtc_clk_cfg, &rtc_clk, &c_cfg, &sपंचांग32rcc_lock);

	hws[RTC_CK] = clk_hw_रेजिस्टर_composite(शून्य,
			rtc_clk.name,
			rtc_clk.parent_name,
			rtc_clk.num_parents,
			c_cfg.mux_hw, c_cfg.mux_ops,
			c_cfg.भाग_hw, c_cfg.भाग_ops,
			c_cfg.gate_hw, c_cfg.gate_ops,
			rtc_clk.flags);

	/* Micro-controller घड़ीs */
	क्रम (n = 0; n < ARRAY_SIZE(mco_clk); n++) अणु
		get_cfg_composite_भाग(&mco_clk_cfg, &mco_clk[n], &c_cfg,
				&sपंचांग32rcc_lock);

		hws[MCO_BANK + n] = clk_hw_रेजिस्टर_composite(शून्य,
				mco_clk[n].name,
				mco_clk[n].parent_name,
				mco_clk[n].num_parents,
				c_cfg.mux_hw, c_cfg.mux_ops,
				c_cfg.भाग_hw, c_cfg.भाग_ops,
				c_cfg.gate_hw, c_cfg.gate_ops,
				mco_clk[n].flags);
	पूर्ण

	of_clk_add_hw_provider(np, of_clk_hw_onecell_get, clk_data);

	वापस;

err_मुक्त_clks:
	kमुक्त(clk_data);
पूर्ण

/* The RCC node is a घड़ी and reset controller, and these
 * functionalities are supported by dअगरferent drivers that
 * matches the same compatible strings.
 */
CLK_OF_DECLARE_DRIVER(sपंचांग32h7_rcc, "st,stm32h743-rcc", sपंचांग32h7_rcc_init);
