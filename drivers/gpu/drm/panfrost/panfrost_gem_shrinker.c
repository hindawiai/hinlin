<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2019 Arm Ltd.
 *
 * Based on msm_gem_मुक्तdreno.c:
 * Copyright (C) 2016 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/list.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_gem_shmem_helper.h>

#समावेश "panfrost_device.h"
#समावेश "panfrost_gem.h"
#समावेश "panfrost_mmu.h"

अटल अचिन्हित दीर्घ
panfrost_gem_shrinker_count(काष्ठा shrinker *shrinker, काष्ठा shrink_control *sc)
अणु
	काष्ठा panfrost_device *pfdev =
		container_of(shrinker, काष्ठा panfrost_device, shrinker);
	काष्ठा drm_gem_shmem_object *shmem;
	अचिन्हित दीर्घ count = 0;

	अगर (!mutex_trylock(&pfdev->shrinker_lock))
		वापस 0;

	list_क्रम_each_entry(shmem, &pfdev->shrinker_list, madv_list) अणु
		अगर (drm_gem_shmem_is_purgeable(shmem))
			count += shmem->base.size >> PAGE_SHIFT;
	पूर्ण

	mutex_unlock(&pfdev->shrinker_lock);

	वापस count;
पूर्ण

अटल bool panfrost_gem_purge(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);
	काष्ठा panfrost_gem_object *bo = to_panfrost_bo(obj);
	bool ret = false;

	अगर (atomic_पढ़ो(&bo->gpu_usecount))
		वापस false;

	अगर (!mutex_trylock(&bo->mappings.lock))
		वापस false;

	अगर (!mutex_trylock(&shmem->pages_lock))
		जाओ unlock_mappings;

	panfrost_gem_tearकरोwn_mappings_locked(bo);
	drm_gem_shmem_purge_locked(obj);
	ret = true;

	mutex_unlock(&shmem->pages_lock);

unlock_mappings:
	mutex_unlock(&bo->mappings.lock);
	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ
panfrost_gem_shrinker_scan(काष्ठा shrinker *shrinker, काष्ठा shrink_control *sc)
अणु
	काष्ठा panfrost_device *pfdev =
		container_of(shrinker, काष्ठा panfrost_device, shrinker);
	काष्ठा drm_gem_shmem_object *shmem, *पंचांगp;
	अचिन्हित दीर्घ मुक्तd = 0;

	अगर (!mutex_trylock(&pfdev->shrinker_lock))
		वापस SHRINK_STOP;

	list_क्रम_each_entry_safe(shmem, पंचांगp, &pfdev->shrinker_list, madv_list) अणु
		अगर (मुक्तd >= sc->nr_to_scan)
			अवरोध;
		अगर (drm_gem_shmem_is_purgeable(shmem) &&
		    panfrost_gem_purge(&shmem->base)) अणु
			मुक्तd += shmem->base.size >> PAGE_SHIFT;
			list_del_init(&shmem->madv_list);
		पूर्ण
	पूर्ण

	mutex_unlock(&pfdev->shrinker_lock);

	अगर (मुक्तd > 0)
		pr_info_ratelimited("Purging %lu bytes\n", मुक्तd << PAGE_SHIFT);

	वापस मुक्तd;
पूर्ण

/**
 * panfrost_gem_shrinker_init - Initialize panfrost shrinker
 * @dev: DRM device
 *
 * This function रेजिस्टरs and sets up the panfrost shrinker.
 */
व्योम panfrost_gem_shrinker_init(काष्ठा drm_device *dev)
अणु
	काष्ठा panfrost_device *pfdev = dev->dev_निजी;
	pfdev->shrinker.count_objects = panfrost_gem_shrinker_count;
	pfdev->shrinker.scan_objects = panfrost_gem_shrinker_scan;
	pfdev->shrinker.seeks = DEFAULT_SEEKS;
	WARN_ON(रेजिस्टर_shrinker(&pfdev->shrinker));
पूर्ण

/**
 * panfrost_gem_shrinker_cleanup - Clean up panfrost shrinker
 * @dev: DRM device
 *
 * This function unरेजिस्टरs the panfrost shrinker.
 */
व्योम panfrost_gem_shrinker_cleanup(काष्ठा drm_device *dev)
अणु
	काष्ठा panfrost_device *pfdev = dev->dev_निजी;

	अगर (pfdev->shrinker.nr_deferred) अणु
		unरेजिस्टर_shrinker(&pfdev->shrinker);
	पूर्ण
पूर्ण
