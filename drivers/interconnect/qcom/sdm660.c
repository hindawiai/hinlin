<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Qualcomm SDM630/SDM636/SDM660 Network-on-Chip (NoC) QoS driver
 * Copyright (C) 2020, AngeloGioacchino Del Regno <kholk11@gmail.com>
 */

#समावेश <dt-bindings/पूर्णांकerconnect/qcom,sdm660.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerconnect-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश "smd-rpm.h"

#घोषणा RPM_BUS_MASTER_REQ	0x73616d62
#घोषणा RPM_BUS_SLAVE_REQ	0x766c7362

/* BIMC QoS */
#घोषणा M_BKE_REG_BASE(n)		(0x300 + (0x4000 * n))
#घोषणा M_BKE_EN_ADDR(n)		(M_BKE_REG_BASE(n))
#घोषणा M_BKE_HEALTH_CFG_ADDR(i, n)	(M_BKE_REG_BASE(n) + 0x40 + (0x4 * i))

#घोषणा M_BKE_HEALTH_CFG_LIMITCMDS_MASK	0x80000000
#घोषणा M_BKE_HEALTH_CFG_AREQPRIO_MASK	0x300
#घोषणा M_BKE_HEALTH_CFG_PRIOLVL_MASK	0x3
#घोषणा M_BKE_HEALTH_CFG_AREQPRIO_SHIFT	0x8
#घोषणा M_BKE_HEALTH_CFG_LIMITCMDS_SHIFT 0x1f

#घोषणा M_BKE_EN_EN_BMASK		0x1

/* Valid क्रम both NoC and BIMC */
#घोषणा NOC_QOS_MODE_FIXED		0x0
#घोषणा NOC_QOS_MODE_LIMITER		0x1
#घोषणा NOC_QOS_MODE_BYPASS		0x2

/* NoC QoS */
#घोषणा NOC_PERM_MODE_FIXED		1
#घोषणा NOC_PERM_MODE_BYPASS		(1 << NOC_QOS_MODE_BYPASS)

#घोषणा NOC_QOS_PRIORITYn_ADDR(n)	(0x8 + (n * 0x1000))
#घोषणा NOC_QOS_PRIORITY_MASK		0xf
#घोषणा NOC_QOS_PRIORITY_P1_SHIFT	0x2
#घोषणा NOC_QOS_PRIORITY_P0_SHIFT	0x3

#घोषणा NOC_QOS_MODEn_ADDR(n)		(0xc + (n * 0x1000))
#घोषणा NOC_QOS_MODEn_MASK		0x3

क्रमागत अणु
	SDM660_MASTER_IPA = 1,
	SDM660_MASTER_CNOC_A2NOC,
	SDM660_MASTER_SDCC_1,
	SDM660_MASTER_SDCC_2,
	SDM660_MASTER_BLSP_1,
	SDM660_MASTER_BLSP_2,
	SDM660_MASTER_UFS,
	SDM660_MASTER_USB_HS,
	SDM660_MASTER_USB3,
	SDM660_MASTER_CRYPTO_C0,
	SDM660_MASTER_GNOC_BIMC,
	SDM660_MASTER_OXILI,
	SDM660_MASTER_MNOC_BIMC,
	SDM660_MASTER_SNOC_BIMC,
	SDM660_MASTER_PIMEM,
	SDM660_MASTER_SNOC_CNOC,
	SDM660_MASTER_QDSS_DAP,
	SDM660_MASTER_APPS_PROC,
	SDM660_MASTER_CNOC_MNOC_MMSS_CFG,
	SDM660_MASTER_CNOC_MNOC_CFG,
	SDM660_MASTER_CPP,
	SDM660_MASTER_JPEG,
	SDM660_MASTER_MDP_P0,
	SDM660_MASTER_MDP_P1,
	SDM660_MASTER_VENUS,
	SDM660_MASTER_VFE,
	SDM660_MASTER_QDSS_ETR,
	SDM660_MASTER_QDSS_BAM,
	SDM660_MASTER_SNOC_CFG,
	SDM660_MASTER_BIMC_SNOC,
	SDM660_MASTER_A2NOC_SNOC,
	SDM660_MASTER_GNOC_SNOC,

	SDM660_SLAVE_A2NOC_SNOC,
	SDM660_SLAVE_EBI,
	SDM660_SLAVE_HMSS_L3,
	SDM660_SLAVE_BIMC_SNOC,
	SDM660_SLAVE_CNOC_A2NOC,
	SDM660_SLAVE_MPM,
	SDM660_SLAVE_PMIC_ARB,
	SDM660_SLAVE_TLMM_NORTH,
	SDM660_SLAVE_TCSR,
	SDM660_SLAVE_PIMEM_CFG,
	SDM660_SLAVE_IMEM_CFG,
	SDM660_SLAVE_MESSAGE_RAM,
	SDM660_SLAVE_GLM,
	SDM660_SLAVE_BIMC_CFG,
	SDM660_SLAVE_PRNG,
	SDM660_SLAVE_SPDM,
	SDM660_SLAVE_QDSS_CFG,
	SDM660_SLAVE_CNOC_MNOC_CFG,
	SDM660_SLAVE_SNOC_CFG,
	SDM660_SLAVE_QM_CFG,
	SDM660_SLAVE_CLK_CTL,
	SDM660_SLAVE_MSS_CFG,
	SDM660_SLAVE_TLMM_SOUTH,
	SDM660_SLAVE_UFS_CFG,
	SDM660_SLAVE_A2NOC_CFG,
	SDM660_SLAVE_A2NOC_SMMU_CFG,
	SDM660_SLAVE_GPUSS_CFG,
	SDM660_SLAVE_AHB2PHY,
	SDM660_SLAVE_BLSP_1,
	SDM660_SLAVE_SDCC_1,
	SDM660_SLAVE_SDCC_2,
	SDM660_SLAVE_TLMM_CENTER,
	SDM660_SLAVE_BLSP_2,
	SDM660_SLAVE_PDM,
	SDM660_SLAVE_CNOC_MNOC_MMSS_CFG,
	SDM660_SLAVE_USB_HS,
	SDM660_SLAVE_USB3_0,
	SDM660_SLAVE_SRVC_CNOC,
	SDM660_SLAVE_GNOC_BIMC,
	SDM660_SLAVE_GNOC_SNOC,
	SDM660_SLAVE_CAMERA_CFG,
	SDM660_SLAVE_CAMERA_THROTTLE_CFG,
	SDM660_SLAVE_MISC_CFG,
	SDM660_SLAVE_VENUS_THROTTLE_CFG,
	SDM660_SLAVE_VENUS_CFG,
	SDM660_SLAVE_MMSS_CLK_XPU_CFG,
	SDM660_SLAVE_MMSS_CLK_CFG,
	SDM660_SLAVE_MNOC_MPU_CFG,
	SDM660_SLAVE_DISPLAY_CFG,
	SDM660_SLAVE_CSI_PHY_CFG,
	SDM660_SLAVE_DISPLAY_THROTTLE_CFG,
	SDM660_SLAVE_SMMU_CFG,
	SDM660_SLAVE_MNOC_BIMC,
	SDM660_SLAVE_SRVC_MNOC,
	SDM660_SLAVE_HMSS,
	SDM660_SLAVE_LPASS,
	SDM660_SLAVE_WLAN,
	SDM660_SLAVE_CDSP,
	SDM660_SLAVE_IPA,
	SDM660_SLAVE_SNOC_BIMC,
	SDM660_SLAVE_SNOC_CNOC,
	SDM660_SLAVE_IMEM,
	SDM660_SLAVE_PIMEM,
	SDM660_SLAVE_QDSS_STM,
	SDM660_SLAVE_SRVC_SNOC,

	SDM660_A2NOC,
	SDM660_BIMC,
	SDM660_CNOC,
	SDM660_GNOC,
	SDM660_MNOC,
	SDM660_SNOC,
पूर्ण;

#घोषणा to_qcom_provider(_provider) \
	container_of(_provider, काष्ठा qcom_icc_provider, provider)

अटल स्थिर काष्ठा clk_bulk_data bus_घड़ीs[] = अणु
	अणु .id = "bus" पूर्ण,
	अणु .id = "bus_a" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_bulk_data bus_mm_घड़ीs[] = अणु
	अणु .id = "bus" पूर्ण,
	अणु .id = "bus_a" पूर्ण,
	अणु .id = "iface" पूर्ण,
पूर्ण;

/**
 * काष्ठा qcom_icc_provider - Qualcomm specअगरic पूर्णांकerconnect provider
 * @provider: generic पूर्णांकerconnect provider
 * @bus_clks: the clk_bulk_data table of bus घड़ीs
 * @num_clks: the total number of clk_bulk_data entries
 * @is_bimc_node: indicates whether to use bimc specअगरic setting
 * @regmap: regmap क्रम QoS रेजिस्टरs पढ़ो/ग_लिखो access
 * @mmio: NoC base iospace
 */
काष्ठा qcom_icc_provider अणु
	काष्ठा icc_provider provider;
	काष्ठा clk_bulk_data *bus_clks;
	पूर्णांक num_clks;
	bool is_bimc_node;
	काष्ठा regmap *regmap;
	व्योम __iomem *mmio;
पूर्ण;

#घोषणा SDM660_MAX_LINKS	34

/**
 * काष्ठा qcom_icc_qos - Qualcomm specअगरic पूर्णांकerconnect QoS parameters
 * @areq_prio: node requests priority
 * @prio_level: priority level क्रम bus communication
 * @limit_commands: activate/deactivate limiter mode during runसमय
 * @ap_owned: indicates अगर the node is owned by the AP or by the RPM
 * @qos_mode: शेष qos mode क्रम this node
 * @qos_port: qos port number क्रम finding qos रेजिस्टरs of this node
 */
काष्ठा qcom_icc_qos अणु
	u32 areq_prio;
	u32 prio_level;
	bool limit_commands;
	bool ap_owned;
	पूर्णांक qos_mode;
	पूर्णांक qos_port;
पूर्ण;

/**
 * काष्ठा qcom_icc_node - Qualcomm specअगरic पूर्णांकerconnect nodes
 * @name: the node name used in debugfs
 * @id: a unique node identअगरier
 * @links: an array of nodes where we can go next जबतक traversing
 * @num_links: the total number of @links
 * @buswidth: width of the पूर्णांकerconnect between a node and the bus (bytes)
 * @mas_rpm_id: RPM id क्रम devices that are bus masters
 * @slv_rpm_id: RPM id क्रम devices that are bus slaves
 * @qos: NoC QoS setting parameters
 * @rate: current bus घड़ी rate in Hz
 */
काष्ठा qcom_icc_node अणु
	अचिन्हित अक्षर *name;
	u16 id;
	u16 links[SDM660_MAX_LINKS];
	u16 num_links;
	u16 buswidth;
	पूर्णांक mas_rpm_id;
	पूर्णांक slv_rpm_id;
	काष्ठा qcom_icc_qos qos;
	u64 rate;
पूर्ण;

काष्ठा qcom_icc_desc अणु
	काष्ठा qcom_icc_node **nodes;
	माप_प्रकार num_nodes;
	स्थिर काष्ठा regmap_config *regmap_cfg;
पूर्ण;

#घोषणा DEFINE_QNODE(_name, _id, _buswidth, _mas_rpm_id, _slv_rpm_id,	\
		     _ap_owned, _qos_mode, _qos_prio, _qos_port, ...)	\
		अटल काष्ठा qcom_icc_node _name = अणु			\
		.name = #_name,						\
		.id = _id,						\
		.buswidth = _buswidth,					\
		.mas_rpm_id = _mas_rpm_id,				\
		.slv_rpm_id = _slv_rpm_id,				\
		.qos.ap_owned = _ap_owned,				\
		.qos.qos_mode = _qos_mode,				\
		.qos.areq_prio = _qos_prio,				\
		.qos.prio_level = _qos_prio,				\
		.qos.qos_port = _qos_port,				\
		.num_links = ARRAY_SIZE(((पूर्णांक[])अणु __VA_ARGS__ पूर्ण)),	\
		.links = अणु __VA_ARGS__ पूर्ण,				\
	पूर्ण

DEFINE_QNODE(mas_ipa, SDM660_MASTER_IPA, 8, 59, -1, true, NOC_QOS_MODE_FIXED, 1, 3, SDM660_SLAVE_A2NOC_SNOC);
DEFINE_QNODE(mas_cnoc_a2noc, SDM660_MASTER_CNOC_A2NOC, 8, 146, -1, true, -1, 0, -1, SDM660_SLAVE_A2NOC_SNOC);
DEFINE_QNODE(mas_sdcc_1, SDM660_MASTER_SDCC_1, 8, 33, -1, false, -1, 0, -1, SDM660_SLAVE_A2NOC_SNOC);
DEFINE_QNODE(mas_sdcc_2, SDM660_MASTER_SDCC_2, 8, 35, -1, false, -1, 0, -1, SDM660_SLAVE_A2NOC_SNOC);
DEFINE_QNODE(mas_blsp_1, SDM660_MASTER_BLSP_1, 4, 41, -1, false, -1, 0, -1, SDM660_SLAVE_A2NOC_SNOC);
DEFINE_QNODE(mas_blsp_2, SDM660_MASTER_BLSP_2, 4, 39, -1, false, -1, 0, -1, SDM660_SLAVE_A2NOC_SNOC);
DEFINE_QNODE(mas_ufs, SDM660_MASTER_UFS, 8, 68, -1, true, NOC_QOS_MODE_FIXED, 1, 4, SDM660_SLAVE_A2NOC_SNOC);
DEFINE_QNODE(mas_usb_hs, SDM660_MASTER_USB_HS, 8, 42, -1, true, NOC_QOS_MODE_FIXED, 1, 1, SDM660_SLAVE_A2NOC_SNOC);
DEFINE_QNODE(mas_usb3, SDM660_MASTER_USB3, 8, 32, -1, true, NOC_QOS_MODE_FIXED, 1, 2, SDM660_SLAVE_A2NOC_SNOC);
DEFINE_QNODE(mas_crypto, SDM660_MASTER_CRYPTO_C0, 8, 23, -1, true, NOC_QOS_MODE_FIXED, 1, 11, SDM660_SLAVE_A2NOC_SNOC);
DEFINE_QNODE(mas_gnoc_bimc, SDM660_MASTER_GNOC_BIMC, 4, 144, -1, true, NOC_QOS_MODE_FIXED, 0, 0, SDM660_SLAVE_EBI);
DEFINE_QNODE(mas_oxili, SDM660_MASTER_OXILI, 4, 6, -1, true, NOC_QOS_MODE_BYPASS, 0, 1, SDM660_SLAVE_HMSS_L3, SDM660_SLAVE_EBI, SDM660_SLAVE_BIMC_SNOC);
DEFINE_QNODE(mas_mnoc_bimc, SDM660_MASTER_MNOC_BIMC, 4, 2, -1, true, NOC_QOS_MODE_BYPASS, 0, 2, SDM660_SLAVE_HMSS_L3, SDM660_SLAVE_EBI, SDM660_SLAVE_BIMC_SNOC);
DEFINE_QNODE(mas_snoc_bimc, SDM660_MASTER_SNOC_BIMC, 4, 3, -1, false, -1, 0, -1, SDM660_SLAVE_HMSS_L3, SDM660_SLAVE_EBI);
DEFINE_QNODE(mas_pimem, SDM660_MASTER_PIMEM, 4, 113, -1, true, NOC_QOS_MODE_FIXED, 1, 4, SDM660_SLAVE_HMSS_L3, SDM660_SLAVE_EBI);
DEFINE_QNODE(mas_snoc_cnoc, SDM660_MASTER_SNOC_CNOC, 8, 52, -1, true, -1, 0, -1, SDM660_SLAVE_CLK_CTL, SDM660_SLAVE_QDSS_CFG, SDM660_SLAVE_QM_CFG, SDM660_SLAVE_SRVC_CNOC, SDM660_SLAVE_UFS_CFG, SDM660_SLAVE_TCSR, SDM660_SLAVE_A2NOC_SMMU_CFG, SDM660_SLAVE_SNOC_CFG, SDM660_SLAVE_TLMM_SOUTH, SDM660_SLAVE_MPM, SDM660_SLAVE_CNOC_MNOC_MMSS_CFG, SDM660_SLAVE_SDCC_2, SDM660_SLAVE_SDCC_1, SDM660_SLAVE_SPDM, SDM660_SLAVE_PMIC_ARB, SDM660_SLAVE_PRNG, SDM660_SLAVE_MSS_CFG, SDM660_SLAVE_GPUSS_CFG, SDM660_SLAVE_IMEM_CFG, SDM660_SLAVE_USB3_0, SDM660_SLAVE_A2NOC_CFG, SDM660_SLAVE_TLMM_NORTH, SDM660_SLAVE_USB_HS, SDM660_SLAVE_PDM, SDM660_SLAVE_TLMM_CENTER, SDM660_SLAVE_AHB2PHY, SDM660_SLAVE_BLSP_2, SDM660_SLAVE_BLSP_1, SDM660_SLAVE_PIMEM_CFG, SDM660_SLAVE_GLM, SDM660_SLAVE_MESSAGE_RAM, SDM660_SLAVE_BIMC_CFG, SDM660_SLAVE_CNOC_MNOC_CFG);
DEFINE_QNODE(mas_qdss_dap, SDM660_MASTER_QDSS_DAP, 8, 49, -1, true, -1, 0, -1, SDM660_SLAVE_CLK_CTL, SDM660_SLAVE_QDSS_CFG, SDM660_SLAVE_QM_CFG, SDM660_SLAVE_SRVC_CNOC, SDM660_SLAVE_UFS_CFG, SDM660_SLAVE_TCSR, SDM660_SLAVE_A2NOC_SMMU_CFG, SDM660_SLAVE_SNOC_CFG, SDM660_SLAVE_TLMM_SOUTH, SDM660_SLAVE_MPM, SDM660_SLAVE_CNOC_MNOC_MMSS_CFG, SDM660_SLAVE_SDCC_2, SDM660_SLAVE_SDCC_1, SDM660_SLAVE_SPDM, SDM660_SLAVE_PMIC_ARB, SDM660_SLAVE_PRNG, SDM660_SLAVE_MSS_CFG, SDM660_SLAVE_GPUSS_CFG, SDM660_SLAVE_IMEM_CFG, SDM660_SLAVE_USB3_0, SDM660_SLAVE_A2NOC_CFG, SDM660_SLAVE_TLMM_NORTH, SDM660_SLAVE_USB_HS, SDM660_SLAVE_PDM, SDM660_SLAVE_TLMM_CENTER, SDM660_SLAVE_AHB2PHY, SDM660_SLAVE_BLSP_2, SDM660_SLAVE_BLSP_1, SDM660_SLAVE_PIMEM_CFG, SDM660_SLAVE_GLM, SDM660_SLAVE_MESSAGE_RAM, SDM660_SLAVE_CNOC_A2NOC, SDM660_SLAVE_BIMC_CFG, SDM660_SLAVE_CNOC_MNOC_CFG);
DEFINE_QNODE(mas_apss_proc, SDM660_MASTER_APPS_PROC, 16, 0, -1, true, -1, 0, -1, SDM660_SLAVE_GNOC_SNOC, SDM660_SLAVE_GNOC_BIMC);
DEFINE_QNODE(mas_cnoc_mnoc_mmss_cfg, SDM660_MASTER_CNOC_MNOC_MMSS_CFG, 8, 4, -1, true, -1, 0, -1, SDM660_SLAVE_VENUS_THROTTLE_CFG, SDM660_SLAVE_VENUS_CFG, SDM660_SLAVE_CAMERA_THROTTLE_CFG, SDM660_SLAVE_SMMU_CFG, SDM660_SLAVE_CAMERA_CFG, SDM660_SLAVE_CSI_PHY_CFG, SDM660_SLAVE_DISPLAY_THROTTLE_CFG, SDM660_SLAVE_DISPLAY_CFG, SDM660_SLAVE_MMSS_CLK_CFG, SDM660_SLAVE_MNOC_MPU_CFG, SDM660_SLAVE_MISC_CFG, SDM660_SLAVE_MMSS_CLK_XPU_CFG);
DEFINE_QNODE(mas_cnoc_mnoc_cfg, SDM660_MASTER_CNOC_MNOC_CFG, 4, 5, -1, true, -1, 0, -1, SDM660_SLAVE_SRVC_MNOC);
DEFINE_QNODE(mas_cpp, SDM660_MASTER_CPP, 16, 115, -1, true, NOC_QOS_MODE_BYPASS, 0, 4, SDM660_SLAVE_MNOC_BIMC);
DEFINE_QNODE(mas_jpeg, SDM660_MASTER_JPEG, 16, 7, -1, true, NOC_QOS_MODE_BYPASS, 0, 6, SDM660_SLAVE_MNOC_BIMC);
DEFINE_QNODE(mas_mdp_p0, SDM660_MASTER_MDP_P0, 16, 8, -1, true, NOC_QOS_MODE_BYPASS, 0, 0, SDM660_SLAVE_MNOC_BIMC); /* vrail-comp???? */
DEFINE_QNODE(mas_mdp_p1, SDM660_MASTER_MDP_P1, 16, 61, -1, true, NOC_QOS_MODE_BYPASS, 0, 1, SDM660_SLAVE_MNOC_BIMC); /* vrail-comp??? */
DEFINE_QNODE(mas_venus, SDM660_MASTER_VENUS, 16, 9, -1, true, NOC_QOS_MODE_BYPASS, 0, 1, SDM660_SLAVE_MNOC_BIMC);
DEFINE_QNODE(mas_vfe, SDM660_MASTER_VFE, 16, 11, -1, true, NOC_QOS_MODE_BYPASS, 0, 5, SDM660_SLAVE_MNOC_BIMC);
DEFINE_QNODE(mas_qdss_etr, SDM660_MASTER_QDSS_ETR, 8, 31, -1, true, NOC_QOS_MODE_FIXED, 1, 1, SDM660_SLAVE_PIMEM, SDM660_SLAVE_IMEM, SDM660_SLAVE_SNOC_CNOC, SDM660_SLAVE_SNOC_BIMC);
DEFINE_QNODE(mas_qdss_bam, SDM660_MASTER_QDSS_BAM, 4, 19, -1, true, NOC_QOS_MODE_FIXED, 1, 0, SDM660_SLAVE_PIMEM, SDM660_SLAVE_IMEM, SDM660_SLAVE_SNOC_CNOC, SDM660_SLAVE_SNOC_BIMC);
DEFINE_QNODE(mas_snoc_cfg, SDM660_MASTER_SNOC_CFG, 4, 20, -1, false, -1, 0, -1, SDM660_SLAVE_SRVC_SNOC);
DEFINE_QNODE(mas_bimc_snoc, SDM660_MASTER_BIMC_SNOC, 8, 21, -1, false, -1, 0, -1, SDM660_SLAVE_PIMEM, SDM660_SLAVE_IPA, SDM660_SLAVE_QDSS_STM, SDM660_SLAVE_LPASS, SDM660_SLAVE_HMSS, SDM660_SLAVE_CDSP, SDM660_SLAVE_SNOC_CNOC, SDM660_SLAVE_WLAN, SDM660_SLAVE_IMEM);
DEFINE_QNODE(mas_gnoc_snoc, SDM660_MASTER_GNOC_SNOC, 8, 150, -1, false, -1, 0, -1, SDM660_SLAVE_PIMEM, SDM660_SLAVE_IPA, SDM660_SLAVE_QDSS_STM, SDM660_SLAVE_LPASS, SDM660_SLAVE_HMSS, SDM660_SLAVE_CDSP, SDM660_SLAVE_SNOC_CNOC, SDM660_SLAVE_WLAN, SDM660_SLAVE_IMEM);
DEFINE_QNODE(mas_a2noc_snoc, SDM660_MASTER_A2NOC_SNOC, 16, 112, -1, false, -1, 0, -1, SDM660_SLAVE_PIMEM, SDM660_SLAVE_IPA, SDM660_SLAVE_QDSS_STM, SDM660_SLAVE_LPASS, SDM660_SLAVE_HMSS, SDM660_SLAVE_SNOC_BIMC, SDM660_SLAVE_CDSP, SDM660_SLAVE_SNOC_CNOC, SDM660_SLAVE_WLAN, SDM660_SLAVE_IMEM);
DEFINE_QNODE(slv_a2noc_snoc, SDM660_SLAVE_A2NOC_SNOC, 16, -1, 143, false, -1, 0, -1, SDM660_MASTER_A2NOC_SNOC);
DEFINE_QNODE(slv_ebi, SDM660_SLAVE_EBI, 4, -1, 0, false, -1, 0, -1, 0);
DEFINE_QNODE(slv_hmss_l3, SDM660_SLAVE_HMSS_L3, 4, -1, 160, false, -1, 0, -1, 0);
DEFINE_QNODE(slv_bimc_snoc, SDM660_SLAVE_BIMC_SNOC, 4, -1, 2, false, -1, 0, -1, SDM660_MASTER_BIMC_SNOC);
DEFINE_QNODE(slv_cnoc_a2noc, SDM660_SLAVE_CNOC_A2NOC, 8, -1, 208, true, -1, 0, -1, SDM660_MASTER_CNOC_A2NOC);
DEFINE_QNODE(slv_mpm, SDM660_SLAVE_MPM, 4, -1, 62, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_pmic_arb, SDM660_SLAVE_PMIC_ARB, 4, -1, 59, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_tlmm_north, SDM660_SLAVE_TLMM_NORTH, 8, -1, 214, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_tcsr, SDM660_SLAVE_TCSR, 4, -1, 50, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_pimem_cfg, SDM660_SLAVE_PIMEM_CFG, 4, -1, 167, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_imem_cfg, SDM660_SLAVE_IMEM_CFG, 4, -1, 54, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_message_ram, SDM660_SLAVE_MESSAGE_RAM, 4, -1, 55, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_glm, SDM660_SLAVE_GLM, 4, -1, 209, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_bimc_cfg, SDM660_SLAVE_BIMC_CFG, 4, -1, 56, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_prng, SDM660_SLAVE_PRNG, 4, -1, 44, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_spdm, SDM660_SLAVE_SPDM, 4, -1, 60, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_qdss_cfg, SDM660_SLAVE_QDSS_CFG, 4, -1, 63, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_cnoc_mnoc_cfg, SDM660_SLAVE_BLSP_1, 4, -1, 66, true, -1, 0, -1, SDM660_MASTER_CNOC_MNOC_CFG);
DEFINE_QNODE(slv_snoc_cfg, SDM660_SLAVE_SNOC_CFG, 4, -1, 70, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_qm_cfg, SDM660_SLAVE_QM_CFG, 4, -1, 212, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_clk_ctl, SDM660_SLAVE_CLK_CTL, 4, -1, 47, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_mss_cfg, SDM660_SLAVE_MSS_CFG, 4, -1, 48, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_tlmm_south, SDM660_SLAVE_TLMM_SOUTH, 4, -1, 217, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_ufs_cfg, SDM660_SLAVE_UFS_CFG, 4, -1, 92, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_a2noc_cfg, SDM660_SLAVE_A2NOC_CFG, 4, -1, 150, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_a2noc_smmu_cfg, SDM660_SLAVE_A2NOC_SMMU_CFG, 8, -1, 152, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_gpuss_cfg, SDM660_SLAVE_GPUSS_CFG, 8, -1, 11, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_ahb2phy, SDM660_SLAVE_AHB2PHY, 4, -1, 163, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_blsp_1, SDM660_SLAVE_BLSP_1, 4, -1, 39, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_sdcc_1, SDM660_SLAVE_SDCC_1, 4, -1, 31, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_sdcc_2, SDM660_SLAVE_SDCC_2, 4, -1, 33, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_tlmm_center, SDM660_SLAVE_TLMM_CENTER, 4, -1, 218, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_blsp_2, SDM660_SLAVE_BLSP_2, 4, -1, 37, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_pdm, SDM660_SLAVE_PDM, 4, -1, 41, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_cnoc_mnoc_mmss_cfg, SDM660_SLAVE_CNOC_MNOC_MMSS_CFG, 8, -1, 58, true, -1, 0, -1, SDM660_MASTER_CNOC_MNOC_MMSS_CFG);
DEFINE_QNODE(slv_usb_hs, SDM660_SLAVE_USB_HS, 4, -1, 40, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_usb3_0, SDM660_SLAVE_USB3_0, 4, -1, 22, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_srvc_cnoc, SDM660_SLAVE_SRVC_CNOC, 4, -1, 76, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_gnoc_bimc, SDM660_SLAVE_GNOC_BIMC, 16, -1, 210, true, -1, 0, -1, SDM660_MASTER_GNOC_BIMC);
DEFINE_QNODE(slv_gnoc_snoc, SDM660_SLAVE_GNOC_SNOC, 8, -1, 211, true, -1, 0, -1, SDM660_MASTER_GNOC_SNOC);
DEFINE_QNODE(slv_camera_cfg, SDM660_SLAVE_CAMERA_CFG, 4, -1, 3, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_camera_throttle_cfg, SDM660_SLAVE_CAMERA_THROTTLE_CFG, 4, -1, 154, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_misc_cfg, SDM660_SLAVE_MISC_CFG, 4, -1, 8, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_venus_throttle_cfg, SDM660_SLAVE_VENUS_THROTTLE_CFG, 4, -1, 178, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_venus_cfg, SDM660_SLAVE_VENUS_CFG, 4, -1, 10, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_mmss_clk_xpu_cfg, SDM660_SLAVE_MMSS_CLK_XPU_CFG, 4, -1, 13, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_mmss_clk_cfg, SDM660_SLAVE_MMSS_CLK_CFG, 4, -1, 12, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_mnoc_mpu_cfg, SDM660_SLAVE_MNOC_MPU_CFG, 4, -1, 14, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_display_cfg, SDM660_SLAVE_DISPLAY_CFG, 4, -1, 4, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_csi_phy_cfg, SDM660_SLAVE_CSI_PHY_CFG, 4, -1, 224, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_display_throttle_cfg, SDM660_SLAVE_DISPLAY_THROTTLE_CFG, 4, -1, 156, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_smmu_cfg, SDM660_SLAVE_SMMU_CFG, 8, -1, 205, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_mnoc_bimc, SDM660_SLAVE_MNOC_BIMC, 16, -1, 16, true, -1, 0, -1, SDM660_MASTER_MNOC_BIMC);
DEFINE_QNODE(slv_srvc_mnoc, SDM660_SLAVE_SRVC_MNOC, 8, -1, 17, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_hmss, SDM660_SLAVE_HMSS, 8, -1, 20, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_lpass, SDM660_SLAVE_LPASS, 4, -1, 21, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_wlan, SDM660_SLAVE_WLAN, 4, -1, 206, false, -1, 0, -1, 0);
DEFINE_QNODE(slv_cdsp, SDM660_SLAVE_CDSP, 4, -1, 221, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_ipa, SDM660_SLAVE_IPA, 4, -1, 183, true, -1, 0, -1, 0);
DEFINE_QNODE(slv_snoc_bimc, SDM660_SLAVE_SNOC_BIMC, 16, -1, 24, false, -1, 0, -1, SDM660_MASTER_SNOC_BIMC);
DEFINE_QNODE(slv_snoc_cnoc, SDM660_SLAVE_SNOC_CNOC, 8, -1, 25, false, -1, 0, -1, SDM660_MASTER_SNOC_CNOC);
DEFINE_QNODE(slv_imem, SDM660_SLAVE_IMEM, 8, -1, 26, false, -1, 0, -1, 0);
DEFINE_QNODE(slv_pimem, SDM660_SLAVE_PIMEM, 8, -1, 166, false, -1, 0, -1, 0);
DEFINE_QNODE(slv_qdss_sपंचांग, SDM660_SLAVE_QDSS_STM, 4, -1, 30, false, -1, 0, -1, 0);
DEFINE_QNODE(slv_srvc_snoc, SDM660_SLAVE_SRVC_SNOC, 16, -1, 29, false, -1, 0, -1, 0);

अटल काष्ठा qcom_icc_node *sdm660_a2noc_nodes[] = अणु
	[MASTER_IPA] = &mas_ipa,
	[MASTER_CNOC_A2NOC] = &mas_cnoc_a2noc,
	[MASTER_SDCC_1] = &mas_sdcc_1,
	[MASTER_SDCC_2] = &mas_sdcc_2,
	[MASTER_BLSP_1] = &mas_blsp_1,
	[MASTER_BLSP_2] = &mas_blsp_2,
	[MASTER_UFS] = &mas_ufs,
	[MASTER_USB_HS] = &mas_usb_hs,
	[MASTER_USB3] = &mas_usb3,
	[MASTER_CRYPTO_C0] = &mas_crypto,
	[SLAVE_A2NOC_SNOC] = &slv_a2noc_snoc,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sdm660_a2noc_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x20000,
	.fast_io	= true,
पूर्ण;

अटल काष्ठा qcom_icc_desc sdm660_a2noc = अणु
	.nodes = sdm660_a2noc_nodes,
	.num_nodes = ARRAY_SIZE(sdm660_a2noc_nodes),
	.regmap_cfg = &sdm660_a2noc_regmap_config,
पूर्ण;

अटल काष्ठा qcom_icc_node *sdm660_bimc_nodes[] = अणु
	[MASTER_GNOC_BIMC] = &mas_gnoc_bimc,
	[MASTER_OXILI] = &mas_oxili,
	[MASTER_MNOC_BIMC] = &mas_mnoc_bimc,
	[MASTER_SNOC_BIMC] = &mas_snoc_bimc,
	[MASTER_PIMEM] = &mas_pimem,
	[SLAVE_EBI] = &slv_ebi,
	[SLAVE_HMSS_L3] = &slv_hmss_l3,
	[SLAVE_BIMC_SNOC] = &slv_bimc_snoc,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sdm660_bimc_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x80000,
	.fast_io	= true,
पूर्ण;

अटल काष्ठा qcom_icc_desc sdm660_bimc = अणु
	.nodes = sdm660_bimc_nodes,
	.num_nodes = ARRAY_SIZE(sdm660_bimc_nodes),
	.regmap_cfg = &sdm660_bimc_regmap_config,
पूर्ण;

अटल काष्ठा qcom_icc_node *sdm660_cnoc_nodes[] = अणु
	[MASTER_SNOC_CNOC] = &mas_snoc_cnoc,
	[MASTER_QDSS_DAP] = &mas_qdss_dap,
	[SLAVE_CNOC_A2NOC] = &slv_cnoc_a2noc,
	[SLAVE_MPM] = &slv_mpm,
	[SLAVE_PMIC_ARB] = &slv_pmic_arb,
	[SLAVE_TLMM_NORTH] = &slv_tlmm_north,
	[SLAVE_TCSR] = &slv_tcsr,
	[SLAVE_PIMEM_CFG] = &slv_pimem_cfg,
	[SLAVE_IMEM_CFG] = &slv_imem_cfg,
	[SLAVE_MESSAGE_RAM] = &slv_message_ram,
	[SLAVE_GLM] = &slv_glm,
	[SLAVE_BIMC_CFG] = &slv_bimc_cfg,
	[SLAVE_PRNG] = &slv_prng,
	[SLAVE_SPDM] = &slv_spdm,
	[SLAVE_QDSS_CFG] = &slv_qdss_cfg,
	[SLAVE_CNOC_MNOC_CFG] = &slv_cnoc_mnoc_cfg,
	[SLAVE_SNOC_CFG] = &slv_snoc_cfg,
	[SLAVE_QM_CFG] = &slv_qm_cfg,
	[SLAVE_CLK_CTL] = &slv_clk_ctl,
	[SLAVE_MSS_CFG] = &slv_mss_cfg,
	[SLAVE_TLMM_SOUTH] = &slv_tlmm_south,
	[SLAVE_UFS_CFG] = &slv_ufs_cfg,
	[SLAVE_A2NOC_CFG] = &slv_a2noc_cfg,
	[SLAVE_A2NOC_SMMU_CFG] = &slv_a2noc_smmu_cfg,
	[SLAVE_GPUSS_CFG] = &slv_gpuss_cfg,
	[SLAVE_AHB2PHY] = &slv_ahb2phy,
	[SLAVE_BLSP_1] = &slv_blsp_1,
	[SLAVE_SDCC_1] = &slv_sdcc_1,
	[SLAVE_SDCC_2] = &slv_sdcc_2,
	[SLAVE_TLMM_CENTER] = &slv_tlmm_center,
	[SLAVE_BLSP_2] = &slv_blsp_2,
	[SLAVE_PDM] = &slv_pdm,
	[SLAVE_CNOC_MNOC_MMSS_CFG] = &slv_cnoc_mnoc_mmss_cfg,
	[SLAVE_USB_HS] = &slv_usb_hs,
	[SLAVE_USB3_0] = &slv_usb3_0,
	[SLAVE_SRVC_CNOC] = &slv_srvc_cnoc,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sdm660_cnoc_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x10000,
	.fast_io	= true,
पूर्ण;

अटल काष्ठा qcom_icc_desc sdm660_cnoc = अणु
	.nodes = sdm660_cnoc_nodes,
	.num_nodes = ARRAY_SIZE(sdm660_cnoc_nodes),
	.regmap_cfg = &sdm660_cnoc_regmap_config,
पूर्ण;

अटल काष्ठा qcom_icc_node *sdm660_gnoc_nodes[] = अणु
	[MASTER_APSS_PROC] = &mas_apss_proc,
	[SLAVE_GNOC_BIMC] = &slv_gnoc_bimc,
	[SLAVE_GNOC_SNOC] = &slv_gnoc_snoc,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sdm660_gnoc_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0xe000,
	.fast_io	= true,
पूर्ण;

अटल काष्ठा qcom_icc_desc sdm660_gnoc = अणु
	.nodes = sdm660_gnoc_nodes,
	.num_nodes = ARRAY_SIZE(sdm660_gnoc_nodes),
	.regmap_cfg = &sdm660_gnoc_regmap_config,
पूर्ण;

अटल काष्ठा qcom_icc_node *sdm660_mnoc_nodes[] = अणु
	[MASTER_CPP] = &mas_cpp,
	[MASTER_JPEG] = &mas_jpeg,
	[MASTER_MDP_P0] = &mas_mdp_p0,
	[MASTER_MDP_P1] = &mas_mdp_p1,
	[MASTER_VENUS] = &mas_venus,
	[MASTER_VFE] = &mas_vfe,
	[MASTER_CNOC_MNOC_MMSS_CFG] = &mas_cnoc_mnoc_mmss_cfg,
	[MASTER_CNOC_MNOC_CFG] = &mas_cnoc_mnoc_cfg,
	[SLAVE_CAMERA_CFG] = &slv_camera_cfg,
	[SLAVE_CAMERA_THROTTLE_CFG] = &slv_camera_throttle_cfg,
	[SLAVE_MISC_CFG] = &slv_misc_cfg,
	[SLAVE_VENUS_THROTTLE_CFG] = &slv_venus_throttle_cfg,
	[SLAVE_VENUS_CFG] = &slv_venus_cfg,
	[SLAVE_MMSS_CLK_XPU_CFG] = &slv_mmss_clk_xpu_cfg,
	[SLAVE_MMSS_CLK_CFG] = &slv_mmss_clk_cfg,
	[SLAVE_MNOC_MPU_CFG] = &slv_mnoc_mpu_cfg,
	[SLAVE_DISPLAY_CFG] = &slv_display_cfg,
	[SLAVE_CSI_PHY_CFG] = &slv_csi_phy_cfg,
	[SLAVE_DISPLAY_THROTTLE_CFG] = &slv_display_throttle_cfg,
	[SLAVE_SMMU_CFG] = &slv_smmu_cfg,
	[SLAVE_SRVC_MNOC] = &slv_srvc_mnoc,
	[SLAVE_MNOC_BIMC] = &slv_mnoc_bimc,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sdm660_mnoc_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x10000,
	.fast_io	= true,
पूर्ण;

अटल काष्ठा qcom_icc_desc sdm660_mnoc = अणु
	.nodes = sdm660_mnoc_nodes,
	.num_nodes = ARRAY_SIZE(sdm660_mnoc_nodes),
	.regmap_cfg = &sdm660_mnoc_regmap_config,
पूर्ण;

अटल काष्ठा qcom_icc_node *sdm660_snoc_nodes[] = अणु
	[MASTER_QDSS_ETR] = &mas_qdss_etr,
	[MASTER_QDSS_BAM] = &mas_qdss_bam,
	[MASTER_SNOC_CFG] = &mas_snoc_cfg,
	[MASTER_BIMC_SNOC] = &mas_bimc_snoc,
	[MASTER_A2NOC_SNOC] = &mas_a2noc_snoc,
	[MASTER_GNOC_SNOC] = &mas_gnoc_snoc,
	[SLAVE_HMSS] = &slv_hmss,
	[SLAVE_LPASS] = &slv_lpass,
	[SLAVE_WLAN] = &slv_wlan,
	[SLAVE_CDSP] = &slv_cdsp,
	[SLAVE_IPA] = &slv_ipa,
	[SLAVE_SNOC_BIMC] = &slv_snoc_bimc,
	[SLAVE_SNOC_CNOC] = &slv_snoc_cnoc,
	[SLAVE_IMEM] = &slv_imem,
	[SLAVE_PIMEM] = &slv_pimem,
	[SLAVE_QDSS_STM] = &slv_qdss_sपंचांग,
	[SLAVE_SRVC_SNOC] = &slv_srvc_snoc,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sdm660_snoc_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x20000,
	.fast_io	= true,
पूर्ण;

अटल काष्ठा qcom_icc_desc sdm660_snoc = अणु
	.nodes = sdm660_snoc_nodes,
	.num_nodes = ARRAY_SIZE(sdm660_snoc_nodes),
	.regmap_cfg = &sdm660_snoc_regmap_config,
पूर्ण;

अटल पूर्णांक qcom_icc_bimc_set_qos_health(काष्ठा regmap *rmap,
					काष्ठा qcom_icc_qos *qos,
					पूर्णांक regnum)
अणु
	u32 val;
	u32 mask;

	val = qos->prio_level;
	mask = M_BKE_HEALTH_CFG_PRIOLVL_MASK;

	val |= qos->areq_prio << M_BKE_HEALTH_CFG_AREQPRIO_SHIFT;
	mask |= M_BKE_HEALTH_CFG_AREQPRIO_MASK;

	/* LIMITCMDS is not present on M_BKE_HEALTH_3 */
	अगर (regnum != 3) अणु
		val |= qos->limit_commands << M_BKE_HEALTH_CFG_LIMITCMDS_SHIFT;
		mask |= M_BKE_HEALTH_CFG_LIMITCMDS_MASK;
	पूर्ण

	वापस regmap_update_bits(rmap,
				  M_BKE_HEALTH_CFG_ADDR(regnum, qos->qos_port),
				  mask, val);
पूर्ण

अटल पूर्णांक qcom_icc_set_bimc_qos(काष्ठा icc_node *src, u64 max_bw,
				 bool bypass_mode)
अणु
	काष्ठा qcom_icc_provider *qp;
	काष्ठा qcom_icc_node *qn;
	काष्ठा icc_provider *provider;
	u32 mode = NOC_QOS_MODE_BYPASS;
	u32 val = 0;
	पूर्णांक i, rc = 0;

	qn = src->data;
	provider = src->provider;
	qp = to_qcom_provider(provider);

	अगर (qn->qos.qos_mode != -1)
		mode = qn->qos.qos_mode;

	/* QoS Priority: The QoS Health parameters are getting considered
	 * only अगर we are NOT in Bypass Mode.
	 */
	अगर (mode != NOC_QOS_MODE_BYPASS) अणु
		क्रम (i = 3; i >= 0; i--) अणु
			rc = qcom_icc_bimc_set_qos_health(qp->regmap,
							  &qn->qos, i);
			अगर (rc)
				वापस rc;
		पूर्ण

		/* Set BKE_EN to 1 when Fixed, Regulator or Limiter Mode */
		val = 1;
	पूर्ण

	वापस regmap_update_bits(qp->regmap, M_BKE_EN_ADDR(qn->qos.qos_port),
				  M_BKE_EN_EN_BMASK, val);
पूर्ण

अटल पूर्णांक qcom_icc_noc_set_qos_priority(काष्ठा regmap *rmap,
					 काष्ठा qcom_icc_qos *qos)
अणु
	u32 val;
	पूर्णांक rc;

	/* Must be updated one at a समय, P1 first, P0 last */
	val = qos->areq_prio << NOC_QOS_PRIORITY_P1_SHIFT;
	rc = regmap_update_bits(rmap, NOC_QOS_PRIORITYn_ADDR(qos->qos_port),
				NOC_QOS_PRIORITY_MASK, val);
	अगर (rc)
		वापस rc;

	val = qos->prio_level << NOC_QOS_PRIORITY_P0_SHIFT;
	वापस regmap_update_bits(rmap, NOC_QOS_PRIORITYn_ADDR(qos->qos_port),
				  NOC_QOS_PRIORITY_MASK, val);
पूर्ण

अटल पूर्णांक qcom_icc_set_noc_qos(काष्ठा icc_node *src, u64 max_bw)
अणु
	काष्ठा qcom_icc_provider *qp;
	काष्ठा qcom_icc_node *qn;
	काष्ठा icc_provider *provider;
	u32 mode = NOC_QOS_MODE_BYPASS;
	पूर्णांक rc = 0;

	qn = src->data;
	provider = src->provider;
	qp = to_qcom_provider(provider);

	अगर (qn->qos.qos_port < 0) अणु
		dev_dbg(src->provider->dev,
			"NoC QoS: Skipping %s: vote aggregated on parent.\n",
			qn->name);
		वापस 0;
	पूर्ण

	अगर (qn->qos.qos_mode != -1)
		mode = qn->qos.qos_mode;

	अगर (mode == NOC_QOS_MODE_FIXED) अणु
		dev_dbg(src->provider->dev, "NoC QoS: %s: Set Fixed mode\n",
			qn->name);
		rc = qcom_icc_noc_set_qos_priority(qp->regmap, &qn->qos);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अगर (mode == NOC_QOS_MODE_BYPASS) अणु
		dev_dbg(src->provider->dev, "NoC QoS: %s: Set Bypass mode\n",
			qn->name);
	पूर्ण

	वापस regmap_update_bits(qp->regmap,
				  NOC_QOS_MODEn_ADDR(qn->qos.qos_port),
				  NOC_QOS_MODEn_MASK, mode);
पूर्ण

अटल पूर्णांक qcom_icc_qos_set(काष्ठा icc_node *node, u64 sum_bw)
अणु
	काष्ठा qcom_icc_provider *qp = to_qcom_provider(node->provider);
	काष्ठा qcom_icc_node *qn = node->data;

	dev_dbg(node->provider->dev, "Setting QoS for %s\n", qn->name);

	अगर (qp->is_bimc_node)
		वापस qcom_icc_set_bimc_qos(node, sum_bw,
				(qn->qos.qos_mode == NOC_QOS_MODE_BYPASS));

	वापस qcom_icc_set_noc_qos(node, sum_bw);
पूर्ण

अटल पूर्णांक qcom_icc_rpm_set(पूर्णांक mas_rpm_id, पूर्णांक slv_rpm_id, u64 sum_bw)
अणु
	पूर्णांक ret = 0;

	अगर (mas_rpm_id != -1) अणु
		ret = qcom_icc_rpm_smd_send(QCOM_SMD_RPM_ACTIVE_STATE,
					    RPM_BUS_MASTER_REQ,
					    mas_rpm_id,
					    sum_bw);
		अगर (ret) अणु
			pr_err("qcom_icc_rpm_smd_send mas %d error %d\n",
			       mas_rpm_id, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (slv_rpm_id != -1) अणु
		ret = qcom_icc_rpm_smd_send(QCOM_SMD_RPM_ACTIVE_STATE,
					    RPM_BUS_SLAVE_REQ,
					    slv_rpm_id,
					    sum_bw);
		अगर (ret) अणु
			pr_err("qcom_icc_rpm_smd_send slv %d error %d\n",
			       slv_rpm_id, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_icc_set(काष्ठा icc_node *src, काष्ठा icc_node *dst)
अणु
	काष्ठा qcom_icc_provider *qp;
	काष्ठा qcom_icc_node *qn;
	काष्ठा icc_provider *provider;
	काष्ठा icc_node *n;
	u64 sum_bw;
	u64 max_peak_bw;
	u64 rate;
	u32 agg_avg = 0;
	u32 agg_peak = 0;
	पूर्णांक ret, i;

	qn = src->data;
	provider = src->provider;
	qp = to_qcom_provider(provider);

	list_क्रम_each_entry(n, &provider->nodes, node_list)
		provider->aggregate(n, 0, n->avg_bw, n->peak_bw,
				    &agg_avg, &agg_peak);

	sum_bw = icc_units_to_bps(agg_avg);
	max_peak_bw = icc_units_to_bps(agg_peak);

	अगर (!qn->qos.ap_owned) अणु
		/* send bandwidth request message to the RPM processor */
		ret = qcom_icc_rpm_set(qn->mas_rpm_id, qn->slv_rpm_id, sum_bw);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (qn->qos.qos_mode != -1) अणु
		/* set bandwidth directly from the AP */
		ret = qcom_icc_qos_set(src, sum_bw);
		अगर (ret)
			वापस ret;
	पूर्ण

	rate = max(sum_bw, max_peak_bw);

	करो_भाग(rate, qn->buswidth);

	अगर (qn->rate == rate)
		वापस 0;

	क्रम (i = 0; i < qp->num_clks; i++) अणु
		ret = clk_set_rate(qp->bus_clks[i].clk, rate);
		अगर (ret) अणु
			pr_err("%s clk_set_rate error: %d\n",
			       qp->bus_clks[i].id, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	qn->rate = rate;

	वापस 0;
पूर्ण

अटल पूर्णांक qnoc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा qcom_icc_desc *desc;
	काष्ठा icc_onecell_data *data;
	काष्ठा icc_provider *provider;
	काष्ठा qcom_icc_node **qnodes;
	काष्ठा qcom_icc_provider *qp;
	काष्ठा icc_node *node;
	काष्ठा resource *res;
	माप_प्रकार num_nodes, i;
	पूर्णांक ret;

	/* रुको क्रम the RPM proxy */
	अगर (!qcom_icc_rpm_smd_available())
		वापस -EPROBE_DEFER;

	desc = of_device_get_match_data(dev);
	अगर (!desc)
		वापस -EINVAL;

	qnodes = desc->nodes;
	num_nodes = desc->num_nodes;

	qp = devm_kzalloc(dev, माप(*qp), GFP_KERNEL);
	अगर (!qp)
		वापस -ENOMEM;

	data = devm_kzalloc(dev, काष्ठा_size(data, nodes, num_nodes),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	अगर (of_device_is_compatible(dev->of_node, "qcom,sdm660-mnoc")) अणु
		qp->bus_clks = devm_kmemdup(dev, bus_mm_घड़ीs,
					    माप(bus_mm_घड़ीs), GFP_KERNEL);
		qp->num_clks = ARRAY_SIZE(bus_mm_घड़ीs);
	पूर्ण अन्यथा अणु
		अगर (of_device_is_compatible(dev->of_node, "qcom,sdm660-bimc"))
			qp->is_bimc_node = true;

		qp->bus_clks = devm_kmemdup(dev, bus_घड़ीs, माप(bus_घड़ीs),
					    GFP_KERNEL);
		qp->num_clks = ARRAY_SIZE(bus_घड़ीs);
	पूर्ण
	अगर (!qp->bus_clks)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	qp->mmio = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(qp->mmio)) अणु
		dev_err(dev, "Cannot ioremap interconnect bus resource\n");
		वापस PTR_ERR(qp->mmio);
	पूर्ण

	qp->regmap = devm_regmap_init_mmio(dev, qp->mmio, desc->regmap_cfg);
	अगर (IS_ERR(qp->regmap)) अणु
		dev_err(dev, "Cannot regmap interconnect bus resource\n");
		वापस PTR_ERR(qp->regmap);
	पूर्ण

	ret = devm_clk_bulk_get(dev, qp->num_clks, qp->bus_clks);
	अगर (ret)
		वापस ret;

	ret = clk_bulk_prepare_enable(qp->num_clks, qp->bus_clks);
	अगर (ret)
		वापस ret;

	provider = &qp->provider;
	INIT_LIST_HEAD(&provider->nodes);
	provider->dev = dev;
	provider->set = qcom_icc_set;
	provider->aggregate = icc_std_aggregate;
	provider->xlate = of_icc_xlate_onecell;
	provider->data = data;

	ret = icc_provider_add(provider);
	अगर (ret) अणु
		dev_err(dev, "error adding interconnect provider: %d\n", ret);
		clk_bulk_disable_unprepare(qp->num_clks, qp->bus_clks);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < num_nodes; i++) अणु
		माप_प्रकार j;

		node = icc_node_create(qnodes[i]->id);
		अगर (IS_ERR(node)) अणु
			ret = PTR_ERR(node);
			जाओ err;
		पूर्ण

		node->name = qnodes[i]->name;
		node->data = qnodes[i];
		icc_node_add(node, provider);

		क्रम (j = 0; j < qnodes[i]->num_links; j++)
			icc_link_create(node, qnodes[i]->links[j]);

		data->nodes[i] = node;
	पूर्ण
	data->num_nodes = num_nodes;
	platक्रमm_set_drvdata(pdev, qp);

	वापस 0;
err:
	icc_nodes_हटाओ(provider);
	clk_bulk_disable_unprepare(qp->num_clks, qp->bus_clks);
	icc_provider_del(provider);

	वापस ret;
पूर्ण

अटल पूर्णांक qnoc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_icc_provider *qp = platक्रमm_get_drvdata(pdev);

	icc_nodes_हटाओ(&qp->provider);
	clk_bulk_disable_unprepare(qp->num_clks, qp->bus_clks);
	वापस icc_provider_del(&qp->provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id sdm660_noc_of_match[] = अणु
	अणु .compatible = "qcom,sdm660-a2noc", .data = &sdm660_a2noc पूर्ण,
	अणु .compatible = "qcom,sdm660-bimc", .data = &sdm660_bimc पूर्ण,
	अणु .compatible = "qcom,sdm660-cnoc", .data = &sdm660_cnoc पूर्ण,
	अणु .compatible = "qcom,sdm660-gnoc", .data = &sdm660_gnoc पूर्ण,
	अणु .compatible = "qcom,sdm660-mnoc", .data = &sdm660_mnoc पूर्ण,
	अणु .compatible = "qcom,sdm660-snoc", .data = &sdm660_snoc पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sdm660_noc_of_match);

अटल काष्ठा platक्रमm_driver sdm660_noc_driver = अणु
	.probe = qnoc_probe,
	.हटाओ = qnoc_हटाओ,
	.driver = अणु
		.name = "qnoc-sdm660",
		.of_match_table = sdm660_noc_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sdm660_noc_driver);
MODULE_DESCRIPTION("Qualcomm sdm660 NoC driver");
MODULE_LICENSE("GPL v2");
