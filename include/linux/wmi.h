<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * wmi.h - ACPI WMI पूर्णांकerface
 *
 * Copyright (c) 2015 Andrew Lutomirski
 */

#अगर_अघोषित _LINUX_WMI_H
#घोषणा _LINUX_WMI_H

#समावेश <linux/device.h>
#समावेश <linux/acpi.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <uapi/linux/wmi.h>

काष्ठा wmi_device अणु
	काष्ठा device dev;

	 /* True क्रम data blocks implementing the Set Control Method */
	bool setable;
पूर्ण;

/* evaluate the ACPI method associated with this device */
बाह्य acpi_status wmidev_evaluate_method(काष्ठा wmi_device *wdev,
					  u8 instance, u32 method_id,
					  स्थिर काष्ठा acpi_buffer *in,
					  काष्ठा acpi_buffer *out);

/* Caller must kमुक्त the result. */
बाह्य जोड़ acpi_object *wmidev_block_query(काष्ठा wmi_device *wdev,
					     u8 instance);

बाह्य पूर्णांक set_required_buffer_size(काष्ठा wmi_device *wdev, u64 length);

काष्ठा wmi_driver अणु
	काष्ठा device_driver driver;
	स्थिर काष्ठा wmi_device_id *id_table;

	पूर्णांक (*probe)(काष्ठा wmi_device *wdev, स्थिर व्योम *context);
	व्योम (*हटाओ)(काष्ठा wmi_device *wdev);
	व्योम (*notअगरy)(काष्ठा wmi_device *device, जोड़ acpi_object *data);
	दीर्घ (*filter_callback)(काष्ठा wmi_device *wdev, अचिन्हित पूर्णांक cmd,
				काष्ठा wmi_ioctl_buffer *arg);
पूर्ण;

बाह्य पूर्णांक __must_check __wmi_driver_रेजिस्टर(काष्ठा wmi_driver *driver,
					      काष्ठा module *owner);
बाह्य व्योम wmi_driver_unरेजिस्टर(काष्ठा wmi_driver *driver);
#घोषणा wmi_driver_रेजिस्टर(driver) __wmi_driver_रेजिस्टर((driver), THIS_MODULE)

#घोषणा module_wmi_driver(__wmi_driver) \
	module_driver(__wmi_driver, wmi_driver_रेजिस्टर, \
		      wmi_driver_unरेजिस्टर)

#पूर्ण_अगर
