<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Aic94xx SAS/SATA driver initialization.
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>

#समावेश <scsi/scsi_host.h>

#समावेश "aic94xx.h"
#समावेश "aic94xx_reg.h"
#समावेश "aic94xx_hwi.h"
#समावेश "aic94xx_seq.h"
#समावेश "aic94xx_sds.h"

/* The क्रमmat is "version.release.patchlevel" */
#घोषणा ASD_DRIVER_VERSION "1.0.3"

अटल पूर्णांक use_msi = 0;
module_param_named(use_msi, use_msi, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(use_msi, "\n"
	"\tEnable(1) or disable(0) using PCI MSI.\n"
	"\tDefault: 0");

अटल काष्ठा scsi_transport_ढाँचा *aic94xx_transport_ढाँचा;
अटल पूर्णांक asd_scan_finished(काष्ठा Scsi_Host *, अचिन्हित दीर्घ);
अटल व्योम asd_scan_start(काष्ठा Scsi_Host *);

अटल काष्ठा scsi_host_ढाँचा aic94xx_sht = अणु
	.module			= THIS_MODULE,
	/* .name is initialized */
	.name			= "aic94xx",
	.queuecommand		= sas_queuecommand,
	.dma_need_drain		= ata_scsi_dma_need_drain,
	.target_alloc		= sas_target_alloc,
	.slave_configure	= sas_slave_configure,
	.scan_finished		= asd_scan_finished,
	.scan_start		= asd_scan_start,
	.change_queue_depth	= sas_change_queue_depth,
	.bios_param		= sas_bios_param,
	.can_queue		= 1,
	.this_id		= -1,
	.sg_tablesize		= SG_ALL,
	.max_sectors		= SCSI_DEFAULT_MAX_SECTORS,
	.eh_device_reset_handler	= sas_eh_device_reset_handler,
	.eh_target_reset_handler	= sas_eh_target_reset_handler,
	.target_destroy		= sas_target_destroy,
	.ioctl			= sas_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl		= sas_ioctl,
#पूर्ण_अगर
	.track_queue_depth	= 1,
पूर्ण;

अटल पूर्णांक asd_map_memio(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक err, i;
	काष्ठा asd_ha_addrspace *io_handle;

	asd_ha->iospace = 0;
	क्रम (i = 0; i < 3; i += 2) अणु
		io_handle = &asd_ha->io_handle[i==0?0:1];
		io_handle->start = pci_resource_start(asd_ha->pcidev, i);
		io_handle->len   = pci_resource_len(asd_ha->pcidev, i);
		io_handle->flags = pci_resource_flags(asd_ha->pcidev, i);
		err = -ENODEV;
		अगर (!io_handle->start || !io_handle->len) अणु
			asd_prपूर्णांकk("MBAR%d start or length for %s is 0.\n",
				   i==0?0:1, pci_name(asd_ha->pcidev));
			जाओ Err;
		पूर्ण
		err = pci_request_region(asd_ha->pcidev, i, ASD_DRIVER_NAME);
		अगर (err) अणु
			asd_prपूर्णांकk("couldn't reserve memory region for %s\n",
				   pci_name(asd_ha->pcidev));
			जाओ Err;
		पूर्ण
		io_handle->addr = ioremap(io_handle->start, io_handle->len);
		अगर (!io_handle->addr) अणु
			asd_prपूर्णांकk("couldn't map MBAR%d of %s\n", i==0?0:1,
				   pci_name(asd_ha->pcidev));
			err = -ENOMEM;
			जाओ Err_unreq;
		पूर्ण
	पूर्ण

	वापस 0;
Err_unreq:
	pci_release_region(asd_ha->pcidev, i);
Err:
	अगर (i > 0) अणु
		io_handle = &asd_ha->io_handle[0];
		iounmap(io_handle->addr);
		pci_release_region(asd_ha->pcidev, 0);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम asd_unmap_memio(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	काष्ठा asd_ha_addrspace *io_handle;

	io_handle = &asd_ha->io_handle[1];
	iounmap(io_handle->addr);
	pci_release_region(asd_ha->pcidev, 2);

	io_handle = &asd_ha->io_handle[0];
	iounmap(io_handle->addr);
	pci_release_region(asd_ha->pcidev, 0);
पूर्ण

अटल पूर्णांक asd_map_ioport(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक i = PCI_IOBAR_OFFSET, err;
	काष्ठा asd_ha_addrspace *io_handle = &asd_ha->io_handle[0];

	asd_ha->iospace = 1;
	io_handle->start = pci_resource_start(asd_ha->pcidev, i);
	io_handle->len   = pci_resource_len(asd_ha->pcidev, i);
	io_handle->flags = pci_resource_flags(asd_ha->pcidev, i);
	io_handle->addr  = (व्योम __iomem *) io_handle->start;
	अगर (!io_handle->start || !io_handle->len) अणु
		asd_prपूर्णांकk("couldn't get IO ports for %s\n",
			   pci_name(asd_ha->pcidev));
		वापस -ENODEV;
	पूर्ण
	err = pci_request_region(asd_ha->pcidev, i, ASD_DRIVER_NAME);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't reserve io space for %s\n",
			   pci_name(asd_ha->pcidev));
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम asd_unmap_ioport(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	pci_release_region(asd_ha->pcidev, PCI_IOBAR_OFFSET);
पूर्ण

अटल पूर्णांक asd_map_ha(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक err;
	u16 cmd_reg;

	err = pci_पढ़ो_config_word(asd_ha->pcidev, PCI_COMMAND, &cmd_reg);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't read command register of %s\n",
			   pci_name(asd_ha->pcidev));
		जाओ Err;
	पूर्ण

	err = -ENODEV;
	अगर (cmd_reg & PCI_COMMAND_MEMORY) अणु
		अगर ((err = asd_map_memio(asd_ha)))
			जाओ Err;
	पूर्ण अन्यथा अगर (cmd_reg & PCI_COMMAND_IO) अणु
		अगर ((err = asd_map_ioport(asd_ha)))
			जाओ Err;
		asd_prपूर्णांकk("%s ioport mapped -- upgrade your hardware\n",
			   pci_name(asd_ha->pcidev));
	पूर्ण अन्यथा अणु
		asd_prपूर्णांकk("no proper device access to %s\n",
			   pci_name(asd_ha->pcidev));
		जाओ Err;
	पूर्ण

	वापस 0;
Err:
	वापस err;
पूर्ण

अटल व्योम asd_unmap_ha(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	अगर (asd_ha->iospace)
		asd_unmap_ioport(asd_ha);
	अन्यथा
		asd_unmap_memio(asd_ha);
पूर्ण

अटल स्थिर अक्षर *asd_dev_rev[30] = अणु
	[0] = "A0",
	[1] = "A1",
	[8] = "B0",
पूर्ण;

अटल पूर्णांक asd_common_setup(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक err, i;

	asd_ha->revision_id = asd_ha->pcidev->revision;

	err = -ENODEV;
	अगर (asd_ha->revision_id < AIC9410_DEV_REV_B0) अणु
		asd_prपूर्णांकk("%s is revision %s (%X), which is not supported\n",
			   pci_name(asd_ha->pcidev),
			   asd_dev_rev[asd_ha->revision_id],
			   asd_ha->revision_id);
		जाओ Err;
	पूर्ण
	/* Provide some sane शेष values. */
	asd_ha->hw_prof.max_scbs = 512;
	asd_ha->hw_prof.max_ddbs = ASD_MAX_DDBS;
	asd_ha->hw_prof.num_phys = ASD_MAX_PHYS;
	/* All phys are enabled, by शेष. */
	asd_ha->hw_prof.enabled_phys = 0xFF;
	क्रम (i = 0; i < ASD_MAX_PHYS; i++) अणु
		asd_ha->hw_prof.phy_desc[i].max_sas_lrate =
			SAS_LINK_RATE_3_0_GBPS;
		asd_ha->hw_prof.phy_desc[i].min_sas_lrate =
			SAS_LINK_RATE_1_5_GBPS;
		asd_ha->hw_prof.phy_desc[i].max_sata_lrate =
			SAS_LINK_RATE_1_5_GBPS;
		asd_ha->hw_prof.phy_desc[i].min_sata_lrate =
			SAS_LINK_RATE_1_5_GBPS;
	पूर्ण

	वापस 0;
Err:
	वापस err;
पूर्ण

अटल पूर्णांक asd_aic9410_setup(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक err = asd_common_setup(asd_ha);

	अगर (err)
		वापस err;

	asd_ha->hw_prof.addr_range = 8;
	asd_ha->hw_prof.port_name_base = 0;
	asd_ha->hw_prof.dev_name_base = 8;
	asd_ha->hw_prof.sata_name_base = 16;

	वापस 0;
पूर्ण

अटल पूर्णांक asd_aic9405_setup(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक err = asd_common_setup(asd_ha);

	अगर (err)
		वापस err;

	asd_ha->hw_prof.addr_range = 4;
	asd_ha->hw_prof.port_name_base = 0;
	asd_ha->hw_prof.dev_name_base = 4;
	asd_ha->hw_prof.sata_name_base = 8;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार asd_show_dev_rev(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = dev_to_asd_ha(dev);
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n",
			asd_dev_rev[asd_ha->revision_id]);
पूर्ण
अटल DEVICE_ATTR(aic_revision, S_IRUGO, asd_show_dev_rev, शून्य);

अटल sमाप_प्रकार asd_show_dev_bios_build(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,अक्षर *buf)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = dev_to_asd_ha(dev);
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", asd_ha->hw_prof.bios.bld);
पूर्ण
अटल DEVICE_ATTR(bios_build, S_IRUGO, asd_show_dev_bios_build, शून्य);

अटल sमाप_प्रकार asd_show_dev_pcba_sn(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = dev_to_asd_ha(dev);
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", asd_ha->hw_prof.pcba_sn);
पूर्ण
अटल DEVICE_ATTR(pcba_sn, S_IRUGO, asd_show_dev_pcba_sn, शून्य);

#घोषणा FLASH_CMD_NONE      0x00
#घोषणा FLASH_CMD_UPDATE    0x01
#घोषणा FLASH_CMD_VERIFY    0x02

काष्ठा flash_command अणु
     u8      command[8];
     पूर्णांक     code;
पूर्ण;

अटल काष्ठा flash_command flash_command_table[] =
अणु
     अणु"verify",      FLASH_CMD_VERIFYपूर्ण,
     अणु"update",      FLASH_CMD_UPDATEपूर्ण,
     अणु"",            FLASH_CMD_NONEपूर्ण      /* Last entry should be शून्य. */
पूर्ण;

काष्ठा error_bios अणु
     अक्षर    *reason;
     पूर्णांक     err_code;
पूर्ण;

अटल काष्ठा error_bios flash_error_table[] =
अणु
     अणु"Failed to open bios image file",      FAIL_OPEN_BIOS_खातापूर्ण,
     अणु"PCI ID mismatch",                     FAIL_CHECK_PCI_IDपूर्ण,
     अणु"Checksum mismatch",                   FAIL_CHECK_SUMपूर्ण,
     अणु"Unknown Error",                       FAIL_UNKNOWNपूर्ण,
     अणु"Failed to verify.",                   FAIL_VERIFYपूर्ण,
     अणु"Failed to reset flash chip.",         FAIL_RESET_FLASHपूर्ण,
     अणु"Failed to find flash chip type.",     FAIL_FIND_FLASH_IDपूर्ण,
     अणु"Failed to erash flash chip.",         FAIL_ERASE_FLASHपूर्ण,
     अणु"Failed to program flash chip.",       FAIL_WRITE_FLASHपूर्ण,
     अणु"Flash in progress",                   FLASH_IN_PROGRESSपूर्ण,
     अणु"Image file size Error",               FAIL_खाता_SIZEपूर्ण,
     अणु"Input parameter error",               FAIL_PARAMETERSपूर्ण,
     अणु"Out of memory",                       FAIL_OUT_MEMORYपूर्ण,
     अणु"OK", 0पूर्ण	/* Last entry err_code = 0. */
पूर्ण;

अटल sमाप_प्रकार asd_store_update_bios(काष्ठा device *dev,
	काष्ठा device_attribute *attr,
	स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = dev_to_asd_ha(dev);
	अक्षर *cmd_ptr, *filename_ptr;
	काष्ठा bios_file_header header, *hdr_ptr;
	पूर्णांक res, i;
	u32 csum = 0;
	पूर्णांक flash_command = FLASH_CMD_NONE;
	पूर्णांक err = 0;

	cmd_ptr = kसुस्मृति(count, 2, GFP_KERNEL);

	अगर (!cmd_ptr) अणु
		err = FAIL_OUT_MEMORY;
		जाओ out;
	पूर्ण

	filename_ptr = cmd_ptr + count;
	res = माला_पूछो(buf, "%s %s", cmd_ptr, filename_ptr);
	अगर (res != 2) अणु
		err = FAIL_PARAMETERS;
		जाओ out1;
	पूर्ण

	क्रम (i = 0; flash_command_table[i].code != FLASH_CMD_NONE; i++) अणु
		अगर (!स_भेद(flash_command_table[i].command,
				 cmd_ptr, म_माप(cmd_ptr))) अणु
			flash_command = flash_command_table[i].code;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (flash_command == FLASH_CMD_NONE) अणु
		err = FAIL_PARAMETERS;
		जाओ out1;
	पूर्ण

	अगर (asd_ha->bios_status == FLASH_IN_PROGRESS) अणु
		err = FLASH_IN_PROGRESS;
		जाओ out1;
	पूर्ण
	err = request_firmware(&asd_ha->bios_image,
				   filename_ptr,
				   &asd_ha->pcidev->dev);
	अगर (err) अणु
		asd_prपूर्णांकk("Failed to load bios image file %s, error %d\n",
			   filename_ptr, err);
		err = FAIL_OPEN_BIOS_खाता;
		जाओ out1;
	पूर्ण

	hdr_ptr = (काष्ठा bios_file_header *)asd_ha->bios_image->data;

	अगर ((hdr_ptr->contrl_id.venकरोr != asd_ha->pcidev->venकरोr ||
		hdr_ptr->contrl_id.device != asd_ha->pcidev->device) &&
		(hdr_ptr->contrl_id.sub_venकरोr != asd_ha->pcidev->venकरोr ||
		hdr_ptr->contrl_id.sub_device != asd_ha->pcidev->device)) अणु

		ASD_DPRINTK("The PCI vendor or device id does not match\n");
		ASD_DPRINTK("vendor=%x dev=%x sub_vendor=%x sub_dev=%x"
		" pci vendor=%x pci dev=%x\n",
		hdr_ptr->contrl_id.venकरोr,
		hdr_ptr->contrl_id.device,
		hdr_ptr->contrl_id.sub_venकरोr,
		hdr_ptr->contrl_id.sub_device,
		asd_ha->pcidev->venकरोr,
		asd_ha->pcidev->device);
		err = FAIL_CHECK_PCI_ID;
		जाओ out2;
	पूर्ण

	अगर (hdr_ptr->filelen != asd_ha->bios_image->size) अणु
		err = FAIL_खाता_SIZE;
		जाओ out2;
	पूर्ण

	/* calculate checksum */
	क्रम (i = 0; i < hdr_ptr->filelen; i++)
		csum += asd_ha->bios_image->data[i];

	अगर ((csum & 0x0000ffff) != hdr_ptr->checksum) अणु
		ASD_DPRINTK("BIOS file checksum mismatch\n");
		err = FAIL_CHECK_SUM;
		जाओ out2;
	पूर्ण
	अगर (flash_command == FLASH_CMD_UPDATE) अणु
		asd_ha->bios_status = FLASH_IN_PROGRESS;
		err = asd_ग_लिखो_flash_seg(asd_ha,
			&asd_ha->bios_image->data[माप(*hdr_ptr)],
			0, hdr_ptr->filelen-माप(*hdr_ptr));
		अगर (!err)
			err = asd_verअगरy_flash_seg(asd_ha,
				&asd_ha->bios_image->data[माप(*hdr_ptr)],
				0, hdr_ptr->filelen-माप(*hdr_ptr));
	पूर्ण अन्यथा अणु
		asd_ha->bios_status = FLASH_IN_PROGRESS;
		err = asd_verअगरy_flash_seg(asd_ha,
			&asd_ha->bios_image->data[माप(header)],
			0, hdr_ptr->filelen-माप(header));
	पूर्ण

out2:
	release_firmware(asd_ha->bios_image);
out1:
	kमुक्त(cmd_ptr);
out:
	asd_ha->bios_status = err;

	अगर (!err)
		वापस count;
	अन्यथा
		वापस -err;
पूर्ण

अटल sमाप_प्रकार asd_show_update_bios(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक i;
	काष्ठा asd_ha_काष्ठा *asd_ha = dev_to_asd_ha(dev);

	क्रम (i = 0; flash_error_table[i].err_code != 0; i++) अणु
		अगर (flash_error_table[i].err_code == asd_ha->bios_status)
			अवरोध;
	पूर्ण
	अगर (asd_ha->bios_status != FLASH_IN_PROGRESS)
		asd_ha->bios_status = FLASH_OK;

	वापस snम_लिखो(buf, PAGE_SIZE, "status=%x %s\n",
			flash_error_table[i].err_code,
			flash_error_table[i].reason);
पूर्ण

अटल DEVICE_ATTR(update_bios, S_IRUGO|S_IWUSR,
	asd_show_update_bios, asd_store_update_bios);

अटल पूर्णांक asd_create_dev_attrs(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक err;

	err = device_create_file(&asd_ha->pcidev->dev, &dev_attr_aic_revision);
	अगर (err)
		वापस err;

	err = device_create_file(&asd_ha->pcidev->dev, &dev_attr_bios_build);
	अगर (err)
		जाओ err_rev;

	err = device_create_file(&asd_ha->pcidev->dev, &dev_attr_pcba_sn);
	अगर (err)
		जाओ err_biosb;
	err = device_create_file(&asd_ha->pcidev->dev, &dev_attr_update_bios);
	अगर (err)
		जाओ err_update_bios;

	वापस 0;

err_update_bios:
	device_हटाओ_file(&asd_ha->pcidev->dev, &dev_attr_pcba_sn);
err_biosb:
	device_हटाओ_file(&asd_ha->pcidev->dev, &dev_attr_bios_build);
err_rev:
	device_हटाओ_file(&asd_ha->pcidev->dev, &dev_attr_aic_revision);
	वापस err;
पूर्ण

अटल व्योम asd_हटाओ_dev_attrs(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	device_हटाओ_file(&asd_ha->pcidev->dev, &dev_attr_aic_revision);
	device_हटाओ_file(&asd_ha->pcidev->dev, &dev_attr_bios_build);
	device_हटाओ_file(&asd_ha->pcidev->dev, &dev_attr_pcba_sn);
	device_हटाओ_file(&asd_ha->pcidev->dev, &dev_attr_update_bios);
पूर्ण

/* The first entry, 0, is used क्रम dynamic ids, the rest क्रम devices
 * we know about.
 */
अटल स्थिर काष्ठा asd_pcidev_काष्ठा अणु
	स्थिर अक्षर * name;
	पूर्णांक (*setup)(काष्ठा asd_ha_काष्ठा *asd_ha);
पूर्ण asd_pcidev_data[] = अणु
	/* Id 0 is used क्रम dynamic ids. */
	अणु .name  = "Adaptec AIC-94xx SAS/SATA Host Adapter",
	  .setup = asd_aic9410_setup
	पूर्ण,
	अणु .name  = "Adaptec AIC-9410W SAS/SATA Host Adapter",
	  .setup = asd_aic9410_setup
	पूर्ण,
	अणु .name  = "Adaptec AIC-9405W SAS/SATA Host Adapter",
	  .setup = asd_aic9405_setup
	पूर्ण,
पूर्ण;

अटल पूर्णांक asd_create_ha_caches(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	asd_ha->scb_pool = dma_pool_create(ASD_DRIVER_NAME "_scb_pool",
					   &asd_ha->pcidev->dev,
					   माप(काष्ठा scb),
					   8, 0);
	अगर (!asd_ha->scb_pool) अणु
		asd_prपूर्णांकk("couldn't create scb pool\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * asd_मुक्त_edbs -- मुक्त empty data buffers
 * asd_ha: poपूर्णांकer to host adapter काष्ठाure
 */
अटल व्योम asd_मुक्त_edbs(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	काष्ठा asd_seq_data *seq = &asd_ha->seq;
	पूर्णांक i;

	क्रम (i = 0; i < seq->num_edbs; i++)
		asd_मुक्त_coherent(asd_ha, seq->edb_arr[i]);
	kमुक्त(seq->edb_arr);
	seq->edb_arr = शून्य;
पूर्ण

अटल व्योम asd_मुक्त_escbs(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	काष्ठा asd_seq_data *seq = &asd_ha->seq;
	पूर्णांक i;

	क्रम (i = 0; i < seq->num_escbs; i++) अणु
		अगर (!list_empty(&seq->escb_arr[i]->list))
			list_del_init(&seq->escb_arr[i]->list);

		asd_ascb_मुक्त(seq->escb_arr[i]);
	पूर्ण
	kमुक्त(seq->escb_arr);
	seq->escb_arr = शून्य;
पूर्ण

अटल व्योम asd_destroy_ha_caches(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक i;

	अगर (asd_ha->hw_prof.ddb_ext)
		asd_मुक्त_coherent(asd_ha, asd_ha->hw_prof.ddb_ext);
	अगर (asd_ha->hw_prof.scb_ext)
		asd_मुक्त_coherent(asd_ha, asd_ha->hw_prof.scb_ext);

	kमुक्त(asd_ha->hw_prof.ddb_biपंचांगap);
	asd_ha->hw_prof.ddb_biपंचांगap = शून्य;

	क्रम (i = 0; i < ASD_MAX_PHYS; i++) अणु
		काष्ठा asd_phy *phy = &asd_ha->phys[i];

		asd_मुक्त_coherent(asd_ha, phy->id_frm_tok);
	पूर्ण
	अगर (asd_ha->seq.escb_arr)
		asd_मुक्त_escbs(asd_ha);
	अगर (asd_ha->seq.edb_arr)
		asd_मुक्त_edbs(asd_ha);
	अगर (asd_ha->hw_prof.ue.area) अणु
		kमुक्त(asd_ha->hw_prof.ue.area);
		asd_ha->hw_prof.ue.area = शून्य;
	पूर्ण
	अगर (asd_ha->seq.tc_index_array) अणु
		kमुक्त(asd_ha->seq.tc_index_array);
		kमुक्त(asd_ha->seq.tc_index_biपंचांगap);
		asd_ha->seq.tc_index_array = शून्य;
		asd_ha->seq.tc_index_biपंचांगap = शून्य;
	पूर्ण
	अगर (asd_ha->seq.actual_dl) अणु
			asd_मुक्त_coherent(asd_ha, asd_ha->seq.actual_dl);
			asd_ha->seq.actual_dl = शून्य;
			asd_ha->seq.dl = शून्य;
	पूर्ण
	अगर (asd_ha->seq.next_scb.vaddr) अणु
		dma_pool_मुक्त(asd_ha->scb_pool, asd_ha->seq.next_scb.vaddr,
			      asd_ha->seq.next_scb.dma_handle);
		asd_ha->seq.next_scb.vaddr = शून्य;
	पूर्ण
	dma_pool_destroy(asd_ha->scb_pool);
	asd_ha->scb_pool = शून्य;
पूर्ण

काष्ठा kmem_cache *asd_dma_token_cache;
काष्ठा kmem_cache *asd_ascb_cache;

अटल पूर्णांक asd_create_global_caches(व्योम)
अणु
	अगर (!asd_dma_token_cache) अणु
		asd_dma_token_cache
			= kmem_cache_create(ASD_DRIVER_NAME "_dma_token",
					    माप(काष्ठा asd_dma_tok),
					    0,
					    SLAB_HWCACHE_ALIGN,
					    शून्य);
		अगर (!asd_dma_token_cache) अणु
			asd_prपूर्णांकk("couldn't create dma token cache\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (!asd_ascb_cache) अणु
		asd_ascb_cache = kmem_cache_create(ASD_DRIVER_NAME "_ascb",
						   माप(काष्ठा asd_ascb),
						   0,
						   SLAB_HWCACHE_ALIGN,
						   शून्य);
		अगर (!asd_ascb_cache) अणु
			asd_prपूर्णांकk("couldn't create ascb cache\n");
			जाओ Err;
		पूर्ण
	पूर्ण

	वापस 0;
Err:
	kmem_cache_destroy(asd_dma_token_cache);
	asd_dma_token_cache = शून्य;
	वापस -ENOMEM;
पूर्ण

अटल व्योम asd_destroy_global_caches(व्योम)
अणु
	kmem_cache_destroy(asd_dma_token_cache);
	asd_dma_token_cache = शून्य;

	kmem_cache_destroy(asd_ascb_cache);
	asd_ascb_cache = शून्य;
पूर्ण

अटल पूर्णांक asd_रेजिस्टर_sas_ha(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक i;
	काष्ठा asd_sas_phy   **sas_phys =
		kसुस्मृति(ASD_MAX_PHYS, माप(*sas_phys), GFP_KERNEL);
	काष्ठा asd_sas_port  **sas_ports =
		kसुस्मृति(ASD_MAX_PHYS, माप(*sas_ports), GFP_KERNEL);

	अगर (!sas_phys || !sas_ports) अणु
		kमुक्त(sas_phys);
		kमुक्त(sas_ports);
		वापस -ENOMEM;
	पूर्ण

	asd_ha->sas_ha.sas_ha_name = (अक्षर *) asd_ha->name;
	asd_ha->sas_ha.lldd_module = THIS_MODULE;
	asd_ha->sas_ha.sas_addr = &asd_ha->hw_prof.sas_addr[0];

	क्रम (i = 0; i < ASD_MAX_PHYS; i++) अणु
		sas_phys[i] = &asd_ha->phys[i].sas_phy;
		sas_ports[i] = &asd_ha->ports[i];
	पूर्ण

	asd_ha->sas_ha.sas_phy = sas_phys;
	asd_ha->sas_ha.sas_port= sas_ports;
	asd_ha->sas_ha.num_phys= ASD_MAX_PHYS;

	वापस sas_रेजिस्टर_ha(&asd_ha->sas_ha);
पूर्ण

अटल पूर्णांक asd_unरेजिस्टर_sas_ha(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक err;

	err = sas_unरेजिस्टर_ha(&asd_ha->sas_ha);

	sas_हटाओ_host(asd_ha->sas_ha.core.shost);
	scsi_host_put(asd_ha->sas_ha.core.shost);

	kमुक्त(asd_ha->sas_ha.sas_phy);
	kमुक्त(asd_ha->sas_ha.sas_port);

	वापस err;
पूर्ण

अटल पूर्णांक asd_pci_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	स्थिर काष्ठा asd_pcidev_काष्ठा *asd_dev;
	अचिन्हित asd_id = (अचिन्हित) id->driver_data;
	काष्ठा asd_ha_काष्ठा *asd_ha;
	काष्ठा Scsi_Host *shost;
	पूर्णांक err;

	अगर (asd_id >= ARRAY_SIZE(asd_pcidev_data)) अणु
		asd_prपूर्णांकk("wrong driver_data in PCI table\n");
		वापस -ENODEV;
	पूर्ण

	अगर ((err = pci_enable_device(dev))) अणु
		asd_prपूर्णांकk("couldn't enable device %s\n", pci_name(dev));
		वापस err;
	पूर्ण

	pci_set_master(dev);

	err = -ENOMEM;

	shost = scsi_host_alloc(&aic94xx_sht, माप(व्योम *));
	अगर (!shost)
		जाओ Err;

	asd_dev = &asd_pcidev_data[asd_id];

	asd_ha = kzalloc(माप(*asd_ha), GFP_KERNEL);
	अगर (!asd_ha) अणु
		asd_prपूर्णांकk("out of memory\n");
		जाओ Err_put;
	पूर्ण
	asd_ha->pcidev = dev;
	asd_ha->sas_ha.dev = &asd_ha->pcidev->dev;
	asd_ha->sas_ha.lldd_ha = asd_ha;

	asd_ha->bios_status = FLASH_OK;
	asd_ha->name = asd_dev->name;
	asd_prपूर्णांकk("found %s, device %s\n", asd_ha->name, pci_name(dev));

	SHOST_TO_SAS_HA(shost) = &asd_ha->sas_ha;
	asd_ha->sas_ha.core.shost = shost;
	shost->transportt = aic94xx_transport_ढाँचा;
	shost->max_id = ~0;
	shost->max_lun = ~0;
	shost->max_cmd_len = 16;

	err = scsi_add_host(shost, &dev->dev);
	अगर (err)
		जाओ Err_मुक्त;

	err = asd_dev->setup(asd_ha);
	अगर (err)
		जाओ Err_हटाओ;

	err = dma_set_mask_and_coherent(&dev->dev, DMA_BIT_MASK(64));
	अगर (err)
		err = dma_set_mask_and_coherent(&dev->dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		err = -ENODEV;
		asd_prपूर्णांकk("no suitable DMA mask for %s\n", pci_name(dev));
		जाओ Err_हटाओ;
	पूर्ण

	pci_set_drvdata(dev, asd_ha);

	err = asd_map_ha(asd_ha);
	अगर (err)
		जाओ Err_हटाओ;

	err = asd_create_ha_caches(asd_ha);
        अगर (err)
		जाओ Err_unmap;

	err = asd_init_hw(asd_ha);
	अगर (err)
		जाओ Err_मुक्त_cache;

	asd_prपूर्णांकk("device %s: SAS addr %llx, PCBA SN %s, %d phys, %d enabled "
		   "phys, flash %s, BIOS %s%d\n",
		   pci_name(dev), SAS_ADDR(asd_ha->hw_prof.sas_addr),
		   asd_ha->hw_prof.pcba_sn, asd_ha->hw_prof.max_phys,
		   asd_ha->hw_prof.num_phys,
		   asd_ha->hw_prof.flash.present ? "present" : "not present",
		   asd_ha->hw_prof.bios.present ? "build " : "not present",
		   asd_ha->hw_prof.bios.bld);

	shost->can_queue = asd_ha->seq.can_queue;

	अगर (use_msi)
		pci_enable_msi(asd_ha->pcidev);

	err = request_irq(asd_ha->pcidev->irq, asd_hw_isr, IRQF_SHARED,
			  ASD_DRIVER_NAME, asd_ha);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't get irq %d for %s\n",
			   asd_ha->pcidev->irq, pci_name(asd_ha->pcidev));
		जाओ Err_irq;
	पूर्ण
	asd_enable_पूर्णांकs(asd_ha);

	err = asd_init_post_escbs(asd_ha);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't post escbs for %s\n",
			   pci_name(asd_ha->pcidev));
		जाओ Err_escbs;
	पूर्ण
	ASD_DPRINTK("escbs posted\n");

	err = asd_create_dev_attrs(asd_ha);
	अगर (err)
		जाओ Err_dev_attrs;

	err = asd_रेजिस्टर_sas_ha(asd_ha);
	अगर (err)
		जाओ Err_reg_sas;

	scsi_scan_host(shost);

	वापस 0;

Err_reg_sas:
	asd_हटाओ_dev_attrs(asd_ha);
Err_dev_attrs:
Err_escbs:
	asd_disable_पूर्णांकs(asd_ha);
	मुक्त_irq(dev->irq, asd_ha);
Err_irq:
	अगर (use_msi)
		pci_disable_msi(dev);
	asd_chip_hardrst(asd_ha);
Err_मुक्त_cache:
	asd_destroy_ha_caches(asd_ha);
Err_unmap:
	asd_unmap_ha(asd_ha);
Err_हटाओ:
	scsi_हटाओ_host(shost);
Err_मुक्त:
	kमुक्त(asd_ha);
Err_put:
	scsi_host_put(shost);
Err:
	pci_disable_device(dev);
	वापस err;
पूर्ण

अटल व्योम asd_मुक्त_queues(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	अचिन्हित दीर्घ flags;
	LIST_HEAD(pending);
	काष्ठा list_head *n, *pos;

	spin_lock_irqsave(&asd_ha->seq.pend_q_lock, flags);
	asd_ha->seq.pending = 0;
	list_splice_init(&asd_ha->seq.pend_q, &pending);
	spin_unlock_irqrestore(&asd_ha->seq.pend_q_lock, flags);

	अगर (!list_empty(&pending))
		ASD_DPRINTK("Uh-oh! Pending is not empty!\n");

	list_क्रम_each_safe(pos, n, &pending) अणु
		काष्ठा asd_ascb *ascb = list_entry(pos, काष्ठा asd_ascb, list);
		/*
		 * Delete unexpired ascb समयrs.  This may happen अगर we issue
		 * a CONTROL PHY scb to an adapter and rmmod beक्रमe the scb
		 * बार out.  Apparently we करोn't रुको क्रम the CONTROL PHY
		 * to complete, so it करोesn't matter अगर we समाप्त the समयr.
		 */
		del_समयr_sync(&ascb->समयr);
		WARN_ON(ascb->scb->header.opcode != CONTROL_PHY);

		list_del_init(pos);
		ASD_DPRINTK("freeing from pending\n");
		asd_ascb_मुक्त(ascb);
	पूर्ण
पूर्ण

अटल व्योम asd_turn_off_leds(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	u8 phy_mask = asd_ha->hw_prof.enabled_phys;
	u8 i;

	क्रम_each_phy(phy_mask, phy_mask, i) अणु
		asd_turn_led(asd_ha, i, 0);
		asd_control_led(asd_ha, i, 0);
	पूर्ण
पूर्ण

अटल व्योम asd_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = pci_get_drvdata(dev);

	अगर (!asd_ha)
		वापस;

	asd_unरेजिस्टर_sas_ha(asd_ha);

	asd_disable_पूर्णांकs(asd_ha);

	asd_हटाओ_dev_attrs(asd_ha);

	/* XXX more here as needed */

	मुक्त_irq(dev->irq, asd_ha);
	अगर (use_msi)
		pci_disable_msi(asd_ha->pcidev);
	asd_turn_off_leds(asd_ha);
	asd_chip_hardrst(asd_ha);
	asd_मुक्त_queues(asd_ha);
	asd_destroy_ha_caches(asd_ha);
	asd_unmap_ha(asd_ha);
	kमुक्त(asd_ha);
	pci_disable_device(dev);
	वापस;
पूर्ण

अटल व्योम asd_scan_start(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha;
	पूर्णांक err;

	asd_ha = SHOST_TO_SAS_HA(shost)->lldd_ha;
	err = asd_enable_phys(asd_ha, asd_ha->hw_prof.enabled_phys);
	अगर (err)
		asd_prपूर्णांकk("Couldn't enable phys, err:%d\n", err);
पूर्ण

अटल पूर्णांक asd_scan_finished(काष्ठा Scsi_Host *shost, अचिन्हित दीर्घ समय)
अणु
	/* give the phy enabling पूर्णांकerrupt event समय to come in (1s
	 * is empirically about all it takes) */
	अगर (समय < HZ)
		वापस 0;
	/* Wait क्रम discovery to finish */
	sas_drain_work(SHOST_TO_SAS_HA(shost));
	वापस 1;
पूर्ण

अटल sमाप_प्रकार version_show(काष्ठा device_driver *driver, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", ASD_DRIVER_VERSION);
पूर्ण
अटल DRIVER_ATTR_RO(version);

अटल पूर्णांक asd_create_driver_attrs(काष्ठा device_driver *driver)
अणु
	वापस driver_create_file(driver, &driver_attr_version);
पूर्ण

अटल व्योम asd_हटाओ_driver_attrs(काष्ठा device_driver *driver)
अणु
	driver_हटाओ_file(driver, &driver_attr_version);
पूर्ण

अटल काष्ठा sas_करोमुख्य_function_ढाँचा aic94xx_transport_functions = अणु
	.lldd_dev_found		= asd_dev_found,
	.lldd_dev_gone		= asd_dev_gone,

	.lldd_execute_task	= asd_execute_task,

	.lldd_पात_task	= asd_पात_task,
	.lldd_पात_task_set	= asd_पात_task_set,
	.lldd_clear_aca		= asd_clear_aca,
	.lldd_clear_task_set	= asd_clear_task_set,
	.lldd_I_T_nexus_reset	= asd_I_T_nexus_reset,
	.lldd_lu_reset		= asd_lu_reset,
	.lldd_query_task	= asd_query_task,

	.lldd_clear_nexus_port	= asd_clear_nexus_port,
	.lldd_clear_nexus_ha	= asd_clear_nexus_ha,

	.lldd_control_phy	= asd_control_phy,

	.lldd_ata_set_dmamode	= asd_set_dmamode,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id aic94xx_pci_table[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_ADAPTEC2, 0x410),0, 0, 1पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ADAPTEC2, 0x412),0, 0, 1पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ADAPTEC2, 0x416),0, 0, 1पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ADAPTEC2, 0x41E),0, 0, 1पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ADAPTEC2, 0x41F),0, 0, 1पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ADAPTEC2, 0x430),0, 0, 2पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ADAPTEC2, 0x432),0, 0, 2पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ADAPTEC2, 0x43E),0, 0, 2पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ADAPTEC2, 0x43F),0, 0, 2पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, aic94xx_pci_table);

अटल काष्ठा pci_driver aic94xx_pci_driver = अणु
	.name		= ASD_DRIVER_NAME,
	.id_table	= aic94xx_pci_table,
	.probe		= asd_pci_probe,
	.हटाओ		= asd_pci_हटाओ,
पूर्ण;

अटल पूर्णांक __init aic94xx_init(व्योम)
अणु
	पूर्णांक err;


	asd_prपूर्णांकk("%s version %s loaded\n", ASD_DRIVER_DESCRIPTION,
		   ASD_DRIVER_VERSION);

	err = asd_create_global_caches();
	अगर (err)
		वापस err;

	aic94xx_transport_ढाँचा =
		sas_करोमुख्य_attach_transport(&aic94xx_transport_functions);
	अगर (!aic94xx_transport_ढाँचा) अणु
		err = -ENOMEM;
		जाओ out_destroy_caches;
	पूर्ण

	err = pci_रेजिस्टर_driver(&aic94xx_pci_driver);
	अगर (err)
		जाओ out_release_transport;

	err = asd_create_driver_attrs(&aic94xx_pci_driver.driver);
	अगर (err)
		जाओ out_unरेजिस्टर_pcidrv;

	वापस err;

 out_unरेजिस्टर_pcidrv:
	pci_unरेजिस्टर_driver(&aic94xx_pci_driver);
 out_release_transport:
	sas_release_transport(aic94xx_transport_ढाँचा);
 out_destroy_caches:
	asd_destroy_global_caches();

	वापस err;
पूर्ण

अटल व्योम __निकास aic94xx_निकास(व्योम)
अणु
	asd_हटाओ_driver_attrs(&aic94xx_pci_driver.driver);
	pci_unरेजिस्टर_driver(&aic94xx_pci_driver);
	sas_release_transport(aic94xx_transport_ढाँचा);
	asd_release_firmware();
	asd_destroy_global_caches();
	asd_prपूर्णांकk("%s version %s unloaded\n", ASD_DRIVER_DESCRIPTION,
		   ASD_DRIVER_VERSION);
पूर्ण

module_init(aic94xx_init);
module_निकास(aic94xx_निकास);

MODULE_AUTHOR("Luben Tuikov <luben_tuikov@adaptec.com>");
MODULE_DESCRIPTION(ASD_DRIVER_DESCRIPTION);
MODULE_LICENSE("GPL v2");
MODULE_VERSION(ASD_DRIVER_VERSION);
