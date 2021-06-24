<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 1994-1998	    Linus Torvalds & authors (see below)
 *  Copyright (C) 2003-2005, 2007   Bartlomiej Zolnierkiewicz
 */

/*
 *  Mostly written by Mark Lord  <mlord@pobox.com>
 *                and Gadi Oxman <gadio@netvision.net.il>
 *                and Andre Hedrick <andre@linux-ide.org>
 *
 *  See linux/MAINTAINERS क्रम address of current मुख्यtainer.
 *
 * This is the multiple IDE पूर्णांकerface driver, as evolved from hd.c.
 * It supports up to MAX_HWIFS IDE पूर्णांकerfaces, on one or more IRQs
 *   (usually 14 & 15).
 * There can be up to two drives per पूर्णांकerface, as per the ATA-2 spec.
 *
 * ...
 *
 *  From hd.c:
 *  |
 *  | It traverses the request-list, using पूर्णांकerrupts to jump between functions.
 *  | As nearly all functions can be called within पूर्णांकerrupts, we may not sleep.
 *  | Special care is recommended.  Have Fun!
 *  |
 *  | modअगरied by Drew Eckhardt to check nr of hd's from the CMOS.
 *  |
 *  | Thanks to Branko Lankester, lankeste@fwi.uva.nl, who found a bug
 *  | in the early extended-partition checks and added DM partitions.
 *  |
 *  | Early work on error handling by Mika Liljeberg (liljeber@cs.Helsinki.FI).
 *  |
 *  | IRQ-unmask, drive-id, multiple-mode, support क्रम ">16 heads",
 *  | and general streamlining by Mark Lord (mlord@pobox.com).
 *
 *  October, 1994 -- Complete line-by-line overhaul क्रम linux 1.1.x, by:
 *
 *	Mark Lord	(mlord@pobox.com)		(IDE Perf.Pkg)
 *	Delman Lee	(delman@ieee.org)		("Mr. atdisk2")
 *	Scott Snyder	(snyder@fnald0.fnal.gov)	(ATAPI IDE cd-rom)
 *
 *  This was a reग_लिखो of just about everything from hd.c, though some original
 *  code is still sprinkled about.  Think of it as a major evolution, with
 *  inspiration from lots of linux users, esp.  hamish@zot.apana.org.au
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/major.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/genhd.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/completion.h>
#समावेश <linux/device.h>

काष्ठा class *ide_port_class;

/**
 * ide_device_get	-	get an additional reference to a ide_drive_t
 * @drive:	device to get a reference to
 *
 * Gets a reference to the ide_drive_t and increments the use count of the
 * underlying LLDD module.
 */
पूर्णांक ide_device_get(ide_drive_t *drive)
अणु
	काष्ठा device *host_dev;
	काष्ठा module *module;

	अगर (!get_device(&drive->gendev))
		वापस -ENXIO;

	host_dev = drive->hwअगर->host->dev[0];
	module = host_dev ? host_dev->driver->owner : शून्य;

	अगर (module && !try_module_get(module)) अणु
		put_device(&drive->gendev);
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ide_device_get);

/**
 * ide_device_put	-	release a reference to a ide_drive_t
 * @drive:	device to release a reference on
 *
 * Release a reference to the ide_drive_t and decrements the use count of
 * the underlying LLDD module.
 */
व्योम ide_device_put(ide_drive_t *drive)
अणु
#अगर_घोषित CONFIG_MODULE_UNLOAD
	काष्ठा device *host_dev = drive->hwअगर->host->dev[0];
	काष्ठा module *module = host_dev ? host_dev->driver->owner : शून्य;

	module_put(module);
#पूर्ण_अगर
	put_device(&drive->gendev);
पूर्ण
EXPORT_SYMBOL_GPL(ide_device_put);

अटल पूर्णांक ide_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक ide_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	ide_drive_t *drive = to_ide_device(dev);

	add_uevent_var(env, "MEDIA=%s", ide_media_string(drive));
	add_uevent_var(env, "DRIVENAME=%s", drive->name);
	add_uevent_var(env, "MODALIAS=ide:m-%s", ide_media_string(drive));
	वापस 0;
पूर्ण

अटल पूर्णांक generic_ide_probe(काष्ठा device *dev)
अणु
	ide_drive_t *drive = to_ide_device(dev);
	काष्ठा ide_driver *drv = to_ide_driver(dev->driver);

	वापस drv->probe ? drv->probe(drive) : -ENODEV;
पूर्ण

अटल पूर्णांक generic_ide_हटाओ(काष्ठा device *dev)
अणु
	ide_drive_t *drive = to_ide_device(dev);
	काष्ठा ide_driver *drv = to_ide_driver(dev->driver);

	अगर (drv->हटाओ)
		drv->हटाओ(drive);

	वापस 0;
पूर्ण

अटल व्योम generic_ide_shutकरोwn(काष्ठा device *dev)
अणु
	ide_drive_t *drive = to_ide_device(dev);
	काष्ठा ide_driver *drv = to_ide_driver(dev->driver);

	अगर (dev->driver && drv->shutकरोwn)
		drv->shutकरोwn(drive);
पूर्ण

काष्ठा bus_type ide_bus_type = अणु
	.name		= "ide",
	.match		= ide_bus_match,
	.uevent		= ide_uevent,
	.probe		= generic_ide_probe,
	.हटाओ		= generic_ide_हटाओ,
	.shutकरोwn	= generic_ide_shutकरोwn,
	.dev_groups	= ide_dev_groups,
	.suspend	= generic_ide_suspend,
	.resume		= generic_ide_resume,
पूर्ण;

EXPORT_SYMBOL_GPL(ide_bus_type);

पूर्णांक ide_vlb_clk;
EXPORT_SYMBOL_GPL(ide_vlb_clk);

module_param_named(vlb_घड़ी, ide_vlb_clk, पूर्णांक, 0);
MODULE_PARM_DESC(vlb_घड़ी, "VLB clock frequency (in MHz)");

पूर्णांक ide_pci_clk;
EXPORT_SYMBOL_GPL(ide_pci_clk);

module_param_named(pci_घड़ी, ide_pci_clk, पूर्णांक, 0);
MODULE_PARM_DESC(pci_घड़ी, "PCI bus clock frequency (in MHz)");

अटल पूर्णांक ide_set_dev_param_mask(स्थिर अक्षर *s, स्थिर काष्ठा kernel_param *kp)
अणु
	अचिन्हित पूर्णांक a, b, i, j = 1;
	अचिन्हित पूर्णांक *dev_param_mask = (अचिन्हित पूर्णांक *)kp->arg;

	/* controller . device (0 or 1) [ : 1 (set) | 0 (clear) ] */
	अगर (माला_पूछो(s, "%u.%u:%u", &a, &b, &j) != 3 &&
	    माला_पूछो(s, "%u.%u", &a, &b) != 2)
		वापस -EINVAL;

	i = a * MAX_DRIVES + b;

	अगर (i >= MAX_HWIFS * MAX_DRIVES || j > 1)
		वापस -EINVAL;

	अगर (j)
		*dev_param_mask |= (1 << i);
	अन्यथा
		*dev_param_mask &= ~(1 << i);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops param_ops_ide_dev_mask = अणु
	.set = ide_set_dev_param_mask
पूर्ण;

#घोषणा param_check_ide_dev_mask(name, p) param_check_uपूर्णांक(name, p)

अटल अचिन्हित पूर्णांक ide_nodma;

module_param_named(nodma, ide_nodma, ide_dev_mask, 0);
MODULE_PARM_DESC(nodma, "disallow DMA for a device");

अटल अचिन्हित पूर्णांक ide_noflush;

module_param_named(noflush, ide_noflush, ide_dev_mask, 0);
MODULE_PARM_DESC(noflush, "disable flush requests for a device");

अटल अचिन्हित पूर्णांक ide_nohpa;

module_param_named(nohpa, ide_nohpa, ide_dev_mask, 0);
MODULE_PARM_DESC(nohpa, "disable Host Protected Area for a device");

अटल अचिन्हित पूर्णांक ide_noprobe;

module_param_named(noprobe, ide_noprobe, ide_dev_mask, 0);
MODULE_PARM_DESC(noprobe, "skip probing for a device");

अटल अचिन्हित पूर्णांक ide_nowerr;

module_param_named(nowerr, ide_nowerr, ide_dev_mask, 0);
MODULE_PARM_DESC(nowerr, "ignore the ATA_DF bit for a device");

अटल अचिन्हित पूर्णांक ide_cdroms;

module_param_named(cdrom, ide_cdroms, ide_dev_mask, 0);
MODULE_PARM_DESC(cdrom, "force device as a CD-ROM");

काष्ठा chs_geom अणु
	अचिन्हित पूर्णांक	cyl;
	u8		head;
	u8		sect;
पूर्ण;

अटल अचिन्हित पूर्णांक ide_disks;
अटल काष्ठा chs_geom ide_disks_chs[MAX_HWIFS * MAX_DRIVES];

अटल पूर्णांक ide_set_disk_chs(स्थिर अक्षर *str, स्थिर काष्ठा kernel_param *kp)
अणु
	अचिन्हित पूर्णांक a, b, c = 0, h = 0, s = 0, i, j = 1;

	/* controller . device (0 or 1) : Cylinders , Heads , Sectors */
	/* controller . device (0 or 1) : 1 (use CHS) | 0 (ignore CHS) */
	अगर (माला_पूछो(str, "%u.%u:%u,%u,%u", &a, &b, &c, &h, &s) != 5 &&
	    माला_पूछो(str, "%u.%u:%u", &a, &b, &j) != 3)
		वापस -EINVAL;

	i = a * MAX_DRIVES + b;

	अगर (i >= MAX_HWIFS * MAX_DRIVES || j > 1)
		वापस -EINVAL;

	अगर (c > पूर्णांक_उच्च || h > 255 || s > 255)
		वापस -EINVAL;

	अगर (j)
		ide_disks |= (1 << i);
	अन्यथा
		ide_disks &= ~(1 << i);

	ide_disks_chs[i].cyl  = c;
	ide_disks_chs[i].head = h;
	ide_disks_chs[i].sect = s;

	वापस 0;
पूर्ण

module_param_call(chs, ide_set_disk_chs, शून्य, शून्य, 0);
MODULE_PARM_DESC(chs, "force device as a disk (using CHS)");

अटल व्योम ide_dev_apply_params(ide_drive_t *drive, u8 unit)
अणु
	पूर्णांक i = drive->hwअगर->index * MAX_DRIVES + unit;

	अगर (ide_nodma & (1 << i)) अणु
		prपूर्णांकk(KERN_INFO "ide: disallowing DMA for %s\n", drive->name);
		drive->dev_flags |= IDE_DFLAG_NODMA;
	पूर्ण
	अगर (ide_noflush & (1 << i)) अणु
		prपूर्णांकk(KERN_INFO "ide: disabling flush requests for %s\n",
				 drive->name);
		drive->dev_flags |= IDE_DFLAG_NOFLUSH;
	पूर्ण
	अगर (ide_nohpa & (1 << i)) अणु
		prपूर्णांकk(KERN_INFO "ide: disabling Host Protected Area for %s\n",
				 drive->name);
		drive->dev_flags |= IDE_DFLAG_NOHPA;
	पूर्ण
	अगर (ide_noprobe & (1 << i)) अणु
		prपूर्णांकk(KERN_INFO "ide: skipping probe for %s\n", drive->name);
		drive->dev_flags |= IDE_DFLAG_NOPROBE;
	पूर्ण
	अगर (ide_nowerr & (1 << i)) अणु
		prपूर्णांकk(KERN_INFO "ide: ignoring the ATA_DF bit for %s\n",
				 drive->name);
		drive->bad_wstat = BAD_R_STAT;
	पूर्ण
	अगर (ide_cdroms & (1 << i)) अणु
		prपूर्णांकk(KERN_INFO "ide: forcing %s as a CD-ROM\n", drive->name);
		drive->dev_flags |= IDE_DFLAG_PRESENT;
		drive->media = ide_cdrom;
		/* an ATAPI device ignores DRDY */
		drive->पढ़ोy_stat = 0;
	पूर्ण
	अगर (ide_disks & (1 << i)) अणु
		drive->cyl  = drive->bios_cyl  = ide_disks_chs[i].cyl;
		drive->head = drive->bios_head = ide_disks_chs[i].head;
		drive->sect = drive->bios_sect = ide_disks_chs[i].sect;

		prपूर्णांकk(KERN_INFO "ide: forcing %s as a disk (%d/%d/%d)\n",
				 drive->name,
				 drive->cyl, drive->head, drive->sect);

		drive->dev_flags |= IDE_DFLAG_FORCED_GEOM | IDE_DFLAG_PRESENT;
		drive->media = ide_disk;
		drive->पढ़ोy_stat = ATA_DRDY;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक ide_ignore_cable;

अटल पूर्णांक ide_set_ignore_cable(स्थिर अक्षर *s, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक i, j = 1;

	/* controller (ignore) */
	/* controller : 1 (ignore) | 0 (use) */
	अगर (माला_पूछो(s, "%d:%d", &i, &j) != 2 && माला_पूछो(s, "%d", &i) != 1)
		वापस -EINVAL;

	अगर (i >= MAX_HWIFS || j < 0 || j > 1)
		वापस -EINVAL;

	अगर (j)
		ide_ignore_cable |= (1 << i);
	अन्यथा
		ide_ignore_cable &= ~(1 << i);

	वापस 0;
पूर्ण

module_param_call(ignore_cable, ide_set_ignore_cable, शून्य, शून्य, 0);
MODULE_PARM_DESC(ignore_cable, "ignore cable detection");

व्योम ide_port_apply_params(ide_hwअगर_t *hwअगर)
अणु
	ide_drive_t *drive;
	पूर्णांक i;

	अगर (ide_ignore_cable & (1 << hwअगर->index)) अणु
		prपूर्णांकk(KERN_INFO "ide: ignoring cable detection for %s\n",
				 hwअगर->name);
		hwअगर->cbl = ATA_CBL_PATA40_SHORT;
	पूर्ण

	ide_port_क्रम_each_dev(i, drive, hwअगर)
		ide_dev_apply_params(drive, i);
पूर्ण

/*
 * This is माला_लो invoked once during initialization, to set *everything* up
 */
अटल पूर्णांक __init ide_init(व्योम)
अणु
	पूर्णांक ret;

	prपूर्णांकk(KERN_INFO "Uniform Multi-Platform E-IDE driver\n");

	ret = bus_रेजिस्टर(&ide_bus_type);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_WARNING "IDE: bus_register error: %d\n", ret);
		वापस ret;
	पूर्ण

	ide_port_class = class_create(THIS_MODULE, "ide_port");
	अगर (IS_ERR(ide_port_class)) अणु
		ret = PTR_ERR(ide_port_class);
		जाओ out_port_class;
	पूर्ण

	ide_acpi_init();

	proc_ide_create();

	वापस 0;

out_port_class:
	bus_unरेजिस्टर(&ide_bus_type);

	वापस ret;
पूर्ण

अटल व्योम __निकास ide_निकास(व्योम)
अणु
	proc_ide_destroy();

	class_destroy(ide_port_class);

	bus_unरेजिस्टर(&ide_bus_type);
पूर्ण

module_init(ide_init);
module_निकास(ide_निकास);

MODULE_LICENSE("GPL");
