<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित __SOC_MEDIATEK_MT8167_PM_DOMAINS_H
#घोषणा __SOC_MEDIATEK_MT8167_PM_DOMAINS_H

#समावेश "mtk-pm-domains.h"
#समावेश <dt-bindings/घातer/mt8167-घातer.h>

#घोषणा MT8167_PWR_STATUS_MFG_2D	BIT(24)
#घोषणा MT8167_PWR_STATUS_MFG_ASYNC	BIT(25)

/*
 * MT8167 घातer करोमुख्य support
 */

अटल स्थिर काष्ठा scpsys_करोमुख्य_data scpsys_करोमुख्य_data_mt8167[] = अणु
	[MT8167_POWER_DOMAIN_MM] = अणु
		.name = "mm",
		.sta_mask = PWR_STATUS_DISP,
		.ctl_offs = SPM_DIS_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
		.bp_infracfg = अणु
			BUS_PROT_UPDATE_TOPAXI(MT8167_TOP_AXI_PROT_EN_MM_EMI |
					       MT8167_TOP_AXI_PROT_EN_MCU_MM),
		पूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT8167_POWER_DOMAIN_VDEC] = अणु
		.name = "vdec",
		.sta_mask = PWR_STATUS_VDEC,
		.ctl_offs = SPM_VDE_PWR_CON,
		.sram_pdn_bits = GENMASK(8, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT8167_POWER_DOMAIN_ISP] = अणु
		.name = "isp",
		.sta_mask = PWR_STATUS_ISP,
		.ctl_offs = SPM_ISP_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(13, 12),
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT8167_POWER_DOMAIN_MFG_ASYNC] = अणु
		.name = "mfg_async",
		.sta_mask = MT8167_PWR_STATUS_MFG_ASYNC,
		.ctl_offs = SPM_MFG_ASYNC_PWR_CON,
		.sram_pdn_bits = 0,
		.sram_pdn_ack_bits = 0,
		.bp_infracfg = अणु
			BUS_PROT_UPDATE_TOPAXI(MT8167_TOP_AXI_PROT_EN_MCU_MFG |
					       MT8167_TOP_AXI_PROT_EN_MFG_EMI),
		पूर्ण,
	पूर्ण,
	[MT8167_POWER_DOMAIN_MFG_2D] = अणु
		.name = "mfg_2d",
		.sta_mask = MT8167_PWR_STATUS_MFG_2D,
		.ctl_offs = SPM_MFG_2D_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
	पूर्ण,
	[MT8167_POWER_DOMAIN_MFG] = अणु
		.name = "mfg",
		.sta_mask = PWR_STATUS_MFG,
		.ctl_offs = SPM_MFG_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
	पूर्ण,
	[MT8167_POWER_DOMAIN_CONN] = अणु
		.name = "conn",
		.sta_mask = PWR_STATUS_CONN,
		.ctl_offs = SPM_CONN_PWR_CON,
		.sram_pdn_bits = GENMASK(8, 8),
		.sram_pdn_ack_bits = 0,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
		.bp_infracfg = अणु
			BUS_PROT_UPDATE_TOPAXI(MT8167_TOP_AXI_PROT_EN_CONN_EMI |
					       MT8167_TOP_AXI_PROT_EN_CONN_MCU |
					       MT8167_TOP_AXI_PROT_EN_MCU_CONN),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा scpsys_soc_data mt8167_scpsys_data = अणु
	.करोमुख्यs_data = scpsys_करोमुख्य_data_mt8167,
	.num_करोमुख्यs = ARRAY_SIZE(scpsys_करोमुख्य_data_mt8167),
	.pwr_sta_offs = SPM_PWR_STATUS,
	.pwr_sta2nd_offs = SPM_PWR_STATUS_2ND,
पूर्ण;

#पूर्ण_अगर /* __SOC_MEDIATEK_MT8167_PM_DOMAINS_H */

