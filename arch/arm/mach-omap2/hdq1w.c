<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IP block पूर्णांकegration code क्रम the HDQ1W/1-wire IP block
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 * Paul Walmsley
 *
 * Based on the I2C reset code in arch/arm/mach-omap2/i2c.c by
 *     Avinash.H.M <avinashhm@ti.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "soc.h"
#समावेश "omap_hwmod.h"
#समावेश "omap_device.h"
#समावेश "hdq1w.h"

#समावेश "prm.h"
#समावेश "common.h"

/**
 * omap_hdq1w_reset - reset the OMAP HDQ1W module
 * @oh: काष्ठा omap_hwmod *
 *
 * OCP soft reset the HDQ1W IP block.  Section 20.6.1.4 "HDQ1W/1-Wire
 * Software Reset" of the OMAP34xx Technical Reference Manual Revision
 * ZR (SWPU223R) करोes not include the rather important fact that, क्रम
 * the reset to succeed, the HDQ1W module's पूर्णांकernal घड़ी gate must be
 * programmed to allow the घड़ी to propagate to the rest of the
 * module.  In this sense, it's rather similar to the I2C custom reset
 * function.  Returns 0.
 */
पूर्णांक omap_hdq1w_reset(काष्ठा omap_hwmod *oh)
अणु
	u32 v;
	पूर्णांक c = 0;

	/* Write to the SOFTRESET bit */
	omap_hwmod_softreset(oh);

	/* Enable the module's पूर्णांकernal घड़ीs */
	v = omap_hwmod_पढ़ो(oh, HDQ_CTRL_STATUS_OFFSET);
	v |= 1 << HDQ_CTRL_STATUS_CLOCKENABLE_SHIFT;
	omap_hwmod_ग_लिखो(v, oh, HDQ_CTRL_STATUS_OFFSET);

	/* Poll on RESETDONE bit */
	omap_test_समयout((omap_hwmod_पढ़ो(oh,
					   oh->class->sysc->syss_offs)
			   & SYSS_RESETDONE_MASK),
			  MAX_MODULE_SOFTRESET_WAIT, c);

	अगर (c == MAX_MODULE_SOFTRESET_WAIT)
		pr_warn("%s: %s: softreset failed (waited %d usec)\n",
			__func__, oh->name, MAX_MODULE_SOFTRESET_WAIT);
	अन्यथा
		pr_debug("%s: %s: softreset in %d usec\n", __func__,
			 oh->name, c);

	वापस 0;
पूर्ण
