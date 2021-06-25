<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 HiSilicon Limited. */
#समावेश <linux/acpi.h>
#समावेश <linux/aer.h>
#समावेश <linux/bitops.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/topology.h>
#समावेश <linux/uacce.h>
#समावेश "zip.h"

#घोषणा PCI_DEVICE_ID_ZIP_PF		0xa250
#घोषणा PCI_DEVICE_ID_ZIP_VF		0xa251

#घोषणा HZIP_QUEUE_NUM_V1		4096

#घोषणा HZIP_CLOCK_GATE_CTRL		0x301004
#घोषणा COMP0_ENABLE			BIT(0)
#घोषणा COMP1_ENABLE			BIT(1)
#घोषणा DECOMP0_ENABLE			BIT(2)
#घोषणा DECOMP1_ENABLE			BIT(3)
#घोषणा DECOMP2_ENABLE			BIT(4)
#घोषणा DECOMP3_ENABLE			BIT(5)
#घोषणा DECOMP4_ENABLE			BIT(6)
#घोषणा DECOMP5_ENABLE			BIT(7)
#घोषणा HZIP_ALL_COMP_DECOMP_EN		(COMP0_ENABLE | COMP1_ENABLE | \
					 DECOMP0_ENABLE | DECOMP1_ENABLE | \
					 DECOMP2_ENABLE | DECOMP3_ENABLE | \
					 DECOMP4_ENABLE | DECOMP5_ENABLE)
#घोषणा HZIP_DECOMP_CHECK_ENABLE	BIT(16)
#घोषणा HZIP_FSM_MAX_CNT		0x301008

#घोषणा HZIP_PORT_ARCA_CHE_0		0x301040
#घोषणा HZIP_PORT_ARCA_CHE_1		0x301044
#घोषणा HZIP_PORT_AWCA_CHE_0		0x301060
#घोषणा HZIP_PORT_AWCA_CHE_1		0x301064
#घोषणा HZIP_CACHE_ALL_EN		0xffffffff

#घोषणा HZIP_BD_RUSER_32_63		0x301110
#घोषणा HZIP_SGL_RUSER_32_63		0x30111c
#घोषणा HZIP_DATA_RUSER_32_63		0x301128
#घोषणा HZIP_DATA_WUSER_32_63		0x301134
#घोषणा HZIP_BD_WUSER_32_63		0x301140

#घोषणा HZIP_QM_IDEL_STATUS		0x3040e4

#घोषणा HZIP_CORE_DEBUG_COMP_0		0x302000
#घोषणा HZIP_CORE_DEBUG_COMP_1		0x303000
#घोषणा HZIP_CORE_DEBUG_DECOMP_0	0x304000
#घोषणा HZIP_CORE_DEBUG_DECOMP_1	0x305000
#घोषणा HZIP_CORE_DEBUG_DECOMP_2	0x306000
#घोषणा HZIP_CORE_DEBUG_DECOMP_3	0x307000
#घोषणा HZIP_CORE_DEBUG_DECOMP_4	0x308000
#घोषणा HZIP_CORE_DEBUG_DECOMP_5	0x309000

#घोषणा HZIP_CORE_INT_SOURCE		0x3010A0
#घोषणा HZIP_CORE_INT_MASK_REG		0x3010A4
#घोषणा HZIP_CORE_INT_SET		0x3010A8
#घोषणा HZIP_CORE_INT_STATUS		0x3010AC
#घोषणा HZIP_CORE_INT_STATUS_M_ECC	BIT(1)
#घोषणा HZIP_CORE_SRAM_ECC_ERR_INFO	0x301148
#घोषणा HZIP_CORE_INT_RAS_CE_ENB	0x301160
#घोषणा HZIP_CORE_INT_RAS_CE_ENABLE	0x1
#घोषणा HZIP_CORE_INT_RAS_NFE_ENB	0x301164
#घोषणा HZIP_CORE_INT_RAS_FE_ENB        0x301168
#घोषणा HZIP_CORE_INT_RAS_NFE_ENABLE	0x1FFE
#घोषणा HZIP_SRAM_ECC_ERR_NUM_SHIFT	16
#घोषणा HZIP_SRAM_ECC_ERR_ADDR_SHIFT	24
#घोषणा HZIP_CORE_INT_MASK_ALL		GENMASK(12, 0)
#घोषणा HZIP_COMP_CORE_NUM		2
#घोषणा HZIP_DECOMP_CORE_NUM		6
#घोषणा HZIP_CORE_NUM			(HZIP_COMP_CORE_NUM + \
					 HZIP_DECOMP_CORE_NUM)
#घोषणा HZIP_SQE_SIZE			128
#घोषणा HZIP_SQ_SIZE			(HZIP_SQE_SIZE * QM_Q_DEPTH)
#घोषणा HZIP_PF_DEF_Q_NUM		64
#घोषणा HZIP_PF_DEF_Q_BASE		0

#घोषणा HZIP_SOFT_CTRL_CNT_CLR_CE	0x301000
#घोषणा HZIP_SOFT_CTRL_CNT_CLR_CE_BIT	BIT(0)
#घोषणा HZIP_SOFT_CTRL_ZIP_CONTROL	0x30100C
#घोषणा HZIP_AXI_SHUTDOWN_ENABLE	BIT(14)
#घोषणा HZIP_WR_PORT			BIT(11)

#घोषणा HZIP_BUF_SIZE			22
#घोषणा HZIP_SQE_MASK_OFFSET		64
#घोषणा HZIP_SQE_MASK_LEN		48

#घोषणा HZIP_CNT_CLR_CE_EN		BIT(0)
#घोषणा HZIP_RO_CNT_CLR_CE_EN		BIT(2)
#घोषणा HZIP_RD_CNT_CLR_CE_EN		(HZIP_CNT_CLR_CE_EN | \
					 HZIP_RO_CNT_CLR_CE_EN)

अटल स्थिर अक्षर hisi_zip_name[] = "hisi_zip";
अटल काष्ठा dentry *hzip_debugfs_root;

काष्ठा hisi_zip_hw_error अणु
	u32 पूर्णांक_msk;
	स्थिर अक्षर *msg;
पूर्ण;

काष्ठा zip_dfx_item अणु
	स्थिर अक्षर *name;
	u32 offset;
पूर्ण;

अटल काष्ठा hisi_qm_list zip_devices = अणु
	.रेजिस्टर_to_crypto	= hisi_zip_रेजिस्टर_to_crypto,
	.unरेजिस्टर_from_crypto	= hisi_zip_unरेजिस्टर_from_crypto,
पूर्ण;

अटल काष्ठा zip_dfx_item zip_dfx_files[] = अणु
	अणु"send_cnt", दुरत्व(काष्ठा hisi_zip_dfx, send_cnt)पूर्ण,
	अणु"recv_cnt", दुरत्व(काष्ठा hisi_zip_dfx, recv_cnt)पूर्ण,
	अणु"send_busy_cnt", दुरत्व(काष्ठा hisi_zip_dfx, send_busy_cnt)पूर्ण,
	अणु"err_bd_cnt", दुरत्व(काष्ठा hisi_zip_dfx, err_bd_cnt)पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hisi_zip_hw_error zip_hw_error[] = अणु
	अणु .पूर्णांक_msk = BIT(0), .msg = "zip_ecc_1bitt_err" पूर्ण,
	अणु .पूर्णांक_msk = BIT(1), .msg = "zip_ecc_2bit_err" पूर्ण,
	अणु .पूर्णांक_msk = BIT(2), .msg = "zip_axi_rresp_err" पूर्ण,
	अणु .पूर्णांक_msk = BIT(3), .msg = "zip_axi_bresp_err" पूर्ण,
	अणु .पूर्णांक_msk = BIT(4), .msg = "zip_src_addr_parse_err" पूर्ण,
	अणु .पूर्णांक_msk = BIT(5), .msg = "zip_dst_addr_parse_err" पूर्ण,
	अणु .पूर्णांक_msk = BIT(6), .msg = "zip_pre_in_addr_err" पूर्ण,
	अणु .पूर्णांक_msk = BIT(7), .msg = "zip_pre_in_data_err" पूर्ण,
	अणु .पूर्णांक_msk = BIT(8), .msg = "zip_com_inf_err" पूर्ण,
	अणु .पूर्णांक_msk = BIT(9), .msg = "zip_enc_inf_err" पूर्ण,
	अणु .पूर्णांक_msk = BIT(10), .msg = "zip_pre_out_err" पूर्ण,
	अणु .पूर्णांक_msk = BIT(11), .msg = "zip_axi_poison_err" पूर्ण,
	अणु .पूर्णांक_msk = BIT(12), .msg = "zip_sva_err" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

क्रमागत ctrl_debug_file_index अणु
	HZIP_CLEAR_ENABLE,
	HZIP_DEBUG_खाता_NUM,
पूर्ण;

अटल स्थिर अक्षर * स्थिर ctrl_debug_file_name[] = अणु
	[HZIP_CLEAR_ENABLE] = "clear_enable",
पूर्ण;

काष्ठा ctrl_debug_file अणु
	क्रमागत ctrl_debug_file_index index;
	spinlock_t lock;
	काष्ठा hisi_zip_ctrl *ctrl;
पूर्ण;

/*
 * One ZIP controller has one PF and multiple VFs, some global configurations
 * which PF has need this काष्ठाure.
 *
 * Just relevant क्रम PF.
 */
काष्ठा hisi_zip_ctrl अणु
	काष्ठा hisi_zip *hisi_zip;
	काष्ठा ctrl_debug_file files[HZIP_DEBUG_खाता_NUM];
पूर्ण;

क्रमागत अणु
	HZIP_COMP_CORE0,
	HZIP_COMP_CORE1,
	HZIP_DECOMP_CORE0,
	HZIP_DECOMP_CORE1,
	HZIP_DECOMP_CORE2,
	HZIP_DECOMP_CORE3,
	HZIP_DECOMP_CORE4,
	HZIP_DECOMP_CORE5,
पूर्ण;

अटल स्थिर u64 core_offsets[] = अणु
	[HZIP_COMP_CORE0]   = 0x302000,
	[HZIP_COMP_CORE1]   = 0x303000,
	[HZIP_DECOMP_CORE0] = 0x304000,
	[HZIP_DECOMP_CORE1] = 0x305000,
	[HZIP_DECOMP_CORE2] = 0x306000,
	[HZIP_DECOMP_CORE3] = 0x307000,
	[HZIP_DECOMP_CORE4] = 0x308000,
	[HZIP_DECOMP_CORE5] = 0x309000,
पूर्ण;

अटल स्थिर काष्ठा debugfs_reg32 hzip_dfx_regs[] = अणु
	अणु"HZIP_GET_BD_NUM                ",  0x00ullपूर्ण,
	अणु"HZIP_GET_RIGHT_BD              ",  0x04ullपूर्ण,
	अणु"HZIP_GET_ERROR_BD              ",  0x08ullपूर्ण,
	अणु"HZIP_DONE_BD_NUM               ",  0x0cullपूर्ण,
	अणु"HZIP_WORK_CYCLE                ",  0x10ullपूर्ण,
	अणु"HZIP_IDLE_CYCLE                ",  0x18ullपूर्ण,
	अणु"HZIP_MAX_DELAY                 ",  0x20ullपूर्ण,
	अणु"HZIP_MIN_DELAY                 ",  0x24ullपूर्ण,
	अणु"HZIP_AVG_DELAY                 ",  0x28ullपूर्ण,
	अणु"HZIP_MEM_VISIBLE_DATA          ",  0x30ullपूर्ण,
	अणु"HZIP_MEM_VISIBLE_ADDR          ",  0x34ullपूर्ण,
	अणु"HZIP_COMSUMED_BYTE             ",  0x38ullपूर्ण,
	अणु"HZIP_PRODUCED_BYTE             ",  0x40ullपूर्ण,
	अणु"HZIP_COMP_INF                  ",  0x70ullपूर्ण,
	अणु"HZIP_PRE_OUT                   ",  0x78ullपूर्ण,
	अणु"HZIP_BD_RD                     ",  0x7cullपूर्ण,
	अणु"HZIP_BD_WR                     ",  0x80ullपूर्ण,
	अणु"HZIP_GET_BD_AXI_ERR_NUM        ",  0x84ullपूर्ण,
	अणु"HZIP_GET_BD_PARSE_ERR_NUM      ",  0x88ullपूर्ण,
	अणु"HZIP_ADD_BD_AXI_ERR_NUM        ",  0x8cullपूर्ण,
	अणु"HZIP_DECOMP_STF_RELOAD_CURR_ST ",  0x94ullपूर्ण,
	अणु"HZIP_DECOMP_LZ77_CURR_ST       ",  0x9cullपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा kernel_param_ops zip_uacce_mode_ops = अणु
	.set = uacce_mode_set,
	.get = param_get_पूर्णांक,
पूर्ण;

/*
 * uacce_mode = 0 means zip only रेजिस्टर to crypto,
 * uacce_mode = 1 means zip both रेजिस्टर to crypto and uacce.
 */
अटल u32 uacce_mode = UACCE_MODE_NOUACCE;
module_param_cb(uacce_mode, &zip_uacce_mode_ops, &uacce_mode, 0444);
MODULE_PARM_DESC(uacce_mode, UACCE_MODE_DESC);

अटल पूर्णांक pf_q_num_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	वापस q_num_set(val, kp, PCI_DEVICE_ID_ZIP_PF);
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops pf_q_num_ops = अणु
	.set = pf_q_num_set,
	.get = param_get_पूर्णांक,
पूर्ण;

अटल u32 pf_q_num = HZIP_PF_DEF_Q_NUM;
module_param_cb(pf_q_num, &pf_q_num_ops, &pf_q_num, 0444);
MODULE_PARM_DESC(pf_q_num, "Number of queues in PF(v1 2-4096, v2 2-1024)");

अटल स्थिर काष्ठा kernel_param_ops vfs_num_ops = अणु
	.set = vfs_num_set,
	.get = param_get_पूर्णांक,
पूर्ण;

अटल u32 vfs_num;
module_param_cb(vfs_num, &vfs_num_ops, &vfs_num, 0444);
MODULE_PARM_DESC(vfs_num, "Number of VFs to enable(1-63), 0(default)");

अटल स्थिर काष्ठा pci_device_id hisi_zip_dev_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_HUAWEI, PCI_DEVICE_ID_ZIP_PF) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_HUAWEI, PCI_DEVICE_ID_ZIP_VF) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, hisi_zip_dev_ids);

पूर्णांक zip_create_qps(काष्ठा hisi_qp **qps, पूर्णांक qp_num, पूर्णांक node)
अणु
	अगर (node == NUMA_NO_NODE)
		node = cpu_to_node(smp_processor_id());

	वापस hisi_qm_alloc_qps_node(&zip_devices, qp_num, 0, node, qps);
पूर्ण

अटल पूर्णांक hisi_zip_set_user_करोमुख्य_and_cache(काष्ठा hisi_qm *qm)
अणु
	व्योम __iomem *base = qm->io_base;

	/* qm user करोमुख्य */
	ग_लिखोl(AXUSER_BASE, base + QM_ARUSER_M_CFG_1);
	ग_लिखोl(ARUSER_M_CFG_ENABLE, base + QM_ARUSER_M_CFG_ENABLE);
	ग_लिखोl(AXUSER_BASE, base + QM_AWUSER_M_CFG_1);
	ग_लिखोl(AWUSER_M_CFG_ENABLE, base + QM_AWUSER_M_CFG_ENABLE);
	ग_लिखोl(WUSER_M_CFG_ENABLE, base + QM_WUSER_M_CFG_ENABLE);

	/* qm cache */
	ग_लिखोl(AXI_M_CFG, base + QM_AXI_M_CFG);
	ग_लिखोl(AXI_M_CFG_ENABLE, base + QM_AXI_M_CFG_ENABLE);

	/* disable FLR triggered by BME(bus master enable) */
	ग_लिखोl(PEH_AXUSER_CFG, base + QM_PEH_AXUSER_CFG);
	ग_लिखोl(PEH_AXUSER_CFG_ENABLE, base + QM_PEH_AXUSER_CFG_ENABLE);

	/* cache */
	ग_लिखोl(HZIP_CACHE_ALL_EN, base + HZIP_PORT_ARCA_CHE_0);
	ग_लिखोl(HZIP_CACHE_ALL_EN, base + HZIP_PORT_ARCA_CHE_1);
	ग_लिखोl(HZIP_CACHE_ALL_EN, base + HZIP_PORT_AWCA_CHE_0);
	ग_लिखोl(HZIP_CACHE_ALL_EN, base + HZIP_PORT_AWCA_CHE_1);

	/* user करोमुख्य configurations */
	ग_लिखोl(AXUSER_BASE, base + HZIP_BD_RUSER_32_63);
	ग_लिखोl(AXUSER_BASE, base + HZIP_SGL_RUSER_32_63);
	ग_लिखोl(AXUSER_BASE, base + HZIP_BD_WUSER_32_63);

	अगर (qm->use_sva && qm->ver == QM_HW_V2) अणु
		ग_लिखोl(AXUSER_BASE | AXUSER_SSV, base + HZIP_DATA_RUSER_32_63);
		ग_लिखोl(AXUSER_BASE | AXUSER_SSV, base + HZIP_DATA_WUSER_32_63);
	पूर्ण अन्यथा अणु
		ग_लिखोl(AXUSER_BASE, base + HZIP_DATA_RUSER_32_63);
		ग_लिखोl(AXUSER_BASE, base + HZIP_DATA_WUSER_32_63);
	पूर्ण

	/* let's खोलो all compression/decompression cores */
	ग_लिखोl(HZIP_DECOMP_CHECK_ENABLE | HZIP_ALL_COMP_DECOMP_EN,
	       base + HZIP_CLOCK_GATE_CTRL);

	/* enable sqc,cqc ग_लिखोback */
	ग_लिखोl(SQC_CACHE_ENABLE | CQC_CACHE_ENABLE | SQC_CACHE_WB_ENABLE |
	       CQC_CACHE_WB_ENABLE | FIELD_PREP(SQC_CACHE_WB_THRD, 1) |
	       FIELD_PREP(CQC_CACHE_WB_THRD, 1), base + QM_CACHE_CTL);

	वापस 0;
पूर्ण

अटल व्योम hisi_zip_hw_error_enable(काष्ठा hisi_qm *qm)
अणु
	u32 val;

	अगर (qm->ver == QM_HW_V1) अणु
		ग_लिखोl(HZIP_CORE_INT_MASK_ALL,
		       qm->io_base + HZIP_CORE_INT_MASK_REG);
		dev_info(&qm->pdev->dev, "Does not support hw error handle\n");
		वापस;
	पूर्ण

	/* clear ZIP hw error source अगर having */
	ग_लिखोl(HZIP_CORE_INT_MASK_ALL, qm->io_base + HZIP_CORE_INT_SOURCE);

	/* configure error type */
	ग_लिखोl(HZIP_CORE_INT_RAS_CE_ENABLE,
	       qm->io_base + HZIP_CORE_INT_RAS_CE_ENB);
	ग_लिखोl(0x0, qm->io_base + HZIP_CORE_INT_RAS_FE_ENB);
	ग_लिखोl(HZIP_CORE_INT_RAS_NFE_ENABLE,
	       qm->io_base + HZIP_CORE_INT_RAS_NFE_ENB);

	/* enable ZIP hw error पूर्णांकerrupts */
	ग_लिखोl(0, qm->io_base + HZIP_CORE_INT_MASK_REG);

	/* enable ZIP block master OOO when m-bit error occur */
	val = पढ़ोl(qm->io_base + HZIP_SOFT_CTRL_ZIP_CONTROL);
	val = val | HZIP_AXI_SHUTDOWN_ENABLE;
	ग_लिखोl(val, qm->io_base + HZIP_SOFT_CTRL_ZIP_CONTROL);
पूर्ण

अटल व्योम hisi_zip_hw_error_disable(काष्ठा hisi_qm *qm)
अणु
	u32 val;

	/* disable ZIP hw error पूर्णांकerrupts */
	ग_लिखोl(HZIP_CORE_INT_MASK_ALL, qm->io_base + HZIP_CORE_INT_MASK_REG);

	/* disable ZIP block master OOO when m-bit error occur */
	val = पढ़ोl(qm->io_base + HZIP_SOFT_CTRL_ZIP_CONTROL);
	val = val & ~HZIP_AXI_SHUTDOWN_ENABLE;
	ग_लिखोl(val, qm->io_base + HZIP_SOFT_CTRL_ZIP_CONTROL);
पूर्ण

अटल अंतरभूत काष्ठा hisi_qm *file_to_qm(काष्ठा ctrl_debug_file *file)
अणु
	काष्ठा hisi_zip *hisi_zip = file->ctrl->hisi_zip;

	वापस &hisi_zip->qm;
पूर्ण

अटल u32 clear_enable_पढ़ो(काष्ठा ctrl_debug_file *file)
अणु
	काष्ठा hisi_qm *qm = file_to_qm(file);

	वापस पढ़ोl(qm->io_base + HZIP_SOFT_CTRL_CNT_CLR_CE) &
		     HZIP_SOFT_CTRL_CNT_CLR_CE_BIT;
पूर्ण

अटल पूर्णांक clear_enable_ग_लिखो(काष्ठा ctrl_debug_file *file, u32 val)
अणु
	काष्ठा hisi_qm *qm = file_to_qm(file);
	u32 पंचांगp;

	अगर (val != 1 && val != 0)
		वापस -EINVAL;

	पंचांगp = (पढ़ोl(qm->io_base + HZIP_SOFT_CTRL_CNT_CLR_CE) &
	       ~HZIP_SOFT_CTRL_CNT_CLR_CE_BIT) | val;
	ग_लिखोl(पंचांगp, qm->io_base + HZIP_SOFT_CTRL_CNT_CLR_CE);

	वापस  0;
पूर्ण

अटल sमाप_प्रकार hisi_zip_ctrl_debug_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
					माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा ctrl_debug_file *file = filp->निजी_data;
	अक्षर tbuf[HZIP_BUF_SIZE];
	u32 val;
	पूर्णांक ret;

	spin_lock_irq(&file->lock);
	चयन (file->index) अणु
	हाल HZIP_CLEAR_ENABLE:
		val = clear_enable_पढ़ो(file);
		अवरोध;
	शेष:
		spin_unlock_irq(&file->lock);
		वापस -EINVAL;
	पूर्ण
	spin_unlock_irq(&file->lock);
	ret = scnम_लिखो(tbuf, माप(tbuf), "%u\n", val);
	वापस simple_पढ़ो_from_buffer(buf, count, pos, tbuf, ret);
पूर्ण

अटल sमाप_प्रकार hisi_zip_ctrl_debug_ग_लिखो(काष्ठा file *filp,
					 स्थिर अक्षर __user *buf,
					 माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा ctrl_debug_file *file = filp->निजी_data;
	अक्षर tbuf[HZIP_BUF_SIZE];
	अचिन्हित दीर्घ val;
	पूर्णांक len, ret;

	अगर (*pos != 0)
		वापस 0;

	अगर (count >= HZIP_BUF_SIZE)
		वापस -ENOSPC;

	len = simple_ग_लिखो_to_buffer(tbuf, HZIP_BUF_SIZE - 1, pos, buf, count);
	अगर (len < 0)
		वापस len;

	tbuf[len] = '\0';
	अगर (kम_से_अदीर्घ(tbuf, 0, &val))
		वापस -EFAULT;

	spin_lock_irq(&file->lock);
	चयन (file->index) अणु
	हाल HZIP_CLEAR_ENABLE:
		ret = clear_enable_ग_लिखो(file, val);
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

अटल स्थिर काष्ठा file_operations ctrl_debug_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = hisi_zip_ctrl_debug_पढ़ो,
	.ग_लिखो = hisi_zip_ctrl_debug_ग_लिखो,
पूर्ण;

अटल पूर्णांक zip_debugfs_atomic64_set(व्योम *data, u64 val)
अणु
	अगर (val)
		वापस -EINVAL;

	atomic64_set((atomic64_t *)data, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक zip_debugfs_atomic64_get(व्योम *data, u64 *val)
अणु
	*val = atomic64_पढ़ो((atomic64_t *)data);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(zip_atomic64_ops, zip_debugfs_atomic64_get,
			 zip_debugfs_atomic64_set, "%llu\n");

अटल पूर्णांक hisi_zip_core_debug_init(काष्ठा hisi_qm *qm)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	काष्ठा debugfs_regset32 *regset;
	काष्ठा dentry *पंचांगp_d;
	अक्षर buf[HZIP_BUF_SIZE];
	पूर्णांक i;

	क्रम (i = 0; i < HZIP_CORE_NUM; i++) अणु
		अगर (i < HZIP_COMP_CORE_NUM)
			scnम_लिखो(buf, माप(buf), "comp_core%d", i);
		अन्यथा
			scnम_लिखो(buf, माप(buf), "decomp_core%d",
				  i - HZIP_COMP_CORE_NUM);

		regset = devm_kzalloc(dev, माप(*regset), GFP_KERNEL);
		अगर (!regset)
			वापस -ENOENT;

		regset->regs = hzip_dfx_regs;
		regset->nregs = ARRAY_SIZE(hzip_dfx_regs);
		regset->base = qm->io_base + core_offsets[i];

		पंचांगp_d = debugfs_create_dir(buf, qm->debug.debug_root);
		debugfs_create_regset32("regs", 0444, पंचांगp_d, regset);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hisi_zip_dfx_debug_init(काष्ठा hisi_qm *qm)
अणु
	काष्ठा hisi_zip *zip = container_of(qm, काष्ठा hisi_zip, qm);
	काष्ठा hisi_zip_dfx *dfx = &zip->dfx;
	काष्ठा dentry *पंचांगp_dir;
	व्योम *data;
	पूर्णांक i;

	पंचांगp_dir = debugfs_create_dir("zip_dfx", qm->debug.debug_root);
	क्रम (i = 0; i < ARRAY_SIZE(zip_dfx_files); i++) अणु
		data = (atomic64_t *)((uपूर्णांकptr_t)dfx + zip_dfx_files[i].offset);
		debugfs_create_file(zip_dfx_files[i].name,
				    0644, पंचांगp_dir, data,
				    &zip_atomic64_ops);
	पूर्ण
पूर्ण

अटल पूर्णांक hisi_zip_ctrl_debug_init(काष्ठा hisi_qm *qm)
अणु
	काष्ठा hisi_zip *zip = container_of(qm, काष्ठा hisi_zip, qm);
	पूर्णांक i;

	क्रम (i = HZIP_CLEAR_ENABLE; i < HZIP_DEBUG_खाता_NUM; i++) अणु
		spin_lock_init(&zip->ctrl->files[i].lock);
		zip->ctrl->files[i].ctrl = zip->ctrl;
		zip->ctrl->files[i].index = i;

		debugfs_create_file(ctrl_debug_file_name[i], 0600,
				    qm->debug.debug_root,
				    zip->ctrl->files + i,
				    &ctrl_debug_fops);
	पूर्ण

	वापस hisi_zip_core_debug_init(qm);
पूर्ण

अटल पूर्णांक hisi_zip_debugfs_init(काष्ठा hisi_qm *qm)
अणु
	काष्ठा device *dev = &qm->pdev->dev;
	काष्ठा dentry *dev_d;
	पूर्णांक ret;

	dev_d = debugfs_create_dir(dev_name(dev), hzip_debugfs_root);

	qm->debug.sqe_mask_offset = HZIP_SQE_MASK_OFFSET;
	qm->debug.sqe_mask_len = HZIP_SQE_MASK_LEN;
	qm->debug.debug_root = dev_d;
	hisi_qm_debug_init(qm);

	अगर (qm->fun_type == QM_HW_PF) अणु
		ret = hisi_zip_ctrl_debug_init(qm);
		अगर (ret)
			जाओ failed_to_create;
	पूर्ण

	hisi_zip_dfx_debug_init(qm);

	वापस 0;

failed_to_create:
	debugfs_हटाओ_recursive(hzip_debugfs_root);
	वापस ret;
पूर्ण

/* hisi_zip_debug_regs_clear() - clear the zip debug regs */
अटल व्योम hisi_zip_debug_regs_clear(काष्ठा hisi_qm *qm)
अणु
	पूर्णांक i, j;

	/* enable रेजिस्टर पढ़ो_clear bit */
	ग_लिखोl(HZIP_RD_CNT_CLR_CE_EN, qm->io_base + HZIP_SOFT_CTRL_CNT_CLR_CE);
	क्रम (i = 0; i < ARRAY_SIZE(core_offsets); i++)
		क्रम (j = 0; j < ARRAY_SIZE(hzip_dfx_regs); j++)
			पढ़ोl(qm->io_base + core_offsets[i] +
			      hzip_dfx_regs[j].offset);

	/* disable रेजिस्टर पढ़ो_clear bit */
	ग_लिखोl(0x0, qm->io_base + HZIP_SOFT_CTRL_CNT_CLR_CE);

	hisi_qm_debug_regs_clear(qm);
पूर्ण

अटल व्योम hisi_zip_debugfs_निकास(काष्ठा hisi_qm *qm)
अणु
	debugfs_हटाओ_recursive(qm->debug.debug_root);

	अगर (qm->fun_type == QM_HW_PF) अणु
		hisi_zip_debug_regs_clear(qm);
		qm->debug.curr_qm_qp_num = 0;
	पूर्ण
पूर्ण

अटल व्योम hisi_zip_log_hw_error(काष्ठा hisi_qm *qm, u32 err_sts)
अणु
	स्थिर काष्ठा hisi_zip_hw_error *err = zip_hw_error;
	काष्ठा device *dev = &qm->pdev->dev;
	u32 err_val;

	जबतक (err->msg) अणु
		अगर (err->पूर्णांक_msk & err_sts) अणु
			dev_err(dev, "%s [error status=0x%x] found\n",
				err->msg, err->पूर्णांक_msk);

			अगर (err->पूर्णांक_msk & HZIP_CORE_INT_STATUS_M_ECC) अणु
				err_val = पढ़ोl(qm->io_base +
						HZIP_CORE_SRAM_ECC_ERR_INFO);
				dev_err(dev, "hisi-zip multi ecc sram num=0x%x\n",
					((err_val >>
					HZIP_SRAM_ECC_ERR_NUM_SHIFT) & 0xFF));
			पूर्ण
		पूर्ण
		err++;
	पूर्ण
पूर्ण

अटल u32 hisi_zip_get_hw_err_status(काष्ठा hisi_qm *qm)
अणु
	वापस पढ़ोl(qm->io_base + HZIP_CORE_INT_STATUS);
पूर्ण

अटल व्योम hisi_zip_clear_hw_err_status(काष्ठा hisi_qm *qm, u32 err_sts)
अणु
	ग_लिखोl(err_sts, qm->io_base + HZIP_CORE_INT_SOURCE);
पूर्ण

अटल व्योम hisi_zip_खोलो_axi_master_ooo(काष्ठा hisi_qm *qm)
अणु
	u32 val;

	val = पढ़ोl(qm->io_base + HZIP_SOFT_CTRL_ZIP_CONTROL);

	ग_लिखोl(val & ~HZIP_AXI_SHUTDOWN_ENABLE,
	       qm->io_base + HZIP_SOFT_CTRL_ZIP_CONTROL);

	ग_लिखोl(val | HZIP_AXI_SHUTDOWN_ENABLE,
	       qm->io_base + HZIP_SOFT_CTRL_ZIP_CONTROL);
पूर्ण

अटल व्योम hisi_zip_बंद_axi_master_ooo(काष्ठा hisi_qm *qm)
अणु
	u32 nfe_enb;

	/* Disable ECC Mbit error report. */
	nfe_enb = पढ़ोl(qm->io_base + HZIP_CORE_INT_RAS_NFE_ENB);
	ग_लिखोl(nfe_enb & ~HZIP_CORE_INT_STATUS_M_ECC,
	       qm->io_base + HZIP_CORE_INT_RAS_NFE_ENB);

	/* Inject zip ECC Mbit error to block master ooo. */
	ग_लिखोl(HZIP_CORE_INT_STATUS_M_ECC,
	       qm->io_base + HZIP_CORE_INT_SET);
पूर्ण

अटल व्योम hisi_zip_err_info_init(काष्ठा hisi_qm *qm)
अणु
	काष्ठा hisi_qm_err_info *err_info = &qm->err_info;

	err_info->ce = QM_BASE_CE;
	err_info->fe = 0;
	err_info->ecc_2bits_mask = HZIP_CORE_INT_STATUS_M_ECC;
	err_info->dev_ce_mask = HZIP_CORE_INT_RAS_CE_ENABLE;
	err_info->msi_wr_port = HZIP_WR_PORT;
	err_info->acpi_rst = "ZRST";
	err_info->nfe = QM_BASE_NFE | QM_ACC_WB_NOT_READY_TIMEOUT;

	अगर (qm->ver >= QM_HW_V3)
		err_info->nfe |= QM_ACC_DO_TASK_TIMEOUT;
पूर्ण

अटल स्थिर काष्ठा hisi_qm_err_ini hisi_zip_err_ini = अणु
	.hw_init		= hisi_zip_set_user_करोमुख्य_and_cache,
	.hw_err_enable		= hisi_zip_hw_error_enable,
	.hw_err_disable		= hisi_zip_hw_error_disable,
	.get_dev_hw_err_status	= hisi_zip_get_hw_err_status,
	.clear_dev_hw_err_status = hisi_zip_clear_hw_err_status,
	.log_dev_hw_err		= hisi_zip_log_hw_error,
	.खोलो_axi_master_ooo	= hisi_zip_खोलो_axi_master_ooo,
	.बंद_axi_master_ooo	= hisi_zip_बंद_axi_master_ooo,
	.err_info_init		= hisi_zip_err_info_init,
पूर्ण;

अटल पूर्णांक hisi_zip_pf_probe_init(काष्ठा hisi_zip *hisi_zip)
अणु
	काष्ठा hisi_qm *qm = &hisi_zip->qm;
	काष्ठा hisi_zip_ctrl *ctrl;

	ctrl = devm_kzalloc(&qm->pdev->dev, माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl)
		वापस -ENOMEM;

	hisi_zip->ctrl = ctrl;
	ctrl->hisi_zip = hisi_zip;
	qm->err_ini = &hisi_zip_err_ini;
	qm->err_ini->err_info_init(qm);

	hisi_zip_set_user_करोमुख्य_and_cache(qm);
	hisi_qm_dev_err_init(qm);
	hisi_zip_debug_regs_clear(qm);

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_zip_qm_init(काष्ठा hisi_qm *qm, काष्ठा pci_dev *pdev)
अणु
	पूर्णांक ret;

	qm->pdev = pdev;
	qm->ver = pdev->revision;
	qm->algs = "zlib\ngzip";
	qm->mode = uacce_mode;
	qm->sqe_size = HZIP_SQE_SIZE;
	qm->dev_name = hisi_zip_name;

	qm->fun_type = (pdev->device == PCI_DEVICE_ID_ZIP_PF) ?
			QM_HW_PF : QM_HW_VF;
	अगर (qm->fun_type == QM_HW_PF) अणु
		qm->qp_base = HZIP_PF_DEF_Q_BASE;
		qm->qp_num = pf_q_num;
		qm->debug.curr_qm_qp_num = pf_q_num;
		qm->qm_list = &zip_devices;
	पूर्ण अन्यथा अगर (qm->fun_type == QM_HW_VF && qm->ver == QM_HW_V1) अणु
		/*
		 * have no way to get qm configure in VM in v1 hardware,
		 * so currently क्रमce PF to uses HZIP_PF_DEF_Q_NUM, and क्रमce
		 * to trigger only one VF in v1 hardware.
		 *
		 * v2 hardware has no such problem.
		 */
		qm->qp_base = HZIP_PF_DEF_Q_NUM;
		qm->qp_num = HZIP_QUEUE_NUM_V1 - HZIP_PF_DEF_Q_NUM;
	पूर्ण

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

अटल व्योम hisi_zip_qm_uninit(काष्ठा hisi_qm *qm)
अणु
	hisi_qm_uninit(qm);
	destroy_workqueue(qm->wq);
पूर्ण

अटल पूर्णांक hisi_zip_probe_init(काष्ठा hisi_zip *hisi_zip)
अणु
	काष्ठा hisi_qm *qm = &hisi_zip->qm;
	पूर्णांक ret;

	अगर (qm->fun_type == QM_HW_PF) अणु
		ret = hisi_zip_pf_probe_init(hisi_zip);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_zip_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा hisi_zip *hisi_zip;
	काष्ठा hisi_qm *qm;
	पूर्णांक ret;

	hisi_zip = devm_kzalloc(&pdev->dev, माप(*hisi_zip), GFP_KERNEL);
	अगर (!hisi_zip)
		वापस -ENOMEM;

	qm = &hisi_zip->qm;

	ret = hisi_zip_qm_init(qm, pdev);
	अगर (ret) अणु
		pci_err(pdev, "Failed to init ZIP QM (%d)!\n", ret);
		वापस ret;
	पूर्ण

	ret = hisi_zip_probe_init(hisi_zip);
	अगर (ret) अणु
		pci_err(pdev, "Failed to probe (%d)!\n", ret);
		जाओ err_qm_uninit;
	पूर्ण

	ret = hisi_qm_start(qm);
	अगर (ret)
		जाओ err_dev_err_uninit;

	ret = hisi_zip_debugfs_init(qm);
	अगर (ret)
		pci_err(pdev, "failed to init debugfs (%d)!\n", ret);

	ret = hisi_qm_alg_रेजिस्टर(qm, &zip_devices);
	अगर (ret < 0) अणु
		pci_err(pdev, "failed to register driver to crypto!\n");
		जाओ err_qm_stop;
	पूर्ण

	अगर (qm->uacce) अणु
		ret = uacce_रेजिस्टर(qm->uacce);
		अगर (ret) अणु
			pci_err(pdev, "failed to register uacce (%d)!\n", ret);
			जाओ err_qm_alg_unरेजिस्टर;
		पूर्ण
	पूर्ण

	अगर (qm->fun_type == QM_HW_PF && vfs_num > 0) अणु
		ret = hisi_qm_sriov_enable(pdev, vfs_num);
		अगर (ret < 0)
			जाओ err_qm_alg_unरेजिस्टर;
	पूर्ण

	वापस 0;

err_qm_alg_unरेजिस्टर:
	hisi_qm_alg_unरेजिस्टर(qm, &zip_devices);

err_qm_stop:
	hisi_zip_debugfs_निकास(qm);
	hisi_qm_stop(qm, QM_NORMAL);

err_dev_err_uninit:
	hisi_qm_dev_err_uninit(qm);

err_qm_uninit:
	hisi_zip_qm_uninit(qm);

	वापस ret;
पूर्ण

अटल व्योम hisi_zip_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hisi_qm *qm = pci_get_drvdata(pdev);

	hisi_qm_रुको_task_finish(qm, &zip_devices);
	hisi_qm_alg_unरेजिस्टर(qm, &zip_devices);

	अगर (qm->fun_type == QM_HW_PF && qm->vfs_num)
		hisi_qm_sriov_disable(pdev, true);

	hisi_zip_debugfs_निकास(qm);
	hisi_qm_stop(qm, QM_NORMAL);
	hisi_qm_dev_err_uninit(qm);
	hisi_zip_qm_uninit(qm);
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers hisi_zip_err_handler = अणु
	.error_detected	= hisi_qm_dev_err_detected,
	.slot_reset	= hisi_qm_dev_slot_reset,
	.reset_prepare	= hisi_qm_reset_prepare,
	.reset_करोne	= hisi_qm_reset_करोne,
पूर्ण;

अटल काष्ठा pci_driver hisi_zip_pci_driver = अणु
	.name			= "hisi_zip",
	.id_table		= hisi_zip_dev_ids,
	.probe			= hisi_zip_probe,
	.हटाओ			= hisi_zip_हटाओ,
	.sriov_configure	= IS_ENABLED(CONFIG_PCI_IOV) ?
					hisi_qm_sriov_configure : शून्य,
	.err_handler		= &hisi_zip_err_handler,
	.shutकरोwn		= hisi_qm_dev_shutकरोwn,
पूर्ण;

अटल व्योम hisi_zip_रेजिस्टर_debugfs(व्योम)
अणु
	अगर (!debugfs_initialized())
		वापस;

	hzip_debugfs_root = debugfs_create_dir("hisi_zip", शून्य);
पूर्ण

अटल व्योम hisi_zip_unरेजिस्टर_debugfs(व्योम)
अणु
	debugfs_हटाओ_recursive(hzip_debugfs_root);
पूर्ण

अटल पूर्णांक __init hisi_zip_init(व्योम)
अणु
	पूर्णांक ret;

	hisi_qm_init_list(&zip_devices);
	hisi_zip_रेजिस्टर_debugfs();

	ret = pci_रेजिस्टर_driver(&hisi_zip_pci_driver);
	अगर (ret < 0) अणु
		hisi_zip_unरेजिस्टर_debugfs();
		pr_err("Failed to register pci driver.\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास hisi_zip_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&hisi_zip_pci_driver);
	hisi_zip_unरेजिस्टर_debugfs();
पूर्ण

module_init(hisi_zip_init);
module_निकास(hisi_zip_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Zhou Wang <wangzhou1@hisilicon.com>");
MODULE_DESCRIPTION("Driver for HiSilicon ZIP accelerator");
