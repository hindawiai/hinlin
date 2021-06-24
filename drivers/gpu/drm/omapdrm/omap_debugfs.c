<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Rob Clark <rob.clark@linaro.org>
 */

#समावेश <linux/seq_file.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_fb_helper.h>

#समावेश "omap_drv.h"
#समावेश "omap_dmm_tiler.h"

#अगर_घोषित CONFIG_DEBUG_FS

अटल पूर्णांक gem_show(काष्ठा seq_file *m, व्योम *arg)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *) m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;

	seq_म_लिखो(m, "All Objects:\n");
	mutex_lock(&priv->list_lock);
	omap_gem_describe_objects(&priv->obj_list, m);
	mutex_unlock(&priv->list_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक mm_show(काष्ठा seq_file *m, व्योम *arg)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *) m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	drm_mm_prपूर्णांक(&dev->vma_offset_manager->vm_addr_space_mm, &p);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DRM_FBDEV_EMULATION
अटल पूर्णांक fb_show(काष्ठा seq_file *m, व्योम *arg)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *) m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_framebuffer *fb;

	seq_म_लिखो(m, "fbcon ");
	omap_framebuffer_describe(priv->fbdev->fb, m);

	mutex_lock(&dev->mode_config.fb_lock);
	list_क्रम_each_entry(fb, &dev->mode_config.fb_list, head) अणु
		अगर (fb == priv->fbdev->fb)
			जारी;

		seq_म_लिखो(m, "user ");
		omap_framebuffer_describe(fb, m);
	पूर्ण
	mutex_unlock(&dev->mode_config.fb_lock);

	वापस 0;
पूर्ण
#पूर्ण_अगर

/* list of debufs files that are applicable to all devices */
अटल काष्ठा drm_info_list omap_debugfs_list[] = अणु
	अणु"gem", gem_show, 0पूर्ण,
	अणु"mm", mm_show, 0पूर्ण,
#अगर_घोषित CONFIG_DRM_FBDEV_EMULATION
	अणु"fb", fb_show, 0पूर्ण,
#पूर्ण_अगर
पूर्ण;

/* list of debugfs files that are specअगरic to devices with dmm/tiler */
अटल काष्ठा drm_info_list omap_dmm_debugfs_list[] = अणु
	अणु"tiler_map", tiler_map_show, 0पूर्ण,
पूर्ण;

व्योम omap_debugfs_init(काष्ठा drm_minor *minor)
अणु
	drm_debugfs_create_files(omap_debugfs_list,
				 ARRAY_SIZE(omap_debugfs_list),
				 minor->debugfs_root, minor);

	अगर (dmm_is_available())
		drm_debugfs_create_files(omap_dmm_debugfs_list,
					 ARRAY_SIZE(omap_dmm_debugfs_list),
					 minor->debugfs_root, minor);
पूर्ण

#पूर्ण_अगर
