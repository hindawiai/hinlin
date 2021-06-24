<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NOUVEAU_BO_H__
#घोषणा __NOUVEAU_BO_H__
#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>
#समावेश <drm/drm_gem.h>

काष्ठा nouveau_channel;
काष्ठा nouveau_cli;
काष्ठा nouveau_drm;
काष्ठा nouveau_fence;

काष्ठा nouveau_bo अणु
	काष्ठा tपंचांग_buffer_object bo;
	काष्ठा tपंचांग_placement placement;
	u32 valid_करोमुख्यs;
	काष्ठा tपंचांग_place placements[3];
	काष्ठा tपंचांग_place busy_placements[3];
	bool क्रमce_coherent;
	काष्ठा tपंचांग_bo_kmap_obj kmap;
	काष्ठा list_head head;
	काष्ठा list_head io_reserve_lru;

	/* रक्षित by tपंचांग_bo_reserve() */
	काष्ठा drm_file *reserved_by;
	काष्ठा list_head entry;
	पूर्णांक pbbo_index;
	bool validate_mapped;

	/* GPU address space is independent of CPU word size */
	uपूर्णांक64_t offset;

	काष्ठा list_head vma_list;

	अचिन्हित contig:1;
	अचिन्हित page:5;
	अचिन्हित kind:8;
	अचिन्हित comp:3;
	अचिन्हित zeta:3;
	अचिन्हित mode;

	काष्ठा nouveau_drm_tile *tile;
पूर्ण;

अटल अंतरभूत काष्ठा nouveau_bo *
nouveau_bo(काष्ठा tपंचांग_buffer_object *bo)
अणु
	वापस container_of(bo, काष्ठा nouveau_bo, bo);
पूर्ण

अटल अंतरभूत पूर्णांक
nouveau_bo_ref(काष्ठा nouveau_bo *ref, काष्ठा nouveau_bo **pnvbo)
अणु
	काष्ठा nouveau_bo *prev;

	अगर (!pnvbo)
		वापस -EINVAL;
	prev = *pnvbo;

	अगर (ref) अणु
		tपंचांग_bo_get(&ref->bo);
		*pnvbo = nouveau_bo(&ref->bo);
	पूर्ण अन्यथा अणु
		*pnvbo = शून्य;
	पूर्ण
	अगर (prev)
		tपंचांग_bo_put(&prev->bo);

	वापस 0;
पूर्ण

बाह्य काष्ठा tपंचांग_device_funcs nouveau_bo_driver;

व्योम nouveau_bo_move_init(काष्ठा nouveau_drm *);
काष्ठा nouveau_bo *nouveau_bo_alloc(काष्ठा nouveau_cli *, u64 *size, पूर्णांक *align,
				    u32 करोमुख्य, u32 tile_mode, u32 tile_flags);
पूर्णांक  nouveau_bo_init(काष्ठा nouveau_bo *, u64 size, पूर्णांक align, u32 करोमुख्य,
		     काष्ठा sg_table *sg, काष्ठा dma_resv *robj);
पूर्णांक  nouveau_bo_new(काष्ठा nouveau_cli *, u64 size, पूर्णांक align, u32 करोमुख्य,
		    u32 tile_mode, u32 tile_flags, काष्ठा sg_table *sg,
		    काष्ठा dma_resv *robj,
		    काष्ठा nouveau_bo **);
पूर्णांक  nouveau_bo_pin(काष्ठा nouveau_bo *, u32 flags, bool contig);
पूर्णांक  nouveau_bo_unpin(काष्ठा nouveau_bo *);
पूर्णांक  nouveau_bo_map(काष्ठा nouveau_bo *);
व्योम nouveau_bo_unmap(काष्ठा nouveau_bo *);
व्योम nouveau_bo_placement_set(काष्ठा nouveau_bo *, u32 type, u32 busy);
व्योम nouveau_bo_wr16(काष्ठा nouveau_bo *, अचिन्हित index, u16 val);
u32  nouveau_bo_rd32(काष्ठा nouveau_bo *, अचिन्हित index);
व्योम nouveau_bo_wr32(काष्ठा nouveau_bo *, अचिन्हित index, u32 val);
vm_fault_t nouveau_tपंचांग_fault_reserve_notअगरy(काष्ठा tपंचांग_buffer_object *bo);
व्योम nouveau_bo_fence(काष्ठा nouveau_bo *, काष्ठा nouveau_fence *, bool exclusive);
पूर्णांक  nouveau_bo_validate(काष्ठा nouveau_bo *, bool पूर्णांकerruptible,
			 bool no_रुको_gpu);
व्योम nouveau_bo_sync_क्रम_device(काष्ठा nouveau_bo *nvbo);
व्योम nouveau_bo_sync_क्रम_cpu(काष्ठा nouveau_bo *nvbo);
व्योम nouveau_bo_add_io_reserve_lru(काष्ठा tपंचांग_buffer_object *bo);
व्योम nouveau_bo_del_io_reserve_lru(काष्ठा tपंचांग_buffer_object *bo);

/* TODO: submit equivalent to TTM generic API upstream? */
अटल अंतरभूत व्योम __iomem *
nvbo_kmap_obj_ioभव(काष्ठा nouveau_bo *nvbo)
अणु
	bool is_iomem;
	व्योम __iomem *ioptr = (व्योम __क्रमce __iomem *)tपंचांग_kmap_obj_भव(
						&nvbo->kmap, &is_iomem);
	WARN_ON_ONCE(ioptr && !is_iomem);
	वापस ioptr;
पूर्ण

अटल अंतरभूत व्योम
nouveau_bo_unmap_unpin_unref(काष्ठा nouveau_bo **pnvbo)
अणु
	अगर (*pnvbo) अणु
		nouveau_bo_unmap(*pnvbo);
		nouveau_bo_unpin(*pnvbo);
		nouveau_bo_ref(शून्य, pnvbo);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
nouveau_bo_new_pin_map(काष्ठा nouveau_cli *cli, u64 size, पूर्णांक align, u32 करोमुख्य,
		       काष्ठा nouveau_bo **pnvbo)
अणु
	पूर्णांक ret = nouveau_bo_new(cli, size, align, करोमुख्य,
				 0, 0, शून्य, शून्य, pnvbo);
	अगर (ret == 0) अणु
		ret = nouveau_bo_pin(*pnvbo, करोमुख्य, true);
		अगर (ret == 0) अणु
			ret = nouveau_bo_map(*pnvbo);
			अगर (ret == 0)
				वापस ret;
			nouveau_bo_unpin(*pnvbo);
		पूर्ण
		nouveau_bo_ref(शून्य, pnvbo);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक nv04_bo_move_init(काष्ठा nouveau_channel *, u32);
पूर्णांक nv04_bo_move_m2mf(काष्ठा nouveau_channel *, काष्ठा tपंचांग_buffer_object *,
		      काष्ठा tपंचांग_resource *, काष्ठा tपंचांग_resource *);

पूर्णांक nv50_bo_move_init(काष्ठा nouveau_channel *, u32);
पूर्णांक nv50_bo_move_m2mf(काष्ठा nouveau_channel *, काष्ठा tपंचांग_buffer_object *,
		      काष्ठा tपंचांग_resource *, काष्ठा tपंचांग_resource *);

पूर्णांक nv84_bo_move_exec(काष्ठा nouveau_channel *, काष्ठा tपंचांग_buffer_object *,
		      काष्ठा tपंचांग_resource *, काष्ठा tपंचांग_resource *);

पूर्णांक nva3_bo_move_copy(काष्ठा nouveau_channel *, काष्ठा tपंचांग_buffer_object *,
		      काष्ठा tपंचांग_resource *, काष्ठा tपंचांग_resource *);

पूर्णांक nvc0_bo_move_init(काष्ठा nouveau_channel *, u32);
पूर्णांक nvc0_bo_move_m2mf(काष्ठा nouveau_channel *, काष्ठा tपंचांग_buffer_object *,
		      काष्ठा tपंचांग_resource *, काष्ठा tपंचांग_resource *);

पूर्णांक nvc0_bo_move_copy(काष्ठा nouveau_channel *, काष्ठा tपंचांग_buffer_object *,
		      काष्ठा tपंचांग_resource *, काष्ठा tपंचांग_resource *);

पूर्णांक nve0_bo_move_init(काष्ठा nouveau_channel *, u32);
पूर्णांक nve0_bo_move_copy(काष्ठा nouveau_channel *, काष्ठा tपंचांग_buffer_object *,
		      काष्ठा tपंचांग_resource *, काष्ठा tपंचांग_resource *);

#घोषणा NVBO_WR32_(b,o,dr,f) nouveau_bo_wr32((b), (o)/4 + (dr), (f))
#घोषणा NVBO_RD32_(b,o,dr)   nouveau_bo_rd32((b), (o)/4 + (dr))
#घोषणा NVBO_RD32(A...) DRF_RD(NVBO_RD32_,                  ##A)
#घोषणा NVBO_RV32(A...) DRF_RV(NVBO_RD32_,                  ##A)
#घोषणा NVBO_TV32(A...) DRF_TV(NVBO_RD32_,                  ##A)
#घोषणा NVBO_TD32(A...) DRF_TD(NVBO_RD32_,                  ##A)
#घोषणा NVBO_WR32(A...) DRF_WR(            NVBO_WR32_,      ##A)
#घोषणा NVBO_WV32(A...) DRF_WV(            NVBO_WR32_,      ##A)
#घोषणा NVBO_WD32(A...) DRF_WD(            NVBO_WR32_,      ##A)
#घोषणा NVBO_MR32(A...) DRF_MR(NVBO_RD32_, NVBO_WR32_, u32, ##A)
#घोषणा NVBO_MV32(A...) DRF_MV(NVBO_RD32_, NVBO_WR32_, u32, ##A)
#घोषणा NVBO_MD32(A...) DRF_MD(NVBO_RD32_, NVBO_WR32_, u32, ##A)
#पूर्ण_अगर
