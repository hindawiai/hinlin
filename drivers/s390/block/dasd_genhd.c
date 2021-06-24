<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Author(s)......: Holger Smolinski <Holger.Smolinski@de.ibm.com>
 *		    Horst Hummel <Horst.Hummel@de.ibm.com>
 *		    Carsten Otte <Cotte@de.ibm.com>
 *		    Martin Schwidefsky <schwidefsky@de.ibm.com>
 * Bugreports.to..: <Linux390@de.ibm.com>
 * Copyright IBM Corp. 1999, 2001
 *
 * gendisk related functions क्रम the dasd driver.
 *
 */

#घोषणा KMSG_COMPONENT "dasd"

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fs.h>
#समावेश <linux/blkpg.h>

#समावेश <linux/uaccess.h>

/* This is ugly... */
#घोषणा PRINTK_HEADER "dasd_gendisk:"

#समावेश "dasd_int.h"

/*
 * Allocate and रेजिस्टर gendisk काष्ठाure क्रम device.
 */
पूर्णांक dasd_gendisk_alloc(काष्ठा dasd_block *block)
अणु
	काष्ठा gendisk *gdp;
	काष्ठा dasd_device *base;
	पूर्णांक len;

	/* Make sure the minor क्रम this device exists. */
	base = block->base;
	अगर (base->devindex >= DASD_PER_MAJOR)
		वापस -EBUSY;

	gdp = alloc_disk(1 << DASD_PARTN_BITS);
	अगर (!gdp)
		वापस -ENOMEM;

	/* Initialize gendisk काष्ठाure. */
	gdp->major = DASD_MAJOR;
	gdp->first_minor = base->devindex << DASD_PARTN_BITS;
	gdp->fops = &dasd_device_operations;

	/*
	 * Set device name.
	 *   dasda - dasdz : 26 devices
	 *   dasdaa - dasdzz : 676 devices, added up = 702
	 *   dasdaaa - dasdzzz : 17576 devices, added up = 18278
	 *   dasdaaaa - dasdzzzz : 456976 devices, added up = 475252
	 */
	len = प्र_लिखो(gdp->disk_name, "dasd");
	अगर (base->devindex > 25) अणु
		अगर (base->devindex > 701) अणु
			अगर (base->devindex > 18277)
			        len += प्र_लिखो(gdp->disk_name + len, "%c",
					       'a'+(((base->devindex-18278)
						     /17576)%26));
			len += प्र_लिखो(gdp->disk_name + len, "%c",
				       'a'+(((base->devindex-702)/676)%26));
		पूर्ण
		len += प्र_लिखो(gdp->disk_name + len, "%c",
			       'a'+(((base->devindex-26)/26)%26));
	पूर्ण
	len += प्र_लिखो(gdp->disk_name + len, "%c", 'a'+(base->devindex%26));

	अगर (base->features & DASD_FEATURE_READONLY ||
	    test_bit(DASD_FLAG_DEVICE_RO, &base->flags))
		set_disk_ro(gdp, 1);
	dasd_add_link_to_gendisk(gdp, base);
	gdp->queue = block->request_queue;
	block->gdp = gdp;
	set_capacity(block->gdp, 0);
	device_add_disk(&base->cdev->dev, block->gdp, शून्य);
	वापस 0;
पूर्ण

/*
 * Unरेजिस्टर and मुक्त gendisk काष्ठाure क्रम device.
 */
व्योम dasd_gendisk_मुक्त(काष्ठा dasd_block *block)
अणु
	अगर (block->gdp) अणु
		del_gendisk(block->gdp);
		block->gdp->निजी_data = शून्य;
		put_disk(block->gdp);
		block->gdp = शून्य;
	पूर्ण
पूर्ण

/*
 * Trigger a partition detection.
 */
पूर्णांक dasd_scan_partitions(काष्ठा dasd_block *block)
अणु
	काष्ठा block_device *bdev;
	पूर्णांक rc;

	bdev = blkdev_get_by_dev(disk_devt(block->gdp), FMODE_READ, शून्य);
	अगर (IS_ERR(bdev)) अणु
		DBF_DEV_EVENT(DBF_ERR, block->base,
			      "scan partitions error, blkdev_get returned %ld",
			      PTR_ERR(bdev));
		वापस -ENODEV;
	पूर्ण

	mutex_lock(&bdev->bd_mutex);
	rc = bdev_disk_changed(bdev, false);
	mutex_unlock(&bdev->bd_mutex);
	अगर (rc)
		DBF_DEV_EVENT(DBF_ERR, block->base,
				"scan partitions error, rc %d", rc);

	/*
	 * Since the matching blkdev_put call to the blkdev_get in
	 * this function is not called beक्रमe dasd_destroy_partitions
	 * the offline खोलो_count limit needs to be increased from
	 * 0 to 1. This is करोne by setting device->bdev (see
	 * dasd_generic_set_offline). As दीर्घ as the partition
	 * detection is running no offline should be allowed. That
	 * is why the assignment to device->bdev is करोne AFTER
	 * the BLKRRPART ioctl.
	 */
	block->bdev = bdev;
	वापस 0;
पूर्ण

/*
 * Remove all inodes in the प्रणाली क्रम a device, delete the
 * partitions and make device unusable by setting its size to zero.
 */
व्योम dasd_destroy_partitions(काष्ठा dasd_block *block)
अणु
	काष्ठा block_device *bdev;

	/*
	 * Get the bdev poपूर्णांकer from the device काष्ठाure and clear
	 * device->bdev to lower the offline खोलो_count limit again.
	 */
	bdev = block->bdev;
	block->bdev = शून्य;

	mutex_lock(&bdev->bd_mutex);
	bdev_disk_changed(bdev, true);
	mutex_unlock(&bdev->bd_mutex);

	/* Matching blkdev_put to the blkdev_get in dasd_scan_partitions. */
	blkdev_put(bdev, FMODE_READ);
पूर्ण

पूर्णांक dasd_gendisk_init(व्योम)
अणु
	पूर्णांक rc;

	/* Register to अटल dasd major 94 */
	rc = रेजिस्टर_blkdev(DASD_MAJOR, "dasd");
	अगर (rc != 0) अणु
		pr_warn("Registering the device driver with major number %d failed\n",
			DASD_MAJOR);
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

व्योम dasd_gendisk_निकास(व्योम)
अणु
	unरेजिस्टर_blkdev(DASD_MAJOR, "dasd");
पूर्ण
