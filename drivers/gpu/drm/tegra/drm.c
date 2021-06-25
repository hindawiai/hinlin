<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Avionic Design GmbH
 * Copyright (C) 2012-2016 NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/host1x.h>
#समावेश <linux/idr.h>
#समावेश <linux/iommu.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_prime.h>
#समावेश <drm/drm_vblank.h>

#समावेश "drm.h"
#समावेश "gem.h"

#घोषणा DRIVER_NAME "tegra"
#घोषणा DRIVER_DESC "NVIDIA Tegra graphics"
#घोषणा DRIVER_DATE "20120330"
#घोषणा DRIVER_MAJOR 0
#घोषणा DRIVER_MINOR 0
#घोषणा DRIVER_PATCHLEVEL 0

#घोषणा CARVEOUT_SZ SZ_64M
#घोषणा CDMA_GATHER_FETCHES_MAX_NB 16383

काष्ठा tegra_drm_file अणु
	काष्ठा idr contexts;
	काष्ठा mutex lock;
पूर्ण;

अटल पूर्णांक tegra_atomic_check(काष्ठा drm_device *drm,
			      काष्ठा drm_atomic_state *state)
अणु
	पूर्णांक err;

	err = drm_atomic_helper_check(drm, state);
	अगर (err < 0)
		वापस err;

	वापस tegra_display_hub_atomic_check(drm, state);
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs tegra_drm_mode_config_funcs = अणु
	.fb_create = tegra_fb_create,
#अगर_घोषित CONFIG_DRM_FBDEV_EMULATION
	.output_poll_changed = drm_fb_helper_output_poll_changed,
#पूर्ण_अगर
	.atomic_check = tegra_atomic_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल व्योम tegra_atomic_commit_tail(काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_device *drm = old_state->dev;
	काष्ठा tegra_drm *tegra = drm->dev_निजी;

	अगर (tegra->hub) अणु
		bool fence_cookie = dma_fence_begin_संकेतling();

		drm_atomic_helper_commit_modeset_disables(drm, old_state);
		tegra_display_hub_atomic_commit(drm, old_state);
		drm_atomic_helper_commit_planes(drm, old_state, 0);
		drm_atomic_helper_commit_modeset_enables(drm, old_state);
		drm_atomic_helper_commit_hw_करोne(old_state);
		dma_fence_end_संकेतling(fence_cookie);
		drm_atomic_helper_रुको_क्रम_vblanks(drm, old_state);
		drm_atomic_helper_cleanup_planes(drm, old_state);
	पूर्ण अन्यथा अणु
		drm_atomic_helper_commit_tail_rpm(old_state);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_helper_funcs
tegra_drm_mode_config_helpers = अणु
	.atomic_commit_tail = tegra_atomic_commit_tail,
पूर्ण;

अटल पूर्णांक tegra_drm_खोलो(काष्ठा drm_device *drm, काष्ठा drm_file *filp)
अणु
	काष्ठा tegra_drm_file *fpriv;

	fpriv = kzalloc(माप(*fpriv), GFP_KERNEL);
	अगर (!fpriv)
		वापस -ENOMEM;

	idr_init_base(&fpriv->contexts, 1);
	mutex_init(&fpriv->lock);
	filp->driver_priv = fpriv;

	वापस 0;
पूर्ण

अटल व्योम tegra_drm_context_मुक्त(काष्ठा tegra_drm_context *context)
अणु
	context->client->ops->बंद_channel(context);
	kमुक्त(context);
पूर्ण

अटल काष्ठा host1x_bo *
host1x_bo_lookup(काष्ठा drm_file *file, u32 handle)
अणु
	काष्ठा drm_gem_object *gem;
	काष्ठा tegra_bo *bo;

	gem = drm_gem_object_lookup(file, handle);
	अगर (!gem)
		वापस शून्य;

	bo = to_tegra_bo(gem);
	वापस &bo->base;
पूर्ण

अटल पूर्णांक host1x_reloc_copy_from_user(काष्ठा host1x_reloc *dest,
				       काष्ठा drm_tegra_reloc __user *src,
				       काष्ठा drm_device *drm,
				       काष्ठा drm_file *file)
अणु
	u32 cmdbuf, target;
	पूर्णांक err;

	err = get_user(cmdbuf, &src->cmdbuf.handle);
	अगर (err < 0)
		वापस err;

	err = get_user(dest->cmdbuf.offset, &src->cmdbuf.offset);
	अगर (err < 0)
		वापस err;

	err = get_user(target, &src->target.handle);
	अगर (err < 0)
		वापस err;

	err = get_user(dest->target.offset, &src->target.offset);
	अगर (err < 0)
		वापस err;

	err = get_user(dest->shअगरt, &src->shअगरt);
	अगर (err < 0)
		वापस err;

	dest->flags = HOST1X_RELOC_READ | HOST1X_RELOC_WRITE;

	dest->cmdbuf.bo = host1x_bo_lookup(file, cmdbuf);
	अगर (!dest->cmdbuf.bo)
		वापस -ENOENT;

	dest->target.bo = host1x_bo_lookup(file, target);
	अगर (!dest->target.bo)
		वापस -ENOENT;

	वापस 0;
पूर्ण

पूर्णांक tegra_drm_submit(काष्ठा tegra_drm_context *context,
		     काष्ठा drm_tegra_submit *args, काष्ठा drm_device *drm,
		     काष्ठा drm_file *file)
अणु
	काष्ठा host1x_client *client = &context->client->base;
	अचिन्हित पूर्णांक num_cmdbufs = args->num_cmdbufs;
	अचिन्हित पूर्णांक num_relocs = args->num_relocs;
	काष्ठा drm_tegra_cmdbuf __user *user_cmdbufs;
	काष्ठा drm_tegra_reloc __user *user_relocs;
	काष्ठा drm_tegra_syncpt __user *user_syncpt;
	काष्ठा drm_tegra_syncpt syncpt;
	काष्ठा host1x *host1x = dev_get_drvdata(drm->dev->parent);
	काष्ठा drm_gem_object **refs;
	काष्ठा host1x_syncpt *sp = शून्य;
	काष्ठा host1x_job *job;
	अचिन्हित पूर्णांक num_refs;
	पूर्णांक err;

	user_cmdbufs = u64_to_user_ptr(args->cmdbufs);
	user_relocs = u64_to_user_ptr(args->relocs);
	user_syncpt = u64_to_user_ptr(args->syncpts);

	/* We करोn't yet support other than one syncpt_incr काष्ठा per submit */
	अगर (args->num_syncpts != 1)
		वापस -EINVAL;

	/* We करोn't yet support रुकोchks */
	अगर (args->num_रुकोchks != 0)
		वापस -EINVAL;

	job = host1x_job_alloc(context->channel, args->num_cmdbufs,
			       args->num_relocs);
	अगर (!job)
		वापस -ENOMEM;

	job->num_relocs = args->num_relocs;
	job->client = client;
	job->class = client->class;
	job->serialize = true;

	/*
	 * Track referenced BOs so that they can be unreferenced after the
	 * submission is complete.
	 */
	num_refs = num_cmdbufs + num_relocs * 2;

	refs = kदो_स्मृति_array(num_refs, माप(*refs), GFP_KERNEL);
	अगर (!refs) अणु
		err = -ENOMEM;
		जाओ put;
	पूर्ण

	/* reuse as an iterator later */
	num_refs = 0;

	जबतक (num_cmdbufs) अणु
		काष्ठा drm_tegra_cmdbuf cmdbuf;
		काष्ठा host1x_bo *bo;
		काष्ठा tegra_bo *obj;
		u64 offset;

		अगर (copy_from_user(&cmdbuf, user_cmdbufs, माप(cmdbuf))) अणु
			err = -EFAULT;
			जाओ fail;
		पूर्ण

		/*
		 * The maximum number of CDMA gather fetches is 16383, a higher
		 * value means the words count is malक्रमmed.
		 */
		अगर (cmdbuf.words > CDMA_GATHER_FETCHES_MAX_NB) अणु
			err = -EINVAL;
			जाओ fail;
		पूर्ण

		bo = host1x_bo_lookup(file, cmdbuf.handle);
		अगर (!bo) अणु
			err = -ENOENT;
			जाओ fail;
		पूर्ण

		offset = (u64)cmdbuf.offset + (u64)cmdbuf.words * माप(u32);
		obj = host1x_to_tegra_bo(bo);
		refs[num_refs++] = &obj->gem;

		/*
		 * Gather buffer base address must be 4-bytes aligned,
		 * unaligned offset is malक्रमmed and cause commands stream
		 * corruption on the buffer address relocation.
		 */
		अगर (offset & 3 || offset > obj->gem.size) अणु
			err = -EINVAL;
			जाओ fail;
		पूर्ण

		host1x_job_add_gather(job, bo, cmdbuf.words, cmdbuf.offset);
		num_cmdbufs--;
		user_cmdbufs++;
	पूर्ण

	/* copy and resolve relocations from submit */
	जबतक (num_relocs--) अणु
		काष्ठा host1x_reloc *reloc;
		काष्ठा tegra_bo *obj;

		err = host1x_reloc_copy_from_user(&job->relocs[num_relocs],
						  &user_relocs[num_relocs], drm,
						  file);
		अगर (err < 0)
			जाओ fail;

		reloc = &job->relocs[num_relocs];
		obj = host1x_to_tegra_bo(reloc->cmdbuf.bo);
		refs[num_refs++] = &obj->gem;

		/*
		 * The unaligned cmdbuf offset will cause an unaligned ग_लिखो
		 * during of the relocations patching, corrupting the commands
		 * stream.
		 */
		अगर (reloc->cmdbuf.offset & 3 ||
		    reloc->cmdbuf.offset >= obj->gem.size) अणु
			err = -EINVAL;
			जाओ fail;
		पूर्ण

		obj = host1x_to_tegra_bo(reloc->target.bo);
		refs[num_refs++] = &obj->gem;

		अगर (reloc->target.offset >= obj->gem.size) अणु
			err = -EINVAL;
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (copy_from_user(&syncpt, user_syncpt, माप(syncpt))) अणु
		err = -EFAULT;
		जाओ fail;
	पूर्ण

	/* Syncpoपूर्णांक ref will be dropped on job release. */
	sp = host1x_syncpt_get_by_id(host1x, syncpt.id);
	अगर (!sp) अणु
		err = -ENOENT;
		जाओ fail;
	पूर्ण

	job->is_addr_reg = context->client->ops->is_addr_reg;
	job->is_valid_class = context->client->ops->is_valid_class;
	job->syncpt_incrs = syncpt.incrs;
	job->syncpt = sp;
	job->समयout = 10000;

	अगर (args->समयout && args->समयout < 10000)
		job->समयout = args->समयout;

	err = host1x_job_pin(job, context->client->base.dev);
	अगर (err)
		जाओ fail;

	err = host1x_job_submit(job);
	अगर (err) अणु
		host1x_job_unpin(job);
		जाओ fail;
	पूर्ण

	args->fence = job->syncpt_end;

fail:
	जबतक (num_refs--)
		drm_gem_object_put(refs[num_refs]);

	kमुक्त(refs);

put:
	host1x_job_put(job);
	वापस err;
पूर्ण


#अगर_घोषित CONFIG_DRM_TEGRA_STAGING
अटल पूर्णांक tegra_gem_create(काष्ठा drm_device *drm, व्योम *data,
			    काष्ठा drm_file *file)
अणु
	काष्ठा drm_tegra_gem_create *args = data;
	काष्ठा tegra_bo *bo;

	bo = tegra_bo_create_with_handle(file, drm, args->size, args->flags,
					 &args->handle);
	अगर (IS_ERR(bo))
		वापस PTR_ERR(bo);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_gem_mmap(काष्ठा drm_device *drm, व्योम *data,
			  काष्ठा drm_file *file)
अणु
	काष्ठा drm_tegra_gem_mmap *args = data;
	काष्ठा drm_gem_object *gem;
	काष्ठा tegra_bo *bo;

	gem = drm_gem_object_lookup(file, args->handle);
	अगर (!gem)
		वापस -EINVAL;

	bo = to_tegra_bo(gem);

	args->offset = drm_vma_node_offset_addr(&bo->gem.vma_node);

	drm_gem_object_put(gem);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_syncpt_पढ़ो(काष्ठा drm_device *drm, व्योम *data,
			     काष्ठा drm_file *file)
अणु
	काष्ठा host1x *host = dev_get_drvdata(drm->dev->parent);
	काष्ठा drm_tegra_syncpt_पढ़ो *args = data;
	काष्ठा host1x_syncpt *sp;

	sp = host1x_syncpt_get_by_id_noref(host, args->id);
	अगर (!sp)
		वापस -EINVAL;

	args->value = host1x_syncpt_पढ़ो_min(sp);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_syncpt_incr(काष्ठा drm_device *drm, व्योम *data,
			     काष्ठा drm_file *file)
अणु
	काष्ठा host1x *host1x = dev_get_drvdata(drm->dev->parent);
	काष्ठा drm_tegra_syncpt_incr *args = data;
	काष्ठा host1x_syncpt *sp;

	sp = host1x_syncpt_get_by_id_noref(host1x, args->id);
	अगर (!sp)
		वापस -EINVAL;

	वापस host1x_syncpt_incr(sp);
पूर्ण

अटल पूर्णांक tegra_syncpt_रुको(काष्ठा drm_device *drm, व्योम *data,
			     काष्ठा drm_file *file)
अणु
	काष्ठा host1x *host1x = dev_get_drvdata(drm->dev->parent);
	काष्ठा drm_tegra_syncpt_रुको *args = data;
	काष्ठा host1x_syncpt *sp;

	sp = host1x_syncpt_get_by_id_noref(host1x, args->id);
	अगर (!sp)
		वापस -EINVAL;

	वापस host1x_syncpt_रुको(sp, args->thresh,
				  msecs_to_jअगरfies(args->समयout),
				  &args->value);
पूर्ण

अटल पूर्णांक tegra_client_खोलो(काष्ठा tegra_drm_file *fpriv,
			     काष्ठा tegra_drm_client *client,
			     काष्ठा tegra_drm_context *context)
अणु
	पूर्णांक err;

	err = client->ops->खोलो_channel(client, context);
	अगर (err < 0)
		वापस err;

	err = idr_alloc(&fpriv->contexts, context, 1, 0, GFP_KERNEL);
	अगर (err < 0) अणु
		client->ops->बंद_channel(context);
		वापस err;
	पूर्ण

	context->client = client;
	context->id = err;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_खोलो_channel(काष्ठा drm_device *drm, व्योम *data,
			      काष्ठा drm_file *file)
अणु
	काष्ठा tegra_drm_file *fpriv = file->driver_priv;
	काष्ठा tegra_drm *tegra = drm->dev_निजी;
	काष्ठा drm_tegra_खोलो_channel *args = data;
	काष्ठा tegra_drm_context *context;
	काष्ठा tegra_drm_client *client;
	पूर्णांक err = -ENODEV;

	context = kzalloc(माप(*context), GFP_KERNEL);
	अगर (!context)
		वापस -ENOMEM;

	mutex_lock(&fpriv->lock);

	list_क्रम_each_entry(client, &tegra->clients, list)
		अगर (client->base.class == args->client) अणु
			err = tegra_client_खोलो(fpriv, client, context);
			अगर (err < 0)
				अवरोध;

			args->context = context->id;
			अवरोध;
		पूर्ण

	अगर (err < 0)
		kमुक्त(context);

	mutex_unlock(&fpriv->lock);
	वापस err;
पूर्ण

अटल पूर्णांक tegra_बंद_channel(काष्ठा drm_device *drm, व्योम *data,
			       काष्ठा drm_file *file)
अणु
	काष्ठा tegra_drm_file *fpriv = file->driver_priv;
	काष्ठा drm_tegra_बंद_channel *args = data;
	काष्ठा tegra_drm_context *context;
	पूर्णांक err = 0;

	mutex_lock(&fpriv->lock);

	context = idr_find(&fpriv->contexts, args->context);
	अगर (!context) अणु
		err = -EINVAL;
		जाओ unlock;
	पूर्ण

	idr_हटाओ(&fpriv->contexts, context->id);
	tegra_drm_context_मुक्त(context);

unlock:
	mutex_unlock(&fpriv->lock);
	वापस err;
पूर्ण

अटल पूर्णांक tegra_get_syncpt(काष्ठा drm_device *drm, व्योम *data,
			    काष्ठा drm_file *file)
अणु
	काष्ठा tegra_drm_file *fpriv = file->driver_priv;
	काष्ठा drm_tegra_get_syncpt *args = data;
	काष्ठा tegra_drm_context *context;
	काष्ठा host1x_syncpt *syncpt;
	पूर्णांक err = 0;

	mutex_lock(&fpriv->lock);

	context = idr_find(&fpriv->contexts, args->context);
	अगर (!context) अणु
		err = -ENODEV;
		जाओ unlock;
	पूर्ण

	अगर (args->index >= context->client->base.num_syncpts) अणु
		err = -EINVAL;
		जाओ unlock;
	पूर्ण

	syncpt = context->client->base.syncpts[args->index];
	args->id = host1x_syncpt_id(syncpt);

unlock:
	mutex_unlock(&fpriv->lock);
	वापस err;
पूर्ण

अटल पूर्णांक tegra_submit(काष्ठा drm_device *drm, व्योम *data,
			काष्ठा drm_file *file)
अणु
	काष्ठा tegra_drm_file *fpriv = file->driver_priv;
	काष्ठा drm_tegra_submit *args = data;
	काष्ठा tegra_drm_context *context;
	पूर्णांक err;

	mutex_lock(&fpriv->lock);

	context = idr_find(&fpriv->contexts, args->context);
	अगर (!context) अणु
		err = -ENODEV;
		जाओ unlock;
	पूर्ण

	err = context->client->ops->submit(context, args, drm, file);

unlock:
	mutex_unlock(&fpriv->lock);
	वापस err;
पूर्ण

अटल पूर्णांक tegra_get_syncpt_base(काष्ठा drm_device *drm, व्योम *data,
				 काष्ठा drm_file *file)
अणु
	काष्ठा tegra_drm_file *fpriv = file->driver_priv;
	काष्ठा drm_tegra_get_syncpt_base *args = data;
	काष्ठा tegra_drm_context *context;
	काष्ठा host1x_syncpt_base *base;
	काष्ठा host1x_syncpt *syncpt;
	पूर्णांक err = 0;

	mutex_lock(&fpriv->lock);

	context = idr_find(&fpriv->contexts, args->context);
	अगर (!context) अणु
		err = -ENODEV;
		जाओ unlock;
	पूर्ण

	अगर (args->syncpt >= context->client->base.num_syncpts) अणु
		err = -EINVAL;
		जाओ unlock;
	पूर्ण

	syncpt = context->client->base.syncpts[args->syncpt];

	base = host1x_syncpt_get_base(syncpt);
	अगर (!base) अणु
		err = -ENXIO;
		जाओ unlock;
	पूर्ण

	args->id = host1x_syncpt_base_id(base);

unlock:
	mutex_unlock(&fpriv->lock);
	वापस err;
पूर्ण

अटल पूर्णांक tegra_gem_set_tiling(काष्ठा drm_device *drm, व्योम *data,
				काष्ठा drm_file *file)
अणु
	काष्ठा drm_tegra_gem_set_tiling *args = data;
	क्रमागत tegra_bo_tiling_mode mode;
	काष्ठा drm_gem_object *gem;
	अचिन्हित दीर्घ value = 0;
	काष्ठा tegra_bo *bo;

	चयन (args->mode) अणु
	हाल DRM_TEGRA_GEM_TILING_MODE_PITCH:
		mode = TEGRA_BO_TILING_MODE_PITCH;

		अगर (args->value != 0)
			वापस -EINVAL;

		अवरोध;

	हाल DRM_TEGRA_GEM_TILING_MODE_TILED:
		mode = TEGRA_BO_TILING_MODE_TILED;

		अगर (args->value != 0)
			वापस -EINVAL;

		अवरोध;

	हाल DRM_TEGRA_GEM_TILING_MODE_BLOCK:
		mode = TEGRA_BO_TILING_MODE_BLOCK;

		अगर (args->value > 5)
			वापस -EINVAL;

		value = args->value;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	gem = drm_gem_object_lookup(file, args->handle);
	अगर (!gem)
		वापस -ENOENT;

	bo = to_tegra_bo(gem);

	bo->tiling.mode = mode;
	bo->tiling.value = value;

	drm_gem_object_put(gem);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_gem_get_tiling(काष्ठा drm_device *drm, व्योम *data,
				काष्ठा drm_file *file)
अणु
	काष्ठा drm_tegra_gem_get_tiling *args = data;
	काष्ठा drm_gem_object *gem;
	काष्ठा tegra_bo *bo;
	पूर्णांक err = 0;

	gem = drm_gem_object_lookup(file, args->handle);
	अगर (!gem)
		वापस -ENOENT;

	bo = to_tegra_bo(gem);

	चयन (bo->tiling.mode) अणु
	हाल TEGRA_BO_TILING_MODE_PITCH:
		args->mode = DRM_TEGRA_GEM_TILING_MODE_PITCH;
		args->value = 0;
		अवरोध;

	हाल TEGRA_BO_TILING_MODE_TILED:
		args->mode = DRM_TEGRA_GEM_TILING_MODE_TILED;
		args->value = 0;
		अवरोध;

	हाल TEGRA_BO_TILING_MODE_BLOCK:
		args->mode = DRM_TEGRA_GEM_TILING_MODE_BLOCK;
		args->value = bo->tiling.value;
		अवरोध;

	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	drm_gem_object_put(gem);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_gem_set_flags(काष्ठा drm_device *drm, व्योम *data,
			       काष्ठा drm_file *file)
अणु
	काष्ठा drm_tegra_gem_set_flags *args = data;
	काष्ठा drm_gem_object *gem;
	काष्ठा tegra_bo *bo;

	अगर (args->flags & ~DRM_TEGRA_GEM_FLAGS)
		वापस -EINVAL;

	gem = drm_gem_object_lookup(file, args->handle);
	अगर (!gem)
		वापस -ENOENT;

	bo = to_tegra_bo(gem);
	bo->flags = 0;

	अगर (args->flags & DRM_TEGRA_GEM_BOTTOM_UP)
		bo->flags |= TEGRA_BO_BOTTOM_UP;

	drm_gem_object_put(gem);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_gem_get_flags(काष्ठा drm_device *drm, व्योम *data,
			       काष्ठा drm_file *file)
अणु
	काष्ठा drm_tegra_gem_get_flags *args = data;
	काष्ठा drm_gem_object *gem;
	काष्ठा tegra_bo *bo;

	gem = drm_gem_object_lookup(file, args->handle);
	अगर (!gem)
		वापस -ENOENT;

	bo = to_tegra_bo(gem);
	args->flags = 0;

	अगर (bo->flags & TEGRA_BO_BOTTOM_UP)
		args->flags |= DRM_TEGRA_GEM_BOTTOM_UP;

	drm_gem_object_put(gem);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा drm_ioctl_desc tegra_drm_ioctls[] = अणु
#अगर_घोषित CONFIG_DRM_TEGRA_STAGING
	DRM_IOCTL_DEF_DRV(TEGRA_GEM_CREATE, tegra_gem_create,
			  DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(TEGRA_GEM_MMAP, tegra_gem_mmap,
			  DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(TEGRA_SYNCPT_READ, tegra_syncpt_पढ़ो,
			  DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(TEGRA_SYNCPT_INCR, tegra_syncpt_incr,
			  DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(TEGRA_SYNCPT_WAIT, tegra_syncpt_रुको,
			  DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(TEGRA_OPEN_CHANNEL, tegra_खोलो_channel,
			  DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(TEGRA_CLOSE_CHANNEL, tegra_बंद_channel,
			  DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(TEGRA_GET_SYNCPT, tegra_get_syncpt,
			  DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(TEGRA_SUBMIT, tegra_submit,
			  DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(TEGRA_GET_SYNCPT_BASE, tegra_get_syncpt_base,
			  DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(TEGRA_GEM_SET_TILING, tegra_gem_set_tiling,
			  DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(TEGRA_GEM_GET_TILING, tegra_gem_get_tiling,
			  DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(TEGRA_GEM_SET_FLAGS, tegra_gem_set_flags,
			  DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(TEGRA_GEM_GET_FLAGS, tegra_gem_get_flags,
			  DRM_RENDER_ALLOW),
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा file_operations tegra_drm_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = drm_खोलो,
	.release = drm_release,
	.unlocked_ioctl = drm_ioctl,
	.mmap = tegra_drm_mmap,
	.poll = drm_poll,
	.पढ़ो = drm_पढ़ो,
	.compat_ioctl = drm_compat_ioctl,
	.llseek = noop_llseek,
पूर्ण;

अटल पूर्णांक tegra_drm_context_cleanup(पूर्णांक id, व्योम *p, व्योम *data)
अणु
	काष्ठा tegra_drm_context *context = p;

	tegra_drm_context_मुक्त(context);

	वापस 0;
पूर्ण

अटल व्योम tegra_drm_postबंद(काष्ठा drm_device *drm, काष्ठा drm_file *file)
अणु
	काष्ठा tegra_drm_file *fpriv = file->driver_priv;

	mutex_lock(&fpriv->lock);
	idr_क्रम_each(&fpriv->contexts, tegra_drm_context_cleanup, शून्य);
	mutex_unlock(&fpriv->lock);

	idr_destroy(&fpriv->contexts);
	mutex_destroy(&fpriv->lock);
	kमुक्त(fpriv);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक tegra_debugfs_framebuffers(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *)s->निजी;
	काष्ठा drm_device *drm = node->minor->dev;
	काष्ठा drm_framebuffer *fb;

	mutex_lock(&drm->mode_config.fb_lock);

	list_क्रम_each_entry(fb, &drm->mode_config.fb_list, head) अणु
		seq_म_लिखो(s, "%3d: user size: %d x %d, depth %d, %d bpp, refcount %d\n",
			   fb->base.id, fb->width, fb->height,
			   fb->क्रमmat->depth,
			   fb->क्रमmat->cpp[0] * 8,
			   drm_framebuffer_पढ़ो_refcount(fb));
	पूर्ण

	mutex_unlock(&drm->mode_config.fb_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_debugfs_iova(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *)s->निजी;
	काष्ठा drm_device *drm = node->minor->dev;
	काष्ठा tegra_drm *tegra = drm->dev_निजी;
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(s);

	अगर (tegra->करोमुख्य) अणु
		mutex_lock(&tegra->mm_lock);
		drm_mm_prपूर्णांक(&tegra->mm, &p);
		mutex_unlock(&tegra->mm_lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा drm_info_list tegra_debugfs_list[] = अणु
	अणु "framebuffers", tegra_debugfs_framebuffers, 0 पूर्ण,
	अणु "iova", tegra_debugfs_iova, 0 पूर्ण,
पूर्ण;

अटल व्योम tegra_debugfs_init(काष्ठा drm_minor *minor)
अणु
	drm_debugfs_create_files(tegra_debugfs_list,
				 ARRAY_SIZE(tegra_debugfs_list),
				 minor->debugfs_root, minor);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा drm_driver tegra_drm_driver = अणु
	.driver_features = DRIVER_MODESET | DRIVER_GEM |
			   DRIVER_ATOMIC | DRIVER_RENDER,
	.खोलो = tegra_drm_खोलो,
	.postबंद = tegra_drm_postबंद,
	.lastबंद = drm_fb_helper_lastबंद,

#अगर defined(CONFIG_DEBUG_FS)
	.debugfs_init = tegra_debugfs_init,
#पूर्ण_अगर

	.prime_handle_to_fd = drm_gem_prime_handle_to_fd,
	.prime_fd_to_handle = drm_gem_prime_fd_to_handle,
	.gem_prime_import = tegra_gem_prime_import,

	.dumb_create = tegra_bo_dumb_create,

	.ioctls = tegra_drm_ioctls,
	.num_ioctls = ARRAY_SIZE(tegra_drm_ioctls),
	.fops = &tegra_drm_fops,

	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
	.patchlevel = DRIVER_PATCHLEVEL,
पूर्ण;

पूर्णांक tegra_drm_रेजिस्टर_client(काष्ठा tegra_drm *tegra,
			      काष्ठा tegra_drm_client *client)
अणु
	mutex_lock(&tegra->clients_lock);
	list_add_tail(&client->list, &tegra->clients);
	client->drm = tegra;
	mutex_unlock(&tegra->clients_lock);

	वापस 0;
पूर्ण

पूर्णांक tegra_drm_unरेजिस्टर_client(काष्ठा tegra_drm *tegra,
				काष्ठा tegra_drm_client *client)
अणु
	mutex_lock(&tegra->clients_lock);
	list_del_init(&client->list);
	client->drm = शून्य;
	mutex_unlock(&tegra->clients_lock);

	वापस 0;
पूर्ण

पूर्णांक host1x_client_iommu_attach(काष्ठा host1x_client *client)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(client->dev);
	काष्ठा drm_device *drm = dev_get_drvdata(client->host);
	काष्ठा tegra_drm *tegra = drm->dev_निजी;
	काष्ठा iommu_group *group = शून्य;
	पूर्णांक err;

	/*
	 * If the host1x client is alपढ़ोy attached to an IOMMU करोमुख्य that is
	 * not the shared IOMMU करोमुख्य, करोn't try to attach it to a dअगरferent
	 * करोमुख्य. This allows using the IOMMU-backed DMA API.
	 */
	अगर (करोमुख्य && करोमुख्य != tegra->करोमुख्य)
		वापस 0;

	अगर (tegra->करोमुख्य) अणु
		group = iommu_group_get(client->dev);
		अगर (!group)
			वापस -ENODEV;

		अगर (करोमुख्य != tegra->करोमुख्य) अणु
			err = iommu_attach_group(tegra->करोमुख्य, group);
			अगर (err < 0) अणु
				iommu_group_put(group);
				वापस err;
			पूर्ण
		पूर्ण

		tegra->use_explicit_iommu = true;
	पूर्ण

	client->group = group;

	वापस 0;
पूर्ण

व्योम host1x_client_iommu_detach(काष्ठा host1x_client *client)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(client->host);
	काष्ठा tegra_drm *tegra = drm->dev_निजी;
	काष्ठा iommu_करोमुख्य *करोमुख्य;

	अगर (client->group) अणु
		/*
		 * Devices that are part of the same group may no दीर्घer be
		 * attached to a करोमुख्य at this poपूर्णांक because their group may
		 * have been detached by an earlier client.
		 */
		करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(client->dev);
		अगर (करोमुख्य)
			iommu_detach_group(tegra->करोमुख्य, client->group);

		iommu_group_put(client->group);
		client->group = शून्य;
	पूर्ण
पूर्ण

व्योम *tegra_drm_alloc(काष्ठा tegra_drm *tegra, माप_प्रकार size, dma_addr_t *dma)
अणु
	काष्ठा iova *alloc;
	व्योम *virt;
	gfp_t gfp;
	पूर्णांक err;

	अगर (tegra->करोमुख्य)
		size = iova_align(&tegra->carveout.करोमुख्य, size);
	अन्यथा
		size = PAGE_ALIGN(size);

	gfp = GFP_KERNEL | __GFP_ZERO;
	अगर (!tegra->करोमुख्य) अणु
		/*
		 * Many units only support 32-bit addresses, even on 64-bit
		 * SoCs. If there is no IOMMU to translate पूर्णांकo a 32-bit IO
		 * भव address space, क्रमce allocations to be in the
		 * lower 32-bit range.
		 */
		gfp |= GFP_DMA;
	पूर्ण

	virt = (व्योम *)__get_मुक्त_pages(gfp, get_order(size));
	अगर (!virt)
		वापस ERR_PTR(-ENOMEM);

	अगर (!tegra->करोमुख्य) अणु
		/*
		 * If IOMMU is disabled, devices address physical memory
		 * directly.
		 */
		*dma = virt_to_phys(virt);
		वापस virt;
	पूर्ण

	alloc = alloc_iova(&tegra->carveout.करोमुख्य,
			   size >> tegra->carveout.shअगरt,
			   tegra->carveout.limit, true);
	अगर (!alloc) अणु
		err = -EBUSY;
		जाओ मुक्त_pages;
	पूर्ण

	*dma = iova_dma_addr(&tegra->carveout.करोमुख्य, alloc);
	err = iommu_map(tegra->करोमुख्य, *dma, virt_to_phys(virt),
			size, IOMMU_READ | IOMMU_WRITE);
	अगर (err < 0)
		जाओ मुक्त_iova;

	वापस virt;

मुक्त_iova:
	__मुक्त_iova(&tegra->carveout.करोमुख्य, alloc);
मुक्त_pages:
	मुक्त_pages((अचिन्हित दीर्घ)virt, get_order(size));

	वापस ERR_PTR(err);
पूर्ण

व्योम tegra_drm_मुक्त(काष्ठा tegra_drm *tegra, माप_प्रकार size, व्योम *virt,
		    dma_addr_t dma)
अणु
	अगर (tegra->करोमुख्य)
		size = iova_align(&tegra->carveout.करोमुख्य, size);
	अन्यथा
		size = PAGE_ALIGN(size);

	अगर (tegra->करोमुख्य) अणु
		iommu_unmap(tegra->करोमुख्य, dma, size);
		मुक्त_iova(&tegra->carveout.करोमुख्य,
			  iova_pfn(&tegra->carveout.करोमुख्य, dma));
	पूर्ण

	मुक्त_pages((अचिन्हित दीर्घ)virt, get_order(size));
पूर्ण

अटल bool host1x_drm_wants_iommu(काष्ठा host1x_device *dev)
अणु
	काष्ठा host1x *host1x = dev_get_drvdata(dev->dev.parent);
	काष्ठा iommu_करोमुख्य *करोमुख्य;

	/*
	 * If the Tegra DRM clients are backed by an IOMMU, push buffers are
	 * likely to be allocated beyond the 32-bit boundary अगर sufficient
	 * प्रणाली memory is available. This is problematic on earlier Tegra
	 * generations where host1x supports a maximum of 32 address bits in
	 * the GATHER opcode. In this हाल, unless host1x is behind an IOMMU
	 * as well it won't be able to process buffers allocated beyond the
	 * 32-bit boundary.
	 *
	 * The DMA API will use bounce buffers in this हाल, so that could
	 * perhaps still be made to work, even अगर less efficient, but there
	 * is another catch: in order to perक्रमm cache मुख्यtenance on pages
	 * allocated क्रम discontiguous buffers we need to map and unmap the
	 * SG table representing these buffers. This is fine क्रम something
	 * small like a push buffer, but it exhausts the bounce buffer pool
	 * (typically on the order of a few MiB) क्रम framebuffers (many MiB
	 * क्रम any modern resolution).
	 *
	 * Work around this by making sure that Tegra DRM clients only use
	 * an IOMMU अगर the parent host1x also uses an IOMMU.
	 *
	 * Note that there's still a small gap here that we don't cover: अगर
	 * the DMA API is backed by an IOMMU there's no way to control which
	 * device is attached to an IOMMU and which isn't, except via wiring
	 * up the device tree appropriately. This is considered an problem
	 * of पूर्णांकegration, so care must be taken क्रम the DT to be consistent.
	 */
	करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev->dev.parent);

	/*
	 * Tegra20 and Tegra30 करोn't support addressing memory beyond the
	 * 32-bit boundary, so the regular GATHER opcodes will always be
	 * sufficient and whether or not the host1x is attached to an IOMMU
	 * करोesn't matter.
	 */
	अगर (!करोमुख्य && host1x_get_dma_mask(host1x) <= DMA_BIT_MASK(32))
		वापस true;

	वापस करोमुख्य != शून्य;
पूर्ण

अटल पूर्णांक host1x_drm_probe(काष्ठा host1x_device *dev)
अणु
	काष्ठा tegra_drm *tegra;
	काष्ठा drm_device *drm;
	पूर्णांक err;

	drm = drm_dev_alloc(&tegra_drm_driver, &dev->dev);
	अगर (IS_ERR(drm))
		वापस PTR_ERR(drm);

	tegra = kzalloc(माप(*tegra), GFP_KERNEL);
	अगर (!tegra) अणु
		err = -ENOMEM;
		जाओ put;
	पूर्ण

	अगर (host1x_drm_wants_iommu(dev) && iommu_present(&platक्रमm_bus_type)) अणु
		tegra->करोमुख्य = iommu_करोमुख्य_alloc(&platक्रमm_bus_type);
		अगर (!tegra->करोमुख्य) अणु
			err = -ENOMEM;
			जाओ मुक्त;
		पूर्ण

		err = iova_cache_get();
		अगर (err < 0)
			जाओ करोमुख्य;
	पूर्ण

	mutex_init(&tegra->clients_lock);
	INIT_LIST_HEAD(&tegra->clients);

	dev_set_drvdata(&dev->dev, drm);
	drm->dev_निजी = tegra;
	tegra->drm = drm;

	drm_mode_config_init(drm);

	drm->mode_config.min_width = 0;
	drm->mode_config.min_height = 0;
	drm->mode_config.max_width = 0;
	drm->mode_config.max_height = 0;

	drm->mode_config.allow_fb_modअगरiers = true;

	drm->mode_config.normalize_zpos = true;

	drm->mode_config.funcs = &tegra_drm_mode_config_funcs;
	drm->mode_config.helper_निजी = &tegra_drm_mode_config_helpers;

	err = tegra_drm_fb_prepare(drm);
	अगर (err < 0)
		जाओ config;

	drm_kms_helper_poll_init(drm);

	err = host1x_device_init(dev);
	अगर (err < 0)
		जाओ fbdev;

	/*
	 * Now that all display controller have been initialized, the maximum
	 * supported resolution is known and the biपंचांगask क्रम horizontal and
	 * vertical bitfields can be computed.
	 */
	tegra->hmask = drm->mode_config.max_width - 1;
	tegra->vmask = drm->mode_config.max_height - 1;

	अगर (tegra->use_explicit_iommu) अणु
		u64 carveout_start, carveout_end, gem_start, gem_end;
		u64 dma_mask = dma_get_mask(&dev->dev);
		dma_addr_t start, end;
		अचिन्हित दीर्घ order;

		start = tegra->करोमुख्य->geometry.aperture_start & dma_mask;
		end = tegra->करोमुख्य->geometry.aperture_end & dma_mask;

		gem_start = start;
		gem_end = end - CARVEOUT_SZ;
		carveout_start = gem_end + 1;
		carveout_end = end;

		order = __ffs(tegra->करोमुख्य->pgsize_biपंचांगap);
		init_iova_करोमुख्य(&tegra->carveout.करोमुख्य, 1UL << order,
				 carveout_start >> order);

		tegra->carveout.shअगरt = iova_shअगरt(&tegra->carveout.करोमुख्य);
		tegra->carveout.limit = carveout_end >> tegra->carveout.shअगरt;

		drm_mm_init(&tegra->mm, gem_start, gem_end - gem_start + 1);
		mutex_init(&tegra->mm_lock);

		DRM_DEBUG_DRIVER("IOMMU apertures:\n");
		DRM_DEBUG_DRIVER("  GEM: %#llx-%#llx\n", gem_start, gem_end);
		DRM_DEBUG_DRIVER("  Carveout: %#llx-%#llx\n", carveout_start,
				 carveout_end);
	पूर्ण अन्यथा अगर (tegra->करोमुख्य) अणु
		iommu_करोमुख्य_मुक्त(tegra->करोमुख्य);
		tegra->करोमुख्य = शून्य;
		iova_cache_put();
	पूर्ण

	अगर (tegra->hub) अणु
		err = tegra_display_hub_prepare(tegra->hub);
		अगर (err < 0)
			जाओ device;
	पूर्ण

	/*
	 * We करोn't use the drm_irq_install() helpers provided by the DRM
	 * core, so we need to set this manually in order to allow the
	 * DRM_IOCTL_WAIT_VBLANK to operate correctly.
	 */
	drm->irq_enabled = true;

	/* syncpoपूर्णांकs are used क्रम full 32-bit hardware VBLANK counters */
	drm->max_vblank_count = 0xffffffff;

	err = drm_vblank_init(drm, drm->mode_config.num_crtc);
	अगर (err < 0)
		जाओ hub;

	drm_mode_config_reset(drm);

	err = drm_fb_helper_हटाओ_conflicting_framebuffers(शून्य, "tegradrmfb",
							    false);
	अगर (err < 0)
		जाओ hub;

	err = tegra_drm_fb_init(drm);
	अगर (err < 0)
		जाओ hub;

	err = drm_dev_रेजिस्टर(drm, 0);
	अगर (err < 0)
		जाओ fb;

	वापस 0;

fb:
	tegra_drm_fb_निकास(drm);
hub:
	अगर (tegra->hub)
		tegra_display_hub_cleanup(tegra->hub);
device:
	अगर (tegra->करोमुख्य) अणु
		mutex_destroy(&tegra->mm_lock);
		drm_mm_takeकरोwn(&tegra->mm);
		put_iova_करोमुख्य(&tegra->carveout.करोमुख्य);
		iova_cache_put();
	पूर्ण

	host1x_device_निकास(dev);
fbdev:
	drm_kms_helper_poll_fini(drm);
	tegra_drm_fb_मुक्त(drm);
config:
	drm_mode_config_cleanup(drm);
करोमुख्य:
	अगर (tegra->करोमुख्य)
		iommu_करोमुख्य_मुक्त(tegra->करोमुख्य);
मुक्त:
	kमुक्त(tegra);
put:
	drm_dev_put(drm);
	वापस err;
पूर्ण

अटल पूर्णांक host1x_drm_हटाओ(काष्ठा host1x_device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(&dev->dev);
	काष्ठा tegra_drm *tegra = drm->dev_निजी;
	पूर्णांक err;

	drm_dev_unरेजिस्टर(drm);

	drm_kms_helper_poll_fini(drm);
	tegra_drm_fb_निकास(drm);
	drm_atomic_helper_shutकरोwn(drm);
	drm_mode_config_cleanup(drm);

	अगर (tegra->hub)
		tegra_display_hub_cleanup(tegra->hub);

	err = host1x_device_निकास(dev);
	अगर (err < 0)
		dev_err(&dev->dev, "host1x device cleanup failed: %d\n", err);

	अगर (tegra->करोमुख्य) अणु
		mutex_destroy(&tegra->mm_lock);
		drm_mm_takeकरोwn(&tegra->mm);
		put_iova_करोमुख्य(&tegra->carveout.करोमुख्य);
		iova_cache_put();
		iommu_करोमुख्य_मुक्त(tegra->करोमुख्य);
	पूर्ण

	kमुक्त(tegra);
	drm_dev_put(drm);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक host1x_drm_suspend(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_suspend(drm);
पूर्ण

अटल पूर्णांक host1x_drm_resume(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_resume(drm);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(host1x_drm_pm_ops, host1x_drm_suspend,
			 host1x_drm_resume);

अटल स्थिर काष्ठा of_device_id host1x_drm_subdevs[] = अणु
	अणु .compatible = "nvidia,tegra20-dc", पूर्ण,
	अणु .compatible = "nvidia,tegra20-hdmi", पूर्ण,
	अणु .compatible = "nvidia,tegra20-gr2d", पूर्ण,
	अणु .compatible = "nvidia,tegra20-gr3d", पूर्ण,
	अणु .compatible = "nvidia,tegra30-dc", पूर्ण,
	अणु .compatible = "nvidia,tegra30-hdmi", पूर्ण,
	अणु .compatible = "nvidia,tegra30-gr2d", पूर्ण,
	अणु .compatible = "nvidia,tegra30-gr3d", पूर्ण,
	अणु .compatible = "nvidia,tegra114-dc", पूर्ण,
	अणु .compatible = "nvidia,tegra114-dsi", पूर्ण,
	अणु .compatible = "nvidia,tegra114-hdmi", पूर्ण,
	अणु .compatible = "nvidia,tegra114-gr2d", पूर्ण,
	अणु .compatible = "nvidia,tegra114-gr3d", पूर्ण,
	अणु .compatible = "nvidia,tegra124-dc", पूर्ण,
	अणु .compatible = "nvidia,tegra124-sor", पूर्ण,
	अणु .compatible = "nvidia,tegra124-hdmi", पूर्ण,
	अणु .compatible = "nvidia,tegra124-dsi", पूर्ण,
	अणु .compatible = "nvidia,tegra124-vic", पूर्ण,
	अणु .compatible = "nvidia,tegra132-dsi", पूर्ण,
	अणु .compatible = "nvidia,tegra210-dc", पूर्ण,
	अणु .compatible = "nvidia,tegra210-dsi", पूर्ण,
	अणु .compatible = "nvidia,tegra210-sor", पूर्ण,
	अणु .compatible = "nvidia,tegra210-sor1", पूर्ण,
	अणु .compatible = "nvidia,tegra210-vic", पूर्ण,
	अणु .compatible = "nvidia,tegra186-display", पूर्ण,
	अणु .compatible = "nvidia,tegra186-dc", पूर्ण,
	अणु .compatible = "nvidia,tegra186-sor", पूर्ण,
	अणु .compatible = "nvidia,tegra186-sor1", पूर्ण,
	अणु .compatible = "nvidia,tegra186-vic", पूर्ण,
	अणु .compatible = "nvidia,tegra194-display", पूर्ण,
	अणु .compatible = "nvidia,tegra194-dc", पूर्ण,
	अणु .compatible = "nvidia,tegra194-sor", पूर्ण,
	अणु .compatible = "nvidia,tegra194-vic", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा host1x_driver host1x_drm_driver = अणु
	.driver = अणु
		.name = "drm",
		.pm = &host1x_drm_pm_ops,
	पूर्ण,
	.probe = host1x_drm_probe,
	.हटाओ = host1x_drm_हटाओ,
	.subdevs = host1x_drm_subdevs,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर drivers[] = अणु
	&tegra_display_hub_driver,
	&tegra_dc_driver,
	&tegra_hdmi_driver,
	&tegra_dsi_driver,
	&tegra_dpaux_driver,
	&tegra_sor_driver,
	&tegra_gr2d_driver,
	&tegra_gr3d_driver,
	&tegra_vic_driver,
पूर्ण;

अटल पूर्णांक __init host1x_drm_init(व्योम)
अणु
	पूर्णांक err;

	err = host1x_driver_रेजिस्टर(&host1x_drm_driver);
	अगर (err < 0)
		वापस err;

	err = platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
	अगर (err < 0)
		जाओ unरेजिस्टर_host1x;

	वापस 0;

unरेजिस्टर_host1x:
	host1x_driver_unरेजिस्टर(&host1x_drm_driver);
	वापस err;
पूर्ण
module_init(host1x_drm_init);

अटल व्योम __निकास host1x_drm_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
	host1x_driver_unरेजिस्टर(&host1x_drm_driver);
पूर्ण
module_निकास(host1x_drm_निकास);

MODULE_AUTHOR("Thierry Reding <thierry.reding@avionic-design.de>");
MODULE_DESCRIPTION("NVIDIA Tegra DRM driver");
MODULE_LICENSE("GPL v2");
