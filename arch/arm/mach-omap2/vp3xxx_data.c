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

#समावेश "prm-regbits-34xx.h"
#समावेश "voltage.h"

#समावेश "vp.h"
#समावेश "prm2xxx_3xxx.h"

अटल स्थिर काष्ठा omap_vp_ops omap3_vp_ops = अणु
	.check_txकरोne = omap_prm_vp_check_txकरोne,
	.clear_txकरोne = omap_prm_vp_clear_txकरोne,
पूर्ण;

/*
 * VP data common to 34xx/36xx chips
 * XXX This stuff presumably beदीर्घs in the vp3xxx.c or vp.c file.
 */
अटल स्थिर काष्ठा omap_vp_common omap3_vp_common = अणु
	.vpconfig_erroroffset_mask = OMAP3430_ERROROFFSET_MASK,
	.vpconfig_errorgain_mask = OMAP3430_ERRORGAIN_MASK,
	.vpconfig_initvoltage_mask = OMAP3430_INITVOLTAGE_MASK,
	.vpconfig_समयouten = OMAP3430_TIMEOUTEN_MASK,
	.vpconfig_initvdd = OMAP3430_INITVDD_MASK,
	.vpconfig_क्रमceupdate = OMAP3430_FORCEUPDATE_MASK,
	.vpconfig_vpenable = OMAP3430_VPENABLE_MASK,
	.vstepmin_smpsरुकोसमयmin_shअगरt = OMAP3430_SMPSWAITTIMEMIN_SHIFT,
	.vstepmax_smpsरुकोसमयmax_shअगरt = OMAP3430_SMPSWAITTIMEMAX_SHIFT,
	.vstepmin_stepmin_shअगरt = OMAP3430_VSTEPMIN_SHIFT,
	.vstepmax_stepmax_shअगरt = OMAP3430_VSTEPMAX_SHIFT,
	.vlimitto_vddmin_shअगरt = OMAP3430_VDDMIN_SHIFT,
	.vlimitto_vddmax_shअगरt = OMAP3430_VDDMAX_SHIFT,
	.vlimitto_समयout_shअगरt = OMAP3430_TIMEOUT_SHIFT,
	.vpvoltage_mask = OMAP3430_VPVOLTAGE_MASK,

	.ops = &omap3_vp_ops,
पूर्ण;

काष्ठा omap_vp_instance omap3_vp_mpu = अणु
	.id = OMAP3_VP_VDD_MPU_ID,
	.common = &omap3_vp_common,
	.vpconfig = OMAP3_PRM_VP1_CONFIG_OFFSET,
	.vstepmin = OMAP3_PRM_VP1_VSTEPMIN_OFFSET,
	.vstepmax = OMAP3_PRM_VP1_VSTEPMAX_OFFSET,
	.vlimitto = OMAP3_PRM_VP1_VLIMITTO_OFFSET,
	.vstatus = OMAP3_PRM_VP1_STATUS_OFFSET,
	.voltage = OMAP3_PRM_VP1_VOLTAGE_OFFSET,
पूर्ण;

काष्ठा omap_vp_instance omap3_vp_core = अणु
	.id = OMAP3_VP_VDD_CORE_ID,
	.common = &omap3_vp_common,
	.vpconfig = OMAP3_PRM_VP2_CONFIG_OFFSET,
	.vstepmin = OMAP3_PRM_VP2_VSTEPMIN_OFFSET,
	.vstepmax = OMAP3_PRM_VP2_VSTEPMAX_OFFSET,
	.vlimitto = OMAP3_PRM_VP2_VLIMITTO_OFFSET,
	.vstatus = OMAP3_PRM_VP2_STATUS_OFFSET,
	.voltage = OMAP3_PRM_VP2_VOLTAGE_OFFSET,
पूर्ण;

काष्ठा omap_vp_param omap3_mpu_vp_data = अणु
	.vddmin			= OMAP3430_VP1_VLIMITTO_VDDMIN,
	.vddmax			= OMAP3430_VP1_VLIMITTO_VDDMAX,
पूर्ण;

काष्ठा omap_vp_param omap3_core_vp_data = अणु
	.vddmin			= OMAP3430_VP2_VLIMITTO_VDDMIN,
	.vddmax			= OMAP3430_VP2_VLIMITTO_VDDMAX,
पूर्ण;
