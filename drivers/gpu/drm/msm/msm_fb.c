<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "msm_drv.h"
#समावेश "msm_kms.h"
#समावेश "msm_gem.h"

काष्ठा msm_framebuffer अणु
	काष्ठा drm_framebuffer base;
	स्थिर काष्ठा msm_क्रमmat *क्रमmat;
पूर्ण;
#घोषणा to_msm_framebuffer(x) container_of(x, काष्ठा msm_framebuffer, base)

अटल काष्ठा drm_framebuffer *msm_framebuffer_init(काष्ठा drm_device *dev,
		स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd, काष्ठा drm_gem_object **bos);

अटल स्थिर काष्ठा drm_framebuffer_funcs msm_framebuffer_funcs = अणु
	.create_handle = drm_gem_fb_create_handle,
	.destroy = drm_gem_fb_destroy,
	.dirty = drm_atomic_helper_dirtyfb,
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
व्योम msm_framebuffer_describe(काष्ठा drm_framebuffer *fb, काष्ठा seq_file *m)
अणु
	काष्ठा msm_gem_stats stats = अणुपूर्ण;
	पूर्णांक i, n = fb->क्रमmat->num_planes;

	seq_म_लिखो(m, "fb: %dx%d@%4.4s (%2d, ID:%d)\n",
			fb->width, fb->height, (अक्षर *)&fb->क्रमmat->क्रमmat,
			drm_framebuffer_पढ़ो_refcount(fb), fb->base.id);

	क्रम (i = 0; i < n; i++) अणु
		seq_म_लिखो(m, "   %d: offset=%d pitch=%d, obj: ",
				i, fb->offsets[i], fb->pitches[i]);
		msm_gem_describe(fb->obj[i], m, &stats);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/* prepare/pin all the fb's bo's क्रम scanout.  Note that it is not valid
 * to prepare an fb more multiple dअगरferent initiator 'id's.  But that
 * should be fine, since only the scanout (mdpN) side of things needs
 * this, the gpu करोesn't care about fb's.
 */
पूर्णांक msm_framebuffer_prepare(काष्ठा drm_framebuffer *fb,
		काष्ठा msm_gem_address_space *aspace)
अणु
	पूर्णांक ret, i, n = fb->क्रमmat->num_planes;
	uपूर्णांक64_t iova;

	क्रम (i = 0; i < n; i++) अणु
		ret = msm_gem_get_and_pin_iova(fb->obj[i], aspace, &iova);
		DBG("FB[%u]: iova[%d]: %08llx (%d)", fb->base.id, i, iova, ret);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम msm_framebuffer_cleanup(काष्ठा drm_framebuffer *fb,
		काष्ठा msm_gem_address_space *aspace)
अणु
	पूर्णांक i, n = fb->क्रमmat->num_planes;

	क्रम (i = 0; i < n; i++)
		msm_gem_unpin_iova(fb->obj[i], aspace);
पूर्ण

uपूर्णांक32_t msm_framebuffer_iova(काष्ठा drm_framebuffer *fb,
		काष्ठा msm_gem_address_space *aspace, पूर्णांक plane)
अणु
	अगर (!fb->obj[plane])
		वापस 0;
	वापस msm_gem_iova(fb->obj[plane], aspace) + fb->offsets[plane];
पूर्ण

काष्ठा drm_gem_object *msm_framebuffer_bo(काष्ठा drm_framebuffer *fb, पूर्णांक plane)
अणु
	वापस drm_gem_fb_get_obj(fb, plane);
पूर्ण

स्थिर काष्ठा msm_क्रमmat *msm_framebuffer_क्रमmat(काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा msm_framebuffer *msm_fb = to_msm_framebuffer(fb);
	वापस msm_fb->क्रमmat;
पूर्ण

काष्ठा drm_framebuffer *msm_framebuffer_create(काष्ठा drm_device *dev,
		काष्ठा drm_file *file, स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_get_क्रमmat_info(dev,
								 mode_cmd);
	काष्ठा drm_gem_object *bos[4] = अणु0पूर्ण;
	काष्ठा drm_framebuffer *fb;
	पूर्णांक ret, i, n = info->num_planes;

	क्रम (i = 0; i < n; i++) अणु
		bos[i] = drm_gem_object_lookup(file, mode_cmd->handles[i]);
		अगर (!bos[i]) अणु
			ret = -ENXIO;
			जाओ out_unref;
		पूर्ण
	पूर्ण

	fb = msm_framebuffer_init(dev, mode_cmd, bos);
	अगर (IS_ERR(fb)) अणु
		ret = PTR_ERR(fb);
		जाओ out_unref;
	पूर्ण

	वापस fb;

out_unref:
	क्रम (i = 0; i < n; i++)
		drm_gem_object_put(bos[i]);
	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा drm_framebuffer *msm_framebuffer_init(काष्ठा drm_device *dev,
		स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd, काष्ठा drm_gem_object **bos)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_get_क्रमmat_info(dev,
								 mode_cmd);
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा msm_kms *kms = priv->kms;
	काष्ठा msm_framebuffer *msm_fb = शून्य;
	काष्ठा drm_framebuffer *fb;
	स्थिर काष्ठा msm_क्रमmat *क्रमmat;
	पूर्णांक ret, i, n;

	DBG("create framebuffer: dev=%p, mode_cmd=%p (%dx%d@%4.4s)",
			dev, mode_cmd, mode_cmd->width, mode_cmd->height,
			(अक्षर *)&mode_cmd->pixel_क्रमmat);

	n = info->num_planes;
	क्रमmat = kms->funcs->get_क्रमmat(kms, mode_cmd->pixel_क्रमmat,
			mode_cmd->modअगरier[0]);
	अगर (!क्रमmat) अणु
		DRM_DEV_ERROR(dev->dev, "unsupported pixel format: %4.4s\n",
				(अक्षर *)&mode_cmd->pixel_क्रमmat);
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	msm_fb = kzalloc(माप(*msm_fb), GFP_KERNEL);
	अगर (!msm_fb) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	fb = &msm_fb->base;

	msm_fb->क्रमmat = क्रमmat;

	अगर (n > ARRAY_SIZE(fb->obj)) अणु
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	क्रम (i = 0; i < n; i++) अणु
		अचिन्हित पूर्णांक width = mode_cmd->width / (i ? info->hsub : 1);
		अचिन्हित पूर्णांक height = mode_cmd->height / (i ? info->vsub : 1);
		अचिन्हित पूर्णांक min_size;

		min_size = (height - 1) * mode_cmd->pitches[i]
			 + width * info->cpp[i]
			 + mode_cmd->offsets[i];

		अगर (bos[i]->size < min_size) अणु
			ret = -EINVAL;
			जाओ fail;
		पूर्ण

		msm_fb->base.obj[i] = bos[i];
	पूर्ण

	drm_helper_mode_fill_fb_काष्ठा(dev, fb, mode_cmd);

	ret = drm_framebuffer_init(dev, fb, &msm_framebuffer_funcs);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev->dev, "framebuffer init failed: %d\n", ret);
		जाओ fail;
	पूर्ण

	DBG("create: FB ID: %d (%p)", fb->base.id, fb);

	वापस fb;

fail:
	kमुक्त(msm_fb);

	वापस ERR_PTR(ret);
पूर्ण

काष्ठा drm_framebuffer *
msm_alloc_stolen_fb(काष्ठा drm_device *dev, पूर्णांक w, पूर्णांक h, पूर्णांक p, uपूर्णांक32_t क्रमmat)
अणु
	काष्ठा drm_mode_fb_cmd2 mode_cmd = अणु
		.pixel_क्रमmat = क्रमmat,
		.width = w,
		.height = h,
		.pitches = अणु p पूर्ण,
	पूर्ण;
	काष्ठा drm_gem_object *bo;
	काष्ठा drm_framebuffer *fb;
	पूर्णांक size;

	/* allocate backing bo */
	size = mode_cmd.pitches[0] * mode_cmd.height;
	DBG("allocating %d bytes for fb %d", size, dev->primary->index);
	bo = msm_gem_new(dev, size, MSM_BO_SCANOUT | MSM_BO_WC | MSM_BO_STOLEN);
	अगर (IS_ERR(bo)) अणु
		dev_warn(dev->dev, "could not allocate stolen bo\n");
		/* try regular bo: */
		bo = msm_gem_new(dev, size, MSM_BO_SCANOUT | MSM_BO_WC);
	पूर्ण
	अगर (IS_ERR(bo)) अणु
		DRM_DEV_ERROR(dev->dev, "failed to allocate buffer object\n");
		वापस ERR_CAST(bo);
	पूर्ण

	msm_gem_object_set_name(bo, "stolenfb");

	fb = msm_framebuffer_init(dev, &mode_cmd, &bo);
	अगर (IS_ERR(fb)) अणु
		DRM_DEV_ERROR(dev->dev, "failed to allocate fb\n");
		/* note: अगर fb creation failed, we can't rely on fb destroy
		 * to unref the bo:
		 */
		drm_gem_object_put(bo);
		वापस ERR_CAST(fb);
	पूर्ण

	वापस fb;
पूर्ण
