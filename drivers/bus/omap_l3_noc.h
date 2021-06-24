<शैली गुरु>
/*
 * OMAP L3 Interconnect  error handling driver header
 *
 * Copyright (C) 2011-2015 Texas Instruments Incorporated - http://www.ti.com/
 *	Santosh Shilimkar <santosh.shilimkar@ti.com>
 *	sriअक्षरan <r.sriअक्षरan@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */
#अगर_अघोषित __OMAP_L3_NOC_H
#घोषणा __OMAP_L3_NOC_H

#घोषणा MAX_L3_MODULES			3
#घोषणा MAX_CLKDM_TARGETS		31

#घोषणा CLEAR_STDERR_LOG		(1 << 31)
#घोषणा CUSTOM_ERROR			0x2
#घोषणा STANDARD_ERROR			0x0
#घोषणा INBAND_ERROR			0x0
#घोषणा L3_APPLICATION_ERROR		0x0
#घोषणा L3_DEBUG_ERROR			0x1

/* L3 TARG रेजिस्टर offsets */
#घोषणा L3_TARG_STDERRLOG_MAIN		0x48
#घोषणा L3_TARG_STDERRLOG_HDR		0x4c
#घोषणा L3_TARG_STDERRLOG_MSTADDR	0x50
#घोषणा L3_TARG_STDERRLOG_INFO		0x58
#घोषणा L3_TARG_STDERRLOG_SLVOFSLSB	0x5c
#घोषणा L3_TARG_STDERRLOG_CINFO_INFO	0x64
#घोषणा L3_TARG_STDERRLOG_CINFO_MSTADDR	0x68
#घोषणा L3_TARG_STDERRLOG_CINFO_OPCODE	0x6c
#घोषणा L3_FLAGMUX_REGERR0		0xc
#घोषणा L3_FLAGMUX_MASK0		0x8

#घोषणा L3_TARGET_NOT_SUPPORTED		शून्य

#घोषणा L3_BASE_IS_SUBMODULE		((व्योम __iomem *)(1 << 0))

अटल स्थिर अक्षर * स्थिर l3_transaction_type[] = अणु
	/* 0 0 0 */ "Idle",
	/* 0 0 1 */ "Write",
	/* 0 1 0 */ "Read",
	/* 0 1 1 */ "ReadEx",
	/* 1 0 0 */ "Read Link",
	/* 1 0 1 */ "Write Non-Posted",
	/* 1 1 0 */ "Write Conditional",
	/* 1 1 1 */ "Write Broadcast",
पूर्ण;

/**
 * काष्ठा l3_masters_data - L3 Master inक्रमmation
 * @id:		ID of the L3 Master
 * @name:	master name
 */
काष्ठा l3_masters_data अणु
	u32 id;
	अक्षर *name;
पूर्ण;

/**
 * काष्ठा l3_target_data - L3 Target inक्रमmation
 * @offset:	Offset from base क्रम L3 Target
 * @name:	Target name
 *
 * Target inक्रमmation is organized indexed by bit field definitions.
 */
काष्ठा l3_target_data अणु
	u32 offset;
	अक्षर *name;
पूर्ण;

/**
 * काष्ठा l3_flagmux_data - Flag Mux inक्रमmation
 * @offset:	offset from base क्रम flagmux रेजिस्टर
 * @l3_targ:	array indexed by flagmux index (bit offset) poपूर्णांकing to the
 *		target data. unsupported ones are marked with
 *		L3_TARGET_NOT_SUPPORTED
 * @num_targ_data: number of entries in target data
 * @mask_app_bits: ignore these from raw application irq status
 * @mask_dbg_bits: ignore these from raw debug irq status
 */
काष्ठा l3_flagmux_data अणु
	u32 offset;
	काष्ठा l3_target_data *l3_targ;
	u8 num_targ_data;
	u32 mask_app_bits;
	u32 mask_dbg_bits;
पूर्ण;


/**
 * काष्ठा omap_l3 - Description of data relevant क्रम L3 bus.
 * @dev:	device representing the bus (populated runसमय)
 * @l3_base:	base addresses of modules (populated runसमय अगर 0)
 *		अगर set to L3_BASE_IS_SUBMODULE, then uses previous
 *		module index as the base address
 * @l3_flag_mux: array containing flag mux data per module
 *		 offset from corresponding module base indexed per
 *		 module.
 * @num_modules: number of घड़ी करोमुख्यs / modules.
 * @l3_masters:	array poपूर्णांकing to master data containing name and रेजिस्टर
 *		offset क्रम the master.
 * @num_master: number of masters
 * @mst_addr_mask: Mask representing MSTADDR inक्रमmation of NTTP packet
 * @debug_irq:	irq number of the debug पूर्णांकerrupt (populated runसमय)
 * @app_irq:	irq number of the application पूर्णांकerrupt (populated runसमय)
 */
काष्ठा omap_l3 अणु
	काष्ठा device *dev;

	व्योम __iomem *l3_base[MAX_L3_MODULES];
	काष्ठा l3_flagmux_data **l3_flagmux;
	पूर्णांक num_modules;

	काष्ठा l3_masters_data *l3_masters;
	पूर्णांक num_masters;
	u32 mst_addr_mask;

	पूर्णांक debug_irq;
	पूर्णांक app_irq;
पूर्ण;

अटल काष्ठा l3_target_data omap_l3_target_data_clk1[] = अणु
	अणु0x100,	"DMM1",पूर्ण,
	अणु0x200,	"DMM2",पूर्ण,
	अणु0x300,	"ABE",पूर्ण,
	अणु0x400,	"L4CFG",पूर्ण,
	अणु0x600,	"CLK2PWRDISC",पूर्ण,
	अणु0x0,	"HOSTCLK1",पूर्ण,
	अणु0x900,	"L4WAKEUP",पूर्ण,
पूर्ण;

अटल काष्ठा l3_flagmux_data omap_l3_flagmux_clk1 = अणु
	.offset = 0x500,
	.l3_targ = omap_l3_target_data_clk1,
	.num_targ_data = ARRAY_SIZE(omap_l3_target_data_clk1),
पूर्ण;


अटल काष्ठा l3_target_data omap_l3_target_data_clk2[] = अणु
	अणु0x500,	"CORTEXM3",पूर्ण,
	अणु0x300,	"DSS",पूर्ण,
	अणु0x100,	"GPMC",पूर्ण,
	अणु0x400,	"ISS",पूर्ण,
	अणु0x700,	"IVAHD",पूर्ण,
	अणु0xD00,	"AES1",पूर्ण,
	अणु0x900,	"L4PER0",पूर्ण,
	अणु0x200,	"OCMRAM",पूर्ण,
	अणु0x100,	"GPMCsERROR",पूर्ण,
	अणु0x600,	"SGX",पूर्ण,
	अणु0x800,	"SL2",पूर्ण,
	अणु0x1600, "C2C",पूर्ण,
	अणु0x1100, "PWRDISCCLK1",पूर्ण,
	अणु0xF00,	"SHA1",पूर्ण,
	अणु0xE00,	"AES2",पूर्ण,
	अणु0xC00,	"L4PER3",पूर्ण,
	अणु0xA00,	"L4PER1",पूर्ण,
	अणु0xB00,	"L4PER2",पूर्ण,
	अणु0x0,	"HOSTCLK2",पूर्ण,
	अणु0x1800, "CAL",पूर्ण,
	अणु0x1700, "LLI",पूर्ण,
पूर्ण;

अटल काष्ठा l3_flagmux_data omap_l3_flagmux_clk2 = अणु
	.offset = 0x1000,
	.l3_targ = omap_l3_target_data_clk2,
	.num_targ_data = ARRAY_SIZE(omap_l3_target_data_clk2),
पूर्ण;


अटल काष्ठा l3_target_data omap4_l3_target_data_clk3[] = अणु
	अणु0x0100, "DEBUGSS",पूर्ण,
पूर्ण;

अटल काष्ठा l3_flagmux_data omap4_l3_flagmux_clk3 = अणु
	.offset = 0x0200,
	.l3_targ = omap4_l3_target_data_clk3,
	.num_targ_data = ARRAY_SIZE(omap4_l3_target_data_clk3),
पूर्ण;

अटल काष्ठा l3_masters_data omap_l3_masters[] = अणु
	अणु 0x00, "MPU"पूर्ण,
	अणु 0x04, "CS_ADP"पूर्ण,
	अणु 0x05, "xxx"पूर्ण,
	अणु 0x08, "DSP"पूर्ण,
	अणु 0x0C, "IVAHD"पूर्ण,
	अणु 0x10, "ISS"पूर्ण,
	अणु 0x11, "DucatiM3"पूर्ण,
	अणु 0x12, "FaceDetect"पूर्ण,
	अणु 0x14, "SDMA_Rd"पूर्ण,
	अणु 0x15, "SDMA_Wr"पूर्ण,
	अणु 0x16, "xxx"पूर्ण,
	अणु 0x17, "xxx"पूर्ण,
	अणु 0x18, "SGX"पूर्ण,
	अणु 0x1C, "DSS"पूर्ण,
	अणु 0x20, "C2C"पूर्ण,
	अणु 0x22, "xxx"पूर्ण,
	अणु 0x23, "xxx"पूर्ण,
	अणु 0x24, "HSI"पूर्ण,
	अणु 0x28, "MMC1"पूर्ण,
	अणु 0x29, "MMC2"पूर्ण,
	अणु 0x2A, "MMC6"पूर्ण,
	अणु 0x2C, "UNIPRO1"पूर्ण,
	अणु 0x30, "USBHOSTHS"पूर्ण,
	अणु 0x31, "USBOTGHS"पूर्ण,
	अणु 0x32, "USBHOSTFS"पूर्ण
पूर्ण;

अटल काष्ठा l3_flagmux_data *omap4_l3_flagmux[] = अणु
	&omap_l3_flagmux_clk1,
	&omap_l3_flagmux_clk2,
	&omap4_l3_flagmux_clk3,
पूर्ण;

अटल स्थिर काष्ठा omap_l3 omap4_l3_data = अणु
	.l3_flagmux = omap4_l3_flagmux,
	.num_modules = ARRAY_SIZE(omap4_l3_flagmux),
	.l3_masters = omap_l3_masters,
	.num_masters = ARRAY_SIZE(omap_l3_masters),
	/* The 6 MSBs of रेजिस्टर field used to distinguish initiator */
	.mst_addr_mask = 0xFC,
पूर्ण;

/* OMAP5 data */
अटल काष्ठा l3_target_data omap5_l3_target_data_clk3[] = अणु
	अणु0x0100, "L3INSTR",पूर्ण,
	अणु0x0300, "DEBUGSS",पूर्ण,
	अणु0x0,	 "HOSTCLK3",पूर्ण,
पूर्ण;

अटल काष्ठा l3_flagmux_data omap5_l3_flagmux_clk3 = अणु
	.offset = 0x0200,
	.l3_targ = omap5_l3_target_data_clk3,
	.num_targ_data = ARRAY_SIZE(omap5_l3_target_data_clk3),
पूर्ण;

अटल काष्ठा l3_flagmux_data *omap5_l3_flagmux[] = अणु
	&omap_l3_flagmux_clk1,
	&omap_l3_flagmux_clk2,
	&omap5_l3_flagmux_clk3,
पूर्ण;

अटल स्थिर काष्ठा omap_l3 omap5_l3_data = अणु
	.l3_flagmux = omap5_l3_flagmux,
	.num_modules = ARRAY_SIZE(omap5_l3_flagmux),
	.l3_masters = omap_l3_masters,
	.num_masters = ARRAY_SIZE(omap_l3_masters),
	/* The 6 MSBs of रेजिस्टर field used to distinguish initiator */
	.mst_addr_mask = 0x7E0,
पूर्ण;

/* DRA7 data */
अटल काष्ठा l3_target_data dra_l3_target_data_clk1[] = अणु
	अणु0x2a00, "AES1",पूर्ण,
	अणु0x0200, "DMM_P1",पूर्ण,
	अणु0x0600, "DSP2_SDMA",पूर्ण,
	अणु0x0b00, "EVE2",पूर्ण,
	अणु0x1300, "DMM_P2",पूर्ण,
	अणु0x2c00, "AES2",पूर्ण,
	अणु0x0300, "DSP1_SDMA",पूर्ण,
	अणु0x0a00, "EVE1",पूर्ण,
	अणु0x0c00, "EVE3",पूर्ण,
	अणु0x0d00, "EVE4",पूर्ण,
	अणु0x2900, "DSS",पूर्ण,
	अणु0x0100, "GPMC",पूर्ण,
	अणु0x3700, "PCIE1",पूर्ण,
	अणु0x1600, "IVA_CONFIG",पूर्ण,
	अणु0x1800, "IVA_SL2IF",पूर्ण,
	अणु0x0500, "L4_CFG",पूर्ण,
	अणु0x1d00, "L4_WKUP",पूर्ण,
	अणु0x3800, "PCIE2",पूर्ण,
	अणु0x3300, "SHA2_1",पूर्ण,
	अणु0x1200, "GPU",पूर्ण,
	अणु0x1000, "IPU1",पूर्ण,
	अणु0x1100, "IPU2",पूर्ण,
	अणु0x2000, "TPCC_EDMA",पूर्ण,
	अणु0x2e00, "TPTC1_EDMA",पूर्ण,
	अणु0x2b00, "TPTC2_EDMA",पूर्ण,
	अणु0x0700, "VCP1",पूर्ण,
	अणु0x2500, "L4_PER2_P3",पूर्ण,
	अणु0x0e00, "L4_PER3_P3",पूर्ण,
	अणु0x2200, "MMU1",पूर्ण,
	अणु0x1400, "PRUSS1",पूर्ण,
	अणु0x1500, "PRUSS2"पूर्ण,
	अणु0x0800, "VCP1",पूर्ण,
पूर्ण;

अटल काष्ठा l3_flagmux_data dra_l3_flagmux_clk1 = अणु
	.offset = 0x803500,
	.l3_targ = dra_l3_target_data_clk1,
	.num_targ_data = ARRAY_SIZE(dra_l3_target_data_clk1),
पूर्ण;

अटल काष्ठा l3_target_data dra_l3_target_data_clk2[] = अणु
	अणु0x0,	"HOST CLK1",पूर्ण,
	अणु0x800000, "HOST CLK2",पूर्ण,
	अणु0xdead, L3_TARGET_NOT_SUPPORTED,पूर्ण,
	अणु0x3400, "SHA2_2",पूर्ण,
	अणु0x0900, "BB2D",पूर्ण,
	अणु0xdead, L3_TARGET_NOT_SUPPORTED,पूर्ण,
	अणु0x2100, "L4_PER1_P3",पूर्ण,
	अणु0x1c00, "L4_PER1_P1",पूर्ण,
	अणु0x1f00, "L4_PER1_P2",पूर्ण,
	अणु0x2300, "L4_PER2_P1",पूर्ण,
	अणु0x2400, "L4_PER2_P2",पूर्ण,
	अणु0x2600, "L4_PER3_P1",पूर्ण,
	अणु0x2700, "L4_PER3_P2",पूर्ण,
	अणु0x2f00, "MCASP1",पूर्ण,
	अणु0x3000, "MCASP2",पूर्ण,
	अणु0x3100, "MCASP3",पूर्ण,
	अणु0x2800, "MMU2",पूर्ण,
	अणु0x0f00, "OCMC_RAM1",पूर्ण,
	अणु0x1700, "OCMC_RAM2",पूर्ण,
	अणु0x1900, "OCMC_RAM3",पूर्ण,
	अणु0x1e00, "OCMC_ROM",पूर्ण,
	अणु0x3900, "QSPI",पूर्ण,
पूर्ण;

अटल काष्ठा l3_flagmux_data dra_l3_flagmux_clk2 = अणु
	.offset = 0x803600,
	.l3_targ = dra_l3_target_data_clk2,
	.num_targ_data = ARRAY_SIZE(dra_l3_target_data_clk2),
पूर्ण;

अटल काष्ठा l3_target_data dra_l3_target_data_clk3[] = अणु
	अणु0x0100, "L3_INSTR"पूर्ण,
	अणु0x0300, "DEBUGSS_CT_TBR"पूर्ण,
	अणु0x0,	 "HOST CLK3"पूर्ण,
पूर्ण;

अटल काष्ठा l3_flagmux_data dra_l3_flagmux_clk3 = अणु
	.offset = 0x200,
	.l3_targ = dra_l3_target_data_clk3,
	.num_targ_data = ARRAY_SIZE(dra_l3_target_data_clk3),
पूर्ण;

अटल काष्ठा l3_masters_data dra_l3_masters[] = अणु
	अणु 0x0, "MPU" पूर्ण,
	अणु 0x4, "CS_DAP" पूर्ण,
	अणु 0x5, "IEEE1500_2_OCP" पूर्ण,
	अणु 0x8, "DSP1_MDMA" पूर्ण,
	अणु 0x9, "DSP1_CFG" पूर्ण,
	अणु 0xA, "DSP1_DMA" पूर्ण,
	अणु 0xB, "DSP2_MDMA" पूर्ण,
	अणु 0xC, "DSP2_CFG" पूर्ण,
	अणु 0xD, "DSP2_DMA" पूर्ण,
	अणु 0xE, "IVA" पूर्ण,
	अणु 0x10, "EVE1_P1" पूर्ण,
	अणु 0x11, "EVE2_P1" पूर्ण,
	अणु 0x12, "EVE3_P1" पूर्ण,
	अणु 0x13, "EVE4_P1" पूर्ण,
	अणु 0x14, "PRUSS1 PRU1" पूर्ण,
	अणु 0x15, "PRUSS1 PRU2" पूर्ण,
	अणु 0x16, "PRUSS2 PRU1" पूर्ण,
	अणु 0x17, "PRUSS2 PRU2" पूर्ण,
	अणु 0x18, "IPU1" पूर्ण,
	अणु 0x19, "IPU2" पूर्ण,
	अणु 0x1A, "SDMA" पूर्ण,
	अणु 0x1B, "CDMA" पूर्ण,
	अणु 0x1C, "TC1_EDMA" पूर्ण,
	अणु 0x1D, "TC2_EDMA" पूर्ण,
	अणु 0x20, "DSS" पूर्ण,
	अणु 0x21, "MMU1" पूर्ण,
	अणु 0x22, "PCIE1" पूर्ण,
	अणु 0x23, "MMU2" पूर्ण,
	अणु 0x24, "VIP1" पूर्ण,
	अणु 0x25, "VIP2" पूर्ण,
	अणु 0x26, "VIP3" पूर्ण,
	अणु 0x27, "VPE" पूर्ण,
	अणु 0x28, "GPU_P1" पूर्ण,
	अणु 0x29, "BB2D" पूर्ण,
	अणु 0x29, "GPU_P2" पूर्ण,
	अणु 0x2B, "GMAC_SW" पूर्ण,
	अणु 0x2C, "USB3" पूर्ण,
	अणु 0x2D, "USB2_SS" पूर्ण,
	अणु 0x2E, "USB2_ULPI_SS1" पूर्ण,
	अणु 0x2F, "USB2_ULPI_SS2" पूर्ण,
	अणु 0x30, "CSI2_1" पूर्ण,
	अणु 0x31, "CSI2_2" पूर्ण,
	अणु 0x33, "SATA" पूर्ण,
	अणु 0x34, "EVE1_P2" पूर्ण,
	अणु 0x35, "EVE2_P2" पूर्ण,
	अणु 0x36, "EVE3_P2" पूर्ण,
	अणु 0x37, "EVE4_P2" पूर्ण
पूर्ण;

अटल काष्ठा l3_flagmux_data *dra_l3_flagmux[] = अणु
	&dra_l3_flagmux_clk1,
	&dra_l3_flagmux_clk2,
	&dra_l3_flagmux_clk3,
पूर्ण;

अटल स्थिर काष्ठा omap_l3 dra_l3_data = अणु
	.l3_base = अणु [1] = L3_BASE_IS_SUBMODULE पूर्ण,
	.l3_flagmux = dra_l3_flagmux,
	.num_modules = ARRAY_SIZE(dra_l3_flagmux),
	.l3_masters = dra_l3_masters,
	.num_masters = ARRAY_SIZE(dra_l3_masters),
	/* The 6 MSBs of रेजिस्टर field used to distinguish initiator */
	.mst_addr_mask = 0xFC,
पूर्ण;

/* AM4372 data */
अटल काष्ठा l3_target_data am4372_l3_target_data_200f[] = अणु
	अणु0xf00,  "EMIF",पूर्ण,
	अणु0x1200, "DES",पूर्ण,
	अणु0x400,  "OCMCRAM",पूर्ण,
	अणु0x700,  "TPTC0",पूर्ण,
	अणु0x800,  "TPTC1",पूर्ण,
	अणु0x900,  "TPTC2"पूर्ण,
	अणु0xb00,  "TPCC",पूर्ण,
	अणु0xd00,  "DEBUGSS",पूर्ण,
	अणु0xdead, L3_TARGET_NOT_SUPPORTED,पूर्ण,
	अणु0x200,  "SHA",पूर्ण,
	अणु0xc00,  "SGX530",पूर्ण,
	अणु0x500,  "AES0",पूर्ण,
	अणु0xa00,  "L4_FAST",पूर्ण,
	अणु0x300,  "MPUSS_L2_RAM",पूर्ण,
	अणु0x100,  "ICSS",पूर्ण,
पूर्ण;

अटल काष्ठा l3_flagmux_data am4372_l3_flagmux_200f = अणु
	.offset = 0x1000,
	.l3_targ = am4372_l3_target_data_200f,
	.num_targ_data = ARRAY_SIZE(am4372_l3_target_data_200f),
पूर्ण;

अटल काष्ठा l3_target_data am4372_l3_target_data_100s[] = अणु
	अणु0x100, "L4_PER_0",पूर्ण,
	अणु0x200, "L4_PER_1",पूर्ण,
	अणु0x300, "L4_PER_2",पूर्ण,
	अणु0x400, "L4_PER_3",पूर्ण,
	अणु0x800, "McASP0",पूर्ण,
	अणु0x900, "McASP1",पूर्ण,
	अणु0xC00, "MMCHS2",पूर्ण,
	अणु0x700, "GPMC",पूर्ण,
	अणु0xD00, "L4_FW",पूर्ण,
	अणु0xdead, L3_TARGET_NOT_SUPPORTED,पूर्ण,
	अणु0x500, "ADCTSC",पूर्ण,
	अणु0xE00, "L4_WKUP",पूर्ण,
	अणु0xA00, "MAG_CARD",पूर्ण,
पूर्ण;

अटल काष्ठा l3_flagmux_data am4372_l3_flagmux_100s = अणु
	.offset = 0x600,
	.l3_targ = am4372_l3_target_data_100s,
	.num_targ_data = ARRAY_SIZE(am4372_l3_target_data_100s),
पूर्ण;

अटल काष्ठा l3_masters_data am4372_l3_masters[] = अणु
	अणु 0x0, "M1 (128-bit)"पूर्ण,
	अणु 0x1, "M2 (64-bit)"पूर्ण,
	अणु 0x4, "DAP"पूर्ण,
	अणु 0x5, "P1500"पूर्ण,
	अणु 0xC, "ICSS0"पूर्ण,
	अणु 0xD, "ICSS1"पूर्ण,
	अणु 0x14, "Wakeup Processor"पूर्ण,
	अणु 0x18, "TPTC0 Read"पूर्ण,
	अणु 0x19, "TPTC0 Write"पूर्ण,
	अणु 0x1A, "TPTC1 Read"पूर्ण,
	अणु 0x1B, "TPTC1 Write"पूर्ण,
	अणु 0x1C, "TPTC2 Read"पूर्ण,
	अणु 0x1D, "TPTC2 Write"पूर्ण,
	अणु 0x20, "SGX530"पूर्ण,
	अणु 0x21, "OCP WP Traffic Probe"पूर्ण,
	अणु 0x22, "OCP WP DMA Profiling"पूर्ण,
	अणु 0x23, "OCP WP Event Trace"पूर्ण,
	अणु 0x25, "DSS"पूर्ण,
	अणु 0x28, "Crypto DMA RD"पूर्ण,
	अणु 0x29, "Crypto DMA WR"पूर्ण,
	अणु 0x2C, "VPFE0"पूर्ण,
	अणु 0x2D, "VPFE1"पूर्ण,
	अणु 0x30, "GEMAC"पूर्ण,
	अणु 0x34, "USB0 RD"पूर्ण,
	अणु 0x35, "USB0 WR"पूर्ण,
	अणु 0x36, "USB1 RD"पूर्ण,
	अणु 0x37, "USB1 WR"पूर्ण,
पूर्ण;

अटल काष्ठा l3_flagmux_data *am4372_l3_flagmux[] = अणु
	&am4372_l3_flagmux_200f,
	&am4372_l3_flagmux_100s,
पूर्ण;

अटल स्थिर काष्ठा omap_l3 am4372_l3_data = अणु
	.l3_flagmux = am4372_l3_flagmux,
	.num_modules = ARRAY_SIZE(am4372_l3_flagmux),
	.l3_masters = am4372_l3_masters,
	.num_masters = ARRAY_SIZE(am4372_l3_masters),
	/* All 6 bits of रेजिस्टर field used to distinguish initiator */
	.mst_addr_mask = 0x3F,
पूर्ण;

#पूर्ण_अगर	/* __OMAP_L3_NOC_H */
