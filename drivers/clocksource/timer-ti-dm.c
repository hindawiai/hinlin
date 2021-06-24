<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * linux/arch/arm/plat-omap/dmसमयr.c
 *
 * OMAP Dual-Mode Timers
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - https://www.ti.com/
 * Tarun Kanti DebBarma <tarun.kanti@ti.com>
 * Thara Gopinath <thara@ti.com>
 *
 * dmसमयr adaptation to platक्रमm_driver.
 *
 * Copyright (C) 2005 Nokia Corporation
 * OMAP2 support by Juha Yrjola
 * API improvements and OMAP2 घड़ी framework support by Timo Teras
 *
 * Copyright (C) 2009 Texas Instruments
 * Added OMAP4 support - Santosh Shilimkar <santosh.shilimkar@ti.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/dmसमयr-omap.h>

#समावेश <घड़ीsource/समयr-ti-dm.h>

अटल u32 omap_reserved_sysसमयrs;
अटल LIST_HEAD(omap_समयr_list);
अटल DEFINE_SPINLOCK(dm_समयr_lock);

क्रमागत अणु
	REQUEST_ANY = 0,
	REQUEST_BY_ID,
	REQUEST_BY_CAP,
	REQUEST_BY_NODE,
पूर्ण;

/**
 * omap_dm_समयr_पढ़ो_reg - पढ़ो समयr रेजिस्टरs in posted and non-posted mode
 * @समयr:      समयr poपूर्णांकer over which पढ़ो operation to perक्रमm
 * @reg:        lowest byte holds the रेजिस्टर offset
 *
 * The posted mode bit is encoded in reg. Note that in posted mode ग_लिखो
 * pending bit must be checked. Otherwise a पढ़ो of a non completed ग_लिखो
 * will produce an error.
 */
अटल अंतरभूत u32 omap_dm_समयr_पढ़ो_reg(काष्ठा omap_dm_समयr *समयr, u32 reg)
अणु
	WARN_ON((reg & 0xff) < _OMAP_TIMER_WAKEUP_EN_OFFSET);
	वापस __omap_dm_समयr_पढ़ो(समयr, reg, समयr->posted);
पूर्ण

/**
 * omap_dm_समयr_ग_लिखो_reg - ग_लिखो समयr रेजिस्टरs in posted and non-posted mode
 * @समयr:      समयr poपूर्णांकer over which ग_लिखो operation is to perक्रमm
 * @reg:        lowest byte holds the रेजिस्टर offset
 * @value:      data to ग_लिखो पूर्णांकo the रेजिस्टर
 *
 * The posted mode bit is encoded in reg. Note that in posted mode the ग_लिखो
 * pending bit must be checked. Otherwise a ग_लिखो on a रेजिस्टर which has a
 * pending ग_लिखो will be lost.
 */
अटल व्योम omap_dm_समयr_ग_लिखो_reg(काष्ठा omap_dm_समयr *समयr, u32 reg,
						u32 value)
अणु
	WARN_ON((reg & 0xff) < _OMAP_TIMER_WAKEUP_EN_OFFSET);
	__omap_dm_समयr_ग_लिखो(समयr, reg, value, समयr->posted);
पूर्ण

अटल व्योम omap_समयr_restore_context(काष्ठा omap_dm_समयr *समयr)
अणु
	omap_dm_समयr_ग_लिखो_reg(समयr, OMAP_TIMER_WAKEUP_EN_REG,
				समयr->context.twer);
	omap_dm_समयr_ग_लिखो_reg(समयr, OMAP_TIMER_COUNTER_REG,
				समयr->context.tcrr);
	omap_dm_समयr_ग_लिखो_reg(समयr, OMAP_TIMER_LOAD_REG,
				समयr->context.tldr);
	omap_dm_समयr_ग_लिखो_reg(समयr, OMAP_TIMER_MATCH_REG,
				समयr->context.पंचांगar);
	omap_dm_समयr_ग_लिखो_reg(समयr, OMAP_TIMER_IF_CTRL_REG,
				समयr->context.tsicr);
	ग_लिखोl_relaxed(समयr->context.tier, समयr->irq_ena);
	omap_dm_समयr_ग_लिखो_reg(समयr, OMAP_TIMER_CTRL_REG,
				समयr->context.tclr);
पूर्ण

अटल व्योम omap_समयr_save_context(काष्ठा omap_dm_समयr *समयr)
अणु
	समयr->context.tclr =
			omap_dm_समयr_पढ़ो_reg(समयr, OMAP_TIMER_CTRL_REG);
	समयr->context.twer =
			omap_dm_समयr_पढ़ो_reg(समयr, OMAP_TIMER_WAKEUP_EN_REG);
	समयr->context.tldr =
			omap_dm_समयr_पढ़ो_reg(समयr, OMAP_TIMER_LOAD_REG);
	समयr->context.पंचांगar =
			omap_dm_समयr_पढ़ो_reg(समयr, OMAP_TIMER_MATCH_REG);
	समयr->context.tier = पढ़ोl_relaxed(समयr->irq_ena);
	समयr->context.tsicr =
			omap_dm_समयr_पढ़ो_reg(समयr, OMAP_TIMER_IF_CTRL_REG);
पूर्ण

अटल पूर्णांक omap_समयr_context_notअगरier(काष्ठा notअगरier_block *nb,
				       अचिन्हित दीर्घ cmd, व्योम *v)
अणु
	काष्ठा omap_dm_समयr *समयr;

	समयr = container_of(nb, काष्ठा omap_dm_समयr, nb);

	चयन (cmd) अणु
	हाल CPU_CLUSTER_PM_ENTER:
		अगर ((समयr->capability & OMAP_TIMER_ALWON) ||
		    !atomic_पढ़ो(&समयr->enabled))
			अवरोध;
		omap_समयr_save_context(समयr);
		अवरोध;
	हाल CPU_CLUSTER_PM_ENTER_FAILED:
	हाल CPU_CLUSTER_PM_EXIT:
		अगर ((समयr->capability & OMAP_TIMER_ALWON) ||
		    !atomic_पढ़ो(&समयr->enabled))
			अवरोध;
		omap_समयr_restore_context(समयr);
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक omap_dm_समयr_reset(काष्ठा omap_dm_समयr *समयr)
अणु
	u32 l, समयout = 100000;

	अगर (समयr->revision != 1)
		वापस -EINVAL;

	omap_dm_समयr_ग_लिखो_reg(समयr, OMAP_TIMER_IF_CTRL_REG, 0x06);

	करो अणु
		l = __omap_dm_समयr_पढ़ो(समयr,
					 OMAP_TIMER_V1_SYS_STAT_OFFSET, 0);
	पूर्ण जबतक (!l && समयout--);

	अगर (!समयout) अणु
		dev_err(&समयr->pdev->dev, "Timer failed to reset\n");
		वापस -ETIMEDOUT;
	पूर्ण

	/* Configure समयr क्रम smart-idle mode */
	l = __omap_dm_समयr_पढ़ो(समयr, OMAP_TIMER_OCP_CFG_OFFSET, 0);
	l |= 0x2 << 0x3;
	__omap_dm_समयr_ग_लिखो(समयr, OMAP_TIMER_OCP_CFG_OFFSET, l, 0);

	समयr->posted = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_dm_समयr_set_source(काष्ठा omap_dm_समयr *समयr, पूर्णांक source)
अणु
	पूर्णांक ret;
	स्थिर अक्षर *parent_name;
	काष्ठा clk *parent;
	काष्ठा dmसमयr_platक्रमm_data *pdata;

	अगर (unlikely(!समयr) || IS_ERR(समयr->fclk))
		वापस -EINVAL;

	चयन (source) अणु
	हाल OMAP_TIMER_SRC_SYS_CLK:
		parent_name = "timer_sys_ck";
		अवरोध;
	हाल OMAP_TIMER_SRC_32_KHZ:
		parent_name = "timer_32k_ck";
		अवरोध;
	हाल OMAP_TIMER_SRC_EXT_CLK:
		parent_name = "timer_ext_ck";
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	pdata = समयr->pdev->dev.platक्रमm_data;

	/*
	 * FIXME: Used क्रम OMAP1 devices only because they करो not currently
	 * use the घड़ी framework to set the parent घड़ी. To be हटाओd
	 * once OMAP1 migrated to using घड़ी framework क्रम dmसमयrs
	 */
	अगर (pdata && pdata->set_समयr_src)
		वापस pdata->set_समयr_src(समयr->pdev, source);

#अगर defined(CONFIG_COMMON_CLK)
	/* Check अगर the घड़ी has configurable parents */
	अगर (clk_hw_get_num_parents(__clk_get_hw(समयr->fclk)) < 2)
		वापस 0;
#पूर्ण_अगर

	parent = clk_get(&समयr->pdev->dev, parent_name);
	अगर (IS_ERR(parent)) अणु
		pr_err("%s: %s not found\n", __func__, parent_name);
		वापस -EINVAL;
	पूर्ण

	ret = clk_set_parent(समयr->fclk, parent);
	अगर (ret < 0)
		pr_err("%s: failed to set %s as parent\n", __func__,
			parent_name);

	clk_put(parent);

	वापस ret;
पूर्ण

अटल व्योम omap_dm_समयr_enable(काष्ठा omap_dm_समयr *समयr)
अणु
	pm_runसमय_get_sync(&समयr->pdev->dev);
पूर्ण

अटल व्योम omap_dm_समयr_disable(काष्ठा omap_dm_समयr *समयr)
अणु
	pm_runसमय_put_sync(&समयr->pdev->dev);
पूर्ण

अटल पूर्णांक omap_dm_समयr_prepare(काष्ठा omap_dm_समयr *समयr)
अणु
	पूर्णांक rc;

	/*
	 * FIXME: OMAP1 devices करो not use the घड़ी framework क्रम dmसमयrs so
	 * करो not call clk_get() क्रम these devices.
	 */
	अगर (!(समयr->capability & OMAP_TIMER_NEEDS_RESET)) अणु
		समयr->fclk = clk_get(&समयr->pdev->dev, "fck");
		अगर (WARN_ON_ONCE(IS_ERR(समयr->fclk))) अणु
			dev_err(&समयr->pdev->dev, ": No fclk handle.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	omap_dm_समयr_enable(समयr);

	अगर (समयr->capability & OMAP_TIMER_NEEDS_RESET) अणु
		rc = omap_dm_समयr_reset(समयr);
		अगर (rc) अणु
			omap_dm_समयr_disable(समयr);
			वापस rc;
		पूर्ण
	पूर्ण

	__omap_dm_समयr_enable_posted(समयr);
	omap_dm_समयr_disable(समयr);

	वापस 0;
पूर्ण

अटल अंतरभूत u32 omap_dm_समयr_reserved_sysसमयr(पूर्णांक id)
अणु
	वापस (omap_reserved_sysसमयrs & (1 << (id - 1))) ? 1 : 0;
पूर्ण

पूर्णांक omap_dm_समयr_reserve_sysसमयr(पूर्णांक id)
अणु
	अगर (omap_dm_समयr_reserved_sysसमयr(id))
		वापस -ENODEV;

	omap_reserved_sysसमयrs |= (1 << (id - 1));

	वापस 0;
पूर्ण

अटल काष्ठा omap_dm_समयr *_omap_dm_समयr_request(पूर्णांक req_type, व्योम *data)
अणु
	काष्ठा omap_dm_समयr *समयr = शून्य, *t;
	काष्ठा device_node *np = शून्य;
	अचिन्हित दीर्घ flags;
	u32 cap = 0;
	पूर्णांक id = 0;

	चयन (req_type) अणु
	हाल REQUEST_BY_ID:
		id = *(पूर्णांक *)data;
		अवरोध;
	हाल REQUEST_BY_CAP:
		cap = *(u32 *)data;
		अवरोध;
	हाल REQUEST_BY_NODE:
		np = (काष्ठा device_node *)data;
		अवरोध;
	शेष:
		/* REQUEST_ANY */
		अवरोध;
	पूर्ण

	spin_lock_irqsave(&dm_समयr_lock, flags);
	list_क्रम_each_entry(t, &omap_समयr_list, node) अणु
		अगर (t->reserved)
			जारी;

		चयन (req_type) अणु
		हाल REQUEST_BY_ID:
			अगर (id == t->pdev->id) अणु
				समयr = t;
				समयr->reserved = 1;
				जाओ found;
			पूर्ण
			अवरोध;
		हाल REQUEST_BY_CAP:
			अगर (cap == (t->capability & cap)) अणु
				/*
				 * If समयr is not शून्य, we have alपढ़ोy found
				 * one समयr. But it was not an exact match
				 * because it had more capabilities than what
				 * was required. Thereक्रमe, unreserve the last
				 * समयr found and see अगर this one is a better
				 * match.
				 */
				अगर (समयr)
					समयr->reserved = 0;
				समयr = t;
				समयr->reserved = 1;

				/* Exit loop early अगर we find an exact match */
				अगर (t->capability == cap)
					जाओ found;
			पूर्ण
			अवरोध;
		हाल REQUEST_BY_NODE:
			अगर (np == t->pdev->dev.of_node) अणु
				समयr = t;
				समयr->reserved = 1;
				जाओ found;
			पूर्ण
			अवरोध;
		शेष:
			/* REQUEST_ANY */
			समयr = t;
			समयr->reserved = 1;
			जाओ found;
		पूर्ण
	पूर्ण
found:
	spin_unlock_irqrestore(&dm_समयr_lock, flags);

	अगर (समयr && omap_dm_समयr_prepare(समयr)) अणु
		समयr->reserved = 0;
		समयr = शून्य;
	पूर्ण

	अगर (!समयr)
		pr_debug("%s: timer request failed!\n", __func__);

	वापस समयr;
पूर्ण

अटल काष्ठा omap_dm_समयr *omap_dm_समयr_request(व्योम)
अणु
	वापस _omap_dm_समयr_request(REQUEST_ANY, शून्य);
पूर्ण

अटल काष्ठा omap_dm_समयr *omap_dm_समयr_request_specअगरic(पूर्णांक id)
अणु
	/* Requesting समयr by ID is not supported when device tree is used */
	अगर (of_have_populated_dt()) अणु
		pr_warn("%s: Please use omap_dm_timer_request_by_node()\n",
			__func__);
		वापस शून्य;
	पूर्ण

	वापस _omap_dm_समयr_request(REQUEST_BY_ID, &id);
पूर्ण

/**
 * omap_dm_समयr_request_by_cap - Request a समयr by capability
 * @cap:	Bit mask of capabilities to match
 *
 * Find a समयr based upon capabilities bit mask. Callers of this function
 * should use the definitions found in the plat/dmसमयr.h file under the
 * comment "timer capabilities used in hwmod database". Returns poपूर्णांकer to
 * समयr handle on success and a शून्य poपूर्णांकer on failure.
 */
काष्ठा omap_dm_समयr *omap_dm_समयr_request_by_cap(u32 cap)
अणु
	वापस _omap_dm_समयr_request(REQUEST_BY_CAP, &cap);
पूर्ण

/**
 * omap_dm_समयr_request_by_node - Request a समयr by device-tree node
 * @np:		Poपूर्णांकer to device-tree समयr node
 *
 * Request a समयr based upon a device node poपूर्णांकer. Returns poपूर्णांकer to
 * समयr handle on success and a शून्य poपूर्णांकer on failure.
 */
अटल काष्ठा omap_dm_समयr *omap_dm_समयr_request_by_node(काष्ठा device_node *np)
अणु
	अगर (!np)
		वापस शून्य;

	वापस _omap_dm_समयr_request(REQUEST_BY_NODE, np);
पूर्ण

अटल पूर्णांक omap_dm_समयr_मुक्त(काष्ठा omap_dm_समयr *समयr)
अणु
	अगर (unlikely(!समयr))
		वापस -EINVAL;

	clk_put(समयr->fclk);

	WARN_ON(!समयr->reserved);
	समयr->reserved = 0;
	वापस 0;
पूर्ण

पूर्णांक omap_dm_समयr_get_irq(काष्ठा omap_dm_समयr *समयr)
अणु
	अगर (समयr)
		वापस समयr->irq;
	वापस -EINVAL;
पूर्ण

#अगर defined(CONFIG_ARCH_OMAP1)
#समावेश <mach/hardware.h>

अटल काष्ठा clk *omap_dm_समयr_get_fclk(काष्ठा omap_dm_समयr *समयr)
अणु
	वापस शून्य;
पूर्ण

/**
 * omap_dm_समयr_modअगरy_idlect_mask - Check अगर any running समयrs use ARMXOR
 * @inpuपंचांगask: current value of idlect mask
 */
__u32 omap_dm_समयr_modअगरy_idlect_mask(__u32 inpuपंचांगask)
अणु
	पूर्णांक i = 0;
	काष्ठा omap_dm_समयr *समयr = शून्य;
	अचिन्हित दीर्घ flags;

	/* If ARMXOR cannot be idled this function call is unnecessary */
	अगर (!(inpuपंचांगask & (1 << 1)))
		वापस inpuपंचांगask;

	/* If any active समयr is using ARMXOR वापस modअगरied mask */
	spin_lock_irqsave(&dm_समयr_lock, flags);
	list_क्रम_each_entry(समयr, &omap_समयr_list, node) अणु
		u32 l;

		l = omap_dm_समयr_पढ़ो_reg(समयr, OMAP_TIMER_CTRL_REG);
		अगर (l & OMAP_TIMER_CTRL_ST) अणु
			अगर (((omap_पढ़ोl(MOD_CONF_CTRL_1) >> (i * 2)) & 0x03) == 0)
				inpuपंचांगask &= ~(1 << 1);
			अन्यथा
				inpuपंचांगask &= ~(1 << 2);
		पूर्ण
		i++;
	पूर्ण
	spin_unlock_irqrestore(&dm_समयr_lock, flags);

	वापस inpuपंचांगask;
पूर्ण

#अन्यथा

अटल काष्ठा clk *omap_dm_समयr_get_fclk(काष्ठा omap_dm_समयr *समयr)
अणु
	अगर (समयr && !IS_ERR(समयr->fclk))
		वापस समयr->fclk;
	वापस शून्य;
पूर्ण

__u32 omap_dm_समयr_modअगरy_idlect_mask(__u32 inpuपंचांगask)
अणु
	BUG();

	वापस 0;
पूर्ण

#पूर्ण_अगर

पूर्णांक omap_dm_समयr_trigger(काष्ठा omap_dm_समयr *समयr)
अणु
	अगर (unlikely(!समयr || !atomic_पढ़ो(&समयr->enabled))) अणु
		pr_err("%s: timer not available or enabled.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	omap_dm_समयr_ग_लिखो_reg(समयr, OMAP_TIMER_TRIGGER_REG, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक omap_dm_समयr_start(काष्ठा omap_dm_समयr *समयr)
अणु
	u32 l;

	अगर (unlikely(!समयr))
		वापस -EINVAL;

	omap_dm_समयr_enable(समयr);

	l = omap_dm_समयr_पढ़ो_reg(समयr, OMAP_TIMER_CTRL_REG);
	अगर (!(l & OMAP_TIMER_CTRL_ST)) अणु
		l |= OMAP_TIMER_CTRL_ST;
		omap_dm_समयr_ग_लिखो_reg(समयr, OMAP_TIMER_CTRL_REG, l);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap_dm_समयr_stop(काष्ठा omap_dm_समयr *समयr)
अणु
	अचिन्हित दीर्घ rate = 0;

	अगर (unlikely(!समयr))
		वापस -EINVAL;

	अगर (!(समयr->capability & OMAP_TIMER_NEEDS_RESET))
		rate = clk_get_rate(समयr->fclk);

	__omap_dm_समयr_stop(समयr, समयr->posted, rate);

	omap_dm_समयr_disable(समयr);
	वापस 0;
पूर्ण

अटल पूर्णांक omap_dm_समयr_set_load(काष्ठा omap_dm_समयr *समयr,
				  अचिन्हित पूर्णांक load)
अणु
	अगर (unlikely(!समयr))
		वापस -EINVAL;

	omap_dm_समयr_enable(समयr);
	omap_dm_समयr_ग_लिखो_reg(समयr, OMAP_TIMER_LOAD_REG, load);

	omap_dm_समयr_disable(समयr);
	वापस 0;
पूर्ण

अटल पूर्णांक omap_dm_समयr_set_match(काष्ठा omap_dm_समयr *समयr, पूर्णांक enable,
				   अचिन्हित पूर्णांक match)
अणु
	u32 l;

	अगर (unlikely(!समयr))
		वापस -EINVAL;

	omap_dm_समयr_enable(समयr);
	l = omap_dm_समयr_पढ़ो_reg(समयr, OMAP_TIMER_CTRL_REG);
	अगर (enable)
		l |= OMAP_TIMER_CTRL_CE;
	अन्यथा
		l &= ~OMAP_TIMER_CTRL_CE;
	omap_dm_समयr_ग_लिखो_reg(समयr, OMAP_TIMER_MATCH_REG, match);
	omap_dm_समयr_ग_लिखो_reg(समयr, OMAP_TIMER_CTRL_REG, l);

	omap_dm_समयr_disable(समयr);
	वापस 0;
पूर्ण

अटल पूर्णांक omap_dm_समयr_set_pwm(काष्ठा omap_dm_समयr *समयr, पूर्णांक def_on,
				 पूर्णांक toggle, पूर्णांक trigger, पूर्णांक स्वतःreload)
अणु
	u32 l;

	अगर (unlikely(!समयr))
		वापस -EINVAL;

	omap_dm_समयr_enable(समयr);
	l = omap_dm_समयr_पढ़ो_reg(समयr, OMAP_TIMER_CTRL_REG);
	l &= ~(OMAP_TIMER_CTRL_GPOCFG | OMAP_TIMER_CTRL_SCPWM |
	       OMAP_TIMER_CTRL_PT | (0x03 << 10) | OMAP_TIMER_CTRL_AR);
	अगर (def_on)
		l |= OMAP_TIMER_CTRL_SCPWM;
	अगर (toggle)
		l |= OMAP_TIMER_CTRL_PT;
	l |= trigger << 10;
	अगर (स्वतःreload)
		l |= OMAP_TIMER_CTRL_AR;
	omap_dm_समयr_ग_लिखो_reg(समयr, OMAP_TIMER_CTRL_REG, l);

	omap_dm_समयr_disable(समयr);
	वापस 0;
पूर्ण

अटल पूर्णांक omap_dm_समयr_get_pwm_status(काष्ठा omap_dm_समयr *समयr)
अणु
	u32 l;

	अगर (unlikely(!समयr))
		वापस -EINVAL;

	omap_dm_समयr_enable(समयr);
	l = omap_dm_समयr_पढ़ो_reg(समयr, OMAP_TIMER_CTRL_REG);
	omap_dm_समयr_disable(समयr);

	वापस l;
पूर्ण

अटल पूर्णांक omap_dm_समयr_set_prescaler(काष्ठा omap_dm_समयr *समयr,
					पूर्णांक prescaler)
अणु
	u32 l;

	अगर (unlikely(!समयr) || prescaler < -1 || prescaler > 7)
		वापस -EINVAL;

	omap_dm_समयr_enable(समयr);
	l = omap_dm_समयr_पढ़ो_reg(समयr, OMAP_TIMER_CTRL_REG);
	l &= ~(OMAP_TIMER_CTRL_PRE | (0x07 << 2));
	अगर (prescaler >= 0) अणु
		l |= OMAP_TIMER_CTRL_PRE;
		l |= prescaler << 2;
	पूर्ण
	omap_dm_समयr_ग_लिखो_reg(समयr, OMAP_TIMER_CTRL_REG, l);

	omap_dm_समयr_disable(समयr);
	वापस 0;
पूर्ण

अटल पूर्णांक omap_dm_समयr_set_पूर्णांक_enable(काष्ठा omap_dm_समयr *समयr,
					अचिन्हित पूर्णांक value)
अणु
	अगर (unlikely(!समयr))
		वापस -EINVAL;

	omap_dm_समयr_enable(समयr);
	__omap_dm_समयr_पूर्णांक_enable(समयr, value);

	omap_dm_समयr_disable(समयr);
	वापस 0;
पूर्ण

/**
 * omap_dm_समयr_set_पूर्णांक_disable - disable समयr पूर्णांकerrupts
 * @समयr:	poपूर्णांकer to समयr handle
 * @mask:	bit mask of पूर्णांकerrupts to be disabled
 *
 * Disables the specअगरied समयr पूर्णांकerrupts क्रम a समयr.
 */
अटल पूर्णांक omap_dm_समयr_set_पूर्णांक_disable(काष्ठा omap_dm_समयr *समयr, u32 mask)
अणु
	u32 l = mask;

	अगर (unlikely(!समयr))
		वापस -EINVAL;

	omap_dm_समयr_enable(समयr);

	अगर (समयr->revision == 1)
		l = पढ़ोl_relaxed(समयr->irq_ena) & ~mask;

	ग_लिखोl_relaxed(l, समयr->irq_dis);
	l = omap_dm_समयr_पढ़ो_reg(समयr, OMAP_TIMER_WAKEUP_EN_REG) & ~mask;
	omap_dm_समयr_ग_लिखो_reg(समयr, OMAP_TIMER_WAKEUP_EN_REG, l);

	omap_dm_समयr_disable(समयr);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक omap_dm_समयr_पढ़ो_status(काष्ठा omap_dm_समयr *समयr)
अणु
	अचिन्हित पूर्णांक l;

	अगर (unlikely(!समयr || !atomic_पढ़ो(&समयr->enabled))) अणु
		pr_err("%s: timer not available or enabled.\n", __func__);
		वापस 0;
	पूर्ण

	l = पढ़ोl_relaxed(समयr->irq_stat);

	वापस l;
पूर्ण

अटल पूर्णांक omap_dm_समयr_ग_लिखो_status(काष्ठा omap_dm_समयr *समयr, अचिन्हित पूर्णांक value)
अणु
	अगर (unlikely(!समयr || !atomic_पढ़ो(&समयr->enabled)))
		वापस -EINVAL;

	__omap_dm_समयr_ग_लिखो_status(समयr, value);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक omap_dm_समयr_पढ़ो_counter(काष्ठा omap_dm_समयr *समयr)
अणु
	अगर (unlikely(!समयr || !atomic_पढ़ो(&समयr->enabled))) अणु
		pr_err("%s: timer not iavailable or enabled.\n", __func__);
		वापस 0;
	पूर्ण

	वापस __omap_dm_समयr_पढ़ो_counter(समयr, समयr->posted);
पूर्ण

अटल पूर्णांक omap_dm_समयr_ग_लिखो_counter(काष्ठा omap_dm_समयr *समयr, अचिन्हित पूर्णांक value)
अणु
	अगर (unlikely(!समयr || !atomic_पढ़ो(&समयr->enabled))) अणु
		pr_err("%s: timer not available or enabled.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	omap_dm_समयr_ग_लिखो_reg(समयr, OMAP_TIMER_COUNTER_REG, value);

	/* Save the context */
	समयr->context.tcrr = value;
	वापस 0;
पूर्ण

पूर्णांक omap_dm_समयrs_active(व्योम)
अणु
	काष्ठा omap_dm_समयr *समयr;

	list_क्रम_each_entry(समयr, &omap_समयr_list, node) अणु
		अगर (!समयr->reserved)
			जारी;

		अगर (omap_dm_समयr_पढ़ो_reg(समयr, OMAP_TIMER_CTRL_REG) &
		    OMAP_TIMER_CTRL_ST) अणु
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused omap_dm_समयr_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा omap_dm_समयr *समयr = dev_get_drvdata(dev);

	atomic_set(&समयr->enabled, 0);

	अगर (समयr->capability & OMAP_TIMER_ALWON || !समयr->func_base)
		वापस 0;

	omap_समयr_save_context(समयr);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused omap_dm_समयr_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा omap_dm_समयr *समयr = dev_get_drvdata(dev);

	अगर (!(समयr->capability & OMAP_TIMER_ALWON) && समयr->func_base)
		omap_समयr_restore_context(समयr);

	atomic_set(&समयr->enabled, 1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops omap_dm_समयr_pm_ops = अणु
	SET_RUNTIME_PM_OPS(omap_dm_समयr_runसमय_suspend,
			   omap_dm_समयr_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id omap_समयr_match[];

/**
 * omap_dm_समयr_probe - probe function called क्रम every रेजिस्टरed device
 * @pdev:	poपूर्णांकer to current समयr platक्रमm device
 *
 * Called by driver framework at the end of device registration क्रम all
 * समयr devices.
 */
अटल पूर्णांक omap_dm_समयr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा omap_dm_समयr *समयr;
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा dmसमयr_platक्रमm_data *pdata;
	पूर्णांक ret;

	pdata = of_device_get_match_data(dev);
	अगर (!pdata)
		pdata = dev_get_platdata(dev);
	अन्यथा
		dev->platक्रमm_data = (व्योम *)pdata;

	अगर (!pdata) अणु
		dev_err(dev, "%s: no platform data.\n", __func__);
		वापस -ENODEV;
	पूर्ण

	समयr = devm_kzalloc(dev, माप(*समयr), GFP_KERNEL);
	अगर (!समयr)
		वापस  -ENOMEM;

	समयr->irq = platक्रमm_get_irq(pdev, 0);
	अगर (समयr->irq < 0)
		वापस समयr->irq;

	समयr->fclk = ERR_PTR(-ENODEV);
	समयr->io_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(समयr->io_base))
		वापस PTR_ERR(समयr->io_base);

	platक्रमm_set_drvdata(pdev, समयr);

	अगर (dev->of_node) अणु
		अगर (of_find_property(dev->of_node, "ti,timer-alwon", शून्य))
			समयr->capability |= OMAP_TIMER_ALWON;
		अगर (of_find_property(dev->of_node, "ti,timer-dsp", शून्य))
			समयr->capability |= OMAP_TIMER_HAS_DSP_IRQ;
		अगर (of_find_property(dev->of_node, "ti,timer-pwm", शून्य))
			समयr->capability |= OMAP_TIMER_HAS_PWM;
		अगर (of_find_property(dev->of_node, "ti,timer-secure", शून्य))
			समयr->capability |= OMAP_TIMER_SECURE;
	पूर्ण अन्यथा अणु
		समयr->id = pdev->id;
		समयr->capability = pdata->समयr_capability;
		समयr->reserved = omap_dm_समयr_reserved_sysसमयr(समयr->id);
	पूर्ण

	अगर (!(समयr->capability & OMAP_TIMER_ALWON)) अणु
		समयr->nb.notअगरier_call = omap_समयr_context_notअगरier;
		cpu_pm_रेजिस्टर_notअगरier(&समयr->nb);
	पूर्ण

	अगर (pdata)
		समयr->errata = pdata->समयr_errata;

	समयr->pdev = pdev;

	pm_runसमय_enable(dev);

	अगर (!समयr->reserved) अणु
		ret = pm_runसमय_get_sync(dev);
		अगर (ret < 0) अणु
			dev_err(dev, "%s: pm_runtime_get_sync failed!\n",
				__func__);
			जाओ err_get_sync;
		पूर्ण
		__omap_dm_समयr_init_regs(समयr);
		pm_runसमय_put(dev);
	पूर्ण

	/* add the समयr element to the list */
	spin_lock_irqsave(&dm_समयr_lock, flags);
	list_add_tail(&समयr->node, &omap_समयr_list);
	spin_unlock_irqrestore(&dm_समयr_lock, flags);

	dev_dbg(dev, "Device Probed.\n");

	वापस 0;

err_get_sync:
	pm_runसमय_put_noidle(dev);
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

/**
 * omap_dm_समयr_हटाओ - cleanup a रेजिस्टरed समयr device
 * @pdev:	poपूर्णांकer to current समयr platक्रमm device
 *
 * Called by driver framework whenever a समयr device is unरेजिस्टरed.
 * In addition to मुक्तing platक्रमm resources it also deletes the समयr
 * entry from the local list.
 */
अटल पूर्णांक omap_dm_समयr_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_dm_समयr *समयr;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EINVAL;

	spin_lock_irqsave(&dm_समयr_lock, flags);
	list_क्रम_each_entry(समयr, &omap_समयr_list, node)
		अगर (!म_भेद(dev_name(&समयr->pdev->dev),
			    dev_name(&pdev->dev))) अणु
			अगर (!(समयr->capability & OMAP_TIMER_ALWON))
				cpu_pm_unरेजिस्टर_notअगरier(&समयr->nb);
			list_del(&समयr->node);
			ret = 0;
			अवरोध;
		पूर्ण
	spin_unlock_irqrestore(&dm_समयr_lock, flags);

	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा omap_dm_समयr_ops dmसमयr_ops = अणु
	.request_by_node = omap_dm_समयr_request_by_node,
	.request_specअगरic = omap_dm_समयr_request_specअगरic,
	.request = omap_dm_समयr_request,
	.set_source = omap_dm_समयr_set_source,
	.get_irq = omap_dm_समयr_get_irq,
	.set_पूर्णांक_enable = omap_dm_समयr_set_पूर्णांक_enable,
	.set_पूर्णांक_disable = omap_dm_समयr_set_पूर्णांक_disable,
	.मुक्त = omap_dm_समयr_मुक्त,
	.enable = omap_dm_समयr_enable,
	.disable = omap_dm_समयr_disable,
	.get_fclk = omap_dm_समयr_get_fclk,
	.start = omap_dm_समयr_start,
	.stop = omap_dm_समयr_stop,
	.set_load = omap_dm_समयr_set_load,
	.set_match = omap_dm_समयr_set_match,
	.set_pwm = omap_dm_समयr_set_pwm,
	.get_pwm_status = omap_dm_समयr_get_pwm_status,
	.set_prescaler = omap_dm_समयr_set_prescaler,
	.पढ़ो_counter = omap_dm_समयr_पढ़ो_counter,
	.ग_लिखो_counter = omap_dm_समयr_ग_लिखो_counter,
	.पढ़ो_status = omap_dm_समयr_पढ़ो_status,
	.ग_लिखो_status = omap_dm_समयr_ग_लिखो_status,
पूर्ण;

अटल स्थिर काष्ठा dmसमयr_platक्रमm_data omap3plus_pdata = अणु
	.समयr_errata = OMAP_TIMER_ERRATA_I103_I767,
	.समयr_ops = &dmसमयr_ops,
पूर्ण;

अटल स्थिर काष्ठा of_device_id omap_समयr_match[] = अणु
	अणु
		.compatible = "ti,omap2420-timer",
	पूर्ण,
	अणु
		.compatible = "ti,omap3430-timer",
		.data = &omap3plus_pdata,
	पूर्ण,
	अणु
		.compatible = "ti,omap4430-timer",
		.data = &omap3plus_pdata,
	पूर्ण,
	अणु
		.compatible = "ti,omap5430-timer",
		.data = &omap3plus_pdata,
	पूर्ण,
	अणु
		.compatible = "ti,am335x-timer",
		.data = &omap3plus_pdata,
	पूर्ण,
	अणु
		.compatible = "ti,am335x-timer-1ms",
		.data = &omap3plus_pdata,
	पूर्ण,
	अणु
		.compatible = "ti,dm816-timer",
		.data = &omap3plus_pdata,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_समयr_match);

अटल काष्ठा platक्रमm_driver omap_dm_समयr_driver = अणु
	.probe  = omap_dm_समयr_probe,
	.हटाओ = omap_dm_समयr_हटाओ,
	.driver = अणु
		.name   = "omap_timer",
		.of_match_table = of_match_ptr(omap_समयr_match),
		.pm = &omap_dm_समयr_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(omap_dm_समयr_driver);

MODULE_DESCRIPTION("OMAP Dual-Mode Timer Driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Texas Instruments Inc");
