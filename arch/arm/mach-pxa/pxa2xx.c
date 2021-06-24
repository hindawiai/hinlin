<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-pxa/pxa2xx.c
 *
 * code specअगरic to pxa2xx
 *
 * Copyright (C) 2008 Dmitry Baryshkov
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>

#समावेश <mach/hardware.h>
#समावेश <mach/pxa2xx-regs.h>
#समावेश "mfp-pxa25x.h"
#समावेश <mach/reset.h>
#समावेश <linux/platक्रमm_data/irda-pxaficp.h>

व्योम pxa2xx_clear_reset_status(अचिन्हित पूर्णांक mask)
अणु
	/* RESET_STATUS_* has a 1:1 mapping with RCSR */
	RCSR = mask;
पूर्ण

अटल अचिन्हित दीर्घ pxa2xx_mfp_fir[] = अणु
	GPIO46_FICP_RXD,
	GPIO47_FICP_TXD,
पूर्ण;

अटल अचिन्हित दीर्घ pxa2xx_mfp_sir[] = अणु
	GPIO46_STUART_RXD,
	GPIO47_STUART_TXD,
पूर्ण;

अटल अचिन्हित दीर्घ pxa2xx_mfp_off[] = अणु
	GPIO46_GPIO | MFP_LPM_DRIVE_LOW,
	GPIO47_GPIO | MFP_LPM_DRIVE_LOW,
पूर्ण;

व्योम pxa2xx_transceiver_mode(काष्ठा device *dev, पूर्णांक mode)
अणु
	अगर (mode & IR_OFF) अणु
		pxa2xx_mfp_config(pxa2xx_mfp_off, ARRAY_SIZE(pxa2xx_mfp_off));
	पूर्ण अन्यथा अगर (mode & IR_SIRMODE) अणु
		pxa2xx_mfp_config(pxa2xx_mfp_sir, ARRAY_SIZE(pxa2xx_mfp_sir));
	पूर्ण अन्यथा अगर (mode & IR_FIRMODE) अणु
		pxa2xx_mfp_config(pxa2xx_mfp_fir, ARRAY_SIZE(pxa2xx_mfp_fir));
	पूर्ण अन्यथा
		BUG();
पूर्ण
EXPORT_SYMBOL_GPL(pxa2xx_transceiver_mode);
