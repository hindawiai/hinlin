<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap_hwmod common data काष्ठाures
 *
 * Copyright (C) 2010 Texas Instruments, Inc.
 * Thara Gopinath <thara@ti.com>
 * Benoथऍt Cousson
 *
 * Copyright (C) 2010 Nokia Corporation
 * Paul Walmsley
 *
 * This data/काष्ठाures are to be used जबतक defining OMAP on-chip module
 * data and their पूर्णांकegration with other OMAP modules and Linux.
 */

#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_data/ti-sysc.h>

#समावेश "omap_hwmod.h"

#समावेश "omap_hwmod_common_data.h"

/**
 * काष्ठा omap_hwmod_sysc_type1 - TYPE1 sysconfig scheme.
 *
 * To be used by hwmod काष्ठाure to specअगरy the sysconfig offsets
 * अगर the device ip is compliant with the original PRCM protocol
 * defined क्रम OMAP2420.
 */
काष्ठा sysc_regbits omap_hwmod_sysc_type1 = अणु
	.midle_shअगरt	= SYSC_TYPE1_MIDLEMODE_SHIFT,
	.clkact_shअगरt	= SYSC_TYPE1_CLOCKACTIVITY_SHIFT,
	.sidle_shअगरt	= SYSC_TYPE1_SIDLEMODE_SHIFT,
	.enwkup_shअगरt	= SYSC_TYPE1_ENAWAKEUP_SHIFT,
	.srst_shअगरt	= SYSC_TYPE1_SOFTRESET_SHIFT,
	.स्वतःidle_shअगरt	= SYSC_TYPE1_AUTOIDLE_SHIFT,
पूर्ण;

/**
 * काष्ठा omap_hwmod_sysc_type2 - TYPE2 sysconfig scheme.
 *
 * To be used by hwmod काष्ठाure to specअगरy the sysconfig offsets अगर the
 * device ip is compliant with the new PRCM protocol defined क्रम new
 * OMAP4 IPs.
 */
काष्ठा sysc_regbits omap_hwmod_sysc_type2 = अणु
	.midle_shअगरt	= SYSC_TYPE2_MIDLEMODE_SHIFT,
	.sidle_shअगरt	= SYSC_TYPE2_SIDLEMODE_SHIFT,
	.srst_shअगरt	= SYSC_TYPE2_SOFTRESET_SHIFT,
	.dmadisable_shअगरt = SYSC_TYPE2_DMADISABLE_SHIFT,
पूर्ण;

/**
 * काष्ठा omap_hwmod_sysc_type3 - TYPE3 sysconfig scheme.
 * Used by some IPs on AM33xx
 */
काष्ठा sysc_regbits omap_hwmod_sysc_type3 = अणु
	.midle_shअगरt	= SYSC_TYPE3_MIDLEMODE_SHIFT,
	.sidle_shअगरt	= SYSC_TYPE3_SIDLEMODE_SHIFT,
पूर्ण;

काष्ठा omap_dss_dispc_dev_attr omap2_3_dss_dispc_dev_attr = अणु
	.manager_count		= 2,
	.has_frameकरोnetv_irq	= 0
पूर्ण;

काष्ठा sysc_regbits omap34xx_sr_sysc_fields = अणु
	.clkact_shअगरt	= 20,
पूर्ण;

काष्ठा sysc_regbits omap36xx_sr_sysc_fields = अणु
	.sidle_shअगरt	= 24,
	.enwkup_shअगरt	= 26,
पूर्ण;

काष्ठा sysc_regbits omap3_sham_sysc_fields = अणु
	.sidle_shअगरt	= 4,
	.srst_shअगरt	= 1,
	.स्वतःidle_shअगरt	= 0,
पूर्ण;

काष्ठा sysc_regbits omap3xxx_aes_sysc_fields = अणु
	.sidle_shअगरt	= 6,
	.srst_shअगरt	= 1,
	.स्वतःidle_shअगरt	= 0,
पूर्ण;

काष्ठा sysc_regbits omap_hwmod_sysc_type_mcasp = अणु
	.sidle_shअगरt	= 0,
पूर्ण;

काष्ठा sysc_regbits omap_hwmod_sysc_type_usb_host_fs = अणु
	.midle_shअगरt	= 4,
	.sidle_shअगरt	= 2,
	.srst_shअगरt	= 1,
पूर्ण;
