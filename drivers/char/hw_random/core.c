<शैली गुरु>
/*
 * hw_अक्रमom/core.c: HWRNG core API
 *
 * Copyright 2006 Michael Buesch <m@bues.ch>
 * Copyright 2005 (c) MontaVista Software, Inc.
 *
 * Please पढ़ो Documentation/admin-guide/hw_अक्रमom.rst क्रम details on use.
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#घोषणा RNG_MODULE_NAME		"hw_random"

अटल काष्ठा hwrng *current_rng;
/* the current rng has been explicitly chosen by user via sysfs */
अटल पूर्णांक cur_rng_set_by_user;
अटल काष्ठा task_काष्ठा *hwrng_fill;
/* list of रेजिस्टरed rngs, sorted decending by quality */
अटल LIST_HEAD(rng_list);
/* Protects rng_list and current_rng */
अटल DEFINE_MUTEX(rng_mutex);
/* Protects rng पढ़ो functions, data_avail, rng_buffer and rng_fillbuf */
अटल DEFINE_MUTEX(पढ़ोing_mutex);
अटल पूर्णांक data_avail;
अटल u8 *rng_buffer, *rng_fillbuf;
अटल अचिन्हित लघु current_quality;
अटल अचिन्हित लघु शेष_quality; /* = 0; शेष to "off" */

module_param(current_quality, uलघु, 0644);
MODULE_PARM_DESC(current_quality,
		 "current hwrng entropy estimation per 1024 bits of input");
module_param(शेष_quality, uलघु, 0644);
MODULE_PARM_DESC(शेष_quality,
		 "default entropy content of hwrng per 1024 bits of input");

अटल व्योम drop_current_rng(व्योम);
अटल पूर्णांक hwrng_init(काष्ठा hwrng *rng);
अटल व्योम start_khwrngd(व्योम);

अटल अंतरभूत पूर्णांक rng_get_data(काष्ठा hwrng *rng, u8 *buffer, माप_प्रकार size,
			       पूर्णांक रुको);

अटल माप_प्रकार rng_buffer_size(व्योम)
अणु
	वापस SMP_CACHE_BYTES < 32 ? 32 : SMP_CACHE_BYTES;
पूर्ण

अटल व्योम add_early_अक्रमomness(काष्ठा hwrng *rng)
अणु
	पूर्णांक bytes_पढ़ो;
	माप_प्रकार size = min_t(माप_प्रकार, 16, rng_buffer_size());

	mutex_lock(&पढ़ोing_mutex);
	bytes_पढ़ो = rng_get_data(rng, rng_buffer, size, 0);
	mutex_unlock(&पढ़ोing_mutex);
	अगर (bytes_पढ़ो > 0)
		add_device_अक्रमomness(rng_buffer, bytes_पढ़ो);
पूर्ण

अटल अंतरभूत व्योम cleanup_rng(काष्ठा kref *kref)
अणु
	काष्ठा hwrng *rng = container_of(kref, काष्ठा hwrng, ref);

	अगर (rng->cleanup)
		rng->cleanup(rng);

	complete(&rng->cleanup_करोne);
पूर्ण

अटल पूर्णांक set_current_rng(काष्ठा hwrng *rng)
अणु
	पूर्णांक err;

	BUG_ON(!mutex_is_locked(&rng_mutex));

	err = hwrng_init(rng);
	अगर (err)
		वापस err;

	drop_current_rng();
	current_rng = rng;

	वापस 0;
पूर्ण

अटल व्योम drop_current_rng(व्योम)
अणु
	BUG_ON(!mutex_is_locked(&rng_mutex));
	अगर (!current_rng)
		वापस;

	/* decrease last reference क्रम triggering the cleanup */
	kref_put(&current_rng->ref, cleanup_rng);
	current_rng = शून्य;
पूर्ण

/* Returns ERR_PTR(), शून्य or refcounted hwrng */
अटल काष्ठा hwrng *get_current_rng_nolock(व्योम)
अणु
	अगर (current_rng)
		kref_get(&current_rng->ref);

	वापस current_rng;
पूर्ण

अटल काष्ठा hwrng *get_current_rng(व्योम)
अणु
	काष्ठा hwrng *rng;

	अगर (mutex_lock_पूर्णांकerruptible(&rng_mutex))
		वापस ERR_PTR(-ERESTARTSYS);

	rng = get_current_rng_nolock();

	mutex_unlock(&rng_mutex);
	वापस rng;
पूर्ण

अटल व्योम put_rng(काष्ठा hwrng *rng)
अणु
	/*
	 * Hold rng_mutex here so we serialize in हाल they set_current_rng
	 * on rng again immediately.
	 */
	mutex_lock(&rng_mutex);
	अगर (rng)
		kref_put(&rng->ref, cleanup_rng);
	mutex_unlock(&rng_mutex);
पूर्ण

अटल पूर्णांक hwrng_init(काष्ठा hwrng *rng)
अणु
	अगर (kref_get_unless_zero(&rng->ref))
		जाओ skip_init;

	अगर (rng->init) अणु
		पूर्णांक ret;

		ret =  rng->init(rng);
		अगर (ret)
			वापस ret;
	पूर्ण

	kref_init(&rng->ref);
	reinit_completion(&rng->cleanup_करोne);

skip_init:
	current_quality = rng->quality ? : शेष_quality;
	अगर (current_quality > 1024)
		current_quality = 1024;

	अगर (current_quality == 0 && hwrng_fill)
		kthपढ़ो_stop(hwrng_fill);
	अगर (current_quality > 0 && !hwrng_fill)
		start_khwrngd();

	वापस 0;
पूर्ण

अटल पूर्णांक rng_dev_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	/* enक्रमce पढ़ो-only access to this chrdev */
	अगर ((filp->f_mode & FMODE_READ) == 0)
		वापस -EINVAL;
	अगर (filp->f_mode & FMODE_WRITE)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक rng_get_data(काष्ठा hwrng *rng, u8 *buffer, माप_प्रकार size,
			पूर्णांक रुको) अणु
	पूर्णांक present;

	BUG_ON(!mutex_is_locked(&पढ़ोing_mutex));
	अगर (rng->पढ़ो)
		वापस rng->पढ़ो(rng, (व्योम *)buffer, size, रुको);

	अगर (rng->data_present)
		present = rng->data_present(rng, रुको);
	अन्यथा
		present = 1;

	अगर (present)
		वापस rng->data_पढ़ो(rng, (u32 *)buffer);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार rng_dev_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
			    माप_प्रकार size, loff_t *offp)
अणु
	sमाप_प्रकार ret = 0;
	पूर्णांक err = 0;
	पूर्णांक bytes_पढ़ो, len;
	काष्ठा hwrng *rng;

	जबतक (size) अणु
		rng = get_current_rng();
		अगर (IS_ERR(rng)) अणु
			err = PTR_ERR(rng);
			जाओ out;
		पूर्ण
		अगर (!rng) अणु
			err = -ENODEV;
			जाओ out;
		पूर्ण

		अगर (mutex_lock_पूर्णांकerruptible(&पढ़ोing_mutex)) अणु
			err = -ERESTARTSYS;
			जाओ out_put;
		पूर्ण
		अगर (!data_avail) अणु
			bytes_पढ़ो = rng_get_data(rng, rng_buffer,
				rng_buffer_size(),
				!(filp->f_flags & O_NONBLOCK));
			अगर (bytes_पढ़ो < 0) अणु
				err = bytes_पढ़ो;
				जाओ out_unlock_पढ़ोing;
			पूर्ण
			data_avail = bytes_पढ़ो;
		पूर्ण

		अगर (!data_avail) अणु
			अगर (filp->f_flags & O_NONBLOCK) अणु
				err = -EAGAIN;
				जाओ out_unlock_पढ़ोing;
			पूर्ण
		पूर्ण अन्यथा अणु
			len = data_avail;
			अगर (len > size)
				len = size;

			data_avail -= len;

			अगर (copy_to_user(buf + ret, rng_buffer + data_avail,
								len)) अणु
				err = -EFAULT;
				जाओ out_unlock_पढ़ोing;
			पूर्ण

			size -= len;
			ret += len;
		पूर्ण

		mutex_unlock(&पढ़ोing_mutex);
		put_rng(rng);

		अगर (need_resched())
			schedule_समयout_पूर्णांकerruptible(1);

		अगर (संकेत_pending(current)) अणु
			err = -ERESTARTSYS;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	वापस ret ? : err;

out_unlock_पढ़ोing:
	mutex_unlock(&पढ़ोing_mutex);
out_put:
	put_rng(rng);
	जाओ out;
पूर्ण

अटल स्थिर काष्ठा file_operations rng_chrdev_ops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= rng_dev_खोलो,
	.पढ़ो		= rng_dev_पढ़ो,
	.llseek		= noop_llseek,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *rng_dev_groups[];

अटल काष्ठा miscdevice rng_miscdev = अणु
	.minor		= HWRNG_MINOR,
	.name		= RNG_MODULE_NAME,
	.nodename	= "hwrng",
	.fops		= &rng_chrdev_ops,
	.groups		= rng_dev_groups,
पूर्ण;

अटल पूर्णांक enable_best_rng(व्योम)
अणु
	पूर्णांक ret = -ENODEV;

	BUG_ON(!mutex_is_locked(&rng_mutex));

	/* rng_list is sorted by quality, use the best (=first) one */
	अगर (!list_empty(&rng_list)) अणु
		काष्ठा hwrng *new_rng;

		new_rng = list_entry(rng_list.next, काष्ठा hwrng, list);
		ret = ((new_rng == current_rng) ? 0 : set_current_rng(new_rng));
		अगर (!ret)
			cur_rng_set_by_user = 0;
	पूर्ण अन्यथा अणु
		drop_current_rng();
		cur_rng_set_by_user = 0;
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार hwrng_attr_current_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक err = -ENODEV;
	काष्ठा hwrng *rng, *old_rng, *new_rng;

	err = mutex_lock_पूर्णांकerruptible(&rng_mutex);
	अगर (err)
		वापस -ERESTARTSYS;

	old_rng = current_rng;
	अगर (sysfs_streq(buf, "")) अणु
		err = enable_best_rng();
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(rng, &rng_list, list) अणु
			अगर (sysfs_streq(rng->name, buf)) अणु
				cur_rng_set_by_user = 1;
				err = set_current_rng(rng);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	new_rng = get_current_rng_nolock();
	mutex_unlock(&rng_mutex);

	अगर (new_rng) अणु
		अगर (new_rng != old_rng)
			add_early_अक्रमomness(new_rng);
		put_rng(new_rng);
	पूर्ण

	वापस err ? : len;
पूर्ण

अटल sमाप_प्रकार hwrng_attr_current_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	sमाप_प्रकार ret;
	काष्ठा hwrng *rng;

	rng = get_current_rng();
	अगर (IS_ERR(rng))
		वापस PTR_ERR(rng);

	ret = snम_लिखो(buf, PAGE_SIZE, "%s\n", rng ? rng->name : "none");
	put_rng(rng);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार hwrng_attr_available_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	पूर्णांक err;
	काष्ठा hwrng *rng;

	err = mutex_lock_पूर्णांकerruptible(&rng_mutex);
	अगर (err)
		वापस -ERESTARTSYS;
	buf[0] = '\0';
	list_क्रम_each_entry(rng, &rng_list, list) अणु
		strlcat(buf, rng->name, PAGE_SIZE);
		strlcat(buf, " ", PAGE_SIZE);
	पूर्ण
	strlcat(buf, "\n", PAGE_SIZE);
	mutex_unlock(&rng_mutex);

	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार hwrng_attr_selected_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", cur_rng_set_by_user);
पूर्ण

अटल DEVICE_ATTR(rng_current, S_IRUGO | S_IWUSR,
		   hwrng_attr_current_show,
		   hwrng_attr_current_store);
अटल DEVICE_ATTR(rng_available, S_IRUGO,
		   hwrng_attr_available_show,
		   शून्य);
अटल DEVICE_ATTR(rng_selected, S_IRUGO,
		   hwrng_attr_selected_show,
		   शून्य);

अटल काष्ठा attribute *rng_dev_attrs[] = अणु
	&dev_attr_rng_current.attr,
	&dev_attr_rng_available.attr,
	&dev_attr_rng_selected.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(rng_dev);

अटल व्योम __निकास unरेजिस्टर_miscdev(व्योम)
अणु
	misc_deरेजिस्टर(&rng_miscdev);
पूर्ण

अटल पूर्णांक __init रेजिस्टर_miscdev(व्योम)
अणु
	वापस misc_रेजिस्टर(&rng_miscdev);
पूर्ण

अटल पूर्णांक hwrng_fillfn(व्योम *unused)
अणु
	दीर्घ rc;

	जबतक (!kthपढ़ो_should_stop()) अणु
		काष्ठा hwrng *rng;

		rng = get_current_rng();
		अगर (IS_ERR(rng) || !rng)
			अवरोध;
		mutex_lock(&पढ़ोing_mutex);
		rc = rng_get_data(rng, rng_fillbuf,
				  rng_buffer_size(), 1);
		mutex_unlock(&पढ़ोing_mutex);
		put_rng(rng);
		अगर (rc <= 0) अणु
			pr_warn("hwrng: no data available\n");
			msleep_पूर्णांकerruptible(10000);
			जारी;
		पूर्ण
		/* Outside lock, sure, but y'know: अक्रमomness. */
		add_hwgenerator_अक्रमomness((व्योम *)rng_fillbuf, rc,
					   rc * current_quality * 8 >> 10);
	पूर्ण
	hwrng_fill = शून्य;
	वापस 0;
पूर्ण

अटल व्योम start_khwrngd(व्योम)
अणु
	hwrng_fill = kthपढ़ो_run(hwrng_fillfn, शून्य, "hwrng");
	अगर (IS_ERR(hwrng_fill)) अणु
		pr_err("hwrng_fill thread creation failed\n");
		hwrng_fill = शून्य;
	पूर्ण
पूर्ण

पूर्णांक hwrng_रेजिस्टर(काष्ठा hwrng *rng)
अणु
	पूर्णांक err = -EINVAL;
	काष्ठा hwrng *पंचांगp;
	काष्ठा list_head *rng_list_ptr;
	bool is_new_current = false;

	अगर (!rng->name || (!rng->data_पढ़ो && !rng->पढ़ो))
		जाओ out;

	mutex_lock(&rng_mutex);

	/* Must not रेजिस्टर two RNGs with the same name. */
	err = -EEXIST;
	list_क्रम_each_entry(पंचांगp, &rng_list, list) अणु
		अगर (म_भेद(पंचांगp->name, rng->name) == 0)
			जाओ out_unlock;
	पूर्ण

	init_completion(&rng->cleanup_करोne);
	complete(&rng->cleanup_करोne);

	/* rng_list is sorted by decreasing quality */
	list_क्रम_each(rng_list_ptr, &rng_list) अणु
		पंचांगp = list_entry(rng_list_ptr, काष्ठा hwrng, list);
		अगर (पंचांगp->quality < rng->quality)
			अवरोध;
	पूर्ण
	list_add_tail(&rng->list, rng_list_ptr);

	अगर (!current_rng ||
	    (!cur_rng_set_by_user && rng->quality > current_rng->quality)) अणु
		/*
		 * Set new rng as current as the new rng source
		 * provides better entropy quality and was not
		 * chosen by userspace.
		 */
		err = set_current_rng(rng);
		अगर (err)
			जाओ out_unlock;
		/* to use current_rng in add_early_अक्रमomness() we need
		 * to take a ref
		 */
		is_new_current = true;
		kref_get(&rng->ref);
	पूर्ण
	mutex_unlock(&rng_mutex);
	अगर (is_new_current || !rng->init) अणु
		/*
		 * Use a new device's input to add some अक्रमomness to
		 * the प्रणाली.  If this rng device isn't going to be
		 * used right away, its init function hasn't been
		 * called yet by set_current_rng(); so only use the
		 * अक्रमomness from devices that करोn't need an init callback
		 */
		add_early_अक्रमomness(rng);
	पूर्ण
	अगर (is_new_current)
		put_rng(rng);
	वापस 0;
out_unlock:
	mutex_unlock(&rng_mutex);
out:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(hwrng_रेजिस्टर);

व्योम hwrng_unरेजिस्टर(काष्ठा hwrng *rng)
अणु
	काष्ठा hwrng *old_rng, *new_rng;
	पूर्णांक err;

	mutex_lock(&rng_mutex);

	old_rng = current_rng;
	list_del(&rng->list);
	अगर (current_rng == rng) अणु
		err = enable_best_rng();
		अगर (err) अणु
			drop_current_rng();
			cur_rng_set_by_user = 0;
		पूर्ण
	पूर्ण

	new_rng = get_current_rng_nolock();
	अगर (list_empty(&rng_list)) अणु
		mutex_unlock(&rng_mutex);
		अगर (hwrng_fill)
			kthपढ़ो_stop(hwrng_fill);
	पूर्ण अन्यथा
		mutex_unlock(&rng_mutex);

	अगर (new_rng) अणु
		अगर (old_rng != new_rng)
			add_early_अक्रमomness(new_rng);
		put_rng(new_rng);
	पूर्ण

	रुको_क्रम_completion(&rng->cleanup_करोne);
पूर्ण
EXPORT_SYMBOL_GPL(hwrng_unरेजिस्टर);

अटल व्योम devm_hwrng_release(काष्ठा device *dev, व्योम *res)
अणु
	hwrng_unरेजिस्टर(*(काष्ठा hwrng **)res);
पूर्ण

अटल पूर्णांक devm_hwrng_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा hwrng **r = res;

	अगर (WARN_ON(!r || !*r))
		वापस 0;

	वापस *r == data;
पूर्ण

पूर्णांक devm_hwrng_रेजिस्टर(काष्ठा device *dev, काष्ठा hwrng *rng)
अणु
	काष्ठा hwrng **ptr;
	पूर्णांक error;

	ptr = devres_alloc(devm_hwrng_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	error = hwrng_रेजिस्टर(rng);
	अगर (error) अणु
		devres_मुक्त(ptr);
		वापस error;
	पूर्ण

	*ptr = rng;
	devres_add(dev, ptr);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_hwrng_रेजिस्टर);

व्योम devm_hwrng_unरेजिस्टर(काष्ठा device *dev, काष्ठा hwrng *rng)
अणु
	devres_release(dev, devm_hwrng_release, devm_hwrng_match, rng);
पूर्ण
EXPORT_SYMBOL_GPL(devm_hwrng_unरेजिस्टर);

अटल पूर्णांक __init hwrng_modinit(व्योम)
अणु
	पूर्णांक ret;

	/* kदो_स्मृति makes this safe क्रम virt_to_page() in virtio_rng.c */
	rng_buffer = kदो_स्मृति(rng_buffer_size(), GFP_KERNEL);
	अगर (!rng_buffer)
		वापस -ENOMEM;

	rng_fillbuf = kदो_स्मृति(rng_buffer_size(), GFP_KERNEL);
	अगर (!rng_fillbuf) अणु
		kमुक्त(rng_buffer);
		वापस -ENOMEM;
	पूर्ण

	ret = रेजिस्टर_miscdev();
	अगर (ret) अणु
		kमुक्त(rng_fillbuf);
		kमुक्त(rng_buffer);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास hwrng_modनिकास(व्योम)
अणु
	mutex_lock(&rng_mutex);
	BUG_ON(current_rng);
	kमुक्त(rng_buffer);
	kमुक्त(rng_fillbuf);
	mutex_unlock(&rng_mutex);

	unरेजिस्टर_miscdev();
पूर्ण

module_init(hwrng_modinit);
module_निकास(hwrng_modनिकास);

MODULE_DESCRIPTION("H/W Random Number Generator (RNG) driver");
MODULE_LICENSE("GPL");
