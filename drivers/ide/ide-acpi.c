<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Provides ACPI support क्रम IDE drives.
 *
 * Copyright (C) 2005 Intel Corp.
 * Copyright (C) 2005 Randy Dunlap
 * Copyright (C) 2006 SUSE Linux Products GmbH
 * Copyright (C) 2006 Hannes Reinecke
 */

#समावेश <linux/acpi.h>
#समावेश <linux/ata.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/ide.h>
#समावेश <linux/pci.h>
#समावेश <linux/dmi.h>
#समावेश <linux/module.h>

#घोषणा REGS_PER_GTF		7

काष्ठा GTM_buffer अणु
	u32	PIO_speed0;
	u32	DMA_speed0;
	u32	PIO_speed1;
	u32	DMA_speed1;
	u32	GTM_flags;
पूर्ण;

काष्ठा ide_acpi_drive_link अणु
	acpi_handle	 obj_handle;
	u8		 idbuff[512];
पूर्ण;

काष्ठा ide_acpi_hwअगर_link अणु
	ide_hwअगर_t			*hwअगर;
	acpi_handle			 obj_handle;
	काष्ठा GTM_buffer		 gपंचांग;
	काष्ठा ide_acpi_drive_link	 master;
	काष्ठा ide_acpi_drive_link	 slave;
पूर्ण;

#अघोषित DEBUGGING
/* note: adds function name and KERN_DEBUG */
#अगर_घोषित DEBUGGING
#घोषणा DEBPRINT(fmt, args...)	\
		prपूर्णांकk(KERN_DEBUG "%s: " fmt, __func__, ## args)
#अन्यथा
#घोषणा DEBPRINT(fmt, args...)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर	/* DEBUGGING */

अटल bool ide_noacpi;
module_param_named(noacpi, ide_noacpi, bool, 0);
MODULE_PARM_DESC(noacpi, "disable IDE ACPI support");

अटल bool ide_acpigtf;
module_param_named(acpigtf, ide_acpigtf, bool, 0);
MODULE_PARM_DESC(acpigtf, "enable IDE ACPI _GTF support");

अटल bool ide_acpionboot;
module_param_named(acpionboot, ide_acpionboot, bool, 0);
MODULE_PARM_DESC(acpionboot, "call IDE ACPI methods on boot");

अटल bool ide_noacpi_psx;
अटल पूर्णांक no_acpi_psx(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	ide_noacpi_psx = true;
	prपूर्णांकk(KERN_NOTICE"%s detected - disable ACPI _PSx.\n", id->ident);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id ide_acpi_dmi_table[] = अणु
	/* Bug 9673. */
	/* We should check अगर this is because ACPI NVS isn't save/restored. */
	अणु
		.callback = no_acpi_psx,
		.ident    = "HP nx9005",
		.matches  = अणु
			DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies Ltd."),
			DMI_MATCH(DMI_BIOS_VERSION, "KAM1.60")
		पूर्ण,
	पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;

पूर्णांक ide_acpi_init(व्योम)
अणु
	dmi_check_प्रणाली(ide_acpi_dmi_table);
	वापस 0;
पूर्ण

bool ide_port_acpi(ide_hwअगर_t *hwअगर)
अणु
	वापस ide_noacpi == 0 && hwअगर->acpidata;
पूर्ण

अटल acpi_handle acpi_get_child(acpi_handle handle, u64 addr)
अणु
	काष्ठा acpi_device *adev;

	अगर (!handle || acpi_bus_get_device(handle, &adev))
		वापस शून्य;

	adev = acpi_find_child_device(adev, addr, false);
	वापस adev ? adev->handle : शून्य;
पूर्ण

/**
 * ide_get_dev_handle - finds acpi_handle and PCI device.function
 * @dev: device to locate
 * @handle: वापसed acpi_handle क्रम @dev
 * @pcidevfn: वापस PCI device.func क्रम @dev
 *
 * Returns the ACPI object handle to the corresponding PCI device.
 *
 * Returns 0 on success, <0 on error.
 */
अटल पूर्णांक ide_get_dev_handle(काष्ठा device *dev, acpi_handle *handle,
			       u64 *pcidevfn)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	अचिन्हित पूर्णांक bus, devnum, func;
	u64 addr;
	acpi_handle dev_handle;
	acpi_status status;
	काष्ठा acpi_device_info	*dinfo = शून्य;
	पूर्णांक ret = -ENODEV;

	bus = pdev->bus->number;
	devnum = PCI_SLOT(pdev->devfn);
	func = PCI_FUNC(pdev->devfn);
	/* ACPI _ADR encoding क्रम PCI bus: */
	addr = (u64)(devnum << 16 | func);

	DEBPRINT("ENTER: pci %02x:%02x.%01x\n", bus, devnum, func);

	dev_handle = ACPI_HANDLE(dev);
	अगर (!dev_handle) अणु
		DEBPRINT("no acpi handle for device\n");
		जाओ err;
	पूर्ण

	status = acpi_get_object_info(dev_handle, &dinfo);
	अगर (ACPI_FAILURE(status)) अणु
		DEBPRINT("get_object_info for device failed\n");
		जाओ err;
	पूर्ण
	अगर (dinfo && (dinfo->valid & ACPI_VALID_ADR) &&
	    dinfo->address == addr) अणु
		*pcidevfn = addr;
		*handle = dev_handle;
	पूर्ण अन्यथा अणु
		DEBPRINT("get_object_info for device has wrong "
			" address: %llu, should be %u\n",
			dinfo ? (अचिन्हित दीर्घ दीर्घ)dinfo->address : -1ULL,
			(अचिन्हित पूर्णांक)addr);
		जाओ err;
	पूर्ण

	DEBPRINT("for dev=0x%x.%x, addr=0x%llx, *handle=0x%p\n",
		 devnum, func, (अचिन्हित दीर्घ दीर्घ)addr, *handle);
	ret = 0;
err:
	kमुक्त(dinfo);
	वापस ret;
पूर्ण

/**
 * ide_acpi_hwअगर_get_handle - Get ACPI object handle क्रम a given hwअगर
 * @hwअगर: device to locate
 *
 * Retrieves the object handle क्रम a given hwअगर.
 *
 * Returns handle on success, 0 on error.
 */
अटल acpi_handle ide_acpi_hwअगर_get_handle(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा device		*dev = hwअगर->gendev.parent;
	acpi_handle		dev_handle;
	u64			pcidevfn;
	acpi_handle		chan_handle;
	पूर्णांक			err;

	DEBPRINT("ENTER: device %s\n", hwअगर->name);

	अगर (!dev) अणु
		DEBPRINT("no PCI device for %s\n", hwअगर->name);
		वापस शून्य;
	पूर्ण

	err = ide_get_dev_handle(dev, &dev_handle, &pcidevfn);
	अगर (err < 0) अणु
		DEBPRINT("ide_get_dev_handle failed (%d)\n", err);
		वापस शून्य;
	पूर्ण

	/* get child objects of dev_handle == channel objects,
	 * + _their_ children == drive objects */
	/* channel is hwअगर->channel */
	chan_handle = acpi_get_child(dev_handle, hwअगर->channel);
	DEBPRINT("chan adr=%d: handle=0x%p\n",
		 hwअगर->channel, chan_handle);

	वापस chan_handle;
पूर्ण

/**
 * करो_drive_get_GTF - get the drive bootup शेष taskfile settings
 * @drive: the drive क्रम which the taskfile settings should be retrieved
 * @gtf_length: number of bytes of _GTF data वापसed at @gtf_address
 * @gtf_address: buffer containing _GTF taskfile arrays
 *
 * The _GTF method has no input parameters.
 * It वापसs a variable number of रेजिस्टर set values (रेजिस्टरs
 * hex 1F1..1F7, taskfiles).
 * The <variable number> is not known in advance, so have ACPI-CA
 * allocate the buffer as needed and वापस it, then मुक्त it later.
 *
 * The वापसed @gtf_length and @gtf_address are only valid अगर the
 * function वापस value is 0.
 */
अटल पूर्णांक करो_drive_get_GTF(ide_drive_t *drive,
		     अचिन्हित पूर्णांक *gtf_length, अचिन्हित दीर्घ *gtf_address,
		     अचिन्हित दीर्घ *obj_loc)
अणु
	acpi_status			status;
	काष्ठा acpi_buffer		output;
	जोड़ acpi_object 		*out_obj;
	पूर्णांक				err = -ENODEV;

	*gtf_length = 0;
	*gtf_address = 0UL;
	*obj_loc = 0UL;

	अगर (!drive->acpidata->obj_handle) अणु
		DEBPRINT("No ACPI object found for %s\n", drive->name);
		जाओ out;
	पूर्ण

	/* Setting up output buffer */
	output.length = ACPI_ALLOCATE_BUFFER;
	output.poपूर्णांकer = शून्य;	/* ACPI-CA sets this; save/मुक्त it later */

	/* _GTF has no input parameters */
	err = -EIO;
	status = acpi_evaluate_object(drive->acpidata->obj_handle, "_GTF",
				      शून्य, &output);
	अगर (ACPI_FAILURE(status)) अणु
		prपूर्णांकk(KERN_DEBUG
		       "%s: Run _GTF error: status = 0x%x\n",
		       __func__, status);
		जाओ out;
	पूर्ण

	अगर (!output.length || !output.poपूर्णांकer) अणु
		DEBPRINT("Run _GTF: "
		       "length or ptr is NULL (0x%llx, 0x%p)\n",
		       (अचिन्हित दीर्घ दीर्घ)output.length,
		       output.poपूर्णांकer);
		जाओ out;
	पूर्ण

	out_obj = output.poपूर्णांकer;
	अगर (out_obj->type != ACPI_TYPE_BUFFER) अणु
		DEBPRINT("Run _GTF: error: "
		       "expected object type of ACPI_TYPE_BUFFER, "
		       "got 0x%x\n", out_obj->type);
		err = -ENOENT;
		kमुक्त(output.poपूर्णांकer);
		जाओ out;
	पूर्ण

	अगर (!out_obj->buffer.length || !out_obj->buffer.poपूर्णांकer ||
	    out_obj->buffer.length % REGS_PER_GTF) अणु
		prपूर्णांकk(KERN_ERR
		       "%s: unexpected GTF length (%d) or addr (0x%p)\n",
		       __func__, out_obj->buffer.length,
		       out_obj->buffer.poपूर्णांकer);
		err = -ENOENT;
		kमुक्त(output.poपूर्णांकer);
		जाओ out;
	पूर्ण

	*gtf_length = out_obj->buffer.length;
	*gtf_address = (अचिन्हित दीर्घ)out_obj->buffer.poपूर्णांकer;
	*obj_loc = (अचिन्हित दीर्घ)out_obj;
	DEBPRINT("returning gtf_length=%d, gtf_address=0x%lx, obj_loc=0x%lx\n",
		 *gtf_length, *gtf_address, *obj_loc);
	err = 0;
out:
	वापस err;
पूर्ण

/**
 * करो_drive_set_taskfiles - ग_लिखो the drive taskfile settings from _GTF
 * @drive: the drive to which the taskfile command should be sent
 * @gtf_length: total number of bytes of _GTF taskfiles
 * @gtf_address: location of _GTF taskfile arrays
 *
 * Write अणुgtf_address, length gtf_lengthपूर्ण in groups of
 * REGS_PER_GTF bytes.
 */
अटल पूर्णांक करो_drive_set_taskfiles(ide_drive_t *drive,
				  अचिन्हित पूर्णांक gtf_length,
				  अचिन्हित दीर्घ gtf_address)
अणु
	पूर्णांक			rc = 0, err;
	पूर्णांक			gtf_count = gtf_length / REGS_PER_GTF;
	पूर्णांक			ix;

	DEBPRINT("total GTF bytes=%u (0x%x), gtf_count=%d, addr=0x%lx\n",
		 gtf_length, gtf_length, gtf_count, gtf_address);

	/* send all taskfile रेजिस्टरs (0x1f1-0x1f7) *in*that*order* */
	क्रम (ix = 0; ix < gtf_count; ix++) अणु
		u8 *gtf = (u8 *)(gtf_address + ix * REGS_PER_GTF);
		काष्ठा ide_cmd cmd;

		DEBPRINT("(0x1f1-1f7): "
			 "hex: %02x %02x %02x %02x %02x %02x %02x\n",
			 gtf[0], gtf[1], gtf[2],
			 gtf[3], gtf[4], gtf[5], gtf[6]);

		अगर (!ide_acpigtf) अणु
			DEBPRINT("_GTF execution disabled\n");
			जारी;
		पूर्ण

		/* convert GTF to taskfile */
		स_रखो(&cmd, 0, माप(cmd));
		स_नकल(&cmd.tf.feature, gtf, REGS_PER_GTF);
		cmd.valid.out.tf = IDE_VALID_OUT_TF | IDE_VALID_DEVICE;
		cmd.valid.in.tf  = IDE_VALID_IN_TF  | IDE_VALID_DEVICE;

		err = ide_no_data_taskfile(drive, &cmd);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "%s: ide_no_data_taskfile failed: %u\n",
					__func__, err);
			rc = err;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/**
 * ide_acpi_exec_tfs - get then ग_लिखो drive taskfile settings
 * @drive: the drive क्रम which the taskfile settings should be
 *         written.
 *
 * According to the ACPI spec this should be called after _STM
 * has been evaluated क्रम the पूर्णांकerface. Some ACPI venकरोrs पूर्णांकerpret
 * that as a hard requirement and modअगरy the taskfile according
 * to the Identअगरy Drive inक्रमmation passed करोwn with _STM.
 * So one should really make sure to call this only after _STM has
 * been executed.
 */
पूर्णांक ide_acpi_exec_tfs(ide_drive_t *drive)
अणु
	पूर्णांक		ret;
	अचिन्हित पूर्णांक	gtf_length;
	अचिन्हित दीर्घ	gtf_address;
	अचिन्हित दीर्घ	obj_loc;

	DEBPRINT("call get_GTF, drive=%s port=%d\n", drive->name, drive->dn);

	ret = करो_drive_get_GTF(drive, &gtf_length, &gtf_address, &obj_loc);
	अगर (ret < 0) अणु
		DEBPRINT("get_GTF error (%d)\n", ret);
		वापस ret;
	पूर्ण

	DEBPRINT("call set_taskfiles, drive=%s\n", drive->name);

	ret = करो_drive_set_taskfiles(drive, gtf_length, gtf_address);
	kमुक्त((व्योम *)obj_loc);
	अगर (ret < 0) अणु
		DEBPRINT("set_taskfiles error (%d)\n", ret);
	पूर्ण

	DEBPRINT("ret=%d\n", ret);

	वापस ret;
पूर्ण

/**
 * ide_acpi_get_timing - get the channel (controller) timings
 * @hwअगर: target IDE पूर्णांकerface (channel)
 *
 * This function executes the _GTM ACPI method क्रम the target channel.
 *
 */
व्योम ide_acpi_get_timing(ide_hwअगर_t *hwअगर)
अणु
	acpi_status		status;
	काष्ठा acpi_buffer	output;
	जोड़ acpi_object 	*out_obj;

	/* Setting up output buffer क्रम _GTM */
	output.length = ACPI_ALLOCATE_BUFFER;
	output.poपूर्णांकer = शून्य;	/* ACPI-CA sets this; save/मुक्त it later */

	/* _GTM has no input parameters */
	status = acpi_evaluate_object(hwअगर->acpidata->obj_handle, "_GTM",
				      शून्य, &output);

	DEBPRINT("_GTM status: %d, outptr: 0x%p, outlen: 0x%llx\n",
		 status, output.poपूर्णांकer,
		 (अचिन्हित दीर्घ दीर्घ)output.length);

	अगर (ACPI_FAILURE(status)) अणु
		DEBPRINT("Run _GTM error: status = 0x%x\n", status);
		वापस;
	पूर्ण

	अगर (!output.length || !output.poपूर्णांकer) अणु
		DEBPRINT("Run _GTM: length or ptr is NULL (0x%llx, 0x%p)\n",
		       (अचिन्हित दीर्घ दीर्घ)output.length,
		       output.poपूर्णांकer);
		kमुक्त(output.poपूर्णांकer);
		वापस;
	पूर्ण

	out_obj = output.poपूर्णांकer;
	अगर (out_obj->type != ACPI_TYPE_BUFFER) अणु
		DEBPRINT("Run _GTM: error: "
		       "expected object type of ACPI_TYPE_BUFFER, "
		       "got 0x%x\n", out_obj->type);
		kमुक्त(output.poपूर्णांकer);
		वापस;
	पूर्ण

	अगर (!out_obj->buffer.length || !out_obj->buffer.poपूर्णांकer ||
	    out_obj->buffer.length != माप(काष्ठा GTM_buffer)) अणु
		prपूर्णांकk(KERN_ERR
			"%s: unexpected _GTM length (0x%x)[should be 0x%zx] or "
			"addr (0x%p)\n",
			__func__, out_obj->buffer.length,
			माप(काष्ठा GTM_buffer), out_obj->buffer.poपूर्णांकer);
		kमुक्त(output.poपूर्णांकer);
		वापस;
	पूर्ण

	स_नकल(&hwअगर->acpidata->gपंचांग, out_obj->buffer.poपूर्णांकer,
	       माप(काष्ठा GTM_buffer));

	DEBPRINT("_GTM info: ptr: 0x%p, len: 0x%x, exp.len: 0x%zx\n",
		 out_obj->buffer.poपूर्णांकer, out_obj->buffer.length,
		 माप(काष्ठा GTM_buffer));

	DEBPRINT("_GTM fields: 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n",
		 hwअगर->acpidata->gपंचांग.PIO_speed0,
		 hwअगर->acpidata->gपंचांग.DMA_speed0,
		 hwअगर->acpidata->gपंचांग.PIO_speed1,
		 hwअगर->acpidata->gपंचांग.DMA_speed1,
		 hwअगर->acpidata->gपंचांग.GTM_flags);

	kमुक्त(output.poपूर्णांकer);
पूर्ण

/**
 * ide_acpi_push_timing - set the channel (controller) timings
 * @hwअगर: target IDE पूर्णांकerface (channel)
 *
 * This function executes the _STM ACPI method क्रम the target channel.
 *
 * _STM requires Identअगरy Drive data, which has to passed as an argument.
 * Unक्रमtunately drive->id is a mangled version which we can't पढ़ोily
 * use; hence we'll get the inक्रमmation afresh.
 */
व्योम ide_acpi_push_timing(ide_hwअगर_t *hwअगर)
अणु
	acpi_status		status;
	काष्ठा acpi_object_list	input;
	जोड़ acpi_object 	in_params[3];
	काष्ठा ide_acpi_drive_link	*master = &hwअगर->acpidata->master;
	काष्ठा ide_acpi_drive_link	*slave = &hwअगर->acpidata->slave;

	/* Give the GTM buffer + drive Identअगरy data to the channel via the
	 * _STM method: */
	/* setup input parameters buffer क्रम _STM */
	input.count = 3;
	input.poपूर्णांकer = in_params;
	in_params[0].type = ACPI_TYPE_BUFFER;
	in_params[0].buffer.length = माप(काष्ठा GTM_buffer);
	in_params[0].buffer.poपूर्णांकer = (u8 *)&hwअगर->acpidata->gपंचांग;
	in_params[1].type = ACPI_TYPE_BUFFER;
	in_params[1].buffer.length = ATA_ID_WORDS * 2;
	in_params[1].buffer.poपूर्णांकer = (u8 *)&master->idbuff;
	in_params[2].type = ACPI_TYPE_BUFFER;
	in_params[2].buffer.length = ATA_ID_WORDS * 2;
	in_params[2].buffer.poपूर्णांकer = (u8 *)&slave->idbuff;
	/* Output buffer: _STM has no output */

	status = acpi_evaluate_object(hwअगर->acpidata->obj_handle, "_STM",
				      &input, शून्य);

	अगर (ACPI_FAILURE(status)) अणु
		DEBPRINT("Run _STM error: status = 0x%x\n", status);
	पूर्ण
	DEBPRINT("_STM status: %d\n", status);
पूर्ण

/**
 * ide_acpi_set_state - set the channel घातer state
 * @hwअगर: target IDE पूर्णांकerface
 * @on: state, on/off
 *
 * This function executes the _PS0/_PS3 ACPI method to set the घातer state.
 * ACPI spec requires _PS0 when IDE घातer on and _PS3 when घातer off
 */
व्योम ide_acpi_set_state(ide_hwअगर_t *hwअगर, पूर्णांक on)
अणु
	ide_drive_t *drive;
	पूर्णांक i;

	अगर (ide_noacpi_psx)
		वापस;

	DEBPRINT("ENTER:\n");

	/* channel first and then drives क्रम घातer on and verse versa क्रम घातer off */
	अगर (on)
		acpi_bus_set_घातer(hwअगर->acpidata->obj_handle, ACPI_STATE_D0);

	ide_port_क्रम_each_present_dev(i, drive, hwअगर) अणु
		अगर (drive->acpidata->obj_handle)
			acpi_bus_set_घातer(drive->acpidata->obj_handle,
				on ? ACPI_STATE_D0 : ACPI_STATE_D3_COLD);
	पूर्ण

	अगर (!on)
		acpi_bus_set_घातer(hwअगर->acpidata->obj_handle,
				   ACPI_STATE_D3_COLD);
पूर्ण

/**
 * ide_acpi_init_port - initialize the ACPI link क्रम an IDE पूर्णांकerface
 * @hwअगर: target IDE पूर्णांकerface (channel)
 *
 * The ACPI spec is not quite clear when the drive identअगरy buffer
 * should be obtained. Calling IDENTIFY DEVICE during shutकरोwn
 * is not the best of ideas as the drive might alपढ़ोy being put to
 * sleep. And obviously we can't call it during resume.
 * So we get the inक्रमmation during startup; but this means that
 * any changes during run-समय will be lost after resume.
 */
व्योम ide_acpi_init_port(ide_hwअगर_t *hwअगर)
अणु
	hwअगर->acpidata = kzalloc(माप(काष्ठा ide_acpi_hwअगर_link), GFP_KERNEL);
	अगर (!hwअगर->acpidata)
		वापस;

	hwअगर->acpidata->obj_handle = ide_acpi_hwअगर_get_handle(hwअगर);
	अगर (!hwअगर->acpidata->obj_handle) अणु
		DEBPRINT("no ACPI object for %s found\n", hwअगर->name);
		kमुक्त(hwअगर->acpidata);
		hwअगर->acpidata = शून्य;
	पूर्ण
पूर्ण

व्योम ide_acpi_port_init_devices(ide_hwअगर_t *hwअगर)
अणु
	ide_drive_t *drive;
	पूर्णांक i, err;

	अगर (hwअगर->acpidata == शून्य)
		वापस;

	/*
	 * The ACPI spec mandates that we send inक्रमmation
	 * क्रम both drives, regardless whether they are connected
	 * or not.
	 */
	hwअगर->devices[0]->acpidata = &hwअगर->acpidata->master;
	hwअगर->devices[1]->acpidata = &hwअगर->acpidata->slave;

	/* get _ADR info क्रम each device */
	ide_port_क्रम_each_present_dev(i, drive, hwअगर) अणु
		acpi_handle dev_handle;

		DEBPRINT("ENTER: %s at channel#: %d port#: %d\n",
			 drive->name, hwअगर->channel, drive->dn & 1);

		/* TBD: could also check ACPI object VALID bits */
		dev_handle = acpi_get_child(hwअगर->acpidata->obj_handle,
					    drive->dn & 1);

		DEBPRINT("drive %s handle 0x%p\n", drive->name, dev_handle);

		drive->acpidata->obj_handle = dev_handle;
	पूर्ण

	/* send IDENTIFY क्रम each device */
	ide_port_क्रम_each_present_dev(i, drive, hwअगर) अणु
		err = taskfile_lib_get_identअगरy(drive, drive->acpidata->idbuff);
		अगर (err)
			DEBPRINT("identify device %s failed (%d)\n",
				 drive->name, err);
	पूर्ण

	अगर (ide_noacpi || ide_acpionboot == 0) अणु
		DEBPRINT("ACPI methods disabled on boot\n");
		वापस;
	पूर्ण

	/* ACPI _PS0 beक्रमe _STM */
	ide_acpi_set_state(hwअगर, 1);
	/*
	 * ACPI requires us to call _STM on startup
	 */
	ide_acpi_get_timing(hwअगर);
	ide_acpi_push_timing(hwअगर);

	ide_port_क्रम_each_present_dev(i, drive, hwअगर) अणु
		ide_acpi_exec_tfs(drive);
	पूर्ण
पूर्ण
