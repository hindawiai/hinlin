<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2019-20 Sean Anderson <seanga2@gmail.com>
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 */
#घोषणा pr_fmt(fmt)     "k210-clk: " fmt

#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <soc/canaan/k210-sysctl.h>

#समावेश <dt-bindings/घड़ी/k210-clk.h>

काष्ठा k210_sysclk;

काष्ठा k210_clk अणु
	पूर्णांक id;
	काष्ठा k210_sysclk *ksc;
	काष्ठा clk_hw hw;
पूर्ण;

काष्ठा k210_clk_cfg अणु
	स्थिर अक्षर *name;
	u8 gate_reg;
	u8 gate_bit;
	u8 भाग_reg;
	u8 भाग_shअगरt;
	u8 भाग_width;
	u8 भाग_प्रकारype;
	u8 mux_reg;
	u8 mux_bit;
पूर्ण;

क्रमागत k210_clk_भाग_प्रकारype अणु
	K210_DIV_NONE,
	K210_DIV_ONE_BASED,
	K210_DIV_DOUBLE_ONE_BASED,
	K210_DIV_POWER_OF_TWO,
पूर्ण;

#घोषणा K210_GATE(_reg, _bit)	\
	.gate_reg = (_reg),	\
	.gate_bit = (_bit)

#घोषणा K210_DIV(_reg, _shअगरt, _width, _type)	\
	.भाग_reg = (_reg),			\
	.भाग_shअगरt = (_shअगरt),			\
	.भाग_width = (_width),			\
	.भाग_प्रकारype = (_type)

#घोषणा K210_MUX(_reg, _bit)	\
	.mux_reg = (_reg),	\
	.mux_bit = (_bit)

अटल काष्ठा k210_clk_cfg k210_clk_cfgs[K210_NUM_CLKS] = अणु
	/* Gated घड़ीs, no mux, no भागider */
	[K210_CLK_CPU] = अणु
		.name = "cpu",
		K210_GATE(K210_SYSCTL_EN_CENT, 0)
	पूर्ण,
	[K210_CLK_DMA] = अणु
		.name = "dma",
		K210_GATE(K210_SYSCTL_EN_PERI, 1)
	पूर्ण,
	[K210_CLK_FFT] = अणु
		.name = "fft",
		K210_GATE(K210_SYSCTL_EN_PERI, 4)
	पूर्ण,
	[K210_CLK_GPIO] = अणु
		.name = "gpio",
		K210_GATE(K210_SYSCTL_EN_PERI, 5)
	पूर्ण,
	[K210_CLK_UART1] = अणु
		.name = "uart1",
		K210_GATE(K210_SYSCTL_EN_PERI, 16)
	पूर्ण,
	[K210_CLK_UART2] = अणु
		.name = "uart2",
		K210_GATE(K210_SYSCTL_EN_PERI, 17)
	पूर्ण,
	[K210_CLK_UART3] = अणु
		.name = "uart3",
		K210_GATE(K210_SYSCTL_EN_PERI, 18)
	पूर्ण,
	[K210_CLK_FPIOA] = अणु
		.name = "fpioa",
		K210_GATE(K210_SYSCTL_EN_PERI, 20)
	पूर्ण,
	[K210_CLK_SHA] = अणु
		.name = "sha",
		K210_GATE(K210_SYSCTL_EN_PERI, 26)
	पूर्ण,
	[K210_CLK_AES] = अणु
		.name = "aes",
		K210_GATE(K210_SYSCTL_EN_PERI, 19)
	पूर्ण,
	[K210_CLK_OTP] = अणु
		.name = "otp",
		K210_GATE(K210_SYSCTL_EN_PERI, 27)
	पूर्ण,
	[K210_CLK_RTC] = अणु
		.name = "rtc",
		K210_GATE(K210_SYSCTL_EN_PERI, 29)
	पूर्ण,

	/* Gated भागider घड़ीs */
	[K210_CLK_SRAM0] = अणु
		.name = "sram0",
		K210_GATE(K210_SYSCTL_EN_CENT, 1),
		K210_DIV(K210_SYSCTL_THR0, 0, 4, K210_DIV_ONE_BASED)
	पूर्ण,
	[K210_CLK_SRAM1] = अणु
		.name = "sram1",
		K210_GATE(K210_SYSCTL_EN_CENT, 2),
		K210_DIV(K210_SYSCTL_THR0, 4, 4, K210_DIV_ONE_BASED)
	पूर्ण,
	[K210_CLK_ROM] = अणु
		.name = "rom",
		K210_GATE(K210_SYSCTL_EN_PERI, 0),
		K210_DIV(K210_SYSCTL_THR0, 16, 4, K210_DIV_ONE_BASED)
	पूर्ण,
	[K210_CLK_DVP] = अणु
		.name = "dvp",
		K210_GATE(K210_SYSCTL_EN_PERI, 3),
		K210_DIV(K210_SYSCTL_THR0, 12, 4, K210_DIV_ONE_BASED)
	पूर्ण,
	[K210_CLK_APB0] = अणु
		.name = "apb0",
		K210_GATE(K210_SYSCTL_EN_CENT, 3),
		K210_DIV(K210_SYSCTL_SEL0, 3, 3, K210_DIV_ONE_BASED)
	पूर्ण,
	[K210_CLK_APB1] = अणु
		.name = "apb1",
		K210_GATE(K210_SYSCTL_EN_CENT, 4),
		K210_DIV(K210_SYSCTL_SEL0, 6, 3, K210_DIV_ONE_BASED)
	पूर्ण,
	[K210_CLK_APB2] = अणु
		.name = "apb2",
		K210_GATE(K210_SYSCTL_EN_CENT, 5),
		K210_DIV(K210_SYSCTL_SEL0, 9, 3, K210_DIV_ONE_BASED)
	पूर्ण,
	[K210_CLK_AI] = अणु
		.name = "ai",
		K210_GATE(K210_SYSCTL_EN_PERI, 2),
		K210_DIV(K210_SYSCTL_THR0, 8, 4, K210_DIV_ONE_BASED)
	पूर्ण,
	[K210_CLK_SPI0] = अणु
		.name = "spi0",
		K210_GATE(K210_SYSCTL_EN_PERI, 6),
		K210_DIV(K210_SYSCTL_THR1, 0, 8, K210_DIV_DOUBLE_ONE_BASED)
	पूर्ण,
	[K210_CLK_SPI1] = अणु
		.name = "spi1",
		K210_GATE(K210_SYSCTL_EN_PERI, 7),
		K210_DIV(K210_SYSCTL_THR1, 8, 8, K210_DIV_DOUBLE_ONE_BASED)
	पूर्ण,
	[K210_CLK_SPI2] = अणु
		.name = "spi2",
		K210_GATE(K210_SYSCTL_EN_PERI, 8),
		K210_DIV(K210_SYSCTL_THR1, 16, 8, K210_DIV_DOUBLE_ONE_BASED)
	पूर्ण,
	[K210_CLK_I2C0] = अणु
		.name = "i2c0",
		K210_GATE(K210_SYSCTL_EN_PERI, 13),
		K210_DIV(K210_SYSCTL_THR5, 8, 8, K210_DIV_DOUBLE_ONE_BASED)
	पूर्ण,
	[K210_CLK_I2C1] = अणु
		.name = "i2c1",
		K210_GATE(K210_SYSCTL_EN_PERI, 14),
		K210_DIV(K210_SYSCTL_THR5, 16, 8, K210_DIV_DOUBLE_ONE_BASED)
	पूर्ण,
	[K210_CLK_I2C2] = अणु
		.name = "i2c2",
		K210_GATE(K210_SYSCTL_EN_PERI, 15),
		K210_DIV(K210_SYSCTL_THR5, 24, 8, K210_DIV_DOUBLE_ONE_BASED)
	पूर्ण,
	[K210_CLK_WDT0] = अणु
		.name = "wdt0",
		K210_GATE(K210_SYSCTL_EN_PERI, 24),
		K210_DIV(K210_SYSCTL_THR6, 0, 8, K210_DIV_DOUBLE_ONE_BASED)
	पूर्ण,
	[K210_CLK_WDT1] = अणु
		.name = "wdt1",
		K210_GATE(K210_SYSCTL_EN_PERI, 25),
		K210_DIV(K210_SYSCTL_THR6, 8, 8, K210_DIV_DOUBLE_ONE_BASED)
	पूर्ण,
	[K210_CLK_I2S0] = अणु
		.name = "i2s0",
		K210_GATE(K210_SYSCTL_EN_PERI, 10),
		K210_DIV(K210_SYSCTL_THR3, 0, 16, K210_DIV_DOUBLE_ONE_BASED)
	पूर्ण,
	[K210_CLK_I2S1] = अणु
		.name = "i2s1",
		K210_GATE(K210_SYSCTL_EN_PERI, 11),
		K210_DIV(K210_SYSCTL_THR3, 16, 16, K210_DIV_DOUBLE_ONE_BASED)
	पूर्ण,
	[K210_CLK_I2S2] = अणु
		.name = "i2s2",
		K210_GATE(K210_SYSCTL_EN_PERI, 12),
		K210_DIV(K210_SYSCTL_THR4, 0, 16, K210_DIV_DOUBLE_ONE_BASED)
	पूर्ण,

	/* Divider घड़ीs, no gate, no mux */
	[K210_CLK_I2S0_M] = अणु
		.name = "i2s0_m",
		K210_DIV(K210_SYSCTL_THR4, 16, 8, K210_DIV_DOUBLE_ONE_BASED)
	पूर्ण,
	[K210_CLK_I2S1_M] = अणु
		.name = "i2s1_m",
		K210_DIV(K210_SYSCTL_THR4, 24, 8, K210_DIV_DOUBLE_ONE_BASED)
	पूर्ण,
	[K210_CLK_I2S2_M] = अणु
		.name = "i2s2_m",
		K210_DIV(K210_SYSCTL_THR4, 0, 8, K210_DIV_DOUBLE_ONE_BASED)
	पूर्ण,

	/* Muxed gated भागider घड़ीs */
	[K210_CLK_SPI3] = अणु
		.name = "spi3",
		K210_GATE(K210_SYSCTL_EN_PERI, 9),
		K210_DIV(K210_SYSCTL_THR1, 24, 8, K210_DIV_DOUBLE_ONE_BASED),
		K210_MUX(K210_SYSCTL_SEL0, 12)
	पूर्ण,
	[K210_CLK_TIMER0] = अणु
		.name = "timer0",
		K210_GATE(K210_SYSCTL_EN_PERI, 21),
		K210_DIV(K210_SYSCTL_THR2,  0, 8, K210_DIV_DOUBLE_ONE_BASED),
		K210_MUX(K210_SYSCTL_SEL0, 13)
	पूर्ण,
	[K210_CLK_TIMER1] = अणु
		.name = "timer1",
		K210_GATE(K210_SYSCTL_EN_PERI, 22),
		K210_DIV(K210_SYSCTL_THR2, 8, 8, K210_DIV_DOUBLE_ONE_BASED),
		K210_MUX(K210_SYSCTL_SEL0, 14)
	पूर्ण,
	[K210_CLK_TIMER2] = अणु
		.name = "timer2",
		K210_GATE(K210_SYSCTL_EN_PERI, 23),
		K210_DIV(K210_SYSCTL_THR2, 16, 8, K210_DIV_DOUBLE_ONE_BASED),
		K210_MUX(K210_SYSCTL_SEL0, 15)
	पूर्ण,
पूर्ण;

/*
 * PLL control रेजिस्टर bits.
 */
#घोषणा K210_PLL_CLKR		GENMASK(3, 0)
#घोषणा K210_PLL_CLKF		GENMASK(9, 4)
#घोषणा K210_PLL_CLKOD		GENMASK(13, 10)
#घोषणा K210_PLL_BWADJ		GENMASK(19, 14)
#घोषणा K210_PLL_RESET		(1 << 20)
#घोषणा K210_PLL_PWRD		(1 << 21)
#घोषणा K210_PLL_INTFB		(1 << 22)
#घोषणा K210_PLL_BYPASS		(1 << 23)
#घोषणा K210_PLL_TEST		(1 << 24)
#घोषणा K210_PLL_EN		(1 << 25)
#घोषणा K210_PLL_SEL		GENMASK(27, 26) /* PLL2 only */

/*
 * PLL lock रेजिस्टर bits.
 */
#घोषणा K210_PLL_LOCK		0
#घोषणा K210_PLL_CLEAR_SLIP	2
#घोषणा K210_PLL_TEST_OUT	3

/*
 * Clock selector रेजिस्टर bits.
 */
#घोषणा K210_ACLK_SEL		BIT(0)
#घोषणा K210_ACLK_DIV		GENMASK(2, 1)

/*
 * PLLs.
 */
क्रमागत k210_pll_id अणु
	K210_PLL0, K210_PLL1, K210_PLL2, K210_PLL_NUM
पूर्ण;

काष्ठा k210_pll अणु
	क्रमागत k210_pll_id id;
	काष्ठा k210_sysclk *ksc;
	व्योम __iomem *base;
	व्योम __iomem *reg;
	व्योम __iomem *lock;
	u8 lock_shअगरt;
	u8 lock_width;
	काष्ठा clk_hw hw;
पूर्ण;
#घोषणा to_k210_pll(_hw)	container_of(_hw, काष्ठा k210_pll, hw)

/*
 * PLLs configuration: by शेष PLL0 runs at 780 MHz and PLL1 at 299 MHz.
 * The first 2 SRAM banks depend on ACLK/CPU घड़ी which is by शेष PLL0
 * rate भागided by 2. Set PLL1 to 390 MHz so that the third SRAM bank has the
 * same घड़ी as the first 2.
 */
काष्ठा k210_pll_cfg अणु
	u32 reg;
	u8 lock_shअगरt;
	u8 lock_width;
	u32 r;
	u32 f;
	u32 od;
	u32 bwadj;
पूर्ण;

अटल काष्ठा k210_pll_cfg k210_plls_cfg[] = अणु
	अणु K210_SYSCTL_PLL0,  0, 2, 0, 59, 1, 59 पूर्ण, /* 780 MHz */
	अणु K210_SYSCTL_PLL1,  8, 1, 0, 59, 3, 59 पूर्ण, /* 390 MHz */
	अणु K210_SYSCTL_PLL2, 16, 1, 0, 22, 1, 22 पूर्ण, /* 299 MHz */
पूर्ण;

/**
 * काष्ठा k210_sysclk - sysclk driver data
 * @regs: प्रणाली controller रेजिस्टरs start address
 * @clk_lock: घड़ी setting spinlock
 * @plls: SoC PLLs descriptors
 * @aclk: ACLK घड़ी
 * @clks: All other घड़ीs
 */
काष्ठा k210_sysclk अणु
	व्योम __iomem			*regs;
	spinlock_t			clk_lock;
	काष्ठा k210_pll			plls[K210_PLL_NUM];
	काष्ठा clk_hw			aclk;
	काष्ठा k210_clk			clks[K210_NUM_CLKS];
पूर्ण;

#घोषणा to_k210_sysclk(_hw)	container_of(_hw, काष्ठा k210_sysclk, aclk)

/*
 * Set ACLK parent selector: 0 क्रम IN0, 1 क्रम PLL0.
 */
अटल व्योम k210_aclk_set_selector(व्योम __iomem *regs, u8 sel)
अणु
	u32 reg = पढ़ोl(regs + K210_SYSCTL_SEL0);

	अगर (sel)
		reg |= K210_ACLK_SEL;
	अन्यथा
		reg &= K210_ACLK_SEL;
	ग_लिखोl(reg, regs + K210_SYSCTL_SEL0);
पूर्ण

अटल व्योम k210_init_pll(व्योम __iomem *regs, क्रमागत k210_pll_id pllid,
			  काष्ठा k210_pll *pll)
अणु
	pll->id = pllid;
	pll->reg = regs + k210_plls_cfg[pllid].reg;
	pll->lock = regs + K210_SYSCTL_PLL_LOCK;
	pll->lock_shअगरt = k210_plls_cfg[pllid].lock_shअगरt;
	pll->lock_width = k210_plls_cfg[pllid].lock_width;
पूर्ण

अटल व्योम k210_pll_रुको_क्रम_lock(काष्ठा k210_pll *pll)
अणु
	u32 reg, mask = GENMASK(pll->lock_shअगरt + pll->lock_width - 1,
				pll->lock_shअगरt);

	जबतक (true) अणु
		reg = पढ़ोl(pll->lock);
		अगर ((reg & mask) == mask)
			अवरोध;

		reg |= BIT(pll->lock_shअगरt + K210_PLL_CLEAR_SLIP);
		ग_लिखोl(reg, pll->lock);
	पूर्ण
पूर्ण

अटल bool k210_pll_hw_is_enabled(काष्ठा k210_pll *pll)
अणु
	u32 reg = पढ़ोl(pll->reg);
	u32 mask = K210_PLL_PWRD | K210_PLL_EN;

	अगर (reg & K210_PLL_RESET)
		वापस false;

	वापस (reg & mask) == mask;
पूर्ण

अटल व्योम k210_pll_enable_hw(व्योम __iomem *regs, काष्ठा k210_pll *pll)
अणु
	काष्ठा k210_pll_cfg *pll_cfg = &k210_plls_cfg[pll->id];
	u32 reg;

	अगर (k210_pll_hw_is_enabled(pll))
		वापस;

	/*
	 * For PLL0, we need to re-parent ACLK to IN0 to keep the CPU cores and
	 * SRAM running.
	 */
	अगर (pll->id == K210_PLL0)
		k210_aclk_set_selector(regs, 0);

	/* Set PLL factors */
	reg = पढ़ोl(pll->reg);
	reg &= ~GENMASK(19, 0);
	reg |= FIELD_PREP(K210_PLL_CLKR, pll_cfg->r);
	reg |= FIELD_PREP(K210_PLL_CLKF, pll_cfg->f);
	reg |= FIELD_PREP(K210_PLL_CLKOD, pll_cfg->od);
	reg |= FIELD_PREP(K210_PLL_BWADJ, pll_cfg->bwadj);
	reg |= K210_PLL_PWRD;
	ग_लिखोl(reg, pll->reg);

	/*
	 * Reset the PLL: ensure reset is low beक्रमe निश्चितing it.
	 * The magic NOPs come from the Kendryte reference SDK.
	 */
	reg &= ~K210_PLL_RESET;
	ग_लिखोl(reg, pll->reg);
	reg |= K210_PLL_RESET;
	ग_लिखोl(reg, pll->reg);
	nop();
	nop();
	reg &= ~K210_PLL_RESET;
	ग_लिखोl(reg, pll->reg);

	k210_pll_रुको_क्रम_lock(pll);

	reg &= ~K210_PLL_BYPASS;
	reg |= K210_PLL_EN;
	ग_लिखोl(reg, pll->reg);

	अगर (pll->id == K210_PLL0)
		k210_aclk_set_selector(regs, 1);
पूर्ण

अटल पूर्णांक k210_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा k210_pll *pll = to_k210_pll(hw);
	काष्ठा k210_sysclk *ksc = pll->ksc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ksc->clk_lock, flags);

	k210_pll_enable_hw(ksc->regs, pll);

	spin_unlock_irqrestore(&ksc->clk_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम k210_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा k210_pll *pll = to_k210_pll(hw);
	काष्ठा k210_sysclk *ksc = pll->ksc;
	अचिन्हित दीर्घ flags;
	u32 reg;

	/*
	 * Bypassing beक्रमe घातering off is important so child घड़ीs करो not
	 * stop working. This is especially important क्रम pll0, the indirect
	 * parent of the cpu घड़ी.
	 */
	spin_lock_irqsave(&ksc->clk_lock, flags);
	reg = पढ़ोl(pll->reg);
	reg |= K210_PLL_BYPASS;
	ग_लिखोl(reg, pll->reg);

	reg &= ~K210_PLL_PWRD;
	reg &= ~K210_PLL_EN;
	ग_लिखोl(reg, pll->reg);
	spin_unlock_irqrestore(&ksc->clk_lock, flags);
पूर्ण

अटल पूर्णांक k210_pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	वापस k210_pll_hw_is_enabled(to_k210_pll(hw));
पूर्ण

अटल अचिन्हित दीर्घ k210_pll_get_rate(काष्ठा clk_hw *hw,
				       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा k210_pll *pll = to_k210_pll(hw);
	u32 reg = पढ़ोl(pll->reg);
	u32 r, f, od;

	अगर (reg & K210_PLL_BYPASS)
		वापस parent_rate;

	अगर (!(reg & K210_PLL_PWRD))
		वापस 0;

	r = FIELD_GET(K210_PLL_CLKR, reg) + 1;
	f = FIELD_GET(K210_PLL_CLKF, reg) + 1;
	od = FIELD_GET(K210_PLL_CLKOD, reg) + 1;

	वापस (u64)parent_rate * f / (r * od);
पूर्ण

अटल स्थिर काष्ठा clk_ops k210_pll_ops = अणु
	.enable		= k210_pll_enable,
	.disable	= k210_pll_disable,
	.is_enabled	= k210_pll_is_enabled,
	.recalc_rate	= k210_pll_get_rate,
पूर्ण;

अटल पूर्णांक k210_pll2_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा k210_pll *pll = to_k210_pll(hw);
	काष्ठा k210_sysclk *ksc = pll->ksc;
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(&ksc->clk_lock, flags);

	reg = पढ़ोl(pll->reg);
	reg &= ~K210_PLL_SEL;
	reg |= FIELD_PREP(K210_PLL_SEL, index);
	ग_लिखोl(reg, pll->reg);

	spin_unlock_irqrestore(&ksc->clk_lock, flags);

	वापस 0;
पूर्ण

अटल u8 k210_pll2_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा k210_pll *pll = to_k210_pll(hw);
	u32 reg = पढ़ोl(pll->reg);

	वापस FIELD_GET(K210_PLL_SEL, reg);
पूर्ण

अटल स्थिर काष्ठा clk_ops k210_pll2_ops = अणु
	.enable		= k210_pll_enable,
	.disable	= k210_pll_disable,
	.is_enabled	= k210_pll_is_enabled,
	.recalc_rate	= k210_pll_get_rate,
	.set_parent	= k210_pll2_set_parent,
	.get_parent	= k210_pll2_get_parent,
पूर्ण;

अटल पूर्णांक __init k210_रेजिस्टर_pll(काष्ठा device_node *np,
				    काष्ठा k210_sysclk *ksc,
				    क्रमागत k210_pll_id pllid, स्थिर अक्षर *name,
				    पूर्णांक num_parents, स्थिर काष्ठा clk_ops *ops)
अणु
	काष्ठा k210_pll *pll = &ksc->plls[pllid];
	काष्ठा clk_init_data init = अणुपूर्ण;
	स्थिर काष्ठा clk_parent_data parent_data[] = अणु
		अणु /* .index = 0 क्रम in0 */ पूर्ण,
		अणु .hw = &ksc->plls[K210_PLL0].hw पूर्ण,
		अणु .hw = &ksc->plls[K210_PLL1].hw पूर्ण,
	पूर्ण;

	init.name = name;
	init.parent_data = parent_data;
	init.num_parents = num_parents;
	init.ops = ops;

	pll->hw.init = &init;
	pll->ksc = ksc;

	वापस of_clk_hw_रेजिस्टर(np, &pll->hw);
पूर्ण

अटल पूर्णांक __init k210_रेजिस्टर_plls(काष्ठा device_node *np,
				     काष्ठा k210_sysclk *ksc)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < K210_PLL_NUM; i++)
		k210_init_pll(ksc->regs, i, &ksc->plls[i]);

	/* PLL0 and PLL1 only have IN0 as parent */
	ret = k210_रेजिस्टर_pll(np, ksc, K210_PLL0, "pll0", 1, &k210_pll_ops);
	अगर (ret) अणु
		pr_err("%pOFP: register PLL0 failed\n", np);
		वापस ret;
	पूर्ण
	ret = k210_रेजिस्टर_pll(np, ksc, K210_PLL1, "pll1", 1, &k210_pll_ops);
	अगर (ret) अणु
		pr_err("%pOFP: register PLL1 failed\n", np);
		वापस ret;
	पूर्ण

	/* PLL2 has IN0, PLL0 and PLL1 as parents */
	ret = k210_रेजिस्टर_pll(np, ksc, K210_PLL2, "pll2", 3, &k210_pll2_ops);
	अगर (ret) अणु
		pr_err("%pOFP: register PLL2 failed\n", np);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक k210_aclk_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा k210_sysclk *ksc = to_k210_sysclk(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ksc->clk_lock, flags);

	k210_aclk_set_selector(ksc->regs, index);

	spin_unlock_irqrestore(&ksc->clk_lock, flags);

	वापस 0;
पूर्ण

अटल u8 k210_aclk_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा k210_sysclk *ksc = to_k210_sysclk(hw);
	u32 sel;

	sel = पढ़ोl(ksc->regs + K210_SYSCTL_SEL0) & K210_ACLK_SEL;

	वापस sel ? 1 : 0;
पूर्ण

अटल अचिन्हित दीर्घ k210_aclk_get_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा k210_sysclk *ksc = to_k210_sysclk(hw);
	u32 reg = पढ़ोl(ksc->regs + K210_SYSCTL_SEL0);
	अचिन्हित पूर्णांक shअगरt;

	अगर (!(reg & 0x1))
		वापस parent_rate;

	shअगरt = FIELD_GET(K210_ACLK_DIV, reg);

	वापस parent_rate / (2UL << shअगरt);
पूर्ण

अटल स्थिर काष्ठा clk_ops k210_aclk_ops = अणु
	.set_parent	= k210_aclk_set_parent,
	.get_parent	= k210_aclk_get_parent,
	.recalc_rate	= k210_aclk_get_rate,
पूर्ण;

/*
 * ACLK has IN0 and PLL0 as parents.
 */
अटल पूर्णांक __init k210_रेजिस्टर_aclk(काष्ठा device_node *np,
				     काष्ठा k210_sysclk *ksc)
अणु
	काष्ठा clk_init_data init = अणुपूर्ण;
	स्थिर काष्ठा clk_parent_data parent_data[] = अणु
		अणु /* .index = 0 क्रम in0 */ पूर्ण,
		अणु .hw = &ksc->plls[K210_PLL0].hw पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	init.name = "aclk";
	init.parent_data = parent_data;
	init.num_parents = 2;
	init.ops = &k210_aclk_ops;
	ksc->aclk.init = &init;

	ret = of_clk_hw_रेजिस्टर(np, &ksc->aclk);
	अगर (ret) अणु
		pr_err("%pOFP: register aclk failed\n", np);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा to_k210_clk(_hw)	container_of(_hw, काष्ठा k210_clk, hw)

अटल पूर्णांक k210_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा k210_clk *kclk = to_k210_clk(hw);
	काष्ठा k210_sysclk *ksc = kclk->ksc;
	काष्ठा k210_clk_cfg *cfg = &k210_clk_cfgs[kclk->id];
	अचिन्हित दीर्घ flags;
	u32 reg;

	अगर (!cfg->gate_reg)
		वापस 0;

	spin_lock_irqsave(&ksc->clk_lock, flags);
	reg = पढ़ोl(ksc->regs + cfg->gate_reg);
	reg |= BIT(cfg->gate_bit);
	ग_लिखोl(reg, ksc->regs + cfg->gate_reg);
	spin_unlock_irqrestore(&ksc->clk_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम k210_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा k210_clk *kclk = to_k210_clk(hw);
	काष्ठा k210_sysclk *ksc = kclk->ksc;
	काष्ठा k210_clk_cfg *cfg = &k210_clk_cfgs[kclk->id];
	अचिन्हित दीर्घ flags;
	u32 reg;

	अगर (!cfg->gate_reg)
		वापस;

	spin_lock_irqsave(&ksc->clk_lock, flags);
	reg = पढ़ोl(ksc->regs + cfg->gate_reg);
	reg &= ~BIT(cfg->gate_bit);
	ग_लिखोl(reg, ksc->regs + cfg->gate_reg);
	spin_unlock_irqrestore(&ksc->clk_lock, flags);
पूर्ण

अटल पूर्णांक k210_clk_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा k210_clk *kclk = to_k210_clk(hw);
	काष्ठा k210_sysclk *ksc = kclk->ksc;
	काष्ठा k210_clk_cfg *cfg = &k210_clk_cfgs[kclk->id];
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(&ksc->clk_lock, flags);
	reg = पढ़ोl(ksc->regs + cfg->mux_reg);
	अगर (index)
		reg |= BIT(cfg->mux_bit);
	अन्यथा
		reg &= ~BIT(cfg->mux_bit);
	spin_unlock_irqrestore(&ksc->clk_lock, flags);

	वापस 0;
पूर्ण

अटल u8 k210_clk_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा k210_clk *kclk = to_k210_clk(hw);
	काष्ठा k210_sysclk *ksc = kclk->ksc;
	काष्ठा k210_clk_cfg *cfg = &k210_clk_cfgs[kclk->id];
	अचिन्हित दीर्घ flags;
	u32 reg, idx;

	spin_lock_irqsave(&ksc->clk_lock, flags);
	reg = पढ़ोl(ksc->regs + cfg->mux_reg);
	idx = (reg & BIT(cfg->mux_bit)) ? 1 : 0;
	spin_unlock_irqrestore(&ksc->clk_lock, flags);

	वापस idx;
पूर्ण

अटल अचिन्हित दीर्घ k210_clk_get_rate(काष्ठा clk_hw *hw,
				       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा k210_clk *kclk = to_k210_clk(hw);
	काष्ठा k210_sysclk *ksc = kclk->ksc;
	काष्ठा k210_clk_cfg *cfg = &k210_clk_cfgs[kclk->id];
	u32 reg, भाग_val;

	अगर (!cfg->भाग_reg)
		वापस parent_rate;

	reg = पढ़ोl(ksc->regs + cfg->भाग_reg);
	भाग_val = (reg >> cfg->भाग_shअगरt) & GENMASK(cfg->भाग_width - 1, 0);

	चयन (cfg->भाग_प्रकारype) अणु
	हाल K210_DIV_ONE_BASED:
		वापस parent_rate / (भाग_val + 1);
	हाल K210_DIV_DOUBLE_ONE_BASED:
		वापस parent_rate / ((भाग_val + 1) * 2);
	हाल K210_DIV_POWER_OF_TWO:
		वापस parent_rate / (2UL << भाग_val);
	हाल K210_DIV_NONE:
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा clk_ops k210_clk_mux_ops = अणु
	.enable		= k210_clk_enable,
	.disable	= k210_clk_disable,
	.set_parent	= k210_clk_set_parent,
	.get_parent	= k210_clk_get_parent,
	.recalc_rate	= k210_clk_get_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops k210_clk_ops = अणु
	.enable		= k210_clk_enable,
	.disable	= k210_clk_disable,
	.recalc_rate	= k210_clk_get_rate,
पूर्ण;

अटल व्योम __init k210_रेजिस्टर_clk(काष्ठा device_node *np,
				     काष्ठा k210_sysclk *ksc, पूर्णांक id,
				     स्थिर काष्ठा clk_parent_data *parent_data,
				     पूर्णांक num_parents, अचिन्हित दीर्घ flags)
अणु
	काष्ठा k210_clk *kclk = &ksc->clks[id];
	काष्ठा clk_init_data init = अणुपूर्ण;
	पूर्णांक ret;

	init.name = k210_clk_cfgs[id].name;
	init.flags = flags;
	init.parent_data = parent_data;
	init.num_parents = num_parents;
	अगर (num_parents > 1)
		init.ops = &k210_clk_mux_ops;
	अन्यथा
		init.ops = &k210_clk_ops;

	kclk->id = id;
	kclk->ksc = ksc;
	kclk->hw.init = &init;

	ret = of_clk_hw_रेजिस्टर(np, &kclk->hw);
	अगर (ret) अणु
		pr_err("%pOFP: register clock %s failed\n",
		       np, k210_clk_cfgs[id].name);
		kclk->id = -1;
	पूर्ण
पूर्ण

/*
 * All muxed घड़ीs have IN0 and PLL0 as parents.
 */
अटल अंतरभूत व्योम __init k210_रेजिस्टर_mux_clk(काष्ठा device_node *np,
						काष्ठा k210_sysclk *ksc, पूर्णांक id)
अणु
	स्थिर काष्ठा clk_parent_data parent_data[2] = अणु
		अणु /* .index = 0 क्रम in0 */ पूर्ण,
		अणु .hw = &ksc->plls[K210_PLL0].hw पूर्ण
	पूर्ण;

	k210_रेजिस्टर_clk(np, ksc, id, parent_data, 2, 0);
पूर्ण

अटल अंतरभूत व्योम __init k210_रेजिस्टर_in0_child(काष्ठा device_node *np,
						काष्ठा k210_sysclk *ksc, पूर्णांक id)
अणु
	स्थिर काष्ठा clk_parent_data parent_data = अणु
		/* .index = 0 क्रम in0 */
	पूर्ण;

	k210_रेजिस्टर_clk(np, ksc, id, &parent_data, 1, 0);
पूर्ण

अटल अंतरभूत व्योम __init k210_रेजिस्टर_pll_child(काष्ठा device_node *np,
						काष्ठा k210_sysclk *ksc, पूर्णांक id,
						क्रमागत k210_pll_id pllid,
						अचिन्हित दीर्घ flags)
अणु
	स्थिर काष्ठा clk_parent_data parent_data = अणु
		.hw = &ksc->plls[pllid].hw,
	पूर्ण;

	k210_रेजिस्टर_clk(np, ksc, id, &parent_data, 1, flags);
पूर्ण

अटल अंतरभूत व्योम __init k210_रेजिस्टर_aclk_child(काष्ठा device_node *np,
						काष्ठा k210_sysclk *ksc, पूर्णांक id,
						अचिन्हित दीर्घ flags)
अणु
	स्थिर काष्ठा clk_parent_data parent_data = अणु
		.hw = &ksc->aclk,
	पूर्ण;

	k210_रेजिस्टर_clk(np, ksc, id, &parent_data, 1, flags);
पूर्ण

अटल अंतरभूत व्योम __init k210_रेजिस्टर_clk_child(काष्ठा device_node *np,
						काष्ठा k210_sysclk *ksc, पूर्णांक id,
						पूर्णांक parent_id)
अणु
	स्थिर काष्ठा clk_parent_data parent_data = अणु
		.hw = &ksc->clks[parent_id].hw,
	पूर्ण;

	k210_रेजिस्टर_clk(np, ksc, id, &parent_data, 1, 0);
पूर्ण

अटल काष्ठा clk_hw *k210_clk_hw_onecell_get(काष्ठा of_phandle_args *clkspec,
					      व्योम *data)
अणु
	काष्ठा k210_sysclk *ksc = data;
	अचिन्हित पूर्णांक idx = clkspec->args[0];

	अगर (idx >= K210_NUM_CLKS)
		वापस ERR_PTR(-EINVAL);

	वापस &ksc->clks[idx].hw;
पूर्ण

अटल व्योम __init k210_clk_init(काष्ठा device_node *np)
अणु
	काष्ठा device_node *sysctl_np;
	काष्ठा k210_sysclk *ksc;
	पूर्णांक i, ret;

	ksc = kzalloc(माप(*ksc), GFP_KERNEL);
	अगर (!ksc)
		वापस;

	spin_lock_init(&ksc->clk_lock);
	sysctl_np = of_get_parent(np);
	ksc->regs = of_iomap(sysctl_np, 0);
	of_node_put(sysctl_np);
	अगर (!ksc->regs) अणु
		pr_err("%pOFP: failed to map registers\n", np);
		वापस;
	पूर्ण

	ret = k210_रेजिस्टर_plls(np, ksc);
	अगर (ret)
		वापस;

	ret = k210_रेजिस्टर_aclk(np, ksc);
	अगर (ret)
		वापस;

	/*
	 * Critical घड़ीs: there are no consumers of the SRAM घड़ीs,
	 * including the AI घड़ी क्रम the third SRAM bank. The CPU घड़ी
	 * is only referenced by the uarths serial device and so would be
	 * disabled अगर the serial console is disabled to चयन to another
	 * console. Mark all these घड़ीs as critical so that they are never
	 * disabled by the core घड़ी management.
	 */
	k210_रेजिस्टर_aclk_child(np, ksc, K210_CLK_CPU, CLK_IS_CRITICAL);
	k210_रेजिस्टर_aclk_child(np, ksc, K210_CLK_SRAM0, CLK_IS_CRITICAL);
	k210_रेजिस्टर_aclk_child(np, ksc, K210_CLK_SRAM1, CLK_IS_CRITICAL);
	k210_रेजिस्टर_pll_child(np, ksc, K210_CLK_AI, K210_PLL1,
				CLK_IS_CRITICAL);

	/* Clocks with aclk as source */
	k210_रेजिस्टर_aclk_child(np, ksc, K210_CLK_DMA, 0);
	k210_रेजिस्टर_aclk_child(np, ksc, K210_CLK_FFT, 0);
	k210_रेजिस्टर_aclk_child(np, ksc, K210_CLK_ROM, 0);
	k210_रेजिस्टर_aclk_child(np, ksc, K210_CLK_DVP, 0);
	k210_रेजिस्टर_aclk_child(np, ksc, K210_CLK_APB0, 0);
	k210_रेजिस्टर_aclk_child(np, ksc, K210_CLK_APB1, 0);
	k210_रेजिस्टर_aclk_child(np, ksc, K210_CLK_APB2, 0);

	/* Clocks with PLL0 as source */
	k210_रेजिस्टर_pll_child(np, ksc, K210_CLK_SPI0, K210_PLL0, 0);
	k210_रेजिस्टर_pll_child(np, ksc, K210_CLK_SPI1, K210_PLL0, 0);
	k210_रेजिस्टर_pll_child(np, ksc, K210_CLK_SPI2, K210_PLL0, 0);
	k210_रेजिस्टर_pll_child(np, ksc, K210_CLK_I2C0, K210_PLL0, 0);
	k210_रेजिस्टर_pll_child(np, ksc, K210_CLK_I2C1, K210_PLL0, 0);
	k210_रेजिस्टर_pll_child(np, ksc, K210_CLK_I2C2, K210_PLL0, 0);

	/* Clocks with PLL2 as source */
	k210_रेजिस्टर_pll_child(np, ksc, K210_CLK_I2S0, K210_PLL2, 0);
	k210_रेजिस्टर_pll_child(np, ksc, K210_CLK_I2S1, K210_PLL2, 0);
	k210_रेजिस्टर_pll_child(np, ksc, K210_CLK_I2S2, K210_PLL2, 0);
	k210_रेजिस्टर_pll_child(np, ksc, K210_CLK_I2S0_M, K210_PLL2, 0);
	k210_रेजिस्टर_pll_child(np, ksc, K210_CLK_I2S1_M, K210_PLL2, 0);
	k210_रेजिस्टर_pll_child(np, ksc, K210_CLK_I2S2_M, K210_PLL2, 0);

	/* Clocks with IN0 as source */
	k210_रेजिस्टर_in0_child(np, ksc, K210_CLK_WDT0);
	k210_रेजिस्टर_in0_child(np, ksc, K210_CLK_WDT1);
	k210_रेजिस्टर_in0_child(np, ksc, K210_CLK_RTC);

	/* Clocks with APB0 as source */
	k210_रेजिस्टर_clk_child(np, ksc, K210_CLK_GPIO, K210_CLK_APB0);
	k210_रेजिस्टर_clk_child(np, ksc, K210_CLK_UART1, K210_CLK_APB0);
	k210_रेजिस्टर_clk_child(np, ksc, K210_CLK_UART2, K210_CLK_APB0);
	k210_रेजिस्टर_clk_child(np, ksc, K210_CLK_UART3, K210_CLK_APB0);
	k210_रेजिस्टर_clk_child(np, ksc, K210_CLK_FPIOA, K210_CLK_APB0);
	k210_रेजिस्टर_clk_child(np, ksc, K210_CLK_SHA, K210_CLK_APB0);

	/* Clocks with APB1 as source */
	k210_रेजिस्टर_clk_child(np, ksc, K210_CLK_AES, K210_CLK_APB1);
	k210_रेजिस्टर_clk_child(np, ksc, K210_CLK_OTP, K210_CLK_APB1);

	/* Mux घड़ीs with in0 or pll0 as source */
	k210_रेजिस्टर_mux_clk(np, ksc, K210_CLK_SPI3);
	k210_रेजिस्टर_mux_clk(np, ksc, K210_CLK_TIMER0);
	k210_रेजिस्टर_mux_clk(np, ksc, K210_CLK_TIMER1);
	k210_रेजिस्टर_mux_clk(np, ksc, K210_CLK_TIMER2);

	/* Check क्रम registration errors */
	क्रम (i = 0; i < K210_NUM_CLKS; i++) अणु
		अगर (ksc->clks[i].id != i)
			वापस;
	पूर्ण

	ret = of_clk_add_hw_provider(np, k210_clk_hw_onecell_get, ksc);
	अगर (ret) अणु
		pr_err("%pOFP: add clock provider failed %d\n", np, ret);
		वापस;
	पूर्ण

	pr_info("%pOFP: CPU running at %lu MHz\n",
		np, clk_hw_get_rate(&ksc->clks[K210_CLK_CPU].hw) / 1000000);
पूर्ण

CLK_OF_DECLARE(k210_clk, "canaan,k210-clk", k210_clk_init);

/*
 * Enable PLL1 to be able to use the AI SRAM.
 */
व्योम __init k210_clk_early_init(व्योम __iomem *regs)
अणु
	काष्ठा k210_pll pll1;

	/* Make sure ACLK selector is set to PLL0 */
	k210_aclk_set_selector(regs, 1);

	/* Startup PLL1 to enable the aisram bank क्रम general memory use */
	k210_init_pll(regs, K210_PLL1, &pll1);
	k210_pll_enable_hw(regs, &pll1);
पूर्ण
