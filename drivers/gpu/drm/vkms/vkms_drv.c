<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

/**
 * DOC: vkms (Virtual Kernel Modesetting)
 *
 * VKMS is a software-only model of a KMS driver that is useful क्रम testing
 * and क्रम running X (or similar) on headless machines. VKMS aims to enable
 * a भव display with no need of a hardware display capability, releasing
 * the GPU in DRM API tests.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>

#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_gem_shmem_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "vkms_drv.h"

#घोषणा DRIVER_NAME	"vkms"
#घोषणा DRIVER_DESC	"Virtual Kernel Mode Setting"
#घोषणा DRIVER_DATE	"20180514"
#घोषणा DRIVER_MAJOR	1
#घोषणा DRIVER_MINOR	0

अटल काष्ठा vkms_config *शेष_config;

अटल bool enable_cursor = true;
module_param_named(enable_cursor, enable_cursor, bool, 0444);
MODULE_PARM_DESC(enable_cursor, "Enable/Disable cursor support");

अटल bool enable_ग_लिखोback = true;
module_param_named(enable_ग_लिखोback, enable_ग_लिखोback, bool, 0444);
MODULE_PARM_DESC(enable_ग_लिखोback, "Enable/Disable writeback connector support");

DEFINE_DRM_GEM_FOPS(vkms_driver_fops);

अटल व्योम vkms_release(काष्ठा drm_device *dev)
अणु
	काष्ठा vkms_device *vkms = container_of(dev, काष्ठा vkms_device, drm);

	destroy_workqueue(vkms->output.composer_workq);
पूर्ण

अटल व्योम vkms_atomic_commit_tail(काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_device *dev = old_state->dev;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state;
	पूर्णांक i;

	drm_atomic_helper_commit_modeset_disables(dev, old_state);

	drm_atomic_helper_commit_planes(dev, old_state, 0);

	drm_atomic_helper_commit_modeset_enables(dev, old_state);

	drm_atomic_helper_fake_vblank(old_state);

	drm_atomic_helper_commit_hw_करोne(old_state);

	drm_atomic_helper_रुको_क्रम_flip_करोne(dev, old_state);

	क्रम_each_old_crtc_in_state(old_state, crtc, old_crtc_state, i) अणु
		काष्ठा vkms_crtc_state *vkms_state =
			to_vkms_crtc_state(old_crtc_state);

		flush_work(&vkms_state->composer_work);
	पूर्ण

	drm_atomic_helper_cleanup_planes(dev, old_state);
पूर्ण

अटल स्थिर काष्ठा drm_driver vkms_driver = अणु
	.driver_features	= DRIVER_MODESET | DRIVER_ATOMIC | DRIVER_GEM,
	.release		= vkms_release,
	.fops			= &vkms_driver_fops,
	DRM_GEM_SHMEM_DRIVER_OPS,

	.name			= DRIVER_NAME,
	.desc			= DRIVER_DESC,
	.date			= DRIVER_DATE,
	.major			= DRIVER_MAJOR,
	.minor			= DRIVER_MINOR,
पूर्ण;

अटल स्थिर काष्ठा drm_mode_config_funcs vkms_mode_funcs = अणु
	.fb_create = drm_gem_fb_create,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल स्थिर काष्ठा drm_mode_config_helper_funcs vkms_mode_config_helpers = अणु
	.atomic_commit_tail = vkms_atomic_commit_tail,
पूर्ण;

अटल पूर्णांक vkms_modeset_init(काष्ठा vkms_device *vkmsdev)
अणु
	काष्ठा drm_device *dev = &vkmsdev->drm;

	drm_mode_config_init(dev);
	dev->mode_config.funcs = &vkms_mode_funcs;
	dev->mode_config.min_width = XRES_MIN;
	dev->mode_config.min_height = YRES_MIN;
	dev->mode_config.max_width = XRES_MAX;
	dev->mode_config.max_height = YRES_MAX;
	dev->mode_config.cursor_width = 512;
	dev->mode_config.cursor_height = 512;
	/* FIXME: There's a confusion between bpp and depth between this and
	 * fbdev helpers. We have to go with 0, meaning "pick the default",
	 * which ix XRGB8888 in all हालs. */
	dev->mode_config.preferred_depth = 0;
	dev->mode_config.helper_निजी = &vkms_mode_config_helpers;

	वापस vkms_output_init(vkmsdev, 0);
पूर्ण

अटल पूर्णांक vkms_create(काष्ठा vkms_config *config)
अणु
	पूर्णांक ret;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा vkms_device *vkms_device;

	pdev = platक्रमm_device_रेजिस्टर_simple(DRIVER_NAME, -1, शून्य, 0);
	अगर (IS_ERR(pdev))
		वापस PTR_ERR(pdev);

	अगर (!devres_खोलो_group(&pdev->dev, शून्य, GFP_KERNEL)) अणु
		ret = -ENOMEM;
		जाओ out_unरेजिस्टर;
	पूर्ण

	vkms_device = devm_drm_dev_alloc(&pdev->dev, &vkms_driver,
					 काष्ठा vkms_device, drm);
	अगर (IS_ERR(vkms_device)) अणु
		ret = PTR_ERR(vkms_device);
		जाओ out_devres;
	पूर्ण
	vkms_device->platक्रमm = pdev;
	vkms_device->config = config;
	config->dev = vkms_device;

	ret = dma_coerce_mask_and_coherent(vkms_device->drm.dev,
					   DMA_BIT_MASK(64));

	अगर (ret) अणु
		DRM_ERROR("Could not initialize DMA support\n");
		जाओ out_devres;
	पूर्ण

	vkms_device->drm.irq_enabled = true;

	ret = drm_vblank_init(&vkms_device->drm, 1);
	अगर (ret) अणु
		DRM_ERROR("Failed to vblank\n");
		जाओ out_devres;
	पूर्ण

	ret = vkms_modeset_init(vkms_device);
	अगर (ret)
		जाओ out_devres;

	ret = drm_dev_रेजिस्टर(&vkms_device->drm, 0);
	अगर (ret)
		जाओ out_devres;

	drm_fbdev_generic_setup(&vkms_device->drm, 0);

	वापस 0;

out_devres:
	devres_release_group(&pdev->dev, शून्य);
out_unरेजिस्टर:
	platक्रमm_device_unरेजिस्टर(pdev);
	वापस ret;
पूर्ण

अटल पूर्णांक __init vkms_init(व्योम)
अणु
	काष्ठा vkms_config *config;

	config = kदो_स्मृति(माप(*config), GFP_KERNEL);
	अगर (!config)
		वापस -ENOMEM;

	शेष_config = config;

	config->cursor = enable_cursor;
	config->ग_लिखोback = enable_ग_लिखोback;

	वापस vkms_create(config);
पूर्ण

अटल व्योम vkms_destroy(काष्ठा vkms_config *config)
अणु
	काष्ठा platक्रमm_device *pdev;

	अगर (!config->dev) अणु
		DRM_INFO("vkms_device is NULL.\n");
		वापस;
	पूर्ण

	pdev = config->dev->platक्रमm;

	drm_dev_unरेजिस्टर(&config->dev->drm);
	drm_atomic_helper_shutकरोwn(&config->dev->drm);
	devres_release_group(&pdev->dev, शून्य);
	platक्रमm_device_unरेजिस्टर(pdev);

	config->dev = शून्य;
पूर्ण

अटल व्योम __निकास vkms_निकास(व्योम)
अणु
	अगर (शेष_config->dev)
		vkms_destroy(शेष_config);

	kमुक्त(शेष_config);
पूर्ण

module_init(vkms_init);
module_निकास(vkms_निकास);

MODULE_AUTHOR("Haneen Mohammed <hamohammed.sa@gmail.com>");
MODULE_AUTHOR("Rodrigo Siqueira <rodrigosiqueiramelo@gmail.com>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
