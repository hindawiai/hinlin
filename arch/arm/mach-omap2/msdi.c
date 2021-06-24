<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MSDI IP block reset
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 * Paul Walmsley
 *
 * XXX What about pad muxing?
 */

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>

#समावेश "prm.h"
#समावेश "common.h"
#समावेश "control.h"
#समावेश "omap_hwmod.h"
#समावेश "omap_device.h"
#समावेश "mmc.h"

/*
 * MSDI_CON_OFFSET: offset in bytes of the MSDI IP block's CON रेजिस्टर
 *     from the IP block's base address
 */
#घोषणा MSDI_CON_OFFSET				0x0c

/* Register bitfields in the CON रेजिस्टर */
#घोषणा MSDI_CON_POW_MASK			BIT(11)
#घोषणा MSDI_CON_CLKD_MASK			(0x3f << 0)
#घोषणा MSDI_CON_CLKD_SHIFT			0

/* MSDI_TARGET_RESET_CLKD: घड़ी भागisor to use throughout the reset */
#घोषणा MSDI_TARGET_RESET_CLKD		0x3ff

/**
 * omap_msdi_reset - reset the MSDI IP block
 * @oh: काष्ठा omap_hwmod *
 *
 * The MSDI IP block on OMAP2420 has to have both the POW and CLKD
 * fields set inside its CON रेजिस्टर क्रम a reset to complete
 * successfully.  This is not करोcumented in the TRM.  For CLKD, we use
 * the value that results in the lowest possible घड़ी rate, to attempt
 * to aव्योम disturbing any cards.
 */
पूर्णांक omap_msdi_reset(काष्ठा omap_hwmod *oh)
अणु
	u16 v = 0;
	पूर्णांक c = 0;

	/* Write to the SOFTRESET bit */
	omap_hwmod_softreset(oh);

	/* Enable the MSDI core and पूर्णांकernal घड़ी */
	v |= MSDI_CON_POW_MASK;
	v |= MSDI_TARGET_RESET_CLKD << MSDI_CON_CLKD_SHIFT;
	omap_hwmod_ग_लिखो(v, oh, MSDI_CON_OFFSET);

	/* Poll on RESETDONE bit */
	omap_test_समयout((omap_hwmod_पढ़ो(oh, oh->class->sysc->syss_offs)
			   & SYSS_RESETDONE_MASK),
			  MAX_MODULE_SOFTRESET_WAIT, c);

	अगर (c == MAX_MODULE_SOFTRESET_WAIT)
		pr_warn("%s: %s: softreset failed (waited %d usec)\n",
			__func__, oh->name, MAX_MODULE_SOFTRESET_WAIT);
	अन्यथा
		pr_debug("%s: %s: softreset in %d usec\n", __func__,
			 oh->name, c);

	/* Disable the MSDI पूर्णांकernal घड़ी */
	v &= ~MSDI_CON_CLKD_MASK;
	omap_hwmod_ग_लिखो(v, oh, MSDI_CON_OFFSET);

	वापस 0;
पूर्ण
