<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Linux MegaRAID driver क्रम SAS based RAID controllers
 *
 *  Copyright (c) 2009-2013  LSI Corporation
 *  Copyright (c) 2013-2016  Avago Technologies
 *  Copyright (c) 2016-2018  Broadcom Inc.
 *
 *  खाता: megaraid_sas_fusion.c
 *
 *  Authors: Broadcom Inc.
 *           Sumant Patro
 *           Adam Radक्रमd
 *           Kashyap Desai <kashyap.desai@broadcom.com>
 *           Sumit Saxena <sumit.saxena@broadcom.com>
 *
 *  Send feedback to: megaraidlinux.pdl@broadcom.com
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/list.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/uपन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/fs.h>
#समावेश <linux/compat.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/mutex.h>
#समावेश <linux/poll.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/irq_poll.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <linux/dmi.h>

#समावेश "megaraid_sas_fusion.h"
#समावेश "megaraid_sas.h"


बाह्य व्योम
megasas_complete_cmd(काष्ठा megasas_instance *instance,
		     काष्ठा megasas_cmd *cmd, u8 alt_status);
पूर्णांक
रुको_and_poll(काष्ठा megasas_instance *instance, काष्ठा megasas_cmd *cmd,
	      पूर्णांक seconds);

पूर्णांक
megasas_clear_पूर्णांकr_fusion(काष्ठा megasas_instance *instance);

पूर्णांक megasas_transition_to_पढ़ोy(काष्ठा megasas_instance *instance, पूर्णांक ocr);

बाह्य u32 megasas_dbg_lvl;
पूर्णांक megasas_sriov_start_heartbeat(काष्ठा megasas_instance *instance,
				  पूर्णांक initial);
बाह्य काष्ठा megasas_mgmt_info megasas_mgmt_info;
बाह्य अचिन्हित पूर्णांक resetरुकोसमय;
बाह्य अचिन्हित पूर्णांक dual_qdepth_disable;
अटल व्योम megasas_मुक्त_rdpq_fusion(काष्ठा megasas_instance *instance);
अटल व्योम megasas_मुक्त_reply_fusion(काष्ठा megasas_instance *instance);
अटल अंतरभूत
व्योम megasas_configure_queue_sizes(काष्ठा megasas_instance *instance);
अटल व्योम megasas_fusion_crash_dump(काष्ठा megasas_instance *instance);

/**
 * megasas_adp_reset_रुको_क्रम_पढ़ोy -	initiate chip reset and रुको क्रम
 *					controller to come to पढ़ोy state
 * @instance:				adapter's soft state
 * @करो_adp_reset:			If true, करो a chip reset
 * @ocr_context:			If called from OCR context this will
 *					be set to 1, अन्यथा 0
 *
 * This function initates a chip reset followed by a रुको क्रम controller to
 * transition to पढ़ोy state.
 * During this, driver will block all access to PCI config space from userspace
 */
पूर्णांक
megasas_adp_reset_रुको_क्रम_पढ़ोy(काष्ठा megasas_instance *instance,
				 bool करो_adp_reset,
				 पूर्णांक ocr_context)
अणु
	पूर्णांक ret = FAILED;

	/*
	 * Block access to PCI config space from userspace
	 * when diag reset is initiated from driver
	 */
	अगर (megasas_dbg_lvl & OCR_DEBUG)
		dev_info(&instance->pdev->dev,
			 "Block access to PCI config space %s %d\n",
			 __func__, __LINE__);

	pci_cfg_access_lock(instance->pdev);

	अगर (करो_adp_reset) अणु
		अगर (instance->instancet->adp_reset
			(instance, instance->reg_set))
			जाओ out;
	पूर्ण

	/* Wait क्रम FW to become पढ़ोy */
	अगर (megasas_transition_to_पढ़ोy(instance, ocr_context)) अणु
		dev_warn(&instance->pdev->dev,
			 "Failed to transition controller to ready for scsi%d.\n",
			 instance->host->host_no);
		जाओ out;
	पूर्ण

	ret = SUCCESS;
out:
	अगर (megasas_dbg_lvl & OCR_DEBUG)
		dev_info(&instance->pdev->dev,
			 "Unlock access to PCI config space %s %d\n",
			 __func__, __LINE__);

	pci_cfg_access_unlock(instance->pdev);

	वापस ret;
पूर्ण

/**
 * megasas_check_same_4gb_region -	check अगर allocation
 *					crosses same 4GB boundary or not
 * @instance:				adapter's soft instance
 * @start_addr:				start address of DMA allocation
 * @size:				size of allocation in bytes
 * @वापस:				true : allocation करोes not cross same
 *					4GB boundary
 *					false: allocation crosses same
 *					4GB boundary
 */
अटल अंतरभूत bool megasas_check_same_4gb_region
	(काष्ठा megasas_instance *instance, dma_addr_t start_addr, माप_प्रकार size)
अणु
	dma_addr_t end_addr;

	end_addr = start_addr + size;

	अगर (upper_32_bits(start_addr) != upper_32_bits(end_addr)) अणु
		dev_err(&instance->pdev->dev,
			"Failed to get same 4GB boundary: start_addr: 0x%llx end_addr: 0x%llx\n",
			(अचिन्हित दीर्घ दीर्घ)start_addr,
			(अचिन्हित दीर्घ दीर्घ)end_addr);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * megasas_enable_पूर्णांकr_fusion -	Enables पूर्णांकerrupts
 * @instance:	adapter's soft instance
 */
अटल व्योम
megasas_enable_पूर्णांकr_fusion(काष्ठा megasas_instance *instance)
अणु
	काष्ठा megasas_रेजिस्टर_set __iomem *regs;
	regs = instance->reg_set;

	instance->mask_पूर्णांकerrupts = 0;
	/* For Thunderbolt/Invader also clear पूर्णांकr on enable */
	ग_लिखोl(~0, &regs->outbound_पूर्णांकr_status);
	पढ़ोl(&regs->outbound_पूर्णांकr_status);

	ग_लिखोl(~MFI_FUSION_ENABLE_INTERRUPT_MASK, &(regs)->outbound_पूर्णांकr_mask);

	/* Dummy पढ़ोl to क्रमce pci flush */
	dev_info(&instance->pdev->dev, "%s is called outbound_intr_mask:0x%08x\n",
		 __func__, पढ़ोl(&regs->outbound_पूर्णांकr_mask));
पूर्ण

/**
 * megasas_disable_पूर्णांकr_fusion - Disables पूर्णांकerrupt
 * @instance:	adapter's soft instance
 */
अटल व्योम
megasas_disable_पूर्णांकr_fusion(काष्ठा megasas_instance *instance)
अणु
	u32 mask = 0xFFFFFFFF;
	काष्ठा megasas_रेजिस्टर_set __iomem *regs;
	regs = instance->reg_set;
	instance->mask_पूर्णांकerrupts = 1;

	ग_लिखोl(mask, &regs->outbound_पूर्णांकr_mask);
	/* Dummy पढ़ोl to क्रमce pci flush */
	dev_info(&instance->pdev->dev, "%s is called outbound_intr_mask:0x%08x\n",
		 __func__, पढ़ोl(&regs->outbound_पूर्णांकr_mask));
पूर्ण

पूर्णांक
megasas_clear_पूर्णांकr_fusion(काष्ठा megasas_instance *instance)
अणु
	u32 status;
	काष्ठा megasas_रेजिस्टर_set __iomem *regs;
	regs = instance->reg_set;
	/*
	 * Check अगर it is our पूर्णांकerrupt
	 */
	status = megasas_पढ़ोl(instance,
			       &regs->outbound_पूर्णांकr_status);

	अगर (status & 1) अणु
		ग_लिखोl(status, &regs->outbound_पूर्णांकr_status);
		पढ़ोl(&regs->outbound_पूर्णांकr_status);
		वापस 1;
	पूर्ण
	अगर (!(status & MFI_FUSION_ENABLE_INTERRUPT_MASK))
		वापस 0;

	वापस 1;
पूर्ण

अटल अंतरभूत व्योम
megasas_sdev_busy_inc(काष्ठा megasas_instance *instance,
		      काष्ठा scsi_cmnd *scmd)
अणु
	अगर (instance->perf_mode == MR_BALANCED_PERF_MODE) अणु
		काष्ठा MR_PRIV_DEVICE *mr_device_priv_data =
			scmd->device->hostdata;
		atomic_inc(&mr_device_priv_data->sdev_priv_busy);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
megasas_sdev_busy_dec(काष्ठा megasas_instance *instance,
		      काष्ठा scsi_cmnd *scmd)
अणु
	अगर (instance->perf_mode == MR_BALANCED_PERF_MODE) अणु
		काष्ठा MR_PRIV_DEVICE *mr_device_priv_data =
			scmd->device->hostdata;
		atomic_dec(&mr_device_priv_data->sdev_priv_busy);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
megasas_sdev_busy_पढ़ो(काष्ठा megasas_instance *instance,
		       काष्ठा scsi_cmnd *scmd)
अणु
	अगर (instance->perf_mode == MR_BALANCED_PERF_MODE) अणु
		काष्ठा MR_PRIV_DEVICE *mr_device_priv_data =
			scmd->device->hostdata;
		वापस atomic_पढ़ो(&mr_device_priv_data->sdev_priv_busy);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * megasas_get_cmd_fusion -	Get a command from the मुक्त pool
 * @instance:		Adapter soft state
 * @blk_tag:		Command tag
 *
 * Returns a blk_tag indexed mpt frame
 */
अंतरभूत काष्ठा megasas_cmd_fusion *megasas_get_cmd_fusion(काष्ठा megasas_instance
						  *instance, u32 blk_tag)
अणु
	काष्ठा fusion_context *fusion;

	fusion = instance->ctrl_context;
	वापस fusion->cmd_list[blk_tag];
पूर्ण

/**
 * megasas_वापस_cmd_fusion -	Return a cmd to मुक्त command pool
 * @instance:		Adapter soft state
 * @cmd:		Command packet to be वापसed to मुक्त command pool
 */
अंतरभूत व्योम megasas_वापस_cmd_fusion(काष्ठा megasas_instance *instance,
	काष्ठा megasas_cmd_fusion *cmd)
अणु
	cmd->scmd = शून्य;
	स_रखो(cmd->io_request, 0, MEGA_MPI2_RAID_DEFAULT_IO_FRAME_SIZE);
	cmd->r1_alt_dev_handle = MR_DEVHANDLE_INVALID;
	cmd->cmd_completed = false;
पूर्ण

/**
 * megasas_ग_लिखो_64bit_req_desc -	PCI ग_लिखोs 64bit request descriptor
 * @instance:				Adapter soft state
 * @req_desc:				64bit Request descriptor
 */
अटल व्योम
megasas_ग_लिखो_64bit_req_desc(काष्ठा megasas_instance *instance,
		जोड़ MEGASAS_REQUEST_DESCRIPTOR_UNION *req_desc)
अणु
#अगर defined(ग_लिखोq) && defined(CONFIG_64BIT)
	u64 req_data = (((u64)le32_to_cpu(req_desc->u.high) << 32) |
		le32_to_cpu(req_desc->u.low));
	ग_लिखोq(req_data, &instance->reg_set->inbound_low_queue_port);
#अन्यथा
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&instance->hba_lock, flags);
	ग_लिखोl(le32_to_cpu(req_desc->u.low),
		&instance->reg_set->inbound_low_queue_port);
	ग_लिखोl(le32_to_cpu(req_desc->u.high),
		&instance->reg_set->inbound_high_queue_port);
	spin_unlock_irqrestore(&instance->hba_lock, flags);
#पूर्ण_अगर
पूर्ण

/**
 * megasas_fire_cmd_fusion -	Sends command to the FW
 * @instance:			Adapter soft state
 * @req_desc:			32bit or 64bit Request descriptor
 *
 * Perक्रमm PCI Write. AERO SERIES supports 32 bit Descriptor.
 * Prior to AERO_SERIES support 64 bit Descriptor.
 */
अटल व्योम
megasas_fire_cmd_fusion(काष्ठा megasas_instance *instance,
		जोड़ MEGASAS_REQUEST_DESCRIPTOR_UNION *req_desc)
अणु
	अगर (instance->atomic_desc_support)
		ग_लिखोl(le32_to_cpu(req_desc->u.low),
			&instance->reg_set->inbound_single_queue_port);
	अन्यथा
		megasas_ग_लिखो_64bit_req_desc(instance, req_desc);
पूर्ण

/**
 * megasas_fusion_update_can_queue -	Do all Adapter Queue depth related calculations here
 * @instance:		Adapter soft state
 * @fw_boot_context:	Whether this function called during probe or after OCR
 *
 * This function is only क्रम fusion controllers.
 * Update host can queue, अगर firmware करोwngrade max supported firmware commands.
 * Firmware upgrade हाल will be skiped because underlying firmware has
 * more resource than exposed to the OS.
 *
 */
अटल व्योम
megasas_fusion_update_can_queue(काष्ठा megasas_instance *instance, पूर्णांक fw_boot_context)
अणु
	u16 cur_max_fw_cmds = 0;
	u16 ldio_threshold = 0;

	/* ventura FW करोes not fill outbound_scratch_pad_2 with queue depth */
	अगर (instance->adapter_type < VENTURA_SERIES)
		cur_max_fw_cmds =
		megasas_पढ़ोl(instance,
			      &instance->reg_set->outbound_scratch_pad_2) & 0x00FFFF;

	अगर (dual_qdepth_disable || !cur_max_fw_cmds)
		cur_max_fw_cmds = instance->instancet->पढ़ो_fw_status_reg(instance) & 0x00FFFF;
	अन्यथा
		ldio_threshold =
			(instance->instancet->पढ़ो_fw_status_reg(instance) & 0x00FFFF) - MEGASAS_FUSION_IOCTL_CMDS;

	dev_info(&instance->pdev->dev,
		 "Current firmware supports maximum commands: %d\t LDIO threshold: %d\n",
		 cur_max_fw_cmds, ldio_threshold);

	अगर (fw_boot_context == OCR_CONTEXT) अणु
		cur_max_fw_cmds = cur_max_fw_cmds - 1;
		अगर (cur_max_fw_cmds < instance->max_fw_cmds) अणु
			instance->cur_can_queue =
				cur_max_fw_cmds - (MEGASAS_FUSION_INTERNAL_CMDS +
						MEGASAS_FUSION_IOCTL_CMDS);
			instance->host->can_queue = instance->cur_can_queue;
			instance->ldio_threshold = ldio_threshold;
		पूर्ण
	पूर्ण अन्यथा अणु
		instance->max_fw_cmds = cur_max_fw_cmds;
		instance->ldio_threshold = ldio_threshold;

		अगर (reset_devices)
			instance->max_fw_cmds = min(instance->max_fw_cmds,
						(u16)MEGASAS_KDUMP_QUEUE_DEPTH);
		/*
		* Reduce the max supported cmds by 1. This is to ensure that the
		* reply_q_sz (1 more than the max cmd that driver may send)
		* करोes not exceed max cmds that the FW can support
		*/
		instance->max_fw_cmds = instance->max_fw_cmds-1;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
megasas_get_msix_index(काष्ठा megasas_instance *instance,
		       काष्ठा scsi_cmnd *scmd,
		       काष्ठा megasas_cmd_fusion *cmd,
		       u8 data_arms)
अणु
	अगर (instance->perf_mode == MR_BALANCED_PERF_MODE &&
	    (megasas_sdev_busy_पढ़ो(instance, scmd) >
	     (data_arms * MR_DEVICE_HIGH_IOPS_DEPTH))) अणु
		cmd->request_desc->SCSIIO.MSIxIndex =
			mega_mod64((atomic64_add_वापस(1, &instance->high_iops_outstanding) /
					MR_HIGH_IOPS_BATCH_COUNT), instance->low_latency_index_start);
	पूर्ण अन्यथा अगर (instance->msix_load_balance) अणु
		cmd->request_desc->SCSIIO.MSIxIndex =
			(mega_mod64(atomic64_add_वापस(1, &instance->total_io_count),
				instance->msix_vectors));
	पूर्ण अन्यथा अगर (instance->host->nr_hw_queues > 1) अणु
		u32 tag = blk_mq_unique_tag(scmd->request);

		cmd->request_desc->SCSIIO.MSIxIndex = blk_mq_unique_tag_to_hwq(tag) +
			instance->low_latency_index_start;
	पूर्ण अन्यथा अणु
		cmd->request_desc->SCSIIO.MSIxIndex =
			instance->reply_map[raw_smp_processor_id()];
	पूर्ण
पूर्ण

/**
 * megasas_मुक्त_cmds_fusion -	Free all the cmds in the मुक्त cmd pool
 * @instance:		Adapter soft state
 */
व्योम
megasas_मुक्त_cmds_fusion(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक i;
	काष्ठा fusion_context *fusion = instance->ctrl_context;
	काष्ठा megasas_cmd_fusion *cmd;

	अगर (fusion->sense)
		dma_pool_मुक्त(fusion->sense_dma_pool, fusion->sense,
			      fusion->sense_phys_addr);

	/* SG */
	अगर (fusion->cmd_list) अणु
		क्रम (i = 0; i < instance->max_mpt_cmds; i++) अणु
			cmd = fusion->cmd_list[i];
			अगर (cmd) अणु
				अगर (cmd->sg_frame)
					dma_pool_मुक्त(fusion->sg_dma_pool,
						      cmd->sg_frame,
						      cmd->sg_frame_phys_addr);
			पूर्ण
			kमुक्त(cmd);
		पूर्ण
		kमुक्त(fusion->cmd_list);
	पूर्ण

	अगर (fusion->sg_dma_pool) अणु
		dma_pool_destroy(fusion->sg_dma_pool);
		fusion->sg_dma_pool = शून्य;
	पूर्ण
	अगर (fusion->sense_dma_pool) अणु
		dma_pool_destroy(fusion->sense_dma_pool);
		fusion->sense_dma_pool = शून्य;
	पूर्ण


	/* Reply Frame, Desc*/
	अगर (instance->is_rdpq)
		megasas_मुक्त_rdpq_fusion(instance);
	अन्यथा
		megasas_मुक्त_reply_fusion(instance);

	/* Request Frame, Desc*/
	अगर (fusion->req_frames_desc)
		dma_मुक्त_coherent(&instance->pdev->dev,
			fusion->request_alloc_sz, fusion->req_frames_desc,
			fusion->req_frames_desc_phys);
	अगर (fusion->io_request_frames)
		dma_pool_मुक्त(fusion->io_request_frames_pool,
			fusion->io_request_frames,
			fusion->io_request_frames_phys);
	अगर (fusion->io_request_frames_pool) अणु
		dma_pool_destroy(fusion->io_request_frames_pool);
		fusion->io_request_frames_pool = शून्य;
	पूर्ण
पूर्ण

/**
 * megasas_create_sg_sense_fusion -	Creates DMA pool क्रम cmd frames
 * @instance:			Adapter soft state
 *
 */
अटल पूर्णांक megasas_create_sg_sense_fusion(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक i;
	u16 max_cmd;
	काष्ठा fusion_context *fusion;
	काष्ठा megasas_cmd_fusion *cmd;
	पूर्णांक sense_sz;
	u32 offset;

	fusion = instance->ctrl_context;
	max_cmd = instance->max_fw_cmds;
	sense_sz = instance->max_mpt_cmds * SCSI_SENSE_BUFFERSIZE;

	fusion->sg_dma_pool =
			dma_pool_create("mr_sg", &instance->pdev->dev,
				instance->max_chain_frame_sz,
				MR_DEFAULT_NVME_PAGE_SIZE, 0);
	/* SCSI_SENSE_BUFFERSIZE  = 96 bytes */
	fusion->sense_dma_pool =
			dma_pool_create("mr_sense", &instance->pdev->dev,
				sense_sz, 64, 0);

	अगर (!fusion->sense_dma_pool || !fusion->sg_dma_pool) अणु
		dev_err(&instance->pdev->dev,
			"Failed from %s %d\n",  __func__, __LINE__);
		वापस -ENOMEM;
	पूर्ण

	fusion->sense = dma_pool_alloc(fusion->sense_dma_pool,
				       GFP_KERNEL, &fusion->sense_phys_addr);
	अगर (!fusion->sense) अणु
		dev_err(&instance->pdev->dev,
			"failed from %s %d\n",  __func__, __LINE__);
		वापस -ENOMEM;
	पूर्ण

	/* sense buffer, request frame and reply desc pool requires to be in
	 * same 4 gb region. Below function will check this.
	 * In हाल of failure, new pci pool will be created with updated
	 * alignment.
	 * Older allocation and pool will be destroyed.
	 * Alignment will be used such a way that next allocation अगर success,
	 * will always meet same 4gb region requirement.
	 * Actual requirement is not alignment, but we need start and end of
	 * DMA address must have same upper 32 bit address.
	 */

	अगर (!megasas_check_same_4gb_region(instance, fusion->sense_phys_addr,
					   sense_sz)) अणु
		dma_pool_मुक्त(fusion->sense_dma_pool, fusion->sense,
			      fusion->sense_phys_addr);
		fusion->sense = शून्य;
		dma_pool_destroy(fusion->sense_dma_pool);

		fusion->sense_dma_pool =
			dma_pool_create("mr_sense_align", &instance->pdev->dev,
					sense_sz, roundup_घात_of_two(sense_sz),
					0);
		अगर (!fusion->sense_dma_pool) अणु
			dev_err(&instance->pdev->dev,
				"Failed from %s %d\n",  __func__, __LINE__);
			वापस -ENOMEM;
		पूर्ण
		fusion->sense = dma_pool_alloc(fusion->sense_dma_pool,
					       GFP_KERNEL,
					       &fusion->sense_phys_addr);
		अगर (!fusion->sense) अणु
			dev_err(&instance->pdev->dev,
				"failed from %s %d\n",  __func__, __LINE__);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/*
	 * Allocate and attach a frame to each of the commands in cmd_list
	 */
	क्रम (i = 0; i < max_cmd; i++) अणु
		cmd = fusion->cmd_list[i];
		cmd->sg_frame = dma_pool_alloc(fusion->sg_dma_pool,
					GFP_KERNEL, &cmd->sg_frame_phys_addr);

		offset = SCSI_SENSE_BUFFERSIZE * i;
		cmd->sense = (u8 *)fusion->sense + offset;
		cmd->sense_phys_addr = fusion->sense_phys_addr + offset;

		अगर (!cmd->sg_frame) अणु
			dev_err(&instance->pdev->dev,
				"Failed from %s %d\n",  __func__, __LINE__);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* create sense buffer क्रम the raid 1/10 fp */
	क्रम (i = max_cmd; i < instance->max_mpt_cmds; i++) अणु
		cmd = fusion->cmd_list[i];
		offset = SCSI_SENSE_BUFFERSIZE * i;
		cmd->sense = (u8 *)fusion->sense + offset;
		cmd->sense_phys_addr = fusion->sense_phys_addr + offset;

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
megasas_alloc_cmdlist_fusion(काष्ठा megasas_instance *instance)
अणु
	u32 max_mpt_cmd, i, j;
	काष्ठा fusion_context *fusion;

	fusion = instance->ctrl_context;

	max_mpt_cmd = instance->max_mpt_cmds;

	/*
	 * fusion->cmd_list is an array of काष्ठा megasas_cmd_fusion poपूर्णांकers.
	 * Allocate the dynamic array first and then allocate inभागidual
	 * commands.
	 */
	fusion->cmd_list =
		kसुस्मृति(max_mpt_cmd, माप(काष्ठा megasas_cmd_fusion *),
			GFP_KERNEL);
	अगर (!fusion->cmd_list) अणु
		dev_err(&instance->pdev->dev,
			"Failed from %s %d\n",  __func__, __LINE__);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < max_mpt_cmd; i++) अणु
		fusion->cmd_list[i] = kzalloc(माप(काष्ठा megasas_cmd_fusion),
					      GFP_KERNEL);
		अगर (!fusion->cmd_list[i]) अणु
			क्रम (j = 0; j < i; j++)
				kमुक्त(fusion->cmd_list[j]);
			kमुक्त(fusion->cmd_list);
			dev_err(&instance->pdev->dev,
				"Failed from %s %d\n",  __func__, __LINE__);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
megasas_alloc_request_fusion(काष्ठा megasas_instance *instance)
अणु
	काष्ठा fusion_context *fusion;

	fusion = instance->ctrl_context;

retry_alloc:
	fusion->io_request_frames_pool =
			dma_pool_create("mr_ioreq", &instance->pdev->dev,
				fusion->io_frames_alloc_sz, 16, 0);

	अगर (!fusion->io_request_frames_pool) अणु
		dev_err(&instance->pdev->dev,
			"Failed from %s %d\n",  __func__, __LINE__);
		वापस -ENOMEM;
	पूर्ण

	fusion->io_request_frames =
			dma_pool_alloc(fusion->io_request_frames_pool,
				GFP_KERNEL | __GFP_NOWARN,
				&fusion->io_request_frames_phys);
	अगर (!fusion->io_request_frames) अणु
		अगर (instance->max_fw_cmds >= (MEGASAS_REDUCE_QD_COUNT * 2)) अणु
			instance->max_fw_cmds -= MEGASAS_REDUCE_QD_COUNT;
			dma_pool_destroy(fusion->io_request_frames_pool);
			megasas_configure_queue_sizes(instance);
			जाओ retry_alloc;
		पूर्ण अन्यथा अणु
			dev_err(&instance->pdev->dev,
				"Failed from %s %d\n",  __func__, __LINE__);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (!megasas_check_same_4gb_region(instance,
					   fusion->io_request_frames_phys,
					   fusion->io_frames_alloc_sz)) अणु
		dma_pool_मुक्त(fusion->io_request_frames_pool,
			      fusion->io_request_frames,
			      fusion->io_request_frames_phys);
		fusion->io_request_frames = शून्य;
		dma_pool_destroy(fusion->io_request_frames_pool);

		fusion->io_request_frames_pool =
			dma_pool_create("mr_ioreq_align",
					&instance->pdev->dev,
					fusion->io_frames_alloc_sz,
					roundup_घात_of_two(fusion->io_frames_alloc_sz),
					0);

		अगर (!fusion->io_request_frames_pool) अणु
			dev_err(&instance->pdev->dev,
				"Failed from %s %d\n",  __func__, __LINE__);
			वापस -ENOMEM;
		पूर्ण

		fusion->io_request_frames =
			dma_pool_alloc(fusion->io_request_frames_pool,
				       GFP_KERNEL | __GFP_NOWARN,
				       &fusion->io_request_frames_phys);

		अगर (!fusion->io_request_frames) अणु
			dev_err(&instance->pdev->dev,
				"Failed from %s %d\n",  __func__, __LINE__);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	fusion->req_frames_desc =
		dma_alloc_coherent(&instance->pdev->dev,
				   fusion->request_alloc_sz,
				   &fusion->req_frames_desc_phys, GFP_KERNEL);
	अगर (!fusion->req_frames_desc) अणु
		dev_err(&instance->pdev->dev,
			"Failed from %s %d\n",  __func__, __LINE__);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
megasas_alloc_reply_fusion(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक i, count;
	काष्ठा fusion_context *fusion;
	जोड़ MPI2_REPLY_DESCRIPTORS_UNION *reply_desc;
	fusion = instance->ctrl_context;

	count = instance->msix_vectors > 0 ? instance->msix_vectors : 1;
	count += instance->iopoll_q_count;

	fusion->reply_frames_desc_pool =
			dma_pool_create("mr_reply", &instance->pdev->dev,
				fusion->reply_alloc_sz * count, 16, 0);

	अगर (!fusion->reply_frames_desc_pool) अणु
		dev_err(&instance->pdev->dev,
			"Failed from %s %d\n",  __func__, __LINE__);
		वापस -ENOMEM;
	पूर्ण

	fusion->reply_frames_desc[0] =
		dma_pool_alloc(fusion->reply_frames_desc_pool,
			GFP_KERNEL, &fusion->reply_frames_desc_phys[0]);
	अगर (!fusion->reply_frames_desc[0]) अणु
		dev_err(&instance->pdev->dev,
			"Failed from %s %d\n",  __func__, __LINE__);
		वापस -ENOMEM;
	पूर्ण

	अगर (!megasas_check_same_4gb_region(instance,
					   fusion->reply_frames_desc_phys[0],
					   (fusion->reply_alloc_sz * count))) अणु
		dma_pool_मुक्त(fusion->reply_frames_desc_pool,
			      fusion->reply_frames_desc[0],
			      fusion->reply_frames_desc_phys[0]);
		fusion->reply_frames_desc[0] = शून्य;
		dma_pool_destroy(fusion->reply_frames_desc_pool);

		fusion->reply_frames_desc_pool =
			dma_pool_create("mr_reply_align",
					&instance->pdev->dev,
					fusion->reply_alloc_sz * count,
					roundup_घात_of_two(fusion->reply_alloc_sz * count),
					0);

		अगर (!fusion->reply_frames_desc_pool) अणु
			dev_err(&instance->pdev->dev,
				"Failed from %s %d\n",  __func__, __LINE__);
			वापस -ENOMEM;
		पूर्ण

		fusion->reply_frames_desc[0] =
			dma_pool_alloc(fusion->reply_frames_desc_pool,
				       GFP_KERNEL,
				       &fusion->reply_frames_desc_phys[0]);

		अगर (!fusion->reply_frames_desc[0]) अणु
			dev_err(&instance->pdev->dev,
				"Failed from %s %d\n",  __func__, __LINE__);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	reply_desc = fusion->reply_frames_desc[0];
	क्रम (i = 0; i < fusion->reply_q_depth * count; i++, reply_desc++)
		reply_desc->Words = cpu_to_le64(ULदीर्घ_उच्च);

	/* This is not a rdpq mode, but driver still populate
	 * reply_frame_desc array to use same msix index in ISR path.
	 */
	क्रम (i = 0; i < (count - 1); i++)
		fusion->reply_frames_desc[i + 1] =
			fusion->reply_frames_desc[i] +
			(fusion->reply_alloc_sz)/माप(जोड़ MPI2_REPLY_DESCRIPTORS_UNION);

	वापस 0;
पूर्ण

अटल पूर्णांक
megasas_alloc_rdpq_fusion(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक i, j, k, msix_count;
	काष्ठा fusion_context *fusion;
	जोड़ MPI2_REPLY_DESCRIPTORS_UNION *reply_desc;
	जोड़ MPI2_REPLY_DESCRIPTORS_UNION *rdpq_chunk_virt[RDPQ_MAX_CHUNK_COUNT];
	dma_addr_t rdpq_chunk_phys[RDPQ_MAX_CHUNK_COUNT];
	u8 dma_alloc_count, असल_index;
	u32 chunk_size, array_size, offset;

	fusion = instance->ctrl_context;
	chunk_size = fusion->reply_alloc_sz * RDPQ_MAX_INDEX_IN_ONE_CHUNK;
	array_size = माप(काष्ठा MPI2_IOC_INIT_RDPQ_ARRAY_ENTRY) *
		     MAX_MSIX_QUEUES_FUSION;

	fusion->rdpq_virt = dma_alloc_coherent(&instance->pdev->dev,
					       array_size, &fusion->rdpq_phys,
					       GFP_KERNEL);
	अगर (!fusion->rdpq_virt) अणु
		dev_err(&instance->pdev->dev,
			"Failed from %s %d\n",  __func__, __LINE__);
		वापस -ENOMEM;
	पूर्ण

	msix_count = instance->msix_vectors > 0 ? instance->msix_vectors : 1;
	msix_count += instance->iopoll_q_count;

	fusion->reply_frames_desc_pool = dma_pool_create("mr_rdpq",
							 &instance->pdev->dev,
							 chunk_size, 16, 0);
	fusion->reply_frames_desc_pool_align =
				dma_pool_create("mr_rdpq_align",
						&instance->pdev->dev,
						chunk_size,
						roundup_घात_of_two(chunk_size),
						0);

	अगर (!fusion->reply_frames_desc_pool ||
	    !fusion->reply_frames_desc_pool_align) अणु
		dev_err(&instance->pdev->dev,
			"Failed from %s %d\n",  __func__, __LINE__);
		वापस -ENOMEM;
	पूर्ण

/*
 * For INVADER_SERIES each set of 8 reply queues(0-7, 8-15, ..) and
 * VENTURA_SERIES each set of 16 reply queues(0-15, 16-31, ..) should be
 * within 4GB boundary and also reply queues in a set must have same
 * upper 32-bits in their memory address. so here driver is allocating the
 * DMA'able memory क्रम reply queues according. Driver uses limitation of
 * VENTURA_SERIES to manage INVADER_SERIES as well.
 */
	dma_alloc_count = DIV_ROUND_UP(msix_count, RDPQ_MAX_INDEX_IN_ONE_CHUNK);

	क्रम (i = 0; i < dma_alloc_count; i++) अणु
		rdpq_chunk_virt[i] =
			dma_pool_alloc(fusion->reply_frames_desc_pool,
				       GFP_KERNEL, &rdpq_chunk_phys[i]);
		अगर (!rdpq_chunk_virt[i]) अणु
			dev_err(&instance->pdev->dev,
				"Failed from %s %d\n",  __func__, __LINE__);
			वापस -ENOMEM;
		पूर्ण
		/* reply desc pool requires to be in same 4 gb region.
		 * Below function will check this.
		 * In हाल of failure, new pci pool will be created with updated
		 * alignment.
		 * For RDPQ buffers, driver always allocate two separate pci pool.
		 * Alignment will be used such a way that next allocation अगर
		 * success, will always meet same 4gb region requirement.
		 * rdpq_tracker keep track of each buffer's physical,
		 * भव address and pci pool descriptor. It will help driver
		 * जबतक मुक्तing the resources.
		 *
		 */
		अगर (!megasas_check_same_4gb_region(instance, rdpq_chunk_phys[i],
						   chunk_size)) अणु
			dma_pool_मुक्त(fusion->reply_frames_desc_pool,
				      rdpq_chunk_virt[i],
				      rdpq_chunk_phys[i]);

			rdpq_chunk_virt[i] =
				dma_pool_alloc(fusion->reply_frames_desc_pool_align,
					       GFP_KERNEL, &rdpq_chunk_phys[i]);
			अगर (!rdpq_chunk_virt[i]) अणु
				dev_err(&instance->pdev->dev,
					"Failed from %s %d\n",
					__func__, __LINE__);
				वापस -ENOMEM;
			पूर्ण
			fusion->rdpq_tracker[i].dma_pool_ptr =
					fusion->reply_frames_desc_pool_align;
		पूर्ण अन्यथा अणु
			fusion->rdpq_tracker[i].dma_pool_ptr =
					fusion->reply_frames_desc_pool;
		पूर्ण

		fusion->rdpq_tracker[i].pool_entry_phys = rdpq_chunk_phys[i];
		fusion->rdpq_tracker[i].pool_entry_virt = rdpq_chunk_virt[i];
	पूर्ण

	क्रम (k = 0; k < dma_alloc_count; k++) अणु
		क्रम (i = 0; i < RDPQ_MAX_INDEX_IN_ONE_CHUNK; i++) अणु
			असल_index = (k * RDPQ_MAX_INDEX_IN_ONE_CHUNK) + i;

			अगर (असल_index == msix_count)
				अवरोध;
			offset = fusion->reply_alloc_sz * i;
			fusion->rdpq_virt[असल_index].RDPQBaseAddress =
					cpu_to_le64(rdpq_chunk_phys[k] + offset);
			fusion->reply_frames_desc_phys[असल_index] =
					rdpq_chunk_phys[k] + offset;
			fusion->reply_frames_desc[असल_index] =
					(जोड़ MPI2_REPLY_DESCRIPTORS_UNION *)((u8 *)rdpq_chunk_virt[k] + offset);

			reply_desc = fusion->reply_frames_desc[असल_index];
			क्रम (j = 0; j < fusion->reply_q_depth; j++, reply_desc++)
				reply_desc->Words = ULदीर्घ_उच्च;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
megasas_मुक्त_rdpq_fusion(काष्ठा megasas_instance *instance) अणु

	पूर्णांक i;
	काष्ठा fusion_context *fusion;

	fusion = instance->ctrl_context;

	क्रम (i = 0; i < RDPQ_MAX_CHUNK_COUNT; i++) अणु
		अगर (fusion->rdpq_tracker[i].pool_entry_virt)
			dma_pool_मुक्त(fusion->rdpq_tracker[i].dma_pool_ptr,
				      fusion->rdpq_tracker[i].pool_entry_virt,
				      fusion->rdpq_tracker[i].pool_entry_phys);

	पूर्ण

	dma_pool_destroy(fusion->reply_frames_desc_pool);
	dma_pool_destroy(fusion->reply_frames_desc_pool_align);

	अगर (fusion->rdpq_virt)
		dma_मुक्त_coherent(&instance->pdev->dev,
			माप(काष्ठा MPI2_IOC_INIT_RDPQ_ARRAY_ENTRY) * MAX_MSIX_QUEUES_FUSION,
			fusion->rdpq_virt, fusion->rdpq_phys);
पूर्ण

अटल व्योम
megasas_मुक्त_reply_fusion(काष्ठा megasas_instance *instance) अणु

	काष्ठा fusion_context *fusion;

	fusion = instance->ctrl_context;

	अगर (fusion->reply_frames_desc[0])
		dma_pool_मुक्त(fusion->reply_frames_desc_pool,
			fusion->reply_frames_desc[0],
			fusion->reply_frames_desc_phys[0]);

	dma_pool_destroy(fusion->reply_frames_desc_pool);

पूर्ण


/**
 * megasas_alloc_cmds_fusion -	Allocates the command packets
 * @instance:		Adapter soft state
 *
 *
 * Each frame has a 32-bit field called context. This context is used to get
 * back the megasas_cmd_fusion from the frame when a frame माला_लो completed
 * In this driver, the 32 bit values are the indices पूर्णांकo an array cmd_list.
 * This array is used only to look up the megasas_cmd_fusion given the context.
 * The मुक्त commands themselves are मुख्यtained in a linked list called cmd_pool.
 *
 * cmds are क्रमmed in the io_request and sg_frame members of the
 * megasas_cmd_fusion. The context field is used to get a request descriptor
 * and is used as SMID of the cmd.
 * SMID value range is from 1 to max_fw_cmds.
 */
अटल पूर्णांक
megasas_alloc_cmds_fusion(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक i;
	काष्ठा fusion_context *fusion;
	काष्ठा megasas_cmd_fusion *cmd;
	u32 offset;
	dma_addr_t io_req_base_phys;
	u8 *io_req_base;


	fusion = instance->ctrl_context;

	अगर (megasas_alloc_request_fusion(instance))
		जाओ fail_निकास;

	अगर (instance->is_rdpq) अणु
		अगर (megasas_alloc_rdpq_fusion(instance))
			जाओ fail_निकास;
	पूर्ण अन्यथा
		अगर (megasas_alloc_reply_fusion(instance))
			जाओ fail_निकास;

	अगर (megasas_alloc_cmdlist_fusion(instance))
		जाओ fail_निकास;

	/* The first 256 bytes (SMID 0) is not used. Don't add to the cmd list */
	io_req_base = fusion->io_request_frames + MEGA_MPI2_RAID_DEFAULT_IO_FRAME_SIZE;
	io_req_base_phys = fusion->io_request_frames_phys + MEGA_MPI2_RAID_DEFAULT_IO_FRAME_SIZE;

	/*
	 * Add all the commands to command pool (fusion->cmd_pool)
	 */

	/* SMID 0 is reserved. Set SMID/index from 1 */
	क्रम (i = 0; i < instance->max_mpt_cmds; i++) अणु
		cmd = fusion->cmd_list[i];
		offset = MEGA_MPI2_RAID_DEFAULT_IO_FRAME_SIZE * i;
		स_रखो(cmd, 0, माप(काष्ठा megasas_cmd_fusion));
		cmd->index = i + 1;
		cmd->scmd = शून्य;
		cmd->sync_cmd_idx =
		(i >= instance->max_scsi_cmds && i < instance->max_fw_cmds) ?
				(i - instance->max_scsi_cmds) :
				(u32)अच_दीर्घ_उच्च; /* Set to Invalid */
		cmd->instance = instance;
		cmd->io_request =
			(काष्ठा MPI2_RAID_SCSI_IO_REQUEST *)
		  (io_req_base + offset);
		स_रखो(cmd->io_request, 0,
		       माप(काष्ठा MPI2_RAID_SCSI_IO_REQUEST));
		cmd->io_request_phys_addr = io_req_base_phys + offset;
		cmd->r1_alt_dev_handle = MR_DEVHANDLE_INVALID;
	पूर्ण

	अगर (megasas_create_sg_sense_fusion(instance))
		जाओ fail_निकास;

	वापस 0;

fail_निकास:
	megasas_मुक्त_cmds_fusion(instance);
	वापस -ENOMEM;
पूर्ण

/**
 * रुको_and_poll -	Issues a polling command
 * @instance:			Adapter soft state
 * @cmd:			Command packet to be issued
 * @seconds:			Maximum poll समय
 *
 * For polling, MFI requires the cmd_status to be set to 0xFF beक्रमe posting.
 */
पूर्णांक
रुको_and_poll(काष्ठा megasas_instance *instance, काष्ठा megasas_cmd *cmd,
	पूर्णांक seconds)
अणु
	पूर्णांक i;
	काष्ठा megasas_header *frame_hdr = &cmd->frame->hdr;
	u32 status_reg;

	u32 msecs = seconds * 1000;

	/*
	 * Wait क्रम cmd_status to change
	 */
	क्रम (i = 0; (i < msecs) && (frame_hdr->cmd_status == 0xff); i += 20) अणु
		rmb();
		msleep(20);
		अगर (!(i % 5000)) अणु
			status_reg = instance->instancet->पढ़ो_fw_status_reg(instance)
					& MFI_STATE_MASK;
			अगर (status_reg == MFI_STATE_FAULT)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (frame_hdr->cmd_status == MFI_STAT_INVALID_STATUS)
		वापस DCMD_TIMEOUT;
	अन्यथा अगर (frame_hdr->cmd_status == MFI_STAT_OK)
		वापस DCMD_SUCCESS;
	अन्यथा
		वापस DCMD_FAILED;
पूर्ण

/**
 * megasas_ioc_init_fusion -	Initializes the FW
 * @instance:		Adapter soft state
 *
 * Issues the IOC Init cmd
 */
पूर्णांक
megasas_ioc_init_fusion(काष्ठा megasas_instance *instance)
अणु
	काष्ठा megasas_init_frame *init_frame;
	काष्ठा MPI2_IOC_INIT_REQUEST *IOCInitMessage = शून्य;
	dma_addr_t	ioc_init_handle;
	काष्ठा megasas_cmd *cmd;
	u8 ret, cur_rdpq_mode;
	काष्ठा fusion_context *fusion;
	जोड़ MEGASAS_REQUEST_DESCRIPTOR_UNION req_desc;
	पूर्णांक i;
	काष्ठा megasas_header *frame_hdr;
	स्थिर अक्षर *sys_info;
	MFI_CAPABILITIES *drv_ops;
	u32 scratch_pad_1;
	kसमय_प्रकार समय;
	bool cur_fw_64bit_dma_capable;
	bool cur_पूर्णांकr_coalescing;

	fusion = instance->ctrl_context;

	ioc_init_handle = fusion->ioc_init_request_phys;
	IOCInitMessage = fusion->ioc_init_request;

	cmd = fusion->ioc_init_cmd;

	scratch_pad_1 = megasas_पढ़ोl
		(instance, &instance->reg_set->outbound_scratch_pad_1);

	cur_rdpq_mode = (scratch_pad_1 & MR_RDPQ_MODE_OFFSET) ? 1 : 0;

	अगर (instance->adapter_type == INVADER_SERIES) अणु
		cur_fw_64bit_dma_capable =
			(scratch_pad_1 & MR_CAN_HANDLE_64_BIT_DMA_OFFSET) ? true : false;

		अगर (instance->consistent_mask_64bit && !cur_fw_64bit_dma_capable) अणु
			dev_err(&instance->pdev->dev, "Driver was operating on 64bit "
				"DMA mask, but upcoming FW does not support 64bit DMA mask\n");
			megaraid_sas_समाप्त_hba(instance);
			ret = 1;
			जाओ fail_fw_init;
		पूर्ण
	पूर्ण

	अगर (instance->is_rdpq && !cur_rdpq_mode) अणु
		dev_err(&instance->pdev->dev, "Firmware downgrade *NOT SUPPORTED*"
			" from RDPQ mode to non RDPQ mode\n");
		ret = 1;
		जाओ fail_fw_init;
	पूर्ण

	cur_पूर्णांकr_coalescing = (scratch_pad_1 & MR_INTR_COALESCING_SUPPORT_OFFSET) ?
							true : false;

	अगर ((instance->low_latency_index_start ==
		MR_HIGH_IOPS_QUEUE_COUNT) && cur_पूर्णांकr_coalescing)
		instance->perf_mode = MR_BALANCED_PERF_MODE;

	dev_info(&instance->pdev->dev, "Performance mode :%s (latency index = %d)\n",
		MEGASAS_PERF_MODE_2STR(instance->perf_mode),
		instance->low_latency_index_start);

	instance->fw_sync_cache_support = (scratch_pad_1 &
		MR_CAN_HANDLE_SYNC_CACHE_OFFSET) ? 1 : 0;
	dev_info(&instance->pdev->dev, "FW supports sync cache\t: %s\n",
		 instance->fw_sync_cache_support ? "Yes" : "No");

	स_रखो(IOCInitMessage, 0, माप(काष्ठा MPI2_IOC_INIT_REQUEST));

	IOCInitMessage->Function = MPI2_FUNCTION_IOC_INIT;
	IOCInitMessage->WhoInit	= MPI2_WHOINIT_HOST_DRIVER;
	IOCInitMessage->MsgVersion = cpu_to_le16(MPI2_VERSION);
	IOCInitMessage->HeaderVersion = cpu_to_le16(MPI2_HEADER_VERSION);
	IOCInitMessage->SystemRequestFrameSize = cpu_to_le16(MEGA_MPI2_RAID_DEFAULT_IO_FRAME_SIZE / 4);

	IOCInitMessage->ReplyDescriptorPostQueueDepth = cpu_to_le16(fusion->reply_q_depth);
	IOCInitMessage->ReplyDescriptorPostQueueAddress = instance->is_rdpq ?
			cpu_to_le64(fusion->rdpq_phys) :
			cpu_to_le64(fusion->reply_frames_desc_phys[0]);
	IOCInitMessage->MsgFlags = instance->is_rdpq ?
			MPI2_IOCINIT_MSGFLAG_RDPQ_ARRAY_MODE : 0;
	IOCInitMessage->SystemRequestFrameBaseAddress = cpu_to_le64(fusion->io_request_frames_phys);
	IOCInitMessage->SenseBufferAddressHigh = cpu_to_le32(upper_32_bits(fusion->sense_phys_addr));
	IOCInitMessage->HostMSIxVectors = instance->msix_vectors + instance->iopoll_q_count;
	IOCInitMessage->HostPageSize = MR_DEFAULT_NVME_PAGE_SHIFT;

	समय = kसमय_get_real();
	/* Convert to milliseconds as per FW requirement */
	IOCInitMessage->TimeStamp = cpu_to_le64(kसमय_प्रकारo_ms(समय));

	init_frame = (काष्ठा megasas_init_frame *)cmd->frame;
	स_रखो(init_frame, 0, IOC_INIT_FRAME_SIZE);

	frame_hdr = &cmd->frame->hdr;
	frame_hdr->cmd_status = 0xFF;
	frame_hdr->flags |= cpu_to_le16(MFI_FRAME_DONT_POST_IN_REPLY_QUEUE);

	init_frame->cmd	= MFI_CMD_INIT;
	init_frame->cmd_status = 0xFF;

	drv_ops = (MFI_CAPABILITIES *) &(init_frame->driver_operations);

	/* driver support Extended MSIX */
	अगर (instance->adapter_type >= INVADER_SERIES)
		drv_ops->mfi_capabilities.support_additional_msix = 1;
	/* driver supports HA / Remote LUN over Fast Path पूर्णांकerface */
	drv_ops->mfi_capabilities.support_fp_remote_lun = 1;

	drv_ops->mfi_capabilities.support_max_255lds = 1;
	drv_ops->mfi_capabilities.support_ndrive_r1_lb = 1;
	drv_ops->mfi_capabilities.security_protocol_cmds_fw = 1;

	अगर (instance->max_chain_frame_sz > MEGASAS_CHAIN_FRAME_SZ_MIN)
		drv_ops->mfi_capabilities.support_ext_io_size = 1;

	drv_ops->mfi_capabilities.support_fp_rlbypass = 1;
	अगर (!dual_qdepth_disable)
		drv_ops->mfi_capabilities.support_ext_queue_depth = 1;

	drv_ops->mfi_capabilities.support_qd_throttling = 1;
	drv_ops->mfi_capabilities.support_pd_map_target_id = 1;
	drv_ops->mfi_capabilities.support_nvme_passthru = 1;
	drv_ops->mfi_capabilities.support_fw_exposed_dev_list = 1;

	अगर (instance->consistent_mask_64bit)
		drv_ops->mfi_capabilities.support_64bit_mode = 1;

	/* Convert capability to LE32 */
	cpu_to_le32s((u32 *)&init_frame->driver_operations.mfi_capabilities);

	sys_info = dmi_get_प्रणाली_info(DMI_PRODUCT_UUID);
	अगर (instance->प्रणाली_info_buf && sys_info) अणु
		स_नकल(instance->प्रणाली_info_buf->प्रणालीId, sys_info,
			म_माप(sys_info) > 64 ? 64 : म_माप(sys_info));
		instance->प्रणाली_info_buf->प्रणालीIdLength =
			म_माप(sys_info) > 64 ? 64 : म_माप(sys_info);
		init_frame->प्रणाली_info_lo = cpu_to_le32(lower_32_bits(instance->प्रणाली_info_h));
		init_frame->प्रणाली_info_hi = cpu_to_le32(upper_32_bits(instance->प्रणाली_info_h));
	पूर्ण

	init_frame->queue_info_new_phys_addr_hi =
		cpu_to_le32(upper_32_bits(ioc_init_handle));
	init_frame->queue_info_new_phys_addr_lo =
		cpu_to_le32(lower_32_bits(ioc_init_handle));
	init_frame->data_xfer_len = cpu_to_le32(माप(काष्ठा MPI2_IOC_INIT_REQUEST));

	/*
	 * Each bit in replyqueue_mask represents one group of MSI-x vectors
	 * (each group has 8 vectors)
	 */
	चयन (instance->perf_mode) अणु
	हाल MR_BALANCED_PERF_MODE:
		init_frame->replyqueue_mask =
		       cpu_to_le16(~(~0 << instance->low_latency_index_start/8));
		अवरोध;
	हाल MR_IOPS_PERF_MODE:
		init_frame->replyqueue_mask =
		       cpu_to_le16(~(~0 << instance->msix_vectors/8));
		अवरोध;
	पूर्ण


	req_desc.u.low = cpu_to_le32(lower_32_bits(cmd->frame_phys_addr));
	req_desc.u.high = cpu_to_le32(upper_32_bits(cmd->frame_phys_addr));
	req_desc.MFAIo.RequestFlags =
		(MEGASAS_REQ_DESCRIPT_FLAGS_MFA <<
		MEGASAS_REQ_DESCRIPT_FLAGS_TYPE_SHIFT);

	/*
	 * disable the पूर्णांकr beक्रमe firing the init frame
	 */
	instance->instancet->disable_पूर्णांकr(instance);

	क्रम (i = 0; i < (10 * 1000); i += 20) अणु
		अगर (megasas_पढ़ोl(instance, &instance->reg_set->करोorbell) & 1)
			msleep(20);
		अन्यथा
			अवरोध;
	पूर्ण

	/* For AERO also, IOC_INIT requires 64 bit descriptor ग_लिखो */
	megasas_ग_लिखो_64bit_req_desc(instance, &req_desc);

	रुको_and_poll(instance, cmd, MFI_IO_TIMEOUT_SECS);

	frame_hdr = &cmd->frame->hdr;
	अगर (frame_hdr->cmd_status != 0) अणु
		ret = 1;
		जाओ fail_fw_init;
	पूर्ण

	अगर (instance->adapter_type >= AERO_SERIES) अणु
		scratch_pad_1 = megasas_पढ़ोl
			(instance, &instance->reg_set->outbound_scratch_pad_1);

		instance->atomic_desc_support =
			(scratch_pad_1 & MR_ATOMIC_DESCRIPTOR_SUPPORT_OFFSET) ? 1 : 0;

		dev_info(&instance->pdev->dev, "FW supports atomic descriptor\t: %s\n",
			instance->atomic_desc_support ? "Yes" : "No");
	पूर्ण

	वापस 0;

fail_fw_init:
	dev_err(&instance->pdev->dev,
		"Init cmd return status FAILED for SCSI host %d\n",
		instance->host->host_no);

	वापस ret;
पूर्ण

/**
 * megasas_sync_pd_seq_num -	JBOD SEQ MAP
 * @instance:		Adapter soft state
 * @pend:		set to 1, अगर it is pended jbod map.
 *
 * Issue Jbod map to the firmware. If it is pended command,
 * issue command and वापस. If it is first instance of jbod map
 * issue and receive command.
 */
पूर्णांक
megasas_sync_pd_seq_num(काष्ठा megasas_instance *instance, bool pend) अणु
	पूर्णांक ret = 0;
	माप_प्रकार pd_seq_map_sz;
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_dcmd_frame *dcmd;
	काष्ठा fusion_context *fusion = instance->ctrl_context;
	काष्ठा MR_PD_CFG_SEQ_NUM_SYNC *pd_sync;
	dma_addr_t pd_seq_h;

	pd_sync = (व्योम *)fusion->pd_seq_sync[(instance->pd_seq_map_id & 1)];
	pd_seq_h = fusion->pd_seq_phys[(instance->pd_seq_map_id & 1)];
	pd_seq_map_sz = काष्ठा_size(pd_sync, seq, MAX_PHYSICAL_DEVICES - 1);

	cmd = megasas_get_cmd(instance);
	अगर (!cmd) अणु
		dev_err(&instance->pdev->dev,
			"Could not get mfi cmd. Fail from %s %d\n",
			__func__, __LINE__);
		वापस -ENOMEM;
	पूर्ण

	dcmd = &cmd->frame->dcmd;

	स_रखो(pd_sync, 0, pd_seq_map_sz);
	स_रखो(dcmd->mbox.b, 0, MFI_MBOX_SIZE);

	अगर (pend) अणु
		dcmd->mbox.b[0] = MEGASAS_DCMD_MBOX_PEND_FLAG;
		dcmd->flags = MFI_FRAME_सूची_WRITE;
		instance->jbod_seq_cmd = cmd;
	पूर्ण अन्यथा अणु
		dcmd->flags = MFI_FRAME_सूची_READ;
	पूर्ण

	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = 0xFF;
	dcmd->sge_count = 1;
	dcmd->समयout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len = cpu_to_le32(pd_seq_map_sz);
	dcmd->opcode = cpu_to_le32(MR_DCMD_SYSTEM_PD_MAP_GET_INFO);

	megasas_set_dma_settings(instance, dcmd, pd_seq_h, pd_seq_map_sz);

	अगर (pend) अणु
		instance->instancet->issue_dcmd(instance, cmd);
		वापस 0;
	पूर्ण

	/* Below code is only क्रम non pended DCMD */
	अगर (!instance->mask_पूर्णांकerrupts)
		ret = megasas_issue_blocked_cmd(instance, cmd,
			MFI_IO_TIMEOUT_SECS);
	अन्यथा
		ret = megasas_issue_polled(instance, cmd);

	अगर (le32_to_cpu(pd_sync->count) > MAX_PHYSICAL_DEVICES) अणु
		dev_warn(&instance->pdev->dev,
			"driver supports max %d JBOD, but FW reports %d\n",
			MAX_PHYSICAL_DEVICES, le32_to_cpu(pd_sync->count));
		ret = -EINVAL;
	पूर्ण

	अगर (ret == DCMD_TIMEOUT)
		dev_warn(&instance->pdev->dev,
			 "%s DCMD timed out, continue without JBOD sequence map\n",
			 __func__);

	अगर (ret == DCMD_SUCCESS)
		instance->pd_seq_map_id++;

	megasas_वापस_cmd(instance, cmd);
	वापस ret;
पूर्ण

/*
 * megasas_get_ld_map_info -	Returns FW's ld_map काष्ठाure
 * @instance:				Adapter soft state
 * @pend:				Pend the command or not
 * Issues an पूर्णांकernal command (DCMD) to get the FW's controller PD
 * list काष्ठाure.  This inक्रमmation is मुख्यly used to find out SYSTEM
 * supported by the FW.
 * dcmd.mbox value setting क्रम MR_DCMD_LD_MAP_GET_INFO
 * dcmd.mbox.b[0]	- number of LDs being sync'd
 * dcmd.mbox.b[1]	- 0 - complete command immediately.
 *			- 1 - pend till config change
 * dcmd.mbox.b[2]	- 0 - supports max 64 lds and uses legacy MR_FW_RAID_MAP
 *			- 1 - supports max MAX_LOGICAL_DRIVES_EXT lds and
 *				uses extended काष्ठा MR_FW_RAID_MAP_EXT
 */
अटल पूर्णांक
megasas_get_ld_map_info(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक ret = 0;
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_dcmd_frame *dcmd;
	व्योम *ci;
	dma_addr_t ci_h = 0;
	u32 size_map_info;
	काष्ठा fusion_context *fusion;

	cmd = megasas_get_cmd(instance);

	अगर (!cmd) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "Failed to get cmd for map info\n");
		वापस -ENOMEM;
	पूर्ण

	fusion = instance->ctrl_context;

	अगर (!fusion) अणु
		megasas_वापस_cmd(instance, cmd);
		वापस -ENXIO;
	पूर्ण

	dcmd = &cmd->frame->dcmd;

	size_map_info = fusion->current_map_sz;

	ci = (व्योम *) fusion->ld_map[(instance->map_id & 1)];
	ci_h = fusion->ld_map_phys[(instance->map_id & 1)];

	अगर (!ci) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "Failed to alloc mem for ld_map_info\n");
		megasas_वापस_cmd(instance, cmd);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(ci, 0, fusion->max_map_sz);
	स_रखो(dcmd->mbox.b, 0, MFI_MBOX_SIZE);
	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = 0xFF;
	dcmd->sge_count = 1;
	dcmd->flags = MFI_FRAME_सूची_READ;
	dcmd->समयout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len = cpu_to_le32(size_map_info);
	dcmd->opcode = cpu_to_le32(MR_DCMD_LD_MAP_GET_INFO);

	megasas_set_dma_settings(instance, dcmd, ci_h, size_map_info);

	अगर (!instance->mask_पूर्णांकerrupts)
		ret = megasas_issue_blocked_cmd(instance, cmd,
			MFI_IO_TIMEOUT_SECS);
	अन्यथा
		ret = megasas_issue_polled(instance, cmd);

	अगर (ret == DCMD_TIMEOUT)
		dev_warn(&instance->pdev->dev,
			 "%s DCMD timed out, RAID map is disabled\n",
			 __func__);

	megasas_वापस_cmd(instance, cmd);

	वापस ret;
पूर्ण

u8
megasas_get_map_info(काष्ठा megasas_instance *instance)
अणु
	काष्ठा fusion_context *fusion = instance->ctrl_context;

	fusion->fast_path_io = 0;
	अगर (!megasas_get_ld_map_info(instance)) अणु
		अगर (MR_ValidateMapInfo(instance, instance->map_id)) अणु
			fusion->fast_path_io = 1;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

/*
 * megasas_sync_map_info -	Returns FW's ld_map काष्ठाure
 * @instance:				Adapter soft state
 *
 * Issues an पूर्णांकernal command (DCMD) to get the FW's controller PD
 * list काष्ठाure.  This inक्रमmation is मुख्यly used to find out SYSTEM
 * supported by the FW.
 */
पूर्णांक
megasas_sync_map_info(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक i;
	काष्ठा megasas_cmd *cmd;
	काष्ठा megasas_dcmd_frame *dcmd;
	u16 num_lds;
	काष्ठा fusion_context *fusion;
	काष्ठा MR_LD_TARGET_SYNC *ci = शून्य;
	काष्ठा MR_DRV_RAID_MAP_ALL *map;
	काष्ठा MR_LD_RAID  *raid;
	काष्ठा MR_LD_TARGET_SYNC *ld_sync;
	dma_addr_t ci_h = 0;
	u32 size_map_info;

	cmd = megasas_get_cmd(instance);

	अगर (!cmd) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &instance->pdev->dev, "Failed to get cmd for sync info\n");
		वापस -ENOMEM;
	पूर्ण

	fusion = instance->ctrl_context;

	अगर (!fusion) अणु
		megasas_वापस_cmd(instance, cmd);
		वापस 1;
	पूर्ण

	map = fusion->ld_drv_map[instance->map_id & 1];

	num_lds = le16_to_cpu(map->raidMap.ldCount);

	dcmd = &cmd->frame->dcmd;

	स_रखो(dcmd->mbox.b, 0, MFI_MBOX_SIZE);

	ci = (काष्ठा MR_LD_TARGET_SYNC *)
	  fusion->ld_map[(instance->map_id - 1) & 1];
	स_रखो(ci, 0, fusion->max_map_sz);

	ci_h = fusion->ld_map_phys[(instance->map_id - 1) & 1];

	ld_sync = (काष्ठा MR_LD_TARGET_SYNC *)ci;

	क्रम (i = 0; i < num_lds; i++, ld_sync++) अणु
		raid = MR_LdRaidGet(i, map);
		ld_sync->targetId = MR_GetLDTgtId(i, map);
		ld_sync->seqNum = raid->seqNum;
	पूर्ण

	size_map_info = fusion->current_map_sz;

	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = 0xFF;
	dcmd->sge_count = 1;
	dcmd->flags = MFI_FRAME_सूची_WRITE;
	dcmd->समयout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len = cpu_to_le32(size_map_info);
	dcmd->mbox.b[0] = num_lds;
	dcmd->mbox.b[1] = MEGASAS_DCMD_MBOX_PEND_FLAG;
	dcmd->opcode = cpu_to_le32(MR_DCMD_LD_MAP_GET_INFO);

	megasas_set_dma_settings(instance, dcmd, ci_h, size_map_info);

	instance->map_update_cmd = cmd;

	instance->instancet->issue_dcmd(instance, cmd);

	वापस 0;
पूर्ण

/*
 * meagasas_display_पूर्णांकel_bअक्रमing - Display bअक्रमing string
 * @instance: per adapter object
 *
 * Return nothing.
 */
अटल व्योम
megasas_display_पूर्णांकel_bअक्रमing(काष्ठा megasas_instance *instance)
अणु
	अगर (instance->pdev->subप्रणाली_venकरोr != PCI_VENDOR_ID_INTEL)
		वापस;

	चयन (instance->pdev->device) अणु
	हाल PCI_DEVICE_ID_LSI_INVADER:
		चयन (instance->pdev->subप्रणाली_device) अणु
		हाल MEGARAID_INTEL_RS3DC080_SSDID:
			dev_info(&instance->pdev->dev, "scsi host %d: %s\n",
				instance->host->host_no,
				MEGARAID_INTEL_RS3DC080_BRANDING);
			अवरोध;
		हाल MEGARAID_INTEL_RS3DC040_SSDID:
			dev_info(&instance->pdev->dev, "scsi host %d: %s\n",
				instance->host->host_no,
				MEGARAID_INTEL_RS3DC040_BRANDING);
			अवरोध;
		हाल MEGARAID_INTEL_RS3SC008_SSDID:
			dev_info(&instance->pdev->dev, "scsi host %d: %s\n",
				instance->host->host_no,
				MEGARAID_INTEL_RS3SC008_BRANDING);
			अवरोध;
		हाल MEGARAID_INTEL_RS3MC044_SSDID:
			dev_info(&instance->pdev->dev, "scsi host %d: %s\n",
				instance->host->host_no,
				MEGARAID_INTEL_RS3MC044_BRANDING);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल PCI_DEVICE_ID_LSI_FURY:
		चयन (instance->pdev->subप्रणाली_device) अणु
		हाल MEGARAID_INTEL_RS3WC080_SSDID:
			dev_info(&instance->pdev->dev, "scsi host %d: %s\n",
				instance->host->host_no,
				MEGARAID_INTEL_RS3WC080_BRANDING);
			अवरोध;
		हाल MEGARAID_INTEL_RS3WC040_SSDID:
			dev_info(&instance->pdev->dev, "scsi host %d: %s\n",
				instance->host->host_no,
				MEGARAID_INTEL_RS3WC040_BRANDING);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल PCI_DEVICE_ID_LSI_CUTLASS_52:
	हाल PCI_DEVICE_ID_LSI_CUTLASS_53:
		चयन (instance->pdev->subप्रणाली_device) अणु
		हाल MEGARAID_INTEL_RMS3BC160_SSDID:
			dev_info(&instance->pdev->dev, "scsi host %d: %s\n",
				instance->host->host_no,
				MEGARAID_INTEL_RMS3BC160_BRANDING);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * megasas_allocate_raid_maps -	Allocate memory क्रम RAID maps
 * @instance:				Adapter soft state
 *
 * वापस:				अगर success: वापस 0
 *					failed:  वापस -ENOMEM
 */
अटल अंतरभूत पूर्णांक megasas_allocate_raid_maps(काष्ठा megasas_instance *instance)
अणु
	काष्ठा fusion_context *fusion;
	पूर्णांक i = 0;

	fusion = instance->ctrl_context;

	fusion->drv_map_pages = get_order(fusion->drv_map_sz);

	क्रम (i = 0; i < 2; i++) अणु
		fusion->ld_map[i] = शून्य;

		fusion->ld_drv_map[i] = (व्योम *)
			__get_मुक्त_pages(__GFP_ZERO | GFP_KERNEL,
					 fusion->drv_map_pages);

		अगर (!fusion->ld_drv_map[i]) अणु
			fusion->ld_drv_map[i] = vzalloc(fusion->drv_map_sz);

			अगर (!fusion->ld_drv_map[i]) अणु
				dev_err(&instance->pdev->dev,
					"Could not allocate memory for local map"
					" size requested: %d\n",
					fusion->drv_map_sz);
				जाओ ld_drv_map_alloc_fail;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		fusion->ld_map[i] = dma_alloc_coherent(&instance->pdev->dev,
						       fusion->max_map_sz,
						       &fusion->ld_map_phys[i],
						       GFP_KERNEL);
		अगर (!fusion->ld_map[i]) अणु
			dev_err(&instance->pdev->dev,
				"Could not allocate memory for map info %s:%d\n",
				__func__, __LINE__);
			जाओ ld_map_alloc_fail;
		पूर्ण
	पूर्ण

	वापस 0;

ld_map_alloc_fail:
	क्रम (i = 0; i < 2; i++) अणु
		अगर (fusion->ld_map[i])
			dma_मुक्त_coherent(&instance->pdev->dev,
					  fusion->max_map_sz,
					  fusion->ld_map[i],
					  fusion->ld_map_phys[i]);
	पूर्ण

ld_drv_map_alloc_fail:
	क्रम (i = 0; i < 2; i++) अणु
		अगर (fusion->ld_drv_map[i]) अणु
			अगर (is_vदो_स्मृति_addr(fusion->ld_drv_map[i]))
				vमुक्त(fusion->ld_drv_map[i]);
			अन्यथा
				मुक्त_pages((uदीर्घ)fusion->ld_drv_map[i],
					   fusion->drv_map_pages);
		पूर्ण
	पूर्ण

	वापस -ENOMEM;
पूर्ण

/**
 * megasas_configure_queue_sizes -	Calculate size of request desc queue,
 *					reply desc queue,
 *					IO request frame queue, set can_queue.
 * @instance:				Adapter soft state
 * @वापस:				व्योम
 */
अटल अंतरभूत
व्योम megasas_configure_queue_sizes(काष्ठा megasas_instance *instance)
अणु
	काष्ठा fusion_context *fusion;
	u16 max_cmd;

	fusion = instance->ctrl_context;
	max_cmd = instance->max_fw_cmds;

	अगर (instance->adapter_type >= VENTURA_SERIES)
		instance->max_mpt_cmds = instance->max_fw_cmds * RAID_1_PEER_CMDS;
	अन्यथा
		instance->max_mpt_cmds = instance->max_fw_cmds;

	instance->max_scsi_cmds = instance->max_fw_cmds - instance->max_mfi_cmds;
	instance->cur_can_queue = instance->max_scsi_cmds;
	instance->host->can_queue = instance->cur_can_queue;

	fusion->reply_q_depth = 2 * ((max_cmd + 1 + 15) / 16) * 16;

	fusion->request_alloc_sz = माप(जोड़ MEGASAS_REQUEST_DESCRIPTOR_UNION) *
					  instance->max_mpt_cmds;
	fusion->reply_alloc_sz = माप(जोड़ MPI2_REPLY_DESCRIPTORS_UNION) *
					(fusion->reply_q_depth);
	fusion->io_frames_alloc_sz = MEGA_MPI2_RAID_DEFAULT_IO_FRAME_SIZE +
		(MEGA_MPI2_RAID_DEFAULT_IO_FRAME_SIZE
		 * (instance->max_mpt_cmds + 1)); /* Extra 1 क्रम SMID 0 */
पूर्ण

अटल पूर्णांक megasas_alloc_ioc_init_frame(काष्ठा megasas_instance *instance)
अणु
	काष्ठा fusion_context *fusion;
	काष्ठा megasas_cmd *cmd;

	fusion = instance->ctrl_context;

	cmd = kzalloc(माप(काष्ठा megasas_cmd), GFP_KERNEL);

	अगर (!cmd) अणु
		dev_err(&instance->pdev->dev, "Failed from func: %s line: %d\n",
			__func__, __LINE__);
		वापस -ENOMEM;
	पूर्ण

	cmd->frame = dma_alloc_coherent(&instance->pdev->dev,
					IOC_INIT_FRAME_SIZE,
					&cmd->frame_phys_addr, GFP_KERNEL);

	अगर (!cmd->frame) अणु
		dev_err(&instance->pdev->dev, "Failed from func: %s line: %d\n",
			__func__, __LINE__);
		kमुक्त(cmd);
		वापस -ENOMEM;
	पूर्ण

	fusion->ioc_init_cmd = cmd;
	वापस 0;
पूर्ण

/**
 * megasas_मुक्त_ioc_init_cmd -	Free IOC INIT command frame
 * @instance:		Adapter soft state
 */
अटल अंतरभूत व्योम megasas_मुक्त_ioc_init_cmd(काष्ठा megasas_instance *instance)
अणु
	काष्ठा fusion_context *fusion;

	fusion = instance->ctrl_context;

	अगर (fusion->ioc_init_cmd && fusion->ioc_init_cmd->frame)
		dma_मुक्त_coherent(&instance->pdev->dev,
				  IOC_INIT_FRAME_SIZE,
				  fusion->ioc_init_cmd->frame,
				  fusion->ioc_init_cmd->frame_phys_addr);

	kमुक्त(fusion->ioc_init_cmd);
पूर्ण

/**
 * megasas_init_adapter_fusion -	Initializes the FW
 * @instance:		Adapter soft state
 *
 * This is the मुख्य function क्रम initializing firmware.
 */
अटल u32
megasas_init_adapter_fusion(काष्ठा megasas_instance *instance)
अणु
	काष्ठा fusion_context *fusion;
	u32 scratch_pad_1;
	पूर्णांक i = 0, count;
	u32 status_reg;

	fusion = instance->ctrl_context;

	megasas_fusion_update_can_queue(instance, PROBE_CONTEXT);

	/*
	 * Only Driver's पूर्णांकernal DCMDs and IOCTL DCMDs needs to have MFI frames
	 */
	instance->max_mfi_cmds =
		MEGASAS_FUSION_INTERNAL_CMDS + MEGASAS_FUSION_IOCTL_CMDS;

	megasas_configure_queue_sizes(instance);

	scratch_pad_1 = megasas_पढ़ोl(instance,
				      &instance->reg_set->outbound_scratch_pad_1);
	/* If scratch_pad_1 & MEGASAS_MAX_CHAIN_SIZE_UNITS_MASK is set,
	 * Firmware support extended IO chain frame which is 4 बार more than
	 * legacy Firmware.
	 * Legacy Firmware - Frame size is (8 * 128) = 1K
	 * 1M IO Firmware  - Frame size is (8 * 128 * 4)  = 4K
	 */
	अगर (scratch_pad_1 & MEGASAS_MAX_CHAIN_SIZE_UNITS_MASK)
		instance->max_chain_frame_sz =
			((scratch_pad_1 & MEGASAS_MAX_CHAIN_SIZE_MASK) >>
			MEGASAS_MAX_CHAIN_SHIFT) * MEGASAS_1MB_IO;
	अन्यथा
		instance->max_chain_frame_sz =
			((scratch_pad_1 & MEGASAS_MAX_CHAIN_SIZE_MASK) >>
			MEGASAS_MAX_CHAIN_SHIFT) * MEGASAS_256K_IO;

	अगर (instance->max_chain_frame_sz < MEGASAS_CHAIN_FRAME_SZ_MIN) अणु
		dev_warn(&instance->pdev->dev, "frame size %d invalid, fall back to legacy max frame size %d\n",
			instance->max_chain_frame_sz,
			MEGASAS_CHAIN_FRAME_SZ_MIN);
		instance->max_chain_frame_sz = MEGASAS_CHAIN_FRAME_SZ_MIN;
	पूर्ण

	fusion->max_sge_in_मुख्य_msg =
		(MEGA_MPI2_RAID_DEFAULT_IO_FRAME_SIZE
			- दुरत्व(काष्ठा MPI2_RAID_SCSI_IO_REQUEST, SGL))/16;

	fusion->max_sge_in_chain =
		instance->max_chain_frame_sz
			/ माप(जोड़ MPI2_SGE_IO_UNION);

	instance->max_num_sge =
		roundकरोwn_घात_of_two(fusion->max_sge_in_मुख्य_msg
			+ fusion->max_sge_in_chain - 2);

	/* Used क्रम pass thru MFI frame (DCMD) */
	fusion->chain_offset_mfi_pthru =
		दुरत्व(काष्ठा MPI2_RAID_SCSI_IO_REQUEST, SGL)/16;

	fusion->chain_offset_io_request =
		(MEGA_MPI2_RAID_DEFAULT_IO_FRAME_SIZE -
		 माप(जोड़ MPI2_SGE_IO_UNION))/16;

	count = instance->msix_vectors > 0 ? instance->msix_vectors : 1;
	count += instance->iopoll_q_count;

	क्रम (i = 0 ; i < count; i++)
		fusion->last_reply_idx[i] = 0;

	/*
	 * For fusion adapters, 3 commands क्रम IOCTL and 8 commands
	 * क्रम driver's पूर्णांकernal DCMDs.
	 */
	instance->max_scsi_cmds = instance->max_fw_cmds -
				(MEGASAS_FUSION_INTERNAL_CMDS +
				MEGASAS_FUSION_IOCTL_CMDS);
	sema_init(&instance->ioctl_sem, MEGASAS_FUSION_IOCTL_CMDS);

	क्रम (i = 0; i < MAX_MSIX_QUEUES_FUSION; i++)
		atomic_set(&fusion->busy_mq_poll[i], 0);

	अगर (megasas_alloc_ioc_init_frame(instance))
		वापस 1;

	/*
	 * Allocate memory क्रम descriptors
	 * Create a pool of commands
	 */
	अगर (megasas_alloc_cmds(instance))
		जाओ fail_alloc_mfi_cmds;
	अगर (megasas_alloc_cmds_fusion(instance))
		जाओ fail_alloc_cmds;

	अगर (megasas_ioc_init_fusion(instance)) अणु
		status_reg = instance->instancet->पढ़ो_fw_status_reg(instance);
		अगर (((status_reg & MFI_STATE_MASK) == MFI_STATE_FAULT) &&
		    (status_reg & MFI_RESET_ADAPTER)) अणु
			/* Do a chip reset and then retry IOC INIT once */
			अगर (megasas_adp_reset_रुको_क्रम_पढ़ोy
				(instance, true, 0) == FAILED)
				जाओ fail_ioc_init;

			अगर (megasas_ioc_init_fusion(instance))
				जाओ fail_ioc_init;
		पूर्ण अन्यथा अणु
			जाओ fail_ioc_init;
		पूर्ण
	पूर्ण

	megasas_display_पूर्णांकel_bअक्रमing(instance);
	अगर (megasas_get_ctrl_info(instance)) अणु
		dev_err(&instance->pdev->dev,
			"Could not get controller info. Fail from %s %d\n",
			__func__, __LINE__);
		जाओ fail_ioc_init;
	पूर्ण

	instance->flag_ieee = 1;
	instance->r1_ldio_hपूर्णांक_शेष =  MR_R1_LDIO_PIGGYBACK_DEFAULT;
	instance->threshold_reply_count = instance->max_fw_cmds / 4;
	fusion->fast_path_io = 0;

	अगर (megasas_allocate_raid_maps(instance))
		जाओ fail_ioc_init;

	अगर (!megasas_get_map_info(instance))
		megasas_sync_map_info(instance);

	वापस 0;

fail_ioc_init:
	megasas_मुक्त_cmds_fusion(instance);
fail_alloc_cmds:
	megasas_मुक्त_cmds(instance);
fail_alloc_mfi_cmds:
	megasas_मुक्त_ioc_init_cmd(instance);
	वापस 1;
पूर्ण

/**
 * megasas_fault_detect_work	-	Worker function of
 *					FW fault handling workqueue.
 * @work:	FW fault work काष्ठा
 */
अटल व्योम
megasas_fault_detect_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा megasas_instance *instance =
		container_of(work, काष्ठा megasas_instance,
			     fw_fault_work.work);
	u32 fw_state, dma_state, status;

	/* Check the fw state */
	fw_state = instance->instancet->पढ़ो_fw_status_reg(instance) &
			MFI_STATE_MASK;

	अगर (fw_state == MFI_STATE_FAULT) अणु
		dma_state = instance->instancet->पढ़ो_fw_status_reg(instance) &
				MFI_STATE_DMADONE;
		/* Start collecting crash, अगर DMA bit is करोne */
		अगर (instance->crash_dump_drv_support &&
		    instance->crash_dump_app_support && dma_state) अणु
			megasas_fusion_crash_dump(instance);
		पूर्ण अन्यथा अणु
			अगर (instance->unload == 0) अणु
				status = megasas_reset_fusion(instance->host, 0);
				अगर (status != SUCCESS) अणु
					dev_err(&instance->pdev->dev,
						"Failed from %s %d, do not re-arm timer\n",
						__func__, __LINE__);
					वापस;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (instance->fw_fault_work_q)
		queue_delayed_work(instance->fw_fault_work_q,
			&instance->fw_fault_work,
			msecs_to_jअगरfies(MEGASAS_WATCHDOG_THREAD_INTERVAL));
पूर्ण

पूर्णांक
megasas_fusion_start_watchकरोg(काष्ठा megasas_instance *instance)
अणु
	/* Check अगर the Fault WQ is alपढ़ोy started */
	अगर (instance->fw_fault_work_q)
		वापस SUCCESS;

	INIT_DELAYED_WORK(&instance->fw_fault_work, megasas_fault_detect_work);

	snम_लिखो(instance->fault_handler_work_q_name,
		 माप(instance->fault_handler_work_q_name),
		 "poll_megasas%d_status", instance->host->host_no);

	instance->fw_fault_work_q =
		create_singlethपढ़ो_workqueue(instance->fault_handler_work_q_name);
	अगर (!instance->fw_fault_work_q) अणु
		dev_err(&instance->pdev->dev, "Failed from %s %d\n",
			__func__, __LINE__);
		वापस FAILED;
	पूर्ण

	queue_delayed_work(instance->fw_fault_work_q,
			   &instance->fw_fault_work,
			   msecs_to_jअगरfies(MEGASAS_WATCHDOG_THREAD_INTERVAL));

	वापस SUCCESS;
पूर्ण

व्योम
megasas_fusion_stop_watchकरोg(काष्ठा megasas_instance *instance)
अणु
	काष्ठा workqueue_काष्ठा *wq;

	अगर (instance->fw_fault_work_q) अणु
		wq = instance->fw_fault_work_q;
		instance->fw_fault_work_q = शून्य;
		अगर (!cancel_delayed_work_sync(&instance->fw_fault_work))
			flush_workqueue(wq);
		destroy_workqueue(wq);
	पूर्ण
पूर्ण

/**
 * map_cmd_status -	Maps FW cmd status to OS cmd status
 * @fusion:		fusion context
 * @scmd:		Poपूर्णांकer to cmd
 * @status:		status of cmd वापसed by FW
 * @ext_status:		ext status of cmd वापसed by FW
 * @data_length:	command data length
 * @sense:		command sense data
 */
अटल व्योम
map_cmd_status(काष्ठा fusion_context *fusion,
		काष्ठा scsi_cmnd *scmd, u8 status, u8 ext_status,
		u32 data_length, u8 *sense)
अणु
	u8 cmd_type;
	पूर्णांक resid;

	cmd_type = megasas_cmd_type(scmd);
	चयन (status) अणु

	हाल MFI_STAT_OK:
		scmd->result = DID_OK << 16;
		अवरोध;

	हाल MFI_STAT_SCSI_IO_FAILED:
	हाल MFI_STAT_LD_INIT_IN_PROGRESS:
		scmd->result = (DID_ERROR << 16) | ext_status;
		अवरोध;

	हाल MFI_STAT_SCSI_DONE_WITH_ERROR:

		scmd->result = (DID_OK << 16) | ext_status;
		अगर (ext_status == SAM_STAT_CHECK_CONDITION) अणु
			स_रखो(scmd->sense_buffer, 0,
			       SCSI_SENSE_BUFFERSIZE);
			स_नकल(scmd->sense_buffer, sense,
			       SCSI_SENSE_BUFFERSIZE);
			scmd->result |= DRIVER_SENSE << 24;
		पूर्ण

		/*
		 * If the  IO request is partially completed, then MR FW will
		 * update "io_request->DataLength" field with actual number of
		 * bytes transferred.Driver will set residual bytes count in
		 * SCSI command काष्ठाure.
		 */
		resid = (scsi_bufflen(scmd) - data_length);
		scsi_set_resid(scmd, resid);

		अगर (resid &&
			((cmd_type == READ_WRITE_LDIO) ||
			(cmd_type == READ_WRITE_SYSPDIO)))
			scmd_prपूर्णांकk(KERN_INFO, scmd, "BRCM Debug mfi stat 0x%x, data len"
				" requested/completed 0x%x/0x%x\n",
				status, scsi_bufflen(scmd), data_length);
		अवरोध;

	हाल MFI_STAT_LD_OFFLINE:
	हाल MFI_STAT_DEVICE_NOT_FOUND:
		scmd->result = DID_BAD_TARGET << 16;
		अवरोध;
	हाल MFI_STAT_CONFIG_SEQ_MISMATCH:
		scmd->result = DID_IMM_RETRY << 16;
		अवरोध;
	शेष:
		scmd->result = DID_ERROR << 16;
		अवरोध;
	पूर्ण
पूर्ण

/**
 * megasas_is_prp_possible -
 * Checks अगर native NVMe PRPs can be built क्रम the IO
 *
 * @instance:		Adapter soft state
 * @scmd:		SCSI command from the mid-layer
 * @sge_count:		scatter gather element count.
 *
 * Returns:		true: PRPs can be built
 *			false: IEEE SGLs needs to be built
 */
अटल bool
megasas_is_prp_possible(काष्ठा megasas_instance *instance,
			काष्ठा scsi_cmnd *scmd, पूर्णांक sge_count)
अणु
	u32 data_length = 0;
	काष्ठा scatterlist *sg_scmd;
	bool build_prp = false;
	u32 mr_nvme_pg_size;

	mr_nvme_pg_size = max_t(u32, instance->nvme_page_size,
				MR_DEFAULT_NVME_PAGE_SIZE);
	data_length = scsi_bufflen(scmd);
	sg_scmd = scsi_sglist(scmd);

	/*
	 * NVMe uses one PRP क्रम each page (or part of a page)
	 * look at the data length - अगर 4 pages or less then IEEE is OK
	 * अगर  > 5 pages then we need to build a native SGL
	 * अगर > 4 and <= 5 pages, then check physical address of 1st SG entry
	 * अगर this first size in the page is >= the residual beyond 4 pages
	 * then use IEEE, otherwise use native SGL
	 */

	अगर (data_length > (mr_nvme_pg_size * 5)) अणु
		build_prp = true;
	पूर्ण अन्यथा अगर ((data_length > (mr_nvme_pg_size * 4)) &&
			(data_length <= (mr_nvme_pg_size * 5)))  अणु
		/* check अगर 1st SG entry size is < residual beyond 4 pages */
		अगर (sg_dma_len(sg_scmd) < (data_length - (mr_nvme_pg_size * 4)))
			build_prp = true;
	पूर्ण

	वापस build_prp;
पूर्ण

/**
 * megasas_make_prp_nvme -
 * Prepare PRPs(Physical Region Page)- SGLs specअगरic to NVMe drives only
 *
 * @instance:		Adapter soft state
 * @scmd:		SCSI command from the mid-layer
 * @sgl_ptr:		SGL to be filled in
 * @cmd:		Fusion command frame
 * @sge_count:		scatter gather element count.
 *
 * Returns:		true: PRPs are built
 *			false: IEEE SGLs needs to be built
 */
अटल bool
megasas_make_prp_nvme(काष्ठा megasas_instance *instance, काष्ठा scsi_cmnd *scmd,
		      काष्ठा MPI25_IEEE_SGE_CHAIN64 *sgl_ptr,
		      काष्ठा megasas_cmd_fusion *cmd, पूर्णांक sge_count)
अणु
	पूर्णांक sge_len, offset, num_prp_in_chain = 0;
	काष्ठा MPI25_IEEE_SGE_CHAIN64 *मुख्य_chain_element, *ptr_first_sgl;
	u64 *ptr_sgl;
	dma_addr_t ptr_sgl_phys;
	u64 sge_addr;
	u32 page_mask, page_mask_result;
	काष्ठा scatterlist *sg_scmd;
	u32 first_prp_len;
	bool build_prp = false;
	पूर्णांक data_len = scsi_bufflen(scmd);
	u32 mr_nvme_pg_size = max_t(u32, instance->nvme_page_size,
					MR_DEFAULT_NVME_PAGE_SIZE);

	build_prp = megasas_is_prp_possible(instance, scmd, sge_count);

	अगर (!build_prp)
		वापस false;

	/*
	 * Nvme has a very convoluted prp क्रमmat.  One prp is required
	 * क्रम each page or partial page. Driver need to split up OS sg_list
	 * entries अगर it is दीर्घer than one page or cross a page
	 * boundary.  Driver also have to insert a PRP list poपूर्णांकer entry as
	 * the last entry in each physical page of the PRP list.
	 *
	 * NOTE: The first PRP "entry" is actually placed in the first
	 * SGL entry in the मुख्य message as IEEE 64 क्रमmat.  The 2nd
	 * entry in the मुख्य message is the chain element, and the rest
	 * of the PRP entries are built in the contiguous pcie buffer.
	 */
	page_mask = mr_nvme_pg_size - 1;
	ptr_sgl = (u64 *)cmd->sg_frame;
	ptr_sgl_phys = cmd->sg_frame_phys_addr;
	स_रखो(ptr_sgl, 0, instance->max_chain_frame_sz);

	/* Build chain frame element which holds all prps except first*/
	मुख्य_chain_element = (काष्ठा MPI25_IEEE_SGE_CHAIN64 *)
	    ((u8 *)sgl_ptr + माप(काष्ठा MPI25_IEEE_SGE_CHAIN64));

	मुख्य_chain_element->Address = cpu_to_le64(ptr_sgl_phys);
	मुख्य_chain_element->NextChainOffset = 0;
	मुख्य_chain_element->Flags = IEEE_SGE_FLAGS_CHAIN_ELEMENT |
					IEEE_SGE_FLAGS_SYSTEM_ADDR |
					MPI26_IEEE_SGE_FLAGS_NSF_NVME_PRP;

	/* Build first prp, sge need not to be page aligned*/
	ptr_first_sgl = sgl_ptr;
	sg_scmd = scsi_sglist(scmd);
	sge_addr = sg_dma_address(sg_scmd);
	sge_len = sg_dma_len(sg_scmd);

	offset = (u32)(sge_addr & page_mask);
	first_prp_len = mr_nvme_pg_size - offset;

	ptr_first_sgl->Address = cpu_to_le64(sge_addr);
	ptr_first_sgl->Length = cpu_to_le32(first_prp_len);

	data_len -= first_prp_len;

	अगर (sge_len > first_prp_len) अणु
		sge_addr += first_prp_len;
		sge_len -= first_prp_len;
	पूर्ण अन्यथा अगर (sge_len == first_prp_len) अणु
		sg_scmd = sg_next(sg_scmd);
		sge_addr = sg_dma_address(sg_scmd);
		sge_len = sg_dma_len(sg_scmd);
	पूर्ण

	क्रम (;;) अणु
		offset = (u32)(sge_addr & page_mask);

		/* Put PRP poपूर्णांकer due to page boundary*/
		page_mask_result = (uपूर्णांकptr_t)(ptr_sgl + 1) & page_mask;
		अगर (unlikely(!page_mask_result)) अणु
			scmd_prपूर्णांकk(KERN_NOTICE,
				    scmd, "page boundary ptr_sgl: 0x%p\n",
				    ptr_sgl);
			ptr_sgl_phys += 8;
			*ptr_sgl = cpu_to_le64(ptr_sgl_phys);
			ptr_sgl++;
			num_prp_in_chain++;
		पूर्ण

		*ptr_sgl = cpu_to_le64(sge_addr);
		ptr_sgl++;
		ptr_sgl_phys += 8;
		num_prp_in_chain++;

		sge_addr += mr_nvme_pg_size;
		sge_len -= mr_nvme_pg_size;
		data_len -= mr_nvme_pg_size;

		अगर (data_len <= 0)
			अवरोध;

		अगर (sge_len > 0)
			जारी;

		sg_scmd = sg_next(sg_scmd);
		sge_addr = sg_dma_address(sg_scmd);
		sge_len = sg_dma_len(sg_scmd);
	पूर्ण

	मुख्य_chain_element->Length =
			cpu_to_le32(num_prp_in_chain * माप(u64));

	वापस build_prp;
पूर्ण

/**
 * megasas_make_sgl_fusion -	Prepares 32-bit SGL
 * @instance:		Adapter soft state
 * @scp:		SCSI command from the mid-layer
 * @sgl_ptr:		SGL to be filled in
 * @cmd:		cmd we are working on
 * @sge_count:		sge count
 *
 */
अटल व्योम
megasas_make_sgl_fusion(काष्ठा megasas_instance *instance,
			काष्ठा scsi_cmnd *scp,
			काष्ठा MPI25_IEEE_SGE_CHAIN64 *sgl_ptr,
			काष्ठा megasas_cmd_fusion *cmd, पूर्णांक sge_count)
अणु
	पूर्णांक i, sg_processed;
	काष्ठा scatterlist *os_sgl;
	काष्ठा fusion_context *fusion;

	fusion = instance->ctrl_context;

	अगर (instance->adapter_type >= INVADER_SERIES) अणु
		काष्ठा MPI25_IEEE_SGE_CHAIN64 *sgl_ptr_end = sgl_ptr;
		sgl_ptr_end += fusion->max_sge_in_मुख्य_msg - 1;
		sgl_ptr_end->Flags = 0;
	पूर्ण

	scsi_क्रम_each_sg(scp, os_sgl, sge_count, i) अणु
		sgl_ptr->Length = cpu_to_le32(sg_dma_len(os_sgl));
		sgl_ptr->Address = cpu_to_le64(sg_dma_address(os_sgl));
		sgl_ptr->Flags = 0;
		अगर (instance->adapter_type >= INVADER_SERIES)
			अगर (i == sge_count - 1)
				sgl_ptr->Flags = IEEE_SGE_FLAGS_END_OF_LIST;
		sgl_ptr++;
		sg_processed = i + 1;

		अगर ((sg_processed ==  (fusion->max_sge_in_मुख्य_msg - 1)) &&
		    (sge_count > fusion->max_sge_in_मुख्य_msg)) अणु

			काष्ठा MPI25_IEEE_SGE_CHAIN64 *sg_chain;
			अगर (instance->adapter_type >= INVADER_SERIES) अणु
				अगर ((le16_to_cpu(cmd->io_request->IoFlags) &
					MPI25_SAS_DEVICE0_FLAGS_ENABLED_FAST_PATH) !=
					MPI25_SAS_DEVICE0_FLAGS_ENABLED_FAST_PATH)
					cmd->io_request->ChainOffset =
						fusion->
						chain_offset_io_request;
				अन्यथा
					cmd->io_request->ChainOffset = 0;
			पूर्ण अन्यथा
				cmd->io_request->ChainOffset =
					fusion->chain_offset_io_request;

			sg_chain = sgl_ptr;
			/* Prepare chain element */
			sg_chain->NextChainOffset = 0;
			अगर (instance->adapter_type >= INVADER_SERIES)
				sg_chain->Flags = IEEE_SGE_FLAGS_CHAIN_ELEMENT;
			अन्यथा
				sg_chain->Flags =
					(IEEE_SGE_FLAGS_CHAIN_ELEMENT |
					 MPI2_IEEE_SGE_FLAGS_IOCPLBNTA_ADDR);
			sg_chain->Length =  cpu_to_le32((माप(जोड़ MPI2_SGE_IO_UNION) * (sge_count - sg_processed)));
			sg_chain->Address = cpu_to_le64(cmd->sg_frame_phys_addr);

			sgl_ptr =
			  (काष्ठा MPI25_IEEE_SGE_CHAIN64 *)cmd->sg_frame;
			स_रखो(sgl_ptr, 0, instance->max_chain_frame_sz);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * megasas_make_sgl -	Build Scatter Gather List(SGLs)
 * @scp:		SCSI command poपूर्णांकer
 * @instance:		Soft instance of controller
 * @cmd:		Fusion command poपूर्णांकer
 *
 * This function will build sgls based on device type.
 * For nvme drives, there is dअगरferent way of building sgls in nvme native
 * क्रमmat- PRPs(Physical Region Page).
 *
 * Returns the number of sg lists actually used, zero अगर the sg lists
 * is शून्य, or -ENOMEM अगर the mapping failed
 */
अटल
पूर्णांक megasas_make_sgl(काष्ठा megasas_instance *instance, काष्ठा scsi_cmnd *scp,
		     काष्ठा megasas_cmd_fusion *cmd)
अणु
	पूर्णांक sge_count;
	bool build_prp = false;
	काष्ठा MPI25_IEEE_SGE_CHAIN64 *sgl_chain64;

	sge_count = scsi_dma_map(scp);

	अगर ((sge_count > instance->max_num_sge) || (sge_count <= 0))
		वापस sge_count;

	sgl_chain64 = (काष्ठा MPI25_IEEE_SGE_CHAIN64 *)&cmd->io_request->SGL;
	अगर ((le16_to_cpu(cmd->io_request->IoFlags) &
	    MPI25_SAS_DEVICE0_FLAGS_ENABLED_FAST_PATH) &&
	    (cmd->pd_पूर्णांकerface == NVME_PD))
		build_prp = megasas_make_prp_nvme(instance, scp, sgl_chain64,
						  cmd, sge_count);

	अगर (!build_prp)
		megasas_make_sgl_fusion(instance, scp, sgl_chain64,
					cmd, sge_count);

	वापस sge_count;
पूर्ण

/**
 * megasas_set_pd_lba -	Sets PD LBA
 * @io_request:		IO request
 * @cdb_len:		cdb length
 * @io_info:		IO inक्रमmation
 * @scp:		SCSI command
 * @local_map_ptr:	Raid map
 * @ref_tag:		Primary reference tag
 *
 * Used to set the PD LBA in CDB क्रम FP IOs
 */
अटल व्योम
megasas_set_pd_lba(काष्ठा MPI2_RAID_SCSI_IO_REQUEST *io_request, u8 cdb_len,
		   काष्ठा IO_REQUEST_INFO *io_info, काष्ठा scsi_cmnd *scp,
		   काष्ठा MR_DRV_RAID_MAP_ALL *local_map_ptr, u32 ref_tag)
अणु
	काष्ठा MR_LD_RAID *raid;
	u16 ld;
	u64 start_blk = io_info->pdBlock;
	u8 *cdb = io_request->CDB.CDB32;
	u32 num_blocks = io_info->numBlocks;
	u8 opcode = 0, flagvals = 0, groupnum = 0, control = 0;

	/* Check अगर T10 PI (DIF) is enabled क्रम this LD */
	ld = MR_TargetIdToLdGet(io_info->ldTgtId, local_map_ptr);
	raid = MR_LdRaidGet(ld, local_map_ptr);
	अगर (raid->capability.ldPiMode == MR_PROT_INFO_TYPE_CONTROLLER) अणु
		स_रखो(cdb, 0, माप(io_request->CDB.CDB32));
		cdb[0] =  MEGASAS_SCSI_VARIABLE_LENGTH_CMD;
		cdb[7] =  MEGASAS_SCSI_ADDL_CDB_LEN;

		अगर (scp->sc_data_direction == DMA_FROM_DEVICE)
			cdb[9] = MEGASAS_SCSI_SERVICE_ACTION_READ32;
		अन्यथा
			cdb[9] = MEGASAS_SCSI_SERVICE_ACTION_WRITE32;
		cdb[10] = MEGASAS_RD_WR_PROTECT_CHECK_ALL;

		/* LBA */
		cdb[12] = (u8)((start_blk >> 56) & 0xff);
		cdb[13] = (u8)((start_blk >> 48) & 0xff);
		cdb[14] = (u8)((start_blk >> 40) & 0xff);
		cdb[15] = (u8)((start_blk >> 32) & 0xff);
		cdb[16] = (u8)((start_blk >> 24) & 0xff);
		cdb[17] = (u8)((start_blk >> 16) & 0xff);
		cdb[18] = (u8)((start_blk >> 8) & 0xff);
		cdb[19] = (u8)(start_blk & 0xff);

		/* Logical block reference tag */
		io_request->CDB.EEDP32.PrimaryReferenceTag =
			cpu_to_be32(ref_tag);
		io_request->CDB.EEDP32.PrimaryApplicationTagMask = cpu_to_be16(0xffff);
		io_request->IoFlags = cpu_to_le16(32); /* Specअगरy 32-byte cdb */

		/* Transfer length */
		cdb[28] = (u8)((num_blocks >> 24) & 0xff);
		cdb[29] = (u8)((num_blocks >> 16) & 0xff);
		cdb[30] = (u8)((num_blocks >> 8) & 0xff);
		cdb[31] = (u8)(num_blocks & 0xff);

		/* set SCSI IO EEDPFlags */
		अगर (scp->sc_data_direction == DMA_FROM_DEVICE) अणु
			io_request->EEDPFlags = cpu_to_le16(
				MPI2_SCSIIO_EEDPFLAGS_INC_PRI_REFTAG  |
				MPI2_SCSIIO_EEDPFLAGS_CHECK_REFTAG |
				MPI2_SCSIIO_EEDPFLAGS_CHECK_REMOVE_OP |
				MPI2_SCSIIO_EEDPFLAGS_CHECK_APPTAG |
				MPI25_SCSIIO_EEDPFLAGS_DO_NOT_DISABLE_MODE |
				MPI2_SCSIIO_EEDPFLAGS_CHECK_GUARD);
		पूर्ण अन्यथा अणु
			io_request->EEDPFlags = cpu_to_le16(
				MPI2_SCSIIO_EEDPFLAGS_INC_PRI_REFTAG |
				MPI2_SCSIIO_EEDPFLAGS_INSERT_OP);
		पूर्ण
		io_request->Control |= cpu_to_le32((0x4 << 26));
		io_request->EEDPBlockSize = cpu_to_le32(scp->device->sector_size);
	पूर्ण अन्यथा अणु
		/* Some drives करोn't support 16/12 byte CDB's, convert to 10 */
		अगर (((cdb_len == 12) || (cdb_len == 16)) &&
		    (start_blk <= 0xffffffff)) अणु
			अगर (cdb_len == 16) अणु
				opcode = cdb[0] == READ_16 ? READ_10 : WRITE_10;
				flagvals = cdb[1];
				groupnum = cdb[14];
				control = cdb[15];
			पूर्ण अन्यथा अणु
				opcode = cdb[0] == READ_12 ? READ_10 : WRITE_10;
				flagvals = cdb[1];
				groupnum = cdb[10];
				control = cdb[11];
			पूर्ण

			स_रखो(cdb, 0, माप(io_request->CDB.CDB32));

			cdb[0] = opcode;
			cdb[1] = flagvals;
			cdb[6] = groupnum;
			cdb[9] = control;

			/* Transfer length */
			cdb[8] = (u8)(num_blocks & 0xff);
			cdb[7] = (u8)((num_blocks >> 8) & 0xff);

			io_request->IoFlags = cpu_to_le16(10); /* Specअगरy 10-byte cdb */
			cdb_len = 10;
		पूर्ण अन्यथा अगर ((cdb_len < 16) && (start_blk > 0xffffffff)) अणु
			/* Convert to 16 byte CDB क्रम large LBA's */
			चयन (cdb_len) अणु
			हाल 6:
				opcode = cdb[0] == READ_6 ? READ_16 : WRITE_16;
				control = cdb[5];
				अवरोध;
			हाल 10:
				opcode =
					cdb[0] == READ_10 ? READ_16 : WRITE_16;
				flagvals = cdb[1];
				groupnum = cdb[6];
				control = cdb[9];
				अवरोध;
			हाल 12:
				opcode =
					cdb[0] == READ_12 ? READ_16 : WRITE_16;
				flagvals = cdb[1];
				groupnum = cdb[10];
				control = cdb[11];
				अवरोध;
			पूर्ण

			स_रखो(cdb, 0, माप(io_request->CDB.CDB32));

			cdb[0] = opcode;
			cdb[1] = flagvals;
			cdb[14] = groupnum;
			cdb[15] = control;

			/* Transfer length */
			cdb[13] = (u8)(num_blocks & 0xff);
			cdb[12] = (u8)((num_blocks >> 8) & 0xff);
			cdb[11] = (u8)((num_blocks >> 16) & 0xff);
			cdb[10] = (u8)((num_blocks >> 24) & 0xff);

			io_request->IoFlags = cpu_to_le16(16); /* Specअगरy 16-byte cdb */
			cdb_len = 16;
		पूर्ण

		/* Normal हाल, just load LBA here */
		चयन (cdb_len) अणु
		हाल 6:
		अणु
			u8 val = cdb[1] & 0xE0;
			cdb[3] = (u8)(start_blk & 0xff);
			cdb[2] = (u8)((start_blk >> 8) & 0xff);
			cdb[1] = val | ((u8)(start_blk >> 16) & 0x1f);
			अवरोध;
		पूर्ण
		हाल 10:
			cdb[5] = (u8)(start_blk & 0xff);
			cdb[4] = (u8)((start_blk >> 8) & 0xff);
			cdb[3] = (u8)((start_blk >> 16) & 0xff);
			cdb[2] = (u8)((start_blk >> 24) & 0xff);
			अवरोध;
		हाल 12:
			cdb[5]    = (u8)(start_blk & 0xff);
			cdb[4]    = (u8)((start_blk >> 8) & 0xff);
			cdb[3]    = (u8)((start_blk >> 16) & 0xff);
			cdb[2]    = (u8)((start_blk >> 24) & 0xff);
			अवरोध;
		हाल 16:
			cdb[9]    = (u8)(start_blk & 0xff);
			cdb[8]    = (u8)((start_blk >> 8) & 0xff);
			cdb[7]    = (u8)((start_blk >> 16) & 0xff);
			cdb[6]    = (u8)((start_blk >> 24) & 0xff);
			cdb[5]    = (u8)((start_blk >> 32) & 0xff);
			cdb[4]    = (u8)((start_blk >> 40) & 0xff);
			cdb[3]    = (u8)((start_blk >> 48) & 0xff);
			cdb[2]    = (u8)((start_blk >> 56) & 0xff);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * megasas_stream_detect -	stream detection on पढ़ो and and ग_लिखो IOs
 * @instance:		Adapter soft state
 * @cmd:		    Command to be prepared
 * @io_info:		IO Request info
 *
 */

/** stream detection on पढ़ो and and ग_लिखो IOs */
अटल व्योम megasas_stream_detect(काष्ठा megasas_instance *instance,
				  काष्ठा megasas_cmd_fusion *cmd,
				  काष्ठा IO_REQUEST_INFO *io_info)
अणु
	काष्ठा fusion_context *fusion = instance->ctrl_context;
	u32 device_id = io_info->ldTgtId;
	काष्ठा LD_STREAM_DETECT *current_ld_sd
		= fusion->stream_detect_by_ld[device_id];
	u32 *track_stream = &current_ld_sd->mru_bit_map, stream_num;
	u32 shअगरted_values, unshअगरted_values;
	u32 index_value_mask, shअगरted_values_mask;
	पूर्णांक i;
	bool is_पढ़ो_ahead = false;
	काष्ठा STREAM_DETECT *current_sd;
	/* find possible stream */
	क्रम (i = 0; i < MAX_STREAMS_TRACKED; ++i) अणु
		stream_num = (*track_stream >>
			(i * BITS_PER_INDEX_STREAM)) &
			STREAM_MASK;
		current_sd = &current_ld_sd->stream_track[stream_num];
		/* अगर we found a stream, update the raid
		 *  context and also update the mruBitMap
		 */
		/*	boundary condition */
		अगर ((current_sd->next_seq_lba) &&
		    (io_info->ldStartBlock >= current_sd->next_seq_lba) &&
		    (io_info->ldStartBlock <= (current_sd->next_seq_lba + 32)) &&
		    (current_sd->is_पढ़ो == io_info->isRead)) अणु

			अगर ((io_info->ldStartBlock != current_sd->next_seq_lba)	&&
			    ((!io_info->isRead) || (!is_पढ़ो_ahead)))
				/*
				 * Once the API availible we need to change this.
				 * At this poपूर्णांक we are not allowing any gap
				 */
				जारी;

			SET_STREAM_DETECTED(cmd->io_request->RaidContext.raid_context_g35);
			current_sd->next_seq_lba =
			io_info->ldStartBlock + io_info->numBlocks;
			/*
			 *	update the mruBitMap LRU
			 */
			shअगरted_values_mask =
				(1 <<  i * BITS_PER_INDEX_STREAM) - 1;
			shअगरted_values = ((*track_stream & shअगरted_values_mask)
						<< BITS_PER_INDEX_STREAM);
			index_value_mask =
				STREAM_MASK << i * BITS_PER_INDEX_STREAM;
			unshअगरted_values =
				*track_stream & ~(shअगरted_values_mask |
				index_value_mask);
			*track_stream =
				unshअगरted_values | shअगरted_values | stream_num;
			वापस;
		पूर्ण
	पूर्ण
	/*
	 * अगर we did not find any stream, create a new one
	 * from the least recently used
	 */
	stream_num = (*track_stream >>
		((MAX_STREAMS_TRACKED - 1) * BITS_PER_INDEX_STREAM)) &
		STREAM_MASK;
	current_sd = &current_ld_sd->stream_track[stream_num];
	current_sd->is_पढ़ो = io_info->isRead;
	current_sd->next_seq_lba = io_info->ldStartBlock + io_info->numBlocks;
	*track_stream = (((*track_stream & ZERO_LAST_STREAM) << 4) | stream_num);
	वापस;
पूर्ण

/**
 * megasas_set_raidflag_cpu_affinity - This function sets the cpu
 * affinity (cpu of the controller) and raid_flags in the raid context
 * based on IO type.
 *
 * @fusion:		Fusion context
 * @praid_context:	IO RAID context
 * @raid:		LD raid map
 * @fp_possible:	Is fast path possible?
 * @is_पढ़ो:		Is पढ़ो IO?
 * @scsi_buff_len:	SCSI command buffer length
 *
 */
अटल व्योम
megasas_set_raidflag_cpu_affinity(काष्ठा fusion_context *fusion,
				जोड़ RAID_CONTEXT_UNION *praid_context,
				काष्ठा MR_LD_RAID *raid, bool fp_possible,
				u8 is_पढ़ो, u32 scsi_buff_len)
अणु
	u8 cpu_sel = MR_RAID_CTX_CPUSEL_0;
	काष्ठा RAID_CONTEXT_G35 *rctx_g35;

	rctx_g35 = &praid_context->raid_context_g35;
	अगर (fp_possible) अणु
		अगर (is_पढ़ो) अणु
			अगर ((raid->cpuAffinity.pdRead.cpu0) &&
			    (raid->cpuAffinity.pdRead.cpu1))
				cpu_sel = MR_RAID_CTX_CPUSEL_FCFS;
			अन्यथा अगर (raid->cpuAffinity.pdRead.cpu1)
				cpu_sel = MR_RAID_CTX_CPUSEL_1;
		पूर्ण अन्यथा अणु
			अगर ((raid->cpuAffinity.pdWrite.cpu0) &&
			    (raid->cpuAffinity.pdWrite.cpu1))
				cpu_sel = MR_RAID_CTX_CPUSEL_FCFS;
			अन्यथा अगर (raid->cpuAffinity.pdWrite.cpu1)
				cpu_sel = MR_RAID_CTX_CPUSEL_1;
			/* Fast path cache by pass capable R0/R1 VD */
			अगर ((raid->level <= 1) &&
			    (raid->capability.fp_cache_bypass_capable)) अणु
				rctx_g35->routing_flags |=
					(1 << MR_RAID_CTX_ROUTINGFLAGS_SLD_SHIFT);
				rctx_g35->raid_flags =
					(MR_RAID_FLAGS_IO_SUB_TYPE_CACHE_BYPASS
					<< MR_RAID_CTX_RAID_FLAGS_IO_SUB_TYPE_SHIFT);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (is_पढ़ो) अणु
			अगर ((raid->cpuAffinity.ldRead.cpu0) &&
			    (raid->cpuAffinity.ldRead.cpu1))
				cpu_sel = MR_RAID_CTX_CPUSEL_FCFS;
			अन्यथा अगर (raid->cpuAffinity.ldRead.cpu1)
				cpu_sel = MR_RAID_CTX_CPUSEL_1;
		पूर्ण अन्यथा अणु
			अगर ((raid->cpuAffinity.ldWrite.cpu0) &&
			    (raid->cpuAffinity.ldWrite.cpu1))
				cpu_sel = MR_RAID_CTX_CPUSEL_FCFS;
			अन्यथा अगर (raid->cpuAffinity.ldWrite.cpu1)
				cpu_sel = MR_RAID_CTX_CPUSEL_1;

			अगर (is_stream_detected(rctx_g35) &&
			    ((raid->level == 5) || (raid->level == 6)) &&
			    (raid->ग_लिखोMode == MR_RL_WRITE_THROUGH_MODE) &&
			    (cpu_sel == MR_RAID_CTX_CPUSEL_FCFS))
				cpu_sel = MR_RAID_CTX_CPUSEL_0;
		पूर्ण
	पूर्ण

	rctx_g35->routing_flags |=
		(cpu_sel << MR_RAID_CTX_ROUTINGFLAGS_CPUSEL_SHIFT);

	/* Always give priority to MR_RAID_FLAGS_IO_SUB_TYPE_LDIO_BW_LIMIT
	 * vs MR_RAID_FLAGS_IO_SUB_TYPE_CACHE_BYPASS.
	 * IO Subtype is not biपंचांगap.
	 */
	अगर ((fusion->pcie_bw_limitation) && (raid->level == 1) && (!is_पढ़ो) &&
			(scsi_buff_len > MR_LARGE_IO_MIN_SIZE)) अणु
		praid_context->raid_context_g35.raid_flags =
			(MR_RAID_FLAGS_IO_SUB_TYPE_LDIO_BW_LIMIT
			<< MR_RAID_CTX_RAID_FLAGS_IO_SUB_TYPE_SHIFT);
	पूर्ण
पूर्ण

/**
 * megasas_build_ldio_fusion -	Prepares IOs to devices
 * @instance:		Adapter soft state
 * @scp:		SCSI command
 * @cmd:		Command to be prepared
 *
 * Prepares the io_request and chain elements (sg_frame) क्रम IO
 * The IO can be क्रम PD (Fast Path) or LD
 */
अटल व्योम
megasas_build_ldio_fusion(काष्ठा megasas_instance *instance,
			  काष्ठा scsi_cmnd *scp,
			  काष्ठा megasas_cmd_fusion *cmd)
अणु
	bool fp_possible;
	u16 ld;
	u32 start_lba_lo, start_lba_hi, device_id, datalength = 0;
	u32 scsi_buff_len;
	काष्ठा MPI2_RAID_SCSI_IO_REQUEST *io_request;
	काष्ठा IO_REQUEST_INFO io_info;
	काष्ठा fusion_context *fusion;
	काष्ठा MR_DRV_RAID_MAP_ALL *local_map_ptr;
	u8 *raidLUN;
	अचिन्हित दीर्घ spinlock_flags;
	काष्ठा MR_LD_RAID *raid = शून्य;
	काष्ठा MR_PRIV_DEVICE *mrdev_priv;
	काष्ठा RAID_CONTEXT *rctx;
	काष्ठा RAID_CONTEXT_G35 *rctx_g35;

	device_id = MEGASAS_DEV_INDEX(scp);

	fusion = instance->ctrl_context;

	io_request = cmd->io_request;
	rctx = &io_request->RaidContext.raid_context;
	rctx_g35 = &io_request->RaidContext.raid_context_g35;

	rctx->भव_disk_tgt_id = cpu_to_le16(device_id);
	rctx->status = 0;
	rctx->ex_status = 0;

	start_lba_lo = 0;
	start_lba_hi = 0;
	fp_possible = false;

	/*
	 * 6-byte READ(0x08) or WRITE(0x0A) cdb
	 */
	अगर (scp->cmd_len == 6) अणु
		datalength = (u32) scp->cmnd[4];
		start_lba_lo = ((u32) scp->cmnd[1] << 16) |
			((u32) scp->cmnd[2] << 8) | (u32) scp->cmnd[3];

		start_lba_lo &= 0x1FFFFF;
	पूर्ण

	/*
	 * 10-byte READ(0x28) or WRITE(0x2A) cdb
	 */
	अन्यथा अगर (scp->cmd_len == 10) अणु
		datalength = (u32) scp->cmnd[8] |
			((u32) scp->cmnd[7] << 8);
		start_lba_lo = ((u32) scp->cmnd[2] << 24) |
			((u32) scp->cmnd[3] << 16) |
			((u32) scp->cmnd[4] << 8) | (u32) scp->cmnd[5];
	पूर्ण

	/*
	 * 12-byte READ(0xA8) or WRITE(0xAA) cdb
	 */
	अन्यथा अगर (scp->cmd_len == 12) अणु
		datalength = ((u32) scp->cmnd[6] << 24) |
			((u32) scp->cmnd[7] << 16) |
			((u32) scp->cmnd[8] << 8) | (u32) scp->cmnd[9];
		start_lba_lo = ((u32) scp->cmnd[2] << 24) |
			((u32) scp->cmnd[3] << 16) |
			((u32) scp->cmnd[4] << 8) | (u32) scp->cmnd[5];
	पूर्ण

	/*
	 * 16-byte READ(0x88) or WRITE(0x8A) cdb
	 */
	अन्यथा अगर (scp->cmd_len == 16) अणु
		datalength = ((u32) scp->cmnd[10] << 24) |
			((u32) scp->cmnd[11] << 16) |
			((u32) scp->cmnd[12] << 8) | (u32) scp->cmnd[13];
		start_lba_lo = ((u32) scp->cmnd[6] << 24) |
			((u32) scp->cmnd[7] << 16) |
			((u32) scp->cmnd[8] << 8) | (u32) scp->cmnd[9];

		start_lba_hi = ((u32) scp->cmnd[2] << 24) |
			((u32) scp->cmnd[3] << 16) |
			((u32) scp->cmnd[4] << 8) | (u32) scp->cmnd[5];
	पूर्ण

	स_रखो(&io_info, 0, माप(काष्ठा IO_REQUEST_INFO));
	io_info.ldStartBlock = ((u64)start_lba_hi << 32) | start_lba_lo;
	io_info.numBlocks = datalength;
	io_info.ldTgtId = device_id;
	io_info.r1_alt_dev_handle = MR_DEVHANDLE_INVALID;
	scsi_buff_len = scsi_bufflen(scp);
	io_request->DataLength = cpu_to_le32(scsi_buff_len);
	io_info.data_arms = 1;

	अगर (scp->sc_data_direction == DMA_FROM_DEVICE)
		io_info.isRead = 1;

	local_map_ptr = fusion->ld_drv_map[(instance->map_id & 1)];
	ld = MR_TargetIdToLdGet(device_id, local_map_ptr);

	अगर (ld < instance->fw_supported_vd_count)
		raid = MR_LdRaidGet(ld, local_map_ptr);

	अगर (!raid || (!fusion->fast_path_io)) अणु
		rctx->reg_lock_flags  = 0;
		fp_possible = false;
	पूर्ण अन्यथा अणु
		अगर (MR_BuildRaidContext(instance, &io_info, rctx,
					local_map_ptr, &raidLUN))
			fp_possible = (io_info.fpOkForIo > 0) ? true : false;
	पूर्ण

	megasas_get_msix_index(instance, scp, cmd, io_info.data_arms);

	अगर (instance->adapter_type >= VENTURA_SERIES) अणु
		/* FP क्रम Optimal raid level 1.
		 * All large RAID-1 ग_लिखोs (> 32 KiB, both WT and WB modes)
		 * are built by the driver as LD I/Os.
		 * All small RAID-1 WT ग_लिखोs (<= 32 KiB) are built as FP I/Os
		 * (there is never a reason to process these as buffered ग_लिखोs)
		 * All small RAID-1 WB ग_लिखोs (<= 32 KiB) are built as FP I/Os
		 * with the SLD bit निश्चितed.
		 */
		अगर (io_info.r1_alt_dev_handle != MR_DEVHANDLE_INVALID) अणु
			mrdev_priv = scp->device->hostdata;

			अगर (atomic_inc_वापस(&instance->fw_outstanding) >
				(instance->host->can_queue)) अणु
				fp_possible = false;
				atomic_dec(&instance->fw_outstanding);
			पूर्ण अन्यथा अगर (fusion->pcie_bw_limitation &&
				((scsi_buff_len > MR_LARGE_IO_MIN_SIZE) ||
				   (atomic_dec_अगर_positive(&mrdev_priv->r1_ldio_hपूर्णांक) > 0))) अणु
				fp_possible = false;
				atomic_dec(&instance->fw_outstanding);
				अगर (scsi_buff_len > MR_LARGE_IO_MIN_SIZE)
					atomic_set(&mrdev_priv->r1_ldio_hपूर्णांक,
						   instance->r1_ldio_hपूर्णांक_शेष);
			पूर्ण
		पूर्ण

		अगर (!fp_possible ||
		    (io_info.isRead && io_info.ra_capable)) अणु
			spin_lock_irqsave(&instance->stream_lock,
					  spinlock_flags);
			megasas_stream_detect(instance, cmd, &io_info);
			spin_unlock_irqrestore(&instance->stream_lock,
					       spinlock_flags);
			/* In ventura अगर stream detected क्रम a पढ़ो and it is
			 * पढ़ो ahead capable make this IO as LDIO
			 */
			अगर (is_stream_detected(rctx_g35))
				fp_possible = false;
		पूर्ण

		/* If raid is शून्य, set CPU affinity to शेष CPU0 */
		अगर (raid)
			megasas_set_raidflag_cpu_affinity(fusion, &io_request->RaidContext,
				raid, fp_possible, io_info.isRead,
				scsi_buff_len);
		अन्यथा
			rctx_g35->routing_flags |=
				(MR_RAID_CTX_CPUSEL_0 << MR_RAID_CTX_ROUTINGFLAGS_CPUSEL_SHIFT);
	पूर्ण

	अगर (fp_possible) अणु
		megasas_set_pd_lba(io_request, scp->cmd_len, &io_info, scp,
				   local_map_ptr, start_lba_lo);
		io_request->Function = MPI2_FUNCTION_SCSI_IO_REQUEST;
		cmd->request_desc->SCSIIO.RequestFlags =
			(MPI2_REQ_DESCRIPT_FLAGS_FP_IO
			 << MEGASAS_REQ_DESCRIPT_FLAGS_TYPE_SHIFT);
		अगर (instance->adapter_type == INVADER_SERIES) अणु
			rctx->type = MPI2_TYPE_CUDA;
			rctx->nseg = 0x1;
			io_request->IoFlags |= cpu_to_le16(MPI25_SAS_DEVICE0_FLAGS_ENABLED_FAST_PATH);
			rctx->reg_lock_flags |=
			  (MR_RL_FLAGS_GRANT_DESTINATION_CUDA |
			   MR_RL_FLAGS_SEQ_NUM_ENABLE);
		पूर्ण अन्यथा अगर (instance->adapter_type >= VENTURA_SERIES) अणु
			rctx_g35->nseg_type |= (1 << RAID_CONTEXT_NSEG_SHIFT);
			rctx_g35->nseg_type |= (MPI2_TYPE_CUDA << RAID_CONTEXT_TYPE_SHIFT);
			rctx_g35->routing_flags |= (1 << MR_RAID_CTX_ROUTINGFLAGS_SQN_SHIFT);
			io_request->IoFlags |=
				cpu_to_le16(MPI25_SAS_DEVICE0_FLAGS_ENABLED_FAST_PATH);
		पूर्ण
		अगर (fusion->load_balance_info &&
			(fusion->load_balance_info[device_id].loadBalanceFlag) &&
			(io_info.isRead)) अणु
			io_info.devHandle =
				get_updated_dev_handle(instance,
					&fusion->load_balance_info[device_id],
					&io_info, local_map_ptr);
			scp->SCp.Status |= MEGASAS_LOAD_BALANCE_FLAG;
			cmd->pd_r1_lb = io_info.pd_after_lb;
			अगर (instance->adapter_type >= VENTURA_SERIES)
				rctx_g35->span_arm = io_info.span_arm;
			अन्यथा
				rctx->span_arm = io_info.span_arm;

		पूर्ण अन्यथा
			scp->SCp.Status &= ~MEGASAS_LOAD_BALANCE_FLAG;

		अगर (instance->adapter_type >= VENTURA_SERIES)
			cmd->r1_alt_dev_handle = io_info.r1_alt_dev_handle;
		अन्यथा
			cmd->r1_alt_dev_handle = MR_DEVHANDLE_INVALID;

		अगर ((raidLUN[0] == 1) &&
			(local_map_ptr->raidMap.devHndlInfo[io_info.pd_after_lb].validHandles > 1)) अणु
			instance->dev_handle = !(instance->dev_handle);
			io_info.devHandle =
				local_map_ptr->raidMap.devHndlInfo[io_info.pd_after_lb].devHandle[instance->dev_handle];
		पूर्ण

		cmd->request_desc->SCSIIO.DevHandle = io_info.devHandle;
		io_request->DevHandle = io_info.devHandle;
		cmd->pd_पूर्णांकerface = io_info.pd_पूर्णांकerface;
		/* populate the LUN field */
		स_नकल(io_request->LUN, raidLUN, 8);
	पूर्ण अन्यथा अणु
		rctx->समयout_value =
			cpu_to_le16(local_map_ptr->raidMap.fpPdIoTimeoutSec);
		cmd->request_desc->SCSIIO.RequestFlags =
			(MEGASAS_REQ_DESCRIPT_FLAGS_LD_IO
			 << MEGASAS_REQ_DESCRIPT_FLAGS_TYPE_SHIFT);
		अगर (instance->adapter_type == INVADER_SERIES) अणु
			अगर (io_info.करो_fp_rlbypass ||
			(rctx->reg_lock_flags == REGION_TYPE_UNUSED))
				cmd->request_desc->SCSIIO.RequestFlags =
					(MEGASAS_REQ_DESCRIPT_FLAGS_NO_LOCK <<
					MEGASAS_REQ_DESCRIPT_FLAGS_TYPE_SHIFT);
			rctx->type = MPI2_TYPE_CUDA;
			rctx->reg_lock_flags |=
				(MR_RL_FLAGS_GRANT_DESTINATION_CPU0 |
					MR_RL_FLAGS_SEQ_NUM_ENABLE);
			rctx->nseg = 0x1;
		पूर्ण अन्यथा अगर (instance->adapter_type >= VENTURA_SERIES) अणु
			rctx_g35->routing_flags |= (1 << MR_RAID_CTX_ROUTINGFLAGS_SQN_SHIFT);
			rctx_g35->nseg_type |= (1 << RAID_CONTEXT_NSEG_SHIFT);
			rctx_g35->nseg_type |= (MPI2_TYPE_CUDA << RAID_CONTEXT_TYPE_SHIFT);
		पूर्ण
		io_request->Function = MEGASAS_MPI2_FUNCTION_LD_IO_REQUEST;
		io_request->DevHandle = cpu_to_le16(device_id);

	पूर्ण /* Not FP */
पूर्ण

/**
 * megasas_build_ld_nonrw_fusion - prepares non rw ios क्रम भव disk
 * @instance:		Adapter soft state
 * @scmd:		SCSI command
 * @cmd:		Command to be prepared
 *
 * Prepares the io_request frame क्रम non-rw io cmds क्रम vd.
 */
अटल व्योम megasas_build_ld_nonrw_fusion(काष्ठा megasas_instance *instance,
			  काष्ठा scsi_cmnd *scmd, काष्ठा megasas_cmd_fusion *cmd)
अणु
	u32 device_id;
	काष्ठा MPI2_RAID_SCSI_IO_REQUEST *io_request;
	u16 ld;
	काष्ठा MR_DRV_RAID_MAP_ALL *local_map_ptr;
	काष्ठा fusion_context *fusion = instance->ctrl_context;
	u8                          span, physArm;
	__le16                      devHandle;
	u32                         arRef, pd;
	काष्ठा MR_LD_RAID                  *raid;
	काष्ठा RAID_CONTEXT                *pRAID_Context;
	u8 fp_possible = 1;

	io_request = cmd->io_request;
	device_id = MEGASAS_DEV_INDEX(scmd);
	local_map_ptr = fusion->ld_drv_map[(instance->map_id & 1)];
	io_request->DataLength = cpu_to_le32(scsi_bufflen(scmd));
	/* get RAID_Context poपूर्णांकer */
	pRAID_Context = &io_request->RaidContext.raid_context;
	/* Check with FW team */
	pRAID_Context->भव_disk_tgt_id = cpu_to_le16(device_id);
	pRAID_Context->reg_lock_row_lba    = 0;
	pRAID_Context->reg_lock_length    = 0;

	अगर (fusion->fast_path_io && (
		device_id < instance->fw_supported_vd_count)) अणु

		ld = MR_TargetIdToLdGet(device_id, local_map_ptr);
		अगर (ld >= instance->fw_supported_vd_count - 1)
			fp_possible = 0;
		अन्यथा अणु
			raid = MR_LdRaidGet(ld, local_map_ptr);
			अगर (!(raid->capability.fpNonRWCapable))
				fp_possible = 0;
		पूर्ण
	पूर्ण अन्यथा
		fp_possible = 0;

	अगर (!fp_possible) अणु
		io_request->Function  = MEGASAS_MPI2_FUNCTION_LD_IO_REQUEST;
		io_request->DevHandle = cpu_to_le16(device_id);
		io_request->LUN[1] = scmd->device->lun;
		pRAID_Context->समयout_value =
			cpu_to_le16 (scmd->request->समयout / HZ);
		cmd->request_desc->SCSIIO.RequestFlags =
			(MPI2_REQ_DESCRIPT_FLAGS_SCSI_IO <<
			MEGASAS_REQ_DESCRIPT_FLAGS_TYPE_SHIFT);
	पूर्ण अन्यथा अणु

		/* set RAID context values */
		pRAID_Context->config_seq_num = raid->seqNum;
		अगर (instance->adapter_type < VENTURA_SERIES)
			pRAID_Context->reg_lock_flags = REGION_TYPE_SHARED_READ;
		pRAID_Context->समयout_value =
			cpu_to_le16(raid->fpIoTimeoutForLd);

		/* get the DevHandle क्रम the PD (since this is
		   fpNonRWCapable, this is a single disk RAID0) */
		span = physArm = 0;
		arRef = MR_LdSpanArrayGet(ld, span, local_map_ptr);
		pd = MR_ArPdGet(arRef, physArm, local_map_ptr);
		devHandle = MR_PdDevHandleGet(pd, local_map_ptr);

		/* build request descriptor */
		cmd->request_desc->SCSIIO.RequestFlags =
			(MPI2_REQ_DESCRIPT_FLAGS_FP_IO <<
			MEGASAS_REQ_DESCRIPT_FLAGS_TYPE_SHIFT);
		cmd->request_desc->SCSIIO.DevHandle = devHandle;

		/* populate the LUN field */
		स_नकल(io_request->LUN, raid->LUN, 8);

		/* build the raidScsiIO काष्ठाure */
		io_request->Function = MPI2_FUNCTION_SCSI_IO_REQUEST;
		io_request->DevHandle = devHandle;
	पूर्ण
पूर्ण

/**
 * megasas_build_syspd_fusion - prepares rw/non-rw ios क्रम syspd
 * @instance:		Adapter soft state
 * @scmd:		SCSI command
 * @cmd:		Command to be prepared
 * @fp_possible:	parameter to detect fast path or firmware path io.
 *
 * Prepares the io_request frame क्रम rw/non-rw io cmds क्रम syspds
 */
अटल व्योम
megasas_build_syspd_fusion(काष्ठा megasas_instance *instance,
	काष्ठा scsi_cmnd *scmd, काष्ठा megasas_cmd_fusion *cmd,
	bool fp_possible)
अणु
	u32 device_id;
	काष्ठा MPI2_RAID_SCSI_IO_REQUEST *io_request;
	u16 pd_index = 0;
	u16 os_समयout_value;
	u16 समयout_limit;
	काष्ठा MR_DRV_RAID_MAP_ALL *local_map_ptr;
	काष्ठा RAID_CONTEXT	*pRAID_Context;
	काष्ठा MR_PD_CFG_SEQ_NUM_SYNC *pd_sync;
	काष्ठा MR_PRIV_DEVICE *mr_device_priv_data;
	काष्ठा fusion_context *fusion = instance->ctrl_context;
	pd_sync = (व्योम *)fusion->pd_seq_sync[(instance->pd_seq_map_id - 1) & 1];

	device_id = MEGASAS_DEV_INDEX(scmd);
	pd_index = MEGASAS_PD_INDEX(scmd);
	os_समयout_value = scmd->request->समयout / HZ;
	mr_device_priv_data = scmd->device->hostdata;
	cmd->pd_पूर्णांकerface = mr_device_priv_data->पूर्णांकerface_type;

	io_request = cmd->io_request;
	/* get RAID_Context poपूर्णांकer */
	pRAID_Context = &io_request->RaidContext.raid_context;
	pRAID_Context->reg_lock_flags = 0;
	pRAID_Context->reg_lock_row_lba = 0;
	pRAID_Context->reg_lock_length = 0;
	io_request->DataLength = cpu_to_le32(scsi_bufflen(scmd));
	io_request->LUN[1] = scmd->device->lun;
	pRAID_Context->raid_flags = MR_RAID_FLAGS_IO_SUB_TYPE_SYSTEM_PD
		<< MR_RAID_CTX_RAID_FLAGS_IO_SUB_TYPE_SHIFT;

	/* If FW supports PD sequence number */
	अगर (instance->support_seqnum_jbod_fp) अणु
		अगर (instance->use_seqnum_jbod_fp &&
			instance->pd_list[pd_index].driveType == TYPE_DISK) अणु

			/* More than 256 PD/JBOD support क्रम Ventura */
			अगर (instance->support_morethan256jbod)
				pRAID_Context->भव_disk_tgt_id =
					pd_sync->seq[pd_index].pd_target_id;
			अन्यथा
				pRAID_Context->भव_disk_tgt_id =
					cpu_to_le16(device_id +
					(MAX_PHYSICAL_DEVICES - 1));
			pRAID_Context->config_seq_num =
				pd_sync->seq[pd_index].seqNum;
			io_request->DevHandle =
				pd_sync->seq[pd_index].devHandle;
			अगर (instance->adapter_type >= VENTURA_SERIES) अणु
				io_request->RaidContext.raid_context_g35.routing_flags |=
					(1 << MR_RAID_CTX_ROUTINGFLAGS_SQN_SHIFT);
				io_request->RaidContext.raid_context_g35.nseg_type |=
					(1 << RAID_CONTEXT_NSEG_SHIFT);
				io_request->RaidContext.raid_context_g35.nseg_type |=
					(MPI2_TYPE_CUDA << RAID_CONTEXT_TYPE_SHIFT);
			पूर्ण अन्यथा अणु
				pRAID_Context->type = MPI2_TYPE_CUDA;
				pRAID_Context->nseg = 0x1;
				pRAID_Context->reg_lock_flags |=
					(MR_RL_FLAGS_SEQ_NUM_ENABLE |
					 MR_RL_FLAGS_GRANT_DESTINATION_CUDA);
			पूर्ण
		पूर्ण अन्यथा अणु
			pRAID_Context->भव_disk_tgt_id =
				cpu_to_le16(device_id +
				(MAX_PHYSICAL_DEVICES - 1));
			pRAID_Context->config_seq_num = 0;
			io_request->DevHandle = cpu_to_le16(0xFFFF);
		पूर्ण
	पूर्ण अन्यथा अणु
		pRAID_Context->भव_disk_tgt_id = cpu_to_le16(device_id);
		pRAID_Context->config_seq_num = 0;

		अगर (fusion->fast_path_io) अणु
			local_map_ptr =
				fusion->ld_drv_map[(instance->map_id & 1)];
			io_request->DevHandle =
				local_map_ptr->raidMap.devHndlInfo[device_id].curDevHdl;
		पूर्ण अन्यथा अणु
			io_request->DevHandle = cpu_to_le16(0xFFFF);
		पूर्ण
	पूर्ण

	cmd->request_desc->SCSIIO.DevHandle = io_request->DevHandle;

	megasas_get_msix_index(instance, scmd, cmd, 1);

	अगर (!fp_possible) अणु
		/* प्रणाली pd firmware path */
		io_request->Function  = MEGASAS_MPI2_FUNCTION_LD_IO_REQUEST;
		cmd->request_desc->SCSIIO.RequestFlags =
			(MPI2_REQ_DESCRIPT_FLAGS_SCSI_IO <<
				MEGASAS_REQ_DESCRIPT_FLAGS_TYPE_SHIFT);
		pRAID_Context->समयout_value = cpu_to_le16(os_समयout_value);
		pRAID_Context->भव_disk_tgt_id = cpu_to_le16(device_id);
	पूर्ण अन्यथा अणु
		अगर (os_समयout_value)
			os_समयout_value++;

		/* प्रणाली pd Fast Path */
		io_request->Function = MPI2_FUNCTION_SCSI_IO_REQUEST;
		समयout_limit = (scmd->device->type == TYPE_DISK) ?
				255 : 0xFFFF;
		pRAID_Context->समयout_value =
			cpu_to_le16((os_समयout_value > समयout_limit) ?
			समयout_limit : os_समयout_value);
		अगर (instance->adapter_type >= INVADER_SERIES)
			io_request->IoFlags |=
				cpu_to_le16(MPI25_SAS_DEVICE0_FLAGS_ENABLED_FAST_PATH);

		cmd->request_desc->SCSIIO.RequestFlags =
			(MPI2_REQ_DESCRIPT_FLAGS_FP_IO <<
				MEGASAS_REQ_DESCRIPT_FLAGS_TYPE_SHIFT);
	पूर्ण
पूर्ण

/**
 * megasas_build_io_fusion -	Prepares IOs to devices
 * @instance:		Adapter soft state
 * @scp:		SCSI command
 * @cmd:		Command to be prepared
 *
 * Invokes helper functions to prepare request frames
 * and sets flags appropriate क्रम IO/Non-IO cmd
 */
अटल पूर्णांक
megasas_build_io_fusion(काष्ठा megasas_instance *instance,
			काष्ठा scsi_cmnd *scp,
			काष्ठा megasas_cmd_fusion *cmd)
अणु
	पूर्णांक sge_count;
	u8  cmd_type;
	काष्ठा MPI2_RAID_SCSI_IO_REQUEST *io_request = cmd->io_request;
	काष्ठा MR_PRIV_DEVICE *mr_device_priv_data;
	mr_device_priv_data = scp->device->hostdata;

	/* Zero out some fields so they करोn't get reused */
	स_रखो(io_request->LUN, 0x0, 8);
	io_request->CDB.EEDP32.PrimaryReferenceTag = 0;
	io_request->CDB.EEDP32.PrimaryApplicationTagMask = 0;
	io_request->EEDPFlags = 0;
	io_request->Control = 0;
	io_request->EEDPBlockSize = 0;
	io_request->ChainOffset = 0;
	io_request->RaidContext.raid_context.raid_flags = 0;
	io_request->RaidContext.raid_context.type = 0;
	io_request->RaidContext.raid_context.nseg = 0;

	स_नकल(io_request->CDB.CDB32, scp->cmnd, scp->cmd_len);
	/*
	 * Just the CDB length,rest of the Flags are zero
	 * This will be modअगरied क्रम FP in build_ldio_fusion
	 */
	io_request->IoFlags = cpu_to_le16(scp->cmd_len);

	चयन (cmd_type = megasas_cmd_type(scp)) अणु
	हाल READ_WRITE_LDIO:
		megasas_build_ldio_fusion(instance, scp, cmd);
		अवरोध;
	हाल NON_READ_WRITE_LDIO:
		megasas_build_ld_nonrw_fusion(instance, scp, cmd);
		अवरोध;
	हाल READ_WRITE_SYSPDIO:
		megasas_build_syspd_fusion(instance, scp, cmd, true);
		अवरोध;
	हाल NON_READ_WRITE_SYSPDIO:
		अगर (instance->secure_jbod_support ||
		    mr_device_priv_data->is_पंचांग_capable)
			megasas_build_syspd_fusion(instance, scp, cmd, false);
		अन्यथा
			megasas_build_syspd_fusion(instance, scp, cmd, true);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * Conकाष्ठा SGL
	 */

	sge_count = megasas_make_sgl(instance, scp, cmd);

	अगर (sge_count > instance->max_num_sge || (sge_count < 0)) अणु
		dev_err(&instance->pdev->dev,
			"%s %d sge_count (%d) is out of range. Range is:  0-%d\n",
			__func__, __LINE__, sge_count, instance->max_num_sge);
		वापस 1;
	पूर्ण

	अगर (instance->adapter_type >= VENTURA_SERIES) अणु
		set_num_sge(&io_request->RaidContext.raid_context_g35, sge_count);
		cpu_to_le16s(&io_request->RaidContext.raid_context_g35.routing_flags);
		cpu_to_le16s(&io_request->RaidContext.raid_context_g35.nseg_type);
	पूर्ण अन्यथा अणु
		/* numSGE store lower 8 bit of sge_count.
		 * numSGEExt store higher 8 bit of sge_count
		 */
		io_request->RaidContext.raid_context.num_sge = sge_count;
		io_request->RaidContext.raid_context.num_sge_ext =
			(u8)(sge_count >> 8);
	पूर्ण

	io_request->SGLFlags = cpu_to_le16(MPI2_SGE_FLAGS_64_BIT_ADDRESSING);

	अगर (scp->sc_data_direction == DMA_TO_DEVICE)
		io_request->Control |= cpu_to_le32(MPI2_SCSIIO_CONTROL_WRITE);
	अन्यथा अगर (scp->sc_data_direction == DMA_FROM_DEVICE)
		io_request->Control |= cpu_to_le32(MPI2_SCSIIO_CONTROL_READ);

	io_request->SGLOffset0 =
		दुरत्व(काष्ठा MPI2_RAID_SCSI_IO_REQUEST, SGL) / 4;

	io_request->SenseBufferLowAddress =
		cpu_to_le32(lower_32_bits(cmd->sense_phys_addr));
	io_request->SenseBufferLength = SCSI_SENSE_BUFFERSIZE;

	cmd->scmd = scp;
	scp->SCp.ptr = (अक्षर *)cmd;

	वापस 0;
पूर्ण

अटल जोड़ MEGASAS_REQUEST_DESCRIPTOR_UNION *
megasas_get_request_descriptor(काष्ठा megasas_instance *instance, u16 index)
अणु
	u8 *p;
	काष्ठा fusion_context *fusion;

	fusion = instance->ctrl_context;
	p = fusion->req_frames_desc +
		माप(जोड़ MEGASAS_REQUEST_DESCRIPTOR_UNION) * index;

	वापस (जोड़ MEGASAS_REQUEST_DESCRIPTOR_UNION *)p;
पूर्ण


/* megasas_prepate_secondRaid1_IO
 *  It prepares the raid 1 second IO
 */
अटल व्योम megasas_prepare_secondRaid1_IO(काष्ठा megasas_instance *instance,
					   काष्ठा megasas_cmd_fusion *cmd,
					   काष्ठा megasas_cmd_fusion *r1_cmd)
अणु
	जोड़ MEGASAS_REQUEST_DESCRIPTOR_UNION *req_desc, *req_desc2 = शून्य;
	काष्ठा fusion_context *fusion;
	fusion = instance->ctrl_context;
	req_desc = cmd->request_desc;
	/* copy the io request frame as well as 8 SGEs data क्रम r1 command*/
	स_नकल(r1_cmd->io_request, cmd->io_request,
	       (माप(काष्ठा MPI2_RAID_SCSI_IO_REQUEST)));
	स_नकल(&r1_cmd->io_request->SGL, &cmd->io_request->SGL,
	       (fusion->max_sge_in_मुख्य_msg * माप(जोड़ MPI2_SGE_IO_UNION)));
	/*sense buffer is dअगरferent क्रम r1 command*/
	r1_cmd->io_request->SenseBufferLowAddress =
			cpu_to_le32(lower_32_bits(r1_cmd->sense_phys_addr));
	r1_cmd->scmd = cmd->scmd;
	req_desc2 = megasas_get_request_descriptor(instance,
						   (r1_cmd->index - 1));
	req_desc2->Words = 0;
	r1_cmd->request_desc = req_desc2;
	req_desc2->SCSIIO.SMID = cpu_to_le16(r1_cmd->index);
	req_desc2->SCSIIO.RequestFlags = req_desc->SCSIIO.RequestFlags;
	r1_cmd->request_desc->SCSIIO.DevHandle = cmd->r1_alt_dev_handle;
	r1_cmd->io_request->DevHandle = cmd->r1_alt_dev_handle;
	r1_cmd->r1_alt_dev_handle = cmd->io_request->DevHandle;
	cmd->io_request->RaidContext.raid_context_g35.flow_specअगरic.peer_smid =
			cpu_to_le16(r1_cmd->index);
	r1_cmd->io_request->RaidContext.raid_context_g35.flow_specअगरic.peer_smid =
			cpu_to_le16(cmd->index);
	/*MSIxIndex of both commands request descriptors should be same*/
	r1_cmd->request_desc->SCSIIO.MSIxIndex =
			cmd->request_desc->SCSIIO.MSIxIndex;
	/*span arm is dअगरferent क्रम r1 cmd*/
	r1_cmd->io_request->RaidContext.raid_context_g35.span_arm =
			cmd->io_request->RaidContext.raid_context_g35.span_arm + 1;
पूर्ण

/**
 * megasas_build_and_issue_cmd_fusion -Main routine क्रम building and
 *                                     issuing non IOCTL cmd
 * @instance:			Adapter soft state
 * @scmd:			poपूर्णांकer to scsi cmd from OS
 */
अटल u32
megasas_build_and_issue_cmd_fusion(काष्ठा megasas_instance *instance,
				   काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा megasas_cmd_fusion *cmd, *r1_cmd = शून्य;
	जोड़ MEGASAS_REQUEST_DESCRIPTOR_UNION *req_desc;
	u32 index;

	अगर ((megasas_cmd_type(scmd) == READ_WRITE_LDIO) &&
		instance->ldio_threshold &&
		(atomic_inc_वापस(&instance->ldio_outstanding) >
		instance->ldio_threshold)) अणु
		atomic_dec(&instance->ldio_outstanding);
		वापस SCSI_MLQUEUE_DEVICE_BUSY;
	पूर्ण

	अगर (atomic_inc_वापस(&instance->fw_outstanding) >
			instance->host->can_queue) अणु
		atomic_dec(&instance->fw_outstanding);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	cmd = megasas_get_cmd_fusion(instance, scmd->request->tag);

	अगर (!cmd) अणु
		atomic_dec(&instance->fw_outstanding);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	index = cmd->index;

	req_desc = megasas_get_request_descriptor(instance, index-1);

	req_desc->Words = 0;
	cmd->request_desc = req_desc;

	अगर (megasas_build_io_fusion(instance, scmd, cmd)) अणु
		megasas_वापस_cmd_fusion(instance, cmd);
		dev_err(&instance->pdev->dev, "Error building command\n");
		cmd->request_desc = शून्य;
		atomic_dec(&instance->fw_outstanding);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	req_desc = cmd->request_desc;
	req_desc->SCSIIO.SMID = cpu_to_le16(index);

	अगर (cmd->io_request->ChainOffset != 0 &&
	    cmd->io_request->ChainOffset != 0xF)
		dev_err(&instance->pdev->dev, "The chain offset value is not "
		       "correct : %x\n", cmd->io_request->ChainOffset);
	/*
	 *	अगर it is raid 1/10 fp ग_लिखो capable.
	 *	try to get second command from pool and स्थिरruct it.
	 *	From FW, it has confirmed that lba values of two PDs
	 *	corresponds to single R1/10 LD are always same
	 *
	 */
	/*	driver side count always should be less than max_fw_cmds
	 *	to get new command
	 */
	अगर (cmd->r1_alt_dev_handle != MR_DEVHANDLE_INVALID) अणु
		r1_cmd = megasas_get_cmd_fusion(instance,
				(scmd->request->tag + instance->max_fw_cmds));
		megasas_prepare_secondRaid1_IO(instance, cmd, r1_cmd);
	पूर्ण


	/*
	 * Issue the command to the FW
	 */

	megasas_sdev_busy_inc(instance, scmd);
	megasas_fire_cmd_fusion(instance, req_desc);

	अगर (r1_cmd)
		megasas_fire_cmd_fusion(instance, r1_cmd->request_desc);


	वापस 0;
पूर्ण

/**
 * megasas_complete_r1_command -
 * completes R1 FP ग_लिखो commands which has valid peer smid
 * @instance:			Adapter soft state
 * @cmd:			MPT command frame
 *
 */
अटल अंतरभूत व्योम
megasas_complete_r1_command(काष्ठा megasas_instance *instance,
			    काष्ठा megasas_cmd_fusion *cmd)
अणु
	u8 *sense, status, ex_status;
	u32 data_length;
	u16 peer_smid;
	काष्ठा fusion_context *fusion;
	काष्ठा megasas_cmd_fusion *r1_cmd = शून्य;
	काष्ठा scsi_cmnd *scmd_local = शून्य;
	काष्ठा RAID_CONTEXT_G35 *rctx_g35;

	rctx_g35 = &cmd->io_request->RaidContext.raid_context_g35;
	fusion = instance->ctrl_context;
	peer_smid = le16_to_cpu(rctx_g35->flow_specअगरic.peer_smid);

	r1_cmd = fusion->cmd_list[peer_smid - 1];
	scmd_local = cmd->scmd;
	status = rctx_g35->status;
	ex_status = rctx_g35->ex_status;
	data_length = cmd->io_request->DataLength;
	sense = cmd->sense;

	cmd->cmd_completed = true;

	/* Check अगर peer command is completed or not*/
	अगर (r1_cmd->cmd_completed) अणु
		rctx_g35 = &r1_cmd->io_request->RaidContext.raid_context_g35;
		अगर (rctx_g35->status != MFI_STAT_OK) अणु
			status = rctx_g35->status;
			ex_status = rctx_g35->ex_status;
			data_length = r1_cmd->io_request->DataLength;
			sense = r1_cmd->sense;
		पूर्ण

		megasas_वापस_cmd_fusion(instance, r1_cmd);
		map_cmd_status(fusion, scmd_local, status, ex_status,
			       le32_to_cpu(data_length), sense);
		अगर (instance->ldio_threshold &&
		    megasas_cmd_type(scmd_local) == READ_WRITE_LDIO)
			atomic_dec(&instance->ldio_outstanding);
		scmd_local->SCp.ptr = शून्य;
		megasas_वापस_cmd_fusion(instance, cmd);
		scsi_dma_unmap(scmd_local);
		megasas_sdev_busy_dec(instance, scmd_local);
		scmd_local->scsi_करोne(scmd_local);
	पूर्ण
पूर्ण

/**
 * complete_cmd_fusion -	Completes command
 * @instance:			Adapter soft state
 * @MSIxIndex:			MSI number
 * @irq_context:		IRQ context
 *
 * Completes all commands that is in reply descriptor queue
 */
अटल पूर्णांक
complete_cmd_fusion(काष्ठा megasas_instance *instance, u32 MSIxIndex,
		    काष्ठा megasas_irq_context *irq_context)
अणु
	जोड़ MPI2_REPLY_DESCRIPTORS_UNION *desc;
	काष्ठा MPI2_SCSI_IO_SUCCESS_REPLY_DESCRIPTOR *reply_desc;
	काष्ठा MPI2_RAID_SCSI_IO_REQUEST *scsi_io_req;
	काष्ठा fusion_context *fusion;
	काष्ठा megasas_cmd *cmd_mfi;
	काष्ठा megasas_cmd_fusion *cmd_fusion;
	u16 smid, num_completed;
	u8 reply_descript_type, *sense, status, extStatus;
	u32 device_id, data_length;
	जोड़ desc_value d_val;
	काष्ठा LD_LOAD_BALANCE_INFO *lbinfo;
	पूर्णांक threshold_reply_count = 0;
	काष्ठा scsi_cmnd *scmd_local = शून्य;
	काष्ठा MR_TASK_MANAGE_REQUEST *mr_पंचांग_req;
	काष्ठा MPI2_SCSI_TASK_MANAGE_REQUEST *mpi_पंचांग_req;

	fusion = instance->ctrl_context;

	अगर (atomic_पढ़ो(&instance->adprecovery) == MEGASAS_HW_CRITICAL_ERROR)
		वापस IRQ_HANDLED;

	desc = fusion->reply_frames_desc[MSIxIndex] +
				fusion->last_reply_idx[MSIxIndex];

	reply_desc = (काष्ठा MPI2_SCSI_IO_SUCCESS_REPLY_DESCRIPTOR *)desc;

	d_val.word = desc->Words;

	reply_descript_type = reply_desc->ReplyFlags &
		MPI2_RPY_DESCRIPT_FLAGS_TYPE_MASK;

	अगर (reply_descript_type == MPI2_RPY_DESCRIPT_FLAGS_UNUSED)
		वापस IRQ_NONE;

	अगर (irq_context && !atomic_add_unless(&irq_context->in_used, 1, 1))
		वापस 0;

	num_completed = 0;

	जबतक (d_val.u.low != cpu_to_le32(अच_पूर्णांक_उच्च) &&
	       d_val.u.high != cpu_to_le32(अच_पूर्णांक_उच्च)) अणु

		smid = le16_to_cpu(reply_desc->SMID);
		cmd_fusion = fusion->cmd_list[smid - 1];
		scsi_io_req = (काष्ठा MPI2_RAID_SCSI_IO_REQUEST *)
						cmd_fusion->io_request;

		scmd_local = cmd_fusion->scmd;
		status = scsi_io_req->RaidContext.raid_context.status;
		extStatus = scsi_io_req->RaidContext.raid_context.ex_status;
		sense = cmd_fusion->sense;
		data_length = scsi_io_req->DataLength;

		चयन (scsi_io_req->Function) अणु
		हाल MPI2_FUNCTION_SCSI_TASK_MGMT:
			mr_पंचांग_req = (काष्ठा MR_TASK_MANAGE_REQUEST *)
						cmd_fusion->io_request;
			mpi_पंचांग_req = (काष्ठा MPI2_SCSI_TASK_MANAGE_REQUEST *)
						&mr_पंचांग_req->TmRequest;
			dev_dbg(&instance->pdev->dev, "TM completion:"
				"type: 0x%x TaskMID: 0x%x\n",
				mpi_पंचांग_req->TaskType, mpi_पंचांग_req->TaskMID);
			complete(&cmd_fusion->करोne);
			अवरोध;
		हाल MPI2_FUNCTION_SCSI_IO_REQUEST:  /*Fast Path IO.*/
			/* Update load balancing info */
			अगर (fusion->load_balance_info &&
			    (cmd_fusion->scmd->SCp.Status &
			    MEGASAS_LOAD_BALANCE_FLAG)) अणु
				device_id = MEGASAS_DEV_INDEX(scmd_local);
				lbinfo = &fusion->load_balance_info[device_id];
				atomic_dec(&lbinfo->scsi_pending_cmds[cmd_fusion->pd_r1_lb]);
				cmd_fusion->scmd->SCp.Status &= ~MEGASAS_LOAD_BALANCE_FLAG;
			पूर्ण
			fallthrough;	/* and complete IO */
		हाल MEGASAS_MPI2_FUNCTION_LD_IO_REQUEST: /* LD-IO Path */
			atomic_dec(&instance->fw_outstanding);
			अगर (cmd_fusion->r1_alt_dev_handle == MR_DEVHANDLE_INVALID) अणु
				map_cmd_status(fusion, scmd_local, status,
					       extStatus, le32_to_cpu(data_length),
					       sense);
				अगर (instance->ldio_threshold &&
				    (megasas_cmd_type(scmd_local) == READ_WRITE_LDIO))
					atomic_dec(&instance->ldio_outstanding);
				scmd_local->SCp.ptr = शून्य;
				megasas_वापस_cmd_fusion(instance, cmd_fusion);
				scsi_dma_unmap(scmd_local);
				megasas_sdev_busy_dec(instance, scmd_local);
				scmd_local->scsi_करोne(scmd_local);
			पूर्ण अन्यथा	/* Optimal VD - R1 FP command completion. */
				megasas_complete_r1_command(instance, cmd_fusion);
			अवरोध;
		हाल MEGASAS_MPI2_FUNCTION_PASSTHRU_IO_REQUEST: /*MFI command */
			cmd_mfi = instance->cmd_list[cmd_fusion->sync_cmd_idx];
			/* Poll mode. Dummy मुक्त.
			 * In हाल of Interrupt mode, caller has reverse check.
			 */
			अगर (cmd_mfi->flags & DRV_DCMD_POLLED_MODE) अणु
				cmd_mfi->flags &= ~DRV_DCMD_POLLED_MODE;
				megasas_वापस_cmd(instance, cmd_mfi);
			पूर्ण अन्यथा
				megasas_complete_cmd(instance, cmd_mfi, DID_OK);
			अवरोध;
		पूर्ण

		fusion->last_reply_idx[MSIxIndex]++;
		अगर (fusion->last_reply_idx[MSIxIndex] >=
		    fusion->reply_q_depth)
			fusion->last_reply_idx[MSIxIndex] = 0;

		desc->Words = cpu_to_le64(ULदीर्घ_उच्च);
		num_completed++;
		threshold_reply_count++;

		/* Get the next reply descriptor */
		अगर (!fusion->last_reply_idx[MSIxIndex])
			desc = fusion->reply_frames_desc[MSIxIndex];
		अन्यथा
			desc++;

		reply_desc =
		  (काष्ठा MPI2_SCSI_IO_SUCCESS_REPLY_DESCRIPTOR *)desc;

		d_val.word = desc->Words;

		reply_descript_type = reply_desc->ReplyFlags &
			MPI2_RPY_DESCRIPT_FLAGS_TYPE_MASK;

		अगर (reply_descript_type == MPI2_RPY_DESCRIPT_FLAGS_UNUSED)
			अवरोध;
		/*
		 * Write to reply post host index रेजिस्टर after completing threshold
		 * number of reply counts and still there are more replies in reply queue
		 * pending to be completed
		 */
		अगर (threshold_reply_count >= instance->threshold_reply_count) अणु
			अगर (instance->msix_combined)
				ग_लिखोl(((MSIxIndex & 0x7) << 24) |
					fusion->last_reply_idx[MSIxIndex],
					instance->reply_post_host_index_addr[MSIxIndex/8]);
			अन्यथा
				ग_लिखोl((MSIxIndex << 24) |
					fusion->last_reply_idx[MSIxIndex],
					instance->reply_post_host_index_addr[0]);
			threshold_reply_count = 0;
			अगर (irq_context) अणु
				अगर (!irq_context->irq_poll_scheduled) अणु
					irq_context->irq_poll_scheduled = true;
					irq_context->irq_line_enable = true;
					irq_poll_sched(&irq_context->irqpoll);
				पूर्ण
				atomic_dec(&irq_context->in_used);
				वापस num_completed;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (num_completed) अणु
		wmb();
		अगर (instance->msix_combined)
			ग_लिखोl(((MSIxIndex & 0x7) << 24) |
				fusion->last_reply_idx[MSIxIndex],
				instance->reply_post_host_index_addr[MSIxIndex/8]);
		अन्यथा
			ग_लिखोl((MSIxIndex << 24) |
				fusion->last_reply_idx[MSIxIndex],
				instance->reply_post_host_index_addr[0]);
		megasas_check_and_restore_queue_depth(instance);
	पूर्ण

	अगर (irq_context)
		atomic_dec(&irq_context->in_used);

	वापस num_completed;
पूर्ण

पूर्णांक megasas_blk_mq_poll(काष्ठा Scsi_Host *shost, अचिन्हित पूर्णांक queue_num)
अणु

	काष्ठा megasas_instance *instance;
	पूर्णांक num_entries = 0;
	काष्ठा fusion_context *fusion;

	instance = (काष्ठा megasas_instance *)shost->hostdata;

	fusion = instance->ctrl_context;

	queue_num = queue_num + instance->low_latency_index_start;

	अगर (!atomic_add_unless(&fusion->busy_mq_poll[queue_num], 1, 1))
		वापस 0;

	num_entries = complete_cmd_fusion(instance, queue_num, शून्य);
	atomic_dec(&fusion->busy_mq_poll[queue_num]);

	वापस num_entries;
पूर्ण

/**
 * megasas_enable_irq_poll() - enable irqpoll
 * @instance:			Adapter soft state
 */
अटल व्योम megasas_enable_irq_poll(काष्ठा megasas_instance *instance)
अणु
	u32 count, i;
	काष्ठा megasas_irq_context *irq_ctx;

	count = instance->msix_vectors > 0 ? instance->msix_vectors : 1;

	क्रम (i = 0; i < count; i++) अणु
		irq_ctx = &instance->irq_context[i];
		irq_poll_enable(&irq_ctx->irqpoll);
	पूर्ण
पूर्ण

/**
 * megasas_sync_irqs -	Synchronizes all IRQs owned by adapter
 * @instance_addr:			Adapter soft state address
 */
अटल व्योम megasas_sync_irqs(अचिन्हित दीर्घ instance_addr)
अणु
	u32 count, i;
	काष्ठा megasas_instance *instance =
		(काष्ठा megasas_instance *)instance_addr;
	काष्ठा megasas_irq_context *irq_ctx;

	count = instance->msix_vectors > 0 ? instance->msix_vectors : 1;

	क्रम (i = 0; i < count; i++) अणु
		synchronize_irq(pci_irq_vector(instance->pdev, i));
		irq_ctx = &instance->irq_context[i];
		irq_poll_disable(&irq_ctx->irqpoll);
		अगर (irq_ctx->irq_poll_scheduled) अणु
			irq_ctx->irq_poll_scheduled = false;
			enable_irq(irq_ctx->os_irq);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * megasas_irqpoll() - process a queue क्रम completed reply descriptors
 * @irqpoll:	IRQ poll काष्ठाure associated with queue to poll.
 * @budget:	Threshold of reply descriptors to process per poll.
 *
 * Return: The number of entries processed.
 */

पूर्णांक megasas_irqpoll(काष्ठा irq_poll *irqpoll, पूर्णांक budget)
अणु
	काष्ठा megasas_irq_context *irq_ctx;
	काष्ठा megasas_instance *instance;
	पूर्णांक num_entries;

	irq_ctx = container_of(irqpoll, काष्ठा megasas_irq_context, irqpoll);
	instance = irq_ctx->instance;

	अगर (irq_ctx->irq_line_enable) अणु
		disable_irq_nosync(irq_ctx->os_irq);
		irq_ctx->irq_line_enable = false;
	पूर्ण

	num_entries = complete_cmd_fusion(instance, irq_ctx->MSIxIndex, irq_ctx);
	अगर (num_entries < budget) अणु
		irq_poll_complete(irqpoll);
		irq_ctx->irq_poll_scheduled = false;
		enable_irq(irq_ctx->os_irq);
	पूर्ण

	वापस num_entries;
पूर्ण

/**
 * megasas_complete_cmd_dpc_fusion -	Completes command
 * @instance_addr:			Adapter soft state address
 *
 * Tasklet to complete cmds
 */
अटल व्योम
megasas_complete_cmd_dpc_fusion(अचिन्हित दीर्घ instance_addr)
अणु
	काष्ठा megasas_instance *instance =
		(काष्ठा megasas_instance *)instance_addr;
	u32 count, MSIxIndex;

	count = instance->msix_vectors > 0 ? instance->msix_vectors : 1;

	/* If we have alपढ़ोy declared adapter dead, करोnot complete cmds */
	अगर (atomic_पढ़ो(&instance->adprecovery) == MEGASAS_HW_CRITICAL_ERROR)
		वापस;

	क्रम (MSIxIndex = 0 ; MSIxIndex < count; MSIxIndex++)
		complete_cmd_fusion(instance, MSIxIndex, शून्य);
पूर्ण

/**
 * megasas_isr_fusion - isr entry poपूर्णांक
 * @irq:	IRQ number
 * @devp:	IRQ context
 */
अटल irqवापस_t megasas_isr_fusion(पूर्णांक irq, व्योम *devp)
अणु
	काष्ठा megasas_irq_context *irq_context = devp;
	काष्ठा megasas_instance *instance = irq_context->instance;
	u32 mfiStatus;

	अगर (instance->mask_पूर्णांकerrupts)
		वापस IRQ_NONE;

	अगर (irq_context->irq_poll_scheduled)
		वापस IRQ_HANDLED;

	अगर (!instance->msix_vectors) अणु
		mfiStatus = instance->instancet->clear_पूर्णांकr(instance);
		अगर (!mfiStatus)
			वापस IRQ_NONE;
	पूर्ण

	/* If we are resetting, bail */
	अगर (test_bit(MEGASAS_FUSION_IN_RESET, &instance->reset_flags)) अणु
		instance->instancet->clear_पूर्णांकr(instance);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस complete_cmd_fusion(instance, irq_context->MSIxIndex, irq_context)
			? IRQ_HANDLED : IRQ_NONE;
पूर्ण

/**
 * build_mpt_mfi_pass_thru - builds a cmd fo MFI Pass thru
 * @instance:			Adapter soft state
 * @mfi_cmd:			megasas_cmd poपूर्णांकer
 *
 */
अटल व्योम
build_mpt_mfi_pass_thru(काष्ठा megasas_instance *instance,
			काष्ठा megasas_cmd *mfi_cmd)
अणु
	काष्ठा MPI25_IEEE_SGE_CHAIN64 *mpi25_ieee_chain;
	काष्ठा MPI2_RAID_SCSI_IO_REQUEST *io_req;
	काष्ठा megasas_cmd_fusion *cmd;
	काष्ठा fusion_context *fusion;
	काष्ठा megasas_header *frame_hdr = &mfi_cmd->frame->hdr;

	fusion = instance->ctrl_context;

	cmd = megasas_get_cmd_fusion(instance,
			instance->max_scsi_cmds + mfi_cmd->index);

	/*  Save the smid. To be used क्रम वापसing the cmd */
	mfi_cmd->context.smid = cmd->index;

	/*
	 * For cmds where the flag is set, store the flag and check
	 * on completion. For cmds with this flag, करोn't call
	 * megasas_complete_cmd
	 */

	अगर (frame_hdr->flags & cpu_to_le16(MFI_FRAME_DONT_POST_IN_REPLY_QUEUE))
		mfi_cmd->flags |= DRV_DCMD_POLLED_MODE;

	io_req = cmd->io_request;

	अगर (instance->adapter_type >= INVADER_SERIES) अणु
		काष्ठा MPI25_IEEE_SGE_CHAIN64 *sgl_ptr_end =
			(काष्ठा MPI25_IEEE_SGE_CHAIN64 *)&io_req->SGL;
		sgl_ptr_end += fusion->max_sge_in_मुख्य_msg - 1;
		sgl_ptr_end->Flags = 0;
	पूर्ण

	mpi25_ieee_chain =
	  (काष्ठा MPI25_IEEE_SGE_CHAIN64 *)&io_req->SGL.IeeeChain;

	io_req->Function    = MEGASAS_MPI2_FUNCTION_PASSTHRU_IO_REQUEST;
	io_req->SGLOffset0  = दुरत्व(काष्ठा MPI2_RAID_SCSI_IO_REQUEST,
				       SGL) / 4;
	io_req->ChainOffset = fusion->chain_offset_mfi_pthru;

	mpi25_ieee_chain->Address = cpu_to_le64(mfi_cmd->frame_phys_addr);

	mpi25_ieee_chain->Flags = IEEE_SGE_FLAGS_CHAIN_ELEMENT |
		MPI2_IEEE_SGE_FLAGS_IOCPLBNTA_ADDR;

	mpi25_ieee_chain->Length = cpu_to_le32(instance->mfi_frame_size);
पूर्ण

/**
 * build_mpt_cmd - Calls helper function to build a cmd MFI Pass thru cmd
 * @instance:			Adapter soft state
 * @cmd:			mfi cmd to build
 *
 */
अटल जोड़ MEGASAS_REQUEST_DESCRIPTOR_UNION *
build_mpt_cmd(काष्ठा megasas_instance *instance, काष्ठा megasas_cmd *cmd)
अणु
	जोड़ MEGASAS_REQUEST_DESCRIPTOR_UNION *req_desc = शून्य;
	u16 index;

	build_mpt_mfi_pass_thru(instance, cmd);
	index = cmd->context.smid;

	req_desc = megasas_get_request_descriptor(instance, index - 1);

	req_desc->Words = 0;
	req_desc->SCSIIO.RequestFlags = (MPI2_REQ_DESCRIPT_FLAGS_SCSI_IO <<
					 MEGASAS_REQ_DESCRIPT_FLAGS_TYPE_SHIFT);

	req_desc->SCSIIO.SMID = cpu_to_le16(index);

	वापस req_desc;
पूर्ण

/**
 * megasas_issue_dcmd_fusion - Issues a MFI Pass thru cmd
 * @instance:			Adapter soft state
 * @cmd:			mfi cmd poपूर्णांकer
 *
 */
अटल व्योम
megasas_issue_dcmd_fusion(काष्ठा megasas_instance *instance,
			  काष्ठा megasas_cmd *cmd)
अणु
	जोड़ MEGASAS_REQUEST_DESCRIPTOR_UNION *req_desc;

	req_desc = build_mpt_cmd(instance, cmd);

	megasas_fire_cmd_fusion(instance, req_desc);
	वापस;
पूर्ण

/**
 * megasas_release_fusion -	Reverses the FW initialization
 * @instance:			Adapter soft state
 */
व्योम
megasas_release_fusion(काष्ठा megasas_instance *instance)
अणु
	megasas_मुक्त_ioc_init_cmd(instance);
	megasas_मुक्त_cmds(instance);
	megasas_मुक्त_cmds_fusion(instance);

	iounmap(instance->reg_set);

	pci_release_selected_regions(instance->pdev, 1<<instance->bar);
पूर्ण

/**
 * megasas_पढ़ो_fw_status_reg_fusion - वापसs the current FW status value
 * @instance:			Adapter soft state
 */
अटल u32
megasas_पढ़ो_fw_status_reg_fusion(काष्ठा megasas_instance *instance)
अणु
	वापस megasas_पढ़ोl(instance, &instance->reg_set->outbound_scratch_pad_0);
पूर्ण

/**
 * megasas_alloc_host_crash_buffer -	Host buffers क्रम Crash dump collection from Firmware
 * @instance:				Controller's soft instance
 * @वापस:			        Number of allocated host crash buffers
 */
अटल व्योम
megasas_alloc_host_crash_buffer(काष्ठा megasas_instance *instance)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < MAX_CRASH_DUMP_SIZE; i++) अणु
		instance->crash_buf[i] = vzalloc(CRASH_DMA_BUF_SIZE);
		अगर (!instance->crash_buf[i]) अणु
			dev_info(&instance->pdev->dev, "Firmware crash dump "
				"memory allocation failed at index %d\n", i);
			अवरोध;
		पूर्ण
	पूर्ण
	instance->drv_buf_alloc = i;
पूर्ण

/**
 * megasas_मुक्त_host_crash_buffer -	Host buffers क्रम Crash dump collection from Firmware
 * @instance:				Controller's soft instance
 */
व्योम
megasas_मुक्त_host_crash_buffer(काष्ठा megasas_instance *instance)
अणु
	अचिन्हित पूर्णांक i;
	क्रम (i = 0; i < instance->drv_buf_alloc; i++) अणु
		vमुक्त(instance->crash_buf[i]);
	पूर्ण
	instance->drv_buf_index = 0;
	instance->drv_buf_alloc = 0;
	instance->fw_crash_state = UNAVAILABLE;
	instance->fw_crash_buffer_size = 0;
पूर्ण

/**
 * megasas_adp_reset_fusion -	For controller reset
 * @instance:				Controller's soft instance
 * @regs:				MFI रेजिस्टर set
 */
अटल पूर्णांक
megasas_adp_reset_fusion(काष्ठा megasas_instance *instance,
			 काष्ठा megasas_रेजिस्टर_set __iomem *regs)
अणु
	u32 host_diag, असल_state, retry;

	/* Now try to reset the chip */
	ग_लिखोl(MPI2_WRSEQ_FLUSH_KEY_VALUE, &instance->reg_set->fusion_seq_offset);
	ग_लिखोl(MPI2_WRSEQ_1ST_KEY_VALUE, &instance->reg_set->fusion_seq_offset);
	ग_लिखोl(MPI2_WRSEQ_2ND_KEY_VALUE, &instance->reg_set->fusion_seq_offset);
	ग_लिखोl(MPI2_WRSEQ_3RD_KEY_VALUE, &instance->reg_set->fusion_seq_offset);
	ग_लिखोl(MPI2_WRSEQ_4TH_KEY_VALUE, &instance->reg_set->fusion_seq_offset);
	ग_लिखोl(MPI2_WRSEQ_5TH_KEY_VALUE, &instance->reg_set->fusion_seq_offset);
	ग_लिखोl(MPI2_WRSEQ_6TH_KEY_VALUE, &instance->reg_set->fusion_seq_offset);

	/* Check that the diag ग_लिखो enable (DRWE) bit is on */
	host_diag = megasas_पढ़ोl(instance, &instance->reg_set->fusion_host_diag);
	retry = 0;
	जबतक (!(host_diag & HOST_DIAG_WRITE_ENABLE)) अणु
		msleep(100);
		host_diag = megasas_पढ़ोl(instance,
					  &instance->reg_set->fusion_host_diag);
		अगर (retry++ == 100) अणु
			dev_warn(&instance->pdev->dev,
				"Host diag unlock failed from %s %d\n",
				__func__, __LINE__);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!(host_diag & HOST_DIAG_WRITE_ENABLE))
		वापस -1;

	/* Send chip reset command */
	ग_लिखोl(host_diag | HOST_DIAG_RESET_ADAPTER,
		&instance->reg_set->fusion_host_diag);
	msleep(3000);

	/* Make sure reset adapter bit is cleared */
	host_diag = megasas_पढ़ोl(instance, &instance->reg_set->fusion_host_diag);
	retry = 0;
	जबतक (host_diag & HOST_DIAG_RESET_ADAPTER) अणु
		msleep(100);
		host_diag = megasas_पढ़ोl(instance,
					  &instance->reg_set->fusion_host_diag);
		अगर (retry++ == 1000) अणु
			dev_warn(&instance->pdev->dev,
				"Diag reset adapter never cleared %s %d\n",
				__func__, __LINE__);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (host_diag & HOST_DIAG_RESET_ADAPTER)
		वापस -1;

	असल_state = instance->instancet->पढ़ो_fw_status_reg(instance)
			& MFI_STATE_MASK;
	retry = 0;

	जबतक ((असल_state <= MFI_STATE_FW_INIT) && (retry++ < 1000)) अणु
		msleep(100);
		असल_state = instance->instancet->
			पढ़ो_fw_status_reg(instance) & MFI_STATE_MASK;
	पूर्ण
	अगर (असल_state <= MFI_STATE_FW_INIT) अणु
		dev_warn(&instance->pdev->dev,
			"fw state < MFI_STATE_FW_INIT, state = 0x%x %s %d\n",
			असल_state, __func__, __LINE__);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * megasas_check_reset_fusion -	For controller reset check
 * @instance:				Controller's soft instance
 * @regs:				MFI रेजिस्टर set
 */
अटल पूर्णांक
megasas_check_reset_fusion(काष्ठा megasas_instance *instance,
			   काष्ठा megasas_रेजिस्टर_set __iomem *regs)
अणु
	वापस 0;
पूर्ण

/**
 * megasas_trigger_snap_dump -	Trigger snap dump in FW
 * @instance:			Soft instance of adapter
 */
अटल अंतरभूत व्योम megasas_trigger_snap_dump(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक j;
	u32 fw_state, असल_state;

	अगर (!instance->disableOnlineCtrlReset) अणु
		dev_info(&instance->pdev->dev, "Trigger snap dump\n");
		ग_लिखोl(MFI_ADP_TRIGGER_SNAP_DUMP,
		       &instance->reg_set->करोorbell);
		पढ़ोl(&instance->reg_set->करोorbell);
	पूर्ण

	क्रम (j = 0; j < instance->snapdump_रुको_समय; j++) अणु
		असल_state = instance->instancet->पढ़ो_fw_status_reg(instance);
		fw_state = असल_state & MFI_STATE_MASK;
		अगर (fw_state == MFI_STATE_FAULT) अणु
			dev_prपूर्णांकk(KERN_ERR, &instance->pdev->dev,
				   "FW in FAULT state Fault code:0x%x subcode:0x%x func:%s\n",
				   असल_state & MFI_STATE_FAULT_CODE,
				   असल_state & MFI_STATE_FAULT_SUBCODE, __func__);
			वापस;
		पूर्ण
		msleep(1000);
	पूर्ण
पूर्ण

/* This function रुकोs क्रम outstanding commands on fusion to complete */
अटल पूर्णांक
megasas_रुको_क्रम_outstanding_fusion(काष्ठा megasas_instance *instance,
				    पूर्णांक reason, पूर्णांक *convert)
अणु
	पूर्णांक i, outstanding, retval = 0, hb_seconds_missed = 0;
	u32 fw_state, असल_state;
	u32 रुकोसमय_क्रम_io_completion;

	रुकोसमय_क्रम_io_completion =
		min_t(u32, resetरुकोसमय,
			(resetरुकोसमय - instance->snapdump_रुको_समय));

	अगर (reason == MFI_IO_TIMEOUT_OCR) अणु
		dev_info(&instance->pdev->dev,
			"MFI command is timed out\n");
		megasas_complete_cmd_dpc_fusion((अचिन्हित दीर्घ)instance);
		अगर (instance->snapdump_रुको_समय)
			megasas_trigger_snap_dump(instance);
		retval = 1;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < रुकोसमय_क्रम_io_completion; i++) अणु
		/* Check अगर firmware is in fault state */
		असल_state = instance->instancet->पढ़ो_fw_status_reg(instance);
		fw_state = असल_state & MFI_STATE_MASK;
		अगर (fw_state == MFI_STATE_FAULT) अणु
			dev_prपूर्णांकk(KERN_ERR, &instance->pdev->dev,
				   "FW in FAULT state Fault code:0x%x subcode:0x%x func:%s\n",
				   असल_state & MFI_STATE_FAULT_CODE,
				   असल_state & MFI_STATE_FAULT_SUBCODE, __func__);
			megasas_complete_cmd_dpc_fusion((अचिन्हित दीर्घ)instance);
			अगर (instance->requestorId && reason) अणु
				dev_warn(&instance->pdev->dev, "SR-IOV Found FW in FAULT"
				" state while polling during"
				" I/O timeout handling for %d\n",
				instance->host->host_no);
				*convert = 1;
			पूर्ण

			retval = 1;
			जाओ out;
		पूर्ण


		/* If SR-IOV VF mode & heartbeat समयout, करोn't रुको */
		अगर (instance->requestorId && !reason) अणु
			retval = 1;
			जाओ out;
		पूर्ण

		/* If SR-IOV VF mode & I/O समयout, check क्रम HB समयout */
		अगर (instance->requestorId && (reason == SCSIIO_TIMEOUT_OCR)) अणु
			अगर (instance->hb_host_mem->HB.fwCounter !=
			    instance->hb_host_mem->HB.driverCounter) अणु
				instance->hb_host_mem->HB.driverCounter =
					instance->hb_host_mem->HB.fwCounter;
				hb_seconds_missed = 0;
			पूर्ण अन्यथा अणु
				hb_seconds_missed++;
				अगर (hb_seconds_missed ==
				    (MEGASAS_SRIOV_HEARTBEAT_INTERVAL_VF/HZ)) अणु
					dev_warn(&instance->pdev->dev, "SR-IOV:"
					       " Heartbeat never completed "
					       " while polling during I/O "
					       " timeout handling for "
					       "scsi%d.\n",
					       instance->host->host_no);
					       *convert = 1;
					       retval = 1;
					       जाओ out;
				पूर्ण
			पूर्ण
		पूर्ण

		megasas_complete_cmd_dpc_fusion((अचिन्हित दीर्घ)instance);
		outstanding = atomic_पढ़ो(&instance->fw_outstanding);
		अगर (!outstanding)
			जाओ out;

		अगर (!(i % MEGASAS_RESET_NOTICE_INTERVAL)) अणु
			dev_notice(&instance->pdev->dev, "[%2d]waiting for %d "
			       "commands to complete for scsi%d\n", i,
			       outstanding, instance->host->host_no);
		पूर्ण
		msleep(1000);
	पूर्ण

	अगर (instance->snapdump_रुको_समय) अणु
		megasas_trigger_snap_dump(instance);
		retval = 1;
		जाओ out;
	पूर्ण

	अगर (atomic_पढ़ो(&instance->fw_outstanding)) अणु
		dev_err(&instance->pdev->dev, "pending commands remain after waiting, "
		       "will reset adapter scsi%d.\n",
		       instance->host->host_no);
		*convert = 1;
		retval = 1;
	पूर्ण

out:
	वापस retval;
पूर्ण

व्योम  megasas_reset_reply_desc(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक i, j, count;
	काष्ठा fusion_context *fusion;
	जोड़ MPI2_REPLY_DESCRIPTORS_UNION *reply_desc;

	fusion = instance->ctrl_context;
	count = instance->msix_vectors > 0 ? instance->msix_vectors : 1;
	count += instance->iopoll_q_count;

	क्रम (i = 0 ; i < count ; i++) अणु
		fusion->last_reply_idx[i] = 0;
		reply_desc = fusion->reply_frames_desc[i];
		क्रम (j = 0 ; j < fusion->reply_q_depth; j++, reply_desc++)
			reply_desc->Words = cpu_to_le64(ULदीर्घ_उच्च);
	पूर्ण
पूर्ण

/*
 * megasas_refire_mgmt_cmd :	Re-fire management commands
 * @instance:				Controller's soft instance
*/
अटल व्योम megasas_refire_mgmt_cmd(काष्ठा megasas_instance *instance,
			     bool वापस_ioctl)
अणु
	पूर्णांक j;
	काष्ठा megasas_cmd_fusion *cmd_fusion;
	काष्ठा fusion_context *fusion;
	काष्ठा megasas_cmd *cmd_mfi;
	जोड़ MEGASAS_REQUEST_DESCRIPTOR_UNION *req_desc;
	काष्ठा MPI2_RAID_SCSI_IO_REQUEST *scsi_io_req;
	u16 smid;
	bool refire_cmd = false;
	u8 result;
	u32 opcode = 0;

	fusion = instance->ctrl_context;

	/* Re-fire management commands.
	 * Do not traverse complet MPT frame pool. Start from max_scsi_cmds.
	 */
	क्रम (j = instance->max_scsi_cmds ; j < instance->max_fw_cmds; j++) अणु
		cmd_fusion = fusion->cmd_list[j];
		cmd_mfi = instance->cmd_list[cmd_fusion->sync_cmd_idx];
		smid = le16_to_cpu(cmd_mfi->context.smid);
		result = REFIRE_CMD;

		अगर (!smid)
			जारी;

		req_desc = megasas_get_request_descriptor(instance, smid - 1);

		चयन (cmd_mfi->frame->hdr.cmd) अणु
		हाल MFI_CMD_DCMD:
			opcode = le32_to_cpu(cmd_mfi->frame->dcmd.opcode);
			 /* Do not refire shutकरोwn command */
			अगर (opcode == MR_DCMD_CTRL_SHUTDOWN) अणु
				cmd_mfi->frame->dcmd.cmd_status = MFI_STAT_OK;
				result = COMPLETE_CMD;
				अवरोध;
			पूर्ण

			refire_cmd = ((opcode != MR_DCMD_LD_MAP_GET_INFO)) &&
				      (opcode != MR_DCMD_SYSTEM_PD_MAP_GET_INFO) &&
				      !(cmd_mfi->flags & DRV_DCMD_SKIP_REFIRE);

			अगर (!refire_cmd)
				result = RETURN_CMD;

			अवरोध;
		हाल MFI_CMD_NVME:
			अगर (!instance->support_nvme_passthru) अणु
				cmd_mfi->frame->hdr.cmd_status = MFI_STAT_INVALID_CMD;
				result = COMPLETE_CMD;
			पूर्ण

			अवरोध;
		हाल MFI_CMD_TOOLBOX:
			अगर (!instance->support_pci_lane_margining) अणु
				cmd_mfi->frame->hdr.cmd_status = MFI_STAT_INVALID_CMD;
				result = COMPLETE_CMD;
			पूर्ण

			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (वापस_ioctl && cmd_mfi->sync_cmd &&
		    cmd_mfi->frame->hdr.cmd != MFI_CMD_ABORT) अणु
			dev_err(&instance->pdev->dev,
				"return -EBUSY from %s %d cmd 0x%x opcode 0x%x\n",
				__func__, __LINE__, cmd_mfi->frame->hdr.cmd,
				le32_to_cpu(cmd_mfi->frame->dcmd.opcode));
			cmd_mfi->cmd_status_drv = DCMD_BUSY;
			result = COMPLETE_CMD;
		पूर्ण

		scsi_io_req = (काष्ठा MPI2_RAID_SCSI_IO_REQUEST *)
				cmd_fusion->io_request;
		अगर (scsi_io_req->Function == MPI2_FUNCTION_SCSI_TASK_MGMT)
			result = RETURN_CMD;

		चयन (result) अणु
		हाल REFIRE_CMD:
			megasas_fire_cmd_fusion(instance, req_desc);
			अवरोध;
		हाल RETURN_CMD:
			megasas_वापस_cmd(instance, cmd_mfi);
			अवरोध;
		हाल COMPLETE_CMD:
			megasas_complete_cmd(instance, cmd_mfi, DID_OK);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * megasas_वापस_polled_cmds: Return polled mode commands back to the pool
 *			       beक्रमe initiating an OCR.
 * @instance:                  Controller's soft instance
 */
अटल व्योम
megasas_वापस_polled_cmds(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक i;
	काष्ठा megasas_cmd_fusion *cmd_fusion;
	काष्ठा fusion_context *fusion;
	काष्ठा megasas_cmd *cmd_mfi;

	fusion = instance->ctrl_context;

	क्रम (i = instance->max_scsi_cmds; i < instance->max_fw_cmds; i++) अणु
		cmd_fusion = fusion->cmd_list[i];
		cmd_mfi = instance->cmd_list[cmd_fusion->sync_cmd_idx];

		अगर (cmd_mfi->flags & DRV_DCMD_POLLED_MODE) अणु
			अगर (megasas_dbg_lvl & OCR_DEBUG)
				dev_info(&instance->pdev->dev,
					 "%s %d return cmd 0x%x opcode 0x%x\n",
					 __func__, __LINE__, cmd_mfi->frame->hdr.cmd,
					 le32_to_cpu(cmd_mfi->frame->dcmd.opcode));
			cmd_mfi->flags &= ~DRV_DCMD_POLLED_MODE;
			megasas_वापस_cmd(instance, cmd_mfi);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * megasas_track_scsiio : Track SCSI IOs outstanding to a SCSI device
 * @instance: per adapter काष्ठा
 * @channel: the channel asचिन्हित by the OS
 * @id: the id asचिन्हित by the OS
 *
 * Returns SUCCESS अगर no IOs pending to SCSI device, अन्यथा वापस FAILED
 */

अटल पूर्णांक megasas_track_scsiio(काष्ठा megasas_instance *instance,
		पूर्णांक id, पूर्णांक channel)
अणु
	पूर्णांक i, found = 0;
	काष्ठा megasas_cmd_fusion *cmd_fusion;
	काष्ठा fusion_context *fusion;
	fusion = instance->ctrl_context;

	क्रम (i = 0 ; i < instance->max_scsi_cmds; i++) अणु
		cmd_fusion = fusion->cmd_list[i];
		अगर (cmd_fusion->scmd &&
			(cmd_fusion->scmd->device->id == id &&
			cmd_fusion->scmd->device->channel == channel)) अणु
			dev_info(&instance->pdev->dev,
				"SCSI commands pending to target"
				"channel %d id %d \tSMID: 0x%x\n",
				channel, id, cmd_fusion->index);
			scsi_prपूर्णांक_command(cmd_fusion->scmd);
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस found ? FAILED : SUCCESS;
पूर्ण

/**
 * megasas_पंचांग_response_code - translation of device response code
 * @instance:	Controller's soft instance
 * @mpi_reply:	MPI reply वापसed by firmware
 *
 * Return nothing.
 */
अटल व्योम
megasas_पंचांग_response_code(काष्ठा megasas_instance *instance,
		काष्ठा MPI2_SCSI_TASK_MANAGE_REPLY *mpi_reply)
अणु
	अक्षर *desc;

	चयन (mpi_reply->ResponseCode) अणु
	हाल MPI2_SCSITASKMGMT_RSP_TM_COMPLETE:
		desc = "task management request completed";
		अवरोध;
	हाल MPI2_SCSITASKMGMT_RSP_INVALID_FRAME:
		desc = "invalid frame";
		अवरोध;
	हाल MPI2_SCSITASKMGMT_RSP_TM_NOT_SUPPORTED:
		desc = "task management request not supported";
		अवरोध;
	हाल MPI2_SCSITASKMGMT_RSP_TM_FAILED:
		desc = "task management request failed";
		अवरोध;
	हाल MPI2_SCSITASKMGMT_RSP_TM_SUCCEEDED:
		desc = "task management request succeeded";
		अवरोध;
	हाल MPI2_SCSITASKMGMT_RSP_TM_INVALID_LUN:
		desc = "invalid lun";
		अवरोध;
	हाल 0xA:
		desc = "overlapped tag attempted";
		अवरोध;
	हाल MPI2_SCSITASKMGMT_RSP_IO_QUEUED_ON_IOC:
		desc = "task queued, however not sent to target";
		अवरोध;
	शेष:
		desc = "unknown";
		अवरोध;
	पूर्ण
	dev_dbg(&instance->pdev->dev, "response_code(%01x): %s\n",
		mpi_reply->ResponseCode, desc);
	dev_dbg(&instance->pdev->dev,
		"TerminationCount/DevHandle/Function/TaskType/IOCStat/IOCLoginfo"
		" 0x%x/0x%x/0x%x/0x%x/0x%x/0x%x\n",
		mpi_reply->TerminationCount, mpi_reply->DevHandle,
		mpi_reply->Function, mpi_reply->TaskType,
		mpi_reply->IOCStatus, mpi_reply->IOCLogInfo);
पूर्ण

/**
 * megasas_issue_पंचांग - मुख्य routine क्रम sending पंचांग requests
 * @instance: per adapter काष्ठा
 * @device_handle: device handle
 * @channel: the channel asचिन्हित by the OS
 * @id: the id asचिन्हित by the OS
 * @smid_task: smid asचिन्हित to the task
 * @type: MPI2_SCSITASKMGMT_TASKTYPE__XXX (defined in megaraid_sas_fusion.c)
 * @mr_device_priv_data: निजी data
 * Context: user
 *
 * MegaRaid use MPT पूर्णांकerface क्रम Task Magement request.
 * A generic API क्रम sending task management requests to firmware.
 *
 * Return SUCCESS or FAILED.
 */
अटल पूर्णांक
megasas_issue_पंचांग(काष्ठा megasas_instance *instance, u16 device_handle,
	uपूर्णांक channel, uपूर्णांक id, u16 smid_task, u8 type,
	काष्ठा MR_PRIV_DEVICE *mr_device_priv_data)
अणु
	काष्ठा MR_TASK_MANAGE_REQUEST *mr_request;
	काष्ठा MPI2_SCSI_TASK_MANAGE_REQUEST *mpi_request;
	अचिन्हित दीर्घ समयleft;
	काष्ठा megasas_cmd_fusion *cmd_fusion;
	काष्ठा megasas_cmd *cmd_mfi;
	जोड़ MEGASAS_REQUEST_DESCRIPTOR_UNION *req_desc;
	काष्ठा fusion_context *fusion = शून्य;
	काष्ठा megasas_cmd_fusion *scsi_lookup;
	पूर्णांक rc;
	पूर्णांक समयout = MEGASAS_DEFAULT_TM_TIMEOUT;
	काष्ठा MPI2_SCSI_TASK_MANAGE_REPLY *mpi_reply;

	fusion = instance->ctrl_context;

	cmd_mfi = megasas_get_cmd(instance);

	अगर (!cmd_mfi) अणु
		dev_err(&instance->pdev->dev, "Failed from %s %d\n",
			__func__, __LINE__);
		वापस -ENOMEM;
	पूर्ण

	cmd_fusion = megasas_get_cmd_fusion(instance,
			instance->max_scsi_cmds + cmd_mfi->index);

	/*  Save the smid. To be used क्रम वापसing the cmd */
	cmd_mfi->context.smid = cmd_fusion->index;

	req_desc = megasas_get_request_descriptor(instance,
			(cmd_fusion->index - 1));

	cmd_fusion->request_desc = req_desc;
	req_desc->Words = 0;

	mr_request = (काष्ठा MR_TASK_MANAGE_REQUEST *) cmd_fusion->io_request;
	स_रखो(mr_request, 0, माप(काष्ठा MR_TASK_MANAGE_REQUEST));
	mpi_request = (काष्ठा MPI2_SCSI_TASK_MANAGE_REQUEST *) &mr_request->TmRequest;
	mpi_request->Function = MPI2_FUNCTION_SCSI_TASK_MGMT;
	mpi_request->DevHandle = cpu_to_le16(device_handle);
	mpi_request->TaskType = type;
	mpi_request->TaskMID = cpu_to_le16(smid_task);
	mpi_request->LUN[1] = 0;


	req_desc = cmd_fusion->request_desc;
	req_desc->HighPriority.SMID = cpu_to_le16(cmd_fusion->index);
	req_desc->HighPriority.RequestFlags =
		(MPI2_REQ_DESCRIPT_FLAGS_HIGH_PRIORITY <<
		MEGASAS_REQ_DESCRIPT_FLAGS_TYPE_SHIFT);
	req_desc->HighPriority.MSIxIndex =  0;
	req_desc->HighPriority.LMID = 0;
	req_desc->HighPriority.Reserved1 = 0;

	अगर (channel < MEGASAS_MAX_PD_CHANNELS)
		mr_request->पंचांगReqFlags.isTMForPD = 1;
	अन्यथा
		mr_request->पंचांगReqFlags.isTMForLD = 1;

	init_completion(&cmd_fusion->करोne);
	megasas_fire_cmd_fusion(instance, req_desc);

	चयन (type) अणु
	हाल MPI2_SCSITASKMGMT_TASKTYPE_ABORT_TASK:
		समयout = mr_device_priv_data->task_पात_पंचांगo;
		अवरोध;
	हाल MPI2_SCSITASKMGMT_TASKTYPE_TARGET_RESET:
		समयout = mr_device_priv_data->target_reset_पंचांगo;
		अवरोध;
	पूर्ण

	समयleft = रुको_क्रम_completion_समयout(&cmd_fusion->करोne, समयout * HZ);

	अगर (!समयleft) अणु
		dev_err(&instance->pdev->dev,
			"task mgmt type 0x%x timed out\n", type);
		mutex_unlock(&instance->reset_mutex);
		rc = megasas_reset_fusion(instance->host, MFI_IO_TIMEOUT_OCR);
		mutex_lock(&instance->reset_mutex);
		वापस rc;
	पूर्ण

	mpi_reply = (काष्ठा MPI2_SCSI_TASK_MANAGE_REPLY *) &mr_request->TMReply;
	megasas_पंचांग_response_code(instance, mpi_reply);

	megasas_वापस_cmd(instance, cmd_mfi);
	rc = SUCCESS;
	चयन (type) अणु
	हाल MPI2_SCSITASKMGMT_TASKTYPE_ABORT_TASK:
		scsi_lookup = fusion->cmd_list[smid_task - 1];

		अगर (scsi_lookup->scmd == शून्य)
			अवरोध;
		अन्यथा अणु
			instance->instancet->disable_पूर्णांकr(instance);
			megasas_sync_irqs((अचिन्हित दीर्घ)instance);
			instance->instancet->enable_पूर्णांकr(instance);
			megasas_enable_irq_poll(instance);
			अगर (scsi_lookup->scmd == शून्य)
				अवरोध;
		पूर्ण
		rc = FAILED;
		अवरोध;

	हाल MPI2_SCSITASKMGMT_TASKTYPE_TARGET_RESET:
		अगर ((channel == 0xFFFFFFFF) && (id == 0xFFFFFFFF))
			अवरोध;
		instance->instancet->disable_पूर्णांकr(instance);
		megasas_sync_irqs((अचिन्हित दीर्घ)instance);
		rc = megasas_track_scsiio(instance, id, channel);
		instance->instancet->enable_पूर्णांकr(instance);
		megasas_enable_irq_poll(instance);

		अवरोध;
	हाल MPI2_SCSITASKMGMT_TASKTYPE_ABRT_TASK_SET:
	हाल MPI2_SCSITASKMGMT_TASKTYPE_QUERY_TASK:
		अवरोध;
	शेष:
		rc = FAILED;
		अवरोध;
	पूर्ण

	वापस rc;

पूर्ण

/*
 * megasas_fusion_smid_lookup : Look क्रम fusion command correpspodning to SCSI
 * @instance: per adapter काष्ठा
 *
 * Return Non Zero index, अगर SMID found in outstanding commands
 */
अटल u16 megasas_fusion_smid_lookup(काष्ठा scsi_cmnd *scmd)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा megasas_instance *instance;
	काष्ठा megasas_cmd_fusion *cmd_fusion;
	काष्ठा fusion_context *fusion;

	instance = (काष्ठा megasas_instance *)scmd->device->host->hostdata;

	fusion = instance->ctrl_context;

	क्रम (i = 0; i < instance->max_scsi_cmds; i++) अणु
		cmd_fusion = fusion->cmd_list[i];
		अगर (cmd_fusion->scmd && (cmd_fusion->scmd == scmd)) अणु
			scmd_prपूर्णांकk(KERN_NOTICE, scmd, "Abort request is for"
				" SMID: %d\n", cmd_fusion->index);
			ret = cmd_fusion->index;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
* megasas_get_पंचांग_devhandle - Get devhandle क्रम TM request
* @sdev-		     OS provided scsi device
*
* Returns-		     devhandle/targetID of SCSI device
*/
अटल u16 megasas_get_पंचांग_devhandle(काष्ठा scsi_device *sdev)
अणु
	u16 pd_index = 0;
	u32 device_id;
	काष्ठा megasas_instance *instance;
	काष्ठा fusion_context *fusion;
	काष्ठा MR_PD_CFG_SEQ_NUM_SYNC *pd_sync;
	u16 devhandle = (u16)अच_दीर्घ_उच्च;

	instance = (काष्ठा megasas_instance *)sdev->host->hostdata;
	fusion = instance->ctrl_context;

	अगर (!MEGASAS_IS_LOGICAL(sdev)) अणु
		अगर (instance->use_seqnum_jbod_fp) अणु
			pd_index = (sdev->channel * MEGASAS_MAX_DEV_PER_CHANNEL)
				    + sdev->id;
			pd_sync = (व्योम *)fusion->pd_seq_sync
					[(instance->pd_seq_map_id - 1) & 1];
			devhandle = pd_sync->seq[pd_index].devHandle;
		पूर्ण अन्यथा
			sdev_prपूर्णांकk(KERN_ERR, sdev, "Firmware expose tmCapable"
				" without JBOD MAP support from %s %d\n", __func__, __LINE__);
	पूर्ण अन्यथा अणु
		device_id = ((sdev->channel % 2) * MEGASAS_MAX_DEV_PER_CHANNEL)
				+ sdev->id;
		devhandle = device_id;
	पूर्ण

	वापस devhandle;
पूर्ण

/*
 * megasas_task_पात_fusion : SCSI task पात function क्रम fusion adapters
 * @scmd : poपूर्णांकer to scsi command object
 *
 * Return SUCCESS, अगर command पातed अन्यथा FAILED
 */

पूर्णांक megasas_task_पात_fusion(काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा megasas_instance *instance;
	u16 smid, devhandle;
	पूर्णांक ret;
	काष्ठा MR_PRIV_DEVICE *mr_device_priv_data;
	mr_device_priv_data = scmd->device->hostdata;

	instance = (काष्ठा megasas_instance *)scmd->device->host->hostdata;

	अगर (atomic_पढ़ो(&instance->adprecovery) != MEGASAS_HBA_OPERATIONAL) अणु
		dev_err(&instance->pdev->dev, "Controller is not OPERATIONAL,"
		"SCSI host:%d\n", instance->host->host_no);
		ret = FAILED;
		वापस ret;
	पूर्ण

	अगर (!mr_device_priv_data) अणु
		sdev_prपूर्णांकk(KERN_INFO, scmd->device, "device been deleted! "
			"scmd(%p)\n", scmd);
		scmd->result = DID_NO_CONNECT << 16;
		ret = SUCCESS;
		जाओ out;
	पूर्ण

	अगर (!mr_device_priv_data->is_पंचांग_capable) अणु
		ret = FAILED;
		जाओ out;
	पूर्ण

	mutex_lock(&instance->reset_mutex);

	smid = megasas_fusion_smid_lookup(scmd);

	अगर (!smid) अणु
		ret = SUCCESS;
		scmd_prपूर्णांकk(KERN_NOTICE, scmd, "Command for which abort is"
			" issued is not found in outstanding commands\n");
		mutex_unlock(&instance->reset_mutex);
		जाओ out;
	पूर्ण

	devhandle = megasas_get_पंचांग_devhandle(scmd->device);

	अगर (devhandle == (u16)अच_दीर्घ_उच्च) अणु
		ret = SUCCESS;
		sdev_prपूर्णांकk(KERN_INFO, scmd->device,
			"task abort issued for invalid devhandle\n");
		mutex_unlock(&instance->reset_mutex);
		जाओ out;
	पूर्ण
	sdev_prपूर्णांकk(KERN_INFO, scmd->device,
		"attempting task abort! scmd(0x%p) tm_dev_handle 0x%x\n",
		scmd, devhandle);

	mr_device_priv_data->पंचांग_busy = true;
	ret = megasas_issue_पंचांग(instance, devhandle,
			scmd->device->channel, scmd->device->id, smid,
			MPI2_SCSITASKMGMT_TASKTYPE_ABORT_TASK,
			mr_device_priv_data);
	mr_device_priv_data->पंचांग_busy = false;

	mutex_unlock(&instance->reset_mutex);
	scmd_prपूर्णांकk(KERN_INFO, scmd, "task abort %s!! scmd(0x%p)\n",
			((ret == SUCCESS) ? "SUCCESS" : "FAILED"), scmd);
out:
	scsi_prपूर्णांक_command(scmd);
	अगर (megasas_dbg_lvl & TM_DEBUG)
		megasas_dump_fusion_io(scmd);

	वापस ret;
पूर्ण

/*
 * megasas_reset_target_fusion : target reset function क्रम fusion adapters
 * scmd: SCSI command poपूर्णांकer
 *
 * Returns SUCCESS अगर all commands associated with target पातed अन्यथा FAILED
 */

पूर्णांक megasas_reset_target_fusion(काष्ठा scsi_cmnd *scmd)
अणु

	काष्ठा megasas_instance *instance;
	पूर्णांक ret = FAILED;
	u16 devhandle;
	काष्ठा MR_PRIV_DEVICE *mr_device_priv_data;
	mr_device_priv_data = scmd->device->hostdata;

	instance = (काष्ठा megasas_instance *)scmd->device->host->hostdata;

	अगर (atomic_पढ़ो(&instance->adprecovery) != MEGASAS_HBA_OPERATIONAL) अणु
		dev_err(&instance->pdev->dev, "Controller is not OPERATIONAL,"
		"SCSI host:%d\n", instance->host->host_no);
		ret = FAILED;
		वापस ret;
	पूर्ण

	अगर (!mr_device_priv_data) अणु
		sdev_prपूर्णांकk(KERN_INFO, scmd->device,
			    "device been deleted! scmd: (0x%p)\n", scmd);
		scmd->result = DID_NO_CONNECT << 16;
		ret = SUCCESS;
		जाओ out;
	पूर्ण

	अगर (!mr_device_priv_data->is_पंचांग_capable) अणु
		ret = FAILED;
		जाओ out;
	पूर्ण

	mutex_lock(&instance->reset_mutex);
	devhandle = megasas_get_पंचांग_devhandle(scmd->device);

	अगर (devhandle == (u16)अच_दीर्घ_उच्च) अणु
		ret = SUCCESS;
		sdev_prपूर्णांकk(KERN_INFO, scmd->device,
			"target reset issued for invalid devhandle\n");
		mutex_unlock(&instance->reset_mutex);
		जाओ out;
	पूर्ण

	sdev_prपूर्णांकk(KERN_INFO, scmd->device,
		"attempting target reset! scmd(0x%p) tm_dev_handle: 0x%x\n",
		scmd, devhandle);
	mr_device_priv_data->पंचांग_busy = true;
	ret = megasas_issue_पंचांग(instance, devhandle,
			scmd->device->channel, scmd->device->id, 0,
			MPI2_SCSITASKMGMT_TASKTYPE_TARGET_RESET,
			mr_device_priv_data);
	mr_device_priv_data->पंचांग_busy = false;
	mutex_unlock(&instance->reset_mutex);
	scmd_prपूर्णांकk(KERN_NOTICE, scmd, "target reset %s!!\n",
		(ret == SUCCESS) ? "SUCCESS" : "FAILED");

out:
	वापस ret;
पूर्ण

/*SRIOV get other instance in cluster अगर any*/
अटल काष्ठा
megasas_instance *megasas_get_peer_instance(काष्ठा megasas_instance *instance)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_MGMT_ADAPTERS; i++) अणु
		अगर (megasas_mgmt_info.instance[i] &&
			(megasas_mgmt_info.instance[i] != instance) &&
			 megasas_mgmt_info.instance[i]->requestorId &&
			 megasas_mgmt_info.instance[i]->peerIsPresent &&
			(स_भेद((megasas_mgmt_info.instance[i]->clusterId),
			instance->clusterId, MEGASAS_CLUSTER_ID_SIZE) == 0))
			वापस megasas_mgmt_info.instance[i];
	पूर्ण
	वापस शून्य;
पूर्ण

/* Check क्रम a second path that is currently UP */
पूर्णांक megasas_check_mpio_paths(काष्ठा megasas_instance *instance,
	काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा megasas_instance *peer_instance = शून्य;
	पूर्णांक retval = (DID_REQUEUE << 16);

	अगर (instance->peerIsPresent) अणु
		peer_instance = megasas_get_peer_instance(instance);
		अगर ((peer_instance) &&
			(atomic_पढ़ो(&peer_instance->adprecovery) ==
			MEGASAS_HBA_OPERATIONAL))
			retval = (DID_NO_CONNECT << 16);
	पूर्ण
	वापस retval;
पूर्ण

/* Core fusion reset function */
पूर्णांक megasas_reset_fusion(काष्ठा Scsi_Host *shost, पूर्णांक reason)
अणु
	पूर्णांक retval = SUCCESS, i, j, convert = 0;
	काष्ठा megasas_instance *instance;
	काष्ठा megasas_cmd_fusion *cmd_fusion, *r1_cmd;
	काष्ठा fusion_context *fusion;
	u32 असल_state, status_reg, reset_adapter, fpio_count = 0;
	u32 io_समयout_in_crash_mode = 0;
	काष्ठा scsi_cmnd *scmd_local = शून्य;
	काष्ठा scsi_device *sdev;
	पूर्णांक ret_target_prop = DCMD_FAILED;
	bool is_target_prop = false;
	bool करो_adp_reset = true;
	पूर्णांक max_reset_tries = MEGASAS_FUSION_MAX_RESET_TRIES;

	instance = (काष्ठा megasas_instance *)shost->hostdata;
	fusion = instance->ctrl_context;

	mutex_lock(&instance->reset_mutex);

	अगर (atomic_पढ़ो(&instance->adprecovery) == MEGASAS_HW_CRITICAL_ERROR) अणु
		dev_warn(&instance->pdev->dev, "Hardware critical error, "
		       "returning FAILED for scsi%d.\n",
			instance->host->host_no);
		mutex_unlock(&instance->reset_mutex);
		वापस FAILED;
	पूर्ण
	status_reg = instance->instancet->पढ़ो_fw_status_reg(instance);
	असल_state = status_reg & MFI_STATE_MASK;

	/* IO समयout detected, क्रमcibly put FW in FAULT state */
	अगर (असल_state != MFI_STATE_FAULT && instance->crash_dump_buf &&
		instance->crash_dump_app_support && reason) अणु
		dev_info(&instance->pdev->dev, "IO/DCMD timeout is detected, "
			"forcibly FAULT Firmware\n");
		atomic_set(&instance->adprecovery, MEGASAS_ADPRESET_SM_INFAULT);
		status_reg = megasas_पढ़ोl(instance, &instance->reg_set->करोorbell);
		ग_लिखोl(status_reg | MFI_STATE_FORCE_OCR,
			&instance->reg_set->करोorbell);
		पढ़ोl(&instance->reg_set->करोorbell);
		mutex_unlock(&instance->reset_mutex);
		करो अणु
			ssleep(3);
			io_समयout_in_crash_mode++;
			dev_dbg(&instance->pdev->dev, "waiting for [%d] "
				"seconds for crash dump collection and OCR "
				"to be done\n", (io_समयout_in_crash_mode * 3));
		पूर्ण जबतक ((atomic_पढ़ो(&instance->adprecovery) != MEGASAS_HBA_OPERATIONAL) &&
			(io_समयout_in_crash_mode < 80));

		अगर (atomic_पढ़ो(&instance->adprecovery) == MEGASAS_HBA_OPERATIONAL) अणु
			dev_info(&instance->pdev->dev, "OCR done for IO "
				"timeout case\n");
			retval = SUCCESS;
		पूर्ण अन्यथा अणु
			dev_info(&instance->pdev->dev, "Controller is not "
				"operational after 240 seconds wait for IO "
				"timeout case in FW crash dump mode\n do "
				"OCR/kill adapter\n");
			retval = megasas_reset_fusion(shost, 0);
		पूर्ण
		वापस retval;
	पूर्ण

	अगर (instance->requestorId && !instance->skip_heartbeat_समयr_del)
		del_समयr_sync(&instance->sriov_heartbeat_समयr);
	set_bit(MEGASAS_FUSION_IN_RESET, &instance->reset_flags);
	set_bit(MEGASAS_FUSION_OCR_NOT_POSSIBLE, &instance->reset_flags);
	atomic_set(&instance->adprecovery, MEGASAS_ADPRESET_SM_POLLING);
	instance->instancet->disable_पूर्णांकr(instance);
	megasas_sync_irqs((अचिन्हित दीर्घ)instance);

	/* First try रुकोing क्रम commands to complete */
	अगर (megasas_रुको_क्रम_outstanding_fusion(instance, reason,
						&convert)) अणु
		atomic_set(&instance->adprecovery, MEGASAS_ADPRESET_SM_INFAULT);
		dev_warn(&instance->pdev->dev, "resetting fusion "
		       "adapter scsi%d.\n", instance->host->host_no);
		अगर (convert)
			reason = 0;

		अगर (megasas_dbg_lvl & OCR_DEBUG)
			dev_info(&instance->pdev->dev, "\nPending SCSI commands:\n");

		/* Now वापस commands back to the OS */
		क्रम (i = 0 ; i < instance->max_scsi_cmds; i++) अणु
			cmd_fusion = fusion->cmd_list[i];
			/*check क्रम extra commands issued by driver*/
			अगर (instance->adapter_type >= VENTURA_SERIES) अणु
				r1_cmd = fusion->cmd_list[i + instance->max_fw_cmds];
				megasas_वापस_cmd_fusion(instance, r1_cmd);
			पूर्ण
			scmd_local = cmd_fusion->scmd;
			अगर (cmd_fusion->scmd) अणु
				अगर (megasas_dbg_lvl & OCR_DEBUG) अणु
					sdev_prपूर्णांकk(KERN_INFO,
						cmd_fusion->scmd->device, "SMID: 0x%x\n",
						cmd_fusion->index);
					megasas_dump_fusion_io(cmd_fusion->scmd);
				पूर्ण

				अगर (cmd_fusion->io_request->Function ==
					MPI2_FUNCTION_SCSI_IO_REQUEST)
					fpio_count++;

				scmd_local->result =
					megasas_check_mpio_paths(instance,
							scmd_local);
				अगर (instance->ldio_threshold &&
					megasas_cmd_type(scmd_local) == READ_WRITE_LDIO)
					atomic_dec(&instance->ldio_outstanding);
				megasas_वापस_cmd_fusion(instance, cmd_fusion);
				scsi_dma_unmap(scmd_local);
				scmd_local->scsi_करोne(scmd_local);
			पूर्ण
		पूर्ण

		dev_info(&instance->pdev->dev, "Outstanding fastpath IOs: %d\n",
			fpio_count);

		atomic_set(&instance->fw_outstanding, 0);

		status_reg = instance->instancet->पढ़ो_fw_status_reg(instance);
		असल_state = status_reg & MFI_STATE_MASK;
		reset_adapter = status_reg & MFI_RESET_ADAPTER;
		अगर (instance->disableOnlineCtrlReset ||
		    (असल_state == MFI_STATE_FAULT && !reset_adapter)) अणु
			/* Reset not supported, समाप्त adapter */
			dev_warn(&instance->pdev->dev, "Reset not supported"
			       ", killing adapter scsi%d.\n",
				instance->host->host_no);
			जाओ समाप्त_hba;
		पूर्ण

		/* Let SR-IOV VF & PF sync up अगर there was a HB failure */
		अगर (instance->requestorId && !reason) अणु
			msleep(MEGASAS_OCR_SETTLE_TIME_VF);
			करो_adp_reset = false;
			max_reset_tries = MEGASAS_SRIOV_MAX_RESET_TRIES_VF;
		पूर्ण

		/* Now try to reset the chip */
		क्रम (i = 0; i < max_reset_tries; i++) अणु
			/*
			 * Do adp reset and रुको क्रम
			 * controller to transition to पढ़ोy
			 */
			अगर (megasas_adp_reset_रुको_क्रम_पढ़ोy(instance,
				करो_adp_reset, 1) == FAILED)
				जारी;

			/* Wait क्रम FW to become पढ़ोy */
			अगर (megasas_transition_to_पढ़ोy(instance, 1)) अणु
				dev_warn(&instance->pdev->dev,
					"Failed to transition controller to ready for "
					"scsi%d.\n", instance->host->host_no);
				जारी;
			पूर्ण
			megasas_reset_reply_desc(instance);
			megasas_fusion_update_can_queue(instance, OCR_CONTEXT);

			अगर (megasas_ioc_init_fusion(instance)) अणु
				जारी;
			पूर्ण

			अगर (megasas_get_ctrl_info(instance)) अणु
				dev_info(&instance->pdev->dev,
					"Failed from %s %d\n",
					__func__, __LINE__);
				जाओ समाप्त_hba;
			पूर्ण

			megasas_refire_mgmt_cmd(instance,
						(i == (MEGASAS_FUSION_MAX_RESET_TRIES - 1)
							? 1 : 0));

			/* Reset load balance info */
			अगर (fusion->load_balance_info)
				स_रखो(fusion->load_balance_info, 0,
				       (माप(काष्ठा LD_LOAD_BALANCE_INFO) *
				       MAX_LOGICAL_DRIVES_EXT));

			अगर (!megasas_get_map_info(instance)) अणु
				megasas_sync_map_info(instance);
			पूर्ण अन्यथा अणु
				/*
				 * Return pending polled mode cmds beक्रमe
				 * retrying OCR
				 */
				megasas_वापस_polled_cmds(instance);
				जारी;
			पूर्ण

			megasas_setup_jbod_map(instance);

			/* reset stream detection array */
			अगर (instance->adapter_type >= VENTURA_SERIES) अणु
				क्रम (j = 0; j < MAX_LOGICAL_DRIVES_EXT; ++j) अणु
					स_रखो(fusion->stream_detect_by_ld[j],
					0, माप(काष्ठा LD_STREAM_DETECT));
				 fusion->stream_detect_by_ld[j]->mru_bit_map
						= MR_STREAM_BITMAP;
				पूर्ण
			पूर्ण

			clear_bit(MEGASAS_FUSION_IN_RESET,
				  &instance->reset_flags);
			instance->instancet->enable_पूर्णांकr(instance);
			megasas_enable_irq_poll(instance);
			shost_क्रम_each_device(sdev, shost) अणु
				अगर ((instance->tgt_prop) &&
				    (instance->nvme_page_size))
					ret_target_prop = megasas_get_target_prop(instance, sdev);

				is_target_prop = (ret_target_prop == DCMD_SUCCESS) ? true : false;
				megasas_set_dynamic_target_properties(sdev, is_target_prop);
			पूर्ण

			status_reg = instance->instancet->पढ़ो_fw_status_reg
					(instance);
			असल_state = status_reg & MFI_STATE_MASK;
			अगर (असल_state != MFI_STATE_OPERATIONAL) अणु
				dev_info(&instance->pdev->dev,
					 "Adapter is not OPERATIONAL, state 0x%x for scsi:%d\n",
					 असल_state, instance->host->host_no);
				जाओ out;
			पूर्ण
			atomic_set(&instance->adprecovery, MEGASAS_HBA_OPERATIONAL);

			dev_info(&instance->pdev->dev,
				 "Adapter is OPERATIONAL for scsi:%d\n",
				 instance->host->host_no);

			/* Restart SR-IOV heartbeat */
			अगर (instance->requestorId) अणु
				अगर (!megasas_sriov_start_heartbeat(instance, 0))
					megasas_start_समयr(instance);
				अन्यथा
					instance->skip_heartbeat_समयr_del = 1;
			पूर्ण

			अगर (instance->crash_dump_drv_support &&
				instance->crash_dump_app_support)
				megasas_set_crash_dump_params(instance,
					MR_CRASH_BUF_TURN_ON);
			अन्यथा
				megasas_set_crash_dump_params(instance,
					MR_CRASH_BUF_TURN_OFF);

			अगर (instance->snapdump_रुको_समय) अणु
				megasas_get_snapdump_properties(instance);
				dev_info(&instance->pdev->dev,
					 "Snap dump wait time\t: %d\n",
					 instance->snapdump_रुको_समय);
			पूर्ण

			retval = SUCCESS;

			/* Adapter reset completed successfully */
			dev_warn(&instance->pdev->dev,
				 "Reset successful for scsi%d.\n",
				 instance->host->host_no);

			जाओ out;
		पूर्ण
		/* Reset failed, समाप्त the adapter */
		dev_warn(&instance->pdev->dev, "Reset failed, killing "
		       "adapter scsi%d.\n", instance->host->host_no);
		जाओ समाप्त_hba;
	पूर्ण अन्यथा अणु
		/* For VF: Restart HB समयr अगर we didn't OCR */
		अगर (instance->requestorId) अणु
			megasas_start_समयr(instance);
		पूर्ण
		clear_bit(MEGASAS_FUSION_IN_RESET, &instance->reset_flags);
		instance->instancet->enable_पूर्णांकr(instance);
		megasas_enable_irq_poll(instance);
		atomic_set(&instance->adprecovery, MEGASAS_HBA_OPERATIONAL);
		जाओ out;
	पूर्ण
समाप्त_hba:
	megaraid_sas_समाप्त_hba(instance);
	megasas_enable_irq_poll(instance);
	instance->skip_heartbeat_समयr_del = 1;
	retval = FAILED;
out:
	clear_bit(MEGASAS_FUSION_OCR_NOT_POSSIBLE, &instance->reset_flags);
	mutex_unlock(&instance->reset_mutex);
	वापस retval;
पूर्ण

/* Fusion Crash dump collection */
अटल व्योम  megasas_fusion_crash_dump(काष्ठा megasas_instance *instance)
अणु
	u32 status_reg;
	u8 partial_copy = 0;
	पूर्णांक रुको = 0;


	status_reg = instance->instancet->पढ़ो_fw_status_reg(instance);

	/*
	 * Allocate host crash buffers to copy data from 1 MB DMA crash buffer
	 * to host crash buffers
	 */
	अगर (instance->drv_buf_index == 0) अणु
		/* Buffer is alपढ़ोy allocated क्रम old Crash dump.
		 * Do OCR and करो not रुको क्रम crash dump collection
		 */
		अगर (instance->drv_buf_alloc) अणु
			dev_info(&instance->pdev->dev, "earlier crash dump is "
				"not yet copied by application, ignoring this "
				"crash dump and initiating OCR\n");
			status_reg |= MFI_STATE_CRASH_DUMP_DONE;
			ग_लिखोl(status_reg,
				&instance->reg_set->outbound_scratch_pad_0);
			पढ़ोl(&instance->reg_set->outbound_scratch_pad_0);
			वापस;
		पूर्ण
		megasas_alloc_host_crash_buffer(instance);
		dev_info(&instance->pdev->dev, "Number of host crash buffers "
			"allocated: %d\n", instance->drv_buf_alloc);
	पूर्ण

	जबतक (!(status_reg & MFI_STATE_CRASH_DUMP_DONE) &&
	       (रुको < MEGASAS_WATCHDOG_WAIT_COUNT)) अणु
		अगर (!(status_reg & MFI_STATE_DMADONE)) अणु
			/*
			 * Next crash dump buffer is not yet DMA'd by FW
			 * Check after 10ms. Wait क्रम 1 second क्रम FW to
			 * post the next buffer. If not bail out.
			 */
			रुको++;
			msleep(MEGASAS_WAIT_FOR_NEXT_DMA_MSECS);
			status_reg = instance->instancet->पढ़ो_fw_status_reg(
					instance);
			जारी;
		पूर्ण

		रुको = 0;
		अगर (instance->drv_buf_index >= instance->drv_buf_alloc) अणु
			dev_info(&instance->pdev->dev,
				 "Driver is done copying the buffer: %d\n",
				 instance->drv_buf_alloc);
			status_reg |= MFI_STATE_CRASH_DUMP_DONE;
			partial_copy = 1;
			अवरोध;
		पूर्ण अन्यथा अणु
			स_नकल(instance->crash_buf[instance->drv_buf_index],
			       instance->crash_dump_buf, CRASH_DMA_BUF_SIZE);
			instance->drv_buf_index++;
			status_reg &= ~MFI_STATE_DMADONE;
		पूर्ण

		ग_लिखोl(status_reg, &instance->reg_set->outbound_scratch_pad_0);
		पढ़ोl(&instance->reg_set->outbound_scratch_pad_0);

		msleep(MEGASAS_WAIT_FOR_NEXT_DMA_MSECS);
		status_reg = instance->instancet->पढ़ो_fw_status_reg(instance);
	पूर्ण

	अगर (status_reg & MFI_STATE_CRASH_DUMP_DONE) अणु
		dev_info(&instance->pdev->dev, "Crash Dump is available,number "
			"of copied buffers: %d\n", instance->drv_buf_index);
		instance->fw_crash_buffer_size =  instance->drv_buf_index;
		instance->fw_crash_state = AVAILABLE;
		instance->drv_buf_index = 0;
		ग_लिखोl(status_reg, &instance->reg_set->outbound_scratch_pad_0);
		पढ़ोl(&instance->reg_set->outbound_scratch_pad_0);
		अगर (!partial_copy)
			megasas_reset_fusion(instance->host, 0);
	पूर्ण
पूर्ण


/* Fusion OCR work queue */
व्योम megasas_fusion_ocr_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा megasas_instance *instance =
		container_of(work, काष्ठा megasas_instance, work_init);

	megasas_reset_fusion(instance->host, 0);
पूर्ण

/* Allocate fusion context */
पूर्णांक
megasas_alloc_fusion_context(काष्ठा megasas_instance *instance)
अणु
	काष्ठा fusion_context *fusion;

	instance->ctrl_context = kzalloc(माप(काष्ठा fusion_context),
					 GFP_KERNEL);
	अगर (!instance->ctrl_context) अणु
		dev_err(&instance->pdev->dev, "Failed from %s %d\n",
			__func__, __LINE__);
		वापस -ENOMEM;
	पूर्ण

	fusion = instance->ctrl_context;

	fusion->log_to_span_pages = get_order(MAX_LOGICAL_DRIVES_EXT *
					      माप(LD_SPAN_INFO));
	fusion->log_to_span =
		(PLD_SPAN_INFO)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO,
						fusion->log_to_span_pages);
	अगर (!fusion->log_to_span) अणु
		fusion->log_to_span =
			vzalloc(array_size(MAX_LOGICAL_DRIVES_EXT,
					   माप(LD_SPAN_INFO)));
		अगर (!fusion->log_to_span) अणु
			dev_err(&instance->pdev->dev, "Failed from %s %d\n",
				__func__, __LINE__);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	fusion->load_balance_info_pages = get_order(MAX_LOGICAL_DRIVES_EXT *
		माप(काष्ठा LD_LOAD_BALANCE_INFO));
	fusion->load_balance_info =
		(काष्ठा LD_LOAD_BALANCE_INFO *)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO,
		fusion->load_balance_info_pages);
	अगर (!fusion->load_balance_info) अणु
		fusion->load_balance_info =
			vzalloc(array_size(MAX_LOGICAL_DRIVES_EXT,
					   माप(काष्ठा LD_LOAD_BALANCE_INFO)));
		अगर (!fusion->load_balance_info)
			dev_err(&instance->pdev->dev, "Failed to allocate load_balance_info, "
				"continuing without Load Balance support\n");
	पूर्ण

	वापस 0;
पूर्ण

व्योम
megasas_मुक्त_fusion_context(काष्ठा megasas_instance *instance)
अणु
	काष्ठा fusion_context *fusion = instance->ctrl_context;

	अगर (fusion) अणु
		अगर (fusion->load_balance_info) अणु
			अगर (is_vदो_स्मृति_addr(fusion->load_balance_info))
				vमुक्त(fusion->load_balance_info);
			अन्यथा
				मुक्त_pages((uदीर्घ)fusion->load_balance_info,
					fusion->load_balance_info_pages);
		पूर्ण

		अगर (fusion->log_to_span) अणु
			अगर (is_vदो_स्मृति_addr(fusion->log_to_span))
				vमुक्त(fusion->log_to_span);
			अन्यथा
				मुक्त_pages((uदीर्घ)fusion->log_to_span,
					   fusion->log_to_span_pages);
		पूर्ण

		kमुक्त(fusion);
	पूर्ण
पूर्ण

काष्ठा megasas_instance_ढाँचा megasas_instance_ढाँचा_fusion = अणु
	.enable_पूर्णांकr = megasas_enable_पूर्णांकr_fusion,
	.disable_पूर्णांकr = megasas_disable_पूर्णांकr_fusion,
	.clear_पूर्णांकr = megasas_clear_पूर्णांकr_fusion,
	.पढ़ो_fw_status_reg = megasas_पढ़ो_fw_status_reg_fusion,
	.adp_reset = megasas_adp_reset_fusion,
	.check_reset = megasas_check_reset_fusion,
	.service_isr = megasas_isr_fusion,
	.tasklet = megasas_complete_cmd_dpc_fusion,
	.init_adapter = megasas_init_adapter_fusion,
	.build_and_issue_cmd = megasas_build_and_issue_cmd_fusion,
	.issue_dcmd = megasas_issue_dcmd_fusion,
पूर्ण;
