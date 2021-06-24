<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP44xx Power Management रेजिस्टर bits
 *
 * Copyright (C) 2009-2010 Texas Instruments, Inc.
 * Copyright (C) 2009-2010 Nokia Corporation
 *
 * Paul Walmsley (paul@pwsan.com)
 * Rajendra Nayak (rnayak@ti.com)
 * Benoit Cousson (b-cousson@ti.com)
 *
 * This file is स्वतःmatically generated from the OMAP hardware databases.
 * We respectfully ask that any modअगरications to this file be coordinated
 * with the खुला linux-omap@vger.kernel.org mailing list and the
 * authors above to ensure that the स्वतःgeneration scripts are kept
 * up-to-date with the file contents.
 */

#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_PRM_REGBITS_44XX_H
#घोषणा __ARCH_ARM_MACH_OMAP2_PRM_REGBITS_44XX_H

#घोषणा OMAP4430_C2C_RST_SHIFT						10
#घोषणा OMAP4430_CMDRA_VDD_CORE_L_MASK					(0xff << 0)
#घोषणा OMAP4430_CMDRA_VDD_IVA_L_MASK					(0xff << 8)
#घोषणा OMAP4430_CMDRA_VDD_MPU_L_MASK					(0xff << 16)
#घोषणा OMAP4430_DATA_SHIFT						16
#घोषणा OMAP4430_ERRORGAIN_MASK						(0xff << 16)
#घोषणा OMAP4430_ERROROFFSET_MASK					(0xff << 24)
#घोषणा OMAP4430_EXTERNAL_WARM_RST_SHIFT				5
#घोषणा OMAP4430_FORCEUPDATE_MASK					(1 << 1)
#घोषणा OMAP4430_GLOBAL_COLD_RST_SHIFT					0
#घोषणा OMAP4430_GLOBAL_WARM_SW_RST_SHIFT				1
#घोषणा OMAP4430_GLOBAL_WUEN_MASK					(1 << 16)
#घोषणा OMAP4430_HSMCODE_MASK						(0x7 << 0)
#घोषणा OMAP4430_SRMODEEN_MASK						(1 << 4)
#घोषणा OMAP4430_HSMODEEN_MASK						(1 << 3)
#घोषणा OMAP4430_HSSCLL_SHIFT						24
#घोषणा OMAP4430_ICEPICK_RST_SHIFT					9
#घोषणा OMAP4430_INITVDD_MASK						(1 << 2)
#घोषणा OMAP4430_INITVOLTAGE_MASK					(0xff << 8)
#घोषणा OMAP4430_LASTPOWERSTATEENTERED_SHIFT				24
#घोषणा OMAP4430_LASTPOWERSTATEENTERED_MASK				(0x3 << 24)
#घोषणा OMAP4430_LOGICRETSTATE_SHIFT					2
#घोषणा OMAP4430_LOGICRETSTATE_MASK					(1 << 2)
#घोषणा OMAP4430_LOGICSTATEST_SHIFT					2
#घोषणा OMAP4430_LOGICSTATEST_MASK					(1 << 2)
#घोषणा OMAP4430_LOSTCONTEXT_DFF_MASK					(1 << 0)
#घोषणा OMAP4430_LOSTMEM_AESSMEM_MASK					(1 << 8)
#घोषणा OMAP4430_LOWPOWERSTATECHANGE_SHIFT				4
#घोषणा OMAP4430_LOWPOWERSTATECHANGE_MASK				(1 << 4)
#घोषणा OMAP4430_MPU_SECURITY_VIOL_RST_SHIFT				2
#घोषणा OMAP4430_MPU_WDT_RST_SHIFT					3
#घोषणा OMAP4430_OCP_NRET_BANK_ONSTATE_MASK				(0x3 << 24)
#घोषणा OMAP4430_OCP_NRET_BANK_RETSTATE_MASK				(1 << 12)
#घोषणा OMAP4430_OCP_NRET_BANK_STATEST_MASK				(0x3 << 12)
#घोषणा OMAP4430_OFF_SHIFT						0
#घोषणा OMAP4430_ON_SHIFT						24
#घोषणा OMAP4430_ON_MASK						(0xff << 24)
#घोषणा OMAP4430_ONLP_SHIFT						16
#घोषणा OMAP4430_RAMP_DOWN_COUNT_SHIFT					16
#घोषणा OMAP4430_RAMP_UP_COUNT_SHIFT					0
#घोषणा OMAP4430_RAMP_UP_PRESCAL_SHIFT					8
#घोषणा OMAP4430_REGADDR_SHIFT						8
#घोषणा OMAP4430_RET_SHIFT						8
#घोषणा OMAP4430_RST_GLOBAL_WARM_SW_MASK				(1 << 0)
#घोषणा OMAP4430_SA_VDD_CORE_L_SHIFT					0
#घोषणा OMAP4430_SA_VDD_CORE_L_0_6_MASK					(0x7f << 0)
#घोषणा OMAP4430_SA_VDD_IVA_L_SHIFT					8
#घोषणा OMAP4430_SA_VDD_IVA_L_PRM_VC_SMPS_SA_MASK			(0x7f << 8)
#घोषणा OMAP4430_SA_VDD_MPU_L_SHIFT					16
#घोषणा OMAP4430_SA_VDD_MPU_L_PRM_VC_SMPS_SA_MASK			(0x7f << 16)
#घोषणा OMAP4430_SCLH_SHIFT						0
#घोषणा OMAP4430_SCLL_SHIFT						8
#घोषणा OMAP4430_SECURE_WDT_RST_SHIFT					4
#घोषणा OMAP4430_SLAVEADDR_SHIFT					0
#घोषणा OMAP4430_SMPSWAITTIMEMAX_SHIFT					8
#घोषणा OMAP4430_SMPSWAITTIMEMIN_SHIFT					8
#घोषणा OMAP4430_TIMEOUT_SHIFT						0
#घोषणा OMAP4430_TIMEOUTEN_MASK						(1 << 3)
#घोषणा OMAP4430_VALID_MASK						(1 << 24)
#घोषणा OMAP4430_VDDMAX_SHIFT						24
#घोषणा OMAP4430_VDDMIN_SHIFT						16
#घोषणा OMAP4430_VDD_CORE_VOLT_MGR_RST_SHIFT				8
#घोषणा OMAP4430_VDD_IVA_VOLT_MGR_RST_SHIFT				7
#घोषणा OMAP4430_VDD_MPU_VOLT_MGR_RST_SHIFT				6
#घोषणा OMAP4430_VOLRA_VDD_CORE_L_MASK					(0xff << 0)
#घोषणा OMAP4430_VOLRA_VDD_IVA_L_MASK					(0xff << 8)
#घोषणा OMAP4430_VOLRA_VDD_MPU_L_MASK					(0xff << 16)
#घोषणा OMAP4430_VPENABLE_MASK						(1 << 0)
#घोषणा OMAP4430_VPVOLTAGE_MASK						(0xff << 0)
#घोषणा OMAP4430_VP_CORE_TRANXDONE_ST_MASK				(1 << 21)
#घोषणा OMAP4430_VP_IVA_TRANXDONE_ST_MASK				(1 << 29)
#घोषणा OMAP4430_VP_MPU_TRANXDONE_ST_MASK				(1 << 5)
#घोषणा OMAP4430_VSTEPMAX_SHIFT						0
#घोषणा OMAP4430_VSTEPMIN_SHIFT						0
#घोषणा OMAP4430_WUCLK_CTRL_MASK					(1 << 8)
#घोषणा OMAP4430_WUCLK_STATUS_SHIFT					9
#घोषणा OMAP4430_WUCLK_STATUS_MASK					(1 << 9)
#पूर्ण_अगर
