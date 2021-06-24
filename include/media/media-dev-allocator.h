<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * media-dev-allocator.h - Media Controller Device Allocator API
 *
 * Copyright (c) 2019 Shuah Khan <shuah@kernel.org>
 *
 * Credits: Suggested by Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

/*
 * This file adds a global ref-counted Media Controller Device Instance API.
 * A प्रणाली wide global media device list is managed and each media device
 * includes a kref count. The last put on the media device releases the media
 * device instance.
 */

#अगर_अघोषित _MEDIA_DEV_ALLOCATOR_H
#घोषणा _MEDIA_DEV_ALLOCATOR_H

काष्ठा usb_device;

#अगर defined(CONFIG_MEDIA_CONTROLLER) && defined(CONFIG_USB)
/**
 * media_device_usb_allocate() - Allocate and वापस काष्ठा &media device
 *
 * @udev:		काष्ठा &usb_device poपूर्णांकer
 * @module_name:	should be filled with %KBUILD_MODNAME
 * @owner:		काष्ठा module poपूर्णांकer %THIS_MODULE क्रम the driver.
 *			%THIS_MODULE is null क्रम a built-in driver.
 *			It is safe even when %THIS_MODULE is null.
 *
 * This पूर्णांकerface should be called to allocate a Media Device when multiple
 * drivers share usb_device and the media device. This पूर्णांकerface allocates
 * &media_device काष्ठाure and calls media_device_usb_init() to initialize
 * it.
 *
 */
काष्ठा media_device *media_device_usb_allocate(काष्ठा usb_device *udev,
					       स्थिर अक्षर *module_name,
					       काष्ठा module *owner);
/**
 * media_device_delete() - Release media device. Calls kref_put().
 *
 * @mdev:		काष्ठा &media_device poपूर्णांकer
 * @module_name:	should be filled with %KBUILD_MODNAME
 * @owner:		काष्ठा module poपूर्णांकer %THIS_MODULE क्रम the driver.
 *			%THIS_MODULE is null क्रम a built-in driver.
 *			It is safe even when %THIS_MODULE is null.
 *
 * This पूर्णांकerface should be called to put Media Device Instance kref.
 */
व्योम media_device_delete(काष्ठा media_device *mdev, स्थिर अक्षर *module_name,
			 काष्ठा module *owner);
#अन्यथा
अटल अंतरभूत काष्ठा media_device *media_device_usb_allocate(
			काष्ठा usb_device *udev, स्थिर अक्षर *module_name,
			काष्ठा module *owner)
			अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम media_device_delete(
			काष्ठा media_device *mdev, स्थिर अक्षर *module_name,
			काष्ठा module *owner) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_MEDIA_CONTROLLER && CONFIG_USB */
#पूर्ण_अगर /* _MEDIA_DEV_ALLOCATOR_H */
