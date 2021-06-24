<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    HMC Drive CD/DVD Device
 *
 *    Copyright IBM Corp. 2013
 *    Author(s): Ralf Hoppe (rhoppe@de.ibm.com)
 *
 *    This file provides a Linux "misc" अक्षरacter device क्रम access to an
 *    asचिन्हित HMC drive CD/DVD-ROM. It works as follows: First create the
 *    device by calling hmcdrv_dev_init(). After खोलो() a lseek(fd, 0,
 *    अंत_से) indicates that a new FTP command follows (not needed on the
 *    first command after खोलो). Then ग_लिखो() the FTP command ASCII string
 *    to it, e.g. "dir /" or "nls <directory>" or "get <filename>". At the
 *    end पढ़ो() the response.
 */

#घोषणा KMSG_COMPONENT "hmcdrv"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/cdev.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/device.h>
#समावेश <linux/capability.h>
#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>

#समावेश "hmcdrv_dev.h"
#समावेश "hmcdrv_ftp.h"

/* If the following macro is defined, then the HMC device creates it's own
 * separated device class (and dynamically assigns a major number). If not
 * defined then the HMC device is asचिन्हित to the "misc" class devices.
 *
#घोषणा HMCDRV_DEV_CLASS "hmcftp"
 */

#घोषणा HMCDRV_DEV_NAME  "hmcdrv"
#घोषणा HMCDRV_DEV_BUSY_DELAY	 500 /* delay between -EBUSY trials in ms */
#घोषणा HMCDRV_DEV_BUSY_RETRIES  3   /* number of retries on -EBUSY */

काष्ठा hmcdrv_dev_node अणु

#अगर_घोषित HMCDRV_DEV_CLASS
	काष्ठा cdev dev; /* अक्षरacter device काष्ठाure */
	umode_t mode;	 /* mode of device node (unused, zero) */
#अन्यथा
	काष्ठा miscdevice dev; /* "misc" device काष्ठाure */
#पूर्ण_अगर

पूर्ण;

अटल पूर्णांक hmcdrv_dev_खोलो(काष्ठा inode *inode, काष्ठा file *fp);
अटल पूर्णांक hmcdrv_dev_release(काष्ठा inode *inode, काष्ठा file *fp);
अटल loff_t hmcdrv_dev_seek(काष्ठा file *fp, loff_t pos, पूर्णांक whence);
अटल sमाप_प्रकार hmcdrv_dev_पढ़ो(काष्ठा file *fp, अक्षर __user *ubuf,
			       माप_प्रकार len, loff_t *pos);
अटल sमाप_प्रकार hmcdrv_dev_ग_लिखो(काष्ठा file *fp, स्थिर अक्षर __user *ubuf,
				माप_प्रकार len, loff_t *pos);
अटल sमाप_प्रकार hmcdrv_dev_transfer(अक्षर __kernel *cmd, loff_t offset,
				   अक्षर __user *buf, माप_प्रकार len);

/*
 * device operations
 */
अटल स्थिर काष्ठा file_operations hmcdrv_dev_fops = अणु
	.खोलो = hmcdrv_dev_खोलो,
	.llseek = hmcdrv_dev_seek,
	.release = hmcdrv_dev_release,
	.पढ़ो = hmcdrv_dev_पढ़ो,
	.ग_लिखो = hmcdrv_dev_ग_लिखो,
पूर्ण;

अटल काष्ठा hmcdrv_dev_node hmcdrv_dev; /* HMC device काष्ठा (अटल) */

#अगर_घोषित HMCDRV_DEV_CLASS

अटल काष्ठा class *hmcdrv_dev_class; /* device class poपूर्णांकer */
अटल dev_t hmcdrv_dev_no; /* device number (major/minor) */

/**
 * hmcdrv_dev_name() - provides a naming hपूर्णांक क्रम a device node in /dev
 * @dev: device क्रम which the naming/mode hपूर्णांक is
 * @mode: file mode क्रम device node created in /dev
 *
 * See: devपंचांगpfs.c, function devपंचांगpfs_create_node()
 *
 * Return: recommended device file name in /dev
 */
अटल अक्षर *hmcdrv_dev_name(काष्ठा device *dev, umode_t *mode)
अणु
	अक्षर *nodename = शून्य;
	स्थिर अक्षर *devname = dev_name(dev); /* kernel device name */

	अगर (devname)
		nodename = kaप्र_लिखो(GFP_KERNEL, "%s", devname);

	/* on device destroy (rmmod) the mode poपूर्णांकer may be शून्य
	 */
	अगर (mode)
		*mode = hmcdrv_dev.mode;

	वापस nodename;
पूर्ण

#पूर्ण_अगर	/* HMCDRV_DEV_CLASS */

/*
 * खोलो()
 */
अटल पूर्णांक hmcdrv_dev_खोलो(काष्ठा inode *inode, काष्ठा file *fp)
अणु
	पूर्णांक rc;

	/* check क्रम non-blocking access, which is really unsupported
	 */
	अगर (fp->f_flags & O_NONBLOCK)
		वापस -EINVAL;

	/* Because it makes no sense to खोलो this device पढ़ो-only (then a
	 * FTP command cannot be emitted), we respond with an error.
	 */
	अगर ((fp->f_flags & O_ACCMODE) == O_RDONLY)
		वापस -EINVAL;

	/* prevent unloading this module as दीर्घ as anyone holds the
	 * device file खोलो - so increment the reference count here
	 */
	अगर (!try_module_get(THIS_MODULE))
		वापस -ENODEV;

	fp->निजी_data = शून्य; /* no command yet */
	rc = hmcdrv_ftp_startup();
	अगर (rc)
		module_put(THIS_MODULE);

	pr_debug("open file '/dev/%pD' with return code %d\n", fp, rc);
	वापस rc;
पूर्ण

/*
 * release()
 */
अटल पूर्णांक hmcdrv_dev_release(काष्ठा inode *inode, काष्ठा file *fp)
अणु
	pr_debug("closing file '/dev/%pD'\n", fp);
	kमुक्त(fp->निजी_data);
	fp->निजी_data = शून्य;
	hmcdrv_ftp_shutकरोwn();
	module_put(THIS_MODULE);
	वापस 0;
पूर्ण

/*
 * lseek()
 */
अटल loff_t hmcdrv_dev_seek(काष्ठा file *fp, loff_t pos, पूर्णांक whence)
अणु
	चयन (whence) अणु
	हाल प्रस्तुत_से: /* relative to current file position */
		pos += fp->f_pos; /* new position stored in 'pos' */
		अवरोध;

	हाल शुरू_से: /* असलolute (relative to beginning of file) */
		अवरोध; /* शुरू_से */

		/* We use अंत_से as a special indicator क्रम a शुरू_से
		 * (set असलolute position), combined with a FTP command
		 * clear.
		 */
	हाल अंत_से:
		अगर (fp->निजी_data) अणु
			kमुक्त(fp->निजी_data);
			fp->निजी_data = शून्य;
		पूर्ण

		अवरोध; /* अंत_से */

	शेष: /* SEEK_DATA, SEEK_HOLE: unsupported */
		वापस -EINVAL;
	पूर्ण

	अगर (pos < 0)
		वापस -EINVAL;

	अगर (fp->f_pos != pos)
		++fp->f_version;

	fp->f_pos = pos;
	वापस pos;
पूर्ण

/*
 * transfer (helper function)
 */
अटल sमाप_प्रकार hmcdrv_dev_transfer(अक्षर __kernel *cmd, loff_t offset,
				   अक्षर __user *buf, माप_प्रकार len)
अणु
	sमाप_प्रकार retlen;
	अचिन्हित trials = HMCDRV_DEV_BUSY_RETRIES;

	करो अणु
		retlen = hmcdrv_ftp_cmd(cmd, offset, buf, len);

		अगर (retlen != -EBUSY)
			अवरोध;

		msleep(HMCDRV_DEV_BUSY_DELAY);

	पूर्ण जबतक (--trials > 0);

	वापस retlen;
पूर्ण

/*
 * पढ़ो()
 */
अटल sमाप_प्रकार hmcdrv_dev_पढ़ो(काष्ठा file *fp, अक्षर __user *ubuf,
			       माप_प्रकार len, loff_t *pos)
अणु
	sमाप_प्रकार retlen;

	अगर (((fp->f_flags & O_ACCMODE) == O_WRONLY) ||
	    (fp->निजी_data == शून्य)) अणु /* no FTP cmd defined ? */
		वापस -EBADF;
	पूर्ण

	retlen = hmcdrv_dev_transfer((अक्षर *) fp->निजी_data,
				     *pos, ubuf, len);

	pr_debug("read from file '/dev/%pD' at %lld returns %zd/%zu\n",
		 fp, (दीर्घ दीर्घ) *pos, retlen, len);

	अगर (retlen > 0)
		*pos += retlen;

	वापस retlen;
पूर्ण

/*
 * ग_लिखो()
 */
अटल sमाप_प्रकार hmcdrv_dev_ग_लिखो(काष्ठा file *fp, स्थिर अक्षर __user *ubuf,
				माप_प्रकार len, loff_t *pos)
अणु
	sमाप_प्रकार retlen;

	pr_debug("writing file '/dev/%pD' at pos. %lld with length %zd\n",
		 fp, (दीर्घ दीर्घ) *pos, len);

	अगर (!fp->निजी_data) अणु /* first expect a cmd ग_लिखो */
		fp->निजी_data = kदो_स्मृति(len + 1, GFP_KERNEL);

		अगर (!fp->निजी_data)
			वापस -ENOMEM;

		अगर (!copy_from_user(fp->निजी_data, ubuf, len)) अणु
			((अक्षर *)fp->निजी_data)[len] = '\0';
			वापस len;
		पूर्ण

		kमुक्त(fp->निजी_data);
		fp->निजी_data = शून्य;
		वापस -EFAULT;
	पूर्ण

	retlen = hmcdrv_dev_transfer((अक्षर *) fp->निजी_data,
				     *pos, (अक्षर __user *) ubuf, len);
	अगर (retlen > 0)
		*pos += retlen;

	pr_debug("write to file '/dev/%pD' returned %zd\n", fp, retlen);

	वापस retlen;
पूर्ण

/**
 * hmcdrv_dev_init() - creates a HMC drive CD/DVD device
 *
 * This function creates a HMC drive CD/DVD kernel device and an associated
 * device under /dev, using a dynamically allocated major number.
 *
 * Return: 0 on success, अन्यथा an error code.
 */
पूर्णांक hmcdrv_dev_init(व्योम)
अणु
	पूर्णांक rc;

#अगर_घोषित HMCDRV_DEV_CLASS
	काष्ठा device *dev;

	rc = alloc_chrdev_region(&hmcdrv_dev_no, 0, 1, HMCDRV_DEV_NAME);

	अगर (rc)
		जाओ out_err;

	cdev_init(&hmcdrv_dev.dev, &hmcdrv_dev_fops);
	hmcdrv_dev.dev.owner = THIS_MODULE;
	rc = cdev_add(&hmcdrv_dev.dev, hmcdrv_dev_no, 1);

	अगर (rc)
		जाओ out_unreg;

	/* At this poपूर्णांक the अक्षरacter device exists in the kernel (see
	 * /proc/devices), but not under /dev nor /sys/devices/भव. So
	 * we have to create an associated class (see /sys/class).
	 */
	hmcdrv_dev_class = class_create(THIS_MODULE, HMCDRV_DEV_CLASS);

	अगर (IS_ERR(hmcdrv_dev_class)) अणु
		rc = PTR_ERR(hmcdrv_dev_class);
		जाओ out_devdel;
	पूर्ण

	/* Finally a device node in /dev has to be established (as 'mkdev'
	 * करोes from the command line). Notice that assignment of a device
	 * node name/mode function is optional (only क्रम mode != 0600).
	 */
	hmcdrv_dev.mode = 0; /* "unset" */
	hmcdrv_dev_class->devnode = hmcdrv_dev_name;

	dev = device_create(hmcdrv_dev_class, शून्य, hmcdrv_dev_no, शून्य,
			    "%s", HMCDRV_DEV_NAME);
	अगर (!IS_ERR(dev))
		वापस 0;

	rc = PTR_ERR(dev);
	class_destroy(hmcdrv_dev_class);
	hmcdrv_dev_class = शून्य;

out_devdel:
	cdev_del(&hmcdrv_dev.dev);

out_unreg:
	unरेजिस्टर_chrdev_region(hmcdrv_dev_no, 1);

out_err:

#अन्यथा  /* !HMCDRV_DEV_CLASS */
	hmcdrv_dev.dev.minor = MISC_DYNAMIC_MINOR;
	hmcdrv_dev.dev.name = HMCDRV_DEV_NAME;
	hmcdrv_dev.dev.fops = &hmcdrv_dev_fops;
	hmcdrv_dev.dev.mode = 0; /* finally produces 0600 */
	rc = misc_रेजिस्टर(&hmcdrv_dev.dev);
#पूर्ण_अगर	/* HMCDRV_DEV_CLASS */

	वापस rc;
पूर्ण

/**
 * hmcdrv_dev_निकास() - destroys a HMC drive CD/DVD device
 */
व्योम hmcdrv_dev_निकास(व्योम)
अणु
#अगर_घोषित HMCDRV_DEV_CLASS
	अगर (!IS_ERR_OR_शून्य(hmcdrv_dev_class)) अणु
		device_destroy(hmcdrv_dev_class, hmcdrv_dev_no);
		class_destroy(hmcdrv_dev_class);
	पूर्ण

	cdev_del(&hmcdrv_dev.dev);
	unरेजिस्टर_chrdev_region(hmcdrv_dev_no, 1);
#अन्यथा  /* !HMCDRV_DEV_CLASS */
	misc_deरेजिस्टर(&hmcdrv_dev.dev);
#पूर्ण_अगर	/* HMCDRV_DEV_CLASS */
पूर्ण
