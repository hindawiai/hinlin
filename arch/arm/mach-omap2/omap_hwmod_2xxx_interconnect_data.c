<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap_hwmod_2xxx_पूर्णांकerconnect_data.c - common पूर्णांकerconnect data क्रम OMAP2xxx
 *
 * Copyright (C) 2009-2011 Nokia Corporation
 * Paul Walmsley
 *
 * XXX handle crossbar/shared link dअगरference क्रम L3?
 * XXX these should be marked initdata क्रम multi-OMAP kernels
 */
#समावेश <linux/sizes.h>

#समावेश "omap_hwmod.h"
#समावेश "l3_2xxx.h"
#समावेश "l4_2xxx.h"
#समावेश "serial.h"

#समावेश "omap_hwmod_common_data.h"

/*
 * Common पूर्णांकerconnect data
 */

/* L3 -> L4_CORE पूर्णांकerface */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_l3_मुख्य__l4_core = अणु
	.master	= &omap2xxx_l3_मुख्य_hwmod,
	.slave	= &omap2xxx_l4_core_hwmod,
	.user	= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* MPU -> L3 पूर्णांकerface */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_mpu__l3_मुख्य = अणु
	.master = &omap2xxx_mpu_hwmod,
	.slave	= &omap2xxx_l3_मुख्य_hwmod,
	.user	= OCP_USER_MPU,
पूर्ण;

/* DSS -> l3 */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_dss__l3 = अणु
	.master		= &omap2xxx_dss_core_hwmod,
	.slave		= &omap2xxx_l3_मुख्य_hwmod,
	.fw = अणु
		.omap2 = अणु
			.l3_perm_bit  = OMAP2_L3_CORE_FW_CONNID_DSS,
			.flags	= OMAP_FIREWALL_L3,
		पूर्ण,
	पूर्ण,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* L4_CORE -> L4_WKUP पूर्णांकerface */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_l4_core__l4_wkup = अणु
	.master	= &omap2xxx_l4_core_hwmod,
	.slave	= &omap2xxx_l4_wkup_hwmod,
	.user	= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* L4 CORE -> UART1 पूर्णांकerface */
काष्ठा omap_hwmod_ocp_अगर omap2_l4_core__uart1 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_uart1_hwmod,
	.clk		= "uart1_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* L4 CORE -> UART2 पूर्णांकerface */
काष्ठा omap_hwmod_ocp_अगर omap2_l4_core__uart2 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_uart2_hwmod,
	.clk		= "uart2_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* L4 PER -> UART3 पूर्णांकerface */
काष्ठा omap_hwmod_ocp_अगर omap2_l4_core__uart3 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_uart3_hwmod,
	.clk		= "uart3_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4 core -> mcspi1 पूर्णांकerface */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_l4_core__mcspi1 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_mcspi1_hwmod,
	.clk		= "mcspi1_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4 core -> mcspi2 पूर्णांकerface */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_l4_core__mcspi2 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_mcspi2_hwmod,
	.clk		= "mcspi2_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> समयr3 */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_l4_core__समयr3 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_समयr3_hwmod,
	.clk		= "gpt3_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> समयr4 */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_l4_core__समयr4 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_समयr4_hwmod,
	.clk		= "gpt4_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> समयr5 */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_l4_core__समयr5 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_समयr5_hwmod,
	.clk		= "gpt5_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> समयr6 */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_l4_core__समयr6 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_समयr6_hwmod,
	.clk		= "gpt6_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> समयr7 */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_l4_core__समयr7 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_समयr7_hwmod,
	.clk		= "gpt7_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> समयr8 */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_l4_core__समयr8 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_समयr8_hwmod,
	.clk		= "gpt8_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> समयr9 */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_l4_core__समयr9 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_समयr9_hwmod,
	.clk		= "gpt9_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> समयr10 */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_l4_core__समयr10 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_समयr10_hwmod,
	.clk		= "gpt10_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> समयr11 */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_l4_core__समयr11 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_समयr11_hwmod,
	.clk		= "gpt11_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> समयr12 */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_l4_core__समयr12 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_समयr12_hwmod,
	.clk		= "gpt12_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> dss */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_l4_core__dss = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_dss_core_hwmod,
	.clk		= "dss_ick",
	.fw = अणु
		.omap2 = अणु
			.l4_fw_region  = OMAP2420_L4_CORE_FW_DSS_CORE_REGION,
			.flags	= OMAP_FIREWALL_L4,
		पूर्ण,
	पूर्ण,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> dss_dispc */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_l4_core__dss_dispc = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_dss_dispc_hwmod,
	.clk		= "dss_ick",
	.fw = अणु
		.omap2 = अणु
			.l4_fw_region  = OMAP2420_L4_CORE_FW_DSS_DISPC_REGION,
			.flags	= OMAP_FIREWALL_L4,
		पूर्ण,
	पूर्ण,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> dss_rfbi */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_l4_core__dss_rfbi = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_dss_rfbi_hwmod,
	.clk		= "dss_ick",
	.fw = अणु
		.omap2 = अणु
			.l4_fw_region  = OMAP2420_L4_CORE_FW_DSS_CORE_REGION,
			.flags	= OMAP_FIREWALL_L4,
		पूर्ण,
	पूर्ण,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> dss_venc */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_l4_core__dss_venc = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_dss_venc_hwmod,
	.clk		= "dss_ick",
	.fw = अणु
		.omap2 = अणु
			.l4_fw_region  = OMAP2420_L4_CORE_FW_DSS_VENC_REGION,
			.flags	= OMAP_FIREWALL_L4,
		पूर्ण,
	पूर्ण,
	.flags		= OCPIF_SWSUP_IDLE,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> rng */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_l4_core__rng = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_rng_hwmod,
	.clk		= "rng_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4 core -> sham पूर्णांकerface */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_l4_core__sham = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_sham_hwmod,
	.clk		= "sha_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4 core -> aes पूर्णांकerface */
काष्ठा omap_hwmod_ocp_अगर omap2xxx_l4_core__aes = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2xxx_aes_hwmod,
	.clk		= "aes_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;
