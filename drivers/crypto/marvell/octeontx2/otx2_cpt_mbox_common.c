<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2020 Marvell. */

#समावेश "otx2_cpt_common.h"
#समावेश "otx2_cptlf.h"

पूर्णांक otx2_cpt_send_mbox_msg(काष्ठा otx2_mbox *mbox, काष्ठा pci_dev *pdev)
अणु
	पूर्णांक ret;

	otx2_mbox_msg_send(mbox, 0);
	ret = otx2_mbox_रुको_क्रम_rsp(mbox, 0);
	अगर (ret == -EIO) अणु
		dev_err(&pdev->dev, "RVU MBOX timeout.\n");
		वापस ret;
	पूर्ण अन्यथा अगर (ret) अणु
		dev_err(&pdev->dev, "RVU MBOX error: %d.\n", ret);
		वापस -EFAULT;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक otx2_cpt_send_पढ़ोy_msg(काष्ठा otx2_mbox *mbox, काष्ठा pci_dev *pdev)
अणु
	काष्ठा mbox_msghdr *req;

	req = otx2_mbox_alloc_msg_rsp(mbox, 0, माप(*req),
				      माप(काष्ठा पढ़ोy_msg_rsp));
	अगर (req == शून्य) अणु
		dev_err(&pdev->dev, "RVU MBOX failed to get message.\n");
		वापस -EFAULT;
	पूर्ण
	req->id = MBOX_MSG_READY;
	req->sig = OTX2_MBOX_REQ_SIG;
	req->pcअगरunc = 0;

	वापस otx2_cpt_send_mbox_msg(mbox, pdev);
पूर्ण

पूर्णांक otx2_cpt_send_af_reg_requests(काष्ठा otx2_mbox *mbox, काष्ठा pci_dev *pdev)
अणु
	वापस otx2_cpt_send_mbox_msg(mbox, pdev);
पूर्ण

पूर्णांक otx2_cpt_add_पढ़ो_af_reg(काष्ठा otx2_mbox *mbox, काष्ठा pci_dev *pdev,
			     u64 reg, u64 *val, पूर्णांक blkaddr)
अणु
	काष्ठा cpt_rd_wr_reg_msg *reg_msg;

	reg_msg = (काष्ठा cpt_rd_wr_reg_msg *)
			otx2_mbox_alloc_msg_rsp(mbox, 0, माप(*reg_msg),
						माप(*reg_msg));
	अगर (reg_msg == शून्य) अणु
		dev_err(&pdev->dev, "RVU MBOX failed to get message.\n");
		वापस -EFAULT;
	पूर्ण

	reg_msg->hdr.id = MBOX_MSG_CPT_RD_WR_REGISTER;
	reg_msg->hdr.sig = OTX2_MBOX_REQ_SIG;
	reg_msg->hdr.pcअगरunc = 0;

	reg_msg->is_ग_लिखो = 0;
	reg_msg->reg_offset = reg;
	reg_msg->ret_val = val;
	reg_msg->blkaddr = blkaddr;

	वापस 0;
पूर्ण

पूर्णांक otx2_cpt_add_ग_लिखो_af_reg(काष्ठा otx2_mbox *mbox, काष्ठा pci_dev *pdev,
			      u64 reg, u64 val, पूर्णांक blkaddr)
अणु
	काष्ठा cpt_rd_wr_reg_msg *reg_msg;

	reg_msg = (काष्ठा cpt_rd_wr_reg_msg *)
			otx2_mbox_alloc_msg_rsp(mbox, 0, माप(*reg_msg),
						माप(*reg_msg));
	अगर (reg_msg == शून्य) अणु
		dev_err(&pdev->dev, "RVU MBOX failed to get message.\n");
		वापस -EFAULT;
	पूर्ण

	reg_msg->hdr.id = MBOX_MSG_CPT_RD_WR_REGISTER;
	reg_msg->hdr.sig = OTX2_MBOX_REQ_SIG;
	reg_msg->hdr.pcअगरunc = 0;

	reg_msg->is_ग_लिखो = 1;
	reg_msg->reg_offset = reg;
	reg_msg->val = val;
	reg_msg->blkaddr = blkaddr;

	वापस 0;
पूर्ण

पूर्णांक otx2_cpt_पढ़ो_af_reg(काष्ठा otx2_mbox *mbox, काष्ठा pci_dev *pdev,
			 u64 reg, u64 *val, पूर्णांक blkaddr)
अणु
	पूर्णांक ret;

	ret = otx2_cpt_add_पढ़ो_af_reg(mbox, pdev, reg, val, blkaddr);
	अगर (ret)
		वापस ret;

	वापस otx2_cpt_send_mbox_msg(mbox, pdev);
पूर्ण

पूर्णांक otx2_cpt_ग_लिखो_af_reg(काष्ठा otx2_mbox *mbox, काष्ठा pci_dev *pdev,
			  u64 reg, u64 val, पूर्णांक blkaddr)
अणु
	पूर्णांक ret;

	ret = otx2_cpt_add_ग_लिखो_af_reg(mbox, pdev, reg, val, blkaddr);
	अगर (ret)
		वापस ret;

	वापस otx2_cpt_send_mbox_msg(mbox, pdev);
पूर्ण

पूर्णांक otx2_cpt_attach_rscrs_msg(काष्ठा otx2_cptlfs_info *lfs)
अणु
	काष्ठा otx2_mbox *mbox = lfs->mbox;
	काष्ठा rsrc_attach *req;
	पूर्णांक ret;

	req = (काष्ठा rsrc_attach *)
			otx2_mbox_alloc_msg_rsp(mbox, 0, माप(*req),
						माप(काष्ठा msg_rsp));
	अगर (req == शून्य) अणु
		dev_err(&lfs->pdev->dev, "RVU MBOX failed to get message.\n");
		वापस -EFAULT;
	पूर्ण

	req->hdr.id = MBOX_MSG_ATTACH_RESOURCES;
	req->hdr.sig = OTX2_MBOX_REQ_SIG;
	req->hdr.pcअगरunc = 0;
	req->cptlfs = lfs->lfs_num;
	ret = otx2_cpt_send_mbox_msg(mbox, lfs->pdev);
	अगर (ret)
		वापस ret;

	अगर (!lfs->are_lfs_attached)
		ret = -EINVAL;

	वापस ret;
पूर्ण

पूर्णांक otx2_cpt_detach_rsrcs_msg(काष्ठा otx2_cptlfs_info *lfs)
अणु
	काष्ठा otx2_mbox *mbox = lfs->mbox;
	काष्ठा rsrc_detach *req;
	पूर्णांक ret;

	req = (काष्ठा rsrc_detach *)
				otx2_mbox_alloc_msg_rsp(mbox, 0, माप(*req),
							माप(काष्ठा msg_rsp));
	अगर (req == शून्य) अणु
		dev_err(&lfs->pdev->dev, "RVU MBOX failed to get message.\n");
		वापस -EFAULT;
	पूर्ण

	req->hdr.id = MBOX_MSG_DETACH_RESOURCES;
	req->hdr.sig = OTX2_MBOX_REQ_SIG;
	req->hdr.pcअगरunc = 0;
	ret = otx2_cpt_send_mbox_msg(mbox, lfs->pdev);
	अगर (ret)
		वापस ret;

	अगर (lfs->are_lfs_attached)
		ret = -EINVAL;

	वापस ret;
पूर्ण

पूर्णांक otx2_cpt_msix_offset_msg(काष्ठा otx2_cptlfs_info *lfs)
अणु
	काष्ठा otx2_mbox *mbox = lfs->mbox;
	काष्ठा pci_dev *pdev = lfs->pdev;
	काष्ठा mbox_msghdr *req;
	पूर्णांक ret, i;

	req = otx2_mbox_alloc_msg_rsp(mbox, 0, माप(*req),
				      माप(काष्ठा msix_offset_rsp));
	अगर (req == शून्य) अणु
		dev_err(&pdev->dev, "RVU MBOX failed to get message.\n");
		वापस -EFAULT;
	पूर्ण

	req->id = MBOX_MSG_MSIX_OFFSET;
	req->sig = OTX2_MBOX_REQ_SIG;
	req->pcअगरunc = 0;
	ret = otx2_cpt_send_mbox_msg(mbox, pdev);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < lfs->lfs_num; i++) अणु
		अगर (lfs->lf[i].msix_offset == MSIX_VECTOR_INVALID) अणु
			dev_err(&pdev->dev,
				"Invalid msix offset %d for LF %d\n",
				lfs->lf[i].msix_offset, i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
