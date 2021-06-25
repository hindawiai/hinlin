<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2019 Intel Corporation. All rights rsvd. */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <uapi/linux/idxd.h>
#समावेश "idxd.h"
#समावेश "registers.h"

अटल काष्ठा idxd_desc *__get_desc(काष्ठा idxd_wq *wq, पूर्णांक idx, पूर्णांक cpu)
अणु
	काष्ठा idxd_desc *desc;
	काष्ठा idxd_device *idxd = wq->idxd;

	desc = wq->descs[idx];
	स_रखो(desc->hw, 0, माप(काष्ठा dsa_hw_desc));
	स_रखो(desc->completion, 0, idxd->data->compl_size);
	desc->cpu = cpu;

	अगर (device_pasid_enabled(idxd))
		desc->hw->pasid = idxd->pasid;

	/*
	 * Descriptor completion vectors are 1...N क्रम MSIX. We will round
	 * robin through the N vectors.
	 */
	wq->vec_ptr = (wq->vec_ptr % idxd->num_wq_irqs) + 1;
	अगर (!idxd->पूर्णांक_handles) अणु
		desc->hw->पूर्णांक_handle = wq->vec_ptr;
	पूर्ण अन्यथा अणु
		desc->vector = wq->vec_ptr;
		/*
		 * पूर्णांक_handles are only क्रम descriptor completion. However क्रम device
		 * MSIX क्रमागतeration, vec 0 is used क्रम misc पूर्णांकerrupts. Thereक्रमe even
		 * though we are rotating through 1...N क्रम descriptor पूर्णांकerrupts, we
		 * need to acqurie the पूर्णांक_handles from 0..N-1.
		 */
		desc->hw->पूर्णांक_handle = idxd->पूर्णांक_handles[desc->vector - 1];
	पूर्ण

	वापस desc;
पूर्ण

काष्ठा idxd_desc *idxd_alloc_desc(काष्ठा idxd_wq *wq, क्रमागत idxd_op_type optype)
अणु
	पूर्णांक cpu, idx;
	काष्ठा idxd_device *idxd = wq->idxd;
	DEFINE_SBQ_WAIT(रुको);
	काष्ठा sbq_रुको_state *ws;
	काष्ठा sbiपंचांगap_queue *sbq;

	अगर (idxd->state != IDXD_DEV_ENABLED)
		वापस ERR_PTR(-EIO);

	sbq = &wq->sbq;
	idx = sbiपंचांगap_queue_get(sbq, &cpu);
	अगर (idx < 0) अणु
		अगर (optype == IDXD_OP_NONBLOCK)
			वापस ERR_PTR(-EAGAIN);
	पूर्ण अन्यथा अणु
		वापस __get_desc(wq, idx, cpu);
	पूर्ण

	ws = &sbq->ws[0];
	क्रम (;;) अणु
		sbiपंचांगap_prepare_to_रुको(sbq, ws, &रुको, TASK_INTERRUPTIBLE);
		अगर (संकेत_pending_state(TASK_INTERRUPTIBLE, current))
			अवरोध;
		idx = sbiपंचांगap_queue_get(sbq, &cpu);
		अगर (idx > 0)
			अवरोध;
		schedule();
	पूर्ण

	sbiपंचांगap_finish_रुको(sbq, ws, &रुको);
	अगर (idx < 0)
		वापस ERR_PTR(-EAGAIN);

	वापस __get_desc(wq, idx, cpu);
पूर्ण

व्योम idxd_मुक्त_desc(काष्ठा idxd_wq *wq, काष्ठा idxd_desc *desc)
अणु
	पूर्णांक cpu = desc->cpu;

	desc->cpu = -1;
	sbiपंचांगap_queue_clear(&wq->sbq, desc->id, cpu);
पूर्ण

पूर्णांक idxd_submit_desc(काष्ठा idxd_wq *wq, काष्ठा idxd_desc *desc)
अणु
	काष्ठा idxd_device *idxd = wq->idxd;
	व्योम __iomem *portal;
	पूर्णांक rc;

	अगर (idxd->state != IDXD_DEV_ENABLED)
		वापस -EIO;

	अगर (!percpu_ref_tryget_live(&wq->wq_active))
		वापस -ENXIO;

	portal = wq->portal;

	/*
	 * The wmb() flushes ग_लिखोs to coherent DMA data beक्रमe
	 * possibly triggering a DMA पढ़ो. The wmb() is necessary
	 * even on UP because the recipient is a device.
	 */
	wmb();
	अगर (wq_dedicated(wq)) अणु
		iosubmit_cmds512(portal, desc->hw, 1);
	पूर्ण अन्यथा अणु
		/*
		 * It's not likely that we would receive queue full rejection
		 * since the descriptor allocation gates at wq size. If we
		 * receive a -EAGAIN, that means something went wrong such as the
		 * device is not accepting descriptor at all.
		 */
		rc = enqcmds(portal, desc->hw);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	percpu_ref_put(&wq->wq_active);

	/*
	 * Pending the descriptor to the lockless list क्रम the irq_entry
	 * that we designated the descriptor to.
	 */
	अगर (desc->hw->flags & IDXD_OP_FLAG_RCI) अणु
		पूर्णांक vec;

		/*
		 * If the driver is on host kernel, it would be the value
		 * asचिन्हित to पूर्णांकerrupt handle, which is index क्रम MSIX
		 * vector. If it's guest then can't use the पूर्णांक_handle since
		 * that is the index to IMS क्रम the entire device. The guest
		 * device local index will be used.
		 */
		vec = !idxd->पूर्णांक_handles ? desc->hw->पूर्णांक_handle : desc->vector;
		llist_add(&desc->llnode, &idxd->irq_entries[vec].pending_llist);
	पूर्ण

	वापस 0;
पूर्ण
