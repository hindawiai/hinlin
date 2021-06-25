<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>

#समावेश "hinic_debugfs.h"

अटल काष्ठा dentry *hinic_dbgfs_root;

क्रमागत sq_dbg_info अणु
	GLB_SQ_ID,
	SQ_PI,
	SQ_CI,
	SQ_FI,
	SQ_MSIX_ENTRY,
पूर्ण;

अटल अक्षर *sq_fields[] = अणु"glb_sq_id", "sq_pi", "sq_ci", "sq_fi", "sq_msix_entry"पूर्ण;

अटल u64 hinic_dbg_get_sq_info(काष्ठा hinic_dev *nic_dev, काष्ठा hinic_sq *sq, पूर्णांक idx)
अणु
	काष्ठा hinic_wq *wq = sq->wq;

	चयन (idx) अणु
	हाल GLB_SQ_ID:
		वापस nic_dev->hwdev->func_to_io.global_qpn + sq->qid;
	हाल SQ_PI:
		वापस atomic_पढ़ो(&wq->prod_idx) & wq->mask;
	हाल SQ_CI:
		वापस atomic_पढ़ो(&wq->cons_idx) & wq->mask;
	हाल SQ_FI:
		वापस be16_to_cpu(*(__be16 *)(sq->hw_ci_addr)) & wq->mask;
	हाल SQ_MSIX_ENTRY:
		वापस sq->msix_entry;
	पूर्ण

	वापस 0;
पूर्ण

क्रमागत rq_dbg_info अणु
	GLB_RQ_ID,
	RQ_HW_PI,
	RQ_SW_CI,
	RQ_SW_PI,
	RQ_MSIX_ENTRY,
पूर्ण;

अटल अक्षर *rq_fields[] = अणु"glb_rq_id", "rq_hw_pi", "rq_sw_ci", "rq_sw_pi", "rq_msix_entry"पूर्ण;

अटल u64 hinic_dbg_get_rq_info(काष्ठा hinic_dev *nic_dev, काष्ठा hinic_rq *rq, पूर्णांक idx)
अणु
	काष्ठा hinic_wq *wq = rq->wq;

	चयन (idx) अणु
	हाल GLB_RQ_ID:
		वापस nic_dev->hwdev->func_to_io.global_qpn + rq->qid;
	हाल RQ_HW_PI:
		वापस be16_to_cpu(*(__be16 *)(rq->pi_virt_addr)) & wq->mask;
	हाल RQ_SW_CI:
		वापस atomic_पढ़ो(&wq->cons_idx) & wq->mask;
	हाल RQ_SW_PI:
		वापस atomic_पढ़ो(&wq->prod_idx) & wq->mask;
	हाल RQ_MSIX_ENTRY:
		वापस rq->msix_entry;
	पूर्ण

	वापस 0;
पूर्ण

क्रमागत func_tbl_info अणु
	VALID,
	RX_MODE,
	MTU,
	RQ_DEPTH,
	QUEUE_NUM,
पूर्ण;

अटल अक्षर *func_table_fields[] = अणु"valid", "rx_mode", "mtu", "rq_depth", "cfg_q_num"पूर्ण;

अटल पूर्णांक hinic_dbg_get_func_table(काष्ठा hinic_dev *nic_dev, पूर्णांक idx)
अणु
	काष्ठा tag_sml_funcfg_tbl *funcfg_table_elem;
	काष्ठा hinic_cmd_lt_rd *पढ़ो_data;
	u16 out_size = माप(*पढ़ो_data);
	पूर्णांक err;

	पढ़ो_data = kzalloc(माप(*पढ़ो_data), GFP_KERNEL);
	अगर (!पढ़ो_data)
		वापस ~0;

	पढ़ो_data->node = TBL_ID_FUNC_CFG_SM_NODE;
	पढ़ो_data->inst = TBL_ID_FUNC_CFG_SM_INST;
	पढ़ो_data->entry_size = HINIC_FUNCTION_CONFIGURE_TABLE_SIZE;
	पढ़ो_data->lt_index = HINIC_HWIF_FUNC_IDX(nic_dev->hwdev->hwअगर);
	पढ़ो_data->len = HINIC_FUNCTION_CONFIGURE_TABLE_SIZE;

	err = hinic_port_msg_cmd(nic_dev->hwdev, HINIC_PORT_CMD_RD_LINE_TBL, पढ़ो_data,
				 माप(*पढ़ो_data), पढ़ो_data, &out_size);
	अगर (err || out_size != माप(*पढ़ो_data) || पढ़ो_data->status) अणु
		netअगर_err(nic_dev, drv, nic_dev->netdev,
			  "Failed to get func table, err: %d, status: 0x%x, out size: 0x%x\n",
			  err, पढ़ो_data->status, out_size);
		kमुक्त(पढ़ो_data);
		वापस ~0;
	पूर्ण

	funcfg_table_elem = (काष्ठा tag_sml_funcfg_tbl *)पढ़ो_data->data;

	चयन (idx) अणु
	हाल VALID:
		वापस funcfg_table_elem->dw0.bs.valid;
	हाल RX_MODE:
		वापस funcfg_table_elem->dw0.bs.nic_rx_mode;
	हाल MTU:
		वापस funcfg_table_elem->dw1.bs.mtu;
	हाल RQ_DEPTH:
		वापस funcfg_table_elem->dw13.bs.cfg_rq_depth;
	हाल QUEUE_NUM:
		वापस funcfg_table_elem->dw13.bs.cfg_q_num;
	पूर्ण

	kमुक्त(पढ़ो_data);

	वापस ~0;
पूर्ण

अटल sमाप_प्रकार hinic_dbg_cmd_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer, माप_प्रकार count,
				  loff_t *ppos)
अणु
	काष्ठा hinic_debug_priv *dbg;
	अक्षर ret_buf[20];
	पूर्णांक *desc;
	u64 out;
	पूर्णांक ret;

	desc = filp->निजी_data;
	dbg = container_of(desc, काष्ठा hinic_debug_priv, field_id[*desc]);

	चयन (dbg->type) अणु
	हाल HINIC_DBG_SQ_INFO:
		out = hinic_dbg_get_sq_info(dbg->dev, dbg->object, *desc);
		अवरोध;

	हाल HINIC_DBG_RQ_INFO:
		out = hinic_dbg_get_rq_info(dbg->dev, dbg->object, *desc);
		अवरोध;

	हाल HINIC_DBG_FUNC_TABLE:
		out = hinic_dbg_get_func_table(dbg->dev, *desc);
		अवरोध;

	शेष:
		netअगर_warn(dbg->dev, drv, dbg->dev->netdev, "Invalid hinic debug cmd: %d\n",
			   dbg->type);
		वापस -EINVAL;
	पूर्ण

	ret = snम_लिखो(ret_buf, माप(ret_buf), "0x%llx\n", out);

	वापस simple_पढ़ो_from_buffer(buffer, count, ppos, ret_buf, ret);
पूर्ण

अटल स्थिर काष्ठा file_operations hinic_dbg_cmd_fops = अणु
	.owner = THIS_MODULE,
	.खोलो  = simple_खोलो,
	.पढ़ो  = hinic_dbg_cmd_पढ़ो,
पूर्ण;

अटल पूर्णांक create_dbg_files(काष्ठा hinic_dev *dev, क्रमागत hinic_dbg_type type, व्योम *data,
			    काष्ठा dentry *root, काष्ठा hinic_debug_priv **dbg, अक्षर **field,
			    पूर्णांक nfile)
अणु
	काष्ठा hinic_debug_priv *पंचांगp;
	पूर्णांक i;

	पंचांगp = kzalloc(माप(*पंचांगp), GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	पंचांगp->dev = dev;
	पंचांगp->object = data;
	पंचांगp->type = type;
	पंचांगp->root = root;

	क्रम (i = 0; i < nfile; i++) अणु
		पंचांगp->field_id[i] = i;
		debugfs_create_file(field[i], 0400, root, &पंचांगp->field_id[i], &hinic_dbg_cmd_fops);
	पूर्ण

	*dbg = पंचांगp;

	वापस 0;
पूर्ण

अटल व्योम rem_dbg_files(काष्ठा hinic_debug_priv *dbg)
अणु
	अगर (dbg->type != HINIC_DBG_FUNC_TABLE)
		debugfs_हटाओ_recursive(dbg->root);

	kमुक्त(dbg);
पूर्ण

पूर्णांक hinic_sq_debug_add(काष्ठा hinic_dev *dev, u16 sq_id)
अणु
	काष्ठा hinic_sq *sq;
	काष्ठा dentry *root;
	अक्षर sub_dir[16];

	sq = dev->txqs[sq_id].sq;

	प्र_लिखो(sub_dir, "0x%x", sq_id);

	root = debugfs_create_dir(sub_dir, dev->sq_dbgfs);

	वापस create_dbg_files(dev, HINIC_DBG_SQ_INFO, sq, root, &sq->dbg, sq_fields,
				ARRAY_SIZE(sq_fields));
पूर्ण

व्योम hinic_sq_debug_rem(काष्ठा hinic_sq *sq)
अणु
	अगर (sq->dbg)
		rem_dbg_files(sq->dbg);
पूर्ण

पूर्णांक hinic_rq_debug_add(काष्ठा hinic_dev *dev, u16 rq_id)
अणु
	काष्ठा hinic_rq *rq;
	काष्ठा dentry *root;
	अक्षर sub_dir[16];

	rq = dev->rxqs[rq_id].rq;

	प्र_लिखो(sub_dir, "0x%x", rq_id);

	root = debugfs_create_dir(sub_dir, dev->rq_dbgfs);

	वापस create_dbg_files(dev, HINIC_DBG_RQ_INFO, rq, root, &rq->dbg, rq_fields,
				ARRAY_SIZE(rq_fields));
पूर्ण

व्योम hinic_rq_debug_rem(काष्ठा hinic_rq *rq)
अणु
	अगर (rq->dbg)
		rem_dbg_files(rq->dbg);
पूर्ण

पूर्णांक hinic_func_table_debug_add(काष्ठा hinic_dev *dev)
अणु
	अगर (HINIC_IS_VF(dev->hwdev->hwअगर))
		वापस 0;

	वापस create_dbg_files(dev, HINIC_DBG_FUNC_TABLE, dev, dev->func_tbl_dbgfs, &dev->dbg,
				func_table_fields, ARRAY_SIZE(func_table_fields));
पूर्ण

व्योम hinic_func_table_debug_rem(काष्ठा hinic_dev *dev)
अणु
	अगर (!HINIC_IS_VF(dev->hwdev->hwअगर) && dev->dbg)
		rem_dbg_files(dev->dbg);
पूर्ण

व्योम hinic_sq_dbgfs_init(काष्ठा hinic_dev *nic_dev)
अणु
	nic_dev->sq_dbgfs = debugfs_create_dir("SQs", nic_dev->dbgfs_root);
पूर्ण

व्योम hinic_sq_dbgfs_uninit(काष्ठा hinic_dev *nic_dev)
अणु
	debugfs_हटाओ_recursive(nic_dev->sq_dbgfs);
पूर्ण

व्योम hinic_rq_dbgfs_init(काष्ठा hinic_dev *nic_dev)
अणु
	nic_dev->rq_dbgfs = debugfs_create_dir("RQs", nic_dev->dbgfs_root);
पूर्ण

व्योम hinic_rq_dbgfs_uninit(काष्ठा hinic_dev *nic_dev)
अणु
	debugfs_हटाओ_recursive(nic_dev->rq_dbgfs);
पूर्ण

व्योम hinic_func_tbl_dbgfs_init(काष्ठा hinic_dev *nic_dev)
अणु
	अगर (!HINIC_IS_VF(nic_dev->hwdev->hwअगर))
		nic_dev->func_tbl_dbgfs = debugfs_create_dir("func_table", nic_dev->dbgfs_root);
पूर्ण

व्योम hinic_func_tbl_dbgfs_uninit(काष्ठा hinic_dev *nic_dev)
अणु
	अगर (!HINIC_IS_VF(nic_dev->hwdev->hwअगर))
		debugfs_हटाओ_recursive(nic_dev->func_tbl_dbgfs);
पूर्ण

व्योम hinic_dbg_init(काष्ठा hinic_dev *nic_dev)
अणु
	nic_dev->dbgfs_root = debugfs_create_dir(pci_name(nic_dev->hwdev->hwअगर->pdev),
						 hinic_dbgfs_root);
पूर्ण

व्योम hinic_dbg_uninit(काष्ठा hinic_dev *nic_dev)
अणु
	debugfs_हटाओ_recursive(nic_dev->dbgfs_root);
	nic_dev->dbgfs_root = शून्य;
पूर्ण

व्योम hinic_dbg_रेजिस्टर_debugfs(स्थिर अक्षर *debugfs_dir_name)
अणु
	hinic_dbgfs_root = debugfs_create_dir(debugfs_dir_name, शून्य);
पूर्ण

व्योम hinic_dbg_unरेजिस्टर_debugfs(व्योम)
अणु
	debugfs_हटाओ_recursive(hinic_dbgfs_root);
	hinic_dbgfs_root = शून्य;
पूर्ण
