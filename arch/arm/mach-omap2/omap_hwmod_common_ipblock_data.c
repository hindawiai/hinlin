<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap_hwmod_common_ipblock_data.c - common IP block data क्रम OMAP2+
 *
 * Copyright (C) 2011 Nokia Corporation
 * Copyright (C) 2012 Texas Instruments, Inc.
 * Paul Walmsley
 */

#समावेश "omap_hwmod.h"
#समावेश "omap_hwmod_common_data.h"

/*
 * 'dss' class
 * display sub-प्रणाली
 */

अटल काष्ठा omap_hwmod_class_sysconfig omap2_dss_sysc = अणु
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE |
			   SYSS_HAS_RESET_STATUS),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

काष्ठा omap_hwmod_class omap2_dss_hwmod_class = अणु
	.name	= "dss",
	.sysc	= &omap2_dss_sysc,
	.reset	= omap_dss_reset,
पूर्ण;

/*
 * 'rfbi' class
 * remote frame buffer पूर्णांकerface
 */

अटल काष्ठा omap_hwmod_class_sysconfig omap2_rfbi_sysc = अणु
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSC_HAS_AUTOIDLE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

काष्ठा omap_hwmod_class omap2_rfbi_hwmod_class = अणु
	.name	= "rfbi",
	.sysc	= &omap2_rfbi_sysc,
पूर्ण;

