<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014 Marvell Technology Group Ltd.
 *
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 * Alexandre Belloni <alexandre.belloni@मुक्त-electrons.com>
 */
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>

#समावेश "berlin2-avpll.h"

/*
 * Berlin2 SoCs comprise up to two PLLs called AVPLL built upon a
 * VCO with 8 channels each, channel 8 is the odd-one-out and करोes
 * not provide mul/भाग.
 *
 * Unक्रमtunately, its रेजिस्टरs are not named but just numbered. To
 * get in at least some kind of काष्ठाure, we split each AVPLL पूर्णांकo
 * the VCOs and each channel पूर्णांकo separate घड़ी drivers.
 *
 * Also, here and there the VCO रेजिस्टरs are a bit dअगरferent with
 * respect to bit shअगरts. Make sure to add a comment क्रम those.
 */
#घोषणा NUM_CHANNELS	8

#घोषणा AVPLL_CTRL(x)		((x) * 0x4)

#घोषणा VCO_CTRL0		AVPLL_CTRL(0)
/* BG2/BG2CDs VCO_B has an additional shअगरt of 4 क्रम its VCO_CTRL0 reg */
#घोषणा  VCO_RESET		BIT(0)
#घोषणा  VCO_POWERUP		BIT(1)
#घोषणा  VCO_INTERPOL_SHIFT	2
#घोषणा  VCO_INTERPOL_MASK	(0xf << VCO_INTERPOL_SHIFT)
#घोषणा  VCO_REG1V45_SEL_SHIFT	6
#घोषणा  VCO_REG1V45_SEL(x)	((x) << VCO_REG1V45_SEL_SHIFT)
#घोषणा  VCO_REG1V45_SEL_1V40	VCO_REG1V45_SEL(0)
#घोषणा  VCO_REG1V45_SEL_1V45	VCO_REG1V45_SEL(1)
#घोषणा  VCO_REG1V45_SEL_1V50	VCO_REG1V45_SEL(2)
#घोषणा  VCO_REG1V45_SEL_1V55	VCO_REG1V45_SEL(3)
#घोषणा  VCO_REG1V45_SEL_MASK	VCO_REG1V45_SEL(3)
#घोषणा  VCO_REG0V9_SEL_SHIFT	8
#घोषणा  VCO_REG0V9_SEL_MASK	(0xf << VCO_REG0V9_SEL_SHIFT)
#घोषणा  VCO_VTHCAL_SHIFT	12
#घोषणा  VCO_VTHCAL(x)		((x) << VCO_VTHCAL_SHIFT)
#घोषणा  VCO_VTHCAL_0V90	VCO_VTHCAL(0)
#घोषणा  VCO_VTHCAL_0V95	VCO_VTHCAL(1)
#घोषणा  VCO_VTHCAL_1V00	VCO_VTHCAL(2)
#घोषणा  VCO_VTHCAL_1V05	VCO_VTHCAL(3)
#घोषणा  VCO_VTHCAL_MASK	VCO_VTHCAL(3)
#घोषणा  VCO_KVCOEXT_SHIFT	14
#घोषणा  VCO_KVCOEXT_MASK	(0x3 << VCO_KVCOEXT_SHIFT)
#घोषणा  VCO_KVCOEXT_ENABLE	BIT(17)
#घोषणा  VCO_V2IEXT_SHIFT	18
#घोषणा  VCO_V2IEXT_MASK	(0xf << VCO_V2IEXT_SHIFT)
#घोषणा  VCO_V2IEXT_ENABLE	BIT(22)
#घोषणा  VCO_SPEED_SHIFT	23
#घोषणा  VCO_SPEED(x)		((x) << VCO_SPEED_SHIFT)
#घोषणा  VCO_SPEED_1G08_1G21	VCO_SPEED(0)
#घोषणा  VCO_SPEED_1G21_1G40	VCO_SPEED(1)
#घोषणा  VCO_SPEED_1G40_1G61	VCO_SPEED(2)
#घोषणा  VCO_SPEED_1G61_1G86	VCO_SPEED(3)
#घोषणा  VCO_SPEED_1G86_2G00	VCO_SPEED(4)
#घोषणा  VCO_SPEED_2G00_2G22	VCO_SPEED(5)
#घोषणा  VCO_SPEED_2G22		VCO_SPEED(6)
#घोषणा  VCO_SPEED_MASK		VCO_SPEED(0x7)
#घोषणा  VCO_CLKDET_ENABLE	BIT(26)
#घोषणा VCO_CTRL1		AVPLL_CTRL(1)
#घोषणा  VCO_REFDIV_SHIFT	0
#घोषणा  VCO_REFDIV(x)		((x) << VCO_REFDIV_SHIFT)
#घोषणा  VCO_REFDIV_1		VCO_REFDIV(0)
#घोषणा  VCO_REFDIV_2		VCO_REFDIV(1)
#घोषणा  VCO_REFDIV_4		VCO_REFDIV(2)
#घोषणा  VCO_REFDIV_3		VCO_REFDIV(3)
#घोषणा  VCO_REFDIV_MASK	VCO_REFDIV(0x3f)
#घोषणा  VCO_FBDIV_SHIFT	6
#घोषणा  VCO_FBDIV(x)		((x) << VCO_FBDIV_SHIFT)
#घोषणा  VCO_FBDIV_MASK		VCO_FBDIV(0xff)
#घोषणा  VCO_ICP_SHIFT		14
/* PLL Charge Pump Current = 10uA * (x + 1) */
#घोषणा  VCO_ICP(x)		((x) << VCO_ICP_SHIFT)
#घोषणा  VCO_ICP_MASK		VCO_ICP(0xf)
#घोषणा  VCO_LOAD_CAP		BIT(18)
#घोषणा  VCO_CALIBRATION_START	BIT(19)
#घोषणा VCO_FREQOFFSETn(x)	AVPLL_CTRL(3 + (x))
#घोषणा  VCO_FREQOFFSET_MASK	0x7ffff
#घोषणा VCO_CTRL10		AVPLL_CTRL(10)
#घोषणा  VCO_POWERUP_CH1	BIT(20)
#घोषणा VCO_CTRL11		AVPLL_CTRL(11)
#घोषणा VCO_CTRL12		AVPLL_CTRL(12)
#घोषणा VCO_CTRL13		AVPLL_CTRL(13)
#घोषणा VCO_CTRL14		AVPLL_CTRL(14)
#घोषणा VCO_CTRL15		AVPLL_CTRL(15)
#घोषणा VCO_SYNC1n(x)		AVPLL_CTRL(15 + (x))
#घोषणा  VCO_SYNC1_MASK		0x1ffff
#घोषणा VCO_SYNC2n(x)		AVPLL_CTRL(23 + (x))
#घोषणा  VCO_SYNC2_MASK		0x1ffff
#घोषणा VCO_CTRL30		AVPLL_CTRL(30)
#घोषणा  VCO_DPLL_CH1_ENABLE	BIT(17)

काष्ठा berlin2_avpll_vco अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *base;
	u8 flags;
पूर्ण;

#घोषणा to_avpll_vco(hw) container_of(hw, काष्ठा berlin2_avpll_vco, hw)

अटल पूर्णांक berlin2_avpll_vco_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा berlin2_avpll_vco *vco = to_avpll_vco(hw);
	u32 reg;

	reg = पढ़ोl_relaxed(vco->base + VCO_CTRL0);
	अगर (vco->flags & BERLIN2_AVPLL_BIT_QUIRK)
		reg >>= 4;

	वापस !!(reg & VCO_POWERUP);
पूर्ण

अटल पूर्णांक berlin2_avpll_vco_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा berlin2_avpll_vco *vco = to_avpll_vco(hw);
	u32 reg;

	reg = पढ़ोl_relaxed(vco->base + VCO_CTRL0);
	अगर (vco->flags & BERLIN2_AVPLL_BIT_QUIRK)
		reg |= VCO_POWERUP << 4;
	अन्यथा
		reg |= VCO_POWERUP;
	ग_लिखोl_relaxed(reg, vco->base + VCO_CTRL0);

	वापस 0;
पूर्ण

अटल व्योम berlin2_avpll_vco_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा berlin2_avpll_vco *vco = to_avpll_vco(hw);
	u32 reg;

	reg = पढ़ोl_relaxed(vco->base + VCO_CTRL0);
	अगर (vco->flags & BERLIN2_AVPLL_BIT_QUIRK)
		reg &= ~(VCO_POWERUP << 4);
	अन्यथा
		reg &= ~VCO_POWERUP;
	ग_लिखोl_relaxed(reg, vco->base + VCO_CTRL0);
पूर्ण

अटल u8 vco_refभाग[] = अणु 1, 2, 4, 3 पूर्ण;

अटल अचिन्हित दीर्घ
berlin2_avpll_vco_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा berlin2_avpll_vco *vco = to_avpll_vco(hw);
	u32 reg, refभाग, fbभाग;
	u64 freq = parent_rate;

	/* AVPLL VCO frequency: Fvco = (Fref / refभाग) * fbभाग */
	reg = पढ़ोl_relaxed(vco->base + VCO_CTRL1);
	refभाग = (reg & VCO_REFDIV_MASK) >> VCO_REFDIV_SHIFT;
	refभाग = vco_refभाग[refभाग];
	fbभाग = (reg & VCO_FBDIV_MASK) >> VCO_FBDIV_SHIFT;
	freq *= fbभाग;
	करो_भाग(freq, refभाग);

	वापस (अचिन्हित दीर्घ)freq;
पूर्ण

अटल स्थिर काष्ठा clk_ops berlin2_avpll_vco_ops = अणु
	.is_enabled	= berlin2_avpll_vco_is_enabled,
	.enable		= berlin2_avpll_vco_enable,
	.disable	= berlin2_avpll_vco_disable,
	.recalc_rate	= berlin2_avpll_vco_recalc_rate,
पूर्ण;

पूर्णांक __init berlin2_avpll_vco_रेजिस्टर(व्योम __iomem *base,
			       स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			       u8 vco_flags, अचिन्हित दीर्घ flags)
अणु
	काष्ठा berlin2_avpll_vco *vco;
	काष्ठा clk_init_data init;

	vco = kzalloc(माप(*vco), GFP_KERNEL);
	अगर (!vco)
		वापस -ENOMEM;

	vco->base = base;
	vco->flags = vco_flags;
	vco->hw.init = &init;
	init.name = name;
	init.ops = &berlin2_avpll_vco_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = flags;

	वापस clk_hw_रेजिस्टर(शून्य, &vco->hw);
पूर्ण

काष्ठा berlin2_avpll_channel अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *base;
	u8 flags;
	u8 index;
पूर्ण;

#घोषणा to_avpll_channel(hw) container_of(hw, काष्ठा berlin2_avpll_channel, hw)

अटल पूर्णांक berlin2_avpll_channel_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा berlin2_avpll_channel *ch = to_avpll_channel(hw);
	u32 reg;

	अगर (ch->index == 7)
		वापस 1;

	reg = पढ़ोl_relaxed(ch->base + VCO_CTRL10);
	reg &= VCO_POWERUP_CH1 << ch->index;

	वापस !!reg;
पूर्ण

अटल पूर्णांक berlin2_avpll_channel_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा berlin2_avpll_channel *ch = to_avpll_channel(hw);
	u32 reg;

	reg = पढ़ोl_relaxed(ch->base + VCO_CTRL10);
	reg |= VCO_POWERUP_CH1 << ch->index;
	ग_लिखोl_relaxed(reg, ch->base + VCO_CTRL10);

	वापस 0;
पूर्ण

अटल व्योम berlin2_avpll_channel_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा berlin2_avpll_channel *ch = to_avpll_channel(hw);
	u32 reg;

	reg = पढ़ोl_relaxed(ch->base + VCO_CTRL10);
	reg &= ~(VCO_POWERUP_CH1 << ch->index);
	ग_लिखोl_relaxed(reg, ch->base + VCO_CTRL10);
पूर्ण

अटल स्थिर u8 भाग_hdmi[] = अणु 1, 2, 4, 6 पूर्ण;
अटल स्थिर u8 भाग_av1[] = अणु 1, 2, 5, 5 पूर्ण;

अटल अचिन्हित दीर्घ
berlin2_avpll_channel_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा berlin2_avpll_channel *ch = to_avpll_channel(hw);
	u32 reg, भाग_av2, भाग_av3, भागider = 1;
	u64 freq = parent_rate;

	reg = पढ़ोl_relaxed(ch->base + VCO_CTRL30);
	अगर ((reg & (VCO_DPLL_CH1_ENABLE << ch->index)) == 0)
		जाओ skip_भाग;

	/*
	 * Fch = (Fref * sync2) /
	 *    (sync1 * भाग_hdmi * भाग_av1 * भाग_av2 * भाग_av3)
	 */

	reg = पढ़ोl_relaxed(ch->base + VCO_SYNC1n(ch->index));
	/* BG2/BG2CDs SYNC1 reg on AVPLL_B channel 1 is shअगरted by 4 */
	अगर (ch->flags & BERLIN2_AVPLL_BIT_QUIRK && ch->index == 0)
		reg >>= 4;
	भागider = reg & VCO_SYNC1_MASK;

	reg = पढ़ोl_relaxed(ch->base + VCO_SYNC2n(ch->index));
	freq *= reg & VCO_SYNC2_MASK;

	/* Channel 8 has no भागiders */
	अगर (ch->index == 7)
		जाओ skip_भाग;

	/*
	 * HDMI भागider start at VCO_CTRL11, bit 7; MSB is enable, lower 2 bit
	 * determine भागider.
	 */
	reg = पढ़ोl_relaxed(ch->base + VCO_CTRL11) >> 7;
	reg = (reg >> (ch->index * 3));
	अगर (reg & BIT(2))
		भागider *= भाग_hdmi[reg & 0x3];

	/*
	 * AV1 भागider start at VCO_CTRL11, bit 28; MSB is enable, lower 2 bit
	 * determine भागider.
	 */
	अगर (ch->index == 0) अणु
		reg = पढ़ोl_relaxed(ch->base + VCO_CTRL11);
		reg >>= 28;
	पूर्ण अन्यथा अणु
		reg = पढ़ोl_relaxed(ch->base + VCO_CTRL12);
		reg >>= (ch->index-1) * 3;
	पूर्ण
	अगर (reg & BIT(2))
		भागider *= भाग_av1[reg & 0x3];

	/*
	 * AV2 भागider start at VCO_CTRL12, bit 18; each 7 bits wide,
	 * zero is not a valid value.
	 */
	अगर (ch->index < 2) अणु
		reg = पढ़ोl_relaxed(ch->base + VCO_CTRL12);
		reg >>= 18 + (ch->index * 7);
	पूर्ण अन्यथा अगर (ch->index < 7) अणु
		reg = पढ़ोl_relaxed(ch->base + VCO_CTRL13);
		reg >>= (ch->index - 2) * 7;
	पूर्ण अन्यथा अणु
		reg = पढ़ोl_relaxed(ch->base + VCO_CTRL14);
	पूर्ण
	भाग_av2 = reg & 0x7f;
	अगर (भाग_av2)
		भागider *= भाग_av2;

	/*
	 * AV3 भागider start at VCO_CTRL14, bit 7; each 4 bits wide.
	 * AV2/AV3 क्रमm a fractional भागider, where only specfic values क्रम AV3
	 * are allowed. AV3 != 0 भागides by AV2/2, AV3=0 is bypass.
	 */
	अगर (ch->index < 6) अणु
		reg = पढ़ोl_relaxed(ch->base + VCO_CTRL14);
		reg >>= 7 + (ch->index * 4);
	पूर्ण अन्यथा अणु
		reg = पढ़ोl_relaxed(ch->base + VCO_CTRL15);
	पूर्ण
	भाग_av3 = reg & 0xf;
	अगर (भाग_av2 && भाग_av3)
		freq *= 2;

skip_भाग:
	करो_भाग(freq, भागider);
	वापस (अचिन्हित दीर्घ)freq;
पूर्ण

अटल स्थिर काष्ठा clk_ops berlin2_avpll_channel_ops = अणु
	.is_enabled	= berlin2_avpll_channel_is_enabled,
	.enable		= berlin2_avpll_channel_enable,
	.disable	= berlin2_avpll_channel_disable,
	.recalc_rate	= berlin2_avpll_channel_recalc_rate,
पूर्ण;

/*
 * Another nice quirk:
 * On some production SoCs, AVPLL channels are scrambled with respect
 * to the channel numbering in the रेजिस्टरs but still referenced by
 * their original channel numbers. We deal with it by having a flag
 * and a translation table क्रम the index.
 */
अटल स्थिर u8 quirk_index[] __initस्थिर = अणु 0, 6, 5, 4, 3, 2, 1, 7 पूर्ण;

पूर्णांक __init berlin2_avpll_channel_रेजिस्टर(व्योम __iomem *base,
			   स्थिर अक्षर *name, u8 index, स्थिर अक्षर *parent_name,
			   u8 ch_flags, अचिन्हित दीर्घ flags)
अणु
	काष्ठा berlin2_avpll_channel *ch;
	काष्ठा clk_init_data init;

	ch = kzalloc(माप(*ch), GFP_KERNEL);
	अगर (!ch)
		वापस -ENOMEM;

	ch->base = base;
	अगर (ch_flags & BERLIN2_AVPLL_SCRAMBLE_QUIRK)
		ch->index = quirk_index[index];
	अन्यथा
		ch->index = index;

	ch->flags = ch_flags;
	ch->hw.init = &init;
	init.name = name;
	init.ops = &berlin2_avpll_channel_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = flags;

	वापस clk_hw_रेजिस्टर(शून्य, &ch->hw);
पूर्ण
