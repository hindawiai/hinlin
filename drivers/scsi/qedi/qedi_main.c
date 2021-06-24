<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic iSCSI Offload Driver
 * Copyright (c) 2016 Cavium Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/अगर_arp.h>
#समावेश <scsi/iscsi_अगर.h>
#समावेश <linux/inet.h>
#समावेश <net/arp.h>
#समावेश <linux/list.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mm.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/cpu.h>
#समावेश <linux/iscsi_boot_sysfs.h>

#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi.h>

#समावेश "qedi.h"
#समावेश "qedi_gbl.h"
#समावेश "qedi_iscsi.h"

अटल uपूर्णांक qedi_qed_debug;
module_param(qedi_qed_debug, uपूर्णांक, 0644);
MODULE_PARM_DESC(qedi_qed_debug, " QED debug level 0 (default)");

अटल uपूर्णांक qedi_fw_debug;
module_param(qedi_fw_debug, uपूर्णांक, 0644);
MODULE_PARM_DESC(qedi_fw_debug, " Firmware debug level 0(default) to 3");

uपूर्णांक qedi_dbg_log = QEDI_LOG_WARN | QEDI_LOG_SCSI_TM;
module_param(qedi_dbg_log, uपूर्णांक, 0644);
MODULE_PARM_DESC(qedi_dbg_log, " Default debug level");

uपूर्णांक qedi_io_tracing;
module_param(qedi_io_tracing, uपूर्णांक, 0644);
MODULE_PARM_DESC(qedi_io_tracing,
		 " Enable logging of SCSI requests/completions into trace buffer. (default off).");

अटल uपूर्णांक qedi_ll2_buf_size = 0x400;
module_param(qedi_ll2_buf_size, uपूर्णांक, 0644);
MODULE_PARM_DESC(qedi_ll2_buf_size,
		 "parameter to set ping packet size, default - 0x400, Jumbo packets - 0x2400.");

अटल uपूर्णांक qedi_flags_override;
module_param(qedi_flags_override, uपूर्णांक, 0644);
MODULE_PARM_DESC(qedi_flags_override, "Disable/Enable MFW error flags bits action.");

स्थिर काष्ठा qed_iscsi_ops *qedi_ops;
अटल काष्ठा scsi_transport_ढाँचा *qedi_scsi_transport;
अटल काष्ठा pci_driver qedi_pci_driver;
अटल DEFINE_PER_CPU(काष्ठा qedi_percpu_s, qedi_percpu);
अटल LIST_HEAD(qedi_udev_list);
/* Static function declaration */
अटल पूर्णांक qedi_alloc_global_queues(काष्ठा qedi_ctx *qedi);
अटल व्योम qedi_मुक्त_global_queues(काष्ठा qedi_ctx *qedi);
अटल काष्ठा qedi_cmd *qedi_get_cmd_from_tid(काष्ठा qedi_ctx *qedi, u32 tid);
अटल व्योम qedi_reset_uio_rings(काष्ठा qedi_uio_dev *udev);
अटल व्योम qedi_ll2_मुक्त_skbs(काष्ठा qedi_ctx *qedi);
अटल काष्ठा nvm_iscsi_block *qedi_get_nvram_block(काष्ठा qedi_ctx *qedi);
अटल व्योम qedi_recovery_handler(काष्ठा work_काष्ठा *work);
अटल व्योम qedi_schedule_hw_err_handler(व्योम *dev,
					 क्रमागत qed_hw_err_type err_type);

अटल पूर्णांक qedi_iscsi_event_cb(व्योम *context, u8 fw_event_code, व्योम *fw_handle)
अणु
	काष्ठा qedi_ctx *qedi;
	काष्ठा qedi_endpoपूर्णांक *qedi_ep;
	काष्ठा iscsi_eqe_data *data;
	पूर्णांक rval = 0;

	अगर (!context || !fw_handle) अणु
		QEDI_ERR(शून्य, "Recv event with ctx NULL\n");
		वापस -EINVAL;
	पूर्ण

	qedi = (काष्ठा qedi_ctx *)context;
	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
		  "Recv Event %d fw_handle %p\n", fw_event_code, fw_handle);

	data = (काष्ठा iscsi_eqe_data *)fw_handle;
	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
		  "icid=0x%x conn_id=0x%x err-code=0x%x error-pdu-opcode-reserved=0x%x\n",
		   data->icid, data->conn_id, data->error_code,
		   data->error_pdu_opcode_reserved);

	qedi_ep = qedi->ep_tbl[data->icid];

	अगर (!qedi_ep) अणु
		QEDI_WARN(&qedi->dbg_ctx,
			  "Cannot process event, ep already disconnected, cid=0x%x\n",
			   data->icid);
		WARN_ON(1);
		वापस -ENODEV;
	पूर्ण

	चयन (fw_event_code) अणु
	हाल ISCSI_EVENT_TYPE_ASYN_CONNECT_COMPLETE:
		अगर (qedi_ep->state == EP_STATE_OFLDCONN_START)
			qedi_ep->state = EP_STATE_OFLDCONN_COMPL;

		wake_up_पूर्णांकerruptible(&qedi_ep->tcp_ofld_रुको);
		अवरोध;
	हाल ISCSI_EVENT_TYPE_ASYN_TERMINATE_DONE:
		qedi_ep->state = EP_STATE_DISCONN_COMPL;
		wake_up_पूर्णांकerruptible(&qedi_ep->tcp_ofld_रुको);
		अवरोध;
	हाल ISCSI_EVENT_TYPE_ISCSI_CONN_ERROR:
		qedi_process_iscsi_error(qedi_ep, data);
		अवरोध;
	हाल ISCSI_EVENT_TYPE_ASYN_ABORT_RCVD:
	हाल ISCSI_EVENT_TYPE_ASYN_SYN_RCVD:
	हाल ISCSI_EVENT_TYPE_ASYN_MAX_RT_TIME:
	हाल ISCSI_EVENT_TYPE_ASYN_MAX_RT_CNT:
	हाल ISCSI_EVENT_TYPE_ASYN_MAX_KA_PROBES_CNT:
	हाल ISCSI_EVENT_TYPE_ASYN_FIN_WAIT2:
	हाल ISCSI_EVENT_TYPE_TCP_CONN_ERROR:
		qedi_process_tcp_error(qedi_ep, data);
		अवरोध;
	शेष:
		QEDI_ERR(&qedi->dbg_ctx, "Recv Unknown Event %u\n",
			 fw_event_code);
	पूर्ण

	वापस rval;
पूर्ण

अटल पूर्णांक qedi_uio_खोलो(काष्ठा uio_info *uinfo, काष्ठा inode *inode)
अणु
	काष्ठा qedi_uio_dev *udev = uinfo->priv;
	काष्ठा qedi_ctx *qedi = udev->qedi;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (udev->uio_dev != -1)
		वापस -EBUSY;

	rtnl_lock();
	udev->uio_dev = iminor(inode);
	qedi_reset_uio_rings(udev);
	set_bit(UIO_DEV_OPENED, &qedi->flags);
	rtnl_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक qedi_uio_बंद(काष्ठा uio_info *uinfo, काष्ठा inode *inode)
अणु
	काष्ठा qedi_uio_dev *udev = uinfo->priv;
	काष्ठा qedi_ctx *qedi = udev->qedi;

	udev->uio_dev = -1;
	clear_bit(UIO_DEV_OPENED, &qedi->flags);
	qedi_ll2_मुक्त_skbs(qedi);
	वापस 0;
पूर्ण

अटल व्योम __qedi_मुक्त_uio_rings(काष्ठा qedi_uio_dev *udev)
अणु
	अगर (udev->uctrl) अणु
		मुक्त_page((अचिन्हित दीर्घ)udev->uctrl);
		udev->uctrl = शून्य;
	पूर्ण

	अगर (udev->ll2_ring) अणु
		मुक्त_page((अचिन्हित दीर्घ)udev->ll2_ring);
		udev->ll2_ring = शून्य;
	पूर्ण

	अगर (udev->ll2_buf) अणु
		मुक्त_pages((अचिन्हित दीर्घ)udev->ll2_buf, 2);
		udev->ll2_buf = शून्य;
	पूर्ण
पूर्ण

अटल व्योम __qedi_मुक्त_uio(काष्ठा qedi_uio_dev *udev)
अणु
	uio_unरेजिस्टर_device(&udev->qedi_uinfo);

	__qedi_मुक्त_uio_rings(udev);

	pci_dev_put(udev->pdev);
	kमुक्त(udev);
पूर्ण

अटल व्योम qedi_मुक्त_uio(काष्ठा qedi_uio_dev *udev)
अणु
	अगर (!udev)
		वापस;

	list_del_init(&udev->list);
	__qedi_मुक्त_uio(udev);
पूर्ण

अटल व्योम qedi_reset_uio_rings(काष्ठा qedi_uio_dev *udev)
अणु
	काष्ठा qedi_ctx *qedi = शून्य;
	काष्ठा qedi_uio_ctrl *uctrl = शून्य;

	qedi = udev->qedi;
	uctrl = udev->uctrl;

	spin_lock_bh(&qedi->ll2_lock);
	uctrl->host_rx_cons = 0;
	uctrl->hw_rx_prod = 0;
	uctrl->hw_rx_bd_prod = 0;
	uctrl->host_rx_bd_cons = 0;

	स_रखो(udev->ll2_ring, 0, udev->ll2_ring_size);
	स_रखो(udev->ll2_buf, 0, udev->ll2_buf_size);
	spin_unlock_bh(&qedi->ll2_lock);
पूर्ण

अटल पूर्णांक __qedi_alloc_uio_rings(काष्ठा qedi_uio_dev *udev)
अणु
	पूर्णांक rc = 0;

	अगर (udev->ll2_ring || udev->ll2_buf)
		वापस rc;

	/* Memory क्रम control area.  */
	udev->uctrl = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!udev->uctrl)
		वापस -ENOMEM;

	/* Allocating memory क्रम LL2 ring  */
	udev->ll2_ring_size = QEDI_PAGE_SIZE;
	udev->ll2_ring = (व्योम *)get_zeroed_page(GFP_KERNEL | __GFP_COMP);
	अगर (!udev->ll2_ring) अणु
		rc = -ENOMEM;
		जाओ निकास_alloc_ring;
	पूर्ण

	/* Allocating memory क्रम Tx/Rx pkt buffer */
	udev->ll2_buf_size = TX_RX_RING * qedi_ll2_buf_size;
	udev->ll2_buf_size = QEDI_PAGE_ALIGN(udev->ll2_buf_size);
	udev->ll2_buf = (व्योम *)__get_मुक्त_pages(GFP_KERNEL | __GFP_COMP |
						 __GFP_ZERO, 2);
	अगर (!udev->ll2_buf) अणु
		rc = -ENOMEM;
		जाओ निकास_alloc_buf;
	पूर्ण
	वापस rc;

निकास_alloc_buf:
	मुक्त_page((अचिन्हित दीर्घ)udev->ll2_ring);
	udev->ll2_ring = शून्य;
निकास_alloc_ring:
	वापस rc;
पूर्ण

अटल पूर्णांक qedi_alloc_uio_rings(काष्ठा qedi_ctx *qedi)
अणु
	काष्ठा qedi_uio_dev *udev = शून्य;
	पूर्णांक rc = 0;

	list_क्रम_each_entry(udev, &qedi_udev_list, list) अणु
		अगर (udev->pdev == qedi->pdev) अणु
			udev->qedi = qedi;
			अगर (__qedi_alloc_uio_rings(udev)) अणु
				udev->qedi = शून्य;
				वापस -ENOMEM;
			पूर्ण
			qedi->udev = udev;
			वापस 0;
		पूर्ण
	पूर्ण

	udev = kzalloc(माप(*udev), GFP_KERNEL);
	अगर (!udev)
		जाओ err_udev;

	udev->uio_dev = -1;

	udev->qedi = qedi;
	udev->pdev = qedi->pdev;

	rc = __qedi_alloc_uio_rings(udev);
	अगर (rc)
		जाओ err_uctrl;

	list_add(&udev->list, &qedi_udev_list);

	pci_dev_get(udev->pdev);
	qedi->udev = udev;

	udev->tx_pkt = udev->ll2_buf;
	udev->rx_pkt = udev->ll2_buf + qedi_ll2_buf_size;
	वापस 0;

 err_uctrl:
	kमुक्त(udev);
 err_udev:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक qedi_init_uio(काष्ठा qedi_ctx *qedi)
अणु
	काष्ठा qedi_uio_dev *udev = qedi->udev;
	काष्ठा uio_info *uinfo;
	पूर्णांक ret = 0;

	अगर (!udev)
		वापस -ENOMEM;

	uinfo = &udev->qedi_uinfo;

	uinfo->mem[0].addr = (अचिन्हित दीर्घ)udev->uctrl;
	uinfo->mem[0].size = माप(काष्ठा qedi_uio_ctrl);
	uinfo->mem[0].memtype = UIO_MEM_LOGICAL;

	uinfo->mem[1].addr = (अचिन्हित दीर्घ)udev->ll2_ring;
	uinfo->mem[1].size = udev->ll2_ring_size;
	uinfo->mem[1].memtype = UIO_MEM_LOGICAL;

	uinfo->mem[2].addr = (अचिन्हित दीर्घ)udev->ll2_buf;
	uinfo->mem[2].size = udev->ll2_buf_size;
	uinfo->mem[2].memtype = UIO_MEM_LOGICAL;

	uinfo->name = "qedi_uio";
	uinfo->version = QEDI_MODULE_VERSION;
	uinfo->irq = UIO_IRQ_CUSTOM;

	uinfo->खोलो = qedi_uio_खोलो;
	uinfo->release = qedi_uio_बंद;

	अगर (udev->uio_dev == -1) अणु
		अगर (!uinfo->priv) अणु
			uinfo->priv = udev;

			ret = uio_रेजिस्टर_device(&udev->pdev->dev, uinfo);
			अगर (ret) अणु
				QEDI_ERR(&qedi->dbg_ctx,
					 "UIO registration failed\n");
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक qedi_alloc_and_init_sb(काष्ठा qedi_ctx *qedi,
				  काष्ठा qed_sb_info *sb_info, u16 sb_id)
अणु
	काष्ठा status_block_e4 *sb_virt;
	dma_addr_t sb_phys;
	पूर्णांक ret;

	sb_virt = dma_alloc_coherent(&qedi->pdev->dev,
				     माप(काष्ठा status_block_e4), &sb_phys,
				     GFP_KERNEL);
	अगर (!sb_virt) अणु
		QEDI_ERR(&qedi->dbg_ctx,
			 "Status block allocation failed for id = %d.\n",
			  sb_id);
		वापस -ENOMEM;
	पूर्ण

	ret = qedi_ops->common->sb_init(qedi->cdev, sb_info, sb_virt, sb_phys,
				       sb_id, QED_SB_TYPE_STORAGE);
	अगर (ret) अणु
		QEDI_ERR(&qedi->dbg_ctx,
			 "Status block initialization failed for id = %d.\n",
			  sb_id);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qedi_मुक्त_sb(काष्ठा qedi_ctx *qedi)
अणु
	काष्ठा qed_sb_info *sb_info;
	पूर्णांक id;

	क्रम (id = 0; id < MIN_NUM_CPUS_MSIX(qedi); id++) अणु
		sb_info = &qedi->sb_array[id];
		अगर (sb_info->sb_virt)
			dma_मुक्त_coherent(&qedi->pdev->dev,
					  माप(*sb_info->sb_virt),
					  (व्योम *)sb_info->sb_virt,
					  sb_info->sb_phys);
	पूर्ण
पूर्ण

अटल व्योम qedi_मुक्त_fp(काष्ठा qedi_ctx *qedi)
अणु
	kमुक्त(qedi->fp_array);
	kमुक्त(qedi->sb_array);
पूर्ण

अटल व्योम qedi_destroy_fp(काष्ठा qedi_ctx *qedi)
अणु
	qedi_मुक्त_sb(qedi);
	qedi_मुक्त_fp(qedi);
पूर्ण

अटल पूर्णांक qedi_alloc_fp(काष्ठा qedi_ctx *qedi)
अणु
	पूर्णांक ret = 0;

	qedi->fp_array = kसुस्मृति(MIN_NUM_CPUS_MSIX(qedi),
				 माप(काष्ठा qedi_fastpath), GFP_KERNEL);
	अगर (!qedi->fp_array) अणु
		QEDI_ERR(&qedi->dbg_ctx,
			 "fastpath fp array allocation failed.\n");
		वापस -ENOMEM;
	पूर्ण

	qedi->sb_array = kसुस्मृति(MIN_NUM_CPUS_MSIX(qedi),
				 माप(काष्ठा qed_sb_info), GFP_KERNEL);
	अगर (!qedi->sb_array) अणु
		QEDI_ERR(&qedi->dbg_ctx,
			 "fastpath sb array allocation failed.\n");
		ret = -ENOMEM;
		जाओ मुक्त_fp;
	पूर्ण

	वापस ret;

मुक्त_fp:
	qedi_मुक्त_fp(qedi);
	वापस ret;
पूर्ण

अटल व्योम qedi_पूर्णांक_fp(काष्ठा qedi_ctx *qedi)
अणु
	काष्ठा qedi_fastpath *fp;
	पूर्णांक id;

	स_रखो(qedi->fp_array, 0, MIN_NUM_CPUS_MSIX(qedi) *
	       माप(*qedi->fp_array));
	स_रखो(qedi->sb_array, 0, MIN_NUM_CPUS_MSIX(qedi) *
	       माप(*qedi->sb_array));

	क्रम (id = 0; id < MIN_NUM_CPUS_MSIX(qedi); id++) अणु
		fp = &qedi->fp_array[id];
		fp->sb_info = &qedi->sb_array[id];
		fp->sb_id = id;
		fp->qedi = qedi;
		snम_लिखो(fp->name, माप(fp->name), "%s-fp-%d",
			 "qedi", id);

		/* fp_array[i] ---- irq cookie
		 * So init data which is needed in पूर्णांक ctx
		 */
	पूर्ण
पूर्ण

अटल पूर्णांक qedi_prepare_fp(काष्ठा qedi_ctx *qedi)
अणु
	काष्ठा qedi_fastpath *fp;
	पूर्णांक id, ret = 0;

	ret = qedi_alloc_fp(qedi);
	अगर (ret)
		जाओ err;

	qedi_पूर्णांक_fp(qedi);

	क्रम (id = 0; id < MIN_NUM_CPUS_MSIX(qedi); id++) अणु
		fp = &qedi->fp_array[id];
		ret = qedi_alloc_and_init_sb(qedi, fp->sb_info, fp->sb_id);
		अगर (ret) अणु
			QEDI_ERR(&qedi->dbg_ctx,
				 "SB allocation and initialization failed.\n");
			ret = -EIO;
			जाओ err_init;
		पूर्ण
	पूर्ण

	वापस 0;

err_init:
	qedi_मुक्त_sb(qedi);
	qedi_मुक्त_fp(qedi);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक qedi_setup_cid_que(काष्ठा qedi_ctx *qedi)
अणु
	पूर्णांक i;

	qedi->cid_que.cid_que_base = kदो_स्मृति_array(qedi->max_active_conns,
						   माप(u32), GFP_KERNEL);
	अगर (!qedi->cid_que.cid_que_base)
		वापस -ENOMEM;

	qedi->cid_que.conn_cid_tbl = kदो_स्मृति_array(qedi->max_active_conns,
						   माप(काष्ठा qedi_conn *),
						   GFP_KERNEL);
	अगर (!qedi->cid_que.conn_cid_tbl) अणु
		kमुक्त(qedi->cid_que.cid_que_base);
		qedi->cid_que.cid_que_base = शून्य;
		वापस -ENOMEM;
	पूर्ण

	qedi->cid_que.cid_que = (u32 *)qedi->cid_que.cid_que_base;
	qedi->cid_que.cid_q_prod_idx = 0;
	qedi->cid_que.cid_q_cons_idx = 0;
	qedi->cid_que.cid_q_max_idx = qedi->max_active_conns;
	qedi->cid_que.cid_मुक्त_cnt = qedi->max_active_conns;

	क्रम (i = 0; i < qedi->max_active_conns; i++) अणु
		qedi->cid_que.cid_que[i] = i;
		qedi->cid_que.conn_cid_tbl[i] = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qedi_release_cid_que(काष्ठा qedi_ctx *qedi)
अणु
	kमुक्त(qedi->cid_que.cid_que_base);
	qedi->cid_que.cid_que_base = शून्य;

	kमुक्त(qedi->cid_que.conn_cid_tbl);
	qedi->cid_que.conn_cid_tbl = शून्य;
पूर्ण

अटल पूर्णांक qedi_init_id_tbl(काष्ठा qedi_portid_tbl *id_tbl, u16 size,
			    u16 start_id, u16 next)
अणु
	id_tbl->start = start_id;
	id_tbl->max = size;
	id_tbl->next = next;
	spin_lock_init(&id_tbl->lock);
	id_tbl->table = kसुस्मृति(BITS_TO_LONGS(size), माप(दीर्घ), GFP_KERNEL);
	अगर (!id_tbl->table)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम qedi_मुक्त_id_tbl(काष्ठा qedi_portid_tbl *id_tbl)
अणु
	kमुक्त(id_tbl->table);
	id_tbl->table = शून्य;
पूर्ण

पूर्णांक qedi_alloc_id(काष्ठा qedi_portid_tbl *id_tbl, u16 id)
अणु
	पूर्णांक ret = -1;

	id -= id_tbl->start;
	अगर (id >= id_tbl->max)
		वापस ret;

	spin_lock(&id_tbl->lock);
	अगर (!test_bit(id, id_tbl->table)) अणु
		set_bit(id, id_tbl->table);
		ret = 0;
	पूर्ण
	spin_unlock(&id_tbl->lock);
	वापस ret;
पूर्ण

u16 qedi_alloc_new_id(काष्ठा qedi_portid_tbl *id_tbl)
अणु
	u16 id;

	spin_lock(&id_tbl->lock);
	id = find_next_zero_bit(id_tbl->table, id_tbl->max, id_tbl->next);
	अगर (id >= id_tbl->max) अणु
		id = QEDI_LOCAL_PORT_INVALID;
		अगर (id_tbl->next != 0) अणु
			id = find_first_zero_bit(id_tbl->table, id_tbl->next);
			अगर (id >= id_tbl->next)
				id = QEDI_LOCAL_PORT_INVALID;
		पूर्ण
	पूर्ण

	अगर (id < id_tbl->max) अणु
		set_bit(id, id_tbl->table);
		id_tbl->next = (id + 1) & (id_tbl->max - 1);
		id += id_tbl->start;
	पूर्ण

	spin_unlock(&id_tbl->lock);

	वापस id;
पूर्ण

व्योम qedi_मुक्त_id(काष्ठा qedi_portid_tbl *id_tbl, u16 id)
अणु
	अगर (id == QEDI_LOCAL_PORT_INVALID)
		वापस;

	id -= id_tbl->start;
	अगर (id >= id_tbl->max)
		वापस;

	clear_bit(id, id_tbl->table);
पूर्ण

अटल व्योम qedi_cm_मुक्त_mem(काष्ठा qedi_ctx *qedi)
अणु
	kमुक्त(qedi->ep_tbl);
	qedi->ep_tbl = शून्य;
	qedi_मुक्त_id_tbl(&qedi->lcl_port_tbl);
पूर्ण

अटल पूर्णांक qedi_cm_alloc_mem(काष्ठा qedi_ctx *qedi)
अणु
	u16 port_id;

	qedi->ep_tbl = kzalloc((qedi->max_active_conns *
				माप(काष्ठा qedi_endpoपूर्णांक *)), GFP_KERNEL);
	अगर (!qedi->ep_tbl)
		वापस -ENOMEM;
	port_id = pअक्रमom_u32() % QEDI_LOCAL_PORT_RANGE;
	अगर (qedi_init_id_tbl(&qedi->lcl_port_tbl, QEDI_LOCAL_PORT_RANGE,
			     QEDI_LOCAL_PORT_MIN, port_id)) अणु
		qedi_cm_मुक्त_mem(qedi);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा qedi_ctx *qedi_host_alloc(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा qedi_ctx *qedi = शून्य;

	shost = iscsi_host_alloc(&qedi_host_ढाँचा,
				 माप(काष्ठा qedi_ctx), 0);
	अगर (!shost) अणु
		QEDI_ERR(शून्य, "Could not allocate shost\n");
		जाओ निकास_setup_shost;
	पूर्ण

	shost->max_id = QEDI_MAX_ISCSI_CONNS_PER_HBA;
	shost->max_channel = 0;
	shost->max_lun = ~0;
	shost->max_cmd_len = 16;
	shost->transportt = qedi_scsi_transport;

	qedi = iscsi_host_priv(shost);
	स_रखो(qedi, 0, माप(*qedi));
	qedi->shost = shost;
	qedi->dbg_ctx.host_no = shost->host_no;
	qedi->pdev = pdev;
	qedi->dbg_ctx.pdev = pdev;
	qedi->max_active_conns = ISCSI_MAX_SESS_PER_HBA;
	qedi->max_sqes = QEDI_SQ_SIZE;

	shost->nr_hw_queues = MIN_NUM_CPUS_MSIX(qedi);

	pci_set_drvdata(pdev, qedi);

निकास_setup_shost:
	वापस qedi;
पूर्ण

अटल पूर्णांक qedi_ll2_rx(व्योम *cookie, काष्ठा sk_buff *skb, u32 arg1, u32 arg2)
अणु
	काष्ठा qedi_ctx *qedi = (काष्ठा qedi_ctx *)cookie;
	काष्ठा skb_work_list *work;
	काष्ठा ethhdr *eh;

	अगर (!qedi) अणु
		QEDI_ERR(शून्य, "qedi is NULL\n");
		वापस -1;
	पूर्ण

	अगर (!test_bit(UIO_DEV_OPENED, &qedi->flags)) अणु
		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_UIO,
			  "UIO DEV is not opened\n");
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	eh = (काष्ठा ethhdr *)skb->data;
	/* Unकरो VLAN encapsulation */
	अगर (eh->h_proto == htons(ETH_P_8021Q)) अणु
		स_हटाओ((u8 *)eh + VLAN_HLEN, eh, ETH_ALEN * 2);
		eh = (काष्ठा ethhdr *)skb_pull(skb, VLAN_HLEN);
		skb_reset_mac_header(skb);
	पूर्ण

	/* Filter out non FIP/FCoE frames here to मुक्त them faster */
	अगर (eh->h_proto != htons(ETH_P_ARP) &&
	    eh->h_proto != htons(ETH_P_IP) &&
	    eh->h_proto != htons(ETH_P_IPV6)) अणु
		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_LL2,
			  "Dropping frame ethertype [0x%x] len [0x%x].\n",
			  eh->h_proto, skb->len);
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_LL2,
		  "Allowed frame ethertype [0x%x] len [0x%x].\n",
		  eh->h_proto, skb->len);

	work = kzalloc(माप(*work), GFP_ATOMIC);
	अगर (!work) अणु
		QEDI_WARN(&qedi->dbg_ctx,
			  "Could not allocate work so dropping frame.\n");
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	INIT_LIST_HEAD(&work->list);
	work->skb = skb;

	अगर (skb_vlan_tag_present(skb))
		work->vlan_id = skb_vlan_tag_get(skb);

	अगर (work->vlan_id)
		__vlan_insert_tag(work->skb, htons(ETH_P_8021Q), work->vlan_id);

	spin_lock_bh(&qedi->ll2_lock);
	list_add_tail(&work->list, &qedi->ll2_skb_list);
	spin_unlock_bh(&qedi->ll2_lock);

	wake_up_process(qedi->ll2_recv_thपढ़ो);

	वापस 0;
पूर्ण

/* map this skb to iscsiuio mmaped region */
अटल पूर्णांक qedi_ll2_process_skb(काष्ठा qedi_ctx *qedi, काष्ठा sk_buff *skb,
				u16 vlan_id)
अणु
	काष्ठा qedi_uio_dev *udev = शून्य;
	काष्ठा qedi_uio_ctrl *uctrl = शून्य;
	काष्ठा qedi_rx_bd rxbd;
	काष्ठा qedi_rx_bd *p_rxbd;
	u32 rx_bd_prod;
	व्योम *pkt;
	पूर्णांक len = 0;
	u32 prod;

	अगर (!qedi) अणु
		QEDI_ERR(शून्य, "qedi is NULL\n");
		वापस -1;
	पूर्ण

	udev = qedi->udev;
	uctrl = udev->uctrl;

	++uctrl->hw_rx_prod_cnt;
	prod = (uctrl->hw_rx_prod + 1) % RX_RING;

	pkt = udev->rx_pkt + (prod * qedi_ll2_buf_size);
	len = min_t(u32, skb->len, (u32)qedi_ll2_buf_size);
	स_नकल(pkt, skb->data, len);

	स_रखो(&rxbd, 0, माप(rxbd));
	rxbd.rx_pkt_index = prod;
	rxbd.rx_pkt_len = len;
	rxbd.vlan_id = vlan_id;

	uctrl->hw_rx_bd_prod = (uctrl->hw_rx_bd_prod + 1) % QEDI_NUM_RX_BD;
	rx_bd_prod = uctrl->hw_rx_bd_prod;
	p_rxbd = (काष्ठा qedi_rx_bd *)udev->ll2_ring;
	p_rxbd += rx_bd_prod;

	स_नकल(p_rxbd, &rxbd, माप(rxbd));

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_LL2,
		  "hw_rx_prod [%d] prod [%d] hw_rx_bd_prod [%d] rx_pkt_idx [%d] rx_len [%d].\n",
		  uctrl->hw_rx_prod, prod, uctrl->hw_rx_bd_prod,
		  rxbd.rx_pkt_index, rxbd.rx_pkt_len);
	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_LL2,
		  "host_rx_cons [%d] hw_rx_bd_cons [%d].\n",
		  uctrl->host_rx_cons, uctrl->host_rx_bd_cons);

	uctrl->hw_rx_prod = prod;

	/* notअगरy the iscsiuio about new packet */
	uio_event_notअगरy(&udev->qedi_uinfo);

	वापस 0;
पूर्ण

अटल व्योम qedi_ll2_मुक्त_skbs(काष्ठा qedi_ctx *qedi)
अणु
	काष्ठा skb_work_list *work, *work_पंचांगp;

	spin_lock_bh(&qedi->ll2_lock);
	list_क्रम_each_entry_safe(work, work_पंचांगp, &qedi->ll2_skb_list, list) अणु
		list_del(&work->list);
		kमुक्त_skb(work->skb);
		kमुक्त(work);
	पूर्ण
	spin_unlock_bh(&qedi->ll2_lock);
पूर्ण

अटल पूर्णांक qedi_ll2_recv_thपढ़ो(व्योम *arg)
अणु
	काष्ठा qedi_ctx *qedi = (काष्ठा qedi_ctx *)arg;
	काष्ठा skb_work_list *work, *work_पंचांगp;

	set_user_nice(current, -20);

	जबतक (!kthपढ़ो_should_stop()) अणु
		spin_lock_bh(&qedi->ll2_lock);
		list_क्रम_each_entry_safe(work, work_पंचांगp, &qedi->ll2_skb_list,
					 list) अणु
			list_del(&work->list);
			qedi_ll2_process_skb(qedi, work->skb, work->vlan_id);
			kमुक्त_skb(work->skb);
			kमुक्त(work);
		पूर्ण
		set_current_state(TASK_INTERRUPTIBLE);
		spin_unlock_bh(&qedi->ll2_lock);
		schedule();
	पूर्ण

	__set_current_state(TASK_RUNNING);
	वापस 0;
पूर्ण

अटल पूर्णांक qedi_set_iscsi_pf_param(काष्ठा qedi_ctx *qedi)
अणु
	u8 num_sq_pages;
	u32 log_page_size;
	पूर्णांक rval = 0;


	num_sq_pages = (MAX_OUTSTANDING_TASKS_PER_CON * 8) / QEDI_PAGE_SIZE;

	qedi->num_queues = MIN_NUM_CPUS_MSIX(qedi);

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
		  "Number of CQ count is %d\n", qedi->num_queues);

	स_रखो(&qedi->pf_params.iscsi_pf_params, 0,
	       माप(qedi->pf_params.iscsi_pf_params));

	qedi->p_cpuq = dma_alloc_coherent(&qedi->pdev->dev,
			qedi->num_queues * माप(काष्ठा qedi_glbl_q_params),
			&qedi->hw_p_cpuq, GFP_KERNEL);
	अगर (!qedi->p_cpuq) अणु
		QEDI_ERR(&qedi->dbg_ctx, "dma_alloc_coherent fail\n");
		rval = -1;
		जाओ err_alloc_mem;
	पूर्ण

	rval = qedi_alloc_global_queues(qedi);
	अगर (rval) अणु
		QEDI_ERR(&qedi->dbg_ctx, "Global queue allocation failed.\n");
		rval = -1;
		जाओ err_alloc_mem;
	पूर्ण

	qedi->pf_params.iscsi_pf_params.num_cons = QEDI_MAX_ISCSI_CONNS_PER_HBA;
	qedi->pf_params.iscsi_pf_params.num_tasks = QEDI_MAX_ISCSI_TASK;
	qedi->pf_params.iscsi_pf_params.half_way_बंद_समयout = 10;
	qedi->pf_params.iscsi_pf_params.num_sq_pages_in_ring = num_sq_pages;
	qedi->pf_params.iscsi_pf_params.num_r2tq_pages_in_ring = num_sq_pages;
	qedi->pf_params.iscsi_pf_params.num_uhq_pages_in_ring = num_sq_pages;
	qedi->pf_params.iscsi_pf_params.num_queues = qedi->num_queues;
	qedi->pf_params.iscsi_pf_params.debug_mode = qedi_fw_debug;
	qedi->pf_params.iscsi_pf_params.two_msl_समयr = 4000;
	qedi->pf_params.iscsi_pf_params.max_fin_rt = 2;

	क्रम (log_page_size = 0 ; log_page_size < 32 ; log_page_size++) अणु
		अगर ((1 << log_page_size) == QEDI_PAGE_SIZE)
			अवरोध;
	पूर्ण
	qedi->pf_params.iscsi_pf_params.log_page_size = log_page_size;

	qedi->pf_params.iscsi_pf_params.glbl_q_params_addr =
							   (u64)qedi->hw_p_cpuq;

	/* RQ BDQ initializations.
	 * rq_num_entries: suggested value क्रम Initiator is 16 (4KB RQ)
	 * rqe_log_size: 8 क्रम 256B RQE
	 */
	qedi->pf_params.iscsi_pf_params.rqe_log_size = 8;
	/* BDQ address and size */
	qedi->pf_params.iscsi_pf_params.bdq_pbl_base_addr[BDQ_ID_RQ] =
							qedi->bdq_pbl_list_dma;
	qedi->pf_params.iscsi_pf_params.bdq_pbl_num_entries[BDQ_ID_RQ] =
						qedi->bdq_pbl_list_num_entries;
	qedi->pf_params.iscsi_pf_params.rq_buffer_size = QEDI_BDQ_BUF_SIZE;

	/* cq_num_entries: num_tasks + rq_num_entries */
	qedi->pf_params.iscsi_pf_params.cq_num_entries = 2048;

	qedi->pf_params.iscsi_pf_params.gl_rq_pi = QEDI_PROTO_CQ_PROD_IDX;
	qedi->pf_params.iscsi_pf_params.gl_cmd_pi = 1;

err_alloc_mem:
	वापस rval;
पूर्ण

/* Free DMA coherent memory क्रम array of queue poपूर्णांकers we pass to qed */
अटल व्योम qedi_मुक्त_iscsi_pf_param(काष्ठा qedi_ctx *qedi)
अणु
	माप_प्रकार size = 0;

	अगर (qedi->p_cpuq) अणु
		size = qedi->num_queues * माप(काष्ठा qedi_glbl_q_params);
		dma_मुक्त_coherent(&qedi->pdev->dev, size, qedi->p_cpuq,
				    qedi->hw_p_cpuq);
	पूर्ण

	qedi_मुक्त_global_queues(qedi);

	kमुक्त(qedi->global_queues);
पूर्ण

अटल व्योम qedi_get_boot_tgt_info(काष्ठा nvm_iscsi_block *block,
				   काष्ठा qedi_boot_target *tgt, u8 index)
अणु
	u32 ipv6_en;

	ipv6_en = !!(block->generic.ctrl_flags &
		     NVM_ISCSI_CFG_GEN_IPV6_ENABLED);

	snम_लिखो(tgt->iscsi_name, माप(tgt->iscsi_name), "%s",
		 block->target[index].target_name.byte);

	tgt->ipv6_en = ipv6_en;

	अगर (ipv6_en)
		snम_लिखो(tgt->ip_addr, IPV6_LEN, "%pI6\n",
			 block->target[index].ipv6_addr.byte);
	अन्यथा
		snम_लिखो(tgt->ip_addr, IPV4_LEN, "%pI4\n",
			 block->target[index].ipv4_addr.byte);
पूर्ण

अटल पूर्णांक qedi_find_boot_info(काष्ठा qedi_ctx *qedi,
			       काष्ठा qed_mfw_tlv_iscsi *iscsi,
			       काष्ठा nvm_iscsi_block *block)
अणु
	काष्ठा qedi_boot_target *pri_tgt = शून्य, *sec_tgt = शून्य;
	u32 pri_ctrl_flags = 0, sec_ctrl_flags = 0, found = 0;
	काष्ठा iscsi_cls_session *cls_sess;
	काष्ठा iscsi_cls_conn *cls_conn;
	काष्ठा qedi_conn *qedi_conn;
	काष्ठा iscsi_session *sess;
	काष्ठा iscsi_conn *conn;
	अक्षर ep_ip_addr[64];
	पूर्णांक i, ret = 0;

	pri_ctrl_flags = !!(block->target[0].ctrl_flags &
					NVM_ISCSI_CFG_TARGET_ENABLED);
	अगर (pri_ctrl_flags) अणु
		pri_tgt = kzalloc(माप(*pri_tgt), GFP_KERNEL);
		अगर (!pri_tgt)
			वापस -1;
		qedi_get_boot_tgt_info(block, pri_tgt, 0);
	पूर्ण

	sec_ctrl_flags = !!(block->target[1].ctrl_flags &
					NVM_ISCSI_CFG_TARGET_ENABLED);
	अगर (sec_ctrl_flags) अणु
		sec_tgt = kzalloc(माप(*sec_tgt), GFP_KERNEL);
		अगर (!sec_tgt) अणु
			ret = -1;
			जाओ मुक्त_tgt;
		पूर्ण
		qedi_get_boot_tgt_info(block, sec_tgt, 1);
	पूर्ण

	क्रम (i = 0; i < qedi->max_active_conns; i++) अणु
		qedi_conn = qedi_get_conn_from_id(qedi, i);
		अगर (!qedi_conn)
			जारी;

		अगर (qedi_conn->ep->ip_type == TCP_IPV4)
			snम_लिखो(ep_ip_addr, IPV4_LEN, "%pI4\n",
				 qedi_conn->ep->dst_addr);
		अन्यथा
			snम_लिखो(ep_ip_addr, IPV6_LEN, "%pI6\n",
				 qedi_conn->ep->dst_addr);

		cls_conn = qedi_conn->cls_conn;
		conn = cls_conn->dd_data;
		cls_sess = iscsi_conn_to_session(cls_conn);
		sess = cls_sess->dd_data;

		अगर (!iscsi_is_session_online(cls_sess))
			जारी;

		अगर (!sess->targetname)
			जारी;

		अगर (pri_ctrl_flags) अणु
			अगर (!म_भेद(pri_tgt->iscsi_name, sess->targetname) &&
			    !म_भेद(pri_tgt->ip_addr, ep_ip_addr)) अणु
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (sec_ctrl_flags) अणु
			अगर (!म_भेद(sec_tgt->iscsi_name, sess->targetname) &&
			    !म_भेद(sec_tgt->ip_addr, ep_ip_addr)) अणु
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (found) अणु
		अगर (conn->hdrdgst_en) अणु
			iscsi->header_digest_set = true;
			iscsi->header_digest = 1;
		पूर्ण

		अगर (conn->datadgst_en) अणु
			iscsi->data_digest_set = true;
			iscsi->data_digest = 1;
		पूर्ण
		iscsi->boot_taget_portal_set = true;
		iscsi->boot_taget_portal = sess->tpgt;

	पूर्ण अन्यथा अणु
		ret = -1;
	पूर्ण

	अगर (sec_ctrl_flags)
		kमुक्त(sec_tgt);
मुक्त_tgt:
	अगर (pri_ctrl_flags)
		kमुक्त(pri_tgt);

	वापस ret;
पूर्ण

अटल व्योम qedi_get_generic_tlv_data(व्योम *dev, काष्ठा qed_generic_tlvs *data)
अणु
	काष्ठा qedi_ctx *qedi;

	अगर (!dev) अणु
		QEDI_INFO(शून्य, QEDI_LOG_EVT,
			  "dev is NULL so ignoring get_generic_tlv_data request.\n");
		वापस;
	पूर्ण
	qedi = (काष्ठा qedi_ctx *)dev;

	स_रखो(data, 0, माप(काष्ठा qed_generic_tlvs));
	ether_addr_copy(data->mac[0], qedi->mac);
पूर्ण

/*
 * Protocol TLV handler
 */
अटल व्योम qedi_get_protocol_tlv_data(व्योम *dev, व्योम *data)
अणु
	काष्ठा qed_mfw_tlv_iscsi *iscsi = data;
	काष्ठा qed_iscsi_stats *fw_iscsi_stats;
	काष्ठा nvm_iscsi_block *block = शून्य;
	u32 chap_en = 0, mchap_en = 0;
	काष्ठा qedi_ctx *qedi = dev;
	पूर्णांक rval = 0;

	fw_iscsi_stats = kदो_स्मृति(माप(*fw_iscsi_stats), GFP_KERNEL);
	अगर (!fw_iscsi_stats) अणु
		QEDI_ERR(&qedi->dbg_ctx,
			 "Could not allocate memory for fw_iscsi_stats.\n");
		जाओ निकास_get_data;
	पूर्ण

	mutex_lock(&qedi->stats_lock);
	/* Query firmware क्रम offload stats */
	qedi_ops->get_stats(qedi->cdev, fw_iscsi_stats);
	mutex_unlock(&qedi->stats_lock);

	iscsi->rx_frames_set = true;
	iscsi->rx_frames = fw_iscsi_stats->iscsi_rx_packet_cnt;
	iscsi->rx_bytes_set = true;
	iscsi->rx_bytes = fw_iscsi_stats->iscsi_rx_bytes_cnt;
	iscsi->tx_frames_set = true;
	iscsi->tx_frames = fw_iscsi_stats->iscsi_tx_packet_cnt;
	iscsi->tx_bytes_set = true;
	iscsi->tx_bytes = fw_iscsi_stats->iscsi_tx_bytes_cnt;
	iscsi->frame_size_set = true;
	iscsi->frame_size = qedi->ll2_mtu;
	block = qedi_get_nvram_block(qedi);
	अगर (block) अणु
		chap_en = !!(block->generic.ctrl_flags &
			     NVM_ISCSI_CFG_GEN_CHAP_ENABLED);
		mchap_en = !!(block->generic.ctrl_flags &
			      NVM_ISCSI_CFG_GEN_CHAP_MUTUAL_ENABLED);

		iscsi->auth_method_set = (chap_en || mchap_en) ? true : false;
		iscsi->auth_method = 1;
		अगर (chap_en)
			iscsi->auth_method = 2;
		अगर (mchap_en)
			iscsi->auth_method = 3;

		iscsi->tx_desc_size_set = true;
		iscsi->tx_desc_size = QEDI_SQ_SIZE;
		iscsi->rx_desc_size_set = true;
		iscsi->rx_desc_size = QEDI_CQ_SIZE;

		/* tpgt, hdr digest, data digest */
		rval = qedi_find_boot_info(qedi, iscsi, block);
		अगर (rval)
			QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
				  "Boot target not set");
	पूर्ण

	kमुक्त(fw_iscsi_stats);
निकास_get_data:
	वापस;
पूर्ण

व्योम qedi_schedule_hw_err_handler(व्योम *dev,
				  क्रमागत qed_hw_err_type err_type)
अणु
	काष्ठा qedi_ctx *qedi = (काष्ठा qedi_ctx *)dev;
	अचिन्हित दीर्घ override_flags = qedi_flags_override;

	अगर (override_flags && test_bit(QEDI_ERR_OVERRIDE_EN, &override_flags))
		qedi->qedi_err_flags = qedi_flags_override;

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
		  "HW error handler scheduled, err=%d err_flags=0x%x\n",
		  err_type, qedi->qedi_err_flags);

	चयन (err_type) अणु
	हाल QED_HW_ERR_FAN_FAIL:
		schedule_delayed_work(&qedi->board_disable_work, 0);
		अवरोध;
	हाल QED_HW_ERR_MFW_RESP_FAIL:
	हाल QED_HW_ERR_HW_ATTN:
	हाल QED_HW_ERR_DMAE_FAIL:
	हाल QED_HW_ERR_RAMROD_FAIL:
	हाल QED_HW_ERR_FW_ASSERT:
		/* Prevent HW attentions from being reनिश्चितed */
		अगर (test_bit(QEDI_ERR_ATTN_CLR_EN, &qedi->qedi_err_flags))
			qedi_ops->common->attn_clr_enable(qedi->cdev, true);

		अगर (err_type == QED_HW_ERR_RAMROD_FAIL &&
		    test_bit(QEDI_ERR_IS_RECOVERABLE, &qedi->qedi_err_flags))
			qedi_ops->common->recovery_process(qedi->cdev);

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम qedi_schedule_recovery_handler(व्योम *dev)
अणु
	काष्ठा qedi_ctx *qedi = dev;

	QEDI_ERR(&qedi->dbg_ctx, "Recovery handler scheduled.\n");

	अगर (test_and_set_bit(QEDI_IN_RECOVERY, &qedi->flags))
		वापस;

	atomic_set(&qedi->link_state, QEDI_LINK_DOWN);

	schedule_delayed_work(&qedi->recovery_work, 0);
पूर्ण

अटल व्योम qedi_set_conn_recovery(काष्ठा iscsi_cls_session *cls_session)
अणु
	काष्ठा iscsi_session *session = cls_session->dd_data;
	काष्ठा iscsi_conn *conn = session->leadconn;
	काष्ठा qedi_conn *qedi_conn = conn->dd_data;

	qedi_start_conn_recovery(qedi_conn->qedi, qedi_conn);
पूर्ण

अटल व्योम qedi_link_update(व्योम *dev, काष्ठा qed_link_output *link)
अणु
	काष्ठा qedi_ctx *qedi = (काष्ठा qedi_ctx *)dev;

	अगर (link->link_up) अणु
		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO, "Link Up event.\n");
		atomic_set(&qedi->link_state, QEDI_LINK_UP);
	पूर्ण अन्यथा अणु
		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
			  "Link Down event.\n");
		atomic_set(&qedi->link_state, QEDI_LINK_DOWN);
		iscsi_host_क्रम_each_session(qedi->shost, qedi_set_conn_recovery);
	पूर्ण
पूर्ण

अटल काष्ठा qed_iscsi_cb_ops qedi_cb_ops = अणु
	अणु
		.link_update =		qedi_link_update,
		.schedule_recovery_handler = qedi_schedule_recovery_handler,
		.schedule_hw_err_handler = qedi_schedule_hw_err_handler,
		.get_protocol_tlv_data = qedi_get_protocol_tlv_data,
		.get_generic_tlv_data = qedi_get_generic_tlv_data,
	पूर्ण
पूर्ण;

अटल पूर्णांक qedi_queue_cqe(काष्ठा qedi_ctx *qedi, जोड़ iscsi_cqe *cqe,
			  u16 que_idx, काष्ठा qedi_percpu_s *p)
अणु
	काष्ठा qedi_work *qedi_work;
	काष्ठा qedi_conn *q_conn;
	काष्ठा qedi_cmd *qedi_cmd;
	u32 iscsi_cid;
	पूर्णांक rc = 0;

	iscsi_cid  = cqe->cqe_common.conn_id;
	q_conn = qedi->cid_que.conn_cid_tbl[iscsi_cid];
	अगर (!q_conn) अणु
		QEDI_WARN(&qedi->dbg_ctx,
			  "Session no longer exists for cid=0x%x!!\n",
			  iscsi_cid);
		वापस -1;
	पूर्ण

	चयन (cqe->cqe_common.cqe_type) अणु
	हाल ISCSI_CQE_TYPE_SOLICITED:
	हाल ISCSI_CQE_TYPE_SOLICITED_WITH_SENSE:
		qedi_cmd = qedi_get_cmd_from_tid(qedi, cqe->cqe_solicited.itid);
		अगर (!qedi_cmd) अणु
			rc = -1;
			अवरोध;
		पूर्ण
		INIT_LIST_HEAD(&qedi_cmd->cqe_work.list);
		qedi_cmd->cqe_work.qedi = qedi;
		स_नकल(&qedi_cmd->cqe_work.cqe, cqe, माप(जोड़ iscsi_cqe));
		qedi_cmd->cqe_work.que_idx = que_idx;
		qedi_cmd->cqe_work.is_solicited = true;
		list_add_tail(&qedi_cmd->cqe_work.list, &p->work_list);
		अवरोध;
	हाल ISCSI_CQE_TYPE_UNSOLICITED:
	हाल ISCSI_CQE_TYPE_DUMMY:
	हाल ISCSI_CQE_TYPE_TASK_CLEANUP:
		qedi_work = kzalloc(माप(*qedi_work), GFP_ATOMIC);
		अगर (!qedi_work) अणु
			rc = -1;
			अवरोध;
		पूर्ण
		INIT_LIST_HEAD(&qedi_work->list);
		qedi_work->qedi = qedi;
		स_नकल(&qedi_work->cqe, cqe, माप(जोड़ iscsi_cqe));
		qedi_work->que_idx = que_idx;
		qedi_work->is_solicited = false;
		list_add_tail(&qedi_work->list, &p->work_list);
		अवरोध;
	शेष:
		rc = -1;
		QEDI_ERR(&qedi->dbg_ctx, "FW Error cqe.\n");
	पूर्ण
	वापस rc;
पूर्ण

अटल bool qedi_process_completions(काष्ठा qedi_fastpath *fp)
अणु
	काष्ठा qedi_ctx *qedi = fp->qedi;
	काष्ठा qed_sb_info *sb_info = fp->sb_info;
	काष्ठा status_block_e4 *sb = sb_info->sb_virt;
	काष्ठा qedi_percpu_s *p = शून्य;
	काष्ठा global_queue *que;
	u16 prod_idx;
	अचिन्हित दीर्घ flags;
	जोड़ iscsi_cqe *cqe;
	पूर्णांक cpu;
	पूर्णांक ret;

	/* Get the current firmware producer index */
	prod_idx = sb->pi_array[QEDI_PROTO_CQ_PROD_IDX];

	अगर (prod_idx >= QEDI_CQ_SIZE)
		prod_idx = prod_idx % QEDI_CQ_SIZE;

	que = qedi->global_queues[fp->sb_id];
	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_IO,
		  "Before: global queue=%p prod_idx=%d cons_idx=%d, sb_id=%d\n",
		  que, prod_idx, que->cq_cons_idx, fp->sb_id);

	qedi->पूर्णांकr_cpu = fp->sb_id;
	cpu = smp_processor_id();
	p = &per_cpu(qedi_percpu, cpu);

	अगर (unlikely(!p->iothपढ़ो))
		WARN_ON(1);

	spin_lock_irqsave(&p->p_work_lock, flags);
	जबतक (que->cq_cons_idx != prod_idx) अणु
		cqe = &que->cq[que->cq_cons_idx];

		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_IO,
			  "cqe=%p prod_idx=%d cons_idx=%d.\n",
			  cqe, prod_idx, que->cq_cons_idx);

		ret = qedi_queue_cqe(qedi, cqe, fp->sb_id, p);
		अगर (ret)
			QEDI_WARN(&qedi->dbg_ctx,
				  "Dropping CQE 0x%x for cid=0x%x.\n",
				  que->cq_cons_idx, cqe->cqe_common.conn_id);

		que->cq_cons_idx++;
		अगर (que->cq_cons_idx == QEDI_CQ_SIZE)
			que->cq_cons_idx = 0;
	पूर्ण
	wake_up_process(p->iothपढ़ो);
	spin_unlock_irqrestore(&p->p_work_lock, flags);

	वापस true;
पूर्ण

अटल bool qedi_fp_has_work(काष्ठा qedi_fastpath *fp)
अणु
	काष्ठा qedi_ctx *qedi = fp->qedi;
	काष्ठा global_queue *que;
	काष्ठा qed_sb_info *sb_info = fp->sb_info;
	काष्ठा status_block_e4 *sb = sb_info->sb_virt;
	u16 prod_idx;

	barrier();

	/* Get the current firmware producer index */
	prod_idx = sb->pi_array[QEDI_PROTO_CQ_PROD_IDX];

	/* Get the poपूर्णांकer to the global CQ this completion is on */
	que = qedi->global_queues[fp->sb_id];

	/* prod idx wrap around uपूर्णांक16 */
	अगर (prod_idx >= QEDI_CQ_SIZE)
		prod_idx = prod_idx % QEDI_CQ_SIZE;

	वापस (que->cq_cons_idx != prod_idx);
पूर्ण

/* MSI-X fastpath handler code */
अटल irqवापस_t qedi_msix_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा qedi_fastpath *fp = dev_id;
	काष्ठा qedi_ctx *qedi = fp->qedi;
	bool wake_io_thपढ़ो = true;

	qed_sb_ack(fp->sb_info, IGU_INT_DISABLE, 0);

process_again:
	wake_io_thपढ़ो = qedi_process_completions(fp);
	अगर (wake_io_thपढ़ो) अणु
		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_DISC,
			  "process already running\n");
	पूर्ण

	अगर (!qedi_fp_has_work(fp))
		qed_sb_update_sb_idx(fp->sb_info);

	/* Check क्रम more work */
	rmb();

	अगर (!qedi_fp_has_work(fp))
		qed_sb_ack(fp->sb_info, IGU_INT_ENABLE, 1);
	अन्यथा
		जाओ process_again;

	वापस IRQ_HANDLED;
पूर्ण

/* simd handler क्रम MSI/INTa */
अटल व्योम qedi_simd_पूर्णांक_handler(व्योम *cookie)
अणु
	/* Cookie is qedi_ctx काष्ठा */
	काष्ठा qedi_ctx *qedi = (काष्ठा qedi_ctx *)cookie;

	QEDI_WARN(&qedi->dbg_ctx, "qedi=%p.\n", qedi);
पूर्ण

#घोषणा QEDI_SIMD_HANDLER_NUM		0
अटल व्योम qedi_sync_मुक्त_irqs(काष्ठा qedi_ctx *qedi)
अणु
	पूर्णांक i;
	u16 idx;

	अगर (qedi->पूर्णांक_info.msix_cnt) अणु
		क्रम (i = 0; i < qedi->पूर्णांक_info.used_cnt; i++) अणु
			idx = i * qedi->dev_info.common.num_hwfns +
			qedi_ops->common->get_affin_hwfn_idx(qedi->cdev);

			QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
				  "Freeing IRQ #%d vector_idx=%d.\n", i, idx);

			synchronize_irq(qedi->पूर्णांक_info.msix[idx].vector);
			irq_set_affinity_hपूर्णांक(qedi->पूर्णांक_info.msix[idx].vector,
					      शून्य);
			मुक्त_irq(qedi->पूर्णांक_info.msix[idx].vector,
				 &qedi->fp_array[i]);
		पूर्ण
	पूर्ण अन्यथा अणु
		qedi_ops->common->simd_handler_clean(qedi->cdev,
						     QEDI_SIMD_HANDLER_NUM);
	पूर्ण

	qedi->पूर्णांक_info.used_cnt = 0;
	qedi_ops->common->set_fp_पूर्णांक(qedi->cdev, 0);
पूर्ण

अटल पूर्णांक qedi_request_msix_irq(काष्ठा qedi_ctx *qedi)
अणु
	पूर्णांक i, rc, cpu;
	u16 idx;

	cpu = cpumask_first(cpu_online_mask);
	क्रम (i = 0; i < qedi->msix_count; i++) अणु
		idx = i * qedi->dev_info.common.num_hwfns +
			  qedi_ops->common->get_affin_hwfn_idx(qedi->cdev);

		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
			  "dev_info: num_hwfns=%d affin_hwfn_idx=%d.\n",
			  qedi->dev_info.common.num_hwfns,
			  qedi_ops->common->get_affin_hwfn_idx(qedi->cdev));

		rc = request_irq(qedi->पूर्णांक_info.msix[idx].vector,
				 qedi_msix_handler, 0, "qedi",
				 &qedi->fp_array[i]);
		अगर (rc) अणु
			QEDI_WARN(&qedi->dbg_ctx, "request_irq failed.\n");
			qedi_sync_मुक्त_irqs(qedi);
			वापस rc;
		पूर्ण
		qedi->पूर्णांक_info.used_cnt++;
		rc = irq_set_affinity_hपूर्णांक(qedi->पूर्णांक_info.msix[idx].vector,
					   get_cpu_mask(cpu));
		cpu = cpumask_next(cpu, cpu_online_mask);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qedi_setup_पूर्णांक(काष्ठा qedi_ctx *qedi)
अणु
	पूर्णांक rc = 0;

	rc = qedi_ops->common->set_fp_पूर्णांक(qedi->cdev, qedi->num_queues);
	अगर (rc < 0)
		जाओ निकास_setup_पूर्णांक;

	qedi->msix_count = rc;

	rc = qedi_ops->common->get_fp_पूर्णांक(qedi->cdev, &qedi->पूर्णांक_info);
	अगर (rc)
		जाओ निकास_setup_पूर्णांक;

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_DISC,
		  "Number of msix_cnt = 0x%x num of cpus = 0x%x\n",
		   qedi->पूर्णांक_info.msix_cnt, num_online_cpus());

	अगर (qedi->पूर्णांक_info.msix_cnt) अणु
		rc = qedi_request_msix_irq(qedi);
		जाओ निकास_setup_पूर्णांक;
	पूर्ण अन्यथा अणु
		qedi_ops->common->simd_handler_config(qedi->cdev, &qedi,
						      QEDI_SIMD_HANDLER_NUM,
						      qedi_simd_पूर्णांक_handler);
		qedi->पूर्णांक_info.used_cnt = 1;
	पूर्ण

निकास_setup_पूर्णांक:
	वापस rc;
पूर्ण

अटल व्योम qedi_मुक्त_nvm_iscsi_cfg(काष्ठा qedi_ctx *qedi)
अणु
	अगर (qedi->iscsi_image)
		dma_मुक्त_coherent(&qedi->pdev->dev,
				  माप(काष्ठा qedi_nvm_iscsi_image),
				  qedi->iscsi_image, qedi->nvm_buf_dma);
पूर्ण

अटल पूर्णांक qedi_alloc_nvm_iscsi_cfg(काष्ठा qedi_ctx *qedi)
अणु
	qedi->iscsi_image = dma_alloc_coherent(&qedi->pdev->dev,
					       माप(काष्ठा qedi_nvm_iscsi_image),
					       &qedi->nvm_buf_dma, GFP_KERNEL);
	अगर (!qedi->iscsi_image) अणु
		QEDI_ERR(&qedi->dbg_ctx, "Could not allocate NVM BUF.\n");
		वापस -ENOMEM;
	पूर्ण
	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
		  "NVM BUF addr=0x%p dma=0x%llx.\n", qedi->iscsi_image,
		  qedi->nvm_buf_dma);

	वापस 0;
पूर्ण

अटल व्योम qedi_मुक्त_bdq(काष्ठा qedi_ctx *qedi)
अणु
	पूर्णांक i;

	अगर (qedi->bdq_pbl_list)
		dma_मुक्त_coherent(&qedi->pdev->dev, QEDI_PAGE_SIZE,
				  qedi->bdq_pbl_list, qedi->bdq_pbl_list_dma);

	अगर (qedi->bdq_pbl)
		dma_मुक्त_coherent(&qedi->pdev->dev, qedi->bdq_pbl_mem_size,
				  qedi->bdq_pbl, qedi->bdq_pbl_dma);

	क्रम (i = 0; i < QEDI_BDQ_NUM; i++) अणु
		अगर (qedi->bdq[i].buf_addr) अणु
			dma_मुक्त_coherent(&qedi->pdev->dev, QEDI_BDQ_BUF_SIZE,
					  qedi->bdq[i].buf_addr,
					  qedi->bdq[i].buf_dma);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qedi_मुक्त_global_queues(काष्ठा qedi_ctx *qedi)
अणु
	पूर्णांक i;
	काष्ठा global_queue **gl = qedi->global_queues;

	क्रम (i = 0; i < qedi->num_queues; i++) अणु
		अगर (!gl[i])
			जारी;

		अगर (gl[i]->cq)
			dma_मुक्त_coherent(&qedi->pdev->dev, gl[i]->cq_mem_size,
					  gl[i]->cq, gl[i]->cq_dma);
		अगर (gl[i]->cq_pbl)
			dma_मुक्त_coherent(&qedi->pdev->dev, gl[i]->cq_pbl_size,
					  gl[i]->cq_pbl, gl[i]->cq_pbl_dma);

		kमुक्त(gl[i]);
	पूर्ण
	qedi_मुक्त_bdq(qedi);
	qedi_मुक्त_nvm_iscsi_cfg(qedi);
पूर्ण

अटल पूर्णांक qedi_alloc_bdq(काष्ठा qedi_ctx *qedi)
अणु
	पूर्णांक i;
	काष्ठा scsi_bd *pbl;
	u64 *list;
	dma_addr_t page;

	/* Alloc dma memory क्रम BDQ buffers */
	क्रम (i = 0; i < QEDI_BDQ_NUM; i++) अणु
		qedi->bdq[i].buf_addr =
				dma_alloc_coherent(&qedi->pdev->dev,
						   QEDI_BDQ_BUF_SIZE,
						   &qedi->bdq[i].buf_dma,
						   GFP_KERNEL);
		अगर (!qedi->bdq[i].buf_addr) अणु
			QEDI_ERR(&qedi->dbg_ctx,
				 "Could not allocate BDQ buffer %d.\n", i);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* Alloc dma memory क्रम BDQ page buffer list */
	qedi->bdq_pbl_mem_size = QEDI_BDQ_NUM * माप(काष्ठा scsi_bd);
	qedi->bdq_pbl_mem_size = ALIGN(qedi->bdq_pbl_mem_size, QEDI_PAGE_SIZE);
	qedi->rq_num_entries = qedi->bdq_pbl_mem_size / माप(काष्ठा scsi_bd);

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_CONN, "rq_num_entries = %d.\n",
		  qedi->rq_num_entries);

	qedi->bdq_pbl = dma_alloc_coherent(&qedi->pdev->dev,
					   qedi->bdq_pbl_mem_size,
					   &qedi->bdq_pbl_dma, GFP_KERNEL);
	अगर (!qedi->bdq_pbl) अणु
		QEDI_ERR(&qedi->dbg_ctx, "Could not allocate BDQ PBL.\n");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Populate BDQ PBL with physical and भव address of inभागidual
	 * BDQ buffers
	 */
	pbl = (काष्ठा scsi_bd  *)qedi->bdq_pbl;
	क्रम (i = 0; i < QEDI_BDQ_NUM; i++) अणु
		pbl->address.hi =
				cpu_to_le32(QEDI_U64_HI(qedi->bdq[i].buf_dma));
		pbl->address.lo =
				cpu_to_le32(QEDI_U64_LO(qedi->bdq[i].buf_dma));
		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_CONN,
			  "pbl [0x%p] pbl->address hi [0x%llx] lo [0x%llx], idx [%d]\n",
			  pbl, pbl->address.hi, pbl->address.lo, i);
		pbl->opaque.iscsi_opaque.reserved_zero[0] = 0;
		pbl->opaque.iscsi_opaque.reserved_zero[1] = 0;
		pbl->opaque.iscsi_opaque.reserved_zero[2] = 0;
		pbl->opaque.iscsi_opaque.opaque = cpu_to_le16(i);
		pbl++;
	पूर्ण

	/* Allocate list of PBL pages */
	qedi->bdq_pbl_list = dma_alloc_coherent(&qedi->pdev->dev,
						QEDI_PAGE_SIZE,
						&qedi->bdq_pbl_list_dma,
						GFP_KERNEL);
	अगर (!qedi->bdq_pbl_list) अणु
		QEDI_ERR(&qedi->dbg_ctx,
			 "Could not allocate list of PBL pages.\n");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Now populate PBL list with pages that contain poपूर्णांकers to the
	 * inभागidual buffers.
	 */
	qedi->bdq_pbl_list_num_entries = qedi->bdq_pbl_mem_size /
					 QEDI_PAGE_SIZE;
	list = (u64 *)qedi->bdq_pbl_list;
	page = qedi->bdq_pbl_list_dma;
	क्रम (i = 0; i < qedi->bdq_pbl_list_num_entries; i++) अणु
		*list = qedi->bdq_pbl_dma;
		list++;
		page += QEDI_PAGE_SIZE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qedi_alloc_global_queues(काष्ठा qedi_ctx *qedi)
अणु
	u32 *list;
	पूर्णांक i;
	पूर्णांक status = 0, rc;
	u32 *pbl;
	dma_addr_t page;
	पूर्णांक num_pages;

	/*
	 * Number of global queues (CQ / RQ). This should
	 * be <= number of available MSIX vectors क्रम the PF
	 */
	अगर (!qedi->num_queues) अणु
		QEDI_ERR(&qedi->dbg_ctx, "No MSI-X vectors available!\n");
		वापस 1;
	पूर्ण

	/* Make sure we allocated the PBL that will contain the physical
	 * addresses of our queues
	 */
	अगर (!qedi->p_cpuq) अणु
		status = 1;
		जाओ mem_alloc_failure;
	पूर्ण

	qedi->global_queues = kzalloc((माप(काष्ठा global_queue *) *
				       qedi->num_queues), GFP_KERNEL);
	अगर (!qedi->global_queues) अणु
		QEDI_ERR(&qedi->dbg_ctx,
			 "Unable to allocate global queues array ptr memory\n");
		वापस -ENOMEM;
	पूर्ण
	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_DISC,
		  "qedi->global_queues=%p.\n", qedi->global_queues);

	/* Allocate DMA coherent buffers क्रम BDQ */
	rc = qedi_alloc_bdq(qedi);
	अगर (rc)
		जाओ mem_alloc_failure;

	/* Allocate DMA coherent buffers क्रम NVM_ISCSI_CFG */
	rc = qedi_alloc_nvm_iscsi_cfg(qedi);
	अगर (rc)
		जाओ mem_alloc_failure;

	/* Allocate a CQ and an associated PBL क्रम each MSI-X
	 * vector.
	 */
	क्रम (i = 0; i < qedi->num_queues; i++) अणु
		qedi->global_queues[i] =
					kzalloc(माप(*qedi->global_queues[0]),
						GFP_KERNEL);
		अगर (!qedi->global_queues[i]) अणु
			QEDI_ERR(&qedi->dbg_ctx,
				 "Unable to allocation global queue %d.\n", i);
			status = -ENOMEM;
			जाओ mem_alloc_failure;
		पूर्ण

		qedi->global_queues[i]->cq_mem_size =
		    (QEDI_CQ_SIZE + 8) * माप(जोड़ iscsi_cqe);
		qedi->global_queues[i]->cq_mem_size =
		    (qedi->global_queues[i]->cq_mem_size +
		    (QEDI_PAGE_SIZE - 1));

		qedi->global_queues[i]->cq_pbl_size =
		    (qedi->global_queues[i]->cq_mem_size /
		    QEDI_PAGE_SIZE) * माप(व्योम *);
		qedi->global_queues[i]->cq_pbl_size =
		    (qedi->global_queues[i]->cq_pbl_size +
		    (QEDI_PAGE_SIZE - 1));

		qedi->global_queues[i]->cq = dma_alloc_coherent(&qedi->pdev->dev,
								qedi->global_queues[i]->cq_mem_size,
								&qedi->global_queues[i]->cq_dma,
								GFP_KERNEL);

		अगर (!qedi->global_queues[i]->cq) अणु
			QEDI_WARN(&qedi->dbg_ctx,
				  "Could not allocate cq.\n");
			status = -ENOMEM;
			जाओ mem_alloc_failure;
		पूर्ण
		qedi->global_queues[i]->cq_pbl = dma_alloc_coherent(&qedi->pdev->dev,
								    qedi->global_queues[i]->cq_pbl_size,
								    &qedi->global_queues[i]->cq_pbl_dma,
								    GFP_KERNEL);

		अगर (!qedi->global_queues[i]->cq_pbl) अणु
			QEDI_WARN(&qedi->dbg_ctx,
				  "Could not allocate cq PBL.\n");
			status = -ENOMEM;
			जाओ mem_alloc_failure;
		पूर्ण

		/* Create PBL */
		num_pages = qedi->global_queues[i]->cq_mem_size /
		    QEDI_PAGE_SIZE;
		page = qedi->global_queues[i]->cq_dma;
		pbl = (u32 *)qedi->global_queues[i]->cq_pbl;

		जबतक (num_pages--) अणु
			*pbl = (u32)page;
			pbl++;
			*pbl = (u32)((u64)page >> 32);
			pbl++;
			page += QEDI_PAGE_SIZE;
		पूर्ण
	पूर्ण

	list = (u32 *)qedi->p_cpuq;

	/*
	 * The list is built as follows: CQ#0 PBL poपूर्णांकer, RQ#0 PBL poपूर्णांकer,
	 * CQ#1 PBL poपूर्णांकer, RQ#1 PBL poपूर्णांकer, etc.  Each PBL poपूर्णांकer poपूर्णांकs
	 * to the physical address which contains an array of poपूर्णांकers to the
	 * physical addresses of the specअगरic queue pages.
	 */
	क्रम (i = 0; i < qedi->num_queues; i++) अणु
		*list = (u32)qedi->global_queues[i]->cq_pbl_dma;
		list++;
		*list = (u32)((u64)qedi->global_queues[i]->cq_pbl_dma >> 32);
		list++;

		*list = (u32)0;
		list++;
		*list = (u32)((u64)0 >> 32);
		list++;
	पूर्ण

	वापस 0;

mem_alloc_failure:
	qedi_मुक्त_global_queues(qedi);
	वापस status;
पूर्ण

पूर्णांक qedi_alloc_sq(काष्ठा qedi_ctx *qedi, काष्ठा qedi_endpoपूर्णांक *ep)
अणु
	पूर्णांक rval = 0;
	u32 *pbl;
	dma_addr_t page;
	पूर्णांक num_pages;

	अगर (!ep)
		वापस -EIO;

	/* Calculate appropriate queue and PBL sizes */
	ep->sq_mem_size = QEDI_SQ_SIZE * माप(काष्ठा iscsi_wqe);
	ep->sq_mem_size += QEDI_PAGE_SIZE - 1;

	ep->sq_pbl_size = (ep->sq_mem_size / QEDI_PAGE_SIZE) * माप(व्योम *);
	ep->sq_pbl_size = ep->sq_pbl_size + QEDI_PAGE_SIZE;

	ep->sq = dma_alloc_coherent(&qedi->pdev->dev, ep->sq_mem_size,
				    &ep->sq_dma, GFP_KERNEL);
	अगर (!ep->sq) अणु
		QEDI_WARN(&qedi->dbg_ctx,
			  "Could not allocate send queue.\n");
		rval = -ENOMEM;
		जाओ out;
	पूर्ण
	ep->sq_pbl = dma_alloc_coherent(&qedi->pdev->dev, ep->sq_pbl_size,
					&ep->sq_pbl_dma, GFP_KERNEL);
	अगर (!ep->sq_pbl) अणु
		QEDI_WARN(&qedi->dbg_ctx,
			  "Could not allocate send queue PBL.\n");
		rval = -ENOMEM;
		जाओ out_मुक्त_sq;
	पूर्ण

	/* Create PBL */
	num_pages = ep->sq_mem_size / QEDI_PAGE_SIZE;
	page = ep->sq_dma;
	pbl = (u32 *)ep->sq_pbl;

	जबतक (num_pages--) अणु
		*pbl = (u32)page;
		pbl++;
		*pbl = (u32)((u64)page >> 32);
		pbl++;
		page += QEDI_PAGE_SIZE;
	पूर्ण

	वापस rval;

out_मुक्त_sq:
	dma_मुक्त_coherent(&qedi->pdev->dev, ep->sq_mem_size, ep->sq,
			  ep->sq_dma);
out:
	वापस rval;
पूर्ण

व्योम qedi_मुक्त_sq(काष्ठा qedi_ctx *qedi, काष्ठा qedi_endpoपूर्णांक *ep)
अणु
	अगर (ep->sq_pbl)
		dma_मुक्त_coherent(&qedi->pdev->dev, ep->sq_pbl_size, ep->sq_pbl,
				  ep->sq_pbl_dma);
	अगर (ep->sq)
		dma_मुक्त_coherent(&qedi->pdev->dev, ep->sq_mem_size, ep->sq,
				  ep->sq_dma);
पूर्ण

पूर्णांक qedi_get_task_idx(काष्ठा qedi_ctx *qedi)
अणु
	s16 पंचांगp_idx;

again:
	पंचांगp_idx = find_first_zero_bit(qedi->task_idx_map,
				      MAX_ISCSI_TASK_ENTRIES);

	अगर (पंचांगp_idx >= MAX_ISCSI_TASK_ENTRIES) अणु
		QEDI_ERR(&qedi->dbg_ctx, "FW task context pool is full.\n");
		पंचांगp_idx = -1;
		जाओ err_idx;
	पूर्ण

	अगर (test_and_set_bit(पंचांगp_idx, qedi->task_idx_map))
		जाओ again;

err_idx:
	वापस पंचांगp_idx;
पूर्ण

व्योम qedi_clear_task_idx(काष्ठा qedi_ctx *qedi, पूर्णांक idx)
अणु
	अगर (!test_and_clear_bit(idx, qedi->task_idx_map))
		QEDI_ERR(&qedi->dbg_ctx,
			 "FW task context, already cleared, tid=0x%x\n", idx);
पूर्ण

व्योम qedi_update_itt_map(काष्ठा qedi_ctx *qedi, u32 tid, u32 proto_itt,
			 काष्ठा qedi_cmd *cmd)
अणु
	qedi->itt_map[tid].itt = proto_itt;
	qedi->itt_map[tid].p_cmd = cmd;

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_CONN,
		  "update itt map tid=0x%x, with proto itt=0x%x\n", tid,
		  qedi->itt_map[tid].itt);
पूर्ण

व्योम qedi_get_task_tid(काष्ठा qedi_ctx *qedi, u32 itt, s16 *tid)
अणु
	u16 i;

	क्रम (i = 0; i < MAX_ISCSI_TASK_ENTRIES; i++) अणु
		अगर (qedi->itt_map[i].itt == itt) अणु
			*tid = i;
			QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_CONN,
				  "Ref itt=0x%x, found at tid=0x%x\n",
				  itt, *tid);
			वापस;
		पूर्ण
	पूर्ण

	WARN_ON(1);
पूर्ण

व्योम qedi_get_proto_itt(काष्ठा qedi_ctx *qedi, u32 tid, u32 *proto_itt)
अणु
	*proto_itt = qedi->itt_map[tid].itt;
	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_CONN,
		  "Get itt map tid [0x%x with proto itt[0x%x]",
		  tid, *proto_itt);
पूर्ण

काष्ठा qedi_cmd *qedi_get_cmd_from_tid(काष्ठा qedi_ctx *qedi, u32 tid)
अणु
	काष्ठा qedi_cmd *cmd = शून्य;

	अगर (tid >= MAX_ISCSI_TASK_ENTRIES)
		वापस शून्य;

	cmd = qedi->itt_map[tid].p_cmd;
	अगर (cmd->task_id != tid)
		वापस शून्य;

	qedi->itt_map[tid].p_cmd = शून्य;

	वापस cmd;
पूर्ण

अटल पूर्णांक qedi_alloc_itt(काष्ठा qedi_ctx *qedi)
अणु
	qedi->itt_map = kसुस्मृति(MAX_ISCSI_TASK_ENTRIES,
				माप(काष्ठा qedi_itt_map), GFP_KERNEL);
	अगर (!qedi->itt_map) अणु
		QEDI_ERR(&qedi->dbg_ctx,
			 "Unable to allocate itt map array memory\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम qedi_मुक्त_itt(काष्ठा qedi_ctx *qedi)
अणु
	kमुक्त(qedi->itt_map);
पूर्ण

अटल काष्ठा qed_ll2_cb_ops qedi_ll2_cb_ops = अणु
	.rx_cb = qedi_ll2_rx,
	.tx_cb = शून्य,
पूर्ण;

अटल पूर्णांक qedi_percpu_io_thपढ़ो(व्योम *arg)
अणु
	काष्ठा qedi_percpu_s *p = arg;
	काष्ठा qedi_work *work, *पंचांगp;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(work_list);

	set_user_nice(current, -20);

	जबतक (!kthपढ़ो_should_stop()) अणु
		spin_lock_irqsave(&p->p_work_lock, flags);
		जबतक (!list_empty(&p->work_list)) अणु
			list_splice_init(&p->work_list, &work_list);
			spin_unlock_irqrestore(&p->p_work_lock, flags);

			list_क्रम_each_entry_safe(work, पंचांगp, &work_list, list) अणु
				list_del_init(&work->list);
				qedi_fp_process_cqes(work);
				अगर (!work->is_solicited)
					kमुक्त(work);
			पूर्ण
			cond_resched();
			spin_lock_irqsave(&p->p_work_lock, flags);
		पूर्ण
		set_current_state(TASK_INTERRUPTIBLE);
		spin_unlock_irqrestore(&p->p_work_lock, flags);
		schedule();
	पूर्ण
	__set_current_state(TASK_RUNNING);

	वापस 0;
पूर्ण

अटल पूर्णांक qedi_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा qedi_percpu_s *p = this_cpu_ptr(&qedi_percpu);
	काष्ठा task_काष्ठा *thपढ़ो;

	thपढ़ो = kthपढ़ो_create_on_node(qedi_percpu_io_thपढ़ो, (व्योम *)p,
					cpu_to_node(cpu),
					"qedi_thread/%d", cpu);
	अगर (IS_ERR(thपढ़ो))
		वापस PTR_ERR(thपढ़ो);

	kthपढ़ो_bind(thपढ़ो, cpu);
	p->iothपढ़ो = thपढ़ो;
	wake_up_process(thपढ़ो);
	वापस 0;
पूर्ण

अटल पूर्णांक qedi_cpu_offline(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा qedi_percpu_s *p = this_cpu_ptr(&qedi_percpu);
	काष्ठा qedi_work *work, *पंचांगp;
	काष्ठा task_काष्ठा *thपढ़ो;

	spin_lock_bh(&p->p_work_lock);
	thपढ़ो = p->iothपढ़ो;
	p->iothपढ़ो = शून्य;

	list_क्रम_each_entry_safe(work, पंचांगp, &p->work_list, list) अणु
		list_del_init(&work->list);
		qedi_fp_process_cqes(work);
		अगर (!work->is_solicited)
			kमुक्त(work);
	पूर्ण

	spin_unlock_bh(&p->p_work_lock);
	अगर (thपढ़ो)
		kthपढ़ो_stop(thपढ़ो);
	वापस 0;
पूर्ण

व्योम qedi_reset_host_mtu(काष्ठा qedi_ctx *qedi, u16 mtu)
अणु
	काष्ठा qed_ll2_params params;

	qedi_recover_all_conns(qedi);

	qedi_ops->ll2->stop(qedi->cdev);
	qedi_ll2_मुक्त_skbs(qedi);

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO, "old MTU %u, new MTU %u\n",
		  qedi->ll2_mtu, mtu);
	स_रखो(&params, 0, माप(params));
	qedi->ll2_mtu = mtu;
	params.mtu = qedi->ll2_mtu + IPV6_HDR_LEN + TCP_HDR_LEN;
	params.drop_ttl0_packets = 0;
	params.rx_vlan_stripping = 1;
	ether_addr_copy(params.ll2_mac_address, qedi->dev_info.common.hw_mac);
	qedi_ops->ll2->start(qedi->cdev, &params);
पूर्ण

/*
 * qedi_get_nvram_block: - Scan through the iSCSI NVRAM block (जबतक accounting
 * क्रम gaps) क्रम the matching असलolute-pf-id of the QEDI device.
 */
अटल काष्ठा nvm_iscsi_block *
qedi_get_nvram_block(काष्ठा qedi_ctx *qedi)
अणु
	पूर्णांक i;
	u8 pf;
	u32 flags;
	काष्ठा nvm_iscsi_block *block;

	pf = qedi->dev_info.common.असल_pf_id;
	block = &qedi->iscsi_image->iscsi_cfg.block[0];
	क्रम (i = 0; i < NUM_OF_ISCSI_PF_SUPPORTED; i++, block++) अणु
		flags = ((block->id) & NVM_ISCSI_CFG_BLK_CTRL_FLAG_MASK) >>
			NVM_ISCSI_CFG_BLK_CTRL_FLAG_OFFSET;
		अगर (flags & (NVM_ISCSI_CFG_BLK_CTRL_FLAG_IS_NOT_EMPTY |
				NVM_ISCSI_CFG_BLK_CTRL_FLAG_PF_MAPPED) &&
			(pf == (block->id & NVM_ISCSI_CFG_BLK_MAPPED_PF_ID_MASK)
				>> NVM_ISCSI_CFG_BLK_MAPPED_PF_ID_OFFSET))
			वापस block;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल sमाप_प्रकार qedi_show_boot_eth_info(व्योम *data, पूर्णांक type, अक्षर *buf)
अणु
	काष्ठा qedi_ctx *qedi = data;
	काष्ठा nvm_iscsi_initiator *initiator;
	पूर्णांक rc = 1;
	u32 ipv6_en, dhcp_en, ip_len;
	काष्ठा nvm_iscsi_block *block;
	अक्षर *fmt, *ip, *sub, *gw;

	block = qedi_get_nvram_block(qedi);
	अगर (!block)
		वापस 0;

	initiator = &block->initiator;
	ipv6_en = block->generic.ctrl_flags &
		  NVM_ISCSI_CFG_GEN_IPV6_ENABLED;
	dhcp_en = block->generic.ctrl_flags &
		  NVM_ISCSI_CFG_GEN_DHCP_TCPIP_CONFIG_ENABLED;
	/* Static IP assignments. */
	fmt = ipv6_en ? "%pI6\n" : "%pI4\n";
	ip = ipv6_en ? initiator->ipv6.addr.byte : initiator->ipv4.addr.byte;
	ip_len = ipv6_en ? IPV6_LEN : IPV4_LEN;
	sub = ipv6_en ? initiator->ipv6.subnet_mask.byte :
	      initiator->ipv4.subnet_mask.byte;
	gw = ipv6_en ? initiator->ipv6.gateway.byte :
	     initiator->ipv4.gateway.byte;
	/* DHCP IP adjusपंचांगents. */
	fmt = dhcp_en ? "%s\n" : fmt;
	अगर (dhcp_en) अणु
		ip = ipv6_en ? "0::0" : "0.0.0.0";
		sub = ip;
		gw = ip;
		ip_len = ipv6_en ? 5 : 8;
	पूर्ण

	चयन (type) अणु
	हाल ISCSI_BOOT_ETH_IP_ADDR:
		rc = snम_लिखो(buf, ip_len, fmt, ip);
		अवरोध;
	हाल ISCSI_BOOT_ETH_SUBNET_MASK:
		rc = snम_लिखो(buf, ip_len, fmt, sub);
		अवरोध;
	हाल ISCSI_BOOT_ETH_GATEWAY:
		rc = snम_लिखो(buf, ip_len, fmt, gw);
		अवरोध;
	हाल ISCSI_BOOT_ETH_FLAGS:
		rc = snम_लिखो(buf, 3, "%hhd\n",
			      SYSFS_FLAG_FW_SEL_BOOT);
		अवरोध;
	हाल ISCSI_BOOT_ETH_INDEX:
		rc = snम_लिखो(buf, 3, "0\n");
		अवरोध;
	हाल ISCSI_BOOT_ETH_MAC:
		rc = sysfs_क्रमmat_mac(buf, qedi->mac, ETH_ALEN);
		अवरोध;
	हाल ISCSI_BOOT_ETH_VLAN:
		rc = snम_लिखो(buf, 12, "%d\n",
			      GET_FIELD2(initiator->generic_cont0,
					 NVM_ISCSI_CFG_INITIATOR_VLAN));
		अवरोध;
	हाल ISCSI_BOOT_ETH_ORIGIN:
		अगर (dhcp_en)
			rc = snम_लिखो(buf, 3, "3\n");
		अवरोध;
	शेष:
		rc = 0;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल umode_t qedi_eth_get_attr_visibility(व्योम *data, पूर्णांक type)
अणु
	पूर्णांक rc = 1;

	चयन (type) अणु
	हाल ISCSI_BOOT_ETH_FLAGS:
	हाल ISCSI_BOOT_ETH_MAC:
	हाल ISCSI_BOOT_ETH_INDEX:
	हाल ISCSI_BOOT_ETH_IP_ADDR:
	हाल ISCSI_BOOT_ETH_SUBNET_MASK:
	हाल ISCSI_BOOT_ETH_GATEWAY:
	हाल ISCSI_BOOT_ETH_ORIGIN:
	हाल ISCSI_BOOT_ETH_VLAN:
		rc = 0444;
		अवरोध;
	शेष:
		rc = 0;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल sमाप_प्रकार qedi_show_boot_ini_info(व्योम *data, पूर्णांक type, अक्षर *buf)
अणु
	काष्ठा qedi_ctx *qedi = data;
	काष्ठा nvm_iscsi_initiator *initiator;
	पूर्णांक rc;
	काष्ठा nvm_iscsi_block *block;

	block = qedi_get_nvram_block(qedi);
	अगर (!block)
		वापस 0;

	initiator = &block->initiator;

	चयन (type) अणु
	हाल ISCSI_BOOT_INI_INITIATOR_NAME:
		rc = प्र_लिखो(buf, "%.*s\n", NVM_ISCSI_CFG_ISCSI_NAME_MAX_LEN,
			     initiator->initiator_name.byte);
		अवरोध;
	शेष:
		rc = 0;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल umode_t qedi_ini_get_attr_visibility(व्योम *data, पूर्णांक type)
अणु
	पूर्णांक rc;

	चयन (type) अणु
	हाल ISCSI_BOOT_INI_INITIATOR_NAME:
		rc = 0444;
		अवरोध;
	शेष:
		rc = 0;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल sमाप_प्रकार
qedi_show_boot_tgt_info(काष्ठा qedi_ctx *qedi, पूर्णांक type,
			अक्षर *buf, क्रमागत qedi_nvm_tgts idx)
अणु
	पूर्णांक rc = 1;
	u32 ctrl_flags, ipv6_en, chap_en, mchap_en, ip_len;
	काष्ठा nvm_iscsi_block *block;
	अक्षर *chap_name, *chap_secret;
	अक्षर *mchap_name, *mchap_secret;

	block = qedi_get_nvram_block(qedi);
	अगर (!block)
		जाओ निकास_show_tgt_info;

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_EVT,
		  "Port:%d, tgt_idx:%d\n",
		  GET_FIELD2(block->id, NVM_ISCSI_CFG_BLK_MAPPED_PF_ID), idx);

	ctrl_flags = block->target[idx].ctrl_flags &
		     NVM_ISCSI_CFG_TARGET_ENABLED;

	अगर (!ctrl_flags) अणु
		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_EVT,
			  "Target disabled\n");
		जाओ निकास_show_tgt_info;
	पूर्ण

	ipv6_en = block->generic.ctrl_flags &
		  NVM_ISCSI_CFG_GEN_IPV6_ENABLED;
	ip_len = ipv6_en ? IPV6_LEN : IPV4_LEN;
	chap_en = block->generic.ctrl_flags &
		  NVM_ISCSI_CFG_GEN_CHAP_ENABLED;
	chap_name = chap_en ? block->initiator.chap_name.byte : शून्य;
	chap_secret = chap_en ? block->initiator.chap_password.byte : शून्य;

	mchap_en = block->generic.ctrl_flags &
		  NVM_ISCSI_CFG_GEN_CHAP_MUTUAL_ENABLED;
	mchap_name = mchap_en ? block->target[idx].chap_name.byte : शून्य;
	mchap_secret = mchap_en ? block->target[idx].chap_password.byte : शून्य;

	चयन (type) अणु
	हाल ISCSI_BOOT_TGT_NAME:
		rc = प्र_लिखो(buf, "%.*s\n", NVM_ISCSI_CFG_ISCSI_NAME_MAX_LEN,
			     block->target[idx].target_name.byte);
		अवरोध;
	हाल ISCSI_BOOT_TGT_IP_ADDR:
		अगर (ipv6_en)
			rc = snम_लिखो(buf, ip_len, "%pI6\n",
				      block->target[idx].ipv6_addr.byte);
		अन्यथा
			rc = snम_लिखो(buf, ip_len, "%pI4\n",
				      block->target[idx].ipv4_addr.byte);
		अवरोध;
	हाल ISCSI_BOOT_TGT_PORT:
		rc = snम_लिखो(buf, 12, "%d\n",
			      GET_FIELD2(block->target[idx].generic_cont0,
					 NVM_ISCSI_CFG_TARGET_TCP_PORT));
		अवरोध;
	हाल ISCSI_BOOT_TGT_LUN:
		rc = snम_लिखो(buf, 22, "%.*d\n",
			      block->target[idx].lun.value[1],
			      block->target[idx].lun.value[0]);
		अवरोध;
	हाल ISCSI_BOOT_TGT_CHAP_NAME:
		rc = प्र_लिखो(buf, "%.*s\n", NVM_ISCSI_CFG_CHAP_NAME_MAX_LEN,
			     chap_name);
		अवरोध;
	हाल ISCSI_BOOT_TGT_CHAP_SECRET:
		rc = प्र_लिखो(buf, "%.*s\n", NVM_ISCSI_CFG_CHAP_PWD_MAX_LEN,
			     chap_secret);
		अवरोध;
	हाल ISCSI_BOOT_TGT_REV_CHAP_NAME:
		rc = प्र_लिखो(buf, "%.*s\n", NVM_ISCSI_CFG_CHAP_NAME_MAX_LEN,
			     mchap_name);
		अवरोध;
	हाल ISCSI_BOOT_TGT_REV_CHAP_SECRET:
		rc = प्र_लिखो(buf, "%.*s\n", NVM_ISCSI_CFG_CHAP_PWD_MAX_LEN,
			     mchap_secret);
		अवरोध;
	हाल ISCSI_BOOT_TGT_FLAGS:
		rc = snम_लिखो(buf, 3, "%hhd\n", SYSFS_FLAG_FW_SEL_BOOT);
		अवरोध;
	हाल ISCSI_BOOT_TGT_NIC_ASSOC:
		rc = snम_लिखो(buf, 3, "0\n");
		अवरोध;
	शेष:
		rc = 0;
		अवरोध;
	पूर्ण

निकास_show_tgt_info:
	वापस rc;
पूर्ण

अटल sमाप_प्रकार qedi_show_boot_tgt_pri_info(व्योम *data, पूर्णांक type, अक्षर *buf)
अणु
	काष्ठा qedi_ctx *qedi = data;

	वापस qedi_show_boot_tgt_info(qedi, type, buf, QEDI_NVM_TGT_PRI);
पूर्ण

अटल sमाप_प्रकार qedi_show_boot_tgt_sec_info(व्योम *data, पूर्णांक type, अक्षर *buf)
अणु
	काष्ठा qedi_ctx *qedi = data;

	वापस qedi_show_boot_tgt_info(qedi, type, buf, QEDI_NVM_TGT_SEC);
पूर्ण

अटल umode_t qedi_tgt_get_attr_visibility(व्योम *data, पूर्णांक type)
अणु
	पूर्णांक rc;

	चयन (type) अणु
	हाल ISCSI_BOOT_TGT_NAME:
	हाल ISCSI_BOOT_TGT_IP_ADDR:
	हाल ISCSI_BOOT_TGT_PORT:
	हाल ISCSI_BOOT_TGT_LUN:
	हाल ISCSI_BOOT_TGT_CHAP_NAME:
	हाल ISCSI_BOOT_TGT_CHAP_SECRET:
	हाल ISCSI_BOOT_TGT_REV_CHAP_NAME:
	हाल ISCSI_BOOT_TGT_REV_CHAP_SECRET:
	हाल ISCSI_BOOT_TGT_NIC_ASSOC:
	हाल ISCSI_BOOT_TGT_FLAGS:
		rc = 0444;
		अवरोध;
	शेष:
		rc = 0;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम qedi_boot_release(व्योम *data)
अणु
	काष्ठा qedi_ctx *qedi = data;

	scsi_host_put(qedi->shost);
पूर्ण

अटल पूर्णांक qedi_get_boot_info(काष्ठा qedi_ctx *qedi)
अणु
	पूर्णांक ret = 1;

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
		  "Get NVM iSCSI CFG image\n");
	ret = qedi_ops->common->nvm_get_image(qedi->cdev,
					      QED_NVM_IMAGE_ISCSI_CFG,
					      (अक्षर *)qedi->iscsi_image,
					      माप(काष्ठा qedi_nvm_iscsi_image));
	अगर (ret)
		QEDI_ERR(&qedi->dbg_ctx,
			 "Could not get NVM image. ret = %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक qedi_setup_boot_info(काष्ठा qedi_ctx *qedi)
अणु
	काष्ठा iscsi_boot_kobj *boot_kobj;

	अगर (qedi_get_boot_info(qedi))
		वापस -EPERM;

	qedi->boot_kset = iscsi_boot_create_host_kset(qedi->shost->host_no);
	अगर (!qedi->boot_kset)
		जाओ kset_मुक्त;

	अगर (!scsi_host_get(qedi->shost))
		जाओ kset_मुक्त;

	boot_kobj = iscsi_boot_create_target(qedi->boot_kset, 0, qedi,
					     qedi_show_boot_tgt_pri_info,
					     qedi_tgt_get_attr_visibility,
					     qedi_boot_release);
	अगर (!boot_kobj)
		जाओ put_host;

	अगर (!scsi_host_get(qedi->shost))
		जाओ kset_मुक्त;

	boot_kobj = iscsi_boot_create_target(qedi->boot_kset, 1, qedi,
					     qedi_show_boot_tgt_sec_info,
					     qedi_tgt_get_attr_visibility,
					     qedi_boot_release);
	अगर (!boot_kobj)
		जाओ put_host;

	अगर (!scsi_host_get(qedi->shost))
		जाओ kset_मुक्त;

	boot_kobj = iscsi_boot_create_initiator(qedi->boot_kset, 0, qedi,
						qedi_show_boot_ini_info,
						qedi_ini_get_attr_visibility,
						qedi_boot_release);
	अगर (!boot_kobj)
		जाओ put_host;

	अगर (!scsi_host_get(qedi->shost))
		जाओ kset_मुक्त;

	boot_kobj = iscsi_boot_create_ethernet(qedi->boot_kset, 0, qedi,
					       qedi_show_boot_eth_info,
					       qedi_eth_get_attr_visibility,
					       qedi_boot_release);
	अगर (!boot_kobj)
		जाओ put_host;

	वापस 0;

put_host:
	scsi_host_put(qedi->shost);
kset_मुक्त:
	iscsi_boot_destroy_kset(qedi->boot_kset);
	वापस -ENOMEM;
पूर्ण

अटल pci_ers_result_t qedi_io_error_detected(काष्ठा pci_dev *pdev,
					       pci_channel_state_t state)
अणु
	काष्ठा qedi_ctx *qedi = pci_get_drvdata(pdev);

	QEDI_ERR(&qedi->dbg_ctx, "%s: PCI error detected [%d]\n",
		 __func__, state);

	अगर (test_and_set_bit(QEDI_IN_RECOVERY, &qedi->flags)) अणु
		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
			  "Recovery already in progress.\n");
		वापस PCI_ERS_RESULT_NONE;
	पूर्ण

	qedi_ops->common->recovery_process(qedi->cdev);

	वापस PCI_ERS_RESULT_CAN_RECOVER;
पूर्ण

अटल व्योम __qedi_हटाओ(काष्ठा pci_dev *pdev, पूर्णांक mode)
अणु
	काष्ठा qedi_ctx *qedi = pci_get_drvdata(pdev);
	पूर्णांक rval;
	u16 retry = 10;

	अगर (mode == QEDI_MODE_SHUTDOWN)
		iscsi_host_क्रम_each_session(qedi->shost,
					    qedi_clear_session_ctx);

	अगर (mode == QEDI_MODE_NORMAL || mode == QEDI_MODE_SHUTDOWN) अणु
		अगर (qedi->पंचांगf_thपढ़ो) अणु
			flush_workqueue(qedi->पंचांगf_thपढ़ो);
			destroy_workqueue(qedi->पंचांगf_thपढ़ो);
			qedi->पंचांगf_thपढ़ो = शून्य;
		पूर्ण

		अगर (qedi->offload_thपढ़ो) अणु
			flush_workqueue(qedi->offload_thपढ़ो);
			destroy_workqueue(qedi->offload_thपढ़ो);
			qedi->offload_thपढ़ो = शून्य;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
	qedi_dbg_host_निकास(&qedi->dbg_ctx);
#पूर्ण_अगर
	अगर (!test_bit(QEDI_IN_OFFLINE, &qedi->flags))
		qedi_ops->common->set_घातer_state(qedi->cdev, PCI_D0);

	qedi_sync_मुक्त_irqs(qedi);

	अगर (!test_bit(QEDI_IN_OFFLINE, &qedi->flags)) अणु
		जबतक (retry--) अणु
			rval = qedi_ops->stop(qedi->cdev);
			अगर (rval < 0)
				msleep(1000);
			अन्यथा
				अवरोध;
		पूर्ण
		qedi_ops->ll2->stop(qedi->cdev);
	पूर्ण

	qedi_मुक्त_iscsi_pf_param(qedi);

	rval = qedi_ops->common->update_drv_state(qedi->cdev, false);
	अगर (rval)
		QEDI_ERR(&qedi->dbg_ctx, "Failed to send drv state to MFW\n");

	अगर (!test_bit(QEDI_IN_OFFLINE, &qedi->flags)) अणु
		qedi_ops->common->slowpath_stop(qedi->cdev);
		qedi_ops->common->हटाओ(qedi->cdev);
	पूर्ण

	qedi_destroy_fp(qedi);

	अगर (mode == QEDI_MODE_NORMAL || mode == QEDI_MODE_SHUTDOWN) अणु
		qedi_release_cid_que(qedi);
		qedi_cm_मुक्त_mem(qedi);
		qedi_मुक्त_uio(qedi->udev);
		qedi_मुक्त_itt(qedi);

		अगर (qedi->ll2_recv_thपढ़ो) अणु
			kthपढ़ो_stop(qedi->ll2_recv_thपढ़ो);
			qedi->ll2_recv_thपढ़ो = शून्य;
		पूर्ण
		qedi_ll2_मुक्त_skbs(qedi);

		अगर (qedi->boot_kset)
			iscsi_boot_destroy_kset(qedi->boot_kset);

		iscsi_host_हटाओ(qedi->shost);
		iscsi_host_मुक्त(qedi->shost);
	पूर्ण
पूर्ण

अटल व्योम qedi_board_disable_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qedi_ctx *qedi =
			container_of(work, काष्ठा qedi_ctx,
				     board_disable_work.work);

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
		  "Fan failure, Unloading firmware context.\n");

	अगर (test_and_set_bit(QEDI_IN_SHUTDOWN, &qedi->flags))
		वापस;

	__qedi_हटाओ(qedi->pdev, QEDI_MODE_SHUTDOWN);
पूर्ण

अटल व्योम qedi_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा qedi_ctx *qedi = pci_get_drvdata(pdev);

	QEDI_ERR(&qedi->dbg_ctx, "%s: Shutdown qedi\n", __func__);
	अगर (test_and_set_bit(QEDI_IN_SHUTDOWN, &qedi->flags))
		वापस;
	__qedi_हटाओ(pdev, QEDI_MODE_SHUTDOWN);
पूर्ण

अटल पूर्णांक __qedi_probe(काष्ठा pci_dev *pdev, पूर्णांक mode)
अणु
	काष्ठा qedi_ctx *qedi;
	काष्ठा qed_ll2_params params;
	u8 dp_level = 0;
	bool is_vf = false;
	अक्षर host_buf[16];
	काष्ठा qed_link_params link_params;
	काष्ठा qed_slowpath_params sp_params;
	काष्ठा qed_probe_params qed_params;
	व्योम *task_start, *task_end;
	पूर्णांक rc;
	u16 retry = 10;

	अगर (mode != QEDI_MODE_RECOVERY) अणु
		qedi = qedi_host_alloc(pdev);
		अगर (!qedi) अणु
			rc = -ENOMEM;
			जाओ निकास_probe;
		पूर्ण
	पूर्ण अन्यथा अणु
		qedi = pci_get_drvdata(pdev);
	पूर्ण

retry_probe:
	अगर (mode == QEDI_MODE_RECOVERY)
		msleep(2000);

	स_रखो(&qed_params, 0, माप(qed_params));
	qed_params.protocol = QED_PROTOCOL_ISCSI;
	qed_params.dp_module = qedi_qed_debug;
	qed_params.dp_level = dp_level;
	qed_params.is_vf = is_vf;
	qedi->cdev = qedi_ops->common->probe(pdev, &qed_params);
	अगर (!qedi->cdev) अणु
		अगर (mode == QEDI_MODE_RECOVERY && retry) अणु
			QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
				  "Retry %d initialize hardware\n", retry);
			retry--;
			जाओ retry_probe;
		पूर्ण

		rc = -ENODEV;
		QEDI_ERR(&qedi->dbg_ctx, "Cannot initialize hardware\n");
		जाओ मुक्त_host;
	पूर्ण

	set_bit(QEDI_ERR_ATTN_CLR_EN, &qedi->qedi_err_flags);
	set_bit(QEDI_ERR_IS_RECOVERABLE, &qedi->qedi_err_flags);
	atomic_set(&qedi->link_state, QEDI_LINK_DOWN);

	rc = qedi_ops->fill_dev_info(qedi->cdev, &qedi->dev_info);
	अगर (rc)
		जाओ मुक्त_host;

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
		  "dev_info: num_hwfns=%d affin_hwfn_idx=%d.\n",
		  qedi->dev_info.common.num_hwfns,
		  qedi_ops->common->get_affin_hwfn_idx(qedi->cdev));

	rc = qedi_set_iscsi_pf_param(qedi);
	अगर (rc) अणु
		rc = -ENOMEM;
		QEDI_ERR(&qedi->dbg_ctx,
			 "Set iSCSI pf param fail\n");
		जाओ मुक्त_host;
	पूर्ण

	qedi_ops->common->update_pf_params(qedi->cdev, &qedi->pf_params);

	rc = qedi_prepare_fp(qedi);
	अगर (rc) अणु
		QEDI_ERR(&qedi->dbg_ctx, "Cannot start slowpath.\n");
		जाओ मुक्त_pf_params;
	पूर्ण

	/* Start the Slowpath-process */
	स_रखो(&sp_params, 0, माप(काष्ठा qed_slowpath_params));
	sp_params.पूर्णांक_mode = QED_INT_MODE_MSIX;
	sp_params.drv_major = QEDI_DRIVER_MAJOR_VER;
	sp_params.drv_minor = QEDI_DRIVER_MINOR_VER;
	sp_params.drv_rev = QEDI_DRIVER_REV_VER;
	sp_params.drv_eng = QEDI_DRIVER_ENG_VER;
	strlcpy(sp_params.name, "qedi iSCSI", QED_DRV_VER_STR_SIZE);
	rc = qedi_ops->common->slowpath_start(qedi->cdev, &sp_params);
	अगर (rc) अणु
		QEDI_ERR(&qedi->dbg_ctx, "Cannot start slowpath\n");
		जाओ stop_hw;
	पूर्ण

	/* update_pf_params needs to be called beक्रमe and after slowpath
	 * start
	 */
	qedi_ops->common->update_pf_params(qedi->cdev, &qedi->pf_params);

	rc = qedi_setup_पूर्णांक(qedi);
	अगर (rc)
		जाओ stop_iscsi_func;

	qedi_ops->common->set_घातer_state(qedi->cdev, PCI_D0);

	/* Learn inक्रमmation crucial क्रम qedi to progress */
	rc = qedi_ops->fill_dev_info(qedi->cdev, &qedi->dev_info);
	अगर (rc)
		जाओ stop_iscsi_func;

	/* Record BDQ producer करोorbell addresses */
	qedi->bdq_primary_prod = qedi->dev_info.primary_dbq_rq_addr;
	qedi->bdq_secondary_prod = qedi->dev_info.secondary_bdq_rq_addr;
	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_DISC,
		  "BDQ primary_prod=%p secondary_prod=%p.\n",
		  qedi->bdq_primary_prod,
		  qedi->bdq_secondary_prod);

	/*
	 * We need to ग_लिखो the number of BDs in the BDQ we've pपुनः_स्मृतिated so
	 * the f/w will करो a prefetch and we'll get an unsolicited CQE when a
	 * packet arrives.
	 */
	qedi->bdq_prod_idx = QEDI_BDQ_NUM;
	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_DISC,
		  "Writing %d to primary and secondary BDQ doorbell registers.\n",
		  qedi->bdq_prod_idx);
	ग_लिखोw(qedi->bdq_prod_idx, qedi->bdq_primary_prod);
	पढ़ोw(qedi->bdq_primary_prod);
	ग_लिखोw(qedi->bdq_prod_idx, qedi->bdq_secondary_prod);
	पढ़ोw(qedi->bdq_secondary_prod);

	ether_addr_copy(qedi->mac, qedi->dev_info.common.hw_mac);
	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_DISC, "MAC address is %pM.\n",
		  qedi->mac);

	snम_लिखो(host_buf, माप(host_buf), "host_%d", qedi->shost->host_no);
	qedi_ops->common->set_name(qedi->cdev, host_buf);

	qedi_ops->रेजिस्टर_ops(qedi->cdev, &qedi_cb_ops, qedi);

	स_रखो(&params, 0, माप(params));
	params.mtu = DEF_PATH_MTU + IPV6_HDR_LEN + TCP_HDR_LEN;
	qedi->ll2_mtu = DEF_PATH_MTU;
	params.drop_ttl0_packets = 0;
	params.rx_vlan_stripping = 1;
	ether_addr_copy(params.ll2_mac_address, qedi->dev_info.common.hw_mac);

	अगर (mode != QEDI_MODE_RECOVERY) अणु
		/* set up rx path */
		INIT_LIST_HEAD(&qedi->ll2_skb_list);
		spin_lock_init(&qedi->ll2_lock);
		/* start qedi context */
		spin_lock_init(&qedi->hba_lock);
		spin_lock_init(&qedi->task_idx_lock);
		mutex_init(&qedi->stats_lock);
	पूर्ण
	qedi_ops->ll2->रेजिस्टर_cb_ops(qedi->cdev, &qedi_ll2_cb_ops, qedi);
	qedi_ops->ll2->start(qedi->cdev, &params);

	अगर (mode != QEDI_MODE_RECOVERY) अणु
		qedi->ll2_recv_thपढ़ो = kthपढ़ो_run(qedi_ll2_recv_thपढ़ो,
						    (व्योम *)qedi,
						    "qedi_ll2_thread");
	पूर्ण

	rc = qedi_ops->start(qedi->cdev, &qedi->tasks,
			     qedi, qedi_iscsi_event_cb);
	अगर (rc) अणु
		rc = -ENODEV;
		QEDI_ERR(&qedi->dbg_ctx, "Cannot start iSCSI function\n");
		जाओ stop_slowpath;
	पूर्ण

	task_start = qedi_get_task_mem(&qedi->tasks, 0);
	task_end = qedi_get_task_mem(&qedi->tasks, MAX_TID_BLOCKS_ISCSI - 1);
	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_DISC,
		  "Task context start=%p, end=%p block_size=%u.\n",
		   task_start, task_end, qedi->tasks.size);

	स_रखो(&link_params, 0, माप(link_params));
	link_params.link_up = true;
	rc = qedi_ops->common->set_link(qedi->cdev, &link_params);
	अगर (rc) अणु
		QEDI_WARN(&qedi->dbg_ctx, "Link set up failed.\n");
		atomic_set(&qedi->link_state, QEDI_LINK_DOWN);
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
	qedi_dbg_host_init(&qedi->dbg_ctx, qedi_debugfs_ops,
			   qedi_dbg_fops);
#पूर्ण_अगर
	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
		  "QLogic FastLinQ iSCSI Module qedi %s, FW %d.%d.%d.%d\n",
		  QEDI_MODULE_VERSION, FW_MAJOR_VERSION, FW_MINOR_VERSION,
		  FW_REVISION_VERSION, FW_ENGINEERING_VERSION);

	अगर (mode == QEDI_MODE_NORMAL) अणु
		अगर (iscsi_host_add(qedi->shost, &pdev->dev)) अणु
			QEDI_ERR(&qedi->dbg_ctx,
				 "Could not add iscsi host\n");
			rc = -ENOMEM;
			जाओ हटाओ_host;
		पूर्ण

		/* Allocate uio buffers */
		rc = qedi_alloc_uio_rings(qedi);
		अगर (rc) अणु
			QEDI_ERR(&qedi->dbg_ctx,
				 "UIO alloc ring failed err=%d\n", rc);
			जाओ हटाओ_host;
		पूर्ण

		rc = qedi_init_uio(qedi);
		अगर (rc) अणु
			QEDI_ERR(&qedi->dbg_ctx,
				 "UIO init failed, err=%d\n", rc);
			जाओ मुक्त_uio;
		पूर्ण

		/* host the array on iscsi_conn */
		rc = qedi_setup_cid_que(qedi);
		अगर (rc) अणु
			QEDI_ERR(&qedi->dbg_ctx,
				 "Could not setup cid que\n");
			जाओ मुक्त_uio;
		पूर्ण

		rc = qedi_cm_alloc_mem(qedi);
		अगर (rc) अणु
			QEDI_ERR(&qedi->dbg_ctx,
				 "Could not alloc cm memory\n");
			जाओ मुक्त_cid_que;
		पूर्ण

		rc = qedi_alloc_itt(qedi);
		अगर (rc) अणु
			QEDI_ERR(&qedi->dbg_ctx,
				 "Could not alloc itt memory\n");
			जाओ मुक्त_cid_que;
		पूर्ण

		प्र_लिखो(host_buf, "host_%d", qedi->shost->host_no);
		qedi->पंचांगf_thपढ़ो = create_singlethपढ़ो_workqueue(host_buf);
		अगर (!qedi->पंचांगf_thपढ़ो) अणु
			QEDI_ERR(&qedi->dbg_ctx,
				 "Unable to start tmf thread!\n");
			rc = -ENODEV;
			जाओ मुक्त_cid_que;
		पूर्ण

		प्र_लिखो(host_buf, "qedi_ofld%d", qedi->shost->host_no);
		qedi->offload_thपढ़ो = create_workqueue(host_buf);
		अगर (!qedi->offload_thपढ़ो) अणु
			QEDI_ERR(&qedi->dbg_ctx,
				 "Unable to start offload thread!\n");
			rc = -ENODEV;
			जाओ मुक्त_पंचांगf_thपढ़ो;
		पूर्ण

		INIT_DELAYED_WORK(&qedi->recovery_work, qedi_recovery_handler);
		INIT_DELAYED_WORK(&qedi->board_disable_work,
				  qedi_board_disable_work);

		/* F/w needs 1st task context memory entry क्रम perक्रमmance */
		set_bit(QEDI_RESERVE_TASK_ID, qedi->task_idx_map);
		atomic_set(&qedi->num_offloads, 0);

		अगर (qedi_setup_boot_info(qedi))
			QEDI_ERR(&qedi->dbg_ctx,
				 "No iSCSI boot target configured\n");

		rc = qedi_ops->common->update_drv_state(qedi->cdev, true);
		अगर (rc)
			QEDI_ERR(&qedi->dbg_ctx,
				 "Failed to send drv state to MFW\n");

	पूर्ण

	वापस 0;

मुक्त_पंचांगf_thपढ़ो:
	destroy_workqueue(qedi->पंचांगf_thपढ़ो);
मुक्त_cid_que:
	qedi_release_cid_que(qedi);
मुक्त_uio:
	qedi_मुक्त_uio(qedi->udev);
हटाओ_host:
#अगर_घोषित CONFIG_DEBUG_FS
	qedi_dbg_host_निकास(&qedi->dbg_ctx);
#पूर्ण_अगर
	iscsi_host_हटाओ(qedi->shost);
stop_iscsi_func:
	qedi_ops->stop(qedi->cdev);
stop_slowpath:
	qedi_ops->common->slowpath_stop(qedi->cdev);
stop_hw:
	qedi_ops->common->हटाओ(qedi->cdev);
मुक्त_pf_params:
	qedi_मुक्त_iscsi_pf_param(qedi);
मुक्त_host:
	iscsi_host_मुक्त(qedi->shost);
निकास_probe:
	वापस rc;
पूर्ण

अटल व्योम qedi_mark_conn_recovery(काष्ठा iscsi_cls_session *cls_session)
अणु
	काष्ठा iscsi_session *session = cls_session->dd_data;
	काष्ठा iscsi_conn *conn = session->leadconn;
	काष्ठा qedi_conn *qedi_conn = conn->dd_data;

	iscsi_conn_failure(qedi_conn->cls_conn->dd_data, ISCSI_ERR_CONN_FAILED);
पूर्ण

अटल व्योम qedi_recovery_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qedi_ctx *qedi =
			container_of(work, काष्ठा qedi_ctx, recovery_work.work);

	iscsi_host_क्रम_each_session(qedi->shost, qedi_mark_conn_recovery);

	/* Call common_ops->recovery_prolog to allow the MFW to quiesce
	 * any PCI transactions.
	 */
	qedi_ops->common->recovery_prolog(qedi->cdev);

	__qedi_हटाओ(qedi->pdev, QEDI_MODE_RECOVERY);
	__qedi_probe(qedi->pdev, QEDI_MODE_RECOVERY);
	clear_bit(QEDI_IN_RECOVERY, &qedi->flags);
पूर्ण

अटल पूर्णांक qedi_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	वापस __qedi_probe(pdev, QEDI_MODE_NORMAL);
पूर्ण

अटल व्योम qedi_हटाओ(काष्ठा pci_dev *pdev)
अणु
	__qedi_हटाओ(pdev, QEDI_MODE_NORMAL);
पूर्ण

अटल काष्ठा pci_device_id qedi_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, 0x165E) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, 0x8084) पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, qedi_pci_tbl);

अटल क्रमागत cpuhp_state qedi_cpuhp_state;

अटल काष्ठा pci_error_handlers qedi_err_handler = अणु
	.error_detected = qedi_io_error_detected,
पूर्ण;

अटल काष्ठा pci_driver qedi_pci_driver = अणु
	.name = QEDI_MODULE_NAME,
	.id_table = qedi_pci_tbl,
	.probe = qedi_probe,
	.हटाओ = qedi_हटाओ,
	.shutकरोwn = qedi_shutकरोwn,
	.err_handler = &qedi_err_handler,
पूर्ण;

अटल पूर्णांक __init qedi_init(व्योम)
अणु
	काष्ठा qedi_percpu_s *p;
	पूर्णांक cpu, rc = 0;

	qedi_ops = qed_get_iscsi_ops();
	अगर (!qedi_ops) अणु
		QEDI_ERR(शून्य, "Failed to get qed iSCSI operations\n");
		वापस -EINVAL;
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
	qedi_dbg_init("qedi");
#पूर्ण_अगर

	qedi_scsi_transport = iscsi_रेजिस्टर_transport(&qedi_iscsi_transport);
	अगर (!qedi_scsi_transport) अणु
		QEDI_ERR(शून्य, "Could not register qedi transport");
		rc = -ENOMEM;
		जाओ निकास_qedi_init_1;
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		p = &per_cpu(qedi_percpu, cpu);
		INIT_LIST_HEAD(&p->work_list);
		spin_lock_init(&p->p_work_lock);
		p->iothपढ़ो = शून्य;
	पूर्ण

	rc = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "scsi/qedi:online",
			       qedi_cpu_online, qedi_cpu_offline);
	अगर (rc < 0)
		जाओ निकास_qedi_init_2;
	qedi_cpuhp_state = rc;

	rc = pci_रेजिस्टर_driver(&qedi_pci_driver);
	अगर (rc) अणु
		QEDI_ERR(शून्य, "Failed to register driver\n");
		जाओ निकास_qedi_hp;
	पूर्ण

	वापस 0;

निकास_qedi_hp:
	cpuhp_हटाओ_state(qedi_cpuhp_state);
निकास_qedi_init_2:
	iscsi_unरेजिस्टर_transport(&qedi_iscsi_transport);
निकास_qedi_init_1:
#अगर_घोषित CONFIG_DEBUG_FS
	qedi_dbg_निकास();
#पूर्ण_अगर
	qed_put_iscsi_ops();
	वापस rc;
पूर्ण

अटल व्योम __निकास qedi_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&qedi_pci_driver);
	cpuhp_हटाओ_state(qedi_cpuhp_state);
	iscsi_unरेजिस्टर_transport(&qedi_iscsi_transport);

#अगर_घोषित CONFIG_DEBUG_FS
	qedi_dbg_निकास();
#पूर्ण_अगर
	qed_put_iscsi_ops();
पूर्ण

MODULE_DESCRIPTION("QLogic FastLinQ 4xxxx iSCSI Module");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("QLogic Corporation");
MODULE_VERSION(QEDI_MODULE_VERSION);
module_init(qedi_init);
module_निकास(qedi_cleanup);
