<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/workqueue.h>

#समावेश "nitrox_csr.h"
#समावेश "nitrox_hal.h"
#समावेश "nitrox_dev.h"
#समावेश "nitrox_mbx.h"

#घोषणा RING_TO_VFNO(_x, _y)	((_x) / (_y))

/**
 * mbx_msg_type - Mailbox message types
 */
क्रमागत mbx_msg_type अणु
	MBX_MSG_TYPE_NOP,
	MBX_MSG_TYPE_REQ,
	MBX_MSG_TYPE_ACK,
	MBX_MSG_TYPE_NACK,
पूर्ण;

/**
 * mbx_msg_opcode - Mailbox message opcodes
 */
क्रमागत mbx_msg_opcode अणु
	MSG_OP_VF_MODE = 1,
	MSG_OP_VF_UP,
	MSG_OP_VF_DOWN,
	MSG_OP_CHIPID_VFID,
	MSG_OP_MCODE_INFO = 11,
पूर्ण;

काष्ठा pf2vf_work अणु
	काष्ठा nitrox_vfdev *vfdev;
	काष्ठा nitrox_device *ndev;
	काष्ठा work_काष्ठा pf2vf_resp;
पूर्ण;

अटल अंतरभूत u64 pf2vf_पढ़ो_mbox(काष्ठा nitrox_device *ndev, पूर्णांक ring)
अणु
	u64 reg_addr;

	reg_addr = NPS_PKT_MBOX_VF_PF_PFDATAX(ring);
	वापस nitrox_पढ़ो_csr(ndev, reg_addr);
पूर्ण

अटल अंतरभूत व्योम pf2vf_ग_लिखो_mbox(काष्ठा nitrox_device *ndev, u64 value,
				    पूर्णांक ring)
अणु
	u64 reg_addr;

	reg_addr = NPS_PKT_MBOX_PF_VF_PFDATAX(ring);
	nitrox_ग_लिखो_csr(ndev, reg_addr, value);
पूर्ण

अटल व्योम pf2vf_send_response(काष्ठा nitrox_device *ndev,
				काष्ठा nitrox_vfdev *vfdev)
अणु
	जोड़ mbox_msg msg;

	msg.value = vfdev->msg.value;

	चयन (vfdev->msg.opcode) अणु
	हाल MSG_OP_VF_MODE:
		msg.data = ndev->mode;
		अवरोध;
	हाल MSG_OP_VF_UP:
		vfdev->nr_queues = vfdev->msg.data;
		atomic_set(&vfdev->state, __NDEV_READY);
		अवरोध;
	हाल MSG_OP_CHIPID_VFID:
		msg.id.chipid = ndev->idx;
		msg.id.vfid = vfdev->vfno;
		अवरोध;
	हाल MSG_OP_VF_DOWN:
		vfdev->nr_queues = 0;
		atomic_set(&vfdev->state, __NDEV_NOT_READY);
		अवरोध;
	हाल MSG_OP_MCODE_INFO:
		msg.data = 0;
		msg.mcode_info.count = 2;
		msg.mcode_info.info = MCODE_TYPE_SE_SSL | (MCODE_TYPE_AE << 5);
		msg.mcode_info.next_se_grp = 1;
		msg.mcode_info.next_ae_grp = 1;
		अवरोध;
	शेष:
		msg.type = MBX_MSG_TYPE_NOP;
		अवरोध;
	पूर्ण

	अगर (msg.type == MBX_MSG_TYPE_NOP)
		वापस;

	/* send ACK to VF */
	msg.type = MBX_MSG_TYPE_ACK;
	pf2vf_ग_लिखो_mbox(ndev, msg.value, vfdev->ring);

	vfdev->msg.value = 0;
	atomic64_inc(&vfdev->mbx_resp);
पूर्ण

अटल व्योम pf2vf_resp_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pf2vf_work *pf2vf_resp = container_of(work, काष्ठा pf2vf_work,
						     pf2vf_resp);
	काष्ठा nitrox_vfdev *vfdev = pf2vf_resp->vfdev;
	काष्ठा nitrox_device *ndev = pf2vf_resp->ndev;

	चयन (vfdev->msg.type) अणु
	हाल MBX_MSG_TYPE_REQ:
		/* process the request from VF */
		pf2vf_send_response(ndev, vfdev);
		अवरोध;
	हाल MBX_MSG_TYPE_ACK:
	हाल MBX_MSG_TYPE_NACK:
		अवरोध;
	पूर्ण

	kमुक्त(pf2vf_resp);
पूर्ण

व्योम nitrox_pf2vf_mbox_handler(काष्ठा nitrox_device *ndev)
अणु
	काष्ठा nitrox_vfdev *vfdev;
	काष्ठा pf2vf_work *pfwork;
	u64 value, reg_addr;
	u32 i;
	पूर्णांक vfno;

	/* loop क्रम VF(0..63) */
	reg_addr = NPS_PKT_MBOX_INT_LO;
	value = nitrox_पढ़ो_csr(ndev, reg_addr);
	क्रम_each_set_bit(i, (स्थिर अचिन्हित दीर्घ *)&value, BITS_PER_LONG) अणु
		/* get the vfno from ring */
		vfno = RING_TO_VFNO(i, ndev->iov.max_vf_queues);
		vfdev = ndev->iov.vfdev + vfno;
		vfdev->ring = i;
		/* fill the vf mailbox data */
		vfdev->msg.value = pf2vf_पढ़ो_mbox(ndev, vfdev->ring);
		pfwork = kzalloc(माप(*pfwork), GFP_ATOMIC);
		अगर (!pfwork)
			जारी;

		pfwork->vfdev = vfdev;
		pfwork->ndev = ndev;
		INIT_WORK(&pfwork->pf2vf_resp, pf2vf_resp_handler);
		queue_work(ndev->iov.pf2vf_wq, &pfwork->pf2vf_resp);
		/* clear the corresponding vf bit */
		nitrox_ग_लिखो_csr(ndev, reg_addr, BIT_ULL(i));
	पूर्ण

	/* loop क्रम VF(64..127) */
	reg_addr = NPS_PKT_MBOX_INT_HI;
	value = nitrox_पढ़ो_csr(ndev, reg_addr);
	क्रम_each_set_bit(i, (स्थिर अचिन्हित दीर्घ *)&value, BITS_PER_LONG) अणु
		/* get the vfno from ring */
		vfno = RING_TO_VFNO(i + 64, ndev->iov.max_vf_queues);
		vfdev = ndev->iov.vfdev + vfno;
		vfdev->ring = (i + 64);
		/* fill the vf mailbox data */
		vfdev->msg.value = pf2vf_पढ़ो_mbox(ndev, vfdev->ring);

		pfwork = kzalloc(माप(*pfwork), GFP_ATOMIC);
		अगर (!pfwork)
			जारी;

		pfwork->vfdev = vfdev;
		pfwork->ndev = ndev;
		INIT_WORK(&pfwork->pf2vf_resp, pf2vf_resp_handler);
		queue_work(ndev->iov.pf2vf_wq, &pfwork->pf2vf_resp);
		/* clear the corresponding vf bit */
		nitrox_ग_लिखो_csr(ndev, reg_addr, BIT_ULL(i));
	पूर्ण
पूर्ण

पूर्णांक nitrox_mbox_init(काष्ठा nitrox_device *ndev)
अणु
	काष्ठा nitrox_vfdev *vfdev;
	पूर्णांक i;

	ndev->iov.vfdev = kसुस्मृति(ndev->iov.num_vfs,
				  माप(काष्ठा nitrox_vfdev), GFP_KERNEL);
	अगर (!ndev->iov.vfdev)
		वापस -ENOMEM;

	क्रम (i = 0; i < ndev->iov.num_vfs; i++) अणु
		vfdev = ndev->iov.vfdev + i;
		vfdev->vfno = i;
	पूर्ण

	/* allocate pf2vf response workqueue */
	ndev->iov.pf2vf_wq = alloc_workqueue("nitrox_pf2vf", 0, 0);
	अगर (!ndev->iov.pf2vf_wq) अणु
		kमुक्त(ndev->iov.vfdev);
		वापस -ENOMEM;
	पूर्ण
	/* enable pf2vf mailbox पूर्णांकerrupts */
	enable_pf2vf_mbox_पूर्णांकerrupts(ndev);

	वापस 0;
पूर्ण

व्योम nitrox_mbox_cleanup(काष्ठा nitrox_device *ndev)
अणु
	/* disable pf2vf mailbox पूर्णांकerrupts */
	disable_pf2vf_mbox_पूर्णांकerrupts(ndev);
	/* destroy workqueue */
	अगर (ndev->iov.pf2vf_wq)
		destroy_workqueue(ndev->iov.pf2vf_wq);

	kमुक्त(ndev->iov.vfdev);
	ndev->iov.pf2vf_wq = शून्य;
	ndev->iov.vfdev = शून्य;
पूर्ण
