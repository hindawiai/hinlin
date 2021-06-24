<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP5 Voltage Management Routines
 *
 * Based on voltageकरोमुख्यs44xx_data.c
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - https://www.ti.com
 */
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>

#समावेश "common.h"

#समावेश "prm54xx.h"
#समावेश "voltage.h"
#समावेश "omap_opp_data.h"
#समावेश "vc.h"
#समावेश "vp.h"

अटल स्थिर काष्ठा omap_vfsm_instance omap5_vdd_mpu_vfsm = अणु
	.voltsetup_reg = OMAP54XX_PRM_VOLTSETUP_MPU_RET_SLEEP_OFFSET,
पूर्ण;

अटल स्थिर काष्ठा omap_vfsm_instance omap5_vdd_mm_vfsm = अणु
	.voltsetup_reg = OMAP54XX_PRM_VOLTSETUP_MM_RET_SLEEP_OFFSET,
पूर्ण;

अटल स्थिर काष्ठा omap_vfsm_instance omap5_vdd_core_vfsm = अणु
	.voltsetup_reg = OMAP54XX_PRM_VOLTSETUP_CORE_RET_SLEEP_OFFSET,
पूर्ण;

अटल काष्ठा voltageकरोमुख्य omap5_voltdm_mpu = अणु
	.name = "mpu",
	.scalable = true,
	.पढ़ो = omap4_prm_vcvp_पढ़ो,
	.ग_लिखो = omap4_prm_vcvp_ग_लिखो,
	.rmw = omap4_prm_vcvp_rmw,
	.vc = &omap4_vc_mpu,
	.vfsm = &omap5_vdd_mpu_vfsm,
	.vp = &omap4_vp_mpu,
पूर्ण;

अटल काष्ठा voltageकरोमुख्य omap5_voltdm_mm = अणु
	.name = "mm",
	.scalable = true,
	.पढ़ो = omap4_prm_vcvp_पढ़ो,
	.ग_लिखो = omap4_prm_vcvp_ग_लिखो,
	.rmw = omap4_prm_vcvp_rmw,
	.vc = &omap4_vc_iva,
	.vfsm = &omap5_vdd_mm_vfsm,
	.vp = &omap4_vp_iva,
पूर्ण;

अटल काष्ठा voltageकरोमुख्य omap5_voltdm_core = अणु
	.name = "core",
	.scalable = true,
	.पढ़ो = omap4_prm_vcvp_पढ़ो,
	.ग_लिखो = omap4_prm_vcvp_ग_लिखो,
	.rmw = omap4_prm_vcvp_rmw,
	.vc = &omap4_vc_core,
	.vfsm = &omap5_vdd_core_vfsm,
	.vp = &omap4_vp_core,
पूर्ण;

अटल काष्ठा voltageकरोमुख्य omap5_voltdm_wkup = अणु
	.name = "wkup",
पूर्ण;

अटल काष्ठा voltageकरोमुख्य *voltageकरोमुख्यs_omap5[] __initdata = अणु
	&omap5_voltdm_mpu,
	&omap5_voltdm_mm,
	&omap5_voltdm_core,
	&omap5_voltdm_wkup,
	शून्य,
पूर्ण;

अटल स्थिर अक्षर *स्थिर sys_clk_name __initस्थिर = "sys_clkin";

व्योम __init omap54xx_voltageकरोमुख्यs_init(व्योम)
अणु
	काष्ठा voltageकरोमुख्य *voltdm;
	पूर्णांक i;

	क्रम (i = 0; voltdm = voltageकरोमुख्यs_omap5[i], voltdm; i++)
		voltdm->sys_clk.name = sys_clk_name;

	voltdm_init(voltageकरोमुख्यs_omap5);
पूर्ण;
