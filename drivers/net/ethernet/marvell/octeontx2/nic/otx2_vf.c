<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell OcteonTx2 RVU Virtual Function ethernet driver */

#समावेश <linux/etherdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "otx2_common.h"
#समावेश "otx2_reg.h"
#समावेश "cn10k.h"

#घोषणा DRV_NAME	"rvu_nicvf"
#घोषणा DRV_STRING	"Marvell RVU NIC Virtual Function Driver"

अटल स्थिर काष्ठा pci_device_id otx2_vf_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, PCI_DEVID_OCTEONTX2_RVU_AFVF) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, PCI_DEVID_OCTEONTX2_RVU_VF) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_AUTHOR("Sunil Goutham <sgoutham@marvell.com>");
MODULE_DESCRIPTION(DRV_STRING);
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(pci, otx2_vf_id_table);

/* RVU VF Interrupt Vector Enumeration */
क्रमागत अणु
	RVU_VF_INT_VEC_MBOX = 0x0,
पूर्ण;

अटल व्योम otx2vf_process_vfaf_mbox_msg(काष्ठा otx2_nic *vf,
					 काष्ठा mbox_msghdr *msg)
अणु
	अगर (msg->id >= MBOX_MSG_MAX) अणु
		dev_err(vf->dev,
			"Mbox msg with unknown ID %d\n", msg->id);
		वापस;
	पूर्ण

	अगर (msg->sig != OTX2_MBOX_RSP_SIG) अणु
		dev_err(vf->dev,
			"Mbox msg with wrong signature %x, ID %d\n",
			msg->sig, msg->id);
		वापस;
	पूर्ण

	अगर (msg->rc == MBOX_MSG_INVALID) अणु
		dev_err(vf->dev,
			"PF/AF says the sent msg(s) %d were invalid\n",
			msg->id);
		वापस;
	पूर्ण

	चयन (msg->id) अणु
	हाल MBOX_MSG_READY:
		vf->pcअगरunc = msg->pcअगरunc;
		अवरोध;
	हाल MBOX_MSG_MSIX_OFFSET:
		mbox_handler_msix_offset(vf, (काष्ठा msix_offset_rsp *)msg);
		अवरोध;
	हाल MBOX_MSG_NPA_LF_ALLOC:
		mbox_handler_npa_lf_alloc(vf, (काष्ठा npa_lf_alloc_rsp *)msg);
		अवरोध;
	हाल MBOX_MSG_NIX_LF_ALLOC:
		mbox_handler_nix_lf_alloc(vf, (काष्ठा nix_lf_alloc_rsp *)msg);
		अवरोध;
	हाल MBOX_MSG_NIX_TXSCH_ALLOC:
		mbox_handler_nix_txsch_alloc(vf,
					     (काष्ठा nix_txsch_alloc_rsp *)msg);
		अवरोध;
	हाल MBOX_MSG_NIX_BP_ENABLE:
		mbox_handler_nix_bp_enable(vf, (काष्ठा nix_bp_cfg_rsp *)msg);
		अवरोध;
	शेष:
		अगर (msg->rc)
			dev_err(vf->dev,
				"Mbox msg response has err %d, ID %d\n",
				msg->rc, msg->id);
	पूर्ण
पूर्ण

अटल व्योम otx2vf_vfaf_mbox_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा otx2_mbox_dev *mdev;
	काष्ठा mbox_hdr *rsp_hdr;
	काष्ठा mbox_msghdr *msg;
	काष्ठा otx2_mbox *mbox;
	काष्ठा mbox *af_mbox;
	पूर्णांक offset, id;

	af_mbox = container_of(work, काष्ठा mbox, mbox_wrk);
	mbox = &af_mbox->mbox;
	mdev = &mbox->dev[0];
	rsp_hdr = (काष्ठा mbox_hdr *)(mdev->mbase + mbox->rx_start);
	अगर (af_mbox->num_msgs == 0)
		वापस;
	offset = mbox->rx_start + ALIGN(माप(*rsp_hdr), MBOX_MSG_ALIGN);

	क्रम (id = 0; id < af_mbox->num_msgs; id++) अणु
		msg = (काष्ठा mbox_msghdr *)(mdev->mbase + offset);
		otx2vf_process_vfaf_mbox_msg(af_mbox->pfvf, msg);
		offset = mbox->rx_start + msg->next_msgoff;
		अगर (mdev->msgs_acked == (af_mbox->num_msgs - 1))
			__otx2_mbox_reset(mbox, 0);
		mdev->msgs_acked++;
	पूर्ण
पूर्ण

अटल पूर्णांक otx2vf_process_mbox_msg_up(काष्ठा otx2_nic *vf,
				      काष्ठा mbox_msghdr *req)
अणु
	काष्ठा msg_rsp *rsp;
	पूर्णांक err;

	/* Check अगर valid, अगर not reply with a invalid msg */
	अगर (req->sig != OTX2_MBOX_REQ_SIG) अणु
		otx2_reply_invalid_msg(&vf->mbox.mbox_up, 0, 0, req->id);
		वापस -ENODEV;
	पूर्ण

	चयन (req->id) अणु
	हाल MBOX_MSG_CGX_LINK_EVENT:
		rsp = (काष्ठा msg_rsp *)otx2_mbox_alloc_msg(
						&vf->mbox.mbox_up, 0,
						माप(काष्ठा msg_rsp));
		अगर (!rsp)
			वापस -ENOMEM;

		rsp->hdr.id = MBOX_MSG_CGX_LINK_EVENT;
		rsp->hdr.sig = OTX2_MBOX_RSP_SIG;
		rsp->hdr.pcअगरunc = 0;
		rsp->hdr.rc = 0;
		err = otx2_mbox_up_handler_cgx_link_event(
				vf, (काष्ठा cgx_link_info_msg *)req, rsp);
		वापस err;
	शेष:
		otx2_reply_invalid_msg(&vf->mbox.mbox_up, 0, 0, req->id);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम otx2vf_vfaf_mbox_up_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा otx2_mbox_dev *mdev;
	काष्ठा mbox_hdr *rsp_hdr;
	काष्ठा mbox_msghdr *msg;
	काष्ठा otx2_mbox *mbox;
	काष्ठा mbox *vf_mbox;
	काष्ठा otx2_nic *vf;
	पूर्णांक offset, id;

	vf_mbox = container_of(work, काष्ठा mbox, mbox_up_wrk);
	vf = vf_mbox->pfvf;
	mbox = &vf_mbox->mbox_up;
	mdev = &mbox->dev[0];

	rsp_hdr = (काष्ठा mbox_hdr *)(mdev->mbase + mbox->rx_start);
	अगर (vf_mbox->up_num_msgs == 0)
		वापस;

	offset = mbox->rx_start + ALIGN(माप(*rsp_hdr), MBOX_MSG_ALIGN);

	क्रम (id = 0; id < vf_mbox->up_num_msgs; id++) अणु
		msg = (काष्ठा mbox_msghdr *)(mdev->mbase + offset);
		otx2vf_process_mbox_msg_up(vf, msg);
		offset = mbox->rx_start + msg->next_msgoff;
	पूर्ण

	otx2_mbox_msg_send(mbox, 0);
पूर्ण

अटल irqवापस_t otx2vf_vfaf_mbox_पूर्णांकr_handler(पूर्णांक irq, व्योम *vf_irq)
अणु
	काष्ठा otx2_nic *vf = (काष्ठा otx2_nic *)vf_irq;
	काष्ठा otx2_mbox_dev *mdev;
	काष्ठा otx2_mbox *mbox;
	काष्ठा mbox_hdr *hdr;

	/* Clear the IRQ */
	otx2_ग_लिखो64(vf, RVU_VF_INT, BIT_ULL(0));

	/* Read latest mbox data */
	smp_rmb();

	/* Check क्रम PF => VF response messages */
	mbox = &vf->mbox.mbox;
	mdev = &mbox->dev[0];
	otx2_sync_mbox_bbuf(mbox, 0);

	trace_otx2_msg_पूर्णांकerrupt(mbox->pdev, "PF to VF", BIT_ULL(0));

	hdr = (काष्ठा mbox_hdr *)(mdev->mbase + mbox->rx_start);
	अगर (hdr->num_msgs) अणु
		vf->mbox.num_msgs = hdr->num_msgs;
		hdr->num_msgs = 0;
		स_रखो(mbox->hwbase + mbox->rx_start, 0,
		       ALIGN(माप(काष्ठा mbox_hdr), माप(u64)));
		queue_work(vf->mbox_wq, &vf->mbox.mbox_wrk);
	पूर्ण
	/* Check क्रम PF => VF notअगरication messages */
	mbox = &vf->mbox.mbox_up;
	mdev = &mbox->dev[0];
	otx2_sync_mbox_bbuf(mbox, 0);

	hdr = (काष्ठा mbox_hdr *)(mdev->mbase + mbox->rx_start);
	अगर (hdr->num_msgs) अणु
		vf->mbox.up_num_msgs = hdr->num_msgs;
		hdr->num_msgs = 0;
		स_रखो(mbox->hwbase + mbox->rx_start, 0,
		       ALIGN(माप(काष्ठा mbox_hdr), माप(u64)));
		queue_work(vf->mbox_wq, &vf->mbox.mbox_up_wrk);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम otx2vf_disable_mbox_पूर्णांकr(काष्ठा otx2_nic *vf)
अणु
	पूर्णांक vector = pci_irq_vector(vf->pdev, RVU_VF_INT_VEC_MBOX);

	/* Disable VF => PF mailbox IRQ */
	otx2_ग_लिखो64(vf, RVU_VF_INT_ENA_W1C, BIT_ULL(0));
	मुक्त_irq(vector, vf);
पूर्ण

अटल पूर्णांक otx2vf_रेजिस्टर_mbox_पूर्णांकr(काष्ठा otx2_nic *vf, bool probe_pf)
अणु
	काष्ठा otx2_hw *hw = &vf->hw;
	काष्ठा msg_req *req;
	अक्षर *irq_name;
	पूर्णांक err;

	/* Register mailbox पूर्णांकerrupt handler */
	irq_name = &hw->irq_name[RVU_VF_INT_VEC_MBOX * NAME_SIZE];
	snम_लिखो(irq_name, NAME_SIZE, "RVUVFAF Mbox");
	err = request_irq(pci_irq_vector(vf->pdev, RVU_VF_INT_VEC_MBOX),
			  otx2vf_vfaf_mbox_पूर्णांकr_handler, 0, irq_name, vf);
	अगर (err) अणु
		dev_err(vf->dev,
			"RVUPF: IRQ registration failed for VFAF mbox irq\n");
		वापस err;
	पूर्ण

	/* Enable mailbox पूर्णांकerrupt क्रम msgs coming from PF.
	 * First clear to aव्योम spurious पूर्णांकerrupts, अगर any.
	 */
	otx2_ग_लिखो64(vf, RVU_VF_INT, BIT_ULL(0));
	otx2_ग_लिखो64(vf, RVU_VF_INT_ENA_W1S, BIT_ULL(0));

	अगर (!probe_pf)
		वापस 0;

	/* Check mailbox communication with PF */
	req = otx2_mbox_alloc_msg_पढ़ोy(&vf->mbox);
	अगर (!req) अणु
		otx2vf_disable_mbox_पूर्णांकr(vf);
		वापस -ENOMEM;
	पूर्ण

	err = otx2_sync_mbox_msg(&vf->mbox);
	अगर (err) अणु
		dev_warn(vf->dev,
			 "AF not responding to mailbox, deferring probe\n");
		otx2vf_disable_mbox_पूर्णांकr(vf);
		वापस -EPROBE_DEFER;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम otx2vf_vfaf_mbox_destroy(काष्ठा otx2_nic *vf)
अणु
	काष्ठा mbox *mbox = &vf->mbox;

	अगर (vf->mbox_wq) अणु
		flush_workqueue(vf->mbox_wq);
		destroy_workqueue(vf->mbox_wq);
		vf->mbox_wq = शून्य;
	पूर्ण

	अगर (mbox->mbox.hwbase && !test_bit(CN10K_MBOX, &vf->hw.cap_flag))
		iounmap((व्योम __iomem *)mbox->mbox.hwbase);

	otx2_mbox_destroy(&mbox->mbox);
	otx2_mbox_destroy(&mbox->mbox_up);
पूर्ण

अटल पूर्णांक otx2vf_vfaf_mbox_init(काष्ठा otx2_nic *vf)
अणु
	काष्ठा mbox *mbox = &vf->mbox;
	व्योम __iomem *hwbase;
	पूर्णांक err;

	mbox->pfvf = vf;
	vf->mbox_wq = alloc_workqueue("otx2_vfaf_mailbox",
				      WQ_UNBOUND | WQ_HIGHPRI |
				      WQ_MEM_RECLAIM, 1);
	अगर (!vf->mbox_wq)
		वापस -ENOMEM;

	अगर (test_bit(CN10K_MBOX, &vf->hw.cap_flag)) अणु
		/* For cn10k platक्रमm, VF mailbox region is in its BAR2
		 * रेजिस्टर space
		 */
		hwbase = vf->reg_base + RVU_VF_MBOX_REGION;
	पूर्ण अन्यथा अणु
		/* Mailbox is a reserved memory (in RAM) region shared between
		 * admin function (i.e PF0) and this VF, shouldn't be mapped as
		 * device memory to allow unaligned accesses.
		 */
		hwbase = ioremap_wc(pci_resource_start(vf->pdev,
						       PCI_MBOX_BAR_NUM),
				    pci_resource_len(vf->pdev,
						     PCI_MBOX_BAR_NUM));
		अगर (!hwbase) अणु
			dev_err(vf->dev, "Unable to map VFAF mailbox region\n");
			err = -ENOMEM;
			जाओ निकास;
		पूर्ण
	पूर्ण

	err = otx2_mbox_init(&mbox->mbox, hwbase, vf->pdev, vf->reg_base,
			     MBOX_सूची_VFPF, 1);
	अगर (err)
		जाओ निकास;

	err = otx2_mbox_init(&mbox->mbox_up, hwbase, vf->pdev, vf->reg_base,
			     MBOX_सूची_VFPF_UP, 1);
	अगर (err)
		जाओ निकास;

	err = otx2_mbox_bbuf_init(mbox, vf->pdev);
	अगर (err)
		जाओ निकास;

	INIT_WORK(&mbox->mbox_wrk, otx2vf_vfaf_mbox_handler);
	INIT_WORK(&mbox->mbox_up_wrk, otx2vf_vfaf_mbox_up_handler);
	mutex_init(&mbox->lock);

	वापस 0;
निकास:
	अगर (hwbase && !test_bit(CN10K_MBOX, &vf->hw.cap_flag))
		iounmap(hwbase);
	destroy_workqueue(vf->mbox_wq);
	वापस err;
पूर्ण

अटल पूर्णांक otx2vf_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा otx2_nic *vf;
	पूर्णांक err;

	err = otx2_खोलो(netdev);
	अगर (err)
		वापस err;

	/* LBKs करो not receive link events so tell everyone we are up here */
	vf = netdev_priv(netdev);
	अगर (is_otx2_lbkvf(vf->pdev)) अणु
		pr_info("%s NIC Link is UP\n", netdev->name);
		netअगर_carrier_on(netdev);
		netअगर_tx_start_all_queues(netdev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक otx2vf_stop(काष्ठा net_device *netdev)
अणु
	वापस otx2_stop(netdev);
पूर्ण

अटल netdev_tx_t otx2vf_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा otx2_nic *vf = netdev_priv(netdev);
	पूर्णांक qidx = skb_get_queue_mapping(skb);
	काष्ठा otx2_snd_queue *sq;
	काष्ठा netdev_queue *txq;

	sq = &vf->qset.sq[qidx];
	txq = netdev_get_tx_queue(netdev, qidx);

	अगर (!otx2_sq_append_skb(netdev, sq, skb, qidx)) अणु
		netअगर_tx_stop_queue(txq);

		/* Check again, inहाल SQBs got मुक्तd up */
		smp_mb();
		अगर (((sq->num_sqbs - *sq->aura_fc_addr) * sq->sqe_per_sqb)
							> sq->sqe_thresh)
			netअगर_tx_wake_queue(txq);

		वापस NETDEV_TX_BUSY;
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक otx2vf_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	bool अगर_up = netअगर_running(netdev);
	पूर्णांक err = 0;

	अगर (अगर_up)
		otx2vf_stop(netdev);

	netdev_info(netdev, "Changing MTU from %d to %d\n",
		    netdev->mtu, new_mtu);
	netdev->mtu = new_mtu;

	अगर (अगर_up)
		err = otx2vf_खोलो(netdev);

	वापस err;
पूर्ण

अटल व्योम otx2vf_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा otx2_nic *vf = container_of(work, काष्ठा otx2_nic, reset_task);

	rtnl_lock();

	अगर (netअगर_running(vf->netdev)) अणु
		otx2vf_stop(vf->netdev);
		vf->reset_count++;
		otx2vf_खोलो(vf->netdev);
	पूर्ण

	rtnl_unlock();
पूर्ण

अटल स्थिर काष्ठा net_device_ops otx2vf_netdev_ops = अणु
	.nकरो_खोलो = otx2vf_खोलो,
	.nकरो_stop = otx2vf_stop,
	.nकरो_start_xmit = otx2vf_xmit,
	.nकरो_set_mac_address = otx2_set_mac_address,
	.nकरो_change_mtu = otx2vf_change_mtu,
	.nकरो_get_stats64 = otx2_get_stats64,
	.nकरो_tx_समयout = otx2_tx_समयout,
पूर्ण;

अटल पूर्णांक otx2vf_पुनः_स्मृति_msix_vectors(काष्ठा otx2_nic *vf)
अणु
	काष्ठा otx2_hw *hw = &vf->hw;
	पूर्णांक num_vec, err;

	num_vec = hw->nix_msixoff;
	num_vec += NIX_LF_CINT_VEC_START + hw->max_queues;

	otx2vf_disable_mbox_पूर्णांकr(vf);
	pci_मुक्त_irq_vectors(hw->pdev);
	err = pci_alloc_irq_vectors(hw->pdev, num_vec, num_vec, PCI_IRQ_MSIX);
	अगर (err < 0) अणु
		dev_err(vf->dev, "%s: Failed to realloc %d IRQ vectors\n",
			__func__, num_vec);
		वापस err;
	पूर्ण

	वापस otx2vf_रेजिस्टर_mbox_पूर्णांकr(vf, false);
पूर्ण

अटल पूर्णांक otx2vf_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक num_vec = pci_msix_vec_count(pdev);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा net_device *netdev;
	काष्ठा otx2_nic *vf;
	काष्ठा otx2_hw *hw;
	पूर्णांक err, qcount;

	err = pcim_enable_device(pdev);
	अगर (err) अणु
		dev_err(dev, "Failed to enable PCI device\n");
		वापस err;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		dev_err(dev, "PCI request regions failed 0x%x\n", err);
		वापस err;
	पूर्ण

	err = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(48));
	अगर (err) अणु
		dev_err(dev, "DMA mask config failed, abort\n");
		जाओ err_release_regions;
	पूर्ण

	pci_set_master(pdev);

	qcount = num_online_cpus();
	netdev = alloc_etherdev_mqs(माप(*vf), qcount, qcount);
	अगर (!netdev) अणु
		err = -ENOMEM;
		जाओ err_release_regions;
	पूर्ण

	pci_set_drvdata(pdev, netdev);
	SET_NETDEV_DEV(netdev, &pdev->dev);
	vf = netdev_priv(netdev);
	vf->netdev = netdev;
	vf->pdev = pdev;
	vf->dev = dev;
	vf->iommu_करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);

	vf->flags |= OTX2_FLAG_INTF_DOWN;
	hw = &vf->hw;
	hw->pdev = vf->pdev;
	hw->rx_queues = qcount;
	hw->tx_queues = qcount;
	hw->max_queues = qcount;

	hw->irq_name = devm_kदो_स्मृति_array(&hw->pdev->dev, num_vec, NAME_SIZE,
					  GFP_KERNEL);
	अगर (!hw->irq_name) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_netdev;
	पूर्ण

	hw->affinity_mask = devm_kसुस्मृति(&hw->pdev->dev, num_vec,
					 माप(cpumask_var_t), GFP_KERNEL);
	अगर (!hw->affinity_mask) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_netdev;
	पूर्ण

	err = pci_alloc_irq_vectors(hw->pdev, num_vec, num_vec, PCI_IRQ_MSIX);
	अगर (err < 0) अणु
		dev_err(dev, "%s: Failed to alloc %d IRQ vectors\n",
			__func__, num_vec);
		जाओ err_मुक्त_netdev;
	पूर्ण

	vf->reg_base = pcim_iomap(pdev, PCI_CFG_REG_BAR_NUM, 0);
	अगर (!vf->reg_base) अणु
		dev_err(dev, "Unable to map physical function CSRs, aborting\n");
		err = -ENOMEM;
		जाओ err_मुक्त_irq_vectors;
	पूर्ण

	otx2_setup_dev_hw_settings(vf);
	/* Init VF <=> PF mailbox stuff */
	err = otx2vf_vfaf_mbox_init(vf);
	अगर (err)
		जाओ err_मुक्त_irq_vectors;

	/* Register mailbox पूर्णांकerrupt */
	err = otx2vf_रेजिस्टर_mbox_पूर्णांकr(vf, true);
	अगर (err)
		जाओ err_mbox_destroy;

	/* Request AF to attach NPA and LIX LFs to this AF */
	err = otx2_attach_npa_nix(vf);
	अगर (err)
		जाओ err_disable_mbox_पूर्णांकr;

	err = otx2vf_पुनः_स्मृति_msix_vectors(vf);
	अगर (err)
		जाओ err_mbox_destroy;

	err = otx2_set_real_num_queues(netdev, qcount, qcount);
	अगर (err)
		जाओ err_detach_rsrc;

	err = cn10k_vf_lmtst_init(vf);
	अगर (err)
		जाओ err_detach_rsrc;

	/* Assign शेष mac address */
	otx2_get_mac_from_af(netdev);

	netdev->hw_features = NETIF_F_RXCSUM | NETIF_F_IP_CSUM |
			      NETIF_F_IPV6_CSUM | NETIF_F_RXHASH |
			      NETIF_F_SG | NETIF_F_TSO | NETIF_F_TSO6 |
			      NETIF_F_GSO_UDP_L4;
	netdev->features = netdev->hw_features;
	/* Support TSO on tag पूर्णांकerface */
	netdev->vlan_features |= netdev->features;
	netdev->hw_features  |= NETIF_F_HW_VLAN_CTAG_TX |
				NETIF_F_HW_VLAN_STAG_TX;
	netdev->features |= netdev->hw_features;

	netdev->gso_max_segs = OTX2_MAX_GSO_SEGS;
	netdev->watchकरोg_समयo = OTX2_TX_TIMEOUT;

	netdev->netdev_ops = &otx2vf_netdev_ops;

	/* MTU range: 68 - 9190 */
	netdev->min_mtu = OTX2_MIN_MTU;
	netdev->max_mtu = otx2_get_max_mtu(vf);

	INIT_WORK(&vf->reset_task, otx2vf_reset_task);

	/* To distinguish, क्रम LBK VFs set netdev name explicitly */
	अगर (is_otx2_lbkvf(vf->pdev)) अणु
		पूर्णांक n;

		n = (vf->pcअगरunc >> RVU_PFVF_FUNC_SHIFT) & RVU_PFVF_FUNC_MASK;
		/* Need to subtract 1 to get proper VF number */
		n -= 1;
		snम_लिखो(netdev->name, माप(netdev->name), "lbk%d", n);
	पूर्ण

	err = रेजिस्टर_netdev(netdev);
	अगर (err) अणु
		dev_err(dev, "Failed to register netdevice\n");
		जाओ err_detach_rsrc;
	पूर्ण

	otx2vf_set_ethtool_ops(netdev);

	/* Enable छोड़ो frames by शेष */
	vf->flags |= OTX2_FLAG_RX_PAUSE_ENABLED;
	vf->flags |= OTX2_FLAG_TX_PAUSE_ENABLED;

	वापस 0;

err_detach_rsrc:
	अगर (hw->lmt_base)
		iounmap(hw->lmt_base);
	otx2_detach_resources(&vf->mbox);
err_disable_mbox_पूर्णांकr:
	otx2vf_disable_mbox_पूर्णांकr(vf);
err_mbox_destroy:
	otx2vf_vfaf_mbox_destroy(vf);
err_मुक्त_irq_vectors:
	pci_मुक्त_irq_vectors(hw->pdev);
err_मुक्त_netdev:
	pci_set_drvdata(pdev, शून्य);
	मुक्त_netdev(netdev);
err_release_regions:
	pci_release_regions(pdev);
	वापस err;
पूर्ण

अटल व्योम otx2vf_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा otx2_nic *vf;

	अगर (!netdev)
		वापस;

	vf = netdev_priv(netdev);

	cancel_work_sync(&vf->reset_task);
	unरेजिस्टर_netdev(netdev);
	otx2vf_disable_mbox_पूर्णांकr(vf);
	otx2_detach_resources(&vf->mbox);

	अगर (vf->hw.lmt_base)
		iounmap(vf->hw.lmt_base);

	otx2vf_vfaf_mbox_destroy(vf);
	pci_मुक्त_irq_vectors(vf->pdev);
	pci_set_drvdata(pdev, शून्य);
	मुक्त_netdev(netdev);

	pci_release_regions(pdev);
पूर्ण

अटल काष्ठा pci_driver otx2vf_driver = अणु
	.name = DRV_NAME,
	.id_table = otx2_vf_id_table,
	.probe = otx2vf_probe,
	.हटाओ = otx2vf_हटाओ,
	.shutकरोwn = otx2vf_हटाओ,
पूर्ण;

अटल पूर्णांक __init otx2vf_init_module(व्योम)
अणु
	pr_info("%s: %s\n", DRV_NAME, DRV_STRING);

	वापस pci_रेजिस्टर_driver(&otx2vf_driver);
पूर्ण

अटल व्योम __निकास otx2vf_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&otx2vf_driver);
पूर्ण

module_init(otx2vf_init_module);
module_निकास(otx2vf_cleanup_module);
