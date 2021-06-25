<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 1991-1998  Linus Torvalds
 * Re-organised Feb 1998 Russell King
 * Copyright (C) 2020 Christoph Hellwig
 */
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/genhd.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/blktrace_api.h>
#समावेश <linux/raid/detect.h>
#समावेश "check.h"

अटल पूर्णांक (*check_part[])(काष्ठा parsed_partitions *) = अणु
	/*
	 * Probe partition क्रमmats with tables at disk address 0
	 * that also have an ADFS boot block at 0xdc0.
	 */
#अगर_घोषित CONFIG_ACORN_PARTITION_ICS
	adfspart_check_ICS,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ACORN_PARTITION_POWERTEC
	adfspart_check_POWERTEC,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ACORN_PARTITION_EESOX
	adfspart_check_EESOX,
#पूर्ण_अगर

	/*
	 * Now move on to क्रमmats that only have partition info at
	 * disk address 0xdc0.  Since these may also have stale
	 * PC/BIOS partition tables, they need to come beक्रमe
	 * the msकरोs entry.
	 */
#अगर_घोषित CONFIG_ACORN_PARTITION_CUMANA
	adfspart_check_CUMANA,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ACORN_PARTITION_ADFS
	adfspart_check_ADFS,
#पूर्ण_अगर

#अगर_घोषित CONFIG_CMDLINE_PARTITION
	cmdline_partition,
#पूर्ण_अगर
#अगर_घोषित CONFIG_EFI_PARTITION
	efi_partition,		/* this must come beक्रमe msकरोs */
#पूर्ण_अगर
#अगर_घोषित CONFIG_SGI_PARTITION
	sgi_partition,
#पूर्ण_अगर
#अगर_घोषित CONFIG_LDM_PARTITION
	ldm_partition,		/* this must come beक्रमe msकरोs */
#पूर्ण_अगर
#अगर_घोषित CONFIG_MSDOS_PARTITION
	msकरोs_partition,
#पूर्ण_अगर
#अगर_घोषित CONFIG_OSF_PARTITION
	osf_partition,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SUN_PARTITION
	sun_partition,
#पूर्ण_अगर
#अगर_घोषित CONFIG_AMIGA_PARTITION
	amiga_partition,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATARI_PARTITION
	atari_partition,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MAC_PARTITION
	mac_partition,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ULTRIX_PARTITION
	ultrix_partition,
#पूर्ण_अगर
#अगर_घोषित CONFIG_IBM_PARTITION
	ibm_partition,
#पूर्ण_अगर
#अगर_घोषित CONFIG_KARMA_PARTITION
	karma_partition,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSV68_PARTITION
	sysv68_partition,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल व्योम bdev_set_nr_sectors(काष्ठा block_device *bdev, sector_t sectors)
अणु
	spin_lock(&bdev->bd_size_lock);
	i_size_ग_लिखो(bdev->bd_inode, (loff_t)sectors << SECTOR_SHIFT);
	spin_unlock(&bdev->bd_size_lock);
पूर्ण

अटल काष्ठा parsed_partitions *allocate_partitions(काष्ठा gendisk *hd)
अणु
	काष्ठा parsed_partitions *state;
	पूर्णांक nr;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	nr = disk_max_parts(hd);
	state->parts = vzalloc(array_size(nr, माप(state->parts[0])));
	अगर (!state->parts) अणु
		kमुक्त(state);
		वापस शून्य;
	पूर्ण

	state->limit = nr;

	वापस state;
पूर्ण

अटल व्योम मुक्त_partitions(काष्ठा parsed_partitions *state)
अणु
	vमुक्त(state->parts);
	kमुक्त(state);
पूर्ण

अटल काष्ठा parsed_partitions *check_partition(काष्ठा gendisk *hd,
		काष्ठा block_device *bdev)
अणु
	काष्ठा parsed_partitions *state;
	पूर्णांक i, res, err;

	state = allocate_partitions(hd);
	अगर (!state)
		वापस शून्य;
	state->pp_buf = (अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!state->pp_buf) अणु
		मुक्त_partitions(state);
		वापस शून्य;
	पूर्ण
	state->pp_buf[0] = '\0';

	state->bdev = bdev;
	disk_name(hd, 0, state->name);
	snम_लिखो(state->pp_buf, PAGE_SIZE, " %s:", state->name);
	अगर (है_अंक(state->name[म_माप(state->name)-1]))
		प्र_लिखो(state->name, "p");

	i = res = err = 0;
	जबतक (!res && check_part[i]) अणु
		स_रखो(state->parts, 0, state->limit * माप(state->parts[0]));
		res = check_part[i++](state);
		अगर (res < 0) अणु
			/*
			 * We have hit an I/O error which we करोn't report now.
			 * But record it, and let the others करो their job.
			 */
			err = res;
			res = 0;
		पूर्ण

	पूर्ण
	अगर (res > 0) अणु
		prपूर्णांकk(KERN_INFO "%s", state->pp_buf);

		मुक्त_page((अचिन्हित दीर्घ)state->pp_buf);
		वापस state;
	पूर्ण
	अगर (state->access_beyond_eod)
		err = -ENOSPC;
	/*
	 * The partition is unrecognized. So report I/O errors अगर there were any
	 */
	अगर (err)
		res = err;
	अगर (res) अणु
		strlcat(state->pp_buf,
			" unable to read partition table\n", PAGE_SIZE);
		prपूर्णांकk(KERN_INFO "%s", state->pp_buf);
	पूर्ण

	मुक्त_page((अचिन्हित दीर्घ)state->pp_buf);
	मुक्त_partitions(state);
	वापस ERR_PTR(res);
पूर्ण

अटल sमाप_प्रकार part_partition_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", dev_to_bdev(dev)->bd_partno);
पूर्ण

अटल sमाप_प्रकार part_start_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%llu\n", dev_to_bdev(dev)->bd_start_sect);
पूर्ण

अटल sमाप_प्रकार part_ro_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", bdev_पढ़ो_only(dev_to_bdev(dev)));
पूर्ण

अटल sमाप_प्रकार part_alignment_offset_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा block_device *bdev = dev_to_bdev(dev);

	वापस प्र_लिखो(buf, "%u\n",
		queue_limit_alignment_offset(&bdev->bd_disk->queue->limits,
				bdev->bd_start_sect));
पूर्ण

अटल sमाप_प्रकार part_discard_alignment_show(काष्ठा device *dev,
					   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा block_device *bdev = dev_to_bdev(dev);

	वापस प्र_लिखो(buf, "%u\n",
		queue_limit_discard_alignment(&bdev->bd_disk->queue->limits,
				bdev->bd_start_sect));
पूर्ण

अटल DEVICE_ATTR(partition, 0444, part_partition_show, शून्य);
अटल DEVICE_ATTR(start, 0444, part_start_show, शून्य);
अटल DEVICE_ATTR(size, 0444, part_size_show, शून्य);
अटल DEVICE_ATTR(ro, 0444, part_ro_show, शून्य);
अटल DEVICE_ATTR(alignment_offset, 0444, part_alignment_offset_show, शून्य);
अटल DEVICE_ATTR(discard_alignment, 0444, part_discard_alignment_show, शून्य);
अटल DEVICE_ATTR(stat, 0444, part_stat_show, शून्य);
अटल DEVICE_ATTR(inflight, 0444, part_inflight_show, शून्य);
#अगर_घोषित CONFIG_FAIL_MAKE_REQUEST
अटल काष्ठा device_attribute dev_attr_fail =
	__ATTR(make-it-fail, 0644, part_fail_show, part_fail_store);
#पूर्ण_अगर

अटल काष्ठा attribute *part_attrs[] = अणु
	&dev_attr_partition.attr,
	&dev_attr_start.attr,
	&dev_attr_size.attr,
	&dev_attr_ro.attr,
	&dev_attr_alignment_offset.attr,
	&dev_attr_discard_alignment.attr,
	&dev_attr_stat.attr,
	&dev_attr_inflight.attr,
#अगर_घोषित CONFIG_FAIL_MAKE_REQUEST
	&dev_attr_fail.attr,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल काष्ठा attribute_group part_attr_group = अणु
	.attrs = part_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *part_attr_groups[] = अणु
	&part_attr_group,
#अगर_घोषित CONFIG_BLK_DEV_IO_TRACE
	&blk_trace_attr_group,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल व्योम part_release(काष्ठा device *dev)
अणु
	blk_मुक्त_devt(dev->devt);
	bdput(dev_to_bdev(dev));
पूर्ण

अटल पूर्णांक part_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा block_device *part = dev_to_bdev(dev);

	add_uevent_var(env, "PARTN=%u", part->bd_partno);
	अगर (part->bd_meta_info && part->bd_meta_info->volname[0])
		add_uevent_var(env, "PARTNAME=%s", part->bd_meta_info->volname);
	वापस 0;
पूर्ण

काष्ठा device_type part_type = अणु
	.name		= "partition",
	.groups		= part_attr_groups,
	.release	= part_release,
	.uevent		= part_uevent,
पूर्ण;

/*
 * Must be called either with bd_mutex held, beक्रमe a disk can be खोलोed or
 * after all disk users are gone.
 */
अटल व्योम delete_partition(काष्ठा block_device *part)
अणु
	fsync_bdev(part);
	__invalidate_device(part, true);

	xa_erase(&part->bd_disk->part_tbl, part->bd_partno);
	kobject_put(part->bd_holder_dir);
	device_del(&part->bd_device);

	/*
	 * Remove the block device from the inode hash, so that it cannot be
	 * looked up any more even when खोलोers still hold references.
	 */
	हटाओ_inode_hash(part->bd_inode);

	put_device(&part->bd_device);
पूर्ण

अटल sमाप_प्रकार whole_disk_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस 0;
पूर्ण
अटल DEVICE_ATTR(whole_disk, 0444, whole_disk_show, शून्य);

/*
 * Must be called either with bd_mutex held, beक्रमe a disk can be खोलोed or
 * after all disk users are gone.
 */
अटल काष्ठा block_device *add_partition(काष्ठा gendisk *disk, पूर्णांक partno,
				sector_t start, sector_t len, पूर्णांक flags,
				काष्ठा partition_meta_info *info)
अणु
	dev_t devt = MKDEV(0, 0);
	काष्ठा device *ddev = disk_to_dev(disk);
	काष्ठा device *pdev;
	काष्ठा block_device *bdev;
	स्थिर अक्षर *dname;
	पूर्णांक err;

	/*
	 * disk_max_parts() won't be zero, either GENHD_FL_EXT_DEVT is set
	 * or 'minors' is passed to alloc_disk().
	 */
	अगर (partno >= disk_max_parts(disk))
		वापस ERR_PTR(-EINVAL);

	/*
	 * Partitions are not supported on zoned block devices that are used as
	 * such.
	 */
	चयन (disk->queue->limits.zoned) अणु
	हाल BLK_ZONED_HM:
		pr_warn("%s: partitions not supported on host managed zoned block device\n",
			disk->disk_name);
		वापस ERR_PTR(-ENXIO);
	हाल BLK_ZONED_HA:
		pr_info("%s: disabling host aware zoned block device support due to partitions\n",
			disk->disk_name);
		blk_queue_set_zoned(disk, BLK_ZONED_NONE);
		अवरोध;
	हाल BLK_ZONED_NONE:
		अवरोध;
	पूर्ण

	अगर (xa_load(&disk->part_tbl, partno))
		वापस ERR_PTR(-EBUSY);

	bdev = bdev_alloc(disk, partno);
	अगर (!bdev)
		वापस ERR_PTR(-ENOMEM);

	bdev->bd_start_sect = start;
	bdev_set_nr_sectors(bdev, len);

	अगर (info) अणु
		err = -ENOMEM;
		bdev->bd_meta_info = kmemdup(info, माप(*info), GFP_KERNEL);
		अगर (!bdev->bd_meta_info)
			जाओ out_bdput;
	पूर्ण

	pdev = &bdev->bd_device;
	dname = dev_name(ddev);
	अगर (है_अंक(dname[म_माप(dname) - 1]))
		dev_set_name(pdev, "%sp%d", dname, partno);
	अन्यथा
		dev_set_name(pdev, "%s%d", dname, partno);

	device_initialize(pdev);
	pdev->class = &block_class;
	pdev->type = &part_type;
	pdev->parent = ddev;

	err = blk_alloc_devt(bdev, &devt);
	अगर (err)
		जाओ out_put;
	pdev->devt = devt;

	/* delay uevent until 'holders' subdir is created */
	dev_set_uevent_suppress(pdev, 1);
	err = device_add(pdev);
	अगर (err)
		जाओ out_put;

	err = -ENOMEM;
	bdev->bd_holder_dir = kobject_create_and_add("holders", &pdev->kobj);
	अगर (!bdev->bd_holder_dir)
		जाओ out_del;

	dev_set_uevent_suppress(pdev, 0);
	अगर (flags & ADDPART_FLAG_WHOLEDISK) अणु
		err = device_create_file(pdev, &dev_attr_whole_disk);
		अगर (err)
			जाओ out_del;
	पूर्ण

	/* everything is up and running, commence */
	err = xa_insert(&disk->part_tbl, partno, bdev, GFP_KERNEL);
	अगर (err)
		जाओ out_del;
	bdev_add(bdev, devt);

	/* suppress uevent अगर the disk suppresses it */
	अगर (!dev_get_uevent_suppress(ddev))
		kobject_uevent(&pdev->kobj, KOBJ_ADD);
	वापस bdev;

out_bdput:
	bdput(bdev);
	वापस ERR_PTR(err);
out_del:
	kobject_put(bdev->bd_holder_dir);
	device_del(pdev);
out_put:
	put_device(pdev);
	वापस ERR_PTR(err);
पूर्ण

अटल bool partition_overlaps(काष्ठा gendisk *disk, sector_t start,
		sector_t length, पूर्णांक skip_partno)
अणु
	काष्ठा block_device *part;
	bool overlap = false;
	अचिन्हित दीर्घ idx;

	rcu_पढ़ो_lock();
	xa_क्रम_each_start(&disk->part_tbl, idx, part, 1) अणु
		अगर (part->bd_partno != skip_partno &&
		    start < part->bd_start_sect + bdev_nr_sectors(part) &&
		    start + length > part->bd_start_sect) अणु
			overlap = true;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस overlap;
पूर्ण

पूर्णांक bdev_add_partition(काष्ठा block_device *bdev, पूर्णांक partno,
		sector_t start, sector_t length)
अणु
	काष्ठा block_device *part;

	mutex_lock(&bdev->bd_mutex);
	अगर (partition_overlaps(bdev->bd_disk, start, length, -1)) अणु
		mutex_unlock(&bdev->bd_mutex);
		वापस -EBUSY;
	पूर्ण

	part = add_partition(bdev->bd_disk, partno, start, length,
			ADDPART_FLAG_NONE, शून्य);
	mutex_unlock(&bdev->bd_mutex);
	वापस PTR_ERR_OR_ZERO(part);
पूर्ण

पूर्णांक bdev_del_partition(काष्ठा block_device *bdev, पूर्णांक partno)
अणु
	काष्ठा block_device *part;
	पूर्णांक ret;

	part = bdget_disk(bdev->bd_disk, partno);
	अगर (!part)
		वापस -ENXIO;

	mutex_lock(&part->bd_mutex);
	mutex_lock_nested(&bdev->bd_mutex, 1);

	ret = -EBUSY;
	अगर (part->bd_खोलोers)
		जाओ out_unlock;

	delete_partition(part);
	ret = 0;
out_unlock:
	mutex_unlock(&bdev->bd_mutex);
	mutex_unlock(&part->bd_mutex);
	bdput(part);
	वापस ret;
पूर्ण

पूर्णांक bdev_resize_partition(काष्ठा block_device *bdev, पूर्णांक partno,
		sector_t start, sector_t length)
अणु
	काष्ठा block_device *part;
	पूर्णांक ret = 0;

	part = bdget_disk(bdev->bd_disk, partno);
	अगर (!part)
		वापस -ENXIO;

	mutex_lock(&part->bd_mutex);
	mutex_lock_nested(&bdev->bd_mutex, 1);
	ret = -EINVAL;
	अगर (start != part->bd_start_sect)
		जाओ out_unlock;

	ret = -EBUSY;
	अगर (partition_overlaps(bdev->bd_disk, start, length, partno))
		जाओ out_unlock;

	bdev_set_nr_sectors(part, length);

	ret = 0;
out_unlock:
	mutex_unlock(&part->bd_mutex);
	mutex_unlock(&bdev->bd_mutex);
	bdput(part);
	वापस ret;
पूर्ण

अटल bool disk_unlock_native_capacity(काष्ठा gendisk *disk)
अणु
	स्थिर काष्ठा block_device_operations *bकरोps = disk->fops;

	अगर (bकरोps->unlock_native_capacity &&
	    !(disk->flags & GENHD_FL_NATIVE_CAPACITY)) अणु
		prपूर्णांकk(KERN_CONT "enabling native capacity\n");
		bकरोps->unlock_native_capacity(disk);
		disk->flags |= GENHD_FL_NATIVE_CAPACITY;
		वापस true;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_CONT "truncated\n");
		वापस false;
	पूर्ण
पूर्ण

व्योम blk_drop_partitions(काष्ठा gendisk *disk)
अणु
	काष्ठा block_device *part;
	अचिन्हित दीर्घ idx;

	lockdep_निश्चित_held(&disk->part0->bd_mutex);

	xa_क्रम_each_start(&disk->part_tbl, idx, part, 1) अणु
		अगर (!bdgrab(part))
			जारी;
		delete_partition(part);
		bdput(part);
	पूर्ण
पूर्ण

अटल bool blk_add_partition(काष्ठा gendisk *disk, काष्ठा block_device *bdev,
		काष्ठा parsed_partitions *state, पूर्णांक p)
अणु
	sector_t size = state->parts[p].size;
	sector_t from = state->parts[p].from;
	काष्ठा block_device *part;

	अगर (!size)
		वापस true;

	अगर (from >= get_capacity(disk)) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: p%d start %llu is beyond EOD, ",
		       disk->disk_name, p, (अचिन्हित दीर्घ दीर्घ) from);
		अगर (disk_unlock_native_capacity(disk))
			वापस false;
		वापस true;
	पूर्ण

	अगर (from + size > get_capacity(disk)) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: p%d size %llu extends beyond EOD, ",
		       disk->disk_name, p, (अचिन्हित दीर्घ दीर्घ) size);

		अगर (disk_unlock_native_capacity(disk))
			वापस false;

		/*
		 * We can not ignore partitions of broken tables created by क्रम
		 * example camera firmware, but we limit them to the end of the
		 * disk to aव्योम creating invalid block devices.
		 */
		size = get_capacity(disk) - from;
	पूर्ण

	part = add_partition(disk, p, from, size, state->parts[p].flags,
			     &state->parts[p].info);
	अगर (IS_ERR(part) && PTR_ERR(part) != -ENXIO) अणु
		prपूर्णांकk(KERN_ERR " %s: p%d could not be added: %ld\n",
		       disk->disk_name, p, -PTR_ERR(part));
		वापस true;
	पूर्ण

	अगर (IS_BUILTIN(CONFIG_BLK_DEV_MD) &&
	    (state->parts[p].flags & ADDPART_FLAG_RAID))
		md_स्वतःdetect_dev(part->bd_dev);

	वापस true;
पूर्ण

पूर्णांक blk_add_partitions(काष्ठा gendisk *disk, काष्ठा block_device *bdev)
अणु
	काष्ठा parsed_partitions *state;
	पूर्णांक ret = -EAGAIN, p;

	अगर (!disk_part_scan_enabled(disk))
		वापस 0;

	state = check_partition(disk, bdev);
	अगर (!state)
		वापस 0;
	अगर (IS_ERR(state)) अणु
		/*
		 * I/O error पढ़ोing the partition table.  If we tried to पढ़ो
		 * beyond EOD, retry after unlocking the native capacity.
		 */
		अगर (PTR_ERR(state) == -ENOSPC) अणु
			prपूर्णांकk(KERN_WARNING "%s: partition table beyond EOD, ",
			       disk->disk_name);
			अगर (disk_unlock_native_capacity(disk))
				वापस -EAGAIN;
		पूर्ण
		वापस -EIO;
	पूर्ण

	/*
	 * Partitions are not supported on host managed zoned block devices.
	 */
	अगर (disk->queue->limits.zoned == BLK_ZONED_HM) अणु
		pr_warn("%s: ignoring partition table on host managed zoned block device\n",
			disk->disk_name);
		ret = 0;
		जाओ out_मुक्त_state;
	पूर्ण

	/*
	 * If we पढ़ो beyond EOD, try unlocking native capacity even अगर the
	 * partition table was successfully पढ़ो as we could be missing some
	 * partitions.
	 */
	अगर (state->access_beyond_eod) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: partition table partially beyond EOD, ",
		       disk->disk_name);
		अगर (disk_unlock_native_capacity(disk))
			जाओ out_मुक्त_state;
	पूर्ण

	/* tell userspace that the media / partition table may have changed */
	kobject_uevent(&disk_to_dev(disk)->kobj, KOBJ_CHANGE);

	क्रम (p = 1; p < state->limit; p++)
		अगर (!blk_add_partition(disk, bdev, state, p))
			जाओ out_मुक्त_state;

	ret = 0;
out_मुक्त_state:
	मुक्त_partitions(state);
	वापस ret;
पूर्ण

व्योम *पढ़ो_part_sector(काष्ठा parsed_partitions *state, sector_t n, Sector *p)
अणु
	काष्ठा address_space *mapping = state->bdev->bd_inode->i_mapping;
	काष्ठा page *page;

	अगर (n >= get_capacity(state->bdev->bd_disk)) अणु
		state->access_beyond_eod = true;
		वापस शून्य;
	पूर्ण

	page = पढ़ो_mapping_page(mapping,
			(pgoff_t)(n >> (PAGE_SHIFT - 9)), शून्य);
	अगर (IS_ERR(page))
		जाओ out;
	अगर (PageError(page))
		जाओ out_put_page;

	p->v = page;
	वापस (अचिन्हित अक्षर *)page_address(page) +
			((n & ((1 << (PAGE_SHIFT - 9)) - 1)) << SECTOR_SHIFT);
out_put_page:
	put_page(page);
out:
	p->v = शून्य;
	वापस शून्य;
पूर्ण
