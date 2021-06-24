<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OMAP2+ MPU WD_TIMER-specअगरic code
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>

#समावेश <linux/platक्रमm_data/omap-wd-समयr.h>

#समावेश "omap_hwmod.h"
#समावेश "omap_device.h"
#समावेश "wd_timer.h"
#समावेश "common.h"
#समावेश "prm.h"
#समावेश "soc.h"

/*
 * In order to aव्योम any assumptions from bootloader regarding WDT
 * settings, WDT module is reset during init. This enables the watchकरोg
 * समयr. Hence it is required to disable the watchकरोg after the WDT reset
 * during init. Otherwise the प्रणाली would reboot as per the शेष
 * watchकरोg समयr रेजिस्टरs settings.
 */
#घोषणा OMAP_WDT_WPS		0x34
#घोषणा OMAP_WDT_SPR		0x48

पूर्णांक omap2_wd_समयr_disable(काष्ठा omap_hwmod *oh)
अणु
	व्योम __iomem *base;

	अगर (!oh) अणु
		pr_err("%s: Could not look up wdtimer_hwmod\n", __func__);
		वापस -EINVAL;
	पूर्ण

	base = omap_hwmod_get_mpu_rt_va(oh);
	अगर (!base) अणु
		pr_err("%s: Could not get the base address for %s\n",
				oh->name, __func__);
		वापस -EINVAL;
	पूर्ण

	/* sequence required to disable watchकरोg */
	ग_लिखोl_relaxed(0xAAAA, base + OMAP_WDT_SPR);
	जबतक (पढ़ोl_relaxed(base + OMAP_WDT_WPS) & 0x10)
		cpu_relax();

	ग_लिखोl_relaxed(0x5555, base + OMAP_WDT_SPR);
	जबतक (पढ़ोl_relaxed(base + OMAP_WDT_WPS) & 0x10)
		cpu_relax();

	वापस 0;
पूर्ण

/**
 * omap2_wdसमयr_reset - reset and disable the WDTIMER IP block
 * @oh: काष्ठा omap_hwmod *
 *
 * After the WDTIMER IP blocks are reset on OMAP2/3, we must also take
 * care to execute the special watchकरोg disable sequence.  This is
 * because the watchकरोg is re-armed upon OCP softreset.  (On OMAP4,
 * this behavior was apparently changed and the watchकरोg is no दीर्घer
 * re-armed after an OCP soft-reset.)  Returns -ETIMEDOUT अगर the reset
 * did not complete, or 0 upon success.
 *
 * XXX Most of this code should be moved to the omap_hwmod.c layer
 * during a normal merge winकरोw.  omap_hwmod_softreset() should be
 * नामd to omap_hwmod_set_ocp_softreset(), and omap_hwmod_softreset()
 * should call the hwmod _ocp_softreset() code.
 */
पूर्णांक omap2_wd_समयr_reset(काष्ठा omap_hwmod *oh)
अणु
	पूर्णांक c = 0;

	/* Write to the SOFTRESET bit */
	omap_hwmod_softreset(oh);

	/* Poll on RESETDONE bit */
	omap_test_समयout((omap_hwmod_पढ़ो(oh,
					   oh->class->sysc->syss_offs)
			   & SYSS_RESETDONE_MASK),
			  MAX_MODULE_SOFTRESET_WAIT, c);

	अगर (oh->class->sysc->srst_udelay)
		udelay(oh->class->sysc->srst_udelay);

	अगर (c == MAX_MODULE_SOFTRESET_WAIT)
		pr_warn("%s: %s: softreset failed (waited %d usec)\n",
			__func__, oh->name, MAX_MODULE_SOFTRESET_WAIT);
	अन्यथा
		pr_debug("%s: %s: softreset in %d usec\n", __func__,
			 oh->name, c);

	वापस (c == MAX_MODULE_SOFTRESET_WAIT) ? -ETIMEDOUT :
		omap2_wd_समयr_disable(oh);
पूर्ण
