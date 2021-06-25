<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2019 Intel Corporation. All rights rsvd. */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/irq.h>
#समावेश <linux/msi.h>
#समावेश <uapi/linux/idxd.h>
#समावेश "../dmaengine.h"
#समावेश "idxd.h"
#समावेश "registers.h"

अटल व्योम idxd_cmd_exec(काष्ठा idxd_device *idxd, पूर्णांक cmd_code, u32 opeअक्रम,
			  u32 *status);

/* Interrupt control bits */
व्योम idxd_mask_msix_vector(काष्ठा idxd_device *idxd, पूर्णांक vec_id)
अणु
	काष्ठा irq_data *data = irq_get_irq_data(idxd->irq_entries[vec_id].vector);

	pci_msi_mask_irq(data);
पूर्ण

व्योम idxd_mask_msix_vectors(काष्ठा idxd_device *idxd)
अणु
	काष्ठा pci_dev *pdev = idxd->pdev;
	पूर्णांक msixcnt = pci_msix_vec_count(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < msixcnt; i++)
		idxd_mask_msix_vector(idxd, i);
पूर्ण

व्योम idxd_unmask_msix_vector(काष्ठा idxd_device *idxd, पूर्णांक vec_id)
अणु
	काष्ठा irq_data *data = irq_get_irq_data(idxd->irq_entries[vec_id].vector);

	pci_msi_unmask_irq(data);
पूर्ण

व्योम idxd_unmask_error_पूर्णांकerrupts(काष्ठा idxd_device *idxd)
अणु
	जोड़ genctrl_reg genctrl;

	genctrl.bits = ioपढ़ो32(idxd->reg_base + IDXD_GENCTRL_OFFSET);
	genctrl.softerr_पूर्णांक_en = 1;
	genctrl.halt_पूर्णांक_en = 1;
	ioग_लिखो32(genctrl.bits, idxd->reg_base + IDXD_GENCTRL_OFFSET);
पूर्ण

व्योम idxd_mask_error_पूर्णांकerrupts(काष्ठा idxd_device *idxd)
अणु
	जोड़ genctrl_reg genctrl;

	genctrl.bits = ioपढ़ो32(idxd->reg_base + IDXD_GENCTRL_OFFSET);
	genctrl.softerr_पूर्णांक_en = 0;
	genctrl.halt_पूर्णांक_en = 0;
	ioग_लिखो32(genctrl.bits, idxd->reg_base + IDXD_GENCTRL_OFFSET);
पूर्ण

अटल व्योम मुक्त_hw_descs(काष्ठा idxd_wq *wq)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < wq->num_descs; i++)
		kमुक्त(wq->hw_descs[i]);

	kमुक्त(wq->hw_descs);
पूर्ण

अटल पूर्णांक alloc_hw_descs(काष्ठा idxd_wq *wq, पूर्णांक num)
अणु
	काष्ठा device *dev = &wq->idxd->pdev->dev;
	पूर्णांक i;
	पूर्णांक node = dev_to_node(dev);

	wq->hw_descs = kसुस्मृति_node(num, माप(काष्ठा dsa_hw_desc *),
				    GFP_KERNEL, node);
	अगर (!wq->hw_descs)
		वापस -ENOMEM;

	क्रम (i = 0; i < num; i++) अणु
		wq->hw_descs[i] = kzalloc_node(माप(*wq->hw_descs[i]),
					       GFP_KERNEL, node);
		अगर (!wq->hw_descs[i]) अणु
			मुक्त_hw_descs(wq);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम मुक्त_descs(काष्ठा idxd_wq *wq)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < wq->num_descs; i++)
		kमुक्त(wq->descs[i]);

	kमुक्त(wq->descs);
पूर्ण

अटल पूर्णांक alloc_descs(काष्ठा idxd_wq *wq, पूर्णांक num)
अणु
	काष्ठा device *dev = &wq->idxd->pdev->dev;
	पूर्णांक i;
	पूर्णांक node = dev_to_node(dev);

	wq->descs = kसुस्मृति_node(num, माप(काष्ठा idxd_desc *),
				 GFP_KERNEL, node);
	अगर (!wq->descs)
		वापस -ENOMEM;

	क्रम (i = 0; i < num; i++) अणु
		wq->descs[i] = kzalloc_node(माप(*wq->descs[i]),
					    GFP_KERNEL, node);
		अगर (!wq->descs[i]) अणु
			मुक्त_descs(wq);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* WQ control bits */
पूर्णांक idxd_wq_alloc_resources(काष्ठा idxd_wq *wq)
अणु
	काष्ठा idxd_device *idxd = wq->idxd;
	काष्ठा device *dev = &idxd->pdev->dev;
	पूर्णांक rc, num_descs, i;
	पूर्णांक align;
	u64 पंचांगp;

	अगर (wq->type != IDXD_WQT_KERNEL)
		वापस 0;

	wq->num_descs = wq->size;
	num_descs = wq->size;

	rc = alloc_hw_descs(wq, num_descs);
	अगर (rc < 0)
		वापस rc;

	align = idxd->data->align;
	wq->compls_size = num_descs * idxd->data->compl_size + align;
	wq->compls_raw = dma_alloc_coherent(dev, wq->compls_size,
					    &wq->compls_addr_raw, GFP_KERNEL);
	अगर (!wq->compls_raw) अणु
		rc = -ENOMEM;
		जाओ fail_alloc_compls;
	पूर्ण

	/* Adjust alignment */
	wq->compls_addr = (wq->compls_addr_raw + (align - 1)) & ~(align - 1);
	पंचांगp = (u64)wq->compls_raw;
	पंचांगp = (पंचांगp + (align - 1)) & ~(align - 1);
	wq->compls = (काष्ठा dsa_completion_record *)पंचांगp;

	rc = alloc_descs(wq, num_descs);
	अगर (rc < 0)
		जाओ fail_alloc_descs;

	rc = sbiपंचांगap_queue_init_node(&wq->sbq, num_descs, -1, false, GFP_KERNEL,
				     dev_to_node(dev));
	अगर (rc < 0)
		जाओ fail_sbiपंचांगap_init;

	क्रम (i = 0; i < num_descs; i++) अणु
		काष्ठा idxd_desc *desc = wq->descs[i];

		desc->hw = wq->hw_descs[i];
		अगर (idxd->data->type == IDXD_TYPE_DSA)
			desc->completion = &wq->compls[i];
		अन्यथा अगर (idxd->data->type == IDXD_TYPE_IAX)
			desc->iax_completion = &wq->iax_compls[i];
		desc->compl_dma = wq->compls_addr + idxd->data->compl_size * i;
		desc->id = i;
		desc->wq = wq;
		desc->cpu = -1;
	पूर्ण

	वापस 0;

 fail_sbiपंचांगap_init:
	मुक्त_descs(wq);
 fail_alloc_descs:
	dma_मुक्त_coherent(dev, wq->compls_size, wq->compls_raw,
			  wq->compls_addr_raw);
 fail_alloc_compls:
	मुक्त_hw_descs(wq);
	वापस rc;
पूर्ण

व्योम idxd_wq_मुक्त_resources(काष्ठा idxd_wq *wq)
अणु
	काष्ठा device *dev = &wq->idxd->pdev->dev;

	अगर (wq->type != IDXD_WQT_KERNEL)
		वापस;

	मुक्त_hw_descs(wq);
	मुक्त_descs(wq);
	dma_मुक्त_coherent(dev, wq->compls_size, wq->compls_raw,
			  wq->compls_addr_raw);
	sbiपंचांगap_queue_मुक्त(&wq->sbq);
पूर्ण

पूर्णांक idxd_wq_enable(काष्ठा idxd_wq *wq)
अणु
	काष्ठा idxd_device *idxd = wq->idxd;
	काष्ठा device *dev = &idxd->pdev->dev;
	u32 status;

	अगर (wq->state == IDXD_WQ_ENABLED) अणु
		dev_dbg(dev, "WQ %d already enabled\n", wq->id);
		वापस -ENXIO;
	पूर्ण

	idxd_cmd_exec(idxd, IDXD_CMD_ENABLE_WQ, wq->id, &status);

	अगर (status != IDXD_CMDSTS_SUCCESS &&
	    status != IDXD_CMDSTS_ERR_WQ_ENABLED) अणु
		dev_dbg(dev, "WQ enable failed: %#x\n", status);
		वापस -ENXIO;
	पूर्ण

	wq->state = IDXD_WQ_ENABLED;
	dev_dbg(dev, "WQ %d enabled\n", wq->id);
	वापस 0;
पूर्ण

पूर्णांक idxd_wq_disable(काष्ठा idxd_wq *wq)
अणु
	काष्ठा idxd_device *idxd = wq->idxd;
	काष्ठा device *dev = &idxd->pdev->dev;
	u32 status, opeअक्रम;

	dev_dbg(dev, "Disabling WQ %d\n", wq->id);

	अगर (wq->state != IDXD_WQ_ENABLED) अणु
		dev_dbg(dev, "WQ %d in wrong state: %d\n", wq->id, wq->state);
		वापस 0;
	पूर्ण

	opeअक्रम = BIT(wq->id % 16) | ((wq->id / 16) << 16);
	idxd_cmd_exec(idxd, IDXD_CMD_DISABLE_WQ, opeअक्रम, &status);

	अगर (status != IDXD_CMDSTS_SUCCESS) अणु
		dev_dbg(dev, "WQ disable failed: %#x\n", status);
		वापस -ENXIO;
	पूर्ण

	wq->state = IDXD_WQ_DISABLED;
	dev_dbg(dev, "WQ %d disabled\n", wq->id);
	वापस 0;
पूर्ण

व्योम idxd_wq_drain(काष्ठा idxd_wq *wq)
अणु
	काष्ठा idxd_device *idxd = wq->idxd;
	काष्ठा device *dev = &idxd->pdev->dev;
	u32 opeअक्रम;

	अगर (wq->state != IDXD_WQ_ENABLED) अणु
		dev_dbg(dev, "WQ %d in wrong state: %d\n", wq->id, wq->state);
		वापस;
	पूर्ण

	dev_dbg(dev, "Draining WQ %d\n", wq->id);
	opeअक्रम = BIT(wq->id % 16) | ((wq->id / 16) << 16);
	idxd_cmd_exec(idxd, IDXD_CMD_DRAIN_WQ, opeअक्रम, शून्य);
पूर्ण

व्योम idxd_wq_reset(काष्ठा idxd_wq *wq)
अणु
	काष्ठा idxd_device *idxd = wq->idxd;
	काष्ठा device *dev = &idxd->pdev->dev;
	u32 opeअक्रम;

	अगर (wq->state != IDXD_WQ_ENABLED) अणु
		dev_dbg(dev, "WQ %d in wrong state: %d\n", wq->id, wq->state);
		वापस;
	पूर्ण

	opeअक्रम = BIT(wq->id % 16) | ((wq->id / 16) << 16);
	idxd_cmd_exec(idxd, IDXD_CMD_RESET_WQ, opeअक्रम, शून्य);
	wq->state = IDXD_WQ_DISABLED;
पूर्ण

पूर्णांक idxd_wq_map_portal(काष्ठा idxd_wq *wq)
अणु
	काष्ठा idxd_device *idxd = wq->idxd;
	काष्ठा pci_dev *pdev = idxd->pdev;
	काष्ठा device *dev = &pdev->dev;
	resource_माप_प्रकार start;

	start = pci_resource_start(pdev, IDXD_WQ_BAR);
	start += idxd_get_wq_portal_full_offset(wq->id, IDXD_PORTAL_LIMITED);

	wq->portal = devm_ioremap(dev, start, IDXD_PORTAL_SIZE);
	अगर (!wq->portal)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम idxd_wq_unmap_portal(काष्ठा idxd_wq *wq)
अणु
	काष्ठा device *dev = &wq->idxd->pdev->dev;

	devm_iounmap(dev, wq->portal);
	wq->portal = शून्य;
पूर्ण

व्योम idxd_wqs_unmap_portal(काष्ठा idxd_device *idxd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < idxd->max_wqs; i++) अणु
		काष्ठा idxd_wq *wq = idxd->wqs[i];

		अगर (wq->portal)
			idxd_wq_unmap_portal(wq);
	पूर्ण
पूर्ण

पूर्णांक idxd_wq_set_pasid(काष्ठा idxd_wq *wq, पूर्णांक pasid)
अणु
	काष्ठा idxd_device *idxd = wq->idxd;
	पूर्णांक rc;
	जोड़ wqcfg wqcfg;
	अचिन्हित पूर्णांक offset;
	अचिन्हित दीर्घ flags;

	rc = idxd_wq_disable(wq);
	अगर (rc < 0)
		वापस rc;

	offset = WQCFG_OFFSET(idxd, wq->id, WQCFG_PASID_IDX);
	spin_lock_irqsave(&idxd->dev_lock, flags);
	wqcfg.bits[WQCFG_PASID_IDX] = ioपढ़ो32(idxd->reg_base + offset);
	wqcfg.pasid_en = 1;
	wqcfg.pasid = pasid;
	ioग_लिखो32(wqcfg.bits[WQCFG_PASID_IDX], idxd->reg_base + offset);
	spin_unlock_irqrestore(&idxd->dev_lock, flags);

	rc = idxd_wq_enable(wq);
	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

पूर्णांक idxd_wq_disable_pasid(काष्ठा idxd_wq *wq)
अणु
	काष्ठा idxd_device *idxd = wq->idxd;
	पूर्णांक rc;
	जोड़ wqcfg wqcfg;
	अचिन्हित पूर्णांक offset;
	अचिन्हित दीर्घ flags;

	rc = idxd_wq_disable(wq);
	अगर (rc < 0)
		वापस rc;

	offset = WQCFG_OFFSET(idxd, wq->id, WQCFG_PASID_IDX);
	spin_lock_irqsave(&idxd->dev_lock, flags);
	wqcfg.bits[WQCFG_PASID_IDX] = ioपढ़ो32(idxd->reg_base + offset);
	wqcfg.pasid_en = 0;
	wqcfg.pasid = 0;
	ioग_लिखो32(wqcfg.bits[WQCFG_PASID_IDX], idxd->reg_base + offset);
	spin_unlock_irqrestore(&idxd->dev_lock, flags);

	rc = idxd_wq_enable(wq);
	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

व्योम idxd_wq_disable_cleanup(काष्ठा idxd_wq *wq)
अणु
	काष्ठा idxd_device *idxd = wq->idxd;

	lockdep_निश्चित_held(&idxd->dev_lock);
	स_रखो(wq->wqcfg, 0, idxd->wqcfg_size);
	wq->type = IDXD_WQT_NONE;
	wq->size = 0;
	wq->group = शून्य;
	wq->threshold = 0;
	wq->priority = 0;
	wq->ats_dis = 0;
	clear_bit(WQ_FLAG_DEDICATED, &wq->flags);
	स_रखो(wq->name, 0, WQ_NAME_SIZE);
पूर्ण

अटल व्योम idxd_wq_ref_release(काष्ठा percpu_ref *ref)
अणु
	काष्ठा idxd_wq *wq = container_of(ref, काष्ठा idxd_wq, wq_active);

	complete(&wq->wq_dead);
पूर्ण

पूर्णांक idxd_wq_init_percpu_ref(काष्ठा idxd_wq *wq)
अणु
	पूर्णांक rc;

	स_रखो(&wq->wq_active, 0, माप(wq->wq_active));
	rc = percpu_ref_init(&wq->wq_active, idxd_wq_ref_release, 0, GFP_KERNEL);
	अगर (rc < 0)
		वापस rc;
	reinit_completion(&wq->wq_dead);
	वापस 0;
पूर्ण

व्योम idxd_wq_quiesce(काष्ठा idxd_wq *wq)
अणु
	percpu_ref_समाप्त(&wq->wq_active);
	रुको_क्रम_completion(&wq->wq_dead);
	percpu_ref_निकास(&wq->wq_active);
पूर्ण

/* Device control bits */
अटल अंतरभूत bool idxd_is_enabled(काष्ठा idxd_device *idxd)
अणु
	जोड़ gensts_reg gensts;

	gensts.bits = ioपढ़ो32(idxd->reg_base + IDXD_GENSTATS_OFFSET);

	अगर (gensts.state == IDXD_DEVICE_STATE_ENABLED)
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool idxd_device_is_halted(काष्ठा idxd_device *idxd)
अणु
	जोड़ gensts_reg gensts;

	gensts.bits = ioपढ़ो32(idxd->reg_base + IDXD_GENSTATS_OFFSET);

	वापस (gensts.state == IDXD_DEVICE_STATE_HALT);
पूर्ण

/*
 * This is function is only used क्रम reset during probe and will
 * poll क्रम completion. Once the device is setup with पूर्णांकerrupts,
 * all commands will be करोne via पूर्णांकerrupt completion.
 */
पूर्णांक idxd_device_init_reset(काष्ठा idxd_device *idxd)
अणु
	काष्ठा device *dev = &idxd->pdev->dev;
	जोड़ idxd_command_reg cmd;
	अचिन्हित दीर्घ flags;

	अगर (idxd_device_is_halted(idxd)) अणु
		dev_warn(&idxd->pdev->dev, "Device is HALTED!\n");
		वापस -ENXIO;
	पूर्ण

	स_रखो(&cmd, 0, माप(cmd));
	cmd.cmd = IDXD_CMD_RESET_DEVICE;
	dev_dbg(dev, "%s: sending reset for init.\n", __func__);
	spin_lock_irqsave(&idxd->cmd_lock, flags);
	ioग_लिखो32(cmd.bits, idxd->reg_base + IDXD_CMD_OFFSET);

	जबतक (ioपढ़ो32(idxd->reg_base + IDXD_CMDSTS_OFFSET) &
	       IDXD_CMDSTS_ACTIVE)
		cpu_relax();
	spin_unlock_irqrestore(&idxd->cmd_lock, flags);
	वापस 0;
पूर्ण

अटल व्योम idxd_cmd_exec(काष्ठा idxd_device *idxd, पूर्णांक cmd_code, u32 opeअक्रम,
			  u32 *status)
अणु
	जोड़ idxd_command_reg cmd;
	DECLARE_COMPLETION_ONSTACK(करोne);
	अचिन्हित दीर्घ flags;

	अगर (idxd_device_is_halted(idxd)) अणु
		dev_warn(&idxd->pdev->dev, "Device is HALTED!\n");
		अगर (status)
			*status = IDXD_CMDSTS_HW_ERR;
		वापस;
	पूर्ण

	स_रखो(&cmd, 0, माप(cmd));
	cmd.cmd = cmd_code;
	cmd.opeअक्रम = opeअक्रम;
	cmd.पूर्णांक_req = 1;

	spin_lock_irqsave(&idxd->cmd_lock, flags);
	रुको_event_lock_irq(idxd->cmd_रुकोq,
			    !test_bit(IDXD_FLAG_CMD_RUNNING, &idxd->flags),
			    idxd->cmd_lock);

	dev_dbg(&idxd->pdev->dev, "%s: sending cmd: %#x op: %#x\n",
		__func__, cmd_code, opeअक्रम);

	idxd->cmd_status = 0;
	__set_bit(IDXD_FLAG_CMD_RUNNING, &idxd->flags);
	idxd->cmd_करोne = &करोne;
	ioग_लिखो32(cmd.bits, idxd->reg_base + IDXD_CMD_OFFSET);

	/*
	 * After command submitted, release lock and go to sleep until
	 * the command completes via पूर्णांकerrupt.
	 */
	spin_unlock_irqrestore(&idxd->cmd_lock, flags);
	रुको_क्रम_completion(&करोne);
	spin_lock_irqsave(&idxd->cmd_lock, flags);
	अगर (status) अणु
		*status = ioपढ़ो32(idxd->reg_base + IDXD_CMDSTS_OFFSET);
		idxd->cmd_status = *status & GENMASK(7, 0);
	पूर्ण

	__clear_bit(IDXD_FLAG_CMD_RUNNING, &idxd->flags);
	/* Wake up other pending commands */
	wake_up(&idxd->cmd_रुकोq);
	spin_unlock_irqrestore(&idxd->cmd_lock, flags);
पूर्ण

पूर्णांक idxd_device_enable(काष्ठा idxd_device *idxd)
अणु
	काष्ठा device *dev = &idxd->pdev->dev;
	u32 status;

	अगर (idxd_is_enabled(idxd)) अणु
		dev_dbg(dev, "Device already enabled\n");
		वापस -ENXIO;
	पूर्ण

	idxd_cmd_exec(idxd, IDXD_CMD_ENABLE_DEVICE, 0, &status);

	/* If the command is successful or अगर the device was enabled */
	अगर (status != IDXD_CMDSTS_SUCCESS &&
	    status != IDXD_CMDSTS_ERR_DEV_ENABLED) अणु
		dev_dbg(dev, "%s: err_code: %#x\n", __func__, status);
		वापस -ENXIO;
	पूर्ण

	idxd->state = IDXD_DEV_ENABLED;
	वापस 0;
पूर्ण

व्योम idxd_device_wqs_clear_state(काष्ठा idxd_device *idxd)
अणु
	पूर्णांक i;

	lockdep_निश्चित_held(&idxd->dev_lock);

	क्रम (i = 0; i < idxd->max_wqs; i++) अणु
		काष्ठा idxd_wq *wq = idxd->wqs[i];

		अगर (wq->state == IDXD_WQ_ENABLED) अणु
			idxd_wq_disable_cleanup(wq);
			wq->state = IDXD_WQ_DISABLED;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक idxd_device_disable(काष्ठा idxd_device *idxd)
अणु
	काष्ठा device *dev = &idxd->pdev->dev;
	u32 status;
	अचिन्हित दीर्घ flags;

	अगर (!idxd_is_enabled(idxd)) अणु
		dev_dbg(dev, "Device is not enabled\n");
		वापस 0;
	पूर्ण

	idxd_cmd_exec(idxd, IDXD_CMD_DISABLE_DEVICE, 0, &status);

	/* If the command is successful or अगर the device was disabled */
	अगर (status != IDXD_CMDSTS_SUCCESS &&
	    !(status & IDXD_CMDSTS_ERR_DIS_DEV_EN)) अणु
		dev_dbg(dev, "%s: err_code: %#x\n", __func__, status);
		वापस -ENXIO;
	पूर्ण

	spin_lock_irqsave(&idxd->dev_lock, flags);
	idxd_device_wqs_clear_state(idxd);
	idxd->state = IDXD_DEV_CONF_READY;
	spin_unlock_irqrestore(&idxd->dev_lock, flags);
	वापस 0;
पूर्ण

व्योम idxd_device_reset(काष्ठा idxd_device *idxd)
अणु
	अचिन्हित दीर्घ flags;

	idxd_cmd_exec(idxd, IDXD_CMD_RESET_DEVICE, 0, शून्य);
	spin_lock_irqsave(&idxd->dev_lock, flags);
	idxd_device_wqs_clear_state(idxd);
	idxd->state = IDXD_DEV_CONF_READY;
	spin_unlock_irqrestore(&idxd->dev_lock, flags);
पूर्ण

व्योम idxd_device_drain_pasid(काष्ठा idxd_device *idxd, पूर्णांक pasid)
अणु
	काष्ठा device *dev = &idxd->pdev->dev;
	u32 opeअक्रम;

	opeअक्रम = pasid;
	dev_dbg(dev, "cmd: %u operand: %#x\n", IDXD_CMD_DRAIN_PASID, opeअक्रम);
	idxd_cmd_exec(idxd, IDXD_CMD_DRAIN_PASID, opeअक्रम, शून्य);
	dev_dbg(dev, "pasid %d drained\n", pasid);
पूर्ण

पूर्णांक idxd_device_request_पूर्णांक_handle(काष्ठा idxd_device *idxd, पूर्णांक idx, पूर्णांक *handle,
				   क्रमागत idxd_पूर्णांकerrupt_type irq_type)
अणु
	काष्ठा device *dev = &idxd->pdev->dev;
	u32 opeअक्रम, status;

	अगर (!(idxd->hw.cmd_cap & BIT(IDXD_CMD_REQUEST_INT_HANDLE)))
		वापस -EOPNOTSUPP;

	dev_dbg(dev, "get int handle, idx %d\n", idx);

	opeअक्रम = idx & GENMASK(15, 0);
	अगर (irq_type == IDXD_IRQ_IMS)
		opeअक्रम |= CMD_INT_HANDLE_IMS;

	dev_dbg(dev, "cmd: %u operand: %#x\n", IDXD_CMD_REQUEST_INT_HANDLE, opeअक्रम);

	idxd_cmd_exec(idxd, IDXD_CMD_REQUEST_INT_HANDLE, opeअक्रम, &status);

	अगर ((status & IDXD_CMDSTS_ERR_MASK) != IDXD_CMDSTS_SUCCESS) अणु
		dev_dbg(dev, "request int handle failed: %#x\n", status);
		वापस -ENXIO;
	पूर्ण

	*handle = (status >> IDXD_CMDSTS_RES_SHIFT) & GENMASK(15, 0);

	dev_dbg(dev, "int handle acquired: %u\n", *handle);
	वापस 0;
पूर्ण

पूर्णांक idxd_device_release_पूर्णांक_handle(काष्ठा idxd_device *idxd, पूर्णांक handle,
				   क्रमागत idxd_पूर्णांकerrupt_type irq_type)
अणु
	काष्ठा device *dev = &idxd->pdev->dev;
	u32 opeअक्रम, status;
	जोड़ idxd_command_reg cmd;
	अचिन्हित दीर्घ flags;

	अगर (!(idxd->hw.cmd_cap & BIT(IDXD_CMD_RELEASE_INT_HANDLE)))
		वापस -EOPNOTSUPP;

	dev_dbg(dev, "release int handle, handle %d\n", handle);

	स_रखो(&cmd, 0, माप(cmd));
	opeअक्रम = handle & GENMASK(15, 0);

	अगर (irq_type == IDXD_IRQ_IMS)
		opeअक्रम |= CMD_INT_HANDLE_IMS;

	cmd.cmd = IDXD_CMD_RELEASE_INT_HANDLE;
	cmd.opeअक्रम = opeअक्रम;

	dev_dbg(dev, "cmd: %u operand: %#x\n", IDXD_CMD_RELEASE_INT_HANDLE, opeअक्रम);

	spin_lock_irqsave(&idxd->cmd_lock, flags);
	ioग_लिखो32(cmd.bits, idxd->reg_base + IDXD_CMD_OFFSET);

	जबतक (ioपढ़ो32(idxd->reg_base + IDXD_CMDSTS_OFFSET) & IDXD_CMDSTS_ACTIVE)
		cpu_relax();
	status = ioपढ़ो32(idxd->reg_base + IDXD_CMDSTS_OFFSET);
	spin_unlock_irqrestore(&idxd->cmd_lock, flags);

	अगर ((status & IDXD_CMDSTS_ERR_MASK) != IDXD_CMDSTS_SUCCESS) अणु
		dev_dbg(dev, "release int handle failed: %#x\n", status);
		वापस -ENXIO;
	पूर्ण

	dev_dbg(dev, "int handle released.\n");
	वापस 0;
पूर्ण

/* Device configuration bits */
व्योम idxd_msix_perm_setup(काष्ठा idxd_device *idxd)
अणु
	जोड़ msix_perm mperm;
	पूर्णांक i, msixcnt;

	msixcnt = pci_msix_vec_count(idxd->pdev);
	अगर (msixcnt < 0)
		वापस;

	mperm.bits = 0;
	mperm.pasid = idxd->pasid;
	mperm.pasid_en = device_pasid_enabled(idxd);
	क्रम (i = 1; i < msixcnt; i++)
		ioग_लिखो32(mperm.bits, idxd->reg_base + idxd->msix_perm_offset + i * 8);
पूर्ण

व्योम idxd_msix_perm_clear(काष्ठा idxd_device *idxd)
अणु
	जोड़ msix_perm mperm;
	पूर्णांक i, msixcnt;

	msixcnt = pci_msix_vec_count(idxd->pdev);
	अगर (msixcnt < 0)
		वापस;

	mperm.bits = 0;
	क्रम (i = 1; i < msixcnt; i++)
		ioग_लिखो32(mperm.bits, idxd->reg_base + idxd->msix_perm_offset + i * 8);
पूर्ण

अटल व्योम idxd_group_config_ग_लिखो(काष्ठा idxd_group *group)
अणु
	काष्ठा idxd_device *idxd = group->idxd;
	काष्ठा device *dev = &idxd->pdev->dev;
	पूर्णांक i;
	u32 grpcfg_offset;

	dev_dbg(dev, "Writing group %d cfg registers\n", group->id);

	/* setup GRPWQCFG */
	क्रम (i = 0; i < GRPWQCFG_STRIDES; i++) अणु
		grpcfg_offset = GRPWQCFG_OFFSET(idxd, group->id, i);
		ioग_लिखो64(group->grpcfg.wqs[i], idxd->reg_base + grpcfg_offset);
		dev_dbg(dev, "GRPCFG wq[%d:%d: %#x]: %#llx\n",
			group->id, i, grpcfg_offset,
			ioपढ़ो64(idxd->reg_base + grpcfg_offset));
	पूर्ण

	/* setup GRPENGCFG */
	grpcfg_offset = GRPENGCFG_OFFSET(idxd, group->id);
	ioग_लिखो64(group->grpcfg.engines, idxd->reg_base + grpcfg_offset);
	dev_dbg(dev, "GRPCFG engs[%d: %#x]: %#llx\n", group->id,
		grpcfg_offset, ioपढ़ो64(idxd->reg_base + grpcfg_offset));

	/* setup GRPFLAGS */
	grpcfg_offset = GRPFLGCFG_OFFSET(idxd, group->id);
	ioग_लिखो32(group->grpcfg.flags.bits, idxd->reg_base + grpcfg_offset);
	dev_dbg(dev, "GRPFLAGS flags[%d: %#x]: %#x\n",
		group->id, grpcfg_offset,
		ioपढ़ो32(idxd->reg_base + grpcfg_offset));
पूर्ण

अटल पूर्णांक idxd_groups_config_ग_लिखो(काष्ठा idxd_device *idxd)

अणु
	जोड़ gencfg_reg reg;
	पूर्णांक i;
	काष्ठा device *dev = &idxd->pdev->dev;

	/* Setup bandwidth token limit */
	अगर (idxd->token_limit) अणु
		reg.bits = ioपढ़ो32(idxd->reg_base + IDXD_GENCFG_OFFSET);
		reg.token_limit = idxd->token_limit;
		ioग_लिखो32(reg.bits, idxd->reg_base + IDXD_GENCFG_OFFSET);
	पूर्ण

	dev_dbg(dev, "GENCFG(%#x): %#x\n", IDXD_GENCFG_OFFSET,
		ioपढ़ो32(idxd->reg_base + IDXD_GENCFG_OFFSET));

	क्रम (i = 0; i < idxd->max_groups; i++) अणु
		काष्ठा idxd_group *group = idxd->groups[i];

		idxd_group_config_ग_लिखो(group);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक idxd_wq_config_ग_लिखो(काष्ठा idxd_wq *wq)
अणु
	काष्ठा idxd_device *idxd = wq->idxd;
	काष्ठा device *dev = &idxd->pdev->dev;
	u32 wq_offset;
	पूर्णांक i;

	अगर (!wq->group)
		वापस 0;

	/*
	 * Instead of स_रखो the entire shaकरोw copy of WQCFG, copy from the hardware after
	 * wq reset. This will copy back the sticky values that are present on some devices.
	 */
	क्रम (i = 0; i < WQCFG_STRIDES(idxd); i++) अणु
		wq_offset = WQCFG_OFFSET(idxd, wq->id, i);
		wq->wqcfg->bits[i] = ioपढ़ो32(idxd->reg_base + wq_offset);
	पूर्ण

	/* byte 0-3 */
	wq->wqcfg->wq_size = wq->size;

	अगर (wq->size == 0) अणु
		dev_warn(dev, "Incorrect work queue size: 0\n");
		वापस -EINVAL;
	पूर्ण

	/* bytes 4-7 */
	wq->wqcfg->wq_thresh = wq->threshold;

	/* byte 8-11 */
	wq->wqcfg->priv = !!(wq->type == IDXD_WQT_KERNEL);
	अगर (wq_dedicated(wq))
		wq->wqcfg->mode = 1;

	अगर (device_pasid_enabled(idxd)) अणु
		wq->wqcfg->pasid_en = 1;
		अगर (wq->type == IDXD_WQT_KERNEL && wq_dedicated(wq))
			wq->wqcfg->pasid = idxd->pasid;
	पूर्ण

	wq->wqcfg->priority = wq->priority;

	अगर (idxd->hw.gen_cap.block_on_fault &&
	    test_bit(WQ_FLAG_BLOCK_ON_FAULT, &wq->flags))
		wq->wqcfg->bof = 1;

	अगर (idxd->hw.wq_cap.wq_ats_support)
		wq->wqcfg->wq_ats_disable = wq->ats_dis;

	/* bytes 12-15 */
	wq->wqcfg->max_xfer_shअगरt = ilog2(wq->max_xfer_bytes);
	wq->wqcfg->max_batch_shअगरt = ilog2(wq->max_batch_size);

	dev_dbg(dev, "WQ %d CFGs\n", wq->id);
	क्रम (i = 0; i < WQCFG_STRIDES(idxd); i++) अणु
		wq_offset = WQCFG_OFFSET(idxd, wq->id, i);
		ioग_लिखो32(wq->wqcfg->bits[i], idxd->reg_base + wq_offset);
		dev_dbg(dev, "WQ[%d][%d][%#x]: %#x\n",
			wq->id, i, wq_offset,
			ioपढ़ो32(idxd->reg_base + wq_offset));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक idxd_wqs_config_ग_लिखो(काष्ठा idxd_device *idxd)
अणु
	पूर्णांक i, rc;

	क्रम (i = 0; i < idxd->max_wqs; i++) अणु
		काष्ठा idxd_wq *wq = idxd->wqs[i];

		rc = idxd_wq_config_ग_लिखो(wq);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम idxd_group_flags_setup(काष्ठा idxd_device *idxd)
अणु
	पूर्णांक i;

	/* TC-A 0 and TC-B 1 should be शेषs */
	क्रम (i = 0; i < idxd->max_groups; i++) अणु
		काष्ठा idxd_group *group = idxd->groups[i];

		अगर (group->tc_a == -1)
			group->tc_a = group->grpcfg.flags.tc_a = 0;
		अन्यथा
			group->grpcfg.flags.tc_a = group->tc_a;
		अगर (group->tc_b == -1)
			group->tc_b = group->grpcfg.flags.tc_b = 1;
		अन्यथा
			group->grpcfg.flags.tc_b = group->tc_b;
		group->grpcfg.flags.use_token_limit = group->use_token_limit;
		group->grpcfg.flags.tokens_reserved = group->tokens_reserved;
		अगर (group->tokens_allowed)
			group->grpcfg.flags.tokens_allowed =
				group->tokens_allowed;
		अन्यथा
			group->grpcfg.flags.tokens_allowed = idxd->max_tokens;
	पूर्ण
पूर्ण

अटल पूर्णांक idxd_engines_setup(काष्ठा idxd_device *idxd)
अणु
	पूर्णांक i, engines = 0;
	काष्ठा idxd_engine *eng;
	काष्ठा idxd_group *group;

	क्रम (i = 0; i < idxd->max_groups; i++) अणु
		group = idxd->groups[i];
		group->grpcfg.engines = 0;
	पूर्ण

	क्रम (i = 0; i < idxd->max_engines; i++) अणु
		eng = idxd->engines[i];
		group = eng->group;

		अगर (!group)
			जारी;

		group->grpcfg.engines |= BIT(eng->id);
		engines++;
	पूर्ण

	अगर (!engines)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक idxd_wqs_setup(काष्ठा idxd_device *idxd)
अणु
	काष्ठा idxd_wq *wq;
	काष्ठा idxd_group *group;
	पूर्णांक i, j, configured = 0;
	काष्ठा device *dev = &idxd->pdev->dev;

	क्रम (i = 0; i < idxd->max_groups; i++) अणु
		group = idxd->groups[i];
		क्रम (j = 0; j < 4; j++)
			group->grpcfg.wqs[j] = 0;
	पूर्ण

	क्रम (i = 0; i < idxd->max_wqs; i++) अणु
		wq = idxd->wqs[i];
		group = wq->group;

		अगर (!wq->group)
			जारी;
		अगर (!wq->size)
			जारी;

		अगर (wq_shared(wq) && !device_swq_supported(idxd)) अणु
			dev_warn(dev, "No shared wq support but configured.\n");
			वापस -EINVAL;
		पूर्ण

		group->grpcfg.wqs[wq->id / 64] |= BIT(wq->id % 64);
		configured++;
	पूर्ण

	अगर (configured == 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक idxd_device_config(काष्ठा idxd_device *idxd)
अणु
	पूर्णांक rc;

	lockdep_निश्चित_held(&idxd->dev_lock);
	rc = idxd_wqs_setup(idxd);
	अगर (rc < 0)
		वापस rc;

	rc = idxd_engines_setup(idxd);
	अगर (rc < 0)
		वापस rc;

	idxd_group_flags_setup(idxd);

	rc = idxd_wqs_config_ग_लिखो(idxd);
	अगर (rc < 0)
		वापस rc;

	rc = idxd_groups_config_ग_लिखो(idxd);
	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक idxd_wq_load_config(काष्ठा idxd_wq *wq)
अणु
	काष्ठा idxd_device *idxd = wq->idxd;
	काष्ठा device *dev = &idxd->pdev->dev;
	पूर्णांक wqcfg_offset;
	पूर्णांक i;

	wqcfg_offset = WQCFG_OFFSET(idxd, wq->id, 0);
	स_नकल_fromio(wq->wqcfg, idxd->reg_base + wqcfg_offset, idxd->wqcfg_size);

	wq->size = wq->wqcfg->wq_size;
	wq->threshold = wq->wqcfg->wq_thresh;
	अगर (wq->wqcfg->priv)
		wq->type = IDXD_WQT_KERNEL;

	/* The driver करोes not support shared WQ mode in पढ़ो-only config yet */
	अगर (wq->wqcfg->mode == 0 || wq->wqcfg->pasid_en)
		वापस -EOPNOTSUPP;

	set_bit(WQ_FLAG_DEDICATED, &wq->flags);

	wq->priority = wq->wqcfg->priority;

	क्रम (i = 0; i < WQCFG_STRIDES(idxd); i++) अणु
		wqcfg_offset = WQCFG_OFFSET(idxd, wq->id, i);
		dev_dbg(dev, "WQ[%d][%d][%#x]: %#x\n", wq->id, i, wqcfg_offset, wq->wqcfg->bits[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम idxd_group_load_config(काष्ठा idxd_group *group)
अणु
	काष्ठा idxd_device *idxd = group->idxd;
	काष्ठा device *dev = &idxd->pdev->dev;
	पूर्णांक i, j, grpcfg_offset;

	/*
	 * Load WQS bit fields
	 * Iterate through all 256 bits 64 bits at a समय
	 */
	क्रम (i = 0; i < GRPWQCFG_STRIDES; i++) अणु
		काष्ठा idxd_wq *wq;

		grpcfg_offset = GRPWQCFG_OFFSET(idxd, group->id, i);
		group->grpcfg.wqs[i] = ioपढ़ो64(idxd->reg_base + grpcfg_offset);
		dev_dbg(dev, "GRPCFG wq[%d:%d: %#x]: %#llx\n",
			group->id, i, grpcfg_offset, group->grpcfg.wqs[i]);

		अगर (i * 64 >= idxd->max_wqs)
			अवरोध;

		/* Iterate through all 64 bits and check क्रम wq set */
		क्रम (j = 0; j < 64; j++) अणु
			पूर्णांक id = i * 64 + j;

			/* No need to check beyond max wqs */
			अगर (id >= idxd->max_wqs)
				अवरोध;

			/* Set group assignment क्रम wq अगर wq bit is set */
			अगर (group->grpcfg.wqs[i] & BIT(j)) अणु
				wq = idxd->wqs[id];
				wq->group = group;
			पूर्ण
		पूर्ण
	पूर्ण

	grpcfg_offset = GRPENGCFG_OFFSET(idxd, group->id);
	group->grpcfg.engines = ioपढ़ो64(idxd->reg_base + grpcfg_offset);
	dev_dbg(dev, "GRPCFG engs[%d: %#x]: %#llx\n", group->id,
		grpcfg_offset, group->grpcfg.engines);

	/* Iterate through all 64 bits to check engines set */
	क्रम (i = 0; i < 64; i++) अणु
		अगर (i >= idxd->max_engines)
			अवरोध;

		अगर (group->grpcfg.engines & BIT(i)) अणु
			काष्ठा idxd_engine *engine = idxd->engines[i];

			engine->group = group;
		पूर्ण
	पूर्ण

	grpcfg_offset = GRPFLGCFG_OFFSET(idxd, group->id);
	group->grpcfg.flags.bits = ioपढ़ो32(idxd->reg_base + grpcfg_offset);
	dev_dbg(dev, "GRPFLAGS flags[%d: %#x]: %#x\n",
		group->id, grpcfg_offset, group->grpcfg.flags.bits);
पूर्ण

पूर्णांक idxd_device_load_config(काष्ठा idxd_device *idxd)
अणु
	जोड़ gencfg_reg reg;
	पूर्णांक i, rc;

	reg.bits = ioपढ़ो32(idxd->reg_base + IDXD_GENCFG_OFFSET);
	idxd->token_limit = reg.token_limit;

	क्रम (i = 0; i < idxd->max_groups; i++) अणु
		काष्ठा idxd_group *group = idxd->groups[i];

		idxd_group_load_config(group);
	पूर्ण

	क्रम (i = 0; i < idxd->max_wqs; i++) अणु
		काष्ठा idxd_wq *wq = idxd->wqs[i];

		rc = idxd_wq_load_config(wq);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण
