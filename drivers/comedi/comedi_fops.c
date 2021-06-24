<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/comedi_fops.c
 * comedi kernel module
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-2007 David A. Schleef <ds@schleef.org>
 * compat ioctls:
 * Author: Ian Abbott, MEV Ltd. <abbotti@mev.co.uk>
 * Copyright (C) 2007 MEV Ltd. <http://www.mev.co.uk/>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/delay.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश "comedidev.h"
#समावेश <linux/cdev.h>

#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/compat.h>

#समावेश "comedi_internal.h"

/*
 * comedi_subdevice "runflags"
 * COMEDI_SRF_RT:		DEPRECATED: command is running real-समय
 * COMEDI_SRF_ERROR:		indicates an COMEDI_CB_ERROR event has occurred
 *				since the last command was started
 * COMEDI_SRF_RUNNING:		command is running
 * COMEDI_SRF_FREE_SPRIV:	मुक्त s->निजी on detach
 *
 * COMEDI_SRF_BUSY_MASK:	runflags that indicate the subdevice is "busy"
 */
#घोषणा COMEDI_SRF_RT		BIT(1)
#घोषणा COMEDI_SRF_ERROR	BIT(2)
#घोषणा COMEDI_SRF_RUNNING	BIT(27)
#घोषणा COMEDI_SRF_FREE_SPRIV	BIT(31)

#घोषणा COMEDI_SRF_BUSY_MASK	(COMEDI_SRF_ERROR | COMEDI_SRF_RUNNING)

/**
 * काष्ठा comedi_file - Per-file निजी data क्रम COMEDI device
 * @dev: COMEDI device.
 * @पढ़ो_subdev: Current "read" subdevice.
 * @ग_लिखो_subdev: Current "write" subdevice.
 * @last_detach_count: Last known detach count.
 * @last_attached: Last known attached/detached state.
 */
काष्ठा comedi_file अणु
	काष्ठा comedi_device *dev;
	काष्ठा comedi_subdevice *पढ़ो_subdev;
	काष्ठा comedi_subdevice *ग_लिखो_subdev;
	अचिन्हित पूर्णांक last_detach_count;
	अचिन्हित पूर्णांक last_attached:1;
पूर्ण;

#घोषणा COMEDI_NUM_MINORS 0x100
#घोषणा COMEDI_NUM_SUBDEVICE_MINORS	\
	(COMEDI_NUM_MINORS - COMEDI_NUM_BOARD_MINORS)

अटल अचिन्हित लघु comedi_num_legacy_minors;
module_param(comedi_num_legacy_minors, uलघु, 0444);
MODULE_PARM_DESC(comedi_num_legacy_minors,
		 "number of comedi minor devices to reserve for non-auto-configured devices (default 0)"
		);

अचिन्हित पूर्णांक comedi_शेष_buf_size_kb = CONFIG_COMEDI_DEFAULT_BUF_SIZE_KB;
module_param(comedi_शेष_buf_size_kb, uपूर्णांक, 0644);
MODULE_PARM_DESC(comedi_शेष_buf_size_kb,
		 "default asynchronous buffer size in KiB (default "
		 __MODULE_STRING(CONFIG_COMEDI_DEFAULT_BUF_SIZE_KB) ")");

अचिन्हित पूर्णांक comedi_शेष_buf_maxsize_kb =
	CONFIG_COMEDI_DEFAULT_BUF_MAXSIZE_KB;
module_param(comedi_शेष_buf_maxsize_kb, uपूर्णांक, 0644);
MODULE_PARM_DESC(comedi_शेष_buf_maxsize_kb,
		 "default maximum size of asynchronous buffer in KiB (default "
		 __MODULE_STRING(CONFIG_COMEDI_DEFAULT_BUF_MAXSIZE_KB) ")");

अटल DEFINE_MUTEX(comedi_board_minor_table_lock);
अटल काष्ठा comedi_device
*comedi_board_minor_table[COMEDI_NUM_BOARD_MINORS];

अटल DEFINE_MUTEX(comedi_subdevice_minor_table_lock);
/* Note: indexed by minor - COMEDI_NUM_BOARD_MINORS. */
अटल काष्ठा comedi_subdevice
*comedi_subdevice_minor_table[COMEDI_NUM_SUBDEVICE_MINORS];

अटल काष्ठा class *comedi_class;
अटल काष्ठा cdev comedi_cdev;

अटल व्योम comedi_device_init(काष्ठा comedi_device *dev)
अणु
	kref_init(&dev->refcount);
	spin_lock_init(&dev->spinlock);
	mutex_init(&dev->mutex);
	init_rwsem(&dev->attach_lock);
	dev->minor = -1;
पूर्ण

अटल व्योम comedi_dev_kref_release(काष्ठा kref *kref)
अणु
	काष्ठा comedi_device *dev =
		container_of(kref, काष्ठा comedi_device, refcount);

	mutex_destroy(&dev->mutex);
	put_device(dev->class_dev);
	kमुक्त(dev);
पूर्ण

/**
 * comedi_dev_put() - Release a use of a COMEDI device
 * @dev: COMEDI device.
 *
 * Must be called when a user of a COMEDI device is finished with it.
 * When the last user of the COMEDI device calls this function, the
 * COMEDI device is destroyed.
 *
 * Return: 1 अगर the COMEDI device is destroyed by this call or @dev is
 * शून्य, otherwise वापस 0.  Callers must not assume the COMEDI
 * device is still valid अगर this function वापसs 0.
 */
पूर्णांक comedi_dev_put(काष्ठा comedi_device *dev)
अणु
	अगर (dev)
		वापस kref_put(&dev->refcount, comedi_dev_kref_release);
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_dev_put);

अटल काष्ठा comedi_device *comedi_dev_get(काष्ठा comedi_device *dev)
अणु
	अगर (dev)
		kref_get(&dev->refcount);
	वापस dev;
पूर्ण

अटल व्योम comedi_device_cleanup(काष्ठा comedi_device *dev)
अणु
	काष्ठा module *driver_module = शून्य;

	अगर (!dev)
		वापस;
	mutex_lock(&dev->mutex);
	अगर (dev->attached)
		driver_module = dev->driver->module;
	comedi_device_detach(dev);
	अगर (driver_module && dev->use_count)
		module_put(driver_module);
	mutex_unlock(&dev->mutex);
पूर्ण

अटल bool comedi_clear_board_dev(काष्ठा comedi_device *dev)
अणु
	अचिन्हित पूर्णांक i = dev->minor;
	bool cleared = false;

	lockdep_निश्चित_held(&dev->mutex);
	mutex_lock(&comedi_board_minor_table_lock);
	अगर (dev == comedi_board_minor_table[i]) अणु
		comedi_board_minor_table[i] = शून्य;
		cleared = true;
	पूर्ण
	mutex_unlock(&comedi_board_minor_table_lock);
	वापस cleared;
पूर्ण

अटल काष्ठा comedi_device *comedi_clear_board_minor(अचिन्हित पूर्णांक minor)
अणु
	काष्ठा comedi_device *dev;

	mutex_lock(&comedi_board_minor_table_lock);
	dev = comedi_board_minor_table[minor];
	comedi_board_minor_table[minor] = शून्य;
	mutex_unlock(&comedi_board_minor_table_lock);
	वापस dev;
पूर्ण

अटल व्योम comedi_मुक्त_board_dev(काष्ठा comedi_device *dev)
अणु
	अगर (dev) अणु
		comedi_device_cleanup(dev);
		अगर (dev->class_dev) अणु
			device_destroy(comedi_class,
				       MKDEV(COMEDI_MAJOR, dev->minor));
		पूर्ण
		comedi_dev_put(dev);
	पूर्ण
पूर्ण

अटल काष्ठा comedi_subdevice *
comedi_subdevice_from_minor(स्थिर काष्ठा comedi_device *dev, अचिन्हित पूर्णांक minor)
अणु
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक i = minor - COMEDI_NUM_BOARD_MINORS;

	mutex_lock(&comedi_subdevice_minor_table_lock);
	s = comedi_subdevice_minor_table[i];
	अगर (s && s->device != dev)
		s = शून्य;
	mutex_unlock(&comedi_subdevice_minor_table_lock);
	वापस s;
पूर्ण

अटल काष्ठा comedi_device *comedi_dev_get_from_board_minor(अचिन्हित पूर्णांक minor)
अणु
	काष्ठा comedi_device *dev;

	mutex_lock(&comedi_board_minor_table_lock);
	dev = comedi_dev_get(comedi_board_minor_table[minor]);
	mutex_unlock(&comedi_board_minor_table_lock);
	वापस dev;
पूर्ण

अटल काष्ठा comedi_device *
comedi_dev_get_from_subdevice_minor(अचिन्हित पूर्णांक minor)
अणु
	काष्ठा comedi_device *dev;
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक i = minor - COMEDI_NUM_BOARD_MINORS;

	mutex_lock(&comedi_subdevice_minor_table_lock);
	s = comedi_subdevice_minor_table[i];
	dev = comedi_dev_get(s ? s->device : शून्य);
	mutex_unlock(&comedi_subdevice_minor_table_lock);
	वापस dev;
पूर्ण

/**
 * comedi_dev_get_from_minor() - Get COMEDI device by minor device number
 * @minor: Minor device number.
 *
 * Finds the COMEDI device associated with the minor device number, अगर any,
 * and increments its reference count.  The COMEDI device is prevented from
 * being मुक्तd until a matching call is made to comedi_dev_put().
 *
 * Return: A poपूर्णांकer to the COMEDI device अगर it exists, with its usage
 * reference incremented.  Return शून्य अगर no COMEDI device exists with the
 * specअगरied minor device number.
 */
काष्ठा comedi_device *comedi_dev_get_from_minor(अचिन्हित पूर्णांक minor)
अणु
	अगर (minor < COMEDI_NUM_BOARD_MINORS)
		वापस comedi_dev_get_from_board_minor(minor);

	वापस comedi_dev_get_from_subdevice_minor(minor);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_dev_get_from_minor);

अटल काष्ठा comedi_subdevice *
comedi_पढ़ो_subdevice(स्थिर काष्ठा comedi_device *dev, अचिन्हित पूर्णांक minor)
अणु
	काष्ठा comedi_subdevice *s;

	lockdep_निश्चित_held(&dev->mutex);
	अगर (minor >= COMEDI_NUM_BOARD_MINORS) अणु
		s = comedi_subdevice_from_minor(dev, minor);
		अगर (!s || (s->subdev_flags & SDF_CMD_READ))
			वापस s;
	पूर्ण
	वापस dev->पढ़ो_subdev;
पूर्ण

अटल काष्ठा comedi_subdevice *
comedi_ग_लिखो_subdevice(स्थिर काष्ठा comedi_device *dev, अचिन्हित पूर्णांक minor)
अणु
	काष्ठा comedi_subdevice *s;

	lockdep_निश्चित_held(&dev->mutex);
	अगर (minor >= COMEDI_NUM_BOARD_MINORS) अणु
		s = comedi_subdevice_from_minor(dev, minor);
		अगर (!s || (s->subdev_flags & SDF_CMD_WRITE))
			वापस s;
	पूर्ण
	वापस dev->ग_लिखो_subdev;
पूर्ण

अटल व्योम comedi_file_reset(काष्ठा file *file)
अणु
	काष्ठा comedi_file *cfp = file->निजी_data;
	काष्ठा comedi_device *dev = cfp->dev;
	काष्ठा comedi_subdevice *s, *पढ़ो_s, *ग_लिखो_s;
	अचिन्हित पूर्णांक minor = iminor(file_inode(file));

	पढ़ो_s = dev->पढ़ो_subdev;
	ग_लिखो_s = dev->ग_लिखो_subdev;
	अगर (minor >= COMEDI_NUM_BOARD_MINORS) अणु
		s = comedi_subdevice_from_minor(dev, minor);
		अगर (!s || s->subdev_flags & SDF_CMD_READ)
			पढ़ो_s = s;
		अगर (!s || s->subdev_flags & SDF_CMD_WRITE)
			ग_लिखो_s = s;
	पूर्ण
	cfp->last_attached = dev->attached;
	cfp->last_detach_count = dev->detach_count;
	WRITE_ONCE(cfp->पढ़ो_subdev, पढ़ो_s);
	WRITE_ONCE(cfp->ग_लिखो_subdev, ग_लिखो_s);
पूर्ण

अटल व्योम comedi_file_check(काष्ठा file *file)
अणु
	काष्ठा comedi_file *cfp = file->निजी_data;
	काष्ठा comedi_device *dev = cfp->dev;

	अगर (cfp->last_attached != dev->attached ||
	    cfp->last_detach_count != dev->detach_count)
		comedi_file_reset(file);
पूर्ण

अटल काष्ठा comedi_subdevice *comedi_file_पढ़ो_subdevice(काष्ठा file *file)
अणु
	काष्ठा comedi_file *cfp = file->निजी_data;

	comedi_file_check(file);
	वापस READ_ONCE(cfp->पढ़ो_subdev);
पूर्ण

अटल काष्ठा comedi_subdevice *comedi_file_ग_लिखो_subdevice(काष्ठा file *file)
अणु
	काष्ठा comedi_file *cfp = file->निजी_data;

	comedi_file_check(file);
	वापस READ_ONCE(cfp->ग_लिखो_subdev);
पूर्ण

अटल पूर्णांक resize_async_buffer(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       अचिन्हित पूर्णांक new_size)
अणु
	काष्ठा comedi_async *async = s->async;
	पूर्णांक retval;

	lockdep_निश्चित_held(&dev->mutex);

	अगर (new_size > async->max_bufsize)
		वापस -EPERM;

	अगर (s->busy) अणु
		dev_dbg(dev->class_dev,
			"subdevice is busy, cannot resize buffer\n");
		वापस -EBUSY;
	पूर्ण
	अगर (comedi_buf_is_mmapped(s)) अणु
		dev_dbg(dev->class_dev,
			"subdevice is mmapped, cannot resize buffer\n");
		वापस -EBUSY;
	पूर्ण

	/* make sure buffer is an पूर्णांकegral number of pages (we round up) */
	new_size = (new_size + PAGE_SIZE - 1) & PAGE_MASK;

	retval = comedi_buf_alloc(dev, s, new_size);
	अगर (retval < 0)
		वापस retval;

	अगर (s->buf_change) अणु
		retval = s->buf_change(dev, s);
		अगर (retval < 0)
			वापस retval;
	पूर्ण

	dev_dbg(dev->class_dev, "subd %d buffer resized to %i bytes\n",
		s->index, async->pपुनः_स्मृति_bufsz);
	वापस 0;
पूर्ण

/* sysfs attribute files */

अटल sमाप_प्रकार max_पढ़ो_buffer_kb_show(काष्ठा device *csdev,
				       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित पूर्णांक minor = MINOR(csdev->devt);
	काष्ठा comedi_device *dev;
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक size = 0;

	dev = comedi_dev_get_from_minor(minor);
	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&dev->mutex);
	s = comedi_पढ़ो_subdevice(dev, minor);
	अगर (s && (s->subdev_flags & SDF_CMD_READ) && s->async)
		size = s->async->max_bufsize / 1024;
	mutex_unlock(&dev->mutex);

	comedi_dev_put(dev);
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", size);
पूर्ण

अटल sमाप_प्रकार max_पढ़ो_buffer_kb_store(काष्ठा device *csdev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक minor = MINOR(csdev->devt);
	काष्ठा comedi_device *dev;
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक size;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &size);
	अगर (err)
		वापस err;
	अगर (size > (अच_पूर्णांक_उच्च / 1024))
		वापस -EINVAL;
	size *= 1024;

	dev = comedi_dev_get_from_minor(minor);
	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&dev->mutex);
	s = comedi_पढ़ो_subdevice(dev, minor);
	अगर (s && (s->subdev_flags & SDF_CMD_READ) && s->async)
		s->async->max_bufsize = size;
	अन्यथा
		err = -EINVAL;
	mutex_unlock(&dev->mutex);

	comedi_dev_put(dev);
	वापस err ? err : count;
पूर्ण
अटल DEVICE_ATTR_RW(max_पढ़ो_buffer_kb);

अटल sमाप_प्रकार पढ़ो_buffer_kb_show(काष्ठा device *csdev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित पूर्णांक minor = MINOR(csdev->devt);
	काष्ठा comedi_device *dev;
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक size = 0;

	dev = comedi_dev_get_from_minor(minor);
	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&dev->mutex);
	s = comedi_पढ़ो_subdevice(dev, minor);
	अगर (s && (s->subdev_flags & SDF_CMD_READ) && s->async)
		size = s->async->pपुनः_स्मृति_bufsz / 1024;
	mutex_unlock(&dev->mutex);

	comedi_dev_put(dev);
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", size);
पूर्ण

अटल sमाप_प्रकार पढ़ो_buffer_kb_store(काष्ठा device *csdev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक minor = MINOR(csdev->devt);
	काष्ठा comedi_device *dev;
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक size;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &size);
	अगर (err)
		वापस err;
	अगर (size > (अच_पूर्णांक_उच्च / 1024))
		वापस -EINVAL;
	size *= 1024;

	dev = comedi_dev_get_from_minor(minor);
	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&dev->mutex);
	s = comedi_पढ़ो_subdevice(dev, minor);
	अगर (s && (s->subdev_flags & SDF_CMD_READ) && s->async)
		err = resize_async_buffer(dev, s, size);
	अन्यथा
		err = -EINVAL;
	mutex_unlock(&dev->mutex);

	comedi_dev_put(dev);
	वापस err ? err : count;
पूर्ण
अटल DEVICE_ATTR_RW(पढ़ो_buffer_kb);

अटल sमाप_प्रकार max_ग_लिखो_buffer_kb_show(काष्ठा device *csdev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	अचिन्हित पूर्णांक minor = MINOR(csdev->devt);
	काष्ठा comedi_device *dev;
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक size = 0;

	dev = comedi_dev_get_from_minor(minor);
	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&dev->mutex);
	s = comedi_ग_लिखो_subdevice(dev, minor);
	अगर (s && (s->subdev_flags & SDF_CMD_WRITE) && s->async)
		size = s->async->max_bufsize / 1024;
	mutex_unlock(&dev->mutex);

	comedi_dev_put(dev);
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", size);
पूर्ण

अटल sमाप_प्रकार max_ग_लिखो_buffer_kb_store(काष्ठा device *csdev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक minor = MINOR(csdev->devt);
	काष्ठा comedi_device *dev;
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक size;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &size);
	अगर (err)
		वापस err;
	अगर (size > (अच_पूर्णांक_उच्च / 1024))
		वापस -EINVAL;
	size *= 1024;

	dev = comedi_dev_get_from_minor(minor);
	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&dev->mutex);
	s = comedi_ग_लिखो_subdevice(dev, minor);
	अगर (s && (s->subdev_flags & SDF_CMD_WRITE) && s->async)
		s->async->max_bufsize = size;
	अन्यथा
		err = -EINVAL;
	mutex_unlock(&dev->mutex);

	comedi_dev_put(dev);
	वापस err ? err : count;
पूर्ण
अटल DEVICE_ATTR_RW(max_ग_लिखो_buffer_kb);

अटल sमाप_प्रकार ग_लिखो_buffer_kb_show(काष्ठा device *csdev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित पूर्णांक minor = MINOR(csdev->devt);
	काष्ठा comedi_device *dev;
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक size = 0;

	dev = comedi_dev_get_from_minor(minor);
	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&dev->mutex);
	s = comedi_ग_लिखो_subdevice(dev, minor);
	अगर (s && (s->subdev_flags & SDF_CMD_WRITE) && s->async)
		size = s->async->pपुनः_स्मृति_bufsz / 1024;
	mutex_unlock(&dev->mutex);

	comedi_dev_put(dev);
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", size);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_buffer_kb_store(काष्ठा device *csdev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक minor = MINOR(csdev->devt);
	काष्ठा comedi_device *dev;
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक size;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &size);
	अगर (err)
		वापस err;
	अगर (size > (अच_पूर्णांक_उच्च / 1024))
		वापस -EINVAL;
	size *= 1024;

	dev = comedi_dev_get_from_minor(minor);
	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&dev->mutex);
	s = comedi_ग_लिखो_subdevice(dev, minor);
	अगर (s && (s->subdev_flags & SDF_CMD_WRITE) && s->async)
		err = resize_async_buffer(dev, s, size);
	अन्यथा
		err = -EINVAL;
	mutex_unlock(&dev->mutex);

	comedi_dev_put(dev);
	वापस err ? err : count;
पूर्ण
अटल DEVICE_ATTR_RW(ग_लिखो_buffer_kb);

अटल काष्ठा attribute *comedi_dev_attrs[] = अणु
	&dev_attr_max_पढ़ो_buffer_kb.attr,
	&dev_attr_पढ़ो_buffer_kb.attr,
	&dev_attr_max_ग_लिखो_buffer_kb.attr,
	&dev_attr_ग_लिखो_buffer_kb.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(comedi_dev);

अटल व्योम __comedi_clear_subdevice_runflags(काष्ठा comedi_subdevice *s,
					      अचिन्हित पूर्णांक bits)
अणु
	s->runflags &= ~bits;
पूर्ण

अटल व्योम __comedi_set_subdevice_runflags(काष्ठा comedi_subdevice *s,
					    अचिन्हित पूर्णांक bits)
अणु
	s->runflags |= bits;
पूर्ण

अटल व्योम comedi_update_subdevice_runflags(काष्ठा comedi_subdevice *s,
					     अचिन्हित पूर्णांक mask,
					     अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->spin_lock, flags);
	__comedi_clear_subdevice_runflags(s, mask);
	__comedi_set_subdevice_runflags(s, bits & mask);
	spin_unlock_irqrestore(&s->spin_lock, flags);
पूर्ण

अटल अचिन्हित पूर्णांक __comedi_get_subdevice_runflags(काष्ठा comedi_subdevice *s)
अणु
	वापस s->runflags;
पूर्ण

अटल अचिन्हित पूर्णांक comedi_get_subdevice_runflags(काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक runflags;

	spin_lock_irqsave(&s->spin_lock, flags);
	runflags = __comedi_get_subdevice_runflags(s);
	spin_unlock_irqrestore(&s->spin_lock, flags);
	वापस runflags;
पूर्ण

अटल bool comedi_is_runflags_running(अचिन्हित पूर्णांक runflags)
अणु
	वापस runflags & COMEDI_SRF_RUNNING;
पूर्ण

अटल bool comedi_is_runflags_in_error(अचिन्हित पूर्णांक runflags)
अणु
	वापस runflags & COMEDI_SRF_ERROR;
पूर्ण

/**
 * comedi_is_subdevice_running() - Check अगर async command running on subdevice
 * @s: COMEDI subdevice.
 *
 * Return: %true अगर an asynchronous COMEDI command is active on the
 * subdevice, अन्यथा %false.
 */
bool comedi_is_subdevice_running(काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित पूर्णांक runflags = comedi_get_subdevice_runflags(s);

	वापस comedi_is_runflags_running(runflags);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_is_subdevice_running);

अटल bool __comedi_is_subdevice_running(काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित पूर्णांक runflags = __comedi_get_subdevice_runflags(s);

	वापस comedi_is_runflags_running(runflags);
पूर्ण

bool comedi_can_स्वतः_मुक्त_spriv(काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित पूर्णांक runflags = __comedi_get_subdevice_runflags(s);

	वापस runflags & COMEDI_SRF_FREE_SPRIV;
पूर्ण

/**
 * comedi_set_spriv_स्वतः_मुक्त() - Mark subdevice निजी data as मुक्तable
 * @s: COMEDI subdevice.
 *
 * Mark the subdevice as having a poपूर्णांकer to निजी data that can be
 * स्वतःmatically मुक्तd when the COMEDI device is detached from the low-level
 * driver.
 */
व्योम comedi_set_spriv_स्वतः_मुक्त(काष्ठा comedi_subdevice *s)
अणु
	__comedi_set_subdevice_runflags(s, COMEDI_SRF_FREE_SPRIV);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_set_spriv_स्वतः_मुक्त);

/**
 * comedi_alloc_spriv - Allocate memory क्रम the subdevice निजी data
 * @s: COMEDI subdevice.
 * @size: Size of the memory to allocate.
 *
 * Allocate memory क्रम the subdevice निजी data and poपूर्णांक @s->निजी
 * to it.  The memory will be मुक्तd स्वतःmatically when the COMEDI device
 * is detached from the low-level driver.
 *
 * Return: A poपूर्णांकer to the allocated memory @s->निजी on success.
 * Return शून्य on failure.
 */
व्योम *comedi_alloc_spriv(काष्ठा comedi_subdevice *s, माप_प्रकार size)
अणु
	s->निजी = kzalloc(size, GFP_KERNEL);
	अगर (s->निजी)
		comedi_set_spriv_स्वतः_मुक्त(s);
	वापस s->निजी;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_alloc_spriv);

/*
 * This function restores a subdevice to an idle state.
 */
अटल व्योम करो_become_nonbusy(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_async *async = s->async;

	lockdep_निश्चित_held(&dev->mutex);
	comedi_update_subdevice_runflags(s, COMEDI_SRF_RUNNING, 0);
	अगर (async) अणु
		comedi_buf_reset(s);
		async->पूर्णांकtrig = शून्य;
		kमुक्त(async->cmd.chanlist);
		async->cmd.chanlist = शून्य;
		s->busy = शून्य;
		wake_up_पूर्णांकerruptible_all(&async->रुको_head);
	पूर्ण अन्यथा अणु
		dev_err(dev->class_dev,
			"BUG: (?) %s called with async=NULL\n", __func__);
		s->busy = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक करो_cancel(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&dev->mutex);
	अगर (comedi_is_subdevice_running(s) && s->cancel)
		ret = s->cancel(dev, s);

	करो_become_nonbusy(dev, s);

	वापस ret;
पूर्ण

व्योम comedi_device_cancel_all(काष्ठा comedi_device *dev)
अणु
	काष्ठा comedi_subdevice *s;
	पूर्णांक i;

	lockdep_निश्चित_held(&dev->mutex);
	अगर (!dev->attached)
		वापस;

	क्रम (i = 0; i < dev->n_subdevices; i++) अणु
		s = &dev->subdevices[i];
		अगर (s->async)
			करो_cancel(dev, s);
	पूर्ण
पूर्ण

अटल पूर्णांक is_device_busy(काष्ठा comedi_device *dev)
अणु
	काष्ठा comedi_subdevice *s;
	पूर्णांक i;

	lockdep_निश्चित_held(&dev->mutex);
	अगर (!dev->attached)
		वापस 0;

	क्रम (i = 0; i < dev->n_subdevices; i++) अणु
		s = &dev->subdevices[i];
		अगर (s->busy)
			वापस 1;
		अगर (s->async && comedi_buf_is_mmapped(s))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * COMEDI_DEVCONFIG ioctl
 * attaches (and configures) or detaches a legacy device
 *
 * arg:
 *	poपूर्णांकer to comedi_devconfig काष्ठाure (शून्य अगर detaching)
 *
 * पढ़ोs:
 *	comedi_devconfig काष्ठाure (अगर attaching)
 *
 * ग_लिखोs:
 *	nothing
 */
अटल पूर्णांक करो_devconfig_ioctl(काष्ठा comedi_device *dev,
			      काष्ठा comedi_devconfig __user *arg)
अणु
	काष्ठा comedi_devconfig it;

	lockdep_निश्चित_held(&dev->mutex);
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (!arg) अणु
		अगर (is_device_busy(dev))
			वापस -EBUSY;
		अगर (dev->attached) अणु
			काष्ठा module *driver_module = dev->driver->module;

			comedi_device_detach(dev);
			module_put(driver_module);
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (copy_from_user(&it, arg, माप(it)))
		वापस -EFAULT;

	it.board_name[COMEDI_NAMELEN - 1] = 0;

	अगर (it.options[COMEDI_DEVCONF_AUX_DATA_LENGTH]) अणु
		dev_warn(dev->class_dev,
			 "comedi_config --init_data is deprecated\n");
		वापस -EINVAL;
	पूर्ण

	अगर (dev->minor >= comedi_num_legacy_minors)
		/* करोn't re-use dynamically allocated comedi devices */
		वापस -EBUSY;

	/* This increments the driver module count on success. */
	वापस comedi_device_attach(dev, &it);
पूर्ण

/*
 * COMEDI_BUFCONFIG ioctl
 * buffer configuration
 *
 * arg:
 *	poपूर्णांकer to comedi_bufconfig काष्ठाure
 *
 * पढ़ोs:
 *	comedi_bufconfig काष्ठाure
 *
 * ग_लिखोs:
 *	modअगरied comedi_bufconfig काष्ठाure
 */
अटल पूर्णांक करो_bufconfig_ioctl(काष्ठा comedi_device *dev,
			      काष्ठा comedi_bufconfig __user *arg)
अणु
	काष्ठा comedi_bufconfig bc;
	काष्ठा comedi_async *async;
	काष्ठा comedi_subdevice *s;
	पूर्णांक retval = 0;

	lockdep_निश्चित_held(&dev->mutex);
	अगर (copy_from_user(&bc, arg, माप(bc)))
		वापस -EFAULT;

	अगर (bc.subdevice >= dev->n_subdevices)
		वापस -EINVAL;

	s = &dev->subdevices[bc.subdevice];
	async = s->async;

	अगर (!async) अणु
		dev_dbg(dev->class_dev,
			"subdevice does not have async capability\n");
		bc.size = 0;
		bc.maximum_size = 0;
		जाओ copyback;
	पूर्ण

	अगर (bc.maximum_size) अणु
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		async->max_bufsize = bc.maximum_size;
	पूर्ण

	अगर (bc.size) अणु
		retval = resize_async_buffer(dev, s, bc.size);
		अगर (retval < 0)
			वापस retval;
	पूर्ण

	bc.size = async->pपुनः_स्मृति_bufsz;
	bc.maximum_size = async->max_bufsize;

copyback:
	अगर (copy_to_user(arg, &bc, माप(bc)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * COMEDI_DEVINFO ioctl
 * device info
 *
 * arg:
 *	poपूर्णांकer to comedi_devinfo काष्ठाure
 *
 * पढ़ोs:
 *	nothing
 *
 * ग_लिखोs:
 *	comedi_devinfo काष्ठाure
 */
अटल पूर्णांक करो_devinfo_ioctl(काष्ठा comedi_device *dev,
			    काष्ठा comedi_devinfo __user *arg,
			    काष्ठा file *file)
अणु
	काष्ठा comedi_subdevice *s;
	काष्ठा comedi_devinfo devinfo;

	lockdep_निश्चित_held(&dev->mutex);
	स_रखो(&devinfo, 0, माप(devinfo));

	/* fill devinfo काष्ठाure */
	devinfo.version_code = COMEDI_VERSION_CODE;
	devinfo.n_subdevs = dev->n_subdevices;
	strscpy(devinfo.driver_name, dev->driver->driver_name, COMEDI_NAMELEN);
	strscpy(devinfo.board_name, dev->board_name, COMEDI_NAMELEN);

	s = comedi_file_पढ़ो_subdevice(file);
	अगर (s)
		devinfo.पढ़ो_subdevice = s->index;
	अन्यथा
		devinfo.पढ़ो_subdevice = -1;

	s = comedi_file_ग_लिखो_subdevice(file);
	अगर (s)
		devinfo.ग_लिखो_subdevice = s->index;
	अन्यथा
		devinfo.ग_लिखो_subdevice = -1;

	अगर (copy_to_user(arg, &devinfo, माप(devinfo)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * COMEDI_SUBDINFO ioctl
 * subdevices info
 *
 * arg:
 *	poपूर्णांकer to array of comedi_subdinfo काष्ठाures
 *
 * पढ़ोs:
 *	nothing
 *
 * ग_लिखोs:
 *	array of comedi_subdinfo काष्ठाures
 */
अटल पूर्णांक करो_subdinfo_ioctl(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdinfo __user *arg, व्योम *file)
अणु
	पूर्णांक ret, i;
	काष्ठा comedi_subdinfo *पंचांगp, *us;
	काष्ठा comedi_subdevice *s;

	lockdep_निश्चित_held(&dev->mutex);
	पंचांगp = kसुस्मृति(dev->n_subdevices, माप(*पंचांगp), GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	/* fill subdinfo काष्ठाs */
	क्रम (i = 0; i < dev->n_subdevices; i++) अणु
		s = &dev->subdevices[i];
		us = पंचांगp + i;

		us->type = s->type;
		us->n_chan = s->n_chan;
		us->subd_flags = s->subdev_flags;
		अगर (comedi_is_subdevice_running(s))
			us->subd_flags |= SDF_RUNNING;
#घोषणा TIMER_nanosec 5		/* backwards compatibility */
		us->समयr_type = TIMER_nanosec;
		us->len_chanlist = s->len_chanlist;
		us->maxdata = s->maxdata;
		अगर (s->range_table) अणु
			us->range_type =
			    (i << 24) | (0 << 16) | (s->range_table->length);
		पूर्ण अन्यथा अणु
			us->range_type = 0;	/* XXX */
		पूर्ण

		अगर (s->busy)
			us->subd_flags |= SDF_BUSY;
		अगर (s->busy == file)
			us->subd_flags |= SDF_BUSY_OWNER;
		अगर (s->lock)
			us->subd_flags |= SDF_LOCKED;
		अगर (s->lock == file)
			us->subd_flags |= SDF_LOCK_OWNER;
		अगर (!s->maxdata && s->maxdata_list)
			us->subd_flags |= SDF_MAXDATA;
		अगर (s->range_table_list)
			us->subd_flags |= SDF_RANGETYPE;
		अगर (s->करो_cmd)
			us->subd_flags |= SDF_CMD;

		अगर (s->insn_bits != &insn_inval)
			us->insn_bits_support = COMEDI_SUPPORTED;
		अन्यथा
			us->insn_bits_support = COMEDI_UNSUPPORTED;
	पूर्ण

	ret = copy_to_user(arg, पंचांगp, dev->n_subdevices * माप(*पंचांगp));

	kमुक्त(पंचांगp);

	वापस ret ? -EFAULT : 0;
पूर्ण

/*
 * COMEDI_CHANINFO ioctl
 * subdevice channel info
 *
 * arg:
 *	poपूर्णांकer to comedi_chaninfo काष्ठाure
 *
 * पढ़ोs:
 *	comedi_chaninfo काष्ठाure
 *
 * ग_लिखोs:
 *	array of maxdata values to chaninfo->maxdata_list अगर requested
 *	array of range table lengths to chaninfo->range_table_list अगर requested
 */
अटल पूर्णांक करो_chaninfo_ioctl(काष्ठा comedi_device *dev,
			     काष्ठा comedi_chaninfo *it)
अणु
	काष्ठा comedi_subdevice *s;

	lockdep_निश्चित_held(&dev->mutex);

	अगर (it->subdev >= dev->n_subdevices)
		वापस -EINVAL;
	s = &dev->subdevices[it->subdev];

	अगर (it->maxdata_list) अणु
		अगर (s->maxdata || !s->maxdata_list)
			वापस -EINVAL;
		अगर (copy_to_user(it->maxdata_list, s->maxdata_list,
				 s->n_chan * माप(अचिन्हित पूर्णांक)))
			वापस -EFAULT;
	पूर्ण

	अगर (it->flaglist)
		वापस -EINVAL;	/* flaglist not supported */

	अगर (it->rangelist) अणु
		पूर्णांक i;

		अगर (!s->range_table_list)
			वापस -EINVAL;
		क्रम (i = 0; i < s->n_chan; i++) अणु
			पूर्णांक x;

			x = (dev->minor << 28) | (it->subdev << 24) | (i << 16) |
			    (s->range_table_list[i]->length);
			अगर (put_user(x, it->rangelist + i))
				वापस -EFAULT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * COMEDI_BUFINFO ioctl
 * buffer inक्रमmation
 *
 * arg:
 *	poपूर्णांकer to comedi_bufinfo काष्ठाure
 *
 * पढ़ोs:
 *	comedi_bufinfo काष्ठाure
 *
 * ग_लिखोs:
 *	modअगरied comedi_bufinfo काष्ठाure
 */
अटल पूर्णांक करो_bufinfo_ioctl(काष्ठा comedi_device *dev,
			    काष्ठा comedi_bufinfo __user *arg, व्योम *file)
अणु
	काष्ठा comedi_bufinfo bi;
	काष्ठा comedi_subdevice *s;
	काष्ठा comedi_async *async;
	अचिन्हित पूर्णांक runflags;
	पूर्णांक retval = 0;
	bool become_nonbusy = false;

	lockdep_निश्चित_held(&dev->mutex);
	अगर (copy_from_user(&bi, arg, माप(bi)))
		वापस -EFAULT;

	अगर (bi.subdevice >= dev->n_subdevices)
		वापस -EINVAL;

	s = &dev->subdevices[bi.subdevice];

	async = s->async;

	अगर (!async || s->busy != file)
		वापस -EINVAL;

	runflags = comedi_get_subdevice_runflags(s);
	अगर (!(async->cmd.flags & CMDF_WRITE)) अणु
		/* command was set up in "read" direction */
		अगर (bi.bytes_पढ़ो) अणु
			comedi_buf_पढ़ो_alloc(s, bi.bytes_पढ़ो);
			bi.bytes_पढ़ो = comedi_buf_पढ़ो_मुक्त(s, bi.bytes_पढ़ो);
		पूर्ण
		/*
		 * If nothing left to पढ़ो, and command has stopped, and
		 * अणु"read" position not updated or command stopped normallyपूर्ण,
		 * then become non-busy.
		 */
		अगर (comedi_buf_पढ़ो_n_available(s) == 0 &&
		    !comedi_is_runflags_running(runflags) &&
		    (bi.bytes_पढ़ो == 0 ||
		     !comedi_is_runflags_in_error(runflags))) अणु
			become_nonbusy = true;
			अगर (comedi_is_runflags_in_error(runflags))
				retval = -EPIPE;
		पूर्ण
		bi.bytes_written = 0;
	पूर्ण अन्यथा अणु
		/* command was set up in "write" direction */
		अगर (!comedi_is_runflags_running(runflags)) अणु
			bi.bytes_written = 0;
			become_nonbusy = true;
			अगर (comedi_is_runflags_in_error(runflags))
				retval = -EPIPE;
		पूर्ण अन्यथा अगर (bi.bytes_written) अणु
			comedi_buf_ग_लिखो_alloc(s, bi.bytes_written);
			bi.bytes_written =
			    comedi_buf_ग_लिखो_मुक्त(s, bi.bytes_written);
		पूर्ण
		bi.bytes_पढ़ो = 0;
	पूर्ण

	bi.buf_ग_लिखो_count = async->buf_ग_लिखो_count;
	bi.buf_ग_लिखो_ptr = async->buf_ग_लिखो_ptr;
	bi.buf_पढ़ो_count = async->buf_पढ़ो_count;
	bi.buf_पढ़ो_ptr = async->buf_पढ़ो_ptr;

	अगर (become_nonbusy)
		करो_become_nonbusy(dev, s);

	अगर (retval)
		वापस retval;

	अगर (copy_to_user(arg, &bi, माप(bi)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक check_insn_config_length(काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	अगर (insn->n < 1)
		वापस -EINVAL;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_DIO_OUTPUT:
	हाल INSN_CONFIG_DIO_INPUT:
	हाल INSN_CONFIG_DISARM:
	हाल INSN_CONFIG_RESET:
		अगर (insn->n == 1)
			वापस 0;
		अवरोध;
	हाल INSN_CONFIG_ARM:
	हाल INSN_CONFIG_DIO_QUERY:
	हाल INSN_CONFIG_BLOCK_SIZE:
	हाल INSN_CONFIG_FILTER:
	हाल INSN_CONFIG_SERIAL_CLOCK:
	हाल INSN_CONFIG_BIसूचीECTIONAL_DATA:
	हाल INSN_CONFIG_ALT_SOURCE:
	हाल INSN_CONFIG_SET_COUNTER_MODE:
	हाल INSN_CONFIG_8254_READ_STATUS:
	हाल INSN_CONFIG_SET_ROUTING:
	हाल INSN_CONFIG_GET_ROUTING:
	हाल INSN_CONFIG_GET_PWM_STATUS:
	हाल INSN_CONFIG_PWM_SET_PERIOD:
	हाल INSN_CONFIG_PWM_GET_PERIOD:
		अगर (insn->n == 2)
			वापस 0;
		अवरोध;
	हाल INSN_CONFIG_SET_GATE_SRC:
	हाल INSN_CONFIG_GET_GATE_SRC:
	हाल INSN_CONFIG_SET_CLOCK_SRC:
	हाल INSN_CONFIG_GET_CLOCK_SRC:
	हाल INSN_CONFIG_SET_OTHER_SRC:
	हाल INSN_CONFIG_GET_COUNTER_STATUS:
	हाल INSN_CONFIG_PWM_SET_H_BRIDGE:
	हाल INSN_CONFIG_PWM_GET_H_BRIDGE:
	हाल INSN_CONFIG_GET_HARDWARE_BUFFER_SIZE:
		अगर (insn->n == 3)
			वापस 0;
		अवरोध;
	हाल INSN_CONFIG_PWM_OUTPUT:
	हाल INSN_CONFIG_ANALOG_TRIG:
	हाल INSN_CONFIG_TIMER_1:
		अगर (insn->n == 5)
			वापस 0;
		अवरोध;
	हाल INSN_CONFIG_DIGITAL_TRIG:
		अगर (insn->n == 6)
			वापस 0;
		अवरोध;
	हाल INSN_CONFIG_GET_CMD_TIMING_CONSTRAINTS:
		अगर (insn->n >= 4)
			वापस 0;
		अवरोध;
		/*
		 * by शेष we allow the insn since we करोn't have checks क्रम
		 * all possible हालs yet
		 */
	शेष:
		pr_warn("No check for data length of config insn id %i is implemented\n",
			data[0]);
		pr_warn("Add a check to %s in %s\n", __func__, __खाता__);
		pr_warn("Assuming n=%i is correct\n", insn->n);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक check_insn_device_config_length(काष्ठा comedi_insn *insn,
					   अचिन्हित पूर्णांक *data)
अणु
	अगर (insn->n < 1)
		वापस -EINVAL;

	चयन (data[0]) अणु
	हाल INSN_DEVICE_CONFIG_TEST_ROUTE:
	हाल INSN_DEVICE_CONFIG_CONNECT_ROUTE:
	हाल INSN_DEVICE_CONFIG_DISCONNECT_ROUTE:
		अगर (insn->n == 3)
			वापस 0;
		अवरोध;
	हाल INSN_DEVICE_CONFIG_GET_ROUTES:
		/*
		 * Big enough क्रम config_id and the length of the userland
		 * memory buffer.  Additional length should be in factors of 2
		 * to communicate any वापसed route pairs (source,destination).
		 */
		अगर (insn->n >= 2)
			वापस 0;
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/**
 * get_valid_routes() - Calls low-level driver get_valid_routes function to
 *			either वापस a count of valid routes to user, or copy
 *			of list of all valid device routes to buffer in
 *			userspace.
 * @dev: comedi device poपूर्णांकer
 * @data: data from user insn call.  The length of the data must be >= 2.
 *	  data[0] must contain the INSN_DEVICE_CONFIG config_id.
 *	  data[1](input) contains the number of _pairs_ क्रम which memory is
 *		  allotted from the user.  If the user specअगरies '0', then only
 *		  the number of pairs available is वापसed.
 *	  data[1](output) वापसs either the number of pairs available (अगर none
 *		  where requested) or the number of _pairs_ that are copied back
 *		  to the user.
 *	  data[2::2] वापसs each (source, destination) pair.
 *
 * Return: -EINVAL अगर low-level driver करोes not allocate and वापस routes as
 *	   expected.  Returns 0 otherwise.
 */
अटल पूर्णांक get_valid_routes(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक *data)
अणु
	lockdep_निश्चित_held(&dev->mutex);
	data[1] = dev->get_valid_routes(dev, data[1], data + 2);
	वापस 0;
पूर्ण

अटल पूर्णांक parse_insn(काष्ठा comedi_device *dev, काष्ठा comedi_insn *insn,
		      अचिन्हित पूर्णांक *data, व्योम *file)
अणु
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret = 0;
	पूर्णांक i;

	lockdep_निश्चित_held(&dev->mutex);
	अगर (insn->insn & INSN_MASK_SPECIAL) अणु
		/* a non-subdevice inकाष्ठाion */

		चयन (insn->insn) अणु
		हाल INSN_GTOD:
			अणु
				काष्ठा बारpec64 tv;

				अगर (insn->n != 2) अणु
					ret = -EINVAL;
					अवरोध;
				पूर्ण

				kसमय_get_real_ts64(&tv);
				/* अचिन्हित data safe until 2106 */
				data[0] = (अचिन्हित पूर्णांक)tv.tv_sec;
				data[1] = tv.tv_nsec / NSEC_PER_USEC;
				ret = 2;

				अवरोध;
			पूर्ण
		हाल INSN_WAIT:
			अगर (insn->n != 1 || data[0] >= 100000) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			udelay(data[0] / 1000);
			ret = 1;
			अवरोध;
		हाल INSN_INTTRIG:
			अगर (insn->n != 1) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			अगर (insn->subdev >= dev->n_subdevices) अणु
				dev_dbg(dev->class_dev,
					"%d not usable subdevice\n",
					insn->subdev);
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			s = &dev->subdevices[insn->subdev];
			अगर (!s->async) अणु
				dev_dbg(dev->class_dev, "no async\n");
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			अगर (!s->async->पूर्णांकtrig) अणु
				dev_dbg(dev->class_dev, "no inttrig\n");
				ret = -EAGAIN;
				अवरोध;
			पूर्ण
			ret = s->async->पूर्णांकtrig(dev, s, data[0]);
			अगर (ret >= 0)
				ret = 1;
			अवरोध;
		हाल INSN_DEVICE_CONFIG:
			ret = check_insn_device_config_length(insn, data);
			अगर (ret)
				अवरोध;

			अगर (data[0] == INSN_DEVICE_CONFIG_GET_ROUTES) अणु
				/*
				 * data[1] should be the number of _pairs_ that
				 * the memory can hold.
				 */
				data[1] = (insn->n - 2) / 2;
				ret = get_valid_routes(dev, data);
				अवरोध;
			पूर्ण

			/* other global device config inकाष्ठाions. */
			ret = dev->insn_device_config(dev, insn, data);
			अवरोध;
		शेष:
			dev_dbg(dev->class_dev, "invalid insn\n");
			ret = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* a subdevice inकाष्ठाion */
		अचिन्हित पूर्णांक maxdata;

		अगर (insn->subdev >= dev->n_subdevices) अणु
			dev_dbg(dev->class_dev, "subdevice %d out of range\n",
				insn->subdev);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		s = &dev->subdevices[insn->subdev];

		अगर (s->type == COMEDI_SUBD_UNUSED) अणु
			dev_dbg(dev->class_dev, "%d not usable subdevice\n",
				insn->subdev);
			ret = -EIO;
			जाओ out;
		पूर्ण

		/* are we locked? (ioctl lock) */
		अगर (s->lock && s->lock != file) अणु
			dev_dbg(dev->class_dev, "device locked\n");
			ret = -EACCES;
			जाओ out;
		पूर्ण

		ret = comedi_check_chanlist(s, 1, &insn->chanspec);
		अगर (ret < 0) अणु
			ret = -EINVAL;
			dev_dbg(dev->class_dev, "bad chanspec\n");
			जाओ out;
		पूर्ण

		अगर (s->busy) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण
		/* This looks arbitrary.  It is. */
		s->busy = parse_insn;
		चयन (insn->insn) अणु
		हाल INSN_READ:
			ret = s->insn_पढ़ो(dev, s, insn, data);
			अगर (ret == -ETIMEDOUT) अणु
				dev_dbg(dev->class_dev,
					"subdevice %d read instruction timed out\n",
					s->index);
			पूर्ण
			अवरोध;
		हाल INSN_WRITE:
			maxdata = s->maxdata_list
			    ? s->maxdata_list[CR_CHAN(insn->chanspec)]
			    : s->maxdata;
			क्रम (i = 0; i < insn->n; ++i) अणु
				अगर (data[i] > maxdata) अणु
					ret = -EINVAL;
					dev_dbg(dev->class_dev,
						"bad data value(s)\n");
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (ret == 0) अणु
				ret = s->insn_ग_लिखो(dev, s, insn, data);
				अगर (ret == -ETIMEDOUT) अणु
					dev_dbg(dev->class_dev,
						"subdevice %d write instruction timed out\n",
						s->index);
				पूर्ण
			पूर्ण
			अवरोध;
		हाल INSN_BITS:
			अगर (insn->n != 2) अणु
				ret = -EINVAL;
			पूर्ण अन्यथा अणु
				/*
				 * Most drivers ignore the base channel in
				 * insn->chanspec.  Fix this here अगर
				 * the subdevice has <= 32 channels.
				 */
				अचिन्हित पूर्णांक orig_mask = data[0];
				अचिन्हित पूर्णांक shअगरt = 0;

				अगर (s->n_chan <= 32) अणु
					shअगरt = CR_CHAN(insn->chanspec);
					अगर (shअगरt > 0) अणु
						insn->chanspec = 0;
						data[0] <<= shअगरt;
						data[1] <<= shअगरt;
					पूर्ण
				पूर्ण
				ret = s->insn_bits(dev, s, insn, data);
				data[0] = orig_mask;
				अगर (shअगरt > 0)
					data[1] >>= shअगरt;
			पूर्ण
			अवरोध;
		हाल INSN_CONFIG:
			ret = check_insn_config_length(insn, data);
			अगर (ret)
				अवरोध;
			ret = s->insn_config(dev, s, insn, data);
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		s->busy = शून्य;
	पूर्ण

out:
	वापस ret;
पूर्ण

/*
 * COMEDI_INSNLIST ioctl
 * synchronous inकाष्ठाion list
 *
 * arg:
 *	poपूर्णांकer to comedi_insnlist काष्ठाure
 *
 * पढ़ोs:
 *	comedi_insnlist काष्ठाure
 *	array of comedi_insn काष्ठाures from insnlist->insns poपूर्णांकer
 *	data (क्रम ग_लिखोs) from insns[].data poपूर्णांकers
 *
 * ग_लिखोs:
 *	data (क्रम पढ़ोs) to insns[].data poपूर्णांकers
 */
/* arbitrary limits */
#घोषणा MIN_SAMPLES 16
#घोषणा MAX_SAMPLES 65536
अटल पूर्णांक करो_insnlist_ioctl(काष्ठा comedi_device *dev,
			     काष्ठा comedi_insn *insns,
			     अचिन्हित पूर्णांक n_insns,
			     व्योम *file)
अणु
	अचिन्हित पूर्णांक *data = शून्य;
	अचिन्हित पूर्णांक max_n_data_required = MIN_SAMPLES;
	पूर्णांक i = 0;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&dev->mutex);

	/* Determine maximum memory needed क्रम all inकाष्ठाions. */
	क्रम (i = 0; i < n_insns; ++i) अणु
		अगर (insns[i].n > MAX_SAMPLES) अणु
			dev_dbg(dev->class_dev,
				"number of samples too large\n");
			ret = -EINVAL;
			जाओ error;
		पूर्ण
		max_n_data_required = max(max_n_data_required, insns[i].n);
	पूर्ण

	/* Allocate scratch space क्रम all inकाष्ठाion data. */
	data = kदो_स्मृति_array(max_n_data_required, माप(अचिन्हित पूर्णांक),
			     GFP_KERNEL);
	अगर (!data) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	क्रम (i = 0; i < n_insns; ++i) अणु
		अगर (insns[i].insn & INSN_MASK_WRITE) अणु
			अगर (copy_from_user(data, insns[i].data,
					   insns[i].n * माप(अचिन्हित पूर्णांक))) अणु
				dev_dbg(dev->class_dev,
					"copy_from_user failed\n");
				ret = -EFAULT;
				जाओ error;
			पूर्ण
		पूर्ण
		ret = parse_insn(dev, insns + i, data, file);
		अगर (ret < 0)
			जाओ error;
		अगर (insns[i].insn & INSN_MASK_READ) अणु
			अगर (copy_to_user(insns[i].data, data,
					 insns[i].n * माप(अचिन्हित पूर्णांक))) अणु
				dev_dbg(dev->class_dev,
					"copy_to_user failed\n");
				ret = -EFAULT;
				जाओ error;
			पूर्ण
		पूर्ण
		अगर (need_resched())
			schedule();
	पूर्ण

error:
	kमुक्त(data);

	अगर (ret < 0)
		वापस ret;
	वापस i;
पूर्ण

/*
 * COMEDI_INSN ioctl
 * synchronous inकाष्ठाion
 *
 * arg:
 *	poपूर्णांकer to comedi_insn काष्ठाure
 *
 * पढ़ोs:
 *	comedi_insn काष्ठाure
 *	data (क्रम ग_लिखोs) from insn->data poपूर्णांकer
 *
 * ग_लिखोs:
 *	data (क्रम पढ़ोs) to insn->data poपूर्णांकer
 */
अटल पूर्णांक करो_insn_ioctl(काष्ठा comedi_device *dev,
			 काष्ठा comedi_insn *insn, व्योम *file)
अणु
	अचिन्हित पूर्णांक *data = शून्य;
	अचिन्हित पूर्णांक n_data = MIN_SAMPLES;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&dev->mutex);

	n_data = max(n_data, insn->n);

	/* This is where the behavior of insn and insnlist deviate. */
	अगर (insn->n > MAX_SAMPLES) अणु
		insn->n = MAX_SAMPLES;
		n_data = MAX_SAMPLES;
	पूर्ण

	data = kदो_स्मृति_array(n_data, माप(अचिन्हित पूर्णांक), GFP_KERNEL);
	अगर (!data) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	अगर (insn->insn & INSN_MASK_WRITE) अणु
		अगर (copy_from_user(data,
				   insn->data,
				   insn->n * माप(अचिन्हित पूर्णांक))) अणु
			ret = -EFAULT;
			जाओ error;
		पूर्ण
	पूर्ण
	ret = parse_insn(dev, insn, data, file);
	अगर (ret < 0)
		जाओ error;
	अगर (insn->insn & INSN_MASK_READ) अणु
		अगर (copy_to_user(insn->data,
				 data,
				 insn->n * माप(अचिन्हित पूर्णांक))) अणु
			ret = -EFAULT;
			जाओ error;
		पूर्ण
	पूर्ण
	ret = insn->n;

error:
	kमुक्त(data);

	वापस ret;
पूर्ण

अटल पूर्णांक __comedi_get_user_cmd(काष्ठा comedi_device *dev,
				 काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा comedi_subdevice *s;

	lockdep_निश्चित_held(&dev->mutex);
	अगर (cmd->subdev >= dev->n_subdevices) अणु
		dev_dbg(dev->class_dev, "%d no such subdevice\n", cmd->subdev);
		वापस -ENODEV;
	पूर्ण

	s = &dev->subdevices[cmd->subdev];

	अगर (s->type == COMEDI_SUBD_UNUSED) अणु
		dev_dbg(dev->class_dev, "%d not valid subdevice\n",
			cmd->subdev);
		वापस -EIO;
	पूर्ण

	अगर (!s->करो_cmd || !s->करो_cmdtest || !s->async) अणु
		dev_dbg(dev->class_dev,
			"subdevice %d does not support commands\n",
			cmd->subdev);
		वापस -EIO;
	पूर्ण

	/* make sure channel/gain list isn't too दीर्घ */
	अगर (cmd->chanlist_len > s->len_chanlist) अणु
		dev_dbg(dev->class_dev, "channel/gain list too long %d > %d\n",
			cmd->chanlist_len, s->len_chanlist);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Set the CMDF_WRITE flag to the correct state अगर the subdevice
	 * supports only "read" commands or only "write" commands.
	 */
	चयन (s->subdev_flags & (SDF_CMD_READ | SDF_CMD_WRITE)) अणु
	हाल SDF_CMD_READ:
		cmd->flags &= ~CMDF_WRITE;
		अवरोध;
	हाल SDF_CMD_WRITE:
		cmd->flags |= CMDF_WRITE;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __comedi_get_user_chanlist(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s,
				      अचिन्हित पूर्णांक __user *user_chanlist,
				      काष्ठा comedi_cmd *cmd)
अणु
	अचिन्हित पूर्णांक *chanlist;
	पूर्णांक ret;

	lockdep_निश्चित_held(&dev->mutex);
	cmd->chanlist = शून्य;
	chanlist = memdup_user(user_chanlist,
			       cmd->chanlist_len * माप(अचिन्हित पूर्णांक));
	अगर (IS_ERR(chanlist))
		वापस PTR_ERR(chanlist);

	/* make sure each element in channel/gain list is valid */
	ret = comedi_check_chanlist(s, cmd->chanlist_len, chanlist);
	अगर (ret < 0) अणु
		kमुक्त(chanlist);
		वापस ret;
	पूर्ण

	cmd->chanlist = chanlist;

	वापस 0;
पूर्ण

/*
 * COMEDI_CMD ioctl
 * asynchronous acquisition command set-up
 *
 * arg:
 *	poपूर्णांकer to comedi_cmd काष्ठाure
 *
 * पढ़ोs:
 *	comedi_cmd काष्ठाure
 *	channel/range list from cmd->chanlist poपूर्णांकer
 *
 * ग_लिखोs:
 *	possibly modअगरied comedi_cmd काष्ठाure (when -EAGAIN वापसed)
 */
अटल पूर्णांक करो_cmd_ioctl(काष्ठा comedi_device *dev,
			काष्ठा comedi_cmd *cmd, bool *copy, व्योम *file)
अणु
	काष्ठा comedi_subdevice *s;
	काष्ठा comedi_async *async;
	अचिन्हित पूर्णांक __user *user_chanlist;
	पूर्णांक ret;

	lockdep_निश्चित_held(&dev->mutex);

	/* करो some simple cmd validation */
	ret = __comedi_get_user_cmd(dev, cmd);
	अगर (ret)
		वापस ret;

	/* save user's chanlist poपूर्णांकer so it can be restored later */
	user_chanlist = (अचिन्हित पूर्णांक __user *)cmd->chanlist;

	s = &dev->subdevices[cmd->subdev];
	async = s->async;

	/* are we locked? (ioctl lock) */
	अगर (s->lock && s->lock != file) अणु
		dev_dbg(dev->class_dev, "subdevice locked\n");
		वापस -EACCES;
	पूर्ण

	/* are we busy? */
	अगर (s->busy) अणु
		dev_dbg(dev->class_dev, "subdevice busy\n");
		वापस -EBUSY;
	पूर्ण

	/* make sure channel/gain list isn't too लघु */
	अगर (cmd->chanlist_len < 1) अणु
		dev_dbg(dev->class_dev, "channel/gain list too short %u < 1\n",
			cmd->chanlist_len);
		वापस -EINVAL;
	पूर्ण

	async->cmd = *cmd;
	async->cmd.data = शून्य;

	/* load channel/gain list */
	ret = __comedi_get_user_chanlist(dev, s, user_chanlist, &async->cmd);
	अगर (ret)
		जाओ cleanup;

	ret = s->करो_cmdtest(dev, s, &async->cmd);

	अगर (async->cmd.flags & CMDF_BOGUS || ret) अणु
		dev_dbg(dev->class_dev, "test returned %d\n", ret);
		*cmd = async->cmd;
		/* restore chanlist poपूर्णांकer beक्रमe copying back */
		cmd->chanlist = (अचिन्हित पूर्णांक __क्रमce *)user_chanlist;
		cmd->data = शून्य;
		*copy = true;
		ret = -EAGAIN;
		जाओ cleanup;
	पूर्ण

	अगर (!async->pपुनः_स्मृति_bufsz) अणु
		ret = -ENOMEM;
		dev_dbg(dev->class_dev, "no buffer (?)\n");
		जाओ cleanup;
	पूर्ण

	comedi_buf_reset(s);

	async->cb_mask = COMEDI_CB_BLOCK | COMEDI_CB_CANCEL_MASK;
	अगर (async->cmd.flags & CMDF_WAKE_EOS)
		async->cb_mask |= COMEDI_CB_EOS;

	comedi_update_subdevice_runflags(s, COMEDI_SRF_BUSY_MASK,
					 COMEDI_SRF_RUNNING);

	/*
	 * Set s->busy _after_ setting COMEDI_SRF_RUNNING flag to aव्योम
	 * race with comedi_पढ़ो() or comedi_ग_लिखो().
	 */
	s->busy = file;
	ret = s->करो_cmd(dev, s);
	अगर (ret == 0)
		वापस 0;

cleanup:
	करो_become_nonbusy(dev, s);

	वापस ret;
पूर्ण

/*
 * COMEDI_CMDTEST ioctl
 * asynchronous acquisition command testing
 *
 * arg:
 *	poपूर्णांकer to comedi_cmd काष्ठाure
 *
 * पढ़ोs:
 *	comedi_cmd काष्ठाure
 *	channel/range list from cmd->chanlist poपूर्णांकer
 *
 * ग_लिखोs:
 *	possibly modअगरied comedi_cmd काष्ठाure
 */
अटल पूर्णांक करो_cmdtest_ioctl(काष्ठा comedi_device *dev,
			    काष्ठा comedi_cmd *cmd, bool *copy, व्योम *file)
अणु
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक __user *user_chanlist;
	पूर्णांक ret;

	lockdep_निश्चित_held(&dev->mutex);

	/* करो some simple cmd validation */
	ret = __comedi_get_user_cmd(dev, cmd);
	अगर (ret)
		वापस ret;

	/* save user's chanlist poपूर्णांकer so it can be restored later */
	user_chanlist = (अचिन्हित पूर्णांक __user *)cmd->chanlist;

	s = &dev->subdevices[cmd->subdev];

	/* user_chanlist can be शून्य क्रम COMEDI_CMDTEST ioctl */
	अगर (user_chanlist) अणु
		/* load channel/gain list */
		ret = __comedi_get_user_chanlist(dev, s, user_chanlist, cmd);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = s->करो_cmdtest(dev, s, cmd);

	kमुक्त(cmd->chanlist);	/* मुक्त kernel copy of user chanlist */

	/* restore chanlist poपूर्णांकer beक्रमe copying back */
	cmd->chanlist = (अचिन्हित पूर्णांक __क्रमce *)user_chanlist;
	*copy = true;

	वापस ret;
पूर्ण

/*
 * COMEDI_LOCK ioctl
 * lock subdevice
 *
 * arg:
 *	subdevice number
 *
 * पढ़ोs:
 *	nothing
 *
 * ग_लिखोs:
 *	nothing
 */
अटल पूर्णांक करो_lock_ioctl(काष्ठा comedi_device *dev, अचिन्हित दीर्घ arg,
			 व्योम *file)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा comedi_subdevice *s;

	lockdep_निश्चित_held(&dev->mutex);
	अगर (arg >= dev->n_subdevices)
		वापस -EINVAL;
	s = &dev->subdevices[arg];

	spin_lock_irqsave(&s->spin_lock, flags);
	अगर (s->busy || s->lock)
		ret = -EBUSY;
	अन्यथा
		s->lock = file;
	spin_unlock_irqrestore(&s->spin_lock, flags);

	वापस ret;
पूर्ण

/*
 * COMEDI_UNLOCK ioctl
 * unlock subdevice
 *
 * arg:
 *	subdevice number
 *
 * पढ़ोs:
 *	nothing
 *
 * ग_लिखोs:
 *	nothing
 */
अटल पूर्णांक करो_unlock_ioctl(काष्ठा comedi_device *dev, अचिन्हित दीर्घ arg,
			   व्योम *file)
अणु
	काष्ठा comedi_subdevice *s;

	lockdep_निश्चित_held(&dev->mutex);
	अगर (arg >= dev->n_subdevices)
		वापस -EINVAL;
	s = &dev->subdevices[arg];

	अगर (s->busy)
		वापस -EBUSY;

	अगर (s->lock && s->lock != file)
		वापस -EACCES;

	अगर (s->lock == file)
		s->lock = शून्य;

	वापस 0;
पूर्ण

/*
 * COMEDI_CANCEL ioctl
 * cancel asynchronous acquisition
 *
 * arg:
 *	subdevice number
 *
 * पढ़ोs:
 *	nothing
 *
 * ग_लिखोs:
 *	nothing
 */
अटल पूर्णांक करो_cancel_ioctl(काष्ठा comedi_device *dev, अचिन्हित दीर्घ arg,
			   व्योम *file)
अणु
	काष्ठा comedi_subdevice *s;

	lockdep_निश्चित_held(&dev->mutex);
	अगर (arg >= dev->n_subdevices)
		वापस -EINVAL;
	s = &dev->subdevices[arg];
	अगर (!s->async)
		वापस -EINVAL;

	अगर (!s->busy)
		वापस 0;

	अगर (s->busy != file)
		वापस -EBUSY;

	वापस करो_cancel(dev, s);
पूर्ण

/*
 * COMEDI_POLL ioctl
 * inकाष्ठाs driver to synchronize buffers
 *
 * arg:
 *	subdevice number
 *
 * पढ़ोs:
 *	nothing
 *
 * ग_लिखोs:
 *	nothing
 */
अटल पूर्णांक करो_poll_ioctl(काष्ठा comedi_device *dev, अचिन्हित दीर्घ arg,
			 व्योम *file)
अणु
	काष्ठा comedi_subdevice *s;

	lockdep_निश्चित_held(&dev->mutex);
	अगर (arg >= dev->n_subdevices)
		वापस -EINVAL;
	s = &dev->subdevices[arg];

	अगर (!s->busy)
		वापस 0;

	अगर (s->busy != file)
		वापस -EBUSY;

	अगर (s->poll)
		वापस s->poll(dev, s);

	वापस -EINVAL;
पूर्ण

/*
 * COMEDI_SETRSUBD ioctl
 * sets the current "read" subdevice on a per-file basis
 *
 * arg:
 *	subdevice number
 *
 * पढ़ोs:
 *	nothing
 *
 * ग_लिखोs:
 *	nothing
 */
अटल पूर्णांक करो_setrsubd_ioctl(काष्ठा comedi_device *dev, अचिन्हित दीर्घ arg,
			     काष्ठा file *file)
अणु
	काष्ठा comedi_file *cfp = file->निजी_data;
	काष्ठा comedi_subdevice *s_old, *s_new;

	lockdep_निश्चित_held(&dev->mutex);
	अगर (arg >= dev->n_subdevices)
		वापस -EINVAL;

	s_new = &dev->subdevices[arg];
	s_old = comedi_file_पढ़ो_subdevice(file);
	अगर (s_old == s_new)
		वापस 0;	/* no change */

	अगर (!(s_new->subdev_flags & SDF_CMD_READ))
		वापस -EINVAL;

	/*
	 * Check the file isn't still busy handling a "read" command on the
	 * old subdevice (अगर any).
	 */
	अगर (s_old && s_old->busy == file && s_old->async &&
	    !(s_old->async->cmd.flags & CMDF_WRITE))
		वापस -EBUSY;

	WRITE_ONCE(cfp->पढ़ो_subdev, s_new);
	वापस 0;
पूर्ण

/*
 * COMEDI_SETWSUBD ioctl
 * sets the current "write" subdevice on a per-file basis
 *
 * arg:
 *	subdevice number
 *
 * पढ़ोs:
 *	nothing
 *
 * ग_लिखोs:
 *	nothing
 */
अटल पूर्णांक करो_setwsubd_ioctl(काष्ठा comedi_device *dev, अचिन्हित दीर्घ arg,
			     काष्ठा file *file)
अणु
	काष्ठा comedi_file *cfp = file->निजी_data;
	काष्ठा comedi_subdevice *s_old, *s_new;

	lockdep_निश्चित_held(&dev->mutex);
	अगर (arg >= dev->n_subdevices)
		वापस -EINVAL;

	s_new = &dev->subdevices[arg];
	s_old = comedi_file_ग_लिखो_subdevice(file);
	अगर (s_old == s_new)
		वापस 0;	/* no change */

	अगर (!(s_new->subdev_flags & SDF_CMD_WRITE))
		वापस -EINVAL;

	/*
	 * Check the file isn't still busy handling a "write" command on the
	 * old subdevice (अगर any).
	 */
	अगर (s_old && s_old->busy == file && s_old->async &&
	    (s_old->async->cmd.flags & CMDF_WRITE))
		वापस -EBUSY;

	WRITE_ONCE(cfp->ग_लिखो_subdev, s_new);
	वापस 0;
पूर्ण

अटल दीर्घ comedi_unlocked_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				  अचिन्हित दीर्घ arg)
अणु
	अचिन्हित पूर्णांक minor = iminor(file_inode(file));
	काष्ठा comedi_file *cfp = file->निजी_data;
	काष्ठा comedi_device *dev = cfp->dev;
	पूर्णांक rc;

	mutex_lock(&dev->mutex);

	/*
	 * Device config is special, because it must work on
	 * an unconfigured device.
	 */
	अगर (cmd == COMEDI_DEVCONFIG) अणु
		अगर (minor >= COMEDI_NUM_BOARD_MINORS) अणु
			/* Device config not appropriate on non-board minors. */
			rc = -ENOTTY;
			जाओ करोne;
		पूर्ण
		rc = करो_devconfig_ioctl(dev,
					(काष्ठा comedi_devconfig __user *)arg);
		अगर (rc == 0) अणु
			अगर (arg == 0 &&
			    dev->minor >= comedi_num_legacy_minors) अणु
				/*
				 * Successfully unconfigured a dynamically
				 * allocated device.  Try and हटाओ it.
				 */
				अगर (comedi_clear_board_dev(dev)) अणु
					mutex_unlock(&dev->mutex);
					comedi_मुक्त_board_dev(dev);
					वापस rc;
				पूर्ण
			पूर्ण
		पूर्ण
		जाओ करोne;
	पूर्ण

	अगर (!dev->attached) अणु
		dev_dbg(dev->class_dev, "no driver attached\n");
		rc = -ENODEV;
		जाओ करोne;
	पूर्ण

	चयन (cmd) अणु
	हाल COMEDI_BUFCONFIG:
		rc = करो_bufconfig_ioctl(dev,
					(काष्ठा comedi_bufconfig __user *)arg);
		अवरोध;
	हाल COMEDI_DEVINFO:
		rc = करो_devinfo_ioctl(dev, (काष्ठा comedi_devinfo __user *)arg,
				      file);
		अवरोध;
	हाल COMEDI_SUBDINFO:
		rc = करो_subdinfo_ioctl(dev,
				       (काष्ठा comedi_subdinfo __user *)arg,
				       file);
		अवरोध;
	हाल COMEDI_CHANINFO: अणु
		काष्ठा comedi_chaninfo it;

		अगर (copy_from_user(&it, (व्योम __user *)arg, माप(it)))
			rc = -EFAULT;
		अन्यथा
			rc = करो_chaninfo_ioctl(dev, &it);
		अवरोध;
	पूर्ण
	हाल COMEDI_RANGEINFO: अणु
		काष्ठा comedi_rangeinfo it;

		अगर (copy_from_user(&it, (व्योम __user *)arg, माप(it)))
			rc = -EFAULT;
		अन्यथा
			rc = करो_rangeinfo_ioctl(dev, &it);
		अवरोध;
	पूर्ण
	हाल COMEDI_BUFINFO:
		rc = करो_bufinfo_ioctl(dev,
				      (काष्ठा comedi_bufinfo __user *)arg,
				      file);
		अवरोध;
	हाल COMEDI_LOCK:
		rc = करो_lock_ioctl(dev, arg, file);
		अवरोध;
	हाल COMEDI_UNLOCK:
		rc = करो_unlock_ioctl(dev, arg, file);
		अवरोध;
	हाल COMEDI_CANCEL:
		rc = करो_cancel_ioctl(dev, arg, file);
		अवरोध;
	हाल COMEDI_CMD: अणु
		काष्ठा comedi_cmd cmd;
		bool copy = false;

		अगर (copy_from_user(&cmd, (व्योम __user *)arg, माप(cmd))) अणु
			rc = -EFAULT;
			अवरोध;
		पूर्ण
		rc = करो_cmd_ioctl(dev, &cmd, &copy, file);
		अगर (copy && copy_to_user((व्योम __user *)arg, &cmd, माप(cmd)))
			rc = -EFAULT;
		अवरोध;
	पूर्ण
	हाल COMEDI_CMDTEST: अणु
		काष्ठा comedi_cmd cmd;
		bool copy = false;

		अगर (copy_from_user(&cmd, (व्योम __user *)arg, माप(cmd))) अणु
			rc = -EFAULT;
			अवरोध;
		पूर्ण
		rc = करो_cmdtest_ioctl(dev, &cmd, &copy, file);
		अगर (copy && copy_to_user((व्योम __user *)arg, &cmd, माप(cmd)))
			rc = -EFAULT;
		अवरोध;
	पूर्ण
	हाल COMEDI_INSNLIST: अणु
		काष्ठा comedi_insnlist insnlist;
		काष्ठा comedi_insn *insns = शून्य;

		अगर (copy_from_user(&insnlist, (व्योम __user *)arg,
				   माप(insnlist))) अणु
			rc = -EFAULT;
			अवरोध;
		पूर्ण
		insns = kसुस्मृति(insnlist.n_insns, माप(*insns), GFP_KERNEL);
		अगर (!insns) अणु
			rc = -ENOMEM;
			अवरोध;
		पूर्ण
		अगर (copy_from_user(insns, insnlist.insns,
				   माप(*insns) * insnlist.n_insns)) अणु
			rc = -EFAULT;
			kमुक्त(insns);
			अवरोध;
		पूर्ण
		rc = करो_insnlist_ioctl(dev, insns, insnlist.n_insns, file);
		kमुक्त(insns);
		अवरोध;
	पूर्ण
	हाल COMEDI_INSN: अणु
		काष्ठा comedi_insn insn;

		अगर (copy_from_user(&insn, (व्योम __user *)arg, माप(insn)))
			rc = -EFAULT;
		अन्यथा
			rc = करो_insn_ioctl(dev, &insn, file);
		अवरोध;
	पूर्ण
	हाल COMEDI_POLL:
		rc = करो_poll_ioctl(dev, arg, file);
		अवरोध;
	हाल COMEDI_SETRSUBD:
		rc = करो_setrsubd_ioctl(dev, arg, file);
		अवरोध;
	हाल COMEDI_SETWSUBD:
		rc = करो_setwsubd_ioctl(dev, arg, file);
		अवरोध;
	शेष:
		rc = -ENOTTY;
		अवरोध;
	पूर्ण

करोne:
	mutex_unlock(&dev->mutex);
	वापस rc;
पूर्ण

अटल व्योम comedi_vm_खोलो(काष्ठा vm_area_काष्ठा *area)
अणु
	काष्ठा comedi_buf_map *bm;

	bm = area->vm_निजी_data;
	comedi_buf_map_get(bm);
पूर्ण

अटल व्योम comedi_vm_बंद(काष्ठा vm_area_काष्ठा *area)
अणु
	काष्ठा comedi_buf_map *bm;

	bm = area->vm_निजी_data;
	comedi_buf_map_put(bm);
पूर्ण

अटल पूर्णांक comedi_vm_access(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			    व्योम *buf, पूर्णांक len, पूर्णांक ग_लिखो)
अणु
	काष्ठा comedi_buf_map *bm = vma->vm_निजी_data;
	अचिन्हित दीर्घ offset =
	    addr - vma->vm_start + (vma->vm_pgoff << PAGE_SHIFT);

	अगर (len < 0)
		वापस -EINVAL;
	अगर (len > vma->vm_end - addr)
		len = vma->vm_end - addr;
	वापस comedi_buf_map_access(bm, offset, buf, len, ग_लिखो);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा comedi_vm_ops = अणु
	.खोलो = comedi_vm_खोलो,
	.बंद = comedi_vm_बंद,
	.access = comedi_vm_access,
पूर्ण;

अटल पूर्णांक comedi_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा comedi_file *cfp = file->निजी_data;
	काष्ठा comedi_device *dev = cfp->dev;
	काष्ठा comedi_subdevice *s;
	काष्ठा comedi_async *async;
	काष्ठा comedi_buf_map *bm = शून्य;
	काष्ठा comedi_buf_page *buf;
	अचिन्हित दीर्घ start = vma->vm_start;
	अचिन्हित दीर्घ size;
	पूर्णांक n_pages;
	पूर्णांक i;
	पूर्णांक retval = 0;

	/*
	 * 'trylock' aव्योमs circular dependency with current->mm->mmap_lock
	 * and करोwn-पढ़ोing &dev->attach_lock should normally succeed without
	 * contention unless the device is in the process of being attached
	 * or detached.
	 */
	अगर (!करोwn_पढ़ो_trylock(&dev->attach_lock))
		वापस -EAGAIN;

	अगर (!dev->attached) अणु
		dev_dbg(dev->class_dev, "no driver attached\n");
		retval = -ENODEV;
		जाओ करोne;
	पूर्ण

	अगर (vma->vm_flags & VM_WRITE)
		s = comedi_file_ग_लिखो_subdevice(file);
	अन्यथा
		s = comedi_file_पढ़ो_subdevice(file);
	अगर (!s) अणु
		retval = -EINVAL;
		जाओ करोne;
	पूर्ण

	async = s->async;
	अगर (!async) अणु
		retval = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (vma->vm_pgoff != 0) अणु
		dev_dbg(dev->class_dev, "mmap() offset must be 0.\n");
		retval = -EINVAL;
		जाओ करोne;
	पूर्ण

	size = vma->vm_end - vma->vm_start;
	अगर (size > async->pपुनः_स्मृति_bufsz) अणु
		retval = -EFAULT;
		जाओ करोne;
	पूर्ण
	अगर (offset_in_page(size)) अणु
		retval = -EFAULT;
		जाओ करोne;
	पूर्ण

	n_pages = vma_pages(vma);

	/* get reference to current buf map (अगर any) */
	bm = comedi_buf_map_from_subdev_get(s);
	अगर (!bm || n_pages > bm->n_pages) अणु
		retval = -EINVAL;
		जाओ करोne;
	पूर्ण
	अगर (bm->dma_dir != DMA_NONE) अणु
		/*
		 * DMA buffer was allocated as a single block.
		 * Address is in page_list[0].
		 */
		buf = &bm->page_list[0];
		retval = dma_mmap_coherent(bm->dma_hw_dev, vma, buf->virt_addr,
					   buf->dma_addr, n_pages * PAGE_SIZE);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < n_pages; ++i) अणु
			अचिन्हित दीर्घ pfn;

			buf = &bm->page_list[i];
			pfn = page_to_pfn(virt_to_page(buf->virt_addr));
			retval = remap_pfn_range(vma, start, pfn, PAGE_SIZE,
						 PAGE_SHARED);
			अगर (retval)
				अवरोध;

			start += PAGE_SIZE;
		पूर्ण
	पूर्ण

	अगर (retval == 0) अणु
		vma->vm_ops = &comedi_vm_ops;
		vma->vm_निजी_data = bm;

		vma->vm_ops->खोलो(vma);
	पूर्ण

करोne:
	up_पढ़ो(&dev->attach_lock);
	comedi_buf_map_put(bm);	/* put reference to buf map - okay अगर शून्य */
	वापस retval;
पूर्ण

अटल __poll_t comedi_poll(काष्ठा file *file, poll_table *रुको)
अणु
	__poll_t mask = 0;
	काष्ठा comedi_file *cfp = file->निजी_data;
	काष्ठा comedi_device *dev = cfp->dev;
	काष्ठा comedi_subdevice *s, *s_पढ़ो;

	करोwn_पढ़ो(&dev->attach_lock);

	अगर (!dev->attached) अणु
		dev_dbg(dev->class_dev, "no driver attached\n");
		जाओ करोne;
	पूर्ण

	s = comedi_file_पढ़ो_subdevice(file);
	s_पढ़ो = s;
	अगर (s && s->async) अणु
		poll_रुको(file, &s->async->रुको_head, रुको);
		अगर (s->busy != file || !comedi_is_subdevice_running(s) ||
		    (s->async->cmd.flags & CMDF_WRITE) ||
		    comedi_buf_पढ़ो_n_available(s) > 0)
			mask |= EPOLLIN | EPOLLRDNORM;
	पूर्ण

	s = comedi_file_ग_लिखो_subdevice(file);
	अगर (s && s->async) अणु
		अचिन्हित पूर्णांक bps = comedi_bytes_per_sample(s);

		अगर (s != s_पढ़ो)
			poll_रुको(file, &s->async->रुको_head, रुको);
		अगर (s->busy != file || !comedi_is_subdevice_running(s) ||
		    !(s->async->cmd.flags & CMDF_WRITE) ||
		    comedi_buf_ग_लिखो_n_available(s) >= bps)
			mask |= EPOLLOUT | EPOLLWRNORM;
	पूर्ण

करोne:
	up_पढ़ो(&dev->attach_lock);
	वापस mask;
पूर्ण

अटल sमाप_प्रकार comedi_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			    माप_प्रकार nbytes, loff_t *offset)
अणु
	काष्ठा comedi_subdevice *s;
	काष्ठा comedi_async *async;
	अचिन्हित पूर्णांक n, m;
	sमाप_प्रकार count = 0;
	पूर्णांक retval = 0;
	DECLARE_WAITQUEUE(रुको, current);
	काष्ठा comedi_file *cfp = file->निजी_data;
	काष्ठा comedi_device *dev = cfp->dev;
	bool become_nonbusy = false;
	bool attach_locked;
	अचिन्हित पूर्णांक old_detach_count;

	/* Protect against device detachment during operation. */
	करोwn_पढ़ो(&dev->attach_lock);
	attach_locked = true;
	old_detach_count = dev->detach_count;

	अगर (!dev->attached) अणु
		dev_dbg(dev->class_dev, "no driver attached\n");
		retval = -ENODEV;
		जाओ out;
	पूर्ण

	s = comedi_file_ग_लिखो_subdevice(file);
	अगर (!s || !s->async) अणु
		retval = -EIO;
		जाओ out;
	पूर्ण

	async = s->async;
	अगर (s->busy != file || !(async->cmd.flags & CMDF_WRITE)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	add_रुको_queue(&async->रुको_head, &रुको);
	जबतक (count == 0 && !retval) अणु
		अचिन्हित पूर्णांक runflags;
		अचिन्हित पूर्णांक wp, n1, n2;

		set_current_state(TASK_INTERRUPTIBLE);

		runflags = comedi_get_subdevice_runflags(s);
		अगर (!comedi_is_runflags_running(runflags)) अणु
			अगर (comedi_is_runflags_in_error(runflags))
				retval = -EPIPE;
			अगर (retval || nbytes)
				become_nonbusy = true;
			अवरोध;
		पूर्ण
		अगर (nbytes == 0)
			अवरोध;

		/* Allocate all मुक्त buffer space. */
		comedi_buf_ग_लिखो_alloc(s, async->pपुनः_स्मृति_bufsz);
		m = comedi_buf_ग_लिखो_n_allocated(s);
		n = min_t(माप_प्रकार, m, nbytes);

		अगर (n == 0) अणु
			अगर (file->f_flags & O_NONBLOCK) अणु
				retval = -EAGAIN;
				अवरोध;
			पूर्ण
			schedule();
			अगर (संकेत_pending(current)) अणु
				retval = -ERESTARTSYS;
				अवरोध;
			पूर्ण
			अगर (s->busy != file ||
			    !(async->cmd.flags & CMDF_WRITE)) अणु
				retval = -EINVAL;
				अवरोध;
			पूर्ण
			जारी;
		पूर्ण

		set_current_state(TASK_RUNNING);
		wp = async->buf_ग_लिखो_ptr;
		n1 = min(n, async->pपुनः_स्मृति_bufsz - wp);
		n2 = n - n1;
		m = copy_from_user(async->pपुनः_स्मृति_buf + wp, buf, n1);
		अगर (m)
			m += n2;
		अन्यथा अगर (n2)
			m = copy_from_user(async->pपुनः_स्मृति_buf, buf + n1, n2);
		अगर (m) अणु
			n -= m;
			retval = -EFAULT;
		पूर्ण
		comedi_buf_ग_लिखो_मुक्त(s, n);

		count += n;
		nbytes -= n;

		buf += n;
	पूर्ण
	हटाओ_रुको_queue(&async->रुको_head, &रुको);
	set_current_state(TASK_RUNNING);
	अगर (become_nonbusy && count == 0) अणु
		काष्ठा comedi_subdevice *new_s;

		/*
		 * To aव्योम deadlock, cannot acquire dev->mutex
		 * जबतक dev->attach_lock is held.
		 */
		up_पढ़ो(&dev->attach_lock);
		attach_locked = false;
		mutex_lock(&dev->mutex);
		/*
		 * Check device hasn't become detached behind our back.
		 * Checking dev->detach_count is unchanged ought to be
		 * sufficient (unless there have been 2**32 detaches in the
		 * meanसमय!), but check the subdevice poपूर्णांकer as well just in
		 * हाल.
		 *
		 * Also check the subdevice is still in a suitable state to
		 * become non-busy in हाल it changed behind our back.
		 */
		new_s = comedi_file_ग_लिखो_subdevice(file);
		अगर (dev->attached && old_detach_count == dev->detach_count &&
		    s == new_s && new_s->async == async && s->busy == file &&
		    (async->cmd.flags & CMDF_WRITE) &&
		    !comedi_is_subdevice_running(s))
			करो_become_nonbusy(dev, s);
		mutex_unlock(&dev->mutex);
	पूर्ण
out:
	अगर (attach_locked)
		up_पढ़ो(&dev->attach_lock);

	वापस count ? count : retval;
पूर्ण

अटल sमाप_प्रकार comedi_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार nbytes,
			   loff_t *offset)
अणु
	काष्ठा comedi_subdevice *s;
	काष्ठा comedi_async *async;
	अचिन्हित पूर्णांक n, m;
	sमाप_प्रकार count = 0;
	पूर्णांक retval = 0;
	DECLARE_WAITQUEUE(रुको, current);
	काष्ठा comedi_file *cfp = file->निजी_data;
	काष्ठा comedi_device *dev = cfp->dev;
	अचिन्हित पूर्णांक old_detach_count;
	bool become_nonbusy = false;
	bool attach_locked;

	/* Protect against device detachment during operation. */
	करोwn_पढ़ो(&dev->attach_lock);
	attach_locked = true;
	old_detach_count = dev->detach_count;

	अगर (!dev->attached) अणु
		dev_dbg(dev->class_dev, "no driver attached\n");
		retval = -ENODEV;
		जाओ out;
	पूर्ण

	s = comedi_file_पढ़ो_subdevice(file);
	अगर (!s || !s->async) अणु
		retval = -EIO;
		जाओ out;
	पूर्ण

	async = s->async;
	अगर (s->busy != file || (async->cmd.flags & CMDF_WRITE)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	add_रुको_queue(&async->रुको_head, &रुको);
	जबतक (count == 0 && !retval) अणु
		अचिन्हित पूर्णांक rp, n1, n2;

		set_current_state(TASK_INTERRUPTIBLE);

		m = comedi_buf_पढ़ो_n_available(s);
		n = min_t(माप_प्रकार, m, nbytes);

		अगर (n == 0) अणु
			अचिन्हित पूर्णांक runflags =
				     comedi_get_subdevice_runflags(s);

			अगर (!comedi_is_runflags_running(runflags)) अणु
				अगर (comedi_is_runflags_in_error(runflags))
					retval = -EPIPE;
				अगर (retval || nbytes)
					become_nonbusy = true;
				अवरोध;
			पूर्ण
			अगर (nbytes == 0)
				अवरोध;
			अगर (file->f_flags & O_NONBLOCK) अणु
				retval = -EAGAIN;
				अवरोध;
			पूर्ण
			schedule();
			अगर (संकेत_pending(current)) अणु
				retval = -ERESTARTSYS;
				अवरोध;
			पूर्ण
			अगर (s->busy != file ||
			    (async->cmd.flags & CMDF_WRITE)) अणु
				retval = -EINVAL;
				अवरोध;
			पूर्ण
			जारी;
		पूर्ण

		set_current_state(TASK_RUNNING);
		rp = async->buf_पढ़ो_ptr;
		n1 = min(n, async->pपुनः_स्मृति_bufsz - rp);
		n2 = n - n1;
		m = copy_to_user(buf, async->pपुनः_स्मृति_buf + rp, n1);
		अगर (m)
			m += n2;
		अन्यथा अगर (n2)
			m = copy_to_user(buf + n1, async->pपुनः_स्मृति_buf, n2);
		अगर (m) अणु
			n -= m;
			retval = -EFAULT;
		पूर्ण

		comedi_buf_पढ़ो_alloc(s, n);
		comedi_buf_पढ़ो_मुक्त(s, n);

		count += n;
		nbytes -= n;

		buf += n;
	पूर्ण
	हटाओ_रुको_queue(&async->रुको_head, &रुको);
	set_current_state(TASK_RUNNING);
	अगर (become_nonbusy && count == 0) अणु
		काष्ठा comedi_subdevice *new_s;

		/*
		 * To aव्योम deadlock, cannot acquire dev->mutex
		 * जबतक dev->attach_lock is held.
		 */
		up_पढ़ो(&dev->attach_lock);
		attach_locked = false;
		mutex_lock(&dev->mutex);
		/*
		 * Check device hasn't become detached behind our back.
		 * Checking dev->detach_count is unchanged ought to be
		 * sufficient (unless there have been 2**32 detaches in the
		 * meanसमय!), but check the subdevice poपूर्णांकer as well just in
		 * हाल.
		 *
		 * Also check the subdevice is still in a suitable state to
		 * become non-busy in हाल it changed behind our back.
		 */
		new_s = comedi_file_पढ़ो_subdevice(file);
		अगर (dev->attached && old_detach_count == dev->detach_count &&
		    s == new_s && new_s->async == async && s->busy == file &&
		    !(async->cmd.flags & CMDF_WRITE) &&
		    !comedi_is_subdevice_running(s) &&
		    comedi_buf_पढ़ो_n_available(s) == 0)
			करो_become_nonbusy(dev, s);
		mutex_unlock(&dev->mutex);
	पूर्ण
out:
	अगर (attach_locked)
		up_पढ़ो(&dev->attach_lock);

	वापस count ? count : retval;
पूर्ण

अटल पूर्णांक comedi_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	स्थिर अचिन्हित पूर्णांक minor = iminor(inode);
	काष्ठा comedi_file *cfp;
	काष्ठा comedi_device *dev = comedi_dev_get_from_minor(minor);
	पूर्णांक rc;

	अगर (!dev) अणु
		pr_debug("invalid minor number\n");
		वापस -ENODEV;
	पूर्ण

	cfp = kzalloc(माप(*cfp), GFP_KERNEL);
	अगर (!cfp) अणु
		comedi_dev_put(dev);
		वापस -ENOMEM;
	पूर्ण

	cfp->dev = dev;

	mutex_lock(&dev->mutex);
	अगर (!dev->attached && !capable(CAP_SYS_ADMIN)) अणु
		dev_dbg(dev->class_dev, "not attached and not CAP_SYS_ADMIN\n");
		rc = -ENODEV;
		जाओ out;
	पूर्ण
	अगर (dev->attached && dev->use_count == 0) अणु
		अगर (!try_module_get(dev->driver->module)) अणु
			rc = -ENXIO;
			जाओ out;
		पूर्ण
		अगर (dev->खोलो) अणु
			rc = dev->खोलो(dev);
			अगर (rc < 0) अणु
				module_put(dev->driver->module);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	dev->use_count++;
	file->निजी_data = cfp;
	comedi_file_reset(file);
	rc = 0;

out:
	mutex_unlock(&dev->mutex);
	अगर (rc) अणु
		comedi_dev_put(dev);
		kमुक्त(cfp);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक comedi_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	काष्ठा comedi_file *cfp = file->निजी_data;
	काष्ठा comedi_device *dev = cfp->dev;

	वापस fasync_helper(fd, file, on, &dev->async_queue);
पूर्ण

अटल पूर्णांक comedi_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा comedi_file *cfp = file->निजी_data;
	काष्ठा comedi_device *dev = cfp->dev;
	काष्ठा comedi_subdevice *s = शून्य;
	पूर्णांक i;

	mutex_lock(&dev->mutex);

	अगर (dev->subdevices) अणु
		क्रम (i = 0; i < dev->n_subdevices; i++) अणु
			s = &dev->subdevices[i];

			अगर (s->busy == file)
				करो_cancel(dev, s);
			अगर (s->lock == file)
				s->lock = शून्य;
		पूर्ण
	पूर्ण
	अगर (dev->attached && dev->use_count == 1) अणु
		अगर (dev->बंद)
			dev->बंद(dev);
		module_put(dev->driver->module);
	पूर्ण

	dev->use_count--;

	mutex_unlock(&dev->mutex);
	comedi_dev_put(dev);
	kमुक्त(cfp);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT

#घोषणा COMEDI32_CHANINFO _IOR(CIO, 3, काष्ठा comedi32_chaninfo_काष्ठा)
#घोषणा COMEDI32_RANGEINFO _IOR(CIO, 8, काष्ठा comedi32_rangeinfo_काष्ठा)
/*
 * N.B. COMEDI32_CMD and COMEDI_CMD ought to use _IOWR, not _IOR.
 * It's too late to change it now, but it only affects the command number.
 */
#घोषणा COMEDI32_CMD _IOR(CIO, 9, काष्ठा comedi32_cmd_काष्ठा)
/*
 * N.B. COMEDI32_CMDTEST and COMEDI_CMDTEST ought to use _IOWR, not _IOR.
 * It's too late to change it now, but it only affects the command number.
 */
#घोषणा COMEDI32_CMDTEST _IOR(CIO, 10, काष्ठा comedi32_cmd_काष्ठा)
#घोषणा COMEDI32_INSNLIST _IOR(CIO, 11, काष्ठा comedi32_insnlist_काष्ठा)
#घोषणा COMEDI32_INSN _IOR(CIO, 12, काष्ठा comedi32_insn_काष्ठा)

काष्ठा comedi32_chaninfo_काष्ठा अणु
	अचिन्हित पूर्णांक subdev;
	compat_uptr_t maxdata_list;	/* 32-bit 'unsigned int *' */
	compat_uptr_t flaglist;	/* 32-bit 'unsigned int *' */
	compat_uptr_t rangelist;	/* 32-bit 'unsigned int *' */
	अचिन्हित पूर्णांक unused[4];
पूर्ण;

काष्ठा comedi32_rangeinfo_काष्ठा अणु
	अचिन्हित पूर्णांक range_type;
	compat_uptr_t range_ptr;	/* 32-bit 'void *' */
पूर्ण;

काष्ठा comedi32_cmd_काष्ठा अणु
	अचिन्हित पूर्णांक subdev;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक start_src;
	अचिन्हित पूर्णांक start_arg;
	अचिन्हित पूर्णांक scan_begin_src;
	अचिन्हित पूर्णांक scan_begin_arg;
	अचिन्हित पूर्णांक convert_src;
	अचिन्हित पूर्णांक convert_arg;
	अचिन्हित पूर्णांक scan_end_src;
	अचिन्हित पूर्णांक scan_end_arg;
	अचिन्हित पूर्णांक stop_src;
	अचिन्हित पूर्णांक stop_arg;
	compat_uptr_t chanlist;	/* 32-bit 'unsigned int *' */
	अचिन्हित पूर्णांक chanlist_len;
	compat_uptr_t data;	/* 32-bit 'short *' */
	अचिन्हित पूर्णांक data_len;
पूर्ण;

काष्ठा comedi32_insn_काष्ठा अणु
	अचिन्हित पूर्णांक insn;
	अचिन्हित पूर्णांक n;
	compat_uptr_t data;	/* 32-bit 'unsigned int *' */
	अचिन्हित पूर्णांक subdev;
	अचिन्हित पूर्णांक chanspec;
	अचिन्हित पूर्णांक unused[3];
पूर्ण;

काष्ठा comedi32_insnlist_काष्ठा अणु
	अचिन्हित पूर्णांक n_insns;
	compat_uptr_t insns;	/* 32-bit 'struct comedi_insn *' */
पूर्ण;

/* Handle 32-bit COMEDI_CHANINFO ioctl. */
अटल पूर्णांक compat_chaninfo(काष्ठा file *file, अचिन्हित दीर्घ arg)
अणु
	काष्ठा comedi_file *cfp = file->निजी_data;
	काष्ठा comedi_device *dev = cfp->dev;
	काष्ठा comedi32_chaninfo_काष्ठा chaninfo32;
	काष्ठा comedi_chaninfo chaninfo;
	पूर्णांक err;

	अगर (copy_from_user(&chaninfo32, compat_ptr(arg), माप(chaninfo32)))
		वापस -EFAULT;

	स_रखो(&chaninfo, 0, माप(chaninfo));
	chaninfo.subdev = chaninfo32.subdev;
	chaninfo.maxdata_list = compat_ptr(chaninfo32.maxdata_list);
	chaninfo.flaglist = compat_ptr(chaninfo32.flaglist);
	chaninfo.rangelist = compat_ptr(chaninfo32.rangelist);

	mutex_lock(&dev->mutex);
	err = करो_chaninfo_ioctl(dev, &chaninfo);
	mutex_unlock(&dev->mutex);
	वापस err;
पूर्ण

/* Handle 32-bit COMEDI_RANGEINFO ioctl. */
अटल पूर्णांक compat_rangeinfo(काष्ठा file *file, अचिन्हित दीर्घ arg)
अणु
	काष्ठा comedi_file *cfp = file->निजी_data;
	काष्ठा comedi_device *dev = cfp->dev;
	काष्ठा comedi32_rangeinfo_काष्ठा rangeinfo32;
	काष्ठा comedi_rangeinfo rangeinfo;
	पूर्णांक err;

	अगर (copy_from_user(&rangeinfo32, compat_ptr(arg), माप(rangeinfo32)))
		वापस -EFAULT;
	स_रखो(&rangeinfo, 0, माप(rangeinfo));
	rangeinfo.range_type = rangeinfo32.range_type;
	rangeinfo.range_ptr = compat_ptr(rangeinfo32.range_ptr);

	mutex_lock(&dev->mutex);
	err = करो_rangeinfo_ioctl(dev, &rangeinfo);
	mutex_unlock(&dev->mutex);
	वापस err;
पूर्ण

/* Copy 32-bit cmd काष्ठाure to native cmd काष्ठाure. */
अटल पूर्णांक get_compat_cmd(काष्ठा comedi_cmd *cmd,
			  काष्ठा comedi32_cmd_काष्ठा __user *cmd32)
अणु
	काष्ठा comedi32_cmd_काष्ठा v32;

	अगर (copy_from_user(&v32, cmd32, माप(v32)))
		वापस -EFAULT;

	cmd->subdev = v32.subdev;
	cmd->flags = v32.flags;
	cmd->start_src = v32.start_src;
	cmd->start_arg = v32.start_arg;
	cmd->scan_begin_src = v32.scan_begin_src;
	cmd->scan_begin_arg = v32.scan_begin_arg;
	cmd->convert_src = v32.convert_src;
	cmd->convert_arg = v32.convert_arg;
	cmd->scan_end_src = v32.scan_end_src;
	cmd->scan_end_arg = v32.scan_end_arg;
	cmd->stop_src = v32.stop_src;
	cmd->stop_arg = v32.stop_arg;
	cmd->chanlist = (अचिन्हित पूर्णांक __क्रमce *)compat_ptr(v32.chanlist);
	cmd->chanlist_len = v32.chanlist_len;
	cmd->data = compat_ptr(v32.data);
	cmd->data_len = v32.data_len;
	वापस 0;
पूर्ण

/* Copy native cmd काष्ठाure to 32-bit cmd काष्ठाure. */
अटल पूर्णांक put_compat_cmd(काष्ठा comedi32_cmd_काष्ठा __user *cmd32,
			  काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा comedi32_cmd_काष्ठा v32;

	स_रखो(&v32, 0, माप(v32));
	v32.subdev = cmd->subdev;
	v32.flags = cmd->flags;
	v32.start_src = cmd->start_src;
	v32.start_arg = cmd->start_arg;
	v32.scan_begin_src = cmd->scan_begin_src;
	v32.scan_begin_arg = cmd->scan_begin_arg;
	v32.convert_src = cmd->convert_src;
	v32.convert_arg = cmd->convert_arg;
	v32.scan_end_src = cmd->scan_end_src;
	v32.scan_end_arg = cmd->scan_end_arg;
	v32.stop_src = cmd->stop_src;
	v32.stop_arg = cmd->stop_arg;
	/* Assume chanlist poपूर्णांकer is unchanged. */
	v32.chanlist = ptr_to_compat((अचिन्हित पूर्णांक __user *)cmd->chanlist);
	v32.chanlist_len = cmd->chanlist_len;
	v32.data = ptr_to_compat(cmd->data);
	v32.data_len = cmd->data_len;
	अगर (copy_to_user(cmd32, &v32, माप(v32)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/* Handle 32-bit COMEDI_CMD ioctl. */
अटल पूर्णांक compat_cmd(काष्ठा file *file, अचिन्हित दीर्घ arg)
अणु
	काष्ठा comedi_file *cfp = file->निजी_data;
	काष्ठा comedi_device *dev = cfp->dev;
	काष्ठा comedi_cmd cmd;
	bool copy = false;
	पूर्णांक rc, err;

	rc = get_compat_cmd(&cmd, compat_ptr(arg));
	अगर (rc)
		वापस rc;

	mutex_lock(&dev->mutex);
	rc = करो_cmd_ioctl(dev, &cmd, &copy, file);
	mutex_unlock(&dev->mutex);
	अगर (copy) अणु
		/* Special हाल: copy cmd back to user. */
		err = put_compat_cmd(compat_ptr(arg), &cmd);
		अगर (err)
			rc = err;
	पूर्ण
	वापस rc;
पूर्ण

/* Handle 32-bit COMEDI_CMDTEST ioctl. */
अटल पूर्णांक compat_cmdtest(काष्ठा file *file, अचिन्हित दीर्घ arg)
अणु
	काष्ठा comedi_file *cfp = file->निजी_data;
	काष्ठा comedi_device *dev = cfp->dev;
	काष्ठा comedi_cmd cmd;
	bool copy = false;
	पूर्णांक rc, err;

	rc = get_compat_cmd(&cmd, compat_ptr(arg));
	अगर (rc)
		वापस rc;

	mutex_lock(&dev->mutex);
	rc = करो_cmdtest_ioctl(dev, &cmd, &copy, file);
	mutex_unlock(&dev->mutex);
	अगर (copy) अणु
		err = put_compat_cmd(compat_ptr(arg), &cmd);
		अगर (err)
			rc = err;
	पूर्ण
	वापस rc;
पूर्ण

/* Copy 32-bit insn काष्ठाure to native insn काष्ठाure. */
अटल पूर्णांक get_compat_insn(काष्ठा comedi_insn *insn,
			   काष्ठा comedi32_insn_काष्ठा __user *insn32)
अणु
	काष्ठा comedi32_insn_काष्ठा v32;

	/* Copy insn काष्ठाure.  Ignore the unused members. */
	अगर (copy_from_user(&v32, insn32, माप(v32)))
		वापस -EFAULT;
	स_रखो(insn, 0, माप(*insn));
	insn->insn = v32.insn;
	insn->n = v32.n;
	insn->data = compat_ptr(v32.data);
	insn->subdev = v32.subdev;
	insn->chanspec = v32.chanspec;
	वापस 0;
पूर्ण

/* Handle 32-bit COMEDI_INSNLIST ioctl. */
अटल पूर्णांक compat_insnlist(काष्ठा file *file, अचिन्हित दीर्घ arg)
अणु
	काष्ठा comedi_file *cfp = file->निजी_data;
	काष्ठा comedi_device *dev = cfp->dev;
	काष्ठा comedi32_insnlist_काष्ठा insnlist32;
	काष्ठा comedi32_insn_काष्ठा __user *insn32;
	काष्ठा comedi_insn *insns;
	अचिन्हित पूर्णांक n;
	पूर्णांक rc;

	अगर (copy_from_user(&insnlist32, compat_ptr(arg), माप(insnlist32)))
		वापस -EFAULT;

	insns = kसुस्मृति(insnlist32.n_insns, माप(*insns), GFP_KERNEL);
	अगर (!insns)
		वापस -ENOMEM;

	/* Copy insn काष्ठाures. */
	insn32 = compat_ptr(insnlist32.insns);
	क्रम (n = 0; n < insnlist32.n_insns; n++) अणु
		rc = get_compat_insn(insns + n, insn32 + n);
		अगर (rc) अणु
			kमुक्त(insns);
			वापस rc;
		पूर्ण
	पूर्ण

	mutex_lock(&dev->mutex);
	rc = करो_insnlist_ioctl(dev, insns, insnlist32.n_insns, file);
	mutex_unlock(&dev->mutex);
	वापस rc;
पूर्ण

/* Handle 32-bit COMEDI_INSN ioctl. */
अटल पूर्णांक compat_insn(काष्ठा file *file, अचिन्हित दीर्घ arg)
अणु
	काष्ठा comedi_file *cfp = file->निजी_data;
	काष्ठा comedi_device *dev = cfp->dev;
	काष्ठा comedi_insn insn;
	पूर्णांक rc;

	rc = get_compat_insn(&insn, (व्योम __user *)arg);
	अगर (rc)
		वापस rc;

	mutex_lock(&dev->mutex);
	rc = करो_insn_ioctl(dev, &insn, file);
	mutex_unlock(&dev->mutex);
	वापस rc;
पूर्ण

/*
 * compat_ioctl file operation.
 *
 * Returns -ENOIOCTLCMD क्रम unrecognised ioctl codes.
 */
अटल दीर्घ comedi_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक rc;

	चयन (cmd) अणु
	हाल COMEDI_DEVCONFIG:
	हाल COMEDI_DEVINFO:
	हाल COMEDI_SUBDINFO:
	हाल COMEDI_BUFCONFIG:
	हाल COMEDI_BUFINFO:
		/* Just need to translate the poपूर्णांकer argument. */
		arg = (अचिन्हित दीर्घ)compat_ptr(arg);
		rc = comedi_unlocked_ioctl(file, cmd, arg);
		अवरोध;
	हाल COMEDI_LOCK:
	हाल COMEDI_UNLOCK:
	हाल COMEDI_CANCEL:
	हाल COMEDI_POLL:
	हाल COMEDI_SETRSUBD:
	हाल COMEDI_SETWSUBD:
		/* No translation needed. */
		rc = comedi_unlocked_ioctl(file, cmd, arg);
		अवरोध;
	हाल COMEDI32_CHANINFO:
		rc = compat_chaninfo(file, arg);
		अवरोध;
	हाल COMEDI32_RANGEINFO:
		rc = compat_rangeinfo(file, arg);
		अवरोध;
	हाल COMEDI32_CMD:
		rc = compat_cmd(file, arg);
		अवरोध;
	हाल COMEDI32_CMDTEST:
		rc = compat_cmdtest(file, arg);
		अवरोध;
	हाल COMEDI32_INSNLIST:
		rc = compat_insnlist(file, arg);
		अवरोध;
	हाल COMEDI32_INSN:
		rc = compat_insn(file, arg);
		अवरोध;
	शेष:
		rc = -ENOIOCTLCMD;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण
#अन्यथा
#घोषणा comedi_compat_ioctl शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations comedi_fops = अणु
	.owner = THIS_MODULE,
	.unlocked_ioctl = comedi_unlocked_ioctl,
	.compat_ioctl = comedi_compat_ioctl,
	.खोलो = comedi_खोलो,
	.release = comedi_बंद,
	.पढ़ो = comedi_पढ़ो,
	.ग_लिखो = comedi_ग_लिखो,
	.mmap = comedi_mmap,
	.poll = comedi_poll,
	.fasync = comedi_fasync,
	.llseek = noop_llseek,
पूर्ण;

/**
 * comedi_event() - Handle events क्रम asynchronous COMEDI command
 * @dev: COMEDI device.
 * @s: COMEDI subdevice.
 * Context: in_पूर्णांकerrupt() (usually), @s->spin_lock spin-lock not held.
 *
 * If an asynchronous COMEDI command is active on the subdevice, process
 * any %COMEDI_CB_... event flags that have been set, usually by an
 * पूर्णांकerrupt handler.  These may change the run state of the asynchronous
 * command, wake a task, and/or send a %SIGIO संकेत.
 */
व्योम comedi_event(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_async *async = s->async;
	अचिन्हित पूर्णांक events;
	पूर्णांक si_code = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->spin_lock, flags);

	events = async->events;
	async->events = 0;
	अगर (!__comedi_is_subdevice_running(s)) अणु
		spin_unlock_irqrestore(&s->spin_lock, flags);
		वापस;
	पूर्ण

	अगर (events & COMEDI_CB_CANCEL_MASK)
		__comedi_clear_subdevice_runflags(s, COMEDI_SRF_RUNNING);

	/*
	 * Remember अगर an error event has occurred, so an error can be
	 * वापसed the next समय the user करोes a पढ़ो() or ग_लिखो().
	 */
	अगर (events & COMEDI_CB_ERROR_MASK)
		__comedi_set_subdevice_runflags(s, COMEDI_SRF_ERROR);

	अगर (async->cb_mask & events) अणु
		wake_up_पूर्णांकerruptible(&async->रुको_head);
		si_code = async->cmd.flags & CMDF_WRITE ? POLL_OUT : POLL_IN;
	पूर्ण

	spin_unlock_irqrestore(&s->spin_lock, flags);

	अगर (si_code)
		समाप्त_fasync(&dev->async_queue, SIGIO, si_code);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_event);

/* Note: the ->mutex is pre-locked on successful वापस */
काष्ठा comedi_device *comedi_alloc_board_minor(काष्ठा device *hardware_device)
अणु
	काष्ठा comedi_device *dev;
	काष्ठा device *csdev;
	अचिन्हित पूर्णांक i;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);
	comedi_device_init(dev);
	comedi_set_hw_dev(dev, hardware_device);
	mutex_lock(&dev->mutex);
	mutex_lock(&comedi_board_minor_table_lock);
	क्रम (i = hardware_device ? comedi_num_legacy_minors : 0;
	     i < COMEDI_NUM_BOARD_MINORS; ++i) अणु
		अगर (!comedi_board_minor_table[i]) अणु
			comedi_board_minor_table[i] = dev;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&comedi_board_minor_table_lock);
	अगर (i == COMEDI_NUM_BOARD_MINORS) अणु
		mutex_unlock(&dev->mutex);
		comedi_device_cleanup(dev);
		comedi_dev_put(dev);
		dev_err(hardware_device,
			"ran out of minor numbers for board device files\n");
		वापस ERR_PTR(-EBUSY);
	पूर्ण
	dev->minor = i;
	csdev = device_create(comedi_class, hardware_device,
			      MKDEV(COMEDI_MAJOR, i), शून्य, "comedi%i", i);
	अगर (!IS_ERR(csdev))
		dev->class_dev = get_device(csdev);

	/* Note: dev->mutex needs to be unlocked by the caller. */
	वापस dev;
पूर्ण

व्योम comedi_release_hardware_device(काष्ठा device *hardware_device)
अणु
	पूर्णांक minor;
	काष्ठा comedi_device *dev;

	क्रम (minor = comedi_num_legacy_minors; minor < COMEDI_NUM_BOARD_MINORS;
	     minor++) अणु
		mutex_lock(&comedi_board_minor_table_lock);
		dev = comedi_board_minor_table[minor];
		अगर (dev && dev->hw_dev == hardware_device) अणु
			comedi_board_minor_table[minor] = शून्य;
			mutex_unlock(&comedi_board_minor_table_lock);
			comedi_मुक्त_board_dev(dev);
			अवरोध;
		पूर्ण
		mutex_unlock(&comedi_board_minor_table_lock);
	पूर्ण
पूर्ण

पूर्णांक comedi_alloc_subdevice_minor(काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_device *dev = s->device;
	काष्ठा device *csdev;
	अचिन्हित पूर्णांक i;

	mutex_lock(&comedi_subdevice_minor_table_lock);
	क्रम (i = 0; i < COMEDI_NUM_SUBDEVICE_MINORS; ++i) अणु
		अगर (!comedi_subdevice_minor_table[i]) अणु
			comedi_subdevice_minor_table[i] = s;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&comedi_subdevice_minor_table_lock);
	अगर (i == COMEDI_NUM_SUBDEVICE_MINORS) अणु
		dev_err(dev->class_dev,
			"ran out of minor numbers for subdevice files\n");
		वापस -EBUSY;
	पूर्ण
	i += COMEDI_NUM_BOARD_MINORS;
	s->minor = i;
	csdev = device_create(comedi_class, dev->class_dev,
			      MKDEV(COMEDI_MAJOR, i), शून्य, "comedi%i_subd%i",
			      dev->minor, s->index);
	अगर (!IS_ERR(csdev))
		s->class_dev = csdev;

	वापस 0;
पूर्ण

व्योम comedi_मुक्त_subdevice_minor(काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!s)
		वापस;
	अगर (s->minor < COMEDI_NUM_BOARD_MINORS ||
	    s->minor >= COMEDI_NUM_MINORS)
		वापस;

	i = s->minor - COMEDI_NUM_BOARD_MINORS;
	mutex_lock(&comedi_subdevice_minor_table_lock);
	अगर (s == comedi_subdevice_minor_table[i])
		comedi_subdevice_minor_table[i] = शून्य;
	mutex_unlock(&comedi_subdevice_minor_table_lock);
	अगर (s->class_dev) अणु
		device_destroy(comedi_class, MKDEV(COMEDI_MAJOR, s->minor));
		s->class_dev = शून्य;
	पूर्ण
पूर्ण

अटल व्योम comedi_cleanup_board_minors(व्योम)
अणु
	काष्ठा comedi_device *dev;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < COMEDI_NUM_BOARD_MINORS; i++) अणु
		dev = comedi_clear_board_minor(i);
		comedi_मुक्त_board_dev(dev);
	पूर्ण
पूर्ण

अटल पूर्णांक __init comedi_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक retval;

	pr_info("version " COMEDI_RELEASE " - http://www.comedi.org\n");

	अगर (comedi_num_legacy_minors > COMEDI_NUM_BOARD_MINORS) अणु
		pr_err("invalid value for module parameter \"comedi_num_legacy_minors\".  Valid values are 0 through %i.\n",
		       COMEDI_NUM_BOARD_MINORS);
		वापस -EINVAL;
	पूर्ण

	retval = रेजिस्टर_chrdev_region(MKDEV(COMEDI_MAJOR, 0),
					COMEDI_NUM_MINORS, "comedi");
	अगर (retval)
		वापस retval;

	cdev_init(&comedi_cdev, &comedi_fops);
	comedi_cdev.owner = THIS_MODULE;

	retval = kobject_set_name(&comedi_cdev.kobj, "comedi");
	अगर (retval)
		जाओ out_unरेजिस्टर_chrdev_region;

	retval = cdev_add(&comedi_cdev, MKDEV(COMEDI_MAJOR, 0),
			  COMEDI_NUM_MINORS);
	अगर (retval)
		जाओ out_unरेजिस्टर_chrdev_region;

	comedi_class = class_create(THIS_MODULE, "comedi");
	अगर (IS_ERR(comedi_class)) अणु
		retval = PTR_ERR(comedi_class);
		pr_err("failed to create class\n");
		जाओ out_cdev_del;
	पूर्ण

	comedi_class->dev_groups = comedi_dev_groups;

	/* create devices files क्रम legacy/manual use */
	क्रम (i = 0; i < comedi_num_legacy_minors; i++) अणु
		काष्ठा comedi_device *dev;

		dev = comedi_alloc_board_minor(शून्य);
		अगर (IS_ERR(dev)) अणु
			retval = PTR_ERR(dev);
			जाओ out_cleanup_board_minors;
		पूर्ण
		/* comedi_alloc_board_minor() locked the mutex */
		lockdep_निश्चित_held(&dev->mutex);
		mutex_unlock(&dev->mutex);
	पूर्ण

	/* XXX requires /proc पूर्णांकerface */
	comedi_proc_init();

	वापस 0;

out_cleanup_board_minors:
	comedi_cleanup_board_minors();
	class_destroy(comedi_class);
out_cdev_del:
	cdev_del(&comedi_cdev);
out_unरेजिस्टर_chrdev_region:
	unरेजिस्टर_chrdev_region(MKDEV(COMEDI_MAJOR, 0), COMEDI_NUM_MINORS);
	वापस retval;
पूर्ण
module_init(comedi_init);

अटल व्योम __निकास comedi_cleanup(व्योम)
अणु
	comedi_cleanup_board_minors();
	class_destroy(comedi_class);
	cdev_del(&comedi_cdev);
	unरेजिस्टर_chrdev_region(MKDEV(COMEDI_MAJOR, 0), COMEDI_NUM_MINORS);

	comedi_proc_cleanup();
पूर्ण
module_निकास(comedi_cleanup);

MODULE_AUTHOR("https://www.comedi.org");
MODULE_DESCRIPTION("Comedi core module");
MODULE_LICENSE("GPL");
