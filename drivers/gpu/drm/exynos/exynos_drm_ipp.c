<शैली गुरु>
/*
 * Copyright (C) 2017 Samsung Electronics Co.Ltd
 * Authors:
 *	Marek Szyprowski <m.szyprowski@samsung.com>
 *
 * Exynos DRM Image Post Processing (IPP) related functions
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 */

#समावेश <linux/uaccess.h>

#समावेश <drm/drm_file.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_mode.h>
#समावेश <drm/exynos_drm.h>

#समावेश "exynos_drm_drv.h"
#समावेश "exynos_drm_gem.h"
#समावेश "exynos_drm_ipp.h"

अटल पूर्णांक num_ipp;
अटल LIST_HEAD(ipp_list);

/**
 * exynos_drm_ipp_रेजिस्टर - Register a new picture processor hardware module
 * @dev: DRM device
 * @ipp: ipp module to init
 * @funcs: callbacks क्रम the new ipp object
 * @caps: biपंचांगask of ipp capabilities (%DRM_EXYNOS_IPP_CAP_*)
 * @क्रमmats: array of supported क्रमmats
 * @num_क्रमmats: size of the supported क्रमmats array
 * @name: name (क्रम debugging purposes)
 *
 * Initializes a ipp module.
 *
 * Returns:
 * Zero on success, error code on failure.
 */
पूर्णांक exynos_drm_ipp_रेजिस्टर(काष्ठा device *dev, काष्ठा exynos_drm_ipp *ipp,
		स्थिर काष्ठा exynos_drm_ipp_funcs *funcs, अचिन्हित पूर्णांक caps,
		स्थिर काष्ठा exynos_drm_ipp_क्रमmats *क्रमmats,
		अचिन्हित पूर्णांक num_क्रमmats, स्थिर अक्षर *name)
अणु
	WARN_ON(!ipp);
	WARN_ON(!funcs);
	WARN_ON(!क्रमmats);
	WARN_ON(!num_क्रमmats);

	spin_lock_init(&ipp->lock);
	INIT_LIST_HEAD(&ipp->toकरो_list);
	init_रुकोqueue_head(&ipp->करोne_wq);
	ipp->dev = dev;
	ipp->funcs = funcs;
	ipp->capabilities = caps;
	ipp->name = name;
	ipp->क्रमmats = क्रमmats;
	ipp->num_क्रमmats = num_क्रमmats;

	/* ipp_list modअगरication is serialized by component framework */
	list_add_tail(&ipp->head, &ipp_list);
	ipp->id = num_ipp++;

	DRM_DEV_DEBUG_DRIVER(dev, "Registered ipp %d\n", ipp->id);

	वापस 0;
पूर्ण

/**
 * exynos_drm_ipp_unरेजिस्टर - Unरेजिस्टर the picture processor module
 * @dev: DRM device
 * @ipp: ipp module
 */
व्योम exynos_drm_ipp_unरेजिस्टर(काष्ठा device *dev,
			       काष्ठा exynos_drm_ipp *ipp)
अणु
	WARN_ON(ipp->task);
	WARN_ON(!list_empty(&ipp->toकरो_list));
	list_del(&ipp->head);
पूर्ण

/**
 * exynos_drm_ipp_ioctl_get_res_ioctl - क्रमागतerate all ipp modules
 * @dev: DRM device
 * @data: ioctl data
 * @file_priv: DRM file info
 *
 * Conकाष्ठा a list of ipp ids.
 *
 * Called by the user via ioctl.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक exynos_drm_ipp_get_res_ioctl(काष्ठा drm_device *dev, व्योम *data,
				 काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_exynos_ioctl_ipp_get_res *resp = data;
	काष्ठा exynos_drm_ipp *ipp;
	uपूर्णांक32_t __user *ipp_ptr = (uपूर्णांक32_t __user *)
						(अचिन्हित दीर्घ)resp->ipp_id_ptr;
	अचिन्हित पूर्णांक count = num_ipp, copied = 0;

	/*
	 * This ioctl is called twice, once to determine how much space is
	 * needed, and the 2nd समय to fill it.
	 */
	अगर (count && resp->count_ipps >= count) अणु
		list_क्रम_each_entry(ipp, &ipp_list, head) अणु
			अगर (put_user(ipp->id, ipp_ptr + copied))
				वापस -EFAULT;
			copied++;
		पूर्ण
	पूर्ण
	resp->count_ipps = count;

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा exynos_drm_ipp *__ipp_get(uपूर्णांक32_t id)
अणु
	काष्ठा exynos_drm_ipp *ipp;

	list_क्रम_each_entry(ipp, &ipp_list, head)
		अगर (ipp->id == id)
			वापस ipp;
	वापस शून्य;
पूर्ण

/**
 * exynos_drm_ipp_ioctl_get_caps - get ipp module capabilities and क्रमmats
 * @dev: DRM device
 * @data: ioctl data
 * @file_priv: DRM file info
 *
 * Conकाष्ठा a काष्ठाure describing ipp module capabilities.
 *
 * Called by the user via ioctl.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक exynos_drm_ipp_get_caps_ioctl(काष्ठा drm_device *dev, व्योम *data,
				  काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_exynos_ioctl_ipp_get_caps *resp = data;
	व्योम __user *ptr = (व्योम __user *)(अचिन्हित दीर्घ)resp->क्रमmats_ptr;
	काष्ठा exynos_drm_ipp *ipp;
	पूर्णांक i;

	ipp = __ipp_get(resp->ipp_id);
	अगर (!ipp)
		वापस -ENOENT;

	resp->ipp_id = ipp->id;
	resp->capabilities = ipp->capabilities;

	/*
	 * This ioctl is called twice, once to determine how much space is
	 * needed, and the 2nd समय to fill it.
	 */
	अगर (resp->क्रमmats_count >= ipp->num_क्रमmats) अणु
		क्रम (i = 0; i < ipp->num_क्रमmats; i++) अणु
			काष्ठा drm_exynos_ipp_क्रमmat पंचांगp = अणु
				.fourcc = ipp->क्रमmats[i].fourcc,
				.type = ipp->क्रमmats[i].type,
				.modअगरier = ipp->क्रमmats[i].modअगरier,
			पूर्ण;

			अगर (copy_to_user(ptr, &पंचांगp, माप(पंचांगp)))
				वापस -EFAULT;
			ptr += माप(पंचांगp);
		पूर्ण
	पूर्ण
	resp->क्रमmats_count = ipp->num_क्रमmats;

	वापस 0;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा exynos_drm_ipp_क्रमmats *__ipp_क्रमmat_get(
				काष्ठा exynos_drm_ipp *ipp, uपूर्णांक32_t fourcc,
				uपूर्णांक64_t mod, अचिन्हित पूर्णांक type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ipp->num_क्रमmats; i++) अणु
		अगर ((ipp->क्रमmats[i].type & type) &&
		    ipp->क्रमmats[i].fourcc == fourcc &&
		    ipp->क्रमmats[i].modअगरier == mod)
			वापस &ipp->क्रमmats[i];
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * exynos_drm_ipp_get_limits_ioctl - get ipp module limits
 * @dev: DRM device
 * @data: ioctl data
 * @file_priv: DRM file info
 *
 * Conकाष्ठा a काष्ठाure describing ipp module limitations क्रम provided
 * picture क्रमmat.
 *
 * Called by the user via ioctl.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक exynos_drm_ipp_get_limits_ioctl(काष्ठा drm_device *dev, व्योम *data,
				    काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_exynos_ioctl_ipp_get_limits *resp = data;
	व्योम __user *ptr = (व्योम __user *)(अचिन्हित दीर्घ)resp->limits_ptr;
	स्थिर काष्ठा exynos_drm_ipp_क्रमmats *क्रमmat;
	काष्ठा exynos_drm_ipp *ipp;

	अगर (resp->type != DRM_EXYNOS_IPP_FORMAT_SOURCE &&
	    resp->type != DRM_EXYNOS_IPP_FORMAT_DESTINATION)
		वापस -EINVAL;

	ipp = __ipp_get(resp->ipp_id);
	अगर (!ipp)
		वापस -ENOENT;

	क्रमmat = __ipp_क्रमmat_get(ipp, resp->fourcc, resp->modअगरier,
				  resp->type);
	अगर (!क्रमmat)
		वापस -EINVAL;

	/*
	 * This ioctl is called twice, once to determine how much space is
	 * needed, and the 2nd समय to fill it.
	 */
	अगर (क्रमmat->num_limits && resp->limits_count >= क्रमmat->num_limits)
		अगर (copy_to_user((व्योम __user *)ptr, क्रमmat->limits,
				 माप(*क्रमmat->limits) * क्रमmat->num_limits))
			वापस -EFAULT;
	resp->limits_count = क्रमmat->num_limits;

	वापस 0;
पूर्ण

काष्ठा drm_pending_exynos_ipp_event अणु
	काष्ठा drm_pending_event base;
	काष्ठा drm_exynos_ipp_event event;
पूर्ण;

अटल अंतरभूत काष्ठा exynos_drm_ipp_task *
			exynos_drm_ipp_task_alloc(काष्ठा exynos_drm_ipp *ipp)
अणु
	काष्ठा exynos_drm_ipp_task *task;

	task = kzalloc(माप(*task), GFP_KERNEL);
	अगर (!task)
		वापस शून्य;

	task->dev = ipp->dev;
	task->ipp = ipp;

	/* some शेषs */
	task->src.rect.w = task->dst.rect.w = अच_पूर्णांक_उच्च;
	task->src.rect.h = task->dst.rect.h = अच_पूर्णांक_उच्च;
	task->transक्रमm.rotation = DRM_MODE_ROTATE_0;

	DRM_DEV_DEBUG_DRIVER(task->dev, "Allocated task %pK\n", task);

	वापस task;
पूर्ण

अटल स्थिर काष्ठा exynos_drm_param_map अणु
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक offset;
पूर्ण exynos_drm_ipp_params_maps[] = अणु
	अणु
		DRM_EXYNOS_IPP_TASK_BUFFER | DRM_EXYNOS_IPP_TASK_TYPE_SOURCE,
		माप(काष्ठा drm_exynos_ipp_task_buffer),
		दुरत्व(काष्ठा exynos_drm_ipp_task, src.buf),
	पूर्ण, अणु
		DRM_EXYNOS_IPP_TASK_BUFFER |
			DRM_EXYNOS_IPP_TASK_TYPE_DESTINATION,
		माप(काष्ठा drm_exynos_ipp_task_buffer),
		दुरत्व(काष्ठा exynos_drm_ipp_task, dst.buf),
	पूर्ण, अणु
		DRM_EXYNOS_IPP_TASK_RECTANGLE | DRM_EXYNOS_IPP_TASK_TYPE_SOURCE,
		माप(काष्ठा drm_exynos_ipp_task_rect),
		दुरत्व(काष्ठा exynos_drm_ipp_task, src.rect),
	पूर्ण, अणु
		DRM_EXYNOS_IPP_TASK_RECTANGLE |
			DRM_EXYNOS_IPP_TASK_TYPE_DESTINATION,
		माप(काष्ठा drm_exynos_ipp_task_rect),
		दुरत्व(काष्ठा exynos_drm_ipp_task, dst.rect),
	पूर्ण, अणु
		DRM_EXYNOS_IPP_TASK_TRANSFORM,
		माप(काष्ठा drm_exynos_ipp_task_transक्रमm),
		दुरत्व(काष्ठा exynos_drm_ipp_task, transक्रमm),
	पूर्ण, अणु
		DRM_EXYNOS_IPP_TASK_ALPHA,
		माप(काष्ठा drm_exynos_ipp_task_alpha),
		दुरत्व(काष्ठा exynos_drm_ipp_task, alpha),
	पूर्ण,
पूर्ण;

अटल पूर्णांक exynos_drm_ipp_task_set(काष्ठा exynos_drm_ipp_task *task,
				   काष्ठा drm_exynos_ioctl_ipp_commit *arg)
अणु
	स्थिर काष्ठा exynos_drm_param_map *map = exynos_drm_ipp_params_maps;
	व्योम __user *params = (व्योम __user *)(अचिन्हित दीर्घ)arg->params_ptr;
	अचिन्हित पूर्णांक size = arg->params_size;
	uपूर्णांक32_t id;
	पूर्णांक i;

	जबतक (size) अणु
		अगर (get_user(id, (uपूर्णांक32_t __user *)params))
			वापस -EFAULT;

		क्रम (i = 0; i < ARRAY_SIZE(exynos_drm_ipp_params_maps); i++)
			अगर (map[i].id == id)
				अवरोध;
		अगर (i == ARRAY_SIZE(exynos_drm_ipp_params_maps) ||
		    map[i].size > size)
			वापस -EINVAL;

		अगर (copy_from_user((व्योम *)task + map[i].offset, params,
				   map[i].size))
			वापस -EFAULT;

		params += map[i].size;
		size -= map[i].size;
	पूर्ण

	DRM_DEV_DEBUG_DRIVER(task->dev,
			     "Got task %pK configuration from userspace\n",
			     task);
	वापस 0;
पूर्ण

अटल पूर्णांक exynos_drm_ipp_task_setup_buffer(काष्ठा exynos_drm_ipp_buffer *buf,
					    काष्ठा drm_file *filp)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	/* get GEM buffers and check their size */
	क्रम (i = 0; i < buf->क्रमmat->num_planes; i++) अणु
		अचिन्हित पूर्णांक height = (i == 0) ? buf->buf.height :
			     DIV_ROUND_UP(buf->buf.height, buf->क्रमmat->vsub);
		अचिन्हित दीर्घ size = height * buf->buf.pitch[i];
		काष्ठा exynos_drm_gem *gem = exynos_drm_gem_get(filp,
							    buf->buf.gem_id[i]);
		अगर (!gem) अणु
			ret = -ENOENT;
			जाओ gem_मुक्त;
		पूर्ण
		buf->exynos_gem[i] = gem;

		अगर (size + buf->buf.offset[i] > buf->exynos_gem[i]->size) अणु
			i++;
			ret = -EINVAL;
			जाओ gem_मुक्त;
		पूर्ण
		buf->dma_addr[i] = buf->exynos_gem[i]->dma_addr +
				   buf->buf.offset[i];
	पूर्ण

	वापस 0;
gem_मुक्त:
	जबतक (i--) अणु
		exynos_drm_gem_put(buf->exynos_gem[i]);
		buf->exynos_gem[i] = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम exynos_drm_ipp_task_release_buf(काष्ठा exynos_drm_ipp_buffer *buf)
अणु
	पूर्णांक i;

	अगर (!buf->exynos_gem[0])
		वापस;
	क्रम (i = 0; i < buf->क्रमmat->num_planes; i++)
		exynos_drm_gem_put(buf->exynos_gem[i]);
पूर्ण

अटल व्योम exynos_drm_ipp_task_मुक्त(काष्ठा exynos_drm_ipp *ipp,
				 काष्ठा exynos_drm_ipp_task *task)
अणु
	DRM_DEV_DEBUG_DRIVER(task->dev, "Freeing task %pK\n", task);

	exynos_drm_ipp_task_release_buf(&task->src);
	exynos_drm_ipp_task_release_buf(&task->dst);
	अगर (task->event)
		drm_event_cancel_मुक्त(ipp->drm_dev, &task->event->base);
	kमुक्त(task);
पूर्ण

काष्ठा drm_ipp_limit अणु
	काष्ठा drm_exynos_ipp_limit_val h;
	काष्ठा drm_exynos_ipp_limit_val v;
पूर्ण;

क्रमागत drm_ipp_size_id अणु
	IPP_LIMIT_BUFFER, IPP_LIMIT_AREA, IPP_LIMIT_ROTATED, IPP_LIMIT_MAX
पूर्ण;

अटल स्थिर क्रमागत drm_exynos_ipp_limit_type limit_id_fallback[IPP_LIMIT_MAX][4] = अणु
	[IPP_LIMIT_BUFFER]  = अणु DRM_EXYNOS_IPP_LIMIT_SIZE_BUFFER पूर्ण,
	[IPP_LIMIT_AREA]    = अणु DRM_EXYNOS_IPP_LIMIT_SIZE_AREA,
				DRM_EXYNOS_IPP_LIMIT_SIZE_BUFFER पूर्ण,
	[IPP_LIMIT_ROTATED] = अणु DRM_EXYNOS_IPP_LIMIT_SIZE_ROTATED,
				DRM_EXYNOS_IPP_LIMIT_SIZE_AREA,
				DRM_EXYNOS_IPP_LIMIT_SIZE_BUFFER पूर्ण,
पूर्ण;

अटल अंतरभूत व्योम __limit_set_val(अचिन्हित पूर्णांक *ptr, अचिन्हित पूर्णांक val)
अणु
	अगर (!*ptr)
		*ptr = val;
पूर्ण

अटल व्योम __get_size_limit(स्थिर काष्ठा drm_exynos_ipp_limit *limits,
			     अचिन्हित पूर्णांक num_limits, क्रमागत drm_ipp_size_id id,
			     काष्ठा drm_ipp_limit *res)
अणु
	स्थिर काष्ठा drm_exynos_ipp_limit *l = limits;
	पूर्णांक i = 0;

	स_रखो(res, 0, माप(*res));
	क्रम (i = 0; limit_id_fallback[id][i]; i++)
		क्रम (l = limits; l - limits < num_limits; l++) अणु
			अगर (((l->type & DRM_EXYNOS_IPP_LIMIT_TYPE_MASK) !=
			      DRM_EXYNOS_IPP_LIMIT_TYPE_SIZE) ||
			    ((l->type & DRM_EXYNOS_IPP_LIMIT_SIZE_MASK) !=
						     limit_id_fallback[id][i]))
				जारी;
			__limit_set_val(&res->h.min, l->h.min);
			__limit_set_val(&res->h.max, l->h.max);
			__limit_set_val(&res->h.align, l->h.align);
			__limit_set_val(&res->v.min, l->v.min);
			__limit_set_val(&res->v.max, l->v.max);
			__limit_set_val(&res->v.align, l->v.align);
		पूर्ण
पूर्ण

अटल अंतरभूत bool __align_check(अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक align)
अणु
	अगर (align && (val & (align - 1))) अणु
		DRM_DEBUG_DRIVER("Value %d exceeds HW limits (align %d)\n",
				 val, align);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल अंतरभूत bool __size_limit_check(अचिन्हित पूर्णांक val,
				 काष्ठा drm_exynos_ipp_limit_val *l)
अणु
	अगर ((l->min && val < l->min) || (l->max && val > l->max)) अणु
		DRM_DEBUG_DRIVER("Value %d exceeds HW limits (min %d, max %d)\n",
				 val, l->min, l->max);
		वापस false;
	पूर्ण
	वापस __align_check(val, l->align);
पूर्ण

अटल पूर्णांक exynos_drm_ipp_check_size_limits(काष्ठा exynos_drm_ipp_buffer *buf,
	स्थिर काष्ठा drm_exynos_ipp_limit *limits, अचिन्हित पूर्णांक num_limits,
	bool rotate, bool swap)
अणु
	क्रमागत drm_ipp_size_id id = rotate ? IPP_LIMIT_ROTATED : IPP_LIMIT_AREA;
	काष्ठा drm_ipp_limit l;
	काष्ठा drm_exynos_ipp_limit_val *lh = &l.h, *lv = &l.v;
	पूर्णांक real_width = buf->buf.pitch[0] / buf->क्रमmat->cpp[0];

	अगर (!limits)
		वापस 0;

	__get_size_limit(limits, num_limits, IPP_LIMIT_BUFFER, &l);
	अगर (!__size_limit_check(real_width, &l.h) ||
	    !__size_limit_check(buf->buf.height, &l.v))
		वापस -EINVAL;

	अगर (swap) अणु
		lv = &l.h;
		lh = &l.v;
	पूर्ण
	__get_size_limit(limits, num_limits, id, &l);
	अगर (!__size_limit_check(buf->rect.w, lh) ||
	    !__align_check(buf->rect.x, lh->align) ||
	    !__size_limit_check(buf->rect.h, lv) ||
	    !__align_check(buf->rect.y, lv->align))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल अंतरभूत bool __scale_limit_check(अचिन्हित पूर्णांक src, अचिन्हित पूर्णांक dst,
				       अचिन्हित पूर्णांक min, अचिन्हित पूर्णांक max)
अणु
	अगर ((max && (dst << 16) > src * max) ||
	    (min && (dst << 16) < src * min)) अणु
		DRM_DEBUG_DRIVER("Scale from %d to %d exceeds HW limits (ratio min %d.%05d, max %d.%05d)\n",
			 src, dst,
			 min >> 16, 100000 * (min & 0xffff) / (1 << 16),
			 max >> 16, 100000 * (max & 0xffff) / (1 << 16));
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक exynos_drm_ipp_check_scale_limits(
				काष्ठा drm_exynos_ipp_task_rect *src,
				काष्ठा drm_exynos_ipp_task_rect *dst,
				स्थिर काष्ठा drm_exynos_ipp_limit *limits,
				अचिन्हित पूर्णांक num_limits, bool swap)
अणु
	स्थिर काष्ठा drm_exynos_ipp_limit_val *lh, *lv;
	पूर्णांक dw, dh;

	क्रम (; num_limits; limits++, num_limits--)
		अगर ((limits->type & DRM_EXYNOS_IPP_LIMIT_TYPE_MASK) ==
		    DRM_EXYNOS_IPP_LIMIT_TYPE_SCALE)
			अवरोध;
	अगर (!num_limits)
		वापस 0;

	lh = (!swap) ? &limits->h : &limits->v;
	lv = (!swap) ? &limits->v : &limits->h;
	dw = (!swap) ? dst->w : dst->h;
	dh = (!swap) ? dst->h : dst->w;

	अगर (!__scale_limit_check(src->w, dw, lh->min, lh->max) ||
	    !__scale_limit_check(src->h, dh, lv->min, lv->max))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_drm_ipp_check_क्रमmat(काष्ठा exynos_drm_ipp_task *task,
				       काष्ठा exynos_drm_ipp_buffer *buf,
				       काष्ठा exynos_drm_ipp_buffer *src,
				       काष्ठा exynos_drm_ipp_buffer *dst,
				       bool rotate, bool swap)
अणु
	स्थिर काष्ठा exynos_drm_ipp_क्रमmats *fmt;
	पूर्णांक ret, i;

	fmt = __ipp_क्रमmat_get(task->ipp, buf->buf.fourcc, buf->buf.modअगरier,
			       buf == src ? DRM_EXYNOS_IPP_FORMAT_SOURCE :
					    DRM_EXYNOS_IPP_FORMAT_DESTINATION);
	अगर (!fmt) अणु
		DRM_DEV_DEBUG_DRIVER(task->dev,
				     "Task %pK: %s format not supported\n",
				     task, buf == src ? "src" : "dst");
		वापस -EINVAL;
	पूर्ण

	/* basic checks */
	अगर (buf->buf.width == 0 || buf->buf.height == 0)
		वापस -EINVAL;

	buf->क्रमmat = drm_क्रमmat_info(buf->buf.fourcc);
	क्रम (i = 0; i < buf->क्रमmat->num_planes; i++) अणु
		अचिन्हित पूर्णांक width = (i == 0) ? buf->buf.width :
			     DIV_ROUND_UP(buf->buf.width, buf->क्रमmat->hsub);

		अगर (buf->buf.pitch[i] == 0)
			buf->buf.pitch[i] = width * buf->क्रमmat->cpp[i];
		अगर (buf->buf.pitch[i] < width * buf->क्रमmat->cpp[i])
			वापस -EINVAL;
		अगर (!buf->buf.gem_id[i])
			वापस -ENOENT;
	पूर्ण

	/* pitch क्रम additional planes must match */
	अगर (buf->क्रमmat->num_planes > 2 &&
	    buf->buf.pitch[1] != buf->buf.pitch[2])
		वापस -EINVAL;

	/* check driver limits */
	ret = exynos_drm_ipp_check_size_limits(buf, fmt->limits,
					       fmt->num_limits,
					       rotate,
					       buf == dst ? swap : false);
	अगर (ret)
		वापस ret;
	ret = exynos_drm_ipp_check_scale_limits(&src->rect, &dst->rect,
						fmt->limits,
						fmt->num_limits, swap);
	वापस ret;
पूर्ण

अटल पूर्णांक exynos_drm_ipp_task_check(काष्ठा exynos_drm_ipp_task *task)
अणु
	काष्ठा exynos_drm_ipp *ipp = task->ipp;
	काष्ठा exynos_drm_ipp_buffer *src = &task->src, *dst = &task->dst;
	अचिन्हित पूर्णांक rotation = task->transक्रमm.rotation;
	पूर्णांक ret = 0;
	bool swap = drm_rotation_90_or_270(rotation);
	bool rotate = (rotation != DRM_MODE_ROTATE_0);
	bool scale = false;

	DRM_DEV_DEBUG_DRIVER(task->dev, "Checking task %pK\n", task);

	अगर (src->rect.w == अच_पूर्णांक_उच्च)
		src->rect.w = src->buf.width;
	अगर (src->rect.h == अच_पूर्णांक_उच्च)
		src->rect.h = src->buf.height;
	अगर (dst->rect.w == अच_पूर्णांक_उच्च)
		dst->rect.w = dst->buf.width;
	अगर (dst->rect.h == अच_पूर्णांक_उच्च)
		dst->rect.h = dst->buf.height;

	अगर (src->rect.x + src->rect.w > (src->buf.width) ||
	    src->rect.y + src->rect.h > (src->buf.height) ||
	    dst->rect.x + dst->rect.w > (dst->buf.width) ||
	    dst->rect.y + dst->rect.h > (dst->buf.height)) अणु
		DRM_DEV_DEBUG_DRIVER(task->dev,
				     "Task %pK: defined area is outside provided buffers\n",
				     task);
		वापस -EINVAL;
	पूर्ण

	अगर ((!swap && (src->rect.w != dst->rect.w ||
		       src->rect.h != dst->rect.h)) ||
	    (swap && (src->rect.w != dst->rect.h ||
		      src->rect.h != dst->rect.w)))
		scale = true;

	अगर ((!(ipp->capabilities & DRM_EXYNOS_IPP_CAP_CROP) &&
	     (src->rect.x || src->rect.y || dst->rect.x || dst->rect.y)) ||
	    (!(ipp->capabilities & DRM_EXYNOS_IPP_CAP_ROTATE) && rotate) ||
	    (!(ipp->capabilities & DRM_EXYNOS_IPP_CAP_SCALE) && scale) ||
	    (!(ipp->capabilities & DRM_EXYNOS_IPP_CAP_CONVERT) &&
	     src->buf.fourcc != dst->buf.fourcc)) अणु
		DRM_DEV_DEBUG_DRIVER(task->dev, "Task %pK: hw capabilities exceeded\n",
				     task);
		वापस -EINVAL;
	पूर्ण

	ret = exynos_drm_ipp_check_क्रमmat(task, src, src, dst, rotate, swap);
	अगर (ret)
		वापस ret;

	ret = exynos_drm_ipp_check_क्रमmat(task, dst, src, dst, false, swap);
	अगर (ret)
		वापस ret;

	DRM_DEV_DEBUG_DRIVER(ipp->dev, "Task %pK: all checks done.\n",
			     task);

	वापस ret;
पूर्ण

अटल पूर्णांक exynos_drm_ipp_task_setup_buffers(काष्ठा exynos_drm_ipp_task *task,
				     काष्ठा drm_file *filp)
अणु
	काष्ठा exynos_drm_ipp_buffer *src = &task->src, *dst = &task->dst;
	पूर्णांक ret = 0;

	DRM_DEV_DEBUG_DRIVER(task->dev, "Setting buffer for task %pK\n",
			     task);

	ret = exynos_drm_ipp_task_setup_buffer(src, filp);
	अगर (ret) अणु
		DRM_DEV_DEBUG_DRIVER(task->dev,
				     "Task %pK: src buffer setup failed\n",
				     task);
		वापस ret;
	पूर्ण
	ret = exynos_drm_ipp_task_setup_buffer(dst, filp);
	अगर (ret) अणु
		DRM_DEV_DEBUG_DRIVER(task->dev,
				     "Task %pK: dst buffer setup failed\n",
				     task);
		वापस ret;
	पूर्ण

	DRM_DEV_DEBUG_DRIVER(task->dev, "Task %pK: buffers prepared.\n",
			     task);

	वापस ret;
पूर्ण


अटल पूर्णांक exynos_drm_ipp_event_create(काष्ठा exynos_drm_ipp_task *task,
				 काष्ठा drm_file *file_priv, uपूर्णांक64_t user_data)
अणु
	काष्ठा drm_pending_exynos_ipp_event *e = शून्य;
	पूर्णांक ret;

	e = kzalloc(माप(*e), GFP_KERNEL);
	अगर (!e)
		वापस -ENOMEM;

	e->event.base.type = DRM_EXYNOS_IPP_EVENT;
	e->event.base.length = माप(e->event);
	e->event.user_data = user_data;

	ret = drm_event_reserve_init(task->ipp->drm_dev, file_priv, &e->base,
				     &e->event.base);
	अगर (ret)
		जाओ मुक्त;

	task->event = e;
	वापस 0;
मुक्त:
	kमुक्त(e);
	वापस ret;
पूर्ण

अटल व्योम exynos_drm_ipp_event_send(काष्ठा exynos_drm_ipp_task *task)
अणु
	काष्ठा बारpec64 now;

	kसमय_get_ts64(&now);
	task->event->event.tv_sec = now.tv_sec;
	task->event->event.tv_usec = now.tv_nsec / NSEC_PER_USEC;
	task->event->event.sequence = atomic_inc_वापस(&task->ipp->sequence);

	drm_send_event(task->ipp->drm_dev, &task->event->base);
पूर्ण

अटल पूर्णांक exynos_drm_ipp_task_cleanup(काष्ठा exynos_drm_ipp_task *task)
अणु
	पूर्णांक ret = task->ret;

	अगर (ret == 0 && task->event) अणु
		exynos_drm_ipp_event_send(task);
		/* ensure event won't be canceled on task मुक्त */
		task->event = शून्य;
	पूर्ण

	exynos_drm_ipp_task_मुक्त(task->ipp, task);
	वापस ret;
पूर्ण

अटल व्योम exynos_drm_ipp_cleanup_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा exynos_drm_ipp_task *task = container_of(work,
				      काष्ठा exynos_drm_ipp_task, cleanup_work);

	exynos_drm_ipp_task_cleanup(task);
पूर्ण

अटल व्योम exynos_drm_ipp_next_task(काष्ठा exynos_drm_ipp *ipp);

/**
 * exynos_drm_ipp_task_करोne - finish given task and set वापस code
 * @task: ipp task to finish
 * @ret: error code or 0 अगर operation has been perक्रमmed successfully
 */
व्योम exynos_drm_ipp_task_करोne(काष्ठा exynos_drm_ipp_task *task, पूर्णांक ret)
अणु
	काष्ठा exynos_drm_ipp *ipp = task->ipp;
	अचिन्हित दीर्घ flags;

	DRM_DEV_DEBUG_DRIVER(task->dev, "ipp: %d, task %pK done: %d\n",
			     ipp->id, task, ret);

	spin_lock_irqsave(&ipp->lock, flags);
	अगर (ipp->task == task)
		ipp->task = शून्य;
	task->flags |= DRM_EXYNOS_IPP_TASK_DONE;
	task->ret = ret;
	spin_unlock_irqrestore(&ipp->lock, flags);

	exynos_drm_ipp_next_task(ipp);
	wake_up(&ipp->करोne_wq);

	अगर (task->flags & DRM_EXYNOS_IPP_TASK_ASYNC) अणु
		INIT_WORK(&task->cleanup_work, exynos_drm_ipp_cleanup_work);
		schedule_work(&task->cleanup_work);
	पूर्ण
पूर्ण

अटल व्योम exynos_drm_ipp_next_task(काष्ठा exynos_drm_ipp *ipp)
अणु
	काष्ठा exynos_drm_ipp_task *task;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	DRM_DEV_DEBUG_DRIVER(ipp->dev, "ipp: %d, try to run new task\n",
			     ipp->id);

	spin_lock_irqsave(&ipp->lock, flags);

	अगर (ipp->task || list_empty(&ipp->toकरो_list)) अणु
		spin_unlock_irqrestore(&ipp->lock, flags);
		वापस;
	पूर्ण

	task = list_first_entry(&ipp->toकरो_list, काष्ठा exynos_drm_ipp_task,
				head);
	list_del_init(&task->head);
	ipp->task = task;

	spin_unlock_irqrestore(&ipp->lock, flags);

	DRM_DEV_DEBUG_DRIVER(ipp->dev,
			     "ipp: %d, selected task %pK to run\n", ipp->id,
			     task);

	ret = ipp->funcs->commit(ipp, task);
	अगर (ret)
		exynos_drm_ipp_task_करोne(task, ret);
पूर्ण

अटल व्योम exynos_drm_ipp_schedule_task(काष्ठा exynos_drm_ipp *ipp,
					 काष्ठा exynos_drm_ipp_task *task)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ipp->lock, flags);
	list_add(&task->head, &ipp->toकरो_list);
	spin_unlock_irqrestore(&ipp->lock, flags);

	exynos_drm_ipp_next_task(ipp);
पूर्ण

अटल व्योम exynos_drm_ipp_task_पात(काष्ठा exynos_drm_ipp *ipp,
				      काष्ठा exynos_drm_ipp_task *task)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ipp->lock, flags);
	अगर (task->flags & DRM_EXYNOS_IPP_TASK_DONE) अणु
		/* alपढ़ोy completed task */
		exynos_drm_ipp_task_cleanup(task);
	पूर्ण अन्यथा अगर (ipp->task != task) अणु
		/* task has not been scheduled क्रम execution yet */
		list_del_init(&task->head);
		exynos_drm_ipp_task_cleanup(task);
	पूर्ण अन्यथा अणु
		/*
		 * currently processed task, call पात() and perक्रमm
		 * cleanup with async worker
		 */
		task->flags |= DRM_EXYNOS_IPP_TASK_ASYNC;
		spin_unlock_irqrestore(&ipp->lock, flags);
		अगर (ipp->funcs->पात)
			ipp->funcs->पात(ipp, task);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&ipp->lock, flags);
पूर्ण

/**
 * exynos_drm_ipp_commit_ioctl - perक्रमm image processing operation
 * @dev: DRM device
 * @data: ioctl data
 * @file_priv: DRM file info
 *
 * Conकाष्ठा a ipp task from the set of properties provided from the user
 * and try to schedule it to framebuffer processor hardware.
 *
 * Called by the user via ioctl.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक exynos_drm_ipp_commit_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_exynos_ioctl_ipp_commit *arg = data;
	काष्ठा exynos_drm_ipp *ipp;
	काष्ठा exynos_drm_ipp_task *task;
	पूर्णांक ret = 0;

	अगर ((arg->flags & ~DRM_EXYNOS_IPP_FLAGS) || arg->reserved)
		वापस -EINVAL;

	/* can't test and expect an event at the same समय */
	अगर ((arg->flags & DRM_EXYNOS_IPP_FLAG_TEST_ONLY) &&
			(arg->flags & DRM_EXYNOS_IPP_FLAG_EVENT))
		वापस -EINVAL;

	ipp = __ipp_get(arg->ipp_id);
	अगर (!ipp)
		वापस -ENOENT;

	task = exynos_drm_ipp_task_alloc(ipp);
	अगर (!task)
		वापस -ENOMEM;

	ret = exynos_drm_ipp_task_set(task, arg);
	अगर (ret)
		जाओ मुक्त;

	ret = exynos_drm_ipp_task_check(task);
	अगर (ret)
		जाओ मुक्त;

	ret = exynos_drm_ipp_task_setup_buffers(task, file_priv);
	अगर (ret || arg->flags & DRM_EXYNOS_IPP_FLAG_TEST_ONLY)
		जाओ मुक्त;

	अगर (arg->flags & DRM_EXYNOS_IPP_FLAG_EVENT) अणु
		ret = exynos_drm_ipp_event_create(task, file_priv,
						 arg->user_data);
		अगर (ret)
			जाओ मुक्त;
	पूर्ण

	/*
	 * Queue task क्रम processing on the hardware. task object will be
	 * then मुक्तd after exynos_drm_ipp_task_करोne()
	 */
	अगर (arg->flags & DRM_EXYNOS_IPP_FLAG_NONBLOCK) अणु
		DRM_DEV_DEBUG_DRIVER(ipp->dev,
				     "ipp: %d, nonblocking processing task %pK\n",
				     ipp->id, task);

		task->flags |= DRM_EXYNOS_IPP_TASK_ASYNC;
		exynos_drm_ipp_schedule_task(task->ipp, task);
		ret = 0;
	पूर्ण अन्यथा अणु
		DRM_DEV_DEBUG_DRIVER(ipp->dev, "ipp: %d, processing task %pK\n",
				     ipp->id, task);
		exynos_drm_ipp_schedule_task(ipp, task);
		ret = रुको_event_पूर्णांकerruptible(ipp->करोne_wq,
					task->flags & DRM_EXYNOS_IPP_TASK_DONE);
		अगर (ret)
			exynos_drm_ipp_task_पात(ipp, task);
		अन्यथा
			ret = exynos_drm_ipp_task_cleanup(task);
	पूर्ण
	वापस ret;
मुक्त:
	exynos_drm_ipp_task_मुक्त(ipp, task);

	वापस ret;
पूर्ण
