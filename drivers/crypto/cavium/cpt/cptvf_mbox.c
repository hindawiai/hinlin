<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Cavium, Inc.
 */

#समावेश "cptvf.h"

अटल व्योम cptvf_send_msg_to_pf(काष्ठा cpt_vf *cptvf, काष्ठा cpt_mbox *mbx)
अणु
	/* Writing mbox(1) causes पूर्णांकerrupt */
	cpt_ग_लिखो_csr64(cptvf->reg_base, CPTX_VFX_PF_MBOXX(0, 0, 0),
			mbx->msg);
	cpt_ग_लिखो_csr64(cptvf->reg_base, CPTX_VFX_PF_MBOXX(0, 0, 1),
			mbx->data);
पूर्ण

/* Interrupt handler to handle mailbox messages from VFs */
व्योम cptvf_handle_mbox_पूर्णांकr(काष्ठा cpt_vf *cptvf)
अणु
	काष्ठा cpt_mbox mbx = अणुपूर्ण;

	/*
	 * MBOX[0] contains msg
	 * MBOX[1] contains data
	 */
	mbx.msg  = cpt_पढ़ो_csr64(cptvf->reg_base, CPTX_VFX_PF_MBOXX(0, 0, 0));
	mbx.data = cpt_पढ़ो_csr64(cptvf->reg_base, CPTX_VFX_PF_MBOXX(0, 0, 1));
	dev_dbg(&cptvf->pdev->dev, "%s: Mailbox msg 0x%llx from PF\n",
		__func__, mbx.msg);
	चयन (mbx.msg) अणु
	हाल CPT_MSG_READY:
	अणु
		cptvf->pf_acked = true;
		cptvf->vfid = mbx.data;
		dev_dbg(&cptvf->pdev->dev, "Received VFID %d\n", cptvf->vfid);
		अवरोध;
	पूर्ण
	हाल CPT_MSG_QBIND_GRP:
		cptvf->pf_acked = true;
		cptvf->vftype = mbx.data;
		dev_dbg(&cptvf->pdev->dev, "VF %d type %s group %d\n",
			cptvf->vfid, ((mbx.data == SE_TYPES) ? "SE" : "AE"),
			cptvf->vfgrp);
		अवरोध;
	हाल CPT_MBOX_MSG_TYPE_ACK:
		cptvf->pf_acked = true;
		अवरोध;
	हाल CPT_MBOX_MSG_TYPE_NACK:
		cptvf->pf_nacked = true;
		अवरोध;
	शेष:
		dev_err(&cptvf->pdev->dev, "Invalid msg from PF, msg 0x%llx\n",
			mbx.msg);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक cptvf_send_msg_to_pf_समयout(काष्ठा cpt_vf *cptvf,
					काष्ठा cpt_mbox *mbx)
अणु
	पूर्णांक समयout = CPT_MBOX_MSG_TIMEOUT;
	पूर्णांक sleep = 10;

	cptvf->pf_acked = false;
	cptvf->pf_nacked = false;
	cptvf_send_msg_to_pf(cptvf, mbx);
	/* Wait क्रम previous message to be acked, समयout 2sec */
	जबतक (!cptvf->pf_acked) अणु
		अगर (cptvf->pf_nacked)
			वापस -EINVAL;
		msleep(sleep);
		अगर (cptvf->pf_acked)
			अवरोध;
		समयout -= sleep;
		अगर (!समयout) अणु
			dev_err(&cptvf->pdev->dev, "PF didn't ack to mbox msg %llx from VF%u\n",
				(mbx->msg & 0xFF), cptvf->vfid);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Checks अगर VF is able to comminicate with PF
 * and also माला_लो the CPT number this VF is associated to.
 */
पूर्णांक cptvf_check_pf_पढ़ोy(काष्ठा cpt_vf *cptvf)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;
	काष्ठा cpt_mbox mbx = अणुपूर्ण;

	mbx.msg = CPT_MSG_READY;
	अगर (cptvf_send_msg_to_pf_समयout(cptvf, &mbx)) अणु
		dev_err(&pdev->dev, "PF didn't respond to READY msg\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Communicate VQs size to PF to program CPT(0)_PF_Q(0-15)_CTL of the VF.
 * Must be ACKed.
 */
पूर्णांक cptvf_send_vq_size_msg(काष्ठा cpt_vf *cptvf)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;
	काष्ठा cpt_mbox mbx = अणुपूर्ण;

	mbx.msg = CPT_MSG_QLEN;
	mbx.data = cptvf->qsize;
	अगर (cptvf_send_msg_to_pf_समयout(cptvf, &mbx)) अणु
		dev_err(&pdev->dev, "PF didn't respond to vq_size msg\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Communicate VF group required to PF and get the VQ binded to that group
 */
पूर्णांक cptvf_send_vf_to_grp_msg(काष्ठा cpt_vf *cptvf)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;
	काष्ठा cpt_mbox mbx = अणुपूर्ण;

	mbx.msg = CPT_MSG_QBIND_GRP;
	/* Convey group of the VF */
	mbx.data = cptvf->vfgrp;
	अगर (cptvf_send_msg_to_pf_समयout(cptvf, &mbx)) अणु
		dev_err(&pdev->dev, "PF didn't respond to vf_type msg\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Communicate VF group required to PF and get the VQ binded to that group
 */
पूर्णांक cptvf_send_vf_priority_msg(काष्ठा cpt_vf *cptvf)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;
	काष्ठा cpt_mbox mbx = अणुपूर्ण;

	mbx.msg = CPT_MSG_VQ_PRIORITY;
	/* Convey group of the VF */
	mbx.data = cptvf->priority;
	अगर (cptvf_send_msg_to_pf_समयout(cptvf, &mbx)) अणु
		dev_err(&pdev->dev, "PF didn't respond to vf_type msg\n");
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Communicate to PF that VF is UP and running
 */
पूर्णांक cptvf_send_vf_up(काष्ठा cpt_vf *cptvf)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;
	काष्ठा cpt_mbox mbx = अणुपूर्ण;

	mbx.msg = CPT_MSG_VF_UP;
	अगर (cptvf_send_msg_to_pf_समयout(cptvf, &mbx)) अणु
		dev_err(&pdev->dev, "PF didn't respond to UP msg\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Communicate to PF that VF is DOWN and running
 */
पूर्णांक cptvf_send_vf_करोwn(काष्ठा cpt_vf *cptvf)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;
	काष्ठा cpt_mbox mbx = अणुपूर्ण;

	mbx.msg = CPT_MSG_VF_DOWN;
	अगर (cptvf_send_msg_to_pf_समयout(cptvf, &mbx)) अणु
		dev_err(&pdev->dev, "PF didn't respond to DOWN msg\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण
