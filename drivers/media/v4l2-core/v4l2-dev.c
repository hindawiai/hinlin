<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Video capture पूर्णांकerface क्रम Linux version 2
 *
 *	A generic video device पूर्णांकerface क्रम the LINUX operating प्रणाली
 *	using a set of device काष्ठाures/vectors क्रम low level operations.
 *
 * Authors:	Alan Cox, <alan@lxorguk.ukuu.org.uk> (version 1)
 *              Mauro Carvalho Chehab <mchehab@kernel.org> (version 2)
 *
 * Fixes:	20000516  Claudio Matsuoka <claudio@conectiva.com>
 *		- Added procfs support
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kmod.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>

#घोषणा VIDEO_NUM_DEVICES	256
#घोषणा VIDEO_NAME              "video4linux"

#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु					\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt),			\
		       __func__, ##arg);				\
पूर्ण जबतक (0)

अटल काष्ठा dentry *v4l2_debugfs_dir;

/*
 *	sysfs stuff
 */

अटल sमाप_प्रकार index_show(काष्ठा device *cd,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा video_device *vdev = to_video_device(cd);

	वापस प्र_लिखो(buf, "%i\n", vdev->index);
पूर्ण
अटल DEVICE_ATTR_RO(index);

अटल sमाप_प्रकार dev_debug_show(काष्ठा device *cd,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा video_device *vdev = to_video_device(cd);

	वापस प्र_लिखो(buf, "%i\n", vdev->dev_debug);
पूर्ण

अटल sमाप_प्रकार dev_debug_store(काष्ठा device *cd, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा video_device *vdev = to_video_device(cd);
	पूर्णांक res = 0;
	u16 value;

	res = kstrtou16(buf, 0, &value);
	अगर (res)
		वापस res;

	vdev->dev_debug = value;
	वापस len;
पूर्ण
अटल DEVICE_ATTR_RW(dev_debug);

अटल sमाप_प्रकार name_show(काष्ठा device *cd,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा video_device *vdev = to_video_device(cd);

	वापस प्र_लिखो(buf, "%.*s\n", (पूर्णांक)माप(vdev->name), vdev->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल काष्ठा attribute *video_device_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_dev_debug.attr,
	&dev_attr_index.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(video_device);

/*
 *	Active devices
 */
अटल काष्ठा video_device *video_devices[VIDEO_NUM_DEVICES];
अटल DEFINE_MUTEX(videodev_lock);
अटल DECLARE_BITMAP(devnode_nums[VFL_TYPE_MAX], VIDEO_NUM_DEVICES);

/* Device node utility functions */

/* Note: these utility functions all assume that vfl_type is in the range
   [0, VFL_TYPE_MAX-1]. */

#अगर_घोषित CONFIG_VIDEO_FIXED_MINOR_RANGES
/* Return the biपंचांगap corresponding to vfl_type. */
अटल अंतरभूत अचिन्हित दीर्घ *devnode_bits(क्रमागत vfl_devnode_type vfl_type)
अणु
	/* Any types not asचिन्हित to fixed minor ranges must be mapped to
	   one single biपंचांगap क्रम the purposes of finding a मुक्त node number
	   since all those unasचिन्हित types use the same minor range. */
	पूर्णांक idx = (vfl_type > VFL_TYPE_RADIO) ? VFL_TYPE_MAX - 1 : vfl_type;

	वापस devnode_nums[idx];
पूर्ण
#अन्यथा
/* Return the biपंचांगap corresponding to vfl_type. */
अटल अंतरभूत अचिन्हित दीर्घ *devnode_bits(क्रमागत vfl_devnode_type vfl_type)
अणु
	वापस devnode_nums[vfl_type];
पूर्ण
#पूर्ण_अगर

/* Mark device node number vdev->num as used */
अटल अंतरभूत व्योम devnode_set(काष्ठा video_device *vdev)
अणु
	set_bit(vdev->num, devnode_bits(vdev->vfl_type));
पूर्ण

/* Mark device node number vdev->num as unused */
अटल अंतरभूत व्योम devnode_clear(काष्ठा video_device *vdev)
अणु
	clear_bit(vdev->num, devnode_bits(vdev->vfl_type));
पूर्ण

/* Try to find a मुक्त device node number in the range [from, to> */
अटल अंतरभूत पूर्णांक devnode_find(काष्ठा video_device *vdev, पूर्णांक from, पूर्णांक to)
अणु
	वापस find_next_zero_bit(devnode_bits(vdev->vfl_type), to, from);
पूर्ण

काष्ठा video_device *video_device_alloc(व्योम)
अणु
	वापस kzalloc(माप(काष्ठा video_device), GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL(video_device_alloc);

व्योम video_device_release(काष्ठा video_device *vdev)
अणु
	kमुक्त(vdev);
पूर्ण
EXPORT_SYMBOL(video_device_release);

व्योम video_device_release_empty(काष्ठा video_device *vdev)
अणु
	/* Do nothing */
	/* Only valid when the video_device काष्ठा is a अटल. */
पूर्ण
EXPORT_SYMBOL(video_device_release_empty);

अटल अंतरभूत व्योम video_get(काष्ठा video_device *vdev)
अणु
	get_device(&vdev->dev);
पूर्ण

अटल अंतरभूत व्योम video_put(काष्ठा video_device *vdev)
अणु
	put_device(&vdev->dev);
पूर्ण

/* Called when the last user of the video device निकासs. */
अटल व्योम v4l2_device_release(काष्ठा device *cd)
अणु
	काष्ठा video_device *vdev = to_video_device(cd);
	काष्ठा v4l2_device *v4l2_dev = vdev->v4l2_dev;

	mutex_lock(&videodev_lock);
	अगर (WARN_ON(video_devices[vdev->minor] != vdev)) अणु
		/* should not happen */
		mutex_unlock(&videodev_lock);
		वापस;
	पूर्ण

	/* Free up this device क्रम reuse */
	video_devices[vdev->minor] = शून्य;

	/* Delete the cdev on this minor as well */
	cdev_del(vdev->cdev);
	/* Just in हाल some driver tries to access this from
	   the release() callback. */
	vdev->cdev = शून्य;

	/* Mark device node number as मुक्त */
	devnode_clear(vdev);

	mutex_unlock(&videodev_lock);

#अगर defined(CONFIG_MEDIA_CONTROLLER)
	अगर (v4l2_dev->mdev && vdev->vfl_dir != VFL_सूची_M2M) अणु
		/* Remove पूर्णांकerfaces and पूर्णांकerface links */
		media_devnode_हटाओ(vdev->पूर्णांकf_devnode);
		अगर (vdev->entity.function != MEDIA_ENT_F_UNKNOWN)
			media_device_unरेजिस्टर_entity(&vdev->entity);
	पूर्ण
#पूर्ण_अगर

	/* Do not call v4l2_device_put अगर there is no release callback set.
	 * Drivers that have no v4l2_device release callback might मुक्त the
	 * v4l2_dev instance in the video_device release callback below, so we
	 * must perक्रमm this check here.
	 *
	 * TODO: In the दीर्घ run all drivers that use v4l2_device should use the
	 * v4l2_device release callback. This check will then be unnecessary.
	 */
	अगर (v4l2_dev->release == शून्य)
		v4l2_dev = शून्य;

	/* Release video_device and perक्रमm other
	   cleanups as needed. */
	vdev->release(vdev);

	/* Decrease v4l2_device refcount */
	अगर (v4l2_dev)
		v4l2_device_put(v4l2_dev);
पूर्ण

अटल काष्ठा class video_class = अणु
	.name = VIDEO_NAME,
	.dev_groups = video_device_groups,
पूर्ण;

काष्ठा video_device *video_devdata(काष्ठा file *file)
अणु
	वापस video_devices[iminor(file_inode(file))];
पूर्ण
EXPORT_SYMBOL(video_devdata);


/* Priority handling */

अटल अंतरभूत bool prio_is_valid(क्रमागत v4l2_priority prio)
अणु
	वापस prio == V4L2_PRIORITY_BACKGROUND ||
	       prio == V4L2_PRIORITY_INTERACTIVE ||
	       prio == V4L2_PRIORITY_RECORD;
पूर्ण

व्योम v4l2_prio_init(काष्ठा v4l2_prio_state *global)
अणु
	स_रखो(global, 0, माप(*global));
पूर्ण
EXPORT_SYMBOL(v4l2_prio_init);

पूर्णांक v4l2_prio_change(काष्ठा v4l2_prio_state *global, क्रमागत v4l2_priority *local,
		     क्रमागत v4l2_priority new)
अणु
	अगर (!prio_is_valid(new))
		वापस -EINVAL;
	अगर (*local == new)
		वापस 0;

	atomic_inc(&global->prios[new]);
	अगर (prio_is_valid(*local))
		atomic_dec(&global->prios[*local]);
	*local = new;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(v4l2_prio_change);

व्योम v4l2_prio_खोलो(काष्ठा v4l2_prio_state *global, क्रमागत v4l2_priority *local)
अणु
	v4l2_prio_change(global, local, V4L2_PRIORITY_DEFAULT);
पूर्ण
EXPORT_SYMBOL(v4l2_prio_खोलो);

व्योम v4l2_prio_बंद(काष्ठा v4l2_prio_state *global, क्रमागत v4l2_priority local)
अणु
	अगर (prio_is_valid(local))
		atomic_dec(&global->prios[local]);
पूर्ण
EXPORT_SYMBOL(v4l2_prio_बंद);

क्रमागत v4l2_priority v4l2_prio_max(काष्ठा v4l2_prio_state *global)
अणु
	अगर (atomic_पढ़ो(&global->prios[V4L2_PRIORITY_RECORD]) > 0)
		वापस V4L2_PRIORITY_RECORD;
	अगर (atomic_पढ़ो(&global->prios[V4L2_PRIORITY_INTERACTIVE]) > 0)
		वापस V4L2_PRIORITY_INTERACTIVE;
	अगर (atomic_पढ़ो(&global->prios[V4L2_PRIORITY_BACKGROUND]) > 0)
		वापस V4L2_PRIORITY_BACKGROUND;
	वापस V4L2_PRIORITY_UNSET;
पूर्ण
EXPORT_SYMBOL(v4l2_prio_max);

पूर्णांक v4l2_prio_check(काष्ठा v4l2_prio_state *global, क्रमागत v4l2_priority local)
अणु
	वापस (local < v4l2_prio_max(global)) ? -EBUSY : 0;
पूर्ण
EXPORT_SYMBOL(v4l2_prio_check);


अटल sमाप_प्रकार v4l2_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
		माप_प्रकार sz, loff_t *off)
अणु
	काष्ठा video_device *vdev = video_devdata(filp);
	पूर्णांक ret = -ENODEV;

	अगर (!vdev->fops->पढ़ो)
		वापस -EINVAL;
	अगर (video_is_रेजिस्टरed(vdev))
		ret = vdev->fops->पढ़ो(filp, buf, sz, off);
	अगर ((vdev->dev_debug & V4L2_DEV_DEBUG_FOP) &&
	    (vdev->dev_debug & V4L2_DEV_DEBUG_STREAMING))
		dprपूर्णांकk("%s: read: %zd (%d)\n",
			video_device_node_name(vdev), sz, ret);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार v4l2_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
		माप_प्रकार sz, loff_t *off)
अणु
	काष्ठा video_device *vdev = video_devdata(filp);
	पूर्णांक ret = -ENODEV;

	अगर (!vdev->fops->ग_लिखो)
		वापस -EINVAL;
	अगर (video_is_रेजिस्टरed(vdev))
		ret = vdev->fops->ग_लिखो(filp, buf, sz, off);
	अगर ((vdev->dev_debug & V4L2_DEV_DEBUG_FOP) &&
	    (vdev->dev_debug & V4L2_DEV_DEBUG_STREAMING))
		dprपूर्णांकk("%s: write: %zd (%d)\n",
			video_device_node_name(vdev), sz, ret);
	वापस ret;
पूर्ण

अटल __poll_t v4l2_poll(काष्ठा file *filp, काष्ठा poll_table_काष्ठा *poll)
अणु
	काष्ठा video_device *vdev = video_devdata(filp);
	__poll_t res = EPOLLERR | EPOLLHUP | EPOLLPRI;

	अगर (video_is_रेजिस्टरed(vdev)) अणु
		अगर (!vdev->fops->poll)
			res = DEFAULT_POLLMASK;
		अन्यथा
			res = vdev->fops->poll(filp, poll);
	पूर्ण
	अगर (vdev->dev_debug & V4L2_DEV_DEBUG_POLL)
		dprपूर्णांकk("%s: poll: %08x %08x\n",
			video_device_node_name(vdev), res,
			poll_requested_events(poll));
	वापस res;
पूर्ण

अटल दीर्घ v4l2_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा video_device *vdev = video_devdata(filp);
	पूर्णांक ret = -ENODEV;

	अगर (vdev->fops->unlocked_ioctl) अणु
		अगर (video_is_रेजिस्टरed(vdev))
			ret = vdev->fops->unlocked_ioctl(filp, cmd, arg);
	पूर्ण अन्यथा
		ret = -ENOTTY;

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_MMU
#घोषणा v4l2_get_unmapped_area शून्य
#अन्यथा
अटल अचिन्हित दीर्घ v4l2_get_unmapped_area(काष्ठा file *filp,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा video_device *vdev = video_devdata(filp);
	पूर्णांक ret;

	अगर (!vdev->fops->get_unmapped_area)
		वापस -ENOSYS;
	अगर (!video_is_रेजिस्टरed(vdev))
		वापस -ENODEV;
	ret = vdev->fops->get_unmapped_area(filp, addr, len, pgoff, flags);
	अगर (vdev->dev_debug & V4L2_DEV_DEBUG_FOP)
		dprपूर्णांकk("%s: get_unmapped_area (%d)\n",
			video_device_node_name(vdev), ret);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक v4l2_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vm)
अणु
	काष्ठा video_device *vdev = video_devdata(filp);
	पूर्णांक ret = -ENODEV;

	अगर (!vdev->fops->mmap)
		वापस -ENODEV;
	अगर (video_is_रेजिस्टरed(vdev))
		ret = vdev->fops->mmap(filp, vm);
	अगर (vdev->dev_debug & V4L2_DEV_DEBUG_FOP)
		dprपूर्णांकk("%s: mmap (%d)\n",
			video_device_node_name(vdev), ret);
	वापस ret;
पूर्ण

/* Override क्रम the खोलो function */
अटल पूर्णांक v4l2_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा video_device *vdev;
	पूर्णांक ret = 0;

	/* Check अगर the video device is available */
	mutex_lock(&videodev_lock);
	vdev = video_devdata(filp);
	/* वापस ENODEV अगर the video device has alपढ़ोy been हटाओd. */
	अगर (vdev == शून्य || !video_is_रेजिस्टरed(vdev)) अणु
		mutex_unlock(&videodev_lock);
		वापस -ENODEV;
	पूर्ण
	/* and increase the device refcount */
	video_get(vdev);
	mutex_unlock(&videodev_lock);
	अगर (vdev->fops->खोलो) अणु
		अगर (video_is_रेजिस्टरed(vdev))
			ret = vdev->fops->खोलो(filp);
		अन्यथा
			ret = -ENODEV;
	पूर्ण

	अगर (vdev->dev_debug & V4L2_DEV_DEBUG_FOP)
		dprपूर्णांकk("%s: open (%d)\n",
			video_device_node_name(vdev), ret);
	/* decrease the refcount in हाल of an error */
	अगर (ret)
		video_put(vdev);
	वापस ret;
पूर्ण

/* Override क्रम the release function */
अटल पूर्णांक v4l2_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा video_device *vdev = video_devdata(filp);
	पूर्णांक ret = 0;

	/*
	 * We need to serialize the release() with queueing new requests.
	 * The release() may trigger the cancellation of a streaming
	 * operation, and that should not be mixed with queueing a new
	 * request at the same समय.
	 */
	अगर (vdev->fops->release) अणु
		अगर (v4l2_device_supports_requests(vdev->v4l2_dev)) अणु
			mutex_lock(&vdev->v4l2_dev->mdev->req_queue_mutex);
			ret = vdev->fops->release(filp);
			mutex_unlock(&vdev->v4l2_dev->mdev->req_queue_mutex);
		पूर्ण अन्यथा अणु
			ret = vdev->fops->release(filp);
		पूर्ण
	पूर्ण

	अगर (vdev->dev_debug & V4L2_DEV_DEBUG_FOP)
		dprपूर्णांकk("%s: release\n",
			video_device_node_name(vdev));

	/* decrease the refcount unconditionally since the release()
	   वापस value is ignored. */
	video_put(vdev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations v4l2_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = v4l2_पढ़ो,
	.ग_लिखो = v4l2_ग_लिखो,
	.खोलो = v4l2_खोलो,
	.get_unmapped_area = v4l2_get_unmapped_area,
	.mmap = v4l2_mmap,
	.unlocked_ioctl = v4l2_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = v4l2_compat_ioctl32,
#पूर्ण_अगर
	.release = v4l2_release,
	.poll = v4l2_poll,
	.llseek = no_llseek,
पूर्ण;

/**
 * get_index - assign stream index number based on v4l2_dev
 * @vdev: video_device to assign index number to, vdev->v4l2_dev should be asचिन्हित
 *
 * Note that when this is called the new device has not yet been रेजिस्टरed
 * in the video_device array, but it was able to obtain a minor number.
 *
 * This means that we can always obtain a मुक्त stream index number since
 * the worst हाल scenario is that there are VIDEO_NUM_DEVICES - 1 slots in
 * use of the video_device array.
 *
 * Returns a मुक्त index number.
 */
अटल पूर्णांक get_index(काष्ठा video_device *vdev)
अणु
	/* This can be अटल since this function is called with the global
	   videodev_lock held. */
	अटल DECLARE_BITMAP(used, VIDEO_NUM_DEVICES);
	पूर्णांक i;

	biपंचांगap_zero(used, VIDEO_NUM_DEVICES);

	क्रम (i = 0; i < VIDEO_NUM_DEVICES; i++) अणु
		अगर (video_devices[i] != शून्य &&
		    video_devices[i]->v4l2_dev == vdev->v4l2_dev) अणु
			set_bit(video_devices[i]->index, used);
		पूर्ण
	पूर्ण

	वापस find_first_zero_bit(used, VIDEO_NUM_DEVICES);
पूर्ण

#घोषणा SET_VALID_IOCTL(ops, cmd, op)			\
	अगर (ops->op)					\
		set_bit(_IOC_NR(cmd), valid_ioctls)

/* This determines which ioctls are actually implemented in the driver.
   It's a one-समय thing which simplअगरies video_ioctl2 as it can just करो
   a bit test.

   Note that drivers can override this by setting bits to 1 in
   vdev->valid_ioctls. If an ioctl is marked as 1 when this function is
   called, then that ioctl will actually be marked as unimplemented.

   It करोes that by first setting up the local valid_ioctls biपंचांगap, and
   at the end करो a:

   vdev->valid_ioctls = valid_ioctls & ~(vdev->valid_ioctls)
 */
अटल व्योम determine_valid_ioctls(काष्ठा video_device *vdev)
अणु
	स्थिर u32 vid_caps = V4L2_CAP_VIDEO_CAPTURE |
			     V4L2_CAP_VIDEO_CAPTURE_MPLANE |
			     V4L2_CAP_VIDEO_OUTPUT |
			     V4L2_CAP_VIDEO_OUTPUT_MPLANE |
			     V4L2_CAP_VIDEO_M2M | V4L2_CAP_VIDEO_M2M_MPLANE;
	स्थिर u32 meta_caps = V4L2_CAP_META_CAPTURE |
			      V4L2_CAP_META_OUTPUT;
	DECLARE_BITMAP(valid_ioctls, BASE_VIDIOC_PRIVATE);
	स्थिर काष्ठा v4l2_ioctl_ops *ops = vdev->ioctl_ops;
	bool is_vid = vdev->vfl_type == VFL_TYPE_VIDEO &&
		      (vdev->device_caps & vid_caps);
	bool is_vbi = vdev->vfl_type == VFL_TYPE_VBI;
	bool is_radio = vdev->vfl_type == VFL_TYPE_RADIO;
	bool is_sdr = vdev->vfl_type == VFL_TYPE_SDR;
	bool is_tch = vdev->vfl_type == VFL_TYPE_TOUCH;
	bool is_meta = vdev->vfl_type == VFL_TYPE_VIDEO &&
		       (vdev->device_caps & meta_caps);
	bool is_rx = vdev->vfl_dir != VFL_सूची_TX;
	bool is_tx = vdev->vfl_dir != VFL_सूची_RX;
	bool is_io_mc = vdev->device_caps & V4L2_CAP_IO_MC;

	biपंचांगap_zero(valid_ioctls, BASE_VIDIOC_PRIVATE);

	/* vfl_type and vfl_dir independent ioctls */

	SET_VALID_IOCTL(ops, VIDIOC_QUERYCAP, vidioc_querycap);
	set_bit(_IOC_NR(VIDIOC_G_PRIORITY), valid_ioctls);
	set_bit(_IOC_NR(VIDIOC_S_PRIORITY), valid_ioctls);

	/* Note: the control handler can also be passed through the filehandle,
	   and that can't be tested here. If the bit क्रम these control ioctls
	   is set, then the ioctl is valid. But अगर it is 0, then it can still
	   be valid अगर the filehandle passed the control handler. */
	अगर (vdev->ctrl_handler || ops->vidioc_queryctrl)
		set_bit(_IOC_NR(VIDIOC_QUERYCTRL), valid_ioctls);
	अगर (vdev->ctrl_handler || ops->vidioc_query_ext_ctrl)
		set_bit(_IOC_NR(VIDIOC_QUERY_EXT_CTRL), valid_ioctls);
	अगर (vdev->ctrl_handler || ops->vidioc_g_ctrl || ops->vidioc_g_ext_ctrls)
		set_bit(_IOC_NR(VIDIOC_G_CTRL), valid_ioctls);
	अगर (vdev->ctrl_handler || ops->vidioc_s_ctrl || ops->vidioc_s_ext_ctrls)
		set_bit(_IOC_NR(VIDIOC_S_CTRL), valid_ioctls);
	अगर (vdev->ctrl_handler || ops->vidioc_g_ext_ctrls)
		set_bit(_IOC_NR(VIDIOC_G_EXT_CTRLS), valid_ioctls);
	अगर (vdev->ctrl_handler || ops->vidioc_s_ext_ctrls)
		set_bit(_IOC_NR(VIDIOC_S_EXT_CTRLS), valid_ioctls);
	अगर (vdev->ctrl_handler || ops->vidioc_try_ext_ctrls)
		set_bit(_IOC_NR(VIDIOC_TRY_EXT_CTRLS), valid_ioctls);
	अगर (vdev->ctrl_handler || ops->vidioc_querymenu)
		set_bit(_IOC_NR(VIDIOC_QUERYMENU), valid_ioctls);
	अगर (!is_tch) अणु
		SET_VALID_IOCTL(ops, VIDIOC_G_FREQUENCY, vidioc_g_frequency);
		SET_VALID_IOCTL(ops, VIDIOC_S_FREQUENCY, vidioc_s_frequency);
	पूर्ण
	SET_VALID_IOCTL(ops, VIDIOC_LOG_STATUS, vidioc_log_status);
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	set_bit(_IOC_NR(VIDIOC_DBG_G_CHIP_INFO), valid_ioctls);
	set_bit(_IOC_NR(VIDIOC_DBG_G_REGISTER), valid_ioctls);
	set_bit(_IOC_NR(VIDIOC_DBG_S_REGISTER), valid_ioctls);
#पूर्ण_अगर
	/* yes, really vidioc_subscribe_event */
	SET_VALID_IOCTL(ops, VIDIOC_DQEVENT, vidioc_subscribe_event);
	SET_VALID_IOCTL(ops, VIDIOC_SUBSCRIBE_EVENT, vidioc_subscribe_event);
	SET_VALID_IOCTL(ops, VIDIOC_UNSUBSCRIBE_EVENT, vidioc_unsubscribe_event);
	अगर (ops->vidioc_क्रमागत_freq_bands || ops->vidioc_g_tuner || ops->vidioc_g_modulator)
		set_bit(_IOC_NR(VIDIOC_ENUM_FREQ_BANDS), valid_ioctls);

	अगर (is_vid) अणु
		/* video specअगरic ioctls */
		अगर ((is_rx && (ops->vidioc_क्रमागत_fmt_vid_cap ||
			       ops->vidioc_क्रमागत_fmt_vid_overlay)) ||
		    (is_tx && ops->vidioc_क्रमागत_fmt_vid_out))
			set_bit(_IOC_NR(VIDIOC_ENUM_FMT), valid_ioctls);
		अगर ((is_rx && (ops->vidioc_g_fmt_vid_cap ||
			       ops->vidioc_g_fmt_vid_cap_mplane ||
			       ops->vidioc_g_fmt_vid_overlay)) ||
		    (is_tx && (ops->vidioc_g_fmt_vid_out ||
			       ops->vidioc_g_fmt_vid_out_mplane ||
			       ops->vidioc_g_fmt_vid_out_overlay)))
			 set_bit(_IOC_NR(VIDIOC_G_FMT), valid_ioctls);
		अगर ((is_rx && (ops->vidioc_s_fmt_vid_cap ||
			       ops->vidioc_s_fmt_vid_cap_mplane ||
			       ops->vidioc_s_fmt_vid_overlay)) ||
		    (is_tx && (ops->vidioc_s_fmt_vid_out ||
			       ops->vidioc_s_fmt_vid_out_mplane ||
			       ops->vidioc_s_fmt_vid_out_overlay)))
			 set_bit(_IOC_NR(VIDIOC_S_FMT), valid_ioctls);
		अगर ((is_rx && (ops->vidioc_try_fmt_vid_cap ||
			       ops->vidioc_try_fmt_vid_cap_mplane ||
			       ops->vidioc_try_fmt_vid_overlay)) ||
		    (is_tx && (ops->vidioc_try_fmt_vid_out ||
			       ops->vidioc_try_fmt_vid_out_mplane ||
			       ops->vidioc_try_fmt_vid_out_overlay)))
			 set_bit(_IOC_NR(VIDIOC_TRY_FMT), valid_ioctls);
		SET_VALID_IOCTL(ops, VIDIOC_OVERLAY, vidioc_overlay);
		SET_VALID_IOCTL(ops, VIDIOC_G_FBUF, vidioc_g_fbuf);
		SET_VALID_IOCTL(ops, VIDIOC_S_FBUF, vidioc_s_fbuf);
		SET_VALID_IOCTL(ops, VIDIOC_G_JPEGCOMP, vidioc_g_jpegcomp);
		SET_VALID_IOCTL(ops, VIDIOC_S_JPEGCOMP, vidioc_s_jpegcomp);
		SET_VALID_IOCTL(ops, VIDIOC_G_ENC_INDEX, vidioc_g_enc_index);
		SET_VALID_IOCTL(ops, VIDIOC_ENCODER_CMD, vidioc_encoder_cmd);
		SET_VALID_IOCTL(ops, VIDIOC_TRY_ENCODER_CMD, vidioc_try_encoder_cmd);
		SET_VALID_IOCTL(ops, VIDIOC_DECODER_CMD, vidioc_decoder_cmd);
		SET_VALID_IOCTL(ops, VIDIOC_TRY_DECODER_CMD, vidioc_try_decoder_cmd);
		SET_VALID_IOCTL(ops, VIDIOC_ENUM_FRAMESIZES, vidioc_क्रमागत_framesizes);
		SET_VALID_IOCTL(ops, VIDIOC_ENUM_FRAMEINTERVALS, vidioc_क्रमागत_frameपूर्णांकervals);
		अगर (ops->vidioc_g_selection) अणु
			set_bit(_IOC_NR(VIDIOC_G_CROP), valid_ioctls);
			set_bit(_IOC_NR(VIDIOC_CROPCAP), valid_ioctls);
		पूर्ण
		अगर (ops->vidioc_s_selection)
			set_bit(_IOC_NR(VIDIOC_S_CROP), valid_ioctls);
		SET_VALID_IOCTL(ops, VIDIOC_G_SELECTION, vidioc_g_selection);
		SET_VALID_IOCTL(ops, VIDIOC_S_SELECTION, vidioc_s_selection);
	पूर्ण
	अगर (is_meta && is_rx) अणु
		/* metadata capture specअगरic ioctls */
		SET_VALID_IOCTL(ops, VIDIOC_ENUM_FMT, vidioc_क्रमागत_fmt_meta_cap);
		SET_VALID_IOCTL(ops, VIDIOC_G_FMT, vidioc_g_fmt_meta_cap);
		SET_VALID_IOCTL(ops, VIDIOC_S_FMT, vidioc_s_fmt_meta_cap);
		SET_VALID_IOCTL(ops, VIDIOC_TRY_FMT, vidioc_try_fmt_meta_cap);
	पूर्ण अन्यथा अगर (is_meta && is_tx) अणु
		/* metadata output specअगरic ioctls */
		SET_VALID_IOCTL(ops, VIDIOC_ENUM_FMT, vidioc_क्रमागत_fmt_meta_out);
		SET_VALID_IOCTL(ops, VIDIOC_G_FMT, vidioc_g_fmt_meta_out);
		SET_VALID_IOCTL(ops, VIDIOC_S_FMT, vidioc_s_fmt_meta_out);
		SET_VALID_IOCTL(ops, VIDIOC_TRY_FMT, vidioc_try_fmt_meta_out);
	पूर्ण
	अगर (is_vbi) अणु
		/* vbi specअगरic ioctls */
		अगर ((is_rx && (ops->vidioc_g_fmt_vbi_cap ||
			       ops->vidioc_g_fmt_sliced_vbi_cap)) ||
		    (is_tx && (ops->vidioc_g_fmt_vbi_out ||
			       ops->vidioc_g_fmt_sliced_vbi_out)))
			set_bit(_IOC_NR(VIDIOC_G_FMT), valid_ioctls);
		अगर ((is_rx && (ops->vidioc_s_fmt_vbi_cap ||
			       ops->vidioc_s_fmt_sliced_vbi_cap)) ||
		    (is_tx && (ops->vidioc_s_fmt_vbi_out ||
			       ops->vidioc_s_fmt_sliced_vbi_out)))
			set_bit(_IOC_NR(VIDIOC_S_FMT), valid_ioctls);
		अगर ((is_rx && (ops->vidioc_try_fmt_vbi_cap ||
			       ops->vidioc_try_fmt_sliced_vbi_cap)) ||
		    (is_tx && (ops->vidioc_try_fmt_vbi_out ||
			       ops->vidioc_try_fmt_sliced_vbi_out)))
			set_bit(_IOC_NR(VIDIOC_TRY_FMT), valid_ioctls);
		SET_VALID_IOCTL(ops, VIDIOC_G_SLICED_VBI_CAP, vidioc_g_sliced_vbi_cap);
	पूर्ण अन्यथा अगर (is_tch) अणु
		/* touch specअगरic ioctls */
		SET_VALID_IOCTL(ops, VIDIOC_ENUM_FMT, vidioc_क्रमागत_fmt_vid_cap);
		SET_VALID_IOCTL(ops, VIDIOC_G_FMT, vidioc_g_fmt_vid_cap);
		SET_VALID_IOCTL(ops, VIDIOC_S_FMT, vidioc_s_fmt_vid_cap);
		SET_VALID_IOCTL(ops, VIDIOC_TRY_FMT, vidioc_try_fmt_vid_cap);
		SET_VALID_IOCTL(ops, VIDIOC_ENUM_FRAMESIZES, vidioc_क्रमागत_framesizes);
		SET_VALID_IOCTL(ops, VIDIOC_ENUM_FRAMEINTERVALS, vidioc_क्रमागत_frameपूर्णांकervals);
		SET_VALID_IOCTL(ops, VIDIOC_ENUMINPUT, vidioc_क्रमागत_input);
		SET_VALID_IOCTL(ops, VIDIOC_G_INPUT, vidioc_g_input);
		SET_VALID_IOCTL(ops, VIDIOC_S_INPUT, vidioc_s_input);
		SET_VALID_IOCTL(ops, VIDIOC_G_PARM, vidioc_g_parm);
		SET_VALID_IOCTL(ops, VIDIOC_S_PARM, vidioc_s_parm);
	पूर्ण अन्यथा अगर (is_sdr && is_rx) अणु
		/* SDR receiver specअगरic ioctls */
		SET_VALID_IOCTL(ops, VIDIOC_ENUM_FMT, vidioc_क्रमागत_fmt_sdr_cap);
		SET_VALID_IOCTL(ops, VIDIOC_G_FMT, vidioc_g_fmt_sdr_cap);
		SET_VALID_IOCTL(ops, VIDIOC_S_FMT, vidioc_s_fmt_sdr_cap);
		SET_VALID_IOCTL(ops, VIDIOC_TRY_FMT, vidioc_try_fmt_sdr_cap);
	पूर्ण अन्यथा अगर (is_sdr && is_tx) अणु
		/* SDR transmitter specअगरic ioctls */
		SET_VALID_IOCTL(ops, VIDIOC_ENUM_FMT, vidioc_क्रमागत_fmt_sdr_out);
		SET_VALID_IOCTL(ops, VIDIOC_G_FMT, vidioc_g_fmt_sdr_out);
		SET_VALID_IOCTL(ops, VIDIOC_S_FMT, vidioc_s_fmt_sdr_out);
		SET_VALID_IOCTL(ops, VIDIOC_TRY_FMT, vidioc_try_fmt_sdr_out);
	पूर्ण

	अगर (is_vid || is_vbi || is_sdr || is_tch || is_meta) अणु
		/* ioctls valid क्रम video, vbi, sdr, touch and metadata */
		SET_VALID_IOCTL(ops, VIDIOC_REQBUFS, vidioc_reqbufs);
		SET_VALID_IOCTL(ops, VIDIOC_QUERYBUF, vidioc_querybuf);
		SET_VALID_IOCTL(ops, VIDIOC_QBUF, vidioc_qbuf);
		SET_VALID_IOCTL(ops, VIDIOC_EXPBUF, vidioc_expbuf);
		SET_VALID_IOCTL(ops, VIDIOC_DQBUF, vidioc_dqbuf);
		SET_VALID_IOCTL(ops, VIDIOC_CREATE_BUFS, vidioc_create_bufs);
		SET_VALID_IOCTL(ops, VIDIOC_PREPARE_BUF, vidioc_prepare_buf);
		SET_VALID_IOCTL(ops, VIDIOC_STREAMON, vidioc_streamon);
		SET_VALID_IOCTL(ops, VIDIOC_STREAMOFF, vidioc_streamoff);
	पूर्ण

	अगर (is_vid || is_vbi || is_meta) अणु
		/* ioctls valid क्रम video, vbi and metadata */
		अगर (ops->vidioc_s_std)
			set_bit(_IOC_NR(VIDIOC_ENUMSTD), valid_ioctls);
		SET_VALID_IOCTL(ops, VIDIOC_S_STD, vidioc_s_std);
		SET_VALID_IOCTL(ops, VIDIOC_G_STD, vidioc_g_std);
		अगर (is_rx) अणु
			SET_VALID_IOCTL(ops, VIDIOC_QUERYSTD, vidioc_querystd);
			अगर (is_io_mc) अणु
				set_bit(_IOC_NR(VIDIOC_ENUMINPUT), valid_ioctls);
				set_bit(_IOC_NR(VIDIOC_G_INPUT), valid_ioctls);
				set_bit(_IOC_NR(VIDIOC_S_INPUT), valid_ioctls);
			पूर्ण अन्यथा अणु
				SET_VALID_IOCTL(ops, VIDIOC_ENUMINPUT, vidioc_क्रमागत_input);
				SET_VALID_IOCTL(ops, VIDIOC_G_INPUT, vidioc_g_input);
				SET_VALID_IOCTL(ops, VIDIOC_S_INPUT, vidioc_s_input);
			पूर्ण
			SET_VALID_IOCTL(ops, VIDIOC_ENUMAUDIO, vidioc_क्रमागतaudio);
			SET_VALID_IOCTL(ops, VIDIOC_G_AUDIO, vidioc_g_audio);
			SET_VALID_IOCTL(ops, VIDIOC_S_AUDIO, vidioc_s_audio);
			SET_VALID_IOCTL(ops, VIDIOC_QUERY_DV_TIMINGS, vidioc_query_dv_timings);
			SET_VALID_IOCTL(ops, VIDIOC_S_EDID, vidioc_s_edid);
		पूर्ण
		अगर (is_tx) अणु
			अगर (is_io_mc) अणु
				set_bit(_IOC_NR(VIDIOC_ENUMOUTPUT), valid_ioctls);
				set_bit(_IOC_NR(VIDIOC_G_OUTPUT), valid_ioctls);
				set_bit(_IOC_NR(VIDIOC_S_OUTPUT), valid_ioctls);
			पूर्ण अन्यथा अणु
				SET_VALID_IOCTL(ops, VIDIOC_ENUMOUTPUT, vidioc_क्रमागत_output);
				SET_VALID_IOCTL(ops, VIDIOC_G_OUTPUT, vidioc_g_output);
				SET_VALID_IOCTL(ops, VIDIOC_S_OUTPUT, vidioc_s_output);
			पूर्ण
			SET_VALID_IOCTL(ops, VIDIOC_ENUMAUDOUT, vidioc_क्रमागतauकरोut);
			SET_VALID_IOCTL(ops, VIDIOC_G_AUDOUT, vidioc_g_auकरोut);
			SET_VALID_IOCTL(ops, VIDIOC_S_AUDOUT, vidioc_s_auकरोut);
		पूर्ण
		अगर (ops->vidioc_g_parm || ops->vidioc_g_std)
			set_bit(_IOC_NR(VIDIOC_G_PARM), valid_ioctls);
		SET_VALID_IOCTL(ops, VIDIOC_S_PARM, vidioc_s_parm);
		SET_VALID_IOCTL(ops, VIDIOC_S_DV_TIMINGS, vidioc_s_dv_timings);
		SET_VALID_IOCTL(ops, VIDIOC_G_DV_TIMINGS, vidioc_g_dv_timings);
		SET_VALID_IOCTL(ops, VIDIOC_ENUM_DV_TIMINGS, vidioc_क्रमागत_dv_timings);
		SET_VALID_IOCTL(ops, VIDIOC_DV_TIMINGS_CAP, vidioc_dv_timings_cap);
		SET_VALID_IOCTL(ops, VIDIOC_G_EDID, vidioc_g_edid);
	पूर्ण
	अगर (is_tx && (is_radio || is_sdr)) अणु
		/* radio transmitter only ioctls */
		SET_VALID_IOCTL(ops, VIDIOC_G_MODULATOR, vidioc_g_modulator);
		SET_VALID_IOCTL(ops, VIDIOC_S_MODULATOR, vidioc_s_modulator);
	पूर्ण
	अगर (is_rx && !is_tch) अणु
		/* receiver only ioctls */
		SET_VALID_IOCTL(ops, VIDIOC_G_TUNER, vidioc_g_tuner);
		SET_VALID_IOCTL(ops, VIDIOC_S_TUNER, vidioc_s_tuner);
		SET_VALID_IOCTL(ops, VIDIOC_S_HW_FREQ_SEEK, vidioc_s_hw_freq_seek);
	पूर्ण

	biपंचांगap_andnot(vdev->valid_ioctls, valid_ioctls, vdev->valid_ioctls,
			BASE_VIDIOC_PRIVATE);
पूर्ण

अटल पूर्णांक video_रेजिस्टर_media_controller(काष्ठा video_device *vdev)
अणु
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	u32 पूर्णांकf_type;
	पूर्णांक ret;

	/* Memory-to-memory devices are more complex and use
	 * their own function to रेजिस्टर its mc entities.
	 */
	अगर (!vdev->v4l2_dev->mdev || vdev->vfl_dir == VFL_सूची_M2M)
		वापस 0;

	vdev->entity.obj_type = MEDIA_ENTITY_TYPE_VIDEO_DEVICE;
	vdev->entity.function = MEDIA_ENT_F_UNKNOWN;

	चयन (vdev->vfl_type) अणु
	हाल VFL_TYPE_VIDEO:
		पूर्णांकf_type = MEDIA_INTF_T_V4L_VIDEO;
		vdev->entity.function = MEDIA_ENT_F_IO_V4L;
		अवरोध;
	हाल VFL_TYPE_VBI:
		पूर्णांकf_type = MEDIA_INTF_T_V4L_VBI;
		vdev->entity.function = MEDIA_ENT_F_IO_VBI;
		अवरोध;
	हाल VFL_TYPE_SDR:
		पूर्णांकf_type = MEDIA_INTF_T_V4L_SWRADIO;
		vdev->entity.function = MEDIA_ENT_F_IO_SWRADIO;
		अवरोध;
	हाल VFL_TYPE_TOUCH:
		पूर्णांकf_type = MEDIA_INTF_T_V4L_TOUCH;
		vdev->entity.function = MEDIA_ENT_F_IO_V4L;
		अवरोध;
	हाल VFL_TYPE_RADIO:
		पूर्णांकf_type = MEDIA_INTF_T_V4L_RADIO;
		/*
		 * Radio करोesn't have an entity at the V4L2 side to represent
		 * radio input or output. Instead, the audio input/output goes
		 * via either physical wires or ALSA.
		 */
		अवरोध;
	हाल VFL_TYPE_SUBDEV:
		पूर्णांकf_type = MEDIA_INTF_T_V4L_SUBDEV;
		/* Entity will be created via v4l2_device_रेजिस्टर_subdev() */
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (vdev->entity.function != MEDIA_ENT_F_UNKNOWN) अणु
		vdev->entity.name = vdev->name;

		/* Needed just क्रम backward compatibility with legacy MC API */
		vdev->entity.info.dev.major = VIDEO_MAJOR;
		vdev->entity.info.dev.minor = vdev->minor;

		ret = media_device_रेजिस्टर_entity(vdev->v4l2_dev->mdev,
						   &vdev->entity);
		अगर (ret < 0) अणु
			pr_warn("%s: media_device_register_entity failed\n",
				__func__);
			वापस ret;
		पूर्ण
	पूर्ण

	vdev->पूर्णांकf_devnode = media_devnode_create(vdev->v4l2_dev->mdev,
						  पूर्णांकf_type,
						  0, VIDEO_MAJOR,
						  vdev->minor);
	अगर (!vdev->पूर्णांकf_devnode) अणु
		media_device_unरेजिस्टर_entity(&vdev->entity);
		वापस -ENOMEM;
	पूर्ण

	अगर (vdev->entity.function != MEDIA_ENT_F_UNKNOWN) अणु
		काष्ठा media_link *link;

		link = media_create_पूर्णांकf_link(&vdev->entity,
					      &vdev->पूर्णांकf_devnode->पूर्णांकf,
					      MEDIA_LNK_FL_ENABLED |
					      MEDIA_LNK_FL_IMMUTABLE);
		अगर (!link) अणु
			media_devnode_हटाओ(vdev->पूर्णांकf_devnode);
			media_device_unरेजिस्टर_entity(&vdev->entity);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* FIXME: how to create the other पूर्णांकerface links? */

#पूर्ण_अगर
	वापस 0;
पूर्ण

पूर्णांक __video_रेजिस्टर_device(काष्ठा video_device *vdev,
			    क्रमागत vfl_devnode_type type,
			    पूर्णांक nr, पूर्णांक warn_अगर_nr_in_use,
			    काष्ठा module *owner)
अणु
	पूर्णांक i = 0;
	पूर्णांक ret;
	पूर्णांक minor_offset = 0;
	पूर्णांक minor_cnt = VIDEO_NUM_DEVICES;
	स्थिर अक्षर *name_base;

	/* A minor value of -1 marks this video device as never
	   having been रेजिस्टरed */
	vdev->minor = -1;

	/* the release callback MUST be present */
	अगर (WARN_ON(!vdev->release))
		वापस -EINVAL;
	/* the v4l2_dev poपूर्णांकer MUST be present */
	अगर (WARN_ON(!vdev->v4l2_dev))
		वापस -EINVAL;
	/* the device_caps field MUST be set क्रम all but subdevs */
	अगर (WARN_ON(type != VFL_TYPE_SUBDEV && !vdev->device_caps))
		वापस -EINVAL;

	/* v4l2_fh support */
	spin_lock_init(&vdev->fh_lock);
	INIT_LIST_HEAD(&vdev->fh_list);

	/* Part 1: check device type */
	चयन (type) अणु
	हाल VFL_TYPE_VIDEO:
		name_base = "video";
		अवरोध;
	हाल VFL_TYPE_VBI:
		name_base = "vbi";
		अवरोध;
	हाल VFL_TYPE_RADIO:
		name_base = "radio";
		अवरोध;
	हाल VFL_TYPE_SUBDEV:
		name_base = "v4l-subdev";
		अवरोध;
	हाल VFL_TYPE_SDR:
		/* Use device name 'swradio' because 'sdr' was alपढ़ोy taken. */
		name_base = "swradio";
		अवरोध;
	हाल VFL_TYPE_TOUCH:
		name_base = "v4l-touch";
		अवरोध;
	शेष:
		pr_err("%s called with unknown type: %d\n",
		       __func__, type);
		वापस -EINVAL;
	पूर्ण

	vdev->vfl_type = type;
	vdev->cdev = शून्य;
	अगर (vdev->dev_parent == शून्य)
		vdev->dev_parent = vdev->v4l2_dev->dev;
	अगर (vdev->ctrl_handler == शून्य)
		vdev->ctrl_handler = vdev->v4l2_dev->ctrl_handler;
	/* If the prio state poपूर्णांकer is शून्य, then use the v4l2_device
	   prio state. */
	अगर (vdev->prio == शून्य)
		vdev->prio = &vdev->v4l2_dev->prio;

	/* Part 2: find a मुक्त minor, device node number and device index. */
#अगर_घोषित CONFIG_VIDEO_FIXED_MINOR_RANGES
	/* Keep the ranges क्रम the first four types क्रम historical
	 * reasons.
	 * Newer devices (not yet in place) should use the range
	 * of 128-191 and just pick the first मुक्त minor there
	 * (new style). */
	चयन (type) अणु
	हाल VFL_TYPE_VIDEO:
		minor_offset = 0;
		minor_cnt = 64;
		अवरोध;
	हाल VFL_TYPE_RADIO:
		minor_offset = 64;
		minor_cnt = 64;
		अवरोध;
	हाल VFL_TYPE_VBI:
		minor_offset = 224;
		minor_cnt = 32;
		अवरोध;
	शेष:
		minor_offset = 128;
		minor_cnt = 64;
		अवरोध;
	पूर्ण
#पूर्ण_अगर

	/* Pick a device node number */
	mutex_lock(&videodev_lock);
	nr = devnode_find(vdev, nr == -1 ? 0 : nr, minor_cnt);
	अगर (nr == minor_cnt)
		nr = devnode_find(vdev, 0, minor_cnt);
	अगर (nr == minor_cnt) अणु
		pr_err("could not get a free device node number\n");
		mutex_unlock(&videodev_lock);
		वापस -ENखाता;
	पूर्ण
#अगर_घोषित CONFIG_VIDEO_FIXED_MINOR_RANGES
	/* 1-on-1 mapping of device node number to minor number */
	i = nr;
#अन्यथा
	/* The device node number and minor numbers are independent, so
	   we just find the first मुक्त minor number. */
	क्रम (i = 0; i < VIDEO_NUM_DEVICES; i++)
		अगर (video_devices[i] == शून्य)
			अवरोध;
	अगर (i == VIDEO_NUM_DEVICES) अणु
		mutex_unlock(&videodev_lock);
		pr_err("could not get a free minor\n");
		वापस -ENखाता;
	पूर्ण
#पूर्ण_अगर
	vdev->minor = i + minor_offset;
	vdev->num = nr;

	/* Should not happen since we thought this minor was मुक्त */
	अगर (WARN_ON(video_devices[vdev->minor])) अणु
		mutex_unlock(&videodev_lock);
		pr_err("video_device not empty!\n");
		वापस -ENखाता;
	पूर्ण
	devnode_set(vdev);
	vdev->index = get_index(vdev);
	video_devices[vdev->minor] = vdev;
	mutex_unlock(&videodev_lock);

	अगर (vdev->ioctl_ops)
		determine_valid_ioctls(vdev);

	/* Part 3: Initialize the अक्षरacter device */
	vdev->cdev = cdev_alloc();
	अगर (vdev->cdev == शून्य) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण
	vdev->cdev->ops = &v4l2_fops;
	vdev->cdev->owner = owner;
	ret = cdev_add(vdev->cdev, MKDEV(VIDEO_MAJOR, vdev->minor), 1);
	अगर (ret < 0) अणु
		pr_err("%s: cdev_add failed\n", __func__);
		kमुक्त(vdev->cdev);
		vdev->cdev = शून्य;
		जाओ cleanup;
	पूर्ण

	/* Part 4: रेजिस्टर the device with sysfs */
	vdev->dev.class = &video_class;
	vdev->dev.devt = MKDEV(VIDEO_MAJOR, vdev->minor);
	vdev->dev.parent = vdev->dev_parent;
	dev_set_name(&vdev->dev, "%s%d", name_base, vdev->num);
	ret = device_रेजिस्टर(&vdev->dev);
	अगर (ret < 0) अणु
		pr_err("%s: device_register failed\n", __func__);
		जाओ cleanup;
	पूर्ण
	/* Register the release callback that will be called when the last
	   reference to the device goes away. */
	vdev->dev.release = v4l2_device_release;

	अगर (nr != -1 && nr != vdev->num && warn_अगर_nr_in_use)
		pr_warn("%s: requested %s%d, got %s\n", __func__,
			name_base, nr, video_device_node_name(vdev));

	/* Increase v4l2_device refcount */
	v4l2_device_get(vdev->v4l2_dev);

	/* Part 5: Register the entity. */
	ret = video_रेजिस्टर_media_controller(vdev);

	/* Part 6: Activate this minor. The अक्षर device can now be used. */
	set_bit(V4L2_FL_REGISTERED, &vdev->flags);

	वापस 0;

cleanup:
	mutex_lock(&videodev_lock);
	अगर (vdev->cdev)
		cdev_del(vdev->cdev);
	video_devices[vdev->minor] = शून्य;
	devnode_clear(vdev);
	mutex_unlock(&videodev_lock);
	/* Mark this video device as never having been रेजिस्टरed. */
	vdev->minor = -1;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__video_रेजिस्टर_device);

/**
 *	video_unरेजिस्टर_device - unरेजिस्टर a video4linux device
 *	@vdev: the device to unरेजिस्टर
 *
 *	This unरेजिस्टरs the passed device. Future खोलो calls will
 *	be met with errors.
 */
व्योम video_unरेजिस्टर_device(काष्ठा video_device *vdev)
अणु
	/* Check अगर vdev was ever रेजिस्टरed at all */
	अगर (!vdev || !video_is_रेजिस्टरed(vdev))
		वापस;

	mutex_lock(&videodev_lock);
	/* This must be in a critical section to prevent a race with v4l2_खोलो.
	 * Once this bit has been cleared video_get may never be called again.
	 */
	clear_bit(V4L2_FL_REGISTERED, &vdev->flags);
	mutex_unlock(&videodev_lock);
	अगर (test_bit(V4L2_FL_USES_V4L2_FH, &vdev->flags))
		v4l2_event_wake_all(vdev);
	device_unरेजिस्टर(&vdev->dev);
पूर्ण
EXPORT_SYMBOL(video_unरेजिस्टर_device);

/*
 *	Initialise video क्रम linux
 */
अटल पूर्णांक __init videodev_init(व्योम)
अणु
	dev_t dev = MKDEV(VIDEO_MAJOR, 0);
	पूर्णांक ret;

	pr_info("Linux video capture interface: v2.00\n");
	ret = रेजिस्टर_chrdev_region(dev, VIDEO_NUM_DEVICES, VIDEO_NAME);
	अगर (ret < 0) अणु
		pr_warn("videodev: unable to get major %d\n",
				VIDEO_MAJOR);
		वापस ret;
	पूर्ण

	ret = class_रेजिस्टर(&video_class);
	अगर (ret < 0) अणु
		unरेजिस्टर_chrdev_region(dev, VIDEO_NUM_DEVICES);
		pr_warn("video_dev: class_register failed\n");
		वापस -EIO;
	पूर्ण

	v4l2_debugfs_dir = debugfs_create_dir("video4linux", शून्य);
	v4l2_async_debug_init(v4l2_debugfs_dir);
	वापस 0;
पूर्ण

अटल व्योम __निकास videodev_निकास(व्योम)
अणु
	dev_t dev = MKDEV(VIDEO_MAJOR, 0);

	debugfs_हटाओ_recursive(v4l2_debugfs_dir);
	class_unरेजिस्टर(&video_class);
	unरेजिस्टर_chrdev_region(dev, VIDEO_NUM_DEVICES);
पूर्ण

subsys_initcall(videodev_init);
module_निकास(videodev_निकास)

MODULE_AUTHOR("Alan Cox, Mauro Carvalho Chehab <mchehab@kernel.org>, Bill Dirks, Justin Schoeman, Gerd Knorr");
MODULE_DESCRIPTION("Video4Linux2 core driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS_CHARDEV_MAJOR(VIDEO_MAJOR);
