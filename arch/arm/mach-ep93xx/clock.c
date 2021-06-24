<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/arm/mach-ep93xx/घड़ी.c
 * Clock control क्रम Cirrus EP93xx chips.
 *
 * Copyright (C) 2006 Lennert Buytenhek <buytenh@wantstofly.org>
 */

#घोषणा pr_fmt(fmt) "ep93xx " KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/soc/cirrus/ep93xx.h>

#समावेश "hardware.h"

#समावेश <यंत्र/भाग64.h>

#समावेश "soc.h"

काष्ठा clk अणु
	काष्ठा clk	*parent;
	अचिन्हित दीर्घ	rate;
	पूर्णांक		users;
	पूर्णांक		sw_locked;
	व्योम __iomem	*enable_reg;
	u32		enable_mask;

	अचिन्हित दीर्घ	(*get_rate)(काष्ठा clk *clk);
	पूर्णांक		(*set_rate)(काष्ठा clk *clk, अचिन्हित दीर्घ rate);
पूर्ण;


अटल अचिन्हित दीर्घ get_uart_rate(काष्ठा clk *clk);

अटल पूर्णांक set_keytchclk_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate);
अटल पूर्णांक set_भाग_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate);
अटल पूर्णांक set_i2s_sclk_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate);
अटल पूर्णांक set_i2s_lrclk_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate);

अटल काष्ठा clk clk_xtali = अणु
	.rate		= EP93XX_EXT_CLK_RATE,
पूर्ण;
अटल काष्ठा clk clk_uart1 = अणु
	.parent		= &clk_xtali,
	.sw_locked	= 1,
	.enable_reg	= EP93XX_SYSCON_DEVCFG,
	.enable_mask	= EP93XX_SYSCON_DEVCFG_U1EN,
	.get_rate	= get_uart_rate,
पूर्ण;
अटल काष्ठा clk clk_uart2 = अणु
	.parent		= &clk_xtali,
	.sw_locked	= 1,
	.enable_reg	= EP93XX_SYSCON_DEVCFG,
	.enable_mask	= EP93XX_SYSCON_DEVCFG_U2EN,
	.get_rate	= get_uart_rate,
पूर्ण;
अटल काष्ठा clk clk_uart3 = अणु
	.parent		= &clk_xtali,
	.sw_locked	= 1,
	.enable_reg	= EP93XX_SYSCON_DEVCFG,
	.enable_mask	= EP93XX_SYSCON_DEVCFG_U3EN,
	.get_rate	= get_uart_rate,
पूर्ण;
अटल काष्ठा clk clk_pll1 = अणु
	.parent		= &clk_xtali,
पूर्ण;
अटल काष्ठा clk clk_f = अणु
	.parent		= &clk_pll1,
पूर्ण;
अटल काष्ठा clk clk_h = अणु
	.parent		= &clk_pll1,
पूर्ण;
अटल काष्ठा clk clk_p = अणु
	.parent		= &clk_pll1,
पूर्ण;
अटल काष्ठा clk clk_pll2 = अणु
	.parent		= &clk_xtali,
पूर्ण;
अटल काष्ठा clk clk_usb_host = अणु
	.parent		= &clk_pll2,
	.enable_reg	= EP93XX_SYSCON_PWRCNT,
	.enable_mask	= EP93XX_SYSCON_PWRCNT_USH_EN,
पूर्ण;
अटल काष्ठा clk clk_keypad = अणु
	.parent		= &clk_xtali,
	.sw_locked	= 1,
	.enable_reg	= EP93XX_SYSCON_KEYTCHCLKDIV,
	.enable_mask	= EP93XX_SYSCON_KEYTCHCLKDIV_KEN,
	.set_rate	= set_keytchclk_rate,
पूर्ण;
अटल काष्ठा clk clk_adc = अणु
	.parent		= &clk_xtali,
	.sw_locked	= 1,
	.enable_reg	= EP93XX_SYSCON_KEYTCHCLKDIV,
	.enable_mask	= EP93XX_SYSCON_KEYTCHCLKDIV_TSEN,
	.set_rate	= set_keytchclk_rate,
पूर्ण;
अटल काष्ठा clk clk_spi = अणु
	.parent		= &clk_xtali,
	.rate		= EP93XX_EXT_CLK_RATE,
पूर्ण;
अटल काष्ठा clk clk_pwm = अणु
	.parent		= &clk_xtali,
	.rate		= EP93XX_EXT_CLK_RATE,
पूर्ण;

अटल काष्ठा clk clk_video = अणु
	.sw_locked	= 1,
	.enable_reg     = EP93XX_SYSCON_VIDCLKDIV,
	.enable_mask    = EP93XX_SYSCON_CLKDIV_ENABLE,
	.set_rate	= set_भाग_rate,
पूर्ण;

अटल काष्ठा clk clk_i2s_mclk = अणु
	.sw_locked	= 1,
	.enable_reg	= EP93XX_SYSCON_I2SCLKDIV,
	.enable_mask	= EP93XX_SYSCON_CLKDIV_ENABLE,
	.set_rate	= set_भाग_rate,
पूर्ण;

अटल काष्ठा clk clk_i2s_sclk = अणु
	.sw_locked	= 1,
	.parent		= &clk_i2s_mclk,
	.enable_reg	= EP93XX_SYSCON_I2SCLKDIV,
	.enable_mask	= EP93XX_SYSCON_I2SCLKDIV_SENA,
	.set_rate	= set_i2s_sclk_rate,
पूर्ण;

अटल काष्ठा clk clk_i2s_lrclk = अणु
	.sw_locked	= 1,
	.parent		= &clk_i2s_sclk,
	.enable_reg	= EP93XX_SYSCON_I2SCLKDIV,
	.enable_mask	= EP93XX_SYSCON_I2SCLKDIV_SENA,
	.set_rate	= set_i2s_lrclk_rate,
पूर्ण;

/* DMA Clocks */
अटल काष्ठा clk clk_m2p0 = अणु
	.parent		= &clk_h,
	.enable_reg	= EP93XX_SYSCON_PWRCNT,
	.enable_mask	= EP93XX_SYSCON_PWRCNT_DMA_M2P0,
पूर्ण;
अटल काष्ठा clk clk_m2p1 = अणु
	.parent		= &clk_h,
	.enable_reg	= EP93XX_SYSCON_PWRCNT,
	.enable_mask	= EP93XX_SYSCON_PWRCNT_DMA_M2P1,
पूर्ण;
अटल काष्ठा clk clk_m2p2 = अणु
	.parent		= &clk_h,
	.enable_reg	= EP93XX_SYSCON_PWRCNT,
	.enable_mask	= EP93XX_SYSCON_PWRCNT_DMA_M2P2,
पूर्ण;
अटल काष्ठा clk clk_m2p3 = अणु
	.parent		= &clk_h,
	.enable_reg	= EP93XX_SYSCON_PWRCNT,
	.enable_mask	= EP93XX_SYSCON_PWRCNT_DMA_M2P3,
पूर्ण;
अटल काष्ठा clk clk_m2p4 = अणु
	.parent		= &clk_h,
	.enable_reg	= EP93XX_SYSCON_PWRCNT,
	.enable_mask	= EP93XX_SYSCON_PWRCNT_DMA_M2P4,
पूर्ण;
अटल काष्ठा clk clk_m2p5 = अणु
	.parent		= &clk_h,
	.enable_reg	= EP93XX_SYSCON_PWRCNT,
	.enable_mask	= EP93XX_SYSCON_PWRCNT_DMA_M2P5,
पूर्ण;
अटल काष्ठा clk clk_m2p6 = अणु
	.parent		= &clk_h,
	.enable_reg	= EP93XX_SYSCON_PWRCNT,
	.enable_mask	= EP93XX_SYSCON_PWRCNT_DMA_M2P6,
पूर्ण;
अटल काष्ठा clk clk_m2p7 = अणु
	.parent		= &clk_h,
	.enable_reg	= EP93XX_SYSCON_PWRCNT,
	.enable_mask	= EP93XX_SYSCON_PWRCNT_DMA_M2P7,
पूर्ण;
अटल काष्ठा clk clk_m2p8 = अणु
	.parent		= &clk_h,
	.enable_reg	= EP93XX_SYSCON_PWRCNT,
	.enable_mask	= EP93XX_SYSCON_PWRCNT_DMA_M2P8,
पूर्ण;
अटल काष्ठा clk clk_m2p9 = अणु
	.parent		= &clk_h,
	.enable_reg	= EP93XX_SYSCON_PWRCNT,
	.enable_mask	= EP93XX_SYSCON_PWRCNT_DMA_M2P9,
पूर्ण;
अटल काष्ठा clk clk_m2m0 = अणु
	.parent		= &clk_h,
	.enable_reg	= EP93XX_SYSCON_PWRCNT,
	.enable_mask	= EP93XX_SYSCON_PWRCNT_DMA_M2M0,
पूर्ण;
अटल काष्ठा clk clk_m2m1 = अणु
	.parent		= &clk_h,
	.enable_reg	= EP93XX_SYSCON_PWRCNT,
	.enable_mask	= EP93XX_SYSCON_PWRCNT_DMA_M2M1,
पूर्ण;

#घोषणा INIT_CK(dev,con,ck)					\
	अणु .dev_id = dev, .con_id = con, .clk = ck पूर्ण

अटल काष्ठा clk_lookup घड़ीs[] = अणु
	INIT_CK(शून्य,			"xtali",	&clk_xtali),
	INIT_CK("apb:uart1",		शून्य,		&clk_uart1),
	INIT_CK("apb:uart2",		शून्य,		&clk_uart2),
	INIT_CK("apb:uart3",		शून्य,		&clk_uart3),
	INIT_CK(शून्य,			"pll1",		&clk_pll1),
	INIT_CK(शून्य,			"fclk",		&clk_f),
	INIT_CK(शून्य,			"hclk",		&clk_h),
	INIT_CK(शून्य,			"apb_pclk",	&clk_p),
	INIT_CK(शून्य,			"pll2",		&clk_pll2),
	INIT_CK("ohci-platform",	शून्य,		&clk_usb_host),
	INIT_CK("ep93xx-keypad",	शून्य,		&clk_keypad),
	INIT_CK("ep93xx-adc",		शून्य,		&clk_adc),
	INIT_CK("ep93xx-fb",		शून्य,		&clk_video),
	INIT_CK("ep93xx-spi.0",		शून्य,		&clk_spi),
	INIT_CK("ep93xx-i2s",		"mclk",		&clk_i2s_mclk),
	INIT_CK("ep93xx-i2s",		"sclk",		&clk_i2s_sclk),
	INIT_CK("ep93xx-i2s",		"lrclk",	&clk_i2s_lrclk),
	INIT_CK(शून्य,			"pwm_clk",	&clk_pwm),
	INIT_CK(शून्य,			"m2p0",		&clk_m2p0),
	INIT_CK(शून्य,			"m2p1",		&clk_m2p1),
	INIT_CK(शून्य,			"m2p2",		&clk_m2p2),
	INIT_CK(शून्य,			"m2p3",		&clk_m2p3),
	INIT_CK(शून्य,			"m2p4",		&clk_m2p4),
	INIT_CK(शून्य,			"m2p5",		&clk_m2p5),
	INIT_CK(शून्य,			"m2p6",		&clk_m2p6),
	INIT_CK(शून्य,			"m2p7",		&clk_m2p7),
	INIT_CK(शून्य,			"m2p8",		&clk_m2p8),
	INIT_CK(शून्य,			"m2p9",		&clk_m2p9),
	INIT_CK(शून्य,			"m2m0",		&clk_m2m0),
	INIT_CK(शून्य,			"m2m1",		&clk_m2m1),
पूर्ण;

अटल DEFINE_SPINLOCK(clk_lock);

अटल व्योम __clk_enable(काष्ठा clk *clk)
अणु
	अगर (!clk->users++) अणु
		अगर (clk->parent)
			__clk_enable(clk->parent);

		अगर (clk->enable_reg) अणु
			u32 v;

			v = __raw_पढ़ोl(clk->enable_reg);
			v |= clk->enable_mask;
			अगर (clk->sw_locked)
				ep93xx_syscon_swlocked_ग_लिखो(v, clk->enable_reg);
			अन्यथा
				__raw_ग_लिखोl(v, clk->enable_reg);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक clk_enable(काष्ठा clk *clk)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!clk)
		वापस -EINVAL;

	spin_lock_irqsave(&clk_lock, flags);
	__clk_enable(clk);
	spin_unlock_irqrestore(&clk_lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(clk_enable);

अटल व्योम __clk_disable(काष्ठा clk *clk)
अणु
	अगर (!--clk->users) अणु
		अगर (clk->enable_reg) अणु
			u32 v;

			v = __raw_पढ़ोl(clk->enable_reg);
			v &= ~clk->enable_mask;
			अगर (clk->sw_locked)
				ep93xx_syscon_swlocked_ग_लिखो(v, clk->enable_reg);
			अन्यथा
				__raw_ग_लिखोl(v, clk->enable_reg);
		पूर्ण

		अगर (clk->parent)
			__clk_disable(clk->parent);
	पूर्ण
पूर्ण

व्योम clk_disable(काष्ठा clk *clk)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!clk)
		वापस;

	spin_lock_irqsave(&clk_lock, flags);
	__clk_disable(clk);
	spin_unlock_irqrestore(&clk_lock, flags);
पूर्ण
EXPORT_SYMBOL(clk_disable);

अटल अचिन्हित दीर्घ get_uart_rate(काष्ठा clk *clk)
अणु
	अचिन्हित दीर्घ rate = clk_get_rate(clk->parent);
	u32 value;

	value = __raw_पढ़ोl(EP93XX_SYSCON_PWRCNT);
	अगर (value & EP93XX_SYSCON_PWRCNT_UARTBAUD)
		वापस rate;
	अन्यथा
		वापस rate / 2;
पूर्ण

अचिन्हित दीर्घ clk_get_rate(काष्ठा clk *clk)
अणु
	अगर (clk->get_rate)
		वापस clk->get_rate(clk);

	वापस clk->rate;
पूर्ण
EXPORT_SYMBOL(clk_get_rate);

अटल पूर्णांक set_keytchclk_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	u32 val;
	u32 भाग_bit;

	val = __raw_पढ़ोl(clk->enable_reg);

	/*
	 * The Key Matrix and ADC घड़ीs are configured using the same
	 * System Controller रेजिस्टर.  The घड़ी used will be either
	 * 1/4 or 1/16 the बाह्यal घड़ी rate depending on the
	 * EP93XX_SYSCON_KEYTCHCLKDIV_KDIV/EP93XX_SYSCON_KEYTCHCLKDIV_ADIV
	 * bit being set or cleared.
	 */
	भाग_bit = clk->enable_mask >> 15;

	अगर (rate == EP93XX_KEYTCHCLK_DIV4)
		val |= भाग_bit;
	अन्यथा अगर (rate == EP93XX_KEYTCHCLK_DIV16)
		val &= ~भाग_bit;
	अन्यथा
		वापस -EINVAL;

	ep93xx_syscon_swlocked_ग_लिखो(val, clk->enable_reg);
	clk->rate = rate;
	वापस 0;
पूर्ण

अटल पूर्णांक calc_clk_भाग(काष्ठा clk *clk, अचिन्हित दीर्घ rate,
			पूर्णांक *psel, पूर्णांक *esel, पूर्णांक *pभाग, पूर्णांक *भाग)
अणु
	काष्ठा clk *mclk;
	अचिन्हित दीर्घ max_rate, actual_rate, mclk_rate, rate_err = -1;
	पूर्णांक i, found = 0, __भाग = 0, __pभाग = 0;

	/* Don't exceed the maximum rate */
	max_rate = max3(clk_pll1.rate / 4, clk_pll2.rate / 4, clk_xtali.rate / 4);
	rate = min(rate, max_rate);

	/*
	 * Try the two pll's and the बाह्यal घड़ी
	 * Because the valid preभागiders are 2, 2.5 and 3, we multiply
	 * all the घड़ीs by 2 to aव्योम भग्नing poपूर्णांक math.
	 *
	 * This is based on the algorithm in the ep93xx raster guide:
	 * http://be-a-maverick.com/en/pubs/appNote/AN269REV1.pdf
	 *
	 */
	क्रम (i = 0; i < 3; i++) अणु
		अगर (i == 0)
			mclk = &clk_xtali;
		अन्यथा अगर (i == 1)
			mclk = &clk_pll1;
		अन्यथा
			mclk = &clk_pll2;
		mclk_rate = mclk->rate * 2;

		/* Try each preभागider value */
		क्रम (__pभाग = 4; __pभाग <= 6; __pभाग++) अणु
			__भाग = mclk_rate / (rate * __pभाग);
			अगर (__भाग < 2 || __भाग > 127)
				जारी;

			actual_rate = mclk_rate / (__pभाग * __भाग);

			अगर (!found || असल(actual_rate - rate) < rate_err) अणु
				*pभाग = __pभाग - 3;
				*भाग = __भाग;
				*psel = (i == 2);
				*esel = (i != 0);
				clk->parent = mclk;
				clk->rate = actual_rate;
				rate_err = असल(actual_rate - rate);
				found = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक set_भाग_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	पूर्णांक err, psel = 0, esel = 0, pभाग = 0, भाग = 0;
	u32 val;

	err = calc_clk_भाग(clk, rate, &psel, &esel, &pभाग, &भाग);
	अगर (err)
		वापस err;

	/* Clear the esel, psel, pभाग and भाग bits */
	val = __raw_पढ़ोl(clk->enable_reg);
	val &= ~0x7fff;

	/* Set the new esel, psel, pभाग and भाग bits क्रम the new घड़ी rate */
	val |= (esel ? EP93XX_SYSCON_CLKDIV_ESEL : 0) |
		(psel ? EP93XX_SYSCON_CLKDIV_PSEL : 0) |
		(pभाग << EP93XX_SYSCON_CLKDIV_PDIV_SHIFT) | भाग;
	ep93xx_syscon_swlocked_ग_लिखो(val, clk->enable_reg);
	वापस 0;
पूर्ण

अटल पूर्णांक set_i2s_sclk_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	अचिन्हित val = __raw_पढ़ोl(clk->enable_reg);

	अगर (rate == clk_i2s_mclk.rate / 2)
		ep93xx_syscon_swlocked_ग_लिखो(val & ~EP93XX_I2SCLKDIV_SDIV, 
					     clk->enable_reg);
	अन्यथा अगर (rate == clk_i2s_mclk.rate / 4)
		ep93xx_syscon_swlocked_ग_लिखो(val | EP93XX_I2SCLKDIV_SDIV, 
					     clk->enable_reg);
	अन्यथा
		वापस -EINVAL;

	clk_i2s_sclk.rate = rate;
	वापस 0;
पूर्ण

अटल पूर्णांक set_i2s_lrclk_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	अचिन्हित val = __raw_पढ़ोl(clk->enable_reg) & 
		~EP93XX_I2SCLKDIV_LRDIV_MASK;
	
	अगर (rate == clk_i2s_sclk.rate / 32)
		ep93xx_syscon_swlocked_ग_लिखो(val | EP93XX_I2SCLKDIV_LRDIV32,
					     clk->enable_reg);
	अन्यथा अगर (rate == clk_i2s_sclk.rate / 64)
		ep93xx_syscon_swlocked_ग_लिखो(val | EP93XX_I2SCLKDIV_LRDIV64,
					     clk->enable_reg);
	अन्यथा अगर (rate == clk_i2s_sclk.rate / 128)
		ep93xx_syscon_swlocked_ग_लिखो(val | EP93XX_I2SCLKDIV_LRDIV128,
					     clk->enable_reg);
	अन्यथा
		वापस -EINVAL;

	clk_i2s_lrclk.rate = rate;
	वापस 0;
पूर्ण

पूर्णांक clk_set_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	अगर (clk->set_rate)
		वापस clk->set_rate(clk, rate);

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(clk_set_rate);

दीर्घ clk_round_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	WARN_ON(clk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(clk_round_rate);

पूर्णांक clk_set_parent(काष्ठा clk *clk, काष्ठा clk *parent)
अणु
	WARN_ON(clk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(clk_set_parent);

काष्ठा clk *clk_get_parent(काष्ठा clk *clk)
अणु
	वापस clk->parent;
पूर्ण
EXPORT_SYMBOL(clk_get_parent);


अटल अक्षर fclk_भागisors[] = अणु 1, 2, 4, 8, 16, 1, 1, 1 पूर्ण;
अटल अक्षर hclk_भागisors[] = अणु 1, 2, 4, 5, 6, 8, 16, 32 पूर्ण;
अटल अक्षर pclk_भागisors[] = अणु 1, 2, 4, 8 पूर्ण;

/*
 * PLL rate = 14.7456 MHz * (X1FBD + 1) * (X2FBD + 1) / (X2IPD + 1) / 2^PS
 */
अटल अचिन्हित दीर्घ calc_pll_rate(u32 config_word)
अणु
	अचिन्हित दीर्घ दीर्घ rate;
	पूर्णांक i;

	rate = clk_xtali.rate;
	rate *= ((config_word >> 11) & 0x1f) + 1;		/* X1FBD */
	rate *= ((config_word >> 5) & 0x3f) + 1;		/* X2FBD */
	करो_भाग(rate, (config_word & 0x1f) + 1);			/* X2IPD */
	क्रम (i = 0; i < ((config_word >> 16) & 3); i++)		/* PS */
		rate >>= 1;

	वापस (अचिन्हित दीर्घ)rate;
पूर्ण

अटल व्योम __init ep93xx_dma_घड़ी_init(व्योम)
अणु
	clk_m2p0.rate = clk_h.rate;
	clk_m2p1.rate = clk_h.rate;
	clk_m2p2.rate = clk_h.rate;
	clk_m2p3.rate = clk_h.rate;
	clk_m2p4.rate = clk_h.rate;
	clk_m2p5.rate = clk_h.rate;
	clk_m2p6.rate = clk_h.rate;
	clk_m2p7.rate = clk_h.rate;
	clk_m2p8.rate = clk_h.rate;
	clk_m2p9.rate = clk_h.rate;
	clk_m2m0.rate = clk_h.rate;
	clk_m2m1.rate = clk_h.rate;
पूर्ण

अटल पूर्णांक __init ep93xx_घड़ी_init(व्योम)
अणु
	u32 value;

	/* Determine the bootloader configured pll1 rate */
	value = __raw_पढ़ोl(EP93XX_SYSCON_CLKSET1);
	अगर (!(value & EP93XX_SYSCON_CLKSET1_NBYP1))
		clk_pll1.rate = clk_xtali.rate;
	अन्यथा
		clk_pll1.rate = calc_pll_rate(value);

	/* Initialize the pll1 derived घड़ीs */
	clk_f.rate = clk_pll1.rate / fclk_भागisors[(value >> 25) & 0x7];
	clk_h.rate = clk_pll1.rate / hclk_भागisors[(value >> 20) & 0x7];
	clk_p.rate = clk_h.rate / pclk_भागisors[(value >> 18) & 0x3];
	ep93xx_dma_घड़ी_init();

	/* Determine the bootloader configured pll2 rate */
	value = __raw_पढ़ोl(EP93XX_SYSCON_CLKSET2);
	अगर (!(value & EP93XX_SYSCON_CLKSET2_NBYP2))
		clk_pll2.rate = clk_xtali.rate;
	अन्यथा अगर (value & EP93XX_SYSCON_CLKSET2_PLL2_EN)
		clk_pll2.rate = calc_pll_rate(value);
	अन्यथा
		clk_pll2.rate = 0;

	/* Initialize the pll2 derived घड़ीs */
	clk_usb_host.rate = clk_pll2.rate / (((value >> 28) & 0xf) + 1);

	/*
	 * EP93xx SSP घड़ी rate was द्विगुनd in version E2. For more inक्रमmation
	 * see:
	 *     http://www.cirrus.com/en/pubs/appNote/AN273REV4.pdf
	 */
	अगर (ep93xx_chip_revision() < EP93XX_CHIP_REV_E2)
		clk_spi.rate /= 2;

	pr_info("PLL1 running at %ld MHz, PLL2 at %ld MHz\n",
		clk_pll1.rate / 1000000, clk_pll2.rate / 1000000);
	pr_info("FCLK %ld MHz, HCLK %ld MHz, PCLK %ld MHz\n",
		clk_f.rate / 1000000, clk_h.rate / 1000000,
		clk_p.rate / 1000000);

	clkdev_add_table(घड़ीs, ARRAY_SIZE(घड़ीs));
	वापस 0;
पूर्ण
postcore_initcall(ep93xx_घड़ी_init);
