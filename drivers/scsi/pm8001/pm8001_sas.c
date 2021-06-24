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

/**
 * pm8001_find_tag - from sas task to find out  tag that beदीर्घs to this task
 * @task: the task sent to the LLDD
 * @tag: the found tag associated with the task
 */
अटल पूर्णांक pm8001_find_tag(काष्ठा sas_task *task, u32 *tag)
अणु
	अगर (task->lldd_task) अणु
		काष्ठा pm8001_ccb_info *ccb;
		ccb = task->lldd_task;
		*tag = ccb->ccb_tag;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
  * pm8001_tag_मुक्त - मुक्त the no more needed tag
  * @pm8001_ha: our hba काष्ठा
  * @tag: the found tag associated with the task
  */
व्योम pm8001_tag_मुक्त(काष्ठा pm8001_hba_info *pm8001_ha, u32 tag)
अणु
	व्योम *biपंचांगap = pm8001_ha->tags;
	clear_bit(tag, biपंचांगap);
पूर्ण

/**
  * pm8001_tag_alloc - allocate a empty tag क्रम task used.
  * @pm8001_ha: our hba काष्ठा
  * @tag_out: the found empty tag .
  */
अंतरभूत पूर्णांक pm8001_tag_alloc(काष्ठा pm8001_hba_info *pm8001_ha, u32 *tag_out)
अणु
	अचिन्हित पूर्णांक tag;
	व्योम *biपंचांगap = pm8001_ha->tags;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pm8001_ha->biपंचांगap_lock, flags);
	tag = find_first_zero_bit(biपंचांगap, pm8001_ha->tags_num);
	अगर (tag >= pm8001_ha->tags_num) अणु
		spin_unlock_irqrestore(&pm8001_ha->biपंचांगap_lock, flags);
		वापस -SAS_QUEUE_FULL;
	पूर्ण
	set_bit(tag, biपंचांगap);
	spin_unlock_irqrestore(&pm8001_ha->biपंचांगap_lock, flags);
	*tag_out = tag;
	वापस 0;
पूर्ण

व्योम pm8001_tag_init(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < pm8001_ha->tags_num; ++i)
		pm8001_tag_मुक्त(pm8001_ha, i);
पूर्ण

 /**
  * pm8001_mem_alloc - allocate memory क्रम pm8001.
  * @pdev: pci device.
  * @virt_addr: the allocated भव address
  * @pphys_addr_hi: the physical address high byte address.
  * @pphys_addr_lo: the physical address low byte address.
  * @mem_size: memory size.
  */
पूर्णांक pm8001_mem_alloc(काष्ठा pci_dev *pdev, व्योम **virt_addr,
	dma_addr_t *pphys_addr, u32 *pphys_addr_hi,
	u32 *pphys_addr_lo, u32 mem_size, u32 align)
अणु
	caddr_t mem_virt_alloc;
	dma_addr_t mem_dma_handle;
	u64 phys_align;
	u64 align_offset = 0;
	अगर (align)
		align_offset = (dma_addr_t)align - 1;
	mem_virt_alloc = dma_alloc_coherent(&pdev->dev, mem_size + align,
					    &mem_dma_handle, GFP_KERNEL);
	अगर (!mem_virt_alloc) अणु
		pr_err("pm80xx: memory allocation error\n");
		वापस -1;
	पूर्ण
	*pphys_addr = mem_dma_handle;
	phys_align = (*pphys_addr + align_offset) & ~align_offset;
	*virt_addr = (व्योम *)mem_virt_alloc + phys_align - *pphys_addr;
	*pphys_addr_hi = upper_32_bits(phys_align);
	*pphys_addr_lo = lower_32_bits(phys_align);
	वापस 0;
पूर्ण

/**
  * pm8001_find_ha_by_dev - from करोमुख्य device which come from sas layer to
  * find out our hba काष्ठा.
  * @dev: the करोमुख्य device which from sas layer.
  */
अटल
काष्ठा pm8001_hba_info *pm8001_find_ha_by_dev(काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा sas_ha_काष्ठा *sha = dev->port->ha;
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	वापस pm8001_ha;
पूर्ण

/**
  * pm8001_phy_control - this function should be रेजिस्टरed to
  * sas_करोमुख्य_function_ढाँचा to provide libsas used, note: this is just
  * control the HBA phy rather than other expander phy अगर you want control
  * other phy, you should use SMP command.
  * @sas_phy: which phy in HBA phys.
  * @func: the operation.
  * @funcdata: always शून्य.
  */
पूर्णांक pm8001_phy_control(काष्ठा asd_sas_phy *sas_phy, क्रमागत phy_func func,
	व्योम *funcdata)
अणु
	पूर्णांक rc = 0, phy_id = sas_phy->id;
	काष्ठा pm8001_hba_info *pm8001_ha = शून्य;
	काष्ठा sas_phy_linkrates *rates;
	काष्ठा pm8001_phy *phy;
	DECLARE_COMPLETION_ONSTACK(completion);
	अचिन्हित दीर्घ flags;
	pm8001_ha = sas_phy->ha->lldd_ha;
	phy = &pm8001_ha->phy[phy_id];
	pm8001_ha->phy[phy_id].enable_completion = &completion;
	चयन (func) अणु
	हाल PHY_FUNC_SET_LINK_RATE:
		rates = funcdata;
		अगर (rates->minimum_linkrate) अणु
			pm8001_ha->phy[phy_id].minimum_linkrate =
				rates->minimum_linkrate;
		पूर्ण
		अगर (rates->maximum_linkrate) अणु
			pm8001_ha->phy[phy_id].maximum_linkrate =
				rates->maximum_linkrate;
		पूर्ण
		अगर (pm8001_ha->phy[phy_id].phy_state ==  PHY_LINK_DISABLE) अणु
			PM8001_CHIP_DISP->phy_start_req(pm8001_ha, phy_id);
			रुको_क्रम_completion(&completion);
		पूर्ण
		PM8001_CHIP_DISP->phy_ctl_req(pm8001_ha, phy_id,
					      PHY_LINK_RESET);
		अवरोध;
	हाल PHY_FUNC_HARD_RESET:
		अगर (pm8001_ha->phy[phy_id].phy_state == PHY_LINK_DISABLE) अणु
			PM8001_CHIP_DISP->phy_start_req(pm8001_ha, phy_id);
			रुको_क्रम_completion(&completion);
		पूर्ण
		PM8001_CHIP_DISP->phy_ctl_req(pm8001_ha, phy_id,
					      PHY_HARD_RESET);
		अवरोध;
	हाल PHY_FUNC_LINK_RESET:
		अगर (pm8001_ha->phy[phy_id].phy_state == PHY_LINK_DISABLE) अणु
			PM8001_CHIP_DISP->phy_start_req(pm8001_ha, phy_id);
			रुको_क्रम_completion(&completion);
		पूर्ण
		PM8001_CHIP_DISP->phy_ctl_req(pm8001_ha, phy_id,
					      PHY_LINK_RESET);
		अवरोध;
	हाल PHY_FUNC_RELEASE_SPINUP_HOLD:
		PM8001_CHIP_DISP->phy_ctl_req(pm8001_ha, phy_id,
					      PHY_LINK_RESET);
		अवरोध;
	हाल PHY_FUNC_DISABLE:
		अगर (pm8001_ha->chip_id != chip_8001) अणु
			अगर (pm8001_ha->phy[phy_id].phy_state ==
				PHY_STATE_LINK_UP_SPCV) अणु
				sas_phy_disconnected(&phy->sas_phy);
				sas_notअगरy_phy_event(&phy->sas_phy,
					PHYE_LOSS_OF_SIGNAL, GFP_KERNEL);
				phy->phy_attached = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (pm8001_ha->phy[phy_id].phy_state ==
				PHY_STATE_LINK_UP_SPC) अणु
				sas_phy_disconnected(&phy->sas_phy);
				sas_notअगरy_phy_event(&phy->sas_phy,
					PHYE_LOSS_OF_SIGNAL, GFP_KERNEL);
				phy->phy_attached = 0;
			पूर्ण
		पूर्ण
		PM8001_CHIP_DISP->phy_stop_req(pm8001_ha, phy_id);
		अवरोध;
	हाल PHY_FUNC_GET_EVENTS:
		spin_lock_irqsave(&pm8001_ha->lock, flags);
		अगर (pm8001_ha->chip_id == chip_8001) अणु
			अगर (-1 == pm8001_bar4_shअगरt(pm8001_ha,
					(phy_id < 4) ? 0x30000 : 0x40000)) अणु
				spin_unlock_irqrestore(&pm8001_ha->lock, flags);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अणु
			काष्ठा sas_phy *phy = sas_phy->phy;
			uपूर्णांक32_t *qp = (uपूर्णांक32_t *)(((अक्षर *)
				pm8001_ha->io_mem[2].memvirtaddr)
				+ 0x1034 + (0x4000 * (phy_id & 3)));

			phy->invalid_dword_count = qp[0];
			phy->running_disparity_error_count = qp[1];
			phy->loss_of_dword_sync_count = qp[3];
			phy->phy_reset_problem_count = qp[4];
		पूर्ण
		अगर (pm8001_ha->chip_id == chip_8001)
			pm8001_bar4_shअगरt(pm8001_ha, 0);
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		वापस 0;
	शेष:
		pm8001_dbg(pm8001_ha, DEVIO, "func 0x%x\n", func);
		rc = -EOPNOTSUPP;
	पूर्ण
	msleep(300);
	वापस rc;
पूर्ण

/**
  * pm8001_scan_start - we should enable all HBA phys by sending the phy_start
  * command to HBA.
  * @shost: the scsi host data.
  */
व्योम pm8001_scan_start(काष्ठा Scsi_Host *shost)
अणु
	पूर्णांक i;
	काष्ठा pm8001_hba_info *pm8001_ha;
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	DECLARE_COMPLETION_ONSTACK(completion);
	pm8001_ha = sha->lldd_ha;
	/* SAS_RE_INITIALIZATION not available in SPCv/ve */
	अगर (pm8001_ha->chip_id == chip_8001)
		PM8001_CHIP_DISP->sas_re_init_req(pm8001_ha);
	क्रम (i = 0; i < pm8001_ha->chip->n_phy; ++i) अणु
		pm8001_ha->phy[i].enable_completion = &completion;
		PM8001_CHIP_DISP->phy_start_req(pm8001_ha, i);
		रुको_क्रम_completion(&completion);
		msleep(300);
	पूर्ण
पूर्ण

पूर्णांक pm8001_scan_finished(काष्ठा Scsi_Host *shost, अचिन्हित दीर्घ समय)
अणु
	काष्ठा sas_ha_काष्ठा *ha = SHOST_TO_SAS_HA(shost);

	/* give the phy enabling पूर्णांकerrupt event समय to come in (1s
	* is empirically about all it takes) */
	अगर (समय < HZ)
		वापस 0;
	/* Wait क्रम discovery to finish */
	sas_drain_work(ha);
	वापस 1;
पूर्ण

/**
  * pm8001_task_prep_smp - the dispatcher function, prepare data क्रम smp task
  * @pm8001_ha: our hba card inक्रमmation
  * @ccb: the ccb which attached to smp task
  */
अटल पूर्णांक pm8001_task_prep_smp(काष्ठा pm8001_hba_info *pm8001_ha,
	काष्ठा pm8001_ccb_info *ccb)
अणु
	वापस PM8001_CHIP_DISP->smp_req(pm8001_ha, ccb);
पूर्ण

u32 pm8001_get_ncq_tag(काष्ठा sas_task *task, u32 *tag)
अणु
	काष्ठा ata_queued_cmd *qc = task->uldd_task;
	अगर (qc) अणु
		अगर (qc->tf.command == ATA_CMD_FPDMA_WRITE ||
		    qc->tf.command == ATA_CMD_FPDMA_READ ||
		    qc->tf.command == ATA_CMD_FPDMA_RECV ||
		    qc->tf.command == ATA_CMD_FPDMA_SEND ||
		    qc->tf.command == ATA_CMD_NCQ_NON_DATA) अणु
			*tag = qc->tag;
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
  * pm8001_task_prep_ata - the dispatcher function, prepare data क्रम sata task
  * @pm8001_ha: our hba card inक्रमmation
  * @ccb: the ccb which attached to sata task
  */
अटल पूर्णांक pm8001_task_prep_ata(काष्ठा pm8001_hba_info *pm8001_ha,
	काष्ठा pm8001_ccb_info *ccb)
अणु
	वापस PM8001_CHIP_DISP->sata_req(pm8001_ha, ccb);
पूर्ण

/**
  * pm8001_task_prep_ssp_पंचांग - the dispatcher function, prepare task management data
  * @pm8001_ha: our hba card inक्रमmation
  * @ccb: the ccb which attached to TM
  * @पंचांगf: the task management IU
  */
अटल पूर्णांक pm8001_task_prep_ssp_पंचांग(काष्ठा pm8001_hba_info *pm8001_ha,
	काष्ठा pm8001_ccb_info *ccb, काष्ठा pm8001_पंचांगf_task *पंचांगf)
अणु
	वापस PM8001_CHIP_DISP->ssp_पंचांग_req(pm8001_ha, ccb, पंचांगf);
पूर्ण

/**
  * pm8001_task_prep_ssp - the dispatcher function,prepare ssp data क्रम ssp task
  * @pm8001_ha: our hba card inक्रमmation
  * @ccb: the ccb which attached to ssp task
  */
अटल पूर्णांक pm8001_task_prep_ssp(काष्ठा pm8001_hba_info *pm8001_ha,
	काष्ठा pm8001_ccb_info *ccb)
अणु
	वापस PM8001_CHIP_DISP->ssp_io_req(pm8001_ha, ccb);
पूर्ण

 /* Find the local port id that's attached to this device */
अटल पूर्णांक sas_find_local_port_id(काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा करोमुख्य_device *pdev = dev->parent;

	/* Directly attached device */
	अगर (!pdev)
		वापस dev->port->id;
	जबतक (pdev) अणु
		काष्ठा करोमुख्य_device *pdev_p = pdev->parent;
		अगर (!pdev_p)
			वापस pdev->port->id;
		pdev = pdev->parent;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा DEV_IS_GONE(pm8001_dev)	\
	((!pm8001_dev || (pm8001_dev->dev_type == SAS_PHY_UNUSED)))
/**
  * pm8001_task_exec - queue the task(ssp, smp && ata) to the hardware.
  * @task: the task to be execute.
  * @gfp_flags: gfp_flags.
  * @is_पंचांगf: अगर it is task management task.
  * @पंचांगf: the task management IU
  */
अटल पूर्णांक pm8001_task_exec(काष्ठा sas_task *task,
	gfp_t gfp_flags, पूर्णांक is_पंचांगf, काष्ठा pm8001_पंचांगf_task *पंचांगf)
अणु
	काष्ठा करोमुख्य_device *dev = task->dev;
	काष्ठा pm8001_hba_info *pm8001_ha;
	काष्ठा pm8001_device *pm8001_dev;
	काष्ठा pm8001_port *port = शून्य;
	काष्ठा sas_task *t = task;
	काष्ठा pm8001_ccb_info *ccb;
	u32 tag = 0xdeadbeef, rc = 0, n_elem = 0;
	अचिन्हित दीर्घ flags = 0;
	क्रमागत sas_protocol task_proto = t->task_proto;

	अगर (!dev->port) अणु
		काष्ठा task_status_काष्ठा *tsm = &t->task_status;
		tsm->resp = SAS_TASK_UNDELIVERED;
		tsm->stat = SAS_PHY_DOWN;
		अगर (dev->dev_type != SAS_SATA_DEV)
			t->task_करोne(t);
		वापस 0;
	पूर्ण
	pm8001_ha = pm8001_find_ha_by_dev(task->dev);
	अगर (pm8001_ha->controller_fatal_error) अणु
		काष्ठा task_status_काष्ठा *ts = &t->task_status;

		ts->resp = SAS_TASK_UNDELIVERED;
		t->task_करोne(t);
		वापस 0;
	पूर्ण
	pm8001_dbg(pm8001_ha, IO, "pm8001_task_exec device\n");
	spin_lock_irqsave(&pm8001_ha->lock, flags);
	करो अणु
		dev = t->dev;
		pm8001_dev = dev->lldd_dev;
		port = &pm8001_ha->port[sas_find_local_port_id(dev)];
		अगर (DEV_IS_GONE(pm8001_dev) || !port->port_attached) अणु
			अगर (sas_protocol_ata(task_proto)) अणु
				काष्ठा task_status_काष्ठा *ts = &t->task_status;
				ts->resp = SAS_TASK_UNDELIVERED;
				ts->stat = SAS_PHY_DOWN;

				spin_unlock_irqrestore(&pm8001_ha->lock, flags);
				t->task_करोne(t);
				spin_lock_irqsave(&pm8001_ha->lock, flags);
				जारी;
			पूर्ण अन्यथा अणु
				काष्ठा task_status_काष्ठा *ts = &t->task_status;
				ts->resp = SAS_TASK_UNDELIVERED;
				ts->stat = SAS_PHY_DOWN;
				t->task_करोne(t);
				जारी;
			पूर्ण
		पूर्ण
		rc = pm8001_tag_alloc(pm8001_ha, &tag);
		अगर (rc)
			जाओ err_out;
		ccb = &pm8001_ha->ccb_info[tag];

		अगर (!sas_protocol_ata(task_proto)) अणु
			अगर (t->num_scatter) अणु
				n_elem = dma_map_sg(pm8001_ha->dev,
					t->scatter,
					t->num_scatter,
					t->data_dir);
				अगर (!n_elem) अणु
					rc = -ENOMEM;
					जाओ err_out_tag;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			n_elem = t->num_scatter;
		पूर्ण

		t->lldd_task = ccb;
		ccb->n_elem = n_elem;
		ccb->ccb_tag = tag;
		ccb->task = t;
		ccb->device = pm8001_dev;
		चयन (task_proto) अणु
		हाल SAS_PROTOCOL_SMP:
			atomic_inc(&pm8001_dev->running_req);
			rc = pm8001_task_prep_smp(pm8001_ha, ccb);
			अवरोध;
		हाल SAS_PROTOCOL_SSP:
			atomic_inc(&pm8001_dev->running_req);
			अगर (is_पंचांगf)
				rc = pm8001_task_prep_ssp_पंचांग(pm8001_ha,
					ccb, पंचांगf);
			अन्यथा
				rc = pm8001_task_prep_ssp(pm8001_ha, ccb);
			अवरोध;
		हाल SAS_PROTOCOL_SATA:
		हाल SAS_PROTOCOL_STP:
			atomic_inc(&pm8001_dev->running_req);
			rc = pm8001_task_prep_ata(pm8001_ha, ccb);
			अवरोध;
		शेष:
			dev_prपूर्णांकk(KERN_ERR, pm8001_ha->dev,
				"unknown sas_task proto: 0x%x\n", task_proto);
			rc = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (rc) अणु
			pm8001_dbg(pm8001_ha, IO, "rc is %x\n", rc);
			atomic_dec(&pm8001_dev->running_req);
			जाओ err_out_tag;
		पूर्ण
		/* TODO: select normal or high priority */
		spin_lock(&t->task_state_lock);
		t->task_state_flags |= SAS_TASK_AT_INITIATOR;
		spin_unlock(&t->task_state_lock);
	पूर्ण जबतक (0);
	rc = 0;
	जाओ out_करोne;

err_out_tag:
	pm8001_tag_मुक्त(pm8001_ha, tag);
err_out:
	dev_prपूर्णांकk(KERN_ERR, pm8001_ha->dev, "pm8001 exec failed[%d]!\n", rc);
	अगर (!sas_protocol_ata(task_proto))
		अगर (n_elem)
			dma_unmap_sg(pm8001_ha->dev, t->scatter, t->num_scatter,
				t->data_dir);
out_करोne:
	spin_unlock_irqrestore(&pm8001_ha->lock, flags);
	वापस rc;
पूर्ण

/**
  * pm8001_queue_command - रेजिस्टर क्रम upper layer used, all IO commands sent
  * to HBA are from this पूर्णांकerface.
  * @task: the task to be execute.
  * @gfp_flags: gfp_flags
  */
पूर्णांक pm8001_queue_command(काष्ठा sas_task *task, gfp_t gfp_flags)
अणु
	वापस pm8001_task_exec(task, gfp_flags, 0, शून्य);
पूर्ण

/**
  * pm8001_ccb_task_मुक्त - मुक्त the sg क्रम ssp and smp command, मुक्त the ccb.
  * @pm8001_ha: our hba card inक्रमmation
  * @ccb: the ccb which attached to ssp task
  * @task: the task to be मुक्त.
  * @ccb_idx: ccb index.
  */
व्योम pm8001_ccb_task_मुक्त(काष्ठा pm8001_hba_info *pm8001_ha,
	काष्ठा sas_task *task, काष्ठा pm8001_ccb_info *ccb, u32 ccb_idx)
अणु
	अगर (!ccb->task)
		वापस;
	अगर (!sas_protocol_ata(task->task_proto))
		अगर (ccb->n_elem)
			dma_unmap_sg(pm8001_ha->dev, task->scatter,
				task->num_scatter, task->data_dir);

	चयन (task->task_proto) अणु
	हाल SAS_PROTOCOL_SMP:
		dma_unmap_sg(pm8001_ha->dev, &task->smp_task.smp_resp, 1,
			DMA_FROM_DEVICE);
		dma_unmap_sg(pm8001_ha->dev, &task->smp_task.smp_req, 1,
			DMA_TO_DEVICE);
		अवरोध;

	हाल SAS_PROTOCOL_SATA:
	हाल SAS_PROTOCOL_STP:
	हाल SAS_PROTOCOL_SSP:
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण
	task->lldd_task = शून्य;
	ccb->task = शून्य;
	ccb->ccb_tag = 0xFFFFFFFF;
	ccb->खोलो_retry = 0;
	pm8001_tag_मुक्त(pm8001_ha, ccb_idx);
पूर्ण

 /**
  * pm8001_alloc_dev - find a empty pm8001_device
  * @pm8001_ha: our hba card inक्रमmation
  */
अटल काष्ठा pm8001_device *pm8001_alloc_dev(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	u32 dev;
	क्रम (dev = 0; dev < PM8001_MAX_DEVICES; dev++) अणु
		अगर (pm8001_ha->devices[dev].dev_type == SAS_PHY_UNUSED) अणु
			pm8001_ha->devices[dev].id = dev;
			वापस &pm8001_ha->devices[dev];
		पूर्ण
	पूर्ण
	अगर (dev == PM8001_MAX_DEVICES) अणु
		pm8001_dbg(pm8001_ha, FAIL,
			   "max support %d devices, ignore ..\n",
			   PM8001_MAX_DEVICES);
	पूर्ण
	वापस शून्य;
पूर्ण
/**
  * pm8001_find_dev - find a matching pm8001_device
  * @pm8001_ha: our hba card inक्रमmation
  * @device_id: device ID to match against
  */
काष्ठा pm8001_device *pm8001_find_dev(काष्ठा pm8001_hba_info *pm8001_ha,
					u32 device_id)
अणु
	u32 dev;
	क्रम (dev = 0; dev < PM8001_MAX_DEVICES; dev++) अणु
		अगर (pm8001_ha->devices[dev].device_id == device_id)
			वापस &pm8001_ha->devices[dev];
	पूर्ण
	अगर (dev == PM8001_MAX_DEVICES) अणु
		pm8001_dbg(pm8001_ha, FAIL, "NO MATCHING DEVICE FOUND !!!\n");
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम pm8001_मुक्त_dev(काष्ठा pm8001_device *pm8001_dev)
अणु
	u32 id = pm8001_dev->id;
	स_रखो(pm8001_dev, 0, माप(*pm8001_dev));
	pm8001_dev->id = id;
	pm8001_dev->dev_type = SAS_PHY_UNUSED;
	pm8001_dev->device_id = PM8001_MAX_DEVICES;
	pm8001_dev->sas_device = शून्य;
पूर्ण

/**
  * pm8001_dev_found_notअगरy - libsas notअगरy a device is found.
  * @dev: the device काष्ठाure which sas layer used.
  *
  * when libsas find a sas करोमुख्य device, it should tell the LLDD that
  * device is found, and then LLDD रेजिस्टर this device to HBA firmware
  * by the command "OPC_INB_REG_DEV", after that the HBA will assign a
  * device ID(according to device's sas address) and वापसed it to LLDD. From
  * now on, we communicate with HBA FW with the device ID which HBA asचिन्हित
  * rather than sas address. it is the necessary step क्रम our HBA but it is
  * the optional क्रम other HBA driver.
  */
अटल पूर्णांक pm8001_dev_found_notअगरy(काष्ठा करोमुख्य_device *dev)
अणु
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक res = 0;
	काष्ठा pm8001_hba_info *pm8001_ha = शून्य;
	काष्ठा करोमुख्य_device *parent_dev = dev->parent;
	काष्ठा pm8001_device *pm8001_device;
	DECLARE_COMPLETION_ONSTACK(completion);
	u32 flag = 0;
	pm8001_ha = pm8001_find_ha_by_dev(dev);
	spin_lock_irqsave(&pm8001_ha->lock, flags);

	pm8001_device = pm8001_alloc_dev(pm8001_ha);
	अगर (!pm8001_device) अणु
		res = -1;
		जाओ found_out;
	पूर्ण
	pm8001_device->sas_device = dev;
	dev->lldd_dev = pm8001_device;
	pm8001_device->dev_type = dev->dev_type;
	pm8001_device->dcompletion = &completion;
	अगर (parent_dev && dev_is_expander(parent_dev->dev_type)) अणु
		पूर्णांक phy_id;
		काष्ठा ex_phy *phy;
		क्रम (phy_id = 0; phy_id < parent_dev->ex_dev.num_phys;
		phy_id++) अणु
			phy = &parent_dev->ex_dev.ex_phy[phy_id];
			अगर (SAS_ADDR(phy->attached_sas_addr)
				== SAS_ADDR(dev->sas_addr)) अणु
				pm8001_device->attached_phy = phy_id;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (phy_id == parent_dev->ex_dev.num_phys) अणु
			pm8001_dbg(pm8001_ha, FAIL,
				   "Error: no attached dev:%016llx at ex:%016llx.\n",
				   SAS_ADDR(dev->sas_addr),
				   SAS_ADDR(parent_dev->sas_addr));
			res = -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (dev->dev_type == SAS_SATA_DEV) अणु
			pm8001_device->attached_phy =
				dev->rphy->identअगरy.phy_identअगरier;
			flag = 1; /* directly sata */
		पूर्ण
	पूर्ण /*रेजिस्टर this device to HBA*/
	pm8001_dbg(pm8001_ha, DISC, "Found device\n");
	PM8001_CHIP_DISP->reg_dev_req(pm8001_ha, pm8001_device, flag);
	spin_unlock_irqrestore(&pm8001_ha->lock, flags);
	रुको_क्रम_completion(&completion);
	अगर (dev->dev_type == SAS_END_DEVICE)
		msleep(50);
	pm8001_ha->flags = PM8001F_RUN_TIME;
	वापस 0;
found_out:
	spin_unlock_irqrestore(&pm8001_ha->lock, flags);
	वापस res;
पूर्ण

पूर्णांक pm8001_dev_found(काष्ठा करोमुख्य_device *dev)
अणु
	वापस pm8001_dev_found_notअगरy(dev);
पूर्ण

व्योम pm8001_task_करोne(काष्ठा sas_task *task)
अणु
	अगर (!del_समयr(&task->slow_task->समयr))
		वापस;
	complete(&task->slow_task->completion);
पूर्ण

अटल व्योम pm8001_पंचांगf_समयकरोut(काष्ठा समयr_list *t)
अणु
	काष्ठा sas_task_slow *slow = from_समयr(slow, t, समयr);
	काष्ठा sas_task *task = slow->task;

	task->task_state_flags |= SAS_TASK_STATE_ABORTED;
	complete(&task->slow_task->completion);
पूर्ण

#घोषणा PM8001_TASK_TIMEOUT 20
/**
  * pm8001_exec_पूर्णांकernal_पंचांगf_task - execute some task management commands.
  * @dev: the wanted device.
  * @पंचांगf: which task management wanted to be take.
  * @para_len: para_len.
  * @parameter: ssp task parameter.
  *
  * when errors or exception happened, we may want to करो something, क्रम example
  * पात the issued task which result in this execption, it is करोne by calling
  * this function, note it is also with the task execute पूर्णांकerface.
  */
अटल पूर्णांक pm8001_exec_पूर्णांकernal_पंचांगf_task(काष्ठा करोमुख्य_device *dev,
	व्योम *parameter, u32 para_len, काष्ठा pm8001_पंचांगf_task *पंचांगf)
अणु
	पूर्णांक res, retry;
	काष्ठा sas_task *task = शून्य;
	काष्ठा pm8001_hba_info *pm8001_ha = pm8001_find_ha_by_dev(dev);
	काष्ठा pm8001_device *pm8001_dev = dev->lldd_dev;
	DECLARE_COMPLETION_ONSTACK(completion_setstate);

	क्रम (retry = 0; retry < 3; retry++) अणु
		task = sas_alloc_slow_task(GFP_KERNEL);
		अगर (!task)
			वापस -ENOMEM;

		task->dev = dev;
		task->task_proto = dev->tproto;
		स_नकल(&task->ssp_task, parameter, para_len);
		task->task_करोne = pm8001_task_करोne;
		task->slow_task->समयr.function = pm8001_पंचांगf_समयकरोut;
		task->slow_task->समयr.expires = jअगरfies + PM8001_TASK_TIMEOUT*HZ;
		add_समयr(&task->slow_task->समयr);

		res = pm8001_task_exec(task, GFP_KERNEL, 1, पंचांगf);

		अगर (res) अणु
			del_समयr(&task->slow_task->समयr);
			pm8001_dbg(pm8001_ha, FAIL, "Executing internal task failed\n");
			जाओ ex_err;
		पूर्ण
		रुको_क्रम_completion(&task->slow_task->completion);
		अगर (pm8001_ha->chip_id != chip_8001) अणु
			pm8001_dev->setds_completion = &completion_setstate;
			PM8001_CHIP_DISP->set_dev_state_req(pm8001_ha,
				pm8001_dev, DS_OPERATIONAL);
			रुको_क्रम_completion(&completion_setstate);
		पूर्ण
		res = -TMF_RESP_FUNC_FAILED;
		/* Even TMF समयd out, वापस direct. */
		अगर ((task->task_state_flags & SAS_TASK_STATE_ABORTED)) अणु
			अगर (!(task->task_state_flags & SAS_TASK_STATE_DONE)) अणु
				pm8001_dbg(pm8001_ha, FAIL,
					   "TMF task[%x]timeout.\n",
					   पंचांगf->पंचांगf);
				जाओ ex_err;
			पूर्ण
		पूर्ण

		अगर (task->task_status.resp == SAS_TASK_COMPLETE &&
			task->task_status.stat == SAM_STAT_GOOD) अणु
			res = TMF_RESP_FUNC_COMPLETE;
			अवरोध;
		पूर्ण

		अगर (task->task_status.resp == SAS_TASK_COMPLETE &&
		task->task_status.stat == SAS_DATA_UNDERRUN) अणु
			/* no error, but वापस the number of bytes of
			* underrun */
			res = task->task_status.residual;
			अवरोध;
		पूर्ण

		अगर (task->task_status.resp == SAS_TASK_COMPLETE &&
			task->task_status.stat == SAS_DATA_OVERRUN) अणु
			pm8001_dbg(pm8001_ha, FAIL, "Blocked task error.\n");
			res = -EMSGSIZE;
			अवरोध;
		पूर्ण अन्यथा अणु
			pm8001_dbg(pm8001_ha, EH,
				   " Task to dev %016llx response:0x%x status 0x%x\n",
				   SAS_ADDR(dev->sas_addr),
				   task->task_status.resp,
				   task->task_status.stat);
			sas_मुक्त_task(task);
			task = शून्य;
		पूर्ण
	पूर्ण
ex_err:
	BUG_ON(retry == 3 && task != शून्य);
	sas_मुक्त_task(task);
	वापस res;
पूर्ण

अटल पूर्णांक
pm8001_exec_पूर्णांकernal_task_पात(काष्ठा pm8001_hba_info *pm8001_ha,
	काष्ठा pm8001_device *pm8001_dev, काष्ठा करोमुख्य_device *dev, u32 flag,
	u32 task_tag)
अणु
	पूर्णांक res, retry;
	u32 ccb_tag;
	काष्ठा pm8001_ccb_info *ccb;
	काष्ठा sas_task *task = शून्य;

	क्रम (retry = 0; retry < 3; retry++) अणु
		task = sas_alloc_slow_task(GFP_KERNEL);
		अगर (!task)
			वापस -ENOMEM;

		task->dev = dev;
		task->task_proto = dev->tproto;
		task->task_करोne = pm8001_task_करोne;
		task->slow_task->समयr.function = pm8001_पंचांगf_समयकरोut;
		task->slow_task->समयr.expires = jअगरfies + PM8001_TASK_TIMEOUT * HZ;
		add_समयr(&task->slow_task->समयr);

		res = pm8001_tag_alloc(pm8001_ha, &ccb_tag);
		अगर (res)
			जाओ ex_err;
		ccb = &pm8001_ha->ccb_info[ccb_tag];
		ccb->device = pm8001_dev;
		ccb->ccb_tag = ccb_tag;
		ccb->task = task;
		ccb->n_elem = 0;

		res = PM8001_CHIP_DISP->task_पात(pm8001_ha,
			pm8001_dev, flag, task_tag, ccb_tag);

		अगर (res) अणु
			del_समयr(&task->slow_task->समयr);
			pm8001_dbg(pm8001_ha, FAIL, "Executing internal task failed\n");
			जाओ ex_err;
		पूर्ण
		रुको_क्रम_completion(&task->slow_task->completion);
		res = TMF_RESP_FUNC_FAILED;
		/* Even TMF समयd out, वापस direct. */
		अगर ((task->task_state_flags & SAS_TASK_STATE_ABORTED)) अणु
			अगर (!(task->task_state_flags & SAS_TASK_STATE_DONE)) अणु
				pm8001_dbg(pm8001_ha, FAIL,
					   "TMF task timeout.\n");
				जाओ ex_err;
			पूर्ण
		पूर्ण

		अगर (task->task_status.resp == SAS_TASK_COMPLETE &&
			task->task_status.stat == SAM_STAT_GOOD) अणु
			res = TMF_RESP_FUNC_COMPLETE;
			अवरोध;

		पूर्ण अन्यथा अणु
			pm8001_dbg(pm8001_ha, EH,
				   " Task to dev %016llx response: 0x%x status 0x%x\n",
				   SAS_ADDR(dev->sas_addr),
				   task->task_status.resp,
				   task->task_status.stat);
			sas_मुक्त_task(task);
			task = शून्य;
		पूर्ण
	पूर्ण
ex_err:
	BUG_ON(retry == 3 && task != शून्य);
	sas_मुक्त_task(task);
	वापस res;
पूर्ण

/**
  * pm8001_dev_gone_notअगरy - see the comments क्रम "pm8001_dev_found_notify"
  * @dev: the device काष्ठाure which sas layer used.
  */
अटल व्योम pm8001_dev_gone_notअगरy(काष्ठा करोमुख्य_device *dev)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा pm8001_hba_info *pm8001_ha;
	काष्ठा pm8001_device *pm8001_dev = dev->lldd_dev;

	pm8001_ha = pm8001_find_ha_by_dev(dev);
	spin_lock_irqsave(&pm8001_ha->lock, flags);
	अगर (pm8001_dev) अणु
		u32 device_id = pm8001_dev->device_id;

		pm8001_dbg(pm8001_ha, DISC, "found dev[%d:%x] is gone.\n",
			   pm8001_dev->device_id, pm8001_dev->dev_type);
		अगर (atomic_पढ़ो(&pm8001_dev->running_req)) अणु
			spin_unlock_irqrestore(&pm8001_ha->lock, flags);
			pm8001_exec_पूर्णांकernal_task_पात(pm8001_ha, pm8001_dev,
							dev, 1, 0);
			जबतक (atomic_पढ़ो(&pm8001_dev->running_req))
				msleep(20);
			spin_lock_irqsave(&pm8001_ha->lock, flags);
		पूर्ण
		PM8001_CHIP_DISP->dereg_dev_req(pm8001_ha, device_id);
		pm8001_मुक्त_dev(pm8001_dev);
	पूर्ण अन्यथा अणु
		pm8001_dbg(pm8001_ha, DISC, "Found dev has gone.\n");
	पूर्ण
	dev->lldd_dev = शून्य;
	spin_unlock_irqrestore(&pm8001_ha->lock, flags);
पूर्ण

व्योम pm8001_dev_gone(काष्ठा करोमुख्य_device *dev)
अणु
	pm8001_dev_gone_notअगरy(dev);
पूर्ण

अटल पूर्णांक pm8001_issue_ssp_पंचांगf(काष्ठा करोमुख्य_device *dev,
	u8 *lun, काष्ठा pm8001_पंचांगf_task *पंचांगf)
अणु
	काष्ठा sas_ssp_task ssp_task;
	अगर (!(dev->tproto & SAS_PROTOCOL_SSP))
		वापस TMF_RESP_FUNC_ESUPP;

	स_नकल((u8 *)&ssp_task.LUN, lun, 8);
	वापस pm8001_exec_पूर्णांकernal_पंचांगf_task(dev, &ssp_task, माप(ssp_task),
		पंचांगf);
पूर्ण

/* retry commands by ha, by task and/or by device */
व्योम pm8001_खोलो_reject_retry(
	काष्ठा pm8001_hba_info *pm8001_ha,
	काष्ठा sas_task *task_to_बंद,
	काष्ठा pm8001_device *device_to_बंद)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	अगर (pm8001_ha == शून्य)
		वापस;

	spin_lock_irqsave(&pm8001_ha->lock, flags);

	क्रम (i = 0; i < PM8001_MAX_CCB; i++) अणु
		काष्ठा sas_task *task;
		काष्ठा task_status_काष्ठा *ts;
		काष्ठा pm8001_device *pm8001_dev;
		अचिन्हित दीर्घ flags1;
		u32 tag;
		काष्ठा pm8001_ccb_info *ccb = &pm8001_ha->ccb_info[i];

		pm8001_dev = ccb->device;
		अगर (!pm8001_dev || (pm8001_dev->dev_type == SAS_PHY_UNUSED))
			जारी;
		अगर (!device_to_बंद) अणु
			uपूर्णांकptr_t d = (uपूर्णांकptr_t)pm8001_dev
					- (uपूर्णांकptr_t)&pm8001_ha->devices;
			अगर (((d % माप(*pm8001_dev)) != 0)
			 || ((d / माप(*pm8001_dev)) >= PM8001_MAX_DEVICES))
				जारी;
		पूर्ण अन्यथा अगर (pm8001_dev != device_to_बंद)
			जारी;
		tag = ccb->ccb_tag;
		अगर (!tag || (tag == 0xFFFFFFFF))
			जारी;
		task = ccb->task;
		अगर (!task || !task->task_करोne)
			जारी;
		अगर (task_to_बंद && (task != task_to_बंद))
			जारी;
		ts = &task->task_status;
		ts->resp = SAS_TASK_COMPLETE;
		/* Force the midlayer to retry */
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		spin_lock_irqsave(&task->task_state_lock, flags1);
		task->task_state_flags &= ~SAS_TASK_STATE_PENDING;
		task->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
		task->task_state_flags |= SAS_TASK_STATE_DONE;
		अगर (unlikely((task->task_state_flags
				& SAS_TASK_STATE_ABORTED))) अणु
			spin_unlock_irqrestore(&task->task_state_lock,
				flags1);
			pm8001_ccb_task_मुक्त(pm8001_ha, task, ccb, tag);
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&task->task_state_lock,
				flags1);
			pm8001_ccb_task_मुक्त(pm8001_ha, task, ccb, tag);
			mb();/* in order to क्रमce CPU ordering */
			spin_unlock_irqrestore(&pm8001_ha->lock, flags);
			task->task_करोne(task);
			spin_lock_irqsave(&pm8001_ha->lock, flags);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&pm8001_ha->lock, flags);
पूर्ण

/**
 * pm8001_I_T_nexus_reset()
  * Standard mandates link reset क्रम ATA  (type 0) and hard reset क्रम
  * SSP (type 1) , only क्रम RECOVERY
  * @dev: the device काष्ठाure क्रम the device to reset.
  */
पूर्णांक pm8001_I_T_nexus_reset(काष्ठा करोमुख्य_device *dev)
अणु
	पूर्णांक rc = TMF_RESP_FUNC_FAILED;
	काष्ठा pm8001_device *pm8001_dev;
	काष्ठा pm8001_hba_info *pm8001_ha;
	काष्ठा sas_phy *phy;

	अगर (!dev || !dev->lldd_dev)
		वापस -ENODEV;

	pm8001_dev = dev->lldd_dev;
	pm8001_ha = pm8001_find_ha_by_dev(dev);
	phy = sas_get_local_phy(dev);

	अगर (dev_is_sata(dev)) अणु
		अगर (scsi_is_sas_phy_local(phy)) अणु
			rc = 0;
			जाओ out;
		पूर्ण
		rc = sas_phy_reset(phy, 1);
		अगर (rc) अणु
			pm8001_dbg(pm8001_ha, EH,
				   "phy reset failed for device %x\n"
				   "with rc %d\n", pm8001_dev->device_id, rc);
			rc = TMF_RESP_FUNC_FAILED;
			जाओ out;
		पूर्ण
		msleep(2000);
		rc = pm8001_exec_पूर्णांकernal_task_पात(pm8001_ha, pm8001_dev,
						     dev, 1, 0);
		अगर (rc) अणु
			pm8001_dbg(pm8001_ha, EH, "task abort failed %x\n"
				   "with rc %d\n", pm8001_dev->device_id, rc);
			rc = TMF_RESP_FUNC_FAILED;
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = sas_phy_reset(phy, 1);
		msleep(2000);
	पूर्ण
	pm8001_dbg(pm8001_ha, EH, " for device[%x]:rc=%d\n",
		   pm8001_dev->device_id, rc);
 out:
	sas_put_local_phy(phy);
	वापस rc;
पूर्ण

/*
* This function handle the IT_NEXUS_XXX event or completion
* status code क्रम SSP/SATA/SMP I/O request.
*/
पूर्णांक pm8001_I_T_nexus_event_handler(काष्ठा करोमुख्य_device *dev)
अणु
	पूर्णांक rc = TMF_RESP_FUNC_FAILED;
	काष्ठा pm8001_device *pm8001_dev;
	काष्ठा pm8001_hba_info *pm8001_ha;
	काष्ठा sas_phy *phy;

	अगर (!dev || !dev->lldd_dev)
		वापस -1;

	pm8001_dev = dev->lldd_dev;
	pm8001_ha = pm8001_find_ha_by_dev(dev);

	pm8001_dbg(pm8001_ha, EH, "I_T_Nexus handler invoked !!\n");

	phy = sas_get_local_phy(dev);

	अगर (dev_is_sata(dev)) अणु
		DECLARE_COMPLETION_ONSTACK(completion_setstate);
		अगर (scsi_is_sas_phy_local(phy)) अणु
			rc = 0;
			जाओ out;
		पूर्ण
		/* send पूर्णांकernal ssp/sata/smp पात command to FW */
		rc = pm8001_exec_पूर्णांकernal_task_पात(pm8001_ha, pm8001_dev,
						     dev, 1, 0);
		msleep(100);

		/* deरेजिस्टर the target device */
		pm8001_dev_gone_notअगरy(dev);
		msleep(200);

		/*send phy reset to hard reset target */
		rc = sas_phy_reset(phy, 1);
		msleep(2000);
		pm8001_dev->setds_completion = &completion_setstate;

		रुको_क्रम_completion(&completion_setstate);
	पूर्ण अन्यथा अणु
		/* send पूर्णांकernal ssp/sata/smp पात command to FW */
		rc = pm8001_exec_पूर्णांकernal_task_पात(pm8001_ha, pm8001_dev,
						     dev, 1, 0);
		msleep(100);

		/* deरेजिस्टर the target device */
		pm8001_dev_gone_notअगरy(dev);
		msleep(200);

		/*send phy reset to hard reset target */
		rc = sas_phy_reset(phy, 1);
		msleep(2000);
	पूर्ण
	pm8001_dbg(pm8001_ha, EH, " for device[%x]:rc=%d\n",
		   pm8001_dev->device_id, rc);
out:
	sas_put_local_phy(phy);

	वापस rc;
पूर्ण
/* mandatory SAM-3, the task reset the specअगरied LUN*/
पूर्णांक pm8001_lu_reset(काष्ठा करोमुख्य_device *dev, u8 *lun)
अणु
	पूर्णांक rc = TMF_RESP_FUNC_FAILED;
	काष्ठा pm8001_पंचांगf_task पंचांगf_task;
	काष्ठा pm8001_device *pm8001_dev = dev->lldd_dev;
	काष्ठा pm8001_hba_info *pm8001_ha = pm8001_find_ha_by_dev(dev);
	DECLARE_COMPLETION_ONSTACK(completion_setstate);
	अगर (dev_is_sata(dev)) अणु
		काष्ठा sas_phy *phy = sas_get_local_phy(dev);
		rc = pm8001_exec_पूर्णांकernal_task_पात(pm8001_ha, pm8001_dev,
						     dev, 1, 0);
		rc = sas_phy_reset(phy, 1);
		sas_put_local_phy(phy);
		pm8001_dev->setds_completion = &completion_setstate;
		rc = PM8001_CHIP_DISP->set_dev_state_req(pm8001_ha,
			pm8001_dev, DS_OPERATIONAL);
		रुको_क्रम_completion(&completion_setstate);
	पूर्ण अन्यथा अणु
		पंचांगf_task.पंचांगf = TMF_LU_RESET;
		rc = pm8001_issue_ssp_पंचांगf(dev, lun, &पंचांगf_task);
	पूर्ण
	/* If failed, fall-through I_T_Nexus reset */
	pm8001_dbg(pm8001_ha, EH, "for device[%x]:rc=%d\n",
		   pm8001_dev->device_id, rc);
	वापस rc;
पूर्ण

/* optional SAM-3 */
पूर्णांक pm8001_query_task(काष्ठा sas_task *task)
अणु
	u32 tag = 0xdeadbeef;
	काष्ठा scsi_lun lun;
	काष्ठा pm8001_पंचांगf_task पंचांगf_task;
	पूर्णांक rc = TMF_RESP_FUNC_FAILED;
	अगर (unlikely(!task || !task->lldd_task || !task->dev))
		वापस rc;

	अगर (task->task_proto & SAS_PROTOCOL_SSP) अणु
		काष्ठा scsi_cmnd *cmnd = task->uldd_task;
		काष्ठा करोमुख्य_device *dev = task->dev;
		काष्ठा pm8001_hba_info *pm8001_ha =
			pm8001_find_ha_by_dev(dev);

		पूर्णांक_to_scsilun(cmnd->device->lun, &lun);
		rc = pm8001_find_tag(task, &tag);
		अगर (rc == 0) अणु
			rc = TMF_RESP_FUNC_FAILED;
			वापस rc;
		पूर्ण
		pm8001_dbg(pm8001_ha, EH, "Query:[%16ph]\n", cmnd->cmnd);
		पंचांगf_task.पंचांगf = 	TMF_QUERY_TASK;
		पंचांगf_task.tag_of_task_to_be_managed = tag;

		rc = pm8001_issue_ssp_पंचांगf(dev, lun.scsi_lun, &पंचांगf_task);
		चयन (rc) अणु
		/* The task is still in Lun, release it then */
		हाल TMF_RESP_FUNC_SUCC:
			pm8001_dbg(pm8001_ha, EH,
				   "The task is still in Lun\n");
			अवरोध;
		/* The task is not in Lun or failed, reset the phy */
		हाल TMF_RESP_FUNC_FAILED:
		हाल TMF_RESP_FUNC_COMPLETE:
			pm8001_dbg(pm8001_ha, EH,
				   "The task is not in Lun or failed, reset the phy\n");
			अवरोध;
		पूर्ण
	पूर्ण
	pr_err("pm80xx: rc= %d\n", rc);
	वापस rc;
पूर्ण

/*  mandatory SAM-3, still need मुक्त task/ccb info, पात the specअगरied task */
पूर्णांक pm8001_पात_task(काष्ठा sas_task *task)
अणु
	अचिन्हित दीर्घ flags;
	u32 tag;
	काष्ठा करोमुख्य_device *dev ;
	काष्ठा pm8001_hba_info *pm8001_ha;
	काष्ठा scsi_lun lun;
	काष्ठा pm8001_device *pm8001_dev;
	काष्ठा pm8001_पंचांगf_task पंचांगf_task;
	पूर्णांक rc = TMF_RESP_FUNC_FAILED, ret;
	u32 phy_id;
	काष्ठा sas_task_slow slow_task;

	अगर (unlikely(!task || !task->lldd_task || !task->dev))
		वापस TMF_RESP_FUNC_FAILED;

	dev = task->dev;
	pm8001_dev = dev->lldd_dev;
	pm8001_ha = pm8001_find_ha_by_dev(dev);
	phy_id = pm8001_dev->attached_phy;

	अगर (PM8001_CHIP_DISP->fatal_errors(pm8001_ha)) अणु
		// If the controller is seeing fatal errors
		// पात task will not get a response from the controller
		वापस TMF_RESP_FUNC_FAILED;
	पूर्ण

	ret = pm8001_find_tag(task, &tag);
	अगर (ret == 0) अणु
		pm8001_info(pm8001_ha, "no tag for task:%p\n", task);
		वापस TMF_RESP_FUNC_FAILED;
	पूर्ण
	spin_lock_irqsave(&task->task_state_lock, flags);
	अगर (task->task_state_flags & SAS_TASK_STATE_DONE) अणु
		spin_unlock_irqrestore(&task->task_state_lock, flags);
		वापस TMF_RESP_FUNC_COMPLETE;
	पूर्ण
	task->task_state_flags |= SAS_TASK_STATE_ABORTED;
	अगर (task->slow_task == शून्य) अणु
		init_completion(&slow_task.completion);
		task->slow_task = &slow_task;
	पूर्ण
	spin_unlock_irqrestore(&task->task_state_lock, flags);
	अगर (task->task_proto & SAS_PROTOCOL_SSP) अणु
		काष्ठा scsi_cmnd *cmnd = task->uldd_task;
		पूर्णांक_to_scsilun(cmnd->device->lun, &lun);
		पंचांगf_task.पंचांगf = TMF_ABORT_TASK;
		पंचांगf_task.tag_of_task_to_be_managed = tag;
		rc = pm8001_issue_ssp_पंचांगf(dev, lun.scsi_lun, &पंचांगf_task);
		pm8001_exec_पूर्णांकernal_task_पात(pm8001_ha, pm8001_dev,
			pm8001_dev->sas_device, 0, tag);
	पूर्ण अन्यथा अगर (task->task_proto & SAS_PROTOCOL_SATA ||
		task->task_proto & SAS_PROTOCOL_STP) अणु
		अगर (pm8001_ha->chip_id == chip_8006) अणु
			DECLARE_COMPLETION_ONSTACK(completion_reset);
			DECLARE_COMPLETION_ONSTACK(completion);
			काष्ठा pm8001_phy *phy = pm8001_ha->phy + phy_id;

			/* 1. Set Device state as Recovery */
			pm8001_dev->setds_completion = &completion;
			PM8001_CHIP_DISP->set_dev_state_req(pm8001_ha,
				pm8001_dev, DS_IN_RECOVERY);
			रुको_क्रम_completion(&completion);

			/* 2. Send Phy Control Hard Reset */
			reinit_completion(&completion);
			phy->port_reset_status = PORT_RESET_TMO;
			phy->reset_success = false;
			phy->enable_completion = &completion;
			phy->reset_completion = &completion_reset;
			ret = PM8001_CHIP_DISP->phy_ctl_req(pm8001_ha, phy_id,
				PHY_HARD_RESET);
			अगर (ret) अणु
				phy->enable_completion = शून्य;
				phy->reset_completion = शून्य;
				जाओ out;
			पूर्ण

			/* In the हाल of the reset समयout/fail we still
			 * पात the command at the firmware. The assumption
			 * here is that the drive is off करोing something so
			 * that it's not processing requests, and we want to
			 * aव्योम getting a completion क्रम this and either
			 * leaking the task in libsas or losing the race and
			 * getting a द्विगुन मुक्त.
			 */
			pm8001_dbg(pm8001_ha, MSG,
				   "Waiting for local phy ctl\n");
			ret = रुको_क्रम_completion_समयout(&completion,
					PM8001_TASK_TIMEOUT * HZ);
			अगर (!ret || !phy->reset_success) अणु
				phy->enable_completion = शून्य;
				phy->reset_completion = शून्य;
			पूर्ण अन्यथा अणु
				/* 3. Wait क्रम Port Reset complete or
				 * Port reset TMO
				 */
				pm8001_dbg(pm8001_ha, MSG,
					   "Waiting for Port reset\n");
				ret = रुको_क्रम_completion_समयout(
					&completion_reset,
					PM8001_TASK_TIMEOUT * HZ);
				अगर (!ret)
					phy->reset_completion = शून्य;
				WARN_ON(phy->port_reset_status ==
						PORT_RESET_TMO);
				अगर (phy->port_reset_status == PORT_RESET_TMO) अणु
					pm8001_dev_gone_notअगरy(dev);
					जाओ out;
				पूर्ण
			पूर्ण

			/*
			 * 4. SATA Abort ALL
			 * we रुको क्रम the task to be पातed so that the task
			 * is हटाओd from the ccb. on success the caller is
			 * going to मुक्त the task.
			 */
			ret = pm8001_exec_पूर्णांकernal_task_पात(pm8001_ha,
				pm8001_dev, pm8001_dev->sas_device, 1, tag);
			अगर (ret)
				जाओ out;
			ret = रुको_क्रम_completion_समयout(
				&task->slow_task->completion,
				PM8001_TASK_TIMEOUT * HZ);
			अगर (!ret)
				जाओ out;

			/* 5. Set Device State as Operational */
			reinit_completion(&completion);
			pm8001_dev->setds_completion = &completion;
			PM8001_CHIP_DISP->set_dev_state_req(pm8001_ha,
				pm8001_dev, DS_OPERATIONAL);
			रुको_क्रम_completion(&completion);
		पूर्ण अन्यथा अणु
			rc = pm8001_exec_पूर्णांकernal_task_पात(pm8001_ha,
				pm8001_dev, pm8001_dev->sas_device, 0, tag);
		पूर्ण
		rc = TMF_RESP_FUNC_COMPLETE;
	पूर्ण अन्यथा अगर (task->task_proto & SAS_PROTOCOL_SMP) अणु
		/* SMP */
		rc = pm8001_exec_पूर्णांकernal_task_पात(pm8001_ha, pm8001_dev,
			pm8001_dev->sas_device, 0, tag);

	पूर्ण
out:
	spin_lock_irqsave(&task->task_state_lock, flags);
	अगर (task->slow_task == &slow_task)
		task->slow_task = शून्य;
	spin_unlock_irqrestore(&task->task_state_lock, flags);
	अगर (rc != TMF_RESP_FUNC_COMPLETE)
		pm8001_info(pm8001_ha, "rc= %d\n", rc);
	वापस rc;
पूर्ण

पूर्णांक pm8001_पात_task_set(काष्ठा करोमुख्य_device *dev, u8 *lun)
अणु
	काष्ठा pm8001_पंचांगf_task पंचांगf_task;

	पंचांगf_task.पंचांगf = TMF_ABORT_TASK_SET;
	वापस pm8001_issue_ssp_पंचांगf(dev, lun, &पंचांगf_task);
पूर्ण

पूर्णांक pm8001_clear_aca(काष्ठा करोमुख्य_device *dev, u8 *lun)
अणु
	काष्ठा pm8001_पंचांगf_task पंचांगf_task;

	पंचांगf_task.पंचांगf = TMF_CLEAR_ACA;
	वापस pm8001_issue_ssp_पंचांगf(dev, lun, &पंचांगf_task);
पूर्ण

पूर्णांक pm8001_clear_task_set(काष्ठा करोमुख्य_device *dev, u8 *lun)
अणु
	काष्ठा pm8001_पंचांगf_task पंचांगf_task;
	काष्ठा pm8001_device *pm8001_dev = dev->lldd_dev;
	काष्ठा pm8001_hba_info *pm8001_ha = pm8001_find_ha_by_dev(dev);

	pm8001_dbg(pm8001_ha, EH, "I_T_L_Q clear task set[%x]\n",
		   pm8001_dev->device_id);
	पंचांगf_task.पंचांगf = TMF_CLEAR_TASK_SET;
	वापस pm8001_issue_ssp_पंचांगf(dev, lun, &पंचांगf_task);
पूर्ण
