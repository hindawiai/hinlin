<शैली गुरु>
/*
 * Clk driver क्रम NXP LPC18xx/LPC43xx Clock Generation Unit (CGU)
 *
 * Copyright (C) 2015 Joachim Eastwood <manabian@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश <dt-bindings/घड़ी/lpc18xx-cgu.h>

/* Clock Generation Unit (CGU) रेजिस्टरs */
#घोषणा LPC18XX_CGU_XTAL_OSC_CTRL	0x018
#घोषणा LPC18XX_CGU_PLL0USB_STAT	0x01c
#घोषणा LPC18XX_CGU_PLL0USB_CTRL	0x020
#घोषणा LPC18XX_CGU_PLL0USB_MDIV	0x024
#घोषणा LPC18XX_CGU_PLL0USB_NP_DIV	0x028
#घोषणा LPC18XX_CGU_PLL0AUDIO_STAT	0x02c
#घोषणा LPC18XX_CGU_PLL0AUDIO_CTRL	0x030
#घोषणा LPC18XX_CGU_PLL0AUDIO_MDIV	0x034
#घोषणा LPC18XX_CGU_PLL0AUDIO_NP_DIV	0x038
#घोषणा LPC18XX_CGU_PLL0AUDIO_FRAC	0x03c
#घोषणा LPC18XX_CGU_PLL1_STAT		0x040
#घोषणा LPC18XX_CGU_PLL1_CTRL		0x044
#घोषणा  LPC18XX_PLL1_CTRL_FBSEL	BIT(6)
#घोषणा  LPC18XX_PLL1_CTRL_सूचीECT	BIT(7)
#घोषणा LPC18XX_CGU_IDIV_CTRL(n)	(0x048 + (n) * माप(u32))
#घोषणा LPC18XX_CGU_BASE_CLK(id)	(0x05c + (id) * माप(u32))
#घोषणा LPC18XX_CGU_PLL_CTRL_OFFSET	0x4

/* PLL0 bits common to both audio and USB PLL */
#घोषणा LPC18XX_PLL0_STAT_LOCK		BIT(0)
#घोषणा LPC18XX_PLL0_CTRL_PD		BIT(0)
#घोषणा LPC18XX_PLL0_CTRL_BYPASS	BIT(1)
#घोषणा LPC18XX_PLL0_CTRL_सूचीECTI	BIT(2)
#घोषणा LPC18XX_PLL0_CTRL_सूचीECTO	BIT(3)
#घोषणा LPC18XX_PLL0_CTRL_CLKEN		BIT(4)
#घोषणा LPC18XX_PLL0_MDIV_MDEC_MASK	0x1ffff
#घोषणा LPC18XX_PLL0_MDIV_SELP_SHIFT	17
#घोषणा LPC18XX_PLL0_MDIV_SELI_SHIFT	22
#घोषणा LPC18XX_PLL0_MSEL_MAX		BIT(15)

/* Register value that gives PLL0 post/pre भागiders equal to 1 */
#घोषणा LPC18XX_PLL0_NP_DIVS_1		0x00302062

क्रमागत अणु
	CLK_SRC_OSC32,
	CLK_SRC_IRC,
	CLK_SRC_ENET_RX_CLK,
	CLK_SRC_ENET_TX_CLK,
	CLK_SRC_GP_CLKIN,
	CLK_SRC_RESERVED1,
	CLK_SRC_OSC,
	CLK_SRC_PLL0USB,
	CLK_SRC_PLL0AUDIO,
	CLK_SRC_PLL1,
	CLK_SRC_RESERVED2,
	CLK_SRC_RESERVED3,
	CLK_SRC_IDIVA,
	CLK_SRC_IDIVB,
	CLK_SRC_IDIVC,
	CLK_SRC_IDIVD,
	CLK_SRC_IDIVE,
	CLK_SRC_MAX
पूर्ण;

अटल स्थिर अक्षर *clk_src_names[CLK_SRC_MAX] = अणु
	[CLK_SRC_OSC32]		= "osc32",
	[CLK_SRC_IRC]		= "irc",
	[CLK_SRC_ENET_RX_CLK]	= "enet_rx_clk",
	[CLK_SRC_ENET_TX_CLK]	= "enet_tx_clk",
	[CLK_SRC_GP_CLKIN]	= "gp_clkin",
	[CLK_SRC_OSC]		= "osc",
	[CLK_SRC_PLL0USB]	= "pll0usb",
	[CLK_SRC_PLL0AUDIO]	= "pll0audio",
	[CLK_SRC_PLL1]		= "pll1",
	[CLK_SRC_IDIVA]		= "idiva",
	[CLK_SRC_IDIVB]		= "idivb",
	[CLK_SRC_IDIVC]		= "idivc",
	[CLK_SRC_IDIVD]		= "idivd",
	[CLK_SRC_IDIVE]		= "idive",
पूर्ण;

अटल स्थिर अक्षर *clk_base_names[BASE_CLK_MAX] = अणु
	[BASE_SAFE_CLK]		= "base_safe_clk",
	[BASE_USB0_CLK]		= "base_usb0_clk",
	[BASE_PERIPH_CLK]	= "base_periph_clk",
	[BASE_USB1_CLK]		= "base_usb1_clk",
	[BASE_CPU_CLK]		= "base_cpu_clk",
	[BASE_SPIFI_CLK]	= "base_spifi_clk",
	[BASE_SPI_CLK]		= "base_spi_clk",
	[BASE_PHY_RX_CLK]	= "base_phy_rx_clk",
	[BASE_PHY_TX_CLK]	= "base_phy_tx_clk",
	[BASE_APB1_CLK]		= "base_apb1_clk",
	[BASE_APB3_CLK]		= "base_apb3_clk",
	[BASE_LCD_CLK]		= "base_lcd_clk",
	[BASE_ADCHS_CLK]	= "base_adchs_clk",
	[BASE_SDIO_CLK]		= "base_sdio_clk",
	[BASE_SSP0_CLK]		= "base_ssp0_clk",
	[BASE_SSP1_CLK]		= "base_ssp1_clk",
	[BASE_UART0_CLK]	= "base_uart0_clk",
	[BASE_UART1_CLK]	= "base_uart1_clk",
	[BASE_UART2_CLK]	= "base_uart2_clk",
	[BASE_UART3_CLK]	= "base_uart3_clk",
	[BASE_OUT_CLK]		= "base_out_clk",
	[BASE_AUDIO_CLK]	= "base_audio_clk",
	[BASE_CGU_OUT0_CLK]	= "base_cgu_out0_clk",
	[BASE_CGU_OUT1_CLK]	= "base_cgu_out1_clk",
पूर्ण;

अटल u32 lpc18xx_cgu_pll0_src_ids[] = अणु
	CLK_SRC_OSC32, CLK_SRC_IRC, CLK_SRC_ENET_RX_CLK,
	CLK_SRC_ENET_TX_CLK, CLK_SRC_GP_CLKIN, CLK_SRC_OSC,
	CLK_SRC_PLL1, CLK_SRC_IDIVA, CLK_SRC_IDIVB, CLK_SRC_IDIVC,
	CLK_SRC_IDIVD, CLK_SRC_IDIVE,
पूर्ण;

अटल u32 lpc18xx_cgu_pll1_src_ids[] = अणु
	CLK_SRC_OSC32, CLK_SRC_IRC, CLK_SRC_ENET_RX_CLK,
	CLK_SRC_ENET_TX_CLK, CLK_SRC_GP_CLKIN, CLK_SRC_OSC,
	CLK_SRC_PLL0USB, CLK_SRC_PLL0AUDIO, CLK_SRC_IDIVA,
	CLK_SRC_IDIVB, CLK_SRC_IDIVC, CLK_SRC_IDIVD, CLK_SRC_IDIVE,
पूर्ण;

अटल u32 lpc18xx_cgu_iभागa_src_ids[] = अणु
	CLK_SRC_OSC32, CLK_SRC_IRC, CLK_SRC_ENET_RX_CLK,
	CLK_SRC_ENET_TX_CLK, CLK_SRC_GP_CLKIN, CLK_SRC_OSC,
	CLK_SRC_PLL0USB, CLK_SRC_PLL0AUDIO, CLK_SRC_PLL1
पूर्ण;

अटल u32 lpc18xx_cgu_iभागbcde_src_ids[] = अणु
	CLK_SRC_OSC32, CLK_SRC_IRC, CLK_SRC_ENET_RX_CLK,
	CLK_SRC_ENET_TX_CLK, CLK_SRC_GP_CLKIN, CLK_SRC_OSC,
	CLK_SRC_PLL0AUDIO, CLK_SRC_PLL1, CLK_SRC_IDIVA,
पूर्ण;

अटल u32 lpc18xx_cgu_base_irc_src_ids[] = अणुCLK_SRC_IRCपूर्ण;

अटल u32 lpc18xx_cgu_base_usb0_src_ids[] = अणुCLK_SRC_PLL0USBपूर्ण;

अटल u32 lpc18xx_cgu_base_common_src_ids[] = अणु
	CLK_SRC_OSC32, CLK_SRC_IRC, CLK_SRC_ENET_RX_CLK,
	CLK_SRC_ENET_TX_CLK, CLK_SRC_GP_CLKIN, CLK_SRC_OSC,
	CLK_SRC_PLL0AUDIO, CLK_SRC_PLL1, CLK_SRC_IDIVA,
	CLK_SRC_IDIVB, CLK_SRC_IDIVC, CLK_SRC_IDIVD, CLK_SRC_IDIVE,
पूर्ण;

अटल u32 lpc18xx_cgu_base_all_src_ids[] = अणु
	CLK_SRC_OSC32, CLK_SRC_IRC, CLK_SRC_ENET_RX_CLK,
	CLK_SRC_ENET_TX_CLK, CLK_SRC_GP_CLKIN, CLK_SRC_OSC,
	CLK_SRC_PLL0USB, CLK_SRC_PLL0AUDIO, CLK_SRC_PLL1,
	CLK_SRC_IDIVA, CLK_SRC_IDIVB, CLK_SRC_IDIVC,
	CLK_SRC_IDIVD, CLK_SRC_IDIVE,
पूर्ण;

काष्ठा lpc18xx_cgu_src_clk_भाग अणु
	u8 clk_id;
	u8 n_parents;
	काष्ठा clk_भागider	भाग;
	काष्ठा clk_mux		mux;
	काष्ठा clk_gate		gate;
पूर्ण;

#घोषणा LPC1XX_CGU_SRC_CLK_DIV(_id, _width, _table)	\
अणु							\
	.clk_id = CLK_SRC_ ##_id,			\
	.n_parents = ARRAY_SIZE(lpc18xx_cgu_ ##_table),	\
	.भाग = अणु					\
		.shअगरt = 2,				\
		.width = _width,			\
	पूर्ण,						\
	.mux = अणु					\
		.mask = 0x1f,				\
		.shअगरt = 24,				\
		.table = lpc18xx_cgu_ ##_table,		\
	पूर्ण,						\
	.gate = अणु					\
		.bit_idx = 0,				\
		.flags = CLK_GATE_SET_TO_DISABLE,	\
	पूर्ण,						\
पूर्ण

अटल काष्ठा lpc18xx_cgu_src_clk_भाग lpc18xx_cgu_src_clk_भागs[] = अणु
	LPC1XX_CGU_SRC_CLK_DIV(IDIVA, 2, iभागa_src_ids),
	LPC1XX_CGU_SRC_CLK_DIV(IDIVB, 4, iभागbcde_src_ids),
	LPC1XX_CGU_SRC_CLK_DIV(IDIVC, 4, iभागbcde_src_ids),
	LPC1XX_CGU_SRC_CLK_DIV(IDIVD, 4, iभागbcde_src_ids),
	LPC1XX_CGU_SRC_CLK_DIV(IDIVE, 8, iभागbcde_src_ids),
पूर्ण;

काष्ठा lpc18xx_cgu_base_clk अणु
	u8 clk_id;
	u8 n_parents;
	काष्ठा clk_mux mux;
	काष्ठा clk_gate gate;
पूर्ण;

#घोषणा LPC1XX_CGU_BASE_CLK(_id, _table, _flags)	\
अणु							\
	.clk_id = BASE_ ##_id ##_CLK,			\
	.n_parents = ARRAY_SIZE(lpc18xx_cgu_ ##_table),	\
	.mux = अणु					\
		.mask = 0x1f,				\
		.shअगरt = 24,				\
		.table = lpc18xx_cgu_ ##_table,		\
		.flags = _flags,			\
	पूर्ण,						\
	.gate = अणु					\
		.bit_idx = 0,				\
		.flags = CLK_GATE_SET_TO_DISABLE,	\
	पूर्ण,						\
पूर्ण

अटल काष्ठा lpc18xx_cgu_base_clk lpc18xx_cgu_base_clks[] = अणु
	LPC1XX_CGU_BASE_CLK(SAFE,	base_irc_src_ids, CLK_MUX_READ_ONLY),
	LPC1XX_CGU_BASE_CLK(USB0,	base_usb0_src_ids,   0),
	LPC1XX_CGU_BASE_CLK(PERIPH,	base_common_src_ids, 0),
	LPC1XX_CGU_BASE_CLK(USB1,	base_all_src_ids,    0),
	LPC1XX_CGU_BASE_CLK(CPU,	base_common_src_ids, 0),
	LPC1XX_CGU_BASE_CLK(SPIFI,	base_common_src_ids, 0),
	LPC1XX_CGU_BASE_CLK(SPI,	base_common_src_ids, 0),
	LPC1XX_CGU_BASE_CLK(PHY_RX,	base_common_src_ids, 0),
	LPC1XX_CGU_BASE_CLK(PHY_TX,	base_common_src_ids, 0),
	LPC1XX_CGU_BASE_CLK(APB1,	base_common_src_ids, 0),
	LPC1XX_CGU_BASE_CLK(APB3,	base_common_src_ids, 0),
	LPC1XX_CGU_BASE_CLK(LCD,	base_common_src_ids, 0),
	LPC1XX_CGU_BASE_CLK(ADCHS,	base_common_src_ids, 0),
	LPC1XX_CGU_BASE_CLK(SDIO,	base_common_src_ids, 0),
	LPC1XX_CGU_BASE_CLK(SSP0,	base_common_src_ids, 0),
	LPC1XX_CGU_BASE_CLK(SSP1,	base_common_src_ids, 0),
	LPC1XX_CGU_BASE_CLK(UART0,	base_common_src_ids, 0),
	LPC1XX_CGU_BASE_CLK(UART1,	base_common_src_ids, 0),
	LPC1XX_CGU_BASE_CLK(UART2,	base_common_src_ids, 0),
	LPC1XX_CGU_BASE_CLK(UART3,	base_common_src_ids, 0),
	LPC1XX_CGU_BASE_CLK(OUT,	base_all_src_ids,    0),
	अणु /* 21 reserved */ पूर्ण,
	अणु /* 22 reserved */ पूर्ण,
	अणु /* 23 reserved */ पूर्ण,
	अणु /* 24 reserved */ पूर्ण,
	LPC1XX_CGU_BASE_CLK(AUDIO,	base_common_src_ids, 0),
	LPC1XX_CGU_BASE_CLK(CGU_OUT0,	base_all_src_ids,    0),
	LPC1XX_CGU_BASE_CLK(CGU_OUT1,	base_all_src_ids,    0),
पूर्ण;

काष्ठा lpc18xx_pll अणु
	काष्ठा		clk_hw hw;
	व्योम __iomem	*reg;
	spinlock_t	*lock;
	u8		flags;
पूर्ण;

#घोषणा to_lpc_pll(hw) container_of(hw, काष्ठा lpc18xx_pll, hw)

काष्ठा lpc18xx_cgu_pll_clk अणु
	u8 clk_id;
	u8 n_parents;
	u8 reg_offset;
	काष्ठा clk_mux mux;
	काष्ठा clk_gate gate;
	काष्ठा lpc18xx_pll pll;
	स्थिर काष्ठा clk_ops *pll_ops;
पूर्ण;

#घोषणा LPC1XX_CGU_CLK_PLL(_id, _table, _pll_ops)	\
अणु							\
	.clk_id = CLK_SRC_ ##_id,			\
	.n_parents = ARRAY_SIZE(lpc18xx_cgu_ ##_table),	\
	.reg_offset = LPC18XX_CGU_ ##_id ##_STAT,	\
	.mux = अणु					\
		.mask = 0x1f,				\
		.shअगरt = 24,				\
		.table = lpc18xx_cgu_ ##_table,		\
	पूर्ण,						\
	.gate = अणु					\
		.bit_idx = 0,				\
		.flags = CLK_GATE_SET_TO_DISABLE,	\
	पूर्ण,						\
	.pll_ops = &lpc18xx_ ##_pll_ops,		\
पूर्ण

/*
 * PLL0 uses a special रेजिस्टर value encoding. The compute functions below
 * are taken or derived from the LPC1850 user manual (section 12.6.3.3).
 */

/* Compute PLL0 multiplier from decoded version */
अटल u32 lpc18xx_pll0_mdec2msel(u32 x)
अणु
	पूर्णांक i;

	चयन (x) अणु
	हाल 0x18003: वापस 1;
	हाल 0x10003: वापस 2;
	शेष:
		क्रम (i = LPC18XX_PLL0_MSEL_MAX + 1; x != 0x4000 && i > 0; i--)
			x = ((x ^ x >> 14) & 1) | (x << 1 & 0x7fff);
		वापस i;
	पूर्ण
पूर्ण
/* Compute PLL0 decoded multiplier from binary version */
अटल u32 lpc18xx_pll0_msel2mdec(u32 msel)
अणु
	u32 i, x = 0x4000;

	चयन (msel) अणु
	हाल 0: वापस 0;
	हाल 1: वापस 0x18003;
	हाल 2: वापस 0x10003;
	शेष:
		क्रम (i = msel; i <= LPC18XX_PLL0_MSEL_MAX; i++)
			x = ((x ^ x >> 1) & 1) << 14 | (x >> 1 & 0xffff);
		वापस x;
	पूर्ण
पूर्ण

/* Compute PLL0 bandwidth SELI reg from multiplier */
अटल u32 lpc18xx_pll0_msel2seli(u32 msel)
अणु
	u32 पंचांगp;

	अगर (msel > 16384) वापस 1;
	अगर (msel >  8192) वापस 2;
	अगर (msel >  2048) वापस 4;
	अगर (msel >=  501) वापस 8;
	अगर (msel >=   60) अणु
		पंचांगp = 1024 / (msel + 9);
		वापस ((1024 == (पंचांगp * (msel + 9))) == 0) ? पंचांगp * 4 : (पंचांगp + 1) * 4;
	पूर्ण

	वापस (msel & 0x3c) + 4;
पूर्ण

/* Compute PLL0 bandwidth SELP reg from multiplier */
अटल u32 lpc18xx_pll0_msel2selp(u32 msel)
अणु
	अगर (msel < 60)
		वापस (msel >> 1) + 1;

	वापस 31;
पूर्ण

अटल अचिन्हित दीर्घ lpc18xx_pll0_recalc_rate(काष्ठा clk_hw *hw,
					      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा lpc18xx_pll *pll = to_lpc_pll(hw);
	u32 ctrl, mभाग, msel, npभाग;

	ctrl = पढ़ोl(pll->reg + LPC18XX_CGU_PLL0USB_CTRL);
	mभाग = पढ़ोl(pll->reg + LPC18XX_CGU_PLL0USB_MDIV);
	npभाग = पढ़ोl(pll->reg + LPC18XX_CGU_PLL0USB_NP_DIV);

	अगर (ctrl & LPC18XX_PLL0_CTRL_BYPASS)
		वापस parent_rate;

	अगर (npभाग != LPC18XX_PLL0_NP_DIVS_1) अणु
		pr_warn("%s: pre/post dividers not supported\n", __func__);
		वापस 0;
	पूर्ण

	msel = lpc18xx_pll0_mdec2msel(mभाग & LPC18XX_PLL0_MDIV_MDEC_MASK);
	अगर (msel)
		वापस 2 * msel * parent_rate;

	pr_warn("%s: unable to calculate rate\n", __func__);

	वापस 0;
पूर्ण

अटल दीर्घ lpc18xx_pll0_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ *prate)
अणु
	अचिन्हित दीर्घ m;

	अगर (*prate < rate) अणु
		pr_warn("%s: pll dividers not supported\n", __func__);
		वापस -EINVAL;
	पूर्ण

	m = DIV_ROUND_UP_ULL(*prate, rate * 2);
	अगर (m <= 0 && m > LPC18XX_PLL0_MSEL_MAX) अणु
		pr_warn("%s: unable to support rate %lu\n", __func__, rate);
		वापस -EINVAL;
	पूर्ण

	वापस 2 * *prate * m;
पूर्ण

अटल पूर्णांक lpc18xx_pll0_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा lpc18xx_pll *pll = to_lpc_pll(hw);
	u32 ctrl, stat, m;
	पूर्णांक retry = 3;

	अगर (parent_rate < rate) अणु
		pr_warn("%s: pll dividers not supported\n", __func__);
		वापस -EINVAL;
	पूर्ण

	m = DIV_ROUND_UP_ULL(parent_rate, rate * 2);
	अगर (m <= 0 && m > LPC18XX_PLL0_MSEL_MAX) अणु
		pr_warn("%s: unable to support rate %lu\n", __func__, rate);
		वापस -EINVAL;
	पूर्ण

	m  = lpc18xx_pll0_msel2mdec(m);
	m |= lpc18xx_pll0_msel2selp(m) << LPC18XX_PLL0_MDIV_SELP_SHIFT;
	m |= lpc18xx_pll0_msel2seli(m) << LPC18XX_PLL0_MDIV_SELI_SHIFT;

	/* Power करोwn PLL, disable clk output and भागiders */
	ctrl = पढ़ोl(pll->reg + LPC18XX_CGU_PLL0USB_CTRL);
	ctrl |= LPC18XX_PLL0_CTRL_PD;
	ctrl &= ~(LPC18XX_PLL0_CTRL_BYPASS | LPC18XX_PLL0_CTRL_सूचीECTI |
		  LPC18XX_PLL0_CTRL_सूचीECTO | LPC18XX_PLL0_CTRL_CLKEN);
	ग_लिखोl(ctrl, pll->reg + LPC18XX_CGU_PLL0USB_CTRL);

	/* Configure new PLL settings */
	ग_लिखोl(m, pll->reg + LPC18XX_CGU_PLL0USB_MDIV);
	ग_लिखोl(LPC18XX_PLL0_NP_DIVS_1, pll->reg + LPC18XX_CGU_PLL0USB_NP_DIV);

	/* Power up PLL and रुको क्रम lock */
	ctrl &= ~LPC18XX_PLL0_CTRL_PD;
	ग_लिखोl(ctrl, pll->reg + LPC18XX_CGU_PLL0USB_CTRL);
	करो अणु
		udelay(10);
		stat = पढ़ोl(pll->reg + LPC18XX_CGU_PLL0USB_STAT);
		अगर (stat & LPC18XX_PLL0_STAT_LOCK) अणु
			ctrl |= LPC18XX_PLL0_CTRL_CLKEN;
			ग_लिखोl(ctrl, pll->reg + LPC18XX_CGU_PLL0USB_CTRL);

			वापस 0;
		पूर्ण
	पूर्ण जबतक (retry--);

	pr_warn("%s: unable to lock pll\n", __func__);

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा clk_ops lpc18xx_pll0_ops = अणु
	.recalc_rate	= lpc18xx_pll0_recalc_rate,
	.round_rate	= lpc18xx_pll0_round_rate,
	.set_rate	= lpc18xx_pll0_set_rate,
पूर्ण;

अटल अचिन्हित दीर्घ lpc18xx_pll1_recalc_rate(काष्ठा clk_hw *hw,
					      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा lpc18xx_pll *pll = to_lpc_pll(hw);
	u16 msel, nsel, psel;
	bool direct, fbsel;
	u32 stat, ctrl;

	stat = पढ़ोl(pll->reg + LPC18XX_CGU_PLL1_STAT);
	ctrl = पढ़ोl(pll->reg + LPC18XX_CGU_PLL1_CTRL);

	direct = (ctrl & LPC18XX_PLL1_CTRL_सूचीECT) ? true : false;
	fbsel = (ctrl & LPC18XX_PLL1_CTRL_FBSEL) ? true : false;

	msel = ((ctrl >> 16) & 0xff) + 1;
	nsel = ((ctrl >> 12) & 0x3) + 1;

	अगर (direct || fbsel)
		वापस msel * (parent_rate / nsel);

	psel = (ctrl >>  8) & 0x3;
	psel = 1 << psel;

	वापस (msel / (2 * psel)) * (parent_rate / nsel);
पूर्ण

अटल स्थिर काष्ठा clk_ops lpc18xx_pll1_ops = अणु
	.recalc_rate = lpc18xx_pll1_recalc_rate,
पूर्ण;

अटल पूर्णांक lpc18xx_cgu_gate_enable(काष्ठा clk_hw *hw)
अणु
	वापस clk_gate_ops.enable(hw);
पूर्ण

अटल व्योम lpc18xx_cgu_gate_disable(काष्ठा clk_hw *hw)
अणु
	clk_gate_ops.disable(hw);
पूर्ण

अटल पूर्णांक lpc18xx_cgu_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	स्थिर काष्ठा clk_hw *parent;

	/*
	 * The consumer of base घड़ीs needs know अगर the
	 * base घड़ी is really enabled beक्रमe it can be
	 * accessed. It is thereक्रमe necessary to verअगरy
	 * this all the way up.
	 */
	parent = clk_hw_get_parent(hw);
	अगर (!parent)
		वापस 0;

	अगर (!clk_hw_is_enabled(parent))
		वापस 0;

	वापस clk_gate_ops.is_enabled(hw);
पूर्ण

अटल स्थिर काष्ठा clk_ops lpc18xx_gate_ops = अणु
	.enable = lpc18xx_cgu_gate_enable,
	.disable = lpc18xx_cgu_gate_disable,
	.is_enabled = lpc18xx_cgu_gate_is_enabled,
पूर्ण;

अटल काष्ठा lpc18xx_cgu_pll_clk lpc18xx_cgu_src_clk_plls[] = अणु
	LPC1XX_CGU_CLK_PLL(PLL0USB,	pll0_src_ids, pll0_ops),
	LPC1XX_CGU_CLK_PLL(PLL0AUDIO,	pll0_src_ids, pll0_ops),
	LPC1XX_CGU_CLK_PLL(PLL1,	pll1_src_ids, pll1_ops),
पूर्ण;

अटल व्योम lpc18xx_fill_parent_names(स्थिर अक्षर **parent, u32 *id, पूर्णांक size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < size; i++)
		parent[i] = clk_src_names[id[i]];
पूर्ण

अटल काष्ठा clk *lpc18xx_cgu_रेजिस्टर_भाग(काष्ठा lpc18xx_cgu_src_clk_भाग *clk,
					    व्योम __iomem *base, पूर्णांक n)
अणु
	व्योम __iomem *reg = base + LPC18XX_CGU_IDIV_CTRL(n);
	स्थिर अक्षर *name = clk_src_names[clk->clk_id];
	स्थिर अक्षर *parents[CLK_SRC_MAX];

	clk->भाग.reg = reg;
	clk->mux.reg = reg;
	clk->gate.reg = reg;

	lpc18xx_fill_parent_names(parents, clk->mux.table, clk->n_parents);

	वापस clk_रेजिस्टर_composite(शून्य, name, parents, clk->n_parents,
				      &clk->mux.hw, &clk_mux_ops,
				      &clk->भाग.hw, &clk_भागider_ops,
				      &clk->gate.hw, &lpc18xx_gate_ops, 0);
पूर्ण


अटल काष्ठा clk *lpc18xx_रेजिस्टर_base_clk(काष्ठा lpc18xx_cgu_base_clk *clk,
					     व्योम __iomem *reg_base, पूर्णांक n)
अणु
	व्योम __iomem *reg = reg_base + LPC18XX_CGU_BASE_CLK(n);
	स्थिर अक्षर *name = clk_base_names[clk->clk_id];
	स्थिर अक्षर *parents[CLK_SRC_MAX];

	अगर (clk->n_parents == 0)
		वापस ERR_PTR(-ENOENT);

	clk->mux.reg = reg;
	clk->gate.reg = reg;

	lpc18xx_fill_parent_names(parents, clk->mux.table, clk->n_parents);

	/* SAFE_CLK can not be turned off */
	अगर (n == BASE_SAFE_CLK)
		वापस clk_रेजिस्टर_composite(शून्य, name, parents, clk->n_parents,
					      &clk->mux.hw, &clk_mux_ops,
					      शून्य, शून्य, शून्य, शून्य, 0);

	वापस clk_रेजिस्टर_composite(शून्य, name, parents, clk->n_parents,
				      &clk->mux.hw, &clk_mux_ops,
				      शून्य,  शून्य,
				      &clk->gate.hw, &lpc18xx_gate_ops, 0);
पूर्ण


अटल काष्ठा clk *lpc18xx_cgu_रेजिस्टर_pll(काष्ठा lpc18xx_cgu_pll_clk *clk,
					    व्योम __iomem *base)
अणु
	स्थिर अक्षर *name = clk_src_names[clk->clk_id];
	स्थिर अक्षर *parents[CLK_SRC_MAX];

	clk->pll.reg  = base;
	clk->mux.reg  = base + clk->reg_offset + LPC18XX_CGU_PLL_CTRL_OFFSET;
	clk->gate.reg = base + clk->reg_offset + LPC18XX_CGU_PLL_CTRL_OFFSET;

	lpc18xx_fill_parent_names(parents, clk->mux.table, clk->n_parents);

	वापस clk_रेजिस्टर_composite(शून्य, name, parents, clk->n_parents,
				      &clk->mux.hw, &clk_mux_ops,
				      &clk->pll.hw, clk->pll_ops,
				      &clk->gate.hw, &lpc18xx_gate_ops, 0);
पूर्ण

अटल व्योम __init lpc18xx_cgu_रेजिस्टर_source_clks(काष्ठा device_node *np,
						    व्योम __iomem *base)
अणु
	स्थिर अक्षर *parents[CLK_SRC_MAX];
	काष्ठा clk *clk;
	पूर्णांक i;

	/* Register the पूर्णांकernal 12 MHz RC oscillator (IRC) */
	clk = clk_रेजिस्टर_fixed_rate(शून्य, clk_src_names[CLK_SRC_IRC],
				      शून्य, 0, 12000000);
	अगर (IS_ERR(clk))
		pr_warn("%s: failed to register irc clk\n", __func__);

	/* Register crystal oscillator controlller */
	parents[0] = of_clk_get_parent_name(np, 0);
	clk = clk_रेजिस्टर_gate(शून्य, clk_src_names[CLK_SRC_OSC], parents[0],
				0, base + LPC18XX_CGU_XTAL_OSC_CTRL,
				0, CLK_GATE_SET_TO_DISABLE, शून्य);
	अगर (IS_ERR(clk))
		pr_warn("%s: failed to register osc clk\n", __func__);

	/* Register all PLLs */
	क्रम (i = 0; i < ARRAY_SIZE(lpc18xx_cgu_src_clk_plls); i++) अणु
		clk = lpc18xx_cgu_रेजिस्टर_pll(&lpc18xx_cgu_src_clk_plls[i],
						   base);
		अगर (IS_ERR(clk))
			pr_warn("%s: failed to register pll (%d)\n", __func__, i);
	पूर्ण

	/* Register all घड़ी भागiders A-E */
	क्रम (i = 0; i < ARRAY_SIZE(lpc18xx_cgu_src_clk_भागs); i++) अणु
		clk = lpc18xx_cgu_रेजिस्टर_भाग(&lpc18xx_cgu_src_clk_भागs[i],
					       base, i);
		अगर (IS_ERR(clk))
			pr_warn("%s: failed to register div %d\n", __func__, i);
	पूर्ण
पूर्ण

अटल काष्ठा clk *clk_base[BASE_CLK_MAX];
अटल काष्ठा clk_onecell_data clk_base_data = अणु
	.clks = clk_base,
	.clk_num = BASE_CLK_MAX,
पूर्ण;

अटल व्योम __init lpc18xx_cgu_रेजिस्टर_base_clks(व्योम __iomem *reg_base)
अणु
	पूर्णांक i;

	क्रम (i = BASE_SAFE_CLK; i < BASE_CLK_MAX; i++) अणु
		clk_base[i] = lpc18xx_रेजिस्टर_base_clk(&lpc18xx_cgu_base_clks[i],
							reg_base, i);
		अगर (IS_ERR(clk_base[i]) && PTR_ERR(clk_base[i]) != -ENOENT)
			pr_warn("%s: register base clk %d failed\n", __func__, i);
	पूर्ण
पूर्ण

अटल व्योम __init lpc18xx_cgu_init(काष्ठा device_node *np)
अणु
	व्योम __iomem *reg_base;

	reg_base = of_iomap(np, 0);
	अगर (!reg_base) अणु
		pr_warn("%s: failed to map address range\n", __func__);
		वापस;
	पूर्ण

	lpc18xx_cgu_रेजिस्टर_source_clks(np, reg_base);
	lpc18xx_cgu_रेजिस्टर_base_clks(reg_base);

	of_clk_add_provider(np, of_clk_src_onecell_get, &clk_base_data);
पूर्ण
CLK_OF_DECLARE(lpc18xx_cgu, "nxp,lpc1850-cgu", lpc18xx_cgu_init);
