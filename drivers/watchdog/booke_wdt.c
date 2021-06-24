<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Watchकरोg समयr क्रम PowerPC Book-E प्रणालीs
 *
 * Author: Matthew McClपूर्णांकock
 * Maपूर्णांकainer: Kumar Gala <galak@kernel.crashing.org>
 *
 * Copyright 2005, 2008, 2010-2011 Freescale Semiconductor Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/smp.h>
#समावेश <linux/watchकरोg.h>

#समावेश <यंत्र/reg_booke.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/भाग64.h>

/* If the kernel parameter wdt=1, the watchकरोg will be enabled at boot.
 * Also, the wdt_period sets the watchकरोg समयr period समयout.
 * For E500 cpus the wdt_period sets which bit changing from 0->1 will
 * trigger a watchकरोg समयout. This watchकरोg समयout will occur 3 बार, the
 * first समय nothing will happen, the second समय a watchकरोg exception will
 * occur, and the final समय the board will reset.
 */


#अगर_घोषित	CONFIG_PPC_FSL_BOOK3E
#घोषणा WDTP(x)		((((x)&0x3)<<30)|(((x)&0x3c)<<15))
#घोषणा WDTP_MASK	(WDTP(0x3f))
#अन्यथा
#घोषणा WDTP(x)		(TCR_WP(x))
#घोषणा WDTP_MASK	(TCR_WP_MASK)
#पूर्ण_अगर

अटल bool booke_wdt_enabled;
module_param(booke_wdt_enabled, bool, 0);
अटल पूर्णांक  booke_wdt_period = CONFIG_BOOKE_WDT_DEFAULT_TIMEOUT;
module_param(booke_wdt_period, पूर्णांक, 0);
अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

#अगर_घोषित CONFIG_PPC_FSL_BOOK3E

/* For the specअगरied period, determine the number of seconds
 * corresponding to the reset समय.  There will be a watchकरोg
 * exception at approximately 3/5 of this समय.
 *
 * The क्रमmula to calculate this is given by:
 * 2.5 * (2^(63-period+1)) / समयbase_freq
 *
 * In order to simplअगरy things, we assume that period is
 * at least 1.  This will still result in a very दीर्घ समयout.
 */
अटल अचिन्हित दीर्घ दीर्घ period_to_sec(अचिन्हित पूर्णांक period)
अणु
	अचिन्हित दीर्घ दीर्घ पंचांगp = 1ULL << (64 - period);
	अचिन्हित दीर्घ पंचांगp2 = ppc_tb_freq;

	/* पंचांगp may be a very large number and we करोn't want to overflow,
	 * so भागide the समयbase freq instead of multiplying पंचांगp
	 */
	पंचांगp2 = पंचांगp2 / 5 * 2;

	करो_भाग(पंचांगp, पंचांगp2);
	वापस पंचांगp;
पूर्ण

/*
 * This procedure will find the highest period which will give a समयout
 * greater than the one required. e.g. क्रम a bus speed of 66666666 and
 * and a parameter of 2 secs, then this procedure will वापस a value of 38.
 */
अटल अचिन्हित पूर्णांक sec_to_period(अचिन्हित पूर्णांक secs)
अणु
	अचिन्हित पूर्णांक period;
	क्रम (period = 63; period > 0; period--) अणु
		अगर (period_to_sec(period) >= secs)
			वापस period;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा MAX_WDT_TIMEOUT		period_to_sec(1)

#अन्यथा /* CONFIG_PPC_FSL_BOOK3E */

अटल अचिन्हित दीर्घ दीर्घ period_to_sec(अचिन्हित पूर्णांक period)
अणु
	वापस period;
पूर्ण

अटल अचिन्हित पूर्णांक sec_to_period(अचिन्हित पूर्णांक secs)
अणु
	वापस secs;
पूर्ण

#घोषणा MAX_WDT_TIMEOUT		3	/* from Kconfig */

#पूर्ण_अगर /* !CONFIG_PPC_FSL_BOOK3E */

अटल व्योम __booke_wdt_set(व्योम *data)
अणु
	u32 val;
	काष्ठा watchकरोg_device *wकरोg = data;

	val = mfspr(SPRN_TCR);
	val &= ~WDTP_MASK;
	val |= WDTP(sec_to_period(wकरोg->समयout));

	mtspr(SPRN_TCR, val);
पूर्ण

अटल व्योम booke_wdt_set(व्योम *data)
अणु
	on_each_cpu(__booke_wdt_set, data, 0);
पूर्ण

अटल व्योम __booke_wdt_ping(व्योम *data)
अणु
	mtspr(SPRN_TSR, TSR_ENW|TSR_WIS);
पूर्ण

अटल पूर्णांक booke_wdt_ping(काष्ठा watchकरोg_device *wकरोg)
अणु
	on_each_cpu(__booke_wdt_ping, शून्य, 0);

	वापस 0;
पूर्ण

अटल व्योम __booke_wdt_enable(व्योम *data)
अणु
	u32 val;
	काष्ठा watchकरोg_device *wकरोg = data;

	/* clear status beक्रमe enabling watchकरोg */
	__booke_wdt_ping(शून्य);
	val = mfspr(SPRN_TCR);
	val &= ~WDTP_MASK;
	val |= (TCR_WIE|TCR_WRC(WRC_CHIP)|WDTP(sec_to_period(wकरोg->समयout)));

	mtspr(SPRN_TCR, val);
पूर्ण

/**
 * booke_wdt_disable - disable the watchकरोg on the given CPU
 *
 * This function is called on each CPU.  It disables the watchकरोg on that CPU.
 *
 * TCR[WRC] cannot be changed once it has been set to non-zero, but we can
 * effectively disable the watchकरोg by setting its period to the maximum value.
 */
अटल व्योम __booke_wdt_disable(व्योम *data)
अणु
	u32 val;

	val = mfspr(SPRN_TCR);
	val &= ~(TCR_WIE | WDTP_MASK);
	mtspr(SPRN_TCR, val);

	/* clear status to make sure nothing is pending */
	__booke_wdt_ping(शून्य);

पूर्ण

अटल पूर्णांक booke_wdt_start(काष्ठा watchकरोg_device *wकरोg)
अणु
	on_each_cpu(__booke_wdt_enable, wकरोg, 0);
	pr_debug("watchdog enabled (timeout = %u sec)\n", wकरोg->समयout);

	वापस 0;
पूर्ण

अटल पूर्णांक booke_wdt_stop(काष्ठा watchकरोg_device *wकरोg)
अणु
	on_each_cpu(__booke_wdt_disable, शून्य, 0);
	pr_debug("watchdog disabled\n");

	वापस 0;
पूर्ण

अटल पूर्णांक booke_wdt_set_समयout(काष्ठा watchकरोg_device *wdt_dev,
				 अचिन्हित पूर्णांक समयout)
अणु
	wdt_dev->समयout = समयout;
	booke_wdt_set(wdt_dev);

	वापस 0;
पूर्ण

अटल काष्ठा watchकरोg_info booke_wdt_info __ro_after_init = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING,
	.identity = "PowerPC Book-E Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops booke_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = booke_wdt_start,
	.stop = booke_wdt_stop,
	.ping = booke_wdt_ping,
	.set_समयout = booke_wdt_set_समयout,
पूर्ण;

अटल काष्ठा watchकरोg_device booke_wdt_dev = अणु
	.info = &booke_wdt_info,
	.ops = &booke_wdt_ops,
	.min_समयout = 1,
पूर्ण;

अटल व्योम __निकास booke_wdt_निकास(व्योम)
अणु
	watchकरोg_unरेजिस्टर_device(&booke_wdt_dev);
पूर्ण

अटल पूर्णांक __init booke_wdt_init(व्योम)
अणु
	पूर्णांक ret = 0;

	pr_info("powerpc book-e watchdog driver loaded\n");
	booke_wdt_info.firmware_version = cur_cpu_spec->pvr_value;
	booke_wdt_set_समयout(&booke_wdt_dev,
			      period_to_sec(booke_wdt_period));
	watchकरोg_set_nowayout(&booke_wdt_dev, nowayout);
	booke_wdt_dev.max_समयout = MAX_WDT_TIMEOUT;
	अगर (booke_wdt_enabled)
		booke_wdt_start(&booke_wdt_dev);

	ret = watchकरोg_रेजिस्टर_device(&booke_wdt_dev);

	वापस ret;
पूर्ण

module_init(booke_wdt_init);
module_निकास(booke_wdt_निकास);

MODULE_ALIAS("booke_wdt");
MODULE_DESCRIPTION("PowerPC Book-E watchdog driver");
MODULE_LICENSE("GPL");
