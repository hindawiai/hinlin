<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-pxa/mfp.c
 *
 * PXA3xx Multi-Function Pin Support
 *
 * Copyright (C) 2007 Marvell Internation Ltd.
 *
 * 2007-08-21: eric miao <eric.miao@marvell.com>
 *             initial version
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/syscore_ops.h>

#समावेश <mach/hardware.h>
#समावेश "mfp-pxa3xx.h"
#समावेश <mach/pxa3xx-regs.h>

#अगर_घोषित CONFIG_PM
/*
 * Configure the MFPs appropriately क्रम suspend/resume.
 * FIXME: this should probably depend on which प्रणाली state we're
 * entering - क्रम instance, we might not want to place MFP pins in
 * a pull-करोwn mode अगर they're an active low chip select, and we're
 * just entering standby.
 */
अटल पूर्णांक pxa3xx_mfp_suspend(व्योम)
अणु
	mfp_config_lpm();
	वापस 0;
पूर्ण

अटल व्योम pxa3xx_mfp_resume(व्योम)
अणु
	mfp_config_run();

	/* clear RDH bit when MFP settings are restored
	 *
	 * NOTE: the last 3 bits DxS are ग_लिखो-1-to-clear so carefully
	 * preserve them here in हाल they will be referenced later
	 */
	ASCR &= ~(ASCR_RDH | ASCR_D1S | ASCR_D2S | ASCR_D3S);
पूर्ण
#अन्यथा
#घोषणा pxa3xx_mfp_suspend	शून्य
#घोषणा pxa3xx_mfp_resume	शून्य
#पूर्ण_अगर

काष्ठा syscore_ops pxa3xx_mfp_syscore_ops = अणु
	.suspend	= pxa3xx_mfp_suspend,
	.resume		= pxa3xx_mfp_resume,
पूर्ण;
