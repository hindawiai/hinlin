<शैली गुरु>
/*
 * dvbdev.h
 *
 * Copyright (C) 2000 Ralph Metzler & Marcus Metzler
 *                    क्रम convergence पूर्णांकegrated media GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Lesser Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */

#अगर_अघोषित _DVBDEV_H_
#घोषणा _DVBDEV_H_

#समावेश <linux/types.h>
#समावेश <linux/poll.h>
#समावेश <linux/fs.h>
#समावेश <linux/list.h>
#समावेश <media/media-device.h>

#घोषणा DVB_MAJOR 212

#अगर defined(CONFIG_DVB_MAX_ADAPTERS) && CONFIG_DVB_MAX_ADAPTERS > 0
  #घोषणा DVB_MAX_ADAPTERS CONFIG_DVB_MAX_ADAPTERS
#अन्यथा
  #घोषणा DVB_MAX_ADAPTERS 16
#पूर्ण_अगर

#घोषणा DVB_UNSET (-1)

/* List of DVB device types */

/**
 * क्रमागत dvb_device_type - type of the Digital TV device
 *
 * @DVB_DEVICE_SEC:		Digital TV standalone Common Interface (CI)
 * @DVB_DEVICE_FRONTEND:	Digital TV frontend.
 * @DVB_DEVICE_DEMUX:		Digital TV demux.
 * @DVB_DEVICE_DVR:		Digital TV digital video record (DVR).
 * @DVB_DEVICE_CA:		Digital TV Conditional Access (CA).
 * @DVB_DEVICE_NET:		Digital TV network.
 *
 * @DVB_DEVICE_VIDEO:		Digital TV video decoder.
 *				Deprecated. Used only on av7110-av.
 * @DVB_DEVICE_AUDIO:		Digital TV audio decoder.
 *				Deprecated. Used only on av7110-av.
 * @DVB_DEVICE_OSD:		Digital TV On Screen Display (OSD).
 *				Deprecated. Used only on av7110.
 */
क्रमागत dvb_device_type अणु
	DVB_DEVICE_SEC,
	DVB_DEVICE_FRONTEND,
	DVB_DEVICE_DEMUX,
	DVB_DEVICE_DVR,
	DVB_DEVICE_CA,
	DVB_DEVICE_NET,

	DVB_DEVICE_VIDEO,
	DVB_DEVICE_AUDIO,
	DVB_DEVICE_OSD,
पूर्ण;

#घोषणा DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr) \
	अटल लघु adapter_nr[] = \
		अणु[0 ... (DVB_MAX_ADAPTERS - 1)] = DVB_UNSET पूर्ण; \
	module_param_array(adapter_nr, लघु, शून्य, 0444); \
	MODULE_PARM_DESC(adapter_nr, "DVB adapter numbers")

काष्ठा dvb_frontend;

/**
 * काष्ठा dvb_adapter - represents a Digital TV adapter using Linux DVB API
 *
 * @num:		Number of the adapter
 * @list_head:		List with the DVB adapters
 * @device_list:	List with the DVB devices
 * @name:		Name of the adapter
 * @proposed_mac:	proposed MAC address क्रम the adapter
 * @priv:		निजी data
 * @device:		poपूर्णांकer to काष्ठा device
 * @module:		poपूर्णांकer to काष्ठा module
 * @mfe_shared:		indicates mutually exclusive frontends.
 *			Use of this flag is currently deprecated.
 * @mfe_dvbdev:		Frontend device in use, in the हाल of MFE
 * @mfe_lock:		Lock to prevent using the other frontends when MFE is
 *			used.
 * @mdev_lock:          Protect access to the mdev poपूर्णांकer.
 * @mdev:		poपूर्णांकer to काष्ठा media_device, used when the media
 *			controller is used.
 * @conn:		RF connector. Used only अगर the device has no separate
 *			tuner.
 * @conn_pads:		poपूर्णांकer to काष्ठा media_pad associated with @conn;
 */
काष्ठा dvb_adapter अणु
	पूर्णांक num;
	काष्ठा list_head list_head;
	काष्ठा list_head device_list;
	स्थिर अक्षर *name;
	u8 proposed_mac [6];
	व्योम* priv;

	काष्ठा device *device;

	काष्ठा module *module;

	पूर्णांक mfe_shared;			/* indicates mutually exclusive frontends */
	काष्ठा dvb_device *mfe_dvbdev;	/* frontend device in use */
	काष्ठा mutex mfe_lock;		/* access lock क्रम thपढ़ो creation */

#अगर defined(CONFIG_MEDIA_CONTROLLER_DVB)
	काष्ठा mutex mdev_lock;
	काष्ठा media_device *mdev;
	काष्ठा media_entity *conn;
	काष्ठा media_pad *conn_pads;
#पूर्ण_अगर
पूर्ण;

/**
 * काष्ठा dvb_device - represents a DVB device node
 *
 * @list_head:	List head with all DVB devices
 * @fops:	poपूर्णांकer to काष्ठा file_operations
 * @adapter:	poपूर्णांकer to the adapter that holds this device node
 * @type:	type of the device, as defined by &क्रमागत dvb_device_type.
 * @minor:	devnode minor number. Major number is always DVB_MAJOR.
 * @id:		device ID number, inside the adapter
 * @पढ़ोers:	Initialized by the caller. Each call to खोलो() in Read Only mode
 *		decreases this counter by one.
 * @ग_लिखोrs:	Initialized by the caller. Each call to खोलो() in Read/Write
 *		mode decreases this counter by one.
 * @users:	Initialized by the caller. Each call to खोलो() in any mode
 *		decreases this counter by one.
 * @रुको_queue:	रुको queue, used to रुको क्रम certain events inside one of
 *		the DVB API callers
 * @kernel_ioctl: callback function used to handle ioctl calls from userspace.
 * @name:	Name to be used क्रम the device at the Media Controller
 * @entity:	poपूर्णांकer to काष्ठा media_entity associated with the device node
 * @pads:	poपूर्णांकer to काष्ठा media_pad associated with @entity;
 * @priv:	निजी data
 * @पूर्णांकf_devnode: Poपूर्णांकer to media_पूर्णांकf_devnode. Used by the dvbdev core to
 *		store the MC device node पूर्णांकerface
 * @tsout_num_entities: Number of Transport Stream output entities
 * @tsout_entity: array with MC entities associated to each TS output node
 * @tsout_pads: array with the source pads क्रम each @tsout_entity
 *
 * This काष्ठाure is used by the DVB core (frontend, CA, net, demux) in
 * order to create the device nodes. Usually, driver should not initialize
 * this काष्ठा diretly.
 */
काष्ठा dvb_device अणु
	काष्ठा list_head list_head;
	स्थिर काष्ठा file_operations *fops;
	काष्ठा dvb_adapter *adapter;
	क्रमागत dvb_device_type type;
	पूर्णांक minor;
	u32 id;

	/* in theory, 'users' can vanish now,
	   but I करोn't want to change too much now... */
	पूर्णांक पढ़ोers;
	पूर्णांक ग_लिखोrs;
	पूर्णांक users;

	रुको_queue_head_t	  रुको_queue;
	/* करोn't really need those !? -- FIXME: use video_usercopy  */
	पूर्णांक (*kernel_ioctl)(काष्ठा file *file, अचिन्हित पूर्णांक cmd, व्योम *arg);

	/* Needed क्रम media controller रेजिस्टर/unरेजिस्टर */
#अगर defined(CONFIG_MEDIA_CONTROLLER_DVB)
	स्थिर अक्षर *name;

	/* Allocated and filled inside dvbdev.c */
	काष्ठा media_पूर्णांकf_devnode *पूर्णांकf_devnode;

	अचिन्हित tsout_num_entities;
	काष्ठा media_entity *entity, *tsout_entity;
	काष्ठा media_pad *pads, *tsout_pads;
#पूर्ण_अगर

	व्योम *priv;
पूर्ण;

/**
 * dvb_रेजिस्टर_adapter - Registers a new DVB adapter
 *
 * @adap:	poपूर्णांकer to काष्ठा dvb_adapter
 * @name:	Adapter's name
 * @module:	initialized with THIS_MODULE at the caller
 * @device:	poपूर्णांकer to काष्ठा device that corresponds to the device driver
 * @adapter_nums: Array with a list of the numbers क्रम @dvb_रेजिस्टर_adapter;
 *		to select among them. Typically, initialized with:
 *		DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nums)
 */
पूर्णांक dvb_रेजिस्टर_adapter(काष्ठा dvb_adapter *adap, स्थिर अक्षर *name,
			 काष्ठा module *module, काष्ठा device *device,
			 लघु *adapter_nums);

/**
 * dvb_unरेजिस्टर_adapter - Unरेजिस्टरs a DVB adapter
 *
 * @adap:	poपूर्णांकer to काष्ठा dvb_adapter
 */
पूर्णांक dvb_unरेजिस्टर_adapter(काष्ठा dvb_adapter *adap);

/**
 * dvb_रेजिस्टर_device - Registers a new DVB device
 *
 * @adap:	poपूर्णांकer to काष्ठा dvb_adapter
 * @pdvbdev:	poपूर्णांकer to the place where the new काष्ठा dvb_device will be
 *		stored
 * @ढाँचा:	Template used to create &pdvbdev;
 * @priv:	निजी data
 * @type:	type of the device, as defined by &क्रमागत dvb_device_type.
 * @demux_sink_pads: Number of demux outमाला_दो, to be used to create the TS
 *		outमाला_दो via the Media Controller.
 */
पूर्णांक dvb_रेजिस्टर_device(काष्ठा dvb_adapter *adap,
			काष्ठा dvb_device **pdvbdev,
			स्थिर काष्ठा dvb_device *ढाँचा,
			व्योम *priv,
			क्रमागत dvb_device_type type,
			पूर्णांक demux_sink_pads);

/**
 * dvb_हटाओ_device - Remove a रेजिस्टरed DVB device
 *
 * This करोes not मुक्त memory.  To करो that, call dvb_मुक्त_device().
 *
 * @dvbdev:	poपूर्णांकer to काष्ठा dvb_device
 */
व्योम dvb_हटाओ_device(काष्ठा dvb_device *dvbdev);

/**
 * dvb_मुक्त_device - Free memory occupied by a DVB device.
 *
 * Call dvb_unरेजिस्टर_device() beक्रमe calling this function.
 *
 * @dvbdev:	poपूर्णांकer to काष्ठा dvb_device
 */
व्योम dvb_मुक्त_device(काष्ठा dvb_device *dvbdev);

/**
 * dvb_unरेजिस्टर_device - Unरेजिस्टरs a DVB device
 *
 * This is a combination of dvb_हटाओ_device() and dvb_मुक्त_device().
 * Using this function is usually a mistake, and is often an indicator
 * क्रम a use-after-मुक्त bug (when a userspace process keeps a file
 * handle to a detached device).
 *
 * @dvbdev:	poपूर्णांकer to काष्ठा dvb_device
 */
व्योम dvb_unरेजिस्टर_device(काष्ठा dvb_device *dvbdev);

#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
/**
 * dvb_create_media_graph - Creates media graph क्रम the Digital TV part of the
 *				device.
 *
 * @adap:			poपूर्णांकer to &काष्ठा dvb_adapter
 * @create_rf_connector:	अगर true, it creates the RF connector too
 *
 * This function checks all DVB-related functions at the media controller
 * entities and creates the needed links क्रम the media graph. It is
 * capable of working with multiple tuners or multiple frontends, but it
 * won't create links अगर the device has multiple tuners and multiple frontends
 * or अगर the device has multiple muxes. In such हाल, the caller driver should
 * manually create the reमुख्यing links.
 */
__must_check पूर्णांक dvb_create_media_graph(काष्ठा dvb_adapter *adap,
					bool create_rf_connector);

/**
 * dvb_रेजिस्टर_media_controller - रेजिस्टरs a media controller at DVB adapter
 *
 * @adap:			poपूर्णांकer to &काष्ठा dvb_adapter
 * @mdev:			poपूर्णांकer to &काष्ठा media_device
 */
अटल अंतरभूत व्योम dvb_रेजिस्टर_media_controller(काष्ठा dvb_adapter *adap,
						 काष्ठा media_device *mdev)
अणु
	adap->mdev = mdev;
पूर्ण

/**
 * dvb_get_media_controller - माला_लो the associated media controller
 *
 * @adap:			poपूर्णांकer to &काष्ठा dvb_adapter
 */
अटल अंतरभूत काष्ठा media_device *
dvb_get_media_controller(काष्ठा dvb_adapter *adap)
अणु
	वापस adap->mdev;
पूर्ण
#अन्यथा
अटल अंतरभूत
पूर्णांक dvb_create_media_graph(काष्ठा dvb_adapter *adap,
			   bool create_rf_connector)
अणु
	वापस 0;
पूर्ण;
#घोषणा dvb_रेजिस्टर_media_controller(a, b) अणुपूर्ण
#घोषणा dvb_get_media_controller(a) शून्य
#पूर्ण_अगर

/**
 * dvb_generic_खोलो - Digital TV खोलो function, used by DVB devices
 *
 * @inode: poपूर्णांकer to &काष्ठा inode.
 * @file: poपूर्णांकer to &काष्ठा file.
 *
 * Checks अगर a DVB devnode is still valid, and अगर the permissions are
 * OK and increment negative use count.
 */
पूर्णांक dvb_generic_खोलो(काष्ठा inode *inode, काष्ठा file *file);

/**
 * dvb_generic_release - Digital TV बंद function, used by DVB devices
 *
 * @inode: poपूर्णांकer to &काष्ठा inode.
 * @file: poपूर्णांकer to &काष्ठा file.
 *
 * Checks अगर a DVB devnode is still valid, and अगर the permissions are
 * OK and decrement negative use count.
 */
पूर्णांक dvb_generic_release(काष्ठा inode *inode, काष्ठा file *file);

/**
 * dvb_generic_ioctl - Digital TV बंद function, used by DVB devices
 *
 * @file: poपूर्णांकer to &काष्ठा file.
 * @cmd: Ioctl name.
 * @arg: Ioctl argument.
 *
 * Checks अगर a DVB devnode and काष्ठा dvbdev.kernel_ioctl is still valid.
 * If so, calls dvb_usercopy().
 */
दीर्घ dvb_generic_ioctl(काष्ठा file *file,
		       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

/**
 * dvb_usercopy - copies data from/to userspace memory when an ioctl is
 *      issued.
 *
 * @file: Poपूर्णांकer to काष्ठा &file.
 * @cmd: Ioctl name.
 * @arg: Ioctl argument.
 * @func: function that will actually handle the ioctl
 *
 * Ancillary function that uses ioctl direction and size to copy from
 * userspace. Then, it calls @func, and, अगर needed, data is copied back
 * to userspace.
 */
पूर्णांक dvb_usercopy(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg,
		 पूर्णांक (*func)(काष्ठा file *file, अचिन्हित पूर्णांक cmd, व्योम *arg));

#अगर IS_ENABLED(CONFIG_I2C)

काष्ठा i2c_adapter;
काष्ठा i2c_client;
/**
 * dvb_module_probe - helper routine to probe an I2C module
 *
 * @module_name:
 *	Name of the I2C module to be probed
 * @name:
 *	Optional name क्रम the I2C module. Used क्रम debug purposes.
 * 	If %शून्य, शेषs to @module_name.
 * @adap:
 *	poपूर्णांकer to &काष्ठा i2c_adapter that describes the I2C adapter where
 *	the module will be bound.
 * @addr:
 *	I2C address of the adapter, in 7-bit notation.
 * @platक्रमm_data:
 *	Platक्रमm data to be passed to the I2C module probed.
 *
 * This function binds an I2C device पूर्णांकo the DVB core. Should be used by
 * all drivers that use I2C bus to control the hardware. A module bound
 * with dvb_module_probe() should use dvb_module_release() to unbind.
 *
 * Return:
 *	On success, वापस an &काष्ठा i2c_client, poपूर्णांकing to the bound
 *	I2C device. %शून्य otherwise.
 *
 * .. note::
 *
 *    In the past, DVB modules (मुख्यly, frontends) were bound via dvb_attach()
 *    macro, with करोes an ugly hack, using I2C low level functions. Such
 *    usage is deprecated and will be हटाओd soon. Instead, use this routine.
 */
काष्ठा i2c_client *dvb_module_probe(स्थिर अक्षर *module_name,
				    स्थिर अक्षर *name,
				    काष्ठा i2c_adapter *adap,
				    अचिन्हित अक्षर addr,
				    व्योम *platक्रमm_data);

/**
 * dvb_module_release - releases an I2C device allocated with
 *	 dvb_module_probe().
 *
 * @client: poपूर्णांकer to &काष्ठा i2c_client with the I2C client to be released.
 *	    can be %शून्य.
 *
 * This function should be used to मुक्त all resources reserved by
 * dvb_module_probe() and unbinding the I2C hardware.
 */
व्योम dvb_module_release(काष्ठा i2c_client *client);

#पूर्ण_अगर /* CONFIG_I2C */

/* Legacy generic DVB attach function. */
#अगर_घोषित CONFIG_MEDIA_ATTACH

/**
 * dvb_attach - attaches a DVB frontend पूर्णांकo the DVB core.
 *
 * @FUNCTION:	function on a frontend module to be called.
 * @ARGS:	@FUNCTION arguments.
 *
 * This ancillary function loads a frontend module in runसमय and runs
 * the @FUNCTION function there, with @ARGS.
 * As it increments symbol usage cont, at unरेजिस्टर, dvb_detach()
 * should be called.
 *
 * .. note::
 *
 *    In the past, DVB modules (मुख्यly, frontends) were bound via dvb_attach()
 *    macro, with करोes an ugly hack, using I2C low level functions. Such
 *    usage is deprecated and will be हटाओd soon. Instead, you should use
 *    dvb_module_probe().
 */
#घोषणा dvb_attach(FUNCTION, ARGS...) (अणु \
	व्योम *__r = शून्य; \
	typeof(&FUNCTION) __a = symbol_request(FUNCTION); \
	अगर (__a) अणु \
		__r = (व्योम *) __a(ARGS); \
		अगर (__r == शून्य) \
			symbol_put(FUNCTION); \
	पूर्ण अन्यथा अणु \
		prपूर्णांकk(KERN_ERR "DVB: Unable to find symbol "#FUNCTION"()\n"); \
	पूर्ण \
	__r; \
पूर्ण)

/**
 * dvb_detach - detaches a DVB frontend loaded via dvb_attach()
 *
 * @FUNC:	attach function
 *
 * Decrements usage count क्रम a function previously called via dvb_attach().
 */

#घोषणा dvb_detach(FUNC)	symbol_put_addr(FUNC)

#अन्यथा
#घोषणा dvb_attach(FUNCTION, ARGS...) (अणु \
	FUNCTION(ARGS); \
पूर्ण)

#घोषणा dvb_detach(FUNC)	अणुपूर्ण

#पूर्ण_अगर	/* CONFIG_MEDIA_ATTACH */

#पूर्ण_अगर /* #अगर_अघोषित _DVBDEV_H_ */
