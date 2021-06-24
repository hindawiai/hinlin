<शैली गुरु>
/*
*******************************************************************************
**        O.S   : Linux
**   खाता NAME  : arcmsr_hba.c
**        BY    : Nick Cheng, C.L. Huang
**   Description: SCSI RAID Device Driver क्रम Areca RAID Controller
*******************************************************************************
** Copyright (C) 2002 - 2014, Areca Technology Corporation All rights reserved
**
**     Web site: www.areca.com.tw
**       E-mail: support@areca.com.tw
**
** This program is मुक्त software; you can redistribute it and/or modअगरy
** it under the terms of the GNU General Public License version 2 as
** published by the Free Software Foundation.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License क्रम more details.
*******************************************************************************
** Redistribution and use in source and binary क्रमms, with or without
** modअगरication, are permitted provided that the following conditions
** are met:
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary क्रमm must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    करोcumentation and/or other materials provided with the distribution.
** 3. The name of the author may not be used to enकरोrse or promote products
**    derived from this software without specअगरic prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
** IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING,BUT
** NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION)HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE)ARISING IN ANY WAY OUT OF THE USE OF
** THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************
** For history of changes, see Documentation/scsi/ChangeLog.arcmsr
**     Firmware Specअगरication, see Documentation/scsi/arcmsr_spec.rst
*******************************************************************************
*/
#समावेश <linux/module.h>
#समावेश <linux/reboot.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/समयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/aer.h>
#समावेश <linux/circ_buf.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsicam.h>
#समावेश "arcmsr.h"
MODULE_AUTHOR("Nick Cheng, C.L. Huang <support@areca.com.tw>");
MODULE_DESCRIPTION("Areca ARC11xx/12xx/16xx/188x SAS/SATA RAID Controller Driver");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION(ARCMSR_DRIVER_VERSION);

अटल पूर्णांक msix_enable = 1;
module_param(msix_enable, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(msix_enable, "Enable MSI-X interrupt(0 ~ 1), msix_enable=1(enable), =0(disable)");

अटल पूर्णांक msi_enable = 1;
module_param(msi_enable, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(msi_enable, "Enable MSI interrupt(0 ~ 1), msi_enable=1(enable), =0(disable)");

अटल पूर्णांक host_can_queue = ARCMSR_DEFAULT_OUTSTANDING_CMD;
module_param(host_can_queue, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(host_can_queue, " adapter queue depth(32 ~ 1024), default is 128");

अटल पूर्णांक cmd_per_lun = ARCMSR_DEFAULT_CMD_PERLUN;
module_param(cmd_per_lun, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(cmd_per_lun, " device queue depth(1 ~ 128), default is 32");

अटल पूर्णांक dma_mask_64 = 0;
module_param(dma_mask_64, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(dma_mask_64, " set DMA mask to 64 bits(0 ~ 1), dma_mask_64=1(64 bits), =0(32 bits)");

अटल पूर्णांक set_date_समय = 0;
module_param(set_date_समय, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(set_date_समय, " send date, time to iop(0 ~ 1), set_date_time=1(enable), default(=0) is disable");

अटल पूर्णांक cmd_समयout = ARCMSR_DEFAULT_TIMEOUT;
module_param(cmd_समयout, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(cmd_समयout, " scsi cmd timeout(0 ~ 120 sec.), default is 90");

#घोषणा	ARCMSR_SLEEPTIME	10
#घोषणा	ARCMSR_RETRYCOUNT	12

अटल रुको_queue_head_t रुको_q;
अटल पूर्णांक arcmsr_iop_message_xfer(काष्ठा AdapterControlBlock *acb,
					काष्ठा scsi_cmnd *cmd);
अटल पूर्णांक arcmsr_iop_confirm(काष्ठा AdapterControlBlock *acb);
अटल पूर्णांक arcmsr_पात(काष्ठा scsi_cmnd *);
अटल पूर्णांक arcmsr_bus_reset(काष्ठा scsi_cmnd *);
अटल पूर्णांक arcmsr_bios_param(काष्ठा scsi_device *sdev,
		काष्ठा block_device *bdev, sector_t capacity, पूर्णांक *info);
अटल पूर्णांक arcmsr_queue_command(काष्ठा Scsi_Host *h, काष्ठा scsi_cmnd *cmd);
अटल पूर्णांक arcmsr_probe(काष्ठा pci_dev *pdev,
				स्थिर काष्ठा pci_device_id *id);
अटल पूर्णांक __maybe_unused arcmsr_suspend(काष्ठा device *dev);
अटल पूर्णांक __maybe_unused arcmsr_resume(काष्ठा device *dev);
अटल व्योम arcmsr_हटाओ(काष्ठा pci_dev *pdev);
अटल व्योम arcmsr_shutकरोwn(काष्ठा pci_dev *pdev);
अटल व्योम arcmsr_iop_init(काष्ठा AdapterControlBlock *acb);
अटल व्योम arcmsr_मुक्त_ccb_pool(काष्ठा AdapterControlBlock *acb);
अटल u32 arcmsr_disable_outbound_पूर्णांकs(काष्ठा AdapterControlBlock *acb);
अटल व्योम arcmsr_enable_outbound_पूर्णांकs(काष्ठा AdapterControlBlock *acb,
	u32 पूर्णांकmask_org);
अटल व्योम arcmsr_stop_adapter_bgrb(काष्ठा AdapterControlBlock *acb);
अटल व्योम arcmsr_hbaA_flush_cache(काष्ठा AdapterControlBlock *acb);
अटल व्योम arcmsr_hbaB_flush_cache(काष्ठा AdapterControlBlock *acb);
अटल व्योम arcmsr_request_device_map(काष्ठा समयr_list *t);
अटल व्योम arcmsr_message_isr_bh_fn(काष्ठा work_काष्ठा *work);
अटल bool arcmsr_get_firmware_spec(काष्ठा AdapterControlBlock *acb);
अटल व्योम arcmsr_start_adapter_bgrb(काष्ठा AdapterControlBlock *acb);
अटल व्योम arcmsr_hbaC_message_isr(काष्ठा AdapterControlBlock *pACB);
अटल व्योम arcmsr_hbaD_message_isr(काष्ठा AdapterControlBlock *acb);
अटल व्योम arcmsr_hbaE_message_isr(काष्ठा AdapterControlBlock *acb);
अटल व्योम arcmsr_hbaE_postqueue_isr(काष्ठा AdapterControlBlock *acb);
अटल व्योम arcmsr_hbaF_postqueue_isr(काष्ठा AdapterControlBlock *acb);
अटल व्योम arcmsr_hardware_reset(काष्ठा AdapterControlBlock *acb);
अटल स्थिर अक्षर *arcmsr_info(काष्ठा Scsi_Host *);
अटल irqवापस_t arcmsr_पूर्णांकerrupt(काष्ठा AdapterControlBlock *acb);
अटल व्योम arcmsr_मुक्त_irq(काष्ठा pci_dev *, काष्ठा AdapterControlBlock *);
अटल व्योम arcmsr_रुको_firmware_पढ़ोy(काष्ठा AdapterControlBlock *acb);
अटल व्योम arcmsr_set_iop_dateसमय(काष्ठा समयr_list *);
अटल पूर्णांक arcmsr_slave_config(काष्ठा scsi_device *sdev);
अटल पूर्णांक arcmsr_adjust_disk_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक queue_depth)
अणु
	अगर (queue_depth > ARCMSR_MAX_CMD_PERLUN)
		queue_depth = ARCMSR_MAX_CMD_PERLUN;
	वापस scsi_change_queue_depth(sdev, queue_depth);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा arcmsr_scsi_host_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "Areca SAS/SATA RAID driver",
	.info			= arcmsr_info,
	.queuecommand		= arcmsr_queue_command,
	.eh_पात_handler	= arcmsr_पात,
	.eh_bus_reset_handler	= arcmsr_bus_reset,
	.bios_param		= arcmsr_bios_param,
	.slave_configure	= arcmsr_slave_config,
	.change_queue_depth	= arcmsr_adjust_disk_queue_depth,
	.can_queue		= ARCMSR_DEFAULT_OUTSTANDING_CMD,
	.this_id		= ARCMSR_SCSI_INITIATOR_ID,
	.sg_tablesize	        = ARCMSR_DEFAULT_SG_ENTRIES,
	.max_sectors		= ARCMSR_MAX_XFER_SECTORS_C,
	.cmd_per_lun		= ARCMSR_DEFAULT_CMD_PERLUN,
	.shost_attrs		= arcmsr_host_attrs,
	.no_ग_लिखो_same		= 1,
पूर्ण;

अटल काष्ठा pci_device_id arcmsr_device_id_table[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1110),
		.driver_data = ACB_ADAPTER_TYPE_Aपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1120),
		.driver_data = ACB_ADAPTER_TYPE_Aपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1130),
		.driver_data = ACB_ADAPTER_TYPE_Aपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1160),
		.driver_data = ACB_ADAPTER_TYPE_Aपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1170),
		.driver_data = ACB_ADAPTER_TYPE_Aपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1200),
		.driver_data = ACB_ADAPTER_TYPE_Bपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1201),
		.driver_data = ACB_ADAPTER_TYPE_Bपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1202),
		.driver_data = ACB_ADAPTER_TYPE_Bपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1203),
		.driver_data = ACB_ADAPTER_TYPE_Bपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1210),
		.driver_data = ACB_ADAPTER_TYPE_Aपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1214),
		.driver_data = ACB_ADAPTER_TYPE_Dपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1220),
		.driver_data = ACB_ADAPTER_TYPE_Aपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1230),
		.driver_data = ACB_ADAPTER_TYPE_Aपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1260),
		.driver_data = ACB_ADAPTER_TYPE_Aपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1270),
		.driver_data = ACB_ADAPTER_TYPE_Aपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1280),
		.driver_data = ACB_ADAPTER_TYPE_Aपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1380),
		.driver_data = ACB_ADAPTER_TYPE_Aपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1381),
		.driver_data = ACB_ADAPTER_TYPE_Aपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1680),
		.driver_data = ACB_ADAPTER_TYPE_Aपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1681),
		.driver_data = ACB_ADAPTER_TYPE_Aपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1880),
		.driver_data = ACB_ADAPTER_TYPE_Cपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1884),
		.driver_data = ACB_ADAPTER_TYPE_Eपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ARECA, PCI_DEVICE_ID_ARECA_1886),
		.driver_data = ACB_ADAPTER_TYPE_Fपूर्ण,
	अणु0, 0पूर्ण, /* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(pci, arcmsr_device_id_table);

अटल SIMPLE_DEV_PM_OPS(arcmsr_pm_ops, arcmsr_suspend, arcmsr_resume);

अटल काष्ठा pci_driver arcmsr_pci_driver = अणु
	.name			= "arcmsr",
	.id_table		= arcmsr_device_id_table,
	.probe			= arcmsr_probe,
	.हटाओ			= arcmsr_हटाओ,
	.driver.pm		= &arcmsr_pm_ops,
	.shutकरोwn		= arcmsr_shutकरोwn,
पूर्ण;
/*
****************************************************************************
****************************************************************************
*/

अटल व्योम arcmsr_मुक्त_io_queue(काष्ठा AdapterControlBlock *acb)
अणु
	चयन (acb->adapter_type) अणु
	हाल ACB_ADAPTER_TYPE_B:
	हाल ACB_ADAPTER_TYPE_D:
	हाल ACB_ADAPTER_TYPE_E:
	हाल ACB_ADAPTER_TYPE_F:
		dma_मुक्त_coherent(&acb->pdev->dev, acb->ioqueue_size,
			acb->dma_coherent2, acb->dma_coherent_handle2);
		अवरोध;
	पूर्ण
पूर्ण

अटल bool arcmsr_remap_pciregion(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा pci_dev *pdev = acb->pdev;
	चयन (acb->adapter_type)अणु
	हाल ACB_ADAPTER_TYPE_A:अणु
		acb->pmuA = ioremap(pci_resource_start(pdev,0), pci_resource_len(pdev,0));
		अगर (!acb->pmuA) अणु
			prपूर्णांकk(KERN_NOTICE "arcmsr%d: memory mapping region fail \n", acb->host->host_no);
			वापस false;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल ACB_ADAPTER_TYPE_B:अणु
		व्योम __iomem *mem_base0, *mem_base1;
		mem_base0 = ioremap(pci_resource_start(pdev, 0), pci_resource_len(pdev, 0));
		अगर (!mem_base0) अणु
			prपूर्णांकk(KERN_NOTICE "arcmsr%d: memory mapping region fail \n", acb->host->host_no);
			वापस false;
		पूर्ण
		mem_base1 = ioremap(pci_resource_start(pdev, 2), pci_resource_len(pdev, 2));
		अगर (!mem_base1) अणु
			iounmap(mem_base0);
			prपूर्णांकk(KERN_NOTICE "arcmsr%d: memory mapping region fail \n", acb->host->host_no);
			वापस false;
		पूर्ण
		acb->mem_base0 = mem_base0;
		acb->mem_base1 = mem_base1;
		अवरोध;
	पूर्ण
	हाल ACB_ADAPTER_TYPE_C:अणु
		acb->pmuC = ioremap(pci_resource_start(pdev, 1), pci_resource_len(pdev, 1));
		अगर (!acb->pmuC) अणु
			prपूर्णांकk(KERN_NOTICE "arcmsr%d: memory mapping region fail \n", acb->host->host_no);
			वापस false;
		पूर्ण
		अगर (पढ़ोl(&acb->pmuC->outbound_करोorbell) & ARCMSR_HBCMU_IOP2DRV_MESSAGE_CMD_DONE) अणु
			ग_लिखोl(ARCMSR_HBCMU_IOP2DRV_MESSAGE_CMD_DONE_DOORBELL_CLEAR, &acb->pmuC->outbound_करोorbell_clear);/*clear पूर्णांकerrupt*/
			वापस true;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल ACB_ADAPTER_TYPE_D: अणु
		व्योम __iomem *mem_base0;
		अचिन्हित दीर्घ addr, range;

		addr = (अचिन्हित दीर्घ)pci_resource_start(pdev, 0);
		range = pci_resource_len(pdev, 0);
		mem_base0 = ioremap(addr, range);
		अगर (!mem_base0) अणु
			pr_notice("arcmsr%d: memory mapping region fail\n",
				acb->host->host_no);
			वापस false;
		पूर्ण
		acb->mem_base0 = mem_base0;
		अवरोध;
		पूर्ण
	हाल ACB_ADAPTER_TYPE_E: अणु
		acb->pmuE = ioremap(pci_resource_start(pdev, 1),
			pci_resource_len(pdev, 1));
		अगर (!acb->pmuE) अणु
			pr_notice("arcmsr%d: memory mapping region fail \n",
				acb->host->host_no);
			वापस false;
		पूर्ण
		ग_लिखोl(0, &acb->pmuE->host_पूर्णांक_status); /*clear पूर्णांकerrupt*/
		ग_लिखोl(ARCMSR_HBEMU_DOORBELL_SYNC, &acb->pmuE->iobound_करोorbell);	/* synchronize करोorbell to 0 */
		acb->in_करोorbell = 0;
		acb->out_करोorbell = 0;
		अवरोध;
		पूर्ण
	हाल ACB_ADAPTER_TYPE_F: अणु
		acb->pmuF = ioremap(pci_resource_start(pdev, 0), pci_resource_len(pdev, 0));
		अगर (!acb->pmuF) अणु
			pr_notice("arcmsr%d: memory mapping region fail\n",
				acb->host->host_no);
			वापस false;
		पूर्ण
		ग_लिखोl(0, &acb->pmuF->host_पूर्णांक_status); /* clear पूर्णांकerrupt */
		ग_लिखोl(ARCMSR_HBFMU_DOORBELL_SYNC, &acb->pmuF->iobound_करोorbell);
		acb->in_करोorbell = 0;
		acb->out_करोorbell = 0;
		अवरोध;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम arcmsr_unmap_pciregion(काष्ठा AdapterControlBlock *acb)
अणु
	चयन (acb->adapter_type) अणु
	हाल ACB_ADAPTER_TYPE_A:
		iounmap(acb->pmuA);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_B:
		iounmap(acb->mem_base0);
		iounmap(acb->mem_base1);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_C:
		iounmap(acb->pmuC);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_D:
		iounmap(acb->mem_base0);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_E:
		iounmap(acb->pmuE);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_F:
		iounmap(acb->pmuF);
		अवरोध;
	पूर्ण
पूर्ण

अटल irqवापस_t arcmsr_करो_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	irqवापस_t handle_state;
	काष्ठा AdapterControlBlock *acb = dev_id;

	handle_state = arcmsr_पूर्णांकerrupt(acb);
	वापस handle_state;
पूर्ण

अटल पूर्णांक arcmsr_bios_param(काष्ठा scsi_device *sdev,
		काष्ठा block_device *bdev, sector_t capacity, पूर्णांक *geom)
अणु
	पूर्णांक heads, sectors, cylinders, total_capacity;

	अगर (scsi_partsize(bdev, capacity, geom))
		वापस 0;

	total_capacity = capacity;
	heads = 64;
	sectors = 32;
	cylinders = total_capacity / (heads * sectors);
	अगर (cylinders > 1024) अणु
		heads = 255;
		sectors = 63;
		cylinders = total_capacity / (heads * sectors);
	पूर्ण
	geom[0] = heads;
	geom[1] = sectors;
	geom[2] = cylinders;
	वापस 0;
पूर्ण

अटल uपूर्णांक8_t arcmsr_hbaA_रुको_msgपूर्णांक_पढ़ोy(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;
	पूर्णांक i;

	क्रम (i = 0; i < 2000; i++) अणु
		अगर (पढ़ोl(&reg->outbound_पूर्णांकstatus) &
				ARCMSR_MU_OUTBOUND_MESSAGE0_INT) अणु
			ग_लिखोl(ARCMSR_MU_OUTBOUND_MESSAGE0_INT,
				&reg->outbound_पूर्णांकstatus);
			वापस true;
		पूर्ण
		msleep(10);
	पूर्ण /* max 20 seconds */

	वापस false;
पूर्ण

अटल uपूर्णांक8_t arcmsr_hbaB_रुको_msgपूर्णांक_पढ़ोy(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा MessageUnit_B *reg = acb->pmuB;
	पूर्णांक i;

	क्रम (i = 0; i < 2000; i++) अणु
		अगर (पढ़ोl(reg->iop2drv_करोorbell)
			& ARCMSR_IOP2DRV_MESSAGE_CMD_DONE) अणु
			ग_लिखोl(ARCMSR_MESSAGE_INT_CLEAR_PATTERN,
					reg->iop2drv_करोorbell);
			ग_लिखोl(ARCMSR_DRV2IOP_END_OF_INTERRUPT,
					reg->drv2iop_करोorbell);
			वापस true;
		पूर्ण
		msleep(10);
	पूर्ण /* max 20 seconds */

	वापस false;
पूर्ण

अटल uपूर्णांक8_t arcmsr_hbaC_रुको_msgपूर्णांक_पढ़ोy(काष्ठा AdapterControlBlock *pACB)
अणु
	काष्ठा MessageUnit_C __iomem *phbcmu = pACB->pmuC;
	पूर्णांक i;

	क्रम (i = 0; i < 2000; i++) अणु
		अगर (पढ़ोl(&phbcmu->outbound_करोorbell)
				& ARCMSR_HBCMU_IOP2DRV_MESSAGE_CMD_DONE) अणु
			ग_लिखोl(ARCMSR_HBCMU_IOP2DRV_MESSAGE_CMD_DONE_DOORBELL_CLEAR,
				&phbcmu->outbound_करोorbell_clear); /*clear पूर्णांकerrupt*/
			वापस true;
		पूर्ण
		msleep(10);
	पूर्ण /* max 20 seconds */

	वापस false;
पूर्ण

अटल bool arcmsr_hbaD_रुको_msgपूर्णांक_पढ़ोy(काष्ठा AdapterControlBlock *pACB)
अणु
	काष्ठा MessageUnit_D *reg = pACB->pmuD;
	पूर्णांक i;

	क्रम (i = 0; i < 2000; i++) अणु
		अगर (पढ़ोl(reg->outbound_करोorbell)
			& ARCMSR_ARC1214_IOP2DRV_MESSAGE_CMD_DONE) अणु
			ग_लिखोl(ARCMSR_ARC1214_IOP2DRV_MESSAGE_CMD_DONE,
				reg->outbound_करोorbell);
			वापस true;
		पूर्ण
		msleep(10);
	पूर्ण /* max 20 seconds */
	वापस false;
पूर्ण

अटल bool arcmsr_hbaE_रुको_msgपूर्णांक_पढ़ोy(काष्ठा AdapterControlBlock *pACB)
अणु
	पूर्णांक i;
	uपूर्णांक32_t पढ़ो_करोorbell;
	काष्ठा MessageUnit_E __iomem *phbcmu = pACB->pmuE;

	क्रम (i = 0; i < 2000; i++) अणु
		पढ़ो_करोorbell = पढ़ोl(&phbcmu->iobound_करोorbell);
		अगर ((पढ़ो_करोorbell ^ pACB->in_करोorbell) & ARCMSR_HBEMU_IOP2DRV_MESSAGE_CMD_DONE) अणु
			ग_लिखोl(0, &phbcmu->host_पूर्णांक_status); /*clear पूर्णांकerrupt*/
			pACB->in_करोorbell = पढ़ो_करोorbell;
			वापस true;
		पूर्ण
		msleep(10);
	पूर्ण /* max 20 seconds */
	वापस false;
पूर्ण

अटल व्योम arcmsr_hbaA_flush_cache(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;
	पूर्णांक retry_count = 30;
	ग_लिखोl(ARCMSR_INBOUND_MESG0_FLUSH_CACHE, &reg->inbound_msgaddr0);
	करो अणु
		अगर (arcmsr_hbaA_रुको_msgपूर्णांक_पढ़ोy(acb))
			अवरोध;
		अन्यथा अणु
			retry_count--;
			prपूर्णांकk(KERN_NOTICE "arcmsr%d: रुको 'flush adapter cache' \
			समयout, retry count करोwn = %d \न", acb->host->host_no, retry_count);
		पूर्ण
	पूर्ण जबतक (retry_count != 0);
पूर्ण

अटल व्योम arcmsr_hbaB_flush_cache(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा MessageUnit_B *reg = acb->pmuB;
	पूर्णांक retry_count = 30;
	ग_लिखोl(ARCMSR_MESSAGE_FLUSH_CACHE, reg->drv2iop_करोorbell);
	करो अणु
		अगर (arcmsr_hbaB_रुको_msgपूर्णांक_पढ़ोy(acb))
			अवरोध;
		अन्यथा अणु
			retry_count--;
			prपूर्णांकk(KERN_NOTICE "arcmsr%d: रुको 'flush adapter cache' \
			समयout,retry count करोwn = %d \न", acb->host->host_no, retry_count);
		पूर्ण
	पूर्ण जबतक (retry_count != 0);
पूर्ण

अटल व्योम arcmsr_hbaC_flush_cache(काष्ठा AdapterControlBlock *pACB)
अणु
	काष्ठा MessageUnit_C __iomem *reg = pACB->pmuC;
	पूर्णांक retry_count = 30;/* enlarge रुको flush adapter cache समय: 10 minute */
	ग_लिखोl(ARCMSR_INBOUND_MESG0_FLUSH_CACHE, &reg->inbound_msgaddr0);
	ग_लिखोl(ARCMSR_HBCMU_DRV2IOP_MESSAGE_CMD_DONE, &reg->inbound_करोorbell);
	करो अणु
		अगर (arcmsr_hbaC_रुको_msgपूर्णांक_पढ़ोy(pACB)) अणु
			अवरोध;
		पूर्ण अन्यथा अणु
			retry_count--;
			prपूर्णांकk(KERN_NOTICE "arcmsr%d: रुको 'flush adapter cache' \
			समयout,retry count करोwn = %d \न", pACB->host->host_no, retry_count);
		पूर्ण
	पूर्ण जबतक (retry_count != 0);
	वापस;
पूर्ण

अटल व्योम arcmsr_hbaD_flush_cache(काष्ठा AdapterControlBlock *pACB)
अणु
	पूर्णांक retry_count = 15;
	काष्ठा MessageUnit_D *reg = pACB->pmuD;

	ग_लिखोl(ARCMSR_INBOUND_MESG0_FLUSH_CACHE, reg->inbound_msgaddr0);
	करो अणु
		अगर (arcmsr_hbaD_रुको_msgपूर्णांक_पढ़ोy(pACB))
			अवरोध;

		retry_count--;
		pr_notice("arcmsr%d: wait 'flush adapter "
			"cache' timeout, retry count down = %d\n",
			pACB->host->host_no, retry_count);
	पूर्ण जबतक (retry_count != 0);
पूर्ण

अटल व्योम arcmsr_hbaE_flush_cache(काष्ठा AdapterControlBlock *pACB)
अणु
	पूर्णांक retry_count = 30;
	काष्ठा MessageUnit_E __iomem *reg = pACB->pmuE;

	ग_लिखोl(ARCMSR_INBOUND_MESG0_FLUSH_CACHE, &reg->inbound_msgaddr0);
	pACB->out_करोorbell ^= ARCMSR_HBEMU_DRV2IOP_MESSAGE_CMD_DONE;
	ग_लिखोl(pACB->out_करोorbell, &reg->iobound_करोorbell);
	करो अणु
		अगर (arcmsr_hbaE_रुको_msgपूर्णांक_पढ़ोy(pACB))
			अवरोध;
		retry_count--;
		pr_notice("arcmsr%d: wait 'flush adapter "
			"cache' timeout, retry count down = %d\n",
			pACB->host->host_no, retry_count);
	पूर्ण जबतक (retry_count != 0);
पूर्ण

अटल व्योम arcmsr_flush_adapter_cache(काष्ठा AdapterControlBlock *acb)
अणु
	चयन (acb->adapter_type) अणु

	हाल ACB_ADAPTER_TYPE_A:
		arcmsr_hbaA_flush_cache(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_B:
		arcmsr_hbaB_flush_cache(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_C:
		arcmsr_hbaC_flush_cache(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_D:
		arcmsr_hbaD_flush_cache(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_E:
	हाल ACB_ADAPTER_TYPE_F:
		arcmsr_hbaE_flush_cache(acb);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम arcmsr_hbaB_assign_regAddr(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा MessageUnit_B *reg = acb->pmuB;

	अगर (acb->pdev->device == PCI_DEVICE_ID_ARECA_1203) अणु
		reg->drv2iop_करोorbell = MEM_BASE0(ARCMSR_DRV2IOP_DOORBELL_1203);
		reg->drv2iop_करोorbell_mask = MEM_BASE0(ARCMSR_DRV2IOP_DOORBELL_MASK_1203);
		reg->iop2drv_करोorbell = MEM_BASE0(ARCMSR_IOP2DRV_DOORBELL_1203);
		reg->iop2drv_करोorbell_mask = MEM_BASE0(ARCMSR_IOP2DRV_DOORBELL_MASK_1203);
	पूर्ण अन्यथा अणु
		reg->drv2iop_करोorbell= MEM_BASE0(ARCMSR_DRV2IOP_DOORBELL);
		reg->drv2iop_करोorbell_mask = MEM_BASE0(ARCMSR_DRV2IOP_DOORBELL_MASK);
		reg->iop2drv_करोorbell = MEM_BASE0(ARCMSR_IOP2DRV_DOORBELL);
		reg->iop2drv_करोorbell_mask = MEM_BASE0(ARCMSR_IOP2DRV_DOORBELL_MASK);
	पूर्ण
	reg->message_wbuffer = MEM_BASE1(ARCMSR_MESSAGE_WBUFFER);
	reg->message_rbuffer =  MEM_BASE1(ARCMSR_MESSAGE_RBUFFER);
	reg->message_rwbuffer = MEM_BASE1(ARCMSR_MESSAGE_RWBUFFER);
पूर्ण

अटल व्योम arcmsr_hbaD_assign_regAddr(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा MessageUnit_D *reg = acb->pmuD;

	reg->chip_id = MEM_BASE0(ARCMSR_ARC1214_CHIP_ID);
	reg->cpu_mem_config = MEM_BASE0(ARCMSR_ARC1214_CPU_MEMORY_CONFIGURATION);
	reg->i2o_host_पूर्णांकerrupt_mask = MEM_BASE0(ARCMSR_ARC1214_I2_HOST_INTERRUPT_MASK);
	reg->sample_at_reset = MEM_BASE0(ARCMSR_ARC1214_SAMPLE_RESET);
	reg->reset_request = MEM_BASE0(ARCMSR_ARC1214_RESET_REQUEST);
	reg->host_पूर्णांक_status = MEM_BASE0(ARCMSR_ARC1214_MAIN_INTERRUPT_STATUS);
	reg->pcief0_पूर्णांक_enable = MEM_BASE0(ARCMSR_ARC1214_PCIE_F0_INTERRUPT_ENABLE);
	reg->inbound_msgaddr0 = MEM_BASE0(ARCMSR_ARC1214_INBOUND_MESSAGE0);
	reg->inbound_msgaddr1 = MEM_BASE0(ARCMSR_ARC1214_INBOUND_MESSAGE1);
	reg->outbound_msgaddr0 = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_MESSAGE0);
	reg->outbound_msgaddr1 = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_MESSAGE1);
	reg->inbound_करोorbell = MEM_BASE0(ARCMSR_ARC1214_INBOUND_DOORBELL);
	reg->outbound_करोorbell = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_DOORBELL);
	reg->outbound_करोorbell_enable = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_DOORBELL_ENABLE);
	reg->inboundlist_base_low = MEM_BASE0(ARCMSR_ARC1214_INBOUND_LIST_BASE_LOW);
	reg->inboundlist_base_high = MEM_BASE0(ARCMSR_ARC1214_INBOUND_LIST_BASE_HIGH);
	reg->inboundlist_ग_लिखो_poपूर्णांकer = MEM_BASE0(ARCMSR_ARC1214_INBOUND_LIST_WRITE_POINTER);
	reg->outboundlist_base_low = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_LIST_BASE_LOW);
	reg->outboundlist_base_high = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_LIST_BASE_HIGH);
	reg->outboundlist_copy_poपूर्णांकer = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_LIST_COPY_POINTER);
	reg->outboundlist_पढ़ो_poपूर्णांकer = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_LIST_READ_POINTER);
	reg->outboundlist_पूर्णांकerrupt_cause = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_INTERRUPT_CAUSE);
	reg->outboundlist_पूर्णांकerrupt_enable = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_INTERRUPT_ENABLE);
	reg->message_wbuffer = MEM_BASE0(ARCMSR_ARC1214_MESSAGE_WBUFFER);
	reg->message_rbuffer = MEM_BASE0(ARCMSR_ARC1214_MESSAGE_RBUFFER);
	reg->msgcode_rwbuffer = MEM_BASE0(ARCMSR_ARC1214_MESSAGE_RWBUFFER);
पूर्ण

अटल व्योम arcmsr_hbaF_assign_regAddr(काष्ठा AdapterControlBlock *acb)
अणु
	dma_addr_t host_buffer_dma;
	काष्ठा MessageUnit_F __iomem *pmuF;

	स_रखो(acb->dma_coherent2, 0xff, acb->completeQ_size);
	acb->message_wbuffer = (uपूर्णांक32_t *)round_up((अचिन्हित दीर्घ)acb->dma_coherent2 +
		acb->completeQ_size, 4);
	acb->message_rbuffer = ((व्योम *)acb->message_wbuffer) + 0x100;
	acb->msgcode_rwbuffer = ((व्योम *)acb->message_wbuffer) + 0x200;
	स_रखो((व्योम *)acb->message_wbuffer, 0, MESG_RW_BUFFER_SIZE);
	host_buffer_dma = round_up(acb->dma_coherent_handle2 + acb->completeQ_size, 4);
	pmuF = acb->pmuF;
	/* host buffer low address, bit0:1 all buffer active */
	ग_लिखोl(lower_32_bits(host_buffer_dma | 1), &pmuF->inbound_msgaddr0);
	/* host buffer high address */
	ग_लिखोl(upper_32_bits(host_buffer_dma), &pmuF->inbound_msgaddr1);
	/* set host buffer physical address */
	ग_लिखोl(ARCMSR_HBFMU_DOORBELL_SYNC1, &pmuF->iobound_करोorbell);
पूर्ण

अटल bool arcmsr_alloc_io_queue(काष्ठा AdapterControlBlock *acb)
अणु
	bool rtn = true;
	व्योम *dma_coherent;
	dma_addr_t dma_coherent_handle;
	काष्ठा pci_dev *pdev = acb->pdev;

	चयन (acb->adapter_type) अणु
	हाल ACB_ADAPTER_TYPE_B: अणु
		acb->ioqueue_size = roundup(माप(काष्ठा MessageUnit_B), 32);
		dma_coherent = dma_alloc_coherent(&pdev->dev, acb->ioqueue_size,
			&dma_coherent_handle, GFP_KERNEL);
		अगर (!dma_coherent) अणु
			pr_notice("arcmsr%d: DMA allocation failed\n", acb->host->host_no);
			वापस false;
		पूर्ण
		acb->dma_coherent_handle2 = dma_coherent_handle;
		acb->dma_coherent2 = dma_coherent;
		acb->pmuB = (काष्ठा MessageUnit_B *)dma_coherent;
		arcmsr_hbaB_assign_regAddr(acb);
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_D: अणु
		acb->ioqueue_size = roundup(माप(काष्ठा MessageUnit_D), 32);
		dma_coherent = dma_alloc_coherent(&pdev->dev, acb->ioqueue_size,
			&dma_coherent_handle, GFP_KERNEL);
		अगर (!dma_coherent) अणु
			pr_notice("arcmsr%d: DMA allocation failed\n", acb->host->host_no);
			वापस false;
		पूर्ण
		acb->dma_coherent_handle2 = dma_coherent_handle;
		acb->dma_coherent2 = dma_coherent;
		acb->pmuD = (काष्ठा MessageUnit_D *)dma_coherent;
		arcmsr_hbaD_assign_regAddr(acb);
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_E: अणु
		uपूर्णांक32_t completeQ_size;
		completeQ_size = माप(काष्ठा deliver_completeQ) * ARCMSR_MAX_HBE_DONEQUEUE + 128;
		acb->ioqueue_size = roundup(completeQ_size, 32);
		dma_coherent = dma_alloc_coherent(&pdev->dev, acb->ioqueue_size,
			&dma_coherent_handle, GFP_KERNEL);
		अगर (!dma_coherent)अणु
			pr_notice("arcmsr%d: DMA allocation failed\n", acb->host->host_no);
			वापस false;
		पूर्ण
		acb->dma_coherent_handle2 = dma_coherent_handle;
		acb->dma_coherent2 = dma_coherent;
		acb->pCompletionQ = dma_coherent;
		acb->completionQ_entry = acb->ioqueue_size / माप(काष्ठा deliver_completeQ);
		acb->करोneq_index = 0;
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_F: अणु
		uपूर्णांक32_t QueueDepth;
		uपूर्णांक32_t depthTbl[] = अणु256, 512, 1024, 128, 64, 32पूर्ण;

		arcmsr_रुको_firmware_पढ़ोy(acb);
		QueueDepth = depthTbl[पढ़ोl(&acb->pmuF->outbound_msgaddr1) & 7];
		acb->completeQ_size = माप(काष्ठा deliver_completeQ) * QueueDepth + 128;
		acb->ioqueue_size = roundup(acb->completeQ_size + MESG_RW_BUFFER_SIZE, 32);
		dma_coherent = dma_alloc_coherent(&pdev->dev, acb->ioqueue_size,
			&dma_coherent_handle, GFP_KERNEL);
		अगर (!dma_coherent) अणु
			pr_notice("arcmsr%d: DMA allocation failed\n", acb->host->host_no);
			वापस false;
		पूर्ण
		acb->dma_coherent_handle2 = dma_coherent_handle;
		acb->dma_coherent2 = dma_coherent;
		acb->pCompletionQ = dma_coherent;
		acb->completionQ_entry = acb->completeQ_size / माप(काष्ठा deliver_completeQ);
		acb->करोneq_index = 0;
		arcmsr_hbaF_assign_regAddr(acb);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस rtn;
पूर्ण

अटल पूर्णांक arcmsr_alloc_ccb_pool(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा pci_dev *pdev = acb->pdev;
	व्योम *dma_coherent;
	dma_addr_t dma_coherent_handle;
	काष्ठा CommandControlBlock *ccb_पंचांगp;
	पूर्णांक i = 0, j = 0;
	अचिन्हित दीर्घ cdb_phyaddr, next_ccb_phy;
	अचिन्हित दीर्घ roundup_ccbsize;
	अचिन्हित दीर्घ max_xfer_len;
	अचिन्हित दीर्घ max_sg_entrys;
	uपूर्णांक32_t  firm_config_version, curr_phy_upper32;

	क्रम (i = 0; i < ARCMSR_MAX_TARGETID; i++)
		क्रम (j = 0; j < ARCMSR_MAX_TARGETLUN; j++)
			acb->devstate[i][j] = ARECA_RAID_GONE;

	max_xfer_len = ARCMSR_MAX_XFER_LEN;
	max_sg_entrys = ARCMSR_DEFAULT_SG_ENTRIES;
	firm_config_version = acb->firm_cfg_version;
	अगर((firm_config_version & 0xFF) >= 3)अणु
		max_xfer_len = (ARCMSR_CDB_SG_PAGE_LENGTH << ((firm_config_version >> 8) & 0xFF)) * 1024;/* max 4M byte */
		max_sg_entrys = (max_xfer_len/4096);
	पूर्ण
	acb->host->max_sectors = max_xfer_len/512;
	acb->host->sg_tablesize = max_sg_entrys;
	roundup_ccbsize = roundup(माप(काष्ठा CommandControlBlock) + (max_sg_entrys - 1) * माप(काष्ठा SG64ENTRY), 32);
	acb->uncache_size = roundup_ccbsize * acb->maxFreeCCB;
	अगर (acb->adapter_type != ACB_ADAPTER_TYPE_F)
		acb->uncache_size += acb->ioqueue_size;
	dma_coherent = dma_alloc_coherent(&pdev->dev, acb->uncache_size, &dma_coherent_handle, GFP_KERNEL);
	अगर(!dma_coherent)अणु
		prपूर्णांकk(KERN_NOTICE "arcmsr%d: dma_alloc_coherent got error\n", acb->host->host_no);
		वापस -ENOMEM;
	पूर्ण
	acb->dma_coherent = dma_coherent;
	acb->dma_coherent_handle = dma_coherent_handle;
	स_रखो(dma_coherent, 0, acb->uncache_size);
	acb->ccbsize = roundup_ccbsize;
	ccb_पंचांगp = dma_coherent;
	curr_phy_upper32 = upper_32_bits(dma_coherent_handle);
	acb->vir2phy_offset = (अचिन्हित दीर्घ)dma_coherent - (अचिन्हित दीर्घ)dma_coherent_handle;
	क्रम(i = 0; i < acb->maxFreeCCB; i++)अणु
		cdb_phyaddr = (अचिन्हित दीर्घ)dma_coherent_handle + दुरत्व(काष्ठा CommandControlBlock, arcmsr_cdb);
		चयन (acb->adapter_type) अणु
		हाल ACB_ADAPTER_TYPE_A:
		हाल ACB_ADAPTER_TYPE_B:
			ccb_पंचांगp->cdb_phyaddr = cdb_phyaddr >> 5;
			अवरोध;
		हाल ACB_ADAPTER_TYPE_C:
		हाल ACB_ADAPTER_TYPE_D:
		हाल ACB_ADAPTER_TYPE_E:
		हाल ACB_ADAPTER_TYPE_F:
			ccb_पंचांगp->cdb_phyaddr = cdb_phyaddr;
			अवरोध;
		पूर्ण
		acb->pccb_pool[i] = ccb_पंचांगp;
		ccb_पंचांगp->acb = acb;
		ccb_पंचांगp->smid = (u32)i << 16;
		INIT_LIST_HEAD(&ccb_पंचांगp->list);
		next_ccb_phy = dma_coherent_handle + roundup_ccbsize;
		अगर (upper_32_bits(next_ccb_phy) != curr_phy_upper32) अणु
			acb->maxFreeCCB = i;
			acb->host->can_queue = i;
			अवरोध;
		पूर्ण
		अन्यथा
			list_add_tail(&ccb_पंचांगp->list, &acb->ccb_मुक्त_list);
		ccb_पंचांगp = (काष्ठा CommandControlBlock *)((अचिन्हित दीर्घ)ccb_पंचांगp + roundup_ccbsize);
		dma_coherent_handle = next_ccb_phy;
	पूर्ण
	अगर (acb->adapter_type != ACB_ADAPTER_TYPE_F) अणु
		acb->dma_coherent_handle2 = dma_coherent_handle;
		acb->dma_coherent2 = ccb_पंचांगp;
	पूर्ण
	चयन (acb->adapter_type) अणु
	हाल ACB_ADAPTER_TYPE_B:
		acb->pmuB = (काष्ठा MessageUnit_B *)acb->dma_coherent2;
		arcmsr_hbaB_assign_regAddr(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_D:
		acb->pmuD = (काष्ठा MessageUnit_D *)acb->dma_coherent2;
		arcmsr_hbaD_assign_regAddr(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_E:
		acb->pCompletionQ = acb->dma_coherent2;
		acb->completionQ_entry = acb->ioqueue_size / माप(काष्ठा deliver_completeQ);
		acb->करोneq_index = 0;
		अवरोध;
	पूर्ण	
	वापस 0;
पूर्ण

अटल व्योम arcmsr_message_isr_bh_fn(काष्ठा work_काष्ठा *work) 
अणु
	काष्ठा AdapterControlBlock *acb = container_of(work,
		काष्ठा AdapterControlBlock, arcmsr_करो_message_isr_bh);
	अक्षर *acb_dev_map = (अक्षर *)acb->device_map;
	uपूर्णांक32_t __iomem *signature = शून्य;
	अक्षर __iomem *devicemap = शून्य;
	पूर्णांक target, lun;
	काष्ठा scsi_device *psdev;
	अक्षर dअगरf, temp;

	चयन (acb->adapter_type) अणु
	हाल ACB_ADAPTER_TYPE_A: अणु
		काष्ठा MessageUnit_A __iomem *reg  = acb->pmuA;

		signature = (uपूर्णांक32_t __iomem *)(&reg->message_rwbuffer[0]);
		devicemap = (अक्षर __iomem *)(&reg->message_rwbuffer[21]);
		अवरोध;
	पूर्ण
	हाल ACB_ADAPTER_TYPE_B: अणु
		काष्ठा MessageUnit_B *reg  = acb->pmuB;

		signature = (uपूर्णांक32_t __iomem *)(&reg->message_rwbuffer[0]);
		devicemap = (अक्षर __iomem *)(&reg->message_rwbuffer[21]);
		अवरोध;
	पूर्ण
	हाल ACB_ADAPTER_TYPE_C: अणु
		काष्ठा MessageUnit_C __iomem *reg  = acb->pmuC;

		signature = (uपूर्णांक32_t __iomem *)(&reg->msgcode_rwbuffer[0]);
		devicemap = (अक्षर __iomem *)(&reg->msgcode_rwbuffer[21]);
		अवरोध;
	पूर्ण
	हाल ACB_ADAPTER_TYPE_D: अणु
		काष्ठा MessageUnit_D *reg  = acb->pmuD;

		signature = (uपूर्णांक32_t __iomem *)(&reg->msgcode_rwbuffer[0]);
		devicemap = (अक्षर __iomem *)(&reg->msgcode_rwbuffer[21]);
		अवरोध;
	पूर्ण
	हाल ACB_ADAPTER_TYPE_E: अणु
		काष्ठा MessageUnit_E __iomem *reg  = acb->pmuE;

		signature = (uपूर्णांक32_t __iomem *)(&reg->msgcode_rwbuffer[0]);
		devicemap = (अक्षर __iomem *)(&reg->msgcode_rwbuffer[21]);
		अवरोध;
		पूर्ण
	हाल ACB_ADAPTER_TYPE_F: अणु
		signature = (uपूर्णांक32_t __iomem *)(&acb->msgcode_rwbuffer[0]);
		devicemap = (अक्षर __iomem *)(&acb->msgcode_rwbuffer[21]);
		अवरोध;
		पूर्ण
	पूर्ण
	अगर (पढ़ोl(signature) != ARCMSR_SIGNATURE_GET_CONFIG)
		वापस;
	क्रम (target = 0; target < ARCMSR_MAX_TARGETID - 1;
		target++) अणु
		temp = पढ़ोb(devicemap);
		dअगरf = (*acb_dev_map) ^ temp;
		अगर (dअगरf != 0) अणु
			*acb_dev_map = temp;
			क्रम (lun = 0; lun < ARCMSR_MAX_TARGETLUN;
				lun++) अणु
				अगर ((dअगरf & 0x01) == 1 &&
					(temp & 0x01) == 1) अणु
					scsi_add_device(acb->host,
						0, target, lun);
				पूर्ण अन्यथा अगर ((dअगरf & 0x01) == 1
					&& (temp & 0x01) == 0) अणु
					psdev = scsi_device_lookup(acb->host,
						0, target, lun);
					अगर (psdev != शून्य) अणु
						scsi_हटाओ_device(psdev);
						scsi_device_put(psdev);
					पूर्ण
				पूर्ण
				temp >>= 1;
				dअगरf >>= 1;
			पूर्ण
		पूर्ण
		devicemap++;
		acb_dev_map++;
	पूर्ण
	acb->acb_flags &= ~ACB_F_MSG_GET_CONFIG;
पूर्ण

अटल पूर्णांक
arcmsr_request_irq(काष्ठा pci_dev *pdev, काष्ठा AdapterControlBlock *acb)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक nvec, i;

	अगर (msix_enable == 0)
		जाओ msi_पूर्णांक0;
	nvec = pci_alloc_irq_vectors(pdev, 1, ARCMST_NUM_MSIX_VECTORS,
			PCI_IRQ_MSIX);
	अगर (nvec > 0) अणु
		pr_info("arcmsr%d: msi-x enabled\n", acb->host->host_no);
		flags = 0;
	पूर्ण अन्यथा अणु
msi_पूर्णांक0:
		अगर (msi_enable == 1) अणु
			nvec = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_MSI);
			अगर (nvec == 1) अणु
				dev_info(&pdev->dev, "msi enabled\n");
				जाओ msi_पूर्णांक1;
			पूर्ण
		पूर्ण
		nvec = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_LEGACY);
		अगर (nvec < 1)
			वापस FAILED;
msi_पूर्णांक1:
		flags = IRQF_SHARED;
	पूर्ण

	acb->vector_count = nvec;
	क्रम (i = 0; i < nvec; i++) अणु
		अगर (request_irq(pci_irq_vector(pdev, i), arcmsr_करो_पूर्णांकerrupt,
				flags, "arcmsr", acb)) अणु
			pr_warn("arcmsr%d: request_irq =%d failed!\n",
				acb->host->host_no, pci_irq_vector(pdev, i));
			जाओ out_मुक्त_irq;
		पूर्ण
	पूर्ण

	वापस SUCCESS;
out_मुक्त_irq:
	जबतक (--i >= 0)
		मुक्त_irq(pci_irq_vector(pdev, i), acb);
	pci_मुक्त_irq_vectors(pdev);
	वापस FAILED;
पूर्ण

अटल व्योम arcmsr_init_get_devmap_समयr(काष्ठा AdapterControlBlock *pacb)
अणु
	INIT_WORK(&pacb->arcmsr_करो_message_isr_bh, arcmsr_message_isr_bh_fn);
	pacb->fw_flag = FW_NORMAL;
	समयr_setup(&pacb->eternal_समयr, arcmsr_request_device_map, 0);
	pacb->eternal_समयr.expires = jअगरfies + msecs_to_jअगरfies(6 * HZ);
	add_समयr(&pacb->eternal_समयr);
पूर्ण

अटल व्योम arcmsr_init_set_dateसमय_प्रकारimer(काष्ठा AdapterControlBlock *pacb)
अणु
	समयr_setup(&pacb->refresh_समयr, arcmsr_set_iop_dateसमय, 0);
	pacb->refresh_समयr.expires = jअगरfies + msecs_to_jअगरfies(60 * 1000);
	add_समयr(&pacb->refresh_समयr);
पूर्ण

अटल पूर्णांक arcmsr_set_dma_mask(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा pci_dev *pcidev = acb->pdev;

	अगर (IS_DMA64) अणु
		अगर (((acb->adapter_type == ACB_ADAPTER_TYPE_A) && !dma_mask_64) ||
		    dma_set_mask(&pcidev->dev, DMA_BIT_MASK(64)))
			जाओ	dma32;
		अगर (dma_set_coherent_mask(&pcidev->dev, DMA_BIT_MASK(64)) ||
		    dma_set_mask_and_coherent(&pcidev->dev, DMA_BIT_MASK(64))) अणु
			prपूर्णांकk("arcmsr: set DMA 64 mask failed\n");
			वापस -ENXIO;
		पूर्ण
	पूर्ण अन्यथा अणु
dma32:
		अगर (dma_set_mask(&pcidev->dev, DMA_BIT_MASK(32)) ||
		    dma_set_coherent_mask(&pcidev->dev, DMA_BIT_MASK(32)) ||
		    dma_set_mask_and_coherent(&pcidev->dev, DMA_BIT_MASK(32))) अणु
			prपूर्णांकk("arcmsr: set DMA 32-bit mask failed\n");
			वापस -ENXIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक arcmsr_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा Scsi_Host *host;
	काष्ठा AdapterControlBlock *acb;
	uपूर्णांक8_t bus,dev_fun;
	पूर्णांक error;
	error = pci_enable_device(pdev);
	अगर(error)अणु
		वापस -ENODEV;
	पूर्ण
	host = scsi_host_alloc(&arcmsr_scsi_host_ढाँचा, माप(काष्ठा AdapterControlBlock));
	अगर(!host)अणु
    		जाओ pci_disable_dev;
	पूर्ण
	init_रुकोqueue_head(&रुको_q);
	bus = pdev->bus->number;
	dev_fun = pdev->devfn;
	acb = (काष्ठा AdapterControlBlock *) host->hostdata;
	स_रखो(acb,0,माप(काष्ठा AdapterControlBlock));
	acb->pdev = pdev;
	acb->adapter_type = id->driver_data;
	अगर (arcmsr_set_dma_mask(acb))
		जाओ scsi_host_release;
	acb->host = host;
	host->max_lun = ARCMSR_MAX_TARGETLUN;
	host->max_id = ARCMSR_MAX_TARGETID;		/*16:8*/
	host->max_cmd_len = 16;	 			/*this is issue of 64bit LBA ,over 2T byte*/
	अगर ((host_can_queue < ARCMSR_MIN_OUTSTANDING_CMD) || (host_can_queue > ARCMSR_MAX_OUTSTANDING_CMD))
		host_can_queue = ARCMSR_DEFAULT_OUTSTANDING_CMD;
	host->can_queue = host_can_queue;	/* max simultaneous cmds */
	अगर ((cmd_per_lun < ARCMSR_MIN_CMD_PERLUN) || (cmd_per_lun > ARCMSR_MAX_CMD_PERLUN))
		cmd_per_lun = ARCMSR_DEFAULT_CMD_PERLUN;
	host->cmd_per_lun = cmd_per_lun;
	host->this_id = ARCMSR_SCSI_INITIATOR_ID;
	host->unique_id = (bus << 8) | dev_fun;
	pci_set_drvdata(pdev, host);
	pci_set_master(pdev);
	error = pci_request_regions(pdev, "arcmsr");
	अगर(error)अणु
		जाओ scsi_host_release;
	पूर्ण
	spin_lock_init(&acb->eh_lock);
	spin_lock_init(&acb->ccblist_lock);
	spin_lock_init(&acb->postq_lock);
	spin_lock_init(&acb->करोneq_lock);
	spin_lock_init(&acb->rqbuffer_lock);
	spin_lock_init(&acb->wqbuffer_lock);
	acb->acb_flags |= (ACB_F_MESSAGE_WQBUFFER_CLEARED |
			ACB_F_MESSAGE_RQBUFFER_CLEARED |
			ACB_F_MESSAGE_WQBUFFER_READED);
	acb->acb_flags &= ~ACB_F_SCSISTOPADAPTER;
	INIT_LIST_HEAD(&acb->ccb_मुक्त_list);
	error = arcmsr_remap_pciregion(acb);
	अगर(!error)अणु
		जाओ pci_release_regs;
	पूर्ण
	error = arcmsr_alloc_io_queue(acb);
	अगर (!error)
		जाओ unmap_pci_region;
	error = arcmsr_get_firmware_spec(acb);
	अगर(!error)अणु
		जाओ मुक्त_hbb_mu;
	पूर्ण
	अगर (acb->adapter_type != ACB_ADAPTER_TYPE_F)
		arcmsr_मुक्त_io_queue(acb);
	error = arcmsr_alloc_ccb_pool(acb);
	अगर(error)अणु
		जाओ unmap_pci_region;
	पूर्ण
	error = scsi_add_host(host, &pdev->dev);
	अगर(error)अणु
		जाओ मुक्त_ccb_pool;
	पूर्ण
	अगर (arcmsr_request_irq(pdev, acb) == FAILED)
		जाओ scsi_host_हटाओ;
	arcmsr_iop_init(acb);
	arcmsr_init_get_devmap_समयr(acb);
	अगर (set_date_समय)
		arcmsr_init_set_dateसमय_प्रकारimer(acb);
	अगर(arcmsr_alloc_sysfs_attr(acb))
		जाओ out_मुक्त_sysfs;
	scsi_scan_host(host);
	वापस 0;
out_मुक्त_sysfs:
	अगर (set_date_समय)
		del_समयr_sync(&acb->refresh_समयr);
	del_समयr_sync(&acb->eternal_समयr);
	flush_work(&acb->arcmsr_करो_message_isr_bh);
	arcmsr_stop_adapter_bgrb(acb);
	arcmsr_flush_adapter_cache(acb);
	arcmsr_मुक्त_irq(pdev, acb);
scsi_host_हटाओ:
	scsi_हटाओ_host(host);
मुक्त_ccb_pool:
	arcmsr_मुक्त_ccb_pool(acb);
	जाओ unmap_pci_region;
मुक्त_hbb_mu:
	arcmsr_मुक्त_io_queue(acb);
unmap_pci_region:
	arcmsr_unmap_pciregion(acb);
pci_release_regs:
	pci_release_regions(pdev);
scsi_host_release:
	scsi_host_put(host);
pci_disable_dev:
	pci_disable_device(pdev);
	वापस -ENODEV;
पूर्ण

अटल व्योम arcmsr_मुक्त_irq(काष्ठा pci_dev *pdev,
		काष्ठा AdapterControlBlock *acb)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < acb->vector_count; i++)
		मुक्त_irq(pci_irq_vector(pdev, i), acb);
	pci_मुक्त_irq_vectors(pdev);
पूर्ण

अटल पूर्णांक __maybe_unused arcmsr_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);
	काष्ठा AdapterControlBlock *acb =
		(काष्ठा AdapterControlBlock *)host->hostdata;

	arcmsr_disable_outbound_पूर्णांकs(acb);
	arcmsr_मुक्त_irq(pdev, acb);
	del_समयr_sync(&acb->eternal_समयr);
	अगर (set_date_समय)
		del_समयr_sync(&acb->refresh_समयr);
	flush_work(&acb->arcmsr_करो_message_isr_bh);
	arcmsr_stop_adapter_bgrb(acb);
	arcmsr_flush_adapter_cache(acb);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused arcmsr_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);
	काष्ठा AdapterControlBlock *acb =
		(काष्ठा AdapterControlBlock *)host->hostdata;

	अगर (arcmsr_set_dma_mask(acb))
		जाओ controller_unरेजिस्टर;
	अगर (arcmsr_request_irq(pdev, acb) == FAILED)
		जाओ controller_stop;
	चयन (acb->adapter_type) अणु
	हाल ACB_ADAPTER_TYPE_B: अणु
		काष्ठा MessageUnit_B *reg = acb->pmuB;
		uपूर्णांक32_t i;
		क्रम (i = 0; i < ARCMSR_MAX_HBB_POSTQUEUE; i++) अणु
			reg->post_qbuffer[i] = 0;
			reg->करोne_qbuffer[i] = 0;
		पूर्ण
		reg->postq_index = 0;
		reg->करोneq_index = 0;
		अवरोध;
		पूर्ण
	हाल ACB_ADAPTER_TYPE_E:
		ग_लिखोl(0, &acb->pmuE->host_पूर्णांक_status);
		ग_लिखोl(ARCMSR_HBEMU_DOORBELL_SYNC, &acb->pmuE->iobound_करोorbell);
		acb->in_करोorbell = 0;
		acb->out_करोorbell = 0;
		acb->करोneq_index = 0;
		अवरोध;
	हाल ACB_ADAPTER_TYPE_F:
		ग_लिखोl(0, &acb->pmuF->host_पूर्णांक_status);
		ग_लिखोl(ARCMSR_HBFMU_DOORBELL_SYNC, &acb->pmuF->iobound_करोorbell);
		acb->in_करोorbell = 0;
		acb->out_करोorbell = 0;
		acb->करोneq_index = 0;
		arcmsr_hbaF_assign_regAddr(acb);
		अवरोध;
	पूर्ण
	arcmsr_iop_init(acb);
	arcmsr_init_get_devmap_समयr(acb);
	अगर (set_date_समय)
		arcmsr_init_set_dateसमय_प्रकारimer(acb);
	वापस 0;
controller_stop:
	arcmsr_stop_adapter_bgrb(acb);
	arcmsr_flush_adapter_cache(acb);
controller_unरेजिस्टर:
	scsi_हटाओ_host(host);
	arcmsr_मुक्त_ccb_pool(acb);
	अगर (acb->adapter_type == ACB_ADAPTER_TYPE_F)
		arcmsr_मुक्त_io_queue(acb);
	arcmsr_unmap_pciregion(acb);
	scsi_host_put(host);
	वापस -ENODEV;
पूर्ण

अटल uपूर्णांक8_t arcmsr_hbaA_पात_allcmd(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;
	ग_लिखोl(ARCMSR_INBOUND_MESG0_ABORT_CMD, &reg->inbound_msgaddr0);
	अगर (!arcmsr_hbaA_रुको_msgपूर्णांक_पढ़ोy(acb)) अणु
		prपूर्णांकk(KERN_NOTICE
			"arcmsr%d: wait 'abort all outstanding command' timeout\n"
			, acb->host->host_no);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल uपूर्णांक8_t arcmsr_hbaB_पात_allcmd(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा MessageUnit_B *reg = acb->pmuB;

	ग_लिखोl(ARCMSR_MESSAGE_ABORT_CMD, reg->drv2iop_करोorbell);
	अगर (!arcmsr_hbaB_रुको_msgपूर्णांक_पढ़ोy(acb)) अणु
		prपूर्णांकk(KERN_NOTICE
			"arcmsr%d: wait 'abort all outstanding command' timeout\n"
			, acb->host->host_no);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण
अटल uपूर्णांक8_t arcmsr_hbaC_पात_allcmd(काष्ठा AdapterControlBlock *pACB)
अणु
	काष्ठा MessageUnit_C __iomem *reg = pACB->pmuC;
	ग_लिखोl(ARCMSR_INBOUND_MESG0_ABORT_CMD, &reg->inbound_msgaddr0);
	ग_लिखोl(ARCMSR_HBCMU_DRV2IOP_MESSAGE_CMD_DONE, &reg->inbound_करोorbell);
	अगर (!arcmsr_hbaC_रुको_msgपूर्णांक_पढ़ोy(pACB)) अणु
		prपूर्णांकk(KERN_NOTICE
			"arcmsr%d: wait 'abort all outstanding command' timeout\n"
			, pACB->host->host_no);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल uपूर्णांक8_t arcmsr_hbaD_पात_allcmd(काष्ठा AdapterControlBlock *pACB)
अणु
	काष्ठा MessageUnit_D *reg = pACB->pmuD;

	ग_लिखोl(ARCMSR_INBOUND_MESG0_ABORT_CMD, reg->inbound_msgaddr0);
	अगर (!arcmsr_hbaD_रुको_msgपूर्णांक_पढ़ोy(pACB)) अणु
		pr_notice("arcmsr%d: wait 'abort all outstanding "
			"command' timeout\n", pACB->host->host_no);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल uपूर्णांक8_t arcmsr_hbaE_पात_allcmd(काष्ठा AdapterControlBlock *pACB)
अणु
	काष्ठा MessageUnit_E __iomem *reg = pACB->pmuE;

	ग_लिखोl(ARCMSR_INBOUND_MESG0_ABORT_CMD, &reg->inbound_msgaddr0);
	pACB->out_करोorbell ^= ARCMSR_HBEMU_DRV2IOP_MESSAGE_CMD_DONE;
	ग_लिखोl(pACB->out_करोorbell, &reg->iobound_करोorbell);
	अगर (!arcmsr_hbaE_रुको_msgपूर्णांक_पढ़ोy(pACB)) अणु
		pr_notice("arcmsr%d: wait 'abort all outstanding "
			"command' timeout\n", pACB->host->host_no);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल uपूर्णांक8_t arcmsr_पात_allcmd(काष्ठा AdapterControlBlock *acb)
अणु
	uपूर्णांक8_t rtnval = 0;
	चयन (acb->adapter_type) अणु
	हाल ACB_ADAPTER_TYPE_A:
		rtnval = arcmsr_hbaA_पात_allcmd(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_B:
		rtnval = arcmsr_hbaB_पात_allcmd(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_C:
		rtnval = arcmsr_hbaC_पात_allcmd(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_D:
		rtnval = arcmsr_hbaD_पात_allcmd(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_E:
	हाल ACB_ADAPTER_TYPE_F:
		rtnval = arcmsr_hbaE_पात_allcmd(acb);
		अवरोध;
	पूर्ण
	वापस rtnval;
पूर्ण

अटल व्योम arcmsr_pci_unmap_dma(काष्ठा CommandControlBlock *ccb)
अणु
	काष्ठा scsi_cmnd *pcmd = ccb->pcmd;

	scsi_dma_unmap(pcmd);
पूर्ण

अटल व्योम arcmsr_ccb_complete(काष्ठा CommandControlBlock *ccb)
अणु
	काष्ठा AdapterControlBlock *acb = ccb->acb;
	काष्ठा scsi_cmnd *pcmd = ccb->pcmd;
	अचिन्हित दीर्घ flags;
	atomic_dec(&acb->ccboutstandingcount);
	arcmsr_pci_unmap_dma(ccb);
	ccb->startकरोne = ARCMSR_CCB_DONE;
	spin_lock_irqsave(&acb->ccblist_lock, flags);
	list_add_tail(&ccb->list, &acb->ccb_मुक्त_list);
	spin_unlock_irqrestore(&acb->ccblist_lock, flags);
	pcmd->scsi_करोne(pcmd);
पूर्ण

अटल व्योम arcmsr_report_sense_info(काष्ठा CommandControlBlock *ccb)
अणु

	काष्ठा scsi_cmnd *pcmd = ccb->pcmd;
	काष्ठा SENSE_DATA *sensebuffer = (काष्ठा SENSE_DATA *)pcmd->sense_buffer;
	pcmd->result = (DID_OK << 16) | (CHECK_CONDITION << 1);
	अगर (sensebuffer) अणु
		पूर्णांक sense_data_length =
			माप(काष्ठा SENSE_DATA) < SCSI_SENSE_BUFFERSIZE
			? माप(काष्ठा SENSE_DATA) : SCSI_SENSE_BUFFERSIZE;
		स_रखो(sensebuffer, 0, SCSI_SENSE_BUFFERSIZE);
		स_नकल(sensebuffer, ccb->arcmsr_cdb.SenseData, sense_data_length);
		sensebuffer->ErrorCode = SCSI_SENSE_CURRENT_ERRORS;
		sensebuffer->Valid = 1;
		pcmd->result |= (DRIVER_SENSE << 24);
	पूर्ण
पूर्ण

अटल u32 arcmsr_disable_outbound_पूर्णांकs(काष्ठा AdapterControlBlock *acb)
अणु
	u32 orig_mask = 0;
	चयन (acb->adapter_type) अणु	
	हाल ACB_ADAPTER_TYPE_A : अणु
		काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;
		orig_mask = पढ़ोl(&reg->outbound_पूर्णांकmask);
		ग_लिखोl(orig_mask|ARCMSR_MU_OUTBOUND_ALL_INTMASKENABLE, \
						&reg->outbound_पूर्णांकmask);
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_B : अणु
		काष्ठा MessageUnit_B *reg = acb->pmuB;
		orig_mask = पढ़ोl(reg->iop2drv_करोorbell_mask);
		ग_लिखोl(0, reg->iop2drv_करोorbell_mask);
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_C:अणु
		काष्ठा MessageUnit_C __iomem *reg = acb->pmuC;
		/* disable all outbound पूर्णांकerrupt */
		orig_mask = पढ़ोl(&reg->host_पूर्णांक_mask); /* disable outbound message0 पूर्णांक */
		ग_लिखोl(orig_mask|ARCMSR_HBCMU_ALL_INTMASKENABLE, &reg->host_पूर्णांक_mask);
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_D: अणु
		काष्ठा MessageUnit_D *reg = acb->pmuD;
		/* disable all outbound पूर्णांकerrupt */
		ग_लिखोl(ARCMSR_ARC1214_ALL_INT_DISABLE, reg->pcief0_पूर्णांक_enable);
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_E:
	हाल ACB_ADAPTER_TYPE_F: अणु
		काष्ठा MessageUnit_E __iomem *reg = acb->pmuE;
		orig_mask = पढ़ोl(&reg->host_पूर्णांक_mask);
		ग_लिखोl(orig_mask | ARCMSR_HBEMU_OUTBOUND_DOORBELL_ISR | ARCMSR_HBEMU_OUTBOUND_POSTQUEUE_ISR, &reg->host_पूर्णांक_mask);
		पढ़ोl(&reg->host_पूर्णांक_mask); /* Dummy पढ़ोl to क्रमce pci flush */
		पूर्ण
		अवरोध;
	पूर्ण
	वापस orig_mask;
पूर्ण

अटल व्योम arcmsr_report_ccb_state(काष्ठा AdapterControlBlock *acb, 
			काष्ठा CommandControlBlock *ccb, bool error)
अणु
	uपूर्णांक8_t id, lun;
	id = ccb->pcmd->device->id;
	lun = ccb->pcmd->device->lun;
	अगर (!error) अणु
		अगर (acb->devstate[id][lun] == ARECA_RAID_GONE)
			acb->devstate[id][lun] = ARECA_RAID_GOOD;
		ccb->pcmd->result = DID_OK << 16;
		arcmsr_ccb_complete(ccb);
	पूर्णअन्यथाअणु
		चयन (ccb->arcmsr_cdb.DeviceStatus) अणु
		हाल ARCMSR_DEV_SELECT_TIMEOUT: अणु
			acb->devstate[id][lun] = ARECA_RAID_GONE;
			ccb->pcmd->result = DID_NO_CONNECT << 16;
			arcmsr_ccb_complete(ccb);
			पूर्ण
			अवरोध;

		हाल ARCMSR_DEV_ABORTED:

		हाल ARCMSR_DEV_INIT_FAIL: अणु
			acb->devstate[id][lun] = ARECA_RAID_GONE;
			ccb->pcmd->result = DID_BAD_TARGET << 16;
			arcmsr_ccb_complete(ccb);
			पूर्ण
			अवरोध;

		हाल ARCMSR_DEV_CHECK_CONDITION: अणु
			acb->devstate[id][lun] = ARECA_RAID_GOOD;
			arcmsr_report_sense_info(ccb);
			arcmsr_ccb_complete(ccb);
			पूर्ण
			अवरोध;

		शेष:
			prपूर्णांकk(KERN_NOTICE
				"arcmsr%d: scsi id = %d lun = %d isr get command error करोne, \
				but got unknown DeviceStatus = 0x%x \न"
				, acb->host->host_no
				, id
				, lun
				, ccb->arcmsr_cdb.DeviceStatus);
				acb->devstate[id][lun] = ARECA_RAID_GONE;
				ccb->pcmd->result = DID_NO_CONNECT << 16;
				arcmsr_ccb_complete(ccb);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम arcmsr_drain_करोnequeue(काष्ठा AdapterControlBlock *acb, काष्ठा CommandControlBlock *pCCB, bool error)
अणु
	अगर ((pCCB->acb != acb) || (pCCB->startकरोne != ARCMSR_CCB_START)) अणु
		अगर (pCCB->startकरोne == ARCMSR_CCB_ABORTED) अणु
			काष्ठा scsi_cmnd *पातcmd = pCCB->pcmd;
			अगर (पातcmd) अणु
				पातcmd->result |= DID_ABORT << 16;
				arcmsr_ccb_complete(pCCB);
				prपूर्णांकk(KERN_NOTICE "arcmsr%d: pCCB ='0x%p' isr got aborted command \n",
				acb->host->host_no, pCCB);
			पूर्ण
			वापस;
		पूर्ण
		prपूर्णांकk(KERN_NOTICE "arcmsr%d: isr get an illegal ccb command \
				करोne acb = '0x%p'"
				"ccb = '0x%p' ccbacb = '0x%p' startdone = 0x%x"
				" ccboutstandingcount = %d \n"
				, acb->host->host_no
				, acb
				, pCCB
				, pCCB->acb
				, pCCB->startकरोne
				, atomic_पढ़ो(&acb->ccboutstandingcount));
		वापस;
	पूर्ण
	arcmsr_report_ccb_state(acb, pCCB, error);
पूर्ण

अटल व्योम arcmsr_करोne4पात_postqueue(काष्ठा AdapterControlBlock *acb)
अणु
	पूर्णांक i = 0;
	uपूर्णांक32_t flag_ccb;
	काष्ठा ARCMSR_CDB *pARCMSR_CDB;
	bool error;
	काष्ठा CommandControlBlock *pCCB;
	अचिन्हित दीर्घ ccb_cdb_phy;

	चयन (acb->adapter_type) अणु

	हाल ACB_ADAPTER_TYPE_A: अणु
		काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;
		uपूर्णांक32_t outbound_पूर्णांकstatus;
		outbound_पूर्णांकstatus = पढ़ोl(&reg->outbound_पूर्णांकstatus) &
					acb->outbound_पूर्णांक_enable;
		/*clear and पात all outbound posted Q*/
		ग_लिखोl(outbound_पूर्णांकstatus, &reg->outbound_पूर्णांकstatus);/*clear पूर्णांकerrupt*/
		जबतक(((flag_ccb = पढ़ोl(&reg->outbound_queueport)) != 0xFFFFFFFF)
				&& (i++ < acb->maxOutstanding)) अणु
			ccb_cdb_phy = (flag_ccb << 5) & 0xffffffff;
			अगर (acb->cdb_phyadd_hipart)
				ccb_cdb_phy = ccb_cdb_phy | acb->cdb_phyadd_hipart;
			pARCMSR_CDB = (काष्ठा ARCMSR_CDB *)(acb->vir2phy_offset + ccb_cdb_phy);
			pCCB = container_of(pARCMSR_CDB, काष्ठा CommandControlBlock, arcmsr_cdb);
			error = (flag_ccb & ARCMSR_CCBREPLY_FLAG_ERROR_MODE0) ? true : false;
			arcmsr_drain_करोnequeue(acb, pCCB, error);
		पूर्ण
		पूर्ण
		अवरोध;

	हाल ACB_ADAPTER_TYPE_B: अणु
		काष्ठा MessageUnit_B *reg = acb->pmuB;
		/*clear all outbound posted Q*/
		ग_लिखोl(ARCMSR_DOORBELL_INT_CLEAR_PATTERN, reg->iop2drv_करोorbell); /* clear करोorbell पूर्णांकerrupt */
		क्रम (i = 0; i < ARCMSR_MAX_HBB_POSTQUEUE; i++) अणु
			flag_ccb = reg->करोne_qbuffer[i];
			अगर (flag_ccb != 0) अणु
				reg->करोne_qbuffer[i] = 0;
				ccb_cdb_phy = (flag_ccb << 5) & 0xffffffff;
				अगर (acb->cdb_phyadd_hipart)
					ccb_cdb_phy = ccb_cdb_phy | acb->cdb_phyadd_hipart;
				pARCMSR_CDB = (काष्ठा ARCMSR_CDB *)(acb->vir2phy_offset + ccb_cdb_phy);
				pCCB = container_of(pARCMSR_CDB, काष्ठा CommandControlBlock, arcmsr_cdb);
				error = (flag_ccb & ARCMSR_CCBREPLY_FLAG_ERROR_MODE0) ? true : false;
				arcmsr_drain_करोnequeue(acb, pCCB, error);
			पूर्ण
			reg->post_qbuffer[i] = 0;
		पूर्ण
		reg->करोneq_index = 0;
		reg->postq_index = 0;
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_C: अणु
		काष्ठा MessageUnit_C __iomem *reg = acb->pmuC;
		जबतक ((पढ़ोl(&reg->host_पूर्णांक_status) & ARCMSR_HBCMU_OUTBOUND_POSTQUEUE_ISR) && (i++ < acb->maxOutstanding)) अणु
			/*need to करो*/
			flag_ccb = पढ़ोl(&reg->outbound_queueport_low);
			ccb_cdb_phy = (flag_ccb & 0xFFFFFFF0);
			अगर (acb->cdb_phyadd_hipart)
				ccb_cdb_phy = ccb_cdb_phy | acb->cdb_phyadd_hipart;
			pARCMSR_CDB = (काष्ठा  ARCMSR_CDB *)(acb->vir2phy_offset + ccb_cdb_phy);
			pCCB = container_of(pARCMSR_CDB, काष्ठा CommandControlBlock, arcmsr_cdb);
			error = (flag_ccb & ARCMSR_CCBREPLY_FLAG_ERROR_MODE1) ? true : false;
			arcmsr_drain_करोnequeue(acb, pCCB, error);
		पूर्ण
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_D: अणु
		काष्ठा MessageUnit_D  *pmu = acb->pmuD;
		uपूर्णांक32_t outbound_ग_लिखो_poपूर्णांकer;
		uपूर्णांक32_t करोneq_index, index_stripped, addressLow, residual, toggle;
		अचिन्हित दीर्घ flags;

		residual = atomic_पढ़ो(&acb->ccboutstandingcount);
		क्रम (i = 0; i < residual; i++) अणु
			spin_lock_irqsave(&acb->करोneq_lock, flags);
			outbound_ग_लिखो_poपूर्णांकer =
				pmu->करोne_qbuffer[0].addressLow + 1;
			करोneq_index = pmu->करोneq_index;
			अगर ((करोneq_index & 0xFFF) !=
				(outbound_ग_लिखो_poपूर्णांकer & 0xFFF)) अणु
				toggle = करोneq_index & 0x4000;
				index_stripped = (करोneq_index & 0xFFF) + 1;
				index_stripped %= ARCMSR_MAX_ARC1214_DONEQUEUE;
				pmu->करोneq_index = index_stripped ? (index_stripped | toggle) :
					((toggle ^ 0x4000) + 1);
				करोneq_index = pmu->करोneq_index;
				spin_unlock_irqrestore(&acb->करोneq_lock, flags);
				addressLow = pmu->करोne_qbuffer[करोneq_index &
					0xFFF].addressLow;
				ccb_cdb_phy = (addressLow & 0xFFFFFFF0);
				अगर (acb->cdb_phyadd_hipart)
					ccb_cdb_phy = ccb_cdb_phy | acb->cdb_phyadd_hipart;
				pARCMSR_CDB = (काष्ठा  ARCMSR_CDB *)
					(acb->vir2phy_offset + ccb_cdb_phy);
				pCCB = container_of(pARCMSR_CDB,
					काष्ठा CommandControlBlock, arcmsr_cdb);
				error = (addressLow &
					ARCMSR_CCBREPLY_FLAG_ERROR_MODE1) ?
					true : false;
				arcmsr_drain_करोnequeue(acb, pCCB, error);
				ग_लिखोl(करोneq_index,
					pmu->outboundlist_पढ़ो_poपूर्णांकer);
			पूर्ण अन्यथा अणु
				spin_unlock_irqrestore(&acb->करोneq_lock, flags);
				mdelay(10);
			पूर्ण
		पूर्ण
		pmu->postq_index = 0;
		pmu->करोneq_index = 0x40FF;
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_E:
		arcmsr_hbaE_postqueue_isr(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_F:
		arcmsr_hbaF_postqueue_isr(acb);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम arcmsr_हटाओ_scsi_devices(काष्ठा AdapterControlBlock *acb)
अणु
	अक्षर *acb_dev_map = (अक्षर *)acb->device_map;
	पूर्णांक target, lun, i;
	काष्ठा scsi_device *psdev;
	काष्ठा CommandControlBlock *ccb;
	अक्षर temp;

	क्रम (i = 0; i < acb->maxFreeCCB; i++) अणु
		ccb = acb->pccb_pool[i];
		अगर (ccb->startकरोne == ARCMSR_CCB_START) अणु
			ccb->pcmd->result = DID_NO_CONNECT << 16;
			arcmsr_pci_unmap_dma(ccb);
			ccb->pcmd->scsi_करोne(ccb->pcmd);
		पूर्ण
	पूर्ण
	क्रम (target = 0; target < ARCMSR_MAX_TARGETID; target++) अणु
		temp = *acb_dev_map;
		अगर (temp) अणु
			क्रम (lun = 0; lun < ARCMSR_MAX_TARGETLUN; lun++) अणु
				अगर (temp & 1) अणु
					psdev = scsi_device_lookup(acb->host,
						0, target, lun);
					अगर (psdev != शून्य) अणु
						scsi_हटाओ_device(psdev);
						scsi_device_put(psdev);
					पूर्ण
				पूर्ण
				temp >>= 1;
			पूर्ण
			*acb_dev_map = 0;
		पूर्ण
		acb_dev_map++;
	पूर्ण
पूर्ण

अटल व्योम arcmsr_मुक्त_pcidev(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा pci_dev *pdev;
	काष्ठा Scsi_Host *host;

	host = acb->host;
	arcmsr_मुक्त_sysfs_attr(acb);
	scsi_हटाओ_host(host);
	flush_work(&acb->arcmsr_करो_message_isr_bh);
	del_समयr_sync(&acb->eternal_समयr);
	अगर (set_date_समय)
		del_समयr_sync(&acb->refresh_समयr);
	pdev = acb->pdev;
	arcmsr_मुक्त_irq(pdev, acb);
	arcmsr_मुक्त_ccb_pool(acb);
	अगर (acb->adapter_type == ACB_ADAPTER_TYPE_F)
		arcmsr_मुक्त_io_queue(acb);
	arcmsr_unmap_pciregion(acb);
	pci_release_regions(pdev);
	scsi_host_put(host);
	pci_disable_device(pdev);
पूर्ण

अटल व्योम arcmsr_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);
	काष्ठा AdapterControlBlock *acb =
		(काष्ठा AdapterControlBlock *) host->hostdata;
	पूर्णांक poll_count = 0;
	uपूर्णांक16_t dev_id;

	pci_पढ़ो_config_word(pdev, PCI_DEVICE_ID, &dev_id);
	अगर (dev_id == 0xffff) अणु
		acb->acb_flags &= ~ACB_F_IOP_INITED;
		acb->acb_flags |= ACB_F_ADAPTER_REMOVED;
		arcmsr_हटाओ_scsi_devices(acb);
		arcmsr_मुक्त_pcidev(acb);
		वापस;
	पूर्ण
	arcmsr_मुक्त_sysfs_attr(acb);
	scsi_हटाओ_host(host);
	flush_work(&acb->arcmsr_करो_message_isr_bh);
	del_समयr_sync(&acb->eternal_समयr);
	अगर (set_date_समय)
		del_समयr_sync(&acb->refresh_समयr);
	arcmsr_disable_outbound_पूर्णांकs(acb);
	arcmsr_stop_adapter_bgrb(acb);
	arcmsr_flush_adapter_cache(acb);	
	acb->acb_flags |= ACB_F_SCSISTOPADAPTER;
	acb->acb_flags &= ~ACB_F_IOP_INITED;

	क्रम (poll_count = 0; poll_count < acb->maxOutstanding; poll_count++)अणु
		अगर (!atomic_पढ़ो(&acb->ccboutstandingcount))
			अवरोध;
		arcmsr_पूर्णांकerrupt(acb);/* FIXME: need spinlock */
		msleep(25);
	पूर्ण

	अगर (atomic_पढ़ो(&acb->ccboutstandingcount)) अणु
		पूर्णांक i;

		arcmsr_पात_allcmd(acb);
		arcmsr_करोne4पात_postqueue(acb);
		क्रम (i = 0; i < acb->maxFreeCCB; i++) अणु
			काष्ठा CommandControlBlock *ccb = acb->pccb_pool[i];
			अगर (ccb->startकरोne == ARCMSR_CCB_START) अणु
				ccb->startकरोne = ARCMSR_CCB_ABORTED;
				ccb->pcmd->result = DID_ABORT << 16;
				arcmsr_ccb_complete(ccb);
			पूर्ण
		पूर्ण
	पूर्ण
	arcmsr_मुक्त_irq(pdev, acb);
	arcmsr_मुक्त_ccb_pool(acb);
	अगर (acb->adapter_type == ACB_ADAPTER_TYPE_F)
		arcmsr_मुक्त_io_queue(acb);
	arcmsr_unmap_pciregion(acb);
	pci_release_regions(pdev);
	scsi_host_put(host);
	pci_disable_device(pdev);
पूर्ण

अटल व्योम arcmsr_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);
	काष्ठा AdapterControlBlock *acb =
		(काष्ठा AdapterControlBlock *)host->hostdata;
	अगर (acb->acb_flags & ACB_F_ADAPTER_REMOVED)
		वापस;
	del_समयr_sync(&acb->eternal_समयr);
	अगर (set_date_समय)
		del_समयr_sync(&acb->refresh_समयr);
	arcmsr_disable_outbound_पूर्णांकs(acb);
	arcmsr_मुक्त_irq(pdev, acb);
	flush_work(&acb->arcmsr_करो_message_isr_bh);
	arcmsr_stop_adapter_bgrb(acb);
	arcmsr_flush_adapter_cache(acb);
पूर्ण

अटल पूर्णांक arcmsr_module_init(व्योम)
अणु
	पूर्णांक error = 0;
	error = pci_रेजिस्टर_driver(&arcmsr_pci_driver);
	वापस error;
पूर्ण

अटल व्योम arcmsr_module_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&arcmsr_pci_driver);
पूर्ण
module_init(arcmsr_module_init);
module_निकास(arcmsr_module_निकास);

अटल व्योम arcmsr_enable_outbound_पूर्णांकs(काष्ठा AdapterControlBlock *acb,
						u32 पूर्णांकmask_org)
अणु
	u32 mask;
	चयन (acb->adapter_type) अणु

	हाल ACB_ADAPTER_TYPE_A: अणु
		काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;
		mask = पूर्णांकmask_org & ~(ARCMSR_MU_OUTBOUND_POSTQUEUE_INTMASKENABLE |
			     ARCMSR_MU_OUTBOUND_DOORBELL_INTMASKENABLE|
			     ARCMSR_MU_OUTBOUND_MESSAGE0_INTMASKENABLE);
		ग_लिखोl(mask, &reg->outbound_पूर्णांकmask);
		acb->outbound_पूर्णांक_enable = ~(पूर्णांकmask_org & mask) & 0x000000ff;
		पूर्ण
		अवरोध;

	हाल ACB_ADAPTER_TYPE_B: अणु
		काष्ठा MessageUnit_B *reg = acb->pmuB;
		mask = पूर्णांकmask_org | (ARCMSR_IOP2DRV_DATA_WRITE_OK |
			ARCMSR_IOP2DRV_DATA_READ_OK |
			ARCMSR_IOP2DRV_CDB_DONE |
			ARCMSR_IOP2DRV_MESSAGE_CMD_DONE);
		ग_लिखोl(mask, reg->iop2drv_करोorbell_mask);
		acb->outbound_पूर्णांक_enable = (पूर्णांकmask_org | mask) & 0x0000000f;
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_C: अणु
		काष्ठा MessageUnit_C __iomem *reg = acb->pmuC;
		mask = ~(ARCMSR_HBCMU_UTILITY_A_ISR_MASK | ARCMSR_HBCMU_OUTBOUND_DOORBELL_ISR_MASK|ARCMSR_HBCMU_OUTBOUND_POSTQUEUE_ISR_MASK);
		ग_लिखोl(पूर्णांकmask_org & mask, &reg->host_पूर्णांक_mask);
		acb->outbound_पूर्णांक_enable = ~(पूर्णांकmask_org & mask) & 0x0000000f;
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_D: अणु
		काष्ठा MessageUnit_D *reg = acb->pmuD;

		mask = ARCMSR_ARC1214_ALL_INT_ENABLE;
		ग_लिखोl(पूर्णांकmask_org | mask, reg->pcief0_पूर्णांक_enable);
		अवरोध;
		पूर्ण
	हाल ACB_ADAPTER_TYPE_E:
	हाल ACB_ADAPTER_TYPE_F: अणु
		काष्ठा MessageUnit_E __iomem *reg = acb->pmuE;

		mask = ~(ARCMSR_HBEMU_OUTBOUND_DOORBELL_ISR | ARCMSR_HBEMU_OUTBOUND_POSTQUEUE_ISR);
		ग_लिखोl(पूर्णांकmask_org & mask, &reg->host_पूर्णांक_mask);
		अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक arcmsr_build_ccb(काष्ठा AdapterControlBlock *acb,
	काष्ठा CommandControlBlock *ccb, काष्ठा scsi_cmnd *pcmd)
अणु
	काष्ठा ARCMSR_CDB *arcmsr_cdb = (काष्ठा ARCMSR_CDB *)&ccb->arcmsr_cdb;
	पूर्णांक8_t *psge = (पूर्णांक8_t *)&arcmsr_cdb->u;
	__le32 address_lo, address_hi;
	पूर्णांक arccdbsize = 0x30;
	__le32 length = 0;
	पूर्णांक i;
	काष्ठा scatterlist *sg;
	पूर्णांक nseg;
	ccb->pcmd = pcmd;
	स_रखो(arcmsr_cdb, 0, माप(काष्ठा ARCMSR_CDB));
	arcmsr_cdb->TargetID = pcmd->device->id;
	arcmsr_cdb->LUN = pcmd->device->lun;
	arcmsr_cdb->Function = 1;
	arcmsr_cdb->msgContext = 0;
	स_नकल(arcmsr_cdb->Cdb, pcmd->cmnd, pcmd->cmd_len);

	nseg = scsi_dma_map(pcmd);
	अगर (unlikely(nseg > acb->host->sg_tablesize || nseg < 0))
		वापस FAILED;
	scsi_क्रम_each_sg(pcmd, sg, nseg, i) अणु
		/* Get the physical address of the current data poपूर्णांकer */
		length = cpu_to_le32(sg_dma_len(sg));
		address_lo = cpu_to_le32(dma_addr_lo32(sg_dma_address(sg)));
		address_hi = cpu_to_le32(dma_addr_hi32(sg_dma_address(sg)));
		अगर (address_hi == 0) अणु
			काष्ठा SG32ENTRY *pdma_sg = (काष्ठा SG32ENTRY *)psge;

			pdma_sg->address = address_lo;
			pdma_sg->length = length;
			psge += माप (काष्ठा SG32ENTRY);
			arccdbsize += माप (काष्ठा SG32ENTRY);
		पूर्ण अन्यथा अणु
			काष्ठा SG64ENTRY *pdma_sg = (काष्ठा SG64ENTRY *)psge;

			pdma_sg->addresshigh = address_hi;
			pdma_sg->address = address_lo;
			pdma_sg->length = length|cpu_to_le32(IS_SG64_ADDR);
			psge += माप (काष्ठा SG64ENTRY);
			arccdbsize += माप (काष्ठा SG64ENTRY);
		पूर्ण
	पूर्ण
	arcmsr_cdb->sgcount = (uपूर्णांक8_t)nseg;
	arcmsr_cdb->DataLength = scsi_bufflen(pcmd);
	arcmsr_cdb->msgPages = arccdbsize/0x100 + (arccdbsize % 0x100 ? 1 : 0);
	अगर ( arccdbsize > 256)
		arcmsr_cdb->Flags |= ARCMSR_CDB_FLAG_SGL_BSIZE;
	अगर (pcmd->sc_data_direction == DMA_TO_DEVICE)
		arcmsr_cdb->Flags |= ARCMSR_CDB_FLAG_WRITE;
	ccb->arc_cdb_size = arccdbsize;
	वापस SUCCESS;
पूर्ण

अटल व्योम arcmsr_post_ccb(काष्ठा AdapterControlBlock *acb, काष्ठा CommandControlBlock *ccb)
अणु
	uपूर्णांक32_t cdb_phyaddr = ccb->cdb_phyaddr;
	काष्ठा ARCMSR_CDB *arcmsr_cdb = (काष्ठा ARCMSR_CDB *)&ccb->arcmsr_cdb;
	atomic_inc(&acb->ccboutstandingcount);
	ccb->startकरोne = ARCMSR_CCB_START;
	चयन (acb->adapter_type) अणु
	हाल ACB_ADAPTER_TYPE_A: अणु
		काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;

		अगर (arcmsr_cdb->Flags & ARCMSR_CDB_FLAG_SGL_BSIZE)
			ग_लिखोl(cdb_phyaddr | ARCMSR_CCBPOST_FLAG_SGL_BSIZE,
			&reg->inbound_queueport);
		अन्यथा
			ग_लिखोl(cdb_phyaddr, &reg->inbound_queueport);
		अवरोध;
	पूर्ण

	हाल ACB_ADAPTER_TYPE_B: अणु
		काष्ठा MessageUnit_B *reg = acb->pmuB;
		uपूर्णांक32_t ending_index, index = reg->postq_index;

		ending_index = ((index + 1) % ARCMSR_MAX_HBB_POSTQUEUE);
		reg->post_qbuffer[ending_index] = 0;
		अगर (arcmsr_cdb->Flags & ARCMSR_CDB_FLAG_SGL_BSIZE) अणु
			reg->post_qbuffer[index] =
				cdb_phyaddr | ARCMSR_CCBPOST_FLAG_SGL_BSIZE;
		पूर्ण अन्यथा अणु
			reg->post_qbuffer[index] = cdb_phyaddr;
		पूर्ण
		index++;
		index %= ARCMSR_MAX_HBB_POSTQUEUE;/*अगर last index number set it to 0 */
		reg->postq_index = index;
		ग_लिखोl(ARCMSR_DRV2IOP_CDB_POSTED, reg->drv2iop_करोorbell);
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_C: अणु
		काष्ठा MessageUnit_C __iomem *phbcmu = acb->pmuC;
		uपूर्णांक32_t ccb_post_stamp, arc_cdb_size;

		arc_cdb_size = (ccb->arc_cdb_size > 0x300) ? 0x300 : ccb->arc_cdb_size;
		ccb_post_stamp = (cdb_phyaddr | ((arc_cdb_size - 1) >> 6) | 1);
		ग_लिखोl(upper_32_bits(ccb->cdb_phyaddr), &phbcmu->inbound_queueport_high);
		ग_लिखोl(ccb_post_stamp, &phbcmu->inbound_queueport_low);
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_D: अणु
		काष्ठा MessageUnit_D  *pmu = acb->pmuD;
		u16 index_stripped;
		u16 postq_index, toggle;
		अचिन्हित दीर्घ flags;
		काष्ठा InBound_SRB *pinbound_srb;

		spin_lock_irqsave(&acb->postq_lock, flags);
		postq_index = pmu->postq_index;
		pinbound_srb = (काष्ठा InBound_SRB *)&(pmu->post_qbuffer[postq_index & 0xFF]);
		pinbound_srb->addressHigh = upper_32_bits(ccb->cdb_phyaddr);
		pinbound_srb->addressLow = cdb_phyaddr;
		pinbound_srb->length = ccb->arc_cdb_size >> 2;
		arcmsr_cdb->msgContext = dma_addr_lo32(cdb_phyaddr);
		toggle = postq_index & 0x4000;
		index_stripped = postq_index + 1;
		index_stripped &= (ARCMSR_MAX_ARC1214_POSTQUEUE - 1);
		pmu->postq_index = index_stripped ? (index_stripped | toggle) :
			(toggle ^ 0x4000);
		ग_लिखोl(postq_index, pmu->inboundlist_ग_लिखो_poपूर्णांकer);
		spin_unlock_irqrestore(&acb->postq_lock, flags);
		अवरोध;
		पूर्ण
	हाल ACB_ADAPTER_TYPE_E: अणु
		काष्ठा MessageUnit_E __iomem *pmu = acb->pmuE;
		u32 ccb_post_stamp, arc_cdb_size;

		arc_cdb_size = (ccb->arc_cdb_size > 0x300) ? 0x300 : ccb->arc_cdb_size;
		ccb_post_stamp = (ccb->smid | ((arc_cdb_size - 1) >> 6));
		ग_लिखोl(0, &pmu->inbound_queueport_high);
		ग_लिखोl(ccb_post_stamp, &pmu->inbound_queueport_low);
		अवरोध;
		पूर्ण
	हाल ACB_ADAPTER_TYPE_F: अणु
		काष्ठा MessageUnit_F __iomem *pmu = acb->pmuF;
		u32 ccb_post_stamp, arc_cdb_size;

		अगर (ccb->arc_cdb_size <= 0x300)
			arc_cdb_size = (ccb->arc_cdb_size - 1) >> 6 | 1;
		अन्यथा
			arc_cdb_size = (((ccb->arc_cdb_size + 0xff) >> 8) + 2) << 1 | 1;
		ccb_post_stamp = (ccb->smid | arc_cdb_size);
		ग_लिखोl(0, &pmu->inbound_queueport_high);
		ग_लिखोl(ccb_post_stamp, &pmu->inbound_queueport_low);
		अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम arcmsr_hbaA_stop_bgrb(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;
	acb->acb_flags &= ~ACB_F_MSG_START_BGRB;
	ग_लिखोl(ARCMSR_INBOUND_MESG0_STOP_BGRB, &reg->inbound_msgaddr0);
	अगर (!arcmsr_hbaA_रुको_msgपूर्णांक_पढ़ोy(acb)) अणु
		prपूर्णांकk(KERN_NOTICE
			"arcmsr%d: wait 'stop adapter background rebuild' timeout\n"
			, acb->host->host_no);
	पूर्ण
पूर्ण

अटल व्योम arcmsr_hbaB_stop_bgrb(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा MessageUnit_B *reg = acb->pmuB;
	acb->acb_flags &= ~ACB_F_MSG_START_BGRB;
	ग_लिखोl(ARCMSR_MESSAGE_STOP_BGRB, reg->drv2iop_करोorbell);

	अगर (!arcmsr_hbaB_रुको_msgपूर्णांक_पढ़ोy(acb)) अणु
		prपूर्णांकk(KERN_NOTICE
			"arcmsr%d: wait 'stop adapter background rebuild' timeout\n"
			, acb->host->host_no);
	पूर्ण
पूर्ण

अटल व्योम arcmsr_hbaC_stop_bgrb(काष्ठा AdapterControlBlock *pACB)
अणु
	काष्ठा MessageUnit_C __iomem *reg = pACB->pmuC;
	pACB->acb_flags &= ~ACB_F_MSG_START_BGRB;
	ग_लिखोl(ARCMSR_INBOUND_MESG0_STOP_BGRB, &reg->inbound_msgaddr0);
	ग_लिखोl(ARCMSR_HBCMU_DRV2IOP_MESSAGE_CMD_DONE, &reg->inbound_करोorbell);
	अगर (!arcmsr_hbaC_रुको_msgपूर्णांक_पढ़ोy(pACB)) अणु
		prपूर्णांकk(KERN_NOTICE
			"arcmsr%d: wait 'stop adapter background rebuild' timeout\n"
			, pACB->host->host_no);
	पूर्ण
	वापस;
पूर्ण

अटल व्योम arcmsr_hbaD_stop_bgrb(काष्ठा AdapterControlBlock *pACB)
अणु
	काष्ठा MessageUnit_D *reg = pACB->pmuD;

	pACB->acb_flags &= ~ACB_F_MSG_START_BGRB;
	ग_लिखोl(ARCMSR_INBOUND_MESG0_STOP_BGRB, reg->inbound_msgaddr0);
	अगर (!arcmsr_hbaD_रुको_msgपूर्णांक_पढ़ोy(pACB))
		pr_notice("arcmsr%d: wait 'stop adapter background rebuild' "
			"timeout\n", pACB->host->host_no);
पूर्ण

अटल व्योम arcmsr_hbaE_stop_bgrb(काष्ठा AdapterControlBlock *pACB)
अणु
	काष्ठा MessageUnit_E __iomem *reg = pACB->pmuE;

	pACB->acb_flags &= ~ACB_F_MSG_START_BGRB;
	ग_लिखोl(ARCMSR_INBOUND_MESG0_STOP_BGRB, &reg->inbound_msgaddr0);
	pACB->out_करोorbell ^= ARCMSR_HBEMU_DRV2IOP_MESSAGE_CMD_DONE;
	ग_लिखोl(pACB->out_करोorbell, &reg->iobound_करोorbell);
	अगर (!arcmsr_hbaE_रुको_msgपूर्णांक_पढ़ोy(pACB)) अणु
		pr_notice("arcmsr%d: wait 'stop adapter background rebuild' "
			"timeout\n", pACB->host->host_no);
	पूर्ण
पूर्ण

अटल व्योम arcmsr_stop_adapter_bgrb(काष्ठा AdapterControlBlock *acb)
अणु
	चयन (acb->adapter_type) अणु
	हाल ACB_ADAPTER_TYPE_A:
		arcmsr_hbaA_stop_bgrb(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_B:
		arcmsr_hbaB_stop_bgrb(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_C:
		arcmsr_hbaC_stop_bgrb(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_D:
		arcmsr_hbaD_stop_bgrb(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_E:
	हाल ACB_ADAPTER_TYPE_F:
		arcmsr_hbaE_stop_bgrb(acb);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम arcmsr_मुक्त_ccb_pool(काष्ठा AdapterControlBlock *acb)
अणु
	dma_मुक्त_coherent(&acb->pdev->dev, acb->uncache_size, acb->dma_coherent, acb->dma_coherent_handle);
पूर्ण

अटल व्योम arcmsr_iop_message_पढ़ो(काष्ठा AdapterControlBlock *acb)
अणु
	चयन (acb->adapter_type) अणु
	हाल ACB_ADAPTER_TYPE_A: अणु
		काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;
		ग_लिखोl(ARCMSR_INBOUND_DRIVER_DATA_READ_OK, &reg->inbound_करोorbell);
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_B: अणु
		काष्ठा MessageUnit_B *reg = acb->pmuB;
		ग_लिखोl(ARCMSR_DRV2IOP_DATA_READ_OK, reg->drv2iop_करोorbell);
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_C: अणु
		काष्ठा MessageUnit_C __iomem *reg = acb->pmuC;

		ग_लिखोl(ARCMSR_HBCMU_DRV2IOP_DATA_READ_OK, &reg->inbound_करोorbell);
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_D: अणु
		काष्ठा MessageUnit_D *reg = acb->pmuD;
		ग_लिखोl(ARCMSR_ARC1214_DRV2IOP_DATA_OUT_READ,
			reg->inbound_करोorbell);
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_E:
	हाल ACB_ADAPTER_TYPE_F: अणु
		काष्ठा MessageUnit_E __iomem *reg = acb->pmuE;
		acb->out_करोorbell ^= ARCMSR_HBEMU_DRV2IOP_DATA_READ_OK;
		ग_लिखोl(acb->out_करोorbell, &reg->iobound_करोorbell);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम arcmsr_iop_message_wrote(काष्ठा AdapterControlBlock *acb)
अणु
	चयन (acb->adapter_type) अणु
	हाल ACB_ADAPTER_TYPE_A: अणु
		काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;
		/*
		** push inbound करोorbell tell iop, driver data ग_लिखो ok
		** and रुको reply on next hwपूर्णांकerrupt क्रम next Qbuffer post
		*/
		ग_लिखोl(ARCMSR_INBOUND_DRIVER_DATA_WRITE_OK, &reg->inbound_करोorbell);
		पूर्ण
		अवरोध;

	हाल ACB_ADAPTER_TYPE_B: अणु
		काष्ठा MessageUnit_B *reg = acb->pmuB;
		/*
		** push inbound करोorbell tell iop, driver data ग_लिखो ok
		** and रुको reply on next hwपूर्णांकerrupt क्रम next Qbuffer post
		*/
		ग_लिखोl(ARCMSR_DRV2IOP_DATA_WRITE_OK, reg->drv2iop_करोorbell);
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_C: अणु
		काष्ठा MessageUnit_C __iomem *reg = acb->pmuC;
		/*
		** push inbound करोorbell tell iop, driver data ग_लिखो ok
		** and रुको reply on next hwपूर्णांकerrupt क्रम next Qbuffer post
		*/
		ग_लिखोl(ARCMSR_HBCMU_DRV2IOP_DATA_WRITE_OK, &reg->inbound_करोorbell);
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_D: अणु
		काष्ठा MessageUnit_D *reg = acb->pmuD;
		ग_लिखोl(ARCMSR_ARC1214_DRV2IOP_DATA_IN_READY,
			reg->inbound_करोorbell);
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_E:
	हाल ACB_ADAPTER_TYPE_F: अणु
		काष्ठा MessageUnit_E __iomem *reg = acb->pmuE;
		acb->out_करोorbell ^= ARCMSR_HBEMU_DRV2IOP_DATA_WRITE_OK;
		ग_लिखोl(acb->out_करोorbell, &reg->iobound_करोorbell);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

काष्ठा QBUFFER __iomem *arcmsr_get_iop_rqbuffer(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा QBUFFER __iomem *qbuffer = शून्य;
	चयन (acb->adapter_type) अणु

	हाल ACB_ADAPTER_TYPE_A: अणु
		काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;
		qbuffer = (काष्ठा QBUFFER __iomem *)&reg->message_rbuffer;
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_B: अणु
		काष्ठा MessageUnit_B *reg = acb->pmuB;
		qbuffer = (काष्ठा QBUFFER __iomem *)reg->message_rbuffer;
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_C: अणु
		काष्ठा MessageUnit_C __iomem *phbcmu = acb->pmuC;
		qbuffer = (काष्ठा QBUFFER __iomem *)&phbcmu->message_rbuffer;
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_D: अणु
		काष्ठा MessageUnit_D *reg = acb->pmuD;
		qbuffer = (काष्ठा QBUFFER __iomem *)reg->message_rbuffer;
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_E: अणु
		काष्ठा MessageUnit_E __iomem *reg = acb->pmuE;
		qbuffer = (काष्ठा QBUFFER __iomem *)&reg->message_rbuffer;
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_F: अणु
		qbuffer = (काष्ठा QBUFFER __iomem *)acb->message_rbuffer;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस qbuffer;
पूर्ण

अटल काष्ठा QBUFFER __iomem *arcmsr_get_iop_wqbuffer(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा QBUFFER __iomem *pqbuffer = शून्य;
	चयन (acb->adapter_type) अणु

	हाल ACB_ADAPTER_TYPE_A: अणु
		काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;
		pqbuffer = (काष्ठा QBUFFER __iomem *) &reg->message_wbuffer;
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_B: अणु
		काष्ठा MessageUnit_B  *reg = acb->pmuB;
		pqbuffer = (काष्ठा QBUFFER __iomem *)reg->message_wbuffer;
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_C: अणु
		काष्ठा MessageUnit_C __iomem *reg = acb->pmuC;
		pqbuffer = (काष्ठा QBUFFER __iomem *)&reg->message_wbuffer;
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_D: अणु
		काष्ठा MessageUnit_D *reg = acb->pmuD;
		pqbuffer = (काष्ठा QBUFFER __iomem *)reg->message_wbuffer;
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_E: अणु
		काष्ठा MessageUnit_E __iomem *reg = acb->pmuE;
		pqbuffer = (काष्ठा QBUFFER __iomem *)&reg->message_wbuffer;
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_F:
		pqbuffer = (काष्ठा QBUFFER __iomem *)acb->message_wbuffer;
		अवरोध;
	पूर्ण
	वापस pqbuffer;
पूर्ण

अटल uपूर्णांक32_t
arcmsr_Read_iop_rqbuffer_in_DWORD(काष्ठा AdapterControlBlock *acb,
		काष्ठा QBUFFER __iomem *prbuffer)
अणु
	uपूर्णांक8_t *pQbuffer;
	uपूर्णांक8_t *buf1 = शून्य;
	uपूर्णांक32_t __iomem *iop_data;
	uपूर्णांक32_t iop_len, data_len, *buf2 = शून्य;

	iop_data = (uपूर्णांक32_t __iomem *)prbuffer->data;
	iop_len = पढ़ोl(&prbuffer->data_len);
	अगर (iop_len > 0) अणु
		buf1 = kदो_स्मृति(128, GFP_ATOMIC);
		buf2 = (uपूर्णांक32_t *)buf1;
		अगर (buf1 == शून्य)
			वापस 0;
		data_len = iop_len;
		जबतक (data_len >= 4) अणु
			*buf2++ = पढ़ोl(iop_data);
			iop_data++;
			data_len -= 4;
		पूर्ण
		अगर (data_len)
			*buf2 = पढ़ोl(iop_data);
		buf2 = (uपूर्णांक32_t *)buf1;
	पूर्ण
	जबतक (iop_len > 0) अणु
		pQbuffer = &acb->rqbuffer[acb->rqbuf_putIndex];
		*pQbuffer = *buf1;
		acb->rqbuf_putIndex++;
		/* अगर last, index number set it to 0 */
		acb->rqbuf_putIndex %= ARCMSR_MAX_QBUFFER;
		buf1++;
		iop_len--;
	पूर्ण
	kमुक्त(buf2);
	/* let IOP know data has been पढ़ो */
	arcmsr_iop_message_पढ़ो(acb);
	वापस 1;
पूर्ण

uपूर्णांक32_t
arcmsr_Read_iop_rqbuffer_data(काष्ठा AdapterControlBlock *acb,
	काष्ठा QBUFFER __iomem *prbuffer) अणु

	uपूर्णांक8_t *pQbuffer;
	uपूर्णांक8_t __iomem *iop_data;
	uपूर्णांक32_t iop_len;

	अगर (acb->adapter_type > ACB_ADAPTER_TYPE_B)
		वापस arcmsr_Read_iop_rqbuffer_in_DWORD(acb, prbuffer);
	iop_data = (uपूर्णांक8_t __iomem *)prbuffer->data;
	iop_len = पढ़ोl(&prbuffer->data_len);
	जबतक (iop_len > 0) अणु
		pQbuffer = &acb->rqbuffer[acb->rqbuf_putIndex];
		*pQbuffer = पढ़ोb(iop_data);
		acb->rqbuf_putIndex++;
		acb->rqbuf_putIndex %= ARCMSR_MAX_QBUFFER;
		iop_data++;
		iop_len--;
	पूर्ण
	arcmsr_iop_message_पढ़ो(acb);
	वापस 1;
पूर्ण

अटल व्योम arcmsr_iop2drv_data_wrote_handle(काष्ठा AdapterControlBlock *acb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा QBUFFER __iomem  *prbuffer;
	पूर्णांक32_t buf_empty_len;

	spin_lock_irqsave(&acb->rqbuffer_lock, flags);
	prbuffer = arcmsr_get_iop_rqbuffer(acb);
	buf_empty_len = (acb->rqbuf_putIndex - acb->rqbuf_getIndex - 1) &
		(ARCMSR_MAX_QBUFFER - 1);
	अगर (buf_empty_len >= पढ़ोl(&prbuffer->data_len)) अणु
		अगर (arcmsr_Read_iop_rqbuffer_data(acb, prbuffer) == 0)
			acb->acb_flags |= ACB_F_IOPDATA_OVERFLOW;
	पूर्ण अन्यथा
		acb->acb_flags |= ACB_F_IOPDATA_OVERFLOW;
	spin_unlock_irqrestore(&acb->rqbuffer_lock, flags);
पूर्ण

अटल व्योम arcmsr_ग_लिखो_ioctldata2iop_in_DWORD(काष्ठा AdapterControlBlock *acb)
अणु
	uपूर्णांक8_t *pQbuffer;
	काष्ठा QBUFFER __iomem *pwbuffer;
	uपूर्णांक8_t *buf1 = शून्य;
	uपूर्णांक32_t __iomem *iop_data;
	uपूर्णांक32_t allxfer_len = 0, data_len, *buf2 = शून्य, data;

	अगर (acb->acb_flags & ACB_F_MESSAGE_WQBUFFER_READED) अणु
		buf1 = kदो_स्मृति(128, GFP_ATOMIC);
		buf2 = (uपूर्णांक32_t *)buf1;
		अगर (buf1 == शून्य)
			वापस;

		acb->acb_flags &= (~ACB_F_MESSAGE_WQBUFFER_READED);
		pwbuffer = arcmsr_get_iop_wqbuffer(acb);
		iop_data = (uपूर्णांक32_t __iomem *)pwbuffer->data;
		जबतक ((acb->wqbuf_getIndex != acb->wqbuf_putIndex)
			&& (allxfer_len < 124)) अणु
			pQbuffer = &acb->wqbuffer[acb->wqbuf_getIndex];
			*buf1 = *pQbuffer;
			acb->wqbuf_getIndex++;
			acb->wqbuf_getIndex %= ARCMSR_MAX_QBUFFER;
			buf1++;
			allxfer_len++;
		पूर्ण
		data_len = allxfer_len;
		buf1 = (uपूर्णांक8_t *)buf2;
		जबतक (data_len >= 4) अणु
			data = *buf2++;
			ग_लिखोl(data, iop_data);
			iop_data++;
			data_len -= 4;
		पूर्ण
		अगर (data_len) अणु
			data = *buf2;
			ग_लिखोl(data, iop_data);
		पूर्ण
		ग_लिखोl(allxfer_len, &pwbuffer->data_len);
		kमुक्त(buf1);
		arcmsr_iop_message_wrote(acb);
	पूर्ण
पूर्ण

व्योम
arcmsr_ग_लिखो_ioctldata2iop(काष्ठा AdapterControlBlock *acb)
अणु
	uपूर्णांक8_t *pQbuffer;
	काष्ठा QBUFFER __iomem *pwbuffer;
	uपूर्णांक8_t __iomem *iop_data;
	पूर्णांक32_t allxfer_len = 0;

	अगर (acb->adapter_type > ACB_ADAPTER_TYPE_B) अणु
		arcmsr_ग_लिखो_ioctldata2iop_in_DWORD(acb);
		वापस;
	पूर्ण
	अगर (acb->acb_flags & ACB_F_MESSAGE_WQBUFFER_READED) अणु
		acb->acb_flags &= (~ACB_F_MESSAGE_WQBUFFER_READED);
		pwbuffer = arcmsr_get_iop_wqbuffer(acb);
		iop_data = (uपूर्णांक8_t __iomem *)pwbuffer->data;
		जबतक ((acb->wqbuf_getIndex != acb->wqbuf_putIndex)
			&& (allxfer_len < 124)) अणु
			pQbuffer = &acb->wqbuffer[acb->wqbuf_getIndex];
			ग_लिखोb(*pQbuffer, iop_data);
			acb->wqbuf_getIndex++;
			acb->wqbuf_getIndex %= ARCMSR_MAX_QBUFFER;
			iop_data++;
			allxfer_len++;
		पूर्ण
		ग_लिखोl(allxfer_len, &pwbuffer->data_len);
		arcmsr_iop_message_wrote(acb);
	पूर्ण
पूर्ण

अटल व्योम arcmsr_iop2drv_data_पढ़ो_handle(काष्ठा AdapterControlBlock *acb)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&acb->wqbuffer_lock, flags);
	acb->acb_flags |= ACB_F_MESSAGE_WQBUFFER_READED;
	अगर (acb->wqbuf_getIndex != acb->wqbuf_putIndex)
		arcmsr_ग_लिखो_ioctldata2iop(acb);
	अगर (acb->wqbuf_getIndex == acb->wqbuf_putIndex)
		acb->acb_flags |= ACB_F_MESSAGE_WQBUFFER_CLEARED;
	spin_unlock_irqrestore(&acb->wqbuffer_lock, flags);
पूर्ण

अटल व्योम arcmsr_hbaA_करोorbell_isr(काष्ठा AdapterControlBlock *acb)
अणु
	uपूर्णांक32_t outbound_करोorbell;
	काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;
	outbound_करोorbell = पढ़ोl(&reg->outbound_करोorbell);
	करो अणु
		ग_लिखोl(outbound_करोorbell, &reg->outbound_करोorbell);
		अगर (outbound_करोorbell & ARCMSR_OUTBOUND_IOP331_DATA_WRITE_OK)
			arcmsr_iop2drv_data_wrote_handle(acb);
		अगर (outbound_करोorbell & ARCMSR_OUTBOUND_IOP331_DATA_READ_OK)
			arcmsr_iop2drv_data_पढ़ो_handle(acb);
		outbound_करोorbell = पढ़ोl(&reg->outbound_करोorbell);
	पूर्ण जबतक (outbound_करोorbell & (ARCMSR_OUTBOUND_IOP331_DATA_WRITE_OK
		| ARCMSR_OUTBOUND_IOP331_DATA_READ_OK));
पूर्ण
अटल व्योम arcmsr_hbaC_करोorbell_isr(काष्ठा AdapterControlBlock *pACB)
अणु
	uपूर्णांक32_t outbound_करोorbell;
	काष्ठा MessageUnit_C __iomem *reg = pACB->pmuC;
	/*
	*******************************************************************
	**  Maybe here we need to check wrqbuffer_lock is lock or not
	**  DOORBELL: din! करोn!
	**  check अगर there are any mail need to pack from firmware
	*******************************************************************
	*/
	outbound_करोorbell = पढ़ोl(&reg->outbound_करोorbell);
	करो अणु
		ग_लिखोl(outbound_करोorbell, &reg->outbound_करोorbell_clear);
		पढ़ोl(&reg->outbound_करोorbell_clear);
		अगर (outbound_करोorbell & ARCMSR_HBCMU_IOP2DRV_DATA_WRITE_OK)
			arcmsr_iop2drv_data_wrote_handle(pACB);
		अगर (outbound_करोorbell & ARCMSR_HBCMU_IOP2DRV_DATA_READ_OK)
			arcmsr_iop2drv_data_पढ़ो_handle(pACB);
		अगर (outbound_करोorbell & ARCMSR_HBCMU_IOP2DRV_MESSAGE_CMD_DONE)
			arcmsr_hbaC_message_isr(pACB);
		outbound_करोorbell = पढ़ोl(&reg->outbound_करोorbell);
	पूर्ण जबतक (outbound_करोorbell & (ARCMSR_HBCMU_IOP2DRV_DATA_WRITE_OK
		| ARCMSR_HBCMU_IOP2DRV_DATA_READ_OK
		| ARCMSR_HBCMU_IOP2DRV_MESSAGE_CMD_DONE));
पूर्ण

अटल व्योम arcmsr_hbaD_करोorbell_isr(काष्ठा AdapterControlBlock *pACB)
अणु
	uपूर्णांक32_t outbound_करोorbell;
	काष्ठा MessageUnit_D  *pmu = pACB->pmuD;

	outbound_करोorbell = पढ़ोl(pmu->outbound_करोorbell);
	करो अणु
		ग_लिखोl(outbound_करोorbell, pmu->outbound_करोorbell);
		अगर (outbound_करोorbell & ARCMSR_ARC1214_IOP2DRV_MESSAGE_CMD_DONE)
			arcmsr_hbaD_message_isr(pACB);
		अगर (outbound_करोorbell & ARCMSR_ARC1214_IOP2DRV_DATA_WRITE_OK)
			arcmsr_iop2drv_data_wrote_handle(pACB);
		अगर (outbound_करोorbell & ARCMSR_ARC1214_IOP2DRV_DATA_READ_OK)
			arcmsr_iop2drv_data_पढ़ो_handle(pACB);
		outbound_करोorbell = पढ़ोl(pmu->outbound_करोorbell);
	पूर्ण जबतक (outbound_करोorbell & (ARCMSR_ARC1214_IOP2DRV_DATA_WRITE_OK
		| ARCMSR_ARC1214_IOP2DRV_DATA_READ_OK
		| ARCMSR_ARC1214_IOP2DRV_MESSAGE_CMD_DONE));
पूर्ण

अटल व्योम arcmsr_hbaE_करोorbell_isr(काष्ठा AdapterControlBlock *pACB)
अणु
	uपूर्णांक32_t outbound_करोorbell, in_करोorbell, पंचांगp;
	काष्ठा MessageUnit_E __iomem *reg = pACB->pmuE;

	in_करोorbell = पढ़ोl(&reg->iobound_करोorbell);
	outbound_करोorbell = in_करोorbell ^ pACB->in_करोorbell;
	करो अणु
		ग_लिखोl(0, &reg->host_पूर्णांक_status); /* clear पूर्णांकerrupt */
		अगर (outbound_करोorbell & ARCMSR_HBEMU_IOP2DRV_DATA_WRITE_OK) अणु
			arcmsr_iop2drv_data_wrote_handle(pACB);
		पूर्ण
		अगर (outbound_करोorbell & ARCMSR_HBEMU_IOP2DRV_DATA_READ_OK) अणु
			arcmsr_iop2drv_data_पढ़ो_handle(pACB);
		पूर्ण
		अगर (outbound_करोorbell & ARCMSR_HBEMU_IOP2DRV_MESSAGE_CMD_DONE) अणु
			arcmsr_hbaE_message_isr(pACB);
		पूर्ण
		पंचांगp = in_करोorbell;
		in_करोorbell = पढ़ोl(&reg->iobound_करोorbell);
		outbound_करोorbell = पंचांगp ^ in_करोorbell;
	पूर्ण जबतक (outbound_करोorbell & (ARCMSR_HBEMU_IOP2DRV_DATA_WRITE_OK
		| ARCMSR_HBEMU_IOP2DRV_DATA_READ_OK
		| ARCMSR_HBEMU_IOP2DRV_MESSAGE_CMD_DONE));
	pACB->in_करोorbell = in_करोorbell;
पूर्ण

अटल व्योम arcmsr_hbaA_postqueue_isr(काष्ठा AdapterControlBlock *acb)
अणु
	uपूर्णांक32_t flag_ccb;
	काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;
	काष्ठा ARCMSR_CDB *pARCMSR_CDB;
	काष्ठा CommandControlBlock *pCCB;
	bool error;
	अचिन्हित दीर्घ cdb_phy_addr;

	जबतक ((flag_ccb = पढ़ोl(&reg->outbound_queueport)) != 0xFFFFFFFF) अणु
		cdb_phy_addr = (flag_ccb << 5) & 0xffffffff;
		अगर (acb->cdb_phyadd_hipart)
			cdb_phy_addr = cdb_phy_addr | acb->cdb_phyadd_hipart;
		pARCMSR_CDB = (काष्ठा ARCMSR_CDB *)(acb->vir2phy_offset + cdb_phy_addr);
		pCCB = container_of(pARCMSR_CDB, काष्ठा CommandControlBlock, arcmsr_cdb);
		error = (flag_ccb & ARCMSR_CCBREPLY_FLAG_ERROR_MODE0) ? true : false;
		arcmsr_drain_करोnequeue(acb, pCCB, error);
	पूर्ण
पूर्ण
अटल व्योम arcmsr_hbaB_postqueue_isr(काष्ठा AdapterControlBlock *acb)
अणु
	uपूर्णांक32_t index;
	uपूर्णांक32_t flag_ccb;
	काष्ठा MessageUnit_B *reg = acb->pmuB;
	काष्ठा ARCMSR_CDB *pARCMSR_CDB;
	काष्ठा CommandControlBlock *pCCB;
	bool error;
	अचिन्हित दीर्घ cdb_phy_addr;

	index = reg->करोneq_index;
	जबतक ((flag_ccb = reg->करोne_qbuffer[index]) != 0) अणु
		cdb_phy_addr = (flag_ccb << 5) & 0xffffffff;
		अगर (acb->cdb_phyadd_hipart)
			cdb_phy_addr = cdb_phy_addr | acb->cdb_phyadd_hipart;
		pARCMSR_CDB = (काष्ठा ARCMSR_CDB *)(acb->vir2phy_offset + cdb_phy_addr);
		pCCB = container_of(pARCMSR_CDB, काष्ठा CommandControlBlock, arcmsr_cdb);
		error = (flag_ccb & ARCMSR_CCBREPLY_FLAG_ERROR_MODE0) ? true : false;
		arcmsr_drain_करोnequeue(acb, pCCB, error);
		reg->करोne_qbuffer[index] = 0;
		index++;
		index %= ARCMSR_MAX_HBB_POSTQUEUE;
		reg->करोneq_index = index;
	पूर्ण
पूर्ण

अटल व्योम arcmsr_hbaC_postqueue_isr(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा MessageUnit_C __iomem *phbcmu;
	काष्ठा ARCMSR_CDB *arcmsr_cdb;
	काष्ठा CommandControlBlock *ccb;
	uपूर्णांक32_t flag_ccb, throttling = 0;
	अचिन्हित दीर्घ ccb_cdb_phy;
	पूर्णांक error;

	phbcmu = acb->pmuC;
	/* areca cdb command करोne */
	/* Use correct offset and size क्रम syncing */

	जबतक ((flag_ccb = पढ़ोl(&phbcmu->outbound_queueport_low)) !=
			0xFFFFFFFF) अणु
		ccb_cdb_phy = (flag_ccb & 0xFFFFFFF0);
		अगर (acb->cdb_phyadd_hipart)
			ccb_cdb_phy = ccb_cdb_phy | acb->cdb_phyadd_hipart;
		arcmsr_cdb = (काष्ठा ARCMSR_CDB *)(acb->vir2phy_offset
			+ ccb_cdb_phy);
		ccb = container_of(arcmsr_cdb, काष्ठा CommandControlBlock,
			arcmsr_cdb);
		error = (flag_ccb & ARCMSR_CCBREPLY_FLAG_ERROR_MODE1)
			? true : false;
		/* check अगर command करोne with no error */
		arcmsr_drain_करोnequeue(acb, ccb, error);
		throttling++;
		अगर (throttling == ARCMSR_HBC_ISR_THROTTLING_LEVEL) अणु
			ग_लिखोl(ARCMSR_HBCMU_DRV2IOP_POSTQUEUE_THROTTLING,
				&phbcmu->inbound_करोorbell);
			throttling = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम arcmsr_hbaD_postqueue_isr(काष्ठा AdapterControlBlock *acb)
अणु
	u32 outbound_ग_लिखो_poपूर्णांकer, करोneq_index, index_stripped, toggle;
	uपूर्णांक32_t addressLow;
	पूर्णांक error;
	काष्ठा MessageUnit_D  *pmu;
	काष्ठा ARCMSR_CDB *arcmsr_cdb;
	काष्ठा CommandControlBlock *ccb;
	अचिन्हित दीर्घ flags, ccb_cdb_phy;

	spin_lock_irqsave(&acb->करोneq_lock, flags);
	pmu = acb->pmuD;
	outbound_ग_लिखो_poपूर्णांकer = pmu->करोne_qbuffer[0].addressLow + 1;
	करोneq_index = pmu->करोneq_index;
	अगर ((करोneq_index & 0xFFF) != (outbound_ग_लिखो_poपूर्णांकer & 0xFFF)) अणु
		करो अणु
			toggle = करोneq_index & 0x4000;
			index_stripped = (करोneq_index & 0xFFF) + 1;
			index_stripped %= ARCMSR_MAX_ARC1214_DONEQUEUE;
			pmu->करोneq_index = index_stripped ? (index_stripped | toggle) :
				((toggle ^ 0x4000) + 1);
			करोneq_index = pmu->करोneq_index;
			addressLow = pmu->करोne_qbuffer[करोneq_index &
				0xFFF].addressLow;
			ccb_cdb_phy = (addressLow & 0xFFFFFFF0);
			अगर (acb->cdb_phyadd_hipart)
				ccb_cdb_phy = ccb_cdb_phy | acb->cdb_phyadd_hipart;
			arcmsr_cdb = (काष्ठा ARCMSR_CDB *)(acb->vir2phy_offset
				+ ccb_cdb_phy);
			ccb = container_of(arcmsr_cdb,
				काष्ठा CommandControlBlock, arcmsr_cdb);
			error = (addressLow & ARCMSR_CCBREPLY_FLAG_ERROR_MODE1)
				? true : false;
			arcmsr_drain_करोnequeue(acb, ccb, error);
			ग_लिखोl(करोneq_index, pmu->outboundlist_पढ़ो_poपूर्णांकer);
		पूर्ण जबतक ((करोneq_index & 0xFFF) !=
			(outbound_ग_लिखो_poपूर्णांकer & 0xFFF));
	पूर्ण
	ग_लिखोl(ARCMSR_ARC1214_OUTBOUND_LIST_INTERRUPT_CLEAR,
		pmu->outboundlist_पूर्णांकerrupt_cause);
	पढ़ोl(pmu->outboundlist_पूर्णांकerrupt_cause);
	spin_unlock_irqrestore(&acb->करोneq_lock, flags);
पूर्ण

अटल व्योम arcmsr_hbaE_postqueue_isr(काष्ठा AdapterControlBlock *acb)
अणु
	uपूर्णांक32_t करोneq_index;
	uपूर्णांक16_t cmdSMID;
	पूर्णांक error;
	काष्ठा MessageUnit_E __iomem *pmu;
	काष्ठा CommandControlBlock *ccb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&acb->करोneq_lock, flags);
	करोneq_index = acb->करोneq_index;
	pmu = acb->pmuE;
	जबतक ((पढ़ोl(&pmu->reply_post_producer_index) & 0xFFFF) != करोneq_index) अणु
		cmdSMID = acb->pCompletionQ[करोneq_index].cmdSMID;
		ccb = acb->pccb_pool[cmdSMID];
		error = (acb->pCompletionQ[करोneq_index].cmdFlag
			& ARCMSR_CCBREPLY_FLAG_ERROR_MODE1) ? true : false;
		arcmsr_drain_करोnequeue(acb, ccb, error);
		करोneq_index++;
		अगर (करोneq_index >= acb->completionQ_entry)
			करोneq_index = 0;
	पूर्ण
	acb->करोneq_index = करोneq_index;
	ग_लिखोl(करोneq_index, &pmu->reply_post_consumer_index);
	spin_unlock_irqrestore(&acb->करोneq_lock, flags);
पूर्ण

अटल व्योम arcmsr_hbaF_postqueue_isr(काष्ठा AdapterControlBlock *acb)
अणु
	uपूर्णांक32_t करोneq_index;
	uपूर्णांक16_t cmdSMID;
	पूर्णांक error;
	काष्ठा MessageUnit_F __iomem *phbcmu;
	काष्ठा CommandControlBlock *ccb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&acb->करोneq_lock, flags);
	करोneq_index = acb->करोneq_index;
	phbcmu = acb->pmuF;
	जबतक (1) अणु
		cmdSMID = acb->pCompletionQ[करोneq_index].cmdSMID;
		अगर (cmdSMID == 0xffff)
			अवरोध;
		ccb = acb->pccb_pool[cmdSMID];
		error = (acb->pCompletionQ[करोneq_index].cmdFlag &
			ARCMSR_CCBREPLY_FLAG_ERROR_MODE1) ? true : false;
		arcmsr_drain_करोnequeue(acb, ccb, error);
		acb->pCompletionQ[करोneq_index].cmdSMID = 0xffff;
		करोneq_index++;
		अगर (करोneq_index >= acb->completionQ_entry)
			करोneq_index = 0;
	पूर्ण
	acb->करोneq_index = करोneq_index;
	ग_लिखोl(करोneq_index, &phbcmu->reply_post_consumer_index);
	spin_unlock_irqrestore(&acb->करोneq_lock, flags);
पूर्ण

/*
**********************************************************************************
** Handle a message पूर्णांकerrupt
**
** The only message पूर्णांकerrupt we expect is in response to a query क्रम the current adapter config.  
** We want this in order to compare the drivemap so that we can detect newly-attached drives.
**********************************************************************************
*/
अटल व्योम arcmsr_hbaA_message_isr(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा MessageUnit_A __iomem *reg  = acb->pmuA;
	/*clear पूर्णांकerrupt and message state*/
	ग_लिखोl(ARCMSR_MU_OUTBOUND_MESSAGE0_INT, &reg->outbound_पूर्णांकstatus);
	अगर (acb->acb_flags & ACB_F_MSG_GET_CONFIG)
		schedule_work(&acb->arcmsr_करो_message_isr_bh);
पूर्ण
अटल व्योम arcmsr_hbaB_message_isr(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा MessageUnit_B *reg  = acb->pmuB;

	/*clear पूर्णांकerrupt and message state*/
	ग_लिखोl(ARCMSR_MESSAGE_INT_CLEAR_PATTERN, reg->iop2drv_करोorbell);
	अगर (acb->acb_flags & ACB_F_MSG_GET_CONFIG)
		schedule_work(&acb->arcmsr_करो_message_isr_bh);
पूर्ण
/*
**********************************************************************************
** Handle a message पूर्णांकerrupt
**
** The only message पूर्णांकerrupt we expect is in response to a query क्रम the
** current adapter config.
** We want this in order to compare the drivemap so that we can detect newly-attached drives.
**********************************************************************************
*/
अटल व्योम arcmsr_hbaC_message_isr(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा MessageUnit_C __iomem *reg  = acb->pmuC;
	/*clear पूर्णांकerrupt and message state*/
	ग_लिखोl(ARCMSR_HBCMU_IOP2DRV_MESSAGE_CMD_DONE_DOORBELL_CLEAR, &reg->outbound_करोorbell_clear);
	अगर (acb->acb_flags & ACB_F_MSG_GET_CONFIG)
		schedule_work(&acb->arcmsr_करो_message_isr_bh);
पूर्ण

अटल व्योम arcmsr_hbaD_message_isr(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा MessageUnit_D *reg  = acb->pmuD;

	ग_लिखोl(ARCMSR_ARC1214_IOP2DRV_MESSAGE_CMD_DONE, reg->outbound_करोorbell);
	पढ़ोl(reg->outbound_करोorbell);
	अगर (acb->acb_flags & ACB_F_MSG_GET_CONFIG)
		schedule_work(&acb->arcmsr_करो_message_isr_bh);
पूर्ण

अटल व्योम arcmsr_hbaE_message_isr(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा MessageUnit_E __iomem *reg  = acb->pmuE;

	ग_लिखोl(0, &reg->host_पूर्णांक_status);
	अगर (acb->acb_flags & ACB_F_MSG_GET_CONFIG)
		schedule_work(&acb->arcmsr_करो_message_isr_bh);
पूर्ण

अटल पूर्णांक arcmsr_hbaA_handle_isr(काष्ठा AdapterControlBlock *acb)
अणु
	uपूर्णांक32_t outbound_पूर्णांकstatus;
	काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;
	outbound_पूर्णांकstatus = पढ़ोl(&reg->outbound_पूर्णांकstatus) &
		acb->outbound_पूर्णांक_enable;
	अगर (!(outbound_पूर्णांकstatus & ARCMSR_MU_OUTBOUND_HANDLE_INT))
		वापस IRQ_NONE;
	करो अणु
		ग_लिखोl(outbound_पूर्णांकstatus, &reg->outbound_पूर्णांकstatus);
		अगर (outbound_पूर्णांकstatus & ARCMSR_MU_OUTBOUND_DOORBELL_INT)
			arcmsr_hbaA_करोorbell_isr(acb);
		अगर (outbound_पूर्णांकstatus & ARCMSR_MU_OUTBOUND_POSTQUEUE_INT)
			arcmsr_hbaA_postqueue_isr(acb);
		अगर (outbound_पूर्णांकstatus & ARCMSR_MU_OUTBOUND_MESSAGE0_INT)
			arcmsr_hbaA_message_isr(acb);
		outbound_पूर्णांकstatus = पढ़ोl(&reg->outbound_पूर्णांकstatus) &
			acb->outbound_पूर्णांक_enable;
	पूर्ण जबतक (outbound_पूर्णांकstatus & (ARCMSR_MU_OUTBOUND_DOORBELL_INT
		| ARCMSR_MU_OUTBOUND_POSTQUEUE_INT
		| ARCMSR_MU_OUTBOUND_MESSAGE0_INT));
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक arcmsr_hbaB_handle_isr(काष्ठा AdapterControlBlock *acb)
अणु
	uपूर्णांक32_t outbound_करोorbell;
	काष्ठा MessageUnit_B *reg = acb->pmuB;
	outbound_करोorbell = पढ़ोl(reg->iop2drv_करोorbell) &
				acb->outbound_पूर्णांक_enable;
	अगर (!outbound_करोorbell)
		वापस IRQ_NONE;
	करो अणु
		ग_लिखोl(~outbound_करोorbell, reg->iop2drv_करोorbell);
		ग_लिखोl(ARCMSR_DRV2IOP_END_OF_INTERRUPT, reg->drv2iop_करोorbell);
		अगर (outbound_करोorbell & ARCMSR_IOP2DRV_DATA_WRITE_OK)
			arcmsr_iop2drv_data_wrote_handle(acb);
		अगर (outbound_करोorbell & ARCMSR_IOP2DRV_DATA_READ_OK)
			arcmsr_iop2drv_data_पढ़ो_handle(acb);
		अगर (outbound_करोorbell & ARCMSR_IOP2DRV_CDB_DONE)
			arcmsr_hbaB_postqueue_isr(acb);
		अगर (outbound_करोorbell & ARCMSR_IOP2DRV_MESSAGE_CMD_DONE)
			arcmsr_hbaB_message_isr(acb);
		outbound_करोorbell = पढ़ोl(reg->iop2drv_करोorbell) &
			acb->outbound_पूर्णांक_enable;
	पूर्ण जबतक (outbound_करोorbell & (ARCMSR_IOP2DRV_DATA_WRITE_OK
		| ARCMSR_IOP2DRV_DATA_READ_OK
		| ARCMSR_IOP2DRV_CDB_DONE
		| ARCMSR_IOP2DRV_MESSAGE_CMD_DONE));
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक arcmsr_hbaC_handle_isr(काष्ठा AdapterControlBlock *pACB)
अणु
	uपूर्णांक32_t host_पूर्णांकerrupt_status;
	काष्ठा MessageUnit_C __iomem *phbcmu = pACB->pmuC;
	/*
	*********************************************
	**   check outbound पूर्णांकstatus
	*********************************************
	*/
	host_पूर्णांकerrupt_status = पढ़ोl(&phbcmu->host_पूर्णांक_status) &
		(ARCMSR_HBCMU_OUTBOUND_POSTQUEUE_ISR |
		ARCMSR_HBCMU_OUTBOUND_DOORBELL_ISR);
	अगर (!host_पूर्णांकerrupt_status)
		वापस IRQ_NONE;
	करो अणु
		अगर (host_पूर्णांकerrupt_status & ARCMSR_HBCMU_OUTBOUND_DOORBELL_ISR)
			arcmsr_hbaC_करोorbell_isr(pACB);
		/* MU post queue पूर्णांकerrupts*/
		अगर (host_पूर्णांकerrupt_status & ARCMSR_HBCMU_OUTBOUND_POSTQUEUE_ISR)
			arcmsr_hbaC_postqueue_isr(pACB);
		host_पूर्णांकerrupt_status = पढ़ोl(&phbcmu->host_पूर्णांक_status);
	पूर्ण जबतक (host_पूर्णांकerrupt_status & (ARCMSR_HBCMU_OUTBOUND_POSTQUEUE_ISR |
		ARCMSR_HBCMU_OUTBOUND_DOORBELL_ISR));
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t arcmsr_hbaD_handle_isr(काष्ठा AdapterControlBlock *pACB)
अणु
	u32 host_पूर्णांकerrupt_status;
	काष्ठा MessageUnit_D  *pmu = pACB->pmuD;

	host_पूर्णांकerrupt_status = पढ़ोl(pmu->host_पूर्णांक_status) &
		(ARCMSR_ARC1214_OUTBOUND_POSTQUEUE_ISR |
		ARCMSR_ARC1214_OUTBOUND_DOORBELL_ISR);
	अगर (!host_पूर्णांकerrupt_status)
		वापस IRQ_NONE;
	करो अणु
		/* MU post queue पूर्णांकerrupts*/
		अगर (host_पूर्णांकerrupt_status &
			ARCMSR_ARC1214_OUTBOUND_POSTQUEUE_ISR)
			arcmsr_hbaD_postqueue_isr(pACB);
		अगर (host_पूर्णांकerrupt_status &
			ARCMSR_ARC1214_OUTBOUND_DOORBELL_ISR)
			arcmsr_hbaD_करोorbell_isr(pACB);
		host_पूर्णांकerrupt_status = पढ़ोl(pmu->host_पूर्णांक_status);
	पूर्ण जबतक (host_पूर्णांकerrupt_status &
		(ARCMSR_ARC1214_OUTBOUND_POSTQUEUE_ISR |
		ARCMSR_ARC1214_OUTBOUND_DOORBELL_ISR));
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t arcmsr_hbaE_handle_isr(काष्ठा AdapterControlBlock *pACB)
अणु
	uपूर्णांक32_t host_पूर्णांकerrupt_status;
	काष्ठा MessageUnit_E __iomem *pmu = pACB->pmuE;

	host_पूर्णांकerrupt_status = पढ़ोl(&pmu->host_पूर्णांक_status) &
		(ARCMSR_HBEMU_OUTBOUND_POSTQUEUE_ISR |
		ARCMSR_HBEMU_OUTBOUND_DOORBELL_ISR);
	अगर (!host_पूर्णांकerrupt_status)
		वापस IRQ_NONE;
	करो अणु
		/* MU ioctl transfer करोorbell पूर्णांकerrupts*/
		अगर (host_पूर्णांकerrupt_status & ARCMSR_HBEMU_OUTBOUND_DOORBELL_ISR) अणु
			arcmsr_hbaE_करोorbell_isr(pACB);
		पूर्ण
		/* MU post queue पूर्णांकerrupts*/
		अगर (host_पूर्णांकerrupt_status & ARCMSR_HBEMU_OUTBOUND_POSTQUEUE_ISR) अणु
			arcmsr_hbaE_postqueue_isr(pACB);
		पूर्ण
		host_पूर्णांकerrupt_status = पढ़ोl(&pmu->host_पूर्णांक_status);
	पूर्ण जबतक (host_पूर्णांकerrupt_status & (ARCMSR_HBEMU_OUTBOUND_POSTQUEUE_ISR |
		ARCMSR_HBEMU_OUTBOUND_DOORBELL_ISR));
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t arcmsr_hbaF_handle_isr(काष्ठा AdapterControlBlock *pACB)
अणु
	uपूर्णांक32_t host_पूर्णांकerrupt_status;
	काष्ठा MessageUnit_F __iomem *phbcmu = pACB->pmuF;

	host_पूर्णांकerrupt_status = पढ़ोl(&phbcmu->host_पूर्णांक_status) &
		(ARCMSR_HBEMU_OUTBOUND_POSTQUEUE_ISR |
		ARCMSR_HBEMU_OUTBOUND_DOORBELL_ISR);
	अगर (!host_पूर्णांकerrupt_status)
		वापस IRQ_NONE;
	करो अणु
		/* MU post queue पूर्णांकerrupts*/
		अगर (host_पूर्णांकerrupt_status & ARCMSR_HBEMU_OUTBOUND_POSTQUEUE_ISR)
			arcmsr_hbaF_postqueue_isr(pACB);

		/* MU ioctl transfer करोorbell पूर्णांकerrupts*/
		अगर (host_पूर्णांकerrupt_status & ARCMSR_HBEMU_OUTBOUND_DOORBELL_ISR)
			arcmsr_hbaE_करोorbell_isr(pACB);

		host_पूर्णांकerrupt_status = पढ़ोl(&phbcmu->host_पूर्णांक_status);
	पूर्ण जबतक (host_पूर्णांकerrupt_status & (ARCMSR_HBEMU_OUTBOUND_POSTQUEUE_ISR |
		ARCMSR_HBEMU_OUTBOUND_DOORBELL_ISR));
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t arcmsr_पूर्णांकerrupt(काष्ठा AdapterControlBlock *acb)
अणु
	चयन (acb->adapter_type) अणु
	हाल ACB_ADAPTER_TYPE_A:
		वापस arcmsr_hbaA_handle_isr(acb);
	हाल ACB_ADAPTER_TYPE_B:
		वापस arcmsr_hbaB_handle_isr(acb);
	हाल ACB_ADAPTER_TYPE_C:
		वापस arcmsr_hbaC_handle_isr(acb);
	हाल ACB_ADAPTER_TYPE_D:
		वापस arcmsr_hbaD_handle_isr(acb);
	हाल ACB_ADAPTER_TYPE_E:
		वापस arcmsr_hbaE_handle_isr(acb);
	हाल ACB_ADAPTER_TYPE_F:
		वापस arcmsr_hbaF_handle_isr(acb);
	शेष:
		वापस IRQ_NONE;
	पूर्ण
पूर्ण

अटल व्योम arcmsr_iop_parking(काष्ठा AdapterControlBlock *acb)
अणु
	अगर (acb) अणु
		/* stop adapter background rebuild */
		अगर (acb->acb_flags & ACB_F_MSG_START_BGRB) अणु
			uपूर्णांक32_t पूर्णांकmask_org;
			acb->acb_flags &= ~ACB_F_MSG_START_BGRB;
			पूर्णांकmask_org = arcmsr_disable_outbound_पूर्णांकs(acb);
			arcmsr_stop_adapter_bgrb(acb);
			arcmsr_flush_adapter_cache(acb);
			arcmsr_enable_outbound_पूर्णांकs(acb, पूर्णांकmask_org);
		पूर्ण
	पूर्ण
पूर्ण


व्योम arcmsr_clear_iop2drv_rqueue_buffer(काष्ठा AdapterControlBlock *acb)
अणु
	uपूर्णांक32_t	i;

	अगर (acb->acb_flags & ACB_F_IOPDATA_OVERFLOW) अणु
		क्रम (i = 0; i < 15; i++) अणु
			अगर (acb->acb_flags & ACB_F_IOPDATA_OVERFLOW) अणु
				acb->acb_flags &= ~ACB_F_IOPDATA_OVERFLOW;
				acb->rqbuf_getIndex = 0;
				acb->rqbuf_putIndex = 0;
				arcmsr_iop_message_पढ़ो(acb);
				mdelay(30);
			पूर्ण अन्यथा अगर (acb->rqbuf_getIndex !=
				   acb->rqbuf_putIndex) अणु
				acb->rqbuf_getIndex = 0;
				acb->rqbuf_putIndex = 0;
				mdelay(30);
			पूर्ण अन्यथा
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक arcmsr_iop_message_xfer(काष्ठा AdapterControlBlock *acb,
		काष्ठा scsi_cmnd *cmd)
अणु
	अक्षर *buffer;
	अचिन्हित लघु use_sg;
	पूर्णांक retvalue = 0, transfer_len = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा CMD_MESSAGE_FIELD *pcmdmessagefld;
	uपूर्णांक32_t controlcode = (uपूर्णांक32_t)cmd->cmnd[5] << 24 |
		(uपूर्णांक32_t)cmd->cmnd[6] << 16 |
		(uपूर्णांक32_t)cmd->cmnd[7] << 8 |
		(uपूर्णांक32_t)cmd->cmnd[8];
	काष्ठा scatterlist *sg;

	use_sg = scsi_sg_count(cmd);
	sg = scsi_sglist(cmd);
	buffer = kmap_atomic(sg_page(sg)) + sg->offset;
	अगर (use_sg > 1) अणु
		retvalue = ARCMSR_MESSAGE_FAIL;
		जाओ message_out;
	पूर्ण
	transfer_len += sg->length;
	अगर (transfer_len > माप(काष्ठा CMD_MESSAGE_FIELD)) अणु
		retvalue = ARCMSR_MESSAGE_FAIL;
		pr_info("%s: ARCMSR_MESSAGE_FAIL!\n", __func__);
		जाओ message_out;
	पूर्ण
	pcmdmessagefld = (काष्ठा CMD_MESSAGE_FIELD *)buffer;
	चयन (controlcode) अणु
	हाल ARCMSR_MESSAGE_READ_RQBUFFER: अणु
		अचिन्हित अक्षर *ver_addr;
		uपूर्णांक8_t *pपंचांगpQbuffer;
		uपूर्णांक32_t allxfer_len = 0;
		ver_addr = kदो_स्मृति(ARCMSR_API_DATA_BUFLEN, GFP_ATOMIC);
		अगर (!ver_addr) अणु
			retvalue = ARCMSR_MESSAGE_FAIL;
			pr_info("%s: memory not enough!\n", __func__);
			जाओ message_out;
		पूर्ण
		pपंचांगpQbuffer = ver_addr;
		spin_lock_irqsave(&acb->rqbuffer_lock, flags);
		अगर (acb->rqbuf_getIndex != acb->rqbuf_putIndex) अणु
			अचिन्हित पूर्णांक tail = acb->rqbuf_getIndex;
			अचिन्हित पूर्णांक head = acb->rqbuf_putIndex;
			अचिन्हित पूर्णांक cnt_to_end = CIRC_CNT_TO_END(head, tail, ARCMSR_MAX_QBUFFER);

			allxfer_len = CIRC_CNT(head, tail, ARCMSR_MAX_QBUFFER);
			अगर (allxfer_len > ARCMSR_API_DATA_BUFLEN)
				allxfer_len = ARCMSR_API_DATA_BUFLEN;

			अगर (allxfer_len <= cnt_to_end)
				स_नकल(pपंचांगpQbuffer, acb->rqbuffer + tail, allxfer_len);
			अन्यथा अणु
				स_नकल(pपंचांगpQbuffer, acb->rqbuffer + tail, cnt_to_end);
				स_नकल(pपंचांगpQbuffer + cnt_to_end, acb->rqbuffer, allxfer_len - cnt_to_end);
			पूर्ण
			acb->rqbuf_getIndex = (acb->rqbuf_getIndex + allxfer_len) % ARCMSR_MAX_QBUFFER;
		पूर्ण
		स_नकल(pcmdmessagefld->messagedatabuffer, ver_addr,
			allxfer_len);
		अगर (acb->acb_flags & ACB_F_IOPDATA_OVERFLOW) अणु
			काष्ठा QBUFFER __iomem *prbuffer;
			acb->acb_flags &= ~ACB_F_IOPDATA_OVERFLOW;
			prbuffer = arcmsr_get_iop_rqbuffer(acb);
			अगर (arcmsr_Read_iop_rqbuffer_data(acb, prbuffer) == 0)
				acb->acb_flags |= ACB_F_IOPDATA_OVERFLOW;
		पूर्ण
		spin_unlock_irqrestore(&acb->rqbuffer_lock, flags);
		kमुक्त(ver_addr);
		pcmdmessagefld->cmdmessage.Length = allxfer_len;
		अगर (acb->fw_flag == FW_DEADLOCK)
			pcmdmessagefld->cmdmessage.ReturnCode =
				ARCMSR_MESSAGE_RETURNCODE_BUS_HANG_ON;
		अन्यथा
			pcmdmessagefld->cmdmessage.ReturnCode =
				ARCMSR_MESSAGE_RETURNCODE_OK;
		अवरोध;
	पूर्ण
	हाल ARCMSR_MESSAGE_WRITE_WQBUFFER: अणु
		अचिन्हित अक्षर *ver_addr;
		uपूर्णांक32_t user_len;
		पूर्णांक32_t cnt2end;
		uपूर्णांक8_t *pQbuffer, *pपंचांगpuserbuffer;

		user_len = pcmdmessagefld->cmdmessage.Length;
		अगर (user_len > ARCMSR_API_DATA_BUFLEN) अणु
			retvalue = ARCMSR_MESSAGE_FAIL;
			जाओ message_out;
		पूर्ण

		ver_addr = kदो_स्मृति(ARCMSR_API_DATA_BUFLEN, GFP_ATOMIC);
		अगर (!ver_addr) अणु
			retvalue = ARCMSR_MESSAGE_FAIL;
			जाओ message_out;
		पूर्ण
		pपंचांगpuserbuffer = ver_addr;

		स_नकल(pपंचांगpuserbuffer,
			pcmdmessagefld->messagedatabuffer, user_len);
		spin_lock_irqsave(&acb->wqbuffer_lock, flags);
		अगर (acb->wqbuf_putIndex != acb->wqbuf_getIndex) अणु
			काष्ठा SENSE_DATA *sensebuffer =
				(काष्ठा SENSE_DATA *)cmd->sense_buffer;
			arcmsr_ग_लिखो_ioctldata2iop(acb);
			/* has error report sensedata */
			sensebuffer->ErrorCode = SCSI_SENSE_CURRENT_ERRORS;
			sensebuffer->SenseKey = ILLEGAL_REQUEST;
			sensebuffer->AdditionalSenseLength = 0x0A;
			sensebuffer->AdditionalSenseCode = 0x20;
			sensebuffer->Valid = 1;
			retvalue = ARCMSR_MESSAGE_FAIL;
		पूर्ण अन्यथा अणु
			pQbuffer = &acb->wqbuffer[acb->wqbuf_putIndex];
			cnt2end = ARCMSR_MAX_QBUFFER - acb->wqbuf_putIndex;
			अगर (user_len > cnt2end) अणु
				स_नकल(pQbuffer, pपंचांगpuserbuffer, cnt2end);
				pपंचांगpuserbuffer += cnt2end;
				user_len -= cnt2end;
				acb->wqbuf_putIndex = 0;
				pQbuffer = acb->wqbuffer;
			पूर्ण
			स_नकल(pQbuffer, pपंचांगpuserbuffer, user_len);
			acb->wqbuf_putIndex += user_len;
			acb->wqbuf_putIndex %= ARCMSR_MAX_QBUFFER;
			अगर (acb->acb_flags & ACB_F_MESSAGE_WQBUFFER_CLEARED) अणु
				acb->acb_flags &=
						~ACB_F_MESSAGE_WQBUFFER_CLEARED;
				arcmsr_ग_लिखो_ioctldata2iop(acb);
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&acb->wqbuffer_lock, flags);
		kमुक्त(ver_addr);
		अगर (acb->fw_flag == FW_DEADLOCK)
			pcmdmessagefld->cmdmessage.ReturnCode =
				ARCMSR_MESSAGE_RETURNCODE_BUS_HANG_ON;
		अन्यथा
			pcmdmessagefld->cmdmessage.ReturnCode =
				ARCMSR_MESSAGE_RETURNCODE_OK;
		अवरोध;
	पूर्ण
	हाल ARCMSR_MESSAGE_CLEAR_RQBUFFER: अणु
		uपूर्णांक8_t *pQbuffer = acb->rqbuffer;

		arcmsr_clear_iop2drv_rqueue_buffer(acb);
		spin_lock_irqsave(&acb->rqbuffer_lock, flags);
		acb->acb_flags |= ACB_F_MESSAGE_RQBUFFER_CLEARED;
		acb->rqbuf_getIndex = 0;
		acb->rqbuf_putIndex = 0;
		स_रखो(pQbuffer, 0, ARCMSR_MAX_QBUFFER);
		spin_unlock_irqrestore(&acb->rqbuffer_lock, flags);
		अगर (acb->fw_flag == FW_DEADLOCK)
			pcmdmessagefld->cmdmessage.ReturnCode =
				ARCMSR_MESSAGE_RETURNCODE_BUS_HANG_ON;
		अन्यथा
			pcmdmessagefld->cmdmessage.ReturnCode =
				ARCMSR_MESSAGE_RETURNCODE_OK;
		अवरोध;
	पूर्ण
	हाल ARCMSR_MESSAGE_CLEAR_WQBUFFER: अणु
		uपूर्णांक8_t *pQbuffer = acb->wqbuffer;
		spin_lock_irqsave(&acb->wqbuffer_lock, flags);
		acb->acb_flags |= (ACB_F_MESSAGE_WQBUFFER_CLEARED |
			ACB_F_MESSAGE_WQBUFFER_READED);
		acb->wqbuf_getIndex = 0;
		acb->wqbuf_putIndex = 0;
		स_रखो(pQbuffer, 0, ARCMSR_MAX_QBUFFER);
		spin_unlock_irqrestore(&acb->wqbuffer_lock, flags);
		अगर (acb->fw_flag == FW_DEADLOCK)
			pcmdmessagefld->cmdmessage.ReturnCode =
				ARCMSR_MESSAGE_RETURNCODE_BUS_HANG_ON;
		अन्यथा
			pcmdmessagefld->cmdmessage.ReturnCode =
				ARCMSR_MESSAGE_RETURNCODE_OK;
		अवरोध;
	पूर्ण
	हाल ARCMSR_MESSAGE_CLEAR_ALLQBUFFER: अणु
		uपूर्णांक8_t *pQbuffer;
		arcmsr_clear_iop2drv_rqueue_buffer(acb);
		spin_lock_irqsave(&acb->rqbuffer_lock, flags);
		acb->acb_flags |= ACB_F_MESSAGE_RQBUFFER_CLEARED;
		acb->rqbuf_getIndex = 0;
		acb->rqbuf_putIndex = 0;
		pQbuffer = acb->rqbuffer;
		स_रखो(pQbuffer, 0, माप(काष्ठा QBUFFER));
		spin_unlock_irqrestore(&acb->rqbuffer_lock, flags);
		spin_lock_irqsave(&acb->wqbuffer_lock, flags);
		acb->acb_flags |= (ACB_F_MESSAGE_WQBUFFER_CLEARED |
			ACB_F_MESSAGE_WQBUFFER_READED);
		acb->wqbuf_getIndex = 0;
		acb->wqbuf_putIndex = 0;
		pQbuffer = acb->wqbuffer;
		स_रखो(pQbuffer, 0, माप(काष्ठा QBUFFER));
		spin_unlock_irqrestore(&acb->wqbuffer_lock, flags);
		अगर (acb->fw_flag == FW_DEADLOCK)
			pcmdmessagefld->cmdmessage.ReturnCode =
				ARCMSR_MESSAGE_RETURNCODE_BUS_HANG_ON;
		अन्यथा
			pcmdmessagefld->cmdmessage.ReturnCode =
				ARCMSR_MESSAGE_RETURNCODE_OK;
		अवरोध;
	पूर्ण
	हाल ARCMSR_MESSAGE_RETURN_CODE_3F: अणु
		अगर (acb->fw_flag == FW_DEADLOCK)
			pcmdmessagefld->cmdmessage.ReturnCode =
				ARCMSR_MESSAGE_RETURNCODE_BUS_HANG_ON;
		अन्यथा
			pcmdmessagefld->cmdmessage.ReturnCode =
				ARCMSR_MESSAGE_RETURNCODE_3F;
		अवरोध;
	पूर्ण
	हाल ARCMSR_MESSAGE_SAY_HELLO: अणु
		पूर्णांक8_t *hello_string = "Hello! I am ARCMSR";
		अगर (acb->fw_flag == FW_DEADLOCK)
			pcmdmessagefld->cmdmessage.ReturnCode =
				ARCMSR_MESSAGE_RETURNCODE_BUS_HANG_ON;
		अन्यथा
			pcmdmessagefld->cmdmessage.ReturnCode =
				ARCMSR_MESSAGE_RETURNCODE_OK;
		स_नकल(pcmdmessagefld->messagedatabuffer,
			hello_string, (पूर्णांक16_t)म_माप(hello_string));
		अवरोध;
	पूर्ण
	हाल ARCMSR_MESSAGE_SAY_GOODBYE: अणु
		अगर (acb->fw_flag == FW_DEADLOCK)
			pcmdmessagefld->cmdmessage.ReturnCode =
				ARCMSR_MESSAGE_RETURNCODE_BUS_HANG_ON;
		अन्यथा
			pcmdmessagefld->cmdmessage.ReturnCode =
				ARCMSR_MESSAGE_RETURNCODE_OK;
		arcmsr_iop_parking(acb);
		अवरोध;
	पूर्ण
	हाल ARCMSR_MESSAGE_FLUSH_ADAPTER_CACHE: अणु
		अगर (acb->fw_flag == FW_DEADLOCK)
			pcmdmessagefld->cmdmessage.ReturnCode =
				ARCMSR_MESSAGE_RETURNCODE_BUS_HANG_ON;
		अन्यथा
			pcmdmessagefld->cmdmessage.ReturnCode =
				ARCMSR_MESSAGE_RETURNCODE_OK;
		arcmsr_flush_adapter_cache(acb);
		अवरोध;
	पूर्ण
	शेष:
		retvalue = ARCMSR_MESSAGE_FAIL;
		pr_info("%s: unknown controlcode!\n", __func__);
	पूर्ण
message_out:
	अगर (use_sg) अणु
		काष्ठा scatterlist *sg = scsi_sglist(cmd);
		kunmap_atomic(buffer - sg->offset);
	पूर्ण
	वापस retvalue;
पूर्ण

अटल काष्ठा CommandControlBlock *arcmsr_get_मुक्तccb(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा list_head *head;
	काष्ठा CommandControlBlock *ccb = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&acb->ccblist_lock, flags);
	head = &acb->ccb_मुक्त_list;
	अगर (!list_empty(head)) अणु
		ccb = list_entry(head->next, काष्ठा CommandControlBlock, list);
		list_del_init(&ccb->list);
	पूर्णअन्यथाअणु
		spin_unlock_irqrestore(&acb->ccblist_lock, flags);
		वापस शून्य;
	पूर्ण
	spin_unlock_irqrestore(&acb->ccblist_lock, flags);
	वापस ccb;
पूर्ण

अटल व्योम arcmsr_handle_भव_command(काष्ठा AdapterControlBlock *acb,
		काष्ठा scsi_cmnd *cmd)
अणु
	चयन (cmd->cmnd[0]) अणु
	हाल INQUIRY: अणु
		अचिन्हित अक्षर inqdata[36];
		अक्षर *buffer;
		काष्ठा scatterlist *sg;

		अगर (cmd->device->lun) अणु
			cmd->result = (DID_TIME_OUT << 16);
			cmd->scsi_करोne(cmd);
			वापस;
		पूर्ण
		inqdata[0] = TYPE_PROCESSOR;
		/* Periph Qualअगरier & Periph Dev Type */
		inqdata[1] = 0;
		/* rem media bit & Dev Type Modअगरier */
		inqdata[2] = 0;
		/* ISO, ECMA, & ANSI versions */
		inqdata[4] = 31;
		/* length of additional data */
		स_नकल(&inqdata[8], "Areca   ", 8);
		/* Venकरोr Identअगरication */
		स_नकल(&inqdata[16], "RAID controller ", 16);
		/* Product Identअगरication */
		स_नकल(&inqdata[32], "R001", 4); /* Product Revision */

		sg = scsi_sglist(cmd);
		buffer = kmap_atomic(sg_page(sg)) + sg->offset;

		स_नकल(buffer, inqdata, माप(inqdata));
		sg = scsi_sglist(cmd);
		kunmap_atomic(buffer - sg->offset);

		cmd->scsi_करोne(cmd);
	पूर्ण
	अवरोध;
	हाल WRITE_BUFFER:
	हाल READ_BUFFER: अणु
		अगर (arcmsr_iop_message_xfer(acb, cmd))
			cmd->result = (DID_ERROR << 16);
		cmd->scsi_करोne(cmd);
	पूर्ण
	अवरोध;
	शेष:
		cmd->scsi_करोne(cmd);
	पूर्ण
पूर्ण

अटल पूर्णांक arcmsr_queue_command_lck(काष्ठा scsi_cmnd *cmd,
	व्योम (* करोne)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा Scsi_Host *host = cmd->device->host;
	काष्ठा AdapterControlBlock *acb = (काष्ठा AdapterControlBlock *) host->hostdata;
	काष्ठा CommandControlBlock *ccb;
	पूर्णांक target = cmd->device->id;

	अगर (acb->acb_flags & ACB_F_ADAPTER_REMOVED) अणु
		cmd->result = (DID_NO_CONNECT << 16);
		cmd->scsi_करोne(cmd);
		वापस 0;
	पूर्ण
	cmd->scsi_करोne = करोne;
	cmd->host_scribble = शून्य;
	cmd->result = 0;
	अगर (target == 16) अणु
		/* भव device क्रम iop message transfer */
		arcmsr_handle_भव_command(acb, cmd);
		वापस 0;
	पूर्ण
	ccb = arcmsr_get_मुक्तccb(acb);
	अगर (!ccb)
		वापस SCSI_MLQUEUE_HOST_BUSY;
	अगर (arcmsr_build_ccb( acb, ccb, cmd ) == FAILED) अणु
		cmd->result = (DID_ERROR << 16) | (RESERVATION_CONFLICT << 1);
		cmd->scsi_करोne(cmd);
		वापस 0;
	पूर्ण
	arcmsr_post_ccb(acb, ccb);
	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(arcmsr_queue_command)

अटल पूर्णांक arcmsr_slave_config(काष्ठा scsi_device *sdev)
अणु
	अचिन्हित पूर्णांक	dev_समयout;

	dev_समयout = sdev->request_queue->rq_समयout;
	अगर ((cmd_समयout > 0) && ((cmd_समयout * HZ) > dev_समयout))
		blk_queue_rq_समयout(sdev->request_queue, cmd_समयout * HZ);
	वापस 0;
पूर्ण

अटल व्योम arcmsr_get_adapter_config(काष्ठा AdapterControlBlock *pACB, uपूर्णांक32_t *rwbuffer)
अणु
	पूर्णांक count;
	uपूर्णांक32_t *acb_firm_model = (uपूर्णांक32_t *)pACB->firm_model;
	uपूर्णांक32_t *acb_firm_version = (uपूर्णांक32_t *)pACB->firm_version;
	uपूर्णांक32_t *acb_device_map = (uपूर्णांक32_t *)pACB->device_map;
	uपूर्णांक32_t *firm_model = &rwbuffer[15];
	uपूर्णांक32_t *firm_version = &rwbuffer[17];
	uपूर्णांक32_t *device_map = &rwbuffer[21];

	count = 2;
	जबतक (count) अणु
		*acb_firm_model = पढ़ोl(firm_model);
		acb_firm_model++;
		firm_model++;
		count--;
	पूर्ण
	count = 4;
	जबतक (count) अणु
		*acb_firm_version = पढ़ोl(firm_version);
		acb_firm_version++;
		firm_version++;
		count--;
	पूर्ण
	count = 4;
	जबतक (count) अणु
		*acb_device_map = पढ़ोl(device_map);
		acb_device_map++;
		device_map++;
		count--;
	पूर्ण
	pACB->signature = पढ़ोl(&rwbuffer[0]);
	pACB->firm_request_len = पढ़ोl(&rwbuffer[1]);
	pACB->firm_numbers_queue = पढ़ोl(&rwbuffer[2]);
	pACB->firm_sdram_size = पढ़ोl(&rwbuffer[3]);
	pACB->firm_hd_channels = पढ़ोl(&rwbuffer[4]);
	pACB->firm_cfg_version = पढ़ोl(&rwbuffer[25]);
	pr_notice("Areca RAID Controller%d: Model %s, F/W %s\n",
		pACB->host->host_no,
		pACB->firm_model,
		pACB->firm_version);
पूर्ण

अटल bool arcmsr_hbaA_get_config(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;

	arcmsr_रुको_firmware_पढ़ोy(acb);
	ग_लिखोl(ARCMSR_INBOUND_MESG0_GET_CONFIG, &reg->inbound_msgaddr0);
	अगर (!arcmsr_hbaA_रुको_msgपूर्णांक_पढ़ोy(acb)) अणु
		prपूर्णांकk(KERN_NOTICE "arcmsr%d: रुको 'get adapter firmware \
			miscellaneous data' समयout \न", acb->host->host_no);
		वापस false;
	पूर्ण
	arcmsr_get_adapter_config(acb, reg->message_rwbuffer);
	वापस true;
पूर्ण
अटल bool arcmsr_hbaB_get_config(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा MessageUnit_B *reg = acb->pmuB;

	arcmsr_रुको_firmware_पढ़ोy(acb);
	ग_लिखोl(ARCMSR_MESSAGE_START_DRIVER_MODE, reg->drv2iop_करोorbell);
	अगर (!arcmsr_hbaB_रुको_msgपूर्णांक_पढ़ोy(acb)) अणु
		prपूर्णांकk(KERN_ERR "arcmsr%d: can't set driver mode.\n", acb->host->host_no);
		वापस false;
	पूर्ण
	ग_लिखोl(ARCMSR_MESSAGE_GET_CONFIG, reg->drv2iop_करोorbell);
	अगर (!arcmsr_hbaB_रुको_msgपूर्णांक_पढ़ोy(acb)) अणु
		prपूर्णांकk(KERN_NOTICE "arcmsr%d: रुको 'get adapter firmware \
			miscellaneous data' समयout \न", acb->host->host_no);
		वापस false;
	पूर्ण
	arcmsr_get_adapter_config(acb, reg->message_rwbuffer);
	वापस true;
पूर्ण

अटल bool arcmsr_hbaC_get_config(काष्ठा AdapterControlBlock *pACB)
अणु
	uपूर्णांक32_t पूर्णांकmask_org;
	काष्ठा MessageUnit_C __iomem *reg = pACB->pmuC;

	/* disable all outbound पूर्णांकerrupt */
	पूर्णांकmask_org = पढ़ोl(&reg->host_पूर्णांक_mask); /* disable outbound message0 पूर्णांक */
	ग_लिखोl(पूर्णांकmask_org|ARCMSR_HBCMU_ALL_INTMASKENABLE, &reg->host_पूर्णांक_mask);
	/* रुको firmware पढ़ोy */
	arcmsr_रुको_firmware_पढ़ोy(pACB);
	/* post "get config" inकाष्ठाion */
	ग_लिखोl(ARCMSR_INBOUND_MESG0_GET_CONFIG, &reg->inbound_msgaddr0);
	ग_लिखोl(ARCMSR_HBCMU_DRV2IOP_MESSAGE_CMD_DONE, &reg->inbound_करोorbell);
	/* रुको message पढ़ोy */
	अगर (!arcmsr_hbaC_रुको_msgपूर्णांक_पढ़ोy(pACB)) अणु
		prपूर्णांकk(KERN_NOTICE "arcmsr%d: रुको 'get adapter firmware \
			miscellaneous data' समयout \न", pACB->host->host_no);
		वापस false;
	पूर्ण
	arcmsr_get_adapter_config(pACB, reg->msgcode_rwbuffer);
	वापस true;
पूर्ण

अटल bool arcmsr_hbaD_get_config(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा MessageUnit_D *reg = acb->pmuD;

	अगर (पढ़ोl(acb->pmuD->outbound_करोorbell) &
		ARCMSR_ARC1214_IOP2DRV_MESSAGE_CMD_DONE) अणु
		ग_लिखोl(ARCMSR_ARC1214_IOP2DRV_MESSAGE_CMD_DONE,
			acb->pmuD->outbound_करोorbell);/*clear पूर्णांकerrupt*/
	पूर्ण
	arcmsr_रुको_firmware_पढ़ोy(acb);
	/* post "get config" inकाष्ठाion */
	ग_लिखोl(ARCMSR_INBOUND_MESG0_GET_CONFIG, reg->inbound_msgaddr0);
	/* रुको message पढ़ोy */
	अगर (!arcmsr_hbaD_रुको_msgपूर्णांक_पढ़ोy(acb)) अणु
		pr_notice("arcmsr%d: wait get adapter firmware "
			"miscellaneous data timeout\n", acb->host->host_no);
		वापस false;
	पूर्ण
	arcmsr_get_adapter_config(acb, reg->msgcode_rwbuffer);
	वापस true;
पूर्ण

अटल bool arcmsr_hbaE_get_config(काष्ठा AdapterControlBlock *pACB)
अणु
	काष्ठा MessageUnit_E __iomem *reg = pACB->pmuE;
	uपूर्णांक32_t पूर्णांकmask_org;

	/* disable all outbound पूर्णांकerrupt */
	पूर्णांकmask_org = पढ़ोl(&reg->host_पूर्णांक_mask); /* disable outbound message0 पूर्णांक */
	ग_लिखोl(पूर्णांकmask_org | ARCMSR_HBEMU_ALL_INTMASKENABLE, &reg->host_पूर्णांक_mask);
	/* रुको firmware पढ़ोy */
	arcmsr_रुको_firmware_पढ़ोy(pACB);
	mdelay(20);
	/* post "get config" inकाष्ठाion */
	ग_लिखोl(ARCMSR_INBOUND_MESG0_GET_CONFIG, &reg->inbound_msgaddr0);

	pACB->out_करोorbell ^= ARCMSR_HBEMU_DRV2IOP_MESSAGE_CMD_DONE;
	ग_लिखोl(pACB->out_करोorbell, &reg->iobound_करोorbell);
	/* रुको message पढ़ोy */
	अगर (!arcmsr_hbaE_रुको_msgपूर्णांक_पढ़ोy(pACB)) अणु
		pr_notice("arcmsr%d: wait get adapter firmware "
			"miscellaneous data timeout\n", pACB->host->host_no);
		वापस false;
	पूर्ण
	arcmsr_get_adapter_config(pACB, reg->msgcode_rwbuffer);
	वापस true;
पूर्ण

अटल bool arcmsr_hbaF_get_config(काष्ठा AdapterControlBlock *pACB)
अणु
	काष्ठा MessageUnit_F __iomem *reg = pACB->pmuF;
	uपूर्णांक32_t पूर्णांकmask_org;

	/* disable all outbound पूर्णांकerrupt */
	पूर्णांकmask_org = पढ़ोl(&reg->host_पूर्णांक_mask); /* disable outbound message0 पूर्णांक */
	ग_लिखोl(पूर्णांकmask_org | ARCMSR_HBEMU_ALL_INTMASKENABLE, &reg->host_पूर्णांक_mask);
	/* रुको firmware पढ़ोy */
	arcmsr_रुको_firmware_पढ़ोy(pACB);
	/* post "get config" inकाष्ठाion */
	ग_लिखोl(ARCMSR_INBOUND_MESG0_GET_CONFIG, &reg->inbound_msgaddr0);

	pACB->out_करोorbell ^= ARCMSR_HBEMU_DRV2IOP_MESSAGE_CMD_DONE;
	ग_लिखोl(pACB->out_करोorbell, &reg->iobound_करोorbell);
	/* रुको message पढ़ोy */
	अगर (!arcmsr_hbaE_रुको_msgपूर्णांक_पढ़ोy(pACB)) अणु
		pr_notice("arcmsr%d: wait get adapter firmware miscellaneous data timeout\n",
			  pACB->host->host_no);
		वापस false;
	पूर्ण
	arcmsr_get_adapter_config(pACB, pACB->msgcode_rwbuffer);
	वापस true;
पूर्ण

अटल bool arcmsr_get_firmware_spec(काष्ठा AdapterControlBlock *acb)
अणु
	bool rtn = false;

	चयन (acb->adapter_type) अणु
	हाल ACB_ADAPTER_TYPE_A:
		rtn = arcmsr_hbaA_get_config(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_B:
		rtn = arcmsr_hbaB_get_config(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_C:
		rtn = arcmsr_hbaC_get_config(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_D:
		rtn = arcmsr_hbaD_get_config(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_E:
		rtn = arcmsr_hbaE_get_config(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_F:
		rtn = arcmsr_hbaF_get_config(acb);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	acb->maxOutstanding = acb->firm_numbers_queue - 1;
	अगर (acb->host->can_queue >= acb->firm_numbers_queue)
		acb->host->can_queue = acb->maxOutstanding;
	अन्यथा
		acb->maxOutstanding = acb->host->can_queue;
	acb->maxFreeCCB = acb->host->can_queue;
	अगर (acb->maxFreeCCB < ARCMSR_MAX_FREECCB_NUM)
		acb->maxFreeCCB += 64;
	वापस rtn;
पूर्ण

अटल पूर्णांक arcmsr_hbaA_polling_ccbकरोne(काष्ठा AdapterControlBlock *acb,
	काष्ठा CommandControlBlock *poll_ccb)
अणु
	काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;
	काष्ठा CommandControlBlock *ccb;
	काष्ठा ARCMSR_CDB *arcmsr_cdb;
	uपूर्णांक32_t flag_ccb, outbound_पूर्णांकstatus, poll_ccb_करोne = 0, poll_count = 0;
	पूर्णांक rtn;
	bool error;
	अचिन्हित दीर्घ ccb_cdb_phy;

polling_hba_ccb_retry:
	poll_count++;
	outbound_पूर्णांकstatus = पढ़ोl(&reg->outbound_पूर्णांकstatus) & acb->outbound_पूर्णांक_enable;
	ग_लिखोl(outbound_पूर्णांकstatus, &reg->outbound_पूर्णांकstatus);/*clear पूर्णांकerrupt*/
	जबतक (1) अणु
		अगर ((flag_ccb = पढ़ोl(&reg->outbound_queueport)) == 0xFFFFFFFF) अणु
			अगर (poll_ccb_करोne)अणु
				rtn = SUCCESS;
				अवरोध;
			पूर्णअन्यथा अणु
				msleep(25);
				अगर (poll_count > 100)अणु
					rtn = FAILED;
					अवरोध;
				पूर्ण
				जाओ polling_hba_ccb_retry;
			पूर्ण
		पूर्ण
		ccb_cdb_phy = (flag_ccb << 5) & 0xffffffff;
		अगर (acb->cdb_phyadd_hipart)
			ccb_cdb_phy = ccb_cdb_phy | acb->cdb_phyadd_hipart;
		arcmsr_cdb = (काष्ठा ARCMSR_CDB *)(acb->vir2phy_offset + ccb_cdb_phy);
		ccb = container_of(arcmsr_cdb, काष्ठा CommandControlBlock, arcmsr_cdb);
		poll_ccb_करोne |= (ccb == poll_ccb) ? 1 : 0;
		अगर ((ccb->acb != acb) || (ccb->startकरोne != ARCMSR_CCB_START)) अणु
			अगर ((ccb->startकरोne == ARCMSR_CCB_ABORTED) || (ccb == poll_ccb)) अणु
				prपूर्णांकk(KERN_NOTICE "arcmsr%d: scsi id = %d lun = %d ccb = '0x%p'"
					" poll command abort successfully \n"
					, acb->host->host_no
					, ccb->pcmd->device->id
					, (u32)ccb->pcmd->device->lun
					, ccb);
				ccb->pcmd->result = DID_ABORT << 16;
				arcmsr_ccb_complete(ccb);
				जारी;
			पूर्ण
			prपूर्णांकk(KERN_NOTICE "arcmsr%d: polling get an illegal ccb"
				" command done ccb = '0x%p'"
				"ccboutstandingcount = %d \n"
				, acb->host->host_no
				, ccb
				, atomic_पढ़ो(&acb->ccboutstandingcount));
			जारी;
		पूर्ण
		error = (flag_ccb & ARCMSR_CCBREPLY_FLAG_ERROR_MODE0) ? true : false;
		arcmsr_report_ccb_state(acb, ccb, error);
	पूर्ण
	वापस rtn;
पूर्ण

अटल पूर्णांक arcmsr_hbaB_polling_ccbकरोne(काष्ठा AdapterControlBlock *acb,
					काष्ठा CommandControlBlock *poll_ccb)
अणु
	काष्ठा MessageUnit_B *reg = acb->pmuB;
	काष्ठा ARCMSR_CDB *arcmsr_cdb;
	काष्ठा CommandControlBlock *ccb;
	uपूर्णांक32_t flag_ccb, poll_ccb_करोne = 0, poll_count = 0;
	पूर्णांक index, rtn;
	bool error;
	अचिन्हित दीर्घ ccb_cdb_phy;

polling_hbb_ccb_retry:
	poll_count++;
	/* clear करोorbell पूर्णांकerrupt */
	ग_लिखोl(ARCMSR_DOORBELL_INT_CLEAR_PATTERN, reg->iop2drv_करोorbell);
	जबतक(1)अणु
		index = reg->करोneq_index;
		flag_ccb = reg->करोne_qbuffer[index];
		अगर (flag_ccb == 0) अणु
			अगर (poll_ccb_करोne)अणु
				rtn = SUCCESS;
				अवरोध;
			पूर्णअन्यथा अणु
				msleep(25);
				अगर (poll_count > 100)अणु
					rtn = FAILED;
					अवरोध;
				पूर्ण
				जाओ polling_hbb_ccb_retry;
			पूर्ण
		पूर्ण
		reg->करोne_qbuffer[index] = 0;
		index++;
		/*अगर last index number set it to 0 */
		index %= ARCMSR_MAX_HBB_POSTQUEUE;
		reg->करोneq_index = index;
		/* check अगर command करोne with no error*/
		ccb_cdb_phy = (flag_ccb << 5) & 0xffffffff;
		अगर (acb->cdb_phyadd_hipart)
			ccb_cdb_phy = ccb_cdb_phy | acb->cdb_phyadd_hipart;
		arcmsr_cdb = (काष्ठा ARCMSR_CDB *)(acb->vir2phy_offset + ccb_cdb_phy);
		ccb = container_of(arcmsr_cdb, काष्ठा CommandControlBlock, arcmsr_cdb);
		poll_ccb_करोne |= (ccb == poll_ccb) ? 1 : 0;
		अगर ((ccb->acb != acb) || (ccb->startकरोne != ARCMSR_CCB_START)) अणु
			अगर ((ccb->startकरोne == ARCMSR_CCB_ABORTED) || (ccb == poll_ccb)) अणु
				prपूर्णांकk(KERN_NOTICE "arcmsr%d: scsi id = %d lun = %d ccb = '0x%p'"
					" poll command abort successfully \n"
					,acb->host->host_no
					,ccb->pcmd->device->id
					,(u32)ccb->pcmd->device->lun
					,ccb);
				ccb->pcmd->result = DID_ABORT << 16;
				arcmsr_ccb_complete(ccb);
				जारी;
			पूर्ण
			prपूर्णांकk(KERN_NOTICE "arcmsr%d: polling get an illegal ccb"
				" command done ccb = '0x%p'"
				"ccboutstandingcount = %d \n"
				, acb->host->host_no
				, ccb
				, atomic_पढ़ो(&acb->ccboutstandingcount));
			जारी;
		पूर्ण 
		error = (flag_ccb & ARCMSR_CCBREPLY_FLAG_ERROR_MODE0) ? true : false;
		arcmsr_report_ccb_state(acb, ccb, error);
	पूर्ण
	वापस rtn;
पूर्ण

अटल पूर्णांक arcmsr_hbaC_polling_ccbकरोne(काष्ठा AdapterControlBlock *acb,
		काष्ठा CommandControlBlock *poll_ccb)
अणु
	काष्ठा MessageUnit_C __iomem *reg = acb->pmuC;
	uपूर्णांक32_t flag_ccb;
	काष्ठा ARCMSR_CDB *arcmsr_cdb;
	bool error;
	काष्ठा CommandControlBlock *pCCB;
	uपूर्णांक32_t poll_ccb_करोne = 0, poll_count = 0;
	पूर्णांक rtn;
	अचिन्हित दीर्घ ccb_cdb_phy;

polling_hbc_ccb_retry:
	poll_count++;
	जबतक (1) अणु
		अगर ((पढ़ोl(&reg->host_पूर्णांक_status) & ARCMSR_HBCMU_OUTBOUND_POSTQUEUE_ISR) == 0) अणु
			अगर (poll_ccb_करोne) अणु
				rtn = SUCCESS;
				अवरोध;
			पूर्ण अन्यथा अणु
				msleep(25);
				अगर (poll_count > 100) अणु
					rtn = FAILED;
					अवरोध;
				पूर्ण
				जाओ polling_hbc_ccb_retry;
			पूर्ण
		पूर्ण
		flag_ccb = पढ़ोl(&reg->outbound_queueport_low);
		ccb_cdb_phy = (flag_ccb & 0xFFFFFFF0);
		अगर (acb->cdb_phyadd_hipart)
			ccb_cdb_phy = ccb_cdb_phy | acb->cdb_phyadd_hipart;
		arcmsr_cdb = (काष्ठा ARCMSR_CDB *)(acb->vir2phy_offset + ccb_cdb_phy);
		pCCB = container_of(arcmsr_cdb, काष्ठा CommandControlBlock, arcmsr_cdb);
		poll_ccb_करोne |= (pCCB == poll_ccb) ? 1 : 0;
		/* check अगरcommand करोne with no error*/
		अगर ((pCCB->acb != acb) || (pCCB->startकरोne != ARCMSR_CCB_START)) अणु
			अगर (pCCB->startकरोne == ARCMSR_CCB_ABORTED) अणु
				prपूर्णांकk(KERN_NOTICE "arcmsr%d: scsi id = %d lun = %d ccb = '0x%p'"
					" poll command abort successfully \n"
					, acb->host->host_no
					, pCCB->pcmd->device->id
					, (u32)pCCB->pcmd->device->lun
					, pCCB);
				pCCB->pcmd->result = DID_ABORT << 16;
				arcmsr_ccb_complete(pCCB);
				जारी;
			पूर्ण
			prपूर्णांकk(KERN_NOTICE "arcmsr%d: polling get an illegal ccb"
				" command done ccb = '0x%p'"
				"ccboutstandingcount = %d \n"
				, acb->host->host_no
				, pCCB
				, atomic_पढ़ो(&acb->ccboutstandingcount));
			जारी;
		पूर्ण
		error = (flag_ccb & ARCMSR_CCBREPLY_FLAG_ERROR_MODE1) ? true : false;
		arcmsr_report_ccb_state(acb, pCCB, error);
	पूर्ण
	वापस rtn;
पूर्ण

अटल पूर्णांक arcmsr_hbaD_polling_ccbकरोne(काष्ठा AdapterControlBlock *acb,
				काष्ठा CommandControlBlock *poll_ccb)
अणु
	bool error;
	uपूर्णांक32_t poll_ccb_करोne = 0, poll_count = 0, flag_ccb;
	पूर्णांक rtn, करोneq_index, index_stripped, outbound_ग_लिखो_poपूर्णांकer, toggle;
	अचिन्हित दीर्घ flags, ccb_cdb_phy;
	काष्ठा ARCMSR_CDB *arcmsr_cdb;
	काष्ठा CommandControlBlock *pCCB;
	काष्ठा MessageUnit_D *pmu = acb->pmuD;

polling_hbaD_ccb_retry:
	poll_count++;
	जबतक (1) अणु
		spin_lock_irqsave(&acb->करोneq_lock, flags);
		outbound_ग_लिखो_poपूर्णांकer = pmu->करोne_qbuffer[0].addressLow + 1;
		करोneq_index = pmu->करोneq_index;
		अगर ((outbound_ग_लिखो_poपूर्णांकer & 0xFFF) == (करोneq_index & 0xFFF)) अणु
			spin_unlock_irqrestore(&acb->करोneq_lock, flags);
			अगर (poll_ccb_करोne) अणु
				rtn = SUCCESS;
				अवरोध;
			पूर्ण अन्यथा अणु
				msleep(25);
				अगर (poll_count > 40) अणु
					rtn = FAILED;
					अवरोध;
				पूर्ण
				जाओ polling_hbaD_ccb_retry;
			पूर्ण
		पूर्ण
		toggle = करोneq_index & 0x4000;
		index_stripped = (करोneq_index & 0xFFF) + 1;
		index_stripped %= ARCMSR_MAX_ARC1214_DONEQUEUE;
		pmu->करोneq_index = index_stripped ? (index_stripped | toggle) :
				((toggle ^ 0x4000) + 1);
		करोneq_index = pmu->करोneq_index;
		spin_unlock_irqrestore(&acb->करोneq_lock, flags);
		flag_ccb = pmu->करोne_qbuffer[करोneq_index & 0xFFF].addressLow;
		ccb_cdb_phy = (flag_ccb & 0xFFFFFFF0);
		अगर (acb->cdb_phyadd_hipart)
			ccb_cdb_phy = ccb_cdb_phy | acb->cdb_phyadd_hipart;
		arcmsr_cdb = (काष्ठा ARCMSR_CDB *)(acb->vir2phy_offset +
			ccb_cdb_phy);
		pCCB = container_of(arcmsr_cdb, काष्ठा CommandControlBlock,
			arcmsr_cdb);
		poll_ccb_करोne |= (pCCB == poll_ccb) ? 1 : 0;
		अगर ((pCCB->acb != acb) ||
			(pCCB->startकरोne != ARCMSR_CCB_START)) अणु
			अगर (pCCB->startकरोne == ARCMSR_CCB_ABORTED) अणु
				pr_notice("arcmsr%d: scsi id = %d "
					"lun = %d ccb = '0x%p' poll command "
					"abort successfully\n"
					, acb->host->host_no
					, pCCB->pcmd->device->id
					, (u32)pCCB->pcmd->device->lun
					, pCCB);
				pCCB->pcmd->result = DID_ABORT << 16;
				arcmsr_ccb_complete(pCCB);
				जारी;
			पूर्ण
			pr_notice("arcmsr%d: polling an illegal "
				"ccb command done ccb = '0x%p' "
				"ccboutstandingcount = %d\n"
				, acb->host->host_no
				, pCCB
				, atomic_पढ़ो(&acb->ccboutstandingcount));
			जारी;
		पूर्ण
		error = (flag_ccb & ARCMSR_CCBREPLY_FLAG_ERROR_MODE1)
			? true : false;
		arcmsr_report_ccb_state(acb, pCCB, error);
	पूर्ण
	वापस rtn;
पूर्ण

अटल पूर्णांक arcmsr_hbaE_polling_ccbकरोne(काष्ठा AdapterControlBlock *acb,
				काष्ठा CommandControlBlock *poll_ccb)
अणु
	bool error;
	uपूर्णांक32_t poll_ccb_करोne = 0, poll_count = 0, करोneq_index;
	uपूर्णांक16_t cmdSMID;
	अचिन्हित दीर्घ flags;
	पूर्णांक rtn;
	काष्ठा CommandControlBlock *pCCB;
	काष्ठा MessageUnit_E __iomem *reg = acb->pmuE;

	polling_hbaC_ccb_retry:
	poll_count++;
	जबतक (1) अणु
		spin_lock_irqsave(&acb->करोneq_lock, flags);
		करोneq_index = acb->करोneq_index;
		अगर ((पढ़ोl(&reg->reply_post_producer_index) & 0xFFFF) ==
				करोneq_index) अणु
			spin_unlock_irqrestore(&acb->करोneq_lock, flags);
			अगर (poll_ccb_करोne) अणु
				rtn = SUCCESS;
				अवरोध;
			पूर्ण अन्यथा अणु
				msleep(25);
				अगर (poll_count > 40) अणु
					rtn = FAILED;
					अवरोध;
				पूर्ण
				जाओ polling_hbaC_ccb_retry;
			पूर्ण
		पूर्ण
		cmdSMID = acb->pCompletionQ[करोneq_index].cmdSMID;
		करोneq_index++;
		अगर (करोneq_index >= acb->completionQ_entry)
			करोneq_index = 0;
		acb->करोneq_index = करोneq_index;
		spin_unlock_irqrestore(&acb->करोneq_lock, flags);
		pCCB = acb->pccb_pool[cmdSMID];
		poll_ccb_करोne |= (pCCB == poll_ccb) ? 1 : 0;
		/* check अगर command करोne with no error*/
		अगर ((pCCB->acb != acb) || (pCCB->startकरोne != ARCMSR_CCB_START)) अणु
			अगर (pCCB->startकरोne == ARCMSR_CCB_ABORTED) अणु
				pr_notice("arcmsr%d: scsi id = %d "
					"lun = %d ccb = '0x%p' poll command "
					"abort successfully\n"
					, acb->host->host_no
					, pCCB->pcmd->device->id
					, (u32)pCCB->pcmd->device->lun
					, pCCB);
				pCCB->pcmd->result = DID_ABORT << 16;
				arcmsr_ccb_complete(pCCB);
				जारी;
			पूर्ण
			pr_notice("arcmsr%d: polling an illegal "
				"ccb command done ccb = '0x%p' "
				"ccboutstandingcount = %d\n"
				, acb->host->host_no
				, pCCB
				, atomic_पढ़ो(&acb->ccboutstandingcount));
			जारी;
		पूर्ण
		error = (acb->pCompletionQ[करोneq_index].cmdFlag &
			ARCMSR_CCBREPLY_FLAG_ERROR_MODE1) ? true : false;
		arcmsr_report_ccb_state(acb, pCCB, error);
	पूर्ण
	ग_लिखोl(करोneq_index, &reg->reply_post_consumer_index);
	वापस rtn;
पूर्ण

अटल पूर्णांक arcmsr_polling_ccbकरोne(काष्ठा AdapterControlBlock *acb,
					काष्ठा CommandControlBlock *poll_ccb)
अणु
	पूर्णांक rtn = 0;
	चयन (acb->adapter_type) अणु

	हाल ACB_ADAPTER_TYPE_A:
		rtn = arcmsr_hbaA_polling_ccbकरोne(acb, poll_ccb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_B:
		rtn = arcmsr_hbaB_polling_ccbकरोne(acb, poll_ccb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_C:
		rtn = arcmsr_hbaC_polling_ccbकरोne(acb, poll_ccb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_D:
		rtn = arcmsr_hbaD_polling_ccbकरोne(acb, poll_ccb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_E:
	हाल ACB_ADAPTER_TYPE_F:
		rtn = arcmsr_hbaE_polling_ccbकरोne(acb, poll_ccb);
		अवरोध;
	पूर्ण
	वापस rtn;
पूर्ण

अटल व्योम arcmsr_set_iop_dateसमय(काष्ठा समयr_list *t)
अणु
	काष्ठा AdapterControlBlock *pacb = from_समयr(pacb, t, refresh_समयr);
	अचिन्हित पूर्णांक next_समय;
	काष्ठा पंचांग पंचांग;

	जोड़ अणु
		काष्ठा	अणु
		uपूर्णांक16_t	signature;
		uपूर्णांक8_t		year;
		uपूर्णांक8_t		month;
		uपूर्णांक8_t		date;
		uपूर्णांक8_t		hour;
		uपूर्णांक8_t		minute;
		uपूर्णांक8_t		second;
		पूर्ण a;
		काष्ठा	अणु
		uपूर्णांक32_t	msg_समय[2];
		पूर्ण b;
	पूर्ण dateसमय;

	समय64_to_पंचांग(kसमय_get_real_seconds(), -sys_tz.tz_minuteswest * 60, &पंचांग);

	dateसमय.a.signature = 0x55AA;
	dateसमय.a.year = पंचांग.पंचांग_year - 100; /* base 2000 instead of 1900 */
	dateसमय.a.month = पंचांग.पंचांग_mon;
	dateसमय.a.date = पंचांग.पंचांग_mday;
	dateसमय.a.hour = पंचांग.पंचांग_hour;
	dateसमय.a.minute = पंचांग.पंचांग_min;
	dateसमय.a.second = पंचांग.पंचांग_sec;

	चयन (pacb->adapter_type) अणु
		हाल ACB_ADAPTER_TYPE_A: अणु
			काष्ठा MessageUnit_A __iomem *reg = pacb->pmuA;
			ग_लिखोl(dateसमय.b.msg_समय[0], &reg->message_rwbuffer[0]);
			ग_लिखोl(dateसमय.b.msg_समय[1], &reg->message_rwbuffer[1]);
			ग_लिखोl(ARCMSR_INBOUND_MESG0_SYNC_TIMER, &reg->inbound_msgaddr0);
			अवरोध;
		पूर्ण
		हाल ACB_ADAPTER_TYPE_B: अणु
			uपूर्णांक32_t __iomem *rwbuffer;
			काष्ठा MessageUnit_B *reg = pacb->pmuB;
			rwbuffer = reg->message_rwbuffer;
			ग_लिखोl(dateसमय.b.msg_समय[0], rwbuffer++);
			ग_लिखोl(dateसमय.b.msg_समय[1], rwbuffer++);
			ग_लिखोl(ARCMSR_MESSAGE_SYNC_TIMER, reg->drv2iop_करोorbell);
			अवरोध;
		पूर्ण
		हाल ACB_ADAPTER_TYPE_C: अणु
			काष्ठा MessageUnit_C __iomem *reg = pacb->pmuC;
			ग_लिखोl(dateसमय.b.msg_समय[0], &reg->msgcode_rwbuffer[0]);
			ग_लिखोl(dateसमय.b.msg_समय[1], &reg->msgcode_rwbuffer[1]);
			ग_लिखोl(ARCMSR_INBOUND_MESG0_SYNC_TIMER, &reg->inbound_msgaddr0);
			ग_लिखोl(ARCMSR_HBCMU_DRV2IOP_MESSAGE_CMD_DONE, &reg->inbound_करोorbell);
			अवरोध;
		पूर्ण
		हाल ACB_ADAPTER_TYPE_D: अणु
			uपूर्णांक32_t __iomem *rwbuffer;
			काष्ठा MessageUnit_D *reg = pacb->pmuD;
			rwbuffer = reg->msgcode_rwbuffer;
			ग_लिखोl(dateसमय.b.msg_समय[0], rwbuffer++);
			ग_लिखोl(dateसमय.b.msg_समय[1], rwbuffer++);
			ग_लिखोl(ARCMSR_INBOUND_MESG0_SYNC_TIMER, reg->inbound_msgaddr0);
			अवरोध;
		पूर्ण
		हाल ACB_ADAPTER_TYPE_E: अणु
			काष्ठा MessageUnit_E __iomem *reg = pacb->pmuE;
			ग_लिखोl(dateसमय.b.msg_समय[0], &reg->msgcode_rwbuffer[0]);
			ग_लिखोl(dateसमय.b.msg_समय[1], &reg->msgcode_rwbuffer[1]);
			ग_लिखोl(ARCMSR_INBOUND_MESG0_SYNC_TIMER, &reg->inbound_msgaddr0);
			pacb->out_करोorbell ^= ARCMSR_HBEMU_DRV2IOP_MESSAGE_CMD_DONE;
			ग_लिखोl(pacb->out_करोorbell, &reg->iobound_करोorbell);
			अवरोध;
		पूर्ण
		हाल ACB_ADAPTER_TYPE_F: अणु
			काष्ठा MessageUnit_F __iomem *reg = pacb->pmuF;

			pacb->msgcode_rwbuffer[0] = dateसमय.b.msg_समय[0];
			pacb->msgcode_rwbuffer[1] = dateसमय.b.msg_समय[1];
			ग_लिखोl(ARCMSR_INBOUND_MESG0_SYNC_TIMER, &reg->inbound_msgaddr0);
			pacb->out_करोorbell ^= ARCMSR_HBEMU_DRV2IOP_MESSAGE_CMD_DONE;
			ग_लिखोl(pacb->out_करोorbell, &reg->iobound_करोorbell);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (sys_tz.tz_minuteswest)
		next_समय = ARCMSR_HOURS;
	अन्यथा
		next_समय = ARCMSR_MINUTES;
	mod_समयr(&pacb->refresh_समयr, jअगरfies + msecs_to_jअगरfies(next_समय));
पूर्ण

अटल पूर्णांक arcmsr_iop_confirm(काष्ठा AdapterControlBlock *acb)
अणु
	uपूर्णांक32_t cdb_phyaddr, cdb_phyaddr_hi32;
	dma_addr_t dma_coherent_handle;

	/*
	********************************************************************
	** here we need to tell iop 331 our मुक्तccb.HighPart
	** अगर मुक्तccb.HighPart is not zero
	********************************************************************
	*/
	चयन (acb->adapter_type) अणु
	हाल ACB_ADAPTER_TYPE_B:
	हाल ACB_ADAPTER_TYPE_D:
		dma_coherent_handle = acb->dma_coherent_handle2;
		अवरोध;
	हाल ACB_ADAPTER_TYPE_E:
	हाल ACB_ADAPTER_TYPE_F:
		dma_coherent_handle = acb->dma_coherent_handle +
			दुरत्व(काष्ठा CommandControlBlock, arcmsr_cdb);
		अवरोध;
	शेष:
		dma_coherent_handle = acb->dma_coherent_handle;
		अवरोध;
	पूर्ण
	cdb_phyaddr = lower_32_bits(dma_coherent_handle);
	cdb_phyaddr_hi32 = upper_32_bits(dma_coherent_handle);
	acb->cdb_phyaddr_hi32 = cdb_phyaddr_hi32;
	acb->cdb_phyadd_hipart = ((uपूर्णांक64_t)cdb_phyaddr_hi32) << 32;
	/*
	***********************************************************************
	**    अगर adapter type B, set winकरोw of "post command Q"
	***********************************************************************
	*/
	चयन (acb->adapter_type) अणु

	हाल ACB_ADAPTER_TYPE_A: अणु
		अगर (cdb_phyaddr_hi32 != 0) अणु
			काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;
			ग_लिखोl(ARCMSR_SIGNATURE_SET_CONFIG, \
						&reg->message_rwbuffer[0]);
			ग_लिखोl(cdb_phyaddr_hi32, &reg->message_rwbuffer[1]);
			ग_लिखोl(ARCMSR_INBOUND_MESG0_SET_CONFIG, \
							&reg->inbound_msgaddr0);
			अगर (!arcmsr_hbaA_रुको_msgपूर्णांक_पढ़ोy(acb)) अणु
				prपूर्णांकk(KERN_NOTICE "arcmsr%d: ""set ccb high \
				part physical address समयout\न",
				acb->host->host_no);
				वापस 1;
			पूर्ण
		पूर्ण
		पूर्ण
		अवरोध;

	हाल ACB_ADAPTER_TYPE_B: अणु
		uपूर्णांक32_t __iomem *rwbuffer;

		काष्ठा MessageUnit_B *reg = acb->pmuB;
		reg->postq_index = 0;
		reg->करोneq_index = 0;
		ग_लिखोl(ARCMSR_MESSAGE_SET_POST_WINDOW, reg->drv2iop_करोorbell);
		अगर (!arcmsr_hbaB_रुको_msgपूर्णांक_पढ़ोy(acb)) अणु
			prपूर्णांकk(KERN_NOTICE "arcmsr%d: cannot set driver mode\n", \
				acb->host->host_no);
			वापस 1;
		पूर्ण
		rwbuffer = reg->message_rwbuffer;
		/* driver "set config" signature */
		ग_लिखोl(ARCMSR_SIGNATURE_SET_CONFIG, rwbuffer++);
		/* normal should be zero */
		ग_लिखोl(cdb_phyaddr_hi32, rwbuffer++);
		/* postQ size (256 + 8)*4	 */
		ग_लिखोl(cdb_phyaddr, rwbuffer++);
		/* करोneQ size (256 + 8)*4	 */
		ग_लिखोl(cdb_phyaddr + 1056, rwbuffer++);
		/* ccb maxQ size must be --> [(256 + 8)*4]*/
		ग_लिखोl(1056, rwbuffer);

		ग_लिखोl(ARCMSR_MESSAGE_SET_CONFIG, reg->drv2iop_करोorbell);
		अगर (!arcmsr_hbaB_रुको_msgपूर्णांक_पढ़ोy(acb)) अणु
			prपूर्णांकk(KERN_NOTICE "arcmsr%d: 'set command Q window' \
			समयout \न",acb->host->host_no);
			वापस 1;
		पूर्ण
		ग_लिखोl(ARCMSR_MESSAGE_START_DRIVER_MODE, reg->drv2iop_करोorbell);
		अगर (!arcmsr_hbaB_रुको_msgपूर्णांक_पढ़ोy(acb)) अणु
			pr_err("arcmsr%d: can't set driver mode.\n",
				acb->host->host_no);
			वापस 1;
		पूर्ण
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_C: अणु
			काष्ठा MessageUnit_C __iomem *reg = acb->pmuC;

			prपूर्णांकk(KERN_NOTICE "arcmsr%d: cdb_phyaddr_hi32=0x%x\n",
					acb->adapter_index, cdb_phyaddr_hi32);
			ग_लिखोl(ARCMSR_SIGNATURE_SET_CONFIG, &reg->msgcode_rwbuffer[0]);
			ग_लिखोl(cdb_phyaddr_hi32, &reg->msgcode_rwbuffer[1]);
			ग_लिखोl(ARCMSR_INBOUND_MESG0_SET_CONFIG, &reg->inbound_msgaddr0);
			ग_लिखोl(ARCMSR_HBCMU_DRV2IOP_MESSAGE_CMD_DONE, &reg->inbound_करोorbell);
			अगर (!arcmsr_hbaC_रुको_msgपूर्णांक_पढ़ोy(acb)) अणु
				prपूर्णांकk(KERN_NOTICE "arcmsr%d: 'set command Q window' \
				समयout \न", acb->host->host_no);
				वापस 1;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_D: अणु
		uपूर्णांक32_t __iomem *rwbuffer;
		काष्ठा MessageUnit_D *reg = acb->pmuD;
		reg->postq_index = 0;
		reg->करोneq_index = 0;
		rwbuffer = reg->msgcode_rwbuffer;
		ग_लिखोl(ARCMSR_SIGNATURE_SET_CONFIG, rwbuffer++);
		ग_लिखोl(cdb_phyaddr_hi32, rwbuffer++);
		ग_लिखोl(cdb_phyaddr, rwbuffer++);
		ग_लिखोl(cdb_phyaddr + (ARCMSR_MAX_ARC1214_POSTQUEUE *
			माप(काष्ठा InBound_SRB)), rwbuffer++);
		ग_लिखोl(0x100, rwbuffer);
		ग_लिखोl(ARCMSR_INBOUND_MESG0_SET_CONFIG, reg->inbound_msgaddr0);
		अगर (!arcmsr_hbaD_रुको_msgपूर्णांक_पढ़ोy(acb)) अणु
			pr_notice("arcmsr%d: 'set command Q window' timeout\n",
				acb->host->host_no);
			वापस 1;
		पूर्ण
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_E: अणु
		काष्ठा MessageUnit_E __iomem *reg = acb->pmuE;
		ग_लिखोl(ARCMSR_SIGNATURE_SET_CONFIG, &reg->msgcode_rwbuffer[0]);
		ग_लिखोl(ARCMSR_SIGNATURE_1884, &reg->msgcode_rwbuffer[1]);
		ग_लिखोl(cdb_phyaddr, &reg->msgcode_rwbuffer[2]);
		ग_लिखोl(cdb_phyaddr_hi32, &reg->msgcode_rwbuffer[3]);
		ग_लिखोl(acb->ccbsize, &reg->msgcode_rwbuffer[4]);
		ग_लिखोl(lower_32_bits(acb->dma_coherent_handle2), &reg->msgcode_rwbuffer[5]);
		ग_लिखोl(upper_32_bits(acb->dma_coherent_handle2), &reg->msgcode_rwbuffer[6]);
		ग_लिखोl(acb->ioqueue_size, &reg->msgcode_rwbuffer[7]);
		ग_लिखोl(ARCMSR_INBOUND_MESG0_SET_CONFIG, &reg->inbound_msgaddr0);
		acb->out_करोorbell ^= ARCMSR_HBEMU_DRV2IOP_MESSAGE_CMD_DONE;
		ग_लिखोl(acb->out_करोorbell, &reg->iobound_करोorbell);
		अगर (!arcmsr_hbaE_रुको_msgपूर्णांक_पढ़ोy(acb)) अणु
			pr_notice("arcmsr%d: 'set command Q window' timeout \n",
				acb->host->host_no);
			वापस 1;
		पूर्ण
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_F: अणु
		काष्ठा MessageUnit_F __iomem *reg = acb->pmuF;

		acb->msgcode_rwbuffer[0] = ARCMSR_SIGNATURE_SET_CONFIG;
		acb->msgcode_rwbuffer[1] = ARCMSR_SIGNATURE_1886;
		acb->msgcode_rwbuffer[2] = cdb_phyaddr;
		acb->msgcode_rwbuffer[3] = cdb_phyaddr_hi32;
		acb->msgcode_rwbuffer[4] = acb->ccbsize;
		acb->msgcode_rwbuffer[5] = lower_32_bits(acb->dma_coherent_handle2);
		acb->msgcode_rwbuffer[6] = upper_32_bits(acb->dma_coherent_handle2);
		acb->msgcode_rwbuffer[7] = acb->completeQ_size;
		ग_लिखोl(ARCMSR_INBOUND_MESG0_SET_CONFIG, &reg->inbound_msgaddr0);
		acb->out_करोorbell ^= ARCMSR_HBEMU_DRV2IOP_MESSAGE_CMD_DONE;
		ग_लिखोl(acb->out_करोorbell, &reg->iobound_करोorbell);
		अगर (!arcmsr_hbaE_रुको_msgपूर्णांक_पढ़ोy(acb)) अणु
			pr_notice("arcmsr%d: 'set command Q window' timeout\n",
				acb->host->host_no);
			वापस 1;
		पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम arcmsr_रुको_firmware_पढ़ोy(काष्ठा AdapterControlBlock *acb)
अणु
	uपूर्णांक32_t firmware_state = 0;
	चयन (acb->adapter_type) अणु

	हाल ACB_ADAPTER_TYPE_A: अणु
		काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;
		करो अणु
			अगर (!(acb->acb_flags & ACB_F_IOP_INITED))
				msleep(20);
			firmware_state = पढ़ोl(&reg->outbound_msgaddr1);
		पूर्ण जबतक ((firmware_state & ARCMSR_OUTBOUND_MESG1_FIRMWARE_OK) == 0);
		पूर्ण
		अवरोध;

	हाल ACB_ADAPTER_TYPE_B: अणु
		काष्ठा MessageUnit_B *reg = acb->pmuB;
		करो अणु
			अगर (!(acb->acb_flags & ACB_F_IOP_INITED))
				msleep(20);
			firmware_state = पढ़ोl(reg->iop2drv_करोorbell);
		पूर्ण जबतक ((firmware_state & ARCMSR_MESSAGE_FIRMWARE_OK) == 0);
		ग_लिखोl(ARCMSR_DRV2IOP_END_OF_INTERRUPT, reg->drv2iop_करोorbell);
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_C: अणु
		काष्ठा MessageUnit_C __iomem *reg = acb->pmuC;
		करो अणु
			अगर (!(acb->acb_flags & ACB_F_IOP_INITED))
				msleep(20);
			firmware_state = पढ़ोl(&reg->outbound_msgaddr1);
		पूर्ण जबतक ((firmware_state & ARCMSR_HBCMU_MESSAGE_FIRMWARE_OK) == 0);
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_D: अणु
		काष्ठा MessageUnit_D *reg = acb->pmuD;
		करो अणु
			अगर (!(acb->acb_flags & ACB_F_IOP_INITED))
				msleep(20);
			firmware_state = पढ़ोl(reg->outbound_msgaddr1);
		पूर्ण जबतक ((firmware_state &
			ARCMSR_ARC1214_MESSAGE_FIRMWARE_OK) == 0);
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_E:
	हाल ACB_ADAPTER_TYPE_F: अणु
		काष्ठा MessageUnit_E __iomem *reg = acb->pmuE;
		करो अणु
			अगर (!(acb->acb_flags & ACB_F_IOP_INITED))
				msleep(20);
			firmware_state = पढ़ोl(&reg->outbound_msgaddr1);
		पूर्ण जबतक ((firmware_state & ARCMSR_HBEMU_MESSAGE_FIRMWARE_OK) == 0);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम arcmsr_request_device_map(काष्ठा समयr_list *t)
अणु
	काष्ठा AdapterControlBlock *acb = from_समयr(acb, t, eternal_समयr);
	अगर (acb->acb_flags & (ACB_F_MSG_GET_CONFIG | ACB_F_BUS_RESET | ACB_F_ABORT)) अणु
		mod_समयr(&acb->eternal_समयr, jअगरfies + msecs_to_jअगरfies(6 * HZ));
	पूर्ण अन्यथा अणु
		acb->fw_flag = FW_NORMAL;
		चयन (acb->adapter_type) अणु
		हाल ACB_ADAPTER_TYPE_A: अणु
			काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;
			ग_लिखोl(ARCMSR_INBOUND_MESG0_GET_CONFIG, &reg->inbound_msgaddr0);
			अवरोध;
			पूर्ण
		हाल ACB_ADAPTER_TYPE_B: अणु
			काष्ठा MessageUnit_B *reg = acb->pmuB;
			ग_लिखोl(ARCMSR_MESSAGE_GET_CONFIG, reg->drv2iop_करोorbell);
			अवरोध;
			पूर्ण
		हाल ACB_ADAPTER_TYPE_C: अणु
			काष्ठा MessageUnit_C __iomem *reg = acb->pmuC;
			ग_लिखोl(ARCMSR_INBOUND_MESG0_GET_CONFIG, &reg->inbound_msgaddr0);
			ग_लिखोl(ARCMSR_HBCMU_DRV2IOP_MESSAGE_CMD_DONE, &reg->inbound_करोorbell);
			अवरोध;
			पूर्ण
		हाल ACB_ADAPTER_TYPE_D: अणु
			काष्ठा MessageUnit_D *reg = acb->pmuD;
			ग_लिखोl(ARCMSR_INBOUND_MESG0_GET_CONFIG, reg->inbound_msgaddr0);
			अवरोध;
			पूर्ण
		हाल ACB_ADAPTER_TYPE_E: अणु
			काष्ठा MessageUnit_E __iomem *reg = acb->pmuE;
			ग_लिखोl(ARCMSR_INBOUND_MESG0_GET_CONFIG, &reg->inbound_msgaddr0);
			acb->out_करोorbell ^= ARCMSR_HBEMU_DRV2IOP_MESSAGE_CMD_DONE;
			ग_लिखोl(acb->out_करोorbell, &reg->iobound_करोorbell);
			अवरोध;
			पूर्ण
		हाल ACB_ADAPTER_TYPE_F: अणु
			काष्ठा MessageUnit_F __iomem *reg = acb->pmuF;
			uपूर्णांक32_t outMsg1 = पढ़ोl(&reg->outbound_msgaddr1);

			अगर (!(outMsg1 & ARCMSR_HBFMU_MESSAGE_FIRMWARE_OK) ||
				(outMsg1 & ARCMSR_HBFMU_MESSAGE_NO_VOLUME_CHANGE))
				जाओ nxt6s;
			ग_लिखोl(ARCMSR_INBOUND_MESG0_GET_CONFIG, &reg->inbound_msgaddr0);
			acb->out_करोorbell ^= ARCMSR_HBEMU_DRV2IOP_MESSAGE_CMD_DONE;
			ग_लिखोl(acb->out_करोorbell, &reg->iobound_करोorbell);
			अवरोध;
			पूर्ण
		शेष:
			वापस;
		पूर्ण
		acb->acb_flags |= ACB_F_MSG_GET_CONFIG;
nxt6s:
		mod_समयr(&acb->eternal_समयr, jअगरfies + msecs_to_jअगरfies(6 * HZ));
	पूर्ण
पूर्ण

अटल व्योम arcmsr_hbaA_start_bgrb(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;
	acb->acb_flags |= ACB_F_MSG_START_BGRB;
	ग_लिखोl(ARCMSR_INBOUND_MESG0_START_BGRB, &reg->inbound_msgaddr0);
	अगर (!arcmsr_hbaA_रुको_msgपूर्णांक_पढ़ोy(acb)) अणु
		prपूर्णांकk(KERN_NOTICE "arcmsr%d: रुको 'start adapter background \
				rebuild' समयout \न", acb->host->host_no);
	पूर्ण
पूर्ण

अटल व्योम arcmsr_hbaB_start_bgrb(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा MessageUnit_B *reg = acb->pmuB;
	acb->acb_flags |= ACB_F_MSG_START_BGRB;
	ग_लिखोl(ARCMSR_MESSAGE_START_BGRB, reg->drv2iop_करोorbell);
	अगर (!arcmsr_hbaB_रुको_msgपूर्णांक_पढ़ोy(acb)) अणु
		prपूर्णांकk(KERN_NOTICE "arcmsr%d: रुको 'start adapter background \
				rebuild' समयout \न",acb->host->host_no);
	पूर्ण
पूर्ण

अटल व्योम arcmsr_hbaC_start_bgrb(काष्ठा AdapterControlBlock *pACB)
अणु
	काष्ठा MessageUnit_C __iomem *phbcmu = pACB->pmuC;
	pACB->acb_flags |= ACB_F_MSG_START_BGRB;
	ग_लिखोl(ARCMSR_INBOUND_MESG0_START_BGRB, &phbcmu->inbound_msgaddr0);
	ग_लिखोl(ARCMSR_HBCMU_DRV2IOP_MESSAGE_CMD_DONE, &phbcmu->inbound_करोorbell);
	अगर (!arcmsr_hbaC_रुको_msgपूर्णांक_पढ़ोy(pACB)) अणु
		prपूर्णांकk(KERN_NOTICE "arcmsr%d: रुको 'start adapter background \
				rebuild' समयout \न", pACB->host->host_no);
	पूर्ण
	वापस;
पूर्ण

अटल व्योम arcmsr_hbaD_start_bgrb(काष्ठा AdapterControlBlock *pACB)
अणु
	काष्ठा MessageUnit_D *pmu = pACB->pmuD;

	pACB->acb_flags |= ACB_F_MSG_START_BGRB;
	ग_लिखोl(ARCMSR_INBOUND_MESG0_START_BGRB, pmu->inbound_msgaddr0);
	अगर (!arcmsr_hbaD_रुको_msgपूर्णांक_पढ़ोy(pACB)) अणु
		pr_notice("arcmsr%d: wait 'start adapter "
			"background rebuild' timeout\n", pACB->host->host_no);
	पूर्ण
पूर्ण

अटल व्योम arcmsr_hbaE_start_bgrb(काष्ठा AdapterControlBlock *pACB)
अणु
	काष्ठा MessageUnit_E __iomem *pmu = pACB->pmuE;

	pACB->acb_flags |= ACB_F_MSG_START_BGRB;
	ग_लिखोl(ARCMSR_INBOUND_MESG0_START_BGRB, &pmu->inbound_msgaddr0);
	pACB->out_करोorbell ^= ARCMSR_HBEMU_DRV2IOP_MESSAGE_CMD_DONE;
	ग_लिखोl(pACB->out_करोorbell, &pmu->iobound_करोorbell);
	अगर (!arcmsr_hbaE_रुको_msgपूर्णांक_पढ़ोy(pACB)) अणु
		pr_notice("arcmsr%d: wait 'start adapter "
			"background rebuild' timeout \n", pACB->host->host_no);
	पूर्ण
पूर्ण

अटल व्योम arcmsr_start_adapter_bgrb(काष्ठा AdapterControlBlock *acb)
अणु
	चयन (acb->adapter_type) अणु
	हाल ACB_ADAPTER_TYPE_A:
		arcmsr_hbaA_start_bgrb(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_B:
		arcmsr_hbaB_start_bgrb(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_C:
		arcmsr_hbaC_start_bgrb(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_D:
		arcmsr_hbaD_start_bgrb(acb);
		अवरोध;
	हाल ACB_ADAPTER_TYPE_E:
	हाल ACB_ADAPTER_TYPE_F:
		arcmsr_hbaE_start_bgrb(acb);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम arcmsr_clear_करोorbell_queue_buffer(काष्ठा AdapterControlBlock *acb)
अणु
	चयन (acb->adapter_type) अणु
	हाल ACB_ADAPTER_TYPE_A: अणु
		काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;
		uपूर्णांक32_t outbound_करोorbell;
		/* empty करोorbell Qbuffer अगर करोor bell ringed */
		outbound_करोorbell = पढ़ोl(&reg->outbound_करोorbell);
		/*clear करोorbell पूर्णांकerrupt */
		ग_लिखोl(outbound_करोorbell, &reg->outbound_करोorbell);
		ग_लिखोl(ARCMSR_INBOUND_DRIVER_DATA_READ_OK, &reg->inbound_करोorbell);
		पूर्ण
		अवरोध;

	हाल ACB_ADAPTER_TYPE_B: अणु
		काष्ठा MessageUnit_B *reg = acb->pmuB;
		uपूर्णांक32_t outbound_करोorbell, i;
		ग_लिखोl(ARCMSR_DOORBELL_INT_CLEAR_PATTERN, reg->iop2drv_करोorbell);
		ग_लिखोl(ARCMSR_DRV2IOP_DATA_READ_OK, reg->drv2iop_करोorbell);
		/* let IOP know data has been पढ़ो */
		क्रम(i=0; i < 200; i++) अणु
			msleep(20);
			outbound_करोorbell = पढ़ोl(reg->iop2drv_करोorbell);
			अगर( outbound_करोorbell & ARCMSR_IOP2DRV_DATA_WRITE_OK) अणु
				ग_लिखोl(ARCMSR_DOORBELL_INT_CLEAR_PATTERN, reg->iop2drv_करोorbell);
				ग_लिखोl(ARCMSR_DRV2IOP_DATA_READ_OK, reg->drv2iop_करोorbell);
			पूर्ण अन्यथा
				अवरोध;
		पूर्ण
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_C: अणु
		काष्ठा MessageUnit_C __iomem *reg = acb->pmuC;
		uपूर्णांक32_t outbound_करोorbell, i;
		/* empty करोorbell Qbuffer अगर करोor bell ringed */
		outbound_करोorbell = पढ़ोl(&reg->outbound_करोorbell);
		ग_लिखोl(outbound_करोorbell, &reg->outbound_करोorbell_clear);
		ग_लिखोl(ARCMSR_HBCMU_DRV2IOP_DATA_READ_OK, &reg->inbound_करोorbell);
		क्रम (i = 0; i < 200; i++) अणु
			msleep(20);
			outbound_करोorbell = पढ़ोl(&reg->outbound_करोorbell);
			अगर (outbound_करोorbell &
				ARCMSR_HBCMU_IOP2DRV_DATA_WRITE_OK) अणु
				ग_लिखोl(outbound_करोorbell,
					&reg->outbound_करोorbell_clear);
				ग_लिखोl(ARCMSR_HBCMU_DRV2IOP_DATA_READ_OK,
					&reg->inbound_करोorbell);
			पूर्ण अन्यथा
				अवरोध;
		पूर्ण
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_D: अणु
		काष्ठा MessageUnit_D *reg = acb->pmuD;
		uपूर्णांक32_t outbound_करोorbell, i;
		/* empty करोorbell Qbuffer अगर करोor bell ringed */
		outbound_करोorbell = पढ़ोl(reg->outbound_करोorbell);
		ग_लिखोl(outbound_करोorbell, reg->outbound_करोorbell);
		ग_लिखोl(ARCMSR_ARC1214_DRV2IOP_DATA_OUT_READ,
			reg->inbound_करोorbell);
		क्रम (i = 0; i < 200; i++) अणु
			msleep(20);
			outbound_करोorbell = पढ़ोl(reg->outbound_करोorbell);
			अगर (outbound_करोorbell &
				ARCMSR_ARC1214_IOP2DRV_DATA_WRITE_OK) अणु
				ग_लिखोl(outbound_करोorbell,
					reg->outbound_करोorbell);
				ग_लिखोl(ARCMSR_ARC1214_DRV2IOP_DATA_OUT_READ,
					reg->inbound_करोorbell);
			पूर्ण अन्यथा
				अवरोध;
		पूर्ण
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_E:
	हाल ACB_ADAPTER_TYPE_F: अणु
		काष्ठा MessageUnit_E __iomem *reg = acb->pmuE;
		uपूर्णांक32_t i, पंचांगp;

		acb->in_करोorbell = पढ़ोl(&reg->iobound_करोorbell);
		ग_लिखोl(0, &reg->host_पूर्णांक_status); /*clear पूर्णांकerrupt*/
		acb->out_करोorbell ^= ARCMSR_HBEMU_DRV2IOP_DATA_READ_OK;
		ग_लिखोl(acb->out_करोorbell, &reg->iobound_करोorbell);
		क्रम(i=0; i < 200; i++) अणु
			msleep(20);
			पंचांगp = acb->in_करोorbell;
			acb->in_करोorbell = पढ़ोl(&reg->iobound_करोorbell);
			अगर((पंचांगp ^ acb->in_करोorbell) & ARCMSR_HBEMU_IOP2DRV_DATA_WRITE_OK) अणु
				ग_लिखोl(0, &reg->host_पूर्णांक_status); /*clear पूर्णांकerrupt*/
				acb->out_करोorbell ^= ARCMSR_HBEMU_DRV2IOP_DATA_READ_OK;
				ग_लिखोl(acb->out_करोorbell, &reg->iobound_करोorbell);
			पूर्ण अन्यथा
				अवरोध;
		पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम arcmsr_enable_eoi_mode(काष्ठा AdapterControlBlock *acb)
अणु
	चयन (acb->adapter_type) अणु
	हाल ACB_ADAPTER_TYPE_A:
		वापस;
	हाल ACB_ADAPTER_TYPE_B:
		अणु
			काष्ठा MessageUnit_B *reg = acb->pmuB;
			ग_लिखोl(ARCMSR_MESSAGE_ACTIVE_EOI_MODE, reg->drv2iop_करोorbell);
			अगर (!arcmsr_hbaB_रुको_msgपूर्णांक_पढ़ोy(acb)) अणु
				prपूर्णांकk(KERN_NOTICE "ARCMSR IOP enables EOI_MODE TIMEOUT");
				वापस;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_C:
		वापस;
	पूर्ण
	वापस;
पूर्ण

अटल व्योम arcmsr_hardware_reset(काष्ठा AdapterControlBlock *acb)
अणु
	uपूर्णांक8_t value[64];
	पूर्णांक i, count = 0;
	काष्ठा MessageUnit_A __iomem *pmuA = acb->pmuA;
	काष्ठा MessageUnit_C __iomem *pmuC = acb->pmuC;
	काष्ठा MessageUnit_D *pmuD = acb->pmuD;

	/* backup pci config data */
	prपूर्णांकk(KERN_NOTICE "arcmsr%d: executing hw bus reset .....\n", acb->host->host_no);
	क्रम (i = 0; i < 64; i++) अणु
		pci_पढ़ो_config_byte(acb->pdev, i, &value[i]);
	पूर्ण
	/* hardware reset संकेत */
	अगर (acb->dev_id == 0x1680) अणु
		ग_लिखोl(ARCMSR_ARC1680_BUS_RESET, &pmuA->reserved1[0]);
	पूर्ण अन्यथा अगर (acb->dev_id == 0x1880) अणु
		करो अणु
			count++;
			ग_लिखोl(0xF, &pmuC->ग_लिखो_sequence);
			ग_लिखोl(0x4, &pmuC->ग_लिखो_sequence);
			ग_लिखोl(0xB, &pmuC->ग_लिखो_sequence);
			ग_लिखोl(0x2, &pmuC->ग_लिखो_sequence);
			ग_लिखोl(0x7, &pmuC->ग_लिखो_sequence);
			ग_लिखोl(0xD, &pmuC->ग_लिखो_sequence);
		पूर्ण जबतक (((पढ़ोl(&pmuC->host_diagnostic) & ARCMSR_ARC1880_DiagWrite_ENABLE) == 0) && (count < 5));
		ग_लिखोl(ARCMSR_ARC1880_RESET_ADAPTER, &pmuC->host_diagnostic);
	पूर्ण अन्यथा अगर (acb->dev_id == 0x1884) अणु
		काष्ठा MessageUnit_E __iomem *pmuE = acb->pmuE;
		करो अणु
			count++;
			ग_लिखोl(0x4, &pmuE->ग_लिखो_sequence_3xxx);
			ग_लिखोl(0xB, &pmuE->ग_लिखो_sequence_3xxx);
			ग_लिखोl(0x2, &pmuE->ग_लिखो_sequence_3xxx);
			ग_लिखोl(0x7, &pmuE->ग_लिखो_sequence_3xxx);
			ग_लिखोl(0xD, &pmuE->ग_लिखो_sequence_3xxx);
			mdelay(10);
		पूर्ण जबतक (((पढ़ोl(&pmuE->host_diagnostic_3xxx) &
			ARCMSR_ARC1884_DiagWrite_ENABLE) == 0) && (count < 5));
		ग_लिखोl(ARCMSR_ARC188X_RESET_ADAPTER, &pmuE->host_diagnostic_3xxx);
	पूर्ण अन्यथा अगर (acb->dev_id == 0x1214) अणु
		ग_लिखोl(0x20, pmuD->reset_request);
	पूर्ण अन्यथा अणु
		pci_ग_लिखो_config_byte(acb->pdev, 0x84, 0x20);
	पूर्ण
	msleep(2000);
	/* ग_लिखो back pci config data */
	क्रम (i = 0; i < 64; i++) अणु
		pci_ग_लिखो_config_byte(acb->pdev, i, value[i]);
	पूर्ण
	msleep(1000);
	वापस;
पूर्ण

अटल bool arcmsr_reset_in_progress(काष्ठा AdapterControlBlock *acb)
अणु
	bool rtn = true;

	चयन(acb->adapter_type) अणु
	हाल ACB_ADAPTER_TYPE_A:अणु
		काष्ठा MessageUnit_A __iomem *reg = acb->pmuA;
		rtn = ((पढ़ोl(&reg->outbound_msgaddr1) &
			ARCMSR_OUTBOUND_MESG1_FIRMWARE_OK) == 0) ? true : false;
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_B:अणु
		काष्ठा MessageUnit_B *reg = acb->pmuB;
		rtn = ((पढ़ोl(reg->iop2drv_करोorbell) &
			ARCMSR_MESSAGE_FIRMWARE_OK) == 0) ? true : false;
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_C:अणु
		काष्ठा MessageUnit_C __iomem *reg = acb->pmuC;
		rtn = (पढ़ोl(&reg->host_diagnostic) & 0x04) ? true : false;
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_D:अणु
		काष्ठा MessageUnit_D *reg = acb->pmuD;
		rtn = ((पढ़ोl(reg->sample_at_reset) & 0x80) == 0) ?
			true : false;
		पूर्ण
		अवरोध;
	हाल ACB_ADAPTER_TYPE_E:
	हाल ACB_ADAPTER_TYPE_F:अणु
		काष्ठा MessageUnit_E __iomem *reg = acb->pmuE;
		rtn = (पढ़ोl(&reg->host_diagnostic_3xxx) &
			ARCMSR_ARC188X_RESET_ADAPTER) ? true : false;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस rtn;
पूर्ण

अटल व्योम arcmsr_iop_init(काष्ठा AdapterControlBlock *acb)
अणु
	uपूर्णांक32_t पूर्णांकmask_org;
	/* disable all outbound पूर्णांकerrupt */
	पूर्णांकmask_org = arcmsr_disable_outbound_पूर्णांकs(acb);
	arcmsr_रुको_firmware_पढ़ोy(acb);
	arcmsr_iop_confirm(acb);
	/*start background rebuild*/
	arcmsr_start_adapter_bgrb(acb);
	/* empty करोorbell Qbuffer अगर करोor bell ringed */
	arcmsr_clear_करोorbell_queue_buffer(acb);
	arcmsr_enable_eoi_mode(acb);
	/* enable outbound Post Queue,outbound करोorbell Interrupt */
	arcmsr_enable_outbound_पूर्णांकs(acb, पूर्णांकmask_org);
	acb->acb_flags |= ACB_F_IOP_INITED;
पूर्ण

अटल uपूर्णांक8_t arcmsr_iop_reset(काष्ठा AdapterControlBlock *acb)
अणु
	काष्ठा CommandControlBlock *ccb;
	uपूर्णांक32_t पूर्णांकmask_org;
	uपूर्णांक8_t rtnval = 0x00;
	पूर्णांक i = 0;
	अचिन्हित दीर्घ flags;

	अगर (atomic_पढ़ो(&acb->ccboutstandingcount) != 0) अणु
		/* disable all outbound पूर्णांकerrupt */
		पूर्णांकmask_org = arcmsr_disable_outbound_पूर्णांकs(acb);
		/* talk to iop 331 outstanding command पातed */
		rtnval = arcmsr_पात_allcmd(acb);
		/* clear all outbound posted Q */
		arcmsr_करोne4पात_postqueue(acb);
		क्रम (i = 0; i < acb->maxFreeCCB; i++) अणु
			ccb = acb->pccb_pool[i];
			अगर (ccb->startकरोne == ARCMSR_CCB_START) अणु
				scsi_dma_unmap(ccb->pcmd);
				ccb->startकरोne = ARCMSR_CCB_DONE;
				ccb->ccb_flags = 0;
				spin_lock_irqsave(&acb->ccblist_lock, flags);
				list_add_tail(&ccb->list, &acb->ccb_मुक्त_list);
				spin_unlock_irqrestore(&acb->ccblist_lock, flags);
			पूर्ण
		पूर्ण
		atomic_set(&acb->ccboutstandingcount, 0);
		/* enable all outbound पूर्णांकerrupt */
		arcmsr_enable_outbound_पूर्णांकs(acb, पूर्णांकmask_org);
		वापस rtnval;
	पूर्ण
	वापस rtnval;
पूर्ण

अटल पूर्णांक arcmsr_bus_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा AdapterControlBlock *acb;
	पूर्णांक retry_count = 0;
	पूर्णांक rtn = FAILED;
	acb = (काष्ठा AdapterControlBlock *) cmd->device->host->hostdata;
	अगर (acb->acb_flags & ACB_F_ADAPTER_REMOVED)
		वापस SUCCESS;
	pr_notice("arcmsr: executing bus reset eh.....num_resets = %d,"
		" num_aborts = %d \n", acb->num_resets, acb->num_पातs);
	acb->num_resets++;

	अगर (acb->acb_flags & ACB_F_BUS_RESET) अणु
		दीर्घ समयout;
		pr_notice("arcmsr: there is a bus reset eh proceeding...\n");
		समयout = रुको_event_समयout(रुको_q, (acb->acb_flags
			& ACB_F_BUS_RESET) == 0, 220 * HZ);
		अगर (समयout)
			वापस SUCCESS;
	पूर्ण
	acb->acb_flags |= ACB_F_BUS_RESET;
	अगर (!arcmsr_iop_reset(acb)) अणु
		arcmsr_hardware_reset(acb);
		acb->acb_flags &= ~ACB_F_IOP_INITED;
रुको_reset_करोne:
		ssleep(ARCMSR_SLEEPTIME);
		अगर (arcmsr_reset_in_progress(acb)) अणु
			अगर (retry_count > ARCMSR_RETRYCOUNT) अणु
				acb->fw_flag = FW_DEADLOCK;
				pr_notice("arcmsr%d: waiting for hw bus reset"
					" return, RETRY TERMINATED!!\n",
					acb->host->host_no);
				वापस FAILED;
			पूर्ण
			retry_count++;
			जाओ रुको_reset_करोne;
		पूर्ण
		arcmsr_iop_init(acb);
		acb->fw_flag = FW_NORMAL;
		mod_समयr(&acb->eternal_समयr, jअगरfies +
			msecs_to_jअगरfies(6 * HZ));
		acb->acb_flags &= ~ACB_F_BUS_RESET;
		rtn = SUCCESS;
		pr_notice("arcmsr: scsi bus reset eh returns with success\n");
	पूर्ण अन्यथा अणु
		acb->acb_flags &= ~ACB_F_BUS_RESET;
		acb->fw_flag = FW_NORMAL;
		mod_समयr(&acb->eternal_समयr, jअगरfies +
			msecs_to_jअगरfies(6 * HZ));
		rtn = SUCCESS;
	पूर्ण
	वापस rtn;
पूर्ण

अटल पूर्णांक arcmsr_पात_one_cmd(काष्ठा AdapterControlBlock *acb,
		काष्ठा CommandControlBlock *ccb)
अणु
	पूर्णांक rtn;
	rtn = arcmsr_polling_ccbकरोne(acb, ccb);
	वापस rtn;
पूर्ण

अटल पूर्णांक arcmsr_पात(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा AdapterControlBlock *acb =
		(काष्ठा AdapterControlBlock *)cmd->device->host->hostdata;
	पूर्णांक i = 0;
	पूर्णांक rtn = FAILED;
	uपूर्णांक32_t पूर्णांकmask_org;

	अगर (acb->acb_flags & ACB_F_ADAPTER_REMOVED)
		वापस SUCCESS;
	prपूर्णांकk(KERN_NOTICE
		"arcmsr%d: abort device command of scsi id = %d lun = %d\n",
		acb->host->host_no, cmd->device->id, (u32)cmd->device->lun);
	acb->acb_flags |= ACB_F_ABORT;
	acb->num_पातs++;
	/*
	************************************************
	** the all पूर्णांकerrupt service routine is locked
	** we need to handle it as soon as possible and निकास
	************************************************
	*/
	अगर (!atomic_पढ़ो(&acb->ccboutstandingcount)) अणु
		acb->acb_flags &= ~ACB_F_ABORT;
		वापस rtn;
	पूर्ण

	पूर्णांकmask_org = arcmsr_disable_outbound_पूर्णांकs(acb);
	क्रम (i = 0; i < acb->maxFreeCCB; i++) अणु
		काष्ठा CommandControlBlock *ccb = acb->pccb_pool[i];
		अगर (ccb->startकरोne == ARCMSR_CCB_START && ccb->pcmd == cmd) अणु
			ccb->startकरोne = ARCMSR_CCB_ABORTED;
			rtn = arcmsr_पात_one_cmd(acb, ccb);
			अवरोध;
		पूर्ण
	पूर्ण
	acb->acb_flags &= ~ACB_F_ABORT;
	arcmsr_enable_outbound_पूर्णांकs(acb, पूर्णांकmask_org);
	वापस rtn;
पूर्ण

अटल स्थिर अक्षर *arcmsr_info(काष्ठा Scsi_Host *host)
अणु
	काष्ठा AdapterControlBlock *acb =
		(काष्ठा AdapterControlBlock *) host->hostdata;
	अटल अक्षर buf[256];
	अक्षर *type;
	पूर्णांक raid6 = 1;
	चयन (acb->pdev->device) अणु
	हाल PCI_DEVICE_ID_ARECA_1110:
	हाल PCI_DEVICE_ID_ARECA_1200:
	हाल PCI_DEVICE_ID_ARECA_1202:
	हाल PCI_DEVICE_ID_ARECA_1210:
		raid6 = 0;
		fallthrough;
	हाल PCI_DEVICE_ID_ARECA_1120:
	हाल PCI_DEVICE_ID_ARECA_1130:
	हाल PCI_DEVICE_ID_ARECA_1160:
	हाल PCI_DEVICE_ID_ARECA_1170:
	हाल PCI_DEVICE_ID_ARECA_1201:
	हाल PCI_DEVICE_ID_ARECA_1203:
	हाल PCI_DEVICE_ID_ARECA_1220:
	हाल PCI_DEVICE_ID_ARECA_1230:
	हाल PCI_DEVICE_ID_ARECA_1260:
	हाल PCI_DEVICE_ID_ARECA_1270:
	हाल PCI_DEVICE_ID_ARECA_1280:
		type = "SATA";
		अवरोध;
	हाल PCI_DEVICE_ID_ARECA_1214:
	हाल PCI_DEVICE_ID_ARECA_1380:
	हाल PCI_DEVICE_ID_ARECA_1381:
	हाल PCI_DEVICE_ID_ARECA_1680:
	हाल PCI_DEVICE_ID_ARECA_1681:
	हाल PCI_DEVICE_ID_ARECA_1880:
	हाल PCI_DEVICE_ID_ARECA_1884:
		type = "SAS/SATA";
		अवरोध;
	हाल PCI_DEVICE_ID_ARECA_1886:
		type = "NVMe/SAS/SATA";
		अवरोध;
	शेष:
		type = "unknown";
		raid6 =	0;
		अवरोध;
	पूर्ण
	प्र_लिखो(buf, "Areca %s RAID Controller %s\narcmsr version %s\n",
		type, raid6 ? "(RAID6 capable)" : "", ARCMSR_DRIVER_VERSION);
	वापस buf;
पूर्ण
