<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/genhd.h>
#समावेश <linux/mutex.h>
#समावेश <linux/ide.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/dmi.h>
#समावेश <linux/slab.h>

#अगर !defined(CONFIG_DEBUG_BLOCK_EXT_DEVT)
#घोषणा IDE_DISK_MINORS		(1 << PARTN_BITS)
#अन्यथा
#घोषणा IDE_DISK_MINORS		0
#पूर्ण_अगर

#समावेश "ide-disk.h"
#समावेश "ide-floppy.h"

#घोषणा IDE_GD_VERSION	"1.18"

/* module parameters */
अटल DEFINE_MUTEX(ide_gd_mutex);
अटल अचिन्हित दीर्घ debug_mask;
module_param(debug_mask, uदीर्घ, 0644);

अटल DEFINE_MUTEX(ide_disk_ref_mutex);

अटल व्योम ide_disk_release(काष्ठा device *);

अटल काष्ठा ide_disk_obj *ide_disk_get(काष्ठा gendisk *disk)
अणु
	काष्ठा ide_disk_obj *idkp = शून्य;

	mutex_lock(&ide_disk_ref_mutex);
	idkp = ide_drv_g(disk, ide_disk_obj);
	अगर (idkp) अणु
		अगर (ide_device_get(idkp->drive))
			idkp = शून्य;
		अन्यथा
			get_device(&idkp->dev);
	पूर्ण
	mutex_unlock(&ide_disk_ref_mutex);
	वापस idkp;
पूर्ण

अटल व्योम ide_disk_put(काष्ठा ide_disk_obj *idkp)
अणु
	ide_drive_t *drive = idkp->drive;

	mutex_lock(&ide_disk_ref_mutex);
	put_device(&idkp->dev);
	ide_device_put(drive);
	mutex_unlock(&ide_disk_ref_mutex);
पूर्ण

sector_t ide_gd_capacity(ide_drive_t *drive)
अणु
	वापस drive->capacity64;
पूर्ण

अटल पूर्णांक ide_gd_probe(ide_drive_t *);

अटल व्योम ide_gd_हटाओ(ide_drive_t *drive)
अणु
	काष्ठा ide_disk_obj *idkp = drive->driver_data;
	काष्ठा gendisk *g = idkp->disk;

	ide_proc_unरेजिस्टर_driver(drive, idkp->driver);
	device_del(&idkp->dev);
	del_gendisk(g);
	drive->disk_ops->flush(drive);

	mutex_lock(&ide_disk_ref_mutex);
	put_device(&idkp->dev);
	mutex_unlock(&ide_disk_ref_mutex);
पूर्ण

अटल व्योम ide_disk_release(काष्ठा device *dev)
अणु
	काष्ठा ide_disk_obj *idkp = to_ide_drv(dev, ide_disk_obj);
	ide_drive_t *drive = idkp->drive;
	काष्ठा gendisk *g = idkp->disk;

	drive->disk_ops = शून्य;
	drive->driver_data = शून्य;
	g->निजी_data = शून्य;
	put_disk(g);
	kमुक्त(idkp);
पूर्ण

/*
 * On HPA drives the capacity needs to be
 * reinitialized on resume otherwise the disk
 * can not be used and a hard reset is required
 */
अटल व्योम ide_gd_resume(ide_drive_t *drive)
अणु
	अगर (ata_id_hpa_enabled(drive->id))
		(व्योम)drive->disk_ops->get_capacity(drive);
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id ide_coldreboot_table[] = अणु
	अणु
		/* Acer TravelMate 66x cuts घातer during reboot */
		.ident   = "Acer TravelMate 660",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 660"),
		पूर्ण,
	पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल व्योम ide_gd_shutकरोwn(ide_drive_t *drive)
अणु
#अगर_घोषित	CONFIG_ALPHA
	/* On Alpha, halt(8) करोesn't actually turn the machine off,
	   it माला_दो you पूर्णांकo the sort of firmware monitor. Typically,
	   it's used to boot another kernel image, so it's not much
	   dअगरferent from reboot(8). Thereक्रमe, we करोn't need to
	   spin करोwn the disk in this हाल, especially since Alpha
	   firmware करोesn't handle disks in standby mode properly.
	   On the other hand, it's reasonably safe to turn the घातer
	   off when the shutकरोwn process reaches the firmware prompt,
	   as the firmware initialization takes rather दीर्घ समय -
	   at least 10 seconds, which should be sufficient क्रम
	   the disk to expire its ग_लिखो cache. */
	अगर (प्रणाली_state != SYSTEM_POWER_OFF) अणु
#अन्यथा
	अगर (प्रणाली_state == SYSTEM_RESTART &&
		!dmi_check_प्रणाली(ide_coldreboot_table)) अणु
#पूर्ण_अगर
		drive->disk_ops->flush(drive);
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_INFO "Shutdown: %s\n", drive->name);

	drive->gendev.bus->suspend(&drive->gendev, PMSG_SUSPEND);
पूर्ण

#अगर_घोषित CONFIG_IDE_PROC_FS
अटल ide_proc_entry_t *ide_disk_proc_entries(ide_drive_t *drive)
अणु
	वापस (drive->media == ide_disk) ? ide_disk_proc : ide_floppy_proc;
पूर्ण

अटल स्थिर काष्ठा ide_proc_devset *ide_disk_proc_devsets(ide_drive_t *drive)
अणु
	वापस (drive->media == ide_disk) ? ide_disk_settings
					  : ide_floppy_settings;
पूर्ण
#पूर्ण_अगर

अटल ide_startstop_t ide_gd_करो_request(ide_drive_t *drive,
					 काष्ठा request *rq, sector_t sector)
अणु
	वापस drive->disk_ops->करो_request(drive, rq, sector);
पूर्ण

अटल काष्ठा ide_driver ide_gd_driver = अणु
	.gen_driver = अणु
		.owner		= THIS_MODULE,
		.name		= "ide-gd",
		.bus		= &ide_bus_type,
	पूर्ण,
	.probe			= ide_gd_probe,
	.हटाओ			= ide_gd_हटाओ,
	.resume			= ide_gd_resume,
	.shutकरोwn		= ide_gd_shutकरोwn,
	.version		= IDE_GD_VERSION,
	.करो_request		= ide_gd_करो_request,
#अगर_घोषित CONFIG_IDE_PROC_FS
	.proc_entries		= ide_disk_proc_entries,
	.proc_devsets		= ide_disk_proc_devsets,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक ide_gd_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा gendisk *disk = bdev->bd_disk;
	काष्ठा ide_disk_obj *idkp;
	ide_drive_t *drive;
	पूर्णांक ret = 0;

	idkp = ide_disk_get(disk);
	अगर (idkp == शून्य)
		वापस -ENXIO;

	drive = idkp->drive;

	ide_debug_log(IDE_DBG_FUNC, "enter");

	idkp->खोलोers++;

	अगर ((drive->dev_flags & IDE_DFLAG_REMOVABLE) && idkp->खोलोers == 1) अणु
		drive->dev_flags &= ~IDE_DFLAG_FORMAT_IN_PROGRESS;
		/* Just in हाल */

		ret = drive->disk_ops->init_media(drive, disk);

		/*
		 * Allow O_NDELAY to खोलो a drive without a disk, or with an
		 * unपढ़ोable disk, so that we can get the क्रमmat capacity
		 * of the drive or begin the क्रमmat - Sam
		 */
		अगर (ret && (mode & FMODE_NDELAY) == 0) अणु
			ret = -EIO;
			जाओ out_put_idkp;
		पूर्ण

		अगर ((drive->dev_flags & IDE_DFLAG_WP) && (mode & FMODE_WRITE)) अणु
			ret = -EROFS;
			जाओ out_put_idkp;
		पूर्ण

		/*
		 * Ignore the वापस code from करोor_lock,
		 * since the खोलो() has alपढ़ोy succeeded,
		 * and the करोor_lock is irrelevant at this poपूर्णांक.
		 */
		drive->disk_ops->set_करोorlock(drive, disk, 1);
		अगर (__invalidate_device(bdev, true))
			pr_warn("VFS: busy inodes on changed media %s\n",
				bdev->bd_disk->disk_name);
		drive->disk_ops->get_capacity(drive);
		set_capacity(disk, ide_gd_capacity(drive));
		set_bit(GD_NEED_PART_SCAN, &disk->state);
	पूर्ण अन्यथा अगर (drive->dev_flags & IDE_DFLAG_FORMAT_IN_PROGRESS) अणु
		ret = -EBUSY;
		जाओ out_put_idkp;
	पूर्ण
	वापस 0;

out_put_idkp:
	idkp->खोलोers--;
	ide_disk_put(idkp);
	वापस ret;
पूर्ण

अटल पूर्णांक ide_gd_unlocked_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	पूर्णांक ret;

	mutex_lock(&ide_gd_mutex);
	ret = ide_gd_खोलो(bdev, mode);
	mutex_unlock(&ide_gd_mutex);

	वापस ret;
पूर्ण


अटल व्योम ide_gd_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा ide_disk_obj *idkp = ide_drv_g(disk, ide_disk_obj);
	ide_drive_t *drive = idkp->drive;

	ide_debug_log(IDE_DBG_FUNC, "enter");

	mutex_lock(&ide_gd_mutex);
	अगर (idkp->खोलोers == 1)
		drive->disk_ops->flush(drive);

	अगर ((drive->dev_flags & IDE_DFLAG_REMOVABLE) && idkp->खोलोers == 1) अणु
		drive->disk_ops->set_करोorlock(drive, disk, 0);
		drive->dev_flags &= ~IDE_DFLAG_FORMAT_IN_PROGRESS;
	पूर्ण

	idkp->खोलोers--;

	ide_disk_put(idkp);
	mutex_unlock(&ide_gd_mutex);
पूर्ण

अटल पूर्णांक ide_gd_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo)
अणु
	काष्ठा ide_disk_obj *idkp = ide_drv_g(bdev->bd_disk, ide_disk_obj);
	ide_drive_t *drive = idkp->drive;

	geo->heads = drive->bios_head;
	geo->sectors = drive->bios_sect;
	geo->cylinders = (u16)drive->bios_cyl; /* truncate */
	वापस 0;
पूर्ण

अटल व्योम ide_gd_unlock_native_capacity(काष्ठा gendisk *disk)
अणु
	काष्ठा ide_disk_obj *idkp = ide_drv_g(disk, ide_disk_obj);
	ide_drive_t *drive = idkp->drive;
	स्थिर काष्ठा ide_disk_ops *disk_ops = drive->disk_ops;

	अगर (disk_ops->unlock_native_capacity)
		disk_ops->unlock_native_capacity(drive);
पूर्ण

अटल पूर्णांक ide_gd_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
			     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ide_disk_obj *idkp = ide_drv_g(bdev->bd_disk, ide_disk_obj);
	ide_drive_t *drive = idkp->drive;

	वापस drive->disk_ops->ioctl(drive, bdev, mode, cmd, arg);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक ide_gd_compat_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
			       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ide_disk_obj *idkp = ide_drv_g(bdev->bd_disk, ide_disk_obj);
	ide_drive_t *drive = idkp->drive;

	अगर (!drive->disk_ops->compat_ioctl)
		वापस -ENOIOCTLCMD;

	वापस drive->disk_ops->compat_ioctl(drive, bdev, mode, cmd, arg);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा block_device_operations ide_gd_ops = अणु
	.owner			= THIS_MODULE,
	.खोलो			= ide_gd_unlocked_खोलो,
	.release		= ide_gd_release,
	.ioctl			= ide_gd_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl		= ide_gd_compat_ioctl,
#पूर्ण_अगर
	.getgeo			= ide_gd_getgeo,
	.unlock_native_capacity	= ide_gd_unlock_native_capacity,
पूर्ण;

अटल पूर्णांक ide_gd_probe(ide_drive_t *drive)
अणु
	स्थिर काष्ठा ide_disk_ops *disk_ops = शून्य;
	काष्ठा ide_disk_obj *idkp;
	काष्ठा gendisk *g;

	/* म_माला("foo", "") is non-शून्य */
	अगर (!म_माला("ide-gd", drive->driver_req))
		जाओ failed;

#अगर_घोषित CONFIG_IDE_GD_ATA
	अगर (drive->media == ide_disk)
		disk_ops = &ide_ata_disk_ops;
#पूर्ण_अगर
#अगर_घोषित CONFIG_IDE_GD_ATAPI
	अगर (drive->media == ide_floppy)
		disk_ops = &ide_atapi_disk_ops;
#पूर्ण_अगर
	अगर (disk_ops == शून्य)
		जाओ failed;

	अगर (disk_ops->check(drive, DRV_NAME) == 0) अणु
		prपूर्णांकk(KERN_ERR PFX "%s: not supported by this driver\n",
			drive->name);
		जाओ failed;
	पूर्ण

	idkp = kzalloc(माप(*idkp), GFP_KERNEL);
	अगर (!idkp) अणु
		prपूर्णांकk(KERN_ERR PFX "%s: can't allocate a disk structure\n",
			drive->name);
		जाओ failed;
	पूर्ण

	g = alloc_disk_node(IDE_DISK_MINORS, hwअगर_to_node(drive->hwअगर));
	अगर (!g)
		जाओ out_मुक्त_idkp;

	ide_init_disk(g, drive);

	idkp->dev.parent = &drive->gendev;
	idkp->dev.release = ide_disk_release;
	dev_set_name(&idkp->dev, "%s", dev_name(&drive->gendev));

	अगर (device_रेजिस्टर(&idkp->dev))
		जाओ out_मुक्त_disk;

	idkp->drive = drive;
	idkp->driver = &ide_gd_driver;
	idkp->disk = g;

	g->निजी_data = &idkp->driver;

	drive->driver_data = idkp;
	drive->debug_mask = debug_mask;
	drive->disk_ops = disk_ops;

	disk_ops->setup(drive);

	set_capacity(g, ide_gd_capacity(drive));

	g->minors = IDE_DISK_MINORS;
	g->flags |= GENHD_FL_EXT_DEVT;
	अगर (drive->dev_flags & IDE_DFLAG_REMOVABLE)
		g->flags = GENHD_FL_REMOVABLE;
	g->fops = &ide_gd_ops;
	g->events = DISK_EVENT_MEDIA_CHANGE;
	device_add_disk(&drive->gendev, g, शून्य);
	वापस 0;

out_मुक्त_disk:
	put_disk(g);
out_मुक्त_idkp:
	kमुक्त(idkp);
failed:
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक __init ide_gd_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO DRV_NAME " driver " IDE_GD_VERSION "\n");
	वापस driver_रेजिस्टर(&ide_gd_driver.gen_driver);
पूर्ण

अटल व्योम __निकास ide_gd_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&ide_gd_driver.gen_driver);
पूर्ण

MODULE_ALIAS("ide:*m-disk*");
MODULE_ALIAS("ide-disk");
MODULE_ALIAS("ide:*m-floppy*");
MODULE_ALIAS("ide-floppy");
module_init(ide_gd_init);
module_निकास(ide_gd_निकास);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("generic ATA/ATAPI disk driver");
