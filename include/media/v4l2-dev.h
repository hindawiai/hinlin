<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *
 *	V 4 L 2   D R I V E R   H E L P E R   A P I
 *
 * Moved from videodev2.h
 *
 *	Some commonly needed functions क्रम drivers (v4l2-common.o module)
 */
#अगर_अघोषित _V4L2_DEV_H
#घोषणा _V4L2_DEV_H

#समावेश <linux/poll.h>
#समावेश <linux/fs.h>
#समावेश <linux/device.h>
#समावेश <linux/cdev.h>
#समावेश <linux/mutex.h>
#समावेश <linux/videodev2.h>

#समावेश <media/media-entity.h>

#घोषणा VIDEO_MAJOR	81

/**
 * क्रमागत vfl_devnode_type - type of V4L2 device node
 *
 * @VFL_TYPE_VIDEO:	क्रम video input/output devices
 * @VFL_TYPE_VBI:	क्रम vertical blank data (i.e. बंदd captions, teletext)
 * @VFL_TYPE_RADIO:	क्रम radio tuners
 * @VFL_TYPE_SUBDEV:	क्रम V4L2 subdevices
 * @VFL_TYPE_SDR:	क्रम Software Defined Radio tuners
 * @VFL_TYPE_TOUCH:	क्रम touch sensors
 * @VFL_TYPE_MAX:	number of VFL types, must always be last in the क्रमागत
 */
क्रमागत vfl_devnode_type अणु
	VFL_TYPE_VIDEO,
	VFL_TYPE_VBI,
	VFL_TYPE_RADIO,
	VFL_TYPE_SUBDEV,
	VFL_TYPE_SDR,
	VFL_TYPE_TOUCH,
	VFL_TYPE_MAX /* Shall be the last one */
पूर्ण;

/**
 * क्रमागत  vfl_devnode_direction - Identअगरies अगर a &काष्ठा video_device
 * 	corresponds to a receiver, a transmitter or a mem-to-mem device.
 *
 * @VFL_सूची_RX:		device is a receiver.
 * @VFL_सूची_TX:		device is a transmitter.
 * @VFL_सूची_M2M:	device is a memory to memory device.
 *
 * Note: Ignored अगर &क्रमागत vfl_devnode_type is %VFL_TYPE_SUBDEV.
 */
क्रमागत vfl_devnode_direction अणु
	VFL_सूची_RX,
	VFL_सूची_TX,
	VFL_सूची_M2M,
पूर्ण;

काष्ठा v4l2_ioctl_callbacks;
काष्ठा video_device;
काष्ठा v4l2_device;
काष्ठा v4l2_ctrl_handler;

/**
 * क्रमागत v4l2_video_device_flags - Flags used by &काष्ठा video_device
 *
 * @V4L2_FL_REGISTERED:
 *	indicates that a &काष्ठा video_device is रेजिस्टरed.
 *	Drivers can clear this flag अगर they want to block all future
 *	device access. It is cleared by video_unरेजिस्टर_device.
 * @V4L2_FL_USES_V4L2_FH:
 *	indicates that file->निजी_data poपूर्णांकs to &काष्ठा v4l2_fh.
 *	This flag is set by the core when v4l2_fh_init() is called.
 *	All new drivers should use it.
 * @V4L2_FL_QUIRK_INVERTED_CROP:
 *	some old M2M drivers use g/s_crop/cropcap incorrectly: crop and
 *	compose are swapped. If this flag is set, then the selection
 *	tarमाला_लो are swapped in the g/s_crop/cropcap functions in v4l2-ioctl.c.
 *	This allows those drivers to correctly implement the selection API,
 *	but the old crop API will still work as expected in order to preserve
 *	backwards compatibility.
 *	Never set this flag क्रम new drivers.
 * @V4L2_FL_SUBDEV_RO_DEVNODE:
 *	indicates that the video device node is रेजिस्टरed in पढ़ो-only mode.
 *	The flag only applies to device nodes रेजिस्टरed क्रम sub-devices, it is
 *	set by the core when the sub-devices device nodes are रेजिस्टरed with
 *	v4l2_device_रेजिस्टर_ro_subdev_nodes() and used by the sub-device ioctl
 *	handler to restrict access to some ioctl calls.
 */
क्रमागत v4l2_video_device_flags अणु
	V4L2_FL_REGISTERED		= 0,
	V4L2_FL_USES_V4L2_FH		= 1,
	V4L2_FL_QUIRK_INVERTED_CROP	= 2,
	V4L2_FL_SUBDEV_RO_DEVNODE	= 3,
पूर्ण;

/* Priority helper functions */

/**
 * काष्ठा v4l2_prio_state - stores the priority states
 *
 * @prios: array with elements to store the array priorities
 *
 *
 * .. note::
 *    The size of @prios array matches the number of priority types defined
 *    by क्रमागत &v4l2_priority.
 */
काष्ठा v4l2_prio_state अणु
	atomic_t prios[4];
पूर्ण;

/**
 * v4l2_prio_init - initializes a काष्ठा v4l2_prio_state
 *
 * @global: poपूर्णांकer to &काष्ठा v4l2_prio_state
 */
व्योम v4l2_prio_init(काष्ठा v4l2_prio_state *global);

/**
 * v4l2_prio_change - changes the v4l2 file handler priority
 *
 * @global: poपूर्णांकer to the &काष्ठा v4l2_prio_state of the device node.
 * @local: poपूर्णांकer to the desired priority, as defined by क्रमागत &v4l2_priority
 * @new: Priority type requested, as defined by क्रमागत &v4l2_priority.
 *
 * .. note::
 *	This function should be used only by the V4L2 core.
 */
पूर्णांक v4l2_prio_change(काष्ठा v4l2_prio_state *global, क्रमागत v4l2_priority *local,
		     क्रमागत v4l2_priority new);

/**
 * v4l2_prio_खोलो - Implements the priority logic क्रम a file handler खोलो
 *
 * @global: poपूर्णांकer to the &काष्ठा v4l2_prio_state of the device node.
 * @local: poपूर्णांकer to the desired priority, as defined by क्रमागत &v4l2_priority
 *
 * .. note::
 *	This function should be used only by the V4L2 core.
 */
व्योम v4l2_prio_खोलो(काष्ठा v4l2_prio_state *global, क्रमागत v4l2_priority *local);

/**
 * v4l2_prio_बंद - Implements the priority logic क्रम a file handler बंद
 *
 * @global: poपूर्णांकer to the &काष्ठा v4l2_prio_state of the device node.
 * @local: priority to be released, as defined by क्रमागत &v4l2_priority
 *
 * .. note::
 *	This function should be used only by the V4L2 core.
 */
व्योम v4l2_prio_बंद(काष्ठा v4l2_prio_state *global, क्रमागत v4l2_priority local);

/**
 * v4l2_prio_max - Return the maximum priority, as stored at the @global array.
 *
 * @global: poपूर्णांकer to the &काष्ठा v4l2_prio_state of the device node.
 *
 * .. note::
 *	This function should be used only by the V4L2 core.
 */
क्रमागत v4l2_priority v4l2_prio_max(काष्ठा v4l2_prio_state *global);

/**
 * v4l2_prio_check - Implements the priority logic क्रम a file handler बंद
 *
 * @global: poपूर्णांकer to the &काष्ठा v4l2_prio_state of the device node.
 * @local: desired priority, as defined by क्रमागत &v4l2_priority local
 *
 * .. note::
 *	This function should be used only by the V4L2 core.
 */
पूर्णांक v4l2_prio_check(काष्ठा v4l2_prio_state *global, क्रमागत v4l2_priority local);

/**
 * काष्ठा v4l2_file_operations - fs operations used by a V4L2 device
 *
 * @owner: poपूर्णांकer to काष्ठा module
 * @पढ़ो: operations needed to implement the पढ़ो() syscall
 * @ग_लिखो: operations needed to implement the ग_लिखो() syscall
 * @poll: operations needed to implement the poll() syscall
 * @unlocked_ioctl: operations needed to implement the ioctl() syscall
 * @compat_ioctl32: operations needed to implement the ioctl() syscall क्रम
 *	the special हाल where the Kernel uses 64 bits inकाष्ठाions, but
 *	the userspace uses 32 bits.
 * @get_unmapped_area: called by the mmap() syscall, used when %!CONFIG_MMU
 * @mmap: operations needed to implement the mmap() syscall
 * @खोलो: operations needed to implement the खोलो() syscall
 * @release: operations needed to implement the release() syscall
 *
 * .. note::
 *
 *	Those operations are used to implemente the fs काष्ठा file_operations
 *	at the V4L2 drivers. The V4L2 core overrides the fs ops with some
 *	extra logic needed by the subप्रणाली.
 */
काष्ठा v4l2_file_operations अणु
	काष्ठा module *owner;
	sमाप_प्रकार (*पढ़ो) (काष्ठा file *, अक्षर __user *, माप_प्रकार, loff_t *);
	sमाप_प्रकार (*ग_लिखो) (काष्ठा file *, स्थिर अक्षर __user *, माप_प्रकार, loff_t *);
	__poll_t (*poll) (काष्ठा file *, काष्ठा poll_table_काष्ठा *);
	दीर्घ (*unlocked_ioctl) (काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
#अगर_घोषित CONFIG_COMPAT
	दीर्घ (*compat_ioctl32) (काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
#पूर्ण_अगर
	अचिन्हित दीर्घ (*get_unmapped_area) (काष्ठा file *, अचिन्हित दीर्घ,
				अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ);
	पूर्णांक (*mmap) (काष्ठा file *, काष्ठा vm_area_काष्ठा *);
	पूर्णांक (*खोलो) (काष्ठा file *);
	पूर्णांक (*release) (काष्ठा file *);
पूर्ण;

/*
 * Newer version of video_device, handled by videodev2.c
 *	This version moves redundant code from video device code to
 *	the common handler
 */

/**
 * काष्ठा video_device - Structure used to create and manage the V4L2 device
 *	nodes.
 *
 * @entity: &काष्ठा media_entity
 * @पूर्णांकf_devnode: poपूर्णांकer to &काष्ठा media_पूर्णांकf_devnode
 * @pipe: &काष्ठा media_pipeline
 * @fops: poपूर्णांकer to &काष्ठा v4l2_file_operations क्रम the video device
 * @device_caps: device capabilities as used in v4l2_capabilities
 * @dev: &काष्ठा device क्रम the video device
 * @cdev: अक्षरacter device
 * @v4l2_dev: poपूर्णांकer to &काष्ठा v4l2_device parent
 * @dev_parent: poपूर्णांकer to &काष्ठा device parent
 * @ctrl_handler: Control handler associated with this device node.
 *	 May be शून्य.
 * @queue: &काष्ठा vb2_queue associated with this device node. May be शून्य.
 * @prio: poपूर्णांकer to &काष्ठा v4l2_prio_state with device's Priority state.
 *	 If शून्य, then v4l2_dev->prio will be used.
 * @name: video device name
 * @vfl_type: V4L device type, as defined by &क्रमागत vfl_devnode_type
 * @vfl_dir: V4L receiver, transmitter or m2m
 * @minor: device node 'minor'. It is set to -1 अगर the registration failed
 * @num: number of the video device node
 * @flags: video device flags. Use bitops to set/clear/test flags.
 *	   Contains a set of &क्रमागत v4l2_video_device_flags.
 * @index: attribute to dअगरferentiate multiple indices on one physical device
 * @fh_lock: Lock क्रम all v4l2_fhs
 * @fh_list: List of &काष्ठा v4l2_fh
 * @dev_debug: Internal device debug flags, not क्रम use by drivers
 * @tvnorms: Supported tv norms
 *
 * @release: video device release() callback
 * @ioctl_ops: poपूर्णांकer to &काष्ठा v4l2_ioctl_ops with ioctl callbacks
 *
 * @valid_ioctls: biपंचांगap with the valid ioctls क्रम this device
 * @lock: poपूर्णांकer to &काष्ठा mutex serialization lock
 *
 * .. note::
 *	Only set @dev_parent अगर that can't be deduced from @v4l2_dev.
 */

काष्ठा video_device
अणु
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	काष्ठा media_entity entity;
	काष्ठा media_पूर्णांकf_devnode *पूर्णांकf_devnode;
	काष्ठा media_pipeline pipe;
#पूर्ण_अगर
	स्थिर काष्ठा v4l2_file_operations *fops;

	u32 device_caps;

	/* sysfs */
	काष्ठा device dev;
	काष्ठा cdev *cdev;

	काष्ठा v4l2_device *v4l2_dev;
	काष्ठा device *dev_parent;

	काष्ठा v4l2_ctrl_handler *ctrl_handler;

	काष्ठा vb2_queue *queue;

	काष्ठा v4l2_prio_state *prio;

	/* device info */
	अक्षर name[32];
	क्रमागत vfl_devnode_type vfl_type;
	क्रमागत vfl_devnode_direction vfl_dir;
	पूर्णांक minor;
	u16 num;
	अचिन्हित दीर्घ flags;
	पूर्णांक index;

	/* V4L2 file handles */
	spinlock_t		fh_lock;
	काष्ठा list_head	fh_list;

	पूर्णांक dev_debug;

	v4l2_std_id tvnorms;

	/* callbacks */
	व्योम (*release)(काष्ठा video_device *vdev);
	स्थिर काष्ठा v4l2_ioctl_ops *ioctl_ops;
	DECLARE_BITMAP(valid_ioctls, BASE_VIDIOC_PRIVATE);

	काष्ठा mutex *lock;
पूर्ण;

/**
 * media_entity_to_video_device - Returns a &काष्ठा video_device from
 *	the &काष्ठा media_entity embedded on it.
 *
 * @__entity: poपूर्णांकer to &काष्ठा media_entity
 */
#घोषणा media_entity_to_video_device(__entity) \
	container_of(__entity, काष्ठा video_device, entity)

/**
 * to_video_device - Returns a &काष्ठा video_device from the
 *	&काष्ठा device embedded on it.
 *
 * @cd: poपूर्णांकer to &काष्ठा device
 */
#घोषणा to_video_device(cd) container_of(cd, काष्ठा video_device, dev)

/**
 * __video_रेजिस्टर_device - रेजिस्टर video4linux devices
 *
 * @vdev: काष्ठा video_device to रेजिस्टर
 * @type: type of device to रेजिस्टर, as defined by &क्रमागत vfl_devnode_type
 * @nr:   which device node number is desired:
 *	(0 == /dev/video0, 1 == /dev/video1, ..., -1 == first मुक्त)
 * @warn_अगर_nr_in_use: warn अगर the desired device node number
 *        was alपढ़ोy in use and another number was chosen instead.
 * @owner: module that owns the video device node
 *
 * The registration code assigns minor numbers and device node numbers
 * based on the requested type and रेजिस्टरs the new device node with
 * the kernel.
 *
 * This function assumes that काष्ठा video_device was zeroed when it
 * was allocated and करोes not contain any stale date.
 *
 * An error is वापसed अगर no मुक्त minor or device node number could be
 * found, or अगर the registration of the device node failed.
 *
 * Returns 0 on success.
 *
 * .. note::
 *
 *	This function is meant to be used only inside the V4L2 core.
 *	Drivers should use video_रेजिस्टर_device() or
 *	video_रेजिस्टर_device_no_warn().
 */
पूर्णांक __must_check __video_रेजिस्टर_device(काष्ठा video_device *vdev,
					 क्रमागत vfl_devnode_type type,
					 पूर्णांक nr, पूर्णांक warn_अगर_nr_in_use,
					 काष्ठा module *owner);

/**
 *  video_रेजिस्टर_device - रेजिस्टर video4linux devices
 *
 * @vdev: काष्ठा video_device to रेजिस्टर
 * @type: type of device to रेजिस्टर, as defined by &क्रमागत vfl_devnode_type
 * @nr:   which device node number is desired:
 *	(0 == /dev/video0, 1 == /dev/video1, ..., -1 == first मुक्त)
 *
 * Internally, it calls __video_रेजिस्टर_device(). Please see its
 * करोcumentation क्रम more details.
 *
 * .. note::
 *	अगर video_रेजिस्टर_device fails, the release() callback of
 *	&काष्ठा video_device काष्ठाure is *not* called, so the caller
 *	is responsible क्रम मुक्तing any data. Usually that means that
 *	you video_device_release() should be called on failure.
 */
अटल अंतरभूत पूर्णांक __must_check video_रेजिस्टर_device(काष्ठा video_device *vdev,
						     क्रमागत vfl_devnode_type type,
						     पूर्णांक nr)
अणु
	वापस __video_रेजिस्टर_device(vdev, type, nr, 1, vdev->fops->owner);
पूर्ण

/**
 *  video_रेजिस्टर_device_no_warn - रेजिस्टर video4linux devices
 *
 * @vdev: काष्ठा video_device to रेजिस्टर
 * @type: type of device to रेजिस्टर, as defined by &क्रमागत vfl_devnode_type
 * @nr:   which device node number is desired:
 *	(0 == /dev/video0, 1 == /dev/video1, ..., -1 == first मुक्त)
 *
 * This function is identical to video_रेजिस्टर_device() except that no
 * warning is issued अगर the desired device node number was alपढ़ोy in use.
 *
 * Internally, it calls __video_रेजिस्टर_device(). Please see its
 * करोcumentation क्रम more details.
 *
 * .. note::
 *	अगर video_रेजिस्टर_device fails, the release() callback of
 *	&काष्ठा video_device काष्ठाure is *not* called, so the caller
 *	is responsible क्रम मुक्तing any data. Usually that means that
 *	you video_device_release() should be called on failure.
 */
अटल अंतरभूत पूर्णांक __must_check
video_रेजिस्टर_device_no_warn(काष्ठा video_device *vdev,
			      क्रमागत vfl_devnode_type type, पूर्णांक nr)
अणु
	वापस __video_रेजिस्टर_device(vdev, type, nr, 0, vdev->fops->owner);
पूर्ण

/**
 * video_unरेजिस्टर_device - Unरेजिस्टर video devices.
 *
 * @vdev: &काष्ठा video_device to रेजिस्टर
 *
 * Does nothing अगर vdev == शून्य or अगर video_is_रेजिस्टरed() वापसs false.
 */
व्योम video_unरेजिस्टर_device(काष्ठा video_device *vdev);

/**
 * video_device_alloc - helper function to alloc &काष्ठा video_device
 *
 * Returns शून्य अगर %-ENOMEM or a &काष्ठा video_device on success.
 */
काष्ठा video_device * __must_check video_device_alloc(व्योम);

/**
 * video_device_release - helper function to release &काष्ठा video_device
 *
 * @vdev: poपूर्णांकer to &काष्ठा video_device
 *
 * Can also be used क्रम video_device->release\(\).
 */
व्योम video_device_release(काष्ठा video_device *vdev);

/**
 * video_device_release_empty - helper function to implement the
 *	video_device->release\(\) callback.
 *
 * @vdev: poपूर्णांकer to &काष्ठा video_device
 *
 * This release function करोes nothing.
 *
 * It should be used when the video_device is a अटल global काष्ठा.
 *
 * .. note::
 *	Having a अटल video_device is a dubious स्थिरruction at best.
 */
व्योम video_device_release_empty(काष्ठा video_device *vdev);

/**
 * v4l2_disable_ioctl- mark that a given command isn't implemented.
 *	shouldn't use core locking
 *
 * @vdev: poपूर्णांकer to &काष्ठा video_device
 * @cmd: ioctl command
 *
 * This function allows drivers to provide just one v4l2_ioctl_ops काष्ठा, but
 * disable ioctls based on the specअगरic card that is actually found.
 *
 * .. note::
 *
 *    This must be called beक्रमe video_रेजिस्टर_device.
 *    See also the comments क्रम determine_valid_ioctls().
 */
अटल अंतरभूत व्योम v4l2_disable_ioctl(काष्ठा video_device *vdev,
				      अचिन्हित पूर्णांक cmd)
अणु
	अगर (_IOC_NR(cmd) < BASE_VIDIOC_PRIVATE)
		set_bit(_IOC_NR(cmd), vdev->valid_ioctls);
पूर्ण

/**
 * video_get_drvdata - माला_लो निजी data from &काष्ठा video_device.
 *
 * @vdev: poपूर्णांकer to &काष्ठा video_device
 *
 * वापसs a poपूर्णांकer to the निजी data
 */
अटल अंतरभूत व्योम *video_get_drvdata(काष्ठा video_device *vdev)
अणु
	वापस dev_get_drvdata(&vdev->dev);
पूर्ण

/**
 * video_set_drvdata - sets निजी data from &काष्ठा video_device.
 *
 * @vdev: poपूर्णांकer to &काष्ठा video_device
 * @data: निजी data poपूर्णांकer
 */
अटल अंतरभूत व्योम video_set_drvdata(काष्ठा video_device *vdev, व्योम *data)
अणु
	dev_set_drvdata(&vdev->dev, data);
पूर्ण

/**
 * video_devdata - माला_लो &काष्ठा video_device from काष्ठा file.
 *
 * @file: poपूर्णांकer to काष्ठा file
 */
काष्ठा video_device *video_devdata(काष्ठा file *file);

/**
 * video_drvdata - माला_लो निजी data from &काष्ठा video_device using the
 *	काष्ठा file.
 *
 * @file: poपूर्णांकer to काष्ठा file
 *
 * This is function combines both video_get_drvdata() and video_devdata()
 * as this is used very often.
 */
अटल अंतरभूत व्योम *video_drvdata(काष्ठा file *file)
अणु
	वापस video_get_drvdata(video_devdata(file));
पूर्ण

/**
 * video_device_node_name - वापसs the video device name
 *
 * @vdev: poपूर्णांकer to &काष्ठा video_device
 *
 * Returns the device name string
 */
अटल अंतरभूत स्थिर अक्षर *video_device_node_name(काष्ठा video_device *vdev)
अणु
	वापस dev_name(&vdev->dev);
पूर्ण

/**
 * video_is_रेजिस्टरed - वापसs true अगर the &काष्ठा video_device is रेजिस्टरed.
 *
 *
 * @vdev: poपूर्णांकer to &काष्ठा video_device
 */
अटल अंतरभूत पूर्णांक video_is_रेजिस्टरed(काष्ठा video_device *vdev)
अणु
	वापस test_bit(V4L2_FL_REGISTERED, &vdev->flags);
पूर्ण

#पूर्ण_अगर /* _V4L2_DEV_H */
