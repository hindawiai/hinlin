<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Qualcomm SDX55 पूर्णांकerconnect driver
 * Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>
 *
 * Copyright (c) 2021, Linaro Ltd.
 *
 */

#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerconnect.h>
#समावेश <linux/पूर्णांकerconnect-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <dt-bindings/पूर्णांकerconnect/qcom,sdx55.h>

#समावेश "bcm-voter.h"
#समावेश "icc-rpmh.h"
#समावेश "sdx55.h"

DEFINE_QNODE(ipa_core_master, SDX55_MASTER_IPA_CORE, 1, 8, SDX55_SLAVE_IPA_CORE);
DEFINE_QNODE(llcc_mc, SDX55_MASTER_LLCC, 4, 4, SDX55_SLAVE_EBI_CH0);
DEFINE_QNODE(acm_tcu, SDX55_MASTER_TCU_0, 1, 8, SDX55_SLAVE_LLCC, SDX55_SLAVE_MEM_NOC_SNOC, SDX55_SLAVE_MEM_NOC_PCIE_SNOC);
DEFINE_QNODE(qnm_snoc_gc, SDX55_MASTER_SNOC_GC_MEM_NOC, 1, 8, SDX55_SLAVE_LLCC);
DEFINE_QNODE(xm_apps_rdwr, SDX55_MASTER_AMPSS_M0, 1, 16, SDX55_SLAVE_LLCC, SDX55_SLAVE_MEM_NOC_SNOC, SDX55_SLAVE_MEM_NOC_PCIE_SNOC);
DEFINE_QNODE(qhm_audio, SDX55_MASTER_AUDIO, 1, 4, SDX55_SLAVE_ANOC_SNOC);
DEFINE_QNODE(qhm_blsp1, SDX55_MASTER_BLSP_1, 1, 4, SDX55_SLAVE_ANOC_SNOC);
DEFINE_QNODE(qhm_qdss_bam, SDX55_MASTER_QDSS_BAM, 1, 4, SDX55_SLAVE_SNOC_CFG, SDX55_SLAVE_EMAC_CFG, SDX55_SLAVE_USB3, SDX55_SLAVE_TLMM, SDX55_SLAVE_SPMI_FETCHER, SDX55_SLAVE_QDSS_CFG, SDX55_SLAVE_PDM, SDX55_SLAVE_SNOC_MEM_NOC_GC, SDX55_SLAVE_TCSR, SDX55_SLAVE_CNOC_DDRSS, SDX55_SLAVE_SPMI_VGI_COEX, SDX55_SLAVE_QPIC, SDX55_SLAVE_OCIMEM, SDX55_SLAVE_IPA_CFG, SDX55_SLAVE_USB3_PHY_CFG, SDX55_SLAVE_AOP, SDX55_SLAVE_BLSP_1, SDX55_SLAVE_SDCC_1, SDX55_SLAVE_CNOC_MSS, SDX55_SLAVE_PCIE_PARF, SDX55_SLAVE_ECC_CFG, SDX55_SLAVE_AUDIO, SDX55_SLAVE_AOSS, SDX55_SLAVE_PRNG, SDX55_SLAVE_CRYPTO_0_CFG, SDX55_SLAVE_TCU, SDX55_SLAVE_CLK_CTL, SDX55_SLAVE_IMEM_CFG);
DEFINE_QNODE(qhm_qpic, SDX55_MASTER_QPIC, 1, 4, SDX55_SLAVE_AOSS, SDX55_SLAVE_IPA_CFG, SDX55_SLAVE_ANOC_SNOC, SDX55_SLAVE_AOP, SDX55_SLAVE_AUDIO);
DEFINE_QNODE(qhm_snoc_cfg, SDX55_MASTER_SNOC_CFG, 1, 4, SDX55_SLAVE_SERVICE_SNOC);
DEFINE_QNODE(qhm_spmi_fetcher1, SDX55_MASTER_SPMI_FETCHER, 1, 4, SDX55_SLAVE_AOSS, SDX55_SLAVE_ANOC_SNOC, SDX55_SLAVE_AOP);
DEFINE_QNODE(qnm_aggre_noc, SDX55_MASTER_ANOC_SNOC, 1, 8, SDX55_SLAVE_PCIE_0, SDX55_SLAVE_SNOC_CFG, SDX55_SLAVE_SDCC_1, SDX55_SLAVE_TLMM, SDX55_SLAVE_SPMI_FETCHER, SDX55_SLAVE_QDSS_CFG, SDX55_SLAVE_PDM, SDX55_SLAVE_SNOC_MEM_NOC_GC, SDX55_SLAVE_TCSR, SDX55_SLAVE_CNOC_DDRSS, SDX55_SLAVE_SPMI_VGI_COEX, SDX55_SLAVE_QDSS_STM, SDX55_SLAVE_QPIC, SDX55_SLAVE_OCIMEM, SDX55_SLAVE_IPA_CFG, SDX55_SLAVE_USB3_PHY_CFG, SDX55_SLAVE_AOP, SDX55_SLAVE_BLSP_1, SDX55_SLAVE_USB3, SDX55_SLAVE_CNOC_MSS, SDX55_SLAVE_PCIE_PARF, SDX55_SLAVE_ECC_CFG, SDX55_SLAVE_APPSS, SDX55_SLAVE_AUDIO, SDX55_SLAVE_AOSS, SDX55_SLAVE_PRNG, SDX55_SLAVE_CRYPTO_0_CFG, SDX55_SLAVE_TCU, SDX55_SLAVE_CLK_CTL, SDX55_SLAVE_IMEM_CFG);
DEFINE_QNODE(qnm_ipa, SDX55_MASTER_IPA, 1, 8, SDX55_SLAVE_SNOC_CFG, SDX55_SLAVE_EMAC_CFG, SDX55_SLAVE_USB3, SDX55_SLAVE_AOSS, SDX55_SLAVE_SPMI_FETCHER, SDX55_SLAVE_QDSS_CFG, SDX55_SLAVE_PDM, SDX55_SLAVE_SNOC_MEM_NOC_GC, SDX55_SLAVE_TCSR, SDX55_SLAVE_CNOC_DDRSS, SDX55_SLAVE_QDSS_STM, SDX55_SLAVE_QPIC, SDX55_SLAVE_OCIMEM, SDX55_SLAVE_IPA_CFG, SDX55_SLAVE_USB3_PHY_CFG, SDX55_SLAVE_AOP, SDX55_SLAVE_BLSP_1, SDX55_SLAVE_SDCC_1, SDX55_SLAVE_CNOC_MSS, SDX55_SLAVE_PCIE_PARF, SDX55_SLAVE_ECC_CFG, SDX55_SLAVE_AUDIO, SDX55_SLAVE_TLMM, SDX55_SLAVE_PRNG, SDX55_SLAVE_CRYPTO_0_CFG, SDX55_SLAVE_CLK_CTL, SDX55_SLAVE_IMEM_CFG);
DEFINE_QNODE(qnm_memnoc, SDX55_MASTER_MEM_NOC_SNOC, 1, 8, SDX55_SLAVE_SNOC_CFG, SDX55_SLAVE_EMAC_CFG, SDX55_SLAVE_USB3, SDX55_SLAVE_TLMM, SDX55_SLAVE_SPMI_FETCHER, SDX55_SLAVE_QDSS_CFG, SDX55_SLAVE_PDM, SDX55_SLAVE_TCSR, SDX55_SLAVE_CNOC_DDRSS, SDX55_SLAVE_SPMI_VGI_COEX, SDX55_SLAVE_QDSS_STM, SDX55_SLAVE_QPIC, SDX55_SLAVE_OCIMEM, SDX55_SLAVE_IPA_CFG, SDX55_SLAVE_USB3_PHY_CFG, SDX55_SLAVE_AOP, SDX55_SLAVE_BLSP_1, SDX55_SLAVE_SDCC_1, SDX55_SLAVE_CNOC_MSS, SDX55_SLAVE_PCIE_PARF, SDX55_SLAVE_ECC_CFG, SDX55_SLAVE_APPSS,  SDX55_SLAVE_AUDIO, SDX55_SLAVE_AOSS, SDX55_SLAVE_PRNG, SDX55_SLAVE_CRYPTO_0_CFG, SDX55_SLAVE_TCU, SDX55_SLAVE_CLK_CTL, SDX55_SLAVE_IMEM_CFG);
DEFINE_QNODE(qnm_memnoc_pcie, SDX55_MASTER_MEM_NOC_PCIE_SNOC, 1, 8, SDX55_SLAVE_PCIE_0);
DEFINE_QNODE(qxm_crypto, SDX55_MASTER_CRYPTO_CORE_0, 1, 8, SDX55_SLAVE_AOSS, SDX55_SLAVE_ANOC_SNOC, SDX55_SLAVE_AOP);
DEFINE_QNODE(xm_emac, SDX55_MASTER_EMAC, 1, 8, SDX55_SLAVE_ANOC_SNOC);
DEFINE_QNODE(xm_ipa2pcie_slv, SDX55_MASTER_IPA_PCIE, 1, 8, SDX55_SLAVE_PCIE_0);
DEFINE_QNODE(xm_pcie, SDX55_MASTER_PCIE, 1, 8, SDX55_SLAVE_ANOC_SNOC);
DEFINE_QNODE(xm_qdss_etr, SDX55_MASTER_QDSS_ETR, 1, 8, SDX55_SLAVE_SNOC_CFG, SDX55_SLAVE_EMAC_CFG, SDX55_SLAVE_USB3, SDX55_SLAVE_AOSS, SDX55_SLAVE_SPMI_FETCHER, SDX55_SLAVE_QDSS_CFG, SDX55_SLAVE_PDM, SDX55_SLAVE_SNOC_MEM_NOC_GC, SDX55_SLAVE_TCSR, SDX55_SLAVE_CNOC_DDRSS, SDX55_SLAVE_SPMI_VGI_COEX, SDX55_SLAVE_QPIC, SDX55_SLAVE_OCIMEM, SDX55_SLAVE_IPA_CFG, SDX55_SLAVE_USB3_PHY_CFG, SDX55_SLAVE_AOP, SDX55_SLAVE_BLSP_1, SDX55_SLAVE_SDCC_1, SDX55_SLAVE_CNOC_MSS, SDX55_SLAVE_PCIE_PARF, SDX55_SLAVE_ECC_CFG, SDX55_SLAVE_AUDIO, SDX55_SLAVE_AOSS, SDX55_SLAVE_PRNG, SDX55_SLAVE_CRYPTO_0_CFG, SDX55_SLAVE_TCU, SDX55_SLAVE_CLK_CTL, SDX55_SLAVE_IMEM_CFG);
DEFINE_QNODE(xm_sdc1, SDX55_MASTER_SDCC_1, 1, 8, SDX55_SLAVE_AOSS, SDX55_SLAVE_IPA_CFG, SDX55_SLAVE_ANOC_SNOC, SDX55_SLAVE_AOP, SDX55_SLAVE_AUDIO);
DEFINE_QNODE(xm_usb3, SDX55_MASTER_USB3, 1, 8, SDX55_SLAVE_ANOC_SNOC);
DEFINE_QNODE(ipa_core_slave, SDX55_SLAVE_IPA_CORE, 1, 8);
DEFINE_QNODE(ebi, SDX55_SLAVE_EBI_CH0, 1, 4);
DEFINE_QNODE(qns_llcc, SDX55_SLAVE_LLCC, 1, 16, SDX55_SLAVE_EBI_CH0);
DEFINE_QNODE(qns_memnoc_snoc, SDX55_SLAVE_MEM_NOC_SNOC, 1, 8, SDX55_MASTER_MEM_NOC_SNOC);
DEFINE_QNODE(qns_sys_pcie, SDX55_SLAVE_MEM_NOC_PCIE_SNOC, 1, 8, SDX55_MASTER_MEM_NOC_PCIE_SNOC);
DEFINE_QNODE(qhs_aop, SDX55_SLAVE_AOP, 1, 4);
DEFINE_QNODE(qhs_aoss, SDX55_SLAVE_AOSS, 1, 4);
DEFINE_QNODE(qhs_apss, SDX55_SLAVE_APPSS, 1, 4);
DEFINE_QNODE(qhs_audio, SDX55_SLAVE_AUDIO, 1, 4);
DEFINE_QNODE(qhs_blsp1, SDX55_SLAVE_BLSP_1, 1, 4);
DEFINE_QNODE(qhs_clk_ctl, SDX55_SLAVE_CLK_CTL, 1, 4);
DEFINE_QNODE(qhs_crypto0_cfg, SDX55_SLAVE_CRYPTO_0_CFG, 1, 4);
DEFINE_QNODE(qhs_ddrss_cfg, SDX55_SLAVE_CNOC_DDRSS, 1, 4);
DEFINE_QNODE(qhs_ecc_cfg, SDX55_SLAVE_ECC_CFG, 1, 4);
DEFINE_QNODE(qhs_emac_cfg, SDX55_SLAVE_EMAC_CFG, 1, 4);
DEFINE_QNODE(qhs_imem_cfg, SDX55_SLAVE_IMEM_CFG, 1, 4);
DEFINE_QNODE(qhs_ipa, SDX55_SLAVE_IPA_CFG, 1, 4);
DEFINE_QNODE(qhs_mss_cfg, SDX55_SLAVE_CNOC_MSS, 1, 4);
DEFINE_QNODE(qhs_pcie_parf, SDX55_SLAVE_PCIE_PARF, 1, 4);
DEFINE_QNODE(qhs_pdm, SDX55_SLAVE_PDM, 1, 4);
DEFINE_QNODE(qhs_prng, SDX55_SLAVE_PRNG, 1, 4);
DEFINE_QNODE(qhs_qdss_cfg, SDX55_SLAVE_QDSS_CFG, 1, 4);
DEFINE_QNODE(qhs_qpic, SDX55_SLAVE_QPIC, 1, 4);
DEFINE_QNODE(qhs_sdc1, SDX55_SLAVE_SDCC_1, 1, 4);
DEFINE_QNODE(qhs_snoc_cfg, SDX55_SLAVE_SNOC_CFG, 1, 4, SDX55_MASTER_SNOC_CFG);
DEFINE_QNODE(qhs_spmi_fetcher, SDX55_SLAVE_SPMI_FETCHER, 1, 4);
DEFINE_QNODE(qhs_spmi_vgi_coex, SDX55_SLAVE_SPMI_VGI_COEX, 1, 4);
DEFINE_QNODE(qhs_tcsr, SDX55_SLAVE_TCSR, 1, 4);
DEFINE_QNODE(qhs_tlmm, SDX55_SLAVE_TLMM, 1, 4);
DEFINE_QNODE(qhs_usb3, SDX55_SLAVE_USB3, 1, 4);
DEFINE_QNODE(qhs_usb3_phy, SDX55_SLAVE_USB3_PHY_CFG, 1, 4);
DEFINE_QNODE(qns_aggre_noc, SDX55_SLAVE_ANOC_SNOC, 1, 8, SDX55_MASTER_ANOC_SNOC);
DEFINE_QNODE(qns_snoc_memnoc, SDX55_SLAVE_SNOC_MEM_NOC_GC, 1, 8, SDX55_MASTER_SNOC_GC_MEM_NOC);
DEFINE_QNODE(qxs_imem, SDX55_SLAVE_OCIMEM, 1, 8);
DEFINE_QNODE(srvc_snoc, SDX55_SLAVE_SERVICE_SNOC, 1, 4);
DEFINE_QNODE(xs_pcie, SDX55_SLAVE_PCIE_0, 1, 8);
DEFINE_QNODE(xs_qdss_sपंचांग, SDX55_SLAVE_QDSS_STM, 1, 4);
DEFINE_QNODE(xs_sys_tcu_cfg, SDX55_SLAVE_TCU, 1, 8);

DEFINE_QBCM(bcm_mc0, "MC0", true, &ebi);
DEFINE_QBCM(bcm_sh0, "SH0", true, &qns_llcc);
DEFINE_QBCM(bcm_ce0, "CE0", false, &qxm_crypto);
DEFINE_QBCM(bcm_ip0, "IP0", false, &ipa_core_slave);
DEFINE_QBCM(bcm_pn0, "PN0", false, &qhm_snoc_cfg);
DEFINE_QBCM(bcm_sh3, "SH3", false, &xm_apps_rdwr);
DEFINE_QBCM(bcm_sh4, "SH4", false, &qns_memnoc_snoc, &qns_sys_pcie);
DEFINE_QBCM(bcm_sn0, "SN0", true, &qns_snoc_memnoc);
DEFINE_QBCM(bcm_sn1, "SN1", false, &qxs_imem);
DEFINE_QBCM(bcm_pn1, "PN1", false, &xm_sdc1);
DEFINE_QBCM(bcm_pn2, "PN2", false, &qhm_audio, &qhm_spmi_fetcher1);
DEFINE_QBCM(bcm_sn3, "SN3", false, &xs_qdss_sपंचांग);
DEFINE_QBCM(bcm_pn3, "PN3", false, &qhm_blsp1, &qhm_qpic);
DEFINE_QBCM(bcm_sn4, "SN4", false, &xs_sys_tcu_cfg);
DEFINE_QBCM(bcm_pn5, "PN5", false, &qxm_crypto);
DEFINE_QBCM(bcm_sn6, "SN6", false, &xs_pcie);
DEFINE_QBCM(bcm_sn7, "SN7", false, &qnm_aggre_noc, &xm_emac, &xm_emac, &xm_usb3,
	    &qns_aggre_noc);
DEFINE_QBCM(bcm_sn8, "SN8", false, &qhm_qdss_bam, &xm_qdss_etr);
DEFINE_QBCM(bcm_sn9, "SN9", false, &qnm_memnoc);
DEFINE_QBCM(bcm_sn10, "SN10", false, &qnm_memnoc_pcie);
DEFINE_QBCM(bcm_sn11, "SN11", false, &qnm_ipa, &xm_ipa2pcie_slv);

अटल काष्ठा qcom_icc_bcm *mc_virt_bcms[] = अणु
	&bcm_mc0,
पूर्ण;

अटल काष्ठा qcom_icc_node *mc_virt_nodes[] = अणु
	[MASTER_LLCC] = &llcc_mc,
	[SLAVE_EBI_CH0] = &ebi,
पूर्ण;

अटल स्थिर काष्ठा qcom_icc_desc sdx55_mc_virt = अणु
	.nodes = mc_virt_nodes,
	.num_nodes = ARRAY_SIZE(mc_virt_nodes),
	.bcms = mc_virt_bcms,
	.num_bcms = ARRAY_SIZE(mc_virt_bcms),
पूर्ण;

अटल काष्ठा qcom_icc_bcm *mem_noc_bcms[] = अणु
	&bcm_sh0,
	&bcm_sh3,
	&bcm_sh4,
पूर्ण;

अटल काष्ठा qcom_icc_node *mem_noc_nodes[] = अणु
	[MASTER_TCU_0] = &acm_tcu,
	[MASTER_SNOC_GC_MEM_NOC] = &qnm_snoc_gc,
	[MASTER_AMPSS_M0] = &xm_apps_rdwr,
	[SLAVE_LLCC] = &qns_llcc,
	[SLAVE_MEM_NOC_SNOC] = &qns_memnoc_snoc,
	[SLAVE_MEM_NOC_PCIE_SNOC] = &qns_sys_pcie,
पूर्ण;

अटल स्थिर काष्ठा qcom_icc_desc sdx55_mem_noc = अणु
	.nodes = mem_noc_nodes,
	.num_nodes = ARRAY_SIZE(mem_noc_nodes),
	.bcms = mem_noc_bcms,
	.num_bcms = ARRAY_SIZE(mem_noc_bcms),
पूर्ण;

अटल काष्ठा qcom_icc_bcm *प्रणाली_noc_bcms[] = अणु
	&bcm_ce0,
	&bcm_pn0,
	&bcm_pn1,
	&bcm_pn2,
	&bcm_pn3,
	&bcm_pn5,
	&bcm_sn0,
	&bcm_sn1,
	&bcm_sn3,
	&bcm_sn4,
	&bcm_sn6,
	&bcm_sn7,
	&bcm_sn8,
	&bcm_sn9,
	&bcm_sn10,
	&bcm_sn11,
पूर्ण;

अटल काष्ठा qcom_icc_node *प्रणाली_noc_nodes[] = अणु
	[MASTER_AUDIO] = &qhm_audio,
	[MASTER_BLSP_1] = &qhm_blsp1,
	[MASTER_QDSS_BAM] = &qhm_qdss_bam,
	[MASTER_QPIC] = &qhm_qpic,
	[MASTER_SNOC_CFG] = &qhm_snoc_cfg,
	[MASTER_SPMI_FETCHER] = &qhm_spmi_fetcher1,
	[MASTER_ANOC_SNOC] = &qnm_aggre_noc,
	[MASTER_IPA] = &qnm_ipa,
	[MASTER_MEM_NOC_SNOC] = &qnm_memnoc,
	[MASTER_MEM_NOC_PCIE_SNOC] = &qnm_memnoc_pcie,
	[MASTER_CRYPTO_CORE_0] = &qxm_crypto,
	[MASTER_EMAC] = &xm_emac,
	[MASTER_IPA_PCIE] = &xm_ipa2pcie_slv,
	[MASTER_PCIE] = &xm_pcie,
	[MASTER_QDSS_ETR] = &xm_qdss_etr,
	[MASTER_SDCC_1] = &xm_sdc1,
	[MASTER_USB3] = &xm_usb3,
	[SLAVE_AOP] = &qhs_aop,
	[SLAVE_AOSS] = &qhs_aoss,
	[SLAVE_APPSS] = &qhs_apss,
	[SLAVE_AUDIO] = &qhs_audio,
	[SLAVE_BLSP_1] = &qhs_blsp1,
	[SLAVE_CLK_CTL] = &qhs_clk_ctl,
	[SLAVE_CRYPTO_0_CFG] = &qhs_crypto0_cfg,
	[SLAVE_CNOC_DDRSS] = &qhs_ddrss_cfg,
	[SLAVE_ECC_CFG] = &qhs_ecc_cfg,
	[SLAVE_EMAC_CFG] = &qhs_emac_cfg,
	[SLAVE_IMEM_CFG] = &qhs_imem_cfg,
	[SLAVE_IPA_CFG] = &qhs_ipa,
	[SLAVE_CNOC_MSS] = &qhs_mss_cfg,
	[SLAVE_PCIE_PARF] = &qhs_pcie_parf,
	[SLAVE_PDM] = &qhs_pdm,
	[SLAVE_PRNG] = &qhs_prng,
	[SLAVE_QDSS_CFG] = &qhs_qdss_cfg,
	[SLAVE_QPIC] = &qhs_qpic,
	[SLAVE_SDCC_1] = &qhs_sdc1,
	[SLAVE_SNOC_CFG] = &qhs_snoc_cfg,
	[SLAVE_SPMI_FETCHER] = &qhs_spmi_fetcher,
	[SLAVE_SPMI_VGI_COEX] = &qhs_spmi_vgi_coex,
	[SLAVE_TCSR] = &qhs_tcsr,
	[SLAVE_TLMM] = &qhs_tlmm,
	[SLAVE_USB3] = &qhs_usb3,
	[SLAVE_USB3_PHY_CFG] = &qhs_usb3_phy,
	[SLAVE_ANOC_SNOC] = &qns_aggre_noc,
	[SLAVE_SNOC_MEM_NOC_GC] = &qns_snoc_memnoc,
	[SLAVE_OCIMEM] = &qxs_imem,
	[SLAVE_SERVICE_SNOC] = &srvc_snoc,
	[SLAVE_PCIE_0] = &xs_pcie,
	[SLAVE_QDSS_STM] = &xs_qdss_sपंचांग,
	[SLAVE_TCU] = &xs_sys_tcu_cfg,
पूर्ण;

अटल स्थिर काष्ठा qcom_icc_desc sdx55_प्रणाली_noc = अणु
	.nodes = प्रणाली_noc_nodes,
	.num_nodes = ARRAY_SIZE(प्रणाली_noc_nodes),
	.bcms = प्रणाली_noc_bcms,
	.num_bcms = ARRAY_SIZE(प्रणाली_noc_bcms),
पूर्ण;

अटल काष्ठा qcom_icc_bcm *ipa_virt_bcms[] = अणु
	&bcm_ip0,
पूर्ण;

अटल काष्ठा qcom_icc_node *ipa_virt_nodes[] = अणु
	[MASTER_IPA_CORE] = &ipa_core_master,
	[SLAVE_IPA_CORE] = &ipa_core_slave,
पूर्ण;

अटल स्थिर काष्ठा qcom_icc_desc sdx55_ipa_virt = अणु
	.nodes = ipa_virt_nodes,
	.num_nodes = ARRAY_SIZE(ipa_virt_nodes),
	.bcms = ipa_virt_bcms,
	.num_bcms = ARRAY_SIZE(ipa_virt_bcms),
पूर्ण;

अटल पूर्णांक qnoc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा qcom_icc_desc *desc;
	काष्ठा icc_onecell_data *data;
	काष्ठा icc_provider *provider;
	काष्ठा qcom_icc_node **qnodes;
	काष्ठा qcom_icc_provider *qp;
	काष्ठा icc_node *node;
	माप_प्रकार num_nodes, i;
	पूर्णांक ret;

	desc = device_get_match_data(&pdev->dev);
	अगर (!desc)
		वापस -EINVAL;

	qnodes = desc->nodes;
	num_nodes = desc->num_nodes;

	qp = devm_kzalloc(&pdev->dev, माप(*qp), GFP_KERNEL);
	अगर (!qp)
		वापस -ENOMEM;

	data = devm_kसुस्मृति(&pdev->dev, num_nodes, माप(*node), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	provider = &qp->provider;
	provider->dev = &pdev->dev;
	provider->set = qcom_icc_set;
	provider->pre_aggregate = qcom_icc_pre_aggregate;
	provider->aggregate = qcom_icc_aggregate;
	provider->xlate = of_icc_xlate_onecell;
	INIT_LIST_HEAD(&provider->nodes);
	provider->data = data;

	qp->dev = &pdev->dev;
	qp->bcms = desc->bcms;
	qp->num_bcms = desc->num_bcms;

	qp->voter = of_bcm_voter_get(qp->dev, शून्य);
	अगर (IS_ERR(qp->voter))
		वापस PTR_ERR(qp->voter);

	ret = icc_provider_add(provider);
	अगर (ret) अणु
		dev_err(&pdev->dev, "error adding interconnect provider\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < qp->num_bcms; i++)
		qcom_icc_bcm_init(qp->bcms[i], &pdev->dev);

	क्रम (i = 0; i < num_nodes; i++) अणु
		माप_प्रकार j;

		अगर (!qnodes[i])
			जारी;

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
	icc_provider_del(provider);
	वापस ret;
पूर्ण

अटल पूर्णांक qnoc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_icc_provider *qp = platक्रमm_get_drvdata(pdev);

	icc_nodes_हटाओ(&qp->provider);
	वापस icc_provider_del(&qp->provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id qnoc_of_match[] = अणु
	अणु .compatible = "qcom,sdx55-mc-virt",
	  .data = &sdx55_mc_virtपूर्ण,
	अणु .compatible = "qcom,sdx55-mem-noc",
	  .data = &sdx55_mem_nocपूर्ण,
	अणु .compatible = "qcom,sdx55-system-noc",
	  .data = &sdx55_प्रणाली_nocपूर्ण,
	अणु .compatible = "qcom,sdx55-ipa-virt",
	  .data = &sdx55_ipa_virtपूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qnoc_of_match);

अटल काष्ठा platक्रमm_driver qnoc_driver = अणु
	.probe = qnoc_probe,
	.हटाओ = qnoc_हटाओ,
	.driver = अणु
		.name = "qnoc-sdx55",
		.of_match_table = qnoc_of_match,
		.sync_state = icc_sync_state,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qnoc_driver);

MODULE_DESCRIPTION("Qualcomm SDX55 NoC driver");
MODULE_AUTHOR("Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>");
MODULE_LICENSE("GPL v2");
