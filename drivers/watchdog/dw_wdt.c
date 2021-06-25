<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2010-2011 Picochip Ltd., Jamie Iles
 * https://www.picochip.com
 *
 * This file implements a driver क्रम the Synopsys DesignWare watchकरोg device
 * in the many subप्रणालीs. The watchकरोg has 16 dअगरferent समयout periods
 * and these are a function of the input घड़ी frequency.
 *
 * The DesignWare watchकरोg cannot be stopped once it has been started so we
 * करो not implement a stop function. The watchकरोg core will जारी to send
 * heartbeat requests after the watchकरोg device has been बंदd.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/pm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/debugfs.h>

#घोषणा WDOG_CONTROL_REG_OFFSET		    0x00
#घोषणा WDOG_CONTROL_REG_WDT_EN_MASK	    0x01
#घोषणा WDOG_CONTROL_REG_RESP_MODE_MASK	    0x02
#घोषणा WDOG_TIMEOUT_RANGE_REG_OFFSET	    0x04
#घोषणा WDOG_TIMEOUT_RANGE_TOPINIT_SHIFT    4
#घोषणा WDOG_CURRENT_COUNT_REG_OFFSET	    0x08
#घोषणा WDOG_COUNTER_RESTART_REG_OFFSET     0x0c
#घोषणा WDOG_COUNTER_RESTART_KICK_VALUE	    0x76
#घोषणा WDOG_INTERRUPT_STATUS_REG_OFFSET    0x10
#घोषणा WDOG_INTERRUPT_CLEAR_REG_OFFSET     0x14
#घोषणा WDOG_COMP_PARAMS_5_REG_OFFSET       0xe4
#घोषणा WDOG_COMP_PARAMS_4_REG_OFFSET       0xe8
#घोषणा WDOG_COMP_PARAMS_3_REG_OFFSET       0xec
#घोषणा WDOG_COMP_PARAMS_2_REG_OFFSET       0xf0
#घोषणा WDOG_COMP_PARAMS_1_REG_OFFSET       0xf4
#घोषणा WDOG_COMP_PARAMS_1_USE_FIX_TOP      BIT(6)
#घोषणा WDOG_COMP_VERSION_REG_OFFSET        0xf8
#घोषणा WDOG_COMP_TYPE_REG_OFFSET           0xfc

/* There are sixteen TOPs (समयout periods) that can be set in the watchकरोg. */
#घोषणा DW_WDT_NUM_TOPS		16
#घोषणा DW_WDT_FIX_TOP(_idx)	(1U << (16 + _idx))

#घोषणा DW_WDT_DEFAULT_SECONDS	30

अटल स्थिर u32 dw_wdt_fix_tops[DW_WDT_NUM_TOPS] = अणु
	DW_WDT_FIX_TOP(0), DW_WDT_FIX_TOP(1), DW_WDT_FIX_TOP(2),
	DW_WDT_FIX_TOP(3), DW_WDT_FIX_TOP(4), DW_WDT_FIX_TOP(5),
	DW_WDT_FIX_TOP(6), DW_WDT_FIX_TOP(7), DW_WDT_FIX_TOP(8),
	DW_WDT_FIX_TOP(9), DW_WDT_FIX_TOP(10), DW_WDT_FIX_TOP(11),
	DW_WDT_FIX_TOP(12), DW_WDT_FIX_TOP(13), DW_WDT_FIX_TOP(14),
	DW_WDT_FIX_TOP(15)
पूर्ण;

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started "
		 "(default=" __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

क्रमागत dw_wdt_rmod अणु
	DW_WDT_RMOD_RESET = 1,
	DW_WDT_RMOD_IRQ = 2
पूर्ण;

काष्ठा dw_wdt_समयout अणु
	u32 top_val;
	अचिन्हित पूर्णांक sec;
	अचिन्हित पूर्णांक msec;
पूर्ण;

काष्ठा dw_wdt अणु
	व्योम __iomem		*regs;
	काष्ठा clk		*clk;
	काष्ठा clk		*pclk;
	अचिन्हित दीर्घ		rate;
	क्रमागत dw_wdt_rmod	rmod;
	काष्ठा dw_wdt_समयout	समयouts[DW_WDT_NUM_TOPS];
	काष्ठा watchकरोg_device	wdd;
	काष्ठा reset_control	*rst;
	/* Save/restore */
	u32			control;
	u32			समयout;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry		*dbgfs_dir;
#पूर्ण_अगर
पूर्ण;

#घोषणा to_dw_wdt(wdd)	container_of(wdd, काष्ठा dw_wdt, wdd)

अटल अंतरभूत पूर्णांक dw_wdt_is_enabled(काष्ठा dw_wdt *dw_wdt)
अणु
	वापस पढ़ोl(dw_wdt->regs + WDOG_CONTROL_REG_OFFSET) &
		WDOG_CONTROL_REG_WDT_EN_MASK;
पूर्ण

अटल व्योम dw_wdt_update_mode(काष्ठा dw_wdt *dw_wdt, क्रमागत dw_wdt_rmod rmod)
अणु
	u32 val;

	val = पढ़ोl(dw_wdt->regs + WDOG_CONTROL_REG_OFFSET);
	अगर (rmod == DW_WDT_RMOD_IRQ)
		val |= WDOG_CONTROL_REG_RESP_MODE_MASK;
	अन्यथा
		val &= ~WDOG_CONTROL_REG_RESP_MODE_MASK;
	ग_लिखोl(val, dw_wdt->regs + WDOG_CONTROL_REG_OFFSET);

	dw_wdt->rmod = rmod;
पूर्ण

अटल अचिन्हित पूर्णांक dw_wdt_find_best_top(काष्ठा dw_wdt *dw_wdt,
					 अचिन्हित पूर्णांक समयout, u32 *top_val)
अणु
	पूर्णांक idx;

	/*
	 * Find a TOP with समयout greater or equal to the requested number.
	 * Note we'll select a TOP with maximum समयout अगर the requested
	 * समयout couldn't be reached.
	 */
	क्रम (idx = 0; idx < DW_WDT_NUM_TOPS; ++idx) अणु
		अगर (dw_wdt->समयouts[idx].sec >= समयout)
			अवरोध;
	पूर्ण

	अगर (idx == DW_WDT_NUM_TOPS)
		--idx;

	*top_val = dw_wdt->समयouts[idx].top_val;

	वापस dw_wdt->समयouts[idx].sec;
पूर्ण

अटल अचिन्हित पूर्णांक dw_wdt_get_min_समयout(काष्ठा dw_wdt *dw_wdt)
अणु
	पूर्णांक idx;

	/*
	 * We'll find a समयout greater or equal to one second anyway because
	 * the driver probe would have failed अगर there was none.
	 */
	क्रम (idx = 0; idx < DW_WDT_NUM_TOPS; ++idx) अणु
		अगर (dw_wdt->समयouts[idx].sec)
			अवरोध;
	पूर्ण

	वापस dw_wdt->समयouts[idx].sec;
पूर्ण

अटल अचिन्हित पूर्णांक dw_wdt_get_max_समयout_ms(काष्ठा dw_wdt *dw_wdt)
अणु
	काष्ठा dw_wdt_समयout *समयout = &dw_wdt->समयouts[DW_WDT_NUM_TOPS - 1];
	u64 msec;

	msec = (u64)समयout->sec * MSEC_PER_SEC + समयout->msec;

	वापस msec < अच_पूर्णांक_उच्च ? msec : अच_पूर्णांक_उच्च;
पूर्ण

अटल अचिन्हित पूर्णांक dw_wdt_get_समयout(काष्ठा dw_wdt *dw_wdt)
अणु
	पूर्णांक top_val = पढ़ोl(dw_wdt->regs + WDOG_TIMEOUT_RANGE_REG_OFFSET) & 0xF;
	पूर्णांक idx;

	क्रम (idx = 0; idx < DW_WDT_NUM_TOPS; ++idx) अणु
		अगर (dw_wdt->समयouts[idx].top_val == top_val)
			अवरोध;
	पूर्ण

	/*
	 * In IRQ mode due to the two stages counter, the actual समयout is
	 * twice greater than the TOP setting.
	 */
	वापस dw_wdt->समयouts[idx].sec * dw_wdt->rmod;
पूर्ण

अटल पूर्णांक dw_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा dw_wdt *dw_wdt = to_dw_wdt(wdd);

	ग_लिखोl(WDOG_COUNTER_RESTART_KICK_VALUE, dw_wdt->regs +
	       WDOG_COUNTER_RESTART_REG_OFFSET);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_wdt_set_समयout(काष्ठा watchकरोg_device *wdd, अचिन्हित पूर्णांक top_s)
अणु
	काष्ठा dw_wdt *dw_wdt = to_dw_wdt(wdd);
	अचिन्हित पूर्णांक समयout;
	u32 top_val;

	/*
	 * Note IRQ mode being enabled means having a non-zero pre-समयout
	 * setup. In this हाल we try to find a TOP as बंद to the half of the
	 * requested समयout as possible since DW Watchकरोg IRQ mode is deचिन्हित
	 * in two stages way - first समयout rises the pre-समयout पूर्णांकerrupt,
	 * second समयout perक्रमms the प्रणाली reset. So basically the effective
	 * watchकरोg-caused reset happens after two watchकरोg TOPs elapsed.
	 */
	समयout = dw_wdt_find_best_top(dw_wdt, DIV_ROUND_UP(top_s, dw_wdt->rmod),
				       &top_val);
	अगर (dw_wdt->rmod == DW_WDT_RMOD_IRQ)
		wdd->preसमयout = समयout;
	अन्यथा
		wdd->preसमयout = 0;

	/*
	 * Set the new value in the watchकरोg.  Some versions of dw_wdt
	 * have have TOPINIT in the TIMEOUT_RANGE रेजिस्टर (as per
	 * CP_WDT_DUAL_TOP in WDT_COMP_PARAMS_1).  On those we
	 * effectively get a pat of the watchकरोg right here.
	 */
	ग_लिखोl(top_val | top_val << WDOG_TIMEOUT_RANGE_TOPINIT_SHIFT,
	       dw_wdt->regs + WDOG_TIMEOUT_RANGE_REG_OFFSET);

	/* Kick new TOP value पूर्णांकo the watchकरोg counter अगर activated. */
	अगर (watchकरोg_active(wdd))
		dw_wdt_ping(wdd);

	/*
	 * In हाल users set bigger समयout value than HW can support,
	 * kernel(watchकरोg_dev.c) helps to feed watchकरोg beक्रमe
	 * wdd->max_hw_heartbeat_ms
	 */
	अगर (top_s * 1000 <= wdd->max_hw_heartbeat_ms)
		wdd->समयout = समयout * dw_wdt->rmod;
	अन्यथा
		wdd->समयout = top_s;

	वापस 0;
पूर्ण

अटल पूर्णांक dw_wdt_set_preसमयout(काष्ठा watchकरोg_device *wdd, अचिन्हित पूर्णांक req)
अणु
	काष्ठा dw_wdt *dw_wdt = to_dw_wdt(wdd);

	/*
	 * We ignore actual value of the समयout passed from user-space
	 * using it as a flag whether the preसमयout functionality is पूर्णांकended
	 * to be activated.
	 */
	dw_wdt_update_mode(dw_wdt, req ? DW_WDT_RMOD_IRQ : DW_WDT_RMOD_RESET);
	dw_wdt_set_समयout(wdd, wdd->समयout);

	वापस 0;
पूर्ण

अटल व्योम dw_wdt_arm_प्रणाली_reset(काष्ठा dw_wdt *dw_wdt)
अणु
	u32 val = पढ़ोl(dw_wdt->regs + WDOG_CONTROL_REG_OFFSET);

	/* Disable/enable पूर्णांकerrupt mode depending on the RMOD flag. */
	अगर (dw_wdt->rmod == DW_WDT_RMOD_IRQ)
		val |= WDOG_CONTROL_REG_RESP_MODE_MASK;
	अन्यथा
		val &= ~WDOG_CONTROL_REG_RESP_MODE_MASK;
	/* Enable watchकरोg. */
	val |= WDOG_CONTROL_REG_WDT_EN_MASK;
	ग_लिखोl(val, dw_wdt->regs + WDOG_CONTROL_REG_OFFSET);
पूर्ण

अटल पूर्णांक dw_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा dw_wdt *dw_wdt = to_dw_wdt(wdd);

	dw_wdt_set_समयout(wdd, wdd->समयout);
	dw_wdt_ping(&dw_wdt->wdd);
	dw_wdt_arm_प्रणाली_reset(dw_wdt);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा dw_wdt *dw_wdt = to_dw_wdt(wdd);

	अगर (!dw_wdt->rst) अणु
		set_bit(WDOG_HW_RUNNING, &wdd->status);
		वापस 0;
	पूर्ण

	reset_control_निश्चित(dw_wdt->rst);
	reset_control_deनिश्चित(dw_wdt->rst);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_wdt_restart(काष्ठा watchकरोg_device *wdd,
			  अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा dw_wdt *dw_wdt = to_dw_wdt(wdd);

	ग_लिखोl(0, dw_wdt->regs + WDOG_TIMEOUT_RANGE_REG_OFFSET);
	dw_wdt_update_mode(dw_wdt, DW_WDT_RMOD_RESET);
	अगर (dw_wdt_is_enabled(dw_wdt))
		ग_लिखोl(WDOG_COUNTER_RESTART_KICK_VALUE,
		       dw_wdt->regs + WDOG_COUNTER_RESTART_REG_OFFSET);
	अन्यथा
		dw_wdt_arm_प्रणाली_reset(dw_wdt);

	/* रुको क्रम reset to निश्चित... */
	mdelay(500);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक dw_wdt_get_समयleft(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा dw_wdt *dw_wdt = to_dw_wdt(wdd);
	अचिन्हित पूर्णांक sec;
	u32 val;

	val = पढ़ोl(dw_wdt->regs + WDOG_CURRENT_COUNT_REG_OFFSET);
	sec = val / dw_wdt->rate;

	अगर (dw_wdt->rmod == DW_WDT_RMOD_IRQ) अणु
		val = पढ़ोl(dw_wdt->regs + WDOG_INTERRUPT_STATUS_REG_OFFSET);
		अगर (!val)
			sec += wdd->preसमयout;
	पूर्ण

	वापस sec;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info dw_wdt_ident = अणु
	.options	= WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT |
			  WDIOF_MAGICCLOSE,
	.identity	= "Synopsys DesignWare Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info dw_wdt_pt_ident = अणु
	.options	= WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT |
			  WDIOF_PRETIMEOUT | WDIOF_MAGICCLOSE,
	.identity	= "Synopsys DesignWare Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops dw_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= dw_wdt_start,
	.stop		= dw_wdt_stop,
	.ping		= dw_wdt_ping,
	.set_समयout	= dw_wdt_set_समयout,
	.set_preसमयout	= dw_wdt_set_preसमयout,
	.get_समयleft	= dw_wdt_get_समयleft,
	.restart	= dw_wdt_restart,
पूर्ण;

अटल irqवापस_t dw_wdt_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा dw_wdt *dw_wdt = devid;
	u32 val;

	/*
	 * We करोn't clear the IRQ status. It's supposed to be करोne by the
	 * following ping operations.
	 */
	val = पढ़ोl(dw_wdt->regs + WDOG_INTERRUPT_STATUS_REG_OFFSET);
	अगर (!val)
		वापस IRQ_NONE;

	watchकरोg_notअगरy_preसमयout(&dw_wdt->wdd);

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक dw_wdt_suspend(काष्ठा device *dev)
अणु
	काष्ठा dw_wdt *dw_wdt = dev_get_drvdata(dev);

	dw_wdt->control = पढ़ोl(dw_wdt->regs + WDOG_CONTROL_REG_OFFSET);
	dw_wdt->समयout = पढ़ोl(dw_wdt->regs + WDOG_TIMEOUT_RANGE_REG_OFFSET);

	clk_disable_unprepare(dw_wdt->pclk);
	clk_disable_unprepare(dw_wdt->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_wdt_resume(काष्ठा device *dev)
अणु
	काष्ठा dw_wdt *dw_wdt = dev_get_drvdata(dev);
	पूर्णांक err = clk_prepare_enable(dw_wdt->clk);

	अगर (err)
		वापस err;

	err = clk_prepare_enable(dw_wdt->pclk);
	अगर (err) अणु
		clk_disable_unprepare(dw_wdt->clk);
		वापस err;
	पूर्ण

	ग_लिखोl(dw_wdt->समयout, dw_wdt->regs + WDOG_TIMEOUT_RANGE_REG_OFFSET);
	ग_लिखोl(dw_wdt->control, dw_wdt->regs + WDOG_CONTROL_REG_OFFSET);

	dw_wdt_ping(&dw_wdt->wdd);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(dw_wdt_pm_ops, dw_wdt_suspend, dw_wdt_resume);

/*
 * In हाल अगर DW WDT IP core is synthesized with fixed TOP feature disabled the
 * TOPs array can be arbitrary ordered with nearly any sixteen uपूर्णांक numbers
 * depending on the प्रणाली engineer imagination. The next method handles the
 * passed TOPs array to pre-calculate the effective समयouts and to sort the
 * TOP items out in the ascending order with respect to the समयouts.
 */

अटल व्योम dw_wdt_handle_tops(काष्ठा dw_wdt *dw_wdt, स्थिर u32 *tops)
अणु
	काष्ठा dw_wdt_समयout tout, *dst;
	पूर्णांक val, tidx;
	u64 msec;

	/*
	 * We walk over the passed TOPs array and calculate corresponding
	 * समयouts in seconds and milliseconds. The milliseconds granularity
	 * is needed to distinguish the TOPs with very बंद समयouts and to
	 * set the watchकरोg max heartbeat setting further.
	 */
	क्रम (val = 0; val < DW_WDT_NUM_TOPS; ++val) अणु
		tout.top_val = val;
		tout.sec = tops[val] / dw_wdt->rate;
		msec = (u64)tops[val] * MSEC_PER_SEC;
		करो_भाग(msec, dw_wdt->rate);
		tout.msec = msec - ((u64)tout.sec * MSEC_PER_SEC);

		/*
		 * Find a suitable place क्रम the current TOP in the समयouts
		 * array so that the list is reमुख्यed in the ascending order.
		 */
		क्रम (tidx = 0; tidx < val; ++tidx) अणु
			dst = &dw_wdt->समयouts[tidx];
			अगर (tout.sec > dst->sec || (tout.sec == dst->sec &&
			    tout.msec >= dst->msec))
				जारी;
			अन्यथा
				swap(*dst, tout);
		पूर्ण

		dw_wdt->समयouts[val] = tout;
	पूर्ण
पूर्ण

अटल पूर्णांक dw_wdt_init_समयouts(काष्ठा dw_wdt *dw_wdt, काष्ठा device *dev)
अणु
	u32 data, of_tops[DW_WDT_NUM_TOPS];
	स्थिर u32 *tops;
	पूर्णांक ret;

	/*
	 * Retrieve custom or fixed counter values depending on the
	 * WDT_USE_FIX_TOP flag found in the component specअगरic parameters
	 * #1 रेजिस्टर.
	 */
	data = पढ़ोl(dw_wdt->regs + WDOG_COMP_PARAMS_1_REG_OFFSET);
	अगर (data & WDOG_COMP_PARAMS_1_USE_FIX_TOP) अणु
		tops = dw_wdt_fix_tops;
	पूर्ण अन्यथा अणु
		ret = of_property_पढ़ो_variable_u32_array(dev_of_node(dev),
			"snps,watchdog-tops", of_tops, DW_WDT_NUM_TOPS,
			DW_WDT_NUM_TOPS);
		अगर (ret < 0) अणु
			dev_warn(dev, "No valid TOPs array specified\n");
			tops = dw_wdt_fix_tops;
		पूर्ण अन्यथा अणु
			tops = of_tops;
		पूर्ण
	पूर्ण

	/* Convert the specअगरied TOPs पूर्णांकo an array of watchकरोg समयouts. */
	dw_wdt_handle_tops(dw_wdt, tops);
	अगर (!dw_wdt->समयouts[DW_WDT_NUM_TOPS - 1].sec) अणु
		dev_err(dev, "No any valid TOP detected\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS

#घोषणा DW_WDT_DBGFS_REG(_name, _off) \
अणु				      \
	.name = _name,		      \
	.offset = _off		      \
पूर्ण

अटल स्थिर काष्ठा debugfs_reg32 dw_wdt_dbgfs_regs[] = अणु
	DW_WDT_DBGFS_REG("cr", WDOG_CONTROL_REG_OFFSET),
	DW_WDT_DBGFS_REG("torr", WDOG_TIMEOUT_RANGE_REG_OFFSET),
	DW_WDT_DBGFS_REG("ccvr", WDOG_CURRENT_COUNT_REG_OFFSET),
	DW_WDT_DBGFS_REG("crr", WDOG_COUNTER_RESTART_REG_OFFSET),
	DW_WDT_DBGFS_REG("stat", WDOG_INTERRUPT_STATUS_REG_OFFSET),
	DW_WDT_DBGFS_REG("param5", WDOG_COMP_PARAMS_5_REG_OFFSET),
	DW_WDT_DBGFS_REG("param4", WDOG_COMP_PARAMS_4_REG_OFFSET),
	DW_WDT_DBGFS_REG("param3", WDOG_COMP_PARAMS_3_REG_OFFSET),
	DW_WDT_DBGFS_REG("param2", WDOG_COMP_PARAMS_2_REG_OFFSET),
	DW_WDT_DBGFS_REG("param1", WDOG_COMP_PARAMS_1_REG_OFFSET),
	DW_WDT_DBGFS_REG("version", WDOG_COMP_VERSION_REG_OFFSET),
	DW_WDT_DBGFS_REG("type", WDOG_COMP_TYPE_REG_OFFSET)
पूर्ण;

अटल व्योम dw_wdt_dbgfs_init(काष्ठा dw_wdt *dw_wdt)
अणु
	काष्ठा device *dev = dw_wdt->wdd.parent;
	काष्ठा debugfs_regset32 *regset;

	regset = devm_kzalloc(dev, माप(*regset), GFP_KERNEL);
	अगर (!regset)
		वापस;

	regset->regs = dw_wdt_dbgfs_regs;
	regset->nregs = ARRAY_SIZE(dw_wdt_dbgfs_regs);
	regset->base = dw_wdt->regs;

	dw_wdt->dbgfs_dir = debugfs_create_dir(dev_name(dev), शून्य);

	debugfs_create_regset32("registers", 0444, dw_wdt->dbgfs_dir, regset);
पूर्ण

अटल व्योम dw_wdt_dbgfs_clear(काष्ठा dw_wdt *dw_wdt)
अणु
	debugfs_हटाओ_recursive(dw_wdt->dbgfs_dir);
पूर्ण

#अन्यथा /* !CONFIG_DEBUG_FS */

अटल व्योम dw_wdt_dbgfs_init(काष्ठा dw_wdt *dw_wdt) अणुपूर्ण
अटल व्योम dw_wdt_dbgfs_clear(काष्ठा dw_wdt *dw_wdt) अणुपूर्ण

#पूर्ण_अगर /* !CONFIG_DEBUG_FS */

अटल पूर्णांक dw_wdt_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा watchकरोg_device *wdd;
	काष्ठा dw_wdt *dw_wdt;
	पूर्णांक ret;

	dw_wdt = devm_kzalloc(dev, माप(*dw_wdt), GFP_KERNEL);
	अगर (!dw_wdt)
		वापस -ENOMEM;

	dw_wdt->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(dw_wdt->regs))
		वापस PTR_ERR(dw_wdt->regs);

	/*
	 * Try to request the watchकरोg dedicated समयr घड़ी source. It must
	 * be supplied अगर asynchronous mode is enabled. Otherwise fallback
	 * to the common समयr/bus घड़ीs configuration, in which the very
	 * first found घड़ी supply both समयr and APB संकेतs.
	 */
	dw_wdt->clk = devm_clk_get(dev, "tclk");
	अगर (IS_ERR(dw_wdt->clk)) अणु
		dw_wdt->clk = devm_clk_get(dev, शून्य);
		अगर (IS_ERR(dw_wdt->clk))
			वापस PTR_ERR(dw_wdt->clk);
	पूर्ण

	ret = clk_prepare_enable(dw_wdt->clk);
	अगर (ret)
		वापस ret;

	dw_wdt->rate = clk_get_rate(dw_wdt->clk);
	अगर (dw_wdt->rate == 0) अणु
		ret = -EINVAL;
		जाओ out_disable_clk;
	पूर्ण

	/*
	 * Request APB घड़ी अगर device is configured with async घड़ीs mode.
	 * In this हाल both tclk and pclk घड़ीs are supposed to be specअगरied.
	 * Alas we can't know क्रम sure whether async mode was really activated,
	 * so the pclk phandle reference is left optional. If it couldn't be
	 * found we consider the device configured in synchronous घड़ीs mode.
	 */
	dw_wdt->pclk = devm_clk_get_optional(dev, "pclk");
	अगर (IS_ERR(dw_wdt->pclk)) अणु
		ret = PTR_ERR(dw_wdt->pclk);
		जाओ out_disable_clk;
	पूर्ण

	ret = clk_prepare_enable(dw_wdt->pclk);
	अगर (ret)
		जाओ out_disable_clk;

	dw_wdt->rst = devm_reset_control_get_optional_shared(&pdev->dev, शून्य);
	अगर (IS_ERR(dw_wdt->rst)) अणु
		ret = PTR_ERR(dw_wdt->rst);
		जाओ out_disable_pclk;
	पूर्ण

	/* Enable normal reset without pre-समयout by शेष. */
	dw_wdt_update_mode(dw_wdt, DW_WDT_RMOD_RESET);

	/*
	 * Pre-समयout IRQ is optional, since some hardware may lack support
	 * of it. Note we must request rising-edge IRQ, since the lane is left
	 * pending either until the next watchकरोg kick event or up to the
	 * प्रणाली reset.
	 */
	ret = platक्रमm_get_irq_optional(pdev, 0);
	अगर (ret > 0) अणु
		ret = devm_request_irq(dev, ret, dw_wdt_irq,
				       IRQF_SHARED | IRQF_TRIGGER_RISING,
				       pdev->name, dw_wdt);
		अगर (ret)
			जाओ out_disable_pclk;

		dw_wdt->wdd.info = &dw_wdt_pt_ident;
	पूर्ण अन्यथा अणु
		अगर (ret == -EPROBE_DEFER)
			जाओ out_disable_pclk;

		dw_wdt->wdd.info = &dw_wdt_ident;
	पूर्ण

	reset_control_deनिश्चित(dw_wdt->rst);

	ret = dw_wdt_init_समयouts(dw_wdt, dev);
	अगर (ret)
		जाओ out_disable_clk;

	wdd = &dw_wdt->wdd;
	wdd->ops = &dw_wdt_ops;
	wdd->min_समयout = dw_wdt_get_min_समयout(dw_wdt);
	wdd->max_hw_heartbeat_ms = dw_wdt_get_max_समयout_ms(dw_wdt);
	wdd->parent = dev;

	watchकरोg_set_drvdata(wdd, dw_wdt);
	watchकरोg_set_nowayout(wdd, nowayout);
	watchकरोg_init_समयout(wdd, 0, dev);

	/*
	 * If the watchकरोg is alपढ़ोy running, use its alपढ़ोy configured
	 * समयout. Otherwise use the शेष or the value provided through
	 * devicetree.
	 */
	अगर (dw_wdt_is_enabled(dw_wdt)) अणु
		wdd->समयout = dw_wdt_get_समयout(dw_wdt);
		set_bit(WDOG_HW_RUNNING, &wdd->status);
	पूर्ण अन्यथा अणु
		wdd->समयout = DW_WDT_DEFAULT_SECONDS;
		watchकरोg_init_समयout(wdd, 0, dev);
	पूर्ण

	platक्रमm_set_drvdata(pdev, dw_wdt);

	watchकरोg_set_restart_priority(wdd, 128);

	ret = watchकरोg_रेजिस्टर_device(wdd);
	अगर (ret)
		जाओ out_disable_pclk;

	dw_wdt_dbgfs_init(dw_wdt);

	वापस 0;

out_disable_pclk:
	clk_disable_unprepare(dw_wdt->pclk);

out_disable_clk:
	clk_disable_unprepare(dw_wdt->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक dw_wdt_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_wdt *dw_wdt = platक्रमm_get_drvdata(pdev);

	dw_wdt_dbgfs_clear(dw_wdt);

	watchकरोg_unरेजिस्टर_device(&dw_wdt->wdd);
	reset_control_निश्चित(dw_wdt->rst);
	clk_disable_unprepare(dw_wdt->pclk);
	clk_disable_unprepare(dw_wdt->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id dw_wdt_of_match[] = अणु
	अणु .compatible = "snps,dw-wdt", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dw_wdt_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver dw_wdt_driver = अणु
	.probe		= dw_wdt_drv_probe,
	.हटाओ		= dw_wdt_drv_हटाओ,
	.driver		= अणु
		.name	= "dw_wdt",
		.of_match_table = of_match_ptr(dw_wdt_of_match),
		.pm	= &dw_wdt_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dw_wdt_driver);

MODULE_AUTHOR("Jamie Iles");
MODULE_DESCRIPTION("Synopsys DesignWare Watchdog Driver");
MODULE_LICENSE("GPL");
