<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Surface System Aggregator Module (SSAM) bus and client-device subप्रणाली.
 *
 * Main पूर्णांकerface क्रम the surface-aggregator bus, surface-aggregator client
 * devices, and respective drivers building on top of the SSAM controller.
 * Provides support क्रम non-platक्रमm/non-ACPI SSAM clients via dedicated
 * subप्रणाली.
 *
 * Copyright (C) 2019-2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#अगर_अघोषित _LINUX_SURFACE_AGGREGATOR_DEVICE_H
#घोषणा _LINUX_SURFACE_AGGREGATOR_DEVICE_H

#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/types.h>

#समावेश <linux/surface_aggregator/controller.h>


/* -- Surface System Aggregator Module bus. --------------------------------- */

/**
 * क्रमागत ssam_device_करोमुख्य - SAM device करोमुख्य.
 * @SSAM_DOMAIN_VIRTUAL:   Virtual device.
 * @SSAM_DOMAIN_SERIALHUB: Physical device connected via Surface Serial Hub.
 */
क्रमागत ssam_device_करोमुख्य अणु
	SSAM_DOMAIN_VIRTUAL   = 0x00,
	SSAM_DOMAIN_SERIALHUB = 0x01,
पूर्ण;

/**
 * क्रमागत ssam_भव_tc - Target categories क्रम the भव SAM करोमुख्य.
 * @SSAM_VIRTUAL_TC_HUB: Device hub category.
 */
क्रमागत ssam_भव_tc अणु
	SSAM_VIRTUAL_TC_HUB = 0x00,
पूर्ण;

/**
 * काष्ठा ssam_device_uid - Unique identअगरier क्रम SSAM device.
 * @करोमुख्य:   Doमुख्य of the device.
 * @category: Target category of the device.
 * @target:   Target ID of the device.
 * @instance: Instance ID of the device.
 * @function: Sub-function of the device. This field can be used to split a
 *            single SAM device पूर्णांकo multiple भव subdevices to separate
 *            dअगरferent functionality of that device and allow one driver per
 *            such functionality.
 */
काष्ठा ssam_device_uid अणु
	u8 करोमुख्य;
	u8 category;
	u8 target;
	u8 instance;
	u8 function;
पूर्ण;

/*
 * Special values क्रम device matching.
 *
 * These values are पूर्णांकended to be used with SSAM_DEVICE(), SSAM_VDEV(), and
 * SSAM_SDEV() exclusively. Specअगरically, they are used to initialize the
 * match_flags member of the device ID काष्ठाure. Do not use them directly
 * with काष्ठा ssam_device_id or काष्ठा ssam_device_uid.
 */
#घोषणा SSAM_ANY_TID		0xffff
#घोषणा SSAM_ANY_IID		0xffff
#घोषणा SSAM_ANY_FUN		0xffff

/**
 * SSAM_DEVICE() - Initialize a &काष्ठा ssam_device_id with the given
 * parameters.
 * @d:   Doमुख्य of the device.
 * @cat: Target category of the device.
 * @tid: Target ID of the device.
 * @iid: Instance ID of the device.
 * @fun: Sub-function of the device.
 *
 * Initializes a &काष्ठा ssam_device_id with the given parameters. See &काष्ठा
 * ssam_device_uid क्रम details regarding the parameters. The special values
 * %SSAM_ANY_TID, %SSAM_ANY_IID, and %SSAM_ANY_FUN can be used to specअगरy that
 * matching should ignore target ID, instance ID, and/or sub-function,
 * respectively. This macro initializes the ``match_flags`` field based on the
 * given parameters.
 *
 * Note: The parameters @d and @cat must be valid &u8 values, the parameters
 * @tid, @iid, and @fun must be either valid &u8 values or %SSAM_ANY_TID,
 * %SSAM_ANY_IID, or %SSAM_ANY_FUN, respectively. Other non-&u8 values are not
 * allowed.
 */
#घोषणा SSAM_DEVICE(d, cat, tid, iid, fun)					\
	.match_flags = (((tid) != SSAM_ANY_TID) ? SSAM_MATCH_TARGET : 0)	\
		     | (((iid) != SSAM_ANY_IID) ? SSAM_MATCH_INSTANCE : 0)	\
		     | (((fun) != SSAM_ANY_FUN) ? SSAM_MATCH_FUNCTION : 0),	\
	.करोमुख्य   = d,								\
	.category = cat,							\
	.target   = __builtin_choose_expr((tid) != SSAM_ANY_TID, (tid), 0),	\
	.instance = __builtin_choose_expr((iid) != SSAM_ANY_IID, (iid), 0),	\
	.function = __builtin_choose_expr((fun) != SSAM_ANY_FUN, (fun), 0)

/**
 * SSAM_VDEV() - Initialize a &काष्ठा ssam_device_id as भव device with
 * the given parameters.
 * @cat: Target category of the device.
 * @tid: Target ID of the device.
 * @iid: Instance ID of the device.
 * @fun: Sub-function of the device.
 *
 * Initializes a &काष्ठा ssam_device_id with the given parameters in the
 * भव करोमुख्य. See &काष्ठा ssam_device_uid क्रम details regarding the
 * parameters. The special values %SSAM_ANY_TID, %SSAM_ANY_IID, and
 * %SSAM_ANY_FUN can be used to specअगरy that matching should ignore target ID,
 * instance ID, and/or sub-function, respectively. This macro initializes the
 * ``match_flags`` field based on the given parameters.
 *
 * Note: The parameter @cat must be a valid &u8 value, the parameters @tid,
 * @iid, and @fun must be either valid &u8 values or %SSAM_ANY_TID,
 * %SSAM_ANY_IID, or %SSAM_ANY_FUN, respectively. Other non-&u8 values are not
 * allowed.
 */
#घोषणा SSAM_VDEV(cat, tid, iid, fun) \
	SSAM_DEVICE(SSAM_DOMAIN_VIRTUAL, SSAM_VIRTUAL_TC_##cat, tid, iid, fun)

/**
 * SSAM_SDEV() - Initialize a &काष्ठा ssam_device_id as physical SSH device
 * with the given parameters.
 * @cat: Target category of the device.
 * @tid: Target ID of the device.
 * @iid: Instance ID of the device.
 * @fun: Sub-function of the device.
 *
 * Initializes a &काष्ठा ssam_device_id with the given parameters in the SSH
 * करोमुख्य. See &काष्ठा ssam_device_uid क्रम details regarding the parameters.
 * The special values %SSAM_ANY_TID, %SSAM_ANY_IID, and %SSAM_ANY_FUN can be
 * used to specअगरy that matching should ignore target ID, instance ID, and/or
 * sub-function, respectively. This macro initializes the ``match_flags``
 * field based on the given parameters.
 *
 * Note: The parameter @cat must be a valid &u8 value, the parameters @tid,
 * @iid, and @fun must be either valid &u8 values or %SSAM_ANY_TID,
 * %SSAM_ANY_IID, or %SSAM_ANY_FUN, respectively. Other non-&u8 values are not
 * allowed.
 */
#घोषणा SSAM_SDEV(cat, tid, iid, fun) \
	SSAM_DEVICE(SSAM_DOMAIN_SERIALHUB, SSAM_SSH_TC_##cat, tid, iid, fun)

/**
 * काष्ठा ssam_device - SSAM client device.
 * @dev:  Driver model representation of the device.
 * @ctrl: SSAM controller managing this device.
 * @uid:  UID identअगरying the device.
 */
काष्ठा ssam_device अणु
	काष्ठा device dev;
	काष्ठा ssam_controller *ctrl;

	काष्ठा ssam_device_uid uid;
पूर्ण;

/**
 * काष्ठा ssam_device_driver - SSAM client device driver.
 * @driver:      Base driver model काष्ठाure.
 * @match_table: Match table specअगरying which devices the driver should bind to.
 * @probe:       Called when the driver is being bound to a device.
 * @हटाओ:      Called when the driver is being unbound from the device.
 */
काष्ठा ssam_device_driver अणु
	काष्ठा device_driver driver;

	स्थिर काष्ठा ssam_device_id *match_table;

	पूर्णांक  (*probe)(काष्ठा ssam_device *sdev);
	व्योम (*हटाओ)(काष्ठा ssam_device *sdev);
पूर्ण;

बाह्य काष्ठा bus_type ssam_bus_type;
बाह्य स्थिर काष्ठा device_type ssam_device_type;

/**
 * is_ssam_device() - Check अगर the given device is a SSAM client device.
 * @d: The device to test the type of.
 *
 * Return: Returns %true अगर the specअगरied device is of type &काष्ठा
 * ssam_device, i.e. the device type poपूर्णांकs to %ssam_device_type, and %false
 * otherwise.
 */
अटल अंतरभूत bool is_ssam_device(काष्ठा device *d)
अणु
	वापस d->type == &ssam_device_type;
पूर्ण

/**
 * to_ssam_device() - Casts the given device to a SSAM client device.
 * @d: The device to cast.
 *
 * Casts the given &काष्ठा device to a &काष्ठा ssam_device. The caller has to
 * ensure that the given device is actually enबंदd in a &काष्ठा ssam_device,
 * e.g. by calling is_ssam_device().
 *
 * Return: Returns a poपूर्णांकer to the &काष्ठा ssam_device wrapping the given
 * device @d.
 */
अटल अंतरभूत काष्ठा ssam_device *to_ssam_device(काष्ठा device *d)
अणु
	वापस container_of(d, काष्ठा ssam_device, dev);
पूर्ण

/**
 * to_ssam_device_driver() - Casts the given device driver to a SSAM client
 * device driver.
 * @d: The driver to cast.
 *
 * Casts the given &काष्ठा device_driver to a &काष्ठा ssam_device_driver. The
 * caller has to ensure that the given driver is actually enबंदd in a
 * &काष्ठा ssam_device_driver.
 *
 * Return: Returns the poपूर्णांकer to the &काष्ठा ssam_device_driver wrapping the
 * given device driver @d.
 */
अटल अंतरभूत
काष्ठा ssam_device_driver *to_ssam_device_driver(काष्ठा device_driver *d)
अणु
	वापस container_of(d, काष्ठा ssam_device_driver, driver);
पूर्ण

स्थिर काष्ठा ssam_device_id *ssam_device_id_match(स्थिर काष्ठा ssam_device_id *table,
						  स्थिर काष्ठा ssam_device_uid uid);

स्थिर काष्ठा ssam_device_id *ssam_device_get_match(स्थिर काष्ठा ssam_device *dev);

स्थिर व्योम *ssam_device_get_match_data(स्थिर काष्ठा ssam_device *dev);

काष्ठा ssam_device *ssam_device_alloc(काष्ठा ssam_controller *ctrl,
				      काष्ठा ssam_device_uid uid);

पूर्णांक ssam_device_add(काष्ठा ssam_device *sdev);
व्योम ssam_device_हटाओ(काष्ठा ssam_device *sdev);

/**
 * ssam_device_get() - Increment reference count of SSAM client device.
 * @sdev: The device to increment the reference count of.
 *
 * Increments the reference count of the given SSAM client device by
 * incrementing the reference count of the enबंदd &काष्ठा device via
 * get_device().
 *
 * See ssam_device_put() क्रम the counter-part of this function.
 *
 * Return: Returns the device provided as input.
 */
अटल अंतरभूत काष्ठा ssam_device *ssam_device_get(काष्ठा ssam_device *sdev)
अणु
	वापस sdev ? to_ssam_device(get_device(&sdev->dev)) : शून्य;
पूर्ण

/**
 * ssam_device_put() - Decrement reference count of SSAM client device.
 * @sdev: The device to decrement the reference count of.
 *
 * Decrements the reference count of the given SSAM client device by
 * decrementing the reference count of the enबंदd &काष्ठा device via
 * put_device().
 *
 * See ssam_device_get() क्रम the counter-part of this function.
 */
अटल अंतरभूत व्योम ssam_device_put(काष्ठा ssam_device *sdev)
अणु
	अगर (sdev)
		put_device(&sdev->dev);
पूर्ण

/**
 * ssam_device_get_drvdata() - Get driver-data of SSAM client device.
 * @sdev: The device to get the driver-data from.
 *
 * Return: Returns the driver-data of the given device, previously set via
 * ssam_device_set_drvdata().
 */
अटल अंतरभूत व्योम *ssam_device_get_drvdata(काष्ठा ssam_device *sdev)
अणु
	वापस dev_get_drvdata(&sdev->dev);
पूर्ण

/**
 * ssam_device_set_drvdata() - Set driver-data of SSAM client device.
 * @sdev: The device to set the driver-data of.
 * @data: The data to set the device's driver-data poपूर्णांकer to.
 */
अटल अंतरभूत व्योम ssam_device_set_drvdata(काष्ठा ssam_device *sdev, व्योम *data)
अणु
	dev_set_drvdata(&sdev->dev, data);
पूर्ण

पूर्णांक __ssam_device_driver_रेजिस्टर(काष्ठा ssam_device_driver *d, काष्ठा module *o);
व्योम ssam_device_driver_unरेजिस्टर(काष्ठा ssam_device_driver *d);

/**
 * ssam_device_driver_रेजिस्टर() - Register a SSAM client device driver.
 * @drv: The driver to रेजिस्टर.
 */
#घोषणा ssam_device_driver_रेजिस्टर(drv) \
	__ssam_device_driver_रेजिस्टर(drv, THIS_MODULE)

/**
 * module_ssam_device_driver() - Helper macro क्रम SSAM device driver
 * registration.
 * @drv: The driver managed by this module.
 *
 * Helper macro to रेजिस्टर a SSAM device driver via module_init() and
 * module_निकास(). This macro may only be used once per module and replaces the
 * aक्रमementioned definitions.
 */
#घोषणा module_ssam_device_driver(drv)			\
	module_driver(drv, ssam_device_driver_रेजिस्टर,	\
		      ssam_device_driver_unरेजिस्टर)


/* -- Helpers क्रम client-device requests. ----------------------------------- */

/**
 * SSAM_DEFINE_SYNC_REQUEST_CL_N() - Define synchronous client-device SAM
 * request function with neither argument nor वापस value.
 * @name: Name of the generated function.
 * @spec: Specअगरication (&काष्ठा ssam_request_spec_md) defining the request.
 *
 * Defines a function executing the synchronous SAM request specअगरied by
 * @spec, with the request having neither argument nor वापस value. Device
 * specअगरying parameters are not hard-coded, but instead are provided via the
 * client device, specअगरically its UID, supplied when calling this function.
 * The generated function takes care of setting up the request काष्ठा, buffer
 * allocation, as well as execution of the request itself, वापसing once the
 * request has been fully completed. The required transport buffer will be
 * allocated on the stack.
 *
 * The generated function is defined as ``अटल पूर्णांक name(काष्ठा ssam_device
 * *sdev)``, वापसing the status of the request, which is zero on success and
 * negative on failure. The ``sdev`` parameter specअगरies both the target
 * device of the request and by association the controller via which the
 * request is sent.
 *
 * Refer to ssam_request_sync_onstack() क्रम more details on the behavior of
 * the generated function.
 */
#घोषणा SSAM_DEFINE_SYNC_REQUEST_CL_N(name, spec...)			\
	SSAM_DEFINE_SYNC_REQUEST_MD_N(__raw_##name, spec)		\
	अटल पूर्णांक name(काष्ठा ssam_device *sdev)			\
	अणु								\
		वापस __raw_##name(sdev->ctrl, sdev->uid.target,	\
				    sdev->uid.instance);		\
	पूर्ण

/**
 * SSAM_DEFINE_SYNC_REQUEST_CL_W() - Define synchronous client-device SAM
 * request function with argument.
 * @name:  Name of the generated function.
 * @atype: Type of the request's argument.
 * @spec:  Specअगरication (&काष्ठा ssam_request_spec_md) defining the request.
 *
 * Defines a function executing the synchronous SAM request specअगरied by
 * @spec, with the request taking an argument of type @atype and having no
 * वापस value. Device specअगरying parameters are not hard-coded, but instead
 * are provided via the client device, specअगरically its UID, supplied when
 * calling this function. The generated function takes care of setting up the
 * request काष्ठा, buffer allocation, as well as execution of the request
 * itself, वापसing once the request has been fully completed. The required
 * transport buffer will be allocated on the stack.
 *
 * The generated function is defined as ``अटल पूर्णांक name(काष्ठा ssam_device
 * *sdev, स्थिर atype *arg)``, वापसing the status of the request, which is
 * zero on success and negative on failure. The ``sdev`` parameter specअगरies
 * both the target device of the request and by association the controller via
 * which the request is sent. The request's argument is specअगरied via the
 * ``arg`` poपूर्णांकer.
 *
 * Refer to ssam_request_sync_onstack() क्रम more details on the behavior of
 * the generated function.
 */
#घोषणा SSAM_DEFINE_SYNC_REQUEST_CL_W(name, atype, spec...)		\
	SSAM_DEFINE_SYNC_REQUEST_MD_W(__raw_##name, atype, spec)	\
	अटल पूर्णांक name(काष्ठा ssam_device *sdev, स्थिर atype *arg)	\
	अणु								\
		वापस __raw_##name(sdev->ctrl, sdev->uid.target,	\
				    sdev->uid.instance, arg);		\
	पूर्ण

/**
 * SSAM_DEFINE_SYNC_REQUEST_CL_R() - Define synchronous client-device SAM
 * request function with वापस value.
 * @name:  Name of the generated function.
 * @rtype: Type of the request's वापस value.
 * @spec:  Specअगरication (&काष्ठा ssam_request_spec_md) defining the request.
 *
 * Defines a function executing the synchronous SAM request specअगरied by
 * @spec, with the request taking no argument but having a वापस value of
 * type @rtype. Device specअगरying parameters are not hard-coded, but instead
 * are provided via the client device, specअगरically its UID, supplied when
 * calling this function. The generated function takes care of setting up the
 * request काष्ठा, buffer allocation, as well as execution of the request
 * itself, वापसing once the request has been fully completed. The required
 * transport buffer will be allocated on the stack.
 *
 * The generated function is defined as ``अटल पूर्णांक name(काष्ठा ssam_device
 * *sdev, rtype *ret)``, वापसing the status of the request, which is zero on
 * success and negative on failure. The ``sdev`` parameter specअगरies both the
 * target device of the request and by association the controller via which
 * the request is sent. The request's वापस value is written to the memory
 * poपूर्णांकed to by the ``ret`` parameter.
 *
 * Refer to ssam_request_sync_onstack() क्रम more details on the behavior of
 * the generated function.
 */
#घोषणा SSAM_DEFINE_SYNC_REQUEST_CL_R(name, rtype, spec...)		\
	SSAM_DEFINE_SYNC_REQUEST_MD_R(__raw_##name, rtype, spec)	\
	अटल पूर्णांक name(काष्ठा ssam_device *sdev, rtype *ret)		\
	अणु								\
		वापस __raw_##name(sdev->ctrl, sdev->uid.target,	\
				    sdev->uid.instance, ret);		\
	पूर्ण

#पूर्ण_अगर /* _LINUX_SURFACE_AGGREGATOR_DEVICE_H */
