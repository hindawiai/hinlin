<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Cavium, Inc.
 */
#समावेश <linux/module.h>
#समावेश "cptpf.h"

अटल व्योम cpt_send_msg_to_vf(काष्ठा cpt_device *cpt, पूर्णांक vf,
			       काष्ठा cpt_mbox *mbx)
अणु
	/* Writing mbox(0) causes पूर्णांकerrupt */
	cpt_ग_लिखो_csr64(cpt->reg_base, CPTX_PF_VFX_MBOXX(0, vf, 1),
			mbx->data);
	cpt_ग_लिखो_csr64(cpt->reg_base, CPTX_PF_VFX_MBOXX(0, vf, 0), mbx->msg);
पूर्ण

/* ACKs VF's mailbox message
 * @vf: VF to which ACK to be sent
 */
अटल व्योम cpt_mbox_send_ack(काष्ठा cpt_device *cpt, पूर्णांक vf,
			      काष्ठा cpt_mbox *mbx)
अणु
	mbx->data = 0ull;
	mbx->msg = CPT_MBOX_MSG_TYPE_ACK;
	cpt_send_msg_to_vf(cpt, vf, mbx);
पूर्ण

अटल व्योम cpt_clear_mbox_पूर्णांकr(काष्ठा cpt_device *cpt, u32 vf)
अणु
	/* W1C क्रम the VF */
	cpt_ग_लिखो_csr64(cpt->reg_base, CPTX_PF_MBOX_INTX(0, 0), (1 << vf));
पूर्ण

/*
 *  Configure QLEN/Chunk sizes क्रम VF
 */
अटल व्योम cpt_cfg_qlen_क्रम_vf(काष्ठा cpt_device *cpt, पूर्णांक vf, u32 size)
अणु
	जोड़ cptx_pf_qx_ctl pf_qx_ctl;

	pf_qx_ctl.u = cpt_पढ़ो_csr64(cpt->reg_base, CPTX_PF_QX_CTL(0, vf));
	pf_qx_ctl.s.size = size;
	pf_qx_ctl.s.cont_err = true;
	cpt_ग_लिखो_csr64(cpt->reg_base, CPTX_PF_QX_CTL(0, vf), pf_qx_ctl.u);
पूर्ण

/*
 * Configure VQ priority
 */
अटल व्योम cpt_cfg_vq_priority(काष्ठा cpt_device *cpt, पूर्णांक vf, u32 pri)
अणु
	जोड़ cptx_pf_qx_ctl pf_qx_ctl;

	pf_qx_ctl.u = cpt_पढ़ो_csr64(cpt->reg_base, CPTX_PF_QX_CTL(0, vf));
	pf_qx_ctl.s.pri = pri;
	cpt_ग_लिखो_csr64(cpt->reg_base, CPTX_PF_QX_CTL(0, vf), pf_qx_ctl.u);
पूर्ण

अटल पूर्णांक cpt_bind_vq_to_grp(काष्ठा cpt_device *cpt, u8 q, u8 grp)
अणु
	काष्ठा microcode *mcode = cpt->mcode;
	जोड़ cptx_pf_qx_ctl pf_qx_ctl;
	काष्ठा device *dev = &cpt->pdev->dev;

	अगर (q >= CPT_MAX_VF_NUM) अणु
		dev_err(dev, "Queues are more than cores in the group");
		वापस -EINVAL;
	पूर्ण
	अगर (grp >= CPT_MAX_CORE_GROUPS) अणु
		dev_err(dev, "Request group is more than possible groups");
		वापस -EINVAL;
	पूर्ण
	अगर (grp >= cpt->next_mc_idx) अणु
		dev_err(dev, "Request group is higher than available functional groups");
		वापस -EINVAL;
	पूर्ण
	pf_qx_ctl.u = cpt_पढ़ो_csr64(cpt->reg_base, CPTX_PF_QX_CTL(0, q));
	pf_qx_ctl.s.grp = mcode[grp].group;
	cpt_ग_लिखो_csr64(cpt->reg_base, CPTX_PF_QX_CTL(0, q), pf_qx_ctl.u);
	dev_dbg(dev, "VF %d TYPE %s", q, (mcode[grp].is_ae ? "AE" : "SE"));

	वापस mcode[grp].is_ae ? AE_TYPES : SE_TYPES;
पूर्ण

/* Interrupt handler to handle mailbox messages from VFs */
अटल व्योम cpt_handle_mbox_पूर्णांकr(काष्ठा cpt_device *cpt, पूर्णांक vf)
अणु
	काष्ठा cpt_vf_info *vfx = &cpt->vfinfo[vf];
	काष्ठा cpt_mbox mbx = अणुपूर्ण;
	पूर्णांक vftype;
	काष्ठा device *dev = &cpt->pdev->dev;
	/*
	 * MBOX[0] contains msg
	 * MBOX[1] contains data
	 */
	mbx.msg  = cpt_पढ़ो_csr64(cpt->reg_base, CPTX_PF_VFX_MBOXX(0, vf, 0));
	mbx.data = cpt_पढ़ो_csr64(cpt->reg_base, CPTX_PF_VFX_MBOXX(0, vf, 1));
	dev_dbg(dev, "%s: Mailbox msg 0x%llx from VF%d", __func__, mbx.msg, vf);
	चयन (mbx.msg) अणु
	हाल CPT_MSG_VF_UP:
		vfx->state = VF_STATE_UP;
		try_module_get(THIS_MODULE);
		cpt_mbox_send_ack(cpt, vf, &mbx);
		अवरोध;
	हाल CPT_MSG_READY:
		mbx.msg  = CPT_MSG_READY;
		mbx.data = vf;
		cpt_send_msg_to_vf(cpt, vf, &mbx);
		अवरोध;
	हाल CPT_MSG_VF_DOWN:
		/* First msg in VF tearकरोwn sequence */
		vfx->state = VF_STATE_DOWN;
		module_put(THIS_MODULE);
		cpt_mbox_send_ack(cpt, vf, &mbx);
		अवरोध;
	हाल CPT_MSG_QLEN:
		vfx->qlen = mbx.data;
		cpt_cfg_qlen_क्रम_vf(cpt, vf, vfx->qlen);
		cpt_mbox_send_ack(cpt, vf, &mbx);
		अवरोध;
	हाल CPT_MSG_QBIND_GRP:
		vftype = cpt_bind_vq_to_grp(cpt, vf, (u8)mbx.data);
		अगर ((vftype != AE_TYPES) && (vftype != SE_TYPES))
			dev_err(dev, "Queue %d binding to group %llu failed",
				vf, mbx.data);
		अन्यथा अणु
			dev_dbg(dev, "Queue %d binding to group %llu successful",
				vf, mbx.data);
			mbx.msg = CPT_MSG_QBIND_GRP;
			mbx.data = vftype;
			cpt_send_msg_to_vf(cpt, vf, &mbx);
		पूर्ण
		अवरोध;
	हाल CPT_MSG_VQ_PRIORITY:
		vfx->priority = mbx.data;
		cpt_cfg_vq_priority(cpt, vf, vfx->priority);
		cpt_mbox_send_ack(cpt, vf, &mbx);
		अवरोध;
	शेष:
		dev_err(&cpt->pdev->dev, "Invalid msg from VF%d, msg 0x%llx\n",
			vf, mbx.msg);
		अवरोध;
	पूर्ण
पूर्ण

व्योम cpt_mbox_पूर्णांकr_handler (काष्ठा cpt_device *cpt, पूर्णांक mbx)
अणु
	u64 पूर्णांकr;
	u8  vf;

	पूर्णांकr = cpt_पढ़ो_csr64(cpt->reg_base, CPTX_PF_MBOX_INTX(0, 0));
	dev_dbg(&cpt->pdev->dev, "PF interrupt Mbox%d 0x%llx\n", mbx, पूर्णांकr);
	क्रम (vf = 0; vf < CPT_MAX_VF_NUM; vf++) अणु
		अगर (पूर्णांकr & (1ULL << vf)) अणु
			dev_dbg(&cpt->pdev->dev, "Intr from VF %d\n", vf);
			cpt_handle_mbox_पूर्णांकr(cpt, vf);
			cpt_clear_mbox_पूर्णांकr(cpt, vf);
		पूर्ण
	पूर्ण
पूर्ण
