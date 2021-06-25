<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#अगर_अघोषित __LINUX_USB_ROLE_H
#घोषणा __LINUX_USB_ROLE_H

#समावेश <linux/device.h>

काष्ठा usb_role_चयन;

क्रमागत usb_role अणु
	USB_ROLE_NONE,
	USB_ROLE_HOST,
	USB_ROLE_DEVICE,
पूर्ण;

प्रकार पूर्णांक (*usb_role_चयन_set_t)(काष्ठा usb_role_चयन *sw,
				     क्रमागत usb_role role);
प्रकार क्रमागत usb_role (*usb_role_चयन_get_t)(काष्ठा usb_role_चयन *sw);

/**
 * काष्ठा usb_role_चयन_desc - USB Role Switch Descriptor
 * @fwnode: The device node to be associated with the role चयन
 * @usb2_port: Optional reference to the host controller port device (USB2)
 * @usb3_port: Optional reference to the host controller port device (USB3)
 * @udc: Optional reference to the peripheral controller device
 * @set: Callback क्रम setting the role
 * @get: Callback क्रम getting the role (optional)
 * @allow_userspace_control: If true userspace may change the role through sysfs
 * @driver_data: Private data poपूर्णांकer
 * @name: Name क्रम the चयन (optional)
 *
 * @usb2_port and @usb3_port will poपूर्णांक to the USB host port and @udc to the USB
 * device controller behind the USB connector with the role चयन. If
 * @usb2_port, @usb3_port and @udc are included in the description, the
 * reference count क्रम them should be incremented by the caller of
 * usb_role_चयन_रेजिस्टर() beक्रमe रेजिस्टरing the चयन.
 */
काष्ठा usb_role_चयन_desc अणु
	काष्ठा fwnode_handle *fwnode;
	काष्ठा device *usb2_port;
	काष्ठा device *usb3_port;
	काष्ठा device *udc;
	usb_role_चयन_set_t set;
	usb_role_चयन_get_t get;
	bool allow_userspace_control;
	व्योम *driver_data;
	स्थिर अक्षर *name;
पूर्ण;


#अगर IS_ENABLED(CONFIG_USB_ROLE_SWITCH)
पूर्णांक usb_role_चयन_set_role(काष्ठा usb_role_चयन *sw, क्रमागत usb_role role);
क्रमागत usb_role usb_role_चयन_get_role(काष्ठा usb_role_चयन *sw);
काष्ठा usb_role_चयन *usb_role_चयन_get(काष्ठा device *dev);
काष्ठा usb_role_चयन *fwnode_usb_role_चयन_get(काष्ठा fwnode_handle *node);
व्योम usb_role_चयन_put(काष्ठा usb_role_चयन *sw);

काष्ठा usb_role_चयन *
usb_role_चयन_find_by_fwnode(स्थिर काष्ठा fwnode_handle *fwnode);

काष्ठा usb_role_चयन *
usb_role_चयन_रेजिस्टर(काष्ठा device *parent,
			 स्थिर काष्ठा usb_role_चयन_desc *desc);
व्योम usb_role_चयन_unरेजिस्टर(काष्ठा usb_role_चयन *sw);

व्योम usb_role_चयन_set_drvdata(काष्ठा usb_role_चयन *sw, व्योम *data);
व्योम *usb_role_चयन_get_drvdata(काष्ठा usb_role_चयन *sw);
#अन्यथा
अटल अंतरभूत पूर्णांक usb_role_चयन_set_role(काष्ठा usb_role_चयन *sw,
		क्रमागत usb_role role)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत क्रमागत usb_role usb_role_चयन_get_role(काष्ठा usb_role_चयन *sw)
अणु
	वापस USB_ROLE_NONE;
पूर्ण

अटल अंतरभूत काष्ठा usb_role_चयन *usb_role_चयन_get(काष्ठा device *dev)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत काष्ठा usb_role_चयन *
fwnode_usb_role_चयन_get(काष्ठा fwnode_handle *node)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत व्योम usb_role_चयन_put(काष्ठा usb_role_चयन *sw) अणु पूर्ण

अटल अंतरभूत काष्ठा usb_role_चयन *
usb_role_चयन_रेजिस्टर(काष्ठा device *parent,
			 स्थिर काष्ठा usb_role_चयन_desc *desc)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत व्योम usb_role_चयन_unरेजिस्टर(काष्ठा usb_role_चयन *sw) अणु पूर्ण

अटल अंतरभूत व्योम
usb_role_चयन_set_drvdata(काष्ठा usb_role_चयन *sw, व्योम *data)
अणु
पूर्ण

अटल अंतरभूत व्योम *usb_role_चयन_get_drvdata(काष्ठा usb_role_चयन *sw)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_USB_ROLE_H */
