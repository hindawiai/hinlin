<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_EXTCON_INTERNAL_H__
#घोषणा __LINUX_EXTCON_INTERNAL_H__

#समावेश <linux/extcon-provider.h>

/**
 * काष्ठा extcon_dev - An extcon device represents one बाह्यal connector.
 * @name:		The name of this extcon device. Parent device name is
 *			used अगर शून्य.
 * @supported_cable:	Array of supported cable names ending with EXTCON_NONE.
 *			If supported_cable is शून्य, cable name related APIs
 *			are disabled.
 * @mutually_exclusive:	Array of mutually exclusive set of cables that cannot
 *			be attached simultaneously. The array should be
 *			ending with शून्य or be शून्य (no mutually exclusive
 *			cables). For example, अगर it is अणु 0x7, 0x30, 0पूर्ण, then,
 *			अणु0, 1पूर्ण, अणु0, 1, 2पूर्ण, अणु0, 2पूर्ण, अणु1, 2पूर्ण, or अणु4, 5पूर्ण cannot
 *			be attached simulataneously. अणु0x7, 0पूर्ण is equivalent to
 *			अणु0x3, 0x6, 0x5, 0पूर्ण. If it is अणु0xFFFFFFFF, 0पूर्ण, there
 *			can be no simultaneous connections.
 * @dev:		Device of this extcon.
 * @state:		Attach/detach state of this extcon. Do not provide at
 *			रेजिस्टर-समय.
 * @nh_all:		Notअगरier क्रम the state change events क्रम all supported
 *			बाह्यal connectors from this extcon.
 * @nh:			Notअगरier क्रम the state change events from this extcon
 * @entry:		To support list of extcon devices so that users can
 *			search क्रम extcon devices based on the extcon name.
 * @lock:
 * @max_supported:	Internal value to store the number of cables.
 * @extcon_dev_type:	Device_type काष्ठा to provide attribute_groups
 *			customized क्रम each extcon device.
 * @cables:		Sysfs subdirectories. Each represents one cable.
 *
 * In most हालs, users only need to provide "User initializing data" of
 * this काष्ठा when रेजिस्टरing an extcon. In some exceptional हालs,
 * optional callbacks may be needed. However, the values in "internal data"
 * are overwritten by रेजिस्टर function.
 */
काष्ठा extcon_dev अणु
	/* Optional user initializing data */
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक *supported_cable;
	स्थिर u32 *mutually_exclusive;

	/* Internal data. Please करो not set. */
	काष्ठा device dev;
	काष्ठा raw_notअगरier_head nh_all;
	काष्ठा raw_notअगरier_head *nh;
	काष्ठा list_head entry;
	पूर्णांक max_supported;
	spinlock_t lock;	/* could be called by irq handler */
	u32 state;

	/* /sys/class/extcon/.../cable.n/... */
	काष्ठा device_type extcon_dev_type;
	काष्ठा extcon_cable *cables;

	/* /sys/class/extcon/.../mutually_exclusive/... */
	काष्ठा attribute_group attr_g_muex;
	काष्ठा attribute **attrs_muex;
	काष्ठा device_attribute *d_attrs_muex;
पूर्ण;

#पूर्ण_अगर /* __LINUX_EXTCON_INTERNAL_H__ */
