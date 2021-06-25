<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(c) 2014 Intel Mobile Communications GmbH
 * Copyright(c) 2015 Intel Deutschland GmbH
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 * Author: Johannes Berg <johannes@sipsolutions.net>
 */
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/devcoredump.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/workqueue.h>

अटल काष्ठा class devcd_class;

/* global disable flag, क्रम security purposes */
अटल bool devcd_disabled;

/* अगर data isn't पढ़ो by userspace after 5 minutes then delete it */
#घोषणा DEVCD_TIMEOUT	(HZ * 60 * 5)

काष्ठा devcd_entry अणु
	काष्ठा device devcd_dev;
	व्योम *data;
	माप_प्रकार datalen;
	काष्ठा module *owner;
	sमाप_प्रकार (*पढ़ो)(अक्षर *buffer, loff_t offset, माप_प्रकार count,
			व्योम *data, माप_प्रकार datalen);
	व्योम (*मुक्त)(व्योम *data);
	काष्ठा delayed_work del_wk;
	काष्ठा device *failing_dev;
पूर्ण;

अटल काष्ठा devcd_entry *dev_to_devcd(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा devcd_entry, devcd_dev);
पूर्ण

अटल व्योम devcd_dev_release(काष्ठा device *dev)
अणु
	काष्ठा devcd_entry *devcd = dev_to_devcd(dev);

	devcd->मुक्त(devcd->data);
	module_put(devcd->owner);

	/*
	 * this seems racy, but I करोn't see a notअगरier or such on
	 * a काष्ठा device to know when it goes away?
	 */
	अगर (devcd->failing_dev->kobj.sd)
		sysfs_delete_link(&devcd->failing_dev->kobj, &dev->kobj,
				  "devcoredump");

	put_device(devcd->failing_dev);
	kमुक्त(devcd);
पूर्ण

अटल व्योम devcd_del(काष्ठा work_काष्ठा *wk)
अणु
	काष्ठा devcd_entry *devcd;

	devcd = container_of(wk, काष्ठा devcd_entry, del_wk.work);

	device_del(&devcd->devcd_dev);
	put_device(&devcd->devcd_dev);
पूर्ण

अटल sमाप_प्रकार devcd_data_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			       काष्ठा bin_attribute *bin_attr,
			       अक्षर *buffer, loff_t offset, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा devcd_entry *devcd = dev_to_devcd(dev);

	वापस devcd->पढ़ो(buffer, offset, count, devcd->data, devcd->datalen);
पूर्ण

अटल sमाप_प्रकार devcd_data_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *bin_attr,
				अक्षर *buffer, loff_t offset, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा devcd_entry *devcd = dev_to_devcd(dev);

	mod_delayed_work(प्रणाली_wq, &devcd->del_wk, 0);

	वापस count;
पूर्ण

अटल काष्ठा bin_attribute devcd_attr_data = अणु
	.attr = अणु .name = "data", .mode = S_IRUSR | S_IWUSR, पूर्ण,
	.size = 0,
	.पढ़ो = devcd_data_पढ़ो,
	.ग_लिखो = devcd_data_ग_लिखो,
पूर्ण;

अटल काष्ठा bin_attribute *devcd_dev_bin_attrs[] = अणु
	&devcd_attr_data, शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group devcd_dev_group = अणु
	.bin_attrs = devcd_dev_bin_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *devcd_dev_groups[] = अणु
	&devcd_dev_group, शून्य,
पूर्ण;

अटल पूर्णांक devcd_मुक्त(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा devcd_entry *devcd = dev_to_devcd(dev);

	flush_delayed_work(&devcd->del_wk);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार disabled_show(काष्ठा class *class, काष्ठा class_attribute *attr,
			     अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", devcd_disabled);
पूर्ण

अटल sमाप_प्रकार disabled_store(काष्ठा class *class, काष्ठा class_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	दीर्घ पंचांगp = simple_म_से_दीर्घ(buf, शून्य, 10);

	/*
	 * This essentially makes the attribute ग_लिखो-once, since you can't
	 * go back to not having it disabled. This is पूर्णांकentional, it serves
	 * as a प्रणाली lockकरोwn feature.
	 */
	अगर (पंचांगp != 1)
		वापस -EINVAL;

	devcd_disabled = true;

	class_क्रम_each_device(&devcd_class, शून्य, शून्य, devcd_मुक्त);

	वापस count;
पूर्ण
अटल CLASS_ATTR_RW(disabled);

अटल काष्ठा attribute *devcd_class_attrs[] = अणु
	&class_attr_disabled.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(devcd_class);

अटल काष्ठा class devcd_class = अणु
	.name		= "devcoredump",
	.owner		= THIS_MODULE,
	.dev_release	= devcd_dev_release,
	.dev_groups	= devcd_dev_groups,
	.class_groups	= devcd_class_groups,
पूर्ण;

अटल sमाप_प्रकार devcd_पढ़ोv(अक्षर *buffer, loff_t offset, माप_प्रकार count,
			   व्योम *data, माप_प्रकार datalen)
अणु
	वापस memory_पढ़ो_from_buffer(buffer, count, &offset, data, datalen);
पूर्ण

अटल व्योम devcd_मुक्तv(व्योम *data)
अणु
	vमुक्त(data);
पूर्ण

/**
 * dev_coredumpv - create device coredump with vदो_स्मृति data
 * @dev: the काष्ठा device क्रम the crashed device
 * @data: vदो_स्मृति data containing the device coredump
 * @datalen: length of the data
 * @gfp: allocation flags
 *
 * This function takes ownership of the vदो_स्मृति'ed data and will मुक्त
 * it when it is no दीर्घer used. See dev_coredumpm() क्रम more inक्रमmation.
 */
व्योम dev_coredumpv(काष्ठा device *dev, व्योम *data, माप_प्रकार datalen,
		   gfp_t gfp)
अणु
	dev_coredumpm(dev, शून्य, data, datalen, gfp, devcd_पढ़ोv, devcd_मुक्तv);
पूर्ण
EXPORT_SYMBOL_GPL(dev_coredumpv);

अटल पूर्णांक devcd_match_failing(काष्ठा device *dev, स्थिर व्योम *failing)
अणु
	काष्ठा devcd_entry *devcd = dev_to_devcd(dev);

	वापस devcd->failing_dev == failing;
पूर्ण

/**
 * devcd_मुक्त_sgtable - मुक्त all the memory of the given scatterlist table
 * (i.e. both pages and scatterlist instances)
 * NOTE: अगर two tables allocated with devcd_alloc_sgtable and then chained
 * using the sg_chain function then that function should be called only once
 * on the chained table
 * @data: poपूर्णांकer to sg_table to मुक्त
 */
अटल व्योम devcd_मुक्त_sgtable(व्योम *data)
अणु
	_devcd_मुक्त_sgtable(data);
पूर्ण

/**
 * devcd_पढ़ो_from_sgtable - copy data from sg_table to a given buffer
 * and वापस the number of bytes पढ़ो
 * @buffer: the buffer to copy the data to it
 * @buf_len: the length of the buffer
 * @data: the scatterlist table to copy from
 * @offset: start copy from @offset@ bytes from the head of the data
 *	in the given scatterlist
 * @data_len: the length of the data in the sg_table
 */
अटल sमाप_प्रकार devcd_पढ़ो_from_sgtable(अक्षर *buffer, loff_t offset,
				       माप_प्रकार buf_len, व्योम *data,
				       माप_प्रकार data_len)
अणु
	काष्ठा scatterlist *table = data;

	अगर (offset > data_len)
		वापस -EINVAL;

	अगर (offset + buf_len > data_len)
		buf_len = data_len - offset;
	वापस sg_pcopy_to_buffer(table, sg_nents(table), buffer, buf_len,
				  offset);
पूर्ण

/**
 * dev_coredumpm - create device coredump with पढ़ो/मुक्त methods
 * @dev: the काष्ठा device क्रम the crashed device
 * @owner: the module that contains the पढ़ो/मुक्त functions, use %THIS_MODULE
 * @data: data cookie क्रम the @पढ़ो/@मुक्त functions
 * @datalen: length of the data
 * @gfp: allocation flags
 * @पढ़ो: function to पढ़ो from the given buffer
 * @मुक्त: function to मुक्त the given buffer
 *
 * Creates a new device coredump क्रम the given device. If a previous one hasn't
 * been पढ़ो yet, the new coredump is discarded. The data lअगरeसमय is determined
 * by the device coredump framework and when it is no दीर्घer needed the @मुक्त
 * function will be called to मुक्त the data.
 */
व्योम dev_coredumpm(काष्ठा device *dev, काष्ठा module *owner,
		   व्योम *data, माप_प्रकार datalen, gfp_t gfp,
		   sमाप_प्रकार (*पढ़ो)(अक्षर *buffer, loff_t offset, माप_प्रकार count,
				   व्योम *data, माप_प्रकार datalen),
		   व्योम (*मुक्त)(व्योम *data))
अणु
	अटल atomic_t devcd_count = ATOMIC_INIT(0);
	काष्ठा devcd_entry *devcd;
	काष्ठा device *existing;

	अगर (devcd_disabled)
		जाओ मुक्त;

	existing = class_find_device(&devcd_class, शून्य, dev,
				     devcd_match_failing);
	अगर (existing) अणु
		put_device(existing);
		जाओ मुक्त;
	पूर्ण

	अगर (!try_module_get(owner))
		जाओ मुक्त;

	devcd = kzalloc(माप(*devcd), gfp);
	अगर (!devcd)
		जाओ put_module;

	devcd->owner = owner;
	devcd->data = data;
	devcd->datalen = datalen;
	devcd->पढ़ो = पढ़ो;
	devcd->मुक्त = मुक्त;
	devcd->failing_dev = get_device(dev);

	device_initialize(&devcd->devcd_dev);

	dev_set_name(&devcd->devcd_dev, "devcd%d",
		     atomic_inc_वापस(&devcd_count));
	devcd->devcd_dev.class = &devcd_class;

	अगर (device_add(&devcd->devcd_dev))
		जाओ put_device;

	/*
	 * These should normally not fail, but there is no problem
	 * continuing without the links, so just warn instead of
	 * failing.
	 */
	अगर (sysfs_create_link(&devcd->devcd_dev.kobj, &dev->kobj,
			      "failing_device") ||
	    sysfs_create_link(&dev->kobj, &devcd->devcd_dev.kobj,
		              "devcoredump"))
		dev_warn(dev, "devcoredump create_link failed\n");

	INIT_DELAYED_WORK(&devcd->del_wk, devcd_del);
	schedule_delayed_work(&devcd->del_wk, DEVCD_TIMEOUT);

	वापस;
 put_device:
	put_device(&devcd->devcd_dev);
 put_module:
	module_put(owner);
 मुक्त:
	मुक्त(data);
पूर्ण
EXPORT_SYMBOL_GPL(dev_coredumpm);

/**
 * dev_coredumpsg - create device coredump that uses scatterlist as data
 * parameter
 * @dev: the काष्ठा device क्रम the crashed device
 * @table: the dump data
 * @datalen: length of the data
 * @gfp: allocation flags
 *
 * Creates a new device coredump क्रम the given device. If a previous one hasn't
 * been पढ़ो yet, the new coredump is discarded. The data lअगरeसमय is determined
 * by the device coredump framework and when it is no दीर्घer needed
 * it will मुक्त the data.
 */
व्योम dev_coredumpsg(काष्ठा device *dev, काष्ठा scatterlist *table,
		    माप_प्रकार datalen, gfp_t gfp)
अणु
	dev_coredumpm(dev, शून्य, table, datalen, gfp, devcd_पढ़ो_from_sgtable,
		      devcd_मुक्त_sgtable);
पूर्ण
EXPORT_SYMBOL_GPL(dev_coredumpsg);

अटल पूर्णांक __init devcoredump_init(व्योम)
अणु
	वापस class_रेजिस्टर(&devcd_class);
पूर्ण
__initcall(devcoredump_init);

अटल व्योम __निकास devcoredump_निकास(व्योम)
अणु
	class_क्रम_each_device(&devcd_class, शून्य, शून्य, devcd_मुक्त);
	class_unरेजिस्टर(&devcd_class);
पूर्ण
__निकासcall(devcoredump_निकास);
