<शैली गुरु>
/*
 * PMC-Sierra PM8001/8081/8088/8089 SAS/SATA based host adapters driver
 *
 * Copyright (c) 2008-2009 USI Co., Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement क्रम further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 */

#समावेश <linux/slab.h>
#समावेश "pm8001_sas.h"
#समावेश "pm8001_chips.h"
#समावेश "pm80xx_hwi.h"

अटल uदीर्घ logging_level = PM8001_FAIL_LOGGING | PM8001_IOERR_LOGGING;
module_param(logging_level, uदीर्घ, 0644);
MODULE_PARM_DESC(logging_level, " bits for enabling logging info.");

अटल uदीर्घ link_rate = LINKRATE_15 | LINKRATE_30 | LINKRATE_60 | LINKRATE_120;
module_param(link_rate, uदीर्घ, 0644);
MODULE_PARM_DESC(link_rate, "Enable link rate.\n"
		" 1: Link rate 1.5G\n"
		" 2: Link rate 3.0G\n"
		" 4: Link rate 6.0G\n"
		" 8: Link rate 12.0G\n");

अटल काष्ठा scsi_transport_ढाँचा *pm8001_stt;
अटल पूर्णांक pm8001_init_ccb_tag(काष्ठा pm8001_hba_info *, काष्ठा Scsi_Host *, काष्ठा pci_dev *);

/*
 * chip info काष्ठाure to identअगरy chip key functionality as
 * encryption available/not, no of ports, hw specअगरic function ref
 */
अटल स्थिर काष्ठा pm8001_chip_info pm8001_chips[] = अणु
	[chip_8001] = अणु0,  8, &pm8001_8001_dispatch,पूर्ण,
	[chip_8008] = अणु0,  8, &pm8001_80xx_dispatch,पूर्ण,
	[chip_8009] = अणु1,  8, &pm8001_80xx_dispatch,पूर्ण,
	[chip_8018] = अणु0,  16, &pm8001_80xx_dispatch,पूर्ण,
	[chip_8019] = अणु1,  16, &pm8001_80xx_dispatch,पूर्ण,
	[chip_8074] = अणु0,  8, &pm8001_80xx_dispatch,पूर्ण,
	[chip_8076] = अणु0,  16, &pm8001_80xx_dispatch,पूर्ण,
	[chip_8077] = अणु0,  16, &pm8001_80xx_dispatch,पूर्ण,
	[chip_8006] = अणु0,  16, &pm8001_80xx_dispatch,पूर्ण,
	[chip_8070] = अणु0,  8, &pm8001_80xx_dispatch,पूर्ण,
	[chip_8072] = अणु0,  16, &pm8001_80xx_dispatch,पूर्ण,
पूर्ण;
अटल पूर्णांक pm8001_id;

LIST_HEAD(hba_list);

काष्ठा workqueue_काष्ठा *pm8001_wq;

/*
 * The मुख्य काष्ठाure which LLDD must रेजिस्टर क्रम scsi core.
 */
अटल काष्ठा scsi_host_ढाँचा pm8001_sht = अणु
	.module			= THIS_MODULE,
	.name			= DRV_NAME,
	.queuecommand		= sas_queuecommand,
	.dma_need_drain		= ata_scsi_dma_need_drain,
	.target_alloc		= sas_target_alloc,
	.slave_configure	= sas_slave_configure,
	.scan_finished		= pm8001_scan_finished,
	.scan_start		= pm8001_scan_start,
	.change_queue_depth	= sas_change_queue_depth,
	.bios_param		= sas_bios_param,
	.can_queue		= 1,
	.this_id		= -1,
	.sg_tablesize		= PM8001_MAX_DMA_SG,
	.max_sectors		= SCSI_DEFAULT_MAX_SECTORS,
	.eh_device_reset_handler = sas_eh_device_reset_handler,
	.eh_target_reset_handler = sas_eh_target_reset_handler,
	.target_destroy		= sas_target_destroy,
	.ioctl			= sas_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl		= sas_ioctl,
#पूर्ण_अगर
	.shost_attrs		= pm8001_host_attrs,
	.track_queue_depth	= 1,
पूर्ण;

/*
 * Sas layer call this function to execute specअगरic task.
 */
अटल काष्ठा sas_करोमुख्य_function_ढाँचा pm8001_transport_ops = अणु
	.lldd_dev_found		= pm8001_dev_found,
	.lldd_dev_gone		= pm8001_dev_gone,

	.lldd_execute_task	= pm8001_queue_command,
	.lldd_control_phy	= pm8001_phy_control,

	.lldd_पात_task	= pm8001_पात_task,
	.lldd_पात_task_set	= pm8001_पात_task_set,
	.lldd_clear_aca		= pm8001_clear_aca,
	.lldd_clear_task_set	= pm8001_clear_task_set,
	.lldd_I_T_nexus_reset   = pm8001_I_T_nexus_reset,
	.lldd_lu_reset		= pm8001_lu_reset,
	.lldd_query_task	= pm8001_query_task,
पूर्ण;

/**
 * pm8001_phy_init - initiate our adapter phys
 * @pm8001_ha: our hba काष्ठाure.
 * @phy_id: phy id.
 */
अटल व्योम pm8001_phy_init(काष्ठा pm8001_hba_info *pm8001_ha, पूर्णांक phy_id)
अणु
	काष्ठा pm8001_phy *phy = &pm8001_ha->phy[phy_id];
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
	phy->phy_state = PHY_LINK_DISABLE;
	phy->pm8001_ha = pm8001_ha;
	sas_phy->enabled = (phy_id < pm8001_ha->chip->n_phy) ? 1 : 0;
	sas_phy->class = SAS;
	sas_phy->iproto = SAS_PROTOCOL_ALL;
	sas_phy->tproto = 0;
	sas_phy->type = PHY_TYPE_PHYSICAL;
	sas_phy->role = PHY_ROLE_INITIATOR;
	sas_phy->oob_mode = OOB_NOT_CONNECTED;
	sas_phy->linkrate = SAS_LINK_RATE_UNKNOWN;
	sas_phy->id = phy_id;
	sas_phy->sas_addr = (u8 *)&phy->dev_sas_addr;
	sas_phy->frame_rcvd = &phy->frame_rcvd[0];
	sas_phy->ha = (काष्ठा sas_ha_काष्ठा *)pm8001_ha->shost->hostdata;
	sas_phy->lldd_phy = phy;
पूर्ण

/**
 * pm8001_मुक्त - मुक्त hba
 * @pm8001_ha:	our hba काष्ठाure.
 */
अटल व्योम pm8001_मुक्त(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	पूर्णांक i;

	अगर (!pm8001_ha)
		वापस;

	क्रम (i = 0; i < USI_MAX_MEMCNT; i++) अणु
		अगर (pm8001_ha->memoryMap.region[i].virt_ptr != शून्य) अणु
			dma_मुक्त_coherent(&pm8001_ha->pdev->dev,
				(pm8001_ha->memoryMap.region[i].total_len +
				pm8001_ha->memoryMap.region[i].alignment),
				pm8001_ha->memoryMap.region[i].virt_ptr,
				pm8001_ha->memoryMap.region[i].phys_addr);
			पूर्ण
	पूर्ण
	PM8001_CHIP_DISP->chip_iounmap(pm8001_ha);
	flush_workqueue(pm8001_wq);
	kमुक्त(pm8001_ha->tags);
	kमुक्त(pm8001_ha);
पूर्ण

#अगर_घोषित PM8001_USE_TASKLET

/**
 * pm8001_tasklet() - tasklet क्रम 64 msi-x पूर्णांकerrupt handler
 * @opaque: the passed general host adapter काष्ठा
 * Note: pm8001_tasklet is common क्रम pm8001 & pm80xx
 */
अटल व्योम pm8001_tasklet(अचिन्हित दीर्घ opaque)
अणु
	काष्ठा pm8001_hba_info *pm8001_ha;
	काष्ठा isr_param *irq_vector;

	irq_vector = (काष्ठा isr_param *)opaque;
	pm8001_ha = irq_vector->drv_inst;
	अगर (unlikely(!pm8001_ha))
		BUG_ON(1);
	PM8001_CHIP_DISP->isr(pm8001_ha, irq_vector->irq_id);
पूर्ण
#पूर्ण_अगर

/**
 * pm8001_पूर्णांकerrupt_handler_msix - मुख्य MSIX पूर्णांकerrupt handler.
 * It obtains the vector number and calls the equivalent bottom
 * half or services directly.
 * @irq: पूर्णांकerrupt number
 * @opaque: the passed outbound queue/vector. Host काष्ठाure is
 * retrieved from the same.
 */
अटल irqवापस_t pm8001_पूर्णांकerrupt_handler_msix(पूर्णांक irq, व्योम *opaque)
अणु
	काष्ठा isr_param *irq_vector;
	काष्ठा pm8001_hba_info *pm8001_ha;
	irqवापस_t ret = IRQ_HANDLED;
	irq_vector = (काष्ठा isr_param *)opaque;
	pm8001_ha = irq_vector->drv_inst;

	अगर (unlikely(!pm8001_ha))
		वापस IRQ_NONE;
	अगर (!PM8001_CHIP_DISP->is_our_पूर्णांकerrupt(pm8001_ha))
		वापस IRQ_NONE;
#अगर_घोषित PM8001_USE_TASKLET
	tasklet_schedule(&pm8001_ha->tasklet[irq_vector->irq_id]);
#अन्यथा
	ret = PM8001_CHIP_DISP->isr(pm8001_ha, irq_vector->irq_id);
#पूर्ण_अगर
	वापस ret;
पूर्ण

/**
 * pm8001_पूर्णांकerrupt_handler_पूर्णांकx - मुख्य INTx पूर्णांकerrupt handler.
 * @irq: पूर्णांकerrupt number
 * @dev_id: sas_ha काष्ठाure. The HBA is retrieved from sas_has काष्ठाure.
 */

अटल irqवापस_t pm8001_पूर्णांकerrupt_handler_पूर्णांकx(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pm8001_hba_info *pm8001_ha;
	irqवापस_t ret = IRQ_HANDLED;
	काष्ठा sas_ha_काष्ठा *sha = dev_id;
	pm8001_ha = sha->lldd_ha;
	अगर (unlikely(!pm8001_ha))
		वापस IRQ_NONE;
	अगर (!PM8001_CHIP_DISP->is_our_पूर्णांकerrupt(pm8001_ha))
		वापस IRQ_NONE;

#अगर_घोषित PM8001_USE_TASKLET
	tasklet_schedule(&pm8001_ha->tasklet[0]);
#अन्यथा
	ret = PM8001_CHIP_DISP->isr(pm8001_ha, 0);
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल u32 pm8001_setup_irq(काष्ठा pm8001_hba_info *pm8001_ha);
अटल u32 pm8001_request_irq(काष्ठा pm8001_hba_info *pm8001_ha);

/**
 * pm8001_alloc - initiate our hba काष्ठाure and 6 DMAs area.
 * @pm8001_ha: our hba काष्ठाure.
 * @ent: PCI device ID काष्ठाure to match on
 */
अटल पूर्णांक pm8001_alloc(काष्ठा pm8001_hba_info *pm8001_ha,
			स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक i, count = 0, rc = 0;
	u32 ci_offset, ib_offset, ob_offset, pi_offset;
	काष्ठा inbound_queue_table *ibq;
	काष्ठा outbound_queue_table *obq;

	spin_lock_init(&pm8001_ha->lock);
	spin_lock_init(&pm8001_ha->biपंचांगap_lock);
	pm8001_dbg(pm8001_ha, INIT, "pm8001_alloc: PHY:%x\n",
		   pm8001_ha->chip->n_phy);

	/* Setup Interrupt */
	rc = pm8001_setup_irq(pm8001_ha);
	अगर (rc) अणु
		pm8001_dbg(pm8001_ha, FAIL,
			   "pm8001_setup_irq failed [ret: %d]\n", rc);
		जाओ err_out_shost;
	पूर्ण
	/* Request Interrupt */
	rc = pm8001_request_irq(pm8001_ha);
	अगर (rc)
		जाओ err_out_shost;

	count = pm8001_ha->max_q_num;
	/* Queues are chosen based on the number of cores/msix availability */
	ib_offset = pm8001_ha->ib_offset  = USI_MAX_MEMCNT_BASE;
	ci_offset = pm8001_ha->ci_offset  = ib_offset + count;
	ob_offset = pm8001_ha->ob_offset  = ci_offset + count;
	pi_offset = pm8001_ha->pi_offset  = ob_offset + count;
	pm8001_ha->max_memcnt = pi_offset + count;

	क्रम (i = 0; i < pm8001_ha->chip->n_phy; i++) अणु
		pm8001_phy_init(pm8001_ha, i);
		pm8001_ha->port[i].wide_port_phymap = 0;
		pm8001_ha->port[i].port_attached = 0;
		pm8001_ha->port[i].port_state = 0;
		INIT_LIST_HEAD(&pm8001_ha->port[i].list);
	पूर्ण

	/* MPI Memory region 1 क्रम AAP Event Log क्रम fw */
	pm8001_ha->memoryMap.region[AAP1].num_elements = 1;
	pm8001_ha->memoryMap.region[AAP1].element_size = PM8001_EVENT_LOG_SIZE;
	pm8001_ha->memoryMap.region[AAP1].total_len = PM8001_EVENT_LOG_SIZE;
	pm8001_ha->memoryMap.region[AAP1].alignment = 32;

	/* MPI Memory region 2 क्रम IOP Event Log क्रम fw */
	pm8001_ha->memoryMap.region[IOP].num_elements = 1;
	pm8001_ha->memoryMap.region[IOP].element_size = PM8001_EVENT_LOG_SIZE;
	pm8001_ha->memoryMap.region[IOP].total_len = PM8001_EVENT_LOG_SIZE;
	pm8001_ha->memoryMap.region[IOP].alignment = 32;

	क्रम (i = 0; i < count; i++) अणु
		ibq = &pm8001_ha->inbnd_q_tbl[i];
		spin_lock_init(&ibq->iq_lock);
		/* MPI Memory region 3 क्रम consumer Index of inbound queues */
		pm8001_ha->memoryMap.region[ci_offset+i].num_elements = 1;
		pm8001_ha->memoryMap.region[ci_offset+i].element_size = 4;
		pm8001_ha->memoryMap.region[ci_offset+i].total_len = 4;
		pm8001_ha->memoryMap.region[ci_offset+i].alignment = 4;

		अगर ((ent->driver_data) != chip_8001) अणु
			/* MPI Memory region 5 inbound queues */
			pm8001_ha->memoryMap.region[ib_offset+i].num_elements =
						PM8001_MPI_QUEUE;
			pm8001_ha->memoryMap.region[ib_offset+i].element_size
								= 128;
			pm8001_ha->memoryMap.region[ib_offset+i].total_len =
						PM8001_MPI_QUEUE * 128;
			pm8001_ha->memoryMap.region[ib_offset+i].alignment
								= 128;
		पूर्ण अन्यथा अणु
			pm8001_ha->memoryMap.region[ib_offset+i].num_elements =
						PM8001_MPI_QUEUE;
			pm8001_ha->memoryMap.region[ib_offset+i].element_size
								= 64;
			pm8001_ha->memoryMap.region[ib_offset+i].total_len =
						PM8001_MPI_QUEUE * 64;
			pm8001_ha->memoryMap.region[ib_offset+i].alignment = 64;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		obq = &pm8001_ha->outbnd_q_tbl[i];
		spin_lock_init(&obq->oq_lock);
		/* MPI Memory region 4 क्रम producer Index of outbound queues */
		pm8001_ha->memoryMap.region[pi_offset+i].num_elements = 1;
		pm8001_ha->memoryMap.region[pi_offset+i].element_size = 4;
		pm8001_ha->memoryMap.region[pi_offset+i].total_len = 4;
		pm8001_ha->memoryMap.region[pi_offset+i].alignment = 4;

		अगर (ent->driver_data != chip_8001) अणु
			/* MPI Memory region 6 Outbound queues */
			pm8001_ha->memoryMap.region[ob_offset+i].num_elements =
						PM8001_MPI_QUEUE;
			pm8001_ha->memoryMap.region[ob_offset+i].element_size
								= 128;
			pm8001_ha->memoryMap.region[ob_offset+i].total_len =
						PM8001_MPI_QUEUE * 128;
			pm8001_ha->memoryMap.region[ob_offset+i].alignment
								= 128;
		पूर्ण अन्यथा अणु
			/* MPI Memory region 6 Outbound queues */
			pm8001_ha->memoryMap.region[ob_offset+i].num_elements =
						PM8001_MPI_QUEUE;
			pm8001_ha->memoryMap.region[ob_offset+i].element_size
								= 64;
			pm8001_ha->memoryMap.region[ob_offset+i].total_len =
						PM8001_MPI_QUEUE * 64;
			pm8001_ha->memoryMap.region[ob_offset+i].alignment = 64;
		पूर्ण

	पूर्ण
	/* Memory region ग_लिखो DMA*/
	pm8001_ha->memoryMap.region[NVMD].num_elements = 1;
	pm8001_ha->memoryMap.region[NVMD].element_size = 4096;
	pm8001_ha->memoryMap.region[NVMD].total_len = 4096;

	/* Memory region क्रम fw flash */
	pm8001_ha->memoryMap.region[FW_FLASH].total_len = 4096;

	pm8001_ha->memoryMap.region[FORENSIC_MEM].num_elements = 1;
	pm8001_ha->memoryMap.region[FORENSIC_MEM].total_len = 0x10000;
	pm8001_ha->memoryMap.region[FORENSIC_MEM].element_size = 0x10000;
	pm8001_ha->memoryMap.region[FORENSIC_MEM].alignment = 0x10000;
	क्रम (i = 0; i < pm8001_ha->max_memcnt; i++) अणु
		काष्ठा mpi_mem *region = &pm8001_ha->memoryMap.region[i];

		अगर (pm8001_mem_alloc(pm8001_ha->pdev,
				     &region->virt_ptr,
				     &region->phys_addr,
				     &region->phys_addr_hi,
				     &region->phys_addr_lo,
				     region->total_len,
				     region->alignment) != 0) अणु
			pm8001_dbg(pm8001_ha, FAIL, "Mem%d alloc failed\n", i);
			जाओ err_out;
		पूर्ण
	पूर्ण

	/* Memory region क्रम devices*/
	pm8001_ha->devices = kzalloc(PM8001_MAX_DEVICES
				* माप(काष्ठा pm8001_device), GFP_KERNEL);
	अगर (!pm8001_ha->devices) अणु
		rc = -ENOMEM;
		जाओ err_out_nodev;
	पूर्ण
	क्रम (i = 0; i < PM8001_MAX_DEVICES; i++) अणु
		pm8001_ha->devices[i].dev_type = SAS_PHY_UNUSED;
		pm8001_ha->devices[i].id = i;
		pm8001_ha->devices[i].device_id = PM8001_MAX_DEVICES;
		atomic_set(&pm8001_ha->devices[i].running_req, 0);
	पूर्ण
	pm8001_ha->flags = PM8001F_INIT_TIME;
	/* Initialize tags */
	pm8001_tag_init(pm8001_ha);
	वापस 0;

err_out_shost:
	scsi_हटाओ_host(pm8001_ha->shost);
err_out_nodev:
	क्रम (i = 0; i < pm8001_ha->max_memcnt; i++) अणु
		अगर (pm8001_ha->memoryMap.region[i].virt_ptr != शून्य) अणु
			dma_मुक्त_coherent(&pm8001_ha->pdev->dev,
				(pm8001_ha->memoryMap.region[i].total_len +
				pm8001_ha->memoryMap.region[i].alignment),
				pm8001_ha->memoryMap.region[i].virt_ptr,
				pm8001_ha->memoryMap.region[i].phys_addr);
		पूर्ण
	पूर्ण
err_out:
	वापस 1;
पूर्ण

/**
 * pm8001_ioremap - remap the pci high physical address to kernal भव
 * address so that we can access them.
 * @pm8001_ha:our hba काष्ठाure.
 */
अटल पूर्णांक pm8001_ioremap(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	u32 bar;
	u32 logicalBar = 0;
	काष्ठा pci_dev *pdev;

	pdev = pm8001_ha->pdev;
	/* map pci mem (PMC pci base 0-3)*/
	क्रम (bar = 0; bar < PCI_STD_NUM_BARS; bar++) अणु
		/*
		** logical BARs क्रम SPC:
		** bar 0 and 1 - logical BAR0
		** bar 2 and 3 - logical BAR1
		** bar4 - logical BAR2
		** bar5 - logical BAR3
		** Skip the appropriate assignments:
		*/
		अगर ((bar == 1) || (bar == 3))
			जारी;
		अगर (pci_resource_flags(pdev, bar) & IORESOURCE_MEM) अणु
			pm8001_ha->io_mem[logicalBar].membase =
				pci_resource_start(pdev, bar);
			pm8001_ha->io_mem[logicalBar].memsize =
				pci_resource_len(pdev, bar);
			pm8001_ha->io_mem[logicalBar].memvirtaddr =
				ioremap(pm8001_ha->io_mem[logicalBar].membase,
				pm8001_ha->io_mem[logicalBar].memsize);
			अगर (!pm8001_ha->io_mem[logicalBar].memvirtaddr) अणु
				pm8001_dbg(pm8001_ha, INIT,
					"Failed to ioremap bar %d, logicalBar %d",
				   bar, logicalBar);
				वापस -ENOMEM;
			पूर्ण
			pm8001_dbg(pm8001_ha, INIT,
				   "base addr %llx virt_addr=%llx len=%d\n",
				   (u64)pm8001_ha->io_mem[logicalBar].membase,
				   (u64)(अचिन्हित दीर्घ)
				   pm8001_ha->io_mem[logicalBar].memvirtaddr,
				   pm8001_ha->io_mem[logicalBar].memsize);
		पूर्ण अन्यथा अणु
			pm8001_ha->io_mem[logicalBar].membase	= 0;
			pm8001_ha->io_mem[logicalBar].memsize	= 0;
			pm8001_ha->io_mem[logicalBar].memvirtaddr = शून्य;
		पूर्ण
		logicalBar++;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * pm8001_pci_alloc - initialize our ha card काष्ठाure
 * @pdev: pci device.
 * @ent: ent
 * @shost: scsi host काष्ठा which has been initialized beक्रमe.
 */
अटल काष्ठा pm8001_hba_info *pm8001_pci_alloc(काष्ठा pci_dev *pdev,
				 स्थिर काष्ठा pci_device_id *ent,
				काष्ठा Scsi_Host *shost)

अणु
	काष्ठा pm8001_hba_info *pm8001_ha;
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	पूर्णांक j;

	pm8001_ha = sha->lldd_ha;
	अगर (!pm8001_ha)
		वापस शून्य;

	pm8001_ha->pdev = pdev;
	pm8001_ha->dev = &pdev->dev;
	pm8001_ha->chip_id = ent->driver_data;
	pm8001_ha->chip = &pm8001_chips[pm8001_ha->chip_id];
	pm8001_ha->irq = pdev->irq;
	pm8001_ha->sas = sha;
	pm8001_ha->shost = shost;
	pm8001_ha->id = pm8001_id++;
	pm8001_ha->logging_level = logging_level;
	pm8001_ha->non_fatal_count = 0;
	अगर (link_rate >= 1 && link_rate <= 15)
		pm8001_ha->link_rate = (link_rate << 8);
	अन्यथा अणु
		pm8001_ha->link_rate = LINKRATE_15 | LINKRATE_30 |
			LINKRATE_60 | LINKRATE_120;
		pm8001_dbg(pm8001_ha, FAIL,
			   "Setting link rate to default value\n");
	पूर्ण
	प्र_लिखो(pm8001_ha->name, "%s%d", DRV_NAME, pm8001_ha->id);
	/* IOMB size is 128 क्रम 8088/89 controllers */
	अगर (pm8001_ha->chip_id != chip_8001)
		pm8001_ha->iomb_size = IOMB_SIZE_SPCV;
	अन्यथा
		pm8001_ha->iomb_size = IOMB_SIZE_SPC;

#अगर_घोषित PM8001_USE_TASKLET
	/* Tasklet क्रम non msi-x पूर्णांकerrupt handler */
	अगर ((!pdev->msix_cap || !pci_msi_enabled())
	    || (pm8001_ha->chip_id == chip_8001))
		tasklet_init(&pm8001_ha->tasklet[0], pm8001_tasklet,
			(अचिन्हित दीर्घ)&(pm8001_ha->irq_vector[0]));
	अन्यथा
		क्रम (j = 0; j < PM8001_MAX_MSIX_VEC; j++)
			tasklet_init(&pm8001_ha->tasklet[j], pm8001_tasklet,
				(अचिन्हित दीर्घ)&(pm8001_ha->irq_vector[j]));
#पूर्ण_अगर
	अगर (pm8001_ioremap(pm8001_ha))
		जाओ failed_pci_alloc;
	अगर (!pm8001_alloc(pm8001_ha, ent))
		वापस pm8001_ha;
failed_pci_alloc:
	pm8001_मुक्त(pm8001_ha);
	वापस शून्य;
पूर्ण

/**
 * pci_go_44 - pm8001 specअगरied, its DMA is 44 bit rather than 64 bit
 * @pdev: pci device.
 */
अटल पूर्णांक pci_go_44(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक rc;

	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(44));
	अगर (rc) अणु
		rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (rc)
			dev_prपूर्णांकk(KERN_ERR, &pdev->dev,
				"32-bit DMA enable failed\n");
	पूर्ण
	वापस rc;
पूर्ण

/**
 * pm8001_prep_sas_ha_init - allocate memory in general hba काष्ठा && init them.
 * @shost: scsi host which has been allocated outside.
 * @chip_info: our ha काष्ठा.
 */
अटल पूर्णांक pm8001_prep_sas_ha_init(काष्ठा Scsi_Host *shost,
				   स्थिर काष्ठा pm8001_chip_info *chip_info)
अणु
	पूर्णांक phy_nr, port_nr;
	काष्ठा asd_sas_phy **arr_phy;
	काष्ठा asd_sas_port **arr_port;
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);

	phy_nr = chip_info->n_phy;
	port_nr = phy_nr;
	स_रखो(sha, 0x00, माप(*sha));
	arr_phy = kसुस्मृति(phy_nr, माप(व्योम *), GFP_KERNEL);
	अगर (!arr_phy)
		जाओ निकास;
	arr_port = kसुस्मृति(port_nr, माप(व्योम *), GFP_KERNEL);
	अगर (!arr_port)
		जाओ निकास_मुक्त2;

	sha->sas_phy = arr_phy;
	sha->sas_port = arr_port;
	sha->lldd_ha = kzalloc(माप(काष्ठा pm8001_hba_info), GFP_KERNEL);
	अगर (!sha->lldd_ha)
		जाओ निकास_मुक्त1;

	shost->transportt = pm8001_stt;
	shost->max_id = PM8001_MAX_DEVICES;
	shost->max_lun = 8;
	shost->max_channel = 0;
	shost->unique_id = pm8001_id;
	shost->max_cmd_len = 16;
	shost->can_queue = PM8001_CAN_QUEUE;
	shost->cmd_per_lun = 32;
	वापस 0;
निकास_मुक्त1:
	kमुक्त(arr_port);
निकास_मुक्त2:
	kमुक्त(arr_phy);
निकास:
	वापस -1;
पूर्ण

/**
 * pm8001_post_sas_ha_init - initialize general hba काष्ठा defined in libsas
 * @shost: scsi host which has been allocated outside
 * @chip_info: our ha काष्ठा.
 */
अटल व्योम  pm8001_post_sas_ha_init(काष्ठा Scsi_Host *shost,
				     स्थिर काष्ठा pm8001_chip_info *chip_info)
अणु
	पूर्णांक i = 0;
	काष्ठा pm8001_hba_info *pm8001_ha;
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);

	pm8001_ha = sha->lldd_ha;
	क्रम (i = 0; i < chip_info->n_phy; i++) अणु
		sha->sas_phy[i] = &pm8001_ha->phy[i].sas_phy;
		sha->sas_port[i] = &pm8001_ha->port[i].sas_port;
		sha->sas_phy[i]->sas_addr =
			(u8 *)&pm8001_ha->phy[i].dev_sas_addr;
	पूर्ण
	sha->sas_ha_name = DRV_NAME;
	sha->dev = pm8001_ha->dev;
	sha->strict_wide_ports = 1;
	sha->lldd_module = THIS_MODULE;
	sha->sas_addr = &pm8001_ha->sas_addr[0];
	sha->num_phys = chip_info->n_phy;
	sha->core.shost = shost;
पूर्ण

/**
 * pm8001_init_sas_add - initialize sas address
 * @pm8001_ha: our ha काष्ठा.
 *
 * Currently we just set the fixed SAS address to our HBA,क्रम manufacture,
 * it should पढ़ो from the EEPROM
 */
अटल व्योम pm8001_init_sas_add(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	u8 i, j;
	u8 sas_add[8];
#अगर_घोषित PM8001_READ_VPD
	/* For new SPC controllers WWN is stored in flash vpd
	*  For SPC/SPCve controllers WWN is stored in EEPROM
	*  For Older SPC WWN is stored in NVMD
	*/
	DECLARE_COMPLETION_ONSTACK(completion);
	काष्ठा pm8001_ioctl_payload payload;
	u16 deviceid;
	पूर्णांक rc;

	pci_पढ़ो_config_word(pm8001_ha->pdev, PCI_DEVICE_ID, &deviceid);
	pm8001_ha->nvmd_completion = &completion;

	अगर (pm8001_ha->chip_id == chip_8001) अणु
		अगर (deviceid == 0x8081 || deviceid == 0x0042) अणु
			payload.minor_function = 4;
			payload.rd_length = 4096;
		पूर्ण अन्यथा अणु
			payload.minor_function = 0;
			payload.rd_length = 128;
		पूर्ण
	पूर्ण अन्यथा अगर ((pm8001_ha->chip_id == chip_8070 ||
			pm8001_ha->chip_id == chip_8072) &&
			pm8001_ha->pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_ATTO) अणु
		payload.minor_function = 4;
		payload.rd_length = 4096;
	पूर्ण अन्यथा अणु
		payload.minor_function = 1;
		payload.rd_length = 4096;
	पूर्ण
	payload.offset = 0;
	payload.func_specअगरic = kzalloc(payload.rd_length, GFP_KERNEL);
	अगर (!payload.func_specअगरic) अणु
		pm8001_dbg(pm8001_ha, INIT, "mem alloc fail\n");
		वापस;
	पूर्ण
	rc = PM8001_CHIP_DISP->get_nvmd_req(pm8001_ha, &payload);
	अगर (rc) अणु
		kमुक्त(payload.func_specअगरic);
		pm8001_dbg(pm8001_ha, INIT, "nvmd failed\n");
		वापस;
	पूर्ण
	रुको_क्रम_completion(&completion);

	क्रम (i = 0, j = 0; i <= 7; i++, j++) अणु
		अगर (pm8001_ha->chip_id == chip_8001) अणु
			अगर (deviceid == 0x8081)
				pm8001_ha->sas_addr[j] =
					payload.func_specअगरic[0x704 + i];
			अन्यथा अगर (deviceid == 0x0042)
				pm8001_ha->sas_addr[j] =
					payload.func_specअगरic[0x010 + i];
		पूर्ण अन्यथा अगर ((pm8001_ha->chip_id == chip_8070 ||
				pm8001_ha->chip_id == chip_8072) &&
				pm8001_ha->pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_ATTO) अणु
			pm8001_ha->sas_addr[j] =
					payload.func_specअगरic[0x010 + i];
		पूर्ण अन्यथा
			pm8001_ha->sas_addr[j] =
					payload.func_specअगरic[0x804 + i];
	पूर्ण
	स_नकल(sas_add, pm8001_ha->sas_addr, SAS_ADDR_SIZE);
	क्रम (i = 0; i < pm8001_ha->chip->n_phy; i++) अणु
		अगर (i && ((i % 4) == 0))
			sas_add[7] = sas_add[7] + 4;
		स_नकल(&pm8001_ha->phy[i].dev_sas_addr,
			sas_add, SAS_ADDR_SIZE);
		pm8001_dbg(pm8001_ha, INIT, "phy %d sas_addr = %016llx\n", i,
			   pm8001_ha->phy[i].dev_sas_addr);
	पूर्ण
	kमुक्त(payload.func_specअगरic);
#अन्यथा
	क्रम (i = 0; i < pm8001_ha->chip->n_phy; i++) अणु
		pm8001_ha->phy[i].dev_sas_addr = 0x50010c600047f9d0ULL;
		pm8001_ha->phy[i].dev_sas_addr =
			cpu_to_be64((u64)
				(*(u64 *)&pm8001_ha->phy[i].dev_sas_addr));
	पूर्ण
	स_नकल(pm8001_ha->sas_addr, &pm8001_ha->phy[0].dev_sas_addr,
		SAS_ADDR_SIZE);
#पूर्ण_अगर
पूर्ण

/*
 * pm8001_get_phy_settings_info : Read phy setting values.
 * @pm8001_ha : our hba.
 */
अटल पूर्णांक pm8001_get_phy_settings_info(काष्ठा pm8001_hba_info *pm8001_ha)
अणु

#अगर_घोषित PM8001_READ_VPD
	/*OPTION ROM FLASH पढ़ो क्रम the SPC cards */
	DECLARE_COMPLETION_ONSTACK(completion);
	काष्ठा pm8001_ioctl_payload payload;
	पूर्णांक rc;

	pm8001_ha->nvmd_completion = &completion;
	/* SAS ADDRESS पढ़ो from flash / EEPROM */
	payload.minor_function = 6;
	payload.offset = 0;
	payload.rd_length = 4096;
	payload.func_specअगरic = kzalloc(4096, GFP_KERNEL);
	अगर (!payload.func_specअगरic)
		वापस -ENOMEM;
	/* Read phy setting values from flash */
	rc = PM8001_CHIP_DISP->get_nvmd_req(pm8001_ha, &payload);
	अगर (rc) अणु
		kमुक्त(payload.func_specअगरic);
		pm8001_dbg(pm8001_ha, INIT, "nvmd failed\n");
		वापस -ENOMEM;
	पूर्ण
	रुको_क्रम_completion(&completion);
	pm8001_set_phy_profile(pm8001_ha, माप(u8), payload.func_specअगरic);
	kमुक्त(payload.func_specअगरic);
#पूर्ण_अगर
	वापस 0;
पूर्ण

काष्ठा pm8001_mpi3_phy_pg_trx_config अणु
	u32 LaneLosCfg;
	u32 LanePgaCfg1;
	u32 LanePisoCfg1;
	u32 LanePisoCfg2;
	u32 LanePisoCfg3;
	u32 LanePisoCfg4;
	u32 LanePisoCfg5;
	u32 LanePisoCfg6;
	u32 LaneBctCtrl;
पूर्ण;

/**
 * pm8001_get_पूर्णांकernal_phy_settings : Retrieves the पूर्णांकernal PHY settings
 * @pm8001_ha : our adapter
 * @phycfg : PHY config page to populate
 */
अटल
व्योम pm8001_get_पूर्णांकernal_phy_settings(काष्ठा pm8001_hba_info *pm8001_ha,
		काष्ठा pm8001_mpi3_phy_pg_trx_config *phycfg)
अणु
	phycfg->LaneLosCfg   = 0x00000132;
	phycfg->LanePgaCfg1  = 0x00203949;
	phycfg->LanePisoCfg1 = 0x000000FF;
	phycfg->LanePisoCfg2 = 0xFF000001;
	phycfg->LanePisoCfg3 = 0xE7011300;
	phycfg->LanePisoCfg4 = 0x631C40C0;
	phycfg->LanePisoCfg5 = 0xF8102036;
	phycfg->LanePisoCfg6 = 0xF74A1000;
	phycfg->LaneBctCtrl  = 0x00FB33F8;
पूर्ण

/**
 * pm8001_get_बाह्यal_phy_settings : Retrieves the बाह्यal PHY settings
 * @pm8001_ha : our adapter
 * @phycfg : PHY config page to populate
 */
अटल
व्योम pm8001_get_बाह्यal_phy_settings(काष्ठा pm8001_hba_info *pm8001_ha,
		काष्ठा pm8001_mpi3_phy_pg_trx_config *phycfg)
अणु
	phycfg->LaneLosCfg   = 0x00000132;
	phycfg->LanePgaCfg1  = 0x00203949;
	phycfg->LanePisoCfg1 = 0x000000FF;
	phycfg->LanePisoCfg2 = 0xFF000001;
	phycfg->LanePisoCfg3 = 0xE7011300;
	phycfg->LanePisoCfg4 = 0x63349140;
	phycfg->LanePisoCfg5 = 0xF8102036;
	phycfg->LanePisoCfg6 = 0xF80D9300;
	phycfg->LaneBctCtrl  = 0x00FB33F8;
पूर्ण

/**
 * pm8001_get_phy_mask : Retrieves the mask that denotes अगर a PHY is पूर्णांक/ext
 * @pm8001_ha : our adapter
 * @phymask : The PHY mask
 */
अटल
व्योम pm8001_get_phy_mask(काष्ठा pm8001_hba_info *pm8001_ha, पूर्णांक *phymask)
अणु
	चयन (pm8001_ha->pdev->subप्रणाली_device) अणु
	हाल 0x0070: /* H1280 - 8 बाह्यal 0 पूर्णांकernal */
	हाल 0x0072: /* H12F0 - 16 बाह्यal 0 पूर्णांकernal */
		*phymask = 0x0000;
		अवरोध;

	हाल 0x0071: /* H1208 - 0 बाह्यal 8 पूर्णांकernal */
	हाल 0x0073: /* H120F - 0 बाह्यal 16 पूर्णांकernal */
		*phymask = 0xFFFF;
		अवरोध;

	हाल 0x0080: /* H1244 - 4 बाह्यal 4 पूर्णांकernal */
		*phymask = 0x00F0;
		अवरोध;

	हाल 0x0081: /* H1248 - 4 बाह्यal 8 पूर्णांकernal */
		*phymask = 0x0FF0;
		अवरोध;

	हाल 0x0082: /* H1288 - 8 बाह्यal 8 पूर्णांकernal */
		*phymask = 0xFF00;
		अवरोध;

	शेष:
		pm8001_dbg(pm8001_ha, INIT,
			   "Unknown subsystem device=0x%.04x\n",
			   pm8001_ha->pdev->subप्रणाली_device);
	पूर्ण
पूर्ण

/**
 * pm8001_set_phy_settings_ven_117c_12G() : Configure ATTO 12Gb PHY settings
 * @pm8001_ha : our adapter
 */
अटल
पूर्णांक pm8001_set_phy_settings_ven_117c_12G(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	काष्ठा pm8001_mpi3_phy_pg_trx_config phycfg_पूर्णांक;
	काष्ठा pm8001_mpi3_phy_pg_trx_config phycfg_ext;
	पूर्णांक phymask = 0;
	पूर्णांक i = 0;

	स_रखो(&phycfg_पूर्णांक, 0, माप(phycfg_पूर्णांक));
	स_रखो(&phycfg_ext, 0, माप(phycfg_ext));

	pm8001_get_पूर्णांकernal_phy_settings(pm8001_ha, &phycfg_पूर्णांक);
	pm8001_get_बाह्यal_phy_settings(pm8001_ha, &phycfg_ext);
	pm8001_get_phy_mask(pm8001_ha, &phymask);

	क्रम (i = 0; i < pm8001_ha->chip->n_phy; i++) अणु
		अगर (phymask & (1 << i)) अणु/* Internal PHY */
			pm8001_set_phy_profile_single(pm8001_ha, i,
					माप(phycfg_पूर्णांक) / माप(u32),
					(u32 *)&phycfg_पूर्णांक);

		पूर्ण अन्यथा अणु /* External PHY */
			pm8001_set_phy_profile_single(pm8001_ha, i,
					माप(phycfg_ext) / माप(u32),
					(u32 *)&phycfg_ext);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pm8001_configure_phy_settings : Configures PHY settings based on venकरोr ID.
 * @pm8001_ha : our hba.
 */
अटल पूर्णांक pm8001_configure_phy_settings(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	चयन (pm8001_ha->pdev->subप्रणाली_venकरोr) अणु
	हाल PCI_VENDOR_ID_ATTO:
		अगर (pm8001_ha->pdev->device == 0x0042) /* 6Gb */
			वापस 0;
		अन्यथा
			वापस pm8001_set_phy_settings_ven_117c_12G(pm8001_ha);

	हाल PCI_VENDOR_ID_ADAPTEC2:
	हाल 0:
		वापस 0;

	शेष:
		वापस pm8001_get_phy_settings_info(pm8001_ha);
	पूर्ण
पूर्ण

#अगर_घोषित PM8001_USE_MSIX
/**
 * pm8001_setup_msix - enable MSI-X पूर्णांकerrupt
 * @pm8001_ha: our ha काष्ठा.
 */
अटल u32 pm8001_setup_msix(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	u32 number_of_पूर्णांकr;
	पूर्णांक rc, cpu_online_count;
	अचिन्हित पूर्णांक allocated_irq_vectors;

	/* SPCv controllers supports 64 msi-x */
	अगर (pm8001_ha->chip_id == chip_8001) अणु
		number_of_पूर्णांकr = 1;
	पूर्ण अन्यथा अणु
		number_of_पूर्णांकr = PM8001_MAX_MSIX_VEC;
	पूर्ण

	cpu_online_count = num_online_cpus();
	number_of_पूर्णांकr = min_t(पूर्णांक, cpu_online_count, number_of_पूर्णांकr);
	rc = pci_alloc_irq_vectors(pm8001_ha->pdev, number_of_पूर्णांकr,
			number_of_पूर्णांकr, PCI_IRQ_MSIX);
	allocated_irq_vectors = rc;
	अगर (rc < 0)
		वापस rc;

	/* Assigns the number of पूर्णांकerrupts */
	number_of_पूर्णांकr = min_t(पूर्णांक, allocated_irq_vectors, number_of_पूर्णांकr);
	pm8001_ha->number_of_पूर्णांकr = number_of_पूर्णांकr;

	/* Maximum queue number updating in HBA काष्ठाure */
	pm8001_ha->max_q_num = number_of_पूर्णांकr;

	pm8001_dbg(pm8001_ha, INIT,
		   "pci_alloc_irq_vectors request ret:%d no of intr %d\n",
		   rc, pm8001_ha->number_of_पूर्णांकr);
	वापस 0;
पूर्ण

अटल u32 pm8001_request_msix(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	u32 i = 0, j = 0;
	पूर्णांक flag = 0, rc = 0;
	पूर्णांक nr_irqs = pm8001_ha->number_of_पूर्णांकr;

	अगर (pm8001_ha->chip_id != chip_8001)
		flag &= ~IRQF_SHARED;

	pm8001_dbg(pm8001_ha, INIT,
		   "pci_enable_msix request number of intr %d\n",
		   pm8001_ha->number_of_पूर्णांकr);

	अगर (nr_irqs > ARRAY_SIZE(pm8001_ha->पूर्णांकr_drvname))
		nr_irqs = ARRAY_SIZE(pm8001_ha->पूर्णांकr_drvname);

	क्रम (i = 0; i < nr_irqs; i++) अणु
		snम_लिखो(pm8001_ha->पूर्णांकr_drvname[i],
			माप(pm8001_ha->पूर्णांकr_drvname[0]),
			"%s-%d", pm8001_ha->name, i);
		pm8001_ha->irq_vector[i].irq_id = i;
		pm8001_ha->irq_vector[i].drv_inst = pm8001_ha;

		rc = request_irq(pci_irq_vector(pm8001_ha->pdev, i),
			pm8001_पूर्णांकerrupt_handler_msix, flag,
			pm8001_ha->पूर्णांकr_drvname[i],
			&(pm8001_ha->irq_vector[i]));
		अगर (rc) अणु
			क्रम (j = 0; j < i; j++) अणु
				मुक्त_irq(pci_irq_vector(pm8001_ha->pdev, i),
					&(pm8001_ha->irq_vector[i]));
			पूर्ण
			pci_मुक्त_irq_vectors(pm8001_ha->pdev);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण
#पूर्ण_अगर

अटल u32 pm8001_setup_irq(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	काष्ठा pci_dev *pdev;

	pdev = pm8001_ha->pdev;

#अगर_घोषित PM8001_USE_MSIX
	अगर (pci_find_capability(pdev, PCI_CAP_ID_MSIX))
		वापस pm8001_setup_msix(pm8001_ha);
	pm8001_dbg(pm8001_ha, INIT, "MSIX not supported!!!\n");
#पूर्ण_अगर
	वापस 0;
पूर्ण

/**
 * pm8001_request_irq - रेजिस्टर पूर्णांकerrupt
 * @pm8001_ha: our ha काष्ठा.
 */
अटल u32 pm8001_request_irq(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	काष्ठा pci_dev *pdev;
	पूर्णांक rc;

	pdev = pm8001_ha->pdev;

#अगर_घोषित PM8001_USE_MSIX
	अगर (pdev->msix_cap && pci_msi_enabled())
		वापस pm8001_request_msix(pm8001_ha);
	अन्यथा अणु
		pm8001_dbg(pm8001_ha, INIT, "MSIX not supported!!!\n");
		जाओ पूर्णांकx;
	पूर्ण
#पूर्ण_अगर

पूर्णांकx:
	/* initialize the INT-X पूर्णांकerrupt */
	pm8001_ha->irq_vector[0].irq_id = 0;
	pm8001_ha->irq_vector[0].drv_inst = pm8001_ha;
	rc = request_irq(pdev->irq, pm8001_पूर्णांकerrupt_handler_पूर्णांकx, IRQF_SHARED,
		pm8001_ha->name, SHOST_TO_SAS_HA(pm8001_ha->shost));
	वापस rc;
पूर्ण

/**
 * pm8001_pci_probe - probe supported device
 * @pdev: pci device which kernel has been prepared क्रम.
 * @ent: pci device id
 *
 * This function is the मुख्य initialization function, when रेजिस्टर a new
 * pci driver it is invoked, all काष्ठा an hardware initilization should be करोne
 * here, also, रेजिस्टर पूर्णांकerrupt
 */
अटल पूर्णांक pm8001_pci_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	अचिन्हित पूर्णांक rc;
	u32	pci_reg;
	u8	i = 0;
	काष्ठा pm8001_hba_info *pm8001_ha;
	काष्ठा Scsi_Host *shost = शून्य;
	स्थिर काष्ठा pm8001_chip_info *chip;
	काष्ठा sas_ha_काष्ठा *sha;

	dev_prपूर्णांकk(KERN_INFO, &pdev->dev,
		"pm80xx: driver version %s\n", DRV_VERSION);
	rc = pci_enable_device(pdev);
	अगर (rc)
		जाओ err_out_enable;
	pci_set_master(pdev);
	/*
	 * Enable pci slot busmaster by setting pci command रेजिस्टर.
	 * This is required by FW क्रम Cyclone card.
	 */

	pci_पढ़ो_config_dword(pdev, PCI_COMMAND, &pci_reg);
	pci_reg |= 0x157;
	pci_ग_लिखो_config_dword(pdev, PCI_COMMAND, pci_reg);
	rc = pci_request_regions(pdev, DRV_NAME);
	अगर (rc)
		जाओ err_out_disable;
	rc = pci_go_44(pdev);
	अगर (rc)
		जाओ err_out_regions;

	shost = scsi_host_alloc(&pm8001_sht, माप(व्योम *));
	अगर (!shost) अणु
		rc = -ENOMEM;
		जाओ err_out_regions;
	पूर्ण
	chip = &pm8001_chips[ent->driver_data];
	sha = kzalloc(माप(काष्ठा sas_ha_काष्ठा), GFP_KERNEL);
	अगर (!sha) अणु
		rc = -ENOMEM;
		जाओ err_out_मुक्त_host;
	पूर्ण
	SHOST_TO_SAS_HA(shost) = sha;

	rc = pm8001_prep_sas_ha_init(shost, chip);
	अगर (rc) अणु
		rc = -ENOMEM;
		जाओ err_out_मुक्त;
	पूर्ण
	pci_set_drvdata(pdev, SHOST_TO_SAS_HA(shost));
	/* ent->driver variable is used to dअगरferentiate between controllers */
	pm8001_ha = pm8001_pci_alloc(pdev, ent, shost);
	अगर (!pm8001_ha) अणु
		rc = -ENOMEM;
		जाओ err_out_मुक्त;
	पूर्ण

	PM8001_CHIP_DISP->chip_soft_rst(pm8001_ha);
	rc = PM8001_CHIP_DISP->chip_init(pm8001_ha);
	अगर (rc) अणु
		pm8001_dbg(pm8001_ha, FAIL,
			   "chip_init failed [ret: %d]\n", rc);
		जाओ err_out_ha_मुक्त;
	पूर्ण

	rc = pm8001_init_ccb_tag(pm8001_ha, shost, pdev);
	अगर (rc)
		जाओ err_out_enable;

	rc = scsi_add_host(shost, &pdev->dev);
	अगर (rc)
		जाओ err_out_ha_मुक्त;

	PM8001_CHIP_DISP->पूर्णांकerrupt_enable(pm8001_ha, 0);
	अगर (pm8001_ha->chip_id != chip_8001) अणु
		क्रम (i = 1; i < pm8001_ha->number_of_पूर्णांकr; i++)
			PM8001_CHIP_DISP->पूर्णांकerrupt_enable(pm8001_ha, i);
		/* setup thermal configuration. */
		pm80xx_set_thermal_config(pm8001_ha);
	पूर्ण

	pm8001_init_sas_add(pm8001_ha);
	/* phy setting support क्रम motherboard controller */
	rc = pm8001_configure_phy_settings(pm8001_ha);
	अगर (rc)
		जाओ err_out_shost;

	pm8001_post_sas_ha_init(shost, chip);
	rc = sas_रेजिस्टर_ha(SHOST_TO_SAS_HA(shost));
	अगर (rc) अणु
		pm8001_dbg(pm8001_ha, FAIL,
			   "sas_register_ha failed [ret: %d]\n", rc);
		जाओ err_out_shost;
	पूर्ण
	list_add_tail(&pm8001_ha->list, &hba_list);
	pm8001_ha->flags = PM8001F_RUN_TIME;
	scsi_scan_host(pm8001_ha->shost);
	वापस 0;

err_out_shost:
	scsi_हटाओ_host(pm8001_ha->shost);
err_out_ha_मुक्त:
	pm8001_मुक्त(pm8001_ha);
err_out_मुक्त:
	kमुक्त(sha);
err_out_मुक्त_host:
	scsi_host_put(shost);
err_out_regions:
	pci_release_regions(pdev);
err_out_disable:
	pci_disable_device(pdev);
err_out_enable:
	वापस rc;
पूर्ण

/*
 * pm8001_init_ccb_tag - allocate memory to CCB and tag.
 * @pm8001_ha: our hba card inक्रमmation.
 * @shost: scsi host which has been allocated outside.
 */
अटल पूर्णांक
pm8001_init_ccb_tag(काष्ठा pm8001_hba_info *pm8001_ha, काष्ठा Scsi_Host *shost,
			काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i = 0;
	u32 max_out_io, ccb_count;
	u32 can_queue;

	max_out_io = pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.max_out_io;
	ccb_count = min_t(पूर्णांक, PM8001_MAX_CCB, max_out_io);

	/* Update to the scsi host*/
	can_queue = ccb_count - PM8001_RESERVE_SLOT;
	shost->can_queue = can_queue;

	pm8001_ha->tags = kzalloc(ccb_count, GFP_KERNEL);
	अगर (!pm8001_ha->tags)
		जाओ err_out;

	/* Memory region क्रम ccb_info*/
	pm8001_ha->ccb_info =
		kसुस्मृति(ccb_count, माप(काष्ठा pm8001_ccb_info), GFP_KERNEL);
	अगर (!pm8001_ha->ccb_info) अणु
		pm8001_dbg(pm8001_ha, FAIL,
			   "Unable to allocate memory for ccb\n");
		जाओ err_out_noccb;
	पूर्ण
	क्रम (i = 0; i < ccb_count; i++) अणु
		pm8001_ha->ccb_info[i].buf_prd = dma_alloc_coherent(&pdev->dev,
				माप(काष्ठा pm8001_prd) * PM8001_MAX_DMA_SG,
				&pm8001_ha->ccb_info[i].ccb_dma_handle,
				GFP_KERNEL);
		अगर (!pm8001_ha->ccb_info[i].buf_prd) अणु
			pm8001_dbg(pm8001_ha, FAIL,
				   "ccb prd memory allocation error\n");
			जाओ err_out;
		पूर्ण
		pm8001_ha->ccb_info[i].task = शून्य;
		pm8001_ha->ccb_info[i].ccb_tag = 0xffffffff;
		pm8001_ha->ccb_info[i].device = शून्य;
		++pm8001_ha->tags_num;
	पूर्ण
	वापस 0;

err_out_noccb:
	kमुक्त(pm8001_ha->devices);
err_out:
	वापस -ENOMEM;
पूर्ण

अटल व्योम pm8001_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sas_ha_काष्ठा *sha = pci_get_drvdata(pdev);
	काष्ठा pm8001_hba_info *pm8001_ha;
	पूर्णांक i, j;
	pm8001_ha = sha->lldd_ha;
	sas_unरेजिस्टर_ha(sha);
	sas_हटाओ_host(pm8001_ha->shost);
	list_del(&pm8001_ha->list);
	PM8001_CHIP_DISP->पूर्णांकerrupt_disable(pm8001_ha, 0xFF);
	PM8001_CHIP_DISP->chip_soft_rst(pm8001_ha);

#अगर_घोषित PM8001_USE_MSIX
	क्रम (i = 0; i < pm8001_ha->number_of_पूर्णांकr; i++)
		synchronize_irq(pci_irq_vector(pdev, i));
	क्रम (i = 0; i < pm8001_ha->number_of_पूर्णांकr; i++)
		मुक्त_irq(pci_irq_vector(pdev, i), &pm8001_ha->irq_vector[i]);
	pci_मुक्त_irq_vectors(pdev);
#अन्यथा
	मुक्त_irq(pm8001_ha->irq, sha);
#पूर्ण_अगर
#अगर_घोषित PM8001_USE_TASKLET
	/* For non-msix and msix पूर्णांकerrupts */
	अगर ((!pdev->msix_cap || !pci_msi_enabled()) ||
	    (pm8001_ha->chip_id == chip_8001))
		tasklet_समाप्त(&pm8001_ha->tasklet[0]);
	अन्यथा
		क्रम (j = 0; j < PM8001_MAX_MSIX_VEC; j++)
			tasklet_समाप्त(&pm8001_ha->tasklet[j]);
#पूर्ण_अगर
	scsi_host_put(pm8001_ha->shost);
	pm8001_मुक्त(pm8001_ha);
	kमुक्त(sha->sas_phy);
	kमुक्त(sha->sas_port);
	kमुक्त(sha);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

/**
 * pm8001_pci_suspend - घातer management suspend मुख्य entry poपूर्णांक
 * @dev: Device काष्ठा
 *
 * Returns 0 success, anything अन्यथा error.
 */
अटल पूर्णांक __maybe_unused pm8001_pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा sas_ha_काष्ठा *sha = pci_get_drvdata(pdev);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	पूर्णांक  i, j;
	sas_suspend_ha(sha);
	flush_workqueue(pm8001_wq);
	scsi_block_requests(pm8001_ha->shost);
	अगर (!pdev->pm_cap) अणु
		dev_err(dev, " PCI PM not supported\n");
		वापस -ENODEV;
	पूर्ण
	PM8001_CHIP_DISP->पूर्णांकerrupt_disable(pm8001_ha, 0xFF);
	PM8001_CHIP_DISP->chip_soft_rst(pm8001_ha);
#अगर_घोषित PM8001_USE_MSIX
	क्रम (i = 0; i < pm8001_ha->number_of_पूर्णांकr; i++)
		synchronize_irq(pci_irq_vector(pdev, i));
	क्रम (i = 0; i < pm8001_ha->number_of_पूर्णांकr; i++)
		मुक्त_irq(pci_irq_vector(pdev, i), &pm8001_ha->irq_vector[i]);
	pci_मुक्त_irq_vectors(pdev);
#अन्यथा
	मुक्त_irq(pm8001_ha->irq, sha);
#पूर्ण_अगर
#अगर_घोषित PM8001_USE_TASKLET
	/* For non-msix and msix पूर्णांकerrupts */
	अगर ((!pdev->msix_cap || !pci_msi_enabled()) ||
	    (pm8001_ha->chip_id == chip_8001))
		tasklet_समाप्त(&pm8001_ha->tasklet[0]);
	अन्यथा
		क्रम (j = 0; j < PM8001_MAX_MSIX_VEC; j++)
			tasklet_समाप्त(&pm8001_ha->tasklet[j]);
#पूर्ण_अगर
	pm8001_info(pm8001_ha, "pdev=0x%p, slot=%s, entering "
		      "suspended state\n", pdev,
		      pm8001_ha->name);
	वापस 0;
पूर्ण

/**
 * pm8001_pci_resume - घातer management resume मुख्य entry poपूर्णांक
 * @dev: Device काष्ठा
 *
 * Returns 0 success, anything अन्यथा error.
 */
अटल पूर्णांक __maybe_unused pm8001_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा sas_ha_काष्ठा *sha = pci_get_drvdata(pdev);
	काष्ठा pm8001_hba_info *pm8001_ha;
	पूर्णांक rc;
	u8 i = 0, j;
	u32 device_state;
	DECLARE_COMPLETION_ONSTACK(completion);
	pm8001_ha = sha->lldd_ha;
	device_state = pdev->current_state;

	pm8001_info(pm8001_ha, "pdev=0x%p, slot=%s, resuming from previous operating state [D%d]\n",
		      pdev, pm8001_ha->name, device_state);

	rc = pci_go_44(pdev);
	अगर (rc)
		जाओ err_out_disable;
	sas_prep_resume_ha(sha);
	/* chip soft rst only क्रम spc */
	अगर (pm8001_ha->chip_id == chip_8001) अणु
		PM8001_CHIP_DISP->chip_soft_rst(pm8001_ha);
		pm8001_dbg(pm8001_ha, INIT, "chip soft reset successful\n");
	पूर्ण
	rc = PM8001_CHIP_DISP->chip_init(pm8001_ha);
	अगर (rc)
		जाओ err_out_disable;

	/* disable all the पूर्णांकerrupt bits */
	PM8001_CHIP_DISP->पूर्णांकerrupt_disable(pm8001_ha, 0xFF);

	rc = pm8001_request_irq(pm8001_ha);
	अगर (rc)
		जाओ err_out_disable;
#अगर_घोषित PM8001_USE_TASKLET
	/*  Tasklet क्रम non msi-x पूर्णांकerrupt handler */
	अगर ((!pdev->msix_cap || !pci_msi_enabled()) ||
	    (pm8001_ha->chip_id == chip_8001))
		tasklet_init(&pm8001_ha->tasklet[0], pm8001_tasklet,
			(अचिन्हित दीर्घ)&(pm8001_ha->irq_vector[0]));
	अन्यथा
		क्रम (j = 0; j < PM8001_MAX_MSIX_VEC; j++)
			tasklet_init(&pm8001_ha->tasklet[j], pm8001_tasklet,
				(अचिन्हित दीर्घ)&(pm8001_ha->irq_vector[j]));
#पूर्ण_अगर
	PM8001_CHIP_DISP->पूर्णांकerrupt_enable(pm8001_ha, 0);
	अगर (pm8001_ha->chip_id != chip_8001) अणु
		क्रम (i = 1; i < pm8001_ha->number_of_पूर्णांकr; i++)
			PM8001_CHIP_DISP->पूर्णांकerrupt_enable(pm8001_ha, i);
	पूर्ण

	/* Chip करोcumentation क्रम the 8070 and 8072 SPCv    */
	/* states that a 500ms minimum delay is required    */
	/* beक्रमe issuing commands. Otherwise, the firmware */
	/* will enter an unrecoverable state.               */

	अगर (pm8001_ha->chip_id == chip_8070 ||
		pm8001_ha->chip_id == chip_8072) अणु
		mdelay(500);
	पूर्ण

	/* Spin up the PHYs */

	pm8001_ha->flags = PM8001F_RUN_TIME;
	क्रम (i = 0; i < pm8001_ha->chip->n_phy; i++) अणु
		pm8001_ha->phy[i].enable_completion = &completion;
		PM8001_CHIP_DISP->phy_start_req(pm8001_ha, i);
		रुको_क्रम_completion(&completion);
	पूर्ण
	sas_resume_ha(sha);
	वापस 0;

err_out_disable:
	scsi_हटाओ_host(pm8001_ha->shost);

	वापस rc;
पूर्ण

/* update of pci device, venकरोr id and driver data with
 * unique value क्रम each of the controller
 */
अटल काष्ठा pci_device_id pm8001_pci_table[] = अणु
	अणु PCI_VDEVICE(PMC_Sierra, 0x8001), chip_8001 पूर्ण,
	अणु PCI_VDEVICE(PMC_Sierra, 0x8006), chip_8006 पूर्ण,
	अणु PCI_VDEVICE(ADAPTEC2, 0x8006), chip_8006 पूर्ण,
	अणु PCI_VDEVICE(ATTO, 0x0042), chip_8001 पूर्ण,
	/* Support क्रम SPC/SPCv/SPCve controllers */
	अणु PCI_VDEVICE(ADAPTEC2, 0x8001), chip_8001 पूर्ण,
	अणु PCI_VDEVICE(PMC_Sierra, 0x8008), chip_8008 पूर्ण,
	अणु PCI_VDEVICE(ADAPTEC2, 0x8008), chip_8008 पूर्ण,
	अणु PCI_VDEVICE(PMC_Sierra, 0x8018), chip_8018 पूर्ण,
	अणु PCI_VDEVICE(ADAPTEC2, 0x8018), chip_8018 पूर्ण,
	अणु PCI_VDEVICE(PMC_Sierra, 0x8009), chip_8009 पूर्ण,
	अणु PCI_VDEVICE(ADAPTEC2, 0x8009), chip_8009 पूर्ण,
	अणु PCI_VDEVICE(PMC_Sierra, 0x8019), chip_8019 पूर्ण,
	अणु PCI_VDEVICE(ADAPTEC2, 0x8019), chip_8019 पूर्ण,
	अणु PCI_VDEVICE(PMC_Sierra, 0x8074), chip_8074 पूर्ण,
	अणु PCI_VDEVICE(ADAPTEC2, 0x8074), chip_8074 पूर्ण,
	अणु PCI_VDEVICE(PMC_Sierra, 0x8076), chip_8076 पूर्ण,
	अणु PCI_VDEVICE(ADAPTEC2, 0x8076), chip_8076 पूर्ण,
	अणु PCI_VDEVICE(PMC_Sierra, 0x8077), chip_8077 पूर्ण,
	अणु PCI_VDEVICE(ADAPTEC2, 0x8077), chip_8077 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, 0x8081,
		PCI_VENDOR_ID_ADAPTEC2, 0x0400, 0, 0, chip_8001 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, 0x8081,
		PCI_VENDOR_ID_ADAPTEC2, 0x0800, 0, 0, chip_8001 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, 0x8088,
		PCI_VENDOR_ID_ADAPTEC2, 0x0008, 0, 0, chip_8008 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, 0x8088,
		PCI_VENDOR_ID_ADAPTEC2, 0x0800, 0, 0, chip_8008 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, 0x8089,
		PCI_VENDOR_ID_ADAPTEC2, 0x0008, 0, 0, chip_8009 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, 0x8089,
		PCI_VENDOR_ID_ADAPTEC2, 0x0800, 0, 0, chip_8009 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, 0x8088,
		PCI_VENDOR_ID_ADAPTEC2, 0x0016, 0, 0, chip_8018 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, 0x8088,
		PCI_VENDOR_ID_ADAPTEC2, 0x1600, 0, 0, chip_8018 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, 0x8089,
		PCI_VENDOR_ID_ADAPTEC2, 0x0016, 0, 0, chip_8019 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, 0x8089,
		PCI_VENDOR_ID_ADAPTEC2, 0x1600, 0, 0, chip_8019 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, 0x8074,
		PCI_VENDOR_ID_ADAPTEC2, 0x0800, 0, 0, chip_8074 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, 0x8076,
		PCI_VENDOR_ID_ADAPTEC2, 0x1600, 0, 0, chip_8076 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, 0x8077,
		PCI_VENDOR_ID_ADAPTEC2, 0x1600, 0, 0, chip_8077 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, 0x8074,
		PCI_VENDOR_ID_ADAPTEC2, 0x0008, 0, 0, chip_8074 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, 0x8076,
		PCI_VENDOR_ID_ADAPTEC2, 0x0016, 0, 0, chip_8076 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, 0x8077,
		PCI_VENDOR_ID_ADAPTEC2, 0x0016, 0, 0, chip_8077 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, 0x8076,
		PCI_VENDOR_ID_ADAPTEC2, 0x0808, 0, 0, chip_8076 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, 0x8077,
		PCI_VENDOR_ID_ADAPTEC2, 0x0808, 0, 0, chip_8077 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, 0x8074,
		PCI_VENDOR_ID_ADAPTEC2, 0x0404, 0, 0, chip_8074 पूर्ण,
	अणु PCI_VENDOR_ID_ATTO, 0x8070,
		PCI_VENDOR_ID_ATTO, 0x0070, 0, 0, chip_8070 पूर्ण,
	अणु PCI_VENDOR_ID_ATTO, 0x8070,
		PCI_VENDOR_ID_ATTO, 0x0071, 0, 0, chip_8070 पूर्ण,
	अणु PCI_VENDOR_ID_ATTO, 0x8072,
		PCI_VENDOR_ID_ATTO, 0x0072, 0, 0, chip_8072 पूर्ण,
	अणु PCI_VENDOR_ID_ATTO, 0x8072,
		PCI_VENDOR_ID_ATTO, 0x0073, 0, 0, chip_8072 पूर्ण,
	अणु PCI_VENDOR_ID_ATTO, 0x8070,
		PCI_VENDOR_ID_ATTO, 0x0080, 0, 0, chip_8070 पूर्ण,
	अणु PCI_VENDOR_ID_ATTO, 0x8072,
		PCI_VENDOR_ID_ATTO, 0x0081, 0, 0, chip_8072 पूर्ण,
	अणु PCI_VENDOR_ID_ATTO, 0x8072,
		PCI_VENDOR_ID_ATTO, 0x0082, 0, 0, chip_8072 पूर्ण,
	अणुपूर्ण /* terminate list */
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(pm8001_pci_pm_ops,
			 pm8001_pci_suspend,
			 pm8001_pci_resume);

अटल काष्ठा pci_driver pm8001_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= pm8001_pci_table,
	.probe		= pm8001_pci_probe,
	.हटाओ		= pm8001_pci_हटाओ,
	.driver.pm	= &pm8001_pci_pm_ops,
पूर्ण;

/**
 *	pm8001_init - initialize scsi transport ढाँचा
 */
अटल पूर्णांक __init pm8001_init(व्योम)
अणु
	पूर्णांक rc = -ENOMEM;

	pm8001_wq = alloc_workqueue("pm80xx", 0, 0);
	अगर (!pm8001_wq)
		जाओ err;

	pm8001_id = 0;
	pm8001_stt = sas_करोमुख्य_attach_transport(&pm8001_transport_ops);
	अगर (!pm8001_stt)
		जाओ err_wq;
	rc = pci_रेजिस्टर_driver(&pm8001_pci_driver);
	अगर (rc)
		जाओ err_tp;
	वापस 0;

err_tp:
	sas_release_transport(pm8001_stt);
err_wq:
	destroy_workqueue(pm8001_wq);
err:
	वापस rc;
पूर्ण

अटल व्योम __निकास pm8001_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&pm8001_pci_driver);
	sas_release_transport(pm8001_stt);
	destroy_workqueue(pm8001_wq);
पूर्ण

module_init(pm8001_init);
module_निकास(pm8001_निकास);

MODULE_AUTHOR("Jack Wang <jack_wang@usish.com>");
MODULE_AUTHOR("Anand Kumar Santhanam <AnandKumar.Santhanam@pmcs.com>");
MODULE_AUTHOR("Sangeetha Gnanasekaran <Sangeetha.Gnanasekaran@pmcs.com>");
MODULE_AUTHOR("Nikith Ganigarakoppal <Nikith.Ganigarakoppal@pmcs.com>");
MODULE_DESCRIPTION(
		"PMC-Sierra PM8001/8006/8081/8088/8089/8074/8076/8077/8070/8072 "
		"SAS/SATA controller driver");
MODULE_VERSION(DRV_VERSION);
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, pm8001_pci_table);

