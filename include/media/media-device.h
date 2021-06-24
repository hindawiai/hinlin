<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Media device
 *
 * Copyright (C) 2010 Nokia Corporation
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#अगर_अघोषित _MEDIA_DEVICE_H
#घोषणा _MEDIA_DEVICE_H

#समावेश <linux/list.h>
#समावेश <linux/mutex.h>

#समावेश <media/media-devnode.h>
#समावेश <media/media-entity.h>

काष्ठा ida;
काष्ठा device;
काष्ठा media_device;

/**
 * काष्ठा media_entity_notअगरy - Media Entity Notअगरy
 *
 * @list: List head
 * @notअगरy_data: Input data to invoke the callback
 * @notअगरy: Callback function poपूर्णांकer
 *
 * Drivers may रेजिस्टर a callback to take action when new entities get
 * रेजिस्टरed with the media device. This handler is पूर्णांकended क्रम creating
 * links between existing entities and should not create entities and रेजिस्टर
 * them.
 */
काष्ठा media_entity_notअगरy अणु
	काष्ठा list_head list;
	व्योम *notअगरy_data;
	व्योम (*notअगरy)(काष्ठा media_entity *entity, व्योम *notअगरy_data);
पूर्ण;

/**
 * काष्ठा media_device_ops - Media device operations
 * @link_notअगरy: Link state change notअगरication callback. This callback is
 *		 called with the graph_mutex held.
 * @req_alloc: Allocate a request. Set this अगर you need to allocate a काष्ठा
 *	       larger then काष्ठा media_request. @req_alloc and @req_मुक्त must
 *	       either both be set or both be शून्य.
 * @req_मुक्त: Free a request. Set this अगर @req_alloc was set as well, leave
 *	      to शून्य otherwise.
 * @req_validate: Validate a request, but करो not queue yet. The req_queue_mutex
 *	          lock is held when this op is called.
 * @req_queue: Queue a validated request, cannot fail. If something goes
 *	       wrong when queueing this request then it should be marked
 *	       as such पूर्णांकernally in the driver and any related buffers
 *	       must eventually वापस to vb2 with state VB2_BUF_STATE_ERROR.
 *	       The req_queue_mutex lock is held when this op is called.
 *	       It is important that vb2 buffer objects are queued last after
 *	       all other object types are queued: queueing a buffer kickstarts
 *	       the request processing, so all other objects related to the
 *	       request (and thus the buffer) must be available to the driver.
 *	       And once a buffer is queued, then the driver can complete
 *	       or delete objects from the request beक्रमe req_queue निकासs.
 */
काष्ठा media_device_ops अणु
	पूर्णांक (*link_notअगरy)(काष्ठा media_link *link, u32 flags,
			   अचिन्हित पूर्णांक notअगरication);
	काष्ठा media_request *(*req_alloc)(काष्ठा media_device *mdev);
	व्योम (*req_मुक्त)(काष्ठा media_request *req);
	पूर्णांक (*req_validate)(काष्ठा media_request *req);
	व्योम (*req_queue)(काष्ठा media_request *req);
पूर्ण;

/**
 * काष्ठा media_device - Media device
 * @dev:	Parent device
 * @devnode:	Media device node
 * @driver_name: Optional device driver name. If not set, calls to
 *		%MEDIA_IOC_DEVICE_INFO will वापस ``dev->driver->name``.
 *		This is needed क्रम USB drivers क्रम example, as otherwise
 *		they'll all appear as अगर the driver name was "usb".
 * @model:	Device model name
 * @serial:	Device serial number (optional)
 * @bus_info:	Unique and stable device location identअगरier
 * @hw_revision: Hardware device revision
 * @topology_version: Monotonic counter क्रम storing the version of the graph
 *		topology. Should be incremented each समय the topology changes.
 * @id:		Unique ID used on the last रेजिस्टरed graph object
 * @entity_पूर्णांकernal_idx: Unique पूर्णांकernal entity ID used by the graph traversal
 *		algorithms
 * @entity_पूर्णांकernal_idx_max: Allocated पूर्णांकernal entity indices
 * @entities:	List of रेजिस्टरed entities
 * @पूर्णांकerfaces:	List of रेजिस्टरed पूर्णांकerfaces
 * @pads:	List of रेजिस्टरed pads
 * @links:	List of रेजिस्टरed links
 * @entity_notअगरy: List of रेजिस्टरed entity_notअगरy callbacks
 * @graph_mutex: Protects access to काष्ठा media_device data
 * @pm_count_walk: Graph walk क्रम घातer state walk. Access serialised using
 *		   graph_mutex.
 *
 * @source_priv: Driver Private data क्रम enable/disable source handlers
 * @enable_source: Enable Source Handler function poपूर्णांकer
 * @disable_source: Disable Source Handler function poपूर्णांकer
 *
 * @ops:	Operation handler callbacks
 * @req_queue_mutex: Serialise the MEDIA_REQUEST_IOC_QUEUE ioctl w.r.t.
 *		     other operations that stop or start streaming.
 * @request_id: Used to generate unique request IDs
 *
 * This काष्ठाure represents an असलtract high-level media device. It allows easy
 * access to entities and provides basic media device-level support. The
 * काष्ठाure can be allocated directly or embedded in a larger काष्ठाure.
 *
 * The parent @dev is a physical device. It must be set beक्रमe रेजिस्टरing the
 * media device.
 *
 * @model is a descriptive model name exported through sysfs. It करोesn't have to
 * be unique.
 *
 * @enable_source is a handler to find source entity क्रम the
 * sink entity  and activate the link between them अगर source
 * entity is मुक्त. Drivers should call this handler beक्रमe
 * accessing the source.
 *
 * @disable_source is a handler to find source entity क्रम the
 * sink entity  and deactivate the link between them. Drivers
 * should call this handler to release the source.
 *
 * Use-हाल: find tuner entity connected to the decoder
 * entity and check अगर it is available, and activate the
 * link between them from @enable_source and deactivate
 * from @disable_source.
 *
 * .. note::
 *
 *    Bridge driver is expected to implement and set the
 *    handler when &media_device is रेजिस्टरed or when
 *    bridge driver finds the media_device during probe.
 *    Bridge driver sets source_priv with inक्रमmation
 *    necessary to run @enable_source and @disable_source handlers.
 *    Callers should hold graph_mutex to access and call @enable_source
 *    and @disable_source handlers.
 */
काष्ठा media_device अणु
	/* dev->driver_data poपूर्णांकs to this काष्ठा. */
	काष्ठा device *dev;
	काष्ठा media_devnode *devnode;

	अक्षर model[32];
	अक्षर driver_name[32];
	अक्षर serial[40];
	अक्षर bus_info[32];
	u32 hw_revision;

	u64 topology_version;

	u32 id;
	काष्ठा ida entity_पूर्णांकernal_idx;
	पूर्णांक entity_पूर्णांकernal_idx_max;

	काष्ठा list_head entities;
	काष्ठा list_head पूर्णांकerfaces;
	काष्ठा list_head pads;
	काष्ठा list_head links;

	/* notअगरy callback list invoked when a new entity is रेजिस्टरed */
	काष्ठा list_head entity_notअगरy;

	/* Serializes graph operations. */
	काष्ठा mutex graph_mutex;
	काष्ठा media_graph pm_count_walk;

	व्योम *source_priv;
	पूर्णांक (*enable_source)(काष्ठा media_entity *entity,
			     काष्ठा media_pipeline *pipe);
	व्योम (*disable_source)(काष्ठा media_entity *entity);

	स्थिर काष्ठा media_device_ops *ops;

	काष्ठा mutex req_queue_mutex;
	atomic_t request_id;
पूर्ण;

/* We करोn't need to include pci.h or usb.h here */
काष्ठा pci_dev;
काष्ठा usb_device;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER

/* Supported link_notअगरy @notअगरication values. */
#घोषणा MEDIA_DEV_NOTIFY_PRE_LINK_CH	0
#घोषणा MEDIA_DEV_NOTIFY_POST_LINK_CH	1

/**
 * media_entity_क्रमागत_init - Initialise an entity क्रमागतeration
 *
 * @ent_क्रमागत: Entity क्रमागतeration to be initialised
 * @mdev: The related media device
 *
 * Return: zero on success or a negative error code.
 */
अटल अंतरभूत __must_check पूर्णांक media_entity_क्रमागत_init(
	काष्ठा media_entity_क्रमागत *ent_क्रमागत, काष्ठा media_device *mdev)
अणु
	वापस __media_entity_क्रमागत_init(ent_क्रमागत,
					mdev->entity_पूर्णांकernal_idx_max + 1);
पूर्ण

/**
 * media_device_init() - Initializes a media device element
 *
 * @mdev:	poपूर्णांकer to काष्ठा &media_device
 *
 * This function initializes the media device prior to its registration.
 * The media device initialization and registration is split in two functions
 * to aव्योम race conditions and make the media device available to user-space
 * beक्रमe the media graph has been completed.
 *
 * So drivers need to first initialize the media device, रेजिस्टर any entity
 * within the media device, create pad to pad links and then finally रेजिस्टर
 * the media device by calling media_device_रेजिस्टर() as a final step.
 */
व्योम media_device_init(काष्ठा media_device *mdev);

/**
 * media_device_cleanup() - Cleanups a media device element
 *
 * @mdev:	poपूर्णांकer to काष्ठा &media_device
 *
 * This function that will destroy the graph_mutex that is
 * initialized in media_device_init().
 */
व्योम media_device_cleanup(काष्ठा media_device *mdev);

/**
 * __media_device_रेजिस्टर() - Registers a media device element
 *
 * @mdev:	poपूर्णांकer to काष्ठा &media_device
 * @owner:	should be filled with %THIS_MODULE
 *
 * Users, should, instead, call the media_device_रेजिस्टर() macro.
 *
 * The caller is responsible क्रम initializing the &media_device काष्ठाure
 * beक्रमe registration. The following fields of &media_device must be set:
 *
 *  - &media_entity.dev must poपूर्णांक to the parent device (usually a &pci_dev,
 *    &usb_पूर्णांकerface or &platक्रमm_device instance).
 *
 *  - &media_entity.model must be filled with the device model name as a
 *    NUL-terminated UTF-8 string. The device/model revision must not be
 *    stored in this field.
 *
 * The following fields are optional:
 *
 *  - &media_entity.serial is a unique serial number stored as a
 *    NUL-terminated ASCII string. The field is big enough to store a GUID
 *    in text क्रमm. If the hardware करोesn't provide a unique serial number
 *    this field must be left empty.
 *
 *  - &media_entity.bus_info represents the location of the device in the
 *    प्रणाली as a NUL-terminated ASCII string. For PCI/PCIe devices
 *    &media_entity.bus_info must be set to "PCI:" (or "PCIe:") followed by
 *    the value of pci_name(). For USB devices,the usb_make_path() function
 *    must be used. This field is used by applications to distinguish between
 *    otherwise identical devices that करोn't provide a serial number.
 *
 *  - &media_entity.hw_revision is the hardware device revision in a
 *    driver-specअगरic क्रमmat. When possible the revision should be क्रमmatted
 *    with the KERNEL_VERSION() macro.
 *
 * .. note::
 *
 *    #) Upon successful registration a अक्षरacter device named media[0-9]+ is created. The device major and minor numbers are dynamic. The model name is exported as a sysfs attribute.
 *
 *    #) Unरेजिस्टरing a media device that hasn't been रेजिस्टरed is **NOT** safe.
 *
 * Return: वापसs zero on success or a negative error code.
 */
पूर्णांक __must_check __media_device_रेजिस्टर(काष्ठा media_device *mdev,
					 काष्ठा module *owner);


/**
 * media_device_रेजिस्टर() - Registers a media device element
 *
 * @mdev:	poपूर्णांकer to काष्ठा &media_device
 *
 * This macro calls __media_device_रेजिस्टर() passing %THIS_MODULE as
 * the __media_device_रेजिस्टर() second argument (**owner**).
 */
#घोषणा media_device_रेजिस्टर(mdev) __media_device_रेजिस्टर(mdev, THIS_MODULE)

/**
 * media_device_unरेजिस्टर() - Unरेजिस्टरs a media device element
 *
 * @mdev:	poपूर्णांकer to काष्ठा &media_device
 *
 * It is safe to call this function on an unरेजिस्टरed (but initialised)
 * media device.
 */
व्योम media_device_unरेजिस्टर(काष्ठा media_device *mdev);

/**
 * media_device_रेजिस्टर_entity() - रेजिस्टरs a media entity inside a
 *	previously रेजिस्टरed media device.
 *
 * @mdev:	poपूर्णांकer to काष्ठा &media_device
 * @entity:	poपूर्णांकer to काष्ठा &media_entity to be रेजिस्टरed
 *
 * Entities are identअगरied by a unique positive पूर्णांकeger ID. The media
 * controller framework will such ID स्वतःmatically. IDs are not guaranteed
 * to be contiguous, and the ID number can change on newer Kernel versions.
 * So, neither the driver nor userspace should hardcode ID numbers to refer
 * to the entities, but, instead, use the framework to find the ID, when
 * needed.
 *
 * The media_entity name, type and flags fields should be initialized beक्रमe
 * calling media_device_रेजिस्टर_entity(). Entities embedded in higher-level
 * standard काष्ठाures can have some of those fields set by the higher-level
 * framework.
 *
 * If the device has pads, media_entity_pads_init() should be called beक्रमe
 * this function. Otherwise, the &media_entity.pad and &media_entity.num_pads
 * should be zeroed beक्रमe calling this function.
 *
 * Entities have flags that describe the entity capabilities and state:
 *
 * %MEDIA_ENT_FL_DEFAULT
 *    indicates the शेष entity क्रम a given type.
 *    This can be used to report the शेष audio and video devices or the
 *    शेष camera sensor.
 *
 * .. note::
 *
 *    Drivers should set the entity function beक्रमe calling this function.
 *    Please notice that the values %MEDIA_ENT_F_V4L2_SUBDEV_UNKNOWN and
 *    %MEDIA_ENT_F_UNKNOWN should not be used by the drivers.
 */
पूर्णांक __must_check media_device_रेजिस्टर_entity(काष्ठा media_device *mdev,
					      काष्ठा media_entity *entity);

/**
 * media_device_unरेजिस्टर_entity() - unरेजिस्टरs a media entity.
 *
 * @entity:	poपूर्णांकer to काष्ठा &media_entity to be unरेजिस्टरed
 *
 * All links associated with the entity and all PADs are स्वतःmatically
 * unरेजिस्टरed from the media_device when this function is called.
 *
 * Unरेजिस्टरing an entity will not change the IDs of the other entities and
 * the previoully used ID will never be reused क्रम a newly रेजिस्टरed entities.
 *
 * When a media device is unरेजिस्टरed, all its entities are unरेजिस्टरed
 * स्वतःmatically. No manual entities unregistration is then required.
 *
 * .. note::
 *
 *    The media_entity instance itself must be मुक्तd explicitly by
 *    the driver अगर required.
 */
व्योम media_device_unरेजिस्टर_entity(काष्ठा media_entity *entity);

/**
 * media_device_रेजिस्टर_entity_notअगरy() - Registers a media entity_notअगरy
 *					   callback
 *
 * @mdev:      The media device
 * @nptr:      The media_entity_notअगरy
 *
 * .. note::
 *
 *    When a new entity is रेजिस्टरed, all the रेजिस्टरed
 *    media_entity_notअगरy callbacks are invoked.
 */

पूर्णांक __must_check media_device_रेजिस्टर_entity_notअगरy(काष्ठा media_device *mdev,
					काष्ठा media_entity_notअगरy *nptr);

/**
 * media_device_unरेजिस्टर_entity_notअगरy() - Unरेजिस्टर a media entity notअगरy
 *					     callback
 *
 * @mdev:      The media device
 * @nptr:      The media_entity_notअगरy
 *
 */
व्योम media_device_unरेजिस्टर_entity_notअगरy(काष्ठा media_device *mdev,
					काष्ठा media_entity_notअगरy *nptr);

/* Iterate over all entities. */
#घोषणा media_device_क्रम_each_entity(entity, mdev)			\
	list_क्रम_each_entry(entity, &(mdev)->entities, graph_obj.list)

/* Iterate over all पूर्णांकerfaces. */
#घोषणा media_device_क्रम_each_पूर्णांकf(पूर्णांकf, mdev)			\
	list_क्रम_each_entry(पूर्णांकf, &(mdev)->पूर्णांकerfaces, graph_obj.list)

/* Iterate over all pads. */
#घोषणा media_device_क्रम_each_pad(pad, mdev)			\
	list_क्रम_each_entry(pad, &(mdev)->pads, graph_obj.list)

/* Iterate over all links. */
#घोषणा media_device_क्रम_each_link(link, mdev)			\
	list_क्रम_each_entry(link, &(mdev)->links, graph_obj.list)

/**
 * media_device_pci_init() - create and initialize a
 *	काष्ठा &media_device from a PCI device.
 *
 * @mdev:	poपूर्णांकer to काष्ठा &media_device
 * @pci_dev:	poपूर्णांकer to काष्ठा pci_dev
 * @name:	media device name. If %शून्य, the routine will use the शेष
 *		name क्रम the pci device, given by pci_name() macro.
 */
व्योम media_device_pci_init(काष्ठा media_device *mdev,
			   काष्ठा pci_dev *pci_dev,
			   स्थिर अक्षर *name);
/**
 * __media_device_usb_init() - create and initialize a
 *	काष्ठा &media_device from a PCI device.
 *
 * @mdev:	poपूर्णांकer to काष्ठा &media_device
 * @udev:	poपूर्णांकer to काष्ठा usb_device
 * @board_name:	media device name. If %शून्य, the routine will use the usb
 *		product name, अगर available.
 * @driver_name: name of the driver. अगर %शून्य, the routine will use the name
 *		given by ``udev->dev->driver->name``, with is usually the wrong
 *		thing to करो.
 *
 * .. note::
 *
 *    It is better to call media_device_usb_init() instead, as
 *    such macro fills driver_name with %KBUILD_MODNAME.
 */
व्योम __media_device_usb_init(काष्ठा media_device *mdev,
			     काष्ठा usb_device *udev,
			     स्थिर अक्षर *board_name,
			     स्थिर अक्षर *driver_name);

#अन्यथा
अटल अंतरभूत पूर्णांक media_device_रेजिस्टर(काष्ठा media_device *mdev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम media_device_unरेजिस्टर(काष्ठा media_device *mdev)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक media_device_रेजिस्टर_entity(काष्ठा media_device *mdev,
						काष्ठा media_entity *entity)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम media_device_unरेजिस्टर_entity(काष्ठा media_entity *entity)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक media_device_रेजिस्टर_entity_notअगरy(
					काष्ठा media_device *mdev,
					काष्ठा media_entity_notअगरy *nptr)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम media_device_unरेजिस्टर_entity_notअगरy(
					काष्ठा media_device *mdev,
					काष्ठा media_entity_notअगरy *nptr)
अणु
पूर्ण

अटल अंतरभूत व्योम media_device_pci_init(काष्ठा media_device *mdev,
					 काष्ठा pci_dev *pci_dev,
					 अक्षर *name)
अणु
पूर्ण

अटल अंतरभूत व्योम __media_device_usb_init(काष्ठा media_device *mdev,
					   काष्ठा usb_device *udev,
					   अक्षर *board_name,
					   अक्षर *driver_name)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_MEDIA_CONTROLLER */

/**
 * media_device_usb_init() - create and initialize a
 *	काष्ठा &media_device from a PCI device.
 *
 * @mdev:	poपूर्णांकer to काष्ठा &media_device
 * @udev:	poपूर्णांकer to काष्ठा usb_device
 * @name:	media device name. If %शून्य, the routine will use the usb
 *		product name, अगर available.
 *
 * This macro calls media_device_usb_init() passing the
 * media_device_usb_init() **driver_name** parameter filled with
 * %KBUILD_MODNAME.
 */
#घोषणा media_device_usb_init(mdev, udev, name) \
	__media_device_usb_init(mdev, udev, name, KBUILD_MODNAME)

#पूर्ण_अगर
