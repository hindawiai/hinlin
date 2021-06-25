<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Released under the GPLv2 only.
 */

#समावेश <linux/pm.h>
#समावेश <linux/acpi.h>

काष्ठा usb_hub_descriptor;
काष्ठा usb_dev_state;

/* Functions local to drivers/usb/core/ */

बाह्य पूर्णांक usb_create_sysfs_dev_files(काष्ठा usb_device *dev);
बाह्य व्योम usb_हटाओ_sysfs_dev_files(काष्ठा usb_device *dev);
बाह्य व्योम usb_create_sysfs_पूर्णांकf_files(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
बाह्य व्योम usb_हटाओ_sysfs_पूर्णांकf_files(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
बाह्य पूर्णांक usb_create_ep_devs(काष्ठा device *parent,
				काष्ठा usb_host_endpoपूर्णांक *endpoपूर्णांक,
				काष्ठा usb_device *udev);
बाह्य व्योम usb_हटाओ_ep_devs(काष्ठा usb_host_endpoपूर्णांक *endpoपूर्णांक);

बाह्य व्योम usb_enable_endpoपूर्णांक(काष्ठा usb_device *dev,
		काष्ठा usb_host_endpoपूर्णांक *ep, bool reset_toggle);
बाह्य व्योम usb_enable_पूर्णांकerface(काष्ठा usb_device *dev,
		काष्ठा usb_पूर्णांकerface *पूर्णांकf, bool reset_toggles);
बाह्य व्योम usb_disable_endpoपूर्णांक(काष्ठा usb_device *dev, अचिन्हित पूर्णांक epaddr,
		bool reset_hardware);
बाह्य व्योम usb_disable_पूर्णांकerface(काष्ठा usb_device *dev,
		काष्ठा usb_पूर्णांकerface *पूर्णांकf, bool reset_hardware);
बाह्य व्योम usb_release_पूर्णांकerface_cache(काष्ठा kref *ref);
बाह्य व्योम usb_disable_device(काष्ठा usb_device *dev, पूर्णांक skip_ep0);
बाह्य पूर्णांक usb_deauthorize_device(काष्ठा usb_device *);
बाह्य पूर्णांक usb_authorize_device(काष्ठा usb_device *);
बाह्य व्योम usb_deauthorize_पूर्णांकerface(काष्ठा usb_पूर्णांकerface *);
बाह्य व्योम usb_authorize_पूर्णांकerface(काष्ठा usb_पूर्णांकerface *);
बाह्य व्योम usb_detect_quirks(काष्ठा usb_device *udev);
बाह्य व्योम usb_detect_पूर्णांकerface_quirks(काष्ठा usb_device *udev);
बाह्य व्योम usb_release_quirk_list(व्योम);
बाह्य bool usb_endpoपूर्णांक_is_ignored(काष्ठा usb_device *udev,
		काष्ठा usb_host_पूर्णांकerface *पूर्णांकf,
		काष्ठा usb_endpoपूर्णांक_descriptor *epd);
बाह्य पूर्णांक usb_हटाओ_device(काष्ठा usb_device *udev);

बाह्य पूर्णांक usb_get_device_descriptor(काष्ठा usb_device *dev,
		अचिन्हित पूर्णांक size);
बाह्य पूर्णांक usb_set_isoch_delay(काष्ठा usb_device *dev);
बाह्य पूर्णांक usb_get_bos_descriptor(काष्ठा usb_device *dev);
बाह्य व्योम usb_release_bos_descriptor(काष्ठा usb_device *dev);
बाह्य अक्षर *usb_cache_string(काष्ठा usb_device *udev, पूर्णांक index);
बाह्य पूर्णांक usb_set_configuration(काष्ठा usb_device *dev, पूर्णांक configuration);
बाह्य पूर्णांक usb_choose_configuration(काष्ठा usb_device *udev);
बाह्य पूर्णांक usb_generic_driver_probe(काष्ठा usb_device *udev);
बाह्य व्योम usb_generic_driver_disconnect(काष्ठा usb_device *udev);
बाह्य पूर्णांक usb_generic_driver_suspend(काष्ठा usb_device *udev,
		pm_message_t msg);
बाह्य पूर्णांक usb_generic_driver_resume(काष्ठा usb_device *udev,
		pm_message_t msg);

अटल अंतरभूत अचिन्हित usb_get_max_घातer(काष्ठा usb_device *udev,
		काष्ठा usb_host_config *c)
अणु
	/* SuperSpeed घातer is in 8 mA units; others are in 2 mA units */
	अचिन्हित mul = (udev->speed >= USB_SPEED_SUPER ? 8 : 2);

	वापस c->desc.bMaxPower * mul;
पूर्ण

बाह्य व्योम usb_kick_hub_wq(काष्ठा usb_device *dev);
बाह्य पूर्णांक usb_match_one_id_पूर्णांकf(काष्ठा usb_device *dev,
				 काष्ठा usb_host_पूर्णांकerface *पूर्णांकf,
				 स्थिर काष्ठा usb_device_id *id);
बाह्य पूर्णांक usb_match_device(काष्ठा usb_device *dev,
			    स्थिर काष्ठा usb_device_id *id);
बाह्य स्थिर काष्ठा usb_device_id *usb_device_match_id(काष्ठा usb_device *udev,
				स्थिर काष्ठा usb_device_id *id);
बाह्य bool usb_driver_applicable(काष्ठा usb_device *udev,
				  काष्ठा usb_device_driver *udrv);
बाह्य व्योम usb_क्रमced_unbind_पूर्णांकf(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
बाह्य व्योम usb_unbind_and_rebind_marked_पूर्णांकerfaces(काष्ठा usb_device *udev);

बाह्य व्योम usb_hub_release_all_ports(काष्ठा usb_device *hdev,
		काष्ठा usb_dev_state *owner);
बाह्य bool usb_device_is_owned(काष्ठा usb_device *udev);

बाह्य पूर्णांक  usb_hub_init(व्योम);
बाह्य व्योम usb_hub_cleanup(व्योम);
बाह्य पूर्णांक usb_major_init(व्योम);
बाह्य व्योम usb_major_cleanup(व्योम);
बाह्य पूर्णांक usb_device_supports_lpm(काष्ठा usb_device *udev);
बाह्य पूर्णांक usb_port_disable(काष्ठा usb_device *udev);

#अगर_घोषित	CONFIG_PM

बाह्य पूर्णांक usb_suspend(काष्ठा device *dev, pm_message_t msg);
बाह्य पूर्णांक usb_resume(काष्ठा device *dev, pm_message_t msg);
बाह्य पूर्णांक usb_resume_complete(काष्ठा device *dev);

बाह्य पूर्णांक usb_port_suspend(काष्ठा usb_device *dev, pm_message_t msg);
बाह्य पूर्णांक usb_port_resume(काष्ठा usb_device *dev, pm_message_t msg);

बाह्य व्योम usb_स्वतःsuspend_device(काष्ठा usb_device *udev);
बाह्य पूर्णांक usb_स्वतःresume_device(काष्ठा usb_device *udev);
बाह्य पूर्णांक usb_remote_wakeup(काष्ठा usb_device *dev);
बाह्य पूर्णांक usb_runसमय_suspend(काष्ठा device *dev);
बाह्य पूर्णांक usb_runसमय_resume(काष्ठा device *dev);
बाह्य पूर्णांक usb_runसमय_idle(काष्ठा device *dev);
बाह्य पूर्णांक usb_enable_usb2_hardware_lpm(काष्ठा usb_device *udev);
बाह्य पूर्णांक usb_disable_usb2_hardware_lpm(काष्ठा usb_device *udev);

बाह्य व्योम usbfs_notअगरy_suspend(काष्ठा usb_device *udev);
बाह्य व्योम usbfs_notअगरy_resume(काष्ठा usb_device *udev);

#अन्यथा

अटल अंतरभूत पूर्णांक usb_port_suspend(काष्ठा usb_device *udev, pm_message_t msg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक usb_port_resume(काष्ठा usb_device *udev, pm_message_t msg)
अणु
	वापस 0;
पूर्ण

#घोषणा usb_स्वतःsuspend_device(udev)		करो अणुपूर्ण जबतक (0)
अटल अंतरभूत पूर्णांक usb_स्वतःresume_device(काष्ठा usb_device *udev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक usb_enable_usb2_hardware_lpm(काष्ठा usb_device *udev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक usb_disable_usb2_hardware_lpm(काष्ठा usb_device *udev)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

बाह्य काष्ठा bus_type usb_bus_type;
बाह्य काष्ठा mutex usb_port_peer_mutex;
बाह्य काष्ठा device_type usb_device_type;
बाह्य काष्ठा device_type usb_अगर_device_type;
बाह्य काष्ठा device_type usb_ep_device_type;
बाह्य काष्ठा device_type usb_port_device_type;
बाह्य काष्ठा usb_device_driver usb_generic_driver;

अटल अंतरभूत पूर्णांक is_usb_device(स्थिर काष्ठा device *dev)
अणु
	वापस dev->type == &usb_device_type;
पूर्ण

अटल अंतरभूत पूर्णांक is_usb_पूर्णांकerface(स्थिर काष्ठा device *dev)
अणु
	वापस dev->type == &usb_अगर_device_type;
पूर्ण

अटल अंतरभूत पूर्णांक is_usb_endpoपूर्णांक(स्थिर काष्ठा device *dev)
अणु
	वापस dev->type == &usb_ep_device_type;
पूर्ण

अटल अंतरभूत पूर्णांक is_usb_port(स्थिर काष्ठा device *dev)
अणु
	वापस dev->type == &usb_port_device_type;
पूर्ण

अटल अंतरभूत पूर्णांक is_root_hub(काष्ठा usb_device *udev)
अणु
	वापस (udev->parent == शून्य);
पूर्ण

/* Do the same क्रम device drivers and पूर्णांकerface drivers. */

अटल अंतरभूत पूर्णांक is_usb_device_driver(काष्ठा device_driver *drv)
अणु
	वापस container_of(drv, काष्ठा usbdrv_wrap, driver)->
			क्रम_devices;
पूर्ण

/* क्रम labeling diagnostics */
बाह्य स्थिर अक्षर *usbcore_name;

/* sysfs stuff */
बाह्य स्थिर काष्ठा attribute_group *usb_device_groups[];
बाह्य स्थिर काष्ठा attribute_group *usb_पूर्णांकerface_groups[];

/* usbfs stuff */
बाह्य काष्ठा usb_driver usbfs_driver;
बाह्य स्थिर काष्ठा file_operations usbfs_devices_fops;
बाह्य स्थिर काष्ठा file_operations usbdev_file_operations;

बाह्य पूर्णांक usb_devio_init(व्योम);
बाह्य व्योम usb_devio_cleanup(व्योम);

/*
 * Firmware specअगरic cookie identअगरying a port's location. '0' == no location
 * data available
 */
प्रकार u32 usb_port_location_t;

/* पूर्णांकernal notअगरy stuff */
बाह्य व्योम usb_notअगरy_add_device(काष्ठा usb_device *udev);
बाह्य व्योम usb_notअगरy_हटाओ_device(काष्ठा usb_device *udev);
बाह्य व्योम usb_notअगरy_add_bus(काष्ठा usb_bus *ubus);
बाह्य व्योम usb_notअगरy_हटाओ_bus(काष्ठा usb_bus *ubus);
बाह्य व्योम usb_hub_adjust_deviceremovable(काष्ठा usb_device *hdev,
		काष्ठा usb_hub_descriptor *desc);

#अगर_घोषित CONFIG_ACPI
बाह्य पूर्णांक usb_acpi_रेजिस्टर(व्योम);
बाह्य व्योम usb_acpi_unरेजिस्टर(व्योम);
बाह्य acpi_handle usb_get_hub_port_acpi_handle(काष्ठा usb_device *hdev,
	पूर्णांक port1);
#अन्यथा
अटल अंतरभूत पूर्णांक usb_acpi_रेजिस्टर(व्योम) अणु वापस 0; पूर्ण;
अटल अंतरभूत व्योम usb_acpi_unरेजिस्टर(व्योम) अणु पूर्ण;
#पूर्ण_अगर
