<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2019 Intel Corporation. All rights rsvd. */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/aer.h>
#समावेश <linux/fs.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/device.h>
#समावेश <linux/idr.h>
#समावेश <linux/पूर्णांकel-svm.h>
#समावेश <linux/iommu.h>
#समावेश <uapi/linux/idxd.h>
#समावेश <linux/dmaengine.h>
#समावेश "../dmaengine.h"
#समावेश "registers.h"
#समावेश "idxd.h"
#समावेश "perfmon.h"

MODULE_VERSION(IDXD_DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Intel Corporation");

अटल bool sva = true;
module_param(sva, bool, 0644);
MODULE_PARM_DESC(sva, "Toggle SVA support on/off");

#घोषणा DRV_NAME "idxd"

bool support_enqcmd;
DEFINE_IDA(idxd_ida);

अटल काष्ठा idxd_driver_data idxd_driver_data[] = अणु
	[IDXD_TYPE_DSA] = अणु
		.name_prefix = "dsa",
		.type = IDXD_TYPE_DSA,
		.compl_size = माप(काष्ठा dsa_completion_record),
		.align = 32,
		.dev_type = &dsa_device_type,
	पूर्ण,
	[IDXD_TYPE_IAX] = अणु
		.name_prefix = "iax",
		.type = IDXD_TYPE_IAX,
		.compl_size = माप(काष्ठा iax_completion_record),
		.align = 64,
		.dev_type = &iax_device_type,
	पूर्ण,
पूर्ण;

अटल काष्ठा pci_device_id idxd_pci_tbl[] = अणु
	/* DSA ver 1.0 platक्रमms */
	अणु PCI_DEVICE_DATA(INTEL, DSA_SPR0, &idxd_driver_data[IDXD_TYPE_DSA]) पूर्ण,

	/* IAX ver 1.0 platक्रमms */
	अणु PCI_DEVICE_DATA(INTEL, IAX_SPR0, &idxd_driver_data[IDXD_TYPE_IAX]) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, idxd_pci_tbl);

अटल पूर्णांक idxd_setup_पूर्णांकerrupts(काष्ठा idxd_device *idxd)
अणु
	काष्ठा pci_dev *pdev = idxd->pdev;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा idxd_irq_entry *irq_entry;
	पूर्णांक i, msixcnt;
	पूर्णांक rc = 0;

	msixcnt = pci_msix_vec_count(pdev);
	अगर (msixcnt < 0) अणु
		dev_err(dev, "Not MSI-X interrupt capable.\n");
		वापस -ENOSPC;
	पूर्ण

	rc = pci_alloc_irq_vectors(pdev, msixcnt, msixcnt, PCI_IRQ_MSIX);
	अगर (rc != msixcnt) अणु
		dev_err(dev, "Failed enabling %d MSIX entries: %d\n", msixcnt, rc);
		वापस -ENOSPC;
	पूर्ण
	dev_dbg(dev, "Enabled %d msix vectors\n", msixcnt);

	/*
	 * We implement 1 completion list per MSI-X entry except क्रम
	 * entry 0, which is क्रम errors and others.
	 */
	idxd->irq_entries = kसुस्मृति_node(msixcnt, माप(काष्ठा idxd_irq_entry),
					 GFP_KERNEL, dev_to_node(dev));
	अगर (!idxd->irq_entries) अणु
		rc = -ENOMEM;
		जाओ err_irq_entries;
	पूर्ण

	क्रम (i = 0; i < msixcnt; i++) अणु
		idxd->irq_entries[i].id = i;
		idxd->irq_entries[i].idxd = idxd;
		idxd->irq_entries[i].vector = pci_irq_vector(pdev, i);
		spin_lock_init(&idxd->irq_entries[i].list_lock);
	पूर्ण

	irq_entry = &idxd->irq_entries[0];
	rc = request_thपढ़ोed_irq(irq_entry->vector, शून्य, idxd_misc_thपढ़ो,
				  0, "idxd-misc", irq_entry);
	अगर (rc < 0) अणु
		dev_err(dev, "Failed to allocate misc interrupt.\n");
		जाओ err_misc_irq;
	पूर्ण

	dev_dbg(dev, "Allocated idxd-misc handler on msix vector %d\n", irq_entry->vector);

	/* first MSI-X entry is not क्रम wq पूर्णांकerrupts */
	idxd->num_wq_irqs = msixcnt - 1;

	क्रम (i = 1; i < msixcnt; i++) अणु
		irq_entry = &idxd->irq_entries[i];

		init_llist_head(&idxd->irq_entries[i].pending_llist);
		INIT_LIST_HEAD(&idxd->irq_entries[i].work_list);
		rc = request_thपढ़ोed_irq(irq_entry->vector, शून्य,
					  idxd_wq_thपढ़ो, 0, "idxd-portal", irq_entry);
		अगर (rc < 0) अणु
			dev_err(dev, "Failed to allocate irq %d.\n", irq_entry->vector);
			जाओ err_wq_irqs;
		पूर्ण

		dev_dbg(dev, "Allocated idxd-msix %d for vector %d\n", i, irq_entry->vector);
		अगर (idxd->hw.cmd_cap & BIT(IDXD_CMD_REQUEST_INT_HANDLE)) अणु
			/*
			 * The MSIX vector क्रमागतeration starts at 1 with vector 0 being the
			 * misc पूर्णांकerrupt that handles non I/O completion events. The
			 * पूर्णांकerrupt handles are क्रम IMS क्रमागतeration on guest. The misc
			 * पूर्णांकerrupt vector करोes not require a handle and thereक्रमe we start
			 * the पूर्णांक_handles at index 0. Since 'i' starts at 1, the first
			 * पूर्णांक_handles index will be 0.
			 */
			rc = idxd_device_request_पूर्णांक_handle(idxd, i, &idxd->पूर्णांक_handles[i - 1],
							    IDXD_IRQ_MSIX);
			अगर (rc < 0) अणु
				मुक्त_irq(irq_entry->vector, irq_entry);
				जाओ err_wq_irqs;
			पूर्ण
			dev_dbg(dev, "int handle requested: %u\n", idxd->पूर्णांक_handles[i - 1]);
		पूर्ण
	पूर्ण

	idxd_unmask_error_पूर्णांकerrupts(idxd);
	idxd_msix_perm_setup(idxd);
	वापस 0;

 err_wq_irqs:
	जबतक (--i >= 0) अणु
		irq_entry = &idxd->irq_entries[i];
		मुक्त_irq(irq_entry->vector, irq_entry);
		अगर (i != 0)
			idxd_device_release_पूर्णांक_handle(idxd,
						       idxd->पूर्णांक_handles[i], IDXD_IRQ_MSIX);
	पूर्ण
 err_misc_irq:
	/* Disable error पूर्णांकerrupt generation */
	idxd_mask_error_पूर्णांकerrupts(idxd);
 err_irq_entries:
	pci_मुक्त_irq_vectors(pdev);
	dev_err(dev, "No usable interrupts\n");
	वापस rc;
पूर्ण

अटल व्योम idxd_cleanup_पूर्णांकerrupts(काष्ठा idxd_device *idxd)
अणु
	काष्ठा pci_dev *pdev = idxd->pdev;
	काष्ठा idxd_irq_entry *irq_entry;
	पूर्णांक i, msixcnt;

	msixcnt = pci_msix_vec_count(pdev);
	अगर (msixcnt <= 0)
		वापस;

	irq_entry = &idxd->irq_entries[0];
	मुक्त_irq(irq_entry->vector, irq_entry);

	क्रम (i = 1; i < msixcnt; i++) अणु

		irq_entry = &idxd->irq_entries[i];
		अगर (idxd->hw.cmd_cap & BIT(IDXD_CMD_RELEASE_INT_HANDLE))
			idxd_device_release_पूर्णांक_handle(idxd, idxd->पूर्णांक_handles[i],
						       IDXD_IRQ_MSIX);
		मुक्त_irq(irq_entry->vector, irq_entry);
	पूर्ण

	idxd_mask_error_पूर्णांकerrupts(idxd);
	pci_मुक्त_irq_vectors(pdev);
पूर्ण

अटल पूर्णांक idxd_setup_wqs(काष्ठा idxd_device *idxd)
अणु
	काष्ठा device *dev = &idxd->pdev->dev;
	काष्ठा idxd_wq *wq;
	पूर्णांक i, rc;

	idxd->wqs = kसुस्मृति_node(idxd->max_wqs, माप(काष्ठा idxd_wq *),
				 GFP_KERNEL, dev_to_node(dev));
	अगर (!idxd->wqs)
		वापस -ENOMEM;

	क्रम (i = 0; i < idxd->max_wqs; i++) अणु
		wq = kzalloc_node(माप(*wq), GFP_KERNEL, dev_to_node(dev));
		अगर (!wq) अणु
			rc = -ENOMEM;
			जाओ err;
		पूर्ण

		wq->id = i;
		wq->idxd = idxd;
		device_initialize(&wq->conf_dev);
		wq->conf_dev.parent = &idxd->conf_dev;
		wq->conf_dev.bus = &dsa_bus_type;
		wq->conf_dev.type = &idxd_wq_device_type;
		rc = dev_set_name(&wq->conf_dev, "wq%d.%d", idxd->id, wq->id);
		अगर (rc < 0) अणु
			put_device(&wq->conf_dev);
			जाओ err;
		पूर्ण

		mutex_init(&wq->wq_lock);
		init_रुकोqueue_head(&wq->err_queue);
		init_completion(&wq->wq_dead);
		wq->max_xfer_bytes = idxd->max_xfer_bytes;
		wq->max_batch_size = idxd->max_batch_size;
		wq->wqcfg = kzalloc_node(idxd->wqcfg_size, GFP_KERNEL, dev_to_node(dev));
		अगर (!wq->wqcfg) अणु
			put_device(&wq->conf_dev);
			rc = -ENOMEM;
			जाओ err;
		पूर्ण
		idxd->wqs[i] = wq;
	पूर्ण

	वापस 0;

 err:
	जबतक (--i >= 0)
		put_device(&idxd->wqs[i]->conf_dev);
	वापस rc;
पूर्ण

अटल पूर्णांक idxd_setup_engines(काष्ठा idxd_device *idxd)
अणु
	काष्ठा idxd_engine *engine;
	काष्ठा device *dev = &idxd->pdev->dev;
	पूर्णांक i, rc;

	idxd->engines = kसुस्मृति_node(idxd->max_engines, माप(काष्ठा idxd_engine *),
				     GFP_KERNEL, dev_to_node(dev));
	अगर (!idxd->engines)
		वापस -ENOMEM;

	क्रम (i = 0; i < idxd->max_engines; i++) अणु
		engine = kzalloc_node(माप(*engine), GFP_KERNEL, dev_to_node(dev));
		अगर (!engine) अणु
			rc = -ENOMEM;
			जाओ err;
		पूर्ण

		engine->id = i;
		engine->idxd = idxd;
		device_initialize(&engine->conf_dev);
		engine->conf_dev.parent = &idxd->conf_dev;
		engine->conf_dev.bus = &dsa_bus_type;
		engine->conf_dev.type = &idxd_engine_device_type;
		rc = dev_set_name(&engine->conf_dev, "engine%d.%d", idxd->id, engine->id);
		अगर (rc < 0) अणु
			put_device(&engine->conf_dev);
			जाओ err;
		पूर्ण

		idxd->engines[i] = engine;
	पूर्ण

	वापस 0;

 err:
	जबतक (--i >= 0)
		put_device(&idxd->engines[i]->conf_dev);
	वापस rc;
पूर्ण

अटल पूर्णांक idxd_setup_groups(काष्ठा idxd_device *idxd)
अणु
	काष्ठा device *dev = &idxd->pdev->dev;
	काष्ठा idxd_group *group;
	पूर्णांक i, rc;

	idxd->groups = kसुस्मृति_node(idxd->max_groups, माप(काष्ठा idxd_group *),
				    GFP_KERNEL, dev_to_node(dev));
	अगर (!idxd->groups)
		वापस -ENOMEM;

	क्रम (i = 0; i < idxd->max_groups; i++) अणु
		group = kzalloc_node(माप(*group), GFP_KERNEL, dev_to_node(dev));
		अगर (!group) अणु
			rc = -ENOMEM;
			जाओ err;
		पूर्ण

		group->id = i;
		group->idxd = idxd;
		device_initialize(&group->conf_dev);
		group->conf_dev.parent = &idxd->conf_dev;
		group->conf_dev.bus = &dsa_bus_type;
		group->conf_dev.type = &idxd_group_device_type;
		rc = dev_set_name(&group->conf_dev, "group%d.%d", idxd->id, group->id);
		अगर (rc < 0) अणु
			put_device(&group->conf_dev);
			जाओ err;
		पूर्ण

		idxd->groups[i] = group;
		group->tc_a = -1;
		group->tc_b = -1;
	पूर्ण

	वापस 0;

 err:
	जबतक (--i >= 0)
		put_device(&idxd->groups[i]->conf_dev);
	वापस rc;
पूर्ण

अटल व्योम idxd_cleanup_पूर्णांकernals(काष्ठा idxd_device *idxd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < idxd->max_groups; i++)
		put_device(&idxd->groups[i]->conf_dev);
	क्रम (i = 0; i < idxd->max_engines; i++)
		put_device(&idxd->engines[i]->conf_dev);
	क्रम (i = 0; i < idxd->max_wqs; i++)
		put_device(&idxd->wqs[i]->conf_dev);
	destroy_workqueue(idxd->wq);
पूर्ण

अटल पूर्णांक idxd_setup_पूर्णांकernals(काष्ठा idxd_device *idxd)
अणु
	काष्ठा device *dev = &idxd->pdev->dev;
	पूर्णांक rc, i;

	init_रुकोqueue_head(&idxd->cmd_रुकोq);

	अगर (idxd->hw.cmd_cap & BIT(IDXD_CMD_REQUEST_INT_HANDLE)) अणु
		idxd->पूर्णांक_handles = devm_kसुस्मृति(dev, idxd->max_wqs, माप(पूर्णांक), GFP_KERNEL);
		अगर (!idxd->पूर्णांक_handles)
			वापस -ENOMEM;
	पूर्ण

	rc = idxd_setup_wqs(idxd);
	अगर (rc < 0)
		जाओ err_wqs;

	rc = idxd_setup_engines(idxd);
	अगर (rc < 0)
		जाओ err_engine;

	rc = idxd_setup_groups(idxd);
	अगर (rc < 0)
		जाओ err_group;

	idxd->wq = create_workqueue(dev_name(dev));
	अगर (!idxd->wq) अणु
		rc = -ENOMEM;
		जाओ err_wkq_create;
	पूर्ण

	वापस 0;

 err_wkq_create:
	क्रम (i = 0; i < idxd->max_groups; i++)
		put_device(&idxd->groups[i]->conf_dev);
 err_group:
	क्रम (i = 0; i < idxd->max_engines; i++)
		put_device(&idxd->engines[i]->conf_dev);
 err_engine:
	क्रम (i = 0; i < idxd->max_wqs; i++)
		put_device(&idxd->wqs[i]->conf_dev);
 err_wqs:
	kमुक्त(idxd->पूर्णांक_handles);
	वापस rc;
पूर्ण

अटल व्योम idxd_पढ़ो_table_offsets(काष्ठा idxd_device *idxd)
अणु
	जोड़ offsets_reg offsets;
	काष्ठा device *dev = &idxd->pdev->dev;

	offsets.bits[0] = ioपढ़ो64(idxd->reg_base + IDXD_TABLE_OFFSET);
	offsets.bits[1] = ioपढ़ो64(idxd->reg_base + IDXD_TABLE_OFFSET + माप(u64));
	idxd->grpcfg_offset = offsets.grpcfg * IDXD_TABLE_MULT;
	dev_dbg(dev, "IDXD Group Config Offset: %#x\n", idxd->grpcfg_offset);
	idxd->wqcfg_offset = offsets.wqcfg * IDXD_TABLE_MULT;
	dev_dbg(dev, "IDXD Work Queue Config Offset: %#x\n", idxd->wqcfg_offset);
	idxd->msix_perm_offset = offsets.msix_perm * IDXD_TABLE_MULT;
	dev_dbg(dev, "IDXD MSIX Permission Offset: %#x\n", idxd->msix_perm_offset);
	idxd->perfmon_offset = offsets.perfmon * IDXD_TABLE_MULT;
	dev_dbg(dev, "IDXD Perfmon Offset: %#x\n", idxd->perfmon_offset);
पूर्ण

अटल व्योम idxd_पढ़ो_caps(काष्ठा idxd_device *idxd)
अणु
	काष्ठा device *dev = &idxd->pdev->dev;
	पूर्णांक i;

	/* पढ़ोing generic capabilities */
	idxd->hw.gen_cap.bits = ioपढ़ो64(idxd->reg_base + IDXD_GENCAP_OFFSET);
	dev_dbg(dev, "gen_cap: %#llx\n", idxd->hw.gen_cap.bits);

	अगर (idxd->hw.gen_cap.cmd_cap) अणु
		idxd->hw.cmd_cap = ioपढ़ो32(idxd->reg_base + IDXD_CMDCAP_OFFSET);
		dev_dbg(dev, "cmd_cap: %#x\n", idxd->hw.cmd_cap);
	पूर्ण

	idxd->max_xfer_bytes = 1ULL << idxd->hw.gen_cap.max_xfer_shअगरt;
	dev_dbg(dev, "max xfer size: %llu bytes\n", idxd->max_xfer_bytes);
	idxd->max_batch_size = 1U << idxd->hw.gen_cap.max_batch_shअगरt;
	dev_dbg(dev, "max batch size: %u\n", idxd->max_batch_size);
	अगर (idxd->hw.gen_cap.config_en)
		set_bit(IDXD_FLAG_CONFIGURABLE, &idxd->flags);

	/* पढ़ोing group capabilities */
	idxd->hw.group_cap.bits =
		ioपढ़ो64(idxd->reg_base + IDXD_GRPCAP_OFFSET);
	dev_dbg(dev, "group_cap: %#llx\n", idxd->hw.group_cap.bits);
	idxd->max_groups = idxd->hw.group_cap.num_groups;
	dev_dbg(dev, "max groups: %u\n", idxd->max_groups);
	idxd->max_tokens = idxd->hw.group_cap.total_tokens;
	dev_dbg(dev, "max tokens: %u\n", idxd->max_tokens);
	idxd->nr_tokens = idxd->max_tokens;

	/* पढ़ो engine capabilities */
	idxd->hw.engine_cap.bits =
		ioपढ़ो64(idxd->reg_base + IDXD_ENGCAP_OFFSET);
	dev_dbg(dev, "engine_cap: %#llx\n", idxd->hw.engine_cap.bits);
	idxd->max_engines = idxd->hw.engine_cap.num_engines;
	dev_dbg(dev, "max engines: %u\n", idxd->max_engines);

	/* पढ़ो workqueue capabilities */
	idxd->hw.wq_cap.bits = ioपढ़ो64(idxd->reg_base + IDXD_WQCAP_OFFSET);
	dev_dbg(dev, "wq_cap: %#llx\n", idxd->hw.wq_cap.bits);
	idxd->max_wq_size = idxd->hw.wq_cap.total_wq_size;
	dev_dbg(dev, "total workqueue size: %u\n", idxd->max_wq_size);
	idxd->max_wqs = idxd->hw.wq_cap.num_wqs;
	dev_dbg(dev, "max workqueues: %u\n", idxd->max_wqs);
	idxd->wqcfg_size = 1 << (idxd->hw.wq_cap.wqcfg_size + IDXD_WQCFG_MIN);
	dev_dbg(dev, "wqcfg size: %u\n", idxd->wqcfg_size);

	/* पढ़ोing operation capabilities */
	क्रम (i = 0; i < 4; i++) अणु
		idxd->hw.opcap.bits[i] = ioपढ़ो64(idxd->reg_base +
				IDXD_OPCAP_OFFSET + i * माप(u64));
		dev_dbg(dev, "opcap[%d]: %#llx\n", i, idxd->hw.opcap.bits[i]);
	पूर्ण
पूर्ण

अटल काष्ठा idxd_device *idxd_alloc(काष्ठा pci_dev *pdev, काष्ठा idxd_driver_data *data)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा idxd_device *idxd;
	पूर्णांक rc;

	idxd = kzalloc_node(माप(*idxd), GFP_KERNEL, dev_to_node(dev));
	अगर (!idxd)
		वापस शून्य;

	idxd->pdev = pdev;
	idxd->data = data;
	idxd->id = ida_alloc(&idxd_ida, GFP_KERNEL);
	अगर (idxd->id < 0)
		वापस शून्य;

	device_initialize(&idxd->conf_dev);
	idxd->conf_dev.parent = dev;
	idxd->conf_dev.bus = &dsa_bus_type;
	idxd->conf_dev.type = idxd->data->dev_type;
	rc = dev_set_name(&idxd->conf_dev, "%s%d", idxd->data->name_prefix, idxd->id);
	अगर (rc < 0) अणु
		put_device(&idxd->conf_dev);
		वापस शून्य;
	पूर्ण

	spin_lock_init(&idxd->dev_lock);
	spin_lock_init(&idxd->cmd_lock);

	वापस idxd;
पूर्ण

अटल पूर्णांक idxd_enable_प्रणाली_pasid(काष्ठा idxd_device *idxd)
अणु
	पूर्णांक flags;
	अचिन्हित पूर्णांक pasid;
	काष्ठा iommu_sva *sva;

	flags = SVM_FLAG_SUPERVISOR_MODE;

	sva = iommu_sva_bind_device(&idxd->pdev->dev, शून्य, &flags);
	अगर (IS_ERR(sva)) अणु
		dev_warn(&idxd->pdev->dev,
			 "iommu sva bind failed: %ld\n", PTR_ERR(sva));
		वापस PTR_ERR(sva);
	पूर्ण

	pasid = iommu_sva_get_pasid(sva);
	अगर (pasid == IOMMU_PASID_INVALID) अणु
		iommu_sva_unbind_device(sva);
		वापस -ENODEV;
	पूर्ण

	idxd->sva = sva;
	idxd->pasid = pasid;
	dev_dbg(&idxd->pdev->dev, "system pasid: %u\n", pasid);
	वापस 0;
पूर्ण

अटल व्योम idxd_disable_प्रणाली_pasid(काष्ठा idxd_device *idxd)
अणु

	iommu_sva_unbind_device(idxd->sva);
	idxd->sva = शून्य;
पूर्ण

अटल पूर्णांक idxd_probe(काष्ठा idxd_device *idxd)
अणु
	काष्ठा pci_dev *pdev = idxd->pdev;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक rc;

	dev_dbg(dev, "%s entered and resetting device\n", __func__);
	rc = idxd_device_init_reset(idxd);
	अगर (rc < 0)
		वापस rc;

	dev_dbg(dev, "IDXD reset complete\n");

	अगर (IS_ENABLED(CONFIG_INTEL_IDXD_SVM) && sva) अणु
		rc = iommu_dev_enable_feature(dev, IOMMU_DEV_FEAT_SVA);
		अगर (rc == 0) अणु
			rc = idxd_enable_प्रणाली_pasid(idxd);
			अगर (rc < 0) अणु
				iommu_dev_disable_feature(dev, IOMMU_DEV_FEAT_SVA);
				dev_warn(dev, "Failed to enable PASID. No SVA support: %d\n", rc);
			पूर्ण अन्यथा अणु
				set_bit(IDXD_FLAG_PASID_ENABLED, &idxd->flags);
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_warn(dev, "Unable to turn on SVA feature.\n");
		पूर्ण
	पूर्ण अन्यथा अगर (!sva) अणु
		dev_warn(dev, "User forced SVA off via module param.\n");
	पूर्ण

	idxd_पढ़ो_caps(idxd);
	idxd_पढ़ो_table_offsets(idxd);

	rc = idxd_setup_पूर्णांकernals(idxd);
	अगर (rc)
		जाओ err;

	/* If the configs are पढ़ोonly, then load them from device */
	अगर (!test_bit(IDXD_FLAG_CONFIGURABLE, &idxd->flags)) अणु
		dev_dbg(dev, "Loading RO device config\n");
		rc = idxd_device_load_config(idxd);
		अगर (rc < 0)
			जाओ err_config;
	पूर्ण

	rc = idxd_setup_पूर्णांकerrupts(idxd);
	अगर (rc)
		जाओ err_config;

	dev_dbg(dev, "IDXD interrupt setup complete.\n");

	idxd->major = idxd_cdev_get_major(idxd);

	rc = perfmon_pmu_init(idxd);
	अगर (rc < 0)
		dev_warn(dev, "Failed to initialize perfmon. No PMU support: %d\n", rc);

	dev_dbg(dev, "IDXD device %d probed successfully\n", idxd->id);
	वापस 0;

 err_config:
	idxd_cleanup_पूर्णांकernals(idxd);
 err:
	अगर (device_pasid_enabled(idxd))
		idxd_disable_प्रणाली_pasid(idxd);
	iommu_dev_disable_feature(dev, IOMMU_DEV_FEAT_SVA);
	वापस rc;
पूर्ण

अटल व्योम idxd_cleanup(काष्ठा idxd_device *idxd)
अणु
	काष्ठा device *dev = &idxd->pdev->dev;

	perfmon_pmu_हटाओ(idxd);
	idxd_cleanup_पूर्णांकerrupts(idxd);
	idxd_cleanup_पूर्णांकernals(idxd);
	अगर (device_pasid_enabled(idxd))
		idxd_disable_प्रणाली_pasid(idxd);
	iommu_dev_disable_feature(dev, IOMMU_DEV_FEAT_SVA);
पूर्ण

अटल पूर्णांक idxd_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा idxd_device *idxd;
	काष्ठा idxd_driver_data *data = (काष्ठा idxd_driver_data *)id->driver_data;
	पूर्णांक rc;

	rc = pci_enable_device(pdev);
	अगर (rc)
		वापस rc;

	dev_dbg(dev, "Alloc IDXD context\n");
	idxd = idxd_alloc(pdev, data);
	अगर (!idxd) अणु
		rc = -ENOMEM;
		जाओ err_idxd_alloc;
	पूर्ण

	dev_dbg(dev, "Mapping BARs\n");
	idxd->reg_base = pci_iomap(pdev, IDXD_MMIO_BAR, 0);
	अगर (!idxd->reg_base) अणु
		rc = -ENOMEM;
		जाओ err_iomap;
	पूर्ण

	dev_dbg(dev, "Set DMA masks\n");
	rc = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (rc)
		rc = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (rc)
		जाओ err;

	rc = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (rc)
		rc = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (rc)
		जाओ err;

	dev_dbg(dev, "Set PCI master\n");
	pci_set_master(pdev);
	pci_set_drvdata(pdev, idxd);

	idxd->hw.version = ioपढ़ो32(idxd->reg_base + IDXD_VER_OFFSET);
	rc = idxd_probe(idxd);
	अगर (rc) अणु
		dev_err(dev, "Intel(R) IDXD DMA Engine init failed\n");
		जाओ err;
	पूर्ण

	rc = idxd_रेजिस्टर_devices(idxd);
	अगर (rc) अणु
		dev_err(dev, "IDXD sysfs setup failed\n");
		जाओ err_dev_रेजिस्टर;
	पूर्ण

	idxd->state = IDXD_DEV_CONF_READY;

	dev_info(&pdev->dev, "Intel(R) Accelerator Device (v%x)\n",
		 idxd->hw.version);

	वापस 0;

 err_dev_रेजिस्टर:
	idxd_cleanup(idxd);
 err:
	pci_iounmap(pdev, idxd->reg_base);
 err_iomap:
	put_device(&idxd->conf_dev);
 err_idxd_alloc:
	pci_disable_device(pdev);
	वापस rc;
पूर्ण

अटल व्योम idxd_flush_pending_llist(काष्ठा idxd_irq_entry *ie)
अणु
	काष्ठा idxd_desc *desc, *itr;
	काष्ठा llist_node *head;

	head = llist_del_all(&ie->pending_llist);
	अगर (!head)
		वापस;

	llist_क्रम_each_entry_safe(desc, itr, head, llnode) अणु
		idxd_dma_complete_txd(desc, IDXD_COMPLETE_ABORT);
		idxd_मुक्त_desc(desc->wq, desc);
	पूर्ण
पूर्ण

अटल व्योम idxd_flush_work_list(काष्ठा idxd_irq_entry *ie)
अणु
	काष्ठा idxd_desc *desc, *iter;

	list_क्रम_each_entry_safe(desc, iter, &ie->work_list, list) अणु
		list_del(&desc->list);
		idxd_dma_complete_txd(desc, IDXD_COMPLETE_ABORT);
		idxd_मुक्त_desc(desc->wq, desc);
	पूर्ण
पूर्ण

व्योम idxd_wqs_quiesce(काष्ठा idxd_device *idxd)
अणु
	काष्ठा idxd_wq *wq;
	पूर्णांक i;

	क्रम (i = 0; i < idxd->max_wqs; i++) अणु
		wq = idxd->wqs[i];
		अगर (wq->state == IDXD_WQ_ENABLED && wq->type == IDXD_WQT_KERNEL)
			idxd_wq_quiesce(wq);
	पूर्ण
पूर्ण

अटल व्योम idxd_release_पूर्णांक_handles(काष्ठा idxd_device *idxd)
अणु
	काष्ठा device *dev = &idxd->pdev->dev;
	पूर्णांक i, rc;

	क्रम (i = 0; i < idxd->num_wq_irqs; i++) अणु
		अगर (idxd->hw.cmd_cap & BIT(IDXD_CMD_RELEASE_INT_HANDLE)) अणु
			rc = idxd_device_release_पूर्णांक_handle(idxd, idxd->पूर्णांक_handles[i],
							    IDXD_IRQ_MSIX);
			अगर (rc < 0)
				dev_warn(dev, "irq handle %d release failed\n",
					 idxd->पूर्णांक_handles[i]);
			अन्यथा
				dev_dbg(dev, "int handle requested: %u\n", idxd->पूर्णांक_handles[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम idxd_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा idxd_device *idxd = pci_get_drvdata(pdev);
	पूर्णांक rc, i;
	काष्ठा idxd_irq_entry *irq_entry;
	पूर्णांक msixcnt = pci_msix_vec_count(pdev);

	rc = idxd_device_disable(idxd);
	अगर (rc)
		dev_err(&pdev->dev, "Disabling device failed\n");

	dev_dbg(&pdev->dev, "%s called\n", __func__);
	idxd_mask_msix_vectors(idxd);
	idxd_mask_error_पूर्णांकerrupts(idxd);

	क्रम (i = 0; i < msixcnt; i++) अणु
		irq_entry = &idxd->irq_entries[i];
		synchronize_irq(irq_entry->vector);
		मुक्त_irq(irq_entry->vector, irq_entry);
		अगर (i == 0)
			जारी;
		idxd_flush_pending_llist(irq_entry);
		idxd_flush_work_list(irq_entry);
	पूर्ण

	idxd_msix_perm_clear(idxd);
	idxd_release_पूर्णांक_handles(idxd);
	pci_मुक्त_irq_vectors(pdev);
	pci_iounmap(pdev, idxd->reg_base);
	pci_disable_device(pdev);
	destroy_workqueue(idxd->wq);
पूर्ण

अटल व्योम idxd_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा idxd_device *idxd = pci_get_drvdata(pdev);

	dev_dbg(&pdev->dev, "%s called\n", __func__);
	idxd_shutकरोwn(pdev);
	अगर (device_pasid_enabled(idxd))
		idxd_disable_प्रणाली_pasid(idxd);
	idxd_unरेजिस्टर_devices(idxd);
	perfmon_pmu_हटाओ(idxd);
	iommu_dev_disable_feature(&pdev->dev, IOMMU_DEV_FEAT_SVA);
पूर्ण

अटल काष्ठा pci_driver idxd_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= idxd_pci_tbl,
	.probe		= idxd_pci_probe,
	.हटाओ		= idxd_हटाओ,
	.shutकरोwn	= idxd_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init idxd_init_module(व्योम)
अणु
	पूर्णांक err;

	/*
	 * If the CPU करोes not support MOVसूची64B or ENQCMDS, there's no poपूर्णांक in
	 * क्रमागतerating the device. We can not utilize it.
	 */
	अगर (!cpu_feature_enabled(X86_FEATURE_MOVसूची64B)) अणु
		pr_warn("idxd driver failed to load without MOVDIR64B.\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!cpu_feature_enabled(X86_FEATURE_ENQCMD))
		pr_warn("Platform does not have ENQCMD(S) support.\n");
	अन्यथा
		support_enqcmd = true;

	perfmon_init();

	err = idxd_रेजिस्टर_bus_type();
	अगर (err < 0)
		वापस err;

	err = idxd_रेजिस्टर_driver();
	अगर (err < 0)
		जाओ err_idxd_driver_रेजिस्टर;

	err = idxd_cdev_रेजिस्टर();
	अगर (err)
		जाओ err_cdev_रेजिस्टर;

	err = pci_रेजिस्टर_driver(&idxd_pci_driver);
	अगर (err)
		जाओ err_pci_रेजिस्टर;

	वापस 0;

err_pci_रेजिस्टर:
	idxd_cdev_हटाओ();
err_cdev_रेजिस्टर:
	idxd_unरेजिस्टर_driver();
err_idxd_driver_रेजिस्टर:
	idxd_unरेजिस्टर_bus_type();
	वापस err;
पूर्ण
module_init(idxd_init_module);

अटल व्योम __निकास idxd_निकास_module(व्योम)
अणु
	idxd_unरेजिस्टर_driver();
	pci_unरेजिस्टर_driver(&idxd_pci_driver);
	idxd_cdev_हटाओ();
	idxd_unरेजिस्टर_bus_type();
	perfmon_निकास();
पूर्ण
module_निकास(idxd_निकास_module);
