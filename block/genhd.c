<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  gendisk handling
 *
 * Portions Copyright (C) 2020 Christoph Hellwig
 */

#समावेश <linux/module.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/fs.h>
#समावेश <linux/genhd.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/kernel.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/kmod.h>
#समावेश <linux/mutex.h>
#समावेश <linux/idr.h>
#समावेश <linux/log2.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/badblocks.h>

#समावेश "blk.h"

अटल काष्ठा kobject *block_depr;

/* क्रम extended dynamic devt allocation, currently only one major is used */
#घोषणा NR_EXT_DEVT		(1 << MINORBITS)
अटल DEFINE_IDA(ext_devt_ida);

अटल व्योम disk_check_events(काष्ठा disk_events *ev,
			      अचिन्हित पूर्णांक *clearing_ptr);
अटल व्योम disk_alloc_events(काष्ठा gendisk *disk);
अटल व्योम disk_add_events(काष्ठा gendisk *disk);
अटल व्योम disk_del_events(काष्ठा gendisk *disk);
अटल व्योम disk_release_events(काष्ठा gendisk *disk);

व्योम set_capacity(काष्ठा gendisk *disk, sector_t sectors)
अणु
	काष्ठा block_device *bdev = disk->part0;

	spin_lock(&bdev->bd_size_lock);
	i_size_ग_लिखो(bdev->bd_inode, (loff_t)sectors << SECTOR_SHIFT);
	spin_unlock(&bdev->bd_size_lock);
पूर्ण
EXPORT_SYMBOL(set_capacity);

/*
 * Set disk capacity and notअगरy अगर the size is not currently zero and will not
 * be set to zero.  Returns true अगर a uevent was sent, otherwise false.
 */
bool set_capacity_and_notअगरy(काष्ठा gendisk *disk, sector_t size)
अणु
	sector_t capacity = get_capacity(disk);
	अक्षर *envp[] = अणु "RESIZE=1", शून्य पूर्ण;

	set_capacity(disk, size);

	/*
	 * Only prपूर्णांक a message and send a uevent अगर the gendisk is user visible
	 * and alive.  This aव्योमs spamming the log and udev when setting the
	 * initial capacity during probing.
	 */
	अगर (size == capacity ||
	    (disk->flags & (GENHD_FL_UP | GENHD_FL_HIDDEN)) != GENHD_FL_UP)
		वापस false;

	pr_info("%s: detected capacity change from %lld to %lld\n",
		disk->disk_name, capacity, size);

	/*
	 * Historically we did not send a uevent क्रम changes to/from an empty
	 * device.
	 */
	अगर (!capacity || !size)
		वापस false;
	kobject_uevent_env(&disk_to_dev(disk)->kobj, KOBJ_CHANGE, envp);
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(set_capacity_and_notअगरy);

/*
 * Format the device name of the indicated disk पूर्णांकo the supplied buffer and
 * वापस a poपूर्णांकer to that same buffer क्रम convenience.
 */
अक्षर *disk_name(काष्ठा gendisk *hd, पूर्णांक partno, अक्षर *buf)
अणु
	अगर (!partno)
		snम_लिखो(buf, BDEVNAME_SIZE, "%s", hd->disk_name);
	अन्यथा अगर (है_अंक(hd->disk_name[म_माप(hd->disk_name)-1]))
		snम_लिखो(buf, BDEVNAME_SIZE, "%sp%d", hd->disk_name, partno);
	अन्यथा
		snम_लिखो(buf, BDEVNAME_SIZE, "%s%d", hd->disk_name, partno);

	वापस buf;
पूर्ण

स्थिर अक्षर *bdevname(काष्ठा block_device *bdev, अक्षर *buf)
अणु
	वापस disk_name(bdev->bd_disk, bdev->bd_partno, buf);
पूर्ण
EXPORT_SYMBOL(bdevname);

अटल व्योम part_stat_पढ़ो_all(काष्ठा block_device *part,
		काष्ठा disk_stats *stat)
अणु
	पूर्णांक cpu;

	स_रखो(stat, 0, माप(काष्ठा disk_stats));
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा disk_stats *ptr = per_cpu_ptr(part->bd_stats, cpu);
		पूर्णांक group;

		क्रम (group = 0; group < NR_STAT_GROUPS; group++) अणु
			stat->nsecs[group] += ptr->nsecs[group];
			stat->sectors[group] += ptr->sectors[group];
			stat->ios[group] += ptr->ios[group];
			stat->merges[group] += ptr->merges[group];
		पूर्ण

		stat->io_ticks += ptr->io_ticks;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक part_in_flight(काष्ठा block_device *part)
अणु
	अचिन्हित पूर्णांक inflight = 0;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		inflight += part_stat_local_पढ़ो_cpu(part, in_flight[0], cpu) +
			    part_stat_local_पढ़ो_cpu(part, in_flight[1], cpu);
	पूर्ण
	अगर ((पूर्णांक)inflight < 0)
		inflight = 0;

	वापस inflight;
पूर्ण

अटल व्योम part_in_flight_rw(काष्ठा block_device *part,
		अचिन्हित पूर्णांक inflight[2])
अणु
	पूर्णांक cpu;

	inflight[0] = 0;
	inflight[1] = 0;
	क्रम_each_possible_cpu(cpu) अणु
		inflight[0] += part_stat_local_पढ़ो_cpu(part, in_flight[0], cpu);
		inflight[1] += part_stat_local_पढ़ो_cpu(part, in_flight[1], cpu);
	पूर्ण
	अगर ((पूर्णांक)inflight[0] < 0)
		inflight[0] = 0;
	अगर ((पूर्णांक)inflight[1] < 0)
		inflight[1] = 0;
पूर्ण

/*
 * Can be deleted altogether. Later.
 *
 */
#घोषणा BLKDEV_MAJOR_HASH_SIZE 255
अटल काष्ठा blk_major_name अणु
	काष्ठा blk_major_name *next;
	पूर्णांक major;
	अक्षर name[16];
	व्योम (*probe)(dev_t devt);
पूर्ण *major_names[BLKDEV_MAJOR_HASH_SIZE];
अटल DEFINE_MUTEX(major_names_lock);

/* index in the above - क्रम now: assume no multimajor ranges */
अटल अंतरभूत पूर्णांक major_to_index(अचिन्हित major)
अणु
	वापस major % BLKDEV_MAJOR_HASH_SIZE;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
व्योम blkdev_show(काष्ठा seq_file *seqf, off_t offset)
अणु
	काष्ठा blk_major_name *dp;

	mutex_lock(&major_names_lock);
	क्रम (dp = major_names[major_to_index(offset)]; dp; dp = dp->next)
		अगर (dp->major == offset)
			seq_म_लिखो(seqf, "%3d %s\n", dp->major, dp->name);
	mutex_unlock(&major_names_lock);
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

/**
 * __रेजिस्टर_blkdev - रेजिस्टर a new block device
 *
 * @major: the requested major device number [1..BLKDEV_MAJOR_MAX-1]. If
 *         @major = 0, try to allocate any unused major number.
 * @name: the name of the new block device as a zero terminated string
 * @probe: allback that is called on access to any minor number of @major
 *
 * The @name must be unique within the प्रणाली.
 *
 * The वापस value depends on the @major input parameter:
 *
 *  - अगर a major device number was requested in range [1..BLKDEV_MAJOR_MAX-1]
 *    then the function वापसs zero on success, or a negative error code
 *  - अगर any unused major number was requested with @major = 0 parameter
 *    then the वापस value is the allocated major number in range
 *    [1..BLKDEV_MAJOR_MAX-1] or a negative error code otherwise
 *
 * See Documentation/admin-guide/devices.txt क्रम the list of allocated
 * major numbers.
 *
 * Use रेजिस्टर_blkdev instead क्रम any new code.
 */
पूर्णांक __रेजिस्टर_blkdev(अचिन्हित पूर्णांक major, स्थिर अक्षर *name,
		व्योम (*probe)(dev_t devt))
अणु
	काष्ठा blk_major_name **n, *p;
	पूर्णांक index, ret = 0;

	mutex_lock(&major_names_lock);

	/* temporary */
	अगर (major == 0) अणु
		क्रम (index = ARRAY_SIZE(major_names)-1; index > 0; index--) अणु
			अगर (major_names[index] == शून्य)
				अवरोध;
		पूर्ण

		अगर (index == 0) अणु
			prपूर्णांकk("%s: failed to get major for %s\n",
			       __func__, name);
			ret = -EBUSY;
			जाओ out;
		पूर्ण
		major = index;
		ret = major;
	पूर्ण

	अगर (major >= BLKDEV_MAJOR_MAX) अणु
		pr_err("%s: major requested (%u) is greater than the maximum (%u) for %s\n",
		       __func__, major, BLKDEV_MAJOR_MAX-1, name);

		ret = -EINVAL;
		जाओ out;
	पूर्ण

	p = kदो_स्मृति(माप(काष्ठा blk_major_name), GFP_KERNEL);
	अगर (p == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	p->major = major;
	p->probe = probe;
	strlcpy(p->name, name, माप(p->name));
	p->next = शून्य;
	index = major_to_index(major);

	क्रम (n = &major_names[index]; *n; n = &(*n)->next) अणु
		अगर ((*n)->major == major)
			अवरोध;
	पूर्ण
	अगर (!*n)
		*n = p;
	अन्यथा
		ret = -EBUSY;

	अगर (ret < 0) अणु
		prपूर्णांकk("register_blkdev: cannot get major %u for %s\n",
		       major, name);
		kमुक्त(p);
	पूर्ण
out:
	mutex_unlock(&major_names_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__रेजिस्टर_blkdev);

व्योम unरेजिस्टर_blkdev(अचिन्हित पूर्णांक major, स्थिर अक्षर *name)
अणु
	काष्ठा blk_major_name **n;
	काष्ठा blk_major_name *p = शून्य;
	पूर्णांक index = major_to_index(major);

	mutex_lock(&major_names_lock);
	क्रम (n = &major_names[index]; *n; n = &(*n)->next)
		अगर ((*n)->major == major)
			अवरोध;
	अगर (!*n || म_भेद((*n)->name, name)) अणु
		WARN_ON(1);
	पूर्ण अन्यथा अणु
		p = *n;
		*n = p->next;
	पूर्ण
	mutex_unlock(&major_names_lock);
	kमुक्त(p);
पूर्ण

EXPORT_SYMBOL(unरेजिस्टर_blkdev);

/**
 * blk_mangle_minor - scatter minor numbers apart
 * @minor: minor number to mangle
 *
 * Scatter consecutively allocated @minor number apart अगर MANGLE_DEVT
 * is enabled.  Mangling twice gives the original value.
 *
 * RETURNS:
 * Mangled value.
 *
 * CONTEXT:
 * Don't care.
 */
अटल पूर्णांक blk_mangle_minor(पूर्णांक minor)
अणु
#अगर_घोषित CONFIG_DEBUG_BLOCK_EXT_DEVT
	पूर्णांक i;

	क्रम (i = 0; i < MINORBITS / 2; i++) अणु
		पूर्णांक low = minor & (1 << i);
		पूर्णांक high = minor & (1 << (MINORBITS - 1 - i));
		पूर्णांक distance = MINORBITS - 1 - 2 * i;

		minor ^= low | high;	/* clear both bits */
		low <<= distance;	/* swap the positions */
		high >>= distance;
		minor |= low | high;	/* and set */
	पूर्ण
#पूर्ण_अगर
	वापस minor;
पूर्ण

/**
 * blk_alloc_devt - allocate a dev_t क्रम a block device
 * @bdev: block device to allocate dev_t क्रम
 * @devt: out parameter क्रम resulting dev_t
 *
 * Allocate a dev_t क्रम block device.
 *
 * RETURNS:
 * 0 on success, allocated dev_t is वापसed in *@devt.  -त्रुटि_सं on
 * failure.
 *
 * CONTEXT:
 * Might sleep.
 */
पूर्णांक blk_alloc_devt(काष्ठा block_device *bdev, dev_t *devt)
अणु
	काष्ठा gendisk *disk = bdev->bd_disk;
	पूर्णांक idx;

	/* in consecutive minor range? */
	अगर (bdev->bd_partno < disk->minors) अणु
		*devt = MKDEV(disk->major, disk->first_minor + bdev->bd_partno);
		वापस 0;
	पूर्ण

	idx = ida_alloc_range(&ext_devt_ida, 0, NR_EXT_DEVT, GFP_KERNEL);
	अगर (idx < 0)
		वापस idx == -ENOSPC ? -EBUSY : idx;

	*devt = MKDEV(BLOCK_EXT_MAJOR, blk_mangle_minor(idx));
	वापस 0;
पूर्ण

/**
 * blk_मुक्त_devt - मुक्त a dev_t
 * @devt: dev_t to मुक्त
 *
 * Free @devt which was allocated using blk_alloc_devt().
 *
 * CONTEXT:
 * Might sleep.
 */
व्योम blk_मुक्त_devt(dev_t devt)
अणु
	अगर (MAJOR(devt) == BLOCK_EXT_MAJOR)
		ida_मुक्त(&ext_devt_ida, blk_mangle_minor(MINOR(devt)));
पूर्ण

अटल अक्षर *bdevt_str(dev_t devt, अक्षर *buf)
अणु
	अगर (MAJOR(devt) <= 0xff && MINOR(devt) <= 0xff) अणु
		अक्षर tbuf[BDEVT_SIZE];
		snम_लिखो(tbuf, BDEVT_SIZE, "%02x%02x", MAJOR(devt), MINOR(devt));
		snम_लिखो(buf, BDEVT_SIZE, "%-9s", tbuf);
	पूर्ण अन्यथा
		snम_लिखो(buf, BDEVT_SIZE, "%03x:%05x", MAJOR(devt), MINOR(devt));

	वापस buf;
पूर्ण

व्योम disk_uevent(काष्ठा gendisk *disk, क्रमागत kobject_action action)
अणु
	काष्ठा block_device *part;
	अचिन्हित दीर्घ idx;

	rcu_पढ़ो_lock();
	xa_क्रम_each(&disk->part_tbl, idx, part) अणु
		अगर (bdev_is_partition(part) && !bdev_nr_sectors(part))
			जारी;
		अगर (!bdgrab(part))
			जारी;

		rcu_पढ़ो_unlock();
		kobject_uevent(bdev_kobj(part), action);
		bdput(part);
		rcu_पढ़ो_lock();
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(disk_uevent);

अटल व्योम disk_scan_partitions(काष्ठा gendisk *disk)
अणु
	काष्ठा block_device *bdev;

	अगर (!get_capacity(disk) || !disk_part_scan_enabled(disk))
		वापस;

	set_bit(GD_NEED_PART_SCAN, &disk->state);
	bdev = blkdev_get_by_dev(disk_devt(disk), FMODE_READ, शून्य);
	अगर (!IS_ERR(bdev))
		blkdev_put(bdev, FMODE_READ);
पूर्ण

अटल व्योम रेजिस्टर_disk(काष्ठा device *parent, काष्ठा gendisk *disk,
			  स्थिर काष्ठा attribute_group **groups)
अणु
	काष्ठा device *ddev = disk_to_dev(disk);
	पूर्णांक err;

	ddev->parent = parent;

	dev_set_name(ddev, "%s", disk->disk_name);

	/* delay uevents, until we scanned partition table */
	dev_set_uevent_suppress(ddev, 1);

	अगर (groups) अणु
		WARN_ON(ddev->groups);
		ddev->groups = groups;
	पूर्ण
	अगर (device_add(ddev))
		वापस;
	अगर (!sysfs_deprecated) अणु
		err = sysfs_create_link(block_depr, &ddev->kobj,
					kobject_name(&ddev->kobj));
		अगर (err) अणु
			device_del(ddev);
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * aव्योम probable deadlock caused by allocating memory with
	 * GFP_KERNEL in runसमय_resume callback of its all ancestor
	 * devices
	 */
	pm_runसमय_set_meदो_स्मृति_noio(ddev, true);

	disk->part0->bd_holder_dir =
		kobject_create_and_add("holders", &ddev->kobj);
	disk->slave_dir = kobject_create_and_add("slaves", &ddev->kobj);

	अगर (disk->flags & GENHD_FL_HIDDEN)
		वापस;

	disk_scan_partitions(disk);

	/* announce the disk and partitions after all partitions are created */
	dev_set_uevent_suppress(ddev, 0);
	disk_uevent(disk, KOBJ_ADD);

	अगर (disk->queue->backing_dev_info->dev) अणु
		err = sysfs_create_link(&ddev->kobj,
			  &disk->queue->backing_dev_info->dev->kobj,
			  "bdi");
		WARN_ON(err);
	पूर्ण
पूर्ण

/**
 * __device_add_disk - add disk inक्रमmation to kernel list
 * @parent: parent device क्रम the disk
 * @disk: per-device partitioning inक्रमmation
 * @groups: Additional per-device sysfs groups
 * @रेजिस्टर_queue: रेजिस्टर the queue अगर set to true
 *
 * This function रेजिस्टरs the partitioning inक्रमmation in @disk
 * with the kernel.
 *
 * FIXME: error handling
 */
अटल व्योम __device_add_disk(काष्ठा device *parent, काष्ठा gendisk *disk,
			      स्थिर काष्ठा attribute_group **groups,
			      bool रेजिस्टर_queue)
अणु
	dev_t devt;
	पूर्णांक retval;

	/*
	 * The disk queue should now be all set with enough inक्रमmation about
	 * the device क्रम the elevator code to pick an adequate शेष
	 * elevator अगर one is needed, that is, क्रम devices requesting queue
	 * registration.
	 */
	अगर (रेजिस्टर_queue)
		elevator_init_mq(disk->queue);

	/* minors == 0 indicates to use ext devt from part0 and should
	 * be accompanied with EXT_DEVT flag.  Make sure all
	 * parameters make sense.
	 */
	WARN_ON(disk->minors && !(disk->major || disk->first_minor));
	WARN_ON(!disk->minors &&
		!(disk->flags & (GENHD_FL_EXT_DEVT | GENHD_FL_HIDDEN)));

	disk->flags |= GENHD_FL_UP;

	retval = blk_alloc_devt(disk->part0, &devt);
	अगर (retval) अणु
		WARN_ON(1);
		वापस;
	पूर्ण
	disk->major = MAJOR(devt);
	disk->first_minor = MINOR(devt);

	disk_alloc_events(disk);

	अगर (disk->flags & GENHD_FL_HIDDEN) अणु
		/*
		 * Don't let hidden disks show up in /proc/partitions,
		 * and करोn't bother scanning क्रम partitions either.
		 */
		disk->flags |= GENHD_FL_SUPPRESS_PARTITION_INFO;
		disk->flags |= GENHD_FL_NO_PART_SCAN;
	पूर्ण अन्यथा अणु
		काष्ठा backing_dev_info *bdi = disk->queue->backing_dev_info;
		काष्ठा device *dev = disk_to_dev(disk);
		पूर्णांक ret;

		/* Register BDI beक्रमe referencing it from bdev */
		dev->devt = devt;
		ret = bdi_रेजिस्टर(bdi, "%u:%u", MAJOR(devt), MINOR(devt));
		WARN_ON(ret);
		bdi_set_owner(bdi, dev);
		bdev_add(disk->part0, devt);
	पूर्ण
	रेजिस्टर_disk(parent, disk, groups);
	अगर (रेजिस्टर_queue)
		blk_रेजिस्टर_queue(disk);

	/*
	 * Take an extra ref on queue which will be put on disk_release()
	 * so that it sticks around as दीर्घ as @disk is there.
	 */
	WARN_ON_ONCE(!blk_get_queue(disk->queue));

	disk_add_events(disk);
	blk_पूर्णांकegrity_add(disk);
पूर्ण

व्योम device_add_disk(काष्ठा device *parent, काष्ठा gendisk *disk,
		     स्थिर काष्ठा attribute_group **groups)

अणु
	__device_add_disk(parent, disk, groups, true);
पूर्ण
EXPORT_SYMBOL(device_add_disk);

व्योम device_add_disk_no_queue_reg(काष्ठा device *parent, काष्ठा gendisk *disk)
अणु
	__device_add_disk(parent, disk, शून्य, false);
पूर्ण
EXPORT_SYMBOL(device_add_disk_no_queue_reg);

/**
 * del_gendisk - हटाओ the gendisk
 * @disk: the काष्ठा gendisk to हटाओ
 *
 * Removes the gendisk and all its associated resources. This deletes the
 * partitions associated with the gendisk, and unरेजिस्टरs the associated
 * request_queue.
 *
 * This is the counter to the respective __device_add_disk() call.
 *
 * The final removal of the काष्ठा gendisk happens when its refcount reaches 0
 * with put_disk(), which should be called after del_gendisk(), अगर
 * __device_add_disk() was used.
 *
 * Drivers exist which depend on the release of the gendisk to be synchronous,
 * it should not be deferred.
 *
 * Context: can sleep
 */
व्योम del_gendisk(काष्ठा gendisk *disk)
अणु
	might_sleep();

	अगर (WARN_ON_ONCE(!disk->queue))
		वापस;

	blk_पूर्णांकegrity_del(disk);
	disk_del_events(disk);

	mutex_lock(&disk->part0->bd_mutex);
	disk->flags &= ~GENHD_FL_UP;
	blk_drop_partitions(disk);
	mutex_unlock(&disk->part0->bd_mutex);

	fsync_bdev(disk->part0);
	__invalidate_device(disk->part0, true);

	/*
	 * Unhash the bdev inode क्रम this device so that it can't be looked
	 * up any more even अगर खोलोers still hold references to it.
	 */
	हटाओ_inode_hash(disk->part0->bd_inode);

	set_capacity(disk, 0);

	अगर (!(disk->flags & GENHD_FL_HIDDEN)) अणु
		sysfs_हटाओ_link(&disk_to_dev(disk)->kobj, "bdi");

		/*
		 * Unरेजिस्टर bdi beक्रमe releasing device numbers (as they can
		 * get reused and we'd get clashes in sysfs).
		 */
		bdi_unरेजिस्टर(disk->queue->backing_dev_info);
	पूर्ण

	blk_unरेजिस्टर_queue(disk);

	kobject_put(disk->part0->bd_holder_dir);
	kobject_put(disk->slave_dir);

	part_stat_set_all(disk->part0, 0);
	disk->part0->bd_stamp = 0;
	अगर (!sysfs_deprecated)
		sysfs_हटाओ_link(block_depr, dev_name(disk_to_dev(disk)));
	pm_runसमय_set_meदो_स्मृति_noio(disk_to_dev(disk), false);
	device_del(disk_to_dev(disk));
पूर्ण
EXPORT_SYMBOL(del_gendisk);

/* sysfs access to bad-blocks list. */
अटल sमाप_प्रकार disk_badblocks_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *page)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);

	अगर (!disk->bb)
		वापस प्र_लिखो(page, "\n");

	वापस badblocks_show(disk->bb, page, 0);
पूर्ण

अटल sमाप_प्रकार disk_badblocks_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);

	अगर (!disk->bb)
		वापस -ENXIO;

	वापस badblocks_store(disk->bb, page, len, 0);
पूर्ण

व्योम blk_request_module(dev_t devt)
अणु
	अचिन्हित पूर्णांक major = MAJOR(devt);
	काष्ठा blk_major_name **n;

	mutex_lock(&major_names_lock);
	क्रम (n = &major_names[major_to_index(major)]; *n; n = &(*n)->next) अणु
		अगर ((*n)->major == major && (*n)->probe) अणु
			(*n)->probe(devt);
			mutex_unlock(&major_names_lock);
			वापस;
		पूर्ण
	पूर्ण
	mutex_unlock(&major_names_lock);

	अगर (request_module("block-major-%d-%d", MAJOR(devt), MINOR(devt)) > 0)
		/* Make old-style 2.4 aliases work */
		request_module("block-major-%d", MAJOR(devt));
पूर्ण

/**
 * bdget_disk - करो bdget() by gendisk and partition number
 * @disk: gendisk of पूर्णांकerest
 * @partno: partition number
 *
 * Find partition @partno from @disk, करो bdget() on it.
 *
 * CONTEXT:
 * Don't care.
 *
 * RETURNS:
 * Resulting block_device on success, शून्य on failure.
 */
काष्ठा block_device *bdget_disk(काष्ठा gendisk *disk, पूर्णांक partno)
अणु
	काष्ठा block_device *bdev = शून्य;

	rcu_पढ़ो_lock();
	bdev = xa_load(&disk->part_tbl, partno);
	अगर (bdev && !bdgrab(bdev))
		bdev = शून्य;
	rcu_पढ़ो_unlock();

	वापस bdev;
पूर्ण

/*
 * prपूर्णांक a full list of all partitions - पूर्णांकended क्रम places where the root
 * fileप्रणाली can't be mounted and thus to give the victim some idea of what
 * went wrong
 */
व्योम __init prपूर्णांकk_all_partitions(व्योम)
अणु
	काष्ठा class_dev_iter iter;
	काष्ठा device *dev;

	class_dev_iter_init(&iter, &block_class, शून्य, &disk_type);
	जबतक ((dev = class_dev_iter_next(&iter))) अणु
		काष्ठा gendisk *disk = dev_to_disk(dev);
		काष्ठा block_device *part;
		अक्षर name_buf[BDEVNAME_SIZE];
		अक्षर devt_buf[BDEVT_SIZE];
		अचिन्हित दीर्घ idx;

		/*
		 * Don't show empty devices or things that have been
		 * suppressed
		 */
		अगर (get_capacity(disk) == 0 ||
		    (disk->flags & GENHD_FL_SUPPRESS_PARTITION_INFO))
			जारी;

		/*
		 * Note, unlike /proc/partitions, I am showing the numbers in
		 * hex - the same क्रमmat as the root= option takes.
		 */
		rcu_पढ़ो_lock();
		xa_क्रम_each(&disk->part_tbl, idx, part) अणु
			अगर (!bdev_nr_sectors(part))
				जारी;
			prपूर्णांकk("%s%s %10llu %s %s",
			       bdev_is_partition(part) ? "  " : "",
			       bdevt_str(part->bd_dev, devt_buf),
			       bdev_nr_sectors(part) >> 1,
			       disk_name(disk, part->bd_partno, name_buf),
			       part->bd_meta_info ?
					part->bd_meta_info->uuid : "");
			अगर (bdev_is_partition(part))
				prपूर्णांकk("\n");
			अन्यथा अगर (dev->parent && dev->parent->driver)
				prपूर्णांकk(" driver: %s\n",
					dev->parent->driver->name);
			अन्यथा
				prपूर्णांकk(" (driver?)\n");
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
	class_dev_iter_निकास(&iter);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
/* iterator */
अटल व्योम *disk_seqf_start(काष्ठा seq_file *seqf, loff_t *pos)
अणु
	loff_t skip = *pos;
	काष्ठा class_dev_iter *iter;
	काष्ठा device *dev;

	iter = kदो_स्मृति(माप(*iter), GFP_KERNEL);
	अगर (!iter)
		वापस ERR_PTR(-ENOMEM);

	seqf->निजी = iter;
	class_dev_iter_init(iter, &block_class, शून्य, &disk_type);
	करो अणु
		dev = class_dev_iter_next(iter);
		अगर (!dev)
			वापस शून्य;
	पूर्ण जबतक (skip--);

	वापस dev_to_disk(dev);
पूर्ण

अटल व्योम *disk_seqf_next(काष्ठा seq_file *seqf, व्योम *v, loff_t *pos)
अणु
	काष्ठा device *dev;

	(*pos)++;
	dev = class_dev_iter_next(seqf->निजी);
	अगर (dev)
		वापस dev_to_disk(dev);

	वापस शून्य;
पूर्ण

अटल व्योम disk_seqf_stop(काष्ठा seq_file *seqf, व्योम *v)
अणु
	काष्ठा class_dev_iter *iter = seqf->निजी;

	/* stop is called even after start failed :-( */
	अगर (iter) अणु
		class_dev_iter_निकास(iter);
		kमुक्त(iter);
		seqf->निजी = शून्य;
	पूर्ण
पूर्ण

अटल व्योम *show_partition_start(काष्ठा seq_file *seqf, loff_t *pos)
अणु
	व्योम *p;

	p = disk_seqf_start(seqf, pos);
	अगर (!IS_ERR_OR_शून्य(p) && !*pos)
		seq_माला_दो(seqf, "major minor  #blocks  name\n\n");
	वापस p;
पूर्ण

अटल पूर्णांक show_partition(काष्ठा seq_file *seqf, व्योम *v)
अणु
	काष्ठा gendisk *sgp = v;
	काष्ठा block_device *part;
	अचिन्हित दीर्घ idx;
	अक्षर buf[BDEVNAME_SIZE];

	/* Don't show non-partitionable हटाओable devices or empty devices */
	अगर (!get_capacity(sgp) || (!disk_max_parts(sgp) &&
				   (sgp->flags & GENHD_FL_REMOVABLE)))
		वापस 0;
	अगर (sgp->flags & GENHD_FL_SUPPRESS_PARTITION_INFO)
		वापस 0;

	rcu_पढ़ो_lock();
	xa_क्रम_each(&sgp->part_tbl, idx, part) अणु
		अगर (!bdev_nr_sectors(part))
			जारी;
		seq_म_लिखो(seqf, "%4d  %7d %10llu %s\n",
			   MAJOR(part->bd_dev), MINOR(part->bd_dev),
			   bdev_nr_sectors(part) >> 1,
			   disk_name(sgp, part->bd_partno, buf));
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations partitions_op = अणु
	.start	= show_partition_start,
	.next	= disk_seqf_next,
	.stop	= disk_seqf_stop,
	.show	= show_partition
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init genhd_device_init(व्योम)
अणु
	पूर्णांक error;

	block_class.dev_kobj = sysfs_dev_block_kobj;
	error = class_रेजिस्टर(&block_class);
	अगर (unlikely(error))
		वापस error;
	blk_dev_init();

	रेजिस्टर_blkdev(BLOCK_EXT_MAJOR, "blkext");

	/* create top-level block dir */
	अगर (!sysfs_deprecated)
		block_depr = kobject_create_and_add("block", शून्य);
	वापस 0;
पूर्ण

subsys_initcall(genhd_device_init);

अटल sमाप_प्रकार disk_range_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);

	वापस प्र_लिखो(buf, "%d\n", disk->minors);
पूर्ण

अटल sमाप_प्रकार disk_ext_range_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);

	वापस प्र_लिखो(buf, "%d\n", disk_max_parts(disk));
पूर्ण

अटल sमाप_प्रकार disk_removable_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);

	वापस प्र_लिखो(buf, "%d\n",
		       (disk->flags & GENHD_FL_REMOVABLE ? 1 : 0));
पूर्ण

अटल sमाप_प्रकार disk_hidden_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);

	वापस प्र_लिखो(buf, "%d\n",
		       (disk->flags & GENHD_FL_HIDDEN ? 1 : 0));
पूर्ण

अटल sमाप_प्रकार disk_ro_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);

	वापस प्र_लिखो(buf, "%d\n", get_disk_ro(disk) ? 1 : 0);
पूर्ण

sमाप_प्रकार part_size_show(काष्ठा device *dev,
		       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%llu\n", bdev_nr_sectors(dev_to_bdev(dev)));
पूर्ण

sमाप_प्रकार part_stat_show(काष्ठा device *dev,
		       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा block_device *bdev = dev_to_bdev(dev);
	काष्ठा request_queue *q = bdev->bd_disk->queue;
	काष्ठा disk_stats stat;
	अचिन्हित पूर्णांक inflight;

	part_stat_पढ़ो_all(bdev, &stat);
	अगर (queue_is_mq(q))
		inflight = blk_mq_in_flight(q, bdev);
	अन्यथा
		inflight = part_in_flight(bdev);

	वापस प्र_लिखो(buf,
		"%8lu %8lu %8llu %8u "
		"%8lu %8lu %8llu %8u "
		"%8u %8u %8u "
		"%8lu %8lu %8llu %8u "
		"%8lu %8u"
		"\n",
		stat.ios[STAT_READ],
		stat.merges[STAT_READ],
		(अचिन्हित दीर्घ दीर्घ)stat.sectors[STAT_READ],
		(अचिन्हित पूर्णांक)भाग_u64(stat.nsecs[STAT_READ], NSEC_PER_MSEC),
		stat.ios[STAT_WRITE],
		stat.merges[STAT_WRITE],
		(अचिन्हित दीर्घ दीर्घ)stat.sectors[STAT_WRITE],
		(अचिन्हित पूर्णांक)भाग_u64(stat.nsecs[STAT_WRITE], NSEC_PER_MSEC),
		inflight,
		jअगरfies_to_msecs(stat.io_ticks),
		(अचिन्हित पूर्णांक)भाग_u64(stat.nsecs[STAT_READ] +
				      stat.nsecs[STAT_WRITE] +
				      stat.nsecs[STAT_DISCARD] +
				      stat.nsecs[STAT_FLUSH],
						NSEC_PER_MSEC),
		stat.ios[STAT_DISCARD],
		stat.merges[STAT_DISCARD],
		(अचिन्हित दीर्घ दीर्घ)stat.sectors[STAT_DISCARD],
		(अचिन्हित पूर्णांक)भाग_u64(stat.nsecs[STAT_DISCARD], NSEC_PER_MSEC),
		stat.ios[STAT_FLUSH],
		(अचिन्हित पूर्णांक)भाग_u64(stat.nsecs[STAT_FLUSH], NSEC_PER_MSEC));
पूर्ण

sमाप_प्रकार part_inflight_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा block_device *bdev = dev_to_bdev(dev);
	काष्ठा request_queue *q = bdev->bd_disk->queue;
	अचिन्हित पूर्णांक inflight[2];

	अगर (queue_is_mq(q))
		blk_mq_in_flight_rw(q, bdev, inflight);
	अन्यथा
		part_in_flight_rw(bdev, inflight);

	वापस प्र_लिखो(buf, "%8u %8u\n", inflight[0], inflight[1]);
पूर्ण

अटल sमाप_प्रकार disk_capability_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);

	वापस प्र_लिखो(buf, "%x\n", disk->flags);
पूर्ण

अटल sमाप_प्रकार disk_alignment_offset_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);

	वापस प्र_लिखो(buf, "%d\n", queue_alignment_offset(disk->queue));
पूर्ण

अटल sमाप_प्रकार disk_discard_alignment_show(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);

	वापस प्र_लिखो(buf, "%d\n", queue_discard_alignment(disk->queue));
पूर्ण

अटल DEVICE_ATTR(range, 0444, disk_range_show, शून्य);
अटल DEVICE_ATTR(ext_range, 0444, disk_ext_range_show, शून्य);
अटल DEVICE_ATTR(removable, 0444, disk_removable_show, शून्य);
अटल DEVICE_ATTR(hidden, 0444, disk_hidden_show, शून्य);
अटल DEVICE_ATTR(ro, 0444, disk_ro_show, शून्य);
अटल DEVICE_ATTR(size, 0444, part_size_show, शून्य);
अटल DEVICE_ATTR(alignment_offset, 0444, disk_alignment_offset_show, शून्य);
अटल DEVICE_ATTR(discard_alignment, 0444, disk_discard_alignment_show, शून्य);
अटल DEVICE_ATTR(capability, 0444, disk_capability_show, शून्य);
अटल DEVICE_ATTR(stat, 0444, part_stat_show, शून्य);
अटल DEVICE_ATTR(inflight, 0444, part_inflight_show, शून्य);
अटल DEVICE_ATTR(badblocks, 0644, disk_badblocks_show, disk_badblocks_store);

#अगर_घोषित CONFIG_FAIL_MAKE_REQUEST
sमाप_प्रकार part_fail_show(काष्ठा device *dev,
		       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", dev_to_bdev(dev)->bd_make_it_fail);
पूर्ण

sमाप_प्रकार part_fail_store(काष्ठा device *dev,
			काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक i;

	अगर (count > 0 && माला_पूछो(buf, "%d", &i) > 0)
		dev_to_bdev(dev)->bd_make_it_fail = i;

	वापस count;
पूर्ण

अटल काष्ठा device_attribute dev_attr_fail =
	__ATTR(make-it-fail, 0644, part_fail_show, part_fail_store);
#पूर्ण_अगर /* CONFIG_FAIL_MAKE_REQUEST */

#अगर_घोषित CONFIG_FAIL_IO_TIMEOUT
अटल काष्ठा device_attribute dev_attr_fail_समयout =
	__ATTR(io-समयout-fail, 0644, part_समयout_show, part_समयout_store);
#पूर्ण_अगर

अटल काष्ठा attribute *disk_attrs[] = अणु
	&dev_attr_range.attr,
	&dev_attr_ext_range.attr,
	&dev_attr_removable.attr,
	&dev_attr_hidden.attr,
	&dev_attr_ro.attr,
	&dev_attr_size.attr,
	&dev_attr_alignment_offset.attr,
	&dev_attr_discard_alignment.attr,
	&dev_attr_capability.attr,
	&dev_attr_stat.attr,
	&dev_attr_inflight.attr,
	&dev_attr_badblocks.attr,
#अगर_घोषित CONFIG_FAIL_MAKE_REQUEST
	&dev_attr_fail.attr,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FAIL_IO_TIMEOUT
	&dev_attr_fail_समयout.attr,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल umode_t disk_visible(काष्ठा kobject *kobj, काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = container_of(kobj, typeof(*dev), kobj);
	काष्ठा gendisk *disk = dev_to_disk(dev);

	अगर (a == &dev_attr_badblocks.attr && !disk->bb)
		वापस 0;
	वापस a->mode;
पूर्ण

अटल काष्ठा attribute_group disk_attr_group = अणु
	.attrs = disk_attrs,
	.is_visible = disk_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *disk_attr_groups[] = अणु
	&disk_attr_group,
	शून्य
पूर्ण;

/**
 * disk_release - releases all allocated resources of the gendisk
 * @dev: the device representing this disk
 *
 * This function releases all allocated resources of the gendisk.
 *
 * Drivers which used __device_add_disk() have a gendisk with a request_queue
 * asचिन्हित. Since the request_queue sits on top of the gendisk क्रम these
 * drivers we also call blk_put_queue() क्रम them, and we expect the
 * request_queue refcount to reach 0 at this poपूर्णांक, and so the request_queue
 * will also be मुक्तd prior to the disk.
 *
 * Context: can sleep
 */
अटल व्योम disk_release(काष्ठा device *dev)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);

	might_sleep();

	blk_मुक्त_devt(dev->devt);
	disk_release_events(disk);
	kमुक्त(disk->अक्रमom);
	xa_destroy(&disk->part_tbl);
	bdput(disk->part0);
	अगर (disk->queue)
		blk_put_queue(disk->queue);
	kमुक्त(disk);
पूर्ण
काष्ठा class block_class = अणु
	.name		= "block",
पूर्ण;

अटल अक्षर *block_devnode(काष्ठा device *dev, umode_t *mode,
			   kuid_t *uid, kgid_t *gid)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);

	अगर (disk->fops->devnode)
		वापस disk->fops->devnode(disk, mode);
	वापस शून्य;
पूर्ण

स्थिर काष्ठा device_type disk_type = अणु
	.name		= "disk",
	.groups		= disk_attr_groups,
	.release	= disk_release,
	.devnode	= block_devnode,
पूर्ण;

#अगर_घोषित CONFIG_PROC_FS
/*
 * aggregate disk stat collector.  Uses the same stats that the sysfs
 * entries करो, above, but makes them available through one seq_file.
 *
 * The output looks suspiciously like /proc/partitions with a bunch of
 * extra fields.
 */
अटल पूर्णांक diskstats_show(काष्ठा seq_file *seqf, व्योम *v)
अणु
	काष्ठा gendisk *gp = v;
	काष्ठा block_device *hd;
	अक्षर buf[BDEVNAME_SIZE];
	अचिन्हित पूर्णांक inflight;
	काष्ठा disk_stats stat;
	अचिन्हित दीर्घ idx;

	/*
	अगर (&disk_to_dev(gp)->kobj.entry == block_class.devices.next)
		seq_माला_दो(seqf,	"major minor name"
				"     rio rmerge rsect ruse wio wmerge "
				"wsect wuse running use aveq"
				"\n\n");
	*/

	rcu_पढ़ो_lock();
	xa_क्रम_each(&gp->part_tbl, idx, hd) अणु
		अगर (bdev_is_partition(hd) && !bdev_nr_sectors(hd))
			जारी;
		part_stat_पढ़ो_all(hd, &stat);
		अगर (queue_is_mq(gp->queue))
			inflight = blk_mq_in_flight(gp->queue, hd);
		अन्यथा
			inflight = part_in_flight(hd);

		seq_म_लिखो(seqf, "%4d %7d %s "
			   "%lu %lu %lu %u "
			   "%lu %lu %lu %u "
			   "%u %u %u "
			   "%lu %lu %lu %u "
			   "%lu %u"
			   "\n",
			   MAJOR(hd->bd_dev), MINOR(hd->bd_dev),
			   disk_name(gp, hd->bd_partno, buf),
			   stat.ios[STAT_READ],
			   stat.merges[STAT_READ],
			   stat.sectors[STAT_READ],
			   (अचिन्हित पूर्णांक)भाग_u64(stat.nsecs[STAT_READ],
							NSEC_PER_MSEC),
			   stat.ios[STAT_WRITE],
			   stat.merges[STAT_WRITE],
			   stat.sectors[STAT_WRITE],
			   (अचिन्हित पूर्णांक)भाग_u64(stat.nsecs[STAT_WRITE],
							NSEC_PER_MSEC),
			   inflight,
			   jअगरfies_to_msecs(stat.io_ticks),
			   (अचिन्हित पूर्णांक)भाग_u64(stat.nsecs[STAT_READ] +
						 stat.nsecs[STAT_WRITE] +
						 stat.nsecs[STAT_DISCARD] +
						 stat.nsecs[STAT_FLUSH],
							NSEC_PER_MSEC),
			   stat.ios[STAT_DISCARD],
			   stat.merges[STAT_DISCARD],
			   stat.sectors[STAT_DISCARD],
			   (अचिन्हित पूर्णांक)भाग_u64(stat.nsecs[STAT_DISCARD],
						 NSEC_PER_MSEC),
			   stat.ios[STAT_FLUSH],
			   (अचिन्हित पूर्णांक)भाग_u64(stat.nsecs[STAT_FLUSH],
						 NSEC_PER_MSEC)
			);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations diskstats_op = अणु
	.start	= disk_seqf_start,
	.next	= disk_seqf_next,
	.stop	= disk_seqf_stop,
	.show	= diskstats_show
पूर्ण;

अटल पूर्णांक __init proc_genhd_init(व्योम)
अणु
	proc_create_seq("diskstats", 0, शून्य, &diskstats_op);
	proc_create_seq("partitions", 0, शून्य, &partitions_op);
	वापस 0;
पूर्ण
module_init(proc_genhd_init);
#पूर्ण_अगर /* CONFIG_PROC_FS */

dev_t blk_lookup_devt(स्थिर अक्षर *name, पूर्णांक partno)
अणु
	dev_t devt = MKDEV(0, 0);
	काष्ठा class_dev_iter iter;
	काष्ठा device *dev;

	class_dev_iter_init(&iter, &block_class, शून्य, &disk_type);
	जबतक ((dev = class_dev_iter_next(&iter))) अणु
		काष्ठा gendisk *disk = dev_to_disk(dev);
		काष्ठा block_device *part;

		अगर (म_भेद(dev_name(dev), name))
			जारी;

		अगर (partno < disk->minors) अणु
			/* We need to वापस the right devno, even
			 * अगर the partition करोesn't exist yet.
			 */
			devt = MKDEV(MAJOR(dev->devt),
				     MINOR(dev->devt) + partno);
			अवरोध;
		पूर्ण
		part = bdget_disk(disk, partno);
		अगर (part) अणु
			devt = part->bd_dev;
			bdput(part);
			अवरोध;
		पूर्ण
	पूर्ण
	class_dev_iter_निकास(&iter);
	वापस devt;
पूर्ण

काष्ठा gendisk *__alloc_disk_node(पूर्णांक minors, पूर्णांक node_id)
अणु
	काष्ठा gendisk *disk;

	अगर (minors > DISK_MAX_PARTS) अणु
		prपूर्णांकk(KERN_ERR
			"block: can't allocate more than %d partitions\n",
			DISK_MAX_PARTS);
		minors = DISK_MAX_PARTS;
	पूर्ण

	disk = kzalloc_node(माप(काष्ठा gendisk), GFP_KERNEL, node_id);
	अगर (!disk)
		वापस शून्य;

	disk->part0 = bdev_alloc(disk, 0);
	अगर (!disk->part0)
		जाओ out_मुक्त_disk;

	disk->node_id = node_id;
	xa_init(&disk->part_tbl);
	अगर (xa_insert(&disk->part_tbl, 0, disk->part0, GFP_KERNEL))
		जाओ out_destroy_part_tbl;

	disk->minors = minors;
	अक्रम_initialize_disk(disk);
	disk_to_dev(disk)->class = &block_class;
	disk_to_dev(disk)->type = &disk_type;
	device_initialize(disk_to_dev(disk));
	वापस disk;

out_destroy_part_tbl:
	xa_destroy(&disk->part_tbl);
	bdput(disk->part0);
out_मुक्त_disk:
	kमुक्त(disk);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(__alloc_disk_node);

/**
 * put_disk - decrements the gendisk refcount
 * @disk: the काष्ठा gendisk to decrement the refcount क्रम
 *
 * This decrements the refcount क्रम the काष्ठा gendisk. When this reaches 0
 * we'll have disk_release() called.
 *
 * Context: Any context, but the last reference must not be dropped from
 *          atomic context.
 */
व्योम put_disk(काष्ठा gendisk *disk)
अणु
	अगर (disk)
		put_device(disk_to_dev(disk));
पूर्ण
EXPORT_SYMBOL(put_disk);

अटल व्योम set_disk_ro_uevent(काष्ठा gendisk *gd, पूर्णांक ro)
अणु
	अक्षर event[] = "DISK_RO=1";
	अक्षर *envp[] = अणु event, शून्य पूर्ण;

	अगर (!ro)
		event[8] = '0';
	kobject_uevent_env(&disk_to_dev(gd)->kobj, KOBJ_CHANGE, envp);
पूर्ण

/**
 * set_disk_ro - set a gendisk पढ़ो-only
 * @disk:	gendisk to operate on
 * @पढ़ो_only:	%true to set the disk पढ़ो-only, %false set the disk पढ़ो/ग_लिखो
 *
 * This function is used to indicate whether a given disk device should have its
 * पढ़ो-only flag set. set_disk_ro() is typically used by device drivers to
 * indicate whether the underlying physical device is ग_लिखो-रक्षित.
 */
व्योम set_disk_ro(काष्ठा gendisk *disk, bool पढ़ो_only)
अणु
	अगर (पढ़ो_only) अणु
		अगर (test_and_set_bit(GD_READ_ONLY, &disk->state))
			वापस;
	पूर्ण अन्यथा अणु
		अगर (!test_and_clear_bit(GD_READ_ONLY, &disk->state))
			वापस;
	पूर्ण
	set_disk_ro_uevent(disk, पढ़ो_only);
पूर्ण
EXPORT_SYMBOL(set_disk_ro);

पूर्णांक bdev_पढ़ो_only(काष्ठा block_device *bdev)
अणु
	वापस bdev->bd_पढ़ो_only || get_disk_ro(bdev->bd_disk);
पूर्ण
EXPORT_SYMBOL(bdev_पढ़ो_only);

/*
 * Disk events - monitor disk events like media change and eject request.
 */
काष्ठा disk_events अणु
	काष्ठा list_head	node;		/* all disk_event's */
	काष्ठा gendisk		*disk;		/* the associated disk */
	spinlock_t		lock;

	काष्ठा mutex		block_mutex;	/* protects blocking */
	पूर्णांक			block;		/* event blocking depth */
	अचिन्हित पूर्णांक		pending;	/* events alपढ़ोy sent out */
	अचिन्हित पूर्णांक		clearing;	/* events being cleared */

	दीर्घ			poll_msecs;	/* पूर्णांकerval, -1 क्रम शेष */
	काष्ठा delayed_work	dwork;
पूर्ण;

अटल स्थिर अक्षर *disk_events_strs[] = अणु
	[ilog2(DISK_EVENT_MEDIA_CHANGE)]	= "media_change",
	[ilog2(DISK_EVENT_EJECT_REQUEST)]	= "eject_request",
पूर्ण;

अटल अक्षर *disk_uevents[] = अणु
	[ilog2(DISK_EVENT_MEDIA_CHANGE)]	= "DISK_MEDIA_CHANGE=1",
	[ilog2(DISK_EVENT_EJECT_REQUEST)]	= "DISK_EJECT_REQUEST=1",
पूर्ण;

/* list of all disk_events */
अटल DEFINE_MUTEX(disk_events_mutex);
अटल LIST_HEAD(disk_events);

/* disable in-kernel polling by शेष */
अटल अचिन्हित दीर्घ disk_events_dfl_poll_msecs;

अटल अचिन्हित दीर्घ disk_events_poll_jअगरfies(काष्ठा gendisk *disk)
अणु
	काष्ठा disk_events *ev = disk->ev;
	दीर्घ पूर्णांकv_msecs = 0;

	/*
	 * If device-specअगरic poll पूर्णांकerval is set, always use it.  If
	 * the शेष is being used, poll अगर the POLL flag is set.
	 */
	अगर (ev->poll_msecs >= 0)
		पूर्णांकv_msecs = ev->poll_msecs;
	अन्यथा अगर (disk->event_flags & DISK_EVENT_FLAG_POLL)
		पूर्णांकv_msecs = disk_events_dfl_poll_msecs;

	वापस msecs_to_jअगरfies(पूर्णांकv_msecs);
पूर्ण

/**
 * disk_block_events - block and flush disk event checking
 * @disk: disk to block events क्रम
 *
 * On वापस from this function, it is guaranteed that event checking
 * isn't in progress and won't happen until unblocked by
 * disk_unblock_events().  Events blocking is counted and the actual
 * unblocking happens after the matching number of unblocks are करोne.
 *
 * Note that this पूर्णांकentionally करोes not block event checking from
 * disk_clear_events().
 *
 * CONTEXT:
 * Might sleep.
 */
व्योम disk_block_events(काष्ठा gendisk *disk)
अणु
	काष्ठा disk_events *ev = disk->ev;
	अचिन्हित दीर्घ flags;
	bool cancel;

	अगर (!ev)
		वापस;

	/*
	 * Outer mutex ensures that the first blocker completes canceling
	 * the event work beक्रमe further blockers are allowed to finish.
	 */
	mutex_lock(&ev->block_mutex);

	spin_lock_irqsave(&ev->lock, flags);
	cancel = !ev->block++;
	spin_unlock_irqrestore(&ev->lock, flags);

	अगर (cancel)
		cancel_delayed_work_sync(&disk->ev->dwork);

	mutex_unlock(&ev->block_mutex);
पूर्ण

अटल व्योम __disk_unblock_events(काष्ठा gendisk *disk, bool check_now)
अणु
	काष्ठा disk_events *ev = disk->ev;
	अचिन्हित दीर्घ पूर्णांकv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ev->lock, flags);

	अगर (WARN_ON_ONCE(ev->block <= 0))
		जाओ out_unlock;

	अगर (--ev->block)
		जाओ out_unlock;

	पूर्णांकv = disk_events_poll_jअगरfies(disk);
	अगर (check_now)
		queue_delayed_work(प्रणाली_मुक्तzable_घातer_efficient_wq,
				&ev->dwork, 0);
	अन्यथा अगर (पूर्णांकv)
		queue_delayed_work(प्रणाली_मुक्तzable_घातer_efficient_wq,
				&ev->dwork, पूर्णांकv);
out_unlock:
	spin_unlock_irqrestore(&ev->lock, flags);
पूर्ण

/**
 * disk_unblock_events - unblock disk event checking
 * @disk: disk to unblock events क्रम
 *
 * Unकरो disk_block_events().  When the block count reaches zero, it
 * starts events polling अगर configured.
 *
 * CONTEXT:
 * Don't care.  Safe to call from irq context.
 */
व्योम disk_unblock_events(काष्ठा gendisk *disk)
अणु
	अगर (disk->ev)
		__disk_unblock_events(disk, false);
पूर्ण

/**
 * disk_flush_events - schedule immediate event checking and flushing
 * @disk: disk to check and flush events क्रम
 * @mask: events to flush
 *
 * Schedule immediate event checking on @disk अगर not blocked.  Events in
 * @mask are scheduled to be cleared from the driver.  Note that this
 * करोesn't clear the events from @disk->ev.
 *
 * CONTEXT:
 * If @mask is non-zero must be called with bdev->bd_mutex held.
 */
व्योम disk_flush_events(काष्ठा gendisk *disk, अचिन्हित पूर्णांक mask)
अणु
	काष्ठा disk_events *ev = disk->ev;

	अगर (!ev)
		वापस;

	spin_lock_irq(&ev->lock);
	ev->clearing |= mask;
	अगर (!ev->block)
		mod_delayed_work(प्रणाली_मुक्तzable_घातer_efficient_wq,
				&ev->dwork, 0);
	spin_unlock_irq(&ev->lock);
पूर्ण

/**
 * disk_clear_events - synchronously check, clear and वापस pending events
 * @disk: disk to fetch and clear events from
 * @mask: mask of events to be fetched and cleared
 *
 * Disk events are synchronously checked and pending events in @mask
 * are cleared and वापसed.  This ignores the block count.
 *
 * CONTEXT:
 * Might sleep.
 */
अटल अचिन्हित पूर्णांक disk_clear_events(काष्ठा gendisk *disk, अचिन्हित पूर्णांक mask)
अणु
	काष्ठा disk_events *ev = disk->ev;
	अचिन्हित पूर्णांक pending;
	अचिन्हित पूर्णांक clearing = mask;

	अगर (!ev)
		वापस 0;

	disk_block_events(disk);

	/*
	 * store the जोड़ of mask and ev->clearing on the stack so that the
	 * race with disk_flush_events करोes not cause ambiguity (ev->clearing
	 * can still be modअगरied even अगर events are blocked).
	 */
	spin_lock_irq(&ev->lock);
	clearing |= ev->clearing;
	ev->clearing = 0;
	spin_unlock_irq(&ev->lock);

	disk_check_events(ev, &clearing);
	/*
	 * अगर ev->clearing is not 0, the disk_flush_events got called in the
	 * middle of this function, so we want to run the workfn without delay.
	 */
	__disk_unblock_events(disk, ev->clearing ? true : false);

	/* then, fetch and clear pending events */
	spin_lock_irq(&ev->lock);
	pending = ev->pending & mask;
	ev->pending &= ~mask;
	spin_unlock_irq(&ev->lock);
	WARN_ON_ONCE(clearing & mask);

	वापस pending;
पूर्ण

/**
 * bdev_check_media_change - check अगर a removable media has been changed
 * @bdev: block device to check
 *
 * Check whether a removable media has been changed, and attempt to मुक्त all
 * dentries and inodes and invalidates all block device page cache entries in
 * that हाल.
 *
 * Returns %true अगर the block device changed, or %false अगर not.
 */
bool bdev_check_media_change(काष्ठा block_device *bdev)
अणु
	अचिन्हित पूर्णांक events;

	events = disk_clear_events(bdev->bd_disk, DISK_EVENT_MEDIA_CHANGE |
				   DISK_EVENT_EJECT_REQUEST);
	अगर (!(events & DISK_EVENT_MEDIA_CHANGE))
		वापस false;

	अगर (__invalidate_device(bdev, true))
		pr_warn("VFS: busy inodes on changed media %s\n",
			bdev->bd_disk->disk_name);
	set_bit(GD_NEED_PART_SCAN, &bdev->bd_disk->state);
	वापस true;
पूर्ण
EXPORT_SYMBOL(bdev_check_media_change);

/*
 * Separate this part out so that a dअगरferent poपूर्णांकer क्रम clearing_ptr can be
 * passed in क्रम disk_clear_events.
 */
अटल व्योम disk_events_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा disk_events *ev = container_of(dwork, काष्ठा disk_events, dwork);

	disk_check_events(ev, &ev->clearing);
पूर्ण

अटल व्योम disk_check_events(काष्ठा disk_events *ev,
			      अचिन्हित पूर्णांक *clearing_ptr)
अणु
	काष्ठा gendisk *disk = ev->disk;
	अक्षर *envp[ARRAY_SIZE(disk_uevents) + 1] = अणु पूर्ण;
	अचिन्हित पूर्णांक clearing = *clearing_ptr;
	अचिन्हित पूर्णांक events;
	अचिन्हित दीर्घ पूर्णांकv;
	पूर्णांक nr_events = 0, i;

	/* check events */
	events = disk->fops->check_events(disk, clearing);

	/* accumulate pending events and schedule next poll अगर necessary */
	spin_lock_irq(&ev->lock);

	events &= ~ev->pending;
	ev->pending |= events;
	*clearing_ptr &= ~clearing;

	पूर्णांकv = disk_events_poll_jअगरfies(disk);
	अगर (!ev->block && पूर्णांकv)
		queue_delayed_work(प्रणाली_मुक्तzable_घातer_efficient_wq,
				&ev->dwork, पूर्णांकv);

	spin_unlock_irq(&ev->lock);

	/*
	 * Tell userland about new events.  Only the events listed in
	 * @disk->events are reported, and only अगर DISK_EVENT_FLAG_UEVENT
	 * is set. Otherwise, events are processed पूर्णांकernally but never
	 * get reported to userland.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(disk_uevents); i++)
		अगर ((events & disk->events & (1 << i)) &&
		    (disk->event_flags & DISK_EVENT_FLAG_UEVENT))
			envp[nr_events++] = disk_uevents[i];

	अगर (nr_events)
		kobject_uevent_env(&disk_to_dev(disk)->kobj, KOBJ_CHANGE, envp);
पूर्ण

/*
 * A disk events enabled device has the following sysfs nodes under
 * its /sys/block/X/ directory.
 *
 * events		: list of all supported events
 * events_async		: list of events which can be detected w/o polling
 *			  (always empty, only क्रम backwards compatibility)
 * events_poll_msecs	: polling पूर्णांकerval, 0: disable, -1: प्रणाली शेष
 */
अटल sमाप_प्रकार __disk_events_show(अचिन्हित पूर्णांक events, अक्षर *buf)
अणु
	स्थिर अक्षर *delim = "";
	sमाप_प्रकार pos = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(disk_events_strs); i++)
		अगर (events & (1 << i)) अणु
			pos += प्र_लिखो(buf + pos, "%s%s",
				       delim, disk_events_strs[i]);
			delim = " ";
		पूर्ण
	अगर (pos)
		pos += प्र_लिखो(buf + pos, "\n");
	वापस pos;
पूर्ण

अटल sमाप_प्रकार disk_events_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);

	अगर (!(disk->event_flags & DISK_EVENT_FLAG_UEVENT))
		वापस 0;

	वापस __disk_events_show(disk->events, buf);
पूर्ण

अटल sमाप_प्रकार disk_events_async_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार disk_events_poll_msecs_show(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);

	अगर (!disk->ev)
		वापस प्र_लिखो(buf, "-1\n");

	वापस प्र_लिखो(buf, "%ld\n", disk->ev->poll_msecs);
पूर्ण

अटल sमाप_प्रकार disk_events_poll_msecs_store(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);
	दीर्घ पूर्णांकv;

	अगर (!count || !माला_पूछो(buf, "%ld", &पूर्णांकv))
		वापस -EINVAL;

	अगर (पूर्णांकv < 0 && पूर्णांकv != -1)
		वापस -EINVAL;

	अगर (!disk->ev)
		वापस -ENODEV;

	disk_block_events(disk);
	disk->ev->poll_msecs = पूर्णांकv;
	__disk_unblock_events(disk, true);

	वापस count;
पूर्ण

अटल स्थिर DEVICE_ATTR(events, 0444, disk_events_show, शून्य);
अटल स्थिर DEVICE_ATTR(events_async, 0444, disk_events_async_show, शून्य);
अटल स्थिर DEVICE_ATTR(events_poll_msecs, 0644,
			 disk_events_poll_msecs_show,
			 disk_events_poll_msecs_store);

अटल स्थिर काष्ठा attribute *disk_events_attrs[] = अणु
	&dev_attr_events.attr,
	&dev_attr_events_async.attr,
	&dev_attr_events_poll_msecs.attr,
	शून्य,
पूर्ण;

/*
 * The शेष polling पूर्णांकerval can be specअगरied by the kernel
 * parameter block.events_dfl_poll_msecs which शेषs to 0
 * (disable).  This can also be modअगरied runसमय by writing to
 * /sys/module/block/parameters/events_dfl_poll_msecs.
 */
अटल पूर्णांक disk_events_set_dfl_poll_msecs(स्थिर अक्षर *val,
					  स्थिर काष्ठा kernel_param *kp)
अणु
	काष्ठा disk_events *ev;
	पूर्णांक ret;

	ret = param_set_uदीर्घ(val, kp);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&disk_events_mutex);

	list_क्रम_each_entry(ev, &disk_events, node)
		disk_flush_events(ev->disk, 0);

	mutex_unlock(&disk_events_mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops disk_events_dfl_poll_msecs_param_ops = अणु
	.set	= disk_events_set_dfl_poll_msecs,
	.get	= param_get_uदीर्घ,
पूर्ण;

#अघोषित MODULE_PARAM_PREFIX
#घोषणा MODULE_PARAM_PREFIX	"block."

module_param_cb(events_dfl_poll_msecs, &disk_events_dfl_poll_msecs_param_ops,
		&disk_events_dfl_poll_msecs, 0644);

/*
 * disk_अणुalloc|add|del|releaseपूर्ण_events - initialize and destroy disk_events.
 */
अटल व्योम disk_alloc_events(काष्ठा gendisk *disk)
अणु
	काष्ठा disk_events *ev;

	अगर (!disk->fops->check_events || !disk->events)
		वापस;

	ev = kzalloc(माप(*ev), GFP_KERNEL);
	अगर (!ev) अणु
		pr_warn("%s: failed to initialize events\n", disk->disk_name);
		वापस;
	पूर्ण

	INIT_LIST_HEAD(&ev->node);
	ev->disk = disk;
	spin_lock_init(&ev->lock);
	mutex_init(&ev->block_mutex);
	ev->block = 1;
	ev->poll_msecs = -1;
	INIT_DELAYED_WORK(&ev->dwork, disk_events_workfn);

	disk->ev = ev;
पूर्ण

अटल व्योम disk_add_events(काष्ठा gendisk *disk)
अणु
	/* FIXME: error handling */
	अगर (sysfs_create_files(&disk_to_dev(disk)->kobj, disk_events_attrs) < 0)
		pr_warn("%s: failed to create sysfs files for events\n",
			disk->disk_name);

	अगर (!disk->ev)
		वापस;

	mutex_lock(&disk_events_mutex);
	list_add_tail(&disk->ev->node, &disk_events);
	mutex_unlock(&disk_events_mutex);

	/*
	 * Block count is initialized to 1 and the following initial
	 * unblock kicks it पूर्णांकo action.
	 */
	__disk_unblock_events(disk, true);
पूर्ण

अटल व्योम disk_del_events(काष्ठा gendisk *disk)
अणु
	अगर (disk->ev) अणु
		disk_block_events(disk);

		mutex_lock(&disk_events_mutex);
		list_del_init(&disk->ev->node);
		mutex_unlock(&disk_events_mutex);
	पूर्ण

	sysfs_हटाओ_files(&disk_to_dev(disk)->kobj, disk_events_attrs);
पूर्ण

अटल व्योम disk_release_events(काष्ठा gendisk *disk)
अणु
	/* the block count should be 1 from disk_del_events() */
	WARN_ON_ONCE(disk->ev && disk->ev->block != 1);
	kमुक्त(disk->ev);
पूर्ण
