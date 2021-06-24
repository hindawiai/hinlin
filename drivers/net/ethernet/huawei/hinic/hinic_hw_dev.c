<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/log2.h>
#समावेश <linux/err.h>
#समावेश <linux/netdevice.h>
#समावेश <net/devlink.h>

#समावेश "hinic_devlink.h"
#समावेश "hinic_sriov.h"
#समावेश "hinic_dev.h"
#समावेश "hinic_hw_if.h"
#समावेश "hinic_hw_eqs.h"
#समावेश "hinic_hw_mgmt.h"
#समावेश "hinic_hw_qp_ctxt.h"
#समावेश "hinic_hw_qp.h"
#समावेश "hinic_hw_io.h"
#समावेश "hinic_hw_dev.h"

#घोषणा IO_STATUS_TIMEOUT               100
#घोषणा OUTBOUND_STATE_TIMEOUT          100
#घोषणा DB_STATE_TIMEOUT                100

#घोषणा MAX_IRQS(max_qps, num_aeqs, num_ceqs)   \
		 (2 * (max_qps) + (num_aeqs) + (num_ceqs))

#घोषणा ADDR_IN_4BYTES(addr)            ((addr) >> 2)

क्रमागत पूर्णांकr_type अणु
	INTR_MSIX_TYPE,
पूर्ण;

क्रमागत io_status अणु
	IO_STOPPED = 0,
	IO_RUNNING = 1,
पूर्ण;

/**
 * get_capability - convert device capabilities to NIC capabilities
 * @hwdev: the HW device to set and convert device capabilities क्रम
 * @dev_cap: device capabilities from FW
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक parse_capability(काष्ठा hinic_hwdev *hwdev,
			    काष्ठा hinic_dev_cap *dev_cap)
अणु
	काष्ठा hinic_cap *nic_cap = &hwdev->nic_cap;
	पूर्णांक num_aeqs, num_ceqs, num_irqs;

	अगर (!HINIC_IS_VF(hwdev->hwअगर) && dev_cap->पूर्णांकr_type != INTR_MSIX_TYPE)
		वापस -EFAULT;

	num_aeqs = HINIC_HWIF_NUM_AEQS(hwdev->hwअगर);
	num_ceqs = HINIC_HWIF_NUM_CEQS(hwdev->hwअगर);
	num_irqs = HINIC_HWIF_NUM_IRQS(hwdev->hwअगर);

	/* Each QP has its own (SQ + RQ) पूर्णांकerrupts */
	nic_cap->num_qps = (num_irqs - (num_aeqs + num_ceqs)) / 2;

	अगर (nic_cap->num_qps > HINIC_Q_CTXT_MAX)
		nic_cap->num_qps = HINIC_Q_CTXT_MAX;

	अगर (!HINIC_IS_VF(hwdev->hwअगर))
		nic_cap->max_qps = dev_cap->max_sqs + 1;
	अन्यथा
		nic_cap->max_qps = dev_cap->max_sqs;

	अगर (nic_cap->num_qps > nic_cap->max_qps)
		nic_cap->num_qps = nic_cap->max_qps;

	अगर (!HINIC_IS_VF(hwdev->hwअगर)) अणु
		nic_cap->max_vf = dev_cap->max_vf;
		nic_cap->max_vf_qps = dev_cap->max_vf_sqs + 1;
	पूर्ण

	hwdev->port_id = dev_cap->port_id;

	वापस 0;
पूर्ण

/**
 * get_cap_from_fw - get device capabilities from FW
 * @pfhwdev: the PF HW device to get capabilities क्रम
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक get_capability(काष्ठा hinic_pfhwdev *pfhwdev)
अणु
	काष्ठा hinic_hwdev *hwdev = &pfhwdev->hwdev;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	काष्ठा hinic_dev_cap dev_cap;
	u16 out_len;
	पूर्णांक err;

	out_len = माप(dev_cap);

	err = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_CFGM,
				HINIC_CFG_NIC_CAP, &dev_cap, माप(dev_cap),
				&dev_cap, &out_len, HINIC_MGMT_MSG_SYNC);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to get capability from FW\n");
		वापस err;
	पूर्ण

	वापस parse_capability(hwdev, &dev_cap);
पूर्ण

/**
 * get_dev_cap - get device capabilities
 * @hwdev: the NIC HW device to get capabilities क्रम
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक get_dev_cap(काष्ठा hinic_hwdev *hwdev)
अणु
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	काष्ठा hinic_pfhwdev *pfhwdev;
	पूर्णांक err;

	चयन (HINIC_FUNC_TYPE(hwअगर)) अणु
	हाल HINIC_PPF:
	हाल HINIC_PF:
	हाल HINIC_VF:
		pfhwdev = container_of(hwdev, काष्ठा hinic_pfhwdev, hwdev);
		err = get_capability(pfhwdev);
		अगर (err) अणु
			dev_err(&pdev->dev, "Failed to get capability\n");
			वापस err;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unsupported PCI Function type\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * init_msix - enable the msix and save the entries
 * @hwdev: the NIC HW device
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक init_msix(काष्ठा hinic_hwdev *hwdev)
अणु
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक nr_irqs, num_aeqs, num_ceqs;
	माप_प्रकार msix_entries_size;
	पूर्णांक i, err;

	num_aeqs = HINIC_HWIF_NUM_AEQS(hwअगर);
	num_ceqs = HINIC_HWIF_NUM_CEQS(hwअगर);
	nr_irqs = MAX_IRQS(HINIC_MAX_QPS, num_aeqs, num_ceqs);
	अगर (nr_irqs > HINIC_HWIF_NUM_IRQS(hwअगर))
		nr_irqs = HINIC_HWIF_NUM_IRQS(hwअगर);

	msix_entries_size = nr_irqs * माप(*hwdev->msix_entries);
	hwdev->msix_entries = devm_kzalloc(&pdev->dev, msix_entries_size,
					   GFP_KERNEL);
	अगर (!hwdev->msix_entries)
		वापस -ENOMEM;

	क्रम (i = 0; i < nr_irqs; i++)
		hwdev->msix_entries[i].entry = i;

	err = pci_enable_msix_exact(pdev, hwdev->msix_entries, nr_irqs);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to enable pci msix\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * disable_msix - disable the msix
 * @hwdev: the NIC HW device
 **/
अटल व्योम disable_msix(काष्ठा hinic_hwdev *hwdev)
अणु
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;

	pci_disable_msix(pdev);
पूर्ण

/**
 * hinic_port_msg_cmd - send port msg to mgmt
 * @hwdev: the NIC HW device
 * @cmd: the port command
 * @buf_in: input buffer
 * @in_size: input size
 * @buf_out: output buffer
 * @out_size: वापसed output size
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_port_msg_cmd(काष्ठा hinic_hwdev *hwdev, क्रमागत hinic_port_cmd cmd,
		       व्योम *buf_in, u16 in_size, व्योम *buf_out, u16 *out_size)
अणु
	काष्ठा hinic_pfhwdev *pfhwdev;

	pfhwdev = container_of(hwdev, काष्ठा hinic_pfhwdev, hwdev);

	वापस hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_L2NIC, cmd,
				 buf_in, in_size, buf_out, out_size,
				 HINIC_MGMT_MSG_SYNC);
पूर्ण

पूर्णांक hinic_hilink_msg_cmd(काष्ठा hinic_hwdev *hwdev, क्रमागत hinic_hilink_cmd cmd,
			 व्योम *buf_in, u16 in_size, व्योम *buf_out,
			 u16 *out_size)
अणु
	काष्ठा hinic_pfhwdev *pfhwdev;

	pfhwdev = container_of(hwdev, काष्ठा hinic_pfhwdev, hwdev);

	वापस hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_HILINK, cmd,
				 buf_in, in_size, buf_out, out_size,
				 HINIC_MGMT_MSG_SYNC);
पूर्ण

/**
 * init_fw_ctxt- Init Firmware tables beक्रमe network mgmt and io operations
 * @hwdev: the NIC HW device
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक init_fw_ctxt(काष्ठा hinic_hwdev *hwdev)
अणु
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	काष्ठा hinic_cmd_fw_ctxt fw_ctxt;
	u16 out_size = माप(fw_ctxt);
	पूर्णांक err;

	fw_ctxt.func_idx = HINIC_HWIF_FUNC_IDX(hwअगर);
	fw_ctxt.rx_buf_sz = HINIC_RX_BUF_SZ;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_FWCTXT_INIT,
				 &fw_ctxt, माप(fw_ctxt),
				 &fw_ctxt, &out_size);
	अगर (err || (out_size != माप(fw_ctxt)) || fw_ctxt.status) अणु
		dev_err(&pdev->dev, "Failed to init FW ctxt, err: %d, status: 0x%x, out size: 0x%x\n",
			err, fw_ctxt.status, out_size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * set_hw_ioctxt - set the shape of the IO queues in FW
 * @hwdev: the NIC HW device
 * @rq_depth: rq depth
 * @sq_depth: sq depth
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक set_hw_ioctxt(काष्ठा hinic_hwdev *hwdev, अचिन्हित पूर्णांक sq_depth,
			 अचिन्हित पूर्णांक rq_depth)
अणु
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा hinic_cmd_hw_ioctxt hw_ioctxt;
	काष्ठा hinic_pfhwdev *pfhwdev;

	hw_ioctxt.func_idx = HINIC_HWIF_FUNC_IDX(hwअगर);
	hw_ioctxt.ppf_idx = HINIC_HWIF_PPF_IDX(hwअगर);

	hw_ioctxt.set_cmdq_depth = HW_IOCTXT_SET_CMDQ_DEPTH_DEFAULT;
	hw_ioctxt.cmdq_depth = 0;

	hw_ioctxt.lro_en = 1;

	hw_ioctxt.rq_depth  = ilog2(rq_depth);

	hw_ioctxt.rx_buf_sz_idx = HINIC_RX_BUF_SZ_IDX;

	hw_ioctxt.sq_depth  = ilog2(sq_depth);

	pfhwdev = container_of(hwdev, काष्ठा hinic_pfhwdev, hwdev);

	वापस hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
				 HINIC_COMM_CMD_HWCTXT_SET,
				 &hw_ioctxt, माप(hw_ioctxt), शून्य,
				 शून्य, HINIC_MGMT_MSG_SYNC);
पूर्ण

अटल पूर्णांक रुको_क्रम_outbound_state(काष्ठा hinic_hwdev *hwdev)
अणु
	क्रमागत hinic_outbound_state outbound_state;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	अचिन्हित दीर्घ end;

	end = jअगरfies + msecs_to_jअगरfies(OUTBOUND_STATE_TIMEOUT);
	करो अणु
		outbound_state = hinic_outbound_state_get(hwअगर);

		अगर (outbound_state == HINIC_OUTBOUND_ENABLE)
			वापस 0;

		msleep(20);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end));

	dev_err(&pdev->dev, "Wait for OUTBOUND - Timeout\n");
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक रुको_क्रम_db_state(काष्ठा hinic_hwdev *hwdev)
अणु
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	क्रमागत hinic_db_state db_state;
	अचिन्हित दीर्घ end;

	end = jअगरfies + msecs_to_jअगरfies(DB_STATE_TIMEOUT);
	करो अणु
		db_state = hinic_db_state_get(hwअगर);

		अगर (db_state == HINIC_DB_ENABLE)
			वापस 0;

		msleep(20);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end));

	dev_err(&pdev->dev, "Wait for DB - Timeout\n");
	वापस -EFAULT;
पूर्ण

/**
 * clear_io_resource - set the IO resources as not active in the NIC
 * @hwdev: the NIC HW device
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक clear_io_resources(काष्ठा hinic_hwdev *hwdev)
अणु
	काष्ठा hinic_cmd_clear_io_res cmd_clear_io_res;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	काष्ठा hinic_pfhwdev *pfhwdev;
	पूर्णांक err;

	/* sleep 100ms to रुको क्रम firmware stopping I/O */
	msleep(100);

	cmd_clear_io_res.func_idx = HINIC_HWIF_FUNC_IDX(hwअगर);

	pfhwdev = container_of(hwdev, काष्ठा hinic_pfhwdev, hwdev);

	err = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
				HINIC_COMM_CMD_IO_RES_CLEAR, &cmd_clear_io_res,
				माप(cmd_clear_io_res), शून्य, शून्य,
				HINIC_MGMT_MSG_SYNC);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to clear IO resources\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * set_resources_state - set the state of the resources in the NIC
 * @hwdev: the NIC HW device
 * @state: the state to set
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक set_resources_state(काष्ठा hinic_hwdev *hwdev,
			       क्रमागत hinic_res_state state)
अणु
	काष्ठा hinic_cmd_set_res_state res_state;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा hinic_pfhwdev *pfhwdev;

	res_state.func_idx = HINIC_HWIF_FUNC_IDX(hwअगर);
	res_state.state = state;

	pfhwdev = container_of(hwdev, काष्ठा hinic_pfhwdev, hwdev);

	वापस hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt,
				 HINIC_MOD_COMM,
				 HINIC_COMM_CMD_RES_STATE_SET,
				 &res_state, माप(res_state), शून्य,
				 शून्य, HINIC_MGMT_MSG_SYNC);
पूर्ण

/**
 * get_base_qpn - get the first qp number
 * @hwdev: the NIC HW device
 * @base_qpn: वापसed qp number
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक get_base_qpn(काष्ठा hinic_hwdev *hwdev, u16 *base_qpn)
अणु
	काष्ठा hinic_cmd_base_qpn cmd_base_qpn;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	u16 out_size = माप(cmd_base_qpn);
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक err;

	cmd_base_qpn.func_idx = HINIC_HWIF_FUNC_IDX(hwअगर);

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_GET_GLOBAL_QPN,
				 &cmd_base_qpn, माप(cmd_base_qpn),
				 &cmd_base_qpn, &out_size);
	अगर (err || (out_size != माप(cmd_base_qpn)) || cmd_base_qpn.status) अणु
		dev_err(&pdev->dev, "Failed to get base qpn, err: %d, status: 0x%x, out size: 0x%x\n",
			err, cmd_base_qpn.status, out_size);
		वापस -EIO;
	पूर्ण

	*base_qpn = cmd_base_qpn.qpn;
	वापस 0;
पूर्ण

/**
 * hinic_hwdev_अगरup - Preparing the HW क्रम passing IO
 * @hwdev: the NIC HW device
 * @sq_depth: the send queue depth
 * @rq_depth: the receive queue depth
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_hwdev_अगरup(काष्ठा hinic_hwdev *hwdev, u16 sq_depth, u16 rq_depth)
अणु
	काष्ठा hinic_func_to_io *func_to_io = &hwdev->func_to_io;
	काष्ठा hinic_cap *nic_cap = &hwdev->nic_cap;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	पूर्णांक err, num_aeqs, num_ceqs, num_qps;
	काष्ठा msix_entry *ceq_msix_entries;
	काष्ठा msix_entry *sq_msix_entries;
	काष्ठा msix_entry *rq_msix_entries;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	u16 base_qpn;

	err = get_base_qpn(hwdev, &base_qpn);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to get global base qp number\n");
		वापस err;
	पूर्ण

	num_aeqs = HINIC_HWIF_NUM_AEQS(hwअगर);
	num_ceqs = HINIC_HWIF_NUM_CEQS(hwअगर);

	ceq_msix_entries = &hwdev->msix_entries[num_aeqs];
	func_to_io->hwdev = hwdev;
	func_to_io->sq_depth = sq_depth;
	func_to_io->rq_depth = rq_depth;
	func_to_io->global_qpn = base_qpn;

	err = hinic_io_init(func_to_io, hwअगर, nic_cap->max_qps, num_ceqs,
			    ceq_msix_entries);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to init IO channel\n");
		वापस err;
	पूर्ण

	num_qps = nic_cap->num_qps;
	sq_msix_entries = &hwdev->msix_entries[num_aeqs + num_ceqs];
	rq_msix_entries = &hwdev->msix_entries[num_aeqs + num_ceqs + num_qps];

	err = hinic_io_create_qps(func_to_io, base_qpn, num_qps,
				  sq_msix_entries, rq_msix_entries);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to create QPs\n");
		जाओ err_create_qps;
	पूर्ण

	err = रुको_क्रम_db_state(hwdev);
	अगर (err) अणु
		dev_warn(&pdev->dev, "db - disabled, try again\n");
		hinic_db_state_set(hwअगर, HINIC_DB_ENABLE);
	पूर्ण

	err = set_hw_ioctxt(hwdev, sq_depth, rq_depth);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to set HW IO ctxt\n");
		जाओ err_hw_ioctxt;
	पूर्ण

	वापस 0;

err_hw_ioctxt:
	hinic_io_destroy_qps(func_to_io, num_qps);

err_create_qps:
	hinic_io_मुक्त(func_to_io);
	वापस err;
पूर्ण

/**
 * hinic_hwdev_अगरकरोwn - Closing the HW क्रम passing IO
 * @hwdev: the NIC HW device
 *
 **/
व्योम hinic_hwdev_अगरकरोwn(काष्ठा hinic_hwdev *hwdev)
अणु
	काष्ठा hinic_func_to_io *func_to_io = &hwdev->func_to_io;
	काष्ठा hinic_cap *nic_cap = &hwdev->nic_cap;

	clear_io_resources(hwdev);

	hinic_io_destroy_qps(func_to_io, nic_cap->num_qps);
	hinic_io_मुक्त(func_to_io);
पूर्ण

/**
 * hinic_hwdev_cb_रेजिस्टर - रेजिस्टर callback handler क्रम MGMT events
 * @hwdev: the NIC HW device
 * @cmd: the mgmt event
 * @handle: निजी data क्रम the handler
 * @handler: event handler
 **/
व्योम hinic_hwdev_cb_रेजिस्टर(काष्ठा hinic_hwdev *hwdev,
			     क्रमागत hinic_mgmt_msg_cmd cmd, व्योम *handle,
			     व्योम (*handler)(व्योम *handle, व्योम *buf_in,
					     u16 in_size, व्योम *buf_out,
					     u16 *out_size))
अणु
	काष्ठा hinic_pfhwdev *pfhwdev;
	काष्ठा hinic_nic_cb *nic_cb;
	u8 cmd_cb;

	pfhwdev = container_of(hwdev, काष्ठा hinic_pfhwdev, hwdev);

	cmd_cb = cmd - HINIC_MGMT_MSG_CMD_BASE;
	nic_cb = &pfhwdev->nic_cb[cmd_cb];

	nic_cb->handler = handler;
	nic_cb->handle = handle;
	nic_cb->cb_state = HINIC_CB_ENABLED;
पूर्ण

/**
 * hinic_hwdev_cb_unरेजिस्टर - unरेजिस्टर callback handler क्रम MGMT events
 * @hwdev: the NIC HW device
 * @cmd: the mgmt event
 **/
व्योम hinic_hwdev_cb_unरेजिस्टर(काष्ठा hinic_hwdev *hwdev,
			       क्रमागत hinic_mgmt_msg_cmd cmd)
अणु
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा hinic_pfhwdev *pfhwdev;
	काष्ठा hinic_nic_cb *nic_cb;
	u8 cmd_cb;

	अगर (!HINIC_IS_PF(hwअगर) && !HINIC_IS_PPF(hwअगर))
		वापस;

	pfhwdev = container_of(hwdev, काष्ठा hinic_pfhwdev, hwdev);

	cmd_cb = cmd - HINIC_MGMT_MSG_CMD_BASE;
	nic_cb = &pfhwdev->nic_cb[cmd_cb];

	nic_cb->cb_state &= ~HINIC_CB_ENABLED;

	जबतक (nic_cb->cb_state & HINIC_CB_RUNNING)
		schedule();

	nic_cb->handler = शून्य;
पूर्ण

/**
 * nic_mgmt_msg_handler - nic mgmt event handler
 * @handle: निजी data क्रम the handler
 * @cmd: message command
 * @buf_in: input buffer
 * @in_size: input size
 * @buf_out: output buffer
 * @out_size: वापसed output size
 **/
अटल व्योम nic_mgmt_msg_handler(व्योम *handle, u8 cmd, व्योम *buf_in,
				 u16 in_size, व्योम *buf_out, u16 *out_size)
अणु
	काष्ठा hinic_pfhwdev *pfhwdev = handle;
	क्रमागत hinic_cb_state cb_state;
	काष्ठा hinic_nic_cb *nic_cb;
	काष्ठा hinic_hwdev *hwdev;
	काष्ठा hinic_hwअगर *hwअगर;
	काष्ठा pci_dev *pdev;
	u8 cmd_cb;

	hwdev = &pfhwdev->hwdev;
	hwअगर = hwdev->hwअगर;
	pdev = hwअगर->pdev;

	अगर ((cmd < HINIC_MGMT_MSG_CMD_BASE) ||
	    (cmd >= HINIC_MGMT_MSG_CMD_MAX)) अणु
		dev_err(&pdev->dev, "unknown L2NIC event, cmd = %d\n", cmd);
		वापस;
	पूर्ण

	cmd_cb = cmd - HINIC_MGMT_MSG_CMD_BASE;

	nic_cb = &pfhwdev->nic_cb[cmd_cb];

	cb_state = cmpxchg(&nic_cb->cb_state,
			   HINIC_CB_ENABLED,
			   HINIC_CB_ENABLED | HINIC_CB_RUNNING);

	अगर ((cb_state == HINIC_CB_ENABLED) && (nic_cb->handler))
		nic_cb->handler(nic_cb->handle, buf_in,
				in_size, buf_out, out_size);
	अन्यथा
		dev_err(&pdev->dev, "Unhandled NIC Event %d\n", cmd);

	nic_cb->cb_state &= ~HINIC_CB_RUNNING;
पूर्ण

अटल व्योम hinic_comm_recv_mgmt_self_cmd_reg(काष्ठा hinic_pfhwdev *pfhwdev,
					      u8 cmd,
					      comm_mgmt_self_msg_proc proc)
अणु
	u8 cmd_idx;

	cmd_idx = pfhwdev->proc.cmd_num;
	अगर (cmd_idx >= HINIC_COMM_SELF_CMD_MAX) अणु
		dev_err(&pfhwdev->hwdev.hwअगर->pdev->dev,
			"Register recv mgmt process failed, cmd: 0x%x\n", cmd);
		वापस;
	पूर्ण

	pfhwdev->proc.info[cmd_idx].cmd = cmd;
	pfhwdev->proc.info[cmd_idx].proc = proc;
	pfhwdev->proc.cmd_num++;
पूर्ण

अटल व्योम hinic_comm_recv_mgmt_self_cmd_unreg(काष्ठा hinic_pfhwdev *pfhwdev,
						u8 cmd)
अणु
	u8 cmd_idx;

	cmd_idx = pfhwdev->proc.cmd_num;
	अगर (cmd_idx >= HINIC_COMM_SELF_CMD_MAX) अणु
		dev_err(&pfhwdev->hwdev.hwअगर->pdev->dev, "Unregister recv mgmt process failed, cmd: 0x%x\n",
			cmd);
		वापस;
	पूर्ण

	क्रम (cmd_idx = 0; cmd_idx < HINIC_COMM_SELF_CMD_MAX; cmd_idx++) अणु
		अगर (cmd == pfhwdev->proc.info[cmd_idx].cmd) अणु
			pfhwdev->proc.info[cmd_idx].cmd = 0;
			pfhwdev->proc.info[cmd_idx].proc = शून्य;
			pfhwdev->proc.cmd_num--;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम comm_mgmt_msg_handler(व्योम *handle, u8 cmd, व्योम *buf_in,
				  u16 in_size, व्योम *buf_out, u16 *out_size)
अणु
	काष्ठा hinic_pfhwdev *pfhwdev = handle;
	u8 cmd_idx;

	क्रम (cmd_idx = 0; cmd_idx < pfhwdev->proc.cmd_num; cmd_idx++) अणु
		अगर (cmd == pfhwdev->proc.info[cmd_idx].cmd) अणु
			अगर (!pfhwdev->proc.info[cmd_idx].proc) अणु
				dev_warn(&pfhwdev->hwdev.hwअगर->pdev->dev,
					 "PF recv mgmt comm msg handle null, cmd: 0x%x\n",
					 cmd);
			पूर्ण अन्यथा अणु
				pfhwdev->proc.info[cmd_idx].proc
					(&pfhwdev->hwdev, buf_in, in_size,
					 buf_out, out_size);
			पूर्ण

			वापस;
		पूर्ण
	पूर्ण

	dev_warn(&pfhwdev->hwdev.hwअगर->pdev->dev, "Received unknown mgmt cpu event: 0x%x\n",
		 cmd);

	*out_size = 0;
पूर्ण

/* pf fault report event */
अटल व्योम pf_fault_event_handler(व्योम *dev, व्योम *buf_in, u16 in_size,
				   व्योम *buf_out, u16 *out_size)
अणु
	काष्ठा hinic_cmd_fault_event *fault_event = buf_in;
	काष्ठा hinic_hwdev *hwdev = dev;

	अगर (in_size != माप(*fault_event)) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Invalid fault event report, length: %d, should be %zu\n",
			in_size, माप(*fault_event));
		वापस;
	पूर्ण

	अगर (!hwdev->devlink_dev || IS_ERR_OR_शून्य(hwdev->devlink_dev->hw_fault_reporter))
		वापस;

	devlink_health_report(hwdev->devlink_dev->hw_fault_reporter,
			      "HW fatal error reported", &fault_event->event);
पूर्ण

अटल व्योम mgmt_watchकरोg_समयout_event_handler(व्योम *dev,
						व्योम *buf_in, u16 in_size,
						व्योम *buf_out, u16 *out_size)
अणु
	काष्ठा hinic_mgmt_watchकरोg_info *watchकरोg_info = buf_in;
	काष्ठा hinic_hwdev *hwdev = dev;

	अगर (in_size != माप(*watchकरोg_info)) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Invalid mgmt watchdog report, length: %d, should be %zu\n",
			in_size, माप(*watchकरोg_info));
		वापस;
	पूर्ण

	अगर (!hwdev->devlink_dev || IS_ERR_OR_शून्य(hwdev->devlink_dev->fw_fault_reporter))
		वापस;

	devlink_health_report(hwdev->devlink_dev->fw_fault_reporter,
			      "FW fatal error reported", watchकरोg_info);
पूर्ण

/**
 * init_pfhwdev - Initialize the extended components of PF
 * @pfhwdev: the HW device क्रम PF
 *
 * Return 0 - success, negative - failure
 **/
अटल पूर्णांक init_pfhwdev(काष्ठा hinic_pfhwdev *pfhwdev)
अणु
	काष्ठा hinic_hwdev *hwdev = &pfhwdev->hwdev;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक err;

	err = hinic_pf_to_mgmt_init(&pfhwdev->pf_to_mgmt, hwअगर);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to initialize PF to MGMT channel\n");
		वापस err;
	पूर्ण

	err = hinic_devlink_रेजिस्टर(hwdev->devlink_dev, &pdev->dev);
	अगर (err) अणु
		dev_err(&hwअगर->pdev->dev, "Failed to register devlink\n");
		hinic_pf_to_mgmt_मुक्त(&pfhwdev->pf_to_mgmt);
		वापस err;
	पूर्ण

	err = hinic_func_to_func_init(hwdev);
	अगर (err) अणु
		dev_err(&hwअगर->pdev->dev, "Failed to init mailbox\n");
		hinic_devlink_unरेजिस्टर(hwdev->devlink_dev);
		hinic_pf_to_mgmt_मुक्त(&pfhwdev->pf_to_mgmt);
		वापस err;
	पूर्ण

	अगर (!HINIC_IS_VF(hwअगर)) अणु
		hinic_रेजिस्टर_mgmt_msg_cb(&pfhwdev->pf_to_mgmt,
					   HINIC_MOD_L2NIC, pfhwdev,
					   nic_mgmt_msg_handler);
		hinic_रेजिस्टर_mgmt_msg_cb(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
					   pfhwdev, comm_mgmt_msg_handler);
		hinic_comm_recv_mgmt_self_cmd_reg(pfhwdev,
						  HINIC_COMM_CMD_FAULT_REPORT,
						  pf_fault_event_handler);
		hinic_comm_recv_mgmt_self_cmd_reg
			(pfhwdev, HINIC_COMM_CMD_WATCHDOG_INFO,
			 mgmt_watchकरोg_समयout_event_handler);
	पूर्ण अन्यथा अणु
		hinic_रेजिस्टर_vf_mbox_cb(hwdev, HINIC_MOD_L2NIC,
					  nic_mgmt_msg_handler);
	पूर्ण

	hinic_set_pf_action(hwअगर, HINIC_PF_MGMT_ACTIVE);

	वापस 0;
पूर्ण

/**
 * मुक्त_pfhwdev - Free the extended components of PF
 * @pfhwdev: the HW device क्रम PF
 **/
अटल व्योम मुक्त_pfhwdev(काष्ठा hinic_pfhwdev *pfhwdev)
अणु
	काष्ठा hinic_hwdev *hwdev = &pfhwdev->hwdev;

	hinic_set_pf_action(hwdev->hwअगर, HINIC_PF_MGMT_INIT);

	अगर (!HINIC_IS_VF(hwdev->hwअगर)) अणु
		hinic_comm_recv_mgmt_self_cmd_unreg(pfhwdev,
						    HINIC_COMM_CMD_WATCHDOG_INFO);
		hinic_comm_recv_mgmt_self_cmd_unreg(pfhwdev,
						    HINIC_COMM_CMD_FAULT_REPORT);
		hinic_unरेजिस्टर_mgmt_msg_cb(&pfhwdev->pf_to_mgmt,
					     HINIC_MOD_COMM);
		hinic_unरेजिस्टर_mgmt_msg_cb(&pfhwdev->pf_to_mgmt,
					     HINIC_MOD_L2NIC);
	पूर्ण अन्यथा अणु
		hinic_unरेजिस्टर_vf_mbox_cb(hwdev, HINIC_MOD_L2NIC);
	पूर्ण

	hinic_func_to_func_मुक्त(hwdev);

	hinic_devlink_unरेजिस्टर(hwdev->devlink_dev);

	hinic_pf_to_mgmt_मुक्त(&pfhwdev->pf_to_mgmt);
पूर्ण

अटल पूर्णांक hinic_l2nic_reset(काष्ठा hinic_hwdev *hwdev)
अणु
	काष्ठा hinic_cmd_l2nic_reset l2nic_reset = अणु0पूर्ण;
	u16 out_size = माप(l2nic_reset);
	काष्ठा hinic_pfhwdev *pfhwdev;
	पूर्णांक err;

	pfhwdev = container_of(hwdev, काष्ठा hinic_pfhwdev, hwdev);

	l2nic_reset.func_id = HINIC_HWIF_FUNC_IDX(hwdev->hwअगर);
	/* 0 represents standard l2nic reset flow */
	l2nic_reset.reset_flag = 0;

	err = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
				HINIC_COMM_CMD_L2NIC_RESET, &l2nic_reset,
				माप(l2nic_reset), &l2nic_reset,
				&out_size, HINIC_MGMT_MSG_SYNC);
	अगर (err || !out_size || l2nic_reset.status) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Failed to reset L2NIC resources, err: %d, status: 0x%x, out_size: 0x%x\n",
			err, l2nic_reset.status, out_size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hinic_get_पूर्णांकerrupt_cfg(काष्ठा hinic_hwdev *hwdev,
			    काष्ठा hinic_msix_config *पूर्णांकerrupt_info)
अणु
	u16 out_size = माप(*पूर्णांकerrupt_info);
	काष्ठा hinic_pfhwdev *pfhwdev;
	पूर्णांक err;

	अगर (!hwdev || !पूर्णांकerrupt_info)
		वापस -EINVAL;

	pfhwdev = container_of(hwdev, काष्ठा hinic_pfhwdev, hwdev);

	पूर्णांकerrupt_info->func_id = HINIC_HWIF_FUNC_IDX(hwdev->hwअगर);

	err = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
				HINIC_COMM_CMD_MSI_CTRL_REG_RD_BY_UP,
				पूर्णांकerrupt_info, माप(*पूर्णांकerrupt_info),
				पूर्णांकerrupt_info, &out_size, HINIC_MGMT_MSG_SYNC);
	अगर (err || !out_size || पूर्णांकerrupt_info->status) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Failed to get interrupt config, err: %d, status: 0x%x, out size: 0x%x\n",
			err, पूर्णांकerrupt_info->status, out_size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hinic_set_पूर्णांकerrupt_cfg(काष्ठा hinic_hwdev *hwdev,
			    काष्ठा hinic_msix_config *पूर्णांकerrupt_info)
अणु
	u16 out_size = माप(*पूर्णांकerrupt_info);
	काष्ठा hinic_msix_config temp_info;
	काष्ठा hinic_pfhwdev *pfhwdev;
	पूर्णांक err;

	अगर (!hwdev)
		वापस -EINVAL;

	pfhwdev = container_of(hwdev, काष्ठा hinic_pfhwdev, hwdev);

	पूर्णांकerrupt_info->func_id = HINIC_HWIF_FUNC_IDX(hwdev->hwअगर);

	err = hinic_get_पूर्णांकerrupt_cfg(hwdev, &temp_info);
	अगर (err)
		वापस -EINVAL;

	पूर्णांकerrupt_info->lli_credit_cnt = temp_info.lli_समयr_cnt;
	पूर्णांकerrupt_info->lli_समयr_cnt = temp_info.lli_समयr_cnt;

	err = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
				HINIC_COMM_CMD_MSI_CTRL_REG_WR_BY_UP,
				पूर्णांकerrupt_info, माप(*पूर्णांकerrupt_info),
				पूर्णांकerrupt_info, &out_size, HINIC_MGMT_MSG_SYNC);
	अगर (err || !out_size || पूर्णांकerrupt_info->status) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Failed to get interrupt config, err: %d, status: 0x%x, out size: 0x%x\n",
			err, पूर्णांकerrupt_info->status, out_size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hinic_init_hwdev - Initialize the NIC HW
 * @pdev: the NIC pci device
 * @devlink: the poniter of hinic devlink
 *
 * Return initialized NIC HW device
 *
 * Initialize the NIC HW device and वापस a poपूर्णांकer to it
 **/
काष्ठा hinic_hwdev *hinic_init_hwdev(काष्ठा pci_dev *pdev, काष्ठा devlink *devlink)
अणु
	काष्ठा hinic_pfhwdev *pfhwdev;
	काष्ठा hinic_hwdev *hwdev;
	काष्ठा hinic_hwअगर *hwअगर;
	पूर्णांक err, num_aeqs;

	hwअगर = devm_kzalloc(&pdev->dev, माप(*hwअगर), GFP_KERNEL);
	अगर (!hwअगर)
		वापस ERR_PTR(-ENOMEM);

	err = hinic_init_hwअगर(hwअगर, pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to init HW interface\n");
		वापस ERR_PTR(err);
	पूर्ण

	pfhwdev = devm_kzalloc(&pdev->dev, माप(*pfhwdev), GFP_KERNEL);
	अगर (!pfhwdev) अणु
		err = -ENOMEM;
		जाओ err_pfhwdev_alloc;
	पूर्ण

	hwdev = &pfhwdev->hwdev;
	hwdev->hwअगर = hwअगर;
	hwdev->devlink_dev = devlink_priv(devlink);
	hwdev->devlink_dev->hwdev = hwdev;

	err = init_msix(hwdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to init msix\n");
		जाओ err_init_msix;
	पूर्ण

	err = रुको_क्रम_outbound_state(hwdev);
	अगर (err) अणु
		dev_warn(&pdev->dev, "outbound - disabled, try again\n");
		hinic_outbound_state_set(hwअगर, HINIC_OUTBOUND_ENABLE);
	पूर्ण

	num_aeqs = HINIC_HWIF_NUM_AEQS(hwअगर);

	err = hinic_aeqs_init(&hwdev->aeqs, hwअगर, num_aeqs,
			      HINIC_DEFAULT_AEQ_LEN, HINIC_EQ_PAGE_SIZE,
			      hwdev->msix_entries);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to init async event queues\n");
		जाओ err_aeqs_init;
	पूर्ण

	err = init_pfhwdev(pfhwdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to init PF HW device\n");
		जाओ err_init_pfhwdev;
	पूर्ण

	err = hinic_l2nic_reset(hwdev);
	अगर (err)
		जाओ err_l2nic_reset;

	err = get_dev_cap(hwdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to get device capabilities\n");
		जाओ err_dev_cap;
	पूर्ण

	mutex_init(&hwdev->func_to_io.nic_cfg.cfg_mutex);

	err = hinic_vf_func_init(hwdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to init nic mbox\n");
		जाओ err_vf_func_init;
	पूर्ण

	err = init_fw_ctxt(hwdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to init function table\n");
		जाओ err_init_fw_ctxt;
	पूर्ण

	err = set_resources_state(hwdev, HINIC_RES_ACTIVE);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to set resources state\n");
		जाओ err_resources_state;
	पूर्ण

	वापस hwdev;

err_resources_state:
err_init_fw_ctxt:
	hinic_vf_func_मुक्त(hwdev);
err_vf_func_init:
err_l2nic_reset:
err_dev_cap:
	मुक्त_pfhwdev(pfhwdev);

err_init_pfhwdev:
	hinic_aeqs_मुक्त(&hwdev->aeqs);

err_aeqs_init:
	disable_msix(hwdev);

err_init_msix:
err_pfhwdev_alloc:
	hinic_मुक्त_hwअगर(hwअगर);
	अगर (err > 0)
		err = -EIO;
	वापस ERR_PTR(err);
पूर्ण

/**
 * hinic_मुक्त_hwdev - Free the NIC HW device
 * @hwdev: the NIC HW device
 **/
व्योम hinic_मुक्त_hwdev(काष्ठा hinic_hwdev *hwdev)
अणु
	काष्ठा hinic_pfhwdev *pfhwdev = container_of(hwdev,
						     काष्ठा hinic_pfhwdev,
						     hwdev);

	set_resources_state(hwdev, HINIC_RES_CLEAN);

	hinic_vf_func_मुक्त(hwdev);

	मुक्त_pfhwdev(pfhwdev);

	hinic_aeqs_मुक्त(&hwdev->aeqs);

	disable_msix(hwdev);

	hinic_मुक्त_hwअगर(hwdev->hwअगर);
पूर्ण

पूर्णांक hinic_hwdev_max_num_qps(काष्ठा hinic_hwdev *hwdev)
अणु
	काष्ठा hinic_cap *nic_cap = &hwdev->nic_cap;

	वापस nic_cap->max_qps;
पूर्ण

/**
 * hinic_hwdev_num_qps - वापस the number QPs available क्रम use
 * @hwdev: the NIC HW device
 *
 * Return number QPs available क्रम use
 **/
पूर्णांक hinic_hwdev_num_qps(काष्ठा hinic_hwdev *hwdev)
अणु
	काष्ठा hinic_cap *nic_cap = &hwdev->nic_cap;

	वापस nic_cap->num_qps;
पूर्ण

/**
 * hinic_hwdev_get_sq - get SQ
 * @hwdev: the NIC HW device
 * @i: the position of the SQ
 *
 * Return: the SQ in the i position
 **/
काष्ठा hinic_sq *hinic_hwdev_get_sq(काष्ठा hinic_hwdev *hwdev, पूर्णांक i)
अणु
	काष्ठा hinic_func_to_io *func_to_io = &hwdev->func_to_io;
	काष्ठा hinic_qp *qp = &func_to_io->qps[i];

	अगर (i >= hinic_hwdev_num_qps(hwdev))
		वापस शून्य;

	वापस &qp->sq;
पूर्ण

/**
 * hinic_hwdev_get_sq - get RQ
 * @hwdev: the NIC HW device
 * @i: the position of the RQ
 *
 * Return: the RQ in the i position
 **/
काष्ठा hinic_rq *hinic_hwdev_get_rq(काष्ठा hinic_hwdev *hwdev, पूर्णांक i)
अणु
	काष्ठा hinic_func_to_io *func_to_io = &hwdev->func_to_io;
	काष्ठा hinic_qp *qp = &func_to_io->qps[i];

	अगर (i >= hinic_hwdev_num_qps(hwdev))
		वापस शून्य;

	वापस &qp->rq;
पूर्ण

/**
 * hinic_hwdev_msix_cnt_set - clear message attribute counters क्रम msix entry
 * @hwdev: the NIC HW device
 * @msix_index: msix_index
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_hwdev_msix_cnt_set(काष्ठा hinic_hwdev *hwdev, u16 msix_index)
अणु
	वापस hinic_msix_attr_cnt_clear(hwdev->hwअगर, msix_index);
पूर्ण

/**
 * hinic_hwdev_msix_set - set message attribute क्रम msix entry
 * @hwdev: the NIC HW device
 * @msix_index: msix_index
 * @pending_limit: the maximum pending पूर्णांकerrupt events (unit 8)
 * @coalesc_समयr: coalesc period क्रम पूर्णांकerrupt (unit 8 us)
 * @lli_समयr_cfg: replenishing period क्रम low latency credit (unit 8 us)
 * @lli_credit_limit: maximum credits क्रम low latency msix messages (unit 8)
 * @resend_समयr: maximum रुको क्रम resending msix (unit coalesc period)
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_hwdev_msix_set(काष्ठा hinic_hwdev *hwdev, u16 msix_index,
			 u8 pending_limit, u8 coalesc_समयr,
			 u8 lli_समयr_cfg, u8 lli_credit_limit,
			 u8 resend_समयr)
अणु
	वापस hinic_msix_attr_set(hwdev->hwअगर, msix_index,
				   pending_limit, coalesc_समयr,
				   lli_समयr_cfg, lli_credit_limit,
				   resend_समयr);
पूर्ण

/**
 * hinic_hwdev_hw_ci_addr_set - set cons idx addr and attributes in HW क्रम sq
 * @hwdev: the NIC HW device
 * @sq: send queue
 * @pending_limit: the maximum pending update ci events (unit 8)
 * @coalesc_समयr: coalesc period क्रम update ci (unit 8 us)
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_hwdev_hw_ci_addr_set(काष्ठा hinic_hwdev *hwdev, काष्ठा hinic_sq *sq,
			       u8 pending_limit, u8 coalesc_समयr)
अणु
	काष्ठा hinic_qp *qp = container_of(sq, काष्ठा hinic_qp, sq);
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा hinic_pfhwdev *pfhwdev;
	काष्ठा hinic_cmd_hw_ci hw_ci;

	hw_ci.dma_attr_off  = 0;
	hw_ci.pending_limit = pending_limit;
	hw_ci.coalesc_समयr = coalesc_समयr;

	hw_ci.msix_en = 1;
	hw_ci.msix_entry_idx = sq->msix_entry;

	hw_ci.func_idx = HINIC_HWIF_FUNC_IDX(hwअगर);

	hw_ci.sq_id = qp->q_id;

	hw_ci.ci_addr = ADDR_IN_4BYTES(sq->hw_ci_dma_addr);

	pfhwdev = container_of(hwdev, काष्ठा hinic_pfhwdev, hwdev);
	वापस hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt,
				 HINIC_MOD_COMM,
				 HINIC_COMM_CMD_SQ_HI_CI_SET,
				 &hw_ci, माप(hw_ci), शून्य,
				 शून्य, HINIC_MGMT_MSG_SYNC);
पूर्ण

/**
 * hinic_hwdev_set_msix_state- set msix state
 * @hwdev: the NIC HW device
 * @msix_index: IRQ corresponding index number
 * @flag: msix state
 *
 **/
व्योम hinic_hwdev_set_msix_state(काष्ठा hinic_hwdev *hwdev, u16 msix_index,
				क्रमागत hinic_msix_state flag)
अणु
	hinic_set_msix_state(hwdev->hwअगर, msix_index, flag);
पूर्ण

पूर्णांक hinic_get_board_info(काष्ठा hinic_hwdev *hwdev,
			 काष्ठा hinic_comm_board_info *board_info)
अणु
	u16 out_size = माप(*board_info);
	काष्ठा hinic_pfhwdev *pfhwdev;
	पूर्णांक err;

	अगर (!hwdev || !board_info)
		वापस -EINVAL;

	pfhwdev = container_of(hwdev, काष्ठा hinic_pfhwdev, hwdev);

	err = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
				HINIC_COMM_CMD_GET_BOARD_INFO,
				board_info, माप(*board_info),
				board_info, &out_size, HINIC_MGMT_MSG_SYNC);
	अगर (err || board_info->status || !out_size) अणु
		dev_err(&hwdev->hwअगर->pdev->dev,
			"Failed to get board info, err: %d, status: 0x%x, out size: 0x%x\n",
			err, board_info->status, out_size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण
