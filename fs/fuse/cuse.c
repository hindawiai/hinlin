<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CUSE: Character device in Userspace
 *
 * Copyright (C) 2008-2009  SUSE Linux Products GmbH
 * Copyright (C) 2008-2009  Tejun Heo <tj@kernel.org>
 *
 * CUSE enables अक्षरacter devices to be implemented from userland much
 * like FUSE allows fileप्रणालीs.  On initialization /dev/cuse is
 * created.  By खोलोing the file and replying to the CUSE_INIT request
 * userland CUSE server can create a अक्षरacter device.  After that the
 * operation is very similar to FUSE.
 *
 * A CUSE instance involves the following objects.
 *
 * cuse_conn	: contains fuse_conn and serves as bonding काष्ठाure
 * channel	: file handle connected to the userland CUSE server
 * cdev		: the implemented अक्षरacter device
 * dev		: generic device क्रम cdev
 *
 * Note that 'channel' is what 'dev' is in FUSE.  As CUSE deals with
 * devices, it's called 'channel' to reduce confusion.
 *
 * channel determines when the अक्षरacter device dies.  When channel is
 * बंदd, everything begins to deकाष्ठा.  The cuse_conn is taken off
 * the lookup table preventing further access from cdev, cdev and
 * generic device are हटाओd and the base reference of cuse_conn is
 * put.
 *
 * On each खोलो, the matching cuse_conn is looked up and अगर found an
 * additional reference is taken which is released when the file is
 * बंदd.
 */

#घोषणा pr_fmt(fmt) "CUSE: " fmt

#समावेश <linux/fuse.h>
#समावेश <linux/cdev.h>
#समावेश <linux/device.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/list.h>
#समावेश <linux/magic.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/module.h>
#समावेश <linux/uपन.स>
#समावेश <linux/user_namespace.h>

#समावेश "fuse_i.h"

#घोषणा CUSE_CONNTBL_LEN	64

काष्ठा cuse_conn अणु
	काष्ठा list_head	list;	/* linked on cuse_conntbl */
	काष्ठा fuse_mount	fm;	/* Dummy mount referencing fc */
	काष्ठा fuse_conn	fc;	/* fuse connection */
	काष्ठा cdev		*cdev;	/* associated अक्षरacter device */
	काष्ठा device		*dev;	/* device representing @cdev */

	/* init parameters, set once during initialization */
	bool			unrestricted_ioctl;
पूर्ण;

अटल DEFINE_MUTEX(cuse_lock);		/* protects registration */
अटल काष्ठा list_head cuse_conntbl[CUSE_CONNTBL_LEN];
अटल काष्ठा class *cuse_class;

अटल काष्ठा cuse_conn *fc_to_cc(काष्ठा fuse_conn *fc)
अणु
	वापस container_of(fc, काष्ठा cuse_conn, fc);
पूर्ण

अटल काष्ठा list_head *cuse_conntbl_head(dev_t devt)
अणु
	वापस &cuse_conntbl[(MAJOR(devt) + MINOR(devt)) % CUSE_CONNTBL_LEN];
पूर्ण


/**************************************************************************
 * CUSE frontend operations
 *
 * These are file operations क्रम the अक्षरacter device.
 *
 * On खोलो, CUSE खोलोs a file from the FUSE mnt and stores it to
 * निजी_data of the खोलो file.  All other ops call FUSE ops on the
 * FUSE file.
 */

अटल sमाप_प्रकार cuse_पढ़ो_iter(काष्ठा kiocb *kiocb, काष्ठा iov_iter *to)
अणु
	काष्ठा fuse_io_priv io = FUSE_IO_PRIV_SYNC(kiocb);
	loff_t pos = 0;

	वापस fuse_direct_io(&io, to, &pos, FUSE_DIO_CUSE);
पूर्ण

अटल sमाप_प्रकार cuse_ग_लिखो_iter(काष्ठा kiocb *kiocb, काष्ठा iov_iter *from)
अणु
	काष्ठा fuse_io_priv io = FUSE_IO_PRIV_SYNC(kiocb);
	loff_t pos = 0;
	/*
	 * No locking or generic_ग_लिखो_checks(), the server is
	 * responsible क्रम locking and sanity checks.
	 */
	वापस fuse_direct_io(&io, from, &pos,
			      FUSE_DIO_WRITE | FUSE_DIO_CUSE);
पूर्ण

अटल पूर्णांक cuse_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	dev_t devt = inode->i_cdev->dev;
	काष्ठा cuse_conn *cc = शून्य, *pos;
	पूर्णांक rc;

	/* look up and get the connection */
	mutex_lock(&cuse_lock);
	list_क्रम_each_entry(pos, cuse_conntbl_head(devt), list)
		अगर (pos->dev->devt == devt) अणु
			fuse_conn_get(&pos->fc);
			cc = pos;
			अवरोध;
		पूर्ण
	mutex_unlock(&cuse_lock);

	/* dead? */
	अगर (!cc)
		वापस -ENODEV;

	/*
	 * Generic permission check is alपढ़ोy करोne against the chrdev
	 * file, proceed to खोलो.
	 */
	rc = fuse_करो_खोलो(&cc->fm, 0, file, 0);
	अगर (rc)
		fuse_conn_put(&cc->fc);
	वापस rc;
पूर्ण

अटल पूर्णांक cuse_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा fuse_file *ff = file->निजी_data;
	काष्ठा fuse_mount *fm = ff->fm;

	fuse_sync_release(शून्य, ff, file->f_flags);
	fuse_conn_put(fm->fc);

	वापस 0;
पूर्ण

अटल दीर्घ cuse_file_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ arg)
अणु
	काष्ठा fuse_file *ff = file->निजी_data;
	काष्ठा cuse_conn *cc = fc_to_cc(ff->fm->fc);
	अचिन्हित पूर्णांक flags = 0;

	अगर (cc->unrestricted_ioctl)
		flags |= FUSE_IOCTL_UNRESTRICTED;

	वापस fuse_करो_ioctl(file, cmd, arg, flags);
पूर्ण

अटल दीर्घ cuse_file_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				   अचिन्हित दीर्घ arg)
अणु
	काष्ठा fuse_file *ff = file->निजी_data;
	काष्ठा cuse_conn *cc = fc_to_cc(ff->fm->fc);
	अचिन्हित पूर्णांक flags = FUSE_IOCTL_COMPAT;

	अगर (cc->unrestricted_ioctl)
		flags |= FUSE_IOCTL_UNRESTRICTED;

	वापस fuse_करो_ioctl(file, cmd, arg, flags);
पूर्ण

अटल स्थिर काष्ठा file_operations cuse_frontend_fops = अणु
	.owner			= THIS_MODULE,
	.पढ़ो_iter		= cuse_पढ़ो_iter,
	.ग_लिखो_iter		= cuse_ग_लिखो_iter,
	.खोलो			= cuse_खोलो,
	.release		= cuse_release,
	.unlocked_ioctl		= cuse_file_ioctl,
	.compat_ioctl		= cuse_file_compat_ioctl,
	.poll			= fuse_file_poll,
	.llseek		= noop_llseek,
पूर्ण;


/**************************************************************************
 * CUSE channel initialization and deकाष्ठाion
 */

काष्ठा cuse_devinfo अणु
	स्थिर अक्षर		*name;
पूर्ण;

/**
 * cuse_parse_one - parse one key=value pair
 * @pp: i/o parameter क्रम the current position
 * @end: poपूर्णांकs to one past the end of the packed string
 * @keyp: out parameter क्रम key
 * @valp: out parameter क्रम value
 *
 * *@pp poपूर्णांकs to packed strings - "key0=val0\0key1=val1\0" which ends
 * at @end - 1.  This function parses one pair and set *@keyp to the
 * start of the key and *@valp to the start of the value.  Note that
 * the original string is modअगरied such that the key string is
 * terminated with '\0'.  *@pp is updated to poपूर्णांक to the next string.
 *
 * RETURNS:
 * 1 on successful parse, 0 on खातापूर्ण, -त्रुटि_सं on failure.
 */
अटल पूर्णांक cuse_parse_one(अक्षर **pp, अक्षर *end, अक्षर **keyp, अक्षर **valp)
अणु
	अक्षर *p = *pp;
	अक्षर *key, *val;

	जबतक (p < end && *p == '\0')
		p++;
	अगर (p == end)
		वापस 0;

	अगर (end[-1] != '\0') अणु
		pr_err("info not properly terminated\n");
		वापस -EINVAL;
	पूर्ण

	key = val = p;
	p += म_माप(p);

	अगर (valp) अणु
		strsep(&val, "=");
		अगर (!val)
			val = key + म_माप(key);
		key = म_मालाip(key);
		val = म_मालाip(val);
	पूर्ण अन्यथा
		key = म_मालाip(key);

	अगर (!म_माप(key)) अणु
		pr_err("zero length info key specified\n");
		वापस -EINVAL;
	पूर्ण

	*pp = p;
	*keyp = key;
	अगर (valp)
		*valp = val;

	वापस 1;
पूर्ण

/**
 * cuse_parse_dev_info - parse device info
 * @p: device info string
 * @len: length of device info string
 * @devinfo: out parameter क्रम parsed device info
 *
 * Parse @p to extract device info and store it पूर्णांकo @devinfo.  String
 * poपूर्णांकed to by @p is modअगरied by parsing and @devinfo poपूर्णांकs पूर्णांकo
 * them, so @p shouldn't be मुक्तd जबतक @devinfo is in use.
 *
 * RETURNS:
 * 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक cuse_parse_devinfo(अक्षर *p, माप_प्रकार len, काष्ठा cuse_devinfo *devinfo)
अणु
	अक्षर *end = p + len;
	अक्षर *key, *val;
	पूर्णांक rc;

	जबतक (true) अणु
		rc = cuse_parse_one(&p, end, &key, &val);
		अगर (rc < 0)
			वापस rc;
		अगर (!rc)
			अवरोध;
		अगर (म_भेद(key, "DEVNAME") == 0)
			devinfo->name = val;
		अन्यथा
			pr_warn("unknown device info \"%s\"\n", key);
	पूर्ण

	अगर (!devinfo->name || !म_माप(devinfo->name)) अणु
		pr_err("DEVNAME unspecified\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cuse_gendev_release(काष्ठा device *dev)
अणु
	kमुक्त(dev);
पूर्ण

काष्ठा cuse_init_args अणु
	काष्ठा fuse_args_pages ap;
	काष्ठा cuse_init_in in;
	काष्ठा cuse_init_out out;
	काष्ठा page *page;
	काष्ठा fuse_page_desc desc;
पूर्ण;

/**
 * cuse_process_init_reply - finish initializing CUSE channel
 *
 * This function creates the अक्षरacter device and sets up all the
 * required data काष्ठाures क्रम it.  Please पढ़ो the comment at the
 * top of this file क्रम high level overview.
 */
अटल व्योम cuse_process_init_reply(काष्ठा fuse_mount *fm,
				    काष्ठा fuse_args *args, पूर्णांक error)
अणु
	काष्ठा fuse_conn *fc = fm->fc;
	काष्ठा cuse_init_args *ia = container_of(args, typeof(*ia), ap.args);
	काष्ठा fuse_args_pages *ap = &ia->ap;
	काष्ठा cuse_conn *cc = fc_to_cc(fc), *pos;
	काष्ठा cuse_init_out *arg = &ia->out;
	काष्ठा page *page = ap->pages[0];
	काष्ठा cuse_devinfo devinfo = अणु पूर्ण;
	काष्ठा device *dev;
	काष्ठा cdev *cdev;
	dev_t devt;
	पूर्णांक rc, i;

	अगर (error || arg->major != FUSE_KERNEL_VERSION || arg->minor < 11)
		जाओ err;

	fc->minor = arg->minor;
	fc->max_पढ़ो = max_t(अचिन्हित, arg->max_पढ़ो, 4096);
	fc->max_ग_लिखो = max_t(अचिन्हित, arg->max_ग_लिखो, 4096);

	/* parse init reply */
	cc->unrestricted_ioctl = arg->flags & CUSE_UNRESTRICTED_IOCTL;

	rc = cuse_parse_devinfo(page_address(page), ap->args.out_args[1].size,
				&devinfo);
	अगर (rc)
		जाओ err;

	/* determine and reserve devt */
	devt = MKDEV(arg->dev_major, arg->dev_minor);
	अगर (!MAJOR(devt))
		rc = alloc_chrdev_region(&devt, MINOR(devt), 1, devinfo.name);
	अन्यथा
		rc = रेजिस्टर_chrdev_region(devt, 1, devinfo.name);
	अगर (rc) अणु
		pr_err("failed to register chrdev region\n");
		जाओ err;
	पूर्ण

	/* devt determined, create device */
	rc = -ENOMEM;
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		जाओ err_region;

	device_initialize(dev);
	dev_set_uevent_suppress(dev, 1);
	dev->class = cuse_class;
	dev->devt = devt;
	dev->release = cuse_gendev_release;
	dev_set_drvdata(dev, cc);
	dev_set_name(dev, "%s", devinfo.name);

	mutex_lock(&cuse_lock);

	/* make sure the device-name is unique */
	क्रम (i = 0; i < CUSE_CONNTBL_LEN; ++i) अणु
		list_क्रम_each_entry(pos, &cuse_conntbl[i], list)
			अगर (!म_भेद(dev_name(pos->dev), dev_name(dev)))
				जाओ err_unlock;
	पूर्ण

	rc = device_add(dev);
	अगर (rc)
		जाओ err_unlock;

	/* रेजिस्टर cdev */
	rc = -ENOMEM;
	cdev = cdev_alloc();
	अगर (!cdev)
		जाओ err_unlock;

	cdev->owner = THIS_MODULE;
	cdev->ops = &cuse_frontend_fops;

	rc = cdev_add(cdev, devt, 1);
	अगर (rc)
		जाओ err_cdev;

	cc->dev = dev;
	cc->cdev = cdev;

	/* make the device available */
	list_add(&cc->list, cuse_conntbl_head(devt));
	mutex_unlock(&cuse_lock);

	/* announce device availability */
	dev_set_uevent_suppress(dev, 0);
	kobject_uevent(&dev->kobj, KOBJ_ADD);
out:
	kमुक्त(ia);
	__मुक्त_page(page);
	वापस;

err_cdev:
	cdev_del(cdev);
err_unlock:
	mutex_unlock(&cuse_lock);
	put_device(dev);
err_region:
	unरेजिस्टर_chrdev_region(devt, 1);
err:
	fuse_पात_conn(fc);
	जाओ out;
पूर्ण

अटल पूर्णांक cuse_send_init(काष्ठा cuse_conn *cc)
अणु
	पूर्णांक rc;
	काष्ठा page *page;
	काष्ठा fuse_mount *fm = &cc->fm;
	काष्ठा cuse_init_args *ia;
	काष्ठा fuse_args_pages *ap;

	BUILD_BUG_ON(CUSE_INIT_INFO_MAX > PAGE_SIZE);

	rc = -ENOMEM;
	page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	अगर (!page)
		जाओ err;

	ia = kzalloc(माप(*ia), GFP_KERNEL);
	अगर (!ia)
		जाओ err_मुक्त_page;

	ap = &ia->ap;
	ia->in.major = FUSE_KERNEL_VERSION;
	ia->in.minor = FUSE_KERNEL_MINOR_VERSION;
	ia->in.flags |= CUSE_UNRESTRICTED_IOCTL;
	ap->args.opcode = CUSE_INIT;
	ap->args.in_numargs = 1;
	ap->args.in_args[0].size = माप(ia->in);
	ap->args.in_args[0].value = &ia->in;
	ap->args.out_numargs = 2;
	ap->args.out_args[0].size = माप(ia->out);
	ap->args.out_args[0].value = &ia->out;
	ap->args.out_args[1].size = CUSE_INIT_INFO_MAX;
	ap->args.out_argvar = true;
	ap->args.out_pages = true;
	ap->num_pages = 1;
	ap->pages = &ia->page;
	ap->descs = &ia->desc;
	ia->page = page;
	ia->desc.length = ap->args.out_args[1].size;
	ap->args.end = cuse_process_init_reply;

	rc = fuse_simple_background(fm, &ap->args, GFP_KERNEL);
	अगर (rc) अणु
		kमुक्त(ia);
err_मुक्त_page:
		__मुक्त_page(page);
	पूर्ण
err:
	वापस rc;
पूर्ण

अटल व्योम cuse_fc_release(काष्ठा fuse_conn *fc)
अणु
	काष्ठा cuse_conn *cc = fc_to_cc(fc);
	kमुक्त_rcu(cc, fc.rcu);
पूर्ण

/**
 * cuse_channel_खोलो - खोलो method क्रम /dev/cuse
 * @inode: inode क्रम /dev/cuse
 * @file: file काष्ठा being खोलोed
 *
 * Userland CUSE server can create a CUSE device by खोलोing /dev/cuse
 * and replying to the initialization request kernel sends.  This
 * function is responsible क्रम handling CUSE device initialization.
 * Because the fd खोलोed by this function is used during
 * initialization, this function only creates cuse_conn and sends
 * init.  The rest is delegated to a kthपढ़ो.
 *
 * RETURNS:
 * 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक cuse_channel_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा fuse_dev *fud;
	काष्ठा cuse_conn *cc;
	पूर्णांक rc;

	/* set up cuse_conn */
	cc = kzalloc(माप(*cc), GFP_KERNEL);
	अगर (!cc)
		वापस -ENOMEM;

	/*
	 * Limit the cuse channel to requests that can
	 * be represented in file->f_cred->user_ns.
	 */
	fuse_conn_init(&cc->fc, &cc->fm, file->f_cred->user_ns,
		       &fuse_dev_fiq_ops, शून्य);

	cc->fc.release = cuse_fc_release;
	fud = fuse_dev_alloc_install(&cc->fc);
	fuse_conn_put(&cc->fc);
	अगर (!fud)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&cc->list);

	cc->fc.initialized = 1;
	rc = cuse_send_init(cc);
	अगर (rc) अणु
		fuse_dev_मुक्त(fud);
		वापस rc;
	पूर्ण
	file->निजी_data = fud;

	वापस 0;
पूर्ण

/**
 * cuse_channel_release - release method क्रम /dev/cuse
 * @inode: inode क्रम /dev/cuse
 * @file: file काष्ठा being बंदd
 *
 * Disconnect the channel, deरेजिस्टर CUSE device and initiate
 * deकाष्ठाion by putting the शेष reference.
 *
 * RETURNS:
 * 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक cuse_channel_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा fuse_dev *fud = file->निजी_data;
	काष्ठा cuse_conn *cc = fc_to_cc(fud->fc);
	पूर्णांक rc;

	/* हटाओ from the conntbl, no more access from this poपूर्णांक on */
	mutex_lock(&cuse_lock);
	list_del_init(&cc->list);
	mutex_unlock(&cuse_lock);

	/* हटाओ device */
	अगर (cc->dev)
		device_unरेजिस्टर(cc->dev);
	अगर (cc->cdev) अणु
		unरेजिस्टर_chrdev_region(cc->cdev->dev, 1);
		cdev_del(cc->cdev);
	पूर्ण

	rc = fuse_dev_release(inode, file);	/* माला_दो the base reference */

	वापस rc;
पूर्ण

अटल काष्ठा file_operations cuse_channel_fops; /* initialized during init */


/**************************************************************************
 * Misc stuff and module initializatiion
 *
 * CUSE exports the same set of attributes to sysfs as fusectl.
 */

अटल sमाप_प्रकार cuse_class_रुकोing_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cuse_conn *cc = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", atomic_पढ़ो(&cc->fc.num_रुकोing));
पूर्ण
अटल DEVICE_ATTR(रुकोing, 0400, cuse_class_रुकोing_show, शून्य);

अटल sमाप_प्रकार cuse_class_पात_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cuse_conn *cc = dev_get_drvdata(dev);

	fuse_पात_conn(&cc->fc);
	वापस count;
पूर्ण
अटल DEVICE_ATTR(पात, 0200, शून्य, cuse_class_पात_store);

अटल काष्ठा attribute *cuse_class_dev_attrs[] = अणु
	&dev_attr_रुकोing.attr,
	&dev_attr_पात.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(cuse_class_dev);

अटल काष्ठा miscdevice cuse_miscdev = अणु
	.minor		= CUSE_MINOR,
	.name		= "cuse",
	.fops		= &cuse_channel_fops,
पूर्ण;

MODULE_ALIAS_MISCDEV(CUSE_MINOR);
MODULE_ALIAS("devname:cuse");

अटल पूर्णांक __init cuse_init(व्योम)
अणु
	पूर्णांक i, rc;

	/* init conntbl */
	क्रम (i = 0; i < CUSE_CONNTBL_LEN; i++)
		INIT_LIST_HEAD(&cuse_conntbl[i]);

	/* inherit and extend fuse_dev_operations */
	cuse_channel_fops		= fuse_dev_operations;
	cuse_channel_fops.owner		= THIS_MODULE;
	cuse_channel_fops.खोलो		= cuse_channel_खोलो;
	cuse_channel_fops.release	= cuse_channel_release;
	/* CUSE is not prepared क्रम FUSE_DEV_IOC_CLONE */
	cuse_channel_fops.unlocked_ioctl	= शून्य;

	cuse_class = class_create(THIS_MODULE, "cuse");
	अगर (IS_ERR(cuse_class))
		वापस PTR_ERR(cuse_class);

	cuse_class->dev_groups = cuse_class_dev_groups;

	rc = misc_रेजिस्टर(&cuse_miscdev);
	अगर (rc) अणु
		class_destroy(cuse_class);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास cuse_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&cuse_miscdev);
	class_destroy(cuse_class);
पूर्ण

module_init(cuse_init);
module_निकास(cuse_निकास);

MODULE_AUTHOR("Tejun Heo <tj@kernel.org>");
MODULE_DESCRIPTION("Character device in Userspace");
MODULE_LICENSE("GPL");
