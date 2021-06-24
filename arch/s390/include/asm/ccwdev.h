<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright IBM Corp. 2002, 2009
 *
 * Author(s): Arnd Bergmann <arndb@de.ibm.com>
 *
 * Interface क्रम CCW device drivers
 */
#अगर_अघोषित _S390_CCWDEV_H_
#घोषणा _S390_CCWDEV_H_

#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <यंत्र/chsc.h>
#समावेश <यंत्र/fcx.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/schid.h>

/* काष्ठाs from यंत्र/cपन.स */
काष्ठा irb;
काष्ठा ccw1;
काष्ठा ccw_dev_id;

/* simplअगरied initializers क्रम काष्ठा ccw_device:
 * CCW_DEVICE and CCW_DEVICE_DEVTYPE initialize one
 * entry in your MODULE_DEVICE_TABLE and set the match_flag correctly */
#घोषणा CCW_DEVICE(cu, cum) 						\
	.cu_type=(cu), .cu_model=(cum),					\
	.match_flags=(CCW_DEVICE_ID_MATCH_CU_TYPE			\
		   | (cum ? CCW_DEVICE_ID_MATCH_CU_MODEL : 0))

#घोषणा CCW_DEVICE_DEVTYPE(cu, cum, dev, devm)				\
	.cu_type=(cu), .cu_model=(cum), .dev_type=(dev), .dev_model=(devm),\
	.match_flags=CCW_DEVICE_ID_MATCH_CU_TYPE			\
		   | ((cum) ? CCW_DEVICE_ID_MATCH_CU_MODEL : 0) 	\
		   | CCW_DEVICE_ID_MATCH_DEVICE_TYPE			\
		   | ((devm) ? CCW_DEVICE_ID_MATCH_DEVICE_MODEL : 0)

/* scan through an array of device ids and वापस the first
 * entry that matches the device.
 *
 * the array must end with an entry containing zero match_flags
 */
अटल अंतरभूत स्थिर काष्ठा ccw_device_id *
ccw_device_id_match(स्थिर काष्ठा ccw_device_id *array,
			स्थिर काष्ठा ccw_device_id *match)
अणु
	स्थिर काष्ठा ccw_device_id *id = array;

	क्रम (id = array; id->match_flags; id++) अणु
		अगर ((id->match_flags & CCW_DEVICE_ID_MATCH_CU_TYPE)
		    && (id->cu_type != match->cu_type))
			जारी;

		अगर ((id->match_flags & CCW_DEVICE_ID_MATCH_CU_MODEL)
		    && (id->cu_model != match->cu_model))
			जारी;

		अगर ((id->match_flags & CCW_DEVICE_ID_MATCH_DEVICE_TYPE)
		    && (id->dev_type != match->dev_type))
			जारी;

		अगर ((id->match_flags & CCW_DEVICE_ID_MATCH_DEVICE_MODEL)
		    && (id->dev_model != match->dev_model))
			जारी;

		वापस id;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * काष्ठा ccw_device - channel attached device
 * @ccwlock: poपूर्णांकer to device lock
 * @id: id of this device
 * @drv: ccw driver क्रम this device
 * @dev: embedded device काष्ठाure
 * @online: online status of device
 * @handler: पूर्णांकerrupt handler
 *
 * @handler is a member of the device rather than the driver since a driver
 * can have dअगरferent पूर्णांकerrupt handlers क्रम dअगरferent ccw devices
 * (multi-subchannel drivers).
 */
काष्ठा ccw_device अणु
	spinlock_t *ccwlock;
/* निजी: */
	काष्ठा ccw_device_निजी *निजी;	/* cio निजी inक्रमmation */
/* खुला: */
	काष्ठा ccw_device_id id;
	काष्ठा ccw_driver *drv;
	काष्ठा device dev;
	पूर्णांक online;
	व्योम (*handler) (काष्ठा ccw_device *, अचिन्हित दीर्घ, काष्ठा irb *);
पूर्ण;

/*
 * Possible events used by the path_event notअगरier.
 */
#घोषणा PE_NONE				0x0
#घोषणा PE_PATH_GONE			0x1 /* A path is no दीर्घer available. */
#घोषणा PE_PATH_AVAILABLE		0x2 /* A path has become available and
					       was successfully verअगरied. */
#घोषणा PE_PATHGROUP_ESTABLISHED	0x4 /* A pathgroup was reset and had
					       to be established again. */
#घोषणा PE_PATH_FCES_EVENT		0x8 /* The FCES Status of a path has
					     * changed. */

/*
 * Possible CIO actions triggered by the unit check handler.
 */
क्रमागत uc_toकरो अणु
	UC_TODO_RETRY,
	UC_TODO_RETRY_ON_NEW_PATH,
	UC_TODO_STOP
पूर्ण;

/**
 * काष्ठा ccw_driver - device driver क्रम channel attached devices
 * @ids: ids supported by this driver
 * @probe: function called on probe
 * @हटाओ: function called on हटाओ
 * @set_online: called when setting device online
 * @set_offline: called when setting device offline
 * @notअगरy: notअगरy driver of device state changes
 * @path_event: notअगरy driver of channel path events
 * @shutकरोwn: called at device shutकरोwn
 * @uc_handler: callback क्रम unit check handler
 * @driver: embedded device driver काष्ठाure
 * @पूर्णांक_class: पूर्णांकerruption class to use क्रम accounting पूर्णांकerrupts
 */
काष्ठा ccw_driver अणु
	काष्ठा ccw_device_id *ids;
	पूर्णांक (*probe) (काष्ठा ccw_device *);
	व्योम (*हटाओ) (काष्ठा ccw_device *);
	पूर्णांक (*set_online) (काष्ठा ccw_device *);
	पूर्णांक (*set_offline) (काष्ठा ccw_device *);
	पूर्णांक (*notअगरy) (काष्ठा ccw_device *, पूर्णांक);
	व्योम (*path_event) (काष्ठा ccw_device *, पूर्णांक *);
	व्योम (*shutकरोwn) (काष्ठा ccw_device *);
	क्रमागत uc_toकरो (*uc_handler) (काष्ठा ccw_device *, काष्ठा irb *);
	काष्ठा device_driver driver;
	क्रमागत पूर्णांकerruption_class पूर्णांक_class;
पूर्ण;

बाह्य काष्ठा ccw_device *get_ccwdev_by_busid(काष्ठा ccw_driver *cdrv,
					      स्थिर अक्षर *bus_id);

/* devices drivers call these during module load and unload.
 * When a driver is रेजिस्टरed, its probe method is called
 * when new devices क्रम its type pop up */
बाह्य पूर्णांक  ccw_driver_रेजिस्टर   (काष्ठा ccw_driver *driver);
बाह्य व्योम ccw_driver_unरेजिस्टर (काष्ठा ccw_driver *driver);
बाह्य पूर्णांक ccw_device_set_options_mask(काष्ठा ccw_device *, अचिन्हित दीर्घ);
बाह्य पूर्णांक ccw_device_set_options(काष्ठा ccw_device *, अचिन्हित दीर्घ);
बाह्य व्योम ccw_device_clear_options(काष्ठा ccw_device *, अचिन्हित दीर्घ);
पूर्णांक ccw_device_is_pathgroup(काष्ठा ccw_device *cdev);
पूर्णांक ccw_device_is_multipath(काष्ठा ccw_device *cdev);

/* Allow क्रम i/o completion notअगरication after primary पूर्णांकerrupt status. */
#घोषणा CCWDEV_EARLY_NOTIFICATION	0x0001
/* Report all पूर्णांकerrupt conditions. */
#घोषणा CCWDEV_REPORT_ALL	 	0x0002
/* Try to perक्रमm path grouping. */
#घोषणा CCWDEV_DO_PATHGROUP             0x0004
/* Allow क्रमced onlining of boxed devices. */
#घोषणा CCWDEV_ALLOW_FORCE              0x0008
/* Try to use multipath mode. */
#घोषणा CCWDEV_DO_MULTIPATH		0x0010

बाह्य पूर्णांक ccw_device_start(काष्ठा ccw_device *, काष्ठा ccw1 *,
			    अचिन्हित दीर्घ, __u8, अचिन्हित दीर्घ);
बाह्य पूर्णांक ccw_device_start_समयout(काष्ठा ccw_device *, काष्ठा ccw1 *,
				    अचिन्हित दीर्घ, __u8, अचिन्हित दीर्घ, पूर्णांक);
बाह्य पूर्णांक ccw_device_start_key(काष्ठा ccw_device *, काष्ठा ccw1 *,
				अचिन्हित दीर्घ, __u8, __u8, अचिन्हित दीर्घ);
बाह्य पूर्णांक ccw_device_start_समयout_key(काष्ठा ccw_device *, काष्ठा ccw1 *,
					अचिन्हित दीर्घ, __u8, __u8,
					अचिन्हित दीर्घ, पूर्णांक);


बाह्य पूर्णांक ccw_device_resume(काष्ठा ccw_device *);
बाह्य पूर्णांक ccw_device_halt(काष्ठा ccw_device *, अचिन्हित दीर्घ);
बाह्य पूर्णांक ccw_device_clear(काष्ठा ccw_device *, अचिन्हित दीर्घ);
पूर्णांक ccw_device_पंचांग_start_key(काष्ठा ccw_device *cdev, काष्ठा tcw *tcw,
			    अचिन्हित दीर्घ पूर्णांकparm, u8 lpm, u8 key);
पूर्णांक ccw_device_पंचांग_start_key(काष्ठा ccw_device *, काष्ठा tcw *,
			    अचिन्हित दीर्घ, u8, u8);
पूर्णांक ccw_device_पंचांग_start_समयout_key(काष्ठा ccw_device *, काष्ठा tcw *,
			    अचिन्हित दीर्घ, u8, u8, पूर्णांक);
पूर्णांक ccw_device_पंचांग_start(काष्ठा ccw_device *, काष्ठा tcw *,
			    अचिन्हित दीर्घ, u8);
पूर्णांक ccw_device_पंचांग_start_समयout(काष्ठा ccw_device *, काष्ठा tcw *,
			    अचिन्हित दीर्घ, u8, पूर्णांक);
पूर्णांक ccw_device_पंचांग_पूर्णांकrg(काष्ठा ccw_device *cdev);

पूर्णांक ccw_device_get_mdc(काष्ठा ccw_device *cdev, u8 mask);

बाह्य पूर्णांक ccw_device_set_online(काष्ठा ccw_device *cdev);
बाह्य पूर्णांक ccw_device_set_offline(काष्ठा ccw_device *cdev);


बाह्य काष्ठा ciw *ccw_device_get_ciw(काष्ठा ccw_device *, __u32 cmd);
बाह्य __u8 ccw_device_get_path_mask(काष्ठा ccw_device *);
बाह्य व्योम ccw_device_get_id(काष्ठा ccw_device *, काष्ठा ccw_dev_id *);

#घोषणा get_ccwdev_lock(x) (x)->ccwlock

#घोषणा to_ccwdev(n) container_of(n, काष्ठा ccw_device, dev)
#घोषणा to_ccwdrv(n) container_of(n, काष्ठा ccw_driver, driver)

बाह्य काष्ठा ccw_device *ccw_device_create_console(काष्ठा ccw_driver *);
बाह्य व्योम ccw_device_destroy_console(काष्ठा ccw_device *);
बाह्य पूर्णांक ccw_device_enable_console(काष्ठा ccw_device *);
बाह्य व्योम ccw_device_रुको_idle(काष्ठा ccw_device *);
बाह्य पूर्णांक ccw_device_क्रमce_console(काष्ठा ccw_device *);

बाह्य व्योम *ccw_device_dma_zalloc(काष्ठा ccw_device *cdev, माप_प्रकार size);
बाह्य व्योम ccw_device_dma_मुक्त(काष्ठा ccw_device *cdev,
				व्योम *cpu_addr, माप_प्रकार size);

पूर्णांक ccw_device_siosl(काष्ठा ccw_device *);

बाह्य व्योम ccw_device_get_schid(काष्ठा ccw_device *, काष्ठा subchannel_id *);

काष्ठा channel_path_desc_fmt0 *ccw_device_get_chp_desc(काष्ठा ccw_device *, पूर्णांक);
u8 *ccw_device_get_util_str(काष्ठा ccw_device *cdev, पूर्णांक chp_idx);
पूर्णांक ccw_device_pnso(काष्ठा ccw_device *cdev,
		    काष्ठा chsc_pnso_area *pnso_area, u8 oc,
		    काष्ठा chsc_pnso_resume_token resume_token, पूर्णांक cnc);
पूर्णांक ccw_device_get_cssid(काष्ठा ccw_device *cdev, u8 *cssid);
पूर्णांक ccw_device_get_iid(काष्ठा ccw_device *cdev, u8 *iid);
पूर्णांक ccw_device_get_chpid(काष्ठा ccw_device *cdev, पूर्णांक chp_idx, u8 *chpid);
पूर्णांक ccw_device_get_chid(काष्ठा ccw_device *cdev, पूर्णांक chp_idx, u16 *chid);
#पूर्ण_अगर /* _S390_CCWDEV_H_ */
