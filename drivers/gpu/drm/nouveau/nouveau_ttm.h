<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NOUVEAU_TTM_H__
#घोषणा __NOUVEAU_TTM_H__

अटल अंतरभूत काष्ठा nouveau_drm *
nouveau_bdev(काष्ठा tपंचांग_device *bd)
अणु
	वापस container_of(bd, काष्ठा nouveau_drm, tपंचांग.bdev);
पूर्ण

बाह्य स्थिर काष्ठा tपंचांग_resource_manager_func nouveau_vram_manager;
बाह्य स्थिर काष्ठा tपंचांग_resource_manager_func nouveau_gart_manager;
बाह्य स्थिर काष्ठा tपंचांग_resource_manager_func nv04_gart_manager;

काष्ठा tपंचांग_tt *nouveau_sgdma_create_tपंचांग(काष्ठा tपंचांग_buffer_object *bo,
					u32 page_flags);

पूर्णांक  nouveau_tपंचांग_init(काष्ठा nouveau_drm *drm);
व्योम nouveau_tपंचांग_fini(काष्ठा nouveau_drm *drm);
पूर्णांक  nouveau_tपंचांग_mmap(काष्ठा file *, काष्ठा vm_area_काष्ठा *);

पूर्णांक  nouveau_tपंचांग_global_init(काष्ठा nouveau_drm *);
व्योम nouveau_tपंचांग_global_release(काष्ठा nouveau_drm *);

पूर्णांक nouveau_sgdma_bind(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग, काष्ठा tपंचांग_resource *reg);
व्योम nouveau_sgdma_unbind(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग);
व्योम nouveau_sgdma_destroy(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग);
#पूर्ण_अगर
