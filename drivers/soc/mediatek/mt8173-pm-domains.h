<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित __SOC_MEDIATEK_MT8173_PM_DOMAINS_H
#घोषणा __SOC_MEDIATEK_MT8173_PM_DOMAINS_H

#समावेश "mtk-pm-domains.h"
#समावेश <dt-bindings/घातer/mt8173-घातer.h>

/*
 * MT8173 घातer करोमुख्य support
 */

अटल स्थिर काष्ठा scpsys_करोमुख्य_data scpsys_करोमुख्य_data_mt8173[] = अणु
	[MT8173_POWER_DOMAIN_VDEC] = अणु
		.name = "vdec",
		.sta_mask = PWR_STATUS_VDEC,
		.ctl_offs = SPM_VDE_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
	पूर्ण,
	[MT8173_POWER_DOMAIN_VENC] = अणु
		.name = "venc",
		.sta_mask = PWR_STATUS_VENC,
		.ctl_offs = SPM_VEN_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
	पूर्ण,
	[MT8173_POWER_DOMAIN_ISP] = अणु
		.name = "isp",
		.sta_mask = PWR_STATUS_ISP,
		.ctl_offs = SPM_ISP_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(13, 12),
	पूर्ण,
	[MT8173_POWER_DOMAIN_MM] = अणु
		.name = "mm",
		.sta_mask = PWR_STATUS_DISP,
		.ctl_offs = SPM_DIS_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
		.bp_infracfg = अणु
			BUS_PROT_UPDATE_TOPAXI(MT8173_TOP_AXI_PROT_EN_MM_M0 |
					       MT8173_TOP_AXI_PROT_EN_MM_M1),
		पूर्ण,
	पूर्ण,
	[MT8173_POWER_DOMAIN_VENC_LT] = अणु
		.name = "venc_lt",
		.sta_mask = PWR_STATUS_VENC_LT,
		.ctl_offs = SPM_VEN2_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
	पूर्ण,
	[MT8173_POWER_DOMAIN_AUDIO] = अणु
		.name = "audio",
		.sta_mask = PWR_STATUS_AUDIO,
		.ctl_offs = SPM_AUDIO_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
	पूर्ण,
	[MT8173_POWER_DOMAIN_USB] = अणु
		.name = "usb",
		.sta_mask = PWR_STATUS_USB,
		.ctl_offs = SPM_USB_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT8173_POWER_DOMAIN_MFG_ASYNC] = अणु
		.name = "mfg_async",
		.sta_mask = PWR_STATUS_MFG_ASYNC,
		.ctl_offs = SPM_MFG_ASYNC_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = 0,
	पूर्ण,
	[MT8173_POWER_DOMAIN_MFG_2D] = अणु
		.name = "mfg_2d",
		.sta_mask = PWR_STATUS_MFG_2D,
		.ctl_offs = SPM_MFG_2D_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(13, 12),
	पूर्ण,
	[MT8173_POWER_DOMAIN_MFG] = अणु
		.name = "mfg",
		.sta_mask = PWR_STATUS_MFG,
		.ctl_offs = SPM_MFG_PWR_CON,
		.sram_pdn_bits = GENMASK(13, 8),
		.sram_pdn_ack_bits = GENMASK(21, 16),
		.bp_infracfg = अणु
			BUS_PROT_UPDATE_TOPAXI(MT8173_TOP_AXI_PROT_EN_MFG_S |
					       MT8173_TOP_AXI_PROT_EN_MFG_M0 |
					       MT8173_TOP_AXI_PROT_EN_MFG_M1 |
					       MT8173_TOP_AXI_PROT_EN_MFG_SNOOP_OUT),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा scpsys_soc_data mt8173_scpsys_data = अणु
	.करोमुख्यs_data = scpsys_करोमुख्य_data_mt8173,
	.num_करोमुख्यs = ARRAY_SIZE(scpsys_करोमुख्य_data_mt8173),
	.pwr_sta_offs = SPM_PWR_STATUS,
	.pwr_sta2nd_offs = SPM_PWR_STATUS_2ND,
पूर्ण;

#पूर्ण_अगर /* __SOC_MEDIATEK_MT8173_PM_DOMAINS_H */
