<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_MMU_H__
#घोषणा __NVKM_MMU_H__
#समावेश <core/subdev.h>

काष्ठा nvkm_vma अणु
	काष्ठा list_head head;
	काष्ठा rb_node tree;
	u64 addr;
	u64 size:50;
	bool mapref:1; /* PTs (de)referenced on (un)map (vs pre-allocated). */
	bool sparse:1; /* Unmapped PDEs/PTEs will not trigger MMU faults. */
#घोषणा NVKM_VMA_PAGE_NONE 7
	u8   page:3; /* Requested page type (index, or NONE क्रम स्वतःmatic). */
	u8   refd:3; /* Current page type (index, or NONE क्रम unreferenced). */
	bool used:1; /* Region allocated. */
	bool part:1; /* Region was split from an allocated region by map(). */
	bool user:1; /* Region user-allocated. */
	bool busy:1; /* Region busy (क्रम temporarily preventing user access). */
	bool mapped:1; /* Region contains valid pages. */
	काष्ठा nvkm_memory *memory; /* Memory currently mapped पूर्णांकo VMA. */
	काष्ठा nvkm_tags *tags; /* Compression tag reference. */
पूर्ण;

काष्ठा nvkm_vmm अणु
	स्थिर काष्ठा nvkm_vmm_func *func;
	काष्ठा nvkm_mmu *mmu;
	स्थिर अक्षर *name;
	u32 debug;
	काष्ठा kref kref;
	काष्ठा mutex mutex;

	u64 start;
	u64 limit;

	काष्ठा nvkm_vmm_pt *pd;
	काष्ठा list_head join;

	काष्ठा list_head list;
	काष्ठा rb_root मुक्त;
	काष्ठा rb_root root;

	bool bootstrapped;
	atomic_t engref[NVKM_SUBDEV_NR];

	dma_addr_t null;
	व्योम *nullp;

	bool replay;
पूर्ण;

पूर्णांक nvkm_vmm_new(काष्ठा nvkm_device *, u64 addr, u64 size, व्योम *argv, u32 argc,
		 काष्ठा lock_class_key *, स्थिर अक्षर *name, काष्ठा nvkm_vmm **);
काष्ठा nvkm_vmm *nvkm_vmm_ref(काष्ठा nvkm_vmm *);
व्योम nvkm_vmm_unref(काष्ठा nvkm_vmm **);
पूर्णांक nvkm_vmm_boot(काष्ठा nvkm_vmm *);
पूर्णांक nvkm_vmm_join(काष्ठा nvkm_vmm *, काष्ठा nvkm_memory *inst);
व्योम nvkm_vmm_part(काष्ठा nvkm_vmm *, काष्ठा nvkm_memory *inst);
पूर्णांक nvkm_vmm_get(काष्ठा nvkm_vmm *, u8 page, u64 size, काष्ठा nvkm_vma **);
व्योम nvkm_vmm_put(काष्ठा nvkm_vmm *, काष्ठा nvkm_vma **);

काष्ठा nvkm_vmm_map अणु
	काष्ठा nvkm_memory *memory;
	u64 offset;

	काष्ठा nvkm_mm_node *mem;
	काष्ठा scatterlist *sgl;
	dma_addr_t *dma;
	u64 *pfn;
	u64 off;

	स्थिर काष्ठा nvkm_vmm_page *page;

	काष्ठा nvkm_tags *tags;
	u64 next;
	u64 type;
	u64 ctag;
पूर्ण;

पूर्णांक nvkm_vmm_map(काष्ठा nvkm_vmm *, काष्ठा nvkm_vma *, व्योम *argv, u32 argc,
		 काष्ठा nvkm_vmm_map *);
व्योम nvkm_vmm_unmap(काष्ठा nvkm_vmm *, काष्ठा nvkm_vma *);

काष्ठा nvkm_memory *nvkm_umem_search(काष्ठा nvkm_client *, u64);
काष्ठा nvkm_vmm *nvkm_uvmm_search(काष्ठा nvkm_client *, u64 handle);

काष्ठा nvkm_mmu अणु
	स्थिर काष्ठा nvkm_mmu_func *func;
	काष्ठा nvkm_subdev subdev;

	u8  dma_bits;

	पूर्णांक heap_nr;
	काष्ठा अणु
#घोषणा NVKM_MEM_VRAM                                                      0x01
#घोषणा NVKM_MEM_HOST                                                      0x02
#घोषणा NVKM_MEM_COMP                                                      0x04
#घोषणा NVKM_MEM_DISP                                                      0x08
		u8  type;
		u64 size;
	पूर्ण heap[4];

	पूर्णांक type_nr;
	काष्ठा अणु
#घोषणा NVKM_MEM_KIND                                                      0x10
#घोषणा NVKM_MEM_MAPPABLE                                                  0x20
#घोषणा NVKM_MEM_COHERENT                                                  0x40
#घोषणा NVKM_MEM_UNCACHED                                                  0x80
		u8 type;
		u8 heap;
	पूर्ण type[16];

	काष्ठा nvkm_vmm *vmm;

	काष्ठा अणु
		काष्ठा mutex mutex;
		काष्ठा list_head list;
	पूर्ण ptc, ptp;

	काष्ठा mutex mutex; /* serialises mmu invalidations */

	काष्ठा nvkm_device_oclass user;
पूर्ण;

पूर्णांक nv04_mmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mmu **);
पूर्णांक nv41_mmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mmu **);
पूर्णांक nv44_mmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mmu **);
पूर्णांक nv50_mmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mmu **);
पूर्णांक g84_mmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mmu **);
पूर्णांक mcp77_mmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mmu **);
पूर्णांक gf100_mmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mmu **);
पूर्णांक gk104_mmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mmu **);
पूर्णांक gk20a_mmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mmu **);
पूर्णांक gm200_mmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mmu **);
पूर्णांक gm20b_mmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mmu **);
पूर्णांक gp100_mmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mmu **);
पूर्णांक gp10b_mmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mmu **);
पूर्णांक gv100_mmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mmu **);
पूर्णांक tu102_mmu_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mmu **);
#पूर्ण_अगर
