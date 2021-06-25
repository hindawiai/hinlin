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

#समावेश "otx_cpt_common.h"
#समावेश "otx_cptpf.h"

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
		pr_debug("MBOX opcode %s received from VF%d raw_data %s\n",
			 get_mbox_opcode_str(mbox_msg->msg), vf_id,
			 raw_data_str);
	अन्यथा
		pr_debug("MBOX opcode %s received from PF raw_data %s\n",
			 get_mbox_opcode_str(mbox_msg->msg), raw_data_str);
पूर्ण

अटल व्योम otx_cpt_send_msg_to_vf(काष्ठा otx_cpt_device *cpt, पूर्णांक vf,
				   काष्ठा otx_cpt_mbox *mbx)
अणु
	/* Writing mbox(0) causes पूर्णांकerrupt */
	ग_लिखोq(mbx->data, cpt->reg_base + OTX_CPT_PF_VFX_MBOXX(vf, 1));
	ग_लिखोq(mbx->msg, cpt->reg_base + OTX_CPT_PF_VFX_MBOXX(vf, 0));
पूर्ण

/*
 * ACKs VF's mailbox message
 * @vf: VF to which ACK to be sent
 */
अटल व्योम otx_cpt_mbox_send_ack(काष्ठा otx_cpt_device *cpt, पूर्णांक vf,
			      काष्ठा otx_cpt_mbox *mbx)
अणु
	mbx->data = 0ull;
	mbx->msg = OTX_CPT_MSG_ACK;
	otx_cpt_send_msg_to_vf(cpt, vf, mbx);
पूर्ण

/* NACKs VF's mailbox message that PF is not able to complete the action */
अटल व्योम otx_cptpf_mbox_send_nack(काष्ठा otx_cpt_device *cpt, पूर्णांक vf,
				     काष्ठा otx_cpt_mbox *mbx)
अणु
	mbx->data = 0ull;
	mbx->msg = OTX_CPT_MSG_NACK;
	otx_cpt_send_msg_to_vf(cpt, vf, mbx);
पूर्ण

अटल व्योम otx_cpt_clear_mbox_पूर्णांकr(काष्ठा otx_cpt_device *cpt, u32 vf)
अणु
	/* W1C क्रम the VF */
	ग_लिखोq(1ull << vf, cpt->reg_base + OTX_CPT_PF_MBOX_INTX(0));
पूर्ण

/*
 * Configure QLEN/Chunk sizes क्रम VF
 */
अटल व्योम otx_cpt_cfg_qlen_क्रम_vf(काष्ठा otx_cpt_device *cpt, पूर्णांक vf,
				    u32 size)
अणु
	जोड़ otx_cptx_pf_qx_ctl pf_qx_ctl;

	pf_qx_ctl.u = पढ़ोq(cpt->reg_base + OTX_CPT_PF_QX_CTL(vf));
	pf_qx_ctl.s.size = size;
	pf_qx_ctl.s.cont_err = true;
	ग_लिखोq(pf_qx_ctl.u, cpt->reg_base + OTX_CPT_PF_QX_CTL(vf));
पूर्ण

/*
 * Configure VQ priority
 */
अटल व्योम otx_cpt_cfg_vq_priority(काष्ठा otx_cpt_device *cpt, पूर्णांक vf, u32 pri)
अणु
	जोड़ otx_cptx_pf_qx_ctl pf_qx_ctl;

	pf_qx_ctl.u = पढ़ोq(cpt->reg_base + OTX_CPT_PF_QX_CTL(vf));
	pf_qx_ctl.s.pri = pri;
	ग_लिखोq(pf_qx_ctl.u, cpt->reg_base + OTX_CPT_PF_QX_CTL(vf));
पूर्ण

अटल पूर्णांक otx_cpt_bind_vq_to_grp(काष्ठा otx_cpt_device *cpt, u8 q, u8 grp)
अणु
	काष्ठा device *dev = &cpt->pdev->dev;
	काष्ठा otx_cpt_eng_grp_info *eng_grp;
	जोड़ otx_cptx_pf_qx_ctl pf_qx_ctl;
	काष्ठा otx_cpt_ucode *ucode;

	अगर (q >= cpt->max_vfs) अणु
		dev_err(dev, "Requested queue %d is > than maximum avail %d\n",
			q, cpt->max_vfs);
		वापस -EINVAL;
	पूर्ण

	अगर (grp >= OTX_CPT_MAX_ENGINE_GROUPS) अणु
		dev_err(dev, "Requested group %d is > than maximum avail %d\n",
			grp, OTX_CPT_MAX_ENGINE_GROUPS);
		वापस -EINVAL;
	पूर्ण

	eng_grp = &cpt->eng_grps.grp[grp];
	अगर (!eng_grp->is_enabled) अणु
		dev_err(dev, "Requested engine group %d is disabled\n", grp);
		वापस -EINVAL;
	पूर्ण

	pf_qx_ctl.u = पढ़ोq(cpt->reg_base + OTX_CPT_PF_QX_CTL(q));
	pf_qx_ctl.s.grp = grp;
	ग_लिखोq(pf_qx_ctl.u, cpt->reg_base + OTX_CPT_PF_QX_CTL(q));

	अगर (eng_grp->mirror.is_ena)
		ucode = &eng_grp->g->grp[eng_grp->mirror.idx].ucode[0];
	अन्यथा
		ucode = &eng_grp->ucode[0];

	अगर (otx_cpt_uc_supports_eng_type(ucode, OTX_CPT_SE_TYPES))
		वापस OTX_CPT_SE_TYPES;
	अन्यथा अगर (otx_cpt_uc_supports_eng_type(ucode, OTX_CPT_AE_TYPES))
		वापस OTX_CPT_AE_TYPES;
	अन्यथा
		वापस BAD_OTX_CPTVF_TYPE;
पूर्ण

/* Interrupt handler to handle mailbox messages from VFs */
अटल व्योम otx_cpt_handle_mbox_पूर्णांकr(काष्ठा otx_cpt_device *cpt, पूर्णांक vf)
अणु
	पूर्णांक vftype = 0;
	काष्ठा otx_cpt_mbox mbx = अणुपूर्ण;
	काष्ठा device *dev = &cpt->pdev->dev;
	/*
	 * MBOX[0] contains msg
	 * MBOX[1] contains data
	 */
	mbx.msg  = पढ़ोq(cpt->reg_base + OTX_CPT_PF_VFX_MBOXX(vf, 0));
	mbx.data = पढ़ोq(cpt->reg_base + OTX_CPT_PF_VFX_MBOXX(vf, 1));

	dump_mbox_msg(&mbx, vf);

	चयन (mbx.msg) अणु
	हाल OTX_CPT_MSG_VF_UP:
		mbx.msg  = OTX_CPT_MSG_VF_UP;
		mbx.data = cpt->vfs_enabled;
		otx_cpt_send_msg_to_vf(cpt, vf, &mbx);
		अवरोध;
	हाल OTX_CPT_MSG_READY:
		mbx.msg  = OTX_CPT_MSG_READY;
		mbx.data = vf;
		otx_cpt_send_msg_to_vf(cpt, vf, &mbx);
		अवरोध;
	हाल OTX_CPT_MSG_VF_DOWN:
		/* First msg in VF tearकरोwn sequence */
		otx_cpt_mbox_send_ack(cpt, vf, &mbx);
		अवरोध;
	हाल OTX_CPT_MSG_QLEN:
		otx_cpt_cfg_qlen_क्रम_vf(cpt, vf, mbx.data);
		otx_cpt_mbox_send_ack(cpt, vf, &mbx);
		अवरोध;
	हाल OTX_CPT_MSG_QBIND_GRP:
		vftype = otx_cpt_bind_vq_to_grp(cpt, vf, (u8)mbx.data);
		अगर ((vftype != OTX_CPT_AE_TYPES) &&
		    (vftype != OTX_CPT_SE_TYPES)) अणु
			dev_err(dev, "VF%d binding to eng group %llu failed\n",
				vf, mbx.data);
			otx_cptpf_mbox_send_nack(cpt, vf, &mbx);
		पूर्ण अन्यथा अणु
			mbx.msg = OTX_CPT_MSG_QBIND_GRP;
			mbx.data = vftype;
			otx_cpt_send_msg_to_vf(cpt, vf, &mbx);
		पूर्ण
		अवरोध;
	हाल OTX_CPT_MSG_PF_TYPE:
		mbx.msg = OTX_CPT_MSG_PF_TYPE;
		mbx.data = cpt->pf_type;
		otx_cpt_send_msg_to_vf(cpt, vf, &mbx);
		अवरोध;
	हाल OTX_CPT_MSG_VQ_PRIORITY:
		otx_cpt_cfg_vq_priority(cpt, vf, mbx.data);
		otx_cpt_mbox_send_ack(cpt, vf, &mbx);
		अवरोध;
	शेष:
		dev_err(&cpt->pdev->dev, "Invalid msg from VF%d, msg 0x%llx\n",
			vf, mbx.msg);
		अवरोध;
	पूर्ण
पूर्ण

व्योम otx_cpt_mbox_पूर्णांकr_handler (काष्ठा otx_cpt_device *cpt, पूर्णांक mbx)
अणु
	u64 पूर्णांकr;
	u8  vf;

	पूर्णांकr = पढ़ोq(cpt->reg_base + OTX_CPT_PF_MBOX_INTX(0));
	pr_debug("PF interrupt mbox%d mask 0x%llx\n", mbx, पूर्णांकr);
	क्रम (vf = 0; vf < cpt->max_vfs; vf++) अणु
		अगर (पूर्णांकr & (1ULL << vf)) अणु
			otx_cpt_handle_mbox_पूर्णांकr(cpt, vf);
			otx_cpt_clear_mbox_पूर्णांकr(cpt, vf);
		पूर्ण
	पूर्ण
पूर्ण
