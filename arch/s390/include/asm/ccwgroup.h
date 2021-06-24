<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित S390_CCWGROUP_H
#घोषणा S390_CCWGROUP_H

काष्ठा ccw_device;
काष्ठा ccw_driver;

/**
 * काष्ठा ccwgroup_device - ccw group device
 * @state: online/offline state
 * @count: number of attached slave devices
 * @dev: embedded device काष्ठाure
 * @cdev: variable number of slave devices, allocated as needed
 * @ungroup_work: work to be करोne when a ccwgroup notअगरier has action
 *	type %BUS_NOTIFY_UNBIND_DRIVER
 */
काष्ठा ccwgroup_device अणु
	क्रमागत अणु
		CCWGROUP_OFFLINE,
		CCWGROUP_ONLINE,
	पूर्ण state;
/* निजी: */
	atomic_t onoff;
	काष्ठा mutex reg_mutex;
/* खुला: */
	अचिन्हित पूर्णांक count;
	काष्ठा device	dev;
	काष्ठा work_काष्ठा ungroup_work;
	काष्ठा ccw_device *cdev[0];
पूर्ण;

/**
 * काष्ठा ccwgroup_driver - driver क्रम ccw group devices
 * @setup: function called during device creation to setup the device
 * @हटाओ: function called on हटाओ
 * @set_online: function called when device is set online
 * @set_offline: function called when device is set offline
 * @shutकरोwn: function called when device is shut करोwn
 * @driver: embedded driver काष्ठाure
 * @ccw_driver: supported ccw_driver (optional)
 */
काष्ठा ccwgroup_driver अणु
	पूर्णांक (*setup) (काष्ठा ccwgroup_device *);
	व्योम (*हटाओ) (काष्ठा ccwgroup_device *);
	पूर्णांक (*set_online) (काष्ठा ccwgroup_device *);
	पूर्णांक (*set_offline) (काष्ठा ccwgroup_device *);
	व्योम (*shutकरोwn)(काष्ठा ccwgroup_device *);

	काष्ठा device_driver driver;
	काष्ठा ccw_driver *ccw_driver;
पूर्ण;

बाह्य पूर्णांक  ccwgroup_driver_रेजिस्टर   (काष्ठा ccwgroup_driver *cdriver);
बाह्य व्योम ccwgroup_driver_unरेजिस्टर (काष्ठा ccwgroup_driver *cdriver);
पूर्णांक ccwgroup_create_dev(काष्ठा device *root, काष्ठा ccwgroup_driver *gdrv,
			पूर्णांक num_devices, स्थिर अक्षर *buf);
काष्ठा ccwgroup_device *get_ccwgroupdev_by_busid(काष्ठा ccwgroup_driver *gdrv,
						 अक्षर *bus_id);

बाह्य पूर्णांक ccwgroup_set_online(काष्ठा ccwgroup_device *gdev);
बाह्य पूर्णांक ccwgroup_set_offline(काष्ठा ccwgroup_device *gdev);

बाह्य पूर्णांक ccwgroup_probe_ccwdev(काष्ठा ccw_device *cdev);
बाह्य व्योम ccwgroup_हटाओ_ccwdev(काष्ठा ccw_device *cdev);

#घोषणा to_ccwgroupdev(x) container_of((x), काष्ठा ccwgroup_device, dev)
#घोषणा to_ccwgroupdrv(x) container_of((x), काष्ठा ccwgroup_driver, driver)

#अगर IS_ENABLED(CONFIG_CCWGROUP)
bool dev_is_ccwgroup(काष्ठा device *dev);
#अन्यथा /* CONFIG_CCWGROUP */
अटल अंतरभूत bool dev_is_ccwgroup(काष्ठा device *dev)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_CCWGROUP */

#पूर्ण_अगर
