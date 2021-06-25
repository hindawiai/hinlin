<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St - Fअगरth Floor, Boston, MA 02110-1301 USA.
 * The full GNU General Public License is included in this distribution
 * in the file called LICENSE.GPL.
 *
 * BSD LICENSE
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the करोcumentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to enकरोrse or promote products derived
 *     from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <linux/efi.h>
#समावेश <यंत्र/माला.स>
#समावेश <scsi/scsi_host.h>
#समावेश "host.h"
#समावेश "isci.h"
#समावेश "task.h"
#समावेश "probe_roms.h"

#घोषणा MAJ 1
#घोषणा MIN 2
#घोषणा BUILD 0
#घोषणा DRV_VERSION __stringअगरy(MAJ) "." __stringअगरy(MIN) "." \
	__stringअगरy(BUILD)

MODULE_VERSION(DRV_VERSION);

अटल काष्ठा scsi_transport_ढाँचा *isci_transport_ढाँचा;

अटल स्थिर काष्ठा pci_device_id isci_id_table[] = अणु
	अणु PCI_VDEVICE(INTEL, 0x1D61),पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1D63),पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1D65),पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1D67),पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1D69),पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1D6B),पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1D60),पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1D62),पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1D64),पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1D66),पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1D68),पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1D6A),पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, isci_id_table);

/* linux isci specअगरic settings */

अचिन्हित अक्षर no_outbound_task_to = 2;
module_param(no_outbound_task_to, byte, 0);
MODULE_PARM_DESC(no_outbound_task_to, "No Outbound Task Timeout (1us incr)");

u16 ssp_max_occ_to = 20;
module_param(ssp_max_occ_to, uलघु, 0);
MODULE_PARM_DESC(ssp_max_occ_to, "SSP Max occupancy timeout (100us incr)");

u16 stp_max_occ_to = 5;
module_param(stp_max_occ_to, uलघु, 0);
MODULE_PARM_DESC(stp_max_occ_to, "STP Max occupancy timeout (100us incr)");

u16 ssp_inactive_to = 5;
module_param(ssp_inactive_to, uलघु, 0);
MODULE_PARM_DESC(ssp_inactive_to, "SSP inactivity timeout (100us incr)");

u16 stp_inactive_to = 5;
module_param(stp_inactive_to, uलघु, 0);
MODULE_PARM_DESC(stp_inactive_to, "STP inactivity timeout (100us incr)");

अचिन्हित अक्षर phy_gen = SCIC_SDS_PARM_GEN2_SPEED;
module_param(phy_gen, byte, 0);
MODULE_PARM_DESC(phy_gen, "PHY generation (1: 1.5Gbps 2: 3.0Gbps 3: 6.0Gbps)");

अचिन्हित अक्षर max_concurr_spinup;
module_param(max_concurr_spinup, byte, 0);
MODULE_PARM_DESC(max_concurr_spinup, "Max concurrent device spinup");

uपूर्णांक cable_selection_override = CABLE_OVERRIDE_DISABLED;
module_param(cable_selection_override, uपूर्णांक, 0);

MODULE_PARM_DESC(cable_selection_override,
		 "This field indicates length of the SAS/SATA cable between "
		 "host and device. If any bits > 15 are set (default) "
		 "indicates \"use platform defaults\"");

अटल sमाप_प्रकार isci_show_id(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = container_of(dev, typeof(*shost), shost_dev);
	काष्ठा sas_ha_काष्ठा *sas_ha = SHOST_TO_SAS_HA(shost);
	काष्ठा isci_host *ihost = container_of(sas_ha, typeof(*ihost), sas_ha);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", ihost->id);
पूर्ण

अटल DEVICE_ATTR(isci_id, S_IRUGO, isci_show_id, शून्य);

अटल काष्ठा device_attribute *isci_host_attrs[] = अणु
	&dev_attr_isci_id,
	शून्य
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा isci_sht = अणु

	.module				= THIS_MODULE,
	.name				= DRV_NAME,
	.proc_name			= DRV_NAME,
	.queuecommand			= sas_queuecommand,
	.dma_need_drain			= ata_scsi_dma_need_drain,
	.target_alloc			= sas_target_alloc,
	.slave_configure		= sas_slave_configure,
	.scan_finished			= isci_host_scan_finished,
	.scan_start			= isci_host_start,
	.change_queue_depth		= sas_change_queue_depth,
	.bios_param			= sas_bios_param,
	.can_queue			= ISCI_CAN_QUEUE_VAL,
	.this_id			= -1,
	.sg_tablesize			= SG_ALL,
	.max_sectors			= SCSI_DEFAULT_MAX_SECTORS,
	.eh_पात_handler		= sas_eh_पात_handler,
	.eh_device_reset_handler        = sas_eh_device_reset_handler,
	.eh_target_reset_handler        = sas_eh_target_reset_handler,
	.target_destroy			= sas_target_destroy,
	.ioctl				= sas_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl			= sas_ioctl,
#पूर्ण_अगर
	.shost_attrs			= isci_host_attrs,
	.track_queue_depth		= 1,
पूर्ण;

अटल काष्ठा sas_करोमुख्य_function_ढाँचा isci_transport_ops  = अणु

	/* The class calls these to notअगरy the LLDD of an event. */
	.lldd_port_क्रमmed	= isci_port_क्रमmed,
	.lldd_port_deक्रमmed	= isci_port_deक्रमmed,

	/* The class calls these when a device is found or gone. */
	.lldd_dev_found		= isci_remote_device_found,
	.lldd_dev_gone		= isci_remote_device_gone,

	.lldd_execute_task	= isci_task_execute_task,
	/* Task Management Functions. Must be called from process context. */
	.lldd_पात_task	= isci_task_पात_task,
	.lldd_पात_task_set	= isci_task_पात_task_set,
	.lldd_clear_aca		= isci_task_clear_aca,
	.lldd_clear_task_set	= isci_task_clear_task_set,
	.lldd_I_T_nexus_reset	= isci_task_I_T_nexus_reset,
	.lldd_lu_reset		= isci_task_lu_reset,
	.lldd_query_task	= isci_task_query_task,

	/* ata recovery called from ata-eh */
	.lldd_ata_check_पढ़ोy	= isci_ata_check_पढ़ोy,

	/* Port and Adapter management */
	.lldd_clear_nexus_port	= isci_task_clear_nexus_port,
	.lldd_clear_nexus_ha	= isci_task_clear_nexus_ha,

	/* Phy management */
	.lldd_control_phy	= isci_phy_control,

	/* GPIO support */
	.lldd_ग_लिखो_gpio	= isci_gpio_ग_लिखो,
पूर्ण;


/******************************************************************************
* P R O T E C T E D  M E T H O D S
******************************************************************************/



/**
 * isci_रेजिस्टर_sas_ha() - This method initializes various lldd
 *    specअगरic members of the sas_ha काष्ठा and calls the libsas
 *    sas_रेजिस्टर_ha() function.
 * @isci_host: This parameter specअगरies the lldd specअगरic wrapper क्रम the
 *    libsas sas_ha काष्ठा.
 *
 * This method वापसs an error code indicating success or failure. The user
 * should check क्रम possible memory allocation error वापस otherwise, a zero
 * indicates success.
 */
अटल पूर्णांक isci_रेजिस्टर_sas_ha(काष्ठा isci_host *isci_host)
अणु
	पूर्णांक i;
	काष्ठा sas_ha_काष्ठा *sas_ha = &(isci_host->sas_ha);
	काष्ठा asd_sas_phy **sas_phys;
	काष्ठा asd_sas_port **sas_ports;

	sas_phys = devm_kसुस्मृति(&isci_host->pdev->dev,
				SCI_MAX_PHYS, माप(व्योम *),
				GFP_KERNEL);
	अगर (!sas_phys)
		वापस -ENOMEM;

	sas_ports = devm_kसुस्मृति(&isci_host->pdev->dev,
				 SCI_MAX_PORTS, माप(व्योम *),
				 GFP_KERNEL);
	अगर (!sas_ports)
		वापस -ENOMEM;

	sas_ha->sas_ha_name = DRV_NAME;
	sas_ha->lldd_module = THIS_MODULE;
	sas_ha->sas_addr    = &isci_host->phys[0].sas_addr[0];

	क्रम (i = 0; i < SCI_MAX_PHYS; i++) अणु
		sas_phys[i] = &isci_host->phys[i].sas_phy;
		sas_ports[i] = &isci_host->sas_ports[i];
	पूर्ण

	sas_ha->sas_phy  = sas_phys;
	sas_ha->sas_port = sas_ports;
	sas_ha->num_phys = SCI_MAX_PHYS;

	sas_ha->strict_wide_ports = 1;

	sas_रेजिस्टर_ha(sas_ha);

	वापस 0;
पूर्ण

अटल व्योम isci_unरेजिस्टर(काष्ठा isci_host *isci_host)
अणु
	काष्ठा Scsi_Host *shost;

	अगर (!isci_host)
		वापस;

	shost = to_shost(isci_host);
	sas_unरेजिस्टर_ha(&isci_host->sas_ha);

	sas_हटाओ_host(shost);
	scsi_host_put(shost);
पूर्ण

अटल पूर्णांक isci_pci_init(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक err, bar_num, bar_mask = 0;
	व्योम __iomem * स्थिर *iomap;

	err = pcim_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"failed enable PCI device %s!\n",
			pci_name(pdev));
		वापस err;
	पूर्ण

	क्रम (bar_num = 0; bar_num < SCI_PCI_BAR_COUNT; bar_num++)
		bar_mask |= 1 << (bar_num * 2);

	err = pcim_iomap_regions(pdev, bar_mask, DRV_NAME);
	अगर (err)
		वापस err;

	iomap = pcim_iomap_table(pdev);
	अगर (!iomap)
		वापस -ENOMEM;

	pci_set_master(pdev);

	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (err)
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	वापस err;
पूर्ण

अटल पूर्णांक num_controllers(काष्ठा pci_dev *pdev)
अणु
	/* bar size alone can tell us अगर we are running with a dual controller
	 * part, no need to trust revision ids that might be under broken firmware
	 * control
	 */
	resource_माप_प्रकार scu_bar_size = pci_resource_len(pdev, SCI_SCU_BAR*2);
	resource_माप_प्रकार smu_bar_size = pci_resource_len(pdev, SCI_SMU_BAR*2);

	अगर (scu_bar_size >= SCI_SCU_BAR_SIZE*SCI_MAX_CONTROLLERS &&
	    smu_bar_size >= SCI_SMU_BAR_SIZE*SCI_MAX_CONTROLLERS)
		वापस SCI_MAX_CONTROLLERS;
	अन्यथा
		वापस 1;
पूर्ण

अटल पूर्णांक isci_setup_पूर्णांकerrupts(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक err, i, num_msix;
	काष्ठा isci_host *ihost;
	काष्ठा isci_pci_info *pci_info = to_pci_info(pdev);

	/*
	 *  Determine the number of vectors associated with this
	 *  PCI function.
	 */
	num_msix = num_controllers(pdev) * SCI_NUM_MSI_X_INT;

	err = pci_alloc_irq_vectors(pdev, num_msix, num_msix, PCI_IRQ_MSIX);
	अगर (err < 0)
		जाओ पूर्णांकx;

	क्रम (i = 0; i < num_msix; i++) अणु
		पूर्णांक id = i / SCI_NUM_MSI_X_INT;
		irq_handler_t isr;

		ihost = pci_info->hosts[id];
		/* odd numbered vectors are error पूर्णांकerrupts */
		अगर (i & 1)
			isr = isci_error_isr;
		अन्यथा
			isr = isci_msix_isr;

		err = devm_request_irq(&pdev->dev, pci_irq_vector(pdev, i),
				isr, 0, DRV_NAME"-msix", ihost);
		अगर (!err)
			जारी;

		dev_info(&pdev->dev, "msix setup failed falling back to intx\n");
		जबतक (i--) अणु
			id = i / SCI_NUM_MSI_X_INT;
			ihost = pci_info->hosts[id];
			devm_मुक्त_irq(&pdev->dev, pci_irq_vector(pdev, i),
					ihost);
		पूर्ण
		pci_मुक्त_irq_vectors(pdev);
		जाओ पूर्णांकx;
	पूर्ण
	वापस 0;

 पूर्णांकx:
	क्रम_each_isci_host(i, ihost, pdev) अणु
		err = devm_request_irq(&pdev->dev, pci_irq_vector(pdev, 0),
				isci_पूर्णांकx_isr, IRQF_SHARED, DRV_NAME"-intx",
				ihost);
		अगर (err)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम isci_user_parameters_get(काष्ठा sci_user_parameters *u)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SCI_MAX_PHYS; i++) अणु
		काष्ठा sci_phy_user_params *u_phy = &u->phys[i];

		u_phy->max_speed_generation = phy_gen;

		/* we are not exporting these क्रम now */
		u_phy->align_insertion_frequency = 0x7f;
		u_phy->in_connection_align_insertion_frequency = 0xff;
		u_phy->notअगरy_enable_spin_up_insertion_frequency = 0x33;
	पूर्ण

	u->stp_inactivity_समयout = stp_inactive_to;
	u->ssp_inactivity_समयout = ssp_inactive_to;
	u->stp_max_occupancy_समयout = stp_max_occ_to;
	u->ssp_max_occupancy_समयout = ssp_max_occ_to;
	u->no_outbound_task_समयout = no_outbound_task_to;
	u->max_concurr_spinup = max_concurr_spinup;
पूर्ण

अटल क्रमागत sci_status sci_user_parameters_set(काष्ठा isci_host *ihost,
					       काष्ठा sci_user_parameters *sci_parms)
अणु
	u16 index;

	/*
	 * Validate the user parameters.  If they are not legal, then
	 * वापस a failure.
	 */
	क्रम (index = 0; index < SCI_MAX_PHYS; index++) अणु
		काष्ठा sci_phy_user_params *u;

		u = &sci_parms->phys[index];

		अगर (!((u->max_speed_generation <= SCIC_SDS_PARM_MAX_SPEED) &&
		      (u->max_speed_generation > SCIC_SDS_PARM_NO_SPEED)))
			वापस SCI_FAILURE_INVALID_PARAMETER_VALUE;

		अगर ((u->in_connection_align_insertion_frequency < 3) ||
		    (u->align_insertion_frequency == 0) ||
		    (u->notअगरy_enable_spin_up_insertion_frequency == 0))
			वापस SCI_FAILURE_INVALID_PARAMETER_VALUE;
	पूर्ण

	अगर ((sci_parms->stp_inactivity_समयout == 0) ||
	    (sci_parms->ssp_inactivity_समयout == 0) ||
	    (sci_parms->stp_max_occupancy_समयout == 0) ||
	    (sci_parms->ssp_max_occupancy_समयout == 0) ||
	    (sci_parms->no_outbound_task_समयout == 0))
		वापस SCI_FAILURE_INVALID_PARAMETER_VALUE;

	स_नकल(&ihost->user_parameters, sci_parms, माप(*sci_parms));

	वापस SCI_SUCCESS;
पूर्ण

अटल व्योम sci_oem_शेषs(काष्ठा isci_host *ihost)
अणु
	/* these शेषs are overridden by the platक्रमm / firmware */
	काष्ठा sci_user_parameters *user = &ihost->user_parameters;
	काष्ठा sci_oem_params *oem = &ihost->oem_parameters;
	पूर्णांक i;

	/* Default to APC mode. */
	oem->controller.mode_type = SCIC_PORT_AUTOMATIC_CONFIGURATION_MODE;

	/* Default to APC mode. */
	oem->controller.max_concurr_spin_up = 1;

	/* Default to no SSC operation. */
	oem->controller.करो_enable_ssc = false;

	/* Default to लघु cables on all phys. */
	oem->controller.cable_selection_mask = 0;

	/* Initialize all of the port parameter inक्रमmation to narrow ports. */
	क्रम (i = 0; i < SCI_MAX_PORTS; i++)
		oem->ports[i].phy_mask = 0;

	/* Initialize all of the phy parameter inक्रमmation. */
	क्रम (i = 0; i < SCI_MAX_PHYS; i++) अणु
		/* Default to 3G (i.e. Gen 2). */
		user->phys[i].max_speed_generation = SCIC_SDS_PARM_GEN2_SPEED;

		/* the frequencies cannot be 0 */
		user->phys[i].align_insertion_frequency = 0x7f;
		user->phys[i].in_connection_align_insertion_frequency = 0xff;
		user->phys[i].notअगरy_enable_spin_up_insertion_frequency = 0x33;

		/* Previous Vitesse based expanders had a arbitration issue that
		 * is worked around by having the upper 32-bits of SAS address
		 * with a value greater then the Vitesse company identअगरier.
		 * Hence, usage of 0x5FCFFFFF.
		 */
		oem->phys[i].sas_address.low = 0x1 + ihost->id;
		oem->phys[i].sas_address.high = 0x5FCFFFFF;
	पूर्ण

	user->stp_inactivity_समयout = 5;
	user->ssp_inactivity_समयout = 5;
	user->stp_max_occupancy_समयout = 5;
	user->ssp_max_occupancy_समयout = 20;
	user->no_outbound_task_समयout = 2;
पूर्ण

अटल काष्ठा isci_host *isci_host_alloc(काष्ठा pci_dev *pdev, पूर्णांक id)
अणु
	काष्ठा isci_orom *orom = to_pci_info(pdev)->orom;
	काष्ठा sci_user_parameters sci_user_params;
	u8 oem_version = ISCI_ROM_VER_1_0;
	काष्ठा isci_host *ihost;
	काष्ठा Scsi_Host *shost;
	पूर्णांक err, i;

	ihost = devm_kzalloc(&pdev->dev, माप(*ihost), GFP_KERNEL);
	अगर (!ihost)
		वापस शून्य;

	ihost->pdev = pdev;
	ihost->id = id;
	spin_lock_init(&ihost->scic_lock);
	init_रुकोqueue_head(&ihost->eventq);
	ihost->sas_ha.dev = &ihost->pdev->dev;
	ihost->sas_ha.lldd_ha = ihost;
	tasklet_init(&ihost->completion_tasklet,
		     isci_host_completion_routine, (अचिन्हित दीर्घ)ihost);

	/* validate module parameters */
	/* TODO: समाप्त काष्ठा sci_user_parameters and reference directly */
	sci_oem_शेषs(ihost);
	isci_user_parameters_get(&sci_user_params);
	अगर (sci_user_parameters_set(ihost, &sci_user_params)) अणु
		dev_warn(&pdev->dev,
			 "%s: sci_user_parameters_set failed\n", __func__);
		वापस शून्य;
	पूर्ण

	/* sanity check platक्रमm (or 'firmware') oem parameters */
	अगर (orom) अणु
		अगर (id < 0 || id >= SCI_MAX_CONTROLLERS || id > orom->hdr.num_elements) अणु
			dev_warn(&pdev->dev, "parsing firmware oem parameters failed\n");
			वापस शून्य;
		पूर्ण
		ihost->oem_parameters = orom->ctrl[id];
		oem_version = orom->hdr.version;
	पूर्ण

	/* validate oem parameters (platक्रमm, firmware, or built-in शेषs) */
	अगर (sci_oem_parameters_validate(&ihost->oem_parameters, oem_version)) अणु
		dev_warn(&pdev->dev, "oem parameter validation failed\n");
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < SCI_MAX_PORTS; i++) अणु
		काष्ठा isci_port *iport = &ihost->ports[i];

		INIT_LIST_HEAD(&iport->remote_dev_list);
		iport->isci_host = ihost;
	पूर्ण

	क्रम (i = 0; i < SCI_MAX_PHYS; i++)
		isci_phy_init(&ihost->phys[i], ihost, i);

	क्रम (i = 0; i < SCI_MAX_REMOTE_DEVICES; i++) अणु
		काष्ठा isci_remote_device *idev = &ihost->devices[i];

		INIT_LIST_HEAD(&idev->node);
	पूर्ण

	shost = scsi_host_alloc(&isci_sht, माप(व्योम *));
	अगर (!shost)
		वापस शून्य;

	dev_info(&pdev->dev, "%sSCU controller %d: phy 3-0 cables: "
		 "{%s, %s, %s, %s}\n",
		 (is_cable_select_overridden() ? "* " : ""), ihost->id,
		 lookup_cable_names(decode_cable_selection(ihost, 3)),
		 lookup_cable_names(decode_cable_selection(ihost, 2)),
		 lookup_cable_names(decode_cable_selection(ihost, 1)),
		 lookup_cable_names(decode_cable_selection(ihost, 0)));

	err = isci_host_init(ihost);
	अगर (err)
		जाओ err_shost;

	SHOST_TO_SAS_HA(shost) = &ihost->sas_ha;
	ihost->sas_ha.core.shost = shost;
	shost->transportt = isci_transport_ढाँचा;

	shost->max_id = ~0;
	shost->max_lun = ~0;
	shost->max_cmd_len = MAX_COMMAND_SIZE;

	/* turn on DIF support */
	scsi_host_set_prot(shost,
			   SHOST_DIF_TYPE1_PROTECTION |
			   SHOST_DIF_TYPE2_PROTECTION |
			   SHOST_DIF_TYPE3_PROTECTION);
	scsi_host_set_guard(shost, SHOST_DIX_GUARD_CRC);

	err = scsi_add_host(shost, &pdev->dev);
	अगर (err)
		जाओ err_shost;

	err = isci_रेजिस्टर_sas_ha(ihost);
	अगर (err)
		जाओ err_shost_हटाओ;

	वापस ihost;

 err_shost_हटाओ:
	scsi_हटाओ_host(shost);
 err_shost:
	scsi_host_put(shost);

	वापस शून्य;
पूर्ण

अटल पूर्णांक isci_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा isci_pci_info *pci_info;
	पूर्णांक err, i;
	काष्ठा isci_host *isci_host;
	स्थिर काष्ठा firmware *fw = शून्य;
	काष्ठा isci_orom *orom = शून्य;
	अक्षर *source = "(platform)";

	dev_info(&pdev->dev, "driver configured for rev: %d silicon\n",
		 pdev->revision);

	pci_info = devm_kzalloc(&pdev->dev, माप(*pci_info), GFP_KERNEL);
	अगर (!pci_info)
		वापस -ENOMEM;
	pci_set_drvdata(pdev, pci_info);

	अगर (efi_rt_services_supported(EFI_RT_SUPPORTED_GET_VARIABLE))
		orom = isci_get_efi_var(pdev);

	अगर (!orom)
		orom = isci_request_oprom(pdev);

	क्रम (i = 0; orom && i < num_controllers(pdev); i++) अणु
		अगर (sci_oem_parameters_validate(&orom->ctrl[i],
						orom->hdr.version)) अणु
			dev_warn(&pdev->dev,
				 "[%d]: invalid oem parameters detected, falling back to firmware\n", i);
			orom = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!orom) अणु
		source = "(firmware)";
		orom = isci_request_firmware(pdev, fw);
		अगर (!orom) अणु
			/* TODO convert this to WARN_TAINT_ONCE once the
			 * orom/efi parameter support is widely available
			 */
			dev_warn(&pdev->dev,
				 "Loading user firmware failed, using default "
				 "values\n");
			dev_warn(&pdev->dev,
				 "Default OEM configuration being used: 4 "
				 "narrow ports, and default SAS Addresses\n");
		पूर्ण
	पूर्ण

	अगर (orom)
		dev_info(&pdev->dev,
			 "OEM SAS parameters (version: %u.%u) loaded %s\n",
			 (orom->hdr.version & 0xf0) >> 4,
			 (orom->hdr.version & 0xf), source);

	pci_info->orom = orom;

	err = isci_pci_init(pdev);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < num_controllers(pdev); i++) अणु
		काष्ठा isci_host *h = isci_host_alloc(pdev, i);

		अगर (!h) अणु
			err = -ENOMEM;
			जाओ err_host_alloc;
		पूर्ण
		pci_info->hosts[i] = h;
	पूर्ण

	err = isci_setup_पूर्णांकerrupts(pdev);
	अगर (err)
		जाओ err_host_alloc;

	क्रम_each_isci_host(i, isci_host, pdev)
		scsi_scan_host(to_shost(isci_host));

	वापस 0;

 err_host_alloc:
	क्रम_each_isci_host(i, isci_host, pdev)
		isci_unरेजिस्टर(isci_host);
	वापस err;
पूर्ण

अटल व्योम isci_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा isci_host *ihost;
	पूर्णांक i;

	क्रम_each_isci_host(i, ihost, pdev) अणु
		रुको_क्रम_start(ihost);
		isci_unरेजिस्टर(ihost);
		isci_host_deinit(ihost);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक isci_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा isci_host *ihost;
	पूर्णांक i;

	क्रम_each_isci_host(i, ihost, pdev) अणु
		sas_suspend_ha(&ihost->sas_ha);
		isci_host_deinit(ihost);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक isci_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा isci_host *ihost;
	पूर्णांक i;

	क्रम_each_isci_host(i, ihost, pdev) अणु
		sas_prep_resume_ha(&ihost->sas_ha);

		isci_host_init(ihost);
		isci_host_start(ihost->sas_ha.core.shost);
		रुको_क्रम_start(ihost);

		sas_resume_ha(&ihost->sas_ha);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(isci_pm_ops, isci_suspend, isci_resume);

अटल काष्ठा pci_driver isci_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= isci_id_table,
	.probe		= isci_pci_probe,
	.हटाओ		= isci_pci_हटाओ,
	.driver.pm      = &isci_pm_ops,
पूर्ण;

अटल __init पूर्णांक isci_init(व्योम)
अणु
	पूर्णांक err;

	pr_info("%s: Intel(R) C600 SAS Controller Driver - version %s\n",
		DRV_NAME, DRV_VERSION);

	isci_transport_ढाँचा = sas_करोमुख्य_attach_transport(&isci_transport_ops);
	अगर (!isci_transport_ढाँचा)
		वापस -ENOMEM;

	err = pci_रेजिस्टर_driver(&isci_pci_driver);
	अगर (err)
		sas_release_transport(isci_transport_ढाँचा);

	वापस err;
पूर्ण

अटल __निकास व्योम isci_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&isci_pci_driver);
	sas_release_transport(isci_transport_ढाँचा);
पूर्ण

MODULE_LICENSE("Dual BSD/GPL");
MODULE_FIRMWARE(ISCI_FW_NAME);
module_init(isci_init);
module_निकास(isci_निकास);
