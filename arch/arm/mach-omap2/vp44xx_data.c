<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP3 Voltage Processor (VP) data
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

#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/init.h>

#समावेश "common.h"

#समावेश "prm44xx.h"
#समावेश "prm-regbits-44xx.h"
#समावेश "voltage.h"

#समावेश "vp.h"

अटल स्थिर काष्ठा omap_vp_ops omap4_vp_ops = अणु
	.check_txकरोne = omap_prm_vp_check_txकरोne,
	.clear_txकरोne = omap_prm_vp_clear_txकरोne,
पूर्ण;

/*
 * VP data common to 44xx chips
 * XXX This stuff presumably beदीर्घs in the vp44xx.c or vp.c file.
 */
अटल स्थिर काष्ठा omap_vp_common omap4_vp_common = अणु
	.vpconfig_erroroffset_mask = OMAP4430_ERROROFFSET_MASK,
	.vpconfig_errorgain_mask = OMAP4430_ERRORGAIN_MASK,
	.vpconfig_initvoltage_mask = OMAP4430_INITVOLTAGE_MASK,
	.vpconfig_समयouten = OMAP4430_TIMEOUTEN_MASK,
	.vpconfig_initvdd = OMAP4430_INITVDD_MASK,
	.vpconfig_क्रमceupdate = OMAP4430_FORCEUPDATE_MASK,
	.vpconfig_vpenable = OMAP4430_VPENABLE_MASK,
	.vstepmin_smpsरुकोसमयmin_shअगरt = OMAP4430_SMPSWAITTIMEMIN_SHIFT,
	.vstepmax_smpsरुकोसमयmax_shअगरt = OMAP4430_SMPSWAITTIMEMAX_SHIFT,
	.vstepmin_stepmin_shअगरt = OMAP4430_VSTEPMIN_SHIFT,
	.vstepmax_stepmax_shअगरt = OMAP4430_VSTEPMAX_SHIFT,
	.vlimitto_vddmin_shअगरt = OMAP4430_VDDMIN_SHIFT,
	.vlimitto_vddmax_shअगरt = OMAP4430_VDDMAX_SHIFT,
	.vlimitto_समयout_shअगरt = OMAP4430_TIMEOUT_SHIFT,
	.vpvoltage_mask = OMAP4430_VPVOLTAGE_MASK,
	.ops = &omap4_vp_ops,
पूर्ण;

काष्ठा omap_vp_instance omap4_vp_mpu = अणु
	.id = OMAP4_VP_VDD_MPU_ID,
	.common = &omap4_vp_common,
	.vpconfig = OMAP4_PRM_VP_MPU_CONFIG_OFFSET,
	.vstepmin = OMAP4_PRM_VP_MPU_VSTEPMIN_OFFSET,
	.vstepmax = OMAP4_PRM_VP_MPU_VSTEPMAX_OFFSET,
	.vlimitto = OMAP4_PRM_VP_MPU_VLIMITTO_OFFSET,
	.vstatus = OMAP4_PRM_VP_MPU_STATUS_OFFSET,
	.voltage = OMAP4_PRM_VP_MPU_VOLTAGE_OFFSET,
पूर्ण;

काष्ठा omap_vp_instance omap4_vp_iva = अणु
	.id = OMAP4_VP_VDD_IVA_ID,
	.common = &omap4_vp_common,
	.vpconfig = OMAP4_PRM_VP_IVA_CONFIG_OFFSET,
	.vstepmin = OMAP4_PRM_VP_IVA_VSTEPMIN_OFFSET,
	.vstepmax = OMAP4_PRM_VP_IVA_VSTEPMAX_OFFSET,
	.vlimitto = OMAP4_PRM_VP_IVA_VLIMITTO_OFFSET,
	.vstatus = OMAP4_PRM_VP_IVA_STATUS_OFFSET,
	.voltage = OMAP4_PRM_VP_IVA_VOLTAGE_OFFSET,
पूर्ण;

काष्ठा omap_vp_instance omap4_vp_core = अणु
	.id = OMAP4_VP_VDD_CORE_ID,
	.common = &omap4_vp_common,
	.vpconfig = OMAP4_PRM_VP_CORE_CONFIG_OFFSET,
	.vstepmin = OMAP4_PRM_VP_CORE_VSTEPMIN_OFFSET,
	.vstepmax = OMAP4_PRM_VP_CORE_VSTEPMAX_OFFSET,
	.vlimitto = OMAP4_PRM_VP_CORE_VLIMITTO_OFFSET,
	.vstatus = OMAP4_PRM_VP_CORE_STATUS_OFFSET,
	.voltage = OMAP4_PRM_VP_CORE_VOLTAGE_OFFSET,
पूर्ण;

काष्ठा omap_vp_param omap4_mpu_vp_data = अणु
	.vddmin			= OMAP4_VP_MPU_VLIMITTO_VDDMIN,
	.vddmax			= OMAP4_VP_MPU_VLIMITTO_VDDMAX,
पूर्ण;

काष्ठा omap_vp_param omap4_iva_vp_data = अणु
	.vddmin			= OMAP4_VP_IVA_VLIMITTO_VDDMIN,
	.vddmax			= OMAP4_VP_IVA_VLIMITTO_VDDMAX,
पूर्ण;

काष्ठा omap_vp_param omap4_core_vp_data = अणु
	.vddmin			= OMAP4_VP_CORE_VLIMITTO_VDDMIN,
	.vddmax			= OMAP4_VP_CORE_VLIMITTO_VDDMAX,
पूर्ण;
