<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#समावेश "goyaP.h"
#समावेश "../include/goya/goya_coresight.h"
#समावेश "../include/goya/asic_reg/goya_regs.h"
#समावेश "../include/goya/asic_reg/goya_masks.h"

#समावेश <uapi/misc/habanaद_असल.h>

#घोषणा GOYA_PLDM_CORESIGHT_TIMEOUT_USEC	(CORESIGHT_TIMEOUT_USEC * 100)

#घोषणा SPMU_SECTION_SIZE		DMA_CH_0_CS_SPMU_MAX_OFFSET
#घोषणा SPMU_EVENT_TYPES_OFFSET		0x400
#घोषणा SPMU_MAX_COUNTERS		6

अटल u64 debug_sपंचांग_regs[GOYA_STM_LAST + 1] = अणु
	[GOYA_STM_CPU]		= mmCPU_STM_BASE,
	[GOYA_STM_DMA_CH_0_CS]	= mmDMA_CH_0_CS_STM_BASE,
	[GOYA_STM_DMA_CH_1_CS]	= mmDMA_CH_1_CS_STM_BASE,
	[GOYA_STM_DMA_CH_2_CS]	= mmDMA_CH_2_CS_STM_BASE,
	[GOYA_STM_DMA_CH_3_CS]	= mmDMA_CH_3_CS_STM_BASE,
	[GOYA_STM_DMA_CH_4_CS]	= mmDMA_CH_4_CS_STM_BASE,
	[GOYA_STM_DMA_MACRO_CS]	= mmDMA_MACRO_CS_STM_BASE,
	[GOYA_STM_MME1_SBA]	= mmMME1_SBA_STM_BASE,
	[GOYA_STM_MME3_SBB]	= mmMME3_SBB_STM_BASE,
	[GOYA_STM_MME4_WACS2]	= mmMME4_WACS2_STM_BASE,
	[GOYA_STM_MME4_WACS]	= mmMME4_WACS_STM_BASE,
	[GOYA_STM_MMU_CS]	= mmMMU_CS_STM_BASE,
	[GOYA_STM_PCIE]		= mmPCIE_STM_BASE,
	[GOYA_STM_PSOC]		= mmPSOC_STM_BASE,
	[GOYA_STM_TPC0_EML]	= mmTPC0_EML_STM_BASE,
	[GOYA_STM_TPC1_EML]	= mmTPC1_EML_STM_BASE,
	[GOYA_STM_TPC2_EML]	= mmTPC2_EML_STM_BASE,
	[GOYA_STM_TPC3_EML]	= mmTPC3_EML_STM_BASE,
	[GOYA_STM_TPC4_EML]	= mmTPC4_EML_STM_BASE,
	[GOYA_STM_TPC5_EML]	= mmTPC5_EML_STM_BASE,
	[GOYA_STM_TPC6_EML]	= mmTPC6_EML_STM_BASE,
	[GOYA_STM_TPC7_EML]	= mmTPC7_EML_STM_BASE
पूर्ण;

अटल u64 debug_etf_regs[GOYA_ETF_LAST + 1] = अणु
	[GOYA_ETF_CPU_0]	= mmCPU_ETF_0_BASE,
	[GOYA_ETF_CPU_1]	= mmCPU_ETF_1_BASE,
	[GOYA_ETF_CPU_TRACE]	= mmCPU_ETF_TRACE_BASE,
	[GOYA_ETF_DMA_CH_0_CS]	= mmDMA_CH_0_CS_ETF_BASE,
	[GOYA_ETF_DMA_CH_1_CS]	= mmDMA_CH_1_CS_ETF_BASE,
	[GOYA_ETF_DMA_CH_2_CS]	= mmDMA_CH_2_CS_ETF_BASE,
	[GOYA_ETF_DMA_CH_3_CS]	= mmDMA_CH_3_CS_ETF_BASE,
	[GOYA_ETF_DMA_CH_4_CS]	= mmDMA_CH_4_CS_ETF_BASE,
	[GOYA_ETF_DMA_MACRO_CS]	= mmDMA_MACRO_CS_ETF_BASE,
	[GOYA_ETF_MME1_SBA]	= mmMME1_SBA_ETF_BASE,
	[GOYA_ETF_MME3_SBB]	= mmMME3_SBB_ETF_BASE,
	[GOYA_ETF_MME4_WACS2]	= mmMME4_WACS2_ETF_BASE,
	[GOYA_ETF_MME4_WACS]	= mmMME4_WACS_ETF_BASE,
	[GOYA_ETF_MMU_CS]	= mmMMU_CS_ETF_BASE,
	[GOYA_ETF_PCIE]		= mmPCIE_ETF_BASE,
	[GOYA_ETF_PSOC]		= mmPSOC_ETF_BASE,
	[GOYA_ETF_TPC0_EML]	= mmTPC0_EML_ETF_BASE,
	[GOYA_ETF_TPC1_EML]	= mmTPC1_EML_ETF_BASE,
	[GOYA_ETF_TPC2_EML]	= mmTPC2_EML_ETF_BASE,
	[GOYA_ETF_TPC3_EML]	= mmTPC3_EML_ETF_BASE,
	[GOYA_ETF_TPC4_EML]	= mmTPC4_EML_ETF_BASE,
	[GOYA_ETF_TPC5_EML]	= mmTPC5_EML_ETF_BASE,
	[GOYA_ETF_TPC6_EML]	= mmTPC6_EML_ETF_BASE,
	[GOYA_ETF_TPC7_EML]	= mmTPC7_EML_ETF_BASE
पूर्ण;

अटल u64 debug_funnel_regs[GOYA_FUNNEL_LAST + 1] = अणु
	[GOYA_FUNNEL_CPU]		= mmCPU_FUNNEL_BASE,
	[GOYA_FUNNEL_DMA_CH_6_1]	= mmDMA_CH_FUNNEL_6_1_BASE,
	[GOYA_FUNNEL_DMA_MACRO_3_1]	= mmDMA_MACRO_FUNNEL_3_1_BASE,
	[GOYA_FUNNEL_MME0_RTR]		= mmMME0_RTR_FUNNEL_BASE,
	[GOYA_FUNNEL_MME1_RTR]		= mmMME1_RTR_FUNNEL_BASE,
	[GOYA_FUNNEL_MME2_RTR]		= mmMME2_RTR_FUNNEL_BASE,
	[GOYA_FUNNEL_MME3_RTR]		= mmMME3_RTR_FUNNEL_BASE,
	[GOYA_FUNNEL_MME4_RTR]		= mmMME4_RTR_FUNNEL_BASE,
	[GOYA_FUNNEL_MME5_RTR]		= mmMME5_RTR_FUNNEL_BASE,
	[GOYA_FUNNEL_PCIE]		= mmPCIE_FUNNEL_BASE,
	[GOYA_FUNNEL_PSOC]		= mmPSOC_FUNNEL_BASE,
	[GOYA_FUNNEL_TPC0_EML]		= mmTPC0_EML_FUNNEL_BASE,
	[GOYA_FUNNEL_TPC1_EML]		= mmTPC1_EML_FUNNEL_BASE,
	[GOYA_FUNNEL_TPC1_RTR]		= mmTPC1_RTR_FUNNEL_BASE,
	[GOYA_FUNNEL_TPC2_EML]		= mmTPC2_EML_FUNNEL_BASE,
	[GOYA_FUNNEL_TPC2_RTR]		= mmTPC2_RTR_FUNNEL_BASE,
	[GOYA_FUNNEL_TPC3_EML]		= mmTPC3_EML_FUNNEL_BASE,
	[GOYA_FUNNEL_TPC3_RTR]		= mmTPC3_RTR_FUNNEL_BASE,
	[GOYA_FUNNEL_TPC4_EML]		= mmTPC4_EML_FUNNEL_BASE,
	[GOYA_FUNNEL_TPC4_RTR]		= mmTPC4_RTR_FUNNEL_BASE,
	[GOYA_FUNNEL_TPC5_EML]		= mmTPC5_EML_FUNNEL_BASE,
	[GOYA_FUNNEL_TPC5_RTR]		= mmTPC5_RTR_FUNNEL_BASE,
	[GOYA_FUNNEL_TPC6_EML]		= mmTPC6_EML_FUNNEL_BASE,
	[GOYA_FUNNEL_TPC6_RTR]		= mmTPC6_RTR_FUNNEL_BASE,
	[GOYA_FUNNEL_TPC7_EML]		= mmTPC7_EML_FUNNEL_BASE
पूर्ण;

अटल u64 debug_bmon_regs[GOYA_BMON_LAST + 1] = अणु
	[GOYA_BMON_CPU_RD]		= mmCPU_RD_BMON_BASE,
	[GOYA_BMON_CPU_WR]		= mmCPU_WR_BMON_BASE,
	[GOYA_BMON_DMA_CH_0_0]		= mmDMA_CH_0_BMON_0_BASE,
	[GOYA_BMON_DMA_CH_0_1]		= mmDMA_CH_0_BMON_1_BASE,
	[GOYA_BMON_DMA_CH_1_0]		= mmDMA_CH_1_BMON_0_BASE,
	[GOYA_BMON_DMA_CH_1_1]		= mmDMA_CH_1_BMON_1_BASE,
	[GOYA_BMON_DMA_CH_2_0]		= mmDMA_CH_2_BMON_0_BASE,
	[GOYA_BMON_DMA_CH_2_1]		= mmDMA_CH_2_BMON_1_BASE,
	[GOYA_BMON_DMA_CH_3_0]		= mmDMA_CH_3_BMON_0_BASE,
	[GOYA_BMON_DMA_CH_3_1]		= mmDMA_CH_3_BMON_1_BASE,
	[GOYA_BMON_DMA_CH_4_0]		= mmDMA_CH_4_BMON_0_BASE,
	[GOYA_BMON_DMA_CH_4_1]		= mmDMA_CH_4_BMON_1_BASE,
	[GOYA_BMON_DMA_MACRO_0]		= mmDMA_MACRO_BMON_0_BASE,
	[GOYA_BMON_DMA_MACRO_1]		= mmDMA_MACRO_BMON_1_BASE,
	[GOYA_BMON_DMA_MACRO_2]		= mmDMA_MACRO_BMON_2_BASE,
	[GOYA_BMON_DMA_MACRO_3]		= mmDMA_MACRO_BMON_3_BASE,
	[GOYA_BMON_DMA_MACRO_4]		= mmDMA_MACRO_BMON_4_BASE,
	[GOYA_BMON_DMA_MACRO_5]		= mmDMA_MACRO_BMON_5_BASE,
	[GOYA_BMON_DMA_MACRO_6]		= mmDMA_MACRO_BMON_6_BASE,
	[GOYA_BMON_DMA_MACRO_7]		= mmDMA_MACRO_BMON_7_BASE,
	[GOYA_BMON_MME1_SBA_0]		= mmMME1_SBA_BMON0_BASE,
	[GOYA_BMON_MME1_SBA_1]		= mmMME1_SBA_BMON1_BASE,
	[GOYA_BMON_MME3_SBB_0]		= mmMME3_SBB_BMON0_BASE,
	[GOYA_BMON_MME3_SBB_1]		= mmMME3_SBB_BMON1_BASE,
	[GOYA_BMON_MME4_WACS2_0]	= mmMME4_WACS2_BMON0_BASE,
	[GOYA_BMON_MME4_WACS2_1]	= mmMME4_WACS2_BMON1_BASE,
	[GOYA_BMON_MME4_WACS2_2]	= mmMME4_WACS2_BMON2_BASE,
	[GOYA_BMON_MME4_WACS_0]		= mmMME4_WACS_BMON0_BASE,
	[GOYA_BMON_MME4_WACS_1]		= mmMME4_WACS_BMON1_BASE,
	[GOYA_BMON_MME4_WACS_2]		= mmMME4_WACS_BMON2_BASE,
	[GOYA_BMON_MME4_WACS_3]		= mmMME4_WACS_BMON3_BASE,
	[GOYA_BMON_MME4_WACS_4]		= mmMME4_WACS_BMON4_BASE,
	[GOYA_BMON_MME4_WACS_5]		= mmMME4_WACS_BMON5_BASE,
	[GOYA_BMON_MME4_WACS_6]		= mmMME4_WACS_BMON6_BASE,
	[GOYA_BMON_MMU_0]		= mmMMU_BMON_0_BASE,
	[GOYA_BMON_MMU_1]		= mmMMU_BMON_1_BASE,
	[GOYA_BMON_PCIE_MSTR_RD]	= mmPCIE_BMON_MSTR_RD_BASE,
	[GOYA_BMON_PCIE_MSTR_WR]	= mmPCIE_BMON_MSTR_WR_BASE,
	[GOYA_BMON_PCIE_SLV_RD]		= mmPCIE_BMON_SLV_RD_BASE,
	[GOYA_BMON_PCIE_SLV_WR]		= mmPCIE_BMON_SLV_WR_BASE,
	[GOYA_BMON_TPC0_EML_0]		= mmTPC0_EML_BUSMON_0_BASE,
	[GOYA_BMON_TPC0_EML_1]		= mmTPC0_EML_BUSMON_1_BASE,
	[GOYA_BMON_TPC0_EML_2]		= mmTPC0_EML_BUSMON_2_BASE,
	[GOYA_BMON_TPC0_EML_3]		= mmTPC0_EML_BUSMON_3_BASE,
	[GOYA_BMON_TPC1_EML_0]		= mmTPC1_EML_BUSMON_0_BASE,
	[GOYA_BMON_TPC1_EML_1]		= mmTPC1_EML_BUSMON_1_BASE,
	[GOYA_BMON_TPC1_EML_2]		= mmTPC1_EML_BUSMON_2_BASE,
	[GOYA_BMON_TPC1_EML_3]		= mmTPC1_EML_BUSMON_3_BASE,
	[GOYA_BMON_TPC2_EML_0]		= mmTPC2_EML_BUSMON_0_BASE,
	[GOYA_BMON_TPC2_EML_1]		= mmTPC2_EML_BUSMON_1_BASE,
	[GOYA_BMON_TPC2_EML_2]		= mmTPC2_EML_BUSMON_2_BASE,
	[GOYA_BMON_TPC2_EML_3]		= mmTPC2_EML_BUSMON_3_BASE,
	[GOYA_BMON_TPC3_EML_0]		= mmTPC3_EML_BUSMON_0_BASE,
	[GOYA_BMON_TPC3_EML_1]		= mmTPC3_EML_BUSMON_1_BASE,
	[GOYA_BMON_TPC3_EML_2]		= mmTPC3_EML_BUSMON_2_BASE,
	[GOYA_BMON_TPC3_EML_3]		= mmTPC3_EML_BUSMON_3_BASE,
	[GOYA_BMON_TPC4_EML_0]		= mmTPC4_EML_BUSMON_0_BASE,
	[GOYA_BMON_TPC4_EML_1]		= mmTPC4_EML_BUSMON_1_BASE,
	[GOYA_BMON_TPC4_EML_2]		= mmTPC4_EML_BUSMON_2_BASE,
	[GOYA_BMON_TPC4_EML_3]		= mmTPC4_EML_BUSMON_3_BASE,
	[GOYA_BMON_TPC5_EML_0]		= mmTPC5_EML_BUSMON_0_BASE,
	[GOYA_BMON_TPC5_EML_1]		= mmTPC5_EML_BUSMON_1_BASE,
	[GOYA_BMON_TPC5_EML_2]		= mmTPC5_EML_BUSMON_2_BASE,
	[GOYA_BMON_TPC5_EML_3]		= mmTPC5_EML_BUSMON_3_BASE,
	[GOYA_BMON_TPC6_EML_0]		= mmTPC6_EML_BUSMON_0_BASE,
	[GOYA_BMON_TPC6_EML_1]		= mmTPC6_EML_BUSMON_1_BASE,
	[GOYA_BMON_TPC6_EML_2]		= mmTPC6_EML_BUSMON_2_BASE,
	[GOYA_BMON_TPC6_EML_3]		= mmTPC6_EML_BUSMON_3_BASE,
	[GOYA_BMON_TPC7_EML_0]		= mmTPC7_EML_BUSMON_0_BASE,
	[GOYA_BMON_TPC7_EML_1]		= mmTPC7_EML_BUSMON_1_BASE,
	[GOYA_BMON_TPC7_EML_2]		= mmTPC7_EML_BUSMON_2_BASE,
	[GOYA_BMON_TPC7_EML_3]		= mmTPC7_EML_BUSMON_3_BASE
पूर्ण;

अटल u64 debug_spmu_regs[GOYA_SPMU_LAST + 1] = अणु
	[GOYA_SPMU_DMA_CH_0_CS]		= mmDMA_CH_0_CS_SPMU_BASE,
	[GOYA_SPMU_DMA_CH_1_CS]		= mmDMA_CH_1_CS_SPMU_BASE,
	[GOYA_SPMU_DMA_CH_2_CS]		= mmDMA_CH_2_CS_SPMU_BASE,
	[GOYA_SPMU_DMA_CH_3_CS]		= mmDMA_CH_3_CS_SPMU_BASE,
	[GOYA_SPMU_DMA_CH_4_CS]		= mmDMA_CH_4_CS_SPMU_BASE,
	[GOYA_SPMU_DMA_MACRO_CS]	= mmDMA_MACRO_CS_SPMU_BASE,
	[GOYA_SPMU_MME1_SBA]		= mmMME1_SBA_SPMU_BASE,
	[GOYA_SPMU_MME3_SBB]		= mmMME3_SBB_SPMU_BASE,
	[GOYA_SPMU_MME4_WACS2]		= mmMME4_WACS2_SPMU_BASE,
	[GOYA_SPMU_MME4_WACS]		= mmMME4_WACS_SPMU_BASE,
	[GOYA_SPMU_MMU_CS]		= mmMMU_CS_SPMU_BASE,
	[GOYA_SPMU_PCIE]		= mmPCIE_SPMU_BASE,
	[GOYA_SPMU_TPC0_EML]		= mmTPC0_EML_SPMU_BASE,
	[GOYA_SPMU_TPC1_EML]		= mmTPC1_EML_SPMU_BASE,
	[GOYA_SPMU_TPC2_EML]		= mmTPC2_EML_SPMU_BASE,
	[GOYA_SPMU_TPC3_EML]		= mmTPC3_EML_SPMU_BASE,
	[GOYA_SPMU_TPC4_EML]		= mmTPC4_EML_SPMU_BASE,
	[GOYA_SPMU_TPC5_EML]		= mmTPC5_EML_SPMU_BASE,
	[GOYA_SPMU_TPC6_EML]		= mmTPC6_EML_SPMU_BASE,
	[GOYA_SPMU_TPC7_EML]		= mmTPC7_EML_SPMU_BASE
पूर्ण;

अटल पूर्णांक goya_coresight_समयout(काष्ठा hl_device *hdev, u64 addr,
		पूर्णांक position, bool up)
अणु
	पूर्णांक rc;
	u32 val, समयout_usec;

	अगर (hdev->pldm)
		समयout_usec = GOYA_PLDM_CORESIGHT_TIMEOUT_USEC;
	अन्यथा
		समयout_usec = CORESIGHT_TIMEOUT_USEC;

	rc = hl_poll_समयout(
		hdev,
		addr,
		val,
		up ? val & BIT(position) : !(val & BIT(position)),
		1000,
		समयout_usec);

	अगर (rc) अणु
		dev_err(hdev->dev,
			"Timeout while waiting for coresight, addr: 0x%llx, position: %d, up: %d\n",
				addr, position, up);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक goya_config_sपंचांग(काष्ठा hl_device *hdev,
		काष्ठा hl_debug_params *params)
अणु
	काष्ठा hl_debug_params_sपंचांग *input;
	u64 base_reg;
	u32 frequency;
	पूर्णांक rc;

	अगर (params->reg_idx >= ARRAY_SIZE(debug_sपंचांग_regs)) अणु
		dev_err(hdev->dev, "Invalid register index in STM\n");
		वापस -EINVAL;
	पूर्ण

	base_reg = debug_sपंचांग_regs[params->reg_idx] - CFG_BASE;

	WREG32(base_reg + 0xFB0, CORESIGHT_UNLOCK);

	अगर (params->enable) अणु
		input = params->input;

		अगर (!input)
			वापस -EINVAL;

		WREG32(base_reg + 0xE80, 0x80004);
		WREG32(base_reg + 0xD64, 7);
		WREG32(base_reg + 0xD60, 0);
		WREG32(base_reg + 0xD00, lower_32_bits(input->he_mask));
		WREG32(base_reg + 0xD20, lower_32_bits(input->sp_mask));
		WREG32(base_reg + 0xD60, 1);
		WREG32(base_reg + 0xD00, upper_32_bits(input->he_mask));
		WREG32(base_reg + 0xD20, upper_32_bits(input->sp_mask));
		WREG32(base_reg + 0xE70, 0x10);
		WREG32(base_reg + 0xE60, 0);
		WREG32(base_reg + 0xE64, 0x420000);
		WREG32(base_reg + 0xE00, 0xFFFFFFFF);
		WREG32(base_reg + 0xE20, 0xFFFFFFFF);
		WREG32(base_reg + 0xEF4, input->id);
		WREG32(base_reg + 0xDF4, 0x80);
		frequency = hdev->asic_prop.psoc_बारtamp_frequency;
		अगर (frequency == 0)
			frequency = input->frequency;
		WREG32(base_reg + 0xE8C, frequency);
		WREG32(base_reg + 0xE90, 0x7FF);
		WREG32(base_reg + 0xE80, 0x27 | (input->id << 16));
	पूर्ण अन्यथा अणु
		WREG32(base_reg + 0xE80, 4);
		WREG32(base_reg + 0xD64, 0);
		WREG32(base_reg + 0xD60, 1);
		WREG32(base_reg + 0xD00, 0);
		WREG32(base_reg + 0xD20, 0);
		WREG32(base_reg + 0xD60, 0);
		WREG32(base_reg + 0xE20, 0);
		WREG32(base_reg + 0xE00, 0);
		WREG32(base_reg + 0xDF4, 0x80);
		WREG32(base_reg + 0xE70, 0);
		WREG32(base_reg + 0xE60, 0);
		WREG32(base_reg + 0xE64, 0);
		WREG32(base_reg + 0xE8C, 0);

		rc = goya_coresight_समयout(hdev, base_reg + 0xE80, 23, false);
		अगर (rc) अणु
			dev_err(hdev->dev,
				"Failed to disable STM on timeout, error %d\n",
				rc);
			वापस rc;
		पूर्ण

		WREG32(base_reg + 0xE80, 4);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक goya_config_etf(काष्ठा hl_device *hdev,
		काष्ठा hl_debug_params *params)
अणु
	काष्ठा hl_debug_params_etf *input;
	u64 base_reg;
	u32 val;
	पूर्णांक rc;

	अगर (params->reg_idx >= ARRAY_SIZE(debug_etf_regs)) अणु
		dev_err(hdev->dev, "Invalid register index in ETF\n");
		वापस -EINVAL;
	पूर्ण

	base_reg = debug_etf_regs[params->reg_idx] - CFG_BASE;

	WREG32(base_reg + 0xFB0, CORESIGHT_UNLOCK);

	val = RREG32(base_reg + 0x304);
	val |= 0x1000;
	WREG32(base_reg + 0x304, val);
	val |= 0x40;
	WREG32(base_reg + 0x304, val);

	rc = goya_coresight_समयout(hdev, base_reg + 0x304, 6, false);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to %s ETF on timeout, error %d\n",
				params->enable ? "enable" : "disable", rc);
		वापस rc;
	पूर्ण

	rc = goya_coresight_समयout(hdev, base_reg + 0xC, 2, true);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to %s ETF on timeout, error %d\n",
				params->enable ? "enable" : "disable", rc);
		वापस rc;
	पूर्ण

	WREG32(base_reg + 0x20, 0);

	अगर (params->enable) अणु
		input = params->input;

		अगर (!input)
			वापस -EINVAL;

		WREG32(base_reg + 0x34, 0x3FFC);
		WREG32(base_reg + 0x28, input->sink_mode);
		WREG32(base_reg + 0x304, 0x4001);
		WREG32(base_reg + 0x308, 0xA);
		WREG32(base_reg + 0x20, 1);
	पूर्ण अन्यथा अणु
		WREG32(base_reg + 0x34, 0);
		WREG32(base_reg + 0x28, 0);
		WREG32(base_reg + 0x304, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक goya_etr_validate_address(काष्ठा hl_device *hdev, u64 addr,
		u64 size)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u64 range_start, range_end;

	अगर (addr > (addr + size)) अणु
		dev_err(hdev->dev,
			"ETR buffer size %llu overflow\n", size);
		वापस false;
	पूर्ण

	अगर (hdev->mmu_enable) अणु
		range_start = prop->dmmu.start_addr;
		range_end = prop->dmmu.end_addr;
	पूर्ण अन्यथा अणु
		range_start = prop->dram_user_base_address;
		range_end = prop->dram_end_address;
	पूर्ण

	वापस hl_mem_area_inside_range(addr, size, range_start, range_end);
पूर्ण

अटल पूर्णांक goya_config_etr(काष्ठा hl_device *hdev,
		काष्ठा hl_debug_params *params)
अणु
	काष्ठा hl_debug_params_etr *input;
	u32 val;
	पूर्णांक rc;

	WREG32(mmPSOC_ETR_LAR, CORESIGHT_UNLOCK);

	val = RREG32(mmPSOC_ETR_FFCR);
	val |= 0x1000;
	WREG32(mmPSOC_ETR_FFCR, val);
	val |= 0x40;
	WREG32(mmPSOC_ETR_FFCR, val);

	rc = goya_coresight_समयout(hdev, mmPSOC_ETR_FFCR, 6, false);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to %s ETR on timeout, error %d\n",
				params->enable ? "enable" : "disable", rc);
		वापस rc;
	पूर्ण

	rc = goya_coresight_समयout(hdev, mmPSOC_ETR_STS, 2, true);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to %s ETR on timeout, error %d\n",
				params->enable ? "enable" : "disable", rc);
		वापस rc;
	पूर्ण

	WREG32(mmPSOC_ETR_CTL, 0);

	अगर (params->enable) अणु
		input = params->input;

		अगर (!input)
			वापस -EINVAL;

		अगर (input->buffer_size == 0) अणु
			dev_err(hdev->dev,
				"ETR buffer size should be bigger than 0\n");
			वापस -EINVAL;
		पूर्ण

		अगर (!goya_etr_validate_address(hdev,
				input->buffer_address, input->buffer_size)) अणु
			dev_err(hdev->dev, "buffer address is not valid\n");
			वापस -EINVAL;
		पूर्ण

		WREG32(mmPSOC_ETR_BUFWM, 0x3FFC);
		WREG32(mmPSOC_ETR_RSZ, input->buffer_size);
		WREG32(mmPSOC_ETR_MODE, input->sink_mode);
		अगर (hdev->asic_prop.fw_security_disabled) अणु
			/* make ETR not privileged */
			val = FIELD_PREP(PSOC_ETR_AXICTL_PROTCTRLBIT0_MASK, 0);
			/* make ETR non-secured (inverted logic) */
			val |= FIELD_PREP(PSOC_ETR_AXICTL_PROTCTRLBIT1_MASK, 1);
			/* burst size 8 */
			val |= FIELD_PREP(PSOC_ETR_AXICTL_WRBURSTLEN_MASK, 7);
			WREG32(mmPSOC_ETR_AXICTL, val);
		पूर्ण
		WREG32(mmPSOC_ETR_DBALO,
				lower_32_bits(input->buffer_address));
		WREG32(mmPSOC_ETR_DBAHI,
				upper_32_bits(input->buffer_address));
		WREG32(mmPSOC_ETR_FFCR, 3);
		WREG32(mmPSOC_ETR_PSCR, 0xA);
		WREG32(mmPSOC_ETR_CTL, 1);
	पूर्ण अन्यथा अणु
		WREG32(mmPSOC_ETR_BUFWM, 0);
		WREG32(mmPSOC_ETR_RSZ, 0x400);
		WREG32(mmPSOC_ETR_DBALO, 0);
		WREG32(mmPSOC_ETR_DBAHI, 0);
		WREG32(mmPSOC_ETR_PSCR, 0);
		WREG32(mmPSOC_ETR_MODE, 0);
		WREG32(mmPSOC_ETR_FFCR, 0);

		अगर (params->output_size >= माप(u64)) अणु
			u32 rwp, rwphi;

			/*
			 * The trace buffer address is 40 bits wide. The end of
			 * the buffer is set in the RWP रेजिस्टर (lower 32
			 * bits), and in the RWPHI रेजिस्टर (upper 8 bits).
			 */
			rwp = RREG32(mmPSOC_ETR_RWP);
			rwphi = RREG32(mmPSOC_ETR_RWPHI) & 0xff;
			*(u64 *) params->output = ((u64) rwphi << 32) | rwp;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक goya_config_funnel(काष्ठा hl_device *hdev,
		काष्ठा hl_debug_params *params)
अणु
	u64 base_reg;

	अगर (params->reg_idx >= ARRAY_SIZE(debug_funnel_regs)) अणु
		dev_err(hdev->dev, "Invalid register index in FUNNEL\n");
		वापस -EINVAL;
	पूर्ण

	base_reg = debug_funnel_regs[params->reg_idx] - CFG_BASE;

	WREG32(base_reg + 0xFB0, CORESIGHT_UNLOCK);

	WREG32(base_reg, params->enable ? 0x33F : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक goya_config_bmon(काष्ठा hl_device *hdev,
		काष्ठा hl_debug_params *params)
अणु
	काष्ठा hl_debug_params_bmon *input;
	u64 base_reg;
	u32 pcie_base = 0;

	अगर (params->reg_idx >= ARRAY_SIZE(debug_bmon_regs)) अणु
		dev_err(hdev->dev, "Invalid register index in BMON\n");
		वापस -EINVAL;
	पूर्ण

	base_reg = debug_bmon_regs[params->reg_idx] - CFG_BASE;

	WREG32(base_reg + 0x104, 1);

	अगर (params->enable) अणु
		input = params->input;

		अगर (!input)
			वापस -EINVAL;

		WREG32(base_reg + 0x200, lower_32_bits(input->start_addr0));
		WREG32(base_reg + 0x204, upper_32_bits(input->start_addr0));
		WREG32(base_reg + 0x208, lower_32_bits(input->addr_mask0));
		WREG32(base_reg + 0x20C, upper_32_bits(input->addr_mask0));
		WREG32(base_reg + 0x240, lower_32_bits(input->start_addr1));
		WREG32(base_reg + 0x244, upper_32_bits(input->start_addr1));
		WREG32(base_reg + 0x248, lower_32_bits(input->addr_mask1));
		WREG32(base_reg + 0x24C, upper_32_bits(input->addr_mask1));
		WREG32(base_reg + 0x224, 0);
		WREG32(base_reg + 0x234, 0);
		WREG32(base_reg + 0x30C, input->bw_win);
		WREG32(base_reg + 0x308, input->win_capture);

		/* PCIE IF BMON bug WA */
		अगर (params->reg_idx != GOYA_BMON_PCIE_MSTR_RD &&
				params->reg_idx != GOYA_BMON_PCIE_MSTR_WR &&
				params->reg_idx != GOYA_BMON_PCIE_SLV_RD &&
				params->reg_idx != GOYA_BMON_PCIE_SLV_WR)
			pcie_base = 0xA000000;

		WREG32(base_reg + 0x700, pcie_base | 0xB00 | (input->id << 12));
		WREG32(base_reg + 0x708, pcie_base | 0xA00 | (input->id << 12));
		WREG32(base_reg + 0x70C, pcie_base | 0xC00 | (input->id << 12));

		WREG32(base_reg + 0x100, 0x11);
		WREG32(base_reg + 0x304, 0x1);
	पूर्ण अन्यथा अणु
		WREG32(base_reg + 0x200, 0);
		WREG32(base_reg + 0x204, 0);
		WREG32(base_reg + 0x208, 0xFFFFFFFF);
		WREG32(base_reg + 0x20C, 0xFFFFFFFF);
		WREG32(base_reg + 0x240, 0);
		WREG32(base_reg + 0x244, 0);
		WREG32(base_reg + 0x248, 0xFFFFFFFF);
		WREG32(base_reg + 0x24C, 0xFFFFFFFF);
		WREG32(base_reg + 0x224, 0xFFFFFFFF);
		WREG32(base_reg + 0x234, 0x1070F);
		WREG32(base_reg + 0x30C, 0);
		WREG32(base_reg + 0x308, 0xFFFF);
		WREG32(base_reg + 0x700, 0xA000B00);
		WREG32(base_reg + 0x708, 0xA000A00);
		WREG32(base_reg + 0x70C, 0xA000C00);
		WREG32(base_reg + 0x100, 1);
		WREG32(base_reg + 0x304, 0);
		WREG32(base_reg + 0x104, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक goya_config_spmu(काष्ठा hl_device *hdev,
		काष्ठा hl_debug_params *params)
अणु
	u64 base_reg;
	काष्ठा hl_debug_params_spmu *input = params->input;
	u64 *output;
	u32 output_arr_len;
	u32 events_num;
	u32 overflow_idx;
	u32 cycle_cnt_idx;
	पूर्णांक i;

	अगर (params->reg_idx >= ARRAY_SIZE(debug_spmu_regs)) अणु
		dev_err(hdev->dev, "Invalid register index in SPMU\n");
		वापस -EINVAL;
	पूर्ण

	base_reg = debug_spmu_regs[params->reg_idx] - CFG_BASE;

	अगर (params->enable) अणु
		input = params->input;

		अगर (!input)
			वापस -EINVAL;

		अगर (input->event_types_num < 3) अणु
			dev_err(hdev->dev,
				"not enough event types values for SPMU enable\n");
			वापस -EINVAL;
		पूर्ण

		अगर (input->event_types_num > SPMU_MAX_COUNTERS) अणु
			dev_err(hdev->dev,
				"too many event types values for SPMU enable\n");
			वापस -EINVAL;
		पूर्ण

		WREG32(base_reg + 0xE04, 0x41013046);
		WREG32(base_reg + 0xE04, 0x41013040);

		क्रम (i = 0 ; i < input->event_types_num ; i++)
			WREG32(base_reg + SPMU_EVENT_TYPES_OFFSET + i * 4,
				input->event_types[i]);

		WREG32(base_reg + 0xE04, 0x41013041);
		WREG32(base_reg + 0xC00, 0x8000003F);
	पूर्ण अन्यथा अणु
		output = params->output;
		output_arr_len = params->output_size / 8;
		events_num = output_arr_len - 2;
		overflow_idx = output_arr_len - 2;
		cycle_cnt_idx = output_arr_len - 1;

		अगर (!output)
			वापस -EINVAL;

		अगर (output_arr_len < 3) अणु
			dev_err(hdev->dev,
				"not enough values for SPMU disable\n");
			वापस -EINVAL;
		पूर्ण

		अगर (events_num > SPMU_MAX_COUNTERS) अणु
			dev_err(hdev->dev,
				"too many events values for SPMU disable\n");
			वापस -EINVAL;
		पूर्ण

		WREG32(base_reg + 0xE04, 0x41013040);

		क्रम (i = 0 ; i < events_num ; i++)
			output[i] = RREG32(base_reg + i * 8);

		output[overflow_idx] = RREG32(base_reg + 0xCC0);

		output[cycle_cnt_idx] = RREG32(base_reg + 0xFC);
		output[cycle_cnt_idx] <<= 32;
		output[cycle_cnt_idx] |= RREG32(base_reg + 0xF8);

		WREG32(base_reg + 0xCC0, 0);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक goya_debug_coresight(काष्ठा hl_device *hdev, व्योम *data)
अणु
	काष्ठा hl_debug_params *params = data;
	पूर्णांक rc = 0;

	चयन (params->op) अणु
	हाल HL_DEBUG_OP_STM:
		rc = goya_config_sपंचांग(hdev, params);
		अवरोध;
	हाल HL_DEBUG_OP_ETF:
		rc = goya_config_etf(hdev, params);
		अवरोध;
	हाल HL_DEBUG_OP_ETR:
		rc = goya_config_etr(hdev, params);
		अवरोध;
	हाल HL_DEBUG_OP_FUNNEL:
		rc = goya_config_funnel(hdev, params);
		अवरोध;
	हाल HL_DEBUG_OP_BMON:
		rc = goya_config_bmon(hdev, params);
		अवरोध;
	हाल HL_DEBUG_OP_SPMU:
		rc = goya_config_spmu(hdev, params);
		अवरोध;
	हाल HL_DEBUG_OP_TIMESTAMP:
		/* Do nothing as this opcode is deprecated */
		अवरोध;

	शेष:
		dev_err(hdev->dev, "Unknown coresight id %d\n", params->op);
		वापस -EINVAL;
	पूर्ण

	/* Perक्रमm पढ़ो from the device to flush all configuration */
	RREG32(mmPCIE_DBI_DEVICE_ID_VENDOR_ID_REG);

	वापस rc;
पूर्ण

व्योम goya_halt_coresight(काष्ठा hl_device *hdev)
अणु
	काष्ठा hl_debug_params params = अणुपूर्ण;
	पूर्णांक i, rc;

	क्रम (i = GOYA_ETF_FIRST ; i <= GOYA_ETF_LAST ; i++) अणु
		params.reg_idx = i;
		rc = goya_config_etf(hdev, &params);
		अगर (rc)
			dev_err(hdev->dev, "halt ETF failed, %d/%d\n", rc, i);
	पूर्ण

	rc = goya_config_etr(hdev, &params);
	अगर (rc)
		dev_err(hdev->dev, "halt ETR failed, %d\n", rc);
पूर्ण
