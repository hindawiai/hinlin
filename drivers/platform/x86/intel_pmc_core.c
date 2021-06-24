<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Core SoC Power Management Controller Driver
 *
 * Copyright (c) 2016, Intel Corporation.
 * All Rights Reserved.
 *
 * Authors: Rajneesh Bhardwaj <rajneesh.bhardwaj@पूर्णांकel.com>
 *          Vishwanath Somayaji <vishwanath.somayaji@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmi.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/suspend.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/uuid.h>

#समावेश <acpi/acpi_bus.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/tsc.h>

#समावेश "intel_pmc_core.h"

#घोषणा ACPI_S0IX_DSM_UUID		"57a6512e-3979-4e9d-9708-ff13b2508972"
#घोषणा ACPI_GET_LOW_MODE_REGISTERS	1

/* PKGC MSRs are common across Intel Core SoCs */
अटल स्थिर काष्ठा pmc_bit_map msr_map[] = अणु
	अणु"Package C2",                  MSR_PKG_C2_RESIDENCYपूर्ण,
	अणु"Package C3",                  MSR_PKG_C3_RESIDENCYपूर्ण,
	अणु"Package C6",                  MSR_PKG_C6_RESIDENCYपूर्ण,
	अणु"Package C7",                  MSR_PKG_C7_RESIDENCYपूर्ण,
	अणु"Package C8",                  MSR_PKG_C8_RESIDENCYपूर्ण,
	अणु"Package C9",                  MSR_PKG_C9_RESIDENCYपूर्ण,
	अणु"Package C10",                 MSR_PKG_C10_RESIDENCYपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map spt_pll_map[] = अणु
	अणु"MIPI PLL",			SPT_PMC_BIT_MPHY_CMN_LANE0पूर्ण,
	अणु"GEN2 USB2PCIE2 PLL",		SPT_PMC_BIT_MPHY_CMN_LANE1पूर्ण,
	अणु"DMIPCIE3 PLL",		SPT_PMC_BIT_MPHY_CMN_LANE2पूर्ण,
	अणु"SATA PLL",			SPT_PMC_BIT_MPHY_CMN_LANE3पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map spt_mphy_map[] = अणु
	अणु"MPHY CORE LANE 0",           SPT_PMC_BIT_MPHY_LANE0पूर्ण,
	अणु"MPHY CORE LANE 1",           SPT_PMC_BIT_MPHY_LANE1पूर्ण,
	अणु"MPHY CORE LANE 2",           SPT_PMC_BIT_MPHY_LANE2पूर्ण,
	अणु"MPHY CORE LANE 3",           SPT_PMC_BIT_MPHY_LANE3पूर्ण,
	अणु"MPHY CORE LANE 4",           SPT_PMC_BIT_MPHY_LANE4पूर्ण,
	अणु"MPHY CORE LANE 5",           SPT_PMC_BIT_MPHY_LANE5पूर्ण,
	अणु"MPHY CORE LANE 6",           SPT_PMC_BIT_MPHY_LANE6पूर्ण,
	अणु"MPHY CORE LANE 7",           SPT_PMC_BIT_MPHY_LANE7पूर्ण,
	अणु"MPHY CORE LANE 8",           SPT_PMC_BIT_MPHY_LANE8पूर्ण,
	अणु"MPHY CORE LANE 9",           SPT_PMC_BIT_MPHY_LANE9पूर्ण,
	अणु"MPHY CORE LANE 10",          SPT_PMC_BIT_MPHY_LANE10पूर्ण,
	अणु"MPHY CORE LANE 11",          SPT_PMC_BIT_MPHY_LANE11पूर्ण,
	अणु"MPHY CORE LANE 12",          SPT_PMC_BIT_MPHY_LANE12पूर्ण,
	अणु"MPHY CORE LANE 13",          SPT_PMC_BIT_MPHY_LANE13पूर्ण,
	अणु"MPHY CORE LANE 14",          SPT_PMC_BIT_MPHY_LANE14पूर्ण,
	अणु"MPHY CORE LANE 15",          SPT_PMC_BIT_MPHY_LANE15पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map spt_pfear_map[] = अणु
	अणु"PMC",				SPT_PMC_BIT_PMCपूर्ण,
	अणु"OPI-DMI",			SPT_PMC_BIT_OPIपूर्ण,
	अणु"SPI / eSPI",			SPT_PMC_BIT_SPIपूर्ण,
	अणु"XHCI",			SPT_PMC_BIT_XHCIपूर्ण,
	अणु"SPA",				SPT_PMC_BIT_SPAपूर्ण,
	अणु"SPB",				SPT_PMC_BIT_SPBपूर्ण,
	अणु"SPC",				SPT_PMC_BIT_SPCपूर्ण,
	अणु"GBE",				SPT_PMC_BIT_GBEपूर्ण,
	अणु"SATA",			SPT_PMC_BIT_SATAपूर्ण,
	अणु"HDA-PGD0",			SPT_PMC_BIT_HDA_PGD0पूर्ण,
	अणु"HDA-PGD1",			SPT_PMC_BIT_HDA_PGD1पूर्ण,
	अणु"HDA-PGD2",			SPT_PMC_BIT_HDA_PGD2पूर्ण,
	अणु"HDA-PGD3",			SPT_PMC_BIT_HDA_PGD3पूर्ण,
	अणु"RSVD",			SPT_PMC_BIT_RSVD_0Bपूर्ण,
	अणु"LPSS",			SPT_PMC_BIT_LPSSपूर्ण,
	अणु"LPC",				SPT_PMC_BIT_LPCपूर्ण,
	अणु"SMB",				SPT_PMC_BIT_SMBपूर्ण,
	अणु"ISH",				SPT_PMC_BIT_ISHपूर्ण,
	अणु"P2SB",			SPT_PMC_BIT_P2SBपूर्ण,
	अणु"DFX",				SPT_PMC_BIT_DFXपूर्ण,
	अणु"SCC",				SPT_PMC_BIT_SCCपूर्ण,
	अणु"RSVD",			SPT_PMC_BIT_RSVD_0Cपूर्ण,
	अणु"FUSE",			SPT_PMC_BIT_FUSEपूर्ण,
	अणु"CAMERA",			SPT_PMC_BIT_CAMREAपूर्ण,
	अणु"RSVD",			SPT_PMC_BIT_RSVD_0Dपूर्ण,
	अणु"USB3-OTG",			SPT_PMC_BIT_USB3_OTGपूर्ण,
	अणु"EXI",				SPT_PMC_BIT_EXIपूर्ण,
	अणु"CSE",				SPT_PMC_BIT_CSEपूर्ण,
	अणु"CSME_KVM",			SPT_PMC_BIT_CSME_KVMपूर्ण,
	अणु"CSME_PMT",			SPT_PMC_BIT_CSME_PMTपूर्ण,
	अणु"CSME_CLINK",			SPT_PMC_BIT_CSME_CLINKपूर्ण,
	अणु"CSME_PTIO",			SPT_PMC_BIT_CSME_PTIOपूर्ण,
	अणु"CSME_USBR",			SPT_PMC_BIT_CSME_USBRपूर्ण,
	अणु"CSME_SUSRAM",			SPT_PMC_BIT_CSME_SUSRAMपूर्ण,
	अणु"CSME_SMT",			SPT_PMC_BIT_CSME_SMTपूर्ण,
	अणु"RSVD",			SPT_PMC_BIT_RSVD_1Aपूर्ण,
	अणु"CSME_SMS2",			SPT_PMC_BIT_CSME_SMS2पूर्ण,
	अणु"CSME_SMS1",			SPT_PMC_BIT_CSME_SMS1पूर्ण,
	अणु"CSME_RTC",			SPT_PMC_BIT_CSME_RTCपूर्ण,
	अणु"CSME_PSF",			SPT_PMC_BIT_CSME_PSFपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map *ext_spt_pfear_map[] = अणु
	/*
	 * Check पूर्णांकel_pmc_core_ids[] users of spt_reg_map क्रम
	 * a list of core SoCs using this.
	 */
	spt_pfear_map,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map spt_ltr_show_map[] = अणु
	अणु"SOUTHPORT_A",		SPT_PMC_LTR_SPAपूर्ण,
	अणु"SOUTHPORT_B",		SPT_PMC_LTR_SPBपूर्ण,
	अणु"SATA",		SPT_PMC_LTR_SATAपूर्ण,
	अणु"GIGABIT_ETHERNET",	SPT_PMC_LTR_GBEपूर्ण,
	अणु"XHCI",		SPT_PMC_LTR_XHCIपूर्ण,
	अणु"Reserved",		SPT_PMC_LTR_RESERVEDपूर्ण,
	अणु"ME",			SPT_PMC_LTR_MEपूर्ण,
	/* EVA is Enterprise Value Add, करोesn't really exist on PCH */
	अणु"EVA",			SPT_PMC_LTR_EVAपूर्ण,
	अणु"SOUTHPORT_C",		SPT_PMC_LTR_SPCपूर्ण,
	अणु"HD_AUDIO",		SPT_PMC_LTR_AZपूर्ण,
	अणु"LPSS",		SPT_PMC_LTR_LPSSपूर्ण,
	अणु"SOUTHPORT_D",		SPT_PMC_LTR_SPDपूर्ण,
	अणु"SOUTHPORT_E",		SPT_PMC_LTR_SPEपूर्ण,
	अणु"CAMERA",		SPT_PMC_LTR_CAMपूर्ण,
	अणु"ESPI",		SPT_PMC_LTR_ESPIपूर्ण,
	अणु"SCC",			SPT_PMC_LTR_SCCपूर्ण,
	अणु"ISH",			SPT_PMC_LTR_ISHपूर्ण,
	/* Below two cannot be used क्रम LTR_IGNORE */
	अणु"CURRENT_PLATFORM",	SPT_PMC_LTR_CUR_PLTपूर्ण,
	अणु"AGGREGATED_SYSTEM",	SPT_PMC_LTR_CUR_ASLTपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pmc_reg_map spt_reg_map = अणु
	.pfear_sts = ext_spt_pfear_map,
	.mphy_sts = spt_mphy_map,
	.pll_sts = spt_pll_map,
	.ltr_show_sts = spt_ltr_show_map,
	.msr_sts = msr_map,
	.slp_s0_offset = SPT_PMC_SLP_S0_RES_COUNTER_OFFSET,
	.slp_s0_res_counter_step = SPT_PMC_SLP_S0_RES_COUNTER_STEP,
	.ltr_ignore_offset = SPT_PMC_LTR_IGNORE_OFFSET,
	.regmap_length = SPT_PMC_MMIO_REG_LEN,
	.ppfear0_offset = SPT_PMC_XRAM_PPFEAR0A,
	.ppfear_buckets = SPT_PPFEAR_NUM_ENTRIES,
	.pm_cfg_offset = SPT_PMC_PM_CFG_OFFSET,
	.pm_पढ़ो_disable_bit = SPT_PMC_READ_DISABLE_BIT,
	.ltr_ignore_max = SPT_NUM_IP_IGN_ALLOWED,
	.pm_vric1_offset = SPT_PMC_VRIC1_OFFSET,
पूर्ण;

/* Cannon Lake: PGD PFET Enable Ack Status Register(s) biपंचांगap */
अटल स्थिर काष्ठा pmc_bit_map cnp_pfear_map[] = अणु
	अणु"PMC",                 BIT(0)पूर्ण,
	अणु"OPI-DMI",             BIT(1)पूर्ण,
	अणु"SPI/eSPI",            BIT(2)पूर्ण,
	अणु"XHCI",                BIT(3)पूर्ण,
	अणु"SPA",                 BIT(4)पूर्ण,
	अणु"SPB",                 BIT(5)पूर्ण,
	अणु"SPC",                 BIT(6)पूर्ण,
	अणु"GBE",                 BIT(7)पूर्ण,

	अणु"SATA",                BIT(0)पूर्ण,
	अणु"HDA_PGD0",            BIT(1)पूर्ण,
	अणु"HDA_PGD1",            BIT(2)पूर्ण,
	अणु"HDA_PGD2",            BIT(3)पूर्ण,
	अणु"HDA_PGD3",            BIT(4)पूर्ण,
	अणु"SPD",                 BIT(5)पूर्ण,
	अणु"LPSS",                BIT(6)पूर्ण,
	अणु"LPC",                 BIT(7)पूर्ण,

	अणु"SMB",                 BIT(0)पूर्ण,
	अणु"ISH",                 BIT(1)पूर्ण,
	अणु"P2SB",                BIT(2)पूर्ण,
	अणु"NPK_VNN",             BIT(3)पूर्ण,
	अणु"SDX",                 BIT(4)पूर्ण,
	अणु"SPE",                 BIT(5)पूर्ण,
	अणु"Fuse",                BIT(6)पूर्ण,
	अणु"SBR8",		BIT(7)पूर्ण,

	अणु"CSME_FSC",            BIT(0)पूर्ण,
	अणु"USB3_OTG",            BIT(1)पूर्ण,
	अणु"EXI",                 BIT(2)पूर्ण,
	अणु"CSE",                 BIT(3)पूर्ण,
	अणु"CSME_KVM",            BIT(4)पूर्ण,
	अणु"CSME_PMT",            BIT(5)पूर्ण,
	अणु"CSME_CLINK",          BIT(6)पूर्ण,
	अणु"CSME_PTIO",           BIT(7)पूर्ण,

	अणु"CSME_USBR",           BIT(0)पूर्ण,
	अणु"CSME_SUSRAM",         BIT(1)पूर्ण,
	अणु"CSME_SMT1",           BIT(2)पूर्ण,
	अणु"CSME_SMT4",           BIT(3)पूर्ण,
	अणु"CSME_SMS2",           BIT(4)पूर्ण,
	अणु"CSME_SMS1",           BIT(5)पूर्ण,
	अणु"CSME_RTC",            BIT(6)पूर्ण,
	अणु"CSME_PSF",            BIT(7)पूर्ण,

	अणु"SBR0",                BIT(0)पूर्ण,
	अणु"SBR1",                BIT(1)पूर्ण,
	अणु"SBR2",                BIT(2)पूर्ण,
	अणु"SBR3",                BIT(3)पूर्ण,
	अणु"SBR4",                BIT(4)पूर्ण,
	अणु"SBR5",                BIT(5)पूर्ण,
	अणु"CSME_PECI",           BIT(6)पूर्ण,
	अणु"PSF1",                BIT(7)पूर्ण,

	अणु"PSF2",                BIT(0)पूर्ण,
	अणु"PSF3",                BIT(1)पूर्ण,
	अणु"PSF4",                BIT(2)पूर्ण,
	अणु"CNVI",                BIT(3)पूर्ण,
	अणु"UFS0",                BIT(4)पूर्ण,
	अणु"EMMC",                BIT(5)पूर्ण,
	अणु"SPF",			BIT(6)पूर्ण,
	अणु"SBR6",                BIT(7)पूर्ण,

	अणु"SBR7",                BIT(0)पूर्ण,
	अणु"NPK_AON",             BIT(1)पूर्ण,
	अणु"HDA_PGD4",            BIT(2)पूर्ण,
	अणु"HDA_PGD5",            BIT(3)पूर्ण,
	अणु"HDA_PGD6",            BIT(4)पूर्ण,
	अणु"PSF6",		BIT(5)पूर्ण,
	अणु"PSF7",		BIT(6)पूर्ण,
	अणु"PSF8",		BIT(7)पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map *ext_cnp_pfear_map[] = अणु
	/*
	 * Check पूर्णांकel_pmc_core_ids[] users of cnp_reg_map क्रम
	 * a list of core SoCs using this.
	 */
	cnp_pfear_map,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map icl_pfear_map[] = अणु
	अणु"RES_65",		BIT(0)पूर्ण,
	अणु"RES_66",		BIT(1)पूर्ण,
	अणु"RES_67",		BIT(2)पूर्ण,
	अणु"TAM",			BIT(3)पूर्ण,
	अणु"GBETSN",		BIT(4)पूर्ण,
	अणु"TBTLSX",		BIT(5)पूर्ण,
	अणु"RES_71",		BIT(6)पूर्ण,
	अणु"RES_72",		BIT(7)पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map *ext_icl_pfear_map[] = अणु
	/*
	 * Check पूर्णांकel_pmc_core_ids[] users of icl_reg_map क्रम
	 * a list of core SoCs using this.
	 */
	cnp_pfear_map,
	icl_pfear_map,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map tgl_pfear_map[] = अणु
	अणु"PSF9",		BIT(0)पूर्ण,
	अणु"RES_66",		BIT(1)पूर्ण,
	अणु"RES_67",		BIT(2)पूर्ण,
	अणु"RES_68",		BIT(3)पूर्ण,
	अणु"RES_69",		BIT(4)पूर्ण,
	अणु"RES_70",		BIT(5)पूर्ण,
	अणु"TBTLSX",		BIT(6)पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map *ext_tgl_pfear_map[] = अणु
	/*
	 * Check पूर्णांकel_pmc_core_ids[] users of tgl_reg_map क्रम
	 * a list of core SoCs using this.
	 */
	cnp_pfear_map,
	tgl_pfear_map,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map cnp_slps0_dbg0_map[] = अणु
	अणु"AUDIO_D3",		BIT(0)पूर्ण,
	अणु"OTG_D3",		BIT(1)पूर्ण,
	अणु"XHCI_D3",		BIT(2)पूर्ण,
	अणु"LPIO_D3",		BIT(3)पूर्ण,
	अणु"SDX_D3",		BIT(4)पूर्ण,
	अणु"SATA_D3",		BIT(5)पूर्ण,
	अणु"UFS0_D3",		BIT(6)पूर्ण,
	अणु"UFS1_D3",		BIT(7)पूर्ण,
	अणु"EMMC_D3",		BIT(8)पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map cnp_slps0_dbg1_map[] = अणु
	अणु"SDIO_PLL_OFF",	BIT(0)पूर्ण,
	अणु"USB2_PLL_OFF",	BIT(1)पूर्ण,
	अणु"AUDIO_PLL_OFF",	BIT(2)पूर्ण,
	अणु"OC_PLL_OFF",		BIT(3)पूर्ण,
	अणु"MAIN_PLL_OFF",	BIT(4)पूर्ण,
	अणु"XOSC_OFF",		BIT(5)पूर्ण,
	अणु"LPC_CLKS_GATED",	BIT(6)पूर्ण,
	अणु"PCIE_CLKREQS_IDLE",	BIT(7)पूर्ण,
	अणु"AUDIO_ROSC_OFF",	BIT(8)पूर्ण,
	अणु"HPET_XOSC_CLK_REQ",	BIT(9)पूर्ण,
	अणु"PMC_ROSC_SLOW_CLK",	BIT(10)पूर्ण,
	अणु"AON2_ROSC_GATED",	BIT(11)पूर्ण,
	अणु"CLKACKS_DEASSERTED",	BIT(12)पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map cnp_slps0_dbg2_map[] = अणु
	अणु"MPHY_CORE_GATED",	BIT(0)पूर्ण,
	अणु"CSME_GATED",		BIT(1)पूर्ण,
	अणु"USB2_SUS_GATED",	BIT(2)पूर्ण,
	अणु"DYN_FLEX_IO_IDLE",	BIT(3)पूर्ण,
	अणु"GBE_NO_LINK",		BIT(4)पूर्ण,
	अणु"THERM_SEN_DISABLED",	BIT(5)पूर्ण,
	अणु"PCIE_LOW_POWER",	BIT(6)पूर्ण,
	अणु"ISH_VNNAON_REQ_ACT",	BIT(7)पूर्ण,
	अणु"ISH_VNN_REQ_ACT",	BIT(8)पूर्ण,
	अणु"CNV_VNNAON_REQ_ACT",	BIT(9)पूर्ण,
	अणु"CNV_VNN_REQ_ACT",	BIT(10)पूर्ण,
	अणु"NPK_VNNON_REQ_ACT",	BIT(11)पूर्ण,
	अणु"PMSYNC_STATE_IDLE",	BIT(12)पूर्ण,
	अणु"ALST_GT_THRES",	BIT(13)पूर्ण,
	अणु"PMC_ARC_PG_READY",	BIT(14)पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map *cnp_slps0_dbg_maps[] = अणु
	cnp_slps0_dbg0_map,
	cnp_slps0_dbg1_map,
	cnp_slps0_dbg2_map,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map cnp_ltr_show_map[] = अणु
	अणु"SOUTHPORT_A",		CNP_PMC_LTR_SPAपूर्ण,
	अणु"SOUTHPORT_B",		CNP_PMC_LTR_SPBपूर्ण,
	अणु"SATA",		CNP_PMC_LTR_SATAपूर्ण,
	अणु"GIGABIT_ETHERNET",	CNP_PMC_LTR_GBEपूर्ण,
	अणु"XHCI",		CNP_PMC_LTR_XHCIपूर्ण,
	अणु"Reserved",		CNP_PMC_LTR_RESERVEDपूर्ण,
	अणु"ME",			CNP_PMC_LTR_MEपूर्ण,
	/* EVA is Enterprise Value Add, करोesn't really exist on PCH */
	अणु"EVA",			CNP_PMC_LTR_EVAपूर्ण,
	अणु"SOUTHPORT_C",		CNP_PMC_LTR_SPCपूर्ण,
	अणु"HD_AUDIO",		CNP_PMC_LTR_AZपूर्ण,
	अणु"CNV",			CNP_PMC_LTR_CNVपूर्ण,
	अणु"LPSS",		CNP_PMC_LTR_LPSSपूर्ण,
	अणु"SOUTHPORT_D",		CNP_PMC_LTR_SPDपूर्ण,
	अणु"SOUTHPORT_E",		CNP_PMC_LTR_SPEपूर्ण,
	अणु"CAMERA",		CNP_PMC_LTR_CAMपूर्ण,
	अणु"ESPI",		CNP_PMC_LTR_ESPIपूर्ण,
	अणु"SCC",			CNP_PMC_LTR_SCCपूर्ण,
	अणु"ISH",			CNP_PMC_LTR_ISHपूर्ण,
	अणु"UFSX2",		CNP_PMC_LTR_UFSX2पूर्ण,
	अणु"EMMC",		CNP_PMC_LTR_EMMCपूर्ण,
	/*
	 * Check पूर्णांकel_pmc_core_ids[] users of cnp_reg_map क्रम
	 * a list of core SoCs using this.
	 */
	अणु"WIGIG",		ICL_PMC_LTR_WIGIGपूर्ण,
	अणु"THC0",                TGL_PMC_LTR_THC0पूर्ण,
	अणु"THC1",                TGL_PMC_LTR_THC1पूर्ण,
	/* Below two cannot be used क्रम LTR_IGNORE */
	अणु"CURRENT_PLATFORM",	CNP_PMC_LTR_CUR_PLTपूर्ण,
	अणु"AGGREGATED_SYSTEM",	CNP_PMC_LTR_CUR_ASLTपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pmc_reg_map cnp_reg_map = अणु
	.pfear_sts = ext_cnp_pfear_map,
	.slp_s0_offset = CNP_PMC_SLP_S0_RES_COUNTER_OFFSET,
	.slp_s0_res_counter_step = SPT_PMC_SLP_S0_RES_COUNTER_STEP,
	.slps0_dbg_maps = cnp_slps0_dbg_maps,
	.ltr_show_sts = cnp_ltr_show_map,
	.msr_sts = msr_map,
	.slps0_dbg_offset = CNP_PMC_SLPS0_DBG_OFFSET,
	.ltr_ignore_offset = CNP_PMC_LTR_IGNORE_OFFSET,
	.regmap_length = CNP_PMC_MMIO_REG_LEN,
	.ppfear0_offset = CNP_PMC_HOST_PPFEAR0A,
	.ppfear_buckets = CNP_PPFEAR_NUM_ENTRIES,
	.pm_cfg_offset = CNP_PMC_PM_CFG_OFFSET,
	.pm_पढ़ो_disable_bit = CNP_PMC_READ_DISABLE_BIT,
	.ltr_ignore_max = CNP_NUM_IP_IGN_ALLOWED,
	.etr3_offset = ETR3_OFFSET,
पूर्ण;

अटल स्थिर काष्ठा pmc_reg_map icl_reg_map = अणु
	.pfear_sts = ext_icl_pfear_map,
	.slp_s0_offset = CNP_PMC_SLP_S0_RES_COUNTER_OFFSET,
	.slp_s0_res_counter_step = ICL_PMC_SLP_S0_RES_COUNTER_STEP,
	.slps0_dbg_maps = cnp_slps0_dbg_maps,
	.ltr_show_sts = cnp_ltr_show_map,
	.msr_sts = msr_map,
	.slps0_dbg_offset = CNP_PMC_SLPS0_DBG_OFFSET,
	.ltr_ignore_offset = CNP_PMC_LTR_IGNORE_OFFSET,
	.regmap_length = CNP_PMC_MMIO_REG_LEN,
	.ppfear0_offset = CNP_PMC_HOST_PPFEAR0A,
	.ppfear_buckets = ICL_PPFEAR_NUM_ENTRIES,
	.pm_cfg_offset = CNP_PMC_PM_CFG_OFFSET,
	.pm_पढ़ो_disable_bit = CNP_PMC_READ_DISABLE_BIT,
	.ltr_ignore_max = ICL_NUM_IP_IGN_ALLOWED,
	.etr3_offset = ETR3_OFFSET,
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map tgl_घड़ीsource_status_map[] = अणु
	अणु"USB2PLL_OFF_STS",			BIT(18)पूर्ण,
	अणु"PCIe/USB3.1_Gen2PLL_OFF_STS",		BIT(19)पूर्ण,
	अणु"PCIe_Gen3PLL_OFF_STS",		BIT(20)पूर्ण,
	अणु"OPIOPLL_OFF_STS",			BIT(21)पूर्ण,
	अणु"OCPLL_OFF_STS",			BIT(22)पूर्ण,
	अणु"MainPLL_OFF_STS",			BIT(23)पूर्ण,
	अणु"MIPIPLL_OFF_STS",			BIT(24)पूर्ण,
	अणु"Fast_XTAL_Osc_OFF_STS",		BIT(25)पूर्ण,
	अणु"AC_Ring_Osc_OFF_STS",			BIT(26)पूर्ण,
	अणु"MC_Ring_Osc_OFF_STS",			BIT(27)पूर्ण,
	अणु"SATAPLL_OFF_STS",			BIT(29)पूर्ण,
	अणु"XTAL_USB2PLL_OFF_STS",		BIT(31)पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map tgl_घातer_gating_status_map[] = अणु
	अणु"CSME_PG_STS",				BIT(0)पूर्ण,
	अणु"SATA_PG_STS",				BIT(1)पूर्ण,
	अणु"xHCI_PG_STS",				BIT(2)पूर्ण,
	अणु"UFSX2_PG_STS",			BIT(3)पूर्ण,
	अणु"OTG_PG_STS",				BIT(5)पूर्ण,
	अणु"SPA_PG_STS",				BIT(6)पूर्ण,
	अणु"SPB_PG_STS",				BIT(7)पूर्ण,
	अणु"SPC_PG_STS",				BIT(8)पूर्ण,
	अणु"SPD_PG_STS",				BIT(9)पूर्ण,
	अणु"SPE_PG_STS",				BIT(10)पूर्ण,
	अणु"SPF_PG_STS",				BIT(11)पूर्ण,
	अणु"LSX_PG_STS",				BIT(13)पूर्ण,
	अणु"P2SB_PG_STS",				BIT(14)पूर्ण,
	अणु"PSF_PG_STS",				BIT(15)पूर्ण,
	अणु"SBR_PG_STS",				BIT(16)पूर्ण,
	अणु"OPIDMI_PG_STS",			BIT(17)पूर्ण,
	अणु"THC0_PG_STS",				BIT(18)पूर्ण,
	अणु"THC1_PG_STS",				BIT(19)पूर्ण,
	अणु"GBETSN_PG_STS",			BIT(20)पूर्ण,
	अणु"GBE_PG_STS",				BIT(21)पूर्ण,
	अणु"LPSS_PG_STS",				BIT(22)पूर्ण,
	अणु"MMP_UFSX2_PG_STS",			BIT(23)पूर्ण,
	अणु"MMP_UFSX2B_PG_STS",			BIT(24)पूर्ण,
	अणु"FIA_PG_STS",				BIT(25)पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map tgl_d3_status_map[] = अणु
	अणु"ADSP_D3_STS",				BIT(0)पूर्ण,
	अणु"SATA_D3_STS",				BIT(1)पूर्ण,
	अणु"xHCI0_D3_STS",			BIT(2)पूर्ण,
	अणु"xDCI1_D3_STS",			BIT(5)पूर्ण,
	अणु"SDX_D3_STS",				BIT(6)पूर्ण,
	अणु"EMMC_D3_STS",				BIT(7)पूर्ण,
	अणु"IS_D3_STS",				BIT(8)पूर्ण,
	अणु"THC0_D3_STS",				BIT(9)पूर्ण,
	अणु"THC1_D3_STS",				BIT(10)पूर्ण,
	अणु"GBE_D3_STS",				BIT(11)पूर्ण,
	अणु"GBE_TSN_D3_STS",			BIT(12)पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map tgl_vnn_req_status_map[] = अणु
	अणु"GPIO_COM0_VNN_REQ_STS",		BIT(1)पूर्ण,
	अणु"GPIO_COM1_VNN_REQ_STS",		BIT(2)पूर्ण,
	अणु"GPIO_COM2_VNN_REQ_STS",		BIT(3)पूर्ण,
	अणु"GPIO_COM3_VNN_REQ_STS",		BIT(4)पूर्ण,
	अणु"GPIO_COM4_VNN_REQ_STS",		BIT(5)पूर्ण,
	अणु"GPIO_COM5_VNN_REQ_STS",		BIT(6)पूर्ण,
	अणु"Audio_VNN_REQ_STS",			BIT(7)पूर्ण,
	अणु"ISH_VNN_REQ_STS",			BIT(8)पूर्ण,
	अणु"CNVI_VNN_REQ_STS",			BIT(9)पूर्ण,
	अणु"eSPI_VNN_REQ_STS",			BIT(10)पूर्ण,
	अणु"Display_VNN_REQ_STS",			BIT(11)पूर्ण,
	अणु"DTS_VNN_REQ_STS",			BIT(12)पूर्ण,
	अणु"SMBUS_VNN_REQ_STS",			BIT(14)पूर्ण,
	अणु"CSME_VNN_REQ_STS",			BIT(15)पूर्ण,
	अणु"SMLINK0_VNN_REQ_STS",			BIT(16)पूर्ण,
	अणु"SMLINK1_VNN_REQ_STS",			BIT(17)पूर्ण,
	अणु"CLINK_VNN_REQ_STS",			BIT(20)पूर्ण,
	अणु"DCI_VNN_REQ_STS",			BIT(21)पूर्ण,
	अणु"ITH_VNN_REQ_STS",			BIT(22)पूर्ण,
	अणु"CSME_VNN_REQ_STS",			BIT(24)पूर्ण,
	अणु"GBE_VNN_REQ_STS",			BIT(25)पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map tgl_vnn_misc_status_map[] = अणु
	अणु"CPU_C10_REQ_STS_0",			BIT(0)पूर्ण,
	अणु"PCIe_LPM_En_REQ_STS_3",		BIT(3)पूर्ण,
	अणु"ITH_REQ_STS_5",			BIT(5)पूर्ण,
	अणु"CNVI_REQ_STS_6",			BIT(6)पूर्ण,
	अणु"ISH_REQ_STS_7",			BIT(7)पूर्ण,
	अणु"USB2_SUS_PG_Sys_REQ_STS_10",		BIT(10)पूर्ण,
	अणु"PCIe_Clk_REQ_STS_12",			BIT(12)पूर्ण,
	अणु"MPHY_Core_DL_REQ_STS_16",		BIT(16)पूर्ण,
	अणु"Break-even_En_REQ_STS_17",		BIT(17)पूर्ण,
	अणु"Auto-demo_En_REQ_STS_18",		BIT(18)पूर्ण,
	अणु"MPHY_SUS_REQ_STS_22",			BIT(22)पूर्ण,
	अणु"xDCI_attached_REQ_STS_24",		BIT(24)पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map tgl_संकेत_status_map[] = अणु
	अणु"LSX_Wake0_En_STS",			BIT(0)पूर्ण,
	अणु"LSX_Wake0_Pol_STS",			BIT(1)पूर्ण,
	अणु"LSX_Wake1_En_STS",			BIT(2)पूर्ण,
	अणु"LSX_Wake1_Pol_STS",			BIT(3)पूर्ण,
	अणु"LSX_Wake2_En_STS",			BIT(4)पूर्ण,
	अणु"LSX_Wake2_Pol_STS",			BIT(5)पूर्ण,
	अणु"LSX_Wake3_En_STS",			BIT(6)पूर्ण,
	अणु"LSX_Wake3_Pol_STS",			BIT(7)पूर्ण,
	अणु"LSX_Wake4_En_STS",			BIT(8)पूर्ण,
	अणु"LSX_Wake4_Pol_STS",			BIT(9)पूर्ण,
	अणु"LSX_Wake5_En_STS",			BIT(10)पूर्ण,
	अणु"LSX_Wake5_Pol_STS",			BIT(11)पूर्ण,
	अणु"LSX_Wake6_En_STS",			BIT(12)पूर्ण,
	अणु"LSX_Wake6_Pol_STS",			BIT(13)पूर्ण,
	अणु"LSX_Wake7_En_STS",			BIT(14)पूर्ण,
	अणु"LSX_Wake7_Pol_STS",			BIT(15)पूर्ण,
	अणु"Intel_Se_IO_Wake0_En_STS",		BIT(16)पूर्ण,
	अणु"Intel_Se_IO_Wake0_Pol_STS",		BIT(17)पूर्ण,
	अणु"Intel_Se_IO_Wake1_En_STS",		BIT(18)पूर्ण,
	अणु"Intel_Se_IO_Wake1_Pol_STS",		BIT(19)पूर्ण,
	अणु"Int_Timer_SS_Wake0_En_STS",		BIT(20)पूर्ण,
	अणु"Int_Timer_SS_Wake0_Pol_STS",		BIT(21)पूर्ण,
	अणु"Int_Timer_SS_Wake1_En_STS",		BIT(22)पूर्ण,
	अणु"Int_Timer_SS_Wake1_Pol_STS",		BIT(23)पूर्ण,
	अणु"Int_Timer_SS_Wake2_En_STS",		BIT(24)पूर्ण,
	अणु"Int_Timer_SS_Wake2_Pol_STS",		BIT(25)पूर्ण,
	अणु"Int_Timer_SS_Wake3_En_STS",		BIT(26)पूर्ण,
	अणु"Int_Timer_SS_Wake3_Pol_STS",		BIT(27)पूर्ण,
	अणु"Int_Timer_SS_Wake4_En_STS",		BIT(28)पूर्ण,
	अणु"Int_Timer_SS_Wake4_Pol_STS",		BIT(29)पूर्ण,
	अणु"Int_Timer_SS_Wake5_En_STS",		BIT(30)पूर्ण,
	अणु"Int_Timer_SS_Wake5_Pol_STS",		BIT(31)पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map *tgl_lpm_maps[] = अणु
	tgl_घड़ीsource_status_map,
	tgl_घातer_gating_status_map,
	tgl_d3_status_map,
	tgl_vnn_req_status_map,
	tgl_vnn_misc_status_map,
	tgl_संकेत_status_map,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा pmc_reg_map tgl_reg_map = अणु
	.pfear_sts = ext_tgl_pfear_map,
	.slp_s0_offset = CNP_PMC_SLP_S0_RES_COUNTER_OFFSET,
	.slp_s0_res_counter_step = TGL_PMC_SLP_S0_RES_COUNTER_STEP,
	.ltr_show_sts = cnp_ltr_show_map,
	.msr_sts = msr_map,
	.ltr_ignore_offset = CNP_PMC_LTR_IGNORE_OFFSET,
	.regmap_length = CNP_PMC_MMIO_REG_LEN,
	.ppfear0_offset = CNP_PMC_HOST_PPFEAR0A,
	.ppfear_buckets = ICL_PPFEAR_NUM_ENTRIES,
	.pm_cfg_offset = CNP_PMC_PM_CFG_OFFSET,
	.pm_पढ़ो_disable_bit = CNP_PMC_READ_DISABLE_BIT,
	.ltr_ignore_max = TGL_NUM_IP_IGN_ALLOWED,
	.lpm_num_maps = TGL_LPM_NUM_MAPS,
	.lpm_res_counter_step_x2 = TGL_PMC_LPM_RES_COUNTER_STEP_X2,
	.lpm_sts_latch_en_offset = TGL_LPM_STS_LATCH_EN_OFFSET,
	.lpm_en_offset = TGL_LPM_EN_OFFSET,
	.lpm_priority_offset = TGL_LPM_PRI_OFFSET,
	.lpm_residency_offset = TGL_LPM_RESIDENCY_OFFSET,
	.lpm_sts = tgl_lpm_maps,
	.lpm_status_offset = TGL_LPM_STATUS_OFFSET,
	.lpm_live_status_offset = TGL_LPM_LIVE_STATUS_OFFSET,
	.etr3_offset = ETR3_OFFSET,
पूर्ण;

अटल व्योम pmc_core_get_tgl_lpm_reqs(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pmc_dev *pmcdev = platक्रमm_get_drvdata(pdev);
	स्थिर पूर्णांक num_maps = pmcdev->map->lpm_num_maps;
	u32 lpm_size = LPM_MAX_NUM_MODES * num_maps * 4;
	जोड़ acpi_object *out_obj;
	काष्ठा acpi_device *adev;
	guid_t s0ix_dsm_guid;
	u32 *lpm_req_regs, *addr;

	adev = ACPI_COMPANION(&pdev->dev);
	अगर (!adev)
		वापस;

	guid_parse(ACPI_S0IX_DSM_UUID, &s0ix_dsm_guid);

	out_obj = acpi_evaluate_dsm(adev->handle, &s0ix_dsm_guid, 0,
				    ACPI_GET_LOW_MODE_REGISTERS, शून्य);
	अगर (out_obj && out_obj->type == ACPI_TYPE_BUFFER) अणु
		u32 size = out_obj->buffer.length;

		अगर (size != lpm_size) अणु
			acpi_handle_debug(adev->handle,
				"_DSM returned unexpected buffer size, have %u, expect %u\n",
				size, lpm_size);
			जाओ मुक्त_acpi_obj;
		पूर्ण
	पूर्ण अन्यथा अणु
		acpi_handle_debug(adev->handle,
				  "_DSM function 0 evaluation failed\n");
		जाओ मुक्त_acpi_obj;
	पूर्ण

	addr = (u32 *)out_obj->buffer.poपूर्णांकer;

	lpm_req_regs = devm_kzalloc(&pdev->dev, lpm_size * माप(u32),
				     GFP_KERNEL);
	अगर (!lpm_req_regs)
		जाओ मुक्त_acpi_obj;

	स_नकल(lpm_req_regs, addr, lpm_size);
	pmcdev->lpm_req_regs = lpm_req_regs;

मुक्त_acpi_obj:
	ACPI_FREE(out_obj);
पूर्ण

अटल अंतरभूत u32 pmc_core_reg_पढ़ो(काष्ठा pmc_dev *pmcdev, पूर्णांक reg_offset)
अणु
	वापस पढ़ोl(pmcdev->regbase + reg_offset);
पूर्ण

अटल अंतरभूत व्योम pmc_core_reg_ग_लिखो(काष्ठा pmc_dev *pmcdev, पूर्णांक reg_offset,
				      u32 val)
अणु
	ग_लिखोl(val, pmcdev->regbase + reg_offset);
पूर्ण

अटल अंतरभूत u64 pmc_core_adjust_slp_s0_step(काष्ठा pmc_dev *pmcdev, u32 value)
अणु
	वापस (u64)value * pmcdev->map->slp_s0_res_counter_step;
पूर्ण

अटल पूर्णांक set_etr3(काष्ठा pmc_dev *pmcdev)
अणु
	स्थिर काष्ठा pmc_reg_map *map = pmcdev->map;
	u32 reg;
	पूर्णांक err;

	अगर (!map->etr3_offset)
		वापस -EOPNOTSUPP;

	mutex_lock(&pmcdev->lock);

	/* check अगर CF9 is locked */
	reg = pmc_core_reg_पढ़ो(pmcdev, map->etr3_offset);
	अगर (reg & ETR3_CF9LOCK) अणु
		err = -EACCES;
		जाओ out_unlock;
	पूर्ण

	/* ग_लिखो CF9 global reset bit */
	reg |= ETR3_CF9GR;
	pmc_core_reg_ग_लिखो(pmcdev, map->etr3_offset, reg);

	reg = pmc_core_reg_पढ़ो(pmcdev, map->etr3_offset);
	अगर (!(reg & ETR3_CF9GR)) अणु
		err = -EIO;
		जाओ out_unlock;
	पूर्ण

	err = 0;

out_unlock:
	mutex_unlock(&pmcdev->lock);
	वापस err;
पूर्ण
अटल umode_t etr3_is_visible(काष्ठा kobject *kobj,
				काष्ठा attribute *attr,
				पूर्णांक idx)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा pmc_dev *pmcdev = dev_get_drvdata(dev);
	स्थिर काष्ठा pmc_reg_map *map = pmcdev->map;
	u32 reg;

	mutex_lock(&pmcdev->lock);
	reg = pmc_core_reg_पढ़ो(pmcdev, map->etr3_offset);
	mutex_unlock(&pmcdev->lock);

	वापस reg & ETR3_CF9LOCK ? attr->mode & (SYSFS_PREALLOC | 0444) : attr->mode;
पूर्ण

अटल sमाप_प्रकार etr3_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pmc_dev *pmcdev = dev_get_drvdata(dev);
	स्थिर काष्ठा pmc_reg_map *map = pmcdev->map;
	u32 reg;

	अगर (!map->etr3_offset)
		वापस -EOPNOTSUPP;

	mutex_lock(&pmcdev->lock);

	reg = pmc_core_reg_पढ़ो(pmcdev, map->etr3_offset);
	reg &= ETR3_CF9GR | ETR3_CF9LOCK;

	mutex_unlock(&pmcdev->lock);

	वापस sysfs_emit(buf, "0x%08x", reg);
पूर्ण

अटल sमाप_प्रकार etr3_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा pmc_dev *pmcdev = dev_get_drvdata(dev);
	पूर्णांक err;
	u32 reg;

	err = kstrtouपूर्णांक(buf, 16, &reg);
	अगर (err)
		वापस err;

	/* allow only CF9 ग_लिखोs */
	अगर (reg != ETR3_CF9GR)
		वापस -EINVAL;

	err = set_etr3(pmcdev);
	अगर (err)
		वापस err;

	वापस len;
पूर्ण
अटल DEVICE_ATTR_RW(etr3);

अटल काष्ठा attribute *pmc_attrs[] = अणु
	&dev_attr_etr3.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group pmc_attr_group = अणु
	.attrs = pmc_attrs,
	.is_visible = etr3_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *pmc_dev_groups[] = अणु
	&pmc_attr_group,
	शून्य
पूर्ण;

अटल पूर्णांक pmc_core_dev_state_get(व्योम *data, u64 *val)
अणु
	काष्ठा pmc_dev *pmcdev = data;
	स्थिर काष्ठा pmc_reg_map *map = pmcdev->map;
	u32 value;

	value = pmc_core_reg_पढ़ो(pmcdev, map->slp_s0_offset);
	*val = pmc_core_adjust_slp_s0_step(pmcdev, value);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(pmc_core_dev_state, pmc_core_dev_state_get, शून्य, "%llu\n");

अटल पूर्णांक pmc_core_check_पढ़ो_lock_bit(काष्ठा pmc_dev *pmcdev)
अणु
	u32 value;

	value = pmc_core_reg_पढ़ो(pmcdev, pmcdev->map->pm_cfg_offset);
	वापस value & BIT(pmcdev->map->pm_पढ़ो_disable_bit);
पूर्ण

अटल व्योम pmc_core_slps0_display(काष्ठा pmc_dev *pmcdev, काष्ठा device *dev,
				   काष्ठा seq_file *s)
अणु
	स्थिर काष्ठा pmc_bit_map **maps = pmcdev->map->slps0_dbg_maps;
	स्थिर काष्ठा pmc_bit_map *map;
	पूर्णांक offset = pmcdev->map->slps0_dbg_offset;
	u32 data;

	जबतक (*maps) अणु
		map = *maps;
		data = pmc_core_reg_पढ़ो(pmcdev, offset);
		offset += 4;
		जबतक (map->name) अणु
			अगर (dev)
				dev_info(dev, "SLP_S0_DBG: %-32s\tState: %s\n",
					map->name,
					data & map->bit_mask ? "Yes" : "No");
			अगर (s)
				seq_म_लिखो(s, "SLP_S0_DBG: %-32s\tState: %s\n",
					   map->name,
					   data & map->bit_mask ? "Yes" : "No");
			++map;
		पूर्ण
		++maps;
	पूर्ण
पूर्ण

अटल पूर्णांक pmc_core_lpm_get_arr_size(स्थिर काष्ठा pmc_bit_map **maps)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; maps[idx]; idx++)
		;/* Nothing */

	वापस idx;
पूर्ण

अटल व्योम pmc_core_lpm_display(काष्ठा pmc_dev *pmcdev, काष्ठा device *dev,
				 काष्ठा seq_file *s, u32 offset,
				 स्थिर अक्षर *str,
				 स्थिर काष्ठा pmc_bit_map **maps)
अणु
	पूर्णांक index, idx, len = 32, bit_mask, arr_size;
	u32 *lpm_regs;

	arr_size = pmc_core_lpm_get_arr_size(maps);
	lpm_regs = kदो_स्मृति_array(arr_size, माप(*lpm_regs), GFP_KERNEL);
	अगर (!lpm_regs)
		वापस;

	क्रम (index = 0; index < arr_size; index++) अणु
		lpm_regs[index] = pmc_core_reg_पढ़ो(pmcdev, offset);
		offset += 4;
	पूर्ण

	क्रम (idx = 0; idx < arr_size; idx++) अणु
		अगर (dev)
			dev_info(dev, "\nLPM_%s_%d:\t0x%x\n", str, idx,
				lpm_regs[idx]);
		अगर (s)
			seq_म_लिखो(s, "\nLPM_%s_%d:\t0x%x\n", str, idx,
				   lpm_regs[idx]);
		क्रम (index = 0; maps[idx][index].name && index < len; index++) अणु
			bit_mask = maps[idx][index].bit_mask;
			अगर (dev)
				dev_info(dev, "%-30s %-30d\n",
					maps[idx][index].name,
					lpm_regs[idx] & bit_mask ? 1 : 0);
			अगर (s)
				seq_म_लिखो(s, "%-30s %-30d\n",
					   maps[idx][index].name,
					   lpm_regs[idx] & bit_mask ? 1 : 0);
		पूर्ण
	पूर्ण

	kमुक्त(lpm_regs);
पूर्ण

अटल bool slps0_dbg_latch;

अटल अंतरभूत u8 pmc_core_reg_पढ़ो_byte(काष्ठा pmc_dev *pmcdev, पूर्णांक offset)
अणु
	वापस पढ़ोb(pmcdev->regbase + offset);
पूर्ण

अटल व्योम pmc_core_display_map(काष्ठा seq_file *s, पूर्णांक index, पूर्णांक idx, पूर्णांक ip,
				 u8 pf_reg, स्थिर काष्ठा pmc_bit_map **pf_map)
अणु
	seq_म_लिखो(s, "PCH IP: %-2d - %-32s\tState: %s\n",
		   ip, pf_map[idx][index].name,
		   pf_map[idx][index].bit_mask & pf_reg ? "Off" : "On");
पूर्ण

अटल पूर्णांक pmc_core_ppfear_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा pmc_dev *pmcdev = s->निजी;
	स्थिर काष्ठा pmc_bit_map **maps = pmcdev->map->pfear_sts;
	u8 pf_regs[PPFEAR_MAX_NUM_ENTRIES];
	पूर्णांक index, iter, idx, ip = 0;

	iter = pmcdev->map->ppfear0_offset;

	क्रम (index = 0; index < pmcdev->map->ppfear_buckets &&
	     index < PPFEAR_MAX_NUM_ENTRIES; index++, iter++)
		pf_regs[index] = pmc_core_reg_पढ़ो_byte(pmcdev, iter);

	क्रम (idx = 0; maps[idx]; idx++) अणु
		क्रम (index = 0; maps[idx][index].name &&
		     index < pmcdev->map->ppfear_buckets * 8; ip++, index++)
			pmc_core_display_map(s, index, idx, ip,
					     pf_regs[index / 8], maps);
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(pmc_core_ppfear);

/* This function should वापस link status, 0 means पढ़ोy */
अटल पूर्णांक pmc_core_mtpmc_link_status(काष्ठा pmc_dev *pmcdev)
अणु
	u32 value;

	value = pmc_core_reg_पढ़ो(pmcdev, SPT_PMC_PM_STS_OFFSET);
	वापस value & BIT(SPT_PMC_MSG_FULL_STS_BIT);
पूर्ण

अटल पूर्णांक pmc_core_send_msg(काष्ठा pmc_dev *pmcdev, u32 *addr_xram)
अणु
	u32 dest;
	पूर्णांक समयout;

	क्रम (समयout = NUM_RETRIES; समयout > 0; समयout--) अणु
		अगर (pmc_core_mtpmc_link_status(pmcdev) == 0)
			अवरोध;
		msleep(5);
	पूर्ण

	अगर (समयout <= 0 && pmc_core_mtpmc_link_status(pmcdev))
		वापस -EBUSY;

	dest = (*addr_xram & MTPMC_MASK) | (1U << 1);
	pmc_core_reg_ग_लिखो(pmcdev, SPT_PMC_MTPMC_OFFSET, dest);
	वापस 0;
पूर्ण

अटल पूर्णांक pmc_core_mphy_pg_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा pmc_dev *pmcdev = s->निजी;
	स्थिर काष्ठा pmc_bit_map *map = pmcdev->map->mphy_sts;
	u32 mphy_core_reg_low, mphy_core_reg_high;
	u32 val_low, val_high;
	पूर्णांक index, err = 0;

	अगर (pmcdev->pmc_xram_पढ़ो_bit) अणु
		seq_माला_दो(s, "Access denied: please disable PMC_READ_DISABLE setting in BIOS.");
		वापस 0;
	पूर्ण

	mphy_core_reg_low  = (SPT_PMC_MPHY_CORE_STS_0 << 16);
	mphy_core_reg_high = (SPT_PMC_MPHY_CORE_STS_1 << 16);

	mutex_lock(&pmcdev->lock);

	अगर (pmc_core_send_msg(pmcdev, &mphy_core_reg_low) != 0) अणु
		err = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	msleep(10);
	val_low = pmc_core_reg_पढ़ो(pmcdev, SPT_PMC_MFPMC_OFFSET);

	अगर (pmc_core_send_msg(pmcdev, &mphy_core_reg_high) != 0) अणु
		err = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	msleep(10);
	val_high = pmc_core_reg_पढ़ो(pmcdev, SPT_PMC_MFPMC_OFFSET);

	क्रम (index = 0; index < 8 && map[index].name; index++) अणु
		seq_म_लिखो(s, "%-32s\tState: %s\n",
			   map[index].name,
			   map[index].bit_mask & val_low ? "Not power gated" :
			   "Power gated");
	पूर्ण

	क्रम (index = 8; map[index].name; index++) अणु
		seq_म_लिखो(s, "%-32s\tState: %s\n",
			   map[index].name,
			   map[index].bit_mask & val_high ? "Not power gated" :
			   "Power gated");
	पूर्ण

out_unlock:
	mutex_unlock(&pmcdev->lock);
	वापस err;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(pmc_core_mphy_pg);

अटल पूर्णांक pmc_core_pll_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा pmc_dev *pmcdev = s->निजी;
	स्थिर काष्ठा pmc_bit_map *map = pmcdev->map->pll_sts;
	u32 mphy_common_reg, val;
	पूर्णांक index, err = 0;

	अगर (pmcdev->pmc_xram_पढ़ो_bit) अणु
		seq_माला_दो(s, "Access denied: please disable PMC_READ_DISABLE setting in BIOS.");
		वापस 0;
	पूर्ण

	mphy_common_reg  = (SPT_PMC_MPHY_COM_STS_0 << 16);
	mutex_lock(&pmcdev->lock);

	अगर (pmc_core_send_msg(pmcdev, &mphy_common_reg) != 0) अणु
		err = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	/* Observed PMC HW response latency क्रम MTPMC-MFPMC is ~10 ms */
	msleep(10);
	val = pmc_core_reg_पढ़ो(pmcdev, SPT_PMC_MFPMC_OFFSET);

	क्रम (index = 0; map[index].name ; index++) अणु
		seq_म_लिखो(s, "%-32s\tState: %s\n",
			   map[index].name,
			   map[index].bit_mask & val ? "Active" : "Idle");
	पूर्ण

out_unlock:
	mutex_unlock(&pmcdev->lock);
	वापस err;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(pmc_core_pll);

अटल पूर्णांक pmc_core_send_ltr_ignore(काष्ठा pmc_dev *pmcdev, u32 value)
अणु
	स्थिर काष्ठा pmc_reg_map *map = pmcdev->map;
	u32 reg;
	पूर्णांक err = 0;

	mutex_lock(&pmcdev->lock);

	अगर (value > map->ltr_ignore_max) अणु
		err = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	reg = pmc_core_reg_पढ़ो(pmcdev, map->ltr_ignore_offset);
	reg |= BIT(value);
	pmc_core_reg_ग_लिखो(pmcdev, map->ltr_ignore_offset, reg);

out_unlock:
	mutex_unlock(&pmcdev->lock);

	वापस err;
पूर्ण

अटल sमाप_प्रकार pmc_core_ltr_ignore_ग_लिखो(काष्ठा file *file,
					 स्थिर अक्षर __user *userbuf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *s = file->निजी_data;
	काष्ठा pmc_dev *pmcdev = s->निजी;
	u32 buf_size, value;
	पूर्णांक err;

	buf_size = min_t(u32, count, 64);

	err = kstrtou32_from_user(userbuf, buf_size, 10, &value);
	अगर (err)
		वापस err;

	err = pmc_core_send_ltr_ignore(pmcdev, value);

	वापस err == 0 ? count : err;
पूर्ण

अटल पूर्णांक pmc_core_ltr_ignore_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक pmc_core_ltr_ignore_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, pmc_core_ltr_ignore_show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations pmc_core_ltr_ignore_ops = अणु
	.खोलो           = pmc_core_ltr_ignore_खोलो,
	.पढ़ो           = seq_पढ़ो,
	.ग_लिखो          = pmc_core_ltr_ignore_ग_लिखो,
	.llseek         = seq_lseek,
	.release        = single_release,
पूर्ण;

अटल व्योम pmc_core_slps0_dbg_latch(काष्ठा pmc_dev *pmcdev, bool reset)
अणु
	स्थिर काष्ठा pmc_reg_map *map = pmcdev->map;
	u32 fd;

	mutex_lock(&pmcdev->lock);

	अगर (!reset && !slps0_dbg_latch)
		जाओ out_unlock;

	fd = pmc_core_reg_पढ़ो(pmcdev, map->slps0_dbg_offset);
	अगर (reset)
		fd &= ~CNP_PMC_LATCH_SLPS0_EVENTS;
	अन्यथा
		fd |= CNP_PMC_LATCH_SLPS0_EVENTS;
	pmc_core_reg_ग_लिखो(pmcdev, map->slps0_dbg_offset, fd);

	slps0_dbg_latch = false;

out_unlock:
	mutex_unlock(&pmcdev->lock);
पूर्ण

अटल पूर्णांक pmc_core_slps0_dbg_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा pmc_dev *pmcdev = s->निजी;

	pmc_core_slps0_dbg_latch(pmcdev, false);
	pmc_core_slps0_display(pmcdev, शून्य, s);
	pmc_core_slps0_dbg_latch(pmcdev, true);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(pmc_core_slps0_dbg);

अटल u32 convert_ltr_scale(u32 val)
अणु
	/*
	 * As per PCIE specअगरication supporting करोcument
	 * ECN_LatencyTolnReporting_14Aug08.pdf the Latency
	 * Tolerance Reporting data payload is encoded in a
	 * 3 bit scale and 10 bit value fields. Values are
	 * multiplied by the indicated scale to yield an असलolute समय
	 * value, expressible in a range from 1 nanosecond to
	 * 2^25*(2^10-1) = 34,326,183,936 nanoseconds.
	 *
	 * scale encoding is as follows:
	 *
	 * ----------------------------------------------
	 * |scale factor	|	Multiplier (ns)	|
	 * ----------------------------------------------
	 * |	0		|	1		|
	 * |	1		|	32		|
	 * |	2		|	1024		|
	 * |	3		|	32768		|
	 * |	4		|	1048576		|
	 * |	5		|	33554432	|
	 * |	6		|	Invalid		|
	 * |	7		|	Invalid		|
	 * ----------------------------------------------
	 */
	अगर (val > 5) अणु
		pr_warn("Invalid LTR scale factor.\n");
		वापस 0;
	पूर्ण

	वापस 1U << (5 * val);
पूर्ण

अटल पूर्णांक pmc_core_ltr_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा pmc_dev *pmcdev = s->निजी;
	स्थिर काष्ठा pmc_bit_map *map = pmcdev->map->ltr_show_sts;
	u64 decoded_snoop_ltr, decoded_non_snoop_ltr;
	u32 ltr_raw_data, scale, val;
	u16 snoop_ltr, nonsnoop_ltr;
	पूर्णांक index;

	क्रम (index = 0; map[index].name ; index++) अणु
		decoded_snoop_ltr = decoded_non_snoop_ltr = 0;
		ltr_raw_data = pmc_core_reg_पढ़ो(pmcdev,
						 map[index].bit_mask);
		snoop_ltr = ltr_raw_data & ~MTPMC_MASK;
		nonsnoop_ltr = (ltr_raw_data >> 0x10) & ~MTPMC_MASK;

		अगर (FIELD_GET(LTR_REQ_NONSNOOP, ltr_raw_data)) अणु
			scale = FIELD_GET(LTR_DECODED_SCALE, nonsnoop_ltr);
			val = FIELD_GET(LTR_DECODED_VAL, nonsnoop_ltr);
			decoded_non_snoop_ltr = val * convert_ltr_scale(scale);
		पूर्ण

		अगर (FIELD_GET(LTR_REQ_SNOOP, ltr_raw_data)) अणु
			scale = FIELD_GET(LTR_DECODED_SCALE, snoop_ltr);
			val = FIELD_GET(LTR_DECODED_VAL, snoop_ltr);
			decoded_snoop_ltr = val * convert_ltr_scale(scale);
		पूर्ण

		seq_म_लिखो(s, "%-32s\tLTR: RAW: 0x%-16x\tNon-Snoop(ns): %-16llu\tSnoop(ns): %-16llu\n",
			   map[index].name, ltr_raw_data,
			   decoded_non_snoop_ltr,
			   decoded_snoop_ltr);
	पूर्ण
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(pmc_core_ltr);

अटल अंतरभूत u64 adjust_lpm_residency(काष्ठा pmc_dev *pmcdev, u32 offset,
				       स्थिर पूर्णांक lpm_adj_x2)
अणु
	u64 lpm_res = pmc_core_reg_पढ़ो(pmcdev, offset);

	वापस GET_X2_COUNTER((u64)lpm_adj_x2 * lpm_res);
पूर्ण

अटल पूर्णांक pmc_core_substate_res_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा pmc_dev *pmcdev = s->निजी;
	स्थिर पूर्णांक lpm_adj_x2 = pmcdev->map->lpm_res_counter_step_x2;
	u32 offset = pmcdev->map->lpm_residency_offset;
	पूर्णांक i, mode;

	seq_म_लिखो(s, "%-10s %-15s\n", "Substate", "Residency");

	pmc_क्रम_each_mode(i, mode, pmcdev) अणु
		seq_म_लिखो(s, "%-10s %-15llu\n", pmc_lpm_modes[mode],
			   adjust_lpm_residency(pmcdev, offset + (4 * mode), lpm_adj_x2));
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(pmc_core_substate_res);

अटल पूर्णांक pmc_core_substate_sts_regs_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा pmc_dev *pmcdev = s->निजी;
	स्थिर काष्ठा pmc_bit_map **maps = pmcdev->map->lpm_sts;
	u32 offset = pmcdev->map->lpm_status_offset;

	pmc_core_lpm_display(pmcdev, शून्य, s, offset, "STATUS", maps);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(pmc_core_substate_sts_regs);

अटल पूर्णांक pmc_core_substate_l_sts_regs_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा pmc_dev *pmcdev = s->निजी;
	स्थिर काष्ठा pmc_bit_map **maps = pmcdev->map->lpm_sts;
	u32 offset = pmcdev->map->lpm_live_status_offset;

	pmc_core_lpm_display(pmcdev, शून्य, s, offset, "LIVE_STATUS", maps);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(pmc_core_substate_l_sts_regs);

अटल व्योम pmc_core_substate_req_header_show(काष्ठा seq_file *s)
अणु
	काष्ठा pmc_dev *pmcdev = s->निजी;
	पूर्णांक i, mode;

	seq_म_लिखो(s, "%30s |", "Element");
	pmc_क्रम_each_mode(i, mode, pmcdev)
		seq_म_लिखो(s, " %9s |", pmc_lpm_modes[mode]);

	seq_म_लिखो(s, " %9s |\n", "Status");
पूर्ण

अटल पूर्णांक pmc_core_substate_req_regs_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा pmc_dev *pmcdev = s->निजी;
	स्थिर काष्ठा pmc_bit_map **maps = pmcdev->map->lpm_sts;
	स्थिर काष्ठा pmc_bit_map *map;
	स्थिर पूर्णांक num_maps = pmcdev->map->lpm_num_maps;
	u32 sts_offset = pmcdev->map->lpm_status_offset;
	u32 *lpm_req_regs = pmcdev->lpm_req_regs;
	पूर्णांक mp;

	/* Display the header */
	pmc_core_substate_req_header_show(s);

	/* Loop over maps */
	क्रम (mp = 0; mp < num_maps; mp++) अणु
		u32 req_mask = 0;
		u32 lpm_status;
		पूर्णांक mode, idx, i, len = 32;

		/*
		 * Capture the requirements and create a mask so that we only
		 * show an element अगर it's required क्रम at least one of the
		 * enabled low घातer modes
		 */
		pmc_क्रम_each_mode(idx, mode, pmcdev)
			req_mask |= lpm_req_regs[mp + (mode * num_maps)];

		/* Get the last latched status क्रम this map */
		lpm_status = pmc_core_reg_पढ़ो(pmcdev, sts_offset + (mp * 4));

		/*  Loop over elements in this map */
		map = maps[mp];
		क्रम (i = 0; map[i].name && i < len; i++) अणु
			u32 bit_mask = map[i].bit_mask;

			अगर (!(bit_mask & req_mask))
				/*
				 * Not required क्रम any enabled states
				 * so करोn't display
				 */
				जारी;

			/* Display the element name in the first column */
			seq_म_लिखो(s, "%30s |", map[i].name);

			/* Loop over the enabled states and display अगर required */
			pmc_क्रम_each_mode(idx, mode, pmcdev) अणु
				अगर (lpm_req_regs[mp + (mode * num_maps)] & bit_mask)
					seq_म_लिखो(s, " %9s |",
						   "Required");
				अन्यथा
					seq_म_लिखो(s, " %9s |", " ");
			पूर्ण

			/* In Status column, show the last captured state of this agent */
			अगर (lpm_status & bit_mask)
				seq_म_लिखो(s, " %9s |", "Yes");
			अन्यथा
				seq_म_लिखो(s, " %9s |", " ");

			seq_माला_दो(s, "\n");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(pmc_core_substate_req_regs);

अटल पूर्णांक pmc_core_lpm_latch_mode_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा pmc_dev *pmcdev = s->निजी;
	bool c10;
	u32 reg;
	पूर्णांक idx, mode;

	reg = pmc_core_reg_पढ़ो(pmcdev, pmcdev->map->lpm_sts_latch_en_offset);
	अगर (reg & LPM_STS_LATCH_MODE) अणु
		seq_माला_दो(s, "c10");
		c10 = false;
	पूर्ण अन्यथा अणु
		seq_माला_दो(s, "[c10]");
		c10 = true;
	पूर्ण

	pmc_क्रम_each_mode(idx, mode, pmcdev) अणु
		अगर ((BIT(mode) & reg) && !c10)
			seq_म_लिखो(s, " [%s]", pmc_lpm_modes[mode]);
		अन्यथा
			seq_म_लिखो(s, " %s", pmc_lpm_modes[mode]);
	पूर्ण

	seq_माला_दो(s, " clear\n");

	वापस 0;
पूर्ण

अटल sमाप_प्रकार pmc_core_lpm_latch_mode_ग_लिखो(काष्ठा file *file,
					     स्थिर अक्षर __user *userbuf,
					     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *s = file->निजी_data;
	काष्ठा pmc_dev *pmcdev = s->निजी;
	bool clear = false, c10 = false;
	अचिन्हित अक्षर buf[8];
	पूर्णांक idx, m, mode;
	u32 reg;

	अगर (count > माप(buf) - 1)
		वापस -EINVAL;
	अगर (copy_from_user(buf, userbuf, count))
		वापस -EFAULT;
	buf[count] = '\0';

	/*
	 * Allowed strings are:
	 *	Any enabled substate, e.g. 'S0i2.0'
	 *	'c10'
	 *	'clear'
	 */
	mode = sysfs_match_string(pmc_lpm_modes, buf);

	/* Check string matches enabled mode */
	pmc_क्रम_each_mode(idx, m, pmcdev)
		अगर (mode == m)
			अवरोध;

	अगर (mode != m || mode < 0) अणु
		अगर (sysfs_streq(buf, "clear"))
			clear = true;
		अन्यथा अगर (sysfs_streq(buf, "c10"))
			c10 = true;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	अगर (clear) अणु
		mutex_lock(&pmcdev->lock);

		reg = pmc_core_reg_पढ़ो(pmcdev, pmcdev->map->etr3_offset);
		reg |= ETR3_CLEAR_LPM_EVENTS;
		pmc_core_reg_ग_लिखो(pmcdev, pmcdev->map->etr3_offset, reg);

		mutex_unlock(&pmcdev->lock);

		वापस count;
	पूर्ण

	अगर (c10) अणु
		mutex_lock(&pmcdev->lock);

		reg = pmc_core_reg_पढ़ो(pmcdev, pmcdev->map->lpm_sts_latch_en_offset);
		reg &= ~LPM_STS_LATCH_MODE;
		pmc_core_reg_ग_लिखो(pmcdev, pmcdev->map->lpm_sts_latch_en_offset, reg);

		mutex_unlock(&pmcdev->lock);

		वापस count;
	पूर्ण

	/*
	 * For LPM mode latching we set the latch enable bit and selected mode
	 * and clear everything अन्यथा.
	 */
	reg = LPM_STS_LATCH_MODE | BIT(mode);
	mutex_lock(&pmcdev->lock);
	pmc_core_reg_ग_लिखो(pmcdev, pmcdev->map->lpm_sts_latch_en_offset, reg);
	mutex_unlock(&pmcdev->lock);

	वापस count;
पूर्ण
DEFINE_PMC_CORE_ATTR_WRITE(pmc_core_lpm_latch_mode);

अटल पूर्णांक pmc_core_pkgc_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा pmc_dev *pmcdev = s->निजी;
	स्थिर काष्ठा pmc_bit_map *map = pmcdev->map->msr_sts;
	u64 pcstate_count;
	पूर्णांक index;

	क्रम (index = 0; map[index].name ; index++) अणु
		अगर (rdmsrl_safe(map[index].bit_mask, &pcstate_count))
			जारी;

		pcstate_count *= 1000;
		करो_भाग(pcstate_count, tsc_khz);
		seq_म_लिखो(s, "%-8s : %llu\n", map[index].name,
			   pcstate_count);
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(pmc_core_pkgc);

अटल व्योम pmc_core_get_low_घातer_modes(काष्ठा pmc_dev *pmcdev)
अणु
	u8 lpm_priority[LPM_MAX_NUM_MODES];
	u32 lpm_en;
	पूर्णांक mode, i, p;

	/* Use LPM Maps to indicate support क्रम substates */
	अगर (!pmcdev->map->lpm_num_maps)
		वापस;

	lpm_en = pmc_core_reg_पढ़ो(pmcdev, pmcdev->map->lpm_en_offset);
	pmcdev->num_lpm_modes = hweight32(lpm_en);

	/* Each byte contains inक्रमmation क्रम 2 modes (7:4 and 3:0) */
	क्रम (mode = 0; mode < LPM_MAX_NUM_MODES; mode += 2) अणु
		u8 priority = pmc_core_reg_पढ़ो_byte(pmcdev,
				pmcdev->map->lpm_priority_offset + (mode / 2));
		पूर्णांक pri0 = GENMASK(3, 0) & priority;
		पूर्णांक pri1 = (GENMASK(7, 4) & priority) >> 4;

		lpm_priority[pri0] = mode;
		lpm_priority[pri1] = mode + 1;
	पूर्ण

	/*
	 * Loop though all modes from lowest to highest priority,
	 * and capture all enabled modes in order
	 */
	i = 0;
	क्रम (p = LPM_MAX_NUM_MODES - 1; p >= 0; p--) अणु
		पूर्णांक mode = lpm_priority[p];

		अगर (!(BIT(mode) & lpm_en))
			जारी;

		pmcdev->lpm_en_modes[i++] = mode;
	पूर्ण
पूर्ण

अटल व्योम pmc_core_dbgfs_unरेजिस्टर(काष्ठा pmc_dev *pmcdev)
अणु
	debugfs_हटाओ_recursive(pmcdev->dbgfs_dir);
पूर्ण

अटल व्योम pmc_core_dbgfs_रेजिस्टर(काष्ठा pmc_dev *pmcdev)
अणु
	काष्ठा dentry *dir;

	dir = debugfs_create_dir("pmc_core", शून्य);
	pmcdev->dbgfs_dir = dir;

	debugfs_create_file("slp_s0_residency_usec", 0444, dir, pmcdev,
			    &pmc_core_dev_state);

	अगर (pmcdev->map->pfear_sts)
		debugfs_create_file("pch_ip_power_gating_status", 0444, dir,
				    pmcdev, &pmc_core_ppfear_fops);

	debugfs_create_file("ltr_ignore", 0644, dir, pmcdev,
			    &pmc_core_ltr_ignore_ops);

	debugfs_create_file("ltr_show", 0444, dir, pmcdev, &pmc_core_ltr_fops);

	debugfs_create_file("package_cstate_show", 0444, dir, pmcdev,
			    &pmc_core_pkgc_fops);

	अगर (pmcdev->map->pll_sts)
		debugfs_create_file("pll_status", 0444, dir, pmcdev,
				    &pmc_core_pll_fops);

	अगर (pmcdev->map->mphy_sts)
		debugfs_create_file("mphy_core_lanes_power_gating_status",
				    0444, dir, pmcdev,
				    &pmc_core_mphy_pg_fops);

	अगर (pmcdev->map->slps0_dbg_maps) अणु
		debugfs_create_file("slp_s0_debug_status", 0444,
				    dir, pmcdev,
				    &pmc_core_slps0_dbg_fops);

		debugfs_create_bool("slp_s0_dbg_latch", 0644,
				    dir, &slps0_dbg_latch);
	पूर्ण

	अगर (pmcdev->map->lpm_en_offset) अणु
		debugfs_create_file("substate_residencies", 0444,
				    pmcdev->dbgfs_dir, pmcdev,
				    &pmc_core_substate_res_fops);
	पूर्ण

	अगर (pmcdev->map->lpm_status_offset) अणु
		debugfs_create_file("substate_status_registers", 0444,
				    pmcdev->dbgfs_dir, pmcdev,
				    &pmc_core_substate_sts_regs_fops);
		debugfs_create_file("substate_live_status_registers", 0444,
				    pmcdev->dbgfs_dir, pmcdev,
				    &pmc_core_substate_l_sts_regs_fops);
		debugfs_create_file("lpm_latch_mode", 0644,
				    pmcdev->dbgfs_dir, pmcdev,
				    &pmc_core_lpm_latch_mode_fops);
	पूर्ण

	अगर (pmcdev->lpm_req_regs) अणु
		debugfs_create_file("substate_requirements", 0444,
				    pmcdev->dbgfs_dir, pmcdev,
				    &pmc_core_substate_req_regs_fops);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा x86_cpu_id पूर्णांकel_pmc_core_ids[] = अणु
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE_L,		&spt_reg_map),
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE,		&spt_reg_map),
	X86_MATCH_INTEL_FAM6_MODEL(KABYLAKE_L,		&spt_reg_map),
	X86_MATCH_INTEL_FAM6_MODEL(KABYLAKE,		&spt_reg_map),
	X86_MATCH_INTEL_FAM6_MODEL(CANNONLAKE_L,	&cnp_reg_map),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_L,		&icl_reg_map),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_NNPI,	&icl_reg_map),
	X86_MATCH_INTEL_FAM6_MODEL(COMETLAKE,		&cnp_reg_map),
	X86_MATCH_INTEL_FAM6_MODEL(COMETLAKE_L,		&cnp_reg_map),
	X86_MATCH_INTEL_FAM6_MODEL(TIGERLAKE_L,		&tgl_reg_map),
	X86_MATCH_INTEL_FAM6_MODEL(TIGERLAKE,		&tgl_reg_map),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_TREMONT,	&tgl_reg_map),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_TREMONT_L,	&icl_reg_map),
	X86_MATCH_INTEL_FAM6_MODEL(ROCKETLAKE,		&tgl_reg_map),
	X86_MATCH_INTEL_FAM6_MODEL(ALDERLAKE_L,		&tgl_reg_map),
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(x86cpu, पूर्णांकel_pmc_core_ids);

अटल स्थिर काष्ठा pci_device_id pmc_pci_ids[] = अणु
	अणु PCI_VDEVICE(INTEL, SPT_PMC_PCI_DEVICE_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;

/*
 * This quirk can be used on those platक्रमms where
 * the platक्रमm BIOS enक्रमces 24Mhz crystal to shutकरोwn
 * beक्रमe PMC can निश्चित SLP_S0#.
 */
अटल bool xtal_ignore;
अटल पूर्णांक quirk_xtal_ignore(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	xtal_ignore = true;
	वापस 0;
पूर्ण

अटल व्योम pmc_core_xtal_ignore(काष्ठा pmc_dev *pmcdev)
अणु
	u32 value;

	value = pmc_core_reg_पढ़ो(pmcdev, pmcdev->map->pm_vric1_offset);
	/* 24MHz Crystal Shutकरोwn Qualअगरication Disable */
	value |= SPT_PMC_VRIC1_XTALSDQDIS;
	/* Low Voltage Mode Enable */
	value &= ~SPT_PMC_VRIC1_SLPS0LVEN;
	pmc_core_reg_ग_लिखो(pmcdev, pmcdev->map->pm_vric1_offset, value);
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id pmc_core_dmi_table[]  = अणु
	अणु
	.callback = quirk_xtal_ignore,
	.ident = "HP Elite x2 1013 G3",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "HP"),
		DMI_MATCH(DMI_PRODUCT_NAME, "HP Elite x2 1013 G3"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम pmc_core_करो_dmi_quirks(काष्ठा pmc_dev *pmcdev)
अणु
	dmi_check_प्रणाली(pmc_core_dmi_table);

	अगर (xtal_ignore)
		pmc_core_xtal_ignore(pmcdev);
पूर्ण

अटल पूर्णांक pmc_core_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अटल bool device_initialized;
	काष्ठा pmc_dev *pmcdev;
	स्थिर काष्ठा x86_cpu_id *cpu_id;
	u64 slp_s0_addr;

	अगर (device_initialized)
		वापस -ENODEV;

	pmcdev = devm_kzalloc(&pdev->dev, माप(*pmcdev), GFP_KERNEL);
	अगर (!pmcdev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, pmcdev);

	cpu_id = x86_match_cpu(पूर्णांकel_pmc_core_ids);
	अगर (!cpu_id)
		वापस -ENODEV;

	pmcdev->map = (काष्ठा pmc_reg_map *)cpu_id->driver_data;

	/*
	 * Coffee Lake has CPU ID of Kaby Lake and Cannon Lake PCH. So here
	 * Sunrisepoपूर्णांक PCH regmap can't be used. Use Cannon Lake PCH regmap
	 * in this हाल.
	 */
	अगर (pmcdev->map == &spt_reg_map && !pci_dev_present(pmc_pci_ids))
		pmcdev->map = &cnp_reg_map;

	अगर (lpit_पढ़ो_residency_count_address(&slp_s0_addr)) अणु
		pmcdev->base_addr = PMC_BASE_ADDR_DEFAULT;

		अगर (page_is_ram(PHYS_PFN(pmcdev->base_addr)))
			वापस -ENODEV;
	पूर्ण अन्यथा अणु
		pmcdev->base_addr = slp_s0_addr - pmcdev->map->slp_s0_offset;
	पूर्ण

	pmcdev->regbase = ioremap(pmcdev->base_addr,
				  pmcdev->map->regmap_length);
	अगर (!pmcdev->regbase)
		वापस -ENOMEM;

	mutex_init(&pmcdev->lock);

	pmcdev->pmc_xram_पढ़ो_bit = pmc_core_check_पढ़ो_lock_bit(pmcdev);
	pmc_core_get_low_घातer_modes(pmcdev);
	pmc_core_करो_dmi_quirks(pmcdev);

	अगर (pmcdev->map == &tgl_reg_map)
		pmc_core_get_tgl_lpm_reqs(pdev);

	/*
	 * On TGL, due to a hardware limitation, the GBE LTR blocks PC10 when
	 * a cable is attached. Tell the PMC to ignore it.
	 */
	अगर (pmcdev->map == &tgl_reg_map) अणु
		dev_dbg(&pdev->dev, "ignoring GBE LTR\n");
		pmc_core_send_ltr_ignore(pmcdev, 3);
	पूर्ण

	pmc_core_dbgfs_रेजिस्टर(pmcdev);

	device_initialized = true;
	dev_info(&pdev->dev, " initialized\n");

	वापस 0;
पूर्ण

अटल पूर्णांक pmc_core_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pmc_dev *pmcdev = platक्रमm_get_drvdata(pdev);

	pmc_core_dbgfs_unरेजिस्टर(pmcdev);
	platक्रमm_set_drvdata(pdev, शून्य);
	mutex_destroy(&pmcdev->lock);
	iounmap(pmcdev->regbase);
	वापस 0;
पूर्ण

अटल bool warn_on_s0ix_failures;
module_param(warn_on_s0ix_failures, bool, 0644);
MODULE_PARM_DESC(warn_on_s0ix_failures, "Check and warn for S0ix failures");

अटल __maybe_unused पूर्णांक pmc_core_suspend(काष्ठा device *dev)
अणु
	काष्ठा pmc_dev *pmcdev = dev_get_drvdata(dev);

	pmcdev->check_counters = false;

	/* No warnings on S0ix failures */
	अगर (!warn_on_s0ix_failures)
		वापस 0;

	/* Check अगर the syspend will actually use S0ix */
	अगर (pm_suspend_via_firmware())
		वापस 0;

	/* Save PC10 residency क्रम checking later */
	अगर (rdmsrl_safe(MSR_PKG_C10_RESIDENCY, &pmcdev->pc10_counter))
		वापस -EIO;

	/* Save S0ix residency क्रम checking later */
	अगर (pmc_core_dev_state_get(pmcdev, &pmcdev->s0ix_counter))
		वापस -EIO;

	pmcdev->check_counters = true;
	वापस 0;
पूर्ण

अटल अंतरभूत bool pmc_core_is_pc10_failed(काष्ठा pmc_dev *pmcdev)
अणु
	u64 pc10_counter;

	अगर (rdmsrl_safe(MSR_PKG_C10_RESIDENCY, &pc10_counter))
		वापस false;

	अगर (pc10_counter == pmcdev->pc10_counter)
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool pmc_core_is_s0ix_failed(काष्ठा pmc_dev *pmcdev)
अणु
	u64 s0ix_counter;

	अगर (pmc_core_dev_state_get(pmcdev, &s0ix_counter))
		वापस false;

	अगर (s0ix_counter == pmcdev->s0ix_counter)
		वापस true;

	वापस false;
पूर्ण

अटल __maybe_unused पूर्णांक pmc_core_resume(काष्ठा device *dev)
अणु
	काष्ठा pmc_dev *pmcdev = dev_get_drvdata(dev);
	स्थिर काष्ठा pmc_bit_map **maps = pmcdev->map->lpm_sts;
	पूर्णांक offset = pmcdev->map->lpm_status_offset;

	अगर (!pmcdev->check_counters)
		वापस 0;

	अगर (!pmc_core_is_s0ix_failed(pmcdev))
		वापस 0;

	अगर (pmc_core_is_pc10_failed(pmcdev)) अणु
		/* S0ix failed because of PC10 entry failure */
		dev_info(dev, "CPU did not enter PC10!!! (PC10 cnt=0x%llx)\n",
			 pmcdev->pc10_counter);
		वापस 0;
	पूर्ण

	/* The real पूर्णांकeresting हाल - S0ix failed - lets ask PMC why. */
	dev_warn(dev, "CPU did not enter SLP_S0!!! (S0ix cnt=%llu)\n",
		 pmcdev->s0ix_counter);
	अगर (pmcdev->map->slps0_dbg_maps)
		pmc_core_slps0_display(pmcdev, dev, शून्य);
	अगर (pmcdev->map->lpm_sts)
		pmc_core_lpm_display(pmcdev, dev, शून्य, offset, "STATUS", maps);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops pmc_core_pm_ops = अणु
	SET_LATE_SYSTEM_SLEEP_PM_OPS(pmc_core_suspend, pmc_core_resume)
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id pmc_core_acpi_ids[] = अणु
	अणु"INT33A1", 0पूर्ण, /* _HID क्रम Intel Power Engine, _CID PNP0D80*/
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, pmc_core_acpi_ids);

अटल काष्ठा platक्रमm_driver pmc_core_driver = अणु
	.driver = अणु
		.name = "intel_pmc_core",
		.acpi_match_table = ACPI_PTR(pmc_core_acpi_ids),
		.pm = &pmc_core_pm_ops,
		.dev_groups = pmc_dev_groups,
	पूर्ण,
	.probe = pmc_core_probe,
	.हटाओ = pmc_core_हटाओ,
पूर्ण;

module_platक्रमm_driver(pmc_core_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel PMC Core Driver");
