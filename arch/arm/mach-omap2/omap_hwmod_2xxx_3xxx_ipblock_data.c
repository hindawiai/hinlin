<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap_hwmod_2xxx_3xxx_ipblock_data.c - common IP block data क्रम OMAP2/3
 *
 * Copyright (C) 2011 Nokia Corporation
 * Copyright (C) 2012 Texas Instruments, Inc.
 * Paul Walmsley
 */

#समावेश <linux/dmaengine.h>
#समावेश <linux/omap-dma.h>

#समावेश "omap_hwmod.h"
#समावेश "hdq1w.h"

#समावेश "omap_hwmod_common_data.h"

/* UART */

अटल काष्ठा omap_hwmod_class_sysconfig omap2_uart_sysc = अणु
	.rev_offs	= 0x50,
	.sysc_offs	= 0x54,
	.syss_offs	= 0x58,
	.sysc_flags	= (SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTRESET |
			   SYSC_HAS_AUTOIDLE | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

काष्ठा omap_hwmod_class omap2_uart_class = अणु
	.name	= "uart",
	.sysc	= &omap2_uart_sysc,
पूर्ण;

/*
 * 'venc' class
 * video encoder
 */

काष्ठा omap_hwmod_class omap2_venc_hwmod_class = अणु
	.name = "venc",
पूर्ण;

/*
 * omap_hwmod class data
 */

काष्ठा omap_hwmod_class l3_hwmod_class = अणु
	.name = "l3",
पूर्ण;

काष्ठा omap_hwmod_class l4_hwmod_class = अणु
	.name = "l4",
पूर्ण;

काष्ठा omap_hwmod_class mpu_hwmod_class = अणु
	.name = "mpu",
पूर्ण;

काष्ठा omap_hwmod_class iva_hwmod_class = अणु
	.name = "iva",
पूर्ण;

काष्ठा omap_hwmod_class_sysconfig omap2_hdq1w_sysc = अणु
	.rev_offs	= 0x0,
	.sysc_offs	= 0x14,
	.syss_offs	= 0x18,
	.sysc_flags	= (SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE |
			   SYSS_HAS_RESET_STATUS),
	.sysc_fields    = &omap_hwmod_sysc_type1,
पूर्ण;

काष्ठा omap_hwmod_class omap2_hdq1w_class = अणु
	.name	= "hdq1w",
	.sysc	= &omap2_hdq1w_sysc,
	.reset	= &omap_hdq1w_reset,
पूर्ण;
