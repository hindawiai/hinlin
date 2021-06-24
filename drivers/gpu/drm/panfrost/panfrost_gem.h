<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright 2019 Linaro, Ltd, Rob Herring <robh@kernel.org> */

#अगर_अघोषित __PANFROST_GEM_H__
#घोषणा __PANFROST_GEM_H__

#समावेश <drm/drm_gem_shmem_helper.h>
#समावेश <drm/drm_mm.h>

काष्ठा panfrost_mmu;

काष्ठा panfrost_gem_object अणु
	काष्ठा drm_gem_shmem_object base;
	काष्ठा sg_table *sgts;

	/*
	 * Use a list क्रम now. If searching a mapping ever becomes the
	 * bottleneck, we should consider using an RB-tree, or even better,
	 * let the core store drm_gem_object_mapping entries (where we
	 * could place driver specअगरic data) instead of drm_gem_object ones
	 * in its drm_file->object_idr table.
	 *
	 * काष्ठा drm_gem_object_mapping अणु
	 *	काष्ठा drm_gem_object *obj;
	 *	व्योम *driver_priv;
	 * पूर्ण;
	 */
	काष्ठा अणु
		काष्ठा list_head list;
		काष्ठा mutex lock;
	पूर्ण mappings;

	/*
	 * Count the number of jobs referencing this BO so we करोn't let the
	 * shrinker reclaim this object prematurely.
	 */
	atomic_t gpu_usecount;

	bool noexec		:1;
	bool is_heap		:1;
पूर्ण;

काष्ठा panfrost_gem_mapping अणु
	काष्ठा list_head node;
	काष्ठा kref refcount;
	काष्ठा panfrost_gem_object *obj;
	काष्ठा drm_mm_node mmnode;
	काष्ठा panfrost_mmu *mmu;
	bool active		:1;
पूर्ण;

अटल अंतरभूत
काष्ठा  panfrost_gem_object *to_panfrost_bo(काष्ठा drm_gem_object *obj)
अणु
	वापस container_of(to_drm_gem_shmem_obj(obj), काष्ठा panfrost_gem_object, base);
पूर्ण

अटल अंतरभूत काष्ठा panfrost_gem_mapping *
drm_mm_node_to_panfrost_mapping(काष्ठा drm_mm_node *node)
अणु
	वापस container_of(node, काष्ठा panfrost_gem_mapping, mmnode);
पूर्ण

काष्ठा drm_gem_object *panfrost_gem_create_object(काष्ठा drm_device *dev, माप_प्रकार size);

काष्ठा drm_gem_object *
panfrost_gem_prime_import_sg_table(काष्ठा drm_device *dev,
				   काष्ठा dma_buf_attachment *attach,
				   काष्ठा sg_table *sgt);

काष्ठा panfrost_gem_object *
panfrost_gem_create_with_handle(काष्ठा drm_file *file_priv,
				काष्ठा drm_device *dev, माप_प्रकार size,
				u32 flags,
				uपूर्णांक32_t *handle);

पूर्णांक panfrost_gem_खोलो(काष्ठा drm_gem_object *obj, काष्ठा drm_file *file_priv);
व्योम panfrost_gem_बंद(काष्ठा drm_gem_object *obj,
			काष्ठा drm_file *file_priv);

काष्ठा panfrost_gem_mapping *
panfrost_gem_mapping_get(काष्ठा panfrost_gem_object *bo,
			 काष्ठा panfrost_file_priv *priv);
व्योम panfrost_gem_mapping_put(काष्ठा panfrost_gem_mapping *mapping);
व्योम panfrost_gem_tearकरोwn_mappings_locked(काष्ठा panfrost_gem_object *bo);

व्योम panfrost_gem_shrinker_init(काष्ठा drm_device *dev);
व्योम panfrost_gem_shrinker_cleanup(काष्ठा drm_device *dev);

#पूर्ण_अगर /* __PANFROST_GEM_H__ */
