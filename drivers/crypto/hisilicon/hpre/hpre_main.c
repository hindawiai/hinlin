<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018-2019 HiSilicon Limited. */
#समावेश <linux/acpi.h>
#समावेश <linux/aer.h>
#समावेश <linux/bitops.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/topology.h>
#समावेश <linux/uacce.h>
#समावेश "hpre.h"

#घोषणा HPRE_QM_ABNML_INT_MASK		0x100004
#घोषणा HPRE_CTRL_CNT_CLR_CE_BIT	BIT(0)
#घोषणा HPRE_COMM_CNT_CLR_CE		0x0
#घोषणा HPRE_CTRL_CNT_CLR_CE		0x301000
#घोषणा HPRE_FSM_MAX_CNT		0x301008
#घोषणा HPRE_VFG_AXQOS			0x30100c
#घोषणा HPRE_VFG_AXCACHE		0x301010
#घोषणा HPRE_RDCHN_INI_CFG		0x301014
#घोषणा HPRE_AWUSR_FP_CFG		0x301018
#घोषणा HPRE_BD_ENDIAN			0x301020
#घोषणा HPRE_ECC_BYPASS			0x301024
#घोषणा HPRE_RAS_WIDTH_CFG		0x301028
#घोषणा HPRE_POISON_BYPASS		0x30102c
#घोषणा HPRE_BD_ARUSR_CFG		0x301030
#घोषणा HPRE_BD_AWUSR_CFG		0x301034
#घोषणा HPRE_TYPES_ENB			0x301038
#घोषणा HPRE_RSA_ENB			BIT(0)
#घोषणा HPRE_ECC_ENB			BIT(1)
#घोषणा HPRE_DATA_RUSER_CFG		0x30103c
#घोषणा HPRE_DATA_WUSER_CFG		0x301040
#घोषणा HPRE_INT_MASK			0x301400
#घोषणा HPRE_INT_STATUS			0x301800
#घोषणा HPRE_CORE_INT_ENABLE		0
#घोषणा HPRE_CORE_INT_DISABLE		0x003fffff
#घोषणा HPRE_RDCHN_INI_ST		0x301a00
#घोषणा HPRE_CLSTR_BASE			0x302000
#घोषणा HPRE_CORE_EN_OFFSET		0x04
#घोषणा HPRE_CORE_INI_CFG_OFFSET	0x20
#घोषणा HPRE_CORE_INI_STATUS_OFFSET	0x80
#घोषणा HPRE_CORE_HTBT_WARN_OFFSET	0x8c
#घोषणा HPRE_CORE_IS_SCHD_OFFSET	0x90

#घोषणा HPRE_RAS_CE_ENB			0x301410
#घोषणा HPRE_HAC_RAS_CE_ENABLE		(BIT(0) | BIT(22) | BIT(23))
#घोषणा HPRE_RAS_NFE_ENB		0x301414
#घोषणा HPRE_HAC_RAS_NFE_ENABLE		0x3ffffe
#घोषणा HPRE_RAS_FE_ENB			0x301418
#घोषणा HPRE_HAC_RAS_FE_ENABLE		0

#घोषणा HPRE_CORE_ENB		(HPRE_CLSTR_BASE + HPRE_CORE_EN_OFFSET)
#घोषणा HPRE_CORE_INI_CFG	(HPRE_CLSTR_BASE + HPRE_CORE_INI_CFG_OFFSET)
#घोषणा HPRE_CORE_INI_STATUS (HPRE_CLSTR_BASE + HPRE_CORE_INI_STATUS_OFFSET)
#घोषणा HPRE_HAC_ECC1_CNT		0x301a04
#घोषणा HPRE_HAC_ECC2_CNT		0x301a08
#घोषणा HPRE_HAC_INT_STATUS		0x301800
#घोषणा HPRE_HAC_SOURCE_INT		0x301600
#घोषणा HPRE_CLSTR_ADDR_INTRVL		0x1000
#घोषणा HPRE_CLUSTER_INQURY		0x100
#घोषणा HPRE_CLSTR_ADDR_INQRY_RSLT	0x104
#घोषणा HPRE_TIMEOUT_ABNML_BIT		6
#घोषणा HPRE_PASID_EN_BIT		9
#घोषणा HPRE_REG_RD_INTVRL_US		10
#घोषणा HPRE_REG_RD_TMOUT_US		1000
#घोषणा HPRE_DBGFS_VAL_MAX_LEN		20
#घोषणा HPRE_PCI_DEVICE_ID		0xa258
#घोषणा HPRE_PCI_VF_DEVICE_ID		0xa259
#घोषणा HPRE_ADDR(qm, offset)		((qm)->io_base + (offset))
#घोषणा HPRE_QM_USR_CFG_MASK		0xfffffffe
#घोषणा HPRE_QM_AXI_CFG_MASK		0xffff
#घोषणा HPRE_QM_VFG_AX_MASK		0xff
#घोषणा HPRE_BD_USR_MASK		0x3
#घोषणा HPRE_CLUSTER_CORE_MASK_V2	0xf
#घोषणा HPRE_CLUSTER_CORE_MASK_V3	0xff

#घोषणा HPRE_AM_OOO_SHUTDOWN_ENB	0x301044
#घोषणा HPRE_AM_OOO_SHUTDOWN_ENABLE	BIT(0)
#घोषणा HPRE_WR_MSI_PORT		BIT(2)

#घोषणा HPRE_CORE_ECC_2BIT_ERR		BIT(1)
#घोषणा HPRE_OOO_ECC_2BIT_ERR		BIT(5)

#घोषणा HPRE_QM_BME_FLR			BIT(7)
#घोषणा HPRE_QM_PM_FLR			BIT(11)
#घोषणा HPRE_QM_SRIOV_FLR		BIT(12)

#घोषणा HPRE_CLUSTERS_NUM(qm)		\
	(((qm)->ver >= QM_HW_V3) ? HPRE_CLUSTERS_NUM_V3 : HPRE_CLUSTERS_NUM_V2)
#घोषणा HPRE_CLUSTER_CORE_MASK(qm)	\
	(((qm)->ver >= QM_HW_V3) ? HPRE_CLUSTER_CORE_MASK_V3 :\
		HPRE_CLUSTER_CORE_MASK_V2)
#घोषणा HPRE_VIA_MSI_DSM		1
#घोषणा HPRE_SQE_MASK_OFFSET		8
#घोषणा HPRE_SQE_MASK_LEN		24

अटल स्थिर अक्षर hpre_name[] = "hisi_hpre";
अटल काष्ठा dentry *hpre_debugfs_root;
अटल स्थिर काष्ठा pci_device_id hpre_dev_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_HUAWEI, HPRE_PCI_DEVICE_ID) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_HUAWEI, HPRE_PCI_VF_DEVICE_ID) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, hpre_dev_ids);

काष्ठा hpre_hw_error अणु
	u32 पूर्णांक_msk;
	स्थिर अक्षर *msg;
पूर्ण;

अटल काष्ठा hisi_qm_list hpre_devices = अणु
	.रेजिस्टर_to_crypto	= hpre_algs_रेजिस्टर,
	.unरेजिस्टर_from_crypto	= hpre_algs_unरेजिस्टर,
पूर्ण;

अटल स्थिर अक्षर * स्थिर hpre_debug_file_name[] = अणु
	[HPRE_CLEAR_ENABLE] = "rdclr_en",
	[HPRE_CLUSTER_CTRL] = "cluster_ctrl",
पूर्ण;

अटल स्थिर काष्ठा hpre_hw_error hpre_hw_errors[] = अणु
	अणु .पूर्णांक_msk = BIT(0), .msg = "core_ecc_1bit_err_int_set" पूर्ण,
	अणु .पूर्णांक_msk = BIT(1), .msg = "core_ecc_2bit_err_int_set" पूर्ण,
	अणु .पूर्णांक_msk = BIT(2), .msg = "dat_wb_poison_int_set" पूर्ण,
	अणु .पूर्णांक_msk = BIT(3), .msg = "dat_rd_poison_int_set" पूर्ण,
	अणु .पूर्णांक_msk = BIT(4), .msg = "bd_rd_poison_int_set" पूर्ण,
	अणु .पूर्णांक_msk = BIT(5), .msg = "ooo_ecc_2bit_err_int_set" पूर्ण,
	अणु .पूर्णांक_msk = BIT(6), .msg = "cluster1_shb_timeout_int_set" पूर्ण,
	अणु .पूर्णांक_msk = BIT(7), .msg = "cluster2_shb_timeout_int_set" पूर्ण,
	अणु .पूर्णांक_msk = BIT(8), .msg = "cluster3_shb_timeout_int_set" पूर्ण,
	अणु .पूर्णांक_msk = BIT(9), .msg = "cluster4_shb_timeout_int_set" पूर्ण,
	अणु .पूर्णांक_msk = GENMASK(15, 10), .msg = "ooo_rdrsp_err_int_set" पूर्ण,
	अणु .पूर्णांक_msk = GENMASK(21, 16), .msg = "ooo_wrrsp_err_int_set" पूर्ण,
	अणु .पूर्णांक_msk = BIT(22), .msg = "pt_rng_timeout_int_set"पूर्ण,
	अणु .पूर्णांक_msk = BIT(23), .msg = "sva_fsm_timeout_int_set"पूर्ण,
	अणु
		/* sentinel */
	पूर्ण
पूर्ण;

अटल स्थिर u64 hpre_cluster_offsets[] = अणु
	[HPRE_CLUSTER0] =
		HPRE_CLSTR_BASE + HPRE_CLUSTER0 * HPRE_CLSTR_ADDR_INTRVL,
	[HPRE_CLUSTER1] =
		HPRE_CLSTR_BASE + HPRE_CLUSTER1 * HPRE_CLSTR_ADDR_INTRVL,
	[HPRE_CLUSTER2] =
		HPRE_CLSTR_BASE + HPRE_CLUSTER2 * HPRE_CLSTR_ADDR_INTRVL,
	[HPRE_CLUSTER3] =
		HPRE_CLSTR_BASE + HPRE_CLUSTER3 * HPRE_CLSTR_ADDR_INTRVL,
पूर्ण;

अटल स्थिर काष्ठा debugfs_reg32 hpre_cluster_dfx_regs[] = अणु
	अणु"CORES_EN_STATUS          ",  HPRE_CORE_EN_OFFSETपूर्ण,
	अणु"CORES_INI_CFG              ",  HPRE_CORE_INI_CFG_OFFSETपूर्ण,
	अणु"CORES_INI_STATUS         ",  HPRE_CORE_INI_STATUS_OFFSETपूर्ण,
	अणु"CORES_HTBT_WARN         ",  HPRE_CORE_HTBT_WARN_OFFSETपूर्ण,
	अणु"CORES_IS_SCHD               ",  HPRE_CORE_IS_SCHD_OFFSETपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा debugfs_reg32 hpre_com_dfx_regs[] = अणु
	अणु"READ_CLR_EN          ",  HPRE_CTRL_CNT_CLR_CEपूर्ण,
	अणु"AXQOS                   ",  HPRE_VFG_AXQOSपूर्ण,
	अणु"AWUSR_CFG              ",  HPRE_AWUSR_FP_CFGपूर्ण,
	अणु"QM_ARUSR_MCFG1           ",  QM_ARUSER_M_CFG_1पूर्ण,
	अणु"QM_AWUSR_MCFG1           ",  QM_AWUSER_M_CFG_1पूर्ण,
	अणु"BD_ENDIAN               ",  HPRE_BD_ENDIANपूर्ण,
	अणु"ECC_CHECK_CTRL       ",  HPRE_ECC_BYPASSपूर्ण,
	अणु"RAS_INT_WIDTH       ",  HPRE_RAS_WIDTH_CFGपूर्ण,
	अणु"POISON_BYPASS       ",  HPRE_POISON_BYPASSपूर्ण,
	अणु"BD_ARUSER               ",  HPRE_BD_ARUSR_CFGपूर्ण,
	अणु"BD_AWUSER               ",  HPRE_BD_AWUSR_CFGपूर्ण,
	अणु"DATA_ARUSER            ",  HPRE_DATA_RUSER_CFGपूर्ण,
	अणु"DATA_AWUSER           ",  HPRE_DATA_WUSER_CFGपूर्ण,
	अणु"INT_STATUS               ",  HPRE_INT_STATUSपूर्ण,
पूर्ण;

अटल स्थिर अक्षर *hpre_dfx_files[HPRE_DFX_खाता_NUM] = अणु
	"send_cnt",
	"recv_cnt",
	"send_fail_cnt",
	"send_busy_cnt",
	"over_thrhld_cnt",
	"overtime_thrhld",
	"invalid_req_cnt"
पूर्ण;

अटल स्थिर काष्ठा kernel_param_ops hpre_uacce_mode_ops = अणु
	.set = uacce_mode_set,
	.get = param_get_पूर्णांक,
पूर्ण;

/*
 * uacce_mode = 0 means hpre only रेजिस्टर to crypto,
 * uacce_mode = 1 means hpre both रेजिस्टर to crypto and uacce.
 */
अटल u32 uacce_mode = UACCE_MODE_NOUACCE;
module_param_cb(uacce_mode, &hpre_uacce_mode_ops, &uacce_mode, 0444);
MODULE_PARM_DESC(uacce_mode, UACCE_MODE_DESC);

अटल पूर्णांक pf_q_num_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	वापस q_num_set(val, kp, HPRE_PCI_DEVICE_ID);
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops hpre_pf_q_num_ops = अणु
	.set = pf_q_num_set,
	.get = param_get_पूर्णांक,
पूर्ण;

अटल u32 pf_q_num = HPRE_PF_DEF_Q_NUM;
module_param_cb(pf_q_num, &hpre_pf_q_num_ops, &pf_q_num, 0444);
MODULE_PARM_DESC(pf_q_num, "Number of queues in PF of CS(2-1024)");

अटल स्थिर काष्ठा kernel_param_ops vfs_num_ops = अणु
	.set = vfs_num_set,
	.get = param_get_पूर्णांक,
पूर्ण;

अटल u32 vfs_num;
module_param_cb(vfs_num, &vfs_num_ops, &vfs_num, 0444);
MODULE_PARM_DESC(vfs_num, "Number of VFs to enable(1-63), 0(default)");

काष्ठा hisi_qp *hpre_create_qp(u8 type)
अणु
	पूर्णांक node = cpu_to_node(smp_processor_id());
	काष्ठा hisi_qp *qp = शून्य;
	पूर्णांक ret;

	अगर (type != HPRE_V2_ALG_TYPE && type != HPRE_V3_ECC_ALG_TYPE)
		वापस शून्य;

	/*
	 * type: 0 - RSA/DH. algorithm supported in V2,
	 *       1 - ECC algorithm in V3.
	 */
	ret = hisi_qm_alloc_qps_node(&hpre_devices, 1, type, node, &qp);
	अगर (!ret)
		वापस qp;

	वापस शून्य;
पूर्ण

अटल व्योम hpre_config_pasid(काष्ठा hisi_qm *qm)
अणु
	u32 val1, val2;

	अगर (qm->ver >= QM_HW_V3)
		वापस;

	val1 = पढ़ोl_relaxed(qm->io_base + HPRE_DATA_RUSER_CFG);
	val2 = पढ़ोl_relaxed(qm->io_base + HPRE_DATA_WUSER_CFG);
	अगर (qm->use_sva) अणु
		val1 |= BIT(HPRE_PASID_EN_BIT);
		val2 |= BIT(HPRE_PASID_EN_BIT);
	पूर्ण अन्यथा अणु
		val1 &= ~BIT(HPRE_PASID_EN_BIT);
		val2 &= ~BIT(HPRE_PASID_EN_BIT);
	पूर्ण
	ग_लिखोl_relaxed(val1, qm->io_base + HPRE_DATA_RUSER_CFG);
	ग_लिखोl_relaxed(val2, qm->io_base + HPRE_DATA_WUSER_CFG);
पूर्ण

अटल पूर्णांक hpre_cfg_by_dsm(काष्ठा hisi_qm *qm)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	जोड़ acpi_object *obj;
	guid_t guid;

	अगर (guid_parse("b06b81ab-0134-4a45-9b0c-483447b95fa7", &guid)) अणु
		dev_err(dev, "Hpre GUID failed\n");
		वापस -EINVAL;
	पूर्ण

	/* Switch over to MSI handling due to non-standard PCI implementation */
	obj = acpi_evaluate_dsm(ACPI_HANDLE(dev), &guid,
				0, HPRE_VIA_MSI_DSM, शून्य);
	अगर (!obj) अणु
		dev_err(dev, "ACPI handle failed!\n");
		वापस -EIO;
	पूर्ण

	ACPI_FREE(obj);

	वापस 0;
पूर्ण

अटल पूर्णांक hpre_set_cluster(काष्ठा hisi_qm *qm)
अणु
	u32 cluster_core_mask = HPRE_CLUSTER_CORE_MASK(qm);
	u8 clusters_num = HPRE_CLUSTERS_NUM(qm);
	काष्ठा device *dev = &qm->pdev->dev;
	अचिन्हित दीर्घ offset;
	u32 val = 0;
	पूर्णांक ret, i;

	क्रम (i = 0; i < clusters_num; i++) अणु
		offset = i * HPRE_CLSTR_ADDR_INTRVL;

		/* clusters initiating */
		ग_लिखोl(cluster_core_mask,
		       HPRE_ADDR(qm, offset + HPRE_CORE_ENB));
		ग_लिखोl(0x1, HPRE_ADDR(qm, offset + HPRE_CORE_INI_CFG));
		ret = पढ़ोl_relaxed_poll_समयout(HPRE_ADDR(qm, offset +
					HPRE_CORE_INI_STATUS), val,
					((val & cluster_core_mask) ==
					cluster_core_mask),
					HPRE_REG_RD_INTVRL_US,
					HPRE_REG_RD_TMOUT_US);
		अगर (ret) अणु
			dev_err(dev,
				"cluster %d int st status timeout!\n", i);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * For Kunpeng 920, we should disable FLR triggered by hardware (BME/PM/SRIOV).
 * Or it may stay in D3 state when we bind and unbind hpre quickly,
 * as it करोes FLR triggered by hardware.
 */
अटल व्योम disable_flr_of_bme(काष्ठा hisi_qm *qm)
अणु
	u32 val;

	val = पढ़ोl(HPRE_ADDR(qm, QM_PEH_AXUSER_CFG));
	val &= ~(HPRE_QM_BME_FLR | HPRE_QM_SRIOV_FLR);
	val |= HPRE_QM_PM_FLR;
	ग_लिखोl(val, HPRE_ADDR(qm, QM_PEH_AXUSER_CFG));
	ग_लिखोl(PEH_AXUSER_CFG_ENABLE, HPRE_ADDR(qm, QM_PEH_AXUSER_CFG_ENABLE));
पूर्ण

अटल पूर्णांक hpre_set_user_करोमुख्य_and_cache(काष्ठा hisi_qm *qm)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	u32 val;
	पूर्णांक ret;

	ग_लिखोl(HPRE_QM_USR_CFG_MASK, HPRE_ADDR(qm, QM_ARUSER_M_CFG_ENABLE));
	ग_लिखोl(HPRE_QM_USR_CFG_MASK, HPRE_ADDR(qm, QM_AWUSER_M_CFG_ENABLE));
	ग_लिखोl_relaxed(HPRE_QM_AXI_CFG_MASK, HPRE_ADDR(qm, QM_AXI_M_CFG));

	/* HPRE need more समय, we बंद this पूर्णांकerrupt */
	val = पढ़ोl_relaxed(HPRE_ADDR(qm, HPRE_QM_ABNML_INT_MASK));
	val |= BIT(HPRE_TIMEOUT_ABNML_BIT);
	ग_लिखोl_relaxed(val, HPRE_ADDR(qm, HPRE_QM_ABNML_INT_MASK));

	अगर (qm->ver >= QM_HW_V3)
		ग_लिखोl(HPRE_RSA_ENB | HPRE_ECC_ENB,
			HPRE_ADDR(qm, HPRE_TYPES_ENB));
	अन्यथा
		ग_लिखोl(HPRE_RSA_ENB, HPRE_ADDR(qm, HPRE_TYPES_ENB));

	ग_लिखोl(HPRE_QM_VFG_AX_MASK, HPRE_ADDR(qm, HPRE_VFG_AXCACHE));
	ग_लिखोl(0x0, HPRE_ADDR(qm, HPRE_BD_ENDIAN));
	ग_लिखोl(0x0, HPRE_ADDR(qm, HPRE_INT_MASK));
	ग_लिखोl(0x0, HPRE_ADDR(qm, HPRE_POISON_BYPASS));
	ग_लिखोl(0x0, HPRE_ADDR(qm, HPRE_COMM_CNT_CLR_CE));
	ग_लिखोl(0x0, HPRE_ADDR(qm, HPRE_ECC_BYPASS));

	ग_लिखोl(HPRE_BD_USR_MASK, HPRE_ADDR(qm, HPRE_BD_ARUSR_CFG));
	ग_लिखोl(HPRE_BD_USR_MASK, HPRE_ADDR(qm, HPRE_BD_AWUSR_CFG));
	ग_लिखोl(0x1, HPRE_ADDR(qm, HPRE_RDCHN_INI_CFG));
	ret = पढ़ोl_relaxed_poll_समयout(HPRE_ADDR(qm, HPRE_RDCHN_INI_ST), val,
					 val & BIT(0),
			HPRE_REG_RD_INTVRL_US,
			HPRE_REG_RD_TMOUT_US);
	अगर (ret) अणु
		dev_err(dev, "read rd channel timeout fail!\n");
		वापस -ETIMEDOUT;
	पूर्ण

	ret = hpre_set_cluster(qm);
	अगर (ret)
		वापस -ETIMEDOUT;

	/* This setting is only needed by Kunpeng 920. */
	अगर (qm->ver == QM_HW_V2) अणु
		ret = hpre_cfg_by_dsm(qm);
		अगर (ret)
			वापस ret;

		disable_flr_of_bme(qm);
	पूर्ण

	/* Config data buffer pasid needed by Kunpeng 920 */
	hpre_config_pasid(qm);

	वापस ret;
पूर्ण

अटल व्योम hpre_cnt_regs_clear(काष्ठा hisi_qm *qm)
अणु
	u8 clusters_num = HPRE_CLUSTERS_NUM(qm);
	अचिन्हित दीर्घ offset;
	पूर्णांक i;

	/* clear clusterX/cluster_ctrl */
	क्रम (i = 0; i < clusters_num; i++) अणु
		offset = HPRE_CLSTR_BASE + i * HPRE_CLSTR_ADDR_INTRVL;
		ग_लिखोl(0x0, qm->io_base + offset + HPRE_CLUSTER_INQURY);
	पूर्ण

	/* clear rdclr_en */
	ग_लिखोl(0x0, qm->io_base + HPRE_CTRL_CNT_CLR_CE);

	hisi_qm_debug_regs_clear(qm);
पूर्ण

अटल व्योम hpre_hw_error_disable(काष्ठा hisi_qm *qm)
अणु
	u32 val;

	/* disable hpre hw error पूर्णांकerrupts */
	ग_लिखोl(HPRE_CORE_INT_DISABLE, qm->io_base + HPRE_INT_MASK);

	/* disable HPRE block master OOO when m-bit error occur */
	val = पढ़ोl(qm->io_base + HPRE_AM_OOO_SHUTDOWN_ENB);
	val &= ~HPRE_AM_OOO_SHUTDOWN_ENABLE;
	ग_लिखोl(val, qm->io_base + HPRE_AM_OOO_SHUTDOWN_ENB);
पूर्ण

अटल व्योम hpre_hw_error_enable(काष्ठा hisi_qm *qm)
अणु
	u32 val;

	/* clear HPRE hw error source अगर having */
	ग_लिखोl(HPRE_CORE_INT_DISABLE, qm->io_base + HPRE_HAC_SOURCE_INT);

	/* enable hpre hw error पूर्णांकerrupts */
	ग_लिखोl(HPRE_CORE_INT_ENABLE, qm->io_base + HPRE_INT_MASK);
	ग_लिखोl(HPRE_HAC_RAS_CE_ENABLE, qm->io_base + HPRE_RAS_CE_ENB);
	ग_लिखोl(HPRE_HAC_RAS_NFE_ENABLE, qm->io_base + HPRE_RAS_NFE_ENB);
	ग_लिखोl(HPRE_HAC_RAS_FE_ENABLE, qm->io_base + HPRE_RAS_FE_ENB);

	/* enable HPRE block master OOO when m-bit error occur */
	val = पढ़ोl(qm->io_base + HPRE_AM_OOO_SHUTDOWN_ENB);
	val |= HPRE_AM_OOO_SHUTDOWN_ENABLE;
	ग_लिखोl(val, qm->io_base + HPRE_AM_OOO_SHUTDOWN_ENB);
पूर्ण

अटल अंतरभूत काष्ठा hisi_qm *hpre_file_to_qm(काष्ठा hpre_debugfs_file *file)
अणु
	काष्ठा hpre *hpre = container_of(file->debug, काष्ठा hpre, debug);

	वापस &hpre->qm;
पूर्ण

अटल u32 hpre_clear_enable_पढ़ो(काष्ठा hpre_debugfs_file *file)
अणु
	काष्ठा hisi_qm *qm = hpre_file_to_qm(file);

	वापस पढ़ोl(qm->io_base + HPRE_CTRL_CNT_CLR_CE) &
	       HPRE_CTRL_CNT_CLR_CE_BIT;
पूर्ण

अटल पूर्णांक hpre_clear_enable_ग_लिखो(काष्ठा hpre_debugfs_file *file, u32 val)
अणु
	काष्ठा hisi_qm *qm = hpre_file_to_qm(file);
	u32 पंचांगp;

	अगर (val != 1 && val != 0)
		वापस -EINVAL;

	पंचांगp = (पढ़ोl(qm->io_base + HPRE_CTRL_CNT_CLR_CE) &
	       ~HPRE_CTRL_CNT_CLR_CE_BIT) | val;
	ग_लिखोl(पंचांगp, qm->io_base + HPRE_CTRL_CNT_CLR_CE);

	वापस 0;
पूर्ण

अटल u32 hpre_cluster_inqry_पढ़ो(काष्ठा hpre_debugfs_file *file)
अणु
	काष्ठा hisi_qm *qm = hpre_file_to_qm(file);
	पूर्णांक cluster_index = file->index - HPRE_CLUSTER_CTRL;
	अचिन्हित दीर्घ offset = HPRE_CLSTR_BASE +
			       cluster_index * HPRE_CLSTR_ADDR_INTRVL;

	वापस पढ़ोl(qm->io_base + offset + HPRE_CLSTR_ADDR_INQRY_RSLT);
पूर्ण

अटल पूर्णांक hpre_cluster_inqry_ग_लिखो(काष्ठा hpre_debugfs_file *file, u32 val)
अणु
	काष्ठा hisi_qm *qm = hpre_file_to_qm(file);
	पूर्णांक cluster_index = file->index - HPRE_CLUSTER_CTRL;
	अचिन्हित दीर्घ offset = HPRE_CLSTR_BASE + cluster_index *
			       HPRE_CLSTR_ADDR_INTRVL;

	ग_लिखोl(val, qm->io_base + offset + HPRE_CLUSTER_INQURY);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार hpre_ctrl_debug_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
				    माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा hpre_debugfs_file *file = filp->निजी_data;
	अक्षर tbuf[HPRE_DBGFS_VAL_MAX_LEN];
	u32 val;
	पूर्णांक ret;

	spin_lock_irq(&file->lock);
	चयन (file->type) अणु
	हाल HPRE_CLEAR_ENABLE:
		val = hpre_clear_enable_पढ़ो(file);
		अवरोध;
	हाल HPRE_CLUSTER_CTRL:
		val = hpre_cluster_inqry_पढ़ो(file);
		अवरोध;
	शेष:
		spin_unlock_irq(&file->lock);
		वापस -EINVAL;
	पूर्ण
	spin_unlock_irq(&file->lock);
	ret = snम_लिखो(tbuf, HPRE_DBGFS_VAL_MAX_LEN, "%u\n", val);
	वापस simple_पढ़ो_from_buffer(buf, count, pos, tbuf, ret);
पूर्ण

अटल sमाप_प्रकार hpre_ctrl_debug_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
				     माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा hpre_debugfs_file *file = filp->निजी_data;
	अक्षर tbuf[HPRE_DBGFS_VAL_MAX_LEN];
	अचिन्हित दीर्घ val;
	पूर्णांक len, ret;

	अगर (*pos != 0)
		वापस 0;

	अगर (count >= HPRE_DBGFS_VAL_MAX_LEN)
		वापस -ENOSPC;

	len = simple_ग_लिखो_to_buffer(tbuf, HPRE_DBGFS_VAL_MAX_LEN - 1,
				     pos, buf, count);
	अगर (len < 0)
		वापस len;

	tbuf[len] = '\0';
	अगर (kम_से_अदीर्घ(tbuf, 0, &val))
		वापस -EFAULT;

	spin_lock_irq(&file->lock);
	चयन (file->type) अणु
	हाल HPRE_CLEAR_ENABLE:
		ret = hpre_clear_enable_ग_लिखो(file, val);
		अगर (ret)
			जाओ err_input;
		अवरोध;
	हाल HPRE_CLUSTER_CTRL:
		ret = hpre_cluster_inqry_ग_लिखो(file, val);
		अगर (ret)
			जाओ err_input;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err_input;
	पूर्ण
	spin_unlock_irq(&file->lock);

	वापस count;

err_input:
	spin_unlock_irq(&file->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations hpre_ctrl_debug_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = hpre_ctrl_debug_पढ़ो,
	.ग_लिखो = hpre_ctrl_debug_ग_लिखो,
पूर्ण;

अटल पूर्णांक hpre_debugfs_atomic64_get(व्योम *data, u64 *val)
अणु
	काष्ठा hpre_dfx *dfx_item = data;

	*val = atomic64_पढ़ो(&dfx_item->value);

	वापस 0;
पूर्ण

अटल पूर्णांक hpre_debugfs_atomic64_set(व्योम *data, u64 val)
अणु
	काष्ठा hpre_dfx *dfx_item = data;
	काष्ठा hpre_dfx *hpre_dfx = शून्य;

	अगर (dfx_item->type == HPRE_OVERTIME_THRHLD) अणु
		hpre_dfx = dfx_item - HPRE_OVERTIME_THRHLD;
		atomic64_set(&hpre_dfx[HPRE_OVER_THRHLD_CNT].value, 0);
	पूर्ण अन्यथा अगर (val) अणु
		वापस -EINVAL;
	पूर्ण

	atomic64_set(&dfx_item->value, val);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(hpre_atomic64_ops, hpre_debugfs_atomic64_get,
			 hpre_debugfs_atomic64_set, "%llu\n");

अटल पूर्णांक hpre_create_debugfs_file(काष्ठा hisi_qm *qm, काष्ठा dentry *dir,
				    क्रमागत hpre_ctrl_dbgfs_file type, पूर्णांक indx)
अणु
	काष्ठा hpre *hpre = container_of(qm, काष्ठा hpre, qm);
	काष्ठा hpre_debug *dbg = &hpre->debug;
	काष्ठा dentry *file_dir;

	अगर (dir)
		file_dir = dir;
	अन्यथा
		file_dir = qm->debug.debug_root;

	अगर (type >= HPRE_DEBUG_खाता_NUM)
		वापस -EINVAL;

	spin_lock_init(&dbg->files[indx].lock);
	dbg->files[indx].debug = dbg;
	dbg->files[indx].type = type;
	dbg->files[indx].index = indx;
	debugfs_create_file(hpre_debug_file_name[type], 0600, file_dir,
			    dbg->files + indx, &hpre_ctrl_debug_fops);

	वापस 0;
पूर्ण

अटल पूर्णांक hpre_pf_comm_regs_debugfs_init(काष्ठा hisi_qm *qm)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	काष्ठा debugfs_regset32 *regset;

	regset = devm_kzalloc(dev, माप(*regset), GFP_KERNEL);
	अगर (!regset)
		वापस -ENOMEM;

	regset->regs = hpre_com_dfx_regs;
	regset->nregs = ARRAY_SIZE(hpre_com_dfx_regs);
	regset->base = qm->io_base;

	debugfs_create_regset32("regs", 0444,  qm->debug.debug_root, regset);
	वापस 0;
पूर्ण

अटल पूर्णांक hpre_cluster_debugfs_init(काष्ठा hisi_qm *qm)
अणु
	u8 clusters_num = HPRE_CLUSTERS_NUM(qm);
	काष्ठा device *dev = &qm->pdev->dev;
	अक्षर buf[HPRE_DBGFS_VAL_MAX_LEN];
	काष्ठा debugfs_regset32 *regset;
	काष्ठा dentry *पंचांगp_d;
	पूर्णांक i, ret;

	क्रम (i = 0; i < clusters_num; i++) अणु
		ret = snम_लिखो(buf, HPRE_DBGFS_VAL_MAX_LEN, "cluster%d", i);
		अगर (ret < 0)
			वापस -EINVAL;
		पंचांगp_d = debugfs_create_dir(buf, qm->debug.debug_root);

		regset = devm_kzalloc(dev, माप(*regset), GFP_KERNEL);
		अगर (!regset)
			वापस -ENOMEM;

		regset->regs = hpre_cluster_dfx_regs;
		regset->nregs = ARRAY_SIZE(hpre_cluster_dfx_regs);
		regset->base = qm->io_base + hpre_cluster_offsets[i];

		debugfs_create_regset32("regs", 0444, पंचांगp_d, regset);
		ret = hpre_create_debugfs_file(qm, पंचांगp_d, HPRE_CLUSTER_CTRL,
					       i + HPRE_CLUSTER_CTRL);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hpre_ctrl_debug_init(काष्ठा hisi_qm *qm)
अणु
	पूर्णांक ret;

	ret = hpre_create_debugfs_file(qm, शून्य, HPRE_CLEAR_ENABLE,
				       HPRE_CLEAR_ENABLE);
	अगर (ret)
		वापस ret;

	ret = hpre_pf_comm_regs_debugfs_init(qm);
	अगर (ret)
		वापस ret;

	वापस hpre_cluster_debugfs_init(qm);
पूर्ण

अटल व्योम hpre_dfx_debug_init(काष्ठा hisi_qm *qm)
अणु
	काष्ठा hpre *hpre = container_of(qm, काष्ठा hpre, qm);
	काष्ठा hpre_dfx *dfx = hpre->debug.dfx;
	काष्ठा dentry *parent;
	पूर्णांक i;

	parent = debugfs_create_dir("hpre_dfx", qm->debug.debug_root);
	क्रम (i = 0; i < HPRE_DFX_खाता_NUM; i++) अणु
		dfx[i].type = i;
		debugfs_create_file(hpre_dfx_files[i], 0644, parent, &dfx[i],
				    &hpre_atomic64_ops);
	पूर्ण
पूर्ण

अटल पूर्णांक hpre_debugfs_init(काष्ठा hisi_qm *qm)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	पूर्णांक ret;

	qm->debug.debug_root = debugfs_create_dir(dev_name(dev),
						  hpre_debugfs_root);

	qm->debug.sqe_mask_offset = HPRE_SQE_MASK_OFFSET;
	qm->debug.sqe_mask_len = HPRE_SQE_MASK_LEN;
	hisi_qm_debug_init(qm);

	अगर (qm->pdev->device == HPRE_PCI_DEVICE_ID) अणु
		ret = hpre_ctrl_debug_init(qm);
		अगर (ret)
			जाओ failed_to_create;
	पूर्ण

	hpre_dfx_debug_init(qm);

	वापस 0;

failed_to_create:
	debugfs_हटाओ_recursive(qm->debug.debug_root);
	वापस ret;
पूर्ण

अटल व्योम hpre_debugfs_निकास(काष्ठा hisi_qm *qm)
अणु
	debugfs_हटाओ_recursive(qm->debug.debug_root);
पूर्ण

अटल पूर्णांक hpre_qm_init(काष्ठा hisi_qm *qm, काष्ठा pci_dev *pdev)
अणु
	अगर (pdev->revision == QM_HW_V1) अणु
		pci_warn(pdev, "HPRE version 1 is not supported!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pdev->revision >= QM_HW_V3)
		qm->algs = "rsa\ndh\necdh\nx25519\nx448\necdsa\nsm2";
	अन्यथा
		qm->algs = "rsa\ndh";
	qm->mode = uacce_mode;
	qm->pdev = pdev;
	qm->ver = pdev->revision;
	qm->sqe_size = HPRE_SQE_SIZE;
	qm->dev_name = hpre_name;

	qm->fun_type = (pdev->device == HPRE_PCI_DEVICE_ID) ?
			QM_HW_PF : QM_HW_VF;
	अगर (qm->fun_type == QM_HW_PF) अणु
		qm->qp_base = HPRE_PF_DEF_Q_BASE;
		qm->qp_num = pf_q_num;
		qm->debug.curr_qm_qp_num = pf_q_num;
		qm->qm_list = &hpre_devices;
	पूर्ण

	वापस hisi_qm_init(qm);
पूर्ण

अटल व्योम hpre_log_hw_error(काष्ठा hisi_qm *qm, u32 err_sts)
अणु
	स्थिर काष्ठा hpre_hw_error *err = hpre_hw_errors;
	काष्ठा device *dev = &qm->pdev->dev;

	जबतक (err->msg) अणु
		अगर (err->पूर्णांक_msk & err_sts)
			dev_warn(dev, "%s [error status=0x%x] found\n",
				 err->msg, err->पूर्णांक_msk);
		err++;
	पूर्ण
पूर्ण

अटल u32 hpre_get_hw_err_status(काष्ठा hisi_qm *qm)
अणु
	वापस पढ़ोl(qm->io_base + HPRE_HAC_INT_STATUS);
पूर्ण

अटल व्योम hpre_clear_hw_err_status(काष्ठा hisi_qm *qm, u32 err_sts)
अणु
	ग_लिखोl(err_sts, qm->io_base + HPRE_HAC_SOURCE_INT);
पूर्ण

अटल व्योम hpre_खोलो_axi_master_ooo(काष्ठा hisi_qm *qm)
अणु
	u32 value;

	value = पढ़ोl(qm->io_base + HPRE_AM_OOO_SHUTDOWN_ENB);
	ग_लिखोl(value & ~HPRE_AM_OOO_SHUTDOWN_ENABLE,
	       HPRE_ADDR(qm, HPRE_AM_OOO_SHUTDOWN_ENB));
	ग_लिखोl(value | HPRE_AM_OOO_SHUTDOWN_ENABLE,
	       HPRE_ADDR(qm, HPRE_AM_OOO_SHUTDOWN_ENB));
पूर्ण

अटल व्योम hpre_err_info_init(काष्ठा hisi_qm *qm)
अणु
	काष्ठा hisi_qm_err_info *err_info = &qm->err_info;

	err_info->ce = QM_BASE_CE;
	err_info->fe = 0;
	err_info->ecc_2bits_mask = HPRE_CORE_ECC_2BIT_ERR |
				   HPRE_OOO_ECC_2BIT_ERR;
	err_info->dev_ce_mask = HPRE_HAC_RAS_CE_ENABLE;
	err_info->msi_wr_port = HPRE_WR_MSI_PORT;
	err_info->acpi_rst = "HRST";
	err_info->nfe = QM_BASE_NFE | QM_ACC_DO_TASK_TIMEOUT;
पूर्ण

अटल स्थिर काष्ठा hisi_qm_err_ini hpre_err_ini = अणु
	.hw_init		= hpre_set_user_करोमुख्य_and_cache,
	.hw_err_enable		= hpre_hw_error_enable,
	.hw_err_disable		= hpre_hw_error_disable,
	.get_dev_hw_err_status	= hpre_get_hw_err_status,
	.clear_dev_hw_err_status = hpre_clear_hw_err_status,
	.log_dev_hw_err		= hpre_log_hw_error,
	.खोलो_axi_master_ooo	= hpre_खोलो_axi_master_ooo,
	.err_info_init		= hpre_err_info_init,
पूर्ण;

अटल पूर्णांक hpre_pf_probe_init(काष्ठा hpre *hpre)
अणु
	काष्ठा hisi_qm *qm = &hpre->qm;
	पूर्णांक ret;

	ret = hpre_set_user_करोमुख्य_and_cache(qm);
	अगर (ret)
		वापस ret;

	qm->err_ini = &hpre_err_ini;
	qm->err_ini->err_info_init(qm);
	hisi_qm_dev_err_init(qm);

	वापस 0;
पूर्ण

अटल पूर्णांक hpre_probe_init(काष्ठा hpre *hpre)
अणु
	काष्ठा hisi_qm *qm = &hpre->qm;
	पूर्णांक ret;

	अगर (qm->fun_type == QM_HW_PF) अणु
		ret = hpre_pf_probe_init(hpre);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hpre_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा hisi_qm *qm;
	काष्ठा hpre *hpre;
	पूर्णांक ret;

	hpre = devm_kzalloc(&pdev->dev, माप(*hpre), GFP_KERNEL);
	अगर (!hpre)
		वापस -ENOMEM;

	qm = &hpre->qm;
	ret = hpre_qm_init(qm, pdev);
	अगर (ret) अणु
		pci_err(pdev, "Failed to init HPRE QM (%d)!\n", ret);
		वापस ret;
	पूर्ण

	ret = hpre_probe_init(hpre);
	अगर (ret) अणु
		pci_err(pdev, "Failed to probe (%d)!\n", ret);
		जाओ err_with_qm_init;
	पूर्ण

	ret = hisi_qm_start(qm);
	अगर (ret)
		जाओ err_with_err_init;

	ret = hpre_debugfs_init(qm);
	अगर (ret)
		dev_warn(&pdev->dev, "init debugfs fail!\n");

	ret = hisi_qm_alg_रेजिस्टर(qm, &hpre_devices);
	अगर (ret < 0) अणु
		pci_err(pdev, "fail to register algs to crypto!\n");
		जाओ err_with_qm_start;
	पूर्ण

	अगर (qm->uacce) अणु
		ret = uacce_रेजिस्टर(qm->uacce);
		अगर (ret) अणु
			pci_err(pdev, "failed to register uacce (%d)!\n", ret);
			जाओ err_with_alg_रेजिस्टर;
		पूर्ण
	पूर्ण

	अगर (qm->fun_type == QM_HW_PF && vfs_num) अणु
		ret = hisi_qm_sriov_enable(pdev, vfs_num);
		अगर (ret < 0)
			जाओ err_with_alg_रेजिस्टर;
	पूर्ण

	वापस 0;

err_with_alg_रेजिस्टर:
	hisi_qm_alg_unरेजिस्टर(qm, &hpre_devices);

err_with_qm_start:
	hpre_debugfs_निकास(qm);
	hisi_qm_stop(qm, QM_NORMAL);

err_with_err_init:
	hisi_qm_dev_err_uninit(qm);

err_with_qm_init:
	hisi_qm_uninit(qm);

	वापस ret;
पूर्ण

अटल व्योम hpre_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hisi_qm *qm = pci_get_drvdata(pdev);
	पूर्णांक ret;

	hisi_qm_रुको_task_finish(qm, &hpre_devices);
	hisi_qm_alg_unरेजिस्टर(qm, &hpre_devices);
	अगर (qm->fun_type == QM_HW_PF && qm->vfs_num) अणु
		ret = hisi_qm_sriov_disable(pdev, true);
		अगर (ret) अणु
			pci_err(pdev, "Disable SRIOV fail!\n");
			वापस;
		पूर्ण
	पूर्ण

	hpre_debugfs_निकास(qm);
	hisi_qm_stop(qm, QM_NORMAL);

	अगर (qm->fun_type == QM_HW_PF) अणु
		hpre_cnt_regs_clear(qm);
		qm->debug.curr_qm_qp_num = 0;
		hisi_qm_dev_err_uninit(qm);
	पूर्ण

	hisi_qm_uninit(qm);
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers hpre_err_handler = अणु
	.error_detected		= hisi_qm_dev_err_detected,
	.slot_reset		= hisi_qm_dev_slot_reset,
	.reset_prepare		= hisi_qm_reset_prepare,
	.reset_करोne		= hisi_qm_reset_करोne,
पूर्ण;

अटल काष्ठा pci_driver hpre_pci_driver = अणु
	.name			= hpre_name,
	.id_table		= hpre_dev_ids,
	.probe			= hpre_probe,
	.हटाओ			= hpre_हटाओ,
	.sriov_configure	= IS_ENABLED(CONFIG_PCI_IOV) ?
				  hisi_qm_sriov_configure : शून्य,
	.err_handler		= &hpre_err_handler,
	.shutकरोwn		= hisi_qm_dev_shutकरोwn,
पूर्ण;

अटल व्योम hpre_रेजिस्टर_debugfs(व्योम)
अणु
	अगर (!debugfs_initialized())
		वापस;

	hpre_debugfs_root = debugfs_create_dir(hpre_name, शून्य);
पूर्ण

अटल व्योम hpre_unरेजिस्टर_debugfs(व्योम)
अणु
	debugfs_हटाओ_recursive(hpre_debugfs_root);
पूर्ण

अटल पूर्णांक __init hpre_init(व्योम)
अणु
	पूर्णांक ret;

	hisi_qm_init_list(&hpre_devices);
	hpre_रेजिस्टर_debugfs();

	ret = pci_रेजिस्टर_driver(&hpre_pci_driver);
	अगर (ret) अणु
		hpre_unरेजिस्टर_debugfs();
		pr_err("hpre: can't register hisi hpre driver.\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास hpre_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&hpre_pci_driver);
	hpre_unरेजिस्टर_debugfs();
पूर्ण

module_init(hpre_init);
module_निकास(hpre_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Zaibo Xu <xuzaibo@huawei.com>");
MODULE_AUTHOR("Meng Yu <yumeng18@huawei.com>");
MODULE_DESCRIPTION("Driver for HiSilicon HPRE accelerator");
