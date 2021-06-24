<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SMS/SDRC (SDRAM controller) common code क्रम OMAP2/3
 *
 * Copyright (C) 2005, 2008 Texas Instruments Inc.
 * Copyright (C) 2005, 2008 Nokia Corporation
 *
 * Tony Lindgren <tony@atomide.com>
 * Paul Walmsley
 * Riअक्षरd Woodruff <r-woodruff2@ti.com>
 */
#अघोषित DEBUG

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>

#समावेश "common.h"
#समावेश "clock.h"
#समावेश "sdrc.h"

अटल काष्ठा omap_sdrc_params *sdrc_init_params_cs0, *sdrc_init_params_cs1;

व्योम __iomem *omap2_sdrc_base;
व्योम __iomem *omap2_sms_base;

काष्ठा omap2_sms_regs अणु
	u32	sms_sysconfig;
पूर्ण;

अटल काष्ठा omap2_sms_regs sms_context;

/* SDRC_POWER रेजिस्टर bits */
#घोषणा SDRC_POWER_EXTCLKDIS_SHIFT		3
#घोषणा SDRC_POWER_PWDENA_SHIFT			2
#घोषणा SDRC_POWER_PAGEPOLICY_SHIFT		0

/**
 * omap2_sms_save_context - Save SMS रेजिस्टरs
 *
 * Save SMS रेजिस्टरs that need to be restored after off mode.
 */
व्योम omap2_sms_save_context(व्योम)
अणु
	sms_context.sms_sysconfig = sms_पढ़ो_reg(SMS_SYSCONFIG);
पूर्ण

/**
 * omap2_sms_restore_context - Restore SMS रेजिस्टरs
 *
 * Restore SMS रेजिस्टरs that need to be Restored after off mode.
 */
व्योम omap2_sms_restore_context(व्योम)
अणु
	sms_ग_लिखो_reg(sms_context.sms_sysconfig, SMS_SYSCONFIG);
पूर्ण

/**
 * omap2_sdrc_get_params - वापस SDRC रेजिस्टर values क्रम a given घड़ी rate
 * @r: SDRC घड़ी rate (in Hz)
 * @sdrc_cs0: chip select 0 ram timings **
 * @sdrc_cs1: chip select 1 ram timings **
 *
 * Return pre-calculated values क्रम the SDRC_ACTIM_CTRLA,
 *  SDRC_ACTIM_CTRLB, SDRC_RFR_CTRL and SDRC_MR रेजिस्टरs in sdrc_cs[01]
 *  काष्ठाs,क्रम a given SDRC घड़ी rate 'r'.
 * These parameters control various timing delays in the SDRAM controller
 *  that are expressed in terms of the number of SDRC घड़ी cycles to
 *  रुको; hence the घड़ी rate dependency.
 *
 * Supports 2 dअगरferent timing parameters क्रम both chip selects.
 *
 * Note 1: the sdrc_init_params_cs[01] must be sorted rate descending.
 * Note 2: If sdrc_init_params_cs_1 is not शून्य it must be of same size
 *  as sdrc_init_params_cs_0.
 *
 * Fills in the काष्ठा omap_sdrc_params * क्रम each chip select.
 * Returns 0 upon success or -1 upon failure.
 */
पूर्णांक omap2_sdrc_get_params(अचिन्हित दीर्घ r,
			  काष्ठा omap_sdrc_params **sdrc_cs0,
			  काष्ठा omap_sdrc_params **sdrc_cs1)
अणु
	काष्ठा omap_sdrc_params *sp0, *sp1;

	अगर (!sdrc_init_params_cs0)
		वापस -1;

	sp0 = sdrc_init_params_cs0;
	sp1 = sdrc_init_params_cs1;

	जबतक (sp0->rate && sp0->rate != r) अणु
		sp0++;
		अगर (sdrc_init_params_cs1)
			sp1++;
	पूर्ण

	अगर (!sp0->rate)
		वापस -1;

	*sdrc_cs0 = sp0;
	*sdrc_cs1 = sp1;
	वापस 0;
पूर्ण


व्योम __init omap2_set_globals_sdrc(व्योम __iomem *sdrc, व्योम __iomem *sms)
अणु
	omap2_sdrc_base = sdrc;
	omap2_sms_base = sms;
पूर्ण

/**
 * omap2_sdrc_init - initialize SMS, SDRC devices on boot
 * @sdrc_cs[01]: poपूर्णांकers to a null-terminated list of काष्ठा omap_sdrc_params
 *  Support क्रम 2 chip selects timings
 *
 * Turn on smart idle modes क्रम SDRAM scheduler and controller.
 * Program a known-good configuration क्रम the SDRC to deal with buggy
 * bootloaders.
 */
व्योम __init omap2_sdrc_init(काष्ठा omap_sdrc_params *sdrc_cs0,
			    काष्ठा omap_sdrc_params *sdrc_cs1)
अणु
	u32 l;

	l = sms_पढ़ो_reg(SMS_SYSCONFIG);
	l &= ~(0x3 << 3);
	l |= (0x2 << 3);
	sms_ग_लिखो_reg(l, SMS_SYSCONFIG);

	l = sdrc_पढ़ो_reg(SDRC_SYSCONFIG);
	l &= ~(0x3 << 3);
	l |= (0x2 << 3);
	sdrc_ग_लिखो_reg(l, SDRC_SYSCONFIG);

	sdrc_init_params_cs0 = sdrc_cs0;
	sdrc_init_params_cs1 = sdrc_cs1;

	/* XXX Enable SRFRONIDLEREQ here also? */
	/*
	 * PWDENA should not be set due to 34xx erratum 1.150 - PWDENA
	 * can cause अक्रमom memory corruption
	 */
	l = (1 << SDRC_POWER_EXTCLKDIS_SHIFT) |
		(1 << SDRC_POWER_PAGEPOLICY_SHIFT);
	sdrc_ग_लिखो_reg(l, SDRC_POWER);
	omap2_sms_save_context();
पूर्ण
