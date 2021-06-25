<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pmcraid.c -- driver क्रम PMC Sierra MaxRAID controller adapters
 *
 * Written By: Anil Ravindranath<anil_ravindranath@pmc-sierra.com>
 *             PMC-Sierra Inc
 *
 * Copyright (C) 2008, 2009 PMC Sierra Inc
 */
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/रुको.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/libata.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kसमय.स>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsicam.h>

#समावेश "pmcraid.h"

/*
 *   Module configuration parameters
 */
अटल अचिन्हित पूर्णांक pmcraid_debug_log;
अटल अचिन्हित पूर्णांक pmcraid_disable_aen;
अटल अचिन्हित पूर्णांक pmcraid_log_level = IOASC_LOG_LEVEL_MUST;
अटल अचिन्हित पूर्णांक pmcraid_enable_msix;

/*
 * Data काष्ठाures to support multiple adapters by the LLD.
 * pmcraid_adapter_count - count of configured adapters
 */
अटल atomic_t pmcraid_adapter_count = ATOMIC_INIT(0);

/*
 * Supporting user-level control पूर्णांकerface through IOCTL commands.
 * pmcraid_major - major number to use
 * pmcraid_minor - minor number(s) to use
 */
अटल अचिन्हित पूर्णांक pmcraid_major;
अटल काष्ठा class *pmcraid_class;
अटल DECLARE_BITMAP(pmcraid_minor, PMCRAID_MAX_ADAPTERS);

/*
 * Module parameters
 */
MODULE_AUTHOR("Anil Ravindranath<anil_ravindranath@pmc-sierra.com>");
MODULE_DESCRIPTION("PMC Sierra MaxRAID Controller Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(PMCRAID_DRIVER_VERSION);

module_param_named(log_level, pmcraid_log_level, uपूर्णांक, (S_IRUGO | S_IWUSR));
MODULE_PARM_DESC(log_level,
		 "Enables firmware error code logging, default :1 high-severity"
		 " errors, 2: all errors including high-severity errors,"
		 " 0: disables logging");

module_param_named(debug, pmcraid_debug_log, uपूर्णांक, (S_IRUGO | S_IWUSR));
MODULE_PARM_DESC(debug,
		 "Enable driver verbose message logging. Set 1 to enable."
		 "(default: 0)");

module_param_named(disable_aen, pmcraid_disable_aen, uपूर्णांक, (S_IRUGO | S_IWUSR));
MODULE_PARM_DESC(disable_aen,
		 "Disable driver aen notifications to apps. Set 1 to disable."
		 "(default: 0)");

/* chip specअगरic स्थिरants क्रम PMC MaxRAID controllers (same क्रम
 * 0x5220 and 0x8010
 */
अटल काष्ठा pmcraid_chip_details pmcraid_chip_cfg[] = अणु
	अणु
	 .ioastatus = 0x0,
	 .ioarrin = 0x00040,
	 .mailbox = 0x7FC30,
	 .global_पूर्णांकr_mask = 0x00034,
	 .ioa_host_पूर्णांकr = 0x0009C,
	 .ioa_host_पूर्णांकr_clr = 0x000A0,
	 .ioa_host_msix_पूर्णांकr = 0x7FC40,
	 .ioa_host_mask = 0x7FC28,
	 .ioa_host_mask_clr = 0x7FC28,
	 .host_ioa_पूर्णांकr = 0x00020,
	 .host_ioa_पूर्णांकr_clr = 0x00020,
	 .transop_समयout = 300
	 पूर्ण
पूर्ण;

/*
 * PCI device ids supported by pmcraid driver
 */
अटल काष्ठा pci_device_id pmcraid_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_PMC, PCI_DEVICE_ID_PMC_MAXRAID),
	  0, 0, (kernel_uदीर्घ_t)&pmcraid_chip_cfg[0]
	पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, pmcraid_pci_table);



/**
 * pmcraid_slave_alloc - Prepare क्रम commands to a device
 * @scsi_dev: scsi device काष्ठा
 *
 * This function is called by mid-layer prior to sending any command to the new
 * device. Stores resource entry details of the device in scsi_device काष्ठा.
 * Queuecommand uses the resource handle and other details to fill up IOARCB
 * जबतक sending commands to the device.
 *
 * Return value:
 *	  0 on success / -ENXIO अगर device करोes not exist
 */
अटल पूर्णांक pmcraid_slave_alloc(काष्ठा scsi_device *scsi_dev)
अणु
	काष्ठा pmcraid_resource_entry *temp, *res = शून्य;
	काष्ठा pmcraid_instance *pinstance;
	u8 target, bus, lun;
	अचिन्हित दीर्घ lock_flags;
	पूर्णांक rc = -ENXIO;
	u16 fw_version;

	pinstance = shost_priv(scsi_dev->host);

	fw_version = be16_to_cpu(pinstance->inq_data->fw_version);

	/* Driver exposes VSET and GSCSI resources only; all other device types
	 * are not exposed. Resource list is synchronized using resource lock
	 * so any traversal or modअगरications to the list should be करोne inside
	 * this lock
	 */
	spin_lock_irqsave(&pinstance->resource_lock, lock_flags);
	list_क्रम_each_entry(temp, &pinstance->used_res_q, queue) अणु

		/* करो not expose VSETs with order-ids > MAX_VSET_TARGETS */
		अगर (RES_IS_VSET(temp->cfg_entry)) अणु
			अगर (fw_version <= PMCRAID_FW_VERSION_1)
				target = temp->cfg_entry.unique_flags1;
			अन्यथा
				target = le16_to_cpu(temp->cfg_entry.array_id) & 0xFF;

			अगर (target > PMCRAID_MAX_VSET_TARGETS)
				जारी;
			bus = PMCRAID_VSET_BUS_ID;
			lun = 0;
		पूर्ण अन्यथा अगर (RES_IS_GSCSI(temp->cfg_entry)) अणु
			target = RES_TARGET(temp->cfg_entry.resource_address);
			bus = PMCRAID_PHYS_BUS_ID;
			lun = RES_LUN(temp->cfg_entry.resource_address);
		पूर्ण अन्यथा अणु
			जारी;
		पूर्ण

		अगर (bus == scsi_dev->channel &&
		    target == scsi_dev->id &&
		    lun == scsi_dev->lun) अणु
			res = temp;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (res) अणु
		res->scsi_dev = scsi_dev;
		scsi_dev->hostdata = res;
		res->change_detected = 0;
		atomic_set(&res->पढ़ो_failures, 0);
		atomic_set(&res->ग_लिखो_failures, 0);
		rc = 0;
	पूर्ण
	spin_unlock_irqrestore(&pinstance->resource_lock, lock_flags);
	वापस rc;
पूर्ण

/**
 * pmcraid_slave_configure - Configures a SCSI device
 * @scsi_dev: scsi device काष्ठा
 *
 * This function is executed by SCSI mid layer just after a device is first
 * scanned (i.e. it has responded to an INQUIRY). For VSET resources, the
 * समयout value (शेष 30s) will be over-written to a higher value (60s)
 * and max_sectors value will be over-written to 512. It also sets queue depth
 * to host->cmd_per_lun value
 *
 * Return value:
 *	  0 on success
 */
अटल पूर्णांक pmcraid_slave_configure(काष्ठा scsi_device *scsi_dev)
अणु
	काष्ठा pmcraid_resource_entry *res = scsi_dev->hostdata;

	अगर (!res)
		वापस 0;

	/* LLD exposes VSETs and Enclosure devices only */
	अगर (RES_IS_GSCSI(res->cfg_entry) &&
	    scsi_dev->type != TYPE_ENCLOSURE)
		वापस -ENXIO;

	pmcraid_info("configuring %x:%x:%x:%x\n",
		     scsi_dev->host->unique_id,
		     scsi_dev->channel,
		     scsi_dev->id,
		     (u8)scsi_dev->lun);

	अगर (RES_IS_GSCSI(res->cfg_entry)) अणु
		scsi_dev->allow_restart = 1;
	पूर्ण अन्यथा अगर (RES_IS_VSET(res->cfg_entry)) अणु
		scsi_dev->allow_restart = 1;
		blk_queue_rq_समयout(scsi_dev->request_queue,
				     PMCRAID_VSET_IO_TIMEOUT);
		blk_queue_max_hw_sectors(scsi_dev->request_queue,
				      PMCRAID_VSET_MAX_SECTORS);
	पूर्ण

	/*
	 * We never want to report TCQ support क्रम these types of devices.
	 */
	अगर (!RES_IS_GSCSI(res->cfg_entry) && !RES_IS_VSET(res->cfg_entry))
		scsi_dev->tagged_supported = 0;

	वापस 0;
पूर्ण

/**
 * pmcraid_slave_destroy - Unconfigure a SCSI device beक्रमe removing it
 *
 * @scsi_dev: scsi device काष्ठा
 *
 * This is called by mid-layer beक्रमe removing a device. Poपूर्णांकer assignments
 * करोne in pmcraid_slave_alloc will be reset to शून्य here.
 *
 * Return value
 *   none
 */
अटल व्योम pmcraid_slave_destroy(काष्ठा scsi_device *scsi_dev)
अणु
	काष्ठा pmcraid_resource_entry *res;

	res = (काष्ठा pmcraid_resource_entry *)scsi_dev->hostdata;

	अगर (res)
		res->scsi_dev = शून्य;

	scsi_dev->hostdata = शून्य;
पूर्ण

/**
 * pmcraid_change_queue_depth - Change the device's queue depth
 * @scsi_dev: scsi device काष्ठा
 * @depth: depth to set
 *
 * Return value
 *	actual depth set
 */
अटल पूर्णांक pmcraid_change_queue_depth(काष्ठा scsi_device *scsi_dev, पूर्णांक depth)
अणु
	अगर (depth > PMCRAID_MAX_CMD_PER_LUN)
		depth = PMCRAID_MAX_CMD_PER_LUN;
	वापस scsi_change_queue_depth(scsi_dev, depth);
पूर्ण

/**
 * pmcraid_init_cmdblk - initializes a command block
 *
 * @cmd: poपूर्णांकer to काष्ठा pmcraid_cmd to be initialized
 * @index: अगर >=0 first समय initialization; otherwise reinitialization
 *
 * Return Value
 *	 None
 */
अटल व्योम pmcraid_init_cmdblk(काष्ठा pmcraid_cmd *cmd, पूर्णांक index)
अणु
	काष्ठा pmcraid_ioarcb *ioarcb = &(cmd->ioa_cb->ioarcb);
	dma_addr_t dma_addr = cmd->ioa_cb_bus_addr;

	अगर (index >= 0) अणु
		/* first समय initialization (called from  probe) */
		u32 ioasa_offset =
			दुरत्व(काष्ठा pmcraid_control_block, ioasa);

		cmd->index = index;
		ioarcb->response_handle = cpu_to_le32(index << 2);
		ioarcb->ioarcb_bus_addr = cpu_to_le64(dma_addr);
		ioarcb->ioasa_bus_addr = cpu_to_le64(dma_addr + ioasa_offset);
		ioarcb->ioasa_len = cpu_to_le16(माप(काष्ठा pmcraid_ioasa));
	पूर्ण अन्यथा अणु
		/* re-initialization of various lengths, called once command is
		 * processed by IOA
		 */
		स_रखो(&cmd->ioa_cb->ioarcb.cdb, 0, PMCRAID_MAX_CDB_LEN);
		ioarcb->hrrq_id = 0;
		ioarcb->request_flags0 = 0;
		ioarcb->request_flags1 = 0;
		ioarcb->cmd_समयout = 0;
		ioarcb->ioarcb_bus_addr &= cpu_to_le64(~0x1FULL);
		ioarcb->ioadl_bus_addr = 0;
		ioarcb->ioadl_length = 0;
		ioarcb->data_transfer_length = 0;
		ioarcb->add_cmd_param_length = 0;
		ioarcb->add_cmd_param_offset = 0;
		cmd->ioa_cb->ioasa.ioasc = 0;
		cmd->ioa_cb->ioasa.residual_data_length = 0;
		cmd->समय_left = 0;
	पूर्ण

	cmd->cmd_करोne = शून्य;
	cmd->scsi_cmd = शून्य;
	cmd->release = 0;
	cmd->completion_req = 0;
	cmd->sense_buffer = शून्य;
	cmd->sense_buffer_dma = 0;
	cmd->dma_handle = 0;
	समयr_setup(&cmd->समयr, शून्य, 0);
पूर्ण

/**
 * pmcraid_reinit_cmdblk - reinitialize a command block
 *
 * @cmd: poपूर्णांकer to काष्ठा pmcraid_cmd to be reinitialized
 *
 * Return Value
 *	 None
 */
अटल व्योम pmcraid_reinit_cmdblk(काष्ठा pmcraid_cmd *cmd)
अणु
	pmcraid_init_cmdblk(cmd, -1);
पूर्ण

/**
 * pmcraid_get_मुक्त_cmd - get a मुक्त cmd block from command block pool
 * @pinstance: adapter instance काष्ठाure
 *
 * Return Value:
 *	वापसs poपूर्णांकer to cmd block or शून्य अगर no blocks are available
 */
अटल काष्ठा pmcraid_cmd *pmcraid_get_मुक्त_cmd(
	काष्ठा pmcraid_instance *pinstance
)
अणु
	काष्ठा pmcraid_cmd *cmd = शून्य;
	अचिन्हित दीर्घ lock_flags;

	/* मुक्त cmd block list is रक्षित by मुक्त_pool_lock */
	spin_lock_irqsave(&pinstance->मुक्त_pool_lock, lock_flags);

	अगर (!list_empty(&pinstance->मुक्त_cmd_pool)) अणु
		cmd = list_entry(pinstance->मुक्त_cmd_pool.next,
				 काष्ठा pmcraid_cmd, मुक्त_list);
		list_del(&cmd->मुक्त_list);
	पूर्ण
	spin_unlock_irqrestore(&pinstance->मुक्त_pool_lock, lock_flags);

	/* Initialize the command block beक्रमe giving it the caller */
	अगर (cmd != शून्य)
		pmcraid_reinit_cmdblk(cmd);
	वापस cmd;
पूर्ण

/**
 * pmcraid_वापस_cmd - वापस a completed command block back पूर्णांकo मुक्त pool
 * @cmd: poपूर्णांकer to the command block
 *
 * Return Value:
 *	nothing
 */
अटल व्योम pmcraid_वापस_cmd(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;
	अचिन्हित दीर्घ lock_flags;

	spin_lock_irqsave(&pinstance->मुक्त_pool_lock, lock_flags);
	list_add_tail(&cmd->मुक्त_list, &pinstance->मुक्त_cmd_pool);
	spin_unlock_irqrestore(&pinstance->मुक्त_pool_lock, lock_flags);
पूर्ण

/**
 * pmcraid_पढ़ो_पूर्णांकerrupts -  पढ़ोs IOA पूर्णांकerrupts
 *
 * @pinstance: poपूर्णांकer to adapter instance काष्ठाure
 *
 * Return value
 *	 पूर्णांकerrupts पढ़ो from IOA
 */
अटल u32 pmcraid_पढ़ो_पूर्णांकerrupts(काष्ठा pmcraid_instance *pinstance)
अणु
	वापस (pinstance->पूर्णांकerrupt_mode) ?
		ioपढ़ो32(pinstance->पूर्णांक_regs.ioa_host_msix_पूर्णांकerrupt_reg) :
		ioपढ़ो32(pinstance->पूर्णांक_regs.ioa_host_पूर्णांकerrupt_reg);
पूर्ण

/**
 * pmcraid_disable_पूर्णांकerrupts - Masks and clears all specअगरied पूर्णांकerrupts
 *
 * @pinstance: poपूर्णांकer to per adapter instance काष्ठाure
 * @पूर्णांकrs: पूर्णांकerrupts to disable
 *
 * Return Value
 *	 None
 */
अटल व्योम pmcraid_disable_पूर्णांकerrupts(
	काष्ठा pmcraid_instance *pinstance,
	u32 पूर्णांकrs
)
अणु
	u32 gmask = ioपढ़ो32(pinstance->पूर्णांक_regs.global_पूर्णांकerrupt_mask_reg);
	u32 nmask = gmask | GLOBAL_INTERRUPT_MASK;

	ioग_लिखो32(पूर्णांकrs, pinstance->पूर्णांक_regs.ioa_host_पूर्णांकerrupt_clr_reg);
	ioग_लिखो32(nmask, pinstance->पूर्णांक_regs.global_पूर्णांकerrupt_mask_reg);
	ioपढ़ो32(pinstance->पूर्णांक_regs.global_पूर्णांकerrupt_mask_reg);

	अगर (!pinstance->पूर्णांकerrupt_mode) अणु
		ioग_लिखो32(पूर्णांकrs,
			pinstance->पूर्णांक_regs.ioa_host_पूर्णांकerrupt_mask_reg);
		ioपढ़ो32(pinstance->पूर्णांक_regs.ioa_host_पूर्णांकerrupt_mask_reg);
	पूर्ण
पूर्ण

/**
 * pmcraid_enable_पूर्णांकerrupts - Enables specअगरied पूर्णांकerrupts
 *
 * @pinstance: poपूर्णांकer to per adapter instance काष्ठाure
 * @पूर्णांकrs: पूर्णांकerrupts to enable
 *
 * Return Value
 *	 None
 */
अटल व्योम pmcraid_enable_पूर्णांकerrupts(
	काष्ठा pmcraid_instance *pinstance,
	u32 पूर्णांकrs)
अणु
	u32 gmask = ioपढ़ो32(pinstance->पूर्णांक_regs.global_पूर्णांकerrupt_mask_reg);
	u32 nmask = gmask & (~GLOBAL_INTERRUPT_MASK);

	ioग_लिखो32(nmask, pinstance->पूर्णांक_regs.global_पूर्णांकerrupt_mask_reg);

	अगर (!pinstance->पूर्णांकerrupt_mode) अणु
		ioग_लिखो32(~पूर्णांकrs,
			 pinstance->पूर्णांक_regs.ioa_host_पूर्णांकerrupt_mask_reg);
		ioपढ़ो32(pinstance->पूर्णांक_regs.ioa_host_पूर्णांकerrupt_mask_reg);
	पूर्ण

	pmcraid_info("enabled interrupts global mask = %x intr_mask = %x\n",
		ioपढ़ो32(pinstance->पूर्णांक_regs.global_पूर्णांकerrupt_mask_reg),
		ioपढ़ो32(pinstance->पूर्णांक_regs.ioa_host_पूर्णांकerrupt_mask_reg));
पूर्ण

/**
 * pmcraid_clr_trans_op - clear trans to op पूर्णांकerrupt
 *
 * @pinstance: poपूर्णांकer to per adapter instance काष्ठाure
 *
 * Return Value
 *	 None
 */
अटल व्योम pmcraid_clr_trans_op(
	काष्ठा pmcraid_instance *pinstance
)
अणु
	अचिन्हित दीर्घ lock_flags;

	अगर (!pinstance->पूर्णांकerrupt_mode) अणु
		ioग_लिखो32(INTRS_TRANSITION_TO_OPERATIONAL,
			pinstance->पूर्णांक_regs.ioa_host_पूर्णांकerrupt_mask_reg);
		ioपढ़ो32(pinstance->पूर्णांक_regs.ioa_host_पूर्णांकerrupt_mask_reg);
		ioग_लिखो32(INTRS_TRANSITION_TO_OPERATIONAL,
			pinstance->पूर्णांक_regs.ioa_host_पूर्णांकerrupt_clr_reg);
		ioपढ़ो32(pinstance->पूर्णांक_regs.ioa_host_पूर्णांकerrupt_clr_reg);
	पूर्ण

	अगर (pinstance->reset_cmd != शून्य) अणु
		del_समयr(&pinstance->reset_cmd->समयr);
		spin_lock_irqsave(
			pinstance->host->host_lock, lock_flags);
		pinstance->reset_cmd->cmd_करोne(pinstance->reset_cmd);
		spin_unlock_irqrestore(
			pinstance->host->host_lock, lock_flags);
	पूर्ण
पूर्ण

/**
 * pmcraid_reset_type - Determine the required reset type
 * @pinstance: poपूर्णांकer to adapter instance काष्ठाure
 *
 * IOA requires hard reset अगर any of the following conditions is true.
 * 1. If HRRQ valid पूर्णांकerrupt is not masked
 * 2. IOA reset alert करोorbell is set
 * 3. If there are any error पूर्णांकerrupts
 */
अटल व्योम pmcraid_reset_type(काष्ठा pmcraid_instance *pinstance)
अणु
	u32 mask;
	u32 पूर्णांकrs;
	u32 alerts;

	mask = ioपढ़ो32(pinstance->पूर्णांक_regs.ioa_host_पूर्णांकerrupt_mask_reg);
	पूर्णांकrs = ioपढ़ो32(pinstance->पूर्णांक_regs.ioa_host_पूर्णांकerrupt_reg);
	alerts = ioपढ़ो32(pinstance->पूर्णांक_regs.host_ioa_पूर्णांकerrupt_reg);

	अगर ((mask & INTRS_HRRQ_VALID) == 0 ||
	    (alerts & DOORBELL_IOA_RESET_ALERT) ||
	    (पूर्णांकrs & PMCRAID_ERROR_INTERRUPTS)) अणु
		pmcraid_info("IOA requires hard reset\n");
		pinstance->ioa_hard_reset = 1;
	पूर्ण

	/* If unit check is active, trigger the dump */
	अगर (पूर्णांकrs & INTRS_IOA_UNIT_CHECK)
		pinstance->ioa_unit_check = 1;
पूर्ण

अटल व्योम pmcraid_ioa_reset(काष्ठा pmcraid_cmd *);
/**
 * pmcraid_bist_करोne - completion function क्रम PCI BIST
 * @t: poपूर्णांकer to reset command
 * Return Value
 *	none
 */
अटल व्योम pmcraid_bist_करोne(काष्ठा समयr_list *t)
अणु
	काष्ठा pmcraid_cmd *cmd = from_समयr(cmd, t, समयr);
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;
	अचिन्हित दीर्घ lock_flags;
	पूर्णांक rc;
	u16 pci_reg;

	rc = pci_पढ़ो_config_word(pinstance->pdev, PCI_COMMAND, &pci_reg);

	/* If PCI config space can't be accessed रुको क्रम another two secs */
	अगर ((rc != PCIBIOS_SUCCESSFUL || (!(pci_reg & PCI_COMMAND_MEMORY))) &&
	    cmd->समय_left > 0) अणु
		pmcraid_info("BIST not complete, waiting another 2 secs\n");
		cmd->समयr.expires = jअगरfies + cmd->समय_left;
		cmd->समय_left = 0;
		add_समयr(&cmd->समयr);
	पूर्ण अन्यथा अणु
		cmd->समय_left = 0;
		pmcraid_info("BIST is complete, proceeding with reset\n");
		spin_lock_irqsave(pinstance->host->host_lock, lock_flags);
		pmcraid_ioa_reset(cmd);
		spin_unlock_irqrestore(pinstance->host->host_lock, lock_flags);
	पूर्ण
पूर्ण

/**
 * pmcraid_start_bist - starts BIST
 * @cmd: poपूर्णांकer to reset cmd
 * Return Value
 *   none
 */
अटल व्योम pmcraid_start_bist(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;
	u32 करोorbells, पूर्णांकrs;

	/* proceed with bist and रुको क्रम 2 seconds */
	ioग_लिखो32(DOORBELL_IOA_START_BIST,
		pinstance->पूर्णांक_regs.host_ioa_पूर्णांकerrupt_reg);
	करोorbells = ioपढ़ो32(pinstance->पूर्णांक_regs.host_ioa_पूर्णांकerrupt_reg);
	पूर्णांकrs = ioपढ़ो32(pinstance->पूर्णांक_regs.ioa_host_पूर्णांकerrupt_reg);
	pmcraid_info("doorbells after start bist: %x intrs: %x\n",
		      करोorbells, पूर्णांकrs);

	cmd->समय_left = msecs_to_jअगरfies(PMCRAID_BIST_TIMEOUT);
	cmd->समयr.expires = jअगरfies + msecs_to_jअगरfies(PMCRAID_BIST_TIMEOUT);
	cmd->समयr.function = pmcraid_bist_करोne;
	add_समयr(&cmd->समयr);
पूर्ण

/**
 * pmcraid_reset_alert_करोne - completion routine क्रम reset_alert
 * @t: poपूर्णांकer to command block used in reset sequence
 * Return value
 *  None
 */
अटल व्योम pmcraid_reset_alert_करोne(काष्ठा समयr_list *t)
अणु
	काष्ठा pmcraid_cmd *cmd = from_समयr(cmd, t, समयr);
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;
	u32 status = ioपढ़ो32(pinstance->ioa_status);
	अचिन्हित दीर्घ lock_flags;

	/* अगर the critical operation in progress bit is set or the रुको बार
	 * out, invoke reset engine to proceed with hard reset. If there is
	 * some more समय to रुको, restart the समयr
	 */
	अगर (((status & INTRS_CRITICAL_OP_IN_PROGRESS) == 0) ||
	    cmd->समय_left <= 0) अणु
		pmcraid_info("critical op is reset proceeding with reset\n");
		spin_lock_irqsave(pinstance->host->host_lock, lock_flags);
		pmcraid_ioa_reset(cmd);
		spin_unlock_irqrestore(pinstance->host->host_lock, lock_flags);
	पूर्ण अन्यथा अणु
		pmcraid_info("critical op is not yet reset waiting again\n");
		/* restart समयr अगर some more समय is available to रुको */
		cmd->समय_left -= PMCRAID_CHECK_FOR_RESET_TIMEOUT;
		cmd->समयr.expires = jअगरfies + PMCRAID_CHECK_FOR_RESET_TIMEOUT;
		cmd->समयr.function = pmcraid_reset_alert_करोne;
		add_समयr(&cmd->समयr);
	पूर्ण
पूर्ण

अटल व्योम pmcraid_notअगरy_ioastate(काष्ठा pmcraid_instance *, u32);
/**
 * pmcraid_reset_alert - alerts IOA क्रम a possible reset
 * @cmd: command block to be used क्रम reset sequence.
 *
 * Return Value
 *	वापसs 0 अगर pci config-space is accessible and RESET_DOORBELL is
 *	successfully written to IOA. Returns non-zero in हाल pci_config_space
 *	is not accessible
 */
अटल व्योम pmcraid_reset_alert(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;
	u32 करोorbells;
	पूर्णांक rc;
	u16 pci_reg;

	/* If we are able to access IOA PCI config space, alert IOA that we are
	 * going to reset it soon. This enables IOA to preserv persistent error
	 * data अगर any. In हाल memory space is not accessible, proceed with
	 * BIST or slot_reset
	 */
	rc = pci_पढ़ो_config_word(pinstance->pdev, PCI_COMMAND, &pci_reg);
	अगर ((rc == PCIBIOS_SUCCESSFUL) && (pci_reg & PCI_COMMAND_MEMORY)) अणु

		/* रुको क्रम IOA permission i.e until CRITICAL_OPERATION bit is
		 * reset IOA करोesn't generate any पूर्णांकerrupts when CRITICAL
		 * OPERATION bit is reset. A समयr is started to रुको क्रम this
		 * bit to be reset.
		 */
		cmd->समय_left = PMCRAID_RESET_TIMEOUT;
		cmd->समयr.expires = jअगरfies + PMCRAID_CHECK_FOR_RESET_TIMEOUT;
		cmd->समयr.function = pmcraid_reset_alert_करोne;
		add_समयr(&cmd->समयr);

		ioग_लिखो32(DOORBELL_IOA_RESET_ALERT,
			pinstance->पूर्णांक_regs.host_ioa_पूर्णांकerrupt_reg);
		करोorbells =
			ioपढ़ो32(pinstance->पूर्णांक_regs.host_ioa_पूर्णांकerrupt_reg);
		pmcraid_info("doorbells after reset alert: %x\n", करोorbells);
	पूर्ण अन्यथा अणु
		pmcraid_info("PCI config is not accessible starting BIST\n");
		pinstance->ioa_state = IOA_STATE_IN_HARD_RESET;
		pmcraid_start_bist(cmd);
	पूर्ण
पूर्ण

/**
 * pmcraid_समयout_handler -  Timeout handler क्रम पूर्णांकernally generated ops
 *
 * @t: poपूर्णांकer to command काष्ठाure, that got समयकरोut
 *
 * This function blocks host requests and initiates an adapter reset.
 *
 * Return value:
 *   None
 */
अटल व्योम pmcraid_समयout_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा pmcraid_cmd *cmd = from_समयr(cmd, t, समयr);
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;
	अचिन्हित दीर्घ lock_flags;

	dev_info(&pinstance->pdev->dev,
		"Adapter being reset due to cmd(CDB[0] = %x) timeout\n",
		cmd->ioa_cb->ioarcb.cdb[0]);

	/* Command समयouts result in hard reset sequence. The command that got
	 * समयd out may be the one used as part of reset sequence. In this
	 * हाल restart reset sequence using the same command block even अगर
	 * reset is in progress. Otherwise fail this command and get a मुक्त
	 * command block to restart the reset sequence.
	 */
	spin_lock_irqsave(pinstance->host->host_lock, lock_flags);
	अगर (!pinstance->ioa_reset_in_progress) अणु
		pinstance->ioa_reset_attempts = 0;
		cmd = pmcraid_get_मुक्त_cmd(pinstance);

		/* If we are out of command blocks, just वापस here itself.
		 * Some other command's समयout handler can करो the reset job
		 */
		अगर (cmd == शून्य) अणु
			spin_unlock_irqrestore(pinstance->host->host_lock,
					       lock_flags);
			pmcraid_err("no free cmnd block for timeout handler\n");
			वापस;
		पूर्ण

		pinstance->reset_cmd = cmd;
		pinstance->ioa_reset_in_progress = 1;
	पूर्ण अन्यथा अणु
		pmcraid_info("reset is already in progress\n");

		अगर (pinstance->reset_cmd != cmd) अणु
			/* This command should have been given to IOA, this
			 * command will be completed by fail_outstanding_cmds
			 * anyway
			 */
			pmcraid_err("cmd is pending but reset in progress\n");
		पूर्ण

		/* If this command was being used as part of the reset
		 * sequence, set cmd_करोne poपूर्णांकer to pmcraid_ioa_reset. This
		 * causes fail_outstanding_commands not to वापस the command
		 * block back to मुक्त pool
		 */
		अगर (cmd == pinstance->reset_cmd)
			cmd->cmd_करोne = pmcraid_ioa_reset;
	पूर्ण

	/* Notअगरy apps of important IOA bringup/bringकरोwn sequences */
	अगर (pinstance->scn.ioa_state != PMC_DEVICE_EVENT_RESET_START &&
	    pinstance->scn.ioa_state != PMC_DEVICE_EVENT_SHUTDOWN_START)
		pmcraid_notअगरy_ioastate(pinstance,
					PMC_DEVICE_EVENT_RESET_START);

	pinstance->ioa_state = IOA_STATE_IN_RESET_ALERT;
	scsi_block_requests(pinstance->host);
	pmcraid_reset_alert(cmd);
	spin_unlock_irqrestore(pinstance->host->host_lock, lock_flags);
पूर्ण

/**
 * pmcraid_पूर्णांकernal_करोne - completion routine क्रम पूर्णांकernally generated cmds
 *
 * @cmd: command that got response from IOA
 *
 * Return Value:
 *	 none
 */
अटल व्योम pmcraid_पूर्णांकernal_करोne(काष्ठा pmcraid_cmd *cmd)
अणु
	pmcraid_info("response internal cmd CDB[0] = %x ioasc = %x\n",
		     cmd->ioa_cb->ioarcb.cdb[0],
		     le32_to_cpu(cmd->ioa_cb->ioasa.ioasc));

	/* Some of the पूर्णांकernal commands are sent with callers blocking क्रम the
	 * response. Same will be indicated as part of cmd->completion_req
	 * field. Response path needs to wake up any रुकोers रुकोing क्रम cmd
	 * completion अगर this flag is set.
	 */
	अगर (cmd->completion_req) अणु
		cmd->completion_req = 0;
		complete(&cmd->रुको_क्रम_completion);
	पूर्ण

	/* most of the पूर्णांकernal commands are completed by caller itself, so
	 * no need to वापस the command block back to मुक्त pool until we are
	 * required to करो so (e.g once करोne with initialization).
	 */
	अगर (cmd->release) अणु
		cmd->release = 0;
		pmcraid_वापस_cmd(cmd);
	पूर्ण
पूर्ण

/**
 * pmcraid_reinit_cfgtable_करोne - करोne function क्रम cfg table reinitialization
 *
 * @cmd: command that got response from IOA
 *
 * This routine is called after driver re-पढ़ोs configuration table due to a
 * lost CCN. It वापसs the command block back to मुक्त pool and schedules
 * worker thपढ़ो to add/delete devices पूर्णांकo the प्रणाली.
 *
 * Return Value:
 *	 none
 */
अटल व्योम pmcraid_reinit_cfgtable_करोne(काष्ठा pmcraid_cmd *cmd)
अणु
	pmcraid_info("response internal cmd CDB[0] = %x ioasc = %x\n",
		     cmd->ioa_cb->ioarcb.cdb[0],
		     le32_to_cpu(cmd->ioa_cb->ioasa.ioasc));

	अगर (cmd->release) अणु
		cmd->release = 0;
		pmcraid_वापस_cmd(cmd);
	पूर्ण
	pmcraid_info("scheduling worker for config table reinitialization\n");
	schedule_work(&cmd->drv_inst->worker_q);
पूर्ण

/**
 * pmcraid_erp_करोne - Process completion of SCSI error response from device
 * @cmd: pmcraid_command
 *
 * This function copies the sense buffer पूर्णांकo the scsi_cmd काष्ठा and completes
 * scsi_cmd by calling scsi_करोne function.
 *
 * Return value:
 *  none
 */
अटल व्योम pmcraid_erp_करोne(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा scsi_cmnd *scsi_cmd = cmd->scsi_cmd;
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;
	u32 ioasc = le32_to_cpu(cmd->ioa_cb->ioasa.ioasc);

	अगर (PMCRAID_IOASC_SENSE_KEY(ioasc) > 0) अणु
		scsi_cmd->result |= (DID_ERROR << 16);
		scmd_prपूर्णांकk(KERN_INFO, scsi_cmd,
			    "command CDB[0] = %x failed with IOASC: 0x%08X\n",
			    cmd->ioa_cb->ioarcb.cdb[0], ioasc);
	पूर्ण

	अगर (cmd->sense_buffer) अणु
		dma_unmap_single(&pinstance->pdev->dev, cmd->sense_buffer_dma,
				 SCSI_SENSE_BUFFERSIZE, DMA_FROM_DEVICE);
		cmd->sense_buffer = शून्य;
		cmd->sense_buffer_dma = 0;
	पूर्ण

	scsi_dma_unmap(scsi_cmd);
	pmcraid_वापस_cmd(cmd);
	scsi_cmd->scsi_करोne(scsi_cmd);
पूर्ण

/**
 * _pmcraid_fire_command - sends an IOA command to adapter
 *
 * This function adds the given block पूर्णांकo pending command list
 * and वापसs without रुकोing
 *
 * @cmd : command to be sent to the device
 *
 * Return Value
 *	None
 */
अटल व्योम _pmcraid_fire_command(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;
	अचिन्हित दीर्घ lock_flags;

	/* Add this command block to pending cmd pool. We करो this prior to
	 * writting IOARCB to ioarrin because IOA might complete the command
	 * by the समय we are about to add it to the list. Response handler
	 * (isr/tasklet) looks क्रम cmd block in the pending pending list.
	 */
	spin_lock_irqsave(&pinstance->pending_pool_lock, lock_flags);
	list_add_tail(&cmd->मुक्त_list, &pinstance->pending_cmd_pool);
	spin_unlock_irqrestore(&pinstance->pending_pool_lock, lock_flags);
	atomic_inc(&pinstance->outstanding_cmds);

	/* driver ग_लिखोs lower 32-bit value of IOARCB address only */
	mb();
	ioग_लिखो32(le64_to_cpu(cmd->ioa_cb->ioarcb.ioarcb_bus_addr), pinstance->ioarrin);
पूर्ण

/**
 * pmcraid_send_cmd - fires a command to IOA
 *
 * This function also sets up समयout function, and command completion
 * function
 *
 * @cmd: poपूर्णांकer to the command block to be fired to IOA
 * @cmd_करोne: command completion function, called once IOA responds
 * @समयout: समयout to रुको क्रम this command completion
 * @समयout_func: समयout handler
 *
 * Return value
 *   none
 */
अटल व्योम pmcraid_send_cmd(
	काष्ठा pmcraid_cmd *cmd,
	व्योम (*cmd_करोne) (काष्ठा pmcraid_cmd *),
	अचिन्हित दीर्घ समयout,
	व्योम (*समयout_func) (काष्ठा समयr_list *)
)
अणु
	/* initialize करोne function */
	cmd->cmd_करोne = cmd_करोne;

	अगर (समयout_func) अणु
		/* setup समयout handler */
		cmd->समयr.expires = jअगरfies + समयout;
		cmd->समयr.function = समयout_func;
		add_समयr(&cmd->समयr);
	पूर्ण

	/* fire the command to IOA */
	_pmcraid_fire_command(cmd);
पूर्ण

/**
 * pmcraid_ioa_shutकरोwn_करोne - completion function क्रम IOA shutकरोwn command
 * @cmd: poपूर्णांकer to the command block used क्रम sending IOA shutकरोwn command
 *
 * Return value
 *  None
 */
अटल व्योम pmcraid_ioa_shutकरोwn_करोne(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;
	अचिन्हित दीर्घ lock_flags;

	spin_lock_irqsave(pinstance->host->host_lock, lock_flags);
	pmcraid_ioa_reset(cmd);
	spin_unlock_irqrestore(pinstance->host->host_lock, lock_flags);
पूर्ण

/**
 * pmcraid_ioa_shutकरोwn - sends SHUTDOWN command to ioa
 *
 * @cmd: poपूर्णांकer to the command block used as part of reset sequence
 *
 * Return Value
 *  None
 */
अटल व्योम pmcraid_ioa_shutकरोwn(काष्ठा pmcraid_cmd *cmd)
अणु
	pmcraid_info("response for Cancel CCN CDB[0] = %x ioasc = %x\n",
		     cmd->ioa_cb->ioarcb.cdb[0],
		     le32_to_cpu(cmd->ioa_cb->ioasa.ioasc));

	/* Note that commands sent during reset require next command to be sent
	 * to IOA. Hence reinit the करोne function as well as समयout function
	 */
	pmcraid_reinit_cmdblk(cmd);
	cmd->ioa_cb->ioarcb.request_type = REQ_TYPE_IOACMD;
	cmd->ioa_cb->ioarcb.resource_handle =
		cpu_to_le32(PMCRAID_IOA_RES_HANDLE);
	cmd->ioa_cb->ioarcb.cdb[0] = PMCRAID_IOA_SHUTDOWN;
	cmd->ioa_cb->ioarcb.cdb[1] = PMCRAID_SHUTDOWN_NORMAL;

	/* fire shutकरोwn command to hardware. */
	pmcraid_info("firing normal shutdown command (%d) to IOA\n",
		     le32_to_cpu(cmd->ioa_cb->ioarcb.response_handle));

	pmcraid_notअगरy_ioastate(cmd->drv_inst, PMC_DEVICE_EVENT_SHUTDOWN_START);

	pmcraid_send_cmd(cmd, pmcraid_ioa_shutकरोwn_करोne,
			 PMCRAID_SHUTDOWN_TIMEOUT,
			 pmcraid_समयout_handler);
पूर्ण

अटल व्योम pmcraid_querycfg(काष्ठा pmcraid_cmd *);
/**
 * pmcraid_get_fwversion_करोne - completion function क्रम get_fwversion
 *
 * @cmd: poपूर्णांकer to command block used to send INQUIRY command
 *
 * Return Value
 *	none
 */
अटल व्योम pmcraid_get_fwversion_करोne(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;
	u32 ioasc = le32_to_cpu(cmd->ioa_cb->ioasa.ioasc);
	अचिन्हित दीर्घ lock_flags;

	/* configuration table entry size depends on firmware version. If fw
	 * version is not known, it is not possible to पूर्णांकerpret IOA config
	 * table
	 */
	अगर (ioasc) अणु
		pmcraid_err("IOA Inquiry failed with %x\n", ioasc);
		spin_lock_irqsave(pinstance->host->host_lock, lock_flags);
		pinstance->ioa_state = IOA_STATE_IN_RESET_ALERT;
		pmcraid_reset_alert(cmd);
		spin_unlock_irqrestore(pinstance->host->host_lock, lock_flags);
	पूर्ण अन्यथा  अणु
		pmcraid_querycfg(cmd);
	पूर्ण
पूर्ण

/**
 * pmcraid_get_fwversion - पढ़ोs firmware version inक्रमmation
 *
 * @cmd: poपूर्णांकer to command block used to send INQUIRY command
 *
 * Return Value
 *	none
 */
अटल व्योम pmcraid_get_fwversion(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा pmcraid_ioarcb *ioarcb = &cmd->ioa_cb->ioarcb;
	काष्ठा pmcraid_ioadl_desc *ioadl;
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;
	u16 data_size = माप(काष्ठा pmcraid_inquiry_data);

	pmcraid_reinit_cmdblk(cmd);
	ioarcb->request_type = REQ_TYPE_SCSI;
	ioarcb->resource_handle = cpu_to_le32(PMCRAID_IOA_RES_HANDLE);
	ioarcb->cdb[0] = INQUIRY;
	ioarcb->cdb[1] = 1;
	ioarcb->cdb[2] = 0xD0;
	ioarcb->cdb[3] = (data_size >> 8) & 0xFF;
	ioarcb->cdb[4] = data_size & 0xFF;

	/* Since entire inquiry data it can be part of IOARCB itself
	 */
	ioarcb->ioadl_bus_addr = cpu_to_le64((cmd->ioa_cb_bus_addr) +
					दुरत्व(काष्ठा pmcraid_ioarcb,
						add_data.u.ioadl[0]));
	ioarcb->ioadl_length = cpu_to_le32(माप(काष्ठा pmcraid_ioadl_desc));
	ioarcb->ioarcb_bus_addr &= cpu_to_le64(~(0x1FULL));

	ioarcb->request_flags0 |= NO_LINK_DESCS;
	ioarcb->data_transfer_length = cpu_to_le32(data_size);
	ioadl = &(ioarcb->add_data.u.ioadl[0]);
	ioadl->flags = IOADL_FLAGS_LAST_DESC;
	ioadl->address = cpu_to_le64(pinstance->inq_data_baddr);
	ioadl->data_len = cpu_to_le32(data_size);

	pmcraid_send_cmd(cmd, pmcraid_get_fwversion_करोne,
			 PMCRAID_INTERNAL_TIMEOUT, pmcraid_समयout_handler);
पूर्ण

/**
 * pmcraid_identअगरy_hrrq - रेजिस्टरs host rrq buffers with IOA
 * @cmd: poपूर्णांकer to command block to be used क्रम identअगरy hrrq
 *
 * Return Value
 *	 none
 */
अटल व्योम pmcraid_identअगरy_hrrq(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;
	काष्ठा pmcraid_ioarcb *ioarcb = &cmd->ioa_cb->ioarcb;
	पूर्णांक index = cmd->hrrq_index;
	__be64 hrrq_addr = cpu_to_be64(pinstance->hrrq_start_bus_addr[index]);
	__be32 hrrq_size = cpu_to_be32(माप(u32) * PMCRAID_MAX_CMD);
	व्योम (*करोne_function)(काष्ठा pmcraid_cmd *);

	pmcraid_reinit_cmdblk(cmd);
	cmd->hrrq_index = index + 1;

	अगर (cmd->hrrq_index < pinstance->num_hrrq) अणु
		करोne_function = pmcraid_identअगरy_hrrq;
	पूर्ण अन्यथा अणु
		cmd->hrrq_index = 0;
		करोne_function = pmcraid_get_fwversion;
	पूर्ण

	/* Initialize ioarcb */
	ioarcb->request_type = REQ_TYPE_IOACMD;
	ioarcb->resource_handle = cpu_to_le32(PMCRAID_IOA_RES_HANDLE);

	/* initialize the hrrq number where IOA will respond to this command */
	ioarcb->hrrq_id = index;
	ioarcb->cdb[0] = PMCRAID_IDENTIFY_HRRQ;
	ioarcb->cdb[1] = index;

	/* IOA expects 64-bit pci address to be written in B.E क्रमmat
	 * (i.e cdb[2]=MSByte..cdb[9]=LSB.
	 */
	pmcraid_info("HRRQ_IDENTIFY with hrrq:ioarcb:index => %llx:%llx:%x\n",
		     hrrq_addr, ioarcb->ioarcb_bus_addr, index);

	स_नकल(&(ioarcb->cdb[2]), &hrrq_addr, माप(hrrq_addr));
	स_नकल(&(ioarcb->cdb[10]), &hrrq_size, माप(hrrq_size));

	/* Subsequent commands require HRRQ identअगरication to be successful.
	 * Note that this माला_लो called even during reset from SCSI mid-layer
	 * or tasklet
	 */
	pmcraid_send_cmd(cmd, करोne_function,
			 PMCRAID_INTERNAL_TIMEOUT,
			 pmcraid_समयout_handler);
पूर्ण

अटल व्योम pmcraid_process_ccn(काष्ठा pmcraid_cmd *cmd);
अटल व्योम pmcraid_process_ldn(काष्ठा pmcraid_cmd *cmd);

/**
 * pmcraid_send_hcam_cmd - send an initialized command block(HCAM) to IOA
 *
 * @cmd: initialized command block poपूर्णांकer
 *
 * Return Value
 *   none
 */
अटल व्योम pmcraid_send_hcam_cmd(काष्ठा pmcraid_cmd *cmd)
अणु
	अगर (cmd->ioa_cb->ioarcb.cdb[1] == PMCRAID_HCAM_CODE_CONFIG_CHANGE)
		atomic_set(&(cmd->drv_inst->ccn.ignore), 0);
	अन्यथा
		atomic_set(&(cmd->drv_inst->ldn.ignore), 0);

	pmcraid_send_cmd(cmd, cmd->cmd_करोne, 0, शून्य);
पूर्ण

/**
 * pmcraid_init_hcam - send an initialized command block(HCAM) to IOA
 *
 * @pinstance: poपूर्णांकer to adapter instance काष्ठाure
 * @type: HCAM type
 *
 * Return Value
 *   poपूर्णांकer to initialized pmcraid_cmd काष्ठाure or शून्य
 */
अटल काष्ठा pmcraid_cmd *pmcraid_init_hcam
(
	काष्ठा pmcraid_instance *pinstance,
	u8 type
)
अणु
	काष्ठा pmcraid_cmd *cmd;
	काष्ठा pmcraid_ioarcb *ioarcb;
	काष्ठा pmcraid_ioadl_desc *ioadl;
	काष्ठा pmcraid_hostrcb *hcam;
	व्योम (*cmd_करोne) (काष्ठा pmcraid_cmd *);
	dma_addr_t dma;
	पूर्णांक rcb_size;

	cmd = pmcraid_get_मुक्त_cmd(pinstance);

	अगर (!cmd) अणु
		pmcraid_err("no free command blocks for hcam\n");
		वापस cmd;
	पूर्ण

	अगर (type == PMCRAID_HCAM_CODE_CONFIG_CHANGE) अणु
		rcb_size = माप(काष्ठा pmcraid_hcam_ccn_ext);
		cmd_करोne = pmcraid_process_ccn;
		dma = pinstance->ccn.baddr + PMCRAID_AEN_HDR_SIZE;
		hcam = &pinstance->ccn;
	पूर्ण अन्यथा अणु
		rcb_size = माप(काष्ठा pmcraid_hcam_ldn);
		cmd_करोne = pmcraid_process_ldn;
		dma = pinstance->ldn.baddr + PMCRAID_AEN_HDR_SIZE;
		hcam = &pinstance->ldn;
	पूर्ण

	/* initialize command poपूर्णांकer used क्रम HCAM registration */
	hcam->cmd = cmd;

	ioarcb = &cmd->ioa_cb->ioarcb;
	ioarcb->ioadl_bus_addr = cpu_to_le64((cmd->ioa_cb_bus_addr) +
					दुरत्व(काष्ठा pmcraid_ioarcb,
						add_data.u.ioadl[0]));
	ioarcb->ioadl_length = cpu_to_le32(माप(काष्ठा pmcraid_ioadl_desc));
	ioadl = ioarcb->add_data.u.ioadl;

	/* Initialize ioarcb */
	ioarcb->request_type = REQ_TYPE_HCAM;
	ioarcb->resource_handle = cpu_to_le32(PMCRAID_IOA_RES_HANDLE);
	ioarcb->cdb[0] = PMCRAID_HOST_CONTROLLED_ASYNC;
	ioarcb->cdb[1] = type;
	ioarcb->cdb[7] = (rcb_size >> 8) & 0xFF;
	ioarcb->cdb[8] = (rcb_size) & 0xFF;

	ioarcb->data_transfer_length = cpu_to_le32(rcb_size);

	ioadl[0].flags |= IOADL_FLAGS_READ_LAST;
	ioadl[0].data_len = cpu_to_le32(rcb_size);
	ioadl[0].address = cpu_to_le64(dma);

	cmd->cmd_करोne = cmd_करोne;
	वापस cmd;
पूर्ण

/**
 * pmcraid_send_hcam - Send an HCAM to IOA
 * @pinstance: ioa config काष्ठा
 * @type: HCAM type
 *
 * This function will send a Host Controlled Async command to IOA.
 *
 * Return value:
 *	none
 */
अटल व्योम pmcraid_send_hcam(काष्ठा pmcraid_instance *pinstance, u8 type)
अणु
	काष्ठा pmcraid_cmd *cmd = pmcraid_init_hcam(pinstance, type);
	pmcraid_send_hcam_cmd(cmd);
पूर्ण


/**
 * pmcraid_prepare_cancel_cmd - prepares a command block to पात another
 *
 * @cmd: poपूर्णांकer to cmd that is used as cancelling command
 * @cmd_to_cancel: poपूर्णांकer to the command that needs to be cancelled
 */
अटल व्योम pmcraid_prepare_cancel_cmd(
	काष्ठा pmcraid_cmd *cmd,
	काष्ठा pmcraid_cmd *cmd_to_cancel
)
अणु
	काष्ठा pmcraid_ioarcb *ioarcb = &cmd->ioa_cb->ioarcb;
	__be64 ioarcb_addr;

	/* IOARCB address of the command to be cancelled is given in
	 * cdb[2]..cdb[9] is Big-Endian क्रमmat. Note that length bits in
	 * IOARCB address are not masked.
	 */
	ioarcb_addr = cpu_to_be64(le64_to_cpu(cmd_to_cancel->ioa_cb->ioarcb.ioarcb_bus_addr));

	/* Get the resource handle to where the command to be पातed has been
	 * sent.
	 */
	ioarcb->resource_handle = cmd_to_cancel->ioa_cb->ioarcb.resource_handle;
	ioarcb->request_type = REQ_TYPE_IOACMD;
	स_रखो(ioarcb->cdb, 0, PMCRAID_MAX_CDB_LEN);
	ioarcb->cdb[0] = PMCRAID_ABORT_CMD;

	स_नकल(&(ioarcb->cdb[2]), &ioarcb_addr, माप(ioarcb_addr));
पूर्ण

/**
 * pmcraid_cancel_hcam - sends ABORT task to पात a given HCAM
 *
 * @cmd: command to be used as cancelling command
 * @type: HCAM type
 * @cmd_करोne: op करोne function क्रम the cancelling command
 */
अटल व्योम pmcraid_cancel_hcam(
	काष्ठा pmcraid_cmd *cmd,
	u8 type,
	व्योम (*cmd_करोne) (काष्ठा pmcraid_cmd *)
)
अणु
	काष्ठा pmcraid_instance *pinstance;
	काष्ठा pmcraid_hostrcb  *hcam;

	pinstance = cmd->drv_inst;
	hcam =  (type == PMCRAID_HCAM_CODE_LOG_DATA) ?
		&pinstance->ldn : &pinstance->ccn;

	/* prepare क्रम cancelling previous hcam command. If the HCAM is
	 * currently not pending with IOA, we would have hcam->cmd as non-null
	 */
	अगर (hcam->cmd == शून्य)
		वापस;

	pmcraid_prepare_cancel_cmd(cmd, hcam->cmd);

	/* writing to IOARRIN must be रक्षित by host_lock, as mid-layer
	 * schedule queuecommand जबतक we are करोing this
	 */
	pmcraid_send_cmd(cmd, cmd_करोne,
			 PMCRAID_INTERNAL_TIMEOUT,
			 pmcraid_समयout_handler);
पूर्ण

/**
 * pmcraid_cancel_ccn - cancel CCN HCAM alपढ़ोy रेजिस्टरed with IOA
 *
 * @cmd: command block to be used क्रम cancelling the HCAM
 */
अटल व्योम pmcraid_cancel_ccn(काष्ठा pmcraid_cmd *cmd)
अणु
	pmcraid_info("response for Cancel LDN CDB[0] = %x ioasc = %x\n",
		     cmd->ioa_cb->ioarcb.cdb[0],
		     le32_to_cpu(cmd->ioa_cb->ioasa.ioasc));

	pmcraid_reinit_cmdblk(cmd);

	pmcraid_cancel_hcam(cmd,
			    PMCRAID_HCAM_CODE_CONFIG_CHANGE,
			    pmcraid_ioa_shutकरोwn);
पूर्ण

/**
 * pmcraid_cancel_ldn - cancel LDN HCAM alपढ़ोy रेजिस्टरed with IOA
 *
 * @cmd: command block to be used क्रम cancelling the HCAM
 */
अटल व्योम pmcraid_cancel_ldn(काष्ठा pmcraid_cmd *cmd)
अणु
	pmcraid_cancel_hcam(cmd,
			    PMCRAID_HCAM_CODE_LOG_DATA,
			    pmcraid_cancel_ccn);
पूर्ण

/**
 * pmcraid_expose_resource - check अगर the resource can be exposed to OS
 *
 * @fw_version: firmware version code
 * @cfgte: poपूर्णांकer to configuration table entry of the resource
 *
 * Return value:
 *	true अगर resource can be added to midlayer, false(0) otherwise
 */
अटल पूर्णांक pmcraid_expose_resource(u16 fw_version,
				   काष्ठा pmcraid_config_table_entry *cfgte)
अणु
	पूर्णांक retval = 0;

	अगर (cfgte->resource_type == RES_TYPE_VSET) अणु
		अगर (fw_version <= PMCRAID_FW_VERSION_1)
			retval = ((cfgte->unique_flags1 & 0x80) == 0);
		अन्यथा
			retval = ((cfgte->unique_flags0 & 0x80) == 0 &&
				  (cfgte->unique_flags1 & 0x80) == 0);

	पूर्ण अन्यथा अगर (cfgte->resource_type == RES_TYPE_GSCSI)
		retval = (RES_BUS(cfgte->resource_address) !=
				PMCRAID_VIRTUAL_ENCL_BUS_ID);
	वापस retval;
पूर्ण

/* attributes supported by pmcraid_event_family */
क्रमागत अणु
	PMCRAID_AEN_ATTR_UNSPEC,
	PMCRAID_AEN_ATTR_EVENT,
	__PMCRAID_AEN_ATTR_MAX,
पूर्ण;
#घोषणा PMCRAID_AEN_ATTR_MAX (__PMCRAID_AEN_ATTR_MAX - 1)

/* commands supported by pmcraid_event_family */
क्रमागत अणु
	PMCRAID_AEN_CMD_UNSPEC,
	PMCRAID_AEN_CMD_EVENT,
	__PMCRAID_AEN_CMD_MAX,
पूर्ण;
#घोषणा PMCRAID_AEN_CMD_MAX (__PMCRAID_AEN_CMD_MAX - 1)

अटल काष्ठा genl_multicast_group pmcraid_mcgrps[] = अणु
	अणु .name = "events", /* not really used - see ID discussion below */ पूर्ण,
पूर्ण;

अटल काष्ठा genl_family pmcraid_event_family __ro_after_init = अणु
	.module = THIS_MODULE,
	.name = "pmcraid",
	.version = 1,
	.maxattr = PMCRAID_AEN_ATTR_MAX,
	.mcgrps = pmcraid_mcgrps,
	.n_mcgrps = ARRAY_SIZE(pmcraid_mcgrps),
पूर्ण;

/**
 * pmcraid_netlink_init - रेजिस्टरs pmcraid_event_family
 *
 * Return value:
 *	0 अगर the pmcraid_event_family is successfully रेजिस्टरed
 *	with netlink generic, non-zero otherwise
 */
अटल पूर्णांक __init pmcraid_netlink_init(व्योम)
अणु
	पूर्णांक result;

	result = genl_रेजिस्टर_family(&pmcraid_event_family);

	अगर (result)
		वापस result;

	pmcraid_info("registered NETLINK GENERIC group: %d\n",
		     pmcraid_event_family.id);

	वापस result;
पूर्ण

/**
 * pmcraid_netlink_release - unरेजिस्टरs pmcraid_event_family
 *
 * Return value:
 *	none
 */
अटल व्योम pmcraid_netlink_release(व्योम)
अणु
	genl_unरेजिस्टर_family(&pmcraid_event_family);
पूर्ण

/*
 * pmcraid_notअगरy_aen - sends event msg to user space application
 * @pinstance: poपूर्णांकer to adapter instance काष्ठाure
 *
 * Return value:
 *	0 अगर success, error value in हाल of any failure.
 */
अटल पूर्णांक pmcraid_notअगरy_aen(
	काष्ठा pmcraid_instance *pinstance,
	काष्ठा pmcraid_aen_msg  *aen_msg,
	u32    data_size)
अणु
	काष्ठा sk_buff *skb;
	व्योम *msg_header;
	u32  total_size, nla_genl_hdr_total_size;
	पूर्णांक result;

	aen_msg->hostno = (pinstance->host->unique_id << 16 |
			   MINOR(pinstance->cdev.dev));
	aen_msg->length = data_size;

	data_size += माप(*aen_msg);

	total_size = nla_total_size(data_size);
	/* Add GENL_HDR to total_size */
	nla_genl_hdr_total_size =
		(total_size + (GENL_HDRLEN +
		((काष्ठा genl_family *)&pmcraid_event_family)->hdrsize)
		 + NLMSG_HDRLEN);
	skb = genlmsg_new(nla_genl_hdr_total_size, GFP_ATOMIC);


	अगर (!skb) अणु
		pmcraid_err("Failed to allocate aen data SKB of size: %x\n",
			     total_size);
		वापस -ENOMEM;
	पूर्ण

	/* add the genetlink message header */
	msg_header = genlmsg_put(skb, 0, 0,
				 &pmcraid_event_family, 0,
				 PMCRAID_AEN_CMD_EVENT);
	अगर (!msg_header) अणु
		pmcraid_err("failed to copy command details\n");
		nlmsg_मुक्त(skb);
		वापस -ENOMEM;
	पूर्ण

	result = nla_put(skb, PMCRAID_AEN_ATTR_EVENT, data_size, aen_msg);

	अगर (result) अणु
		pmcraid_err("failed to copy AEN attribute data\n");
		nlmsg_मुक्त(skb);
		वापस -EINVAL;
	पूर्ण

	/* send genetlink multicast message to notअगरy appplications */
	genlmsg_end(skb, msg_header);

	result = genlmsg_multicast(&pmcraid_event_family, skb,
				   0, 0, GFP_ATOMIC);

	/* If there are no listeners, genlmsg_multicast may वापस non-zero
	 * value.
	 */
	अगर (result)
		pmcraid_info("error (%x) sending aen event message\n", result);
	वापस result;
पूर्ण

/**
 * pmcraid_notअगरy_ccn - notअगरies about CCN event msg to user space
 * @pinstance: poपूर्णांकer adapter instance काष्ठाure
 *
 * Return value:
 *	0 अगर success, error value in हाल of any failure
 */
अटल पूर्णांक pmcraid_notअगरy_ccn(काष्ठा pmcraid_instance *pinstance)
अणु
	वापस pmcraid_notअगरy_aen(pinstance,
				pinstance->ccn.msg,
				le32_to_cpu(pinstance->ccn.hcam->data_len) +
				माप(काष्ठा pmcraid_hcam_hdr));
पूर्ण

/**
 * pmcraid_notअगरy_ldn - notअगरies about CCN event msg to user space
 * @pinstance: poपूर्णांकer adapter instance काष्ठाure
 *
 * Return value:
 *	0 अगर success, error value in हाल of any failure
 */
अटल पूर्णांक pmcraid_notअगरy_ldn(काष्ठा pmcraid_instance *pinstance)
अणु
	वापस pmcraid_notअगरy_aen(pinstance,
				pinstance->ldn.msg,
				le32_to_cpu(pinstance->ldn.hcam->data_len) +
				माप(काष्ठा pmcraid_hcam_hdr));
पूर्ण

/**
 * pmcraid_notअगरy_ioastate - sends IOA state event msg to user space
 * @pinstance: poपूर्णांकer adapter instance काष्ठाure
 * @evt: controller state event to be sent
 *
 * Return value:
 *	0 अगर success, error value in हाल of any failure
 */
अटल व्योम pmcraid_notअगरy_ioastate(काष्ठा pmcraid_instance *pinstance, u32 evt)
अणु
	pinstance->scn.ioa_state = evt;
	pmcraid_notअगरy_aen(pinstance,
			  &pinstance->scn.msg,
			  माप(u32));
पूर्ण

/**
 * pmcraid_handle_config_change - Handle a config change from the adapter
 * @pinstance: poपूर्णांकer to per adapter instance काष्ठाure
 *
 * Return value:
 *  none
 */

अटल व्योम pmcraid_handle_config_change(काष्ठा pmcraid_instance *pinstance)
अणु
	काष्ठा pmcraid_config_table_entry *cfg_entry;
	काष्ठा pmcraid_hcam_ccn *ccn_hcam;
	काष्ठा pmcraid_cmd *cmd;
	काष्ठा pmcraid_cmd *cfgcmd;
	काष्ठा pmcraid_resource_entry *res = शून्य;
	अचिन्हित दीर्घ lock_flags;
	अचिन्हित दीर्घ host_lock_flags;
	u32 new_entry = 1;
	u32 hidden_entry = 0;
	u16 fw_version;
	पूर्णांक rc;

	ccn_hcam = (काष्ठा pmcraid_hcam_ccn *)pinstance->ccn.hcam;
	cfg_entry = &ccn_hcam->cfg_entry;
	fw_version = be16_to_cpu(pinstance->inq_data->fw_version);

	pmcraid_info("CCN(%x): %x बारtamp: %llx type: %x lost: %x flags: %x \
		 res: %x:%x:%x:%x\न",
		 le32_to_cpu(pinstance->ccn.hcam->ilid),
		 pinstance->ccn.hcam->op_code,
		(le32_to_cpu(pinstance->ccn.hcam->बारtamp1) |
		((le32_to_cpu(pinstance->ccn.hcam->बारtamp2) & 0xffffffffLL) << 32)),
		 pinstance->ccn.hcam->notअगरication_type,
		 pinstance->ccn.hcam->notअगरication_lost,
		 pinstance->ccn.hcam->flags,
		 pinstance->host->unique_id,
		 RES_IS_VSET(*cfg_entry) ? PMCRAID_VSET_BUS_ID :
		 (RES_IS_GSCSI(*cfg_entry) ? PMCRAID_PHYS_BUS_ID :
			RES_BUS(cfg_entry->resource_address)),
		 RES_IS_VSET(*cfg_entry) ?
			(fw_version <= PMCRAID_FW_VERSION_1 ?
				cfg_entry->unique_flags1 :
				le16_to_cpu(cfg_entry->array_id) & 0xFF) :
			RES_TARGET(cfg_entry->resource_address),
		 RES_LUN(cfg_entry->resource_address));


	/* If this HCAM indicates a lost notअगरication, पढ़ो the config table */
	अगर (pinstance->ccn.hcam->notअगरication_lost) अणु
		cfgcmd = pmcraid_get_मुक्त_cmd(pinstance);
		अगर (cfgcmd) अणु
			pmcraid_info("lost CCN, reading config table\b");
			pinstance->reinit_cfg_table = 1;
			pmcraid_querycfg(cfgcmd);
		पूर्ण अन्यथा अणु
			pmcraid_err("lost CCN, no free cmd for querycfg\n");
		पूर्ण
		जाओ out_notअगरy_apps;
	पूर्ण

	/* If this resource is not going to be added to mid-layer, just notअगरy
	 * applications and वापस. If this notअगरication is about hiding a VSET
	 * resource, check अगर it was exposed alपढ़ोy.
	 */
	अगर (pinstance->ccn.hcam->notअगरication_type ==
	    NOTIFICATION_TYPE_ENTRY_CHANGED &&
	    cfg_entry->resource_type == RES_TYPE_VSET) अणु
		hidden_entry = (cfg_entry->unique_flags1 & 0x80) != 0;
	पूर्ण अन्यथा अगर (!pmcraid_expose_resource(fw_version, cfg_entry)) अणु
		जाओ out_notअगरy_apps;
	पूर्ण

	spin_lock_irqsave(&pinstance->resource_lock, lock_flags);
	list_क्रम_each_entry(res, &pinstance->used_res_q, queue) अणु
		rc = स_भेद(&res->cfg_entry.resource_address,
			    &cfg_entry->resource_address,
			    माप(cfg_entry->resource_address));
		अगर (!rc) अणु
			new_entry = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (new_entry) अणु

		अगर (hidden_entry) अणु
			spin_unlock_irqrestore(&pinstance->resource_lock,
						lock_flags);
			जाओ out_notअगरy_apps;
		पूर्ण

		/* If there are more number of resources than what driver can
		 * manage, करो not notअगरy the applications about the CCN. Just
		 * ignore this notअगरications and re-रेजिस्टर the same HCAM
		 */
		अगर (list_empty(&pinstance->मुक्त_res_q)) अणु
			spin_unlock_irqrestore(&pinstance->resource_lock,
						lock_flags);
			pmcraid_err("too many resources attached\n");
			spin_lock_irqsave(pinstance->host->host_lock,
					  host_lock_flags);
			pmcraid_send_hcam(pinstance,
					  PMCRAID_HCAM_CODE_CONFIG_CHANGE);
			spin_unlock_irqrestore(pinstance->host->host_lock,
					       host_lock_flags);
			वापस;
		पूर्ण

		res = list_entry(pinstance->मुक्त_res_q.next,
				 काष्ठा pmcraid_resource_entry, queue);

		list_del(&res->queue);
		res->scsi_dev = शून्य;
		res->reset_progress = 0;
		list_add_tail(&res->queue, &pinstance->used_res_q);
	पूर्ण

	स_नकल(&res->cfg_entry, cfg_entry, pinstance->config_table_entry_size);

	अगर (pinstance->ccn.hcam->notअगरication_type ==
	    NOTIFICATION_TYPE_ENTRY_DELETED || hidden_entry) अणु
		अगर (res->scsi_dev) अणु
			अगर (fw_version <= PMCRAID_FW_VERSION_1)
				res->cfg_entry.unique_flags1 &= 0x7F;
			अन्यथा
				res->cfg_entry.array_id &= cpu_to_le16(0xFF);
			res->change_detected = RES_CHANGE_DEL;
			res->cfg_entry.resource_handle =
				PMCRAID_INVALID_RES_HANDLE;
			schedule_work(&pinstance->worker_q);
		पूर्ण अन्यथा अणु
			/* This may be one of the non-exposed resources */
			list_move_tail(&res->queue, &pinstance->मुक्त_res_q);
		पूर्ण
	पूर्ण अन्यथा अगर (!res->scsi_dev) अणु
		res->change_detected = RES_CHANGE_ADD;
		schedule_work(&pinstance->worker_q);
	पूर्ण
	spin_unlock_irqrestore(&pinstance->resource_lock, lock_flags);

out_notअगरy_apps:

	/* Notअगरy configuration changes to रेजिस्टरed applications.*/
	अगर (!pmcraid_disable_aen)
		pmcraid_notअगरy_ccn(pinstance);

	cmd = pmcraid_init_hcam(pinstance, PMCRAID_HCAM_CODE_CONFIG_CHANGE);
	अगर (cmd)
		pmcraid_send_hcam_cmd(cmd);
पूर्ण

/**
 * pmcraid_get_error_info - वापस error string क्रम an ioasc
 * @ioasc: ioasc code
 * Return Value
 *	 none
 */
अटल काष्ठा pmcraid_ioasc_error *pmcraid_get_error_info(u32 ioasc)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(pmcraid_ioasc_error_table); i++) अणु
		अगर (pmcraid_ioasc_error_table[i].ioasc_code == ioasc)
			वापस &pmcraid_ioasc_error_table[i];
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * pmcraid_ioasc_logger - log IOASC inक्रमmation based user-settings
 * @ioasc: ioasc code
 * @cmd: poपूर्णांकer to command that resulted in 'ioasc'
 */
अटल व्योम pmcraid_ioasc_logger(u32 ioasc, काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा pmcraid_ioasc_error *error_info = pmcraid_get_error_info(ioasc);

	अगर (error_info == शून्य ||
		cmd->drv_inst->current_log_level < error_info->log_level)
		वापस;

	/* log the error string */
	pmcraid_err("cmd [%x] for resource %x failed with %x(%s)\n",
		cmd->ioa_cb->ioarcb.cdb[0],
		le32_to_cpu(cmd->ioa_cb->ioarcb.resource_handle),
		ioasc, error_info->error_string);
पूर्ण

/**
 * pmcraid_handle_error_log - Handle a config change (error log) from the IOA
 *
 * @pinstance: poपूर्णांकer to per adapter instance काष्ठाure
 *
 * Return value:
 *  none
 */
अटल व्योम pmcraid_handle_error_log(काष्ठा pmcraid_instance *pinstance)
अणु
	काष्ठा pmcraid_hcam_ldn *hcam_ldn;
	u32 ioasc;

	hcam_ldn = (काष्ठा pmcraid_hcam_ldn *)pinstance->ldn.hcam;

	pmcraid_info
		("LDN(%x): %x type: %x lost: %x flags: %x overlay id: %x\n",
		 pinstance->ldn.hcam->ilid,
		 pinstance->ldn.hcam->op_code,
		 pinstance->ldn.hcam->notअगरication_type,
		 pinstance->ldn.hcam->notअगरication_lost,
		 pinstance->ldn.hcam->flags,
		 pinstance->ldn.hcam->overlay_id);

	/* log only the errors, no need to log inक्रमmational log entries */
	अगर (pinstance->ldn.hcam->notअगरication_type !=
	    NOTIFICATION_TYPE_ERROR_LOG)
		वापस;

	अगर (pinstance->ldn.hcam->notअगरication_lost ==
	    HOSTRCB_NOTIFICATIONS_LOST)
		dev_info(&pinstance->pdev->dev, "Error notifications lost\n");

	ioasc = le32_to_cpu(hcam_ldn->error_log.fd_ioasc);

	अगर (ioasc == PMCRAID_IOASC_UA_BUS_WAS_RESET ||
		ioasc == PMCRAID_IOASC_UA_BUS_WAS_RESET_BY_OTHER) अणु
		dev_info(&pinstance->pdev->dev,
			"UnitAttention due to IOA Bus Reset\n");
		scsi_report_bus_reset(
			pinstance->host,
			RES_BUS(hcam_ldn->error_log.fd_ra));
	पूर्ण

	वापस;
पूर्ण

/**
 * pmcraid_process_ccn - Op करोne function क्रम a CCN.
 * @cmd: poपूर्णांकer to command काष्ठा
 *
 * This function is the op करोne function क्रम a configuration
 * change notअगरication
 *
 * Return value:
 * none
 */
अटल व्योम pmcraid_process_ccn(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;
	u32 ioasc = le32_to_cpu(cmd->ioa_cb->ioasa.ioasc);
	अचिन्हित दीर्घ lock_flags;

	pinstance->ccn.cmd = शून्य;
	pmcraid_वापस_cmd(cmd);

	/* If driver initiated IOA reset happened जबतक this hcam was pending
	 * with IOA, or IOA bringकरोwn sequence is in progress, no need to
	 * re-रेजिस्टर the hcam
	 */
	अगर (ioasc == PMCRAID_IOASC_IOA_WAS_RESET ||
	    atomic_पढ़ो(&pinstance->ccn.ignore) == 1) अणु
		वापस;
	पूर्ण अन्यथा अगर (ioasc) अणु
		dev_info(&pinstance->pdev->dev,
			"Host RCB (CCN) failed with IOASC: 0x%08X\n", ioasc);
		spin_lock_irqsave(pinstance->host->host_lock, lock_flags);
		pmcraid_send_hcam(pinstance, PMCRAID_HCAM_CODE_CONFIG_CHANGE);
		spin_unlock_irqrestore(pinstance->host->host_lock, lock_flags);
	पूर्ण अन्यथा अणु
		pmcraid_handle_config_change(pinstance);
	पूर्ण
पूर्ण

अटल व्योम pmcraid_initiate_reset(काष्ठा pmcraid_instance *);
अटल व्योम pmcraid_set_बारtamp(काष्ठा pmcraid_cmd *cmd);
/**
 * pmcraid_process_ldn - op करोne function क्रम an LDN
 * @cmd: poपूर्णांकer to command block
 *
 * Return value
 *   none
 */
अटल व्योम pmcraid_process_ldn(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;
	काष्ठा pmcraid_hcam_ldn *ldn_hcam =
			(काष्ठा pmcraid_hcam_ldn *)pinstance->ldn.hcam;
	u32 ioasc = le32_to_cpu(cmd->ioa_cb->ioasa.ioasc);
	u32 fd_ioasc = le32_to_cpu(ldn_hcam->error_log.fd_ioasc);
	अचिन्हित दीर्घ lock_flags;

	/* वापस the command block back to मुक्तpool */
	pinstance->ldn.cmd = शून्य;
	pmcraid_वापस_cmd(cmd);

	/* If driver initiated IOA reset happened जबतक this hcam was pending
	 * with IOA, no need to re-रेजिस्टर the hcam as reset engine will करो it
	 * once reset sequence is complete
	 */
	अगर (ioasc == PMCRAID_IOASC_IOA_WAS_RESET ||
	    atomic_पढ़ो(&pinstance->ccn.ignore) == 1) अणु
		वापस;
	पूर्ण अन्यथा अगर (!ioasc) अणु
		pmcraid_handle_error_log(pinstance);
		अगर (fd_ioasc == PMCRAID_IOASC_NR_IOA_RESET_REQUIRED) अणु
			spin_lock_irqsave(pinstance->host->host_lock,
					  lock_flags);
			pmcraid_initiate_reset(pinstance);
			spin_unlock_irqrestore(pinstance->host->host_lock,
					       lock_flags);
			वापस;
		पूर्ण
		अगर (fd_ioasc == PMCRAID_IOASC_TIME_STAMP_OUT_OF_SYNC) अणु
			pinstance->बारtamp_error = 1;
			pmcraid_set_बारtamp(cmd);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_info(&pinstance->pdev->dev,
			"Host RCB(LDN) failed with IOASC: 0x%08X\n", ioasc);
	पूर्ण
	/* send netlink message क्रम HCAM notअगरication अगर enabled */
	अगर (!pmcraid_disable_aen)
		pmcraid_notअगरy_ldn(pinstance);

	cmd = pmcraid_init_hcam(pinstance, PMCRAID_HCAM_CODE_LOG_DATA);
	अगर (cmd)
		pmcraid_send_hcam_cmd(cmd);
पूर्ण

/**
 * pmcraid_रेजिस्टर_hcams - रेजिस्टर HCAMs क्रम CCN and LDN
 *
 * @pinstance: poपूर्णांकer per adapter instance काष्ठाure
 *
 * Return Value
 *   none
 */
अटल व्योम pmcraid_रेजिस्टर_hcams(काष्ठा pmcraid_instance *pinstance)
अणु
	pmcraid_send_hcam(pinstance, PMCRAID_HCAM_CODE_CONFIG_CHANGE);
	pmcraid_send_hcam(pinstance, PMCRAID_HCAM_CODE_LOG_DATA);
पूर्ण

/**
 * pmcraid_unरेजिस्टर_hcams - cancel HCAMs रेजिस्टरed alपढ़ोy
 * @cmd: poपूर्णांकer to command used as part of reset sequence
 */
अटल व्योम pmcraid_unरेजिस्टर_hcams(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;

	/* During IOA bringकरोwn, HCAM माला_लो fired and tasklet proceeds with
	 * handling hcam response though it is not necessary. In order to
	 * prevent this, set 'ignore', so that bring-down sequence doesn't
	 * re-send any more hcams
	 */
	atomic_set(&pinstance->ccn.ignore, 1);
	atomic_set(&pinstance->ldn.ignore, 1);

	/* If adapter reset was क्रमced as part of runसमय reset sequence,
	 * start the reset sequence. Reset will be triggered even in हाल
	 * IOA unit_check.
	 */
	अगर ((pinstance->क्रमce_ioa_reset && !pinstance->ioa_bringकरोwn) ||
	     pinstance->ioa_unit_check) अणु
		pinstance->क्रमce_ioa_reset = 0;
		pinstance->ioa_unit_check = 0;
		pinstance->ioa_state = IOA_STATE_IN_RESET_ALERT;
		pmcraid_reset_alert(cmd);
		वापस;
	पूर्ण

	/* Driver tries to cancel HCAMs by sending ABORT TASK क्रम each HCAM
	 * one after the other. So CCN cancellation will be triggered by
	 * pmcraid_cancel_ldn itself.
	 */
	pmcraid_cancel_ldn(cmd);
पूर्ण

अटल व्योम pmcraid_reinit_buffers(काष्ठा pmcraid_instance *);

/**
 * pmcraid_reset_enable_ioa - re-enable IOA after a hard reset
 * @pinstance: poपूर्णांकer to adapter instance काष्ठाure
 * Return Value
 *  1 अगर TRANSITION_TO_OPERATIONAL is active, otherwise 0
 */
अटल पूर्णांक pmcraid_reset_enable_ioa(काष्ठा pmcraid_instance *pinstance)
अणु
	u32 पूर्णांकrs;

	pmcraid_reinit_buffers(pinstance);
	पूर्णांकrs = pmcraid_पढ़ो_पूर्णांकerrupts(pinstance);

	pmcraid_enable_पूर्णांकerrupts(pinstance, PMCRAID_PCI_INTERRUPTS);

	अगर (पूर्णांकrs & INTRS_TRANSITION_TO_OPERATIONAL) अणु
		अगर (!pinstance->पूर्णांकerrupt_mode) अणु
			ioग_लिखो32(INTRS_TRANSITION_TO_OPERATIONAL,
				pinstance->पूर्णांक_regs.
				ioa_host_पूर्णांकerrupt_mask_reg);
			ioग_लिखो32(INTRS_TRANSITION_TO_OPERATIONAL,
				pinstance->पूर्णांक_regs.ioa_host_पूर्णांकerrupt_clr_reg);
		पूर्ण
		वापस 1;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

/**
 * pmcraid_soft_reset - perक्रमms a soft reset and makes IOA become पढ़ोy
 * @cmd : poपूर्णांकer to reset command block
 *
 * Return Value
 *	none
 */
अटल व्योम pmcraid_soft_reset(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;
	u32 पूर्णांक_reg;
	u32 करोorbell;

	/* There will be an पूर्णांकerrupt when Transition to Operational bit is
	 * set so tasklet would execute next reset task. The समयout handler
	 * would re-initiate a reset
	 */
	cmd->cmd_करोne = pmcraid_ioa_reset;
	cmd->समयr.expires = jअगरfies +
			     msecs_to_jअगरfies(PMCRAID_TRANSOP_TIMEOUT);
	cmd->समयr.function = pmcraid_समयout_handler;

	अगर (!समयr_pending(&cmd->समयr))
		add_समयr(&cmd->समयr);

	/* Enable deकाष्ठाive diagnostics on IOA अगर it is not yet in
	 * operational state
	 */
	करोorbell = DOORBELL_RUNTIME_RESET |
		   DOORBELL_ENABLE_DESTRUCTIVE_DIAGS;

	/* Since we करो RESET_ALERT and Start BIST we have to again ग_लिखो
	 * MSIX Doorbell to indicate the पूर्णांकerrupt mode
	 */
	अगर (pinstance->पूर्णांकerrupt_mode) अणु
		ioग_लिखो32(DOORBELL_INTR_MODE_MSIX,
			  pinstance->पूर्णांक_regs.host_ioa_पूर्णांकerrupt_reg);
		ioपढ़ो32(pinstance->पूर्णांक_regs.host_ioa_पूर्णांकerrupt_reg);
	पूर्ण

	ioग_लिखो32(करोorbell, pinstance->पूर्णांक_regs.host_ioa_पूर्णांकerrupt_reg);
	ioपढ़ो32(pinstance->पूर्णांक_regs.host_ioa_पूर्णांकerrupt_reg),
	पूर्णांक_reg = ioपढ़ो32(pinstance->पूर्णांक_regs.ioa_host_पूर्णांकerrupt_reg);

	pmcraid_info("Waiting for IOA to become operational %x:%x\n",
		     ioपढ़ो32(pinstance->पूर्णांक_regs.host_ioa_पूर्णांकerrupt_reg),
		     पूर्णांक_reg);
पूर्ण

/**
 * pmcraid_get_dump - retrieves IOA dump in हाल of Unit Check पूर्णांकerrupt
 *
 * @pinstance: poपूर्णांकer to adapter instance काष्ठाure
 *
 * Return Value
 *	none
 */
अटल व्योम pmcraid_get_dump(काष्ठा pmcraid_instance *pinstance)
अणु
	pmcraid_info("%s is not yet implemented\n", __func__);
पूर्ण

/**
 * pmcraid_fail_outstanding_cmds - Fails all outstanding ops.
 * @pinstance: poपूर्णांकer to adapter instance काष्ठाure
 *
 * This function fails all outstanding ops. If they are submitted to IOA
 * alपढ़ोy, it sends cancel all messages अगर IOA is still accepting IOARCBs,
 * otherwise just completes the commands and वापसs the cmd blocks to मुक्त
 * pool.
 *
 * Return value:
 *	 none
 */
अटल व्योम pmcraid_fail_outstanding_cmds(काष्ठा pmcraid_instance *pinstance)
अणु
	काष्ठा pmcraid_cmd *cmd, *temp;
	अचिन्हित दीर्घ lock_flags;

	/* pending command list is रक्षित by pending_pool_lock. Its
	 * traversal must be करोne as within this lock
	 */
	spin_lock_irqsave(&pinstance->pending_pool_lock, lock_flags);
	list_क्रम_each_entry_safe(cmd, temp, &pinstance->pending_cmd_pool,
				 मुक्त_list) अणु
		list_del(&cmd->मुक्त_list);
		spin_unlock_irqrestore(&pinstance->pending_pool_lock,
					lock_flags);
		cmd->ioa_cb->ioasa.ioasc =
			cpu_to_le32(PMCRAID_IOASC_IOA_WAS_RESET);
		cmd->ioa_cb->ioasa.ilid =
			cpu_to_le32(PMCRAID_DRIVER_ILID);

		/* In हाल the command समयr is still running */
		del_समयr(&cmd->समयr);

		/* If this is an IO command, complete it by invoking scsi_करोne
		 * function. If this is one of the पूर्णांकernal commands other
		 * than pmcraid_ioa_reset and HCAM commands invoke cmd_करोne to
		 * complete it
		 */
		अगर (cmd->scsi_cmd) अणु

			काष्ठा scsi_cmnd *scsi_cmd = cmd->scsi_cmd;
			__le32 resp = cmd->ioa_cb->ioarcb.response_handle;

			scsi_cmd->result |= DID_ERROR << 16;

			scsi_dma_unmap(scsi_cmd);
			pmcraid_वापस_cmd(cmd);

			pmcraid_info("failing(%d) CDB[0] = %x result: %x\n",
				     le32_to_cpu(resp) >> 2,
				     cmd->ioa_cb->ioarcb.cdb[0],
				     scsi_cmd->result);
			scsi_cmd->scsi_करोne(scsi_cmd);
		पूर्ण अन्यथा अगर (cmd->cmd_करोne == pmcraid_पूर्णांकernal_करोne ||
			   cmd->cmd_करोne == pmcraid_erp_करोne) अणु
			cmd->cmd_करोne(cmd);
		पूर्ण अन्यथा अगर (cmd->cmd_करोne != pmcraid_ioa_reset &&
			   cmd->cmd_करोne != pmcraid_ioa_shutकरोwn_करोne) अणु
			pmcraid_वापस_cmd(cmd);
		पूर्ण

		atomic_dec(&pinstance->outstanding_cmds);
		spin_lock_irqsave(&pinstance->pending_pool_lock, lock_flags);
	पूर्ण

	spin_unlock_irqrestore(&pinstance->pending_pool_lock, lock_flags);
पूर्ण

/**
 * pmcraid_ioa_reset - Implementation of IOA reset logic
 *
 * @cmd: poपूर्णांकer to the cmd block to be used क्रम entire reset process
 *
 * This function executes most of the steps required क्रम IOA reset. This माला_लो
 * called by user thपढ़ोs (modprobe/insmod/rmmod) समयr, tasklet and midlayer's
 * 'eh_' thपढ़ो. Access to variables used क्रम controlling the reset sequence is
 * synchronized using host lock. Various functions called during reset process
 * would make use of a single command block, poपूर्णांकer to which is also stored in
 * adapter instance काष्ठाure.
 *
 * Return Value
 *	 None
 */
अटल व्योम pmcraid_ioa_reset(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;
	u8 reset_complete = 0;

	pinstance->ioa_reset_in_progress = 1;

	अगर (pinstance->reset_cmd != cmd) अणु
		pmcraid_err("reset is called with different command block\n");
		pinstance->reset_cmd = cmd;
	पूर्ण

	pmcraid_info("reset_engine: state = %d, command = %p\n",
		      pinstance->ioa_state, cmd);

	चयन (pinstance->ioa_state) अणु

	हाल IOA_STATE_DEAD:
		/* If IOA is offline, whatever may be the reset reason, just
		 * वापस. callers might be रुकोing on the reset रुको_q, wake
		 * up them
		 */
		pmcraid_err("IOA is offline no reset is possible\n");
		reset_complete = 1;
		अवरोध;

	हाल IOA_STATE_IN_BRINGDOWN:
		/* we enter here, once ioa shutकरोwn command is processed by IOA
		 * Alert IOA क्रम a possible reset. If reset alert fails, IOA
		 * goes through hard-reset
		 */
		pmcraid_disable_पूर्णांकerrupts(pinstance, ~0);
		pinstance->ioa_state = IOA_STATE_IN_RESET_ALERT;
		pmcraid_reset_alert(cmd);
		अवरोध;

	हाल IOA_STATE_UNKNOWN:
		/* We may be called during probe or resume. Some pre-processing
		 * is required क्रम prior to reset
		 */
		scsi_block_requests(pinstance->host);

		/* If asked to reset जबतक IOA was processing responses or
		 * there are any error responses then IOA may require
		 * hard-reset.
		 */
		अगर (pinstance->ioa_hard_reset == 0) अणु
			अगर (ioपढ़ो32(pinstance->ioa_status) &
			    INTRS_TRANSITION_TO_OPERATIONAL) अणु
				pmcraid_info("sticky bit set, bring-up\n");
				pinstance->ioa_state = IOA_STATE_IN_BRINGUP;
				pmcraid_reinit_cmdblk(cmd);
				pmcraid_identअगरy_hrrq(cmd);
			पूर्ण अन्यथा अणु
				pinstance->ioa_state = IOA_STATE_IN_SOFT_RESET;
				pmcraid_soft_reset(cmd);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Alert IOA of a possible reset and रुको क्रम critical
			 * operation in progress bit to reset
			 */
			pinstance->ioa_state = IOA_STATE_IN_RESET_ALERT;
			pmcraid_reset_alert(cmd);
		पूर्ण
		अवरोध;

	हाल IOA_STATE_IN_RESET_ALERT:
		/* If critical operation in progress bit is reset or रुको माला_लो
		 * समयd out, reset proceeds with starting BIST on the IOA.
		 * pmcraid_ioa_hard_reset keeps a count of reset attempts. If
		 * they are 3 or more, reset engine marks IOA dead and वापसs
		 */
		pinstance->ioa_state = IOA_STATE_IN_HARD_RESET;
		pmcraid_start_bist(cmd);
		अवरोध;

	हाल IOA_STATE_IN_HARD_RESET:
		pinstance->ioa_reset_attempts++;

		/* retry reset अगर we haven't reached maximum allowed limit */
		अगर (pinstance->ioa_reset_attempts > PMCRAID_RESET_ATTEMPTS) अणु
			pinstance->ioa_reset_attempts = 0;
			pmcraid_err("IOA didn't respond marking it as dead\n");
			pinstance->ioa_state = IOA_STATE_DEAD;

			अगर (pinstance->ioa_bringकरोwn)
				pmcraid_notअगरy_ioastate(pinstance,
					PMC_DEVICE_EVENT_SHUTDOWN_FAILED);
			अन्यथा
				pmcraid_notअगरy_ioastate(pinstance,
						PMC_DEVICE_EVENT_RESET_FAILED);
			reset_complete = 1;
			अवरोध;
		पूर्ण

		/* Once either bist or pci reset is करोne, restore PCI config
		 * space. If this fails, proceed with hard reset again
		 */
		pci_restore_state(pinstance->pdev);

		/* fail all pending commands */
		pmcraid_fail_outstanding_cmds(pinstance);

		/* check अगर unit check is active, अगर so extract dump */
		अगर (pinstance->ioa_unit_check) अणु
			pmcraid_info("unit check is active\n");
			pinstance->ioa_unit_check = 0;
			pmcraid_get_dump(pinstance);
			pinstance->ioa_reset_attempts--;
			pinstance->ioa_state = IOA_STATE_IN_RESET_ALERT;
			pmcraid_reset_alert(cmd);
			अवरोध;
		पूर्ण

		/* अगर the reset reason is to bring-करोwn the ioa, we might be
		 * करोne with the reset restore pci_config_space and complete
		 * the reset
		 */
		अगर (pinstance->ioa_bringकरोwn) अणु
			pmcraid_info("bringing down the adapter\n");
			pinstance->ioa_shutकरोwn_type = SHUTDOWN_NONE;
			pinstance->ioa_bringकरोwn = 0;
			pinstance->ioa_state = IOA_STATE_UNKNOWN;
			pmcraid_notअगरy_ioastate(pinstance,
					PMC_DEVICE_EVENT_SHUTDOWN_SUCCESS);
			reset_complete = 1;
		पूर्ण अन्यथा अणु
			/* bring-up IOA, so proceed with soft reset
			 * Reinitialize hrrq_buffers and their indices also
			 * enable पूर्णांकerrupts after a pci_restore_state
			 */
			अगर (pmcraid_reset_enable_ioa(pinstance)) अणु
				pinstance->ioa_state = IOA_STATE_IN_BRINGUP;
				pmcraid_info("bringing up the adapter\n");
				pmcraid_reinit_cmdblk(cmd);
				pmcraid_identअगरy_hrrq(cmd);
			पूर्ण अन्यथा अणु
				pinstance->ioa_state = IOA_STATE_IN_SOFT_RESET;
				pmcraid_soft_reset(cmd);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल IOA_STATE_IN_SOFT_RESET:
		/* TRANSITION TO OPERATIONAL is on so start initialization
		 * sequence
		 */
		pmcraid_info("In softreset proceeding with bring-up\n");
		pinstance->ioa_state = IOA_STATE_IN_BRINGUP;

		/* Initialization commands start with HRRQ identअगरication. From
		 * now on tasklet completes most of the commands as IOA is up
		 * and पूर्णांकrs are enabled
		 */
		pmcraid_identअगरy_hrrq(cmd);
		अवरोध;

	हाल IOA_STATE_IN_BRINGUP:
		/* we are करोne with bringing up of IOA, change the ioa_state to
		 * operational and wake up any रुकोers
		 */
		pinstance->ioa_state = IOA_STATE_OPERATIONAL;
		reset_complete = 1;
		अवरोध;

	हाल IOA_STATE_OPERATIONAL:
	शेष:
		/* When IOA is operational and a reset is requested, check क्रम
		 * the reset reason. If reset is to bring करोwn IOA, unरेजिस्टर
		 * HCAMs and initiate shutकरोwn; अगर adapter reset is क्रमced then
		 * restart reset sequence again
		 */
		अगर (pinstance->ioa_shutकरोwn_type == SHUTDOWN_NONE &&
		    pinstance->क्रमce_ioa_reset == 0) अणु
			pmcraid_notअगरy_ioastate(pinstance,
						PMC_DEVICE_EVENT_RESET_SUCCESS);
			reset_complete = 1;
		पूर्ण अन्यथा अणु
			अगर (pinstance->ioa_shutकरोwn_type != SHUTDOWN_NONE)
				pinstance->ioa_state = IOA_STATE_IN_BRINGDOWN;
			pmcraid_reinit_cmdblk(cmd);
			pmcraid_unरेजिस्टर_hcams(cmd);
		पूर्ण
		अवरोध;
	पूर्ण

	/* reset will be completed अगर ioa_state is either DEAD or UNKNOWN or
	 * OPERATIONAL. Reset all control variables used during reset, wake up
	 * any रुकोing thपढ़ोs and let the SCSI mid-layer send commands. Note
	 * that host_lock must be held beक्रमe invoking scsi_report_bus_reset.
	 */
	अगर (reset_complete) अणु
		pinstance->ioa_reset_in_progress = 0;
		pinstance->ioa_reset_attempts = 0;
		pinstance->reset_cmd = शून्य;
		pinstance->ioa_shutकरोwn_type = SHUTDOWN_NONE;
		pinstance->ioa_bringकरोwn = 0;
		pmcraid_वापस_cmd(cmd);

		/* If target state is to bring up the adapter, proceed with
		 * hcam registration and resource exposure to mid-layer.
		 */
		अगर (pinstance->ioa_state == IOA_STATE_OPERATIONAL)
			pmcraid_रेजिस्टर_hcams(pinstance);

		wake_up_all(&pinstance->reset_रुको_q);
	पूर्ण

	वापस;
पूर्ण

/**
 * pmcraid_initiate_reset - initiates reset sequence. This is called from
 * ISR/tasklet during error पूर्णांकerrupts including IOA unit check. If reset
 * is alपढ़ोy in progress, it just वापसs, otherwise initiates IOA reset
 * to bring IOA up to operational state.
 *
 * @pinstance: poपूर्णांकer to adapter instance काष्ठाure
 *
 * Return value
 *	 none
 */
अटल व्योम pmcraid_initiate_reset(काष्ठा pmcraid_instance *pinstance)
अणु
	काष्ठा pmcraid_cmd *cmd;

	/* If the reset is alपढ़ोy in progress, just वापस, otherwise start
	 * reset sequence and वापस
	 */
	अगर (!pinstance->ioa_reset_in_progress) अणु
		scsi_block_requests(pinstance->host);
		cmd = pmcraid_get_मुक्त_cmd(pinstance);

		अगर (cmd == शून्य) अणु
			pmcraid_err("no cmnd blocks for initiate_reset\n");
			वापस;
		पूर्ण

		pinstance->ioa_shutकरोwn_type = SHUTDOWN_NONE;
		pinstance->reset_cmd = cmd;
		pinstance->क्रमce_ioa_reset = 1;
		pmcraid_notअगरy_ioastate(pinstance,
					PMC_DEVICE_EVENT_RESET_START);
		pmcraid_ioa_reset(cmd);
	पूर्ण
पूर्ण

/**
 * pmcraid_reset_reload - utility routine क्रम करोing IOA reset either to bringup
 *			  or bringकरोwn IOA
 * @pinstance: poपूर्णांकer adapter instance काष्ठाure
 * @shutकरोwn_type: shutकरोwn type to be used NONE, NORMAL or ABRREV
 * @target_state: expected target state after reset
 *
 * Note: This command initiates reset and रुकोs क्रम its completion. Hence this
 * should not be called from isr/समयr/tasklet functions (समयout handlers,
 * error response handlers and पूर्णांकerrupt handlers).
 *
 * Return Value
 *	 1 in हाल ioa_state is not target_state, 0 otherwise.
 */
अटल पूर्णांक pmcraid_reset_reload(
	काष्ठा pmcraid_instance *pinstance,
	u8 shutकरोwn_type,
	u8 target_state
)
अणु
	काष्ठा pmcraid_cmd *reset_cmd = शून्य;
	अचिन्हित दीर्घ lock_flags;
	पूर्णांक reset = 1;

	spin_lock_irqsave(pinstance->host->host_lock, lock_flags);

	अगर (pinstance->ioa_reset_in_progress) अणु
		pmcraid_info("reset_reload: reset is already in progress\n");

		spin_unlock_irqrestore(pinstance->host->host_lock, lock_flags);

		रुको_event(pinstance->reset_रुको_q,
			   !pinstance->ioa_reset_in_progress);

		spin_lock_irqsave(pinstance->host->host_lock, lock_flags);

		अगर (pinstance->ioa_state == IOA_STATE_DEAD) अणु
			pmcraid_info("reset_reload: IOA is dead\n");
			जाओ out_unlock;
		पूर्ण

		अगर (pinstance->ioa_state == target_state) अणु
			reset = 0;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	pmcraid_info("reset_reload: proceeding with reset\n");
	scsi_block_requests(pinstance->host);
	reset_cmd = pmcraid_get_मुक्त_cmd(pinstance);
	अगर (reset_cmd == शून्य) अणु
		pmcraid_err("no free cmnd for reset_reload\n");
		जाओ out_unlock;
	पूर्ण

	अगर (shutकरोwn_type == SHUTDOWN_NORMAL)
		pinstance->ioa_bringकरोwn = 1;

	pinstance->ioa_shutकरोwn_type = shutकरोwn_type;
	pinstance->reset_cmd = reset_cmd;
	pinstance->क्रमce_ioa_reset = reset;
	pmcraid_info("reset_reload: initiating reset\n");
	pmcraid_ioa_reset(reset_cmd);
	spin_unlock_irqrestore(pinstance->host->host_lock, lock_flags);
	pmcraid_info("reset_reload: waiting for reset to complete\n");
	रुको_event(pinstance->reset_रुको_q,
		   !pinstance->ioa_reset_in_progress);

	pmcraid_info("reset_reload: reset is complete !!\n");
	scsi_unblock_requests(pinstance->host);
	वापस pinstance->ioa_state != target_state;

out_unlock:
	spin_unlock_irqrestore(pinstance->host->host_lock, lock_flags);
	वापस reset;
पूर्ण

/**
 * pmcraid_reset_bringकरोwn - wrapper over pmcraid_reset_reload to bringकरोwn IOA
 *
 * @pinstance: poपूर्णांकer to adapter instance काष्ठाure
 *
 * Return Value
 *	 whatever is वापसed from pmcraid_reset_reload
 */
अटल पूर्णांक pmcraid_reset_bringकरोwn(काष्ठा pmcraid_instance *pinstance)
अणु
	वापस pmcraid_reset_reload(pinstance,
				    SHUTDOWN_NORMAL,
				    IOA_STATE_UNKNOWN);
पूर्ण

/**
 * pmcraid_reset_bringup - wrapper over pmcraid_reset_reload to bring up IOA
 *
 * @pinstance: poपूर्णांकer to adapter instance काष्ठाure
 *
 * Return Value
 *	 whatever is वापसed from pmcraid_reset_reload
 */
अटल पूर्णांक pmcraid_reset_bringup(काष्ठा pmcraid_instance *pinstance)
अणु
	pmcraid_notअगरy_ioastate(pinstance, PMC_DEVICE_EVENT_RESET_START);

	वापस pmcraid_reset_reload(pinstance,
				    SHUTDOWN_NONE,
				    IOA_STATE_OPERATIONAL);
पूर्ण

/**
 * pmcraid_request_sense - Send request sense to a device
 * @cmd: pmcraid command काष्ठा
 *
 * This function sends a request sense to a device as a result of a check
 * condition. This method re-uses the same command block that failed earlier.
 */
अटल व्योम pmcraid_request_sense(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा pmcraid_ioarcb *ioarcb = &cmd->ioa_cb->ioarcb;
	काष्ठा pmcraid_ioadl_desc *ioadl = ioarcb->add_data.u.ioadl;
	काष्ठा device *dev = &cmd->drv_inst->pdev->dev;

	cmd->sense_buffer = cmd->scsi_cmd->sense_buffer;
	cmd->sense_buffer_dma = dma_map_single(dev, cmd->sense_buffer,
			SCSI_SENSE_BUFFERSIZE, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dev, cmd->sense_buffer_dma)) अणु
		pmcraid_err
			("couldn't allocate sense buffer for request sense\n");
		pmcraid_erp_करोne(cmd);
		वापस;
	पूर्ण

	/* re-use the command block */
	स_रखो(&cmd->ioa_cb->ioasa, 0, माप(काष्ठा pmcraid_ioasa));
	स_रखो(ioarcb->cdb, 0, PMCRAID_MAX_CDB_LEN);
	ioarcb->request_flags0 = (SYNC_COMPLETE |
				  NO_LINK_DESCS |
				  INHIBIT_UL_CHECK);
	ioarcb->request_type = REQ_TYPE_SCSI;
	ioarcb->cdb[0] = REQUEST_SENSE;
	ioarcb->cdb[4] = SCSI_SENSE_BUFFERSIZE;

	ioarcb->ioadl_bus_addr = cpu_to_le64((cmd->ioa_cb_bus_addr) +
					दुरत्व(काष्ठा pmcraid_ioarcb,
						add_data.u.ioadl[0]));
	ioarcb->ioadl_length = cpu_to_le32(माप(काष्ठा pmcraid_ioadl_desc));

	ioarcb->data_transfer_length = cpu_to_le32(SCSI_SENSE_BUFFERSIZE);

	ioadl->address = cpu_to_le64(cmd->sense_buffer_dma);
	ioadl->data_len = cpu_to_le32(SCSI_SENSE_BUFFERSIZE);
	ioadl->flags = IOADL_FLAGS_LAST_DESC;

	/* request sense might be called as part of error response processing
	 * which runs in tasklets context. It is possible that mid-layer might
	 * schedule queuecommand during this समय, hence, writting to IOARRIN
	 * must be protect by host_lock
	 */
	pmcraid_send_cmd(cmd, pmcraid_erp_करोne,
			 PMCRAID_REQUEST_SENSE_TIMEOUT,
			 pmcraid_समयout_handler);
पूर्ण

/**
 * pmcraid_cancel_all - cancel all outstanding IOARCBs as part of error recovery
 * @cmd: command that failed
 * @need_sense: true अगर request_sense is required after cancel all
 *
 * This function sends a cancel all to a device to clear the queue.
 */
अटल व्योम pmcraid_cancel_all(काष्ठा pmcraid_cmd *cmd, bool need_sense)
अणु
	काष्ठा scsi_cmnd *scsi_cmd = cmd->scsi_cmd;
	काष्ठा pmcraid_ioarcb *ioarcb = &cmd->ioa_cb->ioarcb;
	काष्ठा pmcraid_resource_entry *res = scsi_cmd->device->hostdata;

	स_रखो(ioarcb->cdb, 0, PMCRAID_MAX_CDB_LEN);
	ioarcb->request_flags0 = SYNC_OVERRIDE;
	ioarcb->request_type = REQ_TYPE_IOACMD;
	ioarcb->cdb[0] = PMCRAID_CANCEL_ALL_REQUESTS;

	अगर (RES_IS_GSCSI(res->cfg_entry))
		ioarcb->cdb[1] = PMCRAID_SYNC_COMPLETE_AFTER_CANCEL;

	ioarcb->ioadl_bus_addr = 0;
	ioarcb->ioadl_length = 0;
	ioarcb->data_transfer_length = 0;
	ioarcb->ioarcb_bus_addr &= cpu_to_le64((~0x1FULL));

	/* writing to IOARRIN must be रक्षित by host_lock, as mid-layer
	 * schedule queuecommand जबतक we are करोing this
	 */
	pmcraid_send_cmd(cmd, need_sense ?
			 pmcraid_erp_करोne : pmcraid_request_sense,
			 PMCRAID_REQUEST_SENSE_TIMEOUT,
			 pmcraid_समयout_handler);
पूर्ण

/**
 * pmcraid_frame_स्वतः_sense: frame fixed क्रमmat sense inक्रमmation
 *
 * @cmd: poपूर्णांकer to failing command block
 *
 * Return value
 *  none
 */
अटल व्योम pmcraid_frame_स्वतः_sense(काष्ठा pmcraid_cmd *cmd)
अणु
	u8 *sense_buf = cmd->scsi_cmd->sense_buffer;
	काष्ठा pmcraid_resource_entry *res = cmd->scsi_cmd->device->hostdata;
	काष्ठा pmcraid_ioasa *ioasa = &cmd->ioa_cb->ioasa;
	u32 ioasc = le32_to_cpu(ioasa->ioasc);
	u32 failing_lba = 0;

	स_रखो(sense_buf, 0, SCSI_SENSE_BUFFERSIZE);
	cmd->scsi_cmd->result = SAM_STAT_CHECK_CONDITION;

	अगर (RES_IS_VSET(res->cfg_entry) &&
	    ioasc == PMCRAID_IOASC_ME_READ_ERROR_NO_REALLOC &&
	    ioasa->u.vset.failing_lba_hi != 0) अणु

		sense_buf[0] = 0x72;
		sense_buf[1] = PMCRAID_IOASC_SENSE_KEY(ioasc);
		sense_buf[2] = PMCRAID_IOASC_SENSE_CODE(ioasc);
		sense_buf[3] = PMCRAID_IOASC_SENSE_QUAL(ioasc);

		sense_buf[7] = 12;
		sense_buf[8] = 0;
		sense_buf[9] = 0x0A;
		sense_buf[10] = 0x80;

		failing_lba = le32_to_cpu(ioasa->u.vset.failing_lba_hi);

		sense_buf[12] = (failing_lba & 0xff000000) >> 24;
		sense_buf[13] = (failing_lba & 0x00ff0000) >> 16;
		sense_buf[14] = (failing_lba & 0x0000ff00) >> 8;
		sense_buf[15] = failing_lba & 0x000000ff;

		failing_lba = le32_to_cpu(ioasa->u.vset.failing_lba_lo);

		sense_buf[16] = (failing_lba & 0xff000000) >> 24;
		sense_buf[17] = (failing_lba & 0x00ff0000) >> 16;
		sense_buf[18] = (failing_lba & 0x0000ff00) >> 8;
		sense_buf[19] = failing_lba & 0x000000ff;
	पूर्ण अन्यथा अणु
		sense_buf[0] = 0x70;
		sense_buf[2] = PMCRAID_IOASC_SENSE_KEY(ioasc);
		sense_buf[12] = PMCRAID_IOASC_SENSE_CODE(ioasc);
		sense_buf[13] = PMCRAID_IOASC_SENSE_QUAL(ioasc);

		अगर (ioasc == PMCRAID_IOASC_ME_READ_ERROR_NO_REALLOC) अणु
			अगर (RES_IS_VSET(res->cfg_entry))
				failing_lba =
					le32_to_cpu(ioasa->u.
						 vset.failing_lba_lo);
			sense_buf[0] |= 0x80;
			sense_buf[3] = (failing_lba >> 24) & 0xff;
			sense_buf[4] = (failing_lba >> 16) & 0xff;
			sense_buf[5] = (failing_lba >> 8) & 0xff;
			sense_buf[6] = failing_lba & 0xff;
		पूर्ण

		sense_buf[7] = 6; /* additional length */
	पूर्ण
पूर्ण

/**
 * pmcraid_error_handler - Error response handlers क्रम a SCSI op
 * @cmd: poपूर्णांकer to pmcraid_cmd that has failed
 *
 * This function determines whether or not to initiate ERP on the affected
 * device. This is called from a tasklet, which करोesn't hold any locks.
 *
 * Return value:
 *	 0 it caller can complete the request, otherwise 1 where in error
 *	 handler itself completes the request and वापसs the command block
 *	 back to मुक्त-pool
 */
अटल पूर्णांक pmcraid_error_handler(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा scsi_cmnd *scsi_cmd = cmd->scsi_cmd;
	काष्ठा pmcraid_resource_entry *res = scsi_cmd->device->hostdata;
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;
	काष्ठा pmcraid_ioasa *ioasa = &cmd->ioa_cb->ioasa;
	u32 ioasc = le32_to_cpu(ioasa->ioasc);
	u32 masked_ioasc = ioasc & PMCRAID_IOASC_SENSE_MASK;
	bool sense_copied = false;

	अगर (!res) अणु
		pmcraid_info("resource pointer is NULL\n");
		वापस 0;
	पूर्ण

	/* If this was a SCSI पढ़ो/ग_लिखो command keep count of errors */
	अगर (SCSI_CMD_TYPE(scsi_cmd->cmnd[0]) == SCSI_READ_CMD)
		atomic_inc(&res->पढ़ो_failures);
	अन्यथा अगर (SCSI_CMD_TYPE(scsi_cmd->cmnd[0]) == SCSI_WRITE_CMD)
		atomic_inc(&res->ग_लिखो_failures);

	अगर (!RES_IS_GSCSI(res->cfg_entry) &&
		masked_ioasc != PMCRAID_IOASC_HW_DEVICE_BUS_STATUS_ERROR) अणु
		pmcraid_frame_स्वतः_sense(cmd);
	पूर्ण

	/* Log IOASC/IOASA inक्रमmation based on user settings */
	pmcraid_ioasc_logger(ioasc, cmd);

	चयन (masked_ioasc) अणु

	हाल PMCRAID_IOASC_AC_TERMINATED_BY_HOST:
		scsi_cmd->result |= (DID_ABORT << 16);
		अवरोध;

	हाल PMCRAID_IOASC_IR_INVALID_RESOURCE_HANDLE:
	हाल PMCRAID_IOASC_HW_CANNOT_COMMUNICATE:
		scsi_cmd->result |= (DID_NO_CONNECT << 16);
		अवरोध;

	हाल PMCRAID_IOASC_NR_SYNC_REQUIRED:
		res->sync_reqd = 1;
		scsi_cmd->result |= (DID_IMM_RETRY << 16);
		अवरोध;

	हाल PMCRAID_IOASC_ME_READ_ERROR_NO_REALLOC:
		scsi_cmd->result |= (DID_PASSTHROUGH << 16);
		अवरोध;

	हाल PMCRAID_IOASC_UA_BUS_WAS_RESET:
	हाल PMCRAID_IOASC_UA_BUS_WAS_RESET_BY_OTHER:
		अगर (!res->reset_progress)
			scsi_report_bus_reset(pinstance->host,
					      scsi_cmd->device->channel);
		scsi_cmd->result |= (DID_ERROR << 16);
		अवरोध;

	हाल PMCRAID_IOASC_HW_DEVICE_BUS_STATUS_ERROR:
		scsi_cmd->result |= PMCRAID_IOASC_SENSE_STATUS(ioasc);
		res->sync_reqd = 1;

		/* अगर check_condition is not active वापस with error otherwise
		 * get/frame the sense buffer
		 */
		अगर (PMCRAID_IOASC_SENSE_STATUS(ioasc) !=
		    SAM_STAT_CHECK_CONDITION &&
		    PMCRAID_IOASC_SENSE_STATUS(ioasc) != SAM_STAT_ACA_ACTIVE)
			वापस 0;

		/* If we have स्वतः sense data as part of IOASA pass it to
		 * mid-layer
		 */
		अगर (ioasa->स्वतः_sense_length != 0) अणु
			लघु sense_len = le16_to_cpu(ioasa->स्वतः_sense_length);
			पूर्णांक data_size = min_t(u16, sense_len,
					      SCSI_SENSE_BUFFERSIZE);

			स_नकल(scsi_cmd->sense_buffer,
			       ioasa->sense_data,
			       data_size);
			sense_copied = true;
		पूर्ण

		अगर (RES_IS_GSCSI(res->cfg_entry))
			pmcraid_cancel_all(cmd, sense_copied);
		अन्यथा अगर (sense_copied)
			pmcraid_erp_करोne(cmd);
		अन्यथा
			pmcraid_request_sense(cmd);

		वापस 1;

	हाल PMCRAID_IOASC_NR_INIT_CMD_REQUIRED:
		अवरोध;

	शेष:
		अगर (PMCRAID_IOASC_SENSE_KEY(ioasc) > RECOVERED_ERROR)
			scsi_cmd->result |= (DID_ERROR << 16);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * pmcraid_reset_device - device reset handler functions
 *
 * @scsi_cmd: scsi command काष्ठा
 * @समयout: command समयout
 * @modअगरier: reset modअगरier indicating the reset sequence to be perक्रमmed
 *
 * This function issues a device reset to the affected device.
 * A LUN reset will be sent to the device first. If that करोes
 * not work, a target reset will be sent.
 *
 * Return value:
 *	SUCCESS / FAILED
 */
अटल पूर्णांक pmcraid_reset_device(
	काष्ठा scsi_cmnd *scsi_cmd,
	अचिन्हित दीर्घ समयout,
	u8 modअगरier)
अणु
	काष्ठा pmcraid_cmd *cmd;
	काष्ठा pmcraid_instance *pinstance;
	काष्ठा pmcraid_resource_entry *res;
	काष्ठा pmcraid_ioarcb *ioarcb;
	अचिन्हित दीर्घ lock_flags;
	u32 ioasc;

	pinstance =
		(काष्ठा pmcraid_instance *)scsi_cmd->device->host->hostdata;
	res = scsi_cmd->device->hostdata;

	अगर (!res) अणु
		sdev_prपूर्णांकk(KERN_ERR, scsi_cmd->device,
			    "reset_device: NULL resource pointer\n");
		वापस FAILED;
	पूर्ण

	/* If adapter is currently going through reset/reload, वापस failed.
	 * This will क्रमce the mid-layer to call _eh_bus/host reset, which
	 * will then go to sleep and रुको क्रम the reset to complete
	 */
	spin_lock_irqsave(pinstance->host->host_lock, lock_flags);
	अगर (pinstance->ioa_reset_in_progress ||
	    pinstance->ioa_state == IOA_STATE_DEAD) अणु
		spin_unlock_irqrestore(pinstance->host->host_lock, lock_flags);
		वापस FAILED;
	पूर्ण

	res->reset_progress = 1;
	pmcraid_info("Resetting %s resource with addr %x\n",
		     ((modअगरier & RESET_DEVICE_LUN) ? "LUN" :
		     ((modअगरier & RESET_DEVICE_TARGET) ? "TARGET" : "BUS")),
		     le32_to_cpu(res->cfg_entry.resource_address));

	/* get a मुक्त cmd block */
	cmd = pmcraid_get_मुक्त_cmd(pinstance);

	अगर (cmd == शून्य) अणु
		spin_unlock_irqrestore(pinstance->host->host_lock, lock_flags);
		pmcraid_err("%s: no cmd blocks are available\n", __func__);
		वापस FAILED;
	पूर्ण

	ioarcb = &cmd->ioa_cb->ioarcb;
	ioarcb->resource_handle = res->cfg_entry.resource_handle;
	ioarcb->request_type = REQ_TYPE_IOACMD;
	ioarcb->cdb[0] = PMCRAID_RESET_DEVICE;

	/* Initialize reset modअगरier bits */
	अगर (modअगरier)
		modअगरier = ENABLE_RESET_MODIFIER | modअगरier;

	ioarcb->cdb[1] = modअगरier;

	init_completion(&cmd->रुको_क्रम_completion);
	cmd->completion_req = 1;

	pmcraid_info("cmd(CDB[0] = %x) for %x with index = %d\n",
		     cmd->ioa_cb->ioarcb.cdb[0],
		     le32_to_cpu(cmd->ioa_cb->ioarcb.resource_handle),
		     le32_to_cpu(cmd->ioa_cb->ioarcb.response_handle) >> 2);

	pmcraid_send_cmd(cmd,
			 pmcraid_पूर्णांकernal_करोne,
			 समयout,
			 pmcraid_समयout_handler);

	spin_unlock_irqrestore(pinstance->host->host_lock, lock_flags);

	/* RESET_DEVICE command completes after all pending IOARCBs are
	 * completed. Once this command is completed, pmcraind_पूर्णांकernal_करोne
	 * will wake up the 'completion' queue.
	 */
	रुको_क्रम_completion(&cmd->रुको_क्रम_completion);

	/* complete the command here itself and वापस the command block
	 * to मुक्त list
	 */
	pmcraid_वापस_cmd(cmd);
	res->reset_progress = 0;
	ioasc = le32_to_cpu(cmd->ioa_cb->ioasa.ioasc);

	/* set the वापस value based on the वापसed ioasc */
	वापस PMCRAID_IOASC_SENSE_KEY(ioasc) ? FAILED : SUCCESS;
पूर्ण

/**
 * _pmcraid_io_करोne - helper क्रम pmcraid_io_करोne function
 *
 * @cmd: poपूर्णांकer to pmcraid command काष्ठा
 * @reslen: residual data length to be set in the ioasa
 * @ioasc: ioasc either वापसed by IOA or set by driver itself.
 *
 * This function is invoked by pmcraid_io_करोne to complete mid-layer
 * scsi ops.
 *
 * Return value:
 *	  0 अगर caller is required to वापस it to मुक्त_pool. Returns 1 अगर
 *	  caller need not worry about मुक्तing command block as error handler
 *	  will take care of that.
 */

अटल पूर्णांक _pmcraid_io_करोne(काष्ठा pmcraid_cmd *cmd, पूर्णांक reslen, पूर्णांक ioasc)
अणु
	काष्ठा scsi_cmnd *scsi_cmd = cmd->scsi_cmd;
	पूर्णांक rc = 0;

	scsi_set_resid(scsi_cmd, reslen);

	pmcraid_info("response(%d) CDB[0] = %x ioasc:result: %x:%x\n",
		le32_to_cpu(cmd->ioa_cb->ioarcb.response_handle) >> 2,
		cmd->ioa_cb->ioarcb.cdb[0],
		ioasc, scsi_cmd->result);

	अगर (PMCRAID_IOASC_SENSE_KEY(ioasc) != 0)
		rc = pmcraid_error_handler(cmd);

	अगर (rc == 0) अणु
		scsi_dma_unmap(scsi_cmd);
		scsi_cmd->scsi_करोne(scsi_cmd);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * pmcraid_io_करोne - SCSI completion function
 *
 * @cmd: poपूर्णांकer to pmcraid command काष्ठा
 *
 * This function is invoked by tasklet/mid-layer error handler to completing
 * the SCSI ops sent from mid-layer.
 *
 * Return value
 *	  none
 */

अटल व्योम pmcraid_io_करोne(काष्ठा pmcraid_cmd *cmd)
अणु
	u32 ioasc = le32_to_cpu(cmd->ioa_cb->ioasa.ioasc);
	u32 reslen = le32_to_cpu(cmd->ioa_cb->ioasa.residual_data_length);

	अगर (_pmcraid_io_करोne(cmd, reslen, ioasc) == 0)
		pmcraid_वापस_cmd(cmd);
पूर्ण

/**
 * pmcraid_पात_cmd - Aborts a single IOARCB alपढ़ोy submitted to IOA
 *
 * @cmd: command block of the command to be पातed
 *
 * Return Value:
 *	 वापसs poपूर्णांकer to command काष्ठाure used as cancelling cmd
 */
अटल काष्ठा pmcraid_cmd *pmcraid_पात_cmd(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा pmcraid_cmd *cancel_cmd;
	काष्ठा pmcraid_instance *pinstance;

	pinstance = (काष्ठा pmcraid_instance *)cmd->drv_inst;

	cancel_cmd = pmcraid_get_मुक्त_cmd(pinstance);

	अगर (cancel_cmd == शून्य) अणु
		pmcraid_err("%s: no cmd blocks are available\n", __func__);
		वापस शून्य;
	पूर्ण

	pmcraid_prepare_cancel_cmd(cancel_cmd, cmd);

	pmcraid_info("aborting command CDB[0]= %x with index = %d\n",
		cmd->ioa_cb->ioarcb.cdb[0],
		le32_to_cpu(cmd->ioa_cb->ioarcb.response_handle) >> 2);

	init_completion(&cancel_cmd->रुको_क्रम_completion);
	cancel_cmd->completion_req = 1;

	pmcraid_info("command (%d) CDB[0] = %x for %x\n",
		le32_to_cpu(cancel_cmd->ioa_cb->ioarcb.response_handle) >> 2,
		cancel_cmd->ioa_cb->ioarcb.cdb[0],
		le32_to_cpu(cancel_cmd->ioa_cb->ioarcb.resource_handle));

	pmcraid_send_cmd(cancel_cmd,
			 pmcraid_पूर्णांकernal_करोne,
			 PMCRAID_INTERNAL_TIMEOUT,
			 pmcraid_समयout_handler);
	वापस cancel_cmd;
पूर्ण

/**
 * pmcraid_पात_complete - Waits क्रम ABORT TASK completion
 *
 * @cancel_cmd: command block use as cancelling command
 *
 * Return Value:
 *	 वापसs SUCCESS अगर ABORT TASK has good completion
 *	 otherwise FAILED
 */
अटल पूर्णांक pmcraid_पात_complete(काष्ठा pmcraid_cmd *cancel_cmd)
अणु
	काष्ठा pmcraid_resource_entry *res;
	u32 ioasc;

	रुको_क्रम_completion(&cancel_cmd->रुको_क्रम_completion);
	res = cancel_cmd->res;
	cancel_cmd->res = शून्य;
	ioasc = le32_to_cpu(cancel_cmd->ioa_cb->ioasa.ioasc);

	/* If the पात task is not समयd out we will get a Good completion
	 * as sense_key, otherwise we may get one the following responses
	 * due to subsequent bus reset or device reset. In हाल IOASC is
	 * NR_SYNC_REQUIRED, set sync_reqd flag क्रम the corresponding resource
	 */
	अगर (ioasc == PMCRAID_IOASC_UA_BUS_WAS_RESET ||
	    ioasc == PMCRAID_IOASC_NR_SYNC_REQUIRED) अणु
		अगर (ioasc == PMCRAID_IOASC_NR_SYNC_REQUIRED)
			res->sync_reqd = 1;
		ioasc = 0;
	पूर्ण

	/* complete the command here itself */
	pmcraid_वापस_cmd(cancel_cmd);
	वापस PMCRAID_IOASC_SENSE_KEY(ioasc) ? FAILED : SUCCESS;
पूर्ण

/**
 * pmcraid_eh_पात_handler - entry poपूर्णांक क्रम पातing a single task on errors
 *
 * @scsi_cmd:   scsi command काष्ठा given by mid-layer. When this is called
 *		mid-layer ensures that no other commands are queued. This
 *		never माला_लो called under पूर्णांकerrupt, but a separate eh thपढ़ो.
 *
 * Return value:
 *	 SUCCESS / FAILED
 */
अटल पूर्णांक pmcraid_eh_पात_handler(काष्ठा scsi_cmnd *scsi_cmd)
अणु
	काष्ठा pmcraid_instance *pinstance;
	काष्ठा pmcraid_cmd *cmd;
	काष्ठा pmcraid_resource_entry *res;
	अचिन्हित दीर्घ host_lock_flags;
	अचिन्हित दीर्घ pending_lock_flags;
	काष्ठा pmcraid_cmd *cancel_cmd = शून्य;
	पूर्णांक cmd_found = 0;
	पूर्णांक rc = FAILED;

	pinstance =
		(काष्ठा pmcraid_instance *)scsi_cmd->device->host->hostdata;

	scmd_prपूर्णांकk(KERN_INFO, scsi_cmd,
		    "I/O command timed out, aborting it.\n");

	res = scsi_cmd->device->hostdata;

	अगर (res == शून्य)
		वापस rc;

	/* If we are currently going through reset/reload, वापस failed.
	 * This will क्रमce the mid-layer to eventually call
	 * pmcraid_eh_host_reset which will then go to sleep and रुको क्रम the
	 * reset to complete
	 */
	spin_lock_irqsave(pinstance->host->host_lock, host_lock_flags);

	अगर (pinstance->ioa_reset_in_progress ||
	    pinstance->ioa_state == IOA_STATE_DEAD) अणु
		spin_unlock_irqrestore(pinstance->host->host_lock,
				       host_lock_flags);
		वापस rc;
	पूर्ण

	/* loop over pending cmd list to find cmd corresponding to this
	 * scsi_cmd. Note that this command might not have been completed
	 * alपढ़ोy. locking: all pending commands are रक्षित with
	 * pending_pool_lock.
	 */
	spin_lock_irqsave(&pinstance->pending_pool_lock, pending_lock_flags);
	list_क्रम_each_entry(cmd, &pinstance->pending_cmd_pool, मुक्त_list) अणु

		अगर (cmd->scsi_cmd == scsi_cmd) अणु
			cmd_found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&pinstance->pending_pool_lock,
				pending_lock_flags);

	/* If the command to be पातed was given to IOA and still pending with
	 * it, send ABORT_TASK to पात this and रुको क्रम its completion
	 */
	अगर (cmd_found)
		cancel_cmd = pmcraid_पात_cmd(cmd);

	spin_unlock_irqrestore(pinstance->host->host_lock,
			       host_lock_flags);

	अगर (cancel_cmd) अणु
		cancel_cmd->res = cmd->scsi_cmd->device->hostdata;
		rc = pmcraid_पात_complete(cancel_cmd);
	पूर्ण

	वापस cmd_found ? rc : SUCCESS;
पूर्ण

/**
 * pmcraid_eh_device_reset_handler - bus/target/device reset handler callbacks
 *
 * @scmd: poपूर्णांकer to scsi_cmd that was sent to the resource to be reset.
 *
 * All these routines invokve pmcraid_reset_device with appropriate parameters.
 * Since these are called from mid-layer EH thपढ़ो, no other IO will be queued
 * to the resource being reset. However, control path (IOCTL) may be active so
 * it is necessary to synchronize IOARRIN ग_लिखोs which pmcraid_reset_device
 * takes care by locking/unlocking host_lock.
 *
 * Return value
 *	SUCCESS or FAILED
 */
अटल पूर्णांक pmcraid_eh_device_reset_handler(काष्ठा scsi_cmnd *scmd)
अणु
	scmd_prपूर्णांकk(KERN_INFO, scmd,
		    "resetting device due to an I/O command timeout.\n");
	वापस pmcraid_reset_device(scmd,
				    PMCRAID_INTERNAL_TIMEOUT,
				    RESET_DEVICE_LUN);
पूर्ण

अटल पूर्णांक pmcraid_eh_bus_reset_handler(काष्ठा scsi_cmnd *scmd)
अणु
	scmd_prपूर्णांकk(KERN_INFO, scmd,
		    "Doing bus reset due to an I/O command timeout.\n");
	वापस pmcraid_reset_device(scmd,
				    PMCRAID_RESET_BUS_TIMEOUT,
				    RESET_DEVICE_BUS);
पूर्ण

अटल पूर्णांक pmcraid_eh_target_reset_handler(काष्ठा scsi_cmnd *scmd)
अणु
	scmd_prपूर्णांकk(KERN_INFO, scmd,
		    "Doing target reset due to an I/O command timeout.\n");
	वापस pmcraid_reset_device(scmd,
				    PMCRAID_INTERNAL_TIMEOUT,
				    RESET_DEVICE_TARGET);
पूर्ण

/**
 * pmcraid_eh_host_reset_handler - adapter reset handler callback
 *
 * @scmd: poपूर्णांकer to scsi_cmd that was sent to a resource of adapter
 *
 * Initiates adapter reset to bring it up to operational state
 *
 * Return value
 *	SUCCESS or FAILED
 */
अटल पूर्णांक pmcraid_eh_host_reset_handler(काष्ठा scsi_cmnd *scmd)
अणु
	अचिन्हित दीर्घ पूर्णांकerval = 10000; /* 10 seconds पूर्णांकerval */
	पूर्णांक रुकोs = jअगरfies_to_msecs(PMCRAID_RESET_HOST_TIMEOUT) / पूर्णांकerval;
	काष्ठा pmcraid_instance *pinstance =
		(काष्ठा pmcraid_instance *)(scmd->device->host->hostdata);


	/* रुको क्रम an additional 150 seconds just in हाल firmware could come
	 * up and अगर it could complete all the pending commands excluding the
	 * two HCAM (CCN and LDN).
	 */
	जबतक (रुकोs--) अणु
		अगर (atomic_पढ़ो(&pinstance->outstanding_cmds) <=
		    PMCRAID_MAX_HCAM_CMD)
			वापस SUCCESS;
		msleep(पूर्णांकerval);
	पूर्ण

	dev_err(&pinstance->pdev->dev,
		"Adapter being reset due to an I/O command timeout.\n");
	वापस pmcraid_reset_bringup(pinstance) == 0 ? SUCCESS : FAILED;
पूर्ण

/**
 * pmcraid_init_ioadls - initializes IOADL related fields in IOARCB
 * @cmd: pmcraid command काष्ठा
 * @sgcount: count of scatter-gather elements
 *
 * Return value
 *   वापसs poपूर्णांकer pmcraid_ioadl_desc, initialized to poपूर्णांक to पूर्णांकernal
 *   or बाह्यal IOADLs
 */
अटल काष्ठा pmcraid_ioadl_desc *
pmcraid_init_ioadls(काष्ठा pmcraid_cmd *cmd, पूर्णांक sgcount)
अणु
	काष्ठा pmcraid_ioadl_desc *ioadl;
	काष्ठा pmcraid_ioarcb *ioarcb = &cmd->ioa_cb->ioarcb;
	पूर्णांक ioadl_count = 0;

	अगर (ioarcb->add_cmd_param_length)
		ioadl_count = DIV_ROUND_UP(le16_to_cpu(ioarcb->add_cmd_param_length), 16);
	ioarcb->ioadl_length = cpu_to_le32(माप(काष्ठा pmcraid_ioadl_desc) * sgcount);

	अगर ((sgcount + ioadl_count) > (ARRAY_SIZE(ioarcb->add_data.u.ioadl))) अणु
		/* बाह्यal ioadls start at offset 0x80 from control_block
		 * काष्ठाure, re-using 24 out of 27 ioadls part of IOARCB.
		 * It is necessary to indicate to firmware that driver is
		 * using ioadls to be treated as बाह्यal to IOARCB.
		 */
		ioarcb->ioarcb_bus_addr &= cpu_to_le64(~(0x1FULL));
		ioarcb->ioadl_bus_addr =
			cpu_to_le64((cmd->ioa_cb_bus_addr) +
				दुरत्व(काष्ठा pmcraid_ioarcb,
					add_data.u.ioadl[3]));
		ioadl = &ioarcb->add_data.u.ioadl[3];
	पूर्ण अन्यथा अणु
		ioarcb->ioadl_bus_addr =
			cpu_to_le64((cmd->ioa_cb_bus_addr) +
				दुरत्व(काष्ठा pmcraid_ioarcb,
					add_data.u.ioadl[ioadl_count]));

		ioadl = &ioarcb->add_data.u.ioadl[ioadl_count];
		ioarcb->ioarcb_bus_addr |=
			cpu_to_le64(DIV_ROUND_CLOSEST(sgcount + ioadl_count, 8));
	पूर्ण

	वापस ioadl;
पूर्ण

/**
 * pmcraid_build_ioadl - Build a scatter/gather list and map the buffer
 * @pinstance: poपूर्णांकer to adapter instance काष्ठाure
 * @cmd: pmcraid command काष्ठा
 *
 * This function is invoked by queuecommand entry poपूर्णांक जबतक sending a command
 * to firmware. This builds ioadl descriptors and sets up ioarcb fields.
 *
 * Return value:
 *	0 on success or -1 on failure
 */
अटल पूर्णांक pmcraid_build_ioadl(
	काष्ठा pmcraid_instance *pinstance,
	काष्ठा pmcraid_cmd *cmd
)
अणु
	पूर्णांक i, nseg;
	काष्ठा scatterlist *sglist;

	काष्ठा scsi_cmnd *scsi_cmd = cmd->scsi_cmd;
	काष्ठा pmcraid_ioarcb *ioarcb = &(cmd->ioa_cb->ioarcb);
	काष्ठा pmcraid_ioadl_desc *ioadl;

	u32 length = scsi_bufflen(scsi_cmd);

	अगर (!length)
		वापस 0;

	nseg = scsi_dma_map(scsi_cmd);

	अगर (nseg < 0) अणु
		scmd_prपूर्णांकk(KERN_ERR, scsi_cmd, "scsi_map_dma failed!\n");
		वापस -1;
	पूर्ण अन्यथा अगर (nseg > PMCRAID_MAX_IOADLS) अणु
		scsi_dma_unmap(scsi_cmd);
		scmd_prपूर्णांकk(KERN_ERR, scsi_cmd,
			"sg count is (%d) more than allowed!\n", nseg);
		वापस -1;
	पूर्ण

	/* Initialize IOARCB data transfer length fields */
	अगर (scsi_cmd->sc_data_direction == DMA_TO_DEVICE)
		ioarcb->request_flags0 |= TRANSFER_सूची_WRITE;

	ioarcb->request_flags0 |= NO_LINK_DESCS;
	ioarcb->data_transfer_length = cpu_to_le32(length);
	ioadl = pmcraid_init_ioadls(cmd, nseg);

	/* Initialize IOADL descriptor addresses */
	scsi_क्रम_each_sg(scsi_cmd, sglist, nseg, i) अणु
		ioadl[i].data_len = cpu_to_le32(sg_dma_len(sglist));
		ioadl[i].address = cpu_to_le64(sg_dma_address(sglist));
		ioadl[i].flags = 0;
	पूर्ण
	/* setup last descriptor */
	ioadl[i - 1].flags = IOADL_FLAGS_LAST_DESC;

	वापस 0;
पूर्ण

/**
 * pmcraid_मुक्त_sglist - Frees an allocated SG buffer list
 * @sglist: scatter/gather list poपूर्णांकer
 *
 * Free a DMA'able memory previously allocated with pmcraid_alloc_sglist
 *
 * Return value:
 *	none
 */
अटल व्योम pmcraid_मुक्त_sglist(काष्ठा pmcraid_sglist *sglist)
अणु
	sgl_मुक्त_order(sglist->scatterlist, sglist->order);
	kमुक्त(sglist);
पूर्ण

/**
 * pmcraid_alloc_sglist - Allocates memory क्रम a SG list
 * @buflen: buffer length
 *
 * Allocates a DMA'able buffer in chunks and assembles a scatter/gather
 * list.
 *
 * Return value
 *	poपूर्णांकer to sglist / शून्य on failure
 */
अटल काष्ठा pmcraid_sglist *pmcraid_alloc_sglist(पूर्णांक buflen)
अणु
	काष्ठा pmcraid_sglist *sglist;
	पूर्णांक sg_size;
	पूर्णांक order;

	sg_size = buflen / (PMCRAID_MAX_IOADLS - 1);
	order = (sg_size > 0) ? get_order(sg_size) : 0;

	/* Allocate a scatter/gather list क्रम the DMA */
	sglist = kzalloc(माप(काष्ठा pmcraid_sglist), GFP_KERNEL);
	अगर (sglist == शून्य)
		वापस शून्य;

	sglist->order = order;
	sgl_alloc_order(buflen, order, false,
			GFP_KERNEL | GFP_DMA | __GFP_ZERO, &sglist->num_sg);

	वापस sglist;
पूर्ण

/**
 * pmcraid_copy_sglist - Copy user buffer to kernel buffer's SG list
 * @sglist: scatter/gather list poपूर्णांकer
 * @buffer: buffer poपूर्णांकer
 * @len: buffer length
 * @direction: data transfer direction
 *
 * Copy a user buffer पूर्णांकo a buffer allocated by pmcraid_alloc_sglist
 *
 * Return value:
 * 0 on success / other on failure
 */
अटल पूर्णांक pmcraid_copy_sglist(
	काष्ठा pmcraid_sglist *sglist,
	व्योम __user *buffer,
	u32 len,
	पूर्णांक direction
)
अणु
	काष्ठा scatterlist *sg;
	व्योम *kaddr;
	पूर्णांक bsize_elem;
	पूर्णांक i;
	पूर्णांक rc = 0;

	/* Determine the actual number of bytes per element */
	bsize_elem = PAGE_SIZE * (1 << sglist->order);

	sg = sglist->scatterlist;

	क्रम (i = 0; i < (len / bsize_elem); i++, sg = sg_next(sg), buffer += bsize_elem) अणु
		काष्ठा page *page = sg_page(sg);

		kaddr = kmap(page);
		अगर (direction == DMA_TO_DEVICE)
			rc = copy_from_user(kaddr, buffer, bsize_elem);
		अन्यथा
			rc = copy_to_user(buffer, kaddr, bsize_elem);

		kunmap(page);

		अगर (rc) अणु
			pmcraid_err("failed to copy user data into sg list\n");
			वापस -EFAULT;
		पूर्ण

		sg->length = bsize_elem;
	पूर्ण

	अगर (len % bsize_elem) अणु
		काष्ठा page *page = sg_page(sg);

		kaddr = kmap(page);

		अगर (direction == DMA_TO_DEVICE)
			rc = copy_from_user(kaddr, buffer, len % bsize_elem);
		अन्यथा
			rc = copy_to_user(buffer, kaddr, len % bsize_elem);

		kunmap(page);

		sg->length = len % bsize_elem;
	पूर्ण

	अगर (rc) अणु
		pmcraid_err("failed to copy user data into sg list\n");
		rc = -EFAULT;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * pmcraid_queuecommand_lck - Queue a mid-layer request
 * @scsi_cmd: scsi command काष्ठा
 * @करोne: करोne function
 *
 * This function queues a request generated by the mid-layer. Midlayer calls
 * this routine within host->lock. Some of the functions called by queuecommand
 * would use cmd block queue locks (मुक्त_pool_lock and pending_pool_lock)
 *
 * Return value:
 *	  0 on success
 *	  SCSI_MLQUEUE_DEVICE_BUSY अगर device is busy
 *	  SCSI_MLQUEUE_HOST_BUSY अगर host is busy
 */
अटल पूर्णांक pmcraid_queuecommand_lck(
	काष्ठा scsi_cmnd *scsi_cmd,
	व्योम (*करोne) (काष्ठा scsi_cmnd *)
)
अणु
	काष्ठा pmcraid_instance *pinstance;
	काष्ठा pmcraid_resource_entry *res;
	काष्ठा pmcraid_ioarcb *ioarcb;
	काष्ठा pmcraid_cmd *cmd;
	u32 fw_version;
	पूर्णांक rc = 0;

	pinstance =
		(काष्ठा pmcraid_instance *)scsi_cmd->device->host->hostdata;
	fw_version = be16_to_cpu(pinstance->inq_data->fw_version);
	scsi_cmd->scsi_करोne = करोne;
	res = scsi_cmd->device->hostdata;
	scsi_cmd->result = (DID_OK << 16);

	/* अगर adapter is marked as dead, set result to DID_NO_CONNECT complete
	 * the command
	 */
	अगर (pinstance->ioa_state == IOA_STATE_DEAD) अणु
		pmcraid_info("IOA is dead, but queuecommand is scheduled\n");
		scsi_cmd->result = (DID_NO_CONNECT << 16);
		scsi_cmd->scsi_करोne(scsi_cmd);
		वापस 0;
	पूर्ण

	/* If IOA reset is in progress, can't queue the commands */
	अगर (pinstance->ioa_reset_in_progress)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	/* Firmware करोesn't support SYNCHRONIZE_CACHE command (0x35), complete
	 * the command here itself with success वापस
	 */
	अगर (scsi_cmd->cmnd[0] == SYNCHRONIZE_CACHE) अणु
		pmcraid_info("SYNC_CACHE(0x35), completing in driver itself\n");
		scsi_cmd->scsi_करोne(scsi_cmd);
		वापस 0;
	पूर्ण

	/* initialize the command and IOARCB to be sent to IOA */
	cmd = pmcraid_get_मुक्त_cmd(pinstance);

	अगर (cmd == शून्य) अणु
		pmcraid_err("free command block is not available\n");
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	cmd->scsi_cmd = scsi_cmd;
	ioarcb = &(cmd->ioa_cb->ioarcb);
	स_नकल(ioarcb->cdb, scsi_cmd->cmnd, scsi_cmd->cmd_len);
	ioarcb->resource_handle = res->cfg_entry.resource_handle;
	ioarcb->request_type = REQ_TYPE_SCSI;

	/* set hrrq number where the IOA should respond to. Note that all cmds
	 * generated पूर्णांकernally uses hrrq_id 0, exception to this is the cmd
	 * block of scsi_cmd which is re-used (e.g. cancel/पात), which uses
	 * hrrq_id asचिन्हित here in queuecommand
	 */
	ioarcb->hrrq_id = atomic_add_वापस(1, &(pinstance->last_message_id)) %
			  pinstance->num_hrrq;
	cmd->cmd_करोne = pmcraid_io_करोne;

	अगर (RES_IS_GSCSI(res->cfg_entry) || RES_IS_VSET(res->cfg_entry)) अणु
		अगर (scsi_cmd->underflow == 0)
			ioarcb->request_flags0 |= INHIBIT_UL_CHECK;

		अगर (res->sync_reqd) अणु
			ioarcb->request_flags0 |= SYNC_COMPLETE;
			res->sync_reqd = 0;
		पूर्ण

		ioarcb->request_flags0 |= NO_LINK_DESCS;

		अगर (scsi_cmd->flags & SCMD_TAGGED)
			ioarcb->request_flags1 |= TASK_TAG_SIMPLE;

		अगर (RES_IS_GSCSI(res->cfg_entry))
			ioarcb->request_flags1 |= DELAY_AFTER_RESET;
	पूर्ण

	rc = pmcraid_build_ioadl(pinstance, cmd);

	pmcraid_info("command (%d) CDB[0] = %x for %x:%x:%x:%x\n",
		     le32_to_cpu(ioarcb->response_handle) >> 2,
		     scsi_cmd->cmnd[0], pinstance->host->unique_id,
		     RES_IS_VSET(res->cfg_entry) ? PMCRAID_VSET_BUS_ID :
			PMCRAID_PHYS_BUS_ID,
		     RES_IS_VSET(res->cfg_entry) ?
			(fw_version <= PMCRAID_FW_VERSION_1 ?
				res->cfg_entry.unique_flags1 :
				le16_to_cpu(res->cfg_entry.array_id) & 0xFF) :
			RES_TARGET(res->cfg_entry.resource_address),
		     RES_LUN(res->cfg_entry.resource_address));

	अगर (likely(rc == 0)) अणु
		_pmcraid_fire_command(cmd);
	पूर्ण अन्यथा अणु
		pmcraid_err("queuecommand could not build ioadl\n");
		pmcraid_वापस_cmd(cmd);
		rc = SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	वापस rc;
पूर्ण

अटल DEF_SCSI_QCMD(pmcraid_queuecommand)

/*
 * pmcraid_खोलो -अक्षर node "open" entry, allowed only users with admin access
 */
अटल पूर्णांक pmcraid_chr_खोलो(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा pmcraid_instance *pinstance;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	/* Populate adapter instance * poपूर्णांकer क्रम use by ioctl */
	pinstance = container_of(inode->i_cdev, काष्ठा pmcraid_instance, cdev);
	filep->निजी_data = pinstance;

	वापस 0;
पूर्ण

/*
 * pmcraid_fasync - Async notअगरier registration from applications
 *
 * This function adds the calling process to a driver global queue. When an
 * event occurs, SIGIO will be sent to all processes in this queue.
 */
अटल पूर्णांक pmcraid_chr_fasync(पूर्णांक fd, काष्ठा file *filep, पूर्णांक mode)
अणु
	काष्ठा pmcraid_instance *pinstance;
	पूर्णांक rc;

	pinstance = filep->निजी_data;
	mutex_lock(&pinstance->aen_queue_lock);
	rc = fasync_helper(fd, filep, mode, &pinstance->aen_queue);
	mutex_unlock(&pinstance->aen_queue_lock);

	वापस rc;
पूर्ण


/**
 * pmcraid_build_passthrough_ioadls - builds SG elements क्रम passthrough
 * commands sent over IOCTL पूर्णांकerface
 *
 * @cmd       : poपूर्णांकer to काष्ठा pmcraid_cmd
 * @buflen    : length of the request buffer
 * @direction : data transfer direction
 *
 * Return value
 *  0 on success, non-zero error code on failure
 */
अटल पूर्णांक pmcraid_build_passthrough_ioadls(
	काष्ठा pmcraid_cmd *cmd,
	पूर्णांक buflen,
	पूर्णांक direction
)
अणु
	काष्ठा pmcraid_sglist *sglist = शून्य;
	काष्ठा scatterlist *sg = शून्य;
	काष्ठा pmcraid_ioarcb *ioarcb = &cmd->ioa_cb->ioarcb;
	काष्ठा pmcraid_ioadl_desc *ioadl;
	पूर्णांक i;

	sglist = pmcraid_alloc_sglist(buflen);

	अगर (!sglist) अणु
		pmcraid_err("can't allocate memory for passthrough SGls\n");
		वापस -ENOMEM;
	पूर्ण

	sglist->num_dma_sg = dma_map_sg(&cmd->drv_inst->pdev->dev,
					sglist->scatterlist,
					sglist->num_sg, direction);

	अगर (!sglist->num_dma_sg || sglist->num_dma_sg > PMCRAID_MAX_IOADLS) अणु
		dev_err(&cmd->drv_inst->pdev->dev,
			"Failed to map passthrough buffer!\n");
		pmcraid_मुक्त_sglist(sglist);
		वापस -EIO;
	पूर्ण

	cmd->sglist = sglist;
	ioarcb->request_flags0 |= NO_LINK_DESCS;

	ioadl = pmcraid_init_ioadls(cmd, sglist->num_dma_sg);

	/* Initialize IOADL descriptor addresses */
	क्रम_each_sg(sglist->scatterlist, sg, sglist->num_dma_sg, i) अणु
		ioadl[i].data_len = cpu_to_le32(sg_dma_len(sg));
		ioadl[i].address = cpu_to_le64(sg_dma_address(sg));
		ioadl[i].flags = 0;
	पूर्ण

	/* setup the last descriptor */
	ioadl[i - 1].flags = IOADL_FLAGS_LAST_DESC;

	वापस 0;
पूर्ण


/**
 * pmcraid_release_passthrough_ioadls - release passthrough ioadls
 *
 * @cmd: poपूर्णांकer to काष्ठा pmcraid_cmd क्रम which ioadls were allocated
 * @buflen: size of the request buffer
 * @direction: data transfer direction
 *
 * Return value
 *  0 on success, non-zero error code on failure
 */
अटल व्योम pmcraid_release_passthrough_ioadls(
	काष्ठा pmcraid_cmd *cmd,
	पूर्णांक buflen,
	पूर्णांक direction
)
अणु
	काष्ठा pmcraid_sglist *sglist = cmd->sglist;

	अगर (buflen > 0) अणु
		dma_unmap_sg(&cmd->drv_inst->pdev->dev,
			     sglist->scatterlist,
			     sglist->num_sg,
			     direction);
		pmcraid_मुक्त_sglist(sglist);
		cmd->sglist = शून्य;
	पूर्ण
पूर्ण

/**
 * pmcraid_ioctl_passthrough - handling passthrough IOCTL commands
 *
 * @pinstance: poपूर्णांकer to adapter instance काष्ठाure
 * @ioctl_cmd: ioctl code
 * @buflen: unused
 * @arg: poपूर्णांकer to pmcraid_passthrough_buffer user buffer
 *
 * Return value
 *  0 on success, non-zero error code on failure
 */
अटल दीर्घ pmcraid_ioctl_passthrough(
	काष्ठा pmcraid_instance *pinstance,
	अचिन्हित पूर्णांक ioctl_cmd,
	अचिन्हित पूर्णांक buflen,
	व्योम __user *arg
)
अणु
	काष्ठा pmcraid_passthrough_ioctl_buffer *buffer;
	काष्ठा pmcraid_ioarcb *ioarcb;
	काष्ठा pmcraid_cmd *cmd;
	काष्ठा pmcraid_cmd *cancel_cmd;
	व्योम __user *request_buffer;
	अचिन्हित दीर्घ request_offset;
	अचिन्हित दीर्घ lock_flags;
	व्योम __user *ioasa;
	u32 ioasc;
	पूर्णांक request_size;
	पूर्णांक buffer_size;
	u8 direction;
	पूर्णांक rc = 0;

	/* If IOA reset is in progress, रुको 10 secs क्रम reset to complete */
	अगर (pinstance->ioa_reset_in_progress) अणु
		rc = रुको_event_पूर्णांकerruptible_समयout(
				pinstance->reset_रुको_q,
				!pinstance->ioa_reset_in_progress,
				msecs_to_jअगरfies(10000));

		अगर (!rc)
			वापस -ETIMEDOUT;
		अन्यथा अगर (rc < 0)
			वापस -ERESTARTSYS;
	पूर्ण

	/* If adapter is not in operational state, वापस error */
	अगर (pinstance->ioa_state != IOA_STATE_OPERATIONAL) अणु
		pmcraid_err("IOA is not operational\n");
		वापस -ENOTTY;
	पूर्ण

	buffer_size = माप(काष्ठा pmcraid_passthrough_ioctl_buffer);
	buffer = kदो_स्मृति(buffer_size, GFP_KERNEL);

	अगर (!buffer) अणु
		pmcraid_err("no memory for passthrough buffer\n");
		वापस -ENOMEM;
	पूर्ण

	request_offset =
	    दुरत्व(काष्ठा pmcraid_passthrough_ioctl_buffer, request_buffer);

	request_buffer = arg + request_offset;

	rc = copy_from_user(buffer, arg,
			     माप(काष्ठा pmcraid_passthrough_ioctl_buffer));

	ioasa = arg + दुरत्व(काष्ठा pmcraid_passthrough_ioctl_buffer, ioasa);

	अगर (rc) अणु
		pmcraid_err("ioctl: can't copy passthrough buffer\n");
		rc = -EFAULT;
		जाओ out_मुक्त_buffer;
	पूर्ण

	request_size = le32_to_cpu(buffer->ioarcb.data_transfer_length);

	अगर (buffer->ioarcb.request_flags0 & TRANSFER_सूची_WRITE) अणु
		direction = DMA_TO_DEVICE;
	पूर्ण अन्यथा अणु
		direction = DMA_FROM_DEVICE;
	पूर्ण

	अगर (request_size < 0) अणु
		rc = -EINVAL;
		जाओ out_मुक्त_buffer;
	पूर्ण

	/* check अगर we have any additional command parameters */
	अगर (le16_to_cpu(buffer->ioarcb.add_cmd_param_length)
	     > PMCRAID_ADD_CMD_PARAM_LEN) अणु
		rc = -EINVAL;
		जाओ out_मुक्त_buffer;
	पूर्ण

	cmd = pmcraid_get_मुक्त_cmd(pinstance);

	अगर (!cmd) अणु
		pmcraid_err("free command block is not available\n");
		rc = -ENOMEM;
		जाओ out_मुक्त_buffer;
	पूर्ण

	cmd->scsi_cmd = शून्य;
	ioarcb = &(cmd->ioa_cb->ioarcb);

	/* Copy the user-provided IOARCB stuff field by field */
	ioarcb->resource_handle = buffer->ioarcb.resource_handle;
	ioarcb->data_transfer_length = buffer->ioarcb.data_transfer_length;
	ioarcb->cmd_समयout = buffer->ioarcb.cmd_समयout;
	ioarcb->request_type = buffer->ioarcb.request_type;
	ioarcb->request_flags0 = buffer->ioarcb.request_flags0;
	ioarcb->request_flags1 = buffer->ioarcb.request_flags1;
	स_नकल(ioarcb->cdb, buffer->ioarcb.cdb, PMCRAID_MAX_CDB_LEN);

	अगर (buffer->ioarcb.add_cmd_param_length) अणु
		ioarcb->add_cmd_param_length =
			buffer->ioarcb.add_cmd_param_length;
		ioarcb->add_cmd_param_offset =
			buffer->ioarcb.add_cmd_param_offset;
		स_नकल(ioarcb->add_data.u.add_cmd_params,
			buffer->ioarcb.add_data.u.add_cmd_params,
			le16_to_cpu(buffer->ioarcb.add_cmd_param_length));
	पूर्ण

	/* set hrrq number where the IOA should respond to. Note that all cmds
	 * generated पूर्णांकernally uses hrrq_id 0, exception to this is the cmd
	 * block of scsi_cmd which is re-used (e.g. cancel/पात), which uses
	 * hrrq_id asचिन्हित here in queuecommand
	 */
	ioarcb->hrrq_id = atomic_add_वापस(1, &(pinstance->last_message_id)) %
			  pinstance->num_hrrq;

	अगर (request_size) अणु
		rc = pmcraid_build_passthrough_ioadls(cmd,
						      request_size,
						      direction);
		अगर (rc) अणु
			pmcraid_err("couldn't build passthrough ioadls\n");
			जाओ out_मुक्त_cmd;
		पूर्ण
	पूर्ण

	/* If data is being written पूर्णांकo the device, copy the data from user
	 * buffers
	 */
	अगर (direction == DMA_TO_DEVICE && request_size > 0) अणु
		rc = pmcraid_copy_sglist(cmd->sglist,
					 request_buffer,
					 request_size,
					 direction);
		अगर (rc) अणु
			pmcraid_err("failed to copy user buffer\n");
			जाओ out_मुक्त_sglist;
		पूर्ण
	पूर्ण

	/* passthrough ioctl is a blocking command so, put the user to sleep
	 * until समयout. Note that a समयout value of 0 means, करो समयout.
	 */
	cmd->cmd_करोne = pmcraid_पूर्णांकernal_करोne;
	init_completion(&cmd->रुको_क्रम_completion);
	cmd->completion_req = 1;

	pmcraid_info("command(%d) (CDB[0] = %x) for %x\n",
		     le32_to_cpu(cmd->ioa_cb->ioarcb.response_handle) >> 2,
		     cmd->ioa_cb->ioarcb.cdb[0],
		     le32_to_cpu(cmd->ioa_cb->ioarcb.resource_handle));

	spin_lock_irqsave(pinstance->host->host_lock, lock_flags);
	_pmcraid_fire_command(cmd);
	spin_unlock_irqrestore(pinstance->host->host_lock, lock_flags);

	/* NOTE ! Remove the below line once पात_task is implemented
	 * in firmware. This line disables ioctl command समयout handling logic
	 * similar to IO command समयout handling, making ioctl commands to रुको
	 * until the command completion regardless of समयout value specअगरied in
	 * ioarcb
	 */
	buffer->ioarcb.cmd_समयout = 0;

	/* If command समयout is specअगरied put caller to रुको till that समय,
	 * otherwise it would be blocking रुको. If command माला_लो समयd out, it
	 * will be पातed.
	 */
	अगर (buffer->ioarcb.cmd_समयout == 0) अणु
		रुको_क्रम_completion(&cmd->रुको_क्रम_completion);
	पूर्ण अन्यथा अगर (!रुको_क्रम_completion_समयout(
			&cmd->रुको_क्रम_completion,
			msecs_to_jअगरfies(le16_to_cpu(buffer->ioarcb.cmd_समयout) * 1000))) अणु

		pmcraid_info("aborting cmd %d (CDB[0] = %x) due to timeout\n",
			le32_to_cpu(cmd->ioa_cb->ioarcb.response_handle) >> 2,
			cmd->ioa_cb->ioarcb.cdb[0]);

		spin_lock_irqsave(pinstance->host->host_lock, lock_flags);
		cancel_cmd = pmcraid_पात_cmd(cmd);
		spin_unlock_irqrestore(pinstance->host->host_lock, lock_flags);

		अगर (cancel_cmd) अणु
			रुको_क्रम_completion(&cancel_cmd->रुको_क्रम_completion);
			ioasc = le32_to_cpu(cancel_cmd->ioa_cb->ioasa.ioasc);
			pmcraid_वापस_cmd(cancel_cmd);

			/* अगर पात task couldn't find the command i.e it got
			 * completed prior to पातing, वापस good completion.
			 * अगर command got पातed successfully or there was IOA
			 * reset due to पात task itself getting समयकरोut then
			 * वापस -ETIMEDOUT
			 */
			अगर (ioasc == PMCRAID_IOASC_IOA_WAS_RESET ||
			    PMCRAID_IOASC_SENSE_KEY(ioasc) == 0x00) अणु
				अगर (ioasc != PMCRAID_IOASC_GC_IOARCB_NOTFOUND)
					rc = -ETIMEDOUT;
				जाओ out_handle_response;
			पूर्ण
		पूर्ण

		/* no command block क्रम पात task or पात task failed to पात
		 * the IOARCB, then रुको क्रम 150 more seconds and initiate reset
		 * sequence after समयout
		 */
		अगर (!रुको_क्रम_completion_समयout(
			&cmd->रुको_क्रम_completion,
			msecs_to_jअगरfies(150 * 1000))) अणु
			pmcraid_reset_bringup(cmd->drv_inst);
			rc = -ETIMEDOUT;
		पूर्ण
	पूर्ण

out_handle_response:
	/* copy entire IOASA buffer and वापस IOCTL success.
	 * If copying IOASA to user-buffer fails, वापस
	 * EFAULT
	 */
	अगर (copy_to_user(ioasa, &cmd->ioa_cb->ioasa,
		माप(काष्ठा pmcraid_ioasa))) अणु
		pmcraid_err("failed to copy ioasa buffer to user\n");
		rc = -EFAULT;
	पूर्ण

	/* If the data transfer was from device, copy the data onto user
	 * buffers
	 */
	अन्यथा अगर (direction == DMA_FROM_DEVICE && request_size > 0) अणु
		rc = pmcraid_copy_sglist(cmd->sglist,
					 request_buffer,
					 request_size,
					 direction);
		अगर (rc) अणु
			pmcraid_err("failed to copy user buffer\n");
			rc = -EFAULT;
		पूर्ण
	पूर्ण

out_मुक्त_sglist:
	pmcraid_release_passthrough_ioadls(cmd, request_size, direction);

out_मुक्त_cmd:
	pmcraid_वापस_cmd(cmd);

out_मुक्त_buffer:
	kमुक्त(buffer);

	वापस rc;
पूर्ण




/**
 * pmcraid_ioctl_driver - ioctl handler क्रम commands handled by driver itself
 *
 * @pinstance: poपूर्णांकer to adapter instance काष्ठाure
 * @cmd: ioctl command passed in
 * @buflen: length of user_buffer
 * @user_buffer: user buffer poपूर्णांकer
 *
 * Return Value
 *   0 in हाल of success, otherwise appropriate error code
 */
अटल दीर्घ pmcraid_ioctl_driver(
	काष्ठा pmcraid_instance *pinstance,
	अचिन्हित पूर्णांक cmd,
	अचिन्हित पूर्णांक buflen,
	व्योम __user *user_buffer
)
अणु
	पूर्णांक rc = -ENOSYS;

	चयन (cmd) अणु
	हाल PMCRAID_IOCTL_RESET_ADAPTER:
		pmcraid_reset_bringup(pinstance);
		rc = 0;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * pmcraid_check_ioctl_buffer - check क्रम proper access to user buffer
 *
 * @cmd: ioctl command
 * @arg: user buffer
 * @hdr: poपूर्णांकer to kernel memory क्रम pmcraid_ioctl_header
 *
 * Return Value
 *	negetive error code अगर there are access issues, otherwise zero.
 *	Upon success, वापसs ioctl header copied out of user buffer.
 */

अटल पूर्णांक pmcraid_check_ioctl_buffer(
	पूर्णांक cmd,
	व्योम __user *arg,
	काष्ठा pmcraid_ioctl_header *hdr
)
अणु
	पूर्णांक rc;

	अगर (copy_from_user(hdr, arg, माप(काष्ठा pmcraid_ioctl_header))) अणु
		pmcraid_err("couldn't copy ioctl header from user buffer\n");
		वापस -EFAULT;
	पूर्ण

	/* check क्रम valid driver signature */
	rc = स_भेद(hdr->signature,
		    PMCRAID_IOCTL_SIGNATURE,
		    माप(hdr->signature));
	अगर (rc) अणु
		pmcraid_err("signature verification failed\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *  pmcraid_ioctl - अक्षर node ioctl entry poपूर्णांक
 */
अटल दीर्घ pmcraid_chr_ioctl(
	काष्ठा file *filep,
	अचिन्हित पूर्णांक cmd,
	अचिन्हित दीर्घ arg
)
अणु
	काष्ठा pmcraid_instance *pinstance = शून्य;
	काष्ठा pmcraid_ioctl_header *hdr = शून्य;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक retval = -ENOTTY;

	hdr = kदो_स्मृति(माप(काष्ठा pmcraid_ioctl_header), GFP_KERNEL);

	अगर (!hdr) अणु
		pmcraid_err("failed to allocate memory for ioctl header\n");
		वापस -ENOMEM;
	पूर्ण

	retval = pmcraid_check_ioctl_buffer(cmd, argp, hdr);

	अगर (retval) अणु
		pmcraid_info("chr_ioctl: header check failed\n");
		kमुक्त(hdr);
		वापस retval;
	पूर्ण

	pinstance = filep->निजी_data;

	अगर (!pinstance) अणु
		pmcraid_info("adapter instance is not found\n");
		kमुक्त(hdr);
		वापस -ENOTTY;
	पूर्ण

	चयन (_IOC_TYPE(cmd)) अणु

	हाल PMCRAID_PASSTHROUGH_IOCTL:
		/* If ioctl code is to करोwnload microcode, we need to block
		 * mid-layer requests.
		 */
		अगर (cmd == PMCRAID_IOCTL_DOWNLOAD_MICROCODE)
			scsi_block_requests(pinstance->host);

		retval = pmcraid_ioctl_passthrough(pinstance, cmd,
						   hdr->buffer_length, argp);

		अगर (cmd == PMCRAID_IOCTL_DOWNLOAD_MICROCODE)
			scsi_unblock_requests(pinstance->host);
		अवरोध;

	हाल PMCRAID_DRIVER_IOCTL:
		arg += माप(काष्ठा pmcraid_ioctl_header);
		retval = pmcraid_ioctl_driver(pinstance, cmd,
					      hdr->buffer_length, argp);
		अवरोध;

	शेष:
		retval = -ENOTTY;
		अवरोध;
	पूर्ण

	kमुक्त(hdr);

	वापस retval;
पूर्ण

/*
 * File operations काष्ठाure क्रम management पूर्णांकerface
 */
अटल स्थिर काष्ठा file_operations pmcraid_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = pmcraid_chr_खोलो,
	.fasync = pmcraid_chr_fasync,
	.unlocked_ioctl = pmcraid_chr_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.llseek = noop_llseek,
पूर्ण;




/**
 * pmcraid_show_log_level - Display adapter's error logging level
 * @dev: class device काष्ठा
 * @attr: unused
 * @buf: buffer
 *
 * Return value:
 *  number of bytes prपूर्णांकed to buffer
 */
अटल sमाप_प्रकार pmcraid_show_log_level(
	काष्ठा device *dev,
	काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा pmcraid_instance *pinstance =
		(काष्ठा pmcraid_instance *)shost->hostdata;
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", pinstance->current_log_level);
पूर्ण

/**
 * pmcraid_store_log_level - Change the adapter's error logging level
 * @dev: class device काष्ठा
 * @attr: unused
 * @buf: buffer
 * @count: not used
 *
 * Return value:
 *  number of bytes prपूर्णांकed to buffer
 */
अटल sमाप_प्रकार pmcraid_store_log_level(
	काष्ठा device *dev,
	काष्ठा device_attribute *attr,
	स्थिर अक्षर *buf,
	माप_प्रकार count
)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा pmcraid_instance *pinstance;
	u8 val;

	अगर (kstrtou8(buf, 10, &val))
		वापस -EINVAL;
	/* log-level should be from 0 to 2 */
	अगर (val > 2)
		वापस -EINVAL;

	shost = class_to_shost(dev);
	pinstance = (काष्ठा pmcraid_instance *)shost->hostdata;
	pinstance->current_log_level = val;

	वापस म_माप(buf);
पूर्ण

अटल काष्ठा device_attribute pmcraid_log_level_attr = अणु
	.attr = अणु
		 .name = "log_level",
		 .mode = S_IRUGO | S_IWUSR,
		 पूर्ण,
	.show = pmcraid_show_log_level,
	.store = pmcraid_store_log_level,
पूर्ण;

/**
 * pmcraid_show_drv_version - Display driver version
 * @dev: class device काष्ठा
 * @attr: unused
 * @buf: buffer
 *
 * Return value:
 *  number of bytes prपूर्णांकed to buffer
 */
अटल sमाप_प्रकार pmcraid_show_drv_version(
	काष्ठा device *dev,
	काष्ठा device_attribute *attr,
	अक्षर *buf
)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "version: %s\n",
			PMCRAID_DRIVER_VERSION);
पूर्ण

अटल काष्ठा device_attribute pmcraid_driver_version_attr = अणु
	.attr = अणु
		 .name = "drv_version",
		 .mode = S_IRUGO,
		 पूर्ण,
	.show = pmcraid_show_drv_version,
पूर्ण;

/**
 * pmcraid_show_adapter_id - Display driver asचिन्हित adapter id
 * @dev: class device काष्ठा
 * @attr: unused
 * @buf: buffer
 *
 * Return value:
 *  number of bytes prपूर्णांकed to buffer
 */
अटल sमाप_प्रकार pmcraid_show_adapter_id(
	काष्ठा device *dev,
	काष्ठा device_attribute *attr,
	अक्षर *buf
)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा pmcraid_instance *pinstance =
		(काष्ठा pmcraid_instance *)shost->hostdata;
	u32 adapter_id = (pinstance->pdev->bus->number << 8) |
		pinstance->pdev->devfn;
	u32 aen_group = pmcraid_event_family.id;

	वापस snम_लिखो(buf, PAGE_SIZE,
			"adapter id: %d\nminor: %d\naen group: %d\n",
			adapter_id, MINOR(pinstance->cdev.dev), aen_group);
पूर्ण

अटल काष्ठा device_attribute pmcraid_adapter_id_attr = अणु
	.attr = अणु
		 .name = "adapter_id",
		 .mode = S_IRUGO,
		 पूर्ण,
	.show = pmcraid_show_adapter_id,
पूर्ण;

अटल काष्ठा device_attribute *pmcraid_host_attrs[] = अणु
	&pmcraid_log_level_attr,
	&pmcraid_driver_version_attr,
	&pmcraid_adapter_id_attr,
	शून्य,
पूर्ण;


/* host ढाँचा काष्ठाure क्रम pmcraid driver */
अटल काष्ठा scsi_host_ढाँचा pmcraid_host_ढाँचा = अणु
	.module = THIS_MODULE,
	.name = PMCRAID_DRIVER_NAME,
	.queuecommand = pmcraid_queuecommand,
	.eh_पात_handler = pmcraid_eh_पात_handler,
	.eh_bus_reset_handler = pmcraid_eh_bus_reset_handler,
	.eh_target_reset_handler = pmcraid_eh_target_reset_handler,
	.eh_device_reset_handler = pmcraid_eh_device_reset_handler,
	.eh_host_reset_handler = pmcraid_eh_host_reset_handler,

	.slave_alloc = pmcraid_slave_alloc,
	.slave_configure = pmcraid_slave_configure,
	.slave_destroy = pmcraid_slave_destroy,
	.change_queue_depth = pmcraid_change_queue_depth,
	.can_queue = PMCRAID_MAX_IO_CMD,
	.this_id = -1,
	.sg_tablesize = PMCRAID_MAX_IOADLS,
	.max_sectors = PMCRAID_IOA_MAX_SECTORS,
	.no_ग_लिखो_same = 1,
	.cmd_per_lun = PMCRAID_MAX_CMD_PER_LUN,
	.shost_attrs = pmcraid_host_attrs,
	.proc_name = PMCRAID_DRIVER_NAME,
पूर्ण;

/*
 * pmcraid_isr_msix - implements MSI-X पूर्णांकerrupt handling routine
 * @irq: पूर्णांकerrupt vector number
 * @dev_id: poपूर्णांकer hrrq_vector
 *
 * Return Value
 *	 IRQ_HANDLED अगर पूर्णांकerrupt is handled or IRQ_NONE अगर ignored
 */

अटल irqवापस_t pmcraid_isr_msix(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pmcraid_isr_param *hrrq_vector;
	काष्ठा pmcraid_instance *pinstance;
	अचिन्हित दीर्घ lock_flags;
	u32 पूर्णांकrs_val;
	पूर्णांक hrrq_id;

	hrrq_vector = (काष्ठा pmcraid_isr_param *)dev_id;
	hrrq_id = hrrq_vector->hrrq_id;
	pinstance = hrrq_vector->drv_inst;

	अगर (!hrrq_id) अणु
		/* Read the पूर्णांकerrupt */
		पूर्णांकrs_val = pmcraid_पढ़ो_पूर्णांकerrupts(pinstance);
		अगर (पूर्णांकrs_val &&
			((ioपढ़ो32(pinstance->पूर्णांक_regs.host_ioa_पूर्णांकerrupt_reg)
			& DOORBELL_INTR_MSIX_CLR) == 0)) अणु
			/* Any error पूर्णांकerrupts including unit_check,
			 * initiate IOA reset.In हाल of unit check indicate
			 * to reset_sequence that IOA unit checked and prepare
			 * क्रम a dump during reset sequence
			 */
			अगर (पूर्णांकrs_val & PMCRAID_ERROR_INTERRUPTS) अणु
				अगर (पूर्णांकrs_val & INTRS_IOA_UNIT_CHECK)
					pinstance->ioa_unit_check = 1;

				pmcraid_err("ISR: error पूर्णांकerrupts: %x \
					initiating reset\न", पूर्णांकrs_val);
				spin_lock_irqsave(pinstance->host->host_lock,
					lock_flags);
				pmcraid_initiate_reset(pinstance);
				spin_unlock_irqrestore(
					pinstance->host->host_lock,
					lock_flags);
			पूर्ण
			/* If पूर्णांकerrupt was as part of the ioa initialization,
			 * clear it. Delete the समयr and wakeup the
			 * reset engine to proceed with reset sequence
			 */
			अगर (पूर्णांकrs_val & INTRS_TRANSITION_TO_OPERATIONAL)
				pmcraid_clr_trans_op(pinstance);

			/* Clear the पूर्णांकerrupt रेजिस्टर by writing
			 * to host to ioa करोorbell. Once करोne
			 * FW will clear the पूर्णांकerrupt.
			 */
			ioग_लिखो32(DOORBELL_INTR_MSIX_CLR,
				pinstance->पूर्णांक_regs.host_ioa_पूर्णांकerrupt_reg);
			ioपढ़ो32(pinstance->पूर्णांक_regs.host_ioa_पूर्णांकerrupt_reg);


		पूर्ण
	पूर्ण

	tasklet_schedule(&(pinstance->isr_tasklet[hrrq_id]));

	वापस IRQ_HANDLED;
पूर्ण

/**
 * pmcraid_isr  - implements legacy पूर्णांकerrupt handling routine
 *
 * @irq: पूर्णांकerrupt vector number
 * @dev_id: poपूर्णांकer hrrq_vector
 *
 * Return Value
 *	 IRQ_HANDLED अगर पूर्णांकerrupt is handled or IRQ_NONE अगर ignored
 */
अटल irqवापस_t pmcraid_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pmcraid_isr_param *hrrq_vector;
	काष्ठा pmcraid_instance *pinstance;
	u32 पूर्णांकrs;
	अचिन्हित दीर्घ lock_flags;
	पूर्णांक hrrq_id = 0;

	/* In हाल of legacy पूर्णांकerrupt mode where पूर्णांकerrupts are shared across
	 * isrs, it may be possible that the current पूर्णांकerrupt is not from IOA
	 */
	अगर (!dev_id) अणु
		prपूर्णांकk(KERN_INFO "%s(): NULL host pointer\n", __func__);
		वापस IRQ_NONE;
	पूर्ण
	hrrq_vector = (काष्ठा pmcraid_isr_param *)dev_id;
	pinstance = hrrq_vector->drv_inst;

	पूर्णांकrs = pmcraid_पढ़ो_पूर्णांकerrupts(pinstance);

	अगर (unlikely((पूर्णांकrs & PMCRAID_PCI_INTERRUPTS) == 0))
		वापस IRQ_NONE;

	/* Any error पूर्णांकerrupts including unit_check, initiate IOA reset.
	 * In हाल of unit check indicate to reset_sequence that IOA unit
	 * checked and prepare क्रम a dump during reset sequence
	 */
	अगर (पूर्णांकrs & PMCRAID_ERROR_INTERRUPTS) अणु

		अगर (पूर्णांकrs & INTRS_IOA_UNIT_CHECK)
			pinstance->ioa_unit_check = 1;

		ioग_लिखो32(पूर्णांकrs,
			  pinstance->पूर्णांक_regs.ioa_host_पूर्णांकerrupt_clr_reg);
		pmcraid_err("ISR: error interrupts: %x initiating reset\n",
			    पूर्णांकrs);
		पूर्णांकrs = ioपढ़ो32(
				pinstance->पूर्णांक_regs.ioa_host_पूर्णांकerrupt_clr_reg);
		spin_lock_irqsave(pinstance->host->host_lock, lock_flags);
		pmcraid_initiate_reset(pinstance);
		spin_unlock_irqrestore(pinstance->host->host_lock, lock_flags);
	पूर्ण अन्यथा अणु
		/* If पूर्णांकerrupt was as part of the ioa initialization,
		 * clear. Delete the समयr and wakeup the
		 * reset engine to proceed with reset sequence
		 */
		अगर (पूर्णांकrs & INTRS_TRANSITION_TO_OPERATIONAL) अणु
			pmcraid_clr_trans_op(pinstance);
		पूर्ण अन्यथा अणु
			ioग_लिखो32(पूर्णांकrs,
				pinstance->पूर्णांक_regs.ioa_host_पूर्णांकerrupt_clr_reg);
			ioपढ़ो32(
				pinstance->पूर्णांक_regs.ioa_host_पूर्णांकerrupt_clr_reg);

			tasklet_schedule(
					&(pinstance->isr_tasklet[hrrq_id]));
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण


/**
 * pmcraid_worker_function -  worker thपढ़ो function
 *
 * @workp: poपूर्णांकer to काष्ठा work queue
 *
 * Return Value
 *	 None
 */

अटल व्योम pmcraid_worker_function(काष्ठा work_काष्ठा *workp)
अणु
	काष्ठा pmcraid_instance *pinstance;
	काष्ठा pmcraid_resource_entry *res;
	काष्ठा pmcraid_resource_entry *temp;
	काष्ठा scsi_device *sdev;
	अचिन्हित दीर्घ lock_flags;
	अचिन्हित दीर्घ host_lock_flags;
	u16 fw_version;
	u8 bus, target, lun;

	pinstance = container_of(workp, काष्ठा pmcraid_instance, worker_q);
	/* add resources only after host is added पूर्णांकo प्रणाली */
	अगर (!atomic_पढ़ो(&pinstance->expose_resources))
		वापस;

	fw_version = be16_to_cpu(pinstance->inq_data->fw_version);

	spin_lock_irqsave(&pinstance->resource_lock, lock_flags);
	list_क्रम_each_entry_safe(res, temp, &pinstance->used_res_q, queue) अणु

		अगर (res->change_detected == RES_CHANGE_DEL && res->scsi_dev) अणु
			sdev = res->scsi_dev;

			/* host_lock must be held beक्रमe calling
			 * scsi_device_get
			 */
			spin_lock_irqsave(pinstance->host->host_lock,
					  host_lock_flags);
			अगर (!scsi_device_get(sdev)) अणु
				spin_unlock_irqrestore(
						pinstance->host->host_lock,
						host_lock_flags);
				pmcraid_info("deleting %x from midlayer\n",
					     res->cfg_entry.resource_address);
				list_move_tail(&res->queue,
						&pinstance->मुक्त_res_q);
				spin_unlock_irqrestore(
					&pinstance->resource_lock,
					lock_flags);
				scsi_हटाओ_device(sdev);
				scsi_device_put(sdev);
				spin_lock_irqsave(&pinstance->resource_lock,
						   lock_flags);
				res->change_detected = 0;
			पूर्ण अन्यथा अणु
				spin_unlock_irqrestore(
						pinstance->host->host_lock,
						host_lock_flags);
			पूर्ण
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(res, &pinstance->used_res_q, queue) अणु

		अगर (res->change_detected == RES_CHANGE_ADD) अणु

			अगर (!pmcraid_expose_resource(fw_version,
						     &res->cfg_entry))
				जारी;

			अगर (RES_IS_VSET(res->cfg_entry)) अणु
				bus = PMCRAID_VSET_BUS_ID;
				अगर (fw_version <= PMCRAID_FW_VERSION_1)
					target = res->cfg_entry.unique_flags1;
				अन्यथा
					target = le16_to_cpu(res->cfg_entry.array_id) & 0xFF;
				lun = PMCRAID_VSET_LUN_ID;
			पूर्ण अन्यथा अणु
				bus = PMCRAID_PHYS_BUS_ID;
				target =
				     RES_TARGET(
					res->cfg_entry.resource_address);
				lun = RES_LUN(res->cfg_entry.resource_address);
			पूर्ण

			res->change_detected = 0;
			spin_unlock_irqrestore(&pinstance->resource_lock,
						lock_flags);
			scsi_add_device(pinstance->host, bus, target, lun);
			spin_lock_irqsave(&pinstance->resource_lock,
					   lock_flags);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&pinstance->resource_lock, lock_flags);
पूर्ण

/**
 * pmcraid_tasklet_function - Tasklet function
 *
 * @instance: poपूर्णांकer to msix param काष्ठाure
 *
 * Return Value
 *	None
 */
अटल व्योम pmcraid_tasklet_function(अचिन्हित दीर्घ instance)
अणु
	काष्ठा pmcraid_isr_param *hrrq_vector;
	काष्ठा pmcraid_instance *pinstance;
	अचिन्हित दीर्घ hrrq_lock_flags;
	अचिन्हित दीर्घ pending_lock_flags;
	अचिन्हित दीर्घ host_lock_flags;
	spinlock_t *lockp; /* hrrq buffer lock */
	पूर्णांक id;
	u32 resp;

	hrrq_vector = (काष्ठा pmcraid_isr_param *)instance;
	pinstance = hrrq_vector->drv_inst;
	id = hrrq_vector->hrrq_id;
	lockp = &(pinstance->hrrq_lock[id]);

	/* loop through each of the commands responded by IOA. Each HRRQ buf is
	 * रक्षित by its own lock. Traversals must be करोne within this lock
	 * as there may be multiple tasklets running on multiple CPUs. Note
	 * that the lock is held just क्रम picking up the response handle and
	 * manipulating hrrq_curr/toggle_bit values.
	 */
	spin_lock_irqsave(lockp, hrrq_lock_flags);

	resp = le32_to_cpu(*(pinstance->hrrq_curr[id]));

	जबतक ((resp & HRRQ_TOGGLE_BIT) ==
		pinstance->host_toggle_bit[id]) अणु

		पूर्णांक cmd_index = resp >> 2;
		काष्ठा pmcraid_cmd *cmd = शून्य;

		अगर (pinstance->hrrq_curr[id] < pinstance->hrrq_end[id]) अणु
			pinstance->hrrq_curr[id]++;
		पूर्ण अन्यथा अणु
			pinstance->hrrq_curr[id] = pinstance->hrrq_start[id];
			pinstance->host_toggle_bit[id] ^= 1u;
		पूर्ण

		अगर (cmd_index >= PMCRAID_MAX_CMD) अणु
			/* In हाल of invalid response handle, log message */
			pmcraid_err("Invalid response handle %d\n", cmd_index);
			resp = le32_to_cpu(*(pinstance->hrrq_curr[id]));
			जारी;
		पूर्ण

		cmd = pinstance->cmd_list[cmd_index];
		spin_unlock_irqrestore(lockp, hrrq_lock_flags);

		spin_lock_irqsave(&pinstance->pending_pool_lock,
				   pending_lock_flags);
		list_del(&cmd->मुक्त_list);
		spin_unlock_irqrestore(&pinstance->pending_pool_lock,
					pending_lock_flags);
		del_समयr(&cmd->समयr);
		atomic_dec(&pinstance->outstanding_cmds);

		अगर (cmd->cmd_करोne == pmcraid_ioa_reset) अणु
			spin_lock_irqsave(pinstance->host->host_lock,
					  host_lock_flags);
			cmd->cmd_करोne(cmd);
			spin_unlock_irqrestore(pinstance->host->host_lock,
					       host_lock_flags);
		पूर्ण अन्यथा अगर (cmd->cmd_करोne != शून्य) अणु
			cmd->cmd_करोne(cmd);
		पूर्ण
		/* loop over until we are करोne with all responses */
		spin_lock_irqsave(lockp, hrrq_lock_flags);
		resp = le32_to_cpu(*(pinstance->hrrq_curr[id]));
	पूर्ण

	spin_unlock_irqrestore(lockp, hrrq_lock_flags);
पूर्ण

/**
 * pmcraid_unरेजिस्टर_पूर्णांकerrupt_handler - de-रेजिस्टर पूर्णांकerrupts handlers
 * @pinstance: poपूर्णांकer to adapter instance काष्ठाure
 *
 * This routine un-रेजिस्टरs रेजिस्टरed पूर्णांकerrupt handler and
 * also मुक्तs irqs/vectors.
 *
 * Retun Value
 *	None
 */
अटल
व्योम pmcraid_unरेजिस्टर_पूर्णांकerrupt_handler(काष्ठा pmcraid_instance *pinstance)
अणु
	काष्ठा pci_dev *pdev = pinstance->pdev;
	पूर्णांक i;

	क्रम (i = 0; i < pinstance->num_hrrq; i++)
		मुक्त_irq(pci_irq_vector(pdev, i), &pinstance->hrrq_vector[i]);

	pinstance->पूर्णांकerrupt_mode = 0;
	pci_मुक्त_irq_vectors(pdev);
पूर्ण

/**
 * pmcraid_रेजिस्टर_पूर्णांकerrupt_handler - रेजिस्टरs पूर्णांकerrupt handler
 * @pinstance: poपूर्णांकer to per-adapter instance काष्ठाure
 *
 * Return Value
 *	0 on success, non-zero error code otherwise.
 */
अटल पूर्णांक
pmcraid_रेजिस्टर_पूर्णांकerrupt_handler(काष्ठा pmcraid_instance *pinstance)
अणु
	काष्ठा pci_dev *pdev = pinstance->pdev;
	अचिन्हित पूर्णांक irq_flag = PCI_IRQ_LEGACY, flag;
	पूर्णांक num_hrrq, rc, i;
	irq_handler_t isr;

	अगर (pmcraid_enable_msix)
		irq_flag |= PCI_IRQ_MSIX;

	num_hrrq = pci_alloc_irq_vectors(pdev, 1, PMCRAID_NUM_MSIX_VECTORS,
			irq_flag);
	अगर (num_hrrq < 0)
		वापस num_hrrq;

	अगर (pdev->msix_enabled) अणु
		flag = 0;
		isr = pmcraid_isr_msix;
	पूर्ण अन्यथा अणु
		flag = IRQF_SHARED;
		isr = pmcraid_isr;
	पूर्ण

	क्रम (i = 0; i < num_hrrq; i++) अणु
		काष्ठा pmcraid_isr_param *vec = &pinstance->hrrq_vector[i];

		vec->hrrq_id = i;
		vec->drv_inst = pinstance;
		rc = request_irq(pci_irq_vector(pdev, i), isr, flag,
				PMCRAID_DRIVER_NAME, vec);
		अगर (rc)
			जाओ out_unwind;
	पूर्ण

	pinstance->num_hrrq = num_hrrq;
	अगर (pdev->msix_enabled) अणु
		pinstance->पूर्णांकerrupt_mode = 1;
		ioग_लिखो32(DOORBELL_INTR_MODE_MSIX,
			  pinstance->पूर्णांक_regs.host_ioa_पूर्णांकerrupt_reg);
		ioपढ़ो32(pinstance->पूर्णांक_regs.host_ioa_पूर्णांकerrupt_reg);
	पूर्ण

	वापस 0;

out_unwind:
	जबतक (--i > 0)
		मुक्त_irq(pci_irq_vector(pdev, i), &pinstance->hrrq_vector[i]);
	pci_मुक्त_irq_vectors(pdev);
	वापस rc;
पूर्ण

/**
 * pmcraid_release_cmd_blocks - release buufers allocated क्रम command blocks
 * @pinstance: per adapter instance काष्ठाure poपूर्णांकer
 * @max_index: number of buffer blocks to release
 *
 * Return Value
 *  None
 */
अटल व्योम
pmcraid_release_cmd_blocks(काष्ठा pmcraid_instance *pinstance, पूर्णांक max_index)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < max_index; i++) अणु
		kmem_cache_मुक्त(pinstance->cmd_cachep, pinstance->cmd_list[i]);
		pinstance->cmd_list[i] = शून्य;
	पूर्ण
	kmem_cache_destroy(pinstance->cmd_cachep);
	pinstance->cmd_cachep = शून्य;
पूर्ण

/**
 * pmcraid_release_control_blocks - releases buffers alloced क्रम control blocks
 * @pinstance: poपूर्णांकer to per adapter instance काष्ठाure
 * @max_index: number of buffers (from 0 onwards) to release
 *
 * This function assumes that the command blocks क्रम which control blocks are
 * linked are not released.
 *
 * Return Value
 *	 None
 */
अटल व्योम
pmcraid_release_control_blocks(
	काष्ठा pmcraid_instance *pinstance,
	पूर्णांक max_index
)
अणु
	पूर्णांक i;

	अगर (pinstance->control_pool == शून्य)
		वापस;

	क्रम (i = 0; i < max_index; i++) अणु
		dma_pool_मुक्त(pinstance->control_pool,
			      pinstance->cmd_list[i]->ioa_cb,
			      pinstance->cmd_list[i]->ioa_cb_bus_addr);
		pinstance->cmd_list[i]->ioa_cb = शून्य;
		pinstance->cmd_list[i]->ioa_cb_bus_addr = 0;
	पूर्ण
	dma_pool_destroy(pinstance->control_pool);
	pinstance->control_pool = शून्य;
पूर्ण

/**
 * pmcraid_allocate_cmd_blocks - allocate memory क्रम cmd block काष्ठाures
 * @pinstance: poपूर्णांकer to per adapter instance काष्ठाure
 *
 * Allocates memory क्रम command blocks using kernel slab allocator.
 *
 * Return Value
 *	0 in हाल of success; -ENOMEM in हाल of failure
 */
अटल पूर्णांक pmcraid_allocate_cmd_blocks(काष्ठा pmcraid_instance *pinstance)
अणु
	पूर्णांक i;

	प्र_लिखो(pinstance->cmd_pool_name, "pmcraid_cmd_pool_%d",
		pinstance->host->unique_id);


	pinstance->cmd_cachep = kmem_cache_create(
					pinstance->cmd_pool_name,
					माप(काष्ठा pmcraid_cmd), 0,
					SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!pinstance->cmd_cachep)
		वापस -ENOMEM;

	क्रम (i = 0; i < PMCRAID_MAX_CMD; i++) अणु
		pinstance->cmd_list[i] =
			kmem_cache_alloc(pinstance->cmd_cachep, GFP_KERNEL);
		अगर (!pinstance->cmd_list[i]) अणु
			pmcraid_release_cmd_blocks(pinstance, i);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * pmcraid_allocate_control_blocks - allocates memory control blocks
 * @pinstance : poपूर्णांकer to per adapter instance काष्ठाure
 *
 * This function allocates PCI memory क्रम DMAable buffers like IOARCB, IOADLs
 * and IOASAs. This is called after command blocks are alपढ़ोy allocated.
 *
 * Return Value
 *  0 in हाल it can allocate all control blocks, otherwise -ENOMEM
 */
अटल पूर्णांक pmcraid_allocate_control_blocks(काष्ठा pmcraid_instance *pinstance)
अणु
	पूर्णांक i;

	प्र_लिखो(pinstance->ctl_pool_name, "pmcraid_control_pool_%d",
		pinstance->host->unique_id);

	pinstance->control_pool =
		dma_pool_create(pinstance->ctl_pool_name,
				&pinstance->pdev->dev,
				माप(काष्ठा pmcraid_control_block),
				PMCRAID_IOARCB_ALIGNMENT, 0);

	अगर (!pinstance->control_pool)
		वापस -ENOMEM;

	क्रम (i = 0; i < PMCRAID_MAX_CMD; i++) अणु
		pinstance->cmd_list[i]->ioa_cb =
			dma_pool_zalloc(
				pinstance->control_pool,
				GFP_KERNEL,
				&(pinstance->cmd_list[i]->ioa_cb_bus_addr));

		अगर (!pinstance->cmd_list[i]->ioa_cb) अणु
			pmcraid_release_control_blocks(pinstance, i);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * pmcraid_release_host_rrqs - release memory allocated क्रम hrrq buffer(s)
 * @pinstance: poपूर्णांकer to per adapter instance काष्ठाure
 * @maxindex: size of hrrq buffer poपूर्णांकer array
 *
 * Return Value
 *	None
 */
अटल व्योम
pmcraid_release_host_rrqs(काष्ठा pmcraid_instance *pinstance, पूर्णांक maxindex)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < maxindex; i++) अणु
		dma_मुक्त_coherent(&pinstance->pdev->dev,
				    HRRQ_ENTRY_SIZE * PMCRAID_MAX_CMD,
				    pinstance->hrrq_start[i],
				    pinstance->hrrq_start_bus_addr[i]);

		/* reset poपूर्णांकers and toggle bit to zeros */
		pinstance->hrrq_start[i] = शून्य;
		pinstance->hrrq_start_bus_addr[i] = 0;
		pinstance->host_toggle_bit[i] = 0;
	पूर्ण
पूर्ण

/**
 * pmcraid_allocate_host_rrqs - Allocate and initialize host RRQ buffers
 * @pinstance: poपूर्णांकer to per adapter instance काष्ठाure
 *
 * Return value
 *	0 hrrq buffers are allocated, -ENOMEM otherwise.
 */
अटल पूर्णांक pmcraid_allocate_host_rrqs(काष्ठा pmcraid_instance *pinstance)
अणु
	पूर्णांक i, buffer_size;

	buffer_size = HRRQ_ENTRY_SIZE * PMCRAID_MAX_CMD;

	क्रम (i = 0; i < pinstance->num_hrrq; i++) अणु
		pinstance->hrrq_start[i] =
			dma_alloc_coherent(&pinstance->pdev->dev, buffer_size,
					   &pinstance->hrrq_start_bus_addr[i],
					   GFP_KERNEL);
		अगर (!pinstance->hrrq_start[i]) अणु
			pmcraid_err("pci_alloc failed for hrrq vector : %d\n",
				    i);
			pmcraid_release_host_rrqs(pinstance, i);
			वापस -ENOMEM;
		पूर्ण

		pinstance->hrrq_curr[i] = pinstance->hrrq_start[i];
		pinstance->hrrq_end[i] =
			pinstance->hrrq_start[i] + PMCRAID_MAX_CMD - 1;
		pinstance->host_toggle_bit[i] = 1;
		spin_lock_init(&pinstance->hrrq_lock[i]);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * pmcraid_release_hcams - release HCAM buffers
 *
 * @pinstance: poपूर्णांकer to per adapter instance काष्ठाure
 *
 * Return value
 *  none
 */
अटल व्योम pmcraid_release_hcams(काष्ठा pmcraid_instance *pinstance)
अणु
	अगर (pinstance->ccn.msg != शून्य) अणु
		dma_मुक्त_coherent(&pinstance->pdev->dev,
				    PMCRAID_AEN_HDR_SIZE +
				    माप(काष्ठा pmcraid_hcam_ccn_ext),
				    pinstance->ccn.msg,
				    pinstance->ccn.baddr);

		pinstance->ccn.msg = शून्य;
		pinstance->ccn.hcam = शून्य;
		pinstance->ccn.baddr = 0;
	पूर्ण

	अगर (pinstance->ldn.msg != शून्य) अणु
		dma_मुक्त_coherent(&pinstance->pdev->dev,
				    PMCRAID_AEN_HDR_SIZE +
				    माप(काष्ठा pmcraid_hcam_ldn),
				    pinstance->ldn.msg,
				    pinstance->ldn.baddr);

		pinstance->ldn.msg = शून्य;
		pinstance->ldn.hcam = शून्य;
		pinstance->ldn.baddr = 0;
	पूर्ण
पूर्ण

/**
 * pmcraid_allocate_hcams - allocates HCAM buffers
 * @pinstance : poपूर्णांकer to per adapter instance काष्ठाure
 *
 * Return Value:
 *   0 in हाल of successful allocation, non-zero otherwise
 */
अटल पूर्णांक pmcraid_allocate_hcams(काष्ठा pmcraid_instance *pinstance)
अणु
	pinstance->ccn.msg = dma_alloc_coherent(&pinstance->pdev->dev,
					PMCRAID_AEN_HDR_SIZE +
					माप(काष्ठा pmcraid_hcam_ccn_ext),
					&pinstance->ccn.baddr, GFP_KERNEL);

	pinstance->ldn.msg = dma_alloc_coherent(&pinstance->pdev->dev,
					PMCRAID_AEN_HDR_SIZE +
					माप(काष्ठा pmcraid_hcam_ldn),
					&pinstance->ldn.baddr, GFP_KERNEL);

	अगर (pinstance->ldn.msg == शून्य || pinstance->ccn.msg == शून्य) अणु
		pmcraid_release_hcams(pinstance);
	पूर्ण अन्यथा अणु
		pinstance->ccn.hcam =
			(व्योम *)pinstance->ccn.msg + PMCRAID_AEN_HDR_SIZE;
		pinstance->ldn.hcam =
			(व्योम *)pinstance->ldn.msg + PMCRAID_AEN_HDR_SIZE;

		atomic_set(&pinstance->ccn.ignore, 0);
		atomic_set(&pinstance->ldn.ignore, 0);
	पूर्ण

	वापस (pinstance->ldn.msg == शून्य) ? -ENOMEM : 0;
पूर्ण

/**
 * pmcraid_release_config_buffers - release config.table buffers
 * @pinstance: poपूर्णांकer to per adapter instance काष्ठाure
 *
 * Return Value
 *	 none
 */
अटल व्योम pmcraid_release_config_buffers(काष्ठा pmcraid_instance *pinstance)
अणु
	अगर (pinstance->cfg_table != शून्य &&
	    pinstance->cfg_table_bus_addr != 0) अणु
		dma_मुक्त_coherent(&pinstance->pdev->dev,
				    माप(काष्ठा pmcraid_config_table),
				    pinstance->cfg_table,
				    pinstance->cfg_table_bus_addr);
		pinstance->cfg_table = शून्य;
		pinstance->cfg_table_bus_addr = 0;
	पूर्ण

	अगर (pinstance->res_entries != शून्य) अणु
		पूर्णांक i;

		क्रम (i = 0; i < PMCRAID_MAX_RESOURCES; i++)
			list_del(&pinstance->res_entries[i].queue);
		kमुक्त(pinstance->res_entries);
		pinstance->res_entries = शून्य;
	पूर्ण

	pmcraid_release_hcams(pinstance);
पूर्ण

/**
 * pmcraid_allocate_config_buffers - allocates DMAable memory क्रम config table
 * @pinstance : poपूर्णांकer to per adapter instance काष्ठाure
 *
 * Return Value
 *	0 क्रम successful allocation, -ENOMEM क्रम any failure
 */
अटल पूर्णांक pmcraid_allocate_config_buffers(काष्ठा pmcraid_instance *pinstance)
अणु
	पूर्णांक i;

	pinstance->res_entries =
			kसुस्मृति(PMCRAID_MAX_RESOURCES,
				माप(काष्ठा pmcraid_resource_entry),
				GFP_KERNEL);

	अगर (शून्य == pinstance->res_entries) अणु
		pmcraid_err("failed to allocate memory for resource table\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < PMCRAID_MAX_RESOURCES; i++)
		list_add_tail(&pinstance->res_entries[i].queue,
			      &pinstance->मुक्त_res_q);

	pinstance->cfg_table = dma_alloc_coherent(&pinstance->pdev->dev,
				     माप(काष्ठा pmcraid_config_table),
				     &pinstance->cfg_table_bus_addr,
				     GFP_KERNEL);

	अगर (शून्य == pinstance->cfg_table) अणु
		pmcraid_err("couldn't alloc DMA memory for config table\n");
		pmcraid_release_config_buffers(pinstance);
		वापस -ENOMEM;
	पूर्ण

	अगर (pmcraid_allocate_hcams(pinstance)) अणु
		pmcraid_err("could not alloc DMA memory for HCAMS\n");
		pmcraid_release_config_buffers(pinstance);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pmcraid_init_tasklets - रेजिस्टरs tasklets क्रम response handling
 *
 * @pinstance: poपूर्णांकer adapter instance काष्ठाure
 *
 * Return value
 *	none
 */
अटल व्योम pmcraid_init_tasklets(काष्ठा pmcraid_instance *pinstance)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < pinstance->num_hrrq; i++)
		tasklet_init(&pinstance->isr_tasklet[i],
			     pmcraid_tasklet_function,
			     (अचिन्हित दीर्घ)&pinstance->hrrq_vector[i]);
पूर्ण

/**
 * pmcraid_समाप्त_tasklets - destroys tasklets रेजिस्टरed क्रम response handling
 *
 * @pinstance: poपूर्णांकer to adapter instance काष्ठाure
 *
 * Return value
 *	none
 */
अटल व्योम pmcraid_समाप्त_tasklets(काष्ठा pmcraid_instance *pinstance)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < pinstance->num_hrrq; i++)
		tasklet_समाप्त(&pinstance->isr_tasklet[i]);
पूर्ण

/**
 * pmcraid_release_buffers - release per-adapter buffers allocated
 *
 * @pinstance: poपूर्णांकer to adapter soft state
 *
 * Return Value
 *	none
 */
अटल व्योम pmcraid_release_buffers(काष्ठा pmcraid_instance *pinstance)
अणु
	pmcraid_release_config_buffers(pinstance);
	pmcraid_release_control_blocks(pinstance, PMCRAID_MAX_CMD);
	pmcraid_release_cmd_blocks(pinstance, PMCRAID_MAX_CMD);
	pmcraid_release_host_rrqs(pinstance, pinstance->num_hrrq);

	अगर (pinstance->inq_data != शून्य) अणु
		dma_मुक्त_coherent(&pinstance->pdev->dev,
				    माप(काष्ठा pmcraid_inquiry_data),
				    pinstance->inq_data,
				    pinstance->inq_data_baddr);

		pinstance->inq_data = शून्य;
		pinstance->inq_data_baddr = 0;
	पूर्ण

	अगर (pinstance->बारtamp_data != शून्य) अणु
		dma_मुक्त_coherent(&pinstance->pdev->dev,
				    माप(काष्ठा pmcraid_बारtamp_data),
				    pinstance->बारtamp_data,
				    pinstance->बारtamp_data_baddr);

		pinstance->बारtamp_data = शून्य;
		pinstance->बारtamp_data_baddr = 0;
	पूर्ण
पूर्ण

/**
 * pmcraid_init_buffers - allocates memory and initializes various काष्ठाures
 * @pinstance: poपूर्णांकer to per adapter instance काष्ठाure
 *
 * This routine pre-allocates memory based on the type of block as below:
 * cmdblocks(PMCRAID_MAX_CMD): kernel memory using kernel's slab_allocator,
 * IOARCBs(PMCRAID_MAX_CMD)  : DMAable memory, using pci pool allocator
 * config-table entries      : DMAable memory using dma_alloc_coherent
 * HostRRQs                  : DMAable memory, using dma_alloc_coherent
 *
 * Return Value
 *	 0 in हाल all of the blocks are allocated, -ENOMEM otherwise.
 */
अटल पूर्णांक pmcraid_init_buffers(काष्ठा pmcraid_instance *pinstance)
अणु
	पूर्णांक i;

	अगर (pmcraid_allocate_host_rrqs(pinstance)) अणु
		pmcraid_err("couldn't allocate memory for %d host rrqs\n",
			     pinstance->num_hrrq);
		वापस -ENOMEM;
	पूर्ण

	अगर (pmcraid_allocate_config_buffers(pinstance)) अणु
		pmcraid_err("couldn't allocate memory for config buffers\n");
		pmcraid_release_host_rrqs(pinstance, pinstance->num_hrrq);
		वापस -ENOMEM;
	पूर्ण

	अगर (pmcraid_allocate_cmd_blocks(pinstance)) अणु
		pmcraid_err("couldn't allocate memory for cmd blocks\n");
		pmcraid_release_config_buffers(pinstance);
		pmcraid_release_host_rrqs(pinstance, pinstance->num_hrrq);
		वापस -ENOMEM;
	पूर्ण

	अगर (pmcraid_allocate_control_blocks(pinstance)) अणु
		pmcraid_err("couldn't allocate memory control blocks\n");
		pmcraid_release_config_buffers(pinstance);
		pmcraid_release_cmd_blocks(pinstance, PMCRAID_MAX_CMD);
		pmcraid_release_host_rrqs(pinstance, pinstance->num_hrrq);
		वापस -ENOMEM;
	पूर्ण

	/* allocate DMAable memory क्रम page D0 INQUIRY buffer */
	pinstance->inq_data = dma_alloc_coherent(&pinstance->pdev->dev,
					माप(काष्ठा pmcraid_inquiry_data),
					&pinstance->inq_data_baddr, GFP_KERNEL);
	अगर (pinstance->inq_data == शून्य) अणु
		pmcraid_err("couldn't allocate DMA memory for INQUIRY\n");
		pmcraid_release_buffers(pinstance);
		वापस -ENOMEM;
	पूर्ण

	/* allocate DMAable memory क्रम set बारtamp data buffer */
	pinstance->बारtamp_data = dma_alloc_coherent(&pinstance->pdev->dev,
					माप(काष्ठा pmcraid_बारtamp_data),
					&pinstance->बारtamp_data_baddr,
					GFP_KERNEL);
	अगर (pinstance->बारtamp_data == शून्य) अणु
		pmcraid_err("couldn't allocate DMA memory क्रम \
				set समय_stamp \न");
		pmcraid_release_buffers(pinstance);
		वापस -ENOMEM;
	पूर्ण


	/* Initialize all the command blocks and add them to मुक्त pool. No
	 * need to lock (मुक्त_pool_lock) as this is करोne in initialization
	 * itself
	 */
	क्रम (i = 0; i < PMCRAID_MAX_CMD; i++) अणु
		काष्ठा pmcraid_cmd *cmdp = pinstance->cmd_list[i];
		pmcraid_init_cmdblk(cmdp, i);
		cmdp->drv_inst = pinstance;
		list_add_tail(&cmdp->मुक्त_list, &pinstance->मुक्त_cmd_pool);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pmcraid_reinit_buffers - resets various buffer poपूर्णांकers
 * @pinstance: poपूर्णांकer to adapter instance
 * Return value
 *	none
 */
अटल व्योम pmcraid_reinit_buffers(काष्ठा pmcraid_instance *pinstance)
अणु
	पूर्णांक i;
	पूर्णांक buffer_size = HRRQ_ENTRY_SIZE * PMCRAID_MAX_CMD;

	क्रम (i = 0; i < pinstance->num_hrrq; i++) अणु
		स_रखो(pinstance->hrrq_start[i], 0, buffer_size);
		pinstance->hrrq_curr[i] = pinstance->hrrq_start[i];
		pinstance->hrrq_end[i] =
			pinstance->hrrq_start[i] + PMCRAID_MAX_CMD - 1;
		pinstance->host_toggle_bit[i] = 1;
	पूर्ण
पूर्ण

/**
 * pmcraid_init_instance - initialize per instance data काष्ठाure
 * @pdev: poपूर्णांकer to pci device काष्ठाure
 * @host: poपूर्णांकer to Scsi_Host काष्ठाure
 * @mapped_pci_addr: memory mapped IOA configuration रेजिस्टरs
 *
 * Return Value
 *	 0 on success, non-zero in हाल of any failure
 */
अटल पूर्णांक pmcraid_init_instance(काष्ठा pci_dev *pdev, काष्ठा Scsi_Host *host,
				 व्योम __iomem *mapped_pci_addr)
अणु
	काष्ठा pmcraid_instance *pinstance =
		(काष्ठा pmcraid_instance *)host->hostdata;

	pinstance->host = host;
	pinstance->pdev = pdev;

	/* Initialize रेजिस्टर addresses */
	pinstance->mapped_dma_addr = mapped_pci_addr;

	/* Initialize chip-specअगरic details */
	अणु
		काष्ठा pmcraid_chip_details *chip_cfg = pinstance->chip_cfg;
		काष्ठा pmcraid_पूर्णांकerrupts *pपूर्णांक_regs = &pinstance->पूर्णांक_regs;

		pinstance->ioarrin = mapped_pci_addr + chip_cfg->ioarrin;

		pपूर्णांक_regs->ioa_host_पूर्णांकerrupt_reg =
			mapped_pci_addr + chip_cfg->ioa_host_पूर्णांकr;
		pपूर्णांक_regs->ioa_host_पूर्णांकerrupt_clr_reg =
			mapped_pci_addr + chip_cfg->ioa_host_पूर्णांकr_clr;
		pपूर्णांक_regs->ioa_host_msix_पूर्णांकerrupt_reg =
			mapped_pci_addr + chip_cfg->ioa_host_msix_पूर्णांकr;
		pपूर्णांक_regs->host_ioa_पूर्णांकerrupt_reg =
			mapped_pci_addr + chip_cfg->host_ioa_पूर्णांकr;
		pपूर्णांक_regs->host_ioa_पूर्णांकerrupt_clr_reg =
			mapped_pci_addr + chip_cfg->host_ioa_पूर्णांकr_clr;

		/* Current version of firmware exposes पूर्णांकerrupt mask set
		 * and mask clr रेजिस्टरs through memory mapped bar0.
		 */
		pinstance->mailbox = mapped_pci_addr + chip_cfg->mailbox;
		pinstance->ioa_status = mapped_pci_addr + chip_cfg->ioastatus;
		pपूर्णांक_regs->ioa_host_पूर्णांकerrupt_mask_reg =
			mapped_pci_addr + chip_cfg->ioa_host_mask;
		pपूर्णांक_regs->ioa_host_पूर्णांकerrupt_mask_clr_reg =
			mapped_pci_addr + chip_cfg->ioa_host_mask_clr;
		pपूर्णांक_regs->global_पूर्णांकerrupt_mask_reg =
			mapped_pci_addr + chip_cfg->global_पूर्णांकr_mask;
	पूर्ण;

	pinstance->ioa_reset_attempts = 0;
	init_रुकोqueue_head(&pinstance->reset_रुको_q);

	atomic_set(&pinstance->outstanding_cmds, 0);
	atomic_set(&pinstance->last_message_id, 0);
	atomic_set(&pinstance->expose_resources, 0);

	INIT_LIST_HEAD(&pinstance->मुक्त_res_q);
	INIT_LIST_HEAD(&pinstance->used_res_q);
	INIT_LIST_HEAD(&pinstance->मुक्त_cmd_pool);
	INIT_LIST_HEAD(&pinstance->pending_cmd_pool);

	spin_lock_init(&pinstance->मुक्त_pool_lock);
	spin_lock_init(&pinstance->pending_pool_lock);
	spin_lock_init(&pinstance->resource_lock);
	mutex_init(&pinstance->aen_queue_lock);

	/* Work-queue (Shared) क्रम deferred processing error handling */
	INIT_WORK(&pinstance->worker_q, pmcraid_worker_function);

	/* Initialize the शेष log_level */
	pinstance->current_log_level = pmcraid_log_level;

	/* Setup variables required क्रम reset engine */
	pinstance->ioa_state = IOA_STATE_UNKNOWN;
	pinstance->reset_cmd = शून्य;
	वापस 0;
पूर्ण

/**
 * pmcraid_shutकरोwn - shutकरोwn adapter controller.
 * @pdev: pci device काष्ठा
 *
 * Issues an adapter shutकरोwn to the card रुकोs क्रम its completion
 *
 * Return value
 *	  none
 */
अटल व्योम pmcraid_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pmcraid_instance *pinstance = pci_get_drvdata(pdev);
	pmcraid_reset_bringकरोwn(pinstance);
पूर्ण


/*
 * pmcraid_get_minor - वापसs unused minor number from minor number biपंचांगap
 */
अटल अचिन्हित लघु pmcraid_get_minor(व्योम)
अणु
	पूर्णांक minor;

	minor = find_first_zero_bit(pmcraid_minor, PMCRAID_MAX_ADAPTERS);
	__set_bit(minor, pmcraid_minor);
	वापस minor;
पूर्ण

/*
 * pmcraid_release_minor - releases given minor back to minor number biपंचांगap
 */
अटल व्योम pmcraid_release_minor(अचिन्हित लघु minor)
अणु
	__clear_bit(minor, pmcraid_minor);
पूर्ण

/**
 * pmcraid_setup_chrdev - allocates a minor number and रेजिस्टरs a अक्षर device
 *
 * @pinstance: poपूर्णांकer to adapter instance क्रम which to रेजिस्टर device
 *
 * Return value
 *	0 in हाल of success, otherwise non-zero
 */
अटल पूर्णांक pmcraid_setup_chrdev(काष्ठा pmcraid_instance *pinstance)
अणु
	पूर्णांक minor;
	पूर्णांक error;

	minor = pmcraid_get_minor();
	cdev_init(&pinstance->cdev, &pmcraid_fops);
	pinstance->cdev.owner = THIS_MODULE;

	error = cdev_add(&pinstance->cdev, MKDEV(pmcraid_major, minor), 1);

	अगर (error)
		pmcraid_release_minor(minor);
	अन्यथा
		device_create(pmcraid_class, शून्य, MKDEV(pmcraid_major, minor),
			      शून्य, "%s%u", PMCRAID_DEVखाता, minor);
	वापस error;
पूर्ण

/**
 * pmcraid_release_chrdev - unरेजिस्टरs per-adapter management पूर्णांकerface
 *
 * @pinstance: poपूर्णांकer to adapter instance काष्ठाure
 *
 * Return value
 *  none
 */
अटल व्योम pmcraid_release_chrdev(काष्ठा pmcraid_instance *pinstance)
अणु
	pmcraid_release_minor(MINOR(pinstance->cdev.dev));
	device_destroy(pmcraid_class,
		       MKDEV(pmcraid_major, MINOR(pinstance->cdev.dev)));
	cdev_del(&pinstance->cdev);
पूर्ण

/**
 * pmcraid_हटाओ - IOA hot plug हटाओ entry poपूर्णांक
 * @pdev: pci device काष्ठा
 *
 * Return value
 *	  none
 */
अटल व्योम pmcraid_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pmcraid_instance *pinstance = pci_get_drvdata(pdev);

	/* हटाओ the management पूर्णांकerface (/dev file) क्रम this device */
	pmcraid_release_chrdev(pinstance);

	/* हटाओ host ढाँचा from scsi midlayer */
	scsi_हटाओ_host(pinstance->host);

	/* block requests from mid-layer */
	scsi_block_requests(pinstance->host);

	/* initiate shutकरोwn adapter */
	pmcraid_shutकरोwn(pdev);

	pmcraid_disable_पूर्णांकerrupts(pinstance, ~0);
	flush_work(&pinstance->worker_q);

	pmcraid_समाप्त_tasklets(pinstance);
	pmcraid_unरेजिस्टर_पूर्णांकerrupt_handler(pinstance);
	pmcraid_release_buffers(pinstance);
	iounmap(pinstance->mapped_dma_addr);
	pci_release_regions(pdev);
	scsi_host_put(pinstance->host);
	pci_disable_device(pdev);

	वापस;
पूर्ण

/**
 * pmcraid_suspend - driver suspend entry poपूर्णांक क्रम घातer management
 * @dev:   Device काष्ठाure
 *
 * Return Value - 0 always
 */
अटल पूर्णांक __maybe_unused pmcraid_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा pmcraid_instance *pinstance = pci_get_drvdata(pdev);

	pmcraid_shutकरोwn(pdev);
	pmcraid_disable_पूर्णांकerrupts(pinstance, ~0);
	pmcraid_समाप्त_tasklets(pinstance);
	pmcraid_unरेजिस्टर_पूर्णांकerrupt_handler(pinstance);

	वापस 0;
पूर्ण

/**
 * pmcraid_resume - driver resume entry poपूर्णांक PCI घातer management
 * @dev: Device काष्ठाure
 *
 * Return Value - 0 in हाल of success. Error code in हाल of any failure
 */
अटल पूर्णांक __maybe_unused pmcraid_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा pmcraid_instance *pinstance = pci_get_drvdata(pdev);
	काष्ठा Scsi_Host *host = pinstance->host;
	पूर्णांक rc = 0;

	अगर (माप(dma_addr_t) == 4 ||
	    dma_set_mask(&pdev->dev, DMA_BIT_MASK(64)))
		rc = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));

	अगर (rc == 0)
		rc = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));

	अगर (rc != 0) अणु
		dev_err(&pdev->dev, "resume: Failed to set PCI DMA mask\n");
		जाओ disable_device;
	पूर्ण

	pmcraid_disable_पूर्णांकerrupts(pinstance, ~0);
	atomic_set(&pinstance->outstanding_cmds, 0);
	rc = pmcraid_रेजिस्टर_पूर्णांकerrupt_handler(pinstance);

	अगर (rc) अणु
		dev_err(&pdev->dev,
			"resume: couldn't register interrupt handlers\n");
		rc = -ENODEV;
		जाओ release_host;
	पूर्ण

	pmcraid_init_tasklets(pinstance);
	pmcraid_enable_पूर्णांकerrupts(pinstance, PMCRAID_PCI_INTERRUPTS);

	/* Start with hard reset sequence which brings up IOA to operational
	 * state as well as completes the reset sequence.
	 */
	pinstance->ioa_hard_reset = 1;

	/* Start IOA firmware initialization and bring card to Operational
	 * state.
	 */
	अगर (pmcraid_reset_bringup(pinstance)) अणु
		dev_err(&pdev->dev, "couldn't initialize IOA\n");
		rc = -ENODEV;
		जाओ release_tasklets;
	पूर्ण

	वापस 0;

release_tasklets:
	pmcraid_disable_पूर्णांकerrupts(pinstance, ~0);
	pmcraid_समाप्त_tasklets(pinstance);
	pmcraid_unरेजिस्टर_पूर्णांकerrupt_handler(pinstance);

release_host:
	scsi_host_put(host);

disable_device:

	वापस rc;
पूर्ण

/**
 * pmcraid_complete_ioa_reset - Called by either समयr or tasklet during
 *				completion of the ioa reset
 * @cmd: poपूर्णांकer to reset command block
 */
अटल व्योम pmcraid_complete_ioa_reset(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(pinstance->host->host_lock, flags);
	pmcraid_ioa_reset(cmd);
	spin_unlock_irqrestore(pinstance->host->host_lock, flags);
	scsi_unblock_requests(pinstance->host);
	schedule_work(&pinstance->worker_q);
पूर्ण

/**
 * pmcraid_set_supported_devs - sends SET SUPPORTED DEVICES to IOAFP
 *
 * @cmd: poपूर्णांकer to pmcraid_cmd काष्ठाure
 *
 * Return Value
 *  0 क्रम success or non-zero क्रम failure हालs
 */
अटल व्योम pmcraid_set_supported_devs(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा pmcraid_ioarcb *ioarcb = &cmd->ioa_cb->ioarcb;
	व्योम (*cmd_करोne) (काष्ठा pmcraid_cmd *) = pmcraid_complete_ioa_reset;

	pmcraid_reinit_cmdblk(cmd);

	ioarcb->resource_handle = cpu_to_le32(PMCRAID_IOA_RES_HANDLE);
	ioarcb->request_type = REQ_TYPE_IOACMD;
	ioarcb->cdb[0] = PMCRAID_SET_SUPPORTED_DEVICES;
	ioarcb->cdb[1] = ALL_DEVICES_SUPPORTED;

	/* If this was called as part of resource table reinitialization due to
	 * lost CCN, it is enough to वापस the command block back to मुक्त pool
	 * as part of set_supported_devs completion function.
	 */
	अगर (cmd->drv_inst->reinit_cfg_table) अणु
		cmd->drv_inst->reinit_cfg_table = 0;
		cmd->release = 1;
		cmd_करोne = pmcraid_reinit_cfgtable_करोne;
	पूर्ण

	/* we will be करोne with the reset sequence after set supported devices,
	 * setup the करोne function to वापस the command block back to मुक्त
	 * pool
	 */
	pmcraid_send_cmd(cmd,
			 cmd_करोne,
			 PMCRAID_SET_SUP_DEV_TIMEOUT,
			 pmcraid_समयout_handler);
	वापस;
पूर्ण

/**
 * pmcraid_set_बारtamp - set the बारtamp to IOAFP
 *
 * @cmd: poपूर्णांकer to pmcraid_cmd काष्ठाure
 *
 * Return Value
 *  0 क्रम success or non-zero क्रम failure हालs
 */
अटल व्योम pmcraid_set_बारtamp(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;
	काष्ठा pmcraid_ioarcb *ioarcb = &cmd->ioa_cb->ioarcb;
	__be32 समय_stamp_len = cpu_to_be32(PMCRAID_TIMESTAMP_LEN);
	काष्ठा pmcraid_ioadl_desc *ioadl;
	u64 बारtamp;

	बारtamp = kसमय_get_real_seconds() * 1000;

	pinstance->बारtamp_data->बारtamp[0] = (__u8)(बारtamp);
	pinstance->बारtamp_data->बारtamp[1] = (__u8)((बारtamp) >> 8);
	pinstance->बारtamp_data->बारtamp[2] = (__u8)((बारtamp) >> 16);
	pinstance->बारtamp_data->बारtamp[3] = (__u8)((बारtamp) >> 24);
	pinstance->बारtamp_data->बारtamp[4] = (__u8)((बारtamp) >> 32);
	pinstance->बारtamp_data->बारtamp[5] = (__u8)((बारtamp)  >> 40);

	pmcraid_reinit_cmdblk(cmd);
	ioarcb->request_type = REQ_TYPE_SCSI;
	ioarcb->resource_handle = cpu_to_le32(PMCRAID_IOA_RES_HANDLE);
	ioarcb->cdb[0] = PMCRAID_SCSI_SET_TIMESTAMP;
	ioarcb->cdb[1] = PMCRAID_SCSI_SERVICE_ACTION;
	स_नकल(&(ioarcb->cdb[6]), &समय_stamp_len, माप(समय_stamp_len));

	ioarcb->ioadl_bus_addr = cpu_to_le64((cmd->ioa_cb_bus_addr) +
					दुरत्व(काष्ठा pmcraid_ioarcb,
						add_data.u.ioadl[0]));
	ioarcb->ioadl_length = cpu_to_le32(माप(काष्ठा pmcraid_ioadl_desc));
	ioarcb->ioarcb_bus_addr &= cpu_to_le64(~(0x1FULL));

	ioarcb->request_flags0 |= NO_LINK_DESCS;
	ioarcb->request_flags0 |= TRANSFER_सूची_WRITE;
	ioarcb->data_transfer_length =
		cpu_to_le32(माप(काष्ठा pmcraid_बारtamp_data));
	ioadl = &(ioarcb->add_data.u.ioadl[0]);
	ioadl->flags = IOADL_FLAGS_LAST_DESC;
	ioadl->address = cpu_to_le64(pinstance->बारtamp_data_baddr);
	ioadl->data_len = cpu_to_le32(माप(काष्ठा pmcraid_बारtamp_data));

	अगर (!pinstance->बारtamp_error) अणु
		pinstance->बारtamp_error = 0;
		pmcraid_send_cmd(cmd, pmcraid_set_supported_devs,
			 PMCRAID_INTERNAL_TIMEOUT, pmcraid_समयout_handler);
	पूर्ण अन्यथा अणु
		pmcraid_send_cmd(cmd, pmcraid_वापस_cmd,
			 PMCRAID_INTERNAL_TIMEOUT, pmcraid_समयout_handler);
		वापस;
	पूर्ण
पूर्ण


/**
 * pmcraid_init_res_table - Initialize the resource table
 * @cmd:  poपूर्णांकer to pmcraid command काष्ठा
 *
 * This function looks through the existing resource table, comparing
 * it with the config table. This function will take care of old/new
 * devices and schedule adding/removing them from the mid-layer
 * as appropriate.
 *
 * Return value
 *	 None
 */
अटल व्योम pmcraid_init_res_table(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;
	काष्ठा pmcraid_resource_entry *res, *temp;
	काष्ठा pmcraid_config_table_entry *cfgte;
	अचिन्हित दीर्घ lock_flags;
	पूर्णांक found, rc, i;
	u16 fw_version;
	LIST_HEAD(old_res);

	अगर (pinstance->cfg_table->flags & MICROCODE_UPDATE_REQUIRED)
		pmcraid_err("IOA requires microcode download\n");

	fw_version = be16_to_cpu(pinstance->inq_data->fw_version);

	/* resource list is रक्षित by pinstance->resource_lock.
	 * init_res_table can be called from probe (user-thपढ़ो) or runसमय
	 * reset (समयr/tasklet)
	 */
	spin_lock_irqsave(&pinstance->resource_lock, lock_flags);

	list_क्रम_each_entry_safe(res, temp, &pinstance->used_res_q, queue)
		list_move_tail(&res->queue, &old_res);

	क्रम (i = 0; i < le16_to_cpu(pinstance->cfg_table->num_entries); i++) अणु
		अगर (be16_to_cpu(pinstance->inq_data->fw_version) <=
						PMCRAID_FW_VERSION_1)
			cfgte = &pinstance->cfg_table->entries[i];
		अन्यथा
			cfgte = (काष्ठा pmcraid_config_table_entry *)
					&pinstance->cfg_table->entries_ext[i];

		अगर (!pmcraid_expose_resource(fw_version, cfgte))
			जारी;

		found = 0;

		/* If this entry was alपढ़ोy detected and initialized */
		list_क्रम_each_entry_safe(res, temp, &old_res, queue) अणु

			rc = स_भेद(&res->cfg_entry.resource_address,
				    &cfgte->resource_address,
				    माप(cfgte->resource_address));
			अगर (!rc) अणु
				list_move_tail(&res->queue,
						&pinstance->used_res_q);
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण

		/* If this is new entry, initialize it and add it the queue */
		अगर (!found) अणु

			अगर (list_empty(&pinstance->मुक्त_res_q)) अणु
				pmcraid_err("Too many devices attached\n");
				अवरोध;
			पूर्ण

			found = 1;
			res = list_entry(pinstance->मुक्त_res_q.next,
					 काष्ठा pmcraid_resource_entry, queue);

			res->scsi_dev = शून्य;
			res->change_detected = RES_CHANGE_ADD;
			res->reset_progress = 0;
			list_move_tail(&res->queue, &pinstance->used_res_q);
		पूर्ण

		/* copy new configuration table entry details पूर्णांकo driver
		 * मुख्यtained resource entry
		 */
		अगर (found) अणु
			स_नकल(&res->cfg_entry, cfgte,
					pinstance->config_table_entry_size);
			pmcraid_info("New res type:%x, vset:%x, addr:%x:\n",
				 res->cfg_entry.resource_type,
				 (fw_version <= PMCRAID_FW_VERSION_1 ?
					res->cfg_entry.unique_flags1 :
					le16_to_cpu(res->cfg_entry.array_id) & 0xFF),
				 le32_to_cpu(res->cfg_entry.resource_address));
		पूर्ण
	पूर्ण

	/* Detect any deleted entries, mark them क्रम deletion from mid-layer */
	list_क्रम_each_entry_safe(res, temp, &old_res, queue) अणु

		अगर (res->scsi_dev) अणु
			res->change_detected = RES_CHANGE_DEL;
			res->cfg_entry.resource_handle =
				PMCRAID_INVALID_RES_HANDLE;
			list_move_tail(&res->queue, &pinstance->used_res_q);
		पूर्ण अन्यथा अणु
			list_move_tail(&res->queue, &pinstance->मुक्त_res_q);
		पूर्ण
	पूर्ण

	/* release the resource list lock */
	spin_unlock_irqrestore(&pinstance->resource_lock, lock_flags);
	pmcraid_set_बारtamp(cmd);
पूर्ण

/**
 * pmcraid_querycfg - Send a Query IOA Config to the adapter.
 * @cmd: poपूर्णांकer pmcraid_cmd काष्ठा
 *
 * This function sends a Query IOA Configuration command to the adapter to
 * retrieve the IOA configuration table.
 *
 * Return value:
 *	none
 */
अटल व्योम pmcraid_querycfg(काष्ठा pmcraid_cmd *cmd)
अणु
	काष्ठा pmcraid_ioarcb *ioarcb = &cmd->ioa_cb->ioarcb;
	काष्ठा pmcraid_ioadl_desc *ioadl;
	काष्ठा pmcraid_instance *pinstance = cmd->drv_inst;
	__be32 cfg_table_size = cpu_to_be32(माप(काष्ठा pmcraid_config_table));

	अगर (be16_to_cpu(pinstance->inq_data->fw_version) <=
					PMCRAID_FW_VERSION_1)
		pinstance->config_table_entry_size =
			माप(काष्ठा pmcraid_config_table_entry);
	अन्यथा
		pinstance->config_table_entry_size =
			माप(काष्ठा pmcraid_config_table_entry_ext);

	ioarcb->request_type = REQ_TYPE_IOACMD;
	ioarcb->resource_handle = cpu_to_le32(PMCRAID_IOA_RES_HANDLE);

	ioarcb->cdb[0] = PMCRAID_QUERY_IOA_CONFIG;

	/* firmware requires 4-byte length field, specअगरied in B.E क्रमmat */
	स_नकल(&(ioarcb->cdb[10]), &cfg_table_size, माप(cfg_table_size));

	/* Since entire config table can be described by single IOADL, it can
	 * be part of IOARCB itself
	 */
	ioarcb->ioadl_bus_addr = cpu_to_le64((cmd->ioa_cb_bus_addr) +
					दुरत्व(काष्ठा pmcraid_ioarcb,
						add_data.u.ioadl[0]));
	ioarcb->ioadl_length = cpu_to_le32(माप(काष्ठा pmcraid_ioadl_desc));
	ioarcb->ioarcb_bus_addr &= cpu_to_le64(~0x1FULL);

	ioarcb->request_flags0 |= NO_LINK_DESCS;
	ioarcb->data_transfer_length =
		cpu_to_le32(माप(काष्ठा pmcraid_config_table));

	ioadl = &(ioarcb->add_data.u.ioadl[0]);
	ioadl->flags = IOADL_FLAGS_LAST_DESC;
	ioadl->address = cpu_to_le64(pinstance->cfg_table_bus_addr);
	ioadl->data_len = cpu_to_le32(माप(काष्ठा pmcraid_config_table));

	pmcraid_send_cmd(cmd, pmcraid_init_res_table,
			 PMCRAID_INTERNAL_TIMEOUT, pmcraid_समयout_handler);
पूर्ण


/**
 * pmcraid_probe - PCI probe entry poपूर्णांकer क्रम PMC MaxRAID controller driver
 * @pdev: poपूर्णांकer to pci device काष्ठाure
 * @dev_id: poपूर्णांकer to device ids काष्ठाure
 *
 * Return Value
 *	वापसs 0 अगर the device is claimed and successfully configured.
 *	वापसs non-zero error code in हाल of any failure
 */
अटल पूर्णांक pmcraid_probe(काष्ठा pci_dev *pdev,
			 स्थिर काष्ठा pci_device_id *dev_id)
अणु
	काष्ठा pmcraid_instance *pinstance;
	काष्ठा Scsi_Host *host;
	व्योम __iomem *mapped_pci_addr;
	पूर्णांक rc = PCIBIOS_SUCCESSFUL;

	अगर (atomic_पढ़ो(&pmcraid_adapter_count) >= PMCRAID_MAX_ADAPTERS) अणु
		pmcraid_err
			("maximum number(%d) of supported adapters reached\n",
			 atomic_पढ़ो(&pmcraid_adapter_count));
		वापस -ENOMEM;
	पूर्ण

	atomic_inc(&pmcraid_adapter_count);
	rc = pci_enable_device(pdev);

	अगर (rc) अणु
		dev_err(&pdev->dev, "Cannot enable adapter\n");
		atomic_dec(&pmcraid_adapter_count);
		वापस rc;
	पूर्ण

	dev_info(&pdev->dev,
		"Found new IOA(%x:%x), Total IOA count: %d\n",
		 pdev->venकरोr, pdev->device,
		 atomic_पढ़ो(&pmcraid_adapter_count));

	rc = pci_request_regions(pdev, PMCRAID_DRIVER_NAME);

	अगर (rc < 0) अणु
		dev_err(&pdev->dev,
			"Couldn't register memory range of registers\n");
		जाओ out_disable_device;
	पूर्ण

	mapped_pci_addr = pci_iomap(pdev, 0, 0);

	अगर (!mapped_pci_addr) अणु
		dev_err(&pdev->dev, "Couldn't map PCI registers memory\n");
		rc = -ENOMEM;
		जाओ out_release_regions;
	पूर्ण

	pci_set_master(pdev);

	/* Firmware requires the प्रणाली bus address of IOARCB to be within
	 * 32-bit addressable range though it has 64-bit IOARRIN रेजिस्टर.
	 * However, firmware supports 64-bit streaming DMA buffers, whereas
	 * coherent buffers are to be 32-bit. Since dma_alloc_coherent always
	 * वापसs memory within 4GB (अगर not, change this logic), coherent
	 * buffers are within firmware acceptable address ranges.
	 */
	अगर (माप(dma_addr_t) == 4 ||
	    dma_set_mask(&pdev->dev, DMA_BIT_MASK(64)))
		rc = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));

	/* firmware expects 32-bit DMA addresses क्रम IOARRIN रेजिस्टर; set 32
	 * bit mask क्रम dma_alloc_coherent to वापस addresses within 4GB
	 */
	अगर (rc == 0)
		rc = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));

	अगर (rc != 0) अणु
		dev_err(&pdev->dev, "Failed to set PCI DMA mask\n");
		जाओ cleanup_nomem;
	पूर्ण

	host = scsi_host_alloc(&pmcraid_host_ढाँचा,
				माप(काष्ठा pmcraid_instance));

	अगर (!host) अणु
		dev_err(&pdev->dev, "scsi_host_alloc failed!\n");
		rc = -ENOMEM;
		जाओ cleanup_nomem;
	पूर्ण

	host->max_id = PMCRAID_MAX_NUM_TARGETS_PER_BUS;
	host->max_lun = PMCRAID_MAX_NUM_LUNS_PER_TARGET;
	host->unique_id = host->host_no;
	host->max_channel = PMCRAID_MAX_BUS_TO_SCAN;
	host->max_cmd_len = PMCRAID_MAX_CDB_LEN;

	/* zero out entire instance काष्ठाure */
	pinstance = (काष्ठा pmcraid_instance *)host->hostdata;
	स_रखो(pinstance, 0, माप(*pinstance));

	pinstance->chip_cfg =
		(काष्ठा pmcraid_chip_details *)(dev_id->driver_data);

	rc = pmcraid_init_instance(pdev, host, mapped_pci_addr);

	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "failed to initialize adapter instance\n");
		जाओ out_scsi_host_put;
	पूर्ण

	pci_set_drvdata(pdev, pinstance);

	/* Save PCI config-space क्रम use following the reset */
	rc = pci_save_state(pinstance->pdev);

	अगर (rc != 0) अणु
		dev_err(&pdev->dev, "Failed to save PCI config space\n");
		जाओ out_scsi_host_put;
	पूर्ण

	pmcraid_disable_पूर्णांकerrupts(pinstance, ~0);

	rc = pmcraid_रेजिस्टर_पूर्णांकerrupt_handler(pinstance);

	अगर (rc) अणु
		dev_err(&pdev->dev, "couldn't register interrupt handler\n");
		जाओ out_scsi_host_put;
	पूर्ण

	pmcraid_init_tasklets(pinstance);

	/* allocate verious buffers used by LLD.*/
	rc = pmcraid_init_buffers(pinstance);

	अगर (rc) अणु
		pmcraid_err("couldn't allocate memory blocks\n");
		जाओ out_unरेजिस्टर_isr;
	पूर्ण

	/* check the reset type required */
	pmcraid_reset_type(pinstance);

	pmcraid_enable_पूर्णांकerrupts(pinstance, PMCRAID_PCI_INTERRUPTS);

	/* Start IOA firmware initialization and bring card to Operational
	 * state.
	 */
	pmcraid_info("starting IOA initialization sequence\n");
	अगर (pmcraid_reset_bringup(pinstance)) अणु
		dev_err(&pdev->dev, "couldn't initialize IOA\n");
		rc = 1;
		जाओ out_release_bufs;
	पूर्ण

	/* Add adapter instance पूर्णांकo mid-layer list */
	rc = scsi_add_host(pinstance->host, &pdev->dev);
	अगर (rc != 0) अणु
		pmcraid_err("couldn't add host into mid-layer: %d\n", rc);
		जाओ out_release_bufs;
	पूर्ण

	scsi_scan_host(pinstance->host);

	rc = pmcraid_setup_chrdev(pinstance);

	अगर (rc != 0) अणु
		pmcraid_err("couldn't create mgmt interface, error: %x\n",
			     rc);
		जाओ out_हटाओ_host;
	पूर्ण

	/* Schedule worker thपढ़ो to handle CCN and take care of adding and
	 * removing devices to OS
	 */
	atomic_set(&pinstance->expose_resources, 1);
	schedule_work(&pinstance->worker_q);
	वापस rc;

out_हटाओ_host:
	scsi_हटाओ_host(host);

out_release_bufs:
	pmcraid_release_buffers(pinstance);

out_unरेजिस्टर_isr:
	pmcraid_समाप्त_tasklets(pinstance);
	pmcraid_unरेजिस्टर_पूर्णांकerrupt_handler(pinstance);

out_scsi_host_put:
	scsi_host_put(host);

cleanup_nomem:
	iounmap(mapped_pci_addr);

out_release_regions:
	pci_release_regions(pdev);

out_disable_device:
	atomic_dec(&pmcraid_adapter_count);
	pci_disable_device(pdev);
	वापस -ENODEV;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(pmcraid_pm_ops, pmcraid_suspend, pmcraid_resume);

/*
 * PCI driver काष्ठाure of pmcraid driver
 */
अटल काष्ठा pci_driver pmcraid_driver = अणु
	.name = PMCRAID_DRIVER_NAME,
	.id_table = pmcraid_pci_table,
	.probe = pmcraid_probe,
	.हटाओ = pmcraid_हटाओ,
	.driver.pm = &pmcraid_pm_ops,
	.shutकरोwn = pmcraid_shutकरोwn
पूर्ण;

/**
 * pmcraid_init - module load entry poपूर्णांक
 */
अटल पूर्णांक __init pmcraid_init(व्योम)
अणु
	dev_t dev;
	पूर्णांक error;

	pmcraid_info("%s Device Driver version: %s\n",
			 PMCRAID_DRIVER_NAME, PMCRAID_DRIVER_VERSION);

	error = alloc_chrdev_region(&dev, 0,
				    PMCRAID_MAX_ADAPTERS,
				    PMCRAID_DEVखाता);

	अगर (error) अणु
		pmcraid_err("failed to get a major number for adapters\n");
		जाओ out_init;
	पूर्ण

	pmcraid_major = MAJOR(dev);
	pmcraid_class = class_create(THIS_MODULE, PMCRAID_DEVखाता);

	अगर (IS_ERR(pmcraid_class)) अणु
		error = PTR_ERR(pmcraid_class);
		pmcraid_err("failed to register with sysfs, error = %x\n",
			    error);
		जाओ out_unreg_chrdev;
	पूर्ण

	error = pmcraid_netlink_init();

	अगर (error) अणु
		class_destroy(pmcraid_class);
		जाओ out_unreg_chrdev;
	पूर्ण

	error = pci_रेजिस्टर_driver(&pmcraid_driver);

	अगर (error == 0)
		जाओ out_init;

	pmcraid_err("failed to register pmcraid driver, error = %x\n",
		     error);
	class_destroy(pmcraid_class);
	pmcraid_netlink_release();

out_unreg_chrdev:
	unरेजिस्टर_chrdev_region(MKDEV(pmcraid_major, 0), PMCRAID_MAX_ADAPTERS);

out_init:
	वापस error;
पूर्ण

/**
 * pmcraid_निकास - module unload entry poपूर्णांक
 */
अटल व्योम __निकास pmcraid_निकास(व्योम)
अणु
	pmcraid_netlink_release();
	unरेजिस्टर_chrdev_region(MKDEV(pmcraid_major, 0),
				 PMCRAID_MAX_ADAPTERS);
	pci_unरेजिस्टर_driver(&pmcraid_driver);
	class_destroy(pmcraid_class);
पूर्ण

module_init(pmcraid_init);
module_निकास(pmcraid_निकास);
