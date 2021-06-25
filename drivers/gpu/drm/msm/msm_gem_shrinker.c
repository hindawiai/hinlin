<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश "msm_drv.h"
#समावेश "msm_gem.h"
#समावेश "msm_gpu.h"
#समावेश "msm_gpu_trace.h"

/* Default disabled क्रम now until it has some more testing on the dअगरferent
 * iommu combinations that can be paired with the driver:
 */
bool enable_eviction = false;
MODULE_PARM_DESC(enable_eviction, "Enable swappable GEM buffers");
module_param(enable_eviction, bool, 0600);

अटल bool can_swap(व्योम)
अणु
	वापस enable_eviction && get_nr_swap_pages() > 0;
पूर्ण

अटल अचिन्हित दीर्घ
msm_gem_shrinker_count(काष्ठा shrinker *shrinker, काष्ठा shrink_control *sc)
अणु
	काष्ठा msm_drm_निजी *priv =
		container_of(shrinker, काष्ठा msm_drm_निजी, shrinker);
	अचिन्हित count = priv->shrinkable_count;

	अगर (can_swap())
		count += priv->evictable_count;

	वापस count;
पूर्ण

अटल bool
purge(काष्ठा msm_gem_object *msm_obj)
अणु
	अगर (!is_purgeable(msm_obj))
		वापस false;

	/*
	 * This will move the obj out of still_in_list to
	 * the purged list
	 */
	msm_gem_purge(&msm_obj->base);

	वापस true;
पूर्ण

अटल bool
evict(काष्ठा msm_gem_object *msm_obj)
अणु
	अगर (is_unevictable(msm_obj))
		वापस false;

	msm_gem_evict(&msm_obj->base);

	वापस true;
पूर्ण

अटल अचिन्हित दीर्घ
scan(काष्ठा msm_drm_निजी *priv, अचिन्हित nr_to_scan, काष्ठा list_head *list,
		bool (*shrink)(काष्ठा msm_gem_object *msm_obj))
अणु
	अचिन्हित मुक्तd = 0;
	काष्ठा list_head still_in_list;

	INIT_LIST_HEAD(&still_in_list);

	mutex_lock(&priv->mm_lock);

	जबतक (मुक्तd < nr_to_scan) अणु
		काष्ठा msm_gem_object *msm_obj = list_first_entry_or_null(
				list, typeof(*msm_obj), mm_list);

		अगर (!msm_obj)
			अवरोध;

		list_move_tail(&msm_obj->mm_list, &still_in_list);

		/*
		 * If it is in the process of being मुक्तd, msm_gem_मुक्त_object
		 * can be blocked on mm_lock रुकोing to हटाओ it.  So just
		 * skip it.
		 */
		अगर (!kref_get_unless_zero(&msm_obj->base.refcount))
			जारी;

		/*
		 * Now that we own a reference, we can drop mm_lock क्रम the
		 * rest of the loop body, to reduce contention with the
		 * retire_submit path (which could make more objects purgeable)
		 */

		mutex_unlock(&priv->mm_lock);

		/*
		 * Note that this still needs to be trylock, since we can
		 * hit shrinker in response to trying to get backing pages
		 * क्रम this obj (ie. जबतक it's lock is alपढ़ोy held)
		 */
		अगर (!msm_gem_trylock(&msm_obj->base))
			जाओ tail;

		अगर (shrink(msm_obj))
			मुक्तd += msm_obj->base.size >> PAGE_SHIFT;

		msm_gem_unlock(&msm_obj->base);

tail:
		drm_gem_object_put(&msm_obj->base);
		mutex_lock(&priv->mm_lock);
	पूर्ण

	list_splice_tail(&still_in_list, list);
	mutex_unlock(&priv->mm_lock);

	वापस मुक्तd;
पूर्ण

अटल अचिन्हित दीर्घ
msm_gem_shrinker_scan(काष्ठा shrinker *shrinker, काष्ठा shrink_control *sc)
अणु
	काष्ठा msm_drm_निजी *priv =
		container_of(shrinker, काष्ठा msm_drm_निजी, shrinker);
	अचिन्हित दीर्घ मुक्तd;

	मुक्तd = scan(priv, sc->nr_to_scan, &priv->inactive_करोntneed, purge);

	अगर (मुक्तd > 0)
		trace_msm_gem_purge(मुक्तd << PAGE_SHIFT);

	अगर (can_swap() && मुक्तd < sc->nr_to_scan) अणु
		पूर्णांक evicted = scan(priv, sc->nr_to_scan - मुक्तd,
				&priv->inactive_willneed, evict);

		अगर (evicted > 0)
			trace_msm_gem_evict(evicted << PAGE_SHIFT);

		मुक्तd += evicted;
	पूर्ण

	वापस (मुक्तd > 0) ? मुक्तd : SHRINK_STOP;
पूर्ण

/* since we करोn't know any better, lets bail after a few
 * and अगर necessary the shrinker will be invoked again.
 * Seems better than unmapping *everything*
 */
अटल स्थिर पूर्णांक vmap_shrink_limit = 15;

अटल bool
vmap_shrink(काष्ठा msm_gem_object *msm_obj)
अणु
	अगर (!is_vunmapable(msm_obj))
		वापस false;

	msm_gem_vunmap(&msm_obj->base);

	वापस true;
पूर्ण

अटल पूर्णांक
msm_gem_shrinker_vmap(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा msm_drm_निजी *priv =
		container_of(nb, काष्ठा msm_drm_निजी, vmap_notअगरier);
	काष्ठा list_head *mm_lists[] = अणु
		&priv->inactive_करोntneed,
		&priv->inactive_willneed,
		priv->gpu ? &priv->gpu->active_list : शून्य,
		शून्य,
	पूर्ण;
	अचिन्हित idx, unmapped = 0;

	क्रम (idx = 0; mm_lists[idx] && unmapped < vmap_shrink_limit; idx++) अणु
		unmapped += scan(priv, vmap_shrink_limit - unmapped,
				mm_lists[idx], vmap_shrink);
	पूर्ण

	*(अचिन्हित दीर्घ *)ptr += unmapped;

	अगर (unmapped > 0)
		trace_msm_gem_purge_vmaps(unmapped);

	वापस NOTIFY_DONE;
पूर्ण

/**
 * msm_gem_shrinker_init - Initialize msm shrinker
 * @dev: drm device
 *
 * This function रेजिस्टरs and sets up the msm shrinker.
 */
व्योम msm_gem_shrinker_init(काष्ठा drm_device *dev)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	priv->shrinker.count_objects = msm_gem_shrinker_count;
	priv->shrinker.scan_objects = msm_gem_shrinker_scan;
	priv->shrinker.seeks = DEFAULT_SEEKS;
	WARN_ON(रेजिस्टर_shrinker(&priv->shrinker));

	priv->vmap_notअगरier.notअगरier_call = msm_gem_shrinker_vmap;
	WARN_ON(रेजिस्टर_vmap_purge_notअगरier(&priv->vmap_notअगरier));
पूर्ण

/**
 * msm_gem_shrinker_cleanup - Clean up msm shrinker
 * @dev: drm device
 *
 * This function unरेजिस्टरs the msm shrinker.
 */
व्योम msm_gem_shrinker_cleanup(काष्ठा drm_device *dev)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;

	अगर (priv->shrinker.nr_deferred) अणु
		WARN_ON(unरेजिस्टर_vmap_purge_notअगरier(&priv->vmap_notअगरier));
		unरेजिस्टर_shrinker(&priv->shrinker);
	पूर्ण
पूर्ण
