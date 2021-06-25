<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * libata-acpi.c
 * Provides ACPI support क्रम PATA/SATA.
 *
 * Copyright (C) 2006 Intel Corp.
 * Copyright (C) 2006 Randy Dunlap
 */

#समावेश <linux/module.h>
#समावेश <linux/ata.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/acpi.h>
#समावेश <linux/libata.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <scsi/scsi_device.h>
#समावेश "libata.h"

अचिन्हित पूर्णांक ata_acpi_gtf_filter = ATA_ACPI_FILTER_DEFAULT;
module_param_named(acpi_gtf_filter, ata_acpi_gtf_filter, पूर्णांक, 0644);
MODULE_PARM_DESC(acpi_gtf_filter, "filter mask for ACPI _GTF commands, set to filter out (0x1=set xfermode, 0x2=lock/freeze lock, 0x4=DIPM, 0x8=FPDMA non-zero offset, 0x10=FPDMA DMA Setup FIS auto-activate)");

#घोषणा NO_PORT_MULT		0xffff
#घोषणा SATA_ADR(root, pmp)	(((root) << 16) | (pmp))

#घोषणा REGS_PER_GTF		7
काष्ठा ata_acpi_gtf अणु
	u8	tf[REGS_PER_GTF];	/* regs. 0x1f1 - 0x1f7 */
पूर्ण __packed;

अटल व्योम ata_acpi_clear_gtf(काष्ठा ata_device *dev)
अणु
	kमुक्त(dev->gtf_cache);
	dev->gtf_cache = शून्य;
पूर्ण

काष्ठा ata_acpi_hotplug_context अणु
	काष्ठा acpi_hotplug_context hp;
	जोड़ अणु
		काष्ठा ata_port *ap;
		काष्ठा ata_device *dev;
	पूर्ण data;
पूर्ण;

#घोषणा ata_hotplug_data(context) (container_of((context), काष्ठा ata_acpi_hotplug_context, hp)->data)

/**
 * ata_dev_acpi_handle - provide the acpi_handle क्रम an ata_device
 * @dev: the acpi_handle वापसed will correspond to this device
 *
 * Returns the acpi_handle क्रम the ACPI namespace object corresponding to
 * the ata_device passed पूर्णांकo the function, or शून्य अगर no such object exists
 * or ACPI is disabled क्रम this device due to consecutive errors.
 */
acpi_handle ata_dev_acpi_handle(काष्ठा ata_device *dev)
अणु
	वापस dev->flags & ATA_DFLAG_ACPI_DISABLED ?
			शून्य : ACPI_HANDLE(&dev->tdev);
पूर्ण

/* @ap and @dev are the same as ata_acpi_handle_hotplug() */
अटल व्योम ata_acpi_detach_device(काष्ठा ata_port *ap, काष्ठा ata_device *dev)
अणु
	अगर (dev)
		dev->flags |= ATA_DFLAG_DETACH;
	अन्यथा अणु
		काष्ठा ata_link *tlink;
		काष्ठा ata_device *tdev;

		ata_क्रम_each_link(tlink, ap, EDGE)
			ata_क्रम_each_dev(tdev, tlink, ALL)
				tdev->flags |= ATA_DFLAG_DETACH;
	पूर्ण

	ata_port_schedule_eh(ap);
पूर्ण

/**
 * ata_acpi_handle_hotplug - ACPI event handler backend
 * @ap: ATA port ACPI event occurred
 * @dev: ATA device ACPI event occurred (can be शून्य)
 * @event: ACPI event which occurred
 *
 * All ACPI bay / device realted events end up in this function.  If
 * the event is port-wide @dev is शून्य.  If the event is specअगरic to a
 * device, @dev poपूर्णांकs to it.
 *
 * Hotplug (as opposed to unplug) notअगरication is always handled as
 * port-wide जबतक unplug only समाप्तs the target device on device-wide
 * event.
 *
 * LOCKING:
 * ACPI notअगरy handler context.  May sleep.
 */
अटल व्योम ata_acpi_handle_hotplug(काष्ठा ata_port *ap, काष्ठा ata_device *dev,
				    u32 event)
अणु
	काष्ठा ata_eh_info *ehi = &ap->link.eh_info;
	पूर्णांक रुको = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(ap->lock, flags);
	/*
	 * When करोck driver calls पूर्णांकo the routine, it will always use
	 * ACPI_NOTIFY_BUS_CHECK/ACPI_NOTIFY_DEVICE_CHECK क्रम add and
	 * ACPI_NOTIFY_EJECT_REQUEST क्रम हटाओ
	 */
	चयन (event) अणु
	हाल ACPI_NOTIFY_BUS_CHECK:
	हाल ACPI_NOTIFY_DEVICE_CHECK:
		ata_ehi_push_desc(ehi, "ACPI event");

		ata_ehi_hotplugged(ehi);
		ata_port_मुक्तze(ap);
		अवरोध;
	हाल ACPI_NOTIFY_EJECT_REQUEST:
		ata_ehi_push_desc(ehi, "ACPI event");

		ata_acpi_detach_device(ap, dev);
		रुको = 1;
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(ap->lock, flags);

	अगर (रुको)
		ata_port_रुको_eh(ap);
पूर्ण

अटल पूर्णांक ata_acpi_dev_notअगरy_करोck(काष्ठा acpi_device *adev, u32 event)
अणु
	काष्ठा ata_device *dev = ata_hotplug_data(adev->hp).dev;
	ata_acpi_handle_hotplug(dev->link->ap, dev, event);
	वापस 0;
पूर्ण

अटल पूर्णांक ata_acpi_ap_notअगरy_करोck(काष्ठा acpi_device *adev, u32 event)
अणु
	ata_acpi_handle_hotplug(ata_hotplug_data(adev->hp).ap, शून्य, event);
	वापस 0;
पूर्ण

अटल व्योम ata_acpi_uevent(काष्ठा ata_port *ap, काष्ठा ata_device *dev,
	u32 event)
अणु
	काष्ठा kobject *kobj = शून्य;
	अक्षर event_string[20];
	अक्षर *envp[] = अणु event_string, शून्य पूर्ण;

	अगर (dev) अणु
		अगर (dev->sdev)
			kobj = &dev->sdev->sdev_gendev.kobj;
	पूर्ण अन्यथा
		kobj = &ap->dev->kobj;

	अगर (kobj) अणु
		snम_लिखो(event_string, 20, "BAY_EVENT=%d", event);
		kobject_uevent_env(kobj, KOBJ_CHANGE, envp);
	पूर्ण
पूर्ण

अटल व्योम ata_acpi_ap_uevent(काष्ठा acpi_device *adev, u32 event)
अणु
	ata_acpi_uevent(ata_hotplug_data(adev->hp).ap, शून्य, event);
पूर्ण

अटल व्योम ata_acpi_dev_uevent(काष्ठा acpi_device *adev, u32 event)
अणु
	काष्ठा ata_device *dev = ata_hotplug_data(adev->hp).dev;
	ata_acpi_uevent(dev->link->ap, dev, event);
पूर्ण

/* bind acpi handle to pata port */
व्योम ata_acpi_bind_port(काष्ठा ata_port *ap)
अणु
	काष्ठा acpi_device *host_companion = ACPI_COMPANION(ap->host->dev);
	काष्ठा acpi_device *adev;
	काष्ठा ata_acpi_hotplug_context *context;

	अगर (libata_noacpi || ap->flags & ATA_FLAG_ACPI_SATA || !host_companion)
		वापस;

	acpi_preset_companion(&ap->tdev, host_companion, ap->port_no);

	अगर (ata_acpi_gपंचांग(ap, &ap->__acpi_init_gपंचांग) == 0)
		ap->pflags |= ATA_PFLAG_INIT_GTM_VALID;

	adev = ACPI_COMPANION(&ap->tdev);
	अगर (!adev || adev->hp)
		वापस;

	context = kzalloc(माप(*context), GFP_KERNEL);
	अगर (!context)
		वापस;

	context->data.ap = ap;
	acpi_initialize_hp_context(adev, &context->hp, ata_acpi_ap_notअगरy_करोck,
				   ata_acpi_ap_uevent);
पूर्ण

व्योम ata_acpi_bind_dev(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_port *ap = dev->link->ap;
	काष्ठा acpi_device *port_companion = ACPI_COMPANION(&ap->tdev);
	काष्ठा acpi_device *host_companion = ACPI_COMPANION(ap->host->dev);
	काष्ठा acpi_device *parent, *adev;
	काष्ठा ata_acpi_hotplug_context *context;
	u64 adr;

	/*
	 * For both sata/pata devices, host companion device is required.
	 * For pata device, port companion device is also required.
	 */
	अगर (libata_noacpi || !host_companion ||
			(!(ap->flags & ATA_FLAG_ACPI_SATA) && !port_companion))
		वापस;

	अगर (ap->flags & ATA_FLAG_ACPI_SATA) अणु
		अगर (!sata_pmp_attached(ap))
			adr = SATA_ADR(ap->port_no, NO_PORT_MULT);
		अन्यथा
			adr = SATA_ADR(ap->port_no, dev->link->pmp);
		parent = host_companion;
	पूर्ण अन्यथा अणु
		adr = dev->devno;
		parent = port_companion;
	पूर्ण

	acpi_preset_companion(&dev->tdev, parent, adr);
	adev = ACPI_COMPANION(&dev->tdev);
	अगर (!adev || adev->hp)
		वापस;

	context = kzalloc(माप(*context), GFP_KERNEL);
	अगर (!context)
		वापस;

	context->data.dev = dev;
	acpi_initialize_hp_context(adev, &context->hp, ata_acpi_dev_notअगरy_करोck,
				   ata_acpi_dev_uevent);
पूर्ण

/**
 * ata_acpi_dissociate - dissociate ATA host from ACPI objects
 * @host: target ATA host
 *
 * This function is called during driver detach after the whole host
 * is shut करोwn.
 *
 * LOCKING:
 * EH context.
 */
व्योम ata_acpi_dissociate(काष्ठा ata_host *host)
अणु
	पूर्णांक i;

	/* Restore initial _GTM values so that driver which attaches
	 * afterward can use them too.
	 */
	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];
		स्थिर काष्ठा ata_acpi_gपंचांग *gपंचांग = ata_acpi_init_gपंचांग(ap);

		अगर (ACPI_HANDLE(&ap->tdev) && gपंचांग)
			ata_acpi_sपंचांग(ap, gपंचांग);
	पूर्ण
पूर्ण

/**
 * ata_acpi_gपंचांग - execute _GTM
 * @ap: target ATA port
 * @gपंचांग: out parameter क्रम _GTM result
 *
 * Evaluate _GTM and store the result in @gपंचांग.
 *
 * LOCKING:
 * EH context.
 *
 * RETURNS:
 * 0 on success, -ENOENT अगर _GTM करोesn't exist, -त्रुटि_सं on failure.
 */
पूर्णांक ata_acpi_gपंचांग(काष्ठा ata_port *ap, काष्ठा ata_acpi_gपंचांग *gपंचांग)
अणु
	काष्ठा acpi_buffer output = अणु .length = ACPI_ALLOCATE_BUFFER पूर्ण;
	जोड़ acpi_object *out_obj;
	acpi_status status;
	पूर्णांक rc = 0;
	acpi_handle handle = ACPI_HANDLE(&ap->tdev);

	अगर (!handle)
		वापस -EINVAL;

	status = acpi_evaluate_object(handle, "_GTM", शून्य, &output);

	rc = -ENOENT;
	अगर (status == AE_NOT_FOUND)
		जाओ out_मुक्त;

	rc = -EINVAL;
	अगर (ACPI_FAILURE(status)) अणु
		ata_port_err(ap, "ACPI get timing mode failed (AE 0x%x)\n",
			     status);
		जाओ out_मुक्त;
	पूर्ण

	out_obj = output.poपूर्णांकer;
	अगर (out_obj->type != ACPI_TYPE_BUFFER) अणु
		ata_port_warn(ap, "_GTM returned unexpected object type 0x%x\n",
			      out_obj->type);

		जाओ out_मुक्त;
	पूर्ण

	अगर (out_obj->buffer.length != माप(काष्ठा ata_acpi_gपंचांग)) अणु
		ata_port_err(ap, "_GTM returned invalid length %d\n",
			     out_obj->buffer.length);
		जाओ out_मुक्त;
	पूर्ण

	स_नकल(gपंचांग, out_obj->buffer.poपूर्णांकer, माप(काष्ठा ata_acpi_gपंचांग));
	rc = 0;
 out_मुक्त:
	kमुक्त(output.poपूर्णांकer);
	वापस rc;
पूर्ण

EXPORT_SYMBOL_GPL(ata_acpi_gपंचांग);

/**
 * ata_acpi_sपंचांग - execute _STM
 * @ap: target ATA port
 * @sपंचांग: timing parameter to _STM
 *
 * Evaluate _STM with timing parameter @sपंचांग.
 *
 * LOCKING:
 * EH context.
 *
 * RETURNS:
 * 0 on success, -ENOENT अगर _STM करोesn't exist, -त्रुटि_सं on failure.
 */
पूर्णांक ata_acpi_sपंचांग(काष्ठा ata_port *ap, स्थिर काष्ठा ata_acpi_gपंचांग *sपंचांग)
अणु
	acpi_status status;
	काष्ठा ata_acpi_gपंचांग		sपंचांग_buf = *sपंचांग;
	काष्ठा acpi_object_list         input;
	जोड़ acpi_object               in_params[3];

	in_params[0].type = ACPI_TYPE_BUFFER;
	in_params[0].buffer.length = माप(काष्ठा ata_acpi_gपंचांग);
	in_params[0].buffer.poपूर्णांकer = (u8 *)&sपंचांग_buf;
	/* Buffers क्रम id may need byteswapping ? */
	in_params[1].type = ACPI_TYPE_BUFFER;
	in_params[1].buffer.length = 512;
	in_params[1].buffer.poपूर्णांकer = (u8 *)ap->link.device[0].id;
	in_params[2].type = ACPI_TYPE_BUFFER;
	in_params[2].buffer.length = 512;
	in_params[2].buffer.poपूर्णांकer = (u8 *)ap->link.device[1].id;

	input.count = 3;
	input.poपूर्णांकer = in_params;

	status = acpi_evaluate_object(ACPI_HANDLE(&ap->tdev), "_STM",
				      &input, शून्य);

	अगर (status == AE_NOT_FOUND)
		वापस -ENOENT;
	अगर (ACPI_FAILURE(status)) अणु
		ata_port_err(ap, "ACPI set timing mode failed (status=0x%x)\n",
			     status);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

EXPORT_SYMBOL_GPL(ata_acpi_sपंचांग);

/**
 * ata_dev_get_GTF - get the drive bootup शेष taskfile settings
 * @dev: target ATA device
 * @gtf: output parameter क्रम buffer containing _GTF taskfile arrays
 *
 * This applies to both PATA and SATA drives.
 *
 * The _GTF method has no input parameters.
 * It वापसs a variable number of रेजिस्टर set values (रेजिस्टरs
 * hex 1F1..1F7, taskfiles).
 * The <variable number> is not known in advance, so have ACPI-CA
 * allocate the buffer as needed and वापस it, then मुक्त it later.
 *
 * LOCKING:
 * EH context.
 *
 * RETURNS:
 * Number of taskfiles on success, 0 अगर _GTF करोesn't exist.  -EINVAL
 * अगर _GTF is invalid.
 */
अटल पूर्णांक ata_dev_get_GTF(काष्ठा ata_device *dev, काष्ठा ata_acpi_gtf **gtf)
अणु
	काष्ठा ata_port *ap = dev->link->ap;
	acpi_status status;
	काष्ठा acpi_buffer output;
	जोड़ acpi_object *out_obj;
	पूर्णांक rc = 0;

	/* अगर _GTF is cached, use the cached value */
	अगर (dev->gtf_cache) अणु
		out_obj = dev->gtf_cache;
		जाओ करोne;
	पूर्ण

	/* set up output buffer */
	output.length = ACPI_ALLOCATE_BUFFER;
	output.poपूर्णांकer = शून्य;	/* ACPI-CA sets this; save/मुक्त it later */

	अगर (ata_msg_probe(ap))
		ata_dev_dbg(dev, "%s: ENTER: port#: %d\n",
			    __func__, ap->port_no);

	/* _GTF has no input parameters */
	status = acpi_evaluate_object(ata_dev_acpi_handle(dev), "_GTF", शून्य,
				      &output);
	out_obj = dev->gtf_cache = output.poपूर्णांकer;

	अगर (ACPI_FAILURE(status)) अणु
		अगर (status != AE_NOT_FOUND) अणु
			ata_dev_warn(dev, "_GTF evaluation failed (AE 0x%x)\n",
				     status);
			rc = -EINVAL;
		पूर्ण
		जाओ out_मुक्त;
	पूर्ण

	अगर (!output.length || !output.poपूर्णांकer) अणु
		अगर (ata_msg_probe(ap))
			ata_dev_dbg(dev, "%s: Run _GTF: length or ptr is NULL (0x%llx, 0x%p)\n",
				    __func__,
				    (अचिन्हित दीर्घ दीर्घ)output.length,
				    output.poपूर्णांकer);
		rc = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	अगर (out_obj->type != ACPI_TYPE_BUFFER) अणु
		ata_dev_warn(dev, "_GTF unexpected object type 0x%x\n",
			     out_obj->type);
		rc = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	अगर (out_obj->buffer.length % REGS_PER_GTF) अणु
		ata_dev_warn(dev, "unexpected _GTF length (%d)\n",
			     out_obj->buffer.length);
		rc = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

 करोne:
	rc = out_obj->buffer.length / REGS_PER_GTF;
	अगर (gtf) अणु
		*gtf = (व्योम *)out_obj->buffer.poपूर्णांकer;
		अगर (ata_msg_probe(ap))
			ata_dev_dbg(dev, "%s: returning gtf=%p, gtf_count=%d\n",
				    __func__, *gtf, rc);
	पूर्ण
	वापस rc;

 out_मुक्त:
	ata_acpi_clear_gtf(dev);
	वापस rc;
पूर्ण

/**
 * ata_acpi_gपंचांग_xfermask - determine xfermode from GTM parameter
 * @dev: target device
 * @gपंचांग: GTM parameter to use
 *
 * Determine xfermask क्रम @dev from @gपंचांग.
 *
 * LOCKING:
 * None.
 *
 * RETURNS:
 * Determined xfermask.
 */
अचिन्हित दीर्घ ata_acpi_gपंचांग_xfermask(काष्ठा ata_device *dev,
				    स्थिर काष्ठा ata_acpi_gपंचांग *gपंचांग)
अणु
	अचिन्हित दीर्घ xfer_mask = 0;
	अचिन्हित पूर्णांक type;
	पूर्णांक unit;
	u8 mode;

	/* we always use the 0 slot क्रम crap hardware */
	unit = dev->devno;
	अगर (!(gपंचांग->flags & 0x10))
		unit = 0;

	/* PIO */
	mode = ata_timing_cycle2mode(ATA_SHIFT_PIO, gपंचांग->drive[unit].pio);
	xfer_mask |= ata_xfer_mode2mask(mode);

	/* See अगर we have MWDMA or UDMA data. We करोn't bother with
	 * MWDMA अगर UDMA is available as this means the BIOS set UDMA
	 * and our error changeकरोwn अगर it works is UDMA to PIO anyway.
	 */
	अगर (!(gपंचांग->flags & (1 << (2 * unit))))
		type = ATA_SHIFT_MWDMA;
	अन्यथा
		type = ATA_SHIFT_UDMA;

	mode = ata_timing_cycle2mode(type, gपंचांग->drive[unit].dma);
	xfer_mask |= ata_xfer_mode2mask(mode);

	वापस xfer_mask;
पूर्ण
EXPORT_SYMBOL_GPL(ata_acpi_gपंचांग_xfermask);

/**
 * ata_acpi_cbl_80wire		-	Check क्रम 80 wire cable
 * @ap: Port to check
 * @gपंचांग: GTM data to use
 *
 * Return 1 अगर the @gपंचांग indicates the BIOS selected an 80wire mode.
 */
पूर्णांक ata_acpi_cbl_80wire(काष्ठा ata_port *ap, स्थिर काष्ठा ata_acpi_gपंचांग *gपंचांग)
अणु
	काष्ठा ata_device *dev;

	ata_क्रम_each_dev(dev, &ap->link, ENABLED) अणु
		अचिन्हित दीर्घ xfer_mask, udma_mask;

		xfer_mask = ata_acpi_gपंचांग_xfermask(dev, gपंचांग);
		ata_unpack_xfermask(xfer_mask, शून्य, शून्य, &udma_mask);

		अगर (udma_mask & ~ATA_UDMA_MASK_40C)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_acpi_cbl_80wire);

अटल व्योम ata_acpi_gtf_to_tf(काष्ठा ata_device *dev,
			       स्थिर काष्ठा ata_acpi_gtf *gtf,
			       काष्ठा ata_taskfile *tf)
अणु
	ata_tf_init(dev, tf);

	tf->flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE;
	tf->protocol = ATA_PROT_NODATA;
	tf->feature = gtf->tf[0];	/* 0x1f1 */
	tf->nsect   = gtf->tf[1];	/* 0x1f2 */
	tf->lbal    = gtf->tf[2];	/* 0x1f3 */
	tf->lbam    = gtf->tf[3];	/* 0x1f4 */
	tf->lbah    = gtf->tf[4];	/* 0x1f5 */
	tf->device  = gtf->tf[5];	/* 0x1f6 */
	tf->command = gtf->tf[6];	/* 0x1f7 */
पूर्ण

अटल पूर्णांक ata_acpi_filter_tf(काष्ठा ata_device *dev,
			      स्थिर काष्ठा ata_taskfile *tf,
			      स्थिर काष्ठा ata_taskfile *ptf)
अणु
	अगर (dev->gtf_filter & ATA_ACPI_FILTER_SETXFER) अणु
		/* libata करोesn't use ACPI to configure transfer mode.
		 * It will only confuse device configuration.  Skip.
		 */
		अगर (tf->command == ATA_CMD_SET_FEATURES &&
		    tf->feature == SETFEATURES_XFER)
			वापस 1;
	पूर्ण

	अगर (dev->gtf_filter & ATA_ACPI_FILTER_LOCK) अणु
		/* BIOS ग_लिखोrs, sorry but we करोn't wanna lock
		 * features unless the user explicitly said so.
		 */

		/* DEVICE CONFIGURATION FREEZE LOCK */
		अगर (tf->command == ATA_CMD_CONF_OVERLAY &&
		    tf->feature == ATA_DCO_FREEZE_LOCK)
			वापस 1;

		/* SECURITY FREEZE LOCK */
		अगर (tf->command == ATA_CMD_SEC_FREEZE_LOCK)
			वापस 1;

		/* SET MAX LOCK and SET MAX FREEZE LOCK */
		अगर ((!ptf || ptf->command != ATA_CMD_READ_NATIVE_MAX) &&
		    tf->command == ATA_CMD_SET_MAX &&
		    (tf->feature == ATA_SET_MAX_LOCK ||
		     tf->feature == ATA_SET_MAX_FREEZE_LOCK))
			वापस 1;
	पूर्ण

	अगर (tf->command == ATA_CMD_SET_FEATURES &&
	    tf->feature == SETFEATURES_SATA_ENABLE) अणु
		/* inhibit enabling DIPM */
		अगर (dev->gtf_filter & ATA_ACPI_FILTER_DIPM &&
		    tf->nsect == SATA_DIPM)
			वापस 1;

		/* inhibit FPDMA non-zero offset */
		अगर (dev->gtf_filter & ATA_ACPI_FILTER_FPDMA_OFFSET &&
		    (tf->nsect == SATA_FPDMA_OFFSET ||
		     tf->nsect == SATA_FPDMA_IN_ORDER))
			वापस 1;

		/* inhibit FPDMA स्वतः activation */
		अगर (dev->gtf_filter & ATA_ACPI_FILTER_FPDMA_AA &&
		    tf->nsect == SATA_FPDMA_AA)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ata_acpi_run_tf - send taskfile रेजिस्टरs to host controller
 * @dev: target ATA device
 * @gtf: raw ATA taskfile रेजिस्टर set (0x1f1 - 0x1f7)
 * @prev_gtf: previous command
 *
 * Outमाला_दो ATA taskfile to standard ATA host controller.
 * Writes the control, feature, nsect, lbal, lbam, and lbah रेजिस्टरs.
 * Optionally (ATA_TFLAG_LBA48) ग_लिखोs hob_feature, hob_nsect,
 * hob_lbal, hob_lbam, and hob_lbah.
 *
 * This function रुकोs क्रम idle (!BUSY and !DRQ) after writing
 * रेजिस्टरs.  If the control रेजिस्टर has a new value, this
 * function also रुकोs क्रम idle after writing control and beक्रमe
 * writing the reमुख्यing रेजिस्टरs.
 *
 * LOCKING:
 * EH context.
 *
 * RETURNS:
 * 1 अगर command is executed successfully.  0 अगर ignored, rejected or
 * filtered out, -त्रुटि_सं on other errors.
 */
अटल पूर्णांक ata_acpi_run_tf(काष्ठा ata_device *dev,
			   स्थिर काष्ठा ata_acpi_gtf *gtf,
			   स्थिर काष्ठा ata_acpi_gtf *prev_gtf)
अणु
	काष्ठा ata_taskfile *pptf = शून्य;
	काष्ठा ata_taskfile tf, ptf, rtf;
	अचिन्हित पूर्णांक err_mask;
	स्थिर अक्षर *level;
	स्थिर अक्षर *descr;
	अक्षर msg[60];
	पूर्णांक rc;

	अगर ((gtf->tf[0] == 0) && (gtf->tf[1] == 0) && (gtf->tf[2] == 0)
	    && (gtf->tf[3] == 0) && (gtf->tf[4] == 0) && (gtf->tf[5] == 0)
	    && (gtf->tf[6] == 0))
		वापस 0;

	ata_acpi_gtf_to_tf(dev, gtf, &tf);
	अगर (prev_gtf) अणु
		ata_acpi_gtf_to_tf(dev, prev_gtf, &ptf);
		pptf = &ptf;
	पूर्ण

	अगर (!ata_acpi_filter_tf(dev, &tf, pptf)) अणु
		rtf = tf;
		err_mask = ata_exec_पूर्णांकernal(dev, &rtf, शून्य,
					     DMA_NONE, शून्य, 0, 0);

		चयन (err_mask) अणु
		हाल 0:
			level = KERN_DEBUG;
			snम_लिखो(msg, माप(msg), "succeeded");
			rc = 1;
			अवरोध;

		हाल AC_ERR_DEV:
			level = KERN_INFO;
			snम_लिखो(msg, माप(msg),
				 "rejected by device (Stat=0x%02x Err=0x%02x)",
				 rtf.command, rtf.feature);
			rc = 0;
			अवरोध;

		शेष:
			level = KERN_ERR;
			snम_लिखो(msg, माप(msg),
				 "failed (Emask=0x%x Stat=0x%02x Err=0x%02x)",
				 err_mask, rtf.command, rtf.feature);
			rc = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		level = KERN_INFO;
		snम_लिखो(msg, माप(msg), "filtered out");
		rc = 0;
	पूर्ण
	descr = ata_get_cmd_descript(tf.command);

	ata_dev_prपूर्णांकk(dev, level,
		       "ACPI cmd %02x/%02x:%02x:%02x:%02x:%02x:%02x (%s) %s\n",
		       tf.command, tf.feature, tf.nsect, tf.lbal,
		       tf.lbam, tf.lbah, tf.device,
		       (descr ? descr : "unknown"), msg);

	वापस rc;
पूर्ण

/**
 * ata_acpi_exec_tfs - get then ग_लिखो drive taskfile settings
 * @dev: target ATA device
 * @nr_executed: out parameter क्रम the number of executed commands
 *
 * Evaluate _GTF and execute वापसed taskfiles.
 *
 * LOCKING:
 * EH context.
 *
 * RETURNS:
 * Number of executed taskfiles on success, 0 अगर _GTF करोesn't exist.
 * -त्रुटि_सं on other errors.
 */
अटल पूर्णांक ata_acpi_exec_tfs(काष्ठा ata_device *dev, पूर्णांक *nr_executed)
अणु
	काष्ठा ata_acpi_gtf *gtf = शून्य, *pgtf = शून्य;
	पूर्णांक gtf_count, i, rc;

	/* get taskfiles */
	rc = ata_dev_get_GTF(dev, &gtf);
	अगर (rc < 0)
		वापस rc;
	gtf_count = rc;

	/* execute them */
	क्रम (i = 0; i < gtf_count; i++, gtf++) अणु
		rc = ata_acpi_run_tf(dev, gtf, pgtf);
		अगर (rc < 0)
			अवरोध;
		अगर (rc) अणु
			(*nr_executed)++;
			pgtf = gtf;
		पूर्ण
	पूर्ण

	ata_acpi_clear_gtf(dev);

	अगर (rc < 0)
		वापस rc;
	वापस 0;
पूर्ण

/**
 * ata_acpi_push_id - send Identअगरy data to drive
 * @dev: target ATA device
 *
 * _SDD ACPI object: क्रम SATA mode only
 * Must be after Identअगरy (Packet) Device -- uses its data
 * ATM this function never वापसs a failure.  It is an optional
 * method and अगर it fails क्रम whatever reason, we should still
 * just keep going.
 *
 * LOCKING:
 * EH context.
 *
 * RETURNS:
 * 0 on success, -ENOENT अगर _SDD करोesn't exist, -त्रुटि_सं on failure.
 */
अटल पूर्णांक ata_acpi_push_id(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_port *ap = dev->link->ap;
	acpi_status status;
	काष्ठा acpi_object_list input;
	जोड़ acpi_object in_params[1];

	अगर (ata_msg_probe(ap))
		ata_dev_dbg(dev, "%s: ix = %d, port#: %d\n",
			    __func__, dev->devno, ap->port_no);

	/* Give the drive Identअगरy data to the drive via the _SDD method */
	/* _SDD: set up input parameters */
	input.count = 1;
	input.poपूर्णांकer = in_params;
	in_params[0].type = ACPI_TYPE_BUFFER;
	in_params[0].buffer.length = माप(dev->id[0]) * ATA_ID_WORDS;
	in_params[0].buffer.poपूर्णांकer = (u8 *)dev->id;
	/* Output buffer: _SDD has no output */

	/* It's OK क्रम _SDD to be missing too. */
	swap_buf_le16(dev->id, ATA_ID_WORDS);
	status = acpi_evaluate_object(ata_dev_acpi_handle(dev), "_SDD", &input,
				      शून्य);
	swap_buf_le16(dev->id, ATA_ID_WORDS);

	अगर (status == AE_NOT_FOUND)
		वापस -ENOENT;

	अगर (ACPI_FAILURE(status)) अणु
		ata_dev_warn(dev, "ACPI _SDD failed (AE 0x%x)\n", status);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ata_acpi_on_suspend - ATA ACPI hook called on suspend
 * @ap: target ATA port
 *
 * This function is called when @ap is about to be suspended.  All
 * devices are alपढ़ोy put to sleep but the port_suspend() callback
 * hasn't been executed yet.  Error वापस from this function पातs
 * suspend.
 *
 * LOCKING:
 * EH context.
 *
 * RETURNS:
 * 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक ata_acpi_on_suspend(काष्ठा ata_port *ap)
अणु
	/* nada */
	वापस 0;
पूर्ण

/**
 * ata_acpi_on_resume - ATA ACPI hook called on resume
 * @ap: target ATA port
 *
 * This function is called when @ap is resumed - right after port
 * itself is resumed but beक्रमe any EH action is taken.
 *
 * LOCKING:
 * EH context.
 */
व्योम ata_acpi_on_resume(काष्ठा ata_port *ap)
अणु
	स्थिर काष्ठा ata_acpi_gपंचांग *gपंचांग = ata_acpi_init_gपंचांग(ap);
	काष्ठा ata_device *dev;

	अगर (ACPI_HANDLE(&ap->tdev) && gपंचांग) अणु
		/* _GTM valid */

		/* restore timing parameters */
		ata_acpi_sपंचांग(ap, gपंचांग);

		/* _GTF should immediately follow _STM so that it can
		 * use values set by _STM.  Cache _GTF result and
		 * schedule _GTF.
		 */
		ata_क्रम_each_dev(dev, &ap->link, ALL) अणु
			ata_acpi_clear_gtf(dev);
			अगर (ata_dev_enabled(dev) &&
			    ata_dev_acpi_handle(dev) &&
			    ata_dev_get_GTF(dev, शून्य) >= 0)
				dev->flags |= ATA_DFLAG_ACPI_PENDING;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* SATA _GTF needs to be evaulated after _SDD and
		 * there's no reason to evaluate IDE _GTF early
		 * without _STM.  Clear cache and schedule _GTF.
		 */
		ata_क्रम_each_dev(dev, &ap->link, ALL) अणु
			ata_acpi_clear_gtf(dev);
			अगर (ata_dev_enabled(dev))
				dev->flags |= ATA_DFLAG_ACPI_PENDING;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ata_acpi_choose_suspend_state(काष्ठा ata_device *dev, bool runसमय)
अणु
	पूर्णांक d_max_in = ACPI_STATE_D3_COLD;
	अगर (!runसमय)
		जाओ out;

	/*
	 * For ATAPI, runसमय D3 cold is only allowed
	 * क्रम ZPODD in zero घातer पढ़ोy state
	 */
	अगर (dev->class == ATA_DEV_ATAPI &&
	    !(zpodd_dev_enabled(dev) && zpodd_zpपढ़ोy(dev)))
		d_max_in = ACPI_STATE_D3_HOT;

out:
	वापस acpi_pm_device_sleep_state(&dev->tdev, शून्य, d_max_in);
पूर्ण

अटल व्योम sata_acpi_set_state(काष्ठा ata_port *ap, pm_message_t state)
अणु
	bool runसमय = PMSG_IS_AUTO(state);
	काष्ठा ata_device *dev;
	acpi_handle handle;
	पूर्णांक acpi_state;

	ata_क्रम_each_dev(dev, &ap->link, ENABLED) अणु
		handle = ata_dev_acpi_handle(dev);
		अगर (!handle)
			जारी;

		अगर (!(state.event & PM_EVENT_RESUME)) अणु
			acpi_state = ata_acpi_choose_suspend_state(dev, runसमय);
			अगर (acpi_state == ACPI_STATE_D0)
				जारी;
			अगर (runसमय && zpodd_dev_enabled(dev) &&
			    acpi_state == ACPI_STATE_D3_COLD)
				zpodd_enable_run_wake(dev);
			acpi_bus_set_घातer(handle, acpi_state);
		पूर्ण अन्यथा अणु
			अगर (runसमय && zpodd_dev_enabled(dev))
				zpodd_disable_run_wake(dev);
			acpi_bus_set_घातer(handle, ACPI_STATE_D0);
		पूर्ण
	पूर्ण
पूर्ण

/* ACPI spec requires _PS0 when IDE घातer on and _PS3 when घातer off */
अटल व्योम pata_acpi_set_state(काष्ठा ata_port *ap, pm_message_t state)
अणु
	काष्ठा ata_device *dev;
	acpi_handle port_handle;

	port_handle = ACPI_HANDLE(&ap->tdev);
	अगर (!port_handle)
		वापस;

	/* channel first and then drives क्रम घातer on and vica versa
	   क्रम घातer off */
	अगर (state.event & PM_EVENT_RESUME)
		acpi_bus_set_घातer(port_handle, ACPI_STATE_D0);

	ata_क्रम_each_dev(dev, &ap->link, ENABLED) अणु
		acpi_handle dev_handle = ata_dev_acpi_handle(dev);
		अगर (!dev_handle)
			जारी;

		acpi_bus_set_घातer(dev_handle, state.event & PM_EVENT_RESUME ?
					ACPI_STATE_D0 : ACPI_STATE_D3_COLD);
	पूर्ण

	अगर (!(state.event & PM_EVENT_RESUME))
		acpi_bus_set_घातer(port_handle, ACPI_STATE_D3_COLD);
पूर्ण

/**
 * ata_acpi_set_state - set the port घातer state
 * @ap: target ATA port
 * @state: state, on/off
 *
 * This function sets a proper ACPI D state क्रम the device on
 * प्रणाली and runसमय PM operations.
 */
व्योम ata_acpi_set_state(काष्ठा ata_port *ap, pm_message_t state)
अणु
	अगर (ap->flags & ATA_FLAG_ACPI_SATA)
		sata_acpi_set_state(ap, state);
	अन्यथा
		pata_acpi_set_state(ap, state);
पूर्ण

/**
 * ata_acpi_on_devcfg - ATA ACPI hook called on device करोnfiguration
 * @dev: target ATA device
 *
 * This function is called when @dev is about to be configured.
 * IDENTIFY data might have been modअगरied after this hook is run.
 *
 * LOCKING:
 * EH context.
 *
 * RETURNS:
 * Positive number अगर IDENTIFY data needs to be refreshed, 0 अगर not,
 * -त्रुटि_सं on failure.
 */
पूर्णांक ata_acpi_on_devcfg(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_port *ap = dev->link->ap;
	काष्ठा ata_eh_context *ehc = &ap->link.eh_context;
	पूर्णांक acpi_sata = ap->flags & ATA_FLAG_ACPI_SATA;
	पूर्णांक nr_executed = 0;
	पूर्णांक rc;

	अगर (!ata_dev_acpi_handle(dev))
		वापस 0;

	/* करो we need to करो _GTF? */
	अगर (!(dev->flags & ATA_DFLAG_ACPI_PENDING) &&
	    !(acpi_sata && (ehc->i.flags & ATA_EHI_DID_HARDRESET)))
		वापस 0;

	/* करो _SDD अगर SATA */
	अगर (acpi_sata) अणु
		rc = ata_acpi_push_id(dev);
		अगर (rc && rc != -ENOENT)
			जाओ acpi_err;
	पूर्ण

	/* करो _GTF */
	rc = ata_acpi_exec_tfs(dev, &nr_executed);
	अगर (rc)
		जाओ acpi_err;

	dev->flags &= ~ATA_DFLAG_ACPI_PENDING;

	/* refresh IDENTIFY page अगर any _GTF command has been executed */
	अगर (nr_executed) अणु
		rc = ata_dev_reपढ़ो_id(dev, 0);
		अगर (rc < 0) अणु
			ata_dev_err(dev,
				    "failed to IDENTIFY after ACPI commands\n");
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;

 acpi_err:
	/* ignore evaluation failure अगर we can जारी safely */
	अगर (rc == -EINVAL && !nr_executed && !(ap->pflags & ATA_PFLAG_FROZEN))
		वापस 0;

	/* fail and let EH retry once more क्रम unknown IO errors */
	अगर (!(dev->flags & ATA_DFLAG_ACPI_FAILED)) अणु
		dev->flags |= ATA_DFLAG_ACPI_FAILED;
		वापस rc;
	पूर्ण

	dev->flags |= ATA_DFLAG_ACPI_DISABLED;
	ata_dev_warn(dev, "ACPI: failed the second time, disabled\n");

	/* We can safely जारी अगर no _GTF command has been executed
	 * and port is not frozen.
	 */
	अगर (!nr_executed && !(ap->pflags & ATA_PFLAG_FROZEN))
		वापस 0;

	वापस rc;
पूर्ण

/**
 * ata_acpi_on_disable - ATA ACPI hook called when a device is disabled
 * @dev: target ATA device
 *
 * This function is called when @dev is about to be disabled.
 *
 * LOCKING:
 * EH context.
 */
व्योम ata_acpi_on_disable(काष्ठा ata_device *dev)
अणु
	ata_acpi_clear_gtf(dev);
पूर्ण
