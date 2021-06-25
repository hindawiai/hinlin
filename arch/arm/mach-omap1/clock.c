<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-omap1/घड़ी.c
 *
 *  Copyright (C) 2004 - 2005, 2009-2010 Nokia Corporation
 *  Written by Tuukka Tikkanen <tuukka.tikkanen@elektrobit.com>
 *
 *  Modअगरied to use omap shared घड़ी framework by
 *  Tony Lindgren <tony@atomide.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>

#समावेश <यंत्र/mach-types.h>

#समावेश <mach/hardware.h>

#समावेश "soc.h"
#समावेश "iomap.h"
#समावेश "clock.h"
#समावेश "opp.h"
#समावेश "sram.h"

__u32 arm_idlect1_mask;
काष्ठा clk *api_ck_p, *ck_dpll1_p, *ck_ref_p;

अटल LIST_HEAD(घड़ीs);
अटल DEFINE_MUTEX(घड़ीs_mutex);
अटल DEFINE_SPINLOCK(घड़ीfw_lock);

/*
 * Omap1 specअगरic घड़ी functions
 */

अचिन्हित दीर्घ omap1_uart_recalc(काष्ठा clk *clk)
अणु
	अचिन्हित पूर्णांक val = __raw_पढ़ोl(clk->enable_reg);
	वापस val & clk->enable_bit ? 48000000 : 12000000;
पूर्ण

अचिन्हित दीर्घ omap1_sossi_recalc(काष्ठा clk *clk)
अणु
	u32 भाग = omap_पढ़ोl(MOD_CONF_CTRL_1);

	भाग = (भाग >> 17) & 0x7;
	भाग++;

	वापस clk->parent->rate / भाग;
पूर्ण

अटल व्योम omap1_clk_allow_idle(काष्ठा clk *clk)
अणु
	काष्ठा arm_idlect1_clk * iclk = (काष्ठा arm_idlect1_clk *)clk;

	अगर (!(clk->flags & CLOCK_IDLE_CONTROL))
		वापस;

	अगर (iclk->no_idle_count > 0 && !(--iclk->no_idle_count))
		arm_idlect1_mask |= 1 << iclk->idlect_shअगरt;
पूर्ण

अटल व्योम omap1_clk_deny_idle(काष्ठा clk *clk)
अणु
	काष्ठा arm_idlect1_clk * iclk = (काष्ठा arm_idlect1_clk *)clk;

	अगर (!(clk->flags & CLOCK_IDLE_CONTROL))
		वापस;

	अगर (iclk->no_idle_count++ == 0)
		arm_idlect1_mask &= ~(1 << iclk->idlect_shअगरt);
पूर्ण

अटल __u16 verअगरy_ckctl_value(__u16 newval)
अणु
	/* This function checks क्रम following limitations set
	 * by the hardware (all conditions must be true):
	 * DSPMMU_CK == DSP_CK  or  DSPMMU_CK == DSP_CK/2
	 * ARM_CK >= TC_CK
	 * DSP_CK >= TC_CK
	 * DSPMMU_CK >= TC_CK
	 *
	 * In addition following rules are enक्रमced:
	 * LCD_CK <= TC_CK
	 * ARMPER_CK <= TC_CK
	 *
	 * However, maximum frequencies are not checked क्रम!
	 */
	__u8 per_exp;
	__u8 lcd_exp;
	__u8 arm_exp;
	__u8 dsp_exp;
	__u8 tc_exp;
	__u8 dspmmu_exp;

	per_exp = (newval >> CKCTL_PERDIV_OFFSET) & 3;
	lcd_exp = (newval >> CKCTL_LCDDIV_OFFSET) & 3;
	arm_exp = (newval >> CKCTL_ARMDIV_OFFSET) & 3;
	dsp_exp = (newval >> CKCTL_DSPDIV_OFFSET) & 3;
	tc_exp = (newval >> CKCTL_TCDIV_OFFSET) & 3;
	dspmmu_exp = (newval >> CKCTL_DSPMMUDIV_OFFSET) & 3;

	अगर (dspmmu_exp < dsp_exp)
		dspmmu_exp = dsp_exp;
	अगर (dspmmu_exp > dsp_exp+1)
		dspmmu_exp = dsp_exp+1;
	अगर (tc_exp < arm_exp)
		tc_exp = arm_exp;
	अगर (tc_exp < dspmmu_exp)
		tc_exp = dspmmu_exp;
	अगर (tc_exp > lcd_exp)
		lcd_exp = tc_exp;
	अगर (tc_exp > per_exp)
		per_exp = tc_exp;

	newval &= 0xf000;
	newval |= per_exp << CKCTL_PERDIV_OFFSET;
	newval |= lcd_exp << CKCTL_LCDDIV_OFFSET;
	newval |= arm_exp << CKCTL_ARMDIV_OFFSET;
	newval |= dsp_exp << CKCTL_DSPDIV_OFFSET;
	newval |= tc_exp << CKCTL_TCDIV_OFFSET;
	newval |= dspmmu_exp << CKCTL_DSPMMUDIV_OFFSET;

	वापस newval;
पूर्ण

अटल पूर्णांक calc_dsor_exp(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	/* Note: If target frequency is too low, this function will वापस 4,
	 * which is invalid value. Caller must check क्रम this value and act
	 * accordingly.
	 *
	 * Note: This function करोes not check क्रम following limitations set
	 * by the hardware (all conditions must be true):
	 * DSPMMU_CK == DSP_CK  or  DSPMMU_CK == DSP_CK/2
	 * ARM_CK >= TC_CK
	 * DSP_CK >= TC_CK
	 * DSPMMU_CK >= TC_CK
	 */
	अचिन्हित दीर्घ realrate;
	काष्ठा clk * parent;
	अचिन्हित  dsor_exp;

	parent = clk->parent;
	अगर (unlikely(parent == शून्य))
		वापस -EIO;

	realrate = parent->rate;
	क्रम (dsor_exp=0; dsor_exp<4; dsor_exp++) अणु
		अगर (realrate <= rate)
			अवरोध;

		realrate /= 2;
	पूर्ण

	वापस dsor_exp;
पूर्ण

अचिन्हित दीर्घ omap1_ckctl_recalc(काष्ठा clk *clk)
अणु
	/* Calculate भागisor encoded as 2-bit exponent */
	पूर्णांक dsor = 1 << (3 & (omap_पढ़ोw(ARM_CKCTL) >> clk->rate_offset));

	वापस clk->parent->rate / dsor;
पूर्ण

अचिन्हित दीर्घ omap1_ckctl_recalc_dsp_करोमुख्य(काष्ठा clk *clk)
अणु
	पूर्णांक dsor;

	/* Calculate भागisor encoded as 2-bit exponent
	 *
	 * The घड़ी control bits are in DSP करोमुख्य,
	 * so api_ck is needed क्रम access.
	 * Note that DSP_CKCTL virt addr = phys addr, so
	 * we must use __raw_पढ़ोw() instead of omap_पढ़ोw().
	 */
	omap1_clk_enable(api_ck_p);
	dsor = 1 << (3 & (__raw_पढ़ोw(DSP_CKCTL) >> clk->rate_offset));
	omap1_clk_disable(api_ck_p);

	वापस clk->parent->rate / dsor;
पूर्ण

/* MPU भव घड़ी functions */
पूर्णांक omap1_select_table_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	/* Find the highest supported frequency <= rate and चयन to it */
	काष्ठा mpu_rate * ptr;
	अचिन्हित दीर्घ ref_rate;

	ref_rate = ck_ref_p->rate;

	क्रम (ptr = omap1_rate_table; ptr->rate; ptr++) अणु
		अगर (!(ptr->flags & cpu_mask))
			जारी;

		अगर (ptr->xtal != ref_rate)
			जारी;

		/* Can check only after xtal frequency check */
		अगर (ptr->rate <= rate)
			अवरोध;
	पूर्ण

	अगर (!ptr->rate)
		वापस -EINVAL;

	/*
	 * In most हालs we should not need to reprogram DPLL.
	 * Reprogramming the DPLL is tricky, it must be करोne from SRAM.
	 */
	omap_sram_reprogram_घड़ी(ptr->dpllctl_val, ptr->ckctl_val);

	/* XXX Do we need to recalculate the tree below DPLL1 at this poपूर्णांक? */
	ck_dpll1_p->rate = ptr->pll_rate;

	वापस 0;
पूर्ण

पूर्णांक omap1_clk_set_rate_dsp_करोमुख्य(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	पूर्णांक dsor_exp;
	u16 regval;

	dsor_exp = calc_dsor_exp(clk, rate);
	अगर (dsor_exp > 3)
		dsor_exp = -EINVAL;
	अगर (dsor_exp < 0)
		वापस dsor_exp;

	regval = __raw_पढ़ोw(DSP_CKCTL);
	regval &= ~(3 << clk->rate_offset);
	regval |= dsor_exp << clk->rate_offset;
	__raw_ग_लिखोw(regval, DSP_CKCTL);
	clk->rate = clk->parent->rate / (1 << dsor_exp);

	वापस 0;
पूर्ण

दीर्घ omap1_clk_round_rate_ckctl_arm(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	पूर्णांक dsor_exp = calc_dsor_exp(clk, rate);
	अगर (dsor_exp < 0)
		वापस dsor_exp;
	अगर (dsor_exp > 3)
		dsor_exp = 3;
	वापस clk->parent->rate / (1 << dsor_exp);
पूर्ण

पूर्णांक omap1_clk_set_rate_ckctl_arm(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	पूर्णांक dsor_exp;
	u16 regval;

	dsor_exp = calc_dsor_exp(clk, rate);
	अगर (dsor_exp > 3)
		dsor_exp = -EINVAL;
	अगर (dsor_exp < 0)
		वापस dsor_exp;

	regval = omap_पढ़ोw(ARM_CKCTL);
	regval &= ~(3 << clk->rate_offset);
	regval |= dsor_exp << clk->rate_offset;
	regval = verअगरy_ckctl_value(regval);
	omap_ग_लिखोw(regval, ARM_CKCTL);
	clk->rate = clk->parent->rate / (1 << dsor_exp);
	वापस 0;
पूर्ण

दीर्घ omap1_round_to_table_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	/* Find the highest supported frequency <= rate */
	काष्ठा mpu_rate * ptr;
	दीर्घ highest_rate;
	अचिन्हित दीर्घ ref_rate;

	ref_rate = ck_ref_p->rate;

	highest_rate = -EINVAL;

	क्रम (ptr = omap1_rate_table; ptr->rate; ptr++) अणु
		अगर (!(ptr->flags & cpu_mask))
			जारी;

		अगर (ptr->xtal != ref_rate)
			जारी;

		highest_rate = ptr->rate;

		/* Can check only after xtal frequency check */
		अगर (ptr->rate <= rate)
			अवरोध;
	पूर्ण

	वापस highest_rate;
पूर्ण

अटल अचिन्हित calc_ext_dsor(अचिन्हित दीर्घ rate)
अणु
	अचिन्हित dsor;

	/* MCLK and BCLK भागisor selection is not linear:
	 * freq = 96MHz / dsor
	 *
	 * RATIO_SEL range: dsor <-> RATIO_SEL
	 * 0..6: (RATIO_SEL+2) <-> (dsor-2)
	 * 6..48:  (8+(RATIO_SEL-6)*2) <-> ((dsor-8)/2+6)
	 * Minimum dsor is 2 and maximum is 96. Odd भागisors starting from 9
	 * can not be used.
	 */
	क्रम (dsor = 2; dsor < 96; ++dsor) अणु
		अगर ((dsor & 1) && dsor > 8)
			जारी;
		अगर (rate >= 96000000 / dsor)
			अवरोध;
	पूर्ण
	वापस dsor;
पूर्ण

/* XXX Only needed on 1510 */
पूर्णांक omap1_set_uart_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	अचिन्हित पूर्णांक val;

	val = __raw_पढ़ोl(clk->enable_reg);
	अगर (rate == 12000000)
		val &= ~(1 << clk->enable_bit);
	अन्यथा अगर (rate == 48000000)
		val |= (1 << clk->enable_bit);
	अन्यथा
		वापस -EINVAL;
	__raw_ग_लिखोl(val, clk->enable_reg);
	clk->rate = rate;

	वापस 0;
पूर्ण

/* External घड़ी (MCLK & BCLK) functions */
पूर्णांक omap1_set_ext_clk_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	अचिन्हित dsor;
	__u16 ratio_bits;

	dsor = calc_ext_dsor(rate);
	clk->rate = 96000000 / dsor;
	अगर (dsor > 8)
		ratio_bits = ((dsor - 8) / 2 + 6) << 2;
	अन्यथा
		ratio_bits = (dsor - 2) << 2;

	ratio_bits |= __raw_पढ़ोw(clk->enable_reg) & ~0xfd;
	__raw_ग_लिखोw(ratio_bits, clk->enable_reg);

	वापस 0;
पूर्ण

पूर्णांक omap1_set_sossi_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	u32 l;
	पूर्णांक भाग;
	अचिन्हित दीर्घ p_rate;

	p_rate = clk->parent->rate;
	/* Round towards slower frequency */
	भाग = (p_rate + rate - 1) / rate;
	भाग--;
	अगर (भाग < 0 || भाग > 7)
		वापस -EINVAL;

	l = omap_पढ़ोl(MOD_CONF_CTRL_1);
	l &= ~(7 << 17);
	l |= भाग << 17;
	omap_ग_लिखोl(l, MOD_CONF_CTRL_1);

	clk->rate = p_rate / (भाग + 1);

	वापस 0;
पूर्ण

दीर्घ omap1_round_ext_clk_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	वापस 96000000 / calc_ext_dsor(rate);
पूर्ण

व्योम omap1_init_ext_clk(काष्ठा clk *clk)
अणु
	अचिन्हित dsor;
	__u16 ratio_bits;

	/* Determine current rate and ensure घड़ी is based on 96MHz APLL */
	ratio_bits = __raw_पढ़ोw(clk->enable_reg) & ~1;
	__raw_ग_लिखोw(ratio_bits, clk->enable_reg);

	ratio_bits = (ratio_bits & 0xfc) >> 2;
	अगर (ratio_bits > 6)
		dsor = (ratio_bits - 6) * 2 + 8;
	अन्यथा
		dsor = ratio_bits + 2;

	clk-> rate = 96000000 / dsor;
पूर्ण

पूर्णांक omap1_clk_enable(काष्ठा clk *clk)
अणु
	पूर्णांक ret = 0;

	अगर (clk->usecount++ == 0) अणु
		अगर (clk->parent) अणु
			ret = omap1_clk_enable(clk->parent);
			अगर (ret)
				जाओ err;

			अगर (clk->flags & CLOCK_NO_IDLE_PARENT)
				omap1_clk_deny_idle(clk->parent);
		पूर्ण

		ret = clk->ops->enable(clk);
		अगर (ret) अणु
			अगर (clk->parent)
				omap1_clk_disable(clk->parent);
			जाओ err;
		पूर्ण
	पूर्ण
	वापस ret;

err:
	clk->usecount--;
	वापस ret;
पूर्ण

व्योम omap1_clk_disable(काष्ठा clk *clk)
अणु
	अगर (clk->usecount > 0 && !(--clk->usecount)) अणु
		clk->ops->disable(clk);
		अगर (likely(clk->parent)) अणु
			omap1_clk_disable(clk->parent);
			अगर (clk->flags & CLOCK_NO_IDLE_PARENT)
				omap1_clk_allow_idle(clk->parent);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक omap1_clk_enable_generic(काष्ठा clk *clk)
अणु
	__u16 regval16;
	__u32 regval32;

	अगर (unlikely(clk->enable_reg == शून्य)) अणु
		prपूर्णांकk(KERN_ERR "clock.c: Enable for %s without enable code\n",
		       clk->name);
		वापस -EINVAL;
	पूर्ण

	अगर (clk->flags & ENABLE_REG_32BIT) अणु
		regval32 = __raw_पढ़ोl(clk->enable_reg);
		regval32 |= (1 << clk->enable_bit);
		__raw_ग_लिखोl(regval32, clk->enable_reg);
	पूर्ण अन्यथा अणु
		regval16 = __raw_पढ़ोw(clk->enable_reg);
		regval16 |= (1 << clk->enable_bit);
		__raw_ग_लिखोw(regval16, clk->enable_reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम omap1_clk_disable_generic(काष्ठा clk *clk)
अणु
	__u16 regval16;
	__u32 regval32;

	अगर (clk->enable_reg == शून्य)
		वापस;

	अगर (clk->flags & ENABLE_REG_32BIT) अणु
		regval32 = __raw_पढ़ोl(clk->enable_reg);
		regval32 &= ~(1 << clk->enable_bit);
		__raw_ग_लिखोl(regval32, clk->enable_reg);
	पूर्ण अन्यथा अणु
		regval16 = __raw_पढ़ोw(clk->enable_reg);
		regval16 &= ~(1 << clk->enable_bit);
		__raw_ग_लिखोw(regval16, clk->enable_reg);
	पूर्ण
पूर्ण

स्थिर काष्ठा clkops clkops_generic = अणु
	.enable		= omap1_clk_enable_generic,
	.disable	= omap1_clk_disable_generic,
पूर्ण;

अटल पूर्णांक omap1_clk_enable_dsp_करोमुख्य(काष्ठा clk *clk)
अणु
	पूर्णांक retval;

	retval = omap1_clk_enable(api_ck_p);
	अगर (!retval) अणु
		retval = omap1_clk_enable_generic(clk);
		omap1_clk_disable(api_ck_p);
	पूर्ण

	वापस retval;
पूर्ण

अटल व्योम omap1_clk_disable_dsp_करोमुख्य(काष्ठा clk *clk)
अणु
	अगर (omap1_clk_enable(api_ck_p) == 0) अणु
		omap1_clk_disable_generic(clk);
		omap1_clk_disable(api_ck_p);
	पूर्ण
पूर्ण

स्थिर काष्ठा clkops clkops_dspck = अणु
	.enable		= omap1_clk_enable_dsp_करोमुख्य,
	.disable	= omap1_clk_disable_dsp_करोमुख्य,
पूर्ण;

/* XXX SYSC रेजिस्टर handling करोes not beदीर्घ in the घड़ी framework */
अटल पूर्णांक omap1_clk_enable_uart_functional_16xx(काष्ठा clk *clk)
अणु
	पूर्णांक ret;
	काष्ठा uart_clk *uclk;

	ret = omap1_clk_enable_generic(clk);
	अगर (ret == 0) अणु
		/* Set smart idle acknowledgement mode */
		uclk = (काष्ठा uart_clk *)clk;
		omap_ग_लिखोb((omap_पढ़ोb(uclk->sysc_addr) & ~0x10) | 8,
			    uclk->sysc_addr);
	पूर्ण

	वापस ret;
पूर्ण

/* XXX SYSC रेजिस्टर handling करोes not beदीर्घ in the घड़ी framework */
अटल व्योम omap1_clk_disable_uart_functional_16xx(काष्ठा clk *clk)
अणु
	काष्ठा uart_clk *uclk;

	/* Set क्रमce idle acknowledgement mode */
	uclk = (काष्ठा uart_clk *)clk;
	omap_ग_लिखोb((omap_पढ़ोb(uclk->sysc_addr) & ~0x18), uclk->sysc_addr);

	omap1_clk_disable_generic(clk);
पूर्ण

/* XXX SYSC रेजिस्टर handling करोes not beदीर्घ in the घड़ी framework */
स्थिर काष्ठा clkops clkops_uart_16xx = अणु
	.enable		= omap1_clk_enable_uart_functional_16xx,
	.disable	= omap1_clk_disable_uart_functional_16xx,
पूर्ण;

दीर्घ omap1_clk_round_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	अगर (clk->round_rate != शून्य)
		वापस clk->round_rate(clk, rate);

	वापस clk->rate;
पूर्ण

पूर्णांक omap1_clk_set_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	पूर्णांक  ret = -EINVAL;

	अगर (clk->set_rate)
		ret = clk->set_rate(clk, rate);
	वापस ret;
पूर्ण

/*
 * Omap1 घड़ी reset and init functions
 */

#अगर_घोषित CONFIG_OMAP_RESET_CLOCKS

व्योम omap1_clk_disable_unused(काष्ठा clk *clk)
अणु
	__u32 regval32;

	/* Clocks in the DSP करोमुख्य need api_ck. Just assume bootloader
	 * has not enabled any DSP घड़ीs */
	अगर (clk->enable_reg == DSP_IDLECT2) अणु
		pr_info("Skipping reset check for DSP domain clock \"%s\"\n",
			clk->name);
		वापस;
	पूर्ण

	/* Is the घड़ी alपढ़ोy disabled? */
	अगर (clk->flags & ENABLE_REG_32BIT)
		regval32 = __raw_पढ़ोl(clk->enable_reg);
	अन्यथा
		regval32 = __raw_पढ़ोw(clk->enable_reg);

	अगर ((regval32 & (1 << clk->enable_bit)) == 0)
		वापस;

	prपूर्णांकk(KERN_INFO "Disabling unused clock \"%s\"... ", clk->name);
	clk->ops->disable(clk);
	prपूर्णांकk(" done\n");
पूर्ण

#पूर्ण_अगर


पूर्णांक clk_enable(काष्ठा clk *clk)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(clk))
		वापस -EINVAL;

	spin_lock_irqsave(&घड़ीfw_lock, flags);
	ret = omap1_clk_enable(clk);
	spin_unlock_irqrestore(&घड़ीfw_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(clk_enable);

व्योम clk_disable(काष्ठा clk *clk)
अणु
	अचिन्हित दीर्घ flags;

	अगर (IS_ERR_OR_शून्य(clk))
		वापस;

	spin_lock_irqsave(&घड़ीfw_lock, flags);
	अगर (clk->usecount == 0) अणु
		pr_err("Trying disable clock %s with 0 usecount\n",
		       clk->name);
		WARN_ON(1);
		जाओ out;
	पूर्ण

	omap1_clk_disable(clk);

out:
	spin_unlock_irqrestore(&घड़ीfw_lock, flags);
पूर्ण
EXPORT_SYMBOL(clk_disable);

अचिन्हित दीर्घ clk_get_rate(काष्ठा clk *clk)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ ret;

	अगर (IS_ERR_OR_शून्य(clk))
		वापस 0;

	spin_lock_irqsave(&घड़ीfw_lock, flags);
	ret = clk->rate;
	spin_unlock_irqrestore(&घड़ीfw_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(clk_get_rate);

/*
 * Optional घड़ी functions defined in include/linux/clk.h
 */

दीर्घ clk_round_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	अचिन्हित दीर्घ flags;
	दीर्घ ret;

	अगर (IS_ERR_OR_शून्य(clk))
		वापस 0;

	spin_lock_irqsave(&घड़ीfw_lock, flags);
	ret = omap1_clk_round_rate(clk, rate);
	spin_unlock_irqrestore(&घड़ीfw_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(clk_round_rate);

पूर्णांक clk_set_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EINVAL;

	अगर (IS_ERR_OR_शून्य(clk))
		वापस ret;

	spin_lock_irqsave(&घड़ीfw_lock, flags);
	ret = omap1_clk_set_rate(clk, rate);
	अगर (ret == 0)
		propagate_rate(clk);
	spin_unlock_irqrestore(&घड़ीfw_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(clk_set_rate);

पूर्णांक clk_set_parent(काष्ठा clk *clk, काष्ठा clk *parent)
अणु
	WARN_ONCE(1, "clk_set_parent() not implemented for OMAP1\n");

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(clk_set_parent);

काष्ठा clk *clk_get_parent(काष्ठा clk *clk)
अणु
	वापस clk->parent;
पूर्ण
EXPORT_SYMBOL(clk_get_parent);

/*
 * OMAP specअगरic घड़ी functions shared between omap1 and omap2
 */

/* Used क्रम घड़ीs that always have same value as the parent घड़ी */
अचिन्हित दीर्घ followparent_recalc(काष्ठा clk *clk)
अणु
	वापस clk->parent->rate;
पूर्ण

/*
 * Used क्रम घड़ीs that have the same value as the parent घड़ी,
 * भागided by some factor
 */
अचिन्हित दीर्घ omap_fixed_भागisor_recalc(काष्ठा clk *clk)
अणु
	WARN_ON(!clk->fixed_भाग);

	वापस clk->parent->rate / clk->fixed_भाग;
पूर्ण

व्योम clk_reparent(काष्ठा clk *child, काष्ठा clk *parent)
अणु
	list_del_init(&child->sibling);
	अगर (parent)
		list_add(&child->sibling, &parent->children);
	child->parent = parent;

	/* now करो the debugfs renaming to reattach the child
	   to the proper parent */
पूर्ण

/* Propagate rate to children */
व्योम propagate_rate(काष्ठा clk *tclk)
अणु
	काष्ठा clk *clkp;

	list_क्रम_each_entry(clkp, &tclk->children, sibling) अणु
		अगर (clkp->recalc)
			clkp->rate = clkp->recalc(clkp);
		propagate_rate(clkp);
	पूर्ण
पूर्ण

अटल LIST_HEAD(root_clks);

/**
 * recalculate_root_घड़ीs - recalculate and propagate all root घड़ीs
 *
 * Recalculates all root घड़ीs (घड़ीs with no parent), which अगर the
 * घड़ी's .recalc is set correctly, should also propagate their rates.
 * Called at init.
 */
व्योम recalculate_root_घड़ीs(व्योम)
अणु
	काष्ठा clk *clkp;

	list_क्रम_each_entry(clkp, &root_clks, sibling) अणु
		अगर (clkp->recalc)
			clkp->rate = clkp->recalc(clkp);
		propagate_rate(clkp);
	पूर्ण
पूर्ण

/**
 * clk_preinit - initialize any fields in the काष्ठा clk beक्रमe clk init
 * @clk: काष्ठा clk * to initialize
 *
 * Initialize any काष्ठा clk fields needed beक्रमe normal clk initialization
 * can run.  No वापस value.
 */
व्योम clk_preinit(काष्ठा clk *clk)
अणु
	INIT_LIST_HEAD(&clk->children);
पूर्ण

पूर्णांक clk_रेजिस्टर(काष्ठा clk *clk)
अणु
	अगर (IS_ERR_OR_शून्य(clk))
		वापस -EINVAL;

	/*
	 * trap out alपढ़ोy रेजिस्टरed घड़ीs
	 */
	अगर (clk->node.next || clk->node.prev)
		वापस 0;

	mutex_lock(&घड़ीs_mutex);
	अगर (clk->parent)
		list_add(&clk->sibling, &clk->parent->children);
	अन्यथा
		list_add(&clk->sibling, &root_clks);

	list_add(&clk->node, &घड़ीs);
	अगर (clk->init)
		clk->init(clk);
	mutex_unlock(&घड़ीs_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(clk_रेजिस्टर);

व्योम clk_unरेजिस्टर(काष्ठा clk *clk)
अणु
	अगर (IS_ERR_OR_शून्य(clk))
		वापस;

	mutex_lock(&घड़ीs_mutex);
	list_del(&clk->sibling);
	list_del(&clk->node);
	mutex_unlock(&घड़ीs_mutex);
पूर्ण
EXPORT_SYMBOL(clk_unरेजिस्टर);

व्योम clk_enable_init_घड़ीs(व्योम)
अणु
	काष्ठा clk *clkp;

	list_क्रम_each_entry(clkp, &घड़ीs, node)
		अगर (clkp->flags & ENABLE_ON_INIT)
			clk_enable(clkp);
पूर्ण

/**
 * omap_clk_get_by_name - locate OMAP काष्ठा clk by its name
 * @name: name of the काष्ठा clk to locate
 *
 * Locate an OMAP काष्ठा clk by its name.  Assumes that काष्ठा clk
 * names are unique.  Returns शून्य अगर not found or a poपूर्णांकer to the
 * काष्ठा clk अगर found.
 */
काष्ठा clk *omap_clk_get_by_name(स्थिर अक्षर *name)
अणु
	काष्ठा clk *c;
	काष्ठा clk *ret = शून्य;

	mutex_lock(&घड़ीs_mutex);

	list_क्रम_each_entry(c, &घड़ीs, node) अणु
		अगर (!म_भेद(c->name, name)) अणु
			ret = c;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&घड़ीs_mutex);

	वापस ret;
पूर्ण

पूर्णांक omap_clk_enable_स्वतःidle_all(व्योम)
अणु
	काष्ठा clk *c;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&घड़ीfw_lock, flags);

	list_क्रम_each_entry(c, &घड़ीs, node)
		अगर (c->ops->allow_idle)
			c->ops->allow_idle(c);

	spin_unlock_irqrestore(&घड़ीfw_lock, flags);

	वापस 0;
पूर्ण

पूर्णांक omap_clk_disable_स्वतःidle_all(व्योम)
अणु
	काष्ठा clk *c;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&घड़ीfw_lock, flags);

	list_क्रम_each_entry(c, &घड़ीs, node)
		अगर (c->ops->deny_idle)
			c->ops->deny_idle(c);

	spin_unlock_irqrestore(&घड़ीfw_lock, flags);

	वापस 0;
पूर्ण

/*
 * Low level helpers
 */
अटल पूर्णांक clkll_enable_null(काष्ठा clk *clk)
अणु
	वापस 0;
पूर्ण

अटल व्योम clkll_disable_null(काष्ठा clk *clk)
अणु
पूर्ण

स्थिर काष्ठा clkops clkops_null = अणु
	.enable		= clkll_enable_null,
	.disable	= clkll_disable_null,
पूर्ण;

/*
 * Dummy घड़ी
 *
 * Used क्रम घड़ी aliases that are needed on some OMAPs, but not others
 */
काष्ठा clk dummy_ck = अणु
	.name	= "dummy",
	.ops	= &clkops_null,
पूर्ण;

/*
 *
 */

#अगर_घोषित CONFIG_OMAP_RESET_CLOCKS
/*
 * Disable any unused घड़ीs left on by the bootloader
 */
अटल पूर्णांक __init clk_disable_unused(व्योम)
अणु
	काष्ठा clk *ck;
	अचिन्हित दीर्घ flags;

	pr_info("clock: disabling unused clocks to save power\n");

	spin_lock_irqsave(&घड़ीfw_lock, flags);
	list_क्रम_each_entry(ck, &घड़ीs, node) अणु
		अगर (ck->ops == &clkops_null)
			जारी;

		अगर (ck->usecount > 0 || !ck->enable_reg)
			जारी;

		omap1_clk_disable_unused(ck);
	पूर्ण
	spin_unlock_irqrestore(&घड़ीfw_lock, flags);

	वापस 0;
पूर्ण
late_initcall(clk_disable_unused);
late_initcall(omap_clk_enable_स्वतःidle_all);
#पूर्ण_अगर

#अगर defined(CONFIG_PM_DEBUG) && defined(CONFIG_DEBUG_FS)
/*
 *	debugfs support to trace घड़ी tree hierarchy and attributes
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

अटल काष्ठा dentry *clk_debugfs_root;

अटल पूर्णांक debug_घड़ी_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा clk *c;
	काष्ठा clk *pa;

	mutex_lock(&घड़ीs_mutex);
	seq_म_लिखो(s, "%-30s %-30s %-10s %s\n",
		   "clock-name", "parent-name", "rate", "use-count");

	list_क्रम_each_entry(c, &घड़ीs, node) अणु
		pa = c->parent;
		seq_म_लिखो(s, "%-30s %-30s %-10lu %d\n",
			   c->name, pa ? pa->name : "none", c->rate,
			   c->usecount);
	पूर्ण
	mutex_unlock(&घड़ीs_mutex);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(debug_घड़ी);

अटल व्योम clk_debugfs_रेजिस्टर_one(काष्ठा clk *c)
अणु
	काष्ठा dentry *d;
	काष्ठा clk *pa = c->parent;

	d = debugfs_create_dir(c->name, pa ? pa->dent : clk_debugfs_root);
	c->dent = d;

	debugfs_create_u8("usecount", S_IRUGO, c->dent, &c->usecount);
	debugfs_create_uदीर्घ("rate", S_IRUGO, c->dent, &c->rate);
	debugfs_create_x8("flags", S_IRUGO, c->dent, &c->flags);
पूर्ण

अटल व्योम clk_debugfs_रेजिस्टर(काष्ठा clk *c)
अणु
	काष्ठा clk *pa = c->parent;

	अगर (pa && !pa->dent)
		clk_debugfs_रेजिस्टर(pa);

	अगर (!c->dent)
		clk_debugfs_रेजिस्टर_one(c);
पूर्ण

अटल पूर्णांक __init clk_debugfs_init(व्योम)
अणु
	काष्ठा clk *c;
	काष्ठा dentry *d;

	d = debugfs_create_dir("clock", शून्य);
	clk_debugfs_root = d;

	list_क्रम_each_entry(c, &घड़ीs, node)
		clk_debugfs_रेजिस्टर(c);

	debugfs_create_file("summary", S_IRUGO, d, शून्य, &debug_घड़ी_fops);

	वापस 0;
पूर्ण
late_initcall(clk_debugfs_init);

#पूर्ण_अगर /* defined(CONFIG_PM_DEBUG) && defined(CONFIG_DEBUG_FS) */
