<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 Intel
 *
 * Based on drivers/base/devres.c
 */

#समावेश <drm/drm_managed.h>

#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_internal.h"

/**
 * DOC: managed resources
 *
 * Inspired by काष्ठा &device managed resources, but tied to the lअगरeसमय of
 * काष्ठा &drm_device, which can outlive the underlying physical device, usually
 * when userspace has some खोलो files and other handles to resources still खोलो.
 *
 * Release actions can be added with drmm_add_action(), memory allocations can
 * be करोne directly with drmm_kदो_स्मृति() and the related functions. Everything
 * will be released on the final drm_dev_put() in reverse order of how the
 * release actions have been added and memory has been allocated since driver
 * loading started with devm_drm_dev_alloc().
 *
 * Note that release actions and managed memory can also be added and हटाओd
 * during the lअगरeसमय of the driver, all the functions are fully concurrent
 * safe. But it is recommended to use managed resources only क्रम resources that
 * change rarely, अगर ever, during the lअगरeसमय of the &drm_device instance.
 */

काष्ठा drmres_node अणु
	काष्ठा list_head	entry;
	drmres_release_t	release;
	स्थिर अक्षर		*name;
	माप_प्रकार			size;
पूर्ण;

काष्ठा drmres अणु
	काष्ठा drmres_node		node;
	/*
	 * Some archs want to perक्रमm DMA पूर्णांकo kदो_स्मृति caches
	 * and need a guaranteed alignment larger than
	 * the alignment of a 64-bit पूर्णांकeger.
	 * Thus we use ARCH_KMALLOC_MINALIGN here and get exactly the same
	 * buffer alignment as अगर it was allocated by plain kदो_स्मृति().
	 */
	u8 __aligned(ARCH_KMALLOC_MINALIGN) data[];
पूर्ण;

अटल व्योम मुक्त_dr(काष्ठा drmres *dr)
अणु
	kमुक्त_स्थिर(dr->node.name);
	kमुक्त(dr);
पूर्ण

व्योम drm_managed_release(काष्ठा drm_device *dev)
अणु
	काष्ठा drmres *dr, *पंचांगp;

	drm_dbg_drmres(dev, "drmres release begin\n");
	list_क्रम_each_entry_safe(dr, पंचांगp, &dev->managed.resources, node.entry) अणु
		drm_dbg_drmres(dev, "REL %p %s (%zu bytes)\n",
			       dr, dr->node.name, dr->node.size);

		अगर (dr->node.release)
			dr->node.release(dev, dr->node.size ? *(व्योम **)&dr->data : शून्य);

		list_del(&dr->node.entry);
		मुक्त_dr(dr);
	पूर्ण
	drm_dbg_drmres(dev, "drmres release end\n");
पूर्ण

/*
 * Always अंतरभूत so that kदो_स्मृति_track_caller tracks the actual पूर्णांकeresting
 * caller outside of drm_managed.c.
 */
अटल __always_अंतरभूत काष्ठा drmres * alloc_dr(drmres_release_t release,
						माप_प्रकार size, gfp_t gfp, पूर्णांक nid)
अणु
	माप_प्रकार tot_size;
	काष्ठा drmres *dr;

	/* We must catch any near-SIZE_MAX हालs that could overflow. */
	अगर (unlikely(check_add_overflow(माप(*dr), size, &tot_size)))
		वापस शून्य;

	dr = kदो_स्मृति_node_track_caller(tot_size, gfp, nid);
	अगर (unlikely(!dr))
		वापस शून्य;

	स_रखो(dr, 0, दुरत्व(काष्ठा drmres, data));

	INIT_LIST_HEAD(&dr->node.entry);
	dr->node.release = release;
	dr->node.size = size;

	वापस dr;
पूर्ण

अटल व्योम del_dr(काष्ठा drm_device *dev, काष्ठा drmres *dr)
अणु
	list_del_init(&dr->node.entry);

	drm_dbg_drmres(dev, "DEL %p %s (%lu bytes)\n",
		       dr, dr->node.name, (अचिन्हित दीर्घ) dr->node.size);
पूर्ण

अटल व्योम add_dr(काष्ठा drm_device *dev, काष्ठा drmres *dr)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->managed.lock, flags);
	list_add(&dr->node.entry, &dev->managed.resources);
	spin_unlock_irqrestore(&dev->managed.lock, flags);

	drm_dbg_drmres(dev, "ADD %p %s (%lu bytes)\n",
		       dr, dr->node.name, (अचिन्हित दीर्घ) dr->node.size);
पूर्ण

व्योम drmm_add_final_kमुक्त(काष्ठा drm_device *dev, व्योम *container)
अणु
	WARN_ON(dev->managed.final_kमुक्त);
	WARN_ON(dev < (काष्ठा drm_device *) container);
	WARN_ON(dev + 1 > (काष्ठा drm_device *) (container + ksize(container)));
	dev->managed.final_kमुक्त = container;
पूर्ण

पूर्णांक __drmm_add_action(काष्ठा drm_device *dev,
		      drmres_release_t action,
		      व्योम *data, स्थिर अक्षर *name)
अणु
	काष्ठा drmres *dr;
	व्योम **व्योम_ptr;

	dr = alloc_dr(action, data ? माप(व्योम*) : 0,
		      GFP_KERNEL | __GFP_ZERO,
		      dev_to_node(dev->dev));
	अगर (!dr) अणु
		drm_dbg_drmres(dev, "failed to add action %s for %p\n",
			       name, data);
		वापस -ENOMEM;
	पूर्ण

	dr->node.name = kstrdup_स्थिर(name, GFP_KERNEL);
	अगर (data) अणु
		व्योम_ptr = (व्योम **)&dr->data;
		*व्योम_ptr = data;
	पूर्ण

	add_dr(dev, dr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__drmm_add_action);

पूर्णांक __drmm_add_action_or_reset(काष्ठा drm_device *dev,
			       drmres_release_t action,
			       व्योम *data, स्थिर अक्षर *name)
अणु
	पूर्णांक ret;

	ret = __drmm_add_action(dev, action, data, name);
	अगर (ret)
		action(dev, data);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(__drmm_add_action_or_reset);

/**
 * drmm_kदो_स्मृति - &drm_device managed kदो_स्मृति()
 * @dev: DRM device
 * @size: size of the memory allocation
 * @gfp: GFP allocation flags
 *
 * This is a &drm_device managed version of kदो_स्मृति(). The allocated memory is
 * स्वतःmatically मुक्तd on the final drm_dev_put(). Memory can also be मुक्तd
 * beक्रमe the final drm_dev_put() by calling drmm_kमुक्त().
 */
व्योम *drmm_kदो_स्मृति(काष्ठा drm_device *dev, माप_प्रकार size, gfp_t gfp)
अणु
	काष्ठा drmres *dr;

	dr = alloc_dr(शून्य, size, gfp, dev_to_node(dev->dev));
	अगर (!dr) अणु
		drm_dbg_drmres(dev, "failed to allocate %zu bytes, %u flags\n",
			       size, gfp);
		वापस शून्य;
	पूर्ण
	dr->node.name = kstrdup_स्थिर("kmalloc", GFP_KERNEL);

	add_dr(dev, dr);

	वापस dr->data;
पूर्ण
EXPORT_SYMBOL(drmm_kदो_स्मृति);

/**
 * drmm_kstrdup - &drm_device managed kstrdup()
 * @dev: DRM device
 * @s: 0-terminated string to be duplicated
 * @gfp: GFP allocation flags
 *
 * This is a &drm_device managed version of kstrdup(). The allocated memory is
 * स्वतःmatically मुक्तd on the final drm_dev_put() and works exactly like a
 * memory allocation obtained by drmm_kदो_स्मृति().
 */
अक्षर *drmm_kstrdup(काष्ठा drm_device *dev, स्थिर अक्षर *s, gfp_t gfp)
अणु
	माप_प्रकार size;
	अक्षर *buf;

	अगर (!s)
		वापस शून्य;

	size = म_माप(s) + 1;
	buf = drmm_kदो_स्मृति(dev, size, gfp);
	अगर (buf)
		स_नकल(buf, s, size);
	वापस buf;
पूर्ण
EXPORT_SYMBOL_GPL(drmm_kstrdup);

/**
 * drmm_kमुक्त - &drm_device managed kमुक्त()
 * @dev: DRM device
 * @data: memory allocation to be मुक्तd
 *
 * This is a &drm_device managed version of kमुक्त() which can be used to
 * release memory allocated through drmm_kदो_स्मृति() or any of its related
 * functions beक्रमe the final drm_dev_put() of @dev.
 */
व्योम drmm_kमुक्त(काष्ठा drm_device *dev, व्योम *data)
अणु
	काष्ठा drmres *dr_match = शून्य, *dr;
	अचिन्हित दीर्घ flags;

	अगर (!data)
		वापस;

	spin_lock_irqsave(&dev->managed.lock, flags);
	list_क्रम_each_entry(dr, &dev->managed.resources, node.entry) अणु
		अगर (dr->data == data) अणु
			dr_match = dr;
			del_dr(dev, dr_match);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dev->managed.lock, flags);

	अगर (WARN_ON(!dr_match))
		वापस;

	मुक्त_dr(dr_match);
पूर्ण
EXPORT_SYMBOL(drmm_kमुक्त);
