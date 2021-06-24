<शैली गुरु>
/*
 * Copyright (C) 2015 Red Hat, Inc.
 * All Rights Reserved.
 *
 * Authors:
 *    Dave Airlie <airlied@redhat.com>
 *    Gerd Hoffmann <kraxel@redhat.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/module.h>
#समावेश <linux/console.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>

#समावेश "virtgpu_drv.h"

अटल स्थिर काष्ठा drm_driver driver;

अटल पूर्णांक virtio_gpu_modeset = -1;

MODULE_PARM_DESC(modeset, "Disable/Enable modesetting");
module_param_named(modeset, virtio_gpu_modeset, पूर्णांक, 0400);

अटल पूर्णांक virtio_gpu_pci_quirk(काष्ठा drm_device *dev, काष्ठा virtio_device *vdev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(vdev->dev.parent);
	स्थिर अक्षर *pname = dev_name(&pdev->dev);
	bool vga = (pdev->class >> 8) == PCI_CLASS_DISPLAY_VGA;
	अक्षर unique[20];

	DRM_INFO("pci: %s detected at %s\n",
		 vga ? "virtio-vga" : "virtio-gpu-pci",
		 pname);
	अगर (vga)
		drm_fb_helper_हटाओ_conflicting_pci_framebuffers(pdev,
								  "virtiodrmfb");

	/*
	 * Normally the drm_dev_set_unique() call is करोne by core DRM.
	 * The following comment covers, why virtio cannot rely on it.
	 *
	 * Unlike the other भव GPU drivers, virtio असलtracts the
	 * underlying bus type by using काष्ठा virtio_device.
	 *
	 * Hence the dev_is_pci() check, used in core DRM, will fail
	 * and the unique वापसed will be the virtio_device "virtio0",
	 * जबतक a "pci:..." one is required.
	 *
	 * A few other ideas were considered:
	 * - Extend the dev_is_pci() check [in drm_set_busid] to
	 *   consider virtio.
	 *   Seems like a bigger hack than what we have alपढ़ोy.
	 *
	 * - Poपूर्णांक drm_device::dev to the parent of the virtio_device
	 *   Semantic changes:
	 *   * Using the wrong device क्रम i2c, framebuffer_alloc and
	 *     prime import.
	 *   Visual changes:
	 *   * Helpers such as DRM_DEV_ERROR, dev_info, drm_prपूर्णांकer,
	 *     will prपूर्णांक the wrong inक्रमmation.
	 *
	 * We could address the latter issues, by पूर्णांकroducing
	 * drm_device::bus_dev, ... which would be used solely क्रम this.
	 *
	 * So क्रम the moment keep things as-is, with a bulky comment
	 * क्रम the next person who feels like removing this
	 * drm_dev_set_unique() quirk.
	 */
	snम_लिखो(unique, माप(unique), "pci:%s", pname);
	वापस drm_dev_set_unique(dev, unique);
पूर्ण

अटल पूर्णांक virtio_gpu_probe(काष्ठा virtio_device *vdev)
अणु
	काष्ठा drm_device *dev;
	पूर्णांक ret;

	अगर (vgacon_text_क्रमce() && virtio_gpu_modeset == -1)
		वापस -EINVAL;

	अगर (virtio_gpu_modeset == 0)
		वापस -EINVAL;

	dev = drm_dev_alloc(&driver, &vdev->dev);
	अगर (IS_ERR(dev))
		वापस PTR_ERR(dev);
	vdev->priv = dev;

	अगर (!म_भेद(vdev->dev.parent->bus->name, "pci")) अणु
		ret = virtio_gpu_pci_quirk(dev, vdev);
		अगर (ret)
			जाओ err_मुक्त;
	पूर्ण

	ret = virtio_gpu_init(dev);
	अगर (ret)
		जाओ err_मुक्त;

	ret = drm_dev_रेजिस्टर(dev, 0);
	अगर (ret)
		जाओ err_मुक्त;

	drm_fbdev_generic_setup(vdev->priv, 32);
	वापस 0;

err_मुक्त:
	drm_dev_put(dev);
	वापस ret;
पूर्ण

अटल व्योम virtio_gpu_हटाओ(काष्ठा virtio_device *vdev)
अणु
	काष्ठा drm_device *dev = vdev->priv;

	drm_dev_unplug(dev);
	drm_atomic_helper_shutकरोwn(dev);
	virtio_gpu_deinit(dev);
	drm_dev_put(dev);
पूर्ण

अटल व्योम virtio_gpu_config_changed(काष्ठा virtio_device *vdev)
अणु
	काष्ठा drm_device *dev = vdev->priv;
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;

	schedule_work(&vgdev->config_changed_work);
पूर्ण

अटल काष्ठा virtio_device_id id_table[] = अणु
	अणु VIRTIO_ID_GPU, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक features[] = अणु
#अगर_घोषित __LITTLE_ENDIAN
	/*
	 * Gallium command stream send by virgl is native endian.
	 * Because of that we only support little endian guests on
	 * little endian hosts.
	 */
	VIRTIO_GPU_F_VIRGL,
#पूर्ण_अगर
	VIRTIO_GPU_F_EDID,
	VIRTIO_GPU_F_RESOURCE_UUID,
	VIRTIO_GPU_F_RESOURCE_BLOB,
पूर्ण;
अटल काष्ठा virtio_driver virtio_gpu_driver = अणु
	.feature_table = features,
	.feature_table_size = ARRAY_SIZE(features),
	.driver.name = KBUILD_MODNAME,
	.driver.owner = THIS_MODULE,
	.id_table = id_table,
	.probe = virtio_gpu_probe,
	.हटाओ = virtio_gpu_हटाओ,
	.config_changed = virtio_gpu_config_changed
पूर्ण;

module_virtio_driver(virtio_gpu_driver);

MODULE_DEVICE_TABLE(virtio, id_table);
MODULE_DESCRIPTION("Virtio GPU driver");
MODULE_LICENSE("GPL and additional rights");
MODULE_AUTHOR("Dave Airlie <airlied@redhat.com>");
MODULE_AUTHOR("Gerd Hoffmann <kraxel@redhat.com>");
MODULE_AUTHOR("Alon Levy");

DEFINE_DRM_GEM_FOPS(virtio_gpu_driver_fops);

अटल स्थिर काष्ठा drm_driver driver = अणु
	.driver_features = DRIVER_MODESET | DRIVER_GEM | DRIVER_RENDER | DRIVER_ATOMIC,
	.खोलो = virtio_gpu_driver_खोलो,
	.postबंद = virtio_gpu_driver_postबंद,

	.dumb_create = virtio_gpu_mode_dumb_create,
	.dumb_map_offset = virtio_gpu_mode_dumb_mmap,

#अगर defined(CONFIG_DEBUG_FS)
	.debugfs_init = virtio_gpu_debugfs_init,
#पूर्ण_अगर
	.prime_handle_to_fd = drm_gem_prime_handle_to_fd,
	.prime_fd_to_handle = drm_gem_prime_fd_to_handle,
	.gem_prime_mmap = drm_gem_prime_mmap,
	.gem_prime_import = virtgpu_gem_prime_import,
	.gem_prime_import_sg_table = virtgpu_gem_prime_import_sg_table,

	.gem_create_object = virtio_gpu_create_object,
	.fops = &virtio_gpu_driver_fops,

	.ioctls = virtio_gpu_ioctls,
	.num_ioctls = DRM_VIRTIO_NUM_IOCTLS,

	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
	.patchlevel = DRIVER_PATCHLEVEL,

	.release = virtio_gpu_release,
पूर्ण;
