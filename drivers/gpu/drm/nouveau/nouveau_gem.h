<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NOUVEAU_GEM_H__
#घोषणा __NOUVEAU_GEM_H__

#समावेश "nouveau_drv.h"
#समावेश "nouveau_bo.h"

बाह्य स्थिर काष्ठा drm_gem_object_funcs nouveau_gem_object_funcs;

अटल अंतरभूत काष्ठा nouveau_bo *
nouveau_gem_object(काष्ठा drm_gem_object *gem)
अणु
	वापस gem ? container_of(gem, काष्ठा nouveau_bo, bo.base) : शून्य;
पूर्ण

/* nouveau_gem.c */
बाह्य पूर्णांक nouveau_gem_new(काष्ठा nouveau_cli *, u64 size, पूर्णांक align,
			   uपूर्णांक32_t करोमुख्य, uपूर्णांक32_t tile_mode,
			   uपूर्णांक32_t tile_flags, काष्ठा nouveau_bo **);
बाह्य व्योम nouveau_gem_object_del(काष्ठा drm_gem_object *);
बाह्य पूर्णांक nouveau_gem_object_खोलो(काष्ठा drm_gem_object *, काष्ठा drm_file *);
बाह्य व्योम nouveau_gem_object_बंद(काष्ठा drm_gem_object *,
				     काष्ठा drm_file *);
बाह्य पूर्णांक nouveau_gem_ioctl_new(काष्ठा drm_device *, व्योम *,
				 काष्ठा drm_file *);
बाह्य पूर्णांक nouveau_gem_ioctl_pushbuf(काष्ठा drm_device *, व्योम *,
				     काष्ठा drm_file *);
बाह्य पूर्णांक nouveau_gem_ioctl_cpu_prep(काष्ठा drm_device *, व्योम *,
				      काष्ठा drm_file *);
बाह्य पूर्णांक nouveau_gem_ioctl_cpu_fini(काष्ठा drm_device *, व्योम *,
				      काष्ठा drm_file *);
बाह्य पूर्णांक nouveau_gem_ioctl_info(काष्ठा drm_device *, व्योम *,
				  काष्ठा drm_file *);

बाह्य पूर्णांक nouveau_gem_prime_pin(काष्ठा drm_gem_object *);
बाह्य व्योम nouveau_gem_prime_unpin(काष्ठा drm_gem_object *);
बाह्य काष्ठा sg_table *nouveau_gem_prime_get_sg_table(काष्ठा drm_gem_object *);
बाह्य काष्ठा drm_gem_object *nouveau_gem_prime_import_sg_table(
	काष्ठा drm_device *, काष्ठा dma_buf_attachment *, काष्ठा sg_table *);

#पूर्ण_अगर
