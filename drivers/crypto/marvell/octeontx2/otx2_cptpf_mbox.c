<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2020 Marvell. */

#समावेश "otx2_cpt_common.h"
#समावेश "otx2_cptpf.h"
#समावेश "rvu_reg.h"

/*
 * CPT PF driver version, It will be incremented by 1 क्रम every feature
 * addition in CPT mailbox messages.
 */
#घोषणा OTX2_CPT_PF_DRV_VERSION 0x1

अटल पूर्णांक क्रमward_to_af(काष्ठा otx2_cptpf_dev *cptpf,
			 काष्ठा otx2_cptvf_info *vf,
			 काष्ठा mbox_msghdr *req, पूर्णांक size)
अणु
	काष्ठा mbox_msghdr *msg;
	पूर्णांक ret;

	msg = otx2_mbox_alloc_msg(&cptpf->afpf_mbox, 0, size);
	अगर (msg == शून्य)
		वापस -ENOMEM;

	स_नकल((uपूर्णांक8_t *)msg + माप(काष्ठा mbox_msghdr),
	       (uपूर्णांक8_t *)req + माप(काष्ठा mbox_msghdr), size);
	msg->id = req->id;
	msg->pcअगरunc = req->pcअगरunc;
	msg->sig = req->sig;
	msg->ver = req->ver;

	otx2_mbox_msg_send(&cptpf->afpf_mbox, 0);
	ret = otx2_mbox_रुको_क्रम_rsp(&cptpf->afpf_mbox, 0);
	अगर (ret == -EIO) अणु
		dev_err(&cptpf->pdev->dev, "RVU MBOX timeout.\n");
		वापस ret;
	पूर्ण अन्यथा अगर (ret) अणु
		dev_err(&cptpf->pdev->dev, "RVU MBOX error: %d.\n", ret);
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक handle_msg_get_caps(काष्ठा otx2_cptpf_dev *cptpf,
			       काष्ठा otx2_cptvf_info *vf,
			       काष्ठा mbox_msghdr *req)
अणु
	काष्ठा otx2_cpt_caps_rsp *rsp;

	rsp = (काष्ठा otx2_cpt_caps_rsp *)
	      otx2_mbox_alloc_msg(&cptpf->vfpf_mbox, vf->vf_id,
				  माप(*rsp));
	अगर (!rsp)
		वापस -ENOMEM;

	rsp->hdr.id = MBOX_MSG_GET_CAPS;
	rsp->hdr.sig = OTX2_MBOX_RSP_SIG;
	rsp->hdr.pcअगरunc = req->pcअगरunc;
	rsp->cpt_pf_drv_version = OTX2_CPT_PF_DRV_VERSION;
	rsp->cpt_revision = cptpf->pdev->revision;
	स_नकल(&rsp->eng_caps, &cptpf->eng_caps, माप(rsp->eng_caps));

	वापस 0;
पूर्ण

अटल पूर्णांक handle_msg_get_eng_grp_num(काष्ठा otx2_cptpf_dev *cptpf,
				      काष्ठा otx2_cptvf_info *vf,
				      काष्ठा mbox_msghdr *req)
अणु
	काष्ठा otx2_cpt_egrp_num_msg *grp_req;
	काष्ठा otx2_cpt_egrp_num_rsp *rsp;

	grp_req = (काष्ठा otx2_cpt_egrp_num_msg *)req;
	rsp = (काष्ठा otx2_cpt_egrp_num_rsp *)
	       otx2_mbox_alloc_msg(&cptpf->vfpf_mbox, vf->vf_id, माप(*rsp));
	अगर (!rsp)
		वापस -ENOMEM;

	rsp->hdr.id = MBOX_MSG_GET_ENG_GRP_NUM;
	rsp->hdr.sig = OTX2_MBOX_RSP_SIG;
	rsp->hdr.pcअगरunc = req->pcअगरunc;
	rsp->eng_type = grp_req->eng_type;
	rsp->eng_grp_num = otx2_cpt_get_eng_grp(&cptpf->eng_grps,
						grp_req->eng_type);

	वापस 0;
पूर्ण

अटल पूर्णांक handle_msg_kvf_limits(काष्ठा otx2_cptpf_dev *cptpf,
				 काष्ठा otx2_cptvf_info *vf,
				 काष्ठा mbox_msghdr *req)
अणु
	काष्ठा otx2_cpt_kvf_limits_rsp *rsp;

	rsp = (काष्ठा otx2_cpt_kvf_limits_rsp *)
	      otx2_mbox_alloc_msg(&cptpf->vfpf_mbox, vf->vf_id, माप(*rsp));
	अगर (!rsp)
		वापस -ENOMEM;

	rsp->hdr.id = MBOX_MSG_GET_KVF_LIMITS;
	rsp->hdr.sig = OTX2_MBOX_RSP_SIG;
	rsp->hdr.pcअगरunc = req->pcअगरunc;
	rsp->kvf_limits = cptpf->kvf_limits;

	वापस 0;
पूर्ण

अटल पूर्णांक cptpf_handle_vf_req(काष्ठा otx2_cptpf_dev *cptpf,
			       काष्ठा otx2_cptvf_info *vf,
			       काष्ठा mbox_msghdr *req, पूर्णांक size)
अणु
	पूर्णांक err = 0;

	/* Check अगर msg is valid, अगर not reply with an invalid msg */
	अगर (req->sig != OTX2_MBOX_REQ_SIG)
		जाओ inval_msg;

	चयन (req->id) अणु
	हाल MBOX_MSG_GET_ENG_GRP_NUM:
		err = handle_msg_get_eng_grp_num(cptpf, vf, req);
		अवरोध;
	हाल MBOX_MSG_GET_CAPS:
		err = handle_msg_get_caps(cptpf, vf, req);
		अवरोध;
	हाल MBOX_MSG_GET_KVF_LIMITS:
		err = handle_msg_kvf_limits(cptpf, vf, req);
		अवरोध;
	शेष:
		err = क्रमward_to_af(cptpf, vf, req, size);
		अवरोध;
	पूर्ण
	वापस err;

inval_msg:
	otx2_reply_invalid_msg(&cptpf->vfpf_mbox, vf->vf_id, 0, req->id);
	otx2_mbox_msg_send(&cptpf->vfpf_mbox, vf->vf_id);
	वापस err;
पूर्ण

irqवापस_t otx2_cptpf_vfpf_mbox_पूर्णांकr(पूर्णांक __always_unused irq, व्योम *arg)
अणु
	काष्ठा otx2_cptpf_dev *cptpf = arg;
	काष्ठा otx2_cptvf_info *vf;
	पूर्णांक i, vf_idx;
	u64 पूर्णांकr;

	/*
	 * Check which VF has उठाओd an पूर्णांकerrupt and schedule
	 * corresponding work queue to process the messages
	 */
	क्रम (i = 0; i < 2; i++) अणु
		/* Read the पूर्णांकerrupt bits */
		पूर्णांकr = otx2_cpt_पढ़ो64(cptpf->reg_base, BLKADDR_RVUM, 0,
				       RVU_PF_VFPF_MBOX_INTX(i));

		क्रम (vf_idx = i * 64; vf_idx < cptpf->enabled_vfs; vf_idx++) अणु
			vf = &cptpf->vf[vf_idx];
			अगर (पूर्णांकr & (1ULL << vf->पूर्णांकr_idx)) अणु
				queue_work(cptpf->vfpf_mbox_wq,
					   &vf->vfpf_mbox_work);
				/* Clear the पूर्णांकerrupt */
				otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM,
						 0, RVU_PF_VFPF_MBOX_INTX(i),
						 BIT_ULL(vf->पूर्णांकr_idx));
			पूर्ण
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

व्योम otx2_cptpf_vfpf_mbox_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा otx2_cptpf_dev *cptpf;
	काष्ठा otx2_cptvf_info *vf;
	काष्ठा otx2_mbox_dev *mdev;
	काष्ठा mbox_hdr *req_hdr;
	काष्ठा mbox_msghdr *msg;
	काष्ठा otx2_mbox *mbox;
	पूर्णांक offset, i, err;

	vf = container_of(work, काष्ठा otx2_cptvf_info, vfpf_mbox_work);
	cptpf = vf->cptpf;
	mbox = &cptpf->vfpf_mbox;
	/* sync with mbox memory region */
	smp_rmb();
	mdev = &mbox->dev[vf->vf_id];
	/* Process received mbox messages */
	req_hdr = (काष्ठा mbox_hdr *)(mdev->mbase + mbox->rx_start);
	offset = mbox->rx_start + ALIGN(माप(*req_hdr), MBOX_MSG_ALIGN);

	क्रम (i = 0; i < req_hdr->num_msgs; i++) अणु
		msg = (काष्ठा mbox_msghdr *)(mdev->mbase + offset);

		/* Set which VF sent this message based on mbox IRQ */
		msg->pcअगरunc = ((u16)cptpf->pf_id << RVU_PFVF_PF_SHIFT) |
				((vf->vf_id + 1) & RVU_PFVF_FUNC_MASK);

		err = cptpf_handle_vf_req(cptpf, vf, msg,
					  msg->next_msgoff - offset);
		/*
		 * Behave as the AF, drop the msg अगर there is
		 * no memory, समयout handling also goes here
		 */
		अगर (err == -ENOMEM || err == -EIO)
			अवरोध;
		offset = msg->next_msgoff;
	पूर्ण
	/* Send mbox responses to VF */
	अगर (mdev->num_msgs)
		otx2_mbox_msg_send(mbox, vf->vf_id);
पूर्ण

irqवापस_t otx2_cptpf_afpf_mbox_पूर्णांकr(पूर्णांक __always_unused irq, व्योम *arg)
अणु
	काष्ठा otx2_cptpf_dev *cptpf = arg;
	u64 पूर्णांकr;

	/* Read the पूर्णांकerrupt bits */
	पूर्णांकr = otx2_cpt_पढ़ो64(cptpf->reg_base, BLKADDR_RVUM, 0, RVU_PF_INT);

	अगर (पूर्णांकr & 0x1ULL) अणु
		/* Schedule work queue function to process the MBOX request */
		queue_work(cptpf->afpf_mbox_wq, &cptpf->afpf_mbox_work);
		/* Clear and ack the पूर्णांकerrupt */
		otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0, RVU_PF_INT,
				 0x1ULL);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम process_afpf_mbox_msg(काष्ठा otx2_cptpf_dev *cptpf,
				  काष्ठा mbox_msghdr *msg)
अणु
	काष्ठा device *dev = &cptpf->pdev->dev;
	काष्ठा cpt_rd_wr_reg_msg *rsp_rd_wr;

	अगर (msg->id >= MBOX_MSG_MAX) अणु
		dev_err(dev, "MBOX msg with unknown ID %d\n", msg->id);
		वापस;
	पूर्ण
	अगर (msg->sig != OTX2_MBOX_RSP_SIG) अणु
		dev_err(dev, "MBOX msg with wrong signature %x, ID %d\n",
			msg->sig, msg->id);
		वापस;
	पूर्ण

	चयन (msg->id) अणु
	हाल MBOX_MSG_READY:
		cptpf->pf_id = (msg->pcअगरunc >> RVU_PFVF_PF_SHIFT) &
				RVU_PFVF_PF_MASK;
		अवरोध;
	हाल MBOX_MSG_CPT_RD_WR_REGISTER:
		rsp_rd_wr = (काष्ठा cpt_rd_wr_reg_msg *)msg;
		अगर (msg->rc) अणु
			dev_err(dev, "Reg %llx rd/wr(%d) failed %d\n",
				rsp_rd_wr->reg_offset, rsp_rd_wr->is_ग_लिखो,
				msg->rc);
			वापस;
		पूर्ण
		अगर (!rsp_rd_wr->is_ग_लिखो)
			*rsp_rd_wr->ret_val = rsp_rd_wr->val;
		अवरोध;
	हाल MBOX_MSG_ATTACH_RESOURCES:
		अगर (!msg->rc)
			cptpf->lfs.are_lfs_attached = 1;
		अवरोध;
	हाल MBOX_MSG_DETACH_RESOURCES:
		अगर (!msg->rc)
			cptpf->lfs.are_lfs_attached = 0;
		अवरोध;

	शेष:
		dev_err(dev,
			"Unsupported msg %d received.\n", msg->id);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम क्रमward_to_vf(काष्ठा otx2_cptpf_dev *cptpf, काष्ठा mbox_msghdr *msg,
			  पूर्णांक vf_id, पूर्णांक size)
अणु
	काष्ठा otx2_mbox *vfpf_mbox;
	काष्ठा mbox_msghdr *fwd;

	अगर (msg->id >= MBOX_MSG_MAX) अणु
		dev_err(&cptpf->pdev->dev,
			"MBOX msg with unknown ID %d\n", msg->id);
		वापस;
	पूर्ण
	अगर (msg->sig != OTX2_MBOX_RSP_SIG) अणु
		dev_err(&cptpf->pdev->dev,
			"MBOX msg with wrong signature %x, ID %d\n",
			msg->sig, msg->id);
		वापस;
	पूर्ण
	vfpf_mbox = &cptpf->vfpf_mbox;
	vf_id--;
	अगर (vf_id >= cptpf->enabled_vfs) अणु
		dev_err(&cptpf->pdev->dev,
			"MBOX msg to unknown VF: %d >= %d\n",
			vf_id, cptpf->enabled_vfs);
		वापस;
	पूर्ण
	अगर (msg->id == MBOX_MSG_VF_FLR)
		वापस;

	fwd = otx2_mbox_alloc_msg(vfpf_mbox, vf_id, size);
	अगर (!fwd) अणु
		dev_err(&cptpf->pdev->dev,
			"Forwarding to VF%d failed.\n", vf_id);
		वापस;
	पूर्ण
	स_नकल((uपूर्णांक8_t *)fwd + माप(काष्ठा mbox_msghdr),
		(uपूर्णांक8_t *)msg + माप(काष्ठा mbox_msghdr), size);
	fwd->id = msg->id;
	fwd->pcअगरunc = msg->pcअगरunc;
	fwd->sig = msg->sig;
	fwd->ver = msg->ver;
	fwd->rc = msg->rc;
पूर्ण

/* Handle mailbox messages received from AF */
व्योम otx2_cptpf_afpf_mbox_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा otx2_cptpf_dev *cptpf;
	काष्ठा otx2_mbox *afpf_mbox;
	काष्ठा otx2_mbox_dev *mdev;
	काष्ठा mbox_hdr *rsp_hdr;
	काष्ठा mbox_msghdr *msg;
	पूर्णांक offset, vf_id, i;

	cptpf = container_of(work, काष्ठा otx2_cptpf_dev, afpf_mbox_work);
	afpf_mbox = &cptpf->afpf_mbox;
	mdev = &afpf_mbox->dev[0];
	/* Sync mbox data पूर्णांकo memory */
	smp_wmb();

	rsp_hdr = (काष्ठा mbox_hdr *)(mdev->mbase + afpf_mbox->rx_start);
	offset = ALIGN(माप(*rsp_hdr), MBOX_MSG_ALIGN);

	क्रम (i = 0; i < rsp_hdr->num_msgs; i++) अणु
		msg = (काष्ठा mbox_msghdr *)(mdev->mbase + afpf_mbox->rx_start +
					     offset);
		vf_id = (msg->pcअगरunc >> RVU_PFVF_FUNC_SHIFT) &
			 RVU_PFVF_FUNC_MASK;
		अगर (vf_id > 0)
			क्रमward_to_vf(cptpf, msg, vf_id,
				      msg->next_msgoff - offset);
		अन्यथा
			process_afpf_mbox_msg(cptpf, msg);

		offset = msg->next_msgoff;
		mdev->msgs_acked++;
	पूर्ण
	otx2_mbox_reset(afpf_mbox, 0);
पूर्ण
