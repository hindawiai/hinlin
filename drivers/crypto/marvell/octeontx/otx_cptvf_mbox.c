<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell OcteonTX CPT driver
 *
 * Copyright (C) 2019 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#समावेश <linux/delay.h>
#समावेश "otx_cptvf.h"

#घोषणा CPT_MBOX_MSG_TIMEOUT 2000

अटल अक्षर *get_mbox_opcode_str(पूर्णांक msg_opcode)
अणु
	अक्षर *str = "Unknown";

	चयन (msg_opcode) अणु
	हाल OTX_CPT_MSG_VF_UP:
		str = "UP";
		अवरोध;

	हाल OTX_CPT_MSG_VF_DOWN:
		str = "DOWN";
		अवरोध;

	हाल OTX_CPT_MSG_READY:
		str = "READY";
		अवरोध;

	हाल OTX_CPT_MSG_QLEN:
		str = "QLEN";
		अवरोध;

	हाल OTX_CPT_MSG_QBIND_GRP:
		str = "QBIND_GRP";
		अवरोध;

	हाल OTX_CPT_MSG_VQ_PRIORITY:
		str = "VQ_PRIORITY";
		अवरोध;

	हाल OTX_CPT_MSG_PF_TYPE:
		str = "PF_TYPE";
		अवरोध;

	हाल OTX_CPT_MSG_ACK:
		str = "ACK";
		अवरोध;

	हाल OTX_CPT_MSG_NACK:
		str = "NACK";
		अवरोध;
	पूर्ण
	वापस str;
पूर्ण

अटल व्योम dump_mbox_msg(काष्ठा otx_cpt_mbox *mbox_msg, पूर्णांक vf_id)
अणु
	अक्षर raw_data_str[OTX_CPT_MAX_MBOX_DATA_STR_SIZE];

	hex_dump_to_buffer(mbox_msg, माप(काष्ठा otx_cpt_mbox), 16, 8,
			   raw_data_str, OTX_CPT_MAX_MBOX_DATA_STR_SIZE, false);
	अगर (vf_id >= 0)
		pr_debug("MBOX msg %s received from VF%d raw_data %s",
			 get_mbox_opcode_str(mbox_msg->msg), vf_id,
			 raw_data_str);
	अन्यथा
		pr_debug("MBOX msg %s received from PF raw_data %s",
			 get_mbox_opcode_str(mbox_msg->msg), raw_data_str);
पूर्ण

अटल व्योम cptvf_send_msg_to_pf(काष्ठा otx_cptvf *cptvf,
				     काष्ठा otx_cpt_mbox *mbx)
अणु
	/* Writing mbox(1) causes पूर्णांकerrupt */
	ग_लिखोq(mbx->msg, cptvf->reg_base + OTX_CPT_VFX_PF_MBOXX(0, 0));
	ग_लिखोq(mbx->data, cptvf->reg_base + OTX_CPT_VFX_PF_MBOXX(0, 1));
पूर्ण

/* Interrupt handler to handle mailbox messages from VFs */
व्योम otx_cptvf_handle_mbox_पूर्णांकr(काष्ठा otx_cptvf *cptvf)
अणु
	काष्ठा otx_cpt_mbox mbx = अणुपूर्ण;

	/*
	 * MBOX[0] contains msg
	 * MBOX[1] contains data
	 */
	mbx.msg  = पढ़ोq(cptvf->reg_base + OTX_CPT_VFX_PF_MBOXX(0, 0));
	mbx.data = पढ़ोq(cptvf->reg_base + OTX_CPT_VFX_PF_MBOXX(0, 1));

	dump_mbox_msg(&mbx, -1);

	चयन (mbx.msg) अणु
	हाल OTX_CPT_MSG_VF_UP:
		cptvf->pf_acked = true;
		cptvf->num_vfs = mbx.data;
		अवरोध;
	हाल OTX_CPT_MSG_READY:
		cptvf->pf_acked = true;
		cptvf->vfid = mbx.data;
		dev_dbg(&cptvf->pdev->dev, "Received VFID %d\n", cptvf->vfid);
		अवरोध;
	हाल OTX_CPT_MSG_QBIND_GRP:
		cptvf->pf_acked = true;
		cptvf->vftype = mbx.data;
		dev_dbg(&cptvf->pdev->dev, "VF %d type %s group %d\n",
			cptvf->vfid,
			((mbx.data == OTX_CPT_SE_TYPES) ? "SE" : "AE"),
			cptvf->vfgrp);
		अवरोध;
	हाल OTX_CPT_MSG_ACK:
		cptvf->pf_acked = true;
		अवरोध;
	हाल OTX_CPT_MSG_NACK:
		cptvf->pf_nacked = true;
		अवरोध;
	शेष:
		dev_err(&cptvf->pdev->dev, "Invalid msg from PF, msg 0x%llx\n",
			mbx.msg);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक cptvf_send_msg_to_pf_समयout(काष्ठा otx_cptvf *cptvf,
					काष्ठा otx_cpt_mbox *mbx)
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
			dev_err(&cptvf->pdev->dev,
				"PF didn't ack to mbox msg %llx from VF%u\n",
				mbx->msg, cptvf->vfid);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Checks अगर VF is able to comminicate with PF
 * and also माला_लो the CPT number this VF is associated to.
 */
पूर्णांक otx_cptvf_check_pf_पढ़ोy(काष्ठा otx_cptvf *cptvf)
अणु
	काष्ठा otx_cpt_mbox mbx = अणुपूर्ण;
	पूर्णांक ret;

	mbx.msg = OTX_CPT_MSG_READY;
	ret = cptvf_send_msg_to_pf_समयout(cptvf, &mbx);

	वापस ret;
पूर्ण

/*
 * Communicate VQs size to PF to program CPT(0)_PF_Q(0-15)_CTL of the VF.
 * Must be ACKed.
 */
पूर्णांक otx_cptvf_send_vq_size_msg(काष्ठा otx_cptvf *cptvf)
अणु
	काष्ठा otx_cpt_mbox mbx = अणुपूर्ण;
	पूर्णांक ret;

	mbx.msg = OTX_CPT_MSG_QLEN;
	mbx.data = cptvf->qsize;
	ret = cptvf_send_msg_to_pf_समयout(cptvf, &mbx);

	वापस ret;
पूर्ण

/*
 * Communicate VF group required to PF and get the VQ binded to that group
 */
पूर्णांक otx_cptvf_send_vf_to_grp_msg(काष्ठा otx_cptvf *cptvf, पूर्णांक group)
अणु
	काष्ठा otx_cpt_mbox mbx = अणुपूर्ण;
	पूर्णांक ret;

	mbx.msg = OTX_CPT_MSG_QBIND_GRP;
	/* Convey group of the VF */
	mbx.data = group;
	ret = cptvf_send_msg_to_pf_समयout(cptvf, &mbx);
	अगर (ret)
		वापस ret;
	cptvf->vfgrp = group;

	वापस 0;
पूर्ण

/*
 * Communicate VF group required to PF and get the VQ binded to that group
 */
पूर्णांक otx_cptvf_send_vf_priority_msg(काष्ठा otx_cptvf *cptvf)
अणु
	काष्ठा otx_cpt_mbox mbx = अणुपूर्ण;
	पूर्णांक ret;

	mbx.msg = OTX_CPT_MSG_VQ_PRIORITY;
	/* Convey group of the VF */
	mbx.data = cptvf->priority;
	ret = cptvf_send_msg_to_pf_समयout(cptvf, &mbx);

	वापस ret;
पूर्ण

/*
 * Communicate to PF that VF is UP and running
 */
पूर्णांक otx_cptvf_send_vf_up(काष्ठा otx_cptvf *cptvf)
अणु
	काष्ठा otx_cpt_mbox mbx = अणुपूर्ण;
	पूर्णांक ret;

	mbx.msg = OTX_CPT_MSG_VF_UP;
	ret = cptvf_send_msg_to_pf_समयout(cptvf, &mbx);

	वापस ret;
पूर्ण

/*
 * Communicate to PF that VF is DOWN and running
 */
पूर्णांक otx_cptvf_send_vf_करोwn(काष्ठा otx_cptvf *cptvf)
अणु
	काष्ठा otx_cpt_mbox mbx = अणुपूर्ण;
	पूर्णांक ret;

	mbx.msg = OTX_CPT_MSG_VF_DOWN;
	ret = cptvf_send_msg_to_pf_समयout(cptvf, &mbx);

	वापस ret;
पूर्ण
