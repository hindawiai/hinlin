<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics 2018 - All Rights Reserved
 * Author: Olivier Bideau <olivier.bideau@st.com> क्रम STMicroelectronics.
 * Author: Gabriel Fernandez <gabriel.fernandez@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश <dt-bindings/घड़ी/sपंचांग32mp1-clks.h>

अटल DEFINE_SPINLOCK(rlock);

#घोषणा RCC_OCENSETR		0x0C
#घोषणा RCC_HSICFGR		0x18
#घोषणा RCC_RDLSICR		0x144
#घोषणा RCC_PLL1CR		0x80
#घोषणा RCC_PLL1CFGR1		0x84
#घोषणा RCC_PLL1CFGR2		0x88
#घोषणा RCC_PLL2CR		0x94
#घोषणा RCC_PLL2CFGR1		0x98
#घोषणा RCC_PLL2CFGR2		0x9C
#घोषणा RCC_PLL3CR		0x880
#घोषणा RCC_PLL3CFGR1		0x884
#घोषणा RCC_PLL3CFGR2		0x888
#घोषणा RCC_PLL4CR		0x894
#घोषणा RCC_PLL4CFGR1		0x898
#घोषणा RCC_PLL4CFGR2		0x89C
#घोषणा RCC_APB1ENSETR		0xA00
#घोषणा RCC_APB2ENSETR		0xA08
#घोषणा RCC_APB3ENSETR		0xA10
#घोषणा RCC_APB4ENSETR		0x200
#घोषणा RCC_APB5ENSETR		0x208
#घोषणा RCC_AHB2ENSETR		0xA18
#घोषणा RCC_AHB3ENSETR		0xA20
#घोषणा RCC_AHB4ENSETR		0xA28
#घोषणा RCC_AHB5ENSETR		0x210
#घोषणा RCC_AHB6ENSETR		0x218
#घोषणा RCC_AHB6LPENSETR	0x318
#घोषणा RCC_RCK12SELR		0x28
#घोषणा RCC_RCK3SELR		0x820
#घोषणा RCC_RCK4SELR		0x824
#घोषणा RCC_MPCKSELR		0x20
#घोषणा RCC_ASSCKSELR		0x24
#घोषणा RCC_MSSCKSELR		0x48
#घोषणा RCC_SPI6CKSELR		0xC4
#घोषणा RCC_SDMMC12CKSELR	0x8F4
#घोषणा RCC_SDMMC3CKSELR	0x8F8
#घोषणा RCC_FMCCKSELR		0x904
#घोषणा RCC_I2C46CKSELR		0xC0
#घोषणा RCC_I2C12CKSELR		0x8C0
#घोषणा RCC_I2C35CKSELR		0x8C4
#घोषणा RCC_UART1CKSELR		0xC8
#घोषणा RCC_QSPICKSELR		0x900
#घोषणा RCC_ETHCKSELR		0x8FC
#घोषणा RCC_RNG1CKSELR		0xCC
#घोषणा RCC_RNG2CKSELR		0x920
#घोषणा RCC_GPUCKSELR		0x938
#घोषणा RCC_USBCKSELR		0x91C
#घोषणा RCC_STGENCKSELR		0xD4
#घोषणा RCC_SPDIFCKSELR		0x914
#घोषणा RCC_SPI2S1CKSELR	0x8D8
#घोषणा RCC_SPI2S23CKSELR	0x8DC
#घोषणा RCC_SPI2S45CKSELR	0x8E0
#घोषणा RCC_CECCKSELR		0x918
#घोषणा RCC_LPTIM1CKSELR	0x934
#घोषणा RCC_LPTIM23CKSELR	0x930
#घोषणा RCC_LPTIM45CKSELR	0x92C
#घोषणा RCC_UART24CKSELR	0x8E8
#घोषणा RCC_UART35CKSELR	0x8EC
#घोषणा RCC_UART6CKSELR		0x8E4
#घोषणा RCC_UART78CKSELR	0x8F0
#घोषणा RCC_FDCANCKSELR		0x90C
#घोषणा RCC_SAI1CKSELR		0x8C8
#घोषणा RCC_SAI2CKSELR		0x8CC
#घोषणा RCC_SAI3CKSELR		0x8D0
#घोषणा RCC_SAI4CKSELR		0x8D4
#घोषणा RCC_ADCCKSELR		0x928
#घोषणा RCC_MPCKDIVR		0x2C
#घोषणा RCC_DSICKSELR		0x924
#घोषणा RCC_CPERCKSELR		0xD0
#घोषणा RCC_MCO1CFGR		0x800
#घोषणा RCC_MCO2CFGR		0x804
#घोषणा RCC_BDCR		0x140
#घोषणा RCC_AXIDIVR		0x30
#घोषणा RCC_MCUDIVR		0x830
#घोषणा RCC_APB1DIVR		0x834
#घोषणा RCC_APB2DIVR		0x838
#घोषणा RCC_APB3DIVR		0x83C
#घोषणा RCC_APB4DIVR		0x3C
#घोषणा RCC_APB5DIVR		0x40
#घोषणा RCC_TIMG1PRER		0x828
#घोषणा RCC_TIMG2PRER		0x82C
#घोषणा RCC_RTCDIVR		0x44
#घोषणा RCC_DBGCFGR		0x80C

#घोषणा RCC_CLR	0x4

अटल स्थिर अक्षर * स्थिर ref12_parents[] = अणु
	"ck_hsi", "ck_hse"
पूर्ण;

अटल स्थिर अक्षर * स्थिर ref3_parents[] = अणु
	"ck_hsi", "ck_hse", "ck_csi"
पूर्ण;

अटल स्थिर अक्षर * स्थिर ref4_parents[] = अणु
	"ck_hsi", "ck_hse", "ck_csi"
पूर्ण;

अटल स्थिर अक्षर * स्थिर cpu_src[] = अणु
	"ck_hsi", "ck_hse", "pll1_p"
पूर्ण;

अटल स्थिर अक्षर * स्थिर axi_src[] = अणु
	"ck_hsi", "ck_hse", "pll2_p"
पूर्ण;

अटल स्थिर अक्षर * स्थिर per_src[] = अणु
	"ck_hsi", "ck_csi", "ck_hse"
पूर्ण;

अटल स्थिर अक्षर * स्थिर mcu_src[] = अणु
	"ck_hsi", "ck_hse", "ck_csi", "pll3_p"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sdmmc12_src[] = अणु
	"ck_axi", "pll3_r", "pll4_p", "ck_hsi"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sdmmc3_src[] = अणु
	"ck_mcu", "pll3_r", "pll4_p", "ck_hsi"
पूर्ण;

अटल स्थिर अक्षर * स्थिर fmc_src[] = अणु
	"ck_axi", "pll3_r", "pll4_p", "ck_per"
पूर्ण;

अटल स्थिर अक्षर * स्थिर qspi_src[] = अणु
	"ck_axi", "pll3_r", "pll4_p", "ck_per"
पूर्ण;

अटल स्थिर अक्षर * स्थिर eth_src[] = अणु
	"pll4_p", "pll3_q"
पूर्ण;

अटल स्थिर अक्षर * स्थिर rng_src[] = अणु
	"ck_csi", "pll4_r", "ck_lse", "ck_lsi"
पूर्ण;

अटल स्थिर अक्षर * स्थिर usbphy_src[] = अणु
	"ck_hse", "pll4_r", "clk-hse-div2"
पूर्ण;

अटल स्थिर अक्षर * स्थिर usbo_src[] = अणु
	"pll4_r", "ck_usbo_48m"
पूर्ण;

अटल स्थिर अक्षर * स्थिर stgen_src[] = अणु
	"ck_hsi", "ck_hse"
पूर्ण;

अटल स्थिर अक्षर * स्थिर spdअगर_src[] = अणु
	"pll4_p", "pll3_q", "ck_hsi"
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi123_src[] = अणु
	"pll4_p", "pll3_q", "i2s_ckin", "ck_per", "pll3_r"
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi45_src[] = अणु
	"pclk2", "pll4_q", "ck_hsi", "ck_csi", "ck_hse"
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi6_src[] = अणु
	"pclk5", "pll4_q", "ck_hsi", "ck_csi", "ck_hse", "pll3_q"
पूर्ण;

अटल स्थिर अक्षर * स्थिर cec_src[] = अणु
	"ck_lse", "ck_lsi", "ck_csi"
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c12_src[] = अणु
	"pclk1", "pll4_r", "ck_hsi", "ck_csi"
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c35_src[] = अणु
	"pclk1", "pll4_r", "ck_hsi", "ck_csi"
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c46_src[] = अणु
	"pclk5", "pll3_q", "ck_hsi", "ck_csi"
पूर्ण;

अटल स्थिर अक्षर * स्थिर lptim1_src[] = अणु
	"pclk1", "pll4_p", "pll3_q", "ck_lse", "ck_lsi", "ck_per"
पूर्ण;

अटल स्थिर अक्षर * स्थिर lptim23_src[] = अणु
	"pclk3", "pll4_q", "ck_per", "ck_lse", "ck_lsi"
पूर्ण;

अटल स्थिर अक्षर * स्थिर lptim45_src[] = अणु
	"pclk3", "pll4_p", "pll3_q", "ck_lse", "ck_lsi", "ck_per"
पूर्ण;

अटल स्थिर अक्षर * स्थिर usart1_src[] = अणु
	"pclk5", "pll3_q", "ck_hsi", "ck_csi", "pll4_q", "ck_hse"
पूर्ण;

अटल स्थिर अक्षर * स्थिर usart234578_src[] = अणु
	"pclk1", "pll4_q", "ck_hsi", "ck_csi", "ck_hse"
पूर्ण;

अटल स्थिर अक्षर * स्थिर usart6_src[] = अणु
	"pclk2", "pll4_q", "ck_hsi", "ck_csi", "ck_hse"
पूर्ण;

अटल स्थिर अक्षर * स्थिर fdcan_src[] = अणु
	"ck_hse", "pll3_q", "pll4_q", "pll4_r"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sai_src[] = अणु
	"pll4_q", "pll3_q", "i2s_ckin", "ck_per", "pll3_r"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sai2_src[] = अणु
	"pll4_q", "pll3_q", "i2s_ckin", "ck_per", "spdif_ck_symb", "pll3_r"
पूर्ण;

अटल स्थिर अक्षर * स्थिर adc12_src[] = अणु
	"pll4_r", "ck_per", "pll3_q"
पूर्ण;

अटल स्थिर अक्षर * स्थिर dsi_src[] = अणु
	"ck_dsi_phy", "pll4_p"
पूर्ण;

अटल स्थिर अक्षर * स्थिर rtc_src[] = अणु
	"off", "ck_lse", "ck_lsi", "ck_hse_rtc"
पूर्ण;

अटल स्थिर अक्षर * स्थिर mco1_src[] = अणु
	"ck_hsi", "ck_hse", "ck_csi", "ck_lsi", "ck_lse"
पूर्ण;

अटल स्थिर अक्षर * स्थिर mco2_src[] = अणु
	"ck_mpu", "ck_axi", "ck_mcu", "pll4_p", "ck_hse", "ck_hsi"
पूर्ण;

अटल स्थिर अक्षर * स्थिर ck_trace_src[] = अणु
	"ck_axi"
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable axi_भाग_प्रकारable[] = अणु
	अणु 0, 1 पूर्ण, अणु 1, 2 पूर्ण, अणु 2, 3 पूर्ण, अणु 3, 4 पूर्ण,
	अणु 4, 4 पूर्ण, अणु 5, 4 पूर्ण, अणु 6, 4 पूर्ण, अणु 7, 4 पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable mcu_भाग_प्रकारable[] = अणु
	अणु 0, 1 पूर्ण, अणु 1, 2 पूर्ण, अणु 2, 4 पूर्ण, अणु 3, 8 पूर्ण,
	अणु 4, 16 पूर्ण, अणु 5, 32 पूर्ण, अणु 6, 64 पूर्ण, अणु 7, 128 पूर्ण,
	अणु 8, 256 पूर्ण, अणु 9, 512 पूर्ण, अणु 10, 512पूर्ण, अणु 11, 512 पूर्ण,
	अणु 12, 512 पूर्ण, अणु 13, 512 पूर्ण, अणु 14, 512पूर्ण, अणु 15, 512 पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable apb_भाग_प्रकारable[] = अणु
	अणु 0, 1 पूर्ण, अणु 1, 2 पूर्ण, अणु 2, 4 पूर्ण, अणु 3, 8 पूर्ण,
	अणु 4, 16 पूर्ण, अणु 5, 16 पूर्ण, अणु 6, 16 पूर्ण, अणु 7, 16 पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable ck_trace_भाग_प्रकारable[] = अणु
	अणु 0, 1 पूर्ण, अणु 1, 2 पूर्ण, अणु 2, 4 पूर्ण, अणु 3, 8 पूर्ण,
	अणु 4, 16 पूर्ण, अणु 5, 16 पूर्ण, अणु 6, 16 पूर्ण, अणु 7, 16 पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

#घोषणा MAX_MUX_CLK 2

काष्ठा sपंचांग32_mmux अणु
	u8 nbr_clk;
	काष्ठा clk_hw *hws[MAX_MUX_CLK];
पूर्ण;

काष्ठा sपंचांग32_clk_mmux अणु
	काष्ठा clk_mux mux;
	काष्ठा sपंचांग32_mmux *mmux;
पूर्ण;

काष्ठा sपंचांग32_mgate अणु
	u8 nbr_clk;
	u32 flag;
पूर्ण;

काष्ठा sपंचांग32_clk_mgate अणु
	काष्ठा clk_gate gate;
	काष्ठा sपंचांग32_mgate *mgate;
	u32 mask;
पूर्ण;

काष्ठा घड़ी_config अणु
	u32 id;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	स्थिर अक्षर * स्थिर *parent_names;
	पूर्णांक num_parents;
	अचिन्हित दीर्घ flags;
	व्योम *cfg;
	काष्ठा clk_hw * (*func)(काष्ठा device *dev,
				काष्ठा clk_hw_onecell_data *clk_data,
				व्योम __iomem *base, spinlock_t *lock,
				स्थिर काष्ठा घड़ी_config *cfg);
पूर्ण;

#घोषणा NO_ID ~0

काष्ठा gate_cfg अणु
	u32 reg_off;
	u8 bit_idx;
	u8 gate_flags;
पूर्ण;

काष्ठा fixed_factor_cfg अणु
	अचिन्हित पूर्णांक mult;
	अचिन्हित पूर्णांक भाग;
पूर्ण;

काष्ठा भाग_cfg अणु
	u32 reg_off;
	u8 shअगरt;
	u8 width;
	u8 भाग_flags;
	स्थिर काष्ठा clk_भाग_प्रकारable *table;
पूर्ण;

काष्ठा mux_cfg अणु
	u32 reg_off;
	u8 shअगरt;
	u8 width;
	u8 mux_flags;
	u32 *table;
पूर्ण;

काष्ठा sपंचांग32_gate_cfg अणु
	काष्ठा gate_cfg		*gate;
	काष्ठा sपंचांग32_mgate	*mgate;
	स्थिर काष्ठा clk_ops	*ops;
पूर्ण;

काष्ठा sपंचांग32_भाग_cfg अणु
	काष्ठा भाग_cfg		*भाग;
	स्थिर काष्ठा clk_ops	*ops;
पूर्ण;

काष्ठा sपंचांग32_mux_cfg अणु
	काष्ठा mux_cfg		*mux;
	काष्ठा sपंचांग32_mmux	*mmux;
	स्थिर काष्ठा clk_ops	*ops;
पूर्ण;

/* STM32 Composite घड़ी */
काष्ठा sपंचांग32_composite_cfg अणु
	स्थिर काष्ठा sपंचांग32_gate_cfg	*gate;
	स्थिर काष्ठा sपंचांग32_भाग_cfg	*भाग;
	स्थिर काष्ठा sपंचांग32_mux_cfg	*mux;
पूर्ण;

अटल काष्ठा clk_hw *
_clk_hw_रेजिस्टर_gate(काष्ठा device *dev,
		      काष्ठा clk_hw_onecell_data *clk_data,
		      व्योम __iomem *base, spinlock_t *lock,
		      स्थिर काष्ठा घड़ी_config *cfg)
अणु
	काष्ठा gate_cfg *gate_cfg = cfg->cfg;

	वापस clk_hw_रेजिस्टर_gate(dev,
				    cfg->name,
				    cfg->parent_name,
				    cfg->flags,
				    gate_cfg->reg_off + base,
				    gate_cfg->bit_idx,
				    gate_cfg->gate_flags,
				    lock);
पूर्ण

अटल काष्ठा clk_hw *
_clk_hw_रेजिस्टर_fixed_factor(काष्ठा device *dev,
			      काष्ठा clk_hw_onecell_data *clk_data,
			      व्योम __iomem *base, spinlock_t *lock,
			      स्थिर काष्ठा घड़ी_config *cfg)
अणु
	काष्ठा fixed_factor_cfg *ff_cfg = cfg->cfg;

	वापस clk_hw_रेजिस्टर_fixed_factor(dev, cfg->name, cfg->parent_name,
					    cfg->flags, ff_cfg->mult,
					    ff_cfg->भाग);
पूर्ण

अटल काष्ठा clk_hw *
_clk_hw_रेजिस्टर_भागider_table(काष्ठा device *dev,
			       काष्ठा clk_hw_onecell_data *clk_data,
			       व्योम __iomem *base, spinlock_t *lock,
			       स्थिर काष्ठा घड़ी_config *cfg)
अणु
	काष्ठा भाग_cfg *भाग_cfg = cfg->cfg;

	वापस clk_hw_रेजिस्टर_भागider_table(dev,
					     cfg->name,
					     cfg->parent_name,
					     cfg->flags,
					     भाग_cfg->reg_off + base,
					     भाग_cfg->shअगरt,
					     भाग_cfg->width,
					     भाग_cfg->भाग_flags,
					     भाग_cfg->table,
					     lock);
पूर्ण

अटल काष्ठा clk_hw *
_clk_hw_रेजिस्टर_mux(काष्ठा device *dev,
		     काष्ठा clk_hw_onecell_data *clk_data,
		     व्योम __iomem *base, spinlock_t *lock,
		     स्थिर काष्ठा घड़ी_config *cfg)
अणु
	काष्ठा mux_cfg *mux_cfg = cfg->cfg;

	वापस clk_hw_रेजिस्टर_mux(dev, cfg->name, cfg->parent_names,
				   cfg->num_parents, cfg->flags,
				   mux_cfg->reg_off + base, mux_cfg->shअगरt,
				   mux_cfg->width, mux_cfg->mux_flags, lock);
पूर्ण

/* MP1 Gate घड़ी with set & clear रेजिस्टरs */

अटल पूर्णांक mp1_gate_clk_enable(काष्ठा clk_hw *hw)
अणु
	अगर (!clk_gate_ops.is_enabled(hw))
		clk_gate_ops.enable(hw);

	वापस 0;
पूर्ण

अटल व्योम mp1_gate_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gate *gate = to_clk_gate(hw);
	अचिन्हित दीर्घ flags = 0;

	अगर (clk_gate_ops.is_enabled(hw)) अणु
		spin_lock_irqsave(gate->lock, flags);
		ग_लिखोl_relaxed(BIT(gate->bit_idx), gate->reg + RCC_CLR);
		spin_unlock_irqrestore(gate->lock, flags);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा clk_ops mp1_gate_clk_ops = अणु
	.enable		= mp1_gate_clk_enable,
	.disable	= mp1_gate_clk_disable,
	.is_enabled	= clk_gate_is_enabled,
पूर्ण;

अटल काष्ठा clk_hw *_get_sपंचांग32_mux(व्योम __iomem *base,
				     स्थिर काष्ठा sपंचांग32_mux_cfg *cfg,
				     spinlock_t *lock)
अणु
	काष्ठा sपंचांग32_clk_mmux *mmux;
	काष्ठा clk_mux *mux;
	काष्ठा clk_hw *mux_hw;

	अगर (cfg->mmux) अणु
		mmux = kzalloc(माप(*mmux), GFP_KERNEL);
		अगर (!mmux)
			वापस ERR_PTR(-ENOMEM);

		mmux->mux.reg = cfg->mux->reg_off + base;
		mmux->mux.shअगरt = cfg->mux->shअगरt;
		mmux->mux.mask = (1 << cfg->mux->width) - 1;
		mmux->mux.flags = cfg->mux->mux_flags;
		mmux->mux.table = cfg->mux->table;
		mmux->mux.lock = lock;
		mmux->mmux = cfg->mmux;
		mux_hw = &mmux->mux.hw;
		cfg->mmux->hws[cfg->mmux->nbr_clk++] = mux_hw;

	पूर्ण अन्यथा अणु
		mux = kzalloc(माप(*mux), GFP_KERNEL);
		अगर (!mux)
			वापस ERR_PTR(-ENOMEM);

		mux->reg = cfg->mux->reg_off + base;
		mux->shअगरt = cfg->mux->shअगरt;
		mux->mask = (1 << cfg->mux->width) - 1;
		mux->flags = cfg->mux->mux_flags;
		mux->table = cfg->mux->table;
		mux->lock = lock;
		mux_hw = &mux->hw;
	पूर्ण

	वापस mux_hw;
पूर्ण

अटल काष्ठा clk_hw *_get_sपंचांग32_भाग(व्योम __iomem *base,
				     स्थिर काष्ठा sपंचांग32_भाग_cfg *cfg,
				     spinlock_t *lock)
अणु
	काष्ठा clk_भागider *भाग;

	भाग = kzalloc(माप(*भाग), GFP_KERNEL);

	अगर (!भाग)
		वापस ERR_PTR(-ENOMEM);

	भाग->reg = cfg->भाग->reg_off + base;
	भाग->shअगरt = cfg->भाग->shअगरt;
	भाग->width = cfg->भाग->width;
	भाग->flags = cfg->भाग->भाग_flags;
	भाग->table = cfg->भाग->table;
	भाग->lock = lock;

	वापस &भाग->hw;
पूर्ण

अटल काष्ठा clk_hw *
_get_sपंचांग32_gate(व्योम __iomem *base,
		स्थिर काष्ठा sपंचांग32_gate_cfg *cfg, spinlock_t *lock)
अणु
	काष्ठा sपंचांग32_clk_mgate *mgate;
	काष्ठा clk_gate *gate;
	काष्ठा clk_hw *gate_hw;

	अगर (cfg->mgate) अणु
		mgate = kzalloc(माप(*mgate), GFP_KERNEL);
		अगर (!mgate)
			वापस ERR_PTR(-ENOMEM);

		mgate->gate.reg = cfg->gate->reg_off + base;
		mgate->gate.bit_idx = cfg->gate->bit_idx;
		mgate->gate.flags = cfg->gate->gate_flags;
		mgate->gate.lock = lock;
		mgate->mask = BIT(cfg->mgate->nbr_clk++);

		mgate->mgate = cfg->mgate;

		gate_hw = &mgate->gate.hw;

	पूर्ण अन्यथा अणु
		gate = kzalloc(माप(*gate), GFP_KERNEL);
		अगर (!gate)
			वापस ERR_PTR(-ENOMEM);

		gate->reg = cfg->gate->reg_off + base;
		gate->bit_idx = cfg->gate->bit_idx;
		gate->flags = cfg->gate->gate_flags;
		gate->lock = lock;

		gate_hw = &gate->hw;
	पूर्ण

	वापस gate_hw;
पूर्ण

अटल काष्ठा clk_hw *
clk_sपंचांग32_रेजिस्टर_gate_ops(काष्ठा device *dev,
			    स्थिर अक्षर *name,
			    स्थिर अक्षर *parent_name,
			    अचिन्हित दीर्घ flags,
			    व्योम __iomem *base,
			    स्थिर काष्ठा sपंचांग32_gate_cfg *cfg,
			    spinlock_t *lock)
अणु
	काष्ठा clk_init_data init = अणु शून्य पूर्ण;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	init.name = name;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = flags;

	init.ops = &clk_gate_ops;

	अगर (cfg->ops)
		init.ops = cfg->ops;

	hw = _get_sपंचांग32_gate(base, cfg, lock);
	अगर (IS_ERR(hw))
		वापस ERR_PTR(-ENOMEM);

	hw->init = &init;

	ret = clk_hw_रेजिस्टर(dev, hw);
	अगर (ret)
		hw = ERR_PTR(ret);

	वापस hw;
पूर्ण

अटल काष्ठा clk_hw *
clk_sपंचांग32_रेजिस्टर_composite(काष्ठा device *dev,
			     स्थिर अक्षर *name, स्थिर अक्षर * स्थिर *parent_names,
			     पूर्णांक num_parents, व्योम __iomem *base,
			     स्थिर काष्ठा sपंचांग32_composite_cfg *cfg,
			     अचिन्हित दीर्घ flags, spinlock_t *lock)
अणु
	स्थिर काष्ठा clk_ops *mux_ops, *भाग_ops, *gate_ops;
	काष्ठा clk_hw *mux_hw, *भाग_hw, *gate_hw;

	mux_hw = शून्य;
	भाग_hw = शून्य;
	gate_hw = शून्य;
	mux_ops = शून्य;
	भाग_ops = शून्य;
	gate_ops = शून्य;

	अगर (cfg->mux) अणु
		mux_hw = _get_sपंचांग32_mux(base, cfg->mux, lock);

		अगर (!IS_ERR(mux_hw)) अणु
			mux_ops = &clk_mux_ops;

			अगर (cfg->mux->ops)
				mux_ops = cfg->mux->ops;
		पूर्ण
	पूर्ण

	अगर (cfg->भाग) अणु
		भाग_hw = _get_sपंचांग32_भाग(base, cfg->भाग, lock);

		अगर (!IS_ERR(भाग_hw)) अणु
			भाग_ops = &clk_भागider_ops;

			अगर (cfg->भाग->ops)
				भाग_ops = cfg->भाग->ops;
		पूर्ण
	पूर्ण

	अगर (cfg->gate) अणु
		gate_hw = _get_sपंचांग32_gate(base, cfg->gate, lock);

		अगर (!IS_ERR(gate_hw)) अणु
			gate_ops = &clk_gate_ops;

			अगर (cfg->gate->ops)
				gate_ops = cfg->gate->ops;
		पूर्ण
	पूर्ण

	वापस clk_hw_रेजिस्टर_composite(dev, name, parent_names, num_parents,
				       mux_hw, mux_ops, भाग_hw, भाग_ops,
				       gate_hw, gate_ops, flags);
पूर्ण

#घोषणा to_clk_mgate(_gate) container_of(_gate, काष्ठा sपंचांग32_clk_mgate, gate)

अटल पूर्णांक mp1_mgate_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gate *gate = to_clk_gate(hw);
	काष्ठा sपंचांग32_clk_mgate *clk_mgate = to_clk_mgate(gate);

	clk_mgate->mgate->flag |= clk_mgate->mask;

	mp1_gate_clk_enable(hw);

	वापस  0;
पूर्ण

अटल व्योम mp1_mgate_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gate *gate = to_clk_gate(hw);
	काष्ठा sपंचांग32_clk_mgate *clk_mgate = to_clk_mgate(gate);

	clk_mgate->mgate->flag &= ~clk_mgate->mask;

	अगर (clk_mgate->mgate->flag == 0)
		mp1_gate_clk_disable(hw);
पूर्ण

अटल स्थिर काष्ठा clk_ops mp1_mgate_clk_ops = अणु
	.enable		= mp1_mgate_clk_enable,
	.disable	= mp1_mgate_clk_disable,
	.is_enabled	= clk_gate_is_enabled,

पूर्ण;

#घोषणा to_clk_mmux(_mux) container_of(_mux, काष्ठा sपंचांग32_clk_mmux, mux)

अटल u8 clk_mmux_get_parent(काष्ठा clk_hw *hw)
अणु
	वापस clk_mux_ops.get_parent(hw);
पूर्ण

अटल पूर्णांक clk_mmux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_mux *mux = to_clk_mux(hw);
	काष्ठा sपंचांग32_clk_mmux *clk_mmux = to_clk_mmux(mux);
	काष्ठा clk_hw *hwp;
	पूर्णांक ret, n;

	ret = clk_mux_ops.set_parent(hw, index);
	अगर (ret)
		वापस ret;

	hwp = clk_hw_get_parent(hw);

	क्रम (n = 0; n < clk_mmux->mmux->nbr_clk; n++)
		अगर (clk_mmux->mmux->hws[n] != hw)
			clk_hw_reparent(clk_mmux->mmux->hws[n], hwp);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_mmux_ops = अणु
	.get_parent	= clk_mmux_get_parent,
	.set_parent	= clk_mmux_set_parent,
	.determine_rate	= __clk_mux_determine_rate,
पूर्ण;

/* STM32 PLL */
काष्ठा sपंचांग32_pll_obj अणु
	/* lock pll enable/disable रेजिस्टरs */
	spinlock_t *lock;
	व्योम __iomem *reg;
	काष्ठा clk_hw hw;
पूर्ण;

#घोषणा to_pll(_hw) container_of(_hw, काष्ठा sपंचांग32_pll_obj, hw)

#घोषणा PLL_ON		BIT(0)
#घोषणा PLL_RDY		BIT(1)
#घोषणा DIVN_MASK	0x1FF
#घोषणा DIVM_MASK	0x3F
#घोषणा DIVM_SHIFT	16
#घोषणा DIVN_SHIFT	0
#घोषणा FRAC_OFFSET	0xC
#घोषणा FRAC_MASK	0x1FFF
#घोषणा FRAC_SHIFT	3
#घोषणा FRACLE		BIT(16)

अटल पूर्णांक __pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा sपंचांग32_pll_obj *clk_elem = to_pll(hw);

	वापस पढ़ोl_relaxed(clk_elem->reg) & PLL_ON;
पूर्ण

#घोषणा TIMEOUT 5

अटल पूर्णांक pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा sपंचांग32_pll_obj *clk_elem = to_pll(hw);
	u32 reg;
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित पूर्णांक समयout = TIMEOUT;
	पूर्णांक bit_status = 0;

	spin_lock_irqsave(clk_elem->lock, flags);

	अगर (__pll_is_enabled(hw))
		जाओ unlock;

	reg = पढ़ोl_relaxed(clk_elem->reg);
	reg |= PLL_ON;
	ग_लिखोl_relaxed(reg, clk_elem->reg);

	/* We can't use पढ़ोl_poll_समयout() because we can be blocked अगर
	 * someone enables this घड़ी beक्रमe घड़ीsource changes.
	 * Only jअगरfies counter is available. Jअगरfies are incremented by
	 * पूर्णांकerruptions and enable op करोes not allow to be पूर्णांकerrupted.
	 */
	करो अणु
		bit_status = !(पढ़ोl_relaxed(clk_elem->reg) & PLL_RDY);

		अगर (bit_status)
			udelay(120);

	पूर्ण जबतक (bit_status && --समयout);

unlock:
	spin_unlock_irqrestore(clk_elem->lock, flags);

	वापस bit_status;
पूर्ण

अटल व्योम pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा sपंचांग32_pll_obj *clk_elem = to_pll(hw);
	u32 reg;
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(clk_elem->lock, flags);

	reg = पढ़ोl_relaxed(clk_elem->reg);
	reg &= ~PLL_ON;
	ग_लिखोl_relaxed(reg, clk_elem->reg);

	spin_unlock_irqrestore(clk_elem->lock, flags);
पूर्ण

अटल u32 pll_frac_val(काष्ठा clk_hw *hw)
अणु
	काष्ठा sपंचांग32_pll_obj *clk_elem = to_pll(hw);
	u32 reg, frac = 0;

	reg = पढ़ोl_relaxed(clk_elem->reg + FRAC_OFFSET);
	अगर (reg & FRACLE)
		frac = (reg >> FRAC_SHIFT) & FRAC_MASK;

	वापस frac;
पूर्ण

अटल अचिन्हित दीर्घ pll_recalc_rate(काष्ठा clk_hw *hw,
				     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sपंचांग32_pll_obj *clk_elem = to_pll(hw);
	u32 reg;
	u32 frac, भागm, भागn;
	u64 rate, rate_frac = 0;

	reg = पढ़ोl_relaxed(clk_elem->reg + 4);

	भागm = ((reg >> DIVM_SHIFT) & DIVM_MASK) + 1;
	भागn = ((reg >> DIVN_SHIFT) & DIVN_MASK) + 1;
	rate = (u64)parent_rate * भागn;

	करो_भाग(rate, भागm);

	frac = pll_frac_val(hw);
	अगर (frac) अणु
		rate_frac = (u64)parent_rate * (u64)frac;
		करो_भाग(rate_frac, (भागm * 8192));
	पूर्ण

	वापस rate + rate_frac;
पूर्ण

अटल पूर्णांक pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा sपंचांग32_pll_obj *clk_elem = to_pll(hw);
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret;

	spin_lock_irqsave(clk_elem->lock, flags);
	ret = __pll_is_enabled(hw);
	spin_unlock_irqrestore(clk_elem->lock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops pll_ops = अणु
	.enable		= pll_enable,
	.disable	= pll_disable,
	.recalc_rate	= pll_recalc_rate,
	.is_enabled	= pll_is_enabled,
पूर्ण;

अटल काष्ठा clk_hw *clk_रेजिस्टर_pll(काष्ठा device *dev, स्थिर अक्षर *name,
				       स्थिर अक्षर *parent_name,
				       व्योम __iomem *reg,
				       अचिन्हित दीर्घ flags,
				       spinlock_t *lock)
अणु
	काष्ठा sपंचांग32_pll_obj *element;
	काष्ठा clk_init_data init;
	काष्ठा clk_hw *hw;
	पूर्णांक err;

	element = kzalloc(माप(*element), GFP_KERNEL);
	अगर (!element)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &pll_ops;
	init.flags = flags;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	element->hw.init = &init;
	element->reg = reg;
	element->lock = lock;

	hw = &element->hw;
	err = clk_hw_रेजिस्टर(dev, hw);

	अगर (err) अणु
		kमुक्त(element);
		वापस ERR_PTR(err);
	पूर्ण

	वापस hw;
पूर्ण

/* Kernel Timer */
काष्ठा समयr_cker अणु
	/* lock the kernel output भागider रेजिस्टर */
	spinlock_t *lock;
	व्योम __iomem *apbभाग;
	व्योम __iomem *timpre;
	काष्ठा clk_hw hw;
पूर्ण;

#घोषणा to_समयr_cker(_hw) container_of(_hw, काष्ठा समयr_cker, hw)

#घोषणा APB_DIV_MASK 0x07
#घोषणा TIM_PRE_MASK 0x01

अटल अचिन्हित दीर्घ __besपंचांगult(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा समयr_cker *tim_ker = to_समयr_cker(hw);
	u32 prescaler;
	अचिन्हित पूर्णांक mult = 0;

	prescaler = पढ़ोl_relaxed(tim_ker->apbभाग) & APB_DIV_MASK;
	अगर (prescaler < 2)
		वापस 1;

	mult = 2;

	अगर (rate / parent_rate >= 4)
		mult = 4;

	वापस mult;
पूर्ण

अटल दीर्घ समयr_ker_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ *parent_rate)
अणु
	अचिन्हित दीर्घ factor = __besपंचांगult(hw, rate, *parent_rate);

	वापस *parent_rate * factor;
पूर्ण

अटल पूर्णांक समयr_ker_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा समयr_cker *tim_ker = to_समयr_cker(hw);
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित दीर्घ factor = __besपंचांगult(hw, rate, parent_rate);
	पूर्णांक ret = 0;

	spin_lock_irqsave(tim_ker->lock, flags);

	चयन (factor) अणु
	हाल 1:
		अवरोध;
	हाल 2:
		ग_लिखोl_relaxed(0, tim_ker->timpre);
		अवरोध;
	हाल 4:
		ग_लिखोl_relaxed(1, tim_ker->timpre);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	spin_unlock_irqrestore(tim_ker->lock, flags);

	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ समयr_ker_recalc_rate(काष्ठा clk_hw *hw,
					   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा समयr_cker *tim_ker = to_समयr_cker(hw);
	u32 prescaler, timpre;
	u32 mul;

	prescaler = पढ़ोl_relaxed(tim_ker->apbभाग) & APB_DIV_MASK;

	timpre = पढ़ोl_relaxed(tim_ker->timpre) & TIM_PRE_MASK;

	अगर (!prescaler)
		वापस parent_rate;

	mul = (timpre + 1) * 2;

	वापस parent_rate * mul;
पूर्ण

अटल स्थिर काष्ठा clk_ops समयr_ker_ops = अणु
	.recalc_rate	= समयr_ker_recalc_rate,
	.round_rate	= समयr_ker_round_rate,
	.set_rate	= समयr_ker_set_rate,

पूर्ण;

अटल काष्ठा clk_hw *clk_रेजिस्टर_cktim(काष्ठा device *dev, स्थिर अक्षर *name,
					 स्थिर अक्षर *parent_name,
					 अचिन्हित दीर्घ flags,
					 व्योम __iomem *apbभाग,
					 व्योम __iomem *timpre,
					 spinlock_t *lock)
अणु
	काष्ठा समयr_cker *tim_ker;
	काष्ठा clk_init_data init;
	काष्ठा clk_hw *hw;
	पूर्णांक err;

	tim_ker = kzalloc(माप(*tim_ker), GFP_KERNEL);
	अगर (!tim_ker)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &समयr_ker_ops;
	init.flags = flags;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	tim_ker->hw.init = &init;
	tim_ker->lock = lock;
	tim_ker->apbभाग = apbभाग;
	tim_ker->timpre = timpre;

	hw = &tim_ker->hw;
	err = clk_hw_रेजिस्टर(dev, hw);

	अगर (err) अणु
		kमुक्त(tim_ker);
		वापस ERR_PTR(err);
	पूर्ण

	वापस hw;
पूर्ण

काष्ठा sपंचांग32_pll_cfg अणु
	u32 offset;
पूर्ण;

अटल काष्ठा clk_hw *_clk_रेजिस्टर_pll(काष्ठा device *dev,
					काष्ठा clk_hw_onecell_data *clk_data,
					व्योम __iomem *base, spinlock_t *lock,
					स्थिर काष्ठा घड़ी_config *cfg)
अणु
	काष्ठा sपंचांग32_pll_cfg *sपंचांग_pll_cfg = cfg->cfg;

	वापस clk_रेजिस्टर_pll(dev, cfg->name, cfg->parent_name,
				base + sपंचांग_pll_cfg->offset, cfg->flags, lock);
पूर्ण

काष्ठा sपंचांग32_cktim_cfg अणु
	u32 offset_apbभाग;
	u32 offset_timpre;
पूर्ण;

अटल काष्ठा clk_hw *_clk_रेजिस्टर_cktim(काष्ठा device *dev,
					  काष्ठा clk_hw_onecell_data *clk_data,
					  व्योम __iomem *base, spinlock_t *lock,
					  स्थिर काष्ठा घड़ी_config *cfg)
अणु
	काष्ठा sपंचांग32_cktim_cfg *cktim_cfg = cfg->cfg;

	वापस clk_रेजिस्टर_cktim(dev, cfg->name, cfg->parent_name, cfg->flags,
				  cktim_cfg->offset_apbभाग + base,
				  cktim_cfg->offset_timpre + base, lock);
पूर्ण

अटल काष्ठा clk_hw *
_clk_sपंचांग32_रेजिस्टर_gate(काष्ठा device *dev,
			 काष्ठा clk_hw_onecell_data *clk_data,
			 व्योम __iomem *base, spinlock_t *lock,
			 स्थिर काष्ठा घड़ी_config *cfg)
अणु
	वापस clk_sपंचांग32_रेजिस्टर_gate_ops(dev,
				    cfg->name,
				    cfg->parent_name,
				    cfg->flags,
				    base,
				    cfg->cfg,
				    lock);
पूर्ण

अटल काष्ठा clk_hw *
_clk_sपंचांग32_रेजिस्टर_composite(काष्ठा device *dev,
			      काष्ठा clk_hw_onecell_data *clk_data,
			      व्योम __iomem *base, spinlock_t *lock,
			      स्थिर काष्ठा घड़ी_config *cfg)
अणु
	वापस clk_sपंचांग32_रेजिस्टर_composite(dev, cfg->name, cfg->parent_names,
					    cfg->num_parents, base, cfg->cfg,
					    cfg->flags, lock);
पूर्ण

#घोषणा GATE(_id, _name, _parent, _flags, _offset, _bit_idx, _gate_flags)\
अणु\
	.id		= _id,\
	.name		= _name,\
	.parent_name	= _parent,\
	.flags		= _flags,\
	.cfg		=  &(काष्ठा gate_cfg) अणु\
		.reg_off	= _offset,\
		.bit_idx	= _bit_idx,\
		.gate_flags	= _gate_flags,\
	पूर्ण,\
	.func		= _clk_hw_रेजिस्टर_gate,\
पूर्ण

#घोषणा FIXED_FACTOR(_id, _name, _parent, _flags, _mult, _भाग)\
अणु\
	.id		= _id,\
	.name		= _name,\
	.parent_name	= _parent,\
	.flags		= _flags,\
	.cfg		=  &(काष्ठा fixed_factor_cfg) अणु\
		.mult = _mult,\
		.भाग = _भाग,\
	पूर्ण,\
	.func		= _clk_hw_रेजिस्टर_fixed_factor,\
पूर्ण

#घोषणा DIV_TABLE(_id, _name, _parent, _flags, _offset, _shअगरt, _width,\
		  _भाग_flags, _भाग_प्रकारable)\
अणु\
	.id		= _id,\
	.name		= _name,\
	.parent_name	= _parent,\
	.flags		= _flags,\
	.cfg		=  &(काष्ठा भाग_cfg) अणु\
		.reg_off	= _offset,\
		.shअगरt		= _shअगरt,\
		.width		= _width,\
		.भाग_flags	= _भाग_flags,\
		.table		= _भाग_प्रकारable,\
	पूर्ण,\
	.func		= _clk_hw_रेजिस्टर_भागider_table,\
पूर्ण

#घोषणा DIV(_id, _name, _parent, _flags, _offset, _shअगरt, _width, _भाग_flags)\
	DIV_TABLE(_id, _name, _parent, _flags, _offset, _shअगरt, _width,\
		  _भाग_flags, शून्य)

#घोषणा MUX(_id, _name, _parents, _flags, _offset, _shअगरt, _width, _mux_flags)\
अणु\
	.id		= _id,\
	.name		= _name,\
	.parent_names	= _parents,\
	.num_parents	= ARRAY_SIZE(_parents),\
	.flags		= _flags,\
	.cfg		=  &(काष्ठा mux_cfg) अणु\
		.reg_off	= _offset,\
		.shअगरt		= _shअगरt,\
		.width		= _width,\
		.mux_flags	= _mux_flags,\
	पूर्ण,\
	.func		= _clk_hw_रेजिस्टर_mux,\
पूर्ण

#घोषणा PLL(_id, _name, _parent, _flags, _offset)\
अणु\
	.id		= _id,\
	.name		= _name,\
	.parent_name	= _parent,\
	.flags		= _flags,\
	.cfg		=  &(काष्ठा sपंचांग32_pll_cfg) अणु\
		.offset = _offset,\
	पूर्ण,\
	.func		= _clk_रेजिस्टर_pll,\
पूर्ण

#घोषणा STM32_CKTIM(_name, _parent, _flags, _offset_apbभाग, _offset_timpre)\
अणु\
	.id		= NO_ID,\
	.name		= _name,\
	.parent_name	= _parent,\
	.flags		= _flags,\
	.cfg		=  &(काष्ठा sपंचांग32_cktim_cfg) अणु\
		.offset_apbभाग = _offset_apbभाग,\
		.offset_timpre = _offset_timpre,\
	पूर्ण,\
	.func		= _clk_रेजिस्टर_cktim,\
पूर्ण

#घोषणा STM32_TIM(_id, _name, _parent, _offset_set, _bit_idx)\
		  GATE_MP1(_id, _name, _parent, CLK_SET_RATE_PARENT,\
			   _offset_set, _bit_idx, 0)

/* STM32 GATE */
#घोषणा STM32_GATE(_id, _name, _parent, _flags, _gate)\
अणु\
	.id		= _id,\
	.name		= _name,\
	.parent_name	= _parent,\
	.flags		= _flags,\
	.cfg		= (काष्ठा sपंचांग32_gate_cfg *) अणु_gateपूर्ण,\
	.func		= _clk_sपंचांग32_रेजिस्टर_gate,\
पूर्ण

#घोषणा _STM32_GATE(_gate_offset, _gate_bit_idx, _gate_flags, _mgate, _ops)\
	(&(काष्ठा sपंचांग32_gate_cfg) अणु\
		&(काष्ठा gate_cfg) अणु\
			.reg_off	= _gate_offset,\
			.bit_idx	= _gate_bit_idx,\
			.gate_flags	= _gate_flags,\
		पूर्ण,\
		.mgate		= _mgate,\
		.ops		= _ops,\
	पूर्ण)

#घोषणा _STM32_MGATE(_mgate)\
	(&per_gate_cfg[_mgate])

#घोषणा _GATE(_gate_offset, _gate_bit_idx, _gate_flags)\
	_STM32_GATE(_gate_offset, _gate_bit_idx, _gate_flags,\
		    शून्य, शून्य)\

#घोषणा _GATE_MP1(_gate_offset, _gate_bit_idx, _gate_flags)\
	_STM32_GATE(_gate_offset, _gate_bit_idx, _gate_flags,\
		    शून्य, &mp1_gate_clk_ops)\

#घोषणा _MGATE_MP1(_mgate)\
	.gate = &per_gate_cfg[_mgate]

#घोषणा GATE_MP1(_id, _name, _parent, _flags, _offset, _bit_idx, _gate_flags)\
	STM32_GATE(_id, _name, _parent, _flags,\
		   _GATE_MP1(_offset, _bit_idx, _gate_flags))

#घोषणा MGATE_MP1(_id, _name, _parent, _flags, _mgate)\
	STM32_GATE(_id, _name, _parent, _flags,\
		   _STM32_MGATE(_mgate))

#घोषणा _STM32_DIV(_भाग_offset, _भाग_shअगरt, _भाग_width,\
		   _भाग_flags, _भाग_प्रकारable, _ops)\
	.भाग = &(काष्ठा sपंचांग32_भाग_cfg) अणु\
		&(काष्ठा भाग_cfg) अणु\
			.reg_off	= _भाग_offset,\
			.shअगरt		= _भाग_shअगरt,\
			.width		= _भाग_width,\
			.भाग_flags	= _भाग_flags,\
			.table		= _भाग_प्रकारable,\
		पूर्ण,\
		.ops		= _ops,\
	पूर्ण

#घोषणा _DIV(_भाग_offset, _भाग_shअगरt, _भाग_width, _भाग_flags, _भाग_प्रकारable)\
	_STM32_DIV(_भाग_offset, _भाग_shअगरt, _भाग_width,\
		   _भाग_flags, _भाग_प्रकारable, शून्य)\

#घोषणा _STM32_MUX(_offset, _shअगरt, _width, _mux_flags, _mmux, _ops)\
	.mux = &(काष्ठा sपंचांग32_mux_cfg) अणु\
		&(काष्ठा mux_cfg) अणु\
			.reg_off	= _offset,\
			.shअगरt		= _shअगरt,\
			.width		= _width,\
			.mux_flags	= _mux_flags,\
			.table		= शून्य,\
		पूर्ण,\
		.mmux		= _mmux,\
		.ops		= _ops,\
	पूर्ण

#घोषणा _MUX(_offset, _shअगरt, _width, _mux_flags)\
	_STM32_MUX(_offset, _shअगरt, _width, _mux_flags, शून्य, शून्य)\

#घोषणा _MMUX(_mmux) .mux = &ker_mux_cfg[_mmux]

#घोषणा PARENT(_parent) ((स्थिर अक्षर *[]) अणु _parentपूर्ण)

#घोषणा _NO_MUX .mux = शून्य
#घोषणा _NO_DIV .भाग = शून्य
#घोषणा _NO_GATE .gate = शून्य

#घोषणा COMPOSITE(_id, _name, _parents, _flags, _gate, _mux, _भाग)\
अणु\
	.id		= _id,\
	.name		= _name,\
	.parent_names	= _parents,\
	.num_parents	= ARRAY_SIZE(_parents),\
	.flags		= _flags,\
	.cfg		= &(काष्ठा sपंचांग32_composite_cfg) अणु\
		_gate,\
		_mux,\
		_भाग,\
	पूर्ण,\
	.func		= _clk_sपंचांग32_रेजिस्टर_composite,\
पूर्ण

#घोषणा PCLK(_id, _name, _parent, _flags, _mgate)\
	MGATE_MP1(_id, _name, _parent, _flags, _mgate)

#घोषणा KCLK(_id, _name, _parents, _flags, _mgate, _mmux)\
	     COMPOSITE(_id, _name, _parents, CLK_OPS_PARENT_ENABLE |\
		       CLK_SET_RATE_NO_REPARENT | _flags,\
		       _MGATE_MP1(_mgate),\
		       _MMUX(_mmux),\
		       _NO_DIV)

क्रमागत अणु
	G_SAI1,
	G_SAI2,
	G_SAI3,
	G_SAI4,
	G_SPI1,
	G_SPI2,
	G_SPI3,
	G_SPI4,
	G_SPI5,
	G_SPI6,
	G_SPDIF,
	G_I2C1,
	G_I2C2,
	G_I2C3,
	G_I2C4,
	G_I2C5,
	G_I2C6,
	G_USART2,
	G_UART4,
	G_USART3,
	G_UART5,
	G_USART1,
	G_USART6,
	G_UART7,
	G_UART8,
	G_LPTIM1,
	G_LPTIM2,
	G_LPTIM3,
	G_LPTIM4,
	G_LPTIM5,
	G_LTDC,
	G_DSI,
	G_QSPI,
	G_FMC,
	G_SDMMC1,
	G_SDMMC2,
	G_SDMMC3,
	G_USBO,
	G_USBPHY,
	G_RNG1,
	G_RNG2,
	G_FDCAN,
	G_DAC12,
	G_CEC,
	G_ADC12,
	G_GPU,
	G_STGEN,
	G_DFSDM,
	G_ADFSDM,
	G_TIM2,
	G_TIM3,
	G_TIM4,
	G_TIM5,
	G_TIM6,
	G_TIM7,
	G_TIM12,
	G_TIM13,
	G_TIM14,
	G_MDIO,
	G_TIM1,
	G_TIM8,
	G_TIM15,
	G_TIM16,
	G_TIM17,
	G_SYSCFG,
	G_VREF,
	G_TMPSENS,
	G_PMBCTRL,
	G_HDP,
	G_IWDG2,
	G_STGENRO,
	G_DMA1,
	G_DMA2,
	G_DMAMUX,
	G_DCMI,
	G_CRYP2,
	G_HASH2,
	G_CRC2,
	G_HSEM,
	G_IPCC,
	G_GPIOA,
	G_GPIOB,
	G_GPIOC,
	G_GPIOD,
	G_GPIOE,
	G_GPIOF,
	G_GPIOG,
	G_GPIOH,
	G_GPIOI,
	G_GPIOJ,
	G_GPIOK,
	G_MDMA,
	G_ETHCK,
	G_ETHTX,
	G_ETHRX,
	G_ETHMAC,
	G_CRC1,
	G_USBH,
	G_ETHSTP,
	G_RTCAPB,
	G_TZC1,
	G_TZC2,
	G_TZPC,
	G_IWDG1,
	G_BSEC,
	G_GPIOZ,
	G_CRYP1,
	G_HASH1,
	G_BKPSRAM,
	G_DDRPERFM,

	G_LAST
पूर्ण;

अटल काष्ठा sपंचांग32_mgate mp1_mgate[G_LAST];

#घोषणा _K_GATE(_id, _gate_offset, _gate_bit_idx, _gate_flags,\
	       _mgate, _ops)\
	[_id] = अणु\
		&(काष्ठा gate_cfg) अणु\
			.reg_off	= _gate_offset,\
			.bit_idx	= _gate_bit_idx,\
			.gate_flags	= _gate_flags,\
		पूर्ण,\
		.mgate		= _mgate,\
		.ops		= _ops,\
	पूर्ण

#घोषणा K_GATE(_id, _gate_offset, _gate_bit_idx, _gate_flags)\
	_K_GATE(_id, _gate_offset, _gate_bit_idx, _gate_flags,\
	       शून्य, &mp1_gate_clk_ops)

#घोषणा K_MGATE(_id, _gate_offset, _gate_bit_idx, _gate_flags)\
	_K_GATE(_id, _gate_offset, _gate_bit_idx, _gate_flags,\
	       &mp1_mgate[_id], &mp1_mgate_clk_ops)

/* Peripheral gates */
अटल काष्ठा sपंचांग32_gate_cfg per_gate_cfg[G_LAST] = अणु
	/* Multi gates */
	K_GATE(G_MDIO,		RCC_APB1ENSETR, 31, 0),
	K_MGATE(G_DAC12,	RCC_APB1ENSETR, 29, 0),
	K_MGATE(G_CEC,		RCC_APB1ENSETR, 27, 0),
	K_MGATE(G_SPDIF,	RCC_APB1ENSETR, 26, 0),
	K_MGATE(G_I2C5,		RCC_APB1ENSETR, 24, 0),
	K_MGATE(G_I2C3,		RCC_APB1ENSETR, 23, 0),
	K_MGATE(G_I2C2,		RCC_APB1ENSETR, 22, 0),
	K_MGATE(G_I2C1,		RCC_APB1ENSETR, 21, 0),
	K_MGATE(G_UART8,	RCC_APB1ENSETR, 19, 0),
	K_MGATE(G_UART7,	RCC_APB1ENSETR, 18, 0),
	K_MGATE(G_UART5,	RCC_APB1ENSETR, 17, 0),
	K_MGATE(G_UART4,	RCC_APB1ENSETR, 16, 0),
	K_MGATE(G_USART3,	RCC_APB1ENSETR, 15, 0),
	K_MGATE(G_USART2,	RCC_APB1ENSETR, 14, 0),
	K_MGATE(G_SPI3,		RCC_APB1ENSETR, 12, 0),
	K_MGATE(G_SPI2,		RCC_APB1ENSETR, 11, 0),
	K_MGATE(G_LPTIM1,	RCC_APB1ENSETR, 9, 0),
	K_GATE(G_TIM14,		RCC_APB1ENSETR, 8, 0),
	K_GATE(G_TIM13,		RCC_APB1ENSETR, 7, 0),
	K_GATE(G_TIM12,		RCC_APB1ENSETR, 6, 0),
	K_GATE(G_TIM7,		RCC_APB1ENSETR, 5, 0),
	K_GATE(G_TIM6,		RCC_APB1ENSETR, 4, 0),
	K_GATE(G_TIM5,		RCC_APB1ENSETR, 3, 0),
	K_GATE(G_TIM4,		RCC_APB1ENSETR, 2, 0),
	K_GATE(G_TIM3,		RCC_APB1ENSETR, 1, 0),
	K_GATE(G_TIM2,		RCC_APB1ENSETR, 0, 0),

	K_MGATE(G_FDCAN,	RCC_APB2ENSETR, 24, 0),
	K_GATE(G_ADFSDM,	RCC_APB2ENSETR, 21, 0),
	K_GATE(G_DFSDM,		RCC_APB2ENSETR, 20, 0),
	K_MGATE(G_SAI3,		RCC_APB2ENSETR, 18, 0),
	K_MGATE(G_SAI2,		RCC_APB2ENSETR, 17, 0),
	K_MGATE(G_SAI1,		RCC_APB2ENSETR, 16, 0),
	K_MGATE(G_USART6,	RCC_APB2ENSETR, 13, 0),
	K_MGATE(G_SPI5,		RCC_APB2ENSETR, 10, 0),
	K_MGATE(G_SPI4,		RCC_APB2ENSETR, 9, 0),
	K_MGATE(G_SPI1,		RCC_APB2ENSETR, 8, 0),
	K_GATE(G_TIM17,		RCC_APB2ENSETR, 4, 0),
	K_GATE(G_TIM16,		RCC_APB2ENSETR, 3, 0),
	K_GATE(G_TIM15,		RCC_APB2ENSETR, 2, 0),
	K_GATE(G_TIM8,		RCC_APB2ENSETR, 1, 0),
	K_GATE(G_TIM1,		RCC_APB2ENSETR, 0, 0),

	K_GATE(G_HDP,		RCC_APB3ENSETR, 20, 0),
	K_GATE(G_PMBCTRL,	RCC_APB3ENSETR, 17, 0),
	K_GATE(G_TMPSENS,	RCC_APB3ENSETR, 16, 0),
	K_GATE(G_VREF,		RCC_APB3ENSETR, 13, 0),
	K_GATE(G_SYSCFG,	RCC_APB3ENSETR, 11, 0),
	K_MGATE(G_SAI4,		RCC_APB3ENSETR, 8, 0),
	K_MGATE(G_LPTIM5,	RCC_APB3ENSETR, 3, 0),
	K_MGATE(G_LPTIM4,	RCC_APB3ENSETR, 2, 0),
	K_MGATE(G_LPTIM3,	RCC_APB3ENSETR, 1, 0),
	K_MGATE(G_LPTIM2,	RCC_APB3ENSETR, 0, 0),

	K_GATE(G_STGENRO,	RCC_APB4ENSETR, 20, 0),
	K_MGATE(G_USBPHY,	RCC_APB4ENSETR, 16, 0),
	K_GATE(G_IWDG2,		RCC_APB4ENSETR, 15, 0),
	K_GATE(G_DDRPERFM,	RCC_APB4ENSETR, 8, 0),
	K_MGATE(G_DSI,		RCC_APB4ENSETR, 4, 0),
	K_MGATE(G_LTDC,		RCC_APB4ENSETR, 0, 0),

	K_GATE(G_STGEN,		RCC_APB5ENSETR, 20, 0),
	K_GATE(G_BSEC,		RCC_APB5ENSETR, 16, 0),
	K_GATE(G_IWDG1,		RCC_APB5ENSETR, 15, 0),
	K_GATE(G_TZPC,		RCC_APB5ENSETR, 13, 0),
	K_GATE(G_TZC2,		RCC_APB5ENSETR, 12, 0),
	K_GATE(G_TZC1,		RCC_APB5ENSETR, 11, 0),
	K_GATE(G_RTCAPB,	RCC_APB5ENSETR, 8, 0),
	K_MGATE(G_USART1,	RCC_APB5ENSETR, 4, 0),
	K_MGATE(G_I2C6,		RCC_APB5ENSETR, 3, 0),
	K_MGATE(G_I2C4,		RCC_APB5ENSETR, 2, 0),
	K_MGATE(G_SPI6,		RCC_APB5ENSETR, 0, 0),

	K_MGATE(G_SDMMC3,	RCC_AHB2ENSETR, 16, 0),
	K_MGATE(G_USBO,		RCC_AHB2ENSETR, 8, 0),
	K_MGATE(G_ADC12,	RCC_AHB2ENSETR, 5, 0),
	K_GATE(G_DMAMUX,	RCC_AHB2ENSETR, 2, 0),
	K_GATE(G_DMA2,		RCC_AHB2ENSETR, 1, 0),
	K_GATE(G_DMA1,		RCC_AHB2ENSETR, 0, 0),

	K_GATE(G_IPCC,		RCC_AHB3ENSETR, 12, 0),
	K_GATE(G_HSEM,		RCC_AHB3ENSETR, 11, 0),
	K_GATE(G_CRC2,		RCC_AHB3ENSETR, 7, 0),
	K_MGATE(G_RNG2,		RCC_AHB3ENSETR, 6, 0),
	K_GATE(G_HASH2,		RCC_AHB3ENSETR, 5, 0),
	K_GATE(G_CRYP2,		RCC_AHB3ENSETR, 4, 0),
	K_GATE(G_DCMI,		RCC_AHB3ENSETR, 0, 0),

	K_GATE(G_GPIOK,		RCC_AHB4ENSETR, 10, 0),
	K_GATE(G_GPIOJ,		RCC_AHB4ENSETR, 9, 0),
	K_GATE(G_GPIOI,		RCC_AHB4ENSETR, 8, 0),
	K_GATE(G_GPIOH,		RCC_AHB4ENSETR, 7, 0),
	K_GATE(G_GPIOG,		RCC_AHB4ENSETR, 6, 0),
	K_GATE(G_GPIOF,		RCC_AHB4ENSETR, 5, 0),
	K_GATE(G_GPIOE,		RCC_AHB4ENSETR, 4, 0),
	K_GATE(G_GPIOD,		RCC_AHB4ENSETR, 3, 0),
	K_GATE(G_GPIOC,		RCC_AHB4ENSETR, 2, 0),
	K_GATE(G_GPIOB,		RCC_AHB4ENSETR, 1, 0),
	K_GATE(G_GPIOA,		RCC_AHB4ENSETR, 0, 0),

	K_GATE(G_BKPSRAM,	RCC_AHB5ENSETR, 8, 0),
	K_MGATE(G_RNG1,		RCC_AHB5ENSETR, 6, 0),
	K_GATE(G_HASH1,		RCC_AHB5ENSETR, 5, 0),
	K_GATE(G_CRYP1,		RCC_AHB5ENSETR, 4, 0),
	K_GATE(G_GPIOZ,		RCC_AHB5ENSETR, 0, 0),

	K_GATE(G_USBH,		RCC_AHB6ENSETR, 24, 0),
	K_GATE(G_CRC1,		RCC_AHB6ENSETR, 20, 0),
	K_MGATE(G_SDMMC2,	RCC_AHB6ENSETR, 17, 0),
	K_MGATE(G_SDMMC1,	RCC_AHB6ENSETR, 16, 0),
	K_MGATE(G_QSPI,		RCC_AHB6ENSETR, 14, 0),
	K_MGATE(G_FMC,		RCC_AHB6ENSETR, 12, 0),
	K_GATE(G_ETHMAC,	RCC_AHB6ENSETR, 10, 0),
	K_GATE(G_ETHRX,		RCC_AHB6ENSETR, 9, 0),
	K_GATE(G_ETHTX,		RCC_AHB6ENSETR, 8, 0),
	K_GATE(G_ETHCK,		RCC_AHB6ENSETR, 7, 0),
	K_MGATE(G_GPU,		RCC_AHB6ENSETR, 5, 0),
	K_GATE(G_MDMA,		RCC_AHB6ENSETR, 0, 0),
	K_GATE(G_ETHSTP,	RCC_AHB6LPENSETR, 11, 0),
पूर्ण;

क्रमागत अणु
	M_SDMMC12,
	M_SDMMC3,
	M_FMC,
	M_QSPI,
	M_RNG1,
	M_RNG2,
	M_USBPHY,
	M_USBO,
	M_STGEN,
	M_SPDIF,
	M_SPI1,
	M_SPI23,
	M_SPI45,
	M_SPI6,
	M_CEC,
	M_I2C12,
	M_I2C35,
	M_I2C46,
	M_LPTIM1,
	M_LPTIM23,
	M_LPTIM45,
	M_USART1,
	M_UART24,
	M_UART35,
	M_USART6,
	M_UART78,
	M_SAI1,
	M_SAI2,
	M_SAI3,
	M_SAI4,
	M_DSI,
	M_FDCAN,
	M_ADC12,
	M_ETHCK,
	M_CKPER,
	M_LAST
पूर्ण;

अटल काष्ठा sपंचांग32_mmux ker_mux[M_LAST];

#घोषणा _K_MUX(_id, _offset, _shअगरt, _width, _mux_flags, _mmux, _ops)\
	[_id] = अणु\
		&(काष्ठा mux_cfg) अणु\
			.reg_off	= _offset,\
			.shअगरt		= _shअगरt,\
			.width		= _width,\
			.mux_flags	= _mux_flags,\
			.table		= शून्य,\
		पूर्ण,\
		.mmux		= _mmux,\
		.ops		= _ops,\
	पूर्ण

#घोषणा K_MUX(_id, _offset, _shअगरt, _width, _mux_flags)\
	_K_MUX(_id, _offset, _shअगरt, _width, _mux_flags,\
			शून्य, शून्य)

#घोषणा K_MMUX(_id, _offset, _shअगरt, _width, _mux_flags)\
	_K_MUX(_id, _offset, _shअगरt, _width, _mux_flags,\
			&ker_mux[_id], &clk_mmux_ops)

अटल स्थिर काष्ठा sपंचांग32_mux_cfg ker_mux_cfg[M_LAST] = अणु
	/* Kernel multi mux */
	K_MMUX(M_SDMMC12, RCC_SDMMC12CKSELR, 0, 3, 0),
	K_MMUX(M_SPI23, RCC_SPI2S23CKSELR, 0, 3, 0),
	K_MMUX(M_SPI45, RCC_SPI2S45CKSELR, 0, 3, 0),
	K_MMUX(M_I2C12, RCC_I2C12CKSELR, 0, 3, 0),
	K_MMUX(M_I2C35, RCC_I2C35CKSELR, 0, 3, 0),
	K_MMUX(M_LPTIM23, RCC_LPTIM23CKSELR, 0, 3, 0),
	K_MMUX(M_LPTIM45, RCC_LPTIM45CKSELR, 0, 3, 0),
	K_MMUX(M_UART24, RCC_UART24CKSELR, 0, 3, 0),
	K_MMUX(M_UART35, RCC_UART35CKSELR, 0, 3, 0),
	K_MMUX(M_UART78, RCC_UART78CKSELR, 0, 3, 0),
	K_MMUX(M_SAI1, RCC_SAI1CKSELR, 0, 3, 0),
	K_MMUX(M_ETHCK, RCC_ETHCKSELR, 0, 2, 0),
	K_MMUX(M_I2C46, RCC_I2C46CKSELR, 0, 3, 0),

	/*  Kernel simple mux */
	K_MUX(M_RNG2, RCC_RNG2CKSELR, 0, 2, 0),
	K_MUX(M_SDMMC3, RCC_SDMMC3CKSELR, 0, 3, 0),
	K_MUX(M_FMC, RCC_FMCCKSELR, 0, 2, 0),
	K_MUX(M_QSPI, RCC_QSPICKSELR, 0, 2, 0),
	K_MUX(M_USBPHY, RCC_USBCKSELR, 0, 2, 0),
	K_MUX(M_USBO, RCC_USBCKSELR, 4, 1, 0),
	K_MUX(M_SPDIF, RCC_SPDIFCKSELR, 0, 2, 0),
	K_MUX(M_SPI1, RCC_SPI2S1CKSELR, 0, 3, 0),
	K_MUX(M_CEC, RCC_CECCKSELR, 0, 2, 0),
	K_MUX(M_LPTIM1, RCC_LPTIM1CKSELR, 0, 3, 0),
	K_MUX(M_USART6, RCC_UART6CKSELR, 0, 3, 0),
	K_MUX(M_FDCAN, RCC_FDCANCKSELR, 0, 2, 0),
	K_MUX(M_SAI2, RCC_SAI2CKSELR, 0, 3, 0),
	K_MUX(M_SAI3, RCC_SAI3CKSELR, 0, 3, 0),
	K_MUX(M_SAI4, RCC_SAI4CKSELR, 0, 3, 0),
	K_MUX(M_ADC12, RCC_ADCCKSELR, 0, 2, 0),
	K_MUX(M_DSI, RCC_DSICKSELR, 0, 1, 0),
	K_MUX(M_CKPER, RCC_CPERCKSELR, 0, 2, 0),
	K_MUX(M_RNG1, RCC_RNG1CKSELR, 0, 2, 0),
	K_MUX(M_STGEN, RCC_STGENCKSELR, 0, 2, 0),
	K_MUX(M_USART1, RCC_UART1CKSELR, 0, 3, 0),
	K_MUX(M_SPI6, RCC_SPI6CKSELR, 0, 3, 0),
पूर्ण;

अटल स्थिर काष्ठा घड़ी_config sपंचांग32mp1_घड़ी_cfg[] = अणु
	/* Oscillator भागider */
	DIV(NO_ID, "clk-hsi-div", "clk-hsi", CLK_DIVIDER_POWER_OF_TWO,
	    RCC_HSICFGR, 0, 2, CLK_DIVIDER_READ_ONLY),

	/*  External / Internal Oscillators */
	GATE_MP1(CK_HSE, "ck_hse", "clk-hse", 0, RCC_OCENSETR, 8, 0),
	/* ck_csi is used by IO compensation and should be critical */
	GATE_MP1(CK_CSI, "ck_csi", "clk-csi", CLK_IS_CRITICAL,
		 RCC_OCENSETR, 4, 0),
	GATE_MP1(CK_HSI, "ck_hsi", "clk-hsi-div", 0, RCC_OCENSETR, 0, 0),
	GATE(CK_LSI, "ck_lsi", "clk-lsi", 0, RCC_RDLSICR, 0, 0),
	GATE(CK_LSE, "ck_lse", "clk-lse", 0, RCC_BDCR, 0, 0),

	FIXED_FACTOR(CK_HSE_DIV2, "clk-hse-div2", "ck_hse", 0, 1, 2),

	/* ref घड़ी pll */
	MUX(NO_ID, "ref1", ref12_parents, CLK_OPS_PARENT_ENABLE, RCC_RCK12SELR,
	    0, 2, CLK_MUX_READ_ONLY),

	MUX(NO_ID, "ref3", ref3_parents, CLK_OPS_PARENT_ENABLE, RCC_RCK3SELR,
	    0, 2, CLK_MUX_READ_ONLY),

	MUX(NO_ID, "ref4", ref4_parents, CLK_OPS_PARENT_ENABLE, RCC_RCK4SELR,
	    0, 2, CLK_MUX_READ_ONLY),

	/* PLLs */
	PLL(PLL1, "pll1", "ref1", CLK_IGNORE_UNUSED, RCC_PLL1CR),
	PLL(PLL2, "pll2", "ref1", CLK_IGNORE_UNUSED, RCC_PLL2CR),
	PLL(PLL3, "pll3", "ref3", CLK_IGNORE_UNUSED, RCC_PLL3CR),
	PLL(PLL4, "pll4", "ref4", CLK_IGNORE_UNUSED, RCC_PLL4CR),

	/* ODF */
	COMPOSITE(PLL1_P, "pll1_p", PARENT("pll1"), 0,
		  _GATE(RCC_PLL1CR, 4, 0),
		  _NO_MUX,
		  _DIV(RCC_PLL1CFGR2, 0, 7, 0, शून्य)),

	COMPOSITE(PLL2_P, "pll2_p", PARENT("pll2"), 0,
		  _GATE(RCC_PLL2CR, 4, 0),
		  _NO_MUX,
		  _DIV(RCC_PLL2CFGR2, 0, 7, 0, शून्य)),

	COMPOSITE(PLL2_Q, "pll2_q", PARENT("pll2"), 0,
		  _GATE(RCC_PLL2CR, 5, 0),
		  _NO_MUX,
		  _DIV(RCC_PLL2CFGR2, 8, 7, 0, शून्य)),

	COMPOSITE(PLL2_R, "pll2_r", PARENT("pll2"), CLK_IS_CRITICAL,
		  _GATE(RCC_PLL2CR, 6, 0),
		  _NO_MUX,
		  _DIV(RCC_PLL2CFGR2, 16, 7, 0, शून्य)),

	COMPOSITE(PLL3_P, "pll3_p", PARENT("pll3"), 0,
		  _GATE(RCC_PLL3CR, 4, 0),
		  _NO_MUX,
		  _DIV(RCC_PLL3CFGR2, 0, 7, 0, शून्य)),

	COMPOSITE(PLL3_Q, "pll3_q", PARENT("pll3"), 0,
		  _GATE(RCC_PLL3CR, 5, 0),
		  _NO_MUX,
		  _DIV(RCC_PLL3CFGR2, 8, 7, 0, शून्य)),

	COMPOSITE(PLL3_R, "pll3_r", PARENT("pll3"), 0,
		  _GATE(RCC_PLL3CR, 6, 0),
		  _NO_MUX,
		  _DIV(RCC_PLL3CFGR2, 16, 7, 0, शून्य)),

	COMPOSITE(PLL4_P, "pll4_p", PARENT("pll4"), 0,
		  _GATE(RCC_PLL4CR, 4, 0),
		  _NO_MUX,
		  _DIV(RCC_PLL4CFGR2, 0, 7, 0, शून्य)),

	COMPOSITE(PLL4_Q, "pll4_q", PARENT("pll4"), 0,
		  _GATE(RCC_PLL4CR, 5, 0),
		  _NO_MUX,
		  _DIV(RCC_PLL4CFGR2, 8, 7, 0, शून्य)),

	COMPOSITE(PLL4_R, "pll4_r", PARENT("pll4"), 0,
		  _GATE(RCC_PLL4CR, 6, 0),
		  _NO_MUX,
		  _DIV(RCC_PLL4CFGR2, 16, 7, 0, शून्य)),

	/* MUX प्रणाली घड़ीs */
	MUX(CK_PER, "ck_per", per_src, CLK_OPS_PARENT_ENABLE,
	    RCC_CPERCKSELR, 0, 2, 0),

	MUX(CK_MPU, "ck_mpu", cpu_src, CLK_OPS_PARENT_ENABLE |
	     CLK_IS_CRITICAL, RCC_MPCKSELR, 0, 2, 0),

	COMPOSITE(CK_AXI, "ck_axi", axi_src, CLK_IS_CRITICAL |
		   CLK_OPS_PARENT_ENABLE,
		   _NO_GATE,
		   _MUX(RCC_ASSCKSELR, 0, 2, 0),
		   _DIV(RCC_AXIDIVR, 0, 3, 0, axi_भाग_प्रकारable)),

	COMPOSITE(CK_MCU, "ck_mcu", mcu_src, CLK_IS_CRITICAL |
		   CLK_OPS_PARENT_ENABLE,
		   _NO_GATE,
		   _MUX(RCC_MSSCKSELR, 0, 2, 0),
		   _DIV(RCC_MCUDIVR, 0, 4, 0, mcu_भाग_प्रकारable)),

	DIV_TABLE(NO_ID, "pclk1", "ck_mcu", CLK_IGNORE_UNUSED, RCC_APB1DIVR, 0,
		  3, CLK_DIVIDER_READ_ONLY, apb_भाग_प्रकारable),

	DIV_TABLE(NO_ID, "pclk2", "ck_mcu", CLK_IGNORE_UNUSED, RCC_APB2DIVR, 0,
		  3, CLK_DIVIDER_READ_ONLY, apb_भाग_प्रकारable),

	DIV_TABLE(NO_ID, "pclk3", "ck_mcu", CLK_IGNORE_UNUSED, RCC_APB3DIVR, 0,
		  3, CLK_DIVIDER_READ_ONLY, apb_भाग_प्रकारable),

	DIV_TABLE(NO_ID, "pclk4", "ck_axi", CLK_IGNORE_UNUSED, RCC_APB4DIVR, 0,
		  3, CLK_DIVIDER_READ_ONLY, apb_भाग_प्रकारable),

	DIV_TABLE(NO_ID, "pclk5", "ck_axi", CLK_IGNORE_UNUSED, RCC_APB5DIVR, 0,
		  3, CLK_DIVIDER_READ_ONLY, apb_भाग_प्रकारable),

	/* Kernel Timers */
	STM32_CKTIM("ck1_tim", "pclk1", 0, RCC_APB1DIVR, RCC_TIMG1PRER),
	STM32_CKTIM("ck2_tim", "pclk2", 0, RCC_APB2DIVR, RCC_TIMG2PRER),

	STM32_TIM(TIM2_K, "tim2_k", "ck1_tim", RCC_APB1ENSETR, 0),
	STM32_TIM(TIM3_K, "tim3_k", "ck1_tim", RCC_APB1ENSETR, 1),
	STM32_TIM(TIM4_K, "tim4_k", "ck1_tim", RCC_APB1ENSETR, 2),
	STM32_TIM(TIM5_K, "tim5_k", "ck1_tim", RCC_APB1ENSETR, 3),
	STM32_TIM(TIM6_K, "tim6_k", "ck1_tim", RCC_APB1ENSETR, 4),
	STM32_TIM(TIM7_K, "tim7_k", "ck1_tim", RCC_APB1ENSETR, 5),
	STM32_TIM(TIM12_K, "tim12_k", "ck1_tim", RCC_APB1ENSETR, 6),
	STM32_TIM(TIM13_K, "tim13_k", "ck1_tim", RCC_APB1ENSETR, 7),
	STM32_TIM(TIM14_K, "tim14_k", "ck1_tim", RCC_APB1ENSETR, 8),
	STM32_TIM(TIM1_K, "tim1_k", "ck2_tim", RCC_APB2ENSETR, 0),
	STM32_TIM(TIM8_K, "tim8_k", "ck2_tim", RCC_APB2ENSETR, 1),
	STM32_TIM(TIM15_K, "tim15_k", "ck2_tim", RCC_APB2ENSETR, 2),
	STM32_TIM(TIM16_K, "tim16_k", "ck2_tim", RCC_APB2ENSETR, 3),
	STM32_TIM(TIM17_K, "tim17_k", "ck2_tim", RCC_APB2ENSETR, 4),

	/* Peripheral घड़ीs */
	PCLK(TIM2, "tim2", "pclk1", CLK_IGNORE_UNUSED, G_TIM2),
	PCLK(TIM3, "tim3", "pclk1", CLK_IGNORE_UNUSED, G_TIM3),
	PCLK(TIM4, "tim4", "pclk1", CLK_IGNORE_UNUSED, G_TIM4),
	PCLK(TIM5, "tim5", "pclk1", CLK_IGNORE_UNUSED, G_TIM5),
	PCLK(TIM6, "tim6", "pclk1", CLK_IGNORE_UNUSED, G_TIM6),
	PCLK(TIM7, "tim7", "pclk1", CLK_IGNORE_UNUSED, G_TIM7),
	PCLK(TIM12, "tim12", "pclk1", CLK_IGNORE_UNUSED, G_TIM12),
	PCLK(TIM13, "tim13", "pclk1", CLK_IGNORE_UNUSED, G_TIM13),
	PCLK(TIM14, "tim14", "pclk1", CLK_IGNORE_UNUSED, G_TIM14),
	PCLK(LPTIM1, "lptim1", "pclk1", 0, G_LPTIM1),
	PCLK(SPI2, "spi2", "pclk1", 0, G_SPI2),
	PCLK(SPI3, "spi3", "pclk1", 0, G_SPI3),
	PCLK(USART2, "usart2", "pclk1", 0, G_USART2),
	PCLK(USART3, "usart3", "pclk1", 0, G_USART3),
	PCLK(UART4, "uart4", "pclk1", 0, G_UART4),
	PCLK(UART5, "uart5", "pclk1", 0, G_UART5),
	PCLK(UART7, "uart7", "pclk1", 0, G_UART7),
	PCLK(UART8, "uart8", "pclk1", 0, G_UART8),
	PCLK(I2C1, "i2c1", "pclk1", 0, G_I2C1),
	PCLK(I2C2, "i2c2", "pclk1", 0, G_I2C2),
	PCLK(I2C3, "i2c3", "pclk1", 0, G_I2C3),
	PCLK(I2C5, "i2c5", "pclk1", 0, G_I2C5),
	PCLK(SPDIF, "spdif", "pclk1", 0, G_SPDIF),
	PCLK(CEC, "cec", "pclk1", 0, G_CEC),
	PCLK(DAC12, "dac12", "pclk1", 0, G_DAC12),
	PCLK(MDIO, "mdio", "pclk1", 0, G_MDIO),
	PCLK(TIM1, "tim1", "pclk2", CLK_IGNORE_UNUSED, G_TIM1),
	PCLK(TIM8, "tim8", "pclk2", CLK_IGNORE_UNUSED, G_TIM8),
	PCLK(TIM15, "tim15", "pclk2", CLK_IGNORE_UNUSED, G_TIM15),
	PCLK(TIM16, "tim16", "pclk2", CLK_IGNORE_UNUSED, G_TIM16),
	PCLK(TIM17, "tim17", "pclk2", CLK_IGNORE_UNUSED, G_TIM17),
	PCLK(SPI1, "spi1", "pclk2", 0, G_SPI1),
	PCLK(SPI4, "spi4", "pclk2", 0, G_SPI4),
	PCLK(SPI5, "spi5", "pclk2", 0, G_SPI5),
	PCLK(USART6, "usart6", "pclk2", 0, G_USART6),
	PCLK(SAI1, "sai1", "pclk2", 0, G_SAI1),
	PCLK(SAI2, "sai2", "pclk2", 0, G_SAI2),
	PCLK(SAI3, "sai3", "pclk2", 0, G_SAI3),
	PCLK(DFSDM, "dfsdm", "pclk2", 0, G_DFSDM),
	PCLK(FDCAN, "fdcan", "pclk2", 0, G_FDCAN),
	PCLK(LPTIM2, "lptim2", "pclk3", 0, G_LPTIM2),
	PCLK(LPTIM3, "lptim3", "pclk3", 0, G_LPTIM3),
	PCLK(LPTIM4, "lptim4", "pclk3", 0, G_LPTIM4),
	PCLK(LPTIM5, "lptim5", "pclk3", 0, G_LPTIM5),
	PCLK(SAI4, "sai4", "pclk3", 0, G_SAI4),
	PCLK(SYSCFG, "syscfg", "pclk3", 0, G_SYSCFG),
	PCLK(VREF, "vref", "pclk3", 13, G_VREF),
	PCLK(TMPSENS, "tmpsens", "pclk3", 0, G_TMPSENS),
	PCLK(PMBCTRL, "pmbctrl", "pclk3", 0, G_PMBCTRL),
	PCLK(HDP, "hdp", "pclk3", 0, G_HDP),
	PCLK(LTDC, "ltdc", "pclk4", 0, G_LTDC),
	PCLK(DSI, "dsi", "pclk4", 0, G_DSI),
	PCLK(IWDG2, "iwdg2", "pclk4", 0, G_IWDG2),
	PCLK(USBPHY, "usbphy", "pclk4", 0, G_USBPHY),
	PCLK(STGENRO, "stgenro", "pclk4", 0, G_STGENRO),
	PCLK(SPI6, "spi6", "pclk5", 0, G_SPI6),
	PCLK(I2C4, "i2c4", "pclk5", 0, G_I2C4),
	PCLK(I2C6, "i2c6", "pclk5", 0, G_I2C6),
	PCLK(USART1, "usart1", "pclk5", 0, G_USART1),
	PCLK(RTCAPB, "rtcapb", "pclk5", CLK_IGNORE_UNUSED |
	     CLK_IS_CRITICAL, G_RTCAPB),
	PCLK(TZC1, "tzc1", "ck_axi", CLK_IGNORE_UNUSED, G_TZC1),
	PCLK(TZC2, "tzc2", "ck_axi", CLK_IGNORE_UNUSED, G_TZC2),
	PCLK(TZPC, "tzpc", "pclk5", CLK_IGNORE_UNUSED, G_TZPC),
	PCLK(IWDG1, "iwdg1", "pclk5", 0, G_IWDG1),
	PCLK(BSEC, "bsec", "pclk5", CLK_IGNORE_UNUSED, G_BSEC),
	PCLK(STGEN, "stgen", "pclk5", CLK_IGNORE_UNUSED, G_STGEN),
	PCLK(DMA1, "dma1", "ck_mcu", 0, G_DMA1),
	PCLK(DMA2, "dma2", "ck_mcu",  0, G_DMA2),
	PCLK(DMAMUX, "dmamux", "ck_mcu", 0, G_DMAMUX),
	PCLK(ADC12, "adc12", "ck_mcu", 0, G_ADC12),
	PCLK(USBO, "usbo", "ck_mcu", 0, G_USBO),
	PCLK(SDMMC3, "sdmmc3", "ck_mcu", 0, G_SDMMC3),
	PCLK(DCMI, "dcmi", "ck_mcu", 0, G_DCMI),
	PCLK(CRYP2, "cryp2", "ck_mcu", 0, G_CRYP2),
	PCLK(HASH2, "hash2", "ck_mcu", 0, G_HASH2),
	PCLK(RNG2, "rng2", "ck_mcu", 0, G_RNG2),
	PCLK(CRC2, "crc2", "ck_mcu", 0, G_CRC2),
	PCLK(HSEM, "hsem", "ck_mcu", 0, G_HSEM),
	PCLK(IPCC, "ipcc", "ck_mcu", 0, G_IPCC),
	PCLK(GPIOA, "gpioa", "ck_mcu", 0, G_GPIOA),
	PCLK(GPIOB, "gpiob", "ck_mcu", 0, G_GPIOB),
	PCLK(GPIOC, "gpioc", "ck_mcu", 0, G_GPIOC),
	PCLK(GPIOD, "gpiod", "ck_mcu", 0, G_GPIOD),
	PCLK(GPIOE, "gpioe", "ck_mcu", 0, G_GPIOE),
	PCLK(GPIOF, "gpiof", "ck_mcu", 0, G_GPIOF),
	PCLK(GPIOG, "gpiog", "ck_mcu", 0, G_GPIOG),
	PCLK(GPIOH, "gpioh", "ck_mcu", 0, G_GPIOH),
	PCLK(GPIOI, "gpioi", "ck_mcu", 0, G_GPIOI),
	PCLK(GPIOJ, "gpioj", "ck_mcu", 0, G_GPIOJ),
	PCLK(GPIOK, "gpiok", "ck_mcu", 0, G_GPIOK),
	PCLK(GPIOZ, "gpioz", "ck_axi", CLK_IGNORE_UNUSED, G_GPIOZ),
	PCLK(CRYP1, "cryp1", "ck_axi", CLK_IGNORE_UNUSED, G_CRYP1),
	PCLK(HASH1, "hash1", "ck_axi", CLK_IGNORE_UNUSED, G_HASH1),
	PCLK(RNG1, "rng1", "ck_axi", 0, G_RNG1),
	PCLK(BKPSRAM, "bkpsram", "ck_axi", CLK_IGNORE_UNUSED, G_BKPSRAM),
	PCLK(MDMA, "mdma", "ck_axi", 0, G_MDMA),
	PCLK(GPU, "gpu", "ck_axi", 0, G_GPU),
	PCLK(ETHTX, "ethtx", "ck_axi", 0, G_ETHTX),
	PCLK(ETHRX, "ethrx", "ck_axi", 0, G_ETHRX),
	PCLK(ETHMAC, "ethmac", "ck_axi", 0, G_ETHMAC),
	PCLK(FMC, "fmc", "ck_axi", CLK_IGNORE_UNUSED, G_FMC),
	PCLK(QSPI, "qspi", "ck_axi", CLK_IGNORE_UNUSED, G_QSPI),
	PCLK(SDMMC1, "sdmmc1", "ck_axi", 0, G_SDMMC1),
	PCLK(SDMMC2, "sdmmc2", "ck_axi", 0, G_SDMMC2),
	PCLK(CRC1, "crc1", "ck_axi", 0, G_CRC1),
	PCLK(USBH, "usbh", "ck_axi", 0, G_USBH),
	PCLK(ETHSTP, "ethstp", "ck_axi", 0, G_ETHSTP),
	PCLK(DDRPERFM, "ddrperfm", "pclk4", 0, G_DDRPERFM),

	/* Kernel घड़ीs */
	KCLK(SDMMC1_K, "sdmmc1_k", sdmmc12_src, 0, G_SDMMC1, M_SDMMC12),
	KCLK(SDMMC2_K, "sdmmc2_k", sdmmc12_src, 0, G_SDMMC2, M_SDMMC12),
	KCLK(SDMMC3_K, "sdmmc3_k", sdmmc3_src, 0, G_SDMMC3, M_SDMMC3),
	KCLK(FMC_K, "fmc_k", fmc_src, 0, G_FMC, M_FMC),
	KCLK(QSPI_K, "qspi_k", qspi_src, 0, G_QSPI, M_QSPI),
	KCLK(RNG1_K, "rng1_k", rng_src, 0, G_RNG1, M_RNG1),
	KCLK(RNG2_K, "rng2_k", rng_src, 0, G_RNG2, M_RNG2),
	KCLK(USBPHY_K, "usbphy_k", usbphy_src, 0, G_USBPHY, M_USBPHY),
	KCLK(STGEN_K, "stgen_k", stgen_src, CLK_IS_CRITICAL, G_STGEN, M_STGEN),
	KCLK(SPDIF_K, "spdif_k", spdअगर_src, 0, G_SPDIF, M_SPDIF),
	KCLK(SPI1_K, "spi1_k", spi123_src, 0, G_SPI1, M_SPI1),
	KCLK(SPI2_K, "spi2_k", spi123_src, 0, G_SPI2, M_SPI23),
	KCLK(SPI3_K, "spi3_k", spi123_src, 0, G_SPI3, M_SPI23),
	KCLK(SPI4_K, "spi4_k", spi45_src, 0, G_SPI4, M_SPI45),
	KCLK(SPI5_K, "spi5_k", spi45_src, 0, G_SPI5, M_SPI45),
	KCLK(SPI6_K, "spi6_k", spi6_src, 0, G_SPI6, M_SPI6),
	KCLK(CEC_K, "cec_k", cec_src, 0, G_CEC, M_CEC),
	KCLK(I2C1_K, "i2c1_k", i2c12_src, 0, G_I2C1, M_I2C12),
	KCLK(I2C2_K, "i2c2_k", i2c12_src, 0, G_I2C2, M_I2C12),
	KCLK(I2C3_K, "i2c3_k", i2c35_src, 0, G_I2C3, M_I2C35),
	KCLK(I2C5_K, "i2c5_k", i2c35_src, 0, G_I2C5, M_I2C35),
	KCLK(I2C4_K, "i2c4_k", i2c46_src, 0, G_I2C4, M_I2C46),
	KCLK(I2C6_K, "i2c6_k", i2c46_src, 0, G_I2C6, M_I2C46),
	KCLK(LPTIM1_K, "lptim1_k", lptim1_src, 0, G_LPTIM1, M_LPTIM1),
	KCLK(LPTIM2_K, "lptim2_k", lptim23_src, 0, G_LPTIM2, M_LPTIM23),
	KCLK(LPTIM3_K, "lptim3_k", lptim23_src, 0, G_LPTIM3, M_LPTIM23),
	KCLK(LPTIM4_K, "lptim4_k", lptim45_src, 0, G_LPTIM4, M_LPTIM45),
	KCLK(LPTIM5_K, "lptim5_k", lptim45_src, 0, G_LPTIM5, M_LPTIM45),
	KCLK(USART1_K, "usart1_k", usart1_src, 0, G_USART1, M_USART1),
	KCLK(USART2_K, "usart2_k", usart234578_src, 0, G_USART2, M_UART24),
	KCLK(USART3_K, "usart3_k", usart234578_src, 0, G_USART3, M_UART35),
	KCLK(UART4_K, "uart4_k", usart234578_src, 0, G_UART4, M_UART24),
	KCLK(UART5_K, "uart5_k", usart234578_src, 0, G_UART5, M_UART35),
	KCLK(USART6_K, "uart6_k", usart6_src, 0, G_USART6, M_USART6),
	KCLK(UART7_K, "uart7_k", usart234578_src, 0, G_UART7, M_UART78),
	KCLK(UART8_K, "uart8_k", usart234578_src, 0, G_UART8, M_UART78),
	KCLK(FDCAN_K, "fdcan_k", fdcan_src, 0, G_FDCAN, M_FDCAN),
	KCLK(SAI1_K, "sai1_k", sai_src, 0, G_SAI1, M_SAI1),
	KCLK(SAI2_K, "sai2_k", sai2_src, 0, G_SAI2, M_SAI2),
	KCLK(SAI3_K, "sai3_k", sai_src, 0, G_SAI3, M_SAI3),
	KCLK(SAI4_K, "sai4_k", sai_src, 0, G_SAI4, M_SAI4),
	KCLK(ADC12_K, "adc12_k", adc12_src, 0, G_ADC12, M_ADC12),
	KCLK(DSI_K, "dsi_k", dsi_src, 0, G_DSI, M_DSI),
	KCLK(ADFSDM_K, "adfsdm_k", sai_src, 0, G_ADFSDM, M_SAI1),
	KCLK(USBO_K, "usbo_k", usbo_src, 0, G_USBO, M_USBO),
	KCLK(ETHCK_K, "ethck_k", eth_src, 0, G_ETHCK, M_ETHCK),

	/* Particulary Kernel Clocks (no mux or no gate) */
	MGATE_MP1(DFSDM_K, "dfsdm_k", "ck_mcu", 0, G_DFSDM),
	MGATE_MP1(DSI_PX, "dsi_px", "pll4_q", CLK_SET_RATE_PARENT, G_DSI),
	MGATE_MP1(LTDC_PX, "ltdc_px", "pll4_q", CLK_SET_RATE_PARENT, G_LTDC),
	MGATE_MP1(GPU_K, "gpu_k", "pll2_q", 0, G_GPU),
	MGATE_MP1(DAC12_K, "dac12_k", "ck_lsi", 0, G_DAC12),

	COMPOSITE(ETHPTP_K, "ethptp_k", eth_src, CLK_OPS_PARENT_ENABLE |
		  CLK_SET_RATE_NO_REPARENT,
		  _NO_GATE,
		  _MMUX(M_ETHCK),
		  _DIV(RCC_ETHCKSELR, 4, 4, 0, शून्य)),

	/* RTC घड़ी */
	DIV(NO_ID, "ck_hse_rtc", "ck_hse", 0, RCC_RTCDIVR, 0, 6, 0),

	COMPOSITE(RTC, "ck_rtc", rtc_src, CLK_OPS_PARENT_ENABLE |
		   CLK_SET_RATE_PARENT,
		  _GATE(RCC_BDCR, 20, 0),
		  _MUX(RCC_BDCR, 16, 2, 0),
		  _NO_DIV),

	/* MCO घड़ीs */
	COMPOSITE(CK_MCO1, "ck_mco1", mco1_src, CLK_OPS_PARENT_ENABLE |
		  CLK_SET_RATE_NO_REPARENT,
		  _GATE(RCC_MCO1CFGR, 12, 0),
		  _MUX(RCC_MCO1CFGR, 0, 3, 0),
		  _DIV(RCC_MCO1CFGR, 4, 4, 0, शून्य)),

	COMPOSITE(CK_MCO2, "ck_mco2", mco2_src, CLK_OPS_PARENT_ENABLE |
		  CLK_SET_RATE_NO_REPARENT,
		  _GATE(RCC_MCO2CFGR, 12, 0),
		  _MUX(RCC_MCO2CFGR, 0, 3, 0),
		  _DIV(RCC_MCO2CFGR, 4, 4, 0, शून्य)),

	/* Debug घड़ीs */
	GATE(CK_DBG, "ck_sys_dbg", "ck_axi", CLK_IGNORE_UNUSED,
	     RCC_DBGCFGR, 8, 0),

	COMPOSITE(CK_TRACE, "ck_trace", ck_trace_src, CLK_OPS_PARENT_ENABLE,
		  _GATE(RCC_DBGCFGR, 9, 0),
		  _NO_MUX,
		  _DIV(RCC_DBGCFGR, 0, 3, 0, ck_trace_भाग_प्रकारable)),
पूर्ण;

काष्ठा sपंचांग32_घड़ी_match_data अणु
	स्थिर काष्ठा घड़ी_config *cfg;
	अचिन्हित पूर्णांक num;
	अचिन्हित पूर्णांक maxbinding;
पूर्ण;

अटल काष्ठा sपंचांग32_घड़ी_match_data sपंचांग32mp1_data = अणु
	.cfg		= sपंचांग32mp1_घड़ी_cfg,
	.num		= ARRAY_SIZE(sपंचांग32mp1_घड़ी_cfg),
	.maxbinding	= STM32MP1_LAST_CLK,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32mp1_match_data[] = अणु
	अणु
		.compatible = "st,stm32mp1-rcc",
		.data = &sपंचांग32mp1_data,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक sपंचांग32_रेजिस्टर_hw_clk(काष्ठा device *dev,
				 काष्ठा clk_hw_onecell_data *clk_data,
				 व्योम __iomem *base, spinlock_t *lock,
				 स्थिर काष्ठा घड़ी_config *cfg)
अणु
	काष्ठा clk_hw **hws;
	काष्ठा clk_hw *hw = ERR_PTR(-ENOENT);

	hws = clk_data->hws;

	अगर (cfg->func)
		hw = (*cfg->func)(dev, clk_data, base, lock, cfg);

	अगर (IS_ERR(hw)) अणु
		pr_err("Unable to register %s\n", cfg->name);
		वापस  PTR_ERR(hw);
	पूर्ण

	अगर (cfg->id != NO_ID)
		hws[cfg->id] = hw;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_rcc_init(काष्ठा device_node *np,
			  व्योम __iomem *base,
			  स्थिर काष्ठा of_device_id *match_data)
अणु
	काष्ठा clk_hw_onecell_data *clk_data;
	काष्ठा clk_hw **hws;
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा sपंचांग32_घड़ी_match_data *data;
	पूर्णांक err, n, max_binding;

	match = of_match_node(match_data, np);
	अगर (!match) अणु
		pr_err("%s: match data not found\n", __func__);
		वापस -ENODEV;
	पूर्ण

	data = match->data;

	max_binding =  data->maxbinding;

	clk_data = kzalloc(काष्ठा_size(clk_data, hws, max_binding),
			   GFP_KERNEL);
	अगर (!clk_data)
		वापस -ENOMEM;

	clk_data->num = max_binding;

	hws = clk_data->hws;

	क्रम (n = 0; n < max_binding; n++)
		hws[n] = ERR_PTR(-ENOENT);

	क्रम (n = 0; n < data->num; n++) अणु
		err = sपंचांग32_रेजिस्टर_hw_clk(शून्य, clk_data, base, &rlock,
					    &data->cfg[n]);
		अगर (err) अणु
			pr_err("%s: can't register  %s\n", __func__,
			       data->cfg[n].name);

			kमुक्त(clk_data);

			वापस err;
		पूर्ण
	पूर्ण

	वापस of_clk_add_hw_provider(np, of_clk_hw_onecell_get, clk_data);
पूर्ण

अटल व्योम sपंचांग32mp1_rcc_init(काष्ठा device_node *np)
अणु
	व्योम __iomem *base;

	base = of_iomap(np, 0);
	अगर (!base) अणु
		pr_err("%pOFn: unable to map resource", np);
		of_node_put(np);
		वापस;
	पूर्ण

	अगर (sपंचांग32_rcc_init(np, base, sपंचांग32mp1_match_data)) अणु
		iounmap(base);
		of_node_put(np);
	पूर्ण
पूर्ण

CLK_OF_DECLARE_DRIVER(sपंचांग32mp1_rcc, "st,stm32mp1-rcc", sपंचांग32mp1_rcc_init);
