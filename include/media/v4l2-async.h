<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * V4L2 asynchronous subdevice registration API
 *
 * Copyright (C) 2012-2013, Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 */

#अगर_अघोषित V4L2_ASYNC_H
#घोषणा V4L2_ASYNC_H

#समावेश <linux/list.h>
#समावेश <linux/mutex.h>

काष्ठा dentry;
काष्ठा device;
काष्ठा device_node;
काष्ठा v4l2_device;
काष्ठा v4l2_subdev;
काष्ठा v4l2_async_notअगरier;

/**
 * क्रमागत v4l2_async_match_type - type of asynchronous subdevice logic to be used
 *	in order to identअगरy a match
 *
 * @V4L2_ASYNC_MATCH_I2C: Match will check क्रम I2C adapter ID and address
 * @V4L2_ASYNC_MATCH_FWNODE: Match will use firmware node
 *
 * This क्रमागत is used by the asynchronous sub-device logic to define the
 * algorithm that will be used to match an asynchronous device.
 */
क्रमागत v4l2_async_match_type अणु
	V4L2_ASYNC_MATCH_I2C,
	V4L2_ASYNC_MATCH_FWNODE,
पूर्ण;

/**
 * काष्ठा v4l2_async_subdev - sub-device descriptor, as known to a bridge
 *
 * @match_type:	type of match that will be used
 * @match:	जोड़ of per-bus type matching data sets
 * @match.fwnode:
 *		poपूर्णांकer to &काष्ठा fwnode_handle to be matched.
 *		Used अगर @match_type is %V4L2_ASYNC_MATCH_FWNODE.
 * @match.i2c:	embedded काष्ठा with I2C parameters to be matched.
 *		Both @match.i2c.adapter_id and @match.i2c.address
 *		should be matched.
 *		Used अगर @match_type is %V4L2_ASYNC_MATCH_I2C.
 * @match.i2c.adapter_id:
 *		I2C adapter ID to be matched.
 *		Used अगर @match_type is %V4L2_ASYNC_MATCH_I2C.
 * @match.i2c.address:
 *		I2C address to be matched.
 *		Used अगर @match_type is %V4L2_ASYNC_MATCH_I2C.
 * @asd_list:	used to add काष्ठा v4l2_async_subdev objects to the
 *		master notअगरier @asd_list
 * @list:	used to link काष्ठा v4l2_async_subdev objects, रुकोing to be
 *		probed, to a notअगरier->रुकोing list
 *
 * When this काष्ठा is used as a member in a driver specअगरic काष्ठा,
 * the driver specअगरic काष्ठा shall contain the &काष्ठा
 * v4l2_async_subdev as its first member.
 */
काष्ठा v4l2_async_subdev अणु
	क्रमागत v4l2_async_match_type match_type;
	जोड़ अणु
		काष्ठा fwnode_handle *fwnode;
		काष्ठा अणु
			पूर्णांक adapter_id;
			अचिन्हित लघु address;
		पूर्ण i2c;
	पूर्ण match;

	/* v4l2-async core निजी: not to be used by drivers */
	काष्ठा list_head list;
	काष्ठा list_head asd_list;
पूर्ण;

/**
 * काष्ठा v4l2_async_notअगरier_operations - Asynchronous V4L2 notअगरier operations
 * @bound:	a subdevice driver has successfully probed one of the subdevices
 * @complete:	All subdevices have been probed successfully. The complete
 *		callback is only executed क्रम the root notअगरier.
 * @unbind:	a subdevice is leaving
 */
काष्ठा v4l2_async_notअगरier_operations अणु
	पूर्णांक (*bound)(काष्ठा v4l2_async_notअगरier *notअगरier,
		     काष्ठा v4l2_subdev *subdev,
		     काष्ठा v4l2_async_subdev *asd);
	पूर्णांक (*complete)(काष्ठा v4l2_async_notअगरier *notअगरier);
	व्योम (*unbind)(काष्ठा v4l2_async_notअगरier *notअगरier,
		       काष्ठा v4l2_subdev *subdev,
		       काष्ठा v4l2_async_subdev *asd);
पूर्ण;

/**
 * काष्ठा v4l2_async_notअगरier - v4l2_device notअगरier data
 *
 * @ops:	notअगरier operations
 * @v4l2_dev:	v4l2_device of the root notअगरier, शून्य otherwise
 * @sd:		sub-device that रेजिस्टरed the notअगरier, शून्य otherwise
 * @parent:	parent notअगरier
 * @asd_list:	master list of काष्ठा v4l2_async_subdev
 * @रुकोing:	list of काष्ठा v4l2_async_subdev, रुकोing क्रम their drivers
 * @करोne:	list of काष्ठा v4l2_subdev, alपढ़ोy probed
 * @list:	member in a global list of notअगरiers
 */
काष्ठा v4l2_async_notअगरier अणु
	स्थिर काष्ठा v4l2_async_notअगरier_operations *ops;
	काष्ठा v4l2_device *v4l2_dev;
	काष्ठा v4l2_subdev *sd;
	काष्ठा v4l2_async_notअगरier *parent;
	काष्ठा list_head asd_list;
	काष्ठा list_head रुकोing;
	काष्ठा list_head करोne;
	काष्ठा list_head list;
पूर्ण;

/**
 * v4l2_async_debug_init - Initialize debugging tools.
 *
 * @debugfs_dir: poपूर्णांकer to the parent debugfs &काष्ठा dentry
 */
व्योम v4l2_async_debug_init(काष्ठा dentry *debugfs_dir);

/**
 * v4l2_async_notअगरier_init - Initialize a notअगरier.
 *
 * @notअगरier: poपूर्णांकer to &काष्ठा v4l2_async_notअगरier
 *
 * This function initializes the notअगरier @asd_list. It must be called
 * beक्रमe adding a subdevice to a notअगरier, using one of:
 * @v4l2_async_notअगरier_add_fwnode_remote_subdev,
 * @v4l2_async_notअगरier_add_fwnode_subdev,
 * @v4l2_async_notअगरier_add_i2c_subdev,
 * @__v4l2_async_notअगरier_add_subdev or
 * @v4l2_async_notअगरier_parse_fwnode_endpoपूर्णांकs.
 */
व्योम v4l2_async_notअगरier_init(काष्ठा v4l2_async_notअगरier *notअगरier);

/**
 * __v4l2_async_notअगरier_add_subdev - Add an async subdev to the
 *				notअगरier's master asd list.
 *
 * @notअगरier: poपूर्णांकer to &काष्ठा v4l2_async_notअगरier
 * @asd: poपूर्णांकer to &काष्ठा v4l2_async_subdev
 *
 * \warning: Drivers should aव्योम using this function and instead use one of:
 * @v4l2_async_notअगरier_add_fwnode_subdev,
 * @v4l2_async_notअगरier_add_fwnode_remote_subdev or
 * @v4l2_async_notअगरier_add_i2c_subdev.
 *
 * Call this function beक्रमe रेजिस्टरing a notअगरier to link the provided @asd to
 * the notअगरiers master @asd_list. The @asd must be allocated with k*alloc() as
 * it will be मुक्तd by the framework when the notअगरier is destroyed.
 */
पूर्णांक __v4l2_async_notअगरier_add_subdev(काष्ठा v4l2_async_notअगरier *notअगरier,
				   काष्ठा v4l2_async_subdev *asd);

काष्ठा v4l2_async_subdev *
__v4l2_async_notअगरier_add_fwnode_subdev(काष्ठा v4l2_async_notअगरier *notअगरier,
					काष्ठा fwnode_handle *fwnode,
					अचिन्हित पूर्णांक asd_काष्ठा_size);
/**
 * v4l2_async_notअगरier_add_fwnode_subdev - Allocate and add a fwnode async
 *				subdev to the notअगरier's master asd_list.
 *
 * @notअगरier: poपूर्णांकer to &काष्ठा v4l2_async_notअगरier
 * @fwnode: fwnode handle of the sub-device to be matched, poपूर्णांकer to
 *	    &काष्ठा fwnode_handle
 * @type: Type of the driver's async sub-device काष्ठा. The &काष्ठा
 *	  v4l2_async_subdev shall be the first member of the driver's async
 *	  sub-device काष्ठा, i.e. both begin at the same memory address.
 *
 * Allocate a fwnode-matched asd of size asd_काष्ठा_size, and add it to the
 * notअगरiers @asd_list. The function also माला_लो a reference of the fwnode which
 * is released later at notअगरier cleanup समय.
 */
#घोषणा v4l2_async_notअगरier_add_fwnode_subdev(notअगरier, fwnode, type)	\
	((type *)__v4l2_async_notअगरier_add_fwnode_subdev(notअगरier, fwnode, \
							   माप(type)))

काष्ठा v4l2_async_subdev *
__v4l2_async_notअगरier_add_fwnode_remote_subdev(काष्ठा v4l2_async_notअगरier *notअगर,
					       काष्ठा fwnode_handle *endpoपूर्णांक,
					       अचिन्हित पूर्णांक asd_काष्ठा_size);
/**
 * v4l2_async_notअगरier_add_fwnode_remote_subdev - Allocate and add a fwnode
 *						  remote async subdev to the
 *						  notअगरier's master asd_list.
 *
 * @notअगरier: poपूर्णांकer to &काष्ठा v4l2_async_notअगरier
 * @ep: local endpoपूर्णांक poपूर्णांकing to the remote sub-device to be matched,
 *	poपूर्णांकer to &काष्ठा fwnode_handle
 * @type: Type of the driver's async sub-device काष्ठा. The &काष्ठा
 *	  v4l2_async_subdev shall be the first member of the driver's async
 *	  sub-device काष्ठा, i.e. both begin at the same memory address.
 *
 * Gets the remote endpoपूर्णांक of a given local endpoपूर्णांक, set it up क्रम fwnode
 * matching and adds the async sub-device to the notअगरier's @asd_list. The
 * function also माला_लो a reference of the fwnode which is released later at
 * notअगरier cleanup समय.
 *
 * This is just like @v4l2_async_notअगरier_add_fwnode_subdev, but with the
 * exception that the fwnode refers to a local endpoपूर्णांक, not the remote one.
 */
#घोषणा v4l2_async_notअगरier_add_fwnode_remote_subdev(notअगरier, ep, type) \
	((type *)							\
	 __v4l2_async_notअगरier_add_fwnode_remote_subdev(notअगरier, ep,	\
							माप(type)))

काष्ठा v4l2_async_subdev *
__v4l2_async_notअगरier_add_i2c_subdev(काष्ठा v4l2_async_notअगरier *notअगरier,
				     पूर्णांक adapter_id, अचिन्हित लघु address,
				     अचिन्हित पूर्णांक asd_काष्ठा_size);
/**
 * v4l2_async_notअगरier_add_i2c_subdev - Allocate and add an i2c async
 *				subdev to the notअगरier's master asd_list.
 *
 * @notअगरier: poपूर्णांकer to &काष्ठा v4l2_async_notअगरier
 * @adapter: I2C adapter ID to be matched
 * @address: I2C address of sub-device to be matched
 * @type: Type of the driver's async sub-device काष्ठा. The &काष्ठा
 *	  v4l2_async_subdev shall be the first member of the driver's async
 *	  sub-device काष्ठा, i.e. both begin at the same memory address.
 *
 * Same as v4l2_async_notअगरier_add_fwnode_subdev() but क्रम I2C matched
 * sub-devices.
 */
#घोषणा v4l2_async_notअगरier_add_i2c_subdev(notअगरier, adapter, address, type) \
	((type *)__v4l2_async_notअगरier_add_i2c_subdev(notअगरier, adapter, \
						      address, माप(type)))

/**
 * v4l2_async_notअगरier_रेजिस्टर - रेजिस्टरs a subdevice asynchronous notअगरier
 *
 * @v4l2_dev: poपूर्णांकer to &काष्ठा v4l2_device
 * @notअगरier: poपूर्णांकer to &काष्ठा v4l2_async_notअगरier
 */
पूर्णांक v4l2_async_notअगरier_रेजिस्टर(काष्ठा v4l2_device *v4l2_dev,
				 काष्ठा v4l2_async_notअगरier *notअगरier);

/**
 * v4l2_async_subdev_notअगरier_रेजिस्टर - रेजिस्टरs a subdevice asynchronous
 *					 notअगरier क्रम a sub-device
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 * @notअगरier: poपूर्णांकer to &काष्ठा v4l2_async_notअगरier
 */
पूर्णांक v4l2_async_subdev_notअगरier_रेजिस्टर(काष्ठा v4l2_subdev *sd,
					काष्ठा v4l2_async_notअगरier *notअगरier);

/**
 * v4l2_async_notअगरier_unरेजिस्टर - unरेजिस्टरs a subdevice
 *	asynchronous notअगरier
 *
 * @notअगरier: poपूर्णांकer to &काष्ठा v4l2_async_notअगरier
 */
व्योम v4l2_async_notअगरier_unरेजिस्टर(काष्ठा v4l2_async_notअगरier *notअगरier);

/**
 * v4l2_async_notअगरier_cleanup - clean up notअगरier resources
 * @notअगरier: the notअगरier the resources of which are to be cleaned up
 *
 * Release memory resources related to a notअगरier, including the async
 * sub-devices allocated क्रम the purposes of the notअगरier but not the notअगरier
 * itself. The user is responsible क्रम calling this function to clean up the
 * notअगरier after calling
 * @v4l2_async_notअगरier_add_fwnode_remote_subdev,
 * @v4l2_async_notअगरier_add_fwnode_subdev,
 * @v4l2_async_notअगरier_add_i2c_subdev,
 * @__v4l2_async_notअगरier_add_subdev or
 * @v4l2_async_notअगरier_parse_fwnode_endpoपूर्णांकs.
 *
 * There is no harm from calling v4l2_async_notअगरier_cleanup in other
 * हालs as दीर्घ as its memory has been zeroed after it has been
 * allocated.
 */
व्योम v4l2_async_notअगरier_cleanup(काष्ठा v4l2_async_notअगरier *notअगरier);

/**
 * v4l2_async_रेजिस्टर_subdev - रेजिस्टरs a sub-device to the asynchronous
 *	subdevice framework
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 */
पूर्णांक v4l2_async_रेजिस्टर_subdev(काष्ठा v4l2_subdev *sd);

/**
 * v4l2_async_रेजिस्टर_subdev_sensor - रेजिस्टरs a sensor sub-device to the
 *				       asynchronous sub-device framework and
 *				       parse set up common sensor related
 *				       devices
 *
 * @sd: poपूर्णांकer to काष्ठा &v4l2_subdev
 *
 * This function is just like v4l2_async_रेजिस्टर_subdev() with the exception
 * that calling it will also parse firmware पूर्णांकerfaces क्रम remote references
 * using v4l2_async_notअगरier_parse_fwnode_sensor() and रेजिस्टरs the
 * async sub-devices. The sub-device is similarly unरेजिस्टरed by calling
 * v4l2_async_unरेजिस्टर_subdev().
 *
 * While रेजिस्टरed, the subdev module is marked as in-use.
 *
 * An error is वापसed अगर the module is no दीर्घer loaded on any attempts
 * to रेजिस्टर it.
 */
पूर्णांक __must_check
v4l2_async_रेजिस्टर_subdev_sensor(काष्ठा v4l2_subdev *sd);

/**
 * v4l2_async_unरेजिस्टर_subdev - unरेजिस्टरs a sub-device to the asynchronous
 *	subdevice framework
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 */
व्योम v4l2_async_unरेजिस्टर_subdev(काष्ठा v4l2_subdev *sd);
#पूर्ण_अगर
