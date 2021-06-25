<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2020 Marvell. */

#समावेश "otx2_cpt_common.h"
#समावेश "otx2_cptvf.h"
#समावेश <rvu_reg.h>

irqवापस_t otx2_cptvf_pfvf_mbox_पूर्णांकr(पूर्णांक __always_unused irq, व्योम *arg)
अणु
	काष्ठा otx2_cptvf_dev *cptvf = arg;
	u64 पूर्णांकr;

	/* Read the पूर्णांकerrupt bits */
	पूर्णांकr = otx2_cpt_पढ़ो64(cptvf->reg_base, BLKADDR_RVUM, 0,
			       OTX2_RVU_VF_INT);

	अगर (पूर्णांकr & 0x1ULL) अणु
		/* Schedule work queue function to process the MBOX request */
		queue_work(cptvf->pfvf_mbox_wq, &cptvf->pfvf_mbox_work);
		/* Clear and ack the पूर्णांकerrupt */
		otx2_cpt_ग_लिखो64(cptvf->reg_base, BLKADDR_RVUM, 0,
				 OTX2_RVU_VF_INT, 0x1ULL);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम process_pfvf_mbox_mbox_msg(काष्ठा otx2_cptvf_dev *cptvf,
				       काष्ठा mbox_msghdr *msg)
अणु
	काष्ठा otx2_cptlfs_info *lfs = &cptvf->lfs;
	काष्ठा otx2_cpt_kvf_limits_rsp *rsp_limits;
	काष्ठा otx2_cpt_egrp_num_rsp *rsp_grp;
	काष्ठा cpt_rd_wr_reg_msg *rsp_reg;
	काष्ठा msix_offset_rsp *rsp_msix;
	पूर्णांक i;

	अगर (msg->id >= MBOX_MSG_MAX) अणु
		dev_err(&cptvf->pdev->dev,
			"MBOX msg with unknown ID %d\n", msg->id);
		वापस;
	पूर्ण
	अगर (msg->sig != OTX2_MBOX_RSP_SIG) अणु
		dev_err(&cptvf->pdev->dev,
			"MBOX msg with wrong signature %x, ID %d\n",
			msg->sig, msg->id);
		वापस;
	पूर्ण
	चयन (msg->id) अणु
	हाल MBOX_MSG_READY:
		cptvf->vf_id = ((msg->pcअगरunc >> RVU_PFVF_FUNC_SHIFT)
				& RVU_PFVF_FUNC_MASK) - 1;
		अवरोध;
	हाल MBOX_MSG_ATTACH_RESOURCES:
		/* Check अगर resources were successfully attached */
		अगर (!msg->rc)
			lfs->are_lfs_attached = 1;
		अवरोध;
	हाल MBOX_MSG_DETACH_RESOURCES:
		/* Check अगर resources were successfully detached */
		अगर (!msg->rc)
			lfs->are_lfs_attached = 0;
		अवरोध;
	हाल MBOX_MSG_MSIX_OFFSET:
		rsp_msix = (काष्ठा msix_offset_rsp *) msg;
		क्रम (i = 0; i < rsp_msix->cptlfs; i++)
			lfs->lf[i].msix_offset = rsp_msix->cptlf_msixoff[i];
		अवरोध;
	हाल MBOX_MSG_CPT_RD_WR_REGISTER:
		rsp_reg = (काष्ठा cpt_rd_wr_reg_msg *) msg;
		अगर (msg->rc) अणु
			dev_err(&cptvf->pdev->dev,
				"Reg %llx rd/wr(%d) failed %d\n",
				rsp_reg->reg_offset, rsp_reg->is_ग_लिखो,
				msg->rc);
			वापस;
		पूर्ण
		अगर (!rsp_reg->is_ग_लिखो)
			*rsp_reg->ret_val = rsp_reg->val;
		अवरोध;
	हाल MBOX_MSG_GET_ENG_GRP_NUM:
		rsp_grp = (काष्ठा otx2_cpt_egrp_num_rsp *) msg;
		cptvf->lfs.kcrypto_eng_grp_num = rsp_grp->eng_grp_num;
		अवरोध;
	हाल MBOX_MSG_GET_KVF_LIMITS:
		rsp_limits = (काष्ठा otx2_cpt_kvf_limits_rsp *) msg;
		cptvf->lfs.kvf_limits = rsp_limits->kvf_limits;
		अवरोध;
	शेष:
		dev_err(&cptvf->pdev->dev, "Unsupported msg %d received.\n",
			msg->id);
		अवरोध;
	पूर्ण
पूर्ण

व्योम otx2_cptvf_pfvf_mbox_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा otx2_cptvf_dev *cptvf;
	काष्ठा otx2_mbox *pfvf_mbox;
	काष्ठा otx2_mbox_dev *mdev;
	काष्ठा mbox_hdr *rsp_hdr;
	काष्ठा mbox_msghdr *msg;
	पूर्णांक offset, i;

	/* sync with mbox memory region */
	smp_rmb();

	cptvf = container_of(work, काष्ठा otx2_cptvf_dev, pfvf_mbox_work);
	pfvf_mbox = &cptvf->pfvf_mbox;
	mdev = &pfvf_mbox->dev[0];
	rsp_hdr = (काष्ठा mbox_hdr *)(mdev->mbase + pfvf_mbox->rx_start);
	अगर (rsp_hdr->num_msgs == 0)
		वापस;
	offset = ALIGN(माप(काष्ठा mbox_hdr), MBOX_MSG_ALIGN);

	क्रम (i = 0; i < rsp_hdr->num_msgs; i++) अणु
		msg = (काष्ठा mbox_msghdr *)(mdev->mbase + pfvf_mbox->rx_start +
					     offset);
		process_pfvf_mbox_mbox_msg(cptvf, msg);
		offset = msg->next_msgoff;
		mdev->msgs_acked++;
	पूर्ण
	otx2_mbox_reset(pfvf_mbox, 0);
पूर्ण

पूर्णांक otx2_cptvf_send_eng_grp_num_msg(काष्ठा otx2_cptvf_dev *cptvf, पूर्णांक eng_type)
अणु
	काष्ठा otx2_mbox *mbox = &cptvf->pfvf_mbox;
	काष्ठा pci_dev *pdev = cptvf->pdev;
	काष्ठा otx2_cpt_egrp_num_msg *req;

	req = (काष्ठा otx2_cpt_egrp_num_msg *)
	      otx2_mbox_alloc_msg_rsp(mbox, 0, माप(*req),
				      माप(काष्ठा otx2_cpt_egrp_num_rsp));
	अगर (req == शून्य) अणु
		dev_err(&pdev->dev, "RVU MBOX failed to get message.\n");
		वापस -EFAULT;
	पूर्ण
	req->hdr.id = MBOX_MSG_GET_ENG_GRP_NUM;
	req->hdr.sig = OTX2_MBOX_REQ_SIG;
	req->hdr.pcअगरunc = OTX2_CPT_RVU_PFFUNC(cptvf->vf_id, 0);
	req->eng_type = eng_type;

	वापस otx2_cpt_send_mbox_msg(mbox, pdev);
पूर्ण

पूर्णांक otx2_cptvf_send_kvf_limits_msg(काष्ठा otx2_cptvf_dev *cptvf)
अणु
	काष्ठा otx2_mbox *mbox = &cptvf->pfvf_mbox;
	काष्ठा pci_dev *pdev = cptvf->pdev;
	काष्ठा mbox_msghdr *req;
	पूर्णांक ret;

	req = (काष्ठा mbox_msghdr *)
	      otx2_mbox_alloc_msg_rsp(mbox, 0, माप(*req),
				      माप(काष्ठा otx2_cpt_kvf_limits_rsp));
	अगर (req == शून्य) अणु
		dev_err(&pdev->dev, "RVU MBOX failed to get message.\n");
		वापस -EFAULT;
	पूर्ण
	req->id = MBOX_MSG_GET_KVF_LIMITS;
	req->sig = OTX2_MBOX_REQ_SIG;
	req->pcअगरunc = OTX2_CPT_RVU_PFFUNC(cptvf->vf_id, 0);

	ret = otx2_cpt_send_mbox_msg(mbox, pdev);

	वापस ret;
पूर्ण
