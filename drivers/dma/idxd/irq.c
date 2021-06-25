<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2019 Intel Corporation. All rights rsvd. */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/dmaengine.h>
#समावेश <uapi/linux/idxd.h>
#समावेश "../dmaengine.h"
#समावेश "idxd.h"
#समावेश "registers.h"

क्रमागत irq_work_type अणु
	IRQ_WORK_NORMAL = 0,
	IRQ_WORK_PROCESS_FAULT,
पूर्ण;

काष्ठा idxd_fault अणु
	काष्ठा work_काष्ठा work;
	u64 addr;
	काष्ठा idxd_device *idxd;
पूर्ण;

अटल पूर्णांक irq_process_work_list(काष्ठा idxd_irq_entry *irq_entry,
				 क्रमागत irq_work_type wtype,
				 पूर्णांक *processed, u64 data);
अटल पूर्णांक irq_process_pending_llist(काष्ठा idxd_irq_entry *irq_entry,
				     क्रमागत irq_work_type wtype,
				     पूर्णांक *processed, u64 data);

अटल व्योम idxd_device_reinit(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा idxd_device *idxd = container_of(work, काष्ठा idxd_device, work);
	काष्ठा device *dev = &idxd->pdev->dev;
	पूर्णांक rc, i;

	idxd_device_reset(idxd);
	rc = idxd_device_config(idxd);
	अगर (rc < 0)
		जाओ out;

	rc = idxd_device_enable(idxd);
	अगर (rc < 0)
		जाओ out;

	क्रम (i = 0; i < idxd->max_wqs; i++) अणु
		काष्ठा idxd_wq *wq = idxd->wqs[i];

		अगर (wq->state == IDXD_WQ_ENABLED) अणु
			rc = idxd_wq_enable(wq);
			अगर (rc < 0) अणु
				dev_warn(dev, "Unable to re-enable wq %s\n",
					 dev_name(&wq->conf_dev));
			पूर्ण
		पूर्ण
	पूर्ण

	वापस;

 out:
	idxd_device_wqs_clear_state(idxd);
पूर्ण

अटल व्योम idxd_device_fault_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा idxd_fault *fault = container_of(work, काष्ठा idxd_fault, work);
	काष्ठा idxd_irq_entry *ie;
	पूर्णांक i;
	पूर्णांक processed;
	पूर्णांक irqcnt = fault->idxd->num_wq_irqs + 1;

	क्रम (i = 1; i < irqcnt; i++) अणु
		ie = &fault->idxd->irq_entries[i];
		irq_process_work_list(ie, IRQ_WORK_PROCESS_FAULT,
				      &processed, fault->addr);
		अगर (processed)
			अवरोध;

		irq_process_pending_llist(ie, IRQ_WORK_PROCESS_FAULT,
					  &processed, fault->addr);
		अगर (processed)
			अवरोध;
	पूर्ण

	kमुक्त(fault);
पूर्ण

अटल पूर्णांक idxd_device_schedule_fault_process(काष्ठा idxd_device *idxd,
					      u64 fault_addr)
अणु
	काष्ठा idxd_fault *fault;

	fault = kदो_स्मृति(माप(*fault), GFP_ATOMIC);
	अगर (!fault)
		वापस -ENOMEM;

	fault->addr = fault_addr;
	fault->idxd = idxd;
	INIT_WORK(&fault->work, idxd_device_fault_work);
	queue_work(idxd->wq, &fault->work);
	वापस 0;
पूर्ण

अटल पूर्णांक process_misc_पूर्णांकerrupts(काष्ठा idxd_device *idxd, u32 cause)
अणु
	काष्ठा device *dev = &idxd->pdev->dev;
	जोड़ gensts_reg gensts;
	u32 val = 0;
	पूर्णांक i;
	bool err = false;

	अगर (cause & IDXD_INTC_ERR) अणु
		spin_lock_bh(&idxd->dev_lock);
		क्रम (i = 0; i < 4; i++)
			idxd->sw_err.bits[i] = ioपढ़ो64(idxd->reg_base +
					IDXD_SWERR_OFFSET + i * माप(u64));

		ioग_लिखो64(idxd->sw_err.bits[0] & IDXD_SWERR_ACK,
			  idxd->reg_base + IDXD_SWERR_OFFSET);

		अगर (idxd->sw_err.valid && idxd->sw_err.wq_idx_valid) अणु
			पूर्णांक id = idxd->sw_err.wq_idx;
			काष्ठा idxd_wq *wq = idxd->wqs[id];

			अगर (wq->type == IDXD_WQT_USER)
				wake_up_पूर्णांकerruptible(&wq->err_queue);
		पूर्ण अन्यथा अणु
			पूर्णांक i;

			क्रम (i = 0; i < idxd->max_wqs; i++) अणु
				काष्ठा idxd_wq *wq = idxd->wqs[i];

				अगर (wq->type == IDXD_WQT_USER)
					wake_up_पूर्णांकerruptible(&wq->err_queue);
			पूर्ण
		पूर्ण

		spin_unlock_bh(&idxd->dev_lock);
		val |= IDXD_INTC_ERR;

		क्रम (i = 0; i < 4; i++)
			dev_warn(dev, "err[%d]: %#16.16llx\n",
				 i, idxd->sw_err.bits[i]);
		err = true;
	पूर्ण

	अगर (cause & IDXD_INTC_CMD) अणु
		val |= IDXD_INTC_CMD;
		complete(idxd->cmd_करोne);
	पूर्ण

	अगर (cause & IDXD_INTC_OCCUPY) अणु
		/* Driver करोes not utilize occupancy पूर्णांकerrupt */
		val |= IDXD_INTC_OCCUPY;
	पूर्ण

	अगर (cause & IDXD_INTC_PERFMON_OVFL) अणु
		val |= IDXD_INTC_PERFMON_OVFL;
		perfmon_counter_overflow(idxd);
	पूर्ण

	val ^= cause;
	अगर (val)
		dev_warn_once(dev, "Unexpected interrupt cause bits set: %#x\n",
			      val);

	अगर (!err)
		वापस 0;

	/*
	 * This हाल should rarely happen and typically is due to software
	 * programming error by the driver.
	 */
	अगर (idxd->sw_err.valid &&
	    idxd->sw_err.desc_valid &&
	    idxd->sw_err.fault_addr)
		idxd_device_schedule_fault_process(idxd, idxd->sw_err.fault_addr);

	gensts.bits = ioपढ़ो32(idxd->reg_base + IDXD_GENSTATS_OFFSET);
	अगर (gensts.state == IDXD_DEVICE_STATE_HALT) अणु
		idxd->state = IDXD_DEV_HALTED;
		अगर (gensts.reset_type == IDXD_DEVICE_RESET_SOFTWARE) अणु
			/*
			 * If we need a software reset, we will throw the work
			 * on a प्रणाली workqueue in order to allow पूर्णांकerrupts
			 * क्रम the device command completions.
			 */
			INIT_WORK(&idxd->work, idxd_device_reinit);
			queue_work(idxd->wq, &idxd->work);
		पूर्ण अन्यथा अणु
			spin_lock_bh(&idxd->dev_lock);
			idxd_wqs_quiesce(idxd);
			idxd_wqs_unmap_portal(idxd);
			idxd_device_wqs_clear_state(idxd);
			dev_err(&idxd->pdev->dev,
				"idxd halted, need %s.\n",
				gensts.reset_type == IDXD_DEVICE_RESET_FLR ?
				"FLR" : "system reset");
			spin_unlock_bh(&idxd->dev_lock);
			वापस -ENXIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

irqवापस_t idxd_misc_thपढ़ो(पूर्णांक vec, व्योम *data)
अणु
	काष्ठा idxd_irq_entry *irq_entry = data;
	काष्ठा idxd_device *idxd = irq_entry->idxd;
	पूर्णांक rc;
	u32 cause;

	cause = ioपढ़ो32(idxd->reg_base + IDXD_INTCAUSE_OFFSET);
	अगर (cause)
		ioग_लिखो32(cause, idxd->reg_base + IDXD_INTCAUSE_OFFSET);

	जबतक (cause) अणु
		rc = process_misc_पूर्णांकerrupts(idxd, cause);
		अगर (rc < 0)
			अवरोध;
		cause = ioपढ़ो32(idxd->reg_base + IDXD_INTCAUSE_OFFSET);
		अगर (cause)
			ioग_लिखो32(cause, idxd->reg_base + IDXD_INTCAUSE_OFFSET);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत bool match_fault(काष्ठा idxd_desc *desc, u64 fault_addr)
अणु
	/*
	 * Completion address can be bad as well. Check fault address match क्रम descriptor
	 * and completion address.
	 */
	अगर ((u64)desc->hw == fault_addr || (u64)desc->completion == fault_addr) अणु
		काष्ठा idxd_device *idxd = desc->wq->idxd;
		काष्ठा device *dev = &idxd->pdev->dev;

		dev_warn(dev, "desc with fault address: %#llx\n", fault_addr);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत व्योम complete_desc(काष्ठा idxd_desc *desc, क्रमागत idxd_complete_type reason)
अणु
	idxd_dma_complete_txd(desc, reason);
	idxd_मुक्त_desc(desc->wq, desc);
पूर्ण

अटल पूर्णांक irq_process_pending_llist(काष्ठा idxd_irq_entry *irq_entry,
				     क्रमागत irq_work_type wtype,
				     पूर्णांक *processed, u64 data)
अणु
	काष्ठा idxd_desc *desc, *t;
	काष्ठा llist_node *head;
	पूर्णांक queued = 0;
	अचिन्हित दीर्घ flags;
	क्रमागत idxd_complete_type reason;

	*processed = 0;
	head = llist_del_all(&irq_entry->pending_llist);
	अगर (!head)
		जाओ out;

	अगर (wtype == IRQ_WORK_NORMAL)
		reason = IDXD_COMPLETE_NORMAL;
	अन्यथा
		reason = IDXD_COMPLETE_DEV_FAIL;

	llist_क्रम_each_entry_safe(desc, t, head, llnode) अणु
		अगर (desc->completion->status) अणु
			अगर ((desc->completion->status & DSA_COMP_STATUS_MASK) != DSA_COMP_SUCCESS)
				match_fault(desc, data);
			complete_desc(desc, reason);
			(*processed)++;
		पूर्ण अन्यथा अणु
			spin_lock_irqsave(&irq_entry->list_lock, flags);
			list_add_tail(&desc->list,
				      &irq_entry->work_list);
			spin_unlock_irqrestore(&irq_entry->list_lock, flags);
			queued++;
		पूर्ण
	पूर्ण

 out:
	वापस queued;
पूर्ण

अटल पूर्णांक irq_process_work_list(काष्ठा idxd_irq_entry *irq_entry,
				 क्रमागत irq_work_type wtype,
				 पूर्णांक *processed, u64 data)
अणु
	पूर्णांक queued = 0;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(flist);
	काष्ठा idxd_desc *desc, *n;
	क्रमागत idxd_complete_type reason;

	*processed = 0;
	अगर (wtype == IRQ_WORK_NORMAL)
		reason = IDXD_COMPLETE_NORMAL;
	अन्यथा
		reason = IDXD_COMPLETE_DEV_FAIL;

	/*
	 * This lock protects list corruption from access of list outside of the irq handler
	 * thपढ़ो.
	 */
	spin_lock_irqsave(&irq_entry->list_lock, flags);
	अगर (list_empty(&irq_entry->work_list)) अणु
		spin_unlock_irqrestore(&irq_entry->list_lock, flags);
		वापस 0;
	पूर्ण

	list_क्रम_each_entry_safe(desc, n, &irq_entry->work_list, list) अणु
		अगर (desc->completion->status) अणु
			list_del(&desc->list);
			(*processed)++;
			list_add_tail(&desc->list, &flist);
		पूर्ण अन्यथा अणु
			queued++;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&irq_entry->list_lock, flags);

	list_क्रम_each_entry(desc, &flist, list) अणु
		अगर ((desc->completion->status & DSA_COMP_STATUS_MASK) != DSA_COMP_SUCCESS)
			match_fault(desc, data);
		complete_desc(desc, reason);
	पूर्ण

	वापस queued;
पूर्ण

अटल पूर्णांक idxd_desc_process(काष्ठा idxd_irq_entry *irq_entry)
अणु
	पूर्णांक rc, processed, total = 0;

	/*
	 * There are two lists we are processing. The pending_llist is where
	 * submmiter adds all the submitted descriptor after sending it to
	 * the workqueue. It's a lockless singly linked list. The work_list
	 * is the common linux द्विगुन linked list. We are in a scenario of
	 * multiple producers and a single consumer. The producers are all
	 * the kernel submitters of descriptors, and the consumer is the
	 * kernel irq handler thपढ़ो क्रम the msix vector when using thपढ़ोed
	 * irq. To work with the restrictions of llist to reमुख्य lockless,
	 * we are करोing the following steps:
	 * 1. Iterate through the work_list and process any completed
	 *    descriptor. Delete the completed entries during iteration.
	 * 2. llist_del_all() from the pending list.
	 * 3. Iterate through the llist that was deleted from the pending list
	 *    and process the completed entries.
	 * 4. If the entry is still रुकोing on hardware, list_add_tail() to
	 *    the work_list.
	 * 5. Repeat until no more descriptors.
	 */
	करो अणु
		rc = irq_process_work_list(irq_entry, IRQ_WORK_NORMAL,
					   &processed, 0);
		total += processed;
		अगर (rc != 0)
			जारी;

		rc = irq_process_pending_llist(irq_entry, IRQ_WORK_NORMAL,
					       &processed, 0);
		total += processed;
	पूर्ण जबतक (rc != 0);

	वापस total;
पूर्ण

irqवापस_t idxd_wq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा idxd_irq_entry *irq_entry = data;
	पूर्णांक processed;

	processed = idxd_desc_process(irq_entry);
	अगर (processed == 0)
		वापस IRQ_NONE;

	वापस IRQ_HANDLED;
पूर्ण
