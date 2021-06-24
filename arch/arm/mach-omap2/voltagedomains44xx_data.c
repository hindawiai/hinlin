<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP3/OMAP4 Voltage Management Routines
 *
 * Author: Thara Gopinath	<thara@ti.com>
 *
 * Copyright (C) 2007 Texas Instruments, Inc.
 * Rajendra Nayak <rnayak@ti.com>
 * Lesly A M <x0080970@ti.com>
 *
 * Copyright (C) 2008 Nokia Corporation
 * Kalle Jokiniemi
 *
 * Copyright (C) 2010 Texas Instruments, Inc.
 * Thara Gopinath <thara@ti.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>

#समावेश "common.h"
#समावेश "soc.h"
#समावेश "prm-regbits-44xx.h"
#समावेश "prm44xx.h"
#समावेश "prcm44xx.h"
#समावेश "prminst44xx.h"
#समावेश "voltage.h"
#समावेश "omap_opp_data.h"
#समावेश "vc.h"
#समावेश "vp.h"

अटल स्थिर काष्ठा omap_vfsm_instance omap4_vdd_mpu_vfsm = अणु
	.voltsetup_reg = OMAP4_PRM_VOLTSETUP_MPU_RET_SLEEP_OFFSET,
	.voltsetup_off_reg = OMAP4_PRM_VOLTSETUP_MPU_OFF_OFFSET,
पूर्ण;

अटल स्थिर काष्ठा omap_vfsm_instance omap4_vdd_iva_vfsm = अणु
	.voltsetup_reg = OMAP4_PRM_VOLTSETUP_IVA_RET_SLEEP_OFFSET,
	.voltsetup_off_reg = OMAP4_PRM_VOLTSETUP_IVA_OFF_OFFSET,
पूर्ण;

अटल स्थिर काष्ठा omap_vfsm_instance omap4_vdd_core_vfsm = अणु
	.voltsetup_reg = OMAP4_PRM_VOLTSETUP_CORE_RET_SLEEP_OFFSET,
	.voltsetup_off_reg = OMAP4_PRM_VOLTSETUP_CORE_OFF_OFFSET,
पूर्ण;

अटल काष्ठा voltageकरोमुख्य omap4_voltdm_mpu = अणु
	.name = "mpu",
	.scalable = true,
	.पढ़ो = omap4_prm_vcvp_पढ़ो,
	.ग_लिखो = omap4_prm_vcvp_ग_लिखो,
	.rmw = omap4_prm_vcvp_rmw,
	.vc = &omap4_vc_mpu,
	.vfsm = &omap4_vdd_mpu_vfsm,
	.vp = &omap4_vp_mpu,
पूर्ण;

अटल काष्ठा voltageकरोमुख्य omap4_voltdm_iva = अणु
	.name = "iva",
	.scalable = true,
	.पढ़ो = omap4_prm_vcvp_पढ़ो,
	.ग_लिखो = omap4_prm_vcvp_ग_लिखो,
	.rmw = omap4_prm_vcvp_rmw,
	.vc = &omap4_vc_iva,
	.vfsm = &omap4_vdd_iva_vfsm,
	.vp = &omap4_vp_iva,
पूर्ण;

अटल काष्ठा voltageकरोमुख्य omap4_voltdm_core = अणु
	.name = "core",
	.scalable = true,
	.पढ़ो = omap4_prm_vcvp_पढ़ो,
	.ग_लिखो = omap4_prm_vcvp_ग_लिखो,
	.rmw = omap4_prm_vcvp_rmw,
	.vc = &omap4_vc_core,
	.vfsm = &omap4_vdd_core_vfsm,
	.vp = &omap4_vp_core,
पूर्ण;

अटल काष्ठा voltageकरोमुख्य omap4_voltdm_wkup = अणु
	.name = "wakeup",
पूर्ण;

अटल काष्ठा voltageकरोमुख्य *voltageकरोमुख्यs_omap4[] __initdata = अणु
	&omap4_voltdm_mpu,
	&omap4_voltdm_iva,
	&omap4_voltdm_core,
	&omap4_voltdm_wkup,
	शून्य,
पूर्ण;

अटल स्थिर अक्षर *स्थिर sys_clk_name __initस्थिर = "sys_clkin_ck";

व्योम __init omap44xx_voltageकरोमुख्यs_init(व्योम)
अणु
	काष्ठा voltageकरोमुख्य *voltdm;
	पूर्णांक i;

	/*
	 * XXX Will depend on the process, validation, and binning
	 * क्रम the currently-running IC
	 */
#अगर_घोषित CONFIG_PM_OPP
	अगर (cpu_is_omap443x()) अणु
		omap4_voltdm_mpu.volt_data = omap443x_vdd_mpu_volt_data;
		omap4_voltdm_iva.volt_data = omap443x_vdd_iva_volt_data;
		omap4_voltdm_core.volt_data = omap443x_vdd_core_volt_data;
	पूर्ण अन्यथा अगर (cpu_is_omap446x()) अणु
		omap4_voltdm_mpu.volt_data = omap446x_vdd_mpu_volt_data;
		omap4_voltdm_iva.volt_data = omap446x_vdd_iva_volt_data;
		omap4_voltdm_core.volt_data = omap446x_vdd_core_volt_data;
	पूर्ण
#पूर्ण_अगर

	omap4_voltdm_mpu.vp_param = &omap4_mpu_vp_data;
	omap4_voltdm_iva.vp_param = &omap4_iva_vp_data;
	omap4_voltdm_core.vp_param = &omap4_core_vp_data;

	omap4_voltdm_mpu.vc_param = &omap4_mpu_vc_data;
	omap4_voltdm_iva.vc_param = &omap4_iva_vc_data;
	omap4_voltdm_core.vc_param = &omap4_core_vc_data;

	क्रम (i = 0; voltdm = voltageकरोमुख्यs_omap4[i], voltdm; i++)
		voltdm->sys_clk.name = sys_clk_name;

	voltdm_init(voltageकरोमुख्यs_omap4);
पूर्ण;
