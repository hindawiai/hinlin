<शैली गुरु>
#अगर_अघोषित __NVKM_VMM_H__
#घोषणा __NVKM_VMM_H__
#समावेश "priv.h"
#समावेश <core/memory.h>
क्रमागत nvkm_memory_target;

काष्ठा nvkm_vmm_pt अणु
	/* Some GPUs have a mapping level with a dual page tables to
	 * support large and small pages in the same address-range.
	 *
	 * We track the state of both page tables in one place, which
	 * is why there's multiple PT poपूर्णांकers/refcounts here.
	 */
	काष्ठा nvkm_mmu_pt *pt[2];
	u32 refs[2];

	/* Page size handled by this PT.
	 *
	 * Tesla backend needs to know this when writinge PDEs,
	 * otherwise unnecessary.
	 */
	u8 page;

	/* Entire page table sparse.
	 *
	 * Used to propagate sparseness to child page tables.
	 */
	bool sparse:1;

	/* Tracking क्रम page directories.
	 *
	 * The array is indexed by PDE, and will either poपूर्णांक to the
	 * child page table, or indicate the PDE is marked as sparse.
	 **/
#घोषणा NVKM_VMM_PDE_INVALID(pde) IS_ERR_OR_शून्य(pde)
#घोषणा NVKM_VMM_PDE_SPARSED(pde) IS_ERR(pde)
#घोषणा NVKM_VMM_PDE_SPARSE       ERR_PTR(-EBUSY)
	काष्ठा nvkm_vmm_pt **pde;

	/* Tracking क्रम dual page tables.
	 *
	 * There's one entry क्रम each LPTE, keeping track of whether
	 * there are valid SPTEs in the same address-range.
	 *
	 * This inक्रमmation is used to manage LPTE state transitions.
	 */
#घोषणा NVKM_VMM_PTE_SPARSE 0x80
#घोषणा NVKM_VMM_PTE_VALID  0x40
#घोषणा NVKM_VMM_PTE_SPTES  0x3f
	u8 pte[];
पूर्ण;

प्रकार व्योम (*nvkm_vmm_pxe_func)(काष्ठा nvkm_vmm *,
				  काष्ठा nvkm_mmu_pt *, u32 ptei, u32 ptes);
प्रकार व्योम (*nvkm_vmm_pde_func)(काष्ठा nvkm_vmm *,
				  काष्ठा nvkm_vmm_pt *, u32 pdei);
प्रकार व्योम (*nvkm_vmm_pte_func)(काष्ठा nvkm_vmm *, काष्ठा nvkm_mmu_pt *,
				  u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *);

काष्ठा nvkm_vmm_desc_func अणु
	nvkm_vmm_pxe_func invalid;
	nvkm_vmm_pxe_func unmap;
	nvkm_vmm_pxe_func sparse;

	nvkm_vmm_pde_func pde;

	nvkm_vmm_pte_func mem;
	nvkm_vmm_pte_func dma;
	nvkm_vmm_pte_func sgl;

	nvkm_vmm_pte_func pfn;
	bool (*pfn_clear)(काष्ठा nvkm_vmm *, काष्ठा nvkm_mmu_pt *, u32 ptei, u32 ptes);
	nvkm_vmm_pxe_func pfn_unmap;
पूर्ण;

बाह्य स्थिर काष्ठा nvkm_vmm_desc_func gf100_vmm_pgd;
व्योम gf100_vmm_pgd_pde(काष्ठा nvkm_vmm *, काष्ठा nvkm_vmm_pt *, u32);
बाह्य स्थिर काष्ठा nvkm_vmm_desc_func gf100_vmm_pgt;
व्योम gf100_vmm_pgt_unmap(काष्ठा nvkm_vmm *, काष्ठा nvkm_mmu_pt *, u32, u32);
व्योम gf100_vmm_pgt_mem(काष्ठा nvkm_vmm *, काष्ठा nvkm_mmu_pt *, u32, u32,
		       काष्ठा nvkm_vmm_map *);
व्योम gf100_vmm_pgt_dma(काष्ठा nvkm_vmm *, काष्ठा nvkm_mmu_pt *, u32, u32,
		       काष्ठा nvkm_vmm_map *);
व्योम gf100_vmm_pgt_sgl(काष्ठा nvkm_vmm *, काष्ठा nvkm_mmu_pt *, u32, u32,
		       काष्ठा nvkm_vmm_map *);

व्योम gk104_vmm_lpt_invalid(काष्ठा nvkm_vmm *, काष्ठा nvkm_mmu_pt *, u32, u32);

काष्ठा nvkm_vmm_desc अणु
	क्रमागत अणु
		PGD,
		PGT,
		SPT,
		LPT,
	पूर्ण type;
	u8 bits;	/* VMA bits covered by PT. */
	u8 size;	/* Bytes-per-PTE. */
	u32 align;	/* PT address alignment. */
	स्थिर काष्ठा nvkm_vmm_desc_func *func;
पूर्ण;

बाह्य स्थिर काष्ठा nvkm_vmm_desc nv50_vmm_desc_12[];
बाह्य स्थिर काष्ठा nvkm_vmm_desc nv50_vmm_desc_16[];

बाह्य स्थिर काष्ठा nvkm_vmm_desc gk104_vmm_desc_16_12[];
बाह्य स्थिर काष्ठा nvkm_vmm_desc gk104_vmm_desc_16_16[];
बाह्य स्थिर काष्ठा nvkm_vmm_desc gk104_vmm_desc_17_12[];
बाह्य स्थिर काष्ठा nvkm_vmm_desc gk104_vmm_desc_17_17[];

बाह्य स्थिर काष्ठा nvkm_vmm_desc gm200_vmm_desc_16_12[];
बाह्य स्थिर काष्ठा nvkm_vmm_desc gm200_vmm_desc_16_16[];
बाह्य स्थिर काष्ठा nvkm_vmm_desc gm200_vmm_desc_17_12[];
बाह्य स्थिर काष्ठा nvkm_vmm_desc gm200_vmm_desc_17_17[];

बाह्य स्थिर काष्ठा nvkm_vmm_desc gp100_vmm_desc_12[];
बाह्य स्थिर काष्ठा nvkm_vmm_desc gp100_vmm_desc_16[];

काष्ठा nvkm_vmm_page अणु
	u8 shअगरt;
	स्थिर काष्ठा nvkm_vmm_desc *desc;
#घोषणा NVKM_VMM_PAGE_SPARSE                                               0x01
#घोषणा NVKM_VMM_PAGE_VRAM                                                 0x02
#घोषणा NVKM_VMM_PAGE_HOST                                                 0x04
#घोषणा NVKM_VMM_PAGE_COMP                                                 0x08
#घोषणा NVKM_VMM_PAGE_Sxxx                                (NVKM_VMM_PAGE_SPARSE)
#घोषणा NVKM_VMM_PAGE_xVxx                                  (NVKM_VMM_PAGE_VRAM)
#घोषणा NVKM_VMM_PAGE_SVxx             (NVKM_VMM_PAGE_Sxxx | NVKM_VMM_PAGE_VRAM)
#घोषणा NVKM_VMM_PAGE_xxHx                                  (NVKM_VMM_PAGE_HOST)
#घोषणा NVKM_VMM_PAGE_SxHx             (NVKM_VMM_PAGE_Sxxx | NVKM_VMM_PAGE_HOST)
#घोषणा NVKM_VMM_PAGE_xVHx             (NVKM_VMM_PAGE_xVxx | NVKM_VMM_PAGE_HOST)
#घोषणा NVKM_VMM_PAGE_SVHx             (NVKM_VMM_PAGE_SVxx | NVKM_VMM_PAGE_HOST)
#घोषणा NVKM_VMM_PAGE_xVxC             (NVKM_VMM_PAGE_xVxx | NVKM_VMM_PAGE_COMP)
#घोषणा NVKM_VMM_PAGE_SVxC             (NVKM_VMM_PAGE_SVxx | NVKM_VMM_PAGE_COMP)
#घोषणा NVKM_VMM_PAGE_xxHC             (NVKM_VMM_PAGE_xxHx | NVKM_VMM_PAGE_COMP)
#घोषणा NVKM_VMM_PAGE_SxHC             (NVKM_VMM_PAGE_SxHx | NVKM_VMM_PAGE_COMP)
	u8 type;
पूर्ण;

काष्ठा nvkm_vmm_func अणु
	पूर्णांक (*join)(काष्ठा nvkm_vmm *, काष्ठा nvkm_memory *inst);
	व्योम (*part)(काष्ठा nvkm_vmm *, काष्ठा nvkm_memory *inst);

	पूर्णांक (*aper)(क्रमागत nvkm_memory_target);
	पूर्णांक (*valid)(काष्ठा nvkm_vmm *, व्योम *argv, u32 argc,
		     काष्ठा nvkm_vmm_map *);
	व्योम (*flush)(काष्ठा nvkm_vmm *, पूर्णांक depth);

	पूर्णांक (*mthd)(काष्ठा nvkm_vmm *, काष्ठा nvkm_client *,
		    u32 mthd, व्योम *argv, u32 argc);

	व्योम (*invalidate_pdb)(काष्ठा nvkm_vmm *, u64 addr);

	u64 page_block;
	स्थिर काष्ठा nvkm_vmm_page page[];
पूर्ण;

काष्ठा nvkm_vmm_join अणु
	काष्ठा nvkm_memory *inst;
	काष्ठा list_head head;
पूर्ण;

पूर्णांक nvkm_vmm_new_(स्थिर काष्ठा nvkm_vmm_func *, काष्ठा nvkm_mmu *,
		  u32 pd_header, bool managed, u64 addr, u64 size,
		  काष्ठा lock_class_key *, स्थिर अक्षर *name,
		  काष्ठा nvkm_vmm **);
काष्ठा nvkm_vma *nvkm_vmm_node_search(काष्ठा nvkm_vmm *, u64 addr);
काष्ठा nvkm_vma *nvkm_vmm_node_split(काष्ठा nvkm_vmm *, काष्ठा nvkm_vma *,
				     u64 addr, u64 size);
पूर्णांक nvkm_vmm_get_locked(काष्ठा nvkm_vmm *, bool getref, bool mapref,
			bool sparse, u8 page, u8 align, u64 size,
			काष्ठा nvkm_vma **pvma);
व्योम nvkm_vmm_put_locked(काष्ठा nvkm_vmm *, काष्ठा nvkm_vma *);
व्योम nvkm_vmm_unmap_locked(काष्ठा nvkm_vmm *, काष्ठा nvkm_vma *, bool pfn);
व्योम nvkm_vmm_unmap_region(काष्ठा nvkm_vmm *, काष्ठा nvkm_vma *);

#घोषणा NVKM_VMM_PFN_ADDR                                 0xfffffffffffff000ULL
#घोषणा NVKM_VMM_PFN_ADDR_SHIFT                                              12
#घोषणा NVKM_VMM_PFN_APER                                 0x00000000000000f0ULL
#घोषणा NVKM_VMM_PFN_HOST                                 0x0000000000000000ULL
#घोषणा NVKM_VMM_PFN_VRAM                                 0x0000000000000010ULL
#घोषणा NVKM_VMM_PFN_W                                    0x0000000000000002ULL
#घोषणा NVKM_VMM_PFN_V                                    0x0000000000000001ULL
#घोषणा NVKM_VMM_PFN_NONE                                 0x0000000000000000ULL

पूर्णांक nvkm_vmm_pfn_map(काष्ठा nvkm_vmm *, u8 page, u64 addr, u64 size, u64 *pfn);
पूर्णांक nvkm_vmm_pfn_unmap(काष्ठा nvkm_vmm *, u64 addr, u64 size);

काष्ठा nvkm_vma *nvkm_vma_tail(काष्ठा nvkm_vma *, u64 tail);

पूर्णांक nv04_vmm_new_(स्थिर काष्ठा nvkm_vmm_func *, काष्ठा nvkm_mmu *, u32,
		  bool, u64, u64, व्योम *, u32, काष्ठा lock_class_key *,
		  स्थिर अक्षर *, काष्ठा nvkm_vmm **);
पूर्णांक nv04_vmm_valid(काष्ठा nvkm_vmm *, व्योम *, u32, काष्ठा nvkm_vmm_map *);

पूर्णांक nv50_vmm_join(काष्ठा nvkm_vmm *, काष्ठा nvkm_memory *);
व्योम nv50_vmm_part(काष्ठा nvkm_vmm *, काष्ठा nvkm_memory *);
पूर्णांक nv50_vmm_valid(काष्ठा nvkm_vmm *, व्योम *, u32, काष्ठा nvkm_vmm_map *);
व्योम nv50_vmm_flush(काष्ठा nvkm_vmm *, पूर्णांक);

पूर्णांक gf100_vmm_new_(स्थिर काष्ठा nvkm_vmm_func *, स्थिर काष्ठा nvkm_vmm_func *,
		   काष्ठा nvkm_mmu *, bool, u64, u64, व्योम *, u32,
		   काष्ठा lock_class_key *, स्थिर अक्षर *, काष्ठा nvkm_vmm **);
पूर्णांक gf100_vmm_join_(काष्ठा nvkm_vmm *, काष्ठा nvkm_memory *, u64 base);
पूर्णांक gf100_vmm_join(काष्ठा nvkm_vmm *, काष्ठा nvkm_memory *);
व्योम gf100_vmm_part(काष्ठा nvkm_vmm *, काष्ठा nvkm_memory *);
पूर्णांक gf100_vmm_aper(क्रमागत nvkm_memory_target);
पूर्णांक gf100_vmm_valid(काष्ठा nvkm_vmm *, व्योम *, u32, काष्ठा nvkm_vmm_map *);
व्योम gf100_vmm_flush(काष्ठा nvkm_vmm *, पूर्णांक);
व्योम gf100_vmm_invalidate(काष्ठा nvkm_vmm *, u32 type);
व्योम gf100_vmm_invalidate_pdb(काष्ठा nvkm_vmm *, u64 addr);

पूर्णांक gk20a_vmm_aper(क्रमागत nvkm_memory_target);

पूर्णांक gm200_vmm_new_(स्थिर काष्ठा nvkm_vmm_func *, स्थिर काष्ठा nvkm_vmm_func *,
		   काष्ठा nvkm_mmu *, bool, u64, u64, व्योम *, u32,
		   काष्ठा lock_class_key *, स्थिर अक्षर *, काष्ठा nvkm_vmm **);
पूर्णांक gm200_vmm_join_(काष्ठा nvkm_vmm *, काष्ठा nvkm_memory *, u64 base);
पूर्णांक gm200_vmm_join(काष्ठा nvkm_vmm *, काष्ठा nvkm_memory *);

पूर्णांक gp100_vmm_new_(स्थिर काष्ठा nvkm_vmm_func *,
		   काष्ठा nvkm_mmu *, bool, u64, u64, व्योम *, u32,
		   काष्ठा lock_class_key *, स्थिर अक्षर *, काष्ठा nvkm_vmm **);
पूर्णांक gp100_vmm_join(काष्ठा nvkm_vmm *, काष्ठा nvkm_memory *);
पूर्णांक gp100_vmm_valid(काष्ठा nvkm_vmm *, व्योम *, u32, काष्ठा nvkm_vmm_map *);
व्योम gp100_vmm_flush(काष्ठा nvkm_vmm *, पूर्णांक);
पूर्णांक gp100_vmm_mthd(काष्ठा nvkm_vmm *, काष्ठा nvkm_client *, u32, व्योम *, u32);
व्योम gp100_vmm_invalidate_pdb(काष्ठा nvkm_vmm *, u64 addr);

पूर्णांक gv100_vmm_join(काष्ठा nvkm_vmm *, काष्ठा nvkm_memory *);

पूर्णांक nv04_vmm_new(काष्ठा nvkm_mmu *, bool, u64, u64, व्योम *, u32,
		 काष्ठा lock_class_key *, स्थिर अक्षर *, काष्ठा nvkm_vmm **);
पूर्णांक nv41_vmm_new(काष्ठा nvkm_mmu *, bool, u64, u64, व्योम *, u32,
		 काष्ठा lock_class_key *, स्थिर अक्षर *, काष्ठा nvkm_vmm **);
पूर्णांक nv44_vmm_new(काष्ठा nvkm_mmu *, bool, u64, u64, व्योम *, u32,
		 काष्ठा lock_class_key *, स्थिर अक्षर *, काष्ठा nvkm_vmm **);
पूर्णांक nv50_vmm_new(काष्ठा nvkm_mmu *, bool, u64, u64, व्योम *, u32,
		 काष्ठा lock_class_key *, स्थिर अक्षर *, काष्ठा nvkm_vmm **);
पूर्णांक mcp77_vmm_new(काष्ठा nvkm_mmu *, bool, u64, u64, व्योम *, u32,
		  काष्ठा lock_class_key *, स्थिर अक्षर *, काष्ठा nvkm_vmm **);
पूर्णांक g84_vmm_new(काष्ठा nvkm_mmu *, bool, u64, u64, व्योम *, u32,
		काष्ठा lock_class_key *, स्थिर अक्षर *, काष्ठा nvkm_vmm **);
पूर्णांक gf100_vmm_new(काष्ठा nvkm_mmu *, bool, u64, u64, व्योम *, u32,
		  काष्ठा lock_class_key *, स्थिर अक्षर *, काष्ठा nvkm_vmm **);
पूर्णांक gk104_vmm_new(काष्ठा nvkm_mmu *, bool, u64, u64, व्योम *, u32,
		  काष्ठा lock_class_key *, स्थिर अक्षर *, काष्ठा nvkm_vmm **);
पूर्णांक gk20a_vmm_new(काष्ठा nvkm_mmu *, bool, u64, u64, व्योम *, u32,
		  काष्ठा lock_class_key *, स्थिर अक्षर *, काष्ठा nvkm_vmm **);
पूर्णांक gm200_vmm_new_fixed(काष्ठा nvkm_mmu *, bool, u64, u64, व्योम *, u32,
			काष्ठा lock_class_key *, स्थिर अक्षर *,
			काष्ठा nvkm_vmm **);
पूर्णांक gm200_vmm_new(काष्ठा nvkm_mmu *, bool, u64, u64, व्योम *, u32,
		  काष्ठा lock_class_key *, स्थिर अक्षर *,
		  काष्ठा nvkm_vmm **);
पूर्णांक gm20b_vmm_new_fixed(काष्ठा nvkm_mmu *, bool, u64, u64, व्योम *, u32,
			काष्ठा lock_class_key *, स्थिर अक्षर *,
			काष्ठा nvkm_vmm **);
पूर्णांक gm20b_vmm_new(काष्ठा nvkm_mmu *, bool, u64, u64, व्योम *, u32,
		  काष्ठा lock_class_key *, स्थिर अक्षर *,
		  काष्ठा nvkm_vmm **);
पूर्णांक gp100_vmm_new(काष्ठा nvkm_mmu *, bool, u64, u64, व्योम *, u32,
		  काष्ठा lock_class_key *, स्थिर अक्षर *,
		  काष्ठा nvkm_vmm **);
पूर्णांक gp10b_vmm_new(काष्ठा nvkm_mmu *, bool, u64, u64, व्योम *, u32,
		  काष्ठा lock_class_key *, स्थिर अक्षर *,
		  काष्ठा nvkm_vmm **);
पूर्णांक gv100_vmm_new(काष्ठा nvkm_mmu *, bool, u64, u64, व्योम *, u32,
		  काष्ठा lock_class_key *, स्थिर अक्षर *,
		  काष्ठा nvkm_vmm **);
पूर्णांक tu102_vmm_new(काष्ठा nvkm_mmu *, bool, u64, u64, व्योम *, u32,
		  काष्ठा lock_class_key *, स्थिर अक्षर *,
		  काष्ठा nvkm_vmm **);

#घोषणा VMM_PRINT(l,v,p,f,a...) करो अणु                                           \
	काष्ठा nvkm_vmm *_vmm = (v);                                           \
	अगर (CONFIG_NOUVEAU_DEBUG >= (l) && _vmm->debug >= (l)) अणु               \
		nvkm_prपूर्णांकk_(&_vmm->mmu->subdev, 0, p, "%s: "f"\n",            \
			     _vmm->name, ##a);                                 \
	पूर्ण                                                                      \
पूर्ण जबतक(0)
#घोषणा VMM_DEBUG(v,f,a...) VMM_PRINT(NV_DBG_DEBUG, (v), info, f, ##a)
#घोषणा VMM_TRACE(v,f,a...) VMM_PRINT(NV_DBG_TRACE, (v), info, f, ##a)
#घोषणा VMM_SPAM(v,f,a...)  VMM_PRINT(NV_DBG_SPAM , (v),  dbg, f, ##a)

#घोषणा VMM_MAP_ITER(VMM,PT,PTEI,PTEN,MAP,FILL,BASE,SIZE,NEXT) करो अणु            \
	nvkm_kmap((PT)->memory);                                               \
	जबतक (PTEN) अणु                                                         \
		u64 _ptes = ((SIZE) - MAP->off) >> MAP->page->shअगरt;           \
		u64 _addr = ((BASE) + MAP->off);                               \
                                                                               \
		अगर (_ptes > PTEN) अणु                                            \
			MAP->off += PTEN << MAP->page->shअगरt;                  \
			_ptes = PTEN;                                          \
		पूर्ण अन्यथा अणु                                                       \
			MAP->off = 0;                                          \
			NEXT;                                                  \
		पूर्ण                                                              \
                                                                               \
		VMM_SPAM(VMM, "ITER %08x %08x PTE(s)", PTEI, (u32)_ptes);      \
                                                                               \
		FILL(VMM, PT, PTEI, _ptes, MAP, _addr);                        \
		PTEI += _ptes;                                                 \
		PTEN -= _ptes;                                                 \
	पूर्ण                                                                      \
	nvkm_करोne((PT)->memory);                                               \
पूर्ण जबतक(0)

#घोषणा VMM_MAP_ITER_MEM(VMM,PT,PTEI,PTEN,MAP,FILL)                            \
	VMM_MAP_ITER(VMM,PT,PTEI,PTEN,MAP,FILL,                                \
		     ((u64)MAP->mem->offset << NVKM_RAM_MM_SHIFT),             \
		     ((u64)MAP->mem->length << NVKM_RAM_MM_SHIFT),             \
		     (MAP->mem = MAP->mem->next))
#घोषणा VMM_MAP_ITER_DMA(VMM,PT,PTEI,PTEN,MAP,FILL)                            \
	VMM_MAP_ITER(VMM,PT,PTEI,PTEN,MAP,FILL,                                \
		     *MAP->dma, PAGE_SIZE, MAP->dma++)
#घोषणा VMM_MAP_ITER_SGL(VMM,PT,PTEI,PTEN,MAP,FILL)                            \
	VMM_MAP_ITER(VMM,PT,PTEI,PTEN,MAP,FILL,                                \
		     sg_dma_address(MAP->sgl), sg_dma_len(MAP->sgl),           \
		     (MAP->sgl = sg_next(MAP->sgl)))

#घोषणा VMM_FO(m,o,d,c,b) nvkm_fo##b((m)->memory, (o), (d), (c))
#घोषणा VMM_WO(m,o,d,c,b) nvkm_wo##b((m)->memory, (o), (d))
#घोषणा VMM_XO(m,v,o,d,c,b,fn,f,a...) करो अणु                                     \
	स्थिर u32 _pteo = (o); u##b _data = (d);                               \
	VMM_SPAM((v), "   %010llx "f, (m)->addr + _pteo, _data, ##a);          \
	VMM_##fn((m), (m)->base + _pteo, _data, (c), b);                       \
पूर्ण जबतक(0)

#घोषणा VMM_WO032(m,v,o,d) VMM_XO((m),(v),(o),(d),  1, 32, WO, "%08x")
#घोषणा VMM_FO032(m,v,o,d,c)                                                   \
	VMM_XO((m),(v),(o),(d),(c), 32, FO, "%08x %08x", (c))

#घोषणा VMM_WO064(m,v,o,d) VMM_XO((m),(v),(o),(d),  1, 64, WO, "%016llx")
#घोषणा VMM_FO064(m,v,o,d,c)                                                   \
	VMM_XO((m),(v),(o),(d),(c), 64, FO, "%016llx %08x", (c))

#घोषणा VMM_XO128(m,v,o,lo,hi,c,f,a...) करो अणु                                   \
	u32 _pteo = (o), _ptes = (c);                                          \
	स्थिर u64 _addr = (m)->addr + _pteo;                                   \
	VMM_SPAM((v), "   %010llx %016llx%016llx"f, _addr, (hi), (lo), ##a);   \
	जबतक (_ptes--) अणु                                                      \
		nvkm_wo64((m)->memory, (m)->base + _pteo + 0, (lo));           \
		nvkm_wo64((m)->memory, (m)->base + _pteo + 8, (hi));           \
		_pteo += 0x10;                                                 \
	पूर्ण                                                                      \
पूर्ण जबतक(0)

#घोषणा VMM_WO128(m,v,o,lo,hi) VMM_XO128((m),(v),(o),(lo),(hi), 1, "")
#घोषणा VMM_FO128(m,v,o,lo,hi,c) करो अणु                                          \
	nvkm_kmap((m)->memory);                                                \
	VMM_XO128((m),(v),(o),(lo),(hi),(c), " %08x", (c));                    \
	nvkm_करोne((m)->memory);                                                \
पूर्ण जबतक(0)
#पूर्ण_अगर
