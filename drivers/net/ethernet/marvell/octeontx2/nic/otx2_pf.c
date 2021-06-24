<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell OcteonTx2 RVU Physical Function ethernet driver
 *
 * Copyright (C) 2020 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/iommu.h>
#समावेश <net/ip.h>

#समावेश "otx2_reg.h"
#समावेश "otx2_common.h"
#समावेश "otx2_txrx.h"
#समावेश "otx2_struct.h"
#समावेश "otx2_ptp.h"
#समावेश "cn10k.h"
#समावेश <rvu_trace.h>

#घोषणा DRV_NAME	"rvu_nicpf"
#घोषणा DRV_STRING	"Marvell RVU NIC Physical Function Driver"

/* Supported devices */
अटल स्थिर काष्ठा pci_device_id otx2_pf_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, PCI_DEVID_OCTEONTX2_RVU_PF) पूर्ण,
	अणु 0, पूर्ण  /* end of table */
पूर्ण;

MODULE_AUTHOR("Sunil Goutham <sgoutham@marvell.com>");
MODULE_DESCRIPTION(DRV_STRING);
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(pci, otx2_pf_id_table);

क्रमागत अणु
	TYPE_PFAF,
	TYPE_PFVF,
पूर्ण;

अटल पूर्णांक otx2_config_hw_tx_tstamp(काष्ठा otx2_nic *pfvf, bool enable);
अटल पूर्णांक otx2_config_hw_rx_tstamp(काष्ठा otx2_nic *pfvf, bool enable);

अटल पूर्णांक otx2_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	bool अगर_up = netअगर_running(netdev);
	पूर्णांक err = 0;

	अगर (अगर_up)
		otx2_stop(netdev);

	netdev_info(netdev, "Changing MTU from %d to %d\n",
		    netdev->mtu, new_mtu);
	netdev->mtu = new_mtu;

	अगर (अगर_up)
		err = otx2_खोलो(netdev);

	वापस err;
पूर्ण

अटल व्योम otx2_disable_flr_me_पूर्णांकr(काष्ठा otx2_nic *pf)
अणु
	पूर्णांक irq, vfs = pf->total_vfs;

	/* Disable VFs ME पूर्णांकerrupts */
	otx2_ग_लिखो64(pf, RVU_PF_VFME_INT_ENA_W1CX(0), INTR_MASK(vfs));
	irq = pci_irq_vector(pf->pdev, RVU_PF_INT_VEC_VFME0);
	मुक्त_irq(irq, pf);

	/* Disable VFs FLR पूर्णांकerrupts */
	otx2_ग_लिखो64(pf, RVU_PF_VFFLR_INT_ENA_W1CX(0), INTR_MASK(vfs));
	irq = pci_irq_vector(pf->pdev, RVU_PF_INT_VEC_VFFLR0);
	मुक्त_irq(irq, pf);

	अगर (vfs <= 64)
		वापस;

	otx2_ग_लिखो64(pf, RVU_PF_VFME_INT_ENA_W1CX(1), INTR_MASK(vfs - 64));
	irq = pci_irq_vector(pf->pdev, RVU_PF_INT_VEC_VFME1);
	मुक्त_irq(irq, pf);

	otx2_ग_लिखो64(pf, RVU_PF_VFFLR_INT_ENA_W1CX(1), INTR_MASK(vfs - 64));
	irq = pci_irq_vector(pf->pdev, RVU_PF_INT_VEC_VFFLR1);
	मुक्त_irq(irq, pf);
पूर्ण

अटल व्योम otx2_flr_wq_destroy(काष्ठा otx2_nic *pf)
अणु
	अगर (!pf->flr_wq)
		वापस;
	destroy_workqueue(pf->flr_wq);
	pf->flr_wq = शून्य;
	devm_kमुक्त(pf->dev, pf->flr_wrk);
पूर्ण

अटल व्योम otx2_flr_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा flr_work *flrwork = container_of(work, काष्ठा flr_work, work);
	काष्ठा otx2_nic *pf = flrwork->pf;
	काष्ठा mbox *mbox = &pf->mbox;
	काष्ठा msg_req *req;
	पूर्णांक vf, reg = 0;

	vf = flrwork - pf->flr_wrk;

	mutex_lock(&mbox->lock);
	req = otx2_mbox_alloc_msg_vf_flr(mbox);
	अगर (!req) अणु
		mutex_unlock(&mbox->lock);
		वापस;
	पूर्ण
	req->hdr.pcअगरunc &= RVU_PFVF_FUNC_MASK;
	req->hdr.pcअगरunc |= (vf + 1) & RVU_PFVF_FUNC_MASK;

	अगर (!otx2_sync_mbox_msg(&pf->mbox)) अणु
		अगर (vf >= 64) अणु
			reg = 1;
			vf = vf - 64;
		पूर्ण
		/* clear transcation pending bit */
		otx2_ग_लिखो64(pf, RVU_PF_VFTRPENDX(reg), BIT_ULL(vf));
		otx2_ग_लिखो64(pf, RVU_PF_VFFLR_INT_ENA_W1SX(reg), BIT_ULL(vf));
	पूर्ण

	mutex_unlock(&mbox->lock);
पूर्ण

अटल irqवापस_t otx2_pf_flr_पूर्णांकr_handler(पूर्णांक irq, व्योम *pf_irq)
अणु
	काष्ठा otx2_nic *pf = (काष्ठा otx2_nic *)pf_irq;
	पूर्णांक reg, dev, vf, start_vf, num_reg = 1;
	u64 पूर्णांकr;

	अगर (pf->total_vfs > 64)
		num_reg = 2;

	क्रम (reg = 0; reg < num_reg; reg++) अणु
		पूर्णांकr = otx2_पढ़ो64(pf, RVU_PF_VFFLR_INTX(reg));
		अगर (!पूर्णांकr)
			जारी;
		start_vf = 64 * reg;
		क्रम (vf = 0; vf < 64; vf++) अणु
			अगर (!(पूर्णांकr & BIT_ULL(vf)))
				जारी;
			dev = vf + start_vf;
			queue_work(pf->flr_wq, &pf->flr_wrk[dev].work);
			/* Clear पूर्णांकerrupt */
			otx2_ग_लिखो64(pf, RVU_PF_VFFLR_INTX(reg), BIT_ULL(vf));
			/* Disable the पूर्णांकerrupt */
			otx2_ग_लिखो64(pf, RVU_PF_VFFLR_INT_ENA_W1CX(reg),
				     BIT_ULL(vf));
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t otx2_pf_me_पूर्णांकr_handler(पूर्णांक irq, व्योम *pf_irq)
अणु
	काष्ठा otx2_nic *pf = (काष्ठा otx2_nic *)pf_irq;
	पूर्णांक vf, reg, num_reg = 1;
	u64 पूर्णांकr;

	अगर (pf->total_vfs > 64)
		num_reg = 2;

	क्रम (reg = 0; reg < num_reg; reg++) अणु
		पूर्णांकr = otx2_पढ़ो64(pf, RVU_PF_VFME_INTX(reg));
		अगर (!पूर्णांकr)
			जारी;
		क्रम (vf = 0; vf < 64; vf++) अणु
			अगर (!(पूर्णांकr & BIT_ULL(vf)))
				जारी;
			/* clear trpend bit */
			otx2_ग_लिखो64(pf, RVU_PF_VFTRPENDX(reg), BIT_ULL(vf));
			/* clear पूर्णांकerrupt */
			otx2_ग_लिखो64(pf, RVU_PF_VFME_INTX(reg), BIT_ULL(vf));
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक otx2_रेजिस्टर_flr_me_पूर्णांकr(काष्ठा otx2_nic *pf, पूर्णांक numvfs)
अणु
	काष्ठा otx2_hw *hw = &pf->hw;
	अक्षर *irq_name;
	पूर्णांक ret;

	/* Register ME पूर्णांकerrupt handler*/
	irq_name = &hw->irq_name[RVU_PF_INT_VEC_VFME0 * NAME_SIZE];
	snम_लिखो(irq_name, NAME_SIZE, "RVUPF%d_ME0", rvu_get_pf(pf->pcअगरunc));
	ret = request_irq(pci_irq_vector(pf->pdev, RVU_PF_INT_VEC_VFME0),
			  otx2_pf_me_पूर्णांकr_handler, 0, irq_name, pf);
	अगर (ret) अणु
		dev_err(pf->dev,
			"RVUPF: IRQ registration failed for ME0\n");
	पूर्ण

	/* Register FLR पूर्णांकerrupt handler */
	irq_name = &hw->irq_name[RVU_PF_INT_VEC_VFFLR0 * NAME_SIZE];
	snम_लिखो(irq_name, NAME_SIZE, "RVUPF%d_FLR0", rvu_get_pf(pf->pcअगरunc));
	ret = request_irq(pci_irq_vector(pf->pdev, RVU_PF_INT_VEC_VFFLR0),
			  otx2_pf_flr_पूर्णांकr_handler, 0, irq_name, pf);
	अगर (ret) अणु
		dev_err(pf->dev,
			"RVUPF: IRQ registration failed for FLR0\n");
		वापस ret;
	पूर्ण

	अगर (numvfs > 64) अणु
		irq_name = &hw->irq_name[RVU_PF_INT_VEC_VFME1 * NAME_SIZE];
		snम_लिखो(irq_name, NAME_SIZE, "RVUPF%d_ME1",
			 rvu_get_pf(pf->pcअगरunc));
		ret = request_irq(pci_irq_vector
				  (pf->pdev, RVU_PF_INT_VEC_VFME1),
				  otx2_pf_me_पूर्णांकr_handler, 0, irq_name, pf);
		अगर (ret) अणु
			dev_err(pf->dev,
				"RVUPF: IRQ registration failed for ME1\n");
		पूर्ण
		irq_name = &hw->irq_name[RVU_PF_INT_VEC_VFFLR1 * NAME_SIZE];
		snम_लिखो(irq_name, NAME_SIZE, "RVUPF%d_FLR1",
			 rvu_get_pf(pf->pcअगरunc));
		ret = request_irq(pci_irq_vector
				  (pf->pdev, RVU_PF_INT_VEC_VFFLR1),
				  otx2_pf_flr_पूर्णांकr_handler, 0, irq_name, pf);
		अगर (ret) अणु
			dev_err(pf->dev,
				"RVUPF: IRQ registration failed for FLR1\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* Enable ME पूर्णांकerrupt क्रम all VFs*/
	otx2_ग_लिखो64(pf, RVU_PF_VFME_INTX(0), INTR_MASK(numvfs));
	otx2_ग_लिखो64(pf, RVU_PF_VFME_INT_ENA_W1SX(0), INTR_MASK(numvfs));

	/* Enable FLR पूर्णांकerrupt क्रम all VFs*/
	otx2_ग_लिखो64(pf, RVU_PF_VFFLR_INTX(0), INTR_MASK(numvfs));
	otx2_ग_लिखो64(pf, RVU_PF_VFFLR_INT_ENA_W1SX(0), INTR_MASK(numvfs));

	अगर (numvfs > 64) अणु
		numvfs -= 64;

		otx2_ग_लिखो64(pf, RVU_PF_VFME_INTX(1), INTR_MASK(numvfs));
		otx2_ग_लिखो64(pf, RVU_PF_VFME_INT_ENA_W1SX(1),
			     INTR_MASK(numvfs));

		otx2_ग_लिखो64(pf, RVU_PF_VFFLR_INTX(1), INTR_MASK(numvfs));
		otx2_ग_लिखो64(pf, RVU_PF_VFFLR_INT_ENA_W1SX(1),
			     INTR_MASK(numvfs));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक otx2_pf_flr_init(काष्ठा otx2_nic *pf, पूर्णांक num_vfs)
अणु
	पूर्णांक vf;

	pf->flr_wq = alloc_workqueue("otx2_pf_flr_wq",
				     WQ_UNBOUND | WQ_HIGHPRI, 1);
	अगर (!pf->flr_wq)
		वापस -ENOMEM;

	pf->flr_wrk = devm_kसुस्मृति(pf->dev, num_vfs,
				   माप(काष्ठा flr_work), GFP_KERNEL);
	अगर (!pf->flr_wrk) अणु
		destroy_workqueue(pf->flr_wq);
		वापस -ENOMEM;
	पूर्ण

	क्रम (vf = 0; vf < num_vfs; vf++) अणु
		pf->flr_wrk[vf].pf = pf;
		INIT_WORK(&pf->flr_wrk[vf].work, otx2_flr_handler);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम otx2_queue_work(काष्ठा mbox *mw, काष्ठा workqueue_काष्ठा *mbox_wq,
			    पूर्णांक first, पूर्णांक mdevs, u64 पूर्णांकr, पूर्णांक type)
अणु
	काष्ठा otx2_mbox_dev *mdev;
	काष्ठा otx2_mbox *mbox;
	काष्ठा mbox_hdr *hdr;
	पूर्णांक i;

	क्रम (i = first; i < mdevs; i++) अणु
		/* start from 0 */
		अगर (!(पूर्णांकr & BIT_ULL(i - first)))
			जारी;

		mbox = &mw->mbox;
		mdev = &mbox->dev[i];
		अगर (type == TYPE_PFAF)
			otx2_sync_mbox_bbuf(mbox, i);
		hdr = mdev->mbase + mbox->rx_start;
		/* The hdr->num_msgs is set to zero immediately in the पूर्णांकerrupt
		 * handler to  ensure that it holds a correct value next समय
		 * when the पूर्णांकerrupt handler is called.
		 * pf->mbox.num_msgs holds the data क्रम use in pfaf_mbox_handler
		 * pf>mbox.up_num_msgs holds the data क्रम use in
		 * pfaf_mbox_up_handler.
		 */
		अगर (hdr->num_msgs) अणु
			mw[i].num_msgs = hdr->num_msgs;
			hdr->num_msgs = 0;
			अगर (type == TYPE_PFAF)
				स_रखो(mbox->hwbase + mbox->rx_start, 0,
				       ALIGN(माप(काष्ठा mbox_hdr),
					     माप(u64)));

			queue_work(mbox_wq, &mw[i].mbox_wrk);
		पूर्ण

		mbox = &mw->mbox_up;
		mdev = &mbox->dev[i];
		अगर (type == TYPE_PFAF)
			otx2_sync_mbox_bbuf(mbox, i);
		hdr = mdev->mbase + mbox->rx_start;
		अगर (hdr->num_msgs) अणु
			mw[i].up_num_msgs = hdr->num_msgs;
			hdr->num_msgs = 0;
			अगर (type == TYPE_PFAF)
				स_रखो(mbox->hwbase + mbox->rx_start, 0,
				       ALIGN(माप(काष्ठा mbox_hdr),
					     माप(u64)));

			queue_work(mbox_wq, &mw[i].mbox_up_wrk);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम otx2_क्रमward_msg_pfvf(काष्ठा otx2_mbox_dev *mdev,
				  काष्ठा otx2_mbox *pfvf_mbox, व्योम *bbuf_base,
				  पूर्णांक devid)
अणु
	काष्ठा otx2_mbox_dev *src_mdev = mdev;
	पूर्णांक offset;

	/* Msgs are alपढ़ोy copied, trigger VF's mbox irq */
	smp_wmb();

	offset = pfvf_mbox->trigger | (devid << pfvf_mbox->tr_shअगरt);
	ग_लिखोq(1, (व्योम __iomem *)pfvf_mbox->reg_base + offset);

	/* Restore VF's mbox bounce buffer region address */
	src_mdev->mbase = bbuf_base;
पूर्ण

अटल पूर्णांक otx2_क्रमward_vf_mbox_msgs(काष्ठा otx2_nic *pf,
				     काष्ठा otx2_mbox *src_mbox,
				     पूर्णांक dir, पूर्णांक vf, पूर्णांक num_msgs)
अणु
	काष्ठा otx2_mbox_dev *src_mdev, *dst_mdev;
	काष्ठा mbox_hdr *mbox_hdr;
	काष्ठा mbox_hdr *req_hdr;
	काष्ठा mbox *dst_mbox;
	पूर्णांक dst_size, err;

	अगर (dir == MBOX_सूची_PFAF) अणु
		/* Set VF's mailbox memory as PF's bounce buffer memory, so
		 * that explicit copying of VF's msgs to PF=>AF mbox region
		 * and AF=>PF responses to VF's mbox region can be aव्योमed.
		 */
		src_mdev = &src_mbox->dev[vf];
		mbox_hdr = src_mbox->hwbase +
				src_mbox->rx_start + (vf * MBOX_SIZE);

		dst_mbox = &pf->mbox;
		dst_size = dst_mbox->mbox.tx_size -
				ALIGN(माप(*mbox_hdr), MBOX_MSG_ALIGN);
		/* Check अगर msgs fit पूर्णांकo destination area and has valid size */
		अगर (mbox_hdr->msg_size > dst_size || !mbox_hdr->msg_size)
			वापस -EINVAL;

		dst_mdev = &dst_mbox->mbox.dev[0];

		mutex_lock(&pf->mbox.lock);
		dst_mdev->mbase = src_mdev->mbase;
		dst_mdev->msg_size = mbox_hdr->msg_size;
		dst_mdev->num_msgs = num_msgs;
		err = otx2_sync_mbox_msg(dst_mbox);
		अगर (err) अणु
			dev_warn(pf->dev,
				 "AF not responding to VF%d messages\n", vf);
			/* restore PF mbase and निकास */
			dst_mdev->mbase = pf->mbox.bbuf_base;
			mutex_unlock(&pf->mbox.lock);
			वापस err;
		पूर्ण
		/* At this poपूर्णांक, all the VF messages sent to AF are acked
		 * with proper responses and responses are copied to VF
		 * mailbox hence उठाओ पूर्णांकerrupt to VF.
		 */
		req_hdr = (काष्ठा mbox_hdr *)(dst_mdev->mbase +
					      dst_mbox->mbox.rx_start);
		req_hdr->num_msgs = num_msgs;

		otx2_क्रमward_msg_pfvf(dst_mdev, &pf->mbox_pfvf[0].mbox,
				      pf->mbox.bbuf_base, vf);
		mutex_unlock(&pf->mbox.lock);
	पूर्ण अन्यथा अगर (dir == MBOX_सूची_PFVF_UP) अणु
		src_mdev = &src_mbox->dev[0];
		mbox_hdr = src_mbox->hwbase + src_mbox->rx_start;
		req_hdr = (काष्ठा mbox_hdr *)(src_mdev->mbase +
					      src_mbox->rx_start);
		req_hdr->num_msgs = num_msgs;

		dst_mbox = &pf->mbox_pfvf[0];
		dst_size = dst_mbox->mbox_up.tx_size -
				ALIGN(माप(*mbox_hdr), MBOX_MSG_ALIGN);
		/* Check अगर msgs fit पूर्णांकo destination area */
		अगर (mbox_hdr->msg_size > dst_size)
			वापस -EINVAL;

		dst_mdev = &dst_mbox->mbox_up.dev[vf];
		dst_mdev->mbase = src_mdev->mbase;
		dst_mdev->msg_size = mbox_hdr->msg_size;
		dst_mdev->num_msgs = mbox_hdr->num_msgs;
		err = otx2_sync_mbox_up_msg(dst_mbox, vf);
		अगर (err) अणु
			dev_warn(pf->dev,
				 "VF%d is not responding to mailbox\n", vf);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अगर (dir == MBOX_सूची_VFPF_UP) अणु
		req_hdr = (काष्ठा mbox_hdr *)(src_mbox->dev[0].mbase +
					      src_mbox->rx_start);
		req_hdr->num_msgs = num_msgs;
		otx2_क्रमward_msg_pfvf(&pf->mbox_pfvf->mbox_up.dev[vf],
				      &pf->mbox.mbox_up,
				      pf->mbox_pfvf[vf].bbuf_base,
				      0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम otx2_pfvf_mbox_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mbox_msghdr *msg = शून्य;
	पूर्णांक offset, vf_idx, id, err;
	काष्ठा otx2_mbox_dev *mdev;
	काष्ठा mbox_hdr *req_hdr;
	काष्ठा otx2_mbox *mbox;
	काष्ठा mbox *vf_mbox;
	काष्ठा otx2_nic *pf;

	vf_mbox = container_of(work, काष्ठा mbox, mbox_wrk);
	pf = vf_mbox->pfvf;
	vf_idx = vf_mbox - pf->mbox_pfvf;

	mbox = &pf->mbox_pfvf[0].mbox;
	mdev = &mbox->dev[vf_idx];
	req_hdr = (काष्ठा mbox_hdr *)(mdev->mbase + mbox->rx_start);

	offset = ALIGN(माप(*req_hdr), MBOX_MSG_ALIGN);

	क्रम (id = 0; id < vf_mbox->num_msgs; id++) अणु
		msg = (काष्ठा mbox_msghdr *)(mdev->mbase + mbox->rx_start +
					     offset);

		अगर (msg->sig != OTX2_MBOX_REQ_SIG)
			जाओ inval_msg;

		/* Set VF's number in each of the msg */
		msg->pcअगरunc &= RVU_PFVF_FUNC_MASK;
		msg->pcअगरunc |= (vf_idx + 1) & RVU_PFVF_FUNC_MASK;
		offset = msg->next_msgoff;
	पूर्ण
	err = otx2_क्रमward_vf_mbox_msgs(pf, mbox, MBOX_सूची_PFAF, vf_idx,
					vf_mbox->num_msgs);
	अगर (err)
		जाओ inval_msg;
	वापस;

inval_msg:
	otx2_reply_invalid_msg(mbox, vf_idx, 0, msg->id);
	otx2_mbox_msg_send(mbox, vf_idx);
पूर्ण

अटल व्योम otx2_pfvf_mbox_up_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mbox *vf_mbox = container_of(work, काष्ठा mbox, mbox_up_wrk);
	काष्ठा otx2_nic *pf = vf_mbox->pfvf;
	काष्ठा otx2_mbox_dev *mdev;
	पूर्णांक offset, id, vf_idx = 0;
	काष्ठा mbox_hdr *rsp_hdr;
	काष्ठा mbox_msghdr *msg;
	काष्ठा otx2_mbox *mbox;

	vf_idx = vf_mbox - pf->mbox_pfvf;
	mbox = &pf->mbox_pfvf[0].mbox_up;
	mdev = &mbox->dev[vf_idx];

	rsp_hdr = (काष्ठा mbox_hdr *)(mdev->mbase + mbox->rx_start);
	offset = mbox->rx_start + ALIGN(माप(*rsp_hdr), MBOX_MSG_ALIGN);

	क्रम (id = 0; id < vf_mbox->up_num_msgs; id++) अणु
		msg = mdev->mbase + offset;

		अगर (msg->id >= MBOX_MSG_MAX) अणु
			dev_err(pf->dev,
				"Mbox msg with unknown ID 0x%x\n", msg->id);
			जाओ end;
		पूर्ण

		अगर (msg->sig != OTX2_MBOX_RSP_SIG) अणु
			dev_err(pf->dev,
				"Mbox msg with wrong signature %x, ID 0x%x\n",
				msg->sig, msg->id);
			जाओ end;
		पूर्ण

		चयन (msg->id) अणु
		हाल MBOX_MSG_CGX_LINK_EVENT:
			अवरोध;
		शेष:
			अगर (msg->rc)
				dev_err(pf->dev,
					"Mbox msg response has err %d, ID 0x%x\n",
					msg->rc, msg->id);
			अवरोध;
		पूर्ण

end:
		offset = mbox->rx_start + msg->next_msgoff;
		अगर (mdev->msgs_acked == (vf_mbox->up_num_msgs - 1))
			__otx2_mbox_reset(mbox, 0);
		mdev->msgs_acked++;
	पूर्ण
पूर्ण

अटल irqवापस_t otx2_pfvf_mbox_पूर्णांकr_handler(पूर्णांक irq, व्योम *pf_irq)
अणु
	काष्ठा otx2_nic *pf = (काष्ठा otx2_nic *)(pf_irq);
	पूर्णांक vfs = pf->total_vfs;
	काष्ठा mbox *mbox;
	u64 पूर्णांकr;

	mbox = pf->mbox_pfvf;
	/* Handle VF पूर्णांकerrupts */
	अगर (vfs > 64) अणु
		पूर्णांकr = otx2_पढ़ो64(pf, RVU_PF_VFPF_MBOX_INTX(1));
		otx2_ग_लिखो64(pf, RVU_PF_VFPF_MBOX_INTX(1), पूर्णांकr);
		otx2_queue_work(mbox, pf->mbox_pfvf_wq, 64, vfs, पूर्णांकr,
				TYPE_PFVF);
		vfs -= 64;
	पूर्ण

	पूर्णांकr = otx2_पढ़ो64(pf, RVU_PF_VFPF_MBOX_INTX(0));
	otx2_ग_लिखो64(pf, RVU_PF_VFPF_MBOX_INTX(0), पूर्णांकr);

	otx2_queue_work(mbox, pf->mbox_pfvf_wq, 0, vfs, पूर्णांकr, TYPE_PFVF);

	trace_otx2_msg_पूर्णांकerrupt(mbox->mbox.pdev, "VF(s) to PF", पूर्णांकr);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक otx2_pfvf_mbox_init(काष्ठा otx2_nic *pf, पूर्णांक numvfs)
अणु
	व्योम __iomem *hwbase;
	काष्ठा mbox *mbox;
	पूर्णांक err, vf;
	u64 base;

	अगर (!numvfs)
		वापस -EINVAL;

	pf->mbox_pfvf = devm_kसुस्मृति(&pf->pdev->dev, numvfs,
				     माप(काष्ठा mbox), GFP_KERNEL);
	अगर (!pf->mbox_pfvf)
		वापस -ENOMEM;

	pf->mbox_pfvf_wq = alloc_workqueue("otx2_pfvf_mailbox",
					   WQ_UNBOUND | WQ_HIGHPRI |
					   WQ_MEM_RECLAIM, 1);
	अगर (!pf->mbox_pfvf_wq)
		वापस -ENOMEM;

	/* On CN10K platक्रमm, PF <-> VF mailbox region follows after
	 * PF <-> AF mailbox region.
	 */
	अगर (test_bit(CN10K_MBOX, &pf->hw.cap_flag))
		base = pci_resource_start(pf->pdev, PCI_MBOX_BAR_NUM) +
		       MBOX_SIZE;
	अन्यथा
		base = पढ़ोq((व्योम __iomem *)((u64)pf->reg_base +
					      RVU_PF_VF_BAR4_ADDR));

	hwbase = ioremap_wc(base, MBOX_SIZE * pf->total_vfs);
	अगर (!hwbase) अणु
		err = -ENOMEM;
		जाओ मुक्त_wq;
	पूर्ण

	mbox = &pf->mbox_pfvf[0];
	err = otx2_mbox_init(&mbox->mbox, hwbase, pf->pdev, pf->reg_base,
			     MBOX_सूची_PFVF, numvfs);
	अगर (err)
		जाओ मुक्त_iomem;

	err = otx2_mbox_init(&mbox->mbox_up, hwbase, pf->pdev, pf->reg_base,
			     MBOX_सूची_PFVF_UP, numvfs);
	अगर (err)
		जाओ मुक्त_iomem;

	क्रम (vf = 0; vf < numvfs; vf++) अणु
		mbox->pfvf = pf;
		INIT_WORK(&mbox->mbox_wrk, otx2_pfvf_mbox_handler);
		INIT_WORK(&mbox->mbox_up_wrk, otx2_pfvf_mbox_up_handler);
		mbox++;
	पूर्ण

	वापस 0;

मुक्त_iomem:
	अगर (hwbase)
		iounmap(hwbase);
मुक्त_wq:
	destroy_workqueue(pf->mbox_pfvf_wq);
	वापस err;
पूर्ण

अटल व्योम otx2_pfvf_mbox_destroy(काष्ठा otx2_nic *pf)
अणु
	काष्ठा mbox *mbox = &pf->mbox_pfvf[0];

	अगर (!mbox)
		वापस;

	अगर (pf->mbox_pfvf_wq) अणु
		destroy_workqueue(pf->mbox_pfvf_wq);
		pf->mbox_pfvf_wq = शून्य;
	पूर्ण

	अगर (mbox->mbox.hwbase)
		iounmap(mbox->mbox.hwbase);

	otx2_mbox_destroy(&mbox->mbox);
पूर्ण

अटल व्योम otx2_enable_pfvf_mbox_पूर्णांकr(काष्ठा otx2_nic *pf, पूर्णांक numvfs)
अणु
	/* Clear PF <=> VF mailbox IRQ */
	otx2_ग_लिखो64(pf, RVU_PF_VFPF_MBOX_INTX(0), ~0ull);
	otx2_ग_लिखो64(pf, RVU_PF_VFPF_MBOX_INTX(1), ~0ull);

	/* Enable PF <=> VF mailbox IRQ */
	otx2_ग_लिखो64(pf, RVU_PF_VFPF_MBOX_INT_ENA_W1SX(0), INTR_MASK(numvfs));
	अगर (numvfs > 64) अणु
		numvfs -= 64;
		otx2_ग_लिखो64(pf, RVU_PF_VFPF_MBOX_INT_ENA_W1SX(1),
			     INTR_MASK(numvfs));
	पूर्ण
पूर्ण

अटल व्योम otx2_disable_pfvf_mbox_पूर्णांकr(काष्ठा otx2_nic *pf, पूर्णांक numvfs)
अणु
	पूर्णांक vector;

	/* Disable PF <=> VF mailbox IRQ */
	otx2_ग_लिखो64(pf, RVU_PF_VFPF_MBOX_INT_ENA_W1CX(0), ~0ull);
	otx2_ग_लिखो64(pf, RVU_PF_VFPF_MBOX_INT_ENA_W1CX(1), ~0ull);

	otx2_ग_लिखो64(pf, RVU_PF_VFPF_MBOX_INTX(0), ~0ull);
	vector = pci_irq_vector(pf->pdev, RVU_PF_INT_VEC_VFPF_MBOX0);
	मुक्त_irq(vector, pf);

	अगर (numvfs > 64) अणु
		otx2_ग_लिखो64(pf, RVU_PF_VFPF_MBOX_INTX(1), ~0ull);
		vector = pci_irq_vector(pf->pdev, RVU_PF_INT_VEC_VFPF_MBOX1);
		मुक्त_irq(vector, pf);
	पूर्ण
पूर्ण

अटल पूर्णांक otx2_रेजिस्टर_pfvf_mbox_पूर्णांकr(काष्ठा otx2_nic *pf, पूर्णांक numvfs)
अणु
	काष्ठा otx2_hw *hw = &pf->hw;
	अक्षर *irq_name;
	पूर्णांक err;

	/* Register MBOX0 पूर्णांकerrupt handler */
	irq_name = &hw->irq_name[RVU_PF_INT_VEC_VFPF_MBOX0 * NAME_SIZE];
	अगर (pf->pcअगरunc)
		snम_लिखो(irq_name, NAME_SIZE,
			 "RVUPF%d_VF Mbox0", rvu_get_pf(pf->pcअगरunc));
	अन्यथा
		snम_लिखो(irq_name, NAME_SIZE, "RVUPF_VF Mbox0");
	err = request_irq(pci_irq_vector(pf->pdev, RVU_PF_INT_VEC_VFPF_MBOX0),
			  otx2_pfvf_mbox_पूर्णांकr_handler, 0, irq_name, pf);
	अगर (err) अणु
		dev_err(pf->dev,
			"RVUPF: IRQ registration failed for PFVF mbox0 irq\n");
		वापस err;
	पूर्ण

	अगर (numvfs > 64) अणु
		/* Register MBOX1 पूर्णांकerrupt handler */
		irq_name = &hw->irq_name[RVU_PF_INT_VEC_VFPF_MBOX1 * NAME_SIZE];
		अगर (pf->pcअगरunc)
			snम_लिखो(irq_name, NAME_SIZE,
				 "RVUPF%d_VF Mbox1", rvu_get_pf(pf->pcअगरunc));
		अन्यथा
			snम_लिखो(irq_name, NAME_SIZE, "RVUPF_VF Mbox1");
		err = request_irq(pci_irq_vector(pf->pdev,
						 RVU_PF_INT_VEC_VFPF_MBOX1),
						 otx2_pfvf_mbox_पूर्णांकr_handler,
						 0, irq_name, pf);
		अगर (err) अणु
			dev_err(pf->dev,
				"RVUPF: IRQ registration failed for PFVF mbox1 irq\n");
			वापस err;
		पूर्ण
	पूर्ण

	otx2_enable_pfvf_mbox_पूर्णांकr(pf, numvfs);

	वापस 0;
पूर्ण

अटल व्योम otx2_process_pfaf_mbox_msg(काष्ठा otx2_nic *pf,
				       काष्ठा mbox_msghdr *msg)
अणु
	पूर्णांक devid;

	अगर (msg->id >= MBOX_MSG_MAX) अणु
		dev_err(pf->dev,
			"Mbox msg with unknown ID 0x%x\n", msg->id);
		वापस;
	पूर्ण

	अगर (msg->sig != OTX2_MBOX_RSP_SIG) अणु
		dev_err(pf->dev,
			"Mbox msg with wrong signature %x, ID 0x%x\n",
			 msg->sig, msg->id);
		वापस;
	पूर्ण

	/* message response heading VF */
	devid = msg->pcअगरunc & RVU_PFVF_FUNC_MASK;
	अगर (devid) अणु
		काष्ठा otx2_vf_config *config = &pf->vf_configs[devid - 1];
		काष्ठा delayed_work *dwork;

		चयन (msg->id) अणु
		हाल MBOX_MSG_NIX_LF_START_RX:
			config->पूर्णांकf_करोwn = false;
			dwork = &config->link_event_work;
			schedule_delayed_work(dwork, msecs_to_jअगरfies(100));
			अवरोध;
		हाल MBOX_MSG_NIX_LF_STOP_RX:
			config->पूर्णांकf_करोwn = true;
			अवरोध;
		पूर्ण

		वापस;
	पूर्ण

	चयन (msg->id) अणु
	हाल MBOX_MSG_READY:
		pf->pcअगरunc = msg->pcअगरunc;
		अवरोध;
	हाल MBOX_MSG_MSIX_OFFSET:
		mbox_handler_msix_offset(pf, (काष्ठा msix_offset_rsp *)msg);
		अवरोध;
	हाल MBOX_MSG_NPA_LF_ALLOC:
		mbox_handler_npa_lf_alloc(pf, (काष्ठा npa_lf_alloc_rsp *)msg);
		अवरोध;
	हाल MBOX_MSG_NIX_LF_ALLOC:
		mbox_handler_nix_lf_alloc(pf, (काष्ठा nix_lf_alloc_rsp *)msg);
		अवरोध;
	हाल MBOX_MSG_NIX_TXSCH_ALLOC:
		mbox_handler_nix_txsch_alloc(pf,
					     (काष्ठा nix_txsch_alloc_rsp *)msg);
		अवरोध;
	हाल MBOX_MSG_NIX_BP_ENABLE:
		mbox_handler_nix_bp_enable(pf, (काष्ठा nix_bp_cfg_rsp *)msg);
		अवरोध;
	हाल MBOX_MSG_CGX_STATS:
		mbox_handler_cgx_stats(pf, (काष्ठा cgx_stats_rsp *)msg);
		अवरोध;
	हाल MBOX_MSG_CGX_FEC_STATS:
		mbox_handler_cgx_fec_stats(pf, (काष्ठा cgx_fec_stats_rsp *)msg);
		अवरोध;
	शेष:
		अगर (msg->rc)
			dev_err(pf->dev,
				"Mbox msg response has err %d, ID 0x%x\n",
				msg->rc, msg->id);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम otx2_pfaf_mbox_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा otx2_mbox_dev *mdev;
	काष्ठा mbox_hdr *rsp_hdr;
	काष्ठा mbox_msghdr *msg;
	काष्ठा otx2_mbox *mbox;
	काष्ठा mbox *af_mbox;
	काष्ठा otx2_nic *pf;
	पूर्णांक offset, id;

	af_mbox = container_of(work, काष्ठा mbox, mbox_wrk);
	mbox = &af_mbox->mbox;
	mdev = &mbox->dev[0];
	rsp_hdr = (काष्ठा mbox_hdr *)(mdev->mbase + mbox->rx_start);

	offset = mbox->rx_start + ALIGN(माप(*rsp_hdr), MBOX_MSG_ALIGN);
	pf = af_mbox->pfvf;

	क्रम (id = 0; id < af_mbox->num_msgs; id++) अणु
		msg = (काष्ठा mbox_msghdr *)(mdev->mbase + offset);
		otx2_process_pfaf_mbox_msg(pf, msg);
		offset = mbox->rx_start + msg->next_msgoff;
		अगर (mdev->msgs_acked == (af_mbox->num_msgs - 1))
			__otx2_mbox_reset(mbox, 0);
		mdev->msgs_acked++;
	पूर्ण

पूर्ण

अटल व्योम otx2_handle_link_event(काष्ठा otx2_nic *pf)
अणु
	काष्ठा cgx_link_user_info *linfo = &pf->linfo;
	काष्ठा net_device *netdev = pf->netdev;

	pr_info("%s NIC Link is %s %d Mbps %s duplex\n", netdev->name,
		linfo->link_up ? "UP" : "DOWN", linfo->speed,
		linfo->full_duplex ? "Full" : "Half");
	अगर (linfo->link_up) अणु
		netअगर_carrier_on(netdev);
		netअगर_tx_start_all_queues(netdev);
	पूर्ण अन्यथा अणु
		netअगर_tx_stop_all_queues(netdev);
		netअगर_carrier_off(netdev);
	पूर्ण
पूर्ण

पूर्णांक otx2_mbox_up_handler_cgx_link_event(काष्ठा otx2_nic *pf,
					काष्ठा cgx_link_info_msg *msg,
					काष्ठा msg_rsp *rsp)
अणु
	पूर्णांक i;

	/* Copy the link info sent by AF */
	pf->linfo = msg->link_info;

	/* notअगरy VFs about link event */
	क्रम (i = 0; i < pci_num_vf(pf->pdev); i++) अणु
		काष्ठा otx2_vf_config *config = &pf->vf_configs[i];
		काष्ठा delayed_work *dwork = &config->link_event_work;

		अगर (config->पूर्णांकf_करोwn)
			जारी;

		schedule_delayed_work(dwork, msecs_to_jअगरfies(100));
	पूर्ण

	/* पूर्णांकerface has not been fully configured yet */
	अगर (pf->flags & OTX2_FLAG_INTF_DOWN)
		वापस 0;

	otx2_handle_link_event(pf);
	वापस 0;
पूर्ण

अटल पूर्णांक otx2_process_mbox_msg_up(काष्ठा otx2_nic *pf,
				    काष्ठा mbox_msghdr *req)
अणु
	/* Check अगर valid, अगर not reply with a invalid msg */
	अगर (req->sig != OTX2_MBOX_REQ_SIG) अणु
		otx2_reply_invalid_msg(&pf->mbox.mbox_up, 0, 0, req->id);
		वापस -ENODEV;
	पूर्ण

	चयन (req->id) अणु
#घोषणा M(_name, _id, _fn_name, _req_type, _rsp_type)			\
	हाल _id: अणु							\
		काष्ठा _rsp_type *rsp;					\
		पूर्णांक err;						\
									\
		rsp = (काष्ठा _rsp_type *)otx2_mbox_alloc_msg(		\
			&pf->mbox.mbox_up, 0,				\
			माप(काष्ठा _rsp_type));			\
		अगर (!rsp)						\
			वापस -ENOMEM;					\
									\
		rsp->hdr.id = _id;					\
		rsp->hdr.sig = OTX2_MBOX_RSP_SIG;			\
		rsp->hdr.pcअगरunc = 0;					\
		rsp->hdr.rc = 0;					\
									\
		err = otx2_mbox_up_handler_ ## _fn_name(		\
			pf, (काष्ठा _req_type *)req, rsp);		\
		वापस err;						\
	पूर्ण
MBOX_UP_CGX_MESSAGES
#अघोषित M
		अवरोध;
	शेष:
		otx2_reply_invalid_msg(&pf->mbox.mbox_up, 0, 0, req->id);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम otx2_pfaf_mbox_up_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mbox *af_mbox = container_of(work, काष्ठा mbox, mbox_up_wrk);
	काष्ठा otx2_mbox *mbox = &af_mbox->mbox_up;
	काष्ठा otx2_mbox_dev *mdev = &mbox->dev[0];
	काष्ठा otx2_nic *pf = af_mbox->pfvf;
	पूर्णांक offset, id, devid = 0;
	काष्ठा mbox_hdr *rsp_hdr;
	काष्ठा mbox_msghdr *msg;

	rsp_hdr = (काष्ठा mbox_hdr *)(mdev->mbase + mbox->rx_start);

	offset = mbox->rx_start + ALIGN(माप(*rsp_hdr), MBOX_MSG_ALIGN);

	क्रम (id = 0; id < af_mbox->up_num_msgs; id++) अणु
		msg = (काष्ठा mbox_msghdr *)(mdev->mbase + offset);

		devid = msg->pcअगरunc & RVU_PFVF_FUNC_MASK;
		/* Skip processing VF's messages */
		अगर (!devid)
			otx2_process_mbox_msg_up(pf, msg);
		offset = mbox->rx_start + msg->next_msgoff;
	पूर्ण
	अगर (devid) अणु
		otx2_क्रमward_vf_mbox_msgs(pf, &pf->mbox.mbox_up,
					  MBOX_सूची_PFVF_UP, devid - 1,
					  af_mbox->up_num_msgs);
		वापस;
	पूर्ण

	otx2_mbox_msg_send(mbox, 0);
पूर्ण

अटल irqवापस_t otx2_pfaf_mbox_पूर्णांकr_handler(पूर्णांक irq, व्योम *pf_irq)
अणु
	काष्ठा otx2_nic *pf = (काष्ठा otx2_nic *)pf_irq;
	काष्ठा mbox *mbox;

	/* Clear the IRQ */
	otx2_ग_लिखो64(pf, RVU_PF_INT, BIT_ULL(0));

	mbox = &pf->mbox;

	trace_otx2_msg_पूर्णांकerrupt(mbox->mbox.pdev, "AF to PF", BIT_ULL(0));

	otx2_queue_work(mbox, pf->mbox_wq, 0, 1, 1, TYPE_PFAF);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम otx2_disable_mbox_पूर्णांकr(काष्ठा otx2_nic *pf)
अणु
	पूर्णांक vector = pci_irq_vector(pf->pdev, RVU_PF_INT_VEC_AFPF_MBOX);

	/* Disable AF => PF mailbox IRQ */
	otx2_ग_लिखो64(pf, RVU_PF_INT_ENA_W1C, BIT_ULL(0));
	मुक्त_irq(vector, pf);
पूर्ण

अटल पूर्णांक otx2_रेजिस्टर_mbox_पूर्णांकr(काष्ठा otx2_nic *pf, bool probe_af)
अणु
	काष्ठा otx2_hw *hw = &pf->hw;
	काष्ठा msg_req *req;
	अक्षर *irq_name;
	पूर्णांक err;

	/* Register mailbox पूर्णांकerrupt handler */
	irq_name = &hw->irq_name[RVU_PF_INT_VEC_AFPF_MBOX * NAME_SIZE];
	snम_लिखो(irq_name, NAME_SIZE, "RVUPFAF Mbox");
	err = request_irq(pci_irq_vector(pf->pdev, RVU_PF_INT_VEC_AFPF_MBOX),
			  otx2_pfaf_mbox_पूर्णांकr_handler, 0, irq_name, pf);
	अगर (err) अणु
		dev_err(pf->dev,
			"RVUPF: IRQ registration failed for PFAF mbox irq\n");
		वापस err;
	पूर्ण

	/* Enable mailbox पूर्णांकerrupt क्रम msgs coming from AF.
	 * First clear to aव्योम spurious पूर्णांकerrupts, अगर any.
	 */
	otx2_ग_लिखो64(pf, RVU_PF_INT, BIT_ULL(0));
	otx2_ग_लिखो64(pf, RVU_PF_INT_ENA_W1S, BIT_ULL(0));

	अगर (!probe_af)
		वापस 0;

	/* Check mailbox communication with AF */
	req = otx2_mbox_alloc_msg_पढ़ोy(&pf->mbox);
	अगर (!req) अणु
		otx2_disable_mbox_पूर्णांकr(pf);
		वापस -ENOMEM;
	पूर्ण
	err = otx2_sync_mbox_msg(&pf->mbox);
	अगर (err) अणु
		dev_warn(pf->dev,
			 "AF not responding to mailbox, deferring probe\n");
		otx2_disable_mbox_पूर्णांकr(pf);
		वापस -EPROBE_DEFER;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम otx2_pfaf_mbox_destroy(काष्ठा otx2_nic *pf)
अणु
	काष्ठा mbox *mbox = &pf->mbox;

	अगर (pf->mbox_wq) अणु
		destroy_workqueue(pf->mbox_wq);
		pf->mbox_wq = शून्य;
	पूर्ण

	अगर (mbox->mbox.hwbase)
		iounmap((व्योम __iomem *)mbox->mbox.hwbase);

	otx2_mbox_destroy(&mbox->mbox);
	otx2_mbox_destroy(&mbox->mbox_up);
पूर्ण

अटल पूर्णांक otx2_pfaf_mbox_init(काष्ठा otx2_nic *pf)
अणु
	काष्ठा mbox *mbox = &pf->mbox;
	व्योम __iomem *hwbase;
	पूर्णांक err;

	mbox->pfvf = pf;
	pf->mbox_wq = alloc_workqueue("otx2_pfaf_mailbox",
				      WQ_UNBOUND | WQ_HIGHPRI |
				      WQ_MEM_RECLAIM, 1);
	अगर (!pf->mbox_wq)
		वापस -ENOMEM;

	/* Mailbox is a reserved memory (in RAM) region shared between
	 * admin function (i.e AF) and this PF, shouldn't be mapped as
	 * device memory to allow unaligned accesses.
	 */
	hwbase = ioremap_wc(pci_resource_start(pf->pdev, PCI_MBOX_BAR_NUM),
			    MBOX_SIZE);
	अगर (!hwbase) अणु
		dev_err(pf->dev, "Unable to map PFAF mailbox region\n");
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण

	err = otx2_mbox_init(&mbox->mbox, hwbase, pf->pdev, pf->reg_base,
			     MBOX_सूची_PFAF, 1);
	अगर (err)
		जाओ निकास;

	err = otx2_mbox_init(&mbox->mbox_up, hwbase, pf->pdev, pf->reg_base,
			     MBOX_सूची_PFAF_UP, 1);
	अगर (err)
		जाओ निकास;

	err = otx2_mbox_bbuf_init(mbox, pf->pdev);
	अगर (err)
		जाओ निकास;

	INIT_WORK(&mbox->mbox_wrk, otx2_pfaf_mbox_handler);
	INIT_WORK(&mbox->mbox_up_wrk, otx2_pfaf_mbox_up_handler);
	mutex_init(&mbox->lock);

	वापस 0;
निकास:
	otx2_pfaf_mbox_destroy(pf);
	वापस err;
पूर्ण

अटल पूर्णांक otx2_cgx_config_linkevents(काष्ठा otx2_nic *pf, bool enable)
अणु
	काष्ठा msg_req *msg;
	पूर्णांक err;

	mutex_lock(&pf->mbox.lock);
	अगर (enable)
		msg = otx2_mbox_alloc_msg_cgx_start_linkevents(&pf->mbox);
	अन्यथा
		msg = otx2_mbox_alloc_msg_cgx_stop_linkevents(&pf->mbox);

	अगर (!msg) अणु
		mutex_unlock(&pf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	err = otx2_sync_mbox_msg(&pf->mbox);
	mutex_unlock(&pf->mbox.lock);
	वापस err;
पूर्ण

अटल पूर्णांक otx2_cgx_config_loopback(काष्ठा otx2_nic *pf, bool enable)
अणु
	काष्ठा msg_req *msg;
	पूर्णांक err;

	mutex_lock(&pf->mbox.lock);
	अगर (enable)
		msg = otx2_mbox_alloc_msg_cgx_पूर्णांकlbk_enable(&pf->mbox);
	अन्यथा
		msg = otx2_mbox_alloc_msg_cgx_पूर्णांकlbk_disable(&pf->mbox);

	अगर (!msg) अणु
		mutex_unlock(&pf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	err = otx2_sync_mbox_msg(&pf->mbox);
	mutex_unlock(&pf->mbox.lock);
	वापस err;
पूर्ण

पूर्णांक otx2_set_real_num_queues(काष्ठा net_device *netdev,
			     पूर्णांक tx_queues, पूर्णांक rx_queues)
अणु
	पूर्णांक err;

	err = netअगर_set_real_num_tx_queues(netdev, tx_queues);
	अगर (err) अणु
		netdev_err(netdev,
			   "Failed to set no of Tx queues: %d\n", tx_queues);
		वापस err;
	पूर्ण

	err = netअगर_set_real_num_rx_queues(netdev, rx_queues);
	अगर (err)
		netdev_err(netdev,
			   "Failed to set no of Rx queues: %d\n", rx_queues);
	वापस err;
पूर्ण
EXPORT_SYMBOL(otx2_set_real_num_queues);

अटल irqवापस_t otx2_q_पूर्णांकr_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा otx2_nic *pf = data;
	u64 val, *ptr;
	u64 qidx = 0;

	/* CQ */
	क्रम (qidx = 0; qidx < pf->qset.cq_cnt; qidx++) अणु
		ptr = otx2_get_regaddr(pf, NIX_LF_CQ_OP_INT);
		val = otx2_atomic64_add((qidx << 44), ptr);

		otx2_ग_लिखो64(pf, NIX_LF_CQ_OP_INT, (qidx << 44) |
			     (val & NIX_CQERRINT_BITS));
		अगर (!(val & (NIX_CQERRINT_BITS | BIT_ULL(42))))
			जारी;

		अगर (val & BIT_ULL(42)) अणु
			netdev_err(pf->netdev, "CQ%lld: error reading NIX_LF_CQ_OP_INT, NIX_LF_ERR_INT 0x%llx\n",
				   qidx, otx2_पढ़ो64(pf, NIX_LF_ERR_INT));
		पूर्ण अन्यथा अणु
			अगर (val & BIT_ULL(NIX_CQERRINT_DOOR_ERR))
				netdev_err(pf->netdev, "CQ%lld: Doorbell error",
					   qidx);
			अगर (val & BIT_ULL(NIX_CQERRINT_CQE_FAULT))
				netdev_err(pf->netdev, "CQ%lld: Memory fault on CQE write to LLC/DRAM",
					   qidx);
		पूर्ण

		schedule_work(&pf->reset_task);
	पूर्ण

	/* SQ */
	क्रम (qidx = 0; qidx < pf->hw.tx_queues; qidx++) अणु
		ptr = otx2_get_regaddr(pf, NIX_LF_SQ_OP_INT);
		val = otx2_atomic64_add((qidx << 44), ptr);
		otx2_ग_लिखो64(pf, NIX_LF_SQ_OP_INT, (qidx << 44) |
			     (val & NIX_SQINT_BITS));

		अगर (!(val & (NIX_SQINT_BITS | BIT_ULL(42))))
			जारी;

		अगर (val & BIT_ULL(42)) अणु
			netdev_err(pf->netdev, "SQ%lld: error reading NIX_LF_SQ_OP_INT, NIX_LF_ERR_INT 0x%llx\n",
				   qidx, otx2_पढ़ो64(pf, NIX_LF_ERR_INT));
		पूर्ण अन्यथा अणु
			अगर (val & BIT_ULL(NIX_SQINT_LMT_ERR)) अणु
				netdev_err(pf->netdev, "SQ%lld: LMT store error NIX_LF_SQ_OP_ERR_DBG:0x%llx",
					   qidx,
					   otx2_पढ़ो64(pf,
						       NIX_LF_SQ_OP_ERR_DBG));
				otx2_ग_लिखो64(pf, NIX_LF_SQ_OP_ERR_DBG,
					     BIT_ULL(44));
			पूर्ण
			अगर (val & BIT_ULL(NIX_SQINT_MNQ_ERR)) अणु
				netdev_err(pf->netdev, "SQ%lld: Meta-descriptor enqueue error NIX_LF_MNQ_ERR_DGB:0x%llx\n",
					   qidx,
					   otx2_पढ़ो64(pf, NIX_LF_MNQ_ERR_DBG));
				otx2_ग_लिखो64(pf, NIX_LF_MNQ_ERR_DBG,
					     BIT_ULL(44));
			पूर्ण
			अगर (val & BIT_ULL(NIX_SQINT_SEND_ERR)) अणु
				netdev_err(pf->netdev, "SQ%lld: Send error, NIX_LF_SEND_ERR_DBG 0x%llx",
					   qidx,
					   otx2_पढ़ो64(pf,
						       NIX_LF_SEND_ERR_DBG));
				otx2_ग_लिखो64(pf, NIX_LF_SEND_ERR_DBG,
					     BIT_ULL(44));
			पूर्ण
			अगर (val & BIT_ULL(NIX_SQINT_SQB_ALLOC_FAIL))
				netdev_err(pf->netdev, "SQ%lld: SQB allocation failed",
					   qidx);
		पूर्ण

		schedule_work(&pf->reset_task);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t otx2_cq_पूर्णांकr_handler(पूर्णांक irq, व्योम *cq_irq)
अणु
	काष्ठा otx2_cq_poll *cq_poll = (काष्ठा otx2_cq_poll *)cq_irq;
	काष्ठा otx2_nic *pf = (काष्ठा otx2_nic *)cq_poll->dev;
	पूर्णांक qidx = cq_poll->cपूर्णांक_idx;

	/* Disable पूर्णांकerrupts.
	 *
	 * Completion पूर्णांकerrupts behave in a level-triggered पूर्णांकerrupt
	 * fashion, and hence have to be cleared only after it is serviced.
	 */
	otx2_ग_लिखो64(pf, NIX_LF_CINTX_ENA_W1C(qidx), BIT_ULL(0));

	/* Schedule NAPI */
	napi_schedule_irqoff(&cq_poll->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम otx2_disable_napi(काष्ठा otx2_nic *pf)
अणु
	काष्ठा otx2_qset *qset = &pf->qset;
	काष्ठा otx2_cq_poll *cq_poll;
	पूर्णांक qidx;

	क्रम (qidx = 0; qidx < pf->hw.cपूर्णांक_cnt; qidx++) अणु
		cq_poll = &qset->napi[qidx];
		napi_disable(&cq_poll->napi);
		netअगर_napi_del(&cq_poll->napi);
	पूर्ण
पूर्ण

अटल व्योम otx2_मुक्त_cq_res(काष्ठा otx2_nic *pf)
अणु
	काष्ठा otx2_qset *qset = &pf->qset;
	काष्ठा otx2_cq_queue *cq;
	पूर्णांक qidx;

	/* Disable CQs */
	otx2_ctx_disable(&pf->mbox, NIX_AQ_CTYPE_CQ, false);
	क्रम (qidx = 0; qidx < qset->cq_cnt; qidx++) अणु
		cq = &qset->cq[qidx];
		qmem_मुक्त(pf->dev, cq->cqe);
	पूर्ण
पूर्ण

अटल व्योम otx2_मुक्त_sq_res(काष्ठा otx2_nic *pf)
अणु
	काष्ठा otx2_qset *qset = &pf->qset;
	काष्ठा otx2_snd_queue *sq;
	पूर्णांक qidx;

	/* Disable SQs */
	otx2_ctx_disable(&pf->mbox, NIX_AQ_CTYPE_SQ, false);
	/* Free SQB poपूर्णांकers */
	otx2_sq_मुक्त_sqbs(pf);
	क्रम (qidx = 0; qidx < pf->hw.tx_queues; qidx++) अणु
		sq = &qset->sq[qidx];
		qmem_मुक्त(pf->dev, sq->sqe);
		qmem_मुक्त(pf->dev, sq->tso_hdrs);
		kमुक्त(sq->sg);
		kमुक्त(sq->sqb_ptrs);
	पूर्ण
पूर्ण

अटल पूर्णांक otx2_get_rbuf_size(काष्ठा otx2_nic *pf, पूर्णांक mtu)
अणु
	पूर्णांक frame_size;
	पूर्णांक total_size;
	पूर्णांक rbuf_size;

	/* The data transferred by NIX to memory consists of actual packet
	 * plus additional data which has बारtamp and/or EDSA/HIGIG2
	 * headers अगर पूर्णांकerface is configured in corresponding modes.
	 * NIX transfers entire data using 6 segments/buffers and ग_लिखोs
	 * a CQE_RX descriptor with those segment addresses. First segment
	 * has additional data prepended to packet. Also software omits a
	 * headroom of 128 bytes and माप(काष्ठा skb_shared_info) in
	 * each segment. Hence the total size of memory needed
	 * to receive a packet with 'mtu' is:
	 * frame size =  mtu + additional data;
	 * memory = frame_size + (headroom + काष्ठा skb_shared_info size) * 6;
	 * each receive buffer size = memory / 6;
	 */
	frame_size = mtu + OTX2_ETH_HLEN + OTX2_HW_TIMESTAMP_LEN;
	total_size = frame_size + (OTX2_HEAD_ROOM +
		     OTX2_DATA_ALIGN(माप(काष्ठा skb_shared_info))) * 6;
	rbuf_size = total_size / 6;

	वापस ALIGN(rbuf_size, 2048);
पूर्ण

अटल पूर्णांक otx2_init_hw_resources(काष्ठा otx2_nic *pf)
अणु
	काष्ठा nix_lf_मुक्त_req *मुक्त_req;
	काष्ठा mbox *mbox = &pf->mbox;
	काष्ठा otx2_hw *hw = &pf->hw;
	काष्ठा msg_req *req;
	पूर्णांक err = 0, lvl;

	/* Set required NPA LF's pool counts
	 * Auras and Pools are used in a 1:1 mapping,
	 * so, aura count = pool count.
	 */
	hw->rqpool_cnt = hw->rx_queues;
	hw->sqpool_cnt = hw->tx_queues;
	hw->pool_cnt = hw->rqpool_cnt + hw->sqpool_cnt;

	pf->max_frs = pf->netdev->mtu + OTX2_ETH_HLEN + OTX2_HW_TIMESTAMP_LEN;

	pf->rbsize = otx2_get_rbuf_size(pf, pf->netdev->mtu);

	mutex_lock(&mbox->lock);
	/* NPA init */
	err = otx2_config_npa(pf);
	अगर (err)
		जाओ निकास;

	/* NIX init */
	err = otx2_config_nix(pf);
	अगर (err)
		जाओ err_मुक्त_npa_lf;

	/* Enable backpressure */
	otx2_nix_config_bp(pf, true);

	/* Init Auras and pools used by NIX RQ, क्रम मुक्त buffer ptrs */
	err = otx2_rq_aura_pool_init(pf);
	अगर (err) अणु
		mutex_unlock(&mbox->lock);
		जाओ err_मुक्त_nix_lf;
	पूर्ण
	/* Init Auras and pools used by NIX SQ, क्रम queueing SQEs */
	err = otx2_sq_aura_pool_init(pf);
	अगर (err) अणु
		mutex_unlock(&mbox->lock);
		जाओ err_मुक्त_rq_ptrs;
	पूर्ण

	err = otx2_txsch_alloc(pf);
	अगर (err) अणु
		mutex_unlock(&mbox->lock);
		जाओ err_मुक्त_sq_ptrs;
	पूर्ण

	err = otx2_config_nix_queues(pf);
	अगर (err) अणु
		mutex_unlock(&mbox->lock);
		जाओ err_मुक्त_txsch;
	पूर्ण
	क्रम (lvl = 0; lvl < NIX_TXSCH_LVL_CNT; lvl++) अणु
		err = otx2_txschq_config(pf, lvl);
		अगर (err) अणु
			mutex_unlock(&mbox->lock);
			जाओ err_मुक्त_nix_queues;
		पूर्ण
	पूर्ण
	mutex_unlock(&mbox->lock);
	वापस err;

err_मुक्त_nix_queues:
	otx2_मुक्त_sq_res(pf);
	otx2_मुक्त_cq_res(pf);
	otx2_ctx_disable(mbox, NIX_AQ_CTYPE_RQ, false);
err_मुक्त_txsch:
	अगर (otx2_txschq_stop(pf))
		dev_err(pf->dev, "%s failed to stop TX schedulers\n", __func__);
err_मुक्त_sq_ptrs:
	otx2_sq_मुक्त_sqbs(pf);
err_मुक्त_rq_ptrs:
	otx2_मुक्त_aura_ptr(pf, AURA_NIX_RQ);
	otx2_ctx_disable(mbox, NPA_AQ_CTYPE_POOL, true);
	otx2_ctx_disable(mbox, NPA_AQ_CTYPE_AURA, true);
	otx2_aura_pool_मुक्त(pf);
err_मुक्त_nix_lf:
	mutex_lock(&mbox->lock);
	मुक्त_req = otx2_mbox_alloc_msg_nix_lf_मुक्त(mbox);
	अगर (मुक्त_req) अणु
		मुक्त_req->flags = NIX_LF_DISABLE_FLOWS;
		अगर (otx2_sync_mbox_msg(mbox))
			dev_err(pf->dev, "%s failed to free nixlf\n", __func__);
	पूर्ण
err_मुक्त_npa_lf:
	/* Reset NPA LF */
	req = otx2_mbox_alloc_msg_npa_lf_मुक्त(mbox);
	अगर (req) अणु
		अगर (otx2_sync_mbox_msg(mbox))
			dev_err(pf->dev, "%s failed to free npalf\n", __func__);
	पूर्ण
निकास:
	mutex_unlock(&mbox->lock);
	वापस err;
पूर्ण

अटल व्योम otx2_मुक्त_hw_resources(काष्ठा otx2_nic *pf)
अणु
	काष्ठा otx2_qset *qset = &pf->qset;
	काष्ठा nix_lf_मुक्त_req *मुक्त_req;
	काष्ठा mbox *mbox = &pf->mbox;
	काष्ठा otx2_cq_queue *cq;
	काष्ठा msg_req *req;
	पूर्णांक qidx, err;

	/* Ensure all SQE are processed */
	otx2_sqb_flush(pf);

	/* Stop transmission */
	err = otx2_txschq_stop(pf);
	अगर (err)
		dev_err(pf->dev, "RVUPF: Failed to stop/free TX schedulers\n");

	mutex_lock(&mbox->lock);
	/* Disable backpressure */
	अगर (!(pf->pcअगरunc & RVU_PFVF_FUNC_MASK))
		otx2_nix_config_bp(pf, false);
	mutex_unlock(&mbox->lock);

	/* Disable RQs */
	otx2_ctx_disable(mbox, NIX_AQ_CTYPE_RQ, false);

	/*Dequeue all CQEs */
	क्रम (qidx = 0; qidx < qset->cq_cnt; qidx++) अणु
		cq = &qset->cq[qidx];
		अगर (cq->cq_type == CQ_RX)
			otx2_cleanup_rx_cqes(pf, cq);
		अन्यथा
			otx2_cleanup_tx_cqes(pf, cq);
	पूर्ण

	otx2_मुक्त_sq_res(pf);

	/* Free RQ buffer poपूर्णांकers*/
	otx2_मुक्त_aura_ptr(pf, AURA_NIX_RQ);

	otx2_मुक्त_cq_res(pf);

	mutex_lock(&mbox->lock);
	/* Reset NIX LF */
	मुक्त_req = otx2_mbox_alloc_msg_nix_lf_मुक्त(mbox);
	अगर (मुक्त_req) अणु
		मुक्त_req->flags = NIX_LF_DISABLE_FLOWS;
		अगर (!(pf->flags & OTX2_FLAG_PF_SHUTDOWN))
			मुक्त_req->flags |= NIX_LF_DONT_FREE_TX_VTAG;
		अगर (otx2_sync_mbox_msg(mbox))
			dev_err(pf->dev, "%s failed to free nixlf\n", __func__);
	पूर्ण
	mutex_unlock(&mbox->lock);

	/* Disable NPA Pool and Aura hw context */
	otx2_ctx_disable(mbox, NPA_AQ_CTYPE_POOL, true);
	otx2_ctx_disable(mbox, NPA_AQ_CTYPE_AURA, true);
	otx2_aura_pool_मुक्त(pf);

	mutex_lock(&mbox->lock);
	/* Reset NPA LF */
	req = otx2_mbox_alloc_msg_npa_lf_मुक्त(mbox);
	अगर (req) अणु
		अगर (otx2_sync_mbox_msg(mbox))
			dev_err(pf->dev, "%s failed to free npalf\n", __func__);
	पूर्ण
	mutex_unlock(&mbox->lock);
पूर्ण

पूर्णांक otx2_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा otx2_nic *pf = netdev_priv(netdev);
	काष्ठा otx2_cq_poll *cq_poll = शून्य;
	काष्ठा otx2_qset *qset = &pf->qset;
	पूर्णांक err = 0, qidx, vec;
	अक्षर *irq_name;

	netअगर_carrier_off(netdev);

	pf->qset.cq_cnt = pf->hw.rx_queues + pf->hw.tx_queues;
	/* RQ and SQs are mapped to dअगरferent CQs,
	 * so find out max CQ IRQs (i.e CINTs) needed.
	 */
	pf->hw.cपूर्णांक_cnt = max(pf->hw.rx_queues, pf->hw.tx_queues);
	qset->napi = kसुस्मृति(pf->hw.cपूर्णांक_cnt, माप(*cq_poll), GFP_KERNEL);
	अगर (!qset->napi)
		वापस -ENOMEM;

	/* CQ size of RQ */
	qset->rqe_cnt = qset->rqe_cnt ? qset->rqe_cnt : Q_COUNT(Q_SIZE_256);
	/* CQ size of SQ */
	qset->sqe_cnt = qset->sqe_cnt ? qset->sqe_cnt : Q_COUNT(Q_SIZE_4K);

	err = -ENOMEM;
	qset->cq = kसुस्मृति(pf->qset.cq_cnt,
			   माप(काष्ठा otx2_cq_queue), GFP_KERNEL);
	अगर (!qset->cq)
		जाओ err_मुक्त_mem;

	qset->sq = kसुस्मृति(pf->hw.tx_queues,
			   माप(काष्ठा otx2_snd_queue), GFP_KERNEL);
	अगर (!qset->sq)
		जाओ err_मुक्त_mem;

	qset->rq = kसुस्मृति(pf->hw.rx_queues,
			   माप(काष्ठा otx2_rcv_queue), GFP_KERNEL);
	अगर (!qset->rq)
		जाओ err_मुक्त_mem;

	अगर (test_bit(CN10K_LMTST, &pf->hw.cap_flag)) अणु
		/* Reserve LMT lines क्रम NPA AURA batch मुक्त */
		pf->hw.npa_lmt_base = (__क्रमce u64 *)pf->hw.lmt_base;
		/* Reserve LMT lines क्रम NIX TX */
		pf->hw.nix_lmt_base = (__क्रमce u64 *)((u64)pf->hw.npa_lmt_base +
				      (NIX_LMTID_BASE * LMT_LINE_SIZE));
	पूर्ण

	err = otx2_init_hw_resources(pf);
	अगर (err)
		जाओ err_मुक्त_mem;

	/* Register NAPI handler */
	क्रम (qidx = 0; qidx < pf->hw.cपूर्णांक_cnt; qidx++) अणु
		cq_poll = &qset->napi[qidx];
		cq_poll->cपूर्णांक_idx = qidx;
		/* RQ0 & SQ0 are mapped to CINT0 and so on..
		 * 'cq_ids[0]' points to RQ's CQ and
		 * 'cq_ids[1]' points to SQ's CQ and
		 */
		cq_poll->cq_ids[CQ_RX] =
			(qidx <  pf->hw.rx_queues) ? qidx : CINT_INVALID_CQ;
		cq_poll->cq_ids[CQ_TX] = (qidx < pf->hw.tx_queues) ?
				      qidx + pf->hw.rx_queues : CINT_INVALID_CQ;
		cq_poll->dev = (व्योम *)pf;
		netअगर_napi_add(netdev, &cq_poll->napi,
			       otx2_napi_handler, NAPI_POLL_WEIGHT);
		napi_enable(&cq_poll->napi);
	पूर्ण

	/* Set maximum frame size allowed in HW */
	err = otx2_hw_set_mtu(pf, netdev->mtu);
	अगर (err)
		जाओ err_disable_napi;

	/* Setup segmentation algorithms, अगर failed, clear offload capability */
	otx2_setup_segmentation(pf);

	/* Initialize RSS */
	err = otx2_rss_init(pf);
	अगर (err)
		जाओ err_disable_napi;

	/* Register Queue IRQ handlers */
	vec = pf->hw.nix_msixoff + NIX_LF_QINT_VEC_START;
	irq_name = &pf->hw.irq_name[vec * NAME_SIZE];

	snम_लिखो(irq_name, NAME_SIZE, "%s-qerr", pf->netdev->name);

	err = request_irq(pci_irq_vector(pf->pdev, vec),
			  otx2_q_पूर्णांकr_handler, 0, irq_name, pf);
	अगर (err) अणु
		dev_err(pf->dev,
			"RVUPF%d: IRQ registration failed for QERR\n",
			rvu_get_pf(pf->pcअगरunc));
		जाओ err_disable_napi;
	पूर्ण

	/* Enable QINT IRQ */
	otx2_ग_लिखो64(pf, NIX_LF_QINTX_ENA_W1S(0), BIT_ULL(0));

	/* Register CQ IRQ handlers */
	vec = pf->hw.nix_msixoff + NIX_LF_CINT_VEC_START;
	क्रम (qidx = 0; qidx < pf->hw.cपूर्णांक_cnt; qidx++) अणु
		irq_name = &pf->hw.irq_name[vec * NAME_SIZE];

		snम_लिखो(irq_name, NAME_SIZE, "%s-rxtx-%d", pf->netdev->name,
			 qidx);

		err = request_irq(pci_irq_vector(pf->pdev, vec),
				  otx2_cq_पूर्णांकr_handler, 0, irq_name,
				  &qset->napi[qidx]);
		अगर (err) अणु
			dev_err(pf->dev,
				"RVUPF%d: IRQ registration failed for CQ%d\n",
				rvu_get_pf(pf->pcअगरunc), qidx);
			जाओ err_मुक्त_cपूर्णांकs;
		पूर्ण
		vec++;

		otx2_config_irq_coalescing(pf, qidx);

		/* Enable CQ IRQ */
		otx2_ग_लिखो64(pf, NIX_LF_CINTX_INT(qidx), BIT_ULL(0));
		otx2_ग_लिखो64(pf, NIX_LF_CINTX_ENA_W1S(qidx), BIT_ULL(0));
	पूर्ण

	otx2_set_cपूर्णांकs_affinity(pf);

	अगर (pf->flags & OTX2_FLAG_RX_VLAN_SUPPORT)
		otx2_enable_rxvlan(pf, true);

	/* When reinitializing enable समय stamping अगर it is enabled beक्रमe */
	अगर (pf->flags & OTX2_FLAG_TX_TSTAMP_ENABLED) अणु
		pf->flags &= ~OTX2_FLAG_TX_TSTAMP_ENABLED;
		otx2_config_hw_tx_tstamp(pf, true);
	पूर्ण
	अगर (pf->flags & OTX2_FLAG_RX_TSTAMP_ENABLED) अणु
		pf->flags &= ~OTX2_FLAG_RX_TSTAMP_ENABLED;
		otx2_config_hw_rx_tstamp(pf, true);
	पूर्ण

	pf->flags &= ~OTX2_FLAG_INTF_DOWN;
	/* 'intf_down' may be checked on any cpu */
	smp_wmb();

	/* we have alपढ़ोy received link status notअगरication */
	अगर (pf->linfo.link_up && !(pf->pcअगरunc & RVU_PFVF_FUNC_MASK))
		otx2_handle_link_event(pf);

	/* Restore छोड़ो frame settings */
	otx2_config_छोड़ो_frm(pf);

	err = otx2_rxtx_enable(pf, true);
	अगर (err)
		जाओ err_tx_stop_queues;

	वापस 0;

err_tx_stop_queues:
	netअगर_tx_stop_all_queues(netdev);
	netअगर_carrier_off(netdev);
err_मुक्त_cपूर्णांकs:
	otx2_मुक्त_cपूर्णांकs(pf, qidx);
	vec = pci_irq_vector(pf->pdev,
			     pf->hw.nix_msixoff + NIX_LF_QINT_VEC_START);
	otx2_ग_लिखो64(pf, NIX_LF_QINTX_ENA_W1C(0), BIT_ULL(0));
	synchronize_irq(vec);
	मुक्त_irq(vec, pf);
err_disable_napi:
	otx2_disable_napi(pf);
	otx2_मुक्त_hw_resources(pf);
err_मुक्त_mem:
	kमुक्त(qset->sq);
	kमुक्त(qset->cq);
	kमुक्त(qset->rq);
	kमुक्त(qset->napi);
	वापस err;
पूर्ण
EXPORT_SYMBOL(otx2_खोलो);

पूर्णांक otx2_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा otx2_nic *pf = netdev_priv(netdev);
	काष्ठा otx2_cq_poll *cq_poll = शून्य;
	काष्ठा otx2_qset *qset = &pf->qset;
	काष्ठा otx2_rss_info *rss;
	पूर्णांक qidx, vec, wrk;

	netअगर_carrier_off(netdev);
	netअगर_tx_stop_all_queues(netdev);

	pf->flags |= OTX2_FLAG_INTF_DOWN;
	/* 'intf_down' may be checked on any cpu */
	smp_wmb();

	/* First stop packet Rx/Tx */
	otx2_rxtx_enable(pf, false);

	/* Clear RSS enable flag */
	rss = &pf->hw.rss_info;
	rss->enable = false;

	/* Cleanup Queue IRQ */
	vec = pci_irq_vector(pf->pdev,
			     pf->hw.nix_msixoff + NIX_LF_QINT_VEC_START);
	otx2_ग_लिखो64(pf, NIX_LF_QINTX_ENA_W1C(0), BIT_ULL(0));
	synchronize_irq(vec);
	मुक्त_irq(vec, pf);

	/* Cleanup CQ NAPI and IRQ */
	vec = pf->hw.nix_msixoff + NIX_LF_CINT_VEC_START;
	क्रम (qidx = 0; qidx < pf->hw.cपूर्णांक_cnt; qidx++) अणु
		/* Disable पूर्णांकerrupt */
		otx2_ग_लिखो64(pf, NIX_LF_CINTX_ENA_W1C(qidx), BIT_ULL(0));

		synchronize_irq(pci_irq_vector(pf->pdev, vec));

		cq_poll = &qset->napi[qidx];
		napi_synchronize(&cq_poll->napi);
		vec++;
	पूर्ण

	netअगर_tx_disable(netdev);

	otx2_मुक्त_hw_resources(pf);
	otx2_मुक्त_cपूर्णांकs(pf, pf->hw.cपूर्णांक_cnt);
	otx2_disable_napi(pf);

	क्रम (qidx = 0; qidx < netdev->num_tx_queues; qidx++)
		netdev_tx_reset_queue(netdev_get_tx_queue(netdev, qidx));

	क्रम (wrk = 0; wrk < pf->qset.cq_cnt; wrk++)
		cancel_delayed_work_sync(&pf->refill_wrk[wrk].pool_refill_work);
	devm_kमुक्त(pf->dev, pf->refill_wrk);

	kमुक्त(qset->sq);
	kमुक्त(qset->cq);
	kमुक्त(qset->rq);
	kमुक्त(qset->napi);
	/* Do not clear RQ/SQ ringsize settings */
	स_रखो((व्योम *)qset + दुरत्व(काष्ठा otx2_qset, sqe_cnt), 0,
	       माप(*qset) - दुरत्व(काष्ठा otx2_qset, sqe_cnt));
	वापस 0;
पूर्ण
EXPORT_SYMBOL(otx2_stop);

अटल netdev_tx_t otx2_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा otx2_nic *pf = netdev_priv(netdev);
	पूर्णांक qidx = skb_get_queue_mapping(skb);
	काष्ठा otx2_snd_queue *sq;
	काष्ठा netdev_queue *txq;

	/* Check क्रम minimum and maximum packet length */
	अगर (skb->len <= ETH_HLEN ||
	    (!skb_shinfo(skb)->gso_size && skb->len > pf->max_frs)) अणु
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	sq = &pf->qset.sq[qidx];
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

अटल netdev_features_t otx2_fix_features(काष्ठा net_device *dev,
					   netdev_features_t features)
अणु
	/* check अगर n-tuple filters are ON */
	अगर ((features & NETIF_F_HW_TC) && (dev->features & NETIF_F_NTUPLE)) अणु
		netdev_info(dev, "Disabling n-tuple filters\n");
		features &= ~NETIF_F_NTUPLE;
	पूर्ण

	/* check अगर tc hw offload is ON */
	अगर ((features & NETIF_F_NTUPLE) && (dev->features & NETIF_F_HW_TC)) अणु
		netdev_info(dev, "Disabling TC hardware offload\n");
		features &= ~NETIF_F_HW_TC;
	पूर्ण

	वापस features;
पूर्ण

अटल व्योम otx2_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा otx2_nic *pf = netdev_priv(netdev);

	queue_work(pf->otx2_wq, &pf->rx_mode_work);
पूर्ण

अटल व्योम otx2_करो_set_rx_mode(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा otx2_nic *pf = container_of(work, काष्ठा otx2_nic, rx_mode_work);
	काष्ठा net_device *netdev = pf->netdev;
	काष्ठा nix_rx_mode *req;
	bool promisc = false;

	अगर (!(netdev->flags & IFF_UP))
		वापस;

	अगर ((netdev->flags & IFF_PROMISC) ||
	    (netdev_uc_count(netdev) > OTX2_MAX_UNICAST_FLOWS)) अणु
		promisc = true;
	पूर्ण

	/* Write unicast address to mcam entries or del from mcam */
	अगर (!promisc && netdev->priv_flags & IFF_UNICAST_FLT)
		__dev_uc_sync(netdev, otx2_add_macfilter, otx2_del_macfilter);

	mutex_lock(&pf->mbox.lock);
	req = otx2_mbox_alloc_msg_nix_set_rx_mode(&pf->mbox);
	अगर (!req) अणु
		mutex_unlock(&pf->mbox.lock);
		वापस;
	पूर्ण

	req->mode = NIX_RX_MODE_UCAST;

	अगर (promisc)
		req->mode |= NIX_RX_MODE_PROMISC;
	अन्यथा अगर (netdev->flags & (IFF_ALLMULTI | IFF_MULTICAST))
		req->mode |= NIX_RX_MODE_ALLMULTI;

	otx2_sync_mbox_msg(&pf->mbox);
	mutex_unlock(&pf->mbox.lock);
पूर्ण

अटल पूर्णांक otx2_set_features(काष्ठा net_device *netdev,
			     netdev_features_t features)
अणु
	netdev_features_t changed = features ^ netdev->features;
	bool ntuple = !!(features & NETIF_F_NTUPLE);
	काष्ठा otx2_nic *pf = netdev_priv(netdev);

	अगर ((changed & NETIF_F_LOOPBACK) && netअगर_running(netdev))
		वापस otx2_cgx_config_loopback(pf,
						features & NETIF_F_LOOPBACK);

	अगर ((changed & NETIF_F_HW_VLAN_CTAG_RX) && netअगर_running(netdev))
		वापस otx2_enable_rxvlan(pf,
					  features & NETIF_F_HW_VLAN_CTAG_RX);

	अगर ((changed & NETIF_F_NTUPLE) && !ntuple)
		otx2_destroy_ntuple_flows(pf);

	अगर ((netdev->features & NETIF_F_HW_TC) > (features & NETIF_F_HW_TC) &&
	    pf->tc_info.num_entries) अणु
		netdev_err(netdev, "Can't disable TC hardware offload while flows are active\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम otx2_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा otx2_nic *pf = container_of(work, काष्ठा otx2_nic, reset_task);

	अगर (!netअगर_running(pf->netdev))
		वापस;

	rtnl_lock();
	otx2_stop(pf->netdev);
	pf->reset_count++;
	otx2_खोलो(pf->netdev);
	netअगर_trans_update(pf->netdev);
	rtnl_unlock();
पूर्ण

अटल पूर्णांक otx2_config_hw_rx_tstamp(काष्ठा otx2_nic *pfvf, bool enable)
अणु
	काष्ठा msg_req *req;
	पूर्णांक err;

	अगर (pfvf->flags & OTX2_FLAG_RX_TSTAMP_ENABLED && enable)
		वापस 0;

	mutex_lock(&pfvf->mbox.lock);
	अगर (enable)
		req = otx2_mbox_alloc_msg_cgx_ptp_rx_enable(&pfvf->mbox);
	अन्यथा
		req = otx2_mbox_alloc_msg_cgx_ptp_rx_disable(&pfvf->mbox);
	अगर (!req) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	err = otx2_sync_mbox_msg(&pfvf->mbox);
	अगर (err) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस err;
	पूर्ण

	mutex_unlock(&pfvf->mbox.lock);
	अगर (enable)
		pfvf->flags |= OTX2_FLAG_RX_TSTAMP_ENABLED;
	अन्यथा
		pfvf->flags &= ~OTX2_FLAG_RX_TSTAMP_ENABLED;
	वापस 0;
पूर्ण

अटल पूर्णांक otx2_config_hw_tx_tstamp(काष्ठा otx2_nic *pfvf, bool enable)
अणु
	काष्ठा msg_req *req;
	पूर्णांक err;

	अगर (pfvf->flags & OTX2_FLAG_TX_TSTAMP_ENABLED && enable)
		वापस 0;

	mutex_lock(&pfvf->mbox.lock);
	अगर (enable)
		req = otx2_mbox_alloc_msg_nix_lf_ptp_tx_enable(&pfvf->mbox);
	अन्यथा
		req = otx2_mbox_alloc_msg_nix_lf_ptp_tx_disable(&pfvf->mbox);
	अगर (!req) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	err = otx2_sync_mbox_msg(&pfvf->mbox);
	अगर (err) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस err;
	पूर्ण

	mutex_unlock(&pfvf->mbox.lock);
	अगर (enable)
		pfvf->flags |= OTX2_FLAG_TX_TSTAMP_ENABLED;
	अन्यथा
		pfvf->flags &= ~OTX2_FLAG_TX_TSTAMP_ENABLED;
	वापस 0;
पूर्ण

अटल पूर्णांक otx2_config_hwtstamp(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);
	काष्ठा hwtstamp_config config;

	अगर (!pfvf->ptp)
		वापस -ENODEV;

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	/* reserved क्रम future extensions */
	अगर (config.flags)
		वापस -EINVAL;

	चयन (config.tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
		otx2_config_hw_tx_tstamp(pfvf, false);
		अवरोध;
	हाल HWTSTAMP_TX_ON:
		otx2_config_hw_tx_tstamp(pfvf, true);
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	चयन (config.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		otx2_config_hw_rx_tstamp(pfvf, false);
		अवरोध;
	हाल HWTSTAMP_FILTER_ALL:
	हाल HWTSTAMP_FILTER_SOME:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		otx2_config_hw_rx_tstamp(pfvf, true);
		config.rx_filter = HWTSTAMP_FILTER_ALL;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	स_नकल(&pfvf->tstamp, &config, माप(config));

	वापस copy_to_user(अगरr->अगरr_data, &config,
			    माप(config)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक otx2_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *req, पूर्णांक cmd)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);
	काष्ठा hwtstamp_config *cfg = &pfvf->tstamp;

	चयन (cmd) अणु
	हाल SIOCSHWTSTAMP:
		वापस otx2_config_hwtstamp(netdev, req);
	हाल SIOCGHWTSTAMP:
		वापस copy_to_user(req->अगरr_data, cfg,
				    माप(*cfg)) ? -EFAULT : 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक otx2_करो_set_vf_mac(काष्ठा otx2_nic *pf, पूर्णांक vf, स्थिर u8 *mac)
अणु
	काष्ठा npc_install_flow_req *req;
	पूर्णांक err;

	mutex_lock(&pf->mbox.lock);
	req = otx2_mbox_alloc_msg_npc_install_flow(&pf->mbox);
	अगर (!req) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	ether_addr_copy(req->packet.dmac, mac);
	eth_broadcast_addr((u8 *)&req->mask.dmac);
	req->features = BIT_ULL(NPC_DMAC);
	req->channel = pf->hw.rx_chan_base;
	req->पूर्णांकf = NIX_INTF_RX;
	req->शेष_rule = 1;
	req->append = 1;
	req->vf = vf + 1;
	req->op = NIX_RX_ACTION_DEFAULT;

	err = otx2_sync_mbox_msg(&pf->mbox);
out:
	mutex_unlock(&pf->mbox.lock);
	वापस err;
पूर्ण

अटल पूर्णांक otx2_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक vf, u8 *mac)
अणु
	काष्ठा otx2_nic *pf = netdev_priv(netdev);
	काष्ठा pci_dev *pdev = pf->pdev;
	काष्ठा otx2_vf_config *config;
	पूर्णांक ret;

	अगर (!netअगर_running(netdev))
		वापस -EAGAIN;

	अगर (vf >= pci_num_vf(pdev))
		वापस -EINVAL;

	अगर (!is_valid_ether_addr(mac))
		वापस -EINVAL;

	config = &pf->vf_configs[vf];
	ether_addr_copy(config->mac, mac);

	ret = otx2_करो_set_vf_mac(pf, vf, mac);
	अगर (ret == 0)
		dev_info(&pdev->dev, "Reload VF driver to apply the changes\n");

	वापस ret;
पूर्ण

अटल पूर्णांक otx2_करो_set_vf_vlan(काष्ठा otx2_nic *pf, पूर्णांक vf, u16 vlan, u8 qos,
			       __be16 proto)
अणु
	काष्ठा otx2_flow_config *flow_cfg = pf->flow_cfg;
	काष्ठा nix_vtag_config_rsp *vtag_rsp;
	काष्ठा npc_delete_flow_req *del_req;
	काष्ठा nix_vtag_config *vtag_req;
	काष्ठा npc_install_flow_req *req;
	काष्ठा otx2_vf_config *config;
	पूर्णांक err = 0;
	u32 idx;

	config = &pf->vf_configs[vf];

	अगर (!vlan && !config->vlan)
		जाओ out;

	mutex_lock(&pf->mbox.lock);

	/* मुक्त old tx vtag entry */
	अगर (config->vlan) अणु
		vtag_req = otx2_mbox_alloc_msg_nix_vtag_cfg(&pf->mbox);
		अगर (!vtag_req) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		vtag_req->cfg_type = 0;
		vtag_req->tx.मुक्त_vtag0 = 1;
		vtag_req->tx.vtag0_idx = config->tx_vtag_idx;

		err = otx2_sync_mbox_msg(&pf->mbox);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (!vlan && config->vlan) अणु
		/* rx */
		del_req = otx2_mbox_alloc_msg_npc_delete_flow(&pf->mbox);
		अगर (!del_req) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		idx = ((vf * OTX2_PER_VF_VLAN_FLOWS) + OTX2_VF_VLAN_RX_INDEX);
		del_req->entry =
			flow_cfg->entry[flow_cfg->vf_vlan_offset + idx];
		err = otx2_sync_mbox_msg(&pf->mbox);
		अगर (err)
			जाओ out;

		/* tx */
		del_req = otx2_mbox_alloc_msg_npc_delete_flow(&pf->mbox);
		अगर (!del_req) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		idx = ((vf * OTX2_PER_VF_VLAN_FLOWS) + OTX2_VF_VLAN_TX_INDEX);
		del_req->entry =
			flow_cfg->entry[flow_cfg->vf_vlan_offset + idx];
		err = otx2_sync_mbox_msg(&pf->mbox);

		जाओ out;
	पूर्ण

	/* rx */
	req = otx2_mbox_alloc_msg_npc_install_flow(&pf->mbox);
	अगर (!req) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	idx = ((vf * OTX2_PER_VF_VLAN_FLOWS) + OTX2_VF_VLAN_RX_INDEX);
	req->entry = flow_cfg->entry[flow_cfg->vf_vlan_offset + idx];
	req->packet.vlan_tci = htons(vlan);
	req->mask.vlan_tci = htons(VLAN_VID_MASK);
	/* af fills the destination mac addr */
	eth_broadcast_addr((u8 *)&req->mask.dmac);
	req->features = BIT_ULL(NPC_OUTER_VID) | BIT_ULL(NPC_DMAC);
	req->channel = pf->hw.rx_chan_base;
	req->पूर्णांकf = NIX_INTF_RX;
	req->vf = vf + 1;
	req->op = NIX_RX_ACTION_DEFAULT;
	req->vtag0_valid = true;
	req->vtag0_type = NIX_AF_LFX_RX_VTAG_TYPE7;
	req->set_cntr = 1;

	err = otx2_sync_mbox_msg(&pf->mbox);
	अगर (err)
		जाओ out;

	/* tx */
	vtag_req = otx2_mbox_alloc_msg_nix_vtag_cfg(&pf->mbox);
	अगर (!vtag_req) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	/* configure tx vtag params */
	vtag_req->vtag_size = VTAGSIZE_T4;
	vtag_req->cfg_type = 0; /* tx vlan cfg */
	vtag_req->tx.cfg_vtag0 = 1;
	vtag_req->tx.vtag0 = ((u64)ntohs(proto) << 16) | vlan;

	err = otx2_sync_mbox_msg(&pf->mbox);
	अगर (err)
		जाओ out;

	vtag_rsp = (काष्ठा nix_vtag_config_rsp *)otx2_mbox_get_rsp
			(&pf->mbox.mbox, 0, &vtag_req->hdr);
	अगर (IS_ERR(vtag_rsp)) अणु
		err = PTR_ERR(vtag_rsp);
		जाओ out;
	पूर्ण
	config->tx_vtag_idx = vtag_rsp->vtag0_idx;

	req = otx2_mbox_alloc_msg_npc_install_flow(&pf->mbox);
	अगर (!req) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	eth_zero_addr((u8 *)&req->mask.dmac);
	idx = ((vf * OTX2_PER_VF_VLAN_FLOWS) + OTX2_VF_VLAN_TX_INDEX);
	req->entry = flow_cfg->entry[flow_cfg->vf_vlan_offset + idx];
	req->features = BIT_ULL(NPC_DMAC);
	req->channel = pf->hw.tx_chan_base;
	req->पूर्णांकf = NIX_INTF_TX;
	req->vf = vf + 1;
	req->op = NIX_TX_ACTIONOP_UCAST_DEFAULT;
	req->vtag0_def = vtag_rsp->vtag0_idx;
	req->vtag0_op = VTAG_INSERT;
	req->set_cntr = 1;

	err = otx2_sync_mbox_msg(&pf->mbox);
out:
	config->vlan = vlan;
	mutex_unlock(&pf->mbox.lock);
	वापस err;
पूर्ण

अटल पूर्णांक otx2_set_vf_vlan(काष्ठा net_device *netdev, पूर्णांक vf, u16 vlan, u8 qos,
			    __be16 proto)
अणु
	काष्ठा otx2_nic *pf = netdev_priv(netdev);
	काष्ठा pci_dev *pdev = pf->pdev;

	अगर (!netअगर_running(netdev))
		वापस -EAGAIN;

	अगर (vf >= pci_num_vf(pdev))
		वापस -EINVAL;

	/* qos is currently unsupported */
	अगर (vlan >= VLAN_N_VID || qos)
		वापस -EINVAL;

	अगर (proto != htons(ETH_P_8021Q))
		वापस -EPROTONOSUPPORT;

	अगर (!(pf->flags & OTX2_FLAG_VF_VLAN_SUPPORT))
		वापस -EOPNOTSUPP;

	वापस otx2_करो_set_vf_vlan(pf, vf, vlan, qos, proto);
पूर्ण

अटल पूर्णांक otx2_get_vf_config(काष्ठा net_device *netdev, पूर्णांक vf,
			      काष्ठा अगरla_vf_info *ivi)
अणु
	काष्ठा otx2_nic *pf = netdev_priv(netdev);
	काष्ठा pci_dev *pdev = pf->pdev;
	काष्ठा otx2_vf_config *config;

	अगर (!netअगर_running(netdev))
		वापस -EAGAIN;

	अगर (vf >= pci_num_vf(pdev))
		वापस -EINVAL;

	config = &pf->vf_configs[vf];
	ivi->vf = vf;
	ether_addr_copy(ivi->mac, config->mac);
	ivi->vlan = config->vlan;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops otx2_netdev_ops = अणु
	.nकरो_खोलो		= otx2_खोलो,
	.nकरो_stop		= otx2_stop,
	.nकरो_start_xmit		= otx2_xmit,
	.nकरो_fix_features	= otx2_fix_features,
	.nकरो_set_mac_address    = otx2_set_mac_address,
	.nकरो_change_mtu		= otx2_change_mtu,
	.nकरो_set_rx_mode	= otx2_set_rx_mode,
	.nकरो_set_features	= otx2_set_features,
	.nकरो_tx_समयout		= otx2_tx_समयout,
	.nकरो_get_stats64	= otx2_get_stats64,
	.nकरो_करो_ioctl		= otx2_ioctl,
	.nकरो_set_vf_mac		= otx2_set_vf_mac,
	.nकरो_set_vf_vlan	= otx2_set_vf_vlan,
	.nकरो_get_vf_config	= otx2_get_vf_config,
	.nकरो_setup_tc		= otx2_setup_tc,
पूर्ण;

अटल पूर्णांक otx2_wq_init(काष्ठा otx2_nic *pf)
अणु
	pf->otx2_wq = create_singlethपढ़ो_workqueue("otx2_wq");
	अगर (!pf->otx2_wq)
		वापस -ENOMEM;

	INIT_WORK(&pf->rx_mode_work, otx2_करो_set_rx_mode);
	INIT_WORK(&pf->reset_task, otx2_reset_task);
	वापस 0;
पूर्ण

अटल पूर्णांक otx2_check_pf_usable(काष्ठा otx2_nic *nic)
अणु
	u64 rev;

	rev = otx2_पढ़ो64(nic, RVU_PF_BLOCK_ADDRX_DISC(BLKADDR_RVUM));
	rev = (rev >> 12) & 0xFF;
	/* Check अगर AF has setup revision क्रम RVUM block,
	 * otherwise this driver probe should be deferred
	 * until AF driver comes up.
	 */
	अगर (!rev) अणु
		dev_warn(nic->dev,
			 "AF is not initialized, deferring probe\n");
		वापस -EPROBE_DEFER;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक otx2_पुनः_स्मृति_msix_vectors(काष्ठा otx2_nic *pf)
अणु
	काष्ठा otx2_hw *hw = &pf->hw;
	पूर्णांक num_vec, err;

	/* NPA पूर्णांकerrupts are inot रेजिस्टरed, so alloc only
	 * upto NIX vector offset.
	 */
	num_vec = hw->nix_msixoff;
	num_vec += NIX_LF_CINT_VEC_START + hw->max_queues;

	otx2_disable_mbox_पूर्णांकr(pf);
	pci_मुक्त_irq_vectors(hw->pdev);
	err = pci_alloc_irq_vectors(hw->pdev, num_vec, num_vec, PCI_IRQ_MSIX);
	अगर (err < 0) अणु
		dev_err(pf->dev, "%s: Failed to realloc %d IRQ vectors\n",
			__func__, num_vec);
		वापस err;
	पूर्ण

	वापस otx2_रेजिस्टर_mbox_पूर्णांकr(pf, false);
पूर्ण

अटल पूर्णांक otx2_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा net_device *netdev;
	काष्ठा otx2_nic *pf;
	काष्ठा otx2_hw *hw;
	पूर्णांक err, qcount;
	पूर्णांक num_vec;

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

	/* Set number of queues */
	qcount = min_t(पूर्णांक, num_online_cpus(), OTX2_MAX_CQ_CNT);

	netdev = alloc_etherdev_mqs(माप(*pf), qcount, qcount);
	अगर (!netdev) अणु
		err = -ENOMEM;
		जाओ err_release_regions;
	पूर्ण

	pci_set_drvdata(pdev, netdev);
	SET_NETDEV_DEV(netdev, &pdev->dev);
	pf = netdev_priv(netdev);
	pf->netdev = netdev;
	pf->pdev = pdev;
	pf->dev = dev;
	pf->total_vfs = pci_sriov_get_totalvfs(pdev);
	pf->flags |= OTX2_FLAG_INTF_DOWN;

	hw = &pf->hw;
	hw->pdev = pdev;
	hw->rx_queues = qcount;
	hw->tx_queues = qcount;
	hw->max_queues = qcount;

	num_vec = pci_msix_vec_count(pdev);
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

	/* Map CSRs */
	pf->reg_base = pcim_iomap(pdev, PCI_CFG_REG_BAR_NUM, 0);
	अगर (!pf->reg_base) अणु
		dev_err(dev, "Unable to map physical function CSRs, aborting\n");
		err = -ENOMEM;
		जाओ err_मुक्त_netdev;
	पूर्ण

	err = otx2_check_pf_usable(pf);
	अगर (err)
		जाओ err_मुक्त_netdev;

	err = pci_alloc_irq_vectors(hw->pdev, RVU_PF_INT_VEC_CNT,
				    RVU_PF_INT_VEC_CNT, PCI_IRQ_MSIX);
	अगर (err < 0) अणु
		dev_err(dev, "%s: Failed to alloc %d IRQ vectors\n",
			__func__, num_vec);
		जाओ err_मुक्त_netdev;
	पूर्ण

	otx2_setup_dev_hw_settings(pf);

	/* Init PF <=> AF mailbox stuff */
	err = otx2_pfaf_mbox_init(pf);
	अगर (err)
		जाओ err_मुक्त_irq_vectors;

	/* Register mailbox पूर्णांकerrupt */
	err = otx2_रेजिस्टर_mbox_पूर्णांकr(pf, true);
	अगर (err)
		जाओ err_mbox_destroy;

	/* Request AF to attach NPA and NIX LFs to this PF.
	 * NIX and NPA LFs are needed क्रम this PF to function as a NIC.
	 */
	err = otx2_attach_npa_nix(pf);
	अगर (err)
		जाओ err_disable_mbox_पूर्णांकr;

	err = otx2_पुनः_स्मृति_msix_vectors(pf);
	अगर (err)
		जाओ err_detach_rsrc;

	err = otx2_set_real_num_queues(netdev, hw->tx_queues, hw->rx_queues);
	अगर (err)
		जाओ err_detach_rsrc;

	err = cn10k_pf_lmtst_init(pf);
	अगर (err)
		जाओ err_detach_rsrc;

	/* Assign शेष mac address */
	otx2_get_mac_from_af(netdev);

	/* Don't check क्रम error.  Proceed without ptp */
	otx2_ptp_init(pf);

	/* NPA's pool is a stack to which SW मुक्तs buffer poपूर्णांकers via Aura.
	 * HW allocates buffer poपूर्णांकer from stack and uses it क्रम DMA'ing
	 * ingress packet. In some scenarios HW can मुक्त back allocated buffer
	 * poपूर्णांकers to pool. This makes it impossible क्रम SW to मुख्यtain a
	 * parallel list where physical addresses of buffer poपूर्णांकers (IOVAs)
	 * given to HW can be saved क्रम later reference.
	 *
	 * So the only way to convert Rx packet's buffer address is to use
	 * IOMMU's iova_to_phys() handler which translates the address by
	 * walking through the translation tables.
	 */
	pf->iommu_करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);

	netdev->hw_features = (NETIF_F_RXCSUM | NETIF_F_IP_CSUM |
			       NETIF_F_IPV6_CSUM | NETIF_F_RXHASH |
			       NETIF_F_SG | NETIF_F_TSO | NETIF_F_TSO6 |
			       NETIF_F_GSO_UDP_L4);
	netdev->features |= netdev->hw_features;

	netdev->hw_features |= NETIF_F_LOOPBACK | NETIF_F_RXALL;

	err = otx2_mcam_flow_init(pf);
	अगर (err)
		जाओ err_ptp_destroy;

	अगर (pf->flags & OTX2_FLAG_NTUPLE_SUPPORT)
		netdev->hw_features |= NETIF_F_NTUPLE;

	अगर (pf->flags & OTX2_FLAG_UCAST_FLTR_SUPPORT)
		netdev->priv_flags |= IFF_UNICAST_FLT;

	/* Support TSO on tag पूर्णांकerface */
	netdev->vlan_features |= netdev->features;
	netdev->hw_features  |= NETIF_F_HW_VLAN_CTAG_TX |
				NETIF_F_HW_VLAN_STAG_TX;
	अगर (pf->flags & OTX2_FLAG_RX_VLAN_SUPPORT)
		netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_RX |
				       NETIF_F_HW_VLAN_STAG_RX;
	netdev->features |= netdev->hw_features;

	/* HW supports tc offload but mutually exclusive with n-tuple filters */
	अगर (pf->flags & OTX2_FLAG_TC_FLOWER_SUPPORT)
		netdev->hw_features |= NETIF_F_HW_TC;

	netdev->gso_max_segs = OTX2_MAX_GSO_SEGS;
	netdev->watchकरोg_समयo = OTX2_TX_TIMEOUT;

	netdev->netdev_ops = &otx2_netdev_ops;

	/* MTU range: 64 - 9190 */
	netdev->min_mtu = OTX2_MIN_MTU;
	netdev->max_mtu = otx2_get_max_mtu(pf);

	err = रेजिस्टर_netdev(netdev);
	अगर (err) अणु
		dev_err(dev, "Failed to register netdevice\n");
		जाओ err_del_mcam_entries;
	पूर्ण

	err = otx2_wq_init(pf);
	अगर (err)
		जाओ err_unreg_netdev;

	otx2_set_ethtool_ops(netdev);

	err = otx2_init_tc(pf);
	अगर (err)
		जाओ err_mcam_flow_del;

	/* Enable link notअगरications */
	otx2_cgx_config_linkevents(pf, true);

	/* Enable छोड़ो frames by शेष */
	pf->flags |= OTX2_FLAG_RX_PAUSE_ENABLED;
	pf->flags |= OTX2_FLAG_TX_PAUSE_ENABLED;

	वापस 0;

err_mcam_flow_del:
	otx2_mcam_flow_del(pf);
err_unreg_netdev:
	unरेजिस्टर_netdev(netdev);
err_del_mcam_entries:
	otx2_mcam_flow_del(pf);
err_ptp_destroy:
	otx2_ptp_destroy(pf);
err_detach_rsrc:
	अगर (hw->lmt_base)
		iounmap(hw->lmt_base);
	otx2_detach_resources(&pf->mbox);
err_disable_mbox_पूर्णांकr:
	otx2_disable_mbox_पूर्णांकr(pf);
err_mbox_destroy:
	otx2_pfaf_mbox_destroy(pf);
err_मुक्त_irq_vectors:
	pci_मुक्त_irq_vectors(hw->pdev);
err_मुक्त_netdev:
	pci_set_drvdata(pdev, शून्य);
	मुक्त_netdev(netdev);
err_release_regions:
	pci_release_regions(pdev);
	वापस err;
पूर्ण

अटल व्योम otx2_vf_link_event_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा otx2_vf_config *config;
	काष्ठा cgx_link_info_msg *req;
	काष्ठा mbox_msghdr *msghdr;
	काष्ठा otx2_nic *pf;
	पूर्णांक vf_idx;

	config = container_of(work, काष्ठा otx2_vf_config,
			      link_event_work.work);
	vf_idx = config - config->pf->vf_configs;
	pf = config->pf;

	msghdr = otx2_mbox_alloc_msg_rsp(&pf->mbox_pfvf[0].mbox_up, vf_idx,
					 माप(*req), माप(काष्ठा msg_rsp));
	अगर (!msghdr) अणु
		dev_err(pf->dev, "Failed to create VF%d link event\n", vf_idx);
		वापस;
	पूर्ण

	req = (काष्ठा cgx_link_info_msg *)msghdr;
	req->hdr.id = MBOX_MSG_CGX_LINK_EVENT;
	req->hdr.sig = OTX2_MBOX_REQ_SIG;
	स_नकल(&req->link_info, &pf->linfo, माप(req->link_info));

	otx2_sync_mbox_up_msg(&pf->mbox_pfvf[0], vf_idx);
पूर्ण

अटल पूर्णांक otx2_sriov_enable(काष्ठा pci_dev *pdev, पूर्णांक numvfs)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा otx2_nic *pf = netdev_priv(netdev);
	पूर्णांक ret, i;

	/* Init PF <=> VF mailbox stuff */
	ret = otx2_pfvf_mbox_init(pf, numvfs);
	अगर (ret)
		वापस ret;

	ret = otx2_रेजिस्टर_pfvf_mbox_पूर्णांकr(pf, numvfs);
	अगर (ret)
		जाओ मुक्त_mbox;

	pf->vf_configs = kसुस्मृति(numvfs, माप(काष्ठा otx2_vf_config),
				 GFP_KERNEL);
	अगर (!pf->vf_configs) अणु
		ret = -ENOMEM;
		जाओ मुक्त_पूर्णांकr;
	पूर्ण

	क्रम (i = 0; i < numvfs; i++) अणु
		pf->vf_configs[i].pf = pf;
		pf->vf_configs[i].पूर्णांकf_करोwn = true;
		INIT_DELAYED_WORK(&pf->vf_configs[i].link_event_work,
				  otx2_vf_link_event_task);
	पूर्ण

	ret = otx2_pf_flr_init(pf, numvfs);
	अगर (ret)
		जाओ मुक्त_configs;

	ret = otx2_रेजिस्टर_flr_me_पूर्णांकr(pf, numvfs);
	अगर (ret)
		जाओ मुक्त_flr;

	ret = pci_enable_sriov(pdev, numvfs);
	अगर (ret)
		जाओ मुक्त_flr_पूर्णांकr;

	वापस numvfs;
मुक्त_flr_पूर्णांकr:
	otx2_disable_flr_me_पूर्णांकr(pf);
मुक्त_flr:
	otx2_flr_wq_destroy(pf);
मुक्त_configs:
	kमुक्त(pf->vf_configs);
मुक्त_पूर्णांकr:
	otx2_disable_pfvf_mbox_पूर्णांकr(pf, numvfs);
मुक्त_mbox:
	otx2_pfvf_mbox_destroy(pf);
	वापस ret;
पूर्ण

अटल पूर्णांक otx2_sriov_disable(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा otx2_nic *pf = netdev_priv(netdev);
	पूर्णांक numvfs = pci_num_vf(pdev);
	पूर्णांक i;

	अगर (!numvfs)
		वापस 0;

	pci_disable_sriov(pdev);

	क्रम (i = 0; i < pci_num_vf(pdev); i++)
		cancel_delayed_work_sync(&pf->vf_configs[i].link_event_work);
	kमुक्त(pf->vf_configs);

	otx2_disable_flr_me_पूर्णांकr(pf);
	otx2_flr_wq_destroy(pf);
	otx2_disable_pfvf_mbox_पूर्णांकr(pf, numvfs);
	otx2_pfvf_mbox_destroy(pf);

	वापस 0;
पूर्ण

अटल पूर्णांक otx2_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक numvfs)
अणु
	अगर (numvfs == 0)
		वापस otx2_sriov_disable(pdev);
	अन्यथा
		वापस otx2_sriov_enable(pdev, numvfs);
पूर्ण

अटल व्योम otx2_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा otx2_nic *pf;

	अगर (!netdev)
		वापस;

	pf = netdev_priv(netdev);

	pf->flags |= OTX2_FLAG_PF_SHUTDOWN;

	अगर (pf->flags & OTX2_FLAG_TX_TSTAMP_ENABLED)
		otx2_config_hw_tx_tstamp(pf, false);
	अगर (pf->flags & OTX2_FLAG_RX_TSTAMP_ENABLED)
		otx2_config_hw_rx_tstamp(pf, false);

	cancel_work_sync(&pf->reset_task);
	/* Disable link notअगरications */
	otx2_cgx_config_linkevents(pf, false);

	unरेजिस्टर_netdev(netdev);
	otx2_sriov_disable(pf->pdev);
	अगर (pf->otx2_wq)
		destroy_workqueue(pf->otx2_wq);

	otx2_ptp_destroy(pf);
	otx2_mcam_flow_del(pf);
	otx2_shutकरोwn_tc(pf);
	otx2_detach_resources(&pf->mbox);
	अगर (pf->hw.lmt_base)
		iounmap(pf->hw.lmt_base);

	otx2_disable_mbox_पूर्णांकr(pf);
	otx2_pfaf_mbox_destroy(pf);
	pci_मुक्त_irq_vectors(pf->pdev);
	pci_set_drvdata(pdev, शून्य);
	मुक्त_netdev(netdev);

	pci_release_regions(pdev);
पूर्ण

अटल काष्ठा pci_driver otx2_pf_driver = अणु
	.name = DRV_NAME,
	.id_table = otx2_pf_id_table,
	.probe = otx2_probe,
	.shutकरोwn = otx2_हटाओ,
	.हटाओ = otx2_हटाओ,
	.sriov_configure = otx2_sriov_configure
पूर्ण;

अटल पूर्णांक __init otx2_rvupf_init_module(व्योम)
अणु
	pr_info("%s: %s\n", DRV_NAME, DRV_STRING);

	वापस pci_रेजिस्टर_driver(&otx2_pf_driver);
पूर्ण

अटल व्योम __निकास otx2_rvupf_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&otx2_pf_driver);
पूर्ण

module_init(otx2_rvupf_init_module);
module_निकास(otx2_rvupf_cleanup_module);
