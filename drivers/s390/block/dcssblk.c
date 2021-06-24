<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dcssblk.c -- the S/390 block driver क्रम dcss memory
 *
 * Authors: Carsten Otte, Stefan Weinhuber, Gerald Schaefer
 */

#घोषणा KMSG_COMPONENT "dcssblk"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/uपन.स>
#समावेश <linux/dax.h>
#समावेश <यंत्र/exपंचांगem.h>
#समावेश <यंत्र/पन.स>

#घोषणा DCSSBLK_NAME "dcssblk"
#घोषणा DCSSBLK_MINORS_PER_DISK 1
#घोषणा DCSSBLK_PARM_LEN 400
#घोषणा DCSS_BUS_ID_SIZE 20

अटल पूर्णांक dcssblk_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode);
अटल व्योम dcssblk_release(काष्ठा gendisk *disk, भ_शेषe_t mode);
अटल blk_qc_t dcssblk_submit_bio(काष्ठा bio *bio);
अटल दीर्घ dcssblk_dax_direct_access(काष्ठा dax_device *dax_dev, pgoff_t pgoff,
		दीर्घ nr_pages, व्योम **kaddr, pfn_t *pfn);

अटल अक्षर dcssblk_segments[DCSSBLK_PARM_LEN] = "\0";

अटल पूर्णांक dcssblk_major;
अटल स्थिर काष्ठा block_device_operations dcssblk_devops = अणु
	.owner   	= THIS_MODULE,
	.submit_bio	= dcssblk_submit_bio,
	.खोलो    	= dcssblk_खोलो,
	.release 	= dcssblk_release,
पूर्ण;

अटल माप_प्रकार dcssblk_dax_copy_from_iter(काष्ठा dax_device *dax_dev,
		pgoff_t pgoff, व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	वापस copy_from_iter(addr, bytes, i);
पूर्ण

अटल माप_प्रकार dcssblk_dax_copy_to_iter(काष्ठा dax_device *dax_dev,
		pgoff_t pgoff, व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	वापस copy_to_iter(addr, bytes, i);
पूर्ण

अटल पूर्णांक dcssblk_dax_zero_page_range(काष्ठा dax_device *dax_dev,
				       pgoff_t pgoff, माप_प्रकार nr_pages)
अणु
	दीर्घ rc;
	व्योम *kaddr;

	rc = dax_direct_access(dax_dev, pgoff, nr_pages, &kaddr, शून्य);
	अगर (rc < 0)
		वापस rc;
	स_रखो(kaddr, 0, nr_pages << PAGE_SHIFT);
	dax_flush(dax_dev, kaddr, nr_pages << PAGE_SHIFT);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dax_operations dcssblk_dax_ops = अणु
	.direct_access = dcssblk_dax_direct_access,
	.dax_supported = generic_fsdax_supported,
	.copy_from_iter = dcssblk_dax_copy_from_iter,
	.copy_to_iter = dcssblk_dax_copy_to_iter,
	.zero_page_range = dcssblk_dax_zero_page_range,
पूर्ण;

काष्ठा dcssblk_dev_info अणु
	काष्ठा list_head lh;
	काष्ठा device dev;
	अक्षर segment_name[DCSS_BUS_ID_SIZE];
	atomic_t use_count;
	काष्ठा gendisk *gd;
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
	पूर्णांक segment_type;
	अचिन्हित अक्षर save_pending;
	अचिन्हित अक्षर is_shared;
	काष्ठा request_queue *dcssblk_queue;
	पूर्णांक num_of_segments;
	काष्ठा list_head seg_list;
	काष्ठा dax_device *dax_dev;
पूर्ण;

काष्ठा segment_info अणु
	काष्ठा list_head lh;
	अक्षर segment_name[DCSS_BUS_ID_SIZE];
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
	पूर्णांक segment_type;
पूर्ण;

अटल sमाप_प्रकार dcssblk_add_store(काष्ठा device * dev, काष्ठा device_attribute *attr, स्थिर अक्षर * buf,
				  माप_प्रकार count);
अटल sमाप_प्रकार dcssblk_हटाओ_store(काष्ठा device * dev, काष्ठा device_attribute *attr, स्थिर अक्षर * buf,
				  माप_प्रकार count);

अटल DEVICE_ATTR(add, S_IWUSR, शून्य, dcssblk_add_store);
अटल DEVICE_ATTR(हटाओ, S_IWUSR, शून्य, dcssblk_हटाओ_store);

अटल काष्ठा device *dcssblk_root_dev;

अटल LIST_HEAD(dcssblk_devices);
अटल काष्ठा rw_semaphore dcssblk_devices_sem;

/*
 * release function क्रम segment device.
 */
अटल व्योम
dcssblk_release_segment(काष्ठा device *dev)
अणु
	काष्ठा dcssblk_dev_info *dev_info;
	काष्ठा segment_info *entry, *temp;

	dev_info = container_of(dev, काष्ठा dcssblk_dev_info, dev);
	list_क्रम_each_entry_safe(entry, temp, &dev_info->seg_list, lh) अणु
		list_del(&entry->lh);
		kमुक्त(entry);
	पूर्ण
	kमुक्त(dev_info);
	module_put(THIS_MODULE);
पूर्ण

/*
 * get a minor number. needs to be called with
 * करोwn_ग_लिखो(&dcssblk_devices_sem) and the
 * device needs to be enqueued beक्रमe the semaphore is
 * मुक्तd.
 */
अटल पूर्णांक
dcssblk_assign_मुक्त_minor(काष्ठा dcssblk_dev_info *dev_info)
अणु
	पूर्णांक minor, found;
	काष्ठा dcssblk_dev_info *entry;

	अगर (dev_info == शून्य)
		वापस -EINVAL;
	क्रम (minor = 0; minor < (1<<MINORBITS); minor++) अणु
		found = 0;
		// test अगर minor available
		list_क्रम_each_entry(entry, &dcssblk_devices, lh)
			अगर (minor == entry->gd->first_minor)
				found++;
		अगर (!found) अवरोध; // got unused minor
	पूर्ण
	अगर (found)
		वापस -EBUSY;
	dev_info->gd->first_minor = minor;
	वापस 0;
पूर्ण

/*
 * get the काष्ठा dcssblk_dev_info from dcssblk_devices
 * क्रम the given name.
 * करोwn_पढ़ो(&dcssblk_devices_sem) must be held.
 */
अटल काष्ठा dcssblk_dev_info *
dcssblk_get_device_by_name(अक्षर *name)
अणु
	काष्ठा dcssblk_dev_info *entry;

	list_क्रम_each_entry(entry, &dcssblk_devices, lh) अणु
		अगर (!म_भेद(name, entry->segment_name)) अणु
			वापस entry;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * get the काष्ठा segment_info from seg_list
 * क्रम the given name.
 * करोwn_पढ़ो(&dcssblk_devices_sem) must be held.
 */
अटल काष्ठा segment_info *
dcssblk_get_segment_by_name(अक्षर *name)
अणु
	काष्ठा dcssblk_dev_info *dev_info;
	काष्ठा segment_info *entry;

	list_क्रम_each_entry(dev_info, &dcssblk_devices, lh) अणु
		list_क्रम_each_entry(entry, &dev_info->seg_list, lh) अणु
			अगर (!म_भेद(name, entry->segment_name))
				वापस entry;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * get the highest address of the multi-segment block.
 */
अटल अचिन्हित दीर्घ
dcssblk_find_highest_addr(काष्ठा dcssblk_dev_info *dev_info)
अणु
	अचिन्हित दीर्घ highest_addr;
	काष्ठा segment_info *entry;

	highest_addr = 0;
	list_क्रम_each_entry(entry, &dev_info->seg_list, lh) अणु
		अगर (highest_addr < entry->end)
			highest_addr = entry->end;
	पूर्ण
	वापस highest_addr;
पूर्ण

/*
 * get the lowest address of the multi-segment block.
 */
अटल अचिन्हित दीर्घ
dcssblk_find_lowest_addr(काष्ठा dcssblk_dev_info *dev_info)
अणु
	पूर्णांक set_first;
	अचिन्हित दीर्घ lowest_addr;
	काष्ठा segment_info *entry;

	set_first = 0;
	lowest_addr = 0;
	list_क्रम_each_entry(entry, &dev_info->seg_list, lh) अणु
		अगर (set_first == 0) अणु
			lowest_addr = entry->start;
			set_first = 1;
		पूर्ण अन्यथा अणु
			अगर (lowest_addr > entry->start)
				lowest_addr = entry->start;
		पूर्ण
	पूर्ण
	वापस lowest_addr;
पूर्ण

/*
 * Check continuity of segments.
 */
अटल पूर्णांक
dcssblk_is_continuous(काष्ठा dcssblk_dev_info *dev_info)
अणु
	पूर्णांक i, j, rc;
	काष्ठा segment_info *sort_list, *entry, temp;

	अगर (dev_info->num_of_segments <= 1)
		वापस 0;

	sort_list = kसुस्मृति(dev_info->num_of_segments,
			    माप(काष्ठा segment_info),
			    GFP_KERNEL);
	अगर (sort_list == शून्य)
		वापस -ENOMEM;
	i = 0;
	list_क्रम_each_entry(entry, &dev_info->seg_list, lh) अणु
		स_नकल(&sort_list[i], entry, माप(काष्ठा segment_info));
		i++;
	पूर्ण

	/* sort segments */
	क्रम (i = 0; i < dev_info->num_of_segments; i++)
		क्रम (j = 0; j < dev_info->num_of_segments; j++)
			अगर (sort_list[j].start > sort_list[i].start) अणु
				स_नकल(&temp, &sort_list[i],
					माप(काष्ठा segment_info));
				स_नकल(&sort_list[i], &sort_list[j],
					माप(काष्ठा segment_info));
				स_नकल(&sort_list[j], &temp,
					माप(काष्ठा segment_info));
			पूर्ण

	/* check continuity */
	क्रम (i = 0; i < dev_info->num_of_segments - 1; i++) अणु
		अगर ((sort_list[i].end + 1) != sort_list[i+1].start) अणु
			pr_err("Adjacent DCSSs %s and %s are not "
			       "contiguous\n", sort_list[i].segment_name,
			       sort_list[i+1].segment_name);
			rc = -EINVAL;
			जाओ out;
		पूर्ण
		/* EN and EW are allowed in a block device */
		अगर (sort_list[i].segment_type != sort_list[i+1].segment_type) अणु
			अगर (!(sort_list[i].segment_type & SEGMENT_EXCLUSIVE) ||
				(sort_list[i].segment_type == SEG_TYPE_ER) ||
				!(sort_list[i+1].segment_type &
				SEGMENT_EXCLUSIVE) ||
				(sort_list[i+1].segment_type == SEG_TYPE_ER)) अणु
				pr_err("DCSS %s and DCSS %s have "
				       "incompatible types\n",
				       sort_list[i].segment_name,
				       sort_list[i+1].segment_name);
				rc = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	rc = 0;
out:
	kमुक्त(sort_list);
	वापस rc;
पूर्ण

/*
 * Load a segment
 */
अटल पूर्णांक
dcssblk_load_segment(अक्षर *name, काष्ठा segment_info **seg_info)
अणु
	पूर्णांक rc;

	/* alपढ़ोy loaded? */
	करोwn_पढ़ो(&dcssblk_devices_sem);
	*seg_info = dcssblk_get_segment_by_name(name);
	up_पढ़ो(&dcssblk_devices_sem);
	अगर (*seg_info != शून्य)
		वापस -EEXIST;

	/* get a काष्ठा segment_info */
	*seg_info = kzalloc(माप(काष्ठा segment_info), GFP_KERNEL);
	अगर (*seg_info == शून्य)
		वापस -ENOMEM;

	म_नकल((*seg_info)->segment_name, name);

	/* load the segment */
	rc = segment_load(name, SEGMENT_SHARED,
			&(*seg_info)->start, &(*seg_info)->end);
	अगर (rc < 0) अणु
		segment_warning(rc, (*seg_info)->segment_name);
		kमुक्त(*seg_info);
	पूर्ण अन्यथा अणु
		INIT_LIST_HEAD(&(*seg_info)->lh);
		(*seg_info)->segment_type = rc;
	पूर्ण
	वापस rc;
पूर्ण

/*
 * device attribute क्रम चयनing shared/nonshared (exclusive)
 * operation (show + store)
 */
अटल sमाप_प्रकार
dcssblk_shared_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dcssblk_dev_info *dev_info;

	dev_info = container_of(dev, काष्ठा dcssblk_dev_info, dev);
	वापस प्र_लिखो(buf, dev_info->is_shared ? "1\n" : "0\n");
पूर्ण

अटल sमाप_प्रकार
dcssblk_shared_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *inbuf, माप_प्रकार count)
अणु
	काष्ठा dcssblk_dev_info *dev_info;
	काष्ठा segment_info *entry, *temp;
	पूर्णांक rc;

	अगर ((count > 1) && (inbuf[1] != '\n') && (inbuf[1] != '\0'))
		वापस -EINVAL;
	करोwn_ग_लिखो(&dcssblk_devices_sem);
	dev_info = container_of(dev, काष्ठा dcssblk_dev_info, dev);
	अगर (atomic_पढ़ो(&dev_info->use_count)) अणु
		rc = -EBUSY;
		जाओ out;
	पूर्ण
	अगर (inbuf[0] == '1') अणु
		/* reload segments in shared mode */
		list_क्रम_each_entry(entry, &dev_info->seg_list, lh) अणु
			rc = segment_modअगरy_shared(entry->segment_name,
						SEGMENT_SHARED);
			अगर (rc < 0) अणु
				BUG_ON(rc == -EINVAL);
				अगर (rc != -EAGAIN)
					जाओ हटाओseg;
			पूर्ण
		पूर्ण
		dev_info->is_shared = 1;
		चयन (dev_info->segment_type) अणु
		हाल SEG_TYPE_SR:
		हाल SEG_TYPE_ER:
		हाल SEG_TYPE_SC:
			set_disk_ro(dev_info->gd, 1);
		पूर्ण
	पूर्ण अन्यथा अगर (inbuf[0] == '0') अणु
		/* reload segments in exclusive mode */
		अगर (dev_info->segment_type == SEG_TYPE_SC) अणु
			pr_err("DCSS %s is of type SC and cannot be "
			       "loaded as exclusive-writable\n",
			       dev_info->segment_name);
			rc = -EINVAL;
			जाओ out;
		पूर्ण
		list_क्रम_each_entry(entry, &dev_info->seg_list, lh) अणु
			rc = segment_modअगरy_shared(entry->segment_name,
						   SEGMENT_EXCLUSIVE);
			अगर (rc < 0) अणु
				BUG_ON(rc == -EINVAL);
				अगर (rc != -EAGAIN)
					जाओ हटाओseg;
			पूर्ण
		पूर्ण
		dev_info->is_shared = 0;
		set_disk_ro(dev_info->gd, 0);
	पूर्ण अन्यथा अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	rc = count;
	जाओ out;

हटाओseg:
	pr_err("DCSS device %s is removed after a failed access mode "
	       "change\n", dev_info->segment_name);
	temp = entry;
	list_क्रम_each_entry(entry, &dev_info->seg_list, lh) अणु
		अगर (entry != temp)
			segment_unload(entry->segment_name);
	पूर्ण
	list_del(&dev_info->lh);

	समाप्त_dax(dev_info->dax_dev);
	put_dax(dev_info->dax_dev);
	del_gendisk(dev_info->gd);
	blk_cleanup_queue(dev_info->dcssblk_queue);
	dev_info->gd->queue = शून्य;
	put_disk(dev_info->gd);
	up_ग_लिखो(&dcssblk_devices_sem);

	अगर (device_हटाओ_file_self(dev, attr)) अणु
		device_unरेजिस्टर(dev);
		put_device(dev);
	पूर्ण
	वापस rc;
out:
	up_ग_लिखो(&dcssblk_devices_sem);
	वापस rc;
पूर्ण
अटल DEVICE_ATTR(shared, S_IWUSR | S_IRUSR, dcssblk_shared_show,
		   dcssblk_shared_store);

/*
 * device attribute क्रम save operation on current copy
 * of the segment. If the segment is busy, saving will
 * become pending until it माला_लो released, which can be
 * unकरोne by storing a non-true value to this entry.
 * (show + store)
 */
अटल sमाप_प्रकार
dcssblk_save_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dcssblk_dev_info *dev_info;

	dev_info = container_of(dev, काष्ठा dcssblk_dev_info, dev);
	वापस प्र_लिखो(buf, dev_info->save_pending ? "1\n" : "0\n");
पूर्ण

अटल sमाप_प्रकार
dcssblk_save_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *inbuf, माप_प्रकार count)
अणु
	काष्ठा dcssblk_dev_info *dev_info;
	काष्ठा segment_info *entry;

	अगर ((count > 1) && (inbuf[1] != '\n') && (inbuf[1] != '\0'))
		वापस -EINVAL;
	dev_info = container_of(dev, काष्ठा dcssblk_dev_info, dev);

	करोwn_ग_लिखो(&dcssblk_devices_sem);
	अगर (inbuf[0] == '1') अणु
		अगर (atomic_पढ़ो(&dev_info->use_count) == 0) अणु
			// device is idle => we save immediately
			pr_info("All DCSSs that map to device %s are "
				"saved\n", dev_info->segment_name);
			list_क्रम_each_entry(entry, &dev_info->seg_list, lh) अणु
				अगर (entry->segment_type == SEG_TYPE_EN ||
				    entry->segment_type == SEG_TYPE_SN)
					pr_warn("DCSS %s is of type SN or EN"
						" and cannot be saved\n",
						entry->segment_name);
				अन्यथा
					segment_save(entry->segment_name);
			पूर्ण
		पूर्ण  अन्यथा अणु
			// device is busy => we save it when it becomes
			// idle in dcssblk_release
			pr_info("Device %s is in use, its DCSSs will be "
				"saved when it becomes idle\n",
				dev_info->segment_name);
			dev_info->save_pending = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (inbuf[0] == '0') अणु
		अगर (dev_info->save_pending) अणु
			// device is busy & the user wants to unकरो his save
			// request
			dev_info->save_pending = 0;
			pr_info("A pending save request for device %s "
				"has been canceled\n",
				dev_info->segment_name);
		पूर्ण
	पूर्ण अन्यथा अणु
		up_ग_लिखो(&dcssblk_devices_sem);
		वापस -EINVAL;
	पूर्ण
	up_ग_लिखो(&dcssblk_devices_sem);
	वापस count;
पूर्ण
अटल DEVICE_ATTR(save, S_IWUSR | S_IRUSR, dcssblk_save_show,
		   dcssblk_save_store);

/*
 * device attribute क्रम showing all segments in a device
 */
अटल sमाप_प्रकार
dcssblk_seglist_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	पूर्णांक i;

	काष्ठा dcssblk_dev_info *dev_info;
	काष्ठा segment_info *entry;

	करोwn_पढ़ो(&dcssblk_devices_sem);
	dev_info = container_of(dev, काष्ठा dcssblk_dev_info, dev);
	i = 0;
	buf[0] = '\0';
	list_क्रम_each_entry(entry, &dev_info->seg_list, lh) अणु
		म_नकल(&buf[i], entry->segment_name);
		i += म_माप(entry->segment_name);
		buf[i] = '\n';
		i++;
	पूर्ण
	up_पढ़ो(&dcssblk_devices_sem);
	वापस i;
पूर्ण
अटल DEVICE_ATTR(seglist, S_IRUSR, dcssblk_seglist_show, शून्य);

अटल काष्ठा attribute *dcssblk_dev_attrs[] = अणु
	&dev_attr_shared.attr,
	&dev_attr_save.attr,
	&dev_attr_seglist.attr,
	शून्य,
पूर्ण;
अटल काष्ठा attribute_group dcssblk_dev_attr_group = अणु
	.attrs = dcssblk_dev_attrs,
पूर्ण;
अटल स्थिर काष्ठा attribute_group *dcssblk_dev_attr_groups[] = अणु
	&dcssblk_dev_attr_group,
	शून्य,
पूर्ण;

/*
 * device attribute क्रम adding devices
 */
अटल sमाप_प्रकार
dcssblk_add_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc, i, j, num_of_segments;
	काष्ठा dcssblk_dev_info *dev_info;
	काष्ठा segment_info *seg_info, *temp;
	अक्षर *local_buf;
	अचिन्हित दीर्घ seg_byte_size;

	dev_info = शून्य;
	seg_info = शून्य;
	अगर (dev != dcssblk_root_dev) अणु
		rc = -EINVAL;
		जाओ out_nobuf;
	पूर्ण
	अगर ((count < 1) || (buf[0] == '\0') || (buf[0] == '\n')) अणु
		rc = -ENAMETOOLONG;
		जाओ out_nobuf;
	पूर्ण

	local_buf = kदो_स्मृति(count + 1, GFP_KERNEL);
	अगर (local_buf == शून्य) अणु
		rc = -ENOMEM;
		जाओ out_nobuf;
	पूर्ण

	/*
	 * parse input
	 */
	num_of_segments = 0;
	क्रम (i = 0; (i < count && (buf[i] != '\0') && (buf[i] != '\n')); i++) अणु
		क्रम (j = i; j < count &&
			(buf[j] != ':') &&
			(buf[j] != '\0') &&
			(buf[j] != '\n'); j++) अणु
			local_buf[j-i] = बड़े(buf[j]);
		पूर्ण
		local_buf[j-i] = '\0';
		अगर (((j - i) == 0) || ((j - i) > 8)) अणु
			rc = -ENAMETOOLONG;
			जाओ seg_list_del;
		पूर्ण

		rc = dcssblk_load_segment(local_buf, &seg_info);
		अगर (rc < 0)
			जाओ seg_list_del;
		/*
		 * get a काष्ठा dcssblk_dev_info
		 */
		अगर (num_of_segments == 0) अणु
			dev_info = kzalloc(माप(काष्ठा dcssblk_dev_info),
					GFP_KERNEL);
			अगर (dev_info == शून्य) अणु
				rc = -ENOMEM;
				जाओ out;
			पूर्ण
			म_नकल(dev_info->segment_name, local_buf);
			dev_info->segment_type = seg_info->segment_type;
			INIT_LIST_HEAD(&dev_info->seg_list);
		पूर्ण
		list_add_tail(&seg_info->lh, &dev_info->seg_list);
		num_of_segments++;
		i = j;

		अगर ((buf[j] == '\0') || (buf[j] == '\n'))
			अवरोध;
	पूर्ण

	/* no trailing colon at the end of the input */
	अगर ((i > 0) && (buf[i-1] == ':')) अणु
		rc = -ENAMETOOLONG;
		जाओ seg_list_del;
	पूर्ण
	strlcpy(local_buf, buf, i + 1);
	dev_info->num_of_segments = num_of_segments;
	rc = dcssblk_is_continuous(dev_info);
	अगर (rc < 0)
		जाओ seg_list_del;

	dev_info->start = dcssblk_find_lowest_addr(dev_info);
	dev_info->end = dcssblk_find_highest_addr(dev_info);

	dev_set_name(&dev_info->dev, "%s", dev_info->segment_name);
	dev_info->dev.release = dcssblk_release_segment;
	dev_info->dev.groups = dcssblk_dev_attr_groups;
	INIT_LIST_HEAD(&dev_info->lh);
	dev_info->gd = alloc_disk(DCSSBLK_MINORS_PER_DISK);
	अगर (dev_info->gd == शून्य) अणु
		rc = -ENOMEM;
		जाओ seg_list_del;
	पूर्ण
	dev_info->gd->major = dcssblk_major;
	dev_info->gd->fops = &dcssblk_devops;
	dev_info->dcssblk_queue = blk_alloc_queue(NUMA_NO_NODE);
	dev_info->gd->queue = dev_info->dcssblk_queue;
	dev_info->gd->निजी_data = dev_info;
	blk_queue_logical_block_size(dev_info->dcssblk_queue, 4096);
	blk_queue_flag_set(QUEUE_FLAG_DAX, dev_info->dcssblk_queue);

	seg_byte_size = (dev_info->end - dev_info->start + 1);
	set_capacity(dev_info->gd, seg_byte_size >> 9); // size in sectors
	pr_info("Loaded %s with total size %lu bytes and capacity %lu "
		"sectors\n", local_buf, seg_byte_size, seg_byte_size >> 9);

	dev_info->save_pending = 0;
	dev_info->is_shared = 1;
	dev_info->dev.parent = dcssblk_root_dev;

	/*
	 *get minor, add to list
	 */
	करोwn_ग_लिखो(&dcssblk_devices_sem);
	अगर (dcssblk_get_segment_by_name(local_buf)) अणु
		rc = -EEXIST;
		जाओ release_gd;
	पूर्ण
	rc = dcssblk_assign_मुक्त_minor(dev_info);
	अगर (rc)
		जाओ release_gd;
	प्र_लिखो(dev_info->gd->disk_name, "dcssblk%d",
		dev_info->gd->first_minor);
	list_add_tail(&dev_info->lh, &dcssblk_devices);

	अगर (!try_module_get(THIS_MODULE)) अणु
		rc = -ENODEV;
		जाओ dev_list_del;
	पूर्ण
	/*
	 * रेजिस्टर the device
	 */
	rc = device_रेजिस्टर(&dev_info->dev);
	अगर (rc)
		जाओ put_dev;

	dev_info->dax_dev = alloc_dax(dev_info, dev_info->gd->disk_name,
			&dcssblk_dax_ops, DAXDEV_F_SYNC);
	अगर (IS_ERR(dev_info->dax_dev)) अणु
		rc = PTR_ERR(dev_info->dax_dev);
		dev_info->dax_dev = शून्य;
		जाओ put_dev;
	पूर्ण

	get_device(&dev_info->dev);
	device_add_disk(&dev_info->dev, dev_info->gd, शून्य);

	चयन (dev_info->segment_type) अणु
		हाल SEG_TYPE_SR:
		हाल SEG_TYPE_ER:
		हाल SEG_TYPE_SC:
			set_disk_ro(dev_info->gd,1);
			अवरोध;
		शेष:
			set_disk_ro(dev_info->gd,0);
			अवरोध;
	पूर्ण
	up_ग_लिखो(&dcssblk_devices_sem);
	rc = count;
	जाओ out;

put_dev:
	list_del(&dev_info->lh);
	blk_cleanup_queue(dev_info->dcssblk_queue);
	dev_info->gd->queue = शून्य;
	put_disk(dev_info->gd);
	list_क्रम_each_entry(seg_info, &dev_info->seg_list, lh) अणु
		segment_unload(seg_info->segment_name);
	पूर्ण
	put_device(&dev_info->dev);
	up_ग_लिखो(&dcssblk_devices_sem);
	जाओ out;
dev_list_del:
	list_del(&dev_info->lh);
release_gd:
	blk_cleanup_queue(dev_info->dcssblk_queue);
	dev_info->gd->queue = शून्य;
	put_disk(dev_info->gd);
	up_ग_लिखो(&dcssblk_devices_sem);
seg_list_del:
	अगर (dev_info == शून्य)
		जाओ out;
	list_क्रम_each_entry_safe(seg_info, temp, &dev_info->seg_list, lh) अणु
		list_del(&seg_info->lh);
		segment_unload(seg_info->segment_name);
		kमुक्त(seg_info);
	पूर्ण
	kमुक्त(dev_info);
out:
	kमुक्त(local_buf);
out_nobuf:
	वापस rc;
पूर्ण

/*
 * device attribute क्रम removing devices
 */
अटल sमाप_प्रकार
dcssblk_हटाओ_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dcssblk_dev_info *dev_info;
	काष्ठा segment_info *entry;
	पूर्णांक rc, i;
	अक्षर *local_buf;

	अगर (dev != dcssblk_root_dev) अणु
		वापस -EINVAL;
	पूर्ण
	local_buf = kदो_स्मृति(count + 1, GFP_KERNEL);
	अगर (local_buf == शून्य) अणु
		वापस -ENOMEM;
	पूर्ण
	/*
	 * parse input
	 */
	क्रम (i = 0; (i < count && (*(buf+i)!='\0') && (*(buf+i)!='\n')); i++) अणु
		local_buf[i] = बड़े(buf[i]);
	पूर्ण
	local_buf[i] = '\0';
	अगर ((i == 0) || (i > 8)) अणु
		rc = -ENAMETOOLONG;
		जाओ out_buf;
	पूर्ण

	करोwn_ग_लिखो(&dcssblk_devices_sem);
	dev_info = dcssblk_get_device_by_name(local_buf);
	अगर (dev_info == शून्य) अणु
		up_ग_लिखो(&dcssblk_devices_sem);
		pr_warn("Device %s cannot be removed because it is not a known device\n",
			local_buf);
		rc = -ENODEV;
		जाओ out_buf;
	पूर्ण
	अगर (atomic_पढ़ो(&dev_info->use_count) != 0) अणु
		up_ग_लिखो(&dcssblk_devices_sem);
		pr_warn("Device %s cannot be removed while it is in use\n",
			local_buf);
		rc = -EBUSY;
		जाओ out_buf;
	पूर्ण

	list_del(&dev_info->lh);
	समाप्त_dax(dev_info->dax_dev);
	put_dax(dev_info->dax_dev);
	del_gendisk(dev_info->gd);
	blk_cleanup_queue(dev_info->dcssblk_queue);
	dev_info->gd->queue = शून्य;
	put_disk(dev_info->gd);

	/* unload all related segments */
	list_क्रम_each_entry(entry, &dev_info->seg_list, lh)
		segment_unload(entry->segment_name);

	up_ग_लिखो(&dcssblk_devices_sem);

	device_unरेजिस्टर(&dev_info->dev);
	put_device(&dev_info->dev);

	rc = count;
out_buf:
	kमुक्त(local_buf);
	वापस rc;
पूर्ण

अटल पूर्णांक
dcssblk_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा dcssblk_dev_info *dev_info;
	पूर्णांक rc;

	dev_info = bdev->bd_disk->निजी_data;
	अगर (शून्य == dev_info) अणु
		rc = -ENODEV;
		जाओ out;
	पूर्ण
	atomic_inc(&dev_info->use_count);
	rc = 0;
out:
	वापस rc;
पूर्ण

अटल व्योम
dcssblk_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा dcssblk_dev_info *dev_info = disk->निजी_data;
	काष्ठा segment_info *entry;

	अगर (!dev_info) अणु
		WARN_ON(1);
		वापस;
	पूर्ण
	करोwn_ग_लिखो(&dcssblk_devices_sem);
	अगर (atomic_dec_and_test(&dev_info->use_count)
	    && (dev_info->save_pending)) अणु
		pr_info("Device %s has become idle and is being saved "
			"now\n", dev_info->segment_name);
		list_क्रम_each_entry(entry, &dev_info->seg_list, lh) अणु
			अगर (entry->segment_type == SEG_TYPE_EN ||
			    entry->segment_type == SEG_TYPE_SN)
				pr_warn("DCSS %s is of type SN or EN and cannot"
					" be saved\n", entry->segment_name);
			अन्यथा
				segment_save(entry->segment_name);
		पूर्ण
		dev_info->save_pending = 0;
	पूर्ण
	up_ग_लिखो(&dcssblk_devices_sem);
पूर्ण

अटल blk_qc_t
dcssblk_submit_bio(काष्ठा bio *bio)
अणु
	काष्ठा dcssblk_dev_info *dev_info;
	काष्ठा bio_vec bvec;
	काष्ठा bvec_iter iter;
	अचिन्हित दीर्घ index;
	अचिन्हित दीर्घ page_addr;
	अचिन्हित दीर्घ source_addr;
	अचिन्हित दीर्घ bytes_करोne;

	blk_queue_split(&bio);

	bytes_करोne = 0;
	dev_info = bio->bi_bdev->bd_disk->निजी_data;
	अगर (dev_info == शून्य)
		जाओ fail;
	अगर ((bio->bi_iter.bi_sector & 7) != 0 ||
	    (bio->bi_iter.bi_size & 4095) != 0)
		/* Request is not page-aligned. */
		जाओ fail;
	/* verअगरy data transfer direction */
	अगर (dev_info->is_shared) अणु
		चयन (dev_info->segment_type) अणु
		हाल SEG_TYPE_SR:
		हाल SEG_TYPE_ER:
		हाल SEG_TYPE_SC:
			/* cannot ग_लिखो to these segments */
			अगर (bio_data_dir(bio) == WRITE) अणु
				pr_warn("Writing to %s failed because it is a read-only device\n",
					dev_name(&dev_info->dev));
				जाओ fail;
			पूर्ण
		पूर्ण
	पूर्ण

	index = (bio->bi_iter.bi_sector >> 3);
	bio_क्रम_each_segment(bvec, bio, iter) अणु
		page_addr = (अचिन्हित दीर्घ)
			page_address(bvec.bv_page) + bvec.bv_offset;
		source_addr = dev_info->start + (index<<12) + bytes_करोne;
		अगर (unlikely((page_addr & 4095) != 0) || (bvec.bv_len & 4095) != 0)
			// More paranoia.
			जाओ fail;
		अगर (bio_data_dir(bio) == READ) अणु
			स_नकल((व्योम*)page_addr, (व्योम*)source_addr,
				bvec.bv_len);
		पूर्ण अन्यथा अणु
			स_नकल((व्योम*)source_addr, (व्योम*)page_addr,
				bvec.bv_len);
		पूर्ण
		bytes_करोne += bvec.bv_len;
	पूर्ण
	bio_endio(bio);
	वापस BLK_QC_T_NONE;
fail:
	bio_io_error(bio);
	वापस BLK_QC_T_NONE;
पूर्ण

अटल दीर्घ
__dcssblk_direct_access(काष्ठा dcssblk_dev_info *dev_info, pgoff_t pgoff,
		दीर्घ nr_pages, व्योम **kaddr, pfn_t *pfn)
अणु
	resource_माप_प्रकार offset = pgoff * PAGE_SIZE;
	अचिन्हित दीर्घ dev_sz;

	dev_sz = dev_info->end - dev_info->start + 1;
	अगर (kaddr)
		*kaddr = (व्योम *) dev_info->start + offset;
	अगर (pfn)
		*pfn = __pfn_to_pfn_t(PFN_DOWN(dev_info->start + offset),
				PFN_DEV|PFN_SPECIAL);

	वापस (dev_sz - offset) / PAGE_SIZE;
पूर्ण

अटल दीर्घ
dcssblk_dax_direct_access(काष्ठा dax_device *dax_dev, pgoff_t pgoff,
		दीर्घ nr_pages, व्योम **kaddr, pfn_t *pfn)
अणु
	काष्ठा dcssblk_dev_info *dev_info = dax_get_निजी(dax_dev);

	वापस __dcssblk_direct_access(dev_info, pgoff, nr_pages, kaddr, pfn);
पूर्ण

अटल व्योम
dcssblk_check_params(व्योम)
अणु
	पूर्णांक rc, i, j, k;
	अक्षर buf[DCSSBLK_PARM_LEN + 1];
	काष्ठा dcssblk_dev_info *dev_info;

	क्रम (i = 0; (i < DCSSBLK_PARM_LEN) && (dcssblk_segments[i] != '\0');
	     i++) अणु
		क्रम (j = i; (j < DCSSBLK_PARM_LEN) &&
			    (dcssblk_segments[j] != ',')  &&
			    (dcssblk_segments[j] != '\0') &&
			    (dcssblk_segments[j] != '('); j++)
		अणु
			buf[j-i] = dcssblk_segments[j];
		पूर्ण
		buf[j-i] = '\0';
		rc = dcssblk_add_store(dcssblk_root_dev, शून्य, buf, j-i);
		अगर ((rc >= 0) && (dcssblk_segments[j] == '(')) अणु
			क्रम (k = 0; (buf[k] != ':') && (buf[k] != '\0'); k++)
				buf[k] = बड़े(buf[k]);
			buf[k] = '\0';
			अगर (!म_भेदन(&dcssblk_segments[j], "(local)", 7)) अणु
				करोwn_पढ़ो(&dcssblk_devices_sem);
				dev_info = dcssblk_get_device_by_name(buf);
				up_पढ़ो(&dcssblk_devices_sem);
				अगर (dev_info)
					dcssblk_shared_store(&dev_info->dev,
							     शून्य, "0\n", 2);
			पूर्ण
		पूर्ण
		जबतक ((dcssblk_segments[j] != ',') &&
		       (dcssblk_segments[j] != '\0'))
		अणु
			j++;
		पूर्ण
		अगर (dcssblk_segments[j] == '\0')
			अवरोध;
		i = j;
	पूर्ण
पूर्ण

/*
 * Suspend / Resume
 */
अटल पूर्णांक dcssblk_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा dcssblk_dev_info *dev_info;
	पूर्णांक rc = 0;

	list_क्रम_each_entry(dev_info, &dcssblk_devices, lh) अणु
		चयन (dev_info->segment_type) अणु
			हाल SEG_TYPE_SR:
			हाल SEG_TYPE_ER:
			हाल SEG_TYPE_SC:
				अगर (!dev_info->is_shared)
					rc = -EINVAL;
				अवरोध;
			शेष:
				rc = -EINVAL;
				अवरोध;
		पूर्ण
		अगर (rc)
			अवरोध;
	पूर्ण
	अगर (rc)
		pr_err("Suspending the system failed because DCSS device %s "
		       "is writable\n",
		       dev_info->segment_name);
	वापस rc;
पूर्ण

अटल पूर्णांक dcssblk_restore(काष्ठा device *dev)
अणु
	काष्ठा dcssblk_dev_info *dev_info;
	काष्ठा segment_info *entry;
	अचिन्हित दीर्घ start, end;
	पूर्णांक rc = 0;

	list_क्रम_each_entry(dev_info, &dcssblk_devices, lh) अणु
		list_क्रम_each_entry(entry, &dev_info->seg_list, lh) अणु
			segment_unload(entry->segment_name);
			rc = segment_load(entry->segment_name, SEGMENT_SHARED,
					  &start, &end);
			अगर (rc < 0) अणु
// TODO in_use check ?
				segment_warning(rc, entry->segment_name);
				जाओ out_panic;
			पूर्ण
			अगर (start != entry->start || end != entry->end) अणु
				pr_err("The address range of DCSS %s changed "
				       "while the system was suspended\n",
				       entry->segment_name);
				जाओ out_panic;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
out_panic:
	panic("fatal dcssblk resume error\n");
पूर्ण

अटल पूर्णांक dcssblk_thaw(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dcssblk_pm_ops = अणु
	.मुक्तze		= dcssblk_मुक्तze,
	.thaw		= dcssblk_thaw,
	.restore	= dcssblk_restore,
पूर्ण;

अटल काष्ठा platक्रमm_driver dcssblk_pdrv = अणु
	.driver = अणु
		.name	= "dcssblk",
		.pm	= &dcssblk_pm_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *dcssblk_pdev;


/*
 * The init/निकास functions.
 */
अटल व्योम __निकास
dcssblk_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(dcssblk_pdev);
	platक्रमm_driver_unरेजिस्टर(&dcssblk_pdrv);
	root_device_unरेजिस्टर(dcssblk_root_dev);
	unरेजिस्टर_blkdev(dcssblk_major, DCSSBLK_NAME);
पूर्ण

अटल पूर्णांक __init
dcssblk_init(व्योम)
अणु
	पूर्णांक rc;

	rc = platक्रमm_driver_रेजिस्टर(&dcssblk_pdrv);
	अगर (rc)
		वापस rc;

	dcssblk_pdev = platक्रमm_device_रेजिस्टर_simple("dcssblk", -1, शून्य,
							0);
	अगर (IS_ERR(dcssblk_pdev)) अणु
		rc = PTR_ERR(dcssblk_pdev);
		जाओ out_pdrv;
	पूर्ण

	dcssblk_root_dev = root_device_रेजिस्टर("dcssblk");
	अगर (IS_ERR(dcssblk_root_dev)) अणु
		rc = PTR_ERR(dcssblk_root_dev);
		जाओ out_pdev;
	पूर्ण
	rc = device_create_file(dcssblk_root_dev, &dev_attr_add);
	अगर (rc)
		जाओ out_root;
	rc = device_create_file(dcssblk_root_dev, &dev_attr_हटाओ);
	अगर (rc)
		जाओ out_root;
	rc = रेजिस्टर_blkdev(0, DCSSBLK_NAME);
	अगर (rc < 0)
		जाओ out_root;
	dcssblk_major = rc;
	init_rwsem(&dcssblk_devices_sem);

	dcssblk_check_params();
	वापस 0;

out_root:
	root_device_unरेजिस्टर(dcssblk_root_dev);
out_pdev:
	platक्रमm_device_unरेजिस्टर(dcssblk_pdev);
out_pdrv:
	platक्रमm_driver_unरेजिस्टर(&dcssblk_pdrv);
	वापस rc;
पूर्ण

module_init(dcssblk_init);
module_निकास(dcssblk_निकास);

module_param_string(segments, dcssblk_segments, DCSSBLK_PARM_LEN, 0444);
MODULE_PARM_DESC(segments, "Name of DCSS segment(s) to be loaded, "
		 "comma-separated list, names in each set separated "
		 "by commas are separated by colons, each set contains "
		 "names of contiguous segments and each name max. 8 chars.\n"
		 "Adding \"(local)\" to the end of each set equals echoing 0 "
		 "to /sys/devices/dcssblk/<device name>/shared after loading "
		 "the contiguous segments - \n"
		 "e.g. segments=\"mydcss1,mydcss2:mydcss3,mydcss4(local)\"");

MODULE_LICENSE("GPL");
