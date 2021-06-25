<शैली गुरु>
/*
 * AM33XX PRM functions
 *
 * Copyright (C) 2011-2012 Texas Instruments Incorporated - https://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>

#समावेश "powerdomain.h"
#समावेश "prm33xx.h"
#समावेश "prm-regbits-33xx.h"

#घोषणा AM33XX_PRM_RSTCTRL_OFFSET		0x0000

#घोषणा AM33XX_RST_GLOBAL_WARM_SW_MASK		(1 << 0)

/* Read a रेजिस्टर in a PRM instance */
अटल u32 am33xx_prm_पढ़ो_reg(s16 inst, u16 idx)
अणु
	वापस पढ़ोl_relaxed(prm_base.va + inst + idx);
पूर्ण

/* Write पूर्णांकo a रेजिस्टर in a PRM instance */
अटल व्योम am33xx_prm_ग_लिखो_reg(u32 val, s16 inst, u16 idx)
अणु
	ग_लिखोl_relaxed(val, prm_base.va + inst + idx);
पूर्ण

/* Read-modअगरy-ग_लिखो a रेजिस्टर in PRM. Caller must lock */
अटल u32 am33xx_prm_rmw_reg_bits(u32 mask, u32 bits, s16 inst, s16 idx)
अणु
	u32 v;

	v = am33xx_prm_पढ़ो_reg(inst, idx);
	v &= ~mask;
	v |= bits;
	am33xx_prm_ग_लिखो_reg(v, inst, idx);

	वापस v;
पूर्ण

/**
 * am33xx_prm_is_hardreset_निश्चितed - पढ़ो the HW reset line state of
 * submodules contained in the hwmod module
 * @shअगरt: रेजिस्टर bit shअगरt corresponding to the reset line to check
 * @part: PRM partition, ignored क्रम AM33xx
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @rstctrl_offs: RM_RSTCTRL रेजिस्टर address offset क्रम this module
 *
 * Returns 1 अगर the (sub)module hardreset line is currently निश्चितed,
 * 0 अगर the (sub)module hardreset line is not currently निश्चितed, or
 * -EINVAL upon parameter error.
 */
अटल पूर्णांक am33xx_prm_is_hardreset_निश्चितed(u8 shअगरt, u8 part, s16 inst,
					    u16 rstctrl_offs)
अणु
	u32 v;

	v = am33xx_prm_पढ़ो_reg(inst, rstctrl_offs);
	v &= 1 << shअगरt;
	v >>= shअगरt;

	वापस v;
पूर्ण

/**
 * am33xx_prm_निश्चित_hardreset - निश्चित the HW reset line of a submodule
 * @shअगरt: रेजिस्टर bit shअगरt corresponding to the reset line to निश्चित
 * @part: CM partition, ignored क्रम AM33xx
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @rstctrl_reg: RM_RSTCTRL रेजिस्टर address क्रम this module
 *
 * Some IPs like dsp, ipu or iva contain processors that require an HW
 * reset line to be निश्चितed / deनिश्चितed in order to fully enable the
 * IP.  These modules may have multiple hard-reset lines that reset
 * dअगरferent 'submodules' inside the IP block.  This function will
 * place the submodule पूर्णांकo reset.  Returns 0 upon success or -EINVAL
 * upon an argument error.
 */
अटल पूर्णांक am33xx_prm_निश्चित_hardreset(u8 shअगरt, u8 part, s16 inst,
				       u16 rstctrl_offs)
अणु
	u32 mask = 1 << shअगरt;

	am33xx_prm_rmw_reg_bits(mask, mask, inst, rstctrl_offs);

	वापस 0;
पूर्ण

/**
 * am33xx_prm_deनिश्चित_hardreset - deनिश्चित a submodule hardreset line and
 * रुको
 * @shअगरt: रेजिस्टर bit shअगरt corresponding to the reset line to deनिश्चित
 * @st_shअगरt: reset status रेजिस्टर bit shअगरt corresponding to the reset line
 * @part: PRM partition, not used क्रम AM33xx
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @rstctrl_reg: RM_RSTCTRL रेजिस्टर address क्रम this module
 * @rstst_reg: RM_RSTST रेजिस्टर address क्रम this module
 *
 * Some IPs like dsp, ipu or iva contain processors that require an HW
 * reset line to be निश्चितed / deनिश्चितed in order to fully enable the
 * IP.  These modules may have multiple hard-reset lines that reset
 * dअगरferent 'submodules' inside the IP block.  This function will
 * take the submodule out of reset and रुको until the PRCM indicates
 * that the reset has completed beक्रमe वापसing.  Returns 0 upon success or
 * -EINVAL upon an argument error, -EEXIST अगर the submodule was alपढ़ोy out
 * of reset, or -EBUSY अगर the submodule did not निकास reset promptly.
 */
अटल पूर्णांक am33xx_prm_deनिश्चित_hardreset(u8 shअगरt, u8 st_shअगरt, u8 part,
					 s16 inst, u16 rstctrl_offs,
					 u16 rstst_offs)
अणु
	पूर्णांक c;
	u32 mask = 1 << st_shअगरt;

	/* Check the current status to aव्योम  de-निश्चितing the line twice */
	अगर (am33xx_prm_is_hardreset_निश्चितed(shअगरt, 0, inst, rstctrl_offs) == 0)
		वापस -EEXIST;

	/* Clear the reset status by writing 1 to the status bit */
	am33xx_prm_rmw_reg_bits(0xffffffff, mask, inst, rstst_offs);

	/* de-निश्चित the reset control line */
	mask = 1 << shअगरt;

	am33xx_prm_rmw_reg_bits(mask, 0, inst, rstctrl_offs);

	/* रुको the status to be set */
	omap_test_समयout(am33xx_prm_is_hardreset_निश्चितed(st_shअगरt, 0, inst,
							   rstst_offs),
			  MAX_MODULE_HARDRESET_WAIT, c);

	वापस (c == MAX_MODULE_HARDRESET_WAIT) ? -EBUSY : 0;
पूर्ण

अटल पूर्णांक am33xx_pwrdm_set_next_pwrst(काष्ठा घातerकरोमुख्य *pwrdm, u8 pwrst)
अणु
	am33xx_prm_rmw_reg_bits(OMAP_POWERSTATE_MASK,
				(pwrst << OMAP_POWERSTATE_SHIFT),
				pwrdm->prcm_offs, pwrdm->pwrstctrl_offs);
	वापस 0;
पूर्ण

अटल पूर्णांक am33xx_pwrdm_पढ़ो_next_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	u32 v;

	v = am33xx_prm_पढ़ो_reg(pwrdm->prcm_offs,  pwrdm->pwrstctrl_offs);
	v &= OMAP_POWERSTATE_MASK;
	v >>= OMAP_POWERSTATE_SHIFT;

	वापस v;
पूर्ण

अटल पूर्णांक am33xx_pwrdm_पढ़ो_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	u32 v;

	v = am33xx_prm_पढ़ो_reg(pwrdm->prcm_offs, pwrdm->pwrstst_offs);
	v &= OMAP_POWERSTATEST_MASK;
	v >>= OMAP_POWERSTATEST_SHIFT;

	वापस v;
पूर्ण

अटल पूर्णांक am33xx_pwrdm_set_lowpwrstchange(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	am33xx_prm_rmw_reg_bits(AM33XX_LOWPOWERSTATECHANGE_MASK,
				(1 << AM33XX_LOWPOWERSTATECHANGE_SHIFT),
				pwrdm->prcm_offs, pwrdm->pwrstctrl_offs);
	वापस 0;
पूर्ण

अटल पूर्णांक am33xx_pwrdm_clear_all_prev_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	am33xx_prm_rmw_reg_bits(AM33XX_LASTPOWERSTATEENTERED_MASK,
				AM33XX_LASTPOWERSTATEENTERED_MASK,
				pwrdm->prcm_offs, pwrdm->pwrstst_offs);
	वापस 0;
पूर्ण

अटल पूर्णांक am33xx_pwrdm_set_logic_retst(काष्ठा घातerकरोमुख्य *pwrdm, u8 pwrst)
अणु
	u32 m;

	m = pwrdm->logicretstate_mask;
	अगर (!m)
		वापस -EINVAL;

	am33xx_prm_rmw_reg_bits(m, (pwrst << __ffs(m)),
				pwrdm->prcm_offs, pwrdm->pwrstctrl_offs);

	वापस 0;
पूर्ण

अटल पूर्णांक am33xx_pwrdm_पढ़ो_logic_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	u32 v;

	v = am33xx_prm_पढ़ो_reg(pwrdm->prcm_offs, pwrdm->pwrstst_offs);
	v &= AM33XX_LOGICSTATEST_MASK;
	v >>= AM33XX_LOGICSTATEST_SHIFT;

	वापस v;
पूर्ण

अटल पूर्णांक am33xx_pwrdm_पढ़ो_logic_retst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	u32 v, m;

	m = pwrdm->logicretstate_mask;
	अगर (!m)
		वापस -EINVAL;

	v = am33xx_prm_पढ़ो_reg(pwrdm->prcm_offs, pwrdm->pwrstctrl_offs);
	v &= m;
	v >>= __ffs(m);

	वापस v;
पूर्ण

अटल पूर्णांक am33xx_pwrdm_set_mem_onst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank,
		u8 pwrst)
अणु
	u32 m;

	m = pwrdm->mem_on_mask[bank];
	अगर (!m)
		वापस -EINVAL;

	am33xx_prm_rmw_reg_bits(m, (pwrst << __ffs(m)),
				pwrdm->prcm_offs, pwrdm->pwrstctrl_offs);

	वापस 0;
पूर्ण

अटल पूर्णांक am33xx_pwrdm_set_mem_retst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank,
					u8 pwrst)
अणु
	u32 m;

	m = pwrdm->mem_ret_mask[bank];
	अगर (!m)
		वापस -EINVAL;

	am33xx_prm_rmw_reg_bits(m, (pwrst << __ffs(m)),
				pwrdm->prcm_offs, pwrdm->pwrstctrl_offs);

	वापस 0;
पूर्ण

अटल पूर्णांक am33xx_pwrdm_पढ़ो_mem_pwrst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank)
अणु
	u32 m, v;

	m = pwrdm->mem_pwrst_mask[bank];
	अगर (!m)
		वापस -EINVAL;

	v = am33xx_prm_पढ़ो_reg(pwrdm->prcm_offs, pwrdm->pwrstst_offs);
	v &= m;
	v >>= __ffs(m);

	वापस v;
पूर्ण

अटल पूर्णांक am33xx_pwrdm_पढ़ो_mem_retst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank)
अणु
	u32 m, v;

	m = pwrdm->mem_retst_mask[bank];
	अगर (!m)
		वापस -EINVAL;

	v = am33xx_prm_पढ़ो_reg(pwrdm->prcm_offs, pwrdm->pwrstctrl_offs);
	v &= m;
	v >>= __ffs(m);

	वापस v;
पूर्ण

अटल पूर्णांक am33xx_pwrdm_रुको_transition(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	u32 c = 0;

	/*
	 * REVISIT: pwrdm_रुको_transition() may be better implemented
	 * via a callback and a periodic समयr check -- how दीर्घ करो we expect
	 * घातerकरोमुख्य transitions to take?
	 */

	/* XXX Is this udelay() value meaningful? */
	जबतक ((am33xx_prm_पढ़ो_reg(pwrdm->prcm_offs, pwrdm->pwrstst_offs)
			& OMAP_INTRANSITION_MASK) &&
			(c++ < PWRDM_TRANSITION_BAILOUT))
		udelay(1);

	अगर (c > PWRDM_TRANSITION_BAILOUT) अणु
		pr_err("powerdomain: %s: waited too long to complete transition\n",
		       pwrdm->name);
		वापस -EAGAIN;
	पूर्ण

	pr_debug("powerdomain: completed transition in %d loops\n", c);

	वापस 0;
पूर्ण

अटल पूर्णांक am33xx_check_vcvp(व्योम)
अणु
	/* No VC/VP on am33xx devices */
	वापस 0;
पूर्ण

/**
 * am33xx_prm_global_warm_sw_reset - reboot the device via warm reset
 *
 * Immediately reboots the device through warm reset.
 */
अटल व्योम am33xx_prm_global_warm_sw_reset(व्योम)
अणु
	am33xx_prm_rmw_reg_bits(AM33XX_RST_GLOBAL_WARM_SW_MASK,
				AM33XX_RST_GLOBAL_WARM_SW_MASK,
				AM33XX_PRM_DEVICE_MOD,
				AM33XX_PRM_RSTCTRL_OFFSET);

	/* OCP barrier */
	(व्योम)am33xx_prm_पढ़ो_reg(AM33XX_PRM_DEVICE_MOD,
				  AM33XX_PRM_RSTCTRL_OFFSET);
पूर्ण

अटल व्योम am33xx_pwrdm_save_context(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	pwrdm->context = am33xx_prm_पढ़ो_reg(pwrdm->prcm_offs,
						pwrdm->pwrstctrl_offs);
	/*
	 * Do not save LOWPOWERSTATECHANGE, writing a 1 indicates a request,
	 * पढ़ोing back a 1 indicates a request in progress.
	 */
	pwrdm->context &= ~AM33XX_LOWPOWERSTATECHANGE_MASK;
पूर्ण

अटल व्योम am33xx_pwrdm_restore_context(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	पूर्णांक st, ctrl;

	st = am33xx_prm_पढ़ो_reg(pwrdm->prcm_offs,
				 pwrdm->pwrstst_offs);

	am33xx_prm_ग_लिखो_reg(pwrdm->context, pwrdm->prcm_offs,
			     pwrdm->pwrstctrl_offs);

	/* Make sure we only रुको क्रम a transition अगर there is one */
	st &= OMAP_POWERSTATEST_MASK;
	ctrl = OMAP_POWERSTATEST_MASK & pwrdm->context;

	अगर (st != ctrl)
		am33xx_pwrdm_रुको_transition(pwrdm);
पूर्ण

काष्ठा pwrdm_ops am33xx_pwrdm_operations = अणु
	.pwrdm_set_next_pwrst		= am33xx_pwrdm_set_next_pwrst,
	.pwrdm_पढ़ो_next_pwrst		= am33xx_pwrdm_पढ़ो_next_pwrst,
	.pwrdm_पढ़ो_pwrst		= am33xx_pwrdm_पढ़ो_pwrst,
	.pwrdm_set_logic_retst		= am33xx_pwrdm_set_logic_retst,
	.pwrdm_पढ़ो_logic_pwrst		= am33xx_pwrdm_पढ़ो_logic_pwrst,
	.pwrdm_पढ़ो_logic_retst		= am33xx_pwrdm_पढ़ो_logic_retst,
	.pwrdm_clear_all_prev_pwrst	= am33xx_pwrdm_clear_all_prev_pwrst,
	.pwrdm_set_lowpwrstchange	= am33xx_pwrdm_set_lowpwrstchange,
	.pwrdm_पढ़ो_mem_pwrst		= am33xx_pwrdm_पढ़ो_mem_pwrst,
	.pwrdm_पढ़ो_mem_retst		= am33xx_pwrdm_पढ़ो_mem_retst,
	.pwrdm_set_mem_onst		= am33xx_pwrdm_set_mem_onst,
	.pwrdm_set_mem_retst		= am33xx_pwrdm_set_mem_retst,
	.pwrdm_रुको_transition		= am33xx_pwrdm_रुको_transition,
	.pwrdm_has_voltdm		= am33xx_check_vcvp,
	.pwrdm_save_context		= am33xx_pwrdm_save_context,
	.pwrdm_restore_context		= am33xx_pwrdm_restore_context,
पूर्ण;

अटल काष्ठा prm_ll_data am33xx_prm_ll_data = अणु
	.निश्चित_hardreset		= am33xx_prm_निश्चित_hardreset,
	.deनिश्चित_hardreset		= am33xx_prm_deनिश्चित_hardreset,
	.is_hardreset_निश्चितed		= am33xx_prm_is_hardreset_निश्चितed,
	.reset_प्रणाली			= am33xx_prm_global_warm_sw_reset,
पूर्ण;

पूर्णांक __init am33xx_prm_init(स्थिर काष्ठा omap_prcm_init_data *data)
अणु
	वापस prm_रेजिस्टर(&am33xx_prm_ll_data);
पूर्ण

अटल व्योम __निकास am33xx_prm_निकास(व्योम)
अणु
	prm_unरेजिस्टर(&am33xx_prm_ll_data);
पूर्ण
__निकासcall(am33xx_prm_निकास);
