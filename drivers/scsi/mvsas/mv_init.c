<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Marvell 88SE64xx/88SE94xx pci init
 *
 * Copyright 2007 Red Hat, Inc.
 * Copyright 2008 Marvell. <kewei@marvell.com>
 * Copyright 2009-2011 Marvell. <yuxiangl@marvell.com>
*/


#समावेश "mv_sas.h"

पूर्णांक पूर्णांकerrupt_coalescing = 0x80;

अटल काष्ठा scsi_transport_ढाँचा *mvs_stt;
अटल स्थिर काष्ठा mvs_chip_info mvs_chips[] = अणु
	[chip_6320] =	अणु 1, 2, 0x400, 17, 16, 6,  9, &mvs_64xx_dispatch, पूर्ण,
	[chip_6440] =	अणु 1, 4, 0x400, 17, 16, 6,  9, &mvs_64xx_dispatch, पूर्ण,
	[chip_6485] =	अणु 1, 8, 0x800, 33, 32, 6, 10, &mvs_64xx_dispatch, पूर्ण,
	[chip_9180] =	अणु 2, 4, 0x800, 17, 64, 8,  9, &mvs_94xx_dispatch, पूर्ण,
	[chip_9480] =	अणु 2, 4, 0x800, 17, 64, 8,  9, &mvs_94xx_dispatch, पूर्ण,
	[chip_9445] =	अणु 1, 4, 0x800, 17, 64, 8, 11, &mvs_94xx_dispatch, पूर्ण,
	[chip_9485] =	अणु 2, 4, 0x800, 17, 64, 8, 11, &mvs_94xx_dispatch, पूर्ण,
	[chip_1300] =	अणु 1, 4, 0x400, 17, 16, 6,  9, &mvs_64xx_dispatch, पूर्ण,
	[chip_1320] =	अणु 2, 4, 0x800, 17, 64, 8,  9, &mvs_94xx_dispatch, पूर्ण,
पूर्ण;

अटल काष्ठा device_attribute *mvst_host_attrs[];

#घोषणा SOC_SAS_NUM 2

अटल काष्ठा scsi_host_ढाँचा mvs_sht = अणु
	.module			= THIS_MODULE,
	.name			= DRV_NAME,
	.queuecommand		= sas_queuecommand,
	.dma_need_drain		= ata_scsi_dma_need_drain,
	.target_alloc		= sas_target_alloc,
	.slave_configure	= sas_slave_configure,
	.scan_finished		= mvs_scan_finished,
	.scan_start		= mvs_scan_start,
	.change_queue_depth	= sas_change_queue_depth,
	.bios_param		= sas_bios_param,
	.can_queue		= 1,
	.this_id		= -1,
	.sg_tablesize		= SG_ALL,
	.max_sectors		= SCSI_DEFAULT_MAX_SECTORS,
	.eh_device_reset_handler = sas_eh_device_reset_handler,
	.eh_target_reset_handler = sas_eh_target_reset_handler,
	.target_destroy		= sas_target_destroy,
	.ioctl			= sas_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl		= sas_ioctl,
#पूर्ण_अगर
	.shost_attrs		= mvst_host_attrs,
	.track_queue_depth	= 1,
पूर्ण;

अटल काष्ठा sas_करोमुख्य_function_ढाँचा mvs_transport_ops = अणु
	.lldd_dev_found 	= mvs_dev_found,
	.lldd_dev_gone		= mvs_dev_gone,
	.lldd_execute_task	= mvs_queue_command,
	.lldd_control_phy	= mvs_phy_control,

	.lldd_पात_task	= mvs_पात_task,
	.lldd_पात_task_set    = mvs_पात_task_set,
	.lldd_clear_aca         = mvs_clear_aca,
	.lldd_clear_task_set    = mvs_clear_task_set,
	.lldd_I_T_nexus_reset	= mvs_I_T_nexus_reset,
	.lldd_lu_reset 		= mvs_lu_reset,
	.lldd_query_task	= mvs_query_task,
	.lldd_port_क्रमmed	= mvs_port_क्रमmed,
	.lldd_port_deक्रमmed     = mvs_port_deक्रमmed,

	.lldd_ग_लिखो_gpio	= mvs_gpio_ग_लिखो,

पूर्ण;

अटल व्योम mvs_phy_init(काष्ठा mvs_info *mvi, पूर्णांक phy_id)
अणु
	काष्ठा mvs_phy *phy = &mvi->phy[phy_id];
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;

	phy->mvi = mvi;
	phy->port = शून्य;
	समयr_setup(&phy->समयr, शून्य, 0);
	sas_phy->enabled = (phy_id < mvi->chip->n_phy) ? 1 : 0;
	sas_phy->class = SAS;
	sas_phy->iproto = SAS_PROTOCOL_ALL;
	sas_phy->tproto = 0;
	sas_phy->type = PHY_TYPE_PHYSICAL;
	sas_phy->role = PHY_ROLE_INITIATOR;
	sas_phy->oob_mode = OOB_NOT_CONNECTED;
	sas_phy->linkrate = SAS_LINK_RATE_UNKNOWN;

	sas_phy->id = phy_id;
	sas_phy->sas_addr = &mvi->sas_addr[0];
	sas_phy->frame_rcvd = &phy->frame_rcvd[0];
	sas_phy->ha = (काष्ठा sas_ha_काष्ठा *)mvi->shost->hostdata;
	sas_phy->lldd_phy = phy;
पूर्ण

अटल व्योम mvs_मुक्त(काष्ठा mvs_info *mvi)
अणु
	काष्ठा mvs_wq *mwq;
	पूर्णांक slot_nr;

	अगर (!mvi)
		वापस;

	अगर (mvi->flags & MVF_FLAG_SOC)
		slot_nr = MVS_SOC_SLOTS;
	अन्यथा
		slot_nr = MVS_CHIP_SLOT_SZ;

	dma_pool_destroy(mvi->dma_pool);

	अगर (mvi->tx)
		dma_मुक्त_coherent(mvi->dev,
				  माप(*mvi->tx) * MVS_CHIP_SLOT_SZ,
				  mvi->tx, mvi->tx_dma);
	अगर (mvi->rx_fis)
		dma_मुक्त_coherent(mvi->dev, MVS_RX_FISL_SZ,
				  mvi->rx_fis, mvi->rx_fis_dma);
	अगर (mvi->rx)
		dma_मुक्त_coherent(mvi->dev,
				  माप(*mvi->rx) * (MVS_RX_RING_SZ + 1),
				  mvi->rx, mvi->rx_dma);
	अगर (mvi->slot)
		dma_मुक्त_coherent(mvi->dev,
				  माप(*mvi->slot) * slot_nr,
				  mvi->slot, mvi->slot_dma);

	अगर (mvi->bulk_buffer)
		dma_मुक्त_coherent(mvi->dev, TRASH_BUCKET_SIZE,
				  mvi->bulk_buffer, mvi->bulk_buffer_dma);
	अगर (mvi->bulk_buffer1)
		dma_मुक्त_coherent(mvi->dev, TRASH_BUCKET_SIZE,
				  mvi->bulk_buffer1, mvi->bulk_buffer_dma1);

	MVS_CHIP_DISP->chip_iounmap(mvi);
	अगर (mvi->shost)
		scsi_host_put(mvi->shost);
	list_क्रम_each_entry(mwq, &mvi->wq_list, entry)
		cancel_delayed_work(&mwq->work_q);
	kमुक्त(mvi->tags);
	kमुक्त(mvi);
पूर्ण

#अगर_घोषित CONFIG_SCSI_MVSAS_TASKLET
अटल व्योम mvs_tasklet(अचिन्हित दीर्घ opaque)
अणु
	u32 stat;
	u16 core_nr, i = 0;

	काष्ठा mvs_info *mvi;
	काष्ठा sas_ha_काष्ठा *sha = (काष्ठा sas_ha_काष्ठा *)opaque;

	core_nr = ((काष्ठा mvs_prv_info *)sha->lldd_ha)->n_host;
	mvi = ((काष्ठा mvs_prv_info *)sha->lldd_ha)->mvi[0];

	अगर (unlikely(!mvi))
		BUG_ON(1);

	stat = MVS_CHIP_DISP->isr_status(mvi, mvi->pdev->irq);
	अगर (!stat)
		जाओ out;

	क्रम (i = 0; i < core_nr; i++) अणु
		mvi = ((काष्ठा mvs_prv_info *)sha->lldd_ha)->mvi[i];
		MVS_CHIP_DISP->isr(mvi, mvi->pdev->irq, stat);
	पूर्ण
out:
	MVS_CHIP_DISP->पूर्णांकerrupt_enable(mvi);

पूर्ण
#पूर्ण_अगर

अटल irqवापस_t mvs_पूर्णांकerrupt(पूर्णांक irq, व्योम *opaque)
अणु
	u32 stat;
	काष्ठा mvs_info *mvi;
	काष्ठा sas_ha_काष्ठा *sha = opaque;
#अगर_अघोषित CONFIG_SCSI_MVSAS_TASKLET
	u32 i;
	u32 core_nr;

	core_nr = ((काष्ठा mvs_prv_info *)sha->lldd_ha)->n_host;
#पूर्ण_अगर

	mvi = ((काष्ठा mvs_prv_info *)sha->lldd_ha)->mvi[0];

	अगर (unlikely(!mvi))
		वापस IRQ_NONE;
#अगर_घोषित CONFIG_SCSI_MVSAS_TASKLET
	MVS_CHIP_DISP->पूर्णांकerrupt_disable(mvi);
#पूर्ण_अगर

	stat = MVS_CHIP_DISP->isr_status(mvi, irq);
	अगर (!stat) अणु
	#अगर_घोषित CONFIG_SCSI_MVSAS_TASKLET
		MVS_CHIP_DISP->पूर्णांकerrupt_enable(mvi);
	#पूर्ण_अगर
		वापस IRQ_NONE;
	पूर्ण

#अगर_घोषित CONFIG_SCSI_MVSAS_TASKLET
	tasklet_schedule(&((काष्ठा mvs_prv_info *)sha->lldd_ha)->mv_tasklet);
#अन्यथा
	क्रम (i = 0; i < core_nr; i++) अणु
		mvi = ((काष्ठा mvs_prv_info *)sha->lldd_ha)->mvi[i];
		MVS_CHIP_DISP->isr(mvi, irq, stat);
	पूर्ण
#पूर्ण_अगर
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mvs_alloc(काष्ठा mvs_info *mvi, काष्ठा Scsi_Host *shost)
अणु
	पूर्णांक i = 0, slot_nr;
	अक्षर pool_name[32];

	अगर (mvi->flags & MVF_FLAG_SOC)
		slot_nr = MVS_SOC_SLOTS;
	अन्यथा
		slot_nr = MVS_CHIP_SLOT_SZ;

	spin_lock_init(&mvi->lock);
	क्रम (i = 0; i < mvi->chip->n_phy; i++) अणु
		mvs_phy_init(mvi, i);
		mvi->port[i].wide_port_phymap = 0;
		mvi->port[i].port_attached = 0;
		INIT_LIST_HEAD(&mvi->port[i].list);
	पूर्ण
	क्रम (i = 0; i < MVS_MAX_DEVICES; i++) अणु
		mvi->devices[i].taskfileset = MVS_ID_NOT_MAPPED;
		mvi->devices[i].dev_type = SAS_PHY_UNUSED;
		mvi->devices[i].device_id = i;
		mvi->devices[i].dev_status = MVS_DEV_NORMAL;
	पूर्ण

	/*
	 * alloc and init our DMA areas
	 */
	mvi->tx = dma_alloc_coherent(mvi->dev,
				     माप(*mvi->tx) * MVS_CHIP_SLOT_SZ,
				     &mvi->tx_dma, GFP_KERNEL);
	अगर (!mvi->tx)
		जाओ err_out;
	mvi->rx_fis = dma_alloc_coherent(mvi->dev, MVS_RX_FISL_SZ,
					 &mvi->rx_fis_dma, GFP_KERNEL);
	अगर (!mvi->rx_fis)
		जाओ err_out;

	mvi->rx = dma_alloc_coherent(mvi->dev,
				     माप(*mvi->rx) * (MVS_RX_RING_SZ + 1),
				     &mvi->rx_dma, GFP_KERNEL);
	अगर (!mvi->rx)
		जाओ err_out;
	mvi->rx[0] = cpu_to_le32(0xfff);
	mvi->rx_cons = 0xfff;

	mvi->slot = dma_alloc_coherent(mvi->dev,
				       माप(*mvi->slot) * slot_nr,
				       &mvi->slot_dma, GFP_KERNEL);
	अगर (!mvi->slot)
		जाओ err_out;

	mvi->bulk_buffer = dma_alloc_coherent(mvi->dev,
				       TRASH_BUCKET_SIZE,
				       &mvi->bulk_buffer_dma, GFP_KERNEL);
	अगर (!mvi->bulk_buffer)
		जाओ err_out;

	mvi->bulk_buffer1 = dma_alloc_coherent(mvi->dev,
				       TRASH_BUCKET_SIZE,
				       &mvi->bulk_buffer_dma1, GFP_KERNEL);
	अगर (!mvi->bulk_buffer1)
		जाओ err_out;

	प्र_लिखो(pool_name, "%s%d", "mvs_dma_pool", mvi->id);
	mvi->dma_pool = dma_pool_create(pool_name, &mvi->pdev->dev,
					MVS_SLOT_BUF_SZ, 16, 0);
	अगर (!mvi->dma_pool) अणु
			prपूर्णांकk(KERN_DEBUG "failed to create dma pool %s.\n", pool_name);
			जाओ err_out;
	पूर्ण
	mvi->tags_num = slot_nr;

	/* Initialize tags */
	mvs_tag_init(mvi);
	वापस 0;
err_out:
	वापस 1;
पूर्ण


पूर्णांक mvs_ioremap(काष्ठा mvs_info *mvi, पूर्णांक bar, पूर्णांक bar_ex)
अणु
	अचिन्हित दीर्घ res_start, res_len, res_flag_ex = 0;
	काष्ठा pci_dev *pdev = mvi->pdev;
	अगर (bar_ex != -1) अणु
		/*
		 * ioremap मुख्य and peripheral रेजिस्टरs
		 */
		res_start = pci_resource_start(pdev, bar_ex);
		res_len = pci_resource_len(pdev, bar_ex);
		अगर (!res_start || !res_len)
			जाओ err_out;

		res_flag_ex = pci_resource_flags(pdev, bar_ex);
		अगर (res_flag_ex & IORESOURCE_MEM)
			mvi->regs_ex = ioremap(res_start, res_len);
		अन्यथा
			mvi->regs_ex = (व्योम *)res_start;
		अगर (!mvi->regs_ex)
			जाओ err_out;
	पूर्ण

	res_start = pci_resource_start(pdev, bar);
	res_len = pci_resource_len(pdev, bar);
	अगर (!res_start || !res_len) अणु
		iounmap(mvi->regs_ex);
		mvi->regs_ex = शून्य;
		जाओ err_out;
	पूर्ण

	mvi->regs = ioremap(res_start, res_len);

	अगर (!mvi->regs) अणु
		अगर (mvi->regs_ex && (res_flag_ex & IORESOURCE_MEM))
			iounmap(mvi->regs_ex);
		mvi->regs_ex = शून्य;
		जाओ err_out;
	पूर्ण

	वापस 0;
err_out:
	वापस -1;
पूर्ण

व्योम mvs_iounmap(व्योम __iomem *regs)
अणु
	iounmap(regs);
पूर्ण

अटल काष्ठा mvs_info *mvs_pci_alloc(काष्ठा pci_dev *pdev,
				स्थिर काष्ठा pci_device_id *ent,
				काष्ठा Scsi_Host *shost, अचिन्हित पूर्णांक id)
अणु
	काष्ठा mvs_info *mvi = शून्य;
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);

	mvi = kzalloc(माप(*mvi) +
		(1L << mvs_chips[ent->driver_data].slot_width) *
		माप(काष्ठा mvs_slot_info), GFP_KERNEL);
	अगर (!mvi)
		वापस शून्य;

	mvi->pdev = pdev;
	mvi->dev = &pdev->dev;
	mvi->chip_id = ent->driver_data;
	mvi->chip = &mvs_chips[mvi->chip_id];
	INIT_LIST_HEAD(&mvi->wq_list);

	((काष्ठा mvs_prv_info *)sha->lldd_ha)->mvi[id] = mvi;
	((काष्ठा mvs_prv_info *)sha->lldd_ha)->n_phy = mvi->chip->n_phy;

	mvi->id = id;
	mvi->sas = sha;
	mvi->shost = shost;

	mvi->tags = kzalloc(MVS_CHIP_SLOT_SZ>>3, GFP_KERNEL);
	अगर (!mvi->tags)
		जाओ err_out;

	अगर (MVS_CHIP_DISP->chip_ioremap(mvi))
		जाओ err_out;
	अगर (!mvs_alloc(mvi, shost))
		वापस mvi;
err_out:
	mvs_मुक्त(mvi);
	वापस शून्य;
पूर्ण

अटल पूर्णांक pci_go_64(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक rc;

	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (rc) अणु
		rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (rc) अणु
			dev_prपूर्णांकk(KERN_ERR, &pdev->dev,
				   "32-bit DMA enable failed\n");
			वापस rc;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक mvs_prep_sas_ha_init(काष्ठा Scsi_Host *shost,
				स्थिर काष्ठा mvs_chip_info *chip_info)
अणु
	पूर्णांक phy_nr, port_nr; अचिन्हित लघु core_nr;
	काष्ठा asd_sas_phy **arr_phy;
	काष्ठा asd_sas_port **arr_port;
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);

	core_nr = chip_info->n_host;
	phy_nr  = core_nr * chip_info->n_phy;
	port_nr = phy_nr;

	स_रखो(sha, 0x00, माप(काष्ठा sas_ha_काष्ठा));
	arr_phy  = kसुस्मृति(phy_nr, माप(व्योम *), GFP_KERNEL);
	arr_port = kसुस्मृति(port_nr, माप(व्योम *), GFP_KERNEL);
	अगर (!arr_phy || !arr_port)
		जाओ निकास_मुक्त;

	sha->sas_phy = arr_phy;
	sha->sas_port = arr_port;
	sha->core.shost = shost;

	sha->lldd_ha = kzalloc(माप(काष्ठा mvs_prv_info), GFP_KERNEL);
	अगर (!sha->lldd_ha)
		जाओ निकास_मुक्त;

	((काष्ठा mvs_prv_info *)sha->lldd_ha)->n_host = core_nr;

	shost->transportt = mvs_stt;
	shost->max_id = MVS_MAX_DEVICES;
	shost->max_lun = ~0;
	shost->max_channel = 1;
	shost->max_cmd_len = 16;

	वापस 0;
निकास_मुक्त:
	kमुक्त(arr_phy);
	kमुक्त(arr_port);
	वापस -1;

पूर्ण

अटल व्योम  mvs_post_sas_ha_init(काष्ठा Scsi_Host *shost,
			स्थिर काष्ठा mvs_chip_info *chip_info)
अणु
	पूर्णांक can_queue, i = 0, j = 0;
	काष्ठा mvs_info *mvi = शून्य;
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	अचिन्हित लघु nr_core = ((काष्ठा mvs_prv_info *)sha->lldd_ha)->n_host;

	क्रम (j = 0; j < nr_core; j++) अणु
		mvi = ((काष्ठा mvs_prv_info *)sha->lldd_ha)->mvi[j];
		क्रम (i = 0; i < chip_info->n_phy; i++) अणु
			sha->sas_phy[j * chip_info->n_phy  + i] =
				&mvi->phy[i].sas_phy;
			sha->sas_port[j * chip_info->n_phy + i] =
				&mvi->port[i].sas_port;
		पूर्ण
	पूर्ण

	sha->sas_ha_name = DRV_NAME;
	sha->dev = mvi->dev;
	sha->lldd_module = THIS_MODULE;
	sha->sas_addr = &mvi->sas_addr[0];

	sha->num_phys = nr_core * chip_info->n_phy;

	अगर (mvi->flags & MVF_FLAG_SOC)
		can_queue = MVS_SOC_CAN_QUEUE;
	अन्यथा
		can_queue = MVS_CHIP_SLOT_SZ;

	shost->sg_tablesize = min_t(u16, SG_ALL, MVS_MAX_SG);
	shost->can_queue = can_queue;
	mvi->shost->cmd_per_lun = MVS_QUEUE_SIZE;
	sha->core.shost = mvi->shost;
पूर्ण

अटल व्योम mvs_init_sas_add(काष्ठा mvs_info *mvi)
अणु
	u8 i;
	क्रम (i = 0; i < mvi->chip->n_phy; i++) अणु
		mvi->phy[i].dev_sas_addr = 0x5005043011ab0000ULL;
		mvi->phy[i].dev_sas_addr =
			cpu_to_be64((u64)(*(u64 *)&mvi->phy[i].dev_sas_addr));
	पूर्ण

	स_नकल(mvi->sas_addr, &mvi->phy[0].dev_sas_addr, SAS_ADDR_SIZE);
पूर्ण

अटल पूर्णांक mvs_pci_init(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अचिन्हित पूर्णांक rc, nhost = 0;
	काष्ठा mvs_info *mvi;
	काष्ठा mvs_prv_info *mpi;
	irq_handler_t irq_handler = mvs_पूर्णांकerrupt;
	काष्ठा Scsi_Host *shost = शून्य;
	स्थिर काष्ठा mvs_chip_info *chip;

	dev_prपूर्णांकk(KERN_INFO, &pdev->dev,
		"mvsas: driver version %s\n", DRV_VERSION);
	rc = pci_enable_device(pdev);
	अगर (rc)
		जाओ err_out_enable;

	pci_set_master(pdev);

	rc = pci_request_regions(pdev, DRV_NAME);
	अगर (rc)
		जाओ err_out_disable;

	rc = pci_go_64(pdev);
	अगर (rc)
		जाओ err_out_regions;

	shost = scsi_host_alloc(&mvs_sht, माप(व्योम *));
	अगर (!shost) अणु
		rc = -ENOMEM;
		जाओ err_out_regions;
	पूर्ण

	chip = &mvs_chips[ent->driver_data];
	SHOST_TO_SAS_HA(shost) =
		kसुस्मृति(1, माप(काष्ठा sas_ha_काष्ठा), GFP_KERNEL);
	अगर (!SHOST_TO_SAS_HA(shost)) अणु
		scsi_host_put(shost);
		rc = -ENOMEM;
		जाओ err_out_regions;
	पूर्ण

	rc = mvs_prep_sas_ha_init(shost, chip);
	अगर (rc) अणु
		scsi_host_put(shost);
		rc = -ENOMEM;
		जाओ err_out_regions;
	पूर्ण

	pci_set_drvdata(pdev, SHOST_TO_SAS_HA(shost));

	करो अणु
		mvi = mvs_pci_alloc(pdev, ent, shost, nhost);
		अगर (!mvi) अणु
			rc = -ENOMEM;
			जाओ err_out_regions;
		पूर्ण

		स_रखो(&mvi->hba_info_param, 0xFF,
			माप(काष्ठा hba_info_page));

		mvs_init_sas_add(mvi);

		mvi->instance = nhost;
		rc = MVS_CHIP_DISP->chip_init(mvi);
		अगर (rc) अणु
			mvs_मुक्त(mvi);
			जाओ err_out_regions;
		पूर्ण
		nhost++;
	पूर्ण जबतक (nhost < chip->n_host);
	mpi = (काष्ठा mvs_prv_info *)(SHOST_TO_SAS_HA(shost)->lldd_ha);
#अगर_घोषित CONFIG_SCSI_MVSAS_TASKLET
	tasklet_init(&(mpi->mv_tasklet), mvs_tasklet,
		     (अचिन्हित दीर्घ)SHOST_TO_SAS_HA(shost));
#पूर्ण_अगर

	mvs_post_sas_ha_init(shost, chip);

	rc = scsi_add_host(shost, &pdev->dev);
	अगर (rc)
		जाओ err_out_shost;

	rc = sas_रेजिस्टर_ha(SHOST_TO_SAS_HA(shost));
	अगर (rc)
		जाओ err_out_shost;
	rc = request_irq(pdev->irq, irq_handler, IRQF_SHARED,
		DRV_NAME, SHOST_TO_SAS_HA(shost));
	अगर (rc)
		जाओ err_not_sas;

	MVS_CHIP_DISP->पूर्णांकerrupt_enable(mvi);

	scsi_scan_host(mvi->shost);

	वापस 0;

err_not_sas:
	sas_unरेजिस्टर_ha(SHOST_TO_SAS_HA(shost));
err_out_shost:
	scsi_हटाओ_host(mvi->shost);
err_out_regions:
	pci_release_regions(pdev);
err_out_disable:
	pci_disable_device(pdev);
err_out_enable:
	वापस rc;
पूर्ण

अटल व्योम mvs_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित लघु core_nr, i = 0;
	काष्ठा sas_ha_काष्ठा *sha = pci_get_drvdata(pdev);
	काष्ठा mvs_info *mvi = शून्य;

	core_nr = ((काष्ठा mvs_prv_info *)sha->lldd_ha)->n_host;
	mvi = ((काष्ठा mvs_prv_info *)sha->lldd_ha)->mvi[0];

#अगर_घोषित CONFIG_SCSI_MVSAS_TASKLET
	tasklet_समाप्त(&((काष्ठा mvs_prv_info *)sha->lldd_ha)->mv_tasklet);
#पूर्ण_अगर

	sas_unरेजिस्टर_ha(sha);
	sas_हटाओ_host(mvi->shost);

	MVS_CHIP_DISP->पूर्णांकerrupt_disable(mvi);
	मुक्त_irq(mvi->pdev->irq, sha);
	क्रम (i = 0; i < core_nr; i++) अणु
		mvi = ((काष्ठा mvs_prv_info *)sha->lldd_ha)->mvi[i];
		mvs_मुक्त(mvi);
	पूर्ण
	kमुक्त(sha->sas_phy);
	kमुक्त(sha->sas_port);
	kमुक्त(sha);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	वापस;
पूर्ण

अटल काष्ठा pci_device_id mvs_pci_table[] = अणु
	अणु PCI_VDEVICE(MARVELL, 0x6320), chip_6320 पूर्ण,
	अणु PCI_VDEVICE(MARVELL, 0x6340), chip_6440 पूर्ण,
	अणु
		.venकरोr 	= PCI_VENDOR_ID_MARVELL,
		.device 	= 0x6440,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= 0x6480,
		.class		= 0,
		.class_mask	= 0,
		.driver_data	= chip_6485,
	पूर्ण,
	अणु PCI_VDEVICE(MARVELL, 0x6440), chip_6440 पूर्ण,
	अणु PCI_VDEVICE(MARVELL, 0x6485), chip_6485 पूर्ण,
	अणु PCI_VDEVICE(MARVELL, 0x9480), chip_9480 पूर्ण,
	अणु PCI_VDEVICE(MARVELL, 0x9180), chip_9180 पूर्ण,
	अणु PCI_VDEVICE(ARECA, PCI_DEVICE_ID_ARECA_1300), chip_1300 पूर्ण,
	अणु PCI_VDEVICE(ARECA, PCI_DEVICE_ID_ARECA_1320), chip_1320 पूर्ण,
	अणु PCI_VDEVICE(ADAPTEC2, 0x0450), chip_6440 पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x2710), chip_9480 पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x2720), chip_9480 पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x2721), chip_9480 पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x2722), chip_9480 पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x2740), chip_9480 पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x2744), chip_9480 पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x2760), chip_9480 पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_MARVELL_EXT,
		.device		= 0x9480,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= 0x9480,
		.class		= 0,
		.class_mask	= 0,
		.driver_data	= chip_9480,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_MARVELL_EXT,
		.device		= 0x9445,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= 0x9480,
		.class		= 0,
		.class_mask	= 0,
		.driver_data	= chip_9445,
	पूर्ण,
	अणु PCI_VDEVICE(MARVELL_EXT, 0x9485), chip_9485 पूर्ण, /* Marvell 9480/9485 (any venकरोr/model) */
	अणु PCI_VDEVICE(OCZ, 0x1021), chip_9485पूर्ण, /* OCZ RevoDrive3 */
	अणु PCI_VDEVICE(OCZ, 0x1022), chip_9485पूर्ण, /* OCZ RevoDrive3/zDriveR4 (exact model unknown) */
	अणु PCI_VDEVICE(OCZ, 0x1040), chip_9485पूर्ण, /* OCZ RevoDrive3/zDriveR4 (exact model unknown) */
	अणु PCI_VDEVICE(OCZ, 0x1041), chip_9485पूर्ण, /* OCZ RevoDrive3/zDriveR4 (exact model unknown) */
	अणु PCI_VDEVICE(OCZ, 0x1042), chip_9485पूर्ण, /* OCZ RevoDrive3/zDriveR4 (exact model unknown) */
	अणु PCI_VDEVICE(OCZ, 0x1043), chip_9485पूर्ण, /* OCZ RevoDrive3/zDriveR4 (exact model unknown) */
	अणु PCI_VDEVICE(OCZ, 0x1044), chip_9485पूर्ण, /* OCZ RevoDrive3/zDriveR4 (exact model unknown) */
	अणु PCI_VDEVICE(OCZ, 0x1080), chip_9485पूर्ण, /* OCZ RevoDrive3/zDriveR4 (exact model unknown) */
	अणु PCI_VDEVICE(OCZ, 0x1083), chip_9485पूर्ण, /* OCZ RevoDrive3/zDriveR4 (exact model unknown) */
	अणु PCI_VDEVICE(OCZ, 0x1084), chip_9485पूर्ण, /* OCZ RevoDrive3/zDriveR4 (exact model unknown) */

	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा pci_driver mvs_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= mvs_pci_table,
	.probe		= mvs_pci_init,
	.हटाओ		= mvs_pci_हटाओ,
पूर्ण;

अटल sमाप_प्रकार
mvs_show_driver_version(काष्ठा device *cdev,
		काष्ठा device_attribute *attr,  अक्षर *buffer)
अणु
	वापस snम_लिखो(buffer, PAGE_SIZE, "%s\n", DRV_VERSION);
पूर्ण

अटल DEVICE_ATTR(driver_version,
			 S_IRUGO,
			 mvs_show_driver_version,
			 शून्य);

अटल sमाप_प्रकार
mvs_store_पूर्णांकerrupt_coalescing(काष्ठा device *cdev,
			काष्ठा device_attribute *attr,
			स्थिर अक्षर *buffer, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक val = 0;
	काष्ठा mvs_info *mvi = शून्य;
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	u8 i, core_nr;
	अगर (buffer == शून्य)
		वापस size;

	अगर (माला_पूछो(buffer, "%u", &val) != 1)
		वापस -EINVAL;

	अगर (val >= 0x10000) अणु
		mv_dprपूर्णांकk("interrupt coalescing timer %d us is"
			"too long\n", val);
		वापस म_माप(buffer);
	पूर्ण

	पूर्णांकerrupt_coalescing = val;

	core_nr = ((काष्ठा mvs_prv_info *)sha->lldd_ha)->n_host;
	mvi = ((काष्ठा mvs_prv_info *)sha->lldd_ha)->mvi[0];

	अगर (unlikely(!mvi))
		वापस -EINVAL;

	क्रम (i = 0; i < core_nr; i++) अणु
		mvi = ((काष्ठा mvs_prv_info *)sha->lldd_ha)->mvi[i];
		अगर (MVS_CHIP_DISP->tune_पूर्णांकerrupt)
			MVS_CHIP_DISP->tune_पूर्णांकerrupt(mvi,
				पूर्णांकerrupt_coalescing);
	पूर्ण
	mv_dprपूर्णांकk("set interrupt coalescing time to %d us\n",
		पूर्णांकerrupt_coalescing);
	वापस म_माप(buffer);
पूर्ण

अटल sमाप_प्रकार mvs_show_पूर्णांकerrupt_coalescing(काष्ठा device *cdev,
			काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	वापस snम_लिखो(buffer, PAGE_SIZE, "%d\n", पूर्णांकerrupt_coalescing);
पूर्ण

अटल DEVICE_ATTR(पूर्णांकerrupt_coalescing,
			 S_IRUGO|S_IWUSR,
			 mvs_show_पूर्णांकerrupt_coalescing,
			 mvs_store_पूर्णांकerrupt_coalescing);

अटल पूर्णांक __init mvs_init(व्योम)
अणु
	पूर्णांक rc;
	mvs_stt = sas_करोमुख्य_attach_transport(&mvs_transport_ops);
	अगर (!mvs_stt)
		वापस -ENOMEM;

	rc = pci_रेजिस्टर_driver(&mvs_pci_driver);
	अगर (rc)
		जाओ err_out;

	वापस 0;

err_out:
	sas_release_transport(mvs_stt);
	वापस rc;
पूर्ण

अटल व्योम __निकास mvs_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&mvs_pci_driver);
	sas_release_transport(mvs_stt);
पूर्ण

अटल काष्ठा device_attribute *mvst_host_attrs[] = अणु
	&dev_attr_driver_version,
	&dev_attr_पूर्णांकerrupt_coalescing,
	शून्य,
पूर्ण;

module_init(mvs_init);
module_निकास(mvs_निकास);

MODULE_AUTHOR("Jeff Garzik <jgarzik@pobox.com>");
MODULE_DESCRIPTION("Marvell 88SE6440 SAS/SATA controller driver");
MODULE_VERSION(DRV_VERSION);
MODULE_LICENSE("GPL");
#अगर_घोषित CONFIG_PCI
MODULE_DEVICE_TABLE(pci, mvs_pci_table);
#पूर्ण_अगर
