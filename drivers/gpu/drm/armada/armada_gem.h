<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Russell King
 */
#अगर_अघोषित ARMADA_GEM_H
#घोषणा ARMADA_GEM_H

#समावेश <drm/drm_gem.h>

/* GEM */
काष्ठा armada_gem_object अणु
	काष्ठा drm_gem_object	obj;
	व्योम			*addr;
	phys_addr_t		phys_addr;
	resource_माप_प्रकार		dev_addr;
	bool			mapped;
	काष्ठा drm_mm_node	*linear;	/* क्रम linear backed */
	काष्ठा page		*page;		/* क्रम page backed */
	काष्ठा sg_table		*sgt;		/* क्रम imported */
	व्योम			(*update)(व्योम *);
	व्योम			*update_data;
पूर्ण;

#घोषणा drm_to_armada_gem(o) container_of(o, काष्ठा armada_gem_object, obj)

व्योम armada_gem_मुक्त_object(काष्ठा drm_gem_object *);
पूर्णांक armada_gem_linear_back(काष्ठा drm_device *, काष्ठा armada_gem_object *);
व्योम *armada_gem_map_object(काष्ठा drm_device *, काष्ठा armada_gem_object *);
काष्ठा armada_gem_object *armada_gem_alloc_निजी_object(काष्ठा drm_device *,
	माप_प्रकार);
पूर्णांक armada_gem_dumb_create(काष्ठा drm_file *, काष्ठा drm_device *,
	काष्ठा drm_mode_create_dumb *);
काष्ठा dma_buf *armada_gem_prime_export(काष्ठा drm_gem_object *obj, पूर्णांक flags);
काष्ठा drm_gem_object *armada_gem_prime_import(काष्ठा drm_device *,
	काष्ठा dma_buf *);
पूर्णांक armada_gem_map_import(काष्ठा armada_gem_object *);

अटल अंतरभूत काष्ठा armada_gem_object *armada_gem_object_lookup(
	काष्ठा drm_file *dfile, अचिन्हित handle)
अणु
	काष्ठा drm_gem_object *obj = drm_gem_object_lookup(dfile, handle);

	वापस obj ? drm_to_armada_gem(obj) : शून्य;
पूर्ण
#पूर्ण_अगर
