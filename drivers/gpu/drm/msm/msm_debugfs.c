<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013-2016 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#अगर_घोषित CONFIG_DEBUG_FS

#समावेश <linux/debugfs.h>

#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_file.h>

#समावेश "msm_drv.h"
#समावेश "msm_gpu.h"
#समावेश "msm_kms.h"
#समावेश "msm_debugfs.h"

काष्ठा msm_gpu_show_priv अणु
	काष्ठा msm_gpu_state *state;
	काष्ठा drm_device *dev;
पूर्ण;

अटल पूर्णांक msm_gpu_show(काष्ठा seq_file *m, व्योम *arg)
अणु
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);
	काष्ठा msm_gpu_show_priv *show_priv = m->निजी;
	काष्ठा msm_drm_निजी *priv = show_priv->dev->dev_निजी;
	काष्ठा msm_gpu *gpu = priv->gpu;
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&show_priv->dev->काष्ठा_mutex);
	अगर (ret)
		वापस ret;

	drm_म_लिखो(&p, "%s Status:\n", gpu->name);
	gpu->funcs->show(gpu, show_priv->state, &p);

	mutex_unlock(&show_priv->dev->काष्ठा_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक msm_gpu_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा msm_gpu_show_priv *show_priv = m->निजी;
	काष्ठा msm_drm_निजी *priv = show_priv->dev->dev_निजी;
	काष्ठा msm_gpu *gpu = priv->gpu;

	mutex_lock(&show_priv->dev->काष्ठा_mutex);
	gpu->funcs->gpu_state_put(show_priv->state);
	mutex_unlock(&show_priv->dev->काष्ठा_mutex);

	kमुक्त(show_priv);

	वापस single_release(inode, file);
पूर्ण

अटल पूर्णांक msm_gpu_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा drm_device *dev = inode->i_निजी;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा msm_gpu *gpu = priv->gpu;
	काष्ठा msm_gpu_show_priv *show_priv;
	पूर्णांक ret;

	अगर (!gpu || !gpu->funcs->gpu_state_get)
		वापस -ENODEV;

	show_priv = kदो_स्मृति(माप(*show_priv), GFP_KERNEL);
	अगर (!show_priv)
		वापस -ENOMEM;

	ret = mutex_lock_पूर्णांकerruptible(&dev->काष्ठा_mutex);
	अगर (ret)
		जाओ मुक्त_priv;

	pm_runसमय_get_sync(&gpu->pdev->dev);
	show_priv->state = gpu->funcs->gpu_state_get(gpu);
	pm_runसमय_put_sync(&gpu->pdev->dev);

	mutex_unlock(&dev->काष्ठा_mutex);

	अगर (IS_ERR(show_priv->state)) अणु
		ret = PTR_ERR(show_priv->state);
		जाओ मुक्त_priv;
	पूर्ण

	show_priv->dev = dev;

	ret = single_खोलो(file, msm_gpu_show, show_priv);
	अगर (ret)
		जाओ मुक्त_priv;

	वापस 0;

मुक्त_priv:
	kमुक्त(show_priv);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations msm_gpu_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = msm_gpu_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = msm_gpu_release,
पूर्ण;

अटल पूर्णांक msm_gem_show(काष्ठा drm_device *dev, काष्ठा seq_file *m)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&priv->obj_lock);
	अगर (ret)
		वापस ret;

	msm_gem_describe_objects(&priv->objects, m);

	mutex_unlock(&priv->obj_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक msm_mm_show(काष्ठा drm_device *dev, काष्ठा seq_file *m)
अणु
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	drm_mm_prपूर्णांक(&dev->vma_offset_manager->vm_addr_space_mm, &p);

	वापस 0;
पूर्ण

अटल पूर्णांक msm_fb_show(काष्ठा drm_device *dev, काष्ठा seq_file *m)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_framebuffer *fb, *fbdev_fb = शून्य;

	अगर (priv->fbdev) अणु
		seq_म_लिखो(m, "fbcon ");
		fbdev_fb = priv->fbdev->fb;
		msm_framebuffer_describe(fbdev_fb, m);
	पूर्ण

	mutex_lock(&dev->mode_config.fb_lock);
	list_क्रम_each_entry(fb, &dev->mode_config.fb_list, head) अणु
		अगर (fb == fbdev_fb)
			जारी;

		seq_म_लिखो(m, "user ");
		msm_framebuffer_describe(fb, m);
	पूर्ण
	mutex_unlock(&dev->mode_config.fb_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक show_locked(काष्ठा seq_file *m, व्योम *arg)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *) m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	पूर्णांक (*show)(काष्ठा drm_device *dev, काष्ठा seq_file *m) =
			node->info_ent->data;
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&dev->काष्ठा_mutex);
	अगर (ret)
		वापस ret;

	ret = show(dev, m);

	mutex_unlock(&dev->काष्ठा_mutex);

	वापस ret;
पूर्ण

अटल काष्ठा drm_info_list msm_debugfs_list[] = अणु
		अणु"gem", show_locked, 0, msm_gem_showपूर्ण,
		अणु "mm", show_locked, 0, msm_mm_show पूर्ण,
		अणु "fb", show_locked, 0, msm_fb_show पूर्ण,
पूर्ण;

अटल पूर्णांक late_init_minor(काष्ठा drm_minor *minor)
अणु
	पूर्णांक ret;

	अगर (!minor)
		वापस 0;

	ret = msm_rd_debugfs_init(minor);
	अगर (ret) अणु
		DRM_DEV_ERROR(minor->dev->dev, "could not install rd debugfs\n");
		वापस ret;
	पूर्ण

	ret = msm_perf_debugfs_init(minor);
	अगर (ret) अणु
		DRM_DEV_ERROR(minor->dev->dev, "could not install perf debugfs\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक msm_debugfs_late_init(काष्ठा drm_device *dev)
अणु
	पूर्णांक ret;
	ret = late_init_minor(dev->primary);
	अगर (ret)
		वापस ret;
	ret = late_init_minor(dev->render);
	वापस ret;
पूर्ण

व्योम msm_debugfs_init(काष्ठा drm_minor *minor)
अणु
	काष्ठा drm_device *dev = minor->dev;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;

	drm_debugfs_create_files(msm_debugfs_list,
				 ARRAY_SIZE(msm_debugfs_list),
				 minor->debugfs_root, minor);

	debugfs_create_file("gpu", S_IRUSR, minor->debugfs_root,
		dev, &msm_gpu_fops);

	अगर (priv->kms && priv->kms->funcs->debugfs_init)
		priv->kms->funcs->debugfs_init(priv->kms, minor);
पूर्ण
#पूर्ण_अगर

