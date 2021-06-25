<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    V4L2 device support header.

    Copyright (C) 2008  Hans Verkuil <hverkuil@xs4all.nl>

 */

#अगर_अघोषित _V4L2_DEVICE_H
#घोषणा _V4L2_DEVICE_H

#समावेश <media/media-device.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/v4l2-dev.h>

#घोषणा V4L2_DEVICE_NAME_SIZE (20 + 16)

काष्ठा v4l2_ctrl_handler;

/**
 * काष्ठा v4l2_device - मुख्य काष्ठा to क्रम V4L2 device drivers
 *
 * @dev: poपूर्णांकer to काष्ठा device.
 * @mdev: poपूर्णांकer to काष्ठा media_device, may be शून्य.
 * @subdevs: used to keep track of the रेजिस्टरed subdevs
 * @lock: lock this काष्ठा; can be used by the driver as well
 *	अगर this काष्ठा is embedded पूर्णांकo a larger काष्ठा.
 * @name: unique device name, by शेष the driver name + bus ID
 * @notअगरy: notअगरy operation called by some sub-devices.
 * @ctrl_handler: The control handler. May be %शून्य.
 * @prio: Device's priority state
 * @ref: Keep track of the references to this काष्ठा.
 * @release: Release function that is called when the ref count
 *	goes to 0.
 *
 * Each instance of a V4L2 device should create the v4l2_device काष्ठा,
 * either stand-alone or embedded in a larger काष्ठा.
 *
 * It allows easy access to sub-devices (see v4l2-subdev.h) and provides
 * basic V4L2 device-level support.
 *
 * .. note::
 *
 *    #) @dev->driver_data poपूर्णांकs to this काष्ठा.
 *    #) @dev might be %शून्य अगर there is no parent device
 */
काष्ठा v4l2_device अणु
	काष्ठा device *dev;
	काष्ठा media_device *mdev;
	काष्ठा list_head subdevs;
	spinlock_t lock;
	अक्षर name[V4L2_DEVICE_NAME_SIZE];
	व्योम (*notअगरy)(काष्ठा v4l2_subdev *sd,
			अचिन्हित पूर्णांक notअगरication, व्योम *arg);
	काष्ठा v4l2_ctrl_handler *ctrl_handler;
	काष्ठा v4l2_prio_state prio;
	काष्ठा kref ref;
	व्योम (*release)(काष्ठा v4l2_device *v4l2_dev);
पूर्ण;

/**
 * v4l2_device_get - माला_लो a V4L2 device reference
 *
 * @v4l2_dev: poपूर्णांकer to काष्ठा &v4l2_device
 *
 * This is an ancillary routine meant to increment the usage क्रम the
 * काष्ठा &v4l2_device poपूर्णांकed by @v4l2_dev.
 */
अटल अंतरभूत व्योम v4l2_device_get(काष्ठा v4l2_device *v4l2_dev)
अणु
	kref_get(&v4l2_dev->ref);
पूर्ण

/**
 * v4l2_device_put - माला_दो a V4L2 device reference
 *
 * @v4l2_dev: poपूर्णांकer to काष्ठा &v4l2_device
 *
 * This is an ancillary routine meant to decrement the usage क्रम the
 * काष्ठा &v4l2_device poपूर्णांकed by @v4l2_dev.
 */
पूर्णांक v4l2_device_put(काष्ठा v4l2_device *v4l2_dev);

/**
 * v4l2_device_रेजिस्टर - Initialize v4l2_dev and make @dev->driver_data
 *	poपूर्णांक to @v4l2_dev.
 *
 * @dev: poपूर्णांकer to काष्ठा &device
 * @v4l2_dev: poपूर्णांकer to काष्ठा &v4l2_device
 *
 * .. note::
 *	@dev may be %शून्य in rare हालs (ISA devices).
 *	In such हाल the caller must fill in the @v4l2_dev->name field
 *	beक्रमe calling this function.
 */
पूर्णांक __must_check v4l2_device_रेजिस्टर(काष्ठा device *dev,
				      काष्ठा v4l2_device *v4l2_dev);

/**
 * v4l2_device_set_name - Optional function to initialize the
 *	name field of काष्ठा &v4l2_device
 *
 * @v4l2_dev: poपूर्णांकer to काष्ठा &v4l2_device
 * @basename: base name क्रम the device name
 * @instance: poपूर्णांकer to a अटल atomic_t var with the instance usage क्रम
 *	the device driver.
 *
 * v4l2_device_set_name() initializes the name field of काष्ठा &v4l2_device
 * using the driver name and a driver-global atomic_t instance.
 *
 * This function will increment the instance counter and वापसs the
 * instance value used in the name.
 *
 * Example:
 *
 *   अटल atomic_t drv_instance = ATOMIC_INIT(0);
 *
 *   ...
 *
 *   instance = v4l2_device_set_name(&\ v4l2_dev, "foo", &\ drv_instance);
 *
 * The first समय this is called the name field will be set to foo0 and
 * this function वापसs 0. If the name ends with a digit (e.g. cx18),
 * then the name will be set to cx18-0 since cx180 would look really odd.
 */
पूर्णांक v4l2_device_set_name(काष्ठा v4l2_device *v4l2_dev, स्थिर अक्षर *basename,
			 atomic_t *instance);

/**
 * v4l2_device_disconnect - Change V4L2 device state to disconnected.
 *
 * @v4l2_dev: poपूर्णांकer to काष्ठा v4l2_device
 *
 * Should be called when the USB parent disconnects.
 * Since the parent disappears, this ensures that @v4l2_dev करोesn't have
 * an invalid parent poपूर्णांकer.
 *
 * .. note:: This function sets @v4l2_dev->dev to शून्य.
 */
व्योम v4l2_device_disconnect(काष्ठा v4l2_device *v4l2_dev);

/**
 *  v4l2_device_unरेजिस्टर - Unरेजिस्टर all sub-devices and any other
 *	 resources related to @v4l2_dev.
 *
 * @v4l2_dev: poपूर्णांकer to काष्ठा v4l2_device
 */
व्योम v4l2_device_unरेजिस्टर(काष्ठा v4l2_device *v4l2_dev);

/**
 * v4l2_device_रेजिस्टर_subdev - Registers a subdev with a v4l2 device.
 *
 * @v4l2_dev: poपूर्णांकer to काष्ठा &v4l2_device
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 *
 * While रेजिस्टरed, the subdev module is marked as in-use.
 *
 * An error is वापसed अगर the module is no दीर्घer loaded on any attempts
 * to रेजिस्टर it.
 */
पूर्णांक __must_check v4l2_device_रेजिस्टर_subdev(काष्ठा v4l2_device *v4l2_dev,
					     काष्ठा v4l2_subdev *sd);

/**
 * v4l2_device_unरेजिस्टर_subdev - Unरेजिस्टरs a subdev with a v4l2 device.
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 *
 * .. note ::
 *
 *	Can also be called अगर the subdev wasn't रेजिस्टरed. In such
 *	हाल, it will करो nothing.
 */
व्योम v4l2_device_unरेजिस्टर_subdev(काष्ठा v4l2_subdev *sd);

/**
 * __v4l2_device_रेजिस्टर_subdev_nodes - Registers device nodes क्रम
 *      all subdevs of the v4l2 device that are marked with the
 *      %V4L2_SUBDEV_FL_HAS_DEVNODE flag.
 *
 * @v4l2_dev: poपूर्णांकer to काष्ठा v4l2_device
 * @पढ़ो_only: subdevices पढ़ो-only flag. True to रेजिस्टर the subdevices
 *	device nodes in पढ़ो-only mode, false to allow full access to the
 *	subdevice userspace API.
 */
पूर्णांक __must_check
__v4l2_device_रेजिस्टर_subdev_nodes(काष्ठा v4l2_device *v4l2_dev,
				    bool पढ़ो_only);

/**
 * v4l2_device_रेजिस्टर_subdev_nodes - Registers subdevices device nodes with
 *	unrestricted access to the subdevice userspace operations
 *
 * Internally calls __v4l2_device_रेजिस्टर_subdev_nodes(). See its करोcumentation
 * क्रम more details.
 *
 * @v4l2_dev: poपूर्णांकer to काष्ठा v4l2_device
 */
अटल अंतरभूत पूर्णांक __must_check
v4l2_device_रेजिस्टर_subdev_nodes(काष्ठा v4l2_device *v4l2_dev)
अणु
#अगर defined(CONFIG_VIDEO_V4L2_SUBDEV_API)
	वापस __v4l2_device_रेजिस्टर_subdev_nodes(v4l2_dev, false);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/**
 * v4l2_device_रेजिस्टर_ro_subdev_nodes - Registers subdevices device nodes
 *	in पढ़ो-only mode
 *
 * Internally calls __v4l2_device_रेजिस्टर_subdev_nodes(). See its करोcumentation
 * क्रम more details.
 *
 * @v4l2_dev: poपूर्णांकer to काष्ठा v4l2_device
 */
अटल अंतरभूत पूर्णांक __must_check
v4l2_device_रेजिस्टर_ro_subdev_nodes(काष्ठा v4l2_device *v4l2_dev)
अणु
#अगर defined(CONFIG_VIDEO_V4L2_SUBDEV_API)
	वापस __v4l2_device_रेजिस्टर_subdev_nodes(v4l2_dev, true);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/**
 * v4l2_subdev_notअगरy - Sends a notअगरication to v4l2_device.
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 * @notअगरication: type of notअगरication. Please notice that the notअगरication
 *	type is driver-specअगरic.
 * @arg: arguments क्रम the notअगरication. Those are specअगरic to each
 *	notअगरication type.
 */
अटल अंतरभूत व्योम v4l2_subdev_notअगरy(काष्ठा v4l2_subdev *sd,
				      अचिन्हित पूर्णांक notअगरication, व्योम *arg)
अणु
	अगर (sd && sd->v4l2_dev && sd->v4l2_dev->notअगरy)
		sd->v4l2_dev->notअगरy(sd, notअगरication, arg);
पूर्ण

/**
 * v4l2_device_supports_requests - Test अगर requests are supported.
 *
 * @v4l2_dev: poपूर्णांकer to काष्ठा v4l2_device
 */
अटल अंतरभूत bool v4l2_device_supports_requests(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस v4l2_dev->mdev && v4l2_dev->mdev->ops &&
	       v4l2_dev->mdev->ops->req_queue;
पूर्ण

/* Helper macros to iterate over all subdevs. */

/**
 * v4l2_device_क्रम_each_subdev - Helper macro that पूर्णांकerates over all
 *	sub-devices of a given &v4l2_device.
 *
 * @sd: poपूर्णांकer that will be filled by the macro with all
 *	&काष्ठा v4l2_subdev poपूर्णांकer used as an iterator by the loop.
 * @v4l2_dev: &काष्ठा v4l2_device owning the sub-devices to iterate over.
 *
 * This macro iterates over all sub-devices owned by the @v4l2_dev device.
 * It acts as a क्रम loop iterator and executes the next statement with
 * the @sd variable poपूर्णांकing to each sub-device in turn.
 */
#घोषणा v4l2_device_क्रम_each_subdev(sd, v4l2_dev)			\
	list_क्रम_each_entry(sd, &(v4l2_dev)->subdevs, list)

/**
 * __v4l2_device_call_subdevs_p - Calls the specअगरied operation क्रम
 *	all subdevs matching the condition.
 *
 * @v4l2_dev: &काष्ठा v4l2_device owning the sub-devices to iterate over.
 * @sd: poपूर्णांकer that will be filled by the macro with all
 *	&काष्ठा v4l2_subdev poपूर्णांकer used as an iterator by the loop.
 * @cond: condition to be match
 * @o: name of the element at &काष्ठा v4l2_subdev_ops that contains @f.
 *     Each element there groups a set of operations functions.
 * @f: operation function that will be called अगर @cond matches.
 *	The operation functions are defined in groups, according to
 *	each element at &काष्ठा v4l2_subdev_ops.
 * @args: arguments क्रम @f.
 *
 * Ignore any errors.
 *
 * Note: subdevs cannot be added or deleted जबतक walking
 * the subdevs list.
 */
#घोषणा __v4l2_device_call_subdevs_p(v4l2_dev, sd, cond, o, f, args...)	\
	करो अणु								\
		list_क्रम_each_entry((sd), &(v4l2_dev)->subdevs, list)	\
			अगर ((cond) && (sd)->ops->o && (sd)->ops->o->f)	\
				(sd)->ops->o->f((sd) , ##args);		\
	पूर्ण जबतक (0)

/**
 * __v4l2_device_call_subdevs - Calls the specअगरied operation क्रम
 *	all subdevs matching the condition.
 *
 * @v4l2_dev: &काष्ठा v4l2_device owning the sub-devices to iterate over.
 * @cond: condition to be match
 * @o: name of the element at &काष्ठा v4l2_subdev_ops that contains @f.
 *     Each element there groups a set of operations functions.
 * @f: operation function that will be called अगर @cond matches.
 *	The operation functions are defined in groups, according to
 *	each element at &काष्ठा v4l2_subdev_ops.
 * @args: arguments क्रम @f.
 *
 * Ignore any errors.
 *
 * Note: subdevs cannot be added or deleted जबतक walking
 * the subdevs list.
 */
#घोषणा __v4l2_device_call_subdevs(v4l2_dev, cond, o, f, args...)	\
	करो अणु								\
		काष्ठा v4l2_subdev *__sd;				\
									\
		__v4l2_device_call_subdevs_p(v4l2_dev, __sd, cond, o,	\
						f , ##args);		\
	पूर्ण जबतक (0)

/**
 * __v4l2_device_call_subdevs_until_err_p - Calls the specअगरied operation क्रम
 *	all subdevs matching the condition.
 *
 * @v4l2_dev: &काष्ठा v4l2_device owning the sub-devices to iterate over.
 * @sd: poपूर्णांकer that will be filled by the macro with all
 *	&काष्ठा v4l2_subdev sub-devices associated with @v4l2_dev.
 * @cond: condition to be match
 * @o: name of the element at &काष्ठा v4l2_subdev_ops that contains @f.
 *     Each element there groups a set of operations functions.
 * @f: operation function that will be called अगर @cond matches.
 *	The operation functions are defined in groups, according to
 *	each element at &काष्ठा v4l2_subdev_ops.
 * @args: arguments क्रम @f.
 *
 * Return:
 *
 * If the operation वापसs an error other than 0 or ``-ENOIOCTLCMD``
 * क्रम any subdevice, then पात and वापस with that error code, zero
 * otherwise.
 *
 * Note: subdevs cannot be added or deleted जबतक walking
 * the subdevs list.
 */
#घोषणा __v4l2_device_call_subdevs_until_err_p(v4l2_dev, sd, cond, o, f, args...) \
(अणु									\
	दीर्घ __err = 0;							\
									\
	list_क्रम_each_entry((sd), &(v4l2_dev)->subdevs, list) अणु		\
		अगर ((cond) && (sd)->ops->o && (sd)->ops->o->f)		\
			__err = (sd)->ops->o->f((sd) , ##args);		\
		अगर (__err && __err != -ENOIOCTLCMD)			\
			अवरोध;						\
	पूर्ण								\
	(__err == -ENOIOCTLCMD) ? 0 : __err;				\
पूर्ण)

/**
 * __v4l2_device_call_subdevs_until_err - Calls the specअगरied operation क्रम
 *	all subdevs matching the condition.
 *
 * @v4l2_dev: &काष्ठा v4l2_device owning the sub-devices to iterate over.
 * @cond: condition to be match
 * @o: name of the element at &काष्ठा v4l2_subdev_ops that contains @f.
 *     Each element there groups a set of operations functions.
 * @f: operation function that will be called अगर @cond matches.
 *	The operation functions are defined in groups, according to
 *	each element at &काष्ठा v4l2_subdev_ops.
 * @args: arguments क्रम @f.
 *
 * Return:
 *
 * If the operation वापसs an error other than 0 or ``-ENOIOCTLCMD``
 * क्रम any subdevice, then पात and वापस with that error code,
 * zero otherwise.
 *
 * Note: subdevs cannot be added or deleted जबतक walking
 * the subdevs list.
 */
#घोषणा __v4l2_device_call_subdevs_until_err(v4l2_dev, cond, o, f, args...) \
(अणु									\
	काष्ठा v4l2_subdev *__sd;					\
	__v4l2_device_call_subdevs_until_err_p(v4l2_dev, __sd, cond, o,	\
						f , ##args);		\
पूर्ण)

/**
 * v4l2_device_call_all - Calls the specअगरied operation क्रम
 *	all subdevs matching the &v4l2_subdev.grp_id, as asचिन्हित
 *	by the bridge driver.
 *
 * @v4l2_dev: &काष्ठा v4l2_device owning the sub-devices to iterate over.
 * @grpid: &काष्ठा v4l2_subdev->grp_id group ID to match.
 *	    Use 0 to match them all.
 * @o: name of the element at &काष्ठा v4l2_subdev_ops that contains @f.
 *     Each element there groups a set of operations functions.
 * @f: operation function that will be called अगर @cond matches.
 *	The operation functions are defined in groups, according to
 *	each element at &काष्ठा v4l2_subdev_ops.
 * @args: arguments क्रम @f.
 *
 * Ignore any errors.
 *
 * Note: subdevs cannot be added or deleted जबतक walking
 * the subdevs list.
 */
#घोषणा v4l2_device_call_all(v4l2_dev, grpid, o, f, args...)		\
	करो अणु								\
		काष्ठा v4l2_subdev *__sd;				\
									\
		__v4l2_device_call_subdevs_p(v4l2_dev, __sd,		\
			(grpid) == 0 || __sd->grp_id == (grpid), o, f ,	\
			##args);					\
	पूर्ण जबतक (0)

/**
 * v4l2_device_call_until_err - Calls the specअगरied operation क्रम
 *	all subdevs matching the &v4l2_subdev.grp_id, as asचिन्हित
 *	by the bridge driver, until an error occurs.
 *
 * @v4l2_dev: &काष्ठा v4l2_device owning the sub-devices to iterate over.
 * @grpid: &काष्ठा v4l2_subdev->grp_id group ID to match.
 *	   Use 0 to match them all.
 * @o: name of the element at &काष्ठा v4l2_subdev_ops that contains @f.
 *     Each element there groups a set of operations functions.
 * @f: operation function that will be called अगर @cond matches.
 *	The operation functions are defined in groups, according to
 *	each element at &काष्ठा v4l2_subdev_ops.
 * @args: arguments क्रम @f.
 *
 * Return:
 *
 * If the operation वापसs an error other than 0 or ``-ENOIOCTLCMD``
 * क्रम any subdevice, then पात and वापस with that error code,
 * zero otherwise.
 *
 * Note: subdevs cannot be added or deleted जबतक walking
 * the subdevs list.
 */
#घोषणा v4l2_device_call_until_err(v4l2_dev, grpid, o, f, args...)	\
(अणु									\
	काष्ठा v4l2_subdev *__sd;					\
	__v4l2_device_call_subdevs_until_err_p(v4l2_dev, __sd,		\
			(grpid) == 0 || __sd->grp_id == (grpid), o, f ,	\
			##args);					\
पूर्ण)

/**
 * v4l2_device_mask_call_all - Calls the specअगरied operation क्रम
 *	all subdevices where a group ID matches a specअगरied biपंचांगask.
 *
 * @v4l2_dev: &काष्ठा v4l2_device owning the sub-devices to iterate over.
 * @grpmsk: biपंचांगask to be checked against &काष्ठा v4l2_subdev->grp_id
 *	    group ID to be matched. Use 0 to match them all.
 * @o: name of the element at &काष्ठा v4l2_subdev_ops that contains @f.
 *     Each element there groups a set of operations functions.
 * @f: operation function that will be called अगर @cond matches.
 *	The operation functions are defined in groups, according to
 *	each element at &काष्ठा v4l2_subdev_ops.
 * @args: arguments क्रम @f.
 *
 * Ignore any errors.
 *
 * Note: subdevs cannot be added or deleted जबतक walking
 * the subdevs list.
 */
#घोषणा v4l2_device_mask_call_all(v4l2_dev, grpmsk, o, f, args...)	\
	करो अणु								\
		काष्ठा v4l2_subdev *__sd;				\
									\
		__v4l2_device_call_subdevs_p(v4l2_dev, __sd,		\
			(grpmsk) == 0 || (__sd->grp_id & (grpmsk)), o,	\
			f , ##args);					\
	पूर्ण जबतक (0)

/**
 * v4l2_device_mask_call_until_err - Calls the specअगरied operation क्रम
 *	all subdevices where a group ID matches a specअगरied biपंचांगask.
 *
 * @v4l2_dev: &काष्ठा v4l2_device owning the sub-devices to iterate over.
 * @grpmsk: biपंचांगask to be checked against &काष्ठा v4l2_subdev->grp_id
 *	    group ID to be matched. Use 0 to match them all.
 * @o: name of the element at &काष्ठा v4l2_subdev_ops that contains @f.
 *     Each element there groups a set of operations functions.
 * @f: operation function that will be called अगर @cond matches.
 *	The operation functions are defined in groups, according to
 *	each element at &काष्ठा v4l2_subdev_ops.
 * @args: arguments क्रम @f.
 *
 * Return:
 *
 * If the operation वापसs an error other than 0 or ``-ENOIOCTLCMD``
 * क्रम any subdevice, then पात and वापस with that error code,
 * zero otherwise.
 *
 * Note: subdevs cannot be added or deleted जबतक walking
 * the subdevs list.
 */
#घोषणा v4l2_device_mask_call_until_err(v4l2_dev, grpmsk, o, f, args...) \
(अणु									\
	काष्ठा v4l2_subdev *__sd;					\
	__v4l2_device_call_subdevs_until_err_p(v4l2_dev, __sd,		\
			(grpmsk) == 0 || (__sd->grp_id & (grpmsk)), o,	\
			f , ##args);					\
पूर्ण)


/**
 * v4l2_device_has_op - checks अगर any subdev with matching grpid has a
 *	given ops.
 *
 * @v4l2_dev: &काष्ठा v4l2_device owning the sub-devices to iterate over.
 * @grpid: &काष्ठा v4l2_subdev->grp_id group ID to match.
 *	   Use 0 to match them all.
 * @o: name of the element at &काष्ठा v4l2_subdev_ops that contains @f.
 *     Each element there groups a set of operations functions.
 * @f: operation function that will be called अगर @cond matches.
 *	The operation functions are defined in groups, according to
 *	each element at &काष्ठा v4l2_subdev_ops.
 */
#घोषणा v4l2_device_has_op(v4l2_dev, grpid, o, f)			\
(अणु									\
	काष्ठा v4l2_subdev *__sd;					\
	bool __result = false;						\
	list_क्रम_each_entry(__sd, &(v4l2_dev)->subdevs, list) अणु		\
		अगर ((grpid) && __sd->grp_id != (grpid))			\
			जारी;					\
		अगर (v4l2_subdev_has_op(__sd, o, f)) अणु			\
			__result = true;				\
			अवरोध;						\
		पूर्ण							\
	पूर्ण								\
	__result;							\
पूर्ण)

/**
 * v4l2_device_mask_has_op - checks अगर any subdev with matching group
 *	mask has a given ops.
 *
 * @v4l2_dev: &काष्ठा v4l2_device owning the sub-devices to iterate over.
 * @grpmsk: biपंचांगask to be checked against &काष्ठा v4l2_subdev->grp_id
 *	    group ID to be matched. Use 0 to match them all.
 * @o: name of the element at &काष्ठा v4l2_subdev_ops that contains @f.
 *     Each element there groups a set of operations functions.
 * @f: operation function that will be called अगर @cond matches.
 *	The operation functions are defined in groups, according to
 *	each element at &काष्ठा v4l2_subdev_ops.
 */
#घोषणा v4l2_device_mask_has_op(v4l2_dev, grpmsk, o, f)			\
(अणु									\
	काष्ठा v4l2_subdev *__sd;					\
	bool __result = false;						\
	list_क्रम_each_entry(__sd, &(v4l2_dev)->subdevs, list) अणु		\
		अगर ((grpmsk) && !(__sd->grp_id & (grpmsk)))		\
			जारी;					\
		अगर (v4l2_subdev_has_op(__sd, o, f)) अणु			\
			__result = true;				\
			अवरोध;						\
		पूर्ण							\
	पूर्ण								\
	__result;							\
पूर्ण)

#पूर्ण_अगर
