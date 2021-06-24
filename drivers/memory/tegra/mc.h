<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 NVIDIA CORPORATION.  All rights reserved.
 */

#अगर_अघोषित MEMORY_TEGRA_MC_H
#घोषणा MEMORY_TEGRA_MC_H

#समावेश <linux/bits.h>
#समावेश <linux/पन.स>
#समावेश <linux/types.h>

#समावेश <soc/tegra/mc.h>

#घोषणा MC_INTSTATUS					0x00
#घोषणा MC_INTMASK					0x04
#घोषणा MC_ERR_STATUS					0x08
#घोषणा MC_ERR_ADR					0x0c
#घोषणा MC_GART_ERROR_REQ				0x30
#घोषणा MC_EMEM_ADR_CFG					0x54
#घोषणा MC_DECERR_EMEM_OTHERS_STATUS			0x58
#घोषणा MC_SECURITY_VIOLATION_STATUS			0x74
#घोषणा MC_EMEM_ARB_CFG					0x90
#घोषणा MC_EMEM_ARB_OUTSTANDING_REQ			0x94
#घोषणा MC_EMEM_ARB_TIMING_RCD				0x98
#घोषणा MC_EMEM_ARB_TIMING_RP				0x9c
#घोषणा MC_EMEM_ARB_TIMING_RC				0xa0
#घोषणा MC_EMEM_ARB_TIMING_RAS				0xa4
#घोषणा MC_EMEM_ARB_TIMING_FAW				0xa8
#घोषणा MC_EMEM_ARB_TIMING_RRD				0xac
#घोषणा MC_EMEM_ARB_TIMING_RAP2PRE			0xb0
#घोषणा MC_EMEM_ARB_TIMING_WAP2PRE			0xb4
#घोषणा MC_EMEM_ARB_TIMING_R2R				0xb8
#घोषणा MC_EMEM_ARB_TIMING_W2W				0xbc
#घोषणा MC_EMEM_ARB_TIMING_R2W				0xc0
#घोषणा MC_EMEM_ARB_TIMING_W2R				0xc4
#घोषणा MC_EMEM_ARB_MISC2				0xc8
#घोषणा MC_EMEM_ARB_DA_TURNS				0xd0
#घोषणा MC_EMEM_ARB_DA_COVERS				0xd4
#घोषणा MC_EMEM_ARB_MISC0				0xd8
#घोषणा MC_EMEM_ARB_MISC1				0xdc
#घोषणा MC_EMEM_ARB_RING1_THROTTLE			0xe0
#घोषणा MC_EMEM_ARB_OVERRIDE				0xe8
#घोषणा MC_TIMING_CONTROL_DBG				0xf8
#घोषणा MC_TIMING_CONTROL				0xfc

#घोषणा MC_INT_DECERR_MTS				BIT(16)
#घोषणा MC_INT_SECERR_SEC				BIT(13)
#घोषणा MC_INT_DECERR_VPR				BIT(12)
#घोषणा MC_INT_INVALID_APB_ASID_UPDATE			BIT(11)
#घोषणा MC_INT_INVALID_SMMU_PAGE			BIT(10)
#घोषणा MC_INT_ARBITRATION_EMEM				BIT(9)
#घोषणा MC_INT_SECURITY_VIOLATION			BIT(8)
#घोषणा MC_INT_INVALID_GART_PAGE			BIT(7)
#घोषणा MC_INT_DECERR_EMEM				BIT(6)

#घोषणा MC_ERR_STATUS_TYPE_SHIFT			28
#घोषणा MC_ERR_STATUS_TYPE_INVALID_SMMU_PAGE		(0x6 << 28)
#घोषणा MC_ERR_STATUS_TYPE_MASK				(0x7 << 28)
#घोषणा MC_ERR_STATUS_READABLE				BIT(27)
#घोषणा MC_ERR_STATUS_WRITABLE				BIT(26)
#घोषणा MC_ERR_STATUS_NONSECURE				BIT(25)
#घोषणा MC_ERR_STATUS_ADR_HI_SHIFT			20
#घोषणा MC_ERR_STATUS_ADR_HI_MASK			0x3
#घोषणा MC_ERR_STATUS_SECURITY				BIT(17)
#घोषणा MC_ERR_STATUS_RW				BIT(16)

#घोषणा MC_EMEM_ADR_CFG_EMEM_NUMDEV			BIT(0)

#घोषणा MC_EMEM_ARB_CFG_CYCLES_PER_UPDATE(x)		((x) & 0x1ff)
#घोषणा MC_EMEM_ARB_CFG_CYCLES_PER_UPDATE_MASK		0x1ff

#घोषणा MC_EMEM_ARB_OUTSTANDING_REQ_MAX_MASK		0x1ff
#घोषणा MC_EMEM_ARB_OUTSTANDING_REQ_HOLDOFF_OVERRIDE	BIT(30)
#घोषणा MC_EMEM_ARB_OUTSTANDING_REQ_LIMIT_ENABLE	BIT(31)

#घोषणा MC_EMEM_ARB_OVERRIDE_EACK_MASK			0x3

#घोषणा MC_TIMING_UPDATE				BIT(0)

अटल अंतरभूत u32 tegra_mc_scale_percents(u64 val, अचिन्हित पूर्णांक percents)
अणु
	val = val * percents;
	करो_भाग(val, 100);

	वापस min_t(u64, val, U32_MAX);
पूर्ण

अटल अंतरभूत काष्ठा tegra_mc *
icc_provider_to_tegra_mc(काष्ठा icc_provider *provider)
अणु
	वापस container_of(provider, काष्ठा tegra_mc, provider);
पूर्ण

अटल अंतरभूत u32 mc_पढ़ोl(स्थिर काष्ठा tegra_mc *mc, अचिन्हित दीर्घ offset)
अणु
	वापस पढ़ोl_relaxed(mc->regs + offset);
पूर्ण

अटल अंतरभूत व्योम mc_ग_लिखोl(स्थिर काष्ठा tegra_mc *mc, u32 value,
			     अचिन्हित दीर्घ offset)
अणु
	ग_लिखोl_relaxed(value, mc->regs + offset);
पूर्ण

बाह्य स्थिर काष्ठा tegra_mc_reset_ops tegra_mc_reset_ops_common;

#अगर_घोषित CONFIG_ARCH_TEGRA_2x_SOC
बाह्य स्थिर काष्ठा tegra_mc_soc tegra20_mc_soc;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_3x_SOC
बाह्य स्थिर काष्ठा tegra_mc_soc tegra30_mc_soc;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_114_SOC
बाह्य स्थिर काष्ठा tegra_mc_soc tegra114_mc_soc;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_124_SOC
बाह्य स्थिर काष्ठा tegra_mc_soc tegra124_mc_soc;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_132_SOC
बाह्य स्थिर काष्ठा tegra_mc_soc tegra132_mc_soc;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_210_SOC
बाह्य स्थिर काष्ठा tegra_mc_soc tegra210_mc_soc;
#पूर्ण_अगर

/*
 * These IDs are क्रम पूर्णांकernal use of Tegra ICC drivers. The ID numbers are
 * chosen such that they करोn't conflict with the device-tree ICC node IDs.
 */
#घोषणा TEGRA_ICC_MC		1000
#घोषणा TEGRA_ICC_EMC		1001
#घोषणा TEGRA_ICC_EMEM		1002

#पूर्ण_अगर /* MEMORY_TEGRA_MC_H */
