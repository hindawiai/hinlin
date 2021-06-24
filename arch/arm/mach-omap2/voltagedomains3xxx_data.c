<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP3 voltage करोमुख्य data
 *
 * Copyright (C) 2007, 2010 Texas Instruments, Inc.
 * Rajendra Nayak <rnayak@ti.com>
 * Lesly A M <x0080970@ti.com>
 * Thara Gopinath <thara@ti.com>
 *
 * Copyright (C) 2008, 2011 Nokia Corporation
 * Kalle Jokiniemi
 * Paul Walmsley
 */
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>

#समावेश "soc.h"
#समावेश "common.h"
#समावेश "prm-regbits-34xx.h"
#समावेश "omap_opp_data.h"
#समावेश "voltage.h"
#समावेश "vc.h"
#समावेश "vp.h"

/*
 * VDD data
 */

/* OMAP3-common voltageकरोमुख्य data */

अटल काष्ठा voltageकरोमुख्य omap3_voltdm_wkup = अणु
	.name = "wakeup",
पूर्ण;

/* 34xx/36xx voltageकरोमुख्य data */

अटल स्थिर काष्ठा omap_vfsm_instance omap3_vdd1_vfsm = अणु
	.voltsetup_reg = OMAP3_PRM_VOLTSETUP1_OFFSET,
	.voltsetup_mask = OMAP3430_SETUP_TIME1_MASK,
पूर्ण;

अटल स्थिर काष्ठा omap_vfsm_instance omap3_vdd2_vfsm = अणु
	.voltsetup_reg = OMAP3_PRM_VOLTSETUP1_OFFSET,
	.voltsetup_mask = OMAP3430_SETUP_TIME2_MASK,
पूर्ण;

अटल काष्ठा voltageकरोमुख्य omap3_voltdm_mpu = अणु
	.name = "mpu_iva",
	.scalable = true,
	.पढ़ो = omap3_prm_vcvp_पढ़ो,
	.ग_लिखो = omap3_prm_vcvp_ग_लिखो,
	.rmw = omap3_prm_vcvp_rmw,
	.vc = &omap3_vc_mpu,
	.vfsm = &omap3_vdd1_vfsm,
	.vp = &omap3_vp_mpu,
पूर्ण;

अटल काष्ठा voltageकरोमुख्य omap3_voltdm_core = अणु
	.name = "core",
	.scalable = true,
	.पढ़ो = omap3_prm_vcvp_पढ़ो,
	.ग_लिखो = omap3_prm_vcvp_ग_लिखो,
	.rmw = omap3_prm_vcvp_rmw,
	.vc = &omap3_vc_core,
	.vfsm = &omap3_vdd2_vfsm,
	.vp = &omap3_vp_core,
पूर्ण;

अटल काष्ठा voltageकरोमुख्य *voltageकरोमुख्यs_omap3[] __initdata = अणु
	&omap3_voltdm_mpu,
	&omap3_voltdm_core,
	&omap3_voltdm_wkup,
	शून्य,
पूर्ण;

/* AM35xx voltageकरोमुख्य data */

अटल काष्ठा voltageकरोमुख्य am35xx_voltdm_mpu = अणु
	.name = "mpu_iva",
पूर्ण;

अटल काष्ठा voltageकरोमुख्य am35xx_voltdm_core = अणु
	.name = "core",
पूर्ण;

अटल काष्ठा voltageकरोमुख्य *voltageकरोमुख्यs_am35xx[] __initdata = अणु
	&am35xx_voltdm_mpu,
	&am35xx_voltdm_core,
	&omap3_voltdm_wkup,
	शून्य,
पूर्ण;


अटल स्थिर अक्षर *स्थिर sys_clk_name __initस्थिर = "sys_ck";

व्योम __init omap3xxx_voltageकरोमुख्यs_init(व्योम)
अणु
	काष्ठा voltageकरोमुख्य *voltdm;
	काष्ठा voltageकरोमुख्य **voltdms;
	पूर्णांक i;

	/*
	 * XXX Will depend on the process, validation, and binning
	 * क्रम the currently-running IC
	 */
#अगर_घोषित CONFIG_PM_OPP
	अगर (cpu_is_omap3630()) अणु
		omap3_voltdm_mpu.volt_data = omap36xx_vddmpu_volt_data;
		omap3_voltdm_core.volt_data = omap36xx_vddcore_volt_data;
	पूर्ण अन्यथा अणु
		omap3_voltdm_mpu.volt_data = omap34xx_vddmpu_volt_data;
		omap3_voltdm_core.volt_data = omap34xx_vddcore_volt_data;
	पूर्ण
#पूर्ण_अगर

	omap3_voltdm_mpu.vp_param = &omap3_mpu_vp_data;
	omap3_voltdm_core.vp_param = &omap3_core_vp_data;
	omap3_voltdm_mpu.vc_param = &omap3_mpu_vc_data;
	omap3_voltdm_core.vc_param = &omap3_core_vc_data;

	अगर (soc_is_am35xx())
		voltdms = voltageकरोमुख्यs_am35xx;
	अन्यथा
		voltdms = voltageकरोमुख्यs_omap3;

	क्रम (i = 0; voltdm = voltdms[i], voltdm; i++)
		voltdm->sys_clk.name = sys_clk_name;

	voltdm_init(voltdms);
पूर्ण;
