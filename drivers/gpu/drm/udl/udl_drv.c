<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Red Hat
 */

#समावेश <linux/module.h>

#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_gem_shmem_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "udl_drv.h"

अटल पूर्णांक udl_usb_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			   pm_message_t message)
अणु
	काष्ठा drm_device *dev = usb_get_पूर्णांकfdata(पूर्णांकerface);

	वापस drm_mode_config_helper_suspend(dev);
पूर्ण

अटल पूर्णांक udl_usb_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा drm_device *dev = usb_get_पूर्णांकfdata(पूर्णांकerface);

	वापस drm_mode_config_helper_resume(dev);
पूर्ण

/*
 * FIXME: Dma-buf sharing requires DMA support by the importing device.
 *        This function is a workaround to make USB devices work as well.
 *        See toकरो.rst क्रम how to fix the issue in the dma-buf framework.
 */
अटल काष्ठा drm_gem_object *udl_driver_gem_prime_import(काष्ठा drm_device *dev,
							  काष्ठा dma_buf *dma_buf)
अणु
	काष्ठा udl_device *udl = to_udl(dev);

	अगर (!udl->dmadev)
		वापस ERR_PTR(-ENODEV);

	वापस drm_gem_prime_import_dev(dev, dma_buf, udl->dmadev);
पूर्ण

DEFINE_DRM_GEM_FOPS(udl_driver_fops);

अटल स्थिर काष्ठा drm_driver driver = अणु
	.driver_features = DRIVER_ATOMIC | DRIVER_GEM | DRIVER_MODESET,

	/* GEM hooks */
	.fops = &udl_driver_fops,
	DRM_GEM_SHMEM_DRIVER_OPS,
	.gem_prime_import = udl_driver_gem_prime_import,

	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
	.patchlevel = DRIVER_PATCHLEVEL,
पूर्ण;

अटल काष्ठा udl_device *udl_driver_create(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा udl_device *udl;
	पूर्णांक r;

	udl = devm_drm_dev_alloc(&पूर्णांकerface->dev, &driver,
				 काष्ठा udl_device, drm);
	अगर (IS_ERR(udl))
		वापस udl;

	r = udl_init(udl);
	अगर (r)
		वापस ERR_PTR(r);

	usb_set_पूर्णांकfdata(पूर्णांकerface, udl);

	वापस udl;
पूर्ण

अटल पूर्णांक udl_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक r;
	काष्ठा udl_device *udl;

	udl = udl_driver_create(पूर्णांकerface);
	अगर (IS_ERR(udl))
		वापस PTR_ERR(udl);

	r = drm_dev_रेजिस्टर(&udl->drm, 0);
	अगर (r)
		वापस r;

	DRM_INFO("Initialized udl on minor %d\n", udl->drm.primary->index);

	drm_fbdev_generic_setup(&udl->drm, 0);

	वापस 0;
पूर्ण

अटल व्योम udl_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा drm_device *dev = usb_get_पूर्णांकfdata(पूर्णांकerface);

	drm_kms_helper_poll_fini(dev);
	udl_drop_usb(dev);
	drm_dev_unplug(dev);
पूर्ण

/*
 * There are many DisplayLink-based graphics products, all with unique PIDs.
 * So we match on DisplayLink's VID + Venकरोr-Defined Interface Class (0xff)
 * We also require a match on SubClass (0x00) and Protocol (0x00),
 * which is compatible with all known USB 2.0 era graphics chips and firmware,
 * but allows DisplayLink to increment those क्रम any future incompatible chips
 */
अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु.idVenकरोr = 0x17e9, .bInterfaceClass = 0xff,
	 .bInterfaceSubClass = 0x00,
	 .bInterfaceProtocol = 0x00,
	 .match_flags = USB_DEVICE_ID_MATCH_VENDOR |
			USB_DEVICE_ID_MATCH_INT_CLASS |
			USB_DEVICE_ID_MATCH_INT_SUBCLASS |
			USB_DEVICE_ID_MATCH_INT_PROTOCOL,पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

अटल काष्ठा usb_driver udl_driver = अणु
	.name = "udl",
	.probe = udl_usb_probe,
	.disconnect = udl_usb_disconnect,
	.suspend = udl_usb_suspend,
	.resume = udl_usb_resume,
	.id_table = id_table,
पूर्ण;
module_usb_driver(udl_driver);
MODULE_LICENSE("GPL");
