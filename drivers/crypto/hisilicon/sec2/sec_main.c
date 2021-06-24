<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 HiSilicon Limited. */

#समावेश <linux/acpi.h>
#समावेश <linux/aer.h>
#समावेश <linux/bitops.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/iommu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/topology.h>
#समावेश <linux/uacce.h>

#समावेश "sec.h"

#घोषणा SEC_VF_NUM			63
#घोषणा SEC_QUEUE_NUM_V1		4096
#घोषणा SEC_PF_PCI_DEVICE_ID		0xa255
#घोषणा SEC_VF_PCI_DEVICE_ID		0xa256

#घोषणा SEC_BD_ERR_CHK_EN0		0xEFFFFFFF
#घोषणा SEC_BD_ERR_CHK_EN1		0x7ffff7fd
#घोषणा SEC_BD_ERR_CHK_EN3		0xffffbfff

#घोषणा SEC_SQE_SIZE			128
#घोषणा SEC_SQ_SIZE			(SEC_SQE_SIZE * QM_Q_DEPTH)
#घोषणा SEC_PF_DEF_Q_NUM		256
#घोषणा SEC_PF_DEF_Q_BASE		0
#घोषणा SEC_CTX_Q_NUM_DEF		2
#घोषणा SEC_CTX_Q_NUM_MAX		32

#घोषणा SEC_CTRL_CNT_CLR_CE		0x301120
#घोषणा SEC_CTRL_CNT_CLR_CE_BIT	BIT(0)
#घोषणा SEC_CORE_INT_SOURCE		0x301010
#घोषणा SEC_CORE_INT_MASK		0x301000
#घोषणा SEC_CORE_INT_STATUS		0x301008
#घोषणा SEC_CORE_SRAM_ECC_ERR_INFO	0x301C14
#घोषणा SEC_ECC_NUM			16
#घोषणा SEC_ECC_MASH			0xFF
#घोषणा SEC_CORE_INT_DISABLE		0x0
#घोषणा SEC_CORE_INT_ENABLE		0x7c1ff
#घोषणा SEC_CORE_INT_CLEAR		0x7c1ff
#घोषणा SEC_SAA_ENABLE			0x17f

#घोषणा SEC_RAS_CE_REG			0x301050
#घोषणा SEC_RAS_FE_REG			0x301054
#घोषणा SEC_RAS_NFE_REG			0x301058
#घोषणा SEC_RAS_CE_ENB_MSK		0x88
#घोषणा SEC_RAS_FE_ENB_MSK		0x0
#घोषणा SEC_RAS_NFE_ENB_MSK		0x7c177
#घोषणा SEC_RAS_DISABLE		0x0
#घोषणा SEC_MEM_START_INIT_REG	0x301100
#घोषणा SEC_MEM_INIT_DONE_REG		0x301104

#घोषणा SEC_CONTROL_REG		0x301200
#घोषणा SEC_TRNG_EN_SHIFT		8
#घोषणा SEC_CLK_GATE_ENABLE		BIT(3)
#घोषणा SEC_CLK_GATE_DISABLE		(~BIT(3))
#घोषणा SEC_AXI_SHUTDOWN_ENABLE	BIT(12)
#घोषणा SEC_AXI_SHUTDOWN_DISABLE	0xFFFFEFFF

#घोषणा SEC_INTERFACE_USER_CTRL0_REG	0x301220
#घोषणा SEC_INTERFACE_USER_CTRL1_REG	0x301224
#घोषणा SEC_SAA_EN_REG			0x301270
#घोषणा SEC_BD_ERR_CHK_EN_REG0		0x301380
#घोषणा SEC_BD_ERR_CHK_EN_REG1		0x301384
#घोषणा SEC_BD_ERR_CHK_EN_REG3		0x30138c

#घोषणा SEC_USER0_SMMU_NORMAL		(BIT(23) | BIT(15))
#घोषणा SEC_USER1_SMMU_NORMAL		(BIT(31) | BIT(23) | BIT(15) | BIT(7))
#घोषणा SEC_USER1_ENABLE_CONTEXT_SSV	BIT(24)
#घोषणा SEC_USER1_ENABLE_DATA_SSV	BIT(16)
#घोषणा SEC_USER1_WB_CONTEXT_SSV	BIT(8)
#घोषणा SEC_USER1_WB_DATA_SSV		BIT(0)
#घोषणा SEC_USER1_SVA_SET		(SEC_USER1_ENABLE_CONTEXT_SSV | \
					SEC_USER1_ENABLE_DATA_SSV | \
					SEC_USER1_WB_CONTEXT_SSV |  \
					SEC_USER1_WB_DATA_SSV)
#घोषणा SEC_USER1_SMMU_SVA		(SEC_USER1_SMMU_NORMAL | SEC_USER1_SVA_SET)
#घोषणा SEC_USER1_SMMU_MASK		(~SEC_USER1_SVA_SET)
#घोषणा SEC_CORE_INT_STATUS_M_ECC	BIT(2)

#घोषणा SEC_DELAY_10_US			10
#घोषणा SEC_POLL_TIMEOUT_US		1000
#घोषणा SEC_DBGFS_VAL_MAX_LEN		20
#घोषणा SEC_SINGLE_PORT_MAX_TRANS	0x2060

#घोषणा SEC_SQE_MASK_OFFSET		64
#घोषणा SEC_SQE_MASK_LEN		48

काष्ठा sec_hw_error अणु
	u32 पूर्णांक_msk;
	स्थिर अक्षर *msg;
पूर्ण;

काष्ठा sec_dfx_item अणु
	स्थिर अक्षर *name;
	u32 offset;
पूर्ण;

अटल स्थिर अक्षर sec_name[] = "hisi_sec2";
अटल काष्ठा dentry *sec_debugfs_root;

अटल काष्ठा hisi_qm_list sec_devices = अणु
	.रेजिस्टर_to_crypto	= sec_रेजिस्टर_to_crypto,
	.unरेजिस्टर_from_crypto	= sec_unरेजिस्टर_from_crypto,
पूर्ण;

अटल स्थिर काष्ठा sec_hw_error sec_hw_errors[] = अणु
	अणु
		.पूर्णांक_msk = BIT(0),
		.msg = "sec_axi_rresp_err_rint"
	पूर्ण,
	अणु
		.पूर्णांक_msk = BIT(1),
		.msg = "sec_axi_bresp_err_rint"
	पूर्ण,
	अणु
		.पूर्णांक_msk = BIT(2),
		.msg = "sec_ecc_2bit_err_rint"
	पूर्ण,
	अणु
		.पूर्णांक_msk = BIT(3),
		.msg = "sec_ecc_1bit_err_rint"
	पूर्ण,
	अणु
		.पूर्णांक_msk = BIT(4),
		.msg = "sec_req_trng_timeout_rint"
	पूर्ण,
	अणु
		.पूर्णांक_msk = BIT(5),
		.msg = "sec_fsm_hbeat_rint"
	पूर्ण,
	अणु
		.पूर्णांक_msk = BIT(6),
		.msg = "sec_channel_req_rng_timeout_rint"
	पूर्ण,
	अणु
		.पूर्णांक_msk = BIT(7),
		.msg = "sec_bd_err_rint"
	पूर्ण,
	अणु
		.पूर्णांक_msk = BIT(8),
		.msg = "sec_chain_buff_err_rint"
	पूर्ण,
	अणु
		.पूर्णांक_msk = BIT(14),
		.msg = "sec_no_secure_access"
	पूर्ण,
	अणु
		.पूर्णांक_msk = BIT(15),
		.msg = "sec_wrapping_key_auth_err"
	पूर्ण,
	अणु
		.पूर्णांक_msk = BIT(16),
		.msg = "sec_km_key_crc_fail"
	पूर्ण,
	अणु
		.पूर्णांक_msk = BIT(17),
		.msg = "sec_axi_poison_err"
	पूर्ण,
	अणु
		.पूर्णांक_msk = BIT(18),
		.msg = "sec_sva_err"
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर sec_dbg_file_name[] = अणु
	[SEC_CLEAR_ENABLE] = "clear_enable",
पूर्ण;

अटल काष्ठा sec_dfx_item sec_dfx_labels[] = अणु
	अणु"send_cnt", दुरत्व(काष्ठा sec_dfx, send_cnt)पूर्ण,
	अणु"recv_cnt", दुरत्व(काष्ठा sec_dfx, recv_cnt)पूर्ण,
	अणु"send_busy_cnt", दुरत्व(काष्ठा sec_dfx, send_busy_cnt)पूर्ण,
	अणु"recv_busy_cnt", दुरत्व(काष्ठा sec_dfx, recv_busy_cnt)पूर्ण,
	अणु"err_bd_cnt", दुरत्व(काष्ठा sec_dfx, err_bd_cnt)पूर्ण,
	अणु"invalid_req_cnt", दुरत्व(काष्ठा sec_dfx, invalid_req_cnt)पूर्ण,
	अणु"done_flag_cnt", दुरत्व(काष्ठा sec_dfx, करोne_flag_cnt)पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा debugfs_reg32 sec_dfx_regs[] = अणु
	अणु"SEC_PF_ABNORMAL_INT_SOURCE    ",  0x301010पूर्ण,
	अणु"SEC_SAA_EN                    ",  0x301270पूर्ण,
	अणु"SEC_BD_LATENCY_MIN            ",  0x301600पूर्ण,
	अणु"SEC_BD_LATENCY_MAX            ",  0x301608पूर्ण,
	अणु"SEC_BD_LATENCY_AVG            ",  0x30160Cपूर्ण,
	अणु"SEC_BD_NUM_IN_SAA0            ",  0x301670पूर्ण,
	अणु"SEC_BD_NUM_IN_SAA1            ",  0x301674पूर्ण,
	अणु"SEC_BD_NUM_IN_SEC             ",  0x301680पूर्ण,
	अणु"SEC_ECC_1BIT_CNT              ",  0x301C00पूर्ण,
	अणु"SEC_ECC_1BIT_INFO             ",  0x301C04पूर्ण,
	अणु"SEC_ECC_2BIT_CNT              ",  0x301C10पूर्ण,
	अणु"SEC_ECC_2BIT_INFO             ",  0x301C14पूर्ण,
	अणु"SEC_BD_SAA0                   ",  0x301C20पूर्ण,
	अणु"SEC_BD_SAA1                   ",  0x301C24पूर्ण,
	अणु"SEC_BD_SAA2                   ",  0x301C28पूर्ण,
	अणु"SEC_BD_SAA3                   ",  0x301C2Cपूर्ण,
	अणु"SEC_BD_SAA4                   ",  0x301C30पूर्ण,
	अणु"SEC_BD_SAA5                   ",  0x301C34पूर्ण,
	अणु"SEC_BD_SAA6                   ",  0x301C38पूर्ण,
	अणु"SEC_BD_SAA7                   ",  0x301C3Cपूर्ण,
	अणु"SEC_BD_SAA8                   ",  0x301C40पूर्ण,
पूर्ण;

अटल पूर्णांक sec_pf_q_num_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	वापस q_num_set(val, kp, SEC_PF_PCI_DEVICE_ID);
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops sec_pf_q_num_ops = अणु
	.set = sec_pf_q_num_set,
	.get = param_get_पूर्णांक,
पूर्ण;

अटल u32 pf_q_num = SEC_PF_DEF_Q_NUM;
module_param_cb(pf_q_num, &sec_pf_q_num_ops, &pf_q_num, 0444);
MODULE_PARM_DESC(pf_q_num, "Number of queues in PF(v1 2-4096, v2 2-1024)");

अटल पूर्णांक sec_ctx_q_num_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	u32 ctx_q_num;
	पूर्णांक ret;

	अगर (!val)
		वापस -EINVAL;

	ret = kstrtou32(val, 10, &ctx_q_num);
	अगर (ret)
		वापस -EINVAL;

	अगर (!ctx_q_num || ctx_q_num > SEC_CTX_Q_NUM_MAX || ctx_q_num & 0x1) अणु
		pr_err("ctx queue num[%u] is invalid!\n", ctx_q_num);
		वापस -EINVAL;
	पूर्ण

	वापस param_set_पूर्णांक(val, kp);
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops sec_ctx_q_num_ops = अणु
	.set = sec_ctx_q_num_set,
	.get = param_get_पूर्णांक,
पूर्ण;
अटल u32 ctx_q_num = SEC_CTX_Q_NUM_DEF;
module_param_cb(ctx_q_num, &sec_ctx_q_num_ops, &ctx_q_num, 0444);
MODULE_PARM_DESC(ctx_q_num, "Queue num in ctx (2 default, 2, 4, ..., 32)");

अटल स्थिर काष्ठा kernel_param_ops vfs_num_ops = अणु
	.set = vfs_num_set,
	.get = param_get_पूर्णांक,
पूर्ण;

अटल u32 vfs_num;
module_param_cb(vfs_num, &vfs_num_ops, &vfs_num, 0444);
MODULE_PARM_DESC(vfs_num, "Number of VFs to enable(1-63), 0(default)");

व्योम sec_destroy_qps(काष्ठा hisi_qp **qps, पूर्णांक qp_num)
अणु
	hisi_qm_मुक्त_qps(qps, qp_num);
	kमुक्त(qps);
पूर्ण

काष्ठा hisi_qp **sec_create_qps(व्योम)
अणु
	पूर्णांक node = cpu_to_node(smp_processor_id());
	u32 ctx_num = ctx_q_num;
	काष्ठा hisi_qp **qps;
	पूर्णांक ret;

	qps = kसुस्मृति(ctx_num, माप(काष्ठा hisi_qp *), GFP_KERNEL);
	अगर (!qps)
		वापस शून्य;

	ret = hisi_qm_alloc_qps_node(&sec_devices, ctx_num, 0, node, qps);
	अगर (!ret)
		वापस qps;

	kमुक्त(qps);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops sec_uacce_mode_ops = अणु
	.set = uacce_mode_set,
	.get = param_get_पूर्णांक,
पूर्ण;

/*
 * uacce_mode = 0 means sec only रेजिस्टर to crypto,
 * uacce_mode = 1 means sec both रेजिस्टर to crypto and uacce.
 */
अटल u32 uacce_mode = UACCE_MODE_NOUACCE;
module_param_cb(uacce_mode, &sec_uacce_mode_ops, &uacce_mode, 0444);
MODULE_PARM_DESC(uacce_mode, UACCE_MODE_DESC);

अटल स्थिर काष्ठा pci_device_id sec_dev_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_HUAWEI, SEC_PF_PCI_DEVICE_ID) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_HUAWEI, SEC_VF_PCI_DEVICE_ID) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, sec_dev_ids);

अटल u8 sec_get_endian(काष्ठा hisi_qm *qm)
अणु
	u32 reg;

	/*
	 * As क्रम VF, it is a wrong way to get endian setting by
	 * पढ़ोing a रेजिस्टर of the engine
	 */
	अगर (qm->pdev->is_virtfn) अणु
		dev_err_ratelimited(&qm->pdev->dev,
				    "cannot access a register in VF!\n");
		वापस SEC_LE;
	पूर्ण
	reg = पढ़ोl_relaxed(qm->io_base + SEC_CONTROL_REG);
	/* BD little endian mode */
	अगर (!(reg & BIT(0)))
		वापस SEC_LE;

	/* BD 32-bits big endian mode */
	अन्यथा अगर (!(reg & BIT(1)))
		वापस SEC_32BE;

	/* BD 64-bits big endian mode */
	अन्यथा
		वापस SEC_64BE;
पूर्ण

अटल पूर्णांक sec_engine_init(काष्ठा hisi_qm *qm)
अणु
	पूर्णांक ret;
	u32 reg;

	/* disable घड़ी gate control */
	reg = पढ़ोl_relaxed(qm->io_base + SEC_CONTROL_REG);
	reg &= SEC_CLK_GATE_DISABLE;
	ग_लिखोl_relaxed(reg, qm->io_base + SEC_CONTROL_REG);

	ग_लिखोl_relaxed(0x1, qm->io_base + SEC_MEM_START_INIT_REG);

	ret = पढ़ोl_relaxed_poll_समयout(qm->io_base + SEC_MEM_INIT_DONE_REG,
					 reg, reg & 0x1, SEC_DELAY_10_US,
					 SEC_POLL_TIMEOUT_US);
	अगर (ret) अणु
		pci_err(qm->pdev, "fail to init sec mem\n");
		वापस ret;
	पूर्ण

	reg = पढ़ोl_relaxed(qm->io_base + SEC_CONTROL_REG);
	reg |= (0x1 << SEC_TRNG_EN_SHIFT);
	ग_लिखोl_relaxed(reg, qm->io_base + SEC_CONTROL_REG);

	reg = पढ़ोl_relaxed(qm->io_base + SEC_INTERFACE_USER_CTRL0_REG);
	reg |= SEC_USER0_SMMU_NORMAL;
	ग_लिखोl_relaxed(reg, qm->io_base + SEC_INTERFACE_USER_CTRL0_REG);

	reg = पढ़ोl_relaxed(qm->io_base + SEC_INTERFACE_USER_CTRL1_REG);
	reg &= SEC_USER1_SMMU_MASK;
	अगर (qm->use_sva && qm->ver == QM_HW_V2)
		reg |= SEC_USER1_SMMU_SVA;
	अन्यथा
		reg |= SEC_USER1_SMMU_NORMAL;
	ग_लिखोl_relaxed(reg, qm->io_base + SEC_INTERFACE_USER_CTRL1_REG);

	ग_लिखोl(SEC_SINGLE_PORT_MAX_TRANS,
	       qm->io_base + AM_CFG_SINGLE_PORT_MAX_TRANS);

	ग_लिखोl(SEC_SAA_ENABLE, qm->io_base + SEC_SAA_EN_REG);

	/* Enable sm4 extra mode, as ctr/ecb */
	ग_लिखोl_relaxed(SEC_BD_ERR_CHK_EN0,
		       qm->io_base + SEC_BD_ERR_CHK_EN_REG0);
	/* Enable sm4 xts mode multiple iv */
	ग_लिखोl_relaxed(SEC_BD_ERR_CHK_EN1,
		       qm->io_base + SEC_BD_ERR_CHK_EN_REG1);
	ग_लिखोl_relaxed(SEC_BD_ERR_CHK_EN3,
		       qm->io_base + SEC_BD_ERR_CHK_EN_REG3);

	/* config endian */
	reg = पढ़ोl_relaxed(qm->io_base + SEC_CONTROL_REG);
	reg |= sec_get_endian(qm);
	ग_लिखोl_relaxed(reg, qm->io_base + SEC_CONTROL_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक sec_set_user_करोमुख्य_and_cache(काष्ठा hisi_qm *qm)
अणु
	/* qm user करोमुख्य */
	ग_लिखोl(AXUSER_BASE, qm->io_base + QM_ARUSER_M_CFG_1);
	ग_लिखोl(ARUSER_M_CFG_ENABLE, qm->io_base + QM_ARUSER_M_CFG_ENABLE);
	ग_लिखोl(AXUSER_BASE, qm->io_base + QM_AWUSER_M_CFG_1);
	ग_लिखोl(AWUSER_M_CFG_ENABLE, qm->io_base + QM_AWUSER_M_CFG_ENABLE);
	ग_लिखोl(WUSER_M_CFG_ENABLE, qm->io_base + QM_WUSER_M_CFG_ENABLE);

	/* qm cache */
	ग_लिखोl(AXI_M_CFG, qm->io_base + QM_AXI_M_CFG);
	ग_लिखोl(AXI_M_CFG_ENABLE, qm->io_base + QM_AXI_M_CFG_ENABLE);

	/* disable FLR triggered by BME(bus master enable) */
	ग_लिखोl(PEH_AXUSER_CFG, qm->io_base + QM_PEH_AXUSER_CFG);
	ग_लिखोl(PEH_AXUSER_CFG_ENABLE, qm->io_base + QM_PEH_AXUSER_CFG_ENABLE);

	/* enable sqc,cqc ग_लिखोback */
	ग_लिखोl(SQC_CACHE_ENABLE | CQC_CACHE_ENABLE | SQC_CACHE_WB_ENABLE |
	       CQC_CACHE_WB_ENABLE | FIELD_PREP(SQC_CACHE_WB_THRD, 1) |
	       FIELD_PREP(CQC_CACHE_WB_THRD, 1), qm->io_base + QM_CACHE_CTL);

	वापस sec_engine_init(qm);
पूर्ण

/* sec_debug_regs_clear() - clear the sec debug regs */
अटल व्योम sec_debug_regs_clear(काष्ठा hisi_qm *qm)
अणु
	पूर्णांक i;

	/* clear sec dfx regs */
	ग_लिखोl(0x1, qm->io_base + SEC_CTRL_CNT_CLR_CE);
	क्रम (i = 0; i < ARRAY_SIZE(sec_dfx_regs); i++)
		पढ़ोl(qm->io_base + sec_dfx_regs[i].offset);

	/* clear rdclr_en */
	ग_लिखोl(0x0, qm->io_base + SEC_CTRL_CNT_CLR_CE);

	hisi_qm_debug_regs_clear(qm);
पूर्ण

अटल व्योम sec_hw_error_enable(काष्ठा hisi_qm *qm)
अणु
	u32 val;

	अगर (qm->ver == QM_HW_V1) अणु
		ग_लिखोl(SEC_CORE_INT_DISABLE, qm->io_base + SEC_CORE_INT_MASK);
		pci_info(qm->pdev, "V1 not support hw error handle\n");
		वापस;
	पूर्ण

	val = पढ़ोl(qm->io_base + SEC_CONTROL_REG);

	/* clear SEC hw error source अगर having */
	ग_लिखोl(SEC_CORE_INT_CLEAR, qm->io_base + SEC_CORE_INT_SOURCE);

	/* enable SEC hw error पूर्णांकerrupts */
	ग_लिखोl(SEC_CORE_INT_ENABLE, qm->io_base + SEC_CORE_INT_MASK);

	/* enable RAS पूर्णांक */
	ग_लिखोl(SEC_RAS_CE_ENB_MSK, qm->io_base + SEC_RAS_CE_REG);
	ग_लिखोl(SEC_RAS_FE_ENB_MSK, qm->io_base + SEC_RAS_FE_REG);
	ग_लिखोl(SEC_RAS_NFE_ENB_MSK, qm->io_base + SEC_RAS_NFE_REG);

	/* enable SEC block master OOO when m-bit error occur */
	val = val | SEC_AXI_SHUTDOWN_ENABLE;

	ग_लिखोl(val, qm->io_base + SEC_CONTROL_REG);
पूर्ण

अटल व्योम sec_hw_error_disable(काष्ठा hisi_qm *qm)
अणु
	u32 val;

	val = पढ़ोl(qm->io_base + SEC_CONTROL_REG);

	/* disable RAS पूर्णांक */
	ग_लिखोl(SEC_RAS_DISABLE, qm->io_base + SEC_RAS_CE_REG);
	ग_लिखोl(SEC_RAS_DISABLE, qm->io_base + SEC_RAS_FE_REG);
	ग_लिखोl(SEC_RAS_DISABLE, qm->io_base + SEC_RAS_NFE_REG);

	/* disable SEC hw error पूर्णांकerrupts */
	ग_लिखोl(SEC_CORE_INT_DISABLE, qm->io_base + SEC_CORE_INT_MASK);

	/* disable SEC block master OOO when m-bit error occur */
	val = val & SEC_AXI_SHUTDOWN_DISABLE;

	ग_लिखोl(val, qm->io_base + SEC_CONTROL_REG);
पूर्ण

अटल u32 sec_clear_enable_पढ़ो(काष्ठा sec_debug_file *file)
अणु
	काष्ठा hisi_qm *qm = file->qm;

	वापस पढ़ोl(qm->io_base + SEC_CTRL_CNT_CLR_CE) &
			SEC_CTRL_CNT_CLR_CE_BIT;
पूर्ण

अटल पूर्णांक sec_clear_enable_ग_लिखो(काष्ठा sec_debug_file *file, u32 val)
अणु
	काष्ठा hisi_qm *qm = file->qm;
	u32 पंचांगp;

	अगर (val != 1 && val)
		वापस -EINVAL;

	पंचांगp = (पढ़ोl(qm->io_base + SEC_CTRL_CNT_CLR_CE) &
	       ~SEC_CTRL_CNT_CLR_CE_BIT) | val;
	ग_लिखोl(पंचांगp, qm->io_base + SEC_CTRL_CNT_CLR_CE);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार sec_debug_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
			       माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा sec_debug_file *file = filp->निजी_data;
	अक्षर tbuf[SEC_DBGFS_VAL_MAX_LEN];
	u32 val;
	पूर्णांक ret;

	spin_lock_irq(&file->lock);

	चयन (file->index) अणु
	हाल SEC_CLEAR_ENABLE:
		val = sec_clear_enable_पढ़ो(file);
		अवरोध;
	शेष:
		spin_unlock_irq(&file->lock);
		वापस -EINVAL;
	पूर्ण

	spin_unlock_irq(&file->lock);
	ret = snम_लिखो(tbuf, SEC_DBGFS_VAL_MAX_LEN, "%u\n", val);

	वापस simple_पढ़ो_from_buffer(buf, count, pos, tbuf, ret);
पूर्ण

अटल sमाप_प्रकार sec_debug_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			       माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा sec_debug_file *file = filp->निजी_data;
	अक्षर tbuf[SEC_DBGFS_VAL_MAX_LEN];
	अचिन्हित दीर्घ val;
	पूर्णांक len, ret;

	अगर (*pos != 0)
		वापस 0;

	अगर (count >= SEC_DBGFS_VAL_MAX_LEN)
		वापस -ENOSPC;

	len = simple_ग_लिखो_to_buffer(tbuf, SEC_DBGFS_VAL_MAX_LEN - 1,
				     pos, buf, count);
	अगर (len < 0)
		वापस len;

	tbuf[len] = '\0';
	अगर (kम_से_अदीर्घ(tbuf, 0, &val))
		वापस -EFAULT;

	spin_lock_irq(&file->lock);

	चयन (file->index) अणु
	हाल SEC_CLEAR_ENABLE:
		ret = sec_clear_enable_ग_लिखो(file, val);
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

अटल स्थिर काष्ठा file_operations sec_dbg_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = sec_debug_पढ़ो,
	.ग_लिखो = sec_debug_ग_लिखो,
पूर्ण;

अटल पूर्णांक sec_debugfs_atomic64_get(व्योम *data, u64 *val)
अणु
	*val = atomic64_पढ़ो((atomic64_t *)data);

	वापस 0;
पूर्ण

अटल पूर्णांक sec_debugfs_atomic64_set(व्योम *data, u64 val)
अणु
	अगर (val)
		वापस -EINVAL;

	atomic64_set((atomic64_t *)data, 0);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(sec_atomic64_ops, sec_debugfs_atomic64_get,
			 sec_debugfs_atomic64_set, "%lld\n");

अटल पूर्णांक sec_core_debug_init(काष्ठा hisi_qm *qm)
अणु
	काष्ठा sec_dev *sec = container_of(qm, काष्ठा sec_dev, qm);
	काष्ठा device *dev = &qm->pdev->dev;
	काष्ठा sec_dfx *dfx = &sec->debug.dfx;
	काष्ठा debugfs_regset32 *regset;
	काष्ठा dentry *पंचांगp_d;
	पूर्णांक i;

	पंचांगp_d = debugfs_create_dir("sec_dfx", qm->debug.debug_root);

	regset = devm_kzalloc(dev, माप(*regset), GFP_KERNEL);
	अगर (!regset)
		वापस -ENOMEM;

	regset->regs = sec_dfx_regs;
	regset->nregs = ARRAY_SIZE(sec_dfx_regs);
	regset->base = qm->io_base;

	अगर (qm->pdev->device == SEC_PF_PCI_DEVICE_ID)
		debugfs_create_regset32("regs", 0444, पंचांगp_d, regset);

	क्रम (i = 0; i < ARRAY_SIZE(sec_dfx_labels); i++) अणु
		atomic64_t *data = (atomic64_t *)((uपूर्णांकptr_t)dfx +
					sec_dfx_labels[i].offset);
		debugfs_create_file(sec_dfx_labels[i].name, 0644,
				   पंचांगp_d, data, &sec_atomic64_ops);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sec_debug_init(काष्ठा hisi_qm *qm)
अणु
	काष्ठा sec_dev *sec = container_of(qm, काष्ठा sec_dev, qm);
	पूर्णांक i;

	अगर (qm->pdev->device == SEC_PF_PCI_DEVICE_ID) अणु
		क्रम (i = SEC_CLEAR_ENABLE; i < SEC_DEBUG_खाता_NUM; i++) अणु
			spin_lock_init(&sec->debug.files[i].lock);
			sec->debug.files[i].index = i;
			sec->debug.files[i].qm = qm;

			debugfs_create_file(sec_dbg_file_name[i], 0600,
						  qm->debug.debug_root,
						  sec->debug.files + i,
						  &sec_dbg_fops);
		पूर्ण
	पूर्ण

	वापस sec_core_debug_init(qm);
पूर्ण

अटल पूर्णांक sec_debugfs_init(काष्ठा hisi_qm *qm)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	पूर्णांक ret;

	qm->debug.debug_root = debugfs_create_dir(dev_name(dev),
						  sec_debugfs_root);
	qm->debug.sqe_mask_offset = SEC_SQE_MASK_OFFSET;
	qm->debug.sqe_mask_len = SEC_SQE_MASK_LEN;
	hisi_qm_debug_init(qm);

	ret = sec_debug_init(qm);
	अगर (ret)
		जाओ failed_to_create;

	वापस 0;

failed_to_create:
	debugfs_हटाओ_recursive(sec_debugfs_root);
	वापस ret;
पूर्ण

अटल व्योम sec_debugfs_निकास(काष्ठा hisi_qm *qm)
अणु
	debugfs_हटाओ_recursive(qm->debug.debug_root);
पूर्ण

अटल व्योम sec_log_hw_error(काष्ठा hisi_qm *qm, u32 err_sts)
अणु
	स्थिर काष्ठा sec_hw_error *errs = sec_hw_errors;
	काष्ठा device *dev = &qm->pdev->dev;
	u32 err_val;

	जबतक (errs->msg) अणु
		अगर (errs->पूर्णांक_msk & err_sts) अणु
			dev_err(dev, "%s [error status=0x%x] found\n",
					errs->msg, errs->पूर्णांक_msk);

			अगर (SEC_CORE_INT_STATUS_M_ECC & errs->पूर्णांक_msk) अणु
				err_val = पढ़ोl(qm->io_base +
						SEC_CORE_SRAM_ECC_ERR_INFO);
				dev_err(dev, "multi ecc sram num=0x%x\n",
						((err_val) >> SEC_ECC_NUM) &
						SEC_ECC_MASH);
			पूर्ण
		पूर्ण
		errs++;
	पूर्ण
पूर्ण

अटल u32 sec_get_hw_err_status(काष्ठा hisi_qm *qm)
अणु
	वापस पढ़ोl(qm->io_base + SEC_CORE_INT_STATUS);
पूर्ण

अटल व्योम sec_clear_hw_err_status(काष्ठा hisi_qm *qm, u32 err_sts)
अणु
	ग_लिखोl(err_sts, qm->io_base + SEC_CORE_INT_SOURCE);
पूर्ण

अटल व्योम sec_खोलो_axi_master_ooo(काष्ठा hisi_qm *qm)
अणु
	u32 val;

	val = पढ़ोl(qm->io_base + SEC_CONTROL_REG);
	ग_लिखोl(val & SEC_AXI_SHUTDOWN_DISABLE, qm->io_base + SEC_CONTROL_REG);
	ग_लिखोl(val | SEC_AXI_SHUTDOWN_ENABLE, qm->io_base + SEC_CONTROL_REG);
पूर्ण

अटल व्योम sec_err_info_init(काष्ठा hisi_qm *qm)
अणु
	काष्ठा hisi_qm_err_info *err_info = &qm->err_info;

	err_info->ce = QM_BASE_CE;
	err_info->fe = 0;
	err_info->ecc_2bits_mask = SEC_CORE_INT_STATUS_M_ECC;
	err_info->dev_ce_mask = SEC_RAS_CE_ENB_MSK;
	err_info->msi_wr_port = BIT(0);
	err_info->acpi_rst = "SRST";
	err_info->nfe = QM_BASE_NFE | QM_ACC_DO_TASK_TIMEOUT |
			QM_ACC_WB_NOT_READY_TIMEOUT;
पूर्ण

अटल स्थिर काष्ठा hisi_qm_err_ini sec_err_ini = अणु
	.hw_init		= sec_set_user_करोमुख्य_and_cache,
	.hw_err_enable		= sec_hw_error_enable,
	.hw_err_disable		= sec_hw_error_disable,
	.get_dev_hw_err_status	= sec_get_hw_err_status,
	.clear_dev_hw_err_status = sec_clear_hw_err_status,
	.log_dev_hw_err		= sec_log_hw_error,
	.खोलो_axi_master_ooo	= sec_खोलो_axi_master_ooo,
	.err_info_init		= sec_err_info_init,
पूर्ण;

अटल पूर्णांक sec_pf_probe_init(काष्ठा sec_dev *sec)
अणु
	काष्ठा hisi_qm *qm = &sec->qm;
	पूर्णांक ret;

	qm->err_ini = &sec_err_ini;
	qm->err_ini->err_info_init(qm);

	ret = sec_set_user_करोमुख्य_and_cache(qm);
	अगर (ret)
		वापस ret;

	hisi_qm_dev_err_init(qm);
	sec_debug_regs_clear(qm);

	वापस 0;
पूर्ण

अटल पूर्णांक sec_qm_init(काष्ठा hisi_qm *qm, काष्ठा pci_dev *pdev)
अणु
	पूर्णांक ret;

	qm->pdev = pdev;
	qm->ver = pdev->revision;
	qm->algs = "cipher\ndigest\naead";
	qm->mode = uacce_mode;
	qm->sqe_size = SEC_SQE_SIZE;
	qm->dev_name = sec_name;

	qm->fun_type = (pdev->device == SEC_PF_PCI_DEVICE_ID) ?
			QM_HW_PF : QM_HW_VF;
	अगर (qm->fun_type == QM_HW_PF) अणु
		qm->qp_base = SEC_PF_DEF_Q_BASE;
		qm->qp_num = pf_q_num;
		qm->debug.curr_qm_qp_num = pf_q_num;
		qm->qm_list = &sec_devices;
	पूर्ण अन्यथा अगर (qm->fun_type == QM_HW_VF && qm->ver == QM_HW_V1) अणु
		/*
		 * have no way to get qm configure in VM in v1 hardware,
		 * so currently क्रमce PF to uses SEC_PF_DEF_Q_NUM, and क्रमce
		 * to trigger only one VF in v1 hardware.
		 * v2 hardware has no such problem.
		 */
		qm->qp_base = SEC_PF_DEF_Q_NUM;
		qm->qp_num = SEC_QUEUE_NUM_V1 - SEC_PF_DEF_Q_NUM;
	पूर्ण

	/*
	 * WQ_HIGHPRI: SEC request must be low delayed,
	 * so need a high priority workqueue.
	 * WQ_UNBOUND: SEC task is likely with दीर्घ
	 * running CPU पूर्णांकensive workloads.
	 */
	qm->wq = alloc_workqueue("%s", WQ_HIGHPRI | WQ_MEM_RECLAIM |
				 WQ_UNBOUND, num_online_cpus(),
				 pci_name(qm->pdev));
	अगर (!qm->wq) अणु
		pci_err(qm->pdev, "fail to alloc workqueue\n");
		वापस -ENOMEM;
	पूर्ण

	ret = hisi_qm_init(qm);
	अगर (ret)
		destroy_workqueue(qm->wq);

	वापस ret;
पूर्ण

अटल व्योम sec_qm_uninit(काष्ठा hisi_qm *qm)
अणु
	hisi_qm_uninit(qm);
पूर्ण

अटल पूर्णांक sec_probe_init(काष्ठा sec_dev *sec)
अणु
	काष्ठा hisi_qm *qm = &sec->qm;
	पूर्णांक ret;

	अगर (qm->fun_type == QM_HW_PF) अणु
		ret = sec_pf_probe_init(sec);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sec_probe_uninit(काष्ठा hisi_qm *qm)
अणु
	hisi_qm_dev_err_uninit(qm);

	destroy_workqueue(qm->wq);
पूर्ण

अटल व्योम sec_iommu_used_check(काष्ठा sec_dev *sec)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	काष्ठा device *dev = &sec->qm.pdev->dev;

	करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);

	/* Check अगर iommu is used */
	sec->iommu_used = false;
	अगर (करोमुख्य) अणु
		अगर (करोमुख्य->type & __IOMMU_DOMAIN_PAGING)
			sec->iommu_used = true;
		dev_info(dev, "SMMU Opened, the iommu type = %u\n",
			करोमुख्य->type);
	पूर्ण
पूर्ण

अटल पूर्णांक sec_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा sec_dev *sec;
	काष्ठा hisi_qm *qm;
	पूर्णांक ret;

	sec = devm_kzalloc(&pdev->dev, माप(*sec), GFP_KERNEL);
	अगर (!sec)
		वापस -ENOMEM;

	qm = &sec->qm;
	ret = sec_qm_init(qm, pdev);
	अगर (ret) अणु
		pci_err(pdev, "Failed to init SEC QM (%d)!\n", ret);
		वापस ret;
	पूर्ण

	sec->ctx_q_num = ctx_q_num;
	sec_iommu_used_check(sec);

	ret = sec_probe_init(sec);
	अगर (ret) अणु
		pci_err(pdev, "Failed to probe!\n");
		जाओ err_qm_uninit;
	पूर्ण

	ret = hisi_qm_start(qm);
	अगर (ret) अणु
		pci_err(pdev, "Failed to start sec qm!\n");
		जाओ err_probe_uninit;
	पूर्ण

	ret = sec_debugfs_init(qm);
	अगर (ret)
		pci_warn(pdev, "Failed to init debugfs!\n");

	अगर (qm->qp_num >= ctx_q_num) अणु
		ret = hisi_qm_alg_रेजिस्टर(qm, &sec_devices);
		अगर (ret < 0) अणु
			pr_err("Failed to register driver to crypto.\n");
			जाओ err_qm_stop;
		पूर्ण
	पूर्ण अन्यथा अणु
		pci_warn(qm->pdev,
			"Failed to use kernel mode, qp not enough!\n");
	पूर्ण

	अगर (qm->uacce) अणु
		ret = uacce_रेजिस्टर(qm->uacce);
		अगर (ret) अणु
			pci_err(pdev, "failed to register uacce (%d)!\n", ret);
			जाओ err_alg_unरेजिस्टर;
		पूर्ण
	पूर्ण

	अगर (qm->fun_type == QM_HW_PF && vfs_num) अणु
		ret = hisi_qm_sriov_enable(pdev, vfs_num);
		अगर (ret < 0)
			जाओ err_alg_unरेजिस्टर;
	पूर्ण

	वापस 0;

err_alg_unरेजिस्टर:
	hisi_qm_alg_unरेजिस्टर(qm, &sec_devices);
err_qm_stop:
	sec_debugfs_निकास(qm);
	hisi_qm_stop(qm, QM_NORMAL);
err_probe_uninit:
	sec_probe_uninit(qm);
err_qm_uninit:
	sec_qm_uninit(qm);
	वापस ret;
पूर्ण

अटल व्योम sec_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hisi_qm *qm = pci_get_drvdata(pdev);

	hisi_qm_रुको_task_finish(qm, &sec_devices);
	अगर (qm->qp_num >= ctx_q_num)
		hisi_qm_alg_unरेजिस्टर(qm, &sec_devices);

	अगर (qm->fun_type == QM_HW_PF && qm->vfs_num)
		hisi_qm_sriov_disable(pdev, true);

	sec_debugfs_निकास(qm);

	(व्योम)hisi_qm_stop(qm, QM_NORMAL);

	अगर (qm->fun_type == QM_HW_PF)
		sec_debug_regs_clear(qm);

	sec_probe_uninit(qm);

	sec_qm_uninit(qm);
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers sec_err_handler = अणु
	.error_detected = hisi_qm_dev_err_detected,
	.slot_reset	= hisi_qm_dev_slot_reset,
	.reset_prepare	= hisi_qm_reset_prepare,
	.reset_करोne	= hisi_qm_reset_करोne,
पूर्ण;

अटल काष्ठा pci_driver sec_pci_driver = अणु
	.name = "hisi_sec2",
	.id_table = sec_dev_ids,
	.probe = sec_probe,
	.हटाओ = sec_हटाओ,
	.err_handler = &sec_err_handler,
	.sriov_configure = hisi_qm_sriov_configure,
	.shutकरोwn = hisi_qm_dev_shutकरोwn,
पूर्ण;

अटल व्योम sec_रेजिस्टर_debugfs(व्योम)
अणु
	अगर (!debugfs_initialized())
		वापस;

	sec_debugfs_root = debugfs_create_dir("hisi_sec2", शून्य);
पूर्ण

अटल व्योम sec_unरेजिस्टर_debugfs(व्योम)
अणु
	debugfs_हटाओ_recursive(sec_debugfs_root);
पूर्ण

अटल पूर्णांक __init sec_init(व्योम)
अणु
	पूर्णांक ret;

	hisi_qm_init_list(&sec_devices);
	sec_रेजिस्टर_debugfs();

	ret = pci_रेजिस्टर_driver(&sec_pci_driver);
	अगर (ret < 0) अणु
		sec_unरेजिस्टर_debugfs();
		pr_err("Failed to register pci driver.\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास sec_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&sec_pci_driver);
	sec_unरेजिस्टर_debugfs();
पूर्ण

module_init(sec_init);
module_निकास(sec_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Zaibo Xu <xuzaibo@huawei.com>");
MODULE_AUTHOR("Longfang Liu <liulongfang@huawei.com>");
MODULE_AUTHOR("Kai Ye <yekai13@huawei.com>");
MODULE_AUTHOR("Wei Zhang <zhangwei375@huawei.com>");
MODULE_DESCRIPTION("Driver for HiSilicon SEC accelerator");
