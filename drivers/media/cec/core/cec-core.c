<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cec-core.c - HDMI Consumer Electronics Control framework - Core
 *
 * Copyright 2016 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kmod.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#समावेश "cec-priv.h"

#घोषणा CEC_NUM_DEVICES	256
#घोषणा CEC_NAME	"cec"

पूर्णांक cec_debug;
module_param_named(debug, cec_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "debug level (0-2)");

अटल bool debug_phys_addr;
module_param(debug_phys_addr, bool, 0644);
MODULE_PARM_DESC(debug_phys_addr, "add CEC_CAP_PHYS_ADDR if set");

अटल dev_t cec_dev_t;

/* Active devices */
अटल DEFINE_MUTEX(cec_devnode_lock);
अटल DECLARE_BITMAP(cec_devnode_nums, CEC_NUM_DEVICES);

अटल काष्ठा dentry *top_cec_dir;

/* dev to cec_devnode */
#घोषणा to_cec_devnode(cd) container_of(cd, काष्ठा cec_devnode, dev)

पूर्णांक cec_get_device(काष्ठा cec_devnode *devnode)
अणु
	/*
	 * Check अगर the cec device is available. This needs to be करोne with
	 * the devnode->lock held to prevent an खोलो/unरेजिस्टर race:
	 * without the lock, the device could be unरेजिस्टरed and मुक्तd between
	 * the devnode->रेजिस्टरed check and get_device() calls, leading to
	 * a crash.
	 */
	mutex_lock(&devnode->lock);
	/*
	 * वापस ENXIO अगर the cec device has been हटाओd
	 * alपढ़ोy or अगर it is not रेजिस्टरed anymore.
	 */
	अगर (!devnode->रेजिस्टरed) अणु
		mutex_unlock(&devnode->lock);
		वापस -ENXIO;
	पूर्ण
	/* and increase the device refcount */
	get_device(&devnode->dev);
	mutex_unlock(&devnode->lock);
	वापस 0;
पूर्ण

व्योम cec_put_device(काष्ठा cec_devnode *devnode)
अणु
	put_device(&devnode->dev);
पूर्ण

/* Called when the last user of the cec device निकासs. */
अटल व्योम cec_devnode_release(काष्ठा device *cd)
अणु
	काष्ठा cec_devnode *devnode = to_cec_devnode(cd);

	mutex_lock(&cec_devnode_lock);
	/* Mark device node number as मुक्त */
	clear_bit(devnode->minor, cec_devnode_nums);
	mutex_unlock(&cec_devnode_lock);

	cec_delete_adapter(to_cec_adapter(devnode));
पूर्ण

अटल काष्ठा bus_type cec_bus_type = अणु
	.name = CEC_NAME,
पूर्ण;

/*
 * Register a cec device node
 *
 * The registration code assigns minor numbers and रेजिस्टरs the new device node
 * with the kernel. An error is वापसed अगर no मुक्त minor number can be found,
 * or अगर the registration of the device node fails.
 *
 * Zero is वापसed on success.
 *
 * Note that अगर the cec_devnode_रेजिस्टर call fails, the release() callback of
 * the cec_devnode काष्ठाure is *not* called, so the caller is responsible क्रम
 * मुक्तing any data.
 */
अटल पूर्णांक __must_check cec_devnode_रेजिस्टर(काष्ठा cec_devnode *devnode,
					     काष्ठा module *owner)
अणु
	पूर्णांक minor;
	पूर्णांक ret;

	/* Part 1: Find a मुक्त minor number */
	mutex_lock(&cec_devnode_lock);
	minor = find_next_zero_bit(cec_devnode_nums, CEC_NUM_DEVICES, 0);
	अगर (minor == CEC_NUM_DEVICES) अणु
		mutex_unlock(&cec_devnode_lock);
		pr_err("could not get a free minor\n");
		वापस -ENखाता;
	पूर्ण

	set_bit(minor, cec_devnode_nums);
	mutex_unlock(&cec_devnode_lock);

	devnode->minor = minor;
	devnode->dev.bus = &cec_bus_type;
	devnode->dev.devt = MKDEV(MAJOR(cec_dev_t), minor);
	devnode->dev.release = cec_devnode_release;
	dev_set_name(&devnode->dev, "cec%d", devnode->minor);
	device_initialize(&devnode->dev);

	/* Part 2: Initialize and रेजिस्टर the अक्षरacter device */
	cdev_init(&devnode->cdev, &cec_devnode_fops);
	devnode->cdev.owner = owner;
	kobject_set_name(&devnode->cdev.kobj, "cec%d", devnode->minor);

	devnode->रेजिस्टरed = true;
	ret = cdev_device_add(&devnode->cdev, &devnode->dev);
	अगर (ret) अणु
		devnode->रेजिस्टरed = false;
		pr_err("%s: cdev_device_add failed\n", __func__);
		जाओ clr_bit;
	पूर्ण

	वापस 0;

clr_bit:
	mutex_lock(&cec_devnode_lock);
	clear_bit(devnode->minor, cec_devnode_nums);
	mutex_unlock(&cec_devnode_lock);
	वापस ret;
पूर्ण

/*
 * Unरेजिस्टर a cec device node
 *
 * This unरेजिस्टरs the passed device. Future खोलो calls will be met with
 * errors.
 *
 * This function can safely be called अगर the device node has never been
 * रेजिस्टरed or has alपढ़ोy been unरेजिस्टरed.
 */
अटल व्योम cec_devnode_unरेजिस्टर(काष्ठा cec_adapter *adap)
अणु
	काष्ठा cec_devnode *devnode = &adap->devnode;
	काष्ठा cec_fh *fh;

	mutex_lock(&devnode->lock);

	/* Check अगर devnode was never रेजिस्टरed or alपढ़ोy unरेजिस्टरed */
	अगर (!devnode->रेजिस्टरed || devnode->unरेजिस्टरed) अणु
		mutex_unlock(&devnode->lock);
		वापस;
	पूर्ण
	devnode->रेजिस्टरed = false;
	devnode->unरेजिस्टरed = true;

	list_क्रम_each_entry(fh, &devnode->fhs, list)
		wake_up_पूर्णांकerruptible(&fh->रुको);

	mutex_unlock(&devnode->lock);

	mutex_lock(&adap->lock);
	__cec_s_phys_addr(adap, CEC_PHYS_ADDR_INVALID, false);
	__cec_s_log_addrs(adap, शून्य, false);
	mutex_unlock(&adap->lock);

	cdev_device_del(&devnode->cdev, &devnode->dev);
	put_device(&devnode->dev);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल sमाप_प्रकार cec_error_inj_ग_लिखो(काष्ठा file *file,
	स्थिर अक्षर __user *ubuf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *sf = file->निजी_data;
	काष्ठा cec_adapter *adap = sf->निजी;
	अक्षर *buf;
	अक्षर *line;
	अक्षर *p;

	buf = memdup_user_nul(ubuf, min_t(माप_प्रकार, PAGE_SIZE, count));
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);
	p = buf;
	जबतक (p && *p) अणु
		p = skip_spaces(p);
		line = strsep(&p, "\n");
		अगर (!*line || *line == '#')
			जारी;
		अगर (!adap->ops->error_inj_parse_line(adap, line)) अणु
			kमुक्त(buf);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	kमुक्त(buf);
	वापस count;
पूर्ण

अटल पूर्णांक cec_error_inj_show(काष्ठा seq_file *sf, व्योम *unused)
अणु
	काष्ठा cec_adapter *adap = sf->निजी;

	वापस adap->ops->error_inj_show(adap, sf);
पूर्ण

अटल पूर्णांक cec_error_inj_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, cec_error_inj_show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations cec_error_inj_fops = अणु
	.खोलो = cec_error_inj_खोलो,
	.ग_लिखो = cec_error_inj_ग_लिखो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;
#पूर्ण_अगर

काष्ठा cec_adapter *cec_allocate_adapter(स्थिर काष्ठा cec_adap_ops *ops,
					 व्योम *priv, स्थिर अक्षर *name, u32 caps,
					 u8 available_las)
अणु
	काष्ठा cec_adapter *adap;
	पूर्णांक res;

#अगर_अघोषित CONFIG_MEDIA_CEC_RC
	caps &= ~CEC_CAP_RC;
#पूर्ण_अगर

	अगर (WARN_ON(!caps))
		वापस ERR_PTR(-EINVAL);
	अगर (WARN_ON(!ops))
		वापस ERR_PTR(-EINVAL);
	अगर (WARN_ON(!available_las || available_las > CEC_MAX_LOG_ADDRS))
		वापस ERR_PTR(-EINVAL);
	adap = kzalloc(माप(*adap), GFP_KERNEL);
	अगर (!adap)
		वापस ERR_PTR(-ENOMEM);
	strscpy(adap->name, name, माप(adap->name));
	adap->phys_addr = CEC_PHYS_ADDR_INVALID;
	adap->cec_pin_is_high = true;
	adap->log_addrs.cec_version = CEC_OP_CEC_VERSION_2_0;
	adap->log_addrs.venकरोr_id = CEC_VENDOR_ID_NONE;
	adap->capabilities = caps;
	अगर (debug_phys_addr)
		adap->capabilities |= CEC_CAP_PHYS_ADDR;
	adap->needs_hpd = caps & CEC_CAP_NEEDS_HPD;
	adap->available_log_addrs = available_las;
	adap->sequence = 0;
	adap->ops = ops;
	adap->priv = priv;
	mutex_init(&adap->lock);
	INIT_LIST_HEAD(&adap->transmit_queue);
	INIT_LIST_HEAD(&adap->रुको_queue);
	init_रुकोqueue_head(&adap->kthपढ़ो_रुकोq);

	/* adap->devnode initialization */
	INIT_LIST_HEAD(&adap->devnode.fhs);
	mutex_init(&adap->devnode.lock);

	adap->kthपढ़ो = kthपढ़ो_run(cec_thपढ़ो_func, adap, "cec-%s", name);
	अगर (IS_ERR(adap->kthपढ़ो)) अणु
		pr_err("cec-%s: kernel_thread() failed\n", name);
		res = PTR_ERR(adap->kthपढ़ो);
		kमुक्त(adap);
		वापस ERR_PTR(res);
	पूर्ण

#अगर_घोषित CONFIG_MEDIA_CEC_RC
	अगर (!(caps & CEC_CAP_RC))
		वापस adap;

	/* Prepare the RC input device */
	adap->rc = rc_allocate_device(RC_DRIVER_SCANCODE);
	अगर (!adap->rc) अणु
		pr_err("cec-%s: failed to allocate memory for rc_dev\n",
		       name);
		kthपढ़ो_stop(adap->kthपढ़ो);
		kमुक्त(adap);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	snम_लिखो(adap->input_phys, माप(adap->input_phys),
		 "%s/input0", adap->name);

	adap->rc->device_name = adap->name;
	adap->rc->input_phys = adap->input_phys;
	adap->rc->input_id.bustype = BUS_CEC;
	adap->rc->input_id.venकरोr = 0;
	adap->rc->input_id.product = 0;
	adap->rc->input_id.version = 1;
	adap->rc->driver_name = CEC_NAME;
	adap->rc->allowed_protocols = RC_PROTO_BIT_CEC;
	adap->rc->priv = adap;
	adap->rc->map_name = RC_MAP_CEC;
	adap->rc->समयout = MS_TO_US(550);
#पूर्ण_अगर
	वापस adap;
पूर्ण
EXPORT_SYMBOL_GPL(cec_allocate_adapter);

पूर्णांक cec_रेजिस्टर_adapter(काष्ठा cec_adapter *adap,
			 काष्ठा device *parent)
अणु
	पूर्णांक res;

	अगर (IS_ERR_OR_शून्य(adap))
		वापस 0;

	अगर (WARN_ON(!parent))
		वापस -EINVAL;

	adap->owner = parent->driver->owner;
	adap->devnode.dev.parent = parent;

#अगर_घोषित CONFIG_MEDIA_CEC_RC
	अगर (adap->capabilities & CEC_CAP_RC) अणु
		adap->rc->dev.parent = parent;
		res = rc_रेजिस्टर_device(adap->rc);

		अगर (res) अणु
			pr_err("cec-%s: failed to prepare input device\n",
			       adap->name);
			rc_मुक्त_device(adap->rc);
			adap->rc = शून्य;
			वापस res;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	res = cec_devnode_रेजिस्टर(&adap->devnode, adap->owner);
	अगर (res) अणु
#अगर_घोषित CONFIG_MEDIA_CEC_RC
		/* Note: rc_unरेजिस्टर also calls rc_मुक्त */
		rc_unरेजिस्टर_device(adap->rc);
		adap->rc = शून्य;
#पूर्ण_अगर
		वापस res;
	पूर्ण

	dev_set_drvdata(&adap->devnode.dev, adap);
#अगर_घोषित CONFIG_DEBUG_FS
	अगर (!top_cec_dir)
		वापस 0;

	adap->cec_dir = debugfs_create_dir(dev_name(&adap->devnode.dev),
					   top_cec_dir);

	debugfs_create_devm_seqfile(&adap->devnode.dev, "status", adap->cec_dir,
				    cec_adap_status);

	अगर (!adap->ops->error_inj_show || !adap->ops->error_inj_parse_line)
		वापस 0;
	debugfs_create_file("error-inj", 0644, adap->cec_dir, adap,
			    &cec_error_inj_fops);
#पूर्ण_अगर
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cec_रेजिस्टर_adapter);

व्योम cec_unरेजिस्टर_adapter(काष्ठा cec_adapter *adap)
अणु
	अगर (IS_ERR_OR_शून्य(adap))
		वापस;

#अगर_घोषित CONFIG_MEDIA_CEC_RC
	/* Note: rc_unरेजिस्टर also calls rc_मुक्त */
	rc_unरेजिस्टर_device(adap->rc);
	adap->rc = शून्य;
#पूर्ण_अगर
	debugfs_हटाओ_recursive(adap->cec_dir);
#अगर_घोषित CONFIG_CEC_NOTIFIER
	cec_notअगरier_cec_adap_unरेजिस्टर(adap->notअगरier, adap);
#पूर्ण_अगर
	cec_devnode_unरेजिस्टर(adap);
पूर्ण
EXPORT_SYMBOL_GPL(cec_unरेजिस्टर_adapter);

व्योम cec_delete_adapter(काष्ठा cec_adapter *adap)
अणु
	अगर (IS_ERR_OR_शून्य(adap))
		वापस;
	अगर (adap->kthपढ़ो_config)
		kthपढ़ो_stop(adap->kthपढ़ो_config);
	kthपढ़ो_stop(adap->kthपढ़ो);
	अगर (adap->ops->adap_मुक्त)
		adap->ops->adap_मुक्त(adap);
#अगर_घोषित CONFIG_MEDIA_CEC_RC
	rc_मुक्त_device(adap->rc);
#पूर्ण_अगर
	kमुक्त(adap);
पूर्ण
EXPORT_SYMBOL_GPL(cec_delete_adapter);

/*
 *	Initialise cec क्रम linux
 */
अटल पूर्णांक __init cec_devnode_init(व्योम)
अणु
	पूर्णांक ret = alloc_chrdev_region(&cec_dev_t, 0, CEC_NUM_DEVICES, CEC_NAME);

	अगर (ret < 0) अणु
		pr_warn("cec: unable to allocate major\n");
		वापस ret;
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
	top_cec_dir = debugfs_create_dir("cec", शून्य);
	अगर (IS_ERR_OR_शून्य(top_cec_dir)) अणु
		pr_warn("cec: Failed to create debugfs cec dir\n");
		top_cec_dir = शून्य;
	पूर्ण
#पूर्ण_अगर

	ret = bus_रेजिस्टर(&cec_bus_type);
	अगर (ret < 0) अणु
		unरेजिस्टर_chrdev_region(cec_dev_t, CEC_NUM_DEVICES);
		pr_warn("cec: bus_register failed\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास cec_devnode_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(top_cec_dir);
	bus_unरेजिस्टर(&cec_bus_type);
	unरेजिस्टर_chrdev_region(cec_dev_t, CEC_NUM_DEVICES);
पूर्ण

subsys_initcall(cec_devnode_init);
module_निकास(cec_devnode_निकास)

MODULE_AUTHOR("Hans Verkuil <hans.verkuil@cisco.com>");
MODULE_DESCRIPTION("Device node registration for cec drivers");
MODULE_LICENSE("GPL");
